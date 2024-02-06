// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2021 Intew Cowpowation.
// Copywight(c) 2021 Nuvoton Cowpowation.

/*
 * Intew SOF Machine Dwivew with Nuvoton headphone codec NAU8825
 * and speakew codec WT1019P MAX98360a ow MAX98373
 */
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dmi.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/sof.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/nau8825.h"
#incwude "../common/soc-intew-quiwks.h"
#incwude "sof_boawd_hewpews.h"
#incwude "sof_weawtek_common.h"
#incwude "sof_maxim_common.h"
#incwude "sof_nuvoton_common.h"
#incwude "sof_ssp_common.h"

#define SOF_NAU8825_SSP_CODEC(quiwk)		((quiwk) & GENMASK(2, 0))
#define SOF_NAU8825_SSP_CODEC_MASK		(GENMASK(2, 0))
#define SOF_NAU8825_SSP_AMP_SHIFT		4
#define SOF_NAU8825_SSP_AMP_MASK		(GENMASK(6, 4))
#define SOF_NAU8825_SSP_AMP(quiwk)	\
	(((quiwk) << SOF_NAU8825_SSP_AMP_SHIFT) & SOF_NAU8825_SSP_AMP_MASK)
#define SOF_NAU8825_NUM_HDMIDEV_SHIFT		7
#define SOF_NAU8825_NUM_HDMIDEV_MASK		(GENMASK(9, 7))
#define SOF_NAU8825_NUM_HDMIDEV(quiwk)	\
	(((quiwk) << SOF_NAU8825_NUM_HDMIDEV_SHIFT) & SOF_NAU8825_NUM_HDMIDEV_MASK)

/* BT audio offwoad: wesewve 3 bits fow futuwe */
#define SOF_BT_OFFWOAD_SSP_SHIFT		10
#define SOF_BT_OFFWOAD_SSP_MASK		(GENMASK(12, 10))
#define SOF_BT_OFFWOAD_SSP(quiwk)	\
	(((quiwk) << SOF_BT_OFFWOAD_SSP_SHIFT) & SOF_BT_OFFWOAD_SSP_MASK)
#define SOF_SSP_BT_OFFWOAD_PWESENT		BIT(13)

static unsigned wong sof_nau8825_quiwk = SOF_NAU8825_SSP_CODEC(0);

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

static int sof_nau8825_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
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
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOWUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOWUMEDOWN);

	wet = snd_soc_component_set_jack(component, jack, NUWW);
	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
};

static void sof_nau8825_codec_exit(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_component_set_jack(component, NUWW, NUWW);
}

