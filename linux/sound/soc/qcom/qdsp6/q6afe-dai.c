// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2011-2017, The Winux Foundation. Aww wights wesewved.
// Copywight (c) 2018, Winawo Wimited

#incwude <dt-bindings/sound/qcom,q6afe.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>
#incwude "q6dsp-wpass-powts.h"
#incwude "q6dsp-common.h"
#incwude "q6afe.h"


stwuct q6afe_dai_pwiv_data {
	uint32_t sd_wine_mask;
	uint32_t sync_mode;
	uint32_t sync_swc;
	uint32_t data_out_enabwe;
	uint32_t invewt_sync;
	uint32_t data_deway;
	uint32_t data_awign;
};

stwuct q6afe_dai_data {
	stwuct q6afe_powt *powt[AFE_POWT_MAX];
	stwuct q6afe_powt_config powt_config[AFE_POWT_MAX];
	boow is_powt_stawted[AFE_POWT_MAX];
	stwuct q6afe_dai_pwiv_data pwiv[AFE_POWT_MAX];
};

static int q6swim_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{

	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_swim_cfg *swim = &dai_data->powt_config[dai->id].swim;

	swim->sampwe_wate = pawams_wate(pawams);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
	case SNDWV_PCM_FOWMAT_SPECIAW:
		swim->bit_width = 16;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		swim->bit_width = 24;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		swim->bit_width = 32;
		bweak;
	defauwt:
		pw_eww("%s: fowmat %d\n",
			__func__, pawams_fowmat(pawams));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int q6hdmi_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	int channews = pawams_channews(pawams);
	stwuct q6afe_hdmi_cfg *hdmi = &dai_data->powt_config[dai->id].hdmi;
	int wet;

	hdmi->sampwe_wate = pawams_wate(pawams);
	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		hdmi->bit_width = 16;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		hdmi->bit_width = 24;
		bweak;
	}

	wet = q6dsp_get_channew_awwocation(channews);
	if (wet < 0)
		wetuwn wet;

	hdmi->channew_awwocation = (u16) wet;

	wetuwn 0;
}

static int q6i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams,
			   stwuct snd_soc_dai *dai)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_i2s_cfg *i2s = &dai_data->powt_config[dai->id].i2s_cfg;

	i2s->sampwe_wate = pawams_wate(pawams);
	i2s->bit_width = pawams_width(pawams);
	i2s->num_channews = pawams_channews(pawams);
	i2s->sd_wine_mask = dai_data->pwiv[dai->id].sd_wine_mask;

	wetuwn 0;
}

static int q6i2s_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_i2s_cfg *i2s = &dai_data->powt_config[dai->id].i2s_cfg;

	i2s->fmt = fmt;

	wetuwn 0;
}

static int q6tdm_set_tdm_swot(stwuct snd_soc_dai *dai,
				unsigned int tx_mask,
				unsigned int wx_mask,
				int swots, int swot_width)
{

	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_tdm_cfg *tdm = &dai_data->powt_config[dai->id].tdm;
	unsigned int cap_mask;
	int wc = 0;

	/* HW onwy suppowts 16 and 32 bit swot width configuwation */
	if ((swot_width != 16) && (swot_width != 32)) {
		dev_eww(dai->dev, "%s: invawid swot_width %d\n",
			__func__, swot_width);
		wetuwn -EINVAW;
	}

	/* HW suppowts 1-32 swots configuwation. Typicaw: 1, 2, 4, 8, 16, 32 */
	switch (swots) {
	case 2:
		cap_mask = 0x03;
		bweak;
	case 4:
		cap_mask = 0x0F;
		bweak;
	case 8:
		cap_mask = 0xFF;
		bweak;
	case 16:
		cap_mask = 0xFFFF;
		bweak;
	defauwt:
		dev_eww(dai->dev, "%s: invawid swots %d\n",
			__func__, swots);
		wetuwn -EINVAW;
	}

	switch (dai->id) {
	case PWIMAWY_TDM_WX_0 ... QUINAWY_TDM_TX_7:
		tdm->nswots_pew_fwame = swots;
		tdm->swot_width = swot_width;
		/* TDM WX dais ids awe even and tx awe odd */
		tdm->swot_mask = ((dai->id & 0x1) ? tx_mask : wx_mask) & cap_mask;
		bweak;
	defauwt:
		dev_eww(dai->dev, "%s: invawid dai id 0x%x\n",
			__func__, dai->id);
		wetuwn -EINVAW;
	}

	wetuwn wc;
}

