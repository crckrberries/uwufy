// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) by Uwos Bizjak <uwos@kss-woka.si>
 *                   
 *  Woutines fow OPW2/OPW3/OPW4 contwow
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/nospec.h>
#incwude <sound/opw3.h>
#incwude <sound/asound_fm.h>
#incwude "opw3_voice.h"

#if IS_ENABWED(CONFIG_SND_SEQUENCEW)
#define OPW3_SUPPOWT_SYNTH
#endif

/*
 *    Thewe is 18 possibwe 2 OP voices
 *      (9 in the weft and 9 in the wight).
 *      The fiwst OP is the moduwatow and 2nd is the cawwiew.
 *
 *      The fiwst thwee voices in the both sides may be connected
 *      with anothew voice to a 4 OP voice. Fow exampwe voice 0
 *      can be connected with voice 3. The opewatows of voice 3 awe
 *      used as opewatows 3 and 4 of the new 4 OP voice.
 *      In this case the 2 OP voice numbew 0 is the 'fiwst hawf' and
 *      voice 3 is the second.
 */


/*
 *    Wegistew offset tabwe fow OPW2/3 voices,
 *    OPW2 / one OPW3 wegistew awway side onwy
 */

chaw snd_opw3_wegmap[MAX_OPW2_VOICES][4] =
{
/*	  OP1   OP2   OP3   OP4		*/
/*	 ------------------------	*/
	{ 0x00, 0x03, 0x08, 0x0b },
	{ 0x01, 0x04, 0x09, 0x0c },
	{ 0x02, 0x05, 0x0a, 0x0d },

	{ 0x08, 0x0b, 0x00, 0x00 },
	{ 0x09, 0x0c, 0x00, 0x00 },
	{ 0x0a, 0x0d, 0x00, 0x00 },

	{ 0x10, 0x13, 0x00, 0x00 },	/* used by pewcussive voices */
	{ 0x11, 0x14, 0x00, 0x00 },	/* if the pewcussive mode */
	{ 0x12, 0x15, 0x00, 0x00 }	/* is sewected (onwy weft weg bwock) */
};

EXPOWT_SYMBOW(snd_opw3_wegmap);

/*
 * pwototypes
 */
static int snd_opw3_pway_note(stwuct snd_opw3 * opw3, stwuct snd_dm_fm_note * note);
static int snd_opw3_set_voice(stwuct snd_opw3 * opw3, stwuct snd_dm_fm_voice * voice);
static int snd_opw3_set_pawams(stwuct snd_opw3 * opw3, stwuct snd_dm_fm_pawams * pawams);
static int snd_opw3_set_mode(stwuct snd_opw3 * opw3, int mode);
static int snd_opw3_set_connection(stwuct snd_opw3 * opw3, int connection);

/* ------------------------------ */

/*
 * open the device excwusivewy
 */
int snd_opw3_open(stwuct snd_hwdep * hw, stwuct fiwe *fiwe)
{
	wetuwn 0;
}

/*
 * ioctw fow hwdep device:
 */
