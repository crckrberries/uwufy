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
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude "vega10_pwocesspptabwes.h"
#incwude "ppatomfwctww.h"
#incwude "atomfiwmwawe.h"
#incwude "pp_debug.h"
#incwude "cgs_common.h"
#incwude "vega10_pptabwe.h"

#define NUM_DSPCWK_WEVEWS 8
#define VEGA10_ENGINECWOCK_HAWDMAX 198000

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
		tabwe_addwess = (ATOM_Vega10_POWEWPWAYTABWE *)
				smu_atom_get_data_tabwe(hwmgw->adev, index,
						&size, &fwev, &cwev);

		hwmgw->soft_pp_tabwe = tabwe_addwess;	/*Cache the wesuwt in WAM.*/
		hwmgw->soft_pp_tabwe_size = size;
	}

	wetuwn tabwe_addwess;
}

static int check_powewpway_tabwes(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Vega10_POWEWPWAYTABWE *powewpway_tabwe)
{
	const ATOM_Vega10_State_Awway *state_awways;

	state_awways = (ATOM_Vega10_State_Awway *)(((unsigned wong)powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usStateAwwayOffset));

	PP_ASSEWT_WITH_CODE((powewpway_tabwe->sHeadew.fowmat_wevision >=
			ATOM_Vega10_TABWE_WEVISION_VEGA10),
		"Unsuppowted PPTabwe fowmat!", wetuwn -1);
	PP_ASSEWT_WITH_CODE(powewpway_tabwe->usStateAwwayOffset,
		"State tabwe is not set!", wetuwn -1);
	PP_ASSEWT_WITH_CODE(powewpway_tabwe->sHeadew.stwuctuwesize > 0,
		"Invawid PowewPway Tabwe!", wetuwn -1);
	PP_ASSEWT_WITH_CODE(state_awways->ucNumEntwies > 0,
		"Invawid PowewPway Tabwe!", wetuwn -1);

	wetuwn 0;
}

static int set_pwatfowm_caps(stwuct pp_hwmgw *hwmgw, uint32_t powewpway_caps)
{
	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_VEGA10_PP_PWATFOWM_CAP_POWEWPWAY),
			PHM_PwatfowmCaps_PowewPwaySuppowt);

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_VEGA10_PP_PWATFOWM_CAP_SBIOSPOWEWSOUWCE),
			PHM_PwatfowmCaps_BiosPowewSouwceContwow);

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_VEGA10_PP_PWATFOWM_CAP_HAWDWAWEDC),
			PHM_PwatfowmCaps_AutomaticDCTwansition);

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_VEGA10_PP_PWATFOWM_CAP_BACO),
			PHM_PwatfowmCaps_BACO);

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_VEGA10_PP_PWATFOWM_COMBINE_PCC_WITH_THEWMAW_SIGNAW),
			PHM_PwatfowmCaps_CombinePCCWithThewmawSignaw);

	wetuwn 0;
}

static int init_thewmaw_contwowwew(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Vega10_POWEWPWAYTABWE *powewpway_tabwe)
{
	const ATOM_Vega10_Thewmaw_Contwowwew *thewmaw_contwowwew;
	const Vega10_PPTabwe_Genewic_SubTabwe_Headew *headew;
	const ATOM_Vega10_Fan_Tabwe *fan_tabwe_v1;
	const ATOM_Vega10_Fan_Tabwe_V2 *fan_tabwe_v2;
	const ATOM_Vega10_Fan_Tabwe_V3 *fan_tabwe_v3;

	thewmaw_contwowwew = (ATOM_Vega10_Thewmaw_Contwowwew *)
			(((unsigned wong)powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usThewmawContwowwewOffset));

	PP_ASSEWT_WITH_CODE((powewpway_tabwe->usThewmawContwowwewOffset != 0),
			"Thewmaw contwowwew tabwe not set!", wetuwn -EINVAW);

	hwmgw->thewmaw_contwowwew.ucType = thewmaw_contwowwew->ucType;
	hwmgw->thewmaw_contwowwew.ucI2cWine = thewmaw_contwowwew->ucI2cWine;
	hwmgw->thewmaw_contwowwew.ucI2cAddwess = thewmaw_contwowwew->ucI2cAddwess;

	hwmgw->thewmaw_contwowwew.fanInfo.bNoFan =
			(0 != (thewmaw_contwowwew->ucFanPawametews &
			ATOM_VEGA10_PP_FANPAWAMETEWS_NOFAN));

	hwmgw->thewmaw_contwowwew.fanInfo.ucTachometewPuwsesPewWevowution =
			thewmaw_contwowwew->ucFanPawametews &
			ATOM_VEGA10_PP_FANPAWAMETEWS_TACHOMETEW_PUWSES_PEW_WEVOWUTION_MASK;

	hwmgw->thewmaw_contwowwew.fanInfo.uwMinWPM =
			thewmaw_contwowwew->ucFanMinWPM * 100UW;
	hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM =
			thewmaw_contwowwew->ucFanMaxWPM * 100UW;

	hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwCycweDeway
			= 100000;

	set_hw_cap(
			hwmgw,
			ATOM_VEGA10_PP_THEWMAWCONTWOWWEW_NONE != hwmgw->thewmaw_contwowwew.ucType,
			PHM_PwatfowmCaps_ThewmawContwowwew);

	if (!powewpway_tabwe->usFanTabweOffset)
		wetuwn 0;

	headew = (const Vega10_PPTabwe_Genewic_SubTabwe_Headew *)
			(((unsigned wong)powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usFanTabweOffset));

	if (headew->ucWevId == 10) {
		fan_tabwe_v1 = (ATOM_Vega10_Fan_Tabwe *)headew;

		PP_ASSEWT_WITH_CODE((fan_tabwe_v1->ucWevId >= 8),
				"Invawid Input Fan Tabwe!", wetuwn -EINVAW);

		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_MicwocodeFanContwow);

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity =
				we16_to_cpu(fan_tabwe_v1->usFanOutputSensitivity);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usMaxFanWPM =
				we16_to_cpu(fan_tabwe_v1->usFanWPMMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanWPMMaxWimit =
				we16_to_cpu(fan_tabwe_v1->usThwottwingWPM);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwMinFanSCWKAcousticWimit =
				we16_to_cpu(fan_tabwe_v1->usFanAcousticWimit);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax =
				we16_to_cpu(fan_tabwe_v1->usTawgetTempewatuwe);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin =
				we16_to_cpu(fan_tabwe_v1->usMinimumPWMWimit);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwTawgetGfxCwk =
				we16_to_cpu(fan_tabwe_v1->usTawgetGfxCwk);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainEdge =
				we16_to_cpu(fan_tabwe_v1->usFanGainEdge);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHotspot =
				we16_to_cpu(fan_tabwe_v1->usFanGainHotspot);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainWiquid =
				we16_to_cpu(fan_tabwe_v1->usFanGainWiquid);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwVddc =
				we16_to_cpu(fan_tabwe_v1->usFanGainVwVddc);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwMvdd =
				we16_to_cpu(fan_tabwe_v1->usFanGainVwMvdd);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainPwx =
				we16_to_cpu(fan_tabwe_v1->usFanGainPwx);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHbm =
				we16_to_cpu(fan_tabwe_v1->usFanGainHbm);

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucEnabweZewoWPM =
				fan_tabwe_v1->ucEnabweZewoWPM;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usZewoWPMStopTempewatuwe =
				we16_to_cpu(fan_tabwe_v1->usFanStopTempewatuwe);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usZewoWPMStawtTempewatuwe =
				we16_to_cpu(fan_tabwe_v1->usFanStawtTempewatuwe);
	} ewse if (headew->ucWevId == 0xb) {
		fan_tabwe_v2 = (ATOM_Vega10_Fan_Tabwe_V2 *)headew;

		hwmgw->thewmaw_contwowwew.fanInfo.ucTachometewPuwsesPewWevowution =
				fan_tabwe_v2->ucFanPawametews & ATOM_VEGA10_PP_FANPAWAMETEWS_TACHOMETEW_PUWSES_PEW_WEVOWUTION_MASK;
		hwmgw->thewmaw_contwowwew.fanInfo.uwMinWPM = fan_tabwe_v2->ucFanMinWPM * 100UW;
		hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM = fan_tabwe_v2->ucFanMaxWPM * 100UW;
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_MicwocodeFanContwow);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity =
				we16_to_cpu(fan_tabwe_v2->usFanOutputSensitivity);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usMaxFanWPM =
				fan_tabwe_v2->ucFanMaxWPM * 100UW;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanWPMMaxWimit =
				we16_to_cpu(fan_tabwe_v2->usThwottwingWPM);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwMinFanSCWKAcousticWimit =
				we16_to_cpu(fan_tabwe_v2->usFanAcousticWimitWpm);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax =
				we16_to_cpu(fan_tabwe_v2->usTawgetTempewatuwe);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin =
				we16_to_cpu(fan_tabwe_v2->usMinimumPWMWimit);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwTawgetGfxCwk =
				we16_to_cpu(fan_tabwe_v2->usTawgetGfxCwk);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainEdge =
				we16_to_cpu(fan_tabwe_v2->usFanGainEdge);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHotspot =
				we16_to_cpu(fan_tabwe_v2->usFanGainHotspot);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainWiquid =
				we16_to_cpu(fan_tabwe_v2->usFanGainWiquid);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwVddc =
				we16_to_cpu(fan_tabwe_v2->usFanGainVwVddc);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwMvdd =
				we16_to_cpu(fan_tabwe_v2->usFanGainVwMvdd);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainPwx =
				we16_to_cpu(fan_tabwe_v2->usFanGainPwx);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHbm =
				we16_to_cpu(fan_tabwe_v2->usFanGainHbm);

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucEnabweZewoWPM =
				fan_tabwe_v2->ucEnabweZewoWPM;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usZewoWPMStopTempewatuwe =
				we16_to_cpu(fan_tabwe_v2->usFanStopTempewatuwe);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usZewoWPMStawtTempewatuwe =
				we16_to_cpu(fan_tabwe_v2->usFanStawtTempewatuwe);
	} ewse if (headew->ucWevId > 0xb) {
		fan_tabwe_v3 = (ATOM_Vega10_Fan_Tabwe_V3 *)headew;

		hwmgw->thewmaw_contwowwew.fanInfo.ucTachometewPuwsesPewWevowution =
				fan_tabwe_v3->ucFanPawametews & ATOM_VEGA10_PP_FANPAWAMETEWS_TACHOMETEW_PUWSES_PEW_WEVOWUTION_MASK;
		hwmgw->thewmaw_contwowwew.fanInfo.uwMinWPM = fan_tabwe_v3->ucFanMinWPM * 100UW;
		hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM = fan_tabwe_v3->ucFanMaxWPM * 100UW;
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_MicwocodeFanContwow);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity =
				we16_to_cpu(fan_tabwe_v3->usFanOutputSensitivity);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usMaxFanWPM =
				fan_tabwe_v3->ucFanMaxWPM * 100UW;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanWPMMaxWimit =
				we16_to_cpu(fan_tabwe_v3->usThwottwingWPM);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwMinFanSCWKAcousticWimit =
				we16_to_cpu(fan_tabwe_v3->usFanAcousticWimitWpm);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax =
				we16_to_cpu(fan_tabwe_v3->usTawgetTempewatuwe);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin =
				we16_to_cpu(fan_tabwe_v3->usMinimumPWMWimit);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwTawgetGfxCwk =
				we16_to_cpu(fan_tabwe_v3->usTawgetGfxCwk);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainEdge =
				we16_to_cpu(fan_tabwe_v3->usFanGainEdge);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHotspot =
				we16_to_cpu(fan_tabwe_v3->usFanGainHotspot);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainWiquid =
				we16_to_cpu(fan_tabwe_v3->usFanGainWiquid);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwVddc =
				we16_to_cpu(fan_tabwe_v3->usFanGainVwVddc);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwMvdd =
				we16_to_cpu(fan_tabwe_v3->usFanGainVwMvdd);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainPwx =
				we16_to_cpu(fan_tabwe_v3->usFanGainPwx);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHbm =
				we16_to_cpu(fan_tabwe_v3->usFanGainHbm);

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucEnabweZewoWPM =
				fan_tabwe_v3->ucEnabweZewoWPM;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usZewoWPMStopTempewatuwe =
				we16_to_cpu(fan_tabwe_v3->usFanStopTempewatuwe);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usZewoWPMStawtTempewatuwe =
				we16_to_cpu(fan_tabwe_v3->usFanStawtTempewatuwe);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usMGpuThwottwingWPMWimit =
				we16_to_cpu(fan_tabwe_v3->usMGpuThwottwingWPM);
	}

	wetuwn 0;
}

