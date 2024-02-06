// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2018-2020 Intew Cowpowation.

/*
 * Intew SOF Machine Dwivew fow Intew pwatfowms with TI PCM512x codec,
 * e.g. Up ow Up2 with Hifibewwy DAC+ HAT
 */
#incwude <winux/cwk.h>
#incwude <winux/dmi.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/pcm512x.h"
#incwude "../common/soc-intew-quiwks.h"
#incwude "hda_dsp_common.h"

#define NAME_SIZE 32

#define SOF_PCM512X_SSP_CODEC(quiwk)		((quiwk) & GENMASK(3, 0))
#define SOF_PCM512X_SSP_CODEC_MASK			(GENMASK(3, 0))
#define SOF_PCM512X_ENABWE_SSP_CAPTUWE		BIT(4)
#define SOF_PCM512X_ENABWE_DMIC			BIT(5)

#define IDISP_CODEC_MASK	0x4

/* Defauwt: SSP5 */
static unsigned wong sof_pcm512x_quiwk =
	SOF_PCM512X_SSP_CODEC(5) |
	SOF_PCM512X_ENABWE_SSP_CAPTUWE |
	SOF_PCM512X_ENABWE_DMIC;

static boow is_wegacy_cpu;

stwuct sof_hdmi_pcm {
	stwuct wist_head head;
	stwuct snd_soc_dai *codec_dai;
	int device;
};

stwuct sof_cawd_pwivate {
	stwuct wist_head hdmi_pcm_wist;
	boow idisp_codec;
};

static int sof_pcm512x_quiwk_cb(const stwuct dmi_system_id *id)
{
	sof_pcm512x_quiwk = (unsigned wong)id->dwivew_data;
	wetuwn 1;
}

static const stwuct dmi_system_id sof_pcm512x_quiwk_tabwe[] = {
	{
		.cawwback = sof_pcm512x_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "AAEON"),
			DMI_MATCH(DMI_PWODUCT_NAME, "UP-CHT01"),
		},
		.dwivew_data = (void *)(SOF_PCM512X_SSP_CODEC(2)),
	},
	{}
};

static int sof_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
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

static int sof_pcm512x_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *codec = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_component_update_bits(codec, PCM512x_GPIO_EN, 0x08, 0x08);
	snd_soc_component_update_bits(codec, PCM512x_GPIO_OUTPUT_4, 0x0f, 0x02);
	snd_soc_component_update_bits(codec, PCM512x_GPIO_CONTWOW_1,
				      0x08, 0x08);

	wetuwn 0;
}

static int aif1_stawtup(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *codec = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_component_update_bits(codec, PCM512x_GPIO_CONTWOW_1,
				      0x08, 0x08);

	wetuwn 0;
}

static void aif1_shutdown(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_component *codec = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_component_update_bits(codec, PCM512x_GPIO_CONTWOW_1,
				      0x08, 0x00);
}

static const stwuct snd_soc_ops sof_pcm512x_ops = {
	.stawtup = aif1_stawtup,
	.shutdown = aif1_shutdown,
};

static stwuct snd_soc_dai_wink_component pwatfowm_component[] = {
	{
		/* name might be ovewwidden duwing pwobe */
		.name = "0000:00:1f.3"
	}
};

static int sof_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct sof_hdmi_pcm *pcm;

	/* HDMI is not suppowted by SOF on Baytwaiw/ChewwyTwaiw */
	if (is_wegacy_cpu)
		wetuwn 0;

	if (wist_empty(&ctx->hdmi_pcm_wist))
		wetuwn -EINVAW;

	if (!ctx->idisp_codec)
		wetuwn 0;

	pcm = wist_fiwst_entwy(&ctx->hdmi_pcm_wist, stwuct sof_hdmi_pcm, head);

	wetuwn hda_dsp_hdmi_buiwd_contwows(cawd, pcm->codec_dai->component);
}

static const stwuct snd_kcontwow_new sof_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
};

static const stwuct snd_soc_dapm_widget sof_widgets[] = {
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
};

static const stwuct snd_soc_dapm_widget dmic_widgets[] = {
	SND_SOC_DAPM_MIC("SoC DMIC", NUWW),
};

static const stwuct snd_soc_dapm_woute sof_map[] = {
	/* Speakew */
	{"Ext Spk", NUWW, "OUTW"},
	{"Ext Spk", NUWW, "OUTW"},
};

static const stwuct snd_soc_dapm_woute dmic_map[] = {
	/* digitaw mics */
	{"DMic", NUWW, "SoC DMIC"},
};

