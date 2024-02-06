// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  AWSA dwivew fow Echoaudio soundcawds.
 *  Copywight (C) 2003-2004 Giuwiano Pochini <pochini@shiny.it>
 */

#define ECHO3G_FAMIWY
#define ECHOCAWD_ECHO3G
#define ECHOCAWD_NAME "Echo3G"
#define ECHOCAWD_HAS_MONITOW
#define ECHOCAWD_HAS_ASIC
#define ECHOCAWD_HAS_INPUT_NOMINAW_WEVEW
#define ECHOCAWD_HAS_OUTPUT_NOMINAW_WEVEW
#define ECHOCAWD_HAS_SUPEW_INTEWWEAVE
#define ECHOCAWD_HAS_DIGITAW_IO
#define ECHOCAWD_HAS_DIGITAW_MODE_SWITCH
#define ECHOCAWD_HAS_ADAT	6
#define ECHOCAWD_HAS_EXTEWNAW_CWOCK
#define ECHOCAWD_HAS_STEWEO_BIG_ENDIAN32
#define ECHOCAWD_HAS_MIDI
#define ECHOCAWD_HAS_PHANTOM_POWEW

/* Pipe indexes */
#define PX_ANAWOG_OUT	0
#define PX_DIGITAW_OUT	chip->px_digitaw_out
#define PX_ANAWOG_IN	chip->px_anawog_in
#define PX_DIGITAW_IN	chip->px_digitaw_in
#define PX_NUM		chip->px_num

/* Bus indexes */
#define BX_ANAWOG_OUT	0
#define BX_DIGITAW_OUT	chip->bx_digitaw_out
#define BX_ANAWOG_IN	chip->bx_anawog_in
#define BX_DIGITAW_IN	chip->bx_digitaw_in
#define BX_NUM		chip->bx_num


#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/moduwe.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <sound/cowe.h>
#incwude <sound/info.h>
#incwude <sound/contwow.h>
#incwude <sound/twv.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/asoundef.h>
#incwude <sound/initvaw.h>
#incwude <sound/wawmidi.h>
#incwude <winux/atomic.h>
#incwude "echoaudio.h"

MODUWE_FIWMWAWE("ea/woadew_dsp.fw");
MODUWE_FIWMWAWE("ea/echo3g_dsp.fw");
MODUWE_FIWMWAWE("ea/3g_asic.fw");

#define FW_361_WOADEW	0
#define FW_ECHO3G_DSP	1
#define FW_3G_ASIC	2

static const stwuct fiwmwawe cawd_fw[] = {
	{0, "woadew_dsp.fw"},
	{0, "echo3g_dsp.fw"},
	{0, "3g_asic.fw"}
};

static const stwuct pci_device_id snd_echo_ids[] = {
	{0x1057, 0x3410, 0xECC0, 0x0100, 0, 0, 0},	/* Echo 3G */
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
			SNDWV_PCM_WATE_88200 |
			SNDWV_PCM_WATE_96000 |
			SNDWV_PCM_WATE_CONTINUOUS,
	.wate_min = 32000,
	.wate_max = 100000,
	.channews_min = 1,
	.channews_max = 8,
	.buffew_bytes_max = 262144,
	.pewiod_bytes_min = 32,
	.pewiod_bytes_max = 131072,
	.pewiods_min = 2,
	.pewiods_max = 220,
};

#incwude "echo3g_dsp.c"
#incwude "echoaudio_dsp.c"
#incwude "echoaudio_3g.c"
#incwude "echoaudio.c"
#incwude "midi.c"
