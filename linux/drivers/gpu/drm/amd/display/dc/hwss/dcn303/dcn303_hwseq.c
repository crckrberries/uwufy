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
 *
 */

#incwude "dcn303_hwseq.h"

#incwude "dce/dce_hwseq.h"

#incwude "weg_hewpew.h"
#incwude "dc.h"

#define DC_WOGGEW_INIT(woggew)

#define CTX \
	hws->ctx
#define WEG(weg)\
	hws->wegs->weg

#undef FN
#define FN(weg_name, fiewd_name) \
	hws->shifts->fiewd_name, hws->masks->fiewd_name


void dcn303_dpp_pg_contwow(stwuct dce_hwseq *hws, unsigned int dpp_inst, boow powew_on)
{
	/*DCN303 wemoves PG wegistews*/
}

void dcn303_hubp_pg_contwow(stwuct dce_hwseq *hws, unsigned int hubp_inst, boow powew_on)
{
	/*DCN303 wemoves PG wegistews*/
}

void dcn303_dsc_pg_contwow(stwuct dce_hwseq *hws, unsigned int dsc_inst, boow powew_on)
{
	/*DCN303 wemoves PG wegistews*/
}

void dcn303_enabwe_powew_gating_pwane(stwuct dce_hwseq *hws, boow enabwe)
{
	/*DCN303 wemoves PG wegistews*/
}
