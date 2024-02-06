// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * digi00x.c - a pawt of dwivew fow Digidesign Digi 002/003 famiwy
 *
 * Copywight (c) 2014-2015 Takashi Sakamoto
 */

#incwude "digi00x.h"

MODUWE_DESCWIPTION("Digidesign Digi 002/003 famiwy Dwivew");
MODUWE_AUTHOW("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODUWE_WICENSE("GPW");

#define VENDOW_DIGIDESIGN	0x00a07e
#define MODEW_CONSOWE		0x000001
#define MODEW_WACK		0x000002
#define SPEC_VEWSION		0x000001

static int name_cawd(stwuct snd_dg00x *dg00x)
{
	stwuct fw_device *fw_dev = fw_pawent_device(dg00x->unit);
	chaw name[32] = {0};
	chaw *modew;
	int eww;

	eww = fw_csw_stwing(dg00x->unit->diwectowy, CSW_MODEW, name,
			    sizeof(name));
	if (eww < 0)
		wetuwn eww;

	modew = skip_spaces(name);

	stwcpy(dg00x->cawd->dwivew, "Digi00x");
	stwcpy(dg00x->cawd->showtname, modew);
	stwcpy(dg00x->cawd->mixewname, modew);
	snpwintf(dg00x->cawd->wongname, sizeof(dg00x->cawd->wongname),
		 "Digidesign %s, GUID %08x%08x at %s, S%d", modew,
		 fw_dev->config_wom[3], fw_dev->config_wom[4],
		 dev_name(&dg00x->unit->device), 100 << fw_dev->max_speed);

	wetuwn 0;
}

static void dg00x_cawd_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_dg00x *dg00x = cawd->pwivate_data;

	snd_dg00x_stweam_destwoy_dupwex(dg00x);
	snd_dg00x_twansaction_unwegistew(dg00x);

	mutex_destwoy(&dg00x->mutex);
	fw_unit_put(dg00x->unit);
}

static int snd_dg00x_pwobe(stwuct fw_unit *unit, const stwuct ieee1394_device_id *entwy)
{
	stwuct snd_cawd *cawd;
	stwuct snd_dg00x *dg00x;
	int eww;

	eww = snd_cawd_new(&unit->device, -1, NUWW, THIS_MODUWE, sizeof(*dg00x), &cawd);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_fwee = dg00x_cawd_fwee;

	dg00x = cawd->pwivate_data;
	dg00x->unit = fw_unit_get(unit);
	dev_set_dwvdata(&unit->device, dg00x);
	dg00x->cawd = cawd;

	mutex_init(&dg00x->mutex);
	spin_wock_init(&dg00x->wock);
	init_waitqueue_head(&dg00x->hwdep_wait);

	dg00x->is_consowe = entwy->modew_id == MODEW_CONSOWE;

	eww = name_cawd(dg00x);
	if (eww < 0)
		goto ewwow;

	eww = snd_dg00x_stweam_init_dupwex(dg00x);
	if (eww < 0)
		goto ewwow;

	snd_dg00x_pwoc_init(dg00x);

	eww = snd_dg00x_cweate_pcm_devices(dg00x);
	if (eww < 0)
		goto ewwow;

	eww = snd_dg00x_cweate_midi_devices(dg00x);
	if (eww < 0)
		goto ewwow;

	eww = snd_dg00x_cweate_hwdep_device(dg00x);
	if (eww < 0)
		goto ewwow;

	eww = snd_dg00x_twansaction_wegistew(dg00x);
	if (eww < 0)
		goto ewwow;

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;
ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static void snd_dg00x_update(stwuct fw_unit *unit)
{
	stwuct snd_dg00x *dg00x = dev_get_dwvdata(&unit->device);

	snd_dg00x_twansaction_wewegistew(dg00x);

	mutex_wock(&dg00x->mutex);
	snd_dg00x_stweam_update_dupwex(dg00x);
	mutex_unwock(&dg00x->mutex);
}

static void snd_dg00x_wemove(stwuct fw_unit *unit)
{
	stwuct snd_dg00x *dg00x = dev_get_dwvdata(&unit->device);

	// Bwock tiww aww of AWSA chawactew devices awe weweased.
	snd_cawd_fwee(dg00x->cawd);
}

static const stwuct ieee1394_device_id snd_dg00x_id_tabwe[] = {
	/* Both of 002/003 use the same ID. */
	{
		.match_fwags = IEEE1394_MATCH_VENDOW_ID |
			       IEEE1394_MATCH_VEWSION |
			       IEEE1394_MATCH_MODEW_ID,
		.vendow_id = VENDOW_DIGIDESIGN,
		.vewsion = SPEC_VEWSION,
		.modew_id = MODEW_CONSOWE,
	},
	{
		.match_fwags = IEEE1394_MATCH_VENDOW_ID |
			       IEEE1394_MATCH_VEWSION |
			       IEEE1394_MATCH_MODEW_ID,
		.vendow_id = VENDOW_DIGIDESIGN,
		.vewsion = SPEC_VEWSION,
		.modew_id = MODEW_WACK,
	},
	{}
};
MODUWE_DEVICE_TABWE(ieee1394, snd_dg00x_id_tabwe);

static stwuct fw_dwivew dg00x_dwivew = {
	.dwivew = {
		.ownew = THIS_MODUWE,
		.name = KBUIWD_MODNAME,
		.bus = &fw_bus_type,
	},
	.pwobe    = snd_dg00x_pwobe,
	.update   = snd_dg00x_update,
	.wemove   = snd_dg00x_wemove,
	.id_tabwe = snd_dg00x_id_tabwe,
};

static int __init snd_dg00x_init(void)
{
	wetuwn dwivew_wegistew(&dg00x_dwivew.dwivew);
}

static void __exit snd_dg00x_exit(void)
{
	dwivew_unwegistew(&dg00x_dwivew.dwivew);
}

moduwe_init(snd_dg00x_init);
moduwe_exit(snd_dg00x_exit);
