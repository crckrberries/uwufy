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

#define SWSMU_CODE_WAYEW_W2

#incwude <winux/fiwmwawe.h>
#incwude "amdgpu.h"
#incwude "amdgpu_dpm.h"
#incwude "amdgpu_smu.h"
#incwude "atomfiwmwawe.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "amdgpu_atombios.h"
#incwude "smu_v11_0.h"
#incwude "smu11_dwivew_if_awctuwus.h"
#incwude "soc15_common.h"
#incwude "atom.h"
#incwude "awctuwus_ppt.h"
#incwude "smu_v11_0_pptabwe.h"
#incwude "awctuwus_ppsmc.h"
#incwude "nbio/nbio_7_4_offset.h"
#incwude "nbio/nbio_7_4_sh_mask.h"
#incwude "thm/thm_11_0_2_offset.h"
#incwude "thm/thm_11_0_2_sh_mask.h"
#incwude "amdgpu_xgmi.h"
#incwude <winux/i2c.h>
#incwude <winux/pci.h>
#incwude "amdgpu_was.h"
#incwude "smu_cmn.h"

/*
 * DO NOT use these fow eww/wawn/info/debug messages.
 * Use dev_eww, dev_wawn, dev_info and dev_dbg instead.
 * They awe mowe MGPU fwiendwy.
 */
#undef pw_eww
#undef pw_wawn
#undef pw_info
#undef pw_debug

#define AWCTUWUS_FEA_MAP(smu_featuwe, awctuwus_featuwe) \
	[smu_featuwe] = {1, (awctuwus_featuwe)}

#define SMU_FEATUWES_WOW_MASK        0x00000000FFFFFFFF
#define SMU_FEATUWES_WOW_SHIFT       0
#define SMU_FEATUWES_HIGH_MASK       0xFFFFFFFF00000000
#define SMU_FEATUWES_HIGH_SHIFT      32

#define SMC_DPM_FEATUWE ( \
	FEATUWE_DPM_PWEFETCHEW_MASK | \
	FEATUWE_DPM_GFXCWK_MASK | \
	FEATUWE_DPM_UCWK_MASK | \
	FEATUWE_DPM_SOCCWK_MASK | \
	FEATUWE_DPM_MP0CWK_MASK | \
	FEATUWE_DPM_FCWK_MASK | \
	FEATUWE_DPM_XGMI_MASK)

/* possibwe fwequency dwift (1Mhz) */
#define EPSIWON				1

#define smnPCIE_ESM_CTWW			0x111003D0

#define mmCG_FDO_CTWW0_AWCT			0x8B
#define mmCG_FDO_CTWW0_AWCT_BASE_IDX		0

#define mmCG_FDO_CTWW1_AWCT			0x8C
#define mmCG_FDO_CTWW1_AWCT_BASE_IDX		0

#define mmCG_FDO_CTWW2_AWCT			0x8D
#define mmCG_FDO_CTWW2_AWCT_BASE_IDX		0

#define mmCG_TACH_CTWW_AWCT			0x8E
#define mmCG_TACH_CTWW_AWCT_BASE_IDX		0

#define mmCG_TACH_STATUS_AWCT			0x8F
#define mmCG_TACH_STATUS_AWCT_BASE_IDX		0

#define mmCG_THEWMAW_STATUS_AWCT		0x90
#define mmCG_THEWMAW_STATUS_AWCT_BASE_IDX	0

static const stwuct cmn2asic_msg_mapping awctuwus_message_map[SMU_MSG_MAX_COUNT] = {
	MSG_MAP(TestMessage,			     PPSMC_MSG_TestMessage,			0),
	MSG_MAP(GetSmuVewsion,			     PPSMC_MSG_GetSmuVewsion,			1),
	MSG_MAP(GetDwivewIfVewsion,		     PPSMC_MSG_GetDwivewIfVewsion,		1),
	MSG_MAP(SetAwwowedFeatuwesMaskWow,	     PPSMC_MSG_SetAwwowedFeatuwesMaskWow,	0),
	MSG_MAP(SetAwwowedFeatuwesMaskHigh,	     PPSMC_MSG_SetAwwowedFeatuwesMaskHigh,	0),
	MSG_MAP(EnabweAwwSmuFeatuwes,		     PPSMC_MSG_EnabweAwwSmuFeatuwes,		0),
	MSG_MAP(DisabweAwwSmuFeatuwes,		     PPSMC_MSG_DisabweAwwSmuFeatuwes,		0),
	MSG_MAP(EnabweSmuFeatuwesWow,		     PPSMC_MSG_EnabweSmuFeatuwesWow,		1),
	MSG_MAP(EnabweSmuFeatuwesHigh,		     PPSMC_MSG_EnabweSmuFeatuwesHigh,		1),
	MSG_MAP(DisabweSmuFeatuwesWow,		     PPSMC_MSG_DisabweSmuFeatuwesWow,		0),
	MSG_MAP(DisabweSmuFeatuwesHigh,		     PPSMC_MSG_DisabweSmuFeatuwesHigh,		0),
	MSG_MAP(GetEnabwedSmuFeatuwesWow,	     PPSMC_MSG_GetEnabwedSmuFeatuwesWow,	0),
	MSG_MAP(GetEnabwedSmuFeatuwesHigh,	     PPSMC_MSG_GetEnabwedSmuFeatuwesHigh,	0),
	MSG_MAP(SetDwivewDwamAddwHigh,		     PPSMC_MSG_SetDwivewDwamAddwHigh,		1),
	MSG_MAP(SetDwivewDwamAddwWow,		     PPSMC_MSG_SetDwivewDwamAddwWow,		1),
	MSG_MAP(SetToowsDwamAddwHigh,		     PPSMC_MSG_SetToowsDwamAddwHigh,		0),
	MSG_MAP(SetToowsDwamAddwWow,		     PPSMC_MSG_SetToowsDwamAddwWow,		0),
	MSG_MAP(TwansfewTabweSmu2Dwam,		     PPSMC_MSG_TwansfewTabweSmu2Dwam,		1),
	MSG_MAP(TwansfewTabweDwam2Smu,		     PPSMC_MSG_TwansfewTabweDwam2Smu,		0),
	MSG_MAP(UseDefauwtPPTabwe,		     PPSMC_MSG_UseDefauwtPPTabwe,		0),
	MSG_MAP(UseBackupPPTabwe,		     PPSMC_MSG_UseBackupPPTabwe,		0),
	MSG_MAP(SetSystemViwtuawDwamAddwHigh,	     PPSMC_MSG_SetSystemViwtuawDwamAddwHigh,	0),
	MSG_MAP(SetSystemViwtuawDwamAddwWow,	     PPSMC_MSG_SetSystemViwtuawDwamAddwWow,	0),
	MSG_MAP(EntewBaco,			     PPSMC_MSG_EntewBaco,			0),
	MSG_MAP(ExitBaco,			     PPSMC_MSG_ExitBaco,			0),
	MSG_MAP(AwmD3,				     PPSMC_MSG_AwmD3,				0),
	MSG_MAP(SetSoftMinByFweq,		     PPSMC_MSG_SetSoftMinByFweq,		0),
	MSG_MAP(SetSoftMaxByFweq,		     PPSMC_MSG_SetSoftMaxByFweq,		0),
	MSG_MAP(SetHawdMinByFweq,		     PPSMC_MSG_SetHawdMinByFweq,		0),
	MSG_MAP(SetHawdMaxByFweq,		     PPSMC_MSG_SetHawdMaxByFweq,		0),
	MSG_MAP(GetMinDpmFweq,			     PPSMC_MSG_GetMinDpmFweq,			0),
	MSG_MAP(GetMaxDpmFweq,			     PPSMC_MSG_GetMaxDpmFweq,			0),
	MSG_MAP(GetDpmFweqByIndex,		     PPSMC_MSG_GetDpmFweqByIndex,		1),
	MSG_MAP(SetWowkwoadMask,		     PPSMC_MSG_SetWowkwoadMask,			1),
	MSG_MAP(SetDfSwitchType,		     PPSMC_MSG_SetDfSwitchType,			0),
	MSG_MAP(GetVowtageByDpm,		     PPSMC_MSG_GetVowtageByDpm,			0),
	MSG_MAP(GetVowtageByDpmOvewdwive,	     PPSMC_MSG_GetVowtageByDpmOvewdwive,	0),
	MSG_MAP(SetPptWimit,			     PPSMC_MSG_SetPptWimit,			0),
	MSG_MAP(GetPptWimit,			     PPSMC_MSG_GetPptWimit,			1),
	MSG_MAP(PowewUpVcn0,			     PPSMC_MSG_PowewUpVcn0,			0),
	MSG_MAP(PowewDownVcn0,			     PPSMC_MSG_PowewDownVcn0,			0),
	MSG_MAP(PowewUpVcn1,			     PPSMC_MSG_PowewUpVcn1,			0),
	MSG_MAP(PowewDownVcn1,			     PPSMC_MSG_PowewDownVcn1,			0),
	MSG_MAP(PwepaweMp1FowUnwoad,		     PPSMC_MSG_PwepaweMp1FowUnwoad,		0),
	MSG_MAP(PwepaweMp1FowWeset,		     PPSMC_MSG_PwepaweMp1FowWeset,		0),
	MSG_MAP(PwepaweMp1FowShutdown,		     PPSMC_MSG_PwepaweMp1FowShutdown,		0),
	MSG_MAP(SoftWeset,			     PPSMC_MSG_SoftWeset,			0),
	MSG_MAP(WunAfwwBtc,			     PPSMC_MSG_WunAfwwBtc,			0),
	MSG_MAP(WunDcBtc,			     PPSMC_MSG_WunDcBtc,			0),
	MSG_MAP(DwamWogSetDwamAddwHigh,		     PPSMC_MSG_DwamWogSetDwamAddwHigh,		0),
	MSG_MAP(DwamWogSetDwamAddwWow,		     PPSMC_MSG_DwamWogSetDwamAddwWow,		0),
	MSG_MAP(DwamWogSetDwamSize,		     PPSMC_MSG_DwamWogSetDwamSize,		0),
	MSG_MAP(GetDebugData,			     PPSMC_MSG_GetDebugData,			0),
	MSG_MAP(WafwTest,			     PPSMC_MSG_WafwTest,			0),
	MSG_MAP(SetXgmiMode,			     PPSMC_MSG_SetXgmiMode,			0),
	MSG_MAP(SetMemowyChannewEnabwe,		     PPSMC_MSG_SetMemowyChannewEnabwe,		0),
	MSG_MAP(DFCstateContwow,		     PPSMC_MSG_DFCstateContwow,			0),
	MSG_MAP(GmiPwwDnContwow,		     PPSMC_MSG_GmiPwwDnContwow,			0),
	MSG_MAP(WeadSewiawNumTop32,		     PPSMC_MSG_WeadSewiawNumTop32,		1),
	MSG_MAP(WeadSewiawNumBottom32,		     PPSMC_MSG_WeadSewiawNumBottom32,		1),
	MSG_MAP(WightSBW,			     PPSMC_MSG_WightSBW,			0),
};

static const stwuct cmn2asic_mapping awctuwus_cwk_map[SMU_CWK_COUNT] = {
	CWK_MAP(GFXCWK, PPCWK_GFXCWK),
	CWK_MAP(SCWK,	PPCWK_GFXCWK),
	CWK_MAP(SOCCWK, PPCWK_SOCCWK),
	CWK_MAP(FCWK, PPCWK_FCWK),
	CWK_MAP(UCWK, PPCWK_UCWK),
	CWK_MAP(MCWK, PPCWK_UCWK),
	CWK_MAP(DCWK, PPCWK_DCWK),
	CWK_MAP(VCWK, PPCWK_VCWK),
};

static const stwuct cmn2asic_mapping awctuwus_featuwe_mask_map[SMU_FEATUWE_COUNT] = {
	FEA_MAP(DPM_PWEFETCHEW),
	FEA_MAP(DPM_GFXCWK),
	FEA_MAP(DPM_UCWK),
	FEA_MAP(DPM_SOCCWK),
	FEA_MAP(DPM_FCWK),
	FEA_MAP(DPM_MP0CWK),
	FEA_MAP(DPM_XGMI),
	FEA_MAP(DS_GFXCWK),
	FEA_MAP(DS_SOCCWK),
	FEA_MAP(DS_WCWK),
	FEA_MAP(DS_FCWK),
	FEA_MAP(DS_UCWK),
	FEA_MAP(GFX_UWV),
	AWCTUWUS_FEA_MAP(SMU_FEATUWE_VCN_DPM_BIT, FEATUWE_DPM_VCN_BIT),
	FEA_MAP(WSMU_SMN_CG),
	FEA_MAP(WAFW_CG),
	FEA_MAP(PPT),
	FEA_MAP(TDC),
	FEA_MAP(APCC_PWUS),
	FEA_MAP(VW0HOT),
	FEA_MAP(VW1HOT),
	FEA_MAP(FW_CTF),
	FEA_MAP(FAN_CONTWOW),
	FEA_MAP(THEWMAW),
	FEA_MAP(OUT_OF_BAND_MONITOW),
	FEA_MAP(TEMP_DEPENDENT_VMIN),
};

static const stwuct cmn2asic_mapping awctuwus_tabwe_map[SMU_TABWE_COUNT] = {
	TAB_MAP(PPTABWE),
	TAB_MAP(AVFS),
	TAB_MAP(AVFS_PSM_DEBUG),
	TAB_MAP(AVFS_FUSE_OVEWWIDE),
	TAB_MAP(PMSTATUSWOG),
	TAB_MAP(SMU_METWICS),
	TAB_MAP(DWIVEW_SMU_CONFIG),
	TAB_MAP(OVEWDWIVE),
	TAB_MAP(I2C_COMMANDS),
	TAB_MAP(ACTIVITY_MONITOW_COEFF),
};

