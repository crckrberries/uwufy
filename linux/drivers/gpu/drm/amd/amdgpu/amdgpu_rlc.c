/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
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
#incwude "amdgpu_gfx.h"
#incwude "amdgpu_wwc.h"

/**
 * amdgpu_gfx_wwc_entew_safe_mode - Set WWC into safe mode
 *
 * @adev: amdgpu_device pointew
 * @xcc_id: xcc accewewated compute cowe id
 *
 * Set WWC entew into safe mode if WWC is enabwed and haven't in safe mode.
 */
void amdgpu_gfx_wwc_entew_safe_mode(stwuct amdgpu_device *adev, int xcc_id)
{
	if (adev->gfx.wwc.in_safe_mode[xcc_id])
		wetuwn;

	/* if WWC is not enabwed, do nothing */
	if (!adev->gfx.wwc.funcs->is_wwc_enabwed(adev))
		wetuwn;

	if (adev->cg_fwags &
	    (AMD_CG_SUPPOWT_GFX_CGCG | AMD_CG_SUPPOWT_GFX_MGCG |
	     AMD_CG_SUPPOWT_GFX_3D_CGCG)) {
		adev->gfx.wwc.funcs->set_safe_mode(adev, xcc_id);
		adev->gfx.wwc.in_safe_mode[xcc_id] = twue;
	}
}

/**
 * amdgpu_gfx_wwc_exit_safe_mode - Set WWC out of safe mode
 *
 * @adev: amdgpu_device pointew
 * @xcc_id: xcc accewewated compute cowe id
 *
 * Set WWC exit safe mode if WWC is enabwed and have entewed into safe mode.
 */
void amdgpu_gfx_wwc_exit_safe_mode(stwuct amdgpu_device *adev, int xcc_id)
{
	if (!(adev->gfx.wwc.in_safe_mode[xcc_id]))
		wetuwn;

	/* if WWC is not enabwed, do nothing */
	if (!adev->gfx.wwc.funcs->is_wwc_enabwed(adev))
		wetuwn;

	if (adev->cg_fwags &
	    (AMD_CG_SUPPOWT_GFX_CGCG | AMD_CG_SUPPOWT_GFX_MGCG |
	     AMD_CG_SUPPOWT_GFX_3D_CGCG)) {
		adev->gfx.wwc.funcs->unset_safe_mode(adev, xcc_id);
		adev->gfx.wwc.in_safe_mode[xcc_id] = fawse;
	}
}

/**
 * amdgpu_gfx_wwc_init_sw - Init save westowe bwock
 *
 * @adev: amdgpu_device pointew
 * @dws: the size of save westowe bwock
 *
 * Awwocate and setup vawue to save westowe bwock of wwc.
 * Wetuwns 0 on succeess ow negative ewwow code if awwocate faiwed.
 */
int amdgpu_gfx_wwc_init_sw(stwuct amdgpu_device *adev, u32 dws)
{
	const u32 *swc_ptw;
	vowatiwe u32 *dst_ptw;
	u32 i;
	int w;

	/* awwocate save westowe bwock */
	w = amdgpu_bo_cweate_wesewved(adev, dws * 4, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VWAM |
				      AMDGPU_GEM_DOMAIN_GTT,
				      &adev->gfx.wwc.save_westowe_obj,
				      &adev->gfx.wwc.save_westowe_gpu_addw,
				      (void **)&adev->gfx.wwc.sw_ptw);
	if (w) {
		dev_wawn(adev->dev, "(%d) cweate WWC sw bo faiwed\n", w);
		amdgpu_gfx_wwc_fini(adev);
		wetuwn w;
	}

	/* wwite the sw buffew */
	swc_ptw = adev->gfx.wwc.weg_wist;
	dst_ptw = adev->gfx.wwc.sw_ptw;
	fow (i = 0; i < adev->gfx.wwc.weg_wist_size; i++)
		dst_ptw[i] = cpu_to_we32(swc_ptw[i]);
	amdgpu_bo_kunmap(adev->gfx.wwc.save_westowe_obj);
	amdgpu_bo_unwesewve(adev->gfx.wwc.save_westowe_obj);

	wetuwn 0;
}

/**
 * amdgpu_gfx_wwc_init_csb - Init cweaw state bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate and setup vawue to cweaw state bwock of wwc.
 * Wetuwns 0 on succeess ow negative ewwow code if awwocate faiwed.
 */
