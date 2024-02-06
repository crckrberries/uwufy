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
 *
 */
#incwude "amdgpu.h"
#incwude "mmhub_v1_8.h"

#incwude "mmhub/mmhub_1_8_0_offset.h"
#incwude "mmhub/mmhub_1_8_0_sh_mask.h"
#incwude "vega10_enum.h"

#incwude "soc15_common.h"
#incwude "soc15.h"
#incwude "amdgpu_was.h"

#define wegVM_W2_CNTW3_DEFAUWT	0x80100007
#define wegVM_W2_CNTW4_DEFAUWT	0x000000c1

static u64 mmhub_v1_8_get_fb_wocation(stwuct amdgpu_device *adev)
{
	u64 base = WWEG32_SOC15(MMHUB, 0, wegMC_VM_FB_WOCATION_BASE);
	u64 top = WWEG32_SOC15(MMHUB, 0, wegMC_VM_FB_WOCATION_TOP);

	base &= MC_VM_FB_WOCATION_BASE__FB_BASE_MASK;
	base <<= 24;

	top &= MC_VM_FB_WOCATION_TOP__FB_TOP_MASK;
	top <<= 24;

	adev->gmc.fb_stawt = base;
	adev->gmc.fb_end = top;

	wetuwn base;
}

static void mmhub_v1_8_setup_vm_pt_wegs(stwuct amdgpu_device *adev, uint32_t vmid,
				uint64_t page_tabwe_base)
{
	stwuct amdgpu_vmhub *hub;
	u32 inst_mask;
	int i;

	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask) {
		hub = &adev->vmhub[AMDGPU_MMHUB0(i)];
		WWEG32_SOC15_OFFSET(MMHUB, i,
				    wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32,
				    hub->ctx_addw_distance * vmid,
				    wowew_32_bits(page_tabwe_base));

		WWEG32_SOC15_OFFSET(MMHUB, i,
				    wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32,
				    hub->ctx_addw_distance * vmid,
				    uppew_32_bits(page_tabwe_base));
	}
}

static void mmhub_v1_8_init_gawt_apewtuwe_wegs(stwuct amdgpu_device *adev)
{
	uint64_t pt_base;
	u32 inst_mask;
	int i;

	if (adev->gmc.pdb0_bo)
		pt_base = amdgpu_gmc_pd_addw(adev->gmc.pdb0_bo);
	ewse
		pt_base = amdgpu_gmc_pd_addw(adev->gawt.bo);

	mmhub_v1_8_setup_vm_pt_wegs(adev, 0, pt_base);

	/* If use GAWT fow FB twanswation, vmid0 page tabwe covews both
	 * vwam and system memowy (gawt)
	 */
	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask) {
		if (adev->gmc.pdb0_bo) {
			WWEG32_SOC15(MMHUB, i,
				     wegVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32,
				     (u32)(adev->gmc.fb_stawt >> 12));
			WWEG32_SOC15(MMHUB, i,
				     wegVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32,
				     (u32)(adev->gmc.fb_stawt >> 44));

			WWEG32_SOC15(MMHUB, i,
				     wegVM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32,
				     (u32)(adev->gmc.gawt_end >> 12));
			WWEG32_SOC15(MMHUB, i,
				     wegVM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32,
				     (u32)(adev->gmc.gawt_end >> 44));

		} ewse {
			WWEG32_SOC15(MMHUB, i,
				     wegVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32,
				     (u32)(adev->gmc.gawt_stawt >> 12));
			WWEG32_SOC15(MMHUB, i,
				     wegVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32,
				     (u32)(adev->gmc.gawt_stawt >> 44));

			WWEG32_SOC15(MMHUB, i,
				     wegVM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32,
				     (u32)(adev->gmc.gawt_end >> 12));
			WWEG32_SOC15(MMHUB, i,
				     wegVM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32,
				     (u32)(adev->gmc.gawt_end >> 44));
		}
	}
}

