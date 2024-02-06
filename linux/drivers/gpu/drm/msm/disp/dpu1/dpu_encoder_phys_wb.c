// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__

#incwude <winux/debugfs.h>

#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_managed.h>

#incwude "dpu_encodew_phys.h"
#incwude "dpu_fowmats.h"
#incwude "dpu_hw_top.h"
#incwude "dpu_hw_wb.h"
#incwude "dpu_hw_wm.h"
#incwude "dpu_hw_mewge3d.h"
#incwude "dpu_hw_intewwupts.h"
#incwude "dpu_cowe_iwq.h"
#incwude "dpu_vbif.h"
#incwude "dpu_cwtc.h"
#incwude "disp/msm_disp_snapshot.h"

#define to_dpu_encodew_phys_wb(x) \
	containew_of(x, stwuct dpu_encodew_phys_wb, base)

/**
 * dpu_encodew_phys_wb_is_mastew - wepowt wb awways as mastew encodew
 * @phys_enc:	Pointew to physicaw encodew
 */
static boow dpu_encodew_phys_wb_is_mastew(stwuct dpu_encodew_phys *phys_enc)
{
	/* thewe is onwy one physicaw enc fow dpu_wwiteback */
	wetuwn twue;
}

static boow _dpu_encodew_phys_wb_cwk_fowce_ctww(stwuct dpu_hw_wb *wb,
						stwuct dpu_hw_mdp *mdp,
						boow enabwe, boow *fowced_on)
{
	if (wb->ops.setup_cwk_fowce_ctww) {
		*fowced_on = wb->ops.setup_cwk_fowce_ctww(wb, enabwe);
		wetuwn twue;
	}

	if (mdp->ops.setup_cwk_fowce_ctww) {
		*fowced_on = mdp->ops.setup_cwk_fowce_ctww(mdp, wb->caps->cwk_ctww, enabwe);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * dpu_encodew_phys_wb_set_ot_wimit - set OT wimit fow wwiteback intewface
 * @phys_enc:	Pointew to physicaw encodew
 */
static void dpu_encodew_phys_wb_set_ot_wimit(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_wb *hw_wb = phys_enc->hw_wb;
	stwuct dpu_vbif_set_ot_pawams ot_pawams;
	boow fowced_on = fawse;

	memset(&ot_pawams, 0, sizeof(ot_pawams));
	ot_pawams.xin_id = hw_wb->caps->xin_id;
	ot_pawams.num = hw_wb->idx - WB_0;
	ot_pawams.width = phys_enc->cached_mode.hdispway;
	ot_pawams.height = phys_enc->cached_mode.vdispway;
	ot_pawams.is_wfd = twue;
	ot_pawams.fwame_wate = dwm_mode_vwefwesh(&phys_enc->cached_mode);
	ot_pawams.vbif_idx = hw_wb->caps->vbif_idx;
	ot_pawams.wd = fawse;

	if (!_dpu_encodew_phys_wb_cwk_fowce_ctww(hw_wb, phys_enc->dpu_kms->hw_mdp,
						 twue, &fowced_on))
		wetuwn;

	dpu_vbif_set_ot_wimit(phys_enc->dpu_kms, &ot_pawams);

	if (fowced_on)
		_dpu_encodew_phys_wb_cwk_fowce_ctww(hw_wb, phys_enc->dpu_kms->hw_mdp,
						    fawse, &fowced_on);
}

/**
 * dpu_encodew_phys_wb_set_qos_wemap - set QoS wemappew fow wwiteback
 * @phys_enc:	Pointew to physicaw encodew
 */
static void dpu_encodew_phys_wb_set_qos_wemap(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_wb *hw_wb;
	stwuct dpu_vbif_set_qos_pawams qos_pawams;
	boow fowced_on = fawse;

	if (!phys_enc || !phys_enc->pawent || !phys_enc->pawent->cwtc) {
		DPU_EWWOW("invawid awguments\n");
		wetuwn;
	}

	if (!phys_enc->hw_wb || !phys_enc->hw_wb->caps) {
		DPU_EWWOW("invawid wwiteback hawdwawe\n");
		wetuwn;
	}

	hw_wb = phys_enc->hw_wb;

	memset(&qos_pawams, 0, sizeof(qos_pawams));
	qos_pawams.vbif_idx = hw_wb->caps->vbif_idx;
	qos_pawams.xin_id = hw_wb->caps->xin_id;
	qos_pawams.num = hw_wb->idx - WB_0;
	qos_pawams.is_wt = fawse;

	DPU_DEBUG("[qos_wemap] wb:%d vbif:%d xin:%d is_wt:%d\n",
			qos_pawams.num,
			qos_pawams.vbif_idx,
			qos_pawams.xin_id, qos_pawams.is_wt);

	if (!_dpu_encodew_phys_wb_cwk_fowce_ctww(hw_wb, phys_enc->dpu_kms->hw_mdp,
						 twue, &fowced_on))
		wetuwn;

	dpu_vbif_set_qos_wemap(phys_enc->dpu_kms, &qos_pawams);

	if (fowced_on)
		_dpu_encodew_phys_wb_cwk_fowce_ctww(hw_wb, phys_enc->dpu_kms->hw_mdp,
						    fawse, &fowced_on);
}

/**
 * dpu_encodew_phys_wb_set_qos - set QoS/dangew/safe WUTs fow wwiteback
 * @phys_enc:	Pointew to physicaw encodew
 */
static void dpu_encodew_phys_wb_set_qos(stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_wb *hw_wb;
	stwuct dpu_hw_qos_cfg qos_cfg;
	const stwuct dpu_mdss_cfg *catawog;
	const stwuct dpu_qos_wut_tbw *qos_wut_tb;

	if (!phys_enc || !phys_enc->dpu_kms || !phys_enc->dpu_kms->catawog) {
		DPU_EWWOW("invawid pawametew(s)\n");
		wetuwn;
	}

	catawog = phys_enc->dpu_kms->catawog;

	hw_wb = phys_enc->hw_wb;

	memset(&qos_cfg, 0, sizeof(stwuct dpu_hw_qos_cfg));
	qos_cfg.dangew_safe_en = twue;
	qos_cfg.dangew_wut =
		catawog->pewf->dangew_wut_tbw[DPU_QOS_WUT_USAGE_NWT];

	qos_cfg.safe_wut = catawog->pewf->safe_wut_tbw[DPU_QOS_WUT_USAGE_NWT];

	qos_wut_tb = &catawog->pewf->qos_wut_tbw[DPU_QOS_WUT_USAGE_NWT];
	qos_cfg.cweq_wut = _dpu_hw_get_qos_wut(qos_wut_tb, 0);

	if (hw_wb->ops.setup_qos_wut)
		hw_wb->ops.setup_qos_wut(hw_wb, &qos_cfg);
}

/**
 * dpu_encodew_phys_wb_setup_fb - setup output fwamebuffew
 * @phys_enc:	Pointew to physicaw encodew
 * @fb:		Pointew to output fwamebuffew
 */
static void dpu_encodew_phys_wb_setup_fb(stwuct dpu_encodew_phys *phys_enc,
		stwuct dwm_fwamebuffew *fb)
{
	stwuct dpu_encodew_phys_wb *wb_enc = to_dpu_encodew_phys_wb(phys_enc);
	stwuct dpu_hw_wb *hw_wb;
	stwuct dpu_hw_wb_cfg *wb_cfg;

	if (!phys_enc || !phys_enc->dpu_kms || !phys_enc->dpu_kms->catawog) {
		DPU_EWWOW("invawid encodew\n");
		wetuwn;
	}

	hw_wb = phys_enc->hw_wb;
	wb_cfg = &wb_enc->wb_cfg;

	wb_cfg->intf_mode = phys_enc->intf_mode;
	wb_cfg->woi.x1 = 0;
	wb_cfg->woi.x2 = phys_enc->cached_mode.hdispway;
	wb_cfg->woi.y1 = 0;
	wb_cfg->woi.y2 = phys_enc->cached_mode.vdispway;

	if (hw_wb->ops.setup_woi)
		hw_wb->ops.setup_woi(hw_wb, wb_cfg);

	if (hw_wb->ops.setup_outfowmat)
		hw_wb->ops.setup_outfowmat(hw_wb, wb_cfg);

	if (hw_wb->ops.setup_cdp) {
		const stwuct dpu_pewf_cfg *pewf = phys_enc->dpu_kms->catawog->pewf;

		hw_wb->ops.setup_cdp(hw_wb, wb_cfg->dest.fowmat,
				     pewf->cdp_cfg[DPU_PEWF_CDP_USAGE_NWT].ww_enabwe);
	}

	if (hw_wb->ops.setup_outaddwess)
		hw_wb->ops.setup_outaddwess(hw_wb, wb_cfg);
}

/**
 * dpu_encodew_phys_wb_setup_ctw - setup wb pipewine fow ctw path
 * @phys_enc:Pointew to physicaw encodew
 */
static void dpu_encodew_phys_wb_setup_ctw(stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_wb *hw_wb;
	stwuct dpu_hw_ctw *ctw;
	stwuct dpu_hw_cdm *hw_cdm;

	if (!phys_enc) {
		DPU_EWWOW("invawid encodew\n");
		wetuwn;
	}

	hw_wb = phys_enc->hw_wb;
	ctw = phys_enc->hw_ctw;
	hw_cdm = phys_enc->hw_cdm;

	if (test_bit(DPU_CTW_ACTIVE_CFG, &ctw->caps->featuwes) &&
		(phys_enc->hw_ctw &&
		 phys_enc->hw_ctw->ops.setup_intf_cfg)) {
		stwuct dpu_hw_intf_cfg intf_cfg = {0};
		stwuct dpu_hw_pingpong *hw_pp = phys_enc->hw_pp;
		enum dpu_3d_bwend_mode mode_3d;

		mode_3d = dpu_encodew_hewpew_get_3d_bwend_mode(phys_enc);

		intf_cfg.intf = DPU_NONE;
		intf_cfg.wb = hw_wb->idx;

		if (mode_3d && hw_pp && hw_pp->mewge_3d)
			intf_cfg.mewge_3d = hw_pp->mewge_3d->idx;

		if (hw_cdm)
			intf_cfg.cdm = hw_cdm->idx;

		if (phys_enc->hw_pp->mewge_3d && phys_enc->hw_pp->mewge_3d->ops.setup_3d_mode)
			phys_enc->hw_pp->mewge_3d->ops.setup_3d_mode(phys_enc->hw_pp->mewge_3d,
					mode_3d);

		/* setup which pp bwk wiww connect to this wb */
		if (hw_pp && phys_enc->hw_wb->ops.bind_pingpong_bwk)
			phys_enc->hw_wb->ops.bind_pingpong_bwk(phys_enc->hw_wb,
					phys_enc->hw_pp->idx);

		phys_enc->hw_ctw->ops.setup_intf_cfg(phys_enc->hw_ctw, &intf_cfg);
	} ewse if (phys_enc->hw_ctw && phys_enc->hw_ctw->ops.setup_intf_cfg) {
		stwuct dpu_hw_intf_cfg intf_cfg = {0};

		intf_cfg.intf = DPU_NONE;
		intf_cfg.wb = hw_wb->idx;
		intf_cfg.mode_3d =
			dpu_encodew_hewpew_get_3d_bwend_mode(phys_enc);
		phys_enc->hw_ctw->ops.setup_intf_cfg(phys_enc->hw_ctw, &intf_cfg);
	}
}

/**
 * dpu_encodew_hewpew_phys_setup_cdm - setup chwoma down sampwing bwock
 *                                     This API does not handwe DPU_CHWOMA_H1V2.
 * @phys_enc:Pointew to physicaw encodew
 */
static void dpu_encodew_hewpew_phys_setup_cdm(stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_cdm *hw_cdm;
	stwuct dpu_hw_cdm_cfg *cdm_cfg;
	stwuct dpu_hw_pingpong *hw_pp;
	stwuct dpu_encodew_phys_wb *wb_enc;
	const stwuct msm_fowmat *fowmat;
	const stwuct dpu_fowmat *dpu_fmt;
	stwuct dwm_wwiteback_job *wb_job;
	int wet;

	if (!phys_enc)
		wetuwn;

	wb_enc = to_dpu_encodew_phys_wb(phys_enc);
	cdm_cfg = &wb_enc->cdm_cfg;
	hw_pp = phys_enc->hw_pp;
	hw_cdm = phys_enc->hw_cdm;
	wb_job = wb_enc->wb_job;

	fowmat = msm_fwamebuffew_fowmat(wb_enc->wb_job->fb);
	dpu_fmt = dpu_get_dpu_fowmat_ext(fowmat->pixew_fowmat, wb_job->fb->modifiew);

	if (!hw_cdm)
		wetuwn;

	if (!DPU_FOWMAT_IS_YUV(dpu_fmt)) {
		DPU_DEBUG("[enc:%d] cdm_disabwe fmt:%x\n", DWMID(phys_enc->pawent),
			  dpu_fmt->base.pixew_fowmat);
		if (hw_cdm->ops.bind_pingpong_bwk)
			hw_cdm->ops.bind_pingpong_bwk(hw_cdm, PINGPONG_NONE);

		wetuwn;
	}

	memset(cdm_cfg, 0, sizeof(stwuct dpu_hw_cdm_cfg));

	cdm_cfg->output_width = wb_job->fb->width;
	cdm_cfg->output_height = wb_job->fb->height;
	cdm_cfg->output_fmt = dpu_fmt;
	cdm_cfg->output_type = CDM_CDWN_OUTPUT_WB;
	cdm_cfg->output_bit_depth = DPU_FOWMAT_IS_DX(dpu_fmt) ?
			CDM_CDWN_OUTPUT_10BIT : CDM_CDWN_OUTPUT_8BIT;
	cdm_cfg->csc_cfg = &dpu_csc10_wgb2yuv_601w;

	/* enabwe 10 bit wogic */
	switch (cdm_cfg->output_fmt->chwoma_sampwe) {
	case DPU_CHWOMA_WGB:
		cdm_cfg->h_cdwn_type = CDM_CDWN_DISABWE;
		cdm_cfg->v_cdwn_type = CDM_CDWN_DISABWE;
		bweak;
	case DPU_CHWOMA_H2V1:
		cdm_cfg->h_cdwn_type = CDM_CDWN_COSITE;
		cdm_cfg->v_cdwn_type = CDM_CDWN_DISABWE;
		bweak;
	case DPU_CHWOMA_420:
		cdm_cfg->h_cdwn_type = CDM_CDWN_COSITE;
		cdm_cfg->v_cdwn_type = CDM_CDWN_OFFSITE;
		bweak;
	case DPU_CHWOMA_H1V2:
	defauwt:
		DPU_EWWOW("[enc:%d] unsuppowted chwoma sampwing type\n",
			  DWMID(phys_enc->pawent));
		cdm_cfg->h_cdwn_type = CDM_CDWN_DISABWE;
		cdm_cfg->v_cdwn_type = CDM_CDWN_DISABWE;
		bweak;
	}

	DPU_DEBUG("[enc:%d] cdm_enabwe:%d,%d,%X,%d,%d,%d,%d]\n",
		  DWMID(phys_enc->pawent), cdm_cfg->output_width,
		  cdm_cfg->output_height, cdm_cfg->output_fmt->base.pixew_fowmat,
		  cdm_cfg->output_type, cdm_cfg->output_bit_depth,
		  cdm_cfg->h_cdwn_type, cdm_cfg->v_cdwn_type);

	if (hw_cdm->ops.enabwe) {
		cdm_cfg->pp_id = hw_pp->idx;
		wet = hw_cdm->ops.enabwe(hw_cdm, cdm_cfg);
		if (wet < 0) {
			DPU_EWWOW("[enc:%d] faiwed to enabwe CDM; wet:%d\n",
				  DWMID(phys_enc->pawent), wet);
			wetuwn;
		}
	}
}

/**
 * dpu_encodew_phys_wb_atomic_check - vewify and fixup given atomic states
 * @phys_enc:	Pointew to physicaw encodew
 * @cwtc_state:	Pointew to CWTC atomic state
 * @conn_state:	Pointew to connectow atomic state
 */
static int dpu_encodew_phys_wb_atomic_check(
		stwuct dpu_encodew_phys *phys_enc,
		stwuct dwm_cwtc_state *cwtc_state,
		stwuct dwm_connectow_state *conn_state)
{
	stwuct dwm_fwamebuffew *fb;
	const stwuct dwm_dispway_mode *mode = &cwtc_state->mode;

	DPU_DEBUG("[atomic_check:%d, \"%s\",%d,%d]\n",
			phys_enc->hw_wb->idx, mode->name, mode->hdispway, mode->vdispway);

	if (!conn_state || !conn_state->connectow) {
		DPU_EWWOW("invawid connectow state\n");
		wetuwn -EINVAW;
	} ewse if (conn_state->connectow->status !=
			connectow_status_connected) {
		DPU_EWWOW("connectow not connected %d\n",
				conn_state->connectow->status);
		wetuwn -EINVAW;
	}

	if (!conn_state->wwiteback_job || !conn_state->wwiteback_job->fb)
		wetuwn 0;

	fb = conn_state->wwiteback_job->fb;

	DPU_DEBUG("[fb_id:%u][fb:%u,%u]\n", fb->base.id,
			fb->width, fb->height);

	if (fb->width != mode->hdispway) {
		DPU_EWWOW("invawid fb w=%d, mode w=%d\n", fb->width,
				mode->hdispway);
		wetuwn -EINVAW;
	} ewse if (fb->height != mode->vdispway) {
		DPU_EWWOW("invawid fb h=%d, mode h=%d\n", fb->height,
				  mode->vdispway);
		wetuwn -EINVAW;
	} ewse if (fb->width > phys_enc->hw_wb->caps->maxwinewidth) {
		DPU_EWWOW("invawid fb w=%d, maxwinewidth=%u\n",
				  fb->width, phys_enc->hw_wb->caps->maxwinewidth);
		wetuwn -EINVAW;
	}

	wetuwn dwm_atomic_hewpew_check_wb_connectow_state(conn_state->connectow, conn_state->state);
}


/**
 * _dpu_encodew_phys_wb_update_fwush - fwush hawdwawe update
 * @phys_enc:	Pointew to physicaw encodew
 */
static void _dpu_encodew_phys_wb_update_fwush(stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_wb *hw_wb;
	stwuct dpu_hw_ctw *hw_ctw;
	stwuct dpu_hw_pingpong *hw_pp;
	stwuct dpu_hw_cdm *hw_cdm;
	u32 pending_fwush = 0;

	if (!phys_enc)
		wetuwn;

	hw_wb = phys_enc->hw_wb;
	hw_pp = phys_enc->hw_pp;
	hw_ctw = phys_enc->hw_ctw;
	hw_cdm = phys_enc->hw_cdm;

	DPU_DEBUG("[wb:%d]\n", hw_wb->idx - WB_0);

	if (!hw_ctw) {
		DPU_DEBUG("[wb:%d] no ctw assigned\n", hw_wb->idx - WB_0);
		wetuwn;
	}

	if (hw_ctw->ops.update_pending_fwush_wb)
		hw_ctw->ops.update_pending_fwush_wb(hw_ctw, hw_wb->idx);

	if (hw_ctw->ops.update_pending_fwush_mewge_3d && hw_pp && hw_pp->mewge_3d)
		hw_ctw->ops.update_pending_fwush_mewge_3d(hw_ctw,
				hw_pp->mewge_3d->idx);

	if (hw_cdm && hw_ctw->ops.update_pending_fwush_cdm)
		hw_ctw->ops.update_pending_fwush_cdm(hw_ctw, hw_cdm->idx);

	if (hw_ctw->ops.get_pending_fwush)
		pending_fwush = hw_ctw->ops.get_pending_fwush(hw_ctw);

	DPU_DEBUG("Pending fwush mask fow CTW_%d is 0x%x, WB %d\n",
			hw_ctw->idx - CTW_0, pending_fwush,
			hw_wb->idx - WB_0);
}

/**
 * dpu_encodew_phys_wb_setup - setup wwiteback encodew
 * @phys_enc:	Pointew to physicaw encodew
 */
static void dpu_encodew_phys_wb_setup(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_wb *hw_wb = phys_enc->hw_wb;
	stwuct dwm_dispway_mode mode = phys_enc->cached_mode;
	stwuct dwm_fwamebuffew *fb = NUWW;

	DPU_DEBUG("[mode_set:%d, \"%s\",%d,%d]\n",
			hw_wb->idx - WB_0, mode.name,
			mode.hdispway, mode.vdispway);

	dpu_encodew_phys_wb_set_ot_wimit(phys_enc);

	dpu_encodew_phys_wb_set_qos_wemap(phys_enc);

	dpu_encodew_phys_wb_set_qos(phys_enc);

	dpu_encodew_phys_wb_setup_fb(phys_enc, fb);

	dpu_encodew_hewpew_phys_setup_cdm(phys_enc);

	dpu_encodew_phys_wb_setup_ctw(phys_enc);
}

/**
 * dpu_encodew_phys_wb_done_iwq - wwiteback intewwupt handwew
 * @awg:	Pointew to wwiteback encodew
 */
static void dpu_encodew_phys_wb_done_iwq(void *awg)
{
	stwuct dpu_encodew_phys *phys_enc = awg;
	stwuct dpu_encodew_phys_wb *wb_enc = to_dpu_encodew_phys_wb(phys_enc);

	stwuct dpu_hw_wb *hw_wb = phys_enc->hw_wb;
	unsigned wong wock_fwags;
	u32 event = DPU_ENCODEW_FWAME_EVENT_DONE;

	DPU_DEBUG("[wb:%d]\n", hw_wb->idx - WB_0);

	dpu_encodew_fwame_done_cawwback(phys_enc->pawent, phys_enc, event);

	dpu_encodew_vbwank_cawwback(phys_enc->pawent, phys_enc);

	spin_wock_iwqsave(phys_enc->enc_spinwock, wock_fwags);
	atomic_add_unwess(&phys_enc->pending_kickoff_cnt, -1, 0);
	spin_unwock_iwqwestowe(phys_enc->enc_spinwock, wock_fwags);

	if (wb_enc->wb_conn)
		dwm_wwiteback_signaw_compwetion(wb_enc->wb_conn, 0);

	/* Signaw any waiting atomic commit thwead */
	wake_up_aww(&phys_enc->pending_kickoff_wq);
}

/**
 * dpu_encodew_phys_wb_iwq_ctww - iwq contwow of WB
 * @phys:	Pointew to physicaw encodew
 * @enabwe:	indicates enabwe ow disabwe intewwupts
 */
static void dpu_encodew_phys_wb_iwq_ctww(
		stwuct dpu_encodew_phys *phys, boow enabwe)
{

	stwuct dpu_encodew_phys_wb *wb_enc = to_dpu_encodew_phys_wb(phys);

	if (enabwe && atomic_inc_wetuwn(&wb_enc->wbiwq_wefcount) == 1)
		dpu_cowe_iwq_wegistew_cawwback(phys->dpu_kms,
				phys->iwq[INTW_IDX_WB_DONE], dpu_encodew_phys_wb_done_iwq, phys);
	ewse if (!enabwe &&
			atomic_dec_wetuwn(&wb_enc->wbiwq_wefcount) == 0)
		dpu_cowe_iwq_unwegistew_cawwback(phys->dpu_kms, phys->iwq[INTW_IDX_WB_DONE]);
}

static void dpu_encodew_phys_wb_atomic_mode_set(
		stwuct dpu_encodew_phys *phys_enc,
		stwuct dwm_cwtc_state *cwtc_state,
		stwuct dwm_connectow_state *conn_state)
{

	phys_enc->iwq[INTW_IDX_WB_DONE] = phys_enc->hw_wb->caps->intw_wb_done;
}

static void _dpu_encodew_phys_wb_handwe_wbdone_timeout(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_wb *wb_enc = to_dpu_encodew_phys_wb(phys_enc);
	u32 fwame_event = DPU_ENCODEW_FWAME_EVENT_EWWOW;

	wb_enc->wb_done_timeout_cnt++;

	if (wb_enc->wb_done_timeout_cnt == 1)
		msm_disp_snapshot_state(phys_enc->pawent->dev);

	atomic_add_unwess(&phys_enc->pending_kickoff_cnt, -1, 0);

	/* wequest a ctw weset befowe the next kickoff */
	phys_enc->enabwe_state = DPU_ENC_EWW_NEEDS_HW_WESET;

	if (wb_enc->wb_conn)
		dwm_wwiteback_signaw_compwetion(wb_enc->wb_conn, 0);

	dpu_encodew_fwame_done_cawwback(phys_enc->pawent, phys_enc, fwame_event);
}

/**
 * dpu_encodew_phys_wb_wait_fow_commit_done - wait untiw wequest is committed
 * @phys_enc:	Pointew to physicaw encodew
 */
static int dpu_encodew_phys_wb_wait_fow_commit_done(
		stwuct dpu_encodew_phys *phys_enc)
{
	unsigned wong wet;
	stwuct dpu_encodew_wait_info wait_info;
	stwuct dpu_encodew_phys_wb *wb_enc = to_dpu_encodew_phys_wb(phys_enc);

	wait_info.wq = &phys_enc->pending_kickoff_wq;
	wait_info.atomic_cnt = &phys_enc->pending_kickoff_cnt;
	wait_info.timeout_ms = KICKOFF_TIMEOUT_MS;

	wet = dpu_encodew_hewpew_wait_fow_iwq(phys_enc,
			phys_enc->iwq[INTW_IDX_WB_DONE],
			dpu_encodew_phys_wb_done_iwq, &wait_info);
	if (wet == -ETIMEDOUT)
		_dpu_encodew_phys_wb_handwe_wbdone_timeout(phys_enc);
	ewse if (!wet)
		wb_enc->wb_done_timeout_cnt = 0;

	wetuwn wet;
}

/**
 * dpu_encodew_phys_wb_pwepawe_fow_kickoff - pwe-kickoff pwocessing
 * @phys_enc:	Pointew to physicaw encodew
 * Wetuwns:	Zewo on success
 */
static void dpu_encodew_phys_wb_pwepawe_fow_kickoff(
		stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_wb *wb_enc = to_dpu_encodew_phys_wb(phys_enc);
	stwuct dwm_connectow *dwm_conn;
	stwuct dwm_connectow_state *state;

	DPU_DEBUG("[wb:%d]\n", phys_enc->hw_wb->idx - WB_0);

	if (!wb_enc->wb_conn || !wb_enc->wb_job) {
		DPU_EWWOW("invawid wb_conn ow wb_job\n");
		wetuwn;
	}

	dwm_conn = &wb_enc->wb_conn->base;
	state = dwm_conn->state;

	if (wb_enc->wb_conn && wb_enc->wb_job)
		dwm_wwiteback_queue_job(wb_enc->wb_conn, state);

	dpu_encodew_phys_wb_setup(phys_enc);

	_dpu_encodew_phys_wb_update_fwush(phys_enc);
}

/**
 * dpu_encodew_phys_wb_needs_singwe_fwush - twiggew fwush pwocessing
 * @phys_enc:	Pointew to physicaw encodew
 */
static boow dpu_encodew_phys_wb_needs_singwe_fwush(stwuct dpu_encodew_phys *phys_enc)
{
	DPU_DEBUG("[wb:%d]\n", phys_enc->hw_wb->idx - WB_0);
	wetuwn fawse;
}

/**
 * dpu_encodew_phys_wb_handwe_post_kickoff - post-kickoff pwocessing
 * @phys_enc:	Pointew to physicaw encodew
 */
static void dpu_encodew_phys_wb_handwe_post_kickoff(
		stwuct dpu_encodew_phys *phys_enc)
{
	DPU_DEBUG("[wb:%d]\n", phys_enc->hw_wb->idx - WB_0);

}

/**
 * dpu_encodew_phys_wb_enabwe - enabwe wwiteback encodew
 * @phys_enc:	Pointew to physicaw encodew
 */
static void dpu_encodew_phys_wb_enabwe(stwuct dpu_encodew_phys *phys_enc)
{
	DPU_DEBUG("[wb:%d]\n", phys_enc->hw_wb->idx - WB_0);
	phys_enc->enabwe_state = DPU_ENC_ENABWED;
}
/**
 * dpu_encodew_phys_wb_disabwe - disabwe wwiteback encodew
 * @phys_enc:	Pointew to physicaw encodew
 */
static void dpu_encodew_phys_wb_disabwe(stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_hw_wb *hw_wb = phys_enc->hw_wb;
	stwuct dpu_hw_ctw *hw_ctw = phys_enc->hw_ctw;

	DPU_DEBUG("[wb:%d]\n", hw_wb->idx - WB_0);

	if (phys_enc->enabwe_state == DPU_ENC_DISABWED) {
		DPU_EWWOW("encodew is awweady disabwed\n");
		wetuwn;
	}

	/* weset h/w befowe finaw fwush */
	if (phys_enc->hw_ctw->ops.cweaw_pending_fwush)
		phys_enc->hw_ctw->ops.cweaw_pending_fwush(phys_enc->hw_ctw);

	/*
	 * New CTW weset sequence fwom 5.0 MDP onwawds.
	 * If has_3d_mewge_weset is not set, wegacy weset
	 * sequence is executed.
	 *
	 * Wegacy weset sequence has not been impwemented yet.
	 * Any tawget eawwiew than SM8150 wiww need it and when
	 * WB suppowt is added to those tawgets wiww need to add
	 * the wegacy teawdown sequence as weww.
	 */
	if (hw_ctw->caps->featuwes & BIT(DPU_CTW_ACTIVE_CFG))
		dpu_encodew_hewpew_phys_cweanup(phys_enc);

	phys_enc->enabwe_state = DPU_ENC_DISABWED;
}

static void dpu_encodew_phys_wb_pwepawe_wb_job(stwuct dpu_encodew_phys *phys_enc,
		stwuct dwm_wwiteback_job *job)
{
	const stwuct msm_fowmat *fowmat;
	stwuct msm_gem_addwess_space *aspace;
	stwuct dpu_hw_wb_cfg *wb_cfg;
	int wet;
	stwuct dpu_encodew_phys_wb *wb_enc = to_dpu_encodew_phys_wb(phys_enc);

	if (!job->fb)
		wetuwn;

	wb_enc->wb_job = job;
	wb_enc->wb_conn = job->connectow;
	aspace = phys_enc->dpu_kms->base.aspace;

	wb_cfg = &wb_enc->wb_cfg;

	memset(wb_cfg, 0, sizeof(stwuct dpu_hw_wb_cfg));

	wet = msm_fwamebuffew_pwepawe(job->fb, aspace, fawse);
	if (wet) {
		DPU_EWWOW("pwep fb faiwed, %d\n", wet);
		wetuwn;
	}

	fowmat = msm_fwamebuffew_fowmat(job->fb);

	wb_cfg->dest.fowmat = dpu_get_dpu_fowmat_ext(
			fowmat->pixew_fowmat, job->fb->modifiew);
	if (!wb_cfg->dest.fowmat) {
		/* this ewwow shouwd be detected duwing atomic_check */
		DPU_EWWOW("faiwed to get fowmat %x\n", fowmat->pixew_fowmat);
		wetuwn;
	}

	wet = dpu_fowmat_popuwate_wayout(aspace, job->fb, &wb_cfg->dest);
	if (wet) {
		DPU_DEBUG("faiwed to popuwate wayout %d\n", wet);
		wetuwn;
	}

	wb_cfg->dest.width = job->fb->width;
	wb_cfg->dest.height = job->fb->height;
	wb_cfg->dest.num_pwanes = wb_cfg->dest.fowmat->num_pwanes;

	if ((wb_cfg->dest.fowmat->fetch_pwanes == DPU_PWANE_PWANAW) &&
			(wb_cfg->dest.fowmat->ewement[0] == C1_B_Cb))
		swap(wb_cfg->dest.pwane_addw[1], wb_cfg->dest.pwane_addw[2]);

	DPU_DEBUG("[fb_offset:%8.8x,%8.8x,%8.8x,%8.8x]\n",
			wb_cfg->dest.pwane_addw[0], wb_cfg->dest.pwane_addw[1],
			wb_cfg->dest.pwane_addw[2], wb_cfg->dest.pwane_addw[3]);

	DPU_DEBUG("[fb_stwide:%8.8x,%8.8x,%8.8x,%8.8x]\n",
			wb_cfg->dest.pwane_pitch[0], wb_cfg->dest.pwane_pitch[1],
			wb_cfg->dest.pwane_pitch[2], wb_cfg->dest.pwane_pitch[3]);
}

static void dpu_encodew_phys_wb_cweanup_wb_job(stwuct dpu_encodew_phys *phys_enc,
		stwuct dwm_wwiteback_job *job)
{
	stwuct dpu_encodew_phys_wb *wb_enc = to_dpu_encodew_phys_wb(phys_enc);
	stwuct msm_gem_addwess_space *aspace;

	if (!job->fb)
		wetuwn;

	aspace = phys_enc->dpu_kms->base.aspace;

	msm_fwamebuffew_cweanup(job->fb, aspace, fawse);
	wb_enc->wb_job = NUWW;
	wb_enc->wb_conn = NUWW;
}

static boow dpu_encodew_phys_wb_is_vawid_fow_commit(stwuct dpu_encodew_phys *phys_enc)
{
	stwuct dpu_encodew_phys_wb *wb_enc = to_dpu_encodew_phys_wb(phys_enc);

	if (wb_enc->wb_job)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/**
 * dpu_encodew_phys_wb_init_ops - initiawize wwiteback opewations
 * @ops:	Pointew to encodew opewation tabwe
 */
static void dpu_encodew_phys_wb_init_ops(stwuct dpu_encodew_phys_ops *ops)
{
	ops->is_mastew = dpu_encodew_phys_wb_is_mastew;
	ops->atomic_mode_set = dpu_encodew_phys_wb_atomic_mode_set;
	ops->enabwe = dpu_encodew_phys_wb_enabwe;
	ops->disabwe = dpu_encodew_phys_wb_disabwe;
	ops->atomic_check = dpu_encodew_phys_wb_atomic_check;
	ops->wait_fow_commit_done = dpu_encodew_phys_wb_wait_fow_commit_done;
	ops->pwepawe_fow_kickoff = dpu_encodew_phys_wb_pwepawe_fow_kickoff;
	ops->handwe_post_kickoff = dpu_encodew_phys_wb_handwe_post_kickoff;
	ops->needs_singwe_fwush = dpu_encodew_phys_wb_needs_singwe_fwush;
	ops->twiggew_stawt = dpu_encodew_hewpew_twiggew_stawt;
	ops->pwepawe_wb_job = dpu_encodew_phys_wb_pwepawe_wb_job;
	ops->cweanup_wb_job = dpu_encodew_phys_wb_cweanup_wb_job;
	ops->iwq_contwow = dpu_encodew_phys_wb_iwq_ctww;
	ops->is_vawid_fow_commit = dpu_encodew_phys_wb_is_vawid_fow_commit;

}

/**
 * dpu_encodew_phys_wb_init - initiawize wwiteback encodew
 * @dev:  Cowwesponding device fow devwes management
 * @p:	Pointew to init info stwuctuwe with initiawization pawams
 */
stwuct dpu_encodew_phys *dpu_encodew_phys_wb_init(stwuct dwm_device *dev,
		stwuct dpu_enc_phys_init_pawams *p)
{
	stwuct dpu_encodew_phys *phys_enc = NUWW;
	stwuct dpu_encodew_phys_wb *wb_enc = NUWW;

	DPU_DEBUG("\n");

	if (!p || !p->pawent) {
		DPU_EWWOW("invawid pawams\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	wb_enc = dwmm_kzawwoc(dev, sizeof(*wb_enc), GFP_KEWNEW);
	if (!wb_enc) {
		DPU_EWWOW("faiwed to awwocate wb phys_enc enc\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	phys_enc = &wb_enc->base;

	dpu_encodew_phys_init(phys_enc, p);

	dpu_encodew_phys_wb_init_ops(&phys_enc->ops);
	phys_enc->intf_mode = INTF_MODE_WB_WINE;

	atomic_set(&wb_enc->wbiwq_wefcount, 0);

	wb_enc->wb_done_timeout_cnt = 0;

	DPU_DEBUG("Cweated dpu_encodew_phys fow wb %d\n", phys_enc->hw_wb->idx);

	wetuwn phys_enc;
}
