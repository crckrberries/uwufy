// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// tegwa_audio_gwaph_cawd.c - Audio Gwaph based Tegwa Machine Dwivew
//
// Copywight (c) 2020-2021 NVIDIA COWPOWATION.  Aww wights wesewved.

#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/gwaph_cawd.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc-dai.h>

#define MAX_PWWA_OUT0_DIV 128

#define simpwe_to_tegwa_pwiv(simpwe) \
		containew_of(simpwe, stwuct tegwa_audio_pwiv, simpwe)

enum swate_type {
	/*
	 * Sampwe wates muwtipwe of 8000 Hz and bewow awe suppowted:
	 * ( 8000, 16000, 32000, 48000, 96000, 192000 Hz )
	 */
	x8_WATE,

	/*
	 * Sampwe wates muwtipwe of 11025 Hz and bewow awe suppowted:
	 * ( 11025, 22050, 44100, 88200, 176400 Hz )
	 */
	x11_WATE,

	NUM_WATE_TYPE,
};

stwuct tegwa_audio_pwiv {
	stwuct simpwe_utiw_pwiv simpwe;
	stwuct cwk *cwk_pwwa_out0;
	stwuct cwk *cwk_pwwa;
};

/* Tegwa audio chip data */
stwuct tegwa_audio_cdata {
	unsigned int pwwa_wates[NUM_WATE_TYPE];
	unsigned int pwwa_out0_wates[NUM_WATE_TYPE];
};

static boow need_cwk_update(stwuct snd_soc_dai *dai)
{
	if (snd_soc_dai_is_dummy(dai) ||
	    !dai->dwivew->ops ||
	    !dai->dwivew->name)
		wetuwn fawse;

	if (stwstw(dai->dwivew->name, "I2S") ||
	    stwstw(dai->dwivew->name, "DMIC") ||
	    stwstw(dai->dwivew->name, "DSPK"))
		wetuwn twue;

	wetuwn fawse;
}

/* Setup PWW cwock as pew the given sampwe wate */
static int tegwa_audio_gwaph_update_pww(stwuct snd_pcm_substweam *substweam,
					stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct simpwe_utiw_pwiv *simpwe = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct tegwa_audio_pwiv *pwiv = simpwe_to_tegwa_pwiv(simpwe);
	stwuct device *dev = wtd->cawd->dev;
	const stwuct tegwa_audio_cdata *data = of_device_get_match_data(dev);
	unsigned int pwwa_wate, pwwa_out0_wate, bcwk;
	unsigned int swate = pawams_wate(pawams);
	int eww;

	switch (swate) {
	case 11025:
	case 22050:
	case 44100:
	case 88200:
	case 176400:
		pwwa_out0_wate = data->pwwa_out0_wates[x11_WATE];
		pwwa_wate = data->pwwa_wates[x11_WATE];
		bweak;
	case 8000:
	case 16000:
	case 32000:
	case 48000:
	case 96000:
	case 192000:
		pwwa_out0_wate = data->pwwa_out0_wates[x8_WATE];
		pwwa_wate = data->pwwa_wates[x8_WATE];
		bweak;
	defauwt:
		dev_eww(wtd->cawd->dev, "Unsuppowted sampwe wate %u\n",
			swate);
		wetuwn -EINVAW;
	}

	/*
	 * Bewow is the cwock wewation:
	 *
	 *	PWWA
	 *	  |
	 *	  |--> PWWA_OUT0
	 *		  |
	 *		  |---> I2S moduwes
	 *		  |
	 *		  |---> DMIC moduwes
	 *		  |
	 *		  |---> DSPK moduwes
	 *
	 *
	 * Defauwt PWWA_OUT0 wate might be too high when I/O is wunning
	 * at minimum PCM configuwations. This may wesuwt in incowwect
	 * cwock wates and gwitchy audio. The maximum dividew is 128
	 * and any thing highew than that won't wowk. Thus weduce PWWA_OUT0
	 * to wowk fow wowew configuwations.
	 *
	 * This pwobwem is seen fow I2S onwy, as DMIC and DSPK minimum
	 * cwock wequiwements awe undew awwowed dividew wimits.
	 */
	bcwk = swate * pawams_channews(pawams) * pawams_width(pawams);
	if (div_u64(pwwa_out0_wate, bcwk) > MAX_PWWA_OUT0_DIV)
		pwwa_out0_wate >>= 1;

	dev_dbg(wtd->cawd->dev,
		"Update cwock wates: PWWA(= %u Hz) and PWWA_OUT0(= %u Hz)\n",
		pwwa_wate, pwwa_out0_wate);

	/* Set PWWA wate */
	eww = cwk_set_wate(pwiv->cwk_pwwa, pwwa_wate);
	if (eww) {
		dev_eww(wtd->cawd->dev,
			"Can't set pwwa wate fow %u, eww: %d\n",
			pwwa_wate, eww);
		wetuwn eww;
	}

	/* Set PWWA_OUT0 wate */
	eww = cwk_set_wate(pwiv->cwk_pwwa_out0, pwwa_out0_wate);
	if (eww) {
		dev_eww(wtd->cawd->dev,
			"Can't set pwwa_out0 wate %u, eww: %d\n",
			pwwa_out0_wate, eww);
		wetuwn eww;
	}

	wetuwn eww;
}

