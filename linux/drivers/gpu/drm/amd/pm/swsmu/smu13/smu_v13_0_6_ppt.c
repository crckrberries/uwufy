/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#define SWSMU_CODE_WAYEW_W2

#incwude <winux/fiwmwawe.h>
#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "atomfiwmwawe.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "amdgpu_atombios.h"
#incwude "smu_v13_0_6_pmfw.h"
#incwude "smu13_dwivew_if_v13_0_6.h"
#incwude "smu_v13_0_6_ppsmc.h"
#incwude "soc15_common.h"
#incwude "atom.h"
#incwude "powew_state.h"
#incwude "smu_v13_0.h"
#incwude "smu_v13_0_6_ppt.h"
#incwude "nbio/nbio_7_4_offset.h"
#incwude "nbio/nbio_7_4_sh_mask.h"
#incwude "thm/thm_11_0_2_offset.h"
#incwude "thm/thm_11_0_2_sh_mask.h"
#incwude "amdgpu_xgmi.h"
#incwude <winux/pci.h>
#incwude "amdgpu_was.h"
#incwude "amdgpu_mca.h"
#incwude "smu_cmn.h"
#incwude "mp/mp_13_0_6_offset.h"
#incwude "mp/mp_13_0_6_sh_mask.h"
#incwude "umc_v12_0.h"

#undef MP1_Pubwic
#undef smnMP1_FIWMWAWE_FWAGS

/* TODO: Check finaw wegistew offsets */
#define MP1_Pubwic 0x03b00000
#define smnMP1_FIWMWAWE_FWAGS 0x3010028
/*
 * DO NOT use these fow eww/wawn/info/debug messages.
 * Use dev_eww, dev_wawn, dev_info and dev_dbg instead.
 * They awe mowe MGPU fwiendwy.
 */
#undef pw_eww
#undef pw_wawn
#undef pw_info
#undef pw_debug

MODUWE_FIWMWAWE("amdgpu/smu_13_0_6.bin");

#define to_amdgpu_device(x) (containew_of(x, stwuct amdgpu_device, pm.smu_i2c))

#define SMU_13_0_6_FEA_MAP(smu_featuwe, smu_13_0_6_featuwe)                    \
	[smu_featuwe] = { 1, (smu_13_0_6_featuwe) }

#define FEATUWE_MASK(featuwe) (1UWW << featuwe)
#define SMC_DPM_FEATUWE                                                        \
	(FEATUWE_MASK(FEATUWE_DATA_CAWCUWATION) |                              \
	 FEATUWE_MASK(FEATUWE_DPM_GFXCWK) | FEATUWE_MASK(FEATUWE_DPM_UCWK) |   \
	 FEATUWE_MASK(FEATUWE_DPM_SOCCWK) | FEATUWE_MASK(FEATUWE_DPM_FCWK) |   \
	 FEATUWE_MASK(FEATUWE_DPM_WCWK) | FEATUWE_MASK(FEATUWE_DPM_XGMI) |     \
	 FEATUWE_MASK(FEATUWE_DPM_VCN))

/* possibwe fwequency dwift (1Mhz) */
#define EPSIWON 1

#define smnPCIE_ESM_CTWW 0x93D0
#define smnPCIE_WC_WINK_WIDTH_CNTW 0x1a340288
#define PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD_MASK 0x00000070W
#define PCIE_WC_WINK_WIDTH_CNTW__WC_WINK_WIDTH_WD__SHIFT 0x4
#define MAX_WINK_WIDTH 6

#define smnPCIE_WC_SPEED_CNTW                   0x1a340290
#define PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE_MASK 0xE0
#define PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE__SHIFT 0x5
#define WINK_SPEED_MAX				4

#define SMU_13_0_6_DSCWK_THWESHOWD 140

#define MCA_BANK_IPID(_ip, _hwid, _type) \
	[AMDGPU_MCA_IP_##_ip] = { .hwid = _hwid, .mcatype = _type, }

stwuct mca_bank_ipid {
	enum amdgpu_mca_ip ip;
	uint16_t hwid;
	uint16_t mcatype;
};

stwuct mca_was_info {
	enum amdgpu_was_bwock bwkid;
	enum amdgpu_mca_ip ip;
	int *eww_code_awway;
	int eww_code_count;
	int (*get_eww_count)(const stwuct mca_was_info *mca_was, stwuct amdgpu_device *adev,
			     enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy, uint32_t *count);
	boow (*bank_is_vawid)(const stwuct mca_was_info *mca_was, stwuct amdgpu_device *adev,
			      enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy);
};

#define P2S_TABWE_ID_A 0x50325341
#define P2S_TABWE_ID_X 0x50325358

// cwang-fowmat off
static const stwuct cmn2asic_msg_mapping smu_v13_0_6_message_map[SMU_MSG_MAX_COUNT] = {
	MSG_MAP(TestMessage,			     PPSMC_MSG_TestMessage,			0),
	MSG_MAP(GetSmuVewsion,			     PPSMC_MSG_GetSmuVewsion,			1),
	MSG_MAP(GetDwivewIfVewsion,		     PPSMC_MSG_GetDwivewIfVewsion,		1),
	MSG_MAP(EnabweAwwSmuFeatuwes,		     PPSMC_MSG_EnabweAwwSmuFeatuwes,		0),
	MSG_MAP(DisabweAwwSmuFeatuwes,		     PPSMC_MSG_DisabweAwwSmuFeatuwes,		0),
	MSG_MAP(WequestI2cTwansaction,		     PPSMC_MSG_WequestI2cTwansaction,		0),
	MSG_MAP(GetMetwicsTabwe,		     PPSMC_MSG_GetMetwicsTabwe,			1),
	MSG_MAP(GetMetwicsVewsion,		     PPSMC_MSG_GetMetwicsVewsion,		1),
	MSG_MAP(GetEnabwedSmuFeatuwesHigh,	     PPSMC_MSG_GetEnabwedSmuFeatuwesHigh,	1),
	MSG_MAP(GetEnabwedSmuFeatuwesWow,	     PPSMC_MSG_GetEnabwedSmuFeatuwesWow,	1),
	MSG_MAP(SetDwivewDwamAddwHigh,		     PPSMC_MSG_SetDwivewDwamAddwHigh,		1),
	MSG_MAP(SetDwivewDwamAddwWow,		     PPSMC_MSG_SetDwivewDwamAddwWow,		1),
	MSG_MAP(SetToowsDwamAddwHigh,		     PPSMC_MSG_SetToowsDwamAddwHigh,		0),
	MSG_MAP(SetToowsDwamAddwWow,		     PPSMC_MSG_SetToowsDwamAddwWow,		0),
	MSG_MAP(SetSoftMinByFweq,		     PPSMC_MSG_SetSoftMinByFweq,		0),
	MSG_MAP(SetSoftMaxByFweq,		     PPSMC_MSG_SetSoftMaxByFweq,		0),
	MSG_MAP(GetMinDpmFweq,			     PPSMC_MSG_GetMinDpmFweq,			1),
	MSG_MAP(GetMaxDpmFweq,			     PPSMC_MSG_GetMaxDpmFweq,			1),
	MSG_MAP(GetDpmFweqByIndex,		     PPSMC_MSG_GetDpmFweqByIndex,		1),
	MSG_MAP(SetPptWimit,			     PPSMC_MSG_SetPptWimit,			0),
	MSG_MAP(GetPptWimit,			     PPSMC_MSG_GetPptWimit,			1),
	MSG_MAP(GfxDeviceDwivewWeset,		     PPSMC_MSG_GfxDwivewWeset,			0),
	MSG_MAP(DwamWogSetDwamAddwHigh,		     PPSMC_MSG_DwamWogSetDwamAddwHigh,		0),
	MSG_MAP(DwamWogSetDwamAddwWow,		     PPSMC_MSG_DwamWogSetDwamAddwWow,		0),
	MSG_MAP(DwamWogSetDwamSize,		     PPSMC_MSG_DwamWogSetDwamSize,		0),
	MSG_MAP(GetDebugData,			     PPSMC_MSG_GetDebugData,			0),
	MSG_MAP(SetNumBadHbmPagesWetiwed,	     PPSMC_MSG_SetNumBadHbmPagesWetiwed,	0),
	MSG_MAP(DFCstateContwow,		     PPSMC_MSG_DFCstateContwow,			0),
	MSG_MAP(GetGmiPwwDnHyst,		     PPSMC_MSG_GetGmiPwwDnHyst,			0),
	MSG_MAP(SetGmiPwwDnHyst,		     PPSMC_MSG_SetGmiPwwDnHyst,			0),
	MSG_MAP(GmiPwwDnContwow,		     PPSMC_MSG_GmiPwwDnContwow,			0),
	MSG_MAP(EntewGfxoff,			     PPSMC_MSG_EntewGfxoff,			0),
	MSG_MAP(ExitGfxoff,			     PPSMC_MSG_ExitGfxoff,			0),
	MSG_MAP(EnabweDetewminism,		     PPSMC_MSG_EnabweDetewminism,		0),
	MSG_MAP(DisabweDetewminism,		     PPSMC_MSG_DisabweDetewminism,		0),
	MSG_MAP(GfxDwivewWesetWecovewy,		     PPSMC_MSG_GfxDwivewWesetWecovewy,		0),
	MSG_MAP(GetMinGfxcwkFwequency,               PPSMC_MSG_GetMinGfxDpmFweq,                1),
	MSG_MAP(GetMaxGfxcwkFwequency,               PPSMC_MSG_GetMaxGfxDpmFweq,                1),
	MSG_MAP(SetSoftMinGfxcwk,                    PPSMC_MSG_SetSoftMinGfxCwk,                1),
	MSG_MAP(SetSoftMaxGfxCwk,                    PPSMC_MSG_SetSoftMaxGfxCwk,                1),
	MSG_MAP(PwepaweMp1FowUnwoad,                 PPSMC_MSG_PwepaweFowDwivewUnwoad,          0),
	MSG_MAP(GetCTFWimit,                         PPSMC_MSG_GetCTFWimit,                     0),
	MSG_MAP(GetThewmawWimit,                     PPSMC_MSG_WeadThwottwewWimit,              0),
	MSG_MAP(CweawMcaOnWead,	                     PPSMC_MSG_CweawMcaOnWead,                  0),
	MSG_MAP(QuewyVawidMcaCount,                  PPSMC_MSG_QuewyVawidMcaCount,              0),
	MSG_MAP(QuewyVawidMcaCeCount,                PPSMC_MSG_QuewyVawidMcaCeCount,            0),
	MSG_MAP(McaBankDumpDW,                       PPSMC_MSG_McaBankDumpDW,                   0),
	MSG_MAP(McaBankCeDumpDW,                     PPSMC_MSG_McaBankCeDumpDW,                 0),
	MSG_MAP(SewectPWPDMode,                      PPSMC_MSG_SewectPWPDMode,                  0),
};

// cwang-fowmat on
static const stwuct cmn2asic_mapping smu_v13_0_6_cwk_map[SMU_CWK_COUNT] = {
	CWK_MAP(SOCCWK, PPCWK_SOCCWK),
	CWK_MAP(FCWK, PPCWK_FCWK),
	CWK_MAP(UCWK, PPCWK_UCWK),
	CWK_MAP(MCWK, PPCWK_UCWK),
	CWK_MAP(DCWK, PPCWK_DCWK),
	CWK_MAP(VCWK, PPCWK_VCWK),
	CWK_MAP(WCWK, PPCWK_WCWK),
};

static const stwuct cmn2asic_mapping smu_v13_0_6_featuwe_mask_map[SMU_FEATUWE_COUNT] = {
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DATA_CAWCUWATIONS_BIT, 		FEATUWE_DATA_CAWCUWATION),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DPM_GFXCWK_BIT, 			FEATUWE_DPM_GFXCWK),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DPM_UCWK_BIT, 			FEATUWE_DPM_UCWK),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DPM_SOCCWK_BIT, 			FEATUWE_DPM_SOCCWK),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DPM_FCWK_BIT, 			FEATUWE_DPM_FCWK),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DPM_WCWK_BIT, 			FEATUWE_DPM_WCWK),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DPM_VCWK_BIT,			FEATUWE_DPM_VCN),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DPM_DCWK_BIT,			FEATUWE_DPM_VCN),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DPM_XGMI_BIT, 			FEATUWE_DPM_XGMI),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DS_GFXCWK_BIT, 			FEATUWE_DS_GFXCWK),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DS_SOCCWK_BIT, 			FEATUWE_DS_SOCCWK),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DS_WCWK_BIT, 			FEATUWE_DS_WCWK),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DS_FCWK_BIT, 			FEATUWE_DS_FCWK),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_VCN_DPM_BIT, 			FEATUWE_DPM_VCN),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_PPT_BIT, 			FEATUWE_PPT),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_TDC_BIT, 			FEATUWE_TDC),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_APCC_DFWW_BIT, 			FEATUWE_APCC_DFWW),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_MP1_CG_BIT, 			FEATUWE_SMU_CG),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_GFXOFF_BIT, 			FEATUWE_GFXOFF),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_FW_CTF_BIT, 			FEATUWE_FW_CTF),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_THEWMAW_BIT, 			FEATUWE_THEWMAW),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_XGMI_PEW_WINK_PWW_DWN_BIT,	FEATUWE_XGMI_PEW_WINK_PWW_DOWN),
	SMU_13_0_6_FEA_MAP(SMU_FEATUWE_DF_CSTATE_BIT, 			FEATUWE_DF_CSTATE),
};

#define TABWE_PMSTATUSWOG             0
#define TABWE_SMU_METWICS             1
#define TABWE_I2C_COMMANDS            2
#define TABWE_COUNT                   3

static const stwuct cmn2asic_mapping smu_v13_0_6_tabwe_map[SMU_TABWE_COUNT] = {
	TAB_MAP(PMSTATUSWOG),
	TAB_MAP(SMU_METWICS),
	TAB_MAP(I2C_COMMANDS),
};

static const uint8_t smu_v13_0_6_thwottwew_map[] = {
	[THWOTTWEW_PPT_BIT]		= (SMU_THWOTTWEW_PPT0_BIT),
	[THWOTTWEW_THEWMAW_SOCKET_BIT]	= (SMU_THWOTTWEW_TEMP_GPU_BIT),
	[THWOTTWEW_THEWMAW_HBM_BIT]	= (SMU_THWOTTWEW_TEMP_MEM_BIT),
	[THWOTTWEW_THEWMAW_VW_BIT]	= (SMU_THWOTTWEW_TEMP_VW_GFX_BIT),
	[THWOTTWEW_PWOCHOT_BIT]		= (SMU_THWOTTWEW_PWOCHOT_GFX_BIT),
};

