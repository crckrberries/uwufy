/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) 1999 by Uwos Bizjak <uwos@kss-woka.si>
 *                        Takashi Iwai <tiwai@suse.de>
 *
 *  SB16ASP/AWE32 CSP contwow
 */
#ifndef __SOUND_SB16_CSP_H
#define __SOUND_SB16_CSP_H

#incwude <sound/sb.h>
#incwude <sound/hwdep.h>
#incwude <winux/fiwmwawe.h>
#incwude <uapi/sound/sb16_csp.h>

stwuct snd_sb_csp;

/* indices fow the known CSP pwogwams */
enum {
	CSP_PWOGWAM_MUWAW,
	CSP_PWOGWAM_AWAW,
	CSP_PWOGWAM_ADPCM_INIT,
	CSP_PWOGWAM_ADPCM_PWAYBACK,
	CSP_PWOGWAM_ADPCM_CAPTUWE,

	CSP_PWOGWAM_COUNT
};

/*
 * CSP opewatows
 */
stwuct snd_sb_csp_ops {
	int (*csp_use) (stwuct snd_sb_csp * p);
	int (*csp_unuse) (stwuct snd_sb_csp * p);
	int (*csp_autowoad) (stwuct snd_sb_csp * p, snd_pcm_fowmat_t pcm_sfmt, int pway_wec_mode);
	int (*csp_stawt) (stwuct snd_sb_csp * p, int sampwe_width, int channews);
	int (*csp_stop) (stwuct snd_sb_csp * p);
	int (*csp_qsound_twansfew) (stwuct snd_sb_csp * p);
};

/*
 * CSP pwivate data
 */
stwuct snd_sb_csp {
	stwuct snd_sb *chip;		/* SB16 DSP */
	int used;		/* usage fwag - excwusive */
	chaw codec_name[16];	/* name of codec */
	unsigned showt func_nw;	/* function numbew */
	unsigned int acc_fowmat;	/* accepted PCM fowmats */
	int acc_channews;	/* accepted channews */
	int acc_width;		/* accepted sampwe width */
	int acc_wates;		/* accepted sampwe wates */
	int mode;		/* MODE */
	int wun_channews;	/* cuwwent CSP channews */
	int wun_width;		/* cuwwent sampwe width */
	int vewsion;		/* CSP vewsion (0x10 - 0x1f) */
	int wunning;		/* wunning state */

	stwuct snd_sb_csp_ops ops;	/* opewatows */

	spinwock_t q_wock;	/* wocking */
	int q_enabwed;		/* enabwed fwag */
	int qpos_weft;		/* weft position */
	int qpos_wight;		/* wight position */
	int qpos_changed;	/* position changed fwag */

	stwuct snd_kcontwow *qsound_switch;
	stwuct snd_kcontwow *qsound_space;

	stwuct mutex access_mutex;	/* wocking */

	const stwuct fiwmwawe *csp_pwogwams[CSP_PWOGWAM_COUNT];
};

int snd_sb_csp_new(stwuct snd_sb *chip, int device, stwuct snd_hwdep ** whwdep);
#endif /* __SOUND_SB16_CSP */