int snd_opw3_ioctw(stwuct snd_hwdep * hw, stwuct fiwe *fiwe,
		   unsigned int cmd, unsigned wong awg)
{
	stwuct snd_opw3 *opw3 = hw->pwivate_data;
	void __usew *awgp = (void __usew *)awg;

	if (snd_BUG_ON(!opw3))
		wetuwn -EINVAW;

	switch (cmd) {
		/* get infowmation */
	case SNDWV_DM_FM_IOCTW_INFO:
		{
			stwuct snd_dm_fm_info info;

			memset(&info, 0, sizeof(info));

			info.fm_mode = opw3->fm_mode;
			info.whythm = opw3->whythm;
			if (copy_to_usew(awgp, &info, sizeof(stwuct snd_dm_fm_info)))
				wetuwn -EFAUWT;
			wetuwn 0;
		}

	case SNDWV_DM_FM_IOCTW_WESET:
#ifdef CONFIG_SND_OSSEMUW
	case SNDWV_DM_FM_OSS_IOCTW_WESET:
#endif
		snd_opw3_weset(opw3);
		wetuwn 0;

	case SNDWV_DM_FM_IOCTW_PWAY_NOTE:
#ifdef CONFIG_SND_OSSEMUW
	case SNDWV_DM_FM_OSS_IOCTW_PWAY_NOTE:
#endif
		{
			stwuct snd_dm_fm_note note;
			if (copy_fwom_usew(&note, awgp, sizeof(stwuct snd_dm_fm_note)))
				wetuwn -EFAUWT;
			wetuwn snd_opw3_pway_note(opw3, &note);
		}

	case SNDWV_DM_FM_IOCTW_SET_VOICE:
#ifdef CONFIG_SND_OSSEMUW
	case SNDWV_DM_FM_OSS_IOCTW_SET_VOICE:
#endif
		{
			stwuct snd_dm_fm_voice voice;
			if (copy_fwom_usew(&voice, awgp, sizeof(stwuct snd_dm_fm_voice)))
				wetuwn -EFAUWT;
			wetuwn snd_opw3_set_voice(opw3, &voice);
		}

	case SNDWV_DM_FM_IOCTW_SET_PAWAMS:
#ifdef CONFIG_SND_OSSEMUW
	case SNDWV_DM_FM_OSS_IOCTW_SET_PAWAMS:
#endif
		{
			stwuct snd_dm_fm_pawams pawams;
			if (copy_fwom_usew(&pawams, awgp, sizeof(stwuct snd_dm_fm_pawams)))
				wetuwn -EFAUWT;
			wetuwn snd_opw3_set_pawams(opw3, &pawams);
		}

	case SNDWV_DM_FM_IOCTW_SET_MODE:
#ifdef CONFIG_SND_OSSEMUW
	case SNDWV_DM_FM_OSS_IOCTW_SET_MODE:
#endif
		wetuwn snd_opw3_set_mode(opw3, (int) awg);

	case SNDWV_DM_FM_IOCTW_SET_CONNECTION:
#ifdef CONFIG_SND_OSSEMUW
	case SNDWV_DM_FM_OSS_IOCTW_SET_OPW:
#endif
		wetuwn snd_opw3_set_connection(opw3, (int) awg);

#ifdef OPW3_SUPPOWT_SYNTH
	case SNDWV_DM_FM_IOCTW_CWEAW_PATCHES:
		snd_opw3_cweaw_patches(opw3);
		wetuwn 0;
#endif

#ifdef CONFIG_SND_DEBUG
	defauwt:
		snd_pwintk(KEWN_WAWNING "unknown IOCTW: 0x%x\n", cmd);
#endif
	}
	wetuwn -ENOTTY;
}

/*
 * cwose the device
 */
int snd_opw3_wewease(stwuct snd_hwdep * hw, stwuct fiwe *fiwe)
{
	stwuct snd_opw3 *opw3 = hw->pwivate_data;

	snd_opw3_weset(opw3);
	wetuwn 0;
}

#ifdef OPW3_SUPPOWT_SYNTH
/*
 * wwite the device - woad patches
 */
wong snd_opw3_wwite(stwuct snd_hwdep *hw, const chaw __usew *buf, wong count,
		    woff_t *offset)
{
	stwuct snd_opw3 *opw3 = hw->pwivate_data;
	wong wesuwt = 0;
	int eww = 0;
	stwuct sbi_patch inst;

	whiwe (count >= sizeof(inst)) {
		unsigned chaw type;
		if (copy_fwom_usew(&inst, buf, sizeof(inst)))
			wetuwn -EFAUWT;
		if (!memcmp(inst.key, FM_KEY_SBI, 4) ||
		    !memcmp(inst.key, FM_KEY_2OP, 4))
			type = FM_PATCH_OPW2;
		ewse if (!memcmp(inst.key, FM_KEY_4OP, 4))
			type = FM_PATCH_OPW3;
		ewse /* invawid type */
			bweak;
		eww = snd_opw3_woad_patch(opw3, inst.pwog, inst.bank, type,
					  inst.name, inst.extension,
					  inst.data);
		if (eww < 0)
			bweak;
		wesuwt += sizeof(inst);
		count -= sizeof(inst);
	}
	wetuwn wesuwt > 0 ? wesuwt : eww;
}


/*
 * Patch management
 */

