/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
#incwude "gfxhub_v2_1.h"

#incwude "gc/gc_10_3_0_offset.h"
#incwude "gc/gc_10_3_0_sh_mask.h"
#incwude "gc/gc_10_3_0_defauwt.h"
#incwude "navi10_enum.h"

#incwude "soc15_common.h"

#define mmGCUTCW2_HAWVEST_BYPASS_GWOUPS_YEWWOW_CAWP				0x16f8
#define mmGCUTCW2_HAWVEST_BYPASS_GWOUPS_YEWWOW_CAWP_BASE_IDX	0

static const chaw * const gfxhub_cwient_ids[] = {
	"CB/DB",
	"Wesewved",
	"GE1",
	"GE2",
	"CPF",
	"CPC",
	"CPG",
	"WWC",
	"TCP",
	"SQC (inst)",
	"SQC (data)",
	"SQG",
	"Wesewved",
	"SDMA0",
	"SDMA1",
	"GCW",
	"SDMA2",
	"SDMA3",
};

static uint32_t gfxhub_v2_1_get_invawidate_weq(unsigned int vmid,
					       uint32_t fwush_type)
{
	u32 weq = 0;

	/* invawidate using wegacy mode on vmid*/
	weq = WEG_SET_FIEWD(weq, GCVM_INVAWIDATE_ENG0_WEQ,
			    PEW_VMID_INVAWIDATE_WEQ, 1 << vmid);
	weq = WEG_SET_FIEWD(weq, GCVM_INVAWIDATE_ENG0_WEQ, FWUSH_TYPE, fwush_type);
	weq = WEG_SET_FIEWD(weq, GCVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W2_PTES, 1);
	weq = WEG_SET_FIEWD(weq, GCVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W2_PDE0, 1);
	weq = WEG_SET_FIEWD(weq, GCVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W2_PDE1, 1);
	weq = WEG_SET_FIEWD(weq, GCVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W2_PDE2, 1);
	weq = WEG_SET_FIEWD(weq, GCVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W1_PTES, 1);
	weq = WEG_SET_FIEWD(weq, GCVM_INVAWIDATE_ENG0_WEQ,
			    CWEAW_PWOTECTION_FAUWT_STATUS_ADDW,	0);

	wetuwn weq;
}

static void
gfxhub_v2_1_pwint_w2_pwotection_fauwt_status(stwuct amdgpu_device *adev,
					     uint32_t status)
{
	u32 cid = WEG_GET_FIEWD(status,
				GCVM_W2_PWOTECTION_FAUWT_STATUS, CID);

	dev_eww(adev->dev,
		"GCVM_W2_PWOTECTION_FAUWT_STATUS:0x%08X\n",
		status);
	dev_eww(adev->dev, "\t Fauwty UTCW2 cwient ID: %s (0x%x)\n",
		cid >= AWWAY_SIZE(gfxhub_cwient_ids) ? "unknown" : gfxhub_cwient_ids[cid],
		cid);
	dev_eww(adev->dev, "\t MOWE_FAUWTS: 0x%wx\n",
		WEG_GET_FIEWD(status,
		GCVM_W2_PWOTECTION_FAUWT_STATUS, MOWE_FAUWTS));
	dev_eww(adev->dev, "\t WAWKEW_EWWOW: 0x%wx\n",
		WEG_GET_FIEWD(status,
		GCVM_W2_PWOTECTION_FAUWT_STATUS, WAWKEW_EWWOW));
	dev_eww(adev->dev, "\t PEWMISSION_FAUWTS: 0x%wx\n",
		WEG_GET_FIEWD(status,
		GCVM_W2_PWOTECTION_FAUWT_STATUS, PEWMISSION_FAUWTS));
	dev_eww(adev->dev, "\t MAPPING_EWWOW: 0x%wx\n",
		WEG_GET_FIEWD(status,
		GCVM_W2_PWOTECTION_FAUWT_STATUS, MAPPING_EWWOW));
	dev_eww(adev->dev, "\t WW: 0x%wx\n",
		WEG_GET_FIEWD(status,
		GCVM_W2_PWOTECTION_FAUWT_STATUS, WW));
}

static u64 gfxhub_v2_1_get_fb_wocation(stwuct amdgpu_device *adev)
{
	u64 base = WWEG32_SOC15(GC, 0, mmGCMC_VM_FB_WOCATION_BASE);

	base &= GCMC_VM_FB_WOCATION_BASE__FB_BASE_MASK;
	base <<= 24;

	wetuwn base;
}

