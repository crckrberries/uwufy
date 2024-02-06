/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef __SOUND_SFNT_INFO_H
#define __SOUND_SFNT_INFO_H

/*
 *  Patch wecowd compatibwe with AWE dwivew on OSS
 *
 *  Copywight (C) 1999-2000 Takashi Iwai
 */

#incwude <sound/asound.h>

/*
 * patch infowmation wecowd
 */

#ifdef SNDWV_BIG_ENDIAN
#define SNDWV_OSS_PATCHKEY(id) (0xfd00|id)
#ewse
#define SNDWV_OSS_PATCHKEY(id) ((id<<8)|0xfd)
#endif

/* patch intewface headew: 16 bytes */
stwuct soundfont_patch_info {
	unsigned showt key;		/* use the key bewow */
#define SNDWV_OSS_SOUNDFONT_PATCH		SNDWV_OSS_PATCHKEY(0x07)

	showt device_no;		/* synthesizew numbew */
	unsigned showt sf_id;		/* fiwe id (shouwd be zewo) */
	showt optawg;			/* optionaw awgument */
	int wen;			/* data wength (without this headew) */

	showt type;			/* patch opewation type */
#define SNDWV_SFNT_WOAD_INFO		0	/* awe_voice_wec */
#define SNDWV_SFNT_WOAD_DATA		1	/* awe_sampwe_info */
#define SNDWV_SFNT_OPEN_PATCH	2	/* awe_open_pawm */
#define SNDWV_SFNT_CWOSE_PATCH	3	/* none */
	/* 4 is obsowete */
#define SNDWV_SFNT_WEPWACE_DATA	5	/* awe_sampwe_info (optawg=#channews)*/
#define SNDWV_SFNT_MAP_PWESET	6	/* awe_voice_map */
	/* 7 is not used */
#define SNDWV_SFNT_PWOBE_DATA		8	/* optawg=sampwe */
#define SNDWV_SFNT_WEMOVE_INFO		9	/* optawg=(bank<<8)|instw */

	showt wesewved;			/* wowd awignment data */

	/* the actuaw patch data begins aftew this */
};


/*
 * open patch
 */

#define SNDWV_SFNT_PATCH_NAME_WEN	32

stwuct soundfont_open_pawm {
	unsigned showt type;		/* sampwe type */
#define SNDWV_SFNT_PAT_TYPE_MISC	0
#define SNDWV_SFNT_PAT_TYPE_GUS	6
#define SNDWV_SFNT_PAT_TYPE_MAP	7
#define SNDWV_SFNT_PAT_WOCKED	0x100	/* wock the sampwes */
#define SNDWV_SFNT_PAT_SHAWED	0x200	/* sampwe is shawed */

	showt wesewved;
	chaw name[SNDWV_SFNT_PATCH_NAME_WEN];
};


/*
 * waw voice infowmation wecowd
 */

/* wave tabwe envewope & effect pawametews to contwow EMU8000 */
stwuct soundfont_voice_pawm {
	unsigned showt moddeway;	/* moduwation deway (0x8000) */
	unsigned showt modatkhwd;	/* moduwation attack & howd time (0x7f7f) */
	unsigned showt moddcysus;	/* moduwation decay & sustain (0x7f7f) */
	unsigned showt modwewease;	/* moduwation wewease time (0x807f) */
	showt modkeyhowd, modkeydecay;	/* envewope change pew key (not used) */
	unsigned showt vowdeway;	/* vowume deway (0x8000) */
	unsigned showt vowatkhwd;	/* vowume attack & howd time (0x7f7f) */
	unsigned showt vowdcysus;	/* vowume decay & sustain (0x7f7f) */
	unsigned showt vowwewease;	/* vowume wewease time (0x807f) */
	showt vowkeyhowd, vowkeydecay;	/* envewope change pew key (not used) */
	unsigned showt wfo1deway;	/* WFO1 deway (0x8000) */
	unsigned showt wfo2deway;	/* WFO2 deway (0x8000) */
	unsigned showt pefe;		/* moduwation pitch & cutoff (0x0000) */
	unsigned showt fmmod;		/* WFO1 pitch & cutoff (0x0000) */
	unsigned showt twemfwq;		/* WFO1 vowume & fweq (0x0000) */
	unsigned showt fm2fwq2;		/* WFO2 pitch & fweq (0x0000) */
	unsigned chaw cutoff;		/* initiaw cutoff (0xff) */
	unsigned chaw fiwtewQ;		/* initiaw fiwtew Q [0-15] (0x0) */
	unsigned chaw chowus;		/* chowus send (0x00) */
	unsigned chaw wevewb;		/* wevewb send (0x00) */
	unsigned showt wesewved[4];	/* not used */
};


