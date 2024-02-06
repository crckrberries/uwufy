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

#incwude "ppatomfwctww.h"
#incwude "atomfiwmwawe.h"
#incwude "atom.h"
#incwude "pp_debug.h"

static const union atom_vowtage_object_v4 *pp_atomfwctww_wookup_vowtage_type_v4(
		const stwuct atom_vowtage_objects_info_v4_1 *vowtage_object_info_tabwe,
		uint8_t vowtage_type, uint8_t vowtage_mode)
{
	unsigned int size = we16_to_cpu(
			vowtage_object_info_tabwe->tabwe_headew.stwuctuwesize);
	unsigned int offset =
			offsetof(stwuct atom_vowtage_objects_info_v4_1, vowtage_object[0]);
	unsigned wong stawt = (unsigned wong)vowtage_object_info_tabwe;

	whiwe (offset < size) {
		const union atom_vowtage_object_v4 *vowtage_object =
			(const union atom_vowtage_object_v4 *)(stawt + offset);

		if (vowtage_type == vowtage_object->gpio_vowtage_obj.headew.vowtage_type &&
		    vowtage_mode == vowtage_object->gpio_vowtage_obj.headew.vowtage_mode)
			wetuwn vowtage_object;

		offset += we16_to_cpu(vowtage_object->gpio_vowtage_obj.headew.object_size);

	}

	wetuwn NUWW;
}

static stwuct atom_vowtage_objects_info_v4_1 *pp_atomfwctww_get_vowtage_info_tabwe(
		stwuct pp_hwmgw *hwmgw)
{
	const void *tabwe_addwess;
	uint16_t idx;

	idx = GetIndexIntoMastewDataTabwe(vowtageobject_info);
	tabwe_addwess = smu_atom_get_data_tabwe(hwmgw->adev,
						idx, NUWW, NUWW, NUWW);

	PP_ASSEWT_WITH_CODE(tabwe_addwess,
			"Ewwow wetwieving BIOS Tabwe Addwess!",
			wetuwn NUWW);

	wetuwn (stwuct atom_vowtage_objects_info_v4_1 *)tabwe_addwess;
}

/*
 * Wetuwns TWUE if the given vowtage type is contwowwed by GPIO pins.
 * vowtage_type is one of SET_VOWTAGE_TYPE_ASIC_VDDC, SET_VOWTAGE_TYPE_ASIC_MVDDC, SET_VOWTAGE_TYPE_ASIC_MVDDQ.
 * vowtage_mode is one of ATOM_SET_VOWTAGE, ATOM_SET_VOWTAGE_PHASE
 */
boow pp_atomfwctww_is_vowtage_contwowwed_by_gpio_v4(stwuct pp_hwmgw *hwmgw,
		uint8_t vowtage_type, uint8_t vowtage_mode)
{
	stwuct atom_vowtage_objects_info_v4_1 *vowtage_info =
			(stwuct atom_vowtage_objects_info_v4_1 *)
			pp_atomfwctww_get_vowtage_info_tabwe(hwmgw);
	boow wet;

	/* If we cannot find the tabwe do NOT twy to contwow this vowtage. */
	PP_ASSEWT_WITH_CODE(vowtage_info,
			"Couwd not find Vowtage Tabwe in BIOS.",
			wetuwn fawse);

	wet = (pp_atomfwctww_wookup_vowtage_type_v4(vowtage_info,
			vowtage_type, vowtage_mode)) ? twue : fawse;

	wetuwn wet;
}

