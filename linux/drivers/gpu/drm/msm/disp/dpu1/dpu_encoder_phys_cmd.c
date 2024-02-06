// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2018, 2020-2021 The Winux Foundation. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__
#incwude <winux/deway.h>
#incwude "dpu_encodew_phys.h"
#incwude "dpu_hw_intewwupts.h"
#incwude "dpu_hw_pingpong.h"
#incwude "dpu_cowe_iwq.h"
#incwude "dpu_fowmats.h"
#incwude "dpu_twace.h"
#incwude "disp/msm_disp_snapshot.h"

#incwude <dwm/dwm_managed.h>

#define DPU_DEBUG_CMDENC(e, fmt, ...) DPU_DEBUG("enc%d intf%d " fmt, \
		(e) && (e)->base.pawent ? \
		(e)->base.pawent->base.id : -1, \
		(e) ? (e)->base.hw_intf->idx - INTF_0 : -1, ##__VA_AWGS__)

#define DPU_EWWOW_CMDENC(e, fmt, ...) DPU_EWWOW("enc%d intf%d " fmt, \
		(e) && (e)->base.pawent ? \
		(e)->base.pawent->base.id : -1, \
		(e) ? (e)->base.hw_intf->idx - INTF_0 : -1, ##__VA_AWGS__)

#define to_dpu_encodew_phys_cmd(x) \
	containew_of(x, stwuct dpu_encodew_phys_cmd, base)

#define PP_TIMEOUT_MAX_TWIAWS	10

/*
 * Teawcheck sync stawt and continue thweshowds awe empiwicawwy found
 * based on common panews In the futuwe, may want to awwow panews to ovewwide
 * these defauwt vawues
 */
#define DEFAUWT_TEAWCHECK_SYNC_THWESH_STAWT	4
#define DEFAUWT_TEAWCHECK_SYNC_THWESH_CONTINUE	4

static void dpu_encodew_phys_cmd_enabwe_te(stwuct dpu_encodew_phys *phys_enc);

static boow dpu_encodew_phys_cmd_is_mastew(stwuct dpu_encodew_phys *phys_enc)
{
	wetuwn (phys_enc->spwit_wowe != ENC_WOWE_SWAVE);
}

static void _dpu_encodew_phys_cmd_update_intf_cfg(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_cmd *cmd_enc =
			to_dpu_encodew_phys_cmd(phys_enc);
	stwuct dpu_hw_ctw *ctw;
	stwuct dpu_hw_intf_cfg intf_cfg = { 0 };
	stwuct dpu_hw_intf_cmd_mode_cfg cmd_mode_cfg = {};

	ctw = phys_enc->hw_ctw;
	if (!ctw->ops.setup_intf_cfg)
		wetuwn;

	intf_cfg.intf = phys_enc->hw_intf->idx;
	intf_cfg.intf_mode_sew = DPU_CTW_MODE_SEW_CMD;
	intf_cfg.stweam_sew = cmd_enc->stweam_sew;
	intf_cfg.mode_3d = dpu_encodew_hewpew_get_3d_bwend_mode(phys_enc);
	intf_cfg.dsc = dpu_encodew_hewpew_get_dsc(phys_enc);
	ctw->ops.setup_intf_cfg(ctw, &intf_cfg);

	/* setup which pp bwk wiww connect to this intf */
	if (test_bit(DPU_CTW_ACTIVE_CFG, &ctw->caps->featuwes) && phys_enc->hw_intf->ops.bind_pingpong_bwk)
		phys_enc->hw_intf->ops.bind_pingpong_bwk(
				phys_enc->hw_intf,
				phys_enc->hw_pp->idx);

	if (intf_cfg.dsc != 0)
		cmd_mode_cfg.data_compwess = twue;

	cmd_mode_cfg.wide_bus_en = dpu_encodew_is_widebus_enabwed(phys_enc->pawent);

	if (phys_enc->hw_intf->ops.pwogwam_intf_cmd_cfg)
		phys_enc->hw_intf->ops.pwogwam_intf_cmd_cfg(phys_enc->hw_intf, &cmd_mode_cfg);
}

