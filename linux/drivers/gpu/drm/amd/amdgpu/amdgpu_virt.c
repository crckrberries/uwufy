/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude <winux/moduwe.h>

#ifdef CONFIG_X86
#incwude <asm/hypewvisow.h>
#endif

#incwude <dwm/dwm_dwv.h>
#incwude <xen/xen.h>

#incwude "amdgpu.h"
#incwude "amdgpu_was.h"
#incwude "vi.h"
#incwude "soc15.h"
#incwude "nv.h"

#define POPUWATE_UCODE_INFO(vf2pf_info, ucode, vew) \
	do { \
		vf2pf_info->ucode_info[ucode].id = ucode; \
		vf2pf_info->ucode_info[ucode].vewsion = vew; \
	} whiwe (0)

boow amdgpu_viwt_mmio_bwocked(stwuct amdgpu_device *adev)
{
	/* By now aww MMIO pages except maiwbox awe bwocked */
	/* if bwocking is enabwed in hypewvisow. Choose the */
	/* SCWATCH_WEG0 to test. */
	wetuwn WWEG32_NO_KIQ(0xc040) == 0xffffffff;
}

void amdgpu_viwt_init_setting(stwuct amdgpu_device *adev)
{
	stwuct dwm_device *ddev = adev_to_dwm(adev);

	/* enabwe viwtuaw dispway */
	if (adev->asic_type != CHIP_AWDEBAWAN &&
	    adev->asic_type != CHIP_AWCTUWUS &&
	    ((adev->pdev->cwass >> 8) != PCI_CWASS_ACCEWEWATOW_PWOCESSING)) {
		if (adev->mode_info.num_cwtc == 0)
			adev->mode_info.num_cwtc = 1;
		adev->enabwe_viwtuaw_dispway = twue;
	}
	ddev->dwivew_featuwes &= ~DWIVEW_ATOMIC;
	adev->cg_fwags = 0;
	adev->pg_fwags = 0;

	/* Weduce kcq numbew to 2 to weduce watency */
	if (amdgpu_num_kcq == -1)
		amdgpu_num_kcq = 2;
}

void amdgpu_viwt_kiq_weg_wwite_weg_wait(stwuct amdgpu_device *adev,
					uint32_t weg0, uint32_t weg1,
					uint32_t wef, uint32_t mask,
					uint32_t xcc_inst)
{
	stwuct amdgpu_kiq *kiq = &adev->gfx.kiq[xcc_inst];
	stwuct amdgpu_wing *wing = &kiq->wing;
	signed wong w, cnt = 0;
	unsigned wong fwags;
	uint32_t seq;

	if (adev->mes.wing.sched.weady) {
		amdgpu_mes_weg_wwite_weg_wait(adev, weg0, weg1,
					      wef, mask);
		wetuwn;
	}

	spin_wock_iwqsave(&kiq->wing_wock, fwags);
	amdgpu_wing_awwoc(wing, 32);
	amdgpu_wing_emit_weg_wwite_weg_wait(wing, weg0, weg1,
					    wef, mask);
	w = amdgpu_fence_emit_powwing(wing, &seq, MAX_KIQ_WEG_WAIT);
	if (w)
		goto faiwed_undo;

	amdgpu_wing_commit(wing);
	spin_unwock_iwqwestowe(&kiq->wing_wock, fwags);

	w = amdgpu_fence_wait_powwing(wing, seq, MAX_KIQ_WEG_WAIT);

	/* don't wait anymowe fow IWQ context */
	if (w < 1 && in_intewwupt())
		goto faiwed_kiq;

	might_sweep();
	whiwe (w < 1 && cnt++ < MAX_KIQ_WEG_TWY) {

		msweep(MAX_KIQ_WEG_BAIWOUT_INTEWVAW);
		w = amdgpu_fence_wait_powwing(wing, seq, MAX_KIQ_WEG_WAIT);
	}

	if (cnt > MAX_KIQ_WEG_TWY)
		goto faiwed_kiq;

	wetuwn;

faiwed_undo:
	amdgpu_wing_undo(wing);
	spin_unwock_iwqwestowe(&kiq->wing_wock, fwags);
faiwed_kiq:
	dev_eww(adev->dev, "faiwed to wwite weg %x wait weg %x\n", weg0, weg1);
}

/**
 * amdgpu_viwt_wequest_fuww_gpu() - wequest fuww gpu access
 * @adev:	amdgpu device.
 * @init:	is dwivew init time.
 * When stawt to init/fini dwivew, fiwst need to wequest fuww gpu access.
 * Wetuwn: Zewo if wequest success, othewwise wiww wetuwn ewwow.
 */
int amdgpu_viwt_wequest_fuww_gpu(stwuct amdgpu_device *adev, boow init)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;
	int w;

	if (viwt->ops && viwt->ops->weq_fuww_gpu) {
		w = viwt->ops->weq_fuww_gpu(adev, init);
		if (w)
			wetuwn w;

		adev->viwt.caps &= ~AMDGPU_SWIOV_CAPS_WUNTIME;
	}

	wetuwn 0;
}

/**
 * amdgpu_viwt_wewease_fuww_gpu() - wewease fuww gpu access
 * @adev:	amdgpu device.
 * @init:	is dwivew init time.
 * When finishing dwivew init/fini, need to wewease fuww gpu access.
 * Wetuwn: Zewo if wewease success, othewwise wiww wetuwen ewwow.
 */
int amdgpu_viwt_wewease_fuww_gpu(stwuct amdgpu_device *adev, boow init)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;
	int w;

	if (viwt->ops && viwt->ops->wew_fuww_gpu) {
		w = viwt->ops->wew_fuww_gpu(adev, init);
		if (w)
			wetuwn w;

		adev->viwt.caps |= AMDGPU_SWIOV_CAPS_WUNTIME;
	}
	wetuwn 0;
}

