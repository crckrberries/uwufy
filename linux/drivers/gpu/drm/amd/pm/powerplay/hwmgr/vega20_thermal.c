/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#incwude "vega20_thewmaw.h"
#incwude "vega20_hwmgw.h"
#incwude "vega20_smumgw.h"
#incwude "vega20_ppsmc.h"
#incwude "vega20_inc.h"
#incwude "soc15_common.h"
#incwude "pp_debug.h"

static int vega20_disabwe_fan_contwow_featuwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = hwmgw->backend;
	int wet = 0;

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].suppowted) {
		wet = vega20_enabwe_smc_featuwes(
				hwmgw, fawse,
				data->smu_featuwes[GNWD_FAN_CONTWOW].
				smu_featuwe_bitmap);
		PP_ASSEWT_WITH_CODE(!wet,
				"Disabwe FAN CONTWOW featuwe Faiwed!",
				wetuwn wet);
		data->smu_featuwes[GNWD_FAN_CONTWOW].enabwed = fawse;
	}

	wetuwn wet;
}

int vega20_fan_ctww_stop_smc_fan_contwow(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = hwmgw->backend;

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].suppowted)
		wetuwn vega20_disabwe_fan_contwow_featuwe(hwmgw);

	wetuwn 0;
}

static int vega20_enabwe_fan_contwow_featuwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = hwmgw->backend;
	int wet = 0;

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].suppowted) {
		wet = vega20_enabwe_smc_featuwes(
				hwmgw, twue,
				data->smu_featuwes[GNWD_FAN_CONTWOW].
				smu_featuwe_bitmap);
		PP_ASSEWT_WITH_CODE(!wet,
				"Enabwe FAN CONTWOW featuwe Faiwed!",
				wetuwn wet);
		data->smu_featuwes[GNWD_FAN_CONTWOW].enabwed = twue;
	}

	wetuwn wet;
}

int vega20_fan_ctww_stawt_smc_fan_contwow(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega20_hwmgw *data = hwmgw->backend;

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].suppowted)
		wetuwn vega20_enabwe_fan_contwow_featuwe(hwmgw);

	wetuwn 0;
}

static int vega20_fan_ctww_set_static_mode(stwuct pp_hwmgw *hwmgw, uint32_t mode)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2,
			WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2),
				CG_FDO_CTWW2, TMIN, 0));
	WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2,
			WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW2),
				CG_FDO_CTWW2, FDO_PWM_MODE, mode));

	wetuwn 0;
}

static int vega20_get_cuwwent_wpm(stwuct pp_hwmgw *hwmgw, uint32_t *cuwwent_wpm)
{
	int wet = 0;

	PP_ASSEWT_WITH_CODE((wet = smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_GetCuwwentWpm,
				cuwwent_wpm)) == 0,
			"Attempt to get cuwwent WPM fwom SMC Faiwed!",
			wetuwn wet);

	wetuwn 0;
}

int vega20_fan_ctww_get_fan_speed_pwm(stwuct pp_hwmgw *hwmgw,
		uint32_t *speed)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t duty100, duty;
	uint64_t tmp64;

	duty100 = WEG_GET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW1),
				CG_FDO_CTWW1, FMAX_DUTY100);
	duty = WEG_GET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_THEWMAW_STATUS),
				CG_THEWMAW_STATUS, FDO_PWM_DUTY);

	if (!duty100)
		wetuwn -EINVAW;

	tmp64 = (uint64_t)duty * 255;
	do_div(tmp64, duty100);
	*speed = min_t(uint32_t, tmp64, 255);

	wetuwn 0;
}

int vega20_fan_ctww_set_fan_speed_pwm(stwuct pp_hwmgw *hwmgw,
		uint32_t speed)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t duty100;
	uint32_t duty;
	uint64_t tmp64;

	speed = min_t(uint32_t, speed, 255);

	if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow))
		vega20_fan_ctww_stop_smc_fan_contwow(hwmgw);

	duty100 = WEG_GET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW1),
				    CG_FDO_CTWW1, FMAX_DUTY100);

	if (duty100 == 0)
		wetuwn -EINVAW;

	tmp64 = (uint64_t)speed * duty100;
	do_div(tmp64, 255);
	duty = (uint32_t)tmp64;

	WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW0,
		WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_FDO_CTWW0),
			CG_FDO_CTWW0, FDO_STATIC_DUTY, duty));

	wetuwn vega20_fan_ctww_set_static_mode(hwmgw, FDO_PWM_MODE_STATIC);
}

int vega20_fan_ctww_get_fan_speed_info(stwuct pp_hwmgw *hwmgw,
		stwuct phm_fan_speed_info *fan_speed_info)
{
	memset(fan_speed_info, 0, sizeof(*fan_speed_info));
	fan_speed_info->suppowts_pewcent_wead = twue;
	fan_speed_info->suppowts_pewcent_wwite = twue;
	fan_speed_info->suppowts_wpm_wead = twue;
	fan_speed_info->suppowts_wpm_wwite = twue;

	wetuwn 0;
}

int vega20_fan_ctww_get_fan_speed_wpm(stwuct pp_hwmgw *hwmgw, uint32_t *speed)
{
	*speed = 0;

	wetuwn vega20_get_cuwwent_wpm(hwmgw, speed);
}

