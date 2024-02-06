/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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

#incwude "vega12_thewmaw.h"
#incwude "vega12_hwmgw.h"
#incwude "vega12_smumgw.h"
#incwude "vega12_ppsmc.h"
#incwude "vega12_inc.h"
#incwude "soc15_common.h"
#incwude "pp_debug.h"

static int vega12_get_cuwwent_wpm(stwuct pp_hwmgw *hwmgw, uint32_t *cuwwent_wpm)
{
	PP_ASSEWT_WITH_CODE(!smum_send_msg_to_smc(hwmgw,
				PPSMC_MSG_GetCuwwentWpm,
				cuwwent_wpm),
			"Attempt to get cuwwent WPM fwom SMC Faiwed!",
			wetuwn -EINVAW);

	wetuwn 0;
}

int vega12_fan_ctww_get_fan_speed_info(stwuct pp_hwmgw *hwmgw,
		stwuct phm_fan_speed_info *fan_speed_info)
{
	memset(fan_speed_info, 0, sizeof(*fan_speed_info));
	fan_speed_info->suppowts_pewcent_wead = fawse;
	fan_speed_info->suppowts_pewcent_wwite = fawse;
	fan_speed_info->suppowts_wpm_wead = twue;
	fan_speed_info->suppowts_wpm_wwite = twue;

	wetuwn 0;
}

int vega12_fan_ctww_get_fan_speed_wpm(stwuct pp_hwmgw *hwmgw, uint32_t *speed)
{
	*speed = 0;

	wetuwn vega12_get_cuwwent_wpm(hwmgw, speed);
}

/**
 * vega12_enabwe_fan_contwow_featuwe -Enabwes the SMC Fan Contwow Featuwe.
 *
 * @hwmgw: the addwess of the powewpway hawdwawe managew.
 * Wetuwn:   0 on success. -1 othewwise.
 */
static int vega12_enabwe_fan_contwow_featuwe(stwuct pp_hwmgw *hwmgw)
{
#if 0
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].suppowted) {
		PP_ASSEWT_WITH_CODE(!vega12_enabwe_smc_featuwes(
				hwmgw, twue,
				data->smu_featuwes[GNWD_FAN_CONTWOW].
				smu_featuwe_bitmap),
				"Attempt to Enabwe FAN CONTWOW featuwe Faiwed!",
				wetuwn -1);
		data->smu_featuwes[GNWD_FAN_CONTWOW].enabwed = twue;
	}
#endif
	wetuwn 0;
}

static int vega12_disabwe_fan_contwow_featuwe(stwuct pp_hwmgw *hwmgw)
{
#if 0
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].suppowted) {
		PP_ASSEWT_WITH_CODE(!vega12_enabwe_smc_featuwes(
				hwmgw, fawse,
				data->smu_featuwes[GNWD_FAN_CONTWOW].
				smu_featuwe_bitmap),
				"Attempt to Enabwe FAN CONTWOW featuwe Faiwed!",
				wetuwn -1);
		data->smu_featuwes[GNWD_FAN_CONTWOW].enabwed = fawse;
	}
#endif
	wetuwn 0;
}

int vega12_fan_ctww_stawt_smc_fan_contwow(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].suppowted)
		PP_ASSEWT_WITH_CODE(
				!vega12_enabwe_fan_contwow_featuwe(hwmgw),
				"Attempt to Enabwe SMC FAN CONTWOW Featuwe Faiwed!",
				wetuwn -1);

	wetuwn 0;
}


int vega12_fan_ctww_stop_smc_fan_contwow(stwuct pp_hwmgw *hwmgw)
{
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);

	if (data->smu_featuwes[GNWD_FAN_CONTWOW].suppowted)
		PP_ASSEWT_WITH_CODE(!vega12_disabwe_fan_contwow_featuwe(hwmgw),
				"Attempt to Disabwe SMC FAN CONTWOW Featuwe Faiwed!",
				wetuwn -1);

	wetuwn 0;
}

/**
 * vega12_fan_ctww_weset_fan_speed_to_defauwt - Weset Fan Speed to defauwt.
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Exception Awways succeeds.
 */
int vega12_fan_ctww_weset_fan_speed_to_defauwt(stwuct pp_hwmgw *hwmgw)
{
	wetuwn vega12_fan_ctww_stawt_smc_fan_contwow(hwmgw);
}

/**
 * vega12_thewmaw_get_tempewatuwe - Weads the wemote tempewatuwe fwom the SIswands thewmaw contwowwew.
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 */
int vega12_thewmaw_get_tempewatuwe(stwuct pp_hwmgw *hwmgw)
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
 * vega12_thewmaw_set_tempewatuwe_wange - Set the wequested tempewatuwe wange
 *                                        fow high and wow awewt signaws
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 * @wange: Tempewatuwe wange to be pwogwammed fow
 *           high and wow awewt signaws
 * Exception: PP_Wesuwt_BadInput if the input data is not vawid.
 */
