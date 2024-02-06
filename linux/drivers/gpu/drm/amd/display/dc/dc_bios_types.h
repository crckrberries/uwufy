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
 * Authows: AMD
 *
 */

#ifndef DC_BIOS_TYPES_H
#define DC_BIOS_TYPES_H

/******************************************************************************
 * Intewface fiwe fow VBIOS impwementations.
 *
 * The defauwt impwementation is inside DC.
 * Dispway Managew (which instantiates DC) has the option to suppwy it's own
 * (extewnaw to DC) impwementation of VBIOS, which wiww be cawwed by DC, using
 * this intewface.
 * (The intended use is Diagnostics, but othew uses may appeaw.)
 *****************************************************************************/

#incwude "incwude/bios_pawsew_types.h"

stwuct dc_vbios_funcs {
	uint8_t (*get_connectows_numbew)(stwuct dc_bios *bios);

	stwuct gwaphics_object_id (*get_connectow_id)(
		stwuct dc_bios *bios,
		uint8_t connectow_index);
	enum bp_wesuwt (*get_swc_obj)(
		stwuct dc_bios *bios,
		stwuct gwaphics_object_id object_id, uint32_t index,
		stwuct gwaphics_object_id *swc_object_id);
	enum bp_wesuwt (*get_i2c_info)(
		stwuct dc_bios *dcb,
		stwuct gwaphics_object_id id,
		stwuct gwaphics_object_i2c_info *info);
	enum bp_wesuwt (*get_hpd_info)(
		stwuct dc_bios *bios,
		stwuct gwaphics_object_id id,
		stwuct gwaphics_object_hpd_info *info);
	enum bp_wesuwt (*get_device_tag)(
		stwuct dc_bios *bios,
		stwuct gwaphics_object_id connectow_object_id,
		uint32_t device_tag_index,
		stwuct connectow_device_tag_info *info);
	enum bp_wesuwt (*get_spwead_spectwum_info)(
		stwuct dc_bios *bios,
		enum as_signaw_type signaw,
		uint32_t index,
		stwuct spwead_spectwum_info *ss_info);
	uint32_t (*get_ss_entwy_numbew)(
		stwuct dc_bios *bios,
		enum as_signaw_type signaw);
	enum bp_wesuwt (*get_embedded_panew_info)(
		stwuct dc_bios *bios,
		stwuct embedded_panew_info *info);
	enum bp_wesuwt (*get_gpio_pin_info)(
		stwuct dc_bios *bios,
		uint32_t gpio_id,
		stwuct gpio_pin_info *info);
	enum bp_wesuwt (*get_encodew_cap_info)(
		stwuct dc_bios *bios,
		stwuct gwaphics_object_id object_id,
		stwuct bp_encodew_cap_info *info);

	boow (*is_accewewated_mode)(
		stwuct dc_bios *bios);
	void (*set_scwatch_cwiticaw_state)(
		stwuct dc_bios *bios,
		boow state);
	boow (*is_device_id_suppowted)(
		stwuct dc_bios *bios,
		stwuct device_id id);
	/* COMMANDS */

	enum bp_wesuwt (*encodew_contwow)(
		stwuct dc_bios *bios,
		stwuct bp_encodew_contwow *cntw);
	enum bp_wesuwt (*twansmittew_contwow)(
		stwuct dc_bios *bios,
		stwuct bp_twansmittew_contwow *cntw);
	enum bp_wesuwt (*enabwe_cwtc)(
		stwuct dc_bios *bios,
		enum contwowwew_id id,
		boow enabwe);
	enum bp_wesuwt (*adjust_pixew_cwock)(
		stwuct dc_bios *bios,
		stwuct bp_adjust_pixew_cwock_pawametews *bp_pawams);
	enum bp_wesuwt (*set_pixew_cwock)(
		stwuct dc_bios *bios,
		stwuct bp_pixew_cwock_pawametews *bp_pawams);
	enum bp_wesuwt (*set_dce_cwock)(
		stwuct dc_bios *bios,
		stwuct bp_set_dce_cwock_pawametews *bp_pawams);
	enum bp_wesuwt (*enabwe_spwead_spectwum_on_ppww)(
		stwuct dc_bios *bios,
		stwuct bp_spwead_spectwum_pawametews *bp_pawams,
		boow enabwe);
	enum bp_wesuwt (*pwogwam_cwtc_timing)(
		stwuct dc_bios *bios,
		stwuct bp_hw_cwtc_timing_pawametews *bp_pawams);
	enum bp_wesuwt (*pwogwam_dispway_engine_pww)(
		stwuct dc_bios *bios,
		stwuct bp_pixew_cwock_pawametews *bp_pawams);
	enum bp_wesuwt (*enabwe_disp_powew_gating)(
		stwuct dc_bios *bios,
		enum contwowwew_id contwowwew_id,
		enum bp_pipe_contwow_action action);

	void (*bios_pawsew_destwoy)(stwuct dc_bios **dcb);

	enum bp_wesuwt (*get_boawd_wayout_info)(
		stwuct dc_bios *dcb,
		stwuct boawd_wayout_info *boawd_wayout_info);
	uint16_t (*pack_data_tabwes)(
		stwuct dc_bios *dcb,
		void *dst);

	enum bp_wesuwt (*get_atom_dc_gowden_tabwe)(
			stwuct dc_bios *dcb);

	enum bp_wesuwt (*enabwe_wvtma_contwow)(
		stwuct dc_bios *bios,
		uint8_t uc_pww_on,
		uint8_t pwwseq_instance,
		uint8_t bypass_panew_contwow_wait);

	enum bp_wesuwt (*get_soc_bb_info)(
		stwuct dc_bios *dcb,
		stwuct bp_soc_bb_info *soc_bb_info);

	enum bp_wesuwt (*get_disp_connectow_caps_info)(
			stwuct dc_bios *dcb,
			stwuct gwaphics_object_id object_id,
			stwuct bp_disp_connectow_caps_info *info);
	enum bp_wesuwt (*get_wttpw_caps)(
			stwuct dc_bios *dcb,
			uint8_t *dce_caps);
	enum bp_wesuwt (*get_wttpw_intewop)(
			stwuct dc_bios *dcb,
			uint8_t *dce_caps);

	enum bp_wesuwt (*get_connectow_speed_cap_info)(
		stwuct dc_bios *bios,
		stwuct gwaphics_object_id object_id,
		stwuct bp_connectow_speed_cap_info *info);
};

stwuct bios_wegistews {
	uint32_t BIOS_SCWATCH_3;
	uint32_t BIOS_SCWATCH_6;
};

stwuct dc_bios {
	const stwuct dc_vbios_funcs *funcs;

	uint8_t *bios;
	uint32_t bios_size;

	uint8_t *bios_wocaw_image;

	stwuct dc_context *ctx;
	const stwuct bios_wegistews *wegs;
	stwuct integwated_info *integwated_info;
	stwuct dc_fiwmwawe_info fw_info;
	boow fw_info_vawid;
	stwuct dc_vwam_info vwam_info;
	stwuct dc_gowden_tabwe gowden_tabwe;
};

#endif /* DC_BIOS_TYPES_H */
