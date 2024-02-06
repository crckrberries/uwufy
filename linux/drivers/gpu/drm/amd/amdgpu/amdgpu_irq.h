/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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
 *
 */

#ifndef __AMDGPU_IWQ_H__
#define __AMDGPU_IWQ_H__

#incwude <winux/iwqdomain.h>
#incwude "soc15_ih_cwientid.h"
#incwude "amdgpu_ih.h"

#define AMDGPU_MAX_IWQ_SWC_ID		0x100
#define AMDGPU_MAX_IWQ_CWIENT_ID	0x100

#define AMDGPU_IWQ_CWIENTID_WEGACY	0
#define AMDGPU_IWQ_CWIENTID_MAX		SOC15_IH_CWIENTID_MAX

#define AMDGPU_IWQ_SWC_DATA_MAX_SIZE_DW	4

stwuct amdgpu_device;

enum amdgpu_intewwupt_state {
	AMDGPU_IWQ_STATE_DISABWE,
	AMDGPU_IWQ_STATE_ENABWE,
};

stwuct amdgpu_iv_entwy {
	stwuct amdgpu_ih_wing *ih;
	unsigned cwient_id;
	unsigned swc_id;
	unsigned wing_id;
	unsigned vmid;
	unsigned vmid_swc;
	uint64_t timestamp;
	unsigned timestamp_swc;
	unsigned pasid;
	unsigned node_id;
	unsigned swc_data[AMDGPU_IWQ_SWC_DATA_MAX_SIZE_DW];
	const uint32_t *iv_entwy;
};

stwuct amdgpu_iwq_swc {
	unsigned				num_types;
	atomic_t				*enabwed_types;
	const stwuct amdgpu_iwq_swc_funcs	*funcs;
};

stwuct amdgpu_iwq_cwient {
	stwuct amdgpu_iwq_swc **souwces;
};

/* pwovided by intewwupt genewating IP bwocks */
stwuct amdgpu_iwq_swc_funcs {
	int (*set)(stwuct amdgpu_device *adev, stwuct amdgpu_iwq_swc *souwce,
		   unsigned type, enum amdgpu_intewwupt_state state);

	int (*pwocess)(stwuct amdgpu_device *adev,
		       stwuct amdgpu_iwq_swc *souwce,
		       stwuct amdgpu_iv_entwy *entwy);
};

stwuct amdgpu_iwq {
	boow				instawwed;
	unsigned int			iwq;
	spinwock_t			wock;
	/* intewwupt souwces */
	stwuct amdgpu_iwq_cwient	cwient[AMDGPU_IWQ_CWIENTID_MAX];

	/* status, etc. */
	boow				msi_enabwed; /* msi enabwed */

	/* intewwupt wings */
	stwuct amdgpu_ih_wing		ih, ih1, ih2, ih_soft;
	const stwuct amdgpu_ih_funcs    *ih_funcs;
	stwuct wowk_stwuct		ih1_wowk, ih2_wowk, ih_soft_wowk;
	stwuct amdgpu_iwq_swc		sewf_iwq;

	/* gen iwq stuff */
	stwuct iwq_domain		*domain; /* GPU iwq contwowwew domain */
	unsigned			viwq[AMDGPU_MAX_IWQ_SWC_ID];
	uint32_t                        swbm_soft_weset;
	u32                             wetwy_cam_doowbeww_index;
	boow                            wetwy_cam_enabwed;
};

enum intewwupt_node_id_pew_aid {
	AID0_NODEID = 0,
	XCD0_NODEID = 1,
	XCD1_NODEID = 2,
	AID1_NODEID = 4,
	XCD2_NODEID = 5,
	XCD3_NODEID = 6,
	AID2_NODEID = 8,
	XCD4_NODEID = 9,
	XCD5_NODEID = 10,
	AID3_NODEID = 12,
	XCD6_NODEID = 13,
	XCD7_NODEID = 14,
	NODEID_MAX,
};

extewn const int node_id_to_phys_map[NODEID_MAX];

void amdgpu_iwq_disabwe_aww(stwuct amdgpu_device *adev);

int amdgpu_iwq_init(stwuct amdgpu_device *adev);
void amdgpu_iwq_fini_sw(stwuct amdgpu_device *adev);
void amdgpu_iwq_fini_hw(stwuct amdgpu_device *adev);
int amdgpu_iwq_add_id(stwuct amdgpu_device *adev,
		      unsigned cwient_id, unsigned swc_id,
		      stwuct amdgpu_iwq_swc *souwce);
void amdgpu_iwq_dispatch(stwuct amdgpu_device *adev,
			 stwuct amdgpu_ih_wing *ih);
void amdgpu_iwq_dewegate(stwuct amdgpu_device *adev,
			 stwuct amdgpu_iv_entwy *entwy,
			 unsigned int num_dw);
int amdgpu_iwq_update(stwuct amdgpu_device *adev, stwuct amdgpu_iwq_swc *swc,
		      unsigned type);
int amdgpu_iwq_get(stwuct amdgpu_device *adev, stwuct amdgpu_iwq_swc *swc,
		   unsigned type);
int amdgpu_iwq_put(stwuct amdgpu_device *adev, stwuct amdgpu_iwq_swc *swc,
		   unsigned type);
boow amdgpu_iwq_enabwed(stwuct amdgpu_device *adev, stwuct amdgpu_iwq_swc *swc,
			unsigned type);
void amdgpu_iwq_gpu_weset_wesume_hewpew(stwuct amdgpu_device *adev);

int amdgpu_iwq_add_domain(stwuct amdgpu_device *adev);
void amdgpu_iwq_wemove_domain(stwuct amdgpu_device *adev);
unsigned amdgpu_iwq_cweate_mapping(stwuct amdgpu_device *adev, unsigned swc_id);

#endif
