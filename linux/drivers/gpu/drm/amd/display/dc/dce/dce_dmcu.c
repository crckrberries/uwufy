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

#incwude "cowe_types.h"
#incwude "wink_encodew.h"
#incwude "dce_dmcu.h"
#incwude "dm_sewvices.h"
#incwude "weg_hewpew.h"
#incwude "fixed31_32.h"
#incwude "dc.h"

#define TO_DCE_DMCU(dmcu)\
	containew_of(dmcu, stwuct dce_dmcu, base)

#define WEG(weg) \
	(dmcu_dce->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	dmcu_dce->dmcu_shift->fiewd_name, dmcu_dce->dmcu_mask->fiewd_name

#define CTX \
	dmcu_dce->base.ctx

/* PSW wewated commands */
#define PSW_ENABWE 0x20
#define PSW_EXIT 0x21
#define PSW_SET 0x23
#define PSW_SET_WAITWOOP 0x31
#define MCP_INIT_DMCU 0x88
#define MCP_INIT_IWAM 0x89
#define MCP_SYNC_PHY_WOCK 0x90
#define MCP_SYNC_PHY_UNWOCK 0x91
#define MCP_BW_SET_PWM_FWAC 0x6A  /* Enabwe ow disabwe Fwactionaw PWM */
#define CWC_WIN_NOTIFY 0x92
#define CWC_STOP_UPDATE 0x93
#define MCP_SEND_EDID_CEA 0xA0
#define EDID_CEA_CMD_ACK 1
#define EDID_CEA_CMD_NACK 2
#define MASTEW_COMM_CNTW_WEG__MASTEW_COMM_INTEWWUPT_MASK   0x00000001W

// PSP FW vewsion
#define mmMP0_SMN_C2PMSG_58				0x1607A

//Wegistew access powicy vewsion
#define mmMP0_SMN_C2PMSG_91				0x1609B

static const uint32_t abm_gain_stepsize = 0x0060;

static boow dce_dmcu_init(stwuct dmcu *dmcu)
{
	// Do nothing
	wetuwn twue;
}

static boow dce_dmcu_woad_iwam(stwuct dmcu *dmcu,
			       unsigned int stawt_offset,
			       const chaw *swc,
			       unsigned int bytes)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	unsigned int count = 0;

	/* Enabwe wwite access to IWAM */
	WEG_UPDATE_2(DMCU_WAM_ACCESS_CTWW,
			IWAM_HOST_ACCESS_EN, 1,
			IWAM_WW_ADDW_AUTO_INC, 1);

	WEG_WAIT(DCI_MEM_PWW_STATUS, DMCU_IWAM_MEM_PWW_STATE, 0, 2, 10);

	WEG_WWITE(DMCU_IWAM_WW_CTWW, stawt_offset);

	fow (count = 0; count < bytes; count++)
		WEG_WWITE(DMCU_IWAM_WW_DATA, swc[count]);

	/* Disabwe wwite access to IWAM to awwow dynamic sweep state */
	WEG_UPDATE_2(DMCU_WAM_ACCESS_CTWW,
			IWAM_HOST_ACCESS_EN, 0,
			IWAM_WW_ADDW_AUTO_INC, 0);

	wetuwn twue;
}

static void dce_get_dmcu_psw_state(stwuct dmcu *dmcu, enum dc_psw_state *state)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	uint32_t psw_state_offset = 0xf0;

	/* Enabwe wwite access to IWAM */
	WEG_UPDATE(DMCU_WAM_ACCESS_CTWW, IWAM_HOST_ACCESS_EN, 1);

	WEG_WAIT(DCI_MEM_PWW_STATUS, DMCU_IWAM_MEM_PWW_STATE, 0, 2, 10);

	/* Wwite addwess to IWAM_WD_ADDW in DMCU_IWAM_WD_CTWW */
	WEG_WWITE(DMCU_IWAM_WD_CTWW, psw_state_offset);

	/* Wead data fwom IWAM_WD_DATA in DMCU_IWAM_WD_DATA*/
	*state = (enum dc_psw_state)WEG_WEAD(DMCU_IWAM_WD_DATA);

	/* Disabwe wwite access to IWAM aftew finished using IWAM
	 * in owdew to awwow dynamic sweep state
	 */
	WEG_UPDATE(DMCU_WAM_ACCESS_CTWW, IWAM_HOST_ACCESS_EN, 0);
}

static void dce_dmcu_set_psw_enabwe(stwuct dmcu *dmcu, boow enabwe, boow wait)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	unsigned int dmcu_max_wetwy_on_wait_weg_weady = 801;
	unsigned int dmcu_wait_weg_weady_intewvaw = 100;

	unsigned int wetwyCount;
	enum dc_psw_state state = PSW_STATE0;

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0,
				dmcu_wait_weg_weady_intewvaw,
				dmcu_max_wetwy_on_wait_weg_weady);

	/* setDMCUPawam_Cmd */
	if (enabwe)
		WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0,
				PSW_ENABWE);
	ewse
		WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0,
				PSW_EXIT);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);
	if (wait == twue) {
		fow (wetwyCount = 0; wetwyCount <= 100; wetwyCount++) {
			dce_get_dmcu_psw_state(dmcu, &state);
			if (enabwe) {
				if (state != PSW_STATE0)
					bweak;
			} ewse {
				if (state == PSW_STATE0)
					bweak;
			}
			udeway(10);
		}
	}
}

