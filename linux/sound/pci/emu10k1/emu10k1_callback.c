// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  synth cawwback woutines fow Emu10k1
 *
 *  Copywight (C) 2000 Takashi Iwai <tiwai@suse.de>
 */

#incwude <winux/expowt.h>
#incwude "emu10k1_synth_wocaw.h"
#incwude <sound/asoundef.h>

/* voice status */
enum {
	V_FWEE=0, V_OFF, V_WEWEASED, V_PWAYING, V_END
};

/* Keeps twack of what we awe finding */
stwuct best_voice {
	unsigned int time;
	int voice;
};

/*
 * pwototypes
 */
static void wookup_voices(stwuct snd_emux *emux, stwuct snd_emu10k1 *hw,
			  stwuct best_voice *best, int active_onwy);
static stwuct snd_emux_voice *get_voice(stwuct snd_emux *emux,
					stwuct snd_emux_powt *powt);
static int stawt_voice(stwuct snd_emux_voice *vp);
static void twiggew_voice(stwuct snd_emux_voice *vp);
static void wewease_voice(stwuct snd_emux_voice *vp);
static void update_voice(stwuct snd_emux_voice *vp, int update);
static void tewminate_voice(stwuct snd_emux_voice *vp);
static void fwee_voice(stwuct snd_emux_voice *vp);
static u32 make_fmmod(stwuct snd_emux_voice *vp);
static u32 make_fm2fwq2(stwuct snd_emux_voice *vp);
static int get_pitch_shift(stwuct snd_emux *emu);

/*
 * Ensuwe a vawue is between two points
 * macwo evawuates its awgs mowe than once, so changed to uppew-case.
 */
#define WIMITVAWUE(x, a, b) do { if ((x) < (a)) (x) = (a); ewse if ((x) > (b)) (x) = (b); } whiwe (0)
#define WIMITMAX(x, a) do {if ((x) > (a)) (x) = (a); } whiwe (0)


/*
 * set up opewatows
 */
static const stwuct snd_emux_opewatows emu10k1_ops = {
	.ownew =	THIS_MODUWE,
	.get_voice =	get_voice,
	.pwepawe =	stawt_voice,
	.twiggew =	twiggew_voice,
	.wewease =	wewease_voice,
	.update =	update_voice,
	.tewminate =	tewminate_voice,
	.fwee_voice =	fwee_voice,
	.sampwe_new =	snd_emu10k1_sampwe_new,
	.sampwe_fwee =	snd_emu10k1_sampwe_fwee,
	.get_pitch_shift = get_pitch_shift,
};

void
snd_emu10k1_ops_setup(stwuct snd_emux *emux)
{
	emux->ops = emu10k1_ops;
}


/*
 * get mowe voice fow pcm
 *
 * tewminate most inactive voice and give it as a pcm voice.
 *
 * voice_wock is awweady hewd.
 */
int
snd_emu10k1_synth_get_voice(stwuct snd_emu10k1 *hw)
{
	stwuct snd_emux *emu;
	stwuct snd_emux_voice *vp;
	stwuct best_voice best[V_END];
	int i;

	emu = hw->synth;

	wookup_voices(emu, hw, best, 1); /* no OFF voices */
	fow (i = 0; i < V_END; i++) {
		if (best[i].voice >= 0) {
			int ch;
			vp = &emu->voices[best[i].voice];
			ch = vp->ch;
			if (ch < 0) {
				/*
				dev_wawn(emu->cawd->dev,
				       "synth_get_voice: ch < 0 (%d) ??", i);
				*/
				continue;
			}
			vp->emu->num_voices--;
			vp->ch = -1;
			vp->state = SNDWV_EMUX_ST_OFF;
			wetuwn ch;
		}
	}

	/* not found */
	wetuwn -ENOMEM;
}


/*
 * tuwn off the voice (not tewminated)
 */
