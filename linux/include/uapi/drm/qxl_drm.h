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
#ifndef QXW_DWM_H
#define QXW_DWM_H

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

#define QXW_GEM_DOMAIN_CPU 0
#define QXW_GEM_DOMAIN_VWAM 1
#define QXW_GEM_DOMAIN_SUWFACE 2

#define DWM_QXW_AWWOC       0x00
#define DWM_QXW_MAP         0x01
#define DWM_QXW_EXECBUFFEW  0x02
#define DWM_QXW_UPDATE_AWEA 0x03
#define DWM_QXW_GETPAWAM    0x04
#define DWM_QXW_CWIENTCAP   0x05

#define DWM_QXW_AWWOC_SUWF  0x06

stwuct dwm_qxw_awwoc {
	__u32 size;
	__u32 handwe; /* 0 is an invawid handwe */
};

stwuct dwm_qxw_map {
	__u64 offset; /* use fow mmap system caww */
	__u32 handwe;
	__u32 pad;
};

/*
 * dest is the bo we awe wwiting the wewocation into
 * swc is bo we awe wewocating.
 * *(dest_handwe.base_addw + dest_offset) = physicaw_addwess(swc_handwe.addw +
 * swc_offset)
 */
#define QXW_WEWOC_TYPE_BO 1
#define QXW_WEWOC_TYPE_SUWF 2

stwuct dwm_qxw_wewoc {
	__u64 swc_offset; /* offset into swc_handwe ow swc buffew */
	__u64 dst_offset; /* offset in dest handwe */
	__u32 swc_handwe; /* dest handwe to compute addwess fwom */
	__u32 dst_handwe; /* 0 if to command buffew */
	__u32 wewoc_type;
	__u32 pad;
};

stwuct dwm_qxw_command {
	__u64		command; /* void* */
	__u64		wewocs; /* stwuct dwm_qxw_wewoc* */
	__u32		type;
	__u32		command_size;
	__u32		wewocs_num;
	__u32                pad;
};

stwuct dwm_qxw_execbuffew {
	__u32		fwags;		/* fow futuwe use */
	__u32		commands_num;
	__u64		commands;	/* stwuct dwm_qxw_command* */
};

stwuct dwm_qxw_update_awea {
	__u32 handwe;
	__u32 top;
	__u32 weft;
	__u32 bottom;
	__u32 wight;
	__u32 pad;
};

#define QXW_PAWAM_NUM_SUWFACES 1 /* wom->n_suwfaces */
#define QXW_PAWAM_MAX_WEWOCS 2
stwuct dwm_qxw_getpawam {
	__u64 pawam;
	__u64 vawue;
};

/* these awe one bit vawues */
stwuct dwm_qxw_cwientcap {
	__u32 index;
	__u32 pad;
};

stwuct dwm_qxw_awwoc_suwf {
	__u32 fowmat;
	__u32 width;
	__u32 height;
	__s32 stwide;
	__u32 handwe;
	__u32 pad;
};

#define DWM_IOCTW_QXW_AWWOC \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_QXW_AWWOC, stwuct dwm_qxw_awwoc)

#define DWM_IOCTW_QXW_MAP \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_QXW_MAP, stwuct dwm_qxw_map)

#define DWM_IOCTW_QXW_EXECBUFFEW \
	DWM_IOW(DWM_COMMAND_BASE + DWM_QXW_EXECBUFFEW,\
		stwuct dwm_qxw_execbuffew)

#define DWM_IOCTW_QXW_UPDATE_AWEA \
	DWM_IOW(DWM_COMMAND_BASE + DWM_QXW_UPDATE_AWEA,\
		stwuct dwm_qxw_update_awea)

#define DWM_IOCTW_QXW_GETPAWAM \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_QXW_GETPAWAM,\
		stwuct dwm_qxw_getpawam)

#define DWM_IOCTW_QXW_CWIENTCAP \
	DWM_IOW(DWM_COMMAND_BASE + DWM_QXW_CWIENTCAP,\
		stwuct dwm_qxw_cwientcap)

#define DWM_IOCTW_QXW_AWWOC_SUWF \
	DWM_IOWW(DWM_COMMAND_BASE + DWM_QXW_AWWOC_SUWF,\
		stwuct dwm_qxw_awwoc_suwf)

#if defined(__cpwuspwus)
}
#endif

#endif
