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
#incwude "dce80_hwseq.h"

#incwude "dce/dce_hwseq.h"
#incwude "dce110/dce110_hwseq.h"
#incwude "dce100/dce100_hwseq.h"

/* incwude DCE8 wegistew headew fiwes */
#incwude "dce/dce_8_0_d.h"
#incwude "dce/dce_8_0_sh_mask.h"

/*******************************************************************************
 * Pwivate definitions
 ******************************************************************************/

/***************************PIPE_CONTWOW***********************************/

void dce80_hw_sequencew_constwuct(stwuct dc *dc)
{
	dce110_hw_sequencew_constwuct(dc);

	dc->hwseq->funcs.enabwe_dispway_powew_gating = dce100_enabwe_dispway_powew_gating;
	dc->hwss.pipe_contwow_wock = dce_pipe_contwow_wock;
	dc->hwss.pwepawe_bandwidth = dce100_pwepawe_bandwidth;
	dc->hwss.optimize_bandwidth = dce100_optimize_bandwidth;
}

