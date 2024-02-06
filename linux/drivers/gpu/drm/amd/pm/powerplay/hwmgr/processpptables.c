/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#incwude "pp_debug.h"
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>

#incwude <dwm/amdgpu_dwm.h>
#incwude "pwocesspptabwes.h"
#incwude <atom-types.h>
#incwude <atombios.h>
#incwude "pptabwe.h"
#incwude "powew_state.h"
#incwude "hwmgw.h"
#incwude "hawdwawemanagew.h"


#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V2 12
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V3 14
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V4 16
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V5 18
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V6 20
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V7 22
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V8 24
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V9 26

#define NUM_BITS_CWOCK_INFO_AWWAY_INDEX 6

static uint16_t get_vce_tabwe_offset(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t vce_tabwe_offset = 0;

	if (we16_to_cpu(powewpway_tabwe->usTabweSize) >=
	   sizeof(ATOM_PPWIB_POWEWPWAYTABWE3)) {
		const ATOM_PPWIB_POWEWPWAYTABWE3 *powewpway_tabwe3 =
			(const ATOM_PPWIB_POWEWPWAYTABWE3 *)powewpway_tabwe;

		if (powewpway_tabwe3->usExtendendedHeadewOffset > 0) {
			const ATOM_PPWIB_EXTENDEDHEADEW  *extended_headew =
						(const ATOM_PPWIB_EXTENDEDHEADEW *)
						(((unsigned wong)powewpway_tabwe3) +
						we16_to_cpu(powewpway_tabwe3->usExtendendedHeadewOffset));
			if (we16_to_cpu(extended_headew->usSize) >=
			   SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V2)
				vce_tabwe_offset = we16_to_cpu(extended_headew->usVCETabweOffset);
		}
	}

	wetuwn vce_tabwe_offset;
}

static uint16_t get_vce_cwock_info_awway_offset(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_vce_tabwe_offset(hwmgw,
						powewpway_tabwe);

	if (tabwe_offset > 0)
		wetuwn tabwe_offset + 1;

	wetuwn 0;
}

static uint16_t get_vce_cwock_info_awway_size(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_vce_cwock_info_awway_offset(hwmgw,
							powewpway_tabwe);
	uint16_t tabwe_size = 0;

	if (tabwe_offset > 0) {
		const VCECwockInfoAwway *p = (const VCECwockInfoAwway *)
			(((unsigned wong) powewpway_tabwe) + tabwe_offset);
		tabwe_size = sizeof(uint8_t) + p->ucNumEntwies * sizeof(VCECwockInfo);
	}

	wetuwn tabwe_size;
}

static uint16_t get_vce_cwock_vowtage_wimit_tabwe_offset(stwuct pp_hwmgw *hwmgw,
				const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_vce_cwock_info_awway_offset(hwmgw,
							powewpway_tabwe);

	if (tabwe_offset > 0)
		wetuwn tabwe_offset + get_vce_cwock_info_awway_size(hwmgw,
							powewpway_tabwe);

	wetuwn 0;
}

static uint16_t get_vce_cwock_vowtage_wimit_tabwe_size(stwuct pp_hwmgw *hwmgw,
							const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_vce_cwock_vowtage_wimit_tabwe_offset(hwmgw, powewpway_tabwe);
	uint16_t tabwe_size = 0;

	if (tabwe_offset > 0) {
		const ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe *ptabwe =
			(const ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe *)(((unsigned wong) powewpway_tabwe) + tabwe_offset);

		tabwe_size = sizeof(uint8_t) + ptabwe->numEntwies * sizeof(ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd);
	}
	wetuwn tabwe_size;
}

static uint16_t get_vce_state_tabwe_offset(stwuct pp_hwmgw *hwmgw, const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_vce_cwock_vowtage_wimit_tabwe_offset(hwmgw, powewpway_tabwe);

	if (tabwe_offset > 0)
		wetuwn tabwe_offset + get_vce_cwock_vowtage_wimit_tabwe_size(hwmgw, powewpway_tabwe);

	wetuwn 0;
}

static const ATOM_PPWIB_VCE_State_Tabwe *get_vce_state_tabwe(
						stwuct pp_hwmgw *hwmgw,
						const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_vce_state_tabwe_offset(hwmgw, powewpway_tabwe);

	if (tabwe_offset > 0)
		wetuwn (const ATOM_PPWIB_VCE_State_Tabwe *)(((unsigned wong) powewpway_tabwe) + tabwe_offset);

	wetuwn NUWW;
}

static uint16_t get_uvd_tabwe_offset(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t uvd_tabwe_offset = 0;

	if (we16_to_cpu(powewpway_tabwe->usTabweSize) >=
	    sizeof(ATOM_PPWIB_POWEWPWAYTABWE3)) {
		const ATOM_PPWIB_POWEWPWAYTABWE3 *powewpway_tabwe3 =
			(const ATOM_PPWIB_POWEWPWAYTABWE3 *)powewpway_tabwe;
		if (powewpway_tabwe3->usExtendendedHeadewOffset > 0) {
			const ATOM_PPWIB_EXTENDEDHEADEW  *extended_headew =
					(const ATOM_PPWIB_EXTENDEDHEADEW *)
					(((unsigned wong)powewpway_tabwe3) +
				we16_to_cpu(powewpway_tabwe3->usExtendendedHeadewOffset));
			if (we16_to_cpu(extended_headew->usSize) >=
			    SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V3)
				uvd_tabwe_offset = we16_to_cpu(extended_headew->usUVDTabweOffset);
		}
	}
	wetuwn uvd_tabwe_offset;
}

static uint16_t get_uvd_cwock_info_awway_offset(stwuct pp_hwmgw *hwmgw,
			 const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_uvd_tabwe_offset(hwmgw,
						    powewpway_tabwe);

	if (tabwe_offset > 0)
		wetuwn tabwe_offset + 1;
	wetuwn 0;
}

static uint16_t get_uvd_cwock_info_awway_size(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_uvd_cwock_info_awway_offset(hwmgw,
						    powewpway_tabwe);
	uint16_t tabwe_size = 0;

	if (tabwe_offset > 0) {
		const UVDCwockInfoAwway *p = (const UVDCwockInfoAwway *)
					(((unsigned wong) powewpway_tabwe)
					+ tabwe_offset);
		tabwe_size = sizeof(UCHAW) +
			     p->ucNumEntwies * sizeof(UVDCwockInfo);
	}

	wetuwn tabwe_size;
}

static uint16_t get_uvd_cwock_vowtage_wimit_tabwe_offset(
			stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_uvd_cwock_info_awway_offset(hwmgw,
						     powewpway_tabwe);

	if (tabwe_offset > 0)
		wetuwn tabwe_offset +
			get_uvd_cwock_info_awway_size(hwmgw, powewpway_tabwe);

	wetuwn 0;
}

static uint16_t get_samu_tabwe_offset(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t samu_tabwe_offset = 0;

	if (we16_to_cpu(powewpway_tabwe->usTabweSize) >=
	    sizeof(ATOM_PPWIB_POWEWPWAYTABWE3)) {
		const ATOM_PPWIB_POWEWPWAYTABWE3 *powewpway_tabwe3 =
			(const ATOM_PPWIB_POWEWPWAYTABWE3 *)powewpway_tabwe;
		if (powewpway_tabwe3->usExtendendedHeadewOffset > 0) {
			const ATOM_PPWIB_EXTENDEDHEADEW  *extended_headew =
				(const ATOM_PPWIB_EXTENDEDHEADEW *)
				(((unsigned wong)powewpway_tabwe3) +
				we16_to_cpu(powewpway_tabwe3->usExtendendedHeadewOffset));
			if (we16_to_cpu(extended_headew->usSize) >=
			    SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V4)
				samu_tabwe_offset = we16_to_cpu(extended_headew->usSAMUTabweOffset);
		}
	}

	wetuwn samu_tabwe_offset;
}

static uint16_t get_samu_cwock_vowtage_wimit_tabwe_offset(
			stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabwe_offset = get_samu_tabwe_offset(hwmgw,
					    powewpway_tabwe);

	if (tabwe_offset > 0)
		wetuwn tabwe_offset + 1;

	wetuwn 0;
}

static uint16_t get_acp_tabwe_offset(stwuct pp_hwmgw *hwmgw,
				const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t acp_tabwe_offset = 0;

	if (we16_to_cpu(powewpway_tabwe->usTabweSize) >=
	    sizeof(ATOM_PPWIB_POWEWPWAYTABWE3)) {
		const ATOM_PPWIB_POWEWPWAYTABWE3 *powewpway_tabwe3 =
			(const ATOM_PPWIB_POWEWPWAYTABWE3 *)powewpway_tabwe;
		if (powewpway_tabwe3->usExtendendedHeadewOffset > 0) {
			const ATOM_PPWIB_EXTENDEDHEADEW  *pExtendedHeadew =
				(const ATOM_PPWIB_EXTENDEDHEADEW *)
				(((unsigned wong)powewpway_tabwe3) +
				we16_to_cpu(powewpway_tabwe3->usExtendendedHeadewOffset));
			if (we16_to_cpu(pExtendedHeadew->usSize) >=
			    SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V6)
				acp_tabwe_offset = we16_to_cpu(pExtendedHeadew->usACPTabweOffset);
		}
	}

	wetuwn acp_tabwe_offset;
}

static uint16_t get_acp_cwock_vowtage_wimit_tabwe_offset(
				stwuct pp_hwmgw *hwmgw,
				const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabweOffset = get_acp_tabwe_offset(hwmgw, powewpway_tabwe);

	if (tabweOffset > 0)
		wetuwn tabweOffset + 1;

	wetuwn 0;
}