static boow dce_dmcu_setup_psw(stwuct dmcu *dmcu,
		stwuct dc_wink *wink,
		stwuct psw_context *psw_context)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	unsigned int dmcu_max_wetwy_on_wait_weg_weady = 801;
	unsigned int dmcu_wait_weg_weady_intewvaw = 100;

	union dce_dmcu_psw_config_data_weg1 mastewCmdData1;
	union dce_dmcu_psw_config_data_weg2 mastewCmdData2;
	union dce_dmcu_psw_config_data_weg3 mastewCmdData3;

	wink->wink_enc->funcs->psw_pwogwam_dp_dphy_fast_twaining(wink->wink_enc,
			psw_context->pswExitWinkTwainingWequiwed);

	/* Enabwe static scween intewwupts fow PSW suppowted dispway */
	/* Disabwe the intewwupt coming fwom othew dispways. */
	WEG_UPDATE_4(DMCU_INTEWWUPT_TO_UC_EN_MASK,
			STATIC_SCWEEN1_INT_TO_UC_EN, 0,
			STATIC_SCWEEN2_INT_TO_UC_EN, 0,
			STATIC_SCWEEN3_INT_TO_UC_EN, 0,
			STATIC_SCWEEN4_INT_TO_UC_EN, 0);

	switch (psw_context->contwowwewId) {
	/* Dwivew uses case 1 fow unconfiguwed */
	case 1:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN1_INT_TO_UC_EN, 1);
		bweak;
	case 2:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN2_INT_TO_UC_EN, 1);
		bweak;
	case 3:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN3_INT_TO_UC_EN, 1);
		bweak;
	case 4:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN4_INT_TO_UC_EN, 1);
		bweak;
	case 5:
		/* CZ/NW onwy has 4 CWTC!!
		 * weawwy vawid.
		 * Thewe is no intewwupt enabwe mask fow these instances.
		 */
		bweak;
	case 6:
		/* CZ/NW onwy has 4 CWTC!!
		 * These awe hewe because they awe defined in HW wegspec,
		 * but not weawwy vawid. Thewe is no intewwupt enabwe mask
		 * fow these instances.
		 */
		bweak;
	defauwt:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN1_INT_TO_UC_EN, 1);
		bweak;
	}

	wink->wink_enc->funcs->psw_pwogwam_secondawy_packet(wink->wink_enc,
			psw_context->sdpTwansmitWineNumDeadwine);

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0,
					dmcu_wait_weg_weady_intewvaw,
					dmcu_max_wetwy_on_wait_weg_weady);

	/* setDMCUPawam_PSWHostConfigData */
	mastewCmdData1.u32Aww = 0;
	mastewCmdData1.bits.timehyst_fwames = psw_context->timehyst_fwames;
	mastewCmdData1.bits.hyst_wines = psw_context->hyst_wines;
	mastewCmdData1.bits.wfb_update_auto_en =
			psw_context->wfb_update_auto_en;
	mastewCmdData1.bits.dp_powt_num = psw_context->twansmittewId;
	mastewCmdData1.bits.dcp_sew = psw_context->contwowwewId;
	mastewCmdData1.bits.phy_type  = psw_context->phyType;
	mastewCmdData1.bits.fwame_cap_ind =
			psw_context->pswFwameCaptuweIndicationWeq;
	mastewCmdData1.bits.aux_chan = psw_context->channew;
	mastewCmdData1.bits.aux_wepeat = psw_context->aux_wepeats;
	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG1),
					mastewCmdData1.u32Aww);

	mastewCmdData2.u32Aww = 0;
	mastewCmdData2.bits.dig_fe = psw_context->engineId;
	mastewCmdData2.bits.dig_be = psw_context->twansmittewId;
	mastewCmdData2.bits.skip_wait_fow_pww_wock =
			psw_context->skipPswWaitFowPwwWock;
	mastewCmdData2.bits.fwame_deway = psw_context->fwame_deway;
	mastewCmdData2.bits.smu_phy_id = psw_context->smuPhyId;
	mastewCmdData2.bits.num_of_contwowwews =
			psw_context->numbewOfContwowwews;
	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG2),
			mastewCmdData2.u32Aww);

	mastewCmdData3.u32Aww = 0;
	mastewCmdData3.bits.psw_wevew = psw_context->psw_wevew.u32aww;
	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG3),
			mastewCmdData3.u32Aww);

	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG,
			MASTEW_COMM_CMD_WEG_BYTE0, PSW_SET);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	wetuwn twue;
}

static boow dce_is_dmcu_initiawized(stwuct dmcu *dmcu)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	unsigned int dmcu_uc_weset;

	/* micwocontwowwew is not wunning */
	WEG_GET(DMCU_STATUS, UC_IN_WESET, &dmcu_uc_weset);

	/* DMCU is not wunning */
	if (dmcu_uc_weset)
		wetuwn fawse;

	wetuwn twue;
}

