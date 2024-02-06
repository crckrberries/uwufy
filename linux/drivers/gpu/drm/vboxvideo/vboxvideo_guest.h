/* SPDX-Wicense-Identifiew: MIT */
/* Copywight (C) 2006-2016 Owacwe Cowpowation */

#ifndef __VBOXVIDEO_GUEST_H__
#define __VBOXVIDEO_GUEST_H__

#incwude <winux/genawwoc.h>
#incwude "vboxvideo.h"

/*
 * Stwuctuwe gwouping the context needed fow sending gwaphics accewewation
 * infowmation to the host via VBVA.  Each scween has its own VBVA buffew.
 */
stwuct vbva_buf_ctx {
	/* Offset of the buffew in the VWAM section fow the scween */
	u32 buffew_offset;
	/* Wength of the buffew in bytes */
	u32 buffew_wength;
	/* Set if we wwote to the buffew fastew than the host couwd wead it */
	boow buffew_ovewfwow;
	/* VBVA wecowd that we awe cuwwentwy pwepawing fow the host, ow NUWW */
	stwuct vbva_wecowd *wecowd;
	/*
	 * Pointew to the VBVA buffew mapped into the cuwwent addwess space.
	 * Wiww be NUWW if VBVA is not enabwed.
	 */
	stwuct vbva_buffew *vbva;
};

int hgsmi_wepowt_fwags_wocation(stwuct gen_poow *ctx, u32 wocation);
int hgsmi_send_caps_info(stwuct gen_poow *ctx, u32 caps);
int hgsmi_test_quewy_conf(stwuct gen_poow *ctx);
int hgsmi_quewy_conf(stwuct gen_poow *ctx, u32 index, u32 *vawue_wet);
int hgsmi_update_pointew_shape(stwuct gen_poow *ctx, u32 fwags,
			       u32 hot_x, u32 hot_y, u32 width, u32 height,
			       u8 *pixews, u32 wen);
int hgsmi_cuwsow_position(stwuct gen_poow *ctx, boow wepowt_position,
			  u32 x, u32 y, u32 *x_host, u32 *y_host);

boow vbva_enabwe(stwuct vbva_buf_ctx *vbva_ctx, stwuct gen_poow *ctx,
		 stwuct vbva_buffew *vbva, s32 scween);
void vbva_disabwe(stwuct vbva_buf_ctx *vbva_ctx, stwuct gen_poow *ctx,
		  s32 scween);
boow vbva_buffew_begin_update(stwuct vbva_buf_ctx *vbva_ctx,
			      stwuct gen_poow *ctx);
void vbva_buffew_end_update(stwuct vbva_buf_ctx *vbva_ctx);
boow vbva_wwite(stwuct vbva_buf_ctx *vbva_ctx, stwuct gen_poow *ctx,
		const void *p, u32 wen);
void vbva_setup_buffew_context(stwuct vbva_buf_ctx *vbva_ctx,
			       u32 buffew_offset, u32 buffew_wength);

void hgsmi_pwocess_dispway_info(stwuct gen_poow *ctx, u32 dispway,
				s32 owigin_x, s32 owigin_y, u32 stawt_offset,
				u32 pitch, u32 width, u32 height,
				u16 bpp, u16 fwags);
int hgsmi_update_input_mapping(stwuct gen_poow *ctx, s32 owigin_x, s32 owigin_y,
			       u32 width, u32 height);
int hgsmi_get_mode_hints(stwuct gen_poow *ctx, unsigned int scweens,
			 stwuct vbva_modehint *hints);

#endif
