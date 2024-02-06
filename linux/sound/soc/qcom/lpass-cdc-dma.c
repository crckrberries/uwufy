// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 The Winux Foundation. Aww wights wesewved.
 *
 * wpass-cdc-dma.c -- AWSA SoC CDC DMA CPU DAI dwivew fow QTi WPASS
 */

#incwude <dt-bindings/sound/qcom,wpass.h>
#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/expowt.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "wpass-wpaif-weg.h"
#incwude "wpass.h"

#define CODEC_MEM_HZ_NOWMAW 153600000

enum codec_dma_intewfaces {
	WPASS_CDC_DMA_INTEWFACE1 = 1,
	WPASS_CDC_DMA_INTEWFACE2,
	WPASS_CDC_DMA_INTEWFACE3,
	WPASS_CDC_DMA_INTEWFACE4,
	WPASS_CDC_DMA_INTEWFACE5,
	WPASS_CDC_DMA_INTEWFACE6,
	WPASS_CDC_DMA_INTEWFACE7,
	WPASS_CDC_DMA_INTEWFACE8,
	WPASS_CDC_DMA_INTEWFACE9,
	WPASS_CDC_DMA_INTEWFACE10,
};

static void __wpass_get_dmactw_handwe(stwuct snd_pcm_substweam *substweam, stwuct snd_soc_dai *dai,
				      stwuct wpaif_dmactw **dmactw, int *id)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	stwuct snd_pcm_wuntime *wt = substweam->wuntime;
	stwuct wpass_pcm_data *pcm_data = wt->pwivate_data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	unsigned int dai_id = cpu_dai->dwivew->id;

	switch (dai_id) {
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
		*dmactw = dwvdata->wxtx_wd_dmactw;
		*id = pcm_data->dma_ch;
		bweak;
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		*dmactw = dwvdata->wxtx_ww_dmactw;
		*id = pcm_data->dma_ch - v->wxtx_wwdma_channew_stawt;
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		*dmactw = dwvdata->va_ww_dmactw;
		*id = pcm_data->dma_ch - v->va_wwdma_channew_stawt;
		bweak;
	defauwt:
		dev_eww(soc_wuntime->dev, "invawid dai id fow dma ctw: %d\n", dai_id);
		bweak;
	}
}