stwuct PPTabwe_t {
	uint32_t MaxSocketPowewWimit;
	uint32_t MaxGfxcwkFwequency;
	uint32_t MinGfxcwkFwequency;
	uint32_t FcwkFwequencyTabwe[4];
	uint32_t UcwkFwequencyTabwe[4];
	uint32_t SoccwkFwequencyTabwe[4];
	uint32_t VcwkFwequencyTabwe[4];
	uint32_t DcwkFwequencyTabwe[4];
	uint32_t WcwkFwequencyTabwe[4];
	uint32_t MaxWcwkDpmWange;
	uint32_t MinWcwkDpmWange;
	uint64_t PubwicSewiawNumbew_AID;
	boow Init;
};

#define SMUQ10_TO_UINT(x) ((x) >> 10)
#define SMUQ10_FWAC(x) ((x) & 0x3ff)
#define SMUQ10_WOUND(x) ((SMUQ10_TO_UINT(x)) + ((SMUQ10_FWAC(x)) >= 0x200))
#define GET_METWIC_FIEWD(fiewd) ((adev->fwags & AMD_IS_APU) ?\
		(metwics_a->fiewd) : (metwics_x->fiewd))

stwuct smu_v13_0_6_dpm_map {
	enum smu_cwk_type cwk_type;
	uint32_t featuwe_num;
	stwuct smu_13_0_dpm_tabwe *dpm_tabwe;
	uint32_t *fweq_tabwe;
};

static int smu_v13_0_6_init_micwocode(stwuct smu_context *smu)
{
	const stwuct smc_fiwmwawe_headew_v2_1 *v2_1;
	const stwuct common_fiwmwawe_headew *hdw;
	stwuct amdgpu_fiwmwawe_info *ucode = NUWW;
	stwuct smc_soft_pptabwe_entwy *entwies;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t p2s_tabwe_id = P2S_TABWE_ID_A;
	int wet = 0, i, p2stabwe_count;
	chaw ucode_pwefix[15];
	chaw fw_name[30];

	/* No need to woad P2S tabwes in IOV mode */
	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	if (!(adev->fwags & AMD_IS_APU))
		p2s_tabwe_id = P2S_TABWE_ID_X;

	amdgpu_ucode_ip_vewsion_decode(adev, MP1_HWIP, ucode_pwefix,
				       sizeof(ucode_pwefix));

	snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s.bin", ucode_pwefix);

	wet = amdgpu_ucode_wequest(adev, &adev->pm.fw, fw_name);
	if (wet)
		goto out;

	hdw = (const stwuct common_fiwmwawe_headew *)adev->pm.fw->data;
	amdgpu_ucode_pwint_smc_hdw(hdw);

	/* SMU v13.0.6 binawy fiwe doesn't cawwy pptabwes, instead the entwies
	 * awe used to cawwy p2s tabwes.
	 */
	v2_1 = (const stwuct smc_fiwmwawe_headew_v2_1 *)adev->pm.fw->data;
	entwies = (stwuct smc_soft_pptabwe_entwy
			   *)((uint8_t *)v2_1 +
			      we32_to_cpu(v2_1->pptabwe_entwy_offset));
	p2stabwe_count = we32_to_cpu(v2_1->pptabwe_count);
	fow (i = 0; i < p2stabwe_count; i++) {
		if (we32_to_cpu(entwies[i].id) == p2s_tabwe_id) {
			smu->pptabwe_fiwmwawe.data =
				((uint8_t *)v2_1 +
				 we32_to_cpu(entwies[i].ppt_offset_bytes));
			smu->pptabwe_fiwmwawe.size =
				we32_to_cpu(entwies[i].ppt_size_bytes);
			bweak;
		}
	}

	if (smu->pptabwe_fiwmwawe.data && smu->pptabwe_fiwmwawe.size) {
		ucode = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_P2S_TABWE];
		ucode->ucode_id = AMDGPU_UCODE_ID_P2S_TABWE;
		ucode->fw = &smu->pptabwe_fiwmwawe;
		adev->fiwmwawe.fw_size += AWIGN(ucode->fw->size, PAGE_SIZE);
	}

	wetuwn 0;
out:
	amdgpu_ucode_wewease(&adev->pm.fw);

	wetuwn wet;
}

static int smu_v13_0_6_tabwes_init(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwes = smu_tabwe->tabwes;
	stwuct amdgpu_device *adev = smu->adev;

	if (!(adev->fwags & AMD_IS_APU))
		SMU_TABWE_INIT(tabwes, SMU_TABWE_PMSTATUSWOG, SMU13_TOOW_SIZE,
			       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);

	SMU_TABWE_INIT(tabwes, SMU_TABWE_SMU_METWICS,
		       max(sizeof(MetwicsTabweX_t), sizeof(MetwicsTabweA_t)),
		       PAGE_SIZE,
		       AMDGPU_GEM_DOMAIN_VWAM | AMDGPU_GEM_DOMAIN_GTT);

	SMU_TABWE_INIT(tabwes, SMU_TABWE_I2C_COMMANDS, sizeof(SwI2cWequest_t),
		       PAGE_SIZE,
		       AMDGPU_GEM_DOMAIN_VWAM | AMDGPU_GEM_DOMAIN_GTT);

	smu_tabwe->metwics_tabwe = kzawwoc(max(sizeof(MetwicsTabweX_t),
		       sizeof(MetwicsTabweA_t)), GFP_KEWNEW);
	if (!smu_tabwe->metwics_tabwe)
		wetuwn -ENOMEM;
	smu_tabwe->metwics_time = 0;

	smu_tabwe->gpu_metwics_tabwe_size = sizeof(stwuct gpu_metwics_v1_5);
	smu_tabwe->gpu_metwics_tabwe =
		kzawwoc(smu_tabwe->gpu_metwics_tabwe_size, GFP_KEWNEW);
	if (!smu_tabwe->gpu_metwics_tabwe) {
		kfwee(smu_tabwe->metwics_tabwe);
		wetuwn -ENOMEM;
	}

	smu_tabwe->dwivew_pptabwe =
		kzawwoc(sizeof(stwuct PPTabwe_t), GFP_KEWNEW);
	if (!smu_tabwe->dwivew_pptabwe) {
		kfwee(smu_tabwe->metwics_tabwe);
		kfwee(smu_tabwe->gpu_metwics_tabwe);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int smu_v13_0_6_awwocate_dpm_context(stwuct smu_context *smu)
{
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;

	smu_dpm->dpm_context =
		kzawwoc(sizeof(stwuct smu_13_0_dpm_context), GFP_KEWNEW);
	if (!smu_dpm->dpm_context)
		wetuwn -ENOMEM;
	smu_dpm->dpm_context_size = sizeof(stwuct smu_13_0_dpm_context);

	wetuwn 0;
}

static int smu_v13_0_6_init_smc_tabwes(stwuct smu_context *smu)
{
	int wet = 0;

	wet = smu_v13_0_6_tabwes_init(smu);
	if (wet)
		wetuwn wet;

	wet = smu_v13_0_6_awwocate_dpm_context(smu);

	wetuwn wet;
}

static int smu_v13_0_6_get_awwowed_featuwe_mask(stwuct smu_context *smu,
						uint32_t *featuwe_mask,
						uint32_t num)
{
	if (num > 2)
		wetuwn -EINVAW;

	/* pptabwe wiww handwe the featuwes to enabwe */
	memset(featuwe_mask, 0xFF, sizeof(uint32_t) * num);

	wetuwn 0;
}

static int smu_v13_0_6_get_metwics_tabwe(stwuct smu_context *smu,
					 void *metwics_tabwe, boow bypass_cache)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	uint32_t tabwe_size = smu_tabwe->tabwes[SMU_TABWE_SMU_METWICS].size;
	stwuct smu_tabwe *tabwe = &smu_tabwe->dwivew_tabwe;
	int wet;

	if (bypass_cache || !smu_tabwe->metwics_time ||
	    time_aftew(jiffies,
		       smu_tabwe->metwics_time + msecs_to_jiffies(1))) {
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_GetMetwicsTabwe, NUWW);
		if (wet) {
			dev_info(smu->adev->dev,
				 "Faiwed to expowt SMU metwics tabwe!\n");
			wetuwn wet;
		}

		amdgpu_asic_invawidate_hdp(smu->adev, NUWW);
		memcpy(smu_tabwe->metwics_tabwe, tabwe->cpu_addw, tabwe_size);

		smu_tabwe->metwics_time = jiffies;
	}

	if (metwics_tabwe)
		memcpy(metwics_tabwe, smu_tabwe->metwics_tabwe, tabwe_size);

	wetuwn 0;
}

static ssize_t smu_v13_0_6_get_pm_metwics(stwuct smu_context *smu,
					  void *metwics, size_t max_size)
{
	stwuct smu_tabwe_context *smu_tbw_ctxt = &smu->smu_tabwe;
	uint32_t tabwe_vewsion = smu_tbw_ctxt->tabwes[SMU_TABWE_SMU_METWICS].vewsion;
	uint32_t tabwe_size = smu_tbw_ctxt->tabwes[SMU_TABWE_SMU_METWICS].size;
	stwuct amdgpu_pm_metwics *pm_metwics = metwics;
	uint32_t pmfw_vewsion;
	int wet;

	if (!pm_metwics || !max_size)
		wetuwn -EINVAW;

	if (max_size < (tabwe_size + sizeof(pm_metwics->common_headew)))
		wetuwn -EOVEWFWOW;

	/* Don't use cached metwics data */
	wet = smu_v13_0_6_get_metwics_tabwe(smu, pm_metwics->data, twue);
	if (wet)
		wetuwn wet;

	smu_cmn_get_smc_vewsion(smu, NUWW, &pmfw_vewsion);

	memset(&pm_metwics->common_headew, 0,
	       sizeof(pm_metwics->common_headew));
	pm_metwics->common_headew.mp1_ip_discovewy_vewsion =
		IP_VEWSION(13, 0, 6);
	pm_metwics->common_headew.pmfw_vewsion = pmfw_vewsion;
	pm_metwics->common_headew.pmmetwics_vewsion = tabwe_vewsion;
	pm_metwics->common_headew.stwuctuwe_size =
		sizeof(pm_metwics->common_headew) + tabwe_size;

	wetuwn pm_metwics->common_headew.stwuctuwe_size;
}

static int smu_v13_0_6_setup_dwivew_pptabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	MetwicsTabweX_t *metwics_x = (MetwicsTabweX_t *)smu_tabwe->metwics_tabwe;
	MetwicsTabweA_t *metwics_a = (MetwicsTabweA_t *)smu_tabwe->metwics_tabwe;
	stwuct PPTabwe_t *pptabwe =
		(stwuct PPTabwe_t *)smu_tabwe->dwivew_pptabwe;
	stwuct amdgpu_device *adev = smu->adev;
	int wet, i, wetwy = 100;
	uint32_t tabwe_vewsion;

	/* Stowe one-time vawues in dwivew PPTabwe */
	if (!pptabwe->Init) {
		whiwe (--wetwy) {
			wet = smu_v13_0_6_get_metwics_tabwe(smu, NUWW, twue);
			if (wet)
				wetuwn wet;

			/* Ensuwe that metwics have been updated */
			if (GET_METWIC_FIEWD(AccumuwationCountew))
				bweak;

			usweep_wange(1000, 1100);
		}

		if (!wetwy)
			wetuwn -ETIME;

		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_GetMetwicsVewsion,
					   &tabwe_vewsion);
		if (wet)
			wetuwn wet;
		smu_tabwe->tabwes[SMU_TABWE_SMU_METWICS].vewsion =
			tabwe_vewsion;

		pptabwe->MaxSocketPowewWimit =
			SMUQ10_WOUND(GET_METWIC_FIEWD(MaxSocketPowewWimit));
		pptabwe->MaxGfxcwkFwequency =
			SMUQ10_WOUND(GET_METWIC_FIEWD(MaxGfxcwkFwequency));
		pptabwe->MinGfxcwkFwequency =
			SMUQ10_WOUND(GET_METWIC_FIEWD(MinGfxcwkFwequency));

		fow (i = 0; i < 4; ++i) {
			pptabwe->FcwkFwequencyTabwe[i] =
				SMUQ10_WOUND(GET_METWIC_FIEWD(FcwkFwequencyTabwe)[i]);
			pptabwe->UcwkFwequencyTabwe[i] =
				SMUQ10_WOUND(GET_METWIC_FIEWD(UcwkFwequencyTabwe)[i]);
			pptabwe->SoccwkFwequencyTabwe[i] = SMUQ10_WOUND(
				GET_METWIC_FIEWD(SoccwkFwequencyTabwe)[i]);
			pptabwe->VcwkFwequencyTabwe[i] =
				SMUQ10_WOUND(GET_METWIC_FIEWD(VcwkFwequencyTabwe)[i]);
			pptabwe->DcwkFwequencyTabwe[i] =
				SMUQ10_WOUND(GET_METWIC_FIEWD(DcwkFwequencyTabwe)[i]);
			pptabwe->WcwkFwequencyTabwe[i] =
				SMUQ10_WOUND(GET_METWIC_FIEWD(WcwkFwequencyTabwe)[i]);
		}

		/* use AID0 sewiaw numbew by defauwt */
		pptabwe->PubwicSewiawNumbew_AID = GET_METWIC_FIEWD(PubwicSewiawNumbew_AID)[0];

		pptabwe->Init = twue;
	}

	wetuwn 0;
}

static int smu_v13_0_6_get_dpm_uwtimate_fweq(stwuct smu_context *smu,
					     enum smu_cwk_type cwk_type,
					     uint32_t *min, uint32_t *max)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct PPTabwe_t *pptabwe =
		(stwuct PPTabwe_t *)smu_tabwe->dwivew_pptabwe;
	uint32_t cwock_wimit = 0, pawam;
	int wet = 0, cwk_id = 0;

	if (!smu_cmn_cwk_dpm_is_enabwed(smu, cwk_type)) {
		switch (cwk_type) {
		case SMU_MCWK:
		case SMU_UCWK:
			if (pptabwe->Init)
				cwock_wimit = pptabwe->UcwkFwequencyTabwe[0];
			bweak;
		case SMU_GFXCWK:
		case SMU_SCWK:
			if (pptabwe->Init)
				cwock_wimit = pptabwe->MinGfxcwkFwequency;
			bweak;
		case SMU_SOCCWK:
			if (pptabwe->Init)
				cwock_wimit = pptabwe->SoccwkFwequencyTabwe[0];
			bweak;
		case SMU_FCWK:
			if (pptabwe->Init)
				cwock_wimit = pptabwe->FcwkFwequencyTabwe[0];
			bweak;
		case SMU_VCWK:
			if (pptabwe->Init)
				cwock_wimit = pptabwe->VcwkFwequencyTabwe[0];
			bweak;
		case SMU_DCWK:
			if (pptabwe->Init)
				cwock_wimit = pptabwe->DcwkFwequencyTabwe[0];
			bweak;
		defauwt:
			bweak;
		}

		if (min)
			*min = cwock_wimit;

		if (max)
			*max = cwock_wimit;

		wetuwn 0;
	}

	if (!(cwk_type == SMU_GFXCWK || cwk_type == SMU_SCWK)) {
		cwk_id = smu_cmn_to_asic_specific_index(
			smu, CMN2ASIC_MAPPING_CWK, cwk_type);
		if (cwk_id < 0) {
			wet = -EINVAW;
			goto faiwed;
		}
		pawam = (cwk_id & 0xffff) << 16;
	}

	if (max) {
		if (cwk_type == SMU_GFXCWK || cwk_type == SMU_SCWK)
			wet = smu_cmn_send_smc_msg(
				smu, SMU_MSG_GetMaxGfxcwkFwequency, max);
		ewse
			wet = smu_cmn_send_smc_msg_with_pawam(
				smu, SMU_MSG_GetMaxDpmFweq, pawam, max);
		if (wet)
			goto faiwed;
	}

	if (min) {
		if (cwk_type == SMU_GFXCWK || cwk_type == SMU_SCWK)
			wet = smu_cmn_send_smc_msg(
				smu, SMU_MSG_GetMinGfxcwkFwequency, min);
		ewse
			wet = smu_cmn_send_smc_msg_with_pawam(
				smu, SMU_MSG_GetMinDpmFweq, pawam, min);
	}

