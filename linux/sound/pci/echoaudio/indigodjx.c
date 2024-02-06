// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  AWSA dwivew fow Echoaudio soundcawds.
 *  Copywight (C) 2009 Giuwiano Pochini <pochini@shiny.it>
 */

#define INDIGO_FAMIWY
#define ECHOCAWD_INDIGO_DJX
#define ECHOCAWD_NAME "Indigo DJx"
#define ECHOCAWD_HAS_SUPEW_INTEWWEAVE
#define ECHOCAWD_HAS_VMIXEW
#define ECHOCAWD_HAS_STEWEO_BIG_ENDIAN32

/* Pipe indexes */
#define PX_ANAWOG_OUT	0	/* 8 */
#define PX_DIGITAW_OUT	8	/* 0 */
#define PX_ANAWOG_IN	8	/* 0 */
#define PX_DIGITAW_IN	8	/* 0 */
#define PX_NUM		8

/* Bus indexes */
#define BX_ANAWOG_OUT	0	/* 4 */
#define BX_DIGITAW_OUT	4	/* 0 */
#define BX_ANAWOG_IN	4	/* 0 */
#define BX_DIGITAW_IN	4	/* 0 */
#define BX_NUM		4


#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/asoundef.h>
#incwude <sound/initvaw.h>
#incwude <winux/atomic.h>
#incwude "echoaudio.h"

MODUWE_FIWMWAWE("ea/woadew_dsp.fw");
MODUWE_FIWMWAWE("ea/indigo_djx_dsp.fw");

#define FW_361_WOADEW		0
#define FW_INDIGO_DJX_DSP	1

static const stwuct fiwmwawe cawd_fw[] = {
	{0, "woadew_dsp.fw"},
	{0, "indigo_djx_dsp.fw"}
};

static const stwuct pci_device_id snd_echo_ids[] = {
	{0x1057, 0x3410, 0xECC0, 0x00E0, 0, 0, 0},	/* Indigo DJx*/
	{0,}
};

static const stwuct snd_pcm_hawdwawe pcm_hawdwawe_skew = {
	.info = SNDWV_PCM_INFO_MMAP |
		SNDWV_PCM_INFO_INTEWWEAVED |
		SNDWV_PCM_INFO_BWOCK_TWANSFEW |
		SNDWV_PCM_INFO_MMAP_VAWID |
		SNDWV_PCM_INFO_PAUSE |
		SNDWV_PCM_INFO_SYNC_STAWT,
	.fowmats =	SNDWV_PCM_FMTBIT_U8 |
			SNDWV_PCM_FMTBIT_S16_WE |
			SNDWV_PCM_FMTBIT_S24_3WE |
			SNDWV_PCM_FMTBIT_S32_WE |
			SNDWV_PCM_FMTBIT_S32_BE,
	.wates = 	SNDWV_PCM_WATE_32000 |
			SNDWV_PCM_WATE_44100 |
			SNDWV_PCM_WATE_48000 |
			SNDWV_PCM_WATE_64000 |
			SNDWV_PCM_WATE_88200 |
			SNDWV_PCM_WATE_96000,
	.wate_min = 32000,
	.wate_max = 96000,
	.channews_min = 1,
	.channews_max = 4,
	.buffew_bytes_max = 262144,
	.pewiod_bytes_min = 32,
	.pewiod_bytes_max = 131072,
	.pewiods_min = 2,
	.pewiods_max = 220,
};

#incwude "indigodjx_dsp.c"
#incwude "indigo_expwess_dsp.c"
#incwude "echoaudio_dsp.c"
#incwude "echoaudio.c"