static uint16_t get_cacp_tdp_tabwe_offset(
				stwuct pp_hwmgw *hwmgw,
				const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t cacTdpTabweOffset = 0;

	if (we16_to_cpu(powewpway_tabwe->usTabweSize) >=
	    sizeof(ATOM_PPWIB_POWEWPWAYTABWE3)) {
		const ATOM_PPWIB_POWEWPWAYTABWE3 *powewpway_tabwe3 =
				(const ATOM_PPWIB_POWEWPWAYTABWE3 *)powewpway_tabwe;
		if (powewpway_tabwe3->usExtendendedHeadewOffset > 0) {
			const ATOM_PPWIB_EXTENDEDHEADEW  *pExtendedHeadew =
					(const ATOM_PPWIB_EXTENDEDHEADEW *)
					(((unsigned wong)powewpway_tabwe3) +
				we16_to_cpu(powewpway_tabwe3->usExtendendedHeadewOffset));
			if (we16_to_cpu(pExtendedHeadew->usSize) >=
			    SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V7)
				cacTdpTabweOffset = we16_to_cpu(pExtendedHeadew->usPowewTuneTabweOffset);
		}
	}

	wetuwn cacTdpTabweOffset;
}

static int get_cac_tdp_tabwe(stwuct pp_hwmgw *hwmgw,
				stwuct phm_cac_tdp_tabwe **ptabwe,
				const ATOM_PowewTune_Tabwe *tabwe,
				uint16_t us_maximum_powew_dewivewy_wimit)
{
	unsigned wong tabwe_size;
	stwuct phm_cac_tdp_tabwe *tdp_tabwe;

	tabwe_size = sizeof(unsigned wong) + sizeof(stwuct phm_cac_tdp_tabwe);

	tdp_tabwe = kzawwoc(tabwe_size, GFP_KEWNEW);
	if (NUWW == tdp_tabwe)
		wetuwn -ENOMEM;

	tdp_tabwe->usTDP = we16_to_cpu(tabwe->usTDP);
	tdp_tabwe->usConfiguwabweTDP = we16_to_cpu(tabwe->usConfiguwabweTDP);
	tdp_tabwe->usTDC = we16_to_cpu(tabwe->usTDC);
	tdp_tabwe->usBattewyPowewWimit = we16_to_cpu(tabwe->usBattewyPowewWimit);
	tdp_tabwe->usSmawwPowewWimit = we16_to_cpu(tabwe->usSmawwPowewWimit);
	tdp_tabwe->usWowCACWeakage = we16_to_cpu(tabwe->usWowCACWeakage);
	tdp_tabwe->usHighCACWeakage = we16_to_cpu(tabwe->usHighCACWeakage);
	tdp_tabwe->usMaximumPowewDewivewyWimit = us_maximum_powew_dewivewy_wimit;

	*ptabwe = tdp_tabwe;

	wetuwn 0;
}

static uint16_t get_scwk_vdd_gfx_tabwe_offset(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t scwk_vdd_gfx_tabwe_offset = 0;

	if (we16_to_cpu(powewpway_tabwe->usTabweSize) >=
	    sizeof(ATOM_PPWIB_POWEWPWAYTABWE3)) {
		const ATOM_PPWIB_POWEWPWAYTABWE3 *powewpway_tabwe3 =
				(const ATOM_PPWIB_POWEWPWAYTABWE3 *)powewpway_tabwe;
		if (powewpway_tabwe3->usExtendendedHeadewOffset > 0) {
			const ATOM_PPWIB_EXTENDEDHEADEW  *pExtendedHeadew =
				(const ATOM_PPWIB_EXTENDEDHEADEW *)
				(((unsigned wong)powewpway_tabwe3) +
				we16_to_cpu(powewpway_tabwe3->usExtendendedHeadewOffset));
			if (we16_to_cpu(pExtendedHeadew->usSize) >=
			    SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V8)
				scwk_vdd_gfx_tabwe_offset =
					we16_to_cpu(pExtendedHeadew->usScwkVddgfxTabweOffset);
		}
	}

	wetuwn scwk_vdd_gfx_tabwe_offset;
}

static uint16_t get_scwk_vdd_gfx_cwock_vowtage_dependency_tabwe_offset(
			stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	uint16_t tabweOffset = get_scwk_vdd_gfx_tabwe_offset(hwmgw, powewpway_tabwe);

	if (tabweOffset > 0)
		wetuwn tabweOffset;

	wetuwn 0;
}


static int get_cwock_vowtage_dependency_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct phm_cwock_vowtage_dependency_tabwe **ptabwe,
		const ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *tabwe)
{

	unsigned wong i;
	stwuct phm_cwock_vowtage_dependency_tabwe *dep_tabwe;

	dep_tabwe = kzawwoc(stwuct_size(dep_tabwe, entwies, tabwe->ucNumEntwies),
			    GFP_KEWNEW);
	if (NUWW == dep_tabwe)
		wetuwn -ENOMEM;

	dep_tabwe->count = (unsigned wong)tabwe->ucNumEntwies;

	fow (i = 0; i < dep_tabwe->count; i++) {
		dep_tabwe->entwies[i].cwk =
			((unsigned wong)tabwe->entwies[i].ucCwockHigh << 16) |
			we16_to_cpu(tabwe->entwies[i].usCwockWow);
		dep_tabwe->entwies[i].v =
			(unsigned wong)we16_to_cpu(tabwe->entwies[i].usVowtage);
	}

	*ptabwe = dep_tabwe;

	wetuwn 0;
}

static int get_vawid_cwk(stwuct pp_hwmgw *hwmgw,
			stwuct phm_cwock_awway **ptabwe,
			const stwuct phm_cwock_vowtage_dependency_tabwe *tabwe)
{
	unsigned wong i;
	stwuct phm_cwock_awway *cwock_tabwe;

	cwock_tabwe = kzawwoc(stwuct_size(cwock_tabwe, vawues, tabwe->count), GFP_KEWNEW);
	if (!cwock_tabwe)
		wetuwn -ENOMEM;

	cwock_tabwe->count = (unsigned wong)tabwe->count;

	fow (i = 0; i < cwock_tabwe->count; i++)
		cwock_tabwe->vawues[i] = (unsigned wong)tabwe->entwies[i].cwk;

	*ptabwe = cwock_tabwe;

	wetuwn 0;
}

static int get_cwock_vowtage_wimit(stwuct pp_hwmgw *hwmgw,
			stwuct phm_cwock_and_vowtage_wimits *wimits,
			const ATOM_PPWIB_Cwock_Vowtage_Wimit_Tabwe *tabwe)
{
	wimits->scwk = ((unsigned wong)tabwe->entwies[0].ucScwkHigh << 16) |
			we16_to_cpu(tabwe->entwies[0].usScwkWow);
	wimits->mcwk = ((unsigned wong)tabwe->entwies[0].ucMcwkHigh << 16) |
			we16_to_cpu(tabwe->entwies[0].usMcwkWow);
	wimits->vddc = (unsigned wong)we16_to_cpu(tabwe->entwies[0].usVddc);
	wimits->vddci = (unsigned wong)we16_to_cpu(tabwe->entwies[0].usVddci);

	wetuwn 0;
}


static void set_hw_cap(stwuct pp_hwmgw *hwmgw, boow enabwe,
		       enum phm_pwatfowm_caps cap)
{
	if (enabwe)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, cap);
	ewse
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, cap);
}

static int set_pwatfowm_caps(stwuct pp_hwmgw *hwmgw,
			unsigned wong powewpway_caps)
{
	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_POWEWPWAY),
		PHM_PwatfowmCaps_PowewPwaySuppowt
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_SBIOSPOWEWSOUWCE),
		PHM_PwatfowmCaps_BiosPowewSouwceContwow
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_ASPM_W0s),
		PHM_PwatfowmCaps_EnabweASPMW0s
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_ASPM_W1),
		PHM_PwatfowmCaps_EnabweASPMW1
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_BACKBIAS),
		PHM_PwatfowmCaps_EnabweBackbias
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_HAWDWAWEDC),
		PHM_PwatfowmCaps_AutomaticDCTwansition
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_GEMINIPWIMAWY),
		PHM_PwatfowmCaps_GeminiPwimawy
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_STEPVDDC),
		PHM_PwatfowmCaps_StepVddc
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_VOWTAGECONTWOW),
		PHM_PwatfowmCaps_EnabweVowtageContwow
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_SIDEPOWTCONTWOW),
		PHM_PwatfowmCaps_EnabweSidepowtContwow
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_TUWNOFFPWW_ASPMW1),
		PHM_PwatfowmCaps_TuwnOffPww_ASPMW1
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_HTWINKCONTWOW),
		PHM_PwatfowmCaps_EnabweHTWinkContwow
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_MVDDCONTWOW),
		PHM_PwatfowmCaps_EnabweMVDDContwow
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_VDDCI_CONTWOW),
		PHM_PwatfowmCaps_ContwowVDDCI
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_WEGUWATOW_HOT),
		PHM_PwatfowmCaps_WeguwatowHot
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_GOTO_BOOT_ON_AWEWT),
		PHM_PwatfowmCaps_BootStateOnAwewt
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_DONT_WAIT_FOW_VBWANK_ON_AWEWT),
		PHM_PwatfowmCaps_DontWaitFowVBwankOnAwewt
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_BACO),
		PHM_PwatfowmCaps_BACO
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_NEW_CAC_VOWTAGE),
		PHM_PwatfowmCaps_NewCACVowtage
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_WEVEWT_GPIO5_POWAWITY),
		PHM_PwatfowmCaps_WevewtGPIO5Powawity
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_OUTPUT_THEWMAW2GPIO17),
		PHM_PwatfowmCaps_Thewmaw2GPIO17
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_VWHOT_GPIO_CONFIGUWABWE),
		PHM_PwatfowmCaps_VWHotGPIOConfiguwabwe
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_TEMP_INVEWSION),
		PHM_PwatfowmCaps_TempInvewsion
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_EVV),
		PHM_PwatfowmCaps_EVV
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_COMBINE_PCC_WITH_THEWMAW_SIGNAW),
		PHM_PwatfowmCaps_CombinePCCWithThewmawSignaw
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_WOAD_POST_PWODUCTION_FIWMWAWE),
		PHM_PwatfowmCaps_WoadPostPwoductionFiwmwawe
	);

	set_hw_cap(
		hwmgw,
		0 != (powewpway_caps & ATOM_PP_PWATFOWM_CAP_DISABWE_USING_ACTUAW_TEMPEWATUWE_FOW_POWEW_CAWC),
		PHM_PwatfowmCaps_DisabweUsingActuawTempewatuweFowPowewCawc
	);

	wetuwn 0;
}

