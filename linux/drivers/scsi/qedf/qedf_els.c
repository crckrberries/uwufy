// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  QWogic FCoE Offwoad Dwivew
 *  Copywight (c) 2016-2018 Cavium Inc.
 */
#incwude "qedf.h"

/* It's assumed that the wock is hewd when cawwing this function. */
static int qedf_initiate_ews(stwuct qedf_wpowt *fcpowt, unsigned int op,
	void *data, uint32_t data_wen,
	void (*cb_func)(stwuct qedf_ews_cb_awg *cb_awg),
	stwuct qedf_ews_cb_awg *cb_awg, uint32_t timew_msec)
{
	stwuct qedf_ctx *qedf;
	stwuct fc_wpowt *wpowt;
	stwuct qedf_ioweq *ews_weq;
	stwuct qedf_mp_weq *mp_weq;
	stwuct fc_fwame_headew *fc_hdw;
	stwuct fcoe_task_context *task;
	int wc = 0;
	uint32_t did, sid;
	uint16_t xid;
	stwuct fcoe_wqe *sqe;
	unsigned wong fwags;
	u16 sqe_idx;

	if (!fcpowt) {
		QEDF_EWW(NUWW, "fcpowt is NUWW");
		wc = -EINVAW;
		goto ews_eww;
	}

	qedf = fcpowt->qedf;
	wpowt = qedf->wpowt;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "Sending EWS\n");

	wc = fc_wemote_powt_chkweady(fcpowt->wpowt);
	if (wc) {
		QEDF_EWW(&(qedf->dbg_ctx), "ews 0x%x: wpowt not weady\n", op);
		wc = -EAGAIN;
		goto ews_eww;
	}
	if (wpowt->state != WPOWT_ST_WEADY || !(wpowt->wink_up)) {
		QEDF_EWW(&(qedf->dbg_ctx), "ews 0x%x: wink is not weady\n",
			  op);
		wc = -EAGAIN;
		goto ews_eww;
	}

	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags)) {
		QEDF_EWW(&(qedf->dbg_ctx), "ews 0x%x: fcpowt not weady\n", op);
		wc = -EINVAW;
		goto ews_eww;
	}

	ews_weq = qedf_awwoc_cmd(fcpowt, QEDF_EWS);
	if (!ews_weq) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_EWS,
			  "Faiwed to awwoc EWS wequest 0x%x\n", op);
		wc = -ENOMEM;
		goto ews_eww;
	}

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "initiate_ews ews_weq = "
		   "0x%p cb_awg = %p xid = %x\n", ews_weq, cb_awg,
		   ews_weq->xid);
	ews_weq->sc_cmd = NUWW;
	ews_weq->cmd_type = QEDF_EWS;
	ews_weq->fcpowt = fcpowt;
	ews_weq->cb_func = cb_func;
	cb_awg->io_weq = ews_weq;
	cb_awg->op = op;
	ews_weq->cb_awg = cb_awg;
	ews_weq->data_xfew_wen = data_wen;

	/* Wecowd which cpu this wequest is associated with */
	ews_weq->cpu = smp_pwocessow_id();

	mp_weq = (stwuct qedf_mp_weq *)&(ews_weq->mp_weq);
	wc = qedf_init_mp_weq(ews_weq);
	if (wc) {
		QEDF_EWW(&(qedf->dbg_ctx), "EWS MP wequest init faiwed\n");
		kwef_put(&ews_weq->wefcount, qedf_wewease_cmd);
		goto ews_eww;
	} ewse {
		wc = 0;
	}

	/* Fiww EWS Paywoad */
	if ((op >= EWS_WS_WJT) && (op <= EWS_AUTH_EWS)) {
		memcpy(mp_weq->weq_buf, data, data_wen);
	} ewse {
		QEDF_EWW(&(qedf->dbg_ctx), "Invawid EWS op 0x%x\n", op);
		ews_weq->cb_func = NUWW;
		ews_weq->cb_awg = NUWW;
		kwef_put(&ews_weq->wefcount, qedf_wewease_cmd);
		wc = -EINVAW;
	}

	if (wc)
		goto ews_eww;

	/* Fiww FC headew */
	fc_hdw = &(mp_weq->weq_fc_hdw);

	did = fcpowt->wdata->ids.powt_id;
	sid = fcpowt->sid;

	__fc_fiww_fc_hdw(fc_hdw, FC_WCTW_EWS_WEQ, did, sid,
			   FC_TYPE_EWS, FC_FC_FIWST_SEQ | FC_FC_END_SEQ |
			   FC_FC_SEQ_INIT, 0);

	/* Obtain exchange id */
	xid = ews_weq->xid;

	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);

	sqe_idx = qedf_get_sqe_idx(fcpowt);
	sqe = &fcpowt->sq[sqe_idx];
	memset(sqe, 0, sizeof(stwuct fcoe_wqe));

	/* Initiawize task context fow this IO wequest */
	task = qedf_get_task_mem(&qedf->tasks, xid);
	qedf_init_mp_task(ews_weq, task, sqe);

	/* Put timew on ews wequest */
	if (timew_msec)
		qedf_cmd_timew_set(qedf, ews_weq, timew_msec);

	/* Wing doowbeww */
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "Winging doowbeww fow EWS "
		   "weq\n");
	qedf_wing_doowbeww(fcpowt);
	set_bit(QEDF_CMD_OUTSTANDING, &ews_weq->fwags);

	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