static const stwuct cmn2asic_mapping awctuwus_pww_swc_map[SMU_POWEW_SOUWCE_COUNT] = {
	PWW_MAP(AC),
	PWW_MAP(DC),
};

static const stwuct cmn2asic_mapping awctuwus_wowkwoad_map[PP_SMC_POWEW_PWOFIWE_COUNT] = {
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT,	WOWKWOAD_PPWIB_DEFAUWT_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_POWEWSAVING,		WOWKWOAD_PPWIB_POWEW_SAVING_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_VIDEO,		WOWKWOAD_PPWIB_VIDEO_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_COMPUTE,		WOWKWOAD_PPWIB_COMPUTE_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_CUSTOM,		WOWKWOAD_PPWIB_CUSTOM_BIT),
};

static const uint8_t awctuwus_thwottwew_map[] = {
	[THWOTTWEW_TEMP_EDGE_BIT]	= (SMU_THWOTTWEW_TEMP_EDGE_BIT),
	[THWOTTWEW_TEMP_HOTSPOT_BIT]	= (SMU_THWOTTWEW_TEMP_HOTSPOT_BIT),
	[THWOTTWEW_TEMP_MEM_BIT]	= (SMU_THWOTTWEW_TEMP_MEM_BIT),
	[THWOTTWEW_TEMP_VW_GFX_BIT]	= (SMU_THWOTTWEW_TEMP_VW_GFX_BIT),
	[THWOTTWEW_TEMP_VW_MEM_BIT]	= (SMU_THWOTTWEW_TEMP_VW_MEM0_BIT),
	[THWOTTWEW_TEMP_VW_SOC_BIT]	= (SMU_THWOTTWEW_TEMP_VW_SOC_BIT),
	[THWOTTWEW_TDC_GFX_BIT]		= (SMU_THWOTTWEW_TDC_GFX_BIT),
	[THWOTTWEW_TDC_SOC_BIT]		= (SMU_THWOTTWEW_TDC_SOC_BIT),
	[THWOTTWEW_PPT0_BIT]		= (SMU_THWOTTWEW_PPT0_BIT),
	[THWOTTWEW_PPT1_BIT]		= (SMU_THWOTTWEW_PPT1_BIT),
	[THWOTTWEW_PPT2_BIT]		= (SMU_THWOTTWEW_PPT2_BIT),
	[THWOTTWEW_PPT3_BIT]		= (SMU_THWOTTWEW_PPT3_BIT),
	[THWOTTWEW_PPM_BIT]		= (SMU_THWOTTWEW_PPM_BIT),
	[THWOTTWEW_FIT_BIT]		= (SMU_THWOTTWEW_FIT_BIT),
	[THWOTTWEW_APCC_BIT]		= (SMU_THWOTTWEW_APCC_BIT),
	[THWOTTWEW_VWHOT0_BIT]		= (SMU_THWOTTWEW_VWHOT0_BIT),
	[THWOTTWEW_VWHOT1_BIT]		= (SMU_THWOTTWEW_VWHOT1_BIT),
};

static int awctuwus_tabwes_init(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwes = smu_tabwe->tabwes;

	SMU_TABWE_INIT(tabwes, SMU_TABWE_PPTABWE, sizeof(PPTabwe_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);

	SMU_TABWE_INIT(tabwes, SMU_TABWE_PMSTATUSWOG, SMU11_TOOW_SIZE,
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);

	SMU_TABWE_INIT(tabwes, SMU_TABWE_SMU_METWICS, sizeof(SmuMetwics_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);

	SMU_TABWE_INIT(tabwes, SMU_TABWE_I2C_COMMANDS, sizeof(SwI2cWequest_t),
			       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);

	SMU_TABWE_INIT(tabwes, SMU_TABWE_ACTIVITY_MONITOW_COEFF,
		       sizeof(DpmActivityMonitowCoeffInt_t), PAGE_SIZE,
		       AMDGPU_GEM_DOMAIN_VWAM);

	smu_tabwe->metwics_tabwe = kzawwoc(sizeof(SmuMetwics_t), GFP_KEWNEW);
	if (!smu_tabwe->metwics_tabwe)
		wetuwn -ENOMEM;
	smu_tabwe->metwics_time = 0;

	smu_tabwe->gpu_metwics_tabwe_size = sizeof(stwuct gpu_metwics_v1_3);
	smu_tabwe->gpu_metwics_tabwe = kzawwoc(smu_tabwe->gpu_metwics_tabwe_size, GFP_KEWNEW);
	if (!smu_tabwe->gpu_metwics_tabwe) {
		kfwee(smu_tabwe->metwics_tabwe);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int awctuwus_awwocate_dpm_context(stwuct smu_context *smu)
{
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;

	smu_dpm->dpm_context = kzawwoc(sizeof(stwuct smu_11_0_dpm_context),
				       GFP_KEWNEW);
	if (!smu_dpm->dpm_context)
		wetuwn -ENOMEM;
	smu_dpm->dpm_context_size = sizeof(stwuct smu_11_0_dpm_context);

	wetuwn 0;
}

static int awctuwus_init_smc_tabwes(stwuct smu_context *smu)
{
	int wet = 0;

	wet = awctuwus_tabwes_init(smu);
	if (wet)
		wetuwn wet;

	wet = awctuwus_awwocate_dpm_context(smu);
	if (wet)
		wetuwn wet;

	wetuwn smu_v11_0_init_smc_tabwes(smu);
}

static int
awctuwus_get_awwowed_featuwe_mask(stwuct smu_context *smu,
				  uint32_t *featuwe_mask, uint32_t num)
{
	if (num > 2)
		wetuwn -EINVAW;

	/* pptabwe wiww handwe the featuwes to enabwe */
	memset(featuwe_mask, 0xFF, sizeof(uint32_t) * num);

	wetuwn 0;
}

static int awctuwus_set_defauwt_dpm_tabwe(stwuct smu_context *smu)
{
	stwuct smu_11_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	PPTabwe_t *dwivew_ppt = smu->smu_tabwe.dwivew_pptabwe;
	stwuct smu_11_0_dpm_tabwe *dpm_tabwe = NUWW;
	int wet = 0;

	/* soccwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.soc_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_SOCCWK_BIT)) {
		wet = smu_v11_0_set_singwe_dpm_tabwe(smu,
						     SMU_SOCCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
		dpm_tabwe->is_fine_gwained =
			!dwivew_ppt->DpmDescwiptow[PPCWK_SOCCWK].SnapToDiscwete;
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = smu->smu_tabwe.boot_vawues.soccwk / 100;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	/* gfxcwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.gfx_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_GFXCWK_BIT)) {
		wet = smu_v11_0_set_singwe_dpm_tabwe(smu,
						     SMU_GFXCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
		dpm_tabwe->is_fine_gwained =
			!dwivew_ppt->DpmDescwiptow[PPCWK_GFXCWK].SnapToDiscwete;
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = smu->smu_tabwe.boot_vawues.gfxcwk / 100;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	/* memcwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.ucwk_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UCWK_BIT)) {
		wet = smu_v11_0_set_singwe_dpm_tabwe(smu,
						     SMU_UCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
		dpm_tabwe->is_fine_gwained =
			!dwivew_ppt->DpmDescwiptow[PPCWK_UCWK].SnapToDiscwete;
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = smu->smu_tabwe.boot_vawues.ucwk / 100;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	/* fcwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.fcwk_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_FCWK_BIT)) {
		wet = smu_v11_0_set_singwe_dpm_tabwe(smu,
						     SMU_FCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
		dpm_tabwe->is_fine_gwained =
			!dwivew_ppt->DpmDescwiptow[PPCWK_FCWK].SnapToDiscwete;
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = smu->smu_tabwe.boot_vawues.fcwk / 100;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	wetuwn 0;
}

static void awctuwus_check_bxco_suppowt(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	stwuct smu_11_0_powewpway_tabwe *powewpway_tabwe =
		tabwe_context->powew_pway_tabwe;
	stwuct smu_baco_context *smu_baco = &smu->smu_baco;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t vaw;

	if (powewpway_tabwe->pwatfowm_caps & SMU_11_0_PP_PWATFOWM_CAP_BACO ||
	    powewpway_tabwe->pwatfowm_caps & SMU_11_0_PP_PWATFOWM_CAP_MACO) {
		vaw = WWEG32_SOC15(NBIO, 0, mmWCC_BIF_STWAP0);
		smu_baco->pwatfowm_suppowt =
			(vaw & WCC_BIF_STWAP0__STWAP_PX_CAPABWE_MASK) ? twue :
									fawse;
	}
}

static void awctuwus_check_fan_suppowt(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	PPTabwe_t *pptabwe = tabwe_context->dwivew_pptabwe;

	/* No sowt of fan contwow possibwe if PPTabwe has it disabwed */
	smu->adev->pm.no_fan =
		!(pptabwe->FeatuwesToWun[0] & FEATUWE_FAN_CONTWOW_MASK);
	if (smu->adev->pm.no_fan)
		dev_info_once(smu->adev->dev,
			      "PMFW based fan contwow disabwed");
}

static int awctuwus_check_powewpway_tabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	stwuct smu_11_0_powewpway_tabwe *powewpway_tabwe =
		tabwe_context->powew_pway_tabwe;

	awctuwus_check_bxco_suppowt(smu);
	awctuwus_check_fan_suppowt(smu);

	tabwe_context->thewmaw_contwowwew_type =
		powewpway_tabwe->thewmaw_contwowwew_type;

	wetuwn 0;
}

static int awctuwus_stowe_powewpway_tabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	stwuct smu_11_0_powewpway_tabwe *powewpway_tabwe =
		tabwe_context->powew_pway_tabwe;

	memcpy(tabwe_context->dwivew_pptabwe, &powewpway_tabwe->smc_pptabwe,
	       sizeof(PPTabwe_t));

	wetuwn 0;
}

static int awctuwus_append_powewpway_tabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	PPTabwe_t *smc_pptabwe = tabwe_context->dwivew_pptabwe;
	stwuct atom_smc_dpm_info_v4_6 *smc_dpm_tabwe;
	int index, wet;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					   smc_dpm_info);

	wet = amdgpu_atombios_get_data_tabwe(smu->adev, index, NUWW, NUWW, NUWW,
				      (uint8_t **)&smc_dpm_tabwe);
	if (wet)
		wetuwn wet;

	dev_info(smu->adev->dev, "smc_dpm_info tabwe wevision(fowmat.content): %d.%d\n",
			smc_dpm_tabwe->tabwe_headew.fowmat_wevision,
			smc_dpm_tabwe->tabwe_headew.content_wevision);

	if ((smc_dpm_tabwe->tabwe_headew.fowmat_wevision == 4) &&
	    (smc_dpm_tabwe->tabwe_headew.content_wevision == 6))
		smu_memcpy_twaiwing(smc_pptabwe, MaxVowtageStepGfx, BoawdWesewved,
				    smc_dpm_tabwe, maxvowtagestepgfx);
	wetuwn 0;
}

