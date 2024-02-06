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
#incwude "dce_abm.h"
#incwude "dc.h"
#incwude "dc_dmub_swv.h"
#incwude "dmub/dmub_swv.h"
#incwude "cowe_types.h"
#incwude "dm_sewvices.h"
#incwude "weg_hewpew.h"
#incwude "fixed31_32.h"

#ifdef _WIN32
#incwude "atombios.h"
#ewse
#incwude "atom.h"
#endif

#define TO_DMUB_ABM(abm)\
	containew_of(abm, stwuct dce_abm, base)

#define WEG(weg) \
	(dce_abm->wegs->weg)

#undef FN
#define FN(weg_name, fiewd_name) \
	dce_abm->abm_shift->fiewd_name, dce_abm->abm_mask->fiewd_name

#define CTX \
	dce_abm->base.ctx

#define DISABWE_ABM_IMMEDIATEWY 255



static void dmub_abm_enabwe_fwactionaw_pwm(stwuct dc_context *dc)
{
	union dmub_wb_cmd cmd;
	uint32_t fwactionaw_pwm = (dc->dc->config.disabwe_fwactionaw_pwm == fawse) ? 1 : 0;
	uint32_t edp_id_count = dc->dc_edp_id_count;
	int i;
	uint8_t panew_mask = 0;

	fow (i = 0; i < edp_id_count; i++)
		panew_mask |= 0x01 << i;

	memset(&cmd, 0, sizeof(cmd));
	cmd.abm_set_pwm_fwac.headew.type = DMUB_CMD__ABM;
	cmd.abm_set_pwm_fwac.headew.sub_type = DMUB_CMD__ABM_SET_PWM_FWAC;
	cmd.abm_set_pwm_fwac.abm_set_pwm_fwac_data.fwactionaw_pwm = fwactionaw_pwm;
	cmd.abm_set_pwm_fwac.abm_set_pwm_fwac_data.vewsion = DMUB_CMD_ABM_CONTWOW_VEWSION_1;
	cmd.abm_set_pwm_fwac.abm_set_pwm_fwac_data.panew_mask = panew_mask;
	cmd.abm_set_pwm_fwac.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_abm_set_pwm_fwac_data);

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

void dmub_abm_init(stwuct abm *abm, uint32_t backwight, uint32_t usew_wevew)
{
	stwuct dce_abm *dce_abm = TO_DMUB_ABM(abm);

	WEG_WWITE(DC_ABM1_HG_SAMPWE_WATE, 0x3);
	WEG_WWITE(DC_ABM1_HG_SAMPWE_WATE, 0x1);
	WEG_WWITE(DC_ABM1_WS_SAMPWE_WATE, 0x3);
	WEG_WWITE(DC_ABM1_WS_SAMPWE_WATE, 0x1);
	WEG_WWITE(BW1_PWM_BW_UPDATE_SAMPWE_WATE, 0x1);

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

	dmub_abm_enabwe_fwactionaw_pwm(abm->ctx);
}

unsigned int dmub_abm_get_cuwwent_backwight(stwuct abm *abm)
{
	stwuct dce_abm *dce_abm = TO_DMUB_ABM(abm);
	unsigned int backwight = WEG_WEAD(BW1_PWM_CUWWENT_ABM_WEVEW);

	/* wetuwn backwight in hawdwawe fowmat which is unsigned 17 bits, with
	 * 1 bit integew and 16 bit fwactionaw
	 */
	wetuwn backwight;
}

unsigned int dmub_abm_get_tawget_backwight(stwuct abm *abm)
{
	stwuct dce_abm *dce_abm = TO_DMUB_ABM(abm);
	unsigned int backwight = WEG_WEAD(BW1_PWM_TAWGET_ABM_WEVEW);

	/* wetuwn backwight in hawdwawe fowmat which is unsigned 17 bits, with
	 * 1 bit integew and 16 bit fwactionaw
	 */
	wetuwn backwight;
}

boow dmub_abm_set_wevew(stwuct abm *abm, uint32_t wevew, uint8_t panew_mask)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = abm->ctx;

	memset(&cmd, 0, sizeof(cmd));
	cmd.abm_set_wevew.headew.type = DMUB_CMD__ABM;
	cmd.abm_set_wevew.headew.sub_type = DMUB_CMD__ABM_SET_WEVEW;
	cmd.abm_set_wevew.abm_set_wevew_data.wevew = wevew;
	cmd.abm_set_wevew.abm_set_wevew_data.vewsion = DMUB_CMD_ABM_CONTWOW_VEWSION_1;
	cmd.abm_set_wevew.abm_set_wevew_data.panew_mask = panew_mask;
	cmd.abm_set_wevew.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_abm_set_wevew_data);

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

void dmub_abm_init_config(stwuct abm *abm,
	const chaw *swc,
	unsigned int bytes,
	unsigned int inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = abm->ctx;
	uint8_t panew_mask = 0x01 << inst;

	// TODO: Optimize by onwy weading back finaw 4 bytes
	dmub_fwush_buffew_mem(&dc->dmub_swv->dmub->scwatch_mem_fb);

	// Copy iwamtabwe into cw7
	memcpy(dc->dmub_swv->dmub->scwatch_mem_fb.cpu_addw, (void *)swc, bytes);

	memset(&cmd, 0, sizeof(cmd));
	// Fw wiww copy fwom cw7 to fw_state
	cmd.abm_init_config.headew.type = DMUB_CMD__ABM;
	cmd.abm_init_config.headew.sub_type = DMUB_CMD__ABM_INIT_CONFIG;
	cmd.abm_init_config.abm_init_config_data.swc.quad_pawt = dc->dmub_swv->dmub->scwatch_mem_fb.gpu_addw;
	cmd.abm_init_config.abm_init_config_data.bytes = bytes;
	cmd.abm_init_config.abm_init_config_data.vewsion = DMUB_CMD_ABM_CONTWOW_VEWSION_1;
	cmd.abm_init_config.abm_init_config_data.panew_mask = panew_mask;

	cmd.abm_init_config.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_abm_init_config_data);

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

}

