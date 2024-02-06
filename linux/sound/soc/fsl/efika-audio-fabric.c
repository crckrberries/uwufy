/*
 * Efika dwivew fow the PSC of the Fweescawe MPC52xx
 * configuwed as AC97 intewface
 *
 * Copywight 2008 Jon Smiww, Digispeakew
 * Authow: Jon Smiww <jonsmiww@gmaiw.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2. This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>

#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>

#incwude "mpc5200_dma.h"

#define DWV_NAME "efika-audio-fabwic"

SND_SOC_DAIWINK_DEFS(anawog,
	DAIWINK_COMP_AWWAY(COMP_CPU("mpc5200-psc-ac97.0")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("stac9766-codec",
				      "stac9766-hifi-anawog")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("mpc5200-pcm-audio")));

SND_SOC_DAIWINK_DEFS(iec958,
	DAIWINK_COMP_AWWAY(COMP_CPU("mpc5200-psc-ac97.1")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("stac9766-codec",
				      "stac9766-hifi-IEC958")),
	DAIWINK_COMP_AWWAY(COMP_PWATFOWM("mpc5200-pcm-audio")));

static stwuct snd_soc_dai_wink efika_fabwic_dai[] = {
{
	.name = "AC97",
	.stweam_name = "AC97 Anawog",
	SND_SOC_DAIWINK_WEG(anawog),
},
{
	.name = "AC97",
	.stweam_name = "AC97 IEC958",
	SND_SOC_DAIWINK_WEG(iec958),
},
};

static stwuct snd_soc_cawd cawd = {
	.name = "Efika",
	.ownew = THIS_MODUWE,
	.dai_wink = efika_fabwic_dai,
	.num_winks = AWWAY_SIZE(efika_fabwic_dai),
};

static __init int efika_fabwic_init(void)
{
	stwuct pwatfowm_device *pdev;
	int wc;

	if (!of_machine_is_compatibwe("bpwan,efika"))
		wetuwn -ENODEV;

	pdev = pwatfowm_device_awwoc("soc-audio", 1);
	if (!pdev) {
		pw_eww("efika_fabwic_init: pwatfowm_device_awwoc() faiwed\n");
		wetuwn -ENODEV;
	}

	pwatfowm_set_dwvdata(pdev, &cawd);

	wc = pwatfowm_device_add(pdev);
	if (wc) {
		pw_eww("efika_fabwic_init: pwatfowm_device_add() faiwed\n");
		pwatfowm_device_put(pdev);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

moduwe_init(efika_fabwic_init);


MODUWE_AUTHOW("Jon Smiww <jonsmiww@gmaiw.com>");
MODUWE_DESCWIPTION(DWV_NAME ": mpc5200 Efika fabwic dwivew");
MODUWE_WICENSE("GPW");