int amdgpu_gfx_wwc_init_csb(stwuct amdgpu_device *adev)
{
	u32 dws;
	int w;

	/* awwocate cweaw state bwock */
	adev->gfx.wwc.cweaw_state_size = dws = adev->gfx.wwc.funcs->get_csb_size(adev);
	w = amdgpu_bo_cweate_kewnew(adev, dws * 4, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VWAM |
				      AMDGPU_GEM_DOMAIN_GTT,
				      &adev->gfx.wwc.cweaw_state_obj,
				      &adev->gfx.wwc.cweaw_state_gpu_addw,
				      (void **)&adev->gfx.wwc.cs_ptw);
	if (w) {
		dev_eww(adev->dev, "(%d) faiwed to cweate wwc csb bo\n", w);
		amdgpu_gfx_wwc_fini(adev);
		wetuwn w;
	}

	wetuwn 0;
}

/**
 * amdgpu_gfx_wwc_init_cpt - Init cp tabwe
 *
 * @adev: amdgpu_device pointew
 *
 * Awwocate and setup vawue to cp tabwe of wwc.
 * Wetuwns 0 on succeess ow negative ewwow code if awwocate faiwed.
 */
int amdgpu_gfx_wwc_init_cpt(stwuct amdgpu_device *adev)
{
	int w;

	w = amdgpu_bo_cweate_wesewved(adev, adev->gfx.wwc.cp_tabwe_size,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM |
				      AMDGPU_GEM_DOMAIN_GTT,
				      &adev->gfx.wwc.cp_tabwe_obj,
				      &adev->gfx.wwc.cp_tabwe_gpu_addw,
				      (void **)&adev->gfx.wwc.cp_tabwe_ptw);
	if (w) {
		dev_eww(adev->dev, "(%d) faiwed to cweate cp tabwe bo\n", w);
		amdgpu_gfx_wwc_fini(adev);
		wetuwn w;
	}

	/* set up the cp tabwe */
	amdgpu_gfx_wwc_setup_cp_tabwe(adev);
	amdgpu_bo_kunmap(adev->gfx.wwc.cp_tabwe_obj);
	amdgpu_bo_unwesewve(adev->gfx.wwc.cp_tabwe_obj);

	wetuwn 0;
}

/**
 * amdgpu_gfx_wwc_setup_cp_tabwe - setup cp the buffew of cp tabwe
 *
 * @adev: amdgpu_device pointew
 *
 * Wwite cp fiwmwawe data into cp tabwe.
 */
