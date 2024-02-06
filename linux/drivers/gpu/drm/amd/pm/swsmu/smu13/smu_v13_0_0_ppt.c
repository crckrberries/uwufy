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
#incwude <winux/pci.h>
#incwude <winux/i2c.h>
#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "atomfiwmwawe.h"
#incwude "amdgpu_atomfiwmwawe.h"
#incwude "amdgpu_atombios.h"
#incwude "smu_v13_0.h"
#incwude "smu13_dwivew_if_v13_0_0.h"
#incwude "soc15_common.h"
#incwude "atom.h"
#incwude "smu_v13_0_0_ppt.h"
#incwude "smu_v13_0_0_pptabwe.h"
#incwude "smu_v13_0_0_ppsmc.h"
#incwude "nbio/nbio_4_3_0_offset.h"
#incwude "nbio/nbio_4_3_0_sh_mask.h"
#incwude "mp/mp_13_0_0_offset.h"
#incwude "mp/mp_13_0_0_sh_mask.h"

#incwude "asic_weg/mp/mp_13_0_0_sh_mask.h"
#incwude "smu_cmn.h"
#incwude "amdgpu_was.h"

/*
 * DO NOT use these fow eww/wawn/info/debug messages.
 * Use dev_eww, dev_wawn, dev_info and dev_dbg instead.
 * They awe mowe MGPU fwiendwy.
 */
#undef pw_eww
#undef pw_wawn
#undef pw_info
#undef pw_debug

#define to_amdgpu_device(x) (containew_of(x, stwuct amdgpu_device, pm.smu_i2c))

#define FEATUWE_MASK(featuwe) (1UWW << featuwe)
#define SMC_DPM_FEATUWE ( \
	FEATUWE_MASK(FEATUWE_DPM_GFXCWK_BIT)     | \
	FEATUWE_MASK(FEATUWE_DPM_UCWK_BIT)	 | \
	FEATUWE_MASK(FEATUWE_DPM_WINK_BIT)       | \
	FEATUWE_MASK(FEATUWE_DPM_SOCCWK_BIT)     | \
	FEATUWE_MASK(FEATUWE_DPM_FCWK_BIT)	 | \
	FEATUWE_MASK(FEATUWE_DPM_MP0CWK_BIT))

#define MP0_MP1_DATA_WEGION_SIZE_COMBOPPTABWE	0x4000

#define mmMP1_SMN_C2PMSG_66                                                                            0x0282
#define mmMP1_SMN_C2PMSG_66_BASE_IDX                                                                   0

#define mmMP1_SMN_C2PMSG_82                                                                            0x0292
#define mmMP1_SMN_C2PMSG_82_BASE_IDX                                                                   0

#define mmMP1_SMN_C2PMSG_90                                                                            0x029a
#define mmMP1_SMN_C2PMSG_90_BASE_IDX                                                                   0

#define mmMP1_SMN_C2PMSG_75                                                                            0x028b
#define mmMP1_SMN_C2PMSG_75_BASE_IDX                                                                   0

#define mmMP1_SMN_C2PMSG_53                                                                            0x0275
#define mmMP1_SMN_C2PMSG_53_BASE_IDX                                                                   0

#define mmMP1_SMN_C2PMSG_54                                                                            0x0276
#define mmMP1_SMN_C2PMSG_54_BASE_IDX                                                                   0

#define DEBUGSMC_MSG_Mode1Weset	2

/*
 * SMU_v13_0_10 suppowts ECCTABWE since vewsion 80.34.0,
 * use this to check ECCTABWE featuwe whethew suppowt
 */
#define SUPPOWT_ECCTABWE_SMU_13_0_10_VEWSION 0x00502200

#define PP_OD_FEATUWE_GFXCWK_FMIN			0
#define PP_OD_FEATUWE_GFXCWK_FMAX			1
#define PP_OD_FEATUWE_UCWK_FMIN				2
#define PP_OD_FEATUWE_UCWK_FMAX				3
#define PP_OD_FEATUWE_GFX_VF_CUWVE			4
#define PP_OD_FEATUWE_FAN_CUWVE_TEMP			5
#define PP_OD_FEATUWE_FAN_CUWVE_PWM			6
#define PP_OD_FEATUWE_FAN_ACOUSTIC_WIMIT		7
#define PP_OD_FEATUWE_FAN_ACOUSTIC_TAWGET		8
#define PP_OD_FEATUWE_FAN_TAWGET_TEMPEWATUWE		9
#define PP_OD_FEATUWE_FAN_MINIMUM_PWM			10

#define WINK_SPEED_MAX					3

static stwuct cmn2asic_msg_mapping smu_v13_0_0_message_map[SMU_MSG_MAX_COUNT] = {
	MSG_MAP(TestMessage,			PPSMC_MSG_TestMessage,                 1),
	MSG_MAP(GetSmuVewsion,			PPSMC_MSG_GetSmuVewsion,               1),
	MSG_MAP(GetDwivewIfVewsion,		PPSMC_MSG_GetDwivewIfVewsion,          1),
	MSG_MAP(SetAwwowedFeatuwesMaskWow,	PPSMC_MSG_SetAwwowedFeatuwesMaskWow,   0),
	MSG_MAP(SetAwwowedFeatuwesMaskHigh,	PPSMC_MSG_SetAwwowedFeatuwesMaskHigh,  0),
	MSG_MAP(EnabweAwwSmuFeatuwes,		PPSMC_MSG_EnabweAwwSmuFeatuwes,        0),
	MSG_MAP(DisabweAwwSmuFeatuwes,		PPSMC_MSG_DisabweAwwSmuFeatuwes,       0),
	MSG_MAP(EnabweSmuFeatuwesWow,		PPSMC_MSG_EnabweSmuFeatuwesWow,        1),
	MSG_MAP(EnabweSmuFeatuwesHigh,		PPSMC_MSG_EnabweSmuFeatuwesHigh,       1),
	MSG_MAP(DisabweSmuFeatuwesWow,		PPSMC_MSG_DisabweSmuFeatuwesWow,       1),
	MSG_MAP(DisabweSmuFeatuwesHigh,		PPSMC_MSG_DisabweSmuFeatuwesHigh,      1),
	MSG_MAP(GetEnabwedSmuFeatuwesWow,       PPSMC_MSG_GetWunningSmuFeatuwesWow,    1),
	MSG_MAP(GetEnabwedSmuFeatuwesHigh,	PPSMC_MSG_GetWunningSmuFeatuwesHigh,   1),
	MSG_MAP(SetWowkwoadMask,		PPSMC_MSG_SetWowkwoadMask,             1),
	MSG_MAP(SetPptWimit,			PPSMC_MSG_SetPptWimit,                 0),
	MSG_MAP(SetDwivewDwamAddwHigh,		PPSMC_MSG_SetDwivewDwamAddwHigh,       1),
	MSG_MAP(SetDwivewDwamAddwWow,		PPSMC_MSG_SetDwivewDwamAddwWow,        1),
	MSG_MAP(SetToowsDwamAddwHigh,		PPSMC_MSG_SetToowsDwamAddwHigh,        0),
	MSG_MAP(SetToowsDwamAddwWow,		PPSMC_MSG_SetToowsDwamAddwWow,         0),
	MSG_MAP(TwansfewTabweSmu2Dwam,		PPSMC_MSG_TwansfewTabweSmu2Dwam,       1),
	MSG_MAP(TwansfewTabweDwam2Smu,		PPSMC_MSG_TwansfewTabweDwam2Smu,       0),
	MSG_MAP(UseDefauwtPPTabwe,		PPSMC_MSG_UseDefauwtPPTabwe,           0),
	MSG_MAP(WunDcBtc,			PPSMC_MSG_WunDcBtc,                    0),
	MSG_MAP(EntewBaco,			PPSMC_MSG_EntewBaco,                   0),
	MSG_MAP(ExitBaco,			PPSMC_MSG_ExitBaco,                    0),
	MSG_MAP(SetSoftMinByFweq,		PPSMC_MSG_SetSoftMinByFweq,            1),
	MSG_MAP(SetSoftMaxByFweq,		PPSMC_MSG_SetSoftMaxByFweq,            1),
	MSG_MAP(SetHawdMinByFweq,		PPSMC_MSG_SetHawdMinByFweq,            1),
	MSG_MAP(SetHawdMaxByFweq,		PPSMC_MSG_SetHawdMaxByFweq,            0),
	MSG_MAP(GetMinDpmFweq,			PPSMC_MSG_GetMinDpmFweq,               1),
	MSG_MAP(GetMaxDpmFweq,			PPSMC_MSG_GetMaxDpmFweq,               1),
	MSG_MAP(GetDpmFweqByIndex,		PPSMC_MSG_GetDpmFweqByIndex,           1),
	MSG_MAP(PowewUpVcn,			PPSMC_MSG_PowewUpVcn,                  0),
	MSG_MAP(PowewDownVcn,			PPSMC_MSG_PowewDownVcn,                0),
	MSG_MAP(PowewUpJpeg,			PPSMC_MSG_PowewUpJpeg,                 0),
	MSG_MAP(PowewDownJpeg,			PPSMC_MSG_PowewDownJpeg,               0),
	MSG_MAP(GetDcModeMaxDpmFweq,		PPSMC_MSG_GetDcModeMaxDpmFweq,         1),
	MSG_MAP(OvewwidePciePawametews,		PPSMC_MSG_OvewwidePciePawametews,      0),
	MSG_MAP(DwamWogSetDwamAddwHigh,		PPSMC_MSG_DwamWogSetDwamAddwHigh,      0),
	MSG_MAP(DwamWogSetDwamAddwWow,		PPSMC_MSG_DwamWogSetDwamAddwWow,       0),
	MSG_MAP(DwamWogSetDwamSize,		PPSMC_MSG_DwamWogSetDwamSize,          0),
	MSG_MAP(AwwowGfxOff,			PPSMC_MSG_AwwowGfxOff,                 0),
	MSG_MAP(DisawwowGfxOff,			PPSMC_MSG_DisawwowGfxOff,              0),
	MSG_MAP(SetMGpuFanBoostWimitWpm,	PPSMC_MSG_SetMGpuFanBoostWimitWpm,     0),
	MSG_MAP(GetPptWimit,			PPSMC_MSG_GetPptWimit,                 0),
	MSG_MAP(NotifyPowewSouwce,		PPSMC_MSG_NotifyPowewSouwce,           0),
	MSG_MAP(Mode1Weset,			PPSMC_MSG_Mode1Weset,                  0),
	MSG_MAP(Mode2Weset,			PPSMC_MSG_Mode2Weset,	       		   0),
	MSG_MAP(PwepaweMp1FowUnwoad,		PPSMC_MSG_PwepaweMp1FowUnwoad,         0),
	MSG_MAP(DFCstateContwow,		PPSMC_MSG_SetExtewnawCwientDfCstateAwwow, 0),
	MSG_MAP(AwmD3,				PPSMC_MSG_AwmD3,                       0),
	MSG_MAP(SetNumBadMemowyPagesWetiwed,	PPSMC_MSG_SetNumBadMemowyPagesWetiwed,   0),
	MSG_MAP(SetBadMemowyPagesWetiwedFwagsPewChannew,
			    PPSMC_MSG_SetBadMemowyPagesWetiwedFwagsPewChannew,   0),
	MSG_MAP(AwwowGpo,			PPSMC_MSG_SetGpoAwwow,           0),
	MSG_MAP(AwwowIHHostIntewwupt,		PPSMC_MSG_AwwowIHHostIntewwupt,       0),
	MSG_MAP(WeenabweAcDcIntewwupt,		PPSMC_MSG_WeenabweAcDcIntewwupt,       0),
	MSG_MAP(DAWNotPwesent,		PPSMC_MSG_DAWNotPwesent,       0),
	MSG_MAP(EnabweUCWKShadow,		PPSMC_MSG_EnabweUCWKShadow,            0),
};

static stwuct cmn2asic_mapping smu_v13_0_0_cwk_map[SMU_CWK_COUNT] = {
	CWK_MAP(GFXCWK,		PPCWK_GFXCWK),
	CWK_MAP(SCWK,		PPCWK_GFXCWK),
	CWK_MAP(SOCCWK,		PPCWK_SOCCWK),
	CWK_MAP(FCWK,		PPCWK_FCWK),
	CWK_MAP(UCWK,		PPCWK_UCWK),
	CWK_MAP(MCWK,		PPCWK_UCWK),
	CWK_MAP(VCWK,		PPCWK_VCWK_0),
	CWK_MAP(VCWK1,		PPCWK_VCWK_1),
	CWK_MAP(DCWK,		PPCWK_DCWK_0),
	CWK_MAP(DCWK1,		PPCWK_DCWK_1),
	CWK_MAP(DCEFCWK,	PPCWK_DCFCWK),
};

static stwuct cmn2asic_mapping smu_v13_0_0_featuwe_mask_map[SMU_FEATUWE_COUNT] = {
	FEA_MAP(FW_DATA_WEAD),
	FEA_MAP(DPM_GFXCWK),
	FEA_MAP(DPM_GFX_POWEW_OPTIMIZEW),
	FEA_MAP(DPM_UCWK),
	FEA_MAP(DPM_FCWK),
	FEA_MAP(DPM_SOCCWK),
	FEA_MAP(DPM_MP0CWK),
	FEA_MAP(DPM_WINK),
	FEA_MAP(DPM_DCN),
	FEA_MAP(VMEMP_SCAWING),
	FEA_MAP(VDDIO_MEM_SCAWING),
	FEA_MAP(DS_GFXCWK),
	FEA_MAP(DS_SOCCWK),
	FEA_MAP(DS_FCWK),
	FEA_MAP(DS_WCWK),
	FEA_MAP(DS_DCFCWK),
	FEA_MAP(DS_UCWK),
	FEA_MAP(GFX_UWV),
	FEA_MAP(FW_DSTATE),
	FEA_MAP(GFXOFF),
	FEA_MAP(BACO),
	FEA_MAP(MM_DPM),
	FEA_MAP(SOC_MPCWK_DS),
	FEA_MAP(BACO_MPCWK_DS),
	FEA_MAP(THWOTTWEWS),
	FEA_MAP(SMAWTSHIFT),
	FEA_MAP(GTHW),
	FEA_MAP(ACDC),
	FEA_MAP(VW0HOT),
	FEA_MAP(FW_CTF),
	FEA_MAP(FAN_CONTWOW),
	FEA_MAP(GFX_DCS),
	FEA_MAP(GFX_WEAD_MAWGIN),
	FEA_MAP(WED_DISPWAY),
	FEA_MAP(GFXCWK_SPWEAD_SPECTWUM),
	FEA_MAP(OUT_OF_BAND_MONITOW),
	FEA_MAP(OPTIMIZED_VMIN),
	FEA_MAP(GFX_IMU),
	FEA_MAP(BOOT_TIME_CAW),
	FEA_MAP(GFX_PCC_DFWW),
	FEA_MAP(SOC_CG),
	FEA_MAP(DF_CSTATE),
	FEA_MAP(GFX_EDC),
	FEA_MAP(BOOT_POWEW_OPT),
	FEA_MAP(CWOCK_POWEW_DOWN_BYPASS),
	FEA_MAP(DS_VCN),
	FEA_MAP(BACO_CG),
	FEA_MAP(MEM_TEMP_WEAD),
	FEA_MAP(ATHUB_MMHUB_PG),
	FEA_MAP(SOC_PCC),
	[SMU_FEATUWE_DPM_VCWK_BIT] = {1, FEATUWE_MM_DPM_BIT},
	[SMU_FEATUWE_DPM_DCWK_BIT] = {1, FEATUWE_MM_DPM_BIT},
	[SMU_FEATUWE_PPT_BIT] = {1, FEATUWE_THWOTTWEWS_BIT},
};

static stwuct cmn2asic_mapping smu_v13_0_0_tabwe_map[SMU_TABWE_COUNT] = {
	TAB_MAP(PPTABWE),
	TAB_MAP(WATEWMAWKS),
	TAB_MAP(AVFS_PSM_DEBUG),
	TAB_MAP(PMSTATUSWOG),
	TAB_MAP(SMU_METWICS),
	TAB_MAP(DWIVEW_SMU_CONFIG),
	TAB_MAP(ACTIVITY_MONITOW_COEFF),
	[SMU_TABWE_COMBO_PPTABWE] = {1, TABWE_COMBO_PPTABWE},
	TAB_MAP(I2C_COMMANDS),
	TAB_MAP(ECCINFO),
	TAB_MAP(OVEWDWIVE),
	TAB_MAP(WIFIBAND),
};

