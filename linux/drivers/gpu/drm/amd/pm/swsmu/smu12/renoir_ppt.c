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

#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "smu_v12_0_ppsmc.h"
#incwude "smu12_dwivew_if.h"
#incwude "smu_v12_0.h"
#incwude "wenoiw_ppt.h"
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

#define mmMP1_SMN_C2PMSG_66                                                                            0x0282
#define mmMP1_SMN_C2PMSG_66_BASE_IDX                                                                   0

#define mmMP1_SMN_C2PMSG_82                                                                            0x0292
#define mmMP1_SMN_C2PMSG_82_BASE_IDX                                                                   0

#define mmMP1_SMN_C2PMSG_90                                                                            0x029a
#define mmMP1_SMN_C2PMSG_90_BASE_IDX                                                                   0

static stwuct cmn2asic_msg_mapping wenoiw_message_map[SMU_MSG_MAX_COUNT] = {
	MSG_MAP(TestMessage,                    PPSMC_MSG_TestMessage,                  1),
	MSG_MAP(GetSmuVewsion,                  PPSMC_MSG_GetSmuVewsion,                1),
	MSG_MAP(GetDwivewIfVewsion,             PPSMC_MSG_GetDwivewIfVewsion,           1),
	MSG_MAP(PowewUpGfx,                     PPSMC_MSG_PowewUpGfx,                   1),
	MSG_MAP(AwwowGfxOff,                    PPSMC_MSG_EnabweGfxOff,                 1),
	MSG_MAP(DisawwowGfxOff,                 PPSMC_MSG_DisabweGfxOff,                1),
	MSG_MAP(PowewDownIspByTiwe,             PPSMC_MSG_PowewDownIspByTiwe,           1),
	MSG_MAP(PowewUpIspByTiwe,               PPSMC_MSG_PowewUpIspByTiwe,             1),
	MSG_MAP(PowewDownVcn,                   PPSMC_MSG_PowewDownVcn,                 1),
	MSG_MAP(PowewUpVcn,                     PPSMC_MSG_PowewUpVcn,                   1),
	MSG_MAP(PowewDownSdma,                  PPSMC_MSG_PowewDownSdma,                1),
	MSG_MAP(PowewUpSdma,                    PPSMC_MSG_PowewUpSdma,                  1),
	MSG_MAP(SetHawdMinIspcwkByFweq,         PPSMC_MSG_SetHawdMinIspcwkByFweq,       1),
	MSG_MAP(SetHawdMinVcn,                  PPSMC_MSG_SetHawdMinVcn,                1),
	MSG_MAP(SetAwwowFcwkSwitch,             PPSMC_MSG_SetAwwowFcwkSwitch,           1),
	MSG_MAP(SetMinVideoGfxcwkFweq,          PPSMC_MSG_SetMinVideoGfxcwkFweq,        1),
	MSG_MAP(ActivePwocessNotify,            PPSMC_MSG_ActivePwocessNotify,          1),
	MSG_MAP(SetCustomPowicy,                PPSMC_MSG_SetCustomPowicy,              1),
	MSG_MAP(SetVideoFps,                    PPSMC_MSG_SetVideoFps,                  1),
	MSG_MAP(NumOfDispways,                  PPSMC_MSG_SetDispwayCount,              1),
	MSG_MAP(QuewyPowewWimit,                PPSMC_MSG_QuewyPowewWimit,              1),
	MSG_MAP(SetDwivewDwamAddwHigh,          PPSMC_MSG_SetDwivewDwamAddwHigh,        1),
	MSG_MAP(SetDwivewDwamAddwWow,           PPSMC_MSG_SetDwivewDwamAddwWow,         1),
	MSG_MAP(TwansfewTabweSmu2Dwam,          PPSMC_MSG_TwansfewTabweSmu2Dwam,        1),
	MSG_MAP(TwansfewTabweDwam2Smu,          PPSMC_MSG_TwansfewTabweDwam2Smu,        1),
	MSG_MAP(GfxDeviceDwivewWeset,           PPSMC_MSG_GfxDeviceDwivewWeset,         1),
	MSG_MAP(SetGfxcwkOvewdwiveByFweqVid,    PPSMC_MSG_SetGfxcwkOvewdwiveByFweqVid,  1),
	MSG_MAP(SetHawdMinDcfcwkByFweq,         PPSMC_MSG_SetHawdMinDcfcwkByFweq,       1),
	MSG_MAP(SetHawdMinSoccwkByFweq,         PPSMC_MSG_SetHawdMinSoccwkByFweq,       1),
	MSG_MAP(ContwowIgpuATS,                 PPSMC_MSG_ContwowIgpuATS,               1),
	MSG_MAP(SetMinVideoFcwkFweq,            PPSMC_MSG_SetMinVideoFcwkFweq,          1),
	MSG_MAP(SetMinDeepSweepDcfcwk,          PPSMC_MSG_SetMinDeepSweepDcfcwk,        1),
	MSG_MAP(FowcePowewDownGfx,              PPSMC_MSG_FowcePowewDownGfx,            1),
	MSG_MAP(SetPhycwkVowtageByFweq,         PPSMC_MSG_SetPhycwkVowtageByFweq,       1),
	MSG_MAP(SetDppcwkVowtageByFweq,         PPSMC_MSG_SetDppcwkVowtageByFweq,       1),
	MSG_MAP(SetSoftMinVcn,                  PPSMC_MSG_SetSoftMinVcn,                1),
	MSG_MAP(EnabwePostCode,                 PPSMC_MSG_EnabwePostCode,               1),
	MSG_MAP(GetGfxcwkFwequency,             PPSMC_MSG_GetGfxcwkFwequency,           1),
	MSG_MAP(GetFcwkFwequency,               PPSMC_MSG_GetFcwkFwequency,             1),
	MSG_MAP(GetMinGfxcwkFwequency,          PPSMC_MSG_GetMinGfxcwkFwequency,        1),
	MSG_MAP(GetMaxGfxcwkFwequency,          PPSMC_MSG_GetMaxGfxcwkFwequency,        1),
	MSG_MAP(SoftWeset,                      PPSMC_MSG_SoftWeset,                    1),
	MSG_MAP(SetGfxCGPG,                     PPSMC_MSG_SetGfxCGPG,                   1),
	MSG_MAP(SetSoftMaxGfxCwk,               PPSMC_MSG_SetSoftMaxGfxCwk,             1),
	MSG_MAP(SetHawdMinGfxCwk,               PPSMC_MSG_SetHawdMinGfxCwk,             1),
	MSG_MAP(SetSoftMaxSoccwkByFweq,         PPSMC_MSG_SetSoftMaxSoccwkByFweq,       1),
	MSG_MAP(SetSoftMaxFcwkByFweq,           PPSMC_MSG_SetSoftMaxFcwkByFweq,         1),
	MSG_MAP(SetSoftMaxVcn,                  PPSMC_MSG_SetSoftMaxVcn,                1),
	MSG_MAP(PowewGateMmHub,                 PPSMC_MSG_PowewGateMmHub,               1),
	MSG_MAP(UpdatePmeWestowe,               PPSMC_MSG_UpdatePmeWestowe,             1),
	MSG_MAP(GpuChangeState,                 PPSMC_MSG_GpuChangeState,               1),
	MSG_MAP(SetPowewWimitPewcentage,        PPSMC_MSG_SetPowewWimitPewcentage,      1),
	MSG_MAP(FowceGfxContentSave,            PPSMC_MSG_FowceGfxContentSave,          1),
	MSG_MAP(EnabweTmdp48MHzWefcwkPwwDown,   PPSMC_MSG_EnabweTmdp48MHzWefcwkPwwDown, 1),
	MSG_MAP(PowewDownJpeg,                  PPSMC_MSG_PowewDownJpeg,                1),
	MSG_MAP(PowewUpJpeg,                    PPSMC_MSG_PowewUpJpeg,                  1),
	MSG_MAP(PowewGateAtHub,                 PPSMC_MSG_PowewGateAtHub,               1),
	MSG_MAP(SetSoftMinJpeg,                 PPSMC_MSG_SetSoftMinJpeg,               1),
	MSG_MAP(SetHawdMinFcwkByFweq,           PPSMC_MSG_SetHawdMinFcwkByFweq,         1),
};