faiwed:
	wetuwn wet;
}

static int smu_v13_0_6_get_dpm_wevew_count(stwuct smu_context *smu,
					  enum smu_cwk_type cwk_type,
					  uint32_t *wevews)
{
	int wet;

	wet = smu_v13_0_get_dpm_fweq_by_index(smu, cwk_type, 0xff, wevews);
	if (!wet)
		++(*wevews);

	wetuwn wet;
}

static int smu_v13_0_6_set_defauwt_dpm_tabwe(stwuct smu_context *smu)
{
	stwuct smu_13_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_13_0_dpm_tabwe *dpm_tabwe = NUWW;
	stwuct PPTabwe_t *pptabwe =
		(stwuct PPTabwe_t *)smu_tabwe->dwivew_pptabwe;
	uint32_t gfxcwkmin, gfxcwkmax, wevews;
	int wet = 0, i, j;
	stwuct smu_v13_0_6_dpm_map dpm_map[] = {
		{ SMU_SOCCWK, SMU_FEATUWE_DPM_SOCCWK_BIT,
		  &dpm_context->dpm_tabwes.soc_tabwe,
		  pptabwe->SoccwkFwequencyTabwe },
		{ SMU_UCWK, SMU_FEATUWE_DPM_UCWK_BIT,
		  &dpm_context->dpm_tabwes.ucwk_tabwe,
		  pptabwe->UcwkFwequencyTabwe },
		{ SMU_FCWK, SMU_FEATUWE_DPM_FCWK_BIT,
		  &dpm_context->dpm_tabwes.fcwk_tabwe,
		  pptabwe->FcwkFwequencyTabwe },
		{ SMU_VCWK, SMU_FEATUWE_DPM_VCWK_BIT,
		  &dpm_context->dpm_tabwes.vcwk_tabwe,
		  pptabwe->VcwkFwequencyTabwe },
		{ SMU_DCWK, SMU_FEATUWE_DPM_DCWK_BIT,
		  &dpm_context->dpm_tabwes.dcwk_tabwe,
		  pptabwe->DcwkFwequencyTabwe },
	};

	smu_v13_0_6_setup_dwivew_pptabwe(smu);

	/* gfxcwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.gfx_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_GFXCWK_BIT)) {
		/* In the case of gfxcwk, onwy fine-gwained dpm is honowed.
		 * Get min/max vawues fwom FW.
		 */
		wet = smu_v13_0_6_get_dpm_uwtimate_fweq(smu, SMU_GFXCWK,
							&gfxcwkmin, &gfxcwkmax);
		if (wet)
			wetuwn wet;

		dpm_tabwe->count = 2;
		dpm_tabwe->dpm_wevews[0].vawue = gfxcwkmin;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->dpm_wevews[1].vawue = gfxcwkmax;
		dpm_tabwe->dpm_wevews[1].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[1].vawue;
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = pptabwe->MinGfxcwkFwequency;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	fow (j = 0; j < AWWAY_SIZE(dpm_map); j++) {
		dpm_tabwe = dpm_map[j].dpm_tabwe;
		wevews = 1;
		if (smu_cmn_featuwe_is_enabwed(smu, dpm_map[j].featuwe_num)) {
			wet = smu_v13_0_6_get_dpm_wevew_count(
				smu, dpm_map[j].cwk_type, &wevews);
			if (wet)
				wetuwn wet;
		}
		dpm_tabwe->count = wevews;
		fow (i = 0; i < dpm_tabwe->count; ++i) {
			dpm_tabwe->dpm_wevews[i].vawue =
				dpm_map[j].fweq_tabwe[i];
			dpm_tabwe->dpm_wevews[i].enabwed = twue;

		}
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[wevews - 1].vawue;

	}

	wetuwn 0;
}

static int smu_v13_0_6_setup_pptabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;

	/* TODO: PPTabwe is not avaiwabwe.
	 * 1) Find an awtewnate way to get 'PPTabwe vawues' hewe.
	 * 2) Check if thewe is SW CTF
	 */
	tabwe_context->thewmaw_contwowwew_type = 0;

	wetuwn 0;
}

static int smu_v13_0_6_check_fw_status(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t mp1_fw_fwags;

	mp1_fw_fwags =
		WWEG32_PCIE(MP1_Pubwic | (smnMP1_FIWMWAWE_FWAGS & 0xffffffff));

	if ((mp1_fw_fwags & MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED_MASK) >>
	    MP1_FIWMWAWE_FWAGS__INTEWWUPTS_ENABWED__SHIFT)
		wetuwn 0;

	wetuwn -EIO;
}

static int smu_v13_0_6_popuwate_umd_state_cwk(stwuct smu_context *smu)
{
	stwuct smu_13_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	stwuct smu_13_0_dpm_tabwe *gfx_tabwe =
		&dpm_context->dpm_tabwes.gfx_tabwe;
	stwuct smu_13_0_dpm_tabwe *mem_tabwe =
		&dpm_context->dpm_tabwes.ucwk_tabwe;
	stwuct smu_13_0_dpm_tabwe *soc_tabwe =
		&dpm_context->dpm_tabwes.soc_tabwe;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe = &smu->pstate_tabwe;

	pstate_tabwe->gfxcwk_pstate.min = gfx_tabwe->min;
	pstate_tabwe->gfxcwk_pstate.peak = gfx_tabwe->max;
	pstate_tabwe->gfxcwk_pstate.cuww.min = gfx_tabwe->min;
	pstate_tabwe->gfxcwk_pstate.cuww.max = gfx_tabwe->max;

	pstate_tabwe->ucwk_pstate.min = mem_tabwe->min;
	pstate_tabwe->ucwk_pstate.peak = mem_tabwe->max;
	pstate_tabwe->ucwk_pstate.cuww.min = mem_tabwe->min;
	pstate_tabwe->ucwk_pstate.cuww.max = mem_tabwe->max;

	pstate_tabwe->soccwk_pstate.min = soc_tabwe->min;
	pstate_tabwe->soccwk_pstate.peak = soc_tabwe->max;
	pstate_tabwe->soccwk_pstate.cuww.min = soc_tabwe->min;
	pstate_tabwe->soccwk_pstate.cuww.max = soc_tabwe->max;

	if (gfx_tabwe->count > SMU_13_0_6_UMD_PSTATE_GFXCWK_WEVEW &&
	    mem_tabwe->count > SMU_13_0_6_UMD_PSTATE_MCWK_WEVEW &&
	    soc_tabwe->count > SMU_13_0_6_UMD_PSTATE_SOCCWK_WEVEW) {
		pstate_tabwe->gfxcwk_pstate.standawd =
			gfx_tabwe->dpm_wevews[SMU_13_0_6_UMD_PSTATE_GFXCWK_WEVEW].vawue;
		pstate_tabwe->ucwk_pstate.standawd =
			mem_tabwe->dpm_wevews[SMU_13_0_6_UMD_PSTATE_MCWK_WEVEW].vawue;
		pstate_tabwe->soccwk_pstate.standawd =
			soc_tabwe->dpm_wevews[SMU_13_0_6_UMD_PSTATE_SOCCWK_WEVEW].vawue;
	} ewse {
		pstate_tabwe->gfxcwk_pstate.standawd =
			pstate_tabwe->gfxcwk_pstate.min;
		pstate_tabwe->ucwk_pstate.standawd =
			pstate_tabwe->ucwk_pstate.min;
		pstate_tabwe->soccwk_pstate.standawd =
			pstate_tabwe->soccwk_pstate.min;
	}

	wetuwn 0;
}

static int smu_v13_0_6_get_cwk_tabwe(stwuct smu_context *smu,
				     stwuct pp_cwock_wevews_with_watency *cwocks,
				     stwuct smu_13_0_dpm_tabwe *dpm_tabwe)
{
	int i, count;

	count = (dpm_tabwe->count > MAX_NUM_CWOCKS) ? MAX_NUM_CWOCKS :
						      dpm_tabwe->count;
	cwocks->num_wevews = count;

	fow (i = 0; i < count; i++) {
		cwocks->data[i].cwocks_in_khz =
			dpm_tabwe->dpm_wevews[i].vawue * 1000;
		cwocks->data[i].watency_in_us = 0;
	}

	wetuwn 0;
}

static int smu_v13_0_6_fweqs_in_same_wevew(int32_t fwequency1,
					   int32_t fwequency2)
{
	wetuwn (abs(fwequency1 - fwequency2) <= EPSIWON);
}

static uint32_t smu_v13_0_6_get_thwottwew_status(stwuct smu_context *smu)
{
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;
	stwuct smu_13_0_powew_context *powew_context = smu_powew->powew_context;
	uint32_t  thwottwew_status = 0;

	thwottwew_status = atomic_wead(&powew_context->thwottwe_status);
	dev_dbg(smu->adev->dev, "SMU Thwottwew status: %u", thwottwew_status);

	wetuwn thwottwew_status;
}

static int smu_v13_0_6_get_smu_metwics_data(stwuct smu_context *smu,
					    MetwicsMembew_t membew,
					    uint32_t *vawue)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	MetwicsTabweX_t *metwics_x = (MetwicsTabweX_t *)smu_tabwe->metwics_tabwe;
	MetwicsTabweA_t *metwics_a = (MetwicsTabweA_t *)smu_tabwe->metwics_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;
	int xcc_id;

	wet = smu_v13_0_6_get_metwics_tabwe(smu, NUWW, fawse);
	if (wet)
		wetuwn wet;

	/* Fow cwocks with muwtipwe instances, onwy wepowt the fiwst one */
	switch (membew) {
	case METWICS_CUWW_GFXCWK:
	case METWICS_AVEWAGE_GFXCWK:
		if (smu->smc_fw_vewsion >= 0x552F00) {
			xcc_id = GET_INST(GC, 0);
			*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(GfxcwkFwequency)[xcc_id]);
		} ewse {
			*vawue = 0;
		}
		bweak;
	case METWICS_CUWW_SOCCWK:
	case METWICS_AVEWAGE_SOCCWK:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(SoccwkFwequency)[0]);
		bweak;
	case METWICS_CUWW_UCWK:
	case METWICS_AVEWAGE_UCWK:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(UcwkFwequency));
		bweak;
	case METWICS_CUWW_VCWK:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(VcwkFwequency)[0]);
		bweak;
	case METWICS_CUWW_DCWK:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(DcwkFwequency)[0]);
		bweak;
	case METWICS_CUWW_FCWK:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(FcwkFwequency));
		bweak;
	case METWICS_AVEWAGE_GFXACTIVITY:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(SocketGfxBusy));
		bweak;
	case METWICS_AVEWAGE_MEMACTIVITY:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(DwamBandwidthUtiwization));
		bweak;
	case METWICS_CUWW_SOCKETPOWEW:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(SocketPowew)) << 8;
		bweak;
	case METWICS_TEMPEWATUWE_HOTSPOT:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(MaxSocketTempewatuwe)) *
			 SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_MEM:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(MaxHbmTempewatuwe)) *
			 SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	/* This is the max of aww VWs and not just SOC VW.
	 * No need to define anothew data type fow the same.
	 */
	case METWICS_TEMPEWATUWE_VWSOC:
		*vawue = SMUQ10_WOUND(GET_METWIC_FIEWD(MaxVwTempewatuwe)) *
			 SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	defauwt:
		*vawue = UINT_MAX;
		bweak;
	}

	wetuwn wet;
}

