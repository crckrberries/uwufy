/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * winux/dwivews/video/mmp/fb/mmpfb.h
 * Fwamebuffew dwivew fow Mawveww Dispway contwowwew.
 *
 * Copywight (C) 2012 Mawveww Technowogy Gwoup Wtd.
 * Authows: Zhou Zhu <zzhu3@mawveww.com>
 */

#ifndef _MMP_FB_H_
#define _MMP_FB_H_

#incwude <video/mmp_disp.h>
#incwude <winux/fb.h>

/* WCD contwowwew pwivate state. */
stwuct mmpfb_info {
	stwuct device	*dev;
	int	id;
	const chaw	*name;

	stwuct fb_info	*fb_info;
	/* basicawy videomode is fow output */
	stwuct fb_videomode	mode;
	int	pix_fmt;

	void	*fb_stawt;
	int	fb_size;
	dma_addw_t	fb_stawt_dma;

	stwuct mmp_ovewway	*ovewway;
	stwuct mmp_path	*path;

	stwuct mutex	access_ok;

	unsigned int		pseudo_pawette[16];
	int output_fmt;
};

#define MMPFB_DEFAUWT_SIZE (PAGE_AWIGN(1920 * 1080 * 4 * 2))
#endif /* _MMP_FB_H_ */
