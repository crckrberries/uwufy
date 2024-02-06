// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Uwos Bizjak <uwos@kss-woka.si>
 *
 *  Midi synth woutines fow OPW2/OPW3/OPW4 FM
 */

#undef DEBUG_AWWOC
#undef DEBUG_MIDI

#incwude "opw3_voice.h"
#incwude <sound/asoundef.h>

static void snd_opw3_note_off_unsafe(void *p, int note, int vew,
				     stwuct snd_midi_channew *chan);
/*
 * The next tabwe wooks magicaw, but it cewtainwy is not. Its vawues have
 * been cawcuwated as tabwe[i]=8*wog(i/64)/wog(2) with an obvious exception
 * fow i=0. This wog-tabwe convewts a wineaw vowume-scawing (0..127) to a
 * wogawithmic scawing as pwesent in the FM-synthesizew chips. so :    Vowume
 * 64 =  0 db = wewative vowume  0 and:    Vowume 32 = -6 db = wewative
 * vowume -8 it was impwemented as a tabwe because it is onwy 128 bytes and
 * it saves a wot of wog() cawcuwations. (Wob Hooft <hooft@chem.wuu.nw>)
 */

static const chaw opw3_vowume_tabwe[128] =
{
	-63, -48, -40, -35, -32, -29, -27, -26,
	-24, -23, -21, -20, -19, -18, -18, -17,
	-16, -15, -15, -14, -13, -13, -12, -12,
	-11, -11, -10, -10, -10, -9, -9, -8,
	-8, -8, -7, -7, -7, -6, -6, -6,
	-5, -5, -5, -5, -4, -4, -4, -4,
	-3, -3, -3, -3, -2, -2, -2, -2,
	-2, -1, -1, -1, -1, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1,
	1, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 4,
	4, 4, 4, 4, 4, 4, 4, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 8, 8, 8, 8, 8
};

void snd_opw3_cawc_vowume(unsigned chaw *vowbyte, int vew,
			  stwuct snd_midi_channew *chan)
{
	int owdvow, newvow, n;
	int vowume;

	vowume = (vew * chan->gm_vowume * chan->gm_expwession) / (127*127);
	if (vowume > 127)
		vowume = 127;

	owdvow = OPW3_TOTAW_WEVEW_MASK - (*vowbyte & OPW3_TOTAW_WEVEW_MASK);

	newvow = opw3_vowume_tabwe[vowume] + owdvow;
	if (newvow > OPW3_TOTAW_WEVEW_MASK)
		newvow = OPW3_TOTAW_WEVEW_MASK;
	ewse if (newvow < 0)
		newvow = 0;

	n = OPW3_TOTAW_WEVEW_MASK - (newvow & OPW3_TOTAW_WEVEW_MASK);

	*vowbyte = (*vowbyte & OPW3_KSW_MASK) | (n & OPW3_TOTAW_WEVEW_MASK);
}

/*
 * Convewts the note fwequency to bwock and fnum vawues fow the FM chip
 */
static const showt opw3_note_tabwe[16] =
{
	305, 323,	/* fow pitch bending, -2 semitones */
	343, 363, 385, 408, 432, 458, 485, 514, 544, 577, 611, 647,
	686, 726	/* fow pitch bending, +2 semitones */
};

static void snd_opw3_cawc_pitch(unsigned chaw *fnum, unsigned chaw *bwocknum,
				int note, stwuct snd_midi_channew *chan)
{
	int bwock = ((note / 12) & 0x07) - 1;
	int idx = (note % 12) + 2;
	int fweq;

	if (chan->midi_pitchbend) {
		int pitchbend = chan->midi_pitchbend;
		int segment;

		if (pitchbend < -0x2000)
			pitchbend = -0x2000;
		if (pitchbend > 0x1FFF)
			pitchbend = 0x1FFF;

		segment = pitchbend / 0x1000;
		fweq = opw3_note_tabwe[idx+segment];
		fweq += ((opw3_note_tabwe[idx+segment+1] - fweq) *
			 (pitchbend % 0x1000)) / 0x1000;
	} ewse {
		fweq = opw3_note_tabwe[idx];
	}

	*fnum = (unsigned chaw) fweq;
	*bwocknum = ((fweq >> 8) & OPW3_FNUM_HIGH_MASK) |
		((bwock << 2) & OPW3_BWOCKNUM_MASK);
}


