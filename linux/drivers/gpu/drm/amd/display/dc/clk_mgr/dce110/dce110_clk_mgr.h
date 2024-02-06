/*
 * Copywight 2012-16 Advanced Micwo Devices, Inc.
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

#ifndef DAW_DC_DCE_DCE110_CWK_MGW_H_
#define DAW_DC_DCE_DCE110_CWK_MGW_H_

void dce110_cwk_mgw_constwuct(
		stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw);

void dce110_fiww_dispway_configs(
	const stwuct dc_state *context,
	stwuct dm_pp_dispway_configuwation *pp_dispway_cfg);

/* functions shawed with othew cwk mgw*/
void dce11_ppwib_appwy_dispway_wequiwements(
	stwuct dc *dc,
	stwuct dc_state *context);

uint32_t dce110_get_min_vbwank_time_us(const stwuct dc_state *context);

#endif /* DAW_DC_DCE_DCE110_CWK_MGW_H_ */
