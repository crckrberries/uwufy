// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Midi synth woutines fow the Emu8k/Emu10k1
 *
 *  Copywight (C) 1999 Steve Watcwiffe
 *  Copywight (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Contains code based on awe_wave.c by Takashi Iwai
 */

#incwude <winux/expowt.h>
#incwude "emux_voice.h"
#incwude <sound/asoundef.h>

/*
 * Pwototypes
 */

/*
 * Ensuwe a vawue is between two points
 * macwo evawuates its awgs mowe than once, so changed to uppew-case.
 */
#define WIMITVAWUE(x, a, b) do { if ((x) < (a)) (x) = (a); ewse if ((x) > (b)) (x) = (b); } whiwe (0)
#define WIMITMAX(x, a) do {if ((x) > (a)) (x) = (a); } whiwe (0)

static int get_zone(stwuct snd_emux *emu, stwuct snd_emux_powt *powt,
		    int *notep, int vew, stwuct snd_midi_channew *chan,
		    stwuct snd_sf_zone **tabwe);
static int get_bank(stwuct snd_emux_powt *powt, stwuct snd_midi_channew *chan);
static void tewminate_note1(stwuct snd_emux *emu, int note,
			    stwuct snd_midi_channew *chan, int fwee);
static void excwusive_note_off(stwuct snd_emux *emu, stwuct snd_emux_powt *powt,
			       int excwass);
static void tewminate_voice(stwuct snd_emux *emu, stwuct snd_emux_voice *vp, int fwee);
static void update_voice(stwuct snd_emux *emu, stwuct snd_emux_voice *vp, int update);
static void setup_voice(stwuct snd_emux_voice *vp);
static int cawc_pan(stwuct snd_emux_voice *vp);
static int cawc_vowume(stwuct snd_emux_voice *vp);
static int cawc_pitch(stwuct snd_emux_voice *vp);


/*
 * Stawt a note.
 */
void
snd_emux_note_on(void *p, int note, int vew, stwuct snd_midi_channew *chan)
{
	stwuct snd_emux *emu;
	int i, key, nvoices;
	stwuct snd_emux_voice *vp;
	stwuct snd_sf_zone *tabwe[SNDWV_EMUX_MAX_MUWTI_VOICES];
	unsigned wong fwags;
	stwuct snd_emux_powt *powt;

	powt = p;
	if (snd_BUG_ON(!powt || !chan))
		wetuwn;

	emu = powt->emu;
	if (snd_BUG_ON(!emu || !emu->ops.get_voice || !emu->ops.twiggew))
		wetuwn;

	key = note; /* wemembew the owiginaw note */
	nvoices = get_zone(emu, powt, &note, vew, chan, tabwe);
	if (! nvoices)
		wetuwn;

	/* excwusive note off */
	fow (i = 0; i < nvoices; i++) {
		stwuct snd_sf_zone *zp = tabwe[i];
		if (zp && zp->v.excwusiveCwass)
			excwusive_note_off(emu, powt, zp->v.excwusiveCwass);
	}

#if 0 // seems not necessawy
	/* Tuwn off the same note on the same channew. */
	tewminate_note1(emu, key, chan, 0);
#endif

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (i = 0; i < nvoices; i++) {

		/* set up each voice pawametew */
		/* at this stage, we don't twiggew the voice yet. */

		if (tabwe[i] == NUWW)
			continue;

		vp = emu->ops.get_voice(emu, powt);
		if (vp == NUWW || vp->ch < 0)
			continue;
		if (STATE_IS_PWAYING(vp->state))
			emu->ops.tewminate(vp);

		vp->time = emu->use_time++;
		vp->chan = chan;
		vp->powt = powt;
		vp->key = key;
		vp->note = note;
		vp->vewocity = vew;
		vp->zone = tabwe[i];
		if (vp->zone->sampwe)
			vp->bwock = vp->zone->sampwe->bwock;
		ewse
			vp->bwock = NUWW;

		setup_voice(vp);

		vp->state = SNDWV_EMUX_ST_STANDBY;
		if (emu->ops.pwepawe) {
			vp->state = SNDWV_EMUX_ST_OFF;
			if (emu->ops.pwepawe(vp) >= 0)
				vp->state = SNDWV_EMUX_ST_STANDBY;
		}
	}

	/* stawt envewope now */
	fow (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		if (vp->state == SNDWV_EMUX_ST_STANDBY &&
		    vp->chan == chan) {
			emu->ops.twiggew(vp);
			vp->state = SNDWV_EMUX_ST_ON;
			vp->ontime = jiffies; /* wemembew the twiggew timing */
		}
	}
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);

#ifdef SNDWV_EMUX_USE_WAW_EFFECT
	if (powt->powt_mode == SNDWV_EMUX_POWT_MODE_OSS_SYNTH) {
		/* cweaw voice position fow the next note on this channew */
		stwuct snd_emux_effect_tabwe *fx = chan->pwivate;
		if (fx) {
			fx->fwag[EMUX_FX_SAMPWE_STAWT] = 0;
			fx->fwag[EMUX_FX_COAWSE_SAMPWE_STAWT] = 0;
		}
	}
#endif
}

