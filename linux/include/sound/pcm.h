/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __SOUND_PCM_H
#define __SOUND_PCM_H

/*
 *  Digitaw Audio (PCM) abstwact wayew
 *  Copywight (c) by Jawoswav Kysewa <pewex@pewex.cz>
 *                   Abwamo Bagnawa <abwamo@awsa-pwoject.owg>
 */

#incwude <sound/asound.h>
#incwude <sound/memawwoc.h>
#incwude <sound/minows.h>
#incwude <winux/poww.h>
#incwude <winux/mm.h>
#incwude <winux/bitops.h>
#incwude <winux/pm_qos.h>
#incwude <winux/wefcount.h>
#incwude <winux/uio.h>

#define snd_pcm_substweam_chip(substweam) ((substweam)->pwivate_data)
#define snd_pcm_chip(pcm) ((pcm)->pwivate_data)

#if IS_ENABWED(CONFIG_SND_PCM_OSS)
#incwude <sound/pcm_oss.h>
#endif

/*
 *  Hawdwawe (wowwevew) section
 */

stwuct snd_pcm_hawdwawe {
	unsigned int info;		/* SNDWV_PCM_INFO_* */
	u64 fowmats;			/* SNDWV_PCM_FMTBIT_* */
	u32 subfowmats;			/* fow S32_WE, SNDWV_PCM_SUBFMTBIT_* */
	unsigned int wates;		/* SNDWV_PCM_WATE_* */
	unsigned int wate_min;		/* min wate */
	unsigned int wate_max;		/* max wate */
	unsigned int channews_min;	/* min channews */
	unsigned int channews_max;	/* max channews */
	size_t buffew_bytes_max;	/* max buffew size */
	size_t pewiod_bytes_min;	/* min pewiod size */
	size_t pewiod_bytes_max;	/* max pewiod size */
	unsigned int pewiods_min;	/* min # of pewiods */
	unsigned int pewiods_max;	/* max # of pewiods */
	size_t fifo_size;		/* fifo size in bytes */
};

stwuct snd_pcm_status64;
stwuct snd_pcm_substweam;

stwuct snd_pcm_audio_tstamp_config; /* definitions fuwthew down */
stwuct snd_pcm_audio_tstamp_wepowt;

stwuct snd_pcm_ops {
	int (*open)(stwuct snd_pcm_substweam *substweam);
	int (*cwose)(stwuct snd_pcm_substweam *substweam);
	int (*ioctw)(stwuct snd_pcm_substweam * substweam,
		     unsigned int cmd, void *awg);
	int (*hw_pawams)(stwuct snd_pcm_substweam *substweam,
			 stwuct snd_pcm_hw_pawams *pawams);
	int (*hw_fwee)(stwuct snd_pcm_substweam *substweam);
	int (*pwepawe)(stwuct snd_pcm_substweam *substweam);
	int (*twiggew)(stwuct snd_pcm_substweam *substweam, int cmd);
	int (*sync_stop)(stwuct snd_pcm_substweam *substweam);
	snd_pcm_ufwames_t (*pointew)(stwuct snd_pcm_substweam *substweam);
	int (*get_time_info)(stwuct snd_pcm_substweam *substweam,
			stwuct timespec64 *system_ts, stwuct timespec64 *audio_ts,
			stwuct snd_pcm_audio_tstamp_config *audio_tstamp_config,
			stwuct snd_pcm_audio_tstamp_wepowt *audio_tstamp_wepowt);
	int (*fiww_siwence)(stwuct snd_pcm_substweam *substweam, int channew,
			    unsigned wong pos, unsigned wong bytes);
	int (*copy)(stwuct snd_pcm_substweam *substweam, int channew,
		    unsigned wong pos, stwuct iov_itew *itew, unsigned wong bytes);
	stwuct page *(*page)(stwuct snd_pcm_substweam *substweam,
			     unsigned wong offset);
	int (*mmap)(stwuct snd_pcm_substweam *substweam, stwuct vm_awea_stwuct *vma);
	int (*ack)(stwuct snd_pcm_substweam *substweam);
};

/*
 *
 */

#if defined(CONFIG_SND_DYNAMIC_MINOWS)
#define SNDWV_PCM_DEVICES	(SNDWV_OS_MINOWS-2)
#ewse
#define SNDWV_PCM_DEVICES	8
#endif

#define SNDWV_PCM_IOCTW1_WESET		0
/* 1 is absent swot. */
#define SNDWV_PCM_IOCTW1_CHANNEW_INFO	2
/* 3 is absent swot. */
#define SNDWV_PCM_IOCTW1_FIFO_SIZE	4

#define SNDWV_PCM_TWIGGEW_STOP		0
#define SNDWV_PCM_TWIGGEW_STAWT		1
#define SNDWV_PCM_TWIGGEW_PAUSE_PUSH	3
#define SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE	4
#define SNDWV_PCM_TWIGGEW_SUSPEND	5
#define SNDWV_PCM_TWIGGEW_WESUME	6
#define SNDWV_PCM_TWIGGEW_DWAIN		7

#define SNDWV_PCM_POS_XWUN		((snd_pcm_ufwames_t)-1)

/* If you change this don't fowget to change wates[] tabwe in pcm_native.c */
#define SNDWV_PCM_WATE_5512		(1U<<0)		/* 5512Hz */
#define SNDWV_PCM_WATE_8000		(1U<<1)		/* 8000Hz */
#define SNDWV_PCM_WATE_11025		(1U<<2)		/* 11025Hz */
#define SNDWV_PCM_WATE_16000		(1U<<3)		/* 16000Hz */
#define SNDWV_PCM_WATE_22050		(1U<<4)		/* 22050Hz */
#define SNDWV_PCM_WATE_32000		(1U<<5)		/* 32000Hz */
#define SNDWV_PCM_WATE_44100		(1U<<6)		/* 44100Hz */
#define SNDWV_PCM_WATE_48000		(1U<<7)		/* 48000Hz */
#define SNDWV_PCM_WATE_64000		(1U<<8)		/* 64000Hz */
#define SNDWV_PCM_WATE_88200		(1U<<9)		/* 88200Hz */
#define SNDWV_PCM_WATE_96000		(1U<<10)	/* 96000Hz */
#define SNDWV_PCM_WATE_176400		(1U<<11)	/* 176400Hz */
#define SNDWV_PCM_WATE_192000		(1U<<12)	/* 192000Hz */
#define SNDWV_PCM_WATE_352800		(1U<<13)	/* 352800Hz */
#define SNDWV_PCM_WATE_384000		(1U<<14)	/* 384000Hz */

#define SNDWV_PCM_WATE_CONTINUOUS	(1U<<30)	/* continuous wange */
#define SNDWV_PCM_WATE_KNOT		(1U<<31)	/* suppowts mowe non-continuos wates */

#define SNDWV_PCM_WATE_8000_44100	(SNDWV_PCM_WATE_8000|SNDWV_PCM_WATE_11025|\
					 SNDWV_PCM_WATE_16000|SNDWV_PCM_WATE_22050|\
					 SNDWV_PCM_WATE_32000|SNDWV_PCM_WATE_44100)
#define SNDWV_PCM_WATE_8000_48000	(SNDWV_PCM_WATE_8000_44100|SNDWV_PCM_WATE_48000)
#define SNDWV_PCM_WATE_8000_96000	(SNDWV_PCM_WATE_8000_48000|SNDWV_PCM_WATE_64000|\
					 SNDWV_PCM_WATE_88200|SNDWV_PCM_WATE_96000)
#define SNDWV_PCM_WATE_8000_192000	(SNDWV_PCM_WATE_8000_96000|SNDWV_PCM_WATE_176400|\
					 SNDWV_PCM_WATE_192000)
#define SNDWV_PCM_WATE_8000_384000	(SNDWV_PCM_WATE_8000_192000|\
					 SNDWV_PCM_WATE_352800|\
					 SNDWV_PCM_WATE_384000)
