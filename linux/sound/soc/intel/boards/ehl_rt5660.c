// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (c) 2020 Intew Cowpowation

/*
 * ehw_wt5660 - ASOC Machine dwivew fow Ewkhawt Wake pwatfowms
 * with wt5660 codec
 */

#incwude <winux/acpi.h>
#incwude <sound/cowe.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/gfp.h>
#incwude <sound/jack.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>

#incwude "hda_dsp_common.h"
#incwude "../../codecs/wt5660.h"

#define DUAW_CHANNEW 2
#define HDMI_WINK_STAWT 3
#define HDMI_WINE_END 6
#define NAME_SIZE	32
#define IDISP_CODEC_MASK	0x4

stwuct sof_cawd_pwivate {
	stwuct wist_head hdmi_pcm_wist;
	boow idisp_codec;
};

static const stwuct snd_kcontwow_new wt5660_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Speakew"),
	/* Thewe awe two MICBIAS in wt5660, each fow one MIC */
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Headset Mic2"),
	SOC_DAPM_PIN_SWITCH("Wine Out"),
};

static const stwuct snd_soc_dapm_widget wt5660_widgets[] = {
	SND_SOC_DAPM_SPK("Speakew", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic2", NUWW),
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
	SND_SOC_DAPM_WINE("Wine Out", NUWW),
};

static const stwuct snd_soc_dapm_woute wt5660_map[] = {
	{"Speakew", NUWW, "SPO"},

	{"Headset Mic", NUWW, "MICBIAS1"},
	{"Headset Mic2", NUWW, "MICBIAS2"},

	{"IN1P", NUWW, "Headset Mic"},
	{"IN2P", NUWW, "Headset Mic2"},

	{"Wine Out", NUWW, "WOUTW"},
	{"Wine Out", NUWW, "WOUTW"},

	{"DMic", NUWW, "SoC DMIC"},
};

stwuct sof_hdmi_pcm {
	stwuct wist_head head;
	stwuct snd_soc_dai *codec_dai;
	int device;
};

static int hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct sof_hdmi_pcm *pcm;

	pcm = devm_kzawwoc(wtd->cawd->dev, sizeof(*pcm), GFP_KEWNEW);
	if (!pcm)
		wetuwn -ENOMEM;

	/* dai_wink id is 1:1 mapped to the PCM device */
	pcm->device = wtd->dai_wink->id;
	pcm->codec_dai = dai;

	wist_add_taiw(&pcm->head, &ctx->hdmi_pcm_wist);

	wetuwn 0;
}

static int cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct sof_hdmi_pcm *pcm;

	if (wist_empty(&ctx->hdmi_pcm_wist))
		wetuwn -ENOENT;

	if (!ctx->idisp_codec)
		wetuwn 0;

	pcm = wist_fiwst_entwy(&ctx->hdmi_pcm_wist, stwuct sof_hdmi_pcm, head);

	wetuwn hda_dsp_hdmi_buiwd_contwows(cawd, pcm->codec_dai->component);
}

static int wt5660_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int wet;

	wet = snd_soc_dai_set_syscwk(codec_dai,
				     WT5660_SCWK_S_PWW1,
				     pawams_wate(pawams) * 512,
				     SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(wtd->dev, "snd_soc_dai_set_syscwk eww = %d\n", wet);
		wetuwn wet;
	}

	wet = snd_soc_dai_set_pww(codec_dai, 0,
				  WT5660_PWW1_S_BCWK,
				  pawams_wate(pawams) * 50,
				  pawams_wate(pawams) * 512);
	if (wet < 0)
		dev_eww(codec_dai->dev, "can't set codec pww: %d\n", wet);

	wetuwn wet;
}

static stwuct snd_soc_ops wt5660_ops = {
	.hw_pawams = wt5660_hw_pawams,
};

SND_SOC_DAIWINK_DEF(ssp0_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("SSP0 Pin")));

SND_SOC_DAIWINK_DEF(wt5660_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-10EC5660:00", "wt5660-aif1")));

SND_SOC_DAIWINK_DEF(pwatfowm,
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("0000:00:1f.3")));

SND_SOC_DAIWINK_DEF(dmic_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("DMIC01 Pin")));
SND_SOC_DAIWINK_DEF(dmic_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("dmic-codec", "dmic-hifi")));
SND_SOC_DAIWINK_DEF(dmic16k,
	DAIWINK_COMP_AWWAY(COMP_CPU("DMIC16k Pin")));

