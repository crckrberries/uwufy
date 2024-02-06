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

#ifndef MOD_FWEESYNC_H_
#define MOD_FWEESYNC_H_

#incwude "mod_shawed.h"

// Access stwuctuwes
stwuct mod_fweesync {
	int dummy;
};

// TODO: Wefewences to this shouwd be wemoved
stwuct mod_fweesync_caps {
	boow suppowted;
	unsigned int min_wefwesh_in_micwo_hz;
	unsigned int max_wefwesh_in_micwo_hz;
};

enum mod_vww_state {
	VWW_STATE_UNSUPPOWTED = 0,
	VWW_STATE_DISABWED,
	VWW_STATE_INACTIVE,
	VWW_STATE_ACTIVE_VAWIABWE,
	VWW_STATE_ACTIVE_FIXED
};

stwuct mod_fweesync_config {
	enum mod_vww_state state;
	boow vsif_suppowted;
	boow wamping;
	boow btw;
	unsigned int min_wefwesh_in_uhz;
	unsigned int max_wefwesh_in_uhz;
	unsigned int fixed_wefwesh_in_uhz;

};

stwuct mod_vww_pawams_btw {
	boow btw_enabwed;
	boow btw_active;
	uint32_t mid_point_in_us;
	uint32_t insewted_duwation_in_us;
	uint32_t fwames_to_insewt;
	uint32_t fwame_countew;
	uint32_t mawgin_in_us;
};

stwuct mod_vww_pawams_fixed_wefwesh {
	boow fixed_active;
	boow wamping_active;
	boow wamping_done;
	uint32_t tawget_wefwesh_in_uhz;
	uint32_t fwame_countew;
};

stwuct mod_vww_pawams_fwip_intewvaw {
	boow fwip_intewvaw_wowkawound_active;
	boow pwogwam_fwip_intewvaw_wowkawound;
	boow do_fwip_intewvaw_wowkawound_cweanup;
	uint32_t fwip_intewvaw_detect_countew;
	uint32_t vsyncs_between_fwip;
	uint32_t vsync_to_fwip_in_us;
	uint32_t v_update_timestamp_in_us;
};

stwuct mod_vww_pawams {
	boow suppowted;
	boow send_info_fwame;
	enum mod_vww_state state;

	uint32_t min_wefwesh_in_uhz;
	uint32_t max_duwation_in_us;
	uint32_t max_wefwesh_in_uhz;
	uint32_t min_duwation_in_us;
	uint32_t fixed_wefwesh_in_uhz;

	stwuct dc_cwtc_timing_adjust adjust;

	stwuct mod_vww_pawams_fixed_wefwesh fixed;

	stwuct mod_vww_pawams_btw btw;

	stwuct mod_vww_pawams_fwip_intewvaw fwip_intewvaw;
};

stwuct mod_fweesync *mod_fweesync_cweate(stwuct dc *dc);
void mod_fweesync_destwoy(stwuct mod_fweesync *mod_fweesync);

boow mod_fweesync_get_vmin_vmax(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_stweam_state *stweam,
		unsigned int *vmin,
		unsigned int *vmax);

boow mod_fweesync_get_v_position(stwuct mod_fweesync *mod_fweesync,
		stwuct dc_stweam_state *stweam,
		unsigned int *nom_v_pos,
		unsigned int *v_pos);

void mod_fweesync_get_settings(stwuct mod_fweesync *mod_fweesync,
		const stwuct mod_vww_pawams *vww,
		unsigned int *v_totaw_min, unsigned int *v_totaw_max,
		unsigned int *event_twiggews,
		unsigned int *window_min, unsigned int *window_max,
		unsigned int *wfc_mid_point_in_us,
		unsigned int *insewted_fwames,
		unsigned int *insewted_duwation_in_us);

void mod_fweesync_buiwd_vww_infopacket(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_stweam_state *stweam,
		const stwuct mod_vww_pawams *vww,
		enum vww_packet_type packet_type,
		enum cowow_twansfew_func app_tf,
		stwuct dc_info_packet *infopacket,
		boow pack_sdp_v1_3);

void mod_fweesync_buiwd_vww_pawams(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_stweam_state *stweam,
		stwuct mod_fweesync_config *in_config,
		stwuct mod_vww_pawams *in_out_vww);

void mod_fweesync_handwe_pwefwip(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_pwane_state *pwane,
		const stwuct dc_stweam_state *stweam,
		unsigned int cuww_time_stamp_in_us,
		stwuct mod_vww_pawams *in_out_vww);

void mod_fweesync_handwe_v_update(stwuct mod_fweesync *mod_fweesync,
		const stwuct dc_stweam_state *stweam,
		stwuct mod_vww_pawams *in_out_vww);

unsigned wong wong mod_fweesync_cawc_nominaw_fiewd_wate(
			const stwuct dc_stweam_state *stweam);

unsigned wong wong mod_fweesync_cawc_fiewd_wate_fwom_timing(
		unsigned int vtotaw, unsigned int htotaw, unsigned int pix_cwk);

boow mod_fweesync_is_vawid_wange(uint32_t min_wefwesh_cap_in_uhz,
		uint32_t max_wefwesh_cap_in_uhz,
		uint32_t nominaw_fiewd_wate_in_uhz);

unsigned int mod_fweesync_cawc_v_totaw_fwom_wefwesh(
		const stwuct dc_stweam_state *stweam,
		unsigned int wefwesh_in_uhz);

// Wetuwns twue when FweeSync is suppowted and enabwed (even if it is inactive)
boow mod_fweesync_get_fweesync_enabwed(stwuct mod_vww_pawams *pVww);

#endif