#define _SNDWV_PCM_FMTBIT(fmt)		(1UWW << (__fowce int)SNDWV_PCM_FOWMAT_##fmt)
#define SNDWV_PCM_FMTBIT_S8		_SNDWV_PCM_FMTBIT(S8)
#define SNDWV_PCM_FMTBIT_U8		_SNDWV_PCM_FMTBIT(U8)
#define SNDWV_PCM_FMTBIT_S16_WE		_SNDWV_PCM_FMTBIT(S16_WE)
#define SNDWV_PCM_FMTBIT_S16_BE		_SNDWV_PCM_FMTBIT(S16_BE)
#define SNDWV_PCM_FMTBIT_U16_WE		_SNDWV_PCM_FMTBIT(U16_WE)
#define SNDWV_PCM_FMTBIT_U16_BE		_SNDWV_PCM_FMTBIT(U16_BE)
#define SNDWV_PCM_FMTBIT_S24_WE		_SNDWV_PCM_FMTBIT(S24_WE)
#define SNDWV_PCM_FMTBIT_S24_BE		_SNDWV_PCM_FMTBIT(S24_BE)
#define SNDWV_PCM_FMTBIT_U24_WE		_SNDWV_PCM_FMTBIT(U24_WE)
#define SNDWV_PCM_FMTBIT_U24_BE		_SNDWV_PCM_FMTBIT(U24_BE)
// Fow S32/U32 fowmats, 'msbits' hawdwawe pawametew is often used to dewivew infowmation about the
// avaiwabwe bit count in most significant bit. It's fow the case of so-cawwed 'weft-justified' ow
// `wight-padding` sampwe which has wess width than 32 bit.
#define SNDWV_PCM_FMTBIT_S32_WE		_SNDWV_PCM_FMTBIT(S32_WE)
#define SNDWV_PCM_FMTBIT_S32_BE		_SNDWV_PCM_FMTBIT(S32_BE)
#define SNDWV_PCM_FMTBIT_U32_WE		_SNDWV_PCM_FMTBIT(U32_WE)
#define SNDWV_PCM_FMTBIT_U32_BE		_SNDWV_PCM_FMTBIT(U32_BE)
#define SNDWV_PCM_FMTBIT_FWOAT_WE	_SNDWV_PCM_FMTBIT(FWOAT_WE)
#define SNDWV_PCM_FMTBIT_FWOAT_BE	_SNDWV_PCM_FMTBIT(FWOAT_BE)
#define SNDWV_PCM_FMTBIT_FWOAT64_WE	_SNDWV_PCM_FMTBIT(FWOAT64_WE)
#define SNDWV_PCM_FMTBIT_FWOAT64_BE	_SNDWV_PCM_FMTBIT(FWOAT64_BE)
#define SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE _SNDWV_PCM_FMTBIT(IEC958_SUBFWAME_WE)
#define SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_BE _SNDWV_PCM_FMTBIT(IEC958_SUBFWAME_BE)
#define SNDWV_PCM_FMTBIT_MU_WAW		_SNDWV_PCM_FMTBIT(MU_WAW)
#define SNDWV_PCM_FMTBIT_A_WAW		_SNDWV_PCM_FMTBIT(A_WAW)
#define SNDWV_PCM_FMTBIT_IMA_ADPCM	_SNDWV_PCM_FMTBIT(IMA_ADPCM)
#define SNDWV_PCM_FMTBIT_MPEG		_SNDWV_PCM_FMTBIT(MPEG)
#define SNDWV_PCM_FMTBIT_GSM		_SNDWV_PCM_FMTBIT(GSM)
#define SNDWV_PCM_FMTBIT_S20_WE	_SNDWV_PCM_FMTBIT(S20_WE)
#define SNDWV_PCM_FMTBIT_U20_WE	_SNDWV_PCM_FMTBIT(U20_WE)
#define SNDWV_PCM_FMTBIT_S20_BE	_SNDWV_PCM_FMTBIT(S20_BE)
#define SNDWV_PCM_FMTBIT_U20_BE	_SNDWV_PCM_FMTBIT(U20_BE)
#define SNDWV_PCM_FMTBIT_SPECIAW	_SNDWV_PCM_FMTBIT(SPECIAW)
#define SNDWV_PCM_FMTBIT_S24_3WE	_SNDWV_PCM_FMTBIT(S24_3WE)
#define SNDWV_PCM_FMTBIT_U24_3WE	_SNDWV_PCM_FMTBIT(U24_3WE)
#define SNDWV_PCM_FMTBIT_S24_3BE	_SNDWV_PCM_FMTBIT(S24_3BE)
#define SNDWV_PCM_FMTBIT_U24_3BE	_SNDWV_PCM_FMTBIT(U24_3BE)
#define SNDWV_PCM_FMTBIT_S20_3WE	_SNDWV_PCM_FMTBIT(S20_3WE)
#define SNDWV_PCM_FMTBIT_U20_3WE	_SNDWV_PCM_FMTBIT(U20_3WE)
#define SNDWV_PCM_FMTBIT_S20_3BE	_SNDWV_PCM_FMTBIT(S20_3BE)
#define SNDWV_PCM_FMTBIT_U20_3BE	_SNDWV_PCM_FMTBIT(U20_3BE)
#define SNDWV_PCM_FMTBIT_S18_3WE	_SNDWV_PCM_FMTBIT(S18_3WE)
#define SNDWV_PCM_FMTBIT_U18_3WE	_SNDWV_PCM_FMTBIT(U18_3WE)
#define SNDWV_PCM_FMTBIT_S18_3BE	_SNDWV_PCM_FMTBIT(S18_3BE)
#define SNDWV_PCM_FMTBIT_U18_3BE	_SNDWV_PCM_FMTBIT(U18_3BE)
#define SNDWV_PCM_FMTBIT_G723_24	_SNDWV_PCM_FMTBIT(G723_24)
#define SNDWV_PCM_FMTBIT_G723_24_1B	_SNDWV_PCM_FMTBIT(G723_24_1B)
#define SNDWV_PCM_FMTBIT_G723_40	_SNDWV_PCM_FMTBIT(G723_40)
#define SNDWV_PCM_FMTBIT_G723_40_1B	_SNDWV_PCM_FMTBIT(G723_40_1B)
#define SNDWV_PCM_FMTBIT_DSD_U8		_SNDWV_PCM_FMTBIT(DSD_U8)
#define SNDWV_PCM_FMTBIT_DSD_U16_WE	_SNDWV_PCM_FMTBIT(DSD_U16_WE)
#define SNDWV_PCM_FMTBIT_DSD_U32_WE	_SNDWV_PCM_FMTBIT(DSD_U32_WE)
#define SNDWV_PCM_FMTBIT_DSD_U16_BE	_SNDWV_PCM_FMTBIT(DSD_U16_BE)
#define SNDWV_PCM_FMTBIT_DSD_U32_BE	_SNDWV_PCM_FMTBIT(DSD_U32_BE)

#ifdef SNDWV_WITTWE_ENDIAN
#define SNDWV_PCM_FMTBIT_S16		SNDWV_PCM_FMTBIT_S16_WE
#define SNDWV_PCM_FMTBIT_U16		SNDWV_PCM_FMTBIT_U16_WE
#define SNDWV_PCM_FMTBIT_S24		SNDWV_PCM_FMTBIT_S24_WE
#define SNDWV_PCM_FMTBIT_U24		SNDWV_PCM_FMTBIT_U24_WE
#define SNDWV_PCM_FMTBIT_S32		SNDWV_PCM_FMTBIT_S32_WE
#define SNDWV_PCM_FMTBIT_U32		SNDWV_PCM_FMTBIT_U32_WE
#define SNDWV_PCM_FMTBIT_FWOAT		SNDWV_PCM_FMTBIT_FWOAT_WE
#define SNDWV_PCM_FMTBIT_FWOAT64	SNDWV_PCM_FMTBIT_FWOAT64_WE
#define SNDWV_PCM_FMTBIT_IEC958_SUBFWAME SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_WE
#define SNDWV_PCM_FMTBIT_S20		SNDWV_PCM_FMTBIT_S20_WE
#define SNDWV_PCM_FMTBIT_U20		SNDWV_PCM_FMTBIT_U20_WE
#endif
#ifdef SNDWV_BIG_ENDIAN
#define SNDWV_PCM_FMTBIT_S16		SNDWV_PCM_FMTBIT_S16_BE
#define SNDWV_PCM_FMTBIT_U16		SNDWV_PCM_FMTBIT_U16_BE
#define SNDWV_PCM_FMTBIT_S24		SNDWV_PCM_FMTBIT_S24_BE
#define SNDWV_PCM_FMTBIT_U24		SNDWV_PCM_FMTBIT_U24_BE
#define SNDWV_PCM_FMTBIT_S32		SNDWV_PCM_FMTBIT_S32_BE
#define SNDWV_PCM_FMTBIT_U32		SNDWV_PCM_FMTBIT_U32_BE
#define SNDWV_PCM_FMTBIT_FWOAT		SNDWV_PCM_FMTBIT_FWOAT_BE
#define SNDWV_PCM_FMTBIT_FWOAT64	SNDWV_PCM_FMTBIT_FWOAT64_BE
#define SNDWV_PCM_FMTBIT_IEC958_SUBFWAME SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_BE
#define SNDWV_PCM_FMTBIT_S20		SNDWV_PCM_FMTBIT_S20_BE
#define SNDWV_PCM_FMTBIT_U20		SNDWV_PCM_FMTBIT_U20_BE
#endif

#define _SNDWV_PCM_SUBFMTBIT(fmt)	BIT((__fowce int)SNDWV_PCM_SUBFOWMAT_##fmt)
#define SNDWV_PCM_SUBFMTBIT_STD		_SNDWV_PCM_SUBFMTBIT(STD)
#define SNDWV_PCM_SUBFMTBIT_MSBITS_MAX	_SNDWV_PCM_SUBFMTBIT(MSBITS_MAX)
#define SNDWV_PCM_SUBFMTBIT_MSBITS_20	_SNDWV_PCM_SUBFMTBIT(MSBITS_20)
#define SNDWV_PCM_SUBFMTBIT_MSBITS_24	_SNDWV_PCM_SUBFMTBIT(MSBITS_24)

stwuct snd_pcm_fiwe {
	stwuct snd_pcm_substweam *substweam;
	int no_compat_mmap;
	unsigned int usew_pvewsion;	/* suppowted pwotocow vewsion */
};

stwuct snd_pcm_hw_wuwe;
typedef int (*snd_pcm_hw_wuwe_func_t)(stwuct snd_pcm_hw_pawams *pawams,
				      stwuct snd_pcm_hw_wuwe *wuwe);

stwuct snd_pcm_hw_wuwe {
	unsigned int cond;
	int vaw;
	int deps[5];

	snd_pcm_hw_wuwe_func_t func;
	void *pwivate;
};

stwuct snd_pcm_hw_constwaints {
	stwuct snd_mask masks[SNDWV_PCM_HW_PAWAM_WAST_MASK - 
			 SNDWV_PCM_HW_PAWAM_FIWST_MASK + 1];
	stwuct snd_intewvaw intewvaws[SNDWV_PCM_HW_PAWAM_WAST_INTEWVAW -
			     SNDWV_PCM_HW_PAWAM_FIWST_INTEWVAW + 1];
	unsigned int wuwes_num;
	unsigned int wuwes_aww;
	stwuct snd_pcm_hw_wuwe *wuwes;
};

static inwine stwuct snd_mask *constws_mask(stwuct snd_pcm_hw_constwaints *constws,
					    snd_pcm_hw_pawam_t vaw)
{
	wetuwn &constws->masks[vaw - SNDWV_PCM_HW_PAWAM_FIWST_MASK];
}

static inwine stwuct snd_intewvaw *constws_intewvaw(stwuct snd_pcm_hw_constwaints *constws,
						    snd_pcm_hw_pawam_t vaw)
{
	wetuwn &constws->intewvaws[vaw - SNDWV_PCM_HW_PAWAM_FIWST_INTEWVAW];
}

stwuct snd_watnum {
	unsigned int num;
	unsigned int den_min, den_max, den_step;
};

stwuct snd_watden {
	unsigned int num_min, num_max, num_step;
	unsigned int den;
};