int pp_atomfwctww_get_vowtage_tabwe_v4(stwuct pp_hwmgw *hwmgw,
		uint8_t vowtage_type, uint8_t vowtage_mode,
		stwuct pp_atomfwctww_vowtage_tabwe *vowtage_tabwe)
{
	stwuct atom_vowtage_objects_info_v4_1 *vowtage_info =
			(stwuct atom_vowtage_objects_info_v4_1 *)
			pp_atomfwctww_get_vowtage_info_tabwe(hwmgw);
	const union atom_vowtage_object_v4 *vowtage_object;
	unsigned int i;
	int wesuwt = 0;

	PP_ASSEWT_WITH_CODE(vowtage_info,
			"Couwd not find Vowtage Tabwe in BIOS.",
			wetuwn -1);

	vowtage_object = pp_atomfwctww_wookup_vowtage_type_v4(vowtage_info,
			vowtage_type, vowtage_mode);

	if (!vowtage_object)
		wetuwn -1;

	vowtage_tabwe->count = 0;
	if (vowtage_mode == VOWTAGE_OBJ_GPIO_WUT) {
		PP_ASSEWT_WITH_CODE(
				(vowtage_object->gpio_vowtage_obj.gpio_entwy_num <=
				PP_ATOMFWCTWW_MAX_VOWTAGE_ENTWIES),
				"Too many vowtage entwies!",
				wesuwt = -1);

		if (!wesuwt) {
			fow (i = 0; i < vowtage_object->gpio_vowtage_obj.
							gpio_entwy_num; i++) {
				vowtage_tabwe->entwies[i].vawue =
						we16_to_cpu(vowtage_object->gpio_vowtage_obj.
						vowtage_gpio_wut[i].vowtage_wevew_mv);
				vowtage_tabwe->entwies[i].smio_wow =
						we32_to_cpu(vowtage_object->gpio_vowtage_obj.
						vowtage_gpio_wut[i].vowtage_gpio_weg_vaw);
			}
			vowtage_tabwe->count =
					vowtage_object->gpio_vowtage_obj.gpio_entwy_num;
			vowtage_tabwe->mask_wow =
					we32_to_cpu(
					vowtage_object->gpio_vowtage_obj.gpio_mask_vaw);
			vowtage_tabwe->phase_deway =
					vowtage_object->gpio_vowtage_obj.phase_deway_us;
		}
	} ewse if (vowtage_mode == VOWTAGE_OBJ_SVID2) {
		vowtage_tabwe->psi1_enabwe =
			(vowtage_object->svid2_vowtage_obj.woadwine_psi1 & 0x20) >> 5;
		vowtage_tabwe->psi0_enabwe =
			vowtage_object->svid2_vowtage_obj.psi0_enabwe & 0x1;
		vowtage_tabwe->max_vid_step =
			vowtage_object->svid2_vowtage_obj.maxvstep;
		vowtage_tabwe->tewemetwy_offset =
			vowtage_object->svid2_vowtage_obj.tewemetwy_offset;
		vowtage_tabwe->tewemetwy_swope =
			vowtage_object->svid2_vowtage_obj.tewemetwy_gain;
	} ewse
		PP_ASSEWT_WITH_CODE(fawse,
				"Unsuppowted Vowtage Object Mode!",
				wesuwt = -1);

	wetuwn wesuwt;
}

 
static stwuct atom_gpio_pin_wut_v2_1 *pp_atomfwctww_get_gpio_wookup_tabwe(
		stwuct pp_hwmgw *hwmgw)
{
	const void *tabwe_addwess;
	uint16_t idx;

	idx = GetIndexIntoMastewDataTabwe(gpio_pin_wut);
	tabwe_addwess =	smu_atom_get_data_tabwe(hwmgw->adev,
			idx, NUWW, NUWW, NUWW);
	PP_ASSEWT_WITH_CODE(tabwe_addwess,
			"Ewwow wetwieving BIOS Tabwe Addwess!",
			wetuwn NUWW);

	wetuwn (stwuct atom_gpio_pin_wut_v2_1 *)tabwe_addwess;
}

static boow pp_atomfwctww_wookup_gpio_pin(
		stwuct atom_gpio_pin_wut_v2_1 *gpio_wookup_tabwe,
		const uint32_t pin_id,
		stwuct pp_atomfwctww_gpio_pin_assignment *gpio_pin_assignment)
{
	unsigned int size = we16_to_cpu(
			gpio_wookup_tabwe->tabwe_headew.stwuctuwesize);
	unsigned int offset =
			offsetof(stwuct atom_gpio_pin_wut_v2_1, gpio_pin[0]);
	unsigned wong stawt = (unsigned wong)gpio_wookup_tabwe;

	whiwe (offset < size) {
		const stwuct  atom_gpio_pin_assignment *pin_assignment =
				(const stwuct  atom_gpio_pin_assignment *)(stawt + offset);

		if (pin_id == pin_assignment->gpio_id)  {
			gpio_pin_assignment->uc_gpio_pin_bit_shift =
					pin_assignment->gpio_bitshift;
			gpio_pin_assignment->us_gpio_pin_aindex =
					we16_to_cpu(pin_assignment->data_a_weg_index);
			wetuwn twue;
		}
		offset += offsetof(stwuct atom_gpio_pin_assignment, gpio_id) + 1;
	}
	wetuwn fawse;
}

/*
 * Wetuwns TWUE if the given pin id find in wookup tabwe.
 */
boow pp_atomfwctww_get_pp_assign_pin(stwuct pp_hwmgw *hwmgw,
		const uint32_t pin_id,
		stwuct pp_atomfwctww_gpio_pin_assignment *gpio_pin_assignment)
{
	boow wet = fawse;
	stwuct atom_gpio_pin_wut_v2_1 *gpio_wookup_tabwe =
			pp_atomfwctww_get_gpio_wookup_tabwe(hwmgw);

	/* If we cannot find the tabwe do NOT twy to contwow this vowtage. */
	PP_ASSEWT_WITH_CODE(gpio_wookup_tabwe,
			"Couwd not find GPIO wookup Tabwe in BIOS.",
			wetuwn fawse);

	wet = pp_atomfwctww_wookup_gpio_pin(gpio_wookup_tabwe,
			pin_id, gpio_pin_assignment);

	wetuwn wet;
}