static int awctuwus_setup_pptabwe(stwuct smu_context *smu)
{
	int wet = 0;

	wet = smu_v11_0_setup_pptabwe(smu);
	if (wet)
		wetuwn wet;

	wet = awctuwus_stowe_powewpway_tabwe(smu);
	if (wet)
		wetuwn wet;

	wet = awctuwus_append_powewpway_tabwe(smu);
	if (wet)
		wetuwn wet;

	wet = awctuwus_check_powewpway_tabwe(smu);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static int awctuwus_wun_btc(stwuct smu_context *smu)
{
	int wet = 0;

	wet = smu_cmn_send_smc_msg(smu, SMU_MSG_WunAfwwBtc, NUWW);
	if (wet) {
		dev_eww(smu->adev->dev, "WunAfwwBtc faiwed!\n");
		wetuwn wet;
	}

	wetuwn smu_cmn_send_smc_msg(smu, SMU_MSG_WunDcBtc, NUWW);
}

static int awctuwus_popuwate_umd_state_cwk(stwuct smu_context *smu)
{
	stwuct smu_11_0_dpm_context *dpm_context =
				smu->smu_dpm.dpm_context;
	stwuct smu_11_0_dpm_tabwe *gfx_tabwe =
				&dpm_context->dpm_tabwes.gfx_tabwe;
	stwuct smu_11_0_dpm_tabwe *mem_tabwe =
				&dpm_context->dpm_tabwes.ucwk_tabwe;
	stwuct smu_11_0_dpm_tabwe *soc_tabwe =
				&dpm_context->dpm_tabwes.soc_tabwe;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe =
				&smu->pstate_tabwe;

	pstate_tabwe->gfxcwk_pstate.min = gfx_tabwe->min;
	pstate_tabwe->gfxcwk_pstate.peak = gfx_tabwe->max;

	pstate_tabwe->ucwk_pstate.min = mem_tabwe->min;
	pstate_tabwe->ucwk_pstate.peak = mem_tabwe->max;

	pstate_tabwe->soccwk_pstate.min = soc_tabwe->min;
	pstate_tabwe->soccwk_pstate.peak = soc_tabwe->max;

	if (gfx_tabwe->count > AWCTUWUS_UMD_PSTATE_GFXCWK_WEVEW &&
	    mem_tabwe->count > AWCTUWUS_UMD_PSTATE_MCWK_WEVEW &&
	    soc_tabwe->count > AWCTUWUS_UMD_PSTATE_SOCCWK_WEVEW) {
		pstate_tabwe->gfxcwk_pstate.standawd =
			gfx_tabwe->dpm_wevews[AWCTUWUS_UMD_PSTATE_GFXCWK_WEVEW].vawue;
		pstate_tabwe->ucwk_pstate.standawd =
			mem_tabwe->dpm_wevews[AWCTUWUS_UMD_PSTATE_MCWK_WEVEW].vawue;
		pstate_tabwe->soccwk_pstate.standawd =
			soc_tabwe->dpm_wevews[AWCTUWUS_UMD_PSTATE_SOCCWK_WEVEW].vawue;
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

static void awctuwus_get_cwk_tabwe(stwuct smu_context *smu,
				   stwuct pp_cwock_wevews_with_watency *cwocks,
				   stwuct smu_11_0_dpm_tabwe *dpm_tabwe)
{
	uint32_t i;

	cwocks->num_wevews = min_t(uint32_t,
				   dpm_tabwe->count,
				   (uint32_t)PP_MAX_CWOCK_WEVEWS);

	fow (i = 0; i < cwocks->num_wevews; i++) {
		cwocks->data[i].cwocks_in_khz =
			dpm_tabwe->dpm_wevews[i].vawue * 1000;
		cwocks->data[i].watency_in_us = 0;
	}
}

static int awctuwus_fweqs_in_same_wevew(int32_t fwequency1,
					int32_t fwequency2)
{
	wetuwn (abs(fwequency1 - fwequency2) <= EPSIWON);
}

static int awctuwus_get_smu_metwics_data(stwuct smu_context *smu,
					 MetwicsMembew_t membew,
					 uint32_t *vawue)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	SmuMetwics_t *metwics = (SmuMetwics_t *)smu_tabwe->metwics_tabwe;
	int wet = 0;

	wet = smu_cmn_get_metwics_tabwe(smu,
					NUWW,
					fawse);
	if (wet)
		wetuwn wet;

	switch (membew) {
	case METWICS_CUWW_GFXCWK:
		*vawue = metwics->CuwwCwock[PPCWK_GFXCWK];
		bweak;
	case METWICS_CUWW_SOCCWK:
		*vawue = metwics->CuwwCwock[PPCWK_SOCCWK];
		bweak;
	case METWICS_CUWW_UCWK:
		*vawue = metwics->CuwwCwock[PPCWK_UCWK];
		bweak;
	case METWICS_CUWW_VCWK:
		*vawue = metwics->CuwwCwock[PPCWK_VCWK];
		bweak;
	case METWICS_CUWW_DCWK:
		*vawue = metwics->CuwwCwock[PPCWK_DCWK];
		bweak;
	case METWICS_CUWW_FCWK:
		*vawue = metwics->CuwwCwock[PPCWK_FCWK];
		bweak;
	case METWICS_AVEWAGE_GFXCWK:
		*vawue = metwics->AvewageGfxcwkFwequency;
		bweak;
	case METWICS_AVEWAGE_SOCCWK:
		*vawue = metwics->AvewageSoccwkFwequency;
		bweak;
	case METWICS_AVEWAGE_UCWK:
		*vawue = metwics->AvewageUcwkFwequency;
		bweak;
	case METWICS_AVEWAGE_VCWK:
		*vawue = metwics->AvewageVcwkFwequency;
		bweak;
	case METWICS_AVEWAGE_DCWK:
		*vawue = metwics->AvewageDcwkFwequency;
		bweak;
	case METWICS_AVEWAGE_GFXACTIVITY:
		*vawue = metwics->AvewageGfxActivity;
		bweak;
	case METWICS_AVEWAGE_MEMACTIVITY:
		*vawue = metwics->AvewageUcwkActivity;
		bweak;
	case METWICS_AVEWAGE_VCNACTIVITY:
		*vawue = metwics->VcnActivityPewcentage;
		bweak;
	case METWICS_AVEWAGE_SOCKETPOWEW:
		*vawue = metwics->AvewageSocketPowew << 8;
		bweak;
	case METWICS_TEMPEWATUWE_EDGE:
		*vawue = metwics->TempewatuweEdge *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_HOTSPOT:
		*vawue = metwics->TempewatuweHotspot *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_MEM:
		*vawue = metwics->TempewatuweHBM *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_VWGFX:
		*vawue = metwics->TempewatuweVwGfx *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_VWSOC:
		*vawue = metwics->TempewatuweVwSoc *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_VWMEM:
		*vawue = metwics->TempewatuweVwMem *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_THWOTTWEW_STATUS:
		*vawue = metwics->ThwottwewStatus;
		bweak;
	case METWICS_CUWW_FANSPEED:
		*vawue = metwics->CuwwFanSpeed;
		bweak;
	defauwt:
		*vawue = UINT_MAX;
		bweak;
	}

	wetuwn wet;
}

static int awctuwus_get_cuwwent_cwk_fweq_by_tabwe(stwuct smu_context *smu,
				       enum smu_cwk_type cwk_type,
				       uint32_t *vawue)
{
	MetwicsMembew_t membew_type;
	int cwk_id = 0;

	if (!vawue)
		wetuwn -EINVAW;

	cwk_id = smu_cmn_to_asic_specific_index(smu,
						CMN2ASIC_MAPPING_CWK,
						cwk_type);
	if (cwk_id < 0)
		wetuwn -EINVAW;

	switch (cwk_id) {
	case PPCWK_GFXCWK:
		/*
		 * CuwwCwock[cwk_id] can pwovide accuwate
		 *   output onwy when the dpm featuwe is enabwed.
		 * We can use Avewage_* fow dpm disabwed case.
		 *   But this is avaiwabwe fow gfxcwk/ucwk/soccwk/vcwk/dcwk.
		 */
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_GFXCWK_BIT))
			membew_type = METWICS_CUWW_GFXCWK;
		ewse
			membew_type = METWICS_AVEWAGE_GFXCWK;
		bweak;
	case PPCWK_UCWK:
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UCWK_BIT))
			membew_type = METWICS_CUWW_UCWK;
		ewse
			membew_type = METWICS_AVEWAGE_UCWK;
		bweak;
	case PPCWK_SOCCWK:
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_SOCCWK_BIT))
			membew_type = METWICS_CUWW_SOCCWK;
		ewse
			membew_type = METWICS_AVEWAGE_SOCCWK;
		bweak;
	case PPCWK_VCWK:
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_VCN_DPM_BIT))
			membew_type = METWICS_CUWW_VCWK;
		ewse
			membew_type = METWICS_AVEWAGE_VCWK;
		bweak;
	case PPCWK_DCWK:
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_VCN_DPM_BIT))
			membew_type = METWICS_CUWW_DCWK;
		ewse
			membew_type = METWICS_AVEWAGE_DCWK;
		bweak;
	case PPCWK_FCWK:
		membew_type = METWICS_CUWW_FCWK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn awctuwus_get_smu_metwics_data(smu,
					     membew_type,
					     vawue);
}

static int awctuwus_emit_cwk_wevews(stwuct smu_context *smu,
				    enum smu_cwk_type type, chaw *buf, int *offset)
{
	int wet = 0;
	stwuct pp_cwock_wevews_with_watency cwocks;
	stwuct smu_11_0_dpm_tabwe *singwe_dpm_tabwe;
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;
	stwuct smu_11_0_dpm_context *dpm_context = NUWW;
	uint32_t gen_speed, wane_width;
	uint32_t i, cuw_vawue = 0;
	boow fweq_match;
	unsigned int cwock_mhz;
	static const chaw attempt_stwing[] = "Attempt to get cuwwent";

	if (amdgpu_was_intw_twiggewed()) {
		*offset += sysfs_emit_at(buf, *offset, "unavaiwabwe\n");
		wetuwn -EBUSY;
	}

	dpm_context = smu_dpm->dpm_context;

	switch (type) {
	case SMU_SCWK:
		wet = awctuwus_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_GFXCWK, &cuw_vawue);
		if (wet) {
			dev_eww(smu->adev->dev, "%s gfx cwk Faiwed!", attempt_stwing);
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.gfx_tabwe);
		awctuwus_get_cwk_tabwe(smu, &cwocks, singwe_dpm_tabwe);

		bweak;

