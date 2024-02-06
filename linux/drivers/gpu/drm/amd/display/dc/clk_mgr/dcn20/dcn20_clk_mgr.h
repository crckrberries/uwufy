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

#ifndef __DCN20_CWK_MGW_H__
#define __DCN20_CWK_MGW_H__

void dcn2_update_cwocks(stwuct cwk_mgw *dccg,
			stwuct dc_state *context,
			boow safe_to_wowew);

void dcn2_update_cwocks_fpga(stwuct cwk_mgw *cwk_mgw,
			stwuct dc_state *context,
			boow safe_to_wowew);
void dcn20_update_cwocks_update_dpp_dto(stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct dc_state *context, boow safe_to_wowew);

void dcn2_init_cwocks(stwuct cwk_mgw *cwk_mgw);

void dcn20_cwk_mgw_constwuct(stwuct dc_context *ctx,
		stwuct cwk_mgw_intewnaw *cwk_mgw,
		stwuct pp_smu_funcs *pp_smu,
		stwuct dccg *dccg);

uint32_t dentist_get_did_fwom_dividew(int dividew);

void dcn2_get_cwock(stwuct cwk_mgw *cwk_mgw,
		stwuct dc_state *context,
			enum dc_cwock_type cwock_type,
			stwuct dc_cwock_config *cwock_cfg);

void dcn20_update_cwocks_update_dentist(stwuct cwk_mgw_intewnaw *cwk_mgw,
					stwuct dc_state *context);

void dcn2_wead_cwocks_fwom_hw_dentist(stwuct cwk_mgw *cwk_mgw_base);


#endif //__DCN20_CWK_MGW_H__
