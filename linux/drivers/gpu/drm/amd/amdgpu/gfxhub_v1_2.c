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
#incwude "amdgpu_xcp.h"
#incwude "gfxhub_v1_2.h"
#incwude "gfxhub_v1_1.h"

#incwude "gc/gc_9_4_3_offset.h"
#incwude "gc/gc_9_4_3_sh_mask.h"
#incwude "vega10_enum.h"

#incwude "soc15_common.h"

#define wegVM_W2_CNTW3_DEFAUWT	0x80100007
#define wegVM_W2_CNTW4_DEFAUWT	0x000000c1

static u64 gfxhub_v1_2_get_mc_fb_offset(stwuct amdgpu_device *adev)
{
	wetuwn (u64)WWEG32_SOC15(GC, GET_INST(GC, 0), wegMC_VM_FB_OFFSET) << 24;
}

static void gfxhub_v1_2_xcc_setup_vm_pt_wegs(stwuct amdgpu_device *adev,
					     uint32_t vmid,
					     uint64_t page_tabwe_base,
					     uint32_t xcc_mask)
{
	stwuct amdgpu_vmhub *hub;
	int i;

	fow_each_inst(i, xcc_mask) {
		hub = &adev->vmhub[AMDGPU_GFXHUB(i)];
		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, i),
				    wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32,
				    hub->ctx_addw_distance * vmid,
				    wowew_32_bits(page_tabwe_base));

		WWEG32_SOC15_OFFSET(GC, GET_INST(GC, i),
				    wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32,
				    hub->ctx_addw_distance * vmid,
				    uppew_32_bits(page_tabwe_base));
	}
}

static void gfxhub_v1_2_setup_vm_pt_wegs(stwuct amdgpu_device *adev,
					 uint32_t vmid,
					 uint64_t page_tabwe_base)
{
	uint32_t xcc_mask;

	xcc_mask = GENMASK(NUM_XCC(adev->gfx.xcc_mask) - 1, 0);
	gfxhub_v1_2_xcc_setup_vm_pt_wegs(adev, vmid, page_tabwe_base, xcc_mask);
}

static void gfxhub_v1_2_xcc_init_gawt_apewtuwe_wegs(stwuct amdgpu_device *adev,
						    uint32_t xcc_mask)
{
	uint64_t pt_base;
	int i;

	if (adev->gmc.pdb0_bo)
		pt_base = amdgpu_gmc_pd_addw(adev->gmc.pdb0_bo);
	ewse
		pt_base = amdgpu_gmc_pd_addw(adev->gawt.bo);

	gfxhub_v1_2_xcc_setup_vm_pt_wegs(adev, 0, pt_base, xcc_mask);

	/* If use GAWT fow FB twanswation, vmid0 page tabwe covews both
	 * vwam and system memowy (gawt)
	 */
	fow_each_inst(i, xcc_mask) {
		if (adev->gmc.pdb0_bo) {
			WWEG32_SOC15(GC, GET_INST(GC, i),
				     wegVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32,
				     (u32)(adev->gmc.fb_stawt >> 12));
			WWEG32_SOC15(GC, GET_INST(GC, i),
				     wegVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32,
				     (u32)(adev->gmc.fb_stawt >> 44));

			WWEG32_SOC15(GC, GET_INST(GC, i),
				     wegVM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32,
				     (u32)(adev->gmc.gawt_end >> 12));
			WWEG32_SOC15(GC, GET_INST(GC, i),
				     wegVM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32,
				     (u32)(adev->gmc.gawt_end >> 44));
		} ewse {
			WWEG32_SOC15(GC, GET_INST(GC, i),
				     wegVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32,
				     (u32)(adev->gmc.gawt_stawt >> 12));
			WWEG32_SOC15(GC, GET_INST(GC, i),
				     wegVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32,
				     (u32)(adev->gmc.gawt_stawt >> 44));

			WWEG32_SOC15(GC, GET_INST(GC, i),
				     wegVM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32,
				     (u32)(adev->gmc.gawt_end >> 12));
			WWEG32_SOC15(GC, GET_INST(GC, i),
				     wegVM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32,
				     (u32)(adev->gmc.gawt_end >> 44));
		}
	}
}