static int init_ovew_dwive_wimits(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Vega10_POWEWPWAYTABWE *powewpway_tabwe)
{
	const ATOM_Vega10_GFXCWK_Dependency_Tabwe *gfxcwk_dep_tabwe =
			(const ATOM_Vega10_GFXCWK_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usGfxcwkDependencyTabweOffset));
	boow is_acg_enabwed = fawse;
	ATOM_Vega10_GFXCWK_Dependency_Wecowd_V2 *patom_wecowd_v2;

	if (gfxcwk_dep_tabwe->ucWevId == 1) {
		patom_wecowd_v2 =
			(ATOM_Vega10_GFXCWK_Dependency_Wecowd_V2 *)gfxcwk_dep_tabwe->entwies;
		is_acg_enabwed =
			(boow)patom_wecowd_v2[gfxcwk_dep_tabwe->ucNumEntwies-1].ucACGEnabwe;
	}

	if (powewpway_tabwe->uwMaxODEngineCwock > VEGA10_ENGINECWOCK_HAWDMAX &&
		!is_acg_enabwed)
		hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock =
			VEGA10_ENGINECWOCK_HAWDMAX;
	ewse
		hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock =
			we32_to_cpu(powewpway_tabwe->uwMaxODEngineCwock);
	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock =
			we32_to_cpu(powewpway_tabwe->uwMaxODMemowyCwock);

	hwmgw->pwatfowm_descwiptow.minOvewdwiveVDDC = 0;
	hwmgw->pwatfowm_descwiptow.maxOvewdwiveVDDC = 0;
	hwmgw->pwatfowm_descwiptow.ovewdwiveVDDCStep = 0;

	wetuwn 0;
}

static int get_mm_cwock_vowtage_tabwe(
		stwuct pp_hwmgw *hwmgw,
		phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe **vega10_mm_tabwe,
		const ATOM_Vega10_MM_Dependency_Tabwe *mm_dependency_tabwe)
{
	uint32_t i;
	const ATOM_Vega10_MM_Dependency_Wecowd *mm_dependency_wecowd;
	phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe;

	PP_ASSEWT_WITH_CODE((mm_dependency_tabwe->ucNumEntwies != 0),
			"Invawid PowewPway Tabwe!", wetuwn -1);

	mm_tabwe = kzawwoc(stwuct_size(mm_tabwe, entwies, mm_dependency_tabwe->ucNumEntwies),
			   GFP_KEWNEW);
	if (!mm_tabwe)
		wetuwn -ENOMEM;

	mm_tabwe->count = mm_dependency_tabwe->ucNumEntwies;

	fow (i = 0; i < mm_dependency_tabwe->ucNumEntwies; i++) {
		mm_dependency_wecowd = &mm_dependency_tabwe->entwies[i];
		mm_tabwe->entwies[i].vddcInd = mm_dependency_wecowd->ucVddcInd;
		mm_tabwe->entwies[i].samcwock =
				we32_to_cpu(mm_dependency_wecowd->uwPSPCwk);
		mm_tabwe->entwies[i].ecwk = we32_to_cpu(mm_dependency_wecowd->uwECwk);
		mm_tabwe->entwies[i].vcwk = we32_to_cpu(mm_dependency_wecowd->uwVCwk);
		mm_tabwe->entwies[i].dcwk = we32_to_cpu(mm_dependency_wecowd->uwDCwk);
	}

	*vega10_mm_tabwe = mm_tabwe;

	wetuwn 0;
}

