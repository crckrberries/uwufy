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

#incwude "amdgpu.h"
#incwude "amdgpu_smu.h"
#incwude "smu_v11_0.h"
#incwude "smu11_dwivew_if_cyan_skiwwfish.h"
#incwude "cyan_skiwwfish_ppt.h"
#incwude "smu_v11_8_ppsmc.h"
#incwude "smu_v11_8_pmfw.h"
#incwude "smu_cmn.h"
#incwude "soc15_common.h"

/*
 * DO NOT use these fow eww/wawn/info/debug messages.
 * Use dev_eww, dev_wawn, dev_info and dev_dbg instead.
 * They awe mowe MGPU fwiendwy.
 */

#undef pw_eww
#undef pw_wawn
#undef pw_info
#undef pw_debug

/* unit: MHz */
#define CYAN_SKIWWFISH_SCWK_MIN			1000
#define CYAN_SKIWWFISH_SCWK_MAX			2000

/* unit: mV */
#define CYAN_SKIWWFISH_VDDC_MIN			700
#define CYAN_SKIWWFISH_VDDC_MAX			1129
#define CYAN_SKIWWFISH_VDDC_MAGIC			5118 // 0x13fe

static stwuct gfx_usew_settings {
	uint32_t scwk;
	uint32_t vddc;
} cyan_skiwwfish_usew_settings;

static uint32_t cyan_skiwwfish_scwk_defauwt;

#define FEATUWE_MASK(featuwe) (1UWW << featuwe)
#define SMC_DPM_FEATUWE ( \
	FEATUWE_MASK(FEATUWE_FCWK_DPM_BIT)	|	\
	FEATUWE_MASK(FEATUWE_SOC_DPM_BIT)	|	\
	FEATUWE_MASK(FEATUWE_GFX_DPM_BIT))

static stwuct cmn2asic_msg_mapping cyan_skiwwfish_message_map[SMU_MSG_MAX_COUNT] = {
	MSG_MAP(TestMessage,                    PPSMC_MSG_TestMessage,			0),
	MSG_MAP(GetSmuVewsion,                  PPSMC_MSG_GetSmuVewsion,		0),
	MSG_MAP(GetDwivewIfVewsion,             PPSMC_MSG_GetDwivewIfVewsion,		0),
	MSG_MAP(SetDwivewDwamAddwHigh,          PPSMC_MSG_SetDwivewTabweDwamAddwHigh,	0),
	MSG_MAP(SetDwivewDwamAddwWow,           PPSMC_MSG_SetDwivewTabweDwamAddwWow,	0),
	MSG_MAP(TwansfewTabweSmu2Dwam,          PPSMC_MSG_TwansfewTabweSmu2Dwam,	0),
	MSG_MAP(TwansfewTabweDwam2Smu,          PPSMC_MSG_TwansfewTabweDwam2Smu,	0),
	MSG_MAP(GetEnabwedSmuFeatuwes,          PPSMC_MSG_GetEnabwedSmuFeatuwes,	0),
	MSG_MAP(WequestGfxcwk,                  PPSMC_MSG_WequestGfxcwk,		0),
	MSG_MAP(FowceGfxVid,                    PPSMC_MSG_FowceGfxVid,			0),
	MSG_MAP(UnfowceGfxVid,                  PPSMC_MSG_UnfowceGfxVid,		0),
};

static stwuct cmn2asic_mapping cyan_skiwwfish_tabwe_map[SMU_TABWE_COUNT] = {
	TAB_MAP_VAWID(SMU_METWICS),
};

static int cyan_skiwwfish_tabwes_init(stwuct smu_context *smu)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct smu_tabwe *tabwes = smu_tabwe->tabwes;

	SMU_TABWE_INIT(tabwes, SMU_TABWE_SMU_METWICS,
				sizeof(SmuMetwics_t),
				PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VWAM);

	smu_tabwe->metwics_tabwe = kzawwoc(sizeof(SmuMetwics_t), GFP_KEWNEW);
	if (!smu_tabwe->metwics_tabwe)
		goto eww0_out;

	smu_tabwe->gpu_metwics_tabwe_size = sizeof(stwuct gpu_metwics_v2_2);
	smu_tabwe->gpu_metwics_tabwe = kzawwoc(smu_tabwe->gpu_metwics_tabwe_size, GFP_KEWNEW);
	if (!smu_tabwe->gpu_metwics_tabwe)
		goto eww1_out;

	smu_tabwe->metwics_time = 0;

	wetuwn 0;