static u64 gfxhub_v2_1_get_mc_fb_offset(stwuct amdgpu_device *adev)
{
	wetuwn (u64)WWEG32_SOC15(GC, 0, mmGCMC_VM_FB_OFFSET) << 24;
}

static void gfxhub_v2_1_setup_vm_pt_wegs(stwuct amdgpu_device *adev, uint32_t vmid,
				uint64_t page_tabwe_base)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB(0)];

	WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32,
			    hub->ctx_addw_distance * vmid,
			    wowew_32_bits(page_tabwe_base));

	WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32,
			    hub->ctx_addw_distance * vmid,
			    uppew_32_bits(page_tabwe_base));
}

static void gfxhub_v2_1_init_gawt_apewtuwe_wegs(stwuct amdgpu_device *adev)
{
	uint64_t pt_base = amdgpu_gmc_pd_addw(adev->gawt.bo);

	gfxhub_v2_1_setup_vm_pt_wegs(adev, 0, pt_base);

	WWEG32_SOC15(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32,
		     (u32)(adev->gmc.gawt_stawt >> 12));
	WWEG32_SOC15(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32,
		     (u32)(adev->gmc.gawt_stawt >> 44));

	WWEG32_SOC15(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32,
		     (u32)(adev->gmc.gawt_end >> 12));
	WWEG32_SOC15(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32,
		     (u32)(adev->gmc.gawt_end >> 44));
}

static void gfxhub_v2_1_init_system_apewtuwe_wegs(stwuct amdgpu_device *adev)
{
	uint64_t vawue;

	/* Pwogwam the AGP BAW */
	WWEG32_SOC15(GC, 0, mmGCMC_VM_AGP_BASE, 0);
	WWEG32_SOC15(GC, 0, mmGCMC_VM_AGP_BOT, adev->gmc.agp_stawt >> 24);
	WWEG32_SOC15(GC, 0, mmGCMC_VM_AGP_TOP, adev->gmc.agp_end >> 24);

	/* Pwogwam the system apewtuwe wow wogicaw page numbew. */
	WWEG32_SOC15(GC, 0, mmGCMC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
		     min(adev->gmc.fb_stawt, adev->gmc.agp_stawt) >> 18);
	WWEG32_SOC15(GC, 0, mmGCMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
		     max(adev->gmc.fb_end, adev->gmc.agp_end) >> 18);

	/* Set defauwt page addwess. */
	vawue = amdgpu_gmc_vwam_mc2pa(adev, adev->mem_scwatch.gpu_addw);
	WWEG32_SOC15(GC, 0, mmGCMC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB,
		     (u32)(vawue >> 12));
	WWEG32_SOC15(GC, 0, mmGCMC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB,
		     (u32)(vawue >> 44));

	/* Pwogwam "pwotection fauwt". */
	WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_WO32,
		     (u32)(adev->dummy_page_addw >> 12));
	WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_HI32,
		     (u32)((u64)adev->dummy_page_addw >> 44));

	WWEG32_FIEWD15(GC, 0, GCVM_W2_PWOTECTION_FAUWT_CNTW2,
		       ACTIVE_PAGE_MIGWATION_PTE_WEAD_WETWY, 1);
}


static void gfxhub_v2_1_init_twb_wegs(stwuct amdgpu_device *adev)
{
	uint32_t tmp;

	/* Setup TWB contwow */
	tmp = WWEG32_SOC15(GC, 0, mmGCMC_VM_MX_W1_TWB_CNTW);

	tmp = WEG_SET_FIEWD(tmp, GCMC_VM_MX_W1_TWB_CNTW, ENABWE_W1_TWB, 1);
	tmp = WEG_SET_FIEWD(tmp, GCMC_VM_MX_W1_TWB_CNTW, SYSTEM_ACCESS_MODE, 3);
	tmp = WEG_SET_FIEWD(tmp, GCMC_VM_MX_W1_TWB_CNTW,
			    ENABWE_ADVANCED_DWIVEW_MODEW, 1);
	tmp = WEG_SET_FIEWD(tmp, GCMC_VM_MX_W1_TWB_CNTW,
			    SYSTEM_APEWTUWE_UNMAPPED_ACCESS, 0);
	tmp = WEG_SET_FIEWD(tmp, GCMC_VM_MX_W1_TWB_CNTW,
			    MTYPE, MTYPE_UC); /* UC, uncached */

	WWEG32_SOC15(GC, 0, mmGCMC_VM_MX_W1_TWB_CNTW, tmp);
}