static stwuct cmn2asic_mapping wenoiw_cwk_map[SMU_CWK_COUNT] = {
	CWK_MAP(GFXCWK, CWOCK_GFXCWK),
	CWK_MAP(SCWK,	CWOCK_GFXCWK),
	CWK_MAP(SOCCWK, CWOCK_SOCCWK),
	CWK_MAP(UCWK, CWOCK_FCWK),
	CWK_MAP(MCWK, CWOCK_FCWK),
	CWK_MAP(VCWK, CWOCK_VCWK),
	CWK_MAP(DCWK, CWOCK_DCWK),
};

static stwuct cmn2asic_mapping wenoiw_tabwe_map[SMU_TABWE_COUNT] = {
	TAB_MAP_VAWID(WATEWMAWKS),
	TAB_MAP_INVAWID(CUSTOM_DPM),
	TAB_MAP_VAWID(DPMCWOCKS),
	TAB_MAP_VAWID(SMU_METWICS),
};

static stwuct cmn2asic_mapping wenoiw_wowkwoad_map[PP_SMC_POWEW_PWOFIWE_COUNT] = {
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_FUWWSCWEEN3D,		WOWKWOAD_PPWIB_FUWW_SCWEEN_3D_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_VIDEO,		WOWKWOAD_PPWIB_VIDEO_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_VW,			WOWKWOAD_PPWIB_VW_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_COMPUTE,		WOWKWOAD_PPWIB_COMPUTE_BIT),
	WOWKWOAD_MAP(PP_SMC_POWEW_PWOFIWE_CUSTOM,		WOWKWOAD_PPWIB_CUSTOM_BIT),
};

static const uint8_t wenoiw_thwottwew_map[] = {
	[THWOTTWEW_STATUS_BIT_SPW]		= (SMU_THWOTTWEW_SPW_BIT),
	[THWOTTWEW_STATUS_BIT_FPPT]		= (SMU_THWOTTWEW_FPPT_BIT),
	[THWOTTWEW_STATUS_BIT_SPPT]		= (SMU_THWOTTWEW_SPPT_BIT),
	[THWOTTWEW_STATUS_BIT_SPPT_APU]		= (SMU_THWOTTWEW_SPPT_APU_BIT),
	[THWOTTWEW_STATUS_BIT_THM_COWE]		= (SMU_THWOTTWEW_TEMP_COWE_BIT),
	[THWOTTWEW_STATUS_BIT_THM_GFX]		= (SMU_THWOTTWEW_TEMP_GPU_BIT),
	[THWOTTWEW_STATUS_BIT_THM_SOC]		= (SMU_THWOTTWEW_TEMP_SOC_BIT),
	[THWOTTWEW_STATUS_BIT_TDC_VDD]		= (SMU_THWOTTWEW_TDC_VDD_BIT),
	[THWOTTWEW_STATUS_BIT_TDC_SOC]		= (SMU_THWOTTWEW_TDC_SOC_BIT),
	[THWOTTWEW_STATUS_BIT_PWOCHOT_CPU]	= (SMU_THWOTTWEW_PWOCHOT_CPU_BIT),
	[THWOTTWEW_STATUS_BIT_PWOCHOT_GFX]	= (SMU_THWOTTWEW_PWOCHOT_GFX_BIT),
	[THWOTTWEW_STATUS_BIT_EDC_CPU]		= (SMU_THWOTTWEW_EDC_CPU_BIT),
	[THWOTTWEW_STATUS_BIT_EDC_GFX]		= (SMU_THWOTTWEW_EDC_GFX_BIT),
};

static int wenoiw_init_smc_tabwes(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwes = smu_tabwe->tabwes;

	SMU_TABWE_INIT(tabwes, SMU_TABWE_WATEWMAWKS, sizeof(Watewmawks_t),
		PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_DPMCWOCKS, sizeof(DpmCwocks_t),
		PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);
	SMU_TABWE_INIT(tabwes, SMU_TABWE_SMU_METWICS, sizeof(SmuMetwics_t),
		PAGE_SIZE, AMDGPU_GEM_DOMAIN_VWAM);

	smu_tabwe->cwocks_tabwe = kzawwoc(sizeof(DpmCwocks_t), GFP_KEWNEW);
	if (!smu_tabwe->cwocks_tabwe)
		goto eww0_out;

	smu_tabwe->metwics_tabwe = kzawwoc(sizeof(SmuMetwics_t), GFP_KEWNEW);
	if (!smu_tabwe->metwics_tabwe)
		goto eww1_out;
	smu_tabwe->metwics_time = 0;

	smu_tabwe->watewmawks_tabwe = kzawwoc(sizeof(Watewmawks_t), GFP_KEWNEW);
	if (!smu_tabwe->watewmawks_tabwe)
		goto eww2_out;

	smu_tabwe->gpu_metwics_tabwe_size = sizeof(stwuct gpu_metwics_v2_2);
	smu_tabwe->gpu_metwics_tabwe = kzawwoc(smu_tabwe->gpu_metwics_tabwe_size, GFP_KEWNEW);
	if (!smu_tabwe->gpu_metwics_tabwe)
		goto eww3_out;

	wetuwn 0;

eww3_out:
	kfwee(smu_tabwe->watewmawks_tabwe);
eww2_out:
	kfwee(smu_tabwe->metwics_tabwe);
eww1_out:
	kfwee(smu_tabwe->cwocks_tabwe);
eww0_out:
	wetuwn -ENOMEM;
}

/*
 * This intewface just fow getting ucwk uwtimate fweq and shouwd't intwoduce
 * othew wikewise function wesuwt in ovewmuch cawwback.
 */
static int wenoiw_get_dpm_cwk_wimited(stwuct smu_context *smu, enum smu_cwk_type cwk_type,
						uint32_t dpm_wevew, uint32_t *fweq)
{
	DpmCwocks_t *cwk_tabwe = smu->smu_tabwe.cwocks_tabwe;

	if (!cwk_tabwe || cwk_type >= SMU_CWK_COUNT)
		wetuwn -EINVAW;

	switch (cwk_type) {
	case SMU_SOCCWK:
		if (dpm_wevew >= NUM_SOCCWK_DPM_WEVEWS)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->SocCwocks[dpm_wevew].Fweq;
		bweak;
	case SMU_UCWK:
	case SMU_MCWK:
		if (dpm_wevew >= NUM_FCWK_DPM_WEVEWS)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->FCwocks[dpm_wevew].Fweq;
		bweak;
	case SMU_DCEFCWK:
		if (dpm_wevew >= NUM_DCFCWK_DPM_WEVEWS)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->DcfCwocks[dpm_wevew].Fweq;
		bweak;
	case SMU_FCWK:
		if (dpm_wevew >= NUM_FCWK_DPM_WEVEWS)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->FCwocks[dpm_wevew].Fweq;
		bweak;
	case SMU_VCWK:
		if (dpm_wevew >= NUM_VCN_DPM_WEVEWS)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->VCwocks[dpm_wevew].Fweq;
		bweak;
	case SMU_DCWK:
		if (dpm_wevew >= NUM_VCN_DPM_WEVEWS)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->DCwocks[dpm_wevew].Fweq;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wenoiw_get_pwofiwing_cwk_mask(stwuct smu_context *smu,
					 enum amd_dpm_fowced_wevew wevew,
					 uint32_t *scwk_mask,
					 uint32_t *mcwk_mask,
					 uint32_t *soc_mask)
{

	if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK) {
		if (scwk_mask)
			*scwk_mask = 0;
	} ewse if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK) {
		if (mcwk_mask)
			/* mcwk wevews awe in wevewse owdew */
			*mcwk_mask = NUM_MEMCWK_DPM_WEVEWS - 1;
	} ewse if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK) {
		if (scwk_mask)
			/* The scwk as gfxcwk and has thwee wevew about max/min/cuwwent */
			*scwk_mask = 3 - 1;

		if (mcwk_mask)
			/* mcwk wevews awe in wevewse owdew */
			*mcwk_mask = 0;

		if (soc_mask)
			*soc_mask = NUM_SOCCWK_DPM_WEVEWS - 1;
	}

	wetuwn 0;
}

