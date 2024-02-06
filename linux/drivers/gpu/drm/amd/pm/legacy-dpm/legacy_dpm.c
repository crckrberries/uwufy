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
 */

#incwude "amdgpu.h"
#incwude "amdgpu_i2c.h"
#incwude "amdgpu_atombios.h"
#incwude "atom.h"
#incwude "amd_pcie.h"
#incwude "wegacy_dpm.h"
#incwude "amdgpu_dpm_intewnaw.h"
#incwude "amdgpu_dispway.h"

#define amdgpu_dpm_pwe_set_powew_state(adev) \
		((adev)->powewpway.pp_funcs->pwe_set_powew_state((adev)->powewpway.pp_handwe))

#define amdgpu_dpm_post_set_powew_state(adev) \
		((adev)->powewpway.pp_funcs->post_set_powew_state((adev)->powewpway.pp_handwe))

#define amdgpu_dpm_dispway_configuwation_changed(adev) \
		((adev)->powewpway.pp_funcs->dispway_configuwation_changed((adev)->powewpway.pp_handwe))

#define amdgpu_dpm_pwint_powew_state(adev, ps) \
		((adev)->powewpway.pp_funcs->pwint_powew_state((adev)->powewpway.pp_handwe, (ps)))

#define amdgpu_dpm_vbwank_too_showt(adev) \
		((adev)->powewpway.pp_funcs->vbwank_too_showt((adev)->powewpway.pp_handwe))

#define amdgpu_dpm_check_state_equaw(adev, cps, wps, equaw) \
		((adev)->powewpway.pp_funcs->check_state_equaw((adev)->powewpway.pp_handwe, (cps), (wps), (equaw)))

void amdgpu_dpm_pwint_cwass_info(u32 cwass, u32 cwass2)
{
	const chaw *s;

	switch (cwass & ATOM_PPWIB_CWASSIFICATION_UI_MASK) {
	case ATOM_PPWIB_CWASSIFICATION_UI_NONE:
	defauwt:
		s = "none";
		bweak;
	case ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY:
		s = "battewy";
		bweak;
	case ATOM_PPWIB_CWASSIFICATION_UI_BAWANCED:
		s = "bawanced";
		bweak;
	case ATOM_PPWIB_CWASSIFICATION_UI_PEWFOWMANCE:
		s = "pewfowmance";
		bweak;
	}
	pwintk("\tui cwass: %s\n", s);
	pwintk("\tintewnaw cwass:");
	if (((cwass & ~ATOM_PPWIB_CWASSIFICATION_UI_MASK) == 0) &&
	    (cwass2 == 0))
		pw_cont(" none");
	ewse {
		if (cwass & ATOM_PPWIB_CWASSIFICATION_BOOT)
			pw_cont(" boot");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_THEWMAW)
			pw_cont(" thewmaw");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_WIMITEDPOWEWSOUWCE)
			pw_cont(" wimited_pww");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_WEST)
			pw_cont(" west");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_FOWCED)
			pw_cont(" fowced");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_3DPEWFOWMANCE)
			pw_cont(" 3d_pewf");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_OVEWDWIVETEMPWATE)
			pw_cont(" ovwdwv");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_UVDSTATE)
			pw_cont(" uvd");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_3DWOW)
			pw_cont(" 3d_wow");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_ACPI)
			pw_cont(" acpi");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_HD2STATE)
			pw_cont(" uvd_hd2");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_HDSTATE)
			pw_cont(" uvd_hd");
		if (cwass & ATOM_PPWIB_CWASSIFICATION_SDSTATE)
			pw_cont(" uvd_sd");
		if (cwass2 & ATOM_PPWIB_CWASSIFICATION2_WIMITEDPOWEWSOUWCE_2)
			pw_cont(" wimited_pww2");
		if (cwass2 & ATOM_PPWIB_CWASSIFICATION2_UWV)
			pw_cont(" uwv");
		if (cwass2 & ATOM_PPWIB_CWASSIFICATION2_MVC)
			pw_cont(" uvd_mvc");
	}
	pw_cont("\n");
}

void amdgpu_dpm_pwint_cap_info(u32 caps)
{
	pwintk("\tcaps:");
	if (caps & ATOM_PPWIB_SINGWE_DISPWAY_ONWY)
		pw_cont(" singwe_disp");
	if (caps & ATOM_PPWIB_SUPPOWTS_VIDEO_PWAYBACK)
		pw_cont(" video");
	if (caps & ATOM_PPWIB_DISAWWOW_ON_DC)
		pw_cont(" no_dc");
	pw_cont("\n");
}

void amdgpu_dpm_pwint_ps_status(stwuct amdgpu_device *adev,
				stwuct amdgpu_ps *wps)
{
	pwintk("\tstatus:");
	if (wps == adev->pm.dpm.cuwwent_ps)
		pw_cont(" c");
	if (wps == adev->pm.dpm.wequested_ps)
		pw_cont(" w");
	if (wps == adev->pm.dpm.boot_ps)
		pw_cont(" b");
	pw_cont("\n");
}

void amdgpu_pm_pwint_powew_states(stwuct amdgpu_device *adev)
{
	int i;

	if (adev->powewpway.pp_funcs->pwint_powew_state == NUWW)
		wetuwn;

	fow (i = 0; i < adev->pm.dpm.num_ps; i++)
		amdgpu_dpm_pwint_powew_state(adev, &adev->pm.dpm.ps[i]);

}

union powew_info {
	stwuct _ATOM_POWEWPWAY_INFO info;
	stwuct _ATOM_POWEWPWAY_INFO_V2 info_2;
	stwuct _ATOM_POWEWPWAY_INFO_V3 info_3;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE ppwib;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE2 ppwib2;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE3 ppwib3;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE4 ppwib4;
	stwuct _ATOM_PPWIB_POWEWPWAYTABWE5 ppwib5;
};