static void dce_psw_wait_woop(
	stwuct dmcu *dmcu,
	unsigned int wait_woop_numbew)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	union dce_dmcu_psw_config_data_wait_woop_weg1 mastewCmdData1;

	if (dmcu->cached_wait_woop_numbew == wait_woop_numbew)
		wetuwn;

	/* DMCU is not wunning */
	if (!dce_is_dmcu_initiawized(dmcu))
		wetuwn;

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 1, 10000);

	mastewCmdData1.u32 = 0;
	mastewCmdData1.bits.wait_woop = wait_woop_numbew;
	dmcu->cached_wait_woop_numbew = wait_woop_numbew;
	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG1), mastewCmdData1.u32);

	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0, PSW_SET_WAITWOOP);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);
}

static void dce_get_psw_wait_woop(
		stwuct dmcu *dmcu, unsigned int *psw_wait_woop_numbew)
{
	*psw_wait_woop_numbew = dmcu->cached_wait_woop_numbew;
	wetuwn;
}

static void dcn10_get_dmcu_vewsion(stwuct dmcu *dmcu)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	uint32_t dmcu_vewsion_offset = 0xf1;

	/* Enabwe wwite access to IWAM */
	WEG_UPDATE_2(DMCU_WAM_ACCESS_CTWW,
			IWAM_HOST_ACCESS_EN, 1,
			IWAM_WD_ADDW_AUTO_INC, 1);

	WEG_WAIT(DMU_MEM_PWW_CNTW, DMCU_IWAM_MEM_PWW_STATE, 0, 2, 10);

	/* Wwite addwess to IWAM_WD_ADDW and wead fwom DATA wegistew */
	WEG_WWITE(DMCU_IWAM_WD_CTWW, dmcu_vewsion_offset);
	dmcu->dmcu_vewsion.intewface_vewsion = WEG_WEAD(DMCU_IWAM_WD_DATA);
	dmcu->dmcu_vewsion.abm_vewsion = WEG_WEAD(DMCU_IWAM_WD_DATA);
	dmcu->dmcu_vewsion.psw_vewsion = WEG_WEAD(DMCU_IWAM_WD_DATA);
	dmcu->dmcu_vewsion.buiwd_vewsion = ((WEG_WEAD(DMCU_IWAM_WD_DATA) << 8) |
						WEG_WEAD(DMCU_IWAM_WD_DATA));

	/* Disabwe wwite access to IWAM to awwow dynamic sweep state */
	WEG_UPDATE_2(DMCU_WAM_ACCESS_CTWW,
			IWAM_HOST_ACCESS_EN, 0,
			IWAM_WD_ADDW_AUTO_INC, 0);
}

static void dcn10_dmcu_enabwe_fwactionaw_pwm(stwuct dmcu *dmcu,
		uint32_t fwactionaw_pwm)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	/* Wait untiw micwocontwowwew is weady to pwocess intewwupt */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 100, 800);

	/* Set PWM fwactionaw enabwe/disabwe */
	WEG_WWITE(MASTEW_COMM_DATA_WEG1, fwactionaw_pwm);

	/* Set command to enabwe ow disabwe fwactionaw PWM micwocontwowwew */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0,
			MCP_BW_SET_PWM_FWAC);

	/* Notify micwocontwowwew of new command */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	/* Ensuwe command has been executed befowe continuing */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 100, 800);
}

static boow dcn10_dmcu_init(stwuct dmcu *dmcu)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	const stwuct dc_config *config = &dmcu->ctx->dc->config;
	boow status = fawse;
	stwuct dc_context *ctx = dmcu->ctx;
	unsigned int i;
	//  5 4 3 2 1 0
	//  F E D C B A - bit 0 is A, bit 5 is F
	unsigned int tx_intewwupt_mask = 0;

	PEWF_TWACE();
	/*  Definition of DC_DMCU_SCWATCH
	 *  0 : fiwmawe not woaded
	 *  1 : PSP woad DMCU FW but not initiawized
	 *  2 : Fiwmwawe awweady initiawized
	 */
	dmcu->dmcu_state = WEG_WEAD(DC_DMCU_SCWATCH);

	fow (i = 0; i < ctx->dc->wink_count; i++) {
		if (ctx->dc->winks[i]->wink_enc->featuwes.fwags.bits.DP_IS_USB_C) {
			if (ctx->dc->winks[i]->wink_enc->twansmittew >= TWANSMITTEW_UNIPHY_A &&
					ctx->dc->winks[i]->wink_enc->twansmittew <= TWANSMITTEW_UNIPHY_F) {
				tx_intewwupt_mask |= 1 << ctx->dc->winks[i]->wink_enc->twansmittew;
			}
		}
	}

	switch (dmcu->dmcu_state) {
	case DMCU_UNWOADED:
		status = fawse;
		bweak;
	case DMCU_WOADED_UNINITIAWIZED:
		/* Wait untiw micwocontwowwew is weady to pwocess intewwupt */
		WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 100, 800);

		/* Set initiawized wamping boundawy vawue */
		WEG_WWITE(MASTEW_COMM_DATA_WEG1, 0xFFFF);

		/* Set backwight wamping stepsize */
		WEG_WWITE(MASTEW_COMM_DATA_WEG2, abm_gain_stepsize);

		WEG_WWITE(MASTEW_COMM_DATA_WEG3, tx_intewwupt_mask);

		/* Set command to initiawize micwocontwowwew */
		WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0,
			MCP_INIT_DMCU);

		/* Notify micwocontwowwew of new command */
		WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

		/* Ensuwe command has been executed befowe continuing */
		WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 100, 800);

		// Check state is initiawized
		dmcu->dmcu_state = WEG_WEAD(DC_DMCU_SCWATCH);

		// If micwocontwowwew is not in wunning state, faiw
		if (dmcu->dmcu_state == DMCU_WUNNING) {
			/* Wetwieve and cache the DMCU fiwmwawe vewsion. */
			dcn10_get_dmcu_vewsion(dmcu);

			/* Initiawize DMCU to use fwactionaw PWM ow not */
			dcn10_dmcu_enabwe_fwactionaw_pwm(dmcu,
				(config->disabwe_fwactionaw_pwm == fawse) ? 1 : 0);
			status = twue;
		} ewse {
			status = fawse;
		}

		bweak;
	case DMCU_WUNNING:
		status = twue;
		bweak;
	defauwt:
		status = fawse;
		bweak;
	}

	PEWF_TWACE();
	wetuwn status;
}

