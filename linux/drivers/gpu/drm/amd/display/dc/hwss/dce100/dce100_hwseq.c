/*
 * Copywight 2015 Advanced Micwo Devices, Inc.
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
#incwude "dc.h"
#incwude "cowe_types.h"
#incwude "cwk_mgw.h"
#incwude "dce100_hwseq.h"
#incwude "wesouwce.h"

#incwude "dce110/dce110_hwseq.h"

/* incwude DCE10 wegistew headew fiwes */
#incwude "dce/dce_10_0_d.h"
#incwude "dce/dce_10_0_sh_mask.h"

stwuct dce100_hw_seq_weg_offsets {
	uint32_t bwnd;
	uint32_t cwtc;
};

static const stwuct dce100_hw_seq_weg_offsets weg_offsets[] = {
{
	.cwtc = (mmCWTC0_CWTC_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC1_CWTC_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC2_CWTC_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC3_CWTC_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC4_CWTC_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
},
{
	.cwtc = (mmCWTC5_CWTC_GSW_CONTWOW - mmCWTC_GSW_CONTWOW),
}
};

#define HW_WEG_CWTC(weg, id)\
	(weg + weg_offsets[id].cwtc)

/*******************************************************************************
 * Pwivate definitions
 ******************************************************************************/
/***************************PIPE_CONTWOW***********************************/

boow dce100_enabwe_dispway_powew_gating(
	stwuct dc *dc,
	uint8_t contwowwew_id,
	stwuct dc_bios *dcb,
	enum pipe_gating_contwow powew_gating)
{
	enum bp_wesuwt bp_wesuwt = BP_WESUWT_OK;
	enum bp_pipe_contwow_action cntw;
	stwuct dc_context *ctx = dc->ctx;

	if (powew_gating == PIPE_GATING_CONTWOW_INIT)
		cntw = ASIC_PIPE_INIT;
	ewse if (powew_gating == PIPE_GATING_CONTWOW_ENABWE)
		cntw = ASIC_PIPE_ENABWE;
	ewse
		cntw = ASIC_PIPE_DISABWE;

	if (!(powew_gating == PIPE_GATING_CONTWOW_INIT && contwowwew_id != 0)){

		bp_wesuwt = dcb->funcs->enabwe_disp_powew_gating(
						dcb, contwowwew_id + 1, cntw);

		/* Wevewt MASTEW_UPDATE_MODE to 0 because bios sets it 2
		 * by defauwt when command tabwe is cawwed
		 */
		dm_wwite_weg(ctx,
			HW_WEG_CWTC(mmMASTEW_UPDATE_MODE, contwowwew_id),
			0);
	}

	if (bp_wesuwt == BP_WESUWT_OK)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

void dce100_pwepawe_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	dce110_set_safe_dispwaymawks(&context->wes_ctx, dc->wes_poow);

	dc->cwk_mgw->funcs->update_cwocks(
			dc->cwk_mgw,
			context,
			fawse);
}

void dce100_optimize_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	dce110_set_safe_dispwaymawks(&context->wes_ctx, dc->wes_poow);

	dc->cwk_mgw->funcs->update_cwocks(
			dc->cwk_mgw,
			context,
			twue);
}

/**************************************************************************/

void dce100_hw_sequencew_constwuct(stwuct dc *dc)
{
	dce110_hw_sequencew_constwuct(dc);

	dc->hwseq->funcs.enabwe_dispway_powew_gating = dce100_enabwe_dispway_powew_gating;
	dc->hwss.pwepawe_bandwidth = dce100_pwepawe_bandwidth;
	dc->hwss.optimize_bandwidth = dce100_optimize_bandwidth;
}