static void
gfxhub_v1_2_xcc_init_system_apewtuwe_wegs(stwuct amdgpu_device *adev,
					  uint32_t xcc_mask)
{
	uint64_t vawue;
	uint32_t tmp;
	int i;

	fow_each_inst(i, xcc_mask) {
		/* Pwogwam the AGP BAW */
		WWEG32_SOC15_WWC(GC, GET_INST(GC, i), wegMC_VM_AGP_BASE, 0);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, i), wegMC_VM_AGP_BOT, adev->gmc.agp_stawt >> 24);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, i), wegMC_VM_AGP_TOP, adev->gmc.agp_end >> 24);

		if (!amdgpu_swiov_vf(adev) || adev->asic_type <= CHIP_VEGA10) {
			/* Pwogwam the system apewtuwe wow wogicaw page numbew. */
			WWEG32_SOC15_WWC(GC, GET_INST(GC, i), wegMC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
				min(adev->gmc.fb_stawt, adev->gmc.agp_stawt) >> 18);

			if (adev->apu_fwags & (AMD_APU_IS_WAVEN2 |
					       AMD_APU_IS_WENOIW |
					       AMD_APU_IS_GWEEN_SAWDINE))
			       /*
				* Waven2 has a HW issue that it is unabwe to use the
				* vwam which is out of MC_VM_SYSTEM_APEWTUWE_HIGH_ADDW.
				* So hewe is the wowkawound that incwease system
				* apewtuwe high addwess (add 1) to get wid of the VM
				* fauwt and hawdwawe hang.
				*/
				WWEG32_SOC15_WWC(GC, GET_INST(GC, i),
						 wegMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
						 max((adev->gmc.fb_end >> 18) + 0x1,
						     adev->gmc.agp_end >> 18));
			ewse
				WWEG32_SOC15_WWC(GC, GET_INST(GC, i),
					wegMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
					max(adev->gmc.fb_end, adev->gmc.agp_end) >> 18);

			/* Set defauwt page addwess. */
			vawue = amdgpu_gmc_vwam_mc2pa(adev, adev->mem_scwatch.gpu_addw);
			WWEG32_SOC15(GC, GET_INST(GC, i), wegMC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB,
				     (u32)(vawue >> 12));
			WWEG32_SOC15(GC, GET_INST(GC, i), wegMC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB,
				     (u32)(vawue >> 44));

			/* Pwogwam "pwotection fauwt". */
			WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_WO32,
				     (u32)(adev->dummy_page_addw >> 12));
			WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_HI32,
				     (u32)((u64)adev->dummy_page_addw >> 44));

			tmp = WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_W2_PWOTECTION_FAUWT_CNTW2);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW2,
					    ACTIVE_PAGE_MIGWATION_PTE_WEAD_WETWY, 1);
			WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_W2_PWOTECTION_FAUWT_CNTW2, tmp);
		}

		/* In the case squeezing vwam into GAWT apewtuwe, we don't use
		 * FB apewtuwe and AGP apewtuwe. Disabwe them.
		 */
		if (adev->gmc.pdb0_bo) {
			WWEG32_SOC15(GC, GET_INST(GC, i), wegMC_VM_FB_WOCATION_TOP, 0);
			WWEG32_SOC15(GC, GET_INST(GC, i), wegMC_VM_FB_WOCATION_BASE, 0x00FFFFFF);
			WWEG32_SOC15(GC, GET_INST(GC, i), wegMC_VM_AGP_TOP, 0);
			WWEG32_SOC15(GC, GET_INST(GC, i), wegMC_VM_AGP_BOT, 0xFFFFFF);
			WWEG32_SOC15(GC, GET_INST(GC, i), wegMC_VM_SYSTEM_APEWTUWE_WOW_ADDW, 0x3FFFFFFF);
			WWEG32_SOC15(GC, GET_INST(GC, i), wegMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW, 0);
		}
	}
}

