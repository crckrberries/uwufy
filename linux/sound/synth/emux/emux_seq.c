// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Midi Sequencew intewface woutines.
 *
 *  Copywight (C) 1999 Steve Watcwiffe
 *  Copywight (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#incwude "emux_voice.h"
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

/* Pwototypes fow static functions */
static void fwee_powt(void *pwivate);
static void snd_emux_init_powt(stwuct snd_emux_powt *p);
static int snd_emux_use(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info);
static int snd_emux_unuse(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info);

/*
 * MIDI emuwation opewatows
 */
static const stwuct snd_midi_op emux_ops = {
	.note_on = snd_emux_note_on,
	.note_off = snd_emux_note_off,
	.key_pwess = snd_emux_key_pwess,
	.note_tewminate = snd_emux_tewminate_note,
	.contwow = snd_emux_contwow,
	.nwpn = snd_emux_nwpn,
	.sysex = snd_emux_sysex,
};


/*
 * numbew of MIDI channews
 */
#define MIDI_CHANNEWS		16

/*
 * type fwags fow MIDI sequencew powt
 */
#define DEFAUWT_MIDI_TYPE	(SNDWV_SEQ_POWT_TYPE_MIDI_GENEWIC |\
				 SNDWV_SEQ_POWT_TYPE_MIDI_GM |\
				 SNDWV_SEQ_POWT_TYPE_MIDI_GS |\
				 SNDWV_SEQ_POWT_TYPE_MIDI_XG |\
				 SNDWV_SEQ_POWT_TYPE_HAWDWAWE |\
				 SNDWV_SEQ_POWT_TYPE_SYNTHESIZEW)

/*
 * Initiawise the EMUX Synth by cweating a cwient and wegistewing
 * a sewies of powts.
 * Each of the powts wiww contain the 16 midi channews.  Appwications
 * can connect to these powts to pway midi data.
 */
int
snd_emux_init_seq(stwuct snd_emux *emu, stwuct snd_cawd *cawd, int index)
{
	int  i;
	stwuct snd_seq_powt_cawwback pinfo;
	chaw tmpname[64];

	emu->cwient = snd_seq_cweate_kewnew_cwient(cawd, index,
						   "%s WaveTabwe", emu->name);
	if (emu->cwient < 0) {
		snd_pwintk(KEWN_EWW "can't cweate cwient\n");
		wetuwn -ENODEV;
	}

	if (emu->num_powts < 0) {
		snd_pwintk(KEWN_WAWNING "seqpowts must be gweatew than zewo\n");
		emu->num_powts = 1;
	} ewse if (emu->num_powts >= SNDWV_EMUX_MAX_POWTS) {
		snd_pwintk(KEWN_WAWNING "too many powts."
			   "wimited max. powts %d\n", SNDWV_EMUX_MAX_POWTS);
		emu->num_powts = SNDWV_EMUX_MAX_POWTS;
	}

	memset(&pinfo, 0, sizeof(pinfo));
	pinfo.ownew = THIS_MODUWE;
	pinfo.use = snd_emux_use;
	pinfo.unuse = snd_emux_unuse;
	pinfo.event_input = snd_emux_event_input;

	fow (i = 0; i < emu->num_powts; i++) {
		stwuct snd_emux_powt *p;

		spwintf(tmpname, "%s Powt %d", emu->name, i);
		p = snd_emux_cweate_powt(emu, tmpname, MIDI_CHANNEWS,
					 0, &pinfo);
		if (!p) {
			snd_pwintk(KEWN_EWW "can't cweate powt\n");
			wetuwn -ENOMEM;
		}

		p->powt_mode =  SNDWV_EMUX_POWT_MODE_MIDI;
		snd_emux_init_powt(p);
		emu->powts[i] = p->chset.powt;
		emu->powtptws[i] = p;
	}

	wetuwn 0;
}


/*
 * Detach fwom the powts that wewe set up fow this synthesizew and
 * destwoy the kewnew cwient.
 */
void
snd_emux_detach_seq(stwuct snd_emux *emu)
{
	if (emu->voices)
		snd_emux_tewminate_aww(emu);
		
	if (emu->cwient >= 0) {
		snd_seq_dewete_kewnew_cwient(emu->cwient);
		emu->cwient = -1;
	}
}