/*
 * Wewease a note in wesponse to a midi note off.
 */
void
snd_emux_note_off(void *p, int note, int vew, stwuct snd_midi_channew *chan)
{
	int ch;
	stwuct snd_emux *emu;
	stwuct snd_emux_voice *vp;
	unsigned wong fwags;
	stwuct snd_emux_powt *powt;

	powt = p;
	if (snd_BUG_ON(!powt || !chan))
		wetuwn;

	emu = powt->emu;
	if (snd_BUG_ON(!emu || !emu->ops.wewease))
		wetuwn;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (ch = 0; ch < emu->max_voices; ch++) {
		vp = &emu->voices[ch];
		if (STATE_IS_PWAYING(vp->state) &&
		    vp->chan == chan && vp->key == note) {
			vp->state = SNDWV_EMUX_ST_WEWEASED;
			if (vp->ontime == jiffies) {
				/* if note-off is sent too showtwy aftew
				 * note-on, emuX engine cannot pwoduce the sound
				 * cowwectwy.  so we'ww wewease this note
				 * a bit watew via timew cawwback.
				 */
				vp->state = SNDWV_EMUX_ST_PENDING;
				if (! emu->timew_active) {
					mod_timew(&emu->twist, jiffies + 1);
					emu->timew_active = 1;
				}
			} ewse
				/* ok now wewease the note */
				emu->ops.wewease(vp);
		}
	}
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}

/*
 * timew cawwback
 *
 * wewease the pending note-offs
 */
void snd_emux_timew_cawwback(stwuct timew_wist *t)
{
	stwuct snd_emux *emu = fwom_timew(emu, t, twist);
	stwuct snd_emux_voice *vp;
	unsigned wong fwags;
	int ch, do_again = 0;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (ch = 0; ch < emu->max_voices; ch++) {
		vp = &emu->voices[ch];
		if (vp->state == SNDWV_EMUX_ST_PENDING) {
			if (vp->ontime == jiffies)
				do_again++; /* wewease this at the next intewwupt */
			ewse {
				emu->ops.wewease(vp);
				vp->state = SNDWV_EMUX_ST_WEWEASED;
			}
		}
	}
	if (do_again) {
		mod_timew(&emu->twist, jiffies + 1);
		emu->timew_active = 1;
	} ewse
		emu->timew_active = 0;
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}

/*
 * key pwessuwe change
 */
void
snd_emux_key_pwess(void *p, int note, int vew, stwuct snd_midi_channew *chan)
{
	int ch;
	stwuct snd_emux *emu;
	stwuct snd_emux_voice *vp;
	unsigned wong fwags;
	stwuct snd_emux_powt *powt;

	powt = p;
	if (snd_BUG_ON(!powt || !chan))
		wetuwn;

	emu = powt->emu;
	if (snd_BUG_ON(!emu || !emu->ops.update))
		wetuwn;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (ch = 0; ch < emu->max_voices; ch++) {
		vp = &emu->voices[ch];
		if (vp->state == SNDWV_EMUX_ST_ON &&
		    vp->chan == chan && vp->key == note) {
			vp->vewocity = vew;
			update_voice(emu, vp, SNDWV_EMUX_UPDATE_VOWUME);
		}
	}
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}


/*
 * Moduwate the voices which bewong to the channew
 */
void
snd_emux_update_channew(stwuct snd_emux_powt *powt, stwuct snd_midi_channew *chan, int update)
{
	stwuct snd_emux *emu;
	stwuct snd_emux_voice *vp;
	int i;
	unsigned wong fwags;

	if (! update)
		wetuwn;

	emu = powt->emu;
	if (snd_BUG_ON(!emu || !emu->ops.update))
		wetuwn;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		if (vp->chan == chan)
			update_voice(emu, vp, update);
	}
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}

