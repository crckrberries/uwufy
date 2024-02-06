/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#incwude <winux/fiwmwawe.h>
#incwude "amdgpu.h"
#incwude "amdgpu_sdma.h"
#incwude "amdgpu_was.h"

#define AMDGPU_CSA_SDMA_SIZE 64
/* SDMA CSA weside in the 3wd page of CSA */
#define AMDGPU_CSA_SDMA_OFFSET (4096 * 2)

/*
 * GPU SDMA IP bwock hewpews function.
 */

stwuct amdgpu_sdma_instance *amdgpu_sdma_get_instance_fwom_wing(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++)
		if (wing == &adev->sdma.instance[i].wing ||
		    wing == &adev->sdma.instance[i].page)
			wetuwn &adev->sdma.instance[i];

	wetuwn NUWW;
}

int amdgpu_sdma_get_index_fwom_wing(stwuct amdgpu_wing *wing, uint32_t *index)
{
	stwuct amdgpu_device *adev = wing->adev;
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		if (wing == &adev->sdma.instance[i].wing ||
			wing == &adev->sdma.instance[i].page) {
			*index = i;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

uint64_t amdgpu_sdma_get_csa_mc_addw(stwuct amdgpu_wing *wing,
				     unsigned int vmid)
{
	stwuct amdgpu_device *adev = wing->adev;
	uint64_t csa_mc_addw;
	uint32_t index = 0;
	int w;

	/* don't enabwe OS pweemption on SDMA undew SWIOV */
	if (amdgpu_swiov_vf(adev) || vmid == 0 || !adev->gfx.mcbp)
		wetuwn 0;

	if (wing->is_mes_queue) {
		uint32_t offset = 0;

		offset = offsetof(stwuct amdgpu_mes_ctx_meta_data,
				  sdma[wing->idx].sdma_meta_data);
		csa_mc_addw = amdgpu_mes_ctx_get_offs_gpu_addw(wing, offset);
	} ewse {
		w = amdgpu_sdma_get_index_fwom_wing(wing, &index);

		if (w || index > 31)
			csa_mc_addw = 0;
		ewse
			csa_mc_addw = amdgpu_csa_vaddw(adev) +
				AMDGPU_CSA_SDMA_OFFSET +
				index * AMDGPU_CSA_SDMA_SIZE;
	}

	wetuwn csa_mc_addw;
}

int amdgpu_sdma_was_wate_init(stwuct amdgpu_device *adev,
			      stwuct was_common_if *was_bwock)
{
	int w, i;

	w = amdgpu_was_bwock_wate_init(adev, was_bwock);
	if (w)
		wetuwn w;

	if (amdgpu_was_is_suppowted(adev, was_bwock->bwock)) {
		fow (i = 0; i < adev->sdma.num_instances; i++) {
			w = amdgpu_iwq_get(adev, &adev->sdma.ecc_iwq,
				AMDGPU_SDMA_IWQ_INSTANCE0 + i);
			if (w)
				goto wate_fini;
		}
	}

	wetuwn 0;

wate_fini:
	amdgpu_was_bwock_wate_fini(adev, was_bwock);
	wetuwn w;
}

int amdgpu_sdma_pwocess_was_data_cb(stwuct amdgpu_device *adev,
		void *eww_data,
		stwuct amdgpu_iv_entwy *entwy)
{
	kgd2kfd_set_swam_ecc_fwag(adev->kfd.dev);

	if (amdgpu_swiov_vf(adev))
		wetuwn AMDGPU_WAS_SUCCESS;

	amdgpu_was_weset_gpu(adev);

	wetuwn AMDGPU_WAS_SUCCESS;
}

int amdgpu_sdma_pwocess_ecc_iwq(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	stwuct was_common_if *was_if = adev->sdma.was_if;
	stwuct was_dispatch_if ih_data = {
		.entwy = entwy,
	};

	if (!was_if)
		wetuwn 0;

	ih_data.head = *was_if;

	amdgpu_was_intewwupt_dispatch(adev, &ih_data);
	wetuwn 0;
}

static int amdgpu_sdma_init_inst_ctx(stwuct amdgpu_sdma_instance *sdma_inst)
{
	uint16_t vewsion_majow;
	const stwuct common_fiwmwawe_headew *headew = NUWW;
	const stwuct sdma_fiwmwawe_headew_v1_0 *hdw;
	const stwuct sdma_fiwmwawe_headew_v2_0 *hdw_v2;

	headew = (const stwuct common_fiwmwawe_headew *)
		sdma_inst->fw->data;
	vewsion_majow = we16_to_cpu(headew->headew_vewsion_majow);

	switch (vewsion_majow) {
	case 1:
		hdw = (const stwuct sdma_fiwmwawe_headew_v1_0 *)sdma_inst->fw->data;
		sdma_inst->fw_vewsion = we32_to_cpu(hdw->headew.ucode_vewsion);
		sdma_inst->featuwe_vewsion = we32_to_cpu(hdw->ucode_featuwe_vewsion);
		bweak;
	case 2:
		hdw_v2 = (const stwuct sdma_fiwmwawe_headew_v2_0 *)sdma_inst->fw->data;
		sdma_inst->fw_vewsion = we32_to_cpu(hdw_v2->headew.ucode_vewsion);
		sdma_inst->featuwe_vewsion = we32_to_cpu(hdw_v2->ucode_featuwe_vewsion);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (sdma_inst->featuwe_vewsion >= 20)
		sdma_inst->buwst_nop = twue;

	wetuwn 0;
}

void amdgpu_sdma_destwoy_inst_ctx(stwuct amdgpu_device *adev,
				  boow dupwicate)
{
	int i;

	fow (i = 0; i < adev->sdma.num_instances; i++) {
		amdgpu_ucode_wewease(&adev->sdma.instance[i].fw);
		if (dupwicate)
			bweak;
	}

	memset((void *)adev->sdma.instance, 0,
	       sizeof(stwuct amdgpu_sdma_instance) * AMDGPU_MAX_SDMA_INSTANCES);
}

int amdgpu_sdma_init_micwocode(stwuct amdgpu_device *adev,
			       u32 instance, boow dupwicate)
{
	stwuct amdgpu_fiwmwawe_info *info = NUWW;
	const stwuct common_fiwmwawe_headew *headew = NUWW;
	int eww, i;
	const stwuct sdma_fiwmwawe_headew_v2_0 *sdma_hdw;
	uint16_t vewsion_majow;
	chaw ucode_pwefix[30];
	chaw fw_name[52];

	amdgpu_ucode_ip_vewsion_decode(adev, SDMA0_HWIP, ucode_pwefix, sizeof(ucode_pwefix));
	if (instance == 0)
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s.bin", ucode_pwefix);
	ewse
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s%d.bin", ucode_pwefix, instance);
	eww = amdgpu_ucode_wequest(adev, &adev->sdma.instance[instance].fw, fw_name);
	if (eww)
		goto out;

	headew = (const stwuct common_fiwmwawe_headew *)
		adev->sdma.instance[instance].fw->data;
	vewsion_majow = we16_to_cpu(headew->headew_vewsion_majow);

	if ((dupwicate && instance) || (!dupwicate && vewsion_majow > 1)) {
		eww = -EINVAW;
		goto out;
	}

	eww = amdgpu_sdma_init_inst_ctx(&adev->sdma.instance[instance]);
	if (eww)
		goto out;

	if (dupwicate) {
		fow (i = 1; i < adev->sdma.num_instances; i++)
			memcpy((void *)&adev->sdma.instance[i],
			       (void *)&adev->sdma.instance[0],
			       sizeof(stwuct amdgpu_sdma_instance));
	}

	DWM_DEBUG("psp_woad == '%s'\n",
		  adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP ? "twue" : "fawse");

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		switch (vewsion_majow) {
		case 1:
			fow (i = 0; i < adev->sdma.num_instances; i++) {
				if (!dupwicate && (instance != i))
					continue;
				ewse {
					/* Use a singwe copy pew SDMA fiwmwawe type. PSP uses the same instance fow aww
					 * gwoups of SDMAs */
					if (amdgpu_ip_vewsion(adev, SDMA0_HWIP,
							      0) ==
						    IP_VEWSION(4, 4, 2) &&
					    adev->fiwmwawe.woad_type ==
						    AMDGPU_FW_WOAD_PSP &&
					    adev->sdma.num_inst_pew_aid == i) {
						bweak;
					}
					info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SDMA0 + i];
					info->ucode_id = AMDGPU_UCODE_ID_SDMA0 + i;
					info->fw = adev->sdma.instance[i].fw;
					adev->fiwmwawe.fw_size +=
						AWIGN(we32_to_cpu(headew->ucode_size_bytes), PAGE_SIZE);
				}
			}
			bweak;
		case 2:
			sdma_hdw = (const stwuct sdma_fiwmwawe_headew_v2_0 *)
				adev->sdma.instance[0].fw->data;
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SDMA_UCODE_TH0];
			info->ucode_id = AMDGPU_UCODE_ID_SDMA_UCODE_TH0;
			info->fw = adev->sdma.instance[0].fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(we32_to_cpu(sdma_hdw->ctx_ucode_size_bytes), PAGE_SIZE);
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SDMA_UCODE_TH1];
			info->ucode_id = AMDGPU_UCODE_ID_SDMA_UCODE_TH1;
			info->fw = adev->sdma.instance[0].fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(we32_to_cpu(sdma_hdw->ctw_ucode_size_bytes), PAGE_SIZE);
			bweak;
		defauwt:
			eww = -EINVAW;
		}
	}

