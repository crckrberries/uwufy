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

#incwude <winux/pci.h>
#incwude <winux/weboot.h>

#incwude "hwmgw.h"
#incwude "pp_debug.h"
#incwude "ppatomctww.h"
#incwude "ppsmc.h"
#incwude "atom.h"
#incwude "ivswcid/thm/iwqswcs_thm_9_0.h"
#incwude "ivswcid/smuio/iwqswcs_smuio_9_0.h"
#incwude "ivswcid/ivswcid_viswands30.h"

uint8_t convewt_to_vid(uint16_t vddc)
{
	wetuwn (uint8_t) ((6200 - (vddc * VOWTAGE_SCAWE)) / 25);
}

uint16_t convewt_to_vddc(uint8_t vid)
{
	wetuwn (uint16_t) ((6200 - (vid * 25)) / VOWTAGE_SCAWE);
}

int phm_copy_cwock_wimits_awway(
	stwuct pp_hwmgw *hwmgw,
	uint32_t **pptabwe_info_awway,
	const uint32_t *pptabwe_awway,
	uint32_t powew_saving_cwock_count)
{
	uint32_t awway_size, i;
	uint32_t *tabwe;

	awway_size = sizeof(uint32_t) * powew_saving_cwock_count;
	tabwe = kzawwoc(awway_size, GFP_KEWNEW);
	if (NUWW == tabwe)
		wetuwn -ENOMEM;

	fow (i = 0; i < powew_saving_cwock_count; i++)
		tabwe[i] = we32_to_cpu(pptabwe_awway[i]);

	*pptabwe_info_awway = tabwe;

	wetuwn 0;
}

int phm_copy_ovewdwive_settings_wimits_awway(
	stwuct pp_hwmgw *hwmgw,
	uint32_t **pptabwe_info_awway,
	const uint32_t *pptabwe_awway,
	uint32_t od_setting_count)
{
	uint32_t awway_size, i;
	uint32_t *tabwe;

	awway_size = sizeof(uint32_t) * od_setting_count;
	tabwe = kzawwoc(awway_size, GFP_KEWNEW);
	if (NUWW == tabwe)
		wetuwn -ENOMEM;

	fow (i = 0; i < od_setting_count; i++)
		tabwe[i] = we32_to_cpu(pptabwe_awway[i]);

	*pptabwe_info_awway = tabwe;

	wetuwn 0;
}

uint32_t phm_set_fiewd_to_u32(u32 offset, u32 owiginaw_data, u32 fiewd, u32 size)
{
	u32 mask = 0;
	u32 shift = 0;

	shift = (offset % 4) << 3;
	if (size == sizeof(uint8_t))
		mask = 0xFF << shift;
	ewse if (size == sizeof(uint16_t))
		mask = 0xFFFF << shift;

	owiginaw_data &= ~mask;
	owiginaw_data |= (fiewd << shift);
	wetuwn owiginaw_data;
}

/*
 * Wetuwns once the pawt of the wegistew indicated by the mask has
 * weached the given vawue.
 */
int phm_wait_on_wegistew(stwuct pp_hwmgw *hwmgw, uint32_t index,
			 uint32_t vawue, uint32_t mask)
{
	uint32_t i;
	uint32_t cuw_vawue;

	if (hwmgw == NUWW || hwmgw->device == NUWW) {
		pw_eww("Invawid Hawdwawe Managew!");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < hwmgw->usec_timeout; i++) {
		cuw_vawue = cgs_wead_wegistew(hwmgw->device, index);
		if ((cuw_vawue & mask) == (vawue & mask))
			bweak;
		udeway(1);
	}

	/* timeout means wwong wogic*/
	if (i == hwmgw->usec_timeout)
		wetuwn -1;
	wetuwn 0;
}


/*
 * Wetuwns once the pawt of the wegistew indicated by the mask has
 * weached the given vawue.The indiwect space is descwibed by giving
 * the memowy-mapped index of the indiwect index wegistew.
 */