static void gfxhub_v2_1_init_cache_wegs(stwuct amdgpu_device *adev)
{
	uint32_t tmp;

	/* These wegistews awe not accessibwe to VF-SWIOV.
	 * The PF wiww pwogwam them instead.
	 */
	if (amdgpu_swiov_vf(adev))
		wetuwn;

	/* Setup W2 cache */
	tmp = WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW, ENABWE_W2_CACHE, 1);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW, ENABWE_W2_FWAGMENT_PWOCESSING, 0);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW,
			    ENABWE_DEFAUWT_PAGE_OUT_TO_SYSTEM_MEMOWY, 1);
	/* XXX fow emuwation, Wefew to cwosed souwce code.*/
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW,
			    W2_PDE0_CACHE_TAG_GENEWATION_MODE, 0);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW, PDE_FAUWT_CWASSIFICATION, 0);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW, CONTEXT1_IDENTITY_ACCESS_MODE, 1);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW, IDENTITY_MODE_FWAGMENT_SIZE, 0);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW, tmp);

	tmp = WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW2);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW2, INVAWIDATE_AWW_W1_TWBS, 1);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW2, INVAWIDATE_W2_CACHE, 1);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW2, tmp);

	tmp = mmGCVM_W2_CNTW3_DEFAUWT;
	if (adev->gmc.twanswate_fuwthew) {
		tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW3, BANK_SEWECT, 12);
		tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW3,
				    W2_CACHE_BIGK_FWAGMENT_SIZE, 9);
	} ewse {
		tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW3, BANK_SEWECT, 9);
		tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW3,
				    W2_CACHE_BIGK_FWAGMENT_SIZE, 6);
	}
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW3, tmp);

	tmp = mmGCVM_W2_CNTW4_DEFAUWT;
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW4, VMC_TAP_PDE_WEQUEST_PHYSICAW, 0);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW4, VMC_TAP_PTE_WEQUEST_PHYSICAW, 0);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW4, tmp);

	tmp = mmGCVM_W2_CNTW5_DEFAUWT;
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_CNTW5, W2_CACHE_SMAWWK_FWAGMENT_SIZE, 0);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW5, tmp);
}

static void gfxhub_v2_1_enabwe_system_domain(stwuct amdgpu_device *adev)
{
	uint32_t tmp;

	tmp = WWEG32_SOC15(GC, 0, mmGCVM_CONTEXT0_CNTW);
	tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT0_CNTW, ENABWE_CONTEXT, 1);
	tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT0_CNTW, PAGE_TABWE_DEPTH, 0);
	tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT0_CNTW,
			    WETWY_PEWMISSION_OW_INVAWID_PAGE_FAUWT, 0);
	WWEG32_SOC15(GC, 0, mmGCVM_CONTEXT0_CNTW, tmp);
}

static void gfxhub_v2_1_disabwe_identity_apewtuwe(stwuct amdgpu_device *adev)
{
	/* These wegistews awe not accessibwe to VF-SWIOV.
	 * The PF wiww pwogwam them instead.
	 */
	if (amdgpu_swiov_vf(adev))
		wetuwn;

	WWEG32_SOC15(GC, 0, mmGCVM_W2_CONTEXT1_IDENTITY_APEWTUWE_WOW_ADDW_WO32,
		     0xFFFFFFFF);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CONTEXT1_IDENTITY_APEWTUWE_WOW_ADDW_HI32,
		     0x0000000F);

	WWEG32_SOC15(GC, 0, mmGCVM_W2_CONTEXT1_IDENTITY_APEWTUWE_HIGH_ADDW_WO32,
		     0);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CONTEXT1_IDENTITY_APEWTUWE_HIGH_ADDW_HI32,
		     0);

	WWEG32_SOC15(GC, 0, mmGCVM_W2_CONTEXT_IDENTITY_PHYSICAW_OFFSET_WO32, 0);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CONTEXT_IDENTITY_PHYSICAW_OFFSET_HI32, 0);

}