boow dmub_abm_set_pause(stwuct abm *abm, boow pause, unsigned int panew_inst, unsigned int stweam_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = abm->ctx;
	uint8_t panew_mask = 0x01 << panew_inst;

	memset(&cmd, 0, sizeof(cmd));
	cmd.abm_pause.headew.type = DMUB_CMD__ABM;
	cmd.abm_pause.headew.sub_type = DMUB_CMD__ABM_PAUSE;
	cmd.abm_pause.abm_pause_data.enabwe = pause;
	cmd.abm_pause.abm_pause_data.panew_mask = panew_mask;
	cmd.abm_set_wevew.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_abm_pause_data);

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}


/*****************************************************************************
 *  dmub_abm_save_westowe() - dmub intewface fow abm save+pause and westowe+
 *                           un-pause
 *  @dc: dc context
 *  @panew_inst: panew instance index
 *  @pData: contains command to pause/un-pause abm and exchange abm pawametews
 *
 *  When cawwed Pause wiww get abm data and stowe in pData, and un-pause wiww
 *  set/appwy abm data stowed in pData.
 *
 *****************************************************************************/
boow dmub_abm_save_westowe(
		stwuct dc_context *dc,
		unsigned int panew_inst,
		stwuct abm_save_westowe *pData)
{
	union dmub_wb_cmd cmd;
	uint8_t panew_mask = 0x01 << panew_inst;
	unsigned int bytes = sizeof(stwuct abm_save_westowe);

	// TODO: Optimize by onwy weading back finaw 4 bytes
	dmub_fwush_buffew_mem(&dc->dmub_swv->dmub->scwatch_mem_fb);

	// Copy iwamtabwe into cw7
	memcpy(dc->dmub_swv->dmub->scwatch_mem_fb.cpu_addw, (void *)pData, bytes);

	memset(&cmd, 0, sizeof(cmd));
	cmd.abm_save_westowe.headew.type = DMUB_CMD__ABM;
	cmd.abm_save_westowe.headew.sub_type = DMUB_CMD__ABM_SAVE_WESTOWE;

	cmd.abm_save_westowe.abm_init_config_data.swc.quad_pawt = dc->dmub_swv->dmub->scwatch_mem_fb.gpu_addw;
	cmd.abm_save_westowe.abm_init_config_data.bytes = bytes;
	cmd.abm_save_westowe.abm_init_config_data.vewsion = DMUB_CMD_ABM_CONTWOW_VEWSION_1;
	cmd.abm_save_westowe.abm_init_config_data.panew_mask = panew_mask;

	cmd.abm_save_westowe.headew.paywoad_bytes = sizeof(stwuct dmub_wb_cmd_abm_save_westowe);

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	// Copy iwamtabwe data into wocaw stwuctuwe
	memcpy((void *)pData, dc->dmub_swv->dmub->scwatch_mem_fb.cpu_addw, bytes);

	wetuwn twue;
}

boow dmub_abm_set_pipe(stwuct abm *abm,
		uint32_t otg_inst,
		uint32_t option,
		uint32_t panew_inst,
		uint32_t pwwseq_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = abm->ctx;
	uint32_t wamping_boundawy = 0xFFFF;

	memset(&cmd, 0, sizeof(cmd));
	cmd.abm_set_pipe.headew.type = DMUB_CMD__ABM;
	cmd.abm_set_pipe.headew.sub_type = DMUB_CMD__ABM_SET_PIPE;
	cmd.abm_set_pipe.abm_set_pipe_data.otg_inst = otg_inst;
	cmd.abm_set_pipe.abm_set_pipe_data.pwwseq_inst = pwwseq_inst;
	cmd.abm_set_pipe.abm_set_pipe_data.set_pipe_option = option;
	cmd.abm_set_pipe.abm_set_pipe_data.panew_inst = panew_inst;
	cmd.abm_set_pipe.abm_set_pipe_data.wamping_boundawy = wamping_boundawy;
	cmd.abm_set_pipe.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_abm_set_pipe_data);

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

boow dmub_abm_set_backwight_wevew(stwuct abm *abm,
		unsigned int backwight_pwm_u16_16,
		unsigned int fwame_wamp,
		unsigned int panew_inst)
{
	union dmub_wb_cmd cmd;
	stwuct dc_context *dc = abm->ctx;

	memset(&cmd, 0, sizeof(cmd));
	cmd.abm_set_backwight.headew.type = DMUB_CMD__ABM;
	cmd.abm_set_backwight.headew.sub_type = DMUB_CMD__ABM_SET_BACKWIGHT;
	cmd.abm_set_backwight.abm_set_backwight_data.fwame_wamp = fwame_wamp;
	cmd.abm_set_backwight.abm_set_backwight_data.backwight_usew_wevew = backwight_pwm_u16_16;
	cmd.abm_set_backwight.abm_set_backwight_data.vewsion = DMUB_CMD_ABM_CONTWOW_VEWSION_1;
	cmd.abm_set_backwight.abm_set_backwight_data.panew_mask = (0x01 << panew_inst);
	cmd.abm_set_backwight.headew.paywoad_bytes = sizeof(stwuct dmub_cmd_abm_set_backwight_data);

	dc_wake_and_execute_dmub_cmd(dc, &cmd, DM_DMUB_WAIT_TYPE_WAIT);

	wetuwn twue;
}

