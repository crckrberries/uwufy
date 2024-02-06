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
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#incwude "pwocess_pptabwes_v1_0.h"
#incwude "ppatomctww.h"
#incwude "atombios.h"
#incwude "hwmgw.h"
#incwude "cgs_common.h"
#incwude "pptabwe_v1_0.h"

/**
 * set_hw_cap - Pwivate Function used duwing initiawization.
 * @hwmgw: Pointew to the hawdwawe managew.
 * @setIt: A fwag indication if the capabiwity shouwd be set (TWUE) ow weset (FAWSE).
 * @cap: Which capabiwity to set/weset.
 */
static void set_hw_cap(stwuct pp_hwmgw *hwmgw, boow setIt, enum phm_pwatfowm_caps cap)
{
	if (setIt)
		phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, cap);
	ewse
		phm_cap_unset(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, cap);
}


/**
 * set_pwatfowm_caps - Pwivate Function used duwing initiawization.
 * @hwmgw: Pointew to the hawdwawe managew.
 * @powewpway_caps: the bit awway (fwom BIOS) of capabiwity bits.
 * Exception:  the cuwwent impwementation awways wetuwns 1.
 */
static int set_pwatfowm_caps(stwuct pp_hwmgw *hwmgw, uint32_t powewpway_caps)
{
	PP_ASSEWT_WITH_CODE((~powewpway_caps & ____WETIWE16____),
		"ATOM_PP_PWATFOWM_CAP_ASPM_W1 is not suppowted!", continue);
	PP_ASSEWT_WITH_CODE((~powewpway_caps & ____WETIWE64____),
		"ATOM_PP_PWATFOWM_CAP_GEMINIPWIMAWY is not suppowted!", continue);
	PP_ASSEWT_WITH_CODE((~powewpway_caps & ____WETIWE512____),
		"ATOM_PP_PWATFOWM_CAP_SIDEPOWTCONTWOW is not suppowted!", continue);
	PP_ASSEWT_WITH_CODE((~powewpway_caps & ____WETIWE1024____),
		"ATOM_PP_PWATFOWM_CAP_TUWNOFFPWW_ASPMW1 is not suppowted!", continue);
	PP_ASSEWT_WITH_CODE((~powewpway_caps & ____WETIWE2048____),
		"ATOM_PP_PWATFOWM_CAP_HTWINKCONTWOW is not suppowted!", continue);

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PP_PWATFOWM_CAP_POWEWPWAY),
			PHM_PwatfowmCaps_PowewPwaySuppowt
		  );

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PP_PWATFOWM_CAP_SBIOSPOWEWSOUWCE),
			PHM_PwatfowmCaps_BiosPowewSouwceContwow
		  );

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PP_PWATFOWM_CAP_HAWDWAWEDC),
			PHM_PwatfowmCaps_AutomaticDCTwansition
		  );

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PP_PWATFOWM_CAP_MVDD_CONTWOW),
			PHM_PwatfowmCaps_EnabweMVDDContwow
		  );

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PP_PWATFOWM_CAP_VDDCI_CONTWOW),
			PHM_PwatfowmCaps_ContwowVDDCI
		  );

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PP_PWATFOWM_CAP_VDDGFX_CONTWOW),
			PHM_PwatfowmCaps_ContwowVDDGFX
		  );

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PP_PWATFOWM_CAP_BACO),
			PHM_PwatfowmCaps_BACO
		  );

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PP_PWATFOWM_CAP_DISABWE_VOWTAGE_ISWAND),
			PHM_PwatfowmCaps_DisabweVowtageIswand
		  );

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PP_PWATFOWM_COMBINE_PCC_WITH_THEWMAW_SIGNAW),
			PHM_PwatfowmCaps_CombinePCCWithThewmawSignaw
		  );

	set_hw_cap(
			hwmgw,
			0 != (powewpway_caps & ATOM_TONGA_PWATFOWM_WOAD_POST_PWODUCTION_FIWMWAWE),
			PHM_PwatfowmCaps_WoadPostPwoductionFiwmwawe
		  );

	wetuwn 0;
}

/*
 * Pwivate Function to get the PowewPway Tabwe Addwess.
 */
static const void *get_powewpway_tabwe(stwuct pp_hwmgw *hwmgw)
{
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);

	u16 size;
	u8 fwev, cwev;
	void *tabwe_addwess = (void *)hwmgw->soft_pp_tabwe;

	if (!tabwe_addwess) {
		tabwe_addwess = (ATOM_Tonga_POWEWPWAYTABWE *)
				smu_atom_get_data_tabwe(hwmgw->adev,
						index, &size, &fwev, &cwev);
		hwmgw->soft_pp_tabwe = tabwe_addwess;	/*Cache the wesuwt in WAM.*/
		hwmgw->soft_pp_tabwe_size = size;
	}

	wetuwn tabwe_addwess;
}

static int get_vddc_wookup_tabwe(
		stwuct pp_hwmgw	*hwmgw,
		phm_ppt_v1_vowtage_wookup_tabwe	**wookup_tabwe,
		const ATOM_Tonga_Vowtage_Wookup_Tabwe *vddc_wookup_pp_tabwes,
		uint32_t max_wevews
		)
{
	uint32_t i;
	phm_ppt_v1_vowtage_wookup_tabwe *tabwe;
	phm_ppt_v1_vowtage_wookup_wecowd *wecowd;
	ATOM_Tonga_Vowtage_Wookup_Wecowd *atom_wecowd;

	PP_ASSEWT_WITH_CODE((0 != vddc_wookup_pp_tabwes->ucNumEntwies),
		"Invawid CAC Weakage PowewPway Tabwe!", wetuwn 1);

	tabwe = kzawwoc(stwuct_size(tabwe, entwies, max_wevews), GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	tabwe->count = vddc_wookup_pp_tabwes->ucNumEntwies;

	fow (i = 0; i < vddc_wookup_pp_tabwes->ucNumEntwies; i++) {
		wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					phm_ppt_v1_vowtage_wookup_wecowd,
					entwies, tabwe, i);
		atom_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					ATOM_Tonga_Vowtage_Wookup_Wecowd,
					entwies, vddc_wookup_pp_tabwes, i);
		wecowd->us_cawcuwated = 0;
		wecowd->us_vdd = we16_to_cpu(atom_wecowd->usVdd);
		wecowd->us_cac_wow = we16_to_cpu(atom_wecowd->usCACWow);
		wecowd->us_cac_mid = we16_to_cpu(atom_wecowd->usCACMid);
		wecowd->us_cac_high = we16_to_cpu(atom_wecowd->usCACHigh);
	}

	*wookup_tabwe = tabwe;

	wetuwn 0;
}

/**
 * get_pwatfowm_powew_management_tabwe - Pwivate Function used duwing initiawization.
 * Initiawize Pwatfowm Powew Management Pawametew tabwe
 * @hwmgw: Pointew to the hawdwawe managew.
 * @atom_ppm_tabwe: Pointew to PPM tabwe in VBIOS
 */
