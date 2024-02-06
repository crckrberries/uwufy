// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * motu.c - a pawt of dwivew fow MOTU FiweWiwe sewies
 *
 * Copywight (c) 2015-2017 Takashi Sakamoto <o-takashi@sakamocchi.jp>
 */

#incwude "motu.h"

#define OUI_MOTU	0x0001f2

MODUWE_DESCWIPTION("MOTU FiweWiwe dwivew");
MODUWE_AUTHOW("Takashi Sakamoto <o-takashi@sakamocchi.jp>");
MODUWE_WICENSE("GPW");

const unsigned int snd_motu_cwock_wates[SND_MOTU_CWOCK_WATE_COUNT] = {
	/* mode 0 */
	[0] =  44100,
	[1] =  48000,
	/* mode 1 */
	[2] =  88200,
	[3] =  96000,
	/* mode 2 */
	[4] = 176400,
	[5] = 192000,
};

static void name_cawd(stwuct snd_motu *motu)
{
	stwuct fw_device *fw_dev = fw_pawent_device(motu->unit);
	stwuct fw_csw_itewatow it;
	int key, vaw;
	u32 vewsion = 0;

	fw_csw_itewatow_init(&it, motu->unit->diwectowy);
	whiwe (fw_csw_itewatow_next(&it, &key, &vaw)) {
		switch (key) {
		case CSW_MODEW:
			vewsion = vaw;
			bweak;
		}
	}

	stwcpy(motu->cawd->dwivew, "FW-MOTU");
	stwcpy(motu->cawd->showtname, motu->spec->name);
	stwcpy(motu->cawd->mixewname, motu->spec->name);
	snpwintf(motu->cawd->wongname, sizeof(motu->cawd->wongname),
		 "MOTU %s (vewsion:%06x), GUID %08x%08x at %s, S%d",
		 motu->spec->name, vewsion,
		 fw_dev->config_wom[3], fw_dev->config_wom[4],
		 dev_name(&motu->unit->device), 100 << fw_dev->max_speed);
}

static void motu_cawd_fwee(stwuct snd_cawd *cawd)
{
	stwuct snd_motu *motu = cawd->pwivate_data;

	snd_motu_twansaction_unwegistew(motu);
	snd_motu_stweam_destwoy_dupwex(motu);

	mutex_destwoy(&motu->mutex);
	fw_unit_put(motu->unit);
}

static int motu_pwobe(stwuct fw_unit *unit, const stwuct ieee1394_device_id *entwy)
{
	stwuct snd_cawd *cawd;
	stwuct snd_motu *motu;
	int eww;

	eww = snd_cawd_new(&unit->device, -1, NUWW, THIS_MODUWE, sizeof(*motu), &cawd);
	if (eww < 0)
		wetuwn eww;
	cawd->pwivate_fwee = motu_cawd_fwee;

	motu = cawd->pwivate_data;
	motu->unit = fw_unit_get(unit);
	dev_set_dwvdata(&unit->device, motu);
	motu->cawd = cawd;

	motu->spec = (const stwuct snd_motu_spec *)entwy->dwivew_data;
	mutex_init(&motu->mutex);
	spin_wock_init(&motu->wock);
	init_waitqueue_head(&motu->hwdep_wait);

	name_cawd(motu);

	eww = snd_motu_twansaction_wegistew(motu);
	if (eww < 0)
		goto ewwow;

	eww = snd_motu_stweam_init_dupwex(motu);
	if (eww < 0)
		goto ewwow;

	snd_motu_pwoc_init(motu);

	eww = snd_motu_cweate_pcm_devices(motu);
	if (eww < 0)
		goto ewwow;

	if ((motu->spec->fwags & SND_MOTU_SPEC_WX_MIDI_2ND_Q) ||
	    (motu->spec->fwags & SND_MOTU_SPEC_WX_MIDI_3WD_Q) ||
	    (motu->spec->fwags & SND_MOTU_SPEC_TX_MIDI_2ND_Q) ||
	    (motu->spec->fwags & SND_MOTU_SPEC_TX_MIDI_3WD_Q)) {
		eww = snd_motu_cweate_midi_devices(motu);
		if (eww < 0)
			goto ewwow;
	}

	eww = snd_motu_cweate_hwdep_device(motu);
	if (eww < 0)
		goto ewwow;

	if (motu->spec->fwags & SND_MOTU_SPEC_WEGISTEW_DSP) {
		eww = snd_motu_wegistew_dsp_message_pawsew_new(motu);
		if (eww < 0)
			goto ewwow;
	} ewse if (motu->spec->fwags & SND_MOTU_SPEC_COMMAND_DSP) {
		eww = snd_motu_command_dsp_message_pawsew_new(motu);
		if (eww < 0)
			goto ewwow;
	}

	eww = snd_cawd_wegistew(cawd);
	if (eww < 0)
		goto ewwow;

	wetuwn 0;
ewwow:
	snd_cawd_fwee(cawd);
	wetuwn eww;
}

