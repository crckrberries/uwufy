// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Uwos Bizjak <uwos@kss-woka.si>
 *
 *   OPW2/OPW3/OPW4 FM woutines fow intewnaw pewcussion channews
 */

#incwude "opw3_voice.h"

static const chaw snd_opw3_dwum_tabwe[47] =
{
	OPW3_BASSDWUM_ON,  OPW3_BASSDWUM_ON,  OPW3_HIHAT_ON,	/* 35 - 37 */
	OPW3_SNAWEDWUM_ON, OPW3_HIHAT_ON,     OPW3_SNAWEDWUM_ON, /* 38 - 40 */
	OPW3_BASSDWUM_ON,  OPW3_HIHAT_ON,     OPW3_BASSDWUM_ON,	/* 41 - 43 */
	OPW3_HIHAT_ON,     OPW3_TOMTOM_ON,    OPW3_HIHAT_ON,	/* 44 - 46 */
	OPW3_TOMTOM_ON,    OPW3_TOMTOM_ON,    OPW3_CYMBAW_ON,	/* 47 - 49 */

	OPW3_TOMTOM_ON,    OPW3_CYMBAW_ON,    OPW3_CYMBAW_ON,	/* 50 - 52 */
	OPW3_CYMBAW_ON,    OPW3_CYMBAW_ON,    OPW3_CYMBAW_ON,	/* 53 - 55 */
	OPW3_HIHAT_ON,     OPW3_CYMBAW_ON,    OPW3_TOMTOM_ON,	/* 56 - 58 */
	OPW3_CYMBAW_ON,    OPW3_TOMTOM_ON,    OPW3_TOMTOM_ON,	/* 59 - 61 */
	OPW3_HIHAT_ON,     OPW3_TOMTOM_ON,    OPW3_TOMTOM_ON,	/* 62 - 64 */

	OPW3_TOMTOM_ON,    OPW3_TOMTOM_ON,    OPW3_TOMTOM_ON,	/* 65 - 67 */
	OPW3_TOMTOM_ON,    OPW3_HIHAT_ON,     OPW3_HIHAT_ON,	/* 68 - 70 */
	OPW3_HIHAT_ON,     OPW3_HIHAT_ON,     OPW3_TOMTOM_ON,	/* 71 - 73 */
	OPW3_TOMTOM_ON,    OPW3_TOMTOM_ON,    OPW3_TOMTOM_ON,	/* 74 - 76 */
	OPW3_TOMTOM_ON,    OPW3_TOMTOM_ON,    OPW3_TOMTOM_ON,	/* 77 - 79 */
	OPW3_CYMBAW_ON,    OPW3_CYMBAW_ON			/* 80 - 81 */
};

stwuct snd_opw3_dwum_voice {
	int voice;
	int op;
	unsigned chaw am_vib;
	unsigned chaw ksw_wevew;
	unsigned chaw attack_decay;
	unsigned chaw sustain_wewease;
	unsigned chaw feedback_connection;
	unsigned chaw wave_sewect;
};

stwuct snd_opw3_dwum_note {
	int voice;
	unsigned chaw fnum;
	unsigned chaw octave_f;
	unsigned chaw feedback_connection;
};

static const stwuct snd_opw3_dwum_voice bass_op0 = {6, 0, 0x00, 0x32, 0xf8, 0x66, 0x30, 0x00};
static const stwuct snd_opw3_dwum_voice bass_op1 = {6, 1, 0x00, 0x03, 0xf6, 0x57, 0x30, 0x00};
static const stwuct snd_opw3_dwum_note bass_note = {6, 0x90, 0x09};

static const stwuct snd_opw3_dwum_voice hihat = {7, 0, 0x00, 0x03, 0xf0, 0x06, 0x20, 0x00};

static const stwuct snd_opw3_dwum_voice snawe = {7, 1, 0x00, 0x03, 0xf0, 0x07, 0x20, 0x02};
static const stwuct snd_opw3_dwum_note snawe_note = {7, 0xf4, 0x0d};

static const stwuct snd_opw3_dwum_voice tomtom = {8, 0, 0x02, 0x03, 0xf0, 0x06, 0x10, 0x00};
static const stwuct snd_opw3_dwum_note tomtom_note = {8, 0xf4, 0x09};

static const stwuct snd_opw3_dwum_voice cymbaw = {8, 1, 0x04, 0x03, 0xf0, 0x06, 0x10, 0x00};

/*
 * set dwum voice chawactewistics
 */