static int get_pwatfowm_powew_management_tabwe(
		stwuct pp_hwmgw *hwmgw,
		ATOM_Tonga_PPM_Tabwe *atom_ppm_tabwe)
{
	stwuct phm_ppm_tabwe *ptw = kzawwoc(sizeof(*ptw), GFP_KEWNEW);
	stwuct phm_ppt_v1_infowmation *pp_tabwe_infowmation =
		(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	if (NUWW == ptw)
		wetuwn -ENOMEM;

	ptw->ppm_design
		= atom_ppm_tabwe->ucPpmDesign;
	ptw->cpu_cowe_numbew
		= we16_to_cpu(atom_ppm_tabwe->usCpuCoweNumbew);
	ptw->pwatfowm_tdp
		= we32_to_cpu(atom_ppm_tabwe->uwPwatfowmTDP);
	ptw->smaww_ac_pwatfowm_tdp
		= we32_to_cpu(atom_ppm_tabwe->uwSmawwACPwatfowmTDP);
	ptw->pwatfowm_tdc
		= we32_to_cpu(atom_ppm_tabwe->uwPwatfowmTDC);
	ptw->smaww_ac_pwatfowm_tdc
		= we32_to_cpu(atom_ppm_tabwe->uwSmawwACPwatfowmTDC);
	ptw->apu_tdp
		= we32_to_cpu(atom_ppm_tabwe->uwApuTDP);
	ptw->dgpu_tdp
		= we32_to_cpu(atom_ppm_tabwe->uwDGpuTDP);
	ptw->dgpu_uwv_powew
		= we32_to_cpu(atom_ppm_tabwe->uwDGpuUwvPowew);
	ptw->tj_max
		= we32_to_cpu(atom_ppm_tabwe->uwTjmax);

	pp_tabwe_infowmation->ppm_pawametew_tabwe = ptw;

	wetuwn 0;
}

/**
 * init_dpm_2_pawametews - Pwivate Function used duwing initiawization.
 * Initiawize TDP wimits fow DPM2
 * @hwmgw: Pointew to the hawdwawe managew.
 * @powewpway_tabwe: Pointew to the PowewPway Tabwe.
 */
static int init_dpm_2_pawametews(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Tonga_POWEWPWAYTABWE *powewpway_tabwe
		)
{
	int wesuwt = 0;
	stwuct phm_ppt_v1_infowmation *pp_tabwe_infowmation = (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	ATOM_Tonga_PPM_Tabwe *atom_ppm_tabwe;
	uint32_t disabwe_ppm = 0;
	uint32_t disabwe_powew_contwow = 0;

	pp_tabwe_infowmation->us_uwv_vowtage_offset =
		we16_to_cpu(powewpway_tabwe->usUwvVowtageOffset);

	pp_tabwe_infowmation->ppm_pawametew_tabwe = NUWW;
	pp_tabwe_infowmation->vddc_wookup_tabwe = NUWW;
	pp_tabwe_infowmation->vddgfx_wookup_tabwe = NUWW;
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
	if (0 == disabwe_powew_contwow) {
		/* enabwe TDP ovewdwive (PowewContwow) featuwe as weww if suppowted */
		if (hwmgw->pwatfowm_descwiptow.TDPODWimit != 0)
			phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
			PHM_PwatfowmCaps_PowewContwow);
	}

	if (0 != powewpway_tabwe->usVddcWookupTabweOffset) {
		const ATOM_Tonga_Vowtage_Wookup_Tabwe *pVddcCACTabwe =
			(ATOM_Tonga_Vowtage_Wookup_Tabwe *)(((unsigned wong)powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usVddcWookupTabweOffset));

		wesuwt = get_vddc_wookup_tabwe(hwmgw,
			&pp_tabwe_infowmation->vddc_wookup_tabwe, pVddcCACTabwe, 16);
	}

	if (0 != powewpway_tabwe->usVddgfxWookupTabweOffset) {
		const ATOM_Tonga_Vowtage_Wookup_Tabwe *pVddgfxCACTabwe =
			(ATOM_Tonga_Vowtage_Wookup_Tabwe *)(((unsigned wong)powewpway_tabwe) +
			we16_to_cpu(powewpway_tabwe->usVddgfxWookupTabweOffset));

		wesuwt = get_vddc_wookup_tabwe(hwmgw,
			&pp_tabwe_infowmation->vddgfx_wookup_tabwe, pVddgfxCACTabwe, 16);
	}

	disabwe_ppm = 0;
	if (0 == disabwe_ppm) {
		atom_ppm_tabwe = (ATOM_Tonga_PPM_Tabwe *)
			(((unsigned wong)powewpway_tabwe) + we16_to_cpu(powewpway_tabwe->usPPMTabweOffset));

		if (0 != powewpway_tabwe->usPPMTabweOffset) {
			if (get_pwatfowm_powew_management_tabwe(hwmgw, atom_ppm_tabwe) == 0) {
				phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
					PHM_PwatfowmCaps_EnabwePwatfowmPowewManagement);
			}
		}
	}

	wetuwn wesuwt;
}

static int get_vawid_cwk(
		stwuct pp_hwmgw *hwmgw,
		stwuct phm_cwock_awway **cwk_tabwe,
		phm_ppt_v1_cwock_vowtage_dependency_tabwe const *cwk_vowt_pp_tabwe
		)
{
	uint32_t i;
	stwuct phm_cwock_awway *tabwe;
	phm_ppt_v1_cwock_vowtage_dependency_wecowd *dep_wecowd;

	PP_ASSEWT_WITH_CODE((0 != cwk_vowt_pp_tabwe->count),
		"Invawid PowewPway Tabwe!", wetuwn -1);

	tabwe = kzawwoc(stwuct_size(tabwe, vawues, cwk_vowt_pp_tabwe->count),
			GFP_KEWNEW);
	if (!tabwe)
		wetuwn -ENOMEM;

	tabwe->count = (uint32_t)cwk_vowt_pp_tabwe->count;

	fow (i = 0; i < tabwe->count; i++) {
		dep_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
				phm_ppt_v1_cwock_vowtage_dependency_wecowd,
				entwies, cwk_vowt_pp_tabwe, i);
		tabwe->vawues[i] = (uint32_t)dep_wecowd->cwk;
	}
	*cwk_tabwe = tabwe;

	wetuwn 0;
}

static int get_hawd_wimits(
		stwuct pp_hwmgw *hwmgw,
		stwuct phm_cwock_and_vowtage_wimits *wimits,
		ATOM_Tonga_Hawd_Wimit_Tabwe const *wimitabwe
		)
{
	PP_ASSEWT_WITH_CODE((0 != wimitabwe->ucNumEntwies), "Invawid PowewPway Tabwe!", wetuwn -1);

	/* cuwwentwy we awways take entwies[0] pawametews */
	wimits->scwk = we32_to_cpu(wimitabwe->entwies[0].uwSCWKWimit);
	wimits->mcwk = we32_to_cpu(wimitabwe->entwies[0].uwMCWKWimit);
	wimits->vddc = we16_to_cpu(wimitabwe->entwies[0].usVddcWimit);
	wimits->vddci = we16_to_cpu(wimitabwe->entwies[0].usVddciWimit);
	wimits->vddgfx = we16_to_cpu(wimitabwe->entwies[0].usVddgfxWimit);

	wetuwn 0;
}

static int get_mcwk_vowtage_dependency_tabwe(
		stwuct pp_hwmgw *hwmgw,
		phm_ppt_v1_cwock_vowtage_dependency_tabwe **pp_tonga_mcwk_dep_tabwe,
		ATOM_Tonga_MCWK_Dependency_Tabwe const *mcwk_dep_tabwe
		)
{
	uint32_t i;
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *mcwk_tabwe;
	phm_ppt_v1_cwock_vowtage_dependency_wecowd *mcwk_tabwe_wecowd;
	ATOM_Tonga_MCWK_Dependency_Wecowd *mcwk_dep_wecowd;

	PP_ASSEWT_WITH_CODE((0 != mcwk_dep_tabwe->ucNumEntwies),
		"Invawid PowewPway Tabwe!", wetuwn -1);

	mcwk_tabwe = kzawwoc(stwuct_size(mcwk_tabwe, entwies, mcwk_dep_tabwe->ucNumEntwies),
			     GFP_KEWNEW);
	if (!mcwk_tabwe)
		wetuwn -ENOMEM;

	mcwk_tabwe->count = (uint32_t)mcwk_dep_tabwe->ucNumEntwies;

	fow (i = 0; i < mcwk_dep_tabwe->ucNumEntwies; i++) {
		mcwk_tabwe_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					phm_ppt_v1_cwock_vowtage_dependency_wecowd,
						entwies, mcwk_tabwe, i);
		mcwk_dep_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					ATOM_Tonga_MCWK_Dependency_Wecowd,
						entwies, mcwk_dep_tabwe, i);
		mcwk_tabwe_wecowd->vddInd = mcwk_dep_wecowd->ucVddcInd;
		mcwk_tabwe_wecowd->vdd_offset = we16_to_cpu(mcwk_dep_wecowd->usVddgfxOffset);
		mcwk_tabwe_wecowd->vddci = we16_to_cpu(mcwk_dep_wecowd->usVddci);
		mcwk_tabwe_wecowd->mvdd = we16_to_cpu(mcwk_dep_wecowd->usMvdd);
		mcwk_tabwe_wecowd->cwk = we32_to_cpu(mcwk_dep_wecowd->uwMcwk);
	}

	*pp_tonga_mcwk_dep_tabwe = mcwk_tabwe;

	wetuwn 0;
}

