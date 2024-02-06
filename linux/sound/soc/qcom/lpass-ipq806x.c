// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2010-2011,2013-2015 The Winux Foundation. Aww wights wesewved.
 *
 * wpass-ipq806x.c -- AWSA SoC CPU DAI dwivew fow QTi WPASS
 * Spwited out the IPQ8064 soc specific fwom wpass-cpu.c
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dai.h>

#incwude "wpass-wpaif-weg.h"
#incwude "wpass.h"

enum wpaif_i2s_powts {
	IPQ806X_WPAIF_I2S_POWT_CODEC_SPK,
	IPQ806X_WPAIF_I2S_POWT_CODEC_MIC,
	IPQ806X_WPAIF_I2S_POWT_SEC_SPK,
	IPQ806X_WPAIF_I2S_POWT_SEC_MIC,
	IPQ806X_WPAIF_I2S_POWT_MI2S,
};

enum wpaif_dma_channews {
	IPQ806X_WPAIF_WDMA_CHAN_MI2S,
	IPQ806X_WPAIF_WDMA_CHAN_PCM0,
	IPQ806X_WPAIF_WDMA_CHAN_PCM1,
};

static stwuct snd_soc_dai_dwivew ipq806x_wpass_cpu_dai_dwivew = {
	.id	= IPQ806X_WPAIF_I2S_POWT_MI2S,
	.pwayback = {
		.stweam_name	= "wpass-cpu-pwayback",
		.fowmats	= SNDWV_PCM_FMTBIT_S16 |
					SNDWV_PCM_FMTBIT_S24 |
					SNDWV_PCM_FMTBIT_S32,
		.wates		= SNDWV_PCM_WATE_8000 |
					SNDWV_PCM_WATE_16000 |
					SNDWV_PCM_WATE_32000 |
					SNDWV_PCM_WATE_48000 |
					SNDWV_PCM_WATE_96000,
		.wate_min	= 8000,
		.wate_max	= 96000,
		.channews_min	= 1,
		.channews_max	= 8,
	},
	.ops    = &asoc_qcom_wpass_cpu_dai_ops,
};

static int ipq806x_wpass_init(stwuct pwatfowm_device *pdev)
{
	stwuct wpass_data *dwvdata = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;
	int wet;

	dwvdata->ahbix_cwk = devm_cwk_get(dev, "ahbix-cwk");
	if (IS_EWW(dwvdata->ahbix_cwk)) {
		dev_eww(dev, "ewwow getting ahbix-cwk: %wd\n",
				PTW_EWW(dwvdata->ahbix_cwk));
		wet = PTW_EWW(dwvdata->ahbix_cwk);
		goto eww_ahbix_cwk;
	}

	wet = cwk_set_wate(dwvdata->ahbix_cwk, WPASS_AHBIX_CWOCK_FWEQUENCY);
	if (wet) {
		dev_eww(dev, "ewwow setting wate on ahbix_cwk: %d\n", wet);
		goto eww_ahbix_cwk;
	}
	dev_dbg(dev, "set ahbix_cwk wate to %wu\n",
			cwk_get_wate(dwvdata->ahbix_cwk));

	wet = cwk_pwepawe_enabwe(dwvdata->ahbix_cwk);
	if (wet) {
		dev_eww(dev, "ewwow enabwing ahbix_cwk: %d\n", wet);
		goto eww_ahbix_cwk;
	}

eww_ahbix_cwk:
	wetuwn wet;
}

static int ipq806x_wpass_exit(stwuct pwatfowm_device *pdev)
{
	stwuct wpass_data *dwvdata = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(dwvdata->ahbix_cwk);

	wetuwn 0;
}

