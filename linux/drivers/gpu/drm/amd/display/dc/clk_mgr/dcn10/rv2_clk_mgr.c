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

#incwude "cowe_types.h"
#incwude "cwk_mgw_intewnaw.h"
#incwude "wv1_cwk_mgw.h"
#incwude "wv2_cwk_mgw.h"
#incwude "dce112/dce112_cwk_mgw.h"

static stwuct cwk_mgw_intewnaw_funcs wv2_cwk_intewnaw_funcs = {
	.set_dispcwk = dce112_set_dispcwk,
	.set_dpwefcwk = dce112_set_dpwefcwk
};

void wv2_cwk_mgw_constwuct(stwuct dc_context *ctx, stwuct cwk_mgw_intewnaw *cwk_mgw, stwuct pp_smu_funcs *pp_smu)

{
	wv1_cwk_mgw_constwuct(ctx, cwk_mgw, pp_smu);

	cwk_mgw->funcs = &wv2_cwk_intewnaw_funcs;
}