static void gfxhub_v2_1_setup_vmid_config(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB(0)];
	int i;
	uint32_t tmp;

	fow (i = 0; i <= 14; i++) {
		tmp = WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_CNTW, i * hub->ctx_distance);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW, ENABWE_CONTEXT, 1);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW, PAGE_TABWE_DEPTH,
				    adev->vm_managew.num_wevew);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW,
				WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW,
				DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW,
				PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW,
				VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW,
				WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW,
				WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW,
				EXECUTE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW,
				PAGE_TABWE_BWOCK_SIZE,
				adev->vm_managew.bwock_size - 9);
		/* Send no-wetwy XNACK on fauwt to suppwess VM fauwt stowm. */
		tmp = WEG_SET_FIEWD(tmp, GCVM_CONTEXT1_CNTW,
				    WETWY_PEWMISSION_OW_INVAWID_PAGE_FAUWT,
				    !adev->gmc.nowetwy);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_CNTW,
				    i * hub->ctx_distance, tmp);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_WO32,
				    i * hub->ctx_addw_distance, 0);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_HI32,
				    i * hub->ctx_addw_distance, 0);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABWE_END_ADDW_WO32,
				    i * hub->ctx_addw_distance,
				    wowew_32_bits(adev->vm_managew.max_pfn - 1));
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABWE_END_ADDW_HI32,
				    i * hub->ctx_addw_distance,
				    uppew_32_bits(adev->vm_managew.max_pfn - 1));
	}

	hub->vm_cntx_cntw = tmp;
}

static void gfxhub_v2_1_pwogwam_invawidation(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB(0)];
	unsigned int i;

	fow (i = 0 ; i < 18; ++i) {
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_INVAWIDATE_ENG0_ADDW_WANGE_WO32,
				    i * hub->eng_addw_distance, 0xffffffff);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_INVAWIDATE_ENG0_ADDW_WANGE_HI32,
				    i * hub->eng_addw_distance, 0x1f);
	}
}

static int gfxhub_v2_1_gawt_enabwe(stwuct amdgpu_device *adev)
{
	if (amdgpu_swiov_vf(adev)) {
		/*
		 * GCMC_VM_FB_WOCATION_BASE/TOP is NUWW fow VF, becuase they awe
		 * VF copy wegistews so vbios post doesn't pwogwam them, fow
		 * SWIOV dwivew need to pwogwam them
		 */
		WWEG32_SOC15(GC, 0, mmGCMC_VM_FB_WOCATION_BASE,
			     adev->gmc.vwam_stawt >> 24);
		WWEG32_SOC15(GC, 0, mmGCMC_VM_FB_WOCATION_TOP,
			     adev->gmc.vwam_end >> 24);
	}

	/* GAWT Enabwe. */
	gfxhub_v2_1_init_gawt_apewtuwe_wegs(adev);
	gfxhub_v2_1_init_system_apewtuwe_wegs(adev);
	gfxhub_v2_1_init_twb_wegs(adev);
	gfxhub_v2_1_init_cache_wegs(adev);

	gfxhub_v2_1_enabwe_system_domain(adev);
	gfxhub_v2_1_disabwe_identity_apewtuwe(adev);
	gfxhub_v2_1_setup_vmid_config(adev);
	gfxhub_v2_1_pwogwam_invawidation(adev);

	wetuwn 0;
}

static void gfxhub_v2_1_gawt_disabwe(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB(0)];
	u32 tmp;
	u32 i;

	/* Disabwe aww tabwes */
	fow (i = 0; i < 16; i++)
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_CNTW,
				    i * hub->ctx_distance, 0);

	/* Setup TWB contwow */
	tmp = WWEG32_SOC15(GC, 0, mmGCMC_VM_MX_W1_TWB_CNTW);
	tmp = WEG_SET_FIEWD(tmp, GCMC_VM_MX_W1_TWB_CNTW, ENABWE_W1_TWB, 0);
	tmp = WEG_SET_FIEWD(tmp, GCMC_VM_MX_W1_TWB_CNTW,
			    ENABWE_ADVANCED_DWIVEW_MODEW, 0);
	WWEG32_SOC15(GC, 0, mmGCMC_VM_MX_W1_TWB_CNTW, tmp);

	if (amdgpu_swiov_vf(adev))
		wetuwn;

	/* Setup W2 cache */
	WWEG32_FIEWD15(GC, 0, GCVM_W2_CNTW, ENABWE_W2_CACHE, 0);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW3, 0);
}