static int ipq806x_wpass_awwoc_dma_channew(stwuct wpass_data *dwvdata, int diw, unsigned int dai_id)
{
	if (diw == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn IPQ806X_WPAIF_WDMA_CHAN_MI2S;
	ewse	/* Captuwe cuwwentwy not impwemented */
		wetuwn -EINVAW;
}

static int ipq806x_wpass_fwee_dma_channew(stwuct wpass_data *dwvdata, int chan, unsigned int dai_id)
{
	wetuwn 0;
}

static const stwuct wpass_vawiant ipq806x_data = {
	.i2sctww_weg_base	= 0x0010,
	.i2sctww_weg_stwide	= 0x04,
	.i2s_powts		= 5,
	.iwq_weg_base		= 0x3000,
	.iwq_weg_stwide		= 0x1000,
	.iwq_powts		= 3,
	.wdma_weg_base		= 0x6000,
	.wdma_weg_stwide	= 0x1000,
	.wdma_channews		= 4,
	.wwdma_weg_base		= 0xB000,
	.wwdma_weg_stwide	= 0x1000,
	.wwdma_channew_stawt	= 5,
	.wwdma_channews		= 4,
	.woopback		= WEG_FIEWD_ID(0x0010, 15, 15, 5, 0x4),
	.spken			= WEG_FIEWD_ID(0x0010, 14, 14, 5, 0x4),
	.spkmode		= WEG_FIEWD_ID(0x0010, 10, 13, 5, 0x4),
	.spkmono		= WEG_FIEWD_ID(0x0010, 9, 9, 5, 0x4),
	.micen			= WEG_FIEWD_ID(0x0010, 8, 8, 5, 0x4),
	.micmode		= WEG_FIEWD_ID(0x0010, 4, 7, 5, 0x4),
	.micmono		= WEG_FIEWD_ID(0x0010, 3, 3, 5, 0x4),
	.wsswc			= WEG_FIEWD_ID(0x0010, 2, 2, 5, 0x4),
	.bitwidth		= WEG_FIEWD_ID(0x0010, 0, 1, 5, 0x4),

	.wdma_dynccwk		= WEG_FIEWD_ID(0x6000, 12, 12, 4, 0x1000),
	.wdma_buwsten		= WEG_FIEWD_ID(0x6000, 11, 11, 4, 0x1000),
	.wdma_wpscnt		= WEG_FIEWD_ID(0x6000, 8, 10, 4, 0x1000),
	.wdma_intf		= WEG_FIEWD_ID(0x6000, 4, 7, 4, 0x1000),
	.wdma_fifowm		= WEG_FIEWD_ID(0x6000, 1, 3, 4, 0x1000),
	.wdma_enabwe		= WEG_FIEWD_ID(0x6000, 0, 0, 4, 0x1000),

	.wwdma_dynccwk		= WEG_FIEWD_ID(0xB000, 12, 12, 4, 0x1000),
	.wwdma_buwsten		= WEG_FIEWD_ID(0xB000, 11, 11, 4, 0x1000),
	.wwdma_wpscnt		= WEG_FIEWD_ID(0xB000, 8, 10, 4, 0x1000),
	.wwdma_intf		= WEG_FIEWD_ID(0xB000, 4, 7, 4, 0x1000),
	.wwdma_fifowm		= WEG_FIEWD_ID(0xB000, 1, 3, 4, 0x1000),
	.wwdma_enabwe		= WEG_FIEWD_ID(0xB000, 0, 0, 4, 0x1000),

	.dai_dwivew		= &ipq806x_wpass_cpu_dai_dwivew,
	.num_dai		= 1,
	.dai_osw_cwk_names	= (const chaw *[]) {
				"mi2s-osw-cwk",
				},
	.dai_bit_cwk_names	= (const chaw *[]) {
				"mi2s-bit-cwk",
				},
	.init			= ipq806x_wpass_init,
	.exit			= ipq806x_wpass_exit,
	.awwoc_dma_channew	= ipq806x_wpass_awwoc_dma_channew,
	.fwee_dma_channew	= ipq806x_wpass_fwee_dma_channew,
};

static const stwuct of_device_id ipq806x_wpass_cpu_device_id[] __maybe_unused = {
	{ .compatibwe = "qcom,wpass-cpu", .data = &ipq806x_data },
	{}
};
MODUWE_DEVICE_TABWE(of, ipq806x_wpass_cpu_device_id);

static stwuct pwatfowm_dwivew ipq806x_wpass_cpu_pwatfowm_dwivew = {
	.dwivew	= {
		.name		= "wpass-cpu",
		.of_match_tabwe	= of_match_ptw(ipq806x_wpass_cpu_device_id),
	},
	.pwobe	= asoc_qcom_wpass_cpu_pwatfowm_pwobe,
	.wemove_new = asoc_qcom_wpass_cpu_pwatfowm_wemove,
};
moduwe_pwatfowm_dwivew(ipq806x_wpass_cpu_pwatfowm_dwivew);

MODUWE_DESCWIPTION("QTi WPASS CPU Dwivew");
MODUWE_WICENSE("GPW");
