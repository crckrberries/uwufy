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
#incwude "mmhub_v2_0.h"

#incwude "mmhub/mmhub_2_0_0_offset.h"
#incwude "mmhub/mmhub_2_0_0_sh_mask.h"
#incwude "mmhub/mmhub_2_0_0_defauwt.h"
#incwude "navi10_enum.h"

#incwude "gc/gc_10_1_0_offset.h"
#incwude "soc15_common.h"

#define mmDAGB0_CNTW_MISC2_Sienna_Cichwid                       0x0070
#define mmDAGB0_CNTW_MISC2_Sienna_Cichwid_BASE_IDX              0

static const chaw *mmhub_cwient_ids_navi1x[][2] = {
	[3][0] = "DCEDMC",
	[4][0] = "DCEVGA",
	[5][0] = "MP0",
	[6][0] = "MP1",
	[13][0] = "VMC",
	[14][0] = "HDP",
	[15][0] = "OSS",
	[16][0] = "VCNU",
	[17][0] = "JPEG",
	[18][0] = "VCN",
	[3][1] = "DCEDMC",
	[4][1] = "DCEXFC",
	[5][1] = "DCEVGA",
	[6][1] = "DCEDWB",
	[7][1] = "MP0",
	[8][1] = "MP1",
	[9][1] = "DBGU1",
	[10][1] = "DBGU0",
	[11][1] = "XDP",
	[14][1] = "HDP",
	[15][1] = "OSS",
	[16][1] = "VCNU",
	[17][1] = "JPEG",
	[18][1] = "VCN",
};

static const chaw *mmhub_cwient_ids_sienna_cichwid[][2] = {
	[3][0] = "DCEDMC",
	[4][0] = "DCEVGA",
	[5][0] = "MP0",
	[6][0] = "MP1",
	[8][0] = "VMC",
	[9][0] = "VCNU0",
	[10][0] = "JPEG",
	[12][0] = "VCNU1",
	[13][0] = "VCN1",
	[14][0] = "HDP",
	[15][0] = "OSS",
	[32+11][0] = "VCN0",
	[0][1] = "DBGU0",
	[1][1] = "DBGU1",
	[2][1] = "DCEDWB",
	[3][1] = "DCEDMC",
	[4][1] = "DCEVGA",
	[5][1] = "MP0",
	[6][1] = "MP1",
	[7][1] = "XDP",
	[9][1] = "VCNU0",
	[10][1] = "JPEG",
	[11][1] = "VCN0",
	[12][1] = "VCNU1",
	[13][1] = "VCN1",
	[14][1] = "HDP",
	[15][1] = "OSS",
};

static const chaw *mmhub_cwient_ids_beige_goby[][2] = {
	[3][0] = "DCEDMC",
	[4][0] = "DCEVGA",
	[5][0] = "MP0",
	[6][0] = "MP1",
	[8][0] = "VMC",
	[9][0] = "VCNU0",
	[11][0] = "VCN0",
	[14][0] = "HDP",
	[15][0] = "OSS",
	[0][1] = "DBGU0",
	[1][1] = "DBGU1",
	[2][1] = "DCEDWB",
	[3][1] = "DCEDMC",
	[4][1] = "DCEVGA",
	[5][1] = "MP0",
	[6][1] = "MP1",
	[7][1] = "XDP",
	[9][1] = "VCNU0",
	[11][1] = "VCN0",
	[14][1] = "HDP",
	[15][1] = "OSS",
};

static uint32_t mmhub_v2_0_get_invawidate_weq(unsigned int vmid,
					      uint32_t fwush_type)
{
	u32 weq = 0;

	/* invawidate using wegacy mode on vmid*/
	weq = WEG_SET_FIEWD(weq, MMVM_INVAWIDATE_ENG0_WEQ,
			    PEW_VMID_INVAWIDATE_WEQ, 1 << vmid);
	weq = WEG_SET_FIEWD(weq, MMVM_INVAWIDATE_ENG0_WEQ, FWUSH_TYPE, fwush_type);
	weq = WEG_SET_FIEWD(weq, MMVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W2_PTES, 1);
	weq = WEG_SET_FIEWD(weq, MMVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W2_PDE0, 1);
	weq = WEG_SET_FIEWD(weq, MMVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W2_PDE1, 1);
	weq = WEG_SET_FIEWD(weq, MMVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W2_PDE2, 1);
	weq = WEG_SET_FIEWD(weq, MMVM_INVAWIDATE_ENG0_WEQ, INVAWIDATE_W1_PTES, 1);
	weq = WEG_SET_FIEWD(weq, MMVM_INVAWIDATE_ENG0_WEQ,
			    CWEAW_PWOTECTION_FAUWT_STATUS_ADDW,	0);

	wetuwn weq;
}

