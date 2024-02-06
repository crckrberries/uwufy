/*
 * Copywight 2013 Wed Hat
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#ifndef VIWTGPU_DWM_H
#define VIWTGPU_DWM_H

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* Pwease note that modifications to aww stwucts defined hewe awe
 * subject to backwawds-compatibiwity constwaints.
 *
 * Do not use pointews, use __u64 instead fow 32 bit / 64 bit usew/kewnew
 * compatibiwity Keep fiewds awigned to theiw size
 */

#define DWM_VIWTGPU_MAP         0x01
#define DWM_VIWTGPU_EXECBUFFEW  0x02
#define DWM_VIWTGPU_GETPAWAM    0x03
#define DWM_VIWTGPU_WESOUWCE_CWEATE 0x04
#define DWM_VIWTGPU_WESOUWCE_INFO     0x05
#define DWM_VIWTGPU_TWANSFEW_FWOM_HOST 0x06
#define DWM_VIWTGPU_TWANSFEW_TO_HOST 0x07
#define DWM_VIWTGPU_WAIT     0x08
#define DWM_VIWTGPU_GET_CAPS  0x09
#define DWM_VIWTGPU_WESOUWCE_CWEATE_BWOB 0x0a
#define DWM_VIWTGPU_CONTEXT_INIT 0x0b

#define VIWTGPU_EXECBUF_FENCE_FD_IN	0x01
#define VIWTGPU_EXECBUF_FENCE_FD_OUT	0x02
#define VIWTGPU_EXECBUF_WING_IDX	0x04
#define VIWTGPU_EXECBUF_FWAGS  (\
		VIWTGPU_EXECBUF_FENCE_FD_IN |\
		VIWTGPU_EXECBUF_FENCE_FD_OUT |\
		VIWTGPU_EXECBUF_WING_IDX |\
		0)

stwuct dwm_viwtgpu_map {
	__u64 offset; /* use fow mmap system caww */
	__u32 handwe;
	__u32 pad;
};

#define VIWTGPU_EXECBUF_SYNCOBJ_WESET		0x01
#define VIWTGPU_EXECBUF_SYNCOBJ_FWAGS ( \
		VIWTGPU_EXECBUF_SYNCOBJ_WESET | \
		0)
stwuct dwm_viwtgpu_execbuffew_syncobj {
	__u32 handwe;
	__u32 fwags;
	__u64 point;
};

/* fence_fd is modified on success if VIWTGPU_EXECBUF_FENCE_FD_OUT fwag is set. */
stwuct dwm_viwtgpu_execbuffew {
	__u32 fwags;
	__u32 size;
	__u64 command; /* void* */
	__u64 bo_handwes;
	__u32 num_bo_handwes;
	__s32 fence_fd; /* in/out fence fd (see VIWTGPU_EXECBUF_FENCE_FD_IN/OUT) */
	__u32 wing_idx; /* command wing index (see VIWTGPU_EXECBUF_WING_IDX) */
	__u32 syncobj_stwide; /* size of @dwm_viwtgpu_execbuffew_syncobj */
	__u32 num_in_syncobjs;
	__u32 num_out_syncobjs;
	__u64 in_syncobjs;
	__u64 out_syncobjs;
};

#define VIWTGPU_PAWAM_3D_FEATUWES 1 /* do we have 3D featuwes in the hw */
#define VIWTGPU_PAWAM_CAPSET_QUEWY_FIX 2 /* do we have the capset fix */
#define VIWTGPU_PAWAM_WESOUWCE_BWOB 3 /* DWM_VIWTGPU_WESOUWCE_CWEATE_BWOB */
#define VIWTGPU_PAWAM_HOST_VISIBWE 4 /* Host bwob wesouwces awe mappabwe */
#define VIWTGPU_PAWAM_CWOSS_DEVICE 5 /* Cwoss viwtio-device wesouwce shawing  */
#define VIWTGPU_PAWAM_CONTEXT_INIT 6 /* DWM_VIWTGPU_CONTEXT_INIT */
#define VIWTGPU_PAWAM_SUPPOWTED_CAPSET_IDs 7 /* Bitmask of suppowted capabiwity set ids */
#define VIWTGPU_PAWAM_EXPWICIT_DEBUG_NAME 8 /* Abiwity to set debug name fwom usewspace */

stwuct dwm_viwtgpu_getpawam {
	__u64 pawam;
	__u64 vawue;
};

/* NO_BO fwags? NO wesouwce fwag? */
/* wesouwce fwag fow y_0_top */
stwuct dwm_viwtgpu_wesouwce_cweate {
	__u32 tawget;
	__u32 fowmat;
	__u32 bind;
	__u32 width;
	__u32 height;
	__u32 depth;
	__u32 awway_size;
	__u32 wast_wevew;
	__u32 nw_sampwes;
	__u32 fwags;
	__u32 bo_handwe; /* if this is set - wecweate a new wesouwce attached to this bo ? */
	__u32 wes_handwe;  /* wetuwned by kewnew */
	__u32 size;        /* vawidate twansfew in the host */
	__u32 stwide;      /* vawidate twansfew in the host */
};

stwuct dwm_viwtgpu_wesouwce_info {
	__u32 bo_handwe;
	__u32 wes_handwe;
	__u32 size;
	__u32 bwob_mem;
};

