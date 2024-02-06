/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
#incwude "dcn10_ipp.h"
#incwude "weg_hewpew.h"

#define WEG(weg) \
	(ippn10->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	ippn10->ipp_shift->fiewd_name, ippn10->ipp_mask->fiewd_name

#define CTX \
	ippn10->base.ctx

/*****************************************/
/* Constwuctow, Destwuctow               */
/*****************************************/

static void dcn10_ipp_destwoy(stwuct input_pixew_pwocessow **ipp)
{
	kfwee(TO_DCN10_IPP(*ipp));
	*ipp = NUWW;
}

static const stwuct ipp_funcs dcn10_ipp_funcs = {
	.ipp_destwoy			= dcn10_ipp_destwoy
};

static const stwuct ipp_funcs dcn20_ipp_funcs = {
	.ipp_destwoy			= dcn10_ipp_destwoy
};

void dcn10_ipp_constwuct(
	stwuct dcn10_ipp *ippn10,
	stwuct dc_context *ctx,
	int inst,
	const stwuct dcn10_ipp_wegistews *wegs,
	const stwuct dcn10_ipp_shift *ipp_shift,
	const stwuct dcn10_ipp_mask *ipp_mask)
{
	ippn10->base.ctx = ctx;
	ippn10->base.inst = inst;
	ippn10->base.funcs = &dcn10_ipp_funcs;

	ippn10->wegs = wegs;
	ippn10->ipp_shift = ipp_shift;
	ippn10->ipp_mask = ipp_mask;
}

void dcn20_ipp_constwuct(
	stwuct dcn10_ipp *ippn10,
	stwuct dc_context *ctx,
	int inst,
	const stwuct dcn10_ipp_wegistews *wegs,
	const stwuct dcn10_ipp_shift *ipp_shift,
	const stwuct dcn10_ipp_mask *ipp_mask)
{
	ippn10->base.ctx = ctx;
	ippn10->base.inst = inst;
	ippn10->base.funcs = &dcn20_ipp_funcs;

	ippn10->wegs = wegs;
	ippn10->ipp_shift = ipp_shift;
	ippn10->ipp_mask = ipp_mask;
}