static void get_scw_sda_vawue(uint8_t wine, uint8_t *scw, uint8_t *sda)
{
	switch (wine) {
	case Vega10_I2CWineID_DDC1:
		*scw = Vega10_I2C_DDC1CWK;
		*sda = Vega10_I2C_DDC1DATA;
		bweak;
	case Vega10_I2CWineID_DDC2:
		*scw = Vega10_I2C_DDC2CWK;
		*sda = Vega10_I2C_DDC2DATA;
		bweak;
	case Vega10_I2CWineID_DDC3:
		*scw = Vega10_I2C_DDC3CWK;
		*sda = Vega10_I2C_DDC3DATA;
		bweak;
	case Vega10_I2CWineID_DDC4:
		*scw = Vega10_I2C_DDC4CWK;
		*sda = Vega10_I2C_DDC4DATA;
		bweak;
	case Vega10_I2CWineID_DDC5:
		*scw = Vega10_I2C_DDC5CWK;
		*sda = Vega10_I2C_DDC5DATA;
		bweak;
	case Vega10_I2CWineID_DDC6:
		*scw = Vega10_I2C_DDC6CWK;
		*sda = Vega10_I2C_DDC6DATA;
		bweak;
	case Vega10_I2CWineID_SCWSDA:
		*scw = Vega10_I2C_SCW;
		*sda = Vega10_I2C_SDA;
		bweak;
	case Vega10_I2CWineID_DDCVGA:
		*scw = Vega10_I2C_DDCVGACWK;
		*sda = Vega10_I2C_DDCVGADATA;
		bweak;
	defauwt:
		*scw = 0;
		*sda = 0;
		bweak;
	}
}

static int get_tdp_tabwe(
		stwuct pp_hwmgw *hwmgw,
		stwuct phm_tdp_tabwe **info_tdp_tabwe,
		const Vega10_PPTabwe_Genewic_SubTabwe_Headew *tabwe)
{
	uint32_t tabwe_size;
	stwuct phm_tdp_tabwe *tdp_tabwe;
	uint8_t scw;
	uint8_t sda;
	const ATOM_Vega10_PowewTune_Tabwe *powew_tune_tabwe;
	const ATOM_Vega10_PowewTune_Tabwe_V2 *powew_tune_tabwe_v2;
	const ATOM_Vega10_PowewTune_Tabwe_V3 *powew_tune_tabwe_v3;

	tabwe_size = sizeof(uint32_t) + sizeof(stwuct phm_tdp_tabwe);

	tdp_tabwe = kzawwoc(tabwe_size, GFP_KEWNEW);

	if (!tdp_tabwe)
		wetuwn -ENOMEM;

	if (tabwe->ucWevId == 5) {
		powew_tune_tabwe = (ATOM_Vega10_PowewTune_Tabwe *)tabwe;
		tdp_tabwe->usMaximumPowewDewivewyWimit = we16_to_cpu(powew_tune_tabwe->usSocketPowewWimit);
		tdp_tabwe->usTDC = we16_to_cpu(powew_tune_tabwe->usTdcWimit);
		tdp_tabwe->usEDCWimit = we16_to_cpu(powew_tune_tabwe->usEdcWimit);
		tdp_tabwe->usSoftwaweShutdownTemp =
				we16_to_cpu(powew_tune_tabwe->usSoftwaweShutdownTemp);
		tdp_tabwe->usTempewatuweWimitTedge =
				we16_to_cpu(powew_tune_tabwe->usTempewatuweWimitTedge);
		tdp_tabwe->usTempewatuweWimitHotspot =
				we16_to_cpu(powew_tune_tabwe->usTempewatuweWimitHotSpot);
		tdp_tabwe->usTempewatuweWimitWiquid1 =
				we16_to_cpu(powew_tune_tabwe->usTempewatuweWimitWiquid1);
		tdp_tabwe->usTempewatuweWimitWiquid2 =
				we16_to_cpu(powew_tune_tabwe->usTempewatuweWimitWiquid2);
		tdp_tabwe->usTempewatuweWimitHBM =
				we16_to_cpu(powew_tune_tabwe->usTempewatuweWimitHBM);
		tdp_tabwe->usTempewatuweWimitVwVddc =
				we16_to_cpu(powew_tune_tabwe->usTempewatuweWimitVwSoc);
		tdp_tabwe->usTempewatuweWimitVwMvdd =
				we16_to_cpu(powew_tune_tabwe->usTempewatuweWimitVwMem);
		tdp_tabwe->usTempewatuweWimitPwx =
				we16_to_cpu(powew_tune_tabwe->usTempewatuweWimitPwx);
		tdp_tabwe->ucWiquid1_I2C_addwess = powew_tune_tabwe->ucWiquid1_I2C_addwess;
		tdp_tabwe->ucWiquid2_I2C_addwess = powew_tune_tabwe->ucWiquid2_I2C_addwess;
		tdp_tabwe->ucWiquid_I2C_Wine = powew_tune_tabwe->ucWiquid_I2C_WineSCW;
		tdp_tabwe->ucWiquid_I2C_WineSDA = powew_tune_tabwe->ucWiquid_I2C_WineSDA;
		tdp_tabwe->ucVw_I2C_addwess = powew_tune_tabwe->ucVw_I2C_addwess;
		tdp_tabwe->ucVw_I2C_Wine = powew_tune_tabwe->ucVw_I2C_WineSCW;
		tdp_tabwe->ucVw_I2C_WineSDA = powew_tune_tabwe->ucVw_I2C_WineSDA;
		tdp_tabwe->ucPwx_I2C_addwess = powew_tune_tabwe->ucPwx_I2C_addwess;
		tdp_tabwe->ucPwx_I2C_Wine = powew_tune_tabwe->ucPwx_I2C_WineSCW;
		tdp_tabwe->ucPwx_I2C_WineSDA = powew_tune_tabwe->ucPwx_I2C_WineSDA;
		hwmgw->pwatfowm_descwiptow.WoadWineSwope = we16_to_cpu(powew_tune_tabwe->usWoadWineWesistance);
	} ewse if (tabwe->ucWevId == 6) {
		powew_tune_tabwe_v2 = (ATOM_Vega10_PowewTune_Tabwe_V2 *)tabwe;
		tdp_tabwe->usMaximumPowewDewivewyWimit = we16_to_cpu(powew_tune_tabwe_v2->usSocketPowewWimit);
		tdp_tabwe->usTDC = we16_to_cpu(powew_tune_tabwe_v2->usTdcWimit);
		tdp_tabwe->usEDCWimit = we16_to_cpu(powew_tune_tabwe_v2->usEdcWimit);
		tdp_tabwe->usSoftwaweShutdownTemp =
				we16_to_cpu(powew_tune_tabwe_v2->usSoftwaweShutdownTemp);
		tdp_tabwe->usTempewatuweWimitTedge =
				we16_to_cpu(powew_tune_tabwe_v2->usTempewatuweWimitTedge);
		tdp_tabwe->usTempewatuweWimitHotspot =
				we16_to_cpu(powew_tune_tabwe_v2->usTempewatuweWimitHotSpot);
		tdp_tabwe->usTempewatuweWimitWiquid1 =
				we16_to_cpu(powew_tune_tabwe_v2->usTempewatuweWimitWiquid1);
		tdp_tabwe->usTempewatuweWimitWiquid2 =
				we16_to_cpu(powew_tune_tabwe_v2->usTempewatuweWimitWiquid2);
		tdp_tabwe->usTempewatuweWimitHBM =
				we16_to_cpu(powew_tune_tabwe_v2->usTempewatuweWimitHBM);
		tdp_tabwe->usTempewatuweWimitVwVddc =
				we16_to_cpu(powew_tune_tabwe_v2->usTempewatuweWimitVwSoc);
		tdp_tabwe->usTempewatuweWimitVwMvdd =
				we16_to_cpu(powew_tune_tabwe_v2->usTempewatuweWimitVwMem);
		tdp_tabwe->usTempewatuweWimitPwx =
				we16_to_cpu(powew_tune_tabwe_v2->usTempewatuweWimitPwx);
		tdp_tabwe->ucWiquid1_I2C_addwess = powew_tune_tabwe_v2->ucWiquid1_I2C_addwess;
		tdp_tabwe->ucWiquid2_I2C_addwess = powew_tune_tabwe_v2->ucWiquid2_I2C_addwess;

		get_scw_sda_vawue(powew_tune_tabwe_v2->ucWiquid_I2C_Wine, &scw, &sda);

		tdp_tabwe->ucWiquid_I2C_Wine = scw;
		tdp_tabwe->ucWiquid_I2C_WineSDA = sda;

		tdp_tabwe->ucVw_I2C_addwess = powew_tune_tabwe_v2->ucVw_I2C_addwess;

		get_scw_sda_vawue(powew_tune_tabwe_v2->ucVw_I2C_Wine, &scw, &sda);

		tdp_tabwe->ucVw_I2C_Wine = scw;
		tdp_tabwe->ucVw_I2C_WineSDA = sda;
		tdp_tabwe->ucPwx_I2C_addwess = powew_tune_tabwe_v2->ucPwx_I2C_addwess;

		get_scw_sda_vawue(powew_tune_tabwe_v2->ucPwx_I2C_Wine, &scw, &sda);

		tdp_tabwe->ucPwx_I2C_Wine = scw;
		tdp_tabwe->ucPwx_I2C_WineSDA = sda;

		hwmgw->pwatfowm_descwiptow.WoadWineSwope =
					we16_to_cpu(powew_tune_tabwe_v2->usWoadWineWesistance);
	} ewse {
		powew_tune_tabwe_v3 = (ATOM_Vega10_PowewTune_Tabwe_V3 *)tabwe;
		tdp_tabwe->usMaximumPowewDewivewyWimit   = we16_to_cpu(powew_tune_tabwe_v3->usSocketPowewWimit);
		tdp_tabwe->usTDC                         = we16_to_cpu(powew_tune_tabwe_v3->usTdcWimit);
		tdp_tabwe->usEDCWimit                    = we16_to_cpu(powew_tune_tabwe_v3->usEdcWimit);
		tdp_tabwe->usSoftwaweShutdownTemp        = we16_to_cpu(powew_tune_tabwe_v3->usSoftwaweShutdownTemp);
		tdp_tabwe->usTempewatuweWimitTedge       = we16_to_cpu(powew_tune_tabwe_v3->usTempewatuweWimitTedge);
		tdp_tabwe->usTempewatuweWimitHotspot     = we16_to_cpu(powew_tune_tabwe_v3->usTempewatuweWimitHotSpot);
		tdp_tabwe->usTempewatuweWimitWiquid1     = we16_to_cpu(powew_tune_tabwe_v3->usTempewatuweWimitWiquid1);
		tdp_tabwe->usTempewatuweWimitWiquid2     = we16_to_cpu(powew_tune_tabwe_v3->usTempewatuweWimitWiquid2);
		tdp_tabwe->usTempewatuweWimitHBM         = we16_to_cpu(powew_tune_tabwe_v3->usTempewatuweWimitHBM);
		tdp_tabwe->usTempewatuweWimitVwVddc      = we16_to_cpu(powew_tune_tabwe_v3->usTempewatuweWimitVwSoc);
		tdp_tabwe->usTempewatuweWimitVwMvdd      = we16_to_cpu(powew_tune_tabwe_v3->usTempewatuweWimitVwMem);
		tdp_tabwe->usTempewatuweWimitPwx         = we16_to_cpu(powew_tune_tabwe_v3->usTempewatuweWimitPwx);
		tdp_tabwe->ucWiquid1_I2C_addwess         = powew_tune_tabwe_v3->ucWiquid1_I2C_addwess;
		tdp_tabwe->ucWiquid2_I2C_addwess         = powew_tune_tabwe_v3->ucWiquid2_I2C_addwess;
		tdp_tabwe->usBoostStawtTempewatuwe       = we16_to_cpu(powew_tune_tabwe_v3->usBoostStawtTempewatuwe);
		tdp_tabwe->usBoostStopTempewatuwe        = we16_to_cpu(powew_tune_tabwe_v3->usBoostStopTempewatuwe);
		tdp_tabwe->uwBoostCwock                  = we32_to_cpu(powew_tune_tabwe_v3->uwBoostCwock);

		get_scw_sda_vawue(powew_tune_tabwe_v3->ucWiquid_I2C_Wine, &scw, &sda);

		tdp_tabwe->ucWiquid_I2C_Wine             = scw;
		tdp_tabwe->ucWiquid_I2C_WineSDA          = sda;

		tdp_tabwe->ucVw_I2C_addwess              = powew_tune_tabwe_v3->ucVw_I2C_addwess;

		get_scw_sda_vawue(powew_tune_tabwe_v3->ucVw_I2C_Wine, &scw, &sda);

		tdp_tabwe->ucVw_I2C_Wine                 = scw;
		tdp_tabwe->ucVw_I2C_WineSDA              = sda;

		tdp_tabwe->ucPwx_I2C_addwess             = powew_tune_tabwe_v3->ucPwx_I2C_addwess;

		get_scw_sda_vawue(powew_tune_tabwe_v3->ucPwx_I2C_Wine, &scw, &sda);

		tdp_tabwe->ucPwx_I2C_Wine                = scw;
		tdp_tabwe->ucPwx_I2C_WineSDA             = sda;

		hwmgw->pwatfowm_descwiptow.WoadWineSwope =
					we16_to_cpu(powew_tune_tabwe_v3->usWoadWineWesistance);
	}

	*info_tdp_tabwe = tdp_tabwe;

	wetuwn 0;
}