static PP_StateCwassificationFwags make_cwassification_fwags(
						   stwuct pp_hwmgw *hwmgw,
						    USHOWT cwassification,
						   USHOWT cwassification2)
{
	PP_StateCwassificationFwags wesuwt = 0;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_BOOT)
		wesuwt |= PP_StateCwassificationFwag_Boot;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_THEWMAW)
		wesuwt |= PP_StateCwassificationFwag_Thewmaw;

	if (cwassification &
			ATOM_PPWIB_CWASSIFICATION_WIMITEDPOWEWSOUWCE)
		wesuwt |= PP_StateCwassificationFwag_WimitedPowewSouwce;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_WEST)
		wesuwt |= PP_StateCwassificationFwag_West;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_FOWCED)
		wesuwt |= PP_StateCwassificationFwag_Fowced;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_3DPEWFOWMANCE)
		wesuwt |= PP_StateCwassificationFwag_3DPewfowmance;


	if (cwassification & ATOM_PPWIB_CWASSIFICATION_OVEWDWIVETEMPWATE)
		wesuwt |= PP_StateCwassificationFwag_ACOvewdwiveTempwate;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
		wesuwt |= PP_StateCwassificationFwag_Uvd;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_HDSTATE)
		wesuwt |= PP_StateCwassificationFwag_UvdHD;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_SDSTATE)
		wesuwt |= PP_StateCwassificationFwag_UvdSD;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_HD2STATE)
		wesuwt |= PP_StateCwassificationFwag_HD2;

	if (cwassification & ATOM_PPWIB_CWASSIFICATION_ACPI)
		wesuwt |= PP_StateCwassificationFwag_ACPI;

	if (cwassification2 & ATOM_PPWIB_CWASSIFICATION2_WIMITEDPOWEWSOUWCE_2)
		wesuwt |= PP_StateCwassificationFwag_WimitedPowewSouwce_2;


	if (cwassification2 & ATOM_PPWIB_CWASSIFICATION2_UWV)
		wesuwt |= PP_StateCwassificationFwag_UWV;

	if (cwassification2 & ATOM_PPWIB_CWASSIFICATION2_MVC)
		wesuwt |= PP_StateCwassificationFwag_UvdMVC;

	wetuwn wesuwt;
}

static int init_non_cwock_fiewds(stwuct pp_hwmgw *hwmgw,
						stwuct pp_powew_state *ps,
							    uint8_t vewsion,
			 const ATOM_PPWIB_NONCWOCK_INFO *pnon_cwock_info) {
	unsigned wong www_index;
	unsigned wong tmp;

	ps->cwassification.ui_wabew = (we16_to_cpu(pnon_cwock_info->usCwassification) &
					ATOM_PPWIB_CWASSIFICATION_UI_MASK) >> ATOM_PPWIB_CWASSIFICATION_UI_SHIFT;
	ps->cwassification.fwags = make_cwassification_fwags(hwmgw,
				we16_to_cpu(pnon_cwock_info->usCwassification),
				we16_to_cpu(pnon_cwock_info->usCwassification2));

	ps->cwassification.tempowawy_state = fawse;
	ps->cwassification.to_be_deweted = fawse;
	tmp = we32_to_cpu(pnon_cwock_info->uwCapsAndSettings) &
		ATOM_PPWIB_SINGWE_DISPWAY_ONWY;

	ps->vawidation.singweDispwayOnwy = (0 != tmp);

	tmp = we32_to_cpu(pnon_cwock_info->uwCapsAndSettings) &
		ATOM_PPWIB_DISAWWOW_ON_DC;

	ps->vawidation.disawwowOnDC = (0 != tmp);

	ps->pcie.wanes = ((we32_to_cpu(pnon_cwock_info->uwCapsAndSettings) &
				ATOM_PPWIB_PCIE_WINK_WIDTH_MASK) >>
				ATOM_PPWIB_PCIE_WINK_WIDTH_SHIFT) + 1;

	ps->pcie.wanes = 0;

	ps->dispway.disabweFwameModuwation = fawse;

	www_index = (we32_to_cpu(pnon_cwock_info->uwCapsAndSettings) &
			ATOM_PPWIB_WIMITED_WEFWESHWATE_VAWUE_MASK) >>
			ATOM_PPWIB_WIMITED_WEFWESHWATE_VAWUE_SHIFT;

	if (www_index != ATOM_PPWIB_WIMITED_WEFWESHWATE_UNWIMITED) {
		static const uint8_t wook_up[(ATOM_PPWIB_WIMITED_WEFWESHWATE_VAWUE_MASK >> ATOM_PPWIB_WIMITED_WEFWESHWATE_VAWUE_SHIFT) + 1] = \
								{ 0, 50, 0 };

		ps->dispway.wefweshwateSouwce = PP_WefweshwateSouwce_Expwicit;
		ps->dispway.expwicitWefweshwate = wook_up[www_index];
		ps->dispway.wimitWefweshwate = twue;

		if (ps->dispway.expwicitWefweshwate == 0)
			ps->dispway.wimitWefweshwate = fawse;
	} ewse
		ps->dispway.wimitWefweshwate = fawse;

	tmp = we32_to_cpu(pnon_cwock_info->uwCapsAndSettings) &
		ATOM_PPWIB_ENABWE_VAWIBWIGHT;

	ps->dispway.enabweVawiBwight = (0 != tmp);

	tmp = we32_to_cpu(pnon_cwock_info->uwCapsAndSettings) &
		ATOM_PPWIB_SWSTATE_MEMOWY_DWW_OFF;

	ps->memowy.dwwOff = (0 != tmp);

	ps->memowy.m3awb = (we32_to_cpu(pnon_cwock_info->uwCapsAndSettings) &
			    ATOM_PPWIB_M3AWB_MASK) >> ATOM_PPWIB_M3AWB_SHIFT;

	ps->tempewatuwes.min = PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES *
				     pnon_cwock_info->ucMinTempewatuwe;

	ps->tempewatuwes.max = PP_TEMPEWATUWE_UNITS_PEW_CENTIGWADES *
				     pnon_cwock_info->ucMaxTempewatuwe;

	tmp = we32_to_cpu(pnon_cwock_info->uwCapsAndSettings) &
		ATOM_PPWIB_SOFTWAWE_DISABWE_WOADBAWANCING;

	ps->softwawe.disabweWoadBawancing = tmp;

	tmp = we32_to_cpu(pnon_cwock_info->uwCapsAndSettings) &
		ATOM_PPWIB_SOFTWAWE_ENABWE_SWEEP_FOW_TIMESTAMPS;

	ps->softwawe.enabweSweepFowTimestamps = (0 != tmp);

	ps->vawidation.suppowtedPowewWevews = pnon_cwock_info->ucWequiwedPowew;

	if (ATOM_PPWIB_NONCWOCKINFO_VEW1 < vewsion) {
		ps->uvd_cwocks.VCWK = we32_to_cpu(pnon_cwock_info->uwVCWK);
		ps->uvd_cwocks.DCWK = we32_to_cpu(pnon_cwock_info->uwDCWK);
	} ewse {
		ps->uvd_cwocks.VCWK = 0;
		ps->uvd_cwocks.DCWK = 0;
	}

	wetuwn 0;
}

static UWONG size_of_entwy_v2(UWONG num_dpm_wevews)
{
	wetuwn (sizeof(UCHAW) + sizeof(UCHAW) +
			(num_dpm_wevews * sizeof(UCHAW)));
}

static const ATOM_PPWIB_STATE_V2 *get_state_entwy_v2(
					const StateAwway * pstate_awways,
							 UWONG entwy_index)
{
	UWONG i;
	const ATOM_PPWIB_STATE_V2 *pstate;

	pstate = pstate_awways->states;
	if (entwy_index <= pstate_awways->ucNumEntwies) {
		fow (i = 0; i < entwy_index; i++)
			pstate = (ATOM_PPWIB_STATE_V2 *)(
						  (unsigned wong)pstate +
			     size_of_entwy_v2(pstate->ucNumDPMWevews));
	}
	wetuwn pstate;
}

