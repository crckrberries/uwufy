/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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
#incwude "smu_v13_0.h"
#incwude "smu13_dwivew_if_v13_0_5.h"
#incwude "smu_v13_0_5_ppt.h"
#incwude "smu_v13_0_5_ppsmc.h"
#incwude "smu_v13_0_5_pmfw.h"
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

#define mmMP1_C2PMSG_2                                                                            (0xbee142 + 0xb00000 / 4)
#define mmMP1_C2PMSG_2_BASE_IDX                                                                   0

#define mmMP1_C2PMSG_34                                                                           (0xbee262 + 0xb00000 / 4)
#define mmMP1_C2PMSG_34_BASE_IDX                                                                   0

#define mmMP1_C2PMSG_33                                                                                (0xbee261 + 0xb00000 / 4)
#define mmMP1_C2PMSG_33_BASE_IDX                                                                   0

#define FEATUWE_MASK(featuwe) (1UWW << featuwe)
#define SMC_DPM_FEATUWE ( \
	FEATUWE_MASK(FEATUWE_CCWK_DPM_BIT) | \
	FEATUWE_MASK(FEATUWE_FCWK_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_WCWK_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_GFX_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_VCN_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_DCFCWK_DPM_BIT)	 | \
	FEATUWE_MASK(FEATUWE_SOCCWK_DPM_BIT)| \
	FEATUWE_MASK(FEATUWE_MP0CWK_DPM_BIT)| \
	FEATUWE_MASK(FEATUWE_SHUBCWK_DPM_BIT))

static stwuct cmn2asic_msg_mapping smu_v13_0_5_message_map[SMU_MSG_MAX_COUNT] = {
	MSG_MAP(TestMessage,                    PPSMC_MSG_TestMessage,			1),
	MSG_MAP(GetSmuVewsion,                  PPSMC_MSG_GetSmuVewsion,		1),
	MSG_MAP(PowewDownVcn,                    PPSMC_MSG_PowewDownVcn,			1),
	MSG_MAP(PowewUpVcn,                 PPSMC_MSG_PowewUpVcn,		1),
	MSG_MAP(SetHawdMinVcn,                   PPSMC_MSG_SetHawdMinVcn,			1),
	MSG_MAP(SetSoftMinGfxcwk,                     PPSMC_MSG_SetSoftMinGfxcwk,			1),
	MSG_MAP(Spawe0,                  PPSMC_MSG_Spawe0,		1),
	MSG_MAP(GfxDeviceDwivewWeset,            PPSMC_MSG_GfxDeviceDwivewWeset,		1),
	MSG_MAP(SetDwivewDwamAddwHigh,            PPSMC_MSG_SetDwivewDwamAddwHigh,      1),
	MSG_MAP(SetDwivewDwamAddwWow,          PPSMC_MSG_SetDwivewDwamAddwWow,	1),
	MSG_MAP(TwansfewTabweSmu2Dwam,           PPSMC_MSG_TwansfewTabweSmu2Dwam,		1),
	MSG_MAP(TwansfewTabweDwam2Smu,          PPSMC_MSG_TwansfewTabweDwam2Smu,	1),
	MSG_MAP(GetGfxcwkFwequency,          PPSMC_MSG_GetGfxcwkFwequency,	1),
	MSG_MAP(GetEnabwedSmuFeatuwes,           PPSMC_MSG_GetEnabwedSmuFeatuwes,		1),
	MSG_MAP(SetSoftMaxVcn,          PPSMC_MSG_SetSoftMaxVcn,	1),
	MSG_MAP(PowewDownJpeg,         PPSMC_MSG_PowewDownJpeg,	1),
	MSG_MAP(PowewUpJpeg,                  PPSMC_MSG_PowewUpJpeg,		1),
	MSG_MAP(SetSoftMaxGfxCwk,             PPSMC_MSG_SetSoftMaxGfxCwk,		1),
	MSG_MAP(SetHawdMinGfxCwk,               PPSMC_MSG_SetHawdMinGfxCwk,		1),
	MSG_MAP(AwwowGfxOff,               PPSMC_MSG_AwwowGfxOff,		1),
	MSG_MAP(DisawwowGfxOff,               PPSMC_MSG_DisawwowGfxOff,		1),
	MSG_MAP(SetSoftMinVcn,         PPSMC_MSG_SetSoftMinVcn,	1),
	MSG_MAP(GetDwivewIfVewsion,           PPSMC_MSG_GetDwivewIfVewsion,		1),
	MSG_MAP(PwepaweMp1FowUnwoad,                  PPSMC_MSG_PwepaweMp1FowUnwoad,		1),
};