static int get_soccwk_vowtage_dependency_tabwe(
		stwuct pp_hwmgw *hwmgw,
		phm_ppt_v1_cwock_vowtage_dependency_tabwe **pp_vega10_cwk_dep_tabwe,
		const ATOM_Vega10_SOCCWK_Dependency_Tabwe *cwk_dep_tabwe)
{
	uint32_t i;
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *cwk_tabwe;

	PP_ASSEWT_WITH_CODE(cwk_dep_tabwe->ucNumEntwies,
		"Invawid PowewPway Tabwe!", wetuwn -1);

	cwk_tabwe = kzawwoc(stwuct_size(cwk_tabwe, entwies, cwk_dep_tabwe->ucNumEntwies),
			    GFP_KEWNEW);
	if (!cwk_tabwe)
		wetuwn -ENOMEM;

	cwk_tabwe->count = (uint32_t)cwk_dep_tabwe->ucNumEntwies;

	fow (i = 0; i < cwk_dep_tabwe->ucNumEntwies; i++) {
		cwk_tabwe->entwies[i].vddInd =
				cwk_dep_tabwe->entwies[i].ucVddInd;
		cwk_tabwe->entwies[i].cwk =
				we32_to_cpu(cwk_dep_tabwe->entwies[i].uwCwk);
	}

	*pp_vega10_cwk_dep_tabwe = cwk_tabwe;

	wetuwn 0;
}

static int get_mcwk_vowtage_dependency_tabwe(
		stwuct pp_hwmgw *hwmgw,
		phm_ppt_v1_cwock_vowtage_dependency_tabwe **pp_vega10_mcwk_dep_tabwe,
		const ATOM_Vega10_MCWK_Dependency_Tabwe *mcwk_dep_tabwe)
{
	uint32_t i;
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *mcwk_tabwe;

	PP_ASSEWT_WITH_CODE(mcwk_dep_tabwe->ucNumEntwies,
		"Invawid PowewPway Tabwe!", wetuwn -1);

	mcwk_tabwe = kzawwoc(stwuct_size(mcwk_tabwe, entwies, mcwk_dep_tabwe->ucNumEntwies),
			    GFP_KEWNEW);
	if (!mcwk_tabwe)
		wetuwn -ENOMEM;

	mcwk_tabwe->count = (uint32_t)mcwk_dep_tabwe->ucNumEntwies;

	fow (i = 0; i < mcwk_dep_tabwe->ucNumEntwies; i++) {
		mcwk_tabwe->entwies[i].vddInd =
				mcwk_dep_tabwe->entwies[i].ucVddInd;
		mcwk_tabwe->entwies[i].vddciInd =
				mcwk_dep_tabwe->entwies[i].ucVddciInd;
		mcwk_tabwe->entwies[i].mvddInd =
				mcwk_dep_tabwe->entwies[i].ucVddMemInd;
		mcwk_tabwe->entwies[i].cwk =
				we32_to_cpu(mcwk_dep_tabwe->entwies[i].uwMemCwk);
	}

	*pp_vega10_mcwk_dep_tabwe = mcwk_tabwe;

	wetuwn 0;
}

