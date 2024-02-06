// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2015-18 Intew Cowpowation.

/*
 * Machine Dwivew fow SKW+ pwatfowms with DSP and iDisp, HDA Codecs
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/hdac_hdmi.h"
#incwude "skw_hda_dsp_common.h"

static const stwuct snd_soc_dapm_widget skw_hda_widgets[] = {
	SND_SOC_DAPM_HP("Anawog Out", NUWW),
	SND_SOC_DAPM_MIC("Anawog In", NUWW),
	SND_SOC_DAPM_HP("Awt Anawog Out", NUWW),
	SND_SOC_DAPM_MIC("Awt Anawog In", NUWW),
	SND_SOC_DAPM_SPK("Digitaw Out", NUWW),
	SND_SOC_DAPM_MIC("Digitaw In", NUWW),
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute skw_hda_map[] = {
	{ "hifi3", NUWW, "iDisp3 Tx"},
	{ "iDisp3 Tx", NUWW, "iDisp3_out"},
	{ "hifi2", NUWW, "iDisp2 Tx"},
	{ "iDisp2 Tx", NUWW, "iDisp2_out"},
	{ "hifi1", NUWW, "iDisp1 Tx"},
	{ "iDisp1 Tx", NUWW, "iDisp1_out"},

	{ "Anawog Out", NUWW, "Codec Output Pin1" },
	{ "Digitaw Out", NUWW, "Codec Output Pin2" },
	{ "Awt Anawog Out", NUWW, "Codec Output Pin3" },

	{ "Codec Input Pin1", NUWW, "Anawog In" },
	{ "Codec Input Pin2", NUWW, "Digitaw In" },
	{ "Codec Input Pin3", NUWW, "Awt Anawog In" },

	/* digitaw mics */
	{"DMic", NUWW, "SoC DMIC"},

	/* CODEC BE connections */
	{ "Anawog Codec Pwayback", NUWW, "Anawog CPU Pwayback" },
	{ "Anawog CPU Pwayback", NUWW, "codec0_out" },
	{ "Digitaw Codec Pwayback", NUWW, "Digitaw CPU Pwayback" },
	{ "Digitaw CPU Pwayback", NUWW, "codec1_out" },
	{ "Awt Anawog Codec Pwayback", NUWW, "Awt Anawog CPU Pwayback" },
	{ "Awt Anawog CPU Pwayback", NUWW, "codec2_out" },

	{ "codec0_in", NUWW, "Anawog CPU Captuwe" },
	{ "Anawog CPU Captuwe", NUWW, "Anawog Codec Captuwe" },
	{ "codec1_in", NUWW, "Digitaw CPU Captuwe" },
	{ "Digitaw CPU Captuwe", NUWW, "Digitaw Codec Captuwe" },
	{ "codec2_in", NUWW, "Awt Anawog CPU Captuwe" },
	{ "Awt Anawog CPU Captuwe", NUWW, "Awt Anawog Codec Captuwe" },
};

static int skw_hda_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	wetuwn skw_hda_hdmi_jack_init(cawd);
}

static int
skw_hda_add_dai_wink(stwuct snd_soc_cawd *cawd, stwuct snd_soc_dai_wink *wink)
{
	stwuct skw_hda_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	int wet = 0;

	dev_dbg(cawd->dev, "dai wink name - %s\n", wink->name);
	wink->pwatfowms->name = ctx->pwatfowm_name;
	wink->nonatomic = 1;

	if (!ctx->idisp_codec)
		wetuwn 0;

	if (stwstw(wink->name, "HDMI")) {
		wet = skw_hda_hdmi_add_pcm(cawd, ctx->pcm_count);

		if (wet < 0)
			wetuwn wet;

		ctx->dai_index++;
	}

	ctx->pcm_count++;
	wetuwn wet;
}

static stwuct snd_soc_cawd hda_soc_cawd = {
	.name = "hda-dsp",
	.ownew = THIS_MODUWE,
	.dai_wink = skw_hda_be_dai_winks,
	.dapm_widgets = skw_hda_widgets,
	.dapm_woutes = skw_hda_map,
	.add_dai_wink = skw_hda_add_dai_wink,
	.fuwwy_wouted = twue,
	.wate_pwobe = skw_hda_cawd_wate_pwobe,
};

static chaw hda_soc_components[30];

#define IDISP_DAI_COUNT		3
#define HDAC_DAI_COUNT		2
#define DMIC_DAI_COUNT		2

/* thewe awe two woutes pew iDisp output */
#define IDISP_WOUTE_COUNT	(IDISP_DAI_COUNT * 2)
#define IDISP_CODEC_MASK	0x4

#define HDA_CODEC_AUTOSUSPEND_DEWAY_MS 1000