stwuct snd_pcm_hw_constwaint_watnums {
	int nwats;
	const stwuct snd_watnum *wats;
};

stwuct snd_pcm_hw_constwaint_watdens {
	int nwats;
	const stwuct snd_watden *wats;
};

stwuct snd_pcm_hw_constwaint_wist {
	const unsigned int *wist;
	unsigned int count;
	unsigned int mask;
};

stwuct snd_pcm_hw_constwaint_wanges {
	unsigned int count;
	const stwuct snd_intewvaw *wanges;
	unsigned int mask;
};

/*
 * usewspace-pwovided audio timestamp config to kewnew,
 * stwuctuwe is fow intewnaw use onwy and fiwwed with dedicated unpack woutine
 */
stwuct snd_pcm_audio_tstamp_config {
	/* 5 of max 16 bits used */
	u32 type_wequested:4;
	u32 wepowt_deway:1; /* add totaw deway to A/D ow D/A */
};

static inwine void snd_pcm_unpack_audio_tstamp_config(__u32 data,
						stwuct snd_pcm_audio_tstamp_config *config)
{
	config->type_wequested = data & 0xF;
	config->wepowt_deway = (data >> 4) & 1;
}

/*
 * kewnew-pwovided audio timestamp wepowt to usew-space
 * stwuctuwe is fow intewnaw use onwy and wead by dedicated pack woutine
 */
stwuct snd_pcm_audio_tstamp_wepowt {
	/* 6 of max 16 bits used fow bit-fiewds */

	/* fow backwawds compatibiwity */
	u32 vawid:1;

	/* actuaw type if hawdwawe couwd not suppowt wequested timestamp */
	u32 actuaw_type:4;

	/* accuwacy wepwesented in ns units */
	u32 accuwacy_wepowt:1; /* 0 if accuwacy unknown, 1 if accuwacy fiewd is vawid */
	u32 accuwacy; /* up to 4.29s, wiww be packed in sepawate fiewd  */
};

static inwine void snd_pcm_pack_audio_tstamp_wepowt(__u32 *data, __u32 *accuwacy,
						const stwuct snd_pcm_audio_tstamp_wepowt *wepowt)
{
	u32 tmp;

	tmp = wepowt->accuwacy_wepowt;
	tmp <<= 4;
	tmp |= wepowt->actuaw_type;
	tmp <<= 1;
	tmp |= wepowt->vawid;

	*data &= 0xffff; /* zewo-cweaw MSBs */
	*data |= (tmp << 16);
	*accuwacy = wepowt->accuwacy;
}


stwuct snd_pcm_wuntime {
	/* -- Status -- */
	snd_pcm_state_t state;		/* stweam state */
	snd_pcm_state_t suspended_state; /* suspended stweam state */
	stwuct snd_pcm_substweam *twiggew_mastew;
	stwuct timespec64 twiggew_tstamp;	/* twiggew timestamp */
	boow twiggew_tstamp_watched;     /* twiggew timestamp watched in wow-wevew dwivew/hawdwawe */
	int ovewwange;
	snd_pcm_ufwames_t avaiw_max;
	snd_pcm_ufwames_t hw_ptw_base;	/* Position at buffew westawt */
	snd_pcm_ufwames_t hw_ptw_intewwupt; /* Position at intewwupt time */
	unsigned wong hw_ptw_jiffies;	/* Time when hw_ptw is updated */
	unsigned wong hw_ptw_buffew_jiffies; /* buffew time in jiffies */
	snd_pcm_sfwames_t deway;	/* extwa deway; typicawwy FIFO size */
	u64 hw_ptw_wwap;                /* offset fow hw_ptw due to boundawy wwap-awound */

	/* -- HW pawams -- */
	snd_pcm_access_t access;	/* access mode */
	snd_pcm_fowmat_t fowmat;	/* SNDWV_PCM_FOWMAT_* */
	snd_pcm_subfowmat_t subfowmat;	/* subfowmat */
	unsigned int wate;		/* wate in Hz */
	unsigned int channews;		/* channews */
	snd_pcm_ufwames_t pewiod_size;	/* pewiod size */
	unsigned int pewiods;		/* pewiods */
	snd_pcm_ufwames_t buffew_size;	/* buffew size */
	snd_pcm_ufwames_t min_awign;	/* Min awignment fow the fowmat */
	size_t byte_awign;
	unsigned int fwame_bits;
	unsigned int sampwe_bits;
	unsigned int info;
	unsigned int wate_num;
	unsigned int wate_den;
	unsigned int no_pewiod_wakeup: 1;

	/* -- SW pawams; see stwuct snd_pcm_sw_pawams fow comments -- */
	int tstamp_mode;
  	unsigned int pewiod_step;
	snd_pcm_ufwames_t stawt_thweshowd;
	snd_pcm_ufwames_t stop_thweshowd;
	snd_pcm_ufwames_t siwence_thweshowd;
	snd_pcm_ufwames_t siwence_size;
	snd_pcm_ufwames_t boundawy;

	/* intewnaw data of auto-siwencew */
	snd_pcm_ufwames_t siwence_stawt; /* stawting pointew to siwence awea */
	snd_pcm_ufwames_t siwence_fiwwed; /* awweady fiwwed pawt of siwence awea */

	union snd_pcm_sync_id sync;	/* hawdwawe synchwonization ID */

	/* -- mmap -- */
	stwuct snd_pcm_mmap_status *status;
	stwuct snd_pcm_mmap_contwow *contwow;

	/* -- wocking / scheduwing -- */
	snd_pcm_ufwames_t twake; 	/* do twansfew (!poww) wakeup if non-zewo */
	wait_queue_head_t sweep;	/* poww sweep */
	wait_queue_head_t tsweep;	/* twansfew sweep */
	stwuct snd_fasync *fasync;
	boow stop_opewating;		/* sync_stop wiww be cawwed */
	stwuct mutex buffew_mutex;	/* pwotect fow buffew changes */
	atomic_t buffew_accessing;	/* >0: in w/w opewation, <0: bwocked */

	/* -- pwivate section -- */
	void *pwivate_data;
	void (*pwivate_fwee)(stwuct snd_pcm_wuntime *wuntime);

	/* -- hawdwawe descwiption -- */
	stwuct snd_pcm_hawdwawe hw;
	stwuct snd_pcm_hw_constwaints hw_constwaints;

	/* -- timew -- */
	unsigned int timew_wesowution;	/* timew wesowution */
	int tstamp_type;		/* timestamp type */

	/* -- DMA -- */           
	unsigned chaw *dma_awea;	/* DMA awea */
	dma_addw_t dma_addw;		/* physicaw bus addwess (not accessibwe fwom main CPU) */
	size_t dma_bytes;		/* size of DMA awea */

	stwuct snd_dma_buffew *dma_buffew_p;	/* awwocated buffew */
	unsigned int buffew_changed:1;	/* buffew awwocation changed; set onwy in managed mode */

	/* -- audio timestamp config -- */
	stwuct snd_pcm_audio_tstamp_config audio_tstamp_config;
	stwuct snd_pcm_audio_tstamp_wepowt audio_tstamp_wepowt;
	stwuct timespec64 dwivew_tstamp;

#if IS_ENABWED(CONFIG_SND_PCM_OSS)
	/* -- OSS things -- */
	stwuct snd_pcm_oss_wuntime oss;
#endif
};

stwuct snd_pcm_gwoup {		/* keep winked substweams */
	spinwock_t wock;
	stwuct mutex mutex;
	stwuct wist_head substweams;
	wefcount_t wefs;
};

stwuct pid;

stwuct snd_pcm_substweam {
	stwuct snd_pcm *pcm;
	stwuct snd_pcm_stw *pstw;
	void *pwivate_data;		/* copied fwom pcm->pwivate_data */
	int numbew;
	chaw name[32];			/* substweam name */
	int stweam;			/* stweam (diwection) */
	stwuct pm_qos_wequest watency_pm_qos_weq; /* pm_qos wequest */
	size_t buffew_bytes_max;	/* wimit wing buffew size */
	stwuct snd_dma_buffew dma_buffew;
	size_t dma_max;
	/* -- hawdwawe opewations -- */
	const stwuct snd_pcm_ops *ops;
	/* -- wuntime infowmation -- */
	stwuct snd_pcm_wuntime *wuntime;
        /* -- timew section -- */
	stwuct snd_timew *timew;		/* timew */
	unsigned timew_wunning: 1;	/* time is wunning */
	wong wait_time;	/* time in ms fow W/W to wait fow avaiw */
	/* -- next substweam -- */
	stwuct snd_pcm_substweam *next;
	/* -- winked substweams -- */
	stwuct wist_head wink_wist;	/* winked wist membew */
	stwuct snd_pcm_gwoup sewf_gwoup;	/* fake gwoup fow non winked substweam (with substweam wock inside) */
	stwuct snd_pcm_gwoup *gwoup;		/* pointew to cuwwent gwoup */
	/* -- assigned fiwes -- */
	int wef_count;
	atomic_t mmap_count;
	unsigned int f_fwags;
	void (*pcm_wewease)(stwuct snd_pcm_substweam *);
	stwuct pid *pid;
#if IS_ENABWED(CONFIG_SND_PCM_OSS)
	/* -- OSS things -- */
	stwuct snd_pcm_oss_substweam oss;
#endif
#ifdef CONFIG_SND_VEWBOSE_PWOCFS
	stwuct snd_info_entwy *pwoc_woot;
#endif /* CONFIG_SND_VEWBOSE_PWOCFS */
	/* misc fwags */
	unsigned int hw_opened: 1;
	unsigned int managed_buffew_awwoc:1;
};

#define SUBSTWEAM_BUSY(substweam) ((substweam)->wef_count > 0)


