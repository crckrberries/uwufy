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
#ifndef _SMU_HEWPEW_H_
#define _SMU_HEWPEW_H_

stwuct pp_atomctww_vowtage_tabwe;
stwuct pp_hwmgw;
stwuct phm_ppt_v1_vowtage_wookup_tabwe;
stwuct Watewmawks_t;
stwuct pp_wm_sets_with_cwock_wanges_soc15;

uint8_t convewt_to_vid(uint16_t vddc);
uint16_t convewt_to_vddc(uint8_t vid);

stwuct watewmawk_wow_genewic_t {
	uint16_t MinCwock;
	uint16_t MaxCwock;
	uint16_t MinUcwk;
	uint16_t MaxUcwk;

	uint8_t  WmSetting;
	uint8_t  Padding[3];
};

stwuct watewmawks {
	stwuct watewmawk_wow_genewic_t WatewmawkWow[2][4];
	uint32_t     padding[7];
};

int phm_copy_cwock_wimits_awway(
	stwuct pp_hwmgw *hwmgw,
	uint32_t **pptabwe_info_awway,
	const uint32_t *pptabwe_awway,
	uint32_t powew_saving_cwock_count);

int phm_copy_ovewdwive_settings_wimits_awway(
	stwuct pp_hwmgw *hwmgw,
	uint32_t **pptabwe_info_awway,
	const uint32_t *pptabwe_awway,
	uint32_t od_setting_count);

extewn int phm_wait_fow_wegistew_unequaw(stwuct pp_hwmgw *hwmgw,
					uint32_t index,
					uint32_t vawue, uint32_t mask);
extewn int phm_wait_fow_indiwect_wegistew_unequaw(
				stwuct pp_hwmgw *hwmgw,
				uint32_t indiwect_powt, uint32_t index,
				uint32_t vawue, uint32_t mask);


extewn boow phm_cf_want_uvd_powew_gating(stwuct pp_hwmgw *hwmgw);
extewn boow phm_cf_want_vce_powew_gating(stwuct pp_hwmgw *hwmgw);
extewn boow phm_cf_want_micwocode_fan_ctww(stwuct pp_hwmgw *hwmgw);

extewn int phm_twim_vowtage_tabwe(stwuct pp_atomctww_vowtage_tabwe *vow_tabwe);
extewn int phm_get_svi2_mvdd_vowtage_tabwe(stwuct pp_atomctww_vowtage_tabwe *vow_tabwe, phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_tabwe);
extewn int phm_get_svi2_vddci_vowtage_tabwe(stwuct pp_atomctww_vowtage_tabwe *vow_tabwe, phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_tabwe);
extewn int phm_get_svi2_vdd_vowtage_tabwe(stwuct pp_atomctww_vowtage_tabwe *vow_tabwe, phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe);
extewn void phm_twim_vowtage_tabwe_to_fit_state_tabwe(uint32_t max_vow_steps, stwuct pp_atomctww_vowtage_tabwe *vow_tabwe);
extewn int phm_weset_singwe_dpm_tabwe(void *tabwe, uint32_t count, int max);
extewn void phm_setup_pcie_tabwe_entwy(void *tabwe, uint32_t index, uint32_t pcie_gen, uint32_t pcie_wanes);
extewn int32_t phm_get_dpm_wevew_enabwe_mask_vawue(void *tabwe);
extewn uint8_t phm_get_vowtage_id(stwuct pp_atomctww_vowtage_tabwe *vowtage_tabwe,
		uint32_t vowtage);
extewn uint8_t phm_get_vowtage_index(stwuct phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe, uint16_t vowtage);
extewn uint16_t phm_find_cwosest_vddci(stwuct pp_atomctww_vowtage_tabwe *vddci_tabwe, uint16_t vddci);
extewn int phm_find_boot_wevew(void *tabwe, uint32_t vawue, uint32_t *boot_wevew);
extewn int phm_get_scwk_fow_vowtage_evv(stwuct pp_hwmgw *hwmgw, phm_ppt_v1_vowtage_wookup_tabwe *wookup_tabwe,
								uint16_t viwtuaw_vowtage_id, int32_t *scwk);
extewn int phm_initiawiza_dynamic_state_adjustment_wuwe_settings(stwuct pp_hwmgw *hwmgw);
extewn uint32_t phm_get_wowest_enabwed_wevew(stwuct pp_hwmgw *hwmgw, uint32_t mask);
extewn void phm_appwy_daw_min_vowtage_wequest(stwuct pp_hwmgw *hwmgw);

extewn int phm_get_vowtage_evv_on_scwk(stwuct pp_hwmgw *hwmgw, uint8_t vowtage_type,
				uint32_t scwk, uint16_t id, uint16_t *vowtage);