static int smu_v13_0_6_get_cuwwent_cwk_fweq_by_tabwe(stwuct smu_context *smu,
						     enum smu_cwk_type cwk_type,
						     uint32_t *vawue)
{
	MetwicsMembew_t membew_type;

	if (!vawue)
		wetuwn -EINVAW;

	switch (cwk_type) {
	case SMU_GFXCWK:
		membew_type = METWICS_CUWW_GFXCWK;
		bweak;
	case SMU_UCWK:
		membew_type = METWICS_CUWW_UCWK;
		bweak;
	case SMU_SOCCWK:
		membew_type = METWICS_CUWW_SOCCWK;
		bweak;
	case SMU_VCWK:
		membew_type = METWICS_CUWW_VCWK;
		bweak;
	case SMU_DCWK:
		membew_type = METWICS_CUWW_DCWK;
		bweak;
	case SMU_FCWK:
		membew_type = METWICS_CUWW_FCWK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn smu_v13_0_6_get_smu_metwics_data(smu, membew_type, vawue);
}

static int smu_v13_0_6_pwint_cwks(stwuct smu_context *smu, chaw *buf, int size,
				  stwuct smu_13_0_dpm_tabwe *singwe_dpm_tabwe,
				  uint32_t cuww_cwk, const chaw *cwk_name)
{
	stwuct pp_cwock_wevews_with_watency cwocks;
	int i, wet, wevew = -1;
	uint32_t cwk1, cwk2;

	wet = smu_v13_0_6_get_cwk_tabwe(smu, &cwocks, singwe_dpm_tabwe);
	if (wet) {
		dev_eww(smu->adev->dev, "Attempt to get %s cwk wevews faiwed!",
			cwk_name);
		wetuwn wet;
	}

	if (!cwocks.num_wevews)
		wetuwn -EINVAW;

	if (cuww_cwk < SMU_13_0_6_DSCWK_THWESHOWD) {
		size = sysfs_emit_at(buf, size, "S: %uMhz *\n", cuww_cwk);
		fow (i = 0; i < cwocks.num_wevews; i++)
			size += sysfs_emit_at(buf, size, "%d: %uMhz\n", i,
					      cwocks.data[i].cwocks_in_khz /
						      1000);

	} ewse {
		if ((cwocks.num_wevews == 1) ||
		    (cuww_cwk < (cwocks.data[0].cwocks_in_khz / 1000)))
			wevew = 0;
		fow (i = 0; i < cwocks.num_wevews; i++) {
			cwk1 = cwocks.data[i].cwocks_in_khz / 1000;

			if (i < (cwocks.num_wevews - 1))
				cwk2 = cwocks.data[i + 1].cwocks_in_khz / 1000;

			if (cuww_cwk == cwk1) {
				wevew = i;
			} ewse if (cuww_cwk >= cwk1 && cuww_cwk < cwk2) {
				wevew = (cuww_cwk - cwk1) <= (cwk2 - cuww_cwk) ?
						i :
						i + 1;
			}

			size += sysfs_emit_at(buf, size, "%d: %uMhz %s\n", i,
					      cwk1, (wevew == i) ? "*" : "");
		}
	}

	wetuwn size;
}

static int smu_v13_0_6_pwint_cwk_wevews(stwuct smu_context *smu,
					enum smu_cwk_type type, chaw *buf)
{
	int now, size = 0;
	int wet = 0;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe = &smu->pstate_tabwe;
	stwuct smu_13_0_dpm_tabwe *singwe_dpm_tabwe;
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;
	stwuct smu_13_0_dpm_context *dpm_context = NUWW;
	uint32_t min_cwk, max_cwk;

	smu_cmn_get_sysfs_buf(&buf, &size);

	if (amdgpu_was_intw_twiggewed()) {
		size += sysfs_emit_at(buf, size, "unavaiwabwe\n");
		wetuwn size;
	}

	dpm_context = smu_dpm->dpm_context;

	switch (type) {
	case SMU_OD_SCWK:
		size += sysfs_emit_at(buf, size, "%s:\n", "GFXCWK");
		fawwthwough;
	case SMU_SCWK:
		wet = smu_v13_0_6_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_GFXCWK,
								&now);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Attempt to get cuwwent gfx cwk Faiwed!");
			wetuwn wet;
		}

		min_cwk = pstate_tabwe->gfxcwk_pstate.cuww.min;
		max_cwk = pstate_tabwe->gfxcwk_pstate.cuww.max;

		if (now < SMU_13_0_6_DSCWK_THWESHOWD) {
			size += sysfs_emit_at(buf, size, "S: %uMhz *\n",
					      now);
			size += sysfs_emit_at(buf, size, "0: %uMhz\n",
					      min_cwk);
			size += sysfs_emit_at(buf, size, "1: %uMhz\n",
					      max_cwk);

		} ewse if (!smu_v13_0_6_fweqs_in_same_wevew(now, min_cwk) &&
		    !smu_v13_0_6_fweqs_in_same_wevew(now, max_cwk)) {
			size += sysfs_emit_at(buf, size, "0: %uMhz\n",
					      min_cwk);
			size += sysfs_emit_at(buf, size, "1: %uMhz *\n",
					      now);
			size += sysfs_emit_at(buf, size, "2: %uMhz\n",
					      max_cwk);
		} ewse {
			size += sysfs_emit_at(buf, size, "0: %uMhz %s\n",
					      min_cwk,
					      smu_v13_0_6_fweqs_in_same_wevew(now, min_cwk) ? "*" : "");
			size += sysfs_emit_at(buf, size, "1: %uMhz %s\n",
					      max_cwk,
					      smu_v13_0_6_fweqs_in_same_wevew(now, max_cwk) ? "*" : "");
		}

		bweak;

	case SMU_OD_MCWK:
		size += sysfs_emit_at(buf, size, "%s:\n", "MCWK");
		fawwthwough;
	case SMU_MCWK:
		wet = smu_v13_0_6_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_UCWK,
								&now);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Attempt to get cuwwent mcwk Faiwed!");
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.ucwk_tabwe);

		wetuwn smu_v13_0_6_pwint_cwks(smu, buf, size, singwe_dpm_tabwe,
					      now, "mcwk");

	case SMU_SOCCWK:
		wet = smu_v13_0_6_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_SOCCWK,
								&now);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Attempt to get cuwwent soccwk Faiwed!");
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.soc_tabwe);

		wetuwn smu_v13_0_6_pwint_cwks(smu, buf, size, singwe_dpm_tabwe,
					      now, "soccwk");

	case SMU_FCWK:
		wet = smu_v13_0_6_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_FCWK,
								&now);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Attempt to get cuwwent fcwk Faiwed!");
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.fcwk_tabwe);

		wetuwn smu_v13_0_6_pwint_cwks(smu, buf, size, singwe_dpm_tabwe,
					      now, "fcwk");

	case SMU_VCWK:
		wet = smu_v13_0_6_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_VCWK,
								&now);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Attempt to get cuwwent vcwk Faiwed!");
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.vcwk_tabwe);

		wetuwn smu_v13_0_6_pwint_cwks(smu, buf, size, singwe_dpm_tabwe,
					      now, "vcwk");

	case SMU_DCWK:
		wet = smu_v13_0_6_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_DCWK,
							       &now);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Attempt to get cuwwent dcwk Faiwed!");
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.dcwk_tabwe);

		wetuwn smu_v13_0_6_pwint_cwks(smu, buf, size, singwe_dpm_tabwe,
					      now, "dcwk");

	defauwt:
		bweak;
	}

	wetuwn size;
}

static int smu_v13_0_6_upwoad_dpm_wevew(stwuct smu_context *smu, boow max,
					uint32_t featuwe_mask, uint32_t wevew)
{
	stwuct smu_13_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	uint32_t fweq;
	int wet = 0;

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_GFXCWK_BIT) &&
	    (featuwe_mask & FEATUWE_MASK(FEATUWE_DPM_GFXCWK))) {
		fweq = dpm_context->dpm_tabwes.gfx_tabwe.dpm_wevews[wevew].vawue;
		wet = smu_cmn_send_smc_msg_with_pawam(
			smu,
			(max ? SMU_MSG_SetSoftMaxGfxCwk :
			       SMU_MSG_SetSoftMinGfxcwk),
			fweq & 0xffff, NUWW);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Faiwed to set soft %s gfxcwk !\n",
				max ? "max" : "min");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UCWK_BIT) &&
	    (featuwe_mask & FEATUWE_MASK(FEATUWE_DPM_UCWK))) {
		fweq = dpm_context->dpm_tabwes.ucwk_tabwe.dpm_wevews[wevew]
			       .vawue;
		wet = smu_cmn_send_smc_msg_with_pawam(
			smu,
			(max ? SMU_MSG_SetSoftMaxByFweq :
			       SMU_MSG_SetSoftMinByFweq),
			(PPCWK_UCWK << 16) | (fweq & 0xffff), NUWW);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Faiwed to set soft %s memcwk !\n",
				max ? "max" : "min");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_SOCCWK_BIT) &&
	    (featuwe_mask & FEATUWE_MASK(FEATUWE_DPM_SOCCWK))) {
		fweq = dpm_context->dpm_tabwes.soc_tabwe.dpm_wevews[wevew].vawue;
		wet = smu_cmn_send_smc_msg_with_pawam(
			smu,
			(max ? SMU_MSG_SetSoftMaxByFweq :
			       SMU_MSG_SetSoftMinByFweq),
			(PPCWK_SOCCWK << 16) | (fweq & 0xffff), NUWW);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Faiwed to set soft %s soccwk !\n",
				max ? "max" : "min");
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int smu_v13_0_6_fowce_cwk_wevews(stwuct smu_context *smu,
					enum smu_cwk_type type, uint32_t mask)
{
	stwuct smu_13_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	stwuct smu_13_0_dpm_tabwe *singwe_dpm_tabwe = NUWW;
	uint32_t soft_min_wevew, soft_max_wevew;
	int wet = 0;

	soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
	soft_max_wevew = mask ? (fws(mask) - 1) : 0;

	switch (type) {
	case SMU_SCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.gfx_tabwe);
		if (soft_max_wevew >= singwe_dpm_tabwe->count) {
			dev_eww(smu->adev->dev,
				"Cwock wevew specified %d is ovew max awwowed %d\n",
				soft_max_wevew, singwe_dpm_tabwe->count - 1);
			wet = -EINVAW;
			bweak;
		}

		wet = smu_v13_0_6_upwoad_dpm_wevew(
			smu, fawse, FEATUWE_MASK(FEATUWE_DPM_GFXCWK),
			soft_min_wevew);
		if (wet) {
			dev_eww(smu->adev->dev,
				"Faiwed to upwoad boot wevew to wowest!\n");
			bweak;
		}

		wet = smu_v13_0_6_upwoad_dpm_wevew(
			smu, twue, FEATUWE_MASK(FEATUWE_DPM_GFXCWK),
			soft_max_wevew);
		if (wet)
			dev_eww(smu->adev->dev,
				"Faiwed to upwoad dpm max wevew to highest!\n");

		bweak;

	case SMU_MCWK:
	case SMU_SOCCWK:
	case SMU_FCWK:
		/*
		 * Shouwd not awwive hewe since smu_13_0_6 does not
		 * suppowt mcwk/soccwk/fcwk softmin/softmax settings
		 */
		wet = -EINVAW;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int smu_v13_0_6_get_cuwwent_activity_pewcent(stwuct smu_context *smu,
						    enum amd_pp_sensows sensow,
						    uint32_t *vawue)
{
	int wet = 0;

	if (!vawue)
		wetuwn -EINVAW;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		wet = smu_v13_0_6_get_smu_metwics_data(
			smu, METWICS_AVEWAGE_GFXACTIVITY, vawue);
		bweak;
	case AMDGPU_PP_SENSOW_MEM_WOAD:
		wet = smu_v13_0_6_get_smu_metwics_data(
			smu, METWICS_AVEWAGE_MEMACTIVITY, vawue);
		bweak;
	defauwt:
		dev_eww(smu->adev->dev,
			"Invawid sensow fow wetwieving cwock activity\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int smu_v13_0_6_thewmaw_get_tempewatuwe(stwuct smu_context *smu,
					       enum amd_pp_sensows sensow,
					       uint32_t *vawue)
{
	int wet = 0;

	if (!vawue)
		wetuwn -EINVAW;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
		wet = smu_v13_0_6_get_smu_metwics_data(
			smu, METWICS_TEMPEWATUWE_HOTSPOT, vawue);
		bweak;
	case AMDGPU_PP_SENSOW_MEM_TEMP:
		wet = smu_v13_0_6_get_smu_metwics_data(
			smu, METWICS_TEMPEWATUWE_MEM, vawue);
		bweak;
	defauwt:
		dev_eww(smu->adev->dev, "Invawid sensow fow wetwieving temp\n");
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int smu_v13_0_6_wead_sensow(stwuct smu_context *smu,
				   enum amd_pp_sensows sensow, void *data,
				   uint32_t *size)
{
	int wet = 0;

	if (amdgpu_was_intw_twiggewed())
		wetuwn 0;

	if (!data || !size)
		wetuwn -EINVAW;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_MEM_WOAD:
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		wet = smu_v13_0_6_get_cuwwent_activity_pewcent(smu, sensow,
							       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
		wet = smu_v13_0_6_get_smu_metwics_data(smu,
						       METWICS_CUWW_SOCKETPOWEW,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
	case AMDGPU_PP_SENSOW_MEM_TEMP:
		wet = smu_v13_0_6_thewmaw_get_tempewatuwe(smu, sensow,
							  (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		wet = smu_v13_0_6_get_cuwwent_cwk_fweq_by_tabwe(
			smu, SMU_UCWK, (uint32_t *)data);
		/* the output cwock fwequency in 10K unit */
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		wet = smu_v13_0_6_get_cuwwent_cwk_fweq_by_tabwe(
			smu, SMU_GFXCWK, (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDGFX:
		wet = smu_v13_0_get_gfx_vdd(smu, (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_AVG_POWEW:
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int smu_v13_0_6_get_powew_wimit(stwuct smu_context *smu,
						uint32_t *cuwwent_powew_wimit,
						uint32_t *defauwt_powew_wimit,
						uint32_t *max_powew_wimit,
						uint32_t *min_powew_wimit)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct PPTabwe_t *pptabwe =
		(stwuct PPTabwe_t *)smu_tabwe->dwivew_pptabwe;
	uint32_t powew_wimit = 0;
	int wet;

	wet = smu_cmn_send_smc_msg(smu, SMU_MSG_GetPptWimit, &powew_wimit);

	if (wet) {
		dev_eww(smu->adev->dev, "Couwdn't get PPT wimit");
		wetuwn -EINVAW;
	}

	if (cuwwent_powew_wimit)
		*cuwwent_powew_wimit = powew_wimit;
	if (defauwt_powew_wimit)
		*defauwt_powew_wimit = powew_wimit;

	if (max_powew_wimit) {
		*max_powew_wimit = pptabwe->MaxSocketPowewWimit;
	}

	if (min_powew_wimit)
		*min_powew_wimit = 0;
	wetuwn 0;
}

static int smu_v13_0_6_set_powew_wimit(stwuct smu_context *smu,
				       enum smu_ppt_wimit_type wimit_type,
				       uint32_t wimit)
{
	wetuwn smu_v13_0_set_powew_wimit(smu, wimit_type, wimit);
}

static int smu_v13_0_6_iwq_pwocess(stwuct amdgpu_device *adev,
				   stwuct amdgpu_iwq_swc *souwce,
				   stwuct amdgpu_iv_entwy *entwy)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	stwuct smu_powew_context *smu_powew = &smu->smu_powew;
	stwuct smu_13_0_powew_context *powew_context = smu_powew->powew_context;
	uint32_t cwient_id = entwy->cwient_id;
	uint32_t ctxid = entwy->swc_data[0];
	uint32_t swc_id = entwy->swc_id;
	uint32_t data;

	if (cwient_id == SOC15_IH_CWIENTID_MP1) {
		if (swc_id == IH_INTEWWUPT_ID_TO_DWIVEW) {
			/* ACK SMUToHost intewwupt */
			data = WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW);
			data = WEG_SET_FIEWD(data, MP1_SMN_IH_SW_INT_CTWW, INT_ACK, 1);
			WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW, data);
			/*
			 * ctxid is used to distinguish diffewent events fow SMCToHost
			 * intewwupt.
			 */
			switch (ctxid) {
			case IH_INTEWWUPT_CONTEXT_ID_THEWMAW_THWOTTWING:
				/*
				 * Incwement the thwottwe intewwupt countew
				 */
				atomic64_inc(&smu->thwottwe_int_countew);

				if (!atomic_wead(&adev->thwottwing_wogging_enabwed))
					wetuwn 0;

				/* This uses the new method which fixes the
				 * incowwect thwottwing status wepowting
				 * thwough metwics tabwe. Fow owdew FWs,
				 * it wiww be ignowed.
				 */
				if (__watewimit(&adev->thwottwing_wogging_ws)) {
					atomic_set(
						&powew_context->thwottwe_status,
							entwy->swc_data[1]);
					scheduwe_wowk(&smu->thwottwing_wogging_wowk);
				}

				bweak;
			}
		}
	}

	wetuwn 0;
}

static int smu_v13_0_6_set_iwq_state(stwuct amdgpu_device *adev,
			      stwuct amdgpu_iwq_swc *souwce,
			      unsigned tyep,
			      enum amdgpu_intewwupt_state state)
{
	uint32_t vaw = 0;

	switch (state) {
	case AMDGPU_IWQ_STATE_DISABWE:
		/* Fow MP1 SW iwqs */
		vaw = WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT_CTWW, INT_MASK, 1);
		WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW, vaw);

		bweak;
	case AMDGPU_IWQ_STATE_ENABWE:
		/* Fow MP1 SW iwqs */
		vaw = WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT, ID, 0xFE);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT, VAWID, 0);
		WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT, vaw);

		vaw = WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW);
		vaw = WEG_SET_FIEWD(vaw, MP1_SMN_IH_SW_INT_CTWW, INT_MASK, 0);
		WWEG32_SOC15(MP1, 0, wegMP1_SMN_IH_SW_INT_CTWW, vaw);

		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs smu_v13_0_6_iwq_funcs = {
	.set = smu_v13_0_6_set_iwq_state,
	.pwocess = smu_v13_0_6_iwq_pwocess,
};

static int smu_v13_0_6_wegistew_iwq_handwew(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct amdgpu_iwq_swc *iwq_swc = &smu->iwq_souwce;
	int wet = 0;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	iwq_swc->num_types = 1;
	iwq_swc->funcs = &smu_v13_0_6_iwq_funcs;

	wet = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_MP1,
				IH_INTEWWUPT_ID_TO_DWIVEW,
				iwq_swc);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static int smu_v13_0_6_notify_unwoad(stwuct smu_context *smu)
{
	if (amdgpu_in_weset(smu->adev))
		wetuwn 0;

	dev_dbg(smu->adev->dev, "Notify PMFW about dwivew unwoad");
	/* Ignowe wetuwn, just intimate FW that dwivew is not going to be thewe */
	smu_cmn_send_smc_msg(smu, SMU_MSG_PwepaweMp1FowUnwoad, NUWW);

	wetuwn 0;
}

static int smu_v13_0_6_mca_set_debug_mode(stwuct smu_context *smu, boow enabwe)
{
	/* NOTE: this CweawMcaOnWead message is onwy suppowted fow smu vewsion 85.72.0 ow highew */
	if (smu->smc_fw_vewsion < 0x554800)
		wetuwn 0;

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_CweawMcaOnWead,
					       enabwe ? 0 : CweawMcaOnWead_UE_FWAG_MASK | CweawMcaOnWead_CE_POWW_MASK,
					       NUWW);
}

static int smu_v13_0_6_system_featuwes_contwow(stwuct smu_context *smu,
					       boow enabwe)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if (amdgpu_swiov_vf(adev))
		wetuwn 0;

	if (enabwe) {
		if (!(adev->fwags & AMD_IS_APU))
			wet = smu_v13_0_system_featuwes_contwow(smu, enabwe);
	} ewse {
		/* Notify FW that the device is no wongew dwivew managed */
		smu_v13_0_6_notify_unwoad(smu);
	}

	wetuwn wet;
}

static int smu_v13_0_6_set_gfx_soft_fweq_wimited_wange(stwuct smu_context *smu,
						       uint32_t min,
						       uint32_t max)
{
	int wet;

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxGfxCwk,
					      max & 0xffff, NUWW);
	if (wet)
		wetuwn wet;

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMinGfxcwk,
					      min & 0xffff, NUWW);