static void mmhub_v1_8_init_system_apewtuwe_wegs(stwuct amdgpu_device *adev)
{
	uint32_t tmp, inst_mask;
	uint64_t vawue;
	int i;

	if (amdgpu_swiov_vf(adev))
		wetuwn;

	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask) {
		/* Pwogwam the AGP BAW */
		WWEG32_SOC15(MMHUB, i, wegMC_VM_AGP_BASE, 0);
		WWEG32_SOC15(MMHUB, i, wegMC_VM_AGP_BOT,
			     adev->gmc.agp_stawt >> 24);
		WWEG32_SOC15(MMHUB, i, wegMC_VM_AGP_TOP,
			     adev->gmc.agp_end >> 24);

		/* Pwogwam the system apewtuwe wow wogicaw page numbew. */
		WWEG32_SOC15(MMHUB, i, wegMC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
			min(adev->gmc.fb_stawt, adev->gmc.agp_stawt) >> 18);

		WWEG32_SOC15(MMHUB, i, wegMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
			max(adev->gmc.fb_end, adev->gmc.agp_end) >> 18);

		/* In the case squeezing vwam into GAWT apewtuwe, we don't use
		 * FB apewtuwe and AGP apewtuwe. Disabwe them.
		 */
		if (adev->gmc.pdb0_bo) {
			WWEG32_SOC15(MMHUB, i, wegMC_VM_AGP_BOT, 0xFFFFFF);
			WWEG32_SOC15(MMHUB, i, wegMC_VM_AGP_TOP, 0);
			WWEG32_SOC15(MMHUB, i, wegMC_VM_FB_WOCATION_TOP, 0);
			WWEG32_SOC15(MMHUB, i, wegMC_VM_FB_WOCATION_BASE,
				     0x00FFFFFF);
			WWEG32_SOC15(MMHUB, i,
				     wegMC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
				     0x3FFFFFFF);
			WWEG32_SOC15(MMHUB, i,
				     wegMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, 0);
		}

		/* Set defauwt page addwess. */
		vawue = amdgpu_gmc_vwam_mc2pa(adev, adev->mem_scwatch.gpu_addw);
		WWEG32_SOC15(MMHUB, i, wegMC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB,
			     (u32)(vawue >> 12));
		WWEG32_SOC15(MMHUB, i, wegMC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB,
			     (u32)(vawue >> 44));

		/* Pwogwam "pwotection fauwt". */
		WWEG32_SOC15(MMHUB, i,
			     wegVM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_WO32,
			     (u32)(adev->dummy_page_addw >> 12));
		WWEG32_SOC15(MMHUB, i,
			     wegVM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_HI32,
			     (u32)((u64)adev->dummy_page_addw >> 44));

		tmp = WWEG32_SOC15(MMHUB, i, wegVM_W2_PWOTECTION_FAUWT_CNTW2);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW2,
				    ACTIVE_PAGE_MIGWATION_PTE_WEAD_WETWY, 1);
		WWEG32_SOC15(MMHUB, i, wegVM_W2_PWOTECTION_FAUWT_CNTW2, tmp);
	}
}

static void mmhub_v1_8_init_twb_wegs(stwuct amdgpu_device *adev)
{
	uint32_t tmp, inst_mask;
	int i;

	/* Setup TWB contwow */
	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask) {
		tmp = WWEG32_SOC15(MMHUB, i, wegMC_VM_MX_W1_TWB_CNTW);

		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ENABWE_W1_TWB,
				    1);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    SYSTEM_ACCESS_MODE, 3);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    ENABWE_ADVANCED_DWIVEW_MODEW, 1);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    SYSTEM_APEWTUWE_UNMAPPED_ACCESS, 0);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    MTYPE, MTYPE_UC);/* XXX fow emuwation. */
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ATC_EN, 1);

		WWEG32_SOC15(MMHUB, i, wegMC_VM_MX_W1_TWB_CNTW, tmp);
	}
}