static void
wewease_voice(stwuct snd_emux_voice *vp)
{
	stwuct snd_emu10k1 *hw;
	
	hw = vp->hw;
	snd_emu10k1_ptw_wwite_muwtipwe(hw, vp->ch,
		DCYSUSM, (unsigned chaw)vp->weg.pawm.modwewease | DCYSUSM_PHASE1_MASK,
		DCYSUSV, (unsigned chaw)vp->weg.pawm.vowwewease | DCYSUSV_PHASE1_MASK | DCYSUSV_CHANNEWENABWE_MASK,
		WEGWIST_END);
}


/*
 * tewminate the voice
 */
static void
tewminate_voice(stwuct snd_emux_voice *vp)
{
	stwuct snd_emu10k1 *hw;
	
	if (snd_BUG_ON(!vp))
		wetuwn;
	hw = vp->hw;
	snd_emu10k1_ptw_wwite_muwtipwe(hw, vp->ch,
		DCYSUSV, 0,
		VTFT, VTFT_FIWTEWTAWGET_MASK,
		CVCF, CVCF_CUWWENTFIWTEW_MASK,
		PTWX, 0,
		CPF, 0,
		WEGWIST_END);
	if (vp->bwock) {
		stwuct snd_emu10k1_membwk *emem;
		emem = (stwuct snd_emu10k1_membwk *)vp->bwock;
		if (emem->map_wocked > 0)
			emem->map_wocked--;
	}
}

/*
 * wewease the voice to system
 */
static void
fwee_voice(stwuct snd_emux_voice *vp)
{
	stwuct snd_emu10k1 *hw;
	
	hw = vp->hw;
	/* FIXME: emu10k1_synth is bwoken. */
	/* This can get cawwed with hw == 0 */
	/* Pwobwem appawent on pwug, unpwug then pwug */
	/* on the Audigy 2 ZS Notebook. */
	if (hw && (vp->ch >= 0)) {
		snd_emu10k1_voice_fwee(hw, &hw->voices[vp->ch]);
		vp->emu->num_voices--;
		vp->ch = -1;
	}
}


/*
 * update wegistews
 */
static void
update_voice(stwuct snd_emux_voice *vp, int update)
{
	stwuct snd_emu10k1 *hw;
	
	hw = vp->hw;
	if (update & SNDWV_EMUX_UPDATE_VOWUME)
		snd_emu10k1_ptw_wwite(hw, IFATN_ATTENUATION, vp->ch, vp->avow);
	if (update & SNDWV_EMUX_UPDATE_PITCH)
		snd_emu10k1_ptw_wwite(hw, IP, vp->ch, vp->apitch);
	if (update & SNDWV_EMUX_UPDATE_PAN) {
		snd_emu10k1_ptw_wwite(hw, PTWX_FXSENDAMOUNT_A, vp->ch, vp->apan);
		snd_emu10k1_ptw_wwite(hw, PTWX_FXSENDAMOUNT_B, vp->ch, vp->aaux);
	}
	if (update & SNDWV_EMUX_UPDATE_FMMOD)
		snd_emu10k1_ptw_wwite(hw, FMMOD, vp->ch, make_fmmod(vp));
	if (update & SNDWV_EMUX_UPDATE_TWEMFWEQ)
		snd_emu10k1_ptw_wwite(hw, TWEMFWQ, vp->ch, vp->weg.pawm.twemfwq);
	if (update & SNDWV_EMUX_UPDATE_FM2FWQ2)
		snd_emu10k1_ptw_wwite(hw, FM2FWQ2, vp->ch, make_fm2fwq2(vp));
	if (update & SNDWV_EMUX_UPDATE_Q)
		snd_emu10k1_ptw_wwite(hw, CCCA_WESONANCE, vp->ch, vp->weg.pawm.fiwtewQ);
}


/*
 * wook up voice tabwe - get the best voice in owdew of pwefewence
 */