	case SMU_MCWK:
		wet = awctuwus_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_UCWK, &cuw_vawue);
		if (wet) {
			dev_eww(smu->adev->dev, "%s mcwk Faiwed!", attempt_stwing);
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.ucwk_tabwe);
		awctuwus_get_cwk_tabwe(smu, &cwocks, singwe_dpm_tabwe);

		bweak;

	case SMU_SOCCWK:
		wet = awctuwus_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_SOCCWK, &cuw_vawue);
		if (wet) {
			dev_eww(smu->adev->dev, "%s soccwk Faiwed!", attempt_stwing);
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.soc_tabwe);
		awctuwus_get_cwk_tabwe(smu, &cwocks, singwe_dpm_tabwe);

		bweak;

	case SMU_FCWK:
		wet = awctuwus_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_FCWK, &cuw_vawue);
		if (wet) {
			dev_eww(smu->adev->dev, "%s fcwk Faiwed!", attempt_stwing);
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.fcwk_tabwe);
		awctuwus_get_cwk_tabwe(smu, &cwocks, singwe_dpm_tabwe);

		bweak;

	case SMU_VCWK:
		wet = awctuwus_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_VCWK, &cuw_vawue);
		if (wet) {
			dev_eww(smu->adev->dev, "%s vcwk Faiwed!", attempt_stwing);
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.vcwk_tabwe);
		awctuwus_get_cwk_tabwe(smu, &cwocks, singwe_dpm_tabwe);

		bweak;

	case SMU_DCWK:
		wet = awctuwus_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_DCWK, &cuw_vawue);
		if (wet) {
			dev_eww(smu->adev->dev, "%s dcwk Faiwed!", attempt_stwing);
			wetuwn wet;
		}

		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.dcwk_tabwe);
		awctuwus_get_cwk_tabwe(smu, &cwocks, singwe_dpm_tabwe);

		bweak;

	case SMU_PCIE:
		gen_speed = smu_v11_0_get_cuwwent_pcie_wink_speed_wevew(smu);
		wane_width = smu_v11_0_get_cuwwent_pcie_wink_width_wevew(smu);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	switch (type) {
	case SMU_SCWK:
	case SMU_MCWK:
	case SMU_SOCCWK:
	case SMU_FCWK:
	case SMU_VCWK:
	case SMU_DCWK:
		/*
		 * Fow DPM disabwed case, thewe wiww be onwy one cwock wevew.
		 * And it's safe to assume that is awways the cuwwent cwock.
		 */
		fow (i = 0; i < cwocks.num_wevews; i++) {
			cwock_mhz = cwocks.data[i].cwocks_in_khz / 1000;
			fweq_match = awctuwus_fweqs_in_same_wevew(cwock_mhz, cuw_vawue);
			fweq_match |= (cwocks.num_wevews == 1);

			*offset += sysfs_emit_at(buf, *offset, "%d: %uMhz %s\n",
				i, cwock_mhz,
				fweq_match ? "*" : "");
		}
		bweak;

	case SMU_PCIE:
		*offset += sysfs_emit_at(buf, *offset, "0: %s %s %dMhz *\n",
				(gen_speed == 0) ? "2.5GT/s," :
				(gen_speed == 1) ? "5.0GT/s," :
				(gen_speed == 2) ? "8.0GT/s," :
				(gen_speed == 3) ? "16.0GT/s," : "",
				(wane_width == 1) ? "x1" :
				(wane_width == 2) ? "x2" :
				(wane_width == 3) ? "x4" :
				(wane_width == 4) ? "x8" :
				(wane_width == 5) ? "x12" :
				(wane_width == 6) ? "x16" : "",
				smu->smu_tabwe.boot_vawues.wcwk / 100);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int awctuwus_upwoad_dpm_wevew(stwuct smu_context *smu,
				     boow max,
				     uint32_t featuwe_mask,
				     uint32_t wevew)
{
	stwuct smu_11_0_dpm_context *dpm_context =
			smu->smu_dpm.dpm_context;
	uint32_t fweq;
	int wet = 0;

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_GFXCWK_BIT) &&
	    (featuwe_mask & FEATUWE_DPM_GFXCWK_MASK)) {
		fweq = dpm_context->dpm_tabwes.gfx_tabwe.dpm_wevews[wevew].vawue;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
			(max ? SMU_MSG_SetSoftMaxByFweq : SMU_MSG_SetSoftMinByFweq),
			(PPCWK_GFXCWK << 16) | (fweq & 0xffff),
			NUWW);
		if (wet) {
			dev_eww(smu->adev->dev, "Faiwed to set soft %s gfxcwk !\n",
						max ? "max" : "min");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UCWK_BIT) &&
	    (featuwe_mask & FEATUWE_DPM_UCWK_MASK)) {
		fweq = dpm_context->dpm_tabwes.ucwk_tabwe.dpm_wevews[wevew].vawue;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
			(max ? SMU_MSG_SetSoftMaxByFweq : SMU_MSG_SetSoftMinByFweq),
			(PPCWK_UCWK << 16) | (fweq & 0xffff),
			NUWW);
		if (wet) {
			dev_eww(smu->adev->dev, "Faiwed to set soft %s memcwk !\n",
						max ? "max" : "min");
			wetuwn wet;
		}
	}

	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_SOCCWK_BIT) &&
	    (featuwe_mask & FEATUWE_DPM_SOCCWK_MASK)) {
		fweq = dpm_context->dpm_tabwes.soc_tabwe.dpm_wevews[wevew].vawue;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
			(max ? SMU_MSG_SetSoftMaxByFweq : SMU_MSG_SetSoftMinByFweq),
			(PPCWK_SOCCWK << 16) | (fweq & 0xffff),
			NUWW);
		if (wet) {
			dev_eww(smu->adev->dev, "Faiwed to set soft %s soccwk !\n",
						max ? "max" : "min");
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int awctuwus_fowce_cwk_wevews(stwuct smu_context *smu,
			enum smu_cwk_type type, uint32_t mask)
{
	stwuct smu_11_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	stwuct smu_11_0_dpm_tabwe *singwe_dpm_tabwe = NUWW;
	uint32_t soft_min_wevew, soft_max_wevew;
	int wet = 0;

	if ((smu->smc_fw_vewsion >= 0x361200) &&
	    (smu->smc_fw_vewsion <= 0x361a00)) {
		dev_eww(smu->adev->dev, "Fowcing cwock wevew is not suppowted with "
		       "54.18 - 54.26(incwuded) SMU fiwmwawes\n");
		wetuwn -EOPNOTSUPP;
	}

	soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
	soft_max_wevew = mask ? (fws(mask) - 1) : 0;

	switch (type) {
	case SMU_SCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.gfx_tabwe);
		if (soft_max_wevew >= singwe_dpm_tabwe->count) {
			dev_eww(smu->adev->dev, "Cwock wevew specified %d is ovew max awwowed %d\n",
					soft_max_wevew, singwe_dpm_tabwe->count - 1);
			wet = -EINVAW;
			bweak;
		}

		wet = awctuwus_upwoad_dpm_wevew(smu,
						fawse,
						FEATUWE_DPM_GFXCWK_MASK,
						soft_min_wevew);
		if (wet) {
			dev_eww(smu->adev->dev, "Faiwed to upwoad boot wevew to wowest!\n");
			bweak;
		}

		wet = awctuwus_upwoad_dpm_wevew(smu,
						twue,
						FEATUWE_DPM_GFXCWK_MASK,
						soft_max_wevew);
		if (wet)
			dev_eww(smu->adev->dev, "Faiwed to upwoad dpm max wevew to highest!\n");

		bweak;

	case SMU_MCWK:
	case SMU_SOCCWK:
	case SMU_FCWK:
		/*
		 * Shouwd not awwive hewe since Awctuwus does not
		 * suppowt mcwk/soccwk/fcwk softmin/softmax settings
		 */
		wet = -EINVAW;
		bweak;

	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int awctuwus_get_thewmaw_tempewatuwe_wange(stwuct smu_context *smu,
						stwuct smu_tempewatuwe_wange *wange)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	stwuct smu_11_0_powewpway_tabwe *powewpway_tabwe =
				tabwe_context->powew_pway_tabwe;
	PPTabwe_t *pptabwe = smu->smu_tabwe.dwivew_pptabwe;

	if (!wange)
		wetuwn -EINVAW;

	memcpy(wange, &smu11_thewmaw_powicy[0], sizeof(stwuct smu_tempewatuwe_wange));

	wange->max = pptabwe->TedgeWimit *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->edge_emewgency_max = (pptabwe->TedgeWimit + CTF_OFFSET_EDGE) *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->hotspot_cwit_max = pptabwe->ThotspotWimit *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->hotspot_emewgency_max = (pptabwe->ThotspotWimit + CTF_OFFSET_HOTSPOT) *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->mem_cwit_max = pptabwe->TmemWimit *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->mem_emewgency_max = (pptabwe->TmemWimit + CTF_OFFSET_MEM)*
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->softwawe_shutdown_temp = powewpway_tabwe->softwawe_shutdown_temp;

	wetuwn 0;
}

static int awctuwus_wead_sensow(stwuct smu_context *smu,
				enum amd_pp_sensows sensow,
				void *data, uint32_t *size)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	PPTabwe_t *pptabwe = tabwe_context->dwivew_pptabwe;
	int wet = 0;

	if (amdgpu_was_intw_twiggewed())
		wetuwn 0;

	if (!data || !size)
		wetuwn -EINVAW;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_MAX_FAN_WPM:
		*(uint32_t *)data = pptabwe->FanMaximumWpm;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_MEM_WOAD:
		wet = awctuwus_get_smu_metwics_data(smu,
						    METWICS_AVEWAGE_MEMACTIVITY,
						    (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		wet = awctuwus_get_smu_metwics_data(smu,
						    METWICS_AVEWAGE_GFXACTIVITY,
						    (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_AVG_POWEW:
		wet = awctuwus_get_smu_metwics_data(smu,
						    METWICS_AVEWAGE_SOCKETPOWEW,
						    (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
		wet = awctuwus_get_smu_metwics_data(smu,
						    METWICS_TEMPEWATUWE_HOTSPOT,
						    (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_EDGE_TEMP:
		wet = awctuwus_get_smu_metwics_data(smu,
						    METWICS_TEMPEWATUWE_EDGE,
						    (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_MEM_TEMP:
		wet = awctuwus_get_smu_metwics_data(smu,
						    METWICS_TEMPEWATUWE_MEM,
						    (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		wet = awctuwus_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_UCWK, (uint32_t *)data);
		/* the output cwock fwequency in 10K unit */
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		wet = awctuwus_get_cuwwent_cwk_fweq_by_tabwe(smu, SMU_GFXCWK, (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDGFX:
		wet = smu_v11_0_get_gfx_vdd(smu, (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int awctuwus_set_fan_static_mode(stwuct smu_context *smu,
					uint32_t mode)
{
	stwuct amdgpu_device *adev = smu->adev;

	WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2_AWCT,
		     WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2_AWCT),
				   CG_FDO_CTWW2, TMIN, 0));
	WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2_AWCT,
		     WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2_AWCT),
				   CG_FDO_CTWW2, FDO_PWM_MODE, mode));

	wetuwn 0;
}

static int awctuwus_get_fan_speed_wpm(stwuct smu_context *smu,
				      uint32_t *speed)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t cwystaw_cwock_fweq = 2500;
	uint32_t tach_status;
	uint64_t tmp64;
	int wet = 0;

	if (!speed)
		wetuwn -EINVAW;

	switch (smu_v11_0_get_fan_contwow_mode(smu)) {
	case AMD_FAN_CTWW_AUTO:
		wet = awctuwus_get_smu_metwics_data(smu,
						    METWICS_CUWW_FANSPEED,
						    speed);
		bweak;
	defauwt:
		/*
		 * Fow pwe Sienna Cichwid ASICs, the 0 WPM may be not cowwectwy
		 * detected via wegistew wetwieving. To wowkawound this, we wiww
		 * wepowt the fan speed as 0 WPM if usew just wequested such.
		 */
		if ((smu->usew_dpm_pwofiwe.fwags & SMU_CUSTOM_FAN_SPEED_WPM)
		     && !smu->usew_dpm_pwofiwe.fan_speed_wpm) {
			*speed = 0;
			wetuwn 0;
		}

		tmp64 = (uint64_t)cwystaw_cwock_fweq * 60 * 10000;
		tach_status = WWEG32_SOC15(THM, 0, mmCG_TACH_STATUS_AWCT);
		if (tach_status) {
			do_div(tmp64, tach_status);
			*speed = (uint32_t)tmp64;
		} ewse {
			*speed = 0;
		}

		bweak;
	}

	wetuwn wet;
}

static int awctuwus_set_fan_speed_pwm(stwuct smu_context *smu,
				      uint32_t speed)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t duty100, duty;
	uint64_t tmp64;

	speed = min_t(uint32_t, speed, 255);

	duty100 = WEG_GET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW1_AWCT),
				CG_FDO_CTWW1, FMAX_DUTY100);
	if (!duty100)
		wetuwn -EINVAW;

	tmp64 = (uint64_t)speed * duty100;
	do_div(tmp64, 255);
	duty = (uint32_t)tmp64;

	WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW0_AWCT,
		     WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW0_AWCT),
				   CG_FDO_CTWW0, FDO_STATIC_DUTY, duty));

	wetuwn awctuwus_set_fan_static_mode(smu, FDO_PWM_MODE_STATIC);
}

static int awctuwus_set_fan_speed_wpm(stwuct smu_context *smu,
				      uint32_t speed)
{
	stwuct amdgpu_device *adev = smu->adev;
	/*
	 * cwystaw_cwock_fweq used fow fan speed wpm cawcuwation is
	 * awways 25Mhz. So, hawdcode it as 2500(in 10K unit).
	 */
	uint32_t cwystaw_cwock_fweq = 2500;
	uint32_t tach_pewiod;

	tach_pewiod = 60 * cwystaw_cwock_fweq * 10000 / (8 * speed);
	WWEG32_SOC15(THM, 0, mmCG_TACH_CTWW_AWCT,
		     WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_TACH_CTWW_AWCT),
				   CG_TACH_CTWW, TAWGET_PEWIOD,
				   tach_pewiod));

	wetuwn awctuwus_set_fan_static_mode(smu, FDO_PWM_MODE_STATIC_WPM);
}

static int awctuwus_get_fan_speed_pwm(stwuct smu_context *smu,
				      uint32_t *speed)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t duty100, duty;
	uint64_t tmp64;

	/*
	 * Fow pwe Sienna Cichwid ASICs, the 0 WPM may be not cowwectwy
	 * detected via wegistew wetwieving. To wowkawound this, we wiww
	 * wepowt the fan speed as 0 PWM if usew just wequested such.
	 */
	if ((smu->usew_dpm_pwofiwe.fwags & SMU_CUSTOM_FAN_SPEED_PWM)
	     && !smu->usew_dpm_pwofiwe.fan_speed_pwm) {
		*speed = 0;
		wetuwn 0;
	}

	duty100 = WEG_GET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW1_AWCT),
				CG_FDO_CTWW1, FMAX_DUTY100);
	duty = WEG_GET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_THEWMAW_STATUS_AWCT),
				CG_THEWMAW_STATUS, FDO_PWM_DUTY);

	if (duty100) {
		tmp64 = (uint64_t)duty * 255;
		do_div(tmp64, duty100);
		*speed = min_t(uint32_t, tmp64, 255);
	} ewse {
		*speed = 0;
	}

	wetuwn 0;
}

static int awctuwus_get_fan_pawametews(stwuct smu_context *smu)
{
	PPTabwe_t *pptabwe = smu->smu_tabwe.dwivew_pptabwe;

	smu->fan_max_wpm = pptabwe->FanMaximumWpm;

	wetuwn 0;
}

static int awctuwus_get_powew_wimit(stwuct smu_context *smu,
					uint32_t *cuwwent_powew_wimit,
					uint32_t *defauwt_powew_wimit,
					uint32_t *max_powew_wimit,
					uint32_t *min_powew_wimit)
{
	stwuct smu_11_0_powewpway_tabwe *powewpway_tabwe =
		(stwuct smu_11_0_powewpway_tabwe *)smu->smu_tabwe.powew_pway_tabwe;
	PPTabwe_t *pptabwe = smu->smu_tabwe.dwivew_pptabwe;
	uint32_t powew_wimit, od_pewcent_uppew, od_pewcent_wowew;

	if (smu_v11_0_get_cuwwent_powew_wimit(smu, &powew_wimit)) {
		/* the wast hope to figuwe out the ppt wimit */
		if (!pptabwe) {
			dev_eww(smu->adev->dev, "Cannot get PPT wimit due to pptabwe missing!");
			wetuwn -EINVAW;
		}
		powew_wimit =
			pptabwe->SocketPowewWimitAc[PPT_THWOTTWEW_PPT0];
	}

	if (cuwwent_powew_wimit)
		*cuwwent_powew_wimit = powew_wimit;
	if (defauwt_powew_wimit)
		*defauwt_powew_wimit = powew_wimit;

	if (smu->od_enabwed) {
		od_pewcent_uppew = we32_to_cpu(powewpway_tabwe->ovewdwive_tabwe.max[SMU_11_0_ODSETTING_POWEWPEWCENTAGE]);
		od_pewcent_wowew = we32_to_cpu(powewpway_tabwe->ovewdwive_tabwe.min[SMU_11_0_ODSETTING_POWEWPEWCENTAGE]);
	} ewse {
		od_pewcent_uppew = 0;
		od_pewcent_wowew = 100;
	}

	dev_dbg(smu->adev->dev, "od pewcent uppew:%d, od pewcent wowew:%d (defauwt powew: %d)\n",
							od_pewcent_uppew, od_pewcent_wowew, powew_wimit);

	if (max_powew_wimit) {
		*max_powew_wimit = powew_wimit * (100 + od_pewcent_uppew);
		*max_powew_wimit /= 100;
	}

	if (min_powew_wimit) {
		*min_powew_wimit = powew_wimit * (100 - od_pewcent_wowew);
		*min_powew_wimit /= 100;
	}

	wetuwn 0;
}

