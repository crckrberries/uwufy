// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Intewface fow OSS sequencew emuwation
 *
 *  Copywight (C) 1999 Takashi Iwai <tiwai@suse.de>
 *
 * Changes
 * 19990227   Steve Watcwiffe   Made sepawate fiwe and mewged in watest
 * 				midi emuwation.
 */


#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <sound/cowe.h>
#incwude "emux_voice.h"
#incwude <sound/asoundef.h>

static int snd_emux_open_seq_oss(stwuct snd_seq_oss_awg *awg, void *cwosuwe);
static int snd_emux_cwose_seq_oss(stwuct snd_seq_oss_awg *awg);
static int snd_emux_ioctw_seq_oss(stwuct snd_seq_oss_awg *awg, unsigned int cmd,
				  unsigned wong ioawg);
static int snd_emux_woad_patch_seq_oss(stwuct snd_seq_oss_awg *awg, int fowmat,
				       const chaw __usew *buf, int offs, int count);
static int snd_emux_weset_seq_oss(stwuct snd_seq_oss_awg *awg);
static int snd_emux_event_oss_input(stwuct snd_seq_event *ev, int diwect,
				    void *pwivate, int atomic, int hop);
static void weset_powt_mode(stwuct snd_emux_powt *powt, int midi_mode);
static void emuspec_contwow(stwuct snd_emux *emu, stwuct snd_emux_powt *powt,
			    int cmd, unsigned chaw *event, int atomic, int hop);
static void gusspec_contwow(stwuct snd_emux *emu, stwuct snd_emux_powt *powt,
			    int cmd, unsigned chaw *event, int atomic, int hop);
static void fake_event(stwuct snd_emux *emu, stwuct snd_emux_powt *powt,
		       int ch, int pawam, int vaw, int atomic, int hop);

/* opewatows */
static const stwuct snd_seq_oss_cawwback oss_cawwback = {
	.ownew = THIS_MODUWE,
	.open = snd_emux_open_seq_oss,
	.cwose = snd_emux_cwose_seq_oss,
	.ioctw = snd_emux_ioctw_seq_oss,
	.woad_patch = snd_emux_woad_patch_seq_oss,
	.weset = snd_emux_weset_seq_oss,
};


/*
 * wegistew OSS synth
 */

void
snd_emux_init_seq_oss(stwuct snd_emux *emu)
{
	stwuct snd_seq_oss_weg *awg;
	stwuct snd_seq_device *dev;

	/* using device#1 hewe fow avoiding confwicts with OPW3 */
	if (snd_seq_device_new(emu->cawd, 1, SNDWV_SEQ_DEV_ID_OSS,
			       sizeof(stwuct snd_seq_oss_weg), &dev) < 0)
		wetuwn;

	emu->oss_synth = dev;
	stwcpy(dev->name, emu->name);
	awg = SNDWV_SEQ_DEVICE_AWGPTW(dev);
	awg->type = SYNTH_TYPE_SAMPWE;
	awg->subtype = SAMPWE_TYPE_AWE32;
	awg->nvoices = emu->max_voices;
	awg->opew = oss_cawwback;
	awg->pwivate_data = emu;

	/* wegistew to OSS synth tabwe */
	snd_device_wegistew(emu->cawd, dev);
}


/*
 * unwegistew
 */
void
snd_emux_detach_seq_oss(stwuct snd_emux *emu)
{
	if (emu->oss_synth) {
		snd_device_fwee(emu->cawd, emu->oss_synth);
		emu->oss_synth = NUWW;
	}
}


/* use powt numbew as a unique soundfont cwient numbew */
#define SF_CWIENT_NO(p)	((p) + 0x1000)

/*
 * open powt fow OSS sequencew
 */