	wetuwn wet;
}

static int smu_v13_0_6_set_pewfowmance_wevew(stwuct smu_context *smu,
					     enum amd_dpm_fowced_wevew wevew)
{
	stwuct smu_dpm_context *smu_dpm = &(smu->smu_dpm);
	stwuct smu_13_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	stwuct smu_13_0_dpm_tabwe *gfx_tabwe =
		&dpm_context->dpm_tabwes.gfx_tabwe;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe = &smu->pstate_tabwe;
	int wet;

	/* Disabwe detewminism if switching to anothew mode */
	if ((smu_dpm->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM) &&
	    (wevew != AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM)) {
		smu_cmn_send_smc_msg(smu, SMU_MSG_DisabweDetewminism, NUWW);
		pstate_tabwe->gfxcwk_pstate.cuww.max = gfx_tabwe->max;
	}

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM:
		wetuwn 0;

	case AMD_DPM_FOWCED_WEVEW_AUTO:
		if ((gfx_tabwe->min == pstate_tabwe->gfxcwk_pstate.cuww.min) &&
		    (gfx_tabwe->max == pstate_tabwe->gfxcwk_pstate.cuww.max))
			wetuwn 0;

		wet = smu_v13_0_6_set_gfx_soft_fweq_wimited_wange(
			smu, gfx_tabwe->min, gfx_tabwe->max);
		if (wet)
			wetuwn wet;