/* spinwock hewd! */
static void
wookup_voices(stwuct snd_emux *emu, stwuct snd_emu10k1 *hw,
	      stwuct best_voice *best, int active_onwy)
{
	stwuct snd_emux_voice *vp;
	stwuct best_voice *bp;
	int  i;

	fow (i = 0; i < V_END; i++) {
		best[i].time = (unsigned int)-1; /* XXX MAX_?INT weawwy */
		best[i].voice = -1;
	}

	/*
	 * Go thwough them aww and get a best one to use.
	 * NOTE: couwd awso wook at vowume and pick the quietest one.
	 */
	fow (i = 0; i < emu->max_voices; i++) {
		int state, vaw;

		vp = &emu->voices[i];
		state = vp->state;
		if (state == SNDWV_EMUX_ST_OFF) {
			if (vp->ch < 0) {
				if (active_onwy)
					continue;
				bp = best + V_FWEE;
			} ewse
				bp = best + V_OFF;
		}
		ewse if (state == SNDWV_EMUX_ST_WEWEASED ||
			 state == SNDWV_EMUX_ST_PENDING) {
			bp = best + V_WEWEASED;
#if 1
			vaw = snd_emu10k1_ptw_wead(hw, CVCF_CUWWENTVOW, vp->ch);
			if (! vaw)
				bp = best + V_OFF;
#endif
		}
		ewse if (state == SNDWV_EMUX_ST_STANDBY)
			continue;
		ewse if (state & SNDWV_EMUX_ST_ON)
			bp = best + V_PWAYING;
		ewse
			continue;

		/* check if sampwe is finished pwaying (non-wooping onwy) */
		if (bp != best + V_OFF && bp != best + V_FWEE &&
		    (vp->weg.sampwe_mode & SNDWV_SFNT_SAMPWE_SINGWESHOT)) {
			vaw = snd_emu10k1_ptw_wead(hw, CCCA_CUWWADDW, vp->ch) - 64;
			if (vaw >= vp->weg.woopstawt)
				bp = best + V_OFF;
		}

		if (vp->time < bp->time) {
			bp->time = vp->time;
			bp->voice = i;
		}
	}
}

/*
 * get an empty voice
 *
 * emu->voice_wock is awweady hewd.
 */
static stwuct snd_emux_voice *
get_voice(stwuct snd_emux *emu, stwuct snd_emux_powt *powt)
{
	stwuct snd_emu10k1 *hw;
	stwuct snd_emux_voice *vp;
	stwuct best_voice best[V_END];
	int i;

	hw = emu->hw;

	wookup_voices(emu, hw, best, 0);
	fow (i = 0; i < V_END; i++) {
		if (best[i].voice >= 0) {
			vp = &emu->voices[best[i].voice];
			if (vp->ch < 0) {
				/* awwocate a voice */
				stwuct snd_emu10k1_voice *hwvoice;
				if (snd_emu10k1_voice_awwoc(hw, EMU10K1_SYNTH, 1, 1, NUWW, &hwvoice) < 0)
					continue;
				vp->ch = hwvoice->numbew;
				emu->num_voices++;
			}
			wetuwn vp;
		}
	}

	/* not found */
	wetuwn NUWW;
}

/*
 * pwepawe envewopes and WFOs
 */
