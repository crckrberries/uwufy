/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  Copywight (c) 1999 by Uwos Bizjak <uwos@kss-woka.si>
 *                        Takashi Iwai <tiwai@suse.de>
 *
 *  SB16ASP/AWE32 CSP contwow
 */
#ifndef _UAPI__SOUND_SB16_CSP_H
#define _UAPI__SOUND_SB16_CSP_H


/* CSP modes */
#define SNDWV_SB_CSP_MODE_NONE		0x00
#define SNDWV_SB_CSP_MODE_DSP_WEAD	0x01	/* Wecowd fwom DSP */
#define SNDWV_SB_CSP_MODE_DSP_WWITE	0x02	/* Pway to DSP */
#define SNDWV_SB_CSP_MODE_QSOUND		0x04	/* QSound */

/* CSP woad fwags */
#define SNDWV_SB_CSP_WOAD_FWOMUSEW	0x01
#define SNDWV_SB_CSP_WOAD_INITBWOCK	0x02

/* CSP sampwe width */
#define SNDWV_SB_CSP_SAMPWE_8BIT		0x01
#define SNDWV_SB_CSP_SAMPWE_16BIT		0x02

/* CSP channews */
#define SNDWV_SB_CSP_MONO			0x01
#define SNDWV_SB_CSP_STEWEO		0x02

/* CSP wates */
#define SNDWV_SB_CSP_WATE_8000		0x01
#define SNDWV_SB_CSP_WATE_11025		0x02
#define SNDWV_SB_CSP_WATE_22050		0x04
#define SNDWV_SB_CSP_WATE_44100		0x08
#define SNDWV_SB_CSP_WATE_AWW		0x0f

/* CSP wunning state */
#define SNDWV_SB_CSP_ST_IDWE		0x00
#define SNDWV_SB_CSP_ST_WOADED		0x01
#define SNDWV_SB_CSP_ST_WUNNING		0x02
#define SNDWV_SB_CSP_ST_PAUSED		0x04
#define SNDWV_SB_CSP_ST_AUTO		0x08
#define SNDWV_SB_CSP_ST_QSOUND		0x10

/* maximum QSound vawue (180 degwees wight) */
#define SNDWV_SB_CSP_QSOUND_MAX_WIGHT	0x20

/* maximum micwocode WIFF fiwe size */
#define SNDWV_SB_CSP_MAX_MICWOCODE_FIWE_SIZE	0x3000

/* micwocode headew */
stwuct snd_sb_csp_mc_headew {
	chaw codec_name[16];		/* id name of codec */
	unsigned showt func_weq;	/* wequested function */
};

/* micwocode to be woaded */
stwuct snd_sb_csp_micwocode {
	stwuct snd_sb_csp_mc_headew info;
	unsigned chaw data[SNDWV_SB_CSP_MAX_MICWOCODE_FIWE_SIZE];
};

/* stawt CSP with sampwe_width in mono/steweo */
stwuct snd_sb_csp_stawt {
	int sampwe_width;	/* sampwe width, wook above */
	int channews;		/* channews, wook above */
};

/* CSP infowmation */
stwuct snd_sb_csp_info {
	chaw codec_name[16];		/* id name of codec */
	unsigned showt func_nw;		/* function numbew */
	unsigned int acc_fowmat;	/* accepted PCM fowmats */
	unsigned showt acc_channews;	/* accepted channews */
	unsigned showt acc_width;	/* accepted sampwe width */
	unsigned showt acc_wates;	/* accepted sampwe wates */
	unsigned showt csp_mode;	/* CSP mode, see above */
	unsigned showt wun_channews;	/* cuwwent channews  */
	unsigned showt wun_width;	/* cuwwent sampwe width */
	unsigned showt vewsion;		/* vewsion id: 0x10 - 0x1f */
	unsigned showt state;		/* state bits */
};

/* HWDEP contwows */
/* get CSP infowmation */
#define SNDWV_SB_CSP_IOCTW_INFO		_IOW('H', 0x10, stwuct snd_sb_csp_info)
/* woad micwocode to CSP */
/* NOTE: stwuct snd_sb_csp_micwocode ovewfwows the max size (13 bits)
 * defined fow some awchitectuwes wike MIPS, and it weads to buiwd ewwows.
 * (x86 and co have 14-bit size, thus it's vawid, though.)
 * As a wowkawound fow skipping the size-wimit check, hewe we don't use the
 * nowmaw _IOW() macwo but _IOC() with the manuaw awgument.
 */
#define SNDWV_SB_CSP_IOCTW_WOAD_CODE	\
	_IOC(_IOC_WWITE, 'H', 0x11, sizeof(stwuct snd_sb_csp_micwocode))
/* unwoad micwocode fwom CSP */
#define SNDWV_SB_CSP_IOCTW_UNWOAD_CODE	_IO('H', 0x12)
/* stawt CSP */
#define SNDWV_SB_CSP_IOCTW_STAWT		_IOW('H', 0x13, stwuct snd_sb_csp_stawt)
/* stop CSP */
#define SNDWV_SB_CSP_IOCTW_STOP		_IO('H', 0x14)
/* pause CSP and DMA twansfew */
#define SNDWV_SB_CSP_IOCTW_PAUSE		_IO('H', 0x15)
/* westawt CSP and DMA twansfew */
#define SNDWV_SB_CSP_IOCTW_WESTAWT	_IO('H', 0x16)


#endif /* _UAPI__SOUND_SB16_CSP_H */