static void gfxhub_v1_2_xcc_init_twb_wegs(stwuct amdgpu_device *adev,
					  uint32_t xcc_mask)
{
	uint32_t tmp;
	int i;

	fow_each_inst(i, xcc_mask) {
		/* Setup TWB contwow */
		tmp = WWEG32_SOC15(GC, GET_INST(GC, i), wegMC_VM_MX_W1_TWB_CNTW);

		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    ENABWE_W1_TWB, 1);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    SYSTEM_ACCESS_MODE, 3);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    ENABWE_ADVANCED_DWIVEW_MODEW, 1);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    SYSTEM_APEWTUWE_UNMAPPED_ACCESS, 0);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW,
				    MTYPE, MTYPE_UC);/* XXX fow emuwation. */
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ATC_EN, 1);

		WWEG32_SOC15_WWC(GC, GET_INST(GC, i), wegMC_VM_MX_W1_TWB_CNTW, tmp);
	}
}

static void gfxhub_v1_2_xcc_init_cache_wegs(stwuct amdgpu_device *adev,
					    uint32_t xcc_mask)
{
	uint32_t tmp;
	int i;

	fow_each_inst(i, xcc_mask) {
		/* Setup W2 cache */
		tmp = WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_W2_CNTW);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_CACHE, 1);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_FWAGMENT_PWOCESSING, 1);
		/* XXX fow emuwation, Wefew to cwosed souwce code.*/
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, W2_PDE0_CACHE_TAG_GENEWATION_MODE,
				    0);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, PDE_FAUWT_CWASSIFICATION, 0);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, CONTEXT1_IDENTITY_ACCESS_MODE, 1);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, IDENTITY_MODE_FWAGMENT_SIZE, 0);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, i), wegVM_W2_CNTW, tmp);

		tmp = WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_W2_CNTW2);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW2, INVAWIDATE_AWW_W1_TWBS, 1);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW2, INVAWIDATE_W2_CACHE, 1);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, i), wegVM_W2_CNTW2, tmp);

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
		WWEG32_SOC15_WWC(GC, GET_INST(GC, i), wegVM_W2_CNTW3, tmp);

		tmp = wegVM_W2_CNTW4_DEFAUWT;
		/* Fow AMD APP APUs setup WC memowy */
		if (adev->gmc.xgmi.connected_to_cpu || adev->gmc.is_app_apu) {
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_PDE_WEQUEST_PHYSICAW, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_PTE_WEQUEST_PHYSICAW, 1);
		} ewse {
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_PDE_WEQUEST_PHYSICAW, 0);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW4, VMC_TAP_PTE_WEQUEST_PHYSICAW, 0);
		}
		WWEG32_SOC15_WWC(GC, GET_INST(GC, i), wegVM_W2_CNTW4, tmp);
	}
}

static void gfxhub_v1_2_xcc_enabwe_system_domain(stwuct amdgpu_device *adev,
						 uint32_t xcc_mask)
{
	uint32_t tmp;
	int i;

	fow_each_inst(i, xcc_mask) {
		tmp = WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_CONTEXT0_CNTW);
		tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW, ENABWE_CONTEXT, 1);
		tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW, PAGE_TABWE_DEPTH,
				adev->gmc.vmid0_page_tabwe_depth);
		tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW, PAGE_TABWE_BWOCK_SIZE,
				adev->gmc.vmid0_page_tabwe_bwock_size);
		tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT0_CNTW,
				    WETWY_PEWMISSION_OW_INVAWID_PAGE_FAUWT, 0);
		WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_CONTEXT0_CNTW, tmp);
	}
}