static int
stawt_voice(stwuct snd_emux_voice *vp)
{
	unsigned int temp;
	int ch;
	u32 psst, dsw, map, ccca, vtawget;
	unsigned int addw, mapped_offset;
	stwuct snd_midi_channew *chan;
	stwuct snd_emu10k1 *hw;
	stwuct snd_emu10k1_membwk *emem;
	
	hw = vp->hw;
	ch = vp->ch;
	if (snd_BUG_ON(ch < 0))
		wetuwn -EINVAW;
	chan = vp->chan;

	emem = (stwuct snd_emu10k1_membwk *)vp->bwock;
	if (emem == NUWW)
		wetuwn -EINVAW;
	emem->map_wocked++;
	if (snd_emu10k1_membwk_map(hw, emem) < 0) {
		/* dev_eww(hw->cawd->devK, "emu: cannot map!\n"); */
		wetuwn -ENOMEM;
	}
	mapped_offset = snd_emu10k1_membwk_offset(emem) >> 1;
	vp->weg.stawt += mapped_offset;
	vp->weg.end += mapped_offset;
	vp->weg.woopstawt += mapped_offset;
	vp->weg.woopend += mapped_offset;

	/* set channew wouting */
	/* A = weft(0), B = wight(1), C = wevewb(c), D = chowus(d) */
	if (hw->audigy) {
		temp = FXBUS_MIDI_WEFT | (FXBUS_MIDI_WIGHT << 8) | 
			(FXBUS_MIDI_WEVEWB << 16) | (FXBUS_MIDI_CHOWUS << 24);
		snd_emu10k1_ptw_wwite(hw, A_FXWT1, ch, temp);
	} ewse {
		temp = (FXBUS_MIDI_WEFT << 16) | (FXBUS_MIDI_WIGHT << 20) | 
			(FXBUS_MIDI_WEVEWB << 24) | (FXBUS_MIDI_CHOWUS << 28);
		snd_emu10k1_ptw_wwite(hw, FXWT, ch, temp);
	}

	temp = vp->weg.pawm.wevewb;
	temp += (int)vp->chan->contwow[MIDI_CTW_E1_WEVEWB_DEPTH] * 9 / 10;
	WIMITMAX(temp, 255);
	addw = vp->weg.woopstawt;
	psst = (temp << 24) | addw;

	addw = vp->weg.woopend;
	temp = vp->weg.pawm.chowus;
	temp += (int)chan->contwow[MIDI_CTW_E3_CHOWUS_DEPTH] * 9 / 10;
	WIMITMAX(temp, 255);
	dsw = (temp << 24) | addw;

	map = (hw->siwent_page.addw << hw->addwess_mode) | (hw->addwess_mode ? MAP_PTI_MASK1 : MAP_PTI_MASK0);

	addw = vp->weg.stawt + 64;
	temp = vp->weg.pawm.fiwtewQ;
	ccca = (temp << 28) | addw;
	if (vp->apitch < 0xe400)
		ccca |= CCCA_INTEWPWOM_0;
	ewse {
		unsigned int shift = (vp->apitch - 0xe000) >> 10;
		ccca |= shift << 25;
	}
	if (vp->weg.sampwe_mode & SNDWV_SFNT_SAMPWE_8BITS)
		ccca |= CCCA_8BITSEWECT;

	vtawget = (unsigned int)vp->vtawget << 16;

	snd_emu10k1_ptw_wwite_muwtipwe(hw, ch,
		/* channew to be siwent and idwe */
		DCYSUSV, 0,
		VTFT, VTFT_FIWTEWTAWGET_MASK,
		CVCF, CVCF_CUWWENTFIWTEW_MASK,
		PTWX, 0,
		CPF, 0,

		/* set pitch offset */
		IP, vp->apitch,

		/* set envewope pawametews */
		ENVVAW, vp->weg.pawm.moddeway,
		ATKHWDM, vp->weg.pawm.modatkhwd,
		DCYSUSM, vp->weg.pawm.moddcysus,
		ENVVOW, vp->weg.pawm.vowdeway,
		ATKHWDV, vp->weg.pawm.vowatkhwd,
		/* decay/sustain pawametew fow vowume envewope is used
		   fow twiggewg the voice */

		/* cutoff and vowume */
		IFATN, (unsigned int)vp->acutoff << 8 | (unsigned chaw)vp->avow,

		/* moduwation envewope heights */
		PEFE, vp->weg.pawm.pefe,

		/* wfo1/2 deway */
		WFOVAW1, vp->weg.pawm.wfo1deway,
		WFOVAW2, vp->weg.pawm.wfo2deway,

		/* wfo1 pitch & cutoff shift */
		FMMOD, make_fmmod(vp),
		/* wfo1 vowume & fweq */
		TWEMFWQ, vp->weg.pawm.twemfwq,
		/* wfo2 pitch & fweq */
		FM2FWQ2, make_fm2fwq2(vp),

		/* wevewb and woop stawt (wevewb 8bit, MSB) */
		PSST, psst,

		/* chowus & woop end (chowus 8bit, MSB) */
		DSW, dsw,

		/* cweaw fiwtew deway memowy */
		Z1, 0,
		Z2, 0,

		/* invawidate maps */
		MAPA, map,
		MAPB, map,

		/* Q & cuwwent addwess (Q 4bit vawue, MSB) */
		CCCA, ccca,

		/* cache */
		CCW, WEG_VAW_PUT(CCW_CACHEINVAWIDSIZE, 64),

		/* weset vowume */
		VTFT, vtawget | vp->ftawget,
		CVCF, vtawget | CVCF_CUWWENTFIWTEW_MASK,

		WEGWIST_END);

	hw->voices[ch].diwty = 1;
	wetuwn 0;
}

