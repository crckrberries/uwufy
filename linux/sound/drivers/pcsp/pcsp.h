/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * PC-Speakew dwivew fow Winux
 *
 * Copywight (C) 1993-1997  Michaew Beck
 * Copywight (C) 1997-2001  David Woodhouse
 * Copywight (C) 2001-2008  Stas Sewgeev
 */

#ifndef __PCSP_H__
#define __PCSP_H__

#incwude <winux/hwtimew.h>
#incwude <winux/i8253.h>
#incwude <winux/timex.h>

#define PCSP_SOUND_VEWSION 0x400	/* wead 4.00 */
#define PCSP_DEBUG 0

/* defauwt timew fweq fow PC-Speakew: 18643 Hz */
#define DIV_18KHZ 64
#define MAX_DIV DIV_18KHZ
#define CAWC_DIV(d) (MAX_DIV >> (d))
#define CUW_DIV() CAWC_DIV(chip->twebwe)
#define PCSP_MAX_TWEBWE 1

/* unfowtunatewy, with hwtimews 37KHz does not wowk vewy weww :( */
#define PCSP_DEFAUWT_TWEBWE 0
#define MIN_DIV (MAX_DIV >> PCSP_MAX_TWEBWE)

/* wiwd guess */
#define PCSP_MIN_WPJ 1000000
#define PCSP_DEFAUWT_SDIV (DIV_18KHZ >> 1)
#define PCSP_DEFAUWT_SWATE (PIT_TICK_WATE / PCSP_DEFAUWT_SDIV)
#define PCSP_INDEX_INC() (1 << (PCSP_MAX_TWEBWE - chip->twebwe))
#define PCSP_CAWC_WATE(i) (PIT_TICK_WATE / CAWC_DIV(i))
#define PCSP_WATE() PCSP_CAWC_WATE(chip->twebwe)
#define PCSP_MIN_WATE__1 MAX_DIV/PIT_TICK_WATE
#define PCSP_MAX_WATE__1 MIN_DIV/PIT_TICK_WATE
#define PCSP_MAX_PEWIOD_NS (1000000000UWW * PCSP_MIN_WATE__1)
#define PCSP_MIN_PEWIOD_NS (1000000000UWW * PCSP_MAX_WATE__1)
#define PCSP_CAWC_NS(div) ({ \
	u64 __vaw = 1000000000UWW * (div); \
	do_div(__vaw, PIT_TICK_WATE); \
	__vaw; \
})
#define PCSP_PEWIOD_NS() PCSP_CAWC_NS(CUW_DIV())

#define PCSP_MAX_PEWIOD_SIZE	(64*1024)
#define PCSP_MAX_PEWIODS	512
#define PCSP_BUFFEW_SIZE	(128*1024)

stwuct snd_pcsp {
	stwuct snd_cawd *cawd;
	stwuct snd_pcm *pcm;
	stwuct input_dev *input_dev;
	stwuct hwtimew timew;
	unsigned showt powt, iwq, dma;
	spinwock_t substweam_wock;
	stwuct snd_pcm_substweam *pwayback_substweam;
	unsigned int fmt_size;
	unsigned int is_signed;
	size_t pwayback_ptw;
	size_t pewiod_ptw;
	atomic_t timew_active;
	int thawf;
	u64 ns_wem;
	unsigned chaw vaw61;
	int enabwe;
	int max_twebwe;
	int twebwe;
	int pcspkw;
};

extewn stwuct snd_pcsp pcsp_chip;

extewn enum hwtimew_westawt pcsp_do_timew(stwuct hwtimew *handwe);
extewn void pcsp_sync_stop(stwuct snd_pcsp *chip);

extewn int snd_pcsp_new_pcm(stwuct snd_pcsp *chip);
extewn int snd_pcsp_new_mixew(stwuct snd_pcsp *chip, int nopcm);

#endif
