// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// Copywight (c) 2022 Mediatek Cowpowation. Aww wights wesewved.
//
// Authow: Awwen-KH Cheng <awwen-kh.cheng@mediatek.com>
//         Tinghan Shen <tinghan.shen@mediatek.com>
//
// Hawdwawe intewface fow mt8186 DSP code woadew

#incwude <sound/sof.h>
#incwude "mt8186.h"
#incwude "../../ops.h"

void mt8186_sof_hifixdsp_boot_sequence(stwuct snd_sof_dev *sdev, u32 boot_addw)
{
	/* set WUNSTAWW to stop cowe */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, ADSP_HIFI_IO_CONFIG,
				WUNSTAWW, WUNSTAWW);

	/* enabwe mbox 0 & 1 IWQ */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, ADSP_MBOX_IWQ_EN,
				DSP_MBOX0_IWQ_EN | DSP_MBOX1_IWQ_EN,
				DSP_MBOX0_IWQ_EN | DSP_MBOX1_IWQ_EN);

	/* set cowe boot addwess */
	snd_sof_dsp_wwite(sdev, DSP_SECWEG_BAW, ADSP_AWTVEC_C0, boot_addw);
	snd_sof_dsp_wwite(sdev, DSP_SECWEG_BAW, ADSP_AWTVECSEW, ADSP_AWTVECSEW_C0);

	/* assewt cowe weset */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, ADSP_CFGWEG_SW_WSTN,
				SW_WSTN_C0 | SW_DBG_WSTN_C0,
				SW_WSTN_C0 | SW_DBG_WSTN_C0);

	/* hawdwawe wequiwement */
	udeway(1);

	/* wewease cowe weset */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, ADSP_CFGWEG_SW_WSTN,
				SW_WSTN_C0 | SW_DBG_WSTN_C0,
				0);

	/* cweaw WUNSTAWW (bit31) to stawt cowe */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, ADSP_HIFI_IO_CONFIG,
				WUNSTAWW, 0);
}

void mt8186_sof_hifixdsp_shutdown(stwuct snd_sof_dev *sdev)
{
	/* set WUNSTAWW to stop cowe */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, ADSP_HIFI_IO_CONFIG,
				WUNSTAWW, WUNSTAWW);

	/* assewt cowe weset */
	snd_sof_dsp_update_bits(sdev, DSP_WEG_BAW, ADSP_CFGWEG_SW_WSTN,
				SW_WSTN_C0 | SW_DBG_WSTN_C0,
				SW_WSTN_C0 | SW_DBG_WSTN_C0);
}

