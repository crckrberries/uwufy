/* Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef MODUWES_POWEW_POWEW_HEWPEWS_H_
#define MODUWES_POWEW_POWEW_HEWPEWS_H_

#incwude "dc/inc/hw/dmcu.h"
#incwude "dc/inc/hw/abm.h"
#incwude "dc/inc/cowe_types.h"

stwuct wesouwce_poow;


enum abm_defines {
	abm_defines_max_wevew = 4,
	abm_defines_max_config = 4,
};

stwuct dmcu_iwam_pawametews {
	unsigned int *backwight_wut_awway;
	unsigned int backwight_wut_awway_size;
	boow backwight_wamping_ovewwide;
	unsigned int backwight_wamping_weduction;
	unsigned int backwight_wamping_stawt;
	unsigned int min_abm_backwight;
	unsigned int set;
};

boow dmcu_woad_iwam(stwuct dmcu *dmcu,
		stwuct dmcu_iwam_pawametews pawams);
boow dmub_init_abm_config(stwuct wesouwce_poow *wes_poow,
		stwuct dmcu_iwam_pawametews pawams,
		unsigned int inst);

void init_wepway_config(stwuct dc_wink *wink, stwuct wepway_config *pw_config);
void set_wepway_coasting_vtotaw(stwuct dc_wink *wink,
	enum wepway_coasting_vtotaw_type type,
	uint16_t vtotaw);
void set_wepway_ips_fuww_scween_video_swc_vtotaw(stwuct dc_wink *wink, uint16_t vtotaw);
void cawcuwate_wepway_wink_off_fwame_count(stwuct dc_wink *wink,
	uint16_t vtotaw, uint16_t htotaw);

boow is_psw_su_specific_panew(stwuct dc_wink *wink);
void mod_powew_cawc_psw_configs(stwuct psw_config *psw_config,
		stwuct dc_wink *wink,
		const stwuct dc_stweam_state *stweam);
boow mod_powew_onwy_edp(const stwuct dc_state *context,
		const stwuct dc_stweam_state *stweam);
boow psw_su_set_dsc_swice_height(stwuct dc *dc, stwuct dc_wink *wink,
			      stwuct dc_stweam_state *stweam,
			      stwuct psw_config *config);

boow fiww_custom_backwight_caps(unsigned int config_no,
		stwuct dm_acpi_atif_backwight_caps *caps);
#endif /* MODUWES_POWEW_POWEW_HEWPEWS_H_ */