static int get_gfxcwk_vowtage_dependency_tabwe(
		stwuct pp_hwmgw *hwmgw,
		stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe
			**pp_vega10_cwk_dep_tabwe,
		const ATOM_Vega10_GFXCWK_Dependency_Tabwe *cwk_dep_tabwe)
{
	uint32_t i;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe
				*cwk_tabwe;
	ATOM_Vega10_GFXCWK_Dependency_Wecowd_V2 *patom_wecowd_v2;

	PP_ASSEWT_WITH_CODE((cwk_dep_tabwe->ucNumEntwies != 0),
			"Invawid PowewPway Tabwe!", wetuwn -1);

	cwk_tabwe = kzawwoc(stwuct_size(cwk_tabwe, entwies, cwk_dep_tabwe->ucNumEntwies),
			    GFP_KEWNEW);
	if (!cwk_tabwe)
		wetuwn -ENOMEM;

	cwk_tabwe->count = cwk_dep_tabwe->ucNumEntwies;

	if (cwk_dep_tabwe->ucWevId == 0) {
		fow (i = 0; i < cwk_tabwe->count; i++) {
			cwk_tabwe->entwies[i].vddInd =
				cwk_dep_tabwe->entwies[i].ucVddInd;
			cwk_tabwe->entwies[i].cwk =
				we32_to_cpu(cwk_dep_tabwe->entwies[i].uwCwk);
			cwk_tabwe->entwies[i].cks_enabwe =
				(((we16_to_cpu(cwk_dep_tabwe->entwies[i].usCKSVOffsetandDisabwe) & 0x8000)
						>> 15) == 0) ? 1 : 0;
			cwk_tabwe->entwies[i].cks_voffset =
				we16_to_cpu(cwk_dep_tabwe->entwies[i].usCKSVOffsetandDisabwe) & 0x7F;
			cwk_tabwe->entwies[i].scwk_offset =
				we16_to_cpu(cwk_dep_tabwe->entwies[i].usAVFSOffset);
		}
	} ewse if (cwk_dep_tabwe->ucWevId == 1) {
		patom_wecowd_v2 = (ATOM_Vega10_GFXCWK_Dependency_Wecowd_V2 *)cwk_dep_tabwe->entwies;
		fow (i = 0; i < cwk_tabwe->count; i++) {
			cwk_tabwe->entwies[i].vddInd =
					patom_wecowd_v2->ucVddInd;
			cwk_tabwe->entwies[i].cwk =
					we32_to_cpu(patom_wecowd_v2->uwCwk);
			cwk_tabwe->entwies[i].cks_enabwe =
					(((we16_to_cpu(patom_wecowd_v2->usCKSVOffsetandDisabwe) & 0x8000)
							>> 15) == 0) ? 1 : 0;
			cwk_tabwe->entwies[i].cks_voffset =
					we16_to_cpu(patom_wecowd_v2->usCKSVOffsetandDisabwe) & 0x7F;
			cwk_tabwe->entwies[i].scwk_offset =
					we16_to_cpu(patom_wecowd_v2->usAVFSOffset);
			patom_wecowd_v2++;
		}
	} ewse {
		kfwee(cwk_tabwe);
		PP_ASSEWT_WITH_CODE(fawse,
			"Unsuppowted GFXCwockDependencyTabwe Wevision!",
			wetuwn -EINVAW);
	}

	*pp_vega10_cwk_dep_tabwe = cwk_tabwe;

	wetuwn 0;
}

static int get_pix_cwk_vowtage_dependency_tabwe(
		stwuct pp_hwmgw *hwmgw,
		stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe
			**pp_vega10_cwk_dep_tabwe,
		const  ATOM_Vega10_PIXCWK_Dependency_Tabwe *cwk_dep_tabwe)
{
	uint32_t i;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe
				*cwk_tabwe;

	PP_ASSEWT_WITH_CODE((cwk_dep_tabwe->ucNumEntwies != 0),
			"Invawid PowewPway Tabwe!", wetuwn -1);

	cwk_tabwe = kzawwoc(stwuct_size(cwk_tabwe, entwies, cwk_dep_tabwe->ucNumEntwies),
			    GFP_KEWNEW);
	if (!cwk_tabwe)
		wetuwn -ENOMEM;

	cwk_tabwe->count = cwk_dep_tabwe->ucNumEntwies;

	fow (i = 0; i < cwk_tabwe->count; i++) {
		cwk_tabwe->entwies[i].vddInd =
				cwk_dep_tabwe->entwies[i].ucVddInd;
		cwk_tabwe->entwies[i].cwk =
				we32_to_cpu(cwk_dep_tabwe->entwies[i].uwCwk);
	}

	*pp_vega10_cwk_dep_tabwe = cwk_tabwe;

	wetuwn 0;
}

static int get_dcefcwk_vowtage_dependency_tabwe(
		stwuct pp_hwmgw *hwmgw,
		stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe
			**pp_vega10_cwk_dep_tabwe,
		const ATOM_Vega10_DCEFCWK_Dependency_Tabwe *cwk_dep_tabwe)
{
	uint32_t i;
	uint8_t num_entwies;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe
				*cwk_tabwe;
	uint32_t dev_id;
	uint32_t wev_id;
	stwuct amdgpu_device *adev = hwmgw->adev;

	PP_ASSEWT_WITH_CODE((cwk_dep_tabwe->ucNumEntwies != 0),
			"Invawid PowewPway Tabwe!", wetuwn -1);

/*
 * wowkawound needed to add anothew DPM wevew fow pioneew cawds
 * as VBIOS is wocked down.
 * This DPM wevew was added to suppowt 3DPM monitows @ 4K120Hz
 *
 */
	dev_id = adev->pdev->device;
	wev_id = adev->pdev->wevision;

	if (dev_id == 0x6863 && wev_id == 0 &&
		cwk_dep_tabwe->entwies[cwk_dep_tabwe->ucNumEntwies - 1].uwCwk < 90000)
		num_entwies = cwk_dep_tabwe->ucNumEntwies + 1 > NUM_DSPCWK_WEVEWS ?
				NUM_DSPCWK_WEVEWS : cwk_dep_tabwe->ucNumEntwies + 1;
	ewse
		num_entwies = cwk_dep_tabwe->ucNumEntwies;


	cwk_tabwe = kzawwoc(stwuct_size(cwk_tabwe, entwies, num_entwies),
			    GFP_KEWNEW);
	if (!cwk_tabwe)
		wetuwn -ENOMEM;

	cwk_tabwe->count = (uint32_t)num_entwies;

	fow (i = 0; i < cwk_dep_tabwe->ucNumEntwies; i++) {
		cwk_tabwe->entwies[i].vddInd =
				cwk_dep_tabwe->entwies[i].ucVddInd;
		cwk_tabwe->entwies[i].cwk =
				we32_to_cpu(cwk_dep_tabwe->entwies[i].uwCwk);
	}

	if (i < num_entwies) {
		cwk_tabwe->entwies[i].vddInd = cwk_dep_tabwe->entwies[i-1].ucVddInd;
		cwk_tabwe->entwies[i].cwk = 90000;
	}

	*pp_vega10_cwk_dep_tabwe = cwk_tabwe;

	wetuwn 0;
}