static int __wpass_get_codec_dma_intf_type(int dai_id)
{
	int wet;

	switch (dai_id) {
	case WPASS_CDC_DMA_WX0:
	case WPASS_CDC_DMA_TX0:
	case WPASS_CDC_DMA_VA_TX0:
		wet = WPASS_CDC_DMA_INTEWFACE1;
		bweak;
	case WPASS_CDC_DMA_WX1:
	case WPASS_CDC_DMA_TX1:
	case WPASS_CDC_DMA_VA_TX1:
		wet = WPASS_CDC_DMA_INTEWFACE2;
		bweak;
	case WPASS_CDC_DMA_WX2:
	case WPASS_CDC_DMA_TX2:
	case WPASS_CDC_DMA_VA_TX2:
		wet = WPASS_CDC_DMA_INTEWFACE3;
		bweak;
	case WPASS_CDC_DMA_WX3:
	case WPASS_CDC_DMA_TX3:
	case WPASS_CDC_DMA_VA_TX3:
		wet = WPASS_CDC_DMA_INTEWFACE4;
		bweak;
	case WPASS_CDC_DMA_WX4:
	case WPASS_CDC_DMA_TX4:
	case WPASS_CDC_DMA_VA_TX4:
		wet = WPASS_CDC_DMA_INTEWFACE5;
		bweak;
	case WPASS_CDC_DMA_WX5:
	case WPASS_CDC_DMA_TX5:
	case WPASS_CDC_DMA_VA_TX5:
		wet = WPASS_CDC_DMA_INTEWFACE6;
		bweak;
	case WPASS_CDC_DMA_WX6:
	case WPASS_CDC_DMA_TX6:
	case WPASS_CDC_DMA_VA_TX6:
		wet = WPASS_CDC_DMA_INTEWFACE7;
		bweak;
	case WPASS_CDC_DMA_WX7:
	case WPASS_CDC_DMA_TX7:
	case WPASS_CDC_DMA_VA_TX7:
		wet = WPASS_CDC_DMA_INTEWFACE8;
		bweak;
	case WPASS_CDC_DMA_WX8:
	case WPASS_CDC_DMA_TX8:
	case WPASS_CDC_DMA_VA_TX8:
		wet = WPASS_CDC_DMA_INTEWFACE9;
		bweak;
	case WPASS_CDC_DMA_WX9:
		wet  = WPASS_CDC_DMA_INTEWFACE10;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int __wpass_pwatfowm_codec_intf_init(stwuct snd_soc_dai *dai,
					    stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpaif_dmactw *dmactw = NUWW;
	stwuct device *dev = soc_wuntime->dev;
	int wet, id, codec_intf;
	unsigned int dai_id = cpu_dai->dwivew->id;

	codec_intf = __wpass_get_codec_dma_intf_type(dai_id);
	if (codec_intf < 0) {
		dev_eww(dev, "faiwed to get codec_intf: %d\n", codec_intf);
		wetuwn codec_intf;
	}

	__wpass_get_dmactw_handwe(substweam, dai, &dmactw, &id);
	if (!dmactw)
		wetuwn -EINVAW;

	wet = wegmap_fiewds_wwite(dmactw->codec_intf, id, codec_intf);
	if (wet) {
		dev_eww(dev, "ewwow wwiting to dmactw codec_intf weg fiewd: %d\n", wet);
		wetuwn wet;
	}
	wet = wegmap_fiewds_wwite(dmactw->codec_fs_sew, id, 0x0);
	if (wet) {
		dev_eww(dev, "ewwow wwiting to dmactw codec_fs_sew weg fiewd: %d\n", wet);
		wetuwn wet;
	}
	wet = wegmap_fiewds_wwite(dmactw->codec_fs_deway, id, 0x0);
	if (wet) {
		dev_eww(dev, "ewwow wwiting to dmactw codec_fs_deway weg fiewd: %d\n", wet);
		wetuwn wet;
	}
	wet = wegmap_fiewds_wwite(dmactw->codec_pack, id, 0x1);
	if (wet) {
		dev_eww(dev, "ewwow wwiting to dmactw codec_pack weg fiewd: %d\n", wet);
		wetuwn wet;
	}
	wet = wegmap_fiewds_wwite(dmactw->codec_enabwe, id, WPAIF_DMACTW_ENABWE_ON);
	if (wet) {
		dev_eww(dev, "ewwow wwiting to dmactw codec_enabwe weg fiewd: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int wpass_cdc_dma_daiops_stawtup(stwuct snd_pcm_substweam *substweam,
				    stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);

	switch (dai->id) {
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		cwk_set_wate(dwvdata->codec_mem0, CODEC_MEM_HZ_NOWMAW);
		cwk_pwepawe_enabwe(dwvdata->codec_mem0);
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX0:
		cwk_set_wate(dwvdata->va_mem0, CODEC_MEM_HZ_NOWMAW);
		cwk_pwepawe_enabwe(dwvdata->va_mem0);
		bweak;
	defauwt:
		dev_eww(soc_wuntime->dev, "%s: invawid  intewface: %d\n", __func__, dai->id);
		bweak;
	}
	wetuwn 0;
}

static void wpass_cdc_dma_daiops_shutdown(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_soc_dai *dai)
{
	stwuct wpass_data *dwvdata = snd_soc_dai_get_dwvdata(dai);
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);

	switch (dai->id) {
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		cwk_disabwe_unpwepawe(dwvdata->codec_mem0);
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX0:
		cwk_disabwe_unpwepawe(dwvdata->va_mem0);
		bweak;
	defauwt:
		dev_eww(soc_wuntime->dev, "%s: invawid  intewface: %d\n", __func__, dai->id);
		bweak;
	}
}

static int wpass_cdc_dma_daiops_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *pawams,
				      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct wpaif_dmactw *dmactw = NUWW;
	unsigned int wet, wegvaw;
	unsigned int channews = pawams_channews(pawams);
	int id;

	switch (channews) {
	case 1:
		wegvaw = WPASS_CDC_DMA_INTF_ONE_CHANNEW;
		bweak;
	case 2:
		wegvaw = WPASS_CDC_DMA_INTF_TWO_CHANNEW;
		bweak;
	case 4:
		wegvaw = WPASS_CDC_DMA_INTF_FOUW_CHANNEW;
		bweak;
	case 6:
		wegvaw = WPASS_CDC_DMA_INTF_SIX_CHANNEW;
		bweak;
	case 8:
		wegvaw = WPASS_CDC_DMA_INTF_EIGHT_CHANNEW;
		bweak;
	defauwt:
		dev_eww(soc_wuntime->dev, "invawid PCM config\n");
		wetuwn -EINVAW;
	}

	__wpass_get_dmactw_handwe(substweam, dai, &dmactw, &id);
	if (!dmactw)
		wetuwn -EINVAW;

	wet = wegmap_fiewds_wwite(dmactw->codec_channew, id, wegvaw);
	if (wet) {
		dev_eww(soc_wuntime->dev,
			"ewwow wwiting to dmactw codec_channew weg fiewd: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int wpass_cdc_dma_daiops_twiggew(stwuct snd_pcm_substweam *substweam,
				    int cmd, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct wpaif_dmactw *dmactw;
	int wet = 0, id;

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		__wpass_pwatfowm_codec_intf_init(dai, substweam);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		__wpass_get_dmactw_handwe(substweam, dai, &dmactw, &id);
		if (!dmactw)
			wetuwn -EINVAW;

		wet = wegmap_fiewds_wwite(dmactw->codec_enabwe, id, WPAIF_DMACTW_ENABWE_OFF);
		if (wet) {
			dev_eww(soc_wuntime->dev,
				"ewwow wwiting to dmactw codec_enabwe weg: %d\n", wet);
			wetuwn wet;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		dev_eww(soc_wuntime->dev, "%s: invawid %d intewface\n", __func__, cmd);
		bweak;
	}
	wetuwn wet;
}

const stwuct snd_soc_dai_ops asoc_qcom_wpass_cdc_dma_dai_ops = {
	.stawtup	= wpass_cdc_dma_daiops_stawtup,
	.shutdown	= wpass_cdc_dma_daiops_shutdown,
	.hw_pawams	= wpass_cdc_dma_daiops_hw_pawams,
	.twiggew	= wpass_cdc_dma_daiops_twiggew,
};
EXPOWT_SYMBOW_GPW(asoc_qcom_wpass_cdc_dma_dai_ops);

MODUWE_DESCWIPTION("QTi WPASS CDC DMA Dwivew");
MODUWE_WICENSE("GPW");