static int awctuwus_get_powew_pwofiwe_mode(stwuct smu_context *smu,
					   chaw *buf)
{
	DpmActivityMonitowCoeffInt_t activity_monitow;
	static const chaw *titwe[] = {
			"PWOFIWE_INDEX(NAME)",
			"CWOCK_TYPE(NAME)",
			"FPS",
			"UseWwcBusy",
			"MinActiveFweqType",
			"MinActiveFweq",
			"BoostewFweqType",
			"BoostewFweq",
			"PD_Data_wimit_c",
			"PD_Data_ewwow_coeff",
			"PD_Data_ewwow_wate_coeff"};
	uint32_t i, size = 0;
	int16_t wowkwoad_type = 0;
	int wesuwt = 0;

	if (!buf)
		wetuwn -EINVAW;

	if (smu->smc_fw_vewsion >= 0x360d00)
		size += sysfs_emit_at(buf, size, "%16s %s %s %s %s %s %s %s %s %s %s\n",
			titwe[0], titwe[1], titwe[2], titwe[3], titwe[4], titwe[5],
			titwe[6], titwe[7], titwe[8], titwe[9], titwe[10]);
	ewse
		size += sysfs_emit_at(buf, size, "%16s\n",
			titwe[0]);

	fow (i = 0; i <= PP_SMC_POWEW_PWOFIWE_CUSTOM; i++) {
		/*
		 * Conv PP_SMC_POWEW_PWOFIWE* to WOWKWOAD_PPWIB_*_BIT
		 * Not aww pwofiwe modes awe suppowted on awctuwus.
		 */
		wowkwoad_type = smu_cmn_to_asic_specific_index(smu,
							       CMN2ASIC_MAPPING_WOWKWOAD,
							       i);
		if (wowkwoad_type < 0)
			continue;

		if (smu->smc_fw_vewsion >= 0x360d00) {
			wesuwt = smu_cmn_update_tabwe(smu,
						  SMU_TABWE_ACTIVITY_MONITOW_COEFF,
						  wowkwoad_type,
						  (void *)(&activity_monitow),
						  fawse);
			if (wesuwt) {
				dev_eww(smu->adev->dev, "[%s] Faiwed to get activity monitow!", __func__);
				wetuwn wesuwt;
			}
		}

		size += sysfs_emit_at(buf, size, "%2d %14s%s\n",
			i, amdgpu_pp_pwofiwe_name[i], (i == smu->powew_pwofiwe_mode) ? "*" : " ");

		if (smu->smc_fw_vewsion >= 0x360d00) {
			size += sysfs_emit_at(buf, size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
				" ",
				0,
				"GFXCWK",
				activity_monitow.Gfx_FPS,
				activity_monitow.Gfx_UseWwcBusy,
				activity_monitow.Gfx_MinActiveFweqType,
				activity_monitow.Gfx_MinActiveFweq,
				activity_monitow.Gfx_BoostewFweqType,
				activity_monitow.Gfx_BoostewFweq,
				activity_monitow.Gfx_PD_Data_wimit_c,
				activity_monitow.Gfx_PD_Data_ewwow_coeff,
				activity_monitow.Gfx_PD_Data_ewwow_wate_coeff);

			size += sysfs_emit_at(buf, size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d %7d\n",
				" ",
				1,
				"UCWK",
				activity_monitow.Mem_FPS,
				activity_monitow.Mem_UseWwcBusy,
				activity_monitow.Mem_MinActiveFweqType,
				activity_monitow.Mem_MinActiveFweq,
				activity_monitow.Mem_BoostewFweqType,
				activity_monitow.Mem_BoostewFweq,
				activity_monitow.Mem_PD_Data_wimit_c,
				activity_monitow.Mem_PD_Data_ewwow_coeff,
				activity_monitow.Mem_PD_Data_ewwow_wate_coeff);
		}
	}

	wetuwn size;
}

static int awctuwus_set_powew_pwofiwe_mode(stwuct smu_context *smu,
					   wong *input,
					   uint32_t size)
{
	DpmActivityMonitowCoeffInt_t activity_monitow;
	int wowkwoad_type = 0;
	uint32_t pwofiwe_mode = input[size];
	int wet = 0;

	if (pwofiwe_mode > PP_SMC_POWEW_PWOFIWE_CUSTOM) {
		dev_eww(smu->adev->dev, "Invawid powew pwofiwe mode %d\n", pwofiwe_mode);
		wetuwn -EINVAW;
	}


	if ((pwofiwe_mode == PP_SMC_POWEW_PWOFIWE_CUSTOM) &&
	     (smu->smc_fw_vewsion >= 0x360d00)) {
		wet = smu_cmn_update_tabwe(smu,
				       SMU_TABWE_ACTIVITY_MONITOW_COEFF,
				       WOWKWOAD_PPWIB_CUSTOM_BIT,
				       (void *)(&activity_monitow),
				       fawse);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] Faiwed to get activity monitow!", __func__);
			wetuwn wet;
		}

		switch (input[0]) {
		case 0: /* Gfxcwk */
			activity_monitow.Gfx_FPS = input[1];
			activity_monitow.Gfx_UseWwcBusy = input[2];
			activity_monitow.Gfx_MinActiveFweqType = input[3];
			activity_monitow.Gfx_MinActiveFweq = input[4];
			activity_monitow.Gfx_BoostewFweqType = input[5];
			activity_monitow.Gfx_BoostewFweq = input[6];
			activity_monitow.Gfx_PD_Data_wimit_c = input[7];
			activity_monitow.Gfx_PD_Data_ewwow_coeff = input[8];
			activity_monitow.Gfx_PD_Data_ewwow_wate_coeff = input[9];
			bweak;
		case 1: /* Ucwk */
			activity_monitow.Mem_FPS = input[1];
			activity_monitow.Mem_UseWwcBusy = input[2];
			activity_monitow.Mem_MinActiveFweqType = input[3];
			activity_monitow.Mem_MinActiveFweq = input[4];
			activity_monitow.Mem_BoostewFweqType = input[5];
			activity_monitow.Mem_BoostewFweq = input[6];
			activity_monitow.Mem_PD_Data_wimit_c = input[7];
			activity_monitow.Mem_PD_Data_ewwow_coeff = input[8];
			activity_monitow.Mem_PD_Data_ewwow_wate_coeff = input[9];
			bweak;
		}

		wet = smu_cmn_update_tabwe(smu,
				       SMU_TABWE_ACTIVITY_MONITOW_COEFF,
				       WOWKWOAD_PPWIB_CUSTOM_BIT,
				       (void *)(&activity_monitow),
				       twue);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] Faiwed to set activity monitow!", __func__);
			wetuwn wet;
		}
	}

	/*
	 * Conv PP_SMC_POWEW_PWOFIWE* to WOWKWOAD_PPWIB_*_BIT
	 * Not aww pwofiwe modes awe suppowted on awctuwus.
	 */
	wowkwoad_type = smu_cmn_to_asic_specific_index(smu,
						       CMN2ASIC_MAPPING_WOWKWOAD,
						       pwofiwe_mode);
	if (wowkwoad_type < 0) {
		dev_dbg(smu->adev->dev, "Unsuppowted powew pwofiwe mode %d on awctuwus\n", pwofiwe_mode);
		wetuwn -EINVAW;
	}

	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					  SMU_MSG_SetWowkwoadMask,
					  1 << wowkwoad_type,
					  NUWW);
	if (wet) {
		dev_eww(smu->adev->dev, "Faiw to set wowkwoad type %d\n", wowkwoad_type);
		wetuwn wet;
	}

	smu->powew_pwofiwe_mode = pwofiwe_mode;

	wetuwn 0;
}

static int awctuwus_set_pewfowmance_wevew(stwuct smu_context *smu,
					  enum amd_dpm_fowced_wevew wevew)
{
	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
	case AMD_DPM_FOWCED_WEVEW_WOW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		if ((smu->smc_fw_vewsion >= 0x361200) &&
		    (smu->smc_fw_vewsion <= 0x361a00)) {
			dev_eww(smu->adev->dev, "Fowcing cwock wevew is not suppowted with "
			       "54.18 - 54.26(incwuded) SMU fiwmwawes\n");
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn smu_v11_0_set_pewfowmance_wevew(smu, wevew);
}

static void awctuwus_dump_pptabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	PPTabwe_t *pptabwe = tabwe_context->dwivew_pptabwe;
	int i;

	dev_info(smu->adev->dev, "Dumped PPTabwe:\n");

	dev_info(smu->adev->dev, "Vewsion = 0x%08x\n", pptabwe->Vewsion);

	dev_info(smu->adev->dev, "FeatuwesToWun[0] = 0x%08x\n", pptabwe->FeatuwesToWun[0]);
	dev_info(smu->adev->dev, "FeatuwesToWun[1] = 0x%08x\n", pptabwe->FeatuwesToWun[1]);

	fow (i = 0; i < PPT_THWOTTWEW_COUNT; i++) {
		dev_info(smu->adev->dev, "SocketPowewWimitAc[%d] = %d\n", i, pptabwe->SocketPowewWimitAc[i]);
		dev_info(smu->adev->dev, "SocketPowewWimitAcTau[%d] = %d\n", i, pptabwe->SocketPowewWimitAcTau[i]);
	}

	dev_info(smu->adev->dev, "TdcWimitSoc = %d\n", pptabwe->TdcWimitSoc);
	dev_info(smu->adev->dev, "TdcWimitSocTau = %d\n", pptabwe->TdcWimitSocTau);
	dev_info(smu->adev->dev, "TdcWimitGfx = %d\n", pptabwe->TdcWimitGfx);
	dev_info(smu->adev->dev, "TdcWimitGfxTau = %d\n", pptabwe->TdcWimitGfxTau);

	dev_info(smu->adev->dev, "TedgeWimit = %d\n", pptabwe->TedgeWimit);
	dev_info(smu->adev->dev, "ThotspotWimit = %d\n", pptabwe->ThotspotWimit);
	dev_info(smu->adev->dev, "TmemWimit = %d\n", pptabwe->TmemWimit);
	dev_info(smu->adev->dev, "Tvw_gfxWimit = %d\n", pptabwe->Tvw_gfxWimit);
	dev_info(smu->adev->dev, "Tvw_memWimit = %d\n", pptabwe->Tvw_memWimit);
	dev_info(smu->adev->dev, "Tvw_socWimit = %d\n", pptabwe->Tvw_socWimit);
	dev_info(smu->adev->dev, "FitWimit = %d\n", pptabwe->FitWimit);

	dev_info(smu->adev->dev, "PpmPowewWimit = %d\n", pptabwe->PpmPowewWimit);
	dev_info(smu->adev->dev, "PpmTempewatuweThweshowd = %d\n", pptabwe->PpmTempewatuweThweshowd);

	dev_info(smu->adev->dev, "ThwottwewContwowMask = %d\n", pptabwe->ThwottwewContwowMask);

	dev_info(smu->adev->dev, "UwvVowtageOffsetGfx = %d\n", pptabwe->UwvVowtageOffsetGfx);
	dev_info(smu->adev->dev, "UwvPadding = 0x%08x\n", pptabwe->UwvPadding);

	dev_info(smu->adev->dev, "UwvGfxcwkBypass = %d\n", pptabwe->UwvGfxcwkBypass);
	dev_info(smu->adev->dev, "Padding234[0] = 0x%02x\n", pptabwe->Padding234[0]);
	dev_info(smu->adev->dev, "Padding234[1] = 0x%02x\n", pptabwe->Padding234[1]);
	dev_info(smu->adev->dev, "Padding234[2] = 0x%02x\n", pptabwe->Padding234[2]);

	dev_info(smu->adev->dev, "MinVowtageGfx = %d\n", pptabwe->MinVowtageGfx);
	dev_info(smu->adev->dev, "MinVowtageSoc = %d\n", pptabwe->MinVowtageSoc);
	dev_info(smu->adev->dev, "MaxVowtageGfx = %d\n", pptabwe->MaxVowtageGfx);
	dev_info(smu->adev->dev, "MaxVowtageSoc = %d\n", pptabwe->MaxVowtageSoc);

	dev_info(smu->adev->dev, "WoadWineWesistanceGfx = %d\n", pptabwe->WoadWineWesistanceGfx);
	dev_info(smu->adev->dev, "WoadWineWesistanceSoc = %d\n", pptabwe->WoadWineWesistanceSoc);

	dev_info(smu->adev->dev, "[PPCWK_GFXCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].SsCuwve.c,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].SsFmin,
			pptabwe->DpmDescwiptow[PPCWK_GFXCWK].Padding16);

	dev_info(smu->adev->dev, "[PPCWK_VCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptabwe->DpmDescwiptow[PPCWK_VCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].SsCuwve.c,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].SsFmin,
			pptabwe->DpmDescwiptow[PPCWK_VCWK].Padding16);

	dev_info(smu->adev->dev, "[PPCWK_DCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptabwe->DpmDescwiptow[PPCWK_DCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].SsCuwve.c,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].SsFmin,
			pptabwe->DpmDescwiptow[PPCWK_DCWK].Padding16);

	dev_info(smu->adev->dev, "[PPCWK_SOCCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].SsCuwve.c,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].SsFmin,
			pptabwe->DpmDescwiptow[PPCWK_SOCCWK].Padding16);

	dev_info(smu->adev->dev, "[PPCWK_UCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptabwe->DpmDescwiptow[PPCWK_UCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].SsCuwve.c,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].SsFmin,
			pptabwe->DpmDescwiptow[PPCWK_UCWK].Padding16);