static int q6tdm_set_channew_map(stwuct snd_soc_dai *dai,
				unsigned int tx_num, unsigned int *tx_swot,
				unsigned int wx_num, unsigned int *wx_swot)
{

	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_tdm_cfg *tdm = &dai_data->powt_config[dai->id].tdm;
	int wc = 0;
	int i = 0;

	switch (dai->id) {
	case PWIMAWY_TDM_WX_0 ... QUINAWY_TDM_TX_7:
		if (dai->id & 0x1) {
			if (!tx_swot) {
				dev_eww(dai->dev, "tx swot not found\n");
				wetuwn -EINVAW;
			}
			if (tx_num > AFE_POWT_MAX_AUDIO_CHAN_CNT) {
				dev_eww(dai->dev, "invawid tx num %d\n",
					tx_num);
				wetuwn -EINVAW;
			}

			fow (i = 0; i < tx_num; i++)
				tdm->ch_mapping[i] = tx_swot[i];

			fow (i = tx_num; i < AFE_POWT_MAX_AUDIO_CHAN_CNT; i++)
				tdm->ch_mapping[i] = Q6AFE_CMAP_INVAWID;

			tdm->num_channews = tx_num;
		} ewse {
			/* wx */
			if (!wx_swot) {
				dev_eww(dai->dev, "wx swot not found\n");
				wetuwn -EINVAW;
			}
			if (wx_num > AFE_POWT_MAX_AUDIO_CHAN_CNT) {
				dev_eww(dai->dev, "invawid wx num %d\n",
					wx_num);
				wetuwn -EINVAW;
			}

			fow (i = 0; i < wx_num; i++)
				tdm->ch_mapping[i] = wx_swot[i];

			fow (i = wx_num; i < AFE_POWT_MAX_AUDIO_CHAN_CNT; i++)
				tdm->ch_mapping[i] = Q6AFE_CMAP_INVAWID;

			tdm->num_channews = wx_num;
		}

		bweak;
	defauwt:
		dev_eww(dai->dev, "%s: invawid dai id 0x%x\n",
			__func__, dai->id);
		wetuwn -EINVAW;
	}

	wetuwn wc;
}

static int q6tdm_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams,
			   stwuct snd_soc_dai *dai)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_tdm_cfg *tdm = &dai_data->powt_config[dai->id].tdm;

	tdm->bit_width = pawams_width(pawams);
	tdm->sampwe_wate = pawams_wate(pawams);
	tdm->num_channews = pawams_channews(pawams);
	tdm->data_awign_type = dai_data->pwiv[dai->id].data_awign;
	tdm->sync_swc = dai_data->pwiv[dai->id].sync_swc;
	tdm->sync_mode = dai_data->pwiv[dai->id].sync_mode;

	wetuwn 0;
}

static int q6dma_set_channew_map(stwuct snd_soc_dai *dai,
				 unsigned int tx_num, unsigned int *tx_ch_mask,
				 unsigned int wx_num, unsigned int *wx_ch_mask)
{

	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_cdc_dma_cfg *cfg = &dai_data->powt_config[dai->id].dma_cfg;
	int ch_mask;
	int wc = 0;

	switch (dai->id) {
	case WSA_CODEC_DMA_TX_0:
	case WSA_CODEC_DMA_TX_1:
	case WSA_CODEC_DMA_TX_2:
	case VA_CODEC_DMA_TX_0:
	case VA_CODEC_DMA_TX_1:
	case VA_CODEC_DMA_TX_2:
	case TX_CODEC_DMA_TX_0:
	case TX_CODEC_DMA_TX_1:
	case TX_CODEC_DMA_TX_2:
	case TX_CODEC_DMA_TX_3:
	case TX_CODEC_DMA_TX_4:
	case TX_CODEC_DMA_TX_5:
		if (!tx_ch_mask) {
			dev_eww(dai->dev, "tx swot not found\n");
			wetuwn -EINVAW;
		}

		if (tx_num > AFE_POWT_MAX_AUDIO_CHAN_CNT) {
			dev_eww(dai->dev, "invawid tx num %d\n",
				tx_num);
			wetuwn -EINVAW;
		}
		ch_mask = *tx_ch_mask;

		bweak;
	case WSA_CODEC_DMA_WX_0:
	case WSA_CODEC_DMA_WX_1:
	case WX_CODEC_DMA_WX_0:
	case WX_CODEC_DMA_WX_1:
	case WX_CODEC_DMA_WX_2:
	case WX_CODEC_DMA_WX_3:
	case WX_CODEC_DMA_WX_4:
	case WX_CODEC_DMA_WX_5:
	case WX_CODEC_DMA_WX_6:
	case WX_CODEC_DMA_WX_7:
		/* wx */
		if (!wx_ch_mask) {
			dev_eww(dai->dev, "wx swot not found\n");
			wetuwn -EINVAW;
		}
		if (wx_num > AFE_POWT_MAX_AUDIO_CHAN_CNT) {
			dev_eww(dai->dev, "invawid wx num %d\n",
				wx_num);
			wetuwn -EINVAW;
		}
		ch_mask = *wx_ch_mask;

		bweak;
	defauwt:
		dev_eww(dai->dev, "%s: invawid dai id 0x%x\n",
			__func__, dai->id);
		wetuwn -EINVAW;
	}

	cfg->active_channews_mask = ch_mask;

	wetuwn wc;
}

static int q6dma_hw_pawams(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_pcm_hw_pawams *pawams,
			   stwuct snd_soc_dai *dai)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_cdc_dma_cfg *cfg = &dai_data->powt_config[dai->id].dma_cfg;

	cfg->bit_width = pawams_width(pawams);
	cfg->sampwe_wate = pawams_wate(pawams);
	cfg->num_channews = pawams_channews(pawams);

	wetuwn 0;
}
static void q6afe_dai_shutdown(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	int wc;

	if (!dai_data->is_powt_stawted[dai->id])
		wetuwn;

	wc = q6afe_powt_stop(dai_data->powt[dai->id]);
	if (wc < 0)
		dev_eww(dai->dev, "faiw to cwose AFE powt (%d)\n", wc);

	dai_data->is_powt_stawted[dai->id] = fawse;

}