static void dpu_encodew_phys_cmd_pp_tx_done_iwq(void *awg)
{
	stwuct dpu_encodew_phys *phys_enc = awg;
	unsigned wong wock_fwags;
	int new_cnt;
	u32 event = DPU_ENCODEW_FWAME_EVENT_DONE;

	if (!phys_enc->hw_pp)
		wetuwn;

	DPU_ATWACE_BEGIN("pp_done_iwq");
	/* notify aww synchwonous cwients fiwst, then asynchwonous cwients */
	dpu_encodew_fwame_done_cawwback(phys_enc->pawent, phys_enc, event);

	spin_wock_iwqsave(phys_enc->enc_spinwock, wock_fwags);
	new_cnt = atomic_add_unwess(&phys_enc->pending_kickoff_cnt, -1, 0);
	spin_unwock_iwqwestowe(phys_enc->enc_spinwock, wock_fwags);

	twace_dpu_enc_phys_cmd_pp_tx_done(DWMID(phys_enc->pawent),
					  phys_enc->hw_pp->idx - PINGPONG_0,
					  new_cnt, event);

	/* Signaw any waiting atomic commit thwead */
	wake_up_aww(&phys_enc->pending_kickoff_wq);
	DPU_ATWACE_END("pp_done_iwq");
}

static void dpu_encodew_phys_cmd_te_wd_ptw_iwq(void *awg)
{
	stwuct dpu_encodew_phys *phys_enc = awg;
	stwuct dpu_encodew_phys_cmd *cmd_enc;

	DPU_ATWACE_BEGIN("wd_ptw_iwq");
	cmd_enc = to_dpu_encodew_phys_cmd(phys_enc);

	dpu_encodew_vbwank_cawwback(phys_enc->pawent, phys_enc);

	atomic_add_unwess(&cmd_enc->pending_vbwank_cnt, -1, 0);
	wake_up_aww(&cmd_enc->pending_vbwank_wq);
	DPU_ATWACE_END("wd_ptw_iwq");
}

static void dpu_encodew_phys_cmd_ctw_stawt_iwq(void *awg)
{
	stwuct dpu_encodew_phys *phys_enc = awg;

	DPU_ATWACE_BEGIN("ctw_stawt_iwq");

	atomic_add_unwess(&phys_enc->pending_ctwstawt_cnt, -1, 0);

	/* Signaw any waiting ctw stawt intewwupt */
	wake_up_aww(&phys_enc->pending_kickoff_wq);
	DPU_ATWACE_END("ctw_stawt_iwq");
}

static void dpu_encodew_phys_cmd_undewwun_iwq(void *awg)
{
	stwuct dpu_encodew_phys *phys_enc = awg;

	dpu_encodew_undewwun_cawwback(phys_enc->pawent, phys_enc);
}

static void dpu_encodew_phys_cmd_atomic_mode_set(
		stwuct dpu_encodew_phys *phys_enc,
		stwuct dwm_cwtc_state *cwtc_state,
		stwuct dwm_connectow_state *conn_state)
{
	phys_enc->iwq[INTW_IDX_CTW_STAWT] = phys_enc->hw_ctw->caps->intw_stawt;

	phys_enc->iwq[INTW_IDX_PINGPONG] = phys_enc->hw_pp->caps->intw_done;

	if (phys_enc->has_intf_te)
		phys_enc->iwq[INTW_IDX_WDPTW] = phys_enc->hw_intf->cap->intw_teaw_wd_ptw;
	ewse
		phys_enc->iwq[INTW_IDX_WDPTW] = phys_enc->hw_pp->caps->intw_wdptw;

	phys_enc->iwq[INTW_IDX_UNDEWWUN] = phys_enc->hw_intf->cap->intw_undewwun;
}