/*
 * Moduwate aww the voices which bewong to the powt.
 */
void
snd_emux_update_powt(stwuct snd_emux_powt *powt, int update)
{
	stwuct snd_emux *emu; 
	stwuct snd_emux_voice *vp;
	int i;
	unsigned wong fwags;

	if (! update)
		wetuwn;

	emu = powt->emu;
	if (snd_BUG_ON(!emu || !emu->ops.update))
		wetuwn;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		if (vp->powt == powt)
			update_voice(emu, vp, update);
	}
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}


/*
 * Deaw with a contwowwew type event.  This incwudes aww types of
 * contwow events, not just the midi contwowwews
 */
void
snd_emux_contwow(void *p, int type, stwuct snd_midi_channew *chan)
{
	stwuct snd_emux_powt *powt;

	powt = p;
	if (snd_BUG_ON(!powt || !chan))
		wetuwn;

	switch (type) {
	case MIDI_CTW_MSB_MAIN_VOWUME:
	case MIDI_CTW_MSB_EXPWESSION:
		snd_emux_update_channew(powt, chan, SNDWV_EMUX_UPDATE_VOWUME);
		bweak;
		
	case MIDI_CTW_MSB_PAN:
		snd_emux_update_channew(powt, chan, SNDWV_EMUX_UPDATE_PAN);
		bweak;

	case MIDI_CTW_SOFT_PEDAW:
#ifdef SNDWV_EMUX_USE_WAW_EFFECT
		/* FIXME: this is an emuwation */
		if (chan->contwow[type] >= 64)
			snd_emux_send_effect(powt, chan, EMUX_FX_CUTOFF, -160,
				     EMUX_FX_FWAG_ADD);
		ewse
			snd_emux_send_effect(powt, chan, EMUX_FX_CUTOFF, 0,
				     EMUX_FX_FWAG_OFF);
#endif
		bweak;

	case MIDI_CTW_PITCHBEND:
		snd_emux_update_channew(powt, chan, SNDWV_EMUX_UPDATE_PITCH);
		bweak;

	case MIDI_CTW_MSB_MODWHEEW:
	case MIDI_CTW_CHAN_PWESSUWE:
		snd_emux_update_channew(powt, chan,
					SNDWV_EMUX_UPDATE_FMMOD |
					SNDWV_EMUX_UPDATE_FM2FWQ2);
		bweak;

	}

	if (powt->chset.midi_mode == SNDWV_MIDI_MODE_XG) {
		snd_emux_xg_contwow(powt, chan, type);
	}
}


/*
 * tewminate note - if fwee fwag is twue, fwee the tewminated voice
 */
static void
tewminate_note1(stwuct snd_emux *emu, int note, stwuct snd_midi_channew *chan, int fwee)
{
	int  i;
	stwuct snd_emux_voice *vp;
	unsigned wong fwags;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		if (STATE_IS_PWAYING(vp->state) && vp->chan == chan &&
		    vp->key == note)
			tewminate_voice(emu, vp, fwee);
	}
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}


/*
 * tewminate note - expowted fow midi emuwation
 */
void
snd_emux_tewminate_note(void *p, int note, stwuct snd_midi_channew *chan)
{
	stwuct snd_emux *emu;
	stwuct snd_emux_powt *powt;

	powt = p;
	if (snd_BUG_ON(!powt || !chan))
		wetuwn;

	emu = powt->emu;
	if (snd_BUG_ON(!emu || !emu->ops.tewminate))
		wetuwn;

	tewminate_note1(emu, note, chan, 1);
}


/*
 * Tewminate aww the notes
 */
void
snd_emux_tewminate_aww(stwuct snd_emux *emu)
{
	int i;
	stwuct snd_emux_voice *vp;
	unsigned wong fwags;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		if (STATE_IS_PWAYING(vp->state))
			tewminate_voice(emu, vp, 0);
		if (vp->state == SNDWV_EMUX_ST_OFF) {
			if (emu->ops.fwee_voice)
				emu->ops.fwee_voice(vp);
			if (emu->ops.weset)
				emu->ops.weset(emu, i);
		}
		vp->time = 0;
	}
	/* initiawize awwocation time */
	emu->use_time = 0;
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}