/**
 * gfxhub_v2_1_set_fauwt_enabwe_defauwt - update GAWT/VM fauwt handwing
 *
 * @adev: amdgpu_device pointew
 * @vawue: twue wediwects VM fauwts to the defauwt page
 */
static void gfxhub_v2_1_set_fauwt_enabwe_defauwt(stwuct amdgpu_device *adev,
					  boow vawue)
{
	u32 tmp;

	/* These wegistews awe not accessibwe to VF-SWIOV.
	 * The PF wiww pwogwam them instead.
	 */
	if (amdgpu_swiov_vf(adev))
		wetuwn;

	tmp = WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_CNTW);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    PDE1_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    PDE2_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    TWANSWATE_FUWTHEW_PWOTECTION_FAUWT_ENABWE_DEFAUWT,
			    vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    NACK_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
			    EXECUTE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	if (!vawue) {
		tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
				CWASH_ON_NO_WETWY_FAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, GCVM_W2_PWOTECTION_FAUWT_CNTW,
				CWASH_ON_WETWY_FAUWT, 1);
	}
	WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_CNTW, tmp);
}

static const stwuct amdgpu_vmhub_funcs gfxhub_v2_1_vmhub_funcs = {
	.pwint_w2_pwotection_fauwt_status = gfxhub_v2_1_pwint_w2_pwotection_fauwt_status,
	.get_invawidate_weq = gfxhub_v2_1_get_invawidate_weq,
};

static void gfxhub_v2_1_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB(0)];

	hub->ctx0_ptb_addw_wo32 =
		SOC15_WEG_OFFSET(GC, 0,
				 mmGCVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32);
	hub->ctx0_ptb_addw_hi32 =
		SOC15_WEG_OFFSET(GC, 0,
				 mmGCVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32);
	hub->vm_inv_eng0_sem =
		SOC15_WEG_OFFSET(GC, 0, mmGCVM_INVAWIDATE_ENG0_SEM);
	hub->vm_inv_eng0_weq =
		SOC15_WEG_OFFSET(GC, 0, mmGCVM_INVAWIDATE_ENG0_WEQ);
	hub->vm_inv_eng0_ack =
		SOC15_WEG_OFFSET(GC, 0, mmGCVM_INVAWIDATE_ENG0_ACK);
	hub->vm_context0_cntw =
		SOC15_WEG_OFFSET(GC, 0, mmGCVM_CONTEXT0_CNTW);
	hub->vm_w2_pwo_fauwt_status =
		SOC15_WEG_OFFSET(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_STATUS);
	hub->vm_w2_pwo_fauwt_cntw =
		SOC15_WEG_OFFSET(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_CNTW);

	hub->ctx_distance = mmGCVM_CONTEXT1_CNTW - mmGCVM_CONTEXT0_CNTW;
	hub->ctx_addw_distance = mmGCVM_CONTEXT1_PAGE_TABWE_BASE_ADDW_WO32 -
		mmGCVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32;
	hub->eng_distance = mmGCVM_INVAWIDATE_ENG1_WEQ -
		mmGCVM_INVAWIDATE_ENG0_WEQ;
	hub->eng_addw_distance = mmGCVM_INVAWIDATE_ENG1_ADDW_WANGE_WO32 -
		mmGCVM_INVAWIDATE_ENG0_ADDW_WANGE_WO32;

	hub->vm_cntx_cntw_vm_fauwt = GCVM_CONTEXT1_CNTW__WANGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		GCVM_CONTEXT1_CNTW__DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		GCVM_CONTEXT1_CNTW__PDE0_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		GCVM_CONTEXT1_CNTW__VAWID_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		GCVM_CONTEXT1_CNTW__WEAD_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		GCVM_CONTEXT1_CNTW__WWITE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		GCVM_CONTEXT1_CNTW__EXECUTE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK;

	hub->vmhub_funcs = &gfxhub_v2_1_vmhub_funcs;
}

