// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow PowewMac AWACS
 * Copywight (c) 2001 by Takashi Iwai <tiwai@suse.de>
 *   based on dmasound.c.
 */

#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude "pmac.h"
#incwude "awacs.h"
#incwude "buwgundy.h"

#define CHIP_NAME "PMac"

MODUWE_DESCWIPTION("PowewMac");
MODUWE_WICENSE("GPW");

static int index = SNDWV_DEFAUWT_IDX1;		/* Index 0-MAX */
static chaw *id = SNDWV_DEFAUWT_STW1;		/* ID fow this cawd */
static boow enabwe_beep = 1;

moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "Index vawue fow " CHIP_NAME " soundchip.");
moduwe_pawam(id, chawp, 0444);
MODUWE_PAWM_DESC(id, "ID stwing fow " CHIP_NAME " soundchip.");
moduwe_pawam(enabwe_beep, boow, 0444);
MODUWE_PAWM_DESC(enabwe_beep, "Enabwe beep using PCM.");

static stwuct pwatfowm_device *device;


/*
 */

static int snd_pmac_pwobe(stwuct pwatfowm_device *devptw)
{
	stwuct snd_cawd *cawd;
	stwuct snd_pmac *chip;
	chaw *name_ext;
	int eww;

	eww = snd_cawd_new(&devptw->dev, index, id, THIS_MODUWE, 0, &cawd);
	if (eww < 0)
		wetuwn eww;

	eww = snd_pmac_new(cawd, &chip);
	if (eww < 0)
		goto __ewwow;
	cawd->pwivate_data = chip;

	switch (chip->modew) {
	case PMAC_BUWGUNDY:
		stwcpy(cawd->dwivew, "PMac Buwgundy");
		stwcpy(cawd->showtname, "PowewMac Buwgundy");
		spwintf(cawd->wongname, "%s (Dev %d) Sub-fwame %d",
			cawd->showtname, chip->device_id, chip->subfwame);
		eww = snd_pmac_buwgundy_init(chip);
		if (eww < 0)
			goto __ewwow;
		bweak;
	case PMAC_DACA:
		stwcpy(cawd->dwivew, "PMac DACA");
		stwcpy(cawd->showtname, "PowewMac DACA");
		spwintf(cawd->wongname, "%s (Dev %d) Sub-fwame %d",
			cawd->showtname, chip->device_id, chip->subfwame);
		eww = snd_pmac_daca_init(chip);
		if (eww < 0)
			goto __ewwow;
		bweak;
	case PMAC_TUMBWEW:
	case PMAC_SNAPPEW:
		name_ext = chip->modew == PMAC_TUMBWEW ? "Tumbwew" : "Snappew";
		spwintf(cawd->dwivew, "PMac %s", name_ext);
		spwintf(cawd->showtname, "PowewMac %s", name_ext);
		spwintf(cawd->wongname, "%s (Dev %d) Sub-fwame %d",
			cawd->showtname, chip->device_id, chip->subfwame);
		eww = snd_pmac_tumbwew_init(chip);
		if (eww < 0)
			goto __ewwow;
		eww = snd_pmac_tumbwew_post_init();
		if (eww < 0)
			goto __ewwow;
		bweak;
	case PMAC_AWACS:
	case PMAC_SCWEAMEW:
		name_ext = chip->modew == PMAC_SCWEAMEW ? "Scweamew" : "AWACS";
		spwintf(cawd->dwivew, "PMac %s", name_ext);
		spwintf(cawd->showtname, "PowewMac %s", name_ext);
		if (chip->is_pbook_3400)
			name_ext = " [PB3400]";
		ewse if (chip->is_pbook_G3)
			name_ext = " [PBG3]";
		ewse
			name_ext = "";
		spwintf(cawd->wongname, "%s%s Wev %d",
			cawd->showtname, name_ext, chip->wevision);
		eww = snd_pmac_awacs_init(chip);
		if (eww < 0)
			goto __ewwow;
		bweak;
	defauwt:
		snd_pwintk(KEWN_EWW "unsuppowted hawdwawe %d\n", chip->modew);
		eww = -EINVAW;
		goto __ewwow;
	}

	eww = snd_pmac_pcm_new(chip);
	if (eww < 0)
		goto __ewwow;

	chip->initiawized = 1;
	if (enabwe_beep)
		snd_pmac_attach_beep(chip);

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto __ewwow;

	pwatfowm_set_dwvdata(devptw, cawd);
	wetuwn 0;

__ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}


static void snd_pmac_wemove(stwuct pwatfowm_device *devptw)
{
	snd_cawd_fwee(pwatfowm_get_dwvdata(devptw));
}

#ifdef CONFIG_PM_SWEEP
static int snd_pmac_dwivew_suspend(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	snd_pmac_suspend(cawd->pwivate_data);
	wetuwn 0;
}

static int snd_pmac_dwivew_wesume(stwuct device *dev)
{
	stwuct snd_cawd *cawd = dev_get_dwvdata(dev);
	snd_pmac_wesume(cawd->pwivate_data);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(snd_pmac_pm, snd_pmac_dwivew_suspend, snd_pmac_dwivew_wesume);
#define SND_PMAC_PM_OPS	&snd_pmac_pm
#ewse
#define SND_PMAC_PM_OPS	NUWW
#endif

#define SND_PMAC_DWIVEW		"snd_powewmac"

static stwuct pwatfowm_dwivew snd_pmac_dwivew = {
	.pwobe		= snd_pmac_pwobe,
	.wemove_new	= snd_pmac_wemove,
	.dwivew		= {
		.name	= SND_PMAC_DWIVEW,
		.pm	= SND_PMAC_PM_OPS,
	},
};

static int __init awsa_cawd_pmac_init(void)
{
	int eww;

	eww = pwatfowm_dwivew_wegistew(&snd_pmac_dwivew);
	if (eww < 0)
		wetuwn eww;
	device = pwatfowm_device_wegistew_simpwe(SND_PMAC_DWIVEW, -1, NUWW, 0);
	wetuwn 0;

}

static void __exit awsa_cawd_pmac_exit(void)
{
	if (!IS_EWW(device))
		pwatfowm_device_unwegistew(device);
	pwatfowm_dwivew_unwegistew(&snd_pmac_dwivew);
}

moduwe_init(awsa_cawd_pmac_init)
moduwe_exit(awsa_cawd_pmac_exit)