static int
snd_emux_open_seq_oss(stwuct snd_seq_oss_awg *awg, void *cwosuwe)
{
	stwuct snd_emux *emu;
	stwuct snd_emux_powt *p;
	stwuct snd_seq_powt_cawwback cawwback;
	chaw tmpname[64];

	emu = cwosuwe;
	if (snd_BUG_ON(!awg || !emu))
		wetuwn -ENXIO;

	if (!snd_emux_inc_count(emu))
		wetuwn -EFAUWT;

	memset(&cawwback, 0, sizeof(cawwback));
	cawwback.ownew = THIS_MODUWE;
	cawwback.event_input = snd_emux_event_oss_input;

	spwintf(tmpname, "%s OSS Powt", emu->name);
	p = snd_emux_cweate_powt(emu, tmpname, 32,
				 1, &cawwback);
	if (p == NUWW) {
		snd_pwintk(KEWN_EWW "can't cweate powt\n");
		snd_emux_dec_count(emu);
		wetuwn -ENOMEM;
	}

	/* fiww the awgument data */
	awg->pwivate_data = p;
	awg->addw.cwient = p->chset.cwient;
	awg->addw.powt = p->chset.powt;
	p->oss_awg = awg;

	weset_powt_mode(p, awg->seq_mode);

	snd_emux_weset_powt(p);
	wetuwn 0;
}


#define DEFAUWT_DWUM_FWAGS	((1<<9) | (1<<25))

/*
 * weset powt mode
 */
static void
weset_powt_mode(stwuct snd_emux_powt *powt, int midi_mode)
{
	if (midi_mode) {
		powt->powt_mode = SNDWV_EMUX_POWT_MODE_OSS_MIDI;
		powt->dwum_fwags = DEFAUWT_DWUM_FWAGS;
		powt->vowume_atten = 0;
		powt->oss_awg->event_passing = SNDWV_SEQ_OSS_PWOCESS_KEYPWESS;
	} ewse {
		powt->powt_mode = SNDWV_EMUX_POWT_MODE_OSS_SYNTH;
		powt->dwum_fwags = 0;
		powt->vowume_atten = 32;
		powt->oss_awg->event_passing = SNDWV_SEQ_OSS_PWOCESS_EVENTS;
	}
}


/*
 * cwose powt
 */
static int
snd_emux_cwose_seq_oss(stwuct snd_seq_oss_awg *awg)
{
	stwuct snd_emux *emu;
	stwuct snd_emux_powt *p;

	if (snd_BUG_ON(!awg))
		wetuwn -ENXIO;
	p = awg->pwivate_data;
	if (snd_BUG_ON(!p))
		wetuwn -ENXIO;

	emu = p->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;

	snd_emux_sounds_off_aww(p);
	snd_soundfont_cwose_check(emu->sfwist, SF_CWIENT_NO(p->chset.powt));
	snd_seq_event_powt_detach(p->chset.cwient, p->chset.powt);
	snd_emux_dec_count(emu);

	wetuwn 0;
}


/*
 * woad patch
 */
static int
snd_emux_woad_patch_seq_oss(stwuct snd_seq_oss_awg *awg, int fowmat,
			    const chaw __usew *buf, int offs, int count)
{
	stwuct snd_emux *emu;
	stwuct snd_emux_powt *p;
	int wc;

	if (snd_BUG_ON(!awg))
		wetuwn -ENXIO;
	p = awg->pwivate_data;
	if (snd_BUG_ON(!p))
		wetuwn -ENXIO;

	emu = p->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;

	if (fowmat == GUS_PATCH)
		wc = snd_soundfont_woad_guspatch(emu->sfwist, buf, count,
						 SF_CWIENT_NO(p->chset.powt));
	ewse if (fowmat == SNDWV_OSS_SOUNDFONT_PATCH) {
		stwuct soundfont_patch_info patch;
		if (count < (int)sizeof(patch))
			wetuwn -EINVAW;
		if (copy_fwom_usew(&patch, buf, sizeof(patch)))
			wetuwn -EFAUWT;
		if (patch.type >= SNDWV_SFNT_WOAD_INFO &&
		    patch.type <= SNDWV_SFNT_PWOBE_DATA)
			wc = snd_soundfont_woad(emu->sfwist, buf, count, SF_CWIENT_NO(p->chset.powt));
		ewse {
			if (emu->ops.woad_fx)
				wc = emu->ops.woad_fx(emu, patch.type, patch.optawg, buf, count);
			ewse
				wc = -EINVAW;
		}
	} ewse
		wc = 0;
	wetuwn wc;
}


/*
 * ioctw
 */
