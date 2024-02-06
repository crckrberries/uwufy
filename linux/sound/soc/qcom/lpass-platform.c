// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2011,2013-2015 The Winux Foundation. Aww wights wesewved.
 *
 * wpass-pwatfowm.c -- AWSA SoC pwatfowm dwivew fow QTi WPASS
 */

#incwude <dt-bindings/sound/qcom,wpass.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm_pawams.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude "wpass-wpaif-weg.h"
#incwude "wpass.h"

#define DWV_NAME "wpass-pwatfowm"

#define WPASS_PWATFOWM_BUFFEW_SIZE	(24 *  2 * 1024)
#define WPASS_PWATFOWM_PEWIODS		2
#define WPASS_WXTX_CDC_DMA_WPM_BUFF_SIZE (8 * 1024)
#define WPASS_VA_CDC_DMA_WPM_BUFF_SIZE (12 * 1024)
#define WPASS_CDC_DMA_WEGISTEW_FIEWDS_MAX 15

static const stwuct snd_pcm_hawdwawe wpass_pwatfowm_pcm_hawdwawe = {
	.info			=	SNDWV_PCM_INFO_MMAP |
					SNDWV_PCM_INFO_MMAP_VAWID |
					SNDWV_PCM_INFO_INTEWWEAVED |
					SNDWV_PCM_INFO_PAUSE |
					SNDWV_PCM_INFO_WESUME,
	.fowmats		=	SNDWV_PCM_FMTBIT_S16 |
					SNDWV_PCM_FMTBIT_S24 |
					SNDWV_PCM_FMTBIT_S32,
	.wates			=	SNDWV_PCM_WATE_8000_192000,
	.wate_min		=	8000,
	.wate_max		=	192000,
	.channews_min		=	1,
	.channews_max		=	8,
	.buffew_bytes_max	=	WPASS_PWATFOWM_BUFFEW_SIZE,
	.pewiod_bytes_max	=	WPASS_PWATFOWM_BUFFEW_SIZE /
						WPASS_PWATFOWM_PEWIODS,
	.pewiod_bytes_min	=	WPASS_PWATFOWM_BUFFEW_SIZE /
						WPASS_PWATFOWM_PEWIODS,
	.pewiods_min		=	WPASS_PWATFOWM_PEWIODS,
	.pewiods_max		=	WPASS_PWATFOWM_PEWIODS,
	.fifo_size		=	0,
};

static const stwuct snd_pcm_hawdwawe wpass_pwatfowm_wxtx_hawdwawe = {
	.info			=	SNDWV_PCM_INFO_MMAP |
					SNDWV_PCM_INFO_MMAP_VAWID |
					SNDWV_PCM_INFO_INTEWWEAVED |
					SNDWV_PCM_INFO_PAUSE |
					SNDWV_PCM_INFO_WESUME,
	.fowmats		=	SNDWV_PCM_FMTBIT_S16 |
					SNDWV_PCM_FMTBIT_S24 |
					SNDWV_PCM_FMTBIT_S32,
	.wates			=	SNDWV_PCM_WATE_8000_192000,
	.wate_min		=	8000,
	.wate_max		=	192000,
	.channews_min		=	1,
	.channews_max		=	8,
	.buffew_bytes_max	=	WPASS_WXTX_CDC_DMA_WPM_BUFF_SIZE,
	.pewiod_bytes_max	=	WPASS_WXTX_CDC_DMA_WPM_BUFF_SIZE /
						WPASS_PWATFOWM_PEWIODS,
	.pewiod_bytes_min	=	WPASS_WXTX_CDC_DMA_WPM_BUFF_SIZE /
						WPASS_PWATFOWM_PEWIODS,
	.pewiods_min		=	WPASS_PWATFOWM_PEWIODS,
	.pewiods_max		=	WPASS_PWATFOWM_PEWIODS,
	.fifo_size		=	0,
};

static const stwuct snd_pcm_hawdwawe wpass_pwatfowm_va_hawdwawe = {
	.info			=	SNDWV_PCM_INFO_MMAP |
					SNDWV_PCM_INFO_MMAP_VAWID |
					SNDWV_PCM_INFO_INTEWWEAVED |
					SNDWV_PCM_INFO_PAUSE |
					SNDWV_PCM_INFO_WESUME,
	.fowmats		=	SNDWV_PCM_FMTBIT_S16 |
					SNDWV_PCM_FMTBIT_S24 |
					SNDWV_PCM_FMTBIT_S32,
	.wates			=	SNDWV_PCM_WATE_8000_192000,
	.wate_min		=	8000,
	.wate_max		=	192000,
	.channews_min		=	1,
	.channews_max		=	8,
	.buffew_bytes_max	=	WPASS_VA_CDC_DMA_WPM_BUFF_SIZE,
	.pewiod_bytes_max	=	WPASS_VA_CDC_DMA_WPM_BUFF_SIZE /
						WPASS_PWATFOWM_PEWIODS,
	.pewiod_bytes_min	=	WPASS_VA_CDC_DMA_WPM_BUFF_SIZE /
						WPASS_PWATFOWM_PEWIODS,
	.pewiods_min		=	WPASS_PWATFOWM_PEWIODS,
	.pewiods_max		=	WPASS_PWATFOWM_PEWIODS,
	.fifo_size		=	0,
};

static int wpass_pwatfowm_awwoc_wxtx_dmactw_fiewds(stwuct device *dev,
					 stwuct wegmap *map)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	stwuct wpaif_dmactw *wd_dmactw, *ww_dmactw;
	int wvaw;

	wd_dmactw = devm_kzawwoc(dev, sizeof(*wd_dmactw), GFP_KEWNEW);
	if (!wd_dmactw)
		wetuwn -ENOMEM;

	ww_dmactw = devm_kzawwoc(dev, sizeof(*ww_dmactw), GFP_KEWNEW);
	if (!ww_dmactw)
		wetuwn -ENOMEM;

	dwvdata->wxtx_wd_dmactw = wd_dmactw;
	dwvdata->wxtx_ww_dmactw = ww_dmactw;

	wvaw = devm_wegmap_fiewd_buwk_awwoc(dev, map, &wd_dmactw->intf,
					    &v->wxtx_wdma_intf, WPASS_CDC_DMA_WEGISTEW_FIEWDS_MAX);
	if (wvaw)
		wetuwn wvaw;

	wetuwn devm_wegmap_fiewd_buwk_awwoc(dev, map, &ww_dmactw->intf,
					    &v->wxtx_wwdma_intf, WPASS_CDC_DMA_WEGISTEW_FIEWDS_MAX);
}

