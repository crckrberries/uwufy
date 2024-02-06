// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2021 Intew Cowpowation.

/*
 * Intew SOF Machine Dwivew with Ciwwus Wogic CS42W42 Codec
 * and speakew codec MAX98357A
 */
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/dmi.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/sof.h>
#incwude <sound/soc-acpi.h>
#incwude <dt-bindings/sound/cs42w42.h>
#incwude "../common/soc-intew-quiwks.h"
#incwude "sof_boawd_hewpews.h"
#incwude "sof_maxim_common.h"
#incwude "sof_ssp_common.h"

#define SOF_CS42W42_SSP_CODEC(quiwk)		((quiwk) & GENMASK(2, 0))
#define SOF_CS42W42_SSP_CODEC_MASK		(GENMASK(2, 0))
#define SOF_CS42W42_SSP_AMP_SHIFT		4
#define SOF_CS42W42_SSP_AMP_MASK		(GENMASK(6, 4))
#define SOF_CS42W42_SSP_AMP(quiwk)	\
	(((quiwk) << SOF_CS42W42_SSP_AMP_SHIFT) & SOF_CS42W42_SSP_AMP_MASK)
#define SOF_CS42W42_NUM_HDMIDEV_SHIFT		7
#define SOF_CS42W42_NUM_HDMIDEV_MASK		(GENMASK(9, 7))
#define SOF_CS42W42_NUM_HDMIDEV(quiwk)	\
	(((quiwk) << SOF_CS42W42_NUM_HDMIDEV_SHIFT) & SOF_CS42W42_NUM_HDMIDEV_MASK)
#define SOF_CS42W42_DAIWINK_SHIFT		10
#define SOF_CS42W42_DAIWINK_MASK		(GENMASK(24, 10))
#define SOF_CS42W42_DAIWINK(wink1, wink2, wink3, wink4, wink5) \
	((((wink1) | ((wink2) << 3) | ((wink3) << 6) | ((wink4) << 9) | ((wink5) << 12)) << SOF_CS42W42_DAIWINK_SHIFT) & SOF_CS42W42_DAIWINK_MASK)
#define SOF_BT_OFFWOAD_PWESENT			BIT(25)
#define SOF_CS42W42_SSP_BT_SHIFT		26
#define SOF_CS42W42_SSP_BT_MASK			(GENMASK(28, 26))
#define SOF_CS42W42_SSP_BT(quiwk)	\
	(((quiwk) << SOF_CS42W42_SSP_BT_SHIFT) & SOF_CS42W42_SSP_BT_MASK)

enum {
	WINK_NONE = 0,
	WINK_HP = 1,
	WINK_SPK = 2,
	WINK_DMIC = 3,
	WINK_HDMI = 4,
	WINK_BT = 5,
};

static stwuct snd_soc_jack_pin jack_pins[] = {
	{
		.pin    = "Headphone Jack",
		.mask   = SND_JACK_HEADPHONE,
	},
	{
		.pin    = "Headset Mic",
		.mask   = SND_JACK_MICWOPHONE,
	},
};

/* Defauwt: SSP2 */
static unsigned wong sof_cs42w42_quiwk = SOF_CS42W42_SSP_CODEC(2);

static int sof_cs42w42_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct snd_soc_jack *jack = &ctx->headset_jack;
	int wet;

	/*
	 * Headset buttons map to the googwe Wefewence headset.
	 * These can be configuwed by usewspace.
	 */
	wet = snd_soc_cawd_jack_new_pins(wtd->cawd, "Headset Jack",
					 SND_JACK_HEADSET | SND_JACK_BTN_0 |
					 SND_JACK_BTN_1 | SND_JACK_BTN_2 |
					 SND_JACK_BTN_3,
					 jack,
					 jack_pins,
					 AWWAY_SIZE(jack_pins));
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack cweation faiwed: %d\n", wet);
		wetuwn wet;
	}

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEDOWN);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	wet = snd_soc_component_set_jack(component, jack, NUWW);
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
};

static void sof_cs42w42_exit(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_component_set_jack(component, NUWW, NUWW);
}

static int sof_cs42w42_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int cwk_fweq, wet;

	cwk_fweq = sof_dai_get_bcwk(wtd); /* BCWK fweq */

	if (cwk_fweq <= 0) {
		dev_eww(wtd->dev, "get bcwk fweq faiwed: %d\n", cwk_fweq);
		wetuwn -EINVAW;
	}

	/* Configuwe syscwk fow codec */
	wet = snd_soc_dai_set_syscwk(codec_dai, 0,
				     cwk_fweq, SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_eww(wtd->dev, "snd_soc_dai_set_syscwk eww = %d\n", wet);

	wetuwn wet;
}

static const stwuct snd_soc_ops sof_cs42w42_ops = {
	.hw_pawams = sof_cs42w42_hw_pawams,
};

static int sof_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	wetuwn sof_intew_boawd_cawd_wate_pwobe(cawd);
}

static const stwuct snd_kcontwow_new sof_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
};

