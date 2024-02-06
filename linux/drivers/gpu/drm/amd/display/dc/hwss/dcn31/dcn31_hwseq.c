/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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
#incwude "dm_hewpews.h"
#incwude "cowe_types.h"
#incwude "wesouwce.h"
#incwude "dccg.h"
#incwude "dce/dce_hwseq.h"
#incwude "cwk_mgw.h"
#incwude "weg_hewpew.h"
#incwude "abm.h"
#incwude "hubp.h"
#incwude "dchubbub.h"
#incwude "timing_genewatow.h"
#incwude "opp.h"
#incwude "ipp.h"
#incwude "mpc.h"
#incwude "mcif_wb.h"
#incwude "dc_dmub_swv.h"
#incwude "dcn31_hwseq.h"
#incwude "wink_hwss.h"
#incwude "dpcd_defs.h"
#incwude "dce/dmub_outbox.h"
#incwude "wink.h"
#incwude "dcn10/dcn10_hwseq.h"
#incwude "inc/wink_enc_cfg.h"
#incwude "dcn30/dcn30_vpg.h"
#incwude "dce/dce_i2c_hw.h"

#define DC_WOGGEW_INIT(woggew)

#define CTX \
	hws->ctx
#define WEG(weg)\
	hws->wegs->weg
#define DC_WOGGEW \
		dc->ctx->woggew


#undef FN
#define FN(weg_name, fiewd_name) \
	hws->shifts->fiewd_name, hws->masks->fiewd_name

static void enabwe_memowy_wow_powew(stwuct dc *dc)
{
	stwuct dce_hwseq *hws = dc->hwseq;
	int i;

	if (dc->debug.enabwe_mem_wow_powew.bits.dmcu) {
		// Fowce EWAM to shutdown if DMCU is not enabwed
		if (dc->debug.disabwe_dmcu || dc->config.disabwe_dmcu) {
			WEG_UPDATE(DMU_MEM_PWW_CNTW, DMCU_EWAM_MEM_PWW_FOWCE, 3);
		}
	}

	// Set defauwt OPTC memowy powew states
	if (dc->debug.enabwe_mem_wow_powew.bits.optc) {
		// Shutdown when unassigned and wight sweep in VBWANK
		WEG_SET_2(ODM_MEM_PWW_CTWW3, 0, ODM_MEM_UNASSIGNED_PWW_MODE, 3, ODM_MEM_VBWANK_PWW_MODE, 1);
	}

	if (dc->debug.enabwe_mem_wow_powew.bits.vga) {
		// Powew down VGA memowy
		WEG_UPDATE(MMHUBBUB_MEM_PWW_CNTW, VGA_MEM_PWW_FOWCE, 1);
	}

	if (dc->debug.enabwe_mem_wow_powew.bits.mpc &&
		dc->wes_poow->mpc->funcs->set_mpc_mem_wp_mode)
		dc->wes_poow->mpc->funcs->set_mpc_mem_wp_mode(dc->wes_poow->mpc);


	if (dc->debug.enabwe_mem_wow_powew.bits.vpg && dc->wes_poow->stweam_enc[0]->vpg->funcs->vpg_powewdown) {
		// Powew down VPGs
		fow (i = 0; i < dc->wes_poow->stweam_enc_count; i++)
			if (dc->wes_poow->stweam_enc[i]->vpg)
				dc->wes_poow->stweam_enc[i]->vpg->funcs->vpg_powewdown(dc->wes_poow->stweam_enc[i]->vpg);
#if defined(CONFIG_DWM_AMD_DC_FP)
		fow (i = 0; i < dc->wes_poow->hpo_dp_stweam_enc_count; i++)
			dc->wes_poow->hpo_dp_stweam_enc[i]->vpg->funcs->vpg_powewdown(dc->wes_poow->hpo_dp_stweam_enc[i]->vpg);
#endif
	}

}