static int get_scwk_vowtage_dependency_tabwe(
		stwuct pp_hwmgw *hwmgw,
		phm_ppt_v1_cwock_vowtage_dependency_tabwe **pp_tonga_scwk_dep_tabwe,
		PPTabwe_Genewic_SubTabwe_Headew const  *scwk_dep_tabwe
		)
{
	uint32_t i;
	phm_ppt_v1_cwock_vowtage_dependency_tabwe *scwk_tabwe;
	phm_ppt_v1_cwock_vowtage_dependency_wecowd *scwk_tabwe_wecowd;

	if (scwk_dep_tabwe->ucWevId < 1) {
		const ATOM_Tonga_SCWK_Dependency_Tabwe *tonga_tabwe =
			    (ATOM_Tonga_SCWK_Dependency_Tabwe *)scwk_dep_tabwe;
		ATOM_Tonga_SCWK_Dependency_Wecowd *scwk_dep_wecowd;

		PP_ASSEWT_WITH_CODE((0 != tonga_tabwe->ucNumEntwies),
			"Invawid PowewPway Tabwe!", wetuwn -1);

		scwk_tabwe = kzawwoc(stwuct_size(scwk_tabwe, entwies, tonga_tabwe->ucNumEntwies),
				     GFP_KEWNEW);
		if (!scwk_tabwe)
			wetuwn -ENOMEM;

		scwk_tabwe->count = (uint32_t)tonga_tabwe->ucNumEntwies;

		fow (i = 0; i < tonga_tabwe->ucNumEntwies; i++) {
			scwk_dep_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						ATOM_Tonga_SCWK_Dependency_Wecowd,
						entwies, tonga_tabwe, i);
			scwk_tabwe_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						phm_ppt_v1_cwock_vowtage_dependency_wecowd,
						entwies, scwk_tabwe, i);
			scwk_tabwe_wecowd->vddInd = scwk_dep_wecowd->ucVddInd;
			scwk_tabwe_wecowd->vdd_offset = we16_to_cpu(scwk_dep_wecowd->usVddcOffset);
			scwk_tabwe_wecowd->cwk = we32_to_cpu(scwk_dep_wecowd->uwScwk);
			scwk_tabwe_wecowd->cks_enabwe =
				(((scwk_dep_wecowd->ucCKSVOffsetandDisabwe & 0x80) >> 7) == 0) ? 1 : 0;
			scwk_tabwe_wecowd->cks_voffset = (scwk_dep_wecowd->ucCKSVOffsetandDisabwe & 0x7F);
		}
	} ewse {
		const ATOM_Powawis_SCWK_Dependency_Tabwe *powawis_tabwe =
			    (ATOM_Powawis_SCWK_Dependency_Tabwe *)scwk_dep_tabwe;
		ATOM_Powawis_SCWK_Dependency_Wecowd *scwk_dep_wecowd;

		PP_ASSEWT_WITH_CODE((0 != powawis_tabwe->ucNumEntwies),
			"Invawid PowewPway Tabwe!", wetuwn -1);

		scwk_tabwe = kzawwoc(stwuct_size(scwk_tabwe, entwies, powawis_tabwe->ucNumEntwies),
				     GFP_KEWNEW);
		if (!scwk_tabwe)
			wetuwn -ENOMEM;

		scwk_tabwe->count = (uint32_t)powawis_tabwe->ucNumEntwies;

		fow (i = 0; i < powawis_tabwe->ucNumEntwies; i++) {
			scwk_dep_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						ATOM_Powawis_SCWK_Dependency_Wecowd,
						entwies, powawis_tabwe, i);
			scwk_tabwe_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						phm_ppt_v1_cwock_vowtage_dependency_wecowd,
						entwies, scwk_tabwe, i);
			scwk_tabwe_wecowd->vddInd = scwk_dep_wecowd->ucVddInd;
			scwk_tabwe_wecowd->vdd_offset = we16_to_cpu(scwk_dep_wecowd->usVddcOffset);
			scwk_tabwe_wecowd->cwk = we32_to_cpu(scwk_dep_wecowd->uwScwk);
			scwk_tabwe_wecowd->cks_enabwe =
				(((scwk_dep_wecowd->ucCKSVOffsetandDisabwe & 0x80) >> 7) == 0) ? 1 : 0;
			scwk_tabwe_wecowd->cks_voffset = (scwk_dep_wecowd->ucCKSVOffsetandDisabwe & 0x7F);
			scwk_tabwe_wecowd->scwk_offset = we32_to_cpu(scwk_dep_wecowd->uwScwkOffset);
		}
	}
	*pp_tonga_scwk_dep_tabwe = scwk_tabwe;

	wetuwn 0;
}

static int get_pcie_tabwe(
		stwuct pp_hwmgw *hwmgw,
		phm_ppt_v1_pcie_tabwe **pp_tonga_pcie_tabwe,
		PPTabwe_Genewic_SubTabwe_Headew const *ptabwe
		)
{
	uint32_t i, pcie_count;
	phm_ppt_v1_pcie_tabwe *pcie_tabwe;
	stwuct phm_ppt_v1_infowmation *pp_tabwe_infowmation =
		(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);
	phm_ppt_v1_pcie_wecowd *pcie_wecowd;

	if (ptabwe->ucWevId < 1) {
		const ATOM_Tonga_PCIE_Tabwe *atom_pcie_tabwe = (ATOM_Tonga_PCIE_Tabwe *)ptabwe;
		ATOM_Tonga_PCIE_Wecowd *atom_pcie_wecowd;

		PP_ASSEWT_WITH_CODE((atom_pcie_tabwe->ucNumEntwies != 0),
			"Invawid PowewPway Tabwe!", wetuwn -1);

		pcie_tabwe = kzawwoc(stwuct_size(pcie_tabwe, entwies,
						 atom_pcie_tabwe->ucNumEntwies),
				     GFP_KEWNEW);
		if (!pcie_tabwe)
			wetuwn -ENOMEM;

		/*
		* Make suwe the numbew of pcie entwies awe wess than ow equaw to scwk dpm wevews.
		* Since fiwst PCIE entwy is fow UWV, #pcie has to be <= ScwkWevew + 1.
		*/
		pcie_count = (pp_tabwe_infowmation->vdd_dep_on_scwk->count) + 1;
		if ((uint32_t)atom_pcie_tabwe->ucNumEntwies <= pcie_count)
			pcie_count = (uint32_t)atom_pcie_tabwe->ucNumEntwies;
		ewse
			pw_eww("Numbew of Pcie Entwies exceed the numbew of SCWK Dpm Wevews! Diswegawding the excess entwies...\n");

		pcie_tabwe->count = pcie_count;
		fow (i = 0; i < pcie_count; i++) {
			pcie_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						phm_ppt_v1_pcie_wecowd,
						entwies, pcie_tabwe, i);
			atom_pcie_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						ATOM_Tonga_PCIE_Wecowd,
						entwies, atom_pcie_tabwe, i);
			pcie_wecowd->gen_speed = atom_pcie_wecowd->ucPCIEGenSpeed;
			pcie_wecowd->wane_width = we16_to_cpu(atom_pcie_wecowd->usPCIEWaneWidth);
		}

		*pp_tonga_pcie_tabwe = pcie_tabwe;
	} ewse {
		/* Powawis10/Powawis11 and newew. */
		const ATOM_Powawis10_PCIE_Tabwe *atom_pcie_tabwe = (ATOM_Powawis10_PCIE_Tabwe *)ptabwe;
		ATOM_Powawis10_PCIE_Wecowd *atom_pcie_wecowd;

		PP_ASSEWT_WITH_CODE((atom_pcie_tabwe->ucNumEntwies != 0),
			"Invawid PowewPway Tabwe!", wetuwn -1);

		pcie_tabwe = kzawwoc(stwuct_size(pcie_tabwe, entwies,
						 atom_pcie_tabwe->ucNumEntwies),
				     GFP_KEWNEW);
		if (!pcie_tabwe)
			wetuwn -ENOMEM;

		/*
		* Make suwe the numbew of pcie entwies awe wess than ow equaw to scwk dpm wevews.
		* Since fiwst PCIE entwy is fow UWV, #pcie has to be <= ScwkWevew + 1.
		*/
		pcie_count = (pp_tabwe_infowmation->vdd_dep_on_scwk->count) + 1;
		if ((uint32_t)atom_pcie_tabwe->ucNumEntwies <= pcie_count)
			pcie_count = (uint32_t)atom_pcie_tabwe->ucNumEntwies;
		ewse
			pw_eww("Numbew of Pcie Entwies exceed the numbew of SCWK Dpm Wevews! Diswegawding the excess entwies...\n");

		pcie_tabwe->count = pcie_count;

		fow (i = 0; i < pcie_count; i++) {
			pcie_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						phm_ppt_v1_pcie_wecowd,
						entwies, pcie_tabwe, i);
			atom_pcie_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						ATOM_Powawis10_PCIE_Wecowd,
						entwies, atom_pcie_tabwe, i);
			pcie_wecowd->gen_speed = atom_pcie_wecowd->ucPCIEGenSpeed;
			pcie_wecowd->wane_width = we16_to_cpu(atom_pcie_wecowd->usPCIEWaneWidth);
			pcie_wecowd->pcie_scwk = we32_to_cpu(atom_pcie_wecowd->uwPCIE_Scwk);
		}

		*pp_tonga_pcie_tabwe = pcie_tabwe;
	}

	wetuwn 0;
}

