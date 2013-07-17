LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	arch/$(TARGET_ARCH)/begin.S \
	linker.c \
	linker_format.c \
	rt.c \
	dlfcn.c \
	debugger.c \
	ba.c

ifeq ($(TARGET_ARCH),sh)
# SH-4A series virtual address range from 0x00000000 to 0x7FFFFFFF.
LINKER_TEXT_BASE := 0x70000100
else
# This is aligned to 4K page boundary so that both GNU ld and gold work.  Gold
# actually produces a correct binary with starting address 0xB0000100 but the
# extra objcopy step to rename symbols causes the resulting binary to be misaligned
# and unloadable.  Increasing the alignment adds an extra 3840 bytes in padding
# but switching to gold saves about 1M of space.
LINKER_TEXT_BASE := 0xB0001000
endif

# The maximum size set aside for the linker, from
# LINKER_TEXT_BASE rounded down to a megabyte.
LINKER_AREA_SIZE := 0x01000000

LOCAL_LDFLAGS := -Wl,-Ttext,$(LINKER_TEXT_BASE)

LOCAL_CFLAGS += -DPRELINK
LOCAL_CFLAGS += -DLINKER_TEXT_BASE=$(LINKER_TEXT_BASE)
LOCAL_CFLAGS += -DLINKER_AREA_SIZE=$(LINKER_AREA_SIZE)

# Set LINKER_DEBUG to either 1 or 0
#
LOCAL_CFLAGS += -DLINKER_DEBUG=0

# We need to access Bionic private headers in the linker...
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../libc/

# ...one of which is <private/bionic_tls.h>, for which we
# need HAVE_ARM_TLS_REGISTER.
ifeq ($(TARGET_ARCH)-$(ARCH_ARM_HAVE_TLS_REGISTER),arm-true)
    LOCAL_CFLAGS += -DHAVE_ARM_TLS_REGISTER
endif

ifeq ($(TARGET_ARCH),arm)
    LOCAL_CFLAGS += -DANDROID_ARM_LINKER
endif

ifeq ($(TARGET_ARCH),x86)
    LOCAL_CFLAGS += -DANDROID_X86_LINKER
endif

ifeq ($(TARGET_ARCH),mips)
    LOCAL_CFLAGS += -DANDROID_MIPS_LINKER
endif

LOCAL_MODULE:= linker
LOCAL_ADDITIONAL_DEPENDENCIES := $(LOCAL_PATH)/Android.mk

LOCAL_STATIC_LIBRARIES := libc_nomalloc

#LOCAL_FORCE_STATIC_EXECUTABLE := true # not necessary when not including BUILD_EXECUTABLE

#
# include $(BUILD_EXECUTABLE)
#
# Instead of including $(BUILD_EXECUTABLE), we execute the steps to create an executable by
# hand, as we want to insert an extra step that is not supported by the build system, and
# is probably specific the linker only, so there's no need to modify the build system for
# the purpose.

LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_SUFFIX := $(TARGET_EXECUTABLE_SUFFIX)

# we don't want crtbegin.o (because we have begin.o), so unset it
# just for this module
LOCAL_NO_CRT := true

include $(BUILD_SYSTEM)/dynamic_binary.mk

# See build/core/executable.mk
$(linked_module): PRIVATE_TARGET_GLOBAL_LD_DIRS := $(TARGET_GLOBAL_LD_DIRS)
$(linked_module): PRIVATE_TARGET_GLOBAL_LDFLAGS := $(TARGET_GLOBAL_LDFLAGS)
$(linked_module): PRIVATE_TARGET_FDO_LIB := $(TARGET_FDO_LIB)
$(linked_module): PRIVATE_TARGET_LIBGCC := $(TARGET_LIBGCC)
$(linked_module): PRIVATE_TARGET_CRTBEGIN_DYNAMIC_O := $(TARGET_CRTBEGIN_DYNAMIC_O)
$(linked_module): PRIVATE_TARGET_CRTBEGIN_STATIC_O := $(TARGET_CRTBEGIN_STATIC_O)
$(linked_module): PRIVATE_TARGET_CRTEND_O := $(TARGET_CRTEND_O)
$(linked_module): $(TARGET_CRTBEGIN_STATIC_O) $(all_objects) $(all_libraries) $(TARGET_CRTEND_O)
	$(transform-o-to-static-executable)
	@echo "target PrefixSymbols: $(PRIVATE_MODULE) ($@)"
	$(hide) $(TARGET_OBJCOPY) --prefix-symbols=__dl_ $@

#
# end of BUILD_EXECUTABLE hack
#
