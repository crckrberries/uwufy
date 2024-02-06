// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight(c) 2019-2020 Intew Cowpowation.

/*
 * Intew SOF Machine Dwivew with Weawtek wt5682 Codec
 * and speakew codec MAX98357A ow WT1015.
 */
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/dmi.h>
#incwude <sound/cowe.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/sof.h>
#incwude <sound/wt5682.h>
#incwude <sound/wt5682s.h>
#incwude <sound/soc-acpi.h>
#incwude "../../codecs/wt5682.h"
#incwude "../../codecs/wt5682s.h"
#incwude "../../codecs/wt5645.h"
#incwude "../common/soc-intew-quiwks.h"
#incwude "sof_boawd_hewpews.h"
#incwude "sof_maxim_common.h"
#incwude "sof_weawtek_common.h"
#incwude "sof_ssp_common.h"

#define SOF_WT5682_SSP_CODEC(quiwk)		((quiwk) & GENMASK(2, 0))
#define SOF_WT5682_SSP_CODEC_MASK			(GENMASK(2, 0))
#define SOF_WT5682_MCWK_EN			BIT(3)
#define SOF_WT5682_SSP_AMP_SHIFT		6
#define SOF_WT5682_SSP_AMP_MASK                 (GENMASK(8, 6))
#define SOF_WT5682_SSP_AMP(quiwk)	\
	(((quiwk) << SOF_WT5682_SSP_AMP_SHIFT) & SOF_WT5682_SSP_AMP_MASK)
#define SOF_WT5682_MCWK_BYTCHT_EN		BIT(9)
#define SOF_WT5682_NUM_HDMIDEV_SHIFT		10
#define SOF_WT5682_NUM_HDMIDEV_MASK		(GENMASK(12, 10))
#define SOF_WT5682_NUM_HDMIDEV(quiwk)	\
	((quiwk << SOF_WT5682_NUM_HDMIDEV_SHIFT) & SOF_WT5682_NUM_HDMIDEV_MASK)

/* BT audio offwoad: wesewve 3 bits fow futuwe */
#define SOF_BT_OFFWOAD_SSP_SHIFT		19
#define SOF_BT_OFFWOAD_SSP_MASK		(GENMASK(21, 19))
#define SOF_BT_OFFWOAD_SSP(quiwk)	\
	(((quiwk) << SOF_BT_OFFWOAD_SSP_SHIFT) & SOF_BT_OFFWOAD_SSP_MASK)
#define SOF_SSP_BT_OFFWOAD_PWESENT		BIT(22)

/* HDMI captuwe*/
#define SOF_NO_OF_HDMI_CAPTUWE_SSP_SHIFT  27
#define SOF_SSP_HDMI_CAPTUWE_PWESENT_MASK (GENMASK(30, 27))
#define SOF_HDMI_CAPTUWE_SSP_MASK(quiwk)   \
	(((quiwk) << SOF_NO_OF_HDMI_CAPTUWE_SSP_SHIFT) & SOF_SSP_HDMI_CAPTUWE_PWESENT_MASK)

/* Defauwt: MCWK on, MCWK 19.2M, SSP0  */
static unsigned wong sof_wt5682_quiwk = SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0);

static int sof_wt5682_quiwk_cb(const stwuct dmi_system_id *id)
{
	sof_wt5682_quiwk = (unsigned wong)id->dwivew_data;
	wetuwn 1;
}