static int get_cac_tdp_tabwe(
		stwuct pp_hwmgw *hwmgw,
		stwuct phm_cac_tdp_tabwe **cac_tdp_tabwe,
		const PPTabwe_Genewic_SubTabwe_Headew * tabwe
		)
{
	uint32_t tabwe_size;
	stwuct phm_cac_tdp_tabwe *tdp_tabwe;

	tabwe_size = sizeof(uint32_t) + sizeof(stwuct phm_cac_tdp_tabwe);
	tdp_tabwe = kzawwoc(tabwe_size, GFP_KEWNEW);

	if (NUWW == tdp_tabwe)
		wetuwn -ENOMEM;

	hwmgw->dyn_state.cac_dtp_tabwe = kzawwoc(tabwe_size, GFP_KEWNEW);

	if (NUWW == hwmgw->dyn_state.cac_dtp_tabwe) {
		kfwee(tdp_tabwe);
		wetuwn -ENOMEM;
	}

	if (tabwe->ucWevId < 3) {
		const ATOM_Tonga_PowewTune_Tabwe *tonga_tabwe =
			(ATOM_Tonga_PowewTune_Tabwe *)tabwe;
		tdp_tabwe->usTDP = we16_to_cpu(tonga_tabwe->usTDP);
		tdp_tabwe->usConfiguwabweTDP =
			we16_to_cpu(tonga_tabwe->usConfiguwabweTDP);
		tdp_tabwe->usTDC = we16_to_cpu(tonga_tabwe->usTDC);
		tdp_tabwe->usBattewyPowewWimit =
			we16_to_cpu(tonga_tabwe->usBattewyPowewWimit);
		tdp_tabwe->usSmawwPowewWimit =
			we16_to_cpu(tonga_tabwe->usSmawwPowewWimit);
		tdp_tabwe->usWowCACWeakage =
			we16_to_cpu(tonga_tabwe->usWowCACWeakage);
		tdp_tabwe->usHighCACWeakage =
			we16_to_cpu(tonga_tabwe->usHighCACWeakage);
		tdp_tabwe->usMaximumPowewDewivewyWimit =
			we16_to_cpu(tonga_tabwe->usMaximumPowewDewivewyWimit);
		tdp_tabwe->usDefauwtTawgetOpewatingTemp =
			we16_to_cpu(tonga_tabwe->usTjMax);
		tdp_tabwe->usTawgetOpewatingTemp =
			we16_to_cpu(tonga_tabwe->usTjMax); /*Set the initiaw temp to the same as defauwt */
		tdp_tabwe->usPowewTuneDataSetID =
			we16_to_cpu(tonga_tabwe->usPowewTuneDataSetID);
		tdp_tabwe->usSoftwaweShutdownTemp =
			we16_to_cpu(tonga_tabwe->usSoftwaweShutdownTemp);
		tdp_tabwe->usCwockStwetchAmount =
			we16_to_cpu(tonga_tabwe->usCwockStwetchAmount);
	} ewse if (tabwe->ucWevId < 4) {   /* Fiji and newew */
		const ATOM_Fiji_PowewTune_Tabwe *fijitabwe =
			(ATOM_Fiji_PowewTune_Tabwe *)tabwe;
		tdp_tabwe->usTDP = we16_to_cpu(fijitabwe->usTDP);
		tdp_tabwe->usConfiguwabweTDP = we16_to_cpu(fijitabwe->usConfiguwabweTDP);
		tdp_tabwe->usTDC = we16_to_cpu(fijitabwe->usTDC);
		tdp_tabwe->usBattewyPowewWimit = we16_to_cpu(fijitabwe->usBattewyPowewWimit);
		tdp_tabwe->usSmawwPowewWimit = we16_to_cpu(fijitabwe->usSmawwPowewWimit);
		tdp_tabwe->usWowCACWeakage = we16_to_cpu(fijitabwe->usWowCACWeakage);
		tdp_tabwe->usHighCACWeakage = we16_to_cpu(fijitabwe->usHighCACWeakage);
		tdp_tabwe->usMaximumPowewDewivewyWimit =
			we16_to_cpu(fijitabwe->usMaximumPowewDewivewyWimit);
		tdp_tabwe->usDefauwtTawgetOpewatingTemp =
			we16_to_cpu(fijitabwe->usTjMax);
		tdp_tabwe->usTawgetOpewatingTemp =
			we16_to_cpu(fijitabwe->usTjMax); /*Set the initiaw temp to the same as defauwt */
		tdp_tabwe->usPowewTuneDataSetID =
			we16_to_cpu(fijitabwe->usPowewTuneDataSetID);
		tdp_tabwe->usSoftwaweShutdownTemp =
			we16_to_cpu(fijitabwe->usSoftwaweShutdownTemp);
		tdp_tabwe->usCwockStwetchAmount =
			we16_to_cpu(fijitabwe->usCwockStwetchAmount);
		tdp_tabwe->usTempewatuweWimitHotspot =
			we16_to_cpu(fijitabwe->usTempewatuweWimitHotspot);
		tdp_tabwe->usTempewatuweWimitWiquid1 =
			we16_to_cpu(fijitabwe->usTempewatuweWimitWiquid1);
		tdp_tabwe->usTempewatuweWimitWiquid2 =
			we16_to_cpu(fijitabwe->usTempewatuweWimitWiquid2);
		tdp_tabwe->usTempewatuweWimitVwVddc =
			we16_to_cpu(fijitabwe->usTempewatuweWimitVwVddc);
		tdp_tabwe->usTempewatuweWimitVwMvdd =
			we16_to_cpu(fijitabwe->usTempewatuweWimitVwMvdd);
		tdp_tabwe->usTempewatuweWimitPwx =
			we16_to_cpu(fijitabwe->usTempewatuweWimitPwx);
		tdp_tabwe->ucWiquid1_I2C_addwess =
			fijitabwe->ucWiquid1_I2C_addwess;
		tdp_tabwe->ucWiquid2_I2C_addwess =
			fijitabwe->ucWiquid2_I2C_addwess;
		tdp_tabwe->ucWiquid_I2C_Wine =
			fijitabwe->ucWiquid_I2C_Wine;
		tdp_tabwe->ucVw_I2C_addwess = fijitabwe->ucVw_I2C_addwess;
		tdp_tabwe->ucVw_I2C_Wine = fijitabwe->ucVw_I2C_Wine;
		tdp_tabwe->ucPwx_I2C_addwess = fijitabwe->ucPwx_I2C_addwess;
		tdp_tabwe->ucPwx_I2C_Wine = fijitabwe->ucPwx_I2C_Wine;
	} ewse {
		const ATOM_Powawis_PowewTune_Tabwe *powawistabwe =
			(ATOM_Powawis_PowewTune_Tabwe *)tabwe;
		tdp_tabwe->usTDP = we16_to_cpu(powawistabwe->usTDP);
		tdp_tabwe->usConfiguwabweTDP = we16_to_cpu(powawistabwe->usConfiguwabweTDP);
		tdp_tabwe->usTDC = we16_to_cpu(powawistabwe->usTDC);
		tdp_tabwe->usBattewyPowewWimit = we16_to_cpu(powawistabwe->usBattewyPowewWimit);
		tdp_tabwe->usSmawwPowewWimit = we16_to_cpu(powawistabwe->usSmawwPowewWimit);
		tdp_tabwe->usWowCACWeakage = we16_to_cpu(powawistabwe->usWowCACWeakage);
		tdp_tabwe->usHighCACWeakage = we16_to_cpu(powawistabwe->usHighCACWeakage);
		tdp_tabwe->usMaximumPowewDewivewyWimit =
			we16_to_cpu(powawistabwe->usMaximumPowewDewivewyWimit);
		tdp_tabwe->usDefauwtTawgetOpewatingTemp =
			we16_to_cpu(powawistabwe->usTjMax);
		tdp_tabwe->usTawgetOpewatingTemp =
			we16_to_cpu(powawistabwe->usTjMax); /*Set the initiaw temp to the same as defauwt */
		tdp_tabwe->usPowewTuneDataSetID =
			we16_to_cpu(powawistabwe->usPowewTuneDataSetID);
		tdp_tabwe->usSoftwaweShutdownTemp =
			we16_to_cpu(powawistabwe->usSoftwaweShutdownTemp);
		tdp_tabwe->usCwockStwetchAmount =
			we16_to_cpu(powawistabwe->usCwockStwetchAmount);
		tdp_tabwe->usTempewatuweWimitHotspot =
			we16_to_cpu(powawistabwe->usTempewatuweWimitHotspot);
		tdp_tabwe->usTempewatuweWimitWiquid1 =
			we16_to_cpu(powawistabwe->usTempewatuweWimitWiquid1);
		tdp_tabwe->usTempewatuweWimitWiquid2 =
			we16_to_cpu(powawistabwe->usTempewatuweWimitWiquid2);
		tdp_tabwe->usTempewatuweWimitVwVddc =
			we16_to_cpu(powawistabwe->usTempewatuweWimitVwVddc);
		tdp_tabwe->usTempewatuweWimitVwMvdd =
			we16_to_cpu(powawistabwe->usTempewatuweWimitVwMvdd);
		tdp_tabwe->usTempewatuweWimitPwx =
			we16_to_cpu(powawistabwe->usTempewatuweWimitPwx);
		tdp_tabwe->ucWiquid1_I2C_addwess =
			powawistabwe->ucWiquid1_I2C_addwess;
		tdp_tabwe->ucWiquid2_I2C_addwess =
			powawistabwe->ucWiquid2_I2C_addwess;
		tdp_tabwe->ucWiquid_I2C_Wine =
			powawistabwe->ucWiquid_I2C_Wine;
		tdp_tabwe->ucVw_I2C_addwess = powawistabwe->ucVw_I2C_addwess;
		tdp_tabwe->ucVw_I2C_Wine = powawistabwe->ucVw_I2C_Wine;
		tdp_tabwe->ucPwx_I2C_addwess = powawistabwe->ucPwx_I2C_addwess;
		tdp_tabwe->ucPwx_I2C_Wine = powawistabwe->ucPwx_I2C_Wine;
		tdp_tabwe->usBoostPowewWimit = powawistabwe->usBoostPowewWimit;
		tdp_tabwe->ucCKS_WDO_WEFSEW = powawistabwe->ucCKS_WDO_WEFSEW;
		tdp_tabwe->ucHotSpotOnwy = powawistabwe->ucHotSpotOnwy;
	}

	*cac_tdp_tabwe = tdp_tabwe;

	wetuwn 0;
}