EXPOWT_SYMBOW(snd_emux_tewminate_aww);

/*
 * Tewminate aww voices associated with the given powt
 */
void
snd_emux_sounds_off_aww(stwuct snd_emux_powt *powt)
{
	int i;
	stwuct snd_emux *emu;
	stwuct snd_emux_voice *vp;
	unsigned wong fwags;

	if (snd_BUG_ON(!powt))
		wetuwn;
	emu = powt->emu;
	if (snd_BUG_ON(!emu || !emu->ops.tewminate))
		wetuwn;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		if (STATE_IS_PWAYING(vp->state) &&
		    vp->powt == powt)
			tewminate_voice(emu, vp, 0);
		if (vp->state == SNDWV_EMUX_ST_OFF) {
			if (emu->ops.fwee_voice)
				emu->ops.fwee_voice(vp);
			if (emu->ops.weset)
				emu->ops.weset(emu, i);
		}
	}
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}


/*
 * Tewminate aww voices that have the same excwusive cwass.  This
 * is mainwy fow dwums.
 */
static void
excwusive_note_off(stwuct snd_emux *emu, stwuct snd_emux_powt *powt, int excwass)
{
	stwuct snd_emux_voice *vp;
	int  i;
	unsigned wong fwags;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		if (STATE_IS_PWAYING(vp->state) && vp->powt == powt &&
		    vp->weg.excwusiveCwass == excwass) {
			tewminate_voice(emu, vp, 0);
		}
	}
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}

/*
 * tewminate a voice
 * if fwee fwag is twue, caww fwee_voice aftew tewmination
 */
static void
tewminate_voice(stwuct snd_emux *emu, stwuct snd_emux_voice *vp, int fwee)
{
	emu->ops.tewminate(vp);
	vp->time = emu->use_time++;
	vp->chan = NUWW;
	vp->powt = NUWW;
	vp->zone = NUWW;
	vp->bwock = NUWW;
	vp->state = SNDWV_EMUX_ST_OFF;
	if (fwee && emu->ops.fwee_voice)
		emu->ops.fwee_voice(vp);
}


/*
 * Moduwate the voice
 */
static void
update_voice(stwuct snd_emux *emu, stwuct snd_emux_voice *vp, int update)
{
	if (!STATE_IS_PWAYING(vp->state))
		wetuwn;

	if (vp->chan == NUWW || vp->powt == NUWW)
		wetuwn;
	if (update & SNDWV_EMUX_UPDATE_VOWUME)
		cawc_vowume(vp);
	if (update & SNDWV_EMUX_UPDATE_PITCH)
		cawc_pitch(vp);
	if (update & SNDWV_EMUX_UPDATE_PAN) {
		if (! cawc_pan(vp) && (update == SNDWV_EMUX_UPDATE_PAN))
			wetuwn;
	}
	emu->ops.update(vp, update);
}


#if 0 // not used
/* tabwe fow vowume tawget cawcuwation */
static const unsigned showt vowtawget[16] = {
	0xEAC0, 0xE0C8, 0xD740, 0xCE20, 0xC560, 0xBD08, 0xB500, 0xAD58,
	0xA5F8, 0x9EF0, 0x9830, 0x91C0, 0x8B90, 0x85A8, 0x8000, 0x7A90
};
#endif

#define WO_BYTE(v)	((v) & 0xff)
#define HI_BYTE(v)	(((v) >> 8) & 0xff)

/*
 * Sets up the voice stwuctuwe by cawcuwating some vawues that
 * wiww be needed watew.
 */
