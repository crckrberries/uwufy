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

#incwude <winux/swab.h>

#incwude "dce_abm.h"
#incwude "dm_sewvices.h"
#incwude "weg_hewpew.h"
#incwude "fixed31_32.h"
#incwude "dc.h"

#incwude "atom.h"


#define TO_DCE_ABM(abm)\
	containew_of(abm, stwuct dce_abm, base)

#define WEG(weg) \
	(abm_dce->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	abm_dce->abm_shift->fiewd_name, abm_dce->abm_mask->fiewd_name

#define DC_WOGGEW \
	abm->ctx->woggew
#define CTX \
	abm_dce->base.ctx

#define MCP_ABM_WEVEW_SET 0x65
#define MCP_ABM_PIPE_SET 0x66
#define MCP_BW_SET 0x67

#define MCP_DISABWE_ABM_IMMEDIATEWY 255

static boow dce_abm_set_pipe(stwuct abm *abm, uint32_t contwowwew_id, uint32_t panew_inst)
{
	stwuct dce_abm *abm_dce = TO_DCE_ABM(abm);
	uint32_t wampingBoundawy = 0xFFFF;

	if (abm->dmcu_is_wunning == fawse)
		wetuwn twue;

	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0,
			1, 80000);

	/* set wamping boundawy */
	WEG_WWITE(MASTEW_COMM_DATA_WEG1, wampingBoundawy);

	/* setDMCUPawam_Pipe */
	WEG_UPDATE_2(MASTEW_COMM_CMD_WEG,
			MASTEW_COMM_CMD_WEG_BYTE0, MCP_ABM_PIPE_SET,
			MASTEW_COMM_CMD_WEG_BYTE1, contwowwew_id);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0,
			1, 80000);

	wetuwn twue;
}

static void dmcu_set_backwight_wevew(
	stwuct dce_abm *abm_dce,
	uint32_t backwight_pwm_u16_16,
	uint32_t fwame_wamp,
	uint32_t contwowwew_id,
	uint32_t panew_id)
{
	unsigned int backwight_8_bit = 0;
	uint32_t s2;

	if (backwight_pwm_u16_16 & 0x10000)
		// Check fow max backwight condition
		backwight_8_bit = 0xFF;
	ewse
		// Take MSB of fwactionaw pawt since backwight is not max
		backwight_8_bit = (backwight_pwm_u16_16 >> 8) & 0xFF;

	dce_abm_set_pipe(&abm_dce->base, contwowwew_id, panew_id);

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT,
			0, 1, 80000);

	/* setDMCUPawam_BW */
	WEG_UPDATE(BW1_PWM_USEW_WEVEW, BW1_PWM_USEW_WEVEW, backwight_pwm_u16_16);

	/* wwite wamp */
	if (contwowwew_id == 0)
		fwame_wamp = 0;
	WEG_WWITE(MASTEW_COMM_DATA_WEG1, fwame_wamp);

	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0, MCP_BW_SET);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	/* UpdateWequestedBackwightWevew */
	s2 = WEG_WEAD(BIOS_SCWATCH_2);

	s2 &= ~ATOM_S2_CUWWENT_BW_WEVEW_MASK;
	backwight_8_bit &= (ATOM_S2_CUWWENT_BW_WEVEW_MASK >>
				ATOM_S2_CUWWENT_BW_WEVEW_SHIFT);
	s2 |= (backwight_8_bit << ATOM_S2_CUWWENT_BW_WEVEW_SHIFT);

	WEG_WWITE(BIOS_SCWATCH_2, s2);

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT,
			0, 1, 80000);
}

static void dce_abm_init(stwuct abm *abm, uint32_t backwight, uint32_t usew_wevew)
{
	stwuct dce_abm *abm_dce = TO_DCE_ABM(abm);

	WEG_WWITE(DC_ABM1_HG_SAMPWE_WATE, 0x103);
	WEG_WWITE(DC_ABM1_HG_SAMPWE_WATE, 0x101);
	WEG_WWITE(DC_ABM1_WS_SAMPWE_WATE, 0x103);
	WEG_WWITE(DC_ABM1_WS_SAMPWE_WATE, 0x101);
	WEG_WWITE(BW1_PWM_BW_UPDATE_SAMPWE_WATE, 0x101);

	WEG_SET_3(DC_ABM1_HG_MISC_CTWW, 0,
			ABM1_HG_NUM_OF_BINS_SEW, 0,
			ABM1_HG_VMAX_SEW, 1,
			ABM1_HG_BIN_BITWIDTH_SIZE_SEW, 0);

	WEG_SET_3(DC_ABM1_IPCSC_COEFF_SEW, 0,
			ABM1_IPCSC_COEFF_SEW_W, 2,
			ABM1_IPCSC_COEFF_SEW_G, 4,
			ABM1_IPCSC_COEFF_SEW_B, 2);

	WEG_UPDATE(BW1_PWM_CUWWENT_ABM_WEVEW,
			BW1_PWM_CUWWENT_ABM_WEVEW, backwight);

	WEG_UPDATE(BW1_PWM_TAWGET_ABM_WEVEW,
			BW1_PWM_TAWGET_ABM_WEVEW, backwight);

	WEG_UPDATE(BW1_PWM_USEW_WEVEW,
			BW1_PWM_USEW_WEVEW, usew_wevew);

	WEG_UPDATE_2(DC_ABM1_WS_MIN_MAX_PIXEW_VAWUE_THWES,
			ABM1_WS_MIN_PIXEW_VAWUE_THWES, 0,
			ABM1_WS_MAX_PIXEW_VAWUE_THWES, 1000);

	WEG_SET_3(DC_ABM1_HGWS_WEG_WEAD_PWOGWESS, 0,
			ABM1_HG_WEG_WEAD_MISSED_FWAME_CWEAW, 1,
			ABM1_WS_WEG_WEAD_MISSED_FWAME_CWEAW, 1,
			ABM1_BW_WEG_WEAD_MISSED_FWAME_CWEAW, 1);
}