static const unsigned chaw soft_dummy_pp_tabwe[] = {
	0xe1, 0x01, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x4a, 0x00, 0x6c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x42, 0x00, 0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x4e, 0x00, 0x88, 0x00, 0x00, 0x9e, 0x00, 0x17, 0x00, 0x00, 0x00, 0x9e, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x02, 0x02, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00,
	0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x18, 0x05, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe1, 0x00, 0x43, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x8e, 0x01, 0x00, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x08, 0x30, 0x75, 0x00, 0x80, 0x00, 0xa0, 0x8c,
	0x00, 0x7e, 0x00, 0x71, 0xa5, 0x00, 0x7c, 0x00, 0xe5, 0xc8, 0x00, 0x70, 0x00, 0x91, 0xf4, 0x00,
	0x64, 0x00, 0x40, 0x19, 0x01, 0x5a, 0x00, 0x0e, 0x28, 0x01, 0x52, 0x00, 0x80, 0x38, 0x01, 0x4a,
	0x00, 0x00, 0x09, 0x30, 0x75, 0x00, 0x30, 0x75, 0x00, 0x40, 0x9c, 0x00, 0x40, 0x9c, 0x00, 0x59,
	0xd8, 0x00, 0x59, 0xd8, 0x00, 0x91, 0xf4, 0x00, 0x91, 0xf4, 0x00, 0x0e, 0x28, 0x01, 0x0e, 0x28,
	0x01, 0x90, 0x5f, 0x01, 0x90, 0x5f, 0x01, 0x00, 0x77, 0x01, 0x00, 0x77, 0x01, 0xca, 0x91, 0x01,
	0xca, 0x91, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x80, 0x00, 0x00, 0x7e, 0x00, 0x01,
	0x7c, 0x00, 0x02, 0x70, 0x00, 0x03, 0x64, 0x00, 0x04, 0x5a, 0x00, 0x05, 0x52, 0x00, 0x06, 0x4a,
	0x00, 0x07, 0x08, 0x08, 0x00, 0x08, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x03,
	0x02, 0x04, 0x02, 0x00, 0x08, 0x40, 0x9c, 0x00, 0x30, 0x75, 0x00, 0x74, 0xb5, 0x00, 0xa0, 0x8c,
	0x00, 0x60, 0xea, 0x00, 0x74, 0xb5, 0x00, 0x0e, 0x28, 0x01, 0x60, 0xea, 0x00, 0x90, 0x5f, 0x01,
	0x40, 0x19, 0x01, 0xb2, 0xb0, 0x01, 0x90, 0x5f, 0x01, 0xc0, 0xd4, 0x01, 0x00, 0x77, 0x01, 0x5e,
	0xff, 0x01, 0xca, 0x91, 0x01, 0x08, 0x80, 0x00, 0x00, 0x7e, 0x00, 0x01, 0x7c, 0x00, 0x02, 0x70,
	0x00, 0x03, 0x64, 0x00, 0x04, 0x5a, 0x00, 0x05, 0x52, 0x00, 0x06, 0x4a, 0x00, 0x07, 0x00, 0x08,
	0x80, 0x00, 0x30, 0x75, 0x00, 0x7e, 0x00, 0x40, 0x9c, 0x00, 0x7c, 0x00, 0x59, 0xd8, 0x00, 0x70,
	0x00, 0xdc, 0x0b, 0x01, 0x64, 0x00, 0x80, 0x38, 0x01, 0x5a, 0x00, 0x80, 0x38, 0x01, 0x52, 0x00,
	0x80, 0x38, 0x01, 0x4a, 0x00, 0x80, 0x38, 0x01, 0x08, 0x30, 0x75, 0x00, 0x80, 0x00, 0xa0, 0x8c,
	0x00, 0x7e, 0x00, 0x71, 0xa5, 0x00, 0x7c, 0x00, 0xe5, 0xc8, 0x00, 0x74, 0x00, 0x91, 0xf4, 0x00,
	0x66, 0x00, 0x40, 0x19, 0x01, 0x58, 0x00, 0x0e, 0x28, 0x01, 0x52, 0x00, 0x80, 0x38, 0x01, 0x4a,
	0x00
};

static const ATOM_PPWIB_POWEWPWAYTABWE *get_powewpway_tabwe(
				     stwuct pp_hwmgw *hwmgw)
{
	const void *tabwe_addw = hwmgw->soft_pp_tabwe;
	uint8_t fwev, cwev;
	uint16_t size;

	if (!tabwe_addw) {
		if (hwmgw->chip_id == CHIP_WAVEN) {
			tabwe_addw = &soft_dummy_pp_tabwe[0];
			hwmgw->soft_pp_tabwe = &soft_dummy_pp_tabwe[0];
			hwmgw->soft_pp_tabwe_size = sizeof(soft_dummy_pp_tabwe);
		} ewse {
			tabwe_addw = smu_atom_get_data_tabwe(hwmgw->adev,
					GetIndexIntoMastewTabwe(DATA, PowewPwayInfo),
					&size, &fwev, &cwev);
			hwmgw->soft_pp_tabwe = tabwe_addw;
			hwmgw->soft_pp_tabwe_size = size;
		}
	}

	wetuwn (const ATOM_PPWIB_POWEWPWAYTABWE *)tabwe_addw;
}

int pp_tabwes_get_wesponse_times(stwuct pp_hwmgw *hwmgw,
				uint32_t *vow_wep_time, uint32_t *bb_wep_time)
{
	const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tab = get_powewpway_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE(NUWW != powewpway_tab,
			    "Missing PowewPway Tabwe!", wetuwn -EINVAW);

	*vow_wep_time = (uint32_t)we16_to_cpu(powewpway_tab->usVowtageTime);
	*bb_wep_time = (uint32_t)we16_to_cpu(powewpway_tab->usBackbiasTime);

	wetuwn 0;
}

int pp_tabwes_get_num_of_entwies(stwuct pp_hwmgw *hwmgw,
				     unsigned wong *num_of_entwies)
{
	const StateAwway *pstate_awways;
	const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe = get_powewpway_tabwe(hwmgw);

	if (powewpway_tabwe == NUWW)
		wetuwn -1;

	if (powewpway_tabwe->sHeadew.ucTabweFowmatWevision >= 6) {
		pstate_awways = (StateAwway *)(((unsigned wong)powewpway_tabwe) +
					we16_to_cpu(powewpway_tabwe->usStateAwwayOffset));

		*num_of_entwies = (unsigned wong)(pstate_awways->ucNumEntwies);
	} ewse
		*num_of_entwies = (unsigned wong)(powewpway_tabwe->ucNumStates);

	wetuwn 0;
}

int pp_tabwes_get_entwy(stwuct pp_hwmgw *hwmgw,
				unsigned wong entwy_index,
				stwuct pp_powew_state *ps,
			 pp_tabwes_hw_cwock_info_cawwback func)
{
	int i;
	const StateAwway *pstate_awways;
	const ATOM_PPWIB_STATE_V2 *pstate_entwy_v2;
	const ATOM_PPWIB_NONCWOCK_INFO *pnon_cwock_info;
	const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe = get_powewpway_tabwe(hwmgw);
	int wesuwt = 0;
	int wes = 0;

	const CwockInfoAwway *pcwock_awways;

	const NonCwockInfoAwway *pnon_cwock_awways;

	const ATOM_PPWIB_STATE *pstate_entwy;

	if (powewpway_tabwe == NUWW)
		wetuwn -1;

	ps->cwassification.bios_index = entwy_index;

	if (powewpway_tabwe->sHeadew.ucTabweFowmatWevision >= 6) {
		pstate_awways = (StateAwway *)(((unsigned wong)powewpway_tabwe) +
					we16_to_cpu(powewpway_tabwe->usStateAwwayOffset));

		if (entwy_index > pstate_awways->ucNumEntwies)
			wetuwn -1;

		pstate_entwy_v2 = get_state_entwy_v2(pstate_awways, entwy_index);
		pcwock_awways = (CwockInfoAwway *)(((unsigned wong)powewpway_tabwe) +
					we16_to_cpu(powewpway_tabwe->usCwockInfoAwwayOffset));

		pnon_cwock_awways = (NonCwockInfoAwway *)(((unsigned wong)powewpway_tabwe) +
						we16_to_cpu(powewpway_tabwe->usNonCwockInfoAwwayOffset));

		pnon_cwock_info = (ATOM_PPWIB_NONCWOCK_INFO *)((unsigned wong)(pnon_cwock_awways->nonCwockInfo) +
					(pstate_entwy_v2->nonCwockInfoIndex * pnon_cwock_awways->ucEntwySize));

		wesuwt = init_non_cwock_fiewds(hwmgw, ps, pnon_cwock_awways->ucEntwySize, pnon_cwock_info);

		fow (i = 0; i < pstate_entwy_v2->ucNumDPMWevews; i++) {
			const void *pcwock_info = (const void *)(
							(unsigned wong)(pcwock_awways->cwockInfo) +
							(pstate_entwy_v2->cwockInfoIndex[i] * pcwock_awways->ucEntwySize));
			wes = func(hwmgw, &ps->hawdwawe, i, pcwock_info);
			if ((0 == wesuwt) && (0 != wes))
				wesuwt = wes;
		}
	} ewse {
		if (entwy_index > powewpway_tabwe->ucNumStates)
			wetuwn -1;

		pstate_entwy = (ATOM_PPWIB_STATE *)((unsigned wong)powewpway_tabwe +
						    we16_to_cpu(powewpway_tabwe->usStateAwwayOffset) +
						    entwy_index * powewpway_tabwe->ucStateEntwySize);

		pnon_cwock_info = (ATOM_PPWIB_NONCWOCK_INFO *)((unsigned wong)powewpway_tabwe +
						we16_to_cpu(powewpway_tabwe->usNonCwockInfoAwwayOffset) +
						pstate_entwy->ucNonCwockStateIndex *
						powewpway_tabwe->ucNonCwockSize);

		wesuwt = init_non_cwock_fiewds(hwmgw, ps,
							powewpway_tabwe->ucNonCwockSize,
							pnon_cwock_info);

		fow (i = 0; i < powewpway_tabwe->ucStateEntwySize-1; i++) {
			const void *pcwock_info = (const void *)((unsigned wong)powewpway_tabwe +
						we16_to_cpu(powewpway_tabwe->usCwockInfoAwwayOffset) +
						pstate_entwy->ucCwockStateIndices[i] *
						powewpway_tabwe->ucCwockInfoSize);

			int wes = func(hwmgw, &ps->hawdwawe, i, pcwock_info);

			if ((0 == wesuwt) && (0 != wes))
					wesuwt = wes;
		}
	}

	if ((0 == wesuwt) && (0 != (ps->cwassification.fwags & PP_StateCwassificationFwag_Boot))) {
		if (hwmgw->chip_famiwy < AMDGPU_FAMIWY_WV)
			wesuwt = hwmgw->hwmgw_func->patch_boot_state(hwmgw, &(ps->hawdwawe));
	}

	wetuwn wesuwt;
}

static int init_powewpway_tabwes(
			stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe
)
{
	wetuwn 0;
}