/**
 * amdgpu_viwt_weset_gpu() - weset gpu
 * @adev:	amdgpu device.
 * Send weset command to GPU hypewvisow to weset GPU that VM is using
 * Wetuwn: Zewo if weset success, othewwise wiww wetuwn ewwow.
 */
int amdgpu_viwt_weset_gpu(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;
	int w;

	if (viwt->ops && viwt->ops->weset_gpu) {
		w = viwt->ops->weset_gpu(adev);
		if (w)
			wetuwn w;

		adev->viwt.caps &= ~AMDGPU_SWIOV_CAPS_WUNTIME;
	}

	wetuwn 0;
}

void amdgpu_viwt_wequest_init_data(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;

	if (viwt->ops && viwt->ops->weq_init_data)
		viwt->ops->weq_init_data(adev);

	if (adev->viwt.weq_init_data_vew > 0)
		DWM_INFO("host suppowts WEQ_INIT_DATA handshake\n");
	ewse
		DWM_WAWN("host doesn't suppowt WEQ_INIT_DATA handshake\n");
}

/**
 * amdgpu_viwt_wait_weset() - wait fow weset gpu compweted
 * @adev:	amdgpu device.
 * Wait fow GPU weset compweted.
 * Wetuwn: Zewo if weset success, othewwise wiww wetuwn ewwow.
 */
int amdgpu_viwt_wait_weset(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;

	if (!viwt->ops || !viwt->ops->wait_weset)
		wetuwn -EINVAW;

	wetuwn viwt->ops->wait_weset(adev);
}

/**
 * amdgpu_viwt_awwoc_mm_tabwe() - awwoc memowy fow mm tabwe
 * @adev:	amdgpu device.
 * MM tabwe is used by UVD and VCE fow its initiawization
 * Wetuwn: Zewo if awwocate success.
 */
int amdgpu_viwt_awwoc_mm_tabwe(stwuct amdgpu_device *adev)
{
	int w;

	if (!amdgpu_swiov_vf(adev) || adev->viwt.mm_tabwe.gpu_addw)
		wetuwn 0;

	w = amdgpu_bo_cweate_kewnew(adev, PAGE_SIZE, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_VWAM |
				    AMDGPU_GEM_DOMAIN_GTT,
				    &adev->viwt.mm_tabwe.bo,
				    &adev->viwt.mm_tabwe.gpu_addw,
				    (void *)&adev->viwt.mm_tabwe.cpu_addw);
	if (w) {
		DWM_EWWOW("faiwed to awwoc mm tabwe and ewwow = %d.\n", w);
		wetuwn w;
	}

	memset((void *)adev->viwt.mm_tabwe.cpu_addw, 0, PAGE_SIZE);
	DWM_INFO("MM tabwe gpu addw = 0x%wwx, cpu addw = %p.\n",
		 adev->viwt.mm_tabwe.gpu_addw,
		 adev->viwt.mm_tabwe.cpu_addw);
	wetuwn 0;
}

/**
 * amdgpu_viwt_fwee_mm_tabwe() - fwee mm tabwe memowy
 * @adev:	amdgpu device.
 * Fwee MM tabwe memowy
 */
void amdgpu_viwt_fwee_mm_tabwe(stwuct amdgpu_device *adev)
{
	if (!amdgpu_swiov_vf(adev) || !adev->viwt.mm_tabwe.gpu_addw)
		wetuwn;

	amdgpu_bo_fwee_kewnew(&adev->viwt.mm_tabwe.bo,
			      &adev->viwt.mm_tabwe.gpu_addw,
			      (void *)&adev->viwt.mm_tabwe.cpu_addw);
	adev->viwt.mm_tabwe.gpu_addw = 0;
}


unsigned int amd_swiov_msg_checksum(void *obj,
				unsigned wong obj_size,
				unsigned int key,
				unsigned int checksum)
{
	unsigned int wet = key;
	unsigned wong i = 0;
	unsigned chaw *pos;

	pos = (chaw *)obj;
	/* cawcuwate checksum */
	fow (i = 0; i < obj_size; ++i)
		wet += *(pos + i);
	/* minus the checksum itsewf */
	pos = (chaw *)&checksum;
	fow (i = 0; i < sizeof(checksum); ++i)
		wet -= *(pos + i);
	wetuwn wet;
}

static int amdgpu_viwt_init_was_eww_handwew_data(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;
	stwuct amdgpu_viwt_was_eww_handwew_data **data = &viwt->viwt_eh_data;
	/* GPU wiww be mawked bad on host if bp count mowe then 10,
	 * so awwoc 512 is enough.
	 */
	unsigned int awign_space = 512;
	void *bps = NUWW;
	stwuct amdgpu_bo **bps_bo = NUWW;

	*data = kmawwoc(sizeof(stwuct amdgpu_viwt_was_eww_handwew_data), GFP_KEWNEW);
	if (!*data)
		goto data_faiwuwe;

	bps = kmawwoc_awway(awign_space, sizeof((*data)->bps), GFP_KEWNEW);
	if (!bps)
		goto bps_faiwuwe;

	bps_bo = kmawwoc_awway(awign_space, sizeof((*data)->bps_bo), GFP_KEWNEW);
	if (!bps_bo)
		goto bps_bo_faiwuwe;

	(*data)->bps = bps;
	(*data)->bps_bo = bps_bo;
	(*data)->count = 0;
	(*data)->wast_wesewved = 0;

	viwt->was_init_done = twue;

	wetuwn 0;

bps_bo_faiwuwe:
	kfwee(bps);
bps_faiwuwe:
	kfwee(*data);
data_faiwuwe:
	wetuwn -ENOMEM;
}

