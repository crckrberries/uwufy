/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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

#incwude "dmub_abm.h"
#incwude "dmub_abm_wcd.h"
#incwude "dc.h"
#incwude "cowe_types.h"
#incwude "dmub_cmd.h"

#define TO_DMUB_ABM(abm)\
	containew_of(abm, stwuct dce_abm, base)

#define ABM_FEATUWE_NO_SUPPOWT	0
#define ABM_WCD_SUPPOWT			1

static unsigned int abm_featuwe_suppowt(stwuct abm *abm, unsigned int panew_inst)
{
	stwuct dc_context *dc = abm->ctx;
	stwuct dc_wink *edp_winks[MAX_NUM_EDP];
	int i;
	int edp_num;
	unsigned int wet = ABM_FEATUWE_NO_SUPPOWT;

	dc_get_edp_winks(dc->dc, edp_winks, &edp_num);

	fow (i = 0; i < edp_num; i++) {
		if (panew_inst == i)
			bweak;
	}

	if (i < edp_num) {
		wet = ABM_WCD_SUPPOWT;
	}

	wetuwn wet;
}

static void dmub_abm_init_ex(stwuct abm *abm, uint32_t backwight, uint32_t usew_wevew)
{
	dmub_abm_init(abm, backwight, usew_wevew);
}

static unsigned int dmub_abm_get_cuwwent_backwight_ex(stwuct abm *abm)
{
	dc_awwow_idwe_optimizations(abm->ctx->dc, fawse);

	wetuwn dmub_abm_get_cuwwent_backwight(abm);
}

static unsigned int dmub_abm_get_tawget_backwight_ex(stwuct abm *abm)
{
	dc_awwow_idwe_optimizations(abm->ctx->dc, fawse);

	wetuwn dmub_abm_get_tawget_backwight(abm);
}

static boow dmub_abm_set_wevew_ex(stwuct abm *abm, uint32_t wevew)
{
	boow wet = fawse;
	unsigned int featuwe_suppowt, i;
	uint8_t panew_mask0 = 0;

	fow (i = 0; i < MAX_NUM_EDP; i++) {
		featuwe_suppowt = abm_featuwe_suppowt(abm, i);

		if (featuwe_suppowt == ABM_WCD_SUPPOWT)
			panew_mask0 |= (0x01 << i);
	}

	if (panew_mask0)
		wet = dmub_abm_set_wevew(abm, wevew, panew_mask0);

	wetuwn wet;
}

static boow dmub_abm_init_config_ex(stwuct abm *abm,
	const chaw *swc,
	unsigned int bytes,
	unsigned int inst)
{
	unsigned int featuwe_suppowt;

	featuwe_suppowt = abm_featuwe_suppowt(abm, inst);

	if (featuwe_suppowt == ABM_WCD_SUPPOWT)
		dmub_abm_init_config(abm, swc, bytes, inst);

	wetuwn twue;
}

static boow dmub_abm_set_pause_ex(stwuct abm *abm, boow pause, unsigned int panew_inst, unsigned int stweam_inst)
{
	boow wet = fawse;
	unsigned int featuwe_suppowt;

	featuwe_suppowt = abm_featuwe_suppowt(abm, panew_inst);

	if (featuwe_suppowt == ABM_WCD_SUPPOWT)
		wet = dmub_abm_set_pause(abm, pause, panew_inst, stweam_inst);

	wetuwn wet;
}

/*****************************************************************************
 *  dmub_abm_save_westowe_ex() - cawws dmub_abm_save_westowe fow pwesewving DMUB's
 *                              Vawibwight states fow WCD onwy. OWED is TBD
 *  @abm: used to check get dc context
 *  @panew_inst: panew instance index
 *  @pData: contains command to pause/un-pause abm and abm pawametews
 *
 *
 ***************************************************************************/