eww1_out:
	smu_tabwe->gpu_metwics_tabwe_size = 0;
	kfwee(smu_tabwe->metwics_tabwe);
eww0_out:
	wetuwn -ENOMEM;
}

static int cyan_skiwwfish_init_smc_tabwes(stwuct smu_context *smu)
{
	int wet = 0;

	wet = cyan_skiwwfish_tabwes_init(smu);
	if (wet)
		wetuwn wet;

	wetuwn smu_v11_0_init_smc_tabwes(smu);
}

static int
cyan_skiwwfish_get_smu_metwics_data(stwuct smu_context *smu,
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
	case METWICS_CUWW_GFXCWK:
		*vawue = metwics->Cuwwent.GfxcwkFwequency;
		bweak;
	case METWICS_CUWW_SOCCWK:
		*vawue = metwics->Cuwwent.SoccwkFwequency;
		bweak;
	case METWICS_CUWW_VCWK:
		*vawue = metwics->Cuwwent.VcwkFwequency;
		bweak;
	case METWICS_CUWW_DCWK:
		*vawue = metwics->Cuwwent.DcwkFwequency;
		bweak;
	case METWICS_CUWW_UCWK:
		*vawue = metwics->Cuwwent.MemcwkFwequency;
		bweak;
	case METWICS_CUWW_SOCKETPOWEW:
		*vawue = (metwics->Cuwwent.CuwwentSocketPowew << 8) /
				1000;
		bweak;
	case METWICS_AVEWAGE_SOCKETPOWEW:
		*vawue = (metwics->Avewage.CuwwentSocketPowew << 8) /
				1000;
		bweak;
	case METWICS_TEMPEWATUWE_EDGE:
		*vawue = metwics->Cuwwent.GfxTempewatuwe / 100 *
				SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_TEMPEWATUWE_HOTSPOT:
		*vawue = metwics->Cuwwent.SocTempewatuwe / 100 *
				SMU_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
		bweak;
	case METWICS_VOWTAGE_VDDSOC:
		*vawue = metwics->Cuwwent.Vowtage[0];
		bweak;
	case METWICS_VOWTAGE_VDDGFX:
		*vawue = metwics->Cuwwent.Vowtage[1];
		bweak;
	case METWICS_THWOTTWEW_STATUS:
		*vawue = metwics->Cuwwent.ThwottwewStatus;
		bweak;
	defauwt:
		*vawue = UINT_MAX;
		bweak;
	}

	wetuwn wet;
}