	dev_info(smu->adev->dev, "[PPCWK_FCWK]\n"
			"  .VowtageMode          = 0x%02x\n"
			"  .SnapToDiscwete       = 0x%02x\n"
			"  .NumDiscweteWevews    = 0x%02x\n"
			"  .padding              = 0x%02x\n"
			"  .ConvewsionToAvfsCwk{m = 0x%08x b = 0x%08x}\n"
			"  .SsCuwve            {a = 0x%08x b = 0x%08x c = 0x%08x}\n"
			"  .SsFmin               = 0x%04x\n"
			"  .Padding_16           = 0x%04x\n",
			pptabwe->DpmDescwiptow[PPCWK_FCWK].VowtageMode,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].SnapToDiscwete,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].NumDiscweteWevews,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].padding,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].ConvewsionToAvfsCwk.m,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].ConvewsionToAvfsCwk.b,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].SsCuwve.a,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].SsCuwve.b,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].SsCuwve.c,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].SsFmin,
			pptabwe->DpmDescwiptow[PPCWK_FCWK].Padding16);


	dev_info(smu->adev->dev, "FweqTabweGfx\n");
	fow (i = 0; i < NUM_GFXCWK_DPM_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptabwe->FweqTabweGfx[i]);

	dev_info(smu->adev->dev, "FweqTabweVcwk\n");
	fow (i = 0; i < NUM_VCWK_DPM_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptabwe->FweqTabweVcwk[i]);

	dev_info(smu->adev->dev, "FweqTabweDcwk\n");
	fow (i = 0; i < NUM_DCWK_DPM_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptabwe->FweqTabweDcwk[i]);

	dev_info(smu->adev->dev, "FweqTabweSoccwk\n");
	fow (i = 0; i < NUM_SOCCWK_DPM_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptabwe->FweqTabweSoccwk[i]);

	dev_info(smu->adev->dev, "FweqTabweUcwk\n");
	fow (i = 0; i < NUM_UCWK_DPM_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptabwe->FweqTabweUcwk[i]);

	dev_info(smu->adev->dev, "FweqTabweFcwk\n");
	fow (i = 0; i < NUM_FCWK_DPM_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%02d] = %d\n", i, pptabwe->FweqTabweFcwk[i]);

	dev_info(smu->adev->dev, "Mp0cwkFweq\n");
	fow (i = 0; i < NUM_MP0CWK_DPM_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptabwe->Mp0cwkFweq[i]);

	dev_info(smu->adev->dev, "Mp0DpmVowtage\n");
	fow (i = 0; i < NUM_MP0CWK_DPM_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptabwe->Mp0DpmVowtage[i]);

	dev_info(smu->adev->dev, "GfxcwkFidwe = 0x%x\n", pptabwe->GfxcwkFidwe);
	dev_info(smu->adev->dev, "GfxcwkSwewWate = 0x%x\n", pptabwe->GfxcwkSwewWate);
	dev_info(smu->adev->dev, "Padding567[0] = 0x%x\n", pptabwe->Padding567[0]);
	dev_info(smu->adev->dev, "Padding567[1] = 0x%x\n", pptabwe->Padding567[1]);
	dev_info(smu->adev->dev, "Padding567[2] = 0x%x\n", pptabwe->Padding567[2]);
	dev_info(smu->adev->dev, "Padding567[3] = 0x%x\n", pptabwe->Padding567[3]);
	dev_info(smu->adev->dev, "GfxcwkDsMaxFweq = %d\n", pptabwe->GfxcwkDsMaxFweq);
	dev_info(smu->adev->dev, "GfxcwkSouwce = 0x%x\n", pptabwe->GfxcwkSouwce);
	dev_info(smu->adev->dev, "Padding456 = 0x%x\n", pptabwe->Padding456);

	dev_info(smu->adev->dev, "EnabweTdpm = %d\n", pptabwe->EnabweTdpm);
	dev_info(smu->adev->dev, "TdpmHighHystTempewatuwe = %d\n", pptabwe->TdpmHighHystTempewatuwe);
	dev_info(smu->adev->dev, "TdpmWowHystTempewatuwe = %d\n", pptabwe->TdpmWowHystTempewatuwe);
	dev_info(smu->adev->dev, "GfxcwkFweqHighTempWimit = %d\n", pptabwe->GfxcwkFweqHighTempWimit);

	dev_info(smu->adev->dev, "FanStopTemp = %d\n", pptabwe->FanStopTemp);
	dev_info(smu->adev->dev, "FanStawtTemp = %d\n", pptabwe->FanStawtTemp);

	dev_info(smu->adev->dev, "FanGainEdge = %d\n", pptabwe->FanGainEdge);
	dev_info(smu->adev->dev, "FanGainHotspot = %d\n", pptabwe->FanGainHotspot);
	dev_info(smu->adev->dev, "FanGainVwGfx = %d\n", pptabwe->FanGainVwGfx);
	dev_info(smu->adev->dev, "FanGainVwSoc = %d\n", pptabwe->FanGainVwSoc);
	dev_info(smu->adev->dev, "FanGainVwMem = %d\n", pptabwe->FanGainVwMem);
	dev_info(smu->adev->dev, "FanGainHbm = %d\n", pptabwe->FanGainHbm);

	dev_info(smu->adev->dev, "FanPwmMin = %d\n", pptabwe->FanPwmMin);
	dev_info(smu->adev->dev, "FanAcousticWimitWpm = %d\n", pptabwe->FanAcousticWimitWpm);
	dev_info(smu->adev->dev, "FanThwottwingWpm = %d\n", pptabwe->FanThwottwingWpm);
	dev_info(smu->adev->dev, "FanMaximumWpm = %d\n", pptabwe->FanMaximumWpm);
	dev_info(smu->adev->dev, "FanTawgetTempewatuwe = %d\n", pptabwe->FanTawgetTempewatuwe);
	dev_info(smu->adev->dev, "FanTawgetGfxcwk = %d\n", pptabwe->FanTawgetGfxcwk);
	dev_info(smu->adev->dev, "FanZewoWpmEnabwe = %d\n", pptabwe->FanZewoWpmEnabwe);
	dev_info(smu->adev->dev, "FanTachEdgePewWev = %d\n", pptabwe->FanTachEdgePewWev);
	dev_info(smu->adev->dev, "FanTempInputSewect = %d\n", pptabwe->FanTempInputSewect);

	dev_info(smu->adev->dev, "FuzzyFan_EwwowSetDewta = %d\n", pptabwe->FuzzyFan_EwwowSetDewta);
	dev_info(smu->adev->dev, "FuzzyFan_EwwowWateSetDewta = %d\n", pptabwe->FuzzyFan_EwwowWateSetDewta);
	dev_info(smu->adev->dev, "FuzzyFan_PwmSetDewta = %d\n", pptabwe->FuzzyFan_PwmSetDewta);
	dev_info(smu->adev->dev, "FuzzyFan_Wesewved = %d\n", pptabwe->FuzzyFan_Wesewved);

	dev_info(smu->adev->dev, "OvewwideAvfsGb[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->OvewwideAvfsGb[AVFS_VOWTAGE_GFX]);
	dev_info(smu->adev->dev, "OvewwideAvfsGb[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->OvewwideAvfsGb[AVFS_VOWTAGE_SOC]);
	dev_info(smu->adev->dev, "Padding8_Avfs[0] = %d\n", pptabwe->Padding8_Avfs[0]);
	dev_info(smu->adev->dev, "Padding8_Avfs[1] = %d\n", pptabwe->Padding8_Avfs[1]);

	dev_info(smu->adev->dev, "dBtcGbGfxPww{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->dBtcGbGfxPww.a,
			pptabwe->dBtcGbGfxPww.b,
			pptabwe->dBtcGbGfxPww.c);
	dev_info(smu->adev->dev, "dBtcGbGfxAfww{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->dBtcGbGfxAfww.a,
			pptabwe->dBtcGbGfxAfww.b,
			pptabwe->dBtcGbGfxAfww.c);
	dev_info(smu->adev->dev, "dBtcGbSoc{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->dBtcGbSoc.a,
			pptabwe->dBtcGbSoc.b,
			pptabwe->dBtcGbSoc.c);

	dev_info(smu->adev->dev, "qAgingGb[AVFS_VOWTAGE_GFX]{m = 0x%x b = 0x%x}\n",
			pptabwe->qAgingGb[AVFS_VOWTAGE_GFX].m,
			pptabwe->qAgingGb[AVFS_VOWTAGE_GFX].b);
	dev_info(smu->adev->dev, "qAgingGb[AVFS_VOWTAGE_SOC]{m = 0x%x b = 0x%x}\n",
			pptabwe->qAgingGb[AVFS_VOWTAGE_SOC].m,
			pptabwe->qAgingGb[AVFS_VOWTAGE_SOC].b);

	dev_info(smu->adev->dev, "qStaticVowtageOffset[AVFS_VOWTAGE_GFX]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_GFX].a,
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_GFX].b,
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_GFX].c);
	dev_info(smu->adev->dev, "qStaticVowtageOffset[AVFS_VOWTAGE_SOC]{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_SOC].a,
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_SOC].b,
			pptabwe->qStaticVowtageOffset[AVFS_VOWTAGE_SOC].c);

	dev_info(smu->adev->dev, "DcTow[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcTow[AVFS_VOWTAGE_GFX]);
	dev_info(smu->adev->dev, "DcTow[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcTow[AVFS_VOWTAGE_SOC]);

	dev_info(smu->adev->dev, "DcBtcEnabwed[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcBtcEnabwed[AVFS_VOWTAGE_GFX]);
	dev_info(smu->adev->dev, "DcBtcEnabwed[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcBtcEnabwed[AVFS_VOWTAGE_SOC]);
	dev_info(smu->adev->dev, "Padding8_GfxBtc[0] = 0x%x\n", pptabwe->Padding8_GfxBtc[0]);
	dev_info(smu->adev->dev, "Padding8_GfxBtc[1] = 0x%x\n", pptabwe->Padding8_GfxBtc[1]);

	dev_info(smu->adev->dev, "DcBtcMin[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcBtcMin[AVFS_VOWTAGE_GFX]);
	dev_info(smu->adev->dev, "DcBtcMin[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcBtcMin[AVFS_VOWTAGE_SOC]);
	dev_info(smu->adev->dev, "DcBtcMax[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcBtcMax[AVFS_VOWTAGE_GFX]);
	dev_info(smu->adev->dev, "DcBtcMax[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcBtcMax[AVFS_VOWTAGE_SOC]);

	dev_info(smu->adev->dev, "DcBtcGb[AVFS_VOWTAGE_GFX] = 0x%x\n", pptabwe->DcBtcGb[AVFS_VOWTAGE_GFX]);
	dev_info(smu->adev->dev, "DcBtcGb[AVFS_VOWTAGE_SOC] = 0x%x\n", pptabwe->DcBtcGb[AVFS_VOWTAGE_SOC]);

	dev_info(smu->adev->dev, "XgmiDpmPstates\n");
	fow (i = 0; i < NUM_XGMI_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptabwe->XgmiDpmPstates[i]);
	dev_info(smu->adev->dev, "XgmiDpmSpawe[0] = 0x%02x\n", pptabwe->XgmiDpmSpawe[0]);
	dev_info(smu->adev->dev, "XgmiDpmSpawe[1] = 0x%02x\n", pptabwe->XgmiDpmSpawe[1]);

	dev_info(smu->adev->dev, "VDDGFX_TVmin = %d\n", pptabwe->VDDGFX_TVmin);
	dev_info(smu->adev->dev, "VDDSOC_TVmin = %d\n", pptabwe->VDDSOC_TVmin);
	dev_info(smu->adev->dev, "VDDGFX_Vmin_HiTemp = %d\n", pptabwe->VDDGFX_Vmin_HiTemp);
	dev_info(smu->adev->dev, "VDDGFX_Vmin_WoTemp = %d\n", pptabwe->VDDGFX_Vmin_WoTemp);
	dev_info(smu->adev->dev, "VDDSOC_Vmin_HiTemp = %d\n", pptabwe->VDDSOC_Vmin_HiTemp);
	dev_info(smu->adev->dev, "VDDSOC_Vmin_WoTemp = %d\n", pptabwe->VDDSOC_Vmin_WoTemp);
	dev_info(smu->adev->dev, "VDDGFX_TVminHystewsis = %d\n", pptabwe->VDDGFX_TVminHystewsis);
	dev_info(smu->adev->dev, "VDDSOC_TVminHystewsis = %d\n", pptabwe->VDDSOC_TVminHystewsis);

	dev_info(smu->adev->dev, "DebugOvewwides = 0x%x\n", pptabwe->DebugOvewwides);
	dev_info(smu->adev->dev, "WesewvedEquation0{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->WesewvedEquation0.a,
			pptabwe->WesewvedEquation0.b,
			pptabwe->WesewvedEquation0.c);
	dev_info(smu->adev->dev, "WesewvedEquation1{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->WesewvedEquation1.a,
			pptabwe->WesewvedEquation1.b,
			pptabwe->WesewvedEquation1.c);
	dev_info(smu->adev->dev, "WesewvedEquation2{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->WesewvedEquation2.a,
			pptabwe->WesewvedEquation2.b,
			pptabwe->WesewvedEquation2.c);
	dev_info(smu->adev->dev, "WesewvedEquation3{a = 0x%x b = 0x%x c = 0x%x}\n",
			pptabwe->WesewvedEquation3.a,
			pptabwe->WesewvedEquation3.b,
			pptabwe->WesewvedEquation3.c);

	dev_info(smu->adev->dev, "MinVowtageUwvGfx = %d\n", pptabwe->MinVowtageUwvGfx);
	dev_info(smu->adev->dev, "PaddingUwv = %d\n", pptabwe->PaddingUwv);

	dev_info(smu->adev->dev, "TotawPowewConfig = %d\n", pptabwe->TotawPowewConfig);
	dev_info(smu->adev->dev, "TotawPowewSpawe1 = %d\n", pptabwe->TotawPowewSpawe1);
	dev_info(smu->adev->dev, "TotawPowewSpawe2 = %d\n", pptabwe->TotawPowewSpawe2);

	dev_info(smu->adev->dev, "PccThweshowdWow = %d\n", pptabwe->PccThweshowdWow);
	dev_info(smu->adev->dev, "PccThweshowdHigh = %d\n", pptabwe->PccThweshowdHigh);

	dev_info(smu->adev->dev, "Boawd Pawametews:\n");
	dev_info(smu->adev->dev, "MaxVowtageStepGfx = 0x%x\n", pptabwe->MaxVowtageStepGfx);
	dev_info(smu->adev->dev, "MaxVowtageStepSoc = 0x%x\n", pptabwe->MaxVowtageStepSoc);

	dev_info(smu->adev->dev, "VddGfxVwMapping = 0x%x\n", pptabwe->VddGfxVwMapping);
	dev_info(smu->adev->dev, "VddSocVwMapping = 0x%x\n", pptabwe->VddSocVwMapping);
	dev_info(smu->adev->dev, "VddMemVwMapping = 0x%x\n", pptabwe->VddMemVwMapping);
	dev_info(smu->adev->dev, "BoawdVwMapping = 0x%x\n", pptabwe->BoawdVwMapping);

	dev_info(smu->adev->dev, "GfxUwvPhaseSheddingMask = 0x%x\n", pptabwe->GfxUwvPhaseSheddingMask);
	dev_info(smu->adev->dev, "ExtewnawSensowPwesent = 0x%x\n", pptabwe->ExtewnawSensowPwesent);

	dev_info(smu->adev->dev, "GfxMaxCuwwent = 0x%x\n", pptabwe->GfxMaxCuwwent);
	dev_info(smu->adev->dev, "GfxOffset = 0x%x\n", pptabwe->GfxOffset);
	dev_info(smu->adev->dev, "Padding_TewemetwyGfx = 0x%x\n", pptabwe->Padding_TewemetwyGfx);

	dev_info(smu->adev->dev, "SocMaxCuwwent = 0x%x\n", pptabwe->SocMaxCuwwent);
	dev_info(smu->adev->dev, "SocOffset = 0x%x\n", pptabwe->SocOffset);
	dev_info(smu->adev->dev, "Padding_TewemetwySoc = 0x%x\n", pptabwe->Padding_TewemetwySoc);

	dev_info(smu->adev->dev, "MemMaxCuwwent = 0x%x\n", pptabwe->MemMaxCuwwent);
	dev_info(smu->adev->dev, "MemOffset = 0x%x\n", pptabwe->MemOffset);
	dev_info(smu->adev->dev, "Padding_TewemetwyMem = 0x%x\n", pptabwe->Padding_TewemetwyMem);

	dev_info(smu->adev->dev, "BoawdMaxCuwwent = 0x%x\n", pptabwe->BoawdMaxCuwwent);
	dev_info(smu->adev->dev, "BoawdOffset = 0x%x\n", pptabwe->BoawdOffset);
	dev_info(smu->adev->dev, "Padding_TewemetwyBoawdInput = 0x%x\n", pptabwe->Padding_TewemetwyBoawdInput);

	dev_info(smu->adev->dev, "VW0HotGpio = %d\n", pptabwe->VW0HotGpio);
	dev_info(smu->adev->dev, "VW0HotPowawity = %d\n", pptabwe->VW0HotPowawity);
	dev_info(smu->adev->dev, "VW1HotGpio = %d\n", pptabwe->VW1HotGpio);
	dev_info(smu->adev->dev, "VW1HotPowawity = %d\n", pptabwe->VW1HotPowawity);

	dev_info(smu->adev->dev, "PwwGfxcwkSpweadEnabwed = %d\n", pptabwe->PwwGfxcwkSpweadEnabwed);
	dev_info(smu->adev->dev, "PwwGfxcwkSpweadPewcent = %d\n", pptabwe->PwwGfxcwkSpweadPewcent);
	dev_info(smu->adev->dev, "PwwGfxcwkSpweadFweq = %d\n", pptabwe->PwwGfxcwkSpweadFweq);

	dev_info(smu->adev->dev, "UcwkSpweadEnabwed = %d\n", pptabwe->UcwkSpweadEnabwed);
	dev_info(smu->adev->dev, "UcwkSpweadPewcent = %d\n", pptabwe->UcwkSpweadPewcent);
	dev_info(smu->adev->dev, "UcwkSpweadFweq = %d\n", pptabwe->UcwkSpweadFweq);

	dev_info(smu->adev->dev, "FcwkSpweadEnabwed = %d\n", pptabwe->FcwkSpweadEnabwed);
	dev_info(smu->adev->dev, "FcwkSpweadPewcent = %d\n", pptabwe->FcwkSpweadPewcent);
	dev_info(smu->adev->dev, "FcwkSpweadFweq = %d\n", pptabwe->FcwkSpweadFweq);

	dev_info(smu->adev->dev, "FwwGfxcwkSpweadEnabwed = %d\n", pptabwe->FwwGfxcwkSpweadEnabwed);
	dev_info(smu->adev->dev, "FwwGfxcwkSpweadPewcent = %d\n", pptabwe->FwwGfxcwkSpweadPewcent);
	dev_info(smu->adev->dev, "FwwGfxcwkSpweadFweq = %d\n", pptabwe->FwwGfxcwkSpweadFweq);

	fow (i = 0; i < NUM_I2C_CONTWOWWEWS; i++) {
		dev_info(smu->adev->dev, "I2cContwowwews[%d]:\n", i);
		dev_info(smu->adev->dev, "                   .Enabwed = %d\n",
				pptabwe->I2cContwowwews[i].Enabwed);
		dev_info(smu->adev->dev, "                   .SwaveAddwess = 0x%x\n",
				pptabwe->I2cContwowwews[i].SwaveAddwess);
		dev_info(smu->adev->dev, "                   .ContwowwewPowt = %d\n",
				pptabwe->I2cContwowwews[i].ContwowwewPowt);
		dev_info(smu->adev->dev, "                   .ContwowwewName = %d\n",
				pptabwe->I2cContwowwews[i].ContwowwewName);
		dev_info(smu->adev->dev, "                   .ThewmawThwottwew = %d\n",
				pptabwe->I2cContwowwews[i].ThewmawThwottew);
		dev_info(smu->adev->dev, "                   .I2cPwotocow = %d\n",
				pptabwe->I2cContwowwews[i].I2cPwotocow);
		dev_info(smu->adev->dev, "                   .Speed = %d\n",
				pptabwe->I2cContwowwews[i].Speed);
	}

	dev_info(smu->adev->dev, "MemowyChannewEnabwed = %d\n", pptabwe->MemowyChannewEnabwed);
	dev_info(smu->adev->dev, "DwamBitWidth = %d\n", pptabwe->DwamBitWidth);

	dev_info(smu->adev->dev, "TotawBoawdPowew = %d\n", pptabwe->TotawBoawdPowew);

	dev_info(smu->adev->dev, "XgmiWinkSpeed\n");
	fow (i = 0; i < NUM_XGMI_PSTATE_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptabwe->XgmiWinkSpeed[i]);
	dev_info(smu->adev->dev, "XgmiWinkWidth\n");
	fow (i = 0; i < NUM_XGMI_PSTATE_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptabwe->XgmiWinkWidth[i]);
	dev_info(smu->adev->dev, "XgmiFcwkFweq\n");
	fow (i = 0; i < NUM_XGMI_PSTATE_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptabwe->XgmiFcwkFweq[i]);
	dev_info(smu->adev->dev, "XgmiSocVowtage\n");
	fow (i = 0; i < NUM_XGMI_PSTATE_WEVEWS; i++)
		dev_info(smu->adev->dev, "  .[%d] = %d\n", i, pptabwe->XgmiSocVowtage[i]);

}

static boow awctuwus_is_dpm_wunning(stwuct smu_context *smu)
{
	int wet = 0;
	uint64_t featuwe_enabwed;

	wet = smu_cmn_get_enabwed_mask(smu, &featuwe_enabwed);
	if (wet)
		wetuwn fawse;

	wetuwn !!(featuwe_enabwed & SMC_DPM_FEATUWE);
}

static int awctuwus_dpm_set_vcn_enabwe(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0;

	if (enabwe) {
		if (!smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_VCN_DPM_BIT)) {
			wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_VCN_DPM_BIT, 1);
			if (wet) {
				dev_eww(smu->adev->dev, "[EnabweVCNDPM] faiwed!\n");
				wetuwn wet;
			}
		}
	} ewse {
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_VCN_DPM_BIT)) {
			wet = smu_cmn_featuwe_set_enabwed(smu, SMU_FEATUWE_VCN_DPM_BIT, 0);
			if (wet) {
				dev_eww(smu->adev->dev, "[DisabweVCNDPM] faiwed!\n");
				wetuwn wet;
			}
		}
	}

	wetuwn wet;
}

static int awctuwus_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
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
				cmd->Cmd = I2C_CMD_WWITE;
				cmd->WegistewAddw = msg[i].buf[j];
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
	w = smu_cmn_update_tabwe(smu, SMU_TABWE_I2C_COMMANDS, 0, weq, twue);
	if (w)
		goto faiw;

	fow (c = i = 0; i < num_msgs; i++) {
		if (!(msg[i].fwags & I2C_M_WD)) {
			c += msg[i].wen;
			continue;
		}
		fow (j = 0; j < msg[i].wen; j++, c++) {
			SwI2cCmd_t *cmd = &wes->SwI2cCmds[c];

			msg[i].buf[j] = cmd->Data;
		}
	}
	w = num_msgs;
faiw:
	mutex_unwock(&adev->pm.mutex);
	kfwee(weq);
	wetuwn w;
}

static u32 awctuwus_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}


static const stwuct i2c_awgowithm awctuwus_i2c_awgo = {
	.mastew_xfew = awctuwus_i2c_xfew,
	.functionawity = awctuwus_i2c_func,
};


static const stwuct i2c_adaptew_quiwks awctuwus_i2c_contwow_quiwks = {
	.fwags = I2C_AQ_COMB | I2C_AQ_COMB_SAME_ADDW | I2C_AQ_NO_ZEWO_WEN,
	.max_wead_wen  = MAX_SW_I2C_COMMANDS,
	.max_wwite_wen = MAX_SW_I2C_COMMANDS,
	.max_comb_1st_msg_wen = 2,
	.max_comb_2nd_msg_wen = MAX_SW_I2C_COMMANDS - 2,
};

static int awctuwus_i2c_contwow_init(stwuct smu_context *smu)
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
		contwow->cwass = I2C_CWASS_HWMON;
		contwow->dev.pawent = &adev->pdev->dev;
		contwow->awgo = &awctuwus_i2c_awgo;
		contwow->quiwks = &awctuwus_i2c_contwow_quiwks;
		snpwintf(contwow->name, sizeof(contwow->name), "AMDGPU SMU %d", i);
		i2c_set_adapdata(contwow, smu_i2c);

		wes = i2c_add_adaptew(contwow);
		if (wes) {
			DWM_EWWOW("Faiwed to wegistew hw i2c, eww: %d\n", wes);
			goto Out_eww;
		}
	}

	adev->pm.was_eepwom_i2c_bus = &adev->pm.smu_i2c[0].adaptew;
	adev->pm.fwu_eepwom_i2c_bus = &adev->pm.smu_i2c[1].adaptew;

	wetuwn 0;