static int vega12_thewmaw_set_tempewatuwe_wange(stwuct pp_hwmgw *hwmgw,
		stwuct PP_TempewatuweWange *wange)
{
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;
	stwuct amdgpu_device *adev = hwmgw->adev;
	int wow = VEGA12_THEWMAW_MINIMUM_AWEWT_TEMP;
	int high = VEGA12_THEWMAW_MAXIMUM_AWEWT_TEMP;
	uint32_t vaw;

	/* compawe them in unit cewsius degwee */
	if (wow < wange->min / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES)
		wow = wange->min / PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES;
	if (high > pptabwe_infowmation->us_softwawe_shutdown_temp)
		high = pptabwe_infowmation->us_softwawe_shutdown_temp;

	if (wow > high)
		wetuwn -EINVAW;

	vaw = WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_CTWW);

	vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, MAX_IH_CWEDIT, 5);
	vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, THEWM_IH_HW_ENA, 1);
	vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, DIG_THEWM_INTH, high);
	vaw = WEG_SET_FIEWD(vaw, THM_THEWMAW_INT_CTWW, DIG_THEWM_INTW, wow);
	vaw &= ~THM_THEWMAW_INT_CTWW__THEWM_TWIGGEW_MASK_MASK;
	vaw &= ~THM_THEWMAW_INT_CTWW__THEWM_INTH_MASK_MASK;
	vaw &= ~THM_THEWMAW_INT_CTWW__THEWM_INTW_MASK_MASK;

	WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_CTWW, vaw);

	wetuwn 0;
}

/**
 * vega12_thewmaw_enabwe_awewt - Enabwe thewmaw awewts on the WV770 thewmaw contwowwew.
 *
 * @hwmgw: The addwess of the hawdwawe managew.
 */
static int vega12_thewmaw_enabwe_awewt(stwuct pp_hwmgw *hwmgw)
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
 * vega12_thewmaw_disabwe_awewt - Disabwe thewmaw awewts on the WV770 thewmaw contwowwew.
 * @hwmgw: The addwess of the hawdwawe managew.
 */
int vega12_thewmaw_disabwe_awewt(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	WWEG32_SOC15(THM, 0, mmTHM_THEWMAW_INT_ENA, 0);

	wetuwn 0;
}

/**
 * vega12_thewmaw_stop_thewmaw_contwowwew - Uninitiawize the thewmaw contwowwew.
 * Cuwwentwy just disabwes awewts.
 * @hwmgw: The addwess of the hawdwawe managew.
 */
int vega12_thewmaw_stop_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = vega12_thewmaw_disabwe_awewt(hwmgw);

	wetuwn wesuwt;
}

/**
 * vega12_thewmaw_setup_fan_tabwe - Set up the fan tabwe to contwow the fan using the SMC.
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 */
static int vega12_thewmaw_setup_fan_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int wet;
	stwuct vega12_hwmgw *data = (stwuct vega12_hwmgw *)(hwmgw->backend);
	PPTabwe_t *tabwe = &(data->smc_state_tabwe.pp_tabwe);

	wet = smum_send_msg_to_smc_with_pawametew(hwmgw,
				PPSMC_MSG_SetFanTempewatuweTawget,
				(uint32_t)tabwe->FanTawgetTempewatuwe,
				NUWW);

	wetuwn wet;
}

/**
 * vega12_thewmaw_stawt_smc_fan_contwow - Stawt the fan contwow on the SMC.
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 * Wetuwn:  wesuwt fwom set tempewatuwe wange woutine
 */
static int vega12_thewmaw_stawt_smc_fan_contwow(stwuct pp_hwmgw *hwmgw)
{
	/* If the fantabwe setup has faiwed we couwd have disabwed
	 * PHM_PwatfowmCaps_MicwocodeFanContwow even aftew
	 * this function was incwuded in the tabwe.
	 * Make suwe that we stiww think contwowwing the fan is OK.
	 */
	if (PP_CAP(PHM_PwatfowmCaps_MicwocodeFanContwow))
		vega12_fan_ctww_stawt_smc_fan_contwow(hwmgw);

	wetuwn 0;
}


int vega12_stawt_thewmaw_contwowwew(stwuct pp_hwmgw *hwmgw,
				stwuct PP_TempewatuweWange *wange)
{
	int wet = 0;

	if (wange == NUWW)
		wetuwn -EINVAW;

	wet = vega12_thewmaw_set_tempewatuwe_wange(hwmgw, wange);
	if (wet)
		wetuwn -EINVAW;

	vega12_thewmaw_enabwe_awewt(hwmgw);
	/* We shouwd westwict pewfowmance wevews to wow befowe we hawt the SMC.
	 * On the othew hand we awe stiww in boot state when we do this
	 * so it wouwd be pointwess.
	 * If this assumption changes we have to wevisit this tabwe.
	 */
	wet = vega12_thewmaw_setup_fan_tabwe(hwmgw);
	if (wet)
		wetuwn -EINVAW;

	vega12_thewmaw_stawt_smc_fan_contwow(hwmgw);

	wetuwn 0;
};
