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

#incwude "smu_types.h"
#define SWSMU_CODE_WAYEW_W2

#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "smu_v13_0.h"
#incwude "smu13_dwivew_if_v13_0_4.h"
#incwude "smu_v13_0_4_ppt.h"
#incwude "smu_v13_0_4_ppsmc.h"
#incwude "smu_v13_0_4_pmfw.h"
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

#define mmMP1_SMN_C2PMSG_66			0x0282
#define mmMP1_SMN_C2PMSG_66_BASE_IDX            1

#define mmMP1_SMN_C2PMSG_82			0x0292
#define mmMP1_SMN_C2PMSG_82_BASE_IDX            1

#define mmMP1_SMN_C2PMSG_90			0x029a
#define mmMP1_SMN_C2PMSG_90_BASE_IDX		1

#define FEATUWE_MASK(featuwe) (1UWW << featuwe)

#define SMU_13_0_4_UMD_PSTATE_GFXCWK			938
#define SMU_13_0_4_UMD_PSTATE_SOCCWK			938
#define SMU_13_0_4_UMD_PSTATE_FCWK			1875

#define SMC_DPM_FEATUWE ( \
	FEATUWE_MASK(FEATUWE_CCWK_DPM_BIT) | \
	FEATUWE_MASK(FEATUWE_VCN_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_FCWK_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_SOCCWK_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_MP0CWK_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_WCWK_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_SHUBCWK_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_DCFCWK_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_ISP_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_IPU_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_GFX_DPM_BIT))

static stwuct cmn2asic_msg_mapping smu_v13_0_4_message_map[SMU_MSG_MAX_COUNT] = {
	MSG_MAP(TestMessage,                    PPSMC_MSG_TestMessage,			1),
	MSG_MAP(GetSmuVewsion,                  PPSMC_MSG_GetPmfwVewsion,		1),
	MSG_MAP(GetDwivewIfVewsion,             PPSMC_MSG_GetDwivewIfVewsion,		1),
	MSG_MAP(AwwowGfxOff,                    PPSMC_MSG_AwwowGfxOff,			1),
	MSG_MAP(DisawwowGfxOff,                 PPSMC_MSG_DisawwowGfxOff,		1),
	MSG_MAP(PowewDownVcn,                   PPSMC_MSG_PowewDownVcn,			1),
	MSG_MAP(PowewUpVcn,                     PPSMC_MSG_PowewUpVcn,			1),
	MSG_MAP(SetHawdMinVcn,                  PPSMC_MSG_SetHawdMinVcn,		1),
	MSG_MAP(PwepaweMp1FowUnwoad,            PPSMC_MSG_PwepaweMp1FowUnwoad,		1),
	MSG_MAP(SetDwivewDwamAddwHigh,          PPSMC_MSG_SetDwivewDwamAddwHigh,	1),
	MSG_MAP(SetDwivewDwamAddwWow,           PPSMC_MSG_SetDwivewDwamAddwWow,		1),
	MSG_MAP(TwansfewTabweSmu2Dwam,          PPSMC_MSG_TwansfewTabweSmu2Dwam,	1),
	MSG_MAP(TwansfewTabweDwam2Smu,          PPSMC_MSG_TwansfewTabweDwam2Smu,	1),
	MSG_MAP(GfxDeviceDwivewWeset,           PPSMC_MSG_GfxDeviceDwivewWeset,		1),
	MSG_MAP(GetEnabwedSmuFeatuwes,          PPSMC_MSG_GetEnabwedSmuFeatuwes,	1),
	MSG_MAP(SetHawdMinSoccwkByFweq,         PPSMC_MSG_SetHawdMinSoccwkByFweq,	1),
	MSG_MAP(SetSoftMinVcn,                  PPSMC_MSG_SetSoftMinVcn,		1),
	MSG_MAP(GetGfxcwkFwequency,             PPSMC_MSG_GetGfxcwkFwequency,		1),
	MSG_MAP(GetFcwkFwequency,               PPSMC_MSG_GetFcwkFwequency,		1),
	MSG_MAP(SetSoftMaxGfxCwk,               PPSMC_MSG_SetSoftMaxGfxCwk,		1),
	MSG_MAP(SetHawdMinGfxCwk,               PPSMC_MSG_SetHawdMinGfxCwk,		1),
	MSG_MAP(SetSoftMaxSoccwkByFweq,         PPSMC_MSG_SetSoftMaxSoccwkByFweq,	1),
	MSG_MAP(SetSoftMaxFcwkByFweq,           PPSMC_MSG_SetSoftMaxFcwkByFweq,		1),
	MSG_MAP(SetSoftMaxVcn,                  PPSMC_MSG_SetSoftMaxVcn,		1),
	MSG_MAP(SetPowewWimitPewcentage,        PPSMC_MSG_SetPowewWimitPewcentage,	1),
	MSG_MAP(PowewDownJpeg,                  PPSMC_MSG_PowewDownJpeg,		1),
	MSG_MAP(PowewUpJpeg,                    PPSMC_MSG_PowewUpJpeg,			1),
	MSG_MAP(SetHawdMinFcwkByFweq,           PPSMC_MSG_SetHawdMinFcwkByFweq,		1),
	MSG_MAP(SetSoftMinSoccwkByFweq,         PPSMC_MSG_SetSoftMinSoccwkByFweq,	1),
	MSG_MAP(EnabweGfxImu,                   PPSMC_MSG_EnabweGfxImu,			1),
	MSG_MAP(PowewUpIspByTiwe,               PPSMC_MSG_PowewUpIspByTiwe,		1),
	MSG_MAP(PowewDownIspByTiwe,             PPSMC_MSG_PowewDownIspByTiwe,		1),
};

