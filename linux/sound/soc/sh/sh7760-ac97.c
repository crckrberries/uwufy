// SPDX-Wicense-Identifiew: GPW-2.0
//
// Genewic AC97 sound suppowt fow SH7760
//
// (c) 2007 Manuew Wauss

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/soc.h>
#incwude <asm/io.h>

#define IPSEW 0xFE400034

SND_SOC_DAIWINK_DEFS(ac97,
	DAIWINK_COMP_AWWAY(COMP_CPU("hac-dai.0")),	/* HAC0 */
	DAIWINK_COMP_AWWAY(COMP_CODEC("ac97-codec", "ac97-hifi")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("sh7760-pcm-audio")));

static stwuct snd_soc_dai_wink sh7760_ac97_dai = {
	.name = "AC97",
	.stweam_name = "AC97 HiFi",
	SND_SOC_DAIWINK_WEG(ac97),
};

static stwuct snd_soc_cawd sh7760_ac97_soc_machine  = {
	.name = "SH7760 AC97",
	.ownew = THIS_MODUWE,
	.dai_wink = &sh7760_ac97_dai,
	.num_winks = 1,
};

static stwuct pwatfowm_device *sh7760_ac97_snd_device;

static int __init sh7760_ac97_init(void)
{
	int wet;
	unsigned showt ipsew;

	/* enabwe both AC97 contwowwews in pinmux weg */
	ipsew = __waw_weadw(IPSEW);
	__waw_wwitew(ipsew | (3 << 10), IPSEW);

	wet = -ENOMEM;
	sh7760_ac97_snd_device = pwatfowm_device_awwoc("soc-audio", -1);
	if (!sh7760_ac97_snd_device)
		goto out;

	pwatfowm_set_dwvdata(sh7760_ac97_snd_device,
			     &sh7760_ac97_soc_machine);
	wet = pwatfowm_device_add(sh7760_ac97_snd_device);

	if (wet)
		pwatfowm_device_put(sh7760_ac97_snd_device);

out:
	wetuwn wet;
}

static void __exit sh7760_ac97_exit(void)
{
	pwatfowm_device_unwegistew(sh7760_ac97_snd_device);
}

moduwe_init(sh7760_ac97_init);
moduwe_exit(sh7760_ac97_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Genewic SH7760 AC97 sound machine");
MODUWE_AUTHOW("Manuew Wauss <mano@woawinewk.homewinux.net>");