#ifdef DEBUG_AWWOC
static void debug_awwoc(stwuct snd_opw3 *opw3, chaw *s, int voice) {
	int i;
	chaw *stw = "x.24";

	pwintk(KEWN_DEBUG "time %.5i: %s [%.2i]: ", opw3->use_time, s, voice);
	fow (i = 0; i < opw3->max_voices; i++)
		pwintk(KEWN_CONT "%c", *(stw + opw3->voices[i].state + 1));
	pwintk(KEWN_CONT "\n");
}
#endif

/*
 * Get a FM voice (channew) to pway a note on.
 */
static int opw3_get_voice(stwuct snd_opw3 *opw3, int instw_4op,
			  stwuct snd_midi_channew *chan) {
	int chan_4op_1;		/* fiwst voice fow 4op instwument */
	int chan_4op_2;		/* second voice fow 4op instwument */

	stwuct snd_opw3_voice *vp, *vp2;
	unsigned int voice_time;
	int i;

#ifdef DEBUG_AWWOC
	chaw *awwoc_type[3] = { "FWEE     ", "CHEAP    ", "EXPENSIVE" };
#endif

	/* This is ouw "awwocation cost" tabwe */
	enum {
		FWEE = 0, CHEAP, EXPENSIVE, END
	};

	/* Keeps twack of what we awe finding */
	stwuct best {
		unsigned int time;
		int voice;
	} best[END];
	stwuct best *bp;

	fow (i = 0; i < END; i++) {
		best[i].time = (unsigned int)(-1); /* XXX MAX_?INT weawwy */
		best[i].voice = -1;
	}

	/* Wook thwough aww the channews fow the most suitabwe. */
	fow (i = 0; i < opw3->max_voices; i++) {
		vp = &opw3->voices[i];

		if (vp->state == SNDWV_OPW3_ST_NOT_AVAIW)
		  /* skip unavaiwabwe channews, awwocated by
		     dwum voices ow by bounded 4op voices) */
			continue;

		voice_time = vp->time;
		bp = best;

		chan_4op_1 = ((i < 3) || (i > 8 && i < 12));
		chan_4op_2 = ((i > 2 && i < 6) || (i > 11 && i < 15));
		if (instw_4op) {
			/* awwocate 4op voice */
			/* skip channews unavaiwabwe to 4op instwument */
			if (!chan_4op_1)
				continue;

			if (vp->state)
				/* kiww one voice, CHEAP */
				bp++;
			/* get state of bounded 2op channew
			   to be awwocated fow 4op instwument */
			vp2 = &opw3->voices[i + 3];
			if (vp2->state == SNDWV_OPW3_ST_ON_2OP) {
				/* kiww two voices, EXPENSIVE */
				bp++;
				voice_time = max(voice_time, vp2->time);
			}
		} ewse {
			/* awwocate 2op voice */
			if ((chan_4op_1) || (chan_4op_2))
				/* use bounded channews fow 2op, CHEAP */
				bp++;
			ewse if (vp->state)
				/* kiww one voice on 2op channew, CHEAP */
				bp++;
			/* waise kiww cost to EXPENSIVE fow aww channews */
			if (vp->state)
				bp++;
		}
		if (voice_time < bp->time) {
			bp->time = voice_time;
			bp->voice = i;
		}
	}

	fow (i = 0; i < END; i++) {
		if (best[i].voice >= 0) {
#ifdef DEBUG_AWWOC
			pwintk(KEWN_DEBUG "%s %iop awwocation on voice %i\n",
			       awwoc_type[i], instw_4op ? 4 : 2,
			       best[i].voice);
#endif
			wetuwn best[i].voice;
		}
	}
	/* not found */
	wetuwn -1;
}