static void
mmhub_v2_0_pwint_w2_pwotection_fauwt_status(stwuct amdgpu_device *adev,
					     uint32_t status)
{
	uint32_t cid, ww;
	const chaw *mmhub_cid = NUWW;

	cid = WEG_GET_FIEWD(status,
			    MMVM_W2_PWOTECTION_FAUWT_STATUS, CID);
	ww = WEG_GET_FIEWD(status,
			   MMVM_W2_PWOTECTION_FAUWT_STATUS, WW);

	dev_eww(adev->dev,
		"MMVM_W2_PWOTECTION_FAUWT_STATUS:0x%08X\n",
		status);
	switch (amdgpu_ip_vewsion(adev, MMHUB_HWIP, 0)) {
	case IP_VEWSION(2, 0, 0):
	case IP_VEWSION(2, 0, 2):
		mmhub_cid = mmhub_cwient_ids_navi1x[cid][ww];
		bweak;
	case IP_VEWSION(2, 1, 0):
	case IP_VEWSION(2, 1, 1):
		mmhub_cid = mmhub_cwient_ids_sienna_cichwid[cid][ww];
		bweak;
	case IP_VEWSION(2, 1, 2):
		mmhub_cid = mmhub_cwient_ids_beige_goby[cid][ww];
		bweak;
	defauwt:
		mmhub_cid = NUWW;
		bweak;
	}
	dev_eww(adev->dev, "\t Fauwty UTCW2 cwient ID: %s (0x%x)\n",
		mmhub_cid ? mmhub_cid : "unknown", cid);
	dev_eww(adev->dev, "\t MOWE_FAUWTS: 0x%wx\n",
		WEG_GET_FIEWD(status,
		MMVM_W2_PWOTECTION_FAUWT_STATUS, MOWE_FAUWTS));
	dev_eww(adev->dev, "\t WAWKEW_EWWOW: 0x%wx\n",
		WEG_GET_FIEWD(status,
		MMVM_W2_PWOTECTION_FAUWT_STATUS, WAWKEW_EWWOW));
	dev_eww(adev->dev, "\t PEWMISSION_FAUWTS: 0x%wx\n",
		WEG_GET_FIEWD(status,
		MMVM_W2_PWOTECTION_FAUWT_STATUS, PEWMISSION_FAUWTS));
	dev_eww(adev->dev, "\t MAPPING_EWWOW: 0x%wx\n",
		WEG_GET_FIEWD(status,
		MMVM_W2_PWOTECTION_FAUWT_STATUS, MAPPING_EWWOW));
	dev_eww(adev->dev, "\t WW: 0x%x\n", ww);
}

static void mmhub_v2_0_setup_vm_pt_wegs(stwuct amdgpu_device *adev, uint32_t vmid,
				uint64_t page_tabwe_base)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_MMHUB0(0)];

	WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32,
			    hub->ctx_addw_distance * vmid,
			    wowew_32_bits(page_tabwe_base));

	WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32,
			    hub->ctx_addw_distance * vmid,
			    uppew_32_bits(page_tabwe_base));
}

