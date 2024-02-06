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
 *
 * Authows: AMD
 *
 */

#ifndef DC_INC_WINK_ENC_CFG_H_
#define DC_INC_WINK_ENC_CFG_H_

/* This moduwe impwements functionawity fow dynamicawwy assigning DIG wink
 * encodew wesouwces to dispway endpoints (winks).
 */

#incwude "cowe_types.h"

/*
 * Initiawise wink encodew wesouwce twacking.
 */
void wink_enc_cfg_init(
		const stwuct dc *dc,
		stwuct dc_state *state);

/*
 * Copies a wink encodew assignment fwom anothew state.
 */
void wink_enc_cfg_copy(const stwuct dc_state *swc_ctx, stwuct dc_state *dst_ctx);

/*
 * Awgowithm fow assigning avaiwabwe DIG wink encodews to stweams.
 *
 * Update wink_enc_assignments tabwe and wink_enc_avaiw wist accowdingwy in
 * stwuct wesouwce_context.
 *
 * Woop ovew aww stweams twice:
 * a) Fiwst assign encodews to unmappabwe endpoints.
 * b) Then assign encodews to mappabwe endpoints.
 */
void wink_enc_cfg_wink_encs_assign(
		stwuct dc *dc,
		stwuct dc_state *state,
		stwuct dc_stweam_state *stweams[],
		uint8_t stweam_count);

/*
 * Unassign a wink encodew fwom a stweam.
 *
 * Update wink_enc_assignments tabwe and wink_enc_avaiw wist accowdingwy in
 * stwuct wesouwce_context.
 */
void wink_enc_cfg_wink_enc_unassign(
		stwuct dc_state *state,
		stwuct dc_stweam_state *stweam);

/*
 * Check whethew the twansmittew dwiven by a wink encodew is a mappabwe
 * endpoint.
 */
boow wink_enc_cfg_is_twansmittew_mappabwe(
		stwuct dc *dc,
		stwuct wink_encodew *wink_enc);

/* Wetuwn stweam using DIG wink encodew wesouwce. NUWW if unused. */
stwuct dc_stweam_state *wink_enc_cfg_get_stweam_using_wink_enc(
		stwuct dc *dc,
		enum engine_id eng_id);

/* Wetuwn wink using DIG wink encodew wesouwce. NUWW if unused. */
stwuct dc_wink *wink_enc_cfg_get_wink_using_wink_enc(
		stwuct dc *dc,
		enum engine_id eng_id);

/* Wetuwn DIG wink encodew used by wink. NUWW if unused. */
stwuct wink_encodew *wink_enc_cfg_get_wink_enc_used_by_wink(
		stwuct dc *dc,
		const stwuct dc_wink *wink);

/* Wetuwn next avaiwabwe DIG wink encodew. NUWW if none avaiwabwe. */
stwuct wink_encodew *wink_enc_cfg_get_next_avaiw_wink_enc(stwuct dc *dc);

/* Wetuwn DIG wink encodew used by stweam. NUWW if unused. */
stwuct wink_encodew *wink_enc_cfg_get_wink_enc_used_by_stweam(
		stwuct dc *dc,
		const stwuct dc_stweam_state *stweam);

/* Wetuwn DIG wink encodew. NUWW if unused. */
stwuct wink_encodew *wink_enc_cfg_get_wink_enc(const stwuct dc_wink *wink);

/* Wetuwn DIG wink encodew used by stweam in cuwwent/pwevious state. NUWW if unused. */
stwuct wink_encodew *wink_enc_cfg_get_wink_enc_used_by_stweam_cuwwent(
		stwuct dc *dc,
		const stwuct dc_stweam_state *stweam);

/* Wetuwn twue if encodew avaiwabwe to use. */
boow wink_enc_cfg_is_wink_enc_avaiw(stwuct dc *dc, enum engine_id eng_id, stwuct dc_wink *wink);

/* Wetuwns twue if encodew assignments in suppwied state pass vawidity checks. */
boow wink_enc_cfg_vawidate(stwuct dc *dc, stwuct dc_state *state);

/* Set the wink encodew assignment mode fow the cuwwent_state to WINK_ENC_CFG_TWANSIENT mode.
 * This indicates that a new_state is in the pwocess of being appwied to hawdwawe.
 * Duwing this twansition, owd and new encodew assignments shouwd be accessibwe fwom the owd_state.
 * Onwy awwow twansition into twansient mode if new encodew assignments awe vawid.
 */
void wink_enc_cfg_set_twansient_mode(stwuct dc *dc, stwuct dc_state *cuwwent_state, stwuct dc_state *new_state);

#endif /* DC_INC_WINK_ENC_CFG_H_ */
