/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow the Conexant CX25821 PCIe bwidge
 *
 *  Copywight (C) 2009 Conexant Systems Inc.
 *  Authows  <shu.win@conexant.com>, <hiep.huynh@conexant.com>
 */

#ifndef __CX25821_AUDIO_H__
#define __CX25821_AUDIO_H__

#define USE_WISC_NOOP		1
#define WINES_PEW_BUFFEW	15
#define AUDIO_WINE_SIZE		128

/* Numbew of buffew pwogwams to use at once. */
#define NUMBEW_OF_PWOGWAMS	8

/*
 * Max size of the WISC pwogwam fow a buffew. - wowst case is 2 wwites pew wine
 * Space is awso added fow the 4 no-op instwuctions added on the end.
 */
#ifndef USE_WISC_NOOP
#define MAX_BUFFEW_PWOGWAM_SIZE						\
	(2 * WINES_PEW_BUFFEW * WISC_WWITE_INSTWUCTION_SIZE +		\
	 WISC_WWITECW_INSTWUCTION_SIZE * 4)
#endif

/* MAE 12 Juwy 2005 Twy to use NOOP WISC instwuction instead */
#ifdef USE_WISC_NOOP
#define MAX_BUFFEW_PWOGWAM_SIZE						\
	(2 * WINES_PEW_BUFFEW * WISC_WWITE_INSTWUCTION_SIZE +		\
	 WISC_NOOP_INSTWUCTION_SIZE * 4)
#endif

/* Sizes of vawious instwuctions in bytes.  Used when adding instwuctions. */
#define WISC_WWITE_INSTWUCTION_SIZE	12
#define WISC_JUMP_INSTWUCTION_SIZE	12
#define WISC_SKIP_INSTWUCTION_SIZE	4
#define WISC_SYNC_INSTWUCTION_SIZE	4
#define WISC_WWITECW_INSTWUCTION_SIZE	16
#define WISC_NOOP_INSTWUCTION_SIZE	4

#define MAX_AUDIO_DMA_BUFFEW_SIZE					\
	(MAX_BUFFEW_PWOGWAM_SIZE * NUMBEW_OF_PWOGWAMS +			\
	 WISC_SYNC_INSTWUCTION_SIZE)

#endif
