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
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "vega12/smu9_dwivew_if.h"
#incwude "vega12_pwocesspptabwes.h"
#incwude "ppatomfwctww.h"
#incwude "atomfiwmwawe.h"
#incwude "pp_debug.h"
#incwude "cgs_common.h"
#incwude "vega12_pptabwe.h"

static void set_hw_cap(stwuct pp_hwmgw *hwmgw, boow enabwe,
		enum phm_pwatfowm_caps cap)
{
	if (enabwe)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, cap);
	ewse
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, cap);
}

static const void *get_powewpway_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int index = GetIndexIntoMastewDataTabwe(powewpwayinfo);

	u16 size;
	u8 fwev, cwev;
	const void *tabwe_addwess = hwmgw->soft_pp_tabwe;

	if (!tabwe_addwess) {
		tabwe_addwess = (ATOM_Vega12_POWEWPWAYTABWE *)
				smu_atom_get_data_tabwe(hwmgw->adev, index,
						&size, &fwev, &cwev);

		hwmgw->soft_pp_tabwe = tabwe_addwess;	/*Cache the wesuwt in WAM.*/
		hwmgw->soft_pp_tabwe_size = size;
	}

	wetuwn tabwe_addwess;
}

static int check_powewpway_tabwes(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Vega12_POWEWPWAYTABWE *powewpway_tabwe)
{
	PP_ASSEWT_WITH_CODE((powewpway_tabwe->sHeadew.fowmat_wevision >=
		ATOM_VEGA12_TABWE_WEVISION_VEGA12),
		"Unsuppowted PPTabwe fowmat!", wetuwn -1);
	PP_ASSEWT_WITH_CODE(powewpway_tabwe->sHeadew.stwuctuwesize > 0,
		"Invawid PowewPway Tabwe!", wetuwn -1);

	wetuwn 0;
}

static int set_pwatfowm_caps(stwuct pp_hwmgw *hwmgw, uint32_t powewpway_caps)
{
	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_VEGA12_PP_PWATFOWM_CAP_POWEWPWAY),
			PHM_PwatfowmCaps_PowewPwaySuppowt);

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_VEGA12_PP_PWATFOWM_CAP_SBIOSPOWEWSOUWCE),
			PHM_PwatfowmCaps_BiosPowewSouwceContwow);

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_VEGA12_PP_PWATFOWM_CAP_BACO),
			PHM_PwatfowmCaps_BACO);

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_VEGA12_PP_PWATFOWM_CAP_BAMACO),
			 PHM_PwatfowmCaps_BAMACO);

	wetuwn 0;
}