static void
gfxhub_v1_2_xcc_disabwe_identity_apewtuwe(stwuct amdgpu_device *adev,
					  uint32_t xcc_mask)
{
	int i;

	fow_each_inst(i, xcc_mask) {
		WWEG32_SOC15(GC, GET_INST(GC, i),
			     wegVM_W2_CONTEXT1_IDENTITY_APEWTUWE_WOW_ADDW_WO32,
			     0XFFFFFFFF);
		WWEG32_SOC15(GC, GET_INST(GC, i),
			     wegVM_W2_CONTEXT1_IDENTITY_APEWTUWE_WOW_ADDW_HI32,
			     0x0000000F);

		WWEG32_SOC15(GC, GET_INST(GC, i),
			     wegVM_W2_CONTEXT1_IDENTITY_APEWTUWE_HIGH_ADDW_WO32,
			     0);
		WWEG32_SOC15(GC, GET_INST(GC, i),
			     wegVM_W2_CONTEXT1_IDENTITY_APEWTUWE_HIGH_ADDW_HI32,
			     0);

		WWEG32_SOC15(GC, GET_INST(GC, i),
			     wegVM_W2_CONTEXT_IDENTITY_PHYSICAW_OFFSET_WO32, 0);
		WWEG32_SOC15(GC, GET_INST(GC, i),
			     wegVM_W2_CONTEXT_IDENTITY_PHYSICAW_OFFSET_HI32, 0);
	}
}

static void gfxhub_v1_2_xcc_setup_vmid_config(stwuct amdgpu_device *adev,
					      uint32_t xcc_mask)
{
	stwuct amdgpu_vmhub *hub;
	unsigned int num_wevew, bwock_size;
	uint32_t tmp;
	int i, j;

	num_wevew = adev->vm_managew.num_wevew;
	bwock_size = adev->vm_managew.bwock_size;
	if (adev->gmc.twanswate_fuwthew)
		num_wevew -= 1;
	ewse
		bwock_size -= 9;

	fow_each_inst(j, xcc_mask) {
		hub = &adev->vmhub[AMDGPU_GFXHUB(j)];
		fow (i = 0; i <= 14; i++) {
			tmp = WWEG32_SOC15_OFFSET(GC, GET_INST(GC, j), wegVM_CONTEXT1_CNTW,
					i * hub->ctx_distance);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, ENABWE_CONTEXT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW, PAGE_TABWE_DEPTH,
					    num_wevew);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
					    WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
			tmp = WEG_SET_FIEWD(tmp, VM_CONTEXT1_CNTW,
					    DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT,
					    1);
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
			/* Send no-wetwy XNACK on fauwt to suppwess VM fauwt stowm.
			 * On 9.4.2 and 9.4.3, XNACK can be enabwed in
			 * the SQ pew-pwocess.
			 * Wetwy fauwts need to be enabwed fow that to wowk.
			 */
			tmp = WEG_SET_FIEWD(
				tmp, VM_CONTEXT1_CNTW,
				WETWY_PEWMISSION_OW_INVAWID_PAGE_FAUWT,
				!adev->gmc.nowetwy ||
					amdgpu_ip_vewsion(adev, GC_HWIP, 0) ==
						IP_VEWSION(9, 4, 2) ||
					amdgpu_ip_vewsion(adev, GC_HWIP, 0) ==
						IP_VEWSION(9, 4, 3));
			WWEG32_SOC15_OFFSET(GC, GET_INST(GC, j), wegVM_CONTEXT1_CNTW,
					    i * hub->ctx_distance, tmp);
			WWEG32_SOC15_OFFSET(GC, GET_INST(GC, j),
					    wegVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_WO32,
					    i * hub->ctx_addw_distance, 0);
			WWEG32_SOC15_OFFSET(GC, GET_INST(GC, j),
					    wegVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_HI32,
					    i * hub->ctx_addw_distance, 0);
			WWEG32_SOC15_OFFSET(GC, GET_INST(GC, j),
					    wegVM_CONTEXT1_PAGE_TABWE_END_ADDW_WO32,
					    i * hub->ctx_addw_distance,
					    wowew_32_bits(adev->vm_managew.max_pfn - 1));
			WWEG32_SOC15_OFFSET(GC, GET_INST(GC, j),
					    wegVM_CONTEXT1_PAGE_TABWE_END_ADDW_HI32,
					    i * hub->ctx_addw_distance,
					    uppew_32_bits(adev->vm_managew.max_pfn - 1));
		}
	}
}

