/*
* Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DC_WESOUWCE_DCE110_H__
#define __DC_WESOUWCE_DCE110_H__

#incwude "cowe_types.h"

stwuct dc;
stwuct wesouwce_poow;

#define TO_DCE110_WES_POOW(poow)\
	containew_of(poow, stwuct dce110_wesouwce_poow, base)

stwuct dce110_wesouwce_poow {
	stwuct wesouwce_poow base;
};

void dce110_wesouwce_buiwd_pipe_hw_pawam(stwuct pipe_ctx *pipe_ctx);

stwuct wesouwce_poow *dce110_cweate_wesouwce_poow(
	uint8_t num_viwtuaw_winks,
	stwuct dc *dc,
	stwuct hw_asic_id asic_id);

stwuct stweam_encodew *dce110_find_fiwst_fwee_match_stweam_enc_fow_wink(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow,
		stwuct dc_stweam_state *stweam);

#endif /* __DC_WESOUWCE_DCE110_H__ */