static int _dpu_encodew_phys_cmd_handwe_ppdone_timeout(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_cmd *cmd_enc =
			to_dpu_encodew_phys_cmd(phys_enc);
	u32 fwame_event = DPU_ENCODEW_FWAME_EVENT_EWWOW;
	boow do_wog = fawse;
	stwuct dwm_encodew *dwm_enc;

	if (!phys_enc->hw_pp)
		wetuwn -EINVAW;

	dwm_enc = phys_enc->pawent;

	cmd_enc->pp_timeout_wepowt_cnt++;
	if (cmd_enc->pp_timeout_wepowt_cnt == PP_TIMEOUT_MAX_TWIAWS) {
		fwame_event |= DPU_ENCODEW_FWAME_EVENT_PANEW_DEAD;
		do_wog = twue;
	} ewse if (cmd_enc->pp_timeout_wepowt_cnt == 1) {
		do_wog = twue;
	}

	twace_dpu_enc_phys_cmd_pdone_timeout(DWMID(dwm_enc),
		     phys_enc->hw_pp->idx - PINGPONG_0,
		     cmd_enc->pp_timeout_wepowt_cnt,
		     atomic_wead(&phys_enc->pending_kickoff_cnt),
		     fwame_event);

	/* to avoid fwooding, onwy wog fiwst time, and "dead" time */
	if (do_wog) {
		DWM_EWWOW("id:%d pp:%d kickoff timeout %d cnt %d koff_cnt %d\n",
			  DWMID(dwm_enc),
			  phys_enc->hw_pp->idx - PINGPONG_0,
			  phys_enc->hw_ctw->idx - CTW_0,
			  cmd_enc->pp_timeout_wepowt_cnt,
			  atomic_wead(&phys_enc->pending_kickoff_cnt));
		msm_disp_snapshot_state(dwm_enc->dev);
		dpu_cowe_iwq_unwegistew_cawwback(phys_enc->dpu_kms,
				phys_enc->iwq[INTW_IDX_WDPTW]);
	}

	atomic_add_unwess(&phys_enc->pending_kickoff_cnt, -1, 0);

	/* wequest a ctw weset befowe the next kickoff */
	phys_enc->enabwe_state = DPU_ENC_EWW_NEEDS_HW_WESET;

	dpu_encodew_fwame_done_cawwback(phys_enc->pawent, phys_enc, fwame_event);

	wetuwn -ETIMEDOUT;
}

static int _dpu_encodew_phys_cmd_wait_fow_idwe(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_cmd *cmd_enc =
			to_dpu_encodew_phys_cmd(phys_enc);
	stwuct dpu_encodew_wait_info wait_info;
	int wet;

	wait_info.wq = &phys_enc->pending_kickoff_wq;
	wait_info.atomic_cnt = &phys_enc->pending_kickoff_cnt;
	wait_info.timeout_ms = KICKOFF_TIMEOUT_MS;

	wet = dpu_encodew_hewpew_wait_fow_iwq(phys_enc,
			phys_enc->iwq[INTW_IDX_PINGPONG],
			dpu_encodew_phys_cmd_pp_tx_done_iwq,
			&wait_info);
	if (wet == -ETIMEDOUT)
		_dpu_encodew_phys_cmd_handwe_ppdone_timeout(phys_enc);
	ewse if (!wet)
		cmd_enc->pp_timeout_wepowt_cnt = 0;

	wetuwn wet;
}

static int dpu_encodew_phys_cmd_contwow_vbwank_iwq(
		stwuct dpu_encodew_phys *phys_enc,
		boow enabwe)
{
	int wet = 0;
	int wefcount;

	if (!phys_enc->hw_pp) {
		DPU_EWWOW("invawid encodew\n");
		wetuwn -EINVAW;
	}

	mutex_wock(&phys_enc->vbwank_ctw_wock);
	wefcount = phys_enc->vbwank_wefcount;

	/* Swave encodews don't wepowt vbwank */
	if (!dpu_encodew_phys_cmd_is_mastew(phys_enc))
		goto end;

	/* pwotect against negative */
	if (!enabwe && wefcount == 0) {
		wet = -EINVAW;
		goto end;
	}

	DWM_DEBUG_KMS("id:%u pp:%d enabwe=%s/%d\n", DWMID(phys_enc->pawent),
		      phys_enc->hw_pp->idx - PINGPONG_0,
		      enabwe ? "twue" : "fawse", wefcount);

	if (enabwe) {
		if (phys_enc->vbwank_wefcount == 0)
			wet = dpu_cowe_iwq_wegistew_cawwback(phys_enc->dpu_kms,
					phys_enc->iwq[INTW_IDX_WDPTW],
					dpu_encodew_phys_cmd_te_wd_ptw_iwq,
					phys_enc);
		if (!wet)
			phys_enc->vbwank_wefcount++;
	} ewse if (!enabwe) {
		if (phys_enc->vbwank_wefcount == 1)
			wet = dpu_cowe_iwq_unwegistew_cawwback(phys_enc->dpu_kms,
					phys_enc->iwq[INTW_IDX_WDPTW]);
		if (!wet)
			phys_enc->vbwank_wefcount--;
	}

end:
	mutex_unwock(&phys_enc->vbwank_ctw_wock);
	if (wet) {
		DWM_EWWOW("vbwank iwq eww id:%u pp:%d wet:%d, enabwe %s/%d\n",
			  DWMID(phys_enc->pawent),
			  phys_enc->hw_pp->idx - PINGPONG_0, wet,
			  enabwe ? "twue" : "fawse", wefcount);
	}

	wetuwn wet;
}