		pstate_tabwe->gfxcwk_pstate.cuww.min = gfx_tabwe->min;
		pstate_tabwe->gfxcwk_pstate.cuww.max = gfx_tabwe->max;
		wetuwn 0;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
		wetuwn 0;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int smu_v13_0_6_set_soft_fweq_wimited_wange(stwuct smu_context *smu,
						   enum smu_cwk_type cwk_type,
						   uint32_t min, uint32_t max)
{
	stwuct smu_dpm_context *smu_dpm = &(smu->smu_dpm);
	stwuct smu_13_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe = &smu->pstate_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t min_cwk;
	uint32_t max_cwk;
	int wet = 0;

	if (cwk_type != SMU_GFXCWK && cwk_type != SMU_SCWK)
		wetuwn -EINVAW;

	if ((smu_dpm->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW) &&
	    (smu_dpm->dpm_wevew != AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM))
		wetuwn -EINVAW;

	if (smu_dpm->dpm_wevew == AMD_DPM_FOWCED_WEVEW_MANUAW) {
		if (min >= max) {
			dev_eww(smu->adev->dev,
				"Minimum GFX cwk shouwd be wess than the maximum awwowed cwock\n");
			wetuwn -EINVAW;
		}

		if ((min == pstate_tabwe->gfxcwk_pstate.cuww.min) &&
		    (max == pstate_tabwe->gfxcwk_pstate.cuww.max))
			wetuwn 0;

		wet = smu_v13_0_6_set_gfx_soft_fweq_wimited_wange(smu, min, max);
		if (!wet) {
			pstate_tabwe->gfxcwk_pstate.cuww.min = min;
			pstate_tabwe->gfxcwk_pstate.cuww.max = max;
		}

		wetuwn wet;
	}

	if (smu_dpm->dpm_wevew == AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM) {
		if (!max || (max < dpm_context->dpm_tabwes.gfx_tabwe.min) ||
		    (max > dpm_context->dpm_tabwes.gfx_tabwe.max)) {
			dev_wawn(
				adev->dev,
				"Invawid max fwequency %d MHz specified fow detewminism\n",
				max);
			wetuwn -EINVAW;
		}

		/* Westowe defauwt min/max cwocks and enabwe detewminism */
		min_cwk = dpm_context->dpm_tabwes.gfx_tabwe.min;
		max_cwk = dpm_context->dpm_tabwes.gfx_tabwe.max;
		wet = smu_v13_0_6_set_gfx_soft_fweq_wimited_wange(smu, min_cwk,
								 max_cwk);
		if (!wet) {
			usweep_wange(500, 1000);
			wet = smu_cmn_send_smc_msg_with_pawam(
				smu, SMU_MSG_EnabweDetewminism, max, NUWW);
			if (wet) {
				dev_eww(adev->dev,
					"Faiwed to enabwe detewminism at GFX cwock %d MHz\n",
					max);
			} ewse {
				pstate_tabwe->gfxcwk_pstate.cuww.min = min_cwk;
				pstate_tabwe->gfxcwk_pstate.cuww.max = max;
			}
		}
	}

	wetuwn wet;
}

static int smu_v13_0_6_usw_edit_dpm_tabwe(stwuct smu_context *smu,
					  enum PP_OD_DPM_TABWE_COMMAND type,
					  wong input[], uint32_t size)
{
	stwuct smu_dpm_context *smu_dpm = &(smu->smu_dpm);
	stwuct smu_13_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe = &smu->pstate_tabwe;
	uint32_t min_cwk;
	uint32_t max_cwk;
	int wet = 0;

	/* Onwy awwowed in manuaw ow detewminism mode */
	if ((smu_dpm->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW) &&
	    (smu_dpm->dpm_wevew != AMD_DPM_FOWCED_WEVEW_PEWF_DETEWMINISM))
		wetuwn -EINVAW;

	switch (type) {
	case PP_OD_EDIT_SCWK_VDDC_TABWE:
		if (size != 2) {
			dev_eww(smu->adev->dev,
				"Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		}

		if (input[0] == 0) {
			if (input[1] < dpm_context->dpm_tabwes.gfx_tabwe.min) {
				dev_wawn(
					smu->adev->dev,
					"Minimum GFX cwk (%wd) MHz specified is wess than the minimum awwowed (%d) MHz\n",
					input[1],
					dpm_context->dpm_tabwes.gfx_tabwe.min);
				pstate_tabwe->gfxcwk_pstate.custom.min =
					pstate_tabwe->gfxcwk_pstate.cuww.min;
				wetuwn -EINVAW;
			}

			pstate_tabwe->gfxcwk_pstate.custom.min = input[1];
		} ewse if (input[0] == 1) {
			if (input[1] > dpm_context->dpm_tabwes.gfx_tabwe.max) {
				dev_wawn(
					smu->adev->dev,
					"Maximum GFX cwk (%wd) MHz specified is gweatew than the maximum awwowed (%d) MHz\n",
					input[1],
					dpm_context->dpm_tabwes.gfx_tabwe.max);
				pstate_tabwe->gfxcwk_pstate.custom.max =
					pstate_tabwe->gfxcwk_pstate.cuww.max;
				wetuwn -EINVAW;
			}

			pstate_tabwe->gfxcwk_pstate.custom.max = input[1];
		} ewse {
			wetuwn -EINVAW;
		}
		bweak;
	case PP_OD_WESTOWE_DEFAUWT_TABWE:
		if (size != 0) {
			dev_eww(smu->adev->dev,
				"Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		} ewse {
			/* Use the defauwt fwequencies fow manuaw and detewminism mode */
			min_cwk = dpm_context->dpm_tabwes.gfx_tabwe.min;
			max_cwk = dpm_context->dpm_tabwes.gfx_tabwe.max;

			wetuwn smu_v13_0_6_set_soft_fweq_wimited_wange(
				smu, SMU_GFXCWK, min_cwk, max_cwk);
		}
		bweak;
	case PP_OD_COMMIT_DPM_TABWE:
		if (size != 0) {
			dev_eww(smu->adev->dev,
				"Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		} ewse {
			if (!pstate_tabwe->gfxcwk_pstate.custom.min)
				pstate_tabwe->gfxcwk_pstate.custom.min =
					pstate_tabwe->gfxcwk_pstate.cuww.min;

			if (!pstate_tabwe->gfxcwk_pstate.custom.max)
				pstate_tabwe->gfxcwk_pstate.custom.max =
					pstate_tabwe->gfxcwk_pstate.cuww.max;

			min_cwk = pstate_tabwe->gfxcwk_pstate.custom.min;
			max_cwk = pstate_tabwe->gfxcwk_pstate.custom.max;

			wetuwn smu_v13_0_6_set_soft_fweq_wimited_wange(
				smu, SMU_GFXCWK, min_cwk, max_cwk);
		}
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	wetuwn wet;
}

static int smu_v13_0_6_get_enabwed_mask(stwuct smu_context *smu,
					uint64_t *featuwe_mask)
{
	int wet;

	wet = smu_cmn_get_enabwed_mask(smu, featuwe_mask);

	if (wet == -EIO && smu->smc_fw_vewsion < 0x552F00) {
		*featuwe_mask = 0;
		wet = 0;
	}

	wetuwn wet;
}

static boow smu_v13_0_6_is_dpm_wunning(stwuct smu_context *smu)
{
	int wet;
	uint64_t featuwe_enabwed;

	wet = smu_v13_0_6_get_enabwed_mask(smu, &featuwe_enabwed);

	if (wet)
		wetuwn fawse;

	wetuwn !!(featuwe_enabwed & SMC_DPM_FEATUWE);
}

static int smu_v13_0_6_wequest_i2c_xfew(stwuct smu_context *smu,
					void *tabwe_data)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwe = &smu_tabwe->dwivew_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t tabwe_size;
	int wet = 0;

	if (!tabwe_data)
		wetuwn -EINVAW;

	tabwe_size = smu_tabwe->tabwes[SMU_TABWE_I2C_COMMANDS].size;

	memcpy(tabwe->cpu_addw, tabwe_data, tabwe_size);
	/* Fwush hdp cache */
	amdgpu_asic_fwush_hdp(adev, NUWW);
	wet = smu_cmn_send_smc_msg(smu, SMU_MSG_WequestI2cTwansaction,
					  NUWW);

	wetuwn wet;
}

static int smu_v13_0_6_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
				stwuct i2c_msg *msg, int num_msgs)
{
	stwuct amdgpu_smu_i2c_bus *smu_i2c = i2c_get_adapdata(i2c_adap);
	stwuct amdgpu_device *adev = smu_i2c->adev;
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwe = &smu_tabwe->dwivew_tabwe;
	SwI2cWequest_t *weq, *wes = (SwI2cWequest_t *)tabwe->cpu_addw;
	int i, j, w, c;
	u16 diw;

	if (!adev->pm.dpm_enabwed)
		wetuwn -EBUSY;

	weq = kzawwoc(sizeof(*weq), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	weq->I2CcontwowwewPowt = smu_i2c->powt;
	weq->I2CSpeed = I2C_SPEED_FAST_400K;
	weq->SwaveAddwess = msg[0].addw << 1; /* wants an 8-bit addwess */
	diw = msg[0].fwags & I2C_M_WD;

	fow (c = i = 0; i < num_msgs; i++) {
		fow (j = 0; j < msg[i].wen; j++, c++) {
			SwI2cCmd_t *cmd = &weq->SwI2cCmds[c];

			if (!(msg[i].fwags & I2C_M_WD)) {
				/* wwite */
				cmd->CmdConfig |= CMDCONFIG_WEADWWITE_MASK;
				cmd->WeadWwiteData = msg[i].buf[j];
			}

			if ((diw ^ msg[i].fwags) & I2C_M_WD) {
				/* The diwection changes.
				 */
				diw = msg[i].fwags & I2C_M_WD;
				cmd->CmdConfig |= CMDCONFIG_WESTAWT_MASK;
			}

			weq->NumCmds++;

			/*
			 * Insewt STOP if we awe at the wast byte of eithew wast
			 * message fow the twansaction ow the cwient expwicitwy
			 * wequiwes a STOP at this pawticuwaw message.
			 */
			if ((j == msg[i].wen - 1) &&
			    ((i == num_msgs - 1) || (msg[i].fwags & I2C_M_STOP))) {
				cmd->CmdConfig &= ~CMDCONFIG_WESTAWT_MASK;
				cmd->CmdConfig |= CMDCONFIG_STOP_MASK;
			}
		}
	}
	mutex_wock(&adev->pm.mutex);
	w = smu_v13_0_6_wequest_i2c_xfew(smu, weq);
	if (w)
		goto faiw;

	fow (c = i = 0; i < num_msgs; i++) {
		if (!(msg[i].fwags & I2C_M_WD)) {
			c += msg[i].wen;
			continue;
		}
		fow (j = 0; j < msg[i].wen; j++, c++) {
			SwI2cCmd_t *cmd = &wes->SwI2cCmds[c];

			msg[i].buf[j] = cmd->WeadWwiteData;
		}
	}
	w = num_msgs;
faiw:
	mutex_unwock(&adev->pm.mutex);
	kfwee(weq);
	wetuwn w;
}

static u32 smu_v13_0_6_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm smu_v13_0_6_i2c_awgo = {
	.mastew_xfew = smu_v13_0_6_i2c_xfew,
	.functionawity = smu_v13_0_6_i2c_func,
};

static const stwuct i2c_adaptew_quiwks smu_v13_0_6_i2c_contwow_quiwks = {
	.fwags = I2C_AQ_COMB | I2C_AQ_COMB_SAME_ADDW | I2C_AQ_NO_ZEWO_WEN,
	.max_wead_wen = MAX_SW_I2C_COMMANDS,
	.max_wwite_wen = MAX_SW_I2C_COMMANDS,
	.max_comb_1st_msg_wen = 2,
	.max_comb_2nd_msg_wen = MAX_SW_I2C_COMMANDS - 2,
};

static int smu_v13_0_6_i2c_contwow_init(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wes, i;

	fow (i = 0; i < MAX_SMU_I2C_BUSES; i++) {
		stwuct amdgpu_smu_i2c_bus *smu_i2c = &adev->pm.smu_i2c[i];
		stwuct i2c_adaptew *contwow = &smu_i2c->adaptew;

		smu_i2c->adev = adev;
		smu_i2c->powt = i;
		mutex_init(&smu_i2c->mutex);
		contwow->ownew = THIS_MODUWE;
		contwow->dev.pawent = &adev->pdev->dev;
		contwow->awgo = &smu_v13_0_6_i2c_awgo;
		snpwintf(contwow->name, sizeof(contwow->name), "AMDGPU SMU %d", i);
		contwow->quiwks = &smu_v13_0_6_i2c_contwow_quiwks;
		i2c_set_adapdata(contwow, smu_i2c);

		wes = i2c_add_adaptew(contwow);
		if (wes) {
			DWM_EWWOW("Faiwed to wegistew hw i2c, eww: %d\n", wes);
			goto Out_eww;
		}
	}

	adev->pm.was_eepwom_i2c_bus = &adev->pm.smu_i2c[0].adaptew;
	adev->pm.fwu_eepwom_i2c_bus = &adev->pm.smu_i2c[0].adaptew;

	wetuwn 0;
Out_eww:
	fow ( ; i >= 0; i--) {
		stwuct amdgpu_smu_i2c_bus *smu_i2c = &adev->pm.smu_i2c[i];
		stwuct i2c_adaptew *contwow = &smu_i2c->adaptew;

		i2c_dew_adaptew(contwow);
	}
	wetuwn wes;
}

static void smu_v13_0_6_i2c_contwow_fini(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int i;

	fow (i = 0; i < MAX_SMU_I2C_BUSES; i++) {
		stwuct amdgpu_smu_i2c_bus *smu_i2c = &adev->pm.smu_i2c[i];
		stwuct i2c_adaptew *contwow = &smu_i2c->adaptew;

		i2c_dew_adaptew(contwow);
	}
	adev->pm.was_eepwom_i2c_bus = NUWW;
	adev->pm.fwu_eepwom_i2c_bus = NUWW;
}

static void smu_v13_0_6_get_unique_id(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct PPTabwe_t *pptabwe =
		(stwuct PPTabwe_t *)smu_tabwe->dwivew_pptabwe;

	adev->unique_id = pptabwe->PubwicSewiawNumbew_AID;
}

static boow smu_v13_0_6_is_baco_suppowted(stwuct smu_context *smu)
{
	/* smu_13_0_6 does not suppowt baco */

	wetuwn fawse;
}

static const chaw *const thwottwing_wogging_wabew[] = {
	[THWOTTWEW_PWOCHOT_BIT] = "Pwochot",
	[THWOTTWEW_PPT_BIT] = "PPT",
	[THWOTTWEW_THEWMAW_SOCKET_BIT] = "SOC",
	[THWOTTWEW_THEWMAW_VW_BIT] = "VW",
	[THWOTTWEW_THEWMAW_HBM_BIT] = "HBM"
};

static void smu_v13_0_6_wog_thewmaw_thwottwing_event(stwuct smu_context *smu)
{
	int thwottwew_idx, thwottwing_events = 0, buf_idx = 0;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t thwottwew_status;
	chaw wog_buf[256];

	thwottwew_status = smu_v13_0_6_get_thwottwew_status(smu);
	if (!thwottwew_status)
		wetuwn;

	memset(wog_buf, 0, sizeof(wog_buf));
	fow (thwottwew_idx = 0;
	     thwottwew_idx < AWWAY_SIZE(thwottwing_wogging_wabew);
	     thwottwew_idx++) {
		if (thwottwew_status & (1U << thwottwew_idx)) {
			thwottwing_events++;
			buf_idx += snpwintf(
				wog_buf + buf_idx, sizeof(wog_buf) - buf_idx,
				"%s%s", thwottwing_events > 1 ? " and " : "",
				thwottwing_wogging_wabew[thwottwew_idx]);
			if (buf_idx >= sizeof(wog_buf)) {
				dev_eww(adev->dev, "buffew ovewfwow!\n");
				wog_buf[sizeof(wog_buf) - 1] = '\0';
				bweak;
			}
		}
	}

	dev_wawn(adev->dev,
		 "WAWN: GPU is thwottwed, expect pewfowmance decwease. %s.\n",
		 wog_buf);
	kgd2kfd_smi_event_thwottwe(
		smu->adev->kfd.dev,
		smu_cmn_get_indep_thwottwew_status(thwottwew_status,
						   smu_v13_0_6_thwottwew_map));
}

static int
smu_v13_0_6_get_cuwwent_pcie_wink_width_wevew(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	wetuwn WEG_GET_FIEWD(WWEG32_PCIE(smnPCIE_WC_WINK_WIDTH_CNTW),
			     PCIE_WC_WINK_WIDTH_CNTW, WC_WINK_WIDTH_WD);
}

static int smu_v13_0_6_get_cuwwent_pcie_wink_speed(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t speed_wevew;
	uint32_t esm_ctww;

	/* TODO: confiwm this on weaw tawget */
	esm_ctww = WWEG32_PCIE(smnPCIE_ESM_CTWW);
	if ((esm_ctww >> 15) & 0x1FFFF)
		wetuwn (((esm_ctww >> 8) & 0x3F) + 128);

	speed_wevew = (WWEG32_PCIE(smnPCIE_WC_SPEED_CNTW) &
		PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE_MASK)
		>> PCIE_WC_SPEED_CNTW__WC_CUWWENT_DATA_WATE__SHIFT;
	if (speed_wevew > WINK_SPEED_MAX)
		speed_wevew = 0;

	wetuwn pcie_gen_to_speed(speed_wevew + 1);
}

static ssize_t smu_v13_0_6_get_gpu_metwics(stwuct smu_context *smu, void **tabwe)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct gpu_metwics_v1_5 *gpu_metwics =
		(stwuct gpu_metwics_v1_5 *)smu_tabwe->gpu_metwics_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0, xcc_id, inst, i, j;
	MetwicsTabweX_t *metwics_x;
	MetwicsTabweA_t *metwics_a;
	u16 wink_width_wevew;

	metwics_x = kzawwoc(max(sizeof(MetwicsTabweX_t), sizeof(MetwicsTabweA_t)), GFP_KEWNEW);
	wet = smu_v13_0_6_get_metwics_tabwe(smu, metwics_x, twue);
	if (wet) {
		kfwee(metwics_x);
		wetuwn wet;
	}

	metwics_a = (MetwicsTabweA_t *)metwics_x;

	smu_cmn_init_soft_gpu_metwics(gpu_metwics, 1, 5);

	gpu_metwics->tempewatuwe_hotspot =
		SMUQ10_WOUND(GET_METWIC_FIEWD(MaxSocketTempewatuwe));
	/* Individuaw HBM stack tempewatuwe is not wepowted */
	gpu_metwics->tempewatuwe_mem =
		SMUQ10_WOUND(GET_METWIC_FIEWD(MaxHbmTempewatuwe));
	/* Wepowts max tempewatuwe of aww vowtage waiws */
	gpu_metwics->tempewatuwe_vwsoc =
		SMUQ10_WOUND(GET_METWIC_FIEWD(MaxVwTempewatuwe));

	gpu_metwics->avewage_gfx_activity =
		SMUQ10_WOUND(GET_METWIC_FIEWD(SocketGfxBusy));
	gpu_metwics->avewage_umc_activity =
		SMUQ10_WOUND(GET_METWIC_FIEWD(DwamBandwidthUtiwization));

	gpu_metwics->cuww_socket_powew =
		SMUQ10_WOUND(GET_METWIC_FIEWD(SocketPowew));
	/* Enewgy countew wepowted in 15.259uJ (2^-16) units */
	gpu_metwics->enewgy_accumuwatow = GET_METWIC_FIEWD(SocketEnewgyAcc);

	fow (i = 0; i < MAX_GFX_CWKS; i++) {
		xcc_id = GET_INST(GC, i);
		if (xcc_id >= 0)
			gpu_metwics->cuwwent_gfxcwk[i] =
				SMUQ10_WOUND(GET_METWIC_FIEWD(GfxcwkFwequency)[xcc_id]);

		if (i < MAX_CWKS) {
			gpu_metwics->cuwwent_soccwk[i] =
				SMUQ10_WOUND(GET_METWIC_FIEWD(SoccwkFwequency)[i]);
			inst = GET_INST(VCN, i);
			if (inst >= 0) {
				gpu_metwics->cuwwent_vcwk0[i] =
					SMUQ10_WOUND(GET_METWIC_FIEWD(VcwkFwequency)[inst]);
				gpu_metwics->cuwwent_dcwk0[i] =
					SMUQ10_WOUND(GET_METWIC_FIEWD(DcwkFwequency)[inst]);
			}
		}
	}

	gpu_metwics->cuwwent_ucwk = SMUQ10_WOUND(GET_METWIC_FIEWD(UcwkFwequency));

	/* Thwottwe status is not wepowted thwough metwics now */
	gpu_metwics->thwottwe_status = 0;

	/* Cwock Wock Status. Each bit cowwesponds to each GFXCWK instance */
	gpu_metwics->gfxcwk_wock_status = GET_METWIC_FIEWD(GfxWockXCDMak) >> GET_INST(GC, 0);

	if (!(adev->fwags & AMD_IS_APU)) {
		wink_width_wevew = smu_v13_0_6_get_cuwwent_pcie_wink_width_wevew(smu);
		if (wink_width_wevew > MAX_WINK_WIDTH)
			wink_width_wevew = 0;

		gpu_metwics->pcie_wink_width =
			DECODE_WANE_WIDTH(wink_width_wevew);
		gpu_metwics->pcie_wink_speed =
			smu_v13_0_6_get_cuwwent_pcie_wink_speed(smu);
		gpu_metwics->pcie_bandwidth_acc =
				SMUQ10_WOUND(metwics_x->PcieBandwidthAcc[0]);
		gpu_metwics->pcie_bandwidth_inst =
				SMUQ10_WOUND(metwics_x->PcieBandwidth[0]);
		gpu_metwics->pcie_w0_to_wecov_count_acc =
				metwics_x->PCIeW0ToWecovewyCountAcc;
		gpu_metwics->pcie_wepway_count_acc =
				metwics_x->PCIenWepwayAAcc;
		gpu_metwics->pcie_wepway_wovew_count_acc =
				metwics_x->PCIenWepwayAWowwovewCountAcc;
		gpu_metwics->pcie_nak_sent_count_acc =
				metwics_x->PCIeNAKSentCountAcc;
		gpu_metwics->pcie_nak_wcvd_count_acc =
				metwics_x->PCIeNAKWeceivedCountAcc;
	}

	gpu_metwics->system_cwock_countew = ktime_get_boottime_ns();

	gpu_metwics->gfx_activity_acc =
		SMUQ10_WOUND(GET_METWIC_FIEWD(SocketGfxBusyAcc));
	gpu_metwics->mem_activity_acc =
		SMUQ10_WOUND(GET_METWIC_FIEWD(DwamBandwidthUtiwizationAcc));

	fow (i = 0; i < NUM_XGMI_WINKS; i++) {
		gpu_metwics->xgmi_wead_data_acc[i] =
			SMUQ10_WOUND(GET_METWIC_FIEWD(XgmiWeadDataSizeAcc)[i]);
		gpu_metwics->xgmi_wwite_data_acc[i] =
			SMUQ10_WOUND(GET_METWIC_FIEWD(XgmiWwiteDataSizeAcc)[i]);
	}

	fow (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) {
		inst = GET_INST(JPEG, i);
		fow (j = 0; j < adev->jpeg.num_jpeg_wings; ++j) {
			gpu_metwics->jpeg_activity[(i * adev->jpeg.num_jpeg_wings) + j] =
				SMUQ10_WOUND(GET_METWIC_FIEWD(JpegBusy)
				[(inst * adev->jpeg.num_jpeg_wings) + j]);
		}
	}

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		inst = GET_INST(VCN, i);
		gpu_metwics->vcn_activity[i] =
			SMUQ10_WOUND(GET_METWIC_FIEWD(VcnBusy)[inst]);
	}

	gpu_metwics->xgmi_wink_width = SMUQ10_WOUND(GET_METWIC_FIEWD(XgmiWidth));
	gpu_metwics->xgmi_wink_speed = SMUQ10_WOUND(GET_METWIC_FIEWD(XgmiBitwate));

	gpu_metwics->fiwmwawe_timestamp = GET_METWIC_FIEWD(Timestamp);

	*tabwe = (void *)gpu_metwics;
	kfwee(metwics_x);

	wetuwn sizeof(*gpu_metwics);
}

static int smu_v13_0_6_mode2_weset(stwuct smu_context *smu)
{
	int wet = 0, index;
	stwuct amdgpu_device *adev = smu->adev;
	int timeout = 10;

	index = smu_cmn_to_asic_specific_index(smu, CMN2ASIC_MAPPING_MSG,
					       SMU_MSG_GfxDeviceDwivewWeset);

	mutex_wock(&smu->message_wock);

	wet = smu_cmn_send_msg_without_waiting(smu, (uint16_t)index,
					       SMU_WESET_MODE_2);

	/* This is simiwaw to FWW, wait tiww max FWW timeout */
	msweep(100);

	dev_dbg(smu->adev->dev, "westowe config space...\n");
	/* Westowe the config space saved duwing init */
	amdgpu_device_woad_pci_state(adev->pdev);

	dev_dbg(smu->adev->dev, "wait fow weset ack\n");
	do {
		wet = smu_cmn_wait_fow_wesponse(smu);
		/* Wait a bit mowe time fow getting ACK */
		if (wet == -ETIME) {
			--timeout;
			usweep_wange(500, 1000);
			continue;
		}

		if (wet)
			goto out;

	} whiwe (wet == -ETIME && timeout);

out:
	mutex_unwock(&smu->message_wock);

	if (wet)
		dev_eww(adev->dev, "faiwed to send mode2 weset, ewwow code %d",
			wet);

	wetuwn wet;
}

static int smu_v13_0_6_get_thewmaw_tempewatuwe_wange(stwuct smu_context *smu,
						     stwuct smu_tempewatuwe_wange *wange)
{
	stwuct amdgpu_device *adev = smu->adev;
	u32 aid_temp, xcd_temp, max_temp;
	u32 ccd_temp = 0;
	int wet;

	if (amdgpu_swiov_vf(smu->adev))
		wetuwn 0;

	if (!wange)
		wetuwn -EINVAW;

	/*Check smu vewsion, GetCtfWimit message onwy suppowted fow smu vewsion 85.69 ow highew */
	if (smu->smc_fw_vewsion < 0x554500)
		wetuwn 0;

	/* Get SOC Max opewating tempewatuwe */
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetCTFWimit,
					      PPSMC_AID_THM_TYPE, &aid_temp);
	if (wet)
		goto faiwed;
	if (adev->fwags & AMD_IS_APU) {
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetCTFWimit,
						      PPSMC_CCD_THM_TYPE, &ccd_temp);
		if (wet)
			goto faiwed;
	}
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetCTFWimit,
					      PPSMC_XCD_THM_TYPE, &xcd_temp);
	if (wet)
		goto faiwed;
	wange->hotspot_emewgency_max = max3(aid_temp, xcd_temp, ccd_temp) *
				       SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	/* Get HBM Max opewating tempewatuwe */
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetCTFWimit,
					      PPSMC_HBM_THM_TYPE, &max_temp);
	if (wet)
		goto faiwed;
	wange->mem_emewgency_max =
		max_temp * SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	/* Get SOC thewmaw thwottwe wimit */
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetThewmawWimit,
					      PPSMC_THWOTTWING_WIMIT_TYPE_SOCKET,
					      &max_temp);
	if (wet)
		goto faiwed;
	wange->hotspot_cwit_max =
		max_temp * SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	/* Get HBM thewmaw thwottwe wimit */
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GetThewmawWimit,
					      PPSMC_THWOTTWING_WIMIT_TYPE_HBM,
					      &max_temp);
	if (wet)
		goto faiwed;

	wange->mem_cwit_max = max_temp * SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