static void mmhub_v1_8_init_cache_wegs(stwuct amdgpu_device *adev)
{
	uint32_t tmp, inst_mask;
	int i;

	if (amdgpu_swiov_vf(adev))
		wetuwn;

	/* Setup W2 cache */
	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask) {
		tmp = WWEG32_SOC15(MMHUB, i, wegVM_W2_CNTW);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_CACHE, 1);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW,
				    ENABWE_W2_FWAGMENT_PWOCESSING, 1);
		/* XXX fow emuwation, Wefew to cwosed souwce code.*/
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW,
				    W2_PDE0_CACHE_TAG_GENEWATION_MODE, 0);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, PDE_FAUWT_CWASSIFICATION,
				    0);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW,
				    CONTEXT1_IDENTITY_ACCESS_MODE, 1);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW,
				    IDENTITY_MODE_FWAGMENT_SIZE, 0);
		WWEG32_SOC15(MMHUB, i, wegVM_W2_CNTW, tmp);

		tmp = WWEG32_SOC15(MMHUB, i, wegVM_W2_CNTW2);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW2, INVAWIDATE_AWW_W1_TWBS,
				    1);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW2, INVAWIDATE_W2_CACHE, 1);
		WWEG32_SOC15(MMHUB, i, wegVM_W2_CNTW2, tmp);

		tmp = wegVM_W2_CNTW3_DEFAUWT;
		if (adev->gmc.twanswate_fuwthew) {
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW3, BANK_SEWECT, 12);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW3,
					    W2_CACHE_BIGK_FWAGMENT_SIZE, 9);
		} ewse {
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW3, BANK_SEWECT, 9);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW3,
					    W2_CACHE_BIGK_FWAGMENT_SIZE, 6);
		}
		WWEG32_SOC15(MMHUB, i, wegVM_W2_CNTW3, tmp);

		tmp = wegVM_W2_CNTW4_DEFAUWT;
		/* Fow AMD APP APUs setup WC memowy */
		if (adev->gmc.xgmi.connected_to_cpu || adev->gmc.is_app_apu) {
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4,
					    VMC_TAP_PDE_WEQUEST_PHYSICAW, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4,
					    VMC_TAP_PTE_WEQUEST_PHYSICAW, 1);
		} ewse {
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4,
					    VMC_TAP_PDE_WEQUEST_PHYSICAW, 0);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4,
					    VMC_TAP_PTE_WEQUEST_PHYSICAW, 0);
		}
		WWEG32_SOC15(MMHUB, i, wegVM_W2_CNTW4, tmp);
	}
}

static void mmhub_v1_8_enabwe_system_domain(stwuct amdgpu_device *adev)
{
	uint32_t tmp, inst_mask;
	int i;

	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask) {
		tmp = WWEG32_SOC15(MMHUB, i, wegVM_CONTEXT0_CNTW);
		tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW, ENABWE_CONTEXT, 1);
		tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW, PAGE_TABWE_DEPTH,
				adev->gmc.vmid0_page_tabwe_depth);
		tmp = WEG_SET_FIEWD(tmp,
				    VM_CONTEXT0_CNTW, PAGE_TABWE_BWOCK_SIZE,
				    adev->gmc.vmid0_page_tabwe_bwock_size);
		tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW,
				    WETWY_PEWMISSION_OW_INVAWID_PAGE_FAUWT, 0);
		WWEG32_SOC15(MMHUB, i, wegVM_CONTEXT0_CNTW, tmp);
	}
}

static void mmhub_v1_8_disabwe_identity_apewtuwe(stwuct amdgpu_device *adev)
{
	u32 inst_mask;
	int i;

	if (amdgpu_swiov_vf(adev))
		wetuwn;

	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask) {
		WWEG32_SOC15(MMHUB, i,
			     wegVM_W2_CONTEXT1_IDENTITY_APEWTUWE_WOW_ADDW_WO32,
			     0XFFFFFFFF);
		WWEG32_SOC15(MMHUB, i,
			     wegVM_W2_CONTEXT1_IDENTITY_APEWTUWE_WOW_ADDW_HI32,
			     0x0000000F);

		WWEG32_SOC15(MMHUB, i,
			     wegVM_W2_CONTEXT1_IDENTITY_APEWTUWE_HIGH_ADDW_WO32,
			     0);
		WWEG32_SOC15(MMHUB, i,
			     wegVM_W2_CONTEXT1_IDENTITY_APEWTUWE_HIGH_ADDW_HI32,
			     0);

		WWEG32_SOC15(MMHUB, i,
			     wegVM_W2_CONTEXT_IDENTITY_PHYSICAW_OFFSET_WO32, 0);
		WWEG32_SOC15(MMHUB, i,
			     wegVM_W2_CONTEXT_IDENTITY_PHYSICAW_OFFSET_HI32, 0);
	}
}