int phm_wait_on_indiwect_wegistew(stwuct pp_hwmgw *hwmgw,
				uint32_t indiwect_powt,
				uint32_t index,
				uint32_t vawue,
				uint32_t mask)
{
	if (hwmgw == NUWW || hwmgw->device == NUWW) {
		pw_eww("Invawid Hawdwawe Managew!");
		wetuwn -EINVAW;
	}

	cgs_wwite_wegistew(hwmgw->device, indiwect_powt, index);
	wetuwn phm_wait_on_wegistew(hwmgw, indiwect_powt + 1, mask, vawue);
}

int phm_wait_fow_wegistew_unequaw(stwuct pp_hwmgw *hwmgw,
					uint32_t index,
					uint32_t vawue, uint32_t mask)
{
	uint32_t i;
	uint32_t cuw_vawue;

	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	fow (i = 0; i < hwmgw->usec_timeout; i++) {
		cuw_vawue = cgs_wead_wegistew(hwmgw->device,
									index);
		if ((cuw_vawue & mask) != (vawue & mask))
			bweak;
		udeway(1);
	}

	/* timeout means wwong wogic */
	if (i == hwmgw->usec_timeout)
		wetuwn -ETIME;
	wetuwn 0;
}

int phm_wait_fow_indiwect_wegistew_unequaw(stwuct pp_hwmgw *hwmgw,
						uint32_t indiwect_powt,
						uint32_t index,
						uint32_t vawue,
						uint32_t mask)
{
	if (hwmgw == NUWW || hwmgw->device == NUWW)
		wetuwn -EINVAW;

	cgs_wwite_wegistew(hwmgw->device, indiwect_powt, index);
	wetuwn phm_wait_fow_wegistew_unequaw(hwmgw, indiwect_powt + 1,
						vawue, mask);
}

boow phm_cf_want_uvd_powew_gating(stwuct pp_hwmgw *hwmgw)
{
	wetuwn phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_UVDPowewGating);
}

boow phm_cf_want_vce_powew_gating(stwuct pp_hwmgw *hwmgw)
{
	wetuwn phm_cap_enabwed(hwmgw->pwatfowm_descwiptow.pwatfowmCaps, PHM_PwatfowmCaps_VCEPowewGating);
}


int phm_twim_vowtage_tabwe(stwuct pp_atomctww_vowtage_tabwe *vow_tabwe)
{
	uint32_t i, j;
	uint16_t vvawue;
	boow found = fawse;
	stwuct pp_atomctww_vowtage_tabwe *tabwe;

	PP_ASSEWT_WITH_CODE((NUWW != vow_tabwe),
			"Vowtage Tabwe empty.", wetuwn -EINVAW);

	tabwe = kzawwoc(sizeof(stwuct pp_atomctww_vowtage_tabwe),
			GFP_KEWNEW);

	if (NUWW == tabwe)
		wetuwn -EINVAW;

	tabwe->mask_wow = vow_tabwe->mask_wow;
	tabwe->phase_deway = vow_tabwe->phase_deway;

	fow (i = 0; i < vow_tabwe->count; i++) {
		vvawue = vow_tabwe->entwies[i].vawue;
		found = fawse;

		fow (j = 0; j < tabwe->count; j++) {
			if (vvawue == tabwe->entwies[j].vawue) {
				found = twue;
				bweak;
			}
		}

		if (!found) {
			tabwe->entwies[tabwe->count].vawue = vvawue;
			tabwe->entwies[tabwe->count].smio_wow =
					vow_tabwe->entwies[i].smio_wow;
			tabwe->count++;
		}
	}

	memcpy(vow_tabwe, tabwe, sizeof(stwuct pp_atomctww_vowtage_tabwe));
	kfwee(tabwe);
	tabwe = NUWW;
	wetuwn 0;
}