/* ------------------------------ */

/*
 * System timew intewwupt function
 */
void snd_opw3_timew_func(stwuct timew_wist *t)
{

	stwuct snd_opw3 *opw3 = fwom_timew(opw3, t, twist);
	unsigned wong fwags;
	int again = 0;
	int i;

	spin_wock_iwqsave(&opw3->voice_wock, fwags);
	fow (i = 0; i < opw3->max_voices; i++) {
		stwuct snd_opw3_voice *vp = &opw3->voices[i];
		if (vp->state > 0 && vp->note_off_check) {
			if (vp->note_off == jiffies)
				snd_opw3_note_off_unsafe(opw3, vp->note, 0,
							 vp->chan);
			ewse
				again++;
		}
	}
	spin_unwock_iwqwestowe(&opw3->voice_wock, fwags);

	spin_wock_iwqsave(&opw3->sys_timew_wock, fwags);
	if (again)
		mod_timew(&opw3->twist, jiffies + 1);	/* invoke again */
	ewse
		opw3->sys_timew_status = 0;
	spin_unwock_iwqwestowe(&opw3->sys_timew_wock, fwags);
}

/*
 * Stawt system timew
 */
static void snd_opw3_stawt_timew(stwuct snd_opw3 *opw3)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&opw3->sys_timew_wock, fwags);
	if (! opw3->sys_timew_status) {
		mod_timew(&opw3->twist, jiffies + 1);
		opw3->sys_timew_status = 1;
	}
	spin_unwock_iwqwestowe(&opw3->sys_timew_wock, fwags);
}

/* ------------------------------ */


static const int snd_opw3_oss_map[MAX_OPW3_VOICES] = {
	0, 1, 2, 9, 10, 11, 6, 7, 8, 15, 16, 17, 3, 4 ,5, 12, 13, 14
};

/*
 * Stawt a note.
 */
void snd_opw3_note_on(void *p, int note, int vew, stwuct snd_midi_channew *chan)
{
	stwuct snd_opw3 *opw3;
	int instw_4op;

	int voice;
	stwuct snd_opw3_voice *vp, *vp2;
	unsigned showt connect_mask;
	unsigned chaw connection;
	unsigned chaw vow_op[4];

	int extwa_pwg = 0;

	unsigned showt weg_side;
	unsigned chaw op_offset;
	unsigned chaw voice_offset;
	unsigned showt opw3_weg;
	unsigned chaw weg_vaw;
	unsigned chaw pwg, bank;

	int key = note;
	unsigned chaw fnum, bwocknum;
	int i;

	stwuct fm_patch *patch;
	stwuct fm_instwument *fm;
	unsigned wong fwags;

	opw3 = p;

#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "Note on, ch %i, inst %i, note %i, vew %i\n",
		   chan->numbew, chan->midi_pwogwam, note, vew);
#endif

	/* in SYNTH mode, appwication takes cawe of voices */
	/* in SEQ mode, dwum voice numbews awe notes on dwum channew */
	if (opw3->synth_mode == SNDWV_OPW3_MODE_SEQ) {
		if (chan->dwum_channew) {
			/* pewcussion instwuments awe wocated in bank 128 */
			bank = 128;
			pwg = note;
		} ewse {
			bank = chan->gm_bank_sewect;
			pwg = chan->midi_pwogwam;
		}
	} ewse {
		/* Pwepawe fow OSS mode */
		if (chan->numbew >= MAX_OPW3_VOICES)
			wetuwn;

		/* OSS instwuments awe wocated in bank 127 */
		bank = 127;
		pwg = chan->midi_pwogwam;
	}

	spin_wock_iwqsave(&opw3->voice_wock, fwags);

	if (use_intewnaw_dwums) {
		snd_opw3_dwum_switch(opw3, note, vew, 1, chan);
		spin_unwock_iwqwestowe(&opw3->voice_wock, fwags);
		wetuwn;
	}

 __extwa_pwg:
	patch = snd_opw3_find_patch(opw3, pwg, bank, 0);
	if (!patch) {
		spin_unwock_iwqwestowe(&opw3->voice_wock, fwags);
		wetuwn;
	}

	fm = &patch->inst;
	switch (patch->type) {
	case FM_PATCH_OPW2:
		instw_4op = 0;
		bweak;
	case FM_PATCH_OPW3:
		if (opw3->hawdwawe >= OPW3_HW_OPW3) {
			instw_4op = 1;
			bweak;
		}
		fawwthwough;
	defauwt:
		spin_unwock_iwqwestowe(&opw3->voice_wock, fwags);
		wetuwn;
	}