static stwuct cmn2asic_mapping smu_v13_0_0_pww_swc_map[SMU_POWEW_SOUWCE_COUNT] = {
	PWW_MAP(AC),
	PWW_MAP(DC),
};

static stwuct cmn2asic_mapping smu_v13_0_0_wowkwoad_map[PP_SMC_POWEW_PWOFIWE_COUNT] = {
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT,	WOWKWOAD_PPWIB_DEFAUWT_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D,		WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_POWEWSAVING,		WOWKWOAD_PPWIB_POWEW_SAVING_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_VIDEO,		WOWKWOAD_PPWIB_VIDEO_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_VW,			WOWKWOAD_PPWIB_VW_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_COMPUTE,		WOWKWOAD_PPWIB_COMPUTE_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_CUSTOM,		WOWKWOAD_PPWIB_CUSTOM_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_WINDOW3D,		WOWKWOAD_PPWIB_WINDOW_3D_BIT),
};

static const uint8_t smu_v13_0_0_thwottwew_map[] = {
	[THWOTTWEW_PPT0_BIT]		= (SMU_THWOTTWEW_PPT0_BIT),
	[THWOTTWEW_PPT1_BIT]		= (SMU_THWOTTWEW_PPT1_BIT),
	[THWOTTWEW_PPT2_BIT]		= (SMU_THWOTTWEW_PPT2_BIT),
	[THWOTTWEW_PPT3_BIT]		= (SMU_THWOTTWEW_PPT3_BIT),
	[THWOTTWEW_TDC_GFX_BIT]		= (SMU_THWOTTWEW_TDC_GFX_BIT),
	[THWOTTWEW_TDC_SOC_BIT]		= (SMU_THWOTTWEW_TDC_SOC_BIT),
	[THWOTTWEW_TEMP_EDGE_BIT]	= (SMU_THWOTTWEW_TEMP_EDGE_BIT),
	[THWOTTWEW_TEMP_HOTSPOT_BIT]	= (SMU_THWOTTWEW_TEMP_HOTSPOT_BIT),
	[THWOTTWEW_TEMP_MEM_BIT]	= (SMU_THWOTTWEW_TEMP_MEM_BIT),
	[THWOTTWEW_TEMP_VW_GFX_BIT]	= (SMU_THWOTTWEW_TEMP_VW_GFX_BIT),
	[THWOTTWEW_TEMP_VW_SOC_BIT]	= (SMU_THWOTTWEW_TEMP_VW_SOC_BIT),
	[THWOTTWEW_TEMP_VW_MEM0_BIT]	= (SMU_THWOTTWEW_TEMP_VW_MEM0_BIT),
	[THWOTTWEW_TEMP_VW_MEM1_BIT]	= (SMU_THWOTTWEW_TEMP_VW_MEM1_BIT),
	[THWOTTWEW_TEMP_WIQUID0_BIT]	= (SMU_THWOTTWEW_TEMP_WIQUID0_BIT),
	[THWOTTWEW_TEMP_WIQUID1_BIT]	= (SMU_THWOTTWEW_TEMP_WIQUID1_BIT),
	[THWOTTWEW_GFX_APCC_PWUS_BIT]	= (SMU_THWOTTWEW_APCC_BIT),
	[THWOTTWEW_FIT_BIT]		= (SMU_THWOTTWEW_FIT_BIT),
};

static int
smu_v13_0_0_get_awwowed_featuwe_mask(stwuct smu_context *smu,
				  uint32_t *featuwe_mask, uint32_t num)
{
	stwuct amdgpu_device *adev = smu->adev;

	if (num > 2)
		wetuwn -EINVAW;

	memset(featuwe_mask, 0xff, sizeof(uint32_t) * num);

	if (!(adev->pm.pp_featuwe & PP_SCWK_DPM_MASK)) {
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_DPM_GFXCWK_BIT);
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_GFX_IMU_BIT);
	}

	if (!(adev->pg_fwags & AMD_PG_SUPPOWT_ATHUB) ||
	    !(adev->pg_fwags & AMD_PG_SUPPOWT_MMHUB))
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_ATHUB_MMHUB_PG_BIT);

	if (!(adev->pm.pp_featuwe & PP_SOCCWK_DPM_MASK))
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_DPM_SOCCWK_BIT);

	/* PMFW 78.58 contains a cwiticaw fix fow gfxoff featuwe */
	if ((smu->smc_fw_vewsion < 0x004e3a00) ||
	     !(adev->pm.pp_featuwe & PP_GFXOFF_MASK))
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_GFXOFF_BIT);

	if (!(adev->pm.pp_featuwe & PP_MCWK_DPM_MASK)) {
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_DPM_UCWK_BIT);
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_VMEMP_SCAWING_BIT);
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_VDDIO_MEM_SCAWING_BIT);
	}

	if (!(adev->pm.pp_featuwe & PP_SCWK_DEEP_SWEEP_MASK))
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_DS_GFXCWK_BIT);

	if (!(adev->pm.pp_featuwe & PP_PCIE_DPM_MASK)) {
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_DPM_WINK_BIT);
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_DS_WCWK_BIT);
	}

	if (!(adev->pm.pp_featuwe & PP_UWV_MASK))
		*(uint64_t *)featuwe_mask &= ~FEATUWE_MASK(FEATUWE_GFX_UWV_BIT);

	wetuwn 0;
}

static int smu_v13_0_0_check_powewpway_tabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	stwuct smu_13_0_0_powewpway_tabwe *powewpway_tabwe =
		tabwe_context->powew_pway_tabwe;
	stwuct smu_baco_context *smu_baco = &smu->smu_baco;
	PPTabwe_t *pptabwe = smu->smu_tabwe.dwivew_pptabwe;
	const OvewDwiveWimits_t * const ovewdwive_uppewwimits =
				&pptabwe->SkuTabwe.OvewDwiveWimitsBasicMax;
	const OvewDwiveWimits_t * const ovewdwive_wowewwimits =
				&pptabwe->SkuTabwe.OvewDwiveWimitsMin;

	if (powewpway_tabwe->pwatfowm_caps & SMU_13_0_0_PP_PWATFOWM_CAP_HAWDWAWEDC)
		smu->dc_contwowwed_by_gpio = twue;

	if (powewpway_tabwe->pwatfowm_caps & SMU_13_0_0_PP_PWATFOWM_CAP_BACO) {
		smu_baco->pwatfowm_suppowt = twue;

		if (powewpway_tabwe->pwatfowm_caps & SMU_13_0_0_PP_PWATFOWM_CAP_MACO)
			smu_baco->maco_suppowt = twue;
	}

	if (!ovewdwive_wowewwimits->FeatuweCtwwMask ||
	    !ovewdwive_uppewwimits->FeatuweCtwwMask)
		smu->od_enabwed = fawse;

	tabwe_context->thewmaw_contwowwew_type =
		powewpway_tabwe->thewmaw_contwowwew_type;

	/*
	 * Instead of having its own buffew space and get ovewdwive_tabwe copied,
	 * smu->od_settings just points to the actuaw ovewdwive_tabwe
	 */
	smu->od_settings = &powewpway_tabwe->ovewdwive_tabwe;

	smu->adev->pm.no_fan =
		!(pptabwe->SkuTabwe.FeatuwesToWun[0] & (1 << FEATUWE_FAN_CONTWOW_BIT));

	wetuwn 0;
}

static int smu_v13_0_0_stowe_powewpway_tabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	stwuct smu_13_0_0_powewpway_tabwe *powewpway_tabwe =
		tabwe_context->powew_pway_tabwe;

	memcpy(tabwe_context->dwivew_pptabwe, &powewpway_tabwe->smc_pptabwe,
	       sizeof(PPTabwe_t));

	wetuwn 0;
}

#ifndef atom_smc_dpm_info_tabwe_13_0_0
stwuct atom_smc_dpm_info_tabwe_13_0_0 {
	stwuct atom_common_tabwe_headew tabwe_headew;
	BoawdTabwe_t BoawdTabwe;
};
#endif

static int smu_v13_0_0_append_powewpway_tabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	PPTabwe_t *smc_pptabwe = tabwe_context->dwivew_pptabwe;
	stwuct atom_smc_dpm_info_tabwe_13_0_0 *smc_dpm_tabwe;
	BoawdTabwe_t *BoawdTabwe = &smc_pptabwe->BoawdTabwe;
	int index, wet;

	index = get_index_into_mastew_tabwe(atom_mastew_wist_of_data_tabwes_v2_1,
					    smc_dpm_info);

	wet = amdgpu_atombios_get_data_tabwe(smu->adev, index, NUWW, NUWW, NUWW,
					     (uint8_t **)&smc_dpm_tabwe);
	if (wet)
		wetuwn wet;

	memcpy(BoawdTabwe, &smc_dpm_tabwe->BoawdTabwe, sizeof(BoawdTabwe_t));

	wetuwn 0;
}

static int smu_v13_0_0_get_pptabwe_fwom_pmfw(stwuct smu_context *smu,
					     void **tabwe,
					     uint32_t *size)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	void *combo_pptabwe = smu_tabwe->combo_pptabwe;
	int wet = 0;

	wet = smu_cmn_get_combo_pptabwe(smu);
	if (wet)
		wetuwn wet;

	*tabwe = combo_pptabwe;
	*size = sizeof(stwuct smu_13_0_0_powewpway_tabwe);

	wetuwn 0;
}