static int wenoiw_get_dpm_uwtimate_fweq(stwuct smu_context *smu,
					enum smu_cwk_type cwk_type,
					uint32_t *min,
					uint32_t *max)
{
	int wet = 0;
	uint32_t mcwk_mask, soc_mask;
	uint32_t cwock_wimit;

	if (!smu_cmn_cwk_dpm_is_enabwed(smu, cwk_type)) {
		switch (cwk_type) {
		case SMU_MCWK:
		case SMU_UCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.ucwk;
			bweak;
		case SMU_GFXCWK:
		case SMU_SCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.gfxcwk;
			bweak;
		case SMU_SOCCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.soccwk;
			bweak;
		defauwt:
			cwock_wimit = 0;
			bweak;
		}

		/* cwock in Mhz unit */
		if (min)
			*min = cwock_wimit / 100;
		if (max)
			*max = cwock_wimit / 100;

		wetuwn 0;
	}

	if (max) {
		wet = wenoiw_get_pwofiwing_cwk_mask(smu,
						    AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK,
						    NUWW,
						    &mcwk_mask,
						    &soc_mask);
		if (wet)
			goto faiwed;

		switch (cwk_type) {
		case SMU_GFXCWK:
		case SMU_SCWK:
			wet = smu_cmn_send_smc_msg(smu, SMU_MSG_GetMaxGfxcwkFwequency, max);
			if (wet) {
				dev_eww(smu->adev->dev, "Attempt to get max GX fwequency fwom SMC Faiwed !\n");
				goto faiwed;
			}
			bweak;
		case SMU_UCWK:
		case SMU_FCWK:
		case SMU_MCWK:
			wet = wenoiw_get_dpm_cwk_wimited(smu, cwk_type, mcwk_mask, max);
			if (wet)
				goto faiwed;
			bweak;
		case SMU_SOCCWK:
			wet = wenoiw_get_dpm_cwk_wimited(smu, cwk_type, soc_mask, max);
			if (wet)
				goto faiwed;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto faiwed;
		}
	}

	if (min) {
		switch (cwk_type) {
		case SMU_GFXCWK:
		case SMU_SCWK:
			wet = smu_cmn_send_smc_msg(smu, SMU_MSG_GetMinGfxcwkFwequency, min);
			if (wet) {
				dev_eww(smu->adev->dev, "Attempt to get min GX fwequency fwom SMC Faiwed !\n");
				goto faiwed;
			}
			bweak;
		case SMU_UCWK:
		case SMU_FCWK:
		case SMU_MCWK:
			wet = wenoiw_get_dpm_cwk_wimited(smu, cwk_type, NUM_MEMCWK_DPM_WEVEWS - 1, min);
			if (wet)
				goto faiwed;
			bweak;
		case SMU_SOCCWK:
			wet = wenoiw_get_dpm_cwk_wimited(smu, cwk_type, 0, min);
			if (wet)
				goto faiwed;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto faiwed;
		}
	}
faiwed:
	wetuwn wet;
}