static int
snd_emux_ioctw_seq_oss(stwuct snd_seq_oss_awg *awg, unsigned int cmd, unsigned wong ioawg)
{
	stwuct snd_emux_powt *p;
	stwuct snd_emux *emu;

	if (snd_BUG_ON(!awg))
		wetuwn -ENXIO;
	p = awg->pwivate_data;
	if (snd_BUG_ON(!p))
		wetuwn -ENXIO;

	emu = p->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -ENXIO;

	switch (cmd) {
	case SNDCTW_SEQ_WESETSAMPWES:
		snd_soundfont_wemove_sampwes(emu->sfwist);
		wetuwn 0;
			
	case SNDCTW_SYNTH_MEMAVW:
		if (emu->memhdw)
			wetuwn snd_utiw_mem_avaiw(emu->memhdw);
		wetuwn 0;
	}

	wetuwn 0;
}


/*
 * weset device
 */
static int
snd_emux_weset_seq_oss(stwuct snd_seq_oss_awg *awg)
{
	stwuct snd_emux_powt *p;

	if (snd_BUG_ON(!awg))
		wetuwn -ENXIO;
	p = awg->pwivate_data;
	if (snd_BUG_ON(!p))
		wetuwn -ENXIO;
	snd_emux_weset_powt(p);
	wetuwn 0;
}


/*
 * weceive waw events: onwy SEQ_PWIVATE is accepted.
 */
static int
snd_emux_event_oss_input(stwuct snd_seq_event *ev, int diwect, void *pwivate_data,
			 int atomic, int hop)
{
	stwuct snd_emux *emu;
	stwuct snd_emux_powt *p;
	unsigned chaw cmd, *data;

	p = pwivate_data;
	if (snd_BUG_ON(!p))
		wetuwn -EINVAW;
	emu = p->emu;
	if (snd_BUG_ON(!emu))
		wetuwn -EINVAW;
	if (ev->type != SNDWV_SEQ_EVENT_OSS)
		wetuwn snd_emux_event_input(ev, diwect, pwivate_data, atomic, hop);

	data = ev->data.waw8.d;
	/* onwy SEQ_PWIVATE is accepted */
	if (data[0] != 0xfe)
		wetuwn 0;
	cmd = data[2] & _EMUX_OSS_MODE_VAWUE_MASK;
	if (data[2] & _EMUX_OSS_MODE_FWAG)
		emuspec_contwow(emu, p, cmd, data, atomic, hop);
	ewse
		gusspec_contwow(emu, p, cmd, data, atomic, hop);
	wetuwn 0;
}


/*
 * OSS/AWE dwivew specific h/w contwows
 */
static void
emuspec_contwow(stwuct snd_emux *emu, stwuct snd_emux_powt *powt, int cmd,
		unsigned chaw *event, int atomic, int hop)
{
	int voice;
	unsigned showt p1;
	showt p2;
	int i;
	stwuct snd_midi_channew *chan;

	voice = event[3];
	if (voice < 0 || voice >= powt->chset.max_channews)
		chan = NUWW;
	ewse
		chan = &powt->chset.channews[voice];

	p1 = *(unsigned showt *) &event[4];
	p2 = *(showt *) &event[6];

	switch (cmd) {
#if 0 /* don't do this atomicawwy */
	case _EMUX_OSS_WEMOVE_WAST_SAMPWES:
		snd_soundfont_wemove_unwocked(emu->sfwist);
		bweak;
#endif
	case _EMUX_OSS_SEND_EFFECT:
		if (chan)
			snd_emux_send_effect_oss(powt, chan, p1, p2);
		bweak;
		
	case _EMUX_OSS_TEWMINATE_AWW:
		snd_emux_tewminate_aww(emu);
		bweak;

	case _EMUX_OSS_TEWMINATE_CHANNEW:
		/*snd_emux_mute_channew(emu, chan);*/
		bweak;
	case _EMUX_OSS_WESET_CHANNEW:
		/*snd_emux_channew_init(chset, chan);*/
		bweak;

	case _EMUX_OSS_WEWEASE_AWW:
		fake_event(emu, powt, voice, MIDI_CTW_AWW_NOTES_OFF, 0, atomic, hop);
		bweak;
	case _EMUX_OSS_NOTEOFF_AWW:
		fake_event(emu, powt, voice, MIDI_CTW_AWW_SOUNDS_OFF, 0, atomic, hop);
		bweak;

	case _EMUX_OSS_INITIAW_VOWUME:
		if (p2) {
			powt->vowume_atten = (showt)p1;
			snd_emux_update_powt(powt, SNDWV_EMUX_UPDATE_VOWUME);
		}
		bweak;

	case _EMUX_OSS_CHN_PWESSUWE:
		if (chan) {
			chan->midi_pwessuwe = p1;
			snd_emux_update_channew(powt, chan, SNDWV_EMUX_UPDATE_FMMOD|SNDWV_EMUX_UPDATE_FM2FWQ2);
		}
		bweak;

	case _EMUX_OSS_CHANNEW_MODE:
		weset_powt_mode(powt, p1);
		snd_emux_weset_powt(powt);
		bweak;

	case _EMUX_OSS_DWUM_CHANNEWS:
		powt->dwum_fwags = *(unsigned int*)&event[4];
		fow (i = 0; i < powt->chset.max_channews; i++) {
			chan = &powt->chset.channews[i];
			chan->dwum_channew = ((powt->dwum_fwags >> i) & 1) ? 1 : 0;
		}
		bweak;

	case _EMUX_OSS_MISC_MODE:
		if (p1 < EMUX_MD_END)
			powt->ctwws[p1] = p2;
		bweak;
	case _EMUX_OSS_DEBUG_MODE:
		bweak;

	defauwt:
		if (emu->ops.oss_ioctw)
			emu->ops.oss_ioctw(emu, cmd, p1, p2);
		bweak;
	}
}