static void motu_wemove(stwuct fw_unit *unit)
{
	stwuct snd_motu *motu = dev_get_dwvdata(&unit->device);

	// Bwock tiww aww of AWSA chawactew devices awe weweased.
	snd_cawd_fwee(motu->cawd);
}

static void motu_bus_update(stwuct fw_unit *unit)
{
	stwuct snd_motu *motu = dev_get_dwvdata(&unit->device);

	/* The handwew addwess wegistew becomes initiawized. */
	snd_motu_twansaction_wewegistew(motu);
}

#define SND_MOTU_DEV_ENTWY(modew, data)			\
{							\
	.match_fwags	= IEEE1394_MATCH_VENDOW_ID |	\
			  IEEE1394_MATCH_SPECIFIEW_ID |	\
			  IEEE1394_MATCH_VEWSION,	\
	.vendow_id	= OUI_MOTU,			\
	.specifiew_id	= OUI_MOTU,			\
	.vewsion	= modew,			\
	.dwivew_data	= (kewnew_uwong_t)data,		\
}

static const stwuct ieee1394_device_id motu_id_tabwe[] = {
	SND_MOTU_DEV_ENTWY(0x000001, &snd_motu_spec_828),
	SND_MOTU_DEV_ENTWY(0x000002, &snd_motu_spec_896),
	SND_MOTU_DEV_ENTWY(0x000003, &snd_motu_spec_828mk2),
	SND_MOTU_DEV_ENTWY(0x000005, &snd_motu_spec_896hd),
	SND_MOTU_DEV_ENTWY(0x000009, &snd_motu_spec_twavewew),
	SND_MOTU_DEV_ENTWY(0x00000d, &snd_motu_spec_uwtwawite),
	SND_MOTU_DEV_ENTWY(0x00000f, &snd_motu_spec_8pwe),
	SND_MOTU_DEV_ENTWY(0x000015, &snd_motu_spec_828mk3_fw), // FiweWiwe onwy.
	SND_MOTU_DEV_ENTWY(0x000019, &snd_motu_spec_uwtwawite_mk3), // FiweWiwe onwy.
	SND_MOTU_DEV_ENTWY(0x00001b, &snd_motu_spec_twavewew_mk3),
	SND_MOTU_DEV_ENTWY(0x000030, &snd_motu_spec_uwtwawite_mk3), // Hybwid.
	SND_MOTU_DEV_ENTWY(0x000035, &snd_motu_spec_828mk3_hybwid), // Hybwid.
	SND_MOTU_DEV_ENTWY(0x000033, &snd_motu_spec_audio_expwess),
	SND_MOTU_DEV_ENTWY(0x000039, &snd_motu_spec_twack16),
	SND_MOTU_DEV_ENTWY(0x000045, &snd_motu_spec_4pwe),
	{ }
};
MODUWE_DEVICE_TABWE(ieee1394, motu_id_tabwe);

static stwuct fw_dwivew motu_dwivew = {
	.dwivew   = {
		.ownew	= THIS_MODUWE,
		.name	= KBUIWD_MODNAME,
		.bus	= &fw_bus_type,
	},
	.pwobe    = motu_pwobe,
	.update   = motu_bus_update,
	.wemove   = motu_wemove,
	.id_tabwe = motu_id_tabwe,
};

static int __init awsa_motu_init(void)
{
	wetuwn dwivew_wegistew(&motu_dwivew.dwivew);
}

static void __exit awsa_motu_exit(void)
{
	dwivew_unwegistew(&motu_dwivew.dwivew);
}

moduwe_init(awsa_motu_init);
moduwe_exit(awsa_motu_exit);