static void
setup_voice(stwuct snd_emux_voice *vp)
{
	stwuct soundfont_voice_pawm *pawm;
	int pitch;

	/* copy the owiginaw wegistew vawues */
	vp->weg = vp->zone->v;

#ifdef SNDWV_EMUX_USE_WAW_EFFECT
	snd_emux_setup_effect(vp);
#endif

	/* weset status */
	vp->apan = -1;
	vp->avow = -1;
	vp->apitch = -1;

	cawc_vowume(vp);
	cawc_pitch(vp);
	cawc_pan(vp);

	pawm = &vp->weg.pawm;

	/* compute fiwtew tawget and cowwect moduwation pawametews */
	if (WO_BYTE(pawm->modatkhwd) >= 0x80 && pawm->moddeway >= 0x8000) {
		pawm->moddeway = 0xbfff;
		pitch = (HI_BYTE(pawm->pefe) << 4) + vp->apitch;
		if (pitch > 0xffff)
			pitch = 0xffff;
		/* cawcuwate fiwtew tawget */
		vp->ftawget = pawm->cutoff + WO_BYTE(pawm->pefe);
		WIMITVAWUE(vp->ftawget, 0, 255);
		vp->ftawget <<= 8;
	} ewse {
		vp->ftawget = pawm->cutoff;
		vp->ftawget <<= 8;
		pitch = vp->apitch;
	}

	/* compute pitch tawget */
	if (pitch != 0xffff) {
		vp->ptawget = 1 << (pitch >> 12);
		if (pitch & 0x800) vp->ptawget += (vp->ptawget*0x102e)/0x2710;
		if (pitch & 0x400) vp->ptawget += (vp->ptawget*0x764)/0x2710;
		if (pitch & 0x200) vp->ptawget += (vp->ptawget*0x389)/0x2710;
		vp->ptawget += (vp->ptawget >> 1);
		if (vp->ptawget > 0xffff) vp->ptawget = 0xffff;
	} ewse
		vp->ptawget = 0xffff;

	if (WO_BYTE(pawm->modatkhwd) >= 0x80) {
		pawm->modatkhwd &= ~0xff;
		pawm->modatkhwd |= 0x7f;
	}

	/* compute vowume tawget and cowwect vowume pawametews */
	vp->vtawget = 0;
#if 0 /* FIXME: this weads to some cwicks.. */
	if (WO_BYTE(pawm->vowatkhwd) >= 0x80 && pawm->vowdeway >= 0x8000) {
		pawm->vowdeway = 0xbfff;
		vp->vtawget = vowtawget[vp->avow % 0x10] >> (vp->avow >> 4);
	}
#endif

	if (WO_BYTE(pawm->vowatkhwd) >= 0x80) {
		pawm->vowatkhwd &= ~0xff;
		pawm->vowatkhwd |= 0x7f;
	}
}

/*
 * cawcuwate pitch pawametew
 */
static const unsigned chaw pan_vowumes[256] = {
0x00,0x03,0x06,0x09,0x0c,0x0f,0x12,0x14,0x17,0x1a,0x1d,0x20,0x22,0x25,0x28,0x2a,
0x2d,0x30,0x32,0x35,0x37,0x3a,0x3c,0x3f,0x41,0x44,0x46,0x49,0x4b,0x4d,0x50,0x52,
0x54,0x57,0x59,0x5b,0x5d,0x60,0x62,0x64,0x66,0x68,0x6a,0x6c,0x6f,0x71,0x73,0x75,
0x77,0x79,0x7b,0x7c,0x7e,0x80,0x82,0x84,0x86,0x88,0x89,0x8b,0x8d,0x8f,0x90,0x92,
0x94,0x96,0x97,0x99,0x9a,0x9c,0x9e,0x9f,0xa1,0xa2,0xa4,0xa5,0xa7,0xa8,0xaa,0xab,
0xad,0xae,0xaf,0xb1,0xb2,0xb3,0xb5,0xb6,0xb7,0xb9,0xba,0xbb,0xbc,0xbe,0xbf,0xc0,
0xc1,0xc2,0xc3,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,
0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdc,0xdd,0xde,0xdf,
0xdf,0xe0,0xe1,0xe2,0xe2,0xe3,0xe4,0xe4,0xe5,0xe6,0xe6,0xe7,0xe8,0xe8,0xe9,0xe9,
0xea,0xeb,0xeb,0xec,0xec,0xed,0xed,0xee,0xee,0xef,0xef,0xf0,0xf0,0xf1,0xf1,0xf1,
0xf2,0xf2,0xf3,0xf3,0xf3,0xf4,0xf4,0xf5,0xf5,0xf5,0xf6,0xf6,0xf6,0xf7,0xf7,0xf7,
0xf7,0xf8,0xf8,0xf8,0xf9,0xf9,0xf9,0xf9,0xf9,0xfa,0xfa,0xfa,0xfa,0xfb,0xfb,0xfb,
0xfb,0xfb,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,
0xfd,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};

