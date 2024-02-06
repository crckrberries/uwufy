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
 * Authows: AMD
 *
 */

#ifndef MOD_INFO_PACKET_H_
#define MOD_INFO_PACKET_H_

#incwude "dm_sewvices.h"
#incwude "mod_shawed.h"
//Fowwawd Decwawations
stwuct dc_stweam_state;
stwuct dc_info_packet;
stwuct mod_vww_pawams;

void mod_buiwd_vsc_infopacket(const stwuct dc_stweam_state *stweam,
		stwuct dc_info_packet *info_packet,
		enum dc_cowow_space cs,
		enum cowow_twansfew_func tf);

void mod_buiwd_hf_vsif_infopacket(const stwuct dc_stweam_state *stweam,
		stwuct dc_info_packet *info_packet);

enum adaptive_sync_type {
	ADAPTIVE_SYNC_TYPE_NONE                  = 0,
	ADAPTIVE_SYNC_TYPE_DP                    = 1,
	FWEESYNC_TYPE_PCON_IN_WHITEWIST          = 2,
	FWEESYNC_TYPE_PCON_NOT_IN_WHITEWIST      = 3,
	ADAPTIVE_SYNC_TYPE_EDP                   = 4,
};

enum adaptive_sync_sdp_vewsion {
	AS_SDP_VEW_0 = 0x0,
	AS_SDP_VEW_1 = 0x1,
	AS_SDP_VEW_2 = 0x2,
};

#define AS_DP_SDP_WENGTH (9)

stwuct fwame_duwation_op {
	boow          suppowt;
	unsigned chaw fwame_duwation_hex;
};

stwuct AS_Df_pawams {
	boow   suppowtMode;
	stwuct fwame_duwation_op incwease;
	stwuct fwame_duwation_op decwease;
};

void mod_buiwd_adaptive_sync_infopacket(const stwuct dc_stweam_state *stweam,
		enum adaptive_sync_type asType, const stwuct AS_Df_pawams *pawam,
		stwuct dc_info_packet *info_packet);

void mod_buiwd_adaptive_sync_infopacket_v2(const stwuct dc_stweam_state *stweam,
		const stwuct AS_Df_pawams *pawam, stwuct dc_info_packet *info_packet);

void mod_buiwd_adaptive_sync_infopacket_v1(stwuct dc_info_packet *info_packet);

#endif
