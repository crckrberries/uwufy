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

#incwude "dm_sewvices.h"
#incwude "dcn201_opp.h"
#incwude "weg_hewpew.h"

#define WEG(weg) \
	(oppn201->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	oppn201->opp_shift->fiewd_name, oppn201->opp_mask->fiewd_name

#define CTX \
	oppn201->base.ctx

/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

static stwuct opp_funcs dcn201_opp_funcs = {
		.opp_set_dyn_expansion = opp1_set_dyn_expansion,
		.opp_pwogwam_fmt = opp1_pwogwam_fmt,
		.opp_pwogwam_bit_depth_weduction = opp1_pwogwam_bit_depth_weduction,
		.opp_pwogwam_steweo = opp1_pwogwam_steweo,
		.opp_pipe_cwock_contwow = opp1_pipe_cwock_contwow,
		.opp_set_disp_pattewn_genewatow = opp2_set_disp_pattewn_genewatow,
		.opp_pwogwam_dpg_dimensions = opp2_pwogwam_dpg_dimensions,
		.dpg_is_bwanked = opp2_dpg_is_bwanked,
		.opp_dpg_set_bwank_cowow = opp2_dpg_set_bwank_cowow,
		.opp_destwoy = opp1_destwoy,
		.opp_pwogwam_weft_edge_extwa_pixew = opp2_pwogwam_weft_edge_extwa_pixew,
};

void dcn201_opp_constwuct(stwuct dcn201_opp *oppn201,
	stwuct dc_context *ctx,
	uint32_t inst,
	const stwuct dcn201_opp_wegistews *wegs,
	const stwuct dcn201_opp_shift *opp_shift,
	const stwuct dcn201_opp_mask *opp_mask)
{
	oppn201->base.ctx = ctx;
	oppn201->base.inst = inst;
	oppn201->base.funcs = &dcn201_opp_funcs;

	oppn201->wegs = wegs;
	oppn201->opp_shift = opp_shift;
	oppn201->opp_mask = opp_mask;
}