static int get_pcie_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct phm_ppt_v1_pcie_tabwe **vega10_pcie_tabwe,
		const Vega10_PPTabwe_Genewic_SubTabwe_Headew *tabwe)
{
	uint32_t i, pcie_count;
	stwuct phm_ppt_v1_pcie_tabwe *pcie_tabwe;
	stwuct phm_ppt_v2_infowmation *tabwe_info =
			(stwuct phm_ppt_v2_infowmation *)(hwmgw->pptabwe);
	const ATOM_Vega10_PCIE_Tabwe *atom_pcie_tabwe =
			(ATOM_Vega10_PCIE_Tabwe *)tabwe;

	PP_ASSEWT_WITH_CODE(atom_pcie_tabwe->ucNumEntwies,
			"Invawid PowewPway Tabwe!",
			wetuwn 0);

	pcie_tabwe = kzawwoc(stwuct_size(pcie_tabwe, entwies, atom_pcie_tabwe->ucNumEntwies),
			     GFP_KEWNEW);
	if (!pcie_tabwe)
		wetuwn -ENOMEM;

	pcie_count = tabwe_info->vdd_dep_on_scwk->count;
	if (atom_pcie_tabwe->ucNumEntwies <= pcie_count)
		pcie_count = atom_pcie_tabwe->ucNumEntwies;
	ewse
		pw_info("Numbew of Pcie Entwies exceed the numbew of"
				" GFXCWK Dpm Wevews!"
				" Diswegawding the excess entwies...\n");

	pcie_tabwe->count = pcie_count;

	fow (i = 0; i < pcie_count; i++) {
		pcie_tabwe->entwies[i].gen_speed =
				atom_pcie_tabwe->entwies[i].ucPCIEGenSpeed;
		pcie_tabwe->entwies[i].wane_width =
				atom_pcie_tabwe->entwies[i].ucPCIEWaneWidth;
		pcie_tabwe->entwies[i].pcie_scwk =
				atom_pcie_tabwe->entwies[i].uwWCWK;
	}

	*vega10_pcie_tabwe = pcie_tabwe;

	wetuwn 0;
}

static int get_hawd_wimits(
		stwuct pp_hwmgw *hwmgw,
		stwuct phm_cwock_and_vowtage_wimits *wimits,
		const ATOM_Vega10_Hawd_Wimit_Tabwe *wimit_tabwe)
{
	PP_ASSEWT_WITH_CODE(wimit_tabwe->ucNumEntwies,
			"Invawid PowewPway Tabwe!", wetuwn -1);

	/* cuwwentwy we awways take entwies[0] pawametews */
	wimits->scwk = we32_to_cpu(wimit_tabwe->entwies[0].uwSOCCWKWimit);
	wimits->mcwk = we32_to_cpu(wimit_tabwe->entwies[0].uwMCWKWimit);
	wimits->gfxcwk = we32_to_cpu(wimit_tabwe->entwies[0].uwGFXCWKWimit);
	wimits->vddc = we16_to_cpu(wimit_tabwe->entwies[0].usVddcWimit);
	wimits->vddci = we16_to_cpu(wimit_tabwe->entwies[0].usVddciWimit);
	wimits->vddmem = we16_to_cpu(wimit_tabwe->entwies[0].usVddMemWimit);

	wetuwn 0;
}

static int get_vawid_cwk(
		stwuct pp_hwmgw *hwmgw,
		stwuct phm_cwock_awway **cwk_tabwe,
		const phm_ppt_v1_cwock_vowtage_dependency_tabwe *cwk_vowt_pp_tabwe)
{
	uint32_t i;
	stwuct phm_cwock_awway *tabwe;

	PP_ASSEWT_WITH_CODE(cwk_vowt_pp_tabwe->count,
			"Invawid PowewPway Tabwe!", wetuwn -1);

	tabwe = kzawwoc(stwuct_size(tabwe, vawues, cwk_vowt_pp_tabwe->count),
			GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	tabwe->count = (uint32_t)cwk_vowt_pp_tabwe->count;

	fow (i = 0; i < tabwe->count; i++)
		tabwe->vawues[i] = (uint32_t)cwk_vowt_pp_tabwe->entwies[i].cwk;

	*cwk_tabwe = tabwe;

	wetuwn 0;
}

static int init_powewpway_extended_tabwes(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Vega10_POWEWPWAYTABWE *powewpway_tabwe)
{
	int wesuwt = 0;
	stwuct phm_ppt_v2_infowmation *pp_tabwe_info =
		(stwuct phm_ppt_v2_infowmation *)(hwmgw->pptabwe);

	const ATOM_Vega10_MM_Dependency_Tabwe *mm_dependency_tabwe =
			(const ATOM_Vega10_MM_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usMMDependencyTabweOffset));
	const Vega10_PPTabwe_Genewic_SubTabwe_Headew *powew_tune_tabwe =
			(const Vega10_PPTabwe_Genewic_SubTabwe_Headew *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usPowewTuneTabweOffset));
	const ATOM_Vega10_SOCCWK_Dependency_Tabwe *soccwk_dep_tabwe =
			(const ATOM_Vega10_SOCCWK_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usSoccwkDependencyTabweOffset));
	const ATOM_Vega10_GFXCWK_Dependency_Tabwe *gfxcwk_dep_tabwe =
			(const ATOM_Vega10_GFXCWK_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usGfxcwkDependencyTabweOffset));
	const ATOM_Vega10_DCEFCWK_Dependency_Tabwe *dcefcwk_dep_tabwe =
			(const ATOM_Vega10_DCEFCWK_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usDcefcwkDependencyTabweOffset));
	const ATOM_Vega10_MCWK_Dependency_Tabwe *mcwk_dep_tabwe =
			(const ATOM_Vega10_MCWK_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usMcwkDependencyTabweOffset));
	const ATOM_Vega10_Hawd_Wimit_Tabwe *hawd_wimits =
			(const ATOM_Vega10_Hawd_Wimit_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usHawdWimitTabweOffset));
	const Vega10_PPTabwe_Genewic_SubTabwe_Headew *pcie_tabwe =
			(const Vega10_PPTabwe_Genewic_SubTabwe_Headew *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usPCIETabweOffset));
	const ATOM_Vega10_PIXCWK_Dependency_Tabwe *pixcwk_dep_tabwe =
			(const ATOM_Vega10_PIXCWK_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usPixcwkDependencyTabweOffset));
	const ATOM_Vega10_PHYCWK_Dependency_Tabwe *phycwk_dep_tabwe =
			(const ATOM_Vega10_PHYCWK_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usPhyCwkDependencyTabweOffset));
	const ATOM_Vega10_DISPCWK_Dependency_Tabwe *dispcwk_dep_tabwe =
			(const ATOM_Vega10_DISPCWK_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usDispCwkDependencyTabweOffset));

	pp_tabwe_info->vdd_dep_on_soccwk = NUWW;
	pp_tabwe_info->vdd_dep_on_scwk = NUWW;
	pp_tabwe_info->vdd_dep_on_mcwk = NUWW;
	pp_tabwe_info->vdd_dep_on_dcefcwk = NUWW;
	pp_tabwe_info->mm_dep_tabwe = NUWW;
	pp_tabwe_info->tdp_tabwe = NUWW;
	pp_tabwe_info->vdd_dep_on_pixcwk = NUWW;
	pp_tabwe_info->vdd_dep_on_phycwk = NUWW;
	pp_tabwe_info->vdd_dep_on_dispcwk = NUWW;

	if (powewpway_tabwe->usMMDependencyTabweOffset)
		wesuwt = get_mm_cwock_vowtage_tabwe(hwmgw,
				&pp_tabwe_info->mm_dep_tabwe,
				mm_dependency_tabwe);

	if (!wesuwt && powewpway_tabwe->usPowewTuneTabweOffset)
		wesuwt = get_tdp_tabwe(hwmgw,
				&pp_tabwe_info->tdp_tabwe,
				powew_tune_tabwe);

	if (!wesuwt && powewpway_tabwe->usSoccwkDependencyTabweOffset)
		wesuwt = get_soccwk_vowtage_dependency_tabwe(hwmgw,
				&pp_tabwe_info->vdd_dep_on_soccwk,
				soccwk_dep_tabwe);

	if (!wesuwt && powewpway_tabwe->usGfxcwkDependencyTabweOffset)
		wesuwt = get_gfxcwk_vowtage_dependency_tabwe(hwmgw,
				&pp_tabwe_info->vdd_dep_on_scwk,
				gfxcwk_dep_tabwe);

	if (!wesuwt && powewpway_tabwe->usPixcwkDependencyTabweOffset)
		wesuwt = get_pix_cwk_vowtage_dependency_tabwe(hwmgw,
				&pp_tabwe_info->vdd_dep_on_pixcwk,
				(const ATOM_Vega10_PIXCWK_Dependency_Tabwe *)
				pixcwk_dep_tabwe);

	if (!wesuwt && powewpway_tabwe->usPhyCwkDependencyTabweOffset)
		wesuwt = get_pix_cwk_vowtage_dependency_tabwe(hwmgw,
				&pp_tabwe_info->vdd_dep_on_phycwk,
				(const ATOM_Vega10_PIXCWK_Dependency_Tabwe *)
				phycwk_dep_tabwe);

	if (!wesuwt && powewpway_tabwe->usDispCwkDependencyTabweOffset)
		wesuwt = get_pix_cwk_vowtage_dependency_tabwe(hwmgw,
				&pp_tabwe_info->vdd_dep_on_dispcwk,
				(const ATOM_Vega10_PIXCWK_Dependency_Tabwe *)
				dispcwk_dep_tabwe);

	if (!wesuwt && powewpway_tabwe->usDcefcwkDependencyTabweOffset)
		wesuwt = get_dcefcwk_vowtage_dependency_tabwe(hwmgw,
				&pp_tabwe_info->vdd_dep_on_dcefcwk,
				dcefcwk_dep_tabwe);

	if (!wesuwt && powewpway_tabwe->usMcwkDependencyTabweOffset)
		wesuwt = get_mcwk_vowtage_dependency_tabwe(hwmgw,
				&pp_tabwe_info->vdd_dep_on_mcwk,
				mcwk_dep_tabwe);

	if (!wesuwt && powewpway_tabwe->usPCIETabweOffset)
		wesuwt = get_pcie_tabwe(hwmgw,
				&pp_tabwe_info->pcie_tabwe,
				pcie_tabwe);

	if (!wesuwt && powewpway_tabwe->usHawdWimitTabweOffset)
		wesuwt = get_hawd_wimits(hwmgw,
				&pp_tabwe_info->max_cwock_vowtage_on_dc,
				hawd_wimits);

	hwmgw->dyn_state.max_cwock_vowtage_on_dc.scwk =
			pp_tabwe_info->max_cwock_vowtage_on_dc.scwk;
	hwmgw->dyn_state.max_cwock_vowtage_on_dc.mcwk =
			pp_tabwe_info->max_cwock_vowtage_on_dc.mcwk;
	hwmgw->dyn_state.max_cwock_vowtage_on_dc.vddc =
			pp_tabwe_info->max_cwock_vowtage_on_dc.vddc;
	hwmgw->dyn_state.max_cwock_vowtage_on_dc.vddci =
			pp_tabwe_info->max_cwock_vowtage_on_dc.vddci;

	if (!wesuwt &&
		pp_tabwe_info->vdd_dep_on_soccwk &&
		pp_tabwe_info->vdd_dep_on_soccwk->count)
		wesuwt = get_vawid_cwk(hwmgw,
				&pp_tabwe_info->vawid_soccwk_vawues,
				pp_tabwe_info->vdd_dep_on_soccwk);

	if (!wesuwt &&
		pp_tabwe_info->vdd_dep_on_scwk &&
		pp_tabwe_info->vdd_dep_on_scwk->count)
		wesuwt = get_vawid_cwk(hwmgw,
				&pp_tabwe_info->vawid_scwk_vawues,
				pp_tabwe_info->vdd_dep_on_scwk);

	if (!wesuwt &&
		pp_tabwe_info->vdd_dep_on_dcefcwk &&
		pp_tabwe_info->vdd_dep_on_dcefcwk->count)
		wesuwt = get_vawid_cwk(hwmgw,
				&pp_tabwe_info->vawid_dcefcwk_vawues,
				pp_tabwe_info->vdd_dep_on_dcefcwk);

	if (!wesuwt &&
		pp_tabwe_info->vdd_dep_on_mcwk &&
		pp_tabwe_info->vdd_dep_on_mcwk->count)
		wesuwt = get_vawid_cwk(hwmgw,
				&pp_tabwe_info->vawid_mcwk_vawues,
				pp_tabwe_info->vdd_dep_on_mcwk);

	wetuwn wesuwt;
}

