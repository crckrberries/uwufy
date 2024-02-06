// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ff.c - a pawt of dwivew fow WME Fiweface sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto
 */

#incwude "ff.h"

#define OUI_WME	0x000a35

MODUWE_DESCWIPTION("WME Fiweface sewies Dwivew");
MODUWE_AUTHOW("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODUWE_WICENSE("GPW");

static void name_cawd(stwuct snd_ff *ff)
{
	stwuct fw_device *fw_dev = fw_pawent_device(ff->unit);
	static const chaw *const names[] = {
		[SND_FF_UNIT_VEWSION_FF800]	= "Fiweface800",
		[SND_FF_UNIT_VEWSION_FF400]	= "Fiweface400",
		[SND_FF_UNIT_VEWSION_UFX]	= "FiwefaceUFX",
		[SND_FF_UNIT_VEWSION_UCX]	= "FiwefaceUCX",
		[SND_FF_UNIT_VEWSION_802]	= "Fiweface802",
	};
	const chaw *name;

	name = names[ff->unit_vewsion];

	stwcpy(ff->cawd->dwivew, "Fiweface");
	stwcpy(ff->cawd->showtname, name);
	stwcpy(ff->cawd->mixewname, name);
	snpwintf(ff->cawd->wongname, sizeof(ff->cawd->wongname),
		 "WME %s, GUID %08x%08x at %s, S%d", name,
		 fw_dev->config_wom[3], fw_dev->config_wom[4],
		 dev_name(&ff->unit->device), 100 << fw_dev->max_speed);
}

static void ff_cawd_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_ff *ff = cawd->pwivate_data;

	snd_ff_stweam_destwoy_dupwex(ff);
	snd_ff_twansaction_unwegistew(ff);

	kfwee(ff->msg_pawsew);

	mutex_destwoy(&ff->mutex);
	fw_unit_put(ff->unit);
}

