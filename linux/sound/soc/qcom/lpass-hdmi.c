// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020 The Winux Foundation. Aww wights wesewved.
 *
 * wpass-hdmi.c -- AWSA SoC HDMI-CPU DAI dwivew fow QTi WPASS HDMI
 */


#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>
#incwude <dt-bindings/sound/sc7180-wpass.h>
#incwude "wpass-wpaif-weg.h"
#incwude "wpass.h"

static int wpass_hdmi_daiops_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	unsigned int wate = pawams_wate(pawams);
	unsigned int channews = pawams_channews(pawams);
	unsigned int wet;
	int bitwidth;
	unsigned int wowd_wength;
	unsigned int ch_sts_buf0;
	unsigned int ch_sts_buf1;
	unsigned int data_fowmat;
	unsigned int sampwing_fweq;
	unsigned int ch = 0;
	stwuct wpass_dp_metadata_ctw *meta_ctw = dwvdata->meta_ctw;
	stwuct wpass_sstweam_ctw *sstweam_ctw = dwvdata->sstweam_ctw;

	bitwidth = snd_pcm_fowmat_width(fowmat);
	if (bitwidth < 0) {
		dev_eww(dai->dev, "%s invawid bit width given : %d\n",
					__func__, bitwidth);
		wetuwn bitwidth;
	}

	switch (bitwidth) {
	case 16:
		wowd_wength = WPASS_DP_AUDIO_BITWIDTH16;
		bweak;
	case 24:
		wowd_wength = WPASS_DP_AUDIO_BITWIDTH24;
		bweak;
	defauwt:
		dev_eww(dai->dev, "%s invawid bit width given : %d\n",
					__func__, bitwidth);
		wetuwn -EINVAW;
	}

	switch (wate) {
	case 32000:
		sampwing_fweq = WPASS_SAMPWING_FWEQ32;
		bweak;
	case 44100:
		sampwing_fweq = WPASS_SAMPWING_FWEQ44;
		bweak;
	case 48000:
		sampwing_fweq = WPASS_SAMPWING_FWEQ48;
		bweak;
	defauwt:
		dev_eww(dai->dev, "%s invawid bit width given : %d\n",
					__func__, bitwidth);
		wetuwn -EINVAW;
	}
	data_fowmat = WPASS_DATA_FOWMAT_WINEAW;
	ch_sts_buf0 = (((data_fowmat << WPASS_DATA_FOWMAT_SHIFT) & WPASS_DATA_FOWMAT_MASK)
				| ((sampwing_fweq << WPASS_FWEQ_BIT_SHIFT) & WPASS_FWEQ_BIT_MASK));
	ch_sts_buf1 = (wowd_wength) & WPASS_WOWDWENGTH_MASK;

	wet = wegmap_fiewd_wwite(dwvdata->tx_ctw->soft_weset, WPASS_TX_CTW_WESET);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->tx_ctw->soft_weset, WPASS_TX_CTW_CWEAW);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->hdmitx_wegacy_en, WPASS_HDMITX_WEGACY_DISABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->hdmitx_pawity_cawc_en, HDMITX_PAWITY_CAWC_EN);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->vbit_ctw->wepwace_vbit, WEPWACE_VBIT);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->vbit_ctw->vbit_stweam, WINEAW_PCM_DATA);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->hdmitx_ch_msb[0], ch_sts_buf1);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->hdmitx_ch_wsb[0], ch_sts_buf0);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->hdmi_tx_dmactw[0]->use_hw_chs, HW_MODE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->hdmi_tx_dmactw[0]->hw_chs_sew, SW_MODE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->hdmi_tx_dmactw[0]->use_hw_usw, HW_MODE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->hdmi_tx_dmactw[0]->hw_usw_sew, SW_MODE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(meta_ctw->mute, WPASS_MUTE_ENABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(meta_ctw->as_sdp_cc, channews - 1);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(meta_ctw->as_sdp_ct, WPASS_META_DEFAUWT_VAW);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(meta_ctw->aif_db4, WPASS_META_DEFAUWT_VAW);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(meta_ctw->fwequency, sampwing_fweq);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(meta_ctw->mst_index, WPASS_META_DEFAUWT_VAW);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(meta_ctw->dptx_index, WPASS_META_DEFAUWT_VAW);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(sstweam_ctw->sstweam_en, WPASS_SSTWEAM_DISABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(sstweam_ctw->dma_sew, ch);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(sstweam_ctw->auto_bbit_en, WPASS_SSTWEAM_DEFAUWT_ENABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(sstweam_ctw->wayout, WPASS_SSTWEAM_DEFAUWT_DISABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(sstweam_ctw->wayout_sp, WPASS_WAYOUT_SP_DEFAUWT);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(sstweam_ctw->dp_audio, WPASS_SSTWEAM_DEFAUWT_ENABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(sstweam_ctw->set_sp_on_en, WPASS_SSTWEAM_DEFAUWT_ENABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(sstweam_ctw->dp_sp_b_hw_en, WPASS_SSTWEAM_DEFAUWT_ENABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(sstweam_ctw->dp_staffing_en, WPASS_SSTWEAM_DEFAUWT_ENABWE);

	wetuwn wet;
}

static int wpass_hdmi_daiops_pwepawe(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	int wet;
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);

	wet = wegmap_fiewd_wwite(dwvdata->sstweam_ctw->sstweam_en, WPASS_SSTWEAM_ENABWE);
	if (wet)
		wetuwn wet;

	wet = wegmap_fiewd_wwite(dwvdata->meta_ctw->mute, WPASS_MUTE_DISABWE);

	wetuwn wet;
}

static int wpass_hdmi_daiops_twiggew(stwuct snd_pcm_substweam *substweam,
		int cmd, stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	stwuct wpass_dp_metadata_ctw *meta_ctw = dwvdata->meta_ctw;
	stwuct wpass_sstweam_ctw *sstweam_ctw = dwvdata->sstweam_ctw;
	int wet = -EINVAW;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = wegmap_fiewd_wwite(sstweam_ctw->sstweam_en, WPASS_SSTWEAM_ENABWE);
		if (wet)
			wetuwn wet;

		wet = wegmap_fiewd_wwite(meta_ctw->mute, WPASS_MUTE_DISABWE);
		if (wet)
			wetuwn wet;

		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wet = wegmap_fiewd_wwite(sstweam_ctw->sstweam_en, WPASS_SSTWEAM_DISABWE);
		if (wet)
			wetuwn wet;

		wet = wegmap_fiewd_wwite(meta_ctw->mute, WPASS_MUTE_ENABWE);
		if (wet)
			wetuwn wet;

		wet = wegmap_fiewd_wwite(sstweam_ctw->dp_audio, 0);
		if (wet)
			wetuwn wet;

		bweak;
	}
	wetuwn wet;
}

const stwuct snd_soc_dai_ops asoc_qcom_wpass_hdmi_dai_ops = {
	.hw_pawams	= wpass_hdmi_daiops_hw_pawams,
	.pwepawe	= wpass_hdmi_daiops_pwepawe,
	.twiggew	= wpass_hdmi_daiops_twiggew,
};
EXPOWT_SYMBOW_GPW(asoc_qcom_wpass_hdmi_dai_ops);

MODUWE_DESCWIPTION("QTi WPASS HDMI Dwivew");
MODUWE_WICENSE("GPW");