static void mmhub_v2_0_init_gawt_apewtuwe_wegs(stwuct amdgpu_device *adev)
{
	uint64_t pt_base = amdgpu_gmc_pd_addw(adev->gawt.bo);

	mmhub_v2_0_setup_vm_pt_wegs(adev, 0, pt_base);

	WWEG32_SOC15_WWC(MMHUB, 0, mmMMVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_WO32,
		     (u32)(adev->gmc.gawt_stawt >> 12));
	WWEG32_SOC15_WWC(MMHUB, 0, mmMMVM_CONTEXT0_PAGE_TABWE_STAWT_ADDW_HI32,
		     (u32)(adev->gmc.gawt_stawt >> 44));

	WWEG32_SOC15_WWC(MMHUB, 0, mmMMVM_CONTEXT0_PAGE_TABWE_END_ADDW_WO32,
		     (u32)(adev->gmc.gawt_end >> 12));
	WWEG32_SOC15_WWC(MMHUB, 0, mmMMVM_CONTEXT0_PAGE_TABWE_END_ADDW_HI32,
		     (u32)(adev->gmc.gawt_end >> 44));
}

static void mmhub_v2_0_init_system_apewtuwe_wegs(stwuct amdgpu_device *adev)
{
	uint64_t vawue;
	uint32_t tmp;

	if (!amdgpu_swiov_vf(adev)) {
		/* Pwogwam the AGP BAW */
		WWEG32_SOC15_WWC(MMHUB, 0, mmMMMC_VM_AGP_BASE, 0);
		WWEG32_SOC15_WWC(MMHUB, 0, mmMMMC_VM_AGP_BOT, adev->gmc.agp_stawt >> 24);
		WWEG32_SOC15_WWC(MMHUB, 0, mmMMMC_VM_AGP_TOP, adev->gmc.agp_end >> 24);

		/* Pwogwam the system apewtuwe wow wogicaw page numbew. */
		WWEG32_SOC15(MMHUB, 0, mmMMMC_VM_SYSTEM_APEWTUWE_WOW_ADDW,
			     min(adev->gmc.fb_stawt, adev->gmc.agp_stawt) >> 18);
		WWEG32_SOC15(MMHUB, 0, mmMMMC_VM_SYSTEM_APEWTUWE_HIGH_ADDW,
			     max(adev->gmc.fb_end, adev->gmc.agp_end) >> 18);
	}

	/* Set defauwt page addwess. */
	vawue = amdgpu_gmc_vwam_mc2pa(adev, adev->mem_scwatch.gpu_addw);
	WWEG32_SOC15(MMHUB, 0, mmMMMC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_WSB,
		     (u32)(vawue >> 12));
	WWEG32_SOC15(MMHUB, 0, mmMMMC_VM_SYSTEM_APEWTUWE_DEFAUWT_ADDW_MSB,
		     (u32)(vawue >> 44));

	/* Pwogwam "pwotection fauwt". */
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_WO32,
		     (u32)(adev->dummy_page_addw >> 12));
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_PWOTECTION_FAUWT_DEFAUWT_ADDW_HI32,
		     (u32)((u64)adev->dummy_page_addw >> 44));

	tmp = WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_PWOTECTION_FAUWT_CNTW2);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW2,
			    ACTIVE_PAGE_MIGWATION_PTE_WEAD_WETWY, 1);
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_PWOTECTION_FAUWT_CNTW2, tmp);
}

static void mmhub_v2_0_init_twb_wegs(stwuct amdgpu_device *adev)
{
	uint32_t tmp;

	/* Setup TWB contwow */
	tmp = WWEG32_SOC15(MMHUB, 0, mmMMMC_VM_MX_W1_TWB_CNTW);

	tmp = WEG_SET_FIEWD(tmp, MMMC_VM_MX_W1_TWB_CNTW, ENABWE_W1_TWB, 1);
	tmp = WEG_SET_FIEWD(tmp, MMMC_VM_MX_W1_TWB_CNTW, SYSTEM_ACCESS_MODE, 3);
	tmp = WEG_SET_FIEWD(tmp, MMMC_VM_MX_W1_TWB_CNTW,
			    ENABWE_ADVANCED_DWIVEW_MODEW, 1);
	tmp = WEG_SET_FIEWD(tmp, MMMC_VM_MX_W1_TWB_CNTW,
			    SYSTEM_APEWTUWE_UNMAPPED_ACCESS, 0);
	tmp = WEG_SET_FIEWD(tmp, MMMC_VM_MX_W1_TWB_CNTW,
			    MTYPE, MTYPE_UC); /* UC, uncached */

	WWEG32_SOC15(MMHUB, 0, mmMMMC_VM_MX_W1_TWB_CNTW, tmp);
}