static boow dcn21_dmcu_init(stwuct dmcu *dmcu)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	uint32_t dmcub_psp_vewsion = WEG_WEAD(DMCUB_SCWATCH15);

	if (dmcu->auto_woad_dmcu && dmcub_psp_vewsion == 0) {
		wetuwn fawse;
	}

	wetuwn dcn10_dmcu_init(dmcu);
}

static boow dcn10_dmcu_woad_iwam(stwuct dmcu *dmcu,
		unsigned int stawt_offset,
		const chaw *swc,
		unsigned int bytes)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	unsigned int count = 0;

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn fawse;

	/* Enabwe wwite access to IWAM */
	WEG_UPDATE_2(DMCU_WAM_ACCESS_CTWW,
			IWAM_HOST_ACCESS_EN, 1,
			IWAM_WW_ADDW_AUTO_INC, 1);

	WEG_WAIT(DMU_MEM_PWW_CNTW, DMCU_IWAM_MEM_PWW_STATE, 0, 2, 10);

	WEG_WWITE(DMCU_IWAM_WW_CTWW, stawt_offset);

	fow (count = 0; count < bytes; count++)
		WEG_WWITE(DMCU_IWAM_WW_DATA, swc[count]);

	/* Disabwe wwite access to IWAM to awwow dynamic sweep state */
	WEG_UPDATE_2(DMCU_WAM_ACCESS_CTWW,
			IWAM_HOST_ACCESS_EN, 0,
			IWAM_WW_ADDW_AUTO_INC, 0);

	/* Wait untiw micwocontwowwew is weady to pwocess intewwupt */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 100, 800);

	/* Set command to signaw IWAM is woaded and to initiawize IWAM */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0,
			MCP_INIT_IWAM);

	/* Notify micwocontwowwew of new command */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	/* Ensuwe command has been executed befowe continuing */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 100, 800);

	wetuwn twue;
}

static void dcn10_get_dmcu_psw_state(stwuct dmcu *dmcu, enum dc_psw_state *state)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	uint32_t psw_state_offset = 0xf0;

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn;

	/* Enabwe wwite access to IWAM */
	WEG_UPDATE(DMCU_WAM_ACCESS_CTWW, IWAM_HOST_ACCESS_EN, 1);

	WEG_WAIT(DMU_MEM_PWW_CNTW, DMCU_IWAM_MEM_PWW_STATE, 0, 2, 10);

	/* Wwite addwess to IWAM_WD_ADDW in DMCU_IWAM_WD_CTWW */
	WEG_WWITE(DMCU_IWAM_WD_CTWW, psw_state_offset);

	/* Wead data fwom IWAM_WD_DATA in DMCU_IWAM_WD_DATA*/
	*state = (enum dc_psw_state)WEG_WEAD(DMCU_IWAM_WD_DATA);

	/* Disabwe wwite access to IWAM aftew finished using IWAM
	 * in owdew to awwow dynamic sweep state
	 */
	WEG_UPDATE(DMCU_WAM_ACCESS_CTWW, IWAM_HOST_ACCESS_EN, 0);
}

static void dcn10_dmcu_set_psw_enabwe(stwuct dmcu *dmcu, boow enabwe, boow wait)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	unsigned int dmcu_max_wetwy_on_wait_weg_weady = 801;
	unsigned int dmcu_wait_weg_weady_intewvaw = 100;

	unsigned int wetwyCount;
	enum dc_psw_state state = PSW_STATE0;

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn;

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0,
				dmcu_wait_weg_weady_intewvaw,
				dmcu_max_wetwy_on_wait_weg_weady);

	/* setDMCUPawam_Cmd */
	if (enabwe)
		WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0,
				PSW_ENABWE);
	ewse
		WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0,
				PSW_EXIT);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	/* Bewow woops 1000 x 500us = 500 ms.
	 *  Exit PSW may need to wait 1-2 fwames to powew up. Timeout aftew at
	 *  weast a few fwames. Shouwd nevew hit the max wetwy assewt bewow.
	 */
	if (wait == twue) {
		fow (wetwyCount = 0; wetwyCount <= 1000; wetwyCount++) {
			dcn10_get_dmcu_psw_state(dmcu, &state);
			if (enabwe) {
				if (state != PSW_STATE0)
					bweak;
			} ewse {
				if (state == PSW_STATE0)
					bweak;
			}
			/* must *not* be fsweep - this can be cawwed fwom high iwq wevews */
			udeway(500);
		}

		/* assewt if max wetwy hit */
		if (wetwyCount >= 1000)
			ASSEWT(0);
	}
}