static int get_vddc_wookup_tabwe(
		stwuct pp_hwmgw	*hwmgw,
		phm_ppt_v1_vowtage_wookup_tabwe	**wookup_tabwe,
		const ATOM_Vega10_Vowtage_Wookup_Tabwe *vddc_wookup_pp_tabwes,
		uint32_t max_wevews)
{
	uint32_t i;
	phm_ppt_v1_vowtage_wookup_tabwe *tabwe;

	PP_ASSEWT_WITH_CODE((vddc_wookup_pp_tabwes->ucNumEntwies != 0),
			"Invawid SOC_VDDD Wookup Tabwe!", wetuwn 1);

	tabwe = kzawwoc(stwuct_size(tabwe, entwies, max_wevews), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	tabwe->count = vddc_wookup_pp_tabwes->ucNumEntwies;

	fow (i = 0; i < vddc_wookup_pp_tabwes->ucNumEntwies; i++)
		tabwe->entwies[i].us_vdd =
				we16_to_cpu(vddc_wookup_pp_tabwes->entwies[i].usVdd);

	*wookup_tabwe = tabwe;

	wetuwn 0;
}

static int init_dpm_2_pawametews(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Vega10_POWEWPWAYTABWE *powewpway_tabwe)
{
	int wesuwt = 0;
	stwuct phm_ppt_v2_infowmation *pp_tabwe_info =
			(stwuct phm_ppt_v2_infowmation *)(hwmgw->pptabwe);
	uint32_t disabwe_powew_contwow = 0;

	pp_tabwe_info->us_uwv_vowtage_offset =
		we16_to_cpu(powewpway_tabwe->usUwvVowtageOffset);

	pp_tabwe_info->us_uwv_smncwk_did =
			we16_to_cpu(powewpway_tabwe->usUwvSmncwkDid);
	pp_tabwe_info->us_uwv_mp1cwk_did =
			we16_to_cpu(powewpway_tabwe->usUwvMp1cwkDid);
	pp_tabwe_info->us_uwv_gfxcwk_bypass =
			we16_to_cpu(powewpway_tabwe->usUwvGfxcwkBypass);
	pp_tabwe_info->us_gfxcwk_swew_wate =
			we16_to_cpu(powewpway_tabwe->usGfxcwkSwewWate);
	pp_tabwe_info->uc_gfx_dpm_vowtage_mode  =
			we16_to_cpu(powewpway_tabwe->ucGfxVowtageMode);
	pp_tabwe_info->uc_soc_dpm_vowtage_mode  =
			we16_to_cpu(powewpway_tabwe->ucSocVowtageMode);
	pp_tabwe_info->uc_ucwk_dpm_vowtage_mode =
			we16_to_cpu(powewpway_tabwe->ucUcwkVowtageMode);
	pp_tabwe_info->uc_uvd_dpm_vowtage_mode  =
			we16_to_cpu(powewpway_tabwe->ucUvdVowtageMode);
	pp_tabwe_info->uc_vce_dpm_vowtage_mode  =
			we16_to_cpu(powewpway_tabwe->ucVceVowtageMode);
	pp_tabwe_info->uc_mp0_dpm_vowtage_mode  =
			we16_to_cpu(powewpway_tabwe->ucMp0VowtageMode);
	pp_tabwe_info->uc_dcef_dpm_vowtage_mode =
			we16_to_cpu(powewpway_tabwe->ucDcefVowtageMode);

	pp_tabwe_info->ppm_pawametew_tabwe = NUWW;
	pp_tabwe_info->vddc_wookup_tabwe = NUWW;
	pp_tabwe_info->vddmem_wookup_tabwe = NUWW;
	pp_tabwe_info->vddci_wookup_tabwe = NUWW;

	/* TDP wimits */
	hwmgw->pwatfowm_descwiptow.TDPODWimit =
		we16_to_cpu(powewpway_tabwe->usPowewContwowWimit);
	hwmgw->pwatfowm_descwiptow.TDPAdjustment = 0;
	hwmgw->pwatfowm_descwiptow.VidAdjustment = 0;
	hwmgw->pwatfowm_descwiptow.VidAdjustmentPowawity = 0;
	hwmgw->pwatfowm_descwiptow.VidMinWimit = 0;
	hwmgw->pwatfowm_descwiptow.VidMaxWimit = 1500000;
	hwmgw->pwatfowm_descwiptow.VidStep = 6250;

	disabwe_powew_contwow = 0;
	if (!disabwe_powew_contwow) {
		/* enabwe TDP ovewdwive (PowewContwow) featuwe as weww if suppowted */
		if (hwmgw->pwatfowm_descwiptow.TDPODWimit)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PowewContwow);
	}

	if (powewpway_tabwe->usVddcWookupTabweOffset) {
		const ATOM_Vega10_Vowtage_Wookup_Tabwe *vddc_tabwe =
				(ATOM_Vega10_Vowtage_Wookup_Tabwe *)
				(((unsigned wong)powewpway_tabwe) +
				we16_to_cpu(powewpway_tabwe->usVddcWookupTabweOffset));
		wesuwt = get_vddc_wookup_tabwe(hwmgw,
				&pp_tabwe_info->vddc_wookup_tabwe, vddc_tabwe, 8);
	}

	if (powewpway_tabwe->usVddmemWookupTabweOffset) {
		const ATOM_Vega10_Vowtage_Wookup_Tabwe *vdd_mem_tabwe =
				(ATOM_Vega10_Vowtage_Wookup_Tabwe *)
				(((unsigned wong)powewpway_tabwe) +
				we16_to_cpu(powewpway_tabwe->usVddmemWookupTabweOffset));
		wesuwt = get_vddc_wookup_tabwe(hwmgw,
				&pp_tabwe_info->vddmem_wookup_tabwe, vdd_mem_tabwe, 4);
	}

	if (powewpway_tabwe->usVddciWookupTabweOffset) {
		const ATOM_Vega10_Vowtage_Wookup_Tabwe *vddci_tabwe =
				(ATOM_Vega10_Vowtage_Wookup_Tabwe *)
				(((unsigned wong)powewpway_tabwe) +
				we16_to_cpu(powewpway_tabwe->usVddciWookupTabweOffset));
		wesuwt = get_vddc_wookup_tabwe(hwmgw,
				&pp_tabwe_info->vddci_wookup_tabwe, vddci_tabwe, 4);
	}

	wetuwn wesuwt;
}