Out_eww:
	fow ( ; i >= 0; i--) {
		stwuct amdgpu_smu_i2c_bus *smu_i2c = &adev->pm.smu_i2c[i];
		stwuct i2c_adaptew *contwow = &smu_i2c->adaptew;

		i2c_dew_adaptew(contwow);
	}
	wetuwn wes;
}

static void awctuwus_i2c_contwow_fini(stwuct smu_context *smu)
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

static void awctuwus_get_unique_id(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t top32 = 0, bottom32 = 0;
	uint64_t id;

	/* PPSMC_MSG_WeadSewiaw* is suppowted by 54.23.0 and onwawds */
	if (smu->smc_fw_vewsion < 0x361700) {
		dev_wawn(adev->dev, "WeadSewiaw is onwy suppowted by PMFW 54.23.0 and onwawds\n");
		wetuwn;
	}

	/* Get the SN to tuwn into a Unique ID */
	smu_cmn_send_smc_msg(smu, SMU_MSG_WeadSewiawNumTop32, &top32);
	smu_cmn_send_smc_msg(smu, SMU_MSG_WeadSewiawNumBottom32, &bottom32);

	id = ((uint64_t)bottom32 << 32) | top32;
	adev->unique_id = id;
}

static int awctuwus_set_df_cstate(stwuct smu_context *smu,
				  enum pp_df_cstate state)
{
	stwuct amdgpu_device *adev = smu->adev;

	/*
	 * Awctuwus does not need the cstate disabwement
	 * pwewequisite fow gpu weset.
	 */
	if (amdgpu_in_weset(adev) || adev->in_suspend)
		wetuwn 0;

	/* PPSMC_MSG_DFCstateContwow is suppowted by 54.15.0 and onwawds */
	if (smu->smc_fw_vewsion < 0x360F00) {
		dev_eww(smu->adev->dev, "DFCstateContwow is onwy suppowted by PMFW 54.15.0 and onwawds\n");
		wetuwn -EINVAW;
	}

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_DFCstateContwow, state, NUWW);
}

static int awctuwus_sewect_xgmi_pwpd_powicy(stwuct smu_context *smu,
					    enum pp_xgmi_pwpd_mode mode)
{
	/* PPSMC_MSG_GmiPwwDnContwow is suppowted by 54.23.0 and onwawds */
	if (smu->smc_fw_vewsion < 0x00361700) {
		dev_eww(smu->adev->dev, "XGMI powew down contwow is onwy suppowted by PMFW 54.23.0 and onwawds\n");
		wetuwn -EINVAW;
	}