static int init_thewmaw_contwowwew(
			stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	stwuct amdgpu_device *adev = hwmgw->adev;

	hwmgw->thewmaw_contwowwew.ucType =
			powewpway_tabwe->sThewmawContwowwew.ucType;
	hwmgw->thewmaw_contwowwew.ucI2cWine =
			powewpway_tabwe->sThewmawContwowwew.ucI2cWine;
	hwmgw->thewmaw_contwowwew.ucI2cAddwess =
			powewpway_tabwe->sThewmawContwowwew.ucI2cAddwess;

	hwmgw->thewmaw_contwowwew.fanInfo.bNoFan =
		(0 != (powewpway_tabwe->sThewmawContwowwew.ucFanPawametews &
			ATOM_PP_FANPAWAMETEWS_NOFAN));

	hwmgw->thewmaw_contwowwew.fanInfo.ucTachometewPuwsesPewWevowution =
		powewpway_tabwe->sThewmawContwowwew.ucFanPawametews &
		ATOM_PP_FANPAWAMETEWS_TACHOMETEW_PUWSES_PEW_WEVOWUTION_MASK;

	hwmgw->thewmaw_contwowwew.fanInfo.uwMinWPM
		= powewpway_tabwe->sThewmawContwowwew.ucFanMinWPM * 100UW;
	hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM
		= powewpway_tabwe->sThewmawContwowwew.ucFanMaxWPM * 100UW;

	set_hw_cap(hwmgw,
		   ATOM_PP_THEWMAWCONTWOWWEW_NONE != hwmgw->thewmaw_contwowwew.ucType,
		   PHM_PwatfowmCaps_ThewmawContwowwew);

        if (powewpway_tabwe->usTabweSize >= sizeof(ATOM_PPWIB_POWEWPWAYTABWE3)) {
		const ATOM_PPWIB_POWEWPWAYTABWE3 *powewpway_tabwe3 =
			(const ATOM_PPWIB_POWEWPWAYTABWE3 *)powewpway_tabwe;

		if (0 == we16_to_cpu(powewpway_tabwe3->usFanTabweOffset)) {
			hwmgw->thewmaw_contwowwew.use_hw_fan_contwow = 1;
			wetuwn 0;
		} ewse {
			const ATOM_PPWIB_FANTABWE *fan_tabwe =
				(const ATOM_PPWIB_FANTABWE *)(((unsigned wong)powewpway_tabwe) +
							      we16_to_cpu(powewpway_tabwe3->usFanTabweOffset));

			if (1 <= fan_tabwe->ucFanTabweFowmat) {
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTHyst =
					fan_tabwe->ucTHyst;
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin =
					we16_to_cpu(fan_tabwe->usTMin);
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed =
					we16_to_cpu(fan_tabwe->usTMed);
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTHigh =
					we16_to_cpu(fan_tabwe->usTHigh);
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin =
					we16_to_cpu(fan_tabwe->usPWMMin);
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed =
					we16_to_cpu(fan_tabwe->usPWMMed);
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMHigh =
					we16_to_cpu(fan_tabwe->usPWMHigh);
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax = 10900;
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwCycweDeway = 100000;

				phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					    PHM_PwatfowmCaps_MicwocodeFanContwow);
			}

			if (2 <= fan_tabwe->ucFanTabweFowmat) {
				const ATOM_PPWIB_FANTABWE2 *fan_tabwe2 =
					(const ATOM_PPWIB_FANTABWE2 *)(((unsigned wong)powewpway_tabwe) +
								       we16_to_cpu(powewpway_tabwe3->usFanTabweOffset));
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax =
					we16_to_cpu(fan_tabwe2->usTMax);
			}

			if (3 <= fan_tabwe->ucFanTabweFowmat) {
				const ATOM_PPWIB_FANTABWE3 *fan_tabwe3 =
					(const ATOM_PPWIB_FANTABWE3 *) (((unsigned wong)powewpway_tabwe) +
									we16_to_cpu(powewpway_tabwe3->usFanTabweOffset));

				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucFanContwowMode =
					fan_tabwe3->ucFanContwowMode;

				if ((3 == fan_tabwe->ucFanTabweFowmat) &&
				    (0x67B1 == adev->pdev->device))
					hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanPWM =
						47;
				ewse
					hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanPWM =
						we16_to_cpu(fan_tabwe3->usFanPWMMax);

				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtFanOutputSensitivity =
					4836;
				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity =
					we16_to_cpu(fan_tabwe3->usFanOutputSensitivity);
			}

			if (6 <= fan_tabwe->ucFanTabweFowmat) {
				const ATOM_PPWIB_FANTABWE4 *fan_tabwe4 =
					(const ATOM_PPWIB_FANTABWE4 *)(((unsigned wong)powewpway_tabwe) +
								       we16_to_cpu(powewpway_tabwe3->usFanTabweOffset));

				phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					    PHM_PwatfowmCaps_FanSpeedInTabweIsWPM);

				hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanWPM =
					we16_to_cpu(fan_tabwe4->usFanWPMMax);
			}

			if (7 <= fan_tabwe->ucFanTabweFowmat) {
				const ATOM_PPWIB_FANTABWE5 *fan_tabwe5 =
					(const ATOM_PPWIB_FANTABWE5 *)(((unsigned wong)powewpway_tabwe) +
								       we16_to_cpu(powewpway_tabwe3->usFanTabweOffset));

				if (0x67A2 == adev->pdev->device ||
				    0x67A9 == adev->pdev->device ||
				    0x67B9 == adev->pdev->device) {
					phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
						    PHM_PwatfowmCaps_GeminiWeguwatowFanContwowSuppowt);
					hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanCuwwentWow =
						we16_to_cpu(fan_tabwe5->usFanCuwwentWow);
					hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanCuwwentHigh =
						we16_to_cpu(fan_tabwe5->usFanCuwwentHigh);
					hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanWPMWow =
						we16_to_cpu(fan_tabwe5->usFanWPMWow);
					hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanWPMHigh =
						we16_to_cpu(fan_tabwe5->usFanWPMHigh);
				}
			}
		}
	}

	wetuwn 0;
}

static int init_ovewdwive_wimits_V1_4(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe,
			const ATOM_FIWMWAWE_INFO_V1_4 *fw_info)
{
	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock =
				we32_to_cpu(fw_info->uwASICMaxEngineCwock);

	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock =
				we32_to_cpu(fw_info->uwASICMaxMemowyCwock);

	hwmgw->pwatfowm_descwiptow.maxOvewdwiveVDDC =
		we32_to_cpu(fw_info->uw3DAccewewationEngineCwock) & 0x7FF;

	hwmgw->pwatfowm_descwiptow.minOvewdwiveVDDC =
			   we16_to_cpu(fw_info->usBootUpVDDCVowtage);

	hwmgw->pwatfowm_descwiptow.maxOvewdwiveVDDC =
			   we16_to_cpu(fw_info->usBootUpVDDCVowtage);

	hwmgw->pwatfowm_descwiptow.ovewdwiveVDDCStep = 0;
	wetuwn 0;
}

static int init_ovewdwive_wimits_V2_1(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe,
			const ATOM_FIWMWAWE_INFO_V2_1 *fw_info)
{
	const ATOM_PPWIB_POWEWPWAYTABWE3 *powewpway_tabwe3;
	const ATOM_PPWIB_EXTENDEDHEADEW *headew;

	if (we16_to_cpu(powewpway_tabwe->usTabweSize) <
	    sizeof(ATOM_PPWIB_POWEWPWAYTABWE3))
		wetuwn 0;

	powewpway_tabwe3 = (const ATOM_PPWIB_POWEWPWAYTABWE3 *)powewpway_tabwe;

	if (0 == powewpway_tabwe3->usExtendendedHeadewOffset)
		wetuwn 0;

	headew = (ATOM_PPWIB_EXTENDEDHEADEW *)(((unsigned wong) powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe3->usExtendendedHeadewOffset));

	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock = we32_to_cpu(headew->uwMaxEngineCwock);
	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock = we32_to_cpu(headew->uwMaxMemowyCwock);


	hwmgw->pwatfowm_descwiptow.minOvewdwiveVDDC = 0;
	hwmgw->pwatfowm_descwiptow.maxOvewdwiveVDDC = 0;
	hwmgw->pwatfowm_descwiptow.ovewdwiveVDDCStep = 0;

	wetuwn 0;
}

static int init_ovewdwive_wimits(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	int wesuwt = 0;
	uint8_t fwev, cwev;
	uint16_t size;

	const ATOM_COMMON_TABWE_HEADEW *fw_info = NUWW;

	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock = 0;
	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock = 0;
	hwmgw->pwatfowm_descwiptow.minOvewdwiveVDDC = 0;
	hwmgw->pwatfowm_descwiptow.maxOvewdwiveVDDC = 0;
	hwmgw->pwatfowm_descwiptow.ovewdwiveVDDCStep = 0;

	if (hwmgw->chip_id == CHIP_WAVEN)
		wetuwn 0;

	/* We assume hewe that fw_info is unchanged if this caww faiws.*/
	fw_info = smu_atom_get_data_tabwe(hwmgw->adev,
			 GetIndexIntoMastewTabwe(DATA, FiwmwaweInfo),
			 &size, &fwev, &cwev);

	if ((fw_info->ucTabweFowmatWevision == 1)
	    && (we16_to_cpu(fw_info->usStwuctuweSize) >= sizeof(ATOM_FIWMWAWE_INFO_V1_4)))
		wesuwt = init_ovewdwive_wimits_V1_4(hwmgw,
				powewpway_tabwe,
				(const ATOM_FIWMWAWE_INFO_V1_4 *)fw_info);

	ewse if ((fw_info->ucTabweFowmatWevision == 2)
		 && (we16_to_cpu(fw_info->usStwuctuweSize) >= sizeof(ATOM_FIWMWAWE_INFO_V2_1)))
		wesuwt = init_ovewdwive_wimits_V2_1(hwmgw,
				powewpway_tabwe,
				(const ATOM_FIWMWAWE_INFO_V2_1 *)fw_info);

	wetuwn wesuwt;
}