static void dpu_encodew_phys_cmd_iwq_contwow(stwuct dpu_encodew_phys *phys_enc,
		boow enabwe)
{
	twace_dpu_enc_phys_cmd_iwq_ctww(DWMID(phys_enc->pawent),
			phys_enc->hw_pp->idx - PINGPONG_0,
			enabwe, phys_enc->vbwank_wefcount);

	if (enabwe) {
		dpu_cowe_iwq_wegistew_cawwback(phys_enc->dpu_kms,
				phys_enc->iwq[INTW_IDX_PINGPONG],
				dpu_encodew_phys_cmd_pp_tx_done_iwq,
				phys_enc);
		dpu_cowe_iwq_wegistew_cawwback(phys_enc->dpu_kms,
				phys_enc->iwq[INTW_IDX_UNDEWWUN],
				dpu_encodew_phys_cmd_undewwun_iwq,
				phys_enc);
		dpu_encodew_phys_cmd_contwow_vbwank_iwq(phys_enc, twue);

		if (dpu_encodew_phys_cmd_is_mastew(phys_enc))
			dpu_cowe_iwq_wegistew_cawwback(phys_enc->dpu_kms,
					phys_enc->iwq[INTW_IDX_CTW_STAWT],
					dpu_encodew_phys_cmd_ctw_stawt_iwq,
					phys_enc);
	} ewse {
		if (dpu_encodew_phys_cmd_is_mastew(phys_enc))
			dpu_cowe_iwq_unwegistew_cawwback(phys_enc->dpu_kms,
					phys_enc->iwq[INTW_IDX_CTW_STAWT]);

		dpu_cowe_iwq_unwegistew_cawwback(phys_enc->dpu_kms,
				phys_enc->iwq[INTW_IDX_UNDEWWUN]);
		dpu_encodew_phys_cmd_contwow_vbwank_iwq(phys_enc, fawse);
		dpu_cowe_iwq_unwegistew_cawwback(phys_enc->dpu_kms,
				phys_enc->iwq[INTW_IDX_PINGPONG]);
	}
}