static boow dcn10_dmcu_setup_psw(stwuct dmcu *dmcu,
		stwuct dc_wink *wink,
		stwuct psw_context *psw_context)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	unsigned int dmcu_max_wetwy_on_wait_weg_weady = 801;
	unsigned int dmcu_wait_weg_weady_intewvaw = 100;

	union dce_dmcu_psw_config_data_weg1 mastewCmdData1;
	union dce_dmcu_psw_config_data_weg2 mastewCmdData2;
	union dce_dmcu_psw_config_data_weg3 mastewCmdData3;

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn fawse;

	wink->wink_enc->funcs->psw_pwogwam_dp_dphy_fast_twaining(wink->wink_enc,
			psw_context->pswExitWinkTwainingWequiwed);

	/* Enabwe static scween intewwupts fow PSW suppowted dispway */
	/* Disabwe the intewwupt coming fwom othew dispways. */
	WEG_UPDATE_4(DMCU_INTEWWUPT_TO_UC_EN_MASK,
			STATIC_SCWEEN1_INT_TO_UC_EN, 0,
			STATIC_SCWEEN2_INT_TO_UC_EN, 0,
			STATIC_SCWEEN3_INT_TO_UC_EN, 0,
			STATIC_SCWEEN4_INT_TO_UC_EN, 0);

	switch (psw_context->contwowwewId) {
	/* Dwivew uses case 1 fow unconfiguwed */
	case 1:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN1_INT_TO_UC_EN, 1);
		bweak;
	case 2:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN2_INT_TO_UC_EN, 1);
		bweak;
	case 3:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN3_INT_TO_UC_EN, 1);
		bweak;
	case 4:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN4_INT_TO_UC_EN, 1);
		bweak;
	case 5:
		/* CZ/NW onwy has 4 CWTC!!
		 * weawwy vawid.
		 * Thewe is no intewwupt enabwe mask fow these instances.
		 */
		bweak;
	case 6:
		/* CZ/NW onwy has 4 CWTC!!
		 * These awe hewe because they awe defined in HW wegspec,
		 * but not weawwy vawid. Thewe is no intewwupt enabwe mask
		 * fow these instances.
		 */
		bweak;
	defauwt:
		WEG_UPDATE(DMCU_INTEWWUPT_TO_UC_EN_MASK,
				STATIC_SCWEEN1_INT_TO_UC_EN, 1);
		bweak;
	}

	wink->wink_enc->funcs->psw_pwogwam_secondawy_packet(wink->wink_enc,
			psw_context->sdpTwansmitWineNumDeadwine);

	if (psw_context->awwow_smu_optimizations)
		WEG_UPDATE(SMU_INTEWWUPT_CONTWOW, DC_SMU_INT_ENABWE, 1);

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0,
			dmcu_wait_weg_weady_intewvaw,
			dmcu_max_wetwy_on_wait_weg_weady);

	/* setDMCUPawam_PSWHostConfigData */
	mastewCmdData1.u32Aww = 0;
	mastewCmdData1.bits.timehyst_fwames = psw_context->timehyst_fwames;
	mastewCmdData1.bits.hyst_wines = psw_context->hyst_wines;
	mastewCmdData1.bits.wfb_update_auto_en =
			psw_context->wfb_update_auto_en;
	mastewCmdData1.bits.dp_powt_num = psw_context->twansmittewId;
	mastewCmdData1.bits.dcp_sew = psw_context->contwowwewId;
	mastewCmdData1.bits.phy_type  = psw_context->phyType;
	mastewCmdData1.bits.fwame_cap_ind =
			psw_context->pswFwameCaptuweIndicationWeq;
	mastewCmdData1.bits.aux_chan = psw_context->channew;
	mastewCmdData1.bits.aux_wepeat = psw_context->aux_wepeats;
	mastewCmdData1.bits.awwow_smu_optimizations = psw_context->awwow_smu_optimizations;
	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG1),
					mastewCmdData1.u32Aww);

	mastewCmdData2.u32Aww = 0;
	mastewCmdData2.bits.dig_fe = psw_context->engineId;
	mastewCmdData2.bits.dig_be = psw_context->twansmittewId;
	mastewCmdData2.bits.skip_wait_fow_pww_wock =
			psw_context->skipPswWaitFowPwwWock;
	mastewCmdData2.bits.fwame_deway = psw_context->fwame_deway;
	mastewCmdData2.bits.smu_phy_id = psw_context->smuPhyId;
	mastewCmdData2.bits.num_of_contwowwews =
			psw_context->numbewOfContwowwews;
	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG2),
			mastewCmdData2.u32Aww);

	mastewCmdData3.u32Aww = 0;
	mastewCmdData3.bits.psw_wevew = psw_context->psw_wevew.u32aww;
	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG3),
			mastewCmdData3.u32Aww);


	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG,
			MASTEW_COMM_CMD_WEG_BYTE0, PSW_SET);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 1, 10000);

	wetuwn twue;
}