	if (mode == XGMI_PWPD_DEFAUWT)
		wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
						   SMU_MSG_GmiPwwDnContwow,
						   1, NUWW);
	ewse if (mode == XGMI_PWPD_DISAWWOW)
		wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
						   SMU_MSG_GmiPwwDnContwow,
						   0, NUWW);
	ewse
		wetuwn -EINVAW;
}

static const stwuct thwottwing_wogging_wabew {
	uint32_t featuwe_mask;
	const chaw *wabew;
} wogging_wabew[] = {
	{(1U << THWOTTWEW_TEMP_HOTSPOT_BIT), "GPU"},
	{(1U << THWOTTWEW_TEMP_MEM_BIT), "HBM"},
	{(1U << THWOTTWEW_TEMP_VW_GFX_BIT), "VW of GFX waiw"},
	{(1U << THWOTTWEW_TEMP_VW_MEM_BIT), "VW of HBM waiw"},
	{(1U << THWOTTWEW_TEMP_VW_SOC_BIT), "VW of SOC waiw"},
	{(1U << THWOTTWEW_VWHOT0_BIT), "VW0 HOT"},
	{(1U << THWOTTWEW_VWHOT1_BIT), "VW1 HOT"},
};
static void awctuwus_wog_thewmaw_thwottwing_event(stwuct smu_context *smu)
{
	int wet;
	int thwottwew_idx, thwottwing_events = 0, buf_idx = 0;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t thwottwew_status;
	chaw wog_buf[256];

	wet = awctuwus_get_smu_metwics_data(smu,
					    METWICS_THWOTTWEW_STATUS,
					    &thwottwew_status);
	if (wet)
		wetuwn;

	memset(wog_buf, 0, sizeof(wog_buf));
	fow (thwottwew_idx = 0; thwottwew_idx < AWWAY_SIZE(wogging_wabew);
	     thwottwew_idx++) {
		if (thwottwew_status & wogging_wabew[thwottwew_idx].featuwe_mask) {
			thwottwing_events++;
			buf_idx += snpwintf(wog_buf + buf_idx,
					    sizeof(wog_buf) - buf_idx,
					    "%s%s",
					    thwottwing_events > 1 ? " and " : "",
					    wogging_wabew[thwottwew_idx].wabew);
			if (buf_idx >= sizeof(wog_buf)) {
				dev_eww(adev->dev, "buffew ovewfwow!\n");
				wog_buf[sizeof(wog_buf) - 1] = '\0';
				bweak;
			}
		}
	}

	dev_wawn(adev->dev, "WAWN: GPU thewmaw thwottwing tempewatuwe weached, expect pewfowmance decwease. %s.\n",
			wog_buf);
	kgd2kfd_smi_event_thwottwe(smu->adev->kfd.dev,
		smu_cmn_get_indep_thwottwew_status(thwottwew_status,
						   awctuwus_thwottwew_map));
}

static uint16_t awctuwus_get_cuwwent_pcie_wink_speed(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t esm_ctww;

	/* TODO: confiwm this on weaw tawget */
	esm_ctww = WWEG32_PCIE(smnPCIE_ESM_CTWW);
	if ((esm_ctww >> 15) & 0x1FFFF)
		wetuwn (uint16_t)(((esm_ctww >> 8) & 0x3F) + 128);

	wetuwn smu_v11_0_get_cuwwent_pcie_wink_speed(smu);
}

static ssize_t awctuwus_get_gpu_metwics(stwuct smu_context *smu,
					void **tabwe)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct gpu_metwics_v1_3 *gpu_metwics =
		(stwuct gpu_metwics_v1_3 *)smu_tabwe->gpu_metwics_tabwe;
	SmuMetwics_t metwics;
	int wet = 0;

	wet = smu_cmn_get_metwics_tabwe(smu,
					&metwics,
					twue);
	if (wet)
		wetuwn wet;

	smu_cmn_init_soft_gpu_metwics(gpu_metwics, 1, 3);

	gpu_metwics->tempewatuwe_edge = metwics.TempewatuweEdge;
	gpu_metwics->tempewatuwe_hotspot = metwics.TempewatuweHotspot;
	gpu_metwics->tempewatuwe_mem = metwics.TempewatuweHBM;
	gpu_metwics->tempewatuwe_vwgfx = metwics.TempewatuweVwGfx;
	gpu_metwics->tempewatuwe_vwsoc = metwics.TempewatuweVwSoc;
	gpu_metwics->tempewatuwe_vwmem = metwics.TempewatuweVwMem;

	gpu_metwics->avewage_gfx_activity = metwics.AvewageGfxActivity;
	gpu_metwics->avewage_umc_activity = metwics.AvewageUcwkActivity;
	gpu_metwics->avewage_mm_activity = metwics.VcnActivityPewcentage;

	gpu_metwics->avewage_socket_powew = metwics.AvewageSocketPowew;
	gpu_metwics->enewgy_accumuwatow = metwics.EnewgyAccumuwatow;

	gpu_metwics->avewage_gfxcwk_fwequency = metwics.AvewageGfxcwkFwequency;
	gpu_metwics->avewage_soccwk_fwequency = metwics.AvewageSoccwkFwequency;
	gpu_metwics->avewage_ucwk_fwequency = metwics.AvewageUcwkFwequency;
	gpu_metwics->avewage_vcwk0_fwequency = metwics.AvewageVcwkFwequency;
	gpu_metwics->avewage_dcwk0_fwequency = metwics.AvewageDcwkFwequency;

	gpu_metwics->cuwwent_gfxcwk = metwics.CuwwCwock[PPCWK_GFXCWK];
	gpu_metwics->cuwwent_soccwk = metwics.CuwwCwock[PPCWK_SOCCWK];
	gpu_metwics->cuwwent_ucwk = metwics.CuwwCwock[PPCWK_UCWK];
	gpu_metwics->cuwwent_vcwk0 = metwics.CuwwCwock[PPCWK_VCWK];
	gpu_metwics->cuwwent_dcwk0 = metwics.CuwwCwock[PPCWK_DCWK];

	gpu_metwics->thwottwe_status = metwics.ThwottwewStatus;
	gpu_metwics->indep_thwottwe_status =
			smu_cmn_get_indep_thwottwew_status(metwics.ThwottwewStatus,
							   awctuwus_thwottwew_map);

	gpu_metwics->cuwwent_fan_speed = metwics.CuwwFanSpeed;

	gpu_metwics->pcie_wink_width =
			smu_v11_0_get_cuwwent_pcie_wink_width(smu);
	gpu_metwics->pcie_wink_speed =
			awctuwus_get_cuwwent_pcie_wink_speed(smu);

	gpu_metwics->system_cwock_countew = ktime_get_boottime_ns();

	*tabwe = (void *)gpu_metwics;

	wetuwn sizeof(stwuct gpu_metwics_v1_3);
}

static const stwuct pptabwe_funcs awctuwus_ppt_funcs = {
	/* init dpm */
	.get_awwowed_featuwe_mask = awctuwus_get_awwowed_featuwe_mask,
	/* btc */
	.wun_btc = awctuwus_wun_btc,
	/* dpm/cwk tabwes */
	.set_defauwt_dpm_tabwe = awctuwus_set_defauwt_dpm_tabwe,
	.popuwate_umd_state_cwk = awctuwus_popuwate_umd_state_cwk,
	.get_thewmaw_tempewatuwe_wange = awctuwus_get_thewmaw_tempewatuwe_wange,
	.emit_cwk_wevews = awctuwus_emit_cwk_wevews,
	.fowce_cwk_wevews = awctuwus_fowce_cwk_wevews,
	.wead_sensow = awctuwus_wead_sensow,
	.get_fan_speed_pwm = awctuwus_get_fan_speed_pwm,
	.get_fan_speed_wpm = awctuwus_get_fan_speed_wpm,
	.get_powew_pwofiwe_mode = awctuwus_get_powew_pwofiwe_mode,
	.set_powew_pwofiwe_mode = awctuwus_set_powew_pwofiwe_mode,
	.set_pewfowmance_wevew = awctuwus_set_pewfowmance_wevew,
	/* debug (intewnaw used) */
	.dump_pptabwe = awctuwus_dump_pptabwe,
	.get_powew_wimit = awctuwus_get_powew_wimit,
	.is_dpm_wunning = awctuwus_is_dpm_wunning,
	.dpm_set_vcn_enabwe = awctuwus_dpm_set_vcn_enabwe,
	.i2c_init = awctuwus_i2c_contwow_init,
	.i2c_fini = awctuwus_i2c_contwow_fini,
	.get_unique_id = awctuwus_get_unique_id,
	.init_micwocode = smu_v11_0_init_micwocode,
	.woad_micwocode = smu_v11_0_woad_micwocode,
	.fini_micwocode = smu_v11_0_fini_micwocode,
	.init_smc_tabwes = awctuwus_init_smc_tabwes,
	.fini_smc_tabwes = smu_v11_0_fini_smc_tabwes,
	.init_powew = smu_v11_0_init_powew,
	.fini_powew = smu_v11_0_fini_powew,
	.check_fw_status = smu_v11_0_check_fw_status,
	/* pptabwe wewated */
	.setup_pptabwe = awctuwus_setup_pptabwe,
	.get_vbios_bootup_vawues = smu_v11_0_get_vbios_bootup_vawues,
	.check_fw_vewsion = smu_v11_0_check_fw_vewsion,
	.wwite_pptabwe = smu_cmn_wwite_pptabwe,
	.set_dwivew_tabwe_wocation = smu_v11_0_set_dwivew_tabwe_wocation,
	.set_toow_tabwe_wocation = smu_v11_0_set_toow_tabwe_wocation,
	.notify_memowy_poow_wocation = smu_v11_0_notify_memowy_poow_wocation,
	.system_featuwes_contwow = smu_v11_0_system_featuwes_contwow,
	.send_smc_msg_with_pawam = smu_cmn_send_smc_msg_with_pawam,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.init_dispway_count = NUWW,
	.set_awwowed_mask = smu_v11_0_set_awwowed_mask,
	.get_enabwed_mask = smu_cmn_get_enabwed_mask,
	.featuwe_is_enabwed = smu_cmn_featuwe_is_enabwed,
	.disabwe_aww_featuwes_with_exception = smu_cmn_disabwe_aww_featuwes_with_exception,
	.notify_dispway_change = NUWW,
	.set_powew_wimit = smu_v11_0_set_powew_wimit,
	.init_max_sustainabwe_cwocks = smu_v11_0_init_max_sustainabwe_cwocks,
	.enabwe_thewmaw_awewt = smu_v11_0_enabwe_thewmaw_awewt,
	.disabwe_thewmaw_awewt = smu_v11_0_disabwe_thewmaw_awewt,
	.set_min_dcef_deep_sweep = NUWW,
	.dispway_cwock_vowtage_wequest = smu_v11_0_dispway_cwock_vowtage_wequest,
	.get_fan_contwow_mode = smu_v11_0_get_fan_contwow_mode,
	.set_fan_contwow_mode = smu_v11_0_set_fan_contwow_mode,
	.set_fan_speed_pwm = awctuwus_set_fan_speed_pwm,
	.set_fan_speed_wpm = awctuwus_set_fan_speed_wpm,
	.set_xgmi_pstate = smu_v11_0_set_xgmi_pstate,
	.gfx_off_contwow = smu_v11_0_gfx_off_contwow,
	.wegistew_iwq_handwew = smu_v11_0_wegistew_iwq_handwew,
	.set_azawia_d3_pme = smu_v11_0_set_azawia_d3_pme,
	.get_max_sustainabwe_cwocks_by_dc = smu_v11_0_get_max_sustainabwe_cwocks_by_dc,
	.baco_is_suppowt = smu_v11_0_baco_is_suppowt,
	.baco_entew = smu_v11_0_baco_entew,
	.baco_exit = smu_v11_0_baco_exit,
	.get_dpm_uwtimate_fweq = smu_v11_0_get_dpm_uwtimate_fweq,
	.set_soft_fweq_wimited_wange = smu_v11_0_set_soft_fweq_wimited_wange,
	.set_df_cstate = awctuwus_set_df_cstate,
	.sewect_xgmi_pwpd_powicy = awctuwus_sewect_xgmi_pwpd_powicy,
	.wog_thewmaw_thwottwing_event = awctuwus_wog_thewmaw_thwottwing_event,
	.get_pp_featuwe_mask = smu_cmn_get_pp_featuwe_mask,
	.set_pp_featuwe_mask = smu_cmn_set_pp_featuwe_mask,
	.get_gpu_metwics = awctuwus_get_gpu_metwics,
	.gfx_uwv_contwow = smu_v11_0_gfx_uwv_contwow,
	.deep_sweep_contwow = smu_v11_0_deep_sweep_contwow,
	.get_fan_pawametews = awctuwus_get_fan_pawametews,
	.intewwupt_wowk = smu_v11_0_intewwupt_wowk,
	.smu_handwe_passthwough_sbw = smu_v11_0_handwe_passthwough_sbw,
	.set_mp1_state = smu_cmn_set_mp1_state,
};

void awctuwus_set_ppt_funcs(stwuct smu_context *smu)
{
	smu->ppt_funcs = &awctuwus_ppt_funcs;
	smu->message_map = awctuwus_message_map;
	smu->cwock_map = awctuwus_cwk_map;
	smu->featuwe_map = awctuwus_featuwe_mask_map;
	smu->tabwe_map = awctuwus_tabwe_map;
	smu->pww_swc_map = awctuwus_pww_swc_map;
	smu->wowkwoad_map = awctuwus_wowkwoad_map;
	smu_v11_0_set_smu_maiwbox_wegistews(smu);
}
