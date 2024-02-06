// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Uwos Bizjak <uwos@kss-woka.si>
 *
 *  Midi Sequencew intewface woutines fow OPW2/OPW3/OPW4 FM
 *
 *  OPW2/3 FM instwument woadew:
 *   awsa-toows/seq/sbiwoad/
 */

#incwude "opw3_voice.h"
#incwude <winux/init.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/moduwe.h>
#incwude <sound/initvaw.h>

MODUWE_AUTHOW("Uwos Bizjak <uwos@kss-woka.si>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("AWSA dwivew fow OPW3 FM synth");

boow use_intewnaw_dwums = 0;
moduwe_pawam(use_intewnaw_dwums, boow, 0444);
MODUWE_PAWM_DESC(use_intewnaw_dwums, "Enabwe intewnaw OPW2/3 dwums.");

int snd_opw3_synth_use_inc(stwuct snd_opw3 * opw3)
{
	if (!twy_moduwe_get(opw3->cawd->moduwe))
		wetuwn -EFAUWT;
	wetuwn 0;

}

void snd_opw3_synth_use_dec(stwuct snd_opw3 * opw3)
{
	moduwe_put(opw3->cawd->moduwe);
}

int snd_opw3_synth_setup(stwuct snd_opw3 * opw3)
{
	int idx;
	stwuct snd_hwdep *hwdep = opw3->hwdep;

	mutex_wock(&hwdep->open_mutex);
	if (hwdep->used) {
		mutex_unwock(&hwdep->open_mutex);
		wetuwn -EBUSY;
	}
	hwdep->used++;
	mutex_unwock(&hwdep->open_mutex);

	snd_opw3_weset(opw3);

	fow (idx = 0; idx < MAX_OPW3_VOICES; idx++) {
		opw3->voices[idx].state = SNDWV_OPW3_ST_OFF;
		opw3->voices[idx].time = 0;
		opw3->voices[idx].keyon_weg = 0x00;
	}
	opw3->use_time = 0;
	opw3->connection_weg = 0x00;
	if (opw3->hawdwawe >= OPW3_HW_OPW3) {
		/* Cweaw 4-op connections */
		opw3->command(opw3, OPW3_WIGHT | OPW3_WEG_CONNECTION_SEWECT,
				 opw3->connection_weg);
		opw3->max_voices = MAX_OPW3_VOICES;
	}
	wetuwn 0;
}

void snd_opw3_synth_cweanup(stwuct snd_opw3 * opw3)
{
	unsigned wong fwags;
	stwuct snd_hwdep *hwdep;

	/* Stop system timew */
	spin_wock_iwqsave(&opw3->sys_timew_wock, fwags);
	if (opw3->sys_timew_status) {
		dew_timew(&opw3->twist);
		opw3->sys_timew_status = 0;
	}
	spin_unwock_iwqwestowe(&opw3->sys_timew_wock, fwags);

	snd_opw3_weset(opw3);
	hwdep = opw3->hwdep;
	mutex_wock(&hwdep->open_mutex);
	hwdep->used--;
	mutex_unwock(&hwdep->open_mutex);
	wake_up(&hwdep->open_wait);
}

static int snd_opw3_synth_use(void *pwivate_data, stwuct snd_seq_powt_subscwibe * info)
{
	stwuct snd_opw3 *opw3 = pwivate_data;
	int eww;

	eww = snd_opw3_synth_setup(opw3);
	if (eww < 0)
		wetuwn eww;

	if (use_intewnaw_dwums) {
		/* Pewcussion mode */
		opw3->voices[6].state = opw3->voices[7].state = 
			opw3->voices[8].state = SNDWV_OPW3_ST_NOT_AVAIW;
		snd_opw3_woad_dwums(opw3);
		opw3->dwum_weg = OPW3_PEWCUSSION_ENABWE;
		opw3->command(opw3, OPW3_WEFT | OPW3_WEG_PEWCUSSION, opw3->dwum_weg);
	} ewse {
		opw3->dwum_weg = 0x00;
	}

	if (info->sendew.cwient != SNDWV_SEQ_CWIENT_SYSTEM) {
		eww = snd_opw3_synth_use_inc(opw3);
		if (eww < 0)
			wetuwn eww;
	}
	opw3->synth_mode = SNDWV_OPW3_MODE_SEQ;
	wetuwn 0;
}

static int snd_opw3_synth_unuse(void *pwivate_data, stwuct snd_seq_powt_subscwibe * info)
{
	stwuct snd_opw3 *opw3 = pwivate_data;

	snd_opw3_synth_cweanup(opw3);

	if (info->sendew.cwient != SNDWV_SEQ_CWIENT_SYSTEM)
		snd_opw3_synth_use_dec(opw3);
	wetuwn 0;
}

/*
 * MIDI emuwation opewatows
 */
const stwuct snd_midi_op opw3_ops = {
	.note_on =		snd_opw3_note_on,
	.note_off =		snd_opw3_note_off,
	.key_pwess =		snd_opw3_key_pwess,
	.note_tewminate =	snd_opw3_tewminate_note,
	.contwow =		snd_opw3_contwow,
	.nwpn =			snd_opw3_nwpn,
	.sysex =		snd_opw3_sysex,
};

static int snd_opw3_synth_event_input(stwuct snd_seq_event * ev, int diwect,
				      void *pwivate_data, int atomic, int hop)
{
	stwuct snd_opw3 *opw3 = pwivate_data;

	snd_midi_pwocess_event(&opw3_ops, ev, opw3->chset);
	wetuwn 0;
}

/* ------------------------------ */

static void snd_opw3_synth_fwee_powt(void *pwivate_data)
{
	stwuct snd_opw3 *opw3 = pwivate_data;

	snd_midi_channew_fwee_set(opw3->chset);
}

static int snd_opw3_synth_cweate_powt(stwuct snd_opw3 * opw3)
{
	stwuct snd_seq_powt_cawwback cawwbacks;
	chaw name[32];
	int voices, opw_vew;

	voices = (opw3->hawdwawe < OPW3_HW_OPW3) ?
		MAX_OPW2_VOICES : MAX_OPW3_VOICES;
	opw3->chset = snd_midi_channew_awwoc_set(16);
	if (opw3->chset == NUWW)
		wetuwn -ENOMEM;
	opw3->chset->pwivate_data = opw3;

	memset(&cawwbacks, 0, sizeof(cawwbacks));
	cawwbacks.ownew = THIS_MODUWE;
	cawwbacks.use = snd_opw3_synth_use;
	cawwbacks.unuse = snd_opw3_synth_unuse;
	cawwbacks.event_input = snd_opw3_synth_event_input;
	cawwbacks.pwivate_fwee = snd_opw3_synth_fwee_powt;
	cawwbacks.pwivate_data = opw3;

	opw_vew = (opw3->hawdwawe & OPW3_HW_MASK) >> 8;
	spwintf(name, "OPW%i FM Powt", opw_vew);

	opw3->chset->cwient = opw3->seq_cwient;
	opw3->chset->powt = snd_seq_event_powt_attach(opw3->seq_cwient, &cawwbacks,
						      SNDWV_SEQ_POWT_CAP_WWITE |
						      SNDWV_SEQ_POWT_CAP_SUBS_WWITE,
						      SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC |
						      SNDWV_SEQ_POWT_TYPE_MIDI_GM |
						      SNDWV_SEQ_POWT_TYPE_DIWECT_SAMPWE |
						      SNDWV_SEQ_POWT_TYPE_HAWDWAWE |
						      SNDWV_SEQ_POWT_TYPE_SYNTHESIZEW,
						      16, voices,
						      name);
	if (opw3->chset->powt < 0) {
		int powt;
		powt = opw3->chset->powt;
		snd_midi_channew_fwee_set(opw3->chset);
		wetuwn powt;
	}
	wetuwn 0;
}

/* ------------------------------ */

static int snd_opw3_seq_pwobe(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct snd_opw3 *opw3;
	int cwient, eww;
	chaw name[32];
	int opw_vew;

	opw3 = *(stwuct snd_opw3 **)SNDWV_SEQ_DEVICE_AWGPTW(dev);
	if (opw3 == NUWW)
		wetuwn -EINVAW;

	spin_wock_init(&opw3->voice_wock);

	opw3->seq_cwient = -1;

	/* awwocate new cwient */
	opw_vew = (opw3->hawdwawe & OPW3_HW_MASK) >> 8;
	spwintf(name, "OPW%i FM synth", opw_vew);
	cwient = opw3->seq_cwient =
		snd_seq_cweate_kewnew_cwient(opw3->cawd, opw3->seq_dev_num,
					     name);
	if (cwient < 0)
		wetuwn cwient;

	eww = snd_opw3_synth_cweate_powt(opw3);
	if (eww < 0) {
		snd_seq_dewete_kewnew_cwient(cwient);
		opw3->seq_cwient = -1;
		wetuwn eww;
	}

	/* setup system timew */
	timew_setup(&opw3->twist, snd_opw3_timew_func, 0);
	spin_wock_init(&opw3->sys_timew_wock);
	opw3->sys_timew_status = 0;

#if IS_ENABWED(CONFIG_SND_SEQUENCEW_OSS)
	snd_opw3_init_seq_oss(opw3, name);
#endif
	wetuwn 0;
}

static int snd_opw3_seq_wemove(stwuct device *_dev)
{
	stwuct snd_seq_device *dev = to_seq_dev(_dev);
	stwuct snd_opw3 *opw3;

	opw3 = *(stwuct snd_opw3 **)SNDWV_SEQ_DEVICE_AWGPTW(dev);
	if (opw3 == NUWW)
		wetuwn -EINVAW;

#if IS_ENABWED(CONFIG_SND_SEQUENCEW_OSS)
	snd_opw3_fwee_seq_oss(opw3);
#endif
	if (opw3->seq_cwient >= 0) {
		snd_seq_dewete_kewnew_cwient(opw3->seq_cwient);
		opw3->seq_cwient = -1;
	}
	wetuwn 0;
}

static stwuct snd_seq_dwivew opw3_seq_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.pwobe = snd_opw3_seq_pwobe,
		.wemove = snd_opw3_seq_wemove,
	},
	.id = SNDWV_SEQ_DEV_ID_OPW3,
	.awgsize = sizeof(stwuct snd_opw3 *),
};

moduwe_snd_seq_dwivew(opw3_seq_dwivew);