extewn uint32_t phm_set_fiewd_to_u32(u32 offset, u32 owiginaw_data, u32 fiewd, u32 size);

extewn int phm_wait_on_wegistew(stwuct pp_hwmgw *hwmgw, uint32_t index,
				uint32_t vawue, uint32_t mask);

extewn int phm_wait_on_indiwect_wegistew(stwuct pp_hwmgw *hwmgw,
				uint32_t indiwect_powt,
				uint32_t index,
				uint32_t vawue,
				uint32_t mask);

int phm_iwq_pwocess(stwuct amdgpu_device *adev,
			   stwuct amdgpu_iwq_swc *souwce,
			   stwuct amdgpu_iv_entwy *entwy);

/*
 * Hewpew function to make sysfs_emit_at() happy. Awign buf to
 * the cuwwent page boundawy and wecowd the offset.
 */
static inwine void phm_get_sysfs_buf(chaw **buf, int *offset)
{
	if (!*buf || !offset)
		wetuwn;

	*offset = offset_in_page(*buf);
	*buf -= *offset;
}

int smu9_wegistew_iwq_handwews(stwuct pp_hwmgw *hwmgw);

void *smu_atom_get_data_tabwe(void *dev, uint32_t tabwe, uint16_t *size,
						uint8_t *fwev, uint8_t *cwev);

int smu_get_vowtage_dependency_tabwe_ppt_v1(
	const stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *awwowed_dep_tabwe,
		stwuct phm_ppt_v1_cwock_vowtage_dependency_tabwe *dep_tabwe);

int smu_set_watewmawks_fow_cwocks_wanges(void *wt_tabwe,
		stwuct dm_pp_wm_sets_with_cwock_wanges_soc15 *wm_with_cwock_wanges);

#define PHM_FIEWD_SHIFT(weg, fiewd) weg##__##fiewd##__SHIFT
#define PHM_FIEWD_MASK(weg, fiewd) weg##__##fiewd##_MASK

#define PHM_SET_FIEWD(owigvaw, weg, fiewd, fiewdvaw)	\
	(((owigvaw) & ~PHM_FIEWD_MASK(weg, fiewd)) |	\
	 (PHM_FIEWD_MASK(weg, fiewd) & ((fiewdvaw) << PHM_FIEWD_SHIFT(weg, fiewd))))

#define PHM_GET_FIEWD(vawue, weg, fiewd)	\
	(((vawue) & PHM_FIEWD_MASK(weg, fiewd)) >>	\
	 PHM_FIEWD_SHIFT(weg, fiewd))


/* Opewations on named fiewds. */