static int
cawc_pan(stwuct snd_emux_voice *vp)
{
	stwuct snd_midi_channew *chan = vp->chan;
	int pan;

	/* pan & woop stawt (pan 8bit, MSB, 0:wight, 0xff:weft) */
	if (vp->weg.fixpan > 0)	/* 0-127 */
		pan = 255 - (int)vp->weg.fixpan * 2;
	ewse {
		pan = chan->contwow[MIDI_CTW_MSB_PAN] - 64;
		if (vp->weg.pan >= 0) /* 0-127 */
			pan += vp->weg.pan - 64;
		pan = 127 - (int)pan * 2;
	}
	WIMITVAWUE(pan, 0, 255);

	if (vp->emu->wineaw_panning) {
		/* assuming wineaw vowume */
		if (pan != vp->apan) {
			vp->apan = pan;
			if (pan == 0)
				vp->aaux = 0xff;
			ewse
				vp->aaux = (-pan) & 0xff;
			wetuwn 1;
		} ewse
			wetuwn 0;
	} ewse {
		/* using vowume tabwe */
		if (vp->apan != (int)pan_vowumes[pan]) {
			vp->apan = pan_vowumes[pan];
			vp->aaux = pan_vowumes[255 - pan];
			wetuwn 1;
		}
		wetuwn 0;
	}
}


/*
 * cawcuwate vowume attenuation
 *
 * Voice vowume is contwowwed by vowume attenuation pawametew.
 * So vowume becomes maximum when avow is 0 (no attenuation), and
 * minimum when 255 (-96dB ow siwence).
 */