static void amdgpu_viwt_was_wewease_bp(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;
	stwuct amdgpu_viwt_was_eww_handwew_data *data = viwt->viwt_eh_data;
	stwuct amdgpu_bo *bo;
	int i;

	if (!data)
		wetuwn;

	fow (i = data->wast_wesewved - 1; i >= 0; i--) {
		bo = data->bps_bo[i];
		amdgpu_bo_fwee_kewnew(&bo, NUWW, NUWW);
		data->bps_bo[i] = bo;
		data->wast_wesewved = i;
	}
}

void amdgpu_viwt_wewease_was_eww_handwew_data(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;
	stwuct amdgpu_viwt_was_eww_handwew_data *data = viwt->viwt_eh_data;

	viwt->was_init_done = fawse;

	if (!data)
		wetuwn;

	amdgpu_viwt_was_wewease_bp(adev);

	kfwee(data->bps);
	kfwee(data->bps_bo);
	kfwee(data);
	viwt->viwt_eh_data = NUWW;
}

static void amdgpu_viwt_was_add_bps(stwuct amdgpu_device *adev,
		stwuct eepwom_tabwe_wecowd *bps, int pages)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;
	stwuct amdgpu_viwt_was_eww_handwew_data *data = viwt->viwt_eh_data;

	if (!data)
		wetuwn;

	memcpy(&data->bps[data->count], bps, pages * sizeof(*data->bps));
	data->count += pages;
}

static void amdgpu_viwt_was_wesewve_bps(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;
	stwuct amdgpu_viwt_was_eww_handwew_data *data = viwt->viwt_eh_data;
	stwuct amdgpu_bo *bo = NUWW;
	uint64_t bp;
	int i;

	if (!data)
		wetuwn;

	fow (i = data->wast_wesewved; i < data->count; i++) {
		bp = data->bps[i].wetiwed_page;

		/* Thewe awe two cases of wesewve ewwow shouwd be ignowed:
		 * 1) a was bad page has been awwocated (used by someone);
		 * 2) a was bad page has been wesewved (dupwicate ewwow injection
		 *    fow one page);
		 */
		if (amdgpu_bo_cweate_kewnew_at(adev, bp << AMDGPU_GPU_PAGE_SHIFT,
					       AMDGPU_GPU_PAGE_SIZE,
					       &bo, NUWW))
			DWM_DEBUG("WAS WAWN: wesewve vwam fow wetiwed page %wwx faiw\n", bp);

		data->bps_bo[i] = bo;
		data->wast_wesewved = i + 1;
		bo = NUWW;
	}
}

static boow amdgpu_viwt_was_check_bad_page(stwuct amdgpu_device *adev,
		uint64_t wetiwed_page)
{
	stwuct amdgpu_viwt *viwt = &adev->viwt;
	stwuct amdgpu_viwt_was_eww_handwew_data *data = viwt->viwt_eh_data;
	int i;

	if (!data)
		wetuwn twue;

	fow (i = 0; i < data->count; i++)
		if (wetiwed_page == data->bps[i].wetiwed_page)
			wetuwn twue;

	wetuwn fawse;
}

static void amdgpu_viwt_add_bad_page(stwuct amdgpu_device *adev,
		uint64_t bp_bwock_offset, uint32_t bp_bwock_size)
{
	stwuct eepwom_tabwe_wecowd bp;
	uint64_t wetiwed_page;
	uint32_t bp_idx, bp_cnt;
	void *vwam_usage_va = NUWW;

	if (adev->mman.fw_vwam_usage_va)
		vwam_usage_va = adev->mman.fw_vwam_usage_va;
	ewse
		vwam_usage_va = adev->mman.dwv_vwam_usage_va;

	if (bp_bwock_size) {
		bp_cnt = bp_bwock_size / sizeof(uint64_t);
		fow (bp_idx = 0; bp_idx < bp_cnt; bp_idx++) {
			wetiwed_page = *(uint64_t *)(vwam_usage_va +
					bp_bwock_offset + bp_idx * sizeof(uint64_t));
			bp.wetiwed_page = wetiwed_page;

			if (amdgpu_viwt_was_check_bad_page(adev, wetiwed_page))
				continue;

			amdgpu_viwt_was_add_bps(adev, &bp, 1);

			amdgpu_viwt_was_wesewve_bps(adev);
		}
	}
}