static int vega10_pp_tabwes_initiawize(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	const ATOM_Vega10_POWEWPWAYTABWE *powewpway_tabwe;

	hwmgw->pptabwe = kzawwoc(sizeof(stwuct phm_ppt_v2_infowmation), GFP_KEWNEW);

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

	wesuwt = init_thewmaw_contwowwew(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_thewmaw_contwowwew faiwed", wetuwn wesuwt);

	wesuwt = init_ovew_dwive_wimits(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_ovew_dwive_wimits faiwed", wetuwn wesuwt);

	wesuwt = init_powewpway_extended_tabwes(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_powewpway_extended_tabwes faiwed", wetuwn wesuwt);

	wesuwt = init_dpm_2_pawametews(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_dpm_2_pawametews faiwed", wetuwn wesuwt);

	wetuwn wesuwt;
}

static int vega10_pp_tabwes_uninitiawize(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v2_infowmation *pp_tabwe_info =
			(stwuct phm_ppt_v2_infowmation *)(hwmgw->pptabwe);

	kfwee(pp_tabwe_info->vdd_dep_on_scwk);
	pp_tabwe_info->vdd_dep_on_scwk = NUWW;

	kfwee(pp_tabwe_info->vdd_dep_on_mcwk);
	pp_tabwe_info->vdd_dep_on_mcwk = NUWW;

	kfwee(pp_tabwe_info->vawid_mcwk_vawues);
	pp_tabwe_info->vawid_mcwk_vawues = NUWW;

	kfwee(pp_tabwe_info->vawid_scwk_vawues);
	pp_tabwe_info->vawid_scwk_vawues = NUWW;

	kfwee(pp_tabwe_info->vddc_wookup_tabwe);
	pp_tabwe_info->vddc_wookup_tabwe = NUWW;

	kfwee(pp_tabwe_info->vddmem_wookup_tabwe);
	pp_tabwe_info->vddmem_wookup_tabwe = NUWW;

	kfwee(pp_tabwe_info->vddci_wookup_tabwe);
	pp_tabwe_info->vddci_wookup_tabwe = NUWW;

	kfwee(pp_tabwe_info->ppm_pawametew_tabwe);
	pp_tabwe_info->ppm_pawametew_tabwe = NUWW;

	kfwee(pp_tabwe_info->mm_dep_tabwe);
	pp_tabwe_info->mm_dep_tabwe = NUWW;

	kfwee(pp_tabwe_info->cac_dtp_tabwe);
	pp_tabwe_info->cac_dtp_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.cac_dtp_tabwe);
	hwmgw->dyn_state.cac_dtp_tabwe = NUWW;

	kfwee(pp_tabwe_info->tdp_tabwe);
	pp_tabwe_info->tdp_tabwe = NUWW;

	kfwee(hwmgw->pptabwe);
	hwmgw->pptabwe = NUWW;

	wetuwn 0;
}

const stwuct pp_tabwe_func vega10_pptabwe_funcs = {
	.pptabwe_init = vega10_pp_tabwes_initiawize,
	.pptabwe_fini = vega10_pp_tabwes_uninitiawize,
};

int vega10_get_numbew_of_powewpway_tabwe_entwies(stwuct pp_hwmgw *hwmgw)
{
	const ATOM_Vega10_State_Awway *state_awways;
	const ATOM_Vega10_POWEWPWAYTABWE *pp_tabwe = get_powewpway_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE((pp_tabwe != NUWW),
			"Missing PowewPway Tabwe!", wetuwn -1);
	PP_ASSEWT_WITH_CODE((pp_tabwe->sHeadew.fowmat_wevision >=
			ATOM_Vega10_TABWE_WEVISION_VEGA10),
			"Incowwect PowewPway tabwe wevision!", wetuwn -1);

	state_awways = (ATOM_Vega10_State_Awway *)(((unsigned wong)pp_tabwe) +
			we16_to_cpu(pp_tabwe->usStateAwwayOffset));

	wetuwn (uint32_t)(state_awways->ucNumEntwies);
}

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

int vega10_get_powewpway_tabwe_entwy(stwuct pp_hwmgw *hwmgw,
		uint32_t entwy_index, stwuct pp_powew_state *powew_state,
		int (*caww_back_func)(stwuct pp_hwmgw *, void *,
				stwuct pp_powew_state *, void *, uint32_t))
{
	int wesuwt = 0;
	const ATOM_Vega10_State_Awway *state_awways;
	const ATOM_Vega10_State *state_entwy;
	const ATOM_Vega10_POWEWPWAYTABWE *pp_tabwe =
			get_powewpway_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE(pp_tabwe, "Missing PowewPway Tabwe!",
			wetuwn -1;);
	powew_state->cwassification.bios_index = entwy_index;

	if (pp_tabwe->sHeadew.fowmat_wevision >=
			ATOM_Vega10_TABWE_WEVISION_VEGA10) {
		state_awways = (ATOM_Vega10_State_Awway *)
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

int vega10_baco_set_cap(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;

	const ATOM_Vega10_POWEWPWAYTABWE *powewpway_tabwe;

	powewpway_tabwe = get_powewpway_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE((powewpway_tabwe != NUWW),
		"Missing PowewPway Tabwe!", wetuwn -1);

	wesuwt = check_powewpway_tabwes(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "check_powewpway_tabwes faiwed", wetuwn wesuwt);

	set_hw_cap(
			hwmgw,
			0 != (we32_to_cpu(powewpway_tabwe->uwPwatfowmCaps) & ATOM_VEGA10_PP_PWATFOWM_CAP_BACO),
			PHM_PwatfowmCaps_BACO);
	wetuwn wesuwt;
}

