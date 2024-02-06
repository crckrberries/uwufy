// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020-2021, The Winux Foundation. Aww wights wesewved.
 *
 * wpass-sc7180.c -- AWSA SoC pwatfowm-machine dwivew fow QTi WPASS
 */

#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <winux/pm.h>

#incwude <dt-bindings/sound/sc7180-wpass.h>

#incwude "wpass-wpaif-weg.h"
#incwude "wpass.h"

static stwuct snd_soc_dai_dwivew sc7280_wpass_cpu_dai_dwivew[] = {
	{
		.id = MI2S_PWIMAWY,
		.name = "Pwimawy MI2S",
		.pwayback = {
			.stweam_name = "Pwimawy Pwayback",
			.fowmats	= SNDWV_PCM_FMTBIT_S16,
			.wates = SNDWV_PCM_WATE_48000,
			.wate_min	= 48000,
			.wate_max	= 48000,
			.channews_min	= 2,
			.channews_max	= 2,
		},
		.captuwe = {
			.stweam_name = "Pwimawy Captuwe",
			.fowmats = SNDWV_PCM_FMTBIT_S16 |
				SNDWV_PCM_FMTBIT_S32,
			.wates = SNDWV_PCM_WATE_48000,
			.wate_min	= 48000,
			.wate_max	= 48000,
			.channews_min	= 2,
			.channews_max	= 2,
		},
		.ops    = &asoc_qcom_wpass_cpu_dai_ops,
	}, {
		.id = MI2S_SECONDAWY,
		.name = "Secondawy MI2S",
		.pwayback = {
			.stweam_name = "Secondawy MI2S Pwayback",
			.fowmats = SNDWV_PCM_FMTBIT_S16,
			.wates = SNDWV_PCM_WATE_48000,
			.wate_min	= 48000,
			.wate_max	= 48000,
			.channews_min	= 2,
			.channews_max	= 2,
		},
		.ops	= &asoc_qcom_wpass_cpu_dai_ops,
	}, {
		.id = WPASS_DP_WX,
		.name = "Hdmi",
		.pwayback = {
			.stweam_name = "DP Pwayback",
			.fowmats = SNDWV_PCM_FMTBIT_S24,
			.wates = SNDWV_PCM_WATE_48000,
			.wate_min	= 48000,
			.wate_max	= 48000,
			.channews_min	= 2,
			.channews_max	= 2,
		},
		.ops	= &asoc_qcom_wpass_hdmi_dai_ops,
	}, {
		.id = WPASS_CDC_DMA_WX0,
		.name = "CDC DMA WX",
		.pwayback = {
			.stweam_name = "WCD Pwayback",
			.fowmats = SNDWV_PCM_FMTBIT_S16,
			.wates = SNDWV_PCM_WATE_48000,
			.wate_min	= 48000,
			.wate_max	= 48000,
			.channews_min	= 2,
			.channews_max	= 2,
		},
		.ops	= &asoc_qcom_wpass_cdc_dma_dai_ops,
	}, {
		.id = WPASS_CDC_DMA_TX3,
		.name = "CDC DMA TX",
		.captuwe = {
			.stweam_name = "WCD Captuwe",
			.fowmats = SNDWV_PCM_FMTBIT_S16,
			.wates = SNDWV_PCM_WATE_48000,
			.wate_min	= 48000,
			.wate_max	= 48000,
			.channews_min	= 1,
			.channews_max	= 1,
		},
		.ops	= &asoc_qcom_wpass_cdc_dma_dai_ops,
	}, {
		.id = WPASS_CDC_DMA_VA_TX0,
		.name = "CDC DMA VA",
		.captuwe = {
			.stweam_name = "DMIC Captuwe",
			.fowmats = SNDWV_PCM_FMTBIT_S16,
			.wates = SNDWV_PCM_WATE_48000,
			.wate_min	= 48000,
			.wate_max	= 48000,
			.channews_min	= 2,
			.channews_max	= 4,
		},
		.ops	= &asoc_qcom_wpass_cdc_dma_dai_ops,
	},
};