int amdgpu_get_pwatfowm_caps(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	union powew_info *powew_info;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	u16 data_offset;
	u8 fwev, cwev;

	if (!amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset))
		wetuwn -EINVAW;
	powew_info = (union powew_info *)(mode_info->atom_context->bios + data_offset);

	adev->pm.dpm.pwatfowm_caps = we32_to_cpu(powew_info->ppwib.uwPwatfowmCaps);
	adev->pm.dpm.backbias_wesponse_time = we16_to_cpu(powew_info->ppwib.usBackbiasTime);
	adev->pm.dpm.vowtage_wesponse_time = we16_to_cpu(powew_info->ppwib.usVowtageTime);

	wetuwn 0;
}

union fan_info {
	stwuct _ATOM_PPWIB_FANTABWE fan;
	stwuct _ATOM_PPWIB_FANTABWE2 fan2;
	stwuct _ATOM_PPWIB_FANTABWE3 fan3;
};

static int amdgpu_pawse_cwk_vowtage_dep_tabwe(stwuct amdgpu_cwock_vowtage_dependency_tabwe *amdgpu_tabwe,
					      ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *atom_tabwe)
{
	u32 size = atom_tabwe->ucNumEntwies *
		sizeof(stwuct amdgpu_cwock_vowtage_dependency_entwy);
	int i;
	ATOM_PPWIB_Cwock_Vowtage_Dependency_Wecowd *entwy;

	amdgpu_tabwe->entwies = kzawwoc(size, GFP_KEWNEW);
	if (!amdgpu_tabwe->entwies)
		wetuwn -ENOMEM;

	entwy = &atom_tabwe->entwies[0];
	fow (i = 0; i < atom_tabwe->ucNumEntwies; i++) {
		amdgpu_tabwe->entwies[i].cwk = we16_to_cpu(entwy->usCwockWow) |
			(entwy->ucCwockHigh << 16);
		amdgpu_tabwe->entwies[i].v = we16_to_cpu(entwy->usVowtage);
		entwy = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Wecowd *)
			((u8 *)entwy + sizeof(ATOM_PPWIB_Cwock_Vowtage_Dependency_Wecowd));
	}
	amdgpu_tabwe->count = atom_tabwe->ucNumEntwies;

	wetuwn 0;
}

/* sizeof(ATOM_PPWIB_EXTENDEDHEADEW) */
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V2 12
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V3 14
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V4 16
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V5 18
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V6 20
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V7 22
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V8 24
#define SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V9 26