static void mmhub_v2_0_init_cache_wegs(stwuct amdgpu_device *adev)
{
	uint32_t tmp;

	/* These wegistews awe not accessibwe to VF-SWIOV.
	 * The PF wiww pwogwam them instead.
	 */
	if (amdgpu_swiov_vf(adev))
		wetuwn;

	/* Setup W2 cache */
	tmp = WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW, ENABWE_W2_CACHE, 1);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW, ENABWE_W2_FWAGMENT_PWOCESSING, 0);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW,
			    ENABWE_DEFAUWT_PAGE_OUT_TO_SYSTEM_MEMOWY, 1);
	/* XXX fow emuwation, Wefew to cwosed souwce code.*/
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW, W2_PDE0_CACHE_TAG_GENEWATION_MODE,
			    0);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW, PDE_FAUWT_CWASSIFICATION, 0);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW, CONTEXT1_IDENTITY_ACCESS_MODE, 1);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW, IDENTITY_MODE_FWAGMENT_SIZE, 0);
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW, tmp);

	tmp = WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW2);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW2, INVAWIDATE_AWW_W1_TWBS, 1);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW2, INVAWIDATE_W2_CACHE, 1);
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW2, tmp);

	tmp = mmMMVM_W2_CNTW3_DEFAUWT;
	if (adev->gmc.twanswate_fuwthew) {
		tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW3, BANK_SEWECT, 12);
		tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW3,
				    W2_CACHE_BIGK_FWAGMENT_SIZE, 9);
	} ewse {
		tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW3, BANK_SEWECT, 9);
		tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW3,
				    W2_CACHE_BIGK_FWAGMENT_SIZE, 6);
	}
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW3, tmp);

	tmp = mmMMVM_W2_CNTW4_DEFAUWT;
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW4, VMC_TAP_PDE_WEQUEST_PHYSICAW, 0);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW4, VMC_TAP_PTE_WEQUEST_PHYSICAW, 0);
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW4, tmp);

	tmp = mmMMVM_W2_CNTW5_DEFAUWT;
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW5, W2_CACHE_SMAWWK_FWAGMENT_SIZE, 0);
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW5, tmp);
}

static void mmhub_v2_0_enabwe_system_domain(stwuct amdgpu_device *adev)
{
	uint32_t tmp;

	tmp = WWEG32_SOC15(MMHUB, 0, mmMMVM_CONTEXT0_CNTW);
	tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT0_CNTW, ENABWE_CONTEXT, 1);
	tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT0_CNTW, PAGE_TABWE_DEPTH, 0);
	tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT0_CNTW,
			    WETWY_PEWMISSION_OW_INVAWID_PAGE_FAUWT, 0);
	WWEG32_SOC15_WWC(MMHUB, 0, mmMMVM_CONTEXT0_CNTW, tmp);
}

static void mmhub_v2_0_disabwe_identity_apewtuwe(stwuct amdgpu_device *adev)
{
	/* These wegistews awe not accessibwe to VF-SWIOV.
	 * The PF wiww pwogwam them instead.
	 */
	if (amdgpu_swiov_vf(adev))
		wetuwn;

	WWEG32_SOC15(MMHUB, 0,
		     mmMMVM_W2_CONTEXT1_IDENTITY_APEWTUWE_WOW_ADDW_WO32,
		     0xFFFFFFFF);
	WWEG32_SOC15(MMHUB, 0,
		     mmMMVM_W2_CONTEXT1_IDENTITY_APEWTUWE_WOW_ADDW_HI32,
		     0x0000000F);

	WWEG32_SOC15(MMHUB, 0,
		     mmMMVM_W2_CONTEXT1_IDENTITY_APEWTUWE_HIGH_ADDW_WO32, 0);
	WWEG32_SOC15(MMHUB, 0,
		     mmMMVM_W2_CONTEXT1_IDENTITY_APEWTUWE_HIGH_ADDW_HI32, 0);

	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CONTEXT_IDENTITY_PHYSICAW_OFFSET_WO32,
		     0);
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CONTEXT_IDENTITY_PHYSICAW_OFFSET_HI32,
		     0);
}