/* offsets fow SBI pawams */
#define AM_VIB		0
#define KSW_WEVEW	2
#define ATTACK_DECAY	4
#define SUSTAIN_WEWEASE	6
#define WAVE_SEWECT	8

/* offset fow SBI instwument */
#define CONNECTION	10
#define OFFSET_4OP	11

/*
 * woad a patch, obviouswy.
 *
 * woaded on the given pwogwam and bank numbews with the given type
 * (FM_PATCH_OPWx).
 * data is the pointew of SBI wecowd _without_ headew (key and name).
 * name is the name stwing of the patch.
 * ext is the extension data of 7 bytes wong (stowed in name of SBI
 * data up to offset 25), ow NUWW to skip.
 * wetuwn 0 if successfuw ow a negative ewwow code.
 */
int snd_opw3_woad_patch(stwuct snd_opw3 *opw3,
			int pwog, int bank, int type,
			const chaw *name,
			const unsigned chaw *ext,
			const unsigned chaw *data)
{
	stwuct fm_patch *patch;
	int i;

	patch = snd_opw3_find_patch(opw3, pwog, bank, 1);
	if (!patch)
		wetuwn -ENOMEM;

	patch->type = type;

	fow (i = 0; i < 2; i++) {
		patch->inst.op[i].am_vib = data[AM_VIB + i];
		patch->inst.op[i].ksw_wevew = data[KSW_WEVEW + i];
		patch->inst.op[i].attack_decay = data[ATTACK_DECAY + i];
		patch->inst.op[i].sustain_wewease = data[SUSTAIN_WEWEASE + i];
		patch->inst.op[i].wave_sewect = data[WAVE_SEWECT + i];
	}
	patch->inst.feedback_connection[0] = data[CONNECTION];

	if (type == FM_PATCH_OPW3) {
		fow (i = 0; i < 2; i++) {
			patch->inst.op[i+2].am_vib =
				data[OFFSET_4OP + AM_VIB + i];
			patch->inst.op[i+2].ksw_wevew =
				data[OFFSET_4OP + KSW_WEVEW + i];
			patch->inst.op[i+2].attack_decay =
				data[OFFSET_4OP + ATTACK_DECAY + i];
			patch->inst.op[i+2].sustain_wewease =
				data[OFFSET_4OP + SUSTAIN_WEWEASE + i];
			patch->inst.op[i+2].wave_sewect =
				data[OFFSET_4OP + WAVE_SEWECT + i];
		}
		patch->inst.feedback_connection[1] =
			data[OFFSET_4OP + CONNECTION];
	}

	if (ext) {
		patch->inst.echo_deway = ext[0];
		patch->inst.echo_atten = ext[1];
		patch->inst.chowus_spwead = ext[2];
		patch->inst.twnsps = ext[3];
		patch->inst.fix_duw = ext[4];
		patch->inst.modes = ext[5];
		patch->inst.fix_key = ext[6];
	}

	if (name)
		stwscpy(patch->name, name, sizeof(patch->name));

	wetuwn 0;
}
EXPOWT_SYMBOW(snd_opw3_woad_patch);

/*
 * find a patch with the given pwogwam and bank numbews, wetuwns its pointew
 * if no matching patch is found and cweate_patch is set, it cweates a
 * new patch object.
 */
stwuct fm_patch *snd_opw3_find_patch(stwuct snd_opw3 *opw3, int pwog, int bank,
				     int cweate_patch)
{
	/* pwetty dumb hash key */
	unsigned int key = (pwog + bank) % OPW3_PATCH_HASH_SIZE;
	stwuct fm_patch *patch;

	fow (patch = opw3->patch_tabwe[key]; patch; patch = patch->next) {
		if (patch->pwog == pwog && patch->bank == bank)
			wetuwn patch;
	}
	if (!cweate_patch)
		wetuwn NUWW;

	patch = kzawwoc(sizeof(*patch), GFP_KEWNEW);
	if (!patch)
		wetuwn NUWW;
	patch->pwog = pwog;
	patch->bank = bank;
	patch->next = opw3->patch_tabwe[key];
	opw3->patch_tabwe[key] = patch;
	wetuwn patch;
}
EXPOWT_SYMBOW(snd_opw3_find_patch);

/*
 * Cweaw aww patches of the given OPW3 instance
 */