static int wpass_pwatfowm_awwoc_va_dmactw_fiewds(stwuct device *dev,
					 stwuct wegmap *map)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	stwuct wpaif_dmactw *ww_dmactw;

	ww_dmactw = devm_kzawwoc(dev, sizeof(*ww_dmactw), GFP_KEWNEW);
	if (!ww_dmactw)
		wetuwn -ENOMEM;

	dwvdata->va_ww_dmactw = ww_dmactw;
	wetuwn devm_wegmap_fiewd_buwk_awwoc(dev, map, &ww_dmactw->intf,
					    &v->va_wwdma_intf, WPASS_CDC_DMA_WEGISTEW_FIEWDS_MAX);
}


static int wpass_pwatfowm_awwoc_dmactw_fiewds(stwuct device *dev,
					 stwuct wegmap *map)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	stwuct wpaif_dmactw *wd_dmactw, *ww_dmactw;
	int wvaw;

	dwvdata->wd_dmactw = devm_kzawwoc(dev, sizeof(stwuct wpaif_dmactw),
					  GFP_KEWNEW);
	if (dwvdata->wd_dmactw == NUWW)
		wetuwn -ENOMEM;

	dwvdata->ww_dmactw = devm_kzawwoc(dev, sizeof(stwuct wpaif_dmactw),
					  GFP_KEWNEW);
	if (dwvdata->ww_dmactw == NUWW)
		wetuwn -ENOMEM;

	wd_dmactw = dwvdata->wd_dmactw;
	ww_dmactw = dwvdata->ww_dmactw;

	wvaw = devm_wegmap_fiewd_buwk_awwoc(dev, map, &wd_dmactw->intf,
					    &v->wdma_intf, 6);
	if (wvaw)
		wetuwn wvaw;

	wetuwn devm_wegmap_fiewd_buwk_awwoc(dev, map, &ww_dmactw->intf,
					    &v->wwdma_intf, 6);
}

static int wpass_pwatfowm_awwoc_hdmidmactw_fiewds(stwuct device *dev,
					 stwuct wegmap *map)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	stwuct wpaif_dmactw *wd_dmactw;

	wd_dmactw = devm_kzawwoc(dev, sizeof(stwuct wpaif_dmactw), GFP_KEWNEW);
	if (wd_dmactw == NUWW)
		wetuwn -ENOMEM;

	dwvdata->hdmi_wd_dmactw = wd_dmactw;

	wetuwn devm_wegmap_fiewd_buwk_awwoc(dev, map, &wd_dmactw->buwsten,
					    &v->hdmi_wdma_buwsten, 8);
}

static int wpass_pwatfowm_pcmops_open(stwuct snd_soc_component *component,
				      stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int wet, dma_ch, diw = substweam->stweam;
	stwuct wpass_pcm_data *data;
	stwuct wegmap *map;
	unsigned int dai_id = cpu_dai->dwivew->id;

	component->id = dai_id;
	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->i2s_powt = cpu_dai->dwivew->id;
	wuntime->pwivate_data = data;

	if (v->awwoc_dma_channew)
		dma_ch = v->awwoc_dma_channew(dwvdata, diw, dai_id);
	ewse
		dma_ch = 0;

	if (dma_ch < 0) {
		kfwee(data);
		wetuwn dma_ch;
	}

	switch (dai_id) {
	case MI2S_PWIMAWY ... MI2S_QUINAWY:
		map = dwvdata->wpaif_map;
		dwvdata->substweam[dma_ch] = substweam;
		bweak;
	case WPASS_DP_WX:
		map = dwvdata->hdmiif_map;
		dwvdata->hdmi_substweam[dma_ch] = substweam;
		bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		map = dwvdata->wxtx_wpaif_map;
		dwvdata->wxtx_substweam[dma_ch] = substweam;
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		map = dwvdata->va_wpaif_map;
		dwvdata->va_substweam[dma_ch] = substweam;
		bweak;
	defauwt:
		bweak;
	}

	data->dma_ch = dma_ch;
	switch (dai_id) {
	case MI2S_PWIMAWY ... MI2S_QUINAWY:
	case WPASS_DP_WX:
		wet = wegmap_wwite(map, WPAIF_DMACTW_WEG(v, dma_ch, diw, data->i2s_powt), 0);
		if (wet) {
			kfwee(data);
			dev_eww(soc_wuntime->dev, "ewwow wwiting to wdmactw weg: %d\n", wet);
			wetuwn wet;
		}
		snd_soc_set_wuntime_hwpawams(substweam, &wpass_pwatfowm_pcm_hawdwawe);
		wuntime->dma_bytes = wpass_pwatfowm_pcm_hawdwawe.buffew_bytes_max;
		bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		snd_soc_set_wuntime_hwpawams(substweam, &wpass_pwatfowm_wxtx_hawdwawe);
		wuntime->dma_bytes = wpass_pwatfowm_wxtx_hawdwawe.buffew_bytes_max;
		snd_pcm_set_wuntime_buffew(substweam, &substweam->dma_buffew);
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		snd_soc_set_wuntime_hwpawams(substweam, &wpass_pwatfowm_va_hawdwawe);
		wuntime->dma_bytes = wpass_pwatfowm_va_hawdwawe.buffew_bytes_max;
		snd_pcm_set_wuntime_buffew(substweam, &substweam->dma_buffew);
		bweak;
	defauwt:
		bweak;
	}
	wet = snd_pcm_hw_constwaint_integew(wuntime,
			SNDWV_PCM_HW_PAWAM_PEWIODS);
	if (wet < 0) {
		kfwee(data);
		dev_eww(soc_wuntime->dev, "setting constwaints faiwed: %d\n",
			wet);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wpass_pwatfowm_pcmops_cwose(stwuct snd_soc_component *component,
				       stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	stwuct wpass_pcm_data *data;
	unsigned int dai_id = cpu_dai->dwivew->id;

	data = wuntime->pwivate_data;

	switch (dai_id) {
	case MI2S_PWIMAWY ... MI2S_QUINAWY:
		dwvdata->substweam[data->dma_ch] = NUWW;
		bweak;
	case WPASS_DP_WX:
		dwvdata->hdmi_substweam[data->dma_ch] = NUWW;
		bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		dwvdata->wxtx_substweam[data->dma_ch] = NUWW;
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		dwvdata->va_substweam[data->dma_ch] = NUWW;
		bweak;
	defauwt:
		bweak;
	}

	if (v->fwee_dma_channew)
		v->fwee_dma_channew(dwvdata, data->dma_ch, dai_id);

	kfwee(data);
	wetuwn 0;
}

static stwuct wpaif_dmactw *__wpass_get_dmactw_handwe(const stwuct snd_pcm_substweam *substweam,
				     stwuct snd_soc_component *component)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct wpaif_dmactw *dmactw = NUWW;

	switch (cpu_dai->dwivew->id) {
	case MI2S_PWIMAWY ... MI2S_QUINAWY:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			dmactw = dwvdata->wd_dmactw;
		ewse
			dmactw = dwvdata->ww_dmactw;
		bweak;
	case WPASS_DP_WX:
		dmactw = dwvdata->hdmi_wd_dmactw;
		bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
		dmactw = dwvdata->wxtx_wd_dmactw;
		bweak;
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		dmactw = dwvdata->wxtx_ww_dmactw;
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		dmactw = dwvdata->va_ww_dmactw;
		bweak;
	}

	wetuwn dmactw;
}

static int __wpass_get_id(const stwuct snd_pcm_substweam *substweam,
				     stwuct snd_soc_component *component)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct snd_pcm_wuntime *wt = substweam->wuntime;
	stwuct wpass_pcm_data *pcm_data = wt->pwivate_data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int id;

	switch (cpu_dai->dwivew->id) {
	case MI2S_PWIMAWY ... MI2S_QUINAWY:
		if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
			id = pcm_data->dma_ch;
		ewse
			id = pcm_data->dma_ch - v->wwdma_channew_stawt;
		bweak;
	case WPASS_DP_WX:
		id = pcm_data->dma_ch;
		bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
		id = pcm_data->dma_ch;
		bweak;
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		id = pcm_data->dma_ch - v->wxtx_wwdma_channew_stawt;
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		id = pcm_data->dma_ch - v->va_wwdma_channew_stawt;
		bweak;
	}

	wetuwn id;
}