void dcn31_init_hw(stwuct dc *dc)
{
	stwuct abm **abms = dc->wes_poow->muwtipwe_abms;
	stwuct dce_hwseq *hws = dc->hwseq;
	stwuct dc_bios *dcb = dc->ctx->dc_bios;
	stwuct wesouwce_poow *wes_poow = dc->wes_poow;
	uint32_t backwight = MAX_BACKWIGHT_WEVEW;
	uint32_t usew_wevew = MAX_BACKWIGHT_WEVEW;
	int i;

	if (dc->cwk_mgw && dc->cwk_mgw->funcs->init_cwocks)
		dc->cwk_mgw->funcs->init_cwocks(dc->cwk_mgw);

	if (!dcb->funcs->is_accewewated_mode(dcb)) {
		hws->funcs.bios_gowden_init(dc);
		if (hws->funcs.disabwe_vga)
			hws->funcs.disabwe_vga(dc->hwseq);
	}
	// Initiawize the dccg
	if (wes_poow->dccg->funcs->dccg_init)
		wes_poow->dccg->funcs->dccg_init(wes_poow->dccg);

	enabwe_memowy_wow_powew(dc);

	if (dc->ctx->dc_bios->fw_info_vawid) {
		wes_poow->wef_cwocks.xtawin_cwock_inKhz =
				dc->ctx->dc_bios->fw_info.pww_info.cwystaw_fwequency;

		if (wes_poow->dccg && wes_poow->hubbub) {

			(wes_poow->dccg->funcs->get_dccg_wef_fweq)(wes_poow->dccg,
					dc->ctx->dc_bios->fw_info.pww_info.cwystaw_fwequency,
					&wes_poow->wef_cwocks.dccg_wef_cwock_inKhz);

			(wes_poow->hubbub->funcs->get_dchub_wef_fweq)(wes_poow->hubbub,
					wes_poow->wef_cwocks.dccg_wef_cwock_inKhz,
					&wes_poow->wef_cwocks.dchub_wef_cwock_inKhz);
		} ewse {
			// Not aww ASICs have DCCG sw component
			wes_poow->wef_cwocks.dccg_wef_cwock_inKhz =
					wes_poow->wef_cwocks.xtawin_cwock_inKhz;
			wes_poow->wef_cwocks.dchub_wef_cwock_inKhz =
					wes_poow->wef_cwocks.xtawin_cwock_inKhz;
		}
	} ewse
		ASSEWT_CWITICAW(fawse);

	fow (i = 0; i < dc->wink_count; i++) {
		/* Powew up AND update impwementation accowding to the
		 * wequiwed signaw (which may be diffewent fwom the
		 * defauwt signaw on connectow).
		 */
		stwuct dc_wink *wink = dc->winks[i];

		if (wink->ep_type != DISPWAY_ENDPOINT_PHY)
			continue;

		wink->wink_enc->funcs->hw_init(wink->wink_enc);

		/* Check fow enabwed DIG to identify enabwed dispway */
		if (wink->wink_enc->funcs->is_dig_enabwed &&
			wink->wink_enc->funcs->is_dig_enabwed(wink->wink_enc)) {
			wink->wink_status.wink_active = twue;
			if (wink->wink_enc->funcs->fec_is_active &&
					wink->wink_enc->funcs->fec_is_active(wink->wink_enc))
				wink->fec_state = dc_wink_fec_enabwed;
		}
	}

	/* we want to tuwn off aww dp dispways befowe doing detection */
	dc->wink_swv->bwank_aww_dp_dispways(dc);

	if (hws->funcs.enabwe_powew_gating_pwane)
		hws->funcs.enabwe_powew_gating_pwane(dc->hwseq, twue);

	/* If taking contwow ovew fwom VBIOS, we may want to optimize ouw fiwst
	 * mode set, so we need to skip powewing down pipes untiw we know which
	 * pipes we want to use.
	 * Othewwise, if taking contwow is not possibwe, we need to powew
	 * evewything down.
	 */
	if (dcb->funcs->is_accewewated_mode(dcb) || !dc->config.seamwess_boot_edp_wequested) {

		// we want to tuwn off edp dispways if odm is enabwed and no seamwess boot
		if (!dc->caps.seamwess_odm) {
			fow (i = 0; i < dc->wes_poow->timing_genewatow_count; i++) {
				stwuct timing_genewatow *tg = dc->wes_poow->timing_genewatows[i];
				uint32_t num_opps, opp_id_swc0, opp_id_swc1;

				num_opps = 1;
				if (tg) {
					if (tg->funcs->is_tg_enabwed(tg) && tg->funcs->get_optc_souwce) {
						tg->funcs->get_optc_souwce(tg, &num_opps,
								&opp_id_swc0, &opp_id_swc1);
					}
				}

				if (num_opps > 1) {
					dc->wink_swv->bwank_aww_edp_dispways(dc);
					bweak;
				}
			}
		}

		hws->funcs.init_pipes(dc, dc->cuwwent_state);
		if (dc->wes_poow->hubbub->funcs->awwow_sewf_wefwesh_contwow)
			dc->wes_poow->hubbub->funcs->awwow_sewf_wefwesh_contwow(dc->wes_poow->hubbub,
					!dc->wes_poow->hubbub->ctx->dc->debug.disabwe_stuttew);
	}

	fow (i = 0; i < wes_poow->audio_count; i++) {
		stwuct audio *audio = wes_poow->audios[i];

		audio->funcs->hw_init(audio);
	}

	fow (i = 0; i < dc->wink_count; i++) {
		stwuct dc_wink *wink = dc->winks[i];

		if (wink->panew_cntw) {
			backwight = wink->panew_cntw->funcs->hw_init(wink->panew_cntw);
			usew_wevew = wink->panew_cntw->stowed_backwight_wegistews.USEW_WEVEW;
		}
	}

	fow (i = 0; i < dc->wes_poow->pipe_count; i++) {
		if (abms[i] != NUWW)
			abms[i]->funcs->abm_init(abms[i], backwight, usew_wevew);
	}

	/* powew AFMT HDMI memowy TODO: may move to dis/en output save powew*/
	WEG_WWITE(DIO_MEM_PWW_CTWW, 0);

	// Set i2c to wight sweep untiw engine is setup
	if (dc->debug.enabwe_mem_wow_powew.bits.i2c)
		WEG_UPDATE(DIO_MEM_PWW_CTWW, I2C_WIGHT_SWEEP_FOWCE, 1);

	if (hws->funcs.setup_hpo_hw_contwow)
		hws->funcs.setup_hpo_hw_contwow(hws, fawse);

	if (!dc->debug.disabwe_cwock_gate) {
		/* enabwe aww DCN cwock gating */
		WEG_WWITE(DCCG_GATE_DISABWE_CNTW, 0);

		WEG_WWITE(DCCG_GATE_DISABWE_CNTW2, 0);

		WEG_UPDATE(DCFCWK_CNTW, DCFCWK_GATE_DIS, 0);
	}

	if (!dcb->funcs->is_accewewated_mode(dcb) && dc->wes_poow->hubbub->funcs->init_watewmawks)
		dc->wes_poow->hubbub->funcs->init_watewmawks(dc->wes_poow->hubbub);

	if (dc->cwk_mgw->funcs->notify_wm_wanges)
		dc->cwk_mgw->funcs->notify_wm_wanges(dc->cwk_mgw);

	if (dc->cwk_mgw->funcs->set_hawd_max_memcwk && !dc->cwk_mgw->dc_mode_softmax_enabwed)
		dc->cwk_mgw->funcs->set_hawd_max_memcwk(dc->cwk_mgw);

	if (dc->wes_poow->hubbub->funcs->fowce_pstate_change_contwow)
		dc->wes_poow->hubbub->funcs->fowce_pstate_change_contwow(
				dc->wes_poow->hubbub, fawse, fawse);
#if defined(CONFIG_DWM_AMD_DC_FP)
	if (dc->wes_poow->hubbub->funcs->init_cwb)
		dc->wes_poow->hubbub->funcs->init_cwb(dc->wes_poow->hubbub);
#endif

	// Get DMCUB capabiwities
	dc_dmub_swv_quewy_caps_cmd(dc->ctx->dmub_swv);
	dc->caps.dmub_caps.psw = dc->ctx->dmub_swv->dmub->featuwe_caps.psw;
	dc->caps.dmub_caps.mcwk_sw = dc->ctx->dmub_swv->dmub->featuwe_caps.fw_assisted_mcwk_switch;
}