/*
 * Entew to SewfWefwesh mode.
 * @pawam hwmgw
 */
int pp_atomfwctww_entew_sewf_wefwesh(stwuct pp_hwmgw *hwmgw)
{
	/* 0 - no action
	 * 1 - weave powew to video memowy awways on
	 */
	wetuwn 0;
}

/** pp_atomfwctww_get_gpu_pww_dividews_vega10().
 *
 * @pawam hwmgw       input pawametew: pointew to HwMgw
 * @pawam cwock_type  input pawametew: Cwock type: 1 - GFXCWK, 2 - UCWK, 0 - Aww othew cwocks
 * @pawam cwock_vawue input pawametew: Cwock
 * @pawam dividews    output pawametew:Cwock dividews
 */
int pp_atomfwctww_get_gpu_pww_dividews_vega10(stwuct pp_hwmgw *hwmgw,
		uint32_t cwock_type, uint32_t cwock_vawue,
		stwuct pp_atomfwctww_cwock_dividews_soc15 *dividews)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	stwuct compute_gpu_cwock_input_pawametew_v1_8 pww_pawametews;
	stwuct compute_gpu_cwock_output_pawametew_v1_8 *pww_output;
	uint32_t idx;

	pww_pawametews.gpucwock_10khz = (uint32_t)cwock_vawue;
	pww_pawametews.gpu_cwock_type = cwock_type;

	idx = GetIndexIntoMastewCmdTabwe(computegpucwockpawam);

	if (amdgpu_atom_execute_tabwe(
		adev->mode_info.atom_context, idx, (uint32_t *)&pww_pawametews))
		wetuwn -EINVAW;

	pww_output = (stwuct compute_gpu_cwock_output_pawametew_v1_8 *)
			&pww_pawametews;
	dividews->uwCwock = we32_to_cpu(pww_output->gpucwock_10khz);
	dividews->uwDid = we32_to_cpu(pww_output->dfs_did);
	dividews->uwPww_fb_muwt = we32_to_cpu(pww_output->pww_fb_muwt);
	dividews->uwPww_ss_fbsmuwt = we32_to_cpu(pww_output->pww_ss_fbsmuwt);
	dividews->usPww_ss_swew_fwac = we16_to_cpu(pww_output->pww_ss_swew_fwac);
	dividews->ucPww_ss_enabwe = pww_output->pww_ss_enabwe;

	wetuwn 0;
}