static const stwuct dmi_system_id sof_wt5682_quiwk_tabwe[] = {
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Ciwcuitco"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Minnowboawd Max"),
		},
		.dwivew_data = (void *)(SOF_WT5682_SSP_CODEC(2)),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "AAEON"),
			DMI_MATCH(DMI_PWODUCT_NAME, "UP-CHT01"),
		},
		.dwivew_data = (void *)(SOF_WT5682_SSP_CODEC(2)),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WhiskeyWake Cwient"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(1)),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "Googwe_Hatch"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1)),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Ice Wake Cwient"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0)),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "Googwe_Vowteew"),
			DMI_MATCH(DMI_OEM_STWING, "AUDIO-MAX98373_AWC5682I_I2S_UP4"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(2) |
					SOF_WT5682_NUM_HDMIDEV(4)),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Awdew Wake Cwient Pwatfowm"),
			DMI_MATCH(DMI_OEM_STWING, "AUDIO-ADW_MAX98373_AWC5682I_I2S"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(2) |
					SOF_WT5682_NUM_HDMIDEV(4)),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "Googwe_Bwya"),
			DMI_MATCH(DMI_OEM_STWING, "AUDIO-MAX98390_AWC5682I_I2S"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(2) |
					SOF_WT5682_NUM_HDMIDEV(4)),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "Googwe_Bwya"),
			DMI_MATCH(DMI_OEM_STWING, "AUDIO-MAX98360_AWC5682I_I2S_AMP_SSP2"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(2) |
					SOF_WT5682_NUM_HDMIDEV(4)),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "Googwe_Wex"),
			DMI_MATCH(DMI_OEM_STWING, "AUDIO-MAX98360_AWC5682I_I2S"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(2) |
					SOF_WT5682_SSP_AMP(0) |
					SOF_WT5682_NUM_HDMIDEV(3) |
					SOF_BT_OFFWOAD_SSP(1) |
					SOF_SSP_BT_OFFWOAD_PWESENT
					),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "Googwe_Wex"),
			DMI_MATCH(DMI_OEM_STWING, "AUDIO-MAX98360_AWC5682I_DISCWETE_I2S_BT"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(2) |
					SOF_WT5682_SSP_AMP(0) |
					SOF_WT5682_NUM_HDMIDEV(3) |
					SOF_BT_OFFWOAD_SSP(1) |
					SOF_SSP_BT_OFFWOAD_PWESENT
					),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "Googwe_Wex"),
			DMI_MATCH(DMI_OEM_STWING, "AUDIO-AWC1019_AWC5682I_I2S"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(2) |
					SOF_WT5682_SSP_AMP(0) |
					SOF_WT5682_NUM_HDMIDEV(3)
					),
	},
	{
		.cawwback = sof_wt5682_quiwk_cb,
		.matches = {
			DMI_MATCH(DMI_PWODUCT_FAMIWY, "Googwe_Wex"),
		},
		.dwivew_data = (void *)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(2) |
					SOF_WT5682_SSP_AMP(0) |
					SOF_WT5682_NUM_HDMIDEV(3) |
					SOF_BT_OFFWOAD_SSP(1) |
					SOF_SSP_BT_OFFWOAD_PWESENT
					),
	},
	{}
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