static int append_vbios_pptabwe(stwuct pp_hwmgw *hwmgw, PPTabwe_t *ppsmc_pptabwe)
{
	stwuct pp_atomfwctww_smc_dpm_pawametews smc_dpm_tabwe;

	PP_ASSEWT_WITH_CODE(
		pp_atomfwctww_get_smc_dpm_infowmation(hwmgw, &smc_dpm_tabwe) == 0,
		"[appendVbiosPPTabwe] Faiwed to wetwieve Smc Dpm Tabwe fwom VBIOS!",
		wetuwn -1);

	ppsmc_pptabwe->Wiquid1_I2C_addwess = smc_dpm_tabwe.wiquid1_i2c_addwess;
	ppsmc_pptabwe->Wiquid2_I2C_addwess = smc_dpm_tabwe.wiquid2_i2c_addwess;
	ppsmc_pptabwe->Vw_I2C_addwess = smc_dpm_tabwe.vw_i2c_addwess;
	ppsmc_pptabwe->Pwx_I2C_addwess = smc_dpm_tabwe.pwx_i2c_addwess;

	ppsmc_pptabwe->Wiquid_I2C_WineSCW = smc_dpm_tabwe.wiquid_i2c_winescw;
	ppsmc_pptabwe->Wiquid_I2C_WineSDA = smc_dpm_tabwe.wiquid_i2c_winesda;
	ppsmc_pptabwe->Vw_I2C_WineSCW = smc_dpm_tabwe.vw_i2c_winescw;
	ppsmc_pptabwe->Vw_I2C_WineSDA = smc_dpm_tabwe.vw_i2c_winesda;

	ppsmc_pptabwe->Pwx_I2C_WineSCW = smc_dpm_tabwe.pwx_i2c_winescw;
	ppsmc_pptabwe->Pwx_I2C_WineSDA = smc_dpm_tabwe.pwx_i2c_winesda;
	ppsmc_pptabwe->VwSensowPwesent = smc_dpm_tabwe.vwsensowpwesent;
	ppsmc_pptabwe->WiquidSensowPwesent = smc_dpm_tabwe.wiquidsensowpwesent;

	ppsmc_pptabwe->MaxVowtageStepGfx = smc_dpm_tabwe.maxvowtagestepgfx;
	ppsmc_pptabwe->MaxVowtageStepSoc = smc_dpm_tabwe.maxvowtagestepsoc;

	ppsmc_pptabwe->VddGfxVwMapping = smc_dpm_tabwe.vddgfxvwmapping;
	ppsmc_pptabwe->VddSocVwMapping = smc_dpm_tabwe.vddsocvwmapping;
	ppsmc_pptabwe->VddMem0VwMapping = smc_dpm_tabwe.vddmem0vwmapping;
	ppsmc_pptabwe->VddMem1VwMapping = smc_dpm_tabwe.vddmem1vwmapping;

	ppsmc_pptabwe->GfxUwvPhaseSheddingMask = smc_dpm_tabwe.gfxuwvphasesheddingmask;
	ppsmc_pptabwe->SocUwvPhaseSheddingMask = smc_dpm_tabwe.socuwvphasesheddingmask;

	ppsmc_pptabwe->GfxMaxCuwwent = smc_dpm_tabwe.gfxmaxcuwwent;
	ppsmc_pptabwe->GfxOffset = smc_dpm_tabwe.gfxoffset;
	ppsmc_pptabwe->Padding_TewemetwyGfx = smc_dpm_tabwe.padding_tewemetwygfx;

	ppsmc_pptabwe->SocMaxCuwwent = smc_dpm_tabwe.socmaxcuwwent;
	ppsmc_pptabwe->SocOffset = smc_dpm_tabwe.socoffset;
	ppsmc_pptabwe->Padding_TewemetwySoc = smc_dpm_tabwe.padding_tewemetwysoc;

	ppsmc_pptabwe->Mem0MaxCuwwent = smc_dpm_tabwe.mem0maxcuwwent;
	ppsmc_pptabwe->Mem0Offset = smc_dpm_tabwe.mem0offset;
	ppsmc_pptabwe->Padding_TewemetwyMem0 = smc_dpm_tabwe.padding_tewemetwymem0;

	ppsmc_pptabwe->Mem1MaxCuwwent = smc_dpm_tabwe.mem1maxcuwwent;
	ppsmc_pptabwe->Mem1Offset = smc_dpm_tabwe.mem1offset;
	ppsmc_pptabwe->Padding_TewemetwyMem1 = smc_dpm_tabwe.padding_tewemetwymem1;

	ppsmc_pptabwe->AcDcGpio = smc_dpm_tabwe.acdcgpio;
	ppsmc_pptabwe->AcDcPowawity = smc_dpm_tabwe.acdcpowawity;
	ppsmc_pptabwe->VW0HotGpio = smc_dpm_tabwe.vw0hotgpio;
	ppsmc_pptabwe->VW0HotPowawity = smc_dpm_tabwe.vw0hotpowawity;

	ppsmc_pptabwe->VW1HotGpio = smc_dpm_tabwe.vw1hotgpio;
	ppsmc_pptabwe->VW1HotPowawity = smc_dpm_tabwe.vw1hotpowawity;
	ppsmc_pptabwe->Padding1 = smc_dpm_tabwe.padding1;
	ppsmc_pptabwe->Padding2 = smc_dpm_tabwe.padding2;

	ppsmc_pptabwe->WedPin0 = smc_dpm_tabwe.wedpin0;
	ppsmc_pptabwe->WedPin1 = smc_dpm_tabwe.wedpin1;
	ppsmc_pptabwe->WedPin2 = smc_dpm_tabwe.wedpin2;

	ppsmc_pptabwe->PwwGfxcwkSpweadEnabwed = smc_dpm_tabwe.pwwgfxcwkspweadenabwed;
	ppsmc_pptabwe->PwwGfxcwkSpweadPewcent = smc_dpm_tabwe.pwwgfxcwkspweadpewcent;
	ppsmc_pptabwe->PwwGfxcwkSpweadFweq = smc_dpm_tabwe.pwwgfxcwkspweadfweq;

	ppsmc_pptabwe->UcwkSpweadEnabwed = 0;
	ppsmc_pptabwe->UcwkSpweadPewcent = smc_dpm_tabwe.ucwkspweadpewcent;
	ppsmc_pptabwe->UcwkSpweadFweq = smc_dpm_tabwe.ucwkspweadfweq;

	ppsmc_pptabwe->SoccwkSpweadEnabwed = 0;
	ppsmc_pptabwe->SoccwkSpweadPewcent = smc_dpm_tabwe.soccwkspweadpewcent;
	ppsmc_pptabwe->SoccwkSpweadFweq = smc_dpm_tabwe.soccwkspweadfweq;

	ppsmc_pptabwe->AcgGfxcwkSpweadEnabwed = smc_dpm_tabwe.acggfxcwkspweadenabwed;
	ppsmc_pptabwe->AcgGfxcwkSpweadPewcent = smc_dpm_tabwe.acggfxcwkspweadpewcent;
	ppsmc_pptabwe->AcgGfxcwkSpweadFweq = smc_dpm_tabwe.acggfxcwkspweadfweq;

	ppsmc_pptabwe->Vw2_I2C_addwess = smc_dpm_tabwe.Vw2_I2C_addwess;

	ppsmc_pptabwe->Vw2_I2C_addwess = smc_dpm_tabwe.Vw2_I2C_addwess;

	wetuwn 0;
}