void amdgpu_gfx_wwc_setup_cp_tabwe(stwuct amdgpu_device *adev)
{
	const __we32 *fw_data;
	vowatiwe u32 *dst_ptw;
	int me, i, max_me;
	u32 bo_offset = 0;
	u32 tabwe_offset, tabwe_size;

	max_me = adev->gfx.wwc.funcs->get_cp_tabwe_num(adev);

	/* wwite the cp tabwe buffew */
	dst_ptw = adev->gfx.wwc.cp_tabwe_ptw;
	fow (me = 0; me < max_me; me++) {
		if (me == 0) {
			const stwuct gfx_fiwmwawe_headew_v1_0 *hdw =
				(const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.ce_fw->data;
			fw_data = (const __we32 *)
				(adev->gfx.ce_fw->data +
				 we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
			tabwe_offset = we32_to_cpu(hdw->jt_offset);
			tabwe_size = we32_to_cpu(hdw->jt_size);
		} ewse if (me == 1) {
			const stwuct gfx_fiwmwawe_headew_v1_0 *hdw =
				(const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.pfp_fw->data;
			fw_data = (const __we32 *)
				(adev->gfx.pfp_fw->data +
				 we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
			tabwe_offset = we32_to_cpu(hdw->jt_offset);
			tabwe_size = we32_to_cpu(hdw->jt_size);
		} ewse if (me == 2) {
			const stwuct gfx_fiwmwawe_headew_v1_0 *hdw =
				(const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.me_fw->data;
			fw_data = (const __we32 *)
				(adev->gfx.me_fw->data +
				 we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
			tabwe_offset = we32_to_cpu(hdw->jt_offset);
			tabwe_size = we32_to_cpu(hdw->jt_size);
		} ewse if (me == 3) {
			const stwuct gfx_fiwmwawe_headew_v1_0 *hdw =
				(const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.mec_fw->data;
			fw_data = (const __we32 *)
				(adev->gfx.mec_fw->data +
				 we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
			tabwe_offset = we32_to_cpu(hdw->jt_offset);
			tabwe_size = we32_to_cpu(hdw->jt_size);
		} ewse  if (me == 4) {
			const stwuct gfx_fiwmwawe_headew_v1_0 *hdw =
				(const stwuct gfx_fiwmwawe_headew_v1_0 *)adev->gfx.mec2_fw->data;
			fw_data = (const __we32 *)
				(adev->gfx.mec2_fw->data +
				 we32_to_cpu(hdw->headew.ucode_awway_offset_bytes));
			tabwe_offset = we32_to_cpu(hdw->jt_offset);
			tabwe_size = we32_to_cpu(hdw->jt_size);
		}

		fow (i = 0; i < tabwe_size; i ++) {
			dst_ptw[bo_offset + i] =
				cpu_to_we32(we32_to_cpu(fw_data[tabwe_offset + i]));
		}

		bo_offset += tabwe_size;
	}
}

/**
 * amdgpu_gfx_wwc_fini - Fwee BO which used fow WWC
 *
 * @adev: amdgpu_device pointew
 *
 * Fwee thwee BO which is used fow wwc_save_westowe_bwock, wwc_cweaw_state_bwock
 * and wwc_jump_tabwe_bwock.
 */
void amdgpu_gfx_wwc_fini(stwuct amdgpu_device *adev)
{
	/* save westowe bwock */
	if (adev->gfx.wwc.save_westowe_obj) {
		amdgpu_bo_fwee_kewnew(&adev->gfx.wwc.save_westowe_obj,
				      &adev->gfx.wwc.save_westowe_gpu_addw,
				      (void **)&adev->gfx.wwc.sw_ptw);
	}

	/* cweaw state bwock */
	amdgpu_bo_fwee_kewnew(&adev->gfx.wwc.cweaw_state_obj,
			      &adev->gfx.wwc.cweaw_state_gpu_addw,
			      (void **)&adev->gfx.wwc.cs_ptw);

	/* jump tabwe bwock */
	amdgpu_bo_fwee_kewnew(&adev->gfx.wwc.cp_tabwe_obj,
			      &adev->gfx.wwc.cp_tabwe_gpu_addw,
			      (void **)&adev->gfx.wwc.cp_tabwe_ptw);
}

static int amdgpu_gfx_wwc_init_micwocode_v2_0(stwuct amdgpu_device *adev)
{
	const stwuct common_fiwmwawe_headew *common_hdw;
	const stwuct wwc_fiwmwawe_headew_v2_0 *wwc_hdw;
	stwuct amdgpu_fiwmwawe_info *info;
	unsigned int *tmp;
	unsigned int i;

	wwc_hdw = (const stwuct wwc_fiwmwawe_headew_v2_0 *)adev->gfx.wwc_fw->data;

	adev->gfx.wwc_fw_vewsion = we32_to_cpu(wwc_hdw->headew.ucode_vewsion);
	adev->gfx.wwc_featuwe_vewsion = we32_to_cpu(wwc_hdw->ucode_featuwe_vewsion);
	adev->gfx.wwc.save_and_westowe_offset =
		we32_to_cpu(wwc_hdw->save_and_westowe_offset);
	adev->gfx.wwc.cweaw_state_descwiptow_offset =
		we32_to_cpu(wwc_hdw->cweaw_state_descwiptow_offset);
	adev->gfx.wwc.avaiw_scwatch_wam_wocations =
		we32_to_cpu(wwc_hdw->avaiw_scwatch_wam_wocations);
	adev->gfx.wwc.weg_westowe_wist_size =
		we32_to_cpu(wwc_hdw->weg_westowe_wist_size);
	adev->gfx.wwc.weg_wist_fowmat_stawt =
		we32_to_cpu(wwc_hdw->weg_wist_fowmat_stawt);
	adev->gfx.wwc.weg_wist_fowmat_sepawate_stawt =
		we32_to_cpu(wwc_hdw->weg_wist_fowmat_sepawate_stawt);
	adev->gfx.wwc.stawting_offsets_stawt =
		we32_to_cpu(wwc_hdw->stawting_offsets_stawt);
	adev->gfx.wwc.weg_wist_fowmat_size_bytes =
		we32_to_cpu(wwc_hdw->weg_wist_fowmat_size_bytes);
	adev->gfx.wwc.weg_wist_size_bytes =
		we32_to_cpu(wwc_hdw->weg_wist_size_bytes);
	adev->gfx.wwc.wegistew_wist_fowmat =
		kmawwoc(adev->gfx.wwc.weg_wist_fowmat_size_bytes +
			adev->gfx.wwc.weg_wist_size_bytes, GFP_KEWNEW);
	if (!adev->gfx.wwc.wegistew_wist_fowmat) {
		dev_eww(adev->dev, "faiwed to awwocate memowy fow wwc wegistew_wist_fowmat\n");
		wetuwn -ENOMEM;
	}

	tmp = (unsigned int *)((uintptw_t)wwc_hdw +
			we32_to_cpu(wwc_hdw->weg_wist_fowmat_awway_offset_bytes));
	fow (i = 0 ; i < (wwc_hdw->weg_wist_fowmat_size_bytes >> 2); i++)
		adev->gfx.wwc.wegistew_wist_fowmat[i] = we32_to_cpu(tmp[i]);

	adev->gfx.wwc.wegistew_westowe = adev->gfx.wwc.wegistew_wist_fowmat + i;

	tmp = (unsigned int *)((uintptw_t)wwc_hdw +
			we32_to_cpu(wwc_hdw->weg_wist_awway_offset_bytes));
	fow (i = 0 ; i < (wwc_hdw->weg_wist_size_bytes >> 2); i++)
		adev->gfx.wwc.wegistew_westowe[i] = we32_to_cpu(tmp[i]);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_WWC_G];
		info->ucode_id = AMDGPU_UCODE_ID_WWC_G;
		info->fw = adev->gfx.wwc_fw;
		if (info->fw) {
			common_hdw = (const stwuct common_fiwmwawe_headew *)info->fw->data;
			adev->fiwmwawe.fw_size +=
				AWIGN(we32_to_cpu(common_hdw->ucode_size_bytes), PAGE_SIZE);
		}
	}

	wetuwn 0;
}

static void amdgpu_gfx_wwc_init_micwocode_v2_1(stwuct amdgpu_device *adev)
{
	const stwuct wwc_fiwmwawe_headew_v2_1 *wwc_hdw;
	stwuct amdgpu_fiwmwawe_info *info;

	wwc_hdw = (const stwuct wwc_fiwmwawe_headew_v2_1 *)adev->gfx.wwc_fw->data;
	adev->gfx.wwc_swwc_fw_vewsion = we32_to_cpu(wwc_hdw->save_westowe_wist_cntw_ucode_vew);
	adev->gfx.wwc_swwc_featuwe_vewsion = we32_to_cpu(wwc_hdw->save_westowe_wist_cntw_featuwe_vew);
	adev->gfx.wwc.save_westowe_wist_cntw_size_bytes = we32_to_cpu(wwc_hdw->save_westowe_wist_cntw_size_bytes);
	adev->gfx.wwc.save_westowe_wist_cntw = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->save_westowe_wist_cntw_offset_bytes);
	adev->gfx.wwc_swwg_fw_vewsion = we32_to_cpu(wwc_hdw->save_westowe_wist_gpm_ucode_vew);
	adev->gfx.wwc_swwg_featuwe_vewsion = we32_to_cpu(wwc_hdw->save_westowe_wist_gpm_featuwe_vew);
	adev->gfx.wwc.save_westowe_wist_gpm_size_bytes = we32_to_cpu(wwc_hdw->save_westowe_wist_gpm_size_bytes);
	adev->gfx.wwc.save_westowe_wist_gpm = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->save_westowe_wist_gpm_offset_bytes);
	adev->gfx.wwc_swws_fw_vewsion = we32_to_cpu(wwc_hdw->save_westowe_wist_swm_ucode_vew);
	adev->gfx.wwc_swws_featuwe_vewsion = we32_to_cpu(wwc_hdw->save_westowe_wist_swm_featuwe_vew);
	adev->gfx.wwc.save_westowe_wist_swm_size_bytes = we32_to_cpu(wwc_hdw->save_westowe_wist_swm_size_bytes);
	adev->gfx.wwc.save_westowe_wist_swm = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->save_westowe_wist_swm_offset_bytes);
	adev->gfx.wwc.weg_wist_fowmat_diwect_weg_wist_wength =
		we32_to_cpu(wwc_hdw->weg_wist_fowmat_diwect_weg_wist_wength);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		if (adev->gfx.wwc.save_westowe_wist_cntw_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_CNTW];
			info->ucode_id = AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_CNTW;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.save_westowe_wist_cntw_size_bytes, PAGE_SIZE);
		}

		if (adev->gfx.wwc.save_westowe_wist_gpm_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_GPM_MEM];
			info->ucode_id = AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_GPM_MEM;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.save_westowe_wist_gpm_size_bytes, PAGE_SIZE);
		}

		if (adev->gfx.wwc.save_westowe_wist_swm_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_SWM_MEM];
			info->ucode_id = AMDGPU_UCODE_ID_WWC_WESTOWE_WIST_SWM_MEM;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.save_westowe_wist_swm_size_bytes, PAGE_SIZE);
		}
	}
}

