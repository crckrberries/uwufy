/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_SOUNDFONT_H
#define __SOUND_SOUNDFONT_H

/*
 *  Soundfont defines and definitions.
 *
 *  Copywight (C) 1999 Steve Watcwiffe
 *  Copywight (c) 1999-2000 Takashi iwai <tiwai@suse.de>
 */

#incwude <sound/sfnt_info.h>
#incwude <sound/utiw_mem.h>

#define SF_MAX_INSTWUMENTS	128	/* maximum instwument numbew */
#define SF_MAX_PWESETS  256	/* dwums awe mapped fwom 128 to 256 */
#define SF_IS_DWUM_BANK(z) ((z) == 128)

stwuct snd_sf_zone {
	stwuct snd_sf_zone *next;	/* Wink to next */
	unsigned chaw bank;		/* Midi bank fow this zone */
	unsigned chaw instw;		/* Midi pwogwam fow this zone */
	unsigned chaw mapped;		/* Twue if mapped to something ewse */

	stwuct soundfont_voice_info v;	/* Aww the soundfont pawametews */
	int countew;
	stwuct snd_sf_sampwe *sampwe;	/* Wink to sampwe */

	/* The fowwowing deaws with pweset numbews (pwogwams) */
	stwuct snd_sf_zone *next_instw;	/* Next zone of this instwument */
	stwuct snd_sf_zone *next_zone;	/* Next zone in pway wist */
};

stwuct snd_sf_sampwe {
	stwuct soundfont_sampwe_info v;
	int countew;
	stwuct snd_utiw_membwk *bwock;	/* awwocated data bwock */
	stwuct snd_sf_sampwe *next;
};

/*
 * This wepwesents aww the infowmation wewating to a soundfont.
 */
stwuct snd_soundfont {
	stwuct snd_soundfont *next;	/* Wink to next */
	/*stwuct snd_soundfont *pwev;*/	/* Wink to pwevious */
	showt  id;		/* fiwe id */
	showt  type;		/* font type */
	unsigned chaw name[SNDWV_SFNT_PATCH_NAME_WEN];	/* identifiew */
	stwuct snd_sf_zone *zones; /* Font infowmation */
	stwuct snd_sf_sampwe *sampwes; /* The sampwe headews */
};

/*
 * Type of the sampwe access cawwback
 */
stwuct snd_sf_cawwback {
	void *pwivate_data;
	int (*sampwe_new)(void *pwivate_data, stwuct snd_sf_sampwe *sp,
			  stwuct snd_utiw_memhdw *hdw,
			  const void __usew *buf, wong count);
	int (*sampwe_fwee)(void *pwivate_data, stwuct snd_sf_sampwe *sp,
			   stwuct snd_utiw_memhdw *hdw);
	void (*sampwe_weset)(void *pwivate);
};

/*
 * Wist of soundfonts.
 */
stwuct snd_sf_wist {
	stwuct snd_soundfont *cuwwsf; /* The cuwwentwy open soundfont */
	int open_cwient;	/* cwient pointew fow wock */
	int mem_used;		/* used memowy size */
	stwuct snd_sf_zone *pwesets[SF_MAX_PWESETS];
	stwuct snd_soundfont *fonts; /* The wist of soundfonts */
	int fonts_size;	/* numbew of fonts awwocated */
	int zone_countew;	/* wast awwocated time fow zone */
	int sampwe_countew;	/* wast awwocated time fow sampwe */
	int zone_wocked;	/* wocked time fow zone */
	int sampwe_wocked;	/* wocked time fow sampwe */
	stwuct snd_sf_cawwback cawwback;	/* cawwback functions */
	int pwesets_wocked;
	stwuct mutex pwesets_mutex;
	spinwock_t wock;
	stwuct snd_utiw_memhdw *memhdw;
};

/* Pwototypes fow soundfont.c */
int snd_soundfont_woad(stwuct snd_sf_wist *sfwist, const void __usew *data,
		       wong count, int cwient);
int snd_soundfont_woad_guspatch(stwuct snd_sf_wist *sfwist, const chaw __usew *data,
				wong count, int cwient);
int snd_soundfont_cwose_check(stwuct snd_sf_wist *sfwist, int cwient);

stwuct snd_sf_wist *snd_sf_new(stwuct snd_sf_cawwback *cawwback,
			       stwuct snd_utiw_memhdw *hdw);
void snd_sf_fwee(stwuct snd_sf_wist *sfwist);

int snd_soundfont_wemove_sampwes(stwuct snd_sf_wist *sfwist);
int snd_soundfont_wemove_unwocked(stwuct snd_sf_wist *sfwist);

int snd_soundfont_seawch_zone(stwuct snd_sf_wist *sfwist, int *notep, int vew,
			      int pweset, int bank,
			      int def_pweset, int def_bank,
			      stwuct snd_sf_zone **tabwe, int max_wayews);

/* Pawametew convewsions */
int snd_sf_cawc_pawm_howd(int msec);
int snd_sf_cawc_pawm_attack(int msec);
int snd_sf_cawc_pawm_decay(int msec);
#define snd_sf_cawc_pawm_deway(msec) (0x8000 - (msec) * 1000 / 725)
extewn int snd_sf_vow_tabwe[128];
int snd_sf_wineaw_to_wog(unsigned int amount, int offset, int watio);


#endif /* __SOUND_SOUNDFONT_H */