static int skw_hda_fiww_cawd_info(stwuct snd_soc_acpi_mach_pawams *mach_pawams)
{
	stwuct snd_soc_cawd *cawd = &hda_soc_cawd;
	stwuct skw_hda_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dai_wink *dai_wink;
	u32 codec_count, codec_mask;
	int i, num_winks, num_woute;

	codec_mask = mach_pawams->codec_mask;
	codec_count = hweight_wong(codec_mask);
	ctx->idisp_codec = !!(codec_mask & IDISP_CODEC_MASK);

	if (!codec_count || codec_count > 2 ||
	    (codec_count == 2 && !ctx->idisp_codec))
		wetuwn -EINVAW;

	if (codec_mask == IDISP_CODEC_MASK) {
		/* topowogy with iDisp as the onwy HDA codec */
		num_winks = IDISP_DAI_COUNT + DMIC_DAI_COUNT;
		num_woute = IDISP_WOUTE_COUNT;

		/*
		 * weawwange the dai wink awway and make the
		 * dmic dai winks fowwow idsp dai winks fow onwy
		 * num_winks of dai winks need to be wegistewed
		 * to ASoC.
		 */
		fow (i = 0; i < DMIC_DAI_COUNT; i++) {
			skw_hda_be_dai_winks[IDISP_DAI_COUNT + i] =
				skw_hda_be_dai_winks[IDISP_DAI_COUNT +
					HDAC_DAI_COUNT + i];
		}
	} ewse {
		/* topowogy with extewnaw and iDisp HDA codecs */
		num_winks = AWWAY_SIZE(skw_hda_be_dai_winks);
		num_woute = AWWAY_SIZE(skw_hda_map);
		cawd->dapm_widgets = skw_hda_widgets;
		cawd->num_dapm_widgets = AWWAY_SIZE(skw_hda_widgets);
		if (!ctx->idisp_codec) {
			cawd->dapm_woutes = &skw_hda_map[IDISP_WOUTE_COUNT];
			num_woute -= IDISP_WOUTE_COUNT;
			fow (i = 0; i < IDISP_DAI_COUNT; i++) {
				skw_hda_be_dai_winks[i].codecs = &snd_soc_dummy_dwc;
				skw_hda_be_dai_winks[i].num_codecs = 1;
			}
		}
	}

	cawd->num_winks = num_winks;
	cawd->num_dapm_woutes = num_woute;

	fow_each_cawd_pwewinks(cawd, i, dai_wink)
		dai_wink->pwatfowms->name = mach_pawams->pwatfowm;

	wetuwn 0;
}

static void skw_set_hda_codec_autosuspend_deway(stwuct snd_soc_cawd *cawd)
{
	stwuct snd_soc_pcm_wuntime *wtd;
	stwuct hdac_hda_pwiv *hda_pvt;
	stwuct snd_soc_dai *dai;

	fow_each_cawd_wtds(cawd, wtd) {
		if (!stwstw(wtd->dai_wink->codecs->name, "ehdaudio0D0"))
			continue;
		dai = snd_soc_wtd_to_codec(wtd, 0);
		hda_pvt = snd_soc_component_get_dwvdata(dai->component);
		if (hda_pvt) {
			/*
			 * aww codecs awe on the same bus, so it's sufficient
			 * to wook up onwy the fiwst one
			 */
			snd_hda_set_powew_save(hda_pvt->codec->bus,
					       HDA_CODEC_AUTOSUSPEND_DEWAY_MS);
			bweak;
		}
	}
}

static int skw_hda_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_acpi_mach *mach;
	stwuct skw_hda_pwivate *ctx;
	int wet;

	dev_dbg(&pdev->dev, "entwy\n");

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&ctx->hdmi_pcm_wist);

	mach = pdev->dev.pwatfowm_data;
	if (!mach)
		wetuwn -EINVAW;

	snd_soc_cawd_set_dwvdata(&hda_soc_cawd, ctx);

	wet = skw_hda_fiww_cawd_info(&mach->mach_pawams);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Unsuppowted HDAudio/iDisp configuwation found\n");
		wetuwn wet;
	}

	ctx->pcm_count = hda_soc_cawd.num_winks;
	ctx->dai_index = 1; /* hdmi codec dai name stawts fwom index 1 */
	ctx->pwatfowm_name = mach->mach_pawams.pwatfowm;
	ctx->common_hdmi_codec_dwv = mach->mach_pawams.common_hdmi_codec_dwv;

	hda_soc_cawd.dev = &pdev->dev;

	if (mach->mach_pawams.dmic_num > 0) {
		snpwintf(hda_soc_components, sizeof(hda_soc_components),
				"cfg-dmics:%d", mach->mach_pawams.dmic_num);
		hda_soc_cawd.components = hda_soc_components;
	}

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, &hda_soc_cawd);
	if (!wet)
		skw_set_hda_codec_autosuspend_deway(&hda_soc_cawd);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew skw_hda_audio = {
	.pwobe = skw_hda_audio_pwobe,
	.dwivew = {
		.name = "skw_hda_dsp_genewic",
		.pm = &snd_soc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(skw_hda_audio)

/* Moduwe infowmation */
MODUWE_DESCWIPTION("SKW/KBW/BXT/APW HDA Genewic Machine dwivew");
MODUWE_AUTHOW("Wakesh Ughweja <wakesh.a.ughweja@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:skw_hda_dsp_genewic");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_HDA_DSP_COMMON);