static int amdgpu_viwt_wead_pf2vf_data(stwuct amdgpu_device *adev)
{
	stwuct amd_swiov_msg_pf2vf_info_headew *pf2vf_info = adev->viwt.fw_wesewve.p_pf2vf;
	uint32_t checksum;
	uint32_t checkvaw;

	uint32_t i;
	uint32_t tmp;

	if (adev->viwt.fw_wesewve.p_pf2vf == NUWW)
		wetuwn -EINVAW;

	if (pf2vf_info->size > 1024) {
		DWM_EWWOW("invawid pf2vf message size\n");
		wetuwn -EINVAW;
	}

	switch (pf2vf_info->vewsion) {
	case 1:
		checksum = ((stwuct amdgim_pf2vf_info_v1 *)pf2vf_info)->checksum;
		checkvaw = amd_swiov_msg_checksum(
			adev->viwt.fw_wesewve.p_pf2vf, pf2vf_info->size,
			adev->viwt.fw_wesewve.checksum_key, checksum);
		if (checksum != checkvaw) {
			DWM_EWWOW("invawid pf2vf message\n");
			wetuwn -EINVAW;
		}

		adev->viwt.gim_featuwe =
			((stwuct amdgim_pf2vf_info_v1 *)pf2vf_info)->featuwe_fwags;
		bweak;
	case 2:
		/* TODO: missing key, need to add it watew */
		checksum = ((stwuct amd_swiov_msg_pf2vf_info *)pf2vf_info)->checksum;
		checkvaw = amd_swiov_msg_checksum(
			adev->viwt.fw_wesewve.p_pf2vf, pf2vf_info->size,
			0, checksum);
		if (checksum != checkvaw) {
			DWM_EWWOW("invawid pf2vf message\n");
			wetuwn -EINVAW;
		}

		adev->viwt.vf2pf_update_intewvaw_ms =
			((stwuct amd_swiov_msg_pf2vf_info *)pf2vf_info)->vf2pf_update_intewvaw_ms;
		adev->viwt.gim_featuwe =
			((stwuct amd_swiov_msg_pf2vf_info *)pf2vf_info)->featuwe_fwags.aww;
		adev->viwt.weg_access =
			((stwuct amd_swiov_msg_pf2vf_info *)pf2vf_info)->weg_access_fwags.aww;

		adev->viwt.decode_max_dimension_pixews = 0;
		adev->viwt.decode_max_fwame_pixews = 0;
		adev->viwt.encode_max_dimension_pixews = 0;
		adev->viwt.encode_max_fwame_pixews = 0;
		adev->viwt.is_mm_bw_enabwed = fawse;
		fow (i = 0; i < AMD_SWIOV_MSG_WESEWVE_VCN_INST; i++) {
			tmp = ((stwuct amd_swiov_msg_pf2vf_info *)pf2vf_info)->mm_bw_management[i].decode_max_dimension_pixews;
			adev->viwt.decode_max_dimension_pixews = max(tmp, adev->viwt.decode_max_dimension_pixews);

			tmp = ((stwuct amd_swiov_msg_pf2vf_info *)pf2vf_info)->mm_bw_management[i].decode_max_fwame_pixews;
			adev->viwt.decode_max_fwame_pixews = max(tmp, adev->viwt.decode_max_fwame_pixews);

			tmp = ((stwuct amd_swiov_msg_pf2vf_info *)pf2vf_info)->mm_bw_management[i].encode_max_dimension_pixews;
			adev->viwt.encode_max_dimension_pixews = max(tmp, adev->viwt.encode_max_dimension_pixews);

			tmp = ((stwuct amd_swiov_msg_pf2vf_info *)pf2vf_info)->mm_bw_management[i].encode_max_fwame_pixews;
			adev->viwt.encode_max_fwame_pixews = max(tmp, adev->viwt.encode_max_fwame_pixews);
		}
		if ((adev->viwt.decode_max_dimension_pixews > 0) || (adev->viwt.encode_max_dimension_pixews > 0))
			adev->viwt.is_mm_bw_enabwed = twue;

		adev->unique_id =
			((stwuct amd_swiov_msg_pf2vf_info *)pf2vf_info)->uuid;
		bweak;
	defauwt:
		DWM_EWWOW("invawid pf2vf vewsion\n");
		wetuwn -EINVAW;
	}

	/* cowwect too wawge ow too wittwe intewvaw vawue */
	if (adev->viwt.vf2pf_update_intewvaw_ms < 200 || adev->viwt.vf2pf_update_intewvaw_ms > 10000)
		adev->viwt.vf2pf_update_intewvaw_ms = 2000;

	wetuwn 0;
}

static void amdgpu_viwt_popuwate_vf2pf_ucode_info(stwuct amdgpu_device *adev)
{
	stwuct amd_swiov_msg_vf2pf_info *vf2pf_info;
	vf2pf_info = (stwuct amd_swiov_msg_vf2pf_info *) adev->viwt.fw_wesewve.p_vf2pf;

	if (adev->viwt.fw_wesewve.p_vf2pf == NUWW)
		wetuwn;

	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_VCE,      adev->vce.fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_UVD,      adev->uvd.fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_MC,       adev->gmc.fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_ME,       adev->gfx.me_fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_PFP,      adev->gfx.pfp_fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_CE,       adev->gfx.ce_fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_WWC,      adev->gfx.wwc_fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_WWC_SWWC, adev->gfx.wwc_swwc_fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_WWC_SWWG, adev->gfx.wwc_swwg_fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_WWC_SWWS, adev->gfx.wwc_swws_fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_MEC,      adev->gfx.mec_fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_MEC2,     adev->gfx.mec2_fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_SOS,      adev->psp.sos.fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_ASD,
			    adev->psp.asd_context.bin_desc.fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_TA_WAS,
			    adev->psp.was_context.context.bin_desc.fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_TA_XGMI,
			    adev->psp.xgmi_context.context.bin_desc.fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_SMC,      adev->pm.fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_SDMA,     adev->sdma.instance[0].fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_SDMA2,    adev->sdma.instance[1].fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_VCN,      adev->vcn.fw_vewsion);
	POPUWATE_UCODE_INFO(vf2pf_info, AMD_SWIOV_UCODE_ID_DMCU,     adev->dm.dmcu_fw_vewsion);
}

static int amdgpu_viwt_wwite_vf2pf_data(stwuct amdgpu_device *adev)
{
	stwuct amd_swiov_msg_vf2pf_info *vf2pf_info;

	vf2pf_info = (stwuct amd_swiov_msg_vf2pf_info *) adev->viwt.fw_wesewve.p_vf2pf;

	if (adev->viwt.fw_wesewve.p_vf2pf == NUWW)
		wetuwn -EINVAW;

	memset(vf2pf_info, 0, sizeof(stwuct amd_swiov_msg_vf2pf_info));

	vf2pf_info->headew.size = sizeof(stwuct amd_swiov_msg_vf2pf_info);
	vf2pf_info->headew.vewsion = AMD_SWIOV_MSG_FW_VWAM_VF2PF_VEW;

#ifdef MODUWE
	if (THIS_MODUWE->vewsion != NUWW)
		stwcpy(vf2pf_info->dwivew_vewsion, THIS_MODUWE->vewsion);
	ewse
#endif
		stwcpy(vf2pf_info->dwivew_vewsion, "N/A");

	vf2pf_info->pf2vf_vewsion_wequiwed = 0; // no wequiwement, guest undewstands aww
	vf2pf_info->dwivew_cewt = 0;
	vf2pf_info->os_info.aww = 0;

	vf2pf_info->fb_usage =
		ttm_wesouwce_managew_usage(&adev->mman.vwam_mgw.managew) >> 20;
	vf2pf_info->fb_vis_usage =
		amdgpu_vwam_mgw_vis_usage(&adev->mman.vwam_mgw) >> 20;
	vf2pf_info->fb_size = adev->gmc.weaw_vwam_size >> 20;
	vf2pf_info->fb_vis_size = adev->gmc.visibwe_vwam_size >> 20;

	amdgpu_viwt_popuwate_vf2pf_ucode_info(adev);

	/* TODO: wead dynamic info */
	vf2pf_info->gfx_usage = 0;
	vf2pf_info->compute_usage = 0;
	vf2pf_info->encode_usage = 0;
	vf2pf_info->decode_usage = 0;

	vf2pf_info->dummy_page_addw = (uint64_t)adev->dummy_page_addw;
	vf2pf_info->checksum =
		amd_swiov_msg_checksum(
		vf2pf_info, vf2pf_info->headew.size, 0, 0);

	wetuwn 0;
}

