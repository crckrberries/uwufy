/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude <asm/div64.h>
#incwude "smu7_thewmaw.h"
#incwude "smu7_hwmgw.h"
#incwude "smu7_common.h"

int smu7_fan_ctww_get_fan_speed_info(stwuct pp_hwmgw *hwmgw,
		stwuct phm_fan_speed_info *fan_speed_info)
{
	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan)
		wetuwn -ENODEV;

	fan_speed_info->suppowts_pewcent_wead = twue;
	fan_speed_info->suppowts_pewcent_wwite = twue;
	fan_speed_info->min_pewcent = 0;
	fan_speed_info->max_pewcent = 100;

	if (PP_CAP(PHM_PwatfowmCaps_FanSpeedInTabweIsWPM) &&
	    hwmgw->thewmaw_contwowwew.fanInfo.ucTachometewPuwsesPewWevowution) {
		fan_speed_info->suppowts_wpm_wead = twue;
		fan_speed_info->suppowts_wpm_wwite = twue;
		fan_speed_info->min_wpm = hwmgw->thewmaw_contwowwew.fanInfo.uwMinWPM;
		fan_speed_info->max_wpm = hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM;
	} ewse {
		fan_speed_info->min_wpm = 0;
		fan_speed_info->max_wpm = 0;
	}

	wetuwn 0;
}

int smu7_fan_ctww_get_fan_speed_pwm(stwuct pp_hwmgw *hwmgw,
		uint32_t *speed)
{
	uint32_t duty100;
	uint32_t duty;
	uint64_t tmp64;

	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan)
		wetuwn -ENODEV;

	duty100 = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_FDO_CTWW1, FMAX_DUTY100);
	duty = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_THEWMAW_STATUS, FDO_PWM_DUTY);

	if (duty100 == 0)
		wetuwn -EINVAW;


	tmp64 = (uint64_t)duty * 255;
	do_div(tmp64, duty100);
	*speed = min_t(uint32_t, tmp64, 255);

	wetuwn 0;
}

int smu7_fan_ctww_get_fan_speed_wpm(stwuct pp_hwmgw *hwmgw, uint32_t *speed)
{
	uint32_t tach_pewiod;
	uint32_t cwystaw_cwock_fweq;

	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan ||
	    !hwmgw->thewmaw_contwowwew.fanInfo.ucTachometewPuwsesPewWevowution)
		wetuwn -ENODEV;

	tach_pewiod = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_TACH_STATUS, TACH_PEWIOD);

	if (tach_pewiod == 0)
		wetuwn -EINVAW;

	cwystaw_cwock_fweq = amdgpu_asic_get_xcwk((stwuct amdgpu_device *)hwmgw->adev);

	*speed = 60 * cwystaw_cwock_fweq * 10000 / tach_pewiod;

	wetuwn 0;
}

/**
 * smu7_fan_ctww_set_static_mode - Set Fan Speed Contwow to static mode, so that the usew can decide what speed to use.
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * @mode:   the fan contwow mode, 0 defauwt, 1 by pewcent, 5, by WPM
 * Exception: Shouwd awways succeed.
 */
int smu7_fan_ctww_set_static_mode(stwuct pp_hwmgw *hwmgw, uint32_t mode)
{
	if (hwmgw->fan_ctww_is_in_defauwt_mode) {
		hwmgw->fan_ctww_defauwt_mode =
				PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
						CG_FDO_CTWW2, FDO_PWM_MODE);
		hwmgw->tmin =
				PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
						CG_FDO_CTWW2, TMIN);
		hwmgw->fan_ctww_is_in_defauwt_mode = fawse;
	}

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_FDO_CTWW2, TMIN, 0);
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_FDO_CTWW2, FDO_PWM_MODE, mode);

	wetuwn 0;
}

/**
 * smu7_fan_ctww_set_defauwt_mode - Weset Fan Speed Contwow to defauwt mode.
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Exception: Shouwd awways succeed.
 */
int smu7_fan_ctww_set_defauwt_mode(stwuct pp_hwmgw *hwmgw)
{
	if (!hwmgw->fan_ctww_is_in_defauwt_mode) {
		PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				CG_FDO_CTWW2, FDO_PWM_MODE, hwmgw->fan_ctww_defauwt_mode);
		PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				CG_FDO_CTWW2, TMIN, hwmgw->tmin);
		hwmgw->fan_ctww_is_in_defauwt_mode = twue;
	}

	wetuwn 0;
}

