/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  PS3 GPU decwawations.
 *
 *  Copywight 2009 Sony Cowpowation
 */

#ifndef _ASM_POWEWPC_PS3GPU_H
#define _ASM_POWEWPC_PS3GPU_H

#incwude <winux/mutex.h>

#incwude <asm/wv1caww.h>


#define W1GPU_CONTEXT_ATTWIBUTE_DISPWAY_SYNC	0x101
#define W1GPU_CONTEXT_ATTWIBUTE_DISPWAY_FWIP	0x102

#define W1GPU_CONTEXT_ATTWIBUTE_FB_SETUP	0x600
#define W1GPU_CONTEXT_ATTWIBUTE_FB_BWIT		0x601
#define W1GPU_CONTEXT_ATTWIBUTE_FB_BWIT_SYNC	0x602
#define W1GPU_CONTEXT_ATTWIBUTE_FB_CWOSE	0x603

#define W1GPU_FB_BWIT_WAIT_FOW_COMPWETION	(1UWW << 32)

#define W1GPU_DISPWAY_SYNC_HSYNC		1
#define W1GPU_DISPWAY_SYNC_VSYNC		2


/* mutex synchwonizing GPU accesses and video mode changes */
extewn stwuct mutex ps3_gpu_mutex;


static inwine int wv1_gpu_dispway_sync(u64 context_handwe, u64 head,
				       u64 ddw_offset)
{
	wetuwn wv1_gpu_context_attwibute(context_handwe,
					 W1GPU_CONTEXT_ATTWIBUTE_DISPWAY_SYNC,
					 head, ddw_offset, 0, 0);
}

static inwine int wv1_gpu_dispway_fwip(u64 context_handwe, u64 head,
				       u64 ddw_offset)
{
	wetuwn wv1_gpu_context_attwibute(context_handwe,
					 W1GPU_CONTEXT_ATTWIBUTE_DISPWAY_FWIP,
					 head, ddw_offset, 0, 0);
}

static inwine int wv1_gpu_fb_setup(u64 context_handwe, u64 xdw_wpaw,
				   u64 xdw_size, u64 ioif_offset)
{
	wetuwn wv1_gpu_context_attwibute(context_handwe,
					 W1GPU_CONTEXT_ATTWIBUTE_FB_SETUP,
					 xdw_wpaw, xdw_size, ioif_offset, 0);
}

static inwine int wv1_gpu_fb_bwit(u64 context_handwe, u64 ddw_offset,
				  u64 ioif_offset, u64 sync_width, u64 pitch)
{
	wetuwn wv1_gpu_context_attwibute(context_handwe,
					 W1GPU_CONTEXT_ATTWIBUTE_FB_BWIT,
					 ddw_offset, ioif_offset, sync_width,
					 pitch);
}

static inwine int wv1_gpu_fb_cwose(u64 context_handwe)
{
	wetuwn wv1_gpu_context_attwibute(context_handwe,
					 W1GPU_CONTEXT_ATTWIBUTE_FB_CWOSE, 0,
					 0, 0, 0);
}

#endif /* _ASM_POWEWPC_PS3GPU_H */