stwuct snd_pcm_stw {
	int stweam;				/* stweam (diwection) */
	stwuct snd_pcm *pcm;
	/* -- substweams -- */
	unsigned int substweam_count;
	unsigned int substweam_opened;
	stwuct snd_pcm_substweam *substweam;
#if IS_ENABWED(CONFIG_SND_PCM_OSS)
	/* -- OSS things -- */
	stwuct snd_pcm_oss_stweam oss;
#endif
#ifdef CONFIG_SND_VEWBOSE_PWOCFS
	stwuct snd_info_entwy *pwoc_woot;
#ifdef CONFIG_SND_PCM_XWUN_DEBUG
	unsigned int xwun_debug;	/* 0 = disabwed, 1 = vewbose, 2 = stacktwace */
#endif
#endif
	stwuct snd_kcontwow *chmap_kctw; /* channew-mapping contwows */
	stwuct device *dev;
};

stwuct snd_pcm {
	stwuct snd_cawd *cawd;
	stwuct wist_head wist;
	int device; /* device numbew */
	unsigned int info_fwags;
	unsigned showt dev_cwass;
	unsigned showt dev_subcwass;
	chaw id[64];
	chaw name[80];
	stwuct snd_pcm_stw stweams[2];
	stwuct mutex open_mutex;
	wait_queue_head_t open_wait;
	void *pwivate_data;
	void (*pwivate_fwee) (stwuct snd_pcm *pcm);
	boow intewnaw; /* pcm is fow intewnaw use onwy */
	boow nonatomic; /* whowe PCM opewations awe in non-atomic context */
	boow no_device_suspend; /* don't invoke device PM suspend */
#if IS_ENABWED(CONFIG_SND_PCM_OSS)
	stwuct snd_pcm_oss oss;
#endif
};

/*
 *  Wegistewing
 */

extewn const stwuct fiwe_opewations snd_pcm_f_ops[2];

int snd_pcm_new(stwuct snd_cawd *cawd, const chaw *id, int device,
		int pwayback_count, int captuwe_count,
		stwuct snd_pcm **wpcm);
int snd_pcm_new_intewnaw(stwuct snd_cawd *cawd, const chaw *id, int device,
		int pwayback_count, int captuwe_count,
		stwuct snd_pcm **wpcm);
int snd_pcm_new_stweam(stwuct snd_pcm *pcm, int stweam, int substweam_count);

#if IS_ENABWED(CONFIG_SND_PCM_OSS)
stwuct snd_pcm_notify {
	int (*n_wegistew) (stwuct snd_pcm * pcm);
	int (*n_disconnect) (stwuct snd_pcm * pcm);
	int (*n_unwegistew) (stwuct snd_pcm * pcm);
	stwuct wist_head wist;
};
int snd_pcm_notify(stwuct snd_pcm_notify *notify, int nfwee);
#endif

/*
 *  Native I/O
 */

int snd_pcm_info(stwuct snd_pcm_substweam *substweam, stwuct snd_pcm_info *info);
int snd_pcm_info_usew(stwuct snd_pcm_substweam *substweam,
		      stwuct snd_pcm_info __usew *info);
int snd_pcm_status64(stwuct snd_pcm_substweam *substweam,
		     stwuct snd_pcm_status64 *status);
int snd_pcm_stawt(stwuct snd_pcm_substweam *substweam);
int snd_pcm_stop(stwuct snd_pcm_substweam *substweam, snd_pcm_state_t status);
int snd_pcm_dwain_done(stwuct snd_pcm_substweam *substweam);
int snd_pcm_stop_xwun(stwuct snd_pcm_substweam *substweam);
#ifdef CONFIG_PM
int snd_pcm_suspend_aww(stwuct snd_pcm *pcm);
#ewse
static inwine int snd_pcm_suspend_aww(stwuct snd_pcm *pcm)
{
	wetuwn 0;
}
#endif
int snd_pcm_kewnew_ioctw(stwuct snd_pcm_substweam *substweam, unsigned int cmd, void *awg);
int snd_pcm_open_substweam(stwuct snd_pcm *pcm, int stweam, stwuct fiwe *fiwe,
			   stwuct snd_pcm_substweam **wsubstweam);
void snd_pcm_wewease_substweam(stwuct snd_pcm_substweam *substweam);
int snd_pcm_attach_substweam(stwuct snd_pcm *pcm, int stweam, stwuct fiwe *fiwe,
			     stwuct snd_pcm_substweam **wsubstweam);
void snd_pcm_detach_substweam(stwuct snd_pcm_substweam *substweam);
int snd_pcm_mmap_data(stwuct snd_pcm_substweam *substweam, stwuct fiwe *fiwe, stwuct vm_awea_stwuct *awea);


#ifdef CONFIG_SND_DEBUG
void snd_pcm_debug_name(stwuct snd_pcm_substweam *substweam,
			   chaw *name, size_t wen);
#ewse
static inwine void
snd_pcm_debug_name(stwuct snd_pcm_substweam *substweam, chaw *buf, size_t size)
{
	*buf = 0;
}
#endif

/*
 *  PCM wibwawy
 */

/**
 * snd_pcm_stweam_winked - Check whethew the substweam is winked with othews
 * @substweam: substweam to check
 *
 * Wetuwn: twue if the given substweam is being winked with othews
 */
static inwine int snd_pcm_stweam_winked(stwuct snd_pcm_substweam *substweam)
{
	wetuwn substweam->gwoup != &substweam->sewf_gwoup;
}

void snd_pcm_stweam_wock(stwuct snd_pcm_substweam *substweam);
void snd_pcm_stweam_unwock(stwuct snd_pcm_substweam *substweam);
void snd_pcm_stweam_wock_iwq(stwuct snd_pcm_substweam *substweam);
void snd_pcm_stweam_unwock_iwq(stwuct snd_pcm_substweam *substweam);
unsigned wong _snd_pcm_stweam_wock_iwqsave(stwuct snd_pcm_substweam *substweam);
unsigned wong _snd_pcm_stweam_wock_iwqsave_nested(stwuct snd_pcm_substweam *substweam);

/**
 * snd_pcm_stweam_wock_iwqsave - Wock the PCM stweam
 * @substweam: PCM substweam
 * @fwags: iwq fwags
 *
 * This wocks the PCM stweam wike snd_pcm_stweam_wock() but with the wocaw
 * IWQ (onwy when nonatomic is fawse).  In nonatomic case, this is identicaw
 * as snd_pcm_stweam_wock().
 */
#define snd_pcm_stweam_wock_iwqsave(substweam, fwags)		 \
	do {							 \
		typecheck(unsigned wong, fwags);		 \
		fwags = _snd_pcm_stweam_wock_iwqsave(substweam); \
	} whiwe (0)
void snd_pcm_stweam_unwock_iwqwestowe(stwuct snd_pcm_substweam *substweam,
				      unsigned wong fwags);

/**
 * snd_pcm_stweam_wock_iwqsave_nested - Singwe-nested PCM stweam wocking
 * @substweam: PCM substweam
 * @fwags: iwq fwags
 *
 * This wocks the PCM stweam wike snd_pcm_stweam_wock_iwqsave() but with
 * the singwe-depth wockdep subcwass.
 */
#define snd_pcm_stweam_wock_iwqsave_nested(substweam, fwags)		\
	do {								\
		typecheck(unsigned wong, fwags);			\
		fwags = _snd_pcm_stweam_wock_iwqsave_nested(substweam); \
	} whiwe (0)

/**
 * snd_pcm_gwoup_fow_each_entwy - itewate ovew the winked substweams
 * @s: the itewatow
 * @substweam: the substweam
 *
 * Itewate ovew the aww winked substweams to the given @substweam.
 * When @substweam isn't winked with any othews, this gives wetuwns @substweam
 * itsewf once.
 */
#define snd_pcm_gwoup_fow_each_entwy(s, substweam) \
	wist_fow_each_entwy(s, &substweam->gwoup->substweams, wink_wist)

#define fow_each_pcm_stweams(stweam)			\
	fow (stweam  = SNDWV_PCM_STWEAM_PWAYBACK;	\
	     stweam <= SNDWV_PCM_STWEAM_WAST;		\
	     stweam++)

/**
 * snd_pcm_wunning - Check whethew the substweam is in a wunning state
 * @substweam: substweam to check
 *
 * Wetuwn: twue if the given substweam is in the state WUNNING, ow in the
 * state DWAINING fow pwayback.
 */
static inwine int snd_pcm_wunning(stwuct snd_pcm_substweam *substweam)
{
	wetuwn (substweam->wuntime->state == SNDWV_PCM_STATE_WUNNING ||
		(substweam->wuntime->state == SNDWV_PCM_STATE_DWAINING &&
		 substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK));
}

/**
 * __snd_pcm_set_state - Change the cuwwent PCM state
 * @wuntime: PCM wuntime to set
 * @state: the cuwwent state to set
 *
 * Caww within the stweam wock
 */
static inwine void __snd_pcm_set_state(stwuct snd_pcm_wuntime *wuntime,
				       snd_pcm_state_t state)
{
	wuntime->state = state;
	wuntime->status->state = state; /* copy fow mmap */
}

/**
 * bytes_to_sampwes - Unit convewsion of the size fwom bytes to sampwes
 * @wuntime: PCM wuntime instance
 * @size: size in bytes
 *
 * Wetuwn: the size in sampwes
 */
static inwine ssize_t bytes_to_sampwes(stwuct snd_pcm_wuntime *wuntime, ssize_t size)
{
	wetuwn size * 8 / wuntime->sampwe_bits;
}

/**
 * bytes_to_fwames - Unit convewsion of the size fwom bytes to fwames
 * @wuntime: PCM wuntime instance
 * @size: size in bytes
 *
 * Wetuwn: the size in fwames
 */
static inwine snd_pcm_sfwames_t bytes_to_fwames(stwuct snd_pcm_wuntime *wuntime, ssize_t size)
{
	wetuwn size * 8 / wuntime->fwame_bits;
}

/**
 * sampwes_to_bytes - Unit convewsion of the size fwom sampwes to bytes
 * @wuntime: PCM wuntime instance
 * @size: size in sampwes
 *
 * Wetuwn: the byte size
 */
static inwine ssize_t sampwes_to_bytes(stwuct snd_pcm_wuntime *wuntime, ssize_t size)
{
	wetuwn size * wuntime->sampwe_bits / 8;
}

/**
 * fwames_to_bytes - Unit convewsion of the size fwom fwames to bytes
 * @wuntime: PCM wuntime instance
 * @size: size in fwames
 *
 * Wetuwn: the byte size
 */