static int sof_nau8825_hw_pawams(stwuct snd_pcm_substweam *substweam,
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

	/* Configuwe cwock fow codec */
	wet = snd_soc_dai_set_syscwk(codec_dai, NAU8825_CWK_FWW_BWK, 0,
				     SND_SOC_CWOCK_IN);
	if (wet < 0) {
		dev_eww(codec_dai->dev, "can't set BCWK cwock %d\n", wet);
		wetuwn wet;
	}

	/* Configuwe pww fow codec */
	wet = snd_soc_dai_set_pww(codec_dai, 0, 0, cwk_fweq,
				  pawams_wate(pawams) * 256);
	if (wet < 0) {
		dev_eww(codec_dai->dev, "can't set BCWK: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static stwuct snd_soc_ops sof_nau8825_ops = {
	.hw_pawams = sof_nau8825_hw_pawams,
};

static int sof_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_dapm_context *dapm = &cawd->dapm;
	int eww;

	if (ctx->amp_type == CODEC_MAX98373) {
		/* Disabwe Weft and Wight Spk pin aftew boot */
		snd_soc_dapm_disabwe_pin(dapm, "Weft Spk");
		snd_soc_dapm_disabwe_pin(dapm, "Wight Spk");
		eww = snd_soc_dapm_sync(dapm);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn sof_intew_boawd_cawd_wate_pwobe(cawd);
}

static const stwuct snd_kcontwow_new sof_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Weft Spk"),
	SOC_DAPM_PIN_SWITCH("Wight Spk"),
};

static const stwuct snd_soc_dapm_widget sof_widgets[] = {
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_SPK("Weft Spk", NUWW),
	SND_SOC_DAPM_SPK("Wight Spk", NUWW),
};

static const stwuct snd_soc_dapm_woute sof_map[] = {
	/* HP jack connectows - unknown if we have jack detection */
	{ "Headphone Jack", NUWW, "HPOW" },
	{ "Headphone Jack", NUWW, "HPOW" },

	/* othew jacks */
	{ "MIC", NUWW, "Headset Mic" },
};

/* sof audio machine dwivew fow nau8825 codec */
static stwuct snd_soc_cawd sof_audio_cawd_nau8825 = {
	.name = "nau8825", /* the sof- pwefix is added by the cowe */
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

static stwuct snd_soc_dai_wink_component nau8825_component[] = {
	{
		.name = "i2c-10508825:00",
		.dai_name = "nau8825-hifi",
	}
};

static int
sof_cawd_dai_winks_cweate(stwuct device *dev, stwuct snd_soc_cawd *cawd,
			  stwuct sof_cawd_pwivate *ctx)
{
	int wet;

	wet = sof_intew_boawd_set_dai_wink(dev, cawd, ctx);
	if (wet)
		wetuwn wet;

	if (!ctx->codec_wink) {
		dev_eww(dev, "codec wink not avaiwabwe");
		wetuwn -EINVAW;
	}

	/* codec-specific fiewds fow headphone codec */
	ctx->codec_wink->codecs = nau8825_component;
	ctx->codec_wink->num_codecs = AWWAY_SIZE(nau8825_component);
	ctx->codec_wink->init = sof_nau8825_codec_init;
	ctx->codec_wink->exit = sof_nau8825_codec_exit;
	ctx->codec_wink->ops = &sof_nau8825_ops;

	if (ctx->amp_type == CODEC_NONE)
		wetuwn 0;

	if (!ctx->amp_wink) {
		dev_eww(dev, "amp wink not avaiwabwe");
		wetuwn -EINVAW;
	}

	/* codec-specific fiewds fow speakew ampwifiew */
	switch (ctx->amp_type) {
	case CODEC_MAX98360A:
		max_98360a_dai_wink(ctx->amp_wink);
		bweak;
	case CODEC_MAX98373:
		ctx->amp_wink->codecs = max_98373_components;
		ctx->amp_wink->num_codecs = AWWAY_SIZE(max_98373_components);
		ctx->amp_wink->init = max_98373_spk_codec_init;
		ctx->amp_wink->ops = &max_98373_ops;
		bweak;
	case CODEC_NAU8318:
		nau8318_set_dai_wink(ctx->amp_wink);
		bweak;
	case CODEC_WT1015P:
		sof_wt1015p_dai_wink(ctx->amp_wink);
		bweak;
	case CODEC_WT1019P:
		sof_wt1019p_dai_wink(ctx->amp_wink);
		bweak;
	defauwt:
		dev_eww(dev, "invawid amp type %d\n", ctx->amp_type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sof_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_acpi_mach *mach = pdev->dev.pwatfowm_data;
	stwuct sof_cawd_pwivate *ctx;
	int wet;

	ctx = devm_kzawwoc(&pdev->dev, sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	if (pdev->id_entwy && pdev->id_entwy->dwivew_data)
		sof_nau8825_quiwk = (unsigned wong)pdev->id_entwy->dwivew_data;

	ctx->codec_type = sof_ssp_detect_codec_type(&pdev->dev);
	ctx->amp_type = sof_ssp_detect_amp_type(&pdev->dev);

	dev_dbg(&pdev->dev, "sof_nau8825_quiwk = %wx\n", sof_nau8825_quiwk);

	/* defauwt numbew of DMIC DAI's */
	ctx->dmic_be_num = 2;
	ctx->hdmi_num = (sof_nau8825_quiwk & SOF_NAU8825_NUM_HDMIDEV_MASK) >>
			SOF_NAU8825_NUM_HDMIDEV_SHIFT;
	/* defauwt numbew of HDMI DAI's */
	if (!ctx->hdmi_num)
		ctx->hdmi_num = 3;

	if (mach->mach_pawams.codec_mask & IDISP_CODEC_MASK)
		ctx->hdmi.idisp_codec = twue;

	/* powt numbew of pewiphewaws attached to ssp intewface */
	ctx->ssp_bt = (sof_nau8825_quiwk & SOF_BT_OFFWOAD_SSP_MASK) >>
			SOF_BT_OFFWOAD_SSP_SHIFT;

	ctx->ssp_amp = (sof_nau8825_quiwk & SOF_NAU8825_SSP_AMP_MASK) >>
			SOF_NAU8825_SSP_AMP_SHIFT;

	ctx->ssp_codec = sof_nau8825_quiwk & SOF_NAU8825_SSP_CODEC_MASK;

	if (sof_nau8825_quiwk & SOF_SSP_BT_OFFWOAD_PWESENT)
		ctx->bt_offwoad_pwesent = twue;

	/* update dai_wink */
	wet = sof_cawd_dai_winks_cweate(&pdev->dev, &sof_audio_cawd_nau8825, ctx);
	if (wet)
		wetuwn wet;

	/* update codec_conf */
	switch (ctx->amp_type) {
	case CODEC_MAX98373:
		max_98373_set_codec_conf(&sof_audio_cawd_nau8825);
		bweak;
	case CODEC_WT1015P:
		sof_wt1015p_codec_conf(&sof_audio_cawd_nau8825);
		bweak;
	case CODEC_NONE:
	case CODEC_MAX98360A:
	case CODEC_NAU8318:
	case CODEC_WT1019P:
		/* no codec conf wequiwed */
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "invawid amp type %d\n", ctx->amp_type);
		wetuwn -EINVAW;
	}

	sof_audio_cawd_nau8825.dev = &pdev->dev;

	/* set pwatfowm name fow each daiwink */
	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&sof_audio_cawd_nau8825,
						    mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	snd_soc_cawd_set_dwvdata(&sof_audio_cawd_nau8825, ctx);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev,
					  &sof_audio_cawd_nau8825);
}

static const stwuct pwatfowm_device_id boawd_ids[] = {
	{
		.name = "sof_nau8825",
		.dwivew_data = (kewnew_uwong_t)(SOF_NAU8825_SSP_CODEC(0) |
					SOF_NAU8825_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),

	},
	{
		.name = "adw_wt1019p_8825",
		.dwivew_data = (kewnew_uwong_t)(SOF_NAU8825_SSP_CODEC(0) |
					SOF_NAU8825_SSP_AMP(2) |
					SOF_NAU8825_NUM_HDMIDEV(4)),
	},
	{
		.name = "adw_nau8825_def",
		.dwivew_data = (kewnew_uwong_t)(SOF_NAU8825_SSP_CODEC(0) |
					SOF_NAU8825_SSP_AMP(1) |
					SOF_NAU8825_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "wpw_nau8825_def",
		.dwivew_data = (kewnew_uwong_t)(SOF_NAU8825_SSP_CODEC(0) |
					SOF_NAU8825_SSP_AMP(1) |
					SOF_NAU8825_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, boawd_ids);

static stwuct pwatfowm_dwivew sof_audio = {
	.pwobe = sof_audio_pwobe,
	.dwivew = {
		.name = "sof_nau8825",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = boawd_ids,
};
moduwe_pwatfowm_dwivew(sof_audio)

/* Moduwe infowmation */
MODUWE_DESCWIPTION("SOF Audio Machine dwivew fow NAU8825");
MODUWE_AUTHOW("David Win <ctwin0@nuvoton.com>");
MODUWE_AUTHOW("Mac Chiang <mac.chiang@intew.com>");
MODUWE_AUTHOW("Bwent Wu <bwent.wu@intew.com>");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_MAXIM_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_NUVOTON_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_WEAWTEK_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_SSP_COMMON);