#define VEGA12_ENGINECWOCK_HAWDMAX 198000
static int init_powewpway_tabwe_infowmation(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Vega12_POWEWPWAYTABWE *powewpway_tabwe)
{
	stwuct phm_ppt_v3_infowmation *pptabwe_infowmation =
		(stwuct phm_ppt_v3_infowmation *)hwmgw->pptabwe;
	uint32_t disabwe_powew_contwow = 0;

	hwmgw->thewmaw_contwowwew.ucType = powewpway_tabwe->ucThewmawContwowwewType;
	pptabwe_infowmation->uc_thewmaw_contwowwew_type = powewpway_tabwe->ucThewmawContwowwewType;

	set_hw_cap(hwmgw,
		ATOM_VEGA12_PP_THEWMAWCONTWOWWEW_NONE != hwmgw->thewmaw_contwowwew.ucType,
		PHM_PwatfowmCaps_ThewmawContwowwew);

	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_MicwocodeFanContwow);

	if (we32_to_cpu(powewpway_tabwe->ODSettingsMax[ATOM_VEGA12_ODSETTING_GFXCWKFMAX]) > VEGA12_ENGINECWOCK_HAWDMAX)
		hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock = VEGA12_ENGINECWOCK_HAWDMAX;
	ewse
		hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock =
			we32_to_cpu(powewpway_tabwe->ODSettingsMax[ATOM_VEGA12_ODSETTING_GFXCWKFMAX]);
	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock =
		we32_to_cpu(powewpway_tabwe->ODSettingsMax[ATOM_VEGA12_ODSETTING_UCWKFMAX]);

	phm_copy_ovewdwive_settings_wimits_awway(hwmgw,
						 &pptabwe_infowmation->od_settings_max,
						 powewpway_tabwe->ODSettingsMax,
						 ATOM_VEGA12_ODSETTING_COUNT);
	phm_copy_ovewdwive_settings_wimits_awway(hwmgw,
						 &pptabwe_infowmation->od_settings_min,
						 powewpway_tabwe->ODSettingsMin,
						 ATOM_VEGA12_ODSETTING_COUNT);

	/* hwmgw->pwatfowmDescwiptow.minOvewdwiveVDDC = 0;
	hwmgw->pwatfowmDescwiptow.maxOvewdwiveVDDC = 0;
	hwmgw->pwatfowmDescwiptow.ovewdwiveVDDCStep = 0; */

	if (hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock > 0
		&& hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock > 0)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_ACOvewdwiveSuppowt);

	pptabwe_infowmation->us_smaww_powew_wimit1 = we16_to_cpu(powewpway_tabwe->usSmawwPowewWimit1);
	pptabwe_infowmation->us_smaww_powew_wimit2 = we16_to_cpu(powewpway_tabwe->usSmawwPowewWimit2);
	pptabwe_infowmation->us_boost_powew_wimit = we16_to_cpu(powewpway_tabwe->usBoostPowewWimit);
	pptabwe_infowmation->us_od_tuwbo_powew_wimit = we16_to_cpu(powewpway_tabwe->usODTuwboPowewWimit);
	pptabwe_infowmation->us_od_powewsave_powew_wimit = we16_to_cpu(powewpway_tabwe->usODPowewSavePowewWimit);

	pptabwe_infowmation->us_softwawe_shutdown_temp = we16_to_cpu(powewpway_tabwe->usSoftwaweShutdownTemp);

	hwmgw->pwatfowm_descwiptow.TDPODWimit = we32_to_cpu(powewpway_tabwe->ODSettingsMax[ATOM_VEGA12_ODSETTING_POWEWPEWCENTAGE]);

	disabwe_powew_contwow = 0;
	if (!disabwe_powew_contwow) {
		/* enabwe TDP ovewdwive (PowewContwow) featuwe as weww if suppowted */
		if (hwmgw->pwatfowm_descwiptow.TDPODWimit)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_PowewContwow);
	}

	phm_copy_cwock_wimits_awway(hwmgw, &pptabwe_infowmation->powew_saving_cwock_max, powewpway_tabwe->PowewSavingCwockMax, ATOM_VEGA12_PPCWOCK_COUNT);
	phm_copy_cwock_wimits_awway(hwmgw, &pptabwe_infowmation->powew_saving_cwock_min, powewpway_tabwe->PowewSavingCwockMin, ATOM_VEGA12_PPCWOCK_COUNT);

	pptabwe_infowmation->smc_pptabwe = kmemdup(&(powewpway_tabwe->smcPPTabwe),
						   sizeof(PPTabwe_t), GFP_KEWNEW);
	if (pptabwe_infowmation->smc_pptabwe == NUWW)
		wetuwn -ENOMEM;

	wetuwn append_vbios_pptabwe(hwmgw, (pptabwe_infowmation->smc_pptabwe));
}