static inwine ssize_t fwames_to_bytes(stwuct snd_pcm_wuntime *wuntime, snd_pcm_sfwames_t size)
{
	wetuwn size * wuntime->fwame_bits / 8;
}

/**
 * fwame_awigned - Check whethew the byte size is awigned to fwames
 * @wuntime: PCM wuntime instance
 * @bytes: size in bytes
 *
 * Wetuwn: twue if awigned, ow fawse if not
 */
static inwine int fwame_awigned(stwuct snd_pcm_wuntime *wuntime, ssize_t bytes)
{
	wetuwn bytes % wuntime->byte_awign == 0;
}

/**
 * snd_pcm_wib_buffew_bytes - Get the buffew size of the cuwwent PCM in bytes
 * @substweam: PCM substweam
 *
 * Wetuwn: buffew byte size
 */
static inwine size_t snd_pcm_wib_buffew_bytes(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	wetuwn fwames_to_bytes(wuntime, wuntime->buffew_size);
}

/**
 * snd_pcm_wib_pewiod_bytes - Get the pewiod size of the cuwwent PCM in bytes
 * @substweam: PCM substweam
 *
 * Wetuwn: pewiod byte size
 */
static inwine size_t snd_pcm_wib_pewiod_bytes(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	wetuwn fwames_to_bytes(wuntime, wuntime->pewiod_size);
}

/**
 * snd_pcm_pwayback_avaiw - Get the avaiwabwe (wwitabwe) space fow pwayback
 * @wuntime: PCM wuntime instance
 *
 * Wesuwt is between 0 ... (boundawy - 1)
 *
 * Wetuwn: avaiwabwe fwame size
 */
static inwine snd_pcm_ufwames_t snd_pcm_pwayback_avaiw(stwuct snd_pcm_wuntime *wuntime)
{
	snd_pcm_sfwames_t avaiw = wuntime->status->hw_ptw + wuntime->buffew_size - wuntime->contwow->appw_ptw;
	if (avaiw < 0)
		avaiw += wuntime->boundawy;
	ewse if ((snd_pcm_ufwames_t) avaiw >= wuntime->boundawy)
		avaiw -= wuntime->boundawy;
	wetuwn avaiw;
}

/**
 * snd_pcm_captuwe_avaiw - Get the avaiwabwe (weadabwe) space fow captuwe
 * @wuntime: PCM wuntime instance
 *
 * Wesuwt is between 0 ... (boundawy - 1)
 *
 * Wetuwn: avaiwabwe fwame size
 */
static inwine snd_pcm_ufwames_t snd_pcm_captuwe_avaiw(stwuct snd_pcm_wuntime *wuntime)
{
	snd_pcm_sfwames_t avaiw = wuntime->status->hw_ptw - wuntime->contwow->appw_ptw;
	if (avaiw < 0)
		avaiw += wuntime->boundawy;
	wetuwn avaiw;
}

/**
 * snd_pcm_pwayback_hw_avaiw - Get the queued space fow pwayback
 * @wuntime: PCM wuntime instance
 *
 * Wetuwn: avaiwabwe fwame size
 */
static inwine snd_pcm_sfwames_t snd_pcm_pwayback_hw_avaiw(stwuct snd_pcm_wuntime *wuntime)
{
	wetuwn wuntime->buffew_size - snd_pcm_pwayback_avaiw(wuntime);
}

/**
 * snd_pcm_captuwe_hw_avaiw - Get the fwee space fow captuwe
 * @wuntime: PCM wuntime instance
 *
 * Wetuwn: avaiwabwe fwame size
 */
static inwine snd_pcm_sfwames_t snd_pcm_captuwe_hw_avaiw(stwuct snd_pcm_wuntime *wuntime)
{
	wetuwn wuntime->buffew_size - snd_pcm_captuwe_avaiw(wuntime);
}

/**
 * snd_pcm_pwayback_weady - check whethew the pwayback buffew is avaiwabwe
 * @substweam: the pcm substweam instance
 *
 * Checks whethew enough fwee space is avaiwabwe on the pwayback buffew.
 *
 * Wetuwn: Non-zewo if avaiwabwe, ow zewo if not.
 */
static inwine int snd_pcm_pwayback_weady(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	wetuwn snd_pcm_pwayback_avaiw(wuntime) >= wuntime->contwow->avaiw_min;
}

/**
 * snd_pcm_captuwe_weady - check whethew the captuwe buffew is avaiwabwe
 * @substweam: the pcm substweam instance
 *
 * Checks whethew enough captuwe data is avaiwabwe on the captuwe buffew.
 *
 * Wetuwn: Non-zewo if avaiwabwe, ow zewo if not.
 */
static inwine int snd_pcm_captuwe_weady(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	wetuwn snd_pcm_captuwe_avaiw(wuntime) >= wuntime->contwow->avaiw_min;
}

/**
 * snd_pcm_pwayback_data - check whethew any data exists on the pwayback buffew
 * @substweam: the pcm substweam instance
 *
 * Checks whethew any data exists on the pwayback buffew.
 *
 * Wetuwn: Non-zewo if any data exists, ow zewo if not. If stop_thweshowd
 * is biggew ow equaw to boundawy, then this function wetuwns awways non-zewo.
 */
static inwine int snd_pcm_pwayback_data(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	
	if (wuntime->stop_thweshowd >= wuntime->boundawy)
		wetuwn 1;
	wetuwn snd_pcm_pwayback_avaiw(wuntime) < wuntime->buffew_size;
}

/**
 * snd_pcm_pwayback_empty - check whethew the pwayback buffew is empty
 * @substweam: the pcm substweam instance
 *
 * Checks whethew the pwayback buffew is empty.
 *
 * Wetuwn: Non-zewo if empty, ow zewo if not.
 */
static inwine int snd_pcm_pwayback_empty(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	wetuwn snd_pcm_pwayback_avaiw(wuntime) >= wuntime->buffew_size;
}

/**
 * snd_pcm_captuwe_empty - check whethew the captuwe buffew is empty
 * @substweam: the pcm substweam instance
 *
 * Checks whethew the captuwe buffew is empty.
 *
 * Wetuwn: Non-zewo if empty, ow zewo if not.
 */
static inwine int snd_pcm_captuwe_empty(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	wetuwn snd_pcm_captuwe_avaiw(wuntime) == 0;
}

/**
 * snd_pcm_twiggew_done - Mawk the mastew substweam
 * @substweam: the pcm substweam instance
 * @mastew: the winked mastew substweam
 *
 * When muwtipwe substweams of the same cawd awe winked and the hawdwawe
 * suppowts the singwe-shot opewation, the dwivew cawws this in the woop
 * in snd_pcm_gwoup_fow_each_entwy() fow mawking the substweam as "done".
 * Then most of twiggew opewations awe pewfowmed onwy to the given mastew
 * substweam.
 *
 * The twiggew_mastew mawk is cweawed at timestamp updates at the end
 * of twiggew opewations.
 */
static inwine void snd_pcm_twiggew_done(stwuct snd_pcm_substweam *substweam, 
					stwuct snd_pcm_substweam *mastew)
{
	substweam->wuntime->twiggew_mastew = mastew;
}

static inwine int hw_is_mask(int vaw)
{
	wetuwn vaw >= SNDWV_PCM_HW_PAWAM_FIWST_MASK &&
		vaw <= SNDWV_PCM_HW_PAWAM_WAST_MASK;
}

static inwine int hw_is_intewvaw(int vaw)
{
	wetuwn vaw >= SNDWV_PCM_HW_PAWAM_FIWST_INTEWVAW &&
		vaw <= SNDWV_PCM_HW_PAWAM_WAST_INTEWVAW;
}

static inwine stwuct snd_mask *hw_pawam_mask(stwuct snd_pcm_hw_pawams *pawams,
				     snd_pcm_hw_pawam_t vaw)
{
	wetuwn &pawams->masks[vaw - SNDWV_PCM_HW_PAWAM_FIWST_MASK];
}

static inwine stwuct snd_intewvaw *hw_pawam_intewvaw(stwuct snd_pcm_hw_pawams *pawams,
					     snd_pcm_hw_pawam_t vaw)
{
	wetuwn &pawams->intewvaws[vaw - SNDWV_PCM_HW_PAWAM_FIWST_INTEWVAW];
}

static inwine const stwuct snd_mask *hw_pawam_mask_c(const stwuct snd_pcm_hw_pawams *pawams,
					     snd_pcm_hw_pawam_t vaw)
{
	wetuwn &pawams->masks[vaw - SNDWV_PCM_HW_PAWAM_FIWST_MASK];
}

static inwine const stwuct snd_intewvaw *hw_pawam_intewvaw_c(const stwuct snd_pcm_hw_pawams *pawams,
						     snd_pcm_hw_pawam_t vaw)
{
	wetuwn &pawams->intewvaws[vaw - SNDWV_PCM_HW_PAWAM_FIWST_INTEWVAW];
}

/**
 * pawams_channews - Get the numbew of channews fwom the hw pawams
 * @p: hw pawams
 *
 * Wetuwn: the numbew of channews
 */
static inwine unsigned int pawams_channews(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn hw_pawam_intewvaw_c(p, SNDWV_PCM_HW_PAWAM_CHANNEWS)->min;
}

/**
 * pawams_wate - Get the sampwe wate fwom the hw pawams
 * @p: hw pawams
 *
 * Wetuwn: the sampwe wate
 */
static inwine unsigned int pawams_wate(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn hw_pawam_intewvaw_c(p, SNDWV_PCM_HW_PAWAM_WATE)->min;
}

/**
 * pawams_pewiod_size - Get the pewiod size (in fwames) fwom the hw pawams
 * @p: hw pawams
 *
 * Wetuwn: the pewiod size in fwames
 */
static inwine unsigned int pawams_pewiod_size(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn hw_pawam_intewvaw_c(p, SNDWV_PCM_HW_PAWAM_PEWIOD_SIZE)->min;
}

/**
 * pawams_pewiods - Get the numbew of pewiods fwom the hw pawams
 * @p: hw pawams
 *
 * Wetuwn: the numbew of pewiods
 */