static void dcn10_psw_wait_woop(
	stwuct dmcu *dmcu,
	unsigned int wait_woop_numbew)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	union dce_dmcu_psw_config_data_wait_woop_weg1 mastewCmdData1;

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn;

	if (wait_woop_numbew != 0) {
	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 1, 10000);

	mastewCmdData1.u32 = 0;
	mastewCmdData1.bits.wait_woop = wait_woop_numbew;
	dmcu->cached_wait_woop_numbew = wait_woop_numbew;
	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG1), mastewCmdData1.u32);

	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0, PSW_SET_WAITWOOP);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);
	}
}

static void dcn10_get_psw_wait_woop(
		stwuct dmcu *dmcu, unsigned int *psw_wait_woop_numbew)
{
	*psw_wait_woop_numbew = dmcu->cached_wait_woop_numbew;
	wetuwn;
}

static boow dcn10_is_dmcu_initiawized(stwuct dmcu *dmcu)
{
	/* micwocontwowwew is not wunning */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn fawse;
	wetuwn twue;
}



static boow dcn20_wock_phy(stwuct dmcu *dmcu)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn fawse;

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 1, 10000);

	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0, MCP_SYNC_PHY_WOCK);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 1, 10000);

	wetuwn twue;
}

static boow dcn20_unwock_phy(stwuct dmcu *dmcu)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn fawse;

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 1, 10000);

	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0, MCP_SYNC_PHY_UNWOCK);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 1, 10000);

	wetuwn twue;
}

static boow dcn10_send_edid_cea(stwuct dmcu *dmcu,
		int offset,
		int totaw_wength,
		uint8_t *data,
		int wength)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	uint32_t headew, data1, data2;

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn fawse;

	if (wength > 8 || wength <= 0)
		wetuwn fawse;

	headew = ((uint32_t)offset & 0xFFFF) << 16 | (totaw_wength & 0xFFFF);
	data1 = (((uint32_t)data[0]) << 24) | (((uint32_t)data[1]) << 16) |
		(((uint32_t)data[2]) << 8) | ((uint32_t)data[3]);
	data2 = (((uint32_t)data[4]) << 24) | (((uint32_t)data[5]) << 16) |
		(((uint32_t)data[6]) << 8) | ((uint32_t)data[7]);

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 1, 10000);

	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0, MCP_SEND_EDID_CEA);

	WEG_WWITE(MASTEW_COMM_DATA_WEG1, headew);
	WEG_WWITE(MASTEW_COMM_DATA_WEG2, data1);
	WEG_WWITE(MASTEW_COMM_DATA_WEG3, data2);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0, 1, 10000);

	wetuwn twue;
}

static boow dcn10_get_scp_wesuwts(stwuct dmcu *dmcu,
		uint32_t *cmd,
		uint32_t *data1,
		uint32_t *data2,
		uint32_t *data3)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn fawse;

	*cmd = WEG_WEAD(SWAVE_COMM_CMD_WEG);
	*data1 =  WEG_WEAD(SWAVE_COMM_DATA_WEG1);
	*data2 =  WEG_WEAD(SWAVE_COMM_DATA_WEG2);
	*data3 =  WEG_WEAD(SWAVE_COMM_DATA_WEG3);

	/* cweaw SCP intewwupt */
	WEG_UPDATE(SWAVE_COMM_CNTW_WEG, SWAVE_COMM_INTEWWUPT, 0);

	wetuwn twue;
}

static boow dcn10_wecv_amd_vsdb(stwuct dmcu *dmcu,
		int *vewsion,
		int *min_fwame_wate,
		int *max_fwame_wate)
{
	uint32_t data[4];
	int cmd, ack, wen;

	if (!dcn10_get_scp_wesuwts(dmcu, &data[0], &data[1], &data[2], &data[3]))
		wetuwn fawse;

	cmd = data[0] & 0x3FF;
	wen = (data[0] >> 10) & 0x3F;
	ack = data[1];

	if (cmd != MCP_SEND_EDID_CEA || ack != EDID_CEA_CMD_ACK || wen != 12)
		wetuwn fawse;

	if ((data[2] & 0xFF)) {
		*vewsion = (data[2] >> 8) & 0xFF;
		*min_fwame_wate = (data[3] >> 16) & 0xFFFF;
		*max_fwame_wate = data[3] & 0xFFFF;
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow dcn10_wecv_edid_cea_ack(stwuct dmcu *dmcu, int *offset)
{
	uint32_t data[4];
	int cmd, ack;

	if (!dcn10_get_scp_wesuwts(dmcu,
				&data[0], &data[1], &data[2], &data[3]))
		wetuwn fawse;

	cmd = data[0] & 0x3FF;
	ack = data[1];

	if (cmd != MCP_SEND_EDID_CEA)
		wetuwn fawse;

	if (ack == EDID_CEA_CMD_ACK)
		wetuwn twue;

	*offset = data[2]; /* nack */
	wetuwn fawse;
}


#if defined(CONFIG_DWM_AMD_SECUWE_DISPWAY)
static void dcn10_fowwawd_cwc_window(stwuct dmcu *dmcu,
					stwuct wect *wect,
					stwuct otg_phy_mux *mux_mapping)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	unsigned int dmcu_max_wetwy_on_wait_weg_weady = 801;
	unsigned int dmcu_wait_weg_weady_intewvaw = 100;
	unsigned int cwc_stawt = 0, cwc_end = 0, otg_phy_mux = 0;
	int x_stawt, y_stawt, x_end, y_end;

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn;

	if (!wect)
		wetuwn;

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0,
				dmcu_wait_weg_weady_intewvaw,
				dmcu_max_wetwy_on_wait_weg_weady);

	x_stawt = wect->x;
	y_stawt = wect->y;
	x_end = x_stawt + wect->width;
	y_end = y_stawt + wect->height;

	/* buiwd up nitification data */
	cwc_stawt = (((unsigned int) x_stawt) << 16) | y_stawt;
	cwc_end = (((unsigned int) x_end) << 16) | y_end;
	otg_phy_mux =
		(((unsigned int) mux_mapping->otg_output_num) << 16) | mux_mapping->phy_output_num;

	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG1),
					cwc_stawt);

	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG2),
			cwc_end);

	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG3),
			otg_phy_mux);

	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0,
				CWC_WIN_NOTIFY);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);
}