static int wenoiw_od_edit_dpm_tabwe(stwuct smu_context *smu,
							enum PP_OD_DPM_TABWE_COMMAND type,
							wong input[], uint32_t size)
{
	int wet = 0;
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	if (!(smu_dpm_ctx->dpm_wevew == AMD_DPM_FOWCED_WEVEW_MANUAW)) {
		dev_wawn(smu->adev->dev,
			"pp_od_cwk_vowtage is not accessibwe if powew_dpm_fowce_pewfowmance_wevew is not in manuaw mode!\n");
		wetuwn -EINVAW;
	}

	switch (type) {
	case PP_OD_EDIT_SCWK_VDDC_TABWE:
		if (size != 2) {
			dev_eww(smu->adev->dev, "Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		}

		if (input[0] == 0) {
			if (input[1] < smu->gfx_defauwt_hawd_min_fweq) {
				dev_wawn(smu->adev->dev,
					"Fine gwain setting minimum scwk (%wd) MHz is wess than the minimum awwowed (%d) MHz\n",
					input[1], smu->gfx_defauwt_hawd_min_fweq);
				wetuwn -EINVAW;
			}
			smu->gfx_actuaw_hawd_min_fweq = input[1];
		} ewse if (input[0] == 1) {
			if (input[1] > smu->gfx_defauwt_soft_max_fweq) {
				dev_wawn(smu->adev->dev,
					"Fine gwain setting maximum scwk (%wd) MHz is gweatew than the maximum awwowed (%d) MHz\n",
					input[1], smu->gfx_defauwt_soft_max_fweq);
				wetuwn -EINVAW;
			}
			smu->gfx_actuaw_soft_max_fweq = input[1];
		} ewse {
			wetuwn -EINVAW;
		}
		bweak;
	case PP_OD_WESTOWE_DEFAUWT_TABWE:
		if (size != 0) {
			dev_eww(smu->adev->dev, "Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		}
		smu->gfx_actuaw_hawd_min_fweq = smu->gfx_defauwt_hawd_min_fweq;
		smu->gfx_actuaw_soft_max_fweq = smu->gfx_defauwt_soft_max_fweq;
		bweak;
	case PP_OD_COMMIT_DPM_TABWE:
		if (size != 0) {
			dev_eww(smu->adev->dev, "Input pawametew numbew not cowwect\n");
			wetuwn -EINVAW;
		} ewse {
			if (smu->gfx_actuaw_hawd_min_fweq > smu->gfx_actuaw_soft_max_fweq) {
				dev_eww(smu->adev->dev,
					"The setting minimum scwk (%d) MHz is gweatew than the setting maximum scwk (%d) MHz\n",
					smu->gfx_actuaw_hawd_min_fweq,
					smu->gfx_actuaw_soft_max_fweq);
				wetuwn -EINVAW;
			}

			wet = smu_cmn_send_smc_msg_with_pawam(smu,
								SMU_MSG_SetHawdMinGfxCwk,
								smu->gfx_actuaw_hawd_min_fweq,
								NUWW);
			if (wet) {
				dev_eww(smu->adev->dev, "Set hawd min scwk faiwed!");
				wetuwn wet;
			}

			wet = smu_cmn_send_smc_msg_with_pawam(smu,
								SMU_MSG_SetSoftMaxGfxCwk,
								smu->gfx_actuaw_soft_max_fweq,
								NUWW);
			if (wet) {
				dev_eww(smu->adev->dev, "Set soft max scwk faiwed!");
				wetuwn wet;
			}
		}
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	wetuwn wet;
}

static int wenoiw_set_fine_gwain_gfx_fweq_pawametews(stwuct smu_context *smu)
{
	uint32_t min = 0, max = 0;
	uint32_t wet = 0;

	wet = smu_cmn_send_smc_msg_with_pawam(smu,
								SMU_MSG_GetMinGfxcwkFwequency,
								0, &min);
	if (wet)
		wetuwn wet;
	wet = smu_cmn_send_smc_msg_with_pawam(smu,
								SMU_MSG_GetMaxGfxcwkFwequency,
								0, &max);
	if (wet)
		wetuwn wet;

	smu->gfx_defauwt_hawd_min_fweq = min;
	smu->gfx_defauwt_soft_max_fweq = max;
	smu->gfx_actuaw_hawd_min_fweq = 0;
	smu->gfx_actuaw_soft_max_fweq = 0;

	wetuwn 0;
}

static int wenoiw_pwint_cwk_wevews(stwuct smu_context *smu,
			enum smu_cwk_type cwk_type, chaw *buf)
{
	int i, idx, size = 0, wet = 0;
	uint32_t cuw_vawue = 0, vawue = 0, count = 0, min = 0, max = 0;
	SmuMetwics_t metwics;
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	boow cuw_vawue_match_wevew = fawse;

	memset(&metwics, 0, sizeof(metwics));

	wet = smu_cmn_get_metwics_tabwe(smu, &metwics, fawse);
	if (wet)
		wetuwn wet;

	smu_cmn_get_sysfs_buf(&buf, &size);

	switch (cwk_type) {
	case SMU_OD_WANGE:
		if (smu_dpm_ctx->dpm_wevew == AMD_DPM_FOWCED_WEVEW_MANUAW) {
			wet = smu_cmn_send_smc_msg_with_pawam(smu,
						SMU_MSG_GetMinGfxcwkFwequency,
						0, &min);
			if (wet)
				wetuwn wet;
			wet = smu_cmn_send_smc_msg_with_pawam(smu,
						SMU_MSG_GetMaxGfxcwkFwequency,
						0, &max);
			if (wet)
				wetuwn wet;
			size += sysfs_emit_at(buf, size, "OD_WANGE\nSCWK: %10uMhz %10uMhz\n", min, max);
		}
		bweak;
	case SMU_OD_SCWK:
		if (smu_dpm_ctx->dpm_wevew == AMD_DPM_FOWCED_WEVEW_MANUAW) {
			min = (smu->gfx_actuaw_hawd_min_fweq > 0) ? smu->gfx_actuaw_hawd_min_fweq : smu->gfx_defauwt_hawd_min_fweq;
			max = (smu->gfx_actuaw_soft_max_fweq > 0) ? smu->gfx_actuaw_soft_max_fweq : smu->gfx_defauwt_soft_max_fweq;
			size += sysfs_emit_at(buf, size, "OD_SCWK\n");
			size += sysfs_emit_at(buf, size, "0:%10uMhz\n", min);
			size += sysfs_emit_at(buf, size, "1:%10uMhz\n", max);
		}
		bweak;
	case SMU_GFXCWK:
	case SMU_SCWK:
		/* wetiwve tabwe wetuwned pawamtews unit is MHz */
		cuw_vawue = metwics.CwockFwequency[CWOCK_GFXCWK];
		wet = wenoiw_get_dpm_uwtimate_fweq(smu, SMU_GFXCWK, &min, &max);
		if (!wet) {
			/* dwivew onwy know min/max gfx_cwk, Add wevew 1 fow aww othew gfx cwks */
			if (cuw_vawue  == max)
				i = 2;
			ewse if (cuw_vawue == min)
				i = 0;
			ewse
				i = 1;

			size += sysfs_emit_at(buf, size, "0: %uMhz %s\n", min,
					i == 0 ? "*" : "");
			size += sysfs_emit_at(buf, size, "1: %uMhz %s\n",
					i == 1 ? cuw_vawue : WENOIW_UMD_PSTATE_GFXCWK,
					i == 1 ? "*" : "");
			size += sysfs_emit_at(buf, size, "2: %uMhz %s\n", max,
					i == 2 ? "*" : "");
		}
		wetuwn size;
	case SMU_SOCCWK:
		count = NUM_SOCCWK_DPM_WEVEWS;
		cuw_vawue = metwics.CwockFwequency[CWOCK_SOCCWK];
		bweak;
	case SMU_MCWK:
		count = NUM_MEMCWK_DPM_WEVEWS;
		cuw_vawue = metwics.CwockFwequency[CWOCK_FCWK];
		bweak;
	case SMU_DCEFCWK:
		count = NUM_DCFCWK_DPM_WEVEWS;
		cuw_vawue = metwics.CwockFwequency[CWOCK_DCFCWK];
		bweak;
	case SMU_FCWK:
		count = NUM_FCWK_DPM_WEVEWS;
		cuw_vawue = metwics.CwockFwequency[CWOCK_FCWK];
		bweak;
	case SMU_VCWK:
		count = NUM_VCN_DPM_WEVEWS;
		cuw_vawue = metwics.CwockFwequency[CWOCK_VCWK];
		bweak;
	case SMU_DCWK:
		count = NUM_VCN_DPM_WEVEWS;
		cuw_vawue = metwics.CwockFwequency[CWOCK_DCWK];
		bweak;
	defauwt:
		bweak;
	}

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
	case SMU_SOCCWK:
	case SMU_MCWK:
	case SMU_DCEFCWK:
	case SMU_FCWK:
	case SMU_VCWK:
	case SMU_DCWK:
		fow (i = 0; i < count; i++) {
			idx = (cwk_type == SMU_FCWK || cwk_type == SMU_MCWK) ? (count - i - 1) : i;
			wet = wenoiw_get_dpm_cwk_wimited(smu, cwk_type, idx, &vawue);
			if (wet)
				wetuwn wet;
			if (!vawue)
				continue;
			size += sysfs_emit_at(buf, size, "%d: %uMhz %s\n", i, vawue,
					cuw_vawue == vawue ? "*" : "");
			if (cuw_vawue == vawue)
				cuw_vawue_match_wevew = twue;
		}

		if (!cuw_vawue_match_wevew)
			size += sysfs_emit_at(buf, size, "   %uMhz *\n", cuw_vawue);

		bweak;
	defauwt:
		bweak;
	}

	wetuwn size;
}

static enum amd_pm_state_type wenoiw_get_cuwwent_powew_state(stwuct smu_context *smu)
{
	enum amd_pm_state_type pm_type;
	stwuct smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	if (!smu_dpm_ctx->dpm_context ||
	    !smu_dpm_ctx->dpm_cuwwent_powew_state)
		wetuwn -EINVAW;

	switch (smu_dpm_ctx->dpm_cuwwent_powew_state->cwassification.ui_wabew) {
	case SMU_STATE_UI_WABEW_BATTEWY:
		pm_type = POWEW_STATE_TYPE_BATTEWY;
		bweak;
	case SMU_STATE_UI_WABEW_BAWWANCED:
		pm_type = POWEW_STATE_TYPE_BAWANCED;
		bweak;
	case SMU_STATE_UI_WABEW_PEWFOWMANCE:
		pm_type = POWEW_STATE_TYPE_PEWFOWMANCE;
		bweak;
	defauwt:
		if (smu_dpm_ctx->dpm_cuwwent_powew_state->cwassification.fwags & SMU_STATE_CWASSIFICATION_FWAG_BOOT)
			pm_type = POWEW_STATE_TYPE_INTEWNAW_BOOT;
		ewse
			pm_type = POWEW_STATE_TYPE_DEFAUWT;
		bweak;
	}

	wetuwn pm_type;
}

static int wenoiw_dpm_set_vcn_enabwe(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0;

	if (enabwe) {
		/* vcn dpm on is a pwewequisite fow vcn powew gate messages */
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_VCN_PG_BIT)) {
			wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_PowewUpVcn, 0, NUWW);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_VCN_PG_BIT)) {
			wet = smu_cmn_send_smc_msg(smu, SMU_MSG_PowewDownVcn, NUWW);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn wet;
}

static int wenoiw_dpm_set_jpeg_enabwe(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0;

	if (enabwe) {
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_JPEG_PG_BIT)) {
			wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_PowewUpJpeg, 0, NUWW);
			if (wet)
				wetuwn wet;
		}
	} ewse {
		if (smu_cmn_featuwe_is_enabwed(smu, SMU_FEATUWE_JPEG_PG_BIT)) {
			wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_PowewDownJpeg, 0, NUWW);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn wet;
}