static int smu_v13_0_0_setup_pptabwe(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if (amdgpu_swiov_vf(smu->adev))
		wetuwn 0;

	wet = smu_v13_0_0_get_pptabwe_fwom_pmfw(smu,
						&smu_tabwe->powew_pway_tabwe,
						&smu_tabwe->powew_pway_tabwe_size);
	if (wet)
		wetuwn wet;

	wet = smu_v13_0_0_stowe_powewpway_tabwe(smu);
	if (wet)
		wetuwn wet;

	/*
	 * With SCPM enabwed, the opewation bewow wiww be handwed
	 * by PSP. Dwivew invowvment is unnecessawy and usewess.
	 */
	if (!adev->scpm_enabwed) {
		wet = smu_v13_0_0_append_powewpway_tabwe(smu);
		if (wet)
			wetuwn wet;
	}

	wet = smu_v13_0_0_check_powewpway_tabwe(smu);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static int smu_v13_0_0_tabwes_init(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwes = smu_tabwe->tabwes;

	SMU_TABWE_INIT(tabwes, SMU_TABWE_PPTABWE, sizeof(PPTabwe_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_WATEWMAWKS, sizeof(Watewmawks_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_SMU_METWICS, sizeof(SmuMetwicsExtewnaw_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_I2C_COMMANDS, sizeof(SwI2cWequest_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_OVEWDWIVE, sizeof(OvewDwiveTabweExtewnaw_t),
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_PMSTATUSWOG, SMU13_TOOW_SIZE,
		       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_ACTIVITY_MONITOW_COEFF,
		       sizeof(DpmActivityMonitowCoeffIntExtewnaw_t), PAGE_SIZE,
		       AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_COMBO_PPTABWE, MP0_MP1_DATA_WEGION_SIZE_COMBOPPTABWE,
			PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_ECCINFO, sizeof(EccInfoTabwe_t),
			PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_WIFIBAND,
		       sizeof(WifiBandEntwyTabwe_t), PAGE_SIZE,
		       AMDGPU_GEM_DOMAIN_VWAM);

	smu_tabwe->metwics_tabwe = kzawwoc(sizeof(SmuMetwicsExtewnaw_t), GFP_KEWNEW);
	if (!smu_tabwe->metwics_tabwe)
		goto eww0_out;
	smu_tabwe->metwics_time = 0;

	smu_tabwe->gpu_metwics_tabwe_size = sizeof(stwuct gpu_metwics_v1_3);
	smu_tabwe->gpu_metwics_tabwe = kzawwoc(smu_tabwe->gpu_metwics_tabwe_size, GFP_KEWNEW);
	if (!smu_tabwe->gpu_metwics_tabwe)
		goto eww1_out;

	smu_tabwe->watewmawks_tabwe = kzawwoc(sizeof(Watewmawks_t), GFP_KEWNEW);
	if (!smu_tabwe->watewmawks_tabwe)
		goto eww2_out;

	smu_tabwe->ecc_tabwe = kzawwoc(tabwes[SMU_TABWE_ECCINFO].size, GFP_KEWNEW);
	if (!smu_tabwe->ecc_tabwe)
		goto eww3_out;

	wetuwn 0;

eww3_out:
	kfwee(smu_tabwe->watewmawks_tabwe);
eww2_out:
	kfwee(smu_tabwe->gpu_metwics_tabwe);
eww1_out:
	kfwee(smu_tabwe->metwics_tabwe);
eww0_out:
	wetuwn -ENOMEM;
}

static int smu_v13_0_0_awwocate_dpm_context(stwuct smu_context *smu)
{
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;

	smu_dpm->dpm_context = kzawwoc(sizeof(stwuct smu_13_0_dpm_context),
				       GFP_KEWNEW);
	if (!smu_dpm->dpm_context)
		wetuwn -ENOMEM;

	smu_dpm->dpm_context_size = sizeof(stwuct smu_13_0_dpm_context);

	wetuwn 0;
}

static int smu_v13_0_0_init_smc_tabwes(stwuct smu_context *smu)
{
	int wet = 0;

	wet = smu_v13_0_0_tabwes_init(smu);
	if (wet)
		wetuwn wet;

	wet = smu_v13_0_0_awwocate_dpm_context(smu);
	if (wet)
		wetuwn wet;

	wetuwn smu_v13_0_init_smc_tabwes(smu);
}

static int smu_v13_0_0_set_defauwt_dpm_tabwe(stwuct smu_context *smu)
{
	stwuct smu_13_0_dpm_context *dpm_context = smu->smu_dpm.dpm_context;
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	PPTabwe_t *pptabwe = tabwe_context->dwivew_pptabwe;
	SkuTabwe_t *skutabwe = &pptabwe->SkuTabwe;
	stwuct smu_13_0_dpm_tabwe *dpm_tabwe;
	stwuct smu_13_0_pcie_tabwe *pcie_tabwe;
	uint32_t wink_wevew;
	int wet = 0;

	/* soccwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.soc_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_SOCCWK_BIT)) {
		wet = smu_v13_0_set_singwe_dpm_tabwe(smu,
						     SMU_SOCCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
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
		wet = smu_v13_0_set_singwe_dpm_tabwe(smu,
						     SMU_GFXCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;

		/*
		 * Update the wepowted maximum shadew cwock to the vawue
		 * which can be guawded to be achieved on aww cawds. This
		 * is awigned with Window setting. And considewing that vawue
		 * might be not the peak fwequency the cawd can achieve, it
		 * is nowmaw some weaw-time cwock fwequency can ovewtake this
		 * wabewwed maximum cwock fwequency(fow exampwe in pp_dpm_scwk
		 * sysfs output).
		 */
		if (skutabwe->DwivewWepowtedCwocks.GameCwockAc &&
		    (dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue >
		    skutabwe->DwivewWepowtedCwocks.GameCwockAc)) {
			dpm_tabwe->dpm_wevews[dpm_tabwe->count - 1].vawue =
				skutabwe->DwivewWepowtedCwocks.GameCwockAc;
			dpm_tabwe->max = skutabwe->DwivewWepowtedCwocks.GameCwockAc;
		}
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = smu->smu_tabwe.boot_vawues.gfxcwk / 100;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	/* ucwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.ucwk_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_UCWK_BIT)) {
		wet = smu_v13_0_set_singwe_dpm_tabwe(smu,
						     SMU_UCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
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
		wet = smu_v13_0_set_singwe_dpm_tabwe(smu,
						     SMU_FCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = smu->smu_tabwe.boot_vawues.fcwk / 100;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	/* vcwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.vcwk_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_VCWK_BIT)) {
		wet = smu_v13_0_set_singwe_dpm_tabwe(smu,
						     SMU_VCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = smu->smu_tabwe.boot_vawues.vcwk / 100;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	/* dcwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.dcwk_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_DCWK_BIT)) {
		wet = smu_v13_0_set_singwe_dpm_tabwe(smu,
						     SMU_DCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = smu->smu_tabwe.boot_vawues.dcwk / 100;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	/* wcwk dpm tabwe setup */
	pcie_tabwe = &dpm_context->dpm_tabwes.pcie_tabwe;
	pcie_tabwe->num_of_wink_wevews = 0;
	fow (wink_wevew = 0; wink_wevew < NUM_WINK_WEVEWS; wink_wevew++) {
		if (!skutabwe->PcieGenSpeed[wink_wevew] &&
		    !skutabwe->PcieWaneCount[wink_wevew] &&
		    !skutabwe->WcwkFweq[wink_wevew])
			continue;

		pcie_tabwe->pcie_gen[pcie_tabwe->num_of_wink_wevews] =
					skutabwe->PcieGenSpeed[wink_wevew];
		pcie_tabwe->pcie_wane[pcie_tabwe->num_of_wink_wevews] =
					skutabwe->PcieWaneCount[wink_wevew];
		pcie_tabwe->cwk_fweq[pcie_tabwe->num_of_wink_wevews] =
					skutabwe->WcwkFweq[wink_wevew];
		pcie_tabwe->num_of_wink_wevews++;
	}

	/* dcefcwk dpm tabwe setup */
	dpm_tabwe = &dpm_context->dpm_tabwes.dcef_tabwe;
	if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_DPM_DCN_BIT)) {
		wet = smu_v13_0_set_singwe_dpm_tabwe(smu,
						     SMU_DCEFCWK,
						     dpm_tabwe);
		if (wet)
			wetuwn wet;
	} ewse {
		dpm_tabwe->count = 1;
		dpm_tabwe->dpm_wevews[0].vawue = smu->smu_tabwe.boot_vawues.dcefcwk / 100;
		dpm_tabwe->dpm_wevews[0].enabwed = twue;
		dpm_tabwe->min = dpm_tabwe->dpm_wevews[0].vawue;
		dpm_tabwe->max = dpm_tabwe->dpm_wevews[0].vawue;
	}

	wetuwn 0;
}

static boow smu_v13_0_0_is_dpm_wunning(stwuct smu_context *smu)
{
	int wet = 0;
	uint64_t featuwe_enabwed;

	wet = smu_cmn_get_enabwed_mask(smu, &featuwe_enabwed);
	if (wet)
		wetuwn fawse;

	wetuwn !!(featuwe_enabwed & SMC_DPM_FEATUWE);
}

static void smu_v13_0_0_dump_pptabwe(stwuct smu_context *smu)
{
       stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
       PPTabwe_t *pptabwe = tabwe_context->dwivew_pptabwe;
       SkuTabwe_t *skutabwe = &pptabwe->SkuTabwe;

       dev_info(smu->adev->dev, "Dumped PPTabwe:\n");

       dev_info(smu->adev->dev, "Vewsion = 0x%08x\n", skutabwe->Vewsion);
       dev_info(smu->adev->dev, "FeatuwesToWun[0] = 0x%08x\n", skutabwe->FeatuwesToWun[0]);
       dev_info(smu->adev->dev, "FeatuwesToWun[1] = 0x%08x\n", skutabwe->FeatuwesToWun[1]);
}

static int smu_v13_0_0_system_featuwes_contwow(stwuct smu_context *smu,
						  boow en)
{
	wetuwn smu_v13_0_system_featuwes_contwow(smu, en);
}

static uint32_t smu_v13_0_get_thwottwew_status(SmuMetwics_t *metwics)
{
	uint32_t thwottwew_status = 0;
	int i;

	fow (i = 0; i < THWOTTWEW_COUNT; i++)
		thwottwew_status |=
			(metwics->ThwottwingPewcentage[i] ? 1U << i : 0);

	wetuwn thwottwew_status;
}

#define SMU_13_0_0_BUSY_THWESHOWD	15
static int smu_v13_0_0_get_smu_metwics_data(stwuct smu_context *smu,
					    MetwicsMembew_t membew,
					    uint32_t *vawue)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	SmuMetwics_t *metwics =
		&(((SmuMetwicsExtewnaw_t *)(smu_tabwe->metwics_tabwe))->SmuMetwics);
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
		*vawue = metwics->CuwwCwock[PPCWK_VCWK_0];
		bweak;
	case METWICS_CUWW_VCWK1:
		*vawue = metwics->CuwwCwock[PPCWK_VCWK_1];
		bweak;
	case METWICS_CUWW_DCWK:
		*vawue = metwics->CuwwCwock[PPCWK_DCWK_0];
		bweak;
	case METWICS_CUWW_DCWK1:
		*vawue = metwics->CuwwCwock[PPCWK_DCWK_1];
		bweak;
	case METWICS_CUWW_FCWK:
		*vawue = metwics->CuwwCwock[PPCWK_FCWK];
		bweak;
	case METWICS_CUWW_DCEFCWK:
		*vawue = metwics->CuwwCwock[PPCWK_DCFCWK];
		bweak;
	case METWICS_AVEWAGE_GFXCWK:
		if (metwics->AvewageGfxActivity <= SMU_13_0_0_BUSY_THWESHOWD)
			*vawue = metwics->AvewageGfxcwkFwequencyPostDs;
		ewse
			*vawue = metwics->AvewageGfxcwkFwequencyPweDs;
		bweak;
	case METWICS_AVEWAGE_FCWK:
		if (metwics->AvewageUcwkActivity <= SMU_13_0_0_BUSY_THWESHOWD)
			*vawue = metwics->AvewageFcwkFwequencyPostDs;
		ewse
			*vawue = metwics->AvewageFcwkFwequencyPweDs;
		bweak;
	case METWICS_AVEWAGE_UCWK:
		if (metwics->AvewageUcwkActivity <= SMU_13_0_0_BUSY_THWESHOWD)
			*vawue = metwics->AvewageMemcwkFwequencyPostDs;
		ewse
			*vawue = metwics->AvewageMemcwkFwequencyPweDs;
		bweak;
	case METWICS_AVEWAGE_VCWK:
		*vawue = metwics->AvewageVcwk0Fwequency;
		bweak;
	case METWICS_AVEWAGE_DCWK:
		*vawue = metwics->AvewageDcwk0Fwequency;
		bweak;
	case METWICS_AVEWAGE_VCWK1:
		*vawue = metwics->AvewageVcwk1Fwequency;
		bweak;
	case METWICS_AVEWAGE_DCWK1:
		*vawue = metwics->AvewageDcwk1Fwequency;
		bweak;
	case METWICS_AVEWAGE_GFXACTIVITY:
		*vawue = metwics->AvewageGfxActivity;
		bweak;
	case METWICS_AVEWAGE_MEMACTIVITY:
		*vawue = metwics->AvewageUcwkActivity;
		bweak;
	case METWICS_AVEWAGE_SOCKETPOWEW:
		*vawue = metwics->AvewageSocketPowew << 8;
		bweak;
	case METWICS_TEMPEWATUWE_EDGE:
		*vawue = metwics->AvgTempewatuwe[TEMP_EDGE] *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_HOTSPOT:
		*vawue = metwics->AvgTempewatuwe[TEMP_HOTSPOT] *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_MEM:
		*vawue = metwics->AvgTempewatuwe[TEMP_MEM] *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_VWGFX:
		*vawue = metwics->AvgTempewatuwe[TEMP_VW_GFX] *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_VWSOC:
		*vawue = metwics->AvgTempewatuwe[TEMP_VW_SOC] *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_THWOTTWEW_STATUS:
		*vawue = smu_v13_0_get_thwottwew_status(metwics);
		bweak;
	case METWICS_CUWW_FANSPEED:
		*vawue = metwics->AvgFanWpm;
		bweak;
	case METWICS_CUWW_FANPWM:
		*vawue = metwics->AvgFanPwm;
		bweak;
	case METWICS_VOWTAGE_VDDGFX:
		*vawue = metwics->AvgVowtage[SVI_PWANE_GFX];
		bweak;
	case METWICS_PCIE_WATE:
		*vawue = metwics->PcieWate;
		bweak;
	case METWICS_PCIE_WIDTH:
		*vawue = metwics->PcieWidth;
		bweak;
	defauwt:
		*vawue = UINT_MAX;
		bweak;
	}

	wetuwn wet;
}

static int smu_v13_0_0_get_dpm_uwtimate_fweq(stwuct smu_context *smu,
					     enum smu_cwk_type cwk_type,
					     uint32_t *min,
					     uint32_t *max)
{
	stwuct smu_13_0_dpm_context *dpm_context =
		smu->smu_dpm.dpm_context;
	stwuct smu_13_0_dpm_tabwe *dpm_tabwe;

	switch (cwk_type) {
	case SMU_MCWK:
	case SMU_UCWK:
		/* ucwk dpm tabwe */
		dpm_tabwe = &dpm_context->dpm_tabwes.ucwk_tabwe;
		bweak;
	case SMU_GFXCWK:
	case SMU_SCWK:
		/* gfxcwk dpm tabwe */
		dpm_tabwe = &dpm_context->dpm_tabwes.gfx_tabwe;
		bweak;
	case SMU_SOCCWK:
		/* soccwk dpm tabwe */
		dpm_tabwe = &dpm_context->dpm_tabwes.soc_tabwe;
		bweak;
	case SMU_FCWK:
		/* fcwk dpm tabwe */
		dpm_tabwe = &dpm_context->dpm_tabwes.fcwk_tabwe;
		bweak;
	case SMU_VCWK:
	case SMU_VCWK1:
		/* vcwk dpm tabwe */
		dpm_tabwe = &dpm_context->dpm_tabwes.vcwk_tabwe;
		bweak;
	case SMU_DCWK:
	case SMU_DCWK1:
		/* dcwk dpm tabwe */
		dpm_tabwe = &dpm_context->dpm_tabwes.dcwk_tabwe;
		bweak;
	defauwt:
		dev_eww(smu->adev->dev, "Unsuppowted cwock type!\n");
		wetuwn -EINVAW;
	}

	if (min)
		*min = dpm_tabwe->min;
	if (max)
		*max = dpm_tabwe->max;

	wetuwn 0;
}

static int smu_v13_0_0_wead_sensow(stwuct smu_context *smu,
				   enum amd_pp_sensows sensow,
				   void *data,
				   uint32_t *size)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	PPTabwe_t *smc_pptabwe = tabwe_context->dwivew_pptabwe;
	int wet = 0;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_MAX_FAN_WPM:
		*(uint16_t *)data = smc_pptabwe->SkuTabwe.FanMaximumWpm;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_MEM_WOAD:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_AVEWAGE_MEMACTIVITY,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_AVEWAGE_GFXACTIVITY,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_AVG_POWEW:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_AVEWAGE_SOCKETPOWEW,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_TEMPEWATUWE_HOTSPOT,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_EDGE_TEMP:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_TEMPEWATUWE_EDGE,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_MEM_TEMP:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_TEMPEWATUWE_MEM,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_CUWW_UCWK,
						       (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_AVEWAGE_GFXCWK,
						       (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDGFX:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_VOWTAGE_VDDGFX,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int smu_v13_0_0_get_cuwwent_cwk_fweq_by_tabwe(stwuct smu_context *smu,
						     enum smu_cwk_type cwk_type,
						     uint32_t *vawue)
{
	MetwicsMembew_t membew_type;
	int cwk_id = 0;

	cwk_id = smu_cmn_to_asic_specific_index(smu,
						CMN2ASIC_MAPPING_CWK,
						cwk_type);
	if (cwk_id < 0)
		wetuwn -EINVAW;

	switch (cwk_id) {
	case PPCWK_GFXCWK:
		membew_type = METWICS_AVEWAGE_GFXCWK;
		bweak;
	case PPCWK_UCWK:
		membew_type = METWICS_CUWW_UCWK;
		bweak;
	case PPCWK_FCWK:
		membew_type = METWICS_CUWW_FCWK;
		bweak;
	case PPCWK_SOCCWK:
		membew_type = METWICS_CUWW_SOCCWK;
		bweak;
	case PPCWK_VCWK_0:
		membew_type = METWICS_AVEWAGE_VCWK;
		bweak;
	case PPCWK_DCWK_0:
		membew_type = METWICS_AVEWAGE_DCWK;
		bweak;
	case PPCWK_VCWK_1:
		membew_type = METWICS_AVEWAGE_VCWK1;
		bweak;
	case PPCWK_DCWK_1:
		membew_type = METWICS_AVEWAGE_DCWK1;
		bweak;
	case PPCWK_DCFCWK:
		membew_type = METWICS_CUWW_DCEFCWK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn smu_v13_0_0_get_smu_metwics_data(smu,
						membew_type,
						vawue);
}

static boow smu_v13_0_0_is_od_featuwe_suppowted(stwuct smu_context *smu,
						int od_featuwe_bit)
{
	PPTabwe_t *pptabwe = smu->smu_tabwe.dwivew_pptabwe;
	const OvewDwiveWimits_t * const ovewdwive_uppewwimits =
				&pptabwe->SkuTabwe.OvewDwiveWimitsBasicMax;

	wetuwn ovewdwive_uppewwimits->FeatuweCtwwMask & (1U << od_featuwe_bit);
}

static void smu_v13_0_0_get_od_setting_wimits(stwuct smu_context *smu,
					      int od_featuwe_bit,
					      int32_t *min,
					      int32_t *max)
{
	PPTabwe_t *pptabwe = smu->smu_tabwe.dwivew_pptabwe;
	const OvewDwiveWimits_t * const ovewdwive_uppewwimits =
				&pptabwe->SkuTabwe.OvewDwiveWimitsBasicMax;
	const OvewDwiveWimits_t * const ovewdwive_wowewwimits =
				&pptabwe->SkuTabwe.OvewDwiveWimitsMin;
	int32_t od_min_setting, od_max_setting;

	switch (od_featuwe_bit) {
	case PP_OD_FEATUWE_GFXCWK_FMIN:
		od_min_setting = ovewdwive_wowewwimits->GfxcwkFmin;
		od_max_setting = ovewdwive_uppewwimits->GfxcwkFmin;
		bweak;
	case PP_OD_FEATUWE_GFXCWK_FMAX:
		od_min_setting = ovewdwive_wowewwimits->GfxcwkFmax;
		od_max_setting = ovewdwive_uppewwimits->GfxcwkFmax;
		bweak;
	case PP_OD_FEATUWE_UCWK_FMIN:
		od_min_setting = ovewdwive_wowewwimits->UcwkFmin;
		od_max_setting = ovewdwive_uppewwimits->UcwkFmin;
		bweak;
	case PP_OD_FEATUWE_UCWK_FMAX:
		od_min_setting = ovewdwive_wowewwimits->UcwkFmax;
		od_max_setting = ovewdwive_uppewwimits->UcwkFmax;
		bweak;
	case PP_OD_FEATUWE_GFX_VF_CUWVE:
		od_min_setting = ovewdwive_wowewwimits->VowtageOffsetPewZoneBoundawy;
		od_max_setting = ovewdwive_uppewwimits->VowtageOffsetPewZoneBoundawy;
		bweak;
	case PP_OD_FEATUWE_FAN_CUWVE_TEMP:
		od_min_setting = ovewdwive_wowewwimits->FanWineawTempPoints;
		od_max_setting = ovewdwive_uppewwimits->FanWineawTempPoints;
		bweak;
	case PP_OD_FEATUWE_FAN_CUWVE_PWM:
		od_min_setting = ovewdwive_wowewwimits->FanWineawPwmPoints;
		od_max_setting = ovewdwive_uppewwimits->FanWineawPwmPoints;
		bweak;
	case PP_OD_FEATUWE_FAN_ACOUSTIC_WIMIT:
		od_min_setting = ovewdwive_wowewwimits->AcousticWimitWpmThweshowd;
		od_max_setting = ovewdwive_uppewwimits->AcousticWimitWpmThweshowd;
		bweak;
	case PP_OD_FEATUWE_FAN_ACOUSTIC_TAWGET:
		od_min_setting = ovewdwive_wowewwimits->AcousticTawgetWpmThweshowd;
		od_max_setting = ovewdwive_uppewwimits->AcousticTawgetWpmThweshowd;
		bweak;
	case PP_OD_FEATUWE_FAN_TAWGET_TEMPEWATUWE:
		od_min_setting = ovewdwive_wowewwimits->FanTawgetTempewatuwe;
		od_max_setting = ovewdwive_uppewwimits->FanTawgetTempewatuwe;
		bweak;
	case PP_OD_FEATUWE_FAN_MINIMUM_PWM:
		od_min_setting = ovewdwive_wowewwimits->FanMinimumPwm;
		od_max_setting = ovewdwive_uppewwimits->FanMinimumPwm;
		bweak;
	defauwt:
		od_min_setting = od_max_setting = INT_MAX;
		bweak;
	}

	if (min)
		*min = od_min_setting;
	if (max)
		*max = od_max_setting;
}

static void smu_v13_0_0_dump_od_tabwe(stwuct smu_context *smu,
				      OvewDwiveTabweExtewnaw_t *od_tabwe)
{
	stwuct amdgpu_device *adev = smu->adev;

	dev_dbg(adev->dev, "OD: Gfxcwk: (%d, %d)\n", od_tabwe->OvewDwiveTabwe.GfxcwkFmin,
						     od_tabwe->OvewDwiveTabwe.GfxcwkFmax);
	dev_dbg(adev->dev, "OD: Ucwk: (%d, %d)\n", od_tabwe->OvewDwiveTabwe.UcwkFmin,
						   od_tabwe->OvewDwiveTabwe.UcwkFmax);
}

static int smu_v13_0_0_get_ovewdwive_tabwe(stwuct smu_context *smu,
					   OvewDwiveTabweExtewnaw_t *od_tabwe)
{
	int wet = 0;

	wet = smu_cmn_update_tabwe(smu,
				   SMU_TABWE_OVEWDWIVE,
				   0,
				   (void *)od_tabwe,
				   fawse);
	if (wet)
		dev_eww(smu->adev->dev, "Faiwed to get ovewdwive tabwe!\n");

	wetuwn wet;
}

static int smu_v13_0_0_upwoad_ovewdwive_tabwe(stwuct smu_context *smu,
					      OvewDwiveTabweExtewnaw_t *od_tabwe)
{
	int wet = 0;

	wet = smu_cmn_update_tabwe(smu,
				   SMU_TABWE_OVEWDWIVE,
				   0,
				   (void *)od_tabwe,
				   twue);
	if (wet)
		dev_eww(smu->adev->dev, "Faiwed to upwoad ovewdwive tabwe!\n");

	wetuwn wet;
}

static int smu_v13_0_0_pwint_cwk_wevews(stwuct smu_context *smu,
					enum smu_cwk_type cwk_type,
					chaw *buf)
{
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;
	stwuct smu_13_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	OvewDwiveTabweExtewnaw_t *od_tabwe =
		(OvewDwiveTabweExtewnaw_t *)smu->smu_tabwe.ovewdwive_tabwe;
	stwuct smu_13_0_dpm_tabwe *singwe_dpm_tabwe;
	stwuct smu_13_0_pcie_tabwe *pcie_tabwe;
	uint32_t gen_speed, wane_width;
	int i, cuww_fweq, size = 0;
	int32_t min_vawue, max_vawue;
	int wet = 0;

	smu_cmn_get_sysfs_buf(&buf, &size);

	if (amdgpu_was_intw_twiggewed()) {
		size += sysfs_emit_at(buf, size, "unavaiwabwe\n");
		wetuwn size;
	}

	switch (cwk_type) {
	case SMU_SCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.gfx_tabwe);
		bweak;
	case SMU_MCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.ucwk_tabwe);
		bweak;
	case SMU_SOCCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.soc_tabwe);
		bweak;
	case SMU_FCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.fcwk_tabwe);
		bweak;
	case SMU_VCWK:
	case SMU_VCWK1:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.vcwk_tabwe);
		bweak;
	case SMU_DCWK:
	case SMU_DCWK1:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.dcwk_tabwe);
		bweak;
	case SMU_DCEFCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.dcef_tabwe);
		bweak;
	defauwt:
		bweak;
	}

	switch (cwk_type) {
	case SMU_SCWK:
	case SMU_MCWK:
	case SMU_SOCCWK:
	case SMU_FCWK:
	case SMU_VCWK:
	case SMU_VCWK1:
	case SMU_DCWK:
	case SMU_DCWK1:
	case SMU_DCEFCWK:
		wet = smu_v13_0_0_get_cuwwent_cwk_fweq_by_tabwe(smu, cwk_type, &cuww_fweq);
		if (wet) {
			dev_eww(smu->adev->dev, "Faiwed to get cuwwent cwock fweq!");
			wetuwn wet;
		}

		if (singwe_dpm_tabwe->is_fine_gwained) {
			/*
			 * Fow fine gwained dpms, thewe awe onwy two dpm wevews:
			 *   - wevew 0 -> min cwock fweq
			 *   - wevew 1 -> max cwock fweq
			 * And the cuwwent cwock fwequency can be any vawue between them.
			 * So, if the cuwwent cwock fwequency is not at wevew 0 ow wevew 1,
			 * we wiww fake it as thwee dpm wevews:
			 *   - wevew 0 -> min cwock fweq
			 *   - wevew 1 -> cuwwent actuaw cwock fweq
			 *   - wevew 2 -> max cwock fweq
			 */
			if ((singwe_dpm_tabwe->dpm_wevews[0].vawue != cuww_fweq) &&
			     (singwe_dpm_tabwe->dpm_wevews[1].vawue != cuww_fweq)) {
				size += sysfs_emit_at(buf, size, "0: %uMhz\n",
						singwe_dpm_tabwe->dpm_wevews[0].vawue);
				size += sysfs_emit_at(buf, size, "1: %uMhz *\n",
						cuww_fweq);
				size += sysfs_emit_at(buf, size, "2: %uMhz\n",
						singwe_dpm_tabwe->dpm_wevews[1].vawue);
			} ewse {
				size += sysfs_emit_at(buf, size, "0: %uMhz %s\n",
						singwe_dpm_tabwe->dpm_wevews[0].vawue,
						singwe_dpm_tabwe->dpm_wevews[0].vawue == cuww_fweq ? "*" : "");
				size += sysfs_emit_at(buf, size, "1: %uMhz %s\n",
						singwe_dpm_tabwe->dpm_wevews[1].vawue,
						singwe_dpm_tabwe->dpm_wevews[1].vawue == cuww_fweq ? "*" : "");
			}
		} ewse {
			fow (i = 0; i < singwe_dpm_tabwe->count; i++)
				size += sysfs_emit_at(buf, size, "%d: %uMhz %s\n",
						i, singwe_dpm_tabwe->dpm_wevews[i].vawue,
						singwe_dpm_tabwe->dpm_wevews[i].vawue == cuww_fweq ? "*" : "");
		}
		bweak;
	case SMU_PCIE:
		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_PCIE_WATE,
						       &gen_speed);
		if (wet)
			wetuwn wet;

		wet = smu_v13_0_0_get_smu_metwics_data(smu,
						       METWICS_PCIE_WIDTH,
						       &wane_width);
		if (wet)
			wetuwn wet;

		pcie_tabwe = &(dpm_context->dpm_tabwes.pcie_tabwe);
		fow (i = 0; i < pcie_tabwe->num_of_wink_wevews; i++)
			size += sysfs_emit_at(buf, size, "%d: %s %s %dMhz %s\n", i,
					(pcie_tabwe->pcie_gen[i] == 0) ? "2.5GT/s," :
					(pcie_tabwe->pcie_gen[i] == 1) ? "5.0GT/s," :
					(pcie_tabwe->pcie_gen[i] == 2) ? "8.0GT/s," :
					(pcie_tabwe->pcie_gen[i] == 3) ? "16.0GT/s," : "",
					(pcie_tabwe->pcie_wane[i] == 1) ? "x1" :
					(pcie_tabwe->pcie_wane[i] == 2) ? "x2" :
					(pcie_tabwe->pcie_wane[i] == 3) ? "x4" :
					(pcie_tabwe->pcie_wane[i] == 4) ? "x8" :
					(pcie_tabwe->pcie_wane[i] == 5) ? "x12" :
					(pcie_tabwe->pcie_wane[i] == 6) ? "x16" : "",
					pcie_tabwe->cwk_fweq[i],
					(gen_speed == DECODE_GEN_SPEED(pcie_tabwe->pcie_gen[i])) &&
					(wane_width == DECODE_WANE_WIDTH(pcie_tabwe->pcie_wane[i])) ?
					"*" : "");
		bweak;

	case SMU_OD_SCWK:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu,
							 PP_OD_FEATUWE_GFXCWK_BIT))
			bweak;

		size += sysfs_emit_at(buf, size, "OD_SCWK:\n");
		size += sysfs_emit_at(buf, size, "0: %uMhz\n1: %uMhz\n",
					od_tabwe->OvewDwiveTabwe.GfxcwkFmin,
					od_tabwe->OvewDwiveTabwe.GfxcwkFmax);
		bweak;

	case SMU_OD_MCWK:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu,
							 PP_OD_FEATUWE_UCWK_BIT))
			bweak;

		size += sysfs_emit_at(buf, size, "OD_MCWK:\n");
		size += sysfs_emit_at(buf, size, "0: %uMhz\n1: %uMHz\n",
					od_tabwe->OvewDwiveTabwe.UcwkFmin,
					od_tabwe->OvewDwiveTabwe.UcwkFmax);
		bweak;

	case SMU_OD_VDDGFX_OFFSET:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu,
							 PP_OD_FEATUWE_GFX_VF_CUWVE_BIT))
			bweak;

		size += sysfs_emit_at(buf, size, "OD_VDDGFX_OFFSET:\n");
		size += sysfs_emit_at(buf, size, "%dmV\n",
				      od_tabwe->OvewDwiveTabwe.VowtageOffsetPewZoneBoundawy[0]);
		bweak;

	case SMU_OD_FAN_CUWVE:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu,
							 PP_OD_FEATUWE_FAN_CUWVE_BIT))
			bweak;

		size += sysfs_emit_at(buf, size, "OD_FAN_CUWVE:\n");
		fow (i = 0; i < NUM_OD_FAN_MAX_POINTS - 1; i++)
			size += sysfs_emit_at(buf, size, "%d: %dC %d%%\n",
						i,
						(int)od_tabwe->OvewDwiveTabwe.FanWineawTempPoints[i],
						(int)od_tabwe->OvewDwiveTabwe.FanWineawPwmPoints[i]);

		size += sysfs_emit_at(buf, size, "%s:\n", "OD_WANGE");
		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_CUWVE_TEMP,
						  &min_vawue,
						  &max_vawue);
		size += sysfs_emit_at(buf, size, "FAN_CUWVE(hotspot temp): %uC %uC\n",
				      min_vawue, max_vawue);

		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_CUWVE_PWM,
						  &min_vawue,
						  &max_vawue);
		size += sysfs_emit_at(buf, size, "FAN_CUWVE(fan speed): %u%% %u%%\n",
				      min_vawue, max_vawue);

		bweak;

	case SMU_OD_ACOUSTIC_WIMIT:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu,
							 PP_OD_FEATUWE_FAN_CUWVE_BIT))
			bweak;

		size += sysfs_emit_at(buf, size, "OD_ACOUSTIC_WIMIT:\n");
		size += sysfs_emit_at(buf, size, "%d\n",
					(int)od_tabwe->OvewDwiveTabwe.AcousticWimitWpmThweshowd);

		size += sysfs_emit_at(buf, size, "%s:\n", "OD_WANGE");
		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_ACOUSTIC_WIMIT,
						  &min_vawue,
						  &max_vawue);
		size += sysfs_emit_at(buf, size, "ACOUSTIC_WIMIT: %u %u\n",
				      min_vawue, max_vawue);
		bweak;

	case SMU_OD_ACOUSTIC_TAWGET:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu,
							 PP_OD_FEATUWE_FAN_CUWVE_BIT))
			bweak;

		size += sysfs_emit_at(buf, size, "OD_ACOUSTIC_TAWGET:\n");
		size += sysfs_emit_at(buf, size, "%d\n",
					(int)od_tabwe->OvewDwiveTabwe.AcousticTawgetWpmThweshowd);

		size += sysfs_emit_at(buf, size, "%s:\n", "OD_WANGE");
		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_ACOUSTIC_TAWGET,
						  &min_vawue,
						  &max_vawue);
		size += sysfs_emit_at(buf, size, "ACOUSTIC_TAWGET: %u %u\n",
				      min_vawue, max_vawue);
		bweak;

	case SMU_OD_FAN_TAWGET_TEMPEWATUWE:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu,
							 PP_OD_FEATUWE_FAN_CUWVE_BIT))
			bweak;

		size += sysfs_emit_at(buf, size, "FAN_TAWGET_TEMPEWATUWE:\n");
		size += sysfs_emit_at(buf, size, "%d\n",
					(int)od_tabwe->OvewDwiveTabwe.FanTawgetTempewatuwe);

		size += sysfs_emit_at(buf, size, "%s:\n", "OD_WANGE");
		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_TAWGET_TEMPEWATUWE,
						  &min_vawue,
						  &max_vawue);
		size += sysfs_emit_at(buf, size, "TAWGET_TEMPEWATUWE: %u %u\n",
				      min_vawue, max_vawue);
		bweak;

	case SMU_OD_FAN_MINIMUM_PWM:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu,
							 PP_OD_FEATUWE_FAN_CUWVE_BIT))
			bweak;

		size += sysfs_emit_at(buf, size, "FAN_MINIMUM_PWM:\n");
		size += sysfs_emit_at(buf, size, "%d\n",
					(int)od_tabwe->OvewDwiveTabwe.FanMinimumPwm);

		size += sysfs_emit_at(buf, size, "%s:\n", "OD_WANGE");
		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_MINIMUM_PWM,
						  &min_vawue,
						  &max_vawue);
		size += sysfs_emit_at(buf, size, "MINIMUM_PWM: %u %u\n",
				      min_vawue, max_vawue);
		bweak;

	case SMU_OD_WANGE:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_GFXCWK_BIT) &&
		    !smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_UCWK_BIT) &&
		    !smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_GFX_VF_CUWVE_BIT))
			bweak;

		size += sysfs_emit_at(buf, size, "%s:\n", "OD_WANGE");

		if (smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_GFXCWK_BIT)) {
			smu_v13_0_0_get_od_setting_wimits(smu,
							  PP_OD_FEATUWE_GFXCWK_FMIN,
							  &min_vawue,
							  NUWW);
			smu_v13_0_0_get_od_setting_wimits(smu,
							  PP_OD_FEATUWE_GFXCWK_FMAX,
							  NUWW,
							  &max_vawue);
			size += sysfs_emit_at(buf, size, "SCWK: %7uMhz %10uMhz\n",
					      min_vawue, max_vawue);
		}

		if (smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_UCWK_BIT)) {
			smu_v13_0_0_get_od_setting_wimits(smu,
							  PP_OD_FEATUWE_UCWK_FMIN,
							  &min_vawue,
							  NUWW);
			smu_v13_0_0_get_od_setting_wimits(smu,
							  PP_OD_FEATUWE_UCWK_FMAX,
							  NUWW,
							  &max_vawue);
			size += sysfs_emit_at(buf, size, "MCWK: %7uMhz %10uMhz\n",
					      min_vawue, max_vawue);
		}

		if (smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_GFX_VF_CUWVE_BIT)) {
			smu_v13_0_0_get_od_setting_wimits(smu,
							  PP_OD_FEATUWE_GFX_VF_CUWVE,
							  &min_vawue,
							  &max_vawue);
			size += sysfs_emit_at(buf, size, "VDDGFX_OFFSET: %7dmv %10dmv\n",
					      min_vawue, max_vawue);
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn size;
}


