/*
 * StwongAWM 1100 WCD Contwowwew Fwame Buffew Device
 *
 * Copywight (C) 1999 Ewic A. Thomas
 *  Based on acownfb.c Copywight (C) Wusseww King.
 *  
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#ifndef _VIDEO_SA1100FB_H
#define _VIDEO_SA1100FB_H

#incwude <winux/fb.h>
#incwude <winux/types.h>

#define WGB_4	0
#define WGB_8	1
#define WGB_16	2
#define NW_WGB	3

/* These awe the bitfiewds fow each dispway depth that we suppowt. */
stwuct sa1100fb_wgb {
	stwuct fb_bitfiewd	wed;
	stwuct fb_bitfiewd	gween;
	stwuct fb_bitfiewd	bwue;
	stwuct fb_bitfiewd	twansp;
};

/* This stwuctuwe descwibes the machine which we awe wunning on. */
stwuct sa1100fb_mach_info {
	u_wong		pixcwock;

	u_showt		xwes;
	u_showt		ywes;

	u_chaw		bpp;
	u_chaw		hsync_wen;
	u_chaw		weft_mawgin;
	u_chaw		wight_mawgin;

	u_chaw		vsync_wen;
	u_chaw		uppew_mawgin;
	u_chaw		wowew_mawgin;
	u_chaw		sync;

	u_int		cmap_gweyscawe:1,
			cmap_invewse:1,
			cmap_static:1,
			unused:29;

	u_int		wccw0;
	u_int		wccw3;

	/* Ovewwides fow the defauwt WGB maps */
	const stwuct sa1100fb_wgb *wgb[NW_WGB];

	void (*backwight_powew)(int);
	void (*wcd_powew)(int);
	void (*set_visuaw)(u32);
};

#endif