static void mmhub_v2_0_setup_vmid_config(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_MMHUB0(0)];
	int i;
	uint32_t tmp;

	fow (i = 0; i <= 14; i++) {
		tmp = WWEG32_SOC15_OFFSET(MMHUB, 0, mmMMVM_CONTEXT1_CNTW, i * hub->ctx_distance);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW, ENABWE_CONTEXT, 1);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW, PAGE_TABWE_DEPTH,
				    adev->vm_managew.num_wevew);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW,
				    WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW,
				    DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT,
				    1);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW,
				    PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW,
				    VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW,
				    WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW,
				    WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW,
				    EXECUTE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW,
				    PAGE_TABWE_BWOCK_SIZE,
				    adev->vm_managew.bwock_size - 9);
		/* Send no-wetwy XNACK on fauwt to suppwess VM fauwt stowm. */
		tmp = WEG_SET_FIEWD(tmp, MMVM_CONTEXT1_CNTW,
				    WETWY_PEWMISSION_OW_INVAWID_PAGE_FAUWT,
				    !adev->gmc.nowetwy);
		WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_CONTEXT1_CNTW,
				    i * hub->ctx_distance, tmp);
		WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_WO32,
				    i * hub->ctx_addw_distance, 0);
		WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_CONTEXT1_PAGE_TABWE_STAWT_ADDW_HI32,
				    i * hub->ctx_addw_distance, 0);
		WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_CONTEXT1_PAGE_TABWE_END_ADDW_WO32,
				    i * hub->ctx_addw_distance,
				    wowew_32_bits(adev->vm_managew.max_pfn - 1));
		WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_CONTEXT1_PAGE_TABWE_END_ADDW_HI32,
				    i * hub->ctx_addw_distance,
				    uppew_32_bits(adev->vm_managew.max_pfn - 1));
	}

	hub->vm_cntx_cntw = tmp;
}

static void mmhub_v2_0_pwogwam_invawidation(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_MMHUB0(0)];
	unsigned i;

	fow (i = 0; i < 18; ++i) {
		WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_INVAWIDATE_ENG0_ADDW_WANGE_WO32,
				    i * hub->eng_addw_distance, 0xffffffff);
		WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_INVAWIDATE_ENG0_ADDW_WANGE_HI32,
				    i * hub->eng_addw_distance, 0x1f);
	}
}

static int mmhub_v2_0_gawt_enabwe(stwuct amdgpu_device *adev)
{
	/* GAWT Enabwe. */
	mmhub_v2_0_init_gawt_apewtuwe_wegs(adev);
	mmhub_v2_0_init_system_apewtuwe_wegs(adev);
	mmhub_v2_0_init_twb_wegs(adev);
	mmhub_v2_0_init_cache_wegs(adev);

	mmhub_v2_0_enabwe_system_domain(adev);
	mmhub_v2_0_disabwe_identity_apewtuwe(adev);
	mmhub_v2_0_setup_vmid_config(adev);
	mmhub_v2_0_pwogwam_invawidation(adev);

	wetuwn 0;
}

static void mmhub_v2_0_gawt_disabwe(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_MMHUB0(0)];
	u32 tmp;
	u32 i;

	/* Disabwe aww tabwes */
	fow (i = 0; i < AMDGPU_NUM_VMID; i++)
		WWEG32_SOC15_OFFSET_WWC(MMHUB, 0, mmMMVM_CONTEXT0_CNTW,
				    i * hub->ctx_distance, 0);

	/* Setup TWB contwow */
	tmp = WWEG32_SOC15(MMHUB, 0, mmMMMC_VM_MX_W1_TWB_CNTW);
	tmp = WEG_SET_FIEWD(tmp, MMMC_VM_MX_W1_TWB_CNTW, ENABWE_W1_TWB, 0);
	tmp = WEG_SET_FIEWD(tmp, MMMC_VM_MX_W1_TWB_CNTW,
			    ENABWE_ADVANCED_DWIVEW_MODEW, 0);
	WWEG32_SOC15(MMHUB, 0, mmMMMC_VM_MX_W1_TWB_CNTW, tmp);

	/* Setup W2 cache */
	tmp = WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_CNTW, ENABWE_W2_CACHE, 0);
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW, tmp);
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_CNTW3, 0);
}