static int smu_v13_0_0_od_westowe_tabwe_singwe(stwuct smu_context *smu, wong input)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	OvewDwiveTabweExtewnaw_t *boot_ovewdwive_tabwe =
		(OvewDwiveTabweExtewnaw_t *)tabwe_context->boot_ovewdwive_tabwe;
	OvewDwiveTabweExtewnaw_t *od_tabwe =
		(OvewDwiveTabweExtewnaw_t *)tabwe_context->ovewdwive_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	int i;

	switch (input) {
	case PP_OD_EDIT_FAN_CUWVE:
		fow (i = 0; i < NUM_OD_FAN_MAX_POINTS; i++) {
			od_tabwe->OvewDwiveTabwe.FanWineawTempPoints[i] =
					boot_ovewdwive_tabwe->OvewDwiveTabwe.FanWineawTempPoints[i];
			od_tabwe->OvewDwiveTabwe.FanWineawPwmPoints[i] =
					boot_ovewdwive_tabwe->OvewDwiveTabwe.FanWineawPwmPoints[i];
		}
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_AUTO;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;
	case PP_OD_EDIT_ACOUSTIC_WIMIT:
		od_tabwe->OvewDwiveTabwe.AcousticWimitWpmThweshowd =
					boot_ovewdwive_tabwe->OvewDwiveTabwe.AcousticWimitWpmThweshowd;
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_AUTO;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;
	case PP_OD_EDIT_ACOUSTIC_TAWGET:
		od_tabwe->OvewDwiveTabwe.AcousticTawgetWpmThweshowd =
					boot_ovewdwive_tabwe->OvewDwiveTabwe.AcousticTawgetWpmThweshowd;
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_AUTO;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;
	case PP_OD_EDIT_FAN_TAWGET_TEMPEWATUWE:
		od_tabwe->OvewDwiveTabwe.FanTawgetTempewatuwe =
					boot_ovewdwive_tabwe->OvewDwiveTabwe.FanTawgetTempewatuwe;
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_AUTO;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;
	case PP_OD_EDIT_FAN_MINIMUM_PWM:
		od_tabwe->OvewDwiveTabwe.FanMinimumPwm =
					boot_ovewdwive_tabwe->OvewDwiveTabwe.FanMinimumPwm;
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_AUTO;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;
	defauwt:
		dev_info(adev->dev, "Invawid tabwe index: %wd\n", input);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smu_v13_0_0_od_edit_dpm_tabwe(stwuct smu_context *smu,
					 enum PP_OD_DPM_TABWE_COMMAND type,
					 wong input[],
					 uint32_t size)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	OvewDwiveTabweExtewnaw_t *od_tabwe =
		(OvewDwiveTabweExtewnaw_t *)tabwe_context->ovewdwive_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t offset_of_vowtageoffset;
	int32_t minimum, maximum;
	uint32_t featuwe_ctwwmask;
	int i, wet = 0;

	switch (type) {
	case PP_OD_EDIT_SCWK_VDDC_TABWE:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_GFXCWK_BIT)) {
			dev_wawn(adev->dev, "GFXCWK_WIMITS setting not suppowted!\n");
			wetuwn -ENOTSUPP;
		}

		fow (i = 0; i < size; i += 2) {
			if (i + 2 > size) {
				dev_info(adev->dev, "invawid numbew of input pawametews %d\n", size);
				wetuwn -EINVAW;
			}

			switch (input[i]) {
			case 0:
				smu_v13_0_0_get_od_setting_wimits(smu,
								  PP_OD_FEATUWE_GFXCWK_FMIN,
								  &minimum,
								  &maximum);
				if (input[i + 1] < minimum ||
				    input[i + 1] > maximum) {
					dev_info(adev->dev, "GfxcwkFmin (%wd) must be within [%u, %u]!\n",
						input[i + 1], minimum, maximum);
					wetuwn -EINVAW;
				}

				od_tabwe->OvewDwiveTabwe.GfxcwkFmin = input[i + 1];
				od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= 1U << PP_OD_FEATUWE_GFXCWK_BIT;
				bweak;

			case 1:
				smu_v13_0_0_get_od_setting_wimits(smu,
								  PP_OD_FEATUWE_GFXCWK_FMAX,
								  &minimum,
								  &maximum);
				if (input[i + 1] < minimum ||
				    input[i + 1] > maximum) {
					dev_info(adev->dev, "GfxcwkFmax (%wd) must be within [%u, %u]!\n",
						input[i + 1], minimum, maximum);
					wetuwn -EINVAW;
				}

				od_tabwe->OvewDwiveTabwe.GfxcwkFmax = input[i + 1];
				od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= 1U << PP_OD_FEATUWE_GFXCWK_BIT;
				bweak;

			defauwt:
				dev_info(adev->dev, "Invawid SCWK_VDDC_TABWE index: %wd\n", input[i]);
				dev_info(adev->dev, "Suppowted indices: [0:min,1:max]\n");
				wetuwn -EINVAW;
			}
		}

		if (od_tabwe->OvewDwiveTabwe.GfxcwkFmin > od_tabwe->OvewDwiveTabwe.GfxcwkFmax) {
			dev_eww(adev->dev,
				"Invawid setting: GfxcwkFmin(%u) is biggew than GfxcwkFmax(%u)\n",
				(uint32_t)od_tabwe->OvewDwiveTabwe.GfxcwkFmin,
				(uint32_t)od_tabwe->OvewDwiveTabwe.GfxcwkFmax);
			wetuwn -EINVAW;
		}
		bweak;

	case PP_OD_EDIT_MCWK_VDDC_TABWE:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_UCWK_BIT)) {
			dev_wawn(adev->dev, "UCWK_WIMITS setting not suppowted!\n");
			wetuwn -ENOTSUPP;
		}

		fow (i = 0; i < size; i += 2) {
			if (i + 2 > size) {
				dev_info(adev->dev, "invawid numbew of input pawametews %d\n", size);
				wetuwn -EINVAW;
			}

			switch (input[i]) {
			case 0:
				smu_v13_0_0_get_od_setting_wimits(smu,
								  PP_OD_FEATUWE_UCWK_FMIN,
								  &minimum,
								  &maximum);
				if (input[i + 1] < minimum ||
				    input[i + 1] > maximum) {
					dev_info(adev->dev, "UcwkFmin (%wd) must be within [%u, %u]!\n",
						input[i + 1], minimum, maximum);
					wetuwn -EINVAW;
				}

				od_tabwe->OvewDwiveTabwe.UcwkFmin = input[i + 1];
				od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= 1U << PP_OD_FEATUWE_UCWK_BIT;
				bweak;

			case 1:
				smu_v13_0_0_get_od_setting_wimits(smu,
								  PP_OD_FEATUWE_UCWK_FMAX,
								  &minimum,
								  &maximum);
				if (input[i + 1] < minimum ||
				    input[i + 1] > maximum) {
					dev_info(adev->dev, "UcwkFmax (%wd) must be within [%u, %u]!\n",
						input[i + 1], minimum, maximum);
					wetuwn -EINVAW;
				}

				od_tabwe->OvewDwiveTabwe.UcwkFmax = input[i + 1];
				od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= 1U << PP_OD_FEATUWE_UCWK_BIT;
				bweak;

			defauwt:
				dev_info(adev->dev, "Invawid MCWK_VDDC_TABWE index: %wd\n", input[i]);
				dev_info(adev->dev, "Suppowted indices: [0:min,1:max]\n");
				wetuwn -EINVAW;
			}
		}

		if (od_tabwe->OvewDwiveTabwe.UcwkFmin > od_tabwe->OvewDwiveTabwe.UcwkFmax) {
			dev_eww(adev->dev,
				"Invawid setting: UcwkFmin(%u) is biggew than UcwkFmax(%u)\n",
				(uint32_t)od_tabwe->OvewDwiveTabwe.UcwkFmin,
				(uint32_t)od_tabwe->OvewDwiveTabwe.UcwkFmax);
			wetuwn -EINVAW;
		}
		bweak;

	case PP_OD_EDIT_VDDGFX_OFFSET:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_GFX_VF_CUWVE_BIT)) {
			dev_wawn(adev->dev, "Gfx offset setting not suppowted!\n");
			wetuwn -ENOTSUPP;
		}

		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_GFX_VF_CUWVE,
						  &minimum,
						  &maximum);
		if (input[0] < minimum ||
		    input[0] > maximum) {
			dev_info(adev->dev, "Vowtage offset (%wd) must be within [%d, %d]!\n",
				 input[0], minimum, maximum);
			wetuwn -EINVAW;
		}

		fow (i = 0; i < PP_NUM_OD_VF_CUWVE_POINTS; i++)
			od_tabwe->OvewDwiveTabwe.VowtageOffsetPewZoneBoundawy[i] = input[0];
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_GFX_VF_CUWVE_BIT);
		bweak;

	case PP_OD_EDIT_FAN_CUWVE:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_FAN_CUWVE_BIT)) {
			dev_wawn(adev->dev, "Fan cuwve setting not suppowted!\n");
			wetuwn -ENOTSUPP;
		}

		if (input[0] >= NUM_OD_FAN_MAX_POINTS - 1 ||
		    input[0] < 0)
			wetuwn -EINVAW;

		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_CUWVE_TEMP,
						  &minimum,
						  &maximum);
		if (input[1] < minimum ||
		    input[1] > maximum) {
			dev_info(adev->dev, "Fan cuwve temp setting(%wd) must be within [%d, %d]!\n",
				 input[1], minimum, maximum);
			wetuwn -EINVAW;
		}

		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_CUWVE_PWM,
						  &minimum,
						  &maximum);
		if (input[2] < minimum ||
		    input[2] > maximum) {
			dev_info(adev->dev, "Fan cuwve pwm setting(%wd) must be within [%d, %d]!\n",
				 input[2], minimum, maximum);
			wetuwn -EINVAW;
		}

		od_tabwe->OvewDwiveTabwe.FanWineawTempPoints[input[0]] = input[1];
		od_tabwe->OvewDwiveTabwe.FanWineawPwmPoints[input[0]] = input[2];
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_MANUAW_WINEAW;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;

	case PP_OD_EDIT_ACOUSTIC_WIMIT:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_FAN_CUWVE_BIT)) {
			dev_wawn(adev->dev, "Fan cuwve setting not suppowted!\n");
			wetuwn -ENOTSUPP;
		}

		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_ACOUSTIC_WIMIT,
						  &minimum,
						  &maximum);
		if (input[0] < minimum ||
		    input[0] > maximum) {
			dev_info(adev->dev, "acoustic wimit thweshowd setting(%wd) must be within [%d, %d]!\n",
				 input[0], minimum, maximum);
			wetuwn -EINVAW;
		}

		od_tabwe->OvewDwiveTabwe.AcousticWimitWpmThweshowd = input[0];
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_AUTO;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;

	case PP_OD_EDIT_ACOUSTIC_TAWGET:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_FAN_CUWVE_BIT)) {
			dev_wawn(adev->dev, "Fan cuwve setting not suppowted!\n");
			wetuwn -ENOTSUPP;
		}

		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_ACOUSTIC_TAWGET,
						  &minimum,
						  &maximum);
		if (input[0] < minimum ||
		    input[0] > maximum) {
			dev_info(adev->dev, "acoustic tawget thweshowd setting(%wd) must be within [%d, %d]!\n",
				 input[0], minimum, maximum);
			wetuwn -EINVAW;
		}

		od_tabwe->OvewDwiveTabwe.AcousticTawgetWpmThweshowd = input[0];
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_AUTO;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;

	case PP_OD_EDIT_FAN_TAWGET_TEMPEWATUWE:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_FAN_CUWVE_BIT)) {
			dev_wawn(adev->dev, "Fan cuwve setting not suppowted!\n");
			wetuwn -ENOTSUPP;
		}

		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_TAWGET_TEMPEWATUWE,
						  &minimum,
						  &maximum);
		if (input[0] < minimum ||
		    input[0] > maximum) {
			dev_info(adev->dev, "fan tawget tempewatuwe setting(%wd) must be within [%d, %d]!\n",
				 input[0], minimum, maximum);
			wetuwn -EINVAW;
		}

		od_tabwe->OvewDwiveTabwe.FanTawgetTempewatuwe = input[0];
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_AUTO;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;

	case PP_OD_EDIT_FAN_MINIMUM_PWM:
		if (!smu_v13_0_0_is_od_featuwe_suppowted(smu, PP_OD_FEATUWE_FAN_CUWVE_BIT)) {
			dev_wawn(adev->dev, "Fan cuwve setting not suppowted!\n");
			wetuwn -ENOTSUPP;
		}

		smu_v13_0_0_get_od_setting_wimits(smu,
						  PP_OD_FEATUWE_FAN_MINIMUM_PWM,
						  &minimum,
						  &maximum);
		if (input[0] < minimum ||
		    input[0] > maximum) {
			dev_info(adev->dev, "fan minimum pwm setting(%wd) must be within [%d, %d]!\n",
				 input[0], minimum, maximum);
			wetuwn -EINVAW;
		}

		od_tabwe->OvewDwiveTabwe.FanMinimumPwm = input[0];
		od_tabwe->OvewDwiveTabwe.FanMode = FAN_MODE_AUTO;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
		bweak;

	case PP_OD_WESTOWE_DEFAUWT_TABWE:
		if (size == 1) {
			wet = smu_v13_0_0_od_westowe_tabwe_singwe(smu, input[0]);
			if (wet)
				wetuwn wet;
		} ewse {
			featuwe_ctwwmask = od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask;
			memcpy(od_tabwe,
		       tabwe_context->boot_ovewdwive_tabwe,
		       sizeof(OvewDwiveTabweExtewnaw_t));
			od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask = featuwe_ctwwmask;
		}
		fawwthwough;
	case PP_OD_COMMIT_DPM_TABWE:
		/*
		 * The membew bewow instwucts PMFW the settings focused in
		 * this singwe opewation.
		 * `uint32_t FeatuweCtwwMask;`
		 * It does not contain actuaw infowmations about usew's custom
		 * settings. Thus we do not cache it.
		 */
		offset_of_vowtageoffset = offsetof(OvewDwiveTabwe_t, VowtageOffsetPewZoneBoundawy);
		if (memcmp((u8 *)od_tabwe + offset_of_vowtageoffset,
			   tabwe_context->usew_ovewdwive_tabwe + offset_of_vowtageoffset,
			   sizeof(OvewDwiveTabweExtewnaw_t) - offset_of_vowtageoffset)) {
			smu_v13_0_0_dump_od_tabwe(smu, od_tabwe);

			wet = smu_v13_0_0_upwoad_ovewdwive_tabwe(smu, od_tabwe);
			if (wet) {
				dev_eww(adev->dev, "Faiwed to upwoad ovewdwive tabwe!\n");
				wetuwn wet;
			}

			od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask = 0;
			memcpy(tabwe_context->usew_ovewdwive_tabwe + offset_of_vowtageoffset,
			       (u8 *)od_tabwe + offset_of_vowtageoffset,
			       sizeof(OvewDwiveTabweExtewnaw_t) - offset_of_vowtageoffset);

			if (!memcmp(tabwe_context->usew_ovewdwive_tabwe,
				    tabwe_context->boot_ovewdwive_tabwe,
				    sizeof(OvewDwiveTabweExtewnaw_t)))
				smu->usew_dpm_pwofiwe.usew_od = fawse;
			ewse
				smu->usew_dpm_pwofiwe.usew_od = twue;
		}
		bweak;

	defauwt:
		wetuwn -ENOSYS;
	}

	wetuwn wet;
}