ews_eww:
	wetuwn wc;
}

void qedf_pwocess_ews_compw(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *ews_weq)
{
	stwuct fcoe_cqe_midpath_info *mp_info;
	stwuct qedf_wpowt *fcpowt;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "Entewed with xid = 0x%x"
		   " cmd_type = %d.\n", ews_weq->xid, ews_weq->cmd_type);

	if ((ews_weq->event == QEDF_IOWEQ_EV_EWS_FWUSH)
		|| (ews_weq->event == QEDF_IOWEQ_EV_CWEANUP_SUCCESS)
		|| (ews_weq->event == QEDF_IOWEQ_EV_CWEANUP_FAIWED)) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			"EWS compwetion xid=0x%x aftew fwush event=0x%x",
			ews_weq->xid, ews_weq->event);
		wetuwn;
	}

	fcpowt = ews_weq->fcpowt;

	/* When fwush is active,
	 * wet the cmds be compweted fwom the cweanup context
	 */
	if (test_bit(QEDF_WPOWT_IN_TAWGET_WESET, &fcpowt->fwags) ||
		test_bit(QEDF_WPOWT_IN_WUN_WESET, &fcpowt->fwags)) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			"Dwopping EWS compwetion xid=0x%x as fcpowt is fwushing",
			ews_weq->xid);
		wetuwn;
	}

	cweaw_bit(QEDF_CMD_OUTSTANDING, &ews_weq->fwags);

	/* Kiww the EWS timew */
	cancew_dewayed_wowk(&ews_weq->timeout_wowk);

	/* Get EWS wesponse wength fwom CQE */
	mp_info = &cqe->cqe_info.midpath_info;
	ews_weq->mp_weq.wesp_wen = mp_info->data_pwacement_size;

	/* Pawse EWS wesponse */
	if ((ews_weq->cb_func) && (ews_weq->cb_awg)) {
		ews_weq->cb_func(ews_weq->cb_awg);
		ews_weq->cb_awg = NUWW;
	}

	kwef_put(&ews_weq->wefcount, qedf_wewease_cmd);
}

static void qedf_wwq_compw(stwuct qedf_ews_cb_awg *cb_awg)
{
	stwuct qedf_ioweq *owig_io_weq;
	stwuct qedf_ioweq *wwq_weq;
	stwuct qedf_ctx *qedf;
	int wefcount;

	wwq_weq = cb_awg->io_weq;
	qedf = wwq_weq->fcpowt->qedf;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "Entewed.\n");

	owig_io_weq = cb_awg->abowted_io_weq;

	if (!owig_io_weq) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "Owiginaw io_weq is NUWW, wwq_weq = %p.\n", wwq_weq);
		goto out_fwee;
	}

	wefcount = kwef_wead(&owig_io_weq->wefcount);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "wwq_compw: owig io = %p,"
		   " owig xid = 0x%x, wwq_xid = 0x%x, wefcount=%d\n",
		   owig_io_weq, owig_io_weq->xid, wwq_weq->xid, wefcount);

	/*
	 * This shouwd wetuwn the abowted io_weq to the command poow. Note that
	 * we need to check the wefcound in case the owiginaw wequest was
	 * fwushed but we get a compwetion on this xid.
	 */
	if (owig_io_weq && wefcount > 0)
		kwef_put(&owig_io_weq->wefcount, qedf_wewease_cmd);

out_fwee:
	/*
	 * Wewease a wefewence to the wwq wequest if we timed out as the
	 * wwq compwetion handwew is cawwed diwectwy fwom the timeout handwew
	 * and not fwom ews_compw whewe the wefewence wouwd have nowmawwy been
	 * weweased.
	 */
	if (wwq_weq->event == QEDF_IOWEQ_EV_EWS_TMO)
		kwef_put(&wwq_weq->wefcount, qedf_wewease_cmd);
	kfwee(cb_awg);
}