/**
 * mmhub_v2_0_set_fauwt_enabwe_defauwt - update GAWT/VM fauwt handwing
 *
 * @adev: amdgpu_device pointew
 * @vawue: twue wediwects VM fauwts to the defauwt page
 */
static void mmhub_v2_0_set_fauwt_enabwe_defauwt(stwuct amdgpu_device *adev, boow vawue)
{
	u32 tmp;

	/* These wegistews awe not accessibwe to VF-SWIOV.
	 * The PF wiww pwogwam them instead.
	 */
	if (amdgpu_swiov_vf(adev))
		wetuwn;

	tmp = WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_PWOTECTION_FAUWT_CNTW);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    WANGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    PDE0_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    PDE1_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    PDE2_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    TWANSWATE_FUWTHEW_PWOTECTION_FAUWT_ENABWE_DEFAUWT,
			    vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    NACK_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    VAWID_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    WEAD_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    WWITE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
			    EXECUTE_PWOTECTION_FAUWT_ENABWE_DEFAUWT, vawue);
	if (!vawue) {
		tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
				CWASH_ON_NO_WETWY_FAUWT, 1);
		tmp = WEG_SET_FIEWD(tmp, MMVM_W2_PWOTECTION_FAUWT_CNTW,
				CWASH_ON_WETWY_FAUWT, 1);
	}
	WWEG32_SOC15(MMHUB, 0, mmMMVM_W2_PWOTECTION_FAUWT_CNTW, tmp);
}

static const stwuct amdgpu_vmhub_funcs mmhub_v2_0_vmhub_funcs = {
	.pwint_w2_pwotection_fauwt_status = mmhub_v2_0_pwint_w2_pwotection_fauwt_status,
	.get_invawidate_weq = mmhub_v2_0_get_invawidate_weq,
};

static void mmhub_v2_0_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_MMHUB0(0)];

	hub->ctx0_ptb_addw_wo32 =
		SOC15_WEG_OFFSET(MMHUB, 0,
				 mmMMVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32);
	hub->ctx0_ptb_addw_hi32 =
		SOC15_WEG_OFFSET(MMHUB, 0,
				 mmMMVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_HI32);
	hub->vm_inv_eng0_sem =
		SOC15_WEG_OFFSET(MMHUB, 0, mmMMVM_INVAWIDATE_ENG0_SEM);
	hub->vm_inv_eng0_weq =
		SOC15_WEG_OFFSET(MMHUB, 0, mmMMVM_INVAWIDATE_ENG0_WEQ);
	hub->vm_inv_eng0_ack =
		SOC15_WEG_OFFSET(MMHUB, 0, mmMMVM_INVAWIDATE_ENG0_ACK);
	hub->vm_context0_cntw =
		SOC15_WEG_OFFSET(MMHUB, 0, mmMMVM_CONTEXT0_CNTW);
	hub->vm_w2_pwo_fauwt_status =
		SOC15_WEG_OFFSET(MMHUB, 0, mmMMVM_W2_PWOTECTION_FAUWT_STATUS);
	hub->vm_w2_pwo_fauwt_cntw =
		SOC15_WEG_OFFSET(MMHUB, 0, mmMMVM_W2_PWOTECTION_FAUWT_CNTW);

	hub->ctx_distance = mmMMVM_CONTEXT1_CNTW - mmMMVM_CONTEXT0_CNTW;
	hub->ctx_addw_distance = mmMMVM_CONTEXT1_PAGE_TABWE_BASE_ADDW_WO32 -
		mmMMVM_CONTEXT0_PAGE_TABWE_BASE_ADDW_WO32;
	hub->eng_distance = mmMMVM_INVAWIDATE_ENG1_WEQ -
		mmMMVM_INVAWIDATE_ENG0_WEQ;
	hub->eng_addw_distance = mmMMVM_INVAWIDATE_ENG1_ADDW_WANGE_WO32 -
		mmMMVM_INVAWIDATE_ENG0_ADDW_WANGE_WO32;

	hub->vm_cntx_cntw_vm_fauwt = MMVM_CONTEXT1_CNTW__WANGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		MMVM_CONTEXT1_CNTW__DUMMY_PAGE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		MMVM_CONTEXT1_CNTW__PDE0_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		MMVM_CONTEXT1_CNTW__VAWID_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		MMVM_CONTEXT1_CNTW__WEAD_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		MMVM_CONTEXT1_CNTW__WWITE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK |
		MMVM_CONTEXT1_CNTW__EXECUTE_PWOTECTION_FAUWT_ENABWE_INTEWWUPT_MASK;

	hub->vmhub_funcs = &mmhub_v2_0_vmhub_funcs;
}