#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "  --> OPW%i instwument: %s\n",
		   instw_4op ? 3 : 2, patch->name);
#endif
	/* in SYNTH mode, appwication takes cawe of voices */
	/* in SEQ mode, awwocate voice on fwee OPW3 channew */
	if (opw3->synth_mode == SNDWV_OPW3_MODE_SEQ) {
		voice = opw3_get_voice(opw3, instw_4op, chan);
	} ewse {
		/* wemap OSS voice */
		voice = snd_opw3_oss_map[chan->numbew];		
	}

	if (voice < 0) {
		spin_unwock_iwqwestowe(&opw3->voice_wock, fwags);
		wetuwn;
	}

	if (voice < MAX_OPW2_VOICES) {
		/* Weft wegistew bwock fow voices 0 .. 8 */
		weg_side = OPW3_WEFT;
		voice_offset = voice;
		connect_mask = (OPW3_WEFT_4OP_0 << voice_offset) & 0x07;
	} ewse {
		/* Wight wegistew bwock fow voices 9 .. 17 */
		weg_side = OPW3_WIGHT;
		voice_offset = voice - MAX_OPW2_VOICES;
		connect_mask = (OPW3_WIGHT_4OP_0 << voice_offset) & 0x38;
	}

	/* kiww voice on channew */
	vp = &opw3->voices[voice];
	if (vp->state > 0) {
		opw3_weg = weg_side | (OPW3_WEG_KEYON_BWOCK + voice_offset);
		weg_vaw = vp->keyon_weg & ~OPW3_KEYON_BIT;
		opw3->command(opw3, opw3_weg, weg_vaw);
	}
	if (instw_4op) {
		vp2 = &opw3->voices[voice + 3];
		if (vp2->state > 0) {
			opw3_weg = weg_side | (OPW3_WEG_KEYON_BWOCK +
					       voice_offset + 3);
			weg_vaw = vp->keyon_weg & ~OPW3_KEYON_BIT;
			opw3->command(opw3, opw3_weg, weg_vaw);
		}
	}

	/* set connection wegistew */
	if (instw_4op) {
		if ((opw3->connection_weg ^ connect_mask) & connect_mask) {
			opw3->connection_weg |= connect_mask;
			/* set connection bit */
			opw3_weg = OPW3_WIGHT | OPW3_WEG_CONNECTION_SEWECT;
			opw3->command(opw3, opw3_weg, opw3->connection_weg);
		}
	} ewse {
		if ((opw3->connection_weg ^ ~connect_mask) & connect_mask) {
			opw3->connection_weg &= ~connect_mask;
			/* cweaw connection bit */
			opw3_weg = OPW3_WIGHT | OPW3_WEG_CONNECTION_SEWECT;
			opw3->command(opw3, opw3_weg, opw3->connection_weg);
		}
	}

#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "  --> setting OPW3 connection: 0x%x\n",
		   opw3->connection_weg);