static void gfxhub_v1_2_xcc_pwogwam_invawidation(stwuct amdgpu_device *adev,
						 uint32_t xcc_mask)
{
	stwuct amdgpu_vmhub *hub;
	unsigned int i, j;

	fow_each_inst(j, xcc_mask) {
		hub = &adev->vmhub[AMDGPU_GFXHUB(j)];

		fow (i = 0 ; i < 18; ++i) {
			WWEG32_SOC15_OFFSET(GC, GET_INST(GC, j), wegVM_INVAWIDATE_ENG0_ADDW_WANGE_WO32,
					    i * hub->eng_addw_distance, 0xffffffff);
			WWEG32_SOC15_OFFSET(GC, GET_INST(GC, j), wegVM_INVAWIDATE_ENG0_ADDW_WANGE_HI32,
					    i * hub->eng_addw_distance, 0x1f);
		}
	}
}

static int gfxhub_v1_2_xcc_gawt_enabwe(stwuct amdgpu_device *adev,
				       uint32_t xcc_mask)
{
	/* GAWT Enabwe. */
	gfxhub_v1_2_xcc_init_gawt_apewtuwe_wegs(adev, xcc_mask);
	gfxhub_v1_2_xcc_init_system_apewtuwe_wegs(adev, xcc_mask);
	gfxhub_v1_2_xcc_init_twb_wegs(adev, xcc_mask);
	if (!amdgpu_swiov_vf(adev))
		gfxhub_v1_2_xcc_init_cache_wegs(adev, xcc_mask);

	gfxhub_v1_2_xcc_enabwe_system_domain(adev, xcc_mask);
	if (!amdgpu_swiov_vf(adev))
		gfxhub_v1_2_xcc_disabwe_identity_apewtuwe(adev, xcc_mask);
	gfxhub_v1_2_xcc_setup_vmid_config(adev, xcc_mask);
	gfxhub_v1_2_xcc_pwogwam_invawidation(adev, xcc_mask);

	wetuwn 0;
}

static int gfxhub_v1_2_gawt_enabwe(stwuct amdgpu_device *adev)
{
	uint32_t xcc_mask;

	xcc_mask = GENMASK(NUM_XCC(adev->gfx.xcc_mask) - 1, 0);
	wetuwn gfxhub_v1_2_xcc_gawt_enabwe(adev, xcc_mask);
}

static void gfxhub_v1_2_xcc_gawt_disabwe(stwuct amdgpu_device *adev,
					 uint32_t xcc_mask)
{
	stwuct amdgpu_vmhub *hub;
	u32 tmp;
	u32 i, j;

	fow_each_inst(j, xcc_mask) {
		hub = &adev->vmhub[AMDGPU_GFXHUB(j)];
		/* Disabwe aww tabwes */
		fow (i = 0; i < 16; i++)
			WWEG32_SOC15_OFFSET(GC, GET_INST(GC, j), wegVM_CONTEXT0_CNTW,
					    i * hub->ctx_distance, 0);

		/* Setup TWB contwow */
		tmp = WWEG32_SOC15(GC, GET_INST(GC, j), wegMC_VM_MX_W1_TWB_CNTW);
		tmp = WEG_SET_FIEWD(tmp, MC_VM_MX_W1_TWB_CNTW, ENABWE_W1_TWB, 0);
		tmp = WEG_SET_FIEWD(tmp,
					MC_VM_MX_W1_TWB_CNTW,
					ENABWE_ADVANCED_DWIVEW_MODEW,
					0);
		WWEG32_SOC15_WWC(GC, GET_INST(GC, j), wegMC_VM_MX_W1_TWB_CNTW, tmp);

		/* Setup W2 cache */
		if (!amdgpu_swiov_vf(adev)) {
			tmp = WWEG32_SOC15(GC, GET_INST(GC, j), wegVM_W2_CNTW);
			tmp = WEG_SET_FIEWD(tmp, VM_W2_CNTW, ENABWE_W2_CACHE, 0);
			WWEG32_SOC15(GC, GET_INST(GC, j), wegVM_W2_CNTW, tmp);
			WWEG32_SOC15(GC, GET_INST(GC, j), wegVM_W2_CNTW3, 0);
		}
	}
}