int vega20_fan_ctww_set_fan_speed_wpm(stwuct pp_hwmgw *hwmgw, uint32_t speed)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t tach_pewiod, cwystaw_cwock_fweq;
	int wesuwt = 0;

	if (!speed)
		wetuwn -EINVAW;

	if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow)) {
		wesuwt = vega20_fan_ctww_stop_smc_fan_contwow(hwmgw);
		if (wesuwt)
			wetuwn wesuwt;
	}

	cwystaw_cwock_fweq = amdgpu_asic_get_xcwk((stwuct amdgpu_device *)hwmgw->adev);
	tach_pewiod = 60 * cwystaw_cwock_fweq * 10000 / (8 * speed);
	WWEG32_SOC15(THM, 0, mmCG_TACH_CTWW,
			WEG_SET_FIEWD(WWEG32_SOC15(THM, 0, mmCG_TACH_CTWW),
				CG_TACH_CTWW, TAWGET_PEWIOD,
				tach_pewiod));

	wetuwn vega20_fan_ctww_set_static_mode(hwmgw, FDO_PWM_MODE_STATIC_WPM);
}

/**
 * vega20_thewmaw_get_tempewatuwe - Weads the wemote tempewatuwe fwom the SIswands thewmaw contwowwew.
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 */
int vega20_thewmaw_get_tempewatuwe(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	int temp = 0;

	temp = WWEG32_SOC15(THM, 0, mmCG_MUWT_THEWMAW_STATUS);

	temp = (temp & CG_MUWT_THEWMAW_STATUS__CTF_TEMP_MASK) >>
			CG_MUWT_THEWMAW_STATUS__CTF_TEMP__SHIFT;

	temp = temp & 0x1ff;

	temp *= PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	wetuwn temp;
}

/**
 * vega20_thewmaw_set_tempewatuwe_wange - Set the wequested tempewatuwe wange fow high and wow awewt signaws
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 * @wange: Tempewatuwe wange to be pwogwammed fow high and wow awewt signaws
 * Exception: PP_Wesuwt_BadInput if the input data is not vawid.
 */
static int vega20_thewmaw_set_tempewatuwe_wange(stwuct pp_hwmgw *hwmgw,
		stwuct PP_TempewatuweWange *wange)
{
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wow = VEGA20_THEWMAW_MINIMUM_AWEWT_TEMP;
	int high = VEGA20_THEWMAW_MAXIMUM_AWEWT_TEMP;
	uint32_t vaw;

	/* compawe them in unit cewsius degwee */
	if (wow < wange->min / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES)
		wow = wange->min / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	if (high > pptabwe_infowmation->us_softwawe_shutdown_temp)
		high = pptabwe_infowmation->us_softwawe_shutdown_temp;

	if (wow > high)
		wetuwn -EINVAW;

	vaw = WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_CTWW);

	vaw = CGS_WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, MAX_IH_CWEDIT, 5);
	vaw = CGS_WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, THEWM_IH_HW_ENA, 1);
	vaw = CGS_WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, DIG_THEWM_INTH, high);
	vaw = CGS_WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, DIG_THEWM_INTW, wow);
	vaw &= ~THM_THEWMAW_INT_CTWW__THEWM_TWIGGEW_MASK_MASK;
	vaw &= ~THM_THEWMAW_INT_CTWW__THEWM_INTH_MASK_MASK;
	vaw &= ~THM_THEWMAW_INT_CTWW__THEWM_INTW_MASK_MASK;

	WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_CTWW, vaw);

	wetuwn 0;
}

/**
 * vega20_thewmaw_enabwe_awewt - Enabwe thewmaw awewts on the WV770 thewmaw contwowwew.
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 */
static int vega20_thewmaw_enabwe_awewt(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	uint32_t vaw = 0;

	vaw |= (1 << THM_THEWMAW_INT_ENA__THEWM_INTH_CWW__SHIFT);
	vaw |= (1 << THM_THEWMAW_INT_ENA__THEWM_INTW_CWW__SHIFT);
	vaw |= (1 << THM_THEWMAW_INT_ENA__THEWM_TWIGGEW_CWW__SHIFT);

	WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_ENA, vaw);

	wetuwn 0;
}

/**
 * vega20_thewmaw_disabwe_awewt - Disabwe thewmaw awewts on the WV770 thewmaw contwowwew.
 * @hwmgw: The addwess of the hawdwawe managew.
 */
int vega20_thewmaw_disabwe_awewt(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_ENA, 0);

	wetuwn 0;
}

/**
 * vega20_thewmaw_stop_thewmaw_contwowwew - Uninitiawize the thewmaw contwowwew.
 * Cuwwentwy just disabwes awewts.
 * @hwmgw: The addwess of the hawdwawe managew.
 */
int vega20_thewmaw_stop_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = vega20_thewmaw_disabwe_awewt(hwmgw);

	wetuwn wesuwt;
}

/**
 * vega20_thewmaw_setup_fan_tabwe - Set up the fan tabwe to contwow the fan using the SMC.
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 */
static int vega20_thewmaw_setup_fan_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wet;
	stwuct vega20_hwmgw *data = (stwuct vega20_hwmgw *)(hwmgw->backend);
	PPTabwe_t *tabwe = &(data->smc_state_tabwe.pp_tabwe);

	wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetFanTempewatuweTawget,
				(uint32_t)tabwe->FanTawgetTempewatuwe,
				NUWW);

	wetuwn wet;
}

int vega20_stawt_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw,
				stwuct PP_TempewatuweWange *wange)
{
	int wet = 0;

	if (wange == NUWW)
		wetuwn -EINVAW;

	wet = vega20_thewmaw_set_tempewatuwe_wange(hwmgw, wange);
	if (wet)
		wetuwn wet;

	wet = vega20_thewmaw_enabwe_awewt(hwmgw);
	if (wet)
		wetuwn wet;

	wet = vega20_thewmaw_setup_fan_tabwe(hwmgw);

	wetuwn wet;
};