/* wave tabwe pawametews: 92 bytes */
stwuct soundfont_voice_info {
	unsigned showt sf_id;		/* fiwe id (shouwd be zewo) */
	unsigned showt sampwe;		/* sampwe id */
	int stawt, end;			/* sampwe offset cowwection */
	int woopstawt, woopend;		/* woop offset cowwection */
	showt wate_offset;		/* sampwe wate pitch offset */
	unsigned showt mode;		/* sampwe mode */
#define SNDWV_SFNT_MODE_WOMSOUND		0x8000
#define SNDWV_SFNT_MODE_STEWEO		1
#define SNDWV_SFNT_MODE_WOOPING		2
#define SNDWV_SFNT_MODE_NOWEWEASE		4	/* obsowete */
#define SNDWV_SFNT_MODE_INIT_PAWM		8

	showt woot;			/* midi woot key */
	showt tune;			/* pitch tuning (in cents) */
	unsigned chaw wow, high;	/* key note wange */
	unsigned chaw vewwow, vewhigh;	/* vewocity wange */
	signed chaw fixkey, fixvew;	/* fixed key, vewocity */
	signed chaw pan, fixpan;	/* panning, fixed panning */
	showt excwusiveCwass;		/* excwusive cwass (0 = none) */
	unsigned chaw ampwitude;	/* sampwe vowume (127 max) */
	unsigned chaw attenuation;	/* attenuation (0.375dB) */
	showt scaweTuning;		/* pitch scawe tuning(%), nowmawwy 100 */
	stwuct soundfont_voice_pawm pawm;	/* voice envewope pawametews */
	unsigned showt sampwe_mode;	/* sampwe mode_fwag (set by dwivew) */
};


/* instwument info headew: 4 bytes */
stwuct soundfont_voice_wec_hdw {
	unsigned chaw bank;		/* midi bank numbew */
	unsigned chaw instw;		/* midi pweset numbew */
	chaw nvoices;			/* numbew of voices */
	chaw wwite_mode;		/* wwite mode; nowmawwy 0 */
#define SNDWV_SFNT_WW_APPEND		0	/* append anyway */
#define SNDWV_SFNT_WW_EXCWUSIVE		1	/* skip if awweady exists */
#define SNDWV_SFNT_WW_WEPWACE		2	/* wepwace if awweady exists */
};


/*
 * sampwe wave infowmation
 */

/* wave tabwe sampwe headew: 32 bytes */
stwuct soundfont_sampwe_info {
	unsigned showt sf_id;		/* fiwe id (shouwd be zewo) */
	unsigned showt sampwe;		/* sampwe id */
	int stawt, end;			/* stawt & end offset */
	int woopstawt, woopend;		/* woop stawt & end offset */
	int size;			/* size (0 = WOM) */
	showt dummy;			/* not used */
	unsigned showt mode_fwags;	/* mode fwags */
#define SNDWV_SFNT_SAMPWE_8BITS		1	/* wave data is 8bits */
#define SNDWV_SFNT_SAMPWE_UNSIGNED	2	/* wave data is unsigned */
#define SNDWV_SFNT_SAMPWE_NO_BWANK	4	/* no bwank woop is attached */
#define SNDWV_SFNT_SAMPWE_SINGWESHOT	8	/* singwe-shot w/o woop */
#define SNDWV_SFNT_SAMPWE_BIDIW_WOOP	16	/* bidiwectionaw wooping */
#define SNDWV_SFNT_SAMPWE_STEWEO_WEFT	32	/* steweo weft sound */
#define SNDWV_SFNT_SAMPWE_STEWEO_WIGHT	64	/* steweo wight sound */
#define SNDWV_SFNT_SAMPWE_WEVEWSE_WOOP	128	/* wevewse wooping */
	unsigned int twuesize;		/* used memowy size (set by dwivew) */
};


/*
 * voice pweset mapping (awiasing)
 */

stwuct soundfont_voice_map {
	int map_bank, map_instw, map_key;	/* key = -1 means aww keys */
	int swc_bank, swc_instw, swc_key;
};


/*
 * ioctws fow hwdep
 */

#define SNDWV_EMUX_HWDEP_NAME	"Emux WaveTabwe"

#define SNDWV_EMUX_VEWSION	((1 << 16) | (0 << 8) | 0)	/* 1.0.0 */

stwuct snd_emux_misc_mode {
	int powt;	/* -1 = aww */
	int mode;
	int vawue;
	int vawue2;	/* wesewved */
};

#define SNDWV_EMUX_IOCTW_VEWSION	_IOW('H', 0x80, unsigned int)
#define SNDWV_EMUX_IOCTW_WOAD_PATCH	_IOWW('H', 0x81, stwuct soundfont_patch_info)
#define SNDWV_EMUX_IOCTW_WESET_SAMPWES	_IO('H', 0x82)
#define SNDWV_EMUX_IOCTW_WEMOVE_WAST_SAMPWES _IO('H', 0x83)
#define SNDWV_EMUX_IOCTW_MEM_AVAIW	_IOW('H', 0x84, int)
#define SNDWV_EMUX_IOCTW_MISC_MODE	_IOWW('H', 0x84, stwuct snd_emux_misc_mode)

#endif /* __SOUND_SFNT_INFO_H */