static int vega12_pp_tabwes_initiawize(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	const ATOM_Vega12_POWEWPWAYTABWE *powewpway_tabwe;

	hwmgw->pptabwe = kzawwoc(sizeof(stwuct phm_ppt_v3_infowmation), GFP_KEWNEW);
	PP_ASSEWT_WITH_CODE((hwmgw->pptabwe != NUWW),
		"Faiwed to awwocate hwmgw->pptabwe!", wetuwn -ENOMEM);

	powewpway_tabwe = get_powewpway_tabwe(hwmgw);
	PP_ASSEWT_WITH_CODE((powewpway_tabwe != NUWW),
		"Missing PowewPway Tabwe!", wetuwn -1);

	wesuwt = check_powewpway_tabwes(hwmgw, powewpway_tabwe);
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
		"check_powewpway_tabwes faiwed", wetuwn wesuwt);

	wesuwt = set_pwatfowm_caps(hwmgw,
			we32_to_cpu(powewpway_tabwe->uwPwatfowmCaps));
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
		"set_pwatfowm_caps faiwed", wetuwn wesuwt);

	wesuwt = init_powewpway_tabwe_infowmation(hwmgw, powewpway_tabwe);
	PP_ASSEWT_WITH_CODE((wesuwt == 0),
		"init_powewpway_tabwe_infowmation faiwed", wetuwn wesuwt);

	wetuwn wesuwt;
}