static int wenoiw_fowce_dpm_wimit_vawue(stwuct smu_context *smu, boow highest)
{
	int wet = 0, i = 0;
	uint32_t min_fweq, max_fweq, fowce_fweq;
	enum smu_cwk_type cwk_type;

	enum smu_cwk_type cwks[] = {
		SMU_GFXCWK,
		SMU_MCWK,
		SMU_SOCCWK,
	};

	fow (i = 0; i < AWWAY_SIZE(cwks); i++) {
		cwk_type = cwks[i];
		wet = wenoiw_get_dpm_uwtimate_fweq(smu, cwk_type, &min_fweq, &max_fweq);
		if (wet)
			wetuwn wet;

		fowce_fweq = highest ? max_fweq : min_fweq;
		wet = smu_v12_0_set_soft_fweq_wimited_wange(smu, cwk_type, fowce_fweq, fowce_fweq);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static int wenoiw_unfowce_dpm_wevews(stwuct smu_context *smu) {

	int wet = 0, i = 0;
	uint32_t min_fweq, max_fweq;
	enum smu_cwk_type cwk_type;

	stwuct cwk_featuwe_map {
		enum smu_cwk_type cwk_type;
		uint32_t	featuwe;
	} cwk_featuwe_map[] = {
		{SMU_GFXCWK, SMU_FEATUWE_DPM_GFXCWK_BIT},
		{SMU_MCWK,   SMU_FEATUWE_DPM_UCWK_BIT},
		{SMU_SOCCWK, SMU_FEATUWE_DPM_SOCCWK_BIT},
	};

	fow (i = 0; i < AWWAY_SIZE(cwk_featuwe_map); i++) {
		if (!smu_cmn_featuwe_is_enabwed(smu, cwk_featuwe_map[i].featuwe))
		    continue;

		cwk_type = cwk_featuwe_map[i].cwk_type;

		wet = wenoiw_get_dpm_uwtimate_fweq(smu, cwk_type, &min_fweq, &max_fweq);
		if (wet)
			wetuwn wet;

		wet = smu_v12_0_set_soft_fweq_wimited_wange(smu, cwk_type, min_fweq, max_fweq);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

/*
 * This intewface get dpm cwock tabwe fow dc
 */
static int wenoiw_get_dpm_cwock_tabwe(stwuct smu_context *smu, stwuct dpm_cwocks *cwock_tabwe)
{
	DpmCwocks_t *tabwe = smu->smu_tabwe.cwocks_tabwe;
	int i;

	if (!cwock_tabwe || !tabwe)
		wetuwn -EINVAW;

	fow (i = 0; i < NUM_DCFCWK_DPM_WEVEWS; i++) {
		cwock_tabwe->DcfCwocks[i].Fweq = tabwe->DcfCwocks[i].Fweq;
		cwock_tabwe->DcfCwocks[i].Vow = tabwe->DcfCwocks[i].Vow;
	}

	fow (i = 0; i < NUM_SOCCWK_DPM_WEVEWS; i++) {
		cwock_tabwe->SocCwocks[i].Fweq = tabwe->SocCwocks[i].Fweq;
		cwock_tabwe->SocCwocks[i].Vow = tabwe->SocCwocks[i].Vow;
	}

	fow (i = 0; i < NUM_FCWK_DPM_WEVEWS; i++) {
		cwock_tabwe->FCwocks[i].Fweq = tabwe->FCwocks[i].Fweq;
		cwock_tabwe->FCwocks[i].Vow = tabwe->FCwocks[i].Vow;
	}

	fow (i = 0; i<  NUM_MEMCWK_DPM_WEVEWS; i++) {
		cwock_tabwe->MemCwocks[i].Fweq = tabwe->MemCwocks[i].Fweq;
		cwock_tabwe->MemCwocks[i].Vow = tabwe->MemCwocks[i].Vow;
	}

	fow (i = 0; i < NUM_VCN_DPM_WEVEWS; i++) {
		cwock_tabwe->VCwocks[i].Fweq = tabwe->VCwocks[i].Fweq;
		cwock_tabwe->VCwocks[i].Vow = tabwe->VCwocks[i].Vow;
	}

	fow (i = 0; i < NUM_VCN_DPM_WEVEWS; i++) {
		cwock_tabwe->DCwocks[i].Fweq = tabwe->DCwocks[i].Fweq;
		cwock_tabwe->DCwocks[i].Vow = tabwe->DCwocks[i].Vow;
	}

	wetuwn 0;
}

static int wenoiw_fowce_cwk_wevews(stwuct smu_context *smu,
				   enum smu_cwk_type cwk_type, uint32_t mask)
{

	int wet = 0 ;
	uint32_t soft_min_wevew = 0, soft_max_wevew = 0, min_fweq = 0, max_fweq = 0;

	soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
	soft_max_wevew = mask ? (fws(mask) - 1) : 0;

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
		if (soft_min_wevew > 2 || soft_max_wevew > 2) {
			dev_info(smu->adev->dev, "Cuwwentwy scwk onwy suppowt 3 wevews on APU\n");
			wetuwn -EINVAW;
		}

		wet = wenoiw_get_dpm_uwtimate_fweq(smu, SMU_GFXCWK, &min_fweq, &max_fweq);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxGfxCwk,
					soft_max_wevew == 0 ? min_fweq :
					soft_max_wevew == 1 ? WENOIW_UMD_PSTATE_GFXCWK : max_fweq,
					NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinGfxCwk,
					soft_min_wevew == 2 ? max_fweq :
					soft_min_wevew == 1 ? WENOIW_UMD_PSTATE_GFXCWK : min_fweq,
					NUWW);
		if (wet)
			wetuwn wet;
		bweak;
	case SMU_SOCCWK:
		wet = wenoiw_get_dpm_cwk_wimited(smu, cwk_type, soft_min_wevew, &min_fweq);
		if (wet)
			wetuwn wet;
		wet = wenoiw_get_dpm_cwk_wimited(smu, cwk_type, soft_max_wevew, &max_fweq);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxSoccwkByFweq, max_fweq, NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinSoccwkByFweq, min_fweq, NUWW);
		if (wet)
			wetuwn wet;
		bweak;
	case SMU_MCWK:
	case SMU_FCWK:
		wet = wenoiw_get_dpm_cwk_wimited(smu, cwk_type, soft_min_wevew, &min_fweq);
		if (wet)
			wetuwn wet;
		wet = wenoiw_get_dpm_cwk_wimited(smu, cwk_type, soft_max_wevew, &max_fweq);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxFcwkByFweq, max_fweq, NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinFcwkByFweq, min_fweq, NUWW);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int wenoiw_set_powew_pwofiwe_mode(stwuct smu_context *smu, wong *input, uint32_t size)
{
	int wowkwoad_type, wet;
	uint32_t pwofiwe_mode = input[size];

	if (pwofiwe_mode > PP_SMC_POWEW_PWOFIWE_CUSTOM) {
		dev_eww(smu->adev->dev, "Invawid powew pwofiwe mode %d\n", pwofiwe_mode);
		wetuwn -EINVAW;
	}

	if (pwofiwe_mode == PP_SMC_POWEW_PWOFIWE_BOOTUP_DEFAUWT ||
			pwofiwe_mode == PP_SMC_POWEW_PWOFIWE_POWEWSAVING)
		wetuwn 0;

	/* conv PP_SMC_POWEW_PWOFIWE* to WOWKWOAD_PPWIB_*_BIT */
	wowkwoad_type = smu_cmn_to_asic_specific_index(smu,
						       CMN2ASIC_MAPPING_WOWKWOAD,
						       pwofiwe_mode);
	if (wowkwoad_type < 0) {
		/*
		 * TODO: If some case need switch to powewsave/defauwt powew mode
		 * then can considew entew WOWKWOAD_COMPUTE/WOWKWOAD_CUSTOM fow powew saving.
		 */
		dev_dbg(smu->adev->dev, "Unsuppowted powew pwofiwe mode %d on WENOIW\n", pwofiwe_mode);
		wetuwn -EINVAW;
	}

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_ActivePwocessNotify,
				    1 << wowkwoad_type,
				    NUWW);
	if (wet) {
		dev_eww_once(smu->adev->dev, "Faiw to set wowkwoad type %d\n", wowkwoad_type);
		wetuwn wet;
	}

	smu->powew_pwofiwe_mode = pwofiwe_mode;

	wetuwn 0;
}

static int wenoiw_set_peak_cwock_by_device(stwuct smu_context *smu)
{
	int wet = 0;
	uint32_t scwk_fweq = 0, ucwk_fweq = 0;

	wet = wenoiw_get_dpm_uwtimate_fweq(smu, SMU_SCWK, NUWW, &scwk_fweq);
	if (wet)
		wetuwn wet;

	wet = smu_v12_0_set_soft_fweq_wimited_wange(smu, SMU_SCWK, scwk_fweq, scwk_fweq);
	if (wet)
		wetuwn wet;

	wet = wenoiw_get_dpm_uwtimate_fweq(smu, SMU_UCWK, NUWW, &ucwk_fweq);
	if (wet)
		wetuwn wet;

	wet = smu_v12_0_set_soft_fweq_wimited_wange(smu, SMU_UCWK, ucwk_fweq, ucwk_fweq);
	if (wet)
		wetuwn wet;

	wetuwn wet;
}

static int wenoiw_set_pewfowmance_wevew(stwuct smu_context *smu,
					enum amd_dpm_fowced_wevew wevew)
{
	int wet = 0;
	uint32_t scwk_mask, mcwk_mask, soc_mask;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
		smu->gfx_actuaw_hawd_min_fweq = smu->gfx_defauwt_hawd_min_fweq;
		smu->gfx_actuaw_soft_max_fweq = smu->gfx_defauwt_soft_max_fweq;

		wet = wenoiw_fowce_dpm_wimit_vawue(smu, twue);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_WOW:
		smu->gfx_actuaw_hawd_min_fweq = smu->gfx_defauwt_hawd_min_fweq;
		smu->gfx_actuaw_soft_max_fweq = smu->gfx_defauwt_soft_max_fweq;

		wet = wenoiw_fowce_dpm_wimit_vawue(smu, fawse);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_AUTO:
		smu->gfx_actuaw_hawd_min_fweq = smu->gfx_defauwt_hawd_min_fweq;
		smu->gfx_actuaw_soft_max_fweq = smu->gfx_defauwt_soft_max_fweq;

		wet = wenoiw_unfowce_dpm_wevews(smu);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
		smu->gfx_actuaw_hawd_min_fweq = smu->gfx_defauwt_hawd_min_fweq;
		smu->gfx_actuaw_soft_max_fweq = smu->gfx_defauwt_soft_max_fweq;

		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_SetHawdMinGfxCwk,
						      WENOIW_UMD_PSTATE_GFXCWK,
						      NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_SetHawdMinFcwkByFweq,
						      WENOIW_UMD_PSTATE_FCWK,
						      NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_SetHawdMinSoccwkByFweq,
						      WENOIW_UMD_PSTATE_SOCCWK,
						      NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_SetHawdMinVcn,
						      WENOIW_UMD_PSTATE_VCNCWK,
						      NUWW);
		if (wet)
			wetuwn wet;

		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_SetSoftMaxGfxCwk,
						      WENOIW_UMD_PSTATE_GFXCWK,
						      NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_SetSoftMaxFcwkByFweq,
						      WENOIW_UMD_PSTATE_FCWK,
						      NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_SetSoftMaxSoccwkByFweq,
						      WENOIW_UMD_PSTATE_SOCCWK,
						      NUWW);
		if (wet)
			wetuwn wet;
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_SetSoftMaxVcn,
						      WENOIW_UMD_PSTATE_VCNCWK,
						      NUWW);
		if (wet)
			wetuwn wet;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK:
		smu->gfx_actuaw_hawd_min_fweq = smu->gfx_defauwt_hawd_min_fweq;
		smu->gfx_actuaw_soft_max_fweq = smu->gfx_defauwt_soft_max_fweq;

		wet = wenoiw_get_pwofiwing_cwk_mask(smu, wevew,
						    &scwk_mask,
						    &mcwk_mask,
						    &soc_mask);
		if (wet)
			wetuwn wet;
		wenoiw_fowce_cwk_wevews(smu, SMU_SCWK, 1 << scwk_mask);
		wenoiw_fowce_cwk_wevews(smu, SMU_MCWK, 1 << mcwk_mask);
		wenoiw_fowce_cwk_wevews(smu, SMU_SOCCWK, 1 << soc_mask);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		smu->gfx_actuaw_hawd_min_fweq = smu->gfx_defauwt_hawd_min_fweq;
		smu->gfx_actuaw_soft_max_fweq = smu->gfx_defauwt_soft_max_fweq;

		wet = wenoiw_set_peak_cwock_by_device(smu);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
	defauwt:
		bweak;
	}
	wetuwn wet;
}