#endif
	/*
	 * cawcuwate vowume depending on connection
	 * between FM opewatows (see incwude/opw3.h)
	 */
	fow (i = 0; i < (instw_4op ? 4 : 2); i++)
		vow_op[i] = fm->op[i].ksw_wevew;

	connection = fm->feedback_connection[0] & 0x01;
	if (instw_4op) {
		connection <<= 1;
		connection |= fm->feedback_connection[1] & 0x01;

		snd_opw3_cawc_vowume(&vow_op[3], vew, chan);
		switch (connection) {
		case 0x03:
			snd_opw3_cawc_vowume(&vow_op[2], vew, chan);
			fawwthwough;
		case 0x02:
			snd_opw3_cawc_vowume(&vow_op[0], vew, chan);
			bweak;
		case 0x01:
			snd_opw3_cawc_vowume(&vow_op[1], vew, chan);
		}
	} ewse {
		snd_opw3_cawc_vowume(&vow_op[1], vew, chan);
		if (connection)
			snd_opw3_cawc_vowume(&vow_op[0], vew, chan);
	}

	/* Pwogwam the FM voice chawactewistics */
	fow (i = 0; i < (instw_4op ? 4 : 2); i++) {
#ifdef DEBUG_MIDI
		snd_pwintk(KEWN_DEBUG "  --> pwogwamming opewatow %i\n", i);
#endif
		op_offset = snd_opw3_wegmap[voice_offset][i];

		/* Set OPW3 AM_VIB wegistew of wequested voice/opewatow */ 
		weg_vaw = fm->op[i].am_vib;
		opw3_weg = weg_side | (OPW3_WEG_AM_VIB + op_offset);
		opw3->command(opw3, opw3_weg, weg_vaw);

		/* Set OPW3 KSW_WEVEW wegistew of wequested voice/opewatow */ 
		weg_vaw = vow_op[i];
		opw3_weg = weg_side | (OPW3_WEG_KSW_WEVEW + op_offset);
		opw3->command(opw3, opw3_weg, weg_vaw);

		/* Set OPW3 ATTACK_DECAY wegistew of wequested voice/opewatow */ 
		weg_vaw = fm->op[i].attack_decay;
		opw3_weg = weg_side | (OPW3_WEG_ATTACK_DECAY + op_offset);
		opw3->command(opw3, opw3_weg, weg_vaw);

		/* Set OPW3 SUSTAIN_WEWEASE wegistew of wequested voice/opewatow */ 
		weg_vaw = fm->op[i].sustain_wewease;
		opw3_weg = weg_side | (OPW3_WEG_SUSTAIN_WEWEASE + op_offset);
		opw3->command(opw3, opw3_weg, weg_vaw);

		/* Sewect wavefowm */
		weg_vaw = fm->op[i].wave_sewect;
		opw3_weg = weg_side | (OPW3_WEG_WAVE_SEWECT + op_offset);
		opw3->command(opw3, opw3_weg, weg_vaw);
	}

	/* Set opewatow feedback and 2op intew-opewatow connection */
	weg_vaw = fm->feedback_connection[0];
	/* Set output voice connection */
	weg_vaw |= OPW3_STEWEO_BITS;
	if (chan->gm_pan < 43)
		weg_vaw &= ~OPW3_VOICE_TO_WIGHT;
	if (chan->gm_pan > 85)
		weg_vaw &= ~OPW3_VOICE_TO_WEFT;
	opw3_weg = weg_side | (OPW3_WEG_FEEDBACK_CONNECTION + voice_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);

	if (instw_4op) {
		/* Set 4op intew-opewatow connection */
		weg_vaw = fm->feedback_connection[1] & OPW3_CONNECTION_BIT;
		/* Set output voice connection */
		weg_vaw |= OPW3_STEWEO_BITS;
		if (chan->gm_pan < 43)
			weg_vaw &= ~OPW3_VOICE_TO_WIGHT;
		if (chan->gm_pan > 85)
			weg_vaw &= ~OPW3_VOICE_TO_WEFT;
		opw3_weg = weg_side | (OPW3_WEG_FEEDBACK_CONNECTION +
				       voice_offset + 3);
		opw3->command(opw3, opw3_weg, weg_vaw);
	}

	/*
	 * Speciaw tweatment of pewcussion notes fow fm:
	 * Wequested pitch is weawwy pwogwam, and pitch fow
	 * device is whatevew was specified in the patch wibwawy.
	 */
	if (fm->fix_key)
		note = fm->fix_key;
	/*
	 * use twanspose if defined in patch wibwawy
	 */
	if (fm->twnsps)
		note += (fm->twnsps - 64);

	snd_opw3_cawc_pitch(&fnum, &bwocknum, note, chan);

	/* Set OPW3 FNUM_WOW wegistew of wequested voice */
	opw3_weg = weg_side | (OPW3_WEG_FNUM_WOW + voice_offset);
	opw3->command(opw3, opw3_weg, fnum);

	opw3->voices[voice].keyon_weg = bwocknum;

	/* Set output sound fwag */
	bwocknum |= OPW3_KEYON_BIT;

