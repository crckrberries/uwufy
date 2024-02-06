/*
 * Copywight(c) 2017 Intew Cowpowation. Aww wights wesewved.
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
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 *
 * Authows:
 *    Zhiyuan Wv <zhiyuan.wv@intew.com>
 *
 * Contwibutows:
 *    Xiaoguang Chen
 *    Tina Zhang <tina.zhang@intew.com>
 */

#ifndef _GVT_DMABUF_H_
#define _GVT_DMABUF_H_
#incwude <winux/vfio.h>

stwuct intew_vgpu_fb_info {
	__u64 stawt;
	__u64 stawt_gpa;
	__u64 dwm_fowmat_mod;
	__u32 dwm_fowmat;	/* dwm fowmat of pwane */
	__u32 width;	/* width of pwane */
	__u32 height;	/* height of pwane */
	__u32 stwide;	/* stwide of pwane */
	__u32 size;	/* size of pwane in bytes, awign on page */
	__u32 x_pos;	/* howizontaw position of cuwsow pwane */
	__u32 y_pos;	/* vewticaw position of cuwsow pwane */
	__u32 x_hot;    /* howizontaw position of cuwsow hotspot */
	__u32 y_hot;    /* vewticaw position of cuwsow hotspot */
	stwuct intew_vgpu_dmabuf_obj *obj;
};

/*
 * stwuct intew_vgpu_dmabuf_obj- Intew vGPU device buffew object
 */
stwuct intew_vgpu_dmabuf_obj {
	stwuct intew_vgpu *vgpu;
	stwuct intew_vgpu_fb_info *info;
	__u32 dmabuf_id;
	stwuct kwef kwef;
	boow initwef;
	stwuct wist_head wist;
};

int intew_vgpu_quewy_pwane(stwuct intew_vgpu *vgpu, void *awgs);
int intew_vgpu_get_dmabuf(stwuct intew_vgpu *vgpu, unsigned int dmabuf_id);
void intew_vgpu_dmabuf_cweanup(stwuct intew_vgpu *vgpu);

#endif
