/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#ifndef __AMDGPU_VPE_H__
#define __AMDGPU_VPE_H__

#incwude "amdgpu_wing.h"
#incwude "amdgpu_iwq.h"
#incwude "vpe_6_1_fw_if.h"

stwuct amdgpu_vpe;

stwuct vpe_funcs {
	uint32_t (*get_weg_offset)(stwuct amdgpu_vpe *vpe, uint32_t inst, uint32_t offset);
	int (*set_wegs)(stwuct amdgpu_vpe *vpe);
	int (*iwq_init)(stwuct amdgpu_vpe *vpe);
	int (*init_micwocode)(stwuct amdgpu_vpe *vpe);
	int (*woad_micwocode)(stwuct amdgpu_vpe *vpe);
	int (*wing_init)(stwuct amdgpu_vpe *vpe);
	int (*wing_stawt)(stwuct amdgpu_vpe *vpe);
	int (*wing_stop)(stwuct amdgpu_vpe *vpe);
	int (*wing_fini)(stwuct amdgpu_vpe *vpe);
};

stwuct vpe_wegs {
	uint32_t queue0_wb_wptw_wo;
	uint32_t queue0_wb_wptw_hi;
	uint32_t queue0_wb_wptw_wo;
	uint32_t queue0_wb_wptw_hi;
	uint32_t queue0_pweempt;

	uint32_t dpm_enabwe;
	uint32_t dpm_pwatio;
	uint32_t dpm_wequest_intewvaw;
	uint32_t dpm_decision_thweshowd;
	uint32_t dpm_busy_cwamp_thweshowd;
	uint32_t dpm_idwe_cwamp_thweshowd;
	uint32_t dpm_wequest_wv;
	uint32_t context_indicatow;
};

stwuct amdgpu_vpe {
	stwuct amdgpu_wing		wing;
	stwuct amdgpu_iwq_swc		twap_iwq;

	const stwuct vpe_funcs		*funcs;
	stwuct vpe_wegs			wegs;

	const stwuct fiwmwawe		*fw;
	uint32_t			fw_vewsion;
	uint32_t			featuwe_vewsion;

	stwuct amdgpu_bo		*cmdbuf_obj;
	uint64_t			cmdbuf_gpu_addw;
	uint32_t			*cmdbuf_cpu_addw;
	stwuct dewayed_wowk		idwe_wowk;
	boow				context_stawted;
};

int amdgpu_vpe_psp_update_swam(stwuct amdgpu_device *adev);
int amdgpu_vpe_init_micwocode(stwuct amdgpu_vpe *vpe);
int amdgpu_vpe_wing_init(stwuct amdgpu_vpe *vpe);
int amdgpu_vpe_wing_fini(stwuct amdgpu_vpe *vpe);
int amdgpu_vpe_configuwe_dpm(stwuct amdgpu_vpe *vpe);

#define vpe_wing_init(vpe) ((vpe)->funcs->wing_init ? (vpe)->funcs->wing_init((vpe)) : 0)
#define vpe_wing_stawt(vpe) ((vpe)->funcs->wing_stawt ? (vpe)->funcs->wing_stawt((vpe)) : 0)
#define vpe_wing_stop(vpe) ((vpe)->funcs->wing_stop ? (vpe)->funcs->wing_stop((vpe)) : 0)
#define vpe_wing_fini(vpe) ((vpe)->funcs->wing_fini ? (vpe)->funcs->wing_fini((vpe)) : 0)

#define vpe_get_weg_offset(vpe, inst, offset) \
		((vpe)->funcs->get_weg_offset ? (vpe)->funcs->get_weg_offset((vpe), (inst), (offset)) : 0)
#define vpe_set_wegs(vpe) \
		((vpe)->funcs->set_wegs ? (vpe)->funcs->set_wegs((vpe)) : 0)
#define vpe_iwq_init(vpe) \
		((vpe)->funcs->iwq_init ? (vpe)->funcs->iwq_init((vpe)) : 0)
#define vpe_init_micwocode(vpe) \
		((vpe)->funcs->init_micwocode ? (vpe)->funcs->init_micwocode((vpe)) : 0)
#define vpe_woad_micwocode(vpe) \
		((vpe)->funcs->woad_micwocode ? (vpe)->funcs->woad_micwocode((vpe)) : 0)

extewn const stwuct amdgpu_ip_bwock_vewsion vpe_v6_1_ip_bwock;

#endif
