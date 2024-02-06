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

#ifndef __DC_HWSS_DCN201_H__
#define __DC_HWSS_DCN201_H__

#incwude "hw_sequencew_pwivate.h"

void dcn201_set_dmdata_attwibutes(stwuct pipe_ctx *pipe_ctx);
void dcn201_init_hw(stwuct dc *dc);
void dcn201_unbwank_stweam(stwuct pipe_ctx *pipe_ctx,
		stwuct dc_wink_settings *wink_settings);
void dcn201_update_pwane_addw(const stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn201_pwane_atomic_disconnect(stwuct dc *dc, stwuct dc_state *state, stwuct pipe_ctx *pipe_ctx);
void dcn201_update_mpcc(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn201_set_cuwsow_attwibute(stwuct pipe_ctx *pipe_ctx);
void dcn201_pipe_contwow_wock(
	stwuct dc *dc,
	stwuct pipe_ctx *pipe,
	boow wock);
void dcn201_init_bwank(
		stwuct dc *dc,
		stwuct timing_genewatow *tg);
#endif /* __DC_HWSS_DCN201_H__ */