static stwuct cmn2asic_mapping smu_v13_0_4_featuwe_mask_map[SMU_FEATUWE_COUNT] = {
	FEA_MAP(CCWK_DPM),
	FEA_MAP(FAN_CONTWOWWEW),
	FEA_MAP(PPT),
	FEA_MAP(TDC),
	FEA_MAP(THEWMAW),
	FEA_MAP(VCN_DPM),
	FEA_MAP_WEVEWSE(FCWK),
	FEA_MAP_WEVEWSE(SOCCWK),
	FEA_MAP(WCWK_DPM),
	FEA_MAP(SHUBCWK_DPM),
	FEA_MAP(DCFCWK_DPM),
	FEA_MAP_HAWF_WEVEWSE(GFX),
	FEA_MAP(DS_GFXCWK),
	FEA_MAP(DS_SOCCWK),
	FEA_MAP(DS_WCWK),
	FEA_MAP(DS_DCFCWK),
	FEA_MAP(DS_FCWK),
	FEA_MAP(DS_MP1CWK),
	FEA_MAP(DS_MP0CWK),
	FEA_MAP(GFX_DEM),
	FEA_MAP(PSI),
	FEA_MAP(PWOCHOT),
	FEA_MAP(CPUOFF),
	FEA_MAP(STAPM),
	FEA_MAP(S0I3),
	FEA_MAP(PEWF_WIMIT),
	FEA_MAP(COWE_DWDO),
	FEA_MAP(DS_VCN),
	FEA_MAP(CPPC),
	FEA_MAP(DF_CSTATES),
	FEA_MAP(ATHUB_PG),
};

static stwuct cmn2asic_mapping smu_v13_0_4_tabwe_map[SMU_TABWE_COUNT] = {
	TAB_MAP_VAWID(WATEWMAWKS),
	TAB_MAP_VAWID(SMU_METWICS),
	TAB_MAP_VAWID(CUSTOM_DPM),
	TAB_MAP_VAWID(DPMCWOCKS),
};

static int smu_v13_0_4_init_smc_tabwes(stwuct smu_context *smu)
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

	smu_tabwe->gpu_metwics_tabwe_size = sizeof(stwuct gpu_metwics_v2_1);
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

static int smu_v13_0_4_fini_smc_tabwes(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;

	kfwee(smu_tabwe->cwocks_tabwe);
	smu_tabwe->cwocks_tabwe = NUWW;

	kfwee(smu_tabwe->metwics_tabwe);
	smu_tabwe->metwics_tabwe = NUWW;

	kfwee(smu_tabwe->watewmawks_tabwe);
	smu_tabwe->watewmawks_tabwe = NUWW;

	kfwee(smu_tabwe->gpu_metwics_tabwe);
	smu_tabwe->gpu_metwics_tabwe = NUWW;

	wetuwn 0;
}

static boow smu_v13_0_4_is_dpm_wunning(stwuct smu_context *smu)
{
	int wet = 0;
	uint64_t featuwe_enabwed;

	wet = smu_cmn_get_enabwed_mask(smu, &featuwe_enabwed);

	if (wet)
		wetuwn fawse;

	wetuwn !!(featuwe_enabwed & SMC_DPM_FEATUWE);
}

static int smu_v13_0_4_system_featuwes_contwow(stwuct smu_context *smu, boow en)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if (!en && !adev->in_s0ix)
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_PwepaweMp1FowUnwoad, NUWW);

	wetuwn wet;
}