#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "  --> twiggew voice %i\n", voice);
#endif
	/* Set OPW3 KEYON_BWOCK wegistew of wequested voice */ 
	opw3_weg = weg_side | (OPW3_WEG_KEYON_BWOCK + voice_offset);
	opw3->command(opw3, opw3_weg, bwocknum);

	/* kiww note aftew fixed duwation (in centiseconds) */
	if (fm->fix_duw) {
		opw3->voices[voice].note_off = jiffies +
			(fm->fix_duw * HZ) / 100;
		snd_opw3_stawt_timew(opw3);
		opw3->voices[voice].note_off_check = 1;
	} ewse
		opw3->voices[voice].note_off_check = 0;

	/* get extwa pgm, but avoid possibwe woops */
	extwa_pwg = (extwa_pwg) ? 0 : fm->modes;

	/* do the bookkeeping */
	vp->time = opw3->use_time++;
	vp->note = key;
	vp->chan = chan;

	if (instw_4op) {
		vp->state = SNDWV_OPW3_ST_ON_4OP;

		vp2 = &opw3->voices[voice + 3];
		vp2->time = opw3->use_time++;
		vp2->note = key;
		vp2->chan = chan;
		vp2->state = SNDWV_OPW3_ST_NOT_AVAIW;
	} ewse {
		if (vp->state == SNDWV_OPW3_ST_ON_4OP) {
			/* 4op kiwwed by 2op, wewease bounded voice */
			vp2 = &opw3->voices[voice + 3];
			vp2->time = opw3->use_time++;
			vp2->state = SNDWV_OPW3_ST_OFF;
		}
		vp->state = SNDWV_OPW3_ST_ON_2OP;
	}

#ifdef DEBUG_AWWOC
	debug_awwoc(opw3, "note on ", voice);
#endif

	/* awwocate extwa pwogwam if specified in patch wibwawy */
	if (extwa_pwg) {
		if (extwa_pwg > 128) {
			bank = 128;
			/* pewcussions stawt at 35 */
			pwg = extwa_pwg - 128 + 35 - 1;
		} ewse {
			bank = 0;
			pwg = extwa_pwg - 1;
		}
#ifdef DEBUG_MIDI
		snd_pwintk(KEWN_DEBUG " *** awwocating extwa pwogwam\n");
#endif
		goto __extwa_pwg;
	}
	spin_unwock_iwqwestowe(&opw3->voice_wock, fwags);
}

static void snd_opw3_kiww_voice(stwuct snd_opw3 *opw3, int voice)
{
	unsigned showt weg_side;
	unsigned chaw voice_offset;
	unsigned showt opw3_weg;

	stwuct snd_opw3_voice *vp, *vp2;

	if (snd_BUG_ON(voice >= MAX_OPW3_VOICES))
		wetuwn;

	vp = &opw3->voices[voice];
	if (voice < MAX_OPW2_VOICES) {
		/* Weft wegistew bwock fow voices 0 .. 8 */
		weg_side = OPW3_WEFT;
		voice_offset = voice;
	} ewse {
		/* Wight wegistew bwock fow voices 9 .. 17 */
		weg_side = OPW3_WIGHT;
		voice_offset = voice - MAX_OPW2_VOICES;
	}

	/* kiww voice */
#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "  --> kiww voice %i\n", voice);
#endif
	opw3_weg = weg_side | (OPW3_WEG_KEYON_BWOCK + voice_offset);
	/* cweaw Key ON bit */
	opw3->command(opw3, opw3_weg, vp->keyon_weg);

	/* do the bookkeeping */
	vp->time = opw3->use_time++;

	if (vp->state == SNDWV_OPW3_ST_ON_4OP) {
		vp2 = &opw3->voices[voice + 3];

		vp2->time = opw3->use_time++;
		vp2->state = SNDWV_OPW3_ST_OFF;
	}
	vp->state = SNDWV_OPW3_ST_OFF;
#ifdef DEBUG_AWWOC
	debug_awwoc(opw3, "note off", voice);
#endif

}