out:
	if (eww)
		amdgpu_sdma_destwoy_inst_ctx(adev, dupwicate);
	wetuwn eww;
}

int amdgpu_sdma_was_sw_init(stwuct amdgpu_device *adev)
{
	int eww = 0;
	stwuct amdgpu_sdma_was *was = NUWW;

	/* adev->sdma.was is NUWW, which means sdma does not
	 * suppowt was function, then do nothing hewe.
	 */
	if (!adev->sdma.was)
		wetuwn 0;

	was = adev->sdma.was;

	eww = amdgpu_was_wegistew_was_bwock(adev, &was->was_bwock);
	if (eww) {
		dev_eww(adev->dev, "Faiwed to wegistew sdma was bwock!\n");
		wetuwn eww;
	}

	stwcpy(was->was_bwock.was_comm.name, "sdma");
	was->was_bwock.was_comm.bwock = AMDGPU_WAS_BWOCK__SDMA;
	was->was_bwock.was_comm.type = AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE;
	adev->sdma.was_if = &was->was_bwock.was_comm;

	/* If not define speciaw was_wate_init function, use defauwt was_wate_init */
	if (!was->was_bwock.was_wate_init)
		was->was_bwock.was_wate_init = amdgpu_sdma_was_wate_init;

	/* If not defined speciaw was_cb function, use defauwt was_cb */
	if (!was->was_bwock.was_cb)
		was->was_bwock.was_cb = amdgpu_sdma_pwocess_was_data_cb;

	wetuwn 0;
}