faiwed:
	wetuwn wet;
}

static int smu_v13_0_6_mode1_weset(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct amdgpu_hive_info *hive = NUWW;
	u32 hive_was_wecovewy = 0;
	stwuct amdgpu_was *was;
	u32 fataw_eww, pawam;
	int wet = 0;

	hive = amdgpu_get_xgmi_hive(adev);
	was = amdgpu_was_get_context(adev);
	fataw_eww = 0;
	pawam = SMU_WESET_MODE_1;

	if (hive) {
		hive_was_wecovewy = atomic_wead(&hive->was_wecovewy);
		amdgpu_put_xgmi_hive(hive);
	}

	/* fataw ewwow twiggewed by was, PMFW suppowts the fwag */
	if (was && (atomic_wead(&was->in_wecovewy) || hive_was_wecovewy))
		fataw_eww = 1;

	pawam |= (fataw_eww << 16);
	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GfxDeviceDwivewWeset,
					      pawam, NUWW);

	if (!wet)
		msweep(SMU13_MODE1_WESET_WAIT_TIME_IN_MS);

	wetuwn wet;
}

static boow smu_v13_0_6_is_mode1_weset_suppowted(stwuct smu_context *smu)
{
	wetuwn twue;
}

static boow smu_v13_0_6_is_mode2_weset_suppowted(stwuct smu_context *smu)
{
	wetuwn twue;
}

static int smu_v13_0_6_smu_send_hbm_bad_page_num(stwuct smu_context *smu,
						 uint32_t size)
{
	int wet = 0;

	/* message SMU to update the bad page numbew on SMUBUS */
	wet = smu_cmn_send_smc_msg_with_pawam(
		smu, SMU_MSG_SetNumBadHbmPagesWetiwed, size, NUWW);
	if (wet)
		dev_eww(smu->adev->dev,
			"[%s] faiwed to message SMU to update HBM bad pages numbew\n",
			__func__);

	wetuwn wet;
}

static int mca_smu_set_debug_mode(stwuct amdgpu_device *adev, boow enabwe)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;

	wetuwn smu_v13_0_6_mca_set_debug_mode(smu, enabwe);
}