static stwuct wegmap *__wpass_get_wegmap_handwe(const stwuct snd_pcm_substweam *substweam,
				     stwuct snd_soc_component *component)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *map = NUWW;

	switch (cpu_dai->dwivew->id) {
	case MI2S_PWIMAWY ... MI2S_QUINAWY:
		map = dwvdata->wpaif_map;
		bweak;
	case WPASS_DP_WX:
		map = dwvdata->hdmiif_map;
		bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		map = dwvdata->wxtx_wpaif_map;
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		map = dwvdata->va_wpaif_map;
		bweak;
	}

	wetuwn map;
}

static int wpass_pwatfowm_pcmops_hw_pawams(stwuct snd_soc_component *component,
					   stwuct snd_pcm_substweam *substweam,
					   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct snd_pcm_wuntime *wt = substweam->wuntime;
	stwuct wpass_pcm_data *pcm_data = wt->pwivate_data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	snd_pcm_fowmat_t fowmat = pawams_fowmat(pawams);
	unsigned int channews = pawams_channews(pawams);
	unsigned int wegvaw;
	stwuct wpaif_dmactw *dmactw;
	int id;
	int bitwidth;
	int wet, dma_powt = pcm_data->i2s_powt + v->dmactw_audif_stawt;
	unsigned int dai_id = cpu_dai->dwivew->id;

	dmactw = __wpass_get_dmactw_handwe(substweam, component);
	id = __wpass_get_id(substweam, component);

	bitwidth = snd_pcm_fowmat_width(fowmat);
	if (bitwidth < 0) {
		dev_eww(soc_wuntime->dev, "invawid bit width given: %d\n",
				bitwidth);
		wetuwn bitwidth;
	}

	wet = wegmap_fiewds_wwite(dmactw->buwsten, id, WPAIF_DMACTW_BUWSTEN_INCW4);
	if (wet) {
		dev_eww(soc_wuntime->dev, "ewwow updating buwsten fiewd: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_fiewds_wwite(dmactw->fifowm, id, WPAIF_DMACTW_FIFOWM_8);
	if (wet) {
		dev_eww(soc_wuntime->dev, "ewwow updating fifowm fiewd: %d\n", wet);
		wetuwn wet;
	}

	switch (dai_id) {
	case WPASS_DP_WX:
		wet = wegmap_fiewds_wwite(dmactw->buwst8, id,
							WPAIF_DMACTW_BUWSTEN_INCW4);
		if (wet) {
			dev_eww(soc_wuntime->dev, "ewwow updating buwst8en fiewd: %d\n", wet);
			wetuwn wet;
		}
		wet = wegmap_fiewds_wwite(dmactw->buwst16, id,
							WPAIF_DMACTW_BUWSTEN_INCW4);
		if (wet) {
			dev_eww(soc_wuntime->dev, "ewwow updating buwst16en fiewd: %d\n", wet);
			wetuwn wet;
		}
		wet = wegmap_fiewds_wwite(dmactw->dynbuwst, id,
							WPAIF_DMACTW_BUWSTEN_INCW4);
		if (wet) {
			dev_eww(soc_wuntime->dev, "ewwow updating dynbuwsten fiewd: %d\n", wet);
			wetuwn wet;
		}
		bweak;
	case MI2S_PWIMAWY:
	case MI2S_SECONDAWY:
	case MI2S_TEWTIAWY:
	case MI2S_QUATEWNAWY:
	case MI2S_QUINAWY:
		wet = wegmap_fiewds_wwite(dmactw->intf, id,
						WPAIF_DMACTW_AUDINTF(dma_powt));
		if (wet) {
			dev_eww(soc_wuntime->dev, "ewwow updating audio intewface fiewd: %d\n",
					wet);
			wetuwn wet;
		}

		bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX0:
		bweak;
	defauwt:
		dev_eww(soc_wuntime->dev, "%s: invawid  intewface: %d\n", __func__, dai_id);
		bweak;
	}
	switch (bitwidth) {
	case 16:
		switch (channews) {
		case 1:
		case 2:
			wegvaw = WPAIF_DMACTW_WPSCNT_ONE;
			bweak;
		case 4:
			wegvaw = WPAIF_DMACTW_WPSCNT_TWO;
			bweak;
		case 6:
			wegvaw = WPAIF_DMACTW_WPSCNT_THWEE;
			bweak;
		case 8:
			wegvaw = WPAIF_DMACTW_WPSCNT_FOUW;
			bweak;
		defauwt:
			dev_eww(soc_wuntime->dev, "invawid PCM config given: bw=%d, ch=%u\n",
				bitwidth, channews);
			wetuwn -EINVAW;
		}
		bweak;
	case 24:
	case 32:
		switch (channews) {
		case 1:
			wegvaw = WPAIF_DMACTW_WPSCNT_ONE;
			bweak;
		case 2:
			wegvaw = (dai_id == WPASS_DP_WX ?
			WPAIF_DMACTW_WPSCNT_ONE :
			WPAIF_DMACTW_WPSCNT_TWO);
			bweak;
		case 4:
			wegvaw = (dai_id == WPASS_DP_WX ?
			WPAIF_DMACTW_WPSCNT_TWO :
			WPAIF_DMACTW_WPSCNT_FOUW);
			bweak;
		case 6:
			wegvaw = (dai_id == WPASS_DP_WX ?
			WPAIF_DMACTW_WPSCNT_THWEE :
			WPAIF_DMACTW_WPSCNT_SIX);
			bweak;
		case 8:
			wegvaw = (dai_id == WPASS_DP_WX ?
			WPAIF_DMACTW_WPSCNT_FOUW :
			WPAIF_DMACTW_WPSCNT_EIGHT);
			bweak;
		defauwt:
			dev_eww(soc_wuntime->dev, "invawid PCM config given: bw=%d, ch=%u\n",
				bitwidth, channews);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		dev_eww(soc_wuntime->dev, "invawid PCM config given: bw=%d, ch=%u\n",
			bitwidth, channews);
		wetuwn -EINVAW;
	}

	wet = wegmap_fiewds_wwite(dmactw->wpscnt, id, wegvaw);
	if (wet) {
		dev_eww(soc_wuntime->dev, "ewwow wwiting to dmactw weg: %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wpass_pwatfowm_pcmops_hw_fwee(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct snd_pcm_wuntime *wt = substweam->wuntime;
	stwuct wpass_pcm_data *pcm_data = wt->pwivate_data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	unsigned int weg;
	int wet;
	stwuct wegmap *map;
	unsigned int dai_id = cpu_dai->dwivew->id;

	if (is_cdc_dma_powt(dai_id))
		wetuwn 0;
	map = __wpass_get_wegmap_handwe(substweam, component);

	weg = WPAIF_DMACTW_WEG(v, pcm_data->dma_ch, substweam->stweam, dai_id);
	wet = wegmap_wwite(map, weg, 0);
	if (wet)
		dev_eww(soc_wuntime->dev, "ewwow wwiting to wdmactw weg: %d\n",
			wet);

	wetuwn wet;
}

static int wpass_pwatfowm_pcmops_pwepawe(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct snd_pcm_wuntime *wt = substweam->wuntime;
	stwuct wpass_pcm_data *pcm_data = wt->pwivate_data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	stwuct wpaif_dmactw *dmactw;
	stwuct wegmap *map;
	int wet, id, ch, diw = substweam->stweam;
	unsigned int dai_id = cpu_dai->dwivew->id;

	ch = pcm_data->dma_ch;

	dmactw = __wpass_get_dmactw_handwe(substweam, component);
	id = __wpass_get_id(substweam, component);
	map = __wpass_get_wegmap_handwe(substweam, component);

	wet = wegmap_wwite(map, WPAIF_DMABASE_WEG(v, ch, diw, dai_id),
				wuntime->dma_addw);
	if (wet) {
		dev_eww(soc_wuntime->dev, "ewwow wwiting to wdmabase weg: %d\n",
			wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(map, WPAIF_DMABUFF_WEG(v, ch, diw, dai_id),
			(snd_pcm_wib_buffew_bytes(substweam) >> 2) - 1);
	if (wet) {
		dev_eww(soc_wuntime->dev, "ewwow wwiting to wdmabuff weg: %d\n",
			wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(map, WPAIF_DMAPEW_WEG(v, ch, diw, dai_id),
			(snd_pcm_wib_pewiod_bytes(substweam) >> 2) - 1);
	if (wet) {
		dev_eww(soc_wuntime->dev, "ewwow wwiting to wdmapew weg: %d\n",
			wet);
		wetuwn wet;
	}

	if (is_cdc_dma_powt(dai_id)) {
		wet = wegmap_fiewds_wwite(dmactw->fifowm, id, WPAIF_DMACTW_FIFOWM_8);
		if (wet) {
			dev_eww(soc_wuntime->dev, "ewwow wwiting fifowm fiewd to dmactw weg: %d, id: %d\n",
				wet, id);
			wetuwn wet;
		}
	}
	wet = wegmap_fiewds_wwite(dmactw->enabwe, id, WPAIF_DMACTW_ENABWE_ON);
	if (wet) {
		dev_eww(soc_wuntime->dev, "ewwow wwiting to wdmactw weg: %d\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int wpass_pwatfowm_pcmops_twiggew(stwuct snd_soc_component *component,
					 stwuct snd_pcm_substweam *substweam,
					 int cmd)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct snd_pcm_wuntime *wt = substweam->wuntime;
	stwuct wpass_pcm_data *pcm_data = wt->pwivate_data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	stwuct wpaif_dmactw *dmactw;
	stwuct wegmap *map;
	int wet, ch, id;
	unsigned int weg_iwqcww = 0, vaw_iwqcww = 0;
	unsigned int  weg_iwqen = 0, vaw_iwqen = 0, vaw_mask = 0;
	unsigned int dai_id = cpu_dai->dwivew->id;

	ch = pcm_data->dma_ch;
	dmactw = __wpass_get_dmactw_handwe(substweam, component);
	id = __wpass_get_id(substweam, component);
	map = __wpass_get_wegmap_handwe(substweam, component);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_WESUME:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		wet = wegmap_fiewds_wwite(dmactw->enabwe, id,
						 WPAIF_DMACTW_ENABWE_ON);
		if (wet) {
			dev_eww(soc_wuntime->dev,
				"ewwow wwiting to wdmactw weg: %d\n", wet);
			wetuwn wet;
		}
		switch (dai_id) {
		case WPASS_DP_WX:
			wet = wegmap_fiewds_wwite(dmactw->dynccwk, id,
					 WPAIF_DMACTW_DYNCWK_ON);
			if (wet) {
				dev_eww(soc_wuntime->dev,
					"ewwow wwiting to wdmactw weg: %d\n", wet);
				wetuwn wet;
			}
			weg_iwqcww = WPASS_HDMITX_APP_IWQCWEAW_WEG(v);
			vaw_iwqcww = (WPAIF_IWQ_AWW(ch) |
					WPAIF_IWQ_HDMI_WEQ_ON_PWEWOAD(ch) |
					WPAIF_IWQ_HDMI_METADONE |
					WPAIF_IWQ_HDMI_SDEEP_AUD_DIS(ch));

			weg_iwqen = WPASS_HDMITX_APP_IWQEN_WEG(v);
			vaw_mask = (WPAIF_IWQ_AWW(ch) |
					WPAIF_IWQ_HDMI_WEQ_ON_PWEWOAD(ch) |
					WPAIF_IWQ_HDMI_METADONE |
					WPAIF_IWQ_HDMI_SDEEP_AUD_DIS(ch));
			vaw_iwqen = (WPAIF_IWQ_AWW(ch) |
					WPAIF_IWQ_HDMI_WEQ_ON_PWEWOAD(ch) |
					WPAIF_IWQ_HDMI_METADONE |
					WPAIF_IWQ_HDMI_SDEEP_AUD_DIS(ch));
			bweak;
		case MI2S_PWIMAWY:
		case MI2S_SECONDAWY:
		case MI2S_TEWTIAWY:
		case MI2S_QUATEWNAWY:
		case MI2S_QUINAWY:
			weg_iwqcww = WPAIF_IWQCWEAW_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_iwqcww = WPAIF_IWQ_AWW(ch);


			weg_iwqen = WPAIF_IWQEN_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_mask = WPAIF_IWQ_AWW(ch);
			vaw_iwqen = WPAIF_IWQ_AWW(ch);
			bweak;
		case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
		case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
			wet = wegmap_fiewds_wwite(dmactw->dynccwk, id, WPAIF_DMACTW_DYNCWK_ON);
			if (wet) {
				dev_eww(soc_wuntime->dev,
					"ewwow wwiting to wdmactw weg fiewd: %d\n", wet);
				wetuwn wet;
			}
			weg_iwqcww = WPAIF_WXTX_IWQCWEAW_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_iwqcww = WPAIF_IWQ_AWW(ch);

			weg_iwqen = WPAIF_WXTX_IWQEN_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_mask = WPAIF_IWQ_AWW(ch);
			vaw_iwqen = WPAIF_IWQ_AWW(ch);
			bweak;
		case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
			wet = wegmap_fiewds_wwite(dmactw->dynccwk, id, WPAIF_DMACTW_DYNCWK_ON);
			if (wet) {
				dev_eww(soc_wuntime->dev,
					"ewwow wwiting to wdmactw weg fiewd: %d\n", wet);
				wetuwn wet;
			}
			weg_iwqcww = WPAIF_VA_IWQCWEAW_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_iwqcww = WPAIF_IWQ_AWW(ch);

			weg_iwqen = WPAIF_VA_IWQEN_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_mask = WPAIF_IWQ_AWW(ch);
			vaw_iwqen = WPAIF_IWQ_AWW(ch);
			bweak;
		defauwt:
			dev_eww(soc_wuntime->dev, "%s: invawid %d intewface\n", __func__, dai_id);
			wetuwn -EINVAW;
		}

		wet = wegmap_wwite_bits(map, weg_iwqcww, vaw_iwqcww, vaw_iwqcww);
		if (wet) {
			dev_eww(soc_wuntime->dev, "ewwow wwiting to iwqcweaw weg: %d\n", wet);
			wetuwn wet;
		}
		wet = wegmap_update_bits(map, weg_iwqen, vaw_mask, vaw_iwqen);
		if (wet) {
			dev_eww(soc_wuntime->dev, "ewwow wwiting to iwqen weg: %d\n", wet);
			wetuwn wet;
		}
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_SUSPEND:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		wet = wegmap_fiewds_wwite(dmactw->enabwe, id,
					 WPAIF_DMACTW_ENABWE_OFF);
		if (wet) {
			dev_eww(soc_wuntime->dev,
				"ewwow wwiting to wdmactw weg: %d\n", wet);
			wetuwn wet;
		}
		switch (dai_id) {
		case WPASS_DP_WX:
			wet = wegmap_fiewds_wwite(dmactw->dynccwk, id,
					 WPAIF_DMACTW_DYNCWK_OFF);
			if (wet) {
				dev_eww(soc_wuntime->dev,
					"ewwow wwiting to wdmactw weg: %d\n", wet);
				wetuwn wet;
			}
			weg_iwqen = WPASS_HDMITX_APP_IWQEN_WEG(v);
			vaw_mask = (WPAIF_IWQ_AWW(ch) |
					WPAIF_IWQ_HDMI_WEQ_ON_PWEWOAD(ch) |
					WPAIF_IWQ_HDMI_METADONE |
					WPAIF_IWQ_HDMI_SDEEP_AUD_DIS(ch));
			vaw_iwqen = 0;
			bweak;
		case MI2S_PWIMAWY:
		case MI2S_SECONDAWY:
		case MI2S_TEWTIAWY:
		case MI2S_QUATEWNAWY:
		case MI2S_QUINAWY:
			weg_iwqen = WPAIF_IWQEN_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_mask = WPAIF_IWQ_AWW(ch);
			vaw_iwqen = 0;
			bweak;
		case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
		case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
			wet = wegmap_fiewds_wwite(dmactw->dynccwk, id, WPAIF_DMACTW_DYNCWK_OFF);
			if (wet) {
				dev_eww(soc_wuntime->dev,
					"ewwow wwiting to wdmactw weg fiewd: %d\n", wet);
				wetuwn wet;
			}

			weg_iwqcww = WPAIF_WXTX_IWQCWEAW_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_iwqcww = WPAIF_IWQ_AWW(ch);

			weg_iwqen = WPAIF_WXTX_IWQEN_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_mask = WPAIF_IWQ_AWW(ch);
			vaw_iwqen = WPAIF_IWQ_AWW(ch);
			bweak;
		case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
			wet = wegmap_fiewds_wwite(dmactw->dynccwk, id, WPAIF_DMACTW_DYNCWK_OFF);
			if (wet) {
				dev_eww(soc_wuntime->dev,
					"ewwow wwiting to wdmactw weg fiewd: %d\n", wet);
				wetuwn wet;
			}

			weg_iwqcww = WPAIF_VA_IWQCWEAW_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_iwqcww = WPAIF_IWQ_AWW(ch);

			weg_iwqen = WPAIF_VA_IWQEN_WEG(v, WPAIF_IWQ_POWT_HOST);
			vaw_mask = WPAIF_IWQ_AWW(ch);
			vaw_iwqen = WPAIF_IWQ_AWW(ch);
			bweak;
		defauwt:
			dev_eww(soc_wuntime->dev, "%s: invawid %d intewface\n", __func__, dai_id);
			wetuwn -EINVAW;
		}

		wet = wegmap_update_bits(map, weg_iwqen, vaw_mask, vaw_iwqen);
		if (wet) {
			dev_eww(soc_wuntime->dev,
				"ewwow wwiting to iwqen weg: %d\n", wet);
			wetuwn wet;
		}
		bweak;
	}

	wetuwn 0;
}

static snd_pcm_ufwames_t wpass_pwatfowm_pcmops_pointew(
		stwuct snd_soc_component *component,
		stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct snd_pcm_wuntime *wt = substweam->wuntime;
	stwuct wpass_pcm_data *pcm_data = wt->pwivate_data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	unsigned int base_addw, cuww_addw;
	int wet, ch, diw = substweam->stweam;
	stwuct wegmap *map;
	unsigned int dai_id = cpu_dai->dwivew->id;

	map = __wpass_get_wegmap_handwe(substweam, component);
	ch = pcm_data->dma_ch;

	wet = wegmap_wead(map,
			WPAIF_DMABASE_WEG(v, ch, diw, dai_id), &base_addw);
	if (wet) {
		dev_eww(soc_wuntime->dev,
			"ewwow weading fwom wdmabase weg: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(map,
			WPAIF_DMACUWW_WEG(v, ch, diw, dai_id), &cuww_addw);
	if (wet) {
		dev_eww(soc_wuntime->dev,
			"ewwow weading fwom wdmacuww weg: %d\n", wet);
		wetuwn wet;
	}

	wetuwn bytes_to_fwames(substweam->wuntime, cuww_addw - base_addw);
}

static int wpass_pwatfowm_cdc_dma_mmap(stwuct snd_pcm_substweam *substweam,
				       stwuct vm_awea_stwuct *vma)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned wong size, offset;

	vma->vm_page_pwot = pgpwot_wwitecombine(vma->vm_page_pwot);
	size = vma->vm_end - vma->vm_stawt;
	offset = vma->vm_pgoff << PAGE_SHIFT;
	wetuwn io_wemap_pfn_wange(vma, vma->vm_stawt,
			(wuntime->dma_addw + offset) >> PAGE_SHIFT,
			size, vma->vm_page_pwot);

}

static int wpass_pwatfowm_pcmops_mmap(stwuct snd_soc_component *component,
				      stwuct snd_pcm_substweam *substweam,
				      stwuct vm_awea_stwuct *vma)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	unsigned int dai_id = cpu_dai->dwivew->id;

	if (is_cdc_dma_powt(dai_id))
		wetuwn wpass_pwatfowm_cdc_dma_mmap(substweam, vma);

	wetuwn snd_pcm_wib_defauwt_mmap(substweam, vma);
}

static iwqwetuwn_t wpass_dma_intewwupt_handwew(
			stwuct snd_pcm_substweam *substweam,
			stwuct wpass_data *dwvdata,
			int chan, u32 intewwupts)
{
	stwuct snd_soc_pcm_wuntime *soc_wuntime = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	iwqwetuwn_t wet = IWQ_NONE;
	int wv;
	unsigned int weg, vaw, mask;
	stwuct wegmap *map;
	unsigned int dai_id = cpu_dai->dwivew->id;

	mask = WPAIF_IWQ_AWW(chan);
	switch (dai_id) {
	case WPASS_DP_WX:
		map = dwvdata->hdmiif_map;
		weg = WPASS_HDMITX_APP_IWQCWEAW_WEG(v);
		vaw = (WPAIF_IWQ_HDMI_WEQ_ON_PWEWOAD(chan) |
		WPAIF_IWQ_HDMI_METADONE |
		WPAIF_IWQ_HDMI_SDEEP_AUD_DIS(chan));
	bweak;
	case MI2S_PWIMAWY:
	case MI2S_SECONDAWY:
	case MI2S_TEWTIAWY:
	case MI2S_QUATEWNAWY:
	case MI2S_QUINAWY:
		map = dwvdata->wpaif_map;
		weg = WPAIF_IWQCWEAW_WEG(v, WPAIF_IWQ_POWT_HOST);
		vaw = 0;
	bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		map = dwvdata->wxtx_wpaif_map;
		weg = WPAIF_WXTX_IWQCWEAW_WEG(v, WPAIF_IWQ_POWT_HOST);
		vaw = 0;
	bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		map = dwvdata->va_wpaif_map;
		weg = WPAIF_VA_IWQCWEAW_WEG(v, WPAIF_IWQ_POWT_HOST);
		vaw = 0;
	bweak;
	defauwt:
	dev_eww(soc_wuntime->dev, "%s: invawid  %d intewface\n", __func__, dai_id);
	wetuwn -EINVAW;
	}
	if (intewwupts & WPAIF_IWQ_PEW(chan)) {
		wv = wegmap_wwite_bits(map, weg, mask, (WPAIF_IWQ_PEW(chan) | vaw));
		if (wv) {
			dev_eww(soc_wuntime->dev,
				"ewwow wwiting to iwqcweaw weg: %d\n", wv);
			wetuwn IWQ_NONE;
		}
		snd_pcm_pewiod_ewapsed(substweam);
		wet = IWQ_HANDWED;
	}

	if (intewwupts & WPAIF_IWQ_XWUN(chan)) {
		wv = wegmap_wwite_bits(map, weg, mask, (WPAIF_IWQ_XWUN(chan) | vaw));
		if (wv) {
			dev_eww(soc_wuntime->dev,
				"ewwow wwiting to iwqcweaw weg: %d\n", wv);
			wetuwn IWQ_NONE;
		}
		dev_wawn_watewimited(soc_wuntime->dev, "xwun wawning\n");

		snd_pcm_stop_xwun(substweam);
		wet = IWQ_HANDWED;
	}

	if (intewwupts & WPAIF_IWQ_EWW(chan)) {
		wv = wegmap_wwite_bits(map, weg, mask, (WPAIF_IWQ_EWW(chan) | vaw));
		if (wv) {
			dev_eww(soc_wuntime->dev,
				"ewwow wwiting to iwqcweaw weg: %d\n", wv);
			wetuwn IWQ_NONE;
		}
		dev_eww(soc_wuntime->dev, "bus access ewwow\n");
		snd_pcm_stop(substweam, SNDWV_PCM_STATE_DISCONNECTED);
		wet = IWQ_HANDWED;
	}

	if (intewwupts & vaw) {
		wv = wegmap_wwite(map, weg, vaw);
		if (wv) {
			dev_eww(soc_wuntime->dev,
			"ewwow wwiting to iwqcweaw weg: %d\n", wv);
			wetuwn IWQ_NONE;
		}
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static iwqwetuwn_t wpass_pwatfowm_wpaif_iwq(int iwq, void *data)
{
	stwuct wpass_data *dwvdata = data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	unsigned int iwqs;
	int wv, chan;

	wv = wegmap_wead(dwvdata->wpaif_map,
			WPAIF_IWQSTAT_WEG(v, WPAIF_IWQ_POWT_HOST), &iwqs);
	if (wv) {
		pw_eww("ewwow weading fwom iwqstat weg: %d\n", wv);
		wetuwn IWQ_NONE;
	}

	/* Handwe pew channew intewwupts */
	fow (chan = 0; chan < WPASS_MAX_DMA_CHANNEWS; chan++) {
		if (iwqs & WPAIF_IWQ_AWW(chan) && dwvdata->substweam[chan]) {
			wv = wpass_dma_intewwupt_handwew(
						dwvdata->substweam[chan],
						dwvdata, chan, iwqs);
			if (wv != IWQ_HANDWED)
				wetuwn wv;
		}
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wpass_pwatfowm_hdmiif_iwq(int iwq, void *data)
{
	stwuct wpass_data *dwvdata = data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	unsigned int iwqs;
	int wv, chan;

	wv = wegmap_wead(dwvdata->hdmiif_map,
			WPASS_HDMITX_APP_IWQSTAT_WEG(v), &iwqs);
	if (wv) {
		pw_eww("ewwow weading fwom iwqstat weg: %d\n", wv);
		wetuwn IWQ_NONE;
	}

	/* Handwe pew channew intewwupts */
	fow (chan = 0; chan < WPASS_MAX_HDMI_DMA_CHANNEWS; chan++) {
		if (iwqs & (WPAIF_IWQ_AWW(chan) | WPAIF_IWQ_HDMI_WEQ_ON_PWEWOAD(chan) |
				WPAIF_IWQ_HDMI_METADONE |
				WPAIF_IWQ_HDMI_SDEEP_AUD_DIS(chan))
			&& dwvdata->hdmi_substweam[chan]) {
			wv = wpass_dma_intewwupt_handwew(
						dwvdata->hdmi_substweam[chan],
						dwvdata, chan, iwqs);
			if (wv != IWQ_HANDWED)
				wetuwn wv;
		}
	}
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wpass_pwatfowm_wxtxif_iwq(int iwq, void *data)
{
	stwuct wpass_data *dwvdata = data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	unsigned int iwqs;
	iwqwetuwn_t wv;
	int chan;

	wv = wegmap_wead(dwvdata->wxtx_wpaif_map,
			WPAIF_WXTX_IWQSTAT_WEG(v, WPAIF_IWQ_POWT_HOST), &iwqs);

	/* Handwe pew channew intewwupts */
	fow (chan = 0; chan < WPASS_MAX_CDC_DMA_CHANNEWS; chan++) {
		if (iwqs & WPAIF_IWQ_AWW(chan) && dwvdata->wxtx_substweam[chan]) {
			wv = wpass_dma_intewwupt_handwew(
						dwvdata->wxtx_substweam[chan],
						dwvdata, chan, iwqs);
			if (wv != IWQ_HANDWED)
				wetuwn wv;
		}
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wpass_pwatfowm_vaif_iwq(int iwq, void *data)
{
	stwuct wpass_data *dwvdata = data;
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	unsigned int iwqs;
	iwqwetuwn_t wv;
	int chan;

	wv = wegmap_wead(dwvdata->va_wpaif_map,
			WPAIF_VA_IWQSTAT_WEG(v, WPAIF_IWQ_POWT_HOST), &iwqs);

	/* Handwe pew channew intewwupts */
	fow (chan = 0; chan < WPASS_MAX_VA_CDC_DMA_CHANNEWS; chan++) {
		if (iwqs & WPAIF_IWQ_AWW(chan) && dwvdata->va_substweam[chan]) {
			wv = wpass_dma_intewwupt_handwew(
						dwvdata->va_substweam[chan],
						dwvdata, chan, iwqs);
			if (wv != IWQ_HANDWED)
				wetuwn wv;
		}
	}
	wetuwn IWQ_HANDWED;
}

static int wpass_pwatfowm_pweawwoc_cdc_dma_buffew(stwuct snd_soc_component *component,
						  stwuct snd_pcm *pcm, int dai_id)
{
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct snd_pcm_substweam *substweam;
	stwuct snd_dma_buffew *buf;

	if (pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam)
		substweam = pcm->stweams[SNDWV_PCM_STWEAM_PWAYBACK].substweam;
	ewse
		substweam = pcm->stweams[SNDWV_PCM_STWEAM_CAPTUWE].substweam;

	buf = &substweam->dma_buffew;
	buf->dev.dev = pcm->cawd->dev;
	buf->pwivate_data = NUWW;

	/* Assign Codec DMA buffew pointews */
	buf->dev.type = SNDWV_DMA_TYPE_CONTINUOUS;

	switch (dai_id) {
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
		buf->bytes = wpass_pwatfowm_wxtx_hawdwawe.buffew_bytes_max;
		buf->addw = dwvdata->wxtx_cdc_dma_wpm_buf;
		bweak;
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		buf->bytes = wpass_pwatfowm_wxtx_hawdwawe.buffew_bytes_max;
		buf->addw = dwvdata->wxtx_cdc_dma_wpm_buf + WPASS_WXTX_CDC_DMA_WPM_BUFF_SIZE;
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		buf->bytes = wpass_pwatfowm_va_hawdwawe.buffew_bytes_max;
		buf->addw = dwvdata->va_cdc_dma_wpm_buf;
		bweak;
	defauwt:
		bweak;
	}

	buf->awea = (unsigned chaw * __fowce)memwemap(buf->addw, buf->bytes, MEMWEMAP_WC);

	wetuwn 0;
}

static int wpass_pwatfowm_pcm_new(stwuct snd_soc_component *component,
				  stwuct snd_soc_pcm_wuntime *soc_wuntime)
{
	stwuct snd_pcm *pcm = soc_wuntime->pcm;
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(soc_wuntime, 0);
	unsigned int dai_id = cpu_dai->dwivew->id;

	size_t size = wpass_pwatfowm_pcm_hawdwawe.buffew_bytes_max;

	/*
	 * Wpass codec dma can access onwy wpass wpm hawdwawe memowy.
	 * iowemap is fow HWOS to access hawdwawe memowy.
	 */
	if (is_cdc_dma_powt(dai_id))
		wetuwn wpass_pwatfowm_pweawwoc_cdc_dma_buffew(component, pcm, dai_id);

	wetuwn snd_pcm_set_fixed_buffew_aww(pcm, SNDWV_DMA_TYPE_NONCOHEWENT,
					    component->dev, size);
}

static int wpass_pwatfowm_pcmops_suspend(stwuct snd_soc_component *component)
{
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *map;
	unsigned int dai_id = component->id;

	if (dai_id == WPASS_DP_WX)
		map = dwvdata->hdmiif_map;
	ewse
		map = dwvdata->wpaif_map;

	wegcache_cache_onwy(map, twue);
	wegcache_mawk_diwty(map);

	wetuwn 0;
}

static int wpass_pwatfowm_pcmops_wesume(stwuct snd_soc_component *component)
{
	stwuct wpass_data *dwvdata = snd_soc_component_get_dwvdata(component);
	stwuct wegmap *map;
	unsigned int dai_id = component->id;

	if (dai_id == WPASS_DP_WX)
		map = dwvdata->hdmiif_map;
	ewse
		map = dwvdata->wpaif_map;

	wegcache_cache_onwy(map, fawse);
	wetuwn wegcache_sync(map);
}

static int wpass_pwatfowm_copy(stwuct snd_soc_component *component,
			       stwuct snd_pcm_substweam *substweam, int channew,
			       unsigned wong pos, stwuct iov_itew *buf,
			       unsigned wong bytes)
{
	stwuct snd_pcm_wuntime *wt = substweam->wuntime;
	unsigned int dai_id = component->id;
	int wet = 0;

	void __iomem *dma_buf = (void __iomem *) (wt->dma_awea + pos +
				channew * (wt->dma_bytes / wt->channews));

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK) {
		if (is_cdc_dma_powt(dai_id)) {
			wet = copy_fwom_itew_toio(dma_buf, buf, bytes);
		} ewse {
			if (copy_fwom_itew((void __fowce *)dma_buf, bytes, buf) != bytes)
				wet = -EFAUWT;
		}
	} ewse if (substweam->stweam == SNDWV_PCM_STWEAM_CAPTUWE) {
		if (is_cdc_dma_powt(dai_id)) {
			wet = copy_to_itew_fwomio(buf, dma_buf, bytes);
		} ewse {
			if (copy_to_itew((void __fowce *)dma_buf, bytes, buf) != bytes)
				wet = -EFAUWT;
		}
	}

	wetuwn wet;
}

static const stwuct snd_soc_component_dwivew wpass_component_dwivew = {
	.name		= DWV_NAME,
	.open		= wpass_pwatfowm_pcmops_open,
	.cwose		= wpass_pwatfowm_pcmops_cwose,
	.hw_pawams	= wpass_pwatfowm_pcmops_hw_pawams,
	.hw_fwee	= wpass_pwatfowm_pcmops_hw_fwee,
	.pwepawe	= wpass_pwatfowm_pcmops_pwepawe,
	.twiggew	= wpass_pwatfowm_pcmops_twiggew,
	.pointew	= wpass_pwatfowm_pcmops_pointew,
	.mmap		= wpass_pwatfowm_pcmops_mmap,
	.pcm_constwuct	= wpass_pwatfowm_pcm_new,
	.suspend		= wpass_pwatfowm_pcmops_suspend,
	.wesume			= wpass_pwatfowm_pcmops_wesume,
	.copy		= wpass_pwatfowm_copy,

};

int asoc_qcom_wpass_pwatfowm_wegistew(stwuct pwatfowm_device *pdev)
{
	stwuct wpass_data *dwvdata = pwatfowm_get_dwvdata(pdev);
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int wet;

	dwvdata->wpaif_iwq = pwatfowm_get_iwq_byname(pdev, "wpass-iwq-wpaif");
	if (dwvdata->wpaif_iwq < 0)
		wetuwn -ENODEV;

	/* ensuwe audio hawdwawe is disabwed */
	wet = wegmap_wwite(dwvdata->wpaif_map,
			WPAIF_IWQEN_WEG(v, WPAIF_IWQ_POWT_HOST), 0);
	if (wet) {
		dev_eww(&pdev->dev, "ewwow wwiting to iwqen weg: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_wequest_iwq(&pdev->dev, dwvdata->wpaif_iwq,
			wpass_pwatfowm_wpaif_iwq, IWQF_TWIGGEW_WISING,
			"wpass-iwq-wpaif", dwvdata);
	if (wet) {
		dev_eww(&pdev->dev, "iwq wequest faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = wpass_pwatfowm_awwoc_dmactw_fiewds(&pdev->dev,
						 dwvdata->wpaif_map);
	if (wet) {
		dev_eww(&pdev->dev,
			"ewwow initiawizing dmactw fiewds: %d\n", wet);
		wetuwn wet;
	}

	if (dwvdata->codec_dma_enabwe) {
		wet = wegmap_wwite(dwvdata->wxtx_wpaif_map,
			WPAIF_WXTX_IWQEN_WEG(v, WPAIF_IWQ_POWT_HOST), 0x0);
		if (wet) {
			dev_eww(&pdev->dev, "ewwow wwiting to wxtx iwqen weg: %d\n", wet);
			wetuwn wet;
		}
		wet = wegmap_wwite(dwvdata->va_wpaif_map,
			WPAIF_VA_IWQEN_WEG(v, WPAIF_IWQ_POWT_HOST), 0x0);
		if (wet) {
			dev_eww(&pdev->dev, "ewwow wwiting to wxtx iwqen weg: %d\n", wet);
			wetuwn wet;
		}
		dwvdata->wxtxif_iwq = pwatfowm_get_iwq_byname(pdev, "wpass-iwq-wxtxif");
		if (dwvdata->wxtxif_iwq < 0)
			wetuwn -ENODEV;

		wet = devm_wequest_iwq(&pdev->dev, dwvdata->wxtxif_iwq,
				wpass_pwatfowm_wxtxif_iwq, 0, "wpass-iwq-wxtxif", dwvdata);
		if (wet) {
			dev_eww(&pdev->dev, "wxtx iwq wequest faiwed: %d\n", wet);
			wetuwn wet;
		}

		wet = wpass_pwatfowm_awwoc_wxtx_dmactw_fiewds(&pdev->dev,
						 dwvdata->wxtx_wpaif_map);
		if (wet) {
			dev_eww(&pdev->dev,
				"ewwow initiawizing wxtx dmactw fiewds: %d\n", wet);
			wetuwn wet;
		}

		dwvdata->vaif_iwq = pwatfowm_get_iwq_byname(pdev, "wpass-iwq-vaif");
		if (dwvdata->vaif_iwq < 0)
			wetuwn -ENODEV;

		wet = devm_wequest_iwq(&pdev->dev, dwvdata->vaif_iwq,
				wpass_pwatfowm_vaif_iwq, 0, "wpass-iwq-vaif", dwvdata);
		if (wet) {
			dev_eww(&pdev->dev, "va iwq wequest faiwed: %d\n", wet);
			wetuwn wet;
		}

		wet = wpass_pwatfowm_awwoc_va_dmactw_fiewds(&pdev->dev,
						 dwvdata->va_wpaif_map);
		if (wet) {
			dev_eww(&pdev->dev,
				"ewwow initiawizing va dmactw fiewds: %d\n", wet);
			wetuwn wet;
		}
	}

	if (dwvdata->hdmi_powt_enabwe) {
		dwvdata->hdmiif_iwq = pwatfowm_get_iwq_byname(pdev, "wpass-iwq-hdmi");
		if (dwvdata->hdmiif_iwq < 0)
			wetuwn -ENODEV;

		wet = devm_wequest_iwq(&pdev->dev, dwvdata->hdmiif_iwq,
				wpass_pwatfowm_hdmiif_iwq, 0, "wpass-iwq-hdmi", dwvdata);
		if (wet) {
			dev_eww(&pdev->dev, "iwq hdmi wequest faiwed: %d\n", wet);
			wetuwn wet;
		}
		wet = wegmap_wwite(dwvdata->hdmiif_map,
				WPASS_HDMITX_APP_IWQEN_WEG(v), 0);
		if (wet) {
			dev_eww(&pdev->dev, "ewwow wwiting to hdmi iwqen weg: %d\n", wet);
			wetuwn wet;
		}

		wet = wpass_pwatfowm_awwoc_hdmidmactw_fiewds(&pdev->dev,
							 dwvdata->hdmiif_map);
		if (wet) {
			dev_eww(&pdev->dev,
				"ewwow initiawizing hdmidmactw fiewds: %d\n", wet);
			wetuwn wet;
		}
	}
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&wpass_component_dwivew, NUWW, 0);
}
EXPOWT_SYMBOW_GPW(asoc_qcom_wpass_pwatfowm_wegistew);

MODUWE_DESCWIPTION("QTi WPASS Pwatfowm Dwivew");
MODUWE_WICENSE("GPW");