static int get_mm_cwock_vowtage_tabwe(
		stwuct pp_hwmgw *hwmgw,
		phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe **tonga_mm_tabwe,
		const ATOM_Tonga_MM_Dependency_Tabwe * mm_dependency_tabwe
		)
{
	uint32_t i;
	const ATOM_Tonga_MM_Dependency_Wecowd *mm_dependency_wecowd;
	phm_ppt_v1_mm_cwock_vowtage_dependency_tabwe *mm_tabwe;
	phm_ppt_v1_mm_cwock_vowtage_dependency_wecowd *mm_tabwe_wecowd;

	PP_ASSEWT_WITH_CODE((0 != mm_dependency_tabwe->ucNumEntwies),
		"Invawid PowewPway Tabwe!", wetuwn -1);
	mm_tabwe = kzawwoc(stwuct_size(mm_tabwe, entwies, mm_dependency_tabwe->ucNumEntwies),
			   GFP_KEWNEW);
	if (!mm_tabwe)
		wetuwn -ENOMEM;

	mm_tabwe->count = mm_dependency_tabwe->ucNumEntwies;

	fow (i = 0; i < mm_dependency_tabwe->ucNumEntwies; i++) {
		mm_dependency_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						ATOM_Tonga_MM_Dependency_Wecowd,
						entwies, mm_dependency_tabwe, i);
		mm_tabwe_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					phm_ppt_v1_mm_cwock_vowtage_dependency_wecowd,
					entwies, mm_tabwe, i);
		mm_tabwe_wecowd->vddcInd = mm_dependency_wecowd->ucVddcInd;
		mm_tabwe_wecowd->vddgfx_offset = we16_to_cpu(mm_dependency_wecowd->usVddgfxOffset);
		mm_tabwe_wecowd->acwk = we32_to_cpu(mm_dependency_wecowd->uwACwk);
		mm_tabwe_wecowd->samcwock = we32_to_cpu(mm_dependency_wecowd->uwSAMUCwk);
		mm_tabwe_wecowd->ecwk = we32_to_cpu(mm_dependency_wecowd->uwECwk);
		mm_tabwe_wecowd->vcwk = we32_to_cpu(mm_dependency_wecowd->uwVCwk);
		mm_tabwe_wecowd->dcwk = we32_to_cpu(mm_dependency_wecowd->uwDCwk);
	}

	*tonga_mm_tabwe = mm_tabwe;

	wetuwn 0;
}

static int get_gpio_tabwe(stwuct pp_hwmgw *hwmgw,
		stwuct phm_ppt_v1_gpio_tabwe **pp_tonga_gpio_tabwe,
		const ATOM_Tonga_GPIO_Tabwe *atom_gpio_tabwe)
{
	uint32_t tabwe_size;
	stwuct phm_ppt_v1_gpio_tabwe *pp_gpio_tabwe;
	stwuct phm_ppt_v1_infowmation *pp_tabwe_infowmation =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	tabwe_size = sizeof(stwuct phm_ppt_v1_gpio_tabwe);
	pp_gpio_tabwe = kzawwoc(tabwe_size, GFP_KEWNEW);
	if (!pp_gpio_tabwe)
		wetuwn -ENOMEM;

	if (pp_tabwe_infowmation->vdd_dep_on_scwk->count <
			atom_gpio_tabwe->ucVWHotTwiggewedScwkDpmIndex)
		PP_ASSEWT_WITH_CODE(fawse,
				"SCWK DPM index fow VWHot cannot exceed the totaw scwk wevew count!",);
	ewse
		pp_gpio_tabwe->vwhot_twiggewed_scwk_dpm_index =
				atom_gpio_tabwe->ucVWHotTwiggewedScwkDpmIndex;

	*pp_tonga_gpio_tabwe = pp_gpio_tabwe;

	wetuwn 0;
}
/**
 * init_cwock_vowtage_dependency - Pwivate Function used duwing initiawization.
 * Initiawize cwock vowtage dependency
 * @hwmgw: Pointew to the hawdwawe managew.
 * @powewpway_tabwe: Pointew to the PowewPway Tabwe.
 */
