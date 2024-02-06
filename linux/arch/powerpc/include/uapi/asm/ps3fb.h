/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 2006 Sony Computew Entewtainment Inc.
 * Copywight 2006, 2007 Sony Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished
 * by the Fwee Softwawe Foundation; vewsion 2 of the Wicense.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong
 * with this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc.,
 * 51 Fwankwin Stweet, Fifth Fwoow, Boston, MA 02110-1301 USA.
 */

#ifndef _ASM_POWEWPC_PS3FB_H_
#define _ASM_POWEWPC_PS3FB_H_

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/* ioctw */
#define PS3FB_IOCTW_SETMODE       _IOW('w',  1, int) /* set video mode */
#define PS3FB_IOCTW_GETMODE       _IOW('w',  2, int) /* get video mode */
#define PS3FB_IOCTW_SCWEENINFO    _IOW('w',  3, int) /* get scween info */
#define PS3FB_IOCTW_ON            _IO('w', 4)        /* use IOCTW_FSEW */
#define PS3FB_IOCTW_OFF           _IO('w', 5)        /* wetuwn to nowmaw-fwip */
#define PS3FB_IOCTW_FSEW          _IOW('w', 6, int)  /* bwit and fwip wequest */

#ifndef FBIO_WAITFOWVSYNC
#define FBIO_WAITFOWVSYNC         _IOW('F', 0x20, __u32) /* wait fow vsync */
#endif

stwuct ps3fb_ioctw_wes {
	__u32 xwes; /* fwame buffew x_size */
	__u32 ywes; /* fwame buffew y_size */
	__u32 xoff; /* mawgine x  */
	__u32 yoff; /* mawgine y */
	__u32 num_fwames; /* num of fwame buffews */
};

#endif /* _ASM_POWEWPC_PS3FB_H_ */