/* save watewmawk settings into ppwib smu stwuctuwe,
 * awso pass data to smu contwowwew
 */
static int wenoiw_set_watewmawks_tabwe(
		stwuct smu_context *smu,
		stwuct pp_smu_wm_wange_sets *cwock_wanges)
{
	Watewmawks_t *tabwe = smu->smu_tabwe.watewmawks_tabwe;
	int wet = 0;
	int i;

	if (cwock_wanges) {
		if (cwock_wanges->num_weadew_wm_sets > NUM_WM_WANGES ||
		    cwock_wanges->num_wwitew_wm_sets > NUM_WM_WANGES)
			wetuwn -EINVAW;

		/* save into smu->smu_tabwe.tabwes[SMU_TABWE_WATEWMAWKS]->cpu_addw*/
		fow (i = 0; i < cwock_wanges->num_weadew_wm_sets; i++) {
			tabwe->WatewmawkWow[WM_DCFCWK][i].MinCwock =
				cwock_wanges->weadew_wm_sets[i].min_dwain_cwk_mhz;
			tabwe->WatewmawkWow[WM_DCFCWK][i].MaxCwock =
				cwock_wanges->weadew_wm_sets[i].max_dwain_cwk_mhz;
			tabwe->WatewmawkWow[WM_DCFCWK][i].MinMcwk =
				cwock_wanges->weadew_wm_sets[i].min_fiww_cwk_mhz;
			tabwe->WatewmawkWow[WM_DCFCWK][i].MaxMcwk =
				cwock_wanges->weadew_wm_sets[i].max_fiww_cwk_mhz;

			tabwe->WatewmawkWow[WM_DCFCWK][i].WmSetting =
				cwock_wanges->weadew_wm_sets[i].wm_inst;
			tabwe->WatewmawkWow[WM_DCFCWK][i].WmType =
				cwock_wanges->weadew_wm_sets[i].wm_type;
		}

		fow (i = 0; i < cwock_wanges->num_wwitew_wm_sets; i++) {
			tabwe->WatewmawkWow[WM_SOCCWK][i].MinCwock =
				cwock_wanges->wwitew_wm_sets[i].min_fiww_cwk_mhz;
			tabwe->WatewmawkWow[WM_SOCCWK][i].MaxCwock =
				cwock_wanges->wwitew_wm_sets[i].max_fiww_cwk_mhz;
			tabwe->WatewmawkWow[WM_SOCCWK][i].MinMcwk =
				cwock_wanges->wwitew_wm_sets[i].min_dwain_cwk_mhz;
			tabwe->WatewmawkWow[WM_SOCCWK][i].MaxMcwk =
				cwock_wanges->wwitew_wm_sets[i].max_dwain_cwk_mhz;

			tabwe->WatewmawkWow[WM_SOCCWK][i].WmSetting =
				cwock_wanges->wwitew_wm_sets[i].wm_inst;
			tabwe->WatewmawkWow[WM_SOCCWK][i].WmType =
				cwock_wanges->wwitew_wm_sets[i].wm_type;
		}

		smu->watewmawks_bitmap |= WATEWMAWKS_EXIST;
	}

	/* pass data to smu contwowwew */
	if ((smu->watewmawks_bitmap & WATEWMAWKS_EXIST) &&
	     !(smu->watewmawks_bitmap & WATEWMAWKS_WOADED)) {
		wet = smu_cmn_wwite_watewmawks_tabwe(smu);
		if (wet) {
			dev_eww(smu->adev->dev, "Faiwed to update WMTABWE!");
			wetuwn wet;
		}
		smu->watewmawks_bitmap |= WATEWMAWKS_WOADED;
	}

	wetuwn 0;
}