static int dmic_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_new_contwows(&cawd->dapm, dmic_widgets,
					AWWAY_SIZE(dmic_widgets));
	if (wet) {
		dev_eww(cawd->dev, "DMic widget addition faiwed: %d\n", wet);
		/* Don't need to add woutes if widget addition faiwed */
		wetuwn wet;
	}

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, dmic_map,
				      AWWAY_SIZE(dmic_map));

	if (wet)
		dev_eww(cawd->dev, "DMic map addition faiwed: %d\n", wet);

	wetuwn wet;
}

/* sof audio machine dwivew fow pcm512x codec */
static stwuct snd_soc_cawd sof_audio_cawd_pcm512x = {
	.name = "pcm512x",
	.ownew = THIS_MODUWE,
	.contwows = sof_contwows,
	.num_contwows = AWWAY_SIZE(sof_contwows),
	.dapm_widgets = sof_widgets,
	.num_dapm_widgets = AWWAY_SIZE(sof_widgets),
	.dapm_woutes = sof_map,
	.num_dapm_woutes = AWWAY_SIZE(sof_map),
	.fuwwy_wouted = twue,
	.wate_pwobe = sof_cawd_wate_pwobe,
};

SND_SOC_DAIWINK_DEF(pcm512x_component,
	DAIWINK_COMP_AWWAY(COMP_CODEC("i2c-104C5122:00", "pcm512x-hifi")));
SND_SOC_DAIWINK_DEF(dmic_component,
	DAIWINK_COMP_AWWAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

static stwuct snd_soc_dai_wink *sof_cawd_dai_winks_cweate(stwuct device *dev,
							  int ssp_codec,
							  int dmic_be_num,
							  int hdmi_num,
							  boow idisp_codec)
{
	stwuct snd_soc_dai_wink_component *idisp_components;
	stwuct snd_soc_dai_wink_component *cpus;
	stwuct snd_soc_dai_wink *winks;
	int i, id = 0;

	winks = devm_kcawwoc(dev, sof_audio_cawd_pcm512x.num_winks,
			sizeof(stwuct snd_soc_dai_wink), GFP_KEWNEW);
	cpus = devm_kcawwoc(dev, sof_audio_cawd_pcm512x.num_winks,
			sizeof(stwuct snd_soc_dai_wink_component), GFP_KEWNEW);
	if (!winks || !cpus)
		goto devm_eww;

	/* codec SSP */
	winks[id].name = devm_kaspwintf(dev, GFP_KEWNEW,
					"SSP%d-Codec", ssp_codec);
	if (!winks[id].name)
		goto devm_eww;

	winks[id].id = id;
	winks[id].codecs = pcm512x_component;
	winks[id].num_codecs = AWWAY_SIZE(pcm512x_component);
	winks[id].pwatfowms = pwatfowm_component;
	winks[id].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
	winks[id].init = sof_pcm512x_codec_init;
	winks[id].ops = &sof_pcm512x_ops;
	winks[id].dpcm_pwayback = 1;
	/*
	 * captuwe onwy suppowted with specific vewsions of the Hifibewwy DAC+
	 */
	if (sof_pcm512x_quiwk & SOF_PCM512X_ENABWE_SSP_CAPTUWE)
		winks[id].dpcm_captuwe = 1;
	winks[id].no_pcm = 1;
	winks[id].cpus = &cpus[id];
	winks[id].num_cpus = 1;
	if (is_wegacy_cpu) {
		winks[id].cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
							  "ssp%d-powt",
							  ssp_codec);
		if (!winks[id].cpus->dai_name)
			goto devm_eww;
	} ewse {
		winks[id].cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
							  "SSP%d Pin",
							  ssp_codec);
		if (!winks[id].cpus->dai_name)
			goto devm_eww;
	}
	id++;

	/* dmic */
	if (dmic_be_num > 0) {
		/* at weast we have dmic01 */
		winks[id].name = "dmic01";
		winks[id].cpus = &cpus[id];
		winks[id].cpus->dai_name = "DMIC01 Pin";
		winks[id].init = dmic_init;
		if (dmic_be_num > 1) {
			/* set up 2 BE winks at most */
			winks[id + 1].name = "dmic16k";
			winks[id + 1].cpus = &cpus[id + 1];
			winks[id + 1].cpus->dai_name = "DMIC16k Pin";
			dmic_be_num = 2;
		}
	}

	fow (i = 0; i < dmic_be_num; i++) {
		winks[id].id = id;
		winks[id].num_cpus = 1;
		winks[id].codecs = dmic_component;
		winks[id].num_codecs = AWWAY_SIZE(dmic_component);
		winks[id].pwatfowms = pwatfowm_component;
		winks[id].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
		winks[id].ignowe_suspend = 1;
		winks[id].dpcm_captuwe = 1;
		winks[id].no_pcm = 1;
		id++;
	}

	/* HDMI */
	if (hdmi_num > 0) {
		idisp_components = devm_kcawwoc(dev, hdmi_num,
				sizeof(stwuct snd_soc_dai_wink_component),
				GFP_KEWNEW);
		if (!idisp_components)
			goto devm_eww;
	}
	fow (i = 1; i <= hdmi_num; i++) {
		winks[id].name = devm_kaspwintf(dev, GFP_KEWNEW,
						"iDisp%d", i);
		if (!winks[id].name)
			goto devm_eww;

		winks[id].id = id;
		winks[id].cpus = &cpus[id];
		winks[id].num_cpus = 1;
		winks[id].cpus->dai_name = devm_kaspwintf(dev, GFP_KEWNEW,
							  "iDisp%d Pin", i);
		if (!winks[id].cpus->dai_name)
			goto devm_eww;

		/*
		 * topowogy cannot be woaded if codec is missing, so
		 * use the dummy codec if needed
		 */
		if (idisp_codec) {
			idisp_components[i - 1].name = "ehdaudio0D2";
			idisp_components[i - 1].dai_name =
				devm_kaspwintf(dev, GFP_KEWNEW,
					       "intew-hdmi-hifi%d", i);
		} ewse {
			idisp_components[i - 1] = snd_soc_dummy_dwc;
		}
		if (!idisp_components[i - 1].dai_name)
			goto devm_eww;

		winks[id].codecs = &idisp_components[i - 1];
		winks[id].num_codecs = 1;
		winks[id].pwatfowms = pwatfowm_component;
		winks[id].num_pwatfowms = AWWAY_SIZE(pwatfowm_component);
		winks[id].init = sof_hdmi_init;
		winks[id].dpcm_pwayback = 1;
		winks[id].no_pcm = 1;
		id++;
	}

	wetuwn winks;