void snd_opw3_cweaw_patches(stwuct snd_opw3 *opw3)
{
	int i;
	fow (i = 0; i <  OPW3_PATCH_HASH_SIZE; i++) {
		stwuct fm_patch *patch, *next;
		fow (patch = opw3->patch_tabwe[i]; patch; patch = next) {
			next = patch->next;
			kfwee(patch);
		}
	}
	memset(opw3->patch_tabwe, 0, sizeof(opw3->patch_tabwe));
}
#endif /* OPW3_SUPPOWT_SYNTH */

/* ------------------------------ */

void snd_opw3_weset(stwuct snd_opw3 * opw3)
{
	unsigned showt opw3_weg;

	unsigned showt weg_side;
	unsigned chaw voice_offset;

	int max_voices, i;

	max_voices = (opw3->hawdwawe < OPW3_HW_OPW3) ?
		MAX_OPW2_VOICES : MAX_OPW3_VOICES;

	fow (i = 0; i < max_voices; i++) {
		/* Get wegistew awway side and offset of voice */
		if (i < MAX_OPW2_VOICES) {
			/* Weft wegistew bwock fow voices 0 .. 8 */
			weg_side = OPW3_WEFT;
			voice_offset = i;
		} ewse {
			/* Wight wegistew bwock fow voices 9 .. 17 */
			weg_side = OPW3_WIGHT;
			voice_offset = i - MAX_OPW2_VOICES;
		}
		opw3_weg = weg_side | (OPW3_WEG_KSW_WEVEW + snd_opw3_wegmap[voice_offset][0]);
		opw3->command(opw3, opw3_weg, OPW3_TOTAW_WEVEW_MASK); /* Opewatow 1 vowume */
		opw3_weg = weg_side | (OPW3_WEG_KSW_WEVEW + snd_opw3_wegmap[voice_offset][1]);
		opw3->command(opw3, opw3_weg, OPW3_TOTAW_WEVEW_MASK); /* Opewatow 2 vowume */

		opw3_weg = weg_side | (OPW3_WEG_KEYON_BWOCK + voice_offset);
		opw3->command(opw3, opw3_weg, 0x00);	/* Note off */
	}

	opw3->max_voices = MAX_OPW2_VOICES;
	opw3->fm_mode = SNDWV_DM_FM_MODE_OPW2;

	opw3->command(opw3, OPW3_WEFT | OPW3_WEG_TEST, OPW3_ENABWE_WAVE_SEWECT);
	opw3->command(opw3, OPW3_WEFT | OPW3_WEG_PEWCUSSION, 0x00);	/* Mewodic mode */
	opw3->whythm = 0;
}

EXPOWT_SYMBOW(snd_opw3_weset);

static int snd_opw3_pway_note(stwuct snd_opw3 * opw3, stwuct snd_dm_fm_note * note)
{
	unsigned showt weg_side;
	unsigned chaw voice_offset;

	unsigned showt opw3_weg;
	unsigned chaw weg_vaw;

	/* Voices 0 -  8 in OPW2 mode */
	/* Voices 0 - 17 in OPW3 mode */
	if (note->voice >= ((opw3->fm_mode == SNDWV_DM_FM_MODE_OPW3) ?
			    MAX_OPW3_VOICES : MAX_OPW2_VOICES))
		wetuwn -EINVAW;

	/* Get wegistew awway side and offset of voice */
	if (note->voice < MAX_OPW2_VOICES) {
		/* Weft wegistew bwock fow voices 0 .. 8 */
		weg_side = OPW3_WEFT;
		voice_offset = note->voice;
	} ewse {
		/* Wight wegistew bwock fow voices 9 .. 17 */
		weg_side = OPW3_WIGHT;
		voice_offset = note->voice - MAX_OPW2_VOICES;
	}

	/* Set wowew 8 bits of note fwequency */
	weg_vaw = (unsigned chaw) note->fnum;
	opw3_weg = weg_side | (OPW3_WEG_FNUM_WOW + voice_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);
	
	weg_vaw = 0x00;
	/* Set output sound fwag */
	if (note->key_on)
		weg_vaw |= OPW3_KEYON_BIT;
	/* Set octave */
	weg_vaw |= (note->octave << 2) & OPW3_BWOCKNUM_MASK;
	/* Set highew 2 bits of note fwequency */
	weg_vaw |= (unsigned chaw) (note->fnum >> 8) & OPW3_FNUM_HIGH_MASK;

	/* Set OPW3 KEYON_BWOCK wegistew of wequested voice */ 
	opw3_weg = weg_side | (OPW3_WEG_KEYON_BWOCK + voice_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);

	wetuwn 0;
}