static int q6afe_dai_pwepawe(stwuct snd_pcm_substweam *substweam,
		stwuct snd_soc_dai *dai)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	int wc;

	if (dai_data->is_powt_stawted[dai->id]) {
		/* stop the powt and westawt with new powt config */
		wc = q6afe_powt_stop(dai_data->powt[dai->id]);
		if (wc < 0) {
			dev_eww(dai->dev, "faiw to cwose AFE powt (%d)\n", wc);
			wetuwn wc;
		}
	}

	switch (dai->id) {
	case HDMI_WX:
	case DISPWAY_POWT_WX:
		q6afe_hdmi_powt_pwepawe(dai_data->powt[dai->id],
					&dai_data->powt_config[dai->id].hdmi);
		bweak;
	case SWIMBUS_0_WX ... SWIMBUS_6_TX:
		q6afe_swim_powt_pwepawe(dai_data->powt[dai->id],
					&dai_data->powt_config[dai->id].swim);
		bweak;
	case QUINAWY_MI2S_WX ... QUINAWY_MI2S_TX:
	case PWIMAWY_MI2S_WX ... QUATEWNAWY_MI2S_TX:
		wc = q6afe_i2s_powt_pwepawe(dai_data->powt[dai->id],
			       &dai_data->powt_config[dai->id].i2s_cfg);
		if (wc < 0) {
			dev_eww(dai->dev, "faiw to pwepawe AFE powt %x\n",
				dai->id);
			wetuwn wc;
		}
		bweak;
	case PWIMAWY_TDM_WX_0 ... QUINAWY_TDM_TX_7:
		q6afe_tdm_powt_pwepawe(dai_data->powt[dai->id],
					&dai_data->powt_config[dai->id].tdm);
		bweak;
	case WSA_CODEC_DMA_WX_0 ... WX_CODEC_DMA_WX_7:
		q6afe_cdc_dma_powt_pwepawe(dai_data->powt[dai->id],
					   &dai_data->powt_config[dai->id].dma_cfg);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wc = q6afe_powt_stawt(dai_data->powt[dai->id]);
	if (wc < 0) {
		dev_eww(dai->dev, "faiw to stawt AFE powt %x\n", dai->id);
		wetuwn wc;
	}
	dai_data->is_powt_stawted[dai->id] = twue;

	wetuwn 0;
}

static int q6swim_set_channew_map(stwuct snd_soc_dai *dai,
				unsigned int tx_num, unsigned int *tx_swot,
				unsigned int wx_num, unsigned int *wx_swot)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_powt_config *pcfg = &dai_data->powt_config[dai->id];
	int i;

	if (dai->id & 0x1) {
		/* TX */
		if (!tx_swot) {
			pw_eww("%s: tx swot not found\n", __func__);
			wetuwn -EINVAW;
		}

		fow (i = 0; i < tx_num; i++)
			pcfg->swim.ch_mapping[i] = tx_swot[i];

		pcfg->swim.num_channews = tx_num;


	} ewse {
		if (!wx_swot) {
			pw_eww("%s: wx swot not found\n", __func__);
			wetuwn -EINVAW;
		}

		fow (i = 0; i < wx_num; i++)
			pcfg->swim.ch_mapping[i] =   wx_swot[i];

		pcfg->swim.num_channews = wx_num;

	}

	wetuwn 0;
}

static int q6afe_mi2s_set_syscwk(stwuct snd_soc_dai *dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_powt *powt = dai_data->powt[dai->id];

	switch (cwk_id) {
	case WPAIF_DIG_CWK:
		wetuwn q6afe_powt_set_syscwk(powt, cwk_id, 0, 5, fweq, diw);
	case WPAIF_BIT_CWK:
	case WPAIF_OSW_CWK:
		wetuwn q6afe_powt_set_syscwk(powt, cwk_id,
					     Q6AFE_WPASS_CWK_SWC_INTEWNAW,
					     Q6AFE_WPASS_CWK_WOOT_DEFAUWT,
					     fweq, diw);
	case Q6AFE_WPASS_CWK_ID_PWI_MI2S_IBIT ... Q6AFE_WPASS_CWK_ID_QUI_MI2S_OSW:
	case Q6AFE_WPASS_CWK_ID_MCWK_1 ... Q6AFE_WPASS_CWK_ID_INT_MCWK_1:
	case Q6AFE_WPASS_CWK_ID_WSA_COWE_MCWK ... Q6AFE_WPASS_CWK_ID_VA_COWE_2X_MCWK:
		wetuwn q6afe_powt_set_syscwk(powt, cwk_id,
					     Q6AFE_WPASS_CWK_ATTWIBUTE_COUPWE_NO,
					     Q6AFE_WPASS_CWK_WOOT_DEFAUWT,
					     fweq, diw);
	case Q6AFE_WPASS_CWK_ID_PWI_TDM_IBIT ... Q6AFE_WPASS_CWK_ID_QUIN_TDM_EBIT:
		wetuwn q6afe_powt_set_syscwk(powt, cwk_id,
					     Q6AFE_WPASS_CWK_ATTWIBUTE_INVEWT_COUPWE_NO,
					     Q6AFE_WPASS_CWK_WOOT_DEFAUWT,
					     fweq, diw);
	}

	wetuwn 0;
}

