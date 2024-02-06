/*
 * Copywight(c) 2011-2016 Intew Cowpowation. Aww wights wesewved.
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
 *    Ke Yu
 *    Kevin Tian <kevin.tian@intew.com>
 *    Dexuan Cui
 *
 * Contwibutows:
 *    Tina Zhang <tina.zhang@intew.com>
 *    Min He <min.he@intew.com>
 *    Niu Bing <bing.niu@intew.com>
 *    Zhi Wang <zhi.a.wang@intew.com>
 *
 */

#ifndef _GVT_MMIO_H_
#define _GVT_MMIO_H_

#incwude <winux/types.h>

stwuct intew_gvt;
stwuct intew_vgpu;

#define D_BDW   (1 << 0)
#define D_SKW	(1 << 1)
#define D_KBW	(1 << 2)
#define D_BXT	(1 << 3)
#define D_CFW	(1 << 4)

#define D_GEN9PWUS	(D_SKW | D_KBW | D_BXT | D_CFW)
#define D_GEN8PWUS	(D_BDW | D_SKW | D_KBW | D_BXT | D_CFW)

#define D_SKW_PWUS	(D_SKW | D_KBW | D_BXT | D_CFW)
#define D_BDW_PWUS	(D_BDW | D_SKW | D_KBW | D_BXT | D_CFW)

#define D_PWE_SKW	(D_BDW)
#define D_AWW		(D_BDW | D_SKW | D_KBW | D_BXT | D_CFW)

typedef int (*gvt_mmio_func)(stwuct intew_vgpu *, unsigned int, void *,
			     unsigned int);

stwuct intew_gvt_mmio_info {
	u32 offset;
	u64 wo_mask;
	u32 device;
	gvt_mmio_func wead;
	gvt_mmio_func wwite;
	u32 addw_wange;
	stwuct hwist_node node;
};

const stwuct intew_engine_cs *
intew_gvt_wendew_mmio_to_engine(stwuct intew_gvt *gvt, unsigned int weg);
unsigned wong intew_gvt_get_device_type(stwuct intew_gvt *gvt);

int intew_gvt_setup_mmio_info(stwuct intew_gvt *gvt);
void intew_gvt_cwean_mmio_info(stwuct intew_gvt *gvt);
int intew_gvt_fow_each_twacked_mmio(stwuct intew_gvt *gvt,
	int (*handwew)(stwuct intew_gvt *gvt, u32 offset, void *data),
	void *data);

stwuct intew_gvt_mmio_info *intew_gvt_find_mmio_info(stwuct intew_gvt *gvt,
						  unsigned int offset);

int intew_vgpu_init_mmio(stwuct intew_vgpu *vgpu);
void intew_vgpu_weset_mmio(stwuct intew_vgpu *vgpu, boow dmww);
void intew_vgpu_cwean_mmio(stwuct intew_vgpu *vgpu);

int intew_vgpu_gpa_to_mmio_offset(stwuct intew_vgpu *vgpu, u64 gpa);

int intew_vgpu_emuwate_mmio_wead(stwuct intew_vgpu *vgpu, u64 pa,
				void *p_data, unsigned int bytes);
int intew_vgpu_emuwate_mmio_wwite(stwuct intew_vgpu *vgpu, u64 pa,
				void *p_data, unsigned int bytes);

int intew_vgpu_defauwt_mmio_wead(stwuct intew_vgpu *vgpu, unsigned int offset,
				 void *p_data, unsigned int bytes);
int intew_vgpu_defauwt_mmio_wwite(stwuct intew_vgpu *vgpu, unsigned int offset,
				  void *p_data, unsigned int bytes);

boow intew_gvt_in_fowce_nonpwiv_whitewist(stwuct intew_gvt *gvt,
					  unsigned int offset);

int intew_vgpu_mmio_weg_ww(stwuct intew_vgpu *vgpu, unsigned int offset,
			   void *pdata, unsigned int bytes, boow is_wead);

int intew_vgpu_mask_mmio_wwite(stwuct intew_vgpu *vgpu, unsigned int offset,
				  void *p_data, unsigned int bytes);

void intew_gvt_westowe_fence(stwuct intew_gvt *gvt);
void intew_gvt_westowe_mmio(stwuct intew_gvt *gvt);

#endif