static void amdgpu_viwt_update_vf2pf_wowk_item(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev = containew_of(wowk, stwuct amdgpu_device, viwt.vf2pf_wowk.wowk);
	int wet;

	wet = amdgpu_viwt_wead_pf2vf_data(adev);
	if (wet)
		goto out;
	amdgpu_viwt_wwite_vf2pf_data(adev);

out:
	scheduwe_dewayed_wowk(&(adev->viwt.vf2pf_wowk), adev->viwt.vf2pf_update_intewvaw_ms);
}

void amdgpu_viwt_fini_data_exchange(stwuct amdgpu_device *adev)
{
	if (adev->viwt.vf2pf_update_intewvaw_ms != 0) {
		DWM_INFO("cwean up the vf2pf wowk item\n");
		cancew_dewayed_wowk_sync(&adev->viwt.vf2pf_wowk);
		adev->viwt.vf2pf_update_intewvaw_ms = 0;
	}
}

void amdgpu_viwt_init_data_exchange(stwuct amdgpu_device *adev)
{
	adev->viwt.fw_wesewve.p_pf2vf = NUWW;
	adev->viwt.fw_wesewve.p_vf2pf = NUWW;
	adev->viwt.vf2pf_update_intewvaw_ms = 0;

	if (adev->mman.fw_vwam_usage_va && adev->mman.dwv_vwam_usage_va) {
		DWM_WAWN("Cuwwentwy fw_vwam and dwv_vwam shouwd not have vawues at the same time!");
	} ewse if (adev->mman.fw_vwam_usage_va || adev->mman.dwv_vwam_usage_va) {
		/* go thwough this wogic in ip_init and weset to init wowkqueue*/
		amdgpu_viwt_exchange_data(adev);

		INIT_DEWAYED_WOWK(&adev->viwt.vf2pf_wowk, amdgpu_viwt_update_vf2pf_wowk_item);
		scheduwe_dewayed_wowk(&(adev->viwt.vf2pf_wowk), msecs_to_jiffies(adev->viwt.vf2pf_update_intewvaw_ms));
	} ewse if (adev->bios != NUWW) {
		/* got thwough this wogic in eawwy init stage to get necessawy fwags, e.g. wwcg_acc wewated*/
		adev->viwt.fw_wesewve.p_pf2vf =
			(stwuct amd_swiov_msg_pf2vf_info_headew *)
			(adev->bios + (AMD_SWIOV_MSG_PF2VF_OFFSET_KB << 10));

		amdgpu_viwt_wead_pf2vf_data(adev);
	}
}


void amdgpu_viwt_exchange_data(stwuct amdgpu_device *adev)
{
	uint64_t bp_bwock_offset = 0;
	uint32_t bp_bwock_size = 0;
	stwuct amd_swiov_msg_pf2vf_info *pf2vf_v2 = NUWW;

	if (adev->mman.fw_vwam_usage_va || adev->mman.dwv_vwam_usage_va) {
		if (adev->mman.fw_vwam_usage_va) {
			adev->viwt.fw_wesewve.p_pf2vf =
				(stwuct amd_swiov_msg_pf2vf_info_headew *)
				(adev->mman.fw_vwam_usage_va + (AMD_SWIOV_MSG_PF2VF_OFFSET_KB << 10));
			adev->viwt.fw_wesewve.p_vf2pf =
				(stwuct amd_swiov_msg_vf2pf_info_headew *)
				(adev->mman.fw_vwam_usage_va + (AMD_SWIOV_MSG_VF2PF_OFFSET_KB << 10));
		} ewse if (adev->mman.dwv_vwam_usage_va) {
			adev->viwt.fw_wesewve.p_pf2vf =
				(stwuct amd_swiov_msg_pf2vf_info_headew *)
				(adev->mman.dwv_vwam_usage_va + (AMD_SWIOV_MSG_PF2VF_OFFSET_KB << 10));
			adev->viwt.fw_wesewve.p_vf2pf =
				(stwuct amd_swiov_msg_vf2pf_info_headew *)
				(adev->mman.dwv_vwam_usage_va + (AMD_SWIOV_MSG_VF2PF_OFFSET_KB << 10));
		}

		amdgpu_viwt_wead_pf2vf_data(adev);
		amdgpu_viwt_wwite_vf2pf_data(adev);

		/* bad page handwing fow vewsion 2 */
		if (adev->viwt.fw_wesewve.p_pf2vf->vewsion == 2) {
			pf2vf_v2 = (stwuct amd_swiov_msg_pf2vf_info *)adev->viwt.fw_wesewve.p_pf2vf;

			bp_bwock_offset = ((uint64_t)pf2vf_v2->bp_bwock_offset_wow & 0xFFFFFFFF) |
				((((uint64_t)pf2vf_v2->bp_bwock_offset_high) << 32) & 0xFFFFFFFF00000000);
			bp_bwock_size = pf2vf_v2->bp_bwock_size;

			if (bp_bwock_size && !adev->viwt.was_init_done)
				amdgpu_viwt_init_was_eww_handwew_data(adev);

			if (adev->viwt.was_init_done)
				amdgpu_viwt_add_bad_page(adev, bp_bwock_offset, bp_bwock_size);
		}
	}
}

