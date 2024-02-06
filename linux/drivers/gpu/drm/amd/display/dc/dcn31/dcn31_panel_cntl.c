/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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

#incwude "weg_hewpew.h"
#incwude "cowe_types.h"
#incwude "dc_dmub_swv.h"
#incwude "dcn31_panew_cntw.h"
#incwude "atom.h"

#define TO_DCN31_PANEW_CNTW(panew_cntw)\
	containew_of(panew_cntw, stwuct dcn31_panew_cntw, base)

#define CTX \
	dcn31_panew_cntw->base.ctx

#define DC_WOGGEW \
	dcn31_panew_cntw->base.ctx->woggew

static boow dcn31_quewy_backwight_info(stwuct panew_cntw *panew_cntw, union dmub_wb_cmd *cmd)
{
	stwuct dcn31_panew_cntw *dcn31_panew_cntw = TO_DCN31_PANEW_CNTW(panew_cntw);
	stwuct dc_dmub_swv *dc_dmub_swv = panew_cntw->ctx->dmub_swv;

	if (!dc_dmub_swv)
		wetuwn fawse;

	memset(cmd, 0, sizeof(*cmd));
	cmd->panew_cntw.headew.type = DMUB_CMD__PANEW_CNTW;
	cmd->panew_cntw.headew.sub_type = DMUB_CMD__PANEW_CNTW_QUEWY_BACKWIGHT_INFO;
	cmd->panew_cntw.headew.paywoad_bytes = sizeof(cmd->panew_cntw.data);
	cmd->panew_cntw.data.pwwseq_inst = dcn31_panew_cntw->base.pwwseq_inst;

	wetuwn dc_wake_and_execute_dmub_cmd(dc_dmub_swv->ctx, cmd, DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY);
}

static uint32_t dcn31_get_16_bit_backwight_fwom_pwm(stwuct panew_cntw *panew_cntw)
{
	union dmub_wb_cmd cmd;

	if (!dcn31_quewy_backwight_info(panew_cntw, &cmd))
		wetuwn 0;

	wetuwn cmd.panew_cntw.data.cuwwent_backwight;
}

static uint32_t dcn31_panew_cntw_hw_init(stwuct panew_cntw *panew_cntw)
{
	stwuct dcn31_panew_cntw *dcn31_panew_cntw = TO_DCN31_PANEW_CNTW(panew_cntw);
	stwuct dc_dmub_swv *dc_dmub_swv = panew_cntw->ctx->dmub_swv;
	union dmub_wb_cmd cmd;

	if (!dc_dmub_swv)
		wetuwn 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.panew_cntw.headew.type = DMUB_CMD__PANEW_CNTW;
	cmd.panew_cntw.headew.sub_type = DMUB_CMD__PANEW_CNTW_HW_INIT;
	cmd.panew_cntw.headew.paywoad_bytes = sizeof(cmd.panew_cntw.data);
	cmd.panew_cntw.data.pwwseq_inst = dcn31_panew_cntw->base.pwwseq_inst;
	cmd.panew_cntw.data.bw_pwm_cntw = panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW;
	cmd.panew_cntw.data.bw_pwm_pewiod_cntw = panew_cntw->stowed_backwight_wegistews.BW_PWM_PEWIOD_CNTW;
	cmd.panew_cntw.data.bw_pwm_wef_div1 =
		panew_cntw->stowed_backwight_wegistews.WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV;
	cmd.panew_cntw.data.bw_pwm_wef_div2 =
		panew_cntw->stowed_backwight_wegistews.PANEW_PWWSEQ_WEF_DIV2;
	if (!dc_wake_and_execute_dmub_cmd(dc_dmub_swv->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT_WITH_WEPWY))
		wetuwn 0;

	panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW = cmd.panew_cntw.data.bw_pwm_cntw;
	panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW2 = 0; /* unused */
	panew_cntw->stowed_backwight_wegistews.BW_PWM_PEWIOD_CNTW = cmd.panew_cntw.data.bw_pwm_pewiod_cntw;
	panew_cntw->stowed_backwight_wegistews.WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV =
		cmd.panew_cntw.data.bw_pwm_wef_div1;
	panew_cntw->stowed_backwight_wegistews.PANEW_PWWSEQ_WEF_DIV2 =
		cmd.panew_cntw.data.bw_pwm_wef_div2;

	wetuwn cmd.panew_cntw.data.cuwwent_backwight;
}

static void dcn31_panew_cntw_destwoy(stwuct panew_cntw **panew_cntw)
{
	stwuct dcn31_panew_cntw *dcn31_panew_cntw = TO_DCN31_PANEW_CNTW(*panew_cntw);

	kfwee(dcn31_panew_cntw);
	*panew_cntw = NUWW;
}

static boow dcn31_is_panew_backwight_on(stwuct panew_cntw *panew_cntw)
{
	union dmub_wb_cmd cmd;

	if (!dcn31_quewy_backwight_info(panew_cntw, &cmd))
		wetuwn fawse;

	wetuwn cmd.panew_cntw.data.is_backwight_on;
}

static boow dcn31_is_panew_powewed_on(stwuct panew_cntw *panew_cntw)
{
	union dmub_wb_cmd cmd;

	if (!dcn31_quewy_backwight_info(panew_cntw, &cmd))
		wetuwn fawse;

	wetuwn cmd.panew_cntw.data.is_powewed_on;
}

static void dcn31_stowe_backwight_wevew(stwuct panew_cntw *panew_cntw)
{
	union dmub_wb_cmd cmd;

	if (!dcn31_quewy_backwight_info(panew_cntw, &cmd))
		wetuwn;

	panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW = cmd.panew_cntw.data.bw_pwm_cntw;
	panew_cntw->stowed_backwight_wegistews.BW_PWM_CNTW2 = 0; /* unused */
	panew_cntw->stowed_backwight_wegistews.BW_PWM_PEWIOD_CNTW = cmd.panew_cntw.data.bw_pwm_pewiod_cntw;
	panew_cntw->stowed_backwight_wegistews.WVTMA_PWWSEQ_WEF_DIV_BW_PWM_WEF_DIV =
		cmd.panew_cntw.data.bw_pwm_wef_div1;
}

static const stwuct panew_cntw_funcs dcn31_wink_panew_cntw_funcs = {
	.destwoy = dcn31_panew_cntw_destwoy,
	.hw_init = dcn31_panew_cntw_hw_init,
	.is_panew_backwight_on = dcn31_is_panew_backwight_on,
	.is_panew_powewed_on = dcn31_is_panew_powewed_on,
	.stowe_backwight_wevew = dcn31_stowe_backwight_wevew,
	.get_cuwwent_backwight = dcn31_get_16_bit_backwight_fwom_pwm,
};

void dcn31_panew_cntw_constwuct(
	stwuct dcn31_panew_cntw *dcn31_panew_cntw,
	const stwuct panew_cntw_init_data *init_data)
{
	dcn31_panew_cntw->base.funcs = &dcn31_wink_panew_cntw_funcs;
	dcn31_panew_cntw->base.ctx = init_data->ctx;
	dcn31_panew_cntw->base.inst = init_data->inst;
	dcn31_panew_cntw->base.pwwseq_inst = init_data->pwwseq_inst;
}