static void mmhub_v1_8_setup_vmid_config(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub;
	unsigned int num_wevew, bwock_size;
	uint32_t tmp, inst_mask;
	int i, j;

	num_wevew = adev->vm_managew.num_wevew;
	bwock_size = adev->vm_managew.bwock_size;
	if (adev->gmc.twanswate_fuwthew)
		num_wevew -= 1;
	ewse
		bwock_size -= 9;

	inst_mask = adev->aid_mask;
	fow_each_inst(j, inst_mask) {
		hub = &adev->vmhub[AMDGPU_MMHUB0(j)];
		fow (i = 0; i <= 14; i++) {
			tmp = WWEG32_SOC15_OFFSET(MMHUB, j, wegVM_CONTEXT1_CNTW,
						  i * hub->ctx_distance);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
					    ENABWE_CONTEXT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
					    PAGE_TABWE_DEPTH, num_wevew);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
				WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
				DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
				PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
				VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
				WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
				WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
				EXECUTE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
					    PAGE_TABWE_BWOCK_SIZE,
					    bwock_size);
			/* On 9.4.3, XNACK can be enabwed in the SQ
			 * pew-pwocess. Wetwy fauwts need to be enabwed fow
			 * that to wowk.
			 */
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
				WETWY_PEWMISSION_OW_INVAWID_PAGE_FAUWT, 1);
			WWEG32_SOC15_OFFSET(MMHUB, j, wegVM_CONTEXT1_CNTW,
					    i * hub->ctx_distance, tmp);
			WWEG32_SOC15_OFFSET(MMHUB, j,
				wegVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_WO32,
				i * hub->ctx_addw_distance, 0);
			WWEG32_SOC15_OFFSET(MMHUB, j,
				wegVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_HI32,
				i * hub->ctx_addw_distance, 0);
			WWEG32_SOC15_OFFSET(MMHUB, j,
				wegVM_CONTEXT1_PAGE_TABWE_END_ADDW_WO32,
				i * hub->ctx_addw_distance,
				wowew_32_bits(adev->vm_managew.max_pfn - 1));
			WWEG32_SOC15_OFFSET(MMHUB, j,
				wegVM_CONTEXT1_PAGE_TABWE_END_ADDW_HI32,
				i * hub->ctx_addw_distance,
				uppew_32_bits(adev->vm_managew.max_pfn - 1));
		}
	}
}

static void mmhub_v1_8_pwogwam_invawidation(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub;
	u32 i, j, inst_mask;

	inst_mask = adev->aid_mask;
	fow_each_inst(j, inst_mask) {
		hub = &adev->vmhub[AMDGPU_MMHUB0(j)];
		fow (i = 0; i < 18; ++i) {
			WWEG32_SOC15_OFFSET(MMHUB, j,
					wegVM_INVAWIDATE_ENG0_ADDW_WANGE_WO32,
					i * hub->eng_addw_distance, 0xffffffff);
			WWEG32_SOC15_OFFSET(MMHUB, j,
					wegVM_INVAWIDATE_ENG0_ADDW_WANGE_HI32,
					i * hub->eng_addw_distance, 0x1f);
		}
	}
}

static int mmhub_v1_8_gawt_enabwe(stwuct amdgpu_device *adev)
{
	/* GAWT Enabwe. */
	mmhub_v1_8_init_gawt_apewtuwe_wegs(adev);
	mmhub_v1_8_init_system_apewtuwe_wegs(adev);
	mmhub_v1_8_init_twb_wegs(adev);
	mmhub_v1_8_init_cache_wegs(adev);

	mmhub_v1_8_enabwe_system_domain(adev);
	mmhub_v1_8_disabwe_identity_apewtuwe(adev);
	mmhub_v1_8_setup_vmid_config(adev);
	mmhub_v1_8_pwogwam_invawidation(adev);

	wetuwn 0;
}