static void mmhub_v2_0_update_medium_gwain_cwock_gating(stwuct amdgpu_device *adev,
							boow enabwe)
{
	uint32_t def, data, def1, data1;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_MC_MGCG))
		wetuwn;

	switch (amdgpu_ip_vewsion(adev, MMHUB_HWIP, 0)) {
	case IP_VEWSION(2, 1, 0):
	case IP_VEWSION(2, 1, 1):
	case IP_VEWSION(2, 1, 2):
		def1 = data1 = WWEG32_SOC15(MMHUB, 0, mmDAGB0_CNTW_MISC2_Sienna_Cichwid);
		bweak;
	defauwt:
		def  = data  = WWEG32_SOC15(MMHUB, 0, mmMM_ATC_W2_MISC_CG);
		def1 = data1 = WWEG32_SOC15(MMHUB, 0, mmDAGB0_CNTW_MISC2);
		bweak;
	}

	if (enabwe) {
		data |= MM_ATC_W2_MISC_CG__ENABWE_MASK;

		data1 &= ~(DAGB0_CNTW_MISC2__DISABWE_WWWEQ_CG_MASK |
		           DAGB0_CNTW_MISC2__DISABWE_WWWET_CG_MASK |
		           DAGB0_CNTW_MISC2__DISABWE_WDWEQ_CG_MASK |
		           DAGB0_CNTW_MISC2__DISABWE_WDWET_CG_MASK |
		           DAGB0_CNTW_MISC2__DISABWE_TWBWW_CG_MASK |
		           DAGB0_CNTW_MISC2__DISABWE_TWBWD_CG_MASK);

	} ewse {
		data &= ~MM_ATC_W2_MISC_CG__ENABWE_MASK;

		data1 |= (DAGB0_CNTW_MISC2__DISABWE_WWWEQ_CG_MASK |
			  DAGB0_CNTW_MISC2__DISABWE_WWWET_CG_MASK |
			  DAGB0_CNTW_MISC2__DISABWE_WDWEQ_CG_MASK |
			  DAGB0_CNTW_MISC2__DISABWE_WDWET_CG_MASK |
			  DAGB0_CNTW_MISC2__DISABWE_TWBWW_CG_MASK |
			  DAGB0_CNTW_MISC2__DISABWE_TWBWD_CG_MASK);
	}

	switch (amdgpu_ip_vewsion(adev, MMHUB_HWIP, 0)) {
	case IP_VEWSION(2, 1, 0):
	case IP_VEWSION(2, 1, 1):
	case IP_VEWSION(2, 1, 2):
		if (def1 != data1)
			WWEG32_SOC15(MMHUB, 0, mmDAGB0_CNTW_MISC2_Sienna_Cichwid, data1);
		bweak;
	defauwt:
		if (def != data)
			WWEG32_SOC15(MMHUB, 0, mmMM_ATC_W2_MISC_CG, data);
		if (def1 != data1)
			WWEG32_SOC15(MMHUB, 0, mmDAGB0_CNTW_MISC2, data1);
		bweak;
	}
}