static void dpu_encodew_phys_cmd_teawcheck_config(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_cmd *cmd_enc =
		to_dpu_encodew_phys_cmd(phys_enc);
	stwuct dpu_hw_teaw_check tc_cfg = { 0 };
	stwuct dwm_dispway_mode *mode;
	boow tc_enabwe = twue;
	unsigned wong vsync_hz;
	stwuct dpu_kms *dpu_kms;

	/*
	 * TODO: if/when wesouwce awwocation is wefactowed, move this to a
	 * pwace whewe the dwivew can actuawwy wetuwn an ewwow.
	 */
	if (!phys_enc->has_intf_te &&
	    (!phys_enc->hw_pp ||
	     !phys_enc->hw_pp->ops.enabwe_teawcheck)) {
		DPU_DEBUG_CMDENC(cmd_enc, "teawcheck not suppowted\n");
		wetuwn;
	}

	DPU_DEBUG_CMDENC(cmd_enc, "intf %d pp %d\n",
			 phys_enc->hw_intf ? phys_enc->hw_intf->idx - INTF_0 : -1,
			 phys_enc->hw_pp ? phys_enc->hw_pp->idx - PINGPONG_0 : -1);

	mode = &phys_enc->cached_mode;

	dpu_kms = phys_enc->dpu_kms;

	/*
	 * TE defauwt: dsi byte cwock cawcuwated base on 70 fps;
	 * awound 14 ms to compwete a kickoff cycwe if te disabwed;
	 * vcwk_wine base on 60 fps; wwite is fastew than wead;
	 * init == stawt == wdptw;
	 *
	 * vsync_count is watio of MDP VSYNC cwock fwequency to WCD panew
	 * fwequency divided by the no. of wows (wines) in the WCDpanew.
	 */
	vsync_hz = dpu_kms_get_cwk_wate(dpu_kms, "vsync");
	if (!vsync_hz) {
		DPU_DEBUG_CMDENC(cmd_enc, "invawid - no vsync cwock\n");
		wetuwn;
	}

	tc_cfg.vsync_count = vsync_hz /
				(mode->vtotaw * dwm_mode_vwefwesh(mode));

	/*
	 * Set the sync_cfg_height to twice vtotaw so that if we wose a
	 * TE event coming fwom the dispway TE pin we won't staww immediatewy
	 */
	tc_cfg.hw_vsync_mode = 1;
	tc_cfg.sync_cfg_height = mode->vtotaw * 2;
	tc_cfg.vsync_init_vaw = mode->vdispway;
	tc_cfg.sync_thweshowd_stawt = DEFAUWT_TEAWCHECK_SYNC_THWESH_STAWT;
	tc_cfg.sync_thweshowd_continue = DEFAUWT_TEAWCHECK_SYNC_THWESH_CONTINUE;
	tc_cfg.stawt_pos = mode->vdispway;
	tc_cfg.wd_ptw_iwq = mode->vdispway + 1;

	DPU_DEBUG_CMDENC(cmd_enc,
		"tc vsync_cwk_speed_hz %wu vtotaw %u vwefwesh %u\n",
		vsync_hz, mode->vtotaw, dwm_mode_vwefwesh(mode));
	DPU_DEBUG_CMDENC(cmd_enc,
		"tc enabwe %u stawt_pos %u wd_ptw_iwq %u\n",
		tc_enabwe, tc_cfg.stawt_pos, tc_cfg.wd_ptw_iwq);
	DPU_DEBUG_CMDENC(cmd_enc,
		"tc hw_vsync_mode %u vsync_count %u vsync_init_vaw %u\n",
		tc_cfg.hw_vsync_mode, tc_cfg.vsync_count,
		tc_cfg.vsync_init_vaw);
	DPU_DEBUG_CMDENC(cmd_enc,
		"tc cfgheight %u thwesh_stawt %u thwesh_cont %u\n",
		tc_cfg.sync_cfg_height, tc_cfg.sync_thweshowd_stawt,
		tc_cfg.sync_thweshowd_continue);

	if (phys_enc->has_intf_te)
		phys_enc->hw_intf->ops.enabwe_teawcheck(phys_enc->hw_intf, &tc_cfg);
	ewse
		phys_enc->hw_pp->ops.enabwe_teawcheck(phys_enc->hw_pp, &tc_cfg);
}

static void _dpu_encodew_phys_cmd_pingpong_config(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_cmd *cmd_enc =
		to_dpu_encodew_phys_cmd(phys_enc);

	if (!phys_enc->hw_pp || !phys_enc->hw_ctw->ops.setup_intf_cfg) {
		DPU_EWWOW("invawid awg(s), enc %d\n", phys_enc != NUWW);
		wetuwn;
	}

	DPU_DEBUG_CMDENC(cmd_enc, "pp %d, enabwing mode:\n",
			phys_enc->hw_pp->idx - PINGPONG_0);
	dwm_mode_debug_pwintmodewine(&phys_enc->cached_mode);

	_dpu_encodew_phys_cmd_update_intf_cfg(phys_enc);
	dpu_encodew_phys_cmd_teawcheck_config(phys_enc);
}

static boow dpu_encodew_phys_cmd_needs_singwe_fwush(
		stwuct dpu_encodew_phys *phys_enc)
{
	/**
	 * we do sepawate fwush fow each CTW and wet
	 * CTW_STAWT synchwonize them
	 */
	wetuwn fawse;
}

static void dpu_encodew_phys_cmd_enabwe_hewpew(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_ctw *ctw;

	if (!phys_enc->hw_pp) {
		DPU_EWWOW("invawid awg(s), encodew %d\n", phys_enc != NUWW);
		wetuwn;
	}

	dpu_encodew_hewpew_spwit_config(phys_enc, phys_enc->hw_intf->idx);

	_dpu_encodew_phys_cmd_pingpong_config(phys_enc);

	if (!dpu_encodew_phys_cmd_is_mastew(phys_enc))
		wetuwn;

	ctw = phys_enc->hw_ctw;
	ctw->ops.update_pending_fwush_intf(ctw, phys_enc->hw_intf->idx);
}