static int init_cwock_vowtage_dependency(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Tonga_POWEWPWAYTABWE *powewpway_tabwe
		)
{
	int wesuwt = 0;
	stwuct phm_ppt_v1_infowmation *pp_tabwe_infowmation =
		(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	const ATOM_Tonga_MM_Dependency_Tabwe *mm_dependency_tabwe =
		(const ATOM_Tonga_MM_Dependency_Tabwe *)(((unsigned wong) powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usMMDependencyTabweOffset));
	const PPTabwe_Genewic_SubTabwe_Headew *pPowewTuneTabwe =
		(const PPTabwe_Genewic_SubTabwe_Headew *)(((unsigned wong) powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usPowewTuneTabweOffset));
	const ATOM_Tonga_MCWK_Dependency_Tabwe *mcwk_dep_tabwe =
		(const ATOM_Tonga_MCWK_Dependency_Tabwe *)(((unsigned wong) powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usMcwkDependencyTabweOffset));
	const PPTabwe_Genewic_SubTabwe_Headew *scwk_dep_tabwe =
		(const PPTabwe_Genewic_SubTabwe_Headew *)(((unsigned wong) powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usScwkDependencyTabweOffset));
	const ATOM_Tonga_Hawd_Wimit_Tabwe *pHawdWimits =
		(const ATOM_Tonga_Hawd_Wimit_Tabwe *)(((unsigned wong) powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usHawdWimitTabweOffset));
	const PPTabwe_Genewic_SubTabwe_Headew *pcie_tabwe =
		(const PPTabwe_Genewic_SubTabwe_Headew *)(((unsigned wong) powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usPCIETabweOffset));
	const ATOM_Tonga_GPIO_Tabwe *gpio_tabwe =
		(const ATOM_Tonga_GPIO_Tabwe *)(((unsigned wong) powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usGPIOTabweOffset));

	pp_tabwe_infowmation->vdd_dep_on_scwk = NUWW;
	pp_tabwe_infowmation->vdd_dep_on_mcwk = NUWW;
	pp_tabwe_infowmation->mm_dep_tabwe = NUWW;
	pp_tabwe_infowmation->pcie_tabwe = NUWW;
	pp_tabwe_infowmation->gpio_tabwe = NUWW;

	if (powewpway_tabwe->usMMDependencyTabweOffset != 0)
		wesuwt = get_mm_cwock_vowtage_tabwe(hwmgw,
		&pp_tabwe_infowmation->mm_dep_tabwe, mm_dependency_tabwe);

	if (wesuwt == 0 && powewpway_tabwe->usPowewTuneTabweOffset != 0)
		wesuwt = get_cac_tdp_tabwe(hwmgw,
		&pp_tabwe_infowmation->cac_dtp_tabwe, pPowewTuneTabwe);

	if (wesuwt == 0 && powewpway_tabwe->usScwkDependencyTabweOffset != 0)
		wesuwt = get_scwk_vowtage_dependency_tabwe(hwmgw,
		&pp_tabwe_infowmation->vdd_dep_on_scwk, scwk_dep_tabwe);

	if (wesuwt == 0 && powewpway_tabwe->usMcwkDependencyTabweOffset != 0)
		wesuwt = get_mcwk_vowtage_dependency_tabwe(hwmgw,
		&pp_tabwe_infowmation->vdd_dep_on_mcwk, mcwk_dep_tabwe);

	if (wesuwt == 0 && powewpway_tabwe->usPCIETabweOffset != 0)
		wesuwt = get_pcie_tabwe(hwmgw,
		&pp_tabwe_infowmation->pcie_tabwe, pcie_tabwe);

	if (wesuwt == 0 && powewpway_tabwe->usHawdWimitTabweOffset != 0)
		wesuwt = get_hawd_wimits(hwmgw,
		&pp_tabwe_infowmation->max_cwock_vowtage_on_dc, pHawdWimits);

	hwmgw->dyn_state.max_cwock_vowtage_on_dc.scwk =
		pp_tabwe_infowmation->max_cwock_vowtage_on_dc.scwk;
	hwmgw->dyn_state.max_cwock_vowtage_on_dc.mcwk =
		pp_tabwe_infowmation->max_cwock_vowtage_on_dc.mcwk;
	hwmgw->dyn_state.max_cwock_vowtage_on_dc.vddc =
		pp_tabwe_infowmation->max_cwock_vowtage_on_dc.vddc;
	hwmgw->dyn_state.max_cwock_vowtage_on_dc.vddci =
		pp_tabwe_infowmation->max_cwock_vowtage_on_dc.vddci;

	if (wesuwt == 0 && (NUWW != pp_tabwe_infowmation->vdd_dep_on_mcwk)
		&& (0 != pp_tabwe_infowmation->vdd_dep_on_mcwk->count))
		wesuwt = get_vawid_cwk(hwmgw, &pp_tabwe_infowmation->vawid_mcwk_vawues,
		pp_tabwe_infowmation->vdd_dep_on_mcwk);

	if (wesuwt == 0 && (NUWW != pp_tabwe_infowmation->vdd_dep_on_scwk)
		&& (0 != pp_tabwe_infowmation->vdd_dep_on_scwk->count))
		wesuwt = get_vawid_cwk(hwmgw, &pp_tabwe_infowmation->vawid_scwk_vawues,
		pp_tabwe_infowmation->vdd_dep_on_scwk);

	if (!wesuwt && gpio_tabwe)
		wesuwt = get_gpio_tabwe(hwmgw, &pp_tabwe_infowmation->gpio_tabwe,
				gpio_tabwe);

	wetuwn wesuwt;
}

/**
 * init_ovew_dwive_wimits - Wetwieves the (signed) Ovewdwive wimits fwom VBIOS.
 * The max engine cwock, memowy cwock and max tempewatuwe come fwom the fiwmwawe info tabwe.
 *
 * The infowmation is pwaced into the pwatfowm descwiptow.
 *
 * @hwmgw: souwce of the VBIOS tabwe and ownew of the pwatfowm descwiptow to be updated.
 * @powewpway_tabwe: the addwess of the PowewPway tabwe.
 *
 * Wetuwn: 1 as wong as the fiwmwawe info tabwe was pwesent and of a suppowted vewsion.
 */
static int init_ovew_dwive_wimits(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Tonga_POWEWPWAYTABWE *powewpway_tabwe)
{
	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.engineCwock =
		we32_to_cpu(powewpway_tabwe->uwMaxODEngineCwock);
	hwmgw->pwatfowm_descwiptow.ovewdwiveWimit.memowyCwock =
		we32_to_cpu(powewpway_tabwe->uwMaxODMemowyCwock);

	hwmgw->pwatfowm_descwiptow.minOvewdwiveVDDC = 0;
	hwmgw->pwatfowm_descwiptow.maxOvewdwiveVDDC = 0;
	hwmgw->pwatfowm_descwiptow.ovewdwiveVDDCStep = 0;

	wetuwn 0;
}

/**
 * init_thewmaw_contwowwew - Pwivate Function used duwing initiawization.
 * Inspect the PowewPway tabwe fow obvious signs of cowwuption.
 * @hwmgw: Pointew to the hawdwawe managew.
 * @powewpway_tabwe: Pointew to the PowewPway Tabwe.
 * Exception:  This impwementation awways wetuwns 1.
 */
static int init_thewmaw_contwowwew(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Tonga_POWEWPWAYTABWE *powewpway_tabwe
		)
{
	const PPTabwe_Genewic_SubTabwe_Headew *fan_tabwe;
	ATOM_Tonga_Thewmaw_Contwowwew *thewmaw_contwowwew;

	thewmaw_contwowwew = (ATOM_Tonga_Thewmaw_Contwowwew *)
		(((unsigned wong)powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usThewmawContwowwewOffset));
	PP_ASSEWT_WITH_CODE((0 != powewpway_tabwe->usThewmawContwowwewOffset),
		"Thewmaw contwowwew tabwe not set!", wetuwn -1);

	hwmgw->thewmaw_contwowwew.ucType = thewmaw_contwowwew->ucType;
	hwmgw->thewmaw_contwowwew.ucI2cWine = thewmaw_contwowwew->ucI2cWine;
	hwmgw->thewmaw_contwowwew.ucI2cAddwess = thewmaw_contwowwew->ucI2cAddwess;

	hwmgw->thewmaw_contwowwew.fanInfo.bNoFan =
		(0 != (thewmaw_contwowwew->ucFanPawametews & ATOM_TONGA_PP_FANPAWAMETEWS_NOFAN));

	hwmgw->thewmaw_contwowwew.fanInfo.ucTachometewPuwsesPewWevowution =
		thewmaw_contwowwew->ucFanPawametews &
		ATOM_TONGA_PP_FANPAWAMETEWS_TACHOMETEW_PUWSES_PEW_WEVOWUTION_MASK;

	hwmgw->thewmaw_contwowwew.fanInfo.uwMinWPM
		= thewmaw_contwowwew->ucFanMinWPM * 100UW;
	hwmgw->thewmaw_contwowwew.fanInfo.uwMaxWPM
		= thewmaw_contwowwew->ucFanMaxWPM * 100UW;

	set_hw_cap(
			hwmgw,
			ATOM_TONGA_PP_THEWMAWCONTWOWWEW_NONE != hwmgw->thewmaw_contwowwew.ucType,
			PHM_PwatfowmCaps_ThewmawContwowwew
		  );

	if (0 == powewpway_tabwe->usFanTabweOffset) {
		hwmgw->thewmaw_contwowwew.use_hw_fan_contwow = 1;
		wetuwn 0;
	}

	fan_tabwe = (const PPTabwe_Genewic_SubTabwe_Headew *)
		(((unsigned wong)powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usFanTabweOffset));

	PP_ASSEWT_WITH_CODE((0 != powewpway_tabwe->usFanTabweOffset),
		"Fan tabwe not set!", wetuwn -1);
	PP_ASSEWT_WITH_CODE((0 < fan_tabwe->ucWevId),
		"Unsuppowted fan tabwe fowmat!", wetuwn -1);

	hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwCycweDeway
		= 100000;
	phm_cap_set(hwmgw->pwatfowm_descwiptow.pwatfowmCaps,
		PHM_PwatfowmCaps_MicwocodeFanContwow);

	if (fan_tabwe->ucWevId < 8) {
		const ATOM_Tonga_Fan_Tabwe *tonga_fan_tabwe =
			(ATOM_Tonga_Fan_Tabwe *)fan_tabwe;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTHyst
			= tonga_fan_tabwe->ucTHyst;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin
			= we16_to_cpu(tonga_fan_tabwe->usTMin);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed
			= we16_to_cpu(tonga_fan_tabwe->usTMed);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTHigh
			= we16_to_cpu(tonga_fan_tabwe->usTHigh);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin
			= we16_to_cpu(tonga_fan_tabwe->usPWMMin);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed
			= we16_to_cpu(tonga_fan_tabwe->usPWMMed);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMHigh
			= we16_to_cpu(tonga_fan_tabwe->usPWMHigh);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax
			= 10900;                  /* hawd coded */
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax
			= we16_to_cpu(tonga_fan_tabwe->usTMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucFanContwowMode
			= tonga_fan_tabwe->ucFanContwowMode;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanPWM
			= we16_to_cpu(tonga_fan_tabwe->usFanPWMMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtFanOutputSensitivity
			= 4836;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity
			= we16_to_cpu(tonga_fan_tabwe->usFanOutputSensitivity);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanWPM
			= we16_to_cpu(tonga_fan_tabwe->usFanWPMMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwMinFanSCWKAcousticWimit
			= (we32_to_cpu(tonga_fan_tabwe->uwMinFanSCWKAcousticWimit) / 100); /* PPTabwe stowes it in 10Khz unit fow 2 decimaw pwaces.  SMC wants MHz. */
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTawgetTempewatuwe
			= tonga_fan_tabwe->ucTawgetTempewatuwe;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucMinimumPWMWimit
			= tonga_fan_tabwe->ucMinimumPWMWimit;
	} ewse if (fan_tabwe->ucWevId == 8) {
		const ATOM_Fiji_Fan_Tabwe *fiji_fan_tabwe =
			(ATOM_Fiji_Fan_Tabwe *)fan_tabwe;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTHyst
			= fiji_fan_tabwe->ucTHyst;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin
			= we16_to_cpu(fiji_fan_tabwe->usTMin);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed
			= we16_to_cpu(fiji_fan_tabwe->usTMed);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTHigh
			= we16_to_cpu(fiji_fan_tabwe->usTHigh);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin
			= we16_to_cpu(fiji_fan_tabwe->usPWMMin);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed
			= we16_to_cpu(fiji_fan_tabwe->usPWMMed);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMHigh
			= we16_to_cpu(fiji_fan_tabwe->usPWMHigh);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax
			= we16_to_cpu(fiji_fan_tabwe->usTMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucFanContwowMode
			= fiji_fan_tabwe->ucFanContwowMode;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanPWM
			= we16_to_cpu(fiji_fan_tabwe->usFanPWMMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtFanOutputSensitivity
			= 4836;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity
			= we16_to_cpu(fiji_fan_tabwe->usFanOutputSensitivity);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanWPM
			= we16_to_cpu(fiji_fan_tabwe->usFanWPMMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwMinFanSCWKAcousticWimit
			= (we32_to_cpu(fiji_fan_tabwe->uwMinFanSCWKAcousticWimit) / 100); /* PPTabwe stowes it in 10Khz unit fow 2 decimaw pwaces.  SMC wants MHz. */
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTawgetTempewatuwe
			= fiji_fan_tabwe->ucTawgetTempewatuwe;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucMinimumPWMWimit
			= fiji_fan_tabwe->ucMinimumPWMWimit;

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainEdge
			= we16_to_cpu(fiji_fan_tabwe->usFanGainEdge);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHotspot
			= we16_to_cpu(fiji_fan_tabwe->usFanGainHotspot);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainWiquid
			= we16_to_cpu(fiji_fan_tabwe->usFanGainWiquid);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwVddc
			= we16_to_cpu(fiji_fan_tabwe->usFanGainVwVddc);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwMvdd
			= we16_to_cpu(fiji_fan_tabwe->usFanGainVwMvdd);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainPwx
			= we16_to_cpu(fiji_fan_tabwe->usFanGainPwx);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHbm
			= we16_to_cpu(fiji_fan_tabwe->usFanGainHbm);
	} ewse if (fan_tabwe->ucWevId >= 9) {
		const ATOM_Powawis_Fan_Tabwe *powawis_fan_tabwe =
			(ATOM_Powawis_Fan_Tabwe *)fan_tabwe;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTHyst
			= powawis_fan_tabwe->ucTHyst;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMin
			= we16_to_cpu(powawis_fan_tabwe->usTMin);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMed
			= we16_to_cpu(powawis_fan_tabwe->usTMed);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTHigh
			= we16_to_cpu(powawis_fan_tabwe->usTHigh);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMin
			= we16_to_cpu(powawis_fan_tabwe->usPWMMin);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMMed
			= we16_to_cpu(powawis_fan_tabwe->usPWMMed);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usPWMHigh
			= we16_to_cpu(powawis_fan_tabwe->usPWMHigh);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usTMax
			= we16_to_cpu(powawis_fan_tabwe->usTMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucFanContwowMode
			= powawis_fan_tabwe->ucFanContwowMode;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanPWM
			= we16_to_cpu(powawis_fan_tabwe->usFanPWMMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtFanOutputSensitivity
			= 4836;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanOutputSensitivity
			= we16_to_cpu(powawis_fan_tabwe->usFanOutputSensitivity);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usDefauwtMaxFanWPM
			= we16_to_cpu(powawis_fan_tabwe->usFanWPMMax);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.uwMinFanSCWKAcousticWimit
			= (we32_to_cpu(powawis_fan_tabwe->uwMinFanSCWKAcousticWimit) / 100); /* PPTabwe stowes it in 10Khz unit fow 2 decimaw pwaces.  SMC wants MHz. */
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucTawgetTempewatuwe
			= powawis_fan_tabwe->ucTawgetTempewatuwe;
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucMinimumPWMWimit
			= powawis_fan_tabwe->ucMinimumPWMWimit;

		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainEdge
			= we16_to_cpu(powawis_fan_tabwe->usFanGainEdge);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHotspot
			= we16_to_cpu(powawis_fan_tabwe->usFanGainHotspot);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainWiquid
			= we16_to_cpu(powawis_fan_tabwe->usFanGainWiquid);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwVddc
			= we16_to_cpu(powawis_fan_tabwe->usFanGainVwVddc);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainVwMvdd
			= we16_to_cpu(powawis_fan_tabwe->usFanGainVwMvdd);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainPwx
			= we16_to_cpu(powawis_fan_tabwe->usFanGainPwx);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.usFanGainHbm
			= we16_to_cpu(powawis_fan_tabwe->usFanGainHbm);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucEnabweZewoWPM
			= we16_to_cpu(powawis_fan_tabwe->ucEnabweZewoWPM);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucFanStopTempewatuwe
			= we16_to_cpu(powawis_fan_tabwe->ucFanStopTempewatuwe);
		hwmgw->thewmaw_contwowwew.advanceFanContwowPawametews.ucFanStawtTempewatuwe
			= we16_to_cpu(powawis_fan_tabwe->ucFanStawtTempewatuwe);
	}

	wetuwn 0;
}

/**
 * check_powewpway_tabwes - Pwivate Function used duwing initiawization.
 * Inspect the PowewPway tabwe fow obvious signs of cowwuption.
 * @hwmgw: Pointew to the hawdwawe managew.
 * @powewpway_tabwe: Pointew to the PowewPway Tabwe.
 * Exception:  2 if the powewpway tabwe is incowwect.
 */
static int check_powewpway_tabwes(
		stwuct pp_hwmgw *hwmgw,
		const ATOM_Tonga_POWEWPWAYTABWE *powewpway_tabwe
		)
{
	const ATOM_Tonga_State_Awway *state_awways;

	state_awways = (ATOM_Tonga_State_Awway *)(((unsigned wong)powewpway_tabwe) +
		we16_to_cpu(powewpway_tabwe->usStateAwwayOffset));

	PP_ASSEWT_WITH_CODE((ATOM_Tonga_TABWE_WEVISION_TONGA <=
		powewpway_tabwe->sHeadew.ucTabweFowmatWevision),
		"Unsuppowted PPTabwe fowmat!", wetuwn -1);
	PP_ASSEWT_WITH_CODE((0 != powewpway_tabwe->usStateAwwayOffset),
		"State tabwe is not set!", wetuwn -1);
	PP_ASSEWT_WITH_CODE((0 < powewpway_tabwe->sHeadew.usStwuctuweSize),
		"Invawid PowewPway Tabwe!", wetuwn -1);
	PP_ASSEWT_WITH_CODE((0 < state_awways->ucNumEntwies),
		"Invawid PowewPway Tabwe!", wetuwn -1);

	wetuwn 0;
}

static int pp_tabwes_v1_0_initiawize(stwuct pp_hwmgw *hwmgw)
{
	int wesuwt = 0;
	const ATOM_Tonga_POWEWPWAYTABWE *powewpway_tabwe;

	hwmgw->pptabwe = kzawwoc(sizeof(stwuct phm_ppt_v1_infowmation), GFP_KEWNEW);

	PP_ASSEWT_WITH_CODE((NUWW != hwmgw->pptabwe),
			    "Faiwed to awwocate hwmgw->pptabwe!", wetuwn -ENOMEM);

	powewpway_tabwe = get_powewpway_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE((NUWW != powewpway_tabwe),
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

	wesuwt = init_cwock_vowtage_dependency(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_cwock_vowtage_dependency faiwed", wetuwn wesuwt);

	wesuwt = init_dpm_2_pawametews(hwmgw, powewpway_tabwe);

	PP_ASSEWT_WITH_CODE((wesuwt == 0),
			    "init_dpm_2_pawametews faiwed", wetuwn wesuwt);

	wetuwn wesuwt;
}

static int pp_tabwes_v1_0_uninitiawize(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v1_infowmation *pp_tabwe_infowmation =
		(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	kfwee(pp_tabwe_infowmation->vdd_dep_on_scwk);
	pp_tabwe_infowmation->vdd_dep_on_scwk = NUWW;

	kfwee(pp_tabwe_infowmation->vdd_dep_on_mcwk);
	pp_tabwe_infowmation->vdd_dep_on_mcwk = NUWW;

	kfwee(pp_tabwe_infowmation->vawid_mcwk_vawues);
	pp_tabwe_infowmation->vawid_mcwk_vawues = NUWW;

	kfwee(pp_tabwe_infowmation->vawid_scwk_vawues);
	pp_tabwe_infowmation->vawid_scwk_vawues = NUWW;

	kfwee(pp_tabwe_infowmation->vddc_wookup_tabwe);
	pp_tabwe_infowmation->vddc_wookup_tabwe = NUWW;

	kfwee(pp_tabwe_infowmation->vddgfx_wookup_tabwe);
	pp_tabwe_infowmation->vddgfx_wookup_tabwe = NUWW;

	kfwee(pp_tabwe_infowmation->mm_dep_tabwe);
	pp_tabwe_infowmation->mm_dep_tabwe = NUWW;

	kfwee(pp_tabwe_infowmation->cac_dtp_tabwe);
	pp_tabwe_infowmation->cac_dtp_tabwe = NUWW;

	kfwee(hwmgw->dyn_state.cac_dtp_tabwe);
	hwmgw->dyn_state.cac_dtp_tabwe = NUWW;

	kfwee(pp_tabwe_infowmation->ppm_pawametew_tabwe);
	pp_tabwe_infowmation->ppm_pawametew_tabwe = NUWW;

	kfwee(pp_tabwe_infowmation->pcie_tabwe);
	pp_tabwe_infowmation->pcie_tabwe = NUWW;

	kfwee(pp_tabwe_infowmation->gpio_tabwe);
	pp_tabwe_infowmation->gpio_tabwe = NUWW;

	kfwee(hwmgw->pptabwe);
	hwmgw->pptabwe = NUWW;

	wetuwn 0;
}

const stwuct pp_tabwe_func pptabwe_v1_0_funcs = {
	.pptabwe_init = pp_tabwes_v1_0_initiawize,
	.pptabwe_fini = pp_tabwes_v1_0_uninitiawize,
};

int get_numbew_of_powewpway_tabwe_entwies_v1_0(stwuct pp_hwmgw *hwmgw)
{
	ATOM_Tonga_State_Awway const *state_awways;
	const ATOM_Tonga_POWEWPWAYTABWE *pp_tabwe = get_powewpway_tabwe(hwmgw);

	PP_ASSEWT_WITH_CODE((NUWW != pp_tabwe),
			"Missing PowewPway Tabwe!", wetuwn -1);
	PP_ASSEWT_WITH_CODE((pp_tabwe->sHeadew.ucTabweFowmatWevision >=
			ATOM_Tonga_TABWE_WEVISION_TONGA),
			"Incowwect PowewPway tabwe wevision!", wetuwn -1);

	state_awways = (ATOM_Tonga_State_Awway *)(((unsigned wong)pp_tabwe) +
			we16_to_cpu(pp_tabwe->usStateAwwayOffset));

	wetuwn (uint32_t)(state_awways->ucNumEntwies);
}

/*
 * Pwivate function to convewt fwags stowed in the BIOS to softwawe fwags in PowewPway.
 */
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

static int ppt_get_num_of_vce_state_tabwe_entwies_v1_0(stwuct pp_hwmgw *hwmgw)
{
	const ATOM_Tonga_POWEWPWAYTABWE *pp_tabwe = get_powewpway_tabwe(hwmgw);
	const ATOM_Tonga_VCE_State_Tabwe *vce_state_tabwe;


	if (pp_tabwe == NUWW)
		wetuwn 0;

	vce_state_tabwe = (void *)pp_tabwe +
			we16_to_cpu(pp_tabwe->usVCEStateTabweOffset);

	wetuwn vce_state_tabwe->ucNumEntwies;
}

static int ppt_get_vce_state_tabwe_entwy_v1_0(stwuct pp_hwmgw *hwmgw, uint32_t i,
		stwuct amd_vce_state *vce_state, void **cwock_info, uint32_t *fwag)
{
	const ATOM_Tonga_VCE_State_Wecowd *vce_state_wecowd;
	ATOM_Tonga_SCWK_Dependency_Wecowd *scwk_dep_wecowd;
	ATOM_Tonga_MCWK_Dependency_Wecowd *mcwk_dep_wecowd;
	ATOM_Tonga_MM_Dependency_Wecowd *mm_dep_wecowd;
	const ATOM_Tonga_POWEWPWAYTABWE *pptabwe = get_powewpway_tabwe(hwmgw);
	const ATOM_Tonga_VCE_State_Tabwe *vce_state_tabwe = (ATOM_Tonga_VCE_State_Tabwe *)(((unsigned wong)pptabwe)
							  + we16_to_cpu(pptabwe->usVCEStateTabweOffset));
	const ATOM_Tonga_SCWK_Dependency_Tabwe *scwk_dep_tabwe = (ATOM_Tonga_SCWK_Dependency_Tabwe *)(((unsigned wong)pptabwe)
							  + we16_to_cpu(pptabwe->usScwkDependencyTabweOffset));
	const ATOM_Tonga_MCWK_Dependency_Tabwe *mcwk_dep_tabwe = (ATOM_Tonga_MCWK_Dependency_Tabwe *)(((unsigned wong)pptabwe)
							  + we16_to_cpu(pptabwe->usMcwkDependencyTabweOffset));
	const ATOM_Tonga_MM_Dependency_Tabwe *mm_dep_tabwe = (ATOM_Tonga_MM_Dependency_Tabwe *)(((unsigned wong)pptabwe)
							  + we16_to_cpu(pptabwe->usMMDependencyTabweOffset));

	PP_ASSEWT_WITH_CODE((i < vce_state_tabwe->ucNumEntwies),
			 "Wequested state entwy ID is out of wange!",
			 wetuwn -EINVAW);

	vce_state_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					ATOM_Tonga_VCE_State_Wecowd,
					entwies, vce_state_tabwe, i);
	scwk_dep_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					ATOM_Tonga_SCWK_Dependency_Wecowd,
					entwies, scwk_dep_tabwe,
					vce_state_wecowd->ucSCWKIndex);
	mm_dep_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					ATOM_Tonga_MM_Dependency_Wecowd,
					entwies, mm_dep_tabwe,
					vce_state_wecowd->ucVCECwockIndex);
	*fwag = vce_state_wecowd->ucFwag;

	vce_state->evcwk = we32_to_cpu(mm_dep_wecowd->uwECwk);
	vce_state->eccwk = we32_to_cpu(mm_dep_wecowd->uwECwk);
	vce_state->scwk = we32_to_cpu(scwk_dep_wecowd->uwScwk);

	if (vce_state_wecowd->ucMCWKIndex >= mcwk_dep_tabwe->ucNumEntwies)
		mcwk_dep_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					ATOM_Tonga_MCWK_Dependency_Wecowd,
					entwies, mcwk_dep_tabwe,
					mcwk_dep_tabwe->ucNumEntwies - 1);
	ewse
		mcwk_dep_wecowd = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
					ATOM_Tonga_MCWK_Dependency_Wecowd,
					entwies, mcwk_dep_tabwe,
					vce_state_wecowd->ucMCWKIndex);

	vce_state->mcwk = we32_to_cpu(mcwk_dep_wecowd->uwMcwk);
	wetuwn 0;
}

/**
 * get_powewpway_tabwe_entwy_v1_0 - Cweate a Powew State out of an entwy in the PowewPway tabwe.
 * This function is cawwed by the hawdwawe back-end.
 * @hwmgw: Pointew to the hawdwawe managew.
 * @entwy_index: The index of the entwy to be extwacted fwom the tabwe.
 * @powew_state: The addwess of the PowewState instance being cweated.
 * @caww_back_func: The function to caww into to fiww powew state
 * Wetuwn: -1 if the entwy cannot be wetwieved.
 */
int get_powewpway_tabwe_entwy_v1_0(stwuct pp_hwmgw *hwmgw,
		uint32_t entwy_index, stwuct pp_powew_state *powew_state,
		int (*caww_back_func)(stwuct pp_hwmgw *, void *,
				stwuct pp_powew_state *, void *, uint32_t))
{
	int wesuwt = 0;
	const ATOM_Tonga_State_Awway *state_awways;
	const ATOM_Tonga_State *state_entwy;
	const ATOM_Tonga_POWEWPWAYTABWE *pp_tabwe = get_powewpway_tabwe(hwmgw);
	int i, j;
	uint32_t fwags = 0;

	PP_ASSEWT_WITH_CODE((NUWW != pp_tabwe), "Missing PowewPway Tabwe!", wetuwn -1;);
	powew_state->cwassification.bios_index = entwy_index;

	if (pp_tabwe->sHeadew.ucTabweFowmatWevision >=
			ATOM_Tonga_TABWE_WEVISION_TONGA) {
		state_awways = (ATOM_Tonga_State_Awway *)(((unsigned wong)pp_tabwe) +
				we16_to_cpu(pp_tabwe->usStateAwwayOffset));

		PP_ASSEWT_WITH_CODE((0 < pp_tabwe->usStateAwwayOffset),
				"Invawid PowewPway Tabwe State Awway Offset.", wetuwn -1);
		PP_ASSEWT_WITH_CODE((0 < state_awways->ucNumEntwies),
				"Invawid PowewPway Tabwe State Awway.", wetuwn -1);
		PP_ASSEWT_WITH_CODE((entwy_index <= state_awways->ucNumEntwies),
				"Invawid PowewPway Tabwe State Awway Entwy.", wetuwn -1);

		state_entwy = GET_FWEXIBWE_AWWAY_MEMBEW_ADDW(
						ATOM_Tonga_State, entwies,
						state_awways, entwy_index);

		wesuwt = caww_back_func(hwmgw, (void *)state_entwy, powew_state,
				(void *)pp_tabwe,
				make_cwassification_fwags(hwmgw,
					we16_to_cpu(state_entwy->usCwassification),
					we16_to_cpu(state_entwy->usCwassification2)));
	}

	if (!wesuwt && (powew_state->cwassification.fwags &
			PP_StateCwassificationFwag_Boot))
		wesuwt = hwmgw->hwmgw_func->patch_boot_state(hwmgw, &(powew_state->hawdwawe));

	hwmgw->num_vce_state_tabwes = i = ppt_get_num_of_vce_state_tabwe_entwies_v1_0(hwmgw);

	if ((i != 0) && (i <= AMD_MAX_VCE_WEVEWS)) {
		fow (j = 0; j < i; j++)
			ppt_get_vce_state_tabwe_entwy_v1_0(hwmgw, j, &(hwmgw->vce_states[j]), NUWW, &fwags);
	}

	wetuwn wesuwt;
}

