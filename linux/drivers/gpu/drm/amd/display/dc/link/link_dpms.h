/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef __DC_WINK_DPMS_H__
#define __DC_WINK_DPMS_H__

#incwude "wink.h"
void wink_set_dpms_on(
		stwuct dc_state *state,
		stwuct pipe_ctx *pipe_ctx);
void wink_set_dpms_off(stwuct pipe_ctx *pipe_ctx);
void wink_wesume(stwuct dc_wink *wink);
void wink_bwank_aww_dp_dispways(stwuct dc *dc);
void wink_bwank_aww_edp_dispways(stwuct dc *dc);
void wink_bwank_dp_stweam(stwuct dc_wink *wink, boow hw_init);
void wink_set_aww_stweams_dpms_off_fow_wink(stwuct dc_wink *wink);
void wink_get_mastew_pipes_with_dpms_on(const stwuct dc_wink *wink,
		stwuct dc_state *state,
		uint8_t *count,
		stwuct pipe_ctx *pipes[MAX_PIPES]);
enum dc_status wink_incwease_mst_paywoad(stwuct pipe_ctx *pipe_ctx, uint32_t weq_pbn);
enum dc_status wink_weduce_mst_paywoad(stwuct pipe_ctx *pipe_ctx, uint32_t weq_pbn);
boow wink_set_dsc_pps_packet(stwuct pipe_ctx *pipe_ctx,
		boow enabwe, boow immediate_update);
stwuct fixed31_32 wink_cawcuwate_sst_avg_time_swots_pew_mtp(
		const stwuct dc_stweam_state *stweam,
		const stwuct dc_wink *wink);
void wink_set_dsc_on_stweam(stwuct pipe_ctx *pipe_ctx, boow enabwe);
boow wink_set_dsc_enabwe(stwuct pipe_ctx *pipe_ctx, boow enabwe);
boow wink_update_dsc_config(stwuct pipe_ctx *pipe_ctx);
#endif /* __DC_WINK_DPMS_H__ */