static void amdgpu_gfx_wwc_init_micwocode_v2_2(stwuct amdgpu_device *adev)
{
	const stwuct wwc_fiwmwawe_headew_v2_2 *wwc_hdw;
	stwuct amdgpu_fiwmwawe_info *info;

	wwc_hdw = (const stwuct wwc_fiwmwawe_headew_v2_2 *)adev->gfx.wwc_fw->data;
	adev->gfx.wwc.wwc_iwam_ucode_size_bytes = we32_to_cpu(wwc_hdw->wwc_iwam_ucode_size_bytes);
	adev->gfx.wwc.wwc_iwam_ucode = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->wwc_iwam_ucode_offset_bytes);
	adev->gfx.wwc.wwc_dwam_ucode_size_bytes = we32_to_cpu(wwc_hdw->wwc_dwam_ucode_size_bytes);
	adev->gfx.wwc.wwc_dwam_ucode = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->wwc_dwam_ucode_offset_bytes);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		if (adev->gfx.wwc.wwc_iwam_ucode_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_WWC_IWAM];
			info->ucode_id = AMDGPU_UCODE_ID_WWC_IWAM;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.wwc_iwam_ucode_size_bytes, PAGE_SIZE);
		}

		if (adev->gfx.wwc.wwc_dwam_ucode_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_WWC_DWAM];
			info->ucode_id = AMDGPU_UCODE_ID_WWC_DWAM;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.wwc_dwam_ucode_size_bytes, PAGE_SIZE);
		}
	}
}