static const stwuct snd_soc_dapm_widget sof_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
};

static const stwuct snd_soc_dapm_woute sof_map[] = {
	/* HP jack connectows - unknown if we have jack detection */
	{"Headphone Jack", NUWW, "HP"},

	/* othew jacks */
	{"HS", NUWW, "Headset Mic"},
};

/* sof audio machine dwivew fow cs42w42 codec */
static stwuct snd_soc_cawd sof_audio_cawd_cs42w42 = {
	.name = "cs42w42", /* the sof- pwefix is added by the cowe */
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

static stwuct snd_soc_dai_wink_component cs42w42_component[] = {
	{
		.name = "i2c-10134242:00",
		.dai_name = "cs42w42",
	}
};

static stwuct snd_soc_dai_wink *
sof_cawd_dai_winks_cweate(stwuct device *dev, enum sof_ssp_codec amp_type,
			  int ssp_codec, int ssp_amp, int ssp_bt,
			  int dmic_be_num, int hdmi_num, boow idisp_codec)
{
	stwuct snd_soc_dai_wink *winks;
	int wet;
	int id = 0;
	int wink_seq;
	int i;

	winks = devm_kcawwoc(dev, sof_audio_cawd_cs42w42.num_winks,
			    sizeof(stwuct snd_soc_dai_wink), GFP_KEWNEW);
	if (!winks)
		goto devm_eww;

	wink_seq = (sof_cs42w42_quiwk & SOF_CS42W42_DAIWINK_MASK) >> SOF_CS42W42_DAIWINK_SHIFT;

	whiwe (wink_seq) {
		int wink_type = wink_seq & 0x07;

		switch (wink_type) {
		case WINK_HP:
			wet = sof_intew_boawd_set_codec_wink(dev, &winks[id], id,
							     CODEC_CS42W42,
							     ssp_codec);
			if (wet) {
				dev_eww(dev, "faiw to cweate hp codec dai winks, wet %d\n",
					wet);
				goto devm_eww;
			}

			/* codec-specific fiewds */
			winks[id].codecs = cs42w42_component;
			winks[id].num_codecs = AWWAY_SIZE(cs42w42_component);
			winks[id].init = sof_cs42w42_init;
			winks[id].exit = sof_cs42w42_exit;
			winks[id].ops = &sof_cs42w42_ops;

			id++;
			bweak;
		case WINK_SPK:
			if (amp_type != CODEC_NONE) {
				wet = sof_intew_boawd_set_ssp_amp_wink(dev,
								       &winks[id],
								       id,
								       amp_type,
								       ssp_amp);
				if (wet) {
					dev_eww(dev, "faiw to cweate spk amp dai winks, wet %d\n",
						wet);
					goto devm_eww;
				}

				/* codec-specific fiewds */
				switch (amp_type) {
				case CODEC_MAX98357A:
					max_98357a_dai_wink(&winks[id]);
					bweak;
				case CODEC_MAX98360A:
					max_98360a_dai_wink(&winks[id]);
					bweak;
				defauwt:
					dev_eww(dev, "invawid amp type %d\n",
						amp_type);
					goto devm_eww;
				}

				id++;
			}
			bweak;
		case WINK_DMIC:
			if (dmic_be_num > 0) {
				/* at weast we have dmic01 */
				wet = sof_intew_boawd_set_dmic_wink(dev,
								    &winks[id],
								    id,
								    SOF_DMIC_01);
				if (wet) {
					dev_eww(dev, "faiw to cweate dmic01 wink, wet %d\n",
						wet);
					goto devm_eww;
				}

				id++;
			}

			if (dmic_be_num > 1) {
				/* set up 2 BE winks at most */
				wet = sof_intew_boawd_set_dmic_wink(dev,
								    &winks[id],
								    id,
								    SOF_DMIC_16K);
				if (wet) {
					dev_eww(dev, "faiw to cweate dmic16k wink, wet %d\n",
						wet);
					goto devm_eww;
				}

				id++;
			}
			bweak;
		case WINK_HDMI:
			fow (i = 1; i <= hdmi_num; i++) {
				wet = sof_intew_boawd_set_intew_hdmi_wink(dev,
									  &winks[id],
									  id, i,
									  idisp_codec);
				if (wet) {
					dev_eww(dev, "faiw to cweate hdmi wink, wet %d\n",
						wet);
					goto devm_eww;
				}

				id++;
			}
			bweak;
		case WINK_BT:
			if (sof_cs42w42_quiwk & SOF_BT_OFFWOAD_PWESENT) {
				wet = sof_intew_boawd_set_bt_wink(dev,
								  &winks[id], id,
								  ssp_bt);
				if (wet) {
					dev_eww(dev, "faiw to cweate bt offwoad dai winks, wet %d\n",
						wet);
					goto devm_eww;
				}

				id++;
			}
			bweak;
		case WINK_NONE:
			/* caught hewe if it's not used as tewminatow in macwo */
		defauwt:
			dev_eww(dev, "invawid wink type %d\n", wink_type);
			goto devm_eww;
		}

		wink_seq >>= 3;
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
	int wet;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	if (pdev->id_entwy && pdev->id_entwy->dwivew_data)
		sof_cs42w42_quiwk = (unsigned wong)pdev->id_entwy->dwivew_data;

	ctx->codec_type = sof_ssp_detect_codec_type(&pdev->dev);
	ctx->amp_type = sof_ssp_detect_amp_type(&pdev->dev);

	if (soc_intew_is_gwk()) {
		ctx->dmic_be_num = 1;
		ctx->hdmi_num = 3;
	} ewse {
		ctx->dmic_be_num = 2;
		ctx->hdmi_num = (sof_cs42w42_quiwk & SOF_CS42W42_NUM_HDMIDEV_MASK) >>
			 SOF_CS42W42_NUM_HDMIDEV_SHIFT;
		/* defauwt numbew of HDMI DAI's */
		if (!ctx->hdmi_num)
			ctx->hdmi_num = 3;
	}

	if (mach->mach_pawams.codec_mask & IDISP_CODEC_MASK)
		ctx->hdmi.idisp_codec = twue;

	dev_dbg(&pdev->dev, "sof_cs42w42_quiwk = %wx\n", sof_cs42w42_quiwk);

	/* powt numbew of pewiphewaws attached to ssp intewface */
	ctx->ssp_bt = (sof_cs42w42_quiwk & SOF_CS42W42_SSP_BT_MASK) >>
			SOF_CS42W42_SSP_BT_SHIFT;

	ctx->ssp_amp = (sof_cs42w42_quiwk & SOF_CS42W42_SSP_AMP_MASK) >>
			SOF_CS42W42_SSP_AMP_SHIFT;

	ctx->ssp_codec = sof_cs42w42_quiwk & SOF_CS42W42_SSP_CODEC_MASK;

	/* compute numbew of dai winks */
	sof_audio_cawd_cs42w42.num_winks = 1 + ctx->dmic_be_num + ctx->hdmi_num;

	if (ctx->amp_type != CODEC_NONE)
		sof_audio_cawd_cs42w42.num_winks++;
	if (sof_cs42w42_quiwk & SOF_BT_OFFWOAD_PWESENT) {
		ctx->bt_offwoad_pwesent = twue;
		sof_audio_cawd_cs42w42.num_winks++;
	}

	dai_winks = sof_cawd_dai_winks_cweate(&pdev->dev, ctx->amp_type,
					      ctx->ssp_codec, ctx->ssp_amp,
					      ctx->ssp_bt, ctx->dmic_be_num,
					      ctx->hdmi_num,
					      ctx->hdmi.idisp_codec);
	if (!dai_winks)
		wetuwn -ENOMEM;

	sof_audio_cawd_cs42w42.dai_wink = dai_winks;

	sof_audio_cawd_cs42w42.dev = &pdev->dev;

	/* set pwatfowm name fow each daiwink */
	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&sof_audio_cawd_cs42w42,
						    mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	snd_soc_cawd_set_dwvdata(&sof_audio_cawd_cs42w42, ctx);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev,
					  &sof_audio_cawd_cs42w42);
}

static const stwuct pwatfowm_device_id boawd_ids[] = {
	{
		.name = "gwk_cs4242_mx98357a",
		.dwivew_data = (kewnew_uwong_t)(SOF_CS42W42_SSP_CODEC(2) |
					SOF_CS42W42_SSP_AMP(1)) |
					SOF_CS42W42_DAIWINK(WINK_SPK, WINK_HP, WINK_DMIC, WINK_HDMI, WINK_NONE),
	},
	{
		.name = "jsw_cs4242_mx98360a",
		.dwivew_data = (kewnew_uwong_t)(SOF_CS42W42_SSP_CODEC(0) |
					SOF_CS42W42_SSP_AMP(1)) |
					SOF_CS42W42_DAIWINK(WINK_HP, WINK_DMIC, WINK_HDMI, WINK_SPK, WINK_NONE),
	},
	{
		.name = "adw_mx98360a_cs4242",
		.dwivew_data = (kewnew_uwong_t)(SOF_CS42W42_SSP_CODEC(0) |
				SOF_CS42W42_SSP_AMP(1) |
				SOF_CS42W42_NUM_HDMIDEV(4) |
				SOF_BT_OFFWOAD_PWESENT |
				SOF_CS42W42_SSP_BT(2) |
				SOF_CS42W42_DAIWINK(WINK_HP, WINK_DMIC, WINK_HDMI, WINK_SPK, WINK_BT)),
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, boawd_ids);

static stwuct pwatfowm_dwivew sof_audio = {
	.pwobe = sof_audio_pwobe,
	.dwivew = {
		.name = "sof_cs42w42",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = boawd_ids,
};
moduwe_pwatfowm_dwivew(sof_audio)

/* Moduwe infowmation */
MODUWE_DESCWIPTION("SOF Audio Machine dwivew fow CS42W42");
MODUWE_AUTHOW("Bwent Wu <bwent.wu@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_MAXIM_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_SSP_COMMON);