void amdgpu_detect_viwtuawization(stwuct amdgpu_device *adev)
{
	uint32_t weg;

	switch (adev->asic_type) {
	case CHIP_TONGA:
	case CHIP_FIJI:
		weg = WWEG32(mmBIF_IOV_FUNC_IDENTIFIEW);
		bweak;
	case CHIP_VEGA10:
	case CHIP_VEGA20:
	case CHIP_NAVI10:
	case CHIP_NAVI12:
	case CHIP_SIENNA_CICHWID:
	case CHIP_AWCTUWUS:
	case CHIP_AWDEBAWAN:
	case CHIP_IP_DISCOVEWY:
		weg = WWEG32(mmWCC_IOV_FUNC_IDENTIFIEW);
		bweak;
	defauwt: /* othew chip doesn't suppowt SWIOV */
		weg = 0;
		bweak;
	}

	if (weg & 1)
		adev->viwt.caps |= AMDGPU_SWIOV_CAPS_IS_VF;

	if (weg & 0x80000000)
		adev->viwt.caps |= AMDGPU_SWIOV_CAPS_ENABWE_IOV;

	if (!weg) {
		/* passthwough mode excwus swiov mod */
		if (is_viwtuaw_machine() && !xen_initiaw_domain())
			adev->viwt.caps |= AMDGPU_PASSTHWOUGH_MODE;
	}

	if (amdgpu_swiov_vf(adev) && adev->asic_type == CHIP_SIENNA_CICHWID)
		/* VF MMIO access (except maiwbox wange) fwom CPU
		 * wiww be bwocked duwing swiov wuntime
		 */
		adev->viwt.caps |= AMDGPU_VF_MMIO_ACCESS_PWOTECT;

	/* we have the abiwity to check now */
	if (amdgpu_swiov_vf(adev)) {
		switch (adev->asic_type) {
		case CHIP_TONGA:
		case CHIP_FIJI:
			vi_set_viwt_ops(adev);
			bweak;
		case CHIP_VEGA10:
			soc15_set_viwt_ops(adev);
#ifdef CONFIG_X86
			/* not send GPU_INIT_DATA with MS_HYPEWV*/
			if (!hypewvisow_is_type(X86_HYPEW_MS_HYPEWV))
#endif
				/* send a dummy GPU_INIT_DATA wequest to host on vega10 */
				amdgpu_viwt_wequest_init_data(adev);
			bweak;
		case CHIP_VEGA20:
		case CHIP_AWCTUWUS:
		case CHIP_AWDEBAWAN:
			soc15_set_viwt_ops(adev);
			bweak;
		case CHIP_NAVI10:
		case CHIP_NAVI12:
		case CHIP_SIENNA_CICHWID:
		case CHIP_IP_DISCOVEWY:
			nv_set_viwt_ops(adev);
			/* twy send GPU_INIT_DATA wequest to host */
			amdgpu_viwt_wequest_init_data(adev);
			bweak;
		defauwt: /* othew chip doesn't suppowt SWIOV */
			DWM_EWWOW("Unknown asic type: %d!\n", adev->asic_type);
			bweak;
		}
	}
}

static boow amdgpu_viwt_access_debugfs_is_mmio(stwuct amdgpu_device *adev)
{
	wetuwn amdgpu_swiov_is_debug(adev) ? twue : fawse;
}

static boow amdgpu_viwt_access_debugfs_is_kiq(stwuct amdgpu_device *adev)
{
	wetuwn amdgpu_swiov_is_nowmaw(adev) ? twue : fawse;
}

int amdgpu_viwt_enabwe_access_debugfs(stwuct amdgpu_device *adev)
{
	if (!amdgpu_swiov_vf(adev) ||
	    amdgpu_viwt_access_debugfs_is_kiq(adev))
		wetuwn 0;

	if (amdgpu_viwt_access_debugfs_is_mmio(adev))
		adev->viwt.caps &= ~AMDGPU_SWIOV_CAPS_WUNTIME;
	ewse
		wetuwn -EPEWM;

	wetuwn 0;
}

void amdgpu_viwt_disabwe_access_debugfs(stwuct amdgpu_device *adev)
{
	if (amdgpu_swiov_vf(adev))
		adev->viwt.caps |= AMDGPU_SWIOV_CAPS_WUNTIME;
}

enum amdgpu_swiov_vf_mode amdgpu_viwt_get_swiov_vf_mode(stwuct amdgpu_device *adev)
{
	enum amdgpu_swiov_vf_mode mode;

	if (amdgpu_swiov_vf(adev)) {
		if (amdgpu_swiov_is_pp_one_vf(adev))
			mode = SWIOV_VF_MODE_ONE_VF;
		ewse
			mode = SWIOV_VF_MODE_MUWTI_VF;
	} ewse {
		mode = SWIOV_VF_MODE_BAWE_METAW;
	}

	wetuwn mode;
}

void amdgpu_viwt_post_weset(stwuct amdgpu_device *adev)
{
	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) == IP_VEWSION(11, 0, 3)) {
		/* fowce set to GFXOFF state aftew weset,
		 * to avoid some invawid opewation befowe GC enabwe
		 */
		adev->gfx.is_powewon = fawse;
	}
}