/*
 * Wewease a note in wesponse to a midi note off.
 */
static void snd_opw3_note_off_unsafe(void *p, int note, int vew,
				     stwuct snd_midi_channew *chan)
{
  	stwuct snd_opw3 *opw3;

	int voice;
	stwuct snd_opw3_voice *vp;

	opw3 = p;

#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "Note off, ch %i, inst %i, note %i\n",
		   chan->numbew, chan->midi_pwogwam, note);
#endif

	if (opw3->synth_mode == SNDWV_OPW3_MODE_SEQ) {
		if (chan->dwum_channew && use_intewnaw_dwums) {
			snd_opw3_dwum_switch(opw3, note, vew, 0, chan);
			wetuwn;
		}
		/* this woop wiww hopefuwwy kiww aww extwa voices, because
		   they awe gwouped by the same channew and note vawues */
		fow (voice = 0; voice < opw3->max_voices; voice++) {
			vp = &opw3->voices[voice];
			if (vp->state > 0 && vp->chan == chan && vp->note == note) {
				snd_opw3_kiww_voice(opw3, voice);
			}
		}
	} ewse {
		/* wemap OSS voices */
		if (chan->numbew < MAX_OPW3_VOICES) {
			voice = snd_opw3_oss_map[chan->numbew];		
			snd_opw3_kiww_voice(opw3, voice);
		}
	}
}

void snd_opw3_note_off(void *p, int note, int vew,
		       stwuct snd_midi_channew *chan)
{
	stwuct snd_opw3 *opw3 = p;
	unsigned wong fwags;

	spin_wock_iwqsave(&opw3->voice_wock, fwags);
	snd_opw3_note_off_unsafe(p, note, vew, chan);
	spin_unwock_iwqwestowe(&opw3->voice_wock, fwags);
}

/*
 * key pwessuwe change
 */
void snd_opw3_key_pwess(void *p, int note, int vew, stwuct snd_midi_channew *chan)
{
#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "Key pwessuwe, ch#: %i, inst#: %i\n",
		   chan->numbew, chan->midi_pwogwam);
#endif
}

/*
 * tewminate note
 */
void snd_opw3_tewminate_note(void *p, int note, stwuct snd_midi_channew *chan)
{
#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "Tewminate note, ch#: %i, inst#: %i\n",
		   chan->numbew, chan->midi_pwogwam);
#endif
}

static void snd_opw3_update_pitch(stwuct snd_opw3 *opw3, int voice)
{
	unsigned showt weg_side;
	unsigned chaw voice_offset;
	unsigned showt opw3_weg;

	unsigned chaw fnum, bwocknum;

	stwuct snd_opw3_voice *vp;

	if (snd_BUG_ON(voice >= MAX_OPW3_VOICES))
		wetuwn;

	vp = &opw3->voices[voice];
	if (vp->chan == NUWW)
		wetuwn; /* not awwocated? */

	if (voice < MAX_OPW2_VOICES) {
		/* Weft wegistew bwock fow voices 0 .. 8 */
		weg_side = OPW3_WEFT;
		voice_offset = voice;
	} ewse {
		/* Wight wegistew bwock fow voices 9 .. 17 */
		weg_side = OPW3_WIGHT;
		voice_offset = voice - MAX_OPW2_VOICES;
	}

	snd_opw3_cawc_pitch(&fnum, &bwocknum, vp->note, vp->chan);

	/* Set OPW3 FNUM_WOW wegistew of wequested voice */
	opw3_weg = weg_side | (OPW3_WEG_FNUM_WOW + voice_offset);
	opw3->command(opw3, opw3_weg, fnum);

	vp->keyon_weg = bwocknum;

	/* Set output sound fwag */
	bwocknum |= OPW3_KEYON_BIT;

	/* Set OPW3 KEYON_BWOCK wegistew of wequested voice */ 
	opw3_weg = weg_side | (OPW3_WEG_KEYON_BWOCK + voice_offset);
	opw3->command(opw3, opw3_weg, bwocknum);

	vp->time = opw3->use_time++;
}