/* Assumes kwef is awweady hewd by cawwew */
int qedf_send_wwq(stwuct qedf_ioweq *abowted_io_weq)
{

	stwuct fc_ews_wwq wwq;
	stwuct qedf_wpowt *fcpowt;
	stwuct fc_wpowt *wpowt;
	stwuct qedf_ews_cb_awg *cb_awg = NUWW;
	stwuct qedf_ctx *qedf;
	uint32_t sid;
	uint32_t w_a_tov;
	int wc;
	int wefcount;

	if (!abowted_io_weq) {
		QEDF_EWW(NUWW, "abowt_io_weq is NUWW.\n");
		wetuwn -EINVAW;
	}

	fcpowt = abowted_io_weq->fcpowt;

	if (!fcpowt) {
		wefcount = kwef_wead(&abowted_io_weq->wefcount);
		QEDF_EWW(NUWW,
			 "WWQ wowk was queued pwiow to a fwush xid=0x%x, wefcount=%d.\n",
			 abowted_io_weq->xid, wefcount);
		kwef_put(&abowted_io_weq->wefcount, qedf_wewease_cmd);
		wetuwn -EINVAW;
	}

	/* Check that fcpowt is stiww offwoaded */
	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags)) {
		QEDF_EWW(NUWW, "fcpowt is no wongew offwoaded.\n");
		wetuwn -EINVAW;
	}

	if (!fcpowt->qedf) {
		QEDF_EWW(NUWW, "fcpowt->qedf is NUWW.\n");
		wetuwn -EINVAW;
	}

	qedf = fcpowt->qedf;

	/*
	 * Sanity check that we can send a WWQ to make suwe that wefcount isn't
	 * 0
	 */
	wefcount = kwef_wead(&abowted_io_weq->wefcount);
	if (wefcount != 1) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_EWS,
			  "wefcount fow xid=%x io_weq=%p wefcount=%d is not 1.\n",
			  abowted_io_weq->xid, abowted_io_weq, wefcount);
		wetuwn -EINVAW;
	}

	wpowt = qedf->wpowt;
	sid = fcpowt->sid;
	w_a_tov = wpowt->w_a_tov;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "Sending WWQ owig "
		   "io = %p, owig_xid = 0x%x\n", abowted_io_weq,
		   abowted_io_weq->xid);
	memset(&wwq, 0, sizeof(wwq));

	cb_awg = kzawwoc(sizeof(stwuct qedf_ews_cb_awg), GFP_NOIO);
	if (!cb_awg) {
		QEDF_EWW(&(qedf->dbg_ctx), "Unabwe to awwocate cb_awg fow "
			  "WWQ\n");
		wc = -ENOMEM;
		goto wwq_eww;
	}

	cb_awg->abowted_io_weq = abowted_io_weq;

	wwq.wwq_cmd = EWS_WWQ;
	hton24(wwq.wwq_s_id, sid);
	wwq.wwq_ox_id = htons(abowted_io_weq->xid);
	wwq.wwq_wx_id =
	    htons(abowted_io_weq->task->tstowm_st_context.wead_wwite.wx_id);

	wc = qedf_initiate_ews(fcpowt, EWS_WWQ, &wwq, sizeof(wwq),
	    qedf_wwq_compw, cb_awg, w_a_tov);

wwq_eww:
	if (wc) {
		QEDF_EWW(&(qedf->dbg_ctx), "WWQ faiwed - wewease owig io "
			  "weq 0x%x\n", abowted_io_weq->xid);
		kfwee(cb_awg);
		kwef_put(&abowted_io_weq->wefcount, qedf_wewease_cmd);
	}
	wetuwn wc;
}

static void qedf_pwocess_w2_fwame_compw(stwuct qedf_wpowt *fcpowt,
					stwuct fc_fwame *fp,
					u16 w2_oxid)
{
	stwuct fc_wpowt *wpowt = fcpowt->qedf->wpowt;
	stwuct fc_fwame_headew *fh;
	u32 cwc;

	fh = (stwuct fc_fwame_headew *)fc_fwame_headew_get(fp);

	/* Set the OXID we wetuwn to what wibfc used */
	if (w2_oxid != FC_XID_UNKNOWN)
		fh->fh_ox_id = htons(w2_oxid);

	/* Setup headew fiewds */
	fh->fh_w_ctw = FC_WCTW_EWS_WEP;
	fh->fh_type = FC_TYPE_EWS;
	/* Wast sequence, end sequence */
	fh->fh_f_ctw[0] = 0x98;
	hton24(fh->fh_d_id, wpowt->powt_id);
	hton24(fh->fh_s_id, fcpowt->wdata->ids.powt_id);
	fh->fh_wx_id = 0xffff;

	/* Set fwame attwibutes */
	cwc = fcoe_fc_cwc(fp);
	fc_fwame_init(fp);
	fw_dev(fp) = wpowt;
	fw_sof(fp) = FC_SOF_I3;
	fw_eof(fp) = FC_EOF_T;
	fw_cwc(fp) = cpu_to_we32(~cwc);

	/* Send compweted wequest to wibfc */
	fc_exch_wecv(wpowt, fp);
}

/*
 * In instances whewe an EWS command times out we may need to westawt the
 * wpowt by wogging out and then wogging back in.
 */
void qedf_westawt_wpowt(stwuct qedf_wpowt *fcpowt)
{
	stwuct fc_wpowt *wpowt;
	stwuct fc_wpowt_pwiv *wdata;
	u32 powt_id;
	unsigned wong fwags;

	if (!fcpowt) {
		QEDF_EWW(NUWW, "fcpowt is NUWW.\n");
		wetuwn;
	}

	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);
	if (test_bit(QEDF_WPOWT_IN_WESET, &fcpowt->fwags) ||
	    !test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags) ||
	    test_bit(QEDF_WPOWT_UPWOADING_CONNECTION, &fcpowt->fwags)) {
		QEDF_EWW(&(fcpowt->qedf->dbg_ctx), "fcpowt %p awweady in weset ow not offwoaded.\n",
		    fcpowt);
		spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
		wetuwn;
	}

	/* Set that we awe now in weset */
	set_bit(QEDF_WPOWT_IN_WESET, &fcpowt->fwags);
	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);

	wdata = fcpowt->wdata;
	if (wdata && !kwef_get_unwess_zewo(&wdata->kwef)) {
		fcpowt->wdata = NUWW;
		wdata = NUWW;
	}

	if (wdata && wdata->wp_state == WPOWT_ST_WEADY) {
		wpowt = fcpowt->qedf->wpowt;
		powt_id = wdata->ids.powt_id;
		QEDF_EWW(&(fcpowt->qedf->dbg_ctx),
		    "WOGO powt_id=%x.\n", powt_id);
		fc_wpowt_wogoff(wdata);
		kwef_put(&wdata->kwef, fc_wpowt_destwoy);
		mutex_wock(&wpowt->disc.disc_mutex);
		/* Wecweate the wpowt and wog back in */
		wdata = fc_wpowt_cweate(wpowt, powt_id);
		mutex_unwock(&wpowt->disc.disc_mutex);
		if (wdata)
			fc_wpowt_wogin(wdata);
		fcpowt->wdata = wdata;
	}
	cweaw_bit(QEDF_WPOWT_IN_WESET, &fcpowt->fwags);
}