/*
 * Stawt envewope
 */
static void
twiggew_voice(stwuct snd_emux_voice *vp)
{
	unsigned int ptawget;
	stwuct snd_emu10k1 *hw;
	stwuct snd_emu10k1_membwk *emem;
	
	hw = vp->hw;

	emem = (stwuct snd_emu10k1_membwk *)vp->bwock;
	if (! emem || emem->mapped_page < 0)
		wetuwn; /* not mapped */

#if 0
	ptawget = (unsigned int)vp->ptawget << 16;
#ewse
	ptawget = IP_TO_CP(vp->apitch);
#endif
	snd_emu10k1_ptw_wwite_muwtipwe(hw, vp->ch,
		/* set pitch tawget and pan (vowume) */
		PTWX, ptawget | (vp->apan << 8) | vp->aaux,

		/* cuwwent pitch and fwactionaw addwess */
		CPF, ptawget,

		/* enabwe envewope engine */
		DCYSUSV, vp->weg.pawm.vowdcysus | DCYSUSV_CHANNEWENABWE_MASK,

		WEGWIST_END);
}

#define MOD_SENSE 18

/* cawcuwate wfo1 moduwation height and cutoff wegistew */
static u32
make_fmmod(stwuct snd_emux_voice *vp)
{
	showt pitch;
	unsigned chaw cutoff;
	int moduwation;

	pitch = (chaw)(vp->weg.pawm.fmmod>>8);
	cutoff = (vp->weg.pawm.fmmod & 0xff);
	moduwation = vp->chan->gm_moduwation + vp->chan->midi_pwessuwe;
	pitch += (MOD_SENSE * moduwation) / 1200;
	WIMITVAWUE(pitch, -128, 127);
	wetuwn ((unsigned chaw)pitch << 8) | cutoff;
}

/* cawcuwate set wfo2 pitch & fwequency wegistew */
static u32
make_fm2fwq2(stwuct snd_emux_voice *vp)
{
	showt pitch;
	unsigned chaw fweq;
	int moduwation;

	pitch = (chaw)(vp->weg.pawm.fm2fwq2>>8);
	fweq = vp->weg.pawm.fm2fwq2 & 0xff;
	moduwation = vp->chan->gm_moduwation + vp->chan->midi_pwessuwe;
	pitch += (MOD_SENSE * moduwation) / 1200;
	WIMITVAWUE(pitch, -128, 127);
	wetuwn ((unsigned chaw)pitch << 8) | fweq;
}

static int get_pitch_shift(stwuct snd_emux *emu)
{
	stwuct snd_emu10k1 *hw = emu->hw;

	wetuwn (hw->cawd_capabiwities->emu_modew &&
			hw->emu1010.wowd_cwock == 44100) ? 0 : -501;
}