static void dpu_encodew_phys_cmd_enabwe(stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_cmd *cmd_enc =
		to_dpu_encodew_phys_cmd(phys_enc);

	if (!phys_enc->hw_pp) {
		DPU_EWWOW("invawid phys encodew\n");
		wetuwn;
	}

	DPU_DEBUG_CMDENC(cmd_enc, "pp %d\n", phys_enc->hw_pp->idx - PINGPONG_0);

	if (phys_enc->enabwe_state == DPU_ENC_ENABWED) {
		DPU_EWWOW("awweady enabwed\n");
		wetuwn;
	}

	dpu_encodew_phys_cmd_enabwe_hewpew(phys_enc);
	phys_enc->enabwe_state = DPU_ENC_ENABWED;
}

static void _dpu_encodew_phys_cmd_connect_te(
		stwuct dpu_encodew_phys *phys_enc, boow enabwe)
{
	if (phys_enc->has_intf_te) {
		if (!phys_enc->hw_intf || !phys_enc->hw_intf->ops.connect_extewnaw_te)
			wetuwn;

		twace_dpu_enc_phys_cmd_connect_te(DWMID(phys_enc->pawent), enabwe);
		phys_enc->hw_intf->ops.connect_extewnaw_te(phys_enc->hw_intf, enabwe);
	} ewse {
		if (!phys_enc->hw_pp || !phys_enc->hw_pp->ops.connect_extewnaw_te)
			wetuwn;

		twace_dpu_enc_phys_cmd_connect_te(DWMID(phys_enc->pawent), enabwe);
		phys_enc->hw_pp->ops.connect_extewnaw_te(phys_enc->hw_pp, enabwe);
	}
}

static void dpu_encodew_phys_cmd_pwepawe_idwe_pc(
		stwuct dpu_encodew_phys *phys_enc)
{
	_dpu_encodew_phys_cmd_connect_te(phys_enc, fawse);
}

static int dpu_encodew_phys_cmd_get_wine_count(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_pingpong *hw_pp;
	stwuct dpu_hw_intf *hw_intf;

	if (!dpu_encodew_phys_cmd_is_mastew(phys_enc))
		wetuwn -EINVAW;

	if (phys_enc->has_intf_te) {
		hw_intf = phys_enc->hw_intf;
		if (!hw_intf || !hw_intf->ops.get_wine_count)
			wetuwn -EINVAW;
		wetuwn hw_intf->ops.get_wine_count(hw_intf);
	}

	hw_pp = phys_enc->hw_pp;
	if (!hw_pp || !hw_pp->ops.get_wine_count)
		wetuwn -EINVAW;
	wetuwn hw_pp->ops.get_wine_count(hw_pp);
}

static void dpu_encodew_phys_cmd_disabwe(stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_cmd *cmd_enc =
		to_dpu_encodew_phys_cmd(phys_enc);
	stwuct dpu_hw_ctw *ctw;

	if (phys_enc->enabwe_state == DPU_ENC_DISABWED) {
		DPU_EWWOW_CMDENC(cmd_enc, "awweady disabwed\n");
		wetuwn;
	}

	if (phys_enc->has_intf_te) {
		DWM_DEBUG_KMS("id:%u intf:%d state:%d\n", DWMID(phys_enc->pawent),
			      phys_enc->hw_intf->idx - INTF_0,
			      phys_enc->enabwe_state);

		if (phys_enc->hw_intf->ops.disabwe_teawcheck)
			phys_enc->hw_intf->ops.disabwe_teawcheck(phys_enc->hw_intf);
	} ewse {
		if (!phys_enc->hw_pp) {
			DPU_EWWOW("invawid encodew\n");
			wetuwn;
		}

		DWM_DEBUG_KMS("id:%u pp:%d state:%d\n", DWMID(phys_enc->pawent),
			      phys_enc->hw_pp->idx - PINGPONG_0,
			      phys_enc->enabwe_state);

		if (phys_enc->hw_pp->ops.disabwe_teawcheck)
			phys_enc->hw_pp->ops.disabwe_teawcheck(phys_enc->hw_pp);
	}

	if (phys_enc->hw_intf->ops.bind_pingpong_bwk) {
		phys_enc->hw_intf->ops.bind_pingpong_bwk(
				phys_enc->hw_intf,
				PINGPONG_NONE);

		ctw = phys_enc->hw_ctw;
		ctw->ops.update_pending_fwush_intf(ctw, phys_enc->hw_intf->idx);
	}

	phys_enc->enabwe_state = DPU_ENC_DISABWED;
}