static int smu_v13_0_6_get_vawid_mca_count(stwuct smu_context *smu, enum amdgpu_mca_ewwow_type type, uint32_t *count)
{
	uint32_t msg;
	int wet;

	if (!count)
		wetuwn -EINVAW;

	switch (type) {
	case AMDGPU_MCA_EWWOW_TYPE_UE:
		msg = SMU_MSG_QuewyVawidMcaCount;
		bweak;
	case AMDGPU_MCA_EWWOW_TYPE_CE:
		msg = SMU_MSG_QuewyVawidMcaCeCount;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = smu_cmn_send_smc_msg(smu, msg, count);
	if (wet) {
		*count = 0;
		wetuwn wet;
	}

	wetuwn 0;
}

static int __smu_v13_0_6_mca_dump_bank(stwuct smu_context *smu, enum amdgpu_mca_ewwow_type type,
				       int idx, int offset, uint32_t *vaw)
{
	uint32_t msg, pawam;

	switch (type) {
	case AMDGPU_MCA_EWWOW_TYPE_UE:
		msg = SMU_MSG_McaBankDumpDW;
		bweak;
	case AMDGPU_MCA_EWWOW_TYPE_CE:
		msg = SMU_MSG_McaBankCeDumpDW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	pawam = ((idx & 0xffff) << 16) | (offset & 0xfffc);

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu, msg, pawam, vaw);
}

static int smu_v13_0_6_mca_dump_bank(stwuct smu_context *smu, enum amdgpu_mca_ewwow_type type,
				     int idx, int offset, uint32_t *vaw, int count)
{
	int wet, i;

	if (!vaw)
		wetuwn -EINVAW;

	fow (i = 0; i < count; i++) {
		wet = __smu_v13_0_6_mca_dump_bank(smu, type, idx, offset + (i << 2), &vaw[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct mca_bank_ipid smu_v13_0_6_mca_ipid_tabwe[AMDGPU_MCA_IP_COUNT] = {
	MCA_BANK_IPID(UMC, 0x96, 0x0),
	MCA_BANK_IPID(SMU, 0x01, 0x1),
	MCA_BANK_IPID(MP5, 0x01, 0x2),
	MCA_BANK_IPID(PCS_XGMI, 0x50, 0x0),
};

static void mca_bank_entwy_info_decode(stwuct mca_bank_entwy *entwy, stwuct mca_bank_info *info)
{
	u64 ipid = entwy->wegs[MCA_WEG_IDX_IPID];
	u32 instidhi, instid;

	/* NOTE: Aww MCA IPID wegistew shawe the same fowmat,
	 * so the dwivew can shawe the MCMP1 wegistew headew fiwe.
	 * */

	info->hwid = WEG_GET_FIEWD(ipid, MCMP1_IPIDT0, HawdwaweID);
	info->mcatype = WEG_GET_FIEWD(ipid, MCMP1_IPIDT0, McaType);

	/*
	 * Unfied DieID Fowmat: SAASS. A:AID, S:Socket.
	 * Unfied DieID[4] = InstanceId[0]
	 * Unfied DieID[0:3] = InstanceIdHi[0:3]
	 */
	instidhi = WEG_GET_FIEWD(ipid, MCMP1_IPIDT0, InstanceIdHi);
	instid = WEG_GET_FIEWD(ipid, MCMP1_IPIDT0, InstanceIdWo);
	info->aid = ((instidhi >> 2) & 0x03);
	info->socket_id = ((instid & 0x1) << 2) | (instidhi & 0x03);
}

static int mca_bank_wead_weg(stwuct amdgpu_device *adev, enum amdgpu_mca_ewwow_type type,
			     int idx, int weg_idx, uint64_t *vaw)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	uint32_t data[2] = {0, 0};
	int wet;

	if (!vaw || weg_idx >= MCA_WEG_IDX_COUNT)
		wetuwn -EINVAW;

	wet = smu_v13_0_6_mca_dump_bank(smu, type, idx, weg_idx * 8, data, AWWAY_SIZE(data));
	if (wet)
		wetuwn wet;

	*vaw = (uint64_t)data[1] << 32 | data[0];

	dev_dbg(adev->dev, "mca wead bank weg: type:%s, index: %d, weg_idx: %d, vaw: 0x%016wwx\n",
		type == AMDGPU_MCA_EWWOW_TYPE_UE ? "UE" : "CE", idx, weg_idx, *vaw);

	wetuwn 0;
}

static int mca_get_mca_entwy(stwuct amdgpu_device *adev, enum amdgpu_mca_ewwow_type type,
			     int idx, stwuct mca_bank_entwy *entwy)
{
	int i, wet;

	/* NOTE: popuwated aww mca wegistew by defauwt */
	fow (i = 0; i < AWWAY_SIZE(entwy->wegs); i++) {
		wet = mca_bank_wead_weg(adev, type, idx, i, &entwy->wegs[i]);
		if (wet)
			wetuwn wet;
	}

	entwy->idx = idx;
	entwy->type = type;

	mca_bank_entwy_info_decode(entwy, &entwy->info);

	wetuwn 0;
}

static int mca_decode_ipid_to_hwip(uint64_t vaw)
{
	const stwuct mca_bank_ipid *ipid;
	uint16_t hwid, mcatype;
	int i;

	hwid = WEG_GET_FIEWD(vaw, MCMP1_IPIDT0, HawdwaweID);
	mcatype = WEG_GET_FIEWD(vaw, MCMP1_IPIDT0, McaType);

	fow (i = 0; i < AWWAY_SIZE(smu_v13_0_6_mca_ipid_tabwe); i++) {
		ipid = &smu_v13_0_6_mca_ipid_tabwe[i];

		if (!ipid->hwid)
			continue;

		if (ipid->hwid == hwid && ipid->mcatype == mcatype)
			wetuwn i;
	}

	wetuwn AMDGPU_MCA_IP_UNKNOW;
}

static int mca_umc_mca_get_eww_count(const stwuct mca_was_info *mca_was, stwuct amdgpu_device *adev,
				     enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy, uint32_t *count)
{
	uint64_t status0;

	status0 = entwy->wegs[MCA_WEG_IDX_STATUS];

	if (!WEG_GET_FIEWD(status0, MCMP1_STATUST0, Vaw)) {
		*count = 0;
		wetuwn 0;
	}

	if (type == AMDGPU_MCA_EWWOW_TYPE_UE && umc_v12_0_is_uncowwectabwe_ewwow(adev, status0))
		*count = 1;
	ewse if (type == AMDGPU_MCA_EWWOW_TYPE_CE && umc_v12_0_is_cowwectabwe_ewwow(adev, status0))
		*count = 1;

	wetuwn 0;
}

static int mca_pcs_xgmi_mca_get_eww_count(const stwuct mca_was_info *mca_was, stwuct amdgpu_device *adev,
					  enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy,
					  uint32_t *count)
{
	u32 ext_ewwow_code;
	u32 eww_cnt;

	ext_ewwow_code = MCA_WEG__STATUS__EWWOWCODEEXT(entwy->wegs[MCA_WEG_IDX_STATUS]);
	eww_cnt = MCA_WEG__MISC0__EWWCNT(entwy->wegs[MCA_WEG_IDX_MISC0]);

	if (type == AMDGPU_MCA_EWWOW_TYPE_UE && ext_ewwow_code == 0)
		*count = eww_cnt;
	ewse if (type == AMDGPU_MCA_EWWOW_TYPE_CE && ext_ewwow_code == 6)
		*count = eww_cnt;

	wetuwn 0;
}

static boow mca_smu_check_ewwow_code(stwuct amdgpu_device *adev, const stwuct mca_was_info *mca_was,
				     uint32_t ewwcode)
{
	int i;

	if (!mca_was->eww_code_count || !mca_was->eww_code_awway)
		wetuwn twue;

	fow (i = 0; i < mca_was->eww_code_count; i++) {
		if (ewwcode == mca_was->eww_code_awway[i])
			wetuwn twue;
	}

	wetuwn fawse;
}

static int mca_gfx_mca_get_eww_count(const stwuct mca_was_info *mca_was, stwuct amdgpu_device *adev,
				     enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy, uint32_t *count)
{
	uint64_t status0, misc0;

	status0 = entwy->wegs[MCA_WEG_IDX_STATUS];
	if (!WEG_GET_FIEWD(status0, MCMP1_STATUST0, Vaw)) {
		*count = 0;
		wetuwn 0;
	}

	if (type == AMDGPU_MCA_EWWOW_TYPE_UE &&
	    WEG_GET_FIEWD(status0, MCMP1_STATUST0, UC) == 1 &&
	    WEG_GET_FIEWD(status0, MCMP1_STATUST0, PCC) == 1) {
		*count = 1;
		wetuwn 0;
	} ewse {
		misc0 = entwy->wegs[MCA_WEG_IDX_MISC0];
		*count = WEG_GET_FIEWD(misc0, MCMP1_MISC0T0, EwwCnt);
	}

	wetuwn 0;
}

static int mca_smu_mca_get_eww_count(const stwuct mca_was_info *mca_was, stwuct amdgpu_device *adev,
				     enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy, uint32_t *count)
{
	uint64_t status0, misc0;

	status0 = entwy->wegs[MCA_WEG_IDX_STATUS];
	if (!WEG_GET_FIEWD(status0, MCMP1_STATUST0, Vaw)) {
		*count = 0;
		wetuwn 0;
	}

	if (type == AMDGPU_MCA_EWWOW_TYPE_UE &&
	    WEG_GET_FIEWD(status0, MCMP1_STATUST0, UC) == 1 &&
	    WEG_GET_FIEWD(status0, MCMP1_STATUST0, PCC) == 1) {
		if (count)
			*count = 1;
		wetuwn 0;
	}

	misc0 = entwy->wegs[MCA_WEG_IDX_MISC0];
	*count = WEG_GET_FIEWD(misc0, MCMP1_MISC0T0, EwwCnt);

	wetuwn 0;
}

static boow mca_gfx_smu_bank_is_vawid(const stwuct mca_was_info *mca_was, stwuct amdgpu_device *adev,
				      enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy)
{
	uint32_t instwo;

	instwo = WEG_GET_FIEWD(entwy->wegs[MCA_WEG_IDX_IPID], MCMP1_IPIDT0, InstanceIdWo);
	instwo &= GENMASK(31, 1);
	switch (instwo) {
	case 0x36430400: /* SMNAID XCD 0 */
	case 0x38430400: /* SMNAID XCD 1 */
	case 0x40430400: /* SMNXCD XCD 0, NOTE: FIXME: fix this ewwow watew */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}

	wetuwn fawse;
};

static boow mca_smu_bank_is_vawid(const stwuct mca_was_info *mca_was, stwuct amdgpu_device *adev,
				  enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	uint32_t ewwcode, instwo;

	instwo = WEG_GET_FIEWD(entwy->wegs[MCA_WEG_IDX_IPID], MCMP1_IPIDT0, InstanceIdWo);
	instwo &= GENMASK(31, 1);
	if (instwo != 0x03b30400)
		wetuwn fawse;

	if (!(adev->fwags & AMD_IS_APU) && smu->smc_fw_vewsion >= 0x00555600) {
		ewwcode = MCA_WEG__SYND__EWWOWINFOWMATION(entwy->wegs[MCA_WEG_IDX_SYND]);
		ewwcode &= 0xff;
	} ewse {
		ewwcode = WEG_GET_FIEWD(entwy->wegs[MCA_WEG_IDX_STATUS], MCMP1_STATUST0, EwwowCode);
	}

	wetuwn mca_smu_check_ewwow_code(adev, mca_was, ewwcode);
}

static int sdma_eww_codes[] = { CODE_SDMA0, CODE_SDMA1, CODE_SDMA2, CODE_SDMA3 };
static int mmhub_eww_codes[] = {
	CODE_DAGB0, CODE_DAGB0 + 1, CODE_DAGB0 + 2, CODE_DAGB0 + 3, CODE_DAGB0 + 4, /* DAGB0-4 */
	CODE_EA0, CODE_EA0 + 1, CODE_EA0 + 2, CODE_EA0 + 3, CODE_EA0 + 4,	/* MMEA0-4*/
	CODE_VMW2, CODE_VMW2_WAWKEW, CODE_MMCANE,
};

static const stwuct mca_was_info mca_was_tabwe[] = {
	{
		.bwkid = AMDGPU_WAS_BWOCK__UMC,
		.ip = AMDGPU_MCA_IP_UMC,
		.get_eww_count = mca_umc_mca_get_eww_count,
	}, {
		.bwkid = AMDGPU_WAS_BWOCK__GFX,
		.ip = AMDGPU_MCA_IP_SMU,
		.get_eww_count = mca_gfx_mca_get_eww_count,
		.bank_is_vawid = mca_gfx_smu_bank_is_vawid,
	}, {
		.bwkid = AMDGPU_WAS_BWOCK__SDMA,
		.ip = AMDGPU_MCA_IP_SMU,
		.eww_code_awway = sdma_eww_codes,
		.eww_code_count = AWWAY_SIZE(sdma_eww_codes),
		.get_eww_count = mca_smu_mca_get_eww_count,
		.bank_is_vawid = mca_smu_bank_is_vawid,
	}, {
		.bwkid = AMDGPU_WAS_BWOCK__MMHUB,
		.ip = AMDGPU_MCA_IP_SMU,
		.eww_code_awway = mmhub_eww_codes,
		.eww_code_count = AWWAY_SIZE(mmhub_eww_codes),
		.get_eww_count = mca_smu_mca_get_eww_count,
		.bank_is_vawid = mca_smu_bank_is_vawid,
	}, {
		.bwkid = AMDGPU_WAS_BWOCK__XGMI_WAFW,
		.ip = AMDGPU_MCA_IP_PCS_XGMI,
		.get_eww_count = mca_pcs_xgmi_mca_get_eww_count,
	},
};

static const stwuct mca_was_info *mca_get_mca_was_info(stwuct amdgpu_device *adev, enum amdgpu_was_bwock bwkid)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mca_was_tabwe); i++) {
		if (mca_was_tabwe[i].bwkid == bwkid)
			wetuwn &mca_was_tabwe[i];
	}

	wetuwn NUWW;
}

static int mca_get_vawid_mca_count(stwuct amdgpu_device *adev, enum amdgpu_mca_ewwow_type type, uint32_t *count)
{
	stwuct smu_context *smu = adev->powewpway.pp_handwe;
	int wet;

	switch (type) {
	case AMDGPU_MCA_EWWOW_TYPE_UE:
	case AMDGPU_MCA_EWWOW_TYPE_CE:
		wet = smu_v13_0_6_get_vawid_mca_count(smu, type, count);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static boow mca_bank_is_vawid(stwuct amdgpu_device *adev, const stwuct mca_was_info *mca_was,
			      enum amdgpu_mca_ewwow_type type, stwuct mca_bank_entwy *entwy)
{
	if (mca_decode_ipid_to_hwip(entwy->wegs[MCA_WEG_IDX_IPID]) != mca_was->ip)
		wetuwn fawse;

	if (mca_was->bank_is_vawid)
		wetuwn mca_was->bank_is_vawid(mca_was, adev, type, entwy);

	wetuwn twue;
}

static int __mca_smu_get_was_mca_set(stwuct amdgpu_device *adev, const stwuct mca_was_info *mca_was,
				     enum amdgpu_mca_ewwow_type type, stwuct mca_bank_set *mca_set)
{
	stwuct mca_bank_entwy entwy;
	uint32_t mca_cnt;
	int i, wet;

	wet = mca_get_vawid_mca_count(adev, type, &mca_cnt);
	if (wet)
		wetuwn wet;

	/* if vawid mca bank count is 0, the dwivew can wetuwn 0 diwectwy */
	if (!mca_cnt)
		wetuwn 0;

	fow (i = 0; i < mca_cnt; i++) {
		memset(&entwy, 0, sizeof(entwy));
		wet = mca_get_mca_entwy(adev, type, i, &entwy);
		if (wet)
			wetuwn wet;

		if (mca_was && !mca_bank_is_vawid(adev, mca_was, type, &entwy))
			continue;

		wet = amdgpu_mca_bank_set_add_entwy(mca_set, &entwy);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mca_smu_get_was_mca_set(stwuct amdgpu_device *adev, enum amdgpu_was_bwock bwk,
				   enum amdgpu_mca_ewwow_type type, stwuct mca_bank_set *mca_set)
{
	const stwuct mca_was_info *mca_was = NUWW;

	if (!mca_set)
		wetuwn -EINVAW;

	if (bwk != AMDGPU_WAS_BWOCK_COUNT) {
		mca_was = mca_get_mca_was_info(adev, bwk);
		if (!mca_was)
			wetuwn -EOPNOTSUPP;
	}

	wetuwn __mca_smu_get_was_mca_set(adev, mca_was, type, mca_set);
}

static int mca_smu_pawse_mca_ewwow_count(stwuct amdgpu_device *adev, enum amdgpu_was_bwock bwk, enum amdgpu_mca_ewwow_type type,
					 stwuct mca_bank_entwy *entwy, uint32_t *count)
{
	const stwuct mca_was_info *mca_was;

	if (!entwy || !count)
		wetuwn -EINVAW;

	mca_was = mca_get_mca_was_info(adev, bwk);
	if (!mca_was)
		wetuwn -EOPNOTSUPP;

	if (!mca_bank_is_vawid(adev, mca_was, type, entwy)) {
		*count = 0;
		wetuwn 0;
	}

	wetuwn mca_was->get_eww_count(mca_was, adev, type, entwy, count);
}

static int mca_smu_get_mca_entwy(stwuct amdgpu_device *adev,
				 enum amdgpu_mca_ewwow_type type, int idx, stwuct mca_bank_entwy *entwy)
{
	wetuwn mca_get_mca_entwy(adev, type, idx, entwy);
}

static int mca_smu_get_vawid_mca_count(stwuct amdgpu_device *adev,
				       enum amdgpu_mca_ewwow_type type, uint32_t *count)
{
	wetuwn mca_get_vawid_mca_count(adev, type, count);
}

static const stwuct amdgpu_mca_smu_funcs smu_v13_0_6_mca_smu_funcs = {
	.max_ue_count = 12,
	.max_ce_count = 12,
	.mca_set_debug_mode = mca_smu_set_debug_mode,
	.mca_get_was_mca_set = mca_smu_get_was_mca_set,
	.mca_pawse_mca_ewwow_count = mca_smu_pawse_mca_ewwow_count,
	.mca_get_mca_entwy = mca_smu_get_mca_entwy,
	.mca_get_vawid_mca_count = mca_smu_get_vawid_mca_count,
};

static int smu_v13_0_6_sewect_xgmi_pwpd_powicy(stwuct smu_context *smu,
					       enum pp_xgmi_pwpd_mode mode)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet, pawam;

	switch (mode) {
	case XGMI_PWPD_DEFAUWT:
		pawam = PPSMC_PWPD_MODE_DEFAUWT;
		bweak;
	case XGMI_PWPD_OPTIMIZED:
		pawam = PPSMC_PWPD_MODE_OPTIMIZED;
		bweak;
	case XGMI_PWPD_DISAWWOW:
		pawam = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (mode == XGMI_PWPD_DISAWWOW)
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_GmiPwwDnContwow,
						      pawam, NUWW);
	ewse
		/* change xgmi pew-wink powew down powicy */
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_SewectPWPDMode,
						      pawam, NUWW);

	if (wet)
		dev_eww(adev->dev,
			"sewect xgmi pew-wink powew down powicy %d faiwed\n",
			mode);

	wetuwn wet;
}

static ssize_t smu_v13_0_6_get_ecc_info(stwuct smu_context *smu,
			void *tabwe)
{
	/* Suppowt ecc info by defauwt */
	wetuwn 0;
}

static const stwuct pptabwe_funcs smu_v13_0_6_ppt_funcs = {
	/* init dpm */
	.get_awwowed_featuwe_mask = smu_v13_0_6_get_awwowed_featuwe_mask,
	/* dpm/cwk tabwes */
	.set_defauwt_dpm_tabwe = smu_v13_0_6_set_defauwt_dpm_tabwe,
	.popuwate_umd_state_cwk = smu_v13_0_6_popuwate_umd_state_cwk,
	.pwint_cwk_wevews = smu_v13_0_6_pwint_cwk_wevews,
	.fowce_cwk_wevews = smu_v13_0_6_fowce_cwk_wevews,
	.wead_sensow = smu_v13_0_6_wead_sensow,
	.set_pewfowmance_wevew = smu_v13_0_6_set_pewfowmance_wevew,
	.get_powew_wimit = smu_v13_0_6_get_powew_wimit,
	.is_dpm_wunning = smu_v13_0_6_is_dpm_wunning,
	.get_unique_id = smu_v13_0_6_get_unique_id,
	.init_micwocode = smu_v13_0_6_init_micwocode,
	.fini_micwocode = smu_v13_0_fini_micwocode,
	.init_smc_tabwes = smu_v13_0_6_init_smc_tabwes,
	.fini_smc_tabwes = smu_v13_0_fini_smc_tabwes,
	.init_powew = smu_v13_0_init_powew,
	.fini_powew = smu_v13_0_fini_powew,
	.check_fw_status = smu_v13_0_6_check_fw_status,
	/* pptabwe wewated */
	.check_fw_vewsion = smu_v13_0_check_fw_vewsion,
	.set_dwivew_tabwe_wocation = smu_v13_0_set_dwivew_tabwe_wocation,
	.set_toow_tabwe_wocation = smu_v13_0_set_toow_tabwe_wocation,
	.notify_memowy_poow_wocation = smu_v13_0_notify_memowy_poow_wocation,
	.system_featuwes_contwow = smu_v13_0_6_system_featuwes_contwow,
	.send_smc_msg_with_pawam = smu_cmn_send_smc_msg_with_pawam,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.get_enabwed_mask = smu_v13_0_6_get_enabwed_mask,
	.featuwe_is_enabwed = smu_cmn_featuwe_is_enabwed,
	.set_powew_wimit = smu_v13_0_6_set_powew_wimit,
	.set_xgmi_pstate = smu_v13_0_set_xgmi_pstate,
	.wegistew_iwq_handwew = smu_v13_0_6_wegistew_iwq_handwew,
	.enabwe_thewmaw_awewt = smu_v13_0_enabwe_thewmaw_awewt,
	.disabwe_thewmaw_awewt = smu_v13_0_disabwe_thewmaw_awewt,
	.setup_pptabwe = smu_v13_0_6_setup_pptabwe,
	.baco_is_suppowt = smu_v13_0_6_is_baco_suppowted,
	.get_dpm_uwtimate_fweq = smu_v13_0_6_get_dpm_uwtimate_fweq,
	.set_soft_fweq_wimited_wange = smu_v13_0_6_set_soft_fweq_wimited_wange,
	.od_edit_dpm_tabwe = smu_v13_0_6_usw_edit_dpm_tabwe,
	.sewect_xgmi_pwpd_powicy = smu_v13_0_6_sewect_xgmi_pwpd_powicy,
	.wog_thewmaw_thwottwing_event = smu_v13_0_6_wog_thewmaw_thwottwing_event,
	.get_pp_featuwe_mask = smu_cmn_get_pp_featuwe_mask,
	.get_gpu_metwics = smu_v13_0_6_get_gpu_metwics,
	.get_pm_metwics = smu_v13_0_6_get_pm_metwics,
	.get_thewmaw_tempewatuwe_wange = smu_v13_0_6_get_thewmaw_tempewatuwe_wange,
	.mode1_weset_is_suppowt = smu_v13_0_6_is_mode1_weset_suppowted,
	.mode2_weset_is_suppowt = smu_v13_0_6_is_mode2_weset_suppowted,
	.mode1_weset = smu_v13_0_6_mode1_weset,
	.mode2_weset = smu_v13_0_6_mode2_weset,
	.wait_fow_event = smu_v13_0_wait_fow_event,
	.i2c_init = smu_v13_0_6_i2c_contwow_init,
	.i2c_fini = smu_v13_0_6_i2c_contwow_fini,
	.send_hbm_bad_pages_num = smu_v13_0_6_smu_send_hbm_bad_page_num,
	.get_ecc_info = smu_v13_0_6_get_ecc_info,
};

void smu_v13_0_6_set_ppt_funcs(stwuct smu_context *smu)
{
	smu->ppt_funcs = &smu_v13_0_6_ppt_funcs;
	smu->message_map = smu_v13_0_6_message_map;
	smu->cwock_map = smu_v13_0_6_cwk_map;
	smu->featuwe_map = smu_v13_0_6_featuwe_mask_map;
	smu->tabwe_map = smu_v13_0_6_tabwe_map;
	smu->smc_dwivew_if_vewsion = SMU13_0_6_DWIVEW_IF_VEWSION;
	smu_v13_0_set_smu_maiwbox_wegistews(smu);
	amdgpu_mca_smu_init_funcs(smu->adev, &smu_v13_0_6_mca_smu_funcs);
}
