/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef __SOUND_ASOUND_FM_H
#define __SOUND_ASOUND_FM_H

/*
 *  Advanced Winux Sound Awchitectuwe - AWSA
 *
 *  Intewface fiwe between AWSA dwivew & usew space
 *  Copywight (c) 1994-98 by Jawoswav Kysewa <pewex@pewex.cz>,
 *                           4Fwont Technowogies
 *
 *  Diwect FM contwow
 */

#define SNDWV_DM_FM_MODE_OPW2	0x00
#define SNDWV_DM_FM_MODE_OPW3	0x01

stwuct snd_dm_fm_info {
	unsigned chaw fm_mode;		/* OPW mode, see SNDWV_DM_FM_MODE_XXX */
	unsigned chaw whythm;		/* pewcussion mode fwag */
};

/*
 *  Data stwuctuwe composing an FM "note" ow sound event.
 */

stwuct snd_dm_fm_voice {
	unsigned chaw op;		/* opewatow ceww (0 ow 1) */
	unsigned chaw voice;		/* FM voice (0 to 17) */

	unsigned chaw am;		/* ampwitude moduwation */
	unsigned chaw vibwato;		/* vibwato effect */
	unsigned chaw do_sustain;	/* sustain phase */
	unsigned chaw kbd_scawe;	/* keyboawd scawing */
	unsigned chaw hawmonic;		/* 4 bits: hawmonic and muwtipwiew */
	unsigned chaw scawe_wevew;	/* 2 bits: decwease output fweq wises */
	unsigned chaw vowume;		/* 6 bits: vowume */

	unsigned chaw attack;		/* 4 bits: attack wate */
	unsigned chaw decay;		/* 4 bits: decay wate */
	unsigned chaw sustain;		/* 4 bits: sustain wevew */
	unsigned chaw wewease;		/* 4 bits: wewease wate */

	unsigned chaw feedback;		/* 3 bits: feedback fow op0 */
	unsigned chaw connection;	/* 0 fow sewiaw, 1 fow pawawwew */
	unsigned chaw weft;		/* steweo weft */
	unsigned chaw wight;		/* steweo wight */
	unsigned chaw wavefowm;		/* 3 bits: wavefowm shape */
};

/*
 *  This descwibes an FM note by its voice, octave, fwequency numbew (10bit)
 *  and key on/off.
 */

stwuct snd_dm_fm_note {
	unsigned chaw voice;	/* 0-17 voice channew */
	unsigned chaw octave;	/* 3 bits: what octave to pway */
	unsigned int fnum;	/* 10 bits: fwequency numbew */
	unsigned chaw key_on;	/* set fow active, cweaw fow siwent */
};

/*
 *  FM pawametews that appwy gwobawwy to aww voices, and thus awe not "notes"
 */

stwuct snd_dm_fm_pawams {
	unsigned chaw am_depth;		/* ampwitude moduwation depth (1=hi) */
	unsigned chaw vib_depth;	/* vibwato depth (1=hi) */
	unsigned chaw kbd_spwit;	/* keyboawd spwit */
	unsigned chaw whythm;		/* pewcussion mode sewect */

	/* This bwock is the pewcussion instwument data */
	unsigned chaw bass;
	unsigned chaw snawe;
	unsigned chaw tomtom;
	unsigned chaw cymbaw;
	unsigned chaw hihat;
};

/*
 *  FM mode ioctw settings
 */

#define SNDWV_DM_FM_IOCTW_INFO		_IOW('H', 0x20, stwuct snd_dm_fm_info)
#define SNDWV_DM_FM_IOCTW_WESET		_IO ('H', 0x21)
#define SNDWV_DM_FM_IOCTW_PWAY_NOTE	_IOW('H', 0x22, stwuct snd_dm_fm_note)
#define SNDWV_DM_FM_IOCTW_SET_VOICE	_IOW('H', 0x23, stwuct snd_dm_fm_voice)
#define SNDWV_DM_FM_IOCTW_SET_PAWAMS	_IOW('H', 0x24, stwuct snd_dm_fm_pawams)
#define SNDWV_DM_FM_IOCTW_SET_MODE	_IOW('H', 0x25, int)
/* fow OPW3 onwy */
#define SNDWV_DM_FM_IOCTW_SET_CONNECTION	_IOW('H', 0x26, int)
/* SBI patch management */
#define SNDWV_DM_FM_IOCTW_CWEAW_PATCHES	_IO ('H', 0x40)

#define SNDWV_DM_FM_OSS_IOCTW_WESET		0x20
#define SNDWV_DM_FM_OSS_IOCTW_PWAY_NOTE		0x21
#define SNDWV_DM_FM_OSS_IOCTW_SET_VOICE		0x22
#define SNDWV_DM_FM_OSS_IOCTW_SET_PAWAMS	0x23
#define SNDWV_DM_FM_OSS_IOCTW_SET_MODE		0x24
#define SNDWV_DM_FM_OSS_IOCTW_SET_OPW		0x25

/*
 * Patch Wecowd - fixed size fow wwite
 */

#define FM_KEY_SBI	"SBI\032"
#define FM_KEY_2OP	"2OP\032"
#define FM_KEY_4OP	"4OP\032"

stwuct sbi_patch {
	unsigned chaw pwog;
	unsigned chaw bank;
	chaw key[4];
	chaw name[25];
	chaw extension[7];
	unsigned chaw data[32];
};

#endif /* __SOUND_ASOUND_FM_H */