static ssize_t smu_v13_0_4_get_gpu_metwics(stwuct smu_context *smu,
					   void **tabwe)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct gpu_metwics_v2_1 *gpu_metwics =
		(stwuct gpu_metwics_v2_1 *)smu_tabwe->gpu_metwics_tabwe;
	SmuMetwics_t metwics;
	int wet = 0;

	wet = smu_cmn_get_metwics_tabwe(smu, &metwics, twue);
	if (wet)
		wetuwn wet;

	smu_cmn_init_soft_gpu_metwics(gpu_metwics, 2, 1);

	gpu_metwics->tempewatuwe_gfx = metwics.GfxTempewatuwe;
	gpu_metwics->tempewatuwe_soc = metwics.SocTempewatuwe;
	memcpy(&gpu_metwics->tempewatuwe_cowe[0],
		&metwics.CoweTempewatuwe[0],
		sizeof(uint16_t) * 8);
	gpu_metwics->tempewatuwe_w3[0] = metwics.W3Tempewatuwe;

	gpu_metwics->avewage_gfx_activity = metwics.GfxActivity;
	gpu_metwics->avewage_mm_activity = metwics.UvdActivity;

	gpu_metwics->avewage_socket_powew = metwics.AvewageSocketPowew;
	gpu_metwics->avewage_gfx_powew = metwics.Powew[0];
	gpu_metwics->avewage_soc_powew = metwics.Powew[1];
	memcpy(&gpu_metwics->avewage_cowe_powew[0],
		&metwics.CowePowew[0],
		sizeof(uint16_t) * 8);

	gpu_metwics->avewage_gfxcwk_fwequency = metwics.GfxcwkFwequency;
	gpu_metwics->avewage_soccwk_fwequency = metwics.SoccwkFwequency;
	gpu_metwics->avewage_ucwk_fwequency = metwics.MemcwkFwequency;
	gpu_metwics->avewage_fcwk_fwequency = metwics.MemcwkFwequency;
	gpu_metwics->avewage_vcwk_fwequency = metwics.VcwkFwequency;
	gpu_metwics->avewage_dcwk_fwequency = metwics.DcwkFwequency;

	memcpy(&gpu_metwics->cuwwent_cowecwk[0],
		&metwics.CoweFwequency[0],
		sizeof(uint16_t) * 8);
	gpu_metwics->cuwwent_w3cwk[0] = metwics.W3Fwequency;

	gpu_metwics->thwottwe_status = metwics.ThwottwewStatus;

	gpu_metwics->system_cwock_countew = ktime_get_boottime_ns();

	*tabwe = (void *)gpu_metwics;

	wetuwn sizeof(stwuct gpu_metwics_v2_1);
}

static int smu_v13_0_4_get_smu_metwics_data(stwuct smu_context *smu,
					    MetwicsMembew_t membew,
					    uint32_t *vawue)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;

	SmuMetwics_t *metwics = (SmuMetwics_t *)smu_tabwe->metwics_tabwe;
	int wet = 0;

	wet = smu_cmn_get_metwics_tabwe(smu, NUWW, fawse);
	if (wet)
		wetuwn wet;

	switch (membew) {
	case METWICS_AVEWAGE_GFXCWK:
		*vawue = metwics->GfxcwkFwequency;
		bweak;
	case METWICS_AVEWAGE_SOCCWK:
		*vawue = metwics->SoccwkFwequency;
		bweak;
	case METWICS_AVEWAGE_VCWK:
		*vawue = metwics->VcwkFwequency;
		bweak;
	case METWICS_AVEWAGE_DCWK:
		*vawue = metwics->DcwkFwequency;
		bweak;
	case METWICS_AVEWAGE_UCWK:
		*vawue = metwics->MemcwkFwequency;
		bweak;
	case METWICS_AVEWAGE_GFXACTIVITY:
		*vawue = metwics->GfxActivity / 100;
		bweak;
	case METWICS_AVEWAGE_VCNACTIVITY:
		*vawue = metwics->UvdActivity;
		bweak;
	case METWICS_AVEWAGE_SOCKETPOWEW:
		*vawue = (metwics->AvewageSocketPowew << 8) / 1000;
		bweak;
	case METWICS_CUWW_SOCKETPOWEW:
		*vawue = (metwics->CuwwentSocketPowew << 8) / 1000;
		bweak;
	case METWICS_TEMPEWATUWE_EDGE:
		*vawue = metwics->GfxTempewatuwe / 100 *
		SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_HOTSPOT:
		*vawue = metwics->SocTempewatuwe / 100 *
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
		/* wetuwn the pewcentage of APU powew with wespect to APU's powew wimit.
		 * pewcentage is wepowted, this isn't boost vawue. Smawtshift powew
		 * boost/shift is onwy when the pewcentage is mowe than 100.
		 */
		if (metwics->StapmOpnWimit > 0)
			*vawue =  (metwics->ApuPowew * 100) / metwics->StapmOpnWimit;
		ewse
			*vawue = 0;
		bweak;
	case METWICS_SS_DGPU_SHAWE:
		/* wetuwn the pewcentage of dGPU powew with wespect to dGPU's powew wimit.
		 * pewcentage is wepowted, this isn't boost vawue. Smawtshift powew
		 * boost/shift is onwy when the pewcentage is mowe than 100.
		 */
		if ((metwics->dGpuPowew > 0) &&
		    (metwics->StapmCuwwentWimit > metwics->StapmOpnWimit))
			*vawue = (metwics->dGpuPowew * 100) /
				 (metwics->StapmCuwwentWimit - metwics->StapmOpnWimit);
		ewse
			*vawue = 0;
		bweak;
	defauwt:
		*vawue = UINT_MAX;
		bweak;
	}

	wetuwn wet;
}

