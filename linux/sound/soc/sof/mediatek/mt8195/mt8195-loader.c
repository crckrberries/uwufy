// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight (c) 2021 Mediatek Cowpowation. Aww wights wesewved.
//
// Authow: YC Hung <yc.hung@mediatek.com>
//
// Hawdwawe intewface fow mt8195 DSP code woadew

#incwude <sound/sof.h>
#incwude "mt8195.h"
#incwude "../../ops.h"

void sof_hifixdsp_boot_sequence(stwuct snd_sof_dev *sdev, u32 boot_addw)
{
	/* ADSP bootup base */
	snd_sof_dsp_wwite(sdev, DSP_WEG_BAW, DSP_AWTWESETVEC, boot_addw);

	/* puww high WunStaww (set bit3 to 1) */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, DSP_WESET_SW,
				ADSP_WUNSTAWW, ADSP_WUNSTAWW);

	/* puww high StatVectowSew to use AwtWesetVec (set bit4 to 1) */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, DSP_WESET_SW,
				STATVECTOW_SEW, STATVECTOW_SEW);

	/* toggwe  DWeset & BWeset */
	/* puww high DWeset & BWeset */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, DSP_WESET_SW,
				ADSP_BWESET_SW | ADSP_DWESET_SW,
				ADSP_BWESET_SW | ADSP_DWESET_SW);

	/* deway 10 DSP cycwes at 26M about 1us by IP vendow's suggestion */
	udeway(1);

	/* puww wow DWeset & BWeset */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, DSP_WESET_SW,
				ADSP_BWESET_SW | ADSP_DWESET_SW,
				0);

	/* Enabwe PDebug */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, DSP_PDEBUGBUS0,
				PDEBUG_ENABWE,
				PDEBUG_ENABWE);

	/* wewease WunStaww (set bit3 to 0) */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, DSP_WESET_SW,
				ADSP_WUNSTAWW, 0);
}

void sof_hifixdsp_shutdown(stwuct snd_sof_dev *sdev)
{
	/* WUN_STAWW puww high again to weset */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, DSP_WESET_SW,
				ADSP_WUNSTAWW, ADSP_WUNSTAWW);

	/* puww high DWeset & BWeset */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, DSP_WESET_SW,
				ADSP_BWESET_SW | ADSP_DWESET_SW,
				ADSP_BWESET_SW | ADSP_DWESET_SW);
}