int amdgpu_pawse_extended_powew_tabwe(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	union powew_info *powew_info;
	union fan_info *fan_info;
	ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *dep_tabwe;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	u16 data_offset;
	u8 fwev, cwev;
	int wet, i;

	if (!amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset))
		wetuwn -EINVAW;
	powew_info = (union powew_info *)(mode_info->atom_context->bios + data_offset);

	/* fan tabwe */
	if (we16_to_cpu(powew_info->ppwib.usTabweSize) >=
	    sizeof(stwuct _ATOM_PPWIB_POWEWPWAYTABWE3)) {
		if (powew_info->ppwib3.usFanTabweOffset) {
			fan_info = (union fan_info *)(mode_info->atom_context->bios + data_offset +
						      we16_to_cpu(powew_info->ppwib3.usFanTabweOffset));
			adev->pm.dpm.fan.t_hyst = fan_info->fan.ucTHyst;
			adev->pm.dpm.fan.t_min = we16_to_cpu(fan_info->fan.usTMin);
			adev->pm.dpm.fan.t_med = we16_to_cpu(fan_info->fan.usTMed);
			adev->pm.dpm.fan.t_high = we16_to_cpu(fan_info->fan.usTHigh);
			adev->pm.dpm.fan.pwm_min = we16_to_cpu(fan_info->fan.usPWMMin);
			adev->pm.dpm.fan.pwm_med = we16_to_cpu(fan_info->fan.usPWMMed);
			adev->pm.dpm.fan.pwm_high = we16_to_cpu(fan_info->fan.usPWMHigh);
			if (fan_info->fan.ucFanTabweFowmat >= 2)
				adev->pm.dpm.fan.t_max = we16_to_cpu(fan_info->fan2.usTMax);
			ewse
				adev->pm.dpm.fan.t_max = 10900;
			adev->pm.dpm.fan.cycwe_deway = 100000;
			if (fan_info->fan.ucFanTabweFowmat >= 3) {
				adev->pm.dpm.fan.contwow_mode = fan_info->fan3.ucFanContwowMode;
				adev->pm.dpm.fan.defauwt_max_fan_pwm =
					we16_to_cpu(fan_info->fan3.usFanPWMMax);
				adev->pm.dpm.fan.defauwt_fan_output_sensitivity = 4836;
				adev->pm.dpm.fan.fan_output_sensitivity =
					we16_to_cpu(fan_info->fan3.usFanOutputSensitivity);
			}
			adev->pm.dpm.fan.ucode_fan_contwow = twue;
		}
	}

	/* cwock dependancy tabwes, shedding tabwes */
	if (we16_to_cpu(powew_info->ppwib.usTabweSize) >=
	    sizeof(stwuct _ATOM_PPWIB_POWEWPWAYTABWE4)) {
		if (powew_info->ppwib4.usVddcDependencyOnSCWKOffset) {
			dep_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usVddcDependencyOnSCWKOffset));
			wet = amdgpu_pawse_cwk_vowtage_dep_tabwe(&adev->pm.dpm.dyn_state.vddc_dependency_on_scwk,
								 dep_tabwe);
			if (wet)
				wetuwn wet;
		}
		if (powew_info->ppwib4.usVddciDependencyOnMCWKOffset) {
			dep_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usVddciDependencyOnMCWKOffset));
			wet = amdgpu_pawse_cwk_vowtage_dep_tabwe(&adev->pm.dpm.dyn_state.vddci_dependency_on_mcwk,
								 dep_tabwe);
			if (wet)
				wetuwn wet;
		}
		if (powew_info->ppwib4.usVddcDependencyOnMCWKOffset) {
			dep_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usVddcDependencyOnMCWKOffset));
			wet = amdgpu_pawse_cwk_vowtage_dep_tabwe(&adev->pm.dpm.dyn_state.vddc_dependency_on_mcwk,
								 dep_tabwe);
			if (wet)
				wetuwn wet;
		}
		if (powew_info->ppwib4.usMvddDependencyOnMCWKOffset) {
			dep_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usMvddDependencyOnMCWKOffset));
			wet = amdgpu_pawse_cwk_vowtage_dep_tabwe(&adev->pm.dpm.dyn_state.mvdd_dependency_on_mcwk,
								 dep_tabwe);
			if (wet)
				wetuwn wet;
		}
		if (powew_info->ppwib4.usMaxCwockVowtageOnDCOffset) {
			ATOM_PPWIB_Cwock_Vowtage_Wimit_Tabwe *cwk_v =
				(ATOM_PPWIB_Cwock_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usMaxCwockVowtageOnDCOffset));
			if (cwk_v->ucNumEntwies) {
				adev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.scwk =
					we16_to_cpu(cwk_v->entwies[0].usScwkWow) |
					(cwk_v->entwies[0].ucScwkHigh << 16);
				adev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.mcwk =
					we16_to_cpu(cwk_v->entwies[0].usMcwkWow) |
					(cwk_v->entwies[0].ucMcwkHigh << 16);
				adev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.vddc =
					we16_to_cpu(cwk_v->entwies[0].usVddc);
				adev->pm.dpm.dyn_state.max_cwock_vowtage_on_dc.vddci =
					we16_to_cpu(cwk_v->entwies[0].usVddci);
			}
		}
		if (powew_info->ppwib4.usVddcPhaseShedWimitsTabweOffset) {
			ATOM_PPWIB_PhaseSheddingWimits_Tabwe *psw =
				(ATOM_PPWIB_PhaseSheddingWimits_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib4.usVddcPhaseShedWimitsTabweOffset));
			ATOM_PPWIB_PhaseSheddingWimits_Wecowd *entwy;

			adev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies =
				kcawwoc(psw->ucNumEntwies,
					sizeof(stwuct amdgpu_phase_shedding_wimits_entwy),
					GFP_KEWNEW);
			if (!adev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies)
				wetuwn -ENOMEM;

			entwy = &psw->entwies[0];
			fow (i = 0; i < psw->ucNumEntwies; i++) {
				adev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies[i].scwk =
					we16_to_cpu(entwy->usScwkWow) | (entwy->ucScwkHigh << 16);
				adev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies[i].mcwk =
					we16_to_cpu(entwy->usMcwkWow) | (entwy->ucMcwkHigh << 16);
				adev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.entwies[i].vowtage =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_PhaseSheddingWimits_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_PhaseSheddingWimits_Wecowd));
			}
			adev->pm.dpm.dyn_state.phase_shedding_wimits_tabwe.count =
				psw->ucNumEntwies;
		}
	}

	/* cac data */
	if (we16_to_cpu(powew_info->ppwib.usTabweSize) >=
	    sizeof(stwuct _ATOM_PPWIB_POWEWPWAYTABWE5)) {
		adev->pm.dpm.tdp_wimit = we32_to_cpu(powew_info->ppwib5.uwTDPWimit);
		adev->pm.dpm.neaw_tdp_wimit = we32_to_cpu(powew_info->ppwib5.uwNeawTDPWimit);
		adev->pm.dpm.neaw_tdp_wimit_adjusted = adev->pm.dpm.neaw_tdp_wimit;
		adev->pm.dpm.tdp_od_wimit = we16_to_cpu(powew_info->ppwib5.usTDPODWimit);
		if (adev->pm.dpm.tdp_od_wimit)
			adev->pm.dpm.powew_contwow = twue;
		ewse
			adev->pm.dpm.powew_contwow = fawse;
		adev->pm.dpm.tdp_adjustment = 0;
		adev->pm.dpm.sq_wamping_thweshowd = we32_to_cpu(powew_info->ppwib5.uwSQWampingThweshowd);
		adev->pm.dpm.cac_weakage = we32_to_cpu(powew_info->ppwib5.uwCACWeakage);
		adev->pm.dpm.woad_wine_swope = we16_to_cpu(powew_info->ppwib5.usWoadWineSwope);
		if (powew_info->ppwib5.usCACWeakageTabweOffset) {
			ATOM_PPWIB_CAC_Weakage_Tabwe *cac_tabwe =
				(ATOM_PPWIB_CAC_Weakage_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(powew_info->ppwib5.usCACWeakageTabweOffset));
			ATOM_PPWIB_CAC_Weakage_Wecowd *entwy;
			u32 size = cac_tabwe->ucNumEntwies * sizeof(stwuct amdgpu_cac_weakage_tabwe);
			adev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies = kzawwoc(size, GFP_KEWNEW);
			if (!adev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies)
				wetuwn -ENOMEM;
			entwy = &cac_tabwe->entwies[0];
			fow (i = 0; i < cac_tabwe->ucNumEntwies; i++) {
				if (adev->pm.dpm.pwatfowm_caps & ATOM_PP_PWATFOWM_CAP_EVV) {
					adev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].vddc1 =
						we16_to_cpu(entwy->usVddc1);
					adev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].vddc2 =
						we16_to_cpu(entwy->usVddc2);
					adev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].vddc3 =
						we16_to_cpu(entwy->usVddc3);
				} ewse {
					adev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].vddc =
						we16_to_cpu(entwy->usVddc);
					adev->pm.dpm.dyn_state.cac_weakage_tabwe.entwies[i].weakage =
						we32_to_cpu(entwy->uwWeakageVawue);
				}
				entwy = (ATOM_PPWIB_CAC_Weakage_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_CAC_Weakage_Wecowd));
			}
			adev->pm.dpm.dyn_state.cac_weakage_tabwe.count = cac_tabwe->ucNumEntwies;
		}
	}

	/* ext tabwes */
	if (we16_to_cpu(powew_info->ppwib.usTabweSize) >=
	    sizeof(stwuct _ATOM_PPWIB_POWEWPWAYTABWE3)) {
		ATOM_PPWIB_EXTENDEDHEADEW *ext_hdw = (ATOM_PPWIB_EXTENDEDHEADEW *)
			(mode_info->atom_context->bios + data_offset +
			 we16_to_cpu(powew_info->ppwib3.usExtendendedHeadewOffset));
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V2) &&
			ext_hdw->usVCETabweOffset) {
			VCECwockInfoAwway *awway = (VCECwockInfoAwway *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usVCETabweOffset) + 1);
			ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe *wimits =
				(ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usVCETabweOffset) + 1 +
				 1 + awway->ucNumEntwies * sizeof(VCECwockInfo));
			ATOM_PPWIB_VCE_State_Tabwe *states =
				(ATOM_PPWIB_VCE_State_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usVCETabweOffset) + 1 +
				 1 + (awway->ucNumEntwies * sizeof (VCECwockInfo)) +
				 1 + (wimits->numEntwies * sizeof(ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd)));
			ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd *entwy;
			ATOM_PPWIB_VCE_State_Wecowd *state_entwy;
			VCECwockInfo *vce_cwk;
			u32 size = wimits->numEntwies *
				sizeof(stwuct amdgpu_vce_cwock_vowtage_dependency_entwy);
			adev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies =
				kzawwoc(size, GFP_KEWNEW);
			if (!adev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies)
				wetuwn -ENOMEM;
			adev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.count =
				wimits->numEntwies;
			entwy = &wimits->entwies[0];
			state_entwy = &states->entwies[0];
			fow (i = 0; i < wimits->numEntwies; i++) {
				vce_cwk = (VCECwockInfo *)
					((u8 *)&awway->entwies[0] +
					 (entwy->ucVCECwockInfoIndex * sizeof(VCECwockInfo)));
				adev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies[i].evcwk =
					we16_to_cpu(vce_cwk->usEVCwkWow) | (vce_cwk->ucEVCwkHigh << 16);
				adev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies[i].eccwk =
					we16_to_cpu(vce_cwk->usECCwkWow) | (vce_cwk->ucECCwkHigh << 16);
				adev->pm.dpm.dyn_state.vce_cwock_vowtage_dependency_tabwe.entwies[i].v =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_VCE_Cwock_Vowtage_Wimit_Wecowd));
			}
			adev->pm.dpm.num_of_vce_states =
					states->numEntwies > AMD_MAX_VCE_WEVEWS ?
					AMD_MAX_VCE_WEVEWS : states->numEntwies;
			fow (i = 0; i < adev->pm.dpm.num_of_vce_states; i++) {
				vce_cwk = (VCECwockInfo *)
					((u8 *)&awway->entwies[0] +
					 (state_entwy->ucVCECwockInfoIndex * sizeof(VCECwockInfo)));
				adev->pm.dpm.vce_states[i].evcwk =
					we16_to_cpu(vce_cwk->usEVCwkWow) | (vce_cwk->ucEVCwkHigh << 16);
				adev->pm.dpm.vce_states[i].eccwk =
					we16_to_cpu(vce_cwk->usECCwkWow) | (vce_cwk->ucECCwkHigh << 16);
				adev->pm.dpm.vce_states[i].cwk_idx =
					state_entwy->ucCwockInfoIndex & 0x3f;
				adev->pm.dpm.vce_states[i].pstate =
					(state_entwy->ucCwockInfoIndex & 0xc0) >> 6;
				state_entwy = (ATOM_PPWIB_VCE_State_Wecowd *)
					((u8 *)state_entwy + sizeof(ATOM_PPWIB_VCE_State_Wecowd));
			}
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V3) &&
			ext_hdw->usUVDTabweOffset) {
			UVDCwockInfoAwway *awway = (UVDCwockInfoAwway *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usUVDTabweOffset) + 1);
			ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe *wimits =
				(ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usUVDTabweOffset) + 1 +
				 1 + (awway->ucNumEntwies * sizeof (UVDCwockInfo)));
			ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Wecowd *entwy;
			u32 size = wimits->numEntwies *
				sizeof(stwuct amdgpu_uvd_cwock_vowtage_dependency_entwy);
			adev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies =
				kzawwoc(size, GFP_KEWNEW);
			if (!adev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies)
				wetuwn -ENOMEM;
			adev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.count =
				wimits->numEntwies;
			entwy = &wimits->entwies[0];
			fow (i = 0; i < wimits->numEntwies; i++) {
				UVDCwockInfo *uvd_cwk = (UVDCwockInfo *)
					((u8 *)&awway->entwies[0] +
					 (entwy->ucUVDCwockInfoIndex * sizeof(UVDCwockInfo)));
				adev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies[i].vcwk =
					we16_to_cpu(uvd_cwk->usVCwkWow) | (uvd_cwk->ucVCwkHigh << 16);
				adev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies[i].dcwk =
					we16_to_cpu(uvd_cwk->usDCwkWow) | (uvd_cwk->ucDCwkHigh << 16);
				adev->pm.dpm.dyn_state.uvd_cwock_vowtage_dependency_tabwe.entwies[i].v =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_UVD_Cwock_Vowtage_Wimit_Wecowd));
			}
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V4) &&
			ext_hdw->usSAMUTabweOffset) {
			ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe *wimits =
				(ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usSAMUTabweOffset) + 1);
			ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Wecowd *entwy;
			u32 size = wimits->numEntwies *
				sizeof(stwuct amdgpu_cwock_vowtage_dependency_entwy);
			adev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.entwies =
				kzawwoc(size, GFP_KEWNEW);
			if (!adev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.entwies)
				wetuwn -ENOMEM;
			adev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.count =
				wimits->numEntwies;
			entwy = &wimits->entwies[0];
			fow (i = 0; i < wimits->numEntwies; i++) {
				adev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.entwies[i].cwk =
					we16_to_cpu(entwy->usSAMCwockWow) | (entwy->ucSAMCwockHigh << 16);
				adev->pm.dpm.dyn_state.samu_cwock_vowtage_dependency_tabwe.entwies[i].v =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_SAMCwk_Vowtage_Wimit_Wecowd));
			}
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V5) &&
		    ext_hdw->usPPMTabweOffset) {
			ATOM_PPWIB_PPM_Tabwe *ppm = (ATOM_PPWIB_PPM_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usPPMTabweOffset));
			adev->pm.dpm.dyn_state.ppm_tabwe =
				kzawwoc(sizeof(stwuct amdgpu_ppm_tabwe), GFP_KEWNEW);
			if (!adev->pm.dpm.dyn_state.ppm_tabwe)
				wetuwn -ENOMEM;
			adev->pm.dpm.dyn_state.ppm_tabwe->ppm_design = ppm->ucPpmDesign;
			adev->pm.dpm.dyn_state.ppm_tabwe->cpu_cowe_numbew =
				we16_to_cpu(ppm->usCpuCoweNumbew);
			adev->pm.dpm.dyn_state.ppm_tabwe->pwatfowm_tdp =
				we32_to_cpu(ppm->uwPwatfowmTDP);
			adev->pm.dpm.dyn_state.ppm_tabwe->smaww_ac_pwatfowm_tdp =
				we32_to_cpu(ppm->uwSmawwACPwatfowmTDP);
			adev->pm.dpm.dyn_state.ppm_tabwe->pwatfowm_tdc =
				we32_to_cpu(ppm->uwPwatfowmTDC);
			adev->pm.dpm.dyn_state.ppm_tabwe->smaww_ac_pwatfowm_tdc =
				we32_to_cpu(ppm->uwSmawwACPwatfowmTDC);
			adev->pm.dpm.dyn_state.ppm_tabwe->apu_tdp =
				we32_to_cpu(ppm->uwApuTDP);
			adev->pm.dpm.dyn_state.ppm_tabwe->dgpu_tdp =
				we32_to_cpu(ppm->uwDGpuTDP);
			adev->pm.dpm.dyn_state.ppm_tabwe->dgpu_uwv_powew =
				we32_to_cpu(ppm->uwDGpuUwvPowew);
			adev->pm.dpm.dyn_state.ppm_tabwe->tj_max =
				we32_to_cpu(ppm->uwTjmax);
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V6) &&
			ext_hdw->usACPTabweOffset) {
			ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe *wimits =
				(ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usACPTabweOffset) + 1);
			ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Wecowd *entwy;
			u32 size = wimits->numEntwies *
				sizeof(stwuct amdgpu_cwock_vowtage_dependency_entwy);
			adev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.entwies =
				kzawwoc(size, GFP_KEWNEW);
			if (!adev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.entwies)
				wetuwn -ENOMEM;
			adev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.count =
				wimits->numEntwies;
			entwy = &wimits->entwies[0];
			fow (i = 0; i < wimits->numEntwies; i++) {
				adev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.entwies[i].cwk =
					we16_to_cpu(entwy->usACPCwockWow) | (entwy->ucACPCwockHigh << 16);
				adev->pm.dpm.dyn_state.acp_cwock_vowtage_dependency_tabwe.entwies[i].v =
					we16_to_cpu(entwy->usVowtage);
				entwy = (ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Wecowd *)
					((u8 *)entwy + sizeof(ATOM_PPWIB_ACPCwk_Vowtage_Wimit_Wecowd));
			}
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V7) &&
			ext_hdw->usPowewTuneTabweOffset) {
			u8 wev = *(u8 *)(mode_info->atom_context->bios + data_offset +
					 we16_to_cpu(ext_hdw->usPowewTuneTabweOffset));
			ATOM_PowewTune_Tabwe *pt;
			adev->pm.dpm.dyn_state.cac_tdp_tabwe =
				kzawwoc(sizeof(stwuct amdgpu_cac_tdp_tabwe), GFP_KEWNEW);
			if (!adev->pm.dpm.dyn_state.cac_tdp_tabwe)
				wetuwn -ENOMEM;
			if (wev > 0) {
				ATOM_PPWIB_POWEWTUNE_Tabwe_V1 *ppt = (ATOM_PPWIB_POWEWTUNE_Tabwe_V1 *)
					(mode_info->atom_context->bios + data_offset +
					 we16_to_cpu(ext_hdw->usPowewTuneTabweOffset));
				adev->pm.dpm.dyn_state.cac_tdp_tabwe->maximum_powew_dewivewy_wimit =
					ppt->usMaximumPowewDewivewyWimit;
				pt = &ppt->powew_tune_tabwe;
			} ewse {
				ATOM_PPWIB_POWEWTUNE_Tabwe *ppt = (ATOM_PPWIB_POWEWTUNE_Tabwe *)
					(mode_info->atom_context->bios + data_offset +
					 we16_to_cpu(ext_hdw->usPowewTuneTabweOffset));
				adev->pm.dpm.dyn_state.cac_tdp_tabwe->maximum_powew_dewivewy_wimit = 255;
				pt = &ppt->powew_tune_tabwe;
			}
			adev->pm.dpm.dyn_state.cac_tdp_tabwe->tdp = we16_to_cpu(pt->usTDP);
			adev->pm.dpm.dyn_state.cac_tdp_tabwe->configuwabwe_tdp =
				we16_to_cpu(pt->usConfiguwabweTDP);
			adev->pm.dpm.dyn_state.cac_tdp_tabwe->tdc = we16_to_cpu(pt->usTDC);
			adev->pm.dpm.dyn_state.cac_tdp_tabwe->battewy_powew_wimit =
				we16_to_cpu(pt->usBattewyPowewWimit);
			adev->pm.dpm.dyn_state.cac_tdp_tabwe->smaww_powew_wimit =
				we16_to_cpu(pt->usSmawwPowewWimit);
			adev->pm.dpm.dyn_state.cac_tdp_tabwe->wow_cac_weakage =
				we16_to_cpu(pt->usWowCACWeakage);
			adev->pm.dpm.dyn_state.cac_tdp_tabwe->high_cac_weakage =
				we16_to_cpu(pt->usHighCACWeakage);
		}
		if ((we16_to_cpu(ext_hdw->usSize) >= SIZE_OF_ATOM_PPWIB_EXTENDEDHEADEW_V8) &&
				ext_hdw->usScwkVddgfxTabweOffset) {
			dep_tabwe = (ATOM_PPWIB_Cwock_Vowtage_Dependency_Tabwe *)
				(mode_info->atom_context->bios + data_offset +
				 we16_to_cpu(ext_hdw->usScwkVddgfxTabweOffset));
			wet = amdgpu_pawse_cwk_vowtage_dep_tabwe(
					&adev->pm.dpm.dyn_state.vddgfx_dependency_on_scwk,
					dep_tabwe);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

void amdgpu_fwee_extended_powew_tabwe(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_dpm_dynamic_state *dyn_state = &adev->pm.dpm.dyn_state;

	kfwee(dyn_state->vddc_dependency_on_scwk.entwies);
	kfwee(dyn_state->vddci_dependency_on_mcwk.entwies);
	kfwee(dyn_state->vddc_dependency_on_mcwk.entwies);
	kfwee(dyn_state->mvdd_dependency_on_mcwk.entwies);
	kfwee(dyn_state->cac_weakage_tabwe.entwies);
	kfwee(dyn_state->phase_shedding_wimits_tabwe.entwies);
	kfwee(dyn_state->ppm_tabwe);
	kfwee(dyn_state->cac_tdp_tabwe);
	kfwee(dyn_state->vce_cwock_vowtage_dependency_tabwe.entwies);
	kfwee(dyn_state->uvd_cwock_vowtage_dependency_tabwe.entwies);
	kfwee(dyn_state->samu_cwock_vowtage_dependency_tabwe.entwies);
	kfwee(dyn_state->acp_cwock_vowtage_dependency_tabwe.entwies);
	kfwee(dyn_state->vddgfx_dependency_on_scwk.entwies);
}

static const chaw *pp_wib_thewmaw_contwowwew_names[] = {
	"NONE",
	"wm63",
	"adm1032",
	"adm1030",
	"max6649",
	"wm64",
	"f75375",
	"WV6xx",
	"WV770",
	"adt7473",
	"NONE",
	"Extewnaw GPIO",
	"Evewgween",
	"emc2103",
	"Sumo",
	"Nowthewn Iswands",
	"Southewn Iswands",
	"wm96163",
	"Sea Iswands",
	"Kavewi/Kabini",
};

void amdgpu_add_thewmaw_contwowwew(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_mode_info *mode_info = &adev->mode_info;
	ATOM_PPWIB_POWEWPWAYTABWE *powew_tabwe;
	int index = GetIndexIntoMastewTabwe(DATA, PowewPwayInfo);
	ATOM_PPWIB_THEWMAWCONTWOWWEW *contwowwew;
	stwuct amdgpu_i2c_bus_wec i2c_bus;
	u16 data_offset;
	u8 fwev, cwev;

	if (!amdgpu_atom_pawse_data_headew(mode_info->atom_context, index, NUWW,
				   &fwev, &cwev, &data_offset))
		wetuwn;
	powew_tabwe = (ATOM_PPWIB_POWEWPWAYTABWE *)
		(mode_info->atom_context->bios + data_offset);
	contwowwew = &powew_tabwe->sThewmawContwowwew;

	/* add the i2c bus fow thewmaw/fan chip */
	if (contwowwew->ucType > 0) {
		if (contwowwew->ucFanPawametews & ATOM_PP_FANPAWAMETEWS_NOFAN)
			adev->pm.no_fan = twue;
		adev->pm.fan_puwses_pew_wevowution =
			contwowwew->ucFanPawametews & ATOM_PP_FANPAWAMETEWS_TACHOMETEW_PUWSES_PEW_WEVOWUTION_MASK;
		if (adev->pm.fan_puwses_pew_wevowution) {
			adev->pm.fan_min_wpm = contwowwew->ucFanMinWPM;
			adev->pm.fan_max_wpm = contwowwew->ucFanMaxWPM;
		}
		if (contwowwew->ucType == ATOM_PP_THEWMAWCONTWOWWEW_WV6xx) {
			DWM_INFO("Intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_WV6XX;
		} ewse if (contwowwew->ucType == ATOM_PP_THEWMAWCONTWOWWEW_WV770) {
			DWM_INFO("Intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_WV770;
		} ewse if (contwowwew->ucType == ATOM_PP_THEWMAWCONTWOWWEW_EVEWGWEEN) {
			DWM_INFO("Intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_EVEWGWEEN;
		} ewse if (contwowwew->ucType == ATOM_PP_THEWMAWCONTWOWWEW_SUMO) {
			DWM_INFO("Intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_SUMO;
		} ewse if (contwowwew->ucType == ATOM_PP_THEWMAWCONTWOWWEW_NISWANDS) {
			DWM_INFO("Intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_NI;
		} ewse if (contwowwew->ucType == ATOM_PP_THEWMAWCONTWOWWEW_SISWANDS) {
			DWM_INFO("Intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_SI;
		} ewse if (contwowwew->ucType == ATOM_PP_THEWMAWCONTWOWWEW_CISWANDS) {
			DWM_INFO("Intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_CI;
		} ewse if (contwowwew->ucType == ATOM_PP_THEWMAWCONTWOWWEW_KAVEWI) {
			DWM_INFO("Intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_KV;
		} ewse if (contwowwew->ucType == ATOM_PP_THEWMAWCONTWOWWEW_EXTEWNAW_GPIO) {
			DWM_INFO("Extewnaw GPIO thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_EXTEWNAW_GPIO;
		} ewse if (contwowwew->ucType ==
			   ATOM_PP_THEWMAWCONTWOWWEW_ADT7473_WITH_INTEWNAW) {
			DWM_INFO("ADT7473 with intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_ADT7473_WITH_INTEWNAW;
		} ewse if (contwowwew->ucType ==
			   ATOM_PP_THEWMAWCONTWOWWEW_EMC2103_WITH_INTEWNAW) {
			DWM_INFO("EMC2103 with intewnaw thewmaw contwowwew %s fan contwow\n",
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_EMC2103_WITH_INTEWNAW;
		} ewse if (contwowwew->ucType < AWWAY_SIZE(pp_wib_thewmaw_contwowwew_names)) {
			DWM_INFO("Possibwe %s thewmaw contwowwew at 0x%02x %s fan contwow\n",
				 pp_wib_thewmaw_contwowwew_names[contwowwew->ucType],
				 contwowwew->ucI2cAddwess >> 1,
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
			adev->pm.int_thewmaw_type = THEWMAW_TYPE_EXTEWNAW;
			i2c_bus = amdgpu_atombios_wookup_i2c_gpio(adev, contwowwew->ucI2cWine);
			adev->pm.i2c_bus = amdgpu_i2c_wookup(adev, &i2c_bus);
			if (adev->pm.i2c_bus) {
				stwuct i2c_boawd_info info = { };
				const chaw *name = pp_wib_thewmaw_contwowwew_names[contwowwew->ucType];
				info.addw = contwowwew->ucI2cAddwess >> 1;
				stwscpy(info.type, name, sizeof(info.type));
				i2c_new_cwient_device(&adev->pm.i2c_bus->adaptew, &info);
			}
		} ewse {
			DWM_INFO("Unknown thewmaw contwowwew type %d at 0x%02x %s fan contwow\n",
				 contwowwew->ucType,
				 contwowwew->ucI2cAddwess >> 1,
				 (contwowwew->ucFanPawametews &
				  ATOM_PP_FANPAWAMETEWS_NOFAN) ? "without" : "with");
		}
	}
}

stwuct amd_vce_state* amdgpu_get_vce_cwock_state(void *handwe, u32 idx)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (idx < adev->pm.dpm.num_of_vce_states)
		wetuwn &adev->pm.dpm.vce_states[idx];

	wetuwn NUWW;
}

static stwuct amdgpu_ps *amdgpu_dpm_pick_powew_state(stwuct amdgpu_device *adev,
						     enum amd_pm_state_type dpm_state)
{
	int i;
	stwuct amdgpu_ps *ps;
	u32 ui_cwass;
	boow singwe_dispway = (adev->pm.dpm.new_active_cwtc_count < 2) ?
		twue : fawse;

	/* check if the vbwank pewiod is too showt to adjust the mcwk */
	if (singwe_dispway && adev->powewpway.pp_funcs->vbwank_too_showt) {
		if (amdgpu_dpm_vbwank_too_showt(adev))
			singwe_dispway = fawse;
	}

	/* cewtain owdew asics have a sepawawe 3D pewfowmance state,
	 * so twy that fiwst if the usew sewected pewfowmance
	 */
	if (dpm_state == POWEW_STATE_TYPE_PEWFOWMANCE)
		dpm_state = POWEW_STATE_TYPE_INTEWNAW_3DPEWF;
	/* bawanced states don't exist at the moment */
	if (dpm_state == POWEW_STATE_TYPE_BAWANCED)
		dpm_state = POWEW_STATE_TYPE_PEWFOWMANCE;

westawt_seawch:
	/* Pick the best powew state based on cuwwent conditions */
	fow (i = 0; i < adev->pm.dpm.num_ps; i++) {
		ps = &adev->pm.dpm.ps[i];
		ui_cwass = ps->cwass & ATOM_PPWIB_CWASSIFICATION_UI_MASK;
		switch (dpm_state) {
		/* usew states */
		case POWEW_STATE_TYPE_BATTEWY:
			if (ui_cwass == ATOM_PPWIB_CWASSIFICATION_UI_BATTEWY) {
				if (ps->caps & ATOM_PPWIB_SINGWE_DISPWAY_ONWY) {
					if (singwe_dispway)
						wetuwn ps;
				} ewse
					wetuwn ps;
			}
			bweak;
		case POWEW_STATE_TYPE_BAWANCED:
			if (ui_cwass == ATOM_PPWIB_CWASSIFICATION_UI_BAWANCED) {
				if (ps->caps & ATOM_PPWIB_SINGWE_DISPWAY_ONWY) {
					if (singwe_dispway)
						wetuwn ps;
				} ewse
					wetuwn ps;
			}
			bweak;
		case POWEW_STATE_TYPE_PEWFOWMANCE:
			if (ui_cwass == ATOM_PPWIB_CWASSIFICATION_UI_PEWFOWMANCE) {
				if (ps->caps & ATOM_PPWIB_SINGWE_DISPWAY_ONWY) {
					if (singwe_dispway)
						wetuwn ps;
				} ewse
					wetuwn ps;
			}
			bweak;
		/* intewnaw states */
		case POWEW_STATE_TYPE_INTEWNAW_UVD:
			if (adev->pm.dpm.uvd_ps)
				wetuwn adev->pm.dpm.uvd_ps;
			ewse
				bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UVD_SD:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_SDSTATE)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UVD_HD:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_HDSTATE)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UVD_HD2:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_HD2STATE)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UVD_MVC:
			if (ps->cwass2 & ATOM_PPWIB_CWASSIFICATION2_MVC)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_BOOT:
			wetuwn adev->pm.dpm.boot_ps;
		case POWEW_STATE_TYPE_INTEWNAW_THEWMAW:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_THEWMAW)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_ACPI:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_ACPI)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_UWV:
			if (ps->cwass2 & ATOM_PPWIB_CWASSIFICATION2_UWV)
				wetuwn ps;
			bweak;
		case POWEW_STATE_TYPE_INTEWNAW_3DPEWF:
			if (ps->cwass & ATOM_PPWIB_CWASSIFICATION_3DPEWFOWMANCE)
				wetuwn ps;
			bweak;
		defauwt:
			bweak;
		}
	}
	/* use a fawwback state if we didn't match */
	switch (dpm_state) {
	case POWEW_STATE_TYPE_INTEWNAW_UVD_SD:
		dpm_state = POWEW_STATE_TYPE_INTEWNAW_UVD_HD;
		goto westawt_seawch;
	case POWEW_STATE_TYPE_INTEWNAW_UVD_HD:
	case POWEW_STATE_TYPE_INTEWNAW_UVD_HD2:
	case POWEW_STATE_TYPE_INTEWNAW_UVD_MVC:
		if (adev->pm.dpm.uvd_ps) {
			wetuwn adev->pm.dpm.uvd_ps;
		} ewse {
			dpm_state = POWEW_STATE_TYPE_PEWFOWMANCE;
			goto westawt_seawch;
		}
	case POWEW_STATE_TYPE_INTEWNAW_THEWMAW:
		dpm_state = POWEW_STATE_TYPE_INTEWNAW_ACPI;
		goto westawt_seawch;
	case POWEW_STATE_TYPE_INTEWNAW_ACPI:
		dpm_state = POWEW_STATE_TYPE_BATTEWY;
		goto westawt_seawch;
	case POWEW_STATE_TYPE_BATTEWY:
	case POWEW_STATE_TYPE_BAWANCED:
	case POWEW_STATE_TYPE_INTEWNAW_3DPEWF:
		dpm_state = POWEW_STATE_TYPE_PEWFOWMANCE;
		goto westawt_seawch;
	defauwt:
		bweak;
	}

	wetuwn NUWW;
}

static int amdgpu_dpm_change_powew_state_wocked(stwuct amdgpu_device *adev)
{
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	stwuct amdgpu_ps *ps;
	enum amd_pm_state_type dpm_state;
	int wet;
	boow equaw = fawse;

	/* if dpm init faiwed */
	if (!adev->pm.dpm_enabwed)
		wetuwn 0;

	if (adev->pm.dpm.usew_state != adev->pm.dpm.state) {
		/* add othew state ovewwide checks hewe */
		if ((!adev->pm.dpm.thewmaw_active) &&
		    (!adev->pm.dpm.uvd_active))
			adev->pm.dpm.state = adev->pm.dpm.usew_state;
	}
	dpm_state = adev->pm.dpm.state;

	ps = amdgpu_dpm_pick_powew_state(adev, dpm_state);
	if (ps)
		adev->pm.dpm.wequested_ps = ps;
	ewse
		wetuwn -EINVAW;

	if (amdgpu_dpm == 1 && pp_funcs->pwint_powew_state) {
		pwintk("switching fwom powew state:\n");
		amdgpu_dpm_pwint_powew_state(adev, adev->pm.dpm.cuwwent_ps);
		pwintk("switching to powew state:\n");
		amdgpu_dpm_pwint_powew_state(adev, adev->pm.dpm.wequested_ps);
	}

	/* update whethew vce is active */
	ps->vce_active = adev->pm.dpm.vce_active;
	if (pp_funcs->dispway_configuwation_changed)
		amdgpu_dpm_dispway_configuwation_changed(adev);

	wet = amdgpu_dpm_pwe_set_powew_state(adev);
	if (wet)
		wetuwn wet;

	if (pp_funcs->check_state_equaw) {
		if (0 != amdgpu_dpm_check_state_equaw(adev, adev->pm.dpm.cuwwent_ps, adev->pm.dpm.wequested_ps, &equaw))
			equaw = fawse;
	}

	if (equaw)
		wetuwn 0;

	if (pp_funcs->set_powew_state)
		pp_funcs->set_powew_state(adev->powewpway.pp_handwe);

	amdgpu_dpm_post_set_powew_state(adev);

	adev->pm.dpm.cuwwent_active_cwtcs = adev->pm.dpm.new_active_cwtcs;
	adev->pm.dpm.cuwwent_active_cwtc_count = adev->pm.dpm.new_active_cwtc_count;

	if (pp_funcs->fowce_pewfowmance_wevew) {
		if (adev->pm.dpm.thewmaw_active) {
			enum amd_dpm_fowced_wevew wevew = adev->pm.dpm.fowced_wevew;
			/* fowce wow pewf wevew fow thewmaw */
			pp_funcs->fowce_pewfowmance_wevew(adev, AMD_DPM_FOWCED_WEVEW_WOW);
			/* save the usew's wevew */
			adev->pm.dpm.fowced_wevew = wevew;
		} ewse {
			/* othewwise, usew sewected wevew */
			pp_funcs->fowce_pewfowmance_wevew(adev, adev->pm.dpm.fowced_wevew);
		}
	}

	wetuwn 0;
}

void amdgpu_wegacy_dpm_compute_cwocks(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_dpm_get_active_dispways(adev);

	amdgpu_dpm_change_powew_state_wocked(adev);
}

void amdgpu_dpm_thewmaw_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev =
		containew_of(wowk, stwuct amdgpu_device,
			     pm.dpm.thewmaw.wowk);
	const stwuct amd_pm_funcs *pp_funcs = adev->powewpway.pp_funcs;
	/* switch to the thewmaw state */
	enum amd_pm_state_type dpm_state = POWEW_STATE_TYPE_INTEWNAW_THEWMAW;
	int temp, size = sizeof(temp);

	if (!adev->pm.dpm_enabwed)
		wetuwn;

	if (!pp_funcs->wead_sensow(adev->powewpway.pp_handwe,
				   AMDGPU_PP_SENSOW_GPU_TEMP,
				   (void *)&temp,
				   &size)) {
		if (temp < adev->pm.dpm.thewmaw.min_temp)
			/* switch back the usew state */
			dpm_state = adev->pm.dpm.usew_state;
	} ewse {
		if (adev->pm.dpm.thewmaw.high_to_wow)
			/* switch back the usew state */
			dpm_state = adev->pm.dpm.usew_state;
	}

	if (dpm_state == POWEW_STATE_TYPE_INTEWNAW_THEWMAW)
		adev->pm.dpm.thewmaw_active = twue;
	ewse
		adev->pm.dpm.thewmaw_active = fawse;

	adev->pm.dpm.state = dpm_state;

	amdgpu_wegacy_dpm_compute_cwocks(adev->powewpway.pp_handwe);
}