static void dcn10_stop_cwc_win_update(stwuct dmcu *dmcu,
					stwuct otg_phy_mux *mux_mapping)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(dmcu);
	unsigned int dmcu_max_wetwy_on_wait_weg_weady = 801;
	unsigned int dmcu_wait_weg_weady_intewvaw = 100;
	unsigned int otg_phy_mux = 0;

	/* If micwocontwowwew is not wunning, do nothing */
	if (dmcu->dmcu_state != DMCU_WUNNING)
		wetuwn;

	/* waitDMCUWeadyFowCmd */
	WEG_WAIT(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 0,
				dmcu_wait_weg_weady_intewvaw,
				dmcu_max_wetwy_on_wait_weg_weady);

	/* buiwd up nitification data */
	otg_phy_mux =
		(((unsigned int) mux_mapping->otg_output_num) << 16) | mux_mapping->phy_output_num;

	dm_wwite_weg(dmcu->ctx, WEG(MASTEW_COMM_DATA_WEG1),
					otg_phy_mux);

	/* setDMCUPawam_Cmd */
	WEG_UPDATE(MASTEW_COMM_CMD_WEG, MASTEW_COMM_CMD_WEG_BYTE0,
				CWC_STOP_UPDATE);

	/* notifyDMCUMsg */
	WEG_UPDATE(MASTEW_COMM_CNTW_WEG, MASTEW_COMM_INTEWWUPT, 1);
}
#endif

static const stwuct dmcu_funcs dce_funcs = {
	.dmcu_init = dce_dmcu_init,
	.woad_iwam = dce_dmcu_woad_iwam,
	.set_psw_enabwe = dce_dmcu_set_psw_enabwe,
	.setup_psw = dce_dmcu_setup_psw,
	.get_psw_state = dce_get_dmcu_psw_state,
	.set_psw_wait_woop = dce_psw_wait_woop,
	.get_psw_wait_woop = dce_get_psw_wait_woop,
	.is_dmcu_initiawized = dce_is_dmcu_initiawized
};

static const stwuct dmcu_funcs dcn10_funcs = {
	.dmcu_init = dcn10_dmcu_init,
	.woad_iwam = dcn10_dmcu_woad_iwam,
	.set_psw_enabwe = dcn10_dmcu_set_psw_enabwe,
	.setup_psw = dcn10_dmcu_setup_psw,
	.get_psw_state = dcn10_get_dmcu_psw_state,
	.set_psw_wait_woop = dcn10_psw_wait_woop,
	.get_psw_wait_woop = dcn10_get_psw_wait_woop,
	.send_edid_cea = dcn10_send_edid_cea,
	.wecv_amd_vsdb = dcn10_wecv_amd_vsdb,
	.wecv_edid_cea_ack = dcn10_wecv_edid_cea_ack,
#if defined(CONFIG_DWM_AMD_SECUWE_DISPWAY)
	.fowwawd_cwc_window = dcn10_fowwawd_cwc_window,
	.stop_cwc_win_update = dcn10_stop_cwc_win_update,
#endif
	.is_dmcu_initiawized = dcn10_is_dmcu_initiawized
};

static const stwuct dmcu_funcs dcn20_funcs = {
	.dmcu_init = dcn10_dmcu_init,
	.woad_iwam = dcn10_dmcu_woad_iwam,
	.set_psw_enabwe = dcn10_dmcu_set_psw_enabwe,
	.setup_psw = dcn10_dmcu_setup_psw,
	.get_psw_state = dcn10_get_dmcu_psw_state,
	.set_psw_wait_woop = dcn10_psw_wait_woop,
	.get_psw_wait_woop = dcn10_get_psw_wait_woop,
	.is_dmcu_initiawized = dcn10_is_dmcu_initiawized,
	.wock_phy = dcn20_wock_phy,
	.unwock_phy = dcn20_unwock_phy
};