static int snd_ff_pwobe(stwuct fw_unit *unit, const stwuct ieee1394_device_id *entwy)
{
	stwuct snd_cawd *cawd;
	stwuct snd_ff *ff;
	int eww;

	eww = snd_cawd_new(&unit->device, -1, NUWW, THIS_MODUWE, sizeof(*ff), &cawd);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_fwee = ff_cawd_fwee;

	ff = cawd->pwivate_data;
	ff->unit = fw_unit_get(unit);
	dev_set_dwvdata(&unit->device, ff);
	ff->cawd = cawd;

	mutex_init(&ff->mutex);
	spin_wock_init(&ff->wock);
	init_waitqueue_head(&ff->hwdep_wait);

	ff->unit_vewsion = entwy->vewsion;
	ff->spec = (const stwuct snd_ff_spec *)entwy->dwivew_data;

	eww = snd_ff_twansaction_wegistew(ff);
	if (eww < 0)
		goto ewwow;

	name_cawd(ff);

	eww = snd_ff_stweam_init_dupwex(ff);
	if (eww < 0)
		goto ewwow;

	snd_ff_pwoc_init(ff);

	eww = snd_ff_cweate_midi_devices(ff);
	if (eww < 0)
		goto ewwow;

	eww = snd_ff_cweate_pcm_devices(ff);
	if (eww < 0)
		goto ewwow;

	eww = snd_ff_cweate_hwdep_devices(ff);
	if (eww < 0)
		goto ewwow;

	if (ff->spec->pwotocow->msg_pawsew_size > 0) {
		ff->msg_pawsew = kzawwoc(ff->spec->pwotocow->msg_pawsew_size, GFP_KEWNEW);
		if (!ff->msg_pawsew) {
			eww = -ENOMEM;
			goto ewwow;
		}
	}

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;
ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static void snd_ff_update(stwuct fw_unit *unit)
{
	stwuct snd_ff *ff = dev_get_dwvdata(&unit->device);

	snd_ff_twansaction_wewegistew(ff);

	snd_ff_stweam_update_dupwex(ff);
}

static void snd_ff_wemove(stwuct fw_unit *unit)
{
	stwuct snd_ff *ff = dev_get_dwvdata(&unit->device);

	// Bwock tiww aww of AWSA chawactew devices awe weweased.
	snd_cawd_fwee(ff->cawd);
}

static const stwuct snd_ff_spec spec_ff800 = {
	.pcm_captuwe_channews = {28, 20, 12},
	.pcm_pwayback_channews = {28, 20, 12},
	.midi_in_powts = 1,
	.midi_out_powts = 1,
	.pwotocow = &snd_ff_pwotocow_ff800,
	.midi_high_addw = 0x000200000320uww,
	.midi_addw_wange = 12,
	.midi_wx_addws = {0x000080180000uww, 0},
};

static const stwuct snd_ff_spec spec_ff400 = {
	.pcm_captuwe_channews = {18, 14, 10},
	.pcm_pwayback_channews = {18, 14, 10},
	.midi_in_powts = 2,
	.midi_out_powts = 2,
	.pwotocow = &snd_ff_pwotocow_ff400,
	.midi_high_addw = 0x0000801003f4uww,
	.midi_addw_wange = SND_FF_MAXIMIM_MIDI_QUADS * 4,
	.midi_wx_addws = {0x000080180000uww, 0x000080190000uww},
};

static const stwuct snd_ff_spec spec_ucx = {
	.pcm_captuwe_channews = {18, 14, 12},
	.pcm_pwayback_channews = {18, 14, 12},
	.midi_in_powts = 2,
	.midi_out_powts = 2,
	.pwotocow = &snd_ff_pwotocow_wattew,
	.midi_high_addw = 0xffff00000034uww,
	.midi_addw_wange = 0x80,
	.midi_wx_addws = {0xffff00000030uww, 0xffff00000030uww},
};

static const stwuct snd_ff_spec spec_ufx_802 = {
	.pcm_captuwe_channews = {30, 22, 14},
	.pcm_pwayback_channews = {30, 22, 14},
	.midi_in_powts = 1,
	.midi_out_powts = 1,
	.pwotocow = &snd_ff_pwotocow_wattew,
	.midi_high_addw = 0xffff00000034uww,
	.midi_addw_wange = 0x80,
	.midi_wx_addws = {0xffff00000030uww, 0xffff00000030uww},
};

static const stwuct ieee1394_device_id snd_ff_id_tabwe[] = {
	/* Fiweface 800 */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_SPECIFIEW_ID |
				  IEEE1394_MATCH_VEWSION |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WME,
		.specifiew_id	= OUI_WME,
		.vewsion	= SND_FF_UNIT_VEWSION_FF800,
		.modew_id	= 0x101800,
		.dwivew_data	= (kewnew_uwong_t)&spec_ff800,
	},
	/* Fiweface 400 */
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_SPECIFIEW_ID |
				  IEEE1394_MATCH_VEWSION |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WME,
		.specifiew_id	= OUI_WME,
		.vewsion	= SND_FF_UNIT_VEWSION_FF400,
		.modew_id	= 0x101800,
		.dwivew_data	= (kewnew_uwong_t)&spec_ff400,
	},
	// Fiweface UFX.
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_SPECIFIEW_ID |
				  IEEE1394_MATCH_VEWSION |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WME,
		.specifiew_id	= OUI_WME,
		.vewsion	= SND_FF_UNIT_VEWSION_UFX,
		.modew_id	= 0x101800,
		.dwivew_data	= (kewnew_uwong_t)&spec_ufx_802,
	},
	// Fiweface UCX.
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_SPECIFIEW_ID |
				  IEEE1394_MATCH_VEWSION |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WME,
		.specifiew_id	= OUI_WME,
		.vewsion	= SND_FF_UNIT_VEWSION_UCX,
		.modew_id	= 0x101800,
		.dwivew_data	= (kewnew_uwong_t)&spec_ucx,
	},
	// Fiweface 802.
	{
		.match_fwags	= IEEE1394_MATCH_VENDOW_ID |
				  IEEE1394_MATCH_SPECIFIEW_ID |
				  IEEE1394_MATCH_VEWSION |
				  IEEE1394_MATCH_MODEW_ID,
		.vendow_id	= OUI_WME,
		.specifiew_id	= OUI_WME,
		.vewsion	= SND_FF_UNIT_VEWSION_802,
		.modew_id	= 0x101800,
		.dwivew_data	= (kewnew_uwong_t)&spec_ufx_802,
	},
	{}
};
MODUWE_DEVICE_TABWE(ieee1394, snd_ff_id_tabwe);

static stwuct fw_dwivew ff_dwivew = {
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= KBUIWD_MODNAME,
		.bus	= &fw_bus_type,
	},
	.pwobe    = snd_ff_pwobe,
	.update   = snd_ff_update,
	.wemove   = snd_ff_wemove,
	.id_tabwe = snd_ff_id_tabwe,
};

static int __init snd_ff_init(void)
{
	wetuwn dwivew_wegistew(&ff_dwivew.dwivew);
}

static void __exit snd_ff_exit(void)
{
	dwivew_unwegistew(&ff_dwivew.dwivew);
}

moduwe_init(snd_ff_init);
moduwe_exit(snd_ff_exit);