static int smu_v13_0_0_fowce_cwk_wevews(stwuct smu_context *smu,
					enum smu_cwk_type cwk_type,
					uint32_t mask)
{
	stwuct smu_dpm_context *smu_dpm = &smu->smu_dpm;
	stwuct smu_13_0_dpm_context *dpm_context = smu_dpm->dpm_context;
	stwuct smu_13_0_dpm_tabwe *singwe_dpm_tabwe;
	uint32_t soft_min_wevew, soft_max_wevew;
	uint32_t min_fweq, max_fweq;
	int wet = 0;

	soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
	soft_max_wevew = mask ? (fws(mask) - 1) : 0;

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.gfx_tabwe);
		bweak;
	case SMU_MCWK:
	case SMU_UCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.ucwk_tabwe);
		bweak;
	case SMU_SOCCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.soc_tabwe);
		bweak;
	case SMU_FCWK:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.fcwk_tabwe);
		bweak;
	case SMU_VCWK:
	case SMU_VCWK1:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.vcwk_tabwe);
		bweak;
	case SMU_DCWK:
	case SMU_DCWK1:
		singwe_dpm_tabwe = &(dpm_context->dpm_tabwes.dcwk_tabwe);
		bweak;
	defauwt:
		bweak;
	}

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
	case SMU_MCWK:
	case SMU_UCWK:
	case SMU_SOCCWK:
	case SMU_FCWK:
	case SMU_VCWK:
	case SMU_VCWK1:
	case SMU_DCWK:
	case SMU_DCWK1:
		if (singwe_dpm_tabwe->is_fine_gwained) {
			/* Thewe is onwy 2 wevews fow fine gwained DPM */
			soft_max_wevew = (soft_max_wevew >= 1 ? 1 : 0);
			soft_min_wevew = (soft_min_wevew >= 1 ? 1 : 0);
		} ewse {
			if ((soft_max_wevew >= singwe_dpm_tabwe->count) ||
			    (soft_min_wevew >= singwe_dpm_tabwe->count))
				wetuwn -EINVAW;
		}

		min_fweq = singwe_dpm_tabwe->dpm_wevews[soft_min_wevew].vawue;
		max_fweq = singwe_dpm_tabwe->dpm_wevews[soft_max_wevew].vawue;

		wet = smu_v13_0_set_soft_fweq_wimited_wange(smu,
							    cwk_type,
							    min_fweq,
							    max_fweq);
		bweak;
	case SMU_DCEFCWK:
	case SMU_PCIE:
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static const stwuct smu_tempewatuwe_wange smu13_thewmaw_powicy[] = {
	{-273150,  99000, 99000, -273150, 99000, 99000, -273150, 99000, 99000},
	{ 120000, 120000, 120000, 120000, 120000, 120000, 120000, 120000, 120000},
};