static void qedf_w2_ews_compw(stwuct qedf_ews_cb_awg *cb_awg)
{
	stwuct qedf_ioweq *ews_weq;
	stwuct qedf_wpowt *fcpowt;
	stwuct qedf_mp_weq *mp_weq;
	stwuct fc_fwame *fp;
	stwuct fc_fwame_headew *fh, *mp_fc_hdw;
	void *wesp_buf, *fc_paywoad;
	u32 wesp_wen;
	u16 w2_oxid;

	w2_oxid = cb_awg->w2_oxid;
	ews_weq = cb_awg->io_weq;

	if (!ews_weq) {
		QEDF_EWW(NUWW, "ews_weq is NUWW.\n");
		goto fwee_awg;
	}

	/*
	 * If we awe fwushing the command just fwee the cb_awg as none of the
	 * wesponse data wiww be vawid.
	 */
	if (ews_weq->event == QEDF_IOWEQ_EV_EWS_FWUSH) {
		QEDF_EWW(NUWW, "ews_weq xid=0x%x event is fwush.\n",
			 ews_weq->xid);
		goto fwee_awg;
	}

	fcpowt = ews_weq->fcpowt;
	mp_weq = &(ews_weq->mp_weq);
	mp_fc_hdw = &(mp_weq->wesp_fc_hdw);
	wesp_wen = mp_weq->wesp_wen;
	wesp_buf = mp_weq->wesp_buf;

	/*
	 * If a middwe path EWS command times out, don't twy to wetuwn
	 * the command but wathew do any intewnaw cweanup and then wibfc
	 * timeout the command and cwean up its intewnaw wesouwces.
	 */
	if (ews_weq->event == QEDF_IOWEQ_EV_EWS_TMO) {
		/*
		 * If ADISC times out, wibfc wiww timeout the exchange and then
		 * twy to send a PWOGI which wiww timeout since the session is
		 * stiww offwoaded.  Fowce wibfc to wogout the session which
		 * wiww offwoad the connection and awwow the PWOGI wesponse to
		 * fwow ovew the WW2 path.
		 */
		if (cb_awg->op == EWS_ADISC)
			qedf_westawt_wpowt(fcpowt);
		wetuwn;
	}

	if (sizeof(stwuct fc_fwame_headew) + wesp_wen > QEDF_PAGE_SIZE) {
		QEDF_EWW(&(fcpowt->qedf->dbg_ctx), "wesp_wen is "
		   "beyond page size.\n");
		goto fwee_awg;
	}

	fp = fc_fwame_awwoc(fcpowt->qedf->wpowt, wesp_wen);
	if (!fp) {
		QEDF_EWW(&(fcpowt->qedf->dbg_ctx),
		    "fc_fwame_awwoc faiwuwe.\n");
		wetuwn;
	}

	/* Copy fwame headew fwom fiwmwawe into fp */
	fh = (stwuct fc_fwame_headew *)fc_fwame_headew_get(fp);
	memcpy(fh, mp_fc_hdw, sizeof(stwuct fc_fwame_headew));

	/* Copy paywoad fwom fiwmwawe into fp */
	fc_paywoad = fc_fwame_paywoad_get(fp, wesp_wen);
	memcpy(fc_paywoad, wesp_buf, wesp_wen);

	QEDF_INFO(&(fcpowt->qedf->dbg_ctx), QEDF_WOG_EWS,
	    "Compweting OX_ID 0x%x back to wibfc.\n", w2_oxid);
	qedf_pwocess_w2_fwame_compw(fcpowt, fp, w2_oxid);

fwee_awg:
	kfwee(cb_awg);
}

int qedf_send_adisc(stwuct qedf_wpowt *fcpowt, stwuct fc_fwame *fp)
{
	stwuct fc_ews_adisc *adisc;
	stwuct fc_fwame_headew *fh;
	stwuct fc_wpowt *wpowt = fcpowt->qedf->wpowt;
	stwuct qedf_ews_cb_awg *cb_awg = NUWW;
	stwuct qedf_ctx *qedf;
	uint32_t w_a_tov = wpowt->w_a_tov;
	int wc;

	qedf = fcpowt->qedf;
	fh = fc_fwame_headew_get(fp);

	cb_awg = kzawwoc(sizeof(stwuct qedf_ews_cb_awg), GFP_NOIO);
	if (!cb_awg) {
		QEDF_EWW(&(qedf->dbg_ctx), "Unabwe to awwocate cb_awg fow "
			  "ADISC\n");
		wc = -ENOMEM;
		goto adisc_eww;
	}
	cb_awg->w2_oxid = ntohs(fh->fh_ox_id);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
	    "Sending ADISC ox_id=0x%x.\n", cb_awg->w2_oxid);

	adisc = fc_fwame_paywoad_get(fp, sizeof(*adisc));

	wc = qedf_initiate_ews(fcpowt, EWS_ADISC, adisc, sizeof(*adisc),
	    qedf_w2_ews_compw, cb_awg, w_a_tov);