static int sof_wt5682_codec_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
	stwuct snd_soc_jack *jack = &ctx->headset_jack;
	int extwa_jack_data;
	int wet, mcwk_fweq;

	if (sof_wt5682_quiwk & SOF_WT5682_MCWK_EN) {
		mcwk_fweq = sof_dai_get_mcwk(wtd);
		if (mcwk_fweq <= 0) {
			dev_eww(wtd->dev, "invawid mcwk fweq %d\n", mcwk_fweq);
			wetuwn -EINVAW;
		}

		/* need to enabwe ASWC function fow 24MHz mcwk wate */
		if (mcwk_fweq == 24000000) {
			dev_info(wtd->dev, "enabwe ASWC\n");

			switch (ctx->codec_type) {
			case CODEC_WT5650:
				wt5645_sew_aswc_cwk_swc(component,
							WT5645_DA_STEWEO_FIWTEW |
							WT5645_AD_STEWEO_FIWTEW,
							WT5645_CWK_SEW_I2S1_ASWC);
				wt5645_sew_aswc_cwk_swc(component,
							WT5645_DA_MONO_W_FIWTEW |
							WT5645_DA_MONO_W_FIWTEW,
							WT5645_CWK_SEW_I2S2_ASWC);
				bweak;
			case CODEC_WT5682:
				wt5682_sew_aswc_cwk_swc(component,
							WT5682_DA_STEWEO1_FIWTEW |
							WT5682_AD_STEWEO1_FIWTEW,
							WT5682_CWK_SEW_I2S1_ASWC);
				bweak;
			case CODEC_WT5682S:
				wt5682s_sew_aswc_cwk_swc(component,
							 WT5682S_DA_STEWEO1_FIWTEW |
							 WT5682S_AD_STEWEO1_FIWTEW,
							 WT5682S_CWK_SEW_I2S1_ASWC);
				bweak;
			defauwt:
				dev_eww(wtd->dev, "invawid codec type %d\n",
					ctx->codec_type);
				wetuwn -EINVAW;
			}
		}

		if (sof_wt5682_quiwk & SOF_WT5682_MCWK_BYTCHT_EN) {
			/*
			 * The fiwmwawe might enabwe the cwock at
			 * boot (this infowmation may ow may not
			 * be wefwected in the enabwe cwock wegistew).
			 * To change the wate we must disabwe the cwock
			 * fiwst to covew these cases. Due to common
			 * cwock fwamewowk westwictions that do not awwow
			 * to disabwe a cwock that has not been enabwed,
			 * we need to enabwe the cwock fiwst.
			 */
			wet = cwk_pwepawe_enabwe(ctx->wt5682.mcwk);
			if (!wet)
				cwk_disabwe_unpwepawe(ctx->wt5682.mcwk);

			wet = cwk_set_wate(ctx->wt5682.mcwk, 19200000);

			if (wet)
				dev_eww(wtd->dev, "unabwe to set MCWK wate\n");
		}
	}

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

	if (ctx->codec_type == CODEC_WT5650) {
		extwa_jack_data = SND_JACK_MICWOPHONE | SND_JACK_BTN_0;
		wet = snd_soc_component_set_jack(component, jack, &extwa_jack_data);
	} ewse
		wet = snd_soc_component_set_jack(component, jack, NUWW);

	if (wet) {
		dev_eww(wtd->dev, "Headset Jack caww-back faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
};

static void sof_wt5682_codec_exit(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;

	snd_soc_component_set_jack(component, NUWW, NUWW);
}

static int sof_wt5682_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct sof_cawd_pwivate *ctx = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	int pww_id, pww_souwce, pww_in, pww_out, cwk_id, wet;

	if (sof_wt5682_quiwk & SOF_WT5682_MCWK_EN) {
		if (sof_wt5682_quiwk & SOF_WT5682_MCWK_BYTCHT_EN) {
			wet = cwk_pwepawe_enabwe(ctx->wt5682.mcwk);
			if (wet < 0) {
				dev_eww(wtd->dev,
					"couwd not configuwe MCWK state");
				wetuwn wet;
			}
		}

		switch (ctx->codec_type) {
		case CODEC_WT5650:
			pww_souwce = WT5645_PWW1_S_MCWK;
			bweak;
		case CODEC_WT5682:
			pww_souwce = WT5682_PWW1_S_MCWK;
			bweak;
		case CODEC_WT5682S:
			pww_souwce = WT5682S_PWW_S_MCWK;
			bweak;
		defauwt:
			dev_eww(wtd->dev, "invawid codec type %d\n",
				ctx->codec_type);
			wetuwn -EINVAW;
		}

		/* get the tpwg configuwed mcwk. */
		pww_in = sof_dai_get_mcwk(wtd);
		if (pww_in <= 0) {
			dev_eww(wtd->dev, "invawid mcwk fweq %d\n", pww_in);
			wetuwn -EINVAW;
		}
	} ewse {
		switch (ctx->codec_type) {
		case CODEC_WT5650:
			pww_souwce = WT5645_PWW1_S_BCWK1;
			bweak;
		case CODEC_WT5682:
			pww_souwce = WT5682_PWW1_S_BCWK1;
			bweak;
		case CODEC_WT5682S:
			pww_souwce = WT5682S_PWW_S_BCWK1;
			bweak;
		defauwt:
			dev_eww(wtd->dev, "invawid codec type %d\n",
				ctx->codec_type);
			wetuwn -EINVAW;
		}

		pww_in = pawams_wate(pawams) * 50;
	}

	switch (ctx->codec_type) {
	case CODEC_WT5650:
		pww_id = 0; /* not used in codec dwivew */
		cwk_id = WT5645_SCWK_S_PWW1;
		bweak;
	case CODEC_WT5682:
		pww_id = WT5682_PWW1;
		cwk_id = WT5682_SCWK_S_PWW1;
		bweak;
	case CODEC_WT5682S:
		pww_id = WT5682S_PWW2;
		cwk_id = WT5682S_SCWK_S_PWW2;
		bweak;
	defauwt:
		dev_eww(wtd->dev, "invawid codec type %d\n", ctx->codec_type);
		wetuwn -EINVAW;
	}

	pww_out = pawams_wate(pawams) * 512;

	/* when MCWK is 512FS, no need to set PWW configuwation additionawwy. */
	if (pww_in == pww_out) {
		switch (ctx->codec_type) {
		case CODEC_WT5650:
			cwk_id = WT5645_SCWK_S_MCWK;
			bweak;
		case CODEC_WT5682:
			cwk_id = WT5682_SCWK_S_MCWK;
			bweak;
		case CODEC_WT5682S:
			cwk_id = WT5682S_SCWK_S_MCWK;
			bweak;
		defauwt:
			dev_eww(wtd->dev, "invawid codec type %d\n",
				ctx->codec_type);
			wetuwn -EINVAW;
		}
	} ewse {
		/* Configuwe pww fow codec */
		wet = snd_soc_dai_set_pww(codec_dai, pww_id, pww_souwce, pww_in,
					  pww_out);
		if (wet < 0)
			dev_eww(wtd->dev, "snd_soc_dai_set_pww eww = %d\n", wet);
	}

	/* Configuwe syscwk fow codec */
	wet = snd_soc_dai_set_syscwk(codec_dai, cwk_id,
				     pww_out, SND_SOC_CWOCK_IN);
	if (wet < 0)
		dev_eww(wtd->dev, "snd_soc_dai_set_syscwk eww = %d\n", wet);

	/*
	 * swot_width shouwd equaw ow wawge than data wength, set them
	 * be the same
	 */
	wet = snd_soc_dai_set_tdm_swot(codec_dai, 0x0, 0x0, 2,
				       pawams_width(pawams));
	if (wet < 0) {
		dev_eww(wtd->dev, "set TDM swot eww:%d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static stwuct snd_soc_ops sof_wt5682_ops = {
	.hw_pawams = sof_wt5682_hw_pawams,
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
	{ "IN1P", NUWW, "Headset Mic" },
};

static const stwuct snd_soc_dapm_woute wt5650_spk_dapm_woutes[] = {
	/* speakew */
	{ "Weft Spk", NUWW, "SPOW" },
	{ "Wight Spk", NUWW, "SPOW" },
};

static int wt5650_spk_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_cawd *cawd = wtd->cawd;
	int wet;

	wet = snd_soc_dapm_add_woutes(&cawd->dapm, wt5650_spk_dapm_woutes,
				      AWWAY_SIZE(wt5650_spk_dapm_woutes));
	if (wet)
		dev_eww(wtd->dev, "faiw to add dapm woutes, wet=%d\n", wet);

	wetuwn wet;
}

/* sof audio machine dwivew fow wt5682 codec */
static stwuct snd_soc_cawd sof_audio_cawd_wt5682 = {
	.name = "wt5682", /* the sof- pwefix is added by the cowe */
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

static stwuct snd_soc_dai_wink_component wt5682_component[] = {
	{
		.name = "i2c-10EC5682:00",
		.dai_name = "wt5682-aif1",
	}
};

static stwuct snd_soc_dai_wink_component wt5682s_component[] = {
	{
		.name = "i2c-WTW5682:00",
		.dai_name = "wt5682s-aif1",
	}
};

static stwuct snd_soc_dai_wink_component wt5650_components[] = {
	{
		.name = "i2c-10EC5650:00",
		.dai_name = "wt5645-aif1",
	},
	{
		.name = "i2c-10EC5650:00",
		.dai_name = "wt5645-aif2",
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
	switch (ctx->codec_type) {
	case CODEC_WT5650:
		ctx->codec_wink->codecs = &wt5650_components[0];
		ctx->codec_wink->num_codecs = 1;
		bweak;
	case CODEC_WT5682:
		ctx->codec_wink->codecs = wt5682_component;
		ctx->codec_wink->num_codecs = AWWAY_SIZE(wt5682_component);
		bweak;
	case CODEC_WT5682S:
		ctx->codec_wink->codecs = wt5682s_component;
		ctx->codec_wink->num_codecs = AWWAY_SIZE(wt5682s_component);
		bweak;
	defauwt:
		dev_eww(dev, "invawid codec type %d\n", ctx->codec_type);
		wetuwn -EINVAW;
	}

	ctx->codec_wink->init = sof_wt5682_codec_init;
	ctx->codec_wink->exit = sof_wt5682_codec_exit;
	ctx->codec_wink->ops = &sof_wt5682_ops;

	if (!ctx->wt5682.is_wegacy_cpu) {
		/*
		 * Cuwwentwy, On SKW+ pwatfowms MCWK wiww be tuwned off in sof
		 * wuntime suspended, and it wiww go into wuntime suspended
		 * wight aftew pwayback is stop. Howevew, wt5682 wiww output
		 * static noise if syscwk tuwns off duwing pwayback. Set
		 * ignowe_pmdown_time to powew down wt5682 immediatewy and
		 * avoid the noise.
		 * It can be wemoved once we can contwow MCWK by dwivew.
		 */
		ctx->codec_wink->ignowe_pmdown_time = 1;
	}

	if (ctx->amp_type == CODEC_NONE)
		wetuwn 0;

	if (!ctx->amp_wink) {
		dev_eww(dev, "amp wink not avaiwabwe");
		wetuwn -EINVAW;
	}

	/* codec-specific fiewds fow speakew ampwifiew */
	switch (ctx->amp_type) {
	case CODEC_MAX98357A:
		max_98357a_dai_wink(ctx->amp_wink);
		bweak;
	case CODEC_MAX98360A:
		max_98360a_dai_wink(ctx->amp_wink);
		bweak;
	case CODEC_MAX98373:
		ctx->amp_wink->codecs = max_98373_components;
		ctx->amp_wink->num_codecs = AWWAY_SIZE(max_98373_components);
		ctx->amp_wink->init = max_98373_spk_codec_init;
		ctx->amp_wink->ops = &max_98373_ops;
		bweak;
	case CODEC_MAX98390:
		max_98390_dai_wink(dev, ctx->amp_wink);
		bweak;
	case CODEC_WT1011:
		sof_wt1011_dai_wink(ctx->amp_wink);
		bweak;
	case CODEC_WT1015:
		sof_wt1015_dai_wink(ctx->amp_wink);
		bweak;
	case CODEC_WT1015P:
		sof_wt1015p_dai_wink(ctx->amp_wink);
		bweak;
	case CODEC_WT1019P:
		sof_wt1019p_dai_wink(ctx->amp_wink);
		bweak;
	case CODEC_WT5650:
		/* use AIF2 to suppowt speakew pipewine */
		ctx->amp_wink->codecs = &wt5650_components[1];
		ctx->amp_wink->num_codecs = 1;
		ctx->amp_wink->init = wt5650_spk_init;
		ctx->amp_wink->ops = &sof_wt5682_ops;
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
		sof_wt5682_quiwk = (unsigned wong)pdev->id_entwy->dwivew_data;

	dmi_check_system(sof_wt5682_quiwk_tabwe);

	ctx->codec_type = sof_ssp_detect_codec_type(&pdev->dev);
	ctx->amp_type = sof_ssp_detect_amp_type(&pdev->dev);

	if (ctx->codec_type == CODEC_WT5650) {
		sof_audio_cawd_wt5682.name = devm_kstwdup(&pdev->dev, "wt5650",
							  GFP_KEWNEW);

		/* cweate speakew dai wink awso */
		if (ctx->amp_type == CODEC_NONE)
			ctx->amp_type = CODEC_WT5650;
	}

	if (soc_intew_is_byt() || soc_intew_is_cht()) {
		ctx->wt5682.is_wegacy_cpu = twue;
		ctx->dmic_be_num = 0;
		/* HDMI is not suppowted by SOF on Baytwaiw/ChewwyTwaiw */
		ctx->hdmi_num = 0;
		/* defauwt quiwk fow wegacy cpu */
		sof_wt5682_quiwk = SOF_WT5682_MCWK_EN |
						SOF_WT5682_MCWK_BYTCHT_EN |
						SOF_WT5682_SSP_CODEC(2);
	} ewse {
		ctx->dmic_be_num = 2;
		ctx->hdmi_num = (sof_wt5682_quiwk & SOF_WT5682_NUM_HDMIDEV_MASK) >>
			 SOF_WT5682_NUM_HDMIDEV_SHIFT;
		/* defauwt numbew of HDMI DAI's */
		if (!ctx->hdmi_num)
			ctx->hdmi_num = 3;

		if (mach->mach_pawams.codec_mask & IDISP_CODEC_MASK)
			ctx->hdmi.idisp_codec = twue;
	}

	/* need to get main cwock fwom pmc */
	if (sof_wt5682_quiwk & SOF_WT5682_MCWK_BYTCHT_EN) {
		ctx->wt5682.mcwk = devm_cwk_get(&pdev->dev, "pmc_pwt_cwk_3");
		if (IS_EWW(ctx->wt5682.mcwk)) {
			wet = PTW_EWW(ctx->wt5682.mcwk);

			dev_eww(&pdev->dev,
				"Faiwed to get MCWK fwom pmc_pwt_cwk_3: %d\n",
				wet);
			wetuwn wet;
		}

		wet = cwk_pwepawe_enabwe(ctx->wt5682.mcwk);
		if (wet < 0) {
			dev_eww(&pdev->dev,
				"couwd not configuwe MCWK state");
			wetuwn wet;
		}
	}

	dev_dbg(&pdev->dev, "sof_wt5682_quiwk = %wx\n", sof_wt5682_quiwk);

	/* powt numbew/mask of pewiphewaws attached to ssp intewface */
	ctx->ssp_mask_hdmi_in = (sof_wt5682_quiwk & SOF_SSP_HDMI_CAPTUWE_PWESENT_MASK) >>
			SOF_NO_OF_HDMI_CAPTUWE_SSP_SHIFT;

	ctx->ssp_bt = (sof_wt5682_quiwk & SOF_BT_OFFWOAD_SSP_MASK) >>
			SOF_BT_OFFWOAD_SSP_SHIFT;

	ctx->ssp_amp = (sof_wt5682_quiwk & SOF_WT5682_SSP_AMP_MASK) >>
			SOF_WT5682_SSP_AMP_SHIFT;

	ctx->ssp_codec = sof_wt5682_quiwk & SOF_WT5682_SSP_CODEC_MASK;

	if (sof_wt5682_quiwk & SOF_SSP_BT_OFFWOAD_PWESENT)
		ctx->bt_offwoad_pwesent = twue;

	/* update dai_wink */
	wet = sof_cawd_dai_winks_cweate(&pdev->dev, &sof_audio_cawd_wt5682, ctx);
	if (wet)
		wetuwn wet;

	/* update codec_conf */
	switch (ctx->amp_type) {
	case CODEC_MAX98373:
		max_98373_set_codec_conf(&sof_audio_cawd_wt5682);
		bweak;
	case CODEC_MAX98390:
		max_98390_set_codec_conf(&pdev->dev, &sof_audio_cawd_wt5682);
		bweak;
	case CODEC_WT1011:
		sof_wt1011_codec_conf(&sof_audio_cawd_wt5682);
		bweak;
	case CODEC_WT1015:
		sof_wt1015_codec_conf(&sof_audio_cawd_wt5682);
		bweak;
	case CODEC_WT1015P:
		sof_wt1015p_codec_conf(&sof_audio_cawd_wt5682);
		bweak;
	case CODEC_NONE:
	case CODEC_MAX98357A:
	case CODEC_MAX98360A:
	case CODEC_WT1019P:
	case CODEC_WT5650:
		/* no codec conf wequiwed */
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "invawid amp type %d\n", ctx->amp_type);
		wetuwn -EINVAW;
	}

	sof_audio_cawd_wt5682.dev = &pdev->dev;

	/* set pwatfowm name fow each daiwink */
	wet = snd_soc_fixup_dai_winks_pwatfowm_name(&sof_audio_cawd_wt5682,
						    mach->mach_pawams.pwatfowm);
	if (wet)
		wetuwn wet;

	snd_soc_cawd_set_dwvdata(&sof_audio_cawd_wt5682, ctx);

	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev,
					  &sof_audio_cawd_wt5682);
}

static const stwuct pwatfowm_device_id boawd_ids[] = {
	{
		.name = "sof_wt5682",
	},
	{
		.name = "cmw_wt1015_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1)),
	},
	{
		.name = "jsw_wt5682_wt1015",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1)),
	},
	{
		.name = "jsw_wt5682_mx98360",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1)),
	},
	{
		.name = "jsw_wt5682_wt1015p",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1)),
	},
	{
		.name = "jsw_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0)),
	},
	{
		.name = "jsw_wt5650",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1)),
	},
	{
		.name = "tgw_mx98357_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "tgw_wt1011_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "tgw_mx98373_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "adw_mx98373_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "adw_mx98357_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(2) |
					SOF_WT5682_NUM_HDMIDEV(4)),
	},
	{
		.name = "adw_max98390_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "adw_mx98360_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "adw_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "adw_wt1019_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "adw_wt5682_c1_h02",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(1) |
					SOF_WT5682_NUM_HDMIDEV(3) |
					/* SSP 0 and SSP 2 awe used fow HDMI IN */
					SOF_HDMI_CAPTUWE_SSP_MASK(0x5)),
	},
	{
		.name = "adw_wt5650",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "wpw_mx98357_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(2) |
					SOF_WT5682_NUM_HDMIDEV(4)),
	},
	{
		.name = "wpw_mx98360_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "wpw_wt1019_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(4) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "wpw_wt5682_c1_h02",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(1) |
					SOF_WT5682_NUM_HDMIDEV(3) |
					/* SSP 0 and SSP 2 awe used fow HDMI IN */
					SOF_HDMI_CAPTUWE_SSP_MASK(0x5)),
	},
	{
		.name = "mtw_mx98357_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(3) |
					SOF_BT_OFFWOAD_SSP(2) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{
		.name = "mtw_mx98360_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(0) |
					SOF_WT5682_SSP_AMP(1) |
					SOF_WT5682_NUM_HDMIDEV(3)),
	},
	{
		.name = "mtw_wt1019_wt5682",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(2) |
					SOF_WT5682_SSP_AMP(0) |
					SOF_WT5682_NUM_HDMIDEV(3)),
	},
	{
		.name = "mtw_wt5650",
		.dwivew_data = (kewnew_uwong_t)(SOF_WT5682_MCWK_EN |
					SOF_WT5682_SSP_CODEC(2) |
					SOF_WT5682_SSP_AMP(0) |
					SOF_WT5682_NUM_HDMIDEV(3) |
					SOF_BT_OFFWOAD_SSP(1) |
					SOF_SSP_BT_OFFWOAD_PWESENT),
	},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, boawd_ids);

static stwuct pwatfowm_dwivew sof_audio = {
	.pwobe = sof_audio_pwobe,
	.dwivew = {
		.name = "sof_wt5682",
		.pm = &snd_soc_pm_ops,
	},
	.id_tabwe = boawd_ids,
};
moduwe_pwatfowm_dwivew(sof_audio)

/* Moduwe infowmation */
MODUWE_DESCWIPTION("SOF Audio Machine dwivew");
MODUWE_AUTHOW("Bawd Wiao <bawd.wiao@intew.com>");
MODUWE_AUTHOW("Sathya Pwakash M W <sathya.pwakash.m.w@intew.com>");
MODUWE_AUTHOW("Bwent Wu <bwent.wu@intew.com>");
MODUWE_AUTHOW("Mac Chiang <mac.chiang@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_BOAWD_HEWPEWS);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_MAXIM_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_WEAWTEK_COMMON);
MODUWE_IMPOWT_NS(SND_SOC_INTEW_SOF_SSP_COMMON);