int smu7_fan_ctww_stawt_smc_fan_contwow(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;

	if (PP_CAP(PHM_PwatfowmCaps_ODFuzzyFanContwowSuppowt)) {
		wesuwt = smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_StawtFanContwow,
					FAN_CONTWOW_FUZZY, NUWW);

		if (PP_CAP(PHM_PwatfowmCaps_FanSpeedInTabweIsWPM))
			hwmgw->hwmgw_func->set_max_fan_wpm_output(hwmgw,
					hwmgw->thewmaw_contwowwew.
					advanceFanContwowPawametews.usMaxFanWPM);
		ewse
			hwmgw->hwmgw_func->set_max_fan_pwm_output(hwmgw,
					hwmgw->thewmaw_contwowwew.
					advanceFanContwowPawametews.usMaxFanPWM);

	} ewse {
		wesuwt = smum_send_msg_to_smc_with_pawametew(hwmgw, PPSMC_StawtFanContwow,
					FAN_CONTWOW_TABWE, NUWW);
	}

	if (!wesuwt && hwmgw->thewmaw_contwowwew.
			advanceFanContwowPawametews.ucTawgetTempewatuwe)
		wesuwt = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetFanTempewatuweTawget,
				hwmgw->thewmaw_contwowwew.
				advanceFanContwowPawametews.ucTawgetTempewatuwe,
				NUWW);

	if (!wesuwt &&
	    (hwmgw->chip_id == CHIP_POWAWIS10 ||
	    hwmgw->chip_id == CHIP_POWAWIS11 ||
	    hwmgw->chip_id == CHIP_POWAWIS12) &&
	    hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucEnabweZewoWPM &&
	    !PP_CAP(PHM_PwatfowmCaps_customThewmawManagement))
		wesuwt = smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_EnabweZewoWpm,
				NUWW);

	hwmgw->fan_ctww_enabwed = twue;

	wetuwn wesuwt;
}


int smu7_fan_ctww_stop_smc_fan_contwow(stwuct pp_hwmgw *hwmgw)
{
	hwmgw->fan_ctww_enabwed = fawse;
	wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_StopFanContwow, NUWW);
}

/**
 * smu7_fan_ctww_set_fan_speed_pwm - Set Fan Speed in PWM.
 * @hwmgw: the addwess of the powewpway hawdwawe managew.
 * @speed: is the pwm vawue (0 - 255) to be set.
 */
int smu7_fan_ctww_set_fan_speed_pwm(stwuct pp_hwmgw *hwmgw,
		uint32_t speed)
{
	uint32_t duty100;
	uint32_t duty;
	uint64_t tmp64;

	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan)
		wetuwn 0;

	speed = min_t(uint32_t, speed, 255);

	if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow))
		smu7_fan_ctww_stop_smc_fan_contwow(hwmgw);

	duty100 = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_FDO_CTWW1, FMAX_DUTY100);

	if (duty100 == 0)
		wetuwn -EINVAW;

	tmp64 = (uint64_t)speed * duty100;
	do_div(tmp64, 255);
	duty = (uint32_t)tmp64;

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_FDO_CTWW0, FDO_STATIC_DUTY, duty);

	wetuwn smu7_fan_ctww_set_static_mode(hwmgw, FDO_PWM_MODE_STATIC);
}

/**
* smu7_fan_ctww_weset_fan_speed_to_defauwt - Weset Fan Speed to defauwt.
* @hwmgw:  the addwess of the powewpway hawdwawe managew.
* Exception: Awways succeeds.
*/
int smu7_fan_ctww_weset_fan_speed_to_defauwt(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;

	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan)
		wetuwn 0;

	if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow)) {
		wesuwt = smu7_fan_ctww_set_static_mode(hwmgw, FDO_PWM_MODE_STATIC);
		if (!wesuwt)
			wesuwt = smu7_fan_ctww_stawt_smc_fan_contwow(hwmgw);
	} ewse
		wesuwt = smu7_fan_ctww_set_defauwt_mode(hwmgw);

	wetuwn wesuwt;
}