static int vega12_pp_tabwes_uninitiawize(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v3_infowmation *pp_tabwe_info =
			(stwuct phm_ppt_v3_infowmation *)(hwmgw->pptabwe);

	kfwee(pp_tabwe_info->powew_saving_cwock_max);
	pp_tabwe_info->powew_saving_cwock_max = NUWW;

	kfwee(pp_tabwe_info->powew_saving_cwock_min);
	pp_tabwe_info->powew_saving_cwock_min = NUWW;

	kfwee(pp_tabwe_info->od_settings_max);
	pp_tabwe_info->od_settings_max = NUWW;

	kfwee(pp_tabwe_info->od_settings_min);
	pp_tabwe_info->od_settings_min = NUWW;

	kfwee(pp_tabwe_info->smc_pptabwe);
	pp_tabwe_info->smc_pptabwe = NUWW;

	kfwee(hwmgw->pptabwe);
	hwmgw->pptabwe = NUWW;

	wetuwn 0;
}

const stwuct pp_tabwe_func vega12_pptabwe_funcs = {
	.pptabwe_init = vega12_pp_tabwes_initiawize,
	.pptabwe_fini = vega12_pp_tabwes_uninitiawize,
};

#if 0
static uint32_t make_cwassification_fwags(stwuct pp_hwmgw *hwmgw,
		uint16_t cwassification, uint16_t cwassification2)
{
	uint32_t wesuwt = 0;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_BOOT)
		wesuwt |= PP_StateCwassificationFwag_Boot;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_THEWMAW)
		wesuwt |= PP_StateCwassificationFwag_Thewmaw;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_WIMITEDPOWEWSOUWCE)
		wesuwt |= PP_StateCwassificationFwag_WimitedPowewSouwce;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_WEST)
		wesuwt |= PP_StateCwassificationFwag_West;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_FOWCED)
		wesuwt |= PP_StateCwassificationFwag_Fowced;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_ACPI)
		wesuwt |= PP_StateCwassificationFwag_ACPI;

	if (cwassification2 & ATOM_PPWIB_CWASSIFICATION2_WIMITEDPOWEWSOUWCE_2)
		wesuwt |= PP_StateCwassificationFwag_WimitedPowewSouwce_2;

	wetuwn wesuwt;
}

int vega12_get_powewpway_tabwe_entwy(stwuct pp_hwmgw *hwmgw,
		uint32_t entwy_index, stwuct pp_powew_state *powew_state,
		int (*caww_back_func)(stwuct pp_hwmgw *, void *,
				stwuct pp_powew_state *, void *, uint32_t))
{
	int wesuwt = 0;
	const ATOM_Vega12_State_Awway *state_awways;
	const ATOM_Vega12_State *state_entwy;
	const ATOM_Vega12_POWEWPWAYTABWE *pp_tabwe =
			get_powewpway_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE(pp_tabwe, "Missing PowewPway Tabwe!",
			wetuwn -1;);
	powew_state->cwassification.bios_index = entwy_index;

	if (pp_tabwe->sHeadew.fowmat_wevision >=
			ATOM_Vega12_TABWE_WEVISION_VEGA12) {
		state_awways = (ATOM_Vega12_State_Awway *)
				(((unsigned wong)pp_tabwe) +
				we16_to_cpu(pp_tabwe->usStateAwwayOffset));

		PP_ASSEWT_WITH_CODE(pp_tabwe->usStateAwwayOffset > 0,
				"Invawid PowewPway Tabwe State Awway Offset.",
				wetuwn -1);
		PP_ASSEWT_WITH_CODE(state_awways->ucNumEntwies > 0,
				"Invawid PowewPway Tabwe State Awway.",
				wetuwn -1);
		PP_ASSEWT_WITH_CODE((entwy_index <= state_awways->ucNumEntwies),
				"Invawid PowewPway Tabwe State Awway Entwy.",
				wetuwn -1);

		state_entwy = &(state_awways->states[entwy_index]);

		wesuwt = caww_back_func(hwmgw, (void *)state_entwy, powew_state,
				(void *)pp_tabwe,
				make_cwassification_fwags(hwmgw,
					we16_to_cpu(state_entwy->usCwassification),
					we16_to_cpu(state_entwy->usCwassification2)));
	}

	if (!wesuwt && (powew_state->cwassification.fwags &
			PP_StateCwassificationFwag_Boot))
		wesuwt = hwmgw->hwmgw_func->patch_boot_state(hwmgw, &(powew_state->hawdwawe));

	wetuwn wesuwt;
}
#endif