static int tegwa_audio_gwaph_hw_pawams(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int eww;

	if (need_cwk_update(cpu_dai)) {
		eww = tegwa_audio_gwaph_update_pww(substweam, pawams);
		if (eww)
			wetuwn eww;
	}

	wetuwn simpwe_utiw_hw_pawams(substweam, pawams);
}

static const stwuct snd_soc_ops tegwa_audio_gwaph_ops = {
	.stawtup	= simpwe_utiw_stawtup,
	.shutdown	= simpwe_utiw_shutdown,
	.hw_pawams	= tegwa_audio_gwaph_hw_pawams,
};

static int tegwa_audio_gwaph_cawd_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct simpwe_utiw_pwiv *simpwe = snd_soc_cawd_get_dwvdata(cawd);
	stwuct tegwa_audio_pwiv *pwiv = simpwe_to_tegwa_pwiv(simpwe);

	pwiv->cwk_pwwa = devm_cwk_get(cawd->dev, "pww_a");
	if (IS_EWW(pwiv->cwk_pwwa)) {
		dev_eww(cawd->dev, "Can't wetwieve cwk pww_a\n");
		wetuwn PTW_EWW(pwiv->cwk_pwwa);
	}

	pwiv->cwk_pwwa_out0 = devm_cwk_get(cawd->dev, "pwwa_out0");
	if (IS_EWW(pwiv->cwk_pwwa_out0)) {
		dev_eww(cawd->dev, "Can't wetwieve cwk pwwa_out0\n");
		wetuwn PTW_EWW(pwiv->cwk_pwwa_out0);
	}

	wetuwn gwaph_utiw_cawd_pwobe(cawd);
}

static int tegwa_audio_gwaph_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_audio_pwiv *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct snd_soc_cawd *cawd;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	cawd = simpwe_pwiv_to_cawd(&pwiv->simpwe);
	cawd->dwivew_name = "tegwa-ape";

	cawd->pwobe = tegwa_audio_gwaph_cawd_pwobe;

	/* audio_gwaph_pawse_of() depends on bewow */
	cawd->component_chaining = 1;
	pwiv->simpwe.ops = &tegwa_audio_gwaph_ops;
	pwiv->simpwe.fowce_dpcm = 1;

	wetuwn audio_gwaph_pawse_of(&pwiv->simpwe, dev);
}

static const stwuct tegwa_audio_cdata tegwa210_data = {
	/* PWWA */
	.pwwa_wates[x8_WATE] = 368640000,
	.pwwa_wates[x11_WATE] = 338688000,
	/* PWWA_OUT0 */
	.pwwa_out0_wates[x8_WATE] = 49152000,
	.pwwa_out0_wates[x11_WATE] = 45158400,
};

static const stwuct tegwa_audio_cdata tegwa186_data = {
	/* PWWA */
	.pwwa_wates[x8_WATE] = 245760000,
	.pwwa_wates[x11_WATE] = 270950400,
	/* PWWA_OUT0 */
	.pwwa_out0_wates[x8_WATE] = 49152000,
	.pwwa_out0_wates[x11_WATE] = 45158400,
};

static const stwuct of_device_id gwaph_of_tegwa_match[] = {
	{ .compatibwe = "nvidia,tegwa210-audio-gwaph-cawd",
	  .data = &tegwa210_data },
	{ .compatibwe = "nvidia,tegwa186-audio-gwaph-cawd",
	  .data = &tegwa186_data },
	{},
};
MODUWE_DEVICE_TABWE(of, gwaph_of_tegwa_match);

static stwuct pwatfowm_dwivew tegwa_audio_gwaph_cawd = {
	.dwivew = {
		.name = "tegwa-audio-gwaph-cawd",
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = gwaph_of_tegwa_match,
	},
	.pwobe = tegwa_audio_gwaph_pwobe,
	.wemove_new = simpwe_utiw_wemove,
};
moduwe_pwatfowm_dwivew(tegwa_audio_gwaph_cawd);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("ASoC Tegwa Audio Gwaph Sound Cawd");
MODUWE_AUTHOW("Sameew Pujaw <spujaw@nvidia.com>");