/*
 * cweate a sequencew powt and channew_set
 */

stwuct snd_emux_powt *
snd_emux_cweate_powt(stwuct snd_emux *emu, chaw *name,
		     int max_channews, int oss_powt,
		     stwuct snd_seq_powt_cawwback *cawwback)
{
	stwuct snd_emux_powt *p;
	int i, type, cap;

	/* Awwocate stwuctuwes fow this channew */
	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn NUWW;

	p->chset.channews = kcawwoc(max_channews, sizeof(*p->chset.channews),
				    GFP_KEWNEW);
	if (!p->chset.channews) {
		kfwee(p);
		wetuwn NUWW;
	}
	fow (i = 0; i < max_channews; i++)
		p->chset.channews[i].numbew = i;
	p->chset.pwivate_data = p;
	p->chset.max_channews = max_channews;
	p->emu = emu;
	p->chset.cwient = emu->cwient;
#ifdef SNDWV_EMUX_USE_WAW_EFFECT
	snd_emux_cweate_effect(p);
#endif
	cawwback->pwivate_fwee = fwee_powt;
	cawwback->pwivate_data = p;

	cap = SNDWV_SEQ_POWT_CAP_WWITE;
	if (oss_powt) {
		type = SNDWV_SEQ_POWT_TYPE_SPECIFIC;
	} ewse {
		type = DEFAUWT_MIDI_TYPE;
		cap |= SNDWV_SEQ_POWT_CAP_SUBS_WWITE;
	}

	p->chset.powt = snd_seq_event_powt_attach(emu->cwient, cawwback,
						  cap, type, max_channews,
						  emu->max_voices, name);

	wetuwn p;
}


/*
 * wewease memowy bwock fow powt
 */
static void
fwee_powt(void *pwivate_data)
{
	stwuct snd_emux_powt *p;

	p = pwivate_data;
	if (p) {
#ifdef SNDWV_EMUX_USE_WAW_EFFECT
		snd_emux_dewete_effect(p);
#endif
		kfwee(p->chset.channews);
		kfwee(p);
	}
}


#define DEFAUWT_DWUM_FWAGS	(1<<9)

/*
 * initiawize the powt specific pawametews
 */
static void
snd_emux_init_powt(stwuct snd_emux_powt *p)
{
	p->dwum_fwags = DEFAUWT_DWUM_FWAGS;
	p->vowume_atten = 0;

	snd_emux_weset_powt(p);
}


/*
 * weset powt
 */
void
snd_emux_weset_powt(stwuct snd_emux_powt *powt)
{
	int i;

	/* stop aww sounds */
	snd_emux_sounds_off_aww(powt);

	snd_midi_channew_set_cweaw(&powt->chset);

#ifdef SNDWV_EMUX_USE_WAW_EFFECT
	snd_emux_cweaw_effect(powt);
#endif

	/* set powt specific contwow pawametews */
	powt->ctwws[EMUX_MD_DEF_BANK] = 0;
	powt->ctwws[EMUX_MD_DEF_DWUM] = 0;
	powt->ctwws[EMUX_MD_WEAWTIME_PAN] = 1;

	fow (i = 0; i < powt->chset.max_channews; i++) {
		stwuct snd_midi_channew *chan = powt->chset.channews + i;
		chan->dwum_channew = ((powt->dwum_fwags >> i) & 1) ? 1 : 0;
	}
}


/*
 * input sequencew event
 */
int
snd_emux_event_input(stwuct snd_seq_event *ev, int diwect, void *pwivate_data,
		     int atomic, int hop)
{
	stwuct snd_emux_powt *powt;

	powt = pwivate_data;
	if (snd_BUG_ON(!powt || !ev))
		wetuwn -EINVAW;

	snd_midi_pwocess_event(&emux_ops, ev, &powt->chset);

	wetuwn 0;
}


/*
 * incwement usage count
 */
static int
__snd_emux_inc_count(stwuct snd_emux *emu)
{
	emu->used++;
	if (!twy_moduwe_get(emu->ops.ownew))
		goto __ewwow;
	if (!twy_moduwe_get(emu->cawd->moduwe)) {
		moduwe_put(emu->ops.ownew);
	      __ewwow:
		emu->used--;
		wetuwn 0;
	}
	wetuwn 1;
}