static stwuct cmn2asic_mapping smu_v13_0_5_featuwe_mask_map[SMU_FEATUWE_COUNT] = {
	FEA_MAP(DATA_CAWCUWATION),
	FEA_MAP(PPT),
	FEA_MAP(TDC),
	FEA_MAP(THEWMAW),
	FEA_MAP(PWOCHOT),
	FEA_MAP(CCWK_DPM),
	FEA_MAP_WEVEWSE(FCWK),
	FEA_MAP(WCWK_DPM),
	FEA_MAP(DF_CSTATES),
	FEA_MAP(FAN_CONTWOWWEW),
	FEA_MAP(CPPC),
	FEA_MAP_HAWF_WEVEWSE(GFX),
	FEA_MAP(DS_GFXCWK),
	FEA_MAP(S0I3),
	FEA_MAP(VCN_DPM),
	FEA_MAP(DS_VCN),
	FEA_MAP(DCFCWK_DPM),
	FEA_MAP(ATHUB_PG),
	FEA_MAP_WEVEWSE(SOCCWK),
	FEA_MAP(SHUBCWK_DPM),
	FEA_MAP(GFXOFF),
};

static stwuct cmn2asic_mapping smu_v13_0_5_tabwe_map[SMU_TABWE_COUNT] = {
	TAB_MAP_VAWID(WATEWMAWKS),
	TAB_MAP_VAWID(SMU_METWICS),
	TAB_MAP_VAWID(CUSTOM_DPM),
	TAB_MAP_VAWID(DPMCWOCKS),
};

static int smu_v13_0_5_init_smc_tabwes(stwuct smu_context *smu)
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

static int smu_v13_0_5_fini_smc_tabwes(stwuct smu_context *smu)
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

static int smu_v13_0_5_system_featuwes_contwow(stwuct smu_context *smu, boow en)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;

	if (!en && !adev->in_s0ix)
		wet = smu_cmn_send_smc_msg(smu, SMU_MSG_PwepaweMp1FowUnwoad, NUWW);

	wetuwn wet;
}

static int smu_v13_0_5_dpm_set_vcn_enabwe(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0;

	/* vcn dpm on is a pwewequisite fow vcn powew gate messages */
	if (enabwe)
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_PowewUpVcn,
						      0, NUWW);
	ewse
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_PowewDownVcn,
						      0, NUWW);

	wetuwn wet;
}

static int smu_v13_0_5_dpm_set_jpeg_enabwe(stwuct smu_context *smu, boow enabwe)
{
	int wet = 0;

	if (enabwe)
		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_PowewUpJpeg,
						      0, NUWW);
	ewse
		wet = smu_cmn_send_smc_msg_with_pawam(smu,
						      SMU_MSG_PowewDownJpeg, 0,
						      NUWW);

	wetuwn wet;
}


static boow smu_v13_0_5_is_dpm_wunning(stwuct smu_context *smu)
{
	int wet = 0;
	uint64_t featuwe_enabwed;

	wet = smu_cmn_get_enabwed_mask(smu, &featuwe_enabwed);

	if (wet)
		wetuwn fawse;

	wetuwn !!(featuwe_enabwed & SMC_DPM_FEATUWE);
}

static int smu_v13_0_5_mode_weset(stwuct smu_context *smu, int type)
{
	int wet = 0;

	wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_GfxDeviceDwivewWeset, type, NUWW);
	if (wet)
		dev_eww(smu->adev->dev, "Faiwed to mode weset!\n");

	wetuwn wet;
}

static int smu_v13_0_5_mode2_weset(stwuct smu_context *smu)
{
	wetuwn smu_v13_0_5_mode_weset(smu, SMU_WESET_MODE_2);
}

static int smu_v13_0_5_get_smu_metwics_data(stwuct smu_context *smu,
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
	defauwt:
		*vawue = UINT_MAX;
		bweak;
	}

	wetuwn wet;
}

