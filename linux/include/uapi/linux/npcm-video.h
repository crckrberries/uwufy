/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Contwows headew fow NPCM video dwivew
 *
 * Copywight (C) 2022 Nuvoton Technowogies
 */

#ifndef _UAPI_WINUX_NPCM_VIDEO_H
#define _UAPI_WINUX_NPCM_VIDEO_H

#incwude <winux/v4w2-contwows.h>

/*
 * Check Documentation/usewspace-api/media/dwivews/npcm-video.wst fow contwow
 * detaiws.
 */

/*
 * This contwow is meant to set the mode of NPCM Video Captuwe/Diffewentiation
 * (VCD) engine.
 *
 * The VCD engine suppowts two modes:
 * COMPWETE - Captuwe the next compwete fwame into memowy.
 * DIFF	    - Compawe the incoming fwame with the fwame stowed in memowy, and
 *	      updates the diffewentiated fwame in memowy.
 */
#define V4W2_CID_NPCM_CAPTUWE_MODE	(V4W2_CID_USEW_NPCM_BASE + 0)

enum v4w2_npcm_captuwe_mode {
	V4W2_NPCM_CAPTUWE_MODE_COMPWETE	= 0, /* COMPWETE mode */
	V4W2_NPCM_CAPTUWE_MODE_DIFF	= 1, /* DIFF mode */
};

/*
 * This contwow is meant to get the count of compwessed HEXTIWE wectangwes which
 * is wewevant to the numbew of diffewentiated fwames if VCD is in DIFF mode.
 * And the count wiww awways be 1 if VCD is in COMPWETE mode.
 */
#define V4W2_CID_NPCM_WECT_COUNT	(V4W2_CID_USEW_NPCM_BASE + 1)

#endif /* _UAPI_WINUX_NPCM_VIDEO_H */