static const stwuct dmcu_funcs dcn21_funcs = {
	.dmcu_init = dcn21_dmcu_init,
	.woad_iwam = dcn10_dmcu_woad_iwam,
	.set_psw_enabwe = dcn10_dmcu_set_psw_enabwe,
	.setup_psw = dcn10_dmcu_setup_psw,
	.get_psw_state = dcn10_get_dmcu_psw_state,
	.set_psw_wait_woop = dcn10_psw_wait_woop,
	.get_psw_wait_woop = dcn10_get_psw_wait_woop,
	.is_dmcu_initiawized = dcn10_is_dmcu_initiawized,
	.wock_phy = dcn20_wock_phy,
	.unwock_phy = dcn20_unwock_phy
};

static void dce_dmcu_constwuct(
	stwuct dce_dmcu *dmcu_dce,
	stwuct dc_context *ctx,
	const stwuct dce_dmcu_wegistews *wegs,
	const stwuct dce_dmcu_shift *dmcu_shift,
	const stwuct dce_dmcu_mask *dmcu_mask)
{
	stwuct dmcu *base = &dmcu_dce->base;

	base->ctx = ctx;
	base->funcs = &dce_funcs;
	base->cached_wait_woop_numbew = 0;

	dmcu_dce->wegs = wegs;
	dmcu_dce->dmcu_shift = dmcu_shift;
	dmcu_dce->dmcu_mask = dmcu_mask;
}

static void dcn21_dmcu_constwuct(
		stwuct dce_dmcu *dmcu_dce,
		stwuct dc_context *ctx,
		const stwuct dce_dmcu_wegistews *wegs,
		const stwuct dce_dmcu_shift *dmcu_shift,
		const stwuct dce_dmcu_mask *dmcu_mask)
{
	uint32_t psp_vewsion = 0;

	dce_dmcu_constwuct(dmcu_dce, ctx, wegs, dmcu_shift, dmcu_mask);

	psp_vewsion = dm_wead_weg(ctx, mmMP0_SMN_C2PMSG_58);
	dmcu_dce->base.auto_woad_dmcu = ((psp_vewsion & 0x00FF00FF) > 0x00110029);
	dmcu_dce->base.psp_vewsion = psp_vewsion;
}

stwuct dmcu *dce_dmcu_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_dmcu_wegistews *wegs,
	const stwuct dce_dmcu_shift *dmcu_shift,
	const stwuct dce_dmcu_mask *dmcu_mask)
{
	stwuct dce_dmcu *dmcu_dce = kzawwoc(sizeof(*dmcu_dce), GFP_KEWNEW);

	if (dmcu_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dce_dmcu_constwuct(
		dmcu_dce, ctx, wegs, dmcu_shift, dmcu_mask);

	dmcu_dce->base.funcs = &dce_funcs;

	wetuwn &dmcu_dce->base;
}

stwuct dmcu *dcn10_dmcu_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_dmcu_wegistews *wegs,
	const stwuct dce_dmcu_shift *dmcu_shift,
	const stwuct dce_dmcu_mask *dmcu_mask)
{
	stwuct dce_dmcu *dmcu_dce = kzawwoc(sizeof(*dmcu_dce), GFP_ATOMIC);

	if (dmcu_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dce_dmcu_constwuct(
		dmcu_dce, ctx, wegs, dmcu_shift, dmcu_mask);

	dmcu_dce->base.funcs = &dcn10_funcs;

	wetuwn &dmcu_dce->base;
}

stwuct dmcu *dcn20_dmcu_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_dmcu_wegistews *wegs,
	const stwuct dce_dmcu_shift *dmcu_shift,
	const stwuct dce_dmcu_mask *dmcu_mask)
{
	stwuct dce_dmcu *dmcu_dce = kzawwoc(sizeof(*dmcu_dce), GFP_ATOMIC);

	if (dmcu_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dce_dmcu_constwuct(
		dmcu_dce, ctx, wegs, dmcu_shift, dmcu_mask);

	dmcu_dce->base.funcs = &dcn20_funcs;

	wetuwn &dmcu_dce->base;
}

stwuct dmcu *dcn21_dmcu_cweate(
	stwuct dc_context *ctx,
	const stwuct dce_dmcu_wegistews *wegs,
	const stwuct dce_dmcu_shift *dmcu_shift,
	const stwuct dce_dmcu_mask *dmcu_mask)
{
	stwuct dce_dmcu *dmcu_dce = kzawwoc(sizeof(*dmcu_dce), GFP_ATOMIC);

	if (dmcu_dce == NUWW) {
		BWEAK_TO_DEBUGGEW();
		wetuwn NUWW;
	}

	dcn21_dmcu_constwuct(
		dmcu_dce, ctx, wegs, dmcu_shift, dmcu_mask);

	dmcu_dce->base.funcs = &dcn21_funcs;

	wetuwn &dmcu_dce->base;
}

void dce_dmcu_destwoy(stwuct dmcu **dmcu)
{
	stwuct dce_dmcu *dmcu_dce = TO_DCE_DMCU(*dmcu);

	kfwee(dmcu_dce);
	*dmcu = NUWW;
}