static int get_uvd_cwock_vowtage_wimit_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct phm_uvd_cwock_vowtage_dependency_tabwe **ptabwe,
		const ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe *tabwe,
		const UVDCwockInfoAwway *awway)
{
	unsigned wong i;
	stwuct phm_uvd_cwock_vowtage_dependency_tabwe *uvd_tabwe;

	uvd_tabwe = kzawwoc(stwuct_size(uvd_tabwe, entwies, tabwe->numEntwies),
			    GFP_KEWNEW);
	if (!uvd_tabwe)
		wetuwn -ENOMEM;

	uvd_tabwe->count = tabwe->numEntwies;

	fow (i = 0; i < tabwe->numEntwies; i++) {
		const UVDCwockInfo *entwy =
			&awway->entwies[tabwe->entwies[i].ucUVDCwockInfoIndex];
		uvd_tabwe->entwies[i].v = (unsigned wong)we16_to_cpu(tabwe->entwies[i].usVowtage);
		uvd_tabwe->entwies[i].vcwk = ((unsigned wong)entwy->ucVCwkHigh << 16)
					 | we16_to_cpu(entwy->usVCwkWow);
		uvd_tabwe->entwies[i].dcwk = ((unsigned wong)entwy->ucDCwkHigh << 16)
					 | we16_to_cpu(entwy->usDCwkWow);
	}

	*ptabwe = uvd_tabwe;

	wetuwn 0;
}

static int get_vce_cwock_vowtage_wimit_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct phm_vce_cwock_vowtage_dependency_tabwe **ptabwe,
		const ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe *tabwe,
		const VCECwockInfoAwway    *awway)
{
	unsigned wong i;
	stwuct phm_vce_cwock_vowtage_dependency_tabwe *vce_tabwe;

	vce_tabwe = kzawwoc(stwuct_size(vce_tabwe, entwies, tabwe->numEntwies),
			    GFP_KEWNEW);
	if (!vce_tabwe)
		wetuwn -ENOMEM;

	vce_tabwe->count = tabwe->numEntwies;
	fow (i = 0; i < tabwe->numEntwies; i++) {
		const VCECwockInfo *entwy = &awway->entwies[tabwe->entwies[i].ucVCECwockInfoIndex];

		vce_tabwe->entwies[i].v = (unsigned wong)we16_to_cpu(tabwe->entwies[i].usVowtage);
		vce_tabwe->entwies[i].evcwk = ((unsigned wong)entwy->ucEVCwkHigh << 16)
					| we16_to_cpu(entwy->usEVCwkWow);
		vce_tabwe->entwies[i].eccwk = ((unsigned wong)entwy->ucECCwkHigh << 16)
					| we16_to_cpu(entwy->usECCwkWow);
	}

	*ptabwe = vce_tabwe;

	wetuwn 0;
}

static int get_samu_cwock_vowtage_wimit_tabwe(stwuct pp_hwmgw *hwmgw,
		 stwuct phm_samu_cwock_vowtage_dependency_tabwe **ptabwe,
		 const ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe *tabwe)
{
	unsigned wong i;
	stwuct phm_samu_cwock_vowtage_dependency_tabwe *samu_tabwe;

	samu_tabwe = kzawwoc(stwuct_size(samu_tabwe, entwies, tabwe->numEntwies),
			     GFP_KEWNEW);
	if (!samu_tabwe)
		wetuwn -ENOMEM;

	samu_tabwe->count = tabwe->numEntwies;

	fow (i = 0; i < tabwe->numEntwies; i++) {
		samu_tabwe->entwies[i].v = (unsigned wong)we16_to_cpu(tabwe->entwies[i].usVowtage);
		samu_tabwe->entwies[i].samcwk = ((unsigned wong)tabwe->entwies[i].ucSAMCwockHigh << 16)
					 | we16_to_cpu(tabwe->entwies[i].usSAMCwockWow);
	}

	*ptabwe = samu_tabwe;

	wetuwn 0;
}

static int get_acp_cwock_vowtage_wimit_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct phm_acp_cwock_vowtage_dependency_tabwe **ptabwe,
		const ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe *tabwe)
{
	unsigned wong i;
	stwuct phm_acp_cwock_vowtage_dependency_tabwe *acp_tabwe;

	acp_tabwe = kzawwoc(stwuct_size(acp_tabwe, entwies, tabwe->numEntwies),
			    GFP_KEWNEW);
	if (!acp_tabwe)
		wetuwn -ENOMEM;

	acp_tabwe->count = (unsigned wong)tabwe->numEntwies;

	fow (i = 0; i < tabwe->numEntwies; i++) {
		acp_tabwe->entwies[i].v = (unsigned wong)we16_to_cpu(tabwe->entwies[i].usVowtage);
		acp_tabwe->entwies[i].acpcwk = ((unsigned wong)tabwe->entwies[i].ucACPCwockHigh << 16)
					 | we16_to_cpu(tabwe->entwies[i].usACPCwockWow);
	}

	*ptabwe = acp_tabwe;

	wetuwn 0;
}

static int init_cwock_vowtage_dependency(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *tabwe;
	ATOM_PPWIB_Cwock_Vowtage_Wimit_Tabwe *wimit_tabwe;
	int wesuwt = 0;

	uint16_t vce_cwock_info_awway_offset;
	uint16_t uvd_cwock_info_awway_offset;
	uint16_t tabwe_offset;

	hwmgw->dyn_state.vddc_dependency_on_scwk = NUWW;
	hwmgw->dyn_state.vddci_dependency_on_mcwk = NUWW;
	hwmgw->dyn_state.vddc_dependency_on_mcwk = NUWW;
	hwmgw->dyn_state.vddc_dep_on_daw_pwww = NUWW;
	hwmgw->dyn_state.mvdd_dependency_on_mcwk = NUWW;
	hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe = NUWW;
	hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe = NUWW;
	hwmgw->dyn_state.samu_cwock_vowtage_dependency_tabwe = NUWW;
	hwmgw->dyn_state.acp_cwock_vowtage_dependency_tabwe = NUWW;
	hwmgw->dyn_state.ppm_pawametew_tabwe = NUWW;
	hwmgw->dyn_state.vdd_gfx_dependency_on_scwk = NUWW;

	vce_cwock_info_awway_offset = get_vce_cwock_info_awway_offset(
						hwmgw, powewpway_tabwe);
	tabwe_offset = get_vce_cwock_vowtage_wimit_tabwe_offset(hwmgw,
						powewpway_tabwe);
	if (vce_cwock_info_awway_offset > 0 && tabwe_offset > 0) {
		const VCECwockInfoAwway *awway = (const VCECwockInfoAwway *)
				(((unsigned wong) powewpway_tabwe) +
				vce_cwock_info_awway_offset);
		const ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe *tabwe =
				(const ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe *)
				(((unsigned wong) powewpway_tabwe) + tabwe_offset);
		wesuwt = get_vce_cwock_vowtage_wimit_tabwe(hwmgw,
				&hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe,
				tabwe, awway);
	}

	uvd_cwock_info_awway_offset = get_uvd_cwock_info_awway_offset(hwmgw, powewpway_tabwe);
	tabwe_offset = get_uvd_cwock_vowtage_wimit_tabwe_offset(hwmgw, powewpway_tabwe);

	if (uvd_cwock_info_awway_offset > 0 && tabwe_offset > 0) {
		const UVDCwockInfoAwway *awway = (const UVDCwockInfoAwway *)
				(((unsigned wong) powewpway_tabwe) +
				uvd_cwock_info_awway_offset);
		const ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe *ptabwe =
				(const ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe *)
				(((unsigned wong) powewpway_tabwe) + tabwe_offset);
		wesuwt = get_uvd_cwock_vowtage_wimit_tabwe(hwmgw,
				&hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe, ptabwe, awway);
	}

	tabwe_offset = get_samu_cwock_vowtage_wimit_tabwe_offset(hwmgw,
							    powewpway_tabwe);

	if (tabwe_offset > 0) {
		const ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe *ptabwe =
				(const ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe *)
				(((unsigned wong) powewpway_tabwe) + tabwe_offset);
		wesuwt = get_samu_cwock_vowtage_wimit_tabwe(hwmgw,
				&hwmgw->dyn_state.samu_cwock_vowtage_dependency_tabwe, ptabwe);
	}

	tabwe_offset = get_acp_cwock_vowtage_wimit_tabwe_offset(hwmgw,
							     powewpway_tabwe);

	if (tabwe_offset > 0) {
		const ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe *ptabwe =
				(const ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe *)
				(((unsigned wong) powewpway_tabwe) + tabwe_offset);
		wesuwt = get_acp_cwock_vowtage_wimit_tabwe(hwmgw,
				&hwmgw->dyn_state.acp_cwock_vowtage_dependency_tabwe, ptabwe);
	}

	tabwe_offset = get_cacp_tdp_tabwe_offset(hwmgw, powewpway_tabwe);
	if (tabwe_offset > 0) {
		UCHAW wev_id = *(UCHAW *)(((unsigned wong)powewpway_tabwe) + tabwe_offset);

		if (wev_id > 0) {
			const ATOM_PPWIB_POWEWTUNE_Tabwe_V1 *tune_tabwe =
				(const ATOM_PPWIB_POWEWTUNE_Tabwe_V1 *)
				(((unsigned wong) powewpway_tabwe) + tabwe_offset);
			wesuwt = get_cac_tdp_tabwe(hwmgw, &hwmgw->dyn_state.cac_dtp_tabwe,
				&tune_tabwe->powew_tune_tabwe,
				we16_to_cpu(tune_tabwe->usMaximumPowewDewivewyWimit));
			hwmgw->dyn_state.cac_dtp_tabwe->usDefauwtTawgetOpewatingTemp =
				we16_to_cpu(tune_tabwe->usTjMax);
		} ewse {
			const ATOM_PPWIB_POWEWTUNE_Tabwe *tune_tabwe =
				(const ATOM_PPWIB_POWEWTUNE_Tabwe *)
				(((unsigned wong) powewpway_tabwe) + tabwe_offset);
			wesuwt = get_cac_tdp_tabwe(hwmgw,
				&hwmgw->dyn_state.cac_dtp_tabwe,
				&tune_tabwe->powew_tune_tabwe, 255);
		}
	}

	if (we16_to_cpu(powewpway_tabwe->usTabweSize) >=
		sizeof(ATOM_PPWIB_POWEWPWAYTABWE4)) {
		const ATOM_PPWIB_POWEWPWAYTABWE4 *powewpway_tabwe4 =
				(const ATOM_PPWIB_POWEWPWAYTABWE4 *)powewpway_tabwe;
		if (0 != powewpway_tabwe4->usVddcDependencyOnSCWKOffset) {
			tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(((unsigned wong) powewpway_tabwe4) +
				 we16_to_cpu(powewpway_tabwe4->usVddcDependencyOnSCWKOffset));
			wesuwt = get_cwock_vowtage_dependency_tabwe(hwmgw,
				&hwmgw->dyn_state.vddc_dependency_on_scwk, tabwe);
		}

		if (wesuwt == 0 && (0 != powewpway_tabwe4->usVddciDependencyOnMCWKOffset)) {
			tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(((unsigned wong) powewpway_tabwe4) +
				 we16_to_cpu(powewpway_tabwe4->usVddciDependencyOnMCWKOffset));
			wesuwt = get_cwock_vowtage_dependency_tabwe(hwmgw,
				&hwmgw->dyn_state.vddci_dependency_on_mcwk, tabwe);
		}

		if (wesuwt == 0 && (0 != powewpway_tabwe4->usVddcDependencyOnMCWKOffset)) {
			tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(((unsigned wong) powewpway_tabwe4) +
				 we16_to_cpu(powewpway_tabwe4->usVddcDependencyOnMCWKOffset));
			wesuwt = get_cwock_vowtage_dependency_tabwe(hwmgw,
				&hwmgw->dyn_state.vddc_dependency_on_mcwk, tabwe);
		}

		if (wesuwt == 0 && (0 != powewpway_tabwe4->usMaxCwockVowtageOnDCOffset)) {
			wimit_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Wimit_Tabwe *)
				(((unsigned wong) powewpway_tabwe4) +
				 we16_to_cpu(powewpway_tabwe4->usMaxCwockVowtageOnDCOffset));
			wesuwt = get_cwock_vowtage_wimit(hwmgw,
				&hwmgw->dyn_state.max_cwock_vowtage_on_dc, wimit_tabwe);
		}

		if (wesuwt == 0 && (NUWW != hwmgw->dyn_state.vddc_dependency_on_mcwk) &&
			(0 != hwmgw->dyn_state.vddc_dependency_on_mcwk->count))
			wesuwt = get_vawid_cwk(hwmgw, &hwmgw->dyn_state.vawid_mcwk_vawues,
					hwmgw->dyn_state.vddc_dependency_on_mcwk);

		if(wesuwt == 0 && (NUWW != hwmgw->dyn_state.vddc_dependency_on_scwk) &&
			(0 != hwmgw->dyn_state.vddc_dependency_on_scwk->count))
			wesuwt = get_vawid_cwk(hwmgw,
				&hwmgw->dyn_state.vawid_scwk_vawues,
				hwmgw->dyn_state.vddc_dependency_on_scwk);

		if (wesuwt == 0 && (0 != powewpway_tabwe4->usMvddDependencyOnMCWKOffset)) {
			tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(((unsigned wong) powewpway_tabwe4) +
				 we16_to_cpu(powewpway_tabwe4->usMvddDependencyOnMCWKOffset));
			wesuwt = get_cwock_vowtage_dependency_tabwe(hwmgw,
				&hwmgw->dyn_state.mvdd_dependency_on_mcwk, tabwe);
		}
	}

	tabwe_offset = get_scwk_vdd_gfx_cwock_vowtage_dependency_tabwe_offset(hwmgw,
								powewpway_tabwe);

	if (tabwe_offset > 0) {
		tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
			(((unsigned wong) powewpway_tabwe) + tabwe_offset);
		wesuwt = get_cwock_vowtage_dependency_tabwe(hwmgw,
			&hwmgw->dyn_state.vdd_gfx_dependency_on_scwk, tabwe);
	}

	wetuwn wesuwt;
}

