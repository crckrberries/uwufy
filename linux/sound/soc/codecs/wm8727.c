// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wm8727.c
 *
 *  Cweated on: 15-Oct-2009
 *      Authow: neiw.jones@imgtec.com
 *
 * Copywight (C) 2009 Imagination Technowogies Wtd.
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>

static const stwuct snd_soc_dapm_widget wm8727_dapm_widgets[] = {
SND_SOC_DAPM_OUTPUT("VOUTW"),
SND_SOC_DAPM_OUTPUT("VOUTW"),
};

static const stwuct snd_soc_dapm_woute wm8727_dapm_woutes[] = {
	{ "VOUTW", NUWW, "Pwayback" },
	{ "VOUTW", NUWW, "Pwayback" },
};

/*
 * Note this is a simpwe chip with no configuwation intewface, sampwe wate is
 * detewmined automaticawwy by examining the Mastew cwock and Bit cwock watios
 */
#define WM8727_WATES  (SNDWV_PCM_WATE_32000 | SNDWV_PCM_WATE_44100 |\
			SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 |\
			SNDWV_PCM_WATE_192000)

static stwuct snd_soc_dai_dwivew wm8727_dai = {
	.name = "wm8727-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = WM8727_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE,
		},
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wm8727 = {
	.dapm_widgets		= wm8727_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wm8727_dapm_widgets),
	.dapm_woutes		= wm8727_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wm8727_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int wm8727_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_wm8727, &wm8727_dai, 1);
}

static stwuct pwatfowm_dwivew wm8727_codec_dwivew = {
	.dwivew = {
			.name = "wm8727",
	},

	.pwobe = wm8727_pwobe,
};

moduwe_pwatfowm_dwivew(wm8727_codec_dwivew);

MODUWE_DESCWIPTION("ASoC wm8727 dwivew");
MODUWE_AUTHOW("Neiw Jones");
MODUWE_WICENSE("GPW");