static int wenoiw_get_powew_pwofiwe_mode(stwuct smu_context *smu,
					   chaw *buf)
{
	uint32_t i, size = 0;
	int16_t wowkwoad_type = 0;

	if (!buf)
		wetuwn -EINVAW;

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

		size += sysfs_emit_at(buf, size, "%2d %14s%s\n",
			i, amdgpu_pp_pwofiwe_name[i], (i == smu->powew_pwofiwe_mode) ? "*" : " ");
	}

	wetuwn size;
}

static void wenoiw_get_ss_powew_pewcent(SmuMetwics_t *metwics,
					uint32_t *apu_pewcent, uint32_t *dgpu_pewcent)
{
	uint32_t apu_boost = 0;
	uint32_t dgpu_boost = 0;
	uint16_t apu_wimit = 0;
	uint16_t dgpu_wimit = 0;
	uint16_t apu_powew = 0;
	uint16_t dgpu_powew = 0;

	apu_powew = metwics->ApuPowew;
	apu_wimit = metwics->StapmOwiginawWimit;
	if (apu_powew > apu_wimit && apu_wimit != 0)
		apu_boost =  ((apu_powew - apu_wimit) * 100) / apu_wimit;
	apu_boost = (apu_boost > 100) ? 100 : apu_boost;

	dgpu_powew = metwics->dGpuPowew;
	if (metwics->StapmCuwwentWimit > metwics->StapmOwiginawWimit)
		dgpu_wimit = metwics->StapmCuwwentWimit - metwics->StapmOwiginawWimit;
	if (dgpu_powew > dgpu_wimit && dgpu_wimit != 0)
		dgpu_boost = ((dgpu_powew - dgpu_wimit) * 100) / dgpu_wimit;
	dgpu_boost = (dgpu_boost > 100) ? 100 : dgpu_boost;

	if (dgpu_boost >= apu_boost)
		apu_boost = 0;
	ewse
		dgpu_boost = 0;

	*apu_pewcent = apu_boost;
	*dgpu_pewcent = dgpu_boost;
}


static int wenoiw_get_smu_metwics_data(stwuct smu_context *smu,
				       MetwicsMembew_t membew,
				       uint32_t *vawue)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;

	SmuMetwics_t *metwics = (SmuMetwics_t *)smu_tabwe->metwics_tabwe;
	int wet = 0;
	uint32_t apu_pewcent = 0;
	uint32_t dgpu_pewcent = 0;
	stwuct amdgpu_device *adev = smu->adev;


	wet = smu_cmn_get_metwics_tabwe(smu,
					NUWW,
					fawse);
	if (wet)
		wetuwn wet;

	switch (membew) {
	case METWICS_AVEWAGE_GFXCWK:
		*vawue = metwics->CwockFwequency[CWOCK_GFXCWK];
		bweak;
	case METWICS_AVEWAGE_SOCCWK:
		*vawue = metwics->CwockFwequency[CWOCK_SOCCWK];
		bweak;
	case METWICS_AVEWAGE_UCWK:
		*vawue = metwics->CwockFwequency[CWOCK_FCWK];
		bweak;
	case METWICS_AVEWAGE_GFXACTIVITY:
		*vawue = metwics->AvewageGfxActivity / 100;
		bweak;
	case METWICS_AVEWAGE_VCNACTIVITY:
		*vawue = metwics->AvewageUvdActivity / 100;
		bweak;
	case METWICS_CUWW_SOCKETPOWEW:
		if (((amdgpu_ip_vewsion(adev, MP1_HWIP, 0) ==
		      IP_VEWSION(12, 0, 1)) &&
		     (adev->pm.fw_vewsion >= 0x40000f)) ||
		    ((amdgpu_ip_vewsion(adev, MP1_HWIP, 0) ==
		      IP_VEWSION(12, 0, 0)) &&
		     (adev->pm.fw_vewsion >= 0x373200)))
			*vawue = metwics->CuwwentSocketPowew << 8;
		ewse
			*vawue = (metwics->CuwwentSocketPowew << 8) / 1000;
		bweak;
	case METWICS_TEMPEWATUWE_EDGE:
		*vawue = (metwics->GfxTempewatuwe / 100) *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_HOTSPOT:
		*vawue = (metwics->SocTempewatuwe / 100) *
			SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_THWOTTWEW_STATUS:
		*vawue = metwics->ThwottwewStatus;
		bweak;
	case METWICS_VOWTAGE_VDDGFX:
		*vawue = metwics->Vowtage[0];
		bweak;
	case METWICS_VOWTAGE_VDDSOC:
		*vawue = metwics->Vowtage[1];
		bweak;
	case METWICS_SS_APU_SHAWE:
		/* wetuwn the pewcentage of APU powew boost
		 * with wespect to APU's powew wimit.
		 */
		wenoiw_get_ss_powew_pewcent(metwics, &apu_pewcent, &dgpu_pewcent);
		*vawue = apu_pewcent;
		bweak;
	case METWICS_SS_DGPU_SHAWE:
		/* wetuwn the pewcentage of dGPU powew boost
		 * with wespect to dGPU's powew wimit.
		 */
		wenoiw_get_ss_powew_pewcent(metwics, &apu_pewcent, &dgpu_pewcent);
		*vawue = dgpu_pewcent;
		bweak;
	defauwt:
		*vawue = UINT_MAX;
		bweak;
	}

	wetuwn wet;
}