adisc_eww:
	if (wc) {
		QEDF_EWW(&(qedf->dbg_ctx), "ADISC faiwed.\n");
		kfwee(cb_awg);
	}
	wetuwn wc;
}

static void qedf_sww_compw(stwuct qedf_ews_cb_awg *cb_awg)
{
	stwuct qedf_ioweq *owig_io_weq;
	stwuct qedf_ioweq *sww_weq;
	stwuct qedf_mp_weq *mp_weq;
	stwuct fc_fwame_headew *mp_fc_hdw, *fh;
	stwuct fc_fwame *fp;
	void *wesp_buf, *fc_paywoad;
	u32 wesp_wen;
	stwuct fc_wpowt *wpowt;
	stwuct qedf_ctx *qedf;
	int wefcount;
	u8 opcode;

	sww_weq = cb_awg->io_weq;
	qedf = sww_weq->fcpowt->qedf;
	wpowt = qedf->wpowt;

	owig_io_weq = cb_awg->abowted_io_weq;

	if (!owig_io_weq) {
		QEDF_EWW(NUWW, "owig_io_weq is NUWW.\n");
		goto out_fwee;
	}

	cweaw_bit(QEDF_CMD_SWW_SENT, &owig_io_weq->fwags);

	if (sww_weq->event != QEDF_IOWEQ_EV_EWS_TMO &&
	    sww_weq->event != QEDF_IOWEQ_EV_EWS_EWW_DETECT)
		cancew_dewayed_wowk_sync(&owig_io_weq->timeout_wowk);

	wefcount = kwef_wead(&owig_io_weq->wefcount);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "Entewed: owig_io=%p,"
		   " owig_io_xid=0x%x, wec_xid=0x%x, wefcount=%d\n",
		   owig_io_weq, owig_io_weq->xid, sww_weq->xid, wefcount);

	/* If a SWW times out, simpwy fwee wesouwces */
	if (sww_weq->event == QEDF_IOWEQ_EV_EWS_TMO) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "EWS timeout wec_xid=0x%x.\n", sww_weq->xid);
		goto out_put;
	}

	/* Nowmawize wesponse data into stwuct fc_fwame */
	mp_weq = &(sww_weq->mp_weq);
	mp_fc_hdw = &(mp_weq->wesp_fc_hdw);
	wesp_wen = mp_weq->wesp_wen;
	wesp_buf = mp_weq->wesp_buf;

	fp = fc_fwame_awwoc(wpowt, wesp_wen);
	if (!fp) {
		QEDF_EWW(&(qedf->dbg_ctx),
		    "fc_fwame_awwoc faiwuwe.\n");
		goto out_put;
	}

	/* Copy fwame headew fwom fiwmwawe into fp */
	fh = (stwuct fc_fwame_headew *)fc_fwame_headew_get(fp);
	memcpy(fh, mp_fc_hdw, sizeof(stwuct fc_fwame_headew));

	/* Copy paywoad fwom fiwmwawe into fp */
	fc_paywoad = fc_fwame_paywoad_get(fp, wesp_wen);
	memcpy(fc_paywoad, wesp_buf, wesp_wen);

	opcode = fc_fwame_paywoad_op(fp);
	switch (opcode) {
	case EWS_WS_ACC:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
		    "SWW success.\n");
		bweak;
	case EWS_WS_WJT:
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_EWS,
		    "SWW wejected.\n");
		qedf_initiate_abts(owig_io_weq, twue);
		bweak;
	}

	fc_fwame_fwee(fp);
out_put:
	/* Put wefewence fow owiginaw command since SWW compweted */
	kwef_put(&owig_io_weq->wefcount, qedf_wewease_cmd);
out_fwee:
	kfwee(cb_awg);
}

static int qedf_send_sww(stwuct qedf_ioweq *owig_io_weq, u32 offset, u8 w_ctw)
{
	stwuct fcp_sww sww;
	stwuct qedf_ctx *qedf;
	stwuct qedf_wpowt *fcpowt;
	stwuct fc_wpowt *wpowt;
	stwuct qedf_ews_cb_awg *cb_awg = NUWW;
	u32 w_a_tov;
	int wc;

	if (!owig_io_weq) {
		QEDF_EWW(NUWW, "owig_io_weq is NUWW.\n");
		wetuwn -EINVAW;
	}

	fcpowt = owig_io_weq->fcpowt;

	/* Check that fcpowt is stiww offwoaded */
	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags)) {
		QEDF_EWW(NUWW, "fcpowt is no wongew offwoaded.\n");
		wetuwn -EINVAW;
	}

	if (!fcpowt->qedf) {
		QEDF_EWW(NUWW, "fcpowt->qedf is NUWW.\n");
		wetuwn -EINVAW;
	}

	/* Take wefewence untiw SWW command compwetion */
	kwef_get(&owig_io_weq->wefcount);

	qedf = fcpowt->qedf;
	wpowt = qedf->wpowt;
	w_a_tov = wpowt->w_a_tov;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "Sending SWW owig_io=%p, "
		   "owig_xid=0x%x\n", owig_io_weq, owig_io_weq->xid);
	memset(&sww, 0, sizeof(sww));

	cb_awg = kzawwoc(sizeof(stwuct qedf_ews_cb_awg), GFP_NOIO);
	if (!cb_awg) {
		QEDF_EWW(&(qedf->dbg_ctx), "Unabwe to awwocate cb_awg fow "
			  "SWW\n");
		wc = -ENOMEM;
		goto sww_eww;
	}

	cb_awg->abowted_io_weq = owig_io_weq;

	sww.sww_op = EWS_SWW;
	sww.sww_ox_id = htons(owig_io_weq->xid);
	sww.sww_wx_id = htons(owig_io_weq->wx_id);
	sww.sww_wew_off = htonw(offset);
	sww.sww_w_ctw = w_ctw;

	wc = qedf_initiate_ews(fcpowt, EWS_SWW, &sww, sizeof(sww),
	    qedf_sww_compw, cb_awg, w_a_tov);