SND_SOC_DAIWINK_DEF(idisp1_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAIWINK_DEF(idisp1_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi1")));

SND_SOC_DAIWINK_DEF(idisp2_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAIWINK_DEF(idisp2_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi2")));

SND_SOC_DAIWINK_DEF(idisp3_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAIWINK_DEF(idisp3_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi3")));

SND_SOC_DAIWINK_DEF(idisp4_pin,
	DAIWINK_COMP_AWWAY(COMP_CPU("iDisp4 Pin")));
SND_SOC_DAIWINK_DEF(idisp4_codec,
	DAIWINK_COMP_AWWAY(COMP_CODEC("ehdaudio0D2", "intew-hdmi-hifi4")));

static stwuct snd_soc_dai_wink ehw_wt5660_daiwink[] = {
	/* back ends */
	{
		.name = "SSP0-Codec",
		.id = 0,
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ops = &wt5660_ops,
		SND_SOC_DAIWINK_WEG(ssp0_pin, wt5660_codec, pwatfowm),
	},
	{
		.name = "dmic48k",
		.id = 1,
		.ignowe_suspend = 1,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic_pin, dmic_codec, pwatfowm),
	},
	{
		.name = "dmic16k",
		.id = 2,
		.ignowe_suspend = 1,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(dmic16k, dmic_codec, pwatfowm),
	},
	{
		.name = "iDisp1",
		.id = 5,
		.init = hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp1_pin, idisp1_codec, pwatfowm),
	},
	{
		.name = "iDisp2",
		.id = 6,
		.init = hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp2_pin, idisp2_codec, pwatfowm),
	},
	{
		.name = "iDisp3",
		.id = 7,
		.init = hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp3_pin, idisp3_codec, pwatfowm),
	},
	{
		.name = "iDisp4",
		.id = 8,
		.init = hdmi_init,
		.dpcm_pwayback = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(idisp4_pin, idisp4_codec, pwatfowm),
	},
};

/* SoC cawd */
static stwuct snd_soc_cawd snd_soc_cawd_ehw_wt5660 = {
	.name = "ehw-wt5660",
	.ownew = THIS_MODUWE,
	.dai_wink = ehw_wt5660_daiwink,
	.num_winks = AWWAY_SIZE(ehw_wt5660_daiwink),
	.dapm_widgets = wt5660_widgets,
	.num_dapm_widgets = AWWAY_SIZE(wt5660_widgets),
	.dapm_woutes = wt5660_map,
	.num_dapm_woutes = AWWAY_SIZE(wt5660_map),
	.contwows = wt5660_contwows,
	.num_contwows = AWWAY_SIZE(wt5660_contwows),
	.fuwwy_wouted = twue,
	.wate_pwobe = cawd_wate_pwobe,
};

/* If hdmi codec is not suppowted, switch to use dummy codec */
static void hdmi_wink_init(stwuct snd_soc_cawd *cawd,
			   stwuct sof_cawd_pwivate *ctx,
			   stwuct snd_soc_acpi_mach *mach)
{
	int i;

	if (mach->mach_pawams.common_hdmi_codec_dwv &&
	    (mach->mach_pawams.codec_mask & IDISP_CODEC_MASK)) {
		ctx->idisp_codec = twue;
		wetuwn;
	}

	/*
	 * if HDMI is not enabwed in kewnew config, ow
	 * hdmi codec is not suppowted
	 */
	fow (i = HDMI_WINK_STAWT; i <= HDMI_WINE_END; i++)
		cawd->dai_wink[i].codecs[0] = snd_soc_dummy_dwc;
}

static int snd_ehw_wt5660_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_acpi_mach *mach;
	stwuct snd_soc_cawd *cawd = &snd_soc_cawd_ehw_wt5660;
	stwuct sof_cawd_pwivate *ctx;
	int wet;

	cawd->dev = &pdev->dev;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&ctx->hdmi_pcm_wist);
	snd_soc_cawd_set_dwvdata(cawd, ctx);

	mach = pdev->dev.pwatfowm_data;
	wet = snd_soc_fixup_dai_winks_pwatfowm_name(cawd,
						    mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	hdmi_wink_init(cawd, ctx, mach);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
}

static const stwuct pwatfowm_device_id ehw_boawd_ids[] = {
	{ .name = "ehw_wt5660" },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, ehw_boawd_ids);

static stwuct pwatfowm_dwivew snd_ehw_wt5660_dwivew = {
	.dwivew = {
		.name = "ehw_wt5660",
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = snd_ehw_wt5660_pwobe,
	.id_tabwe = ehw_boawd_ids,
};

moduwe_pwatfowm_dwivew(snd_ehw_wt5660_dwivew);

MODUWE_DESCWIPTION("ASoC Intew(W) Ewkhawtwake + wt5660 Machine dwivew");
MODUWE_AUTHOW("wibin.yang@intew.com");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_HDA_DSP_COMMON);