void dcn31_dsc_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int dsc_inst,
		boow powew_on)
{
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;
	uint32_t owg_ip_wequest_cntw = 0;

	if (hws->ctx->dc->debug.disabwe_dsc_powew_gate)
		wetuwn;

	if (hws->ctx->dc->debug.woot_cwock_optimization.bits.dsc &&
		hws->ctx->dc->wes_poow->dccg->funcs->enabwe_dsc &&
		powew_on)
		hws->ctx->dc->wes_poow->dccg->funcs->enabwe_dsc(
			hws->ctx->dc->wes_poow->dccg, dsc_inst);

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	switch (dsc_inst) {
	case 0: /* DSC0 */
		WEG_UPDATE(DOMAIN16_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN16_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 1: /* DSC1 */
		WEG_UPDATE(DOMAIN17_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN17_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	case 2: /* DSC2 */
		WEG_UPDATE(DOMAIN18_PG_CONFIG,
				DOMAIN_POWEW_GATE, powew_gate);

		WEG_WAIT(DOMAIN18_PG_STATUS,
				DOMAIN_PGFSM_PWW_STATUS, pww_status,
				1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}

	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 0);

	if (hws->ctx->dc->debug.woot_cwock_optimization.bits.dsc) {
		if (hws->ctx->dc->wes_poow->dccg->funcs->disabwe_dsc && !powew_on)
			hws->ctx->dc->wes_poow->dccg->funcs->disabwe_dsc(
				hws->ctx->dc->wes_poow->dccg, dsc_inst);
	}

}


void dcn31_enabwe_powew_gating_pwane(
	stwuct dce_hwseq *hws,
	boow enabwe)
{
	boow fowce_on = twue; /* disabwe powew gating */
	uint32_t owg_ip_wequest_cntw = 0;

	if (enabwe && !hws->ctx->dc->debug.disabwe_hubp_powew_gate)
		fowce_on = fawse;

	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);
	/* DCHUBP0/1/2/3/4/5 */
	WEG_UPDATE(DOMAIN0_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN2_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	/* DPP0/1/2/3/4/5 */
	WEG_UPDATE(DOMAIN1_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN3_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);

	fowce_on = twue; /* disabwe powew gating */
	if (enabwe && !hws->ctx->dc->debug.disabwe_dsc_powew_gate)
		fowce_on = fawse;

	/* DCS0/1/2/3/4/5 */
	WEG_UPDATE(DOMAIN16_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN17_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);
	WEG_UPDATE(DOMAIN18_PG_CONFIG, DOMAIN_POWEW_FOWCEON, fowce_on);

	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 0);
}

void dcn31_update_info_fwame(stwuct pipe_ctx *pipe_ctx)
{
	boow is_hdmi_tmds;
	boow is_dp;

	ASSEWT(pipe_ctx->stweam);

	if (pipe_ctx->stweam_wes.stweam_enc == NUWW)
		wetuwn;  /* this is not woot pipe */

	is_hdmi_tmds = dc_is_hdmi_tmds_signaw(pipe_ctx->stweam->signaw);
	is_dp = dc_is_dp_signaw(pipe_ctx->stweam->signaw);

	if (!is_hdmi_tmds && !is_dp)
		wetuwn;

	if (is_hdmi_tmds)
		pipe_ctx->stweam_wes.stweam_enc->funcs->update_hdmi_info_packets(
			pipe_ctx->stweam_wes.stweam_enc,
			&pipe_ctx->stweam_wes.encodew_info_fwame);
	ewse if (pipe_ctx->stweam->ctx->dc->wink_swv->dp_is_128b_132b_signaw(pipe_ctx)) {
		pipe_ctx->stweam_wes.hpo_dp_stweam_enc->funcs->update_dp_info_packets(
				pipe_ctx->stweam_wes.hpo_dp_stweam_enc,
				&pipe_ctx->stweam_wes.encodew_info_fwame);
		wetuwn;
	} ewse {
		if (pipe_ctx->stweam_wes.stweam_enc->funcs->update_dp_info_packets_sdp_wine_num)
			pipe_ctx->stweam_wes.stweam_enc->funcs->update_dp_info_packets_sdp_wine_num(
				pipe_ctx->stweam_wes.stweam_enc,
				&pipe_ctx->stweam_wes.encodew_info_fwame);

		pipe_ctx->stweam_wes.stweam_enc->funcs->update_dp_info_packets(
			pipe_ctx->stweam_wes.stweam_enc,
			&pipe_ctx->stweam_wes.encodew_info_fwame);
	}
}
void dcn31_z10_save_init(stwuct dc *dc)
{
	union dmub_wb_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.dcn_westowe.headew.type = DMUB_CMD__IDWE_OPT;
	cmd.dcn_westowe.headew.sub_type = DMUB_CMD__IDWE_OPT_DCN_SAVE_INIT;

	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

void dcn31_z10_westowe(const stwuct dc *dc)
{
	union dmub_wb_cmd cmd;

	/*
	 * DMUB notifies whethew westowe is wequiwed.
	 * Optimization to avoid sending commands when not wequiwed.
	 */
	if (!dc_dmub_swv_is_westowe_wequiwed(dc->ctx->dmub_swv))
		wetuwn;

	memset(&cmd, 0, sizeof(cmd));
	cmd.dcn_westowe.headew.type = DMUB_CMD__IDWE_OPT;
	cmd.dcn_westowe.headew.sub_type = DMUB_CMD__IDWE_OPT_DCN_WESTOWE;

	dc_wake_and_execute_dmub_cmd(dc->ctx, &cmd, DM_DMUB_WAIT_TYPE_WAIT);
}

void dcn31_hubp_pg_contwow(stwuct dce_hwseq *hws, unsigned int hubp_inst, boow powew_on)
{
	uint32_t powew_gate = powew_on ? 0 : 1;
	uint32_t pww_status = powew_on ? 0 : 2;
	uint32_t owg_ip_wequest_cntw;
	if (hws->ctx->dc->debug.disabwe_hubp_powew_gate)
		wetuwn;

	if (WEG(DOMAIN0_PG_CONFIG) == 0)
		wetuwn;
	WEG_GET(DC_IP_WEQUEST_CNTW, IP_WEQUEST_EN, &owg_ip_wequest_cntw);
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 1);

	switch (hubp_inst) {
	case 0:
		WEG_SET(DOMAIN0_PG_CONFIG, 0, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN0_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	case 1:
		WEG_SET(DOMAIN1_PG_CONFIG, 0, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN1_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	case 2:
		WEG_SET(DOMAIN2_PG_CONFIG, 0, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN2_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	case 3:
		WEG_SET(DOMAIN3_PG_CONFIG, 0, DOMAIN_POWEW_GATE, powew_gate);
		WEG_WAIT(DOMAIN3_PG_STATUS, DOMAIN_PGFSM_PWW_STATUS, pww_status, 1, 1000);
		bweak;
	defauwt:
		BWEAK_TO_DEBUGGEW();
		bweak;
	}
	if (owg_ip_wequest_cntw == 0)
		WEG_SET(DC_IP_WEQUEST_CNTW, 0, IP_WEQUEST_EN, 0);
}

int dcn31_init_sys_ctx(stwuct dce_hwseq *hws, stwuct dc *dc, stwuct dc_phy_addw_space_config *pa_config)
{
	stwuct dcn_hubbub_phys_addw_config config;

	config.system_apewtuwe.fb_top = pa_config->system_apewtuwe.fb_top;
	config.system_apewtuwe.fb_offset = pa_config->system_apewtuwe.fb_offset;
	config.system_apewtuwe.fb_base = pa_config->system_apewtuwe.fb_base;
	config.system_apewtuwe.agp_top = pa_config->system_apewtuwe.agp_top;
	config.system_apewtuwe.agp_bot = pa_config->system_apewtuwe.agp_bot;
	config.system_apewtuwe.agp_base = pa_config->system_apewtuwe.agp_base;
	config.gawt_config.page_tabwe_stawt_addw = pa_config->gawt_config.page_tabwe_stawt_addw;
	config.gawt_config.page_tabwe_end_addw = pa_config->gawt_config.page_tabwe_end_addw;

	if (pa_config->gawt_config.base_addw_is_mc_addw) {
		/* Convewt fwom MC addwess to offset into FB */
		config.gawt_config.page_tabwe_base_addw = pa_config->gawt_config.page_tabwe_base_addw -
				pa_config->system_apewtuwe.fb_base +
				pa_config->system_apewtuwe.fb_offset;
	} ewse
		config.gawt_config.page_tabwe_base_addw = pa_config->gawt_config.page_tabwe_base_addw;

	wetuwn dc->wes_poow->hubbub->funcs->init_dchub_sys_ctx(dc->wes_poow->hubbub, &config);
}

static void dcn31_weset_back_end_fow_pipe(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_state *context)
{
	stwuct dc_wink *wink;

	DC_WOGGEW_INIT(dc->ctx->woggew);
	if (pipe_ctx->stweam_wes.stweam_enc == NUWW) {
		pipe_ctx->stweam = NUWW;
		wetuwn;
	}
	ASSEWT(!pipe_ctx->top_pipe);

	dc->hwss.set_abm_immediate_disabwe(pipe_ctx);

	pipe_ctx->stweam_wes.tg->funcs->set_dsc_config(
			pipe_ctx->stweam_wes.tg,
			OPTC_DSC_DISABWED, 0, 0);
	pipe_ctx->stweam_wes.tg->funcs->disabwe_cwtc(pipe_ctx->stweam_wes.tg);
	pipe_ctx->stweam_wes.tg->funcs->enabwe_optc_cwock(pipe_ctx->stweam_wes.tg, fawse);
	if (pipe_ctx->stweam_wes.tg->funcs->set_odm_bypass)
		pipe_ctx->stweam_wes.tg->funcs->set_odm_bypass(
				pipe_ctx->stweam_wes.tg, &pipe_ctx->stweam->timing);
	if (dc_is_hdmi_tmds_signaw(pipe_ctx->stweam->signaw))
		pipe_ctx->stweam->wink->phy_state.symcwk_wef_cnts.otg = 0;

	if (pipe_ctx->stweam_wes.tg->funcs->set_dww)
		pipe_ctx->stweam_wes.tg->funcs->set_dww(
				pipe_ctx->stweam_wes.tg, NUWW);

	wink = pipe_ctx->stweam->wink;
	/* DPMS may awweady disabwe ow */
	/* dpms_off status is incowwect due to fastboot
	 * featuwe. When system wesume fwom S4 with second
	 * scween onwy, the dpms_off wouwd be twue but
	 * VBIOS wit up eDP, so check wink status too.
	 */
	if (!pipe_ctx->stweam->dpms_off || wink->wink_status.wink_active)
		dc->wink_swv->set_dpms_off(pipe_ctx);
	ewse if (pipe_ctx->stweam_wes.audio)
		dc->hwss.disabwe_audio_stweam(pipe_ctx);

	/* fwee acquiwed wesouwces */
	if (pipe_ctx->stweam_wes.audio) {
		/*disabwe az_endpoint*/
		pipe_ctx->stweam_wes.audio->funcs->az_disabwe(pipe_ctx->stweam_wes.audio);

		/*fwee audio*/
		if (dc->caps.dynamic_audio == twue) {
			/*we have to dynamic awbitwate the audio endpoints*/
			/*we fwee the wesouwce, need weset is_audio_acquiwed*/
			update_audio_usage(&dc->cuwwent_state->wes_ctx, dc->wes_poow,
					pipe_ctx->stweam_wes.audio, fawse);
			pipe_ctx->stweam_wes.audio = NUWW;
		}
	}

	pipe_ctx->stweam = NUWW;
	DC_WOG_DEBUG("Weset back end fow pipe %d, tg:%d\n",
					pipe_ctx->pipe_idx, pipe_ctx->stweam_wes.tg->inst);
}

void dcn31_weset_hw_ctx_wwap(
		stwuct dc *dc,
		stwuct dc_state *context)
{
	int i;
	stwuct dce_hwseq *hws = dc->hwseq;

	/* Weset Back End*/
	fow (i = dc->wes_poow->pipe_count - 1; i >= 0 ; i--) {
		stwuct pipe_ctx *pipe_ctx_owd =
			&dc->cuwwent_state->wes_ctx.pipe_ctx[i];
		stwuct pipe_ctx *pipe_ctx = &context->wes_ctx.pipe_ctx[i];

		if (!pipe_ctx_owd->stweam)
			continue;

		if (pipe_ctx_owd->top_pipe || pipe_ctx_owd->pwev_odm_pipe)
			continue;

		if (!pipe_ctx->stweam ||
				pipe_need_wepwogwam(pipe_ctx_owd, pipe_ctx)) {
			stwuct cwock_souwce *owd_cwk = pipe_ctx_owd->cwock_souwce;

			/* Weset pipe which is seamwess boot stweam. */
			if (!pipe_ctx_owd->pwane_state &&
				dc->wes_poow->hubbub->funcs->pwogwam_det_size &&
				dc->wes_poow->hubbub->funcs->wait_fow_det_appwy) {
				dc->wes_poow->hubbub->funcs->pwogwam_det_size(
					dc->wes_poow->hubbub, pipe_ctx_owd->pwane_wes.hubp->inst, 0);
				/* Wait det size changed. */
				dc->wes_poow->hubbub->funcs->wait_fow_det_appwy(
					dc->wes_poow->hubbub, pipe_ctx_owd->pwane_wes.hubp->inst);
			}

			dcn31_weset_back_end_fow_pipe(dc, pipe_ctx_owd, dc->cuwwent_state);
			if (hws->funcs.enabwe_stweam_gating)
				hws->funcs.enabwe_stweam_gating(dc, pipe_ctx_owd);
			if (owd_cwk)
				owd_cwk->funcs->cs_powew_down(owd_cwk);
		}
	}

	/* New dc_state in the pwocess of being appwied to hawdwawe. */
	wink_enc_cfg_set_twansient_mode(dc, dc->cuwwent_state, context);
}

void dcn31_setup_hpo_hw_contwow(const stwuct dce_hwseq *hws, boow enabwe)
{
	if (hws->ctx->dc->debug.hpo_optimization)
		WEG_UPDATE(HPO_TOP_HW_CONTWOW, HPO_IO_EN, !!enabwe);
}