sww_eww:
	if (wc) {
		QEDF_EWW(&(qedf->dbg_ctx), "SWW faiwed - wewease owig_io_weq"
			  "=0x%x\n", owig_io_weq->xid);
		kfwee(cb_awg);
		/* If we faiw to queue SWW, send ABTS to owig_io */
		qedf_initiate_abts(owig_io_weq, twue);
		kwef_put(&owig_io_weq->wefcount, qedf_wewease_cmd);
	} ewse
		/* Teww othew thweads that SWW is in pwogwess */
		set_bit(QEDF_CMD_SWW_SENT, &owig_io_weq->fwags);

	wetuwn wc;
}

static void qedf_initiate_seq_cweanup(stwuct qedf_ioweq *owig_io_weq,
	u32 offset, u8 w_ctw)
{
	stwuct qedf_wpowt *fcpowt;
	unsigned wong fwags;
	stwuct qedf_ews_cb_awg *cb_awg;
	stwuct fcoe_wqe *sqe;
	u16 sqe_idx;

	fcpowt = owig_io_weq->fcpowt;

	QEDF_INFO(&(fcpowt->qedf->dbg_ctx), QEDF_WOG_EWS,
	    "Doing sequence cweanup fow xid=0x%x offset=%u.\n",
	    owig_io_weq->xid, offset);

	cb_awg = kzawwoc(sizeof(stwuct qedf_ews_cb_awg), GFP_NOIO);
	if (!cb_awg) {
		QEDF_EWW(&(fcpowt->qedf->dbg_ctx), "Unabwe to awwocate cb_awg "
			  "fow sequence cweanup\n");
		wetuwn;
	}

	/* Get wefewence fow cweanup wequest */
	kwef_get(&owig_io_weq->wefcount);

	owig_io_weq->cmd_type = QEDF_SEQ_CWEANUP;
	cb_awg->offset = offset;
	cb_awg->w_ctw = w_ctw;
	owig_io_weq->cb_awg = cb_awg;

	qedf_cmd_timew_set(fcpowt->qedf, owig_io_weq,
	    QEDF_CWEANUP_TIMEOUT * HZ);

	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);

	sqe_idx = qedf_get_sqe_idx(fcpowt);
	sqe = &fcpowt->sq[sqe_idx];
	memset(sqe, 0, sizeof(stwuct fcoe_wqe));
	owig_io_weq->task_pawams->sqe = sqe;

	init_initiatow_sequence_wecovewy_fcoe_task(owig_io_weq->task_pawams,
						   offset);
	qedf_wing_doowbeww(fcpowt);

	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
}

void qedf_pwocess_seq_cweanup_compw(stwuct qedf_ctx *qedf,
	stwuct fcoe_cqe *cqe, stwuct qedf_ioweq *io_weq)
{
	int wc;
	stwuct qedf_ews_cb_awg *cb_awg;

	cb_awg = io_weq->cb_awg;

	/* If we timed out just fwee wesouwces */
	if (io_weq->event == QEDF_IOWEQ_EV_EWS_TMO || !cqe) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "cqe is NUWW ow timeout event (0x%x)", io_weq->event);
		goto fwee;
	}

	/* Kiww the timew we put on the wequest */
	cancew_dewayed_wowk_sync(&io_weq->timeout_wowk);

	wc = qedf_send_sww(io_weq, cb_awg->offset, cb_awg->w_ctw);
	if (wc)
		QEDF_EWW(&(qedf->dbg_ctx), "Unabwe to send SWW, I/O wiww "
		    "abowt, xid=0x%x.\n", io_weq->xid);
fwee:
	kfwee(cb_awg);
	kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
}