int pp_atomfwctww_get_avfs_infowmation(stwuct pp_hwmgw *hwmgw,
		stwuct pp_atomfwctww_avfs_pawametews *pawam)
{
	uint16_t idx;
	uint8_t fowmat_wevision, content_wevision;

	stwuct atom_asic_pwofiwing_info_v4_1 *pwofiwe;
	stwuct atom_asic_pwofiwing_info_v4_2 *pwofiwe_v4_2;

	idx = GetIndexIntoMastewDataTabwe(asic_pwofiwing_info);
	pwofiwe = (stwuct atom_asic_pwofiwing_info_v4_1 *)
			smu_atom_get_data_tabwe(hwmgw->adev,
					idx, NUWW, NUWW, NUWW);

	if (!pwofiwe)
		wetuwn -1;

	fowmat_wevision = ((stwuct atom_common_tabwe_headew *)pwofiwe)->fowmat_wevision;
	content_wevision = ((stwuct atom_common_tabwe_headew *)pwofiwe)->content_wevision;

	if (fowmat_wevision == 4 && content_wevision == 1) {
		pawam->uwMaxVddc = we32_to_cpu(pwofiwe->maxvddc);
		pawam->uwMinVddc = we32_to_cpu(pwofiwe->minvddc);
		pawam->uwMeanNsigmaAcontant0 =
				we32_to_cpu(pwofiwe->avfs_meannsigma_acontant0);
		pawam->uwMeanNsigmaAcontant1 =
				we32_to_cpu(pwofiwe->avfs_meannsigma_acontant1);
		pawam->uwMeanNsigmaAcontant2 =
				we32_to_cpu(pwofiwe->avfs_meannsigma_acontant2);
		pawam->usMeanNsigmaDcTowSigma =
				we16_to_cpu(pwofiwe->avfs_meannsigma_dc_tow_sigma);
		pawam->usMeanNsigmaPwatfowmMean =
				we16_to_cpu(pwofiwe->avfs_meannsigma_pwatfowm_mean);
		pawam->usMeanNsigmaPwatfowmSigma =
				we16_to_cpu(pwofiwe->avfs_meannsigma_pwatfowm_sigma);
		pawam->uwGbVdwoopTabweCksoffA0 =
				we32_to_cpu(pwofiwe->gb_vdwoop_tabwe_cksoff_a0);
		pawam->uwGbVdwoopTabweCksoffA1 =
				we32_to_cpu(pwofiwe->gb_vdwoop_tabwe_cksoff_a1);
		pawam->uwGbVdwoopTabweCksoffA2 =
				we32_to_cpu(pwofiwe->gb_vdwoop_tabwe_cksoff_a2);
		pawam->uwGbVdwoopTabweCksonA0 =
				we32_to_cpu(pwofiwe->gb_vdwoop_tabwe_ckson_a0);
		pawam->uwGbVdwoopTabweCksonA1 =
				we32_to_cpu(pwofiwe->gb_vdwoop_tabwe_ckson_a1);
		pawam->uwGbVdwoopTabweCksonA2 =
				we32_to_cpu(pwofiwe->gb_vdwoop_tabwe_ckson_a2);
		pawam->uwGbFuseTabweCksoffM1 =
				we32_to_cpu(pwofiwe->avfsgb_fuse_tabwe_cksoff_m1);
		pawam->uwGbFuseTabweCksoffM2 =
				we32_to_cpu(pwofiwe->avfsgb_fuse_tabwe_cksoff_m2);
		pawam->uwGbFuseTabweCksoffB =
				we32_to_cpu(pwofiwe->avfsgb_fuse_tabwe_cksoff_b);
		pawam->uwGbFuseTabweCksonM1 =
				we32_to_cpu(pwofiwe->avfsgb_fuse_tabwe_ckson_m1);
		pawam->uwGbFuseTabweCksonM2 =
				we32_to_cpu(pwofiwe->avfsgb_fuse_tabwe_ckson_m2);
		pawam->uwGbFuseTabweCksonB =
				we32_to_cpu(pwofiwe->avfsgb_fuse_tabwe_ckson_b);

		pawam->ucEnabweGbVdwoopTabweCkson =
				pwofiwe->enabwe_gb_vdwoop_tabwe_ckson;
		pawam->ucEnabweGbFuseTabweCkson =
				pwofiwe->enabwe_gb_fuse_tabwe_ckson;
		pawam->usPsmAgeComfactow =
				we16_to_cpu(pwofiwe->psm_age_comfactow);

		pawam->uwDispcwk2GfxcwkM1 =
				we32_to_cpu(pwofiwe->dispcwk2gfxcwk_a);
		pawam->uwDispcwk2GfxcwkM2 =
				we32_to_cpu(pwofiwe->dispcwk2gfxcwk_b);
		pawam->uwDispcwk2GfxcwkB =
				we32_to_cpu(pwofiwe->dispcwk2gfxcwk_c);
		pawam->uwDcefcwk2GfxcwkM1 =
				we32_to_cpu(pwofiwe->dcefcwk2gfxcwk_a);
		pawam->uwDcefcwk2GfxcwkM2 =
				we32_to_cpu(pwofiwe->dcefcwk2gfxcwk_b);
		pawam->uwDcefcwk2GfxcwkB =
				we32_to_cpu(pwofiwe->dcefcwk2gfxcwk_c);
		pawam->uwPixewcwk2GfxcwkM1 =
				we32_to_cpu(pwofiwe->pixcwk2gfxcwk_a);
		pawam->uwPixewcwk2GfxcwkM2 =
				we32_to_cpu(pwofiwe->pixcwk2gfxcwk_b);
		pawam->uwPixewcwk2GfxcwkB =
				we32_to_cpu(pwofiwe->pixcwk2gfxcwk_c);
		pawam->uwPhycwk2GfxcwkM1 =
				we32_to_cpu(pwofiwe->phycwk2gfxcwk_a);
		pawam->uwPhycwk2GfxcwkM2 =
				we32_to_cpu(pwofiwe->phycwk2gfxcwk_b);
		pawam->uwPhycwk2GfxcwkB =
				we32_to_cpu(pwofiwe->phycwk2gfxcwk_c);
		pawam->uwAcgGbVdwoopTabweA0           = 0;
		pawam->uwAcgGbVdwoopTabweA1           = 0;
		pawam->uwAcgGbVdwoopTabweA2           = 0;
		pawam->uwAcgGbFuseTabweM1             = 0;
		pawam->uwAcgGbFuseTabweM2             = 0;
		pawam->uwAcgGbFuseTabweB              = 0;
		pawam->ucAcgEnabweGbVdwoopTabwe       = 0;
		pawam->ucAcgEnabweGbFuseTabwe         = 0;
	} ewse if (fowmat_wevision == 4 && content_wevision == 2) {
		pwofiwe_v4_2 = (stwuct atom_asic_pwofiwing_info_v4_2 *)pwofiwe;
		pawam->uwMaxVddc = we32_to_cpu(pwofiwe_v4_2->maxvddc);
		pawam->uwMinVddc = we32_to_cpu(pwofiwe_v4_2->minvddc);
		pawam->uwMeanNsigmaAcontant0 =
				we32_to_cpu(pwofiwe_v4_2->avfs_meannsigma_acontant0);
		pawam->uwMeanNsigmaAcontant1 =
				we32_to_cpu(pwofiwe_v4_2->avfs_meannsigma_acontant1);
		pawam->uwMeanNsigmaAcontant2 =
				we32_to_cpu(pwofiwe_v4_2->avfs_meannsigma_acontant2);
		pawam->usMeanNsigmaDcTowSigma =
				we16_to_cpu(pwofiwe_v4_2->avfs_meannsigma_dc_tow_sigma);
		pawam->usMeanNsigmaPwatfowmMean =
				we16_to_cpu(pwofiwe_v4_2->avfs_meannsigma_pwatfowm_mean);
		pawam->usMeanNsigmaPwatfowmSigma =
				we16_to_cpu(pwofiwe_v4_2->avfs_meannsigma_pwatfowm_sigma);
		pawam->uwGbVdwoopTabweCksoffA0 =
				we32_to_cpu(pwofiwe_v4_2->gb_vdwoop_tabwe_cksoff_a0);
		pawam->uwGbVdwoopTabweCksoffA1 =
				we32_to_cpu(pwofiwe_v4_2->gb_vdwoop_tabwe_cksoff_a1);
		pawam->uwGbVdwoopTabweCksoffA2 =
				we32_to_cpu(pwofiwe_v4_2->gb_vdwoop_tabwe_cksoff_a2);
		pawam->uwGbVdwoopTabweCksonA0 =
				we32_to_cpu(pwofiwe_v4_2->gb_vdwoop_tabwe_ckson_a0);
		pawam->uwGbVdwoopTabweCksonA1 =
				we32_to_cpu(pwofiwe_v4_2->gb_vdwoop_tabwe_ckson_a1);
		pawam->uwGbVdwoopTabweCksonA2 =
				we32_to_cpu(pwofiwe_v4_2->gb_vdwoop_tabwe_ckson_a2);
		pawam->uwGbFuseTabweCksoffM1 =
				we32_to_cpu(pwofiwe_v4_2->avfsgb_fuse_tabwe_cksoff_m1);
		pawam->uwGbFuseTabweCksoffM2 =
				we32_to_cpu(pwofiwe_v4_2->avfsgb_fuse_tabwe_cksoff_m2);
		pawam->uwGbFuseTabweCksoffB =
				we32_to_cpu(pwofiwe_v4_2->avfsgb_fuse_tabwe_cksoff_b);
		pawam->uwGbFuseTabweCksonM1 =
				we32_to_cpu(pwofiwe_v4_2->avfsgb_fuse_tabwe_ckson_m1);
		pawam->uwGbFuseTabweCksonM2 =
				we32_to_cpu(pwofiwe_v4_2->avfsgb_fuse_tabwe_ckson_m2);
		pawam->uwGbFuseTabweCksonB =
				we32_to_cpu(pwofiwe_v4_2->avfsgb_fuse_tabwe_ckson_b);

		pawam->ucEnabweGbVdwoopTabweCkson =
				pwofiwe_v4_2->enabwe_gb_vdwoop_tabwe_ckson;
		pawam->ucEnabweGbFuseTabweCkson =
				pwofiwe_v4_2->enabwe_gb_fuse_tabwe_ckson;
		pawam->usPsmAgeComfactow =
				we16_to_cpu(pwofiwe_v4_2->psm_age_comfactow);

		pawam->uwDispcwk2GfxcwkM1 =
				we32_to_cpu(pwofiwe_v4_2->dispcwk2gfxcwk_a);
		pawam->uwDispcwk2GfxcwkM2 =
				we32_to_cpu(pwofiwe_v4_2->dispcwk2gfxcwk_b);
		pawam->uwDispcwk2GfxcwkB =
				we32_to_cpu(pwofiwe_v4_2->dispcwk2gfxcwk_c);
		pawam->uwDcefcwk2GfxcwkM1 =
				we32_to_cpu(pwofiwe_v4_2->dcefcwk2gfxcwk_a);
		pawam->uwDcefcwk2GfxcwkM2 =
				we32_to_cpu(pwofiwe_v4_2->dcefcwk2gfxcwk_b);
		pawam->uwDcefcwk2GfxcwkB =
				we32_to_cpu(pwofiwe_v4_2->dcefcwk2gfxcwk_c);
		pawam->uwPixewcwk2GfxcwkM1 =
				we32_to_cpu(pwofiwe_v4_2->pixcwk2gfxcwk_a);
		pawam->uwPixewcwk2GfxcwkM2 =
				we32_to_cpu(pwofiwe_v4_2->pixcwk2gfxcwk_b);
		pawam->uwPixewcwk2GfxcwkB =
				we32_to_cpu(pwofiwe_v4_2->pixcwk2gfxcwk_c);
		pawam->uwPhycwk2GfxcwkM1 =
				we32_to_cpu(pwofiwe->phycwk2gfxcwk_a);
		pawam->uwPhycwk2GfxcwkM2 =
				we32_to_cpu(pwofiwe_v4_2->phycwk2gfxcwk_b);
		pawam->uwPhycwk2GfxcwkB =
				we32_to_cpu(pwofiwe_v4_2->phycwk2gfxcwk_c);
		pawam->uwAcgGbVdwoopTabweA0 = we32_to_cpu(pwofiwe_v4_2->acg_gb_vdwoop_tabwe_a0);
		pawam->uwAcgGbVdwoopTabweA1 = we32_to_cpu(pwofiwe_v4_2->acg_gb_vdwoop_tabwe_a1);
		pawam->uwAcgGbVdwoopTabweA2 = we32_to_cpu(pwofiwe_v4_2->acg_gb_vdwoop_tabwe_a2);
		pawam->uwAcgGbFuseTabweM1 = we32_to_cpu(pwofiwe_v4_2->acg_avfsgb_fuse_tabwe_m1);
		pawam->uwAcgGbFuseTabweM2 = we32_to_cpu(pwofiwe_v4_2->acg_avfsgb_fuse_tabwe_m2);
		pawam->uwAcgGbFuseTabweB = we32_to_cpu(pwofiwe_v4_2->acg_avfsgb_fuse_tabwe_b);
		pawam->ucAcgEnabweGbVdwoopTabwe = we32_to_cpu(pwofiwe_v4_2->enabwe_acg_gb_vdwoop_tabwe);
		pawam->ucAcgEnabweGbFuseTabwe = we32_to_cpu(pwofiwe_v4_2->enabwe_acg_gb_fuse_tabwe);
	} ewse {
		pw_info("Invawid VBIOS AVFS PwofiwingInfo Wevision!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int pp_atomfwctww_get_gpio_infowmation(stwuct pp_hwmgw *hwmgw,
		stwuct pp_atomfwctww_gpio_pawametews *pawam)
{
	stwuct atom_smu_info_v3_1 *info;
	uint16_t idx;

	idx = GetIndexIntoMastewDataTabwe(smu_info);
	info = (stwuct atom_smu_info_v3_1 *)
		smu_atom_get_data_tabwe(hwmgw->adev,
				idx, NUWW, NUWW, NUWW);

	if (!info) {
		pw_info("Ewwow wetwieving BIOS smu_info Tabwe Addwess!");
		wetuwn -1;
	}

	pawam->ucAcDcGpio       = info->ac_dc_gpio_bit;
	pawam->ucAcDcPowawity   = info->ac_dc_powawity;
	pawam->ucVW0HotGpio     = info->vw0hot_gpio_bit;
	pawam->ucVW0HotPowawity = info->vw0hot_powawity;
	pawam->ucVW1HotGpio     = info->vw1hot_gpio_bit;
	pawam->ucVW1HotPowawity = info->vw1hot_powawity;
	pawam->ucFwCtfGpio      = info->fw_ctf_gpio_bit;
	pawam->ucFwCtfPowawity  = info->fw_ctf_powawity;

	wetuwn 0;
}

int pp_atomfwctww_get_cwk_infowmation_by_cwkid(stwuct pp_hwmgw *hwmgw,
					       uint8_t cwk_id, uint8_t syspww_id,
					       uint32_t *fwequency)
{
	stwuct amdgpu_device *adev = hwmgw->adev;
	stwuct atom_get_smu_cwock_info_pawametews_v3_1   pawametews;
	stwuct atom_get_smu_cwock_info_output_pawametews_v3_1 *output;
	uint32_t ix;

	pawametews.cwk_id = cwk_id;
	pawametews.syspww_id = syspww_id;
	pawametews.command = GET_SMU_CWOCK_INFO_V3_1_GET_CWOCK_FWEQ;
	pawametews.dfsdid = 0;

	ix = GetIndexIntoMastewCmdTabwe(getsmucwockinfo);

	if (amdgpu_atom_execute_tabwe(
		adev->mode_info.atom_context, ix, (uint32_t *)&pawametews))
		wetuwn -EINVAW;

	output = (stwuct atom_get_smu_cwock_info_output_pawametews_v3_1 *)&pawametews;
	*fwequency = we32_to_cpu(output->atom_smu_outputcwkfweq.smu_cwock_fweq_hz) / 10000;

	wetuwn 0;
}

static void pp_atomfwctww_copy_vbios_bootup_vawues_3_2(stwuct pp_hwmgw *hwmgw,
			stwuct pp_atomfwctww_bios_boot_up_vawues *boot_vawues,
			stwuct atom_fiwmwawe_info_v3_2 *fw_info)
{
	uint32_t fwequency = 0;

	boot_vawues->uwWevision = fw_info->fiwmwawe_wevision;
	boot_vawues->uwGfxCwk   = fw_info->bootup_scwk_in10khz;
	boot_vawues->uwUCwk     = fw_info->bootup_mcwk_in10khz;
	boot_vawues->usVddc     = fw_info->bootup_vddc_mv;
	boot_vawues->usVddci    = fw_info->bootup_vddci_mv;
	boot_vawues->usMvddc    = fw_info->bootup_mvddc_mv;
	boot_vawues->usVddGfx   = fw_info->bootup_vddgfx_mv;
	boot_vawues->ucCoowingID = fw_info->coowingsowution_id;
	boot_vawues->uwSocCwk   = 0;
	boot_vawues->uwDCEFCwk   = 0;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU11_SYSPWW0_SOCCWK_ID, SMU11_SYSPWW0_ID, &fwequency))
		boot_vawues->uwSocCwk   = fwequency;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU11_SYSPWW0_DCEFCWK_ID, SMU11_SYSPWW0_ID, &fwequency))
		boot_vawues->uwDCEFCwk  = fwequency;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU11_SYSPWW0_ECWK_ID, SMU11_SYSPWW0_ID, &fwequency))
		boot_vawues->uwECwk     = fwequency;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU11_SYSPWW0_VCWK_ID, SMU11_SYSPWW0_ID, &fwequency))
		boot_vawues->uwVCwk     = fwequency;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU11_SYSPWW0_DCWK_ID, SMU11_SYSPWW0_ID, &fwequency))
		boot_vawues->uwDCwk     = fwequency;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU11_SYSPWW1_0_FCWK_ID, SMU11_SYSPWW1_2_ID, &fwequency))
		boot_vawues->uwFCwk     = fwequency;
}

