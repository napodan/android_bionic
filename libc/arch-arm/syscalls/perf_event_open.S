/* autogenerated by gensyscalls.py */
#include <machine/asm.h>
#include <sys/linux-syscalls.h>

ENTRY(perf_event_open)
    mov     ip, sp
    .save   {r4, r5, r6, r7}
    stmfd   sp!, {r4, r5, r6, r7}
    ldmfd   ip, {r4, r5, r6}
    ldr     r7, =__NR_perf_event_open
    swi     #0
    ldmfd   sp!, {r4, r5, r6, r7}
    movs    r0, r0
    bxpl    lr
    b       __set_syscall_errno
END(perf_event_open)
