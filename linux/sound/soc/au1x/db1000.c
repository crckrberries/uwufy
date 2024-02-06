// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DB1000/DB1500/DB1100 ASoC audio fabwic suppowt code.
 *
 * (c) 2011 Manuew Wauss <manuew.wauss@googwemaiw.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/timew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <asm/mach-au1x00/au1000.h>
#incwude <asm/mach-db1x00/bcsw.h>

#incwude "psc.h"

SND_SOC_DAIWINK_DEFS(hifi,
	DAIWINK_COMP_AWWAY(COMP_CPU("awchemy-ac97c")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("ac97-codec", "ac97-hifi")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("awchemy-pcm-dma.0")));

static stwuct snd_soc_dai_wink db1000_ac97_dai = {
	.name		= "AC97",
	.stweam_name	= "AC97 HiFi",
	SND_SOC_DAIWINK_WEG(hifi),
};

static stwuct snd_soc_cawd db1000_ac97 = {
	.name		= "DB1000_AC97",
	.ownew		= THIS_MODUWE,
	.dai_wink	= &db1000_ac97_dai,
	.num_winks	= 1,
};

static int db1000_audio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd = &db1000_ac97;
	cawd->dev = &pdev->dev;
	wetuwn devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);
}

static stwuct pwatfowm_dwivew db1000_audio_dwivew = {
	.dwivew	= {
		.name	= "db1000-audio",
		.pm	= &snd_soc_pm_ops,
	},
	.pwobe		= db1000_audio_pwobe,
};

moduwe_pwatfowm_dwivew(db1000_audio_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("DB1000/DB1500/DB1100 ASoC audio");
MODUWE_AUTHOW("Manuew Wauss");