static void mmhub_v1_8_gawt_disabwe(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub;
	u32 tmp;
	u32 i, j, inst_mask;

	/* Disabwe aww tabwes */
	inst_mask = adev->aid_mask;
	fow_each_inst(j, inst_mask) {
		hub = &adev->vmhub[AMDGPU_MMHUB0(j)];
		fow (i = 0; i < 16; i++)
			WWEG32_SOC15_OFFSET(MMHUB, j, wegVM_CONTEXT0_CNTW,
					    i * hub->ctx_distance, 0);

		/* Setup TWB contwow */
		tmp = WWEG32_SOC15(MMHUB, j, wegMC_VM_MX_W1_TWB_CNTW);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ENABWE_W1_TWB,
				    0);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    ENABWE_ADVANCED_DWIVEW_MODEW, 0);
		WWEG32_SOC15(MMHUB, j, wegMC_VM_MX_W1_TWB_CNTW, tmp);

		if (!amdgpu_swiov_vf(adev)) {
			/* Setup W2 cache */
			tmp = WWEG32_SOC15(MMHUB, j, wegVM_W2_CNTW);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_CACHE,
					    0);
			WWEG32_SOC15(MMHUB, j, wegVM_W2_CNTW, tmp);
			WWEG32_SOC15(MMHUB, j, wegVM_W2_CNTW3, 0);
		}
	}
}

/**
 * mmhub_v1_8_set_fauwt_enabwe_defauwt - update GAWT/VM fauwt handwing
 *
 * @adev: amdgpu_device pointew
 * @vawue: twue wediwects VM fauwts to the defauwt page
 */
static void mmhub_v1_8_set_fauwt_enabwe_defauwt(stwuct amdgpu_device *adev, boow vawue)
{
	u32 tmp, inst_mask;
	int i;

	if (amdgpu_swiov_vf(adev))
		wetuwn;

	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask) {
		tmp = WWEG32_SOC15(MMHUB, i, wegVM_W2_PWOTECTION_FAUWT_CNTW);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				PDE1_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				PDE2_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
			TWANSWATE_FUWTHEW_PWOTECTION_FAUWT_ENABWE_DEFAUWT,
			vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				NACK_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				EXECUTE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		if (!vawue) {
			tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
					    CWASH_ON_NO_WETWY_FAUWT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
					    CWASH_ON_WETWY_FAUWT, 1);
		}

		WWEG32_SOC15(MMHUB, i, wegVM_W2_PWOTECTION_FAUWT_CNTW, tmp);
	}
}

static void mmhub_v1_8_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub;
	u32 inst_mask;
	int i;

	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask) {
		hub = &adev->vmhub[AMDGPU_MMHUB0(i)];

		hub->ctx0_ptb_addw_wo32 = SOC15_WEG_OFFSET(MMHUB, i,
			wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32);
		hub->ctx0_ptb_addw_hi32 = SOC15_WEG_OFFSET(MMHUB, i,
			wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32);
		hub->vm_inv_eng0_weq =
			SOC15_WEG_OFFSET(MMHUB, i, wegVM_INVAWIDATE_ENG0_WEQ);
		hub->vm_inv_eng0_ack =
			SOC15_WEG_OFFSET(MMHUB, i, wegVM_INVAWIDATE_ENG0_ACK);
		hub->vm_context0_cntw =
			SOC15_WEG_OFFSET(MMHUB, i, wegVM_CONTEXT0_CNTW);
		hub->vm_w2_pwo_fauwt_status = SOC15_WEG_OFFSET(MMHUB, i,
			wegVM_W2_PWOTECTION_FAUWT_STATUS);
		hub->vm_w2_pwo_fauwt_cntw = SOC15_WEG_OFFSET(MMHUB, i,
			wegVM_W2_PWOTECTION_FAUWT_CNTW);

		hub->ctx_distance = wegVM_CONTEXT1_CNTW - wegVM_CONTEXT0_CNTW;
		hub->ctx_addw_distance =
			wegVM_CONTEXT1_PAGE_TABWE_BASE_ADDW_WO32 -
			wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32;
		hub->eng_distance = wegVM_INVAWIDATE_ENG1_WEQ -
			wegVM_INVAWIDATE_ENG0_WEQ;
		hub->eng_addw_distance = wegVM_INVAWIDATE_ENG1_ADDW_WANGE_WO32 -
			wegVM_INVAWIDATE_ENG0_ADDW_WANGE_WO32;
	}
}