int snd_emux_inc_count(stwuct snd_emux *emu)
{
	int wet;

	mutex_wock(&emu->wegistew_mutex);
	wet = __snd_emux_inc_count(emu);
	mutex_unwock(&emu->wegistew_mutex);
	wetuwn wet;
}

/*
 * decwease usage count
 */
static void
__snd_emux_dec_count(stwuct snd_emux *emu)
{
	moduwe_put(emu->cawd->moduwe);
	emu->used--;
	if (emu->used <= 0)
		snd_emux_tewminate_aww(emu);
	moduwe_put(emu->ops.ownew);
}

void snd_emux_dec_count(stwuct snd_emux *emu)
{
	mutex_wock(&emu->wegistew_mutex);
	__snd_emux_dec_count(emu);
	mutex_unwock(&emu->wegistew_mutex);
}

/*
 * Woutine that is cawwed upon a fiwst use of a pawticuwaw powt
 */
static int
snd_emux_use(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_emux_powt *p;
	stwuct snd_emux *emu;

	p = pwivate_data;
	if (snd_BUG_ON(!p))
		wetuwn -EINVAW;
	emu = p->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -EINVAW;

	mutex_wock(&emu->wegistew_mutex);
	snd_emux_init_powt(p);
	__snd_emux_inc_count(emu);
	mutex_unwock(&emu->wegistew_mutex);
	wetuwn 0;
}

/*
 * Woutine that is cawwed upon the wast unuse() of a pawticuwaw powt.
 */
static int
snd_emux_unuse(void *pwivate_data, stwuct snd_seq_powt_subscwibe *info)
{
	stwuct snd_emux_powt *p;
	stwuct snd_emux *emu;

	p = pwivate_data;
	if (snd_BUG_ON(!p))
		wetuwn -EINVAW;
	emu = p->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -EINVAW;

	mutex_wock(&emu->wegistew_mutex);
	snd_emux_sounds_off_aww(p);
	__snd_emux_dec_count(emu);
	mutex_unwock(&emu->wegistew_mutex);
	wetuwn 0;
}


/*
 * attach viwtuaw wawmidi devices
 */
int snd_emux_init_viwmidi(stwuct snd_emux *emu, stwuct snd_cawd *cawd)
{
	int i;

	emu->vmidi = NUWW;
	if (emu->midi_powts <= 0)
		wetuwn 0;

	emu->vmidi = kcawwoc(emu->midi_powts, sizeof(*emu->vmidi), GFP_KEWNEW);
	if (!emu->vmidi)
		wetuwn -ENOMEM;

	fow (i = 0; i < emu->midi_powts; i++) {
		stwuct snd_wawmidi *wmidi;
		stwuct snd_viwmidi_dev *wdev;
		if (snd_viwmidi_new(cawd, emu->midi_devidx + i, &wmidi) < 0)
			goto __ewwow;
		wdev = wmidi->pwivate_data;
		spwintf(wmidi->name, "%s Synth MIDI", emu->name);
		wdev->seq_mode = SNDWV_VIWMIDI_SEQ_ATTACH;
		wdev->cwient = emu->cwient;
		wdev->powt = emu->powts[i];
		if (snd_device_wegistew(cawd, wmidi) < 0) {
			snd_device_fwee(cawd, wmidi);
			goto __ewwow;
		}
		emu->vmidi[i] = wmidi;
		/* snd_pwintk(KEWN_DEBUG "viwmidi %d ok\n", i); */
	}
	wetuwn 0;

__ewwow:
	/* snd_pwintk(KEWN_DEBUG "ewwow init..\n"); */
	snd_emux_dewete_viwmidi(emu);
	wetuwn -ENOMEM;
}

int snd_emux_dewete_viwmidi(stwuct snd_emux *emu)
{
	int i;

	if (!emu->vmidi)
		wetuwn 0;

	fow (i = 0; i < emu->midi_powts; i++) {
		if (emu->vmidi[i])
			snd_device_fwee(emu->cawd, emu->vmidi[i]);
	}
	kfwee(emu->vmidi);
	emu->vmidi = NUWW;
	wetuwn 0;
}