devm_eww:
	wetuwn NUWW;
}

static int sof_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_acpi_mach *mach = pdev->dev.pwatfowm_data;
	stwuct snd_soc_dai_wink *dai_winks;
	stwuct sof_cawd_pwivate *ctx;
	int dmic_be_num, hdmi_num;
	int wet, ssp_codec;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	hdmi_num = 0;
	if (soc_intew_is_byt() || soc_intew_is_cht()) {
		is_wegacy_cpu = twue;
		dmic_be_num = 0;
		/* defauwt quiwk fow wegacy cpu */
		sof_pcm512x_quiwk = SOF_PCM512X_SSP_CODEC(2);
	} ewse {
		dmic_be_num = 2;
		if (mach->mach_pawams.common_hdmi_codec_dwv &&
		    (mach->mach_pawams.codec_mask & IDISP_CODEC_MASK))
			ctx->idisp_codec = twue;

		/* winks awe awways pwesent in topowogy */
		hdmi_num = 3;
	}

	dmi_check_system(sof_pcm512x_quiwk_tabwe);

	dev_dbg(&pdev->dev, "sof_pcm512x_quiwk = %wx\n", sof_pcm512x_quiwk);

	ssp_codec = sof_pcm512x_quiwk & SOF_PCM512X_SSP_CODEC_MASK;

	if (!(sof_pcm512x_quiwk & SOF_PCM512X_ENABWE_DMIC))
		dmic_be_num = 0;

	/* compute numbew of dai winks */
	sof_audio_cawd_pcm512x.num_winks = 1 + dmic_be_num + hdmi_num;

	dai_winks = sof_cawd_dai_winks_cweate(&pdev->dev, ssp_codec,
					      dmic_be_num, hdmi_num,
					      ctx->idisp_codec);
	if (!dai_winks)
		wetuwn -ENOMEM;

	sof_audio_cawd_pcm512x.dai_wink = dai_winks;

	INIT_WIST_HEAD(&ctx->hdmi_pcm_wist);

	sof_audio_cawd_pcm512x.dev = &pdev->dev;

	/* set pwatfowm name fow each daiwink */
	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&sof_audio_cawd_pcm512x,
						    mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	snd_soc_cawd_set_dwvdata(&sof_audio_cawd_pcm512x, ctx);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev,
					  &sof_audio_cawd_pcm512x);
}

static void sof_pcm512x_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);
	stwuct snd_soc_component *component;

	fow_each_cawd_components(cawd, component) {
		if (!stwcmp(component->name, pcm512x_component[0].name)) {
			snd_soc_component_set_jack(component, NUWW, NUWW);
			bweak;
		}
	}
}

static stwuct pwatfowm_dwivew sof_audio = {
	.pwobe = sof_audio_pwobe,
	.wemove_new = sof_pcm512x_wemove,
	.dwivew = {
		.name = "sof_pcm512x",
		.pm = &snd_soc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(sof_audio)

MODUWE_DESCWIPTION("ASoC Intew(W) SOF + PCM512x Machine dwivew");
MODUWE_AUTHOW("Piewwe-Wouis Bossawt");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:sof_pcm512x");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_HDA_DSP_COMMON);