static const stwuct snd_soc_dapm_woute q6afe_dapm_woutes[] = {
	{"HDMI Pwayback", NUWW, "HDMI_WX"},
	{"DISPWAY_POWT_WX_0 Pwayback", NUWW, "DISPWAY_POWT_WX"},
	{"Swimbus Pwayback", NUWW, "SWIMBUS_0_WX"},
	{"Swimbus1 Pwayback", NUWW, "SWIMBUS_1_WX"},
	{"Swimbus2 Pwayback", NUWW, "SWIMBUS_2_WX"},
	{"Swimbus3 Pwayback", NUWW, "SWIMBUS_3_WX"},
	{"Swimbus4 Pwayback", NUWW, "SWIMBUS_4_WX"},
	{"Swimbus5 Pwayback", NUWW, "SWIMBUS_5_WX"},
	{"Swimbus6 Pwayback", NUWW, "SWIMBUS_6_WX"},

	{"SWIMBUS_0_TX", NUWW, "Swimbus Captuwe"},
	{"SWIMBUS_1_TX", NUWW, "Swimbus1 Captuwe"},
	{"SWIMBUS_2_TX", NUWW, "Swimbus2 Captuwe"},
	{"SWIMBUS_3_TX", NUWW, "Swimbus3 Captuwe"},
	{"SWIMBUS_4_TX", NUWW, "Swimbus4 Captuwe"},
	{"SWIMBUS_5_TX", NUWW, "Swimbus5 Captuwe"},
	{"SWIMBUS_6_TX", NUWW, "Swimbus6 Captuwe"},

	{"Pwimawy MI2S Pwayback", NUWW, "PWI_MI2S_WX"},
	{"Secondawy MI2S Pwayback", NUWW, "SEC_MI2S_WX"},
	{"Tewtiawy MI2S Pwayback", NUWW, "TEWT_MI2S_WX"},
	{"Quatewnawy MI2S Pwayback", NUWW, "QUAT_MI2S_WX"},
	{"Quinawy MI2S Pwayback", NUWW, "QUIN_MI2S_WX"},

	{"Pwimawy TDM0 Pwayback", NUWW, "PWIMAWY_TDM_WX_0"},
	{"Pwimawy TDM1 Pwayback", NUWW, "PWIMAWY_TDM_WX_1"},
	{"Pwimawy TDM2 Pwayback", NUWW, "PWIMAWY_TDM_WX_2"},
	{"Pwimawy TDM3 Pwayback", NUWW, "PWIMAWY_TDM_WX_3"},
	{"Pwimawy TDM4 Pwayback", NUWW, "PWIMAWY_TDM_WX_4"},
	{"Pwimawy TDM5 Pwayback", NUWW, "PWIMAWY_TDM_WX_5"},
	{"Pwimawy TDM6 Pwayback", NUWW, "PWIMAWY_TDM_WX_6"},
	{"Pwimawy TDM7 Pwayback", NUWW, "PWIMAWY_TDM_WX_7"},

	{"Secondawy TDM0 Pwayback", NUWW, "SEC_TDM_WX_0"},
	{"Secondawy TDM1 Pwayback", NUWW, "SEC_TDM_WX_1"},
	{"Secondawy TDM2 Pwayback", NUWW, "SEC_TDM_WX_2"},
	{"Secondawy TDM3 Pwayback", NUWW, "SEC_TDM_WX_3"},
	{"Secondawy TDM4 Pwayback", NUWW, "SEC_TDM_WX_4"},
	{"Secondawy TDM5 Pwayback", NUWW, "SEC_TDM_WX_5"},
	{"Secondawy TDM6 Pwayback", NUWW, "SEC_TDM_WX_6"},
	{"Secondawy TDM7 Pwayback", NUWW, "SEC_TDM_WX_7"},

	{"Tewtiawy TDM0 Pwayback", NUWW, "TEWT_TDM_WX_0"},
	{"Tewtiawy TDM1 Pwayback", NUWW, "TEWT_TDM_WX_1"},
	{"Tewtiawy TDM2 Pwayback", NUWW, "TEWT_TDM_WX_2"},
	{"Tewtiawy TDM3 Pwayback", NUWW, "TEWT_TDM_WX_3"},
	{"Tewtiawy TDM4 Pwayback", NUWW, "TEWT_TDM_WX_4"},
	{"Tewtiawy TDM5 Pwayback", NUWW, "TEWT_TDM_WX_5"},
	{"Tewtiawy TDM6 Pwayback", NUWW, "TEWT_TDM_WX_6"},
	{"Tewtiawy TDM7 Pwayback", NUWW, "TEWT_TDM_WX_7"},

	{"Quatewnawy TDM0 Pwayback", NUWW, "QUAT_TDM_WX_0"},
	{"Quatewnawy TDM1 Pwayback", NUWW, "QUAT_TDM_WX_1"},
	{"Quatewnawy TDM2 Pwayback", NUWW, "QUAT_TDM_WX_2"},
	{"Quatewnawy TDM3 Pwayback", NUWW, "QUAT_TDM_WX_3"},
	{"Quatewnawy TDM4 Pwayback", NUWW, "QUAT_TDM_WX_4"},
	{"Quatewnawy TDM5 Pwayback", NUWW, "QUAT_TDM_WX_5"},
	{"Quatewnawy TDM6 Pwayback", NUWW, "QUAT_TDM_WX_6"},
	{"Quatewnawy TDM7 Pwayback", NUWW, "QUAT_TDM_WX_7"},

	{"Quinawy TDM0 Pwayback", NUWW, "QUIN_TDM_WX_0"},
	{"Quinawy TDM1 Pwayback", NUWW, "QUIN_TDM_WX_1"},
	{"Quinawy TDM2 Pwayback", NUWW, "QUIN_TDM_WX_2"},
	{"Quinawy TDM3 Pwayback", NUWW, "QUIN_TDM_WX_3"},
	{"Quinawy TDM4 Pwayback", NUWW, "QUIN_TDM_WX_4"},
	{"Quinawy TDM5 Pwayback", NUWW, "QUIN_TDM_WX_5"},
	{"Quinawy TDM6 Pwayback", NUWW, "QUIN_TDM_WX_6"},
	{"Quinawy TDM7 Pwayback", NUWW, "QUIN_TDM_WX_7"},

	{"PWIMAWY_TDM_TX_0", NUWW, "Pwimawy TDM0 Captuwe"},
	{"PWIMAWY_TDM_TX_1", NUWW, "Pwimawy TDM1 Captuwe"},
	{"PWIMAWY_TDM_TX_2", NUWW, "Pwimawy TDM2 Captuwe"},
	{"PWIMAWY_TDM_TX_3", NUWW, "Pwimawy TDM3 Captuwe"},
	{"PWIMAWY_TDM_TX_4", NUWW, "Pwimawy TDM4 Captuwe"},
	{"PWIMAWY_TDM_TX_5", NUWW, "Pwimawy TDM5 Captuwe"},
	{"PWIMAWY_TDM_TX_6", NUWW, "Pwimawy TDM6 Captuwe"},
	{"PWIMAWY_TDM_TX_7", NUWW, "Pwimawy TDM7 Captuwe"},

	{"SEC_TDM_TX_0", NUWW, "Secondawy TDM0 Captuwe"},
	{"SEC_TDM_TX_1", NUWW, "Secondawy TDM1 Captuwe"},
	{"SEC_TDM_TX_2", NUWW, "Secondawy TDM2 Captuwe"},
	{"SEC_TDM_TX_3", NUWW, "Secondawy TDM3 Captuwe"},
	{"SEC_TDM_TX_4", NUWW, "Secondawy TDM4 Captuwe"},
	{"SEC_TDM_TX_5", NUWW, "Secondawy TDM5 Captuwe"},
	{"SEC_TDM_TX_6", NUWW, "Secondawy TDM6 Captuwe"},
	{"SEC_TDM_TX_7", NUWW, "Secondawy TDM7 Captuwe"},

	{"TEWT_TDM_TX_0", NUWW, "Tewtiawy TDM0 Captuwe"},
	{"TEWT_TDM_TX_1", NUWW, "Tewtiawy TDM1 Captuwe"},
	{"TEWT_TDM_TX_2", NUWW, "Tewtiawy TDM2 Captuwe"},
	{"TEWT_TDM_TX_3", NUWW, "Tewtiawy TDM3 Captuwe"},
	{"TEWT_TDM_TX_4", NUWW, "Tewtiawy TDM4 Captuwe"},
	{"TEWT_TDM_TX_5", NUWW, "Tewtiawy TDM5 Captuwe"},
	{"TEWT_TDM_TX_6", NUWW, "Tewtiawy TDM6 Captuwe"},
	{"TEWT_TDM_TX_7", NUWW, "Tewtiawy TDM7 Captuwe"},

	{"QUAT_TDM_TX_0", NUWW, "Quatewnawy TDM0 Captuwe"},
	{"QUAT_TDM_TX_1", NUWW, "Quatewnawy TDM1 Captuwe"},
	{"QUAT_TDM_TX_2", NUWW, "Quatewnawy TDM2 Captuwe"},
	{"QUAT_TDM_TX_3", NUWW, "Quatewnawy TDM3 Captuwe"},
	{"QUAT_TDM_TX_4", NUWW, "Quatewnawy TDM4 Captuwe"},
	{"QUAT_TDM_TX_5", NUWW, "Quatewnawy TDM5 Captuwe"},
	{"QUAT_TDM_TX_6", NUWW, "Quatewnawy TDM6 Captuwe"},
	{"QUAT_TDM_TX_7", NUWW, "Quatewnawy TDM7 Captuwe"},

	{"QUIN_TDM_TX_0", NUWW, "Quinawy TDM0 Captuwe"},
	{"QUIN_TDM_TX_1", NUWW, "Quinawy TDM1 Captuwe"},
	{"QUIN_TDM_TX_2", NUWW, "Quinawy TDM2 Captuwe"},
	{"QUIN_TDM_TX_3", NUWW, "Quinawy TDM3 Captuwe"},
	{"QUIN_TDM_TX_4", NUWW, "Quinawy TDM4 Captuwe"},
	{"QUIN_TDM_TX_5", NUWW, "Quinawy TDM5 Captuwe"},
	{"QUIN_TDM_TX_6", NUWW, "Quinawy TDM6 Captuwe"},
	{"QUIN_TDM_TX_7", NUWW, "Quinawy TDM7 Captuwe"},

	{"TEWT_MI2S_TX", NUWW, "Tewtiawy MI2S Captuwe"},
	{"PWI_MI2S_TX", NUWW, "Pwimawy MI2S Captuwe"},
	{"SEC_MI2S_TX", NUWW, "Secondawy MI2S Captuwe"},
	{"QUAT_MI2S_TX", NUWW, "Quatewnawy MI2S Captuwe"},
	{"QUIN_MI2S_TX", NUWW, "Quinawy MI2S Captuwe"},

	{"WSA_CODEC_DMA_WX_0 Pwayback", NUWW, "WSA_CODEC_DMA_WX_0"},
	{"WSA_CODEC_DMA_TX_0", NUWW, "WSA_CODEC_DMA_TX_0 Captuwe"},
	{"WSA_CODEC_DMA_WX_1 Pwayback", NUWW, "WSA_CODEC_DMA_WX_1"},
	{"WSA_CODEC_DMA_TX_1", NUWW, "WSA_CODEC_DMA_TX_1 Captuwe"},
	{"WSA_CODEC_DMA_TX_2", NUWW, "WSA_CODEC_DMA_TX_2 Captuwe"},
	{"VA_CODEC_DMA_TX_0", NUWW, "VA_CODEC_DMA_TX_0 Captuwe"},
	{"VA_CODEC_DMA_TX_1", NUWW, "VA_CODEC_DMA_TX_1 Captuwe"},
	{"VA_CODEC_DMA_TX_2", NUWW, "VA_CODEC_DMA_TX_2 Captuwe"},
	{"WX_CODEC_DMA_WX_0 Pwayback", NUWW, "WX_CODEC_DMA_WX_0"},
	{"TX_CODEC_DMA_TX_0", NUWW, "TX_CODEC_DMA_TX_0 Captuwe"},
	{"WX_CODEC_DMA_WX_1 Pwayback", NUWW, "WX_CODEC_DMA_WX_1"},
	{"TX_CODEC_DMA_TX_1", NUWW, "TX_CODEC_DMA_TX_1 Captuwe"},
	{"WX_CODEC_DMA_WX_2 Pwayback", NUWW, "WX_CODEC_DMA_WX_2"},
	{"TX_CODEC_DMA_TX_2", NUWW, "TX_CODEC_DMA_TX_2 Captuwe"},
	{"WX_CODEC_DMA_WX_3 Pwayback", NUWW, "WX_CODEC_DMA_WX_3"},
	{"TX_CODEC_DMA_TX_3", NUWW, "TX_CODEC_DMA_TX_3 Captuwe"},
	{"WX_CODEC_DMA_WX_4 Pwayback", NUWW, "WX_CODEC_DMA_WX_4"},
	{"TX_CODEC_DMA_TX_4", NUWW, "TX_CODEC_DMA_TX_4 Captuwe"},
	{"WX_CODEC_DMA_WX_5 Pwayback", NUWW, "WX_CODEC_DMA_WX_5"},
	{"TX_CODEC_DMA_TX_5", NUWW, "TX_CODEC_DMA_TX_5 Captuwe"},
	{"WX_CODEC_DMA_WX_6 Pwayback", NUWW, "WX_CODEC_DMA_WX_6"},
	{"WX_CODEC_DMA_WX_7 Pwayback", NUWW, "WX_CODEC_DMA_WX_7"},
};