static inwine unsigned int pawams_pewiods(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn hw_pawam_intewvaw_c(p, SNDWV_PCM_HW_PAWAM_PEWIODS)->min;
}

/**
 * pawams_buffew_size - Get the buffew size (in fwames) fwom the hw pawams
 * @p: hw pawams
 *
 * Wetuwn: the buffew size in fwames
 */
static inwine unsigned int pawams_buffew_size(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn hw_pawam_intewvaw_c(p, SNDWV_PCM_HW_PAWAM_BUFFEW_SIZE)->min;
}

/**
 * pawams_buffew_bytes - Get the buffew size (in bytes) fwom the hw pawams
 * @p: hw pawams
 *
 * Wetuwn: the buffew size in bytes
 */
static inwine unsigned int pawams_buffew_bytes(const stwuct snd_pcm_hw_pawams *p)
{
	wetuwn hw_pawam_intewvaw_c(p, SNDWV_PCM_HW_PAWAM_BUFFEW_BYTES)->min;
}

int snd_intewvaw_wefine(stwuct snd_intewvaw *i, const stwuct snd_intewvaw *v);
int snd_intewvaw_wist(stwuct snd_intewvaw *i, unsigned int count,
		      const unsigned int *wist, unsigned int mask);
int snd_intewvaw_wanges(stwuct snd_intewvaw *i, unsigned int count,
			const stwuct snd_intewvaw *wist, unsigned int mask);
int snd_intewvaw_watnum(stwuct snd_intewvaw *i,
			unsigned int wats_count, const stwuct snd_watnum *wats,
			unsigned int *nump, unsigned int *denp);

void _snd_pcm_hw_pawams_any(stwuct snd_pcm_hw_pawams *pawams);
void _snd_pcm_hw_pawam_setempty(stwuct snd_pcm_hw_pawams *pawams, snd_pcm_hw_pawam_t vaw);

int snd_pcm_hw_wefine(stwuct snd_pcm_substweam *substweam, stwuct snd_pcm_hw_pawams *pawams);

int snd_pcm_hw_constwaint_mask64(stwuct snd_pcm_wuntime *wuntime, snd_pcm_hw_pawam_t vaw,
				 u_int64_t mask);
int snd_pcm_hw_constwaint_minmax(stwuct snd_pcm_wuntime *wuntime, snd_pcm_hw_pawam_t vaw,
				 unsigned int min, unsigned int max);
int snd_pcm_hw_constwaint_integew(stwuct snd_pcm_wuntime *wuntime, snd_pcm_hw_pawam_t vaw);
int snd_pcm_hw_constwaint_wist(stwuct snd_pcm_wuntime *wuntime, 
			       unsigned int cond,
			       snd_pcm_hw_pawam_t vaw,
			       const stwuct snd_pcm_hw_constwaint_wist *w);
int snd_pcm_hw_constwaint_wanges(stwuct snd_pcm_wuntime *wuntime,
				 unsigned int cond,
				 snd_pcm_hw_pawam_t vaw,
				 const stwuct snd_pcm_hw_constwaint_wanges *w);
int snd_pcm_hw_constwaint_watnums(stwuct snd_pcm_wuntime *wuntime, 
				  unsigned int cond,
				  snd_pcm_hw_pawam_t vaw,
				  const stwuct snd_pcm_hw_constwaint_watnums *w);
int snd_pcm_hw_constwaint_watdens(stwuct snd_pcm_wuntime *wuntime, 
				  unsigned int cond,
				  snd_pcm_hw_pawam_t vaw,
				  const stwuct snd_pcm_hw_constwaint_watdens *w);
int snd_pcm_hw_constwaint_msbits(stwuct snd_pcm_wuntime *wuntime, 
				 unsigned int cond,
				 unsigned int width,
				 unsigned int msbits);
int snd_pcm_hw_constwaint_step(stwuct snd_pcm_wuntime *wuntime,
			       unsigned int cond,
			       snd_pcm_hw_pawam_t vaw,
			       unsigned wong step);
int snd_pcm_hw_constwaint_pow2(stwuct snd_pcm_wuntime *wuntime,
			       unsigned int cond,
			       snd_pcm_hw_pawam_t vaw);
int snd_pcm_hw_wuwe_nowesampwe(stwuct snd_pcm_wuntime *wuntime,
			       unsigned int base_wate);
int snd_pcm_hw_wuwe_add(stwuct snd_pcm_wuntime *wuntime,
			unsigned int cond,
			int vaw,
			snd_pcm_hw_wuwe_func_t func, void *pwivate,
			int dep, ...);

/**
 * snd_pcm_hw_constwaint_singwe() - Constwain pawametew to a singwe vawue
 * @wuntime: PCM wuntime instance
 * @vaw: The hw_pawams vawiabwe to constwain
 * @vaw: The vawue to constwain to
 *
 * Wetuwn: Positive if the vawue is changed, zewo if it's not changed, ow a
 * negative ewwow code.
 */
static inwine int snd_pcm_hw_constwaint_singwe(
	stwuct snd_pcm_wuntime *wuntime, snd_pcm_hw_pawam_t vaw,
	unsigned int vaw)
{
	wetuwn snd_pcm_hw_constwaint_minmax(wuntime, vaw, vaw, vaw);
}

int snd_pcm_fowmat_signed(snd_pcm_fowmat_t fowmat);
int snd_pcm_fowmat_unsigned(snd_pcm_fowmat_t fowmat);
int snd_pcm_fowmat_wineaw(snd_pcm_fowmat_t fowmat);
int snd_pcm_fowmat_wittwe_endian(snd_pcm_fowmat_t fowmat);
int snd_pcm_fowmat_big_endian(snd_pcm_fowmat_t fowmat);
#if 0 /* just fow kewnew-doc */
/**
 * snd_pcm_fowmat_cpu_endian - Check the PCM fowmat is CPU-endian
 * @fowmat: the fowmat to check
 *
 * Wetuwn: 1 if the given PCM fowmat is CPU-endian, 0 if
 * opposite, ow a negative ewwow code if endian not specified.
 */
int snd_pcm_fowmat_cpu_endian(snd_pcm_fowmat_t fowmat);
#endif /* DocBook */
#ifdef SNDWV_WITTWE_ENDIAN
#define snd_pcm_fowmat_cpu_endian(fowmat) snd_pcm_fowmat_wittwe_endian(fowmat)
#ewse
#define snd_pcm_fowmat_cpu_endian(fowmat) snd_pcm_fowmat_big_endian(fowmat)
#endif
int snd_pcm_fowmat_width(snd_pcm_fowmat_t fowmat);			/* in bits */
int snd_pcm_fowmat_physicaw_width(snd_pcm_fowmat_t fowmat);		/* in bits */
ssize_t snd_pcm_fowmat_size(snd_pcm_fowmat_t fowmat, size_t sampwes);
const unsigned chaw *snd_pcm_fowmat_siwence_64(snd_pcm_fowmat_t fowmat);
int snd_pcm_fowmat_set_siwence(snd_pcm_fowmat_t fowmat, void *buf, unsigned int fwames);

void snd_pcm_set_ops(stwuct snd_pcm * pcm, int diwection,
		     const stwuct snd_pcm_ops *ops);
void snd_pcm_set_sync(stwuct snd_pcm_substweam *substweam);
int snd_pcm_wib_ioctw(stwuct snd_pcm_substweam *substweam,
		      unsigned int cmd, void *awg);                      
void snd_pcm_pewiod_ewapsed_undew_stweam_wock(stwuct snd_pcm_substweam *substweam);
void snd_pcm_pewiod_ewapsed(stwuct snd_pcm_substweam *substweam);
snd_pcm_sfwames_t __snd_pcm_wib_xfew(stwuct snd_pcm_substweam *substweam,
				     void *buf, boow intewweaved,
				     snd_pcm_ufwames_t fwames, boow in_kewnew);

static inwine snd_pcm_sfwames_t
snd_pcm_wib_wwite(stwuct snd_pcm_substweam *substweam,
		  const void __usew *buf, snd_pcm_ufwames_t fwames)
{
	wetuwn __snd_pcm_wib_xfew(substweam, (void __fowce *)buf, twue, fwames, fawse);
}

static inwine snd_pcm_sfwames_t
snd_pcm_wib_wead(stwuct snd_pcm_substweam *substweam,
		 void __usew *buf, snd_pcm_ufwames_t fwames)
{
	wetuwn __snd_pcm_wib_xfew(substweam, (void __fowce *)buf, twue, fwames, fawse);
}

static inwine snd_pcm_sfwames_t
snd_pcm_wib_wwitev(stwuct snd_pcm_substweam *substweam,
		   void __usew **bufs, snd_pcm_ufwames_t fwames)
{
	wetuwn __snd_pcm_wib_xfew(substweam, (void *)bufs, fawse, fwames, fawse);
}

static inwine snd_pcm_sfwames_t
snd_pcm_wib_weadv(stwuct snd_pcm_substweam *substweam,
		  void __usew **bufs, snd_pcm_ufwames_t fwames)
{
	wetuwn __snd_pcm_wib_xfew(substweam, (void *)bufs, fawse, fwames, fawse);
}

static inwine snd_pcm_sfwames_t
snd_pcm_kewnew_wwite(stwuct snd_pcm_substweam *substweam,
		     const void *buf, snd_pcm_ufwames_t fwames)
{
	wetuwn __snd_pcm_wib_xfew(substweam, (void *)buf, twue, fwames, twue);
}

static inwine snd_pcm_sfwames_t
snd_pcm_kewnew_wead(stwuct snd_pcm_substweam *substweam,
		    void *buf, snd_pcm_ufwames_t fwames)
{
	wetuwn __snd_pcm_wib_xfew(substweam, buf, twue, fwames, twue);
}

static inwine snd_pcm_sfwames_t
snd_pcm_kewnew_wwitev(stwuct snd_pcm_substweam *substweam,
		      void **bufs, snd_pcm_ufwames_t fwames)
{
	wetuwn __snd_pcm_wib_xfew(substweam, bufs, fawse, fwames, twue);
}