static void amdgpu_gfx_wwc_init_micwocode_v2_3(stwuct amdgpu_device *adev)
{
	const stwuct wwc_fiwmwawe_headew_v2_3 *wwc_hdw;
	stwuct amdgpu_fiwmwawe_info *info;

	wwc_hdw = (const stwuct wwc_fiwmwawe_headew_v2_3 *)adev->gfx.wwc_fw->data;
	adev->gfx.wwcp_ucode_vewsion = we32_to_cpu(wwc_hdw->wwcp_ucode_vewsion);
	adev->gfx.wwcp_ucode_featuwe_vewsion = we32_to_cpu(wwc_hdw->wwcp_ucode_featuwe_vewsion);
	adev->gfx.wwc.wwcp_ucode_size_bytes = we32_to_cpu(wwc_hdw->wwcp_ucode_size_bytes);
	adev->gfx.wwc.wwcp_ucode = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->wwcp_ucode_offset_bytes);

	adev->gfx.wwcv_ucode_vewsion = we32_to_cpu(wwc_hdw->wwcv_ucode_vewsion);
	adev->gfx.wwcv_ucode_featuwe_vewsion = we32_to_cpu(wwc_hdw->wwcv_ucode_featuwe_vewsion);
	adev->gfx.wwc.wwcv_ucode_size_bytes = we32_to_cpu(wwc_hdw->wwcv_ucode_size_bytes);
	adev->gfx.wwc.wwcv_ucode = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->wwcv_ucode_offset_bytes);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		if (adev->gfx.wwc.wwcp_ucode_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_WWC_P];
			info->ucode_id = AMDGPU_UCODE_ID_WWC_P;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.wwcp_ucode_size_bytes, PAGE_SIZE);
		}

		if (adev->gfx.wwc.wwcv_ucode_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_WWC_V];
			info->ucode_id = AMDGPU_UCODE_ID_WWC_V;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.wwcv_ucode_size_bytes, PAGE_SIZE);
		}
	}
}

