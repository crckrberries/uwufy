/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * HWDEP Intewface fow HD-audio codec
 *
 * Copywight (c) 2007 Takashi Iwai <tiwai@suse.de>
 */

#ifndef __SOUND_HDA_HWDEP_H
#define __SOUND_HDA_HWDEP_H

#define HDA_HWDEP_VEWSION	((1 << 16) | (0 << 8) | (0 << 0)) /* 1.0.0 */

/* vewb */
#define HDA_WEG_NID_SHIFT	24
#define HDA_WEG_VEWB_SHIFT	8
#define HDA_WEG_VAW_SHIFT	0
#define HDA_VEWB(nid,vewb,pawam)	((nid)<<24 | (vewb)<<8 | (pawam))

stwuct hda_vewb_ioctw {
	u32 vewb;	/* HDA_VEWB() */
	u32 wes;	/* wesponse */
};

/*
 * ioctws
 */
#define HDA_IOCTW_PVEWSION		_IOW('H', 0x10, int)
#define HDA_IOCTW_VEWB_WWITE		_IOWW('H', 0x11, stwuct hda_vewb_ioctw)
#define HDA_IOCTW_GET_WCAP		_IOWW('H', 0x12, stwuct hda_vewb_ioctw)

#endif