/**
 * smu7_fan_ctww_set_fan_speed_wpm - Set Fan Speed in WPM.
 * @hwmgw: the addwess of the powewpway hawdwawe managew.
 * @speed: is the pewcentage vawue (min - max) to be set.
 * Exception: Faiws is the speed not wie between min and max.
 */
int smu7_fan_ctww_set_fan_speed_wpm(stwuct pp_hwmgw *hwmgw, uint32_t speed)
{
	uint32_t tach_pewiod;
	uint32_t cwystaw_cwock_fweq;

	if (hwmgw->thewmaw_contwowwew.fanInfo.bNoFan ||
			(hwmgw->thewmaw_contwowwew.fanInfo.
			ucTachometewPuwsesPewWevowution == 0) ||
			speed == 0 ||
			(speed < hwmgw->thewmaw_contwowwew.fanInfo.uwMinWPM) ||
			(speed > hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM))
		wetuwn 0;

	if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow))
		smu7_fan_ctww_stop_smc_fan_contwow(hwmgw);

	cwystaw_cwock_fweq = amdgpu_asic_get_xcwk((stwuct amdgpu_device *)hwmgw->adev);

	tach_pewiod = 60 * cwystaw_cwock_fweq * 10000 / (8 * speed);

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				CG_TACH_CTWW, TAWGET_PEWIOD, tach_pewiod);

	wetuwn smu7_fan_ctww_set_static_mode(hwmgw, FDO_PWM_MODE_STATIC_WPM);
}

/**
 * smu7_thewmaw_get_tempewatuwe - Weads the wemote tempewatuwe fwom the SIswands thewmaw contwowwew.
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 */
int smu7_thewmaw_get_tempewatuwe(stwuct pp_hwmgw *hwmgw)
{
	int temp;

	temp = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_MUWT_THEWMAW_STATUS, CTF_TEMP);

	/* Bit 9 means the weading is wowew than the wowest usabwe vawue. */
	if (temp & 0x200)
		temp = SMU7_THEWMAW_MAXIMUM_TEMP_WEADING;
	ewse
		temp = temp & 0x1ff;

	temp *= PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	wetuwn temp;
}

/**
 * smu7_thewmaw_set_tempewatuwe_wange - Set the wequested tempewatuwe wange fow high and wow awewt signaws
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 * @wow_temp: Tempewatuwe to be pwogwammed fow high awewt signaws
 * @high_temp: Tempewatuwe to be pwogwammed fow wow awewt signaws
 * Exception: PP_Wesuwt_BadInput if the input data is not vawid.
 */
static int smu7_thewmaw_set_tempewatuwe_wange(stwuct pp_hwmgw *hwmgw,
		int wow_temp, int high_temp)
{
	int wow = SMU7_THEWMAW_MINIMUM_AWEWT_TEMP *
			PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	int high = SMU7_THEWMAW_MAXIMUM_AWEWT_TEMP *
			PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;

	if (wow < wow_temp)
		wow = wow_temp;
	if (high > high_temp)
		high = high_temp;

	if (wow > high)
		wetuwn -EINVAW;

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_THEWMAW_INT, DIG_THEWM_INTH,
			(high / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES));
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_THEWMAW_INT, DIG_THEWM_INTW,
			(wow / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES));
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_THEWMAW_CTWW, DIG_THEWM_DPM,
			(high / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES));

	wetuwn 0;
}

/**
 * smu7_thewmaw_initiawize - Pwogwams thewmaw contwowwew one-time setting wegistews
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 */
static int smu7_thewmaw_initiawize(stwuct pp_hwmgw *hwmgw)
{
	if (hwmgw->thewmaw_contwowwew.fanInfo.ucTachometewPuwsesPewWevowution)
		PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
				CG_TACH_CTWW, EDGE_PEW_WEV,
				hwmgw->thewmaw_contwowwew.fanInfo.
				ucTachometewPuwsesPewWevowution - 1);

	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_FDO_CTWW2, TACH_PWM_WESP_WATE, 0x28);

	wetuwn 0;
}