static int smu_v13_0_0_get_thewmaw_tempewatuwe_wange(stwuct smu_context *smu,
						     stwuct smu_tempewatuwe_wange *wange)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	stwuct smu_13_0_0_powewpway_tabwe *powewpway_tabwe =
		tabwe_context->powew_pway_tabwe;
	PPTabwe_t *pptabwe = smu->smu_tabwe.dwivew_pptabwe;

	if (amdgpu_swiov_vf(smu->adev))
		wetuwn 0;

	if (!wange)
		wetuwn -EINVAW;

	memcpy(wange, &smu13_thewmaw_powicy[0], sizeof(stwuct smu_tempewatuwe_wange));

	wange->max = pptabwe->SkuTabwe.TempewatuweWimit[TEMP_EDGE] *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->edge_emewgency_max = (pptabwe->SkuTabwe.TempewatuweWimit[TEMP_EDGE] + CTF_OFFSET_EDGE) *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->hotspot_cwit_max = pptabwe->SkuTabwe.TempewatuweWimit[TEMP_HOTSPOT] *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->hotspot_emewgency_max = (pptabwe->SkuTabwe.TempewatuweWimit[TEMP_HOTSPOT] + CTF_OFFSET_HOTSPOT) *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->mem_cwit_max = pptabwe->SkuTabwe.TempewatuweWimit[TEMP_MEM] *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->mem_emewgency_max = (pptabwe->SkuTabwe.TempewatuweWimit[TEMP_MEM] + CTF_OFFSET_MEM)*
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wange->softwawe_shutdown_temp = powewpway_tabwe->softwawe_shutdown_temp;
	wange->softwawe_shutdown_temp_offset = pptabwe->SkuTabwe.FanAbnowmawTempWimitOffset;

	wetuwn 0;
}

static ssize_t smu_v13_0_0_get_gpu_metwics(stwuct smu_context *smu,
					   void **tabwe)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct gpu_metwics_v1_3 *gpu_metwics =
		(stwuct gpu_metwics_v1_3 *)smu_tabwe->gpu_metwics_tabwe;
	SmuMetwicsExtewnaw_t metwics_ext;
	SmuMetwics_t *metwics = &metwics_ext.SmuMetwics;
	int wet = 0;

	wet = smu_cmn_get_metwics_tabwe(smu,
					&metwics_ext,
					twue);
	if (wet)
		wetuwn wet;

	smu_cmn_init_soft_gpu_metwics(gpu_metwics, 1, 3);

	gpu_metwics->tempewatuwe_edge = metwics->AvgTempewatuwe[TEMP_EDGE];
	gpu_metwics->tempewatuwe_hotspot = metwics->AvgTempewatuwe[TEMP_HOTSPOT];
	gpu_metwics->tempewatuwe_mem = metwics->AvgTempewatuwe[TEMP_MEM];
	gpu_metwics->tempewatuwe_vwgfx = metwics->AvgTempewatuwe[TEMP_VW_GFX];
	gpu_metwics->tempewatuwe_vwsoc = metwics->AvgTempewatuwe[TEMP_VW_SOC];
	gpu_metwics->tempewatuwe_vwmem = max(metwics->AvgTempewatuwe[TEMP_VW_MEM0],
					     metwics->AvgTempewatuwe[TEMP_VW_MEM1]);

	gpu_metwics->avewage_gfx_activity = metwics->AvewageGfxActivity;
	gpu_metwics->avewage_umc_activity = metwics->AvewageUcwkActivity;
	gpu_metwics->avewage_mm_activity = max(metwics->Vcn0ActivityPewcentage,
					       metwics->Vcn1ActivityPewcentage);

	gpu_metwics->avewage_socket_powew = metwics->AvewageSocketPowew;
	gpu_metwics->enewgy_accumuwatow = metwics->EnewgyAccumuwatow;

	if (metwics->AvewageGfxActivity <= SMU_13_0_0_BUSY_THWESHOWD)
		gpu_metwics->avewage_gfxcwk_fwequency = metwics->AvewageGfxcwkFwequencyPostDs;
	ewse
		gpu_metwics->avewage_gfxcwk_fwequency = metwics->AvewageGfxcwkFwequencyPweDs;

	if (metwics->AvewageUcwkActivity <= SMU_13_0_0_BUSY_THWESHOWD)
		gpu_metwics->avewage_ucwk_fwequency = metwics->AvewageMemcwkFwequencyPostDs;
	ewse
		gpu_metwics->avewage_ucwk_fwequency = metwics->AvewageMemcwkFwequencyPweDs;

	gpu_metwics->avewage_vcwk0_fwequency = metwics->AvewageVcwk0Fwequency;
	gpu_metwics->avewage_dcwk0_fwequency = metwics->AvewageDcwk0Fwequency;
	gpu_metwics->avewage_vcwk1_fwequency = metwics->AvewageVcwk1Fwequency;
	gpu_metwics->avewage_dcwk1_fwequency = metwics->AvewageDcwk1Fwequency;

	gpu_metwics->cuwwent_gfxcwk = gpu_metwics->avewage_gfxcwk_fwequency;
	gpu_metwics->cuwwent_soccwk = metwics->CuwwCwock[PPCWK_SOCCWK];
	gpu_metwics->cuwwent_ucwk = metwics->CuwwCwock[PPCWK_UCWK];
	gpu_metwics->cuwwent_vcwk0 = metwics->CuwwCwock[PPCWK_VCWK_0];
	gpu_metwics->cuwwent_dcwk0 = metwics->CuwwCwock[PPCWK_DCWK_0];
	gpu_metwics->cuwwent_vcwk1 = metwics->CuwwCwock[PPCWK_VCWK_1];
	gpu_metwics->cuwwent_dcwk1 = metwics->CuwwCwock[PPCWK_DCWK_1];

	gpu_metwics->thwottwe_status =
			smu_v13_0_get_thwottwew_status(metwics);
	gpu_metwics->indep_thwottwe_status =
			smu_cmn_get_indep_thwottwew_status(gpu_metwics->thwottwe_status,
							   smu_v13_0_0_thwottwew_map);

	gpu_metwics->cuwwent_fan_speed = metwics->AvgFanWpm;

	gpu_metwics->pcie_wink_width = metwics->PcieWidth;
	if ((metwics->PcieWate - 1) > WINK_SPEED_MAX)
		gpu_metwics->pcie_wink_speed = pcie_gen_to_speed(1);
	ewse
		gpu_metwics->pcie_wink_speed = pcie_gen_to_speed(metwics->PcieWate);

	gpu_metwics->system_cwock_countew = ktime_get_boottime_ns();

	gpu_metwics->vowtage_gfx = metwics->AvgVowtage[SVI_PWANE_GFX];
	gpu_metwics->vowtage_soc = metwics->AvgVowtage[SVI_PWANE_SOC];
	gpu_metwics->vowtage_mem = metwics->AvgVowtage[SVI_PWANE_VMEMP];

	*tabwe = (void *)gpu_metwics;

	wetuwn sizeof(stwuct gpu_metwics_v1_3);
}

static void smu_v13_0_0_set_suppowted_od_featuwe_mask(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	if (smu_v13_0_0_is_od_featuwe_suppowted(smu,
						PP_OD_FEATUWE_FAN_CUWVE_BIT))
		adev->pm.od_featuwe_mask |= OD_OPS_SUPPOWT_FAN_CUWVE_WETWIEVE |
					    OD_OPS_SUPPOWT_FAN_CUWVE_SET |
					    OD_OPS_SUPPOWT_ACOUSTIC_WIMIT_THWESHOWD_WETWIEVE |
					    OD_OPS_SUPPOWT_ACOUSTIC_WIMIT_THWESHOWD_SET |
					    OD_OPS_SUPPOWT_ACOUSTIC_TAWGET_THWESHOWD_WETWIEVE |
					    OD_OPS_SUPPOWT_ACOUSTIC_TAWGET_THWESHOWD_SET |
					    OD_OPS_SUPPOWT_FAN_TAWGET_TEMPEWATUWE_WETWIEVE |
					    OD_OPS_SUPPOWT_FAN_TAWGET_TEMPEWATUWE_SET |
					    OD_OPS_SUPPOWT_FAN_MINIMUM_PWM_WETWIEVE |
					    OD_OPS_SUPPOWT_FAN_MINIMUM_PWM_SET;
}

static int smu_v13_0_0_set_defauwt_od_settings(stwuct smu_context *smu)
{
	OvewDwiveTabweExtewnaw_t *od_tabwe =
		(OvewDwiveTabweExtewnaw_t *)smu->smu_tabwe.ovewdwive_tabwe;
	OvewDwiveTabweExtewnaw_t *boot_od_tabwe =
		(OvewDwiveTabweExtewnaw_t *)smu->smu_tabwe.boot_ovewdwive_tabwe;
	OvewDwiveTabweExtewnaw_t *usew_od_tabwe =
		(OvewDwiveTabweExtewnaw_t *)smu->smu_tabwe.usew_ovewdwive_tabwe;
	OvewDwiveTabweExtewnaw_t usew_od_tabwe_bak;
	int wet = 0;
	int i;

	wet = smu_v13_0_0_get_ovewdwive_tabwe(smu, boot_od_tabwe);
	if (wet)
		wetuwn wet;

	smu_v13_0_0_dump_od_tabwe(smu, boot_od_tabwe);

	memcpy(od_tabwe,
	       boot_od_tabwe,
	       sizeof(OvewDwiveTabweExtewnaw_t));

	/*
	 * Fow S3/S4/Wunpm wesume, we need to setup those ovewdwive tabwes again,
	 * but we have to pwesewve usew defined vawues in "usew_od_tabwe".
	 */
	if (!smu->adev->in_suspend) {
		memcpy(usew_od_tabwe,
		       boot_od_tabwe,
		       sizeof(OvewDwiveTabweExtewnaw_t));
		smu->usew_dpm_pwofiwe.usew_od = fawse;
	} ewse if (smu->usew_dpm_pwofiwe.usew_od) {
		memcpy(&usew_od_tabwe_bak,
		       usew_od_tabwe,
		       sizeof(OvewDwiveTabweExtewnaw_t));
		memcpy(usew_od_tabwe,
		       boot_od_tabwe,
		       sizeof(OvewDwiveTabweExtewnaw_t));
		usew_od_tabwe->OvewDwiveTabwe.GfxcwkFmin =
				usew_od_tabwe_bak.OvewDwiveTabwe.GfxcwkFmin;
		usew_od_tabwe->OvewDwiveTabwe.GfxcwkFmax =
				usew_od_tabwe_bak.OvewDwiveTabwe.GfxcwkFmax;
		usew_od_tabwe->OvewDwiveTabwe.UcwkFmin =
				usew_od_tabwe_bak.OvewDwiveTabwe.UcwkFmin;
		usew_od_tabwe->OvewDwiveTabwe.UcwkFmax =
				usew_od_tabwe_bak.OvewDwiveTabwe.UcwkFmax;
		fow (i = 0; i < PP_NUM_OD_VF_CUWVE_POINTS; i++)
			usew_od_tabwe->OvewDwiveTabwe.VowtageOffsetPewZoneBoundawy[i] =
				usew_od_tabwe_bak.OvewDwiveTabwe.VowtageOffsetPewZoneBoundawy[i];
		fow (i = 0; i < NUM_OD_FAN_MAX_POINTS - 1; i++) {
			usew_od_tabwe->OvewDwiveTabwe.FanWineawTempPoints[i] =
				usew_od_tabwe_bak.OvewDwiveTabwe.FanWineawTempPoints[i];
			usew_od_tabwe->OvewDwiveTabwe.FanWineawPwmPoints[i] =
				usew_od_tabwe_bak.OvewDwiveTabwe.FanWineawPwmPoints[i];
		}
		usew_od_tabwe->OvewDwiveTabwe.AcousticWimitWpmThweshowd =
			usew_od_tabwe_bak.OvewDwiveTabwe.AcousticWimitWpmThweshowd;
		usew_od_tabwe->OvewDwiveTabwe.AcousticTawgetWpmThweshowd =
			usew_od_tabwe_bak.OvewDwiveTabwe.AcousticTawgetWpmThweshowd;
		usew_od_tabwe->OvewDwiveTabwe.FanTawgetTempewatuwe =
			usew_od_tabwe_bak.OvewDwiveTabwe.FanTawgetTempewatuwe;
		usew_od_tabwe->OvewDwiveTabwe.FanMinimumPwm =
			usew_od_tabwe_bak.OvewDwiveTabwe.FanMinimumPwm;
	}

	smu_v13_0_0_set_suppowted_od_featuwe_mask(smu);

	wetuwn 0;
}

static int smu_v13_0_0_westowe_usew_od_settings(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	OvewDwiveTabweExtewnaw_t *od_tabwe = tabwe_context->ovewdwive_tabwe;
	OvewDwiveTabweExtewnaw_t *usew_od_tabwe = tabwe_context->usew_ovewdwive_tabwe;
	int wes;

	usew_od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask = BIT(PP_OD_FEATUWE_GFXCWK_BIT) |
							BIT(PP_OD_FEATUWE_UCWK_BIT) |
							BIT(PP_OD_FEATUWE_GFX_VF_CUWVE_BIT) |
							BIT(PP_OD_FEATUWE_FAN_CUWVE_BIT);
	wes = smu_v13_0_0_upwoad_ovewdwive_tabwe(smu, usew_od_tabwe);
	usew_od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask = 0;
	if (wes == 0)
		memcpy(od_tabwe, usew_od_tabwe, sizeof(OvewDwiveTabweExtewnaw_t));

	wetuwn wes;
}

static int smu_v13_0_0_popuwate_umd_state_cwk(stwuct smu_context *smu)
{
	stwuct smu_13_0_dpm_context *dpm_context =
				smu->smu_dpm.dpm_context;
	stwuct smu_13_0_dpm_tabwe *gfx_tabwe =
				&dpm_context->dpm_tabwes.gfx_tabwe;
	stwuct smu_13_0_dpm_tabwe *mem_tabwe =
				&dpm_context->dpm_tabwes.ucwk_tabwe;
	stwuct smu_13_0_dpm_tabwe *soc_tabwe =
				&dpm_context->dpm_tabwes.soc_tabwe;
	stwuct smu_13_0_dpm_tabwe *vcwk_tabwe =
				&dpm_context->dpm_tabwes.vcwk_tabwe;
	stwuct smu_13_0_dpm_tabwe *dcwk_tabwe =
				&dpm_context->dpm_tabwes.dcwk_tabwe;
	stwuct smu_13_0_dpm_tabwe *fcwk_tabwe =
				&dpm_context->dpm_tabwes.fcwk_tabwe;
	stwuct smu_umd_pstate_tabwe *pstate_tabwe =
				&smu->pstate_tabwe;
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	PPTabwe_t *pptabwe = tabwe_context->dwivew_pptabwe;
	DwivewWepowtedCwocks_t dwivew_cwocks =
			pptabwe->SkuTabwe.DwivewWepowtedCwocks;

	pstate_tabwe->gfxcwk_pstate.min = gfx_tabwe->min;
	if (dwivew_cwocks.GameCwockAc &&
	    (dwivew_cwocks.GameCwockAc < gfx_tabwe->max))
		pstate_tabwe->gfxcwk_pstate.peak = dwivew_cwocks.GameCwockAc;
	ewse
		pstate_tabwe->gfxcwk_pstate.peak = gfx_tabwe->max;

	pstate_tabwe->ucwk_pstate.min = mem_tabwe->min;
	pstate_tabwe->ucwk_pstate.peak = mem_tabwe->max;

	pstate_tabwe->soccwk_pstate.min = soc_tabwe->min;
	pstate_tabwe->soccwk_pstate.peak = soc_tabwe->max;

	pstate_tabwe->vcwk_pstate.min = vcwk_tabwe->min;
	pstate_tabwe->vcwk_pstate.peak = vcwk_tabwe->max;

	pstate_tabwe->dcwk_pstate.min = dcwk_tabwe->min;
	pstate_tabwe->dcwk_pstate.peak = dcwk_tabwe->max;

	pstate_tabwe->fcwk_pstate.min = fcwk_tabwe->min;
	pstate_tabwe->fcwk_pstate.peak = fcwk_tabwe->max;

	if (dwivew_cwocks.BaseCwockAc &&
	    dwivew_cwocks.BaseCwockAc < gfx_tabwe->max)
		pstate_tabwe->gfxcwk_pstate.standawd = dwivew_cwocks.BaseCwockAc;
	ewse
		pstate_tabwe->gfxcwk_pstate.standawd = gfx_tabwe->max;
	pstate_tabwe->ucwk_pstate.standawd = mem_tabwe->max;
	pstate_tabwe->soccwk_pstate.standawd = soc_tabwe->min;
	pstate_tabwe->vcwk_pstate.standawd = vcwk_tabwe->min;
	pstate_tabwe->dcwk_pstate.standawd = dcwk_tabwe->min;
	pstate_tabwe->fcwk_pstate.standawd = fcwk_tabwe->min;

	wetuwn 0;
}

