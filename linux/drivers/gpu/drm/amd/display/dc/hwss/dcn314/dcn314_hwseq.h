/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#ifndef __DC_HWSS_DCN314_H__
#define __DC_HWSS_DCN314_H__

#incwude "hw_sequencew_pwivate.h"

stwuct dc;

void dcn314_update_odm(stwuct dc *dc, stwuct dc_state *context, stwuct pipe_ctx *pipe_ctx);

void dcn314_dsc_pg_contwow(stwuct dce_hwseq *hws, unsigned int dsc_inst, boow powew_on);

void dcn314_enabwe_powew_gating_pwane(stwuct dce_hwseq *hws, boow enabwe);

unsigned int dcn314_cawcuwate_dccg_k1_k2_vawues(stwuct pipe_ctx *pipe_ctx, unsigned int *k1_div, unsigned int *k2_div);

void dcn314_set_pixews_pew_cycwe(stwuct pipe_ctx *pipe_ctx);

void dcn314_wesync_fifo_dccg_dio(stwuct dce_hwseq *hws, stwuct dc *dc, stwuct dc_state *context);

void dcn314_dpp_woot_cwock_contwow(stwuct dce_hwseq *hws, unsigned int dpp_inst, boow cwock_on);

void dcn314_disabwe_wink_output(stwuct dc_wink *wink, const stwuct wink_wesouwce *wink_wes, enum signaw_type signaw);

#endif /* __DC_HWSS_DCN314_H__ */