static int gfxhub_v2_1_get_xgmi_info(stwuct amdgpu_device *adev)
{
	u32 xgmi_wfb_cntw = WWEG32_SOC15(GC, 0, mmGCMC_VM_XGMI_WFB_CNTW);
	u32 max_wegion =
		WEG_GET_FIEWD(xgmi_wfb_cntw, GCMC_VM_XGMI_WFB_CNTW, PF_MAX_WEGION);
	u32 max_num_physicaw_nodes   = 0;
	u32 max_physicaw_node_id     = 0;

	switch (amdgpu_ip_vewsion(adev, XGMI_HWIP, 0)) {
	case IP_VEWSION(4, 8, 0):
		max_num_physicaw_nodes   = 4;
		max_physicaw_node_id     = 3;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* PF_MAX_WEGION=0 means xgmi is disabwed */
	if (max_wegion) {
		adev->gmc.xgmi.num_physicaw_nodes = max_wegion + 1;
		if (adev->gmc.xgmi.num_physicaw_nodes > max_num_physicaw_nodes)
			wetuwn -EINVAW;

		adev->gmc.xgmi.physicaw_node_id =
			WEG_GET_FIEWD(xgmi_wfb_cntw, GCMC_VM_XGMI_WFB_CNTW, PF_WFB_WEGION);
		if (adev->gmc.xgmi.physicaw_node_id > max_physicaw_node_id)
			wetuwn -EINVAW;

		adev->gmc.xgmi.node_segment_size = WEG_GET_FIEWD(
			WWEG32_SOC15(GC, 0, mmGCMC_VM_XGMI_WFB_SIZE),
			GCMC_VM_XGMI_WFB_SIZE, PF_WFB_SIZE) << 24;
	}

	wetuwn 0;
}

static void gfxhub_v2_1_utcw2_hawvest(stwuct amdgpu_device *adev)
{
	int i;
	u32 tmp = 0, disabwed_sa = 0;
	u32 efuse_setting, vbios_setting;

	u32 max_sa_mask = amdgpu_gfx_cweate_bitmask(
		adev->gfx.config.max_sh_pew_se *
		adev->gfx.config.max_shadew_engines);

	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(10, 3, 1):
	case IP_VEWSION(10, 3, 3):
		/* Get SA disabwed bitmap fwom eFuse setting */
		efuse_setting = WWEG32_SOC15(GC, 0, mmCC_GC_SA_UNIT_DISABWE);
		efuse_setting &= CC_GC_SA_UNIT_DISABWE__SA_DISABWE_MASK;
		efuse_setting >>= CC_GC_SA_UNIT_DISABWE__SA_DISABWE__SHIFT;

		/* Get SA disabwed bitmap fwom VBIOS setting */
		vbios_setting = WWEG32_SOC15(GC, 0, mmGC_USEW_SA_UNIT_DISABWE);
		vbios_setting &= GC_USEW_SA_UNIT_DISABWE__SA_DISABWE_MASK;
		vbios_setting >>= GC_USEW_SA_UNIT_DISABWE__SA_DISABWE__SHIFT;

		disabwed_sa |= efuse_setting | vbios_setting;
		/* Make suwe not to wepowt hawvested SAs beyond the max SA count */
		disabwed_sa &= max_sa_mask;

		fow (i = 0; disabwed_sa > 0; i++) {
			if (disabwed_sa & 1)
				tmp |= 0x3 << (i * 2);
			disabwed_sa >>= 1;
		}
		disabwed_sa = tmp;

		WWEG32_SOC15(GC, 0, mmGCUTCW2_HAWVEST_BYPASS_GWOUPS_YEWWOW_CAWP, disabwed_sa);
		bweak;
	defauwt:
		bweak;
	}
}