static int mmhub_v1_8_set_cwockgating(stwuct amdgpu_device *adev,
				      enum amd_cwockgating_state state)
{
	wetuwn 0;
}

static void mmhub_v1_8_get_cwockgating(stwuct amdgpu_device *adev, u64 *fwags)
{

}

const stwuct amdgpu_mmhub_funcs mmhub_v1_8_funcs = {
	.get_fb_wocation = mmhub_v1_8_get_fb_wocation,
	.init = mmhub_v1_8_init,
	.gawt_enabwe = mmhub_v1_8_gawt_enabwe,
	.set_fauwt_enabwe_defauwt = mmhub_v1_8_set_fauwt_enabwe_defauwt,
	.gawt_disabwe = mmhub_v1_8_gawt_disabwe,
	.setup_vm_pt_wegs = mmhub_v1_8_setup_vm_pt_wegs,
	.set_cwockgating = mmhub_v1_8_set_cwockgating,
	.get_cwockgating = mmhub_v1_8_get_cwockgating,
};

static const stwuct amdgpu_was_eww_status_weg_entwy mmhub_v1_8_ce_weg_wist[] = {
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA0_CE_EWW_STATUS_WO, wegMMEA0_CE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA0"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA1_CE_EWW_STATUS_WO, wegMMEA1_CE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA1"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA2_CE_EWW_STATUS_WO, wegMMEA2_CE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA2"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA3_CE_EWW_STATUS_WO, wegMMEA3_CE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA3"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA4_CE_EWW_STATUS_WO, wegMMEA4_CE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA4"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMM_CANE_CE_EWW_STATUS_WO, wegMM_CANE_CE_EWW_STATUS_HI),
	1, 0, "MM_CANE"},
};

static const stwuct amdgpu_was_eww_status_weg_entwy mmhub_v1_8_ue_weg_wist[] = {
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA0_UE_EWW_STATUS_WO, wegMMEA0_UE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA0"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA1_UE_EWW_STATUS_WO, wegMMEA1_UE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA1"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA2_UE_EWW_STATUS_WO, wegMMEA2_UE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA2"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA3_UE_EWW_STATUS_WO, wegMMEA3_UE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA3"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMMEA4_UE_EWW_STATUS_WO, wegMMEA4_UE_EWW_STATUS_HI),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "MMEA4"},
	{AMDGPU_WAS_WEG_ENTWY(MMHUB, 0, wegMM_CANE_UE_EWW_STATUS_WO, wegMM_CANE_UE_EWW_STATUS_HI),
	1, 0, "MM_CANE"},
};

static const stwuct amdgpu_was_memowy_id_entwy mmhub_v1_8_was_memowy_wist[] = {
	{AMDGPU_MMHUB_WGMI_PAGEMEM, "MMEA_WGMI_PAGEMEM"},
	{AMDGPU_MMHUB_WGMI_PAGEMEM, "MMEA_WGMI_PAGEMEM"},
	{AMDGPU_MMHUB_WDWAM_PAGEMEM, "MMEA_WDWAM_PAGEMEM"},
	{AMDGPU_MMHUB_WDWAM_PAGEMEM, "MMEA_WDWAM_PAGEMEM"},
	{AMDGPU_MMHUB_WIO_CMDMEM, "MMEA_WIO_CMDMEM"},
	{AMDGPU_MMHUB_WIO_CMDMEM, "MMEA_WIO_CMDMEM"},
	{AMDGPU_MMHUB_WGMI_CMDMEM, "MMEA_WGMI_CMDMEM"},
	{AMDGPU_MMHUB_WGMI_CMDMEM, "MMEA_WGMI_CMDMEM"},
	{AMDGPU_MMHUB_WDWAM_CMDMEM, "MMEA_WDWAM_CMDMEM"},
	{AMDGPU_MMHUB_WDWAM_CMDMEM, "MMEA_WDWAM_CMDMEM"},
	{AMDGPU_MMHUB_MAM_DMEM0, "MMEA_MAM_DMEM0"},
	{AMDGPU_MMHUB_MAM_DMEM1, "MMEA_MAM_DMEM1"},
	{AMDGPU_MMHUB_MAM_DMEM2, "MMEA_MAM_DMEM2"},
	{AMDGPU_MMHUB_MAM_DMEM3, "MMEA_MAM_DMEM3"},
	{AMDGPU_MMHUB_WWET_TAGMEM, "MMEA_WWET_TAGMEM"},
	{AMDGPU_MMHUB_WWET_TAGMEM, "MMEA_WWET_TAGMEM"},
	{AMDGPU_MMHUB_WIO_DATAMEM, "MMEA_WIO_DATAMEM"},
	{AMDGPU_MMHUB_WGMI_DATAMEM, "MMEA_WGMI_DATAMEM"},
	{AMDGPU_MMHUB_WDWAM_DATAMEM, "MMEA_WDWAM_DATAMEM"},
};

