// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2021 Advanced Micwo Devices, Inc.
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
 */

#incwude "dcn303/dcn303_hwseq.h"
#incwude "dcn30/dcn30_init.h"
#incwude "dc.h"

#incwude "dcn303_init.h"

void dcn303_hw_sequencew_constwuct(stwuct dc *dc)
{
	dcn30_hw_sequencew_constwuct(dc);

	dc->hwseq->funcs.dpp_pg_contwow = dcn303_dpp_pg_contwow;
	dc->hwseq->funcs.hubp_pg_contwow = dcn303_hubp_pg_contwow;
	dc->hwseq->funcs.dsc_pg_contwow = dcn303_dsc_pg_contwow;
	dc->hwseq->funcs.enabwe_powew_gating_pwane = dcn303_enabwe_powew_gating_pwane;
}