static int get_cac_weakage_tabwe(stwuct pp_hwmgw *hwmgw,
				 stwuct phm_cac_weakage_tabwe **ptabwe,
				const ATOM_PPWIB_CAC_Weakage_Tabwe *tabwe)
{
	stwuct phm_cac_weakage_tabwe  *cac_weakage_tabwe;
	unsigned wong i;

	if (!hwmgw || !tabwe || !ptabwe)
		wetuwn -EINVAW;

	cac_weakage_tabwe = kzawwoc(stwuct_size(cac_weakage_tabwe, entwies, tabwe->ucNumEntwies),
				    GFP_KEWNEW);
	if (!cac_weakage_tabwe)
		wetuwn -ENOMEM;

	cac_weakage_tabwe->count = (UWONG)tabwe->ucNumEntwies;

	fow (i = 0; i < cac_weakage_tabwe->count; i++) {
		if (phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
				PHM_PwatfowmCaps_EVV)) {
			cac_weakage_tabwe->entwies[i].Vddc1 = we16_to_cpu(tabwe->entwies[i].usVddc1);
			cac_weakage_tabwe->entwies[i].Vddc2 = we16_to_cpu(tabwe->entwies[i].usVddc2);
			cac_weakage_tabwe->entwies[i].Vddc3 = we16_to_cpu(tabwe->entwies[i].usVddc3);
		} ewse {
			cac_weakage_tabwe->entwies[i].Vddc    = we16_to_cpu(tabwe->entwies[i].usVddc);
			cac_weakage_tabwe->entwies[i].Weakage = we32_to_cpu(tabwe->entwies[i].uwWeakageVawue);
		}
	}

	*ptabwe = cac_weakage_tabwe;

	wetuwn 0;
}

static int get_pwatfowm_powew_management_tabwe(stwuct pp_hwmgw *hwmgw,
			ATOM_PPWIB_PPM_Tabwe *atom_ppm_tabwe)
{
	stwuct phm_ppm_tabwe *ptw = kzawwoc(sizeof(stwuct phm_ppm_tabwe), GFP_KEWNEW);

	if (NUWW == ptw)
		wetuwn -ENOMEM;

	ptw->ppm_design            = atom_ppm_tabwe->ucPpmDesign;
	ptw->cpu_cowe_numbew        = we16_to_cpu(atom_ppm_tabwe->usCpuCoweNumbew);
	ptw->pwatfowm_tdp          = we32_to_cpu(atom_ppm_tabwe->uwPwatfowmTDP);
	ptw->smaww_ac_pwatfowm_tdp   = we32_to_cpu(atom_ppm_tabwe->uwSmawwACPwatfowmTDP);
	ptw->pwatfowm_tdc          = we32_to_cpu(atom_ppm_tabwe->uwPwatfowmTDC);
	ptw->smaww_ac_pwatfowm_tdc   = we32_to_cpu(atom_ppm_tabwe->uwSmawwACPwatfowmTDC);
	ptw->apu_tdp               = we32_to_cpu(atom_ppm_tabwe->uwApuTDP);
	ptw->dgpu_tdp              = we32_to_cpu(atom_ppm_tabwe->uwDGpuTDP);
	ptw->dgpu_uwv_powew         = we32_to_cpu(atom_ppm_tabwe->uwDGpuUwvPowew);
	ptw->tj_max                = we32_to_cpu(atom_ppm_tabwe->uwTjmax);
	hwmgw->dyn_state.ppm_pawametew_tabwe = ptw;

	wetuwn 0;
}

static int init_dpm2_pawametews(stwuct pp_hwmgw *hwmgw,
			const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	int wesuwt = 0;

	if (we16_to_cpu(powewpway_tabwe->usTabweSize) >=
	    sizeof(ATOM_PPWIB_POWEWPWAYTABWE5)) {
		const  ATOM_PPWIB_POWEWPWAYTABWE5 *ptabwe5 =
				(const ATOM_PPWIB_POWEWPWAYTABWE5 *)powewpway_tabwe;
		const  ATOM_PPWIB_POWEWPWAYTABWE4 *ptabwe4 =
				(const ATOM_PPWIB_POWEWPWAYTABWE4 *)
				(&ptabwe5->basicTabwe4);
		const  ATOM_PPWIB_POWEWPWAYTABWE3 *ptabwe3 =
				(const ATOM_PPWIB_POWEWPWAYTABWE3 *)
				(&ptabwe4->basicTabwe3);
		const  ATOM_PPWIB_EXTENDEDHEADEW  *extended_headew;
		uint16_t tabwe_offset;
		ATOM_PPWIB_PPM_Tabwe *atom_ppm_tabwe;

		hwmgw->pwatfowm_descwiptow.TDPWimit     = we32_to_cpu(ptabwe5->uwTDPWimit);
		hwmgw->pwatfowm_descwiptow.neawTDPWimit = we32_to_cpu(ptabwe5->uwNeawTDPWimit);

		hwmgw->pwatfowm_descwiptow.TDPODWimit   = we16_to_cpu(ptabwe5->usTDPODWimit);
		hwmgw->pwatfowm_descwiptow.TDPAdjustment = 0;

		hwmgw->pwatfowm_descwiptow.VidAdjustment = 0;
		hwmgw->pwatfowm_descwiptow.VidAdjustmentPowawity = 0;
		hwmgw->pwatfowm_descwiptow.VidMinWimit     = 0;
		hwmgw->pwatfowm_descwiptow.VidMaxWimit     = 1500000;
		hwmgw->pwatfowm_descwiptow.VidStep         = 6250;

		hwmgw->pwatfowm_descwiptow.neawTDPWimitAdjusted = we32_to_cpu(ptabwe5->uwNeawTDPWimit);

		if (hwmgw->pwatfowm_descwiptow.TDPODWimit != 0)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_PowewContwow);

		hwmgw->pwatfowm_descwiptow.SQWampingThweshowd = we32_to_cpu(ptabwe5->uwSQWampingThweshowd);

		hwmgw->pwatfowm_descwiptow.CACWeakage = we32_to_cpu(ptabwe5->uwCACWeakage);

		hwmgw->dyn_state.cac_weakage_tabwe = NUWW;

		if (0 != ptabwe5->usCACWeakageTabweOffset) {
			const ATOM_PPWIB_CAC_Weakage_Tabwe *pCAC_weakage_tabwe =
				(ATOM_PPWIB_CAC_Weakage_Tabwe *)(((unsigned wong)ptabwe5) +
				we16_to_cpu(ptabwe5->usCACWeakageTabweOffset));
			wesuwt = get_cac_weakage_tabwe(hwmgw,
				&hwmgw->dyn_state.cac_weakage_tabwe, pCAC_weakage_tabwe);
		}

		hwmgw->pwatfowm_descwiptow.WoadWineSwope = we16_to_cpu(ptabwe5->usWoadWineSwope);

		hwmgw->dyn_state.ppm_pawametew_tabwe = NUWW;

		if (0 != ptabwe3->usExtendendedHeadewOffset) {
			extended_headew = (const ATOM_PPWIB_EXTENDEDHEADEW *)
					(((unsigned wong)powewpway_tabwe) +
					we16_to_cpu(ptabwe3->usExtendendedHeadewOffset));
			if ((extended_headew->usPPMTabweOffset > 0) &&
				we16_to_cpu(extended_headew->usSize) >=
				    SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V5) {
				tabwe_offset = we16_to_cpu(extended_headew->usPPMTabweOffset);
				atom_ppm_tabwe = (ATOM_PPWIB_PPM_Tabwe *)
					(((unsigned wong)powewpway_tabwe) + tabwe_offset);
				if (0 == get_pwatfowm_powew_management_tabwe(hwmgw, atom_ppm_tabwe))
					phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
						PHM_PwatfowmCaps_EnabwePwatfowmPowewManagement);
			}
		}
	}
	wetuwn wesuwt;
}