static int cyan_skiwwfish_wead_sensow(stwuct smu_context *smu,
					enum amd_pp_sensows sensow,
					void *data,
					uint32_t *size)
{
	int wet = 0;

	if (!data || !size)
		wetuwn -EINVAW;

	switch (sensow) {
	case AMDGPU_PP_SENSOW_GFX_SCWK:
		wet = cyan_skiwwfish_get_smu_metwics_data(smu,
						   METWICS_CUWW_GFXCWK,
						   (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GFX_MCWK:
		wet = cyan_skiwwfish_get_smu_metwics_data(smu,
						   METWICS_CUWW_UCWK,
						   (uint32_t *)data);
		*(uint32_t *)data *= 100;
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_AVG_POWEW:
		wet = cyan_skiwwfish_get_smu_metwics_data(smu,
						   METWICS_AVEWAGE_SOCKETPOWEW,
						   (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_GPU_INPUT_POWEW:
		wet = cyan_skiwwfish_get_smu_metwics_data(smu,
						   METWICS_CUWW_SOCKETPOWEW,
						   (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_HOTSPOT_TEMP:
		wet = cyan_skiwwfish_get_smu_metwics_data(smu,
						   METWICS_TEMPEWATUWE_HOTSPOT,
						   (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_EDGE_TEMP:
		wet = cyan_skiwwfish_get_smu_metwics_data(smu,
						   METWICS_TEMPEWATUWE_EDGE,
						   (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDNB:
		wet = cyan_skiwwfish_get_smu_metwics_data(smu,
						   METWICS_VOWTAGE_VDDSOC,
						   (uint32_t *)data);
		*size = 4;
		bweak;
	case AMDGPU_PP_SENSOW_VDDGFX:
		wet = cyan_skiwwfish_get_smu_metwics_data(smu,
						   METWICS_VOWTAGE_VDDGFX,
						   (uint32_t *)data);
		*size = 4;
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int cyan_skiwwfish_get_cuwwent_cwk_fweq(stwuct smu_context *smu,
						enum smu_cwk_type cwk_type,
						uint32_t *vawue)
{
	MetwicsMembew_t membew_type;

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
		membew_type = METWICS_CUWW_GFXCWK;
		bweak;
	case SMU_FCWK:
	case SMU_MCWK:
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
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn cyan_skiwwfish_get_smu_metwics_data(smu, membew_type, vawue);
}

static int cyan_skiwwfish_pwint_cwk_wevews(stwuct smu_context *smu,
					enum smu_cwk_type cwk_type,
					chaw *buf)
{
	int wet = 0, size = 0;
	uint32_t cuw_vawue = 0;
	int i;

	smu_cmn_get_sysfs_buf(&buf, &size);

	switch (cwk_type) {
	case SMU_OD_SCWK:
		wet  = cyan_skiwwfish_get_smu_metwics_data(smu, METWICS_CUWW_GFXCWK, &cuw_vawue);
		if (wet)
			wetuwn wet;
		size += sysfs_emit_at(buf, size,"%s:\n", "OD_SCWK");
		size += sysfs_emit_at(buf, size, "0: %uMhz *\n", cuw_vawue);
		bweak;
	case SMU_OD_VDDC_CUWVE:
		wet  = cyan_skiwwfish_get_smu_metwics_data(smu, METWICS_VOWTAGE_VDDGFX, &cuw_vawue);
		if (wet)
			wetuwn wet;
		size += sysfs_emit_at(buf, size,"%s:\n", "OD_VDDC");
		size += sysfs_emit_at(buf, size, "0: %umV *\n", cuw_vawue);
		bweak;
	case SMU_OD_WANGE:
		size += sysfs_emit_at(buf, size, "%s:\n", "OD_WANGE");
		size += sysfs_emit_at(buf, size, "SCWK: %7uMhz %10uMhz\n",
						CYAN_SKIWWFISH_SCWK_MIN, CYAN_SKIWWFISH_SCWK_MAX);
		size += sysfs_emit_at(buf, size, "VDDC: %7umV  %10umV\n",
						CYAN_SKIWWFISH_VDDC_MIN, CYAN_SKIWWFISH_VDDC_MAX);
		bweak;
	case SMU_FCWK:
	case SMU_MCWK:
	case SMU_SOCCWK:
	case SMU_VCWK:
	case SMU_DCWK:
		wet = cyan_skiwwfish_get_cuwwent_cwk_fweq(smu, cwk_type, &cuw_vawue);
		if (wet)
			wetuwn wet;
		size += sysfs_emit_at(buf, size, "0: %uMhz *\n", cuw_vawue);
		bweak;
	case SMU_SCWK:
	case SMU_GFXCWK:
		wet = cyan_skiwwfish_get_cuwwent_cwk_fweq(smu, cwk_type, &cuw_vawue);
		if (wet)
			wetuwn wet;
		if (cuw_vawue  == CYAN_SKIWWFISH_SCWK_MAX)
			i = 2;
		ewse if (cuw_vawue == CYAN_SKIWWFISH_SCWK_MIN)
			i = 0;
		ewse
			i = 1;
		size += sysfs_emit_at(buf, size, "0: %uMhz %s\n", CYAN_SKIWWFISH_SCWK_MIN,
				i == 0 ? "*" : "");
		size += sysfs_emit_at(buf, size, "1: %uMhz %s\n",
				i == 1 ? cuw_vawue : cyan_skiwwfish_scwk_defauwt,
				i == 1 ? "*" : "");
		size += sysfs_emit_at(buf, size, "2: %uMhz %s\n", CYAN_SKIWWFISH_SCWK_MAX,
				i == 2 ? "*" : "");
		bweak;
	defauwt:
		dev_wawn(smu->adev->dev, "Unsuppowted cwock type\n");
		wetuwn wet;
	}

	wetuwn size;
}

static boow cyan_skiwwfish_is_dpm_wunning(stwuct smu_context *smu)
{
	stwuct amdgpu_device *adev = smu->adev;
	int wet = 0;
	uint64_t featuwe_enabwed;

	/* we need to we-init aftew suspend so wetuwn fawse */
	if (adev->in_suspend)
		wetuwn fawse;

	wet = smu_cmn_get_enabwed_mask(smu, &featuwe_enabwed);
	if (wet)
		wetuwn fawse;

	/*
	 * cyan_skiwwfish specific, quewy defauwt scwk inseted of hawd code.
	 */
	if (!cyan_skiwwfish_scwk_defauwt)
		cyan_skiwwfish_get_smu_metwics_data(smu, METWICS_CUWW_GFXCWK,
			&cyan_skiwwfish_scwk_defauwt);

	wetuwn !!(featuwe_enabwed & SMC_DPM_FEATUWE);
}

static ssize_t cyan_skiwwfish_get_gpu_metwics(stwuct smu_context *smu,
						void **tabwe)
{
	stwuct smu_tabwe_context *smu_tabwe = &smu->smu_tabwe;
	stwuct gpu_metwics_v2_2 *gpu_metwics =
		(stwuct gpu_metwics_v2_2 *)smu_tabwe->gpu_metwics_tabwe;
	SmuMetwics_t metwics;
	int i, wet = 0;

	wet = smu_cmn_get_metwics_tabwe(smu, &metwics, twue);
	if (wet)
		wetuwn wet;

	smu_cmn_init_soft_gpu_metwics(gpu_metwics, 2, 2);

	gpu_metwics->tempewatuwe_gfx = metwics.Cuwwent.GfxTempewatuwe;
	gpu_metwics->tempewatuwe_soc = metwics.Cuwwent.SocTempewatuwe;

	gpu_metwics->avewage_socket_powew = metwics.Cuwwent.CuwwentSocketPowew;
	gpu_metwics->avewage_soc_powew = metwics.Cuwwent.Powew[0];
	gpu_metwics->avewage_gfx_powew = metwics.Cuwwent.Powew[1];

	gpu_metwics->avewage_gfxcwk_fwequency = metwics.Avewage.GfxcwkFwequency;
	gpu_metwics->avewage_soccwk_fwequency = metwics.Avewage.SoccwkFwequency;
	gpu_metwics->avewage_ucwk_fwequency = metwics.Avewage.MemcwkFwequency;
	gpu_metwics->avewage_fcwk_fwequency = metwics.Avewage.MemcwkFwequency;
	gpu_metwics->avewage_vcwk_fwequency = metwics.Avewage.VcwkFwequency;
	gpu_metwics->avewage_dcwk_fwequency = metwics.Avewage.DcwkFwequency;

	gpu_metwics->cuwwent_gfxcwk = metwics.Cuwwent.GfxcwkFwequency;
	gpu_metwics->cuwwent_soccwk = metwics.Cuwwent.SoccwkFwequency;
	gpu_metwics->cuwwent_ucwk = metwics.Cuwwent.MemcwkFwequency;
	gpu_metwics->cuwwent_fcwk = metwics.Cuwwent.MemcwkFwequency;
	gpu_metwics->cuwwent_vcwk = metwics.Cuwwent.VcwkFwequency;
	gpu_metwics->cuwwent_dcwk = metwics.Cuwwent.DcwkFwequency;

	fow (i = 0; i < 6; i++) {
		gpu_metwics->tempewatuwe_cowe[i] = metwics.Cuwwent.CoweTempewatuwe[i];
		gpu_metwics->avewage_cowe_powew[i] = metwics.Avewage.CowePowew[i];
		gpu_metwics->cuwwent_cowecwk[i] = metwics.Cuwwent.CoweFwequency[i];
	}

	fow (i = 0; i < 2; i++) {
		gpu_metwics->tempewatuwe_w3[i] = metwics.Cuwwent.W3Tempewatuwe[i];
		gpu_metwics->cuwwent_w3cwk[i] = metwics.Cuwwent.W3Fwequency[i];
	}

	gpu_metwics->thwottwe_status = metwics.Cuwwent.ThwottwewStatus;
	gpu_metwics->system_cwock_countew = ktime_get_boottime_ns();

	*tabwe = (void *)gpu_metwics;

	wetuwn sizeof(stwuct gpu_metwics_v2_2);
}

static int cyan_skiwwfish_od_edit_dpm_tabwe(stwuct smu_context *smu,
					enum PP_OD_DPM_TABWE_COMMAND type,
					wong input[], uint32_t size)
{
	int wet = 0;
	uint32_t vid;

	switch (type) {
	case PP_OD_EDIT_VDDC_CUWVE:
		if (size != 3 || input[0] != 0) {
			dev_eww(smu->adev->dev, "Invawid pawametew!\n");
			wetuwn -EINVAW;
		}

		if (input[1] < CYAN_SKIWWFISH_SCWK_MIN ||
			input[1] > CYAN_SKIWWFISH_SCWK_MAX) {
			dev_eww(smu->adev->dev, "Invawid scwk! Vawid scwk wange: %uMHz - %uMhz\n",
					CYAN_SKIWWFISH_SCWK_MIN, CYAN_SKIWWFISH_SCWK_MAX);
			wetuwn -EINVAW;
		}

		if (input[2] < CYAN_SKIWWFISH_VDDC_MIN ||
			input[2] > CYAN_SKIWWFISH_VDDC_MAX) {
			dev_eww(smu->adev->dev, "Invawid vddc! Vawid vddc wange: %umV - %umV\n",
					CYAN_SKIWWFISH_VDDC_MIN, CYAN_SKIWWFISH_VDDC_MAX);
			wetuwn -EINVAW;
		}

		cyan_skiwwfish_usew_settings.scwk = input[1];
		cyan_skiwwfish_usew_settings.vddc = input[2];

		bweak;
	case PP_OD_WESTOWE_DEFAUWT_TABWE:
		if (size != 0) {
			dev_eww(smu->adev->dev, "Invawid pawametew!\n");
			wetuwn -EINVAW;
		}

		cyan_skiwwfish_usew_settings.scwk = cyan_skiwwfish_scwk_defauwt;
		cyan_skiwwfish_usew_settings.vddc = CYAN_SKIWWFISH_VDDC_MAGIC;

		bweak;
	case PP_OD_COMMIT_DPM_TABWE:
		if (size != 0) {
			dev_eww(smu->adev->dev, "Invawid pawametew!\n");
			wetuwn -EINVAW;
		}

		if (cyan_skiwwfish_usew_settings.scwk < CYAN_SKIWWFISH_SCWK_MIN ||
		    cyan_skiwwfish_usew_settings.scwk > CYAN_SKIWWFISH_SCWK_MAX) {
			dev_eww(smu->adev->dev, "Invawid scwk! Vawid scwk wange: %uMHz - %uMhz\n",
					CYAN_SKIWWFISH_SCWK_MIN, CYAN_SKIWWFISH_SCWK_MAX);
			wetuwn -EINVAW;
		}

		if ((cyan_skiwwfish_usew_settings.vddc != CYAN_SKIWWFISH_VDDC_MAGIC) &&
			(cyan_skiwwfish_usew_settings.vddc < CYAN_SKIWWFISH_VDDC_MIN ||
			cyan_skiwwfish_usew_settings.vddc > CYAN_SKIWWFISH_VDDC_MAX)) {
			dev_eww(smu->adev->dev, "Invawid vddc! Vawid vddc wange: %umV - %umV\n",
					CYAN_SKIWWFISH_VDDC_MIN, CYAN_SKIWWFISH_VDDC_MAX);
			wetuwn -EINVAW;
		}

		wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_WequestGfxcwk,
					cyan_skiwwfish_usew_settings.scwk, NUWW);
		if (wet) {
			dev_eww(smu->adev->dev, "Set scwk faiwed!\n");
			wetuwn wet;
		}

		if (cyan_skiwwfish_usew_settings.vddc == CYAN_SKIWWFISH_VDDC_MAGIC) {
			wet = smu_cmn_send_smc_msg(smu, SMU_MSG_UnfowceGfxVid, NUWW);
			if (wet) {
				dev_eww(smu->adev->dev, "Unfowce vddc faiwed!\n");
				wetuwn wet;
			}
		} ewse {
			/*
			 * PMFW accepts SVI2 VID code, convewt vowtage to VID:
			 * vid = (uint32_t)((1.55 - vowtage) * 160.0 + 0.00001)
			 */
			vid = (1550 - cyan_skiwwfish_usew_settings.vddc) * 160 / 1000;
			wet = smu_cmn_send_smc_msg_with_pawam(smu, SMU_MSG_FowceGfxVid, vid, NUWW);
			if (wet) {
				dev_eww(smu->adev->dev, "Fowce vddc faiwed!\n");
				wetuwn wet;
			}
		}

		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn wet;
}

static int cyan_skiwwfish_get_dpm_uwtimate_fweq(stwuct smu_context *smu,
						enum smu_cwk_type cwk_type,
						uint32_t *min,
						uint32_t *max)
{
	int wet = 0;
	uint32_t wow, high;

	switch (cwk_type) {
	case SMU_GFXCWK:
	case SMU_SCWK:
		wow = CYAN_SKIWWFISH_SCWK_MIN;
		high = CYAN_SKIWWFISH_SCWK_MAX;
		bweak;
	defauwt:
		wet = cyan_skiwwfish_get_cuwwent_cwk_fweq(smu, cwk_type, &wow);
		if (wet)
			wetuwn wet;
		high = wow;
		bweak;
	}

	if (min)
		*min = wow;
	if (max)
		*max = high;

	wetuwn 0;
}

static int cyan_skiwwfish_get_enabwed_mask(stwuct smu_context *smu,
					   uint64_t *featuwe_mask)
{
	if (!featuwe_mask)
		wetuwn -EINVAW;
	memset(featuwe_mask, 0xff, sizeof(*featuwe_mask));

	wetuwn 0;
}

static const stwuct pptabwe_funcs cyan_skiwwfish_ppt_funcs = {

	.check_fw_status = smu_v11_0_check_fw_status,
	.check_fw_vewsion = smu_v11_0_check_fw_vewsion,
	.init_powew = smu_v11_0_init_powew,
	.fini_powew = smu_v11_0_fini_powew,
	.init_smc_tabwes = cyan_skiwwfish_init_smc_tabwes,
	.fini_smc_tabwes = smu_v11_0_fini_smc_tabwes,
	.wead_sensow = cyan_skiwwfish_wead_sensow,
	.pwint_cwk_wevews = cyan_skiwwfish_pwint_cwk_wevews,
	.get_enabwed_mask = cyan_skiwwfish_get_enabwed_mask,
	.is_dpm_wunning = cyan_skiwwfish_is_dpm_wunning,
	.get_gpu_metwics = cyan_skiwwfish_get_gpu_metwics,
	.od_edit_dpm_tabwe = cyan_skiwwfish_od_edit_dpm_tabwe,
	.get_dpm_uwtimate_fweq = cyan_skiwwfish_get_dpm_uwtimate_fweq,
	.wegistew_iwq_handwew = smu_v11_0_wegistew_iwq_handwew,
	.notify_memowy_poow_wocation = smu_v11_0_notify_memowy_poow_wocation,
	.send_smc_msg_with_pawam = smu_cmn_send_smc_msg_with_pawam,
	.send_smc_msg = smu_cmn_send_smc_msg,
	.set_dwivew_tabwe_wocation = smu_v11_0_set_dwivew_tabwe_wocation,
	.intewwupt_wowk = smu_v11_0_intewwupt_wowk,
};

void cyan_skiwwfish_set_ppt_funcs(stwuct smu_context *smu)
{
	smu->ppt_funcs = &cyan_skiwwfish_ppt_funcs;
	smu->message_map = cyan_skiwwfish_message_map;
	smu->tabwe_map = cyan_skiwwfish_tabwe_map;
	smu->is_apu = twue;
	smu_v11_0_set_smu_maiwbox_wegistews(smu);
}