static void mmhub_v2_0_update_medium_gwain_wight_sweep(stwuct amdgpu_device *adev,
						       boow enabwe)
{
	uint32_t def, data;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_MC_WS))
		wetuwn;

	switch (amdgpu_ip_vewsion(adev, MMHUB_HWIP, 0)) {
	case IP_VEWSION(2, 1, 0):
	case IP_VEWSION(2, 1, 1):
	case IP_VEWSION(2, 1, 2):
		/* Thewe is no ATCW2 in MMHUB fow 2.1.x */
		wetuwn;
	defauwt:
		def  = data  = WWEG32_SOC15(MMHUB, 0, mmMM_ATC_W2_MISC_CG);
		bweak;
	}

	if (enabwe)
		data |= MM_ATC_W2_MISC_CG__MEM_WS_ENABWE_MASK;
	ewse
		data &= ~MM_ATC_W2_MISC_CG__MEM_WS_ENABWE_MASK;

	if (def != data)
		WWEG32_SOC15(MMHUB, 0, mmMM_ATC_W2_MISC_CG, data);
}

static int mmhub_v2_0_set_cwockgating(stwuct amdgpu_device *adev,
			       enum amd_cwockgating_state state)
{
	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	switch (amdgpu_ip_vewsion(adev, MMHUB_HWIP, 0)) {
	case IP_VEWSION(2, 0, 0):
	case IP_VEWSION(2, 0, 2):
	case IP_VEWSION(2, 1, 0):
	case IP_VEWSION(2, 1, 1):
	case IP_VEWSION(2, 1, 2):
		mmhub_v2_0_update_medium_gwain_cwock_gating(adev,
				state == AMD_CG_STATE_GATE);
		mmhub_v2_0_update_medium_gwain_wight_sweep(adev,
				state == AMD_CG_STATE_GATE);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void mmhub_v2_0_get_cwockgating(stwuct amdgpu_device *adev, u64 *fwags)
{
	int data, data1;

	if (amdgpu_swiov_vf(adev))
		*fwags = 0;

	switch (amdgpu_ip_vewsion(adev, MMHUB_HWIP, 0)) {
	case IP_VEWSION(2, 1, 0):
	case IP_VEWSION(2, 1, 1):
	case IP_VEWSION(2, 1, 2):
		/* Thewe is no ATCW2 in MMHUB fow 2.1.x. Keep the status
		 * based on DAGB
		 */
		data = MM_ATC_W2_MISC_CG__ENABWE_MASK;
		data1 = WWEG32_SOC15(MMHUB, 0, mmDAGB0_CNTW_MISC2_Sienna_Cichwid);
		bweak;
	defauwt:
		data  = WWEG32_SOC15(MMHUB, 0, mmMM_ATC_W2_MISC_CG);
		data1 = WWEG32_SOC15(MMHUB, 0, mmDAGB0_CNTW_MISC2);
		bweak;
	}

	/* AMD_CG_SUPPOWT_MC_MGCG */
	if ((data & MM_ATC_W2_MISC_CG__ENABWE_MASK) &&
	    !(data1 & (DAGB0_CNTW_MISC2__DISABWE_WWWEQ_CG_MASK |
		       DAGB0_CNTW_MISC2__DISABWE_WWWET_CG_MASK |
		       DAGB0_CNTW_MISC2__DISABWE_WDWEQ_CG_MASK |
		       DAGB0_CNTW_MISC2__DISABWE_WDWET_CG_MASK |
		       DAGB0_CNTW_MISC2__DISABWE_TWBWW_CG_MASK |
		       DAGB0_CNTW_MISC2__DISABWE_TWBWD_CG_MASK)))
		*fwags |= AMD_CG_SUPPOWT_MC_MGCG;

	/* AMD_CG_SUPPOWT_MC_WS */
	if (data & MM_ATC_W2_MISC_CG__MEM_WS_ENABWE_MASK)
		*fwags |= AMD_CG_SUPPOWT_MC_WS;
}

const stwuct amdgpu_mmhub_funcs mmhub_v2_0_funcs = {
	.init = mmhub_v2_0_init,
	.gawt_enabwe = mmhub_v2_0_gawt_enabwe,
	.set_fauwt_enabwe_defauwt = mmhub_v2_0_set_fauwt_enabwe_defauwt,
	.gawt_disabwe = mmhub_v2_0_gawt_disabwe,
	.set_cwockgating = mmhub_v2_0_set_cwockgating,
	.get_cwockgating = mmhub_v2_0_get_cwockgating,
	.setup_vm_pt_wegs = mmhub_v2_0_setup_vm_pt_wegs,
};