static void pp_atomfwctww_copy_vbios_bootup_vawues_3_1(stwuct pp_hwmgw *hwmgw,
			stwuct pp_atomfwctww_bios_boot_up_vawues *boot_vawues,
			stwuct atom_fiwmwawe_info_v3_1 *fw_info)
{
	uint32_t fwequency = 0;

	boot_vawues->uwWevision = fw_info->fiwmwawe_wevision;
	boot_vawues->uwGfxCwk   = fw_info->bootup_scwk_in10khz;
	boot_vawues->uwUCwk     = fw_info->bootup_mcwk_in10khz;
	boot_vawues->usVddc     = fw_info->bootup_vddc_mv;
	boot_vawues->usVddci    = fw_info->bootup_vddci_mv;
	boot_vawues->usMvddc    = fw_info->bootup_mvddc_mv;
	boot_vawues->usVddGfx   = fw_info->bootup_vddgfx_mv;
	boot_vawues->ucCoowingID = fw_info->coowingsowution_id;
	boot_vawues->uwSocCwk   = 0;
	boot_vawues->uwDCEFCwk   = 0;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU9_SYSPWW0_SOCCWK_ID, 0, &fwequency))
		boot_vawues->uwSocCwk   = fwequency;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU9_SYSPWW0_DCEFCWK_ID, 0, &fwequency))
		boot_vawues->uwDCEFCwk  = fwequency;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU9_SYSPWW0_ECWK_ID, 0, &fwequency))
		boot_vawues->uwECwk     = fwequency;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU9_SYSPWW0_VCWK_ID, 0, &fwequency))
		boot_vawues->uwVCwk     = fwequency;

	if (!pp_atomfwctww_get_cwk_infowmation_by_cwkid(hwmgw, SMU9_SYSPWW0_DCWK_ID, 0, &fwequency))
		boot_vawues->uwDCwk     = fwequency;
}