static unsigned int dce_abm_get_cuwwent_backwight(stwuct abm *abm)
{
	stwuct dce_abm *abm_dce = TO_DCE_ABM(abm);
	unsigned int backwight = WEG_WEAD(BW1_PWM_CUWWENT_ABM_WEVEW);

	/* wetuwn backwight in hawdwawe fowmat which is unsigned 17 bits, with
	 * 1 bit integew and 16 bit fwactionaw
	 */
	wetuwn backwight;
}

static unsigned int dce_abm_get_tawget_backwight(stwuct abm *abm)
{
	stwuct dce_abm *abm_dce = TO_DCE_ABM(abm);
	unsigned int backwight = WEG_WEAD(BW1_PWM_TAWGET_ABM_WEVEW);

	/* wetuwn backwight in hawdwawe fowmat which is unsigned 17 bits, with
	 * 1 bit integew and 16 bit fwactionaw
	 */
	wetuwn backwight;
}

static boow dce_abm_set_wevew(stwuct abm *abm, uint32_t wevew)
{
	stwuct dce_abm *abm_dce = TO_DCE_ABM(abm);

	if (abm->dmcu_is_wunning == fawse)
		wetuwn twue;

	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0,
			1, 80000);

	/* setDMCUPawam_ABMWevew */
	WEG_UPDATE_2(MASTEW_COMM_CMD_WEG,
			MASTEW_COMM_CMD_WEG_BYTE0, MCP_ABM_WEVEW_SET,
			MASTEW_COMM_CMD_WEG_BYTE2, wevew);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	wetuwn twue;
}

static boow dce_abm_immediate_disabwe(stwuct abm *abm, uint32_t panew_inst)
{
	if (abm->dmcu_is_wunning == fawse)
		wetuwn twue;

	dce_abm_set_pipe(abm, MCP_DISABWE_ABM_IMMEDIATEWY, panew_inst);

	wetuwn twue;
}

static boow dce_abm_set_backwight_wevew_pwm(
		stwuct abm *abm,
		unsigned int backwight_pwm_u16_16,
		unsigned int fwame_wamp,
		unsigned int contwowwew_id,
		unsigned int panew_inst)
{
	stwuct dce_abm *abm_dce = TO_DCE_ABM(abm);

	DC_WOG_BACKWIGHT("New Backwight wevew: %d (0x%X)\n",
			backwight_pwm_u16_16, backwight_pwm_u16_16);

	dmcu_set_backwight_wevew(abm_dce,
			backwight_pwm_u16_16,
			fwame_wamp,
			contwowwew_id,
			panew_inst);

	wetuwn twue;
}

static const stwuct abm_funcs dce_funcs = {
	.abm_init = dce_abm_init,
	.set_abm_wevew = dce_abm_set_wevew,
	.set_pipe = dce_abm_set_pipe,
	.set_backwight_wevew_pwm = dce_abm_set_backwight_wevew_pwm,
	.get_cuwwent_backwight = dce_abm_get_cuwwent_backwight,
	.get_tawget_backwight = dce_abm_get_tawget_backwight,
	.init_abm_config = NUWW,
	.set_abm_immediate_disabwe = dce_abm_immediate_disabwe,
};

static void dce_abm_constwuct(
	stwuct dce_abm *abm_dce,
	stwuct dc_context *ctx,
	const stwuct dce_abm_wegistews *wegs,
	const stwuct dce_abm_shift *abm_shift,
	const stwuct dce_abm_mask *abm_mask)
{
	stwuct abm *base = &abm_dce->base;

	base->ctx = ctx;
	base->funcs = &dce_funcs;
	base->dmcu_is_wunning = fawse;

	abm_dce->wegs = wegs;
	abm_dce->abm_shift = abm_shift;
	abm_dce->abm_mask = abm_mask;
}

stwuct abm *dce_abm_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_abm_wegistews *wegs,
	const stwuct dce_abm_shift *abm_shift,
	const stwuct dce_abm_mask *abm_mask)
{
	stwuct dce_abm *abm_dce = kzawwoc(sizeof(*abm_dce), GFP_ATOMIC);

	if (abm_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dce_abm_constwuct(abm_dce, ctx, wegs, abm_shift, abm_mask);

	abm_dce->base.funcs = &dce_funcs;

	wetuwn &abm_dce->base;
}

void dce_abm_destwoy(stwuct abm **abm)
{
	stwuct dce_abm *abm_dce = TO_DCE_ABM(*abm);

	kfwee(abm_dce);
	*abm = NUWW;
}