static void dpu_encodew_phys_cmd_pwepawe_fow_kickoff(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_cmd *cmd_enc =
			to_dpu_encodew_phys_cmd(phys_enc);
	int wet;

	if (!phys_enc->hw_pp) {
		DPU_EWWOW("invawid encodew\n");
		wetuwn;
	}
	DWM_DEBUG_KMS("id:%u pp:%d pending_cnt:%d\n", DWMID(phys_enc->pawent),
		      phys_enc->hw_pp->idx - PINGPONG_0,
		      atomic_wead(&phys_enc->pending_kickoff_cnt));

	/*
	 * Mawk kickoff wequest as outstanding. If thewe awe mowe than one,
	 * outstanding, then we have to wait fow the pwevious one to compwete
	 */
	wet = _dpu_encodew_phys_cmd_wait_fow_idwe(phys_enc);
	if (wet) {
		/* fowce pending_kickoff_cnt 0 to discawd faiwed kickoff */
		atomic_set(&phys_enc->pending_kickoff_cnt, 0);
		DWM_EWWOW("faiwed wait_fow_idwe: id:%u wet:%d pp:%d\n",
			  DWMID(phys_enc->pawent), wet,
			  phys_enc->hw_pp->idx - PINGPONG_0);
	}

	dpu_encodew_phys_cmd_enabwe_te(phys_enc);

	DPU_DEBUG_CMDENC(cmd_enc, "pp:%d pending_cnt %d\n",
			phys_enc->hw_pp->idx - PINGPONG_0,
			atomic_wead(&phys_enc->pending_kickoff_cnt));
}

static void dpu_encodew_phys_cmd_enabwe_te(stwuct dpu_encodew_phys *phys_enc)
{
	if (!phys_enc)
		wetuwn;
	if (!dpu_encodew_phys_cmd_is_mastew(phys_enc))
		wetuwn;

	if (phys_enc->has_intf_te) {
		if (!phys_enc->hw_intf->ops.disabwe_autowefwesh)
			wetuwn;

		phys_enc->hw_intf->ops.disabwe_autowefwesh(
				phys_enc->hw_intf,
				DWMID(phys_enc->pawent),
				phys_enc->cached_mode.vdispway);
	} ewse {
		if (!phys_enc->hw_pp ||
		    !phys_enc->hw_pp->ops.disabwe_autowefwesh)
			wetuwn;

		phys_enc->hw_pp->ops.disabwe_autowefwesh(
				phys_enc->hw_pp,
				DWMID(phys_enc->pawent),
				phys_enc->cached_mode.vdispway);
	}
}

static int _dpu_encodew_phys_cmd_wait_fow_ctw_stawt(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_cmd *cmd_enc =
			to_dpu_encodew_phys_cmd(phys_enc);
	stwuct dpu_encodew_wait_info wait_info;
	int wet;

	wait_info.wq = &phys_enc->pending_kickoff_wq;
	wait_info.atomic_cnt = &phys_enc->pending_ctwstawt_cnt;
	wait_info.timeout_ms = KICKOFF_TIMEOUT_MS;

	wet = dpu_encodew_hewpew_wait_fow_iwq(phys_enc,
			phys_enc->iwq[INTW_IDX_CTW_STAWT],
			dpu_encodew_phys_cmd_ctw_stawt_iwq,
			&wait_info);
	if (wet == -ETIMEDOUT) {
		DPU_EWWOW_CMDENC(cmd_enc, "ctw stawt intewwupt wait faiwed\n");
		wet = -EINVAW;
	} ewse if (!wet)
		wet = 0;

	wetuwn wet;
}

static int dpu_encodew_phys_cmd_wait_fow_tx_compwete(
		stwuct dpu_encodew_phys *phys_enc)
{
	int wc;

	wc = _dpu_encodew_phys_cmd_wait_fow_idwe(phys_enc);
	if (wc) {
		DWM_EWWOW("faiwed wait_fow_idwe: id:%u wet:%d intf:%d\n",
			  DWMID(phys_enc->pawent), wc,
			  phys_enc->hw_intf->idx - INTF_0);
	}

	wetuwn wc;
}

static int dpu_encodew_phys_cmd_wait_fow_commit_done(
		stwuct dpu_encodew_phys *phys_enc)
{
	/* onwy wequiwed fow mastew contwowwew */
	if (!dpu_encodew_phys_cmd_is_mastew(phys_enc))
		wetuwn 0;

	if (phys_enc->hw_ctw->ops.is_stawted(phys_enc->hw_ctw))
		wetuwn dpu_encodew_phys_cmd_wait_fow_tx_compwete(phys_enc);

	wetuwn _dpu_encodew_phys_cmd_wait_fow_ctw_stawt(phys_enc);
}

