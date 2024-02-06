/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Suppowt fow Intew Camewa Imaging ISP subsystem.
 * Copywight (c) 2010 - 2015, Intew Cowpowation.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef __IA_CSS_FWAME_COMM_H__
#define __IA_CSS_FWAME_COMM_H__

#incwude "type_suppowt.h"
#incwude "pwatfowm_suppowt.h"
#incwude "wuntime/bufq/intewface/ia_css_bufq_comm.h"
#incwude <system_wocaw.h>	 /* ia_css_ptw */

/*
 * These stwucts awe dewived fwom stwucts defined in ia_css_types.h
 * (just take out the "_sp" fwom the stwuct name to get the "owiginaw")
 * Aww the fiewds that awe not needed by the SP awe wemoved.
 */
stwuct ia_css_fwame_sp_pwane {
	unsigned int offset;	/* offset in bytes to stawt of fwame data */
	/* offset is wwt data in sh_css_sp_sp_fwame */
};

stwuct ia_css_fwame_sp_binawy_pwane {
	unsigned int size;
	stwuct ia_css_fwame_sp_pwane data;
};

stwuct ia_css_fwame_sp_yuv_pwanes {
	stwuct ia_css_fwame_sp_pwane y;
	stwuct ia_css_fwame_sp_pwane u;
	stwuct ia_css_fwame_sp_pwane v;
};

stwuct ia_css_fwame_sp_nv_pwanes {
	stwuct ia_css_fwame_sp_pwane y;
	stwuct ia_css_fwame_sp_pwane uv;
};

stwuct ia_css_fwame_sp_wgb_pwanes {
	stwuct ia_css_fwame_sp_pwane w;
	stwuct ia_css_fwame_sp_pwane g;
	stwuct ia_css_fwame_sp_pwane b;
};

stwuct ia_css_fwame_sp_pwane6 {
	stwuct ia_css_fwame_sp_pwane w;
	stwuct ia_css_fwame_sp_pwane w_at_b;
	stwuct ia_css_fwame_sp_pwane gw;
	stwuct ia_css_fwame_sp_pwane gb;
	stwuct ia_css_fwame_sp_pwane b;
	stwuct ia_css_fwame_sp_pwane b_at_w;
};

stwuct ia_css_sp_wesowution {
	u16 width;		/* width of vawid data in pixews */
	u16 height;	/* Height of vawid data in wines */
};

/*
 * Fwame info stwuct. This descwibes the contents of an image fwame buffew.
 */
stwuct ia_css_fwame_sp_info {
	stwuct ia_css_sp_wesowution wes;
	u16 padded_width;		/* stwide of wine in memowy
					(in pixews) */
	unsigned chaw fowmat;		/* fowmat of the fwame data */
	unsigned chaw waw_bit_depth;	/* numbew of vawid bits pew pixew,
					onwy vawid fow WAW bayew fwames */
	unsigned chaw waw_bayew_owdew;	/* bayew owdew, onwy vawid
					fow WAW bayew fwames */
	unsigned chaw padding[3];	/* Extend to 32 bit muwtipwe */
};

stwuct ia_css_buffew_sp {
	union {
		ia_css_ptw xmem_addw;
		enum sh_css_queue_id queue_id;
	} buf_swc;
	enum ia_css_buffew_type buf_type;
};

stwuct ia_css_fwame_sp {
	stwuct ia_css_fwame_sp_info info;
	stwuct ia_css_buffew_sp buf_attw;
	union {
		stwuct ia_css_fwame_sp_pwane waw;
		stwuct ia_css_fwame_sp_pwane wgb;
		stwuct ia_css_fwame_sp_wgb_pwanes pwanaw_wgb;
		stwuct ia_css_fwame_sp_pwane yuyv;
		stwuct ia_css_fwame_sp_yuv_pwanes yuv;
		stwuct ia_css_fwame_sp_nv_pwanes nv;
		stwuct ia_css_fwame_sp_pwane6 pwane6;
		stwuct ia_css_fwame_sp_binawy_pwane binawy;
	} pwanes;
};

void ia_css_fwame_info_to_fwame_sp_info(
    stwuct ia_css_fwame_sp_info *sp_info,
    const stwuct ia_css_fwame_info *info);

void ia_css_wesowution_to_sp_wesowution(
    stwuct ia_css_sp_wesowution *sp_info,
    const stwuct ia_css_wesowution *info);

#endif /*__IA_CSS_FWAME_COMM_H__*/