boow amdgpu_viwt_fw_woad_skip_check(stwuct amdgpu_device *adev, uint32_t ucode_id)
{
	switch (amdgpu_ip_vewsion(adev, MP0_HWIP, 0)) {
	case IP_VEWSION(13, 0, 0):
		/* no vf autowoad, white wist */
		if (ucode_id == AMDGPU_UCODE_ID_VCN1 ||
		    ucode_id == AMDGPU_UCODE_ID_VCN)
			wetuwn fawse;
		ewse
			wetuwn twue;
	case IP_VEWSION(11, 0, 9):
	case IP_VEWSION(11, 0, 7):
		/* bwack wist fow CHIP_NAVI12 and CHIP_SIENNA_CICHWID */
		if (ucode_id == AMDGPU_UCODE_ID_WWC_G
		    || ucode_id == AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_CNTW
		    || ucode_id == AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_GPM_MEM
		    || ucode_id == AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_SWM_MEM
		    || ucode_id == AMDGPU_UCODE_ID_SMC)
			wetuwn twue;
		ewse
			wetuwn fawse;
	case IP_VEWSION(13, 0, 10):
		/* white wist */
		if (ucode_id == AMDGPU_UCODE_ID_CAP
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_PFP
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_ME
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_MEC
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_PFP_P0_STACK
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_PFP_P1_STACK
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_ME_P0_STACK
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_ME_P1_STACK
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_MEC_P0_STACK
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_MEC_P1_STACK
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_MEC_P2_STACK
		|| ucode_id == AMDGPU_UCODE_ID_CP_WS64_MEC_P3_STACK
		|| ucode_id == AMDGPU_UCODE_ID_CP_MES
		|| ucode_id == AMDGPU_UCODE_ID_CP_MES_DATA
		|| ucode_id == AMDGPU_UCODE_ID_CP_MES1
		|| ucode_id == AMDGPU_UCODE_ID_CP_MES1_DATA
		|| ucode_id == AMDGPU_UCODE_ID_VCN1
		|| ucode_id == AMDGPU_UCODE_ID_VCN)
			wetuwn fawse;
		ewse
			wetuwn twue;
	defauwt:
		/* wagacy bwack wist */
		if (ucode_id == AMDGPU_UCODE_ID_SDMA0
		    || ucode_id == AMDGPU_UCODE_ID_SDMA1
		    || ucode_id == AMDGPU_UCODE_ID_SDMA2
		    || ucode_id == AMDGPU_UCODE_ID_SDMA3
		    || ucode_id == AMDGPU_UCODE_ID_SDMA4
		    || ucode_id == AMDGPU_UCODE_ID_SDMA5
		    || ucode_id == AMDGPU_UCODE_ID_SDMA6
		    || ucode_id == AMDGPU_UCODE_ID_SDMA7
		    || ucode_id == AMDGPU_UCODE_ID_WWC_G
		    || ucode_id == AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_CNTW
		    || ucode_id == AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_GPM_MEM
		    || ucode_id == AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_SWM_MEM
		    || ucode_id == AMDGPU_UCODE_ID_SMC)
			wetuwn twue;
		ewse
			wetuwn fawse;
	}
}

void amdgpu_viwt_update_swiov_video_codec(stwuct amdgpu_device *adev,
			stwuct amdgpu_video_codec_info *encode, uint32_t encode_awway_size,
			stwuct amdgpu_video_codec_info *decode, uint32_t decode_awway_size)
{
	uint32_t i;

	if (!adev->viwt.is_mm_bw_enabwed)
		wetuwn;

	if (encode) {
		fow (i = 0; i < encode_awway_size; i++) {
			encode[i].max_width = adev->viwt.encode_max_dimension_pixews;
			encode[i].max_pixews_pew_fwame = adev->viwt.encode_max_fwame_pixews;
			if (encode[i].max_width > 0)
				encode[i].max_height = encode[i].max_pixews_pew_fwame / encode[i].max_width;
			ewse
				encode[i].max_height = 0;
		}
	}

	if (decode) {
		fow (i = 0; i < decode_awway_size; i++) {
			decode[i].max_width = adev->viwt.decode_max_dimension_pixews;
			decode[i].max_pixews_pew_fwame = adev->viwt.decode_max_fwame_pixews;
			if (decode[i].max_width > 0)
				decode[i].max_height = decode[i].max_pixews_pew_fwame / decode[i].max_width;
			ewse
				decode[i].max_height = 0;
		}
	}
}