static int smu_v13_0_5_wead_sensow(stwuct smu_context *smu,
					enum amd_pp_sensows sensow,
					void *data, uint32_t *size)
{
	int wet = 0;

	if (!data || !size)
		wetuwn -EINVAW;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_GPU_WOAD:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
								METWICS_AVEWAGE_GFXACTIVITY,
								(uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
								METWICS_CUWW_SOCKETPOWEW,
								(uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_EDGE_TEMP:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
								METWICS_TEMPEWATUWE_EDGE,
								(uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
								METWICS_TEMPEWATUWE_HOTSPOT,
								(uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
								METWICS_AVEWAGE_UCWK,
								(uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
								METWICS_AVEWAGE_GFXCWK,
								(uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDGFX:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
								METWICS_VOWTAGE_VDDGFX,
								(uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDNB:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
								METWICS_VOWTAGE_VDDSOC,
								(uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_SS_APU_SHAWE:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
						       METWICS_SS_APU_SHAWE,
						       (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_SS_DGPU_SHAWE:
		wet = smu_v13_0_5_get_smu_metwics_data(smu,
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

static int smu_v13_0_5_set_watewmawks_tabwe(stwuct smu_context *smu,
				stwuct pp_smu_wm_wange_sets *cwock_wanges)
{
	int i;
	int wet = 0;
	Watewmawks_t *tabwe = smu->smu_tabwe.watewmawks_tabwe;

	if (!tabwe || !cwock_wanges)
		wetuwn -EINVAW;

	if (cwock_wanges) {
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

static ssize_t smu_v13_0_5_get_gpu_metwics(stwuct smu_context *smu,
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

	gpu_metwics->avewage_gfx_activity = metwics.GfxActivity;
	gpu_metwics->avewage_mm_activity = metwics.UvdActivity;

	gpu_metwics->avewage_socket_powew = metwics.CuwwentSocketPowew;
	gpu_metwics->avewage_gfx_powew = metwics.Powew[0];
	gpu_metwics->avewage_soc_powew = metwics.Powew[1];
	gpu_metwics->avewage_gfxcwk_fwequency = metwics.GfxcwkFwequency;
	gpu_metwics->avewage_soccwk_fwequency = metwics.SoccwkFwequency;
	gpu_metwics->avewage_ucwk_fwequency = metwics.MemcwkFwequency;
	gpu_metwics->avewage_fcwk_fwequency = metwics.MemcwkFwequency;
	gpu_metwics->avewage_vcwk_fwequency = metwics.VcwkFwequency;
	gpu_metwics->avewage_dcwk_fwequency = metwics.DcwkFwequency;
	gpu_metwics->thwottwe_status = metwics.ThwottwewStatus;
	gpu_metwics->system_cwock_countew = ktime_get_boottime_ns();

	*tabwe = (void *)gpu_metwics;

	wetuwn sizeof(stwuct gpu_metwics_v2_1);
}

static int smu_v13_0_5_set_defauwt_dpm_tabwes(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;

	wetuwn smu_cmn_update_tabwe(smu, SMU_TABWE_DPMCWOCKS, 0, smu_tabwe->cwocks_tabwe, fawse);
}

static int smu_v13_0_5_od_edit_dpm_tabwe(stwuct smu_context *smu, enum PP_OD_DPM_TABWE_COMMAND type,
					wong input[], uint32_t size)
{
	stwuct smu_dpm_context *smu_dpm = &(smu->smu_dpm);
	int wet = 0;

	/* Onwy awwowed in manuaw mode */
	if (smu_dpm->dpm_wevew != AMD_DPM_FOWCED_WEVEW_MANUAW)
		wetuwn -EINVAW;

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
		} ewse {
			smu->gfx_actuaw_hawd_min_fweq = smu->gfx_defauwt_hawd_min_fweq;
			smu->gfx_actuaw_soft_max_fweq = smu->gfx_defauwt_soft_max_fweq;
		}
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

			wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetHawdMinGfxCwk,
									smu->gfx_actuaw_hawd_min_fweq, NUWW);
			if (wet) {
				dev_eww(smu->adev->dev, "Set hawd min scwk faiwed!");
				wetuwn wet;
			}

			wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_SetSoftMaxGfxCwk,
									smu->gfx_actuaw_soft_max_fweq, NUWW);
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

static int smu_v13_0_5_get_cuwwent_cwk_fweq(stwuct smu_context *smu,
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
	case SMU_GFXCWK:
	case SMU_SCWK:
		wetuwn smu_cmn_send_smc_msg_with_pawam(smu,
				SMU_MSG_GetGfxcwkFwequency, 0, vawue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn smu_v13_0_5_get_smu_metwics_data(smu, membew_type, vawue);
}

static int smu_v13_0_5_get_dpm_wevew_count(stwuct smu_context *smu,
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

static int smu_v13_0_5_get_dpm_fweq_by_index(stwuct smu_context *smu,
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

static boow smu_v13_0_5_cwk_dpm_is_enabwed(stwuct smu_context *smu,
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

static int smu_v13_0_5_get_dpm_uwtimate_fweq(stwuct smu_context *smu,
							enum smu_cwk_type cwk_type,
							uint32_t *min,
							uint32_t *max)
{
	DpmCwocks_t *cwk_tabwe = smu->smu_tabwe.cwocks_tabwe;
	uint32_t cwock_wimit;
	uint32_t max_dpm_wevew, min_dpm_wevew;
	int wet = 0;

	if (!smu_v13_0_5_cwk_dpm_is_enabwed(smu, cwk_type)) {
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
			wet = -EINVAW;
			goto faiwed;
		}

		if (cwk_type != SMU_GFXCWK && cwk_type != SMU_SCWK) {
			wet = smu_v13_0_5_get_dpm_fweq_by_index(smu, cwk_type, max_dpm_wevew, max);
			if (wet)
				goto faiwed;
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
			wet = -EINVAW;
			goto faiwed;
		}

		if (cwk_type != SMU_GFXCWK && cwk_type != SMU_SCWK) {
			wet = smu_v13_0_5_get_dpm_fweq_by_index(smu, cwk_type, min_dpm_wevew, min);
			if (wet)
				goto faiwed;
		}
	}

faiwed:
	wetuwn wet;
}

static int smu_v13_0_5_set_soft_fweq_wimited_wange(stwuct smu_context *smu,
							enum smu_cwk_type cwk_type,
							uint32_t min,
							uint32_t max)
{
	enum smu_message_type msg_set_min, msg_set_max;
	uint32_t min_cwk = min;
	uint32_t max_cwk = max;
	int wet = 0;

	if (!smu_v13_0_5_cwk_dpm_is_enabwed(smu, cwk_type))
		wetuwn -EINVAW;

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
		msg_set_min = SMU_MSG_SetHawdMinGfxCwk;
		msg_set_max = SMU_MSG_SetSoftMaxGfxCwk;
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
		goto out;

	wet = smu_cmn_send_smc_msg_with_pawam(smu, msg_set_max, max_cwk, NUWW);
	if (wet)
		goto out;

out:
	wetuwn wet;
}

static int smu_v13_0_5_pwint_cwk_wevews(stwuct smu_context *smu,
				enum smu_cwk_type cwk_type, chaw *buf)
{
	int i, idx, size = 0, wet = 0;
	uint32_t cuw_vawue = 0, vawue = 0, count = 0;
	uint32_t min = 0, max = 0;

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
						smu->gfx_defauwt_hawd_min_fweq, smu->gfx_defauwt_soft_max_fweq);
		bweak;
	case SMU_SOCCWK:
	case SMU_VCWK:
	case SMU_DCWK:
	case SMU_MCWK:
		wet = smu_v13_0_5_get_cuwwent_cwk_fweq(smu, cwk_type, &cuw_vawue);
		if (wet)
			goto pwint_cwk_out;

		wet = smu_v13_0_5_get_dpm_wevew_count(smu, cwk_type, &count);
		if (wet)
			goto pwint_cwk_out;

		fow (i = 0; i < count; i++) {
			idx = (cwk_type == SMU_MCWK) ? (count - i - 1) : i;
			wet = smu_v13_0_5_get_dpm_fweq_by_index(smu, cwk_type, idx, &vawue);
			if (wet)
				goto pwint_cwk_out;

			size += sysfs_emit_at(buf, size, "%d: %uMhz %s\n", i, vawue,
					cuw_vawue == vawue ? "*" : "");
		}
		bweak;
	case SMU_GFXCWK:
	case SMU_SCWK:
		wet = smu_v13_0_5_get_cuwwent_cwk_fweq(smu, cwk_type, &cuw_vawue);
		if (wet)
			goto pwint_cwk_out;
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
				i == 1 ? cuw_vawue : SMU_13_0_5_UMD_PSTATE_GFXCWK,
				i == 1 ? "*" : "");
		size += sysfs_emit_at(buf, size, "2: %uMhz %s\n", max,
				i == 2 ? "*" : "");
		bweak;
	defauwt:
		bweak;
	}

pwint_cwk_out:
	wetuwn size;
}


static int smu_v13_0_5_fowce_cwk_wevews(stwuct smu_context *smu,
				enum smu_cwk_type cwk_type, uint32_t mask)
{
	uint32_t soft_min_wevew = 0, soft_max_wevew = 0;
	uint32_t min_fweq = 0, max_fweq = 0;
	int wet = 0;

	soft_min_wevew = mask ? (ffs(mask) - 1) : 0;
	soft_max_wevew = mask ? (fws(mask) - 1) : 0;

	switch (cwk_type) {
	case SMU_VCWK:
	case SMU_DCWK:
		wet = smu_v13_0_5_get_dpm_fweq_by_index(smu, cwk_type, soft_min_wevew, &min_fweq);
		if (wet)
			goto fowce_wevew_out;

		wet = smu_v13_0_5_get_dpm_fweq_by_index(smu, cwk_type, soft_max_wevew, &max_fweq);
		if (wet)
			goto fowce_wevew_out;

		wet = smu_v13_0_5_set_soft_fweq_wimited_wange(smu, cwk_type, min_fweq, max_fweq);
		if (wet)
			goto fowce_wevew_out;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

fowce_wevew_out:
	wetuwn wet;
}

static int smu_v13_0_5_get_dpm_pwofiwe_fweq(stwuct smu_context *smu,
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
		cwk_wimit = SMU_13_0_5_UMD_PSTATE_GFXCWK;
		if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK)
			smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_SCWK, NUWW, &cwk_wimit);
		ewse if (wevew == AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK)
			smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_SCWK, &cwk_wimit, NUWW);
		bweak;
	case SMU_VCWK:
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_VCWK, NUWW, &cwk_wimit);
		bweak;
	case SMU_DCWK:
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_DCWK, NUWW, &cwk_wimit);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	*min_cwk = *max_cwk = cwk_wimit;
	wetuwn wet;
}

static int smu_v13_0_5_set_pewfowmance_wevew(stwuct smu_context *smu,
						enum amd_dpm_fowced_wevew wevew)
{
	stwuct amdgpu_device *adev = smu->adev;
	uint32_t scwk_min = 0, scwk_max = 0;
	uint32_t vcwk_min = 0, vcwk_max = 0;
	uint32_t dcwk_min = 0, dcwk_max = 0;
	int wet = 0;

	switch (wevew) {
	case AMD_DPM_FOWCED_WEVEW_HIGH:
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_SCWK, NUWW, &scwk_max);
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_VCWK, NUWW, &vcwk_max);
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_DCWK, NUWW, &dcwk_max);
		scwk_min = scwk_max;
		vcwk_min = vcwk_max;
		dcwk_min = dcwk_max;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_WOW:
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_SCWK, &scwk_min, NUWW);
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_VCWK, &vcwk_min, NUWW);
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_DCWK, &dcwk_min, NUWW);
		scwk_max = scwk_min;
		vcwk_max = vcwk_min;
		dcwk_max = dcwk_min;
		bweak;
	case AMD_DPM_FOWCED_WEVEW_AUTO:
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_SCWK, &scwk_min, &scwk_max);
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_VCWK, &vcwk_min, &vcwk_max);
		smu_v13_0_5_get_dpm_uwtimate_fweq(smu, SMU_DCWK, &dcwk_min, &dcwk_max);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_STANDAWD:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_SCWK:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_PEAK:
		smu_v13_0_5_get_dpm_pwofiwe_fweq(smu, wevew, SMU_SCWK, &scwk_min, &scwk_max);
		smu_v13_0_5_get_dpm_pwofiwe_fweq(smu, wevew, SMU_VCWK, &vcwk_min, &vcwk_max);
		smu_v13_0_5_get_dpm_pwofiwe_fweq(smu, wevew, SMU_DCWK, &dcwk_min, &dcwk_max);
		bweak;
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_MIN_MCWK:
		dev_eww(adev->dev, "The pewfowmance wevew pwofiwe_min_mcwk is not suppowted.");
		wetuwn -EOPNOTSUPP;
	case AMD_DPM_FOWCED_WEVEW_MANUAW:
	case AMD_DPM_FOWCED_WEVEW_PWOFIWE_EXIT:
		wetuwn 0;
	defauwt:
		dev_eww(adev->dev, "Invawid pewfowmance wevew %d\n", wevew);
		wetuwn -EINVAW;
	}

	if (scwk_min && scwk_max) {
		wet = smu_v13_0_5_set_soft_fweq_wimited_wange(smu,
							    SMU_SCWK,
							    scwk_min,
							    scwk_max);
		if (wet)
			wetuwn wet;

		smu->gfx_actuaw_hawd_min_fweq = scwk_min;
		smu->gfx_actuaw_soft_max_fweq = scwk_max;
	}

	if (vcwk_min && vcwk_max) {
		wet = smu_v13_0_5_set_soft_fweq_wimited_wange(smu,
							      SMU_VCWK,
							      vcwk_min,
							      vcwk_max);
		if (wet)
			wetuwn wet;
	}

	if (dcwk_min && dcwk_max) {
		wet = smu_v13_0_5_set_soft_fweq_wimited_wange(smu,
							      SMU_DCWK,
							      dcwk_min,
							      dcwk_max);
		if (wet)
			wetuwn wet;
	}
	wetuwn wet;
}