static int smu_v13_0_4_get_cuwwent_cwk_fweq(stwuct smu_context *smu,
					    enum smu_cwk_type cwk_type,
					    uint32_t *vawue)
{
	MetwicsMembew_t membew_type;

	switch (cwk_type) {
	case SMU_SOCCWK:
		membew_type = METWICS_AVEWAGE_SOCCWK;
		bweak;
	case SMU_VCWK:
		membew_type = METWICS_AVEWAGE_VCWK;
		bweak;
	case SMU_DCWK:
		membew_type = METWICS_AVEWAGE_DCWK;
		bweak;
	case SMU_MCWK:
		membew_type = METWICS_AVEWAGE_UCWK;
		bweak;
	case SMU_FCWK:
		wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
						       SMU_MSG_GetFcwkFwequency,
						       0, vawue);
	case SMU_GFXCWK:
	case SMU_SCWK:
		wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
						       SMU_MSG_GetGfxcwkFwequency,
						       0, vawue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn smu_v13_0_4_get_smu_metwics_data(smu, membew_type, vawue);
}

static int smu_v13_0_4_get_dpm_fweq_by_index(stwuct smu_context *smu,
					     enum smu_cwk_type cwk_type,
					     uint32_t dpm_wevew,
					     uint32_t *fweq)
{
	DpmCwocks_t *cwk_tabwe = smu->smu_tabwe.cwocks_tabwe;

	if (!cwk_tabwe || cwk_type >= SMU_CWK_COUNT)
		wetuwn -EINVAW;

	switch (cwk_type) {
	case SMU_SOCCWK:
		if (dpm_wevew >= cwk_tabwe->NumSocCwkWevewsEnabwed)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->SocCwocks[dpm_wevew];
		bweak;
	case SMU_VCWK:
		if (dpm_wevew >= cwk_tabwe->VcnCwkWevewsEnabwed)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->VCwocks[dpm_wevew];
		bweak;
	case SMU_DCWK:
		if (dpm_wevew >= cwk_tabwe->VcnCwkWevewsEnabwed)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->DCwocks[dpm_wevew];
		bweak;
	case SMU_UCWK:
	case SMU_MCWK:
		if (dpm_wevew >= cwk_tabwe->NumDfPstatesEnabwed)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->DfPstateTabwe[dpm_wevew].MemCwk;
		bweak;
	case SMU_FCWK:
		if (dpm_wevew >= cwk_tabwe->NumDfPstatesEnabwed)
			wetuwn -EINVAW;
		*fweq = cwk_tabwe->DfPstateTabwe[dpm_wevew].FCwk;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int smu_v13_0_4_get_dpm_wevew_count(stwuct smu_context *smu,
					   enum smu_cwk_type cwk_type,
					   uint32_t *count)
{
	DpmCwocks_t *cwk_tabwe = smu->smu_tabwe.cwocks_tabwe;

	switch (cwk_type) {
	case SMU_SOCCWK:
		*count = cwk_tabwe->NumSocCwkWevewsEnabwed;
		bweak;
	case SMU_VCWK:
		*count = cwk_tabwe->VcnCwkWevewsEnabwed;
		bweak;
	case SMU_DCWK:
		*count = cwk_tabwe->VcnCwkWevewsEnabwed;
		bweak;
	case SMU_MCWK:
		*count = cwk_tabwe->NumDfPstatesEnabwed;
		bweak;
	case SMU_FCWK:
		*count = cwk_tabwe->NumDfPstatesEnabwed;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int smu_v13_0_4_pwint_cwk_wevews(stwuct smu_context *smu,
					enum smu_cwk_type cwk_type, chaw *buf)
{
	int i, idx, size = 0, wet = 0;
	uint32_t cuw_vawue = 0, vawue = 0, count = 0;
	uint32_t min, max;

	smu_cmn_get_sysfs_buf(&buf, &size);

	switch (cwk_type) {
	case SMU_OD_SCWK:
		size += sysfs_emit_at(buf, size, "%s:\n", "OD_SCWK");
		size += sysfs_emit_at(buf, size, "0: %10uMhz\n",
		(smu->gfx_actuaw_hawd_min_fweq > 0) ? smu->gfx_actuaw_hawd_min_fweq : smu->gfx_defauwt_hawd_min_fweq);
		size += sysfs_emit_at(buf, size, "1: %10uMhz\n",
		(smu->gfx_actuaw_soft_max_fweq > 0) ? smu->gfx_actuaw_soft_max_fweq : smu->gfx_defauwt_soft_max_fweq);
		bweak;
	case SMU_OD_WANGE:
		size += sysfs_emit_at(buf, size, "%s:\n", "OD_WANGE");
		size += sysfs_emit_at(buf, size, "SCWK: %7uMhz %10uMhz\n",
				      smu->gfx_defauwt_hawd_min_fweq,
				      smu->gfx_defauwt_soft_max_fweq);
		bweak;
	case SMU_SOCCWK:
	case SMU_VCWK:
	case SMU_DCWK:
	case SMU_MCWK:
	case SMU_FCWK:
		wet = smu_v13_0_4_get_cuwwent_cwk_fweq(smu, cwk_type, &cuw_vawue);
		if (wet)
			bweak;

		wet = smu_v13_0_4_get_dpm_wevew_count(smu, cwk_type, &count);
		if (wet)
			bweak;

		fow (i = 0; i < count; i++) {
			idx = (cwk_type == SMU_FCWK || cwk_type == SMU_MCWK) ? (count - i - 1) : i;
			wet = smu_v13_0_4_get_dpm_fweq_by_index(smu, cwk_type, idx, &vawue);
			if (wet)
				bweak;

			size += sysfs_emit_at(buf, size, "%d: %uMhz %s\n", i, vawue,
					      cuw_vawue == vawue ? "*" : "");
		}
		bweak;
	case SMU_GFXCWK:
	case SMU_SCWK:
		wet = smu_v13_0_4_get_cuwwent_cwk_fweq(smu, cwk_type, &cuw_vawue);
		if (wet)
			bweak;
		min = (smu->gfx_actuaw_hawd_min_fweq > 0) ? smu->gfx_actuaw_hawd_min_fweq : smu->gfx_defauwt_hawd_min_fweq;
		max = (smu->gfx_actuaw_soft_max_fweq > 0) ? smu->gfx_actuaw_soft_max_fweq : smu->gfx_defauwt_soft_max_fweq;
		if (cuw_vawue  == max)
			i = 2;
		ewse if (cuw_vawue == min)
			i = 0;
		ewse
			i = 1;
		size += sysfs_emit_at(buf, size, "0: %uMhz %s\n", min,
				      i == 0 ? "*" : "");
		size += sysfs_emit_at(buf, size, "1: %uMhz %s\n",
				      i == 1 ? cuw_vawue : 1100, /* UMD PSTATE GFXCWK 1100 */
				      i == 1 ? "*" : "");
		size += sysfs_emit_at(buf, size, "2: %uMhz %s\n", max,
				      i == 2 ? "*" : "");
		bweak;
	defauwt:
		bweak;
	}

	wetuwn size;
}

static int smu_v13_0_4_wead_sensow(stwuct smu_context *smu,
				   enum amd_pp_sensows sensow,
				   void *data, uint32_t *size)
{
	int wet = 0;

	if (!data || !size)
		wetuwn -EINVAW;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_AVEWAGE_GFXACTIVITY,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_AVG_POWEW:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_AVEWAGE_SOCKETPOWEW,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_CUWW_SOCKETPOWEW,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_EDGE_TEMP:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_TEMPEWATUWE_EDGE,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_TEMPEWATUWE_HOTSPOT,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_AVEWAGE_UCWK,
						       (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_AVEWAGE_GFXCWK,
						       (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDGFX:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_VOWTAGE_VDDGFX,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDNB:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_VOWTAGE_VDDSOC,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_SS_APU_SHAWE:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_SS_APU_SHAWE,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_SS_DGPU_SHAWE:
		wet = smu_v13_0_4_get_smu_metwics_data(smu,
						       METWICS_SS_DGPU_SHAWE,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int smu_v13_0_4_set_watewmawks_tabwe(stwuct smu_context *smu,
					    stwuct pp_smu_wm_wange_sets *cwock_wanges)
{
	int i;
	int wet = 0;
	Watewmawks_t *tabwe = smu->smu_tabwe.watewmawks_tabwe;

	if (!tabwe || !cwock_wanges)
		wetuwn -EINVAW;

	if (cwock_wanges->num_weadew_wm_sets > NUM_WM_WANGES ||
		cwock_wanges->num_wwitew_wm_sets > NUM_WM_WANGES)
		wetuwn -EINVAW;

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
	}

	smu->watewmawks_bitmap |= WATEWMAWKS_EXIST;

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

static boow smu_v13_0_4_cwk_dpm_is_enabwed(stwuct smu_context *smu,
					   enum smu_cwk_type cwk_type)
{
	enum smu_featuwe_mask featuwe_id = 0;

	switch (cwk_type) {
	case SMU_MCWK:
	case SMU_UCWK:
	case SMU_FCWK:
		featuwe_id = SMU_FEATUWE_DPM_FCWK_BIT;
		bweak;
	case SMU_GFXCWK:
	case SMU_SCWK:
		featuwe_id = SMU_FEATUWE_DPM_GFXCWK_BIT;
		bweak;
	case SMU_SOCCWK:
		featuwe_id = SMU_FEATUWE_DPM_SOCCWK_BIT;
		bweak;
	case SMU_VCWK:
	case SMU_DCWK:
		featuwe_id = SMU_FEATUWE_VCN_DPM_BIT;
		bweak;
	defauwt:
		wetuwn twue;
	}

	wetuwn smu_cmn_featuwe_is_enabwed(smu, featuwe_id);
}

static int smu_v13_0_4_get_dpm_uwtimate_fweq(stwuct smu_context *smu,
					     enum smu_cwk_type cwk_type,
					     uint32_t *min,
					     uint32_t *max)
{
	DpmCwocks_t *cwk_tabwe = smu->smu_tabwe.cwocks_tabwe;
	uint32_t cwock_wimit;
	uint32_t max_dpm_wevew, min_dpm_wevew;
	int wet = 0;

	if (!smu_v13_0_4_cwk_dpm_is_enabwed(smu, cwk_type)) {
		switch (cwk_type) {
		case SMU_MCWK:
		case SMU_UCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.ucwk;
			bweak;
		case SMU_FCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.fcwk;
			bweak;
		case SMU_GFXCWK:
		case SMU_SCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.gfxcwk;
			bweak;
		case SMU_SOCCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.soccwk;
			bweak;
		case SMU_VCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.vcwk;
			bweak;
		case SMU_DCWK:
			cwock_wimit = smu->smu_tabwe.boot_vawues.dcwk;
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
		switch (cwk_type) {
		case SMU_GFXCWK:
		case SMU_SCWK:
			*max = cwk_tabwe->MaxGfxCwk;
			bweak;
		case SMU_MCWK:
		case SMU_UCWK:
		case SMU_FCWK:
			max_dpm_wevew = 0;
			bweak;
		case SMU_SOCCWK:
			max_dpm_wevew = cwk_tabwe->NumSocCwkWevewsEnabwed - 1;
			bweak;
		case SMU_VCWK:
		case SMU_DCWK:
			max_dpm_wevew = cwk_tabwe->VcnCwkWevewsEnabwed - 1;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (cwk_type != SMU_GFXCWK && cwk_type != SMU_SCWK) {
			wet = smu_v13_0_4_get_dpm_fweq_by_index(smu, cwk_type,
								max_dpm_wevew,
								max);
			if (wet)
				wetuwn wet;
		}
	}

	if (min) {
		switch (cwk_type) {
		case SMU_GFXCWK:
		case SMU_SCWK:
			*min = cwk_tabwe->MinGfxCwk;
			bweak;
		case SMU_MCWK:
		case SMU_UCWK:
		case SMU_FCWK:
			min_dpm_wevew = cwk_tabwe->NumDfPstatesEnabwed - 1;
			bweak;
		case SMU_SOCCWK:
			min_dpm_wevew = 0;
			bweak;
		case SMU_VCWK:
		case SMU_DCWK:
			min_dpm_wevew = 0;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (cwk_type != SMU_GFXCWK && cwk_type != SMU_SCWK) {
			wet = smu_v13_0_4_get_dpm_fweq_by_index(smu, cwk_type,
								min_dpm_wevew,
								min);
		}
	}

	wetuwn wet;
}

static int smu_v13_0_4_set_soft_fweq_wimited_wange(stwuct smu_context *smu,
						   enum smu_cwk_type cwk_type,
						   uint32_t min,
						   uint32_t max)
{
	enum smu_message_type msg_set_min, msg_set_max;
	uint32_t min_cwk = min;
	uint32_t max_cwk = max;
	int wet = 0;

	if (!smu_v13_0_4_cwk_dpm_is_enabwed(smu, cwk_type))
		wetuwn -EINVAW;

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
		msg_set_min = SMU_MSG_SetHawdMinGfxCwk;
		msg_set_max = SMU_MSG_SetSoftMaxGfxCwk;
		bweak;
	case SMU_FCWK:
		msg_set_min = SMU_MSG_SetHawdMinFcwkByFweq;
		msg_set_max = SMU_MSG_SetSoftMaxFcwkByFweq;
		bweak;
	case SMU_SOCCWK:
		msg_set_min = SMU_MSG_SetHawdMinSoccwkByFweq;
		msg_set_max = SMU_MSG_SetSoftMaxSoccwkByFweq;
		bweak;
	case SMU_VCWK:
	case SMU_DCWK:
		msg_set_min = SMU_MSG_SetHawdMinVcn;
		msg_set_max = SMU_MSG_SetSoftMaxVcn;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (cwk_type == SMU_VCWK) {
		min_cwk = min << SMU_13_VCWK_SHIFT;
		max_cwk = max << SMU_13_VCWK_SHIFT;
	}

	wet = smu_cmn_send_smc_msg_with_pawam(smu, msg_set_min, min_cwk, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn smu_cmn_send_smc_msg_with_pawam(smu, msg_set_max,
					       max_cwk, NUWW);
}

static int smu_v13_0_4_fowce_cwk_wevews(stwuct smu_context *smu,
					enum smu_cwk_type cwk_type,
					uint32_t mask)
{
	uint32_t soft_min_wevew = 0, soft_max_wevew = 0;
	uint32_t min_fweq = 0, max_fweq = 0;
	int wet = 0;

	soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
	soft_max_wevew = mask ? (fws(mask) - 1) : 0;

	switch (cwk_type) {
	case SMU_SOCCWK:
	case SMU_FCWK:
	case SMU_VCWK:
	case SMU_DCWK:
		wet = smu_v13_0_4_get_dpm_fweq_by_index(smu, cwk_type, soft_min_wevew, &min_fweq);
		if (wet)
			bweak;

		wet = smu_v13_0_4_get_dpm_fweq_by_index(smu, cwk_type, soft_max_wevew, &max_fweq);
		if (wet)
			bweak;

		wet = smu_v13_0_4_set_soft_fweq_wimited_wange(smu, cwk_type, min_fweq, max_fweq);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int smu_v13_0_4_get_dpm_pwofiwe_fweq(stwuct smu_context *smu,
					enum amd_dpm_fowced_wevew wevew,
					enum smu_cwk_type cwk_type,
					uint32_t *min_cwk,
					uint32_t *max_cwk)
{
	int wet = 0;
	uint32_t cwk_wimit = 0;

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
		cwk_wimit = SMU_13_0_4_UMD_PSTATE_GFXCWK;
		if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
			smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_SCWK, NUWW, &cwk_wimit);
		ewse if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK)
			smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_SCWK, &cwk_wimit, NUWW);
		bweak;
	case SMU_SOCCWK:
		cwk_wimit = SMU_13_0_4_UMD_PSTATE_SOCCWK;
		if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
			smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_SOCCWK, NUWW, &cwk_wimit);
		bweak;
	case SMU_FCWK:
		cwk_wimit = SMU_13_0_4_UMD_PSTATE_FCWK;
		if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
			smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_FCWK, NUWW, &cwk_wimit);
		ewse if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK)
			smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_FCWK, &cwk_wimit, NUWW);
		bweak;
	case SMU_VCWK:
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_VCWK, NUWW, &cwk_wimit);
		bweak;
	case SMU_DCWK:
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_DCWK, NUWW, &cwk_wimit);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	*min_cwk = *max_cwk = cwk_wimit;
	wetuwn wet;
}

static int smu_v13_0_4_set_pewfowmance_wevew(stwuct smu_context *smu,
					     enum amd_dpm_fowced_wevew wevew)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t scwk_min = 0, scwk_max = 0;
	uint32_t fcwk_min = 0, fcwk_max = 0;
	uint32_t soccwk_min = 0, soccwk_max = 0;
	uint32_t vcwk_min = 0, vcwk_max = 0;
	uint32_t dcwk_min = 0, dcwk_max = 0;
	int wet = 0;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_SCWK, NUWW, &scwk_max);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_FCWK, NUWW, &fcwk_max);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_SOCCWK, NUWW, &soccwk_max);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_VCWK, NUWW, &vcwk_max);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_DCWK, NUWW, &dcwk_max);
		scwk_min = scwk_max;
		fcwk_min = fcwk_max;
		soccwk_min = soccwk_max;
		vcwk_min = vcwk_max;
		dcwk_min = dcwk_max;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_WOW:
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_SCWK, &scwk_min, NUWW);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_FCWK, &fcwk_min, NUWW);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_SOCCWK, &soccwk_min, NUWW);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_VCWK, &vcwk_min, NUWW);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_DCWK, &dcwk_min, NUWW);
		scwk_max = scwk_min;
		fcwk_max = fcwk_min;
		soccwk_max = soccwk_min;
		vcwk_max = vcwk_min;
		dcwk_max = dcwk_min;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_AUTO:
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_SCWK, &scwk_min, &scwk_max);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_FCWK, &fcwk_min, &fcwk_max);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_SOCCWK, &soccwk_min, &soccwk_max);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_VCWK, &vcwk_min, &vcwk_max);
		smu_v13_0_4_get_dpm_uwtimate_fweq(smu, SMU_DCWK, &dcwk_min, &dcwk_max);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		smu_v13_0_4_get_dpm_pwofiwe_fweq(smu, wevew, SMU_SCWK, &scwk_min, &scwk_max);
		smu_v13_0_4_get_dpm_pwofiwe_fweq(smu, wevew, SMU_FCWK, &fcwk_min, &fcwk_max);
		smu_v13_0_4_get_dpm_pwofiwe_fweq(smu, wevew, SMU_SOCCWK, &soccwk_min, &soccwk_max);
		smu_v13_0_4_get_dpm_pwofiwe_fweq(smu, wevew, SMU_VCWK, &vcwk_min, &vcwk_max);
		smu_v13_0_4_get_dpm_pwofiwe_fweq(smu, wevew, SMU_DCWK, &dcwk_min, &dcwk_max);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
		wetuwn 0;
	defauwt:
		dev_eww(adev->dev, "Invawid pewfowmance wevew %d\n", wevew);
		wetuwn -EINVAW;
	}

	if (scwk_min && scwk_max) {
		wet = smu_v13_0_4_set_soft_fweq_wimited_wange(smu,
							      SMU_SCWK,
							      scwk_min,
							      scwk_max);
		if (wet)
			wetuwn wet;

		smu->gfx_actuaw_hawd_min_fweq = scwk_min;
		smu->gfx_actuaw_soft_max_fweq = scwk_max;
	}

	if (fcwk_min && fcwk_max) {
		wet = smu_v13_0_4_set_soft_fweq_wimited_wange(smu,
							      SMU_FCWK,
							      fcwk_min,
							      fcwk_max);
		if (wet)
			wetuwn wet;
	}

	if (soccwk_min && soccwk_max) {
		wet = smu_v13_0_4_set_soft_fweq_wimited_wange(smu,
							      SMU_SOCCWK,
							      soccwk_min,
							      soccwk_max);
		if (wet)
			wetuwn wet;
	}

	if (vcwk_min && vcwk_max) {
		wet = smu_v13_0_4_set_soft_fweq_wimited_wange(smu,
							      SMU_VCWK,
							      vcwk_min,
							      vcwk_max);
		if (wet)
			wetuwn wet;
	}

	if (dcwk_min && dcwk_max) {
		wet = smu_v13_0_4_set_soft_fweq_wimited_wange(smu,
							      SMU_DCWK,
							      dcwk_min,
							      dcwk_max);
		if (wet)
			wetuwn wet;
	}
	wetuwn wet;
}

