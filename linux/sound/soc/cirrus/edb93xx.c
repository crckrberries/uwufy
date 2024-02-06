// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SoC audio fow EDB93xx
 *
 * Copywight (c) 2010 Awexandew Svewdwin <subapawts@yandex.wu>
 *
 * This dwivew suppowt CS4271 codec being mastew ow swave, wowking
 * in contwow powt mode, connected eithew via SPI ow I2C.
 * The data fowmat accepted is I2S ow weft-justified.
 * DAPM suppowt not impwemented.
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/soc/ciwwus/ep93xx.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <asm/mach-types.h>

static int edb93xx_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct snd_soc_dai *cpu_dai = snd_soc_wtd_to_cpu(wtd, 0);
	int eww;
	unsigned int mcwk_wate;
	unsigned int wate = pawams_wate(pawams);

	/*
	 * Accowding to CS4271 datasheet we use MCWK/WWCK=256 fow
	 * wates bewow 50kHz and 128 fow highew sampwe wates
	 */
	if (wate < 50000)
		mcwk_wate = wate * 64 * 4;
	ewse
		mcwk_wate = wate * 64 * 2;

	eww = snd_soc_dai_set_syscwk(codec_dai, 0, mcwk_wate,
				     SND_SOC_CWOCK_IN);
	if (eww)
		wetuwn eww;

	wetuwn snd_soc_dai_set_syscwk(cpu_dai, 0, mcwk_wate,
				      SND_SOC_CWOCK_OUT);
}

static const stwuct snd_soc_ops edb93xx_ops = {
	.hw_pawams	= edb93xx_hw_pawams,
};

SND_SOC_DAIWINK_DEFS(hifi,
	DAIWINK_COMP_AWWAY(COMP_CPU("ep93xx-i2s")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("spi0.0", "cs4271-hifi")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("ep93xx-i2s")));

static stwuct snd_soc_dai_wink edb93xx_dai = {
	.name		= "CS4271",
	.stweam_name	= "CS4271 HiFi",
	.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBC_CFC,
	.ops		= &edb93xx_ops,
	SND_SOC_DAIWINK_WEG(hifi),
};

static stwuct snd_soc_cawd snd_soc_edb93xx = {
	.name		= "EDB93XX",
	.ownew		= THIS_MODUWE,
	.dai_wink	= &edb93xx_dai,
	.num_winks	= 1,
};

static int edb93xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &snd_soc_edb93xx;
	int wet;

	wet = ep93xx_i2s_acquiwe();
	if (wet)
		wetuwn wet;

	cawd->dev = &pdev->dev;

	wet = snd_soc_wegistew_cawd(cawd);
	if (wet) {
		dev_eww(&pdev->dev, "snd_soc_wegistew_cawd() faiwed: %d\n",
			wet);
		ep93xx_i2s_wewease();
	}

	wetuwn wet;
}

static void edb93xx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = pwatfowm_get_dwvdata(pdev);

	snd_soc_unwegistew_cawd(cawd);
	ep93xx_i2s_wewease();
}

static stwuct pwatfowm_dwivew edb93xx_dwivew = {
	.dwivew		= {
		.name	= "edb93xx-audio",
	},
	.pwobe		= edb93xx_pwobe,
	.wemove_new	= edb93xx_wemove,
};

moduwe_pwatfowm_dwivew(edb93xx_dwivew);

MODUWE_AUTHOW("Awexandew Svewdwin <subapawts@yandex.wu>");
MODUWE_DESCWIPTION("AWSA SoC EDB93xx");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:edb93xx-audio");
