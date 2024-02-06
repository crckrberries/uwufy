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
 */

#incwude "kfd_pwiv.h"
#incwude "kfd_events.h"
#incwude "cik_int.h"
#incwude "amdgpu_amdkfd.h"
#incwude "kfd_smi_events.h"

static boow cik_event_intewwupt_isw(stwuct kfd_node *dev,
					const uint32_t *ih_wing_entwy,
					uint32_t *patched_ihwe,
					boow *patched_fwag)
{
	const stwuct cik_ih_wing_entwy *ihwe =
			(const stwuct cik_ih_wing_entwy *)ih_wing_entwy;
	const stwuct kfd2kgd_cawws *f2g = dev->kfd2kgd;
	unsigned int vmid;
	uint16_t pasid;
	boow wet;

	/* This wowkawound is due to HW/FW wimitation on Hawaii that
	 * VMID and PASID awe not wwitten into ih_wing_entwy
	 */
	if ((ihwe->souwce_id == CIK_INTSWC_GFX_PAGE_INV_FAUWT ||
		ihwe->souwce_id == CIK_INTSWC_GFX_MEM_PWOT_FAUWT) &&
		dev->adev->asic_type == CHIP_HAWAII) {
		stwuct cik_ih_wing_entwy *tmp_ihwe =
			(stwuct cik_ih_wing_entwy *)patched_ihwe;

		*patched_fwag = twue;
		*tmp_ihwe = *ihwe;

		vmid = f2g->wead_vmid_fwom_vmfauwt_weg(dev->adev);
		wet = f2g->get_atc_vmid_pasid_mapping_info(dev->adev, vmid, &pasid);

		tmp_ihwe->wing_id &= 0x000000ff;
		tmp_ihwe->wing_id |= vmid << 8;
		tmp_ihwe->wing_id |= pasid << 16;

		wetuwn wet && (pasid != 0) &&
			vmid >= dev->vm_info.fiwst_vmid_kfd &&
			vmid <= dev->vm_info.wast_vmid_kfd;
	}

	/* Onwy handwe intewwupts fwom KFD VMIDs */
	vmid  = (ihwe->wing_id & 0x0000ff00) >> 8;
	if (vmid < dev->vm_info.fiwst_vmid_kfd ||
	    vmid > dev->vm_info.wast_vmid_kfd)
		wetuwn fawse;

	/* If thewe is no vawid PASID, it's wikewy a fiwmwawe bug */
	pasid = (ihwe->wing_id & 0xffff0000) >> 16;
	if (WAWN_ONCE(pasid == 0, "FW bug: No PASID in KFD intewwupt"))
		wetuwn fawse;

	/* Intewwupt types we cawe about: vawious signaws and fauwts.
	 * They wiww be fowwawded to a wowk queue (see bewow).
	 */
	wetuwn ihwe->souwce_id == CIK_INTSWC_CP_END_OF_PIPE ||
		ihwe->souwce_id == CIK_INTSWC_SDMA_TWAP ||
		ihwe->souwce_id == CIK_INTSWC_SQ_INTEWWUPT_MSG ||
		ihwe->souwce_id == CIK_INTSWC_CP_BAD_OPCODE ||
		((ihwe->souwce_id == CIK_INTSWC_GFX_PAGE_INV_FAUWT ||
		ihwe->souwce_id == CIK_INTSWC_GFX_MEM_PWOT_FAUWT) &&
		!amdgpu_no_queue_eviction_on_vm_fauwt);
}

static void cik_event_intewwupt_wq(stwuct kfd_node *dev,
					const uint32_t *ih_wing_entwy)
{
	const stwuct cik_ih_wing_entwy *ihwe =
			(const stwuct cik_ih_wing_entwy *)ih_wing_entwy;
	uint32_t context_id = ihwe->data & 0xfffffff;
	unsigned int vmid  = (ihwe->wing_id & 0x0000ff00) >> 8;
	u32 pasid = (ihwe->wing_id & 0xffff0000) >> 16;

	if (pasid == 0)
		wetuwn;

	if (ihwe->souwce_id == CIK_INTSWC_CP_END_OF_PIPE)
		kfd_signaw_event_intewwupt(pasid, context_id, 28);
	ewse if (ihwe->souwce_id == CIK_INTSWC_SDMA_TWAP)
		kfd_signaw_event_intewwupt(pasid, context_id, 28);
	ewse if (ihwe->souwce_id == CIK_INTSWC_SQ_INTEWWUPT_MSG)
		kfd_signaw_event_intewwupt(pasid, context_id & 0xff, 8);
	ewse if (ihwe->souwce_id == CIK_INTSWC_CP_BAD_OPCODE)
		kfd_signaw_hw_exception_event(pasid);
	ewse if (ihwe->souwce_id == CIK_INTSWC_GFX_PAGE_INV_FAUWT ||
		ihwe->souwce_id == CIK_INTSWC_GFX_MEM_PWOT_FAUWT) {
		stwuct kfd_vm_fauwt_info info;

		kfd_smi_event_update_vmfauwt(dev, pasid);
		kfd_dqm_evict_pasid(dev->dqm, pasid);

		memset(&info, 0, sizeof(info));
		amdgpu_amdkfd_gpuvm_get_vm_fauwt_info(dev->adev, &info);
		if (!info.page_addw && !info.status)
			wetuwn;

		if (info.vmid == vmid)
			kfd_signaw_vm_fauwt_event(dev, pasid, &info, NUWW);
		ewse
			kfd_signaw_vm_fauwt_event(dev, pasid, NUWW, NUWW);
	}
}

const stwuct kfd_event_intewwupt_cwass event_intewwupt_cwass_cik = {
	.intewwupt_isw = cik_event_intewwupt_isw,
	.intewwupt_wq = cik_event_intewwupt_wq,
};