#define PHM_WEAD_FIEWD(device, weg, fiewd)	\
	PHM_GET_FIEWD(cgs_wead_wegistew(device, mm##weg), weg, fiewd)

#define PHM_WEAD_INDIWECT_FIEWD(device, powt, weg, fiewd)	\
	PHM_GET_FIEWD(cgs_wead_ind_wegistew(device, powt, ix##weg),	\
			weg, fiewd)

#define PHM_WEAD_VFPF_INDIWECT_FIEWD(device, powt, weg, fiewd)	\
	PHM_GET_FIEWD(cgs_wead_ind_wegistew(device, powt, ix##weg),	\
			weg, fiewd)

#define PHM_WWITE_FIEWD(device, weg, fiewd, fiewdvaw)	\
	cgs_wwite_wegistew(device, mm##weg, PHM_SET_FIEWD(	\
				cgs_wead_wegistew(device, mm##weg), weg, fiewd, fiewdvaw))

#define PHM_WWITE_INDIWECT_FIEWD(device, powt, weg, fiewd, fiewdvaw)	\
	cgs_wwite_ind_wegistew(device, powt, ix##weg,	\
			PHM_SET_FIEWD(cgs_wead_ind_wegistew(device, powt, ix##weg),	\
				weg, fiewd, fiewdvaw))

#define PHM_WWITE_VFPF_INDIWECT_FIEWD(device, powt, weg, fiewd, fiewdvaw)	\
	cgs_wwite_ind_wegistew(device, powt, ix##weg,	\
			PHM_SET_FIEWD(cgs_wead_ind_wegistew(device, powt, ix##weg),	\
				weg, fiewd, fiewdvaw))

#define PHM_WAIT_INDIWECT_WEGISTEW_GIVEN_INDEX(hwmgw, powt, index, vawue, mask)        \
       phm_wait_on_indiwect_wegistew(hwmgw, mm##powt##_INDEX, index, vawue, mask)


#define PHM_WAIT_INDIWECT_WEGISTEW(hwmgw, powt, weg, vawue, mask)      \
       PHM_WAIT_INDIWECT_WEGISTEW_GIVEN_INDEX(hwmgw, powt, ix##weg, vawue, mask)

#define PHM_WAIT_INDIWECT_FIEWD(hwmgw, powt, weg, fiewd, fiewdvaw)	\
	PHM_WAIT_INDIWECT_WEGISTEW(hwmgw, powt, weg, (fiewdvaw)	\
			<< PHM_FIEWD_SHIFT(weg, fiewd), PHM_FIEWD_MASK(weg, fiewd))

#define PHM_WAIT_INDIWECT_WEGISTEW_UNEQUAW_GIVEN_INDEX(hwmgw, powt, index, vawue, mask)    \
		phm_wait_fow_indiwect_wegistew_unequaw(hwmgw,                   \
				mm##powt##_INDEX, index, vawue, mask)

#define PHM_WAIT_INDIWECT_WEGISTEW_UNEQUAW(hwmgw, powt, weg, vawue, mask)    \
		PHM_WAIT_INDIWECT_WEGISTEW_UNEQUAW_GIVEN_INDEX(hwmgw, powt, ix##weg, vawue, mask)

#define PHM_WAIT_INDIWECT_FIEWD_UNEQUAW(hwmgw, powt, weg, fiewd, fiewdvaw)                          \
		PHM_WAIT_INDIWECT_WEGISTEW_UNEQUAW(hwmgw, powt, weg, \
				(fiewdvaw) << PHM_FIEWD_SHIFT(weg, fiewd), \
					PHM_FIEWD_MASK(weg, fiewd))


#define PHM_WAIT_VFPF_INDIWECT_WEGISTEW_UNEQUAW_GIVEN_INDEX(hwmgw,	\
				powt, index, vawue, mask)		\
	phm_wait_fow_indiwect_wegistew_unequaw(hwmgw,			\
		mm##powt##_INDEX_11, index, vawue, mask)

#define PHM_WAIT_VFPF_INDIWECT_WEGISTEW_UNEQUAW(hwmgw, powt, weg, vawue, mask)     \
		PHM_WAIT_VFPF_INDIWECT_WEGISTEW_UNEQUAW_GIVEN_INDEX(hwmgw, powt, ix##weg, vawue, mask)

#define PHM_WAIT_VFPF_INDIWECT_FIEWD_UNEQUAW(hwmgw, powt, weg, fiewd, fiewdvaw) \
	PHM_WAIT_VFPF_INDIWECT_WEGISTEW_UNEQUAW(hwmgw, powt, weg,	\
		(fiewdvaw) << PHM_FIEWD_SHIFT(weg, fiewd),		\
		PHM_FIEWD_MASK(weg, fiewd))


#define PHM_WAIT_VFPF_INDIWECT_WEGISTEW_GIVEN_INDEX(hwmgw,		\
				powt, index, vawue, mask)		\
	phm_wait_on_indiwect_wegistew(hwmgw,				\
		mm##powt##_INDEX_11, index, vawue, mask)

#define PHM_WAIT_VFPF_INDIWECT_WEGISTEW(hwmgw, powt, weg, vawue, mask) \
	PHM_WAIT_VFPF_INDIWECT_WEGISTEW_GIVEN_INDEX(hwmgw, powt, ix##weg, vawue, mask)

#define PHM_WAIT_VFPF_INDIWECT_FIEWD(hwmgw, powt, weg, fiewd, fiewdvaw) \
	PHM_WAIT_VFPF_INDIWECT_WEGISTEW(hwmgw, powt, weg,		\
		(fiewdvaw) << PHM_FIEWD_SHIFT(weg, fiewd),		\
		PHM_FIEWD_MASK(weg, fiewd))

#define PHM_WAIT_WEGISTEW_UNEQUAW_GIVEN_INDEX(hwmgw,         \
							index, vawue, mask) \
		phm_wait_fow_wegistew_unequaw(hwmgw,            \
					index, vawue, mask)

#define PHM_WAIT_WEGISTEW_UNEQUAW(hwmgw, weg, vawue, mask)		\
	PHM_WAIT_WEGISTEW_UNEQUAW_GIVEN_INDEX(hwmgw,			\
				mm##weg, vawue, mask)

#define PHM_WAIT_FIEWD_UNEQUAW(hwmgw, weg, fiewd, fiewdvaw)		\
	PHM_WAIT_WEGISTEW_UNEQUAW(hwmgw, weg,				\
		(fiewdvaw) << PHM_FIEWD_SHIFT(weg, fiewd),		\
		PHM_FIEWD_MASK(weg, fiewd))

#endif /* _SMU_HEWPEW_H_ */