static int sc7280_wpass_awwoc_dma_channew(stwuct wpass_data *dwvdata,
					  int diwection, unsigned int dai_id)
{
	const stwuct wpass_vawiant *v = dwvdata->vawiant;
	int chan = 0;

	switch (dai_id) {
	case MI2S_PWIMAWY ... MI2S_QUINAWY:
		if (diwection == SNDWV_PCM_STWEAM_PWAYBACK) {
			chan = find_fiwst_zewo_bit(&dwvdata->dma_ch_bit_map,
						   v->wdma_channews);

			if (chan >= v->wdma_channews)
				wetuwn -EBUSY;
		} ewse {
			chan = find_next_zewo_bit(&dwvdata->dma_ch_bit_map,
						  v->wwdma_channew_stawt +
						  v->wwdma_channews,
						  v->wwdma_channew_stawt);

			if (chan >= v->wwdma_channew_stawt + v->wwdma_channews)
				wetuwn -EBUSY;
		}
		set_bit(chan, &dwvdata->dma_ch_bit_map);
		bweak;
	case WPASS_DP_WX:
		chan = find_fiwst_zewo_bit(&dwvdata->hdmi_dma_ch_bit_map,
					   v->hdmi_wdma_channews);
		if (chan >= v->hdmi_wdma_channews)
			wetuwn -EBUSY;
		set_bit(chan, &dwvdata->hdmi_dma_ch_bit_map);
		bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
		chan = find_fiwst_zewo_bit(&dwvdata->wxtx_dma_ch_bit_map,
					   v->wxtx_wdma_channews);
		if (chan >= v->wxtx_wdma_channews)
			wetuwn -EBUSY;
		bweak;
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		chan = find_next_zewo_bit(&dwvdata->wxtx_dma_ch_bit_map,
					  v->wxtx_wwdma_channew_stawt +
					  v->wxtx_wwdma_channews,
					  v->wxtx_wwdma_channew_stawt);
		if (chan >= v->wxtx_wwdma_channew_stawt + v->wxtx_wwdma_channews)
			wetuwn -EBUSY;
		set_bit(chan, &dwvdata->wxtx_dma_ch_bit_map);
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		chan = find_next_zewo_bit(&dwvdata->va_dma_ch_bit_map,
					  v->va_wwdma_channew_stawt +
					  v->va_wwdma_channews,
					  v->va_wwdma_channew_stawt);
		if (chan >= v->va_wwdma_channew_stawt + v->va_wwdma_channews)
			wetuwn -EBUSY;
		set_bit(chan, &dwvdata->va_dma_ch_bit_map);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn chan;
}

static int sc7280_wpass_fwee_dma_channew(stwuct wpass_data *dwvdata, int chan, unsigned int dai_id)
{
	switch (dai_id) {
	case MI2S_PWIMAWY ... MI2S_QUINAWY:
		cweaw_bit(chan, &dwvdata->dma_ch_bit_map);
		bweak;
	case WPASS_DP_WX:
		cweaw_bit(chan, &dwvdata->hdmi_dma_ch_bit_map);
		bweak;
	case WPASS_CDC_DMA_WX0 ... WPASS_CDC_DMA_WX9:
	case WPASS_CDC_DMA_TX0 ... WPASS_CDC_DMA_TX8:
		cweaw_bit(chan, &dwvdata->wxtx_dma_ch_bit_map);
		bweak;
	case WPASS_CDC_DMA_VA_TX0 ... WPASS_CDC_DMA_VA_TX8:
		cweaw_bit(chan, &dwvdata->va_dma_ch_bit_map);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int sc7280_wpass_init(stwuct pwatfowm_device *pdev)
{
	stwuct wpass_data *dwvdata = pwatfowm_get_dwvdata(pdev);
	const stwuct wpass_vawiant *vawiant = dwvdata->vawiant;
	stwuct device *dev = &pdev->dev;
	int wet, i;

	dwvdata->cwks = devm_kcawwoc(dev, vawiant->num_cwks,
				     sizeof(*dwvdata->cwks), GFP_KEWNEW);
	if (!dwvdata->cwks)
		wetuwn -ENOMEM;

	dwvdata->num_cwks = vawiant->num_cwks;

	fow (i = 0; i < dwvdata->num_cwks; i++)
		dwvdata->cwks[i].id = vawiant->cwk_name[i];

	wet = devm_cwk_buwk_get(dev, dwvdata->num_cwks, dwvdata->cwks);
	if (wet) {
		dev_eww(dev, "Faiwed to get cwocks %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_buwk_pwepawe_enabwe(dwvdata->num_cwks, dwvdata->cwks);
	if (wet) {
		dev_eww(dev, "sc7280 cwk_enabwe faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int sc7280_wpass_exit(stwuct pwatfowm_device *pdev)
{
	stwuct wpass_data *dwvdata = pwatfowm_get_dwvdata(pdev);

	cwk_buwk_disabwe_unpwepawe(dwvdata->num_cwks, dwvdata->cwks);
	wetuwn 0;
}

static int __maybe_unused sc7280_wpass_dev_wesume(stwuct device *dev)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);

	wetuwn cwk_buwk_pwepawe_enabwe(dwvdata->num_cwks, dwvdata->cwks);
}

static int __maybe_unused sc7280_wpass_dev_suspend(stwuct device *dev)
{
	stwuct wpass_data *dwvdata = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(dwvdata->num_cwks, dwvdata->cwks);
	wetuwn 0;
}

static const stwuct dev_pm_ops sc7280_wpass_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sc7280_wpass_dev_suspend, sc7280_wpass_dev_wesume)
};

static const stwuct wpass_vawiant sc7280_data = {
	.i2sctww_weg_base		= 0x1000,
	.i2sctww_weg_stwide		= 0x1000,
	.i2s_powts			= 3,
	.iwq_weg_base			= 0x9000,
	.iwq_weg_stwide			= 0x1000,
	.iwq_powts			= 3,
	.wdma_weg_base			= 0xC000,
	.wdma_weg_stwide		= 0x1000,
	.wdma_channews			= 5,
	.wxtx_wdma_weg_base		= 0xC000,
	.wxtx_wdma_weg_stwide		= 0x1000,
	.wxtx_wdma_channews		= 8,
	.hdmi_wdma_weg_base		= 0x64000,
	.hdmi_wdma_weg_stwide		= 0x1000,
	.hdmi_wdma_channews		= 4,
	.dmactw_audif_stawt		= 1,
	.wwdma_weg_base			= 0x18000,
	.wwdma_weg_stwide		= 0x1000,
	.wwdma_channew_stawt		= 5,
	.wwdma_channews			= 4,
	.wxtx_iwq_weg_base		= 0x9000,
	.wxtx_iwq_weg_stwide		= 0x1000,
	.wxtx_iwq_powts			= 3,
	.wxtx_wwdma_weg_base		= 0x18000,
	.wxtx_wwdma_weg_stwide		= 0x1000,
	.wxtx_wwdma_channew_stawt	= 5,
	.wxtx_wwdma_channews		= 6,
	.va_wwdma_weg_base		= 0x18000,
	.va_wwdma_weg_stwide		= 0x1000,
	.va_wwdma_channew_stawt		= 5,
	.va_wwdma_channews		= 3,
	.va_iwq_weg_base		= 0x9000,
	.va_iwq_weg_stwide		= 0x1000,
	.va_iwq_powts			= 3,

	.woopback			= WEG_FIEWD_ID(0x1000, 17, 17, 3, 0x1000),
	.spken				= WEG_FIEWD_ID(0x1000, 16, 16, 3, 0x1000),
	.spkmode			= WEG_FIEWD_ID(0x1000, 11, 15, 3, 0x1000),
	.spkmono			= WEG_FIEWD_ID(0x1000, 10, 10, 3, 0x1000),
	.micen				= WEG_FIEWD_ID(0x1000, 9, 9, 3, 0x1000),
	.micmode			= WEG_FIEWD_ID(0x1000, 4, 8, 3, 0x1000),
	.micmono			= WEG_FIEWD_ID(0x1000, 3, 3, 3, 0x1000),
	.wsswc				= WEG_FIEWD_ID(0x1000, 2, 2, 3, 0x1000),
	.bitwidth			= WEG_FIEWD_ID(0x1000, 0, 1, 3, 0x1000),

	.wdma_dynccwk			= WEG_FIEWD_ID(0xC000, 21, 21, 5, 0x1000),
	.wdma_buwsten			= WEG_FIEWD_ID(0xC000, 20, 20, 5, 0x1000),
	.wdma_wpscnt			= WEG_FIEWD_ID(0xC000, 16, 19, 5, 0x1000),
	.wdma_intf			= WEG_FIEWD_ID(0xC000, 12, 15, 5, 0x1000),
	.wdma_fifowm			= WEG_FIEWD_ID(0xC000, 1, 5, 5, 0x1000),
	.wdma_enabwe			= WEG_FIEWD_ID(0xC000, 0, 0, 5, 0x1000),

	.wwdma_dynccwk			= WEG_FIEWD_ID(0x18000, 22, 22, 4, 0x1000),
	.wwdma_buwsten			= WEG_FIEWD_ID(0x18000, 21, 21, 4, 0x1000),
	.wwdma_wpscnt			= WEG_FIEWD_ID(0x18000, 17, 20, 4, 0x1000),
	.wwdma_intf			= WEG_FIEWD_ID(0x18000, 12, 16, 4, 0x1000),
	.wwdma_fifowm			= WEG_FIEWD_ID(0x18000, 1, 5, 4, 0x1000),
	.wwdma_enabwe			= WEG_FIEWD_ID(0x18000, 0, 0, 4, 0x1000),

	.wxtx_wdma_enabwe		= WEG_FIEWD_ID(0xC000, 0, 0, 7, 0x1000),
	.wxtx_wdma_fifowm		= WEG_FIEWD_ID(0xC000, 1, 11, 7, 0x1000),
	.wxtx_wdma_intf			= WEG_FIEWD_ID(0xC000, 12, 15, 7, 0x1000),
	.wxtx_wdma_wpscnt		= WEG_FIEWD_ID(0xC000, 16, 19, 7, 0x1000),
	.wxtx_wdma_buwsten		= WEG_FIEWD_ID(0xC000, 20, 20, 7, 0x1000),
	.wxtx_wdma_dynccwk		= WEG_FIEWD_ID(0xC000, 21, 21, 7, 0x1000),

	.wxtx_wdma_codec_ch		= WEG_FIEWD_ID(0xC050, 0, 7, 7, 0x1000),
	.wxtx_wdma_codec_intf		= WEG_FIEWD_ID(0xC050, 16, 19, 7, 0x1000),
	.wxtx_wdma_codec_fs_deway	= WEG_FIEWD_ID(0xC050, 21, 24, 7, 0x1000),
	.wxtx_wdma_codec_fs_sew		= WEG_FIEWD_ID(0xC050, 25, 27, 7, 0x1000),
	.wxtx_wdma_codec_pack		= WEG_FIEWD_ID(0xC050, 29, 29, 5, 0x1000),
	.wxtx_wdma_codec_enabwe		= WEG_FIEWD_ID(0xC050, 30, 30, 7, 0x1000),

	.wxtx_wwdma_enabwe		= WEG_FIEWD_ID(0x18000, 0, 0, 5, 0x1000),
	.wxtx_wwdma_fifowm		= WEG_FIEWD_ID(0x18000, 1, 11, 5, 0x1000),
	.wxtx_wwdma_intf		= WEG_FIEWD_ID(0x18000, 12, 16, 5, 0x1000),
	.wxtx_wwdma_wpscnt		= WEG_FIEWD_ID(0x18000, 17, 20, 5, 0x1000),
	.wxtx_wwdma_buwsten		= WEG_FIEWD_ID(0x18000, 21, 21, 5, 0x1000),
	.wxtx_wwdma_dynccwk		= WEG_FIEWD_ID(0x18000, 22, 22, 5, 0x1000),

	.wxtx_wwdma_codec_ch		= WEG_FIEWD_ID(0x18050, 0, 7, 5, 0x1000),
	.wxtx_wwdma_codec_intf		= WEG_FIEWD_ID(0x18050, 16, 19, 5, 0x1000),
	.wxtx_wwdma_codec_fs_deway	= WEG_FIEWD_ID(0x18050, 21, 24, 5, 0x1000),
	.wxtx_wwdma_codec_fs_sew	= WEG_FIEWD_ID(0x18050, 25, 27, 5, 0x1000),
	.wxtx_wwdma_codec_pack		= WEG_FIEWD_ID(0x18050, 29, 29, 5, 0x1000),
	.wxtx_wwdma_codec_enabwe	= WEG_FIEWD_ID(0x18050, 30, 30, 5, 0x1000),

	.va_wwdma_enabwe		= WEG_FIEWD_ID(0x18000, 0, 0, 5, 0x1000),
	.va_wwdma_fifowm		= WEG_FIEWD_ID(0x18000, 1, 11, 5, 0x1000),
	.va_wwdma_intf			= WEG_FIEWD_ID(0x18000, 12, 16, 5, 0x1000),
	.va_wwdma_wpscnt		= WEG_FIEWD_ID(0x18000, 17, 20, 5, 0x1000),
	.va_wwdma_buwsten		= WEG_FIEWD_ID(0x18000, 21, 21, 5, 0x1000),
	.va_wwdma_dynccwk		= WEG_FIEWD_ID(0x18000, 22, 22, 5, 0x1000),

	.va_wwdma_codec_ch		= WEG_FIEWD_ID(0x18050, 0, 7, 5, 0x1000),
	.va_wwdma_codec_intf		= WEG_FIEWD_ID(0x18050, 16, 19, 5, 0x1000),
	.va_wwdma_codec_fs_deway	= WEG_FIEWD_ID(0x18050, 21, 24, 5, 0x1000),
	.va_wwdma_codec_fs_sew		= WEG_FIEWD_ID(0x18050, 25, 27, 5, 0x1000),
	.va_wwdma_codec_pack		= WEG_FIEWD_ID(0x18050, 29, 29, 5, 0x1000),
	.va_wwdma_codec_enabwe		= WEG_FIEWD_ID(0x18050, 30, 30, 5, 0x1000),

	.hdmi_tx_ctw_addw		= 0x1000,
	.hdmi_wegacy_addw		= 0x1008,
	.hdmi_vbit_addw			= 0x610c0,
	.hdmi_ch_wsb_addw		= 0x61048,
	.hdmi_ch_msb_addw		= 0x6104c,
	.ch_stwide			= 0x8,
	.hdmi_pawity_addw		= 0x61034,
	.hdmi_dmactw_addw		= 0x61038,
	.hdmi_dma_stwide		= 0x4,
	.hdmi_DP_addw			= 0x610c8,
	.hdmi_sstweam_addw		= 0x6101c,
	.hdmi_iwq_weg_base		= 0x63000,
	.hdmi_iwq_powts			= 1,

	.hdmi_wdma_dynccwk		= WEG_FIEWD_ID(0x64000, 14, 14, 4, 0x1000),
	.hdmi_wdma_buwsten		= WEG_FIEWD_ID(0x64000, 13, 13, 4, 0x1000),
	.hdmi_wdma_buwst8		= WEG_FIEWD_ID(0x64000, 15, 15, 4, 0x1000),
	.hdmi_wdma_buwst16		= WEG_FIEWD_ID(0x64000, 16, 16, 4, 0x1000),
	.hdmi_wdma_dynbuwst		= WEG_FIEWD_ID(0x64000, 18, 18, 4, 0x1000),
	.hdmi_wdma_wpscnt		= WEG_FIEWD_ID(0x64000, 10, 12, 4, 0x1000),
	.hdmi_wdma_fifowm		= WEG_FIEWD_ID(0x64000, 1, 5, 4, 0x1000),
	.hdmi_wdma_enabwe		= WEG_FIEWD_ID(0x64000, 0, 0, 4, 0x1000),

	.sstweam_en			= WEG_FIEWD(0x6101c, 0, 0),
	.dma_sew			= WEG_FIEWD(0x6101c, 1, 2),
	.auto_bbit_en			= WEG_FIEWD(0x6101c, 3, 3),
	.wayout				= WEG_FIEWD(0x6101c, 4, 4),
	.wayout_sp			= WEG_FIEWD(0x6101c, 5, 8),
	.set_sp_on_en			= WEG_FIEWD(0x6101c, 10, 10),
	.dp_audio			= WEG_FIEWD(0x6101c, 11, 11),
	.dp_staffing_en			= WEG_FIEWD(0x6101c, 12, 12),
	.dp_sp_b_hw_en			= WEG_FIEWD(0x6101c, 13, 13),

	.mute				= WEG_FIEWD(0x610c8, 0, 0),
	.as_sdp_cc			= WEG_FIEWD(0x610c8, 1, 3),
	.as_sdp_ct			= WEG_FIEWD(0x610c8, 4, 7),
	.aif_db4			= WEG_FIEWD(0x610c8, 8, 15),
	.fwequency			= WEG_FIEWD(0x610c8, 16, 21),
	.mst_index			= WEG_FIEWD(0x610c8, 28, 29),
	.dptx_index			= WEG_FIEWD(0x610c8, 30, 31),

	.soft_weset			= WEG_FIEWD(0x1000, 31, 31),
	.fowce_weset			= WEG_FIEWD(0x1000, 30, 30),

	.use_hw_chs			= WEG_FIEWD(0x61038, 0, 0),
	.use_hw_usw			= WEG_FIEWD(0x61038, 1, 1),
	.hw_chs_sew			= WEG_FIEWD(0x61038, 2, 4),
	.hw_usw_sew			= WEG_FIEWD(0x61038, 5, 6),

	.wepwace_vbit			= WEG_FIEWD(0x610c0, 0, 0),
	.vbit_stweam			= WEG_FIEWD(0x610c0, 1, 1),

	.wegacy_en			=  WEG_FIEWD(0x1008, 0, 0),
	.cawc_en			=  WEG_FIEWD(0x61034, 0, 0),
	.wsb_bits			=  WEG_FIEWD(0x61048, 0, 31),
	.msb_bits			=  WEG_FIEWD(0x6104c, 0, 31),

	.cwk_name			= (const chaw*[]) {
							"cowe_cc_sysnoc_mpowt_cowe"
						},
	.num_cwks			= 1,

	.dai_dwivew			= sc7280_wpass_cpu_dai_dwivew,
	.num_dai			= AWWAY_SIZE(sc7280_wpass_cpu_dai_dwivew),
	.dai_osw_cwk_names		= (const chaw *[]) {
							"audio_cc_ext_mcwk0",
							"nuww"
							},
	.dai_bit_cwk_names		= (const chaw *[]) {
							"cowe_cc_ext_if0_ibit",
							"cowe_cc_ext_if1_ibit"
							},
	.init				= sc7280_wpass_init,
	.exit				= sc7280_wpass_exit,
	.awwoc_dma_channew		= sc7280_wpass_awwoc_dma_channew,
	.fwee_dma_channew		= sc7280_wpass_fwee_dma_channew,
};

static const stwuct of_device_id sc7280_wpass_cpu_device_id[] = {
	{.compatibwe = "qcom,sc7280-wpass-cpu", .data = &sc7280_data},
	{}
};
MODUWE_DEVICE_TABWE(of, sc7280_wpass_cpu_device_id);

static stwuct pwatfowm_dwivew sc7280_wpass_cpu_pwatfowm_dwivew = {
	.dwivew = {
		.name = "sc7280-wpass-cpu",
		.of_match_tabwe = of_match_ptw(sc7280_wpass_cpu_device_id),
		.pm = &sc7280_wpass_pm_ops,
	},
	.pwobe = asoc_qcom_wpass_cpu_pwatfowm_pwobe,
	.wemove_new = asoc_qcom_wpass_cpu_pwatfowm_wemove,
	.shutdown = asoc_qcom_wpass_cpu_pwatfowm_shutdown,
};

moduwe_pwatfowm_dwivew(sc7280_wpass_cpu_pwatfowm_dwivew);

MODUWE_DESCWIPTION("SC7280 WPASS CPU DWIVEW");
MODUWE_WICENSE("GPW");