static void smu_v13_0_0_get_unique_id(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	SmuMetwics_t *metwics =
		&(((SmuMetwicsExtewnaw_t *)(smu_tabwe->metwics_tabwe))->SmuMetwics);
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t uppew32 = 0, wowew32 = 0;
	int wet;

	wet = smu_cmn_get_metwics_tabwe(smu, NUWW, fawse);
	if (wet)
		goto out;

	uppew32 = metwics->PubwicSewiawNumbewUppew;
	wowew32 = metwics->PubwicSewiawNumbewWowew;

out:
	adev->unique_id = ((uint64_t)uppew32 << 32) | wowew32;
}

static int smu_v13_0_0_get_fan_speed_pwm(stwuct smu_context *smu,
					 uint32_t *speed)
{
	int wet;

	if (!speed)
		wetuwn -EINVAW;

	wet = smu_v13_0_0_get_smu_metwics_data(smu,
					       METWICS_CUWW_FANPWM,
					       speed);
	if (wet) {
		dev_eww(smu->adev->dev, "Faiwed to get fan speed(PWM)!");
		wetuwn wet;
	}

	/* Convewt the PMFW output which is in pewcent to pwm(255) based */
	*speed = min(*speed * 255 / 100, (uint32_t)255);

	wetuwn 0;
}

static int smu_v13_0_0_get_fan_speed_wpm(stwuct smu_context *smu,
					 uint32_t *speed)
{
	if (!speed)
		wetuwn -EINVAW;

	wetuwn smu_v13_0_0_get_smu_metwics_data(smu,
						METWICS_CUWW_FANSPEED,
						speed);
}

static int smu_v13_0_0_enabwe_mgpu_fan_boost(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	PPTabwe_t *pptabwe = tabwe_context->dwivew_pptabwe;
	SkuTabwe_t *skutabwe = &pptabwe->SkuTabwe;

	/*
	 * Skip the MGpuFanBoost setting fow those ASICs
	 * which do not suppowt it
	 */
	if (skutabwe->MGpuAcousticWimitWpmThweshowd == 0)
		wetuwn 0;

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
					       SMU_MSG_SetMGpuFanBoostWimitWpm,
					       0,
					       NUWW);
}

static int smu_v13_0_0_get_powew_wimit(stwuct smu_context *smu,
						uint32_t *cuwwent_powew_wimit,
						uint32_t *defauwt_powew_wimit,
						uint32_t *max_powew_wimit,
						uint32_t *min_powew_wimit)
{
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	stwuct smu_13_0_0_powewpway_tabwe *powewpway_tabwe =
		(stwuct smu_13_0_0_powewpway_tabwe *)tabwe_context->powew_pway_tabwe;
	PPTabwe_t *pptabwe = tabwe_context->dwivew_pptabwe;
	SkuTabwe_t *skutabwe = &pptabwe->SkuTabwe;
	uint32_t powew_wimit, od_pewcent_uppew, od_pewcent_wowew;
	uint32_t msg_wimit = skutabwe->MsgWimits.Powew[PPT_THWOTTWEW_PPT0][POWEW_SOUWCE_AC];

	if (smu_v13_0_get_cuwwent_powew_wimit(smu, &powew_wimit))
		powew_wimit = smu->adev->pm.ac_powew ?
			      skutabwe->SocketPowewWimitAc[PPT_THWOTTWEW_PPT0] :
			      skutabwe->SocketPowewWimitDc[PPT_THWOTTWEW_PPT0];

	if (cuwwent_powew_wimit)
		*cuwwent_powew_wimit = powew_wimit;
	if (defauwt_powew_wimit)
		*defauwt_powew_wimit = powew_wimit;

	if (smu->od_enabwed) {
		od_pewcent_uppew = we32_to_cpu(powewpway_tabwe->ovewdwive_tabwe.max[SMU_13_0_0_ODSETTING_POWEWPEWCENTAGE]);
		od_pewcent_wowew = we32_to_cpu(powewpway_tabwe->ovewdwive_tabwe.min[SMU_13_0_0_ODSETTING_POWEWPEWCENTAGE]);
	} ewse {
		od_pewcent_uppew = 0;
		od_pewcent_wowew = 100;
	}

	dev_dbg(smu->adev->dev, "od pewcent uppew:%d, od pewcent wowew:%d (defauwt powew: %d)\n",
					od_pewcent_uppew, od_pewcent_wowew, powew_wimit);

	if (max_powew_wimit) {
		*max_powew_wimit = msg_wimit * (100 + od_pewcent_uppew);
		*max_powew_wimit /= 100;
	}

	if (min_powew_wimit) {
		*min_powew_wimit = powew_wimit * (100 - od_pewcent_wowew);
		*min_powew_wimit /= 100;
	}

	wetuwn 0;
}

static int smu_v13_0_0_get_powew_pwofiwe_mode(stwuct smu_context *smu,
					      chaw *buf)
{
	DpmActivityMonitowCoeffIntExtewnaw_t activity_monitow_extewnaw;
	DpmActivityMonitowCoeffInt_t *activity_monitow =
		&(activity_monitow_extewnaw.DpmActivityMonitowCoeffInt);
	static const chaw *titwe[] = {
			"PWOFIWE_INDEX(NAME)",
			"CWOCK_TYPE(NAME)",
			"FPS",
			"MinActiveFweqType",
			"MinActiveFweq",
			"BoostewFweqType",
			"BoostewFweq",
			"PD_Data_wimit_c",
			"PD_Data_ewwow_coeff",
			"PD_Data_ewwow_wate_coeff"};
	int16_t wowkwoad_type = 0;
	uint32_t i, size = 0;
	int wesuwt = 0;

	if (!buf)
		wetuwn -EINVAW;

	size += sysfs_emit_at(buf, size, "%16s %s %s %s %s %s %s %s %s %s\n",
			titwe[0], titwe[1], titwe[2], titwe[3], titwe[4], titwe[5],
			titwe[6], titwe[7], titwe[8], titwe[9]);

	fow (i = 0; i < PP_SMC_POWEW_PWOFIWE_COUNT; i++) {
		/* conv PP_SMC_POWEW_PWOFIWE* to WOWKWOAD_PPWIB_*_BIT */
		wowkwoad_type = smu_cmn_to_asic_specific_index(smu,
							       CMN2ASIC_MAPPING_WOWKWOAD,
							       i);
		if (wowkwoad_type == -ENOTSUPP)
			continue;
		ewse if (wowkwoad_type < 0)
			wetuwn -EINVAW;

		wesuwt = smu_cmn_update_tabwe(smu,
					      SMU_TABWE_ACTIVITY_MONITOW_COEFF,
					      wowkwoad_type,
					      (void *)(&activity_monitow_extewnaw),
					      fawse);
		if (wesuwt) {
			dev_eww(smu->adev->dev, "[%s] Faiwed to get activity monitow!", __func__);
			wetuwn wesuwt;
		}

		size += sysfs_emit_at(buf, size, "%2d %14s%s:\n",
			i, amdgpu_pp_pwofiwe_name[i], (i == smu->powew_pwofiwe_mode) ? "*" : " ");

		size += sysfs_emit_at(buf, size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			0,
			"GFXCWK",
			activity_monitow->Gfx_FPS,
			activity_monitow->Gfx_MinActiveFweqType,
			activity_monitow->Gfx_MinActiveFweq,
			activity_monitow->Gfx_BoostewFweqType,
			activity_monitow->Gfx_BoostewFweq,
			activity_monitow->Gfx_PD_Data_wimit_c,
			activity_monitow->Gfx_PD_Data_ewwow_coeff,
			activity_monitow->Gfx_PD_Data_ewwow_wate_coeff);

		size += sysfs_emit_at(buf, size, "%19s %d(%13s) %7d %7d %7d %7d %7d %7d %7d %7d\n",
			" ",
			1,
			"FCWK",
			activity_monitow->Fcwk_FPS,
			activity_monitow->Fcwk_MinActiveFweqType,
			activity_monitow->Fcwk_MinActiveFweq,
			activity_monitow->Fcwk_BoostewFweqType,
			activity_monitow->Fcwk_BoostewFweq,
			activity_monitow->Fcwk_PD_Data_wimit_c,
			activity_monitow->Fcwk_PD_Data_ewwow_coeff,
			activity_monitow->Fcwk_PD_Data_ewwow_wate_coeff);
	}

	wetuwn size;
}

static int smu_v13_0_0_set_powew_pwofiwe_mode(stwuct smu_context *smu,
					      wong *input,
					      uint32_t size)
{
	DpmActivityMonitowCoeffIntExtewnaw_t activity_monitow_extewnaw;
	DpmActivityMonitowCoeffInt_t *activity_monitow =
		&(activity_monitow_extewnaw.DpmActivityMonitowCoeffInt);
	int wowkwoad_type, wet = 0;
	u32 wowkwoad_mask;

	smu->powew_pwofiwe_mode = input[size];

	if (smu->powew_pwofiwe_mode >= PP_SMC_POWEW_PWOFIWE_COUNT) {
		dev_eww(smu->adev->dev, "Invawid powew pwofiwe mode %d\n", smu->powew_pwofiwe_mode);
		wetuwn -EINVAW;
	}

	if (smu->powew_pwofiwe_mode == PP_SMC_POWEW_PWOFIWE_CUSTOM) {
		wet = smu_cmn_update_tabwe(smu,
					   SMU_TABWE_ACTIVITY_MONITOW_COEFF,
					   WOWKWOAD_PPWIB_CUSTOM_BIT,
					   (void *)(&activity_monitow_extewnaw),
					   fawse);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] Faiwed to get activity monitow!", __func__);
			wetuwn wet;
		}

		switch (input[0]) {
		case 0: /* Gfxcwk */
			activity_monitow->Gfx_FPS = input[1];
			activity_monitow->Gfx_MinActiveFweqType = input[2];
			activity_monitow->Gfx_MinActiveFweq = input[3];
			activity_monitow->Gfx_BoostewFweqType = input[4];
			activity_monitow->Gfx_BoostewFweq = input[5];
			activity_monitow->Gfx_PD_Data_wimit_c = input[6];
			activity_monitow->Gfx_PD_Data_ewwow_coeff = input[7];
			activity_monitow->Gfx_PD_Data_ewwow_wate_coeff = input[8];
			bweak;
		case 1: /* Fcwk */
			activity_monitow->Fcwk_FPS = input[1];
			activity_monitow->Fcwk_MinActiveFweqType = input[2];
			activity_monitow->Fcwk_MinActiveFweq = input[3];
			activity_monitow->Fcwk_BoostewFweqType = input[4];
			activity_monitow->Fcwk_BoostewFweq = input[5];
			activity_monitow->Fcwk_PD_Data_wimit_c = input[6];
			activity_monitow->Fcwk_PD_Data_ewwow_coeff = input[7];
			activity_monitow->Fcwk_PD_Data_ewwow_wate_coeff = input[8];
			bweak;
		}

		wet = smu_cmn_update_tabwe(smu,
					   SMU_TABWE_ACTIVITY_MONITOW_COEFF,
					   WOWKWOAD_PPWIB_CUSTOM_BIT,
					   (void *)(&activity_monitow_extewnaw),
					   twue);
		if (wet) {
			dev_eww(smu->adev->dev, "[%s] Faiwed to set activity monitow!", __func__);
			wetuwn wet;
		}
	}

	/* conv PP_SMC_POWEW_PWOFIWE* to WOWKWOAD_PPWIB_*_BIT */
	wowkwoad_type = smu_cmn_to_asic_specific_index(smu,
						       CMN2ASIC_MAPPING_WOWKWOAD,
						       smu->powew_pwofiwe_mode);

	if (wowkwoad_type < 0)
		wetuwn -EINVAW;

	wowkwoad_mask = 1 << wowkwoad_type;

	/* Add optimizations fow SMU13.0.0/10.  Weuse the powew saving pwofiwe */
	if (smu->powew_pwofiwe_mode == PP_SMC_POWEW_PWOFIWE_COMPUTE) {
		if ((amdgpu_ip_vewsion(smu->adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 0) &&
			((smu->adev->pm.fw_vewsion == 0x004e6601) ||
			(smu->adev->pm.fw_vewsion >= 0x004e7300))) ||
			(amdgpu_ip_vewsion(smu->adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 10) &&
			 smu->adev->pm.fw_vewsion >= 0x00504500)) {
			wowkwoad_type = smu_cmn_to_asic_specific_index(smu,
														   CMN2ASIC_MAPPING_WOWKWOAD,
														   PP_SMC_POWEW_PWOFIWE_POWEWSAVING);
			if (wowkwoad_type >= 0)
				wowkwoad_mask |= 1 << wowkwoad_type;
		}
	}

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
					       SMU_MSG_SetWowkwoadMask,
					       wowkwoad_mask,
					       NUWW);
}

static boow smu_v13_0_0_is_mode1_weset_suppowted(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	u32 smu_vewsion;
	int wet;

	/* SWIOV does not suppowt SMU mode1 weset */
	if (amdgpu_swiov_vf(adev))
		wetuwn fawse;

	/* PMFW suppowt is avaiwabwe since 78.41 */
	wet = smu_cmn_get_smc_vewsion(smu, NUWW, &smu_vewsion);
	if (wet)
		wetuwn fawse;

	if (smu_vewsion < 0x004e2900)
		wetuwn fawse;

	wetuwn twue;
}

static int smu_v13_0_0_i2c_xfew(stwuct i2c_adaptew *i2c_adap,
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

			msg[i].buf[j] = cmd->WeadWwiteData;
		}
	}
	w = num_msgs;
faiw:
	mutex_unwock(&adev->pm.mutex);
	kfwee(weq);
	wetuwn w;
}

static u32 smu_v13_0_0_i2c_func(stwuct i2c_adaptew *adap)
{
	wetuwn I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUW;
}

static const stwuct i2c_awgowithm smu_v13_0_0_i2c_awgo = {
	.mastew_xfew = smu_v13_0_0_i2c_xfew,
	.functionawity = smu_v13_0_0_i2c_func,
};

static const stwuct i2c_adaptew_quiwks smu_v13_0_0_i2c_contwow_quiwks = {
	.fwags = I2C_AQ_COMB | I2C_AQ_COMB_SAME_ADDW | I2C_AQ_NO_ZEWO_WEN,
	.max_wead_wen  = MAX_SW_I2C_COMMANDS,
	.max_wwite_wen = MAX_SW_I2C_COMMANDS,
	.max_comb_1st_msg_wen = 2,
	.max_comb_2nd_msg_wen = MAX_SW_I2C_COMMANDS - 2,
};

static int smu_v13_0_0_i2c_contwow_init(stwuct smu_context *smu)
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
		contwow->awgo = &smu_v13_0_0_i2c_awgo;
		snpwintf(contwow->name, sizeof(contwow->name), "AMDGPU SMU %d", i);
		contwow->quiwks = &smu_v13_0_0_i2c_contwow_quiwks;
		i2c_set_adapdata(contwow, smu_i2c);

		wes = i2c_add_adaptew(contwow);
		if (wes) {
			DWM_EWWOW("Faiwed to wegistew hw i2c, eww: %d\n", wes);
			goto Out_eww;
		}
	}

	/* assign the buses used fow the FWU EEPWOM and WAS EEPWOM */
	/* XXX ideawwy this wouwd be something in a vbios data tabwe */
	adev->pm.was_eepwom_i2c_bus = &adev->pm.smu_i2c[1].adaptew;
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

static void smu_v13_0_0_i2c_contwow_fini(stwuct smu_context *smu)
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

static int smu_v13_0_0_set_mp1_state(stwuct smu_context *smu,
				     enum pp_mp1_state mp1_state)
{
	int wet;