static int wenoiw_wead_sensow(stwuct smu_context *smu,
				 enum amd_pp_sensows sensow,
				 void *data, uint32_t *size)
{
	int wet = 0;

	if (!data || !size)
		wetuwn -EINVAW;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_AVEWAGE_GFXACTIVITY,
						  (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_EDGE_TEMP:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_TEMPEWATUWE_EDGE,
						  (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_TEMPEWATUWE_HOTSPOT,
						  (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_AVEWAGE_UCWK,
						  (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_AVEWAGE_GFXCWK,
						  (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDGFX:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_VOWTAGE_VDDGFX,
						  (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDNB:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_VOWTAGE_VDDSOC,
						  (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_CUWW_SOCKETPOWEW,
						  (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_SS_APU_SHAWE:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_SS_APU_SHAWE,
						  (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_SS_DGPU_SHAWE:
		wet = wenoiw_get_smu_metwics_data(smu,
						  METWICS_SS_DGPU_SHAWE,
						  (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_AVG_POWEW:
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static boow wenoiw_is_dpm_wunning(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	/*
	 * Untiw now, the pmfw hasn't expowted the intewface of SMU
	 * featuwe mask to APU SKU so just fowce on aww the featuwe
	 * at eawwy initiaw stage.
	 */
	if (adev->in_suspend)
		wetuwn fawse;
	ewse
		wetuwn twue;

}

static ssize_t wenoiw_get_gpu_metwics(stwuct smu_context *smu,
				      void **tabwe)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct gpu_metwics_v2_2 *gpu_metwics =
		(stwuct gpu_metwics_v2_2 *)smu_tabwe->gpu_metwics_tabwe;
	SmuMetwics_t metwics;
	int wet = 0;

	wet = smu_cmn_get_metwics_tabwe(smu, &metwics, twue);
	if (wet)
		wetuwn wet;

	smu_cmn_init_soft_gpu_metwics(gpu_metwics, 2, 2);

	gpu_metwics->tempewatuwe_gfx = metwics.GfxTempewatuwe;
	gpu_metwics->tempewatuwe_soc = metwics.SocTempewatuwe;
	memcpy(&gpu_metwics->tempewatuwe_cowe[0],
		&metwics.CoweTempewatuwe[0],
		sizeof(uint16_t) * 8);
	gpu_metwics->tempewatuwe_w3[0] = metwics.W3Tempewatuwe[0];
	gpu_metwics->tempewatuwe_w3[1] = metwics.W3Tempewatuwe[1];

	gpu_metwics->avewage_gfx_activity = metwics.AvewageGfxActivity;
	gpu_metwics->avewage_mm_activity = metwics.AvewageUvdActivity;

	gpu_metwics->avewage_socket_powew = metwics.CuwwentSocketPowew;
	gpu_metwics->avewage_cpu_powew = metwics.Powew[0];
	gpu_metwics->avewage_soc_powew = metwics.Powew[1];
	memcpy(&gpu_metwics->avewage_cowe_powew[0],
		&metwics.CowePowew[0],
		sizeof(uint16_t) * 8);

	gpu_metwics->avewage_gfxcwk_fwequency = metwics.AvewageGfxcwkFwequency;
	gpu_metwics->avewage_soccwk_fwequency = metwics.AvewageSoccwkFwequency;
	gpu_metwics->avewage_fcwk_fwequency = metwics.AvewageFcwkFwequency;
	gpu_metwics->avewage_vcwk_fwequency = metwics.AvewageVcwkFwequency;

	gpu_metwics->cuwwent_gfxcwk = metwics.CwockFwequency[CWOCK_GFXCWK];
	gpu_metwics->cuwwent_soccwk = metwics.CwockFwequency[CWOCK_SOCCWK];
	gpu_metwics->cuwwent_ucwk = metwics.CwockFwequency[CWOCK_UMCCWK];
	gpu_metwics->cuwwent_fcwk = metwics.CwockFwequency[CWOCK_FCWK];
	gpu_metwics->cuwwent_vcwk = metwics.CwockFwequency[CWOCK_VCWK];
	gpu_metwics->cuwwent_dcwk = metwics.CwockFwequency[CWOCK_DCWK];
	memcpy(&gpu_metwics->cuwwent_cowecwk[0],
		&metwics.CoweFwequency[0],
		sizeof(uint16_t) * 8);
	gpu_metwics->cuwwent_w3cwk[0] = metwics.W3Fwequency[0];
	gpu_metwics->cuwwent_w3cwk[1] = metwics.W3Fwequency[1];

	gpu_metwics->thwottwe_status = metwics.ThwottwewStatus;
	gpu_metwics->indep_thwottwe_status =
		smu_cmn_get_indep_thwottwew_status(metwics.ThwottwewStatus,
						   wenoiw_thwottwew_map);

	gpu_metwics->fan_pwm = metwics.FanPwm;

	gpu_metwics->system_cwock_countew = ktime_get_boottime_ns();

	*tabwe = (void *)gpu_metwics;

	wetuwn sizeof(stwuct gpu_metwics_v2_2);
}

static int wenoiw_gfx_state_change_set(stwuct smu_context *smu, uint32_t state)
{

	wetuwn 0;
}

static int wenoiw_get_enabwed_mask(stwuct smu_context *smu,
				   uint64_t *featuwe_mask)
{
	if (!featuwe_mask)
		wetuwn -EINVAW;
	memset(featuwe_mask, 0xff, sizeof(*featuwe_mask));

	wetuwn 0;
}

static const stwuct pptabwe_funcs wenoiw_ppt_funcs = {
	.set_powew_state = NUWW,
	.pwint_cwk_wevews = wenoiw_pwint_cwk_wevews,
	.get_cuwwent_powew_state = wenoiw_get_cuwwent_powew_state,
	.dpm_set_vcn_enabwe = wenoiw_dpm_set_vcn_enabwe,
	.dpm_set_jpeg_enabwe = wenoiw_dpm_set_jpeg_enabwe,
	.fowce_cwk_wevews = wenoiw_fowce_cwk_wevews,
	.set_powew_pwofiwe_mode = wenoiw_set_powew_pwofiwe_mode,
	.set_pewfowmance_wevew = wenoiw_set_pewfowmance_wevew,
	.get_dpm_cwock_tabwe = wenoiw_get_dpm_cwock_tabwe,
	.set_watewmawks_tabwe = wenoiw_set_watewmawks_tabwe,
	.get_powew_pwofiwe_mode = wenoiw_get_powew_pwofiwe_mode,
	.wead_sensow = wenoiw_wead_sensow,
	.check_fw_status = smu_v12_0_check_fw_status,
	.check_fw_vewsion = smu_v12_0_check_fw_vewsion,
	.powewgate_sdma = smu_v12_0_powewgate_sdma,
	.send_smc_msg_with_pawam = smu_cmn_send_smc_msg_with_pawam,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.set_gfx_cgpg = smu_v12_0_set_gfx_cgpg,
	.gfx_off_contwow = smu_v12_0_gfx_off_contwow,
	.get_gfx_off_status = smu_v12_0_get_gfxoff_status,
	.init_smc_tabwes = wenoiw_init_smc_tabwes,
	.fini_smc_tabwes = smu_v12_0_fini_smc_tabwes,
	.set_defauwt_dpm_tabwe = smu_v12_0_set_defauwt_dpm_tabwes,
	.get_enabwed_mask = wenoiw_get_enabwed_mask,
	.featuwe_is_enabwed = smu_cmn_featuwe_is_enabwed,
	.disabwe_aww_featuwes_with_exception = smu_cmn_disabwe_aww_featuwes_with_exception,
	.get_dpm_uwtimate_fweq = wenoiw_get_dpm_uwtimate_fweq,
	.mode2_weset = smu_v12_0_mode2_weset,
	.set_soft_fweq_wimited_wange = smu_v12_0_set_soft_fweq_wimited_wange,
	.set_dwivew_tabwe_wocation = smu_v12_0_set_dwivew_tabwe_wocation,
	.is_dpm_wunning = wenoiw_is_dpm_wunning,
	.get_pp_featuwe_mask = smu_cmn_get_pp_featuwe_mask,
	.set_pp_featuwe_mask = smu_cmn_set_pp_featuwe_mask,
	.get_gpu_metwics = wenoiw_get_gpu_metwics,
	.gfx_state_change_set = wenoiw_gfx_state_change_set,
	.set_fine_gwain_gfx_fweq_pawametews = wenoiw_set_fine_gwain_gfx_fweq_pawametews,
	.od_edit_dpm_tabwe = wenoiw_od_edit_dpm_tabwe,
	.get_vbios_bootup_vawues = smu_v12_0_get_vbios_bootup_vawues,
};

void wenoiw_set_ppt_funcs(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	smu->ppt_funcs = &wenoiw_ppt_funcs;
	smu->message_map = wenoiw_message_map;
	smu->cwock_map = wenoiw_cwk_map;
	smu->tabwe_map = wenoiw_tabwe_map;
	smu->wowkwoad_map = wenoiw_wowkwoad_map;
	smu->smc_dwivew_if_vewsion = SMU12_DWIVEW_IF_VEWSION;
	smu->is_apu = twue;
	smu->pawam_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_82);
	smu->msg_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_66);
	smu->wesp_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);
}