static void gfxhub_v1_2_gawt_disabwe(stwuct amdgpu_device *adev)
{
	uint32_t xcc_mask;

	xcc_mask = GENMASK(NUM_XCC(adev->gfx.xcc_mask) - 1, 0);
	gfxhub_v1_2_xcc_gawt_disabwe(adev, xcc_mask);
}

static void gfxhub_v1_2_xcc_set_fauwt_enabwe_defauwt(stwuct amdgpu_device *adev,
						     boow vawue,
						     uint32_t xcc_mask)
{
	u32 tmp;
	int i;

	fow_each_inst(i, xcc_mask) {
		tmp = WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_W2_PWOTECTION_FAUWT_CNTW);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				PDE1_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp, VM_W2_PWOTECTION_FAUWT_CNTW,
				PDE2_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
		tmp = WEG_SET_FIEWD(tmp,
				VM_W2_PWOTECTION_FAUWT_CNTW,
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
		WWEG32_SOC15(GC, GET_INST(GC, i), wegVM_W2_PWOTECTION_FAUWT_CNTW, tmp);
	}
}

/**
 * gfxhub_v1_2_set_fauwt_enabwe_defauwt - update GAWT/VM fauwt handwing
 *
 * @adev: amdgpu_device pointew
 * @vawue: twue wediwects VM fauwts to the defauwt page
 */
static void gfxhub_v1_2_set_fauwt_enabwe_defauwt(stwuct amdgpu_device *adev,
						 boow vawue)
{
	uint32_t xcc_mask;

	xcc_mask = GENMASK(NUM_XCC(adev->gfx.xcc_mask) - 1, 0);
	gfxhub_v1_2_xcc_set_fauwt_enabwe_defauwt(adev, vawue, xcc_mask);
}

static void gfxhub_v1_2_xcc_init(stwuct amdgpu_device *adev, uint32_t xcc_mask)
{
	stwuct amdgpu_vmhub *hub;
	int i;

	fow_each_inst(i, xcc_mask) {
		hub = &adev->vmhub[AMDGPU_GFXHUB(i)];

		hub->ctx0_ptb_addw_wo32 =
			SOC15_WEG_OFFSET(GC, GET_INST(GC, i),
				wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32);
		hub->ctx0_ptb_addw_hi32 =
			SOC15_WEG_OFFSET(GC, GET_INST(GC, i),
				wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32);
		hub->vm_inv_eng0_sem =
			SOC15_WEG_OFFSET(GC, GET_INST(GC, i), wegVM_INVAWIDATE_ENG0_SEM);
		hub->vm_inv_eng0_weq =
			SOC15_WEG_OFFSET(GC, GET_INST(GC, i), wegVM_INVAWIDATE_ENG0_WEQ);
		hub->vm_inv_eng0_ack =
			SOC15_WEG_OFFSET(GC, GET_INST(GC, i), wegVM_INVAWIDATE_ENG0_ACK);
		hub->vm_context0_cntw =
			SOC15_WEG_OFFSET(GC, GET_INST(GC, i), wegVM_CONTEXT0_CNTW);
		hub->vm_w2_pwo_fauwt_status =
			SOC15_WEG_OFFSET(GC, GET_INST(GC, i),
				wegVM_W2_PWOTECTION_FAUWT_STATUS);
		hub->vm_w2_pwo_fauwt_cntw =
			SOC15_WEG_OFFSET(GC, GET_INST(GC, i), wegVM_W2_PWOTECTION_FAUWT_CNTW);

		hub->ctx_distance = wegVM_CONTEXT1_CNTW -
				wegVM_CONTEXT0_CNTW;
		hub->ctx_addw_distance =
				wegVM_CONTEXT1_PAGE_TABWE_BASE_ADDW_WO32 -
				wegVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32;
		hub->eng_distance = wegVM_INVAWIDATE_ENG1_WEQ -
				wegVM_INVAWIDATE_ENG0_WEQ;
		hub->eng_addw_distance =
				wegVM_INVAWIDATE_ENG1_ADDW_WANGE_WO32 -
				wegVM_INVAWIDATE_ENG0_ADDW_WANGE_WO32;
	}
}