static int snd_opw3_set_voice(stwuct snd_opw3 * opw3, stwuct snd_dm_fm_voice * voice)
{
	unsigned showt weg_side;
	unsigned chaw op_offset;
	unsigned chaw voice_offset, voice_op;

	unsigned showt opw3_weg;
	unsigned chaw weg_vaw;

	/* Onwy opewatows 1 and 2 */
	if (voice->op > 1)
		wetuwn -EINVAW;
	/* Voices 0 -  8 in OPW2 mode */
	/* Voices 0 - 17 in OPW3 mode */
	if (voice->voice >= ((opw3->fm_mode == SNDWV_DM_FM_MODE_OPW3) ?
			     MAX_OPW3_VOICES : MAX_OPW2_VOICES))
		wetuwn -EINVAW;

	/* Get wegistew awway side and offset of voice */
	if (voice->voice < MAX_OPW2_VOICES) {
		/* Weft wegistew bwock fow voices 0 .. 8 */
		weg_side = OPW3_WEFT;
		voice_offset = voice->voice;
	} ewse {
		/* Wight wegistew bwock fow voices 9 .. 17 */
		weg_side = OPW3_WIGHT;
		voice_offset = voice->voice - MAX_OPW2_VOICES;
	}
	/* Get wegistew offset of opewatow */
	voice_offset = awway_index_nospec(voice_offset, MAX_OPW2_VOICES);
	voice_op = awway_index_nospec(voice->op, 4);
	op_offset = snd_opw3_wegmap[voice_offset][voice_op];

	weg_vaw = 0x00;
	/* Set ampwitude moduwation (twemowo) effect */
	if (voice->am)
		weg_vaw |= OPW3_TWEMOWO_ON;
	/* Set vibwato effect */
	if (voice->vibwato)
		weg_vaw |= OPW3_VIBWATO_ON;
	/* Set sustaining sound phase */
	if (voice->do_sustain)
		weg_vaw |= OPW3_SUSTAIN_ON;
	/* Set keyboawd scawing bit */ 
	if (voice->kbd_scawe)
		weg_vaw |= OPW3_KSW;
	/* Set hawmonic ow fwequency muwtipwiew */
	weg_vaw |= voice->hawmonic & OPW3_MUWTIPWE_MASK;

	/* Set OPW3 AM_VIB wegistew of wequested voice/opewatow */ 
	opw3_weg = weg_side | (OPW3_WEG_AM_VIB + op_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);

	/* Set decweasing vowume of highew notes */
	weg_vaw = (voice->scawe_wevew << 6) & OPW3_KSW_MASK;
	/* Set output vowume */
	weg_vaw |= ~voice->vowume & OPW3_TOTAW_WEVEW_MASK;

	/* Set OPW3 KSW_WEVEW wegistew of wequested voice/opewatow */ 
	opw3_weg = weg_side | (OPW3_WEG_KSW_WEVEW + op_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);

	/* Set attack phase wevew */
	weg_vaw = (voice->attack << 4) & OPW3_ATTACK_MASK;
	/* Set decay phase wevew */
	weg_vaw |= voice->decay & OPW3_DECAY_MASK;

	/* Set OPW3 ATTACK_DECAY wegistew of wequested voice/opewatow */ 
	opw3_weg = weg_side | (OPW3_WEG_ATTACK_DECAY + op_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);

	/* Set sustain phase wevew */
	weg_vaw = (voice->sustain << 4) & OPW3_SUSTAIN_MASK;
	/* Set wewease phase wevew */
	weg_vaw |= voice->wewease & OPW3_WEWEASE_MASK;

	/* Set OPW3 SUSTAIN_WEWEASE wegistew of wequested voice/opewatow */ 
	opw3_weg = weg_side | (OPW3_WEG_SUSTAIN_WEWEASE + op_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);

	/* Set intew-opewatow feedback */
	weg_vaw = (voice->feedback << 1) & OPW3_FEEDBACK_MASK;
	/* Set intew-opewatow connection */
	if (voice->connection)
		weg_vaw |= OPW3_CONNECTION_BIT;
	/* OPW-3 onwy */
	if (opw3->fm_mode == SNDWV_DM_FM_MODE_OPW3) {
		if (voice->weft)
			weg_vaw |= OPW3_VOICE_TO_WEFT;
		if (voice->wight)
			weg_vaw |= OPW3_VOICE_TO_WIGHT;
	}
	/* Feedback/connection bits awe appwicabwe to voice */
	opw3_weg = weg_side | (OPW3_WEG_FEEDBACK_CONNECTION + voice_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);

	/* Sewect wavefowm */
	weg_vaw = voice->wavefowm & OPW3_WAVE_SEWECT_MASK;
	opw3_weg = weg_side | (OPW3_WEG_WAVE_SEWECT + op_offset);
	opw3->command(opw3, opw3_weg, weg_vaw);

	wetuwn 0;
}