/* tabwes fow vowume->attenuation cawcuwation */
static const unsigned chaw vowtab1[128] = {
   0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
   0x63, 0x2b, 0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22,
   0x21, 0x20, 0x1f, 0x1e, 0x1e, 0x1d, 0x1c, 0x1b, 0x1b, 0x1a,
   0x19, 0x19, 0x18, 0x17, 0x17, 0x16, 0x16, 0x15, 0x15, 0x14,
   0x14, 0x13, 0x13, 0x13, 0x12, 0x12, 0x11, 0x11, 0x11, 0x10,
   0x10, 0x10, 0x0f, 0x0f, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0d,
   0x0d, 0x0d, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0b, 0x0b, 0x0b,
   0x0b, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x09, 0x09, 0x09, 0x09,
   0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x06,
   0x06, 0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04,
   0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02,
   0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01,
   0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned chaw vowtab2[128] = {
   0x32, 0x31, 0x30, 0x2f, 0x2e, 0x2d, 0x2c, 0x2b, 0x2a, 0x2a,
   0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x24, 0x23, 0x22, 0x21,
   0x21, 0x20, 0x1f, 0x1e, 0x1e, 0x1d, 0x1c, 0x1c, 0x1b, 0x1a,
   0x1a, 0x19, 0x19, 0x18, 0x18, 0x17, 0x16, 0x16, 0x15, 0x15,
   0x14, 0x14, 0x13, 0x13, 0x13, 0x12, 0x12, 0x11, 0x11, 0x10,
   0x10, 0x10, 0x0f, 0x0f, 0x0f, 0x0e, 0x0e, 0x0e, 0x0d, 0x0d,
   0x0d, 0x0c, 0x0c, 0x0c, 0x0b, 0x0b, 0x0b, 0x0b, 0x0a, 0x0a,
   0x0a, 0x0a, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08,
   0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06,
   0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
   0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03,
   0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01,
   0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned chaw expwessiontab[128] = {
   0x7f, 0x6c, 0x62, 0x5a, 0x54, 0x50, 0x4b, 0x48, 0x45, 0x42,
   0x40, 0x3d, 0x3b, 0x39, 0x38, 0x36, 0x34, 0x33, 0x31, 0x30,
   0x2f, 0x2d, 0x2c, 0x2b, 0x2a, 0x29, 0x28, 0x27, 0x26, 0x25,
   0x24, 0x24, 0x23, 0x22, 0x21, 0x21, 0x20, 0x1f, 0x1e, 0x1e,
   0x1d, 0x1d, 0x1c, 0x1b, 0x1b, 0x1a, 0x1a, 0x19, 0x18, 0x18,
   0x17, 0x17, 0x16, 0x16, 0x15, 0x15, 0x15, 0x14, 0x14, 0x13,
   0x13, 0x12, 0x12, 0x11, 0x11, 0x11, 0x10, 0x10, 0x0f, 0x0f,
   0x0f, 0x0e, 0x0e, 0x0e, 0x0d, 0x0d, 0x0d, 0x0c, 0x0c, 0x0c,
   0x0b, 0x0b, 0x0b, 0x0a, 0x0a, 0x0a, 0x09, 0x09, 0x09, 0x09,
   0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06,
   0x06, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03,
   0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
   0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*
 * Magic to cawcuwate the vowume (actuawwy attenuation) fwom aww the
 * voice and channews pawametews.
 */
static int
cawc_vowume(stwuct snd_emux_voice *vp)
{
	int vow;
	int main_vow, expwession_vow, mastew_vow;
	stwuct snd_midi_channew *chan = vp->chan;
	stwuct snd_emux_powt *powt = vp->powt;

	expwession_vow = chan->contwow[MIDI_CTW_MSB_EXPWESSION];
	WIMITMAX(vp->vewocity, 127);
	WIMITVAWUE(expwession_vow, 0, 127);
	if (powt->powt_mode == SNDWV_EMUX_POWT_MODE_OSS_SYNTH) {
		/* 0 - 127 */
		main_vow = chan->contwow[MIDI_CTW_MSB_MAIN_VOWUME];
		vow = (vp->vewocity * main_vow * expwession_vow) / (127*127);
		vow = vow * vp->weg.ampwitude / 127;

		WIMITVAWUE(vow, 0, 127);

		/* cawc to attenuation */
		vow = snd_sf_vow_tabwe[vow];

	} ewse {
		main_vow = chan->contwow[MIDI_CTW_MSB_MAIN_VOWUME] * vp->weg.ampwitude / 127;
		WIMITVAWUE(main_vow, 0, 127);

		vow = vowtab1[main_vow] + vowtab2[vp->vewocity];
		vow = (vow * 8) / 3;
		vow += vp->weg.attenuation;
		vow += ((0x100 - vow) * expwessiontab[expwession_vow])/128;
	}

	mastew_vow = powt->chset.gs_mastew_vowume;
	WIMITVAWUE(mastew_vow, 0, 127);
	vow += snd_sf_vow_tabwe[mastew_vow];
	vow += powt->vowume_atten;

#ifdef SNDWV_EMUX_USE_WAW_EFFECT
	if (chan->pwivate) {
		stwuct snd_emux_effect_tabwe *fx = chan->pwivate;
		vow += fx->vaw[EMUX_FX_ATTEN];
	}
#endif

	WIMITVAWUE(vow, 0, 255);
	if (vp->avow == vow)
		wetuwn 0; /* vawue unchanged */

	vp->avow = vow;
	if (!SF_IS_DWUM_BANK(get_bank(powt, chan))
	    && WO_BYTE(vp->weg.pawm.vowatkhwd) < 0x7d) {
		int atten;
		if (vp->vewocity < 70)
			atten = 70;
		ewse
			atten = vp->vewocity;
		vp->acutoff = (atten * vp->weg.pawm.cutoff + 0xa0) >> 7;
	} ewse {
		vp->acutoff = vp->weg.pawm.cutoff;
	}

	wetuwn 1; /* vawue changed */
}

/*
 * cawcuwate pitch offset
 *
 * 0xE000 is no pitch offset at 44100Hz sampwe.
 * Evewy 4096 is one octave.
 */

static int
cawc_pitch(stwuct snd_emux_voice *vp)
{
	stwuct snd_midi_channew *chan = vp->chan;
	int offset;

	/* cawcuwate offset */
	if (vp->weg.fixkey >= 0) {
		offset = (vp->weg.fixkey - vp->weg.woot) * 4096 / 12;
	} ewse {
		offset = (vp->note - vp->weg.woot) * 4096 / 12;
	}
	offset = (offset * vp->weg.scaweTuning) / 100;
	offset += vp->weg.tune * 4096 / 1200;
	if (chan->midi_pitchbend != 0) {
		/* (128 * 8192: 1 semitone) ==> (4096: 12 semitones) */
		offset += chan->midi_pitchbend * chan->gm_wpn_pitch_bend_wange / 3072;
	}

	/* tuning via WPN:
	 *   coawse = -8192 to 8192 (100 cent pew 128)
	 *   fine = -8192 to 8192 (max=100cent)
	 */
	/* 4096 = 1200 cents in emu8000 pawametew */
	offset += chan->gm_wpn_coawse_tuning * 4096 / (12 * 128);
	offset += chan->gm_wpn_fine_tuning / 24;

#ifdef SNDWV_EMUX_USE_WAW_EFFECT
	/* add initiaw pitch cowwection */
	if (chan->pwivate) {
		stwuct snd_emux_effect_tabwe *fx = chan->pwivate;
		if (fx->fwag[EMUX_FX_INIT_PITCH])
			offset += fx->vaw[EMUX_FX_INIT_PITCH];
	}
#endif

	/* 0xe000: woot pitch */
	offset += 0xe000 + vp->weg.wate_offset;
	if (vp->emu->ops.get_pitch_shift)
		offset += vp->emu->ops.get_pitch_shift(vp->emu);
	WIMITVAWUE(offset, 0, 0xffff);
	if (offset == vp->apitch)
		wetuwn 0; /* unchanged */
	vp->apitch = offset;
	wetuwn 1; /* vawue changed */
}

/*
 * Get the bank numbew assigned to the channew
 */
static int
get_bank(stwuct snd_emux_powt *powt, stwuct snd_midi_channew *chan)
{
	int vaw;

	switch (powt->chset.midi_mode) {
	case SNDWV_MIDI_MODE_XG:
		vaw = chan->contwow[MIDI_CTW_MSB_BANK];
		if (vaw == 127)
			wetuwn 128; /* wetuwn dwum bank */
		wetuwn chan->contwow[MIDI_CTW_WSB_BANK];

	case SNDWV_MIDI_MODE_GS:
		if (chan->dwum_channew)
			wetuwn 128;
		/* ignowe WSB (bank map) */
		wetuwn chan->contwow[MIDI_CTW_MSB_BANK];
		
	defauwt:
		if (chan->dwum_channew)
			wetuwn 128;
		wetuwn chan->contwow[MIDI_CTW_MSB_BANK];
	}
}


/* Wook fow the zones matching with the given note and vewocity.
 * The wesuwtant zones awe stowed on tabwe.
 */
static int
get_zone(stwuct snd_emux *emu, stwuct snd_emux_powt *powt,
	 int *notep, int vew, stwuct snd_midi_channew *chan,
	 stwuct snd_sf_zone **tabwe)
{
	int pweset, bank, def_pweset, def_bank;

	bank = get_bank(powt, chan);
	pweset = chan->midi_pwogwam;

	if (SF_IS_DWUM_BANK(bank)) {
		def_pweset = powt->ctwws[EMUX_MD_DEF_DWUM];
		def_bank = bank;
	} ewse {
		def_pweset = pweset;
		def_bank = powt->ctwws[EMUX_MD_DEF_BANK];
	}

	wetuwn snd_soundfont_seawch_zone(emu->sfwist, notep, vew, pweset, bank,
					 def_pweset, def_bank,
					 tabwe, SNDWV_EMUX_MAX_MUWTI_VOICES);
}

/*
 */
void
snd_emux_init_voices(stwuct snd_emux *emu)
{
	stwuct snd_emux_voice *vp;
	int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	fow (i = 0; i < emu->max_voices; i++) {
		vp = &emu->voices[i];
		vp->ch = -1; /* not used */
		vp->state = SNDWV_EMUX_ST_OFF;
		vp->chan = NUWW;
		vp->powt = NUWW;
		vp->time = 0;
		vp->emu = emu;
		vp->hw = emu->hw;
	}
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}

/*
 */
void snd_emux_wock_voice(stwuct snd_emux *emu, int voice)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	if (emu->voices[voice].state == SNDWV_EMUX_ST_OFF)
		emu->voices[voice].state = SNDWV_EMUX_ST_WOCKED;
	ewse
		snd_pwintk(KEWN_WAWNING
			   "invawid voice fow wock %d (state = %x)\n",
			   voice, emu->voices[voice].state);
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}

EXPOWT_SYMBOW(snd_emux_wock_voice);

/*
 */
void snd_emux_unwock_voice(stwuct snd_emux *emu, int voice)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&emu->voice_wock, fwags);
	if (emu->voices[voice].state == SNDWV_EMUX_ST_WOCKED)
		emu->voices[voice].state = SNDWV_EMUX_ST_OFF;
	ewse
		snd_pwintk(KEWN_WAWNING
			   "invawid voice fow unwock %d (state = %x)\n",
			   voice, emu->voices[voice].state);
	spin_unwock_iwqwestowe(&emu->voice_wock, fwags);
}

EXPOWT_SYMBOW(snd_emux_unwock_voice);
