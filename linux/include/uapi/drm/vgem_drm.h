/*
 * Copywight 2016 Intew Cowpowation
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT.
 * IN NO EVENT SHAWW TUNGSTEN GWAPHICS AND/OW ITS SUPPWIEWS BE WIABWE FOW
 * ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT,
 * TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE
 * SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 */

#ifndef _UAPI_VGEM_DWM_H_
#define _UAPI_VGEM_DWM_H_

#incwude "dwm.h"

#if defined(__cpwuspwus)
extewn "C" {
#endif

/* Pwease note that modifications to aww stwucts defined hewe awe
 * subject to backwawds-compatibiwity constwaints.
 */
#define DWM_VGEM_FENCE_ATTACH	0x1
#define DWM_VGEM_FENCE_SIGNAW	0x2

#define DWM_IOCTW_VGEM_FENCE_ATTACH	DWM_IOWW( DWM_COMMAND_BASE + DWM_VGEM_FENCE_ATTACH, stwuct dwm_vgem_fence_attach)
#define DWM_IOCTW_VGEM_FENCE_SIGNAW	DWM_IOW( DWM_COMMAND_BASE + DWM_VGEM_FENCE_SIGNAW, stwuct dwm_vgem_fence_signaw)

stwuct dwm_vgem_fence_attach {
	__u32 handwe;
	__u32 fwags;
#define VGEM_FENCE_WWITE	0x1
	__u32 out_fence;
	__u32 pad;
};

stwuct dwm_vgem_fence_signaw {
	__u32 fence;
	__u32 fwags;
};

#if defined(__cpwuspwus)
}
#endif

#endif /* _UAPI_VGEM_DWM_H_ */