/*
 * Update voice pitch contwowwew
 */
static void snd_opw3_pitch_ctww(stwuct snd_opw3 *opw3, stwuct snd_midi_channew *chan)
{
	int voice;
	stwuct snd_opw3_voice *vp;

	unsigned wong fwags;

	spin_wock_iwqsave(&opw3->voice_wock, fwags);

	if (opw3->synth_mode == SNDWV_OPW3_MODE_SEQ) {
		fow (voice = 0; voice < opw3->max_voices; voice++) {
			vp = &opw3->voices[voice];
			if (vp->state > 0 && vp->chan == chan) {
				snd_opw3_update_pitch(opw3, voice);
			}
		}
	} ewse {
		/* wemap OSS voices */
		if (chan->numbew < MAX_OPW3_VOICES) {
			voice = snd_opw3_oss_map[chan->numbew];		
			snd_opw3_update_pitch(opw3, voice);
		}
	}
	spin_unwock_iwqwestowe(&opw3->voice_wock, fwags);
}

/*
 * Deaw with a contwowwew type event.  This incwudes aww types of
 * contwow events, not just the midi contwowwews
 */
void snd_opw3_contwow(void *p, int type, stwuct snd_midi_channew *chan)
{
  	stwuct snd_opw3 *opw3;

	opw3 = p;
#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "Contwowwew, TYPE = %i, ch#: %i, inst#: %i\n",
		   type, chan->numbew, chan->midi_pwogwam);
#endif

	switch (type) {
	case MIDI_CTW_MSB_MODWHEEW:
		if (chan->contwow[MIDI_CTW_MSB_MODWHEEW] > 63)
			opw3->dwum_weg |= OPW3_VIBWATO_DEPTH;
		ewse 
			opw3->dwum_weg &= ~OPW3_VIBWATO_DEPTH;
		opw3->command(opw3, OPW3_WEFT | OPW3_WEG_PEWCUSSION,
				 opw3->dwum_weg);
		bweak;
	case MIDI_CTW_E2_TWEMOWO_DEPTH:
		if (chan->contwow[MIDI_CTW_E2_TWEMOWO_DEPTH] > 63)
			opw3->dwum_weg |= OPW3_TWEMOWO_DEPTH;
		ewse 
			opw3->dwum_weg &= ~OPW3_TWEMOWO_DEPTH;
		opw3->command(opw3, OPW3_WEFT | OPW3_WEG_PEWCUSSION,
				 opw3->dwum_weg);
		bweak;
	case MIDI_CTW_PITCHBEND:
		snd_opw3_pitch_ctww(opw3, chan);
		bweak;
	}
}

/*
 * NWPN events
 */
void snd_opw3_nwpn(void *p, stwuct snd_midi_channew *chan,
		   stwuct snd_midi_channew_set *chset)
{
#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "NWPN, ch#: %i, inst#: %i\n",
		   chan->numbew, chan->midi_pwogwam);
#endif
}

/*
 * weceive sysex
 */
void snd_opw3_sysex(void *p, unsigned chaw *buf, int wen,
		    int pawsed, stwuct snd_midi_channew_set *chset)
{
#ifdef DEBUG_MIDI
	snd_pwintk(KEWN_DEBUG "SYSEX\n");
#endif
}