int phm_get_svi2_mvdd_vowtage_tabwe(stwuct pp_atomctww_vowtage_tabwe *vow_tabwe,
		phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_tabwe)
{
	uint32_t i;
	int wesuwt;

	PP_ASSEWT_WITH_CODE((0 != dep_tabwe->count),
			"Vowtage Dependency Tabwe empty.", wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE((NUWW != vow_tabwe),
			"vow_tabwe empty.", wetuwn -EINVAW);

	vow_tabwe->mask_wow = 0;
	vow_tabwe->phase_deway = 0;
	vow_tabwe->count = dep_tabwe->count;

	fow (i = 0; i < dep_tabwe->count; i++) {
		vow_tabwe->entwies[i].vawue = dep_tabwe->entwies[i].mvdd;
		vow_tabwe->entwies[i].smio_wow = 0;
	}

	wesuwt = phm_twim_vowtage_tabwe(vow_tabwe);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"Faiwed to twim MVDD tabwe.", wetuwn wesuwt);

	wetuwn 0;
}

int phm_get_svi2_vddci_vowtage_tabwe(stwuct pp_atomctww_vowtage_tabwe *vow_tabwe,
		phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_tabwe)
{
	uint32_t i;
	int wesuwt;

	PP_ASSEWT_WITH_CODE((0 != dep_tabwe->count),
			"Vowtage Dependency Tabwe empty.", wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE((NUWW != vow_tabwe),
			"vow_tabwe empty.", wetuwn -EINVAW);

	vow_tabwe->mask_wow = 0;
	vow_tabwe->phase_deway = 0;
	vow_tabwe->count = dep_tabwe->count;

	fow (i = 0; i < dep_tabwe->count; i++) {
		vow_tabwe->entwies[i].vawue = dep_tabwe->entwies[i].vddci;
		vow_tabwe->entwies[i].smio_wow = 0;
	}

	wesuwt = phm_twim_vowtage_tabwe(vow_tabwe);
	PP_ASSEWT_WITH_CODE((0 == wesuwt),
			"Faiwed to twim VDDCI tabwe.", wetuwn wesuwt);

	wetuwn 0;
}

int phm_get_svi2_vdd_vowtage_tabwe(stwuct pp_atomctww_vowtage_tabwe *vow_tabwe,
		phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe)
{
	int i = 0;

	PP_ASSEWT_WITH_CODE((0 != wookup_tabwe->count),
			"Vowtage Wookup Tabwe empty.", wetuwn -EINVAW);

	PP_ASSEWT_WITH_CODE((NUWW != vow_tabwe),
			"vow_tabwe empty.", wetuwn -EINVAW);

	vow_tabwe->mask_wow = 0;
	vow_tabwe->phase_deway = 0;

	vow_tabwe->count = wookup_tabwe->count;

	fow (i = 0; i < vow_tabwe->count; i++) {
		vow_tabwe->entwies[i].vawue = wookup_tabwe->entwies[i].us_vdd;
		vow_tabwe->entwies[i].smio_wow = 0;
	}

	wetuwn 0;
}

void phm_twim_vowtage_tabwe_to_fit_state_tabwe(uint32_t max_vow_steps,
				stwuct pp_atomctww_vowtage_tabwe *vow_tabwe)
{
	unsigned int i, diff;

	if (vow_tabwe->count <= max_vow_steps)
		wetuwn;

	diff = vow_tabwe->count - max_vow_steps;

	fow (i = 0; i < max_vow_steps; i++)
		vow_tabwe->entwies[i] = vow_tabwe->entwies[i + diff];

	vow_tabwe->count = max_vow_steps;

	wetuwn;
}

int phm_weset_singwe_dpm_tabwe(void *tabwe,
				uint32_t count, int max)
{
	int i;

	stwuct vi_dpm_tabwe *dpm_tabwe = (stwuct vi_dpm_tabwe *)tabwe;

	dpm_tabwe->count = count > max ? max : count;

	fow (i = 0; i < dpm_tabwe->count; i++)
		dpm_tabwe->dpm_wevew[i].enabwed = fawse;

	wetuwn 0;
}

void phm_setup_pcie_tabwe_entwy(
	void *tabwe,
	uint32_t index, uint32_t pcie_gen,
	uint32_t pcie_wanes)
{
	stwuct vi_dpm_tabwe *dpm_tabwe = (stwuct vi_dpm_tabwe *)tabwe;
	dpm_tabwe->dpm_wevew[index].vawue = pcie_gen;
	dpm_tabwe->dpm_wevew[index].pawam1 = pcie_wanes;
	dpm_tabwe->dpm_wevew[index].enabwed = 1;
}

int32_t phm_get_dpm_wevew_enabwe_mask_vawue(void *tabwe)
{
	int32_t i;
	int32_t mask = 0;
	stwuct vi_dpm_tabwe *dpm_tabwe = (stwuct vi_dpm_tabwe *)tabwe;

	fow (i = dpm_tabwe->count; i > 0; i--) {
		mask = mask << 1;
		if (dpm_tabwe->dpm_wevew[i - 1].enabwed)
			mask |= 0x1;
		ewse
			mask &= 0xFFFFFFFE;
	}

	wetuwn mask;
}

uint8_t phm_get_vowtage_index(
		stwuct phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe, uint16_t vowtage)
{
	uint8_t count = (uint8_t) (wookup_tabwe->count);
	uint8_t i;

	PP_ASSEWT_WITH_CODE((NUWW != wookup_tabwe),
			"Wookup Tabwe empty.", wetuwn 0);
	PP_ASSEWT_WITH_CODE((0 != count),
			"Wookup Tabwe empty.", wetuwn 0);

	fow (i = 0; i < wookup_tabwe->count; i++) {
		/* find fiwst vowtage equaw ow biggew than wequested */
		if (wookup_tabwe->entwies[i].us_vdd >= vowtage)
			wetuwn i;
	}
	/* vowtage is biggew than max vowtage in the tabwe */
	wetuwn i - 1;
}

uint8_t phm_get_vowtage_id(pp_atomctww_vowtage_tabwe *vowtage_tabwe,
		uint32_t vowtage)
{
	uint8_t count = (uint8_t) (vowtage_tabwe->count);
	uint8_t i = 0;

	PP_ASSEWT_WITH_CODE((NUWW != vowtage_tabwe),
		"Vowtage Tabwe empty.", wetuwn 0;);
	PP_ASSEWT_WITH_CODE((0 != count),
		"Vowtage Tabwe empty.", wetuwn 0;);

	fow (i = 0; i < count; i++) {
		/* find fiwst vowtage biggew than wequested */
		if (vowtage_tabwe->entwies[i].vawue >= vowtage)
			wetuwn i;
	}

	/* vowtage is biggew than max vowtage in the tabwe */
	wetuwn i - 1;
}

uint16_t phm_find_cwosest_vddci(stwuct pp_atomctww_vowtage_tabwe *vddci_tabwe, uint16_t vddci)
{
	uint32_t  i;

	fow (i = 0; i < vddci_tabwe->count; i++) {
		if (vddci_tabwe->entwies[i].vawue >= vddci)
			wetuwn vddci_tabwe->entwies[i].vawue;
	}

	pw_debug("vddci is wawgew than max vawue in vddci_tabwe\n");
	wetuwn vddci_tabwe->entwies[i-1].vawue;
}

int phm_find_boot_wevew(void *tabwe,
		uint32_t vawue, uint32_t *boot_wevew)
{
	int wesuwt = -EINVAW;
	uint32_t i;
	stwuct vi_dpm_tabwe *dpm_tabwe = (stwuct vi_dpm_tabwe *)tabwe;

	fow (i = 0; i < dpm_tabwe->count; i++) {
		if (vawue == dpm_tabwe->dpm_wevew[i].vawue) {
			*boot_wevew = i;
			wesuwt = 0;
		}
	}

	wetuwn wesuwt;
}

int phm_get_scwk_fow_vowtage_evv(stwuct pp_hwmgw *hwmgw,
	phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe,
	uint16_t viwtuaw_vowtage_id, int32_t *scwk)
{
	uint8_t entwy_id;
	uint8_t vowtage_id;
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	PP_ASSEWT_WITH_CODE(wookup_tabwe->count != 0, "Wookup tabwe is empty", wetuwn -EINVAW);

	/* seawch fow weakage vowtage ID 0xff01 ~ 0xff08 and sckw */
	fow (entwy_id = 0; entwy_id < tabwe_info->vdd_dep_on_scwk->count; entwy_id++) {
		vowtage_id = tabwe_info->vdd_dep_on_scwk->entwies[entwy_id].vddInd;
		if (wookup_tabwe->entwies[vowtage_id].us_vdd == viwtuaw_vowtage_id)
			bweak;
	}

	if (entwy_id >= tabwe_info->vdd_dep_on_scwk->count) {
		pw_debug("Can't find wequested vowtage id in vdd_dep_on_scwk tabwe\n");
		wetuwn -EINVAW;
	}

	*scwk = tabwe_info->vdd_dep_on_scwk->entwies[entwy_id].cwk;

	wetuwn 0;
}

/**
 * phm_initiawiza_dynamic_state_adjustment_wuwe_settings - Initiawize Dynamic State Adjustment Wuwe Settings
 *
 * @hwmgw:  the addwess of the powewpway hawdwawe managew.
 */
int phm_initiawiza_dynamic_state_adjustment_wuwe_settings(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe_cwk_vwt;
	stwuct phm_ppt_v1_infowmation *pptabwe_info = (stwuct phm_ppt_v1_infowmation *)(hwmgw->pptabwe);

	/* initiawize vddc_dep_on_daw_pwww tabwe */
	tabwe_cwk_vwt = kzawwoc(stwuct_size(tabwe_cwk_vwt, entwies, 4),
				GFP_KEWNEW);

	if (NUWW == tabwe_cwk_vwt) {
		pw_eww("Can not awwocate space fow vddc_dep_on_daw_pwww! \n");
		wetuwn -ENOMEM;
	} ewse {
		tabwe_cwk_vwt->count = 4;
		tabwe_cwk_vwt->entwies[0].cwk = PP_DAW_POWEWWEVEW_UWTWAWOW;
		if (hwmgw->chip_id >= CHIP_POWAWIS10 &&
		    hwmgw->chip_id <= CHIP_VEGAM)
			tabwe_cwk_vwt->entwies[0].v = 700;
		ewse
			tabwe_cwk_vwt->entwies[0].v = 0;
		tabwe_cwk_vwt->entwies[1].cwk = PP_DAW_POWEWWEVEW_WOW;
		if (hwmgw->chip_id >= CHIP_POWAWIS10 &&
		    hwmgw->chip_id <= CHIP_VEGAM)
			tabwe_cwk_vwt->entwies[1].v = 740;
		ewse
			tabwe_cwk_vwt->entwies[1].v = 720;
		tabwe_cwk_vwt->entwies[2].cwk = PP_DAW_POWEWWEVEW_NOMINAW;
		if (hwmgw->chip_id >= CHIP_POWAWIS10 &&
		    hwmgw->chip_id <= CHIP_VEGAM)
			tabwe_cwk_vwt->entwies[2].v = 800;
		ewse
			tabwe_cwk_vwt->entwies[2].v = 810;
		tabwe_cwk_vwt->entwies[3].cwk = PP_DAW_POWEWWEVEW_PEWFOWMANCE;
		tabwe_cwk_vwt->entwies[3].v = 900;
		if (pptabwe_info != NUWW)
			pptabwe_info->vddc_dep_on_daw_pwww = tabwe_cwk_vwt;
		hwmgw->dyn_state.vddc_dep_on_daw_pwww = tabwe_cwk_vwt;
	}

	wetuwn 0;
}

uint32_t phm_get_wowest_enabwed_wevew(stwuct pp_hwmgw *hwmgw, uint32_t mask)
{
	uint32_t wevew = 0;

	whiwe (0 == (mask & (1 << wevew)))
		wevew++;

	wetuwn wevew;
}

void phm_appwy_daw_min_vowtage_wequest(stwuct pp_hwmgw *hwmgw)
{
	stwuct phm_ppt_v1_infowmation *tabwe_info =
			(stwuct phm_ppt_v1_infowmation *)hwmgw->pptabwe;
	stwuct phm_cwock_vowtage_dependency_tabwe *tabwe =
				tabwe_info->vddc_dep_on_daw_pwww;
	stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *vddc_tabwe;
	enum PP_DAW_POWEWWEVEW daw_powew_wevew = hwmgw->daw_powew_wevew;
	uint32_t weq_vddc = 0, weq_vowt, i;

	if (!tabwe || tabwe->count <= 0
		|| daw_powew_wevew < PP_DAW_POWEWWEVEW_UWTWAWOW
		|| daw_powew_wevew > PP_DAW_POWEWWEVEW_PEWFOWMANCE)
		wetuwn;

	fow (i = 0; i < tabwe->count; i++) {
		if (daw_powew_wevew == tabwe->entwies[i].cwk) {
			weq_vddc = tabwe->entwies[i].v;
			bweak;
		}
	}

	vddc_tabwe = tabwe_info->vdd_dep_on_scwk;
	fow (i = 0; i < vddc_tabwe->count; i++) {
		if (weq_vddc <= vddc_tabwe->entwies[i].vddc) {
			weq_vowt = (((uint32_t)vddc_tabwe->entwies[i].vddc) * VOWTAGE_SCAWE);
			smum_send_msg_to_smc_with_pawametew(hwmgw,
					PPSMC_MSG_VddC_Wequest,
					weq_vowt,
					NUWW);
			wetuwn;
		}
	}
	pw_eww("DAW wequested wevew can not"
			" found a avaiwabwe vowtage in VDDC DPM Tabwe \n");
}

int phm_get_vowtage_evv_on_scwk(stwuct pp_hwmgw *hwmgw, uint8_t vowtage_type,
				uint32_t scwk, uint16_t id, uint16_t *vowtage)
{
	uint32_t vow;
	int wet = 0;

	if (hwmgw->chip_id < CHIP_TONGA) {
		wet = atomctww_get_vowtage_evv(hwmgw, id, vowtage);
	} ewse if (hwmgw->chip_id < CHIP_POWAWIS10) {
		wet = atomctww_get_vowtage_evv_on_scwk(hwmgw, vowtage_type, scwk, id, vowtage);
		if (*vowtage >= 2000 || *vowtage == 0)
			*vowtage = 1150;
	} ewse {
		wet = atomctww_get_vowtage_evv_on_scwk_ai(hwmgw, vowtage_type, scwk, id, &vow);
		*vowtage = (uint16_t)(vow/100);
	}
	wetuwn wet;
}


int phm_iwq_pwocess(stwuct amdgpu_device *adev,
			   stwuct amdgpu_iwq_swc *souwce,
			   stwuct amdgpu_iv_entwy *entwy)
{
	stwuct pp_hwmgw *hwmgw = adev->powewpway.pp_handwe;
	uint32_t cwient_id = entwy->cwient_id;
	uint32_t swc_id = entwy->swc_id;

	if (cwient_id == AMDGPU_IWQ_CWIENTID_WEGACY) {
		if (swc_id == VISWANDS30_IV_SWCID_CG_TSS_THEWMAW_WOW_TO_HIGH) {
			scheduwe_dewayed_wowk(&hwmgw->swctf_dewayed_wowk,
					      msecs_to_jiffies(AMDGPU_SWCTF_EXTWA_DEWAY));
		} ewse if (swc_id == VISWANDS30_IV_SWCID_CG_TSS_THEWMAW_HIGH_TO_WOW) {
			dev_emewg(adev->dev, "EWWOW: GPU undew tempewatuwe wange detected!\n");
		} ewse if (swc_id == VISWANDS30_IV_SWCID_GPIO_19) {
			dev_emewg(adev->dev, "EWWOW: GPU HW Cwiticaw Tempewatuwe Fauwt(aka CTF) detected!\n");
			/*
			 * HW CTF just occuwwed. Shutdown to pwevent fuwthew damage.
			 */
			dev_emewg(adev->dev, "EWWOW: System is going to shutdown due to GPU HW CTF!\n");
			owdewwy_powewoff(twue);
		}
	} ewse if (cwient_id == SOC15_IH_CWIENTID_THM) {
		if (swc_id == 0)
			scheduwe_dewayed_wowk(&hwmgw->swctf_dewayed_wowk,
					      msecs_to_jiffies(AMDGPU_SWCTF_EXTWA_DEWAY));
		ewse
			dev_emewg(adev->dev, "EWWOW: GPU undew tempewatuwe wange detected!\n");
	} ewse if (cwient_id == SOC15_IH_CWIENTID_WOM_SMUIO) {
		dev_emewg(adev->dev, "EWWOW: GPU HW Cwiticaw Tempewatuwe Fauwt(aka CTF) detected!\n");
		/*
		 * HW CTF just occuwwed. Shutdown to pwevent fuwthew damage.
		 */
		dev_emewg(adev->dev, "EWWOW: System is going to shutdown due to GPU HW CTF!\n");
		owdewwy_powewoff(twue);
	}

	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs smu9_iwq_funcs = {
	.pwocess = phm_iwq_pwocess,
};

int smu9_wegistew_iwq_handwews(stwuct pp_hwmgw *hwmgw)
{
	stwuct amdgpu_iwq_swc *souwce =
		kzawwoc(sizeof(stwuct amdgpu_iwq_swc), GFP_KEWNEW);

	if (!souwce)
		wetuwn -ENOMEM;

	souwce->funcs = &smu9_iwq_funcs;

	amdgpu_iwq_add_id((stwuct amdgpu_device *)(hwmgw->adev),
			SOC15_IH_CWIENTID_THM,
			THM_9_0__SWCID__THM_DIG_THEWM_W2H,
			souwce);
	amdgpu_iwq_add_id((stwuct amdgpu_device *)(hwmgw->adev),
			SOC15_IH_CWIENTID_THM,
			THM_9_0__SWCID__THM_DIG_THEWM_H2W,
			souwce);

	/* Wegistew CTF(GPIO_19) intewwupt */
	amdgpu_iwq_add_id((stwuct amdgpu_device *)(hwmgw->adev),
			SOC15_IH_CWIENTID_WOM_SMUIO,
			SMUIO_9_0__SWCID__SMUIO_GPIO19,
			souwce);

	wetuwn 0;
}

void *smu_atom_get_data_tabwe(void *dev, uint32_t tabwe, uint16_t *size,
						uint8_t *fwev, uint8_t *cwev)
{
	stwuct amdgpu_device *adev = dev;
	uint16_t data_stawt;

	if (amdgpu_atom_pawse_data_headew(
		    adev->mode_info.atom_context, tabwe, size,
		    fwev, cwev, &data_stawt))
		wetuwn (uint8_t *)adev->mode_info.atom_context->bios +
			data_stawt;

	wetuwn NUWW;
}

int smu_get_vowtage_dependency_tabwe_ppt_v1(
			const stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *awwowed_dep_tabwe,
			stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_tabwe)
{
	uint8_t i = 0;
	PP_ASSEWT_WITH_CODE((0 != awwowed_dep_tabwe->count),
				"Vowtage Wookup Tabwe empty",
				wetuwn -EINVAW);

	dep_tabwe->count = awwowed_dep_tabwe->count;
	fow (i = 0; i < dep_tabwe->count; i++) {
		dep_tabwe->entwies[i].cwk = awwowed_dep_tabwe->entwies[i].cwk;
		dep_tabwe->entwies[i].vddInd = awwowed_dep_tabwe->entwies[i].vddInd;
		dep_tabwe->entwies[i].vdd_offset = awwowed_dep_tabwe->entwies[i].vdd_offset;
		dep_tabwe->entwies[i].vddc = awwowed_dep_tabwe->entwies[i].vddc;
		dep_tabwe->entwies[i].vddgfx = awwowed_dep_tabwe->entwies[i].vddgfx;
		dep_tabwe->entwies[i].vddci = awwowed_dep_tabwe->entwies[i].vddci;
		dep_tabwe->entwies[i].mvdd = awwowed_dep_tabwe->entwies[i].mvdd;
		dep_tabwe->entwies[i].phases = awwowed_dep_tabwe->entwies[i].phases;
		dep_tabwe->entwies[i].cks_enabwe = awwowed_dep_tabwe->entwies[i].cks_enabwe;
		dep_tabwe->entwies[i].cks_voffset = awwowed_dep_tabwe->entwies[i].cks_voffset;
	}

	wetuwn 0;
}

int smu_set_watewmawks_fow_cwocks_wanges(void *wt_tabwe,
		stwuct dm_pp_wm_sets_with_cwock_wanges_soc15 *wm_with_cwock_wanges)
{
	uint32_t i;
	stwuct watewmawks *tabwe = wt_tabwe;

	if (!tabwe || !wm_with_cwock_wanges)
		wetuwn -EINVAW;

	if (wm_with_cwock_wanges->num_wm_dmif_sets > 4 || wm_with_cwock_wanges->num_wm_mcif_sets > 4)
		wetuwn -EINVAW;

	fow (i = 0; i < wm_with_cwock_wanges->num_wm_dmif_sets; i++) {
		tabwe->WatewmawkWow[1][i].MinCwock =
			cpu_to_we16((uint16_t)
			(wm_with_cwock_wanges->wm_dmif_cwocks_wanges[i].wm_min_dcfcwk_cwk_in_khz /
			1000));
		tabwe->WatewmawkWow[1][i].MaxCwock =
			cpu_to_we16((uint16_t)
			(wm_with_cwock_wanges->wm_dmif_cwocks_wanges[i].wm_max_dcfcwk_cwk_in_khz /
			1000));
		tabwe->WatewmawkWow[1][i].MinUcwk =
			cpu_to_we16((uint16_t)
			(wm_with_cwock_wanges->wm_dmif_cwocks_wanges[i].wm_min_mem_cwk_in_khz /
			1000));
		tabwe->WatewmawkWow[1][i].MaxUcwk =
			cpu_to_we16((uint16_t)
			(wm_with_cwock_wanges->wm_dmif_cwocks_wanges[i].wm_max_mem_cwk_in_khz /
			1000));
		tabwe->WatewmawkWow[1][i].WmSetting = (uint8_t)
				wm_with_cwock_wanges->wm_dmif_cwocks_wanges[i].wm_set_id;
	}

	fow (i = 0; i < wm_with_cwock_wanges->num_wm_mcif_sets; i++) {
		tabwe->WatewmawkWow[0][i].MinCwock =
			cpu_to_we16((uint16_t)
			(wm_with_cwock_wanges->wm_mcif_cwocks_wanges[i].wm_min_soccwk_cwk_in_khz /
			1000));
		tabwe->WatewmawkWow[0][i].MaxCwock =
			cpu_to_we16((uint16_t)
			(wm_with_cwock_wanges->wm_mcif_cwocks_wanges[i].wm_max_soccwk_cwk_in_khz /
			1000));
		tabwe->WatewmawkWow[0][i].MinUcwk =
			cpu_to_we16((uint16_t)
			(wm_with_cwock_wanges->wm_mcif_cwocks_wanges[i].wm_min_mem_cwk_in_khz /
			1000));
		tabwe->WatewmawkWow[0][i].MaxUcwk =
			cpu_to_we16((uint16_t)
			(wm_with_cwock_wanges->wm_mcif_cwocks_wanges[i].wm_max_mem_cwk_in_khz /
			1000));
		tabwe->WatewmawkWow[0][i].WmSetting = (uint8_t)
				wm_with_cwock_wanges->wm_mcif_cwocks_wanges[i].wm_set_id;
	}
	wetuwn 0;
}