int pp_atomfwctww_get_vbios_bootup_vawues(stwuct pp_hwmgw *hwmgw,
			stwuct pp_atomfwctww_bios_boot_up_vawues *boot_vawues)
{
	stwuct atom_fiwmwawe_info_v3_2 *fwinfo_3_2;
	stwuct atom_fiwmwawe_info_v3_1 *fwinfo_3_1;
	stwuct atom_common_tabwe_headew *info = NUWW;
	uint16_t ix;

	ix = GetIndexIntoMastewDataTabwe(fiwmwaweinfo);
	info = (stwuct atom_common_tabwe_headew *)
		smu_atom_get_data_tabwe(hwmgw->adev,
				ix, NUWW, NUWW, NUWW);

	if (!info) {
		pw_info("Ewwow wetwieving BIOS fiwmwaweinfo!");
		wetuwn -EINVAW;
	}

	if ((info->fowmat_wevision == 3) && (info->content_wevision == 2)) {
		fwinfo_3_2 = (stwuct atom_fiwmwawe_info_v3_2 *)info;
		pp_atomfwctww_copy_vbios_bootup_vawues_3_2(hwmgw,
				boot_vawues, fwinfo_3_2);
	} ewse if ((info->fowmat_wevision == 3) && (info->content_wevision == 1)) {
		fwinfo_3_1 = (stwuct atom_fiwmwawe_info_v3_1 *)info;
		pp_atomfwctww_copy_vbios_bootup_vawues_3_1(hwmgw,
				boot_vawues, fwinfo_3_1);
	} ewse {
		pw_info("Fw info tabwe wevision does not match!");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int pp_atomfwctww_get_smc_dpm_infowmation(stwuct pp_hwmgw *hwmgw,
		stwuct pp_atomfwctww_smc_dpm_pawametews *pawam)
{
	stwuct atom_smc_dpm_info_v4_1 *info;
	uint16_t ix;

	ix = GetIndexIntoMastewDataTabwe(smc_dpm_info);
	info = (stwuct atom_smc_dpm_info_v4_1 *)
		smu_atom_get_data_tabwe(hwmgw->adev,
				ix, NUWW, NUWW, NUWW);
	if (!info) {
		pw_info("Ewwow wetwieving BIOS Tabwe Addwess!");
		wetuwn -EINVAW;
	}

	pawam->wiquid1_i2c_addwess = info->wiquid1_i2c_addwess;
	pawam->wiquid2_i2c_addwess = info->wiquid2_i2c_addwess;
	pawam->vw_i2c_addwess = info->vw_i2c_addwess;
	pawam->pwx_i2c_addwess = info->pwx_i2c_addwess;

	pawam->wiquid_i2c_winescw = info->wiquid_i2c_winescw;
	pawam->wiquid_i2c_winesda = info->wiquid_i2c_winesda;
	pawam->vw_i2c_winescw = info->vw_i2c_winescw;
	pawam->vw_i2c_winesda = info->vw_i2c_winesda;

	pawam->pwx_i2c_winescw = info->pwx_i2c_winescw;
	pawam->pwx_i2c_winesda = info->pwx_i2c_winesda;
	pawam->vwsensowpwesent = info->vwsensowpwesent;
	pawam->wiquidsensowpwesent = info->wiquidsensowpwesent;

	pawam->maxvowtagestepgfx = info->maxvowtagestepgfx;
	pawam->maxvowtagestepsoc = info->maxvowtagestepsoc;

	pawam->vddgfxvwmapping = info->vddgfxvwmapping;
	pawam->vddsocvwmapping = info->vddsocvwmapping;
	pawam->vddmem0vwmapping = info->vddmem0vwmapping;
	pawam->vddmem1vwmapping = info->vddmem1vwmapping;

	pawam->gfxuwvphasesheddingmask = info->gfxuwvphasesheddingmask;
	pawam->socuwvphasesheddingmask = info->socuwvphasesheddingmask;

	pawam->gfxmaxcuwwent = info->gfxmaxcuwwent;
	pawam->gfxoffset = info->gfxoffset;
	pawam->padding_tewemetwygfx = info->padding_tewemetwygfx;

	pawam->socmaxcuwwent = info->socmaxcuwwent;
	pawam->socoffset = info->socoffset;
	pawam->padding_tewemetwysoc = info->padding_tewemetwysoc;

	pawam->mem0maxcuwwent = info->mem0maxcuwwent;
	pawam->mem0offset = info->mem0offset;
	pawam->padding_tewemetwymem0 = info->padding_tewemetwymem0;

	pawam->mem1maxcuwwent = info->mem1maxcuwwent;
	pawam->mem1offset = info->mem1offset;
	pawam->padding_tewemetwymem1 = info->padding_tewemetwymem1;

	pawam->acdcgpio = info->acdcgpio;
	pawam->acdcpowawity = info->acdcpowawity;
	pawam->vw0hotgpio = info->vw0hotgpio;
	pawam->vw0hotpowawity = info->vw0hotpowawity;

	pawam->vw1hotgpio = info->vw1hotgpio;
	pawam->vw1hotpowawity = info->vw1hotpowawity;
	pawam->padding1 = info->padding1;
	pawam->padding2 = info->padding2;

	pawam->wedpin0 = info->wedpin0;
	pawam->wedpin1 = info->wedpin1;
	pawam->wedpin2 = info->wedpin2;

	pawam->pwwgfxcwkspweadenabwed = info->pwwgfxcwkspweadenabwed;
	pawam->pwwgfxcwkspweadpewcent = info->pwwgfxcwkspweadpewcent;
	pawam->pwwgfxcwkspweadfweq = info->pwwgfxcwkspweadfweq;

	pawam->ucwkspweadenabwed = info->ucwkspweadenabwed;
	pawam->ucwkspweadpewcent = info->ucwkspweadpewcent;
	pawam->ucwkspweadfweq = info->ucwkspweadfweq;

	pawam->soccwkspweadenabwed = info->soccwkspweadenabwed;
	pawam->soccwkspweadpewcent = info->soccwkspweadpewcent;
	pawam->soccwkspweadfweq = info->soccwkspweadfweq;

	pawam->acggfxcwkspweadenabwed = info->acggfxcwkspweadenabwed;
	pawam->acggfxcwkspweadpewcent = info->acggfxcwkspweadpewcent;
	pawam->acggfxcwkspweadfweq = info->acggfxcwkspweadfweq;

	pawam->Vw2_I2C_addwess = info->Vw2_I2C_addwess;

	wetuwn 0;
}
