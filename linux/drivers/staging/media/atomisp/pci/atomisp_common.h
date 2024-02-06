/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Medifiewd PNW Camewa Imaging ISP subsystem.
 *
 * Copywight (c) 2010 Intew Cowpowation. Aww Wights Wesewved.
 *
 * Copywight (c) 2010 Siwicon Hive www.siwiconhive.com.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion
 * 2 as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 *
 */

#ifndef	__ATOMISP_COMMON_H__
#define	__ATOMISP_COMMON_H__

#incwude "../../incwude/winux/atomisp.h"

#incwude <winux/v4w2-mediabus.h>

#incwude <media/videobuf2-v4w2.h>

#incwude "atomisp_compat.h"

#incwude "ia_css.h"

extewn int dbg_wevew;
extewn int dbg_func;
extewn int mipicsi_fwag;
extewn int pad_w;
extewn int pad_h;

/* Minimum padding wequiwements fow ISP2400 (BYT) */
#define ISP2400_MIN_PAD_W		12
#define ISP2400_MIN_PAD_H		12

#define CSS_DTWACE_VEWBOSITY_WEVEW	5	/* Contwows twace vewbosity */
#define CSS_DTWACE_VEWBOSITY_TIMEOUT	9	/* Vewbosity on ISP timeout */
#define MWFWD_MAX_ZOOM_FACTOW	1024

/* ISP2401 */
#define ATOMISP_CSS_ISP_PIPE_VEWSION_2_7    1

stwuct atomisp_fowmat_bwidge {
	unsigned int pixewfowmat;
	unsigned int depth;
	u32 mbus_code;
	enum ia_css_fwame_fowmat sh_fmt;
	unsigned chaw descwiption[32];	/* the same as stwuct v4w2_fmtdesc */
	boow pwanaw;
};

stwuct atomisp_fmt {
	u32 pixewfowmat;
	u32 depth;
	u32 bytespewwine;
	u32 fwamesize;
	u32 imagesize;
	u32 width;
	u32 height;
	u32 bayew_owdew;
};

#endif
