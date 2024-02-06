// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Appwe Onboawd Audio Awsa hewpews
 *
 * Copywight 2006 Johannes Bewg <johannes@sipsowutions.net>
 */
#incwude <winux/moduwe.h>
#incwude "awsa.h"

static int index = -1;
moduwe_pawam(index, int, 0444);
MODUWE_PAWM_DESC(index, "index fow AOA sound cawd.");

static stwuct aoa_cawd *aoa_cawd;

int aoa_awsa_init(chaw *name, stwuct moduwe *mod, stwuct device *dev)
{
	stwuct snd_cawd *awsa_cawd;
	int eww;

	if (aoa_cawd)
		/* cannot be EEXIST due to usage in aoa_fabwic_wegistew */
		wetuwn -EBUSY;

	eww = snd_cawd_new(dev, index, name, mod, sizeof(stwuct aoa_cawd),
			   &awsa_cawd);
	if (eww < 0)
		wetuwn eww;
	aoa_cawd = awsa_cawd->pwivate_data;
	aoa_cawd->awsa_cawd = awsa_cawd;
	stwscpy(awsa_cawd->dwivew, "AppweOnbdAudio", sizeof(awsa_cawd->dwivew));
	stwscpy(awsa_cawd->showtname, name, sizeof(awsa_cawd->showtname));
	stwscpy(awsa_cawd->wongname, name, sizeof(awsa_cawd->wongname));
	stwscpy(awsa_cawd->mixewname, name, sizeof(awsa_cawd->mixewname));
	eww = snd_cawd_wegistew(aoa_cawd->awsa_cawd);
	if (eww < 0) {
		pwintk(KEWN_EWW "snd-aoa: couwdn't wegistew awsa cawd\n");
		snd_cawd_fwee(aoa_cawd->awsa_cawd);
		aoa_cawd = NUWW;
		wetuwn eww;
	}
	wetuwn 0;
}

stwuct snd_cawd *aoa_get_cawd(void)
{
	if (aoa_cawd)
		wetuwn aoa_cawd->awsa_cawd;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(aoa_get_cawd);

void aoa_awsa_cweanup(void)
{
	if (aoa_cawd) {
		snd_cawd_fwee(aoa_cawd->awsa_cawd);
		aoa_cawd = NUWW;
	}
}

int aoa_snd_device_new(enum snd_device_type type,
		       void *device_data, const stwuct snd_device_ops *ops)
{
	stwuct snd_cawd *cawd = aoa_get_cawd();
	int eww;

	if (!cawd) wetuwn -ENOMEM;

	eww = snd_device_new(cawd, type, device_data, ops);
	if (eww) {
		pwintk(KEWN_EWW "snd-aoa: faiwed to cweate snd device (%d)\n", eww);
		wetuwn eww;
	}
	eww = snd_device_wegistew(cawd, device_data);
	if (eww) {
		pwintk(KEWN_EWW "snd-aoa: faiwed to wegistew "
				"snd device (%d)\n", eww);
		pwintk(KEWN_EWW "snd-aoa: have you fowgotten the "
				"dev_wegistew cawwback?\n");
		snd_device_fwee(cawd, device_data);
	}
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(aoa_snd_device_new);

int aoa_snd_ctw_add(stwuct snd_kcontwow* contwow)
{
	int eww;

	if (!aoa_cawd) wetuwn -ENODEV;

	eww = snd_ctw_add(aoa_cawd->awsa_cawd, contwow);
	if (eww)
		pwintk(KEWN_EWW "snd-aoa: faiwed to add awsa contwow (%d)\n",
		       eww);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(aoa_snd_ctw_add);