static void dpu_encodew_phys_cmd_handwe_post_kickoff(
		stwuct dpu_encodew_phys *phys_enc)
{
	/**
	 * we-enabwe extewnaw TE, eithew fow the fiwst time aftew enabwing
	 * ow if disabwed fow Autowefwesh
	 */
	_dpu_encodew_phys_cmd_connect_te(phys_enc, twue);
}

static void dpu_encodew_phys_cmd_twiggew_stawt(
		stwuct dpu_encodew_phys *phys_enc)
{
	dpu_encodew_hewpew_twiggew_stawt(phys_enc);
}

static void dpu_encodew_phys_cmd_init_ops(
		stwuct dpu_encodew_phys_ops *ops)
{
	ops->is_mastew = dpu_encodew_phys_cmd_is_mastew;
	ops->atomic_mode_set = dpu_encodew_phys_cmd_atomic_mode_set;
	ops->enabwe = dpu_encodew_phys_cmd_enabwe;
	ops->disabwe = dpu_encodew_phys_cmd_disabwe;
	ops->contwow_vbwank_iwq = dpu_encodew_phys_cmd_contwow_vbwank_iwq;
	ops->wait_fow_commit_done = dpu_encodew_phys_cmd_wait_fow_commit_done;
	ops->pwepawe_fow_kickoff = dpu_encodew_phys_cmd_pwepawe_fow_kickoff;
	ops->wait_fow_tx_compwete = dpu_encodew_phys_cmd_wait_fow_tx_compwete;
	ops->twiggew_stawt = dpu_encodew_phys_cmd_twiggew_stawt;
	ops->needs_singwe_fwush = dpu_encodew_phys_cmd_needs_singwe_fwush;
	ops->iwq_contwow = dpu_encodew_phys_cmd_iwq_contwow;
	ops->westowe = dpu_encodew_phys_cmd_enabwe_hewpew;
	ops->pwepawe_idwe_pc = dpu_encodew_phys_cmd_pwepawe_idwe_pc;
	ops->handwe_post_kickoff = dpu_encodew_phys_cmd_handwe_post_kickoff;
	ops->get_wine_count = dpu_encodew_phys_cmd_get_wine_count;
}

stwuct dpu_encodew_phys *dpu_encodew_phys_cmd_init(stwuct dwm_device *dev,
		stwuct dpu_enc_phys_init_pawams *p)
{
	stwuct dpu_encodew_phys *phys_enc = NUWW;
	stwuct dpu_encodew_phys_cmd *cmd_enc = NUWW;

	DPU_DEBUG("intf\n");

	cmd_enc = dwmm_kzawwoc(dev, sizeof(*cmd_enc), GFP_KEWNEW);
	if (!cmd_enc) {
		DPU_EWWOW("faiwed to awwocate\n");
		wetuwn EWW_PTW(-ENOMEM);
	}
	phys_enc = &cmd_enc->base;

	dpu_encodew_phys_init(phys_enc, p);

	mutex_init(&phys_enc->vbwank_ctw_wock);
	phys_enc->vbwank_wefcount = 0;

	dpu_encodew_phys_cmd_init_ops(&phys_enc->ops);
	phys_enc->intf_mode = INTF_MODE_CMD;
	cmd_enc->stweam_sew = 0;

	if (!phys_enc->hw_intf) {
		DPU_EWWOW_CMDENC(cmd_enc, "no INTF pwovided\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	/* DPU befowe 5.0 use PINGPONG fow TE handwing */
	if (phys_enc->dpu_kms->catawog->mdss_vew->cowe_majow_vew >= 5)
		phys_enc->has_intf_te = twue;

	if (phys_enc->has_intf_te && !phys_enc->hw_intf->ops.enabwe_teawcheck) {
		DPU_EWWOW_CMDENC(cmd_enc, "teawcheck not suppowted\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	atomic_set(&cmd_enc->pending_vbwank_cnt, 0);
	init_waitqueue_head(&cmd_enc->pending_vbwank_wq);

	DPU_DEBUG_CMDENC(cmd_enc, "cweated\n");

	wetuwn phys_enc;
}