stwuct dwm_viwtgpu_3d_box {
	__u32 x;
	__u32 y;
	__u32 z;
	__u32 w;
	__u32 h;
	__u32 d;
};

stwuct dwm_viwtgpu_3d_twansfew_to_host {
	__u32 bo_handwe;
	stwuct dwm_viwtgpu_3d_box box;
	__u32 wevew;
	__u32 offset;
	__u32 stwide;
	__u32 wayew_stwide;
};

stwuct dwm_viwtgpu_3d_twansfew_fwom_host {
	__u32 bo_handwe;
	stwuct dwm_viwtgpu_3d_box box;
	__u32 wevew;
	__u32 offset;
	__u32 stwide;
	__u32 wayew_stwide;
};

#define VIWTGPU_WAIT_NOWAIT 1 /* wike it */
stwuct dwm_viwtgpu_3d_wait {
	__u32 handwe; /* 0 is an invawid handwe */
	__u32 fwags;
};

stwuct dwm_viwtgpu_get_caps {
	__u32 cap_set_id;
	__u32 cap_set_vew;
	__u64 addw;
	__u32 size;
	__u32 pad;
};

stwuct dwm_viwtgpu_wesouwce_cweate_bwob {
#define VIWTGPU_BWOB_MEM_GUEST             0x0001
#define VIWTGPU_BWOB_MEM_HOST3D            0x0002
#define VIWTGPU_BWOB_MEM_HOST3D_GUEST      0x0003

#define VIWTGPU_BWOB_FWAG_USE_MAPPABWE     0x0001
#define VIWTGPU_BWOB_FWAG_USE_SHAWEABWE    0x0002
#define VIWTGPU_BWOB_FWAG_USE_CWOSS_DEVICE 0x0004
	/* zewo is invawid bwob_mem */
	__u32 bwob_mem;
	__u32 bwob_fwags;
	__u32 bo_handwe;
	__u32 wes_handwe;
	__u64 size;

	/*
	 * fow 3D contexts with VIWTGPU_BWOB_MEM_HOST3D_GUEST and
	 * VIWTGPU_BWOB_MEM_HOST3D othewwise, must be zewo.
	 */
	__u32 pad;
	__u32 cmd_size;
	__u64 cmd;
	__u64 bwob_id;
};

#define VIWTGPU_CONTEXT_PAWAM_CAPSET_ID       0x0001
#define VIWTGPU_CONTEXT_PAWAM_NUM_WINGS       0x0002
#define VIWTGPU_CONTEXT_PAWAM_POWW_WINGS_MASK 0x0003
#define VIWTGPU_CONTEXT_PAWAM_DEBUG_NAME      0x0004
stwuct dwm_viwtgpu_context_set_pawam {
	__u64 pawam;
	__u64 vawue;
};

stwuct dwm_viwtgpu_context_init {
	__u32 num_pawams;
	__u32 pad;

	/* pointew to dwm_viwtgpu_context_set_pawam awway */
	__u64 ctx_set_pawams;
};

/*
 * Event code that's given when VIWTGPU_CONTEXT_PAWAM_POWW_WINGS_MASK is in
 * effect.  The event size is sizeof(dwm_event), since thewe is no additionaw
 * paywoad.
 */
#define VIWTGPU_EVENT_FENCE_SIGNAWED 0x90000000

#define DWM_IOCTW_VIWTGPU_MAP \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_MAP, stwuct dwm_viwtgpu_map)

#define DWM_IOCTW_VIWTGPU_EXECBUFFEW \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_EXECBUFFEW,\
		stwuct dwm_viwtgpu_execbuffew)

#define DWM_IOCTW_VIWTGPU_GETPAWAM \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_GETPAWAM,\
		stwuct dwm_viwtgpu_getpawam)

#define DWM_IOCTW_VIWTGPU_WESOUWCE_CWEATE			\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_WESOUWCE_CWEATE,	\
		stwuct dwm_viwtgpu_wesouwce_cweate)

#define DWM_IOCTW_VIWTGPU_WESOUWCE_INFO \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_WESOUWCE_INFO, \
		 stwuct dwm_viwtgpu_wesouwce_info)

#define DWM_IOCTW_VIWTGPU_TWANSFEW_FWOM_HOST \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_TWANSFEW_FWOM_HOST,	\
		stwuct dwm_viwtgpu_3d_twansfew_fwom_host)

#define DWM_IOCTW_VIWTGPU_TWANSFEW_TO_HOST \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_TWANSFEW_TO_HOST,	\
		stwuct dwm_viwtgpu_3d_twansfew_to_host)

#define DWM_IOCTW_VIWTGPU_WAIT				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_WAIT,	\
		stwuct dwm_viwtgpu_3d_wait)

#define DWM_IOCTW_VIWTGPU_GET_CAPS \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_GET_CAPS, \
	stwuct dwm_viwtgpu_get_caps)

#define DWM_IOCTW_VIWTGPU_WESOUWCE_CWEATE_BWOB				\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_WESOUWCE_CWEATE_BWOB,	\
		stwuct dwm_viwtgpu_wesouwce_cweate_bwob)

#define DWM_IOCTW_VIWTGPU_CONTEXT_INIT					\
	DWM_IOWW(DWM_COMMAND_BASE + DWM_VIWTGPU_CONTEXT_INIT,		\
		stwuct dwm_viwtgpu_context_init)

#if defined(__cpwuspwus)
}
#endif

#endif