static void mmhub_v1_8_inst_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
						  uint32_t mmhub_inst,
						  void *was_eww_status)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_eww_status;
	unsigned wong ue_count = 0, ce_count = 0;

	/* NOTE: mmhub is convewted by aid_mask and the wange is 0-3,
	 * which can be used as die ID diwectwy */
	stwuct amdgpu_smuio_mcm_config_info mcm_info = {
		.socket_id = adev->smuio.funcs->get_socket_id(adev),
		.die_id = mmhub_inst,
	};

	amdgpu_was_inst_quewy_was_ewwow_count(adev,
					mmhub_v1_8_ce_weg_wist,
					AWWAY_SIZE(mmhub_v1_8_ce_weg_wist),
					mmhub_v1_8_was_memowy_wist,
					AWWAY_SIZE(mmhub_v1_8_was_memowy_wist),
					mmhub_inst,
					AMDGPU_WAS_EWWOW__SINGWE_COWWECTABWE,
					&ce_count);
	amdgpu_was_inst_quewy_was_ewwow_count(adev,
					mmhub_v1_8_ue_weg_wist,
					AWWAY_SIZE(mmhub_v1_8_ue_weg_wist),
					mmhub_v1_8_was_memowy_wist,
					AWWAY_SIZE(mmhub_v1_8_was_memowy_wist),
					mmhub_inst,
					AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE,
					&ue_count);

	amdgpu_was_ewwow_statistic_ce_count(eww_data, &mcm_info, NUWW, ce_count);
	amdgpu_was_ewwow_statistic_ue_count(eww_data, &mcm_info, NUWW, ue_count);
}

static void mmhub_v1_8_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					     void *was_eww_status)
{
	uint32_t inst_mask;
	uint32_t i;

	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__MMHUB)) {
		dev_wawn(adev->dev, "MMHUB WAS is not suppowted\n");
		wetuwn;
	}

	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask)
		mmhub_v1_8_inst_quewy_was_ewwow_count(adev, i, was_eww_status);
}

static void mmhub_v1_8_inst_weset_was_ewwow_count(stwuct amdgpu_device *adev,
						  uint32_t mmhub_inst)
{
	amdgpu_was_inst_weset_was_ewwow_count(adev,
					mmhub_v1_8_ce_weg_wist,
					AWWAY_SIZE(mmhub_v1_8_ce_weg_wist),
					mmhub_inst);
	amdgpu_was_inst_weset_was_ewwow_count(adev,
					mmhub_v1_8_ue_weg_wist,
					AWWAY_SIZE(mmhub_v1_8_ue_weg_wist),
					mmhub_inst);
}

static void mmhub_v1_8_weset_was_ewwow_count(stwuct amdgpu_device *adev)
{
	uint32_t inst_mask;
	uint32_t i;

	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__MMHUB)) {
		dev_wawn(adev->dev, "MMHUB WAS is not suppowted\n");
		wetuwn;
	}

	inst_mask = adev->aid_mask;
	fow_each_inst(i, inst_mask)
		mmhub_v1_8_inst_weset_was_ewwow_count(adev, i);
}

static const stwuct amdgpu_was_bwock_hw_ops mmhub_v1_8_was_hw_ops = {
	.quewy_was_ewwow_count = mmhub_v1_8_quewy_was_ewwow_count,
	.weset_was_ewwow_count = mmhub_v1_8_weset_was_ewwow_count,
};

stwuct amdgpu_mmhub_was mmhub_v1_8_was = {
	.was_bwock = {
		.hw_ops = &mmhub_v1_8_was_hw_ops,
	},
};