static int init_phase_shedding_tabwe(stwuct pp_hwmgw *hwmgw,
		const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe)
{
	if (we16_to_cpu(powewpway_tabwe->usTabweSize) >=
	    sizeof(ATOM_PPWIB_POWEWPWAYTABWE4)) {
		const ATOM_PPWIB_POWEWPWAYTABWE4 *powewpway_tabwe4 =
				(const ATOM_PPWIB_POWEWPWAYTABWE4 *)powewpway_tabwe;

		if (0 != powewpway_tabwe4->usVddcPhaseShedWimitsTabweOffset) {
			const ATOM_PPWIB_PhaseSheddingWimits_Tabwe *ptabwe =
				(ATOM_PPWIB_PhaseSheddingWimits_Tabwe *)
				(((unsigned wong)powewpway_tabwe4) +
				we16_to_cpu(powewpway_tabwe4->usVddcPhaseShedWimitsTabweOffset));
			stwuct phm_phase_shedding_wimits_tabwe *tabwe;
			unsigned wong i;


			tabwe = kzawwoc(stwuct_size(tabwe, entwies, ptabwe->ucNumEntwies),
					GFP_KEWNEW);
			if (!tabwe)
				wetuwn -ENOMEM;

			tabwe->count = (unsigned wong)ptabwe->ucNumEntwies;

			fow (i = 0; i < tabwe->count; i++) {
				tabwe->entwies[i].Vowtage = (unsigned wong)we16_to_cpu(ptabwe->entwies[i].usVowtage);
				tabwe->entwies[i].Scwk    = ((unsigned wong)ptabwe->entwies[i].ucScwkHigh << 16)
							| we16_to_cpu(ptabwe->entwies[i].usScwkWow);
				tabwe->entwies[i].Mcwk    = ((unsigned wong)ptabwe->entwies[i].ucMcwkHigh << 16)
							| we16_to_cpu(ptabwe->entwies[i].usMcwkWow);
			}
			hwmgw->dyn_state.vddc_phase_shed_wimits_tabwe = tabwe;
		}
	}

	wetuwn 0;
}

static int get_numbew_of_vce_state_tabwe_entwies(
						  stwuct pp_hwmgw *hwmgw)
{
	const ATOM_PPWIB_POWEWPWAYTABWE *tabwe =
					     get_powewpway_tabwe(hwmgw);
	const ATOM_PPWIB_VCE_State_Tabwe *vce_tabwe =
				    get_vce_state_tabwe(hwmgw, tabwe);

	if (vce_tabwe)
		wetuwn vce_tabwe->numEntwies;

	wetuwn 0;
}

static int get_vce_state_tabwe_entwy(stwuct pp_hwmgw *hwmgw,
							unsigned wong i,
							stwuct amd_vce_state *vce_state,
							void **cwock_info,
							unsigned wong *fwag)
{
	const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe = get_powewpway_tabwe(hwmgw);

	const ATOM_PPWIB_VCE_State_Tabwe *vce_state_tabwe = get_vce_state_tabwe(hwmgw, powewpway_tabwe);

	unsigned showt vce_cwock_info_awway_offset = get_vce_cwock_info_awway_offset(hwmgw, powewpway_tabwe);

	const VCECwockInfoAwway *vce_cwock_info_awway = (const VCECwockInfoAwway *)(((unsigned wong) powewpway_tabwe) + vce_cwock_info_awway_offset);

	const CwockInfoAwway *cwock_awways = (CwockInfoAwway *)(((unsigned wong)powewpway_tabwe) +
								we16_to_cpu(powewpway_tabwe->usCwockInfoAwwayOffset));

	const ATOM_PPWIB_VCE_State_Wecowd *wecowd = &vce_state_tabwe->entwies[i];

	const VCECwockInfo *vce_cwock_info = &vce_cwock_info_awway->entwies[wecowd->ucVCECwockInfoIndex];

	unsigned wong cwockInfoIndex = wecowd->ucCwockInfoIndex & 0x3F;

	*fwag = (wecowd->ucCwockInfoIndex >> NUM_BITS_CWOCK_INFO_AWWAY_INDEX);

	vce_state->evcwk = ((uint32_t)vce_cwock_info->ucEVCwkHigh << 16) | we16_to_cpu(vce_cwock_info->usEVCwkWow);
	vce_state->eccwk = ((uint32_t)vce_cwock_info->ucECCwkHigh << 16) | we16_to_cpu(vce_cwock_info->usECCwkWow);

	*cwock_info = (void *)((unsigned wong)(cwock_awways->cwockInfo) + (cwockInfoIndex * cwock_awways->ucEntwySize));

	wetuwn 0;
}


static int pp_tabwes_initiawize(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt;
	const ATOM_PPWIB_POWEWPWAYTABWE *powewpway_tabwe;

	if (hwmgw->chip_id == CHIP_WAVEN)
		wetuwn 0;

	hwmgw->need_pp_tabwe_upwoad = twue;

	powewpway_tabwe = get_powewpway_tabwe(hwmgw);

	wesuwt = init_powewpway_tabwes(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_powewpway_tabwes faiwed", wetuwn wesuwt);

	wesuwt = set_pwatfowm_caps(hwmgw,
				we32_to_cpu(powewpway_tabwe->uwPwatfowmCaps));

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "set_pwatfowm_caps faiwed", wetuwn wesuwt);

	wesuwt = init_thewmaw_contwowwew(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_thewmaw_contwowwew faiwed", wetuwn wesuwt);

	wesuwt = init_ovewdwive_wimits(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_ovewdwive_wimits faiwed", wetuwn wesuwt);

	wesuwt = init_cwock_vowtage_dependency(hwmgw,
					       powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_cwock_vowtage_dependency faiwed", wetuwn wesuwt);

	wesuwt = init_dpm2_pawametews(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_dpm2_pawametews faiwed", wetuwn wesuwt);

	wesuwt = init_phase_shedding_tabwe(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_phase_shedding_tabwe faiwed", wetuwn wesuwt);

	wetuwn wesuwt;
}

static int pp_tabwes_uninitiawize(stwuct pp_hwmgw *hwmgw)
{
	if (hwmgw->chip_id == CHIP_WAVEN)
		wetuwn 0;

	kfwee(hwmgw->dyn_state.vddc_dependency_on_scwk);
	hwmgw->dyn_state.vddc_dependency_on_scwk = NUWW;

	kfwee(hwmgw->dyn_state.vddci_dependency_on_mcwk);
	hwmgw->dyn_state.vddci_dependency_on_mcwk = NUWW;

	kfwee(hwmgw->dyn_state.vddc_dependency_on_mcwk);
	hwmgw->dyn_state.vddc_dependency_on_mcwk = NUWW;

	kfwee(hwmgw->dyn_state.mvdd_dependency_on_mcwk);
	hwmgw->dyn_state.mvdd_dependency_on_mcwk = NUWW;

	kfwee(hwmgw->dyn_state.vawid_mcwk_vawues);
	hwmgw->dyn_state.vawid_mcwk_vawues = NUWW;

	kfwee(hwmgw->dyn_state.vawid_scwk_vawues);
	hwmgw->dyn_state.vawid_scwk_vawues = NUWW;

	kfwee(hwmgw->dyn_state.cac_weakage_tabwe);
	hwmgw->dyn_state.cac_weakage_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.vddc_phase_shed_wimits_tabwe);
	hwmgw->dyn_state.vddc_phase_shed_wimits_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe);
	hwmgw->dyn_state.vce_cwock_vowtage_dependency_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe);
	hwmgw->dyn_state.uvd_cwock_vowtage_dependency_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.samu_cwock_vowtage_dependency_tabwe);
	hwmgw->dyn_state.samu_cwock_vowtage_dependency_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.acp_cwock_vowtage_dependency_tabwe);
	hwmgw->dyn_state.acp_cwock_vowtage_dependency_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.cac_dtp_tabwe);
	hwmgw->dyn_state.cac_dtp_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.ppm_pawametew_tabwe);
	hwmgw->dyn_state.ppm_pawametew_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.vdd_gfx_dependency_on_scwk);
	hwmgw->dyn_state.vdd_gfx_dependency_on_scwk = NUWW;

	wetuwn 0;
}

const stwuct pp_tabwe_func pptabwe_funcs = {
	.pptabwe_init = pp_tabwes_initiawize,
	.pptabwe_fini = pp_tabwes_uninitiawize,
	.pptabwe_get_numbew_of_vce_state_tabwe_entwies =
				get_numbew_of_vce_state_tabwe_entwies,
	.pptabwe_get_vce_state_tabwe_entwy =
						get_vce_state_tabwe_entwy,
};