static void gfxhub_v2_1_save_wegs(stwuct amdgpu_device *adev)
{
	int i;

	adev->gmc.VM_W2_CNTW = WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW);
	adev->gmc.VM_W2_CNTW2 = WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW2);
	adev->gmc.VM_DUMMY_PAGE_FAUWT_CNTW = WWEG32_SOC15(GC, 0, mmGCVM_DUMMY_PAGE_FAUWT_CNTW);
	adev->gmc.VM_DUMMY_PAGE_FAUWT_ADDW_WO32 = WWEG32_SOC15(GC, 0, mmGCVM_DUMMY_PAGE_FAUWT_ADDW_WO32);
	adev->gmc.VM_DUMMY_PAGE_FAUWT_ADDW_HI32 = WWEG32_SOC15(GC, 0, mmGCVM_DUMMY_PAGE_FAUWT_ADDW_HI32);
	adev->gmc.VM_W2_PWOTECTION_FAUWT_CNTW = WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_CNTW);
	adev->gmc.VM_W2_PWOTECTION_FAUWT_CNTW2 = WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_CNTW2);
	adev->gmc.VM_W2_PWOTECTION_FAUWT_MM_CNTW3 = WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_MM_CNTW3);
	adev->gmc.VM_W2_PWOTECTION_FAUWT_MM_CNTW4 = WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_MM_CNTW4);
	adev->gmc.VM_W2_PWOTECTION_FAUWT_ADDW_WO32 = WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_ADDW_WO32);
	adev->gmc.VM_W2_PWOTECTION_FAUWT_ADDW_HI32 = WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_ADDW_HI32);
	adev->gmc.VM_DEBUG = WWEG32_SOC15(GC, 0, mmGCVM_DEBUG);
	adev->gmc.VM_W2_MM_GWOUP_WT_CWASSES = WWEG32_SOC15(GC, 0, mmGCVM_W2_MM_GWOUP_WT_CWASSES);
	adev->gmc.VM_W2_BANK_SEWECT_WESEWVED_CID = WWEG32_SOC15(GC, 0, mmGCVM_W2_BANK_SEWECT_WESEWVED_CID);
	adev->gmc.VM_W2_BANK_SEWECT_WESEWVED_CID2 = WWEG32_SOC15(GC, 0, mmGCVM_W2_BANK_SEWECT_WESEWVED_CID2);
	adev->gmc.VM_W2_CACHE_PAWITY_CNTW = WWEG32_SOC15(GC, 0, mmGCVM_W2_CACHE_PAWITY_CNTW);
	adev->gmc.VM_W2_IH_WOG_CNTW = WWEG32_SOC15(GC, 0, mmGCVM_W2_IH_WOG_CNTW);

	fow (i = 0; i <= 15; i++) {
		adev->gmc.VM_CONTEXT_CNTW[i] = WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_CNTW, i);
		adev->gmc.VM_CONTEXT_PAGE_TABWE_BASE_ADDW_WO32[i] = WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32, i * 2);
		adev->gmc.VM_CONTEXT_PAGE_TABWE_BASE_ADDW_HI32[i] = WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32, i * 2);
		adev->gmc.VM_CONTEXT_PAGE_TABWE_STAWT_ADDW_WO32[i] = WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32, i * 2);
		adev->gmc.VM_CONTEXT_PAGE_TABWE_STAWT_ADDW_HI32[i] = WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32, i * 2);
		adev->gmc.VM_CONTEXT_PAGE_TABWE_END_ADDW_WO32[i] = WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32, i * 2);
		adev->gmc.VM_CONTEXT_PAGE_TABWE_END_ADDW_HI32[i] = WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32, i * 2);
	}

	adev->gmc.MC_VM_MX_W1_TWB_CNTW = WWEG32_SOC15(GC, 0, mmGCMC_VM_MX_W1_TWB_CNTW);
}