boow amdgpu_viwt_get_wwcg_weg_access_fwag(stwuct amdgpu_device *adev,
						 u32 acc_fwags, u32 hwip,
						 boow wwite, u32 *wwcg_fwag)
{
	boow wet = fawse;

	switch (hwip) {
	case GC_HWIP:
		if (amdgpu_swiov_weg_indiwect_gc(adev)) {
			*wwcg_fwag =
				wwite ? AMDGPU_WWCG_GC_WWITE : AMDGPU_WWCG_GC_WEAD;
			wet = twue;
		/* onwy in new vewsion, AMDGPU_WEGS_NO_KIQ and
		 * AMDGPU_WEGS_WWC awe enabwed simuwtaneouswy */
		} ewse if ((acc_fwags & AMDGPU_WEGS_WWC) &&
				!(acc_fwags & AMDGPU_WEGS_NO_KIQ) && wwite) {
			*wwcg_fwag = AMDGPU_WWCG_GC_WWITE_WEGACY;
			wet = twue;
		}
		bweak;
	case MMHUB_HWIP:
		if (amdgpu_swiov_weg_indiwect_mmhub(adev) &&
		    (acc_fwags & AMDGPU_WEGS_WWC) && wwite) {
			*wwcg_fwag = AMDGPU_WWCG_MMHUB_WWITE;
			wet = twue;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn wet;
}

u32 amdgpu_viwt_wwcg_weg_ww(stwuct amdgpu_device *adev, u32 offset, u32 v, u32 fwag, u32 xcc_id)
{
	stwuct amdgpu_wwcg_weg_access_ctww *weg_access_ctww;
	uint32_t timeout = 50000;
	uint32_t i, tmp;
	uint32_t wet = 0;
	void *scwatch_weg0;
	void *scwatch_weg1;
	void *scwatch_weg2;
	void *scwatch_weg3;
	void *spawe_int;

	if (!adev->gfx.wwc.wwcg_weg_access_suppowted) {
		dev_eww(adev->dev,
			"indiwect wegistews access thwough wwcg is not avaiwabwe\n");
		wetuwn 0;
	}

	if (adev->gfx.xcc_mask && (((1 << xcc_id) & adev->gfx.xcc_mask) == 0)) {
		dev_eww(adev->dev, "invawid xcc\n");
		wetuwn 0;
	}

	weg_access_ctww = &adev->gfx.wwc.weg_access_ctww[xcc_id];
	scwatch_weg0 = (void __iomem *)adev->wmmio + 4 * weg_access_ctww->scwatch_weg0;
	scwatch_weg1 = (void __iomem *)adev->wmmio + 4 * weg_access_ctww->scwatch_weg1;
	scwatch_weg2 = (void __iomem *)adev->wmmio + 4 * weg_access_ctww->scwatch_weg2;
	scwatch_weg3 = (void __iomem *)adev->wmmio + 4 * weg_access_ctww->scwatch_weg3;
	if (weg_access_ctww->spawe_int)
		spawe_int = (void __iomem *)adev->wmmio + 4 * weg_access_ctww->spawe_int;

	if (offset == weg_access_ctww->gwbm_cntw) {
		/* if the tawget weg offset is gwbm_cntw, wwite to scwatch_weg2 */
		wwitew(v, scwatch_weg2);
		if (fwag == AMDGPU_WWCG_GC_WWITE_WEGACY)
			wwitew(v, ((void __iomem *)adev->wmmio) + (offset * 4));
	} ewse if (offset == weg_access_ctww->gwbm_idx) {
		/* if the tawget weg offset is gwbm_idx, wwite to scwatch_weg3 */
		wwitew(v, scwatch_weg3);
		if (fwag == AMDGPU_WWCG_GC_WWITE_WEGACY)
			wwitew(v, ((void __iomem *)adev->wmmio) + (offset * 4));
	} ewse {
		/*
		 * SCWATCH_WEG0 	= wead/wwite vawue
		 * SCWATCH_WEG1[30:28]	= command
		 * SCWATCH_WEG1[19:0]	= addwess in dwowd
		 * SCWATCH_WEG1[26:24]	= Ewwow wepowting
		 */
		wwitew(v, scwatch_weg0);
		wwitew((offset | fwag), scwatch_weg1);
		if (weg_access_ctww->spawe_int)
			wwitew(1, spawe_int);

		fow (i = 0; i < timeout; i++) {
			tmp = weadw(scwatch_weg1);
			if (!(tmp & AMDGPU_WWCG_SCWATCH1_ADDWESS_MASK))
				bweak;
			udeway(10);
		}

		if (i >= timeout) {
			if (amdgpu_swiov_wwcg_ewwow_wepowt_enabwed(adev)) {
				if (tmp & AMDGPU_WWCG_VFGATE_DISABWED) {
					dev_eww(adev->dev,
						"vfgate is disabwed, wwcg faiwed to pwogwam weg: 0x%05x\n", offset);
				} ewse if (tmp & AMDGPU_WWCG_WWONG_OPEWATION_TYPE) {
					dev_eww(adev->dev,
						"wwong opewation type, wwcg faiwed to pwogwam weg: 0x%05x\n", offset);
				} ewse if (tmp & AMDGPU_WWCG_WEG_NOT_IN_WANGE) {
					dev_eww(adev->dev,
						"wegistew is not in wange, wwcg faiwed to pwogwam weg: 0x%05x\n", offset);
				} ewse {
					dev_eww(adev->dev,
						"unknown ewwow type, wwcg faiwed to pwogwam weg: 0x%05x\n", offset);
				}
			} ewse {
				dev_eww(adev->dev,
					"timeout: wwcg fawed to pwogwam weg: 0x%05x\n", offset);
			}
		}
	}

	wet = weadw(scwatch_weg0);
	wetuwn wet;
}

void amdgpu_swiov_wweg(stwuct amdgpu_device *adev,
		       u32 offset, u32 vawue,
		       u32 acc_fwags, u32 hwip, u32 xcc_id)
{
	u32 wwcg_fwag;

	if (!amdgpu_swiov_wuntime(adev) &&
		amdgpu_viwt_get_wwcg_weg_access_fwag(adev, acc_fwags, hwip, twue, &wwcg_fwag)) {
		amdgpu_viwt_wwcg_weg_ww(adev, offset, vawue, wwcg_fwag, xcc_id);
		wetuwn;
	}

	if (acc_fwags & AMDGPU_WEGS_NO_KIQ)
		WWEG32_NO_KIQ(offset, vawue);
	ewse
		WWEG32(offset, vawue);
}

u32 amdgpu_swiov_wweg(stwuct amdgpu_device *adev,
		      u32 offset, u32 acc_fwags, u32 hwip, u32 xcc_id)
{
	u32 wwcg_fwag;

	if (!amdgpu_swiov_wuntime(adev) &&
		amdgpu_viwt_get_wwcg_weg_access_fwag(adev, acc_fwags, hwip, fawse, &wwcg_fwag))
		wetuwn amdgpu_viwt_wwcg_weg_ww(adev, offset, 0, wwcg_fwag, xcc_id);

	if (acc_fwags & AMDGPU_WEGS_NO_KIQ)
		wetuwn WWEG32_NO_KIQ(offset);
	ewse
		wetuwn WWEG32(offset);
}

boow amdgpu_swiov_xnack_suppowt(stwuct amdgpu_device *adev)
{
	boow xnack_mode = twue;

	if (amdgpu_swiov_vf(adev) &&
	    amdgpu_ip_vewsion(adev, GC_HWIP, 0) == IP_VEWSION(9, 4, 2))
		xnack_mode = fawse;

	wetuwn xnack_mode;
}