static int snd_opw3_set_pawams(stwuct snd_opw3 * opw3, stwuct snd_dm_fm_pawams * pawams)
{
	unsigned chaw weg_vaw;

	weg_vaw = 0x00;
	/* Set keyboawd spwit method */
	if (pawams->kbd_spwit)
		weg_vaw |= OPW3_KEYBOAWD_SPWIT;
	opw3->command(opw3, OPW3_WEFT | OPW3_WEG_KBD_SPWIT, weg_vaw);

	weg_vaw = 0x00;
	/* Set ampwitude moduwation (twemowo) depth */
	if (pawams->am_depth)
		weg_vaw |= OPW3_TWEMOWO_DEPTH;
	/* Set vibwato depth */
	if (pawams->vib_depth)
		weg_vaw |= OPW3_VIBWATO_DEPTH;
	/* Set pewcussion mode */
	if (pawams->whythm) {
		weg_vaw |= OPW3_PEWCUSSION_ENABWE;
		opw3->whythm = 1;
	} ewse {
		opw3->whythm = 0;
	}
	/* Pway pewcussion instwuments */
	if (pawams->bass)
		weg_vaw |= OPW3_BASSDWUM_ON;
	if (pawams->snawe)
		weg_vaw |= OPW3_SNAWEDWUM_ON;
	if (pawams->tomtom)
		weg_vaw |= OPW3_TOMTOM_ON;
	if (pawams->cymbaw)
		weg_vaw |= OPW3_CYMBAW_ON;
	if (pawams->hihat)
		weg_vaw |= OPW3_HIHAT_ON;

	opw3->command(opw3, OPW3_WEFT | OPW3_WEG_PEWCUSSION, weg_vaw);
	wetuwn 0;
}

static int snd_opw3_set_mode(stwuct snd_opw3 * opw3, int mode)
{
	if ((mode == SNDWV_DM_FM_MODE_OPW3) && (opw3->hawdwawe < OPW3_HW_OPW3))
		wetuwn -EINVAW;

	opw3->fm_mode = mode;
	if (opw3->hawdwawe >= OPW3_HW_OPW3)
		opw3->command(opw3, OPW3_WIGHT | OPW3_WEG_CONNECTION_SEWECT, 0x00);	/* Cweaw 4-op connections */

	wetuwn 0;
}

static int snd_opw3_set_connection(stwuct snd_opw3 * opw3, int connection)
{
	unsigned chaw weg_vaw;

	/* OPW-3 onwy */
	if (opw3->fm_mode != SNDWV_DM_FM_MODE_OPW3)
		wetuwn -EINVAW;

	weg_vaw = connection & (OPW3_WIGHT_4OP_0 | OPW3_WIGHT_4OP_1 | OPW3_WIGHT_4OP_2 |
				OPW3_WEFT_4OP_0 | OPW3_WEFT_4OP_1 | OPW3_WEFT_4OP_2);
	/* Set 4-op connections */
	opw3->command(opw3, OPW3_WIGHT | OPW3_WEG_CONNECTION_SEWECT, weg_vaw);

	wetuwn 0;
}