static int smu_v13_0_4_mode2_weset(stwuct smu_context *smu)
{
	wetuwn smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GfxDeviceDwivewWeset,
					       SMU_WESET_MODE_2, NUWW);
}

static int smu_v13_0_4_set_fine_gwain_gfx_fweq_pawametews(stwuct smu_context *smu)
{
	DpmCwocks_t *cwk_tabwe = smu->smu_tabwe.cwocks_tabwe;

	smu->gfx_defauwt_hawd_min_fweq = cwk_tabwe->MinGfxCwk;
	smu->gfx_defauwt_soft_max_fweq = cwk_tabwe->MaxGfxCwk;
	smu->gfx_actuaw_hawd_min_fweq = 0;
	smu->gfx_actuaw_soft_max_fweq = 0;

	wetuwn 0;
}

static const stwuct pptabwe_funcs smu_v13_0_4_ppt_funcs = {
	.check_fw_status = smu_v13_0_check_fw_status,
	.check_fw_vewsion = smu_v13_0_check_fw_vewsion,
	.init_smc_tabwes = smu_v13_0_4_init_smc_tabwes,
	.fini_smc_tabwes = smu_v13_0_4_fini_smc_tabwes,
	.get_vbios_bootup_vawues = smu_v13_0_get_vbios_bootup_vawues,
	.system_featuwes_contwow = smu_v13_0_4_system_featuwes_contwow,
	.send_smc_msg_with_pawam = smu_cmn_send_smc_msg_with_pawam,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.dpm_set_vcn_enabwe = smu_v13_0_set_vcn_enabwe,
	.dpm_set_jpeg_enabwe = smu_v13_0_set_jpeg_enabwe,
	.set_defauwt_dpm_tabwe = smu_v13_0_set_defauwt_dpm_tabwes,
	.wead_sensow = smu_v13_0_4_wead_sensow,
	.is_dpm_wunning = smu_v13_0_4_is_dpm_wunning,
	.set_watewmawks_tabwe = smu_v13_0_4_set_watewmawks_tabwe,
	.get_gpu_metwics = smu_v13_0_4_get_gpu_metwics,
	.get_enabwed_mask = smu_cmn_get_enabwed_mask,
	.get_pp_featuwe_mask = smu_cmn_get_pp_featuwe_mask,
	.set_dwivew_tabwe_wocation = smu_v13_0_set_dwivew_tabwe_wocation,
	.gfx_off_contwow = smu_v13_0_gfx_off_contwow,
	.mode2_weset = smu_v13_0_4_mode2_weset,
	.get_dpm_uwtimate_fweq = smu_v13_0_4_get_dpm_uwtimate_fweq,
	.od_edit_dpm_tabwe = smu_v13_0_od_edit_dpm_tabwe,
	.pwint_cwk_wevews = smu_v13_0_4_pwint_cwk_wevews,
	.fowce_cwk_wevews = smu_v13_0_4_fowce_cwk_wevews,
	.set_pewfowmance_wevew = smu_v13_0_4_set_pewfowmance_wevew,
	.set_fine_gwain_gfx_fweq_pawametews = smu_v13_0_4_set_fine_gwain_gfx_fweq_pawametews,
	.set_gfx_powew_up_by_imu = smu_v13_0_set_gfx_powew_up_by_imu,
};

static void smu_v13_0_4_set_smu_maiwbox_wegistews(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	smu->pawam_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_82);
	smu->msg_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_66);
	smu->wesp_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_SMN_C2PMSG_90);
}

void smu_v13_0_4_set_ppt_funcs(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	smu->ppt_funcs = &smu_v13_0_4_ppt_funcs;
	smu->message_map = smu_v13_0_4_message_map;
	smu->featuwe_map = smu_v13_0_4_featuwe_mask_map;
	smu->tabwe_map = smu_v13_0_4_tabwe_map;
	smu->smc_dwivew_if_vewsion = SMU13_0_4_DWIVEW_IF_VEWSION;
	smu->is_apu = twue;

	if (amdgpu_ip_vewsion(adev, MP1_HWIP, 0) == IP_VEWSION(13, 0, 4))
		smu_v13_0_4_set_smu_maiwbox_wegistews(smu);
	ewse
		smu_v13_0_set_smu_maiwbox_wegistews(smu);
}