	switch (mp1_state) {
	case PP_MP1_STATE_UNWOAD:
		wet = smu_cmn_set_mp1_state(smu, mp1_state);
		bweak;
	defauwt:
		/* Ignowe othews */
		wet = 0;
	}

	wetuwn wet;
}

static int smu_v13_0_0_set_df_cstate(stwuct smu_context *smu,
				     enum pp_df_cstate state)
{
	wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
					       SMU_MSG_DFCstateContwow,
					       state,
					       NUWW);
}

static void smu_v13_0_0_set_mode1_weset_pawam(stwuct smu_context *smu,
						uint32_t suppowted_vewsion,
						uint32_t *pawam)
{
	stwuct amdgpu_device *adev = smu->adev;
	stwuct amdgpu_was *was = amdgpu_was_get_context(adev);

	if ((smu->smc_fw_vewsion >= suppowted_vewsion) &&
			was && atomic_wead(&was->in_wecovewy))
		/* Set WAS fataw ewwow weset fwag */
		*pawam = 1 << 16;
	ewse
		*pawam = 0;
}

static int smu_v13_0_0_mode1_weset(stwuct smu_context *smu)
{
	int wet;
	uint32_t pawam;
	stwuct amdgpu_device *adev = smu->adev;

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(13, 0, 0):
		/* SMU 13_0_0 PMFW suppowts WAS fataw ewwow weset fwom 78.77 */
		smu_v13_0_0_set_mode1_weset_pawam(smu, 0x004e4d00, &pawam);

		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						SMU_MSG_Mode1Weset, pawam, NUWW);
		bweak;

	case IP_VEWSION(13, 0, 10):
		/* SMU 13_0_10 PMFW suppowts WAS fataw ewwow weset fwom 80.28 */
		smu_v13_0_0_set_mode1_weset_pawam(smu, 0x00501c00, &pawam);

		wet = smu_cmn_send_debug_smc_msg_with_pawam(smu,
						DEBUGSMC_MSG_Mode1Weset, pawam);
		bweak;

	defauwt:
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_Mode1Weset, NUWW);
		bweak;
	}

	if (!wet)
		msweep(SMU13_MODE1_WESET_WAIT_TIME_IN_MS);

	wetuwn wet;
}

static int smu_v13_0_0_mode2_weset(stwuct smu_context *smu)
{
	int wet;
	stwuct amdgpu_device *adev = smu->adev;

	if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 10))
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_Mode2Weset, NUWW);
	ewse
		wetuwn -EOPNOTSUPP;

	wetuwn wet;
}

static int smu_v13_0_0_enabwe_gfx_featuwes(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 10))
		wetuwn smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_EnabweAwwSmuFeatuwes,
										   FEATUWE_PWW_GFX, NUWW);
	ewse
		wetuwn -EOPNOTSUPP;
}

static void smu_v13_0_0_set_smu_maiwbox_wegistews(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	smu->pawam_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_82);
	smu->msg_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_66);
	smu->wesp_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);

	smu->debug_pawam_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_53);
	smu->debug_msg_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_75);
	smu->debug_wesp_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_54);
}

static int smu_v13_0_0_smu_send_bad_mem_page_num(stwuct smu_context *smu,
		uint32_t size)
{
	int wet = 0;

	/* message SMU to update the bad page numbew on SMUBUS */
	wet = smu_cmn_send_smc_msg_with_pawam(smu,
					  SMU_MSG_SetNumBadMemowyPagesWetiwed,
					  size, NUWW);
	if (wet)
		dev_eww(smu->adev->dev,
			  "[%s] faiwed to message SMU to update bad memowy pages numbew\n",
			  __func__);

	wetuwn wet;
}

static int smu_v13_0_0_send_bad_mem_channew_fwag(stwuct smu_context *smu,
		uint32_t size)
{
	int wet = 0;

	/* message SMU to update the bad channew info on SMUBUS */
	wet = smu_cmn_send_smc_msg_with_pawam(smu,
				  SMU_MSG_SetBadMemowyPagesWetiwedFwagsPewChannew,
				  size, NUWW);
	if (wet)
		dev_eww(smu->adev->dev,
			  "[%s] faiwed to message SMU to update bad memowy pages channew info\n",
			  __func__);

	wetuwn wet;
}

static int smu_v13_0_0_check_ecc_tabwe_suppowt(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if ((amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 10)) &&
		(smu->smc_fw_vewsion >= SUPPOWT_ECCTABWE_SMU_13_0_10_VEWSION))
		wetuwn wet;
	ewse
		wetuwn -EOPNOTSUPP;
}

static ssize_t smu_v13_0_0_get_ecc_info(stwuct smu_context *smu,
									void *tabwe)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct amdgpu_device *adev = smu->adev;
	EccInfoTabwe_t *ecc_tabwe = NUWW;
	stwuct ecc_info_pew_ch *ecc_info_pew_channew = NUWW;
	int i, wet = 0;
	stwuct umc_ecc_info *eccinfo = (stwuct umc_ecc_info *)tabwe;

	wet = smu_v13_0_0_check_ecc_tabwe_suppowt(smu);
	if (wet)
		wetuwn wet;

	wet = smu_cmn_update_tabwe(smu,
					SMU_TABWE_ECCINFO,
					0,
					smu_tabwe->ecc_tabwe,
					fawse);
	if (wet) {
		dev_info(adev->dev, "Faiwed to expowt SMU ecc tabwe!\n");
		wetuwn wet;
	}

	ecc_tabwe = (EccInfoTabwe_t *)smu_tabwe->ecc_tabwe;

	fow (i = 0; i < AWWAY_SIZE(ecc_tabwe->EccInfo); i++) {
		ecc_info_pew_channew = &(eccinfo->ecc[i]);
		ecc_info_pew_channew->ce_count_wo_chip =
				ecc_tabwe->EccInfo[i].ce_count_wo_chip;
		ecc_info_pew_channew->ce_count_hi_chip =
				ecc_tabwe->EccInfo[i].ce_count_hi_chip;
		ecc_info_pew_channew->mca_umc_status =
				ecc_tabwe->EccInfo[i].mca_umc_status;
		ecc_info_pew_channew->mca_umc_addw =
				ecc_tabwe->EccInfo[i].mca_umc_addw;
	}

	wetuwn wet;
}

static boow smu_v13_0_0_wbwf_suppowt_check(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	switch (amdgpu_ip_vewsion(adev, MP1_HWIP, 0)) {
	case IP_VEWSION(13, 0, 0):
		wetuwn smu->smc_fw_vewsion >= 0x004e6300;
	case IP_VEWSION(13, 0, 10):
		wetuwn smu->smc_fw_vewsion >= 0x00503300;
	defauwt:
		wetuwn fawse;
	}
}

static int smu_v13_0_0_set_powew_wimit(stwuct smu_context *smu,
				       enum smu_ppt_wimit_type wimit_type,
				       uint32_t wimit)
{
	PPTabwe_t *pptabwe = smu->smu_tabwe.dwivew_pptabwe;
	SkuTabwe_t *skutabwe = &pptabwe->SkuTabwe;
	uint32_t msg_wimit = skutabwe->MsgWimits.Powew[PPT_THWOTTWEW_PPT0][POWEW_SOUWCE_AC];
	stwuct smu_tabwe_context *tabwe_context = &smu->smu_tabwe;
	OvewDwiveTabweExtewnaw_t *od_tabwe =
		(OvewDwiveTabweExtewnaw_t *)tabwe_context->ovewdwive_tabwe;
	int wet = 0;

	if (wimit_type != SMU_DEFAUWT_PPT_WIMIT)
		wetuwn -EINVAW;

	if (wimit <= msg_wimit) {
		if (smu->cuwwent_powew_wimit > msg_wimit) {
			od_tabwe->OvewDwiveTabwe.Ppt = 0;
			od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= 1U << PP_OD_FEATUWE_PPT_BIT;

			wet = smu_v13_0_0_upwoad_ovewdwive_tabwe(smu, od_tabwe);
			if (wet) {
				dev_eww(smu->adev->dev, "Faiwed to upwoad ovewdwive tabwe!\n");
				wetuwn wet;
			}
		}
		wetuwn smu_v13_0_set_powew_wimit(smu, wimit_type, wimit);
	} ewse if (smu->od_enabwed) {
		wet = smu_v13_0_set_powew_wimit(smu, wimit_type, msg_wimit);
		if (wet)
			wetuwn wet;

		od_tabwe->OvewDwiveTabwe.Ppt = (wimit * 100) / msg_wimit - 100;
		od_tabwe->OvewDwiveTabwe.FeatuweCtwwMask |= 1U << PP_OD_FEATUWE_PPT_BIT;

		wet = smu_v13_0_0_upwoad_ovewdwive_tabwe(smu, od_tabwe);
		if (wet) {
		  dev_eww(smu->adev->dev, "Faiwed to upwoad ovewdwive tabwe!\n");
		  wetuwn wet;
		}

		smu->cuwwent_powew_wimit = wimit;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct pptabwe_funcs smu_v13_0_0_ppt_funcs = {
	.get_awwowed_featuwe_mask = smu_v13_0_0_get_awwowed_featuwe_mask,
	.set_defauwt_dpm_tabwe = smu_v13_0_0_set_defauwt_dpm_tabwe,
	.i2c_init = smu_v13_0_0_i2c_contwow_init,
	.i2c_fini = smu_v13_0_0_i2c_contwow_fini,
	.is_dpm_wunning = smu_v13_0_0_is_dpm_wunning,
	.dump_pptabwe = smu_v13_0_0_dump_pptabwe,
	.init_micwocode = smu_v13_0_init_micwocode,
	.woad_micwocode = smu_v13_0_woad_micwocode,
	.fini_micwocode = smu_v13_0_fini_micwocode,
	.init_smc_tabwes = smu_v13_0_0_init_smc_tabwes,
	.fini_smc_tabwes = smu_v13_0_fini_smc_tabwes,
	.init_powew = smu_v13_0_init_powew,
	.fini_powew = smu_v13_0_fini_powew,
	.check_fw_status = smu_v13_0_check_fw_status,
	.setup_pptabwe = smu_v13_0_0_setup_pptabwe,
	.check_fw_vewsion = smu_v13_0_check_fw_vewsion,
	.wwite_pptabwe = smu_cmn_wwite_pptabwe,
	.set_dwivew_tabwe_wocation = smu_v13_0_set_dwivew_tabwe_wocation,
	.system_featuwes_contwow = smu_v13_0_0_system_featuwes_contwow,
	.set_awwowed_mask = smu_v13_0_set_awwowed_mask,
	.get_enabwed_mask = smu_cmn_get_enabwed_mask,
	.dpm_set_vcn_enabwe = smu_v13_0_set_vcn_enabwe,
	.dpm_set_jpeg_enabwe = smu_v13_0_set_jpeg_enabwe,
	.get_dpm_uwtimate_fweq = smu_v13_0_0_get_dpm_uwtimate_fweq,
	.get_vbios_bootup_vawues = smu_v13_0_get_vbios_bootup_vawues,
	.wead_sensow = smu_v13_0_0_wead_sensow,
	.featuwe_is_enabwed = smu_cmn_featuwe_is_enabwed,
	.pwint_cwk_wevews = smu_v13_0_0_pwint_cwk_wevews,
	.fowce_cwk_wevews = smu_v13_0_0_fowce_cwk_wevews,
	.update_pcie_pawametews = smu_v13_0_update_pcie_pawametews,
	.get_thewmaw_tempewatuwe_wange = smu_v13_0_0_get_thewmaw_tempewatuwe_wange,
	.wegistew_iwq_handwew = smu_v13_0_wegistew_iwq_handwew,
	.enabwe_thewmaw_awewt = smu_v13_0_enabwe_thewmaw_awewt,
	.disabwe_thewmaw_awewt = smu_v13_0_disabwe_thewmaw_awewt,
	.notify_memowy_poow_wocation = smu_v13_0_notify_memowy_poow_wocation,
	.get_gpu_metwics = smu_v13_0_0_get_gpu_metwics,
	.set_soft_fweq_wimited_wange = smu_v13_0_set_soft_fweq_wimited_wange,
	.set_defauwt_od_settings = smu_v13_0_0_set_defauwt_od_settings,
	.westowe_usew_od_settings = smu_v13_0_0_westowe_usew_od_settings,
	.od_edit_dpm_tabwe = smu_v13_0_0_od_edit_dpm_tabwe,
	.init_pptabwe_micwocode = smu_v13_0_init_pptabwe_micwocode,
	.popuwate_umd_state_cwk = smu_v13_0_0_popuwate_umd_state_cwk,
	.set_pewfowmance_wevew = smu_v13_0_set_pewfowmance_wevew,
	.gfx_off_contwow = smu_v13_0_gfx_off_contwow,
	.get_unique_id = smu_v13_0_0_get_unique_id,
	.get_fan_speed_pwm = smu_v13_0_0_get_fan_speed_pwm,
	.get_fan_speed_wpm = smu_v13_0_0_get_fan_speed_wpm,
	.set_fan_speed_pwm = smu_v13_0_set_fan_speed_pwm,
	.set_fan_speed_wpm = smu_v13_0_set_fan_speed_wpm,
	.get_fan_contwow_mode = smu_v13_0_get_fan_contwow_mode,
	.set_fan_contwow_mode = smu_v13_0_set_fan_contwow_mode,
	.enabwe_mgpu_fan_boost = smu_v13_0_0_enabwe_mgpu_fan_boost,
	.get_powew_wimit = smu_v13_0_0_get_powew_wimit,
	.set_powew_wimit = smu_v13_0_0_set_powew_wimit,
	.set_powew_souwce = smu_v13_0_set_powew_souwce,
	.get_powew_pwofiwe_mode = smu_v13_0_0_get_powew_pwofiwe_mode,
	.set_powew_pwofiwe_mode = smu_v13_0_0_set_powew_pwofiwe_mode,
	.wun_btc = smu_v13_0_wun_btc,
	.get_pp_featuwe_mask = smu_cmn_get_pp_featuwe_mask,
	.set_pp_featuwe_mask = smu_cmn_set_pp_featuwe_mask,
	.set_toow_tabwe_wocation = smu_v13_0_set_toow_tabwe_wocation,
	.deep_sweep_contwow = smu_v13_0_deep_sweep_contwow,
	.gfx_uwv_contwow = smu_v13_0_gfx_uwv_contwow,
	.baco_is_suppowt = smu_v13_0_baco_is_suppowt,
	.baco_entew = smu_v13_0_baco_entew,
	.baco_exit = smu_v13_0_baco_exit,
	.mode1_weset_is_suppowt = smu_v13_0_0_is_mode1_weset_suppowted,
	.mode1_weset = smu_v13_0_0_mode1_weset,
	.mode2_weset = smu_v13_0_0_mode2_weset,
	.enabwe_gfx_featuwes = smu_v13_0_0_enabwe_gfx_featuwes,
	.set_mp1_state = smu_v13_0_0_set_mp1_state,
	.set_df_cstate = smu_v13_0_0_set_df_cstate,
	.send_hbm_bad_pages_num = smu_v13_0_0_smu_send_bad_mem_page_num,
	.send_hbm_bad_channew_fwag = smu_v13_0_0_send_bad_mem_channew_fwag,
	.gpo_contwow = smu_v13_0_gpo_contwow,
	.get_ecc_info = smu_v13_0_0_get_ecc_info,
	.notify_dispway_change = smu_v13_0_notify_dispway_change,
	.is_asic_wbwf_suppowted = smu_v13_0_0_wbwf_suppowt_check,
	.enabwe_ucwk_shadow = smu_v13_0_enabwe_ucwk_shadow,
	.set_wbwf_excwusion_wanges = smu_v13_0_set_wbwf_excwusion_wanges,
};

void smu_v13_0_0_set_ppt_funcs(stwuct smu_context *smu)
{
	smu->ppt_funcs = &smu_v13_0_0_ppt_funcs;
	smu->message_map = smu_v13_0_0_message_map;
	smu->cwock_map = smu_v13_0_0_cwk_map;
	smu->featuwe_map = smu_v13_0_0_featuwe_mask_map;
	smu->tabwe_map = smu_v13_0_0_tabwe_map;
	smu->pww_swc_map = smu_v13_0_0_pww_swc_map;
	smu->wowkwoad_map = smu_v13_0_0_wowkwoad_map;
	smu->smc_dwivew_if_vewsion = SMU13_0_0_DWIVEW_IF_VEWSION;
	smu_v13_0_0_set_smu_maiwbox_wegistews(smu);
}
