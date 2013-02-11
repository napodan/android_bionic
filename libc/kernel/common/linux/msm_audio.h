/****************************************************************************
 ****************************************************************************
 ***
 ***   This header was automatically generated from a Linux kernel header
 ***   of the same name, to make information necessary for userspace to
 ***   call into the kernel available to libc.  It contains only constants,
 ***   structures, and macros generated from the original header, and thus,
 ***   contains no copyrightable information.
 ***
 ***   To edit the content of this header, modify the corresponding
 ***   source file (e.g. under external/kernel-headers/original/) then
 ***   run bionic/libc/kernel/tools/update_all.py
 ***
 ***   Any manual change here will be lost the next time this script will
 ***   be run. You've been warned!
 ***
 ****************************************************************************
 ****************************************************************************/
#ifndef __LINUX_MSM_AUDIO_H
#define __LINUX_MSM_AUDIO_H
#include <linux/types.h>
#include <linux/ioctl.h>
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#include <asm/sizes.h>
#define AUDIO_IOCTL_MAGIC 'a'
#define AUDIO_START _IOW(AUDIO_IOCTL_MAGIC, 0, unsigned)
#define AUDIO_STOP _IOW(AUDIO_IOCTL_MAGIC, 1, unsigned)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_FLUSH _IOW(AUDIO_IOCTL_MAGIC, 2, unsigned)
#define AUDIO_GET_CONFIG _IOR(AUDIO_IOCTL_MAGIC, 3, unsigned)
#define AUDIO_SET_CONFIG _IOW(AUDIO_IOCTL_MAGIC, 4, unsigned)
#define AUDIO_GET_STATS _IOR(AUDIO_IOCTL_MAGIC, 5, unsigned)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_ENABLE_AUDPP _IOW(AUDIO_IOCTL_MAGIC, 6, unsigned)
#define AUDIO_SET_ADRC _IOW(AUDIO_IOCTL_MAGIC, 7, unsigned)
#define AUDIO_SET_EQ _IOW(AUDIO_IOCTL_MAGIC, 8, unsigned)
#define AUDIO_SET_RX_IIR _IOW(AUDIO_IOCTL_MAGIC, 9, unsigned)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_SET_VOLUME _IOW(AUDIO_IOCTL_MAGIC, 10, unsigned)
#define AUDIO_ENABLE_AUDPRE _IOW(AUDIO_IOCTL_MAGIC, 11, unsigned)
#define AUDIO_SET_AGC _IOW(AUDIO_IOCTL_MAGIC, 12, unsigned)
#define AUDIO_SET_NS _IOW(AUDIO_IOCTL_MAGIC, 13, unsigned)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_SET_TX_IIR _IOW(AUDIO_IOCTL_MAGIC, 14, unsigned)
#define AUDIO_PAUSE _IOW(AUDIO_IOCTL_MAGIC, 15, unsigned)
#define AUDIO_SET_AAC_CONFIG _IOW(AUDIO_IOCTL_MAGIC, 15, unsigned)
#define AUDIO_WAIT_ADSP_DONE _IOR(AUDIO_IOCTL_MAGIC, 16, unsigned)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_ADSP_PAUSE _IOR(AUDIO_IOCTL_MAGIC, 17, unsigned)
#define AUDIO_ADSP_RESUME _IOR(AUDIO_IOCTL_MAGIC, 18, unsigned)
#define AUDIO_PLAY_DTMF _IOW(AUDIO_IOCTL_MAGIC, 19, unsigned)
#define AUDIO_GET_AAC_CONFIG _IOR(AUDIO_IOCTL_MAGIC, 20, unsigned)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_GET_AMRNB_ENC_CONFIG _IOW(AUDIO_IOCTL_MAGIC, 21, unsigned)
#define AUDIO_SET_AMRNB_ENC_CONFIG _IOR(AUDIO_IOCTL_MAGIC, 22, unsigned)
#define AUDIO_GET_PCM_CONFIG _IOR(AUDIO_IOCTL_MAGIC, 30, unsigned)
#define AUDIO_SET_PCM_CONFIG _IOW(AUDIO_IOCTL_MAGIC, 31, unsigned)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_SWITCH_DEVICE _IOW(AUDIO_IOCTL_MAGIC, 32, unsigned)
#define AUDIO_SET_MUTE _IOW(AUDIO_IOCTL_MAGIC, 33, unsigned)
#define AUDIO_UPDATE_ACDB _IOW(AUDIO_IOCTL_MAGIC, 34, unsigned)
#define AUDIO_START_VOICE _IOW(AUDIO_IOCTL_MAGIC, 35, unsigned)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_STOP_VOICE _IOW(AUDIO_IOCTL_MAGIC, 36, unsigned)
#define AUDIO_START_FM _IOW(AUDIO_IOCTL_MAGIC, 37, unsigned)
#define AUDIO_STOP_FM _IOW(AUDIO_IOCTL_MAGIC, 38, unsigned)
#define AUDIO_REINIT_ACDB _IOW(AUDIO_IOCTL_MAGIC, 39, unsigned)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_ENABLE_AUXPGA_LOOPBACK _IOW(AUDIO_IOCTL_MAGIC, 40, unsigned)
#define AUDIO_SET_AUXPGA_GAIN _IOW(AUDIO_IOCTL_MAGIC, 41, unsigned)
#define AUDIO_SET_RX_MUTE _IOW(AUDIO_IOCTL_MAGIC, 42, unsigned)
#define AUDIO_MAX_COMMON_IOCTL_NUM 100
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_MAX_COMMON_IOCTL_NUM 100
struct msm_audio_config {
 uint32_t buffer_size;
 uint32_t buffer_count;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t channel_count;
 uint32_t sample_rate;
 uint32_t type;
 uint32_t unused[3];
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_audio_stats {
 uint32_t byte_count;
 uint32_t sample_count;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t unused[2];
};
struct msm_mute_info {
 uint32_t mute;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t path;
};
#define AUDIO_AAC_FORMAT_ADTS -1
#define AUDIO_AAC_FORMAT_RAW 0x0000
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_AAC_FORMAT_PSUEDO_RAW 0x0001
#define AUDIO_AAC_FORMAT_LOAS 0x0002
#define AUDIO_AAC_OBJECT_LC 0x0002
#define AUDIO_AAC_OBJECT_LTP 0x0004
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_AAC_OBJECT_ERLC 0x0011
#define AUDIO_AAC_SEC_DATA_RES_ON 0x0001
#define AUDIO_AAC_SEC_DATA_RES_OFF 0x0000
#define AUDIO_AAC_SCA_DATA_RES_ON 0x0001
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_AAC_SCA_DATA_RES_OFF 0x0000
#define AUDIO_AAC_SPEC_DATA_RES_ON 0x0001
#define AUDIO_AAC_SPEC_DATA_RES_OFF 0x0000
#define AUDIO_AAC_SBR_ON_FLAG_ON 0x0001
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_AAC_SBR_ON_FLAG_OFF 0x0000
#define AUDIO_AAC_SBR_PS_ON_FLAG_ON 0x0001
#define AUDIO_AAC_SBR_PS_ON_FLAG_OFF 0x0000
#define AUDIO_AAC_DUAL_MONO_PL_PR 0
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AUDIO_AAC_DUAL_MONO_SL_SR 1
#define AUDIO_AAC_DUAL_MONO_SL_PR 2
#define AUDIO_AAC_DUAL_MONO_PL_SR 3
#define AAC_OBJECT_ER_LC 17
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define AAC_OBJECT_ER_LTP 19
#define AAC_OBJECT_ER_SCALABLE 20
#define AAC_OBJECT_BSAC 22
#define AAC_OBJECT_ER_LD 23
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct aac_format {
 uint16_t sample_rate;
 uint16_t channel_config;
 uint16_t block_formats;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t audio_object_type;
 uint16_t ep_config;
 uint16_t aac_section_data_resilience_flag;
 uint16_t aac_scalefactor_data_resilience_flag;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint16_t aac_spectral_data_resilience_flag;
 uint16_t sbr_on_flag;
 uint16_t sbr_ps_on_flag;
 uint32_t bit_rate;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_audio_aac_config {
 signed short format;
 unsigned short audio_object;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 unsigned short ep_config;
 unsigned short aac_section_data_resilience_flag;
 unsigned short aac_scalefactor_data_resilience_flag;
 unsigned short aac_spectral_data_resilience_flag;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 unsigned short sbr_on_flag;
 unsigned short sbr_ps_on_flag;
 unsigned short dual_mono_mode;
 unsigned short channel_configuration;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
struct msm_audio_amrnb_enc_config {
 unsigned short voicememoencweight1;
 unsigned short voicememoencweight2;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 unsigned short voicememoencweight3;
 unsigned short voicememoencweight4;
 unsigned short dtx_mode_enable;
 unsigned short test_mode_enable;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 unsigned short enc_mode;
};
#define SND_IOCTL_MAGIC 's'
#define SND_MUTE_UNMUTED 0
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
#define SND_MUTE_MUTED 1
struct msm_snd_device_config {
 uint32_t device;
 uint32_t ear_mute;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 uint32_t mic_mute;
};
#define SND_SET_DEVICE _IOW(SND_IOCTL_MAGIC, 2, struct msm_device_config *)
#define SND_METHOD_VOICE 0
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_snd_volume_config {
 uint32_t device;
 uint32_t method;
 uint32_t volume;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
#define SND_SET_VOLUME _IOW(SND_IOCTL_MAGIC, 3, struct msm_snd_volume_config *)
#define SND_GET_NUM_ENDPOINTS _IOR(SND_IOCTL_MAGIC, 4, unsigned *)
struct msm_snd_endpoint {
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
 int id;
 char name[64];
};
#define SND_GET_ENDPOINT _IOWR(SND_IOCTL_MAGIC, 5, struct msm_snd_endpoint *)
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
struct msm_audio_pcm_config {
 uint32_t pcm_feedback;
 uint32_t buffer_count;
 uint32_t buffer_size;
/* WARNING: DO NOT EDIT, AUTO-GENERATED CODE - SEE TOP FOR INSTRUCTIONS */
};
#endif