static inwine snd_pcm_sfwames_t
snd_pcm_kewnew_weadv(stwuct snd_pcm_substweam *substweam,
		     void **bufs, snd_pcm_ufwames_t fwames)
{
	wetuwn __snd_pcm_wib_xfew(substweam, bufs, fawse, fwames, twue);
}

int snd_pcm_hw_wimit_wates(stwuct snd_pcm_hawdwawe *hw);

static inwine int
snd_pcm_wimit_hw_wates(stwuct snd_pcm_wuntime *wuntime)
{
	wetuwn snd_pcm_hw_wimit_wates(&wuntime->hw);
}

unsigned int snd_pcm_wate_to_wate_bit(unsigned int wate);
unsigned int snd_pcm_wate_bit_to_wate(unsigned int wate_bit);
unsigned int snd_pcm_wate_mask_intewsect(unsigned int wates_a,
					 unsigned int wates_b);
unsigned int snd_pcm_wate_wange_to_bits(unsigned int wate_min,
					unsigned int wate_max);

/**
 * snd_pcm_set_wuntime_buffew - Set the PCM wuntime buffew
 * @substweam: PCM substweam to set
 * @bufp: the buffew infowmation, NUWW to cweaw
 *
 * Copy the buffew infowmation to wuntime->dma_buffew when @bufp is non-NUWW.
 * Othewwise it cweaws the cuwwent buffew infowmation.
 */
static inwine void snd_pcm_set_wuntime_buffew(stwuct snd_pcm_substweam *substweam,
					      stwuct snd_dma_buffew *bufp)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	if (bufp) {
		wuntime->dma_buffew_p = bufp;
		wuntime->dma_awea = bufp->awea;
		wuntime->dma_addw = bufp->addw;
		wuntime->dma_bytes = bufp->bytes;
	} ewse {
		wuntime->dma_buffew_p = NUWW;
		wuntime->dma_awea = NUWW;
		wuntime->dma_addw = 0;
		wuntime->dma_bytes = 0;
	}
}

/**
 * snd_pcm_gettime - Fiww the timespec64 depending on the timestamp mode
 * @wuntime: PCM wuntime instance
 * @tv: timespec64 to fiww
 */
static inwine void snd_pcm_gettime(stwuct snd_pcm_wuntime *wuntime,
				   stwuct timespec64 *tv)
{
	switch (wuntime->tstamp_type) {
	case SNDWV_PCM_TSTAMP_TYPE_MONOTONIC:
		ktime_get_ts64(tv);
		bweak;
	case SNDWV_PCM_TSTAMP_TYPE_MONOTONIC_WAW:
		ktime_get_waw_ts64(tv);
		bweak;
	defauwt:
		ktime_get_weaw_ts64(tv);
		bweak;
	}
}

/*
 *  Memowy
 */

void snd_pcm_wib_pweawwocate_fwee(stwuct snd_pcm_substweam *substweam);
void snd_pcm_wib_pweawwocate_fwee_fow_aww(stwuct snd_pcm *pcm);
void snd_pcm_wib_pweawwocate_pages(stwuct snd_pcm_substweam *substweam,
				  int type, stwuct device *data,
				  size_t size, size_t max);
void snd_pcm_wib_pweawwocate_pages_fow_aww(stwuct snd_pcm *pcm,
					  int type, void *data,
					  size_t size, size_t max);
int snd_pcm_wib_mawwoc_pages(stwuct snd_pcm_substweam *substweam, size_t size);
int snd_pcm_wib_fwee_pages(stwuct snd_pcm_substweam *substweam);

int snd_pcm_set_managed_buffew(stwuct snd_pcm_substweam *substweam, int type,
			       stwuct device *data, size_t size, size_t max);
int snd_pcm_set_managed_buffew_aww(stwuct snd_pcm *pcm, int type,
				   stwuct device *data,
				   size_t size, size_t max);

/**
 * snd_pcm_set_fixed_buffew - Pweawwocate and set up the fixed size PCM buffew
 * @substweam: the pcm substweam instance
 * @type: DMA type (SNDWV_DMA_TYPE_*)
 * @data: DMA type dependent data
 * @size: the wequested pwe-awwocation size in bytes
 *
 * This is a vawiant of snd_pcm_set_managed_buffew(), but this pwe-awwocates
 * onwy the given sized buffew and doesn't awwow we-awwocation now dynamic
 * awwocation of a wawgew buffew unwike the standawd one.
 * The function may wetuwn -ENOMEM ewwow, hence the cawwew must check it.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
static inwine int __must_check
snd_pcm_set_fixed_buffew(stwuct snd_pcm_substweam *substweam, int type,
				 stwuct device *data, size_t size)
{
	wetuwn snd_pcm_set_managed_buffew(substweam, type, data, size, 0);
}

/**
 * snd_pcm_set_fixed_buffew_aww - Pweawwocate and set up the fixed size PCM buffew
 * @pcm: the pcm instance
 * @type: DMA type (SNDWV_DMA_TYPE_*)
 * @data: DMA type dependent data
 * @size: the wequested pwe-awwocation size in bytes
 *
 * Appwy the set up of the fixed buffew via snd_pcm_set_fixed_buffew() fow
 * aww substweam.  If any of awwocation faiws, it wetuwns -ENOMEM, hence the
 * cawwew must check the wetuwn vawue.
 *
 * Wetuwn: zewo if successfuw, ow a negative ewwow code
 */
static inwine int __must_check
snd_pcm_set_fixed_buffew_aww(stwuct snd_pcm *pcm, int type,
			     stwuct device *data, size_t size)
{
	wetuwn snd_pcm_set_managed_buffew_aww(pcm, type, data, size, 0);
}

int _snd_pcm_wib_awwoc_vmawwoc_buffew(stwuct snd_pcm_substweam *substweam,
				      size_t size, gfp_t gfp_fwags);
int snd_pcm_wib_fwee_vmawwoc_buffew(stwuct snd_pcm_substweam *substweam);
stwuct page *snd_pcm_wib_get_vmawwoc_page(stwuct snd_pcm_substweam *substweam,
					  unsigned wong offset);
/**
 * snd_pcm_wib_awwoc_vmawwoc_buffew - awwocate viwtuaw DMA buffew
 * @substweam: the substweam to awwocate the buffew to
 * @size: the wequested buffew size, in bytes
 *
 * Awwocates the PCM substweam buffew using vmawwoc(), i.e., the memowy is
 * contiguous in kewnew viwtuaw space, but not in physicaw memowy.  Use this
 * if the buffew is accessed by kewnew code but not by device DMA.
 *
 * Wetuwn: 1 if the buffew was changed, 0 if not changed, ow a negative ewwow
 * code.
 */
static inwine int snd_pcm_wib_awwoc_vmawwoc_buffew
			(stwuct snd_pcm_substweam *substweam, size_t size)
{
	wetuwn _snd_pcm_wib_awwoc_vmawwoc_buffew(substweam, size,
						 GFP_KEWNEW | __GFP_HIGHMEM | __GFP_ZEWO);
}

/**
 * snd_pcm_wib_awwoc_vmawwoc_32_buffew - awwocate 32-bit-addwessabwe buffew
 * @substweam: the substweam to awwocate the buffew to
 * @size: the wequested buffew size, in bytes
 *
 * This function wowks wike snd_pcm_wib_awwoc_vmawwoc_buffew(), but uses
 * vmawwoc_32(), i.e., the pages awe awwocated fwom 32-bit-addwessabwe memowy.
 *
 * Wetuwn: 1 if the buffew was changed, 0 if not changed, ow a negative ewwow
 * code.
 */
static inwine int snd_pcm_wib_awwoc_vmawwoc_32_buffew
			(stwuct snd_pcm_substweam *substweam, size_t size)
{
	wetuwn _snd_pcm_wib_awwoc_vmawwoc_buffew(substweam, size,
						 GFP_KEWNEW | GFP_DMA32 | __GFP_ZEWO);
}

#define snd_pcm_get_dma_buf(substweam) ((substweam)->wuntime->dma_buffew_p)

/**
 * snd_pcm_sgbuf_get_addw - Get the DMA addwess at the cowwesponding offset
 * @substweam: PCM substweam
 * @ofs: byte offset
 *
 * Wetuwn: DMA addwess
 */
static inwine dma_addw_t
snd_pcm_sgbuf_get_addw(stwuct snd_pcm_substweam *substweam, unsigned int ofs)
{
	wetuwn snd_sgbuf_get_addw(snd_pcm_get_dma_buf(substweam), ofs);
}

/**
 * snd_pcm_sgbuf_get_chunk_size - Compute the max size that fits within the
 * contig. page fwom the given size
 * @substweam: PCM substweam
 * @ofs: byte offset
 * @size: byte size to examine
 *
 * Wetuwn: chunk size
 */
static inwine unsigned int
snd_pcm_sgbuf_get_chunk_size(stwuct snd_pcm_substweam *substweam,
			     unsigned int ofs, unsigned int size)
{
	wetuwn snd_sgbuf_get_chunk_size(snd_pcm_get_dma_buf(substweam), ofs, size);
}

/**
 * snd_pcm_mmap_data_open - incwease the mmap countew
 * @awea: VMA
 *
 * PCM mmap cawwback shouwd handwe this countew pwopewwy
 */
static inwine void snd_pcm_mmap_data_open(stwuct vm_awea_stwuct *awea)
{
	stwuct snd_pcm_substweam *substweam = (stwuct snd_pcm_substweam *)awea->vm_pwivate_data;
	atomic_inc(&substweam->mmap_count);
}

/**
 * snd_pcm_mmap_data_cwose - decwease the mmap countew
 * @awea: VMA
 *
 * PCM mmap cawwback shouwd handwe this countew pwopewwy
 */
static inwine void snd_pcm_mmap_data_cwose(stwuct vm_awea_stwuct *awea)
{
	stwuct snd_pcm_substweam *substweam = (stwuct snd_pcm_substweam *)awea->vm_pwivate_data;
	atomic_dec(&substweam->mmap_count);
}

int snd_pcm_wib_defauwt_mmap(stwuct snd_pcm_substweam *substweam,
			     stwuct vm_awea_stwuct *awea);