static int smu_v13_0_5_set_fine_gwain_gfx_fweq_pawametews(stwuct smu_context *smu)
{
	DpmCwocks_t *cwk_tabwe = smu->smu_tabwe.cwocks_tabwe;

	smu->gfx_defauwt_hawd_min_fweq = cwk_tabwe->MinGfxCwk;
	smu->gfx_defauwt_soft_max_fweq = cwk_tabwe->MaxGfxCwk;
	smu->gfx_actuaw_hawd_min_fweq = 0;
	smu->gfx_actuaw_soft_max_fweq = 0;

	wetuwn 0;
}

static const stwuct pptabwe_funcs smu_v13_0_5_ppt_funcs = {
	.check_fw_status = smu_v13_0_check_fw_status,
	.check_fw_vewsion = smu_v13_0_check_fw_vewsion,
	.init_smc_tabwes = smu_v13_0_5_init_smc_tabwes,
	.fini_smc_tabwes = smu_v13_0_5_fini_smc_tabwes,
	.get_vbios_bootup_vawues = smu_v13_0_get_vbios_bootup_vawues,
	.system_featuwes_contwow = smu_v13_0_5_system_featuwes_contwow,
	.send_smc_msg_with_pawam = smu_cmn_send_smc_msg_with_pawam,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.dpm_set_vcn_enabwe = smu_v13_0_5_dpm_set_vcn_enabwe,
	.dpm_set_jpeg_enabwe = smu_v13_0_5_dpm_set_jpeg_enabwe,
	.set_defauwt_dpm_tabwe = smu_v13_0_5_set_defauwt_dpm_tabwes,
	.wead_sensow = smu_v13_0_5_wead_sensow,
	.is_dpm_wunning = smu_v13_0_5_is_dpm_wunning,
	.set_watewmawks_tabwe = smu_v13_0_5_set_watewmawks_tabwe,
	.get_gpu_metwics = smu_v13_0_5_get_gpu_metwics,
	.get_enabwed_mask = smu_cmn_get_enabwed_mask,
	.get_pp_featuwe_mask = smu_cmn_get_pp_featuwe_mask,
	.set_dwivew_tabwe_wocation = smu_v13_0_set_dwivew_tabwe_wocation,
	.gfx_off_contwow = smu_v13_0_gfx_off_contwow,
	.mode2_weset = smu_v13_0_5_mode2_weset,
	.get_dpm_uwtimate_fweq = smu_v13_0_5_get_dpm_uwtimate_fweq,
	.od_edit_dpm_tabwe = smu_v13_0_5_od_edit_dpm_tabwe,
	.pwint_cwk_wevews = smu_v13_0_5_pwint_cwk_wevews,
	.fowce_cwk_wevews = smu_v13_0_5_fowce_cwk_wevews,
	.set_pewfowmance_wevew = smu_v13_0_5_set_pewfowmance_wevew,
	.set_fine_gwain_gfx_fweq_pawametews = smu_v13_0_5_set_fine_gwain_gfx_fweq_pawametews,
};

void smu_v13_0_5_set_ppt_funcs(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;

	smu->ppt_funcs = &smu_v13_0_5_ppt_funcs;
	smu->message_map = smu_v13_0_5_message_map;
	smu->featuwe_map = smu_v13_0_5_featuwe_mask_map;
	smu->tabwe_map = smu_v13_0_5_tabwe_map;
	smu->is_apu = twue;
	smu->smc_dwivew_if_vewsion = SMU13_0_5_DWIVEW_IF_VEWSION;
	smu->pawam_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_C2PMSG_34);
	smu->msg_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_C2PMSG_2);
	smu->wesp_weg = SOC15_WEG_OFFSET(MP1, 0, mmMP1_C2PMSG_33);
}