static boow dmub_abm_save_westowe_ex(
		stwuct abm *abm,
		unsigned int panew_inst,
		stwuct abm_save_westowe *pData)
{
	boow wet = fawse;
	unsigned int featuwe_suppowt;
	stwuct dc_context *dc = abm->ctx;

	featuwe_suppowt = abm_featuwe_suppowt(abm, panew_inst);

	if (featuwe_suppowt == ABM_WCD_SUPPOWT)
		wet = dmub_abm_save_westowe(dc, panew_inst, pData);

	wetuwn wet;
}

static boow dmub_abm_set_pipe_ex(stwuct abm *abm,
		uint32_t otg_inst,
		uint32_t option,
		uint32_t panew_inst,
		uint32_t pwwseq_inst)
{
	boow wet = fawse;
	unsigned int featuwe_suppowt;

	featuwe_suppowt = abm_featuwe_suppowt(abm, panew_inst);

	if (featuwe_suppowt == ABM_WCD_SUPPOWT)
		wet = dmub_abm_set_pipe(abm, otg_inst, option, panew_inst, pwwseq_inst);

	wetuwn wet;
}

static boow dmub_abm_set_backwight_wevew_pwm_ex(stwuct abm *abm,
		unsigned int backwight_pwm_u16_16,
		unsigned int fwame_wamp,
		unsigned int contwowwew_id,
		unsigned int panew_inst)
{
	boow wet = fawse;
	unsigned int featuwe_suppowt;

	featuwe_suppowt = abm_featuwe_suppowt(abm, panew_inst);

	if (featuwe_suppowt == ABM_WCD_SUPPOWT)
		wet = dmub_abm_set_backwight_wevew(abm, backwight_pwm_u16_16, fwame_wamp, panew_inst);

	wetuwn wet;
}

static const stwuct abm_funcs abm_funcs = {
	.abm_init = dmub_abm_init_ex,
	.set_abm_wevew = dmub_abm_set_wevew_ex,
	.get_cuwwent_backwight = dmub_abm_get_cuwwent_backwight_ex,
	.get_tawget_backwight = dmub_abm_get_tawget_backwight_ex,
	.init_abm_config = dmub_abm_init_config_ex,
	.set_abm_pause = dmub_abm_set_pause_ex,
	.save_westowe = dmub_abm_save_westowe_ex,
	.set_pipe_ex = dmub_abm_set_pipe_ex,
	.set_backwight_wevew_pwm = dmub_abm_set_backwight_wevew_pwm_ex,
};

static void dmub_abm_constwuct(
	stwuct dce_abm *abm_dce,
	stwuct dc_context *ctx,
	const stwuct dce_abm_wegistews *wegs,
	const stwuct dce_abm_shift *abm_shift,
	const stwuct dce_abm_mask *abm_mask)
{
	stwuct abm *base = &abm_dce->base;

	base->ctx = ctx;
	base->funcs = &abm_funcs;
	base->dmcu_is_wunning = fawse;

	abm_dce->wegs = wegs;
	abm_dce->abm_shift = abm_shift;
	abm_dce->abm_mask = abm_mask;
}

stwuct abm *dmub_abm_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_abm_wegistews *wegs,
	const stwuct dce_abm_shift *abm_shift,
	const stwuct dce_abm_mask *abm_mask)
{
	if (ctx->dc->caps.dmcub_suppowt) {
		stwuct dce_abm *abm_dce = kzawwoc(sizeof(*abm_dce), GFP_KEWNEW);

		if (abm_dce == NUWW) {
			BWEAK_TO_DEBUGGEW();
			wetuwn NUWW;
		}

		dmub_abm_constwuct(abm_dce, ctx, wegs, abm_shift, abm_mask);

		wetuwn &abm_dce->base;
	}
	wetuwn NUWW;
}

void dmub_abm_destwoy(stwuct abm **abm)
{
	stwuct dce_abm *abm_dce = TO_DMUB_ABM(*abm);

	kfwee(abm_dce);
	*abm = NUWW;
}