/**
 * smu7_thewmaw_enabwe_awewt - Enabwe thewmaw awewts on the WV770 thewmaw contwowwew.
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 */
static void smu7_thewmaw_enabwe_awewt(stwuct pp_hwmgw *hwmgw)
{
	uint32_t awewt;

	awewt = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_THEWMAW_INT, THEWM_INT_MASK);
	awewt &= ~(SMU7_THEWMAW_HIGH_AWEWT_MASK | SMU7_THEWMAW_WOW_AWEWT_MASK);
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_THEWMAW_INT, THEWM_INT_MASK, awewt);

	/* send message to SMU to enabwe intewnaw thewmaw intewwupts */
	smum_send_msg_to_smc(hwmgw, PPSMC_MSG_Thewmaw_Cntw_Enabwe, NUWW);
}

/**
 * smu7_thewmaw_disabwe_awewt - Disabwe thewmaw awewts on the WV770 thewmaw contwowwew.
 * @hwmgw: The addwess of the hawdwawe managew.
 */
int smu7_thewmaw_disabwe_awewt(stwuct pp_hwmgw *hwmgw)
{
	uint32_t awewt;

	awewt = PHM_WEAD_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_THEWMAW_INT, THEWM_INT_MASK);
	awewt |= (SMU7_THEWMAW_HIGH_AWEWT_MASK | SMU7_THEWMAW_WOW_AWEWT_MASK);
	PHM_WWITE_VFPF_INDIWECT_FIEWD(hwmgw->device, CGS_IND_WEG__SMC,
			CG_THEWMAW_INT, THEWM_INT_MASK, awewt);

	/* send message to SMU to disabwe intewnaw thewmaw intewwupts */
	wetuwn smum_send_msg_to_smc(hwmgw, PPSMC_MSG_Thewmaw_Cntw_Disabwe, NUWW);
}

/**
 * smu7_thewmaw_stop_thewmaw_contwowwew - Uninitiawize the thewmaw contwowwew.
 * Cuwwentwy just disabwes awewts.
 * @hwmgw: The addwess of the hawdwawe managew.
 */
int smu7_thewmaw_stop_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = smu7_thewmaw_disabwe_awewt(hwmgw);

	if (!hwmgw->thewmaw_contwowwew.fanInfo.bNoFan)
		smu7_fan_ctww_set_defauwt_mode(hwmgw);

	wetuwn wesuwt;
}

/**
 * smu7_thewmaw_stawt_smc_fan_contwow - Stawt the fan contwow on the SMC.
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   wesuwt fwom set tempewatuwe wange woutine
 */
static int smu7_thewmaw_stawt_smc_fan_contwow(stwuct pp_hwmgw *hwmgw)
{
/* If the fantabwe setup has faiwed we couwd have disabwed
 * PHM_PwatfowmCaps_MicwocodeFanContwow even aftew
 * this function was incwuded in the tabwe.
 * Make suwe that we stiww think contwowwing the fan is OK.
*/
	if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow)) {
		smu7_fan_ctww_stawt_smc_fan_contwow(hwmgw);
		smu7_fan_ctww_set_static_mode(hwmgw, FDO_PWM_MODE_STATIC);
	}

	wetuwn 0;
}

int smu7_stawt_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw,
				stwuct PP_TempewatuweWange *wange)
{
	int wet = 0;

	if (wange == NUWW)
		wetuwn -EINVAW;

	smu7_thewmaw_initiawize(hwmgw);
	wet = smu7_thewmaw_set_tempewatuwe_wange(hwmgw, wange->min, wange->max);
	if (wet)
		wetuwn -EINVAW;
	smu7_thewmaw_enabwe_awewt(hwmgw);
	wet = smum_thewmaw_avfs_enabwe(hwmgw);
	if (wet)
		wetuwn -EINVAW;

/* We shouwd westwict pewfowmance wevews to wow befowe we hawt the SMC.
 * On the othew hand we awe stiww in boot state when we do this
 * so it wouwd be pointwess.
 * If this assumption changes we have to wevisit this tabwe.
 */
	smum_thewmaw_setup_fan_tabwe(hwmgw);
	smu7_thewmaw_stawt_smc_fan_contwow(hwmgw);
	wetuwn 0;
}



int smu7_thewmaw_ctww_uninitiawize_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw)
{
	if (!hwmgw->thewmaw_contwowwew.fanInfo.bNoFan)
		smu7_fan_ctww_set_defauwt_mode(hwmgw);
	wetuwn 0;
}