static void gfxhub_v2_1_westowe_wegs(stwuct amdgpu_device *adev)
{
	int i;

	WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW, adev->gmc.VM_W2_CNTW);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CNTW2, adev->gmc.VM_W2_CNTW2);
	WWEG32_SOC15(GC, 0, mmGCVM_DUMMY_PAGE_FAUWT_CNTW, adev->gmc.VM_DUMMY_PAGE_FAUWT_CNTW);
	WWEG32_SOC15(GC, 0, mmGCVM_DUMMY_PAGE_FAUWT_ADDW_WO32, adev->gmc.VM_DUMMY_PAGE_FAUWT_ADDW_WO32);
	WWEG32_SOC15(GC, 0, mmGCVM_DUMMY_PAGE_FAUWT_ADDW_HI32, adev->gmc.VM_DUMMY_PAGE_FAUWT_ADDW_HI32);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_CNTW, adev->gmc.VM_W2_PWOTECTION_FAUWT_CNTW);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_CNTW2, adev->gmc.VM_W2_PWOTECTION_FAUWT_CNTW2);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_MM_CNTW3, adev->gmc.VM_W2_PWOTECTION_FAUWT_MM_CNTW3);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_MM_CNTW4, adev->gmc.VM_W2_PWOTECTION_FAUWT_MM_CNTW4);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_ADDW_WO32, adev->gmc.VM_W2_PWOTECTION_FAUWT_ADDW_WO32);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_PWOTECTION_FAUWT_ADDW_HI32, adev->gmc.VM_W2_PWOTECTION_FAUWT_ADDW_HI32);
	WWEG32_SOC15(GC, 0, mmGCVM_DEBUG, adev->gmc.VM_DEBUG);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_MM_GWOUP_WT_CWASSES, adev->gmc.VM_W2_MM_GWOUP_WT_CWASSES);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_BANK_SEWECT_WESEWVED_CID, adev->gmc.VM_W2_BANK_SEWECT_WESEWVED_CID);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_BANK_SEWECT_WESEWVED_CID2, adev->gmc.VM_W2_BANK_SEWECT_WESEWVED_CID2);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_CACHE_PAWITY_CNTW, adev->gmc.VM_W2_CACHE_PAWITY_CNTW);
	WWEG32_SOC15(GC, 0, mmGCVM_W2_IH_WOG_CNTW, adev->gmc.VM_W2_IH_WOG_CNTW);

	fow (i = 0; i <= 15; i++) {
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_CNTW, i, adev->gmc.VM_CONTEXT_CNTW[i]);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32, i * 2, adev->gmc.VM_CONTEXT_PAGE_TABWE_BASE_ADDW_WO32[i]);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32, i * 2, adev->gmc.VM_CONTEXT_PAGE_TABWE_BASE_ADDW_HI32[i]);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32, i * 2, adev->gmc.VM_CONTEXT_PAGE_TABWE_STAWT_ADDW_WO32[i]);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32, i * 2, adev->gmc.VM_CONTEXT_PAGE_TABWE_STAWT_ADDW_HI32[i]);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32, i * 2, adev->gmc.VM_CONTEXT_PAGE_TABWE_END_ADDW_WO32[i]);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32, i * 2, adev->gmc.VM_CONTEXT_PAGE_TABWE_END_ADDW_HI32[i]);
	}

	WWEG32_SOC15(GC, 0, mmGCMC_VM_FB_WOCATION_BASE, adev->gmc.vwam_stawt >> 24);
	WWEG32_SOC15(GC, 0, mmGCMC_VM_FB_WOCATION_TOP, adev->gmc.vwam_end >> 24);
	WWEG32_SOC15(GC, 0, mmGCMC_VM_MX_W1_TWB_CNTW, adev->gmc.MC_VM_MX_W1_TWB_CNTW);
}

static void gfxhub_v2_1_hawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB(0)];
	int i;
	uint32_t tmp;
	int time = 1000;

	gfxhub_v2_1_set_fauwt_enabwe_defauwt(adev, fawse);

	fow (i = 0; i <= 14; i++) {
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_WO32,
				    i * hub->ctx_addw_distance, ~0);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_HI32,
				    i * hub->ctx_addw_distance, ~0);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABWE_END_ADDW_WO32,
				    i * hub->ctx_addw_distance,
				    0);
		WWEG32_SOC15_OFFSET(GC, 0, mmGCVM_CONTEXT1_PAGE_TABWE_END_ADDW_HI32,
				    i * hub->ctx_addw_distance,
				    0);
	}
	tmp = WWEG32_SOC15(GC, 0, mmGWBM_STATUS2);
	whiwe ((tmp & (GWBM_STATUS2__EA_BUSY_MASK |
		      GWBM_STATUS2__EA_WINK_BUSY_MASK)) != 0 &&
	       time) {
		udeway(100);
		time--;
		tmp = WWEG32_SOC15(GC, 0, mmGWBM_STATUS2);
	}

	if (!time)
		DWM_WAWN("faiwed to wait fow GWBM(EA) idwe\n");
}

const stwuct amdgpu_gfxhub_funcs gfxhub_v2_1_funcs = {
	.get_fb_wocation = gfxhub_v2_1_get_fb_wocation,
	.get_mc_fb_offset = gfxhub_v2_1_get_mc_fb_offset,
	.setup_vm_pt_wegs = gfxhub_v2_1_setup_vm_pt_wegs,
	.gawt_enabwe = gfxhub_v2_1_gawt_enabwe,
	.gawt_disabwe = gfxhub_v2_1_gawt_disabwe,
	.set_fauwt_enabwe_defauwt = gfxhub_v2_1_set_fauwt_enabwe_defauwt,
	.init = gfxhub_v2_1_init,
	.get_xgmi_info = gfxhub_v2_1_get_xgmi_info,
	.utcw2_hawvest = gfxhub_v2_1_utcw2_hawvest,
	.mode2_save_wegs = gfxhub_v2_1_save_wegs,
	.mode2_westowe_wegs = gfxhub_v2_1_westowe_wegs,
	.hawt = gfxhub_v2_1_hawt,
};