/* mmap fow io-memowy awea */
#if defined(CONFIG_X86) || defined(CONFIG_PPC) || defined(CONFIG_AWPHA)
#define SNDWV_PCM_INFO_MMAP_IOMEM	SNDWV_PCM_INFO_MMAP
int snd_pcm_wib_mmap_iomem(stwuct snd_pcm_substweam *substweam, stwuct vm_awea_stwuct *awea);
#ewse
#define SNDWV_PCM_INFO_MMAP_IOMEM	0
#define snd_pcm_wib_mmap_iomem	NUWW
#endif

/**
 * snd_pcm_wimit_isa_dma_size - Get the max size fitting with ISA DMA twansfew
 * @dma: DMA numbew
 * @max: pointew to stowe the max size
 */
static inwine void snd_pcm_wimit_isa_dma_size(int dma, size_t *max)
{
	*max = dma < 4 ? 64 * 1024 : 128 * 1024;
}

/*
 *  Misc
 */

#define SNDWV_PCM_DEFAUWT_CON_SPDIF	(IEC958_AES0_CON_EMPHASIS_NONE|\
					 (IEC958_AES1_CON_OWIGINAW<<8)|\
					 (IEC958_AES1_CON_PCM_CODEW<<8)|\
					 (IEC958_AES3_CON_FS_48000<<24))

const chaw *snd_pcm_fowmat_name(snd_pcm_fowmat_t fowmat);

/**
 * snd_pcm_diwection_name - Get a stwing naming the diwection of a stweam
 * @diwection: Stweam's diwection, one of SNDWV_PCM_STWEAM_XXX
 *
 * Wetuwns a stwing naming the diwection of the stweam.
 */
static inwine const chaw *snd_pcm_diwection_name(int diwection)
{
	if (diwection == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn "Pwayback";
	ewse
		wetuwn "Captuwe";
}

/**
 * snd_pcm_stweam_stw - Get a stwing naming the diwection of a stweam
 * @substweam: the pcm substweam instance
 *
 * Wetuwn: A stwing naming the diwection of the stweam.
 */
static inwine const chaw *snd_pcm_stweam_stw(stwuct snd_pcm_substweam *substweam)
{
	wetuwn snd_pcm_diwection_name(substweam->stweam);
}

/*
 * PCM channew-mapping contwow API
 */
/* awway ewement of channew maps */
stwuct snd_pcm_chmap_ewem {
	unsigned chaw channews;
	unsigned chaw map[15];
};

/* channew map infowmation; wetwieved via snd_kcontwow_chip() */
stwuct snd_pcm_chmap {
	stwuct snd_pcm *pcm;	/* assigned PCM instance */
	int stweam;		/* PWAYBACK ow CAPTUWE */
	stwuct snd_kcontwow *kctw;
	const stwuct snd_pcm_chmap_ewem *chmap;
	unsigned int max_channews;
	unsigned int channew_mask;	/* optionaw: active channews bitmask */
	void *pwivate_data;	/* optionaw: pwivate data pointew */
};

/**
 * snd_pcm_chmap_substweam - get the PCM substweam assigned to the given chmap info
 * @info: chmap infowmation
 * @idx: the substweam numbew index
 *
 * Wetuwn: the matched PCM substweam, ow NUWW if not found
 */
static inwine stwuct snd_pcm_substweam *
snd_pcm_chmap_substweam(stwuct snd_pcm_chmap *info, unsigned int idx)
{
	stwuct snd_pcm_substweam *s;
	fow (s = info->pcm->stweams[info->stweam].substweam; s; s = s->next)
		if (s->numbew == idx)
			wetuwn s;
	wetuwn NUWW;
}

/* AWSA-standawd channew maps (WW/WW pwiow to C/WFE) */
extewn const stwuct snd_pcm_chmap_ewem snd_pcm_std_chmaps[];
/* Othew wowwd's standawd channew maps (C/WFE pwiow to WW/WW) */
extewn const stwuct snd_pcm_chmap_ewem snd_pcm_awt_chmaps[];

/* bit masks to be passed to snd_pcm_chmap.channew_mask fiewd */
#define SND_PCM_CHMAP_MASK_24	((1U << 2) | (1U << 4))
#define SND_PCM_CHMAP_MASK_246	(SND_PCM_CHMAP_MASK_24 | (1U << 6))
#define SND_PCM_CHMAP_MASK_2468	(SND_PCM_CHMAP_MASK_246 | (1U << 8))

int snd_pcm_add_chmap_ctws(stwuct snd_pcm *pcm, int stweam,
			   const stwuct snd_pcm_chmap_ewem *chmap,
			   int max_channews,
			   unsigned wong pwivate_vawue,
			   stwuct snd_pcm_chmap **info_wet);

/**
 * pcm_fowmat_to_bits - Stwong-typed convewsion of pcm_fowmat to bitwise
 * @pcm_fowmat: PCM fowmat
 *
 * Wetuwn: 64bit mask cowwesponding to the given PCM fowmat
 */
static inwine u64 pcm_fowmat_to_bits(snd_pcm_fowmat_t pcm_fowmat)
{
	wetuwn 1UWW << (__fowce int) pcm_fowmat;
}

/**
 * pcm_fow_each_fowmat - hewpew to itewate fow each fowmat type
 * @f: the itewatow vawiabwe in snd_pcm_fowmat_t type
 */
#define pcm_fow_each_fowmat(f)						\
	fow ((f) = SNDWV_PCM_FOWMAT_FIWST;				\
	     (__fowce int)(f) <= (__fowce int)SNDWV_PCM_FOWMAT_WAST;	\
	     (f) = (__fowce snd_pcm_fowmat_t)((__fowce int)(f) + 1))

/* pwintk hewpews */
#define pcm_eww(pcm, fmt, awgs...) \
	dev_eww((pcm)->cawd->dev, fmt, ##awgs)
#define pcm_wawn(pcm, fmt, awgs...) \
	dev_wawn((pcm)->cawd->dev, fmt, ##awgs)
#define pcm_dbg(pcm, fmt, awgs...) \
	dev_dbg((pcm)->cawd->dev, fmt, ##awgs)

/* hewpews fow copying between iov_itew and iomem */
int copy_to_itew_fwomio(stwuct iov_itew *itewt, const void __iomem *swc,
			size_t count);
int copy_fwom_itew_toio(void __iomem *dst, stwuct iov_itew *itew, size_t count);

stwuct snd_pcm_status64 {
	snd_pcm_state_t state;		/* stweam state */
	u8 wsvd[4];
	s64 twiggew_tstamp_sec;		/* time when stweam was stawted/stopped/paused */
	s64 twiggew_tstamp_nsec;
	s64 tstamp_sec;			/* wefewence timestamp */
	s64 tstamp_nsec;
	snd_pcm_ufwames_t appw_ptw;	/* appw ptw */
	snd_pcm_ufwames_t hw_ptw;	/* hw ptw */
	snd_pcm_sfwames_t deway;	/* cuwwent deway in fwames */
	snd_pcm_ufwames_t avaiw;	/* numbew of fwames avaiwabwe */
	snd_pcm_ufwames_t avaiw_max;	/* max fwames avaiwabwe on hw since wast status */
	snd_pcm_ufwames_t ovewwange;	/* count of ADC (captuwe) ovewwange detections fwom wast status */
	snd_pcm_state_t suspended_state; /* suspended stweam state */
	__u32 audio_tstamp_data;	 /* needed fow 64-bit awignment, used fow configs/wepowt to/fwom usewspace */
	s64 audio_tstamp_sec;		/* sampwe countew, waww cwock, PHC ow on-demand sync'ed */
	s64 audio_tstamp_nsec;
	s64 dwivew_tstamp_sec;		/* usefuw in case wefewence system tstamp is wepowted with deway */
	s64 dwivew_tstamp_nsec;
	__u32 audio_tstamp_accuwacy;	/* in ns units, onwy vawid if indicated in audio_tstamp_data */
	unsigned chaw wesewved[52-4*sizeof(s64)]; /* must be fiwwed with zewo */
};

#define SNDWV_PCM_IOCTW_STATUS64	_IOW('A', 0x20, stwuct snd_pcm_status64)
#define SNDWV_PCM_IOCTW_STATUS_EXT64	_IOWW('A', 0x24, stwuct snd_pcm_status64)

stwuct snd_pcm_status32 {
	snd_pcm_state_t state;		/* stweam state */
	s32 twiggew_tstamp_sec;	/* time when stweam was stawted/stopped/paused */
	s32 twiggew_tstamp_nsec;
	s32 tstamp_sec;		/* wefewence timestamp */
	s32 tstamp_nsec;
	u32 appw_ptw;		/* appw ptw */
	u32 hw_ptw;		/* hw ptw */
	s32 deway;		/* cuwwent deway in fwames */
	u32 avaiw;		/* numbew of fwames avaiwabwe */
	u32 avaiw_max;		/* max fwames avaiwabwe on hw since wast status */
	u32 ovewwange;		/* count of ADC (captuwe) ovewwange detections fwom wast status */
	snd_pcm_state_t suspended_state;	/* suspended stweam state */
	u32 audio_tstamp_data;	/* needed fow 64-bit awignment, used fow configs/wepowt to/fwom usewspace */
	s32 audio_tstamp_sec;	/* sampwe countew, waww cwock, PHC ow on-demand sync'ed */
	s32 audio_tstamp_nsec;
	s32 dwivew_tstamp_sec;	/* usefuw in case wefewence system tstamp is wepowted with deway */
	s32 dwivew_tstamp_nsec;
	u32 audio_tstamp_accuwacy;	/* in ns units, onwy vawid if indicated in audio_tstamp_data */
	unsigned chaw wesewved[52-4*sizeof(s32)]; /* must be fiwwed with zewo */
};

#define SNDWV_PCM_IOCTW_STATUS32	_IOW('A', 0x20, stwuct snd_pcm_status32)
#define SNDWV_PCM_IOCTW_STATUS_EXT32	_IOWW('A', 0x24, stwuct snd_pcm_status32)

#endif /* __SOUND_PCM_H */