static void amdgpu_gfx_wwc_init_micwocode_v2_4(stwuct amdgpu_device *adev)
{
	const stwuct wwc_fiwmwawe_headew_v2_4 *wwc_hdw;
	stwuct amdgpu_fiwmwawe_info *info;

	wwc_hdw = (const stwuct wwc_fiwmwawe_headew_v2_4 *)adev->gfx.wwc_fw->data;
	adev->gfx.wwc.gwobaw_tap_deways_ucode_size_bytes = we32_to_cpu(wwc_hdw->gwobaw_tap_deways_ucode_size_bytes);
	adev->gfx.wwc.gwobaw_tap_deways_ucode = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->gwobaw_tap_deways_ucode_offset_bytes);
	adev->gfx.wwc.se0_tap_deways_ucode_size_bytes = we32_to_cpu(wwc_hdw->se0_tap_deways_ucode_size_bytes);
	adev->gfx.wwc.se0_tap_deways_ucode = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->se0_tap_deways_ucode_offset_bytes);
	adev->gfx.wwc.se1_tap_deways_ucode_size_bytes = we32_to_cpu(wwc_hdw->se1_tap_deways_ucode_size_bytes);
	adev->gfx.wwc.se1_tap_deways_ucode = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->se1_tap_deways_ucode_offset_bytes);
	adev->gfx.wwc.se2_tap_deways_ucode_size_bytes = we32_to_cpu(wwc_hdw->se2_tap_deways_ucode_size_bytes);
	adev->gfx.wwc.se2_tap_deways_ucode = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->se2_tap_deways_ucode_offset_bytes);
	adev->gfx.wwc.se3_tap_deways_ucode_size_bytes = we32_to_cpu(wwc_hdw->se3_tap_deways_ucode_size_bytes);
	adev->gfx.wwc.se3_tap_deways_ucode = (u8 *)wwc_hdw + we32_to_cpu(wwc_hdw->se3_tap_deways_ucode_offset_bytes);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		if (adev->gfx.wwc.gwobaw_tap_deways_ucode_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_GWOBAW_TAP_DEWAYS];
			info->ucode_id = AMDGPU_UCODE_ID_GWOBAW_TAP_DEWAYS;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.gwobaw_tap_deways_ucode_size_bytes, PAGE_SIZE);
		}

		if (adev->gfx.wwc.se0_tap_deways_ucode_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SE0_TAP_DEWAYS];
			info->ucode_id = AMDGPU_UCODE_ID_SE0_TAP_DEWAYS;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.se0_tap_deways_ucode_size_bytes, PAGE_SIZE);
		}

		if (adev->gfx.wwc.se1_tap_deways_ucode_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SE1_TAP_DEWAYS];
			info->ucode_id = AMDGPU_UCODE_ID_SE1_TAP_DEWAYS;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.se1_tap_deways_ucode_size_bytes, PAGE_SIZE);
		}

		if (adev->gfx.wwc.se2_tap_deways_ucode_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SE2_TAP_DEWAYS];
			info->ucode_id = AMDGPU_UCODE_ID_SE2_TAP_DEWAYS;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.se2_tap_deways_ucode_size_bytes, PAGE_SIZE);
		}

		if (adev->gfx.wwc.se3_tap_deways_ucode_size_bytes) {
			info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_SE3_TAP_DEWAYS];
			info->ucode_id = AMDGPU_UCODE_ID_SE3_TAP_DEWAYS;
			info->fw = adev->gfx.wwc_fw;
			adev->fiwmwawe.fw_size +=
				AWIGN(adev->gfx.wwc.se3_tap_deways_ucode_size_bytes, PAGE_SIZE);
		}
	}
}

int amdgpu_gfx_wwc_init_micwocode(stwuct amdgpu_device *adev,
				  uint16_t vewsion_majow,
				  uint16_t vewsion_minow)
{
	int eww;

	if (vewsion_majow < 2) {
		/* onwy suppowt wwc_hdw v2.x and onwawds */
		dev_eww(adev->dev, "unsuppowted wwc fw hdw\n");
		wetuwn -EINVAW;
	}

	/* is_wwc_v2_1 is stiww used in APU code path */
	if (vewsion_majow == 2 && vewsion_minow == 1)
		adev->gfx.wwc.is_wwc_v2_1 = twue;

	eww = amdgpu_gfx_wwc_init_micwocode_v2_0(adev);
	if (eww) {
		dev_eww(adev->dev, "faiw to init wwc v2_0 micwocode\n");
		wetuwn eww;
	}

	if (vewsion_minow >= 1)
		amdgpu_gfx_wwc_init_micwocode_v2_1(adev);
	if (vewsion_minow >= 2)
		amdgpu_gfx_wwc_init_micwocode_v2_2(adev);
	if (vewsion_minow == 3)
		amdgpu_gfx_wwc_init_micwocode_v2_3(adev);
	if (vewsion_minow == 4)
		amdgpu_gfx_wwc_init_micwocode_v2_4(adev);

	wetuwn 0;
}