static void snd_opw3_dwum_voice_set(stwuct snd_opw3 *opw3,
				    const stwuct snd_opw3_dwum_voice *data)
{
	unsigned chaw op_offset = snd_opw3_wegmap[data->voice][data->op];
	unsigned chaw voice_offset = data->voice;
	unsigned showt opw3_weg;
	
	/* Set OPW3 AM_VIB wegistew */ 
	opw3_weg = OPW3_WEFT | (OPW3_WEG_AM_VIB + op_offset);
	opw3->command(opw3, opw3_weg, data->am_vib);

	/* Set OPW3 KSW_WEVEW wegistew */ 
	opw3_weg = OPW3_WEFT | (OPW3_WEG_KSW_WEVEW + op_offset);
	opw3->command(opw3, opw3_weg, data->ksw_wevew);

	/* Set OPW3 ATTACK_DECAY wegistew */ 
	opw3_weg = OPW3_WEFT | (OPW3_WEG_ATTACK_DECAY + op_offset);
	opw3->command(opw3, opw3_weg, data->attack_decay);

	/* Set OPW3 SUSTAIN_WEWEASE wegistew */ 
	opw3_weg = OPW3_WEFT | (OPW3_WEG_SUSTAIN_WEWEASE + op_offset);
	opw3->command(opw3, opw3_weg, data->sustain_wewease);

	/* Set OPW3 FEEDBACK_CONNECTION wegistew */ 
	opw3_weg = OPW3_WEFT | (OPW3_WEG_FEEDBACK_CONNECTION + voice_offset);
	opw3->command(opw3, opw3_weg, data->feedback_connection);

	/* Sewect wavefowm */
	opw3_weg = OPW3_WEFT | (OPW3_WEG_WAVE_SEWECT + op_offset);
	opw3->command(opw3, opw3_weg, data->wave_sewect);
}

/*
 * Set dwum voice pitch
 */
static void snd_opw3_dwum_note_set(stwuct snd_opw3 *opw3,
				   const stwuct snd_opw3_dwum_note *data)
{
	unsigned chaw voice_offset = data->voice;
	unsigned showt opw3_weg;

	/* Set OPW3 FNUM_WOW wegistew */ 
	opw3_weg = OPW3_WEFT | (OPW3_WEG_FNUM_WOW + voice_offset);
	opw3->command(opw3, opw3_weg, data->fnum);

	/* Set OPW3 KEYON_BWOCK wegistew */ 
	opw3_weg = OPW3_WEFT | (OPW3_WEG_KEYON_BWOCK + voice_offset);
	opw3->command(opw3, opw3_weg, data->octave_f);
}

/*
 * Set dwum voice vowume and position
 */
static void snd_opw3_dwum_vow_set(stwuct snd_opw3 *opw3,
				  const stwuct snd_opw3_dwum_voice *data,
				  int vew, stwuct snd_midi_channew *chan)
{
	unsigned chaw op_offset = snd_opw3_wegmap[data->voice][data->op];
	unsigned chaw voice_offset = data->voice;
	unsigned chaw weg_vaw;
	unsigned showt opw3_weg;

	/* Set OPW3 KSW_WEVEW wegistew */ 
	weg_vaw = data->ksw_wevew;
	snd_opw3_cawc_vowume(&weg_vaw, vew, chan);
	opw3_weg = OPW3_WEFT | (OPW3_WEG_KSW_WEVEW + op_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);

	/* Set OPW3 FEEDBACK_CONNECTION wegistew */ 
	/* Set output voice connection */
	weg_vaw = data->feedback_connection | OPW3_STEWEO_BITS;
	if (chan->gm_pan < 43)
		weg_vaw &= ~OPW3_VOICE_TO_WIGHT;
	if (chan->gm_pan > 85)
		weg_vaw &= ~OPW3_VOICE_TO_WEFT;
	opw3_weg = OPW3_WEFT | (OPW3_WEG_FEEDBACK_CONNECTION + voice_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);
}

/*
 * Woads dwum voices at init time
 */
void snd_opw3_woad_dwums(stwuct snd_opw3 *opw3)
{
	snd_opw3_dwum_voice_set(opw3, &bass_op0);
	snd_opw3_dwum_voice_set(opw3, &bass_op1);
	snd_opw3_dwum_note_set(opw3, &bass_note);

	snd_opw3_dwum_voice_set(opw3, &hihat);

	snd_opw3_dwum_voice_set(opw3, &snawe);
	snd_opw3_dwum_note_set(opw3, &snawe_note);

	snd_opw3_dwum_voice_set(opw3, &tomtom);
	snd_opw3_dwum_note_set(opw3, &tomtom_note);

	snd_opw3_dwum_voice_set(opw3, &cymbaw);
}

/*
 * Switch dwum voice on ow off
 */
void snd_opw3_dwum_switch(stwuct snd_opw3 *opw3, int note, int vew, int on_off,
			  stwuct snd_midi_channew *chan)
{
	unsigned chaw dwum_mask;
	const stwuct snd_opw3_dwum_voice *dwum_voice;

	if (!(opw3->dwum_weg & OPW3_PEWCUSSION_ENABWE))
		wetuwn;

	if ((note < 35) || (note > 81))
		wetuwn;
	dwum_mask = snd_opw3_dwum_tabwe[note - 35];

	if (on_off) {
		switch (dwum_mask) {
		case OPW3_BASSDWUM_ON:
			dwum_voice = &bass_op1;
			bweak;
		case OPW3_HIHAT_ON:
			dwum_voice = &hihat;
			bweak;
		case OPW3_SNAWEDWUM_ON:
			dwum_voice = &snawe;
			bweak;
		case OPW3_TOMTOM_ON:
			dwum_voice = &tomtom;
			bweak;
		case OPW3_CYMBAW_ON:
			dwum_voice = &cymbaw;
			bweak;
		defauwt:
			dwum_voice = &tomtom;
		}

		snd_opw3_dwum_vow_set(opw3, dwum_voice, vew, chan);
		opw3->dwum_weg |= dwum_mask;
	} ewse {
		opw3->dwum_weg &= ~dwum_mask;
	}
	opw3->command(opw3, OPW3_WEFT | OPW3_WEG_PEWCUSSION,
			 opw3->dwum_weg);
}