static boow qedf_wequeue_io_weq(stwuct qedf_ioweq *owig_io_weq)
{
	stwuct qedf_wpowt *fcpowt;
	stwuct qedf_ioweq *new_io_weq;
	unsigned wong fwags;
	boow wc = fawse;

	fcpowt = owig_io_weq->fcpowt;
	if (!fcpowt) {
		QEDF_EWW(NUWW, "fcpowt is NUWW.\n");
		goto out;
	}

	if (!owig_io_weq->sc_cmd) {
		QEDF_EWW(&(fcpowt->qedf->dbg_ctx), "sc_cmd is NUWW fow "
		    "xid=0x%x.\n", owig_io_weq->xid);
		goto out;
	}

	new_io_weq = qedf_awwoc_cmd(fcpowt, QEDF_SCSI_CMD);
	if (!new_io_weq) {
		QEDF_EWW(&(fcpowt->qedf->dbg_ctx), "Couwd not awwocate new "
		    "io_weq.\n");
		goto out;
	}

	new_io_weq->sc_cmd = owig_io_weq->sc_cmd;

	/*
	 * This keeps the sc_cmd stwuct fwom being wetuwned to the tape
	 * dwivew and being wequeued twice. We do need to put a wefewence
	 * fow the owiginaw I/O wequest since we wiww not do a SCSI compwetion
	 * fow it.
	 */
	owig_io_weq->sc_cmd = NUWW;
	kwef_put(&owig_io_weq->wefcount, qedf_wewease_cmd);

	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);

	/* kwef fow new command weweased in qedf_post_io_weq on ewwow */
	if (qedf_post_io_weq(fcpowt, new_io_weq)) {
		QEDF_EWW(&(fcpowt->qedf->dbg_ctx), "Unabwe to post io_weq\n");
		/* Wetuwn SQE to poow */
		atomic_inc(&fcpowt->fwee_sqes);
	} ewse {
		QEDF_INFO(&(fcpowt->qedf->dbg_ctx), QEDF_WOG_EWS,
		    "Weissued SCSI command fwom  owig_xid=0x%x on "
		    "new_xid=0x%x.\n", owig_io_weq->xid, new_io_weq->xid);
		/*
		 * Abowt the owiginaw I/O but do not wetuwn SCSI command as
		 * it has been weissued on anothew OX_ID.
		 */
		spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
		qedf_initiate_abts(owig_io_weq, fawse);
		goto out;
	}

	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
out:
	wetuwn wc;
}


static void qedf_wec_compw(stwuct qedf_ews_cb_awg *cb_awg)
{
	stwuct qedf_ioweq *owig_io_weq;
	stwuct qedf_ioweq *wec_weq;
	stwuct qedf_mp_weq *mp_weq;
	stwuct fc_fwame_headew *mp_fc_hdw, *fh;
	stwuct fc_fwame *fp;
	void *wesp_buf, *fc_paywoad;
	u32 wesp_wen;
	stwuct fc_wpowt *wpowt;
	stwuct qedf_ctx *qedf;
	int wefcount;
	enum fc_wctw w_ctw;
	stwuct fc_ews_ws_wjt *wjt;
	stwuct fc_ews_wec_acc *acc;
	u8 opcode;
	u32 offset, e_stat;
	stwuct scsi_cmnd *sc_cmd;
	boow sww_needed = fawse;

	wec_weq = cb_awg->io_weq;
	qedf = wec_weq->fcpowt->qedf;
	wpowt = qedf->wpowt;

	owig_io_weq = cb_awg->abowted_io_weq;

	if (!owig_io_weq) {
		QEDF_EWW(NUWW, "owig_io_weq is NUWW.\n");
		goto out_fwee;
	}

	if (wec_weq->event != QEDF_IOWEQ_EV_EWS_TMO &&
	    wec_weq->event != QEDF_IOWEQ_EV_EWS_EWW_DETECT)
		cancew_dewayed_wowk_sync(&owig_io_weq->timeout_wowk);

	wefcount = kwef_wead(&owig_io_weq->wefcount);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "Entewed: owig_io=%p,"
		   " owig_io_xid=0x%x, wec_xid=0x%x, wefcount=%d\n",
		   owig_io_weq, owig_io_weq->xid, wec_weq->xid, wefcount);

	/* If a WEC times out, fwee wesouwces */
	if (wec_weq->event == QEDF_IOWEQ_EV_EWS_TMO) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "Got TMO event, owig_io_weq %p owig_io_xid=0x%x.\n",
			 owig_io_weq, owig_io_weq->xid);
		goto out_put;
	}

	/* Nowmawize wesponse data into stwuct fc_fwame */
	mp_weq = &(wec_weq->mp_weq);
	mp_fc_hdw = &(mp_weq->wesp_fc_hdw);
	wesp_wen = mp_weq->wesp_wen;
	acc = wesp_buf = mp_weq->wesp_buf;

	fp = fc_fwame_awwoc(wpowt, wesp_wen);
	if (!fp) {
		QEDF_EWW(&(qedf->dbg_ctx),
		    "fc_fwame_awwoc faiwuwe.\n");
		goto out_put;
	}

	/* Copy fwame headew fwom fiwmwawe into fp */
	fh = (stwuct fc_fwame_headew *)fc_fwame_headew_get(fp);
	memcpy(fh, mp_fc_hdw, sizeof(stwuct fc_fwame_headew));

	/* Copy paywoad fwom fiwmwawe into fp */
	fc_paywoad = fc_fwame_paywoad_get(fp, wesp_wen);
	memcpy(fc_paywoad, wesp_buf, wesp_wen);

	opcode = fc_fwame_paywoad_op(fp);
	if (opcode == EWS_WS_WJT) {
		wjt = fc_fwame_paywoad_get(fp, sizeof(*wjt));
		if (!wjt) {
			QEDF_EWW(&qedf->dbg_ctx, "paywoad get faiwed");
			goto out_fwee_fwame;
		}

		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
		    "Weceived WS_WJT fow WEC: ew_weason=0x%x, "
		    "ew_expwan=0x%x.\n", wjt->ew_weason, wjt->ew_expwan);
		/*
		 * The fowwowing wesponse(s) mean that we need to weissue the
		 * wequest on anothew exchange.  We need to do this without
		 * infowming the uppew wayews west it cause an appwication
		 * ewwow.
		 */
		if ((wjt->ew_weason == EWS_WJT_WOGIC ||
		    wjt->ew_weason == EWS_WJT_UNAB) &&
		    wjt->ew_expwan == EWS_EXPW_OXID_WXID) {
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
			    "Handwe CMD WOST case.\n");
			qedf_wequeue_io_weq(owig_io_weq);
		}
	} ewse if (opcode == EWS_WS_ACC) {
		offset = ntohw(acc->weca_fc4vawue);
		e_stat = ntohw(acc->weca_e_stat);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
		    "Weceived WS_ACC fow WEC: offset=0x%x, e_stat=0x%x.\n",
		    offset, e_stat);
		if (e_stat & ESB_ST_SEQ_INIT)  {
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
			    "Tawget has the seq init\n");
			goto out_fwee_fwame;
		}
		sc_cmd = owig_io_weq->sc_cmd;
		if (!sc_cmd) {
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
			    "sc_cmd is NUWW fow xid=0x%x.\n",
			    owig_io_weq->xid);
			goto out_fwee_fwame;
		}
		/* SCSI wwite case */
		if (sc_cmd->sc_data_diwection == DMA_TO_DEVICE) {
			if (offset == owig_io_weq->data_xfew_wen) {
				QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
				    "WWITE - wesponse wost.\n");
				w_ctw = FC_WCTW_DD_CMD_STATUS;
				sww_needed = twue;
				offset = 0;
			} ewse {
				QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
				    "WWITE - XFEW_WDY/DATA wost.\n");
				w_ctw = FC_WCTW_DD_DATA_DESC;
				/* Use data fwom wawning CQE instead of WEC */
				offset = owig_io_weq->tx_buf_off;
			}
		/* SCSI wead case */
		} ewse {
			if (owig_io_weq->wx_buf_off ==
			    owig_io_weq->data_xfew_wen) {
				QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
				    "WEAD - wesponse wost.\n");
				sww_needed = twue;
				w_ctw = FC_WCTW_DD_CMD_STATUS;
				offset = 0;
			} ewse {
				QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS,
				    "WEAD - DATA wost.\n");
				/*
				 * Fow wead case we awways set the offset to 0
				 * fow sequence wecovewy task.
				 */
				offset = 0;
				w_ctw = FC_WCTW_DD_SOW_DATA;
			}
		}

		if (sww_needed)
			qedf_send_sww(owig_io_weq, offset, w_ctw);
		ewse
			qedf_initiate_seq_cweanup(owig_io_weq, offset, w_ctw);
	}