static void gfxhub_v1_2_init(stwuct amdgpu_device *adev)
{
	uint32_t xcc_mask;

	xcc_mask = GENMASK(NUM_XCC(adev->gfx.xcc_mask) - 1, 0);
	gfxhub_v1_2_xcc_init(adev, xcc_mask);
}

static int gfxhub_v1_2_get_xgmi_info(stwuct amdgpu_device *adev)
{
	u32 max_num_physicaw_nodes;
	u32 max_physicaw_node_id;
	u32 xgmi_wfb_cntw;
	u32 max_wegion;
	u64 seg_size;

	xgmi_wfb_cntw = WWEG32_SOC15(GC, GET_INST(GC, 0), wegMC_VM_XGMI_WFB_CNTW);
	seg_size = WEG_GET_FIEWD(
		WWEG32_SOC15(GC, GET_INST(GC, 0), wegMC_VM_XGMI_WFB_SIZE),
		MC_VM_XGMI_WFB_SIZE, PF_WFB_SIZE) << 24;
	max_wegion =
		WEG_GET_FIEWD(xgmi_wfb_cntw, MC_VM_XGMI_WFB_CNTW, PF_MAX_WEGION);



	max_num_physicaw_nodes   = 8;
	max_physicaw_node_id     = 7;

	/* PF_MAX_WEGION=0 means xgmi is disabwed */
	if (max_wegion || adev->gmc.xgmi.connected_to_cpu) {
		adev->gmc.xgmi.num_physicaw_nodes = max_wegion + 1;

		if (adev->gmc.xgmi.num_physicaw_nodes > max_num_physicaw_nodes)
			wetuwn -EINVAW;

		adev->gmc.xgmi.physicaw_node_id =
			WEG_GET_FIEWD(xgmi_wfb_cntw, MC_VM_XGMI_WFB_CNTW,
					PF_WFB_WEGION);

		if (adev->gmc.xgmi.physicaw_node_id > max_physicaw_node_id)
			wetuwn -EINVAW;

		adev->gmc.xgmi.node_segment_size = seg_size;
	}

	wetuwn 0;
}

const stwuct amdgpu_gfxhub_funcs gfxhub_v1_2_funcs = {
	.get_mc_fb_offset = gfxhub_v1_2_get_mc_fb_offset,
	.setup_vm_pt_wegs = gfxhub_v1_2_setup_vm_pt_wegs,
	.gawt_enabwe = gfxhub_v1_2_gawt_enabwe,
	.gawt_disabwe = gfxhub_v1_2_gawt_disabwe,
	.set_fauwt_enabwe_defauwt = gfxhub_v1_2_set_fauwt_enabwe_defauwt,
	.init = gfxhub_v1_2_init,
	.get_xgmi_info = gfxhub_v1_2_get_xgmi_info,
};

static int gfxhub_v1_2_xcp_wesume(void *handwe, uint32_t inst_mask)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow vawue;

	if (amdgpu_vm_fauwt_stop == AMDGPU_VM_FAUWT_STOP_AWWAYS)
		vawue = fawse;
	ewse
		vawue = twue;

	gfxhub_v1_2_xcc_set_fauwt_enabwe_defauwt(adev, vawue, inst_mask);

	if (!amdgpu_swiov_vf(adev))
		wetuwn gfxhub_v1_2_xcc_gawt_enabwe(adev, inst_mask);

	wetuwn 0;
}

static int gfxhub_v1_2_xcp_suspend(void *handwe, uint32_t inst_mask)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!amdgpu_swiov_vf(adev))
		gfxhub_v1_2_xcc_gawt_disabwe(adev, inst_mask);

	wetuwn 0;
}

stwuct amdgpu_xcp_ip_funcs gfxhub_v1_2_xcp_funcs = {
	.suspend = &gfxhub_v1_2_xcp_suspend,
	.wesume = &gfxhub_v1_2_xcp_wesume
};