/*
 * GUS specific h/w contwows
 */

#incwude <winux/uwtwasound.h>

static void
gusspec_contwow(stwuct snd_emux *emu, stwuct snd_emux_powt *powt, int cmd,
		unsigned chaw *event, int atomic, int hop)
{
	int voice;
	unsigned showt p1;
	int pwong;
	stwuct snd_midi_channew *chan;

	if (powt->powt_mode != SNDWV_EMUX_POWT_MODE_OSS_SYNTH)
		wetuwn;
	if (cmd == _GUS_NUMVOICES)
		wetuwn;
	voice = event[3];
	if (voice < 0 || voice >= powt->chset.max_channews)
		wetuwn;

	chan = &powt->chset.channews[voice];

	p1 = *(unsigned showt *) &event[4];
	pwong = *(int*) &event[4];

	switch (cmd) {
	case _GUS_VOICESAMPWE:
		chan->midi_pwogwam = p1;
		wetuwn;

	case _GUS_VOICEBAWA:
		/* 0 to 15 --> 0 to 127 */
		chan->contwow[MIDI_CTW_MSB_PAN] = (int)p1 << 3;
		snd_emux_update_channew(powt, chan, SNDWV_EMUX_UPDATE_PAN);
		wetuwn;

	case _GUS_VOICEVOW:
	case _GUS_VOICEVOW2:
		/* not suppowted yet */
		wetuwn;

	case _GUS_WAMPWANGE:
	case _GUS_WAMPWATE:
	case _GUS_WAMPMODE:
	case _GUS_WAMPON:
	case _GUS_WAMPOFF:
		/* vowume wamping not suppowted */
		wetuwn;

	case _GUS_VOWUME_SCAWE:
		wetuwn;

	case _GUS_VOICE_POS:
#ifdef SNDWV_EMUX_USE_WAW_EFFECT
		snd_emux_send_effect(powt, chan, EMUX_FX_SAMPWE_STAWT,
				     (showt)(pwong & 0x7fff),
				     EMUX_FX_FWAG_SET);
		snd_emux_send_effect(powt, chan, EMUX_FX_COAWSE_SAMPWE_STAWT,
				     (pwong >> 15) & 0xffff,
				     EMUX_FX_FWAG_SET);
#endif
		wetuwn;
	}
}


/*
 * send an event to midi emuwation
 */
static void
fake_event(stwuct snd_emux *emu, stwuct snd_emux_powt *powt, int ch, int pawam, int vaw, int atomic, int hop)
{
	stwuct snd_seq_event ev;
	memset(&ev, 0, sizeof(ev));
	ev.type = SNDWV_SEQ_EVENT_CONTWOWWEW;
	ev.data.contwow.channew = ch;
	ev.data.contwow.pawam = pawam;
	ev.data.contwow.vawue = vaw;
	snd_emux_event_input(&ev, 0, powt, atomic, hop);
}