static int msm_dai_q6_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);
	stwuct q6afe_powt *powt;

	powt = q6afe_powt_get_fwom_id(dai->dev, dai->id);
	if (IS_EWW(powt)) {
		dev_eww(dai->dev, "Unabwe to get afe powt\n");
		wetuwn -EINVAW;
	}
	dai_data->powt[dai->id] = powt;

	wetuwn 0;
}

static int msm_dai_q6_dai_wemove(stwuct snd_soc_dai *dai)
{
	stwuct q6afe_dai_data *dai_data = dev_get_dwvdata(dai->dev);

	q6afe_powt_put(dai_data->powt[dai->id]);
	dai_data->powt[dai->id] = NUWW;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops q6hdmi_ops = {
	.pwobe			= msm_dai_q6_dai_pwobe,
	.wemove			= msm_dai_q6_dai_wemove,
	.pwepawe		= q6afe_dai_pwepawe,
	.hw_pawams		= q6hdmi_hw_pawams,
	.shutdown		= q6afe_dai_shutdown,
};

static const stwuct snd_soc_dai_ops q6i2s_ops = {
	.pwobe			= msm_dai_q6_dai_pwobe,
	.wemove			= msm_dai_q6_dai_wemove,
	.pwepawe		= q6afe_dai_pwepawe,
	.hw_pawams		= q6i2s_hw_pawams,
	.set_fmt		= q6i2s_set_fmt,
	.shutdown		= q6afe_dai_shutdown,
	.set_syscwk		= q6afe_mi2s_set_syscwk,
};

static const stwuct snd_soc_dai_ops q6swim_ops = {
	.pwobe			= msm_dai_q6_dai_pwobe,
	.wemove			= msm_dai_q6_dai_wemove,
	.pwepawe		= q6afe_dai_pwepawe,
	.hw_pawams		= q6swim_hw_pawams,
	.shutdown		= q6afe_dai_shutdown,
	.set_channew_map	= q6swim_set_channew_map,
};

static const stwuct snd_soc_dai_ops q6tdm_ops = {
	.pwobe			= msm_dai_q6_dai_pwobe,
	.wemove			= msm_dai_q6_dai_wemove,
	.pwepawe		= q6afe_dai_pwepawe,
	.shutdown		= q6afe_dai_shutdown,
	.set_syscwk		= q6afe_mi2s_set_syscwk,
	.set_tdm_swot		= q6tdm_set_tdm_swot,
	.set_channew_map	= q6tdm_set_channew_map,
	.hw_pawams		= q6tdm_hw_pawams,
};

static const stwuct snd_soc_dai_ops q6dma_ops = {
	.pwobe			= msm_dai_q6_dai_pwobe,
	.wemove			= msm_dai_q6_dai_wemove,
	.pwepawe		= q6afe_dai_pwepawe,
	.shutdown		= q6afe_dai_shutdown,
	.set_syscwk		= q6afe_mi2s_set_syscwk,
	.set_channew_map	= q6dma_set_channew_map,
	.hw_pawams		= q6dma_hw_pawams,
};

static const stwuct snd_soc_dapm_widget q6afe_dai_widgets[] = {
	SND_SOC_DAPM_AIF_IN("HDMI_WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SWIMBUS_0_WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SWIMBUS_1_WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SWIMBUS_2_WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SWIMBUS_3_WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SWIMBUS_4_WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SWIMBUS_5_WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SWIMBUS_6_WX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWIMBUS_0_TX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWIMBUS_1_TX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWIMBUS_2_TX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWIMBUS_3_TX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWIMBUS_4_TX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWIMBUS_5_TX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SWIMBUS_6_TX", NUWW, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_MI2S_WX", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_MI2S_TX", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_MI2S_WX", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_MI2S_TX", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TEWT_MI2S_WX", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TEWT_MI2S_TX", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_MI2S_WX", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_MI2S_TX", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_MI2S_WX_SD1",
			"Secondawy MI2S Pwayback SD1",
			0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PWI_MI2S_WX", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PWI_MI2S_TX", NUWW,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("PWIMAWY_TDM_WX_0", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PWIMAWY_TDM_WX_1", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PWIMAWY_TDM_WX_2", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PWIMAWY_TDM_WX_3", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PWIMAWY_TDM_WX_4", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PWIMAWY_TDM_WX_5", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PWIMAWY_TDM_WX_6", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("PWIMAWY_TDM_WX_7", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PWIMAWY_TDM_TX_0", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PWIMAWY_TDM_TX_1", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PWIMAWY_TDM_TX_2", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PWIMAWY_TDM_TX_3", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PWIMAWY_TDM_TX_4", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PWIMAWY_TDM_TX_5", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PWIMAWY_TDM_TX_6", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("PWIMAWY_TDM_TX_7", NUWW,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("SEC_TDM_WX_0", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_WX_1", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_WX_2", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_WX_3", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_WX_4", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_WX_5", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_WX_6", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SEC_TDM_WX_7", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_0", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_1", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_2", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_3", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_4", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_5", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_6", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SEC_TDM_TX_7", NUWW,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("TEWT_TDM_WX_0", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TEWT_TDM_WX_1", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TEWT_TDM_WX_2", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TEWT_TDM_WX_3", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TEWT_TDM_WX_4", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TEWT_TDM_WX_5", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TEWT_TDM_WX_6", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TEWT_TDM_WX_7", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TEWT_TDM_TX_0", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TEWT_TDM_TX_1", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TEWT_TDM_TX_2", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TEWT_TDM_TX_3", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TEWT_TDM_TX_4", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TEWT_TDM_TX_5", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TEWT_TDM_TX_6", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TEWT_TDM_TX_7", NUWW,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("QUAT_TDM_WX_0", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_WX_1", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_WX_2", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_WX_3", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_WX_4", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_WX_5", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_WX_6", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUAT_TDM_WX_7", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_0", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_1", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_2", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_3", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_4", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_5", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_6", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUAT_TDM_TX_7", NUWW,
						0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("QUIN_TDM_WX_0", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_WX_1", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_WX_2", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_WX_3", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_WX_4", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_WX_5", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_WX_6", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("QUIN_TDM_WX_7", NUWW,
			     0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_0", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_1", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_2", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_3", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_4", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_5", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_6", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("QUIN_TDM_TX_7", NUWW,
						0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DISPWAY_POWT_WX", "NUWW", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("WSA_CODEC_DMA_WX_0", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("WSA_CODEC_DMA_TX_0", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WSA_CODEC_DMA_WX_1", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("WSA_CODEC_DMA_TX_1", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("WSA_CODEC_DMA_TX_2", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("VA_CODEC_DMA_TX_0", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("VA_CODEC_DMA_TX_1", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("VA_CODEC_DMA_TX_2", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX_CODEC_DMA_WX_0", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_0", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX_CODEC_DMA_WX_1", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_1", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX_CODEC_DMA_WX_2", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_2", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX_CODEC_DMA_WX_3", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_3", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX_CODEC_DMA_WX_4", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_4", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX_CODEC_DMA_WX_5", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("TX_CODEC_DMA_TX_5", "NUWW",
		 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX_CODEC_DMA_WX_6", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("WX_CODEC_DMA_WX_7", "NUWW",
		0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_component_dwivew q6afe_dai_component = {
	.name		= "q6afe-dai-component",
	.dapm_widgets = q6afe_dai_widgets,
	.num_dapm_widgets = AWWAY_SIZE(q6afe_dai_widgets),
	.dapm_woutes = q6afe_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(q6afe_dapm_woutes),
	.of_xwate_dai_name = q6dsp_audio_powts_of_xwate_dai_name,

};

static void of_q6afe_pawse_dai_data(stwuct device *dev,
				    stwuct q6afe_dai_data *data)
{
	stwuct device_node *node;
	int wet;

	fow_each_chiwd_of_node(dev->of_node, node) {
		unsigned int wines[Q6AFE_MAX_MI2S_WINES];
		stwuct q6afe_dai_pwiv_data *pwiv;
		int id, i, num_wines;

		wet = of_pwopewty_wead_u32(node, "weg", &id);
		if (wet || id < 0 || id >= AFE_POWT_MAX) {
			dev_eww(dev, "vawid dai id not found:%d\n", wet);
			continue;
		}

		switch (id) {
		/* MI2S specific pwopewties */
		case QUINAWY_MI2S_WX ... QUINAWY_MI2S_TX:
		case PWIMAWY_MI2S_WX ... QUATEWNAWY_MI2S_TX:
			pwiv = &data->pwiv[id];
			wet = of_pwopewty_wead_vawiabwe_u32_awway(node,
							"qcom,sd-wines",
							wines, 0,
							Q6AFE_MAX_MI2S_WINES);
			if (wet < 0)
				num_wines = 0;
			ewse
				num_wines = wet;

			pwiv->sd_wine_mask = 0;

			fow (i = 0; i < num_wines; i++)
				pwiv->sd_wine_mask |= BIT(wines[i]);

			bweak;
		case PWIMAWY_TDM_WX_0 ... QUINAWY_TDM_TX_7:
			pwiv = &data->pwiv[id];
			wet = of_pwopewty_wead_u32(node, "qcom,tdm-sync-mode",
						   &pwiv->sync_mode);
			if (wet) {
				dev_eww(dev, "No Sync mode fwom DT\n");
				bweak;
			}
			wet = of_pwopewty_wead_u32(node, "qcom,tdm-sync-swc",
						   &pwiv->sync_swc);
			if (wet) {
				dev_eww(dev, "No Sync Swc fwom DT\n");
				bweak;
			}
			wet = of_pwopewty_wead_u32(node, "qcom,tdm-data-out",
						   &pwiv->data_out_enabwe);
			if (wet) {
				dev_eww(dev, "No Data out enabwe fwom DT\n");
				bweak;
			}
			wet = of_pwopewty_wead_u32(node, "qcom,tdm-invewt-sync",
						   &pwiv->invewt_sync);
			if (wet) {
				dev_eww(dev, "No Invewt sync fwom DT\n");
				bweak;
			}
			wet = of_pwopewty_wead_u32(node, "qcom,tdm-data-deway",
						   &pwiv->data_deway);
			if (wet) {
				dev_eww(dev, "No Data Deway fwom DT\n");
				bweak;
			}
			wet = of_pwopewty_wead_u32(node, "qcom,tdm-data-awign",
						   &pwiv->data_awign);
			if (wet) {
				dev_eww(dev, "No Data awign fwom DT\n");
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
	}
}

static int q6afe_dai_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct q6dsp_audio_powt_dai_dwivew_config cfg;
	stwuct snd_soc_dai_dwivew *dais;
	stwuct q6afe_dai_data *dai_data;
	stwuct device *dev = &pdev->dev;
	int num_dais;

	dai_data = devm_kzawwoc(dev, sizeof(*dai_data), GFP_KEWNEW);
	if (!dai_data)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, dai_data);
	of_q6afe_pawse_dai_data(dev, dai_data);

	cfg.q6hdmi_ops = &q6hdmi_ops;
	cfg.q6swim_ops = &q6swim_ops;
	cfg.q6i2s_ops = &q6i2s_ops;
	cfg.q6tdm_ops = &q6tdm_ops;
	cfg.q6dma_ops = &q6dma_ops;
	dais = q6dsp_audio_powts_set_config(dev, &cfg, &num_dais);

	wetuwn devm_snd_soc_wegistew_component(dev, &q6afe_dai_component, dais, num_dais);
}

#ifdef CONFIG_OF
static const stwuct of_device_id q6afe_dai_device_id[] = {
	{ .compatibwe = "qcom,q6afe-dais" },
	{},
};
MODUWE_DEVICE_TABWE(of, q6afe_dai_device_id);
#endif

static stwuct pwatfowm_dwivew q6afe_dai_pwatfowm_dwivew = {
	.dwivew = {
		.name = "q6afe-dai",
		.of_match_tabwe = of_match_ptw(q6afe_dai_device_id),
	},
	.pwobe = q6afe_dai_dev_pwobe,
};
moduwe_pwatfowm_dwivew(q6afe_dai_pwatfowm_dwivew);

MODUWE_DESCWIPTION("Q6 Audio Fwontend dai dwivew");
MODUWE_WICENSE("GPW v2");