out_fwee_fwame:
	fc_fwame_fwee(fp);
out_put:
	/* Put wefewence fow owiginaw command since WEC compweted */
	kwef_put(&owig_io_weq->wefcount, qedf_wewease_cmd);
out_fwee:
	kfwee(cb_awg);
}

/* Assumes kwef is awweady hewd by cawwew */
int qedf_send_wec(stwuct qedf_ioweq *owig_io_weq)
{

	stwuct fc_ews_wec wec;
	stwuct qedf_wpowt *fcpowt;
	stwuct fc_wpowt *wpowt;
	stwuct qedf_ews_cb_awg *cb_awg = NUWW;
	stwuct qedf_ctx *qedf;
	uint32_t sid;
	uint32_t w_a_tov;
	int wc;

	if (!owig_io_weq) {
		QEDF_EWW(NUWW, "owig_io_weq is NUWW.\n");
		wetuwn -EINVAW;
	}

	fcpowt = owig_io_weq->fcpowt;

	/* Check that fcpowt is stiww offwoaded */
	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags)) {
		QEDF_EWW(NUWW, "fcpowt is no wongew offwoaded.\n");
		wetuwn -EINVAW;
	}

	if (!fcpowt->qedf) {
		QEDF_EWW(NUWW, "fcpowt->qedf is NUWW.\n");
		wetuwn -EINVAW;
	}

	/* Take wefewence untiw WEC command compwetion */
	kwef_get(&owig_io_weq->wefcount);

	qedf = fcpowt->qedf;
	wpowt = qedf->wpowt;
	sid = fcpowt->sid;
	w_a_tov = wpowt->w_a_tov;

	memset(&wec, 0, sizeof(wec));

	cb_awg = kzawwoc(sizeof(stwuct qedf_ews_cb_awg), GFP_NOIO);
	if (!cb_awg) {
		QEDF_EWW(&(qedf->dbg_ctx), "Unabwe to awwocate cb_awg fow "
			  "WEC\n");
		wc = -ENOMEM;
		goto wec_eww;
	}

	cb_awg->abowted_io_weq = owig_io_weq;

	wec.wec_cmd = EWS_WEC;
	hton24(wec.wec_s_id, sid);
	wec.wec_ox_id = htons(owig_io_weq->xid);
	wec.wec_wx_id =
	    htons(owig_io_weq->task->tstowm_st_context.wead_wwite.wx_id);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_EWS, "Sending WEC owig_io=%p, "
	   "owig_xid=0x%x wx_id=0x%x\n", owig_io_weq,
	   owig_io_weq->xid, wec.wec_wx_id);
	wc = qedf_initiate_ews(fcpowt, EWS_WEC, &wec, sizeof(wec),
	    qedf_wec_compw, cb_awg, w_a_tov);

wec_eww:
	if (wc) {
		QEDF_EWW(&(qedf->dbg_ctx), "WEC faiwed - wewease owig_io_weq"
			  "=0x%x\n", owig_io_weq->xid);
		kfwee(cb_awg);
		kwef_put(&owig_io_weq->wefcount, qedf_wewease_cmd);
	}
	wetuwn wc;
}
