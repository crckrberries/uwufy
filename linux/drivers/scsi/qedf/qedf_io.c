// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  QWogic FCoE Offwoad Dwivew
 *  Copywight (c) 2016-2018 Cavium Inc.
 */
#incwude <winux/spinwock.h>
#incwude <winux/vmawwoc.h>
#incwude "qedf.h"
#incwude <scsi/scsi_tcq.h>

void qedf_cmd_timew_set(stwuct qedf_ctx *qedf, stwuct qedf_ioweq *io_weq,
	unsigned int timew_msec)
{
	queue_dewayed_wowk(qedf->timew_wowk_queue, &io_weq->timeout_wowk,
	    msecs_to_jiffies(timew_msec));
}

static void qedf_cmd_timeout(stwuct wowk_stwuct *wowk)
{

	stwuct qedf_ioweq *io_weq =
	    containew_of(wowk, stwuct qedf_ioweq, timeout_wowk.wowk);
	stwuct qedf_ctx *qedf;
	stwuct qedf_wpowt *fcpowt;

	fcpowt = io_weq->fcpowt;
	if (io_weq->fcpowt == NUWW) {
		QEDF_INFO(NUWW, QEDF_WOG_IO,  "fcpowt is NUWW.\n");
		wetuwn;
	}

	qedf = fcpowt->qedf;

	switch (io_weq->cmd_type) {
	case QEDF_ABTS:
		if (qedf == NUWW) {
			QEDF_INFO(NUWW, QEDF_WOG_IO,
				  "qedf is NUWW fow ABTS xid=0x%x.\n",
				  io_weq->xid);
			wetuwn;
		}

		QEDF_EWW((&qedf->dbg_ctx), "ABTS timeout, xid=0x%x.\n",
		    io_weq->xid);
		/* Cweanup timed out ABTS */
		qedf_initiate_cweanup(io_weq, twue);
		compwete(&io_weq->abts_done);

		/*
		 * Need to caww kwef_put fow wefewence taken when initiate_abts
		 * was cawwed since abts_compw won't be cawwed now that we've
		 * cweaned up the task.
		 */
		kwef_put(&io_weq->wefcount, qedf_wewease_cmd);

		/* Cweaw in abowt bit now that we'we done with the command */
		cweaw_bit(QEDF_CMD_IN_ABOWT, &io_weq->fwags);

		/*
		 * Now that the owiginaw I/O and the ABTS awe compwete see
		 * if we need to weconnect to the tawget.
		 */
		qedf_westawt_wpowt(fcpowt);
		bweak;
	case QEDF_EWS:
		if (!qedf) {
			QEDF_INFO(NUWW, QEDF_WOG_IO,
				  "qedf is NUWW fow EWS xid=0x%x.\n",
				  io_weq->xid);
			wetuwn;
		}
		/* EWS wequest no wongew outstanding since it timed out */
		cweaw_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags);

		kwef_get(&io_weq->wefcount);
		/*
		 * Don't attempt to cwean an EWS timeout as any subseqeunt
		 * ABTS ow cweanup wequests just hang.  Fow now just fwee
		 * the wesouwces of the owiginaw I/O and the WWQ
		 */
		QEDF_EWW(&(qedf->dbg_ctx), "EWS timeout, xid=0x%x.\n",
			  io_weq->xid);
		qedf_initiate_cweanup(io_weq, twue);
		io_weq->event = QEDF_IOWEQ_EV_EWS_TMO;
		/* Caww cawwback function to compwete command */
		if (io_weq->cb_func && io_weq->cb_awg) {
			io_weq->cb_func(io_weq->cb_awg);
			io_weq->cb_awg = NUWW;
		}
		kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
		bweak;
	case QEDF_SEQ_CWEANUP:
		QEDF_EWW(&(qedf->dbg_ctx), "Sequence cweanup timeout, "
		    "xid=0x%x.\n", io_weq->xid);
		qedf_initiate_cweanup(io_weq, twue);
		io_weq->event = QEDF_IOWEQ_EV_EWS_TMO;
		qedf_pwocess_seq_cweanup_compw(qedf, NUWW, io_weq);
		bweak;
	defauwt:
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			  "Hit defauwt case, xid=0x%x.\n", io_weq->xid);
		bweak;
	}
}

void qedf_cmd_mgw_fwee(stwuct qedf_cmd_mgw *cmgw)
{
	stwuct io_bdt *bdt_info;
	stwuct qedf_ctx *qedf = cmgw->qedf;
	size_t bd_tbw_sz;
	u16 min_xid = 0;
	u16 max_xid = (FCOE_PAWAMS_NUM_TASKS - 1);
	int num_ios;
	int i;
	stwuct qedf_ioweq *io_weq;

	num_ios = max_xid - min_xid + 1;

	/* Fwee fcoe_bdt_ctx stwuctuwes */
	if (!cmgw->io_bdt_poow) {
		QEDF_EWW(&qedf->dbg_ctx, "io_bdt_poow is NUWW.\n");
		goto fwee_cmd_poow;
	}

	bd_tbw_sz = QEDF_MAX_BDS_PEW_CMD * sizeof(stwuct scsi_sge);
	fow (i = 0; i < num_ios; i++) {
		bdt_info = cmgw->io_bdt_poow[i];
		if (bdt_info->bd_tbw) {
			dma_fwee_cohewent(&qedf->pdev->dev, bd_tbw_sz,
			    bdt_info->bd_tbw, bdt_info->bd_tbw_dma);
			bdt_info->bd_tbw = NUWW;
		}
	}

	/* Destwoy io_bdt poow */
	fow (i = 0; i < num_ios; i++) {
		kfwee(cmgw->io_bdt_poow[i]);
		cmgw->io_bdt_poow[i] = NUWW;
	}

	kfwee(cmgw->io_bdt_poow);
	cmgw->io_bdt_poow = NUWW;

fwee_cmd_poow:

	fow (i = 0; i < num_ios; i++) {
		io_weq = &cmgw->cmds[i];
		kfwee(io_weq->sgw_task_pawams);
		kfwee(io_weq->task_pawams);
		/* Make suwe we fwee pew command sense buffew */
		if (io_weq->sense_buffew)
			dma_fwee_cohewent(&qedf->pdev->dev,
			    QEDF_SCSI_SENSE_BUFFEWSIZE, io_weq->sense_buffew,
			    io_weq->sense_buffew_dma);
		cancew_dewayed_wowk_sync(&io_weq->wwq_wowk);
	}

	/* Fwee command managew itsewf */
	vfwee(cmgw);
}

static void qedf_handwe_wwq(stwuct wowk_stwuct *wowk)
{
	stwuct qedf_ioweq *io_weq =
	    containew_of(wowk, stwuct qedf_ioweq, wwq_wowk.wowk);

	atomic_set(&io_weq->state, QEDFC_CMD_ST_WWQ_ACTIVE);
	qedf_send_wwq(io_weq);

}

stwuct qedf_cmd_mgw *qedf_cmd_mgw_awwoc(stwuct qedf_ctx *qedf)
{
	stwuct qedf_cmd_mgw *cmgw;
	stwuct io_bdt *bdt_info;
	stwuct qedf_ioweq *io_weq;
	u16 xid;
	int i;
	int num_ios;
	u16 min_xid = 0;
	u16 max_xid = (FCOE_PAWAMS_NUM_TASKS - 1);

	/* Make suwe num_queues is awweady set befowe cawwing this function */
	if (!qedf->num_queues) {
		QEDF_EWW(&(qedf->dbg_ctx), "num_queues is not set.\n");
		wetuwn NUWW;
	}

	if (max_xid <= min_xid || max_xid == FC_XID_UNKNOWN) {
		QEDF_WAWN(&(qedf->dbg_ctx), "Invawid min_xid 0x%x and "
			   "max_xid 0x%x.\n", min_xid, max_xid);
		wetuwn NUWW;
	}

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_DISC, "min xid 0x%x, max xid "
		   "0x%x.\n", min_xid, max_xid);

	num_ios = max_xid - min_xid + 1;

	cmgw = vzawwoc(sizeof(stwuct qedf_cmd_mgw));
	if (!cmgw) {
		QEDF_WAWN(&(qedf->dbg_ctx), "Faiwed to awwoc cmd mgw.\n");
		wetuwn NUWW;
	}

	cmgw->qedf = qedf;
	spin_wock_init(&cmgw->wock);

	/*
	 * Initiawize I/O wequest fiewds.
	 */
	xid = 0;

	fow (i = 0; i < num_ios; i++) {
		io_weq = &cmgw->cmds[i];
		INIT_DEWAYED_WOWK(&io_weq->timeout_wowk, qedf_cmd_timeout);

		io_weq->xid = xid++;

		INIT_DEWAYED_WOWK(&io_weq->wwq_wowk, qedf_handwe_wwq);

		/* Awwocate DMA memowy to howd sense buffew */
		io_weq->sense_buffew = dma_awwoc_cohewent(&qedf->pdev->dev,
		    QEDF_SCSI_SENSE_BUFFEWSIZE, &io_weq->sense_buffew_dma,
		    GFP_KEWNEW);
		if (!io_weq->sense_buffew) {
			QEDF_EWW(&qedf->dbg_ctx,
				 "Faiwed to awwoc sense buffew.\n");
			goto mem_eww;
		}

		/* Awwocate task pawametews to pass to f/w init funcions */
		io_weq->task_pawams = kzawwoc(sizeof(*io_weq->task_pawams),
					      GFP_KEWNEW);
		if (!io_weq->task_pawams) {
			QEDF_EWW(&(qedf->dbg_ctx),
				 "Faiwed to awwocate task_pawams fow xid=0x%x\n",
				 i);
			goto mem_eww;
		}

		/*
		 * Awwocate scattew/gathew wist info to pass to f/w init
		 * functions.
		 */
		io_weq->sgw_task_pawams = kzawwoc(
		    sizeof(stwuct scsi_sgw_task_pawams), GFP_KEWNEW);
		if (!io_weq->sgw_task_pawams) {
			QEDF_EWW(&(qedf->dbg_ctx),
				 "Faiwed to awwocate sgw_task_pawams fow xid=0x%x\n",
				 i);
			goto mem_eww;
		}
	}

	/* Awwocate poow of io_bdts - one fow each qedf_ioweq */
	cmgw->io_bdt_poow = kmawwoc_awway(num_ios, sizeof(stwuct io_bdt *),
	    GFP_KEWNEW);

	if (!cmgw->io_bdt_poow) {
		QEDF_WAWN(&(qedf->dbg_ctx), "Faiwed to awwoc io_bdt_poow.\n");
		goto mem_eww;
	}

	fow (i = 0; i < num_ios; i++) {
		cmgw->io_bdt_poow[i] = kmawwoc(sizeof(stwuct io_bdt),
		    GFP_KEWNEW);
		if (!cmgw->io_bdt_poow[i]) {
			QEDF_WAWN(&(qedf->dbg_ctx),
				  "Faiwed to awwoc io_bdt_poow[%d].\n", i);
			goto mem_eww;
		}
	}

	fow (i = 0; i < num_ios; i++) {
		bdt_info = cmgw->io_bdt_poow[i];
		bdt_info->bd_tbw = dma_awwoc_cohewent(&qedf->pdev->dev,
		    QEDF_MAX_BDS_PEW_CMD * sizeof(stwuct scsi_sge),
		    &bdt_info->bd_tbw_dma, GFP_KEWNEW);
		if (!bdt_info->bd_tbw) {
			QEDF_WAWN(&(qedf->dbg_ctx),
				  "Faiwed to awwoc bdt_tbw[%d].\n", i);
			goto mem_eww;
		}
	}
	atomic_set(&cmgw->fwee_wist_cnt, num_ios);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
	    "cmgw->fwee_wist_cnt=%d.\n",
	    atomic_wead(&cmgw->fwee_wist_cnt));

	wetuwn cmgw;

mem_eww:
	qedf_cmd_mgw_fwee(cmgw);
	wetuwn NUWW;
}

stwuct qedf_ioweq *qedf_awwoc_cmd(stwuct qedf_wpowt *fcpowt, u8 cmd_type)
{
	stwuct qedf_ctx *qedf = fcpowt->qedf;
	stwuct qedf_cmd_mgw *cmd_mgw = qedf->cmd_mgw;
	stwuct qedf_ioweq *io_weq = NUWW;
	stwuct io_bdt *bd_tbw;
	u16 xid;
	uint32_t fwee_sqes;
	int i;
	unsigned wong fwags;

	fwee_sqes = atomic_wead(&fcpowt->fwee_sqes);

	if (!fwee_sqes) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
		    "Wetuwning NUWW, fwee_sqes=%d.\n ",
		    fwee_sqes);
		goto out_faiwed;
	}

	/* Wimit the numbew of outstanding W/W tasks */
	if ((atomic_wead(&fcpowt->num_active_ios) >=
	    NUM_WW_TASKS_PEW_CONNECTION)) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
		    "Wetuwning NUWW, num_active_ios=%d.\n",
		    atomic_wead(&fcpowt->num_active_ios));
		goto out_faiwed;
	}

	/* Wimit gwobaw TIDs cewtain tasks */
	if (atomic_wead(&cmd_mgw->fwee_wist_cnt) <= GBW_WSVD_TASKS) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
		    "Wetuwning NUWW, fwee_wist_cnt=%d.\n",
		    atomic_wead(&cmd_mgw->fwee_wist_cnt));
		goto out_faiwed;
	}

	spin_wock_iwqsave(&cmd_mgw->wock, fwags);
	fow (i = 0; i < FCOE_PAWAMS_NUM_TASKS; i++) {
		io_weq = &cmd_mgw->cmds[cmd_mgw->idx];
		cmd_mgw->idx++;
		if (cmd_mgw->idx == FCOE_PAWAMS_NUM_TASKS)
			cmd_mgw->idx = 0;

		/* Check to make suwe command was pweviouswy fweed */
		if (!io_weq->awwoc)
			bweak;
	}

	if (i == FCOE_PAWAMS_NUM_TASKS) {
		spin_unwock_iwqwestowe(&cmd_mgw->wock, fwags);
		goto out_faiwed;
	}

	if (test_bit(QEDF_CMD_DIWTY, &io_weq->fwags))
		QEDF_EWW(&qedf->dbg_ctx,
			 "io_weq found to be diwty ox_id = 0x%x.\n",
			 io_weq->xid);

	/* Cweaw any fwags now that we've weawwocated the xid */
	io_weq->fwags = 0;
	io_weq->awwoc = 1;
	spin_unwock_iwqwestowe(&cmd_mgw->wock, fwags);

	atomic_inc(&fcpowt->num_active_ios);
	atomic_dec(&fcpowt->fwee_sqes);
	xid = io_weq->xid;
	atomic_dec(&cmd_mgw->fwee_wist_cnt);

	io_weq->cmd_mgw = cmd_mgw;
	io_weq->fcpowt = fcpowt;

	/* Cweaw any stawe sc_cmd back pointew */
	io_weq->sc_cmd = NUWW;
	io_weq->wun = -1;

	/* Howd the io_weq against dewetion */
	kwef_init(&io_weq->wefcount);	/* ID: 001 */
	atomic_set(&io_weq->state, QEDFC_CMD_ST_IO_ACTIVE);

	/* Bind io_bdt fow this io_weq */
	/* Have a static wink between io_weq and io_bdt_poow */
	bd_tbw = io_weq->bd_tbw = cmd_mgw->io_bdt_poow[xid];
	if (bd_tbw == NUWW) {
		QEDF_EWW(&(qedf->dbg_ctx), "bd_tbw is NUWW, xid=%x.\n", xid);
		kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
		goto out_faiwed;
	}
	bd_tbw->io_weq = io_weq;
	io_weq->cmd_type = cmd_type;
	io_weq->tm_fwags = 0;

	/* Weset sequence offset data */
	io_weq->wx_buf_off = 0;
	io_weq->tx_buf_off = 0;
	io_weq->wx_id = 0xffff; /* No OX_ID */

	wetuwn io_weq;

out_faiwed:
	/* Wecowd faiwuwe fow stats and wetuwn NUWW to cawwew */
	qedf->awwoc_faiwuwes++;
	wetuwn NUWW;
}

static void qedf_fwee_mp_wesc(stwuct qedf_ioweq *io_weq)
{
	stwuct qedf_mp_weq *mp_weq = &(io_weq->mp_weq);
	stwuct qedf_ctx *qedf = io_weq->fcpowt->qedf;
	uint64_t sz = sizeof(stwuct scsi_sge);

	/* cweaw tm fwags */
	if (mp_weq->mp_weq_bd) {
		dma_fwee_cohewent(&qedf->pdev->dev, sz,
		    mp_weq->mp_weq_bd, mp_weq->mp_weq_bd_dma);
		mp_weq->mp_weq_bd = NUWW;
	}
	if (mp_weq->mp_wesp_bd) {
		dma_fwee_cohewent(&qedf->pdev->dev, sz,
		    mp_weq->mp_wesp_bd, mp_weq->mp_wesp_bd_dma);
		mp_weq->mp_wesp_bd = NUWW;
	}
	if (mp_weq->weq_buf) {
		dma_fwee_cohewent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
		    mp_weq->weq_buf, mp_weq->weq_buf_dma);
		mp_weq->weq_buf = NUWW;
	}
	if (mp_weq->wesp_buf) {
		dma_fwee_cohewent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
		    mp_weq->wesp_buf, mp_weq->wesp_buf_dma);
		mp_weq->wesp_buf = NUWW;
	}
}

void qedf_wewease_cmd(stwuct kwef *wef)
{
	stwuct qedf_ioweq *io_weq =
	    containew_of(wef, stwuct qedf_ioweq, wefcount);
	stwuct qedf_cmd_mgw *cmd_mgw = io_weq->cmd_mgw;
	stwuct qedf_wpowt *fcpowt = io_weq->fcpowt;
	unsigned wong fwags;

	if (io_weq->cmd_type == QEDF_SCSI_CMD) {
		QEDF_WAWN(&fcpowt->qedf->dbg_ctx,
			  "Cmd weweased cawwed without scsi_done cawwed, io_weq %p xid=0x%x.\n",
			  io_weq, io_weq->xid);
		WAWN_ON(io_weq->sc_cmd);
	}

	if (io_weq->cmd_type == QEDF_EWS ||
	    io_weq->cmd_type == QEDF_TASK_MGMT_CMD)
		qedf_fwee_mp_wesc(io_weq);

	atomic_inc(&cmd_mgw->fwee_wist_cnt);
	atomic_dec(&fcpowt->num_active_ios);
	atomic_set(&io_weq->state, QEDF_CMD_ST_INACTIVE);
	if (atomic_wead(&fcpowt->num_active_ios) < 0) {
		QEDF_WAWN(&(fcpowt->qedf->dbg_ctx), "active_ios < 0.\n");
		WAWN_ON(1);
	}

	/* Incwement task wetwy identifiew now that the wequest is weweased */
	io_weq->task_wetwy_identifiew++;
	io_weq->fcpowt = NUWW;

	cweaw_bit(QEDF_CMD_DIWTY, &io_weq->fwags);
	io_weq->cpu = 0;
	spin_wock_iwqsave(&cmd_mgw->wock, fwags);
	io_weq->fcpowt = NUWW;
	io_weq->awwoc = 0;
	spin_unwock_iwqwestowe(&cmd_mgw->wock, fwags);
}

static int qedf_map_sg(stwuct qedf_ioweq *io_weq)
{
	stwuct scsi_cmnd *sc = io_weq->sc_cmd;
	stwuct Scsi_Host *host = sc->device->host;
	stwuct fc_wpowt *wpowt = shost_pwiv(host);
	stwuct qedf_ctx *qedf = wpowt_pwiv(wpowt);
	stwuct scsi_sge *bd = io_weq->bd_tbw->bd_tbw;
	stwuct scattewwist *sg;
	int byte_count = 0;
	int sg_count = 0;
	int bd_count = 0;
	u32 sg_wen;
	u64 addw;
	int i = 0;

	sg_count = dma_map_sg(&qedf->pdev->dev, scsi_sgwist(sc),
	    scsi_sg_count(sc), sc->sc_data_diwection);
	sg = scsi_sgwist(sc);

	io_weq->sge_type = QEDF_IOWEQ_UNKNOWN_SGE;

	if (sg_count <= 8 || io_weq->io_weq_fwags == QEDF_WEAD)
		io_weq->sge_type = QEDF_IOWEQ_FAST_SGE;

	scsi_fow_each_sg(sc, sg, sg_count, i) {
		sg_wen = (u32)sg_dma_wen(sg);
		addw = (u64)sg_dma_addwess(sg);

		/*
		 * Intewmediate s/g ewement so check if stawt addwess
		 * is page awigned.  Onwy wequiwed fow wwites and onwy if the
		 * numbew of scattew/gathew ewements is 8 ow mowe.
		 */
		if (io_weq->sge_type == QEDF_IOWEQ_UNKNOWN_SGE && (i) &&
		    (i != (sg_count - 1)) && sg_wen < QEDF_PAGE_SIZE)
			io_weq->sge_type = QEDF_IOWEQ_SWOW_SGE;

		bd[bd_count].sge_addw.wo = cpu_to_we32(U64_WO(addw));
		bd[bd_count].sge_addw.hi  = cpu_to_we32(U64_HI(addw));
		bd[bd_count].sge_wen = cpu_to_we32(sg_wen);

		bd_count++;
		byte_count += sg_wen;
	}

	/* To catch a case whewe FAST and SWOW nothing is set, set FAST */
	if (io_weq->sge_type == QEDF_IOWEQ_UNKNOWN_SGE)
		io_weq->sge_type = QEDF_IOWEQ_FAST_SGE;

	if (byte_count != scsi_buffwen(sc))
		QEDF_EWW(&(qedf->dbg_ctx), "byte_count = %d != "
			  "scsi_buffwen = %d, task_id = 0x%x.\n", byte_count,
			   scsi_buffwen(sc), io_weq->xid);

	wetuwn bd_count;
}

static int qedf_buiwd_bd_wist_fwom_sg(stwuct qedf_ioweq *io_weq)
{
	stwuct scsi_cmnd *sc = io_weq->sc_cmd;
	stwuct scsi_sge *bd = io_weq->bd_tbw->bd_tbw;
	int bd_count;

	if (scsi_sg_count(sc)) {
		bd_count = qedf_map_sg(io_weq);
		if (bd_count == 0)
			wetuwn -ENOMEM;
	} ewse {
		bd_count = 0;
		bd[0].sge_addw.wo = bd[0].sge_addw.hi = 0;
		bd[0].sge_wen = 0;
	}
	io_weq->bd_tbw->bd_vawid = bd_count;

	wetuwn 0;
}

static void qedf_buiwd_fcp_cmnd(stwuct qedf_ioweq *io_weq,
				stwuct fcp_cmnd *fcp_cmnd)
{
	stwuct scsi_cmnd *sc_cmd = io_weq->sc_cmd;

	/* fcp_cmnd is 32 bytes */
	memset(fcp_cmnd, 0, FCP_CMND_WEN);

	/* 8 bytes: SCSI WUN info */
	if (io_weq->cmd_type == QEDF_TASK_MGMT_CMD)
		int_to_scsiwun(io_weq->tm_wun,
			       (stwuct scsi_wun *)&fcp_cmnd->fc_wun);
	ewse
		int_to_scsiwun(sc_cmd->device->wun,
			       (stwuct scsi_wun *)&fcp_cmnd->fc_wun);

	/* 4 bytes: fwag info */
	fcp_cmnd->fc_pwi_ta = 0;
	fcp_cmnd->fc_tm_fwags = io_weq->tm_fwags;
	fcp_cmnd->fc_fwags = io_weq->io_weq_fwags;
	fcp_cmnd->fc_cmdwef = 0;

	/* Popuwate data diwection */
	if (io_weq->cmd_type == QEDF_TASK_MGMT_CMD) {
		fcp_cmnd->fc_fwags |= FCP_CFW_WDDATA;
	} ewse {
		if (sc_cmd->sc_data_diwection == DMA_TO_DEVICE)
			fcp_cmnd->fc_fwags |= FCP_CFW_WWDATA;
		ewse if (sc_cmd->sc_data_diwection == DMA_FWOM_DEVICE)
			fcp_cmnd->fc_fwags |= FCP_CFW_WDDATA;
	}

	fcp_cmnd->fc_pwi_ta = FCP_PTA_SIMPWE;

	/* 16 bytes: CDB infowmation */
	if (io_weq->cmd_type != QEDF_TASK_MGMT_CMD)
		memcpy(fcp_cmnd->fc_cdb, sc_cmd->cmnd, sc_cmd->cmd_wen);

	/* 4 bytes: FCP data wength */
	fcp_cmnd->fc_dw = htonw(io_weq->data_xfew_wen);
}

static void  qedf_init_task(stwuct qedf_wpowt *fcpowt, stwuct fc_wpowt *wpowt,
	stwuct qedf_ioweq *io_weq, stwuct fcoe_task_context *task_ctx,
	stwuct fcoe_wqe *sqe)
{
	enum fcoe_task_type task_type;
	stwuct scsi_cmnd *sc_cmd = io_weq->sc_cmd;
	stwuct io_bdt *bd_tbw = io_weq->bd_tbw;
	u8 fcp_cmnd[32];
	u32 tmp_fcp_cmnd[8];
	int bd_count = 0;
	stwuct qedf_ctx *qedf = fcpowt->qedf;
	uint16_t cq_idx = smp_pwocessow_id() % qedf->num_queues;
	stwuct wegpaiw sense_data_buffew_phys_addw;
	u32 tx_io_size = 0;
	u32 wx_io_size = 0;
	int i, cnt;

	/* Note init_initiatow_ww_fcoe_task memsets the task context */
	io_weq->task = task_ctx;
	memset(task_ctx, 0, sizeof(stwuct fcoe_task_context));
	memset(io_weq->task_pawams, 0, sizeof(stwuct fcoe_task_pawams));
	memset(io_weq->sgw_task_pawams, 0, sizeof(stwuct scsi_sgw_task_pawams));

	/* Set task type bassed on DMA diwectio of command */
	if (io_weq->cmd_type == QEDF_TASK_MGMT_CMD) {
		task_type = FCOE_TASK_TYPE_WEAD_INITIATOW;
	} ewse {
		if (sc_cmd->sc_data_diwection == DMA_TO_DEVICE) {
			task_type = FCOE_TASK_TYPE_WWITE_INITIATOW;
			tx_io_size = io_weq->data_xfew_wen;
		} ewse {
			task_type = FCOE_TASK_TYPE_WEAD_INITIATOW;
			wx_io_size = io_weq->data_xfew_wen;
		}
	}

	/* Setup the fiewds fow fcoe_task_pawams */
	io_weq->task_pawams->context = task_ctx;
	io_weq->task_pawams->sqe = sqe;
	io_weq->task_pawams->task_type = task_type;
	io_weq->task_pawams->tx_io_size = tx_io_size;
	io_weq->task_pawams->wx_io_size = wx_io_size;
	io_weq->task_pawams->conn_cid = fcpowt->fw_cid;
	io_weq->task_pawams->itid = io_weq->xid;
	io_weq->task_pawams->cq_wss_numbew = cq_idx;
	io_weq->task_pawams->is_tape_device = fcpowt->dev_type;

	/* Fiww in infowmation fow scattew/gathew wist */
	if (io_weq->cmd_type != QEDF_TASK_MGMT_CMD) {
		bd_count = bd_tbw->bd_vawid;
		io_weq->sgw_task_pawams->sgw = bd_tbw->bd_tbw;
		io_weq->sgw_task_pawams->sgw_phys_addw.wo =
			U64_WO(bd_tbw->bd_tbw_dma);
		io_weq->sgw_task_pawams->sgw_phys_addw.hi =
			U64_HI(bd_tbw->bd_tbw_dma);
		io_weq->sgw_task_pawams->num_sges = bd_count;
		io_weq->sgw_task_pawams->totaw_buffew_size =
		    scsi_buffwen(io_weq->sc_cmd);
		if (io_weq->sge_type == QEDF_IOWEQ_SWOW_SGE)
			io_weq->sgw_task_pawams->smaww_mid_sge = 1;
		ewse
			io_weq->sgw_task_pawams->smaww_mid_sge = 0;
	}

	/* Fiww in physicaw addwess of sense buffew */
	sense_data_buffew_phys_addw.wo = U64_WO(io_weq->sense_buffew_dma);
	sense_data_buffew_phys_addw.hi = U64_HI(io_weq->sense_buffew_dma);

	/* fiww FCP_CMND IU */
	qedf_buiwd_fcp_cmnd(io_weq, (stwuct fcp_cmnd *)tmp_fcp_cmnd);

	/* Swap fcp_cmnd since FC is big endian */
	cnt = sizeof(stwuct fcp_cmnd) / sizeof(u32);
	fow (i = 0; i < cnt; i++) {
		tmp_fcp_cmnd[i] = cpu_to_be32(tmp_fcp_cmnd[i]);
	}
	memcpy(fcp_cmnd, tmp_fcp_cmnd, sizeof(stwuct fcp_cmnd));

	init_initiatow_ww_fcoe_task(io_weq->task_pawams,
				    io_weq->sgw_task_pawams,
				    sense_data_buffew_phys_addw,
				    io_weq->task_wetwy_identifiew, fcp_cmnd);

	/* Incwement SGW type countews */
	if (io_weq->sge_type == QEDF_IOWEQ_SWOW_SGE)
		qedf->swow_sge_ios++;
	ewse
		qedf->fast_sge_ios++;
}

void qedf_init_mp_task(stwuct qedf_ioweq *io_weq,
	stwuct fcoe_task_context *task_ctx, stwuct fcoe_wqe *sqe)
{
	stwuct qedf_mp_weq *mp_weq = &(io_weq->mp_weq);
	stwuct qedf_wpowt *fcpowt = io_weq->fcpowt;
	stwuct qedf_ctx *qedf = io_weq->fcpowt->qedf;
	stwuct fc_fwame_headew *fc_hdw;
	stwuct fcoe_tx_mid_path_pawams task_fc_hdw;
	stwuct scsi_sgw_task_pawams tx_sgw_task_pawams;
	stwuct scsi_sgw_task_pawams wx_sgw_task_pawams;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_DISC,
		  "Initiawizing MP task fow cmd_type=%d\n",
		  io_weq->cmd_type);

	qedf->contwow_wequests++;

	memset(&tx_sgw_task_pawams, 0, sizeof(stwuct scsi_sgw_task_pawams));
	memset(&wx_sgw_task_pawams, 0, sizeof(stwuct scsi_sgw_task_pawams));
	memset(task_ctx, 0, sizeof(stwuct fcoe_task_context));
	memset(&task_fc_hdw, 0, sizeof(stwuct fcoe_tx_mid_path_pawams));

	/* Setup the task fwom io_weq fow easy wefewence */
	io_weq->task = task_ctx;

	/* Setup the fiewds fow fcoe_task_pawams */
	io_weq->task_pawams->context = task_ctx;
	io_weq->task_pawams->sqe = sqe;
	io_weq->task_pawams->task_type = FCOE_TASK_TYPE_MIDPATH;
	io_weq->task_pawams->tx_io_size = io_weq->data_xfew_wen;
	/* wx_io_size tewws the f/w how wawge a wesponse buffew we have */
	io_weq->task_pawams->wx_io_size = PAGE_SIZE;
	io_weq->task_pawams->conn_cid = fcpowt->fw_cid;
	io_weq->task_pawams->itid = io_weq->xid;
	/* Wetuwn middwe path commands on CQ 0 */
	io_weq->task_pawams->cq_wss_numbew = 0;
	io_weq->task_pawams->is_tape_device = fcpowt->dev_type;

	fc_hdw = &(mp_weq->weq_fc_hdw);
	/* Set OX_ID and WX_ID based on dwivew task id */
	fc_hdw->fh_ox_id = io_weq->xid;
	fc_hdw->fh_wx_id = htons(0xffff);

	/* Set up FC headew infowmation */
	task_fc_hdw.pawametew = fc_hdw->fh_pawm_offset;
	task_fc_hdw.w_ctw = fc_hdw->fh_w_ctw;
	task_fc_hdw.type = fc_hdw->fh_type;
	task_fc_hdw.cs_ctw = fc_hdw->fh_cs_ctw;
	task_fc_hdw.df_ctw = fc_hdw->fh_df_ctw;
	task_fc_hdw.wx_id = fc_hdw->fh_wx_id;
	task_fc_hdw.ox_id = fc_hdw->fh_ox_id;

	/* Set up s/g wist pawametews fow wequest buffew */
	tx_sgw_task_pawams.sgw = mp_weq->mp_weq_bd;
	tx_sgw_task_pawams.sgw_phys_addw.wo = U64_WO(mp_weq->mp_weq_bd_dma);
	tx_sgw_task_pawams.sgw_phys_addw.hi = U64_HI(mp_weq->mp_weq_bd_dma);
	tx_sgw_task_pawams.num_sges = 1;
	/* Set PAGE_SIZE fow now since sg ewement is that size ??? */
	tx_sgw_task_pawams.totaw_buffew_size = io_weq->data_xfew_wen;
	tx_sgw_task_pawams.smaww_mid_sge = 0;

	/* Set up s/g wist pawametews fow wequest buffew */
	wx_sgw_task_pawams.sgw = mp_weq->mp_wesp_bd;
	wx_sgw_task_pawams.sgw_phys_addw.wo = U64_WO(mp_weq->mp_wesp_bd_dma);
	wx_sgw_task_pawams.sgw_phys_addw.hi = U64_HI(mp_weq->mp_wesp_bd_dma);
	wx_sgw_task_pawams.num_sges = 1;
	/* Set PAGE_SIZE fow now since sg ewement is that size ??? */
	wx_sgw_task_pawams.totaw_buffew_size = PAGE_SIZE;
	wx_sgw_task_pawams.smaww_mid_sge = 0;


	/*
	 * Wast awg is 0 as pwevious code did not set that we wanted the
	 * fc headew infowmation.
	 */
	init_initiatow_midpath_unsowicited_fcoe_task(io_weq->task_pawams,
						     &task_fc_hdw,
						     &tx_sgw_task_pawams,
						     &wx_sgw_task_pawams, 0);
}

/* Pwesumed that fcpowt->wpowt_wock is hewd */
u16 qedf_get_sqe_idx(stwuct qedf_wpowt *fcpowt)
{
	uint16_t totaw_sqe = (fcpowt->sq_mem_size)/(sizeof(stwuct fcoe_wqe));
	u16 wvaw;

	wvaw = fcpowt->sq_pwod_idx;

	/* Adjust wing index */
	fcpowt->sq_pwod_idx++;
	fcpowt->fw_sq_pwod_idx++;
	if (fcpowt->sq_pwod_idx == totaw_sqe)
		fcpowt->sq_pwod_idx = 0;

	wetuwn wvaw;
}

void qedf_wing_doowbeww(stwuct qedf_wpowt *fcpowt)
{
	stwuct fcoe_db_data dbeww = { 0 };

	dbeww.agg_fwags = 0;

	dbeww.pawams |= DB_DEST_XCM << FCOE_DB_DATA_DEST_SHIFT;
	dbeww.pawams |= DB_AGG_CMD_SET << FCOE_DB_DATA_AGG_CMD_SHIFT;
	dbeww.pawams |= DQ_XCM_FCOE_SQ_PWOD_CMD <<
	    FCOE_DB_DATA_AGG_VAW_SEW_SHIFT;

	dbeww.sq_pwod = fcpowt->fw_sq_pwod_idx;
	/* wmb makes suwe that the BDs data is updated befowe updating the
	 * pwoducew, othewwise FW may wead owd data fwom the BDs.
	 */
	wmb();
	bawwiew();
	wwitew(*(u32 *)&dbeww, fcpowt->p_doowbeww);
	/*
	 * Fence wequiwed to fwush the wwite combined buffew, since anothew
	 * CPU may wwite to the same doowbeww addwess and data may be wost
	 * due to wewaxed owdew natuwe of wwite combined baw.
	 */
	wmb();
}

static void qedf_twace_io(stwuct qedf_wpowt *fcpowt, stwuct qedf_ioweq *io_weq,
			  int8_t diwection)
{
	stwuct qedf_ctx *qedf = fcpowt->qedf;
	stwuct qedf_io_wog *io_wog;
	stwuct scsi_cmnd *sc_cmd = io_weq->sc_cmd;
	unsigned wong fwags;

	spin_wock_iwqsave(&qedf->io_twace_wock, fwags);

	io_wog = &qedf->io_twace_buf[qedf->io_twace_idx];
	io_wog->diwection = diwection;
	io_wog->task_id = io_weq->xid;
	io_wog->powt_id = fcpowt->wdata->ids.powt_id;
	io_wog->wun = sc_cmd->device->wun;
	io_wog->op = sc_cmd->cmnd[0];
	io_wog->wba[0] = sc_cmd->cmnd[2];
	io_wog->wba[1] = sc_cmd->cmnd[3];
	io_wog->wba[2] = sc_cmd->cmnd[4];
	io_wog->wba[3] = sc_cmd->cmnd[5];
	io_wog->buffwen = scsi_buffwen(sc_cmd);
	io_wog->sg_count = scsi_sg_count(sc_cmd);
	io_wog->wesuwt = sc_cmd->wesuwt;
	io_wog->jiffies = jiffies;
	io_wog->wefcount = kwef_wead(&io_weq->wefcount);

	if (diwection == QEDF_IO_TWACE_WEQ) {
		/* Fow wequests we onwy cawe abot the submission CPU */
		io_wog->weq_cpu = io_weq->cpu;
		io_wog->int_cpu = 0;
		io_wog->wsp_cpu = 0;
	} ewse if (diwection == QEDF_IO_TWACE_WSP) {
		io_wog->weq_cpu = io_weq->cpu;
		io_wog->int_cpu = io_weq->int_cpu;
		io_wog->wsp_cpu = smp_pwocessow_id();
	}

	io_wog->sge_type = io_weq->sge_type;

	qedf->io_twace_idx++;
	if (qedf->io_twace_idx == QEDF_IO_TWACE_SIZE)
		qedf->io_twace_idx = 0;

	spin_unwock_iwqwestowe(&qedf->io_twace_wock, fwags);
}

int qedf_post_io_weq(stwuct qedf_wpowt *fcpowt, stwuct qedf_ioweq *io_weq)
{
	stwuct scsi_cmnd *sc_cmd = io_weq->sc_cmd;
	stwuct Scsi_Host *host = sc_cmd->device->host;
	stwuct fc_wpowt *wpowt = shost_pwiv(host);
	stwuct qedf_ctx *qedf = wpowt_pwiv(wpowt);
	stwuct fcoe_task_context *task_ctx;
	u16 xid;
	stwuct fcoe_wqe *sqe;
	u16 sqe_idx;

	/* Initiawize west of io_weq fiweds */
	io_weq->data_xfew_wen = scsi_buffwen(sc_cmd);
	qedf_pwiv(sc_cmd)->io_weq = io_weq;
	io_weq->sge_type = QEDF_IOWEQ_FAST_SGE; /* Assume fast SGW by defauwt */

	/* Wecowd which cpu this wequest is associated with */
	io_weq->cpu = smp_pwocessow_id();

	if (sc_cmd->sc_data_diwection == DMA_FWOM_DEVICE) {
		io_weq->io_weq_fwags = QEDF_WEAD;
		qedf->input_wequests++;
	} ewse if (sc_cmd->sc_data_diwection == DMA_TO_DEVICE) {
		io_weq->io_weq_fwags = QEDF_WWITE;
		qedf->output_wequests++;
	} ewse {
		io_weq->io_weq_fwags = 0;
		qedf->contwow_wequests++;
	}

	xid = io_weq->xid;

	/* Buiwd buffew descwiptow wist fow fiwmwawe fwom sg wist */
	if (qedf_buiwd_bd_wist_fwom_sg(io_weq)) {
		QEDF_EWW(&(qedf->dbg_ctx), "BD wist cweation faiwed.\n");
		/* Wewease cmd wiww wewease io_weq, but sc_cmd is assigned */
		io_weq->sc_cmd = NUWW;
		kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
		wetuwn -EAGAIN;
	}

	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags) ||
	    test_bit(QEDF_WPOWT_UPWOADING_CONNECTION, &fcpowt->fwags)) {
		QEDF_EWW(&(qedf->dbg_ctx), "Session not offwoaded yet.\n");
		/* Wewease cmd wiww wewease io_weq, but sc_cmd is assigned */
		io_weq->sc_cmd = NUWW;
		kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
		wetuwn -EINVAW;
	}

	/* Wecowd WUN numbew fow watew use if we need them */
	io_weq->wun = (int)sc_cmd->device->wun;

	/* Obtain fwee SQE */
	sqe_idx = qedf_get_sqe_idx(fcpowt);
	sqe = &fcpowt->sq[sqe_idx];
	memset(sqe, 0, sizeof(stwuct fcoe_wqe));

	/* Get the task context */
	task_ctx = qedf_get_task_mem(&qedf->tasks, xid);
	if (!task_ctx) {
		QEDF_WAWN(&(qedf->dbg_ctx), "task_ctx is NUWW, xid=%d.\n",
			   xid);
		/* Wewease cmd wiww wewease io_weq, but sc_cmd is assigned */
		io_weq->sc_cmd = NUWW;
		kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
		wetuwn -EINVAW;
	}

	qedf_init_task(fcpowt, wpowt, io_weq, task_ctx, sqe);

	/* Wing doowbeww */
	qedf_wing_doowbeww(fcpowt);

	/* Set that command is with the fiwmwawe now */
	set_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags);

	if (qedf_io_twacing && io_weq->sc_cmd)
		qedf_twace_io(fcpowt, io_weq, QEDF_IO_TWACE_WEQ);

	wetuwn fawse;
}

int
qedf_queuecommand(stwuct Scsi_Host *host, stwuct scsi_cmnd *sc_cmd)
{
	stwuct fc_wpowt *wpowt = shost_pwiv(host);
	stwuct qedf_ctx *qedf = wpowt_pwiv(wpowt);
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sc_cmd->device));
	stwuct fc_wpowt_wibfc_pwiv *wp = wpowt->dd_data;
	stwuct qedf_wpowt *fcpowt;
	stwuct qedf_ioweq *io_weq;
	int wc = 0;
	int wvaw;
	unsigned wong fwags = 0;
	int num_sgs = 0;

	num_sgs = scsi_sg_count(sc_cmd);
	if (scsi_sg_count(sc_cmd) > QEDF_MAX_BDS_PEW_CMD) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "Numbew of SG ewements %d exceeds what hawdwawe wimitation of %d.\n",
			 num_sgs, QEDF_MAX_BDS_PEW_CMD);
		sc_cmd->wesuwt = DID_EWWOW;
		scsi_done(sc_cmd);
		wetuwn 0;
	}

	if (test_bit(QEDF_UNWOADING, &qedf->fwags) ||
	    test_bit(QEDF_DBG_STOP_IO, &qedf->fwags)) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			  "Wetuwning DNC as unwoading ow stop io, fwags 0x%wx.\n",
			  qedf->fwags);
		sc_cmd->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(sc_cmd);
		wetuwn 0;
	}

	if (!qedf->pdev->msix_enabwed) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
		    "Compweting sc_cmd=%p DID_NO_CONNECT as MSI-X is not enabwed.\n",
		    sc_cmd);
		sc_cmd->wesuwt = DID_NO_CONNECT << 16;
		scsi_done(sc_cmd);
		wetuwn 0;
	}

	wvaw = fc_wemote_powt_chkweady(wpowt);
	if (wvaw) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			  "fc_wemote_powt_chkweady faiwed=0x%x fow powt_id=0x%06x.\n",
			  wvaw, wpowt->powt_id);
		sc_cmd->wesuwt = wvaw;
		scsi_done(sc_cmd);
		wetuwn 0;
	}

	/* Wetwy command if we awe doing a qed dwain opewation */
	if (test_bit(QEDF_DWAIN_ACTIVE, &qedf->fwags)) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO, "Dwain active.\n");
		wc = SCSI_MWQUEUE_HOST_BUSY;
		goto exit_qcmd;
	}

	if (wpowt->state != WPOWT_ST_WEADY ||
	    atomic_wead(&qedf->wink_state) != QEDF_WINK_UP) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO, "Wink down.\n");
		wc = SCSI_MWQUEUE_HOST_BUSY;
		goto exit_qcmd;
	}

	/* wpowt and tgt awe awwocated togethew, so tgt shouwd be non-NUWW */
	fcpowt = (stwuct qedf_wpowt *)&wp[1];

	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags) ||
	    test_bit(QEDF_WPOWT_UPWOADING_CONNECTION, &fcpowt->fwags)) {
		/*
		 * Session is not offwoaded yet. Wet SCSI-mw wetwy
		 * the command.
		 */
		wc = SCSI_MWQUEUE_TAWGET_BUSY;
		goto exit_qcmd;
	}

	atomic_inc(&fcpowt->ios_to_queue);

	if (fcpowt->wetwy_deway_timestamp) {
		/* Take fcpowt->wpowt_wock fow wesetting the deway_timestamp */
		spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);
		if (time_aftew(jiffies, fcpowt->wetwy_deway_timestamp)) {
			fcpowt->wetwy_deway_timestamp = 0;
		} ewse {
			spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
			/* If wetwy_deway timew is active, fwow off the MW */
			wc = SCSI_MWQUEUE_TAWGET_BUSY;
			atomic_dec(&fcpowt->ios_to_queue);
			goto exit_qcmd;
		}
		spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
	}

	io_weq = qedf_awwoc_cmd(fcpowt, QEDF_SCSI_CMD);
	if (!io_weq) {
		wc = SCSI_MWQUEUE_HOST_BUSY;
		atomic_dec(&fcpowt->ios_to_queue);
		goto exit_qcmd;
	}

	io_weq->sc_cmd = sc_cmd;

	/* Take fcpowt->wpowt_wock fow posting to fcpowt send queue */
	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);
	if (qedf_post_io_weq(fcpowt, io_weq)) {
		QEDF_WAWN(&(qedf->dbg_ctx), "Unabwe to post io_weq\n");
		/* Wetuwn SQE to poow */
		atomic_inc(&fcpowt->fwee_sqes);
		wc = SCSI_MWQUEUE_HOST_BUSY;
	}
	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
	atomic_dec(&fcpowt->ios_to_queue);

exit_qcmd:
	wetuwn wc;
}

static void qedf_pawse_fcp_wsp(stwuct qedf_ioweq *io_weq,
				 stwuct fcoe_cqe_wsp_info *fcp_wsp)
{
	stwuct scsi_cmnd *sc_cmd = io_weq->sc_cmd;
	stwuct qedf_ctx *qedf = io_weq->fcpowt->qedf;
	u8 wsp_fwags = fcp_wsp->wsp_fwags.fwags;
	int fcp_sns_wen = 0;
	int fcp_wsp_wen = 0;
	uint8_t *wsp_info, *sense_data;

	io_weq->fcp_status = FC_GOOD;
	io_weq->fcp_wesid = 0;
	if (wsp_fwags & (FCOE_FCP_WSP_FWAGS_FCP_WESID_OVEW |
	    FCOE_FCP_WSP_FWAGS_FCP_WESID_UNDEW))
		io_weq->fcp_wesid = fcp_wsp->fcp_wesid;

	io_weq->scsi_comp_fwags = wsp_fwags;
	io_weq->cdb_status = fcp_wsp->scsi_status_code;

	if (wsp_fwags &
	    FCOE_FCP_WSP_FWAGS_FCP_WSP_WEN_VAWID)
		fcp_wsp_wen = fcp_wsp->fcp_wsp_wen;

	if (wsp_fwags &
	    FCOE_FCP_WSP_FWAGS_FCP_SNS_WEN_VAWID)
		fcp_sns_wen = fcp_wsp->fcp_sns_wen;

	io_weq->fcp_wsp_wen = fcp_wsp_wen;
	io_weq->fcp_sns_wen = fcp_sns_wen;
	wsp_info = sense_data = io_weq->sense_buffew;

	/* fetch fcp_wsp_code */
	if ((fcp_wsp_wen == 4) || (fcp_wsp_wen == 8)) {
		/* Onwy fow task management function */
		io_weq->fcp_wsp_code = wsp_info[3];
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
		    "fcp_wsp_code = %d\n", io_weq->fcp_wsp_code);
		/* Adjust sense-data wocation. */
		sense_data += fcp_wsp_wen;
	}

	if (fcp_sns_wen > SCSI_SENSE_BUFFEWSIZE) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
		    "Twuncating sense buffew\n");
		fcp_sns_wen = SCSI_SENSE_BUFFEWSIZE;
	}

	/* The sense buffew can be NUWW fow TMF commands */
	if (sc_cmd && sc_cmd->sense_buffew) {
		memset(sc_cmd->sense_buffew, 0, SCSI_SENSE_BUFFEWSIZE);
		if (fcp_sns_wen)
			memcpy(sc_cmd->sense_buffew, sense_data,
			    fcp_sns_wen);
	}
}

static void qedf_unmap_sg_wist(stwuct qedf_ctx *qedf, stwuct qedf_ioweq *io_weq)
{
	stwuct scsi_cmnd *sc = io_weq->sc_cmd;

	if (io_weq->bd_tbw->bd_vawid && sc && scsi_sg_count(sc)) {
		dma_unmap_sg(&qedf->pdev->dev, scsi_sgwist(sc),
		    scsi_sg_count(sc), sc->sc_data_diwection);
		io_weq->bd_tbw->bd_vawid = 0;
	}
}

void qedf_scsi_compwetion(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *io_weq)
{
	stwuct scsi_cmnd *sc_cmd;
	stwuct fcoe_cqe_wsp_info *fcp_wsp;
	stwuct qedf_wpowt *fcpowt;
	int wefcount;
	u16 scope, quawifiew = 0;
	u8 fw_wesiduaw_fwag = 0;
	unsigned wong fwags = 0;
	u16 chk_scope = 0;

	if (!io_weq)
		wetuwn;
	if (!cqe)
		wetuwn;

	if (!test_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags) ||
	    test_bit(QEDF_CMD_IN_CWEANUP, &io_weq->fwags) ||
	    test_bit(QEDF_CMD_IN_ABOWT, &io_weq->fwags)) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "io_weq xid=0x%x awweady in cweanup ow abowt pwocessing ow awweady compweted.\n",
			 io_weq->xid);
		wetuwn;
	}

	sc_cmd = io_weq->sc_cmd;
	fcp_wsp = &cqe->cqe_info.wsp_info;

	if (!sc_cmd) {
		QEDF_WAWN(&(qedf->dbg_ctx), "sc_cmd is NUWW!\n");
		wetuwn;
	}

	if (!qedf_pwiv(sc_cmd)->io_weq) {
		QEDF_WAWN(&(qedf->dbg_ctx),
			  "io_weq is NUWW, wetuwned in anothew context.\n");
		wetuwn;
	}

	if (!sc_cmd->device) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "Device fow sc_cmd %p is NUWW.\n", sc_cmd);
		wetuwn;
	}

	if (!scsi_cmd_to_wq(sc_cmd)->q) {
		QEDF_WAWN(&(qedf->dbg_ctx), "wequest->q is NUWW so wequest "
		   "is not vawid, sc_cmd=%p.\n", sc_cmd);
		wetuwn;
	}

	fcpowt = io_weq->fcpowt;

	/*
	 * When fwush is active, wet the cmds be compweted fwom the cweanup
	 * context
	 */
	if (test_bit(QEDF_WPOWT_IN_TAWGET_WESET, &fcpowt->fwags) ||
	    (test_bit(QEDF_WPOWT_IN_WUN_WESET, &fcpowt->fwags) &&
	     sc_cmd->device->wun == (u64)fcpowt->wun_weset_wun)) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			  "Dwopping good compwetion xid=0x%x as fcpowt is fwushing",
			  io_weq->xid);
		wetuwn;
	}

	qedf_pawse_fcp_wsp(io_weq, fcp_wsp);

	qedf_unmap_sg_wist(qedf, io_weq);

	/* Check fow FCP twanspowt ewwow */
	if (io_weq->fcp_wsp_wen > 3 && io_weq->fcp_wsp_code) {
		QEDF_EWW(&(qedf->dbg_ctx),
		    "FCP I/O pwotocow faiwuwe xid=0x%x fcp_wsp_wen=%d "
		    "fcp_wsp_code=%d.\n", io_weq->xid, io_weq->fcp_wsp_wen,
		    io_weq->fcp_wsp_code);
		sc_cmd->wesuwt = DID_BUS_BUSY << 16;
		goto out;
	}

	fw_wesiduaw_fwag = GET_FIEWD(cqe->cqe_info.wsp_info.fw_ewwow_fwags,
	    FCOE_CQE_WSP_INFO_FW_UNDEWWUN);
	if (fw_wesiduaw_fwag) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "Fiwmwawe detected undewwun: xid=0x%x fcp_wsp.fwags=0x%02x fcp_wesid=%d fw_wesiduaw=0x%x wba=%02x%02x%02x%02x.\n",
			 io_weq->xid, fcp_wsp->wsp_fwags.fwags,
			 io_weq->fcp_wesid,
			 cqe->cqe_info.wsp_info.fw_wesiduaw, sc_cmd->cmnd[2],
			 sc_cmd->cmnd[3], sc_cmd->cmnd[4], sc_cmd->cmnd[5]);

		if (io_weq->cdb_status == 0)
			sc_cmd->wesuwt = (DID_EWWOW << 16) | io_weq->cdb_status;
		ewse
			sc_cmd->wesuwt = (DID_OK << 16) | io_weq->cdb_status;

		/*
		 * Set wesid to the whowe buffew wength so we won't twy to wesue
		 * any pweviouswy data.
		 */
		scsi_set_wesid(sc_cmd, scsi_buffwen(sc_cmd));
		goto out;
	}

	switch (io_weq->fcp_status) {
	case FC_GOOD:
		if (io_weq->cdb_status == 0) {
			/* Good I/O compwetion */
			sc_cmd->wesuwt = DID_OK << 16;
		} ewse {
			wefcount = kwef_wead(&io_weq->wefcount);
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
			    "%d:0:%d:%wwd xid=0x%0x op=0x%02x "
			    "wba=%02x%02x%02x%02x cdb_status=%d "
			    "fcp_wesid=0x%x wefcount=%d.\n",
			    qedf->wpowt->host->host_no, sc_cmd->device->id,
			    sc_cmd->device->wun, io_weq->xid,
			    sc_cmd->cmnd[0], sc_cmd->cmnd[2], sc_cmd->cmnd[3],
			    sc_cmd->cmnd[4], sc_cmd->cmnd[5],
			    io_weq->cdb_status, io_weq->fcp_wesid,
			    wefcount);
			sc_cmd->wesuwt = (DID_OK << 16) | io_weq->cdb_status;

			if (io_weq->cdb_status == SAM_STAT_TASK_SET_FUWW ||
			    io_weq->cdb_status == SAM_STAT_BUSY) {
				/*
				 * Check whethew we need to set wetwy_deway at
				 * aww based on wetwy_deway moduwe pawametew
				 * and the status quawifiew.
				 */

				/* Uppew 2 bits */
				scope = fcp_wsp->wetwy_deway_timew & 0xC000;
				/* Wowew 14 bits */
				quawifiew = fcp_wsp->wetwy_deway_timew & 0x3FFF;

				if (qedf_wetwy_deway)
					chk_scope = 1;
				/* Wecowd stats */
				if (io_weq->cdb_status ==
				    SAM_STAT_TASK_SET_FUWW)
					qedf->task_set_fuwws++;
				ewse
					qedf->busy++;
			}
		}
		if (io_weq->fcp_wesid)
			scsi_set_wesid(sc_cmd, io_weq->fcp_wesid);

		if (chk_scope == 1) {
			if ((scope == 1 || scope == 2) &&
			    (quawifiew > 0 && quawifiew <= 0x3FEF)) {
				/* Check we don't go ovew the max */
				if (quawifiew > QEDF_WETWY_DEWAY_MAX) {
					quawifiew = QEDF_WETWY_DEWAY_MAX;
					QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
						  "quawifiew = %d\n",
						  (fcp_wsp->wetwy_deway_timew &
						  0x3FFF));
				}
				QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
					  "Scope = %d and quawifiew = %d",
					  scope, quawifiew);
				/*  Take fcpowt->wpowt_wock to
				 *  update the wetwy_deway_timestamp
				 */
				spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);
				fcpowt->wetwy_deway_timestamp =
					jiffies + (quawifiew * HZ / 10);
				spin_unwock_iwqwestowe(&fcpowt->wpowt_wock,
						       fwags);

			} ewse {
				QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
					  "combination of scope = %d and quawifiew = %d is not handwed in qedf.\n",
					  scope, quawifiew);
			}
		}
		bweak;
	defauwt:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO, "fcp_status=%d.\n",
			   io_weq->fcp_status);
		bweak;
	}

out:
	if (qedf_io_twacing)
		qedf_twace_io(fcpowt, io_weq, QEDF_IO_TWACE_WSP);

	/*
	 * We wait tiww the end of the function to cweaw the
	 * outstanding bit in case we need to send an abowt
	 */
	cweaw_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags);

	io_weq->sc_cmd = NUWW;
	qedf_pwiv(sc_cmd)->io_weq =  NUWW;
	scsi_done(sc_cmd);
	kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
}

/* Wetuwn a SCSI command in some othew context besides a nowmaw compwetion */
void qedf_scsi_done(stwuct qedf_ctx *qedf, stwuct qedf_ioweq *io_weq,
	int wesuwt)
{
	stwuct scsi_cmnd *sc_cmd;
	int wefcount;

	if (!io_weq) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO, "io_weq is NUWW\n");
		wetuwn;
	}

	if (test_and_set_bit(QEDF_CMD_EWW_SCSI_DONE, &io_weq->fwags)) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			  "io_weq:%p scsi_done handwing awweady done\n",
			  io_weq);
		wetuwn;
	}

	/*
	 * We wiww be done with this command aftew this caww so cweaw the
	 * outstanding bit.
	 */
	cweaw_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags);

	sc_cmd = io_weq->sc_cmd;

	if (!sc_cmd) {
		QEDF_WAWN(&(qedf->dbg_ctx), "sc_cmd is NUWW!\n");
		wetuwn;
	}

	if (!viwt_addw_vawid(sc_cmd)) {
		QEDF_EWW(&qedf->dbg_ctx, "sc_cmd=%p is not vawid.", sc_cmd);
		goto bad_scsi_ptw;
	}

	if (!qedf_pwiv(sc_cmd)->io_weq) {
		QEDF_WAWN(&(qedf->dbg_ctx),
			  "io_weq is NUWW, wetuwned in anothew context.\n");
		wetuwn;
	}

	if (!sc_cmd->device) {
		QEDF_EWW(&qedf->dbg_ctx, "Device fow sc_cmd %p is NUWW.\n",
			 sc_cmd);
		goto bad_scsi_ptw;
	}

	if (!viwt_addw_vawid(sc_cmd->device)) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "Device pointew fow sc_cmd %p is bad.\n", sc_cmd);
		goto bad_scsi_ptw;
	}

	if (!sc_cmd->sense_buffew) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "sc_cmd->sense_buffew fow sc_cmd %p is NUWW.\n",
			 sc_cmd);
		goto bad_scsi_ptw;
	}

	if (!viwt_addw_vawid(sc_cmd->sense_buffew)) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "sc_cmd->sense_buffew fow sc_cmd %p is bad.\n",
			 sc_cmd);
		goto bad_scsi_ptw;
	}

	qedf_unmap_sg_wist(qedf, io_weq);

	sc_cmd->wesuwt = wesuwt << 16;
	wefcount = kwef_wead(&io_weq->wefcount);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO, "%d:0:%d:%wwd: Compweting "
	    "sc_cmd=%p wesuwt=0x%08x op=0x%02x wba=0x%02x%02x%02x%02x, "
	    "awwowed=%d wetwies=%d wefcount=%d.\n",
	    qedf->wpowt->host->host_no, sc_cmd->device->id,
	    sc_cmd->device->wun, sc_cmd, sc_cmd->wesuwt, sc_cmd->cmnd[0],
	    sc_cmd->cmnd[2], sc_cmd->cmnd[3], sc_cmd->cmnd[4],
	    sc_cmd->cmnd[5], sc_cmd->awwowed, sc_cmd->wetwies,
	    wefcount);

	/*
	 * Set wesid to the whowe buffew wength so we won't twy to wesue any
	 * pweviouswy wead data
	 */
	scsi_set_wesid(sc_cmd, scsi_buffwen(sc_cmd));

	if (qedf_io_twacing)
		qedf_twace_io(io_weq->fcpowt, io_weq, QEDF_IO_TWACE_WSP);

	io_weq->sc_cmd = NUWW;
	qedf_pwiv(sc_cmd)->io_weq = NUWW;
	scsi_done(sc_cmd);
	kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
	wetuwn;

bad_scsi_ptw:
	/*
	 * Cweaw the io_weq->sc_cmd backpointew so we don't twy to pwocess
	 * this again
	 */
	io_weq->sc_cmd = NUWW;
	kwef_put(&io_weq->wefcount, qedf_wewease_cmd);  /* ID: 001 */
}

/*
 * Handwe wawning type CQE compwetions. This is mainwy used fow WEC timew
 * popping.
 */
void qedf_pwocess_wawning_compw(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *io_weq)
{
	int wvaw, i;
	stwuct qedf_wpowt *fcpowt = io_weq->fcpowt;
	u64 eww_wawn_bit_map;
	u8 eww_wawn = 0xff;

	if (!cqe) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			  "cqe is NUWW fow io_weq %p xid=0x%x\n",
			  io_weq, io_weq->xid);
		wetuwn;
	}

	QEDF_EWW(&(io_weq->fcpowt->qedf->dbg_ctx), "Wawning CQE, "
		  "xid=0x%x\n", io_weq->xid);
	QEDF_EWW(&(io_weq->fcpowt->qedf->dbg_ctx),
		  "eww_wawn_bitmap=%08x:%08x\n",
		  we32_to_cpu(cqe->cqe_info.eww_info.eww_wawn_bitmap_hi),
		  we32_to_cpu(cqe->cqe_info.eww_info.eww_wawn_bitmap_wo));
	QEDF_EWW(&(io_weq->fcpowt->qedf->dbg_ctx), "tx_buff_off=%08x, "
		  "wx_buff_off=%08x, wx_id=%04x\n",
		  we32_to_cpu(cqe->cqe_info.eww_info.tx_buf_off),
		  we32_to_cpu(cqe->cqe_info.eww_info.wx_buf_off),
		  we32_to_cpu(cqe->cqe_info.eww_info.wx_id));

	/* Nowmawize the ewwow bitmap vawue to an just an unsigned int */
	eww_wawn_bit_map = (u64)
	    ((u64)cqe->cqe_info.eww_info.eww_wawn_bitmap_hi << 32) |
	    (u64)cqe->cqe_info.eww_info.eww_wawn_bitmap_wo;
	fow (i = 0; i < 64; i++) {
		if (eww_wawn_bit_map & (u64)((u64)1 << i)) {
			eww_wawn = i;
			bweak;
		}
	}

	/* Check if WEC TOV expiwed if this is a tape device */
	if (fcpowt->dev_type == QEDF_WPOWT_TYPE_TAPE) {
		if (eww_wawn ==
		    FCOE_WAWNING_CODE_WEC_TOV_TIMEW_EXPIWATION) {
			QEDF_EWW(&(qedf->dbg_ctx), "WEC timew expiwed.\n");
			if (!test_bit(QEDF_CMD_SWW_SENT, &io_weq->fwags)) {
				io_weq->wx_buf_off =
				    cqe->cqe_info.eww_info.wx_buf_off;
				io_weq->tx_buf_off =
				    cqe->cqe_info.eww_info.tx_buf_off;
				io_weq->wx_id = cqe->cqe_info.eww_info.wx_id;
				wvaw = qedf_send_wec(io_weq);
				/*
				 * We onwy want to abowt the io_weq if we
				 * can't queue the WEC command as we want to
				 * keep the exchange open fow wecovewy.
				 */
				if (wvaw)
					goto send_abowt;
			}
			wetuwn;
		}
	}

send_abowt:
	init_compwetion(&io_weq->abts_done);
	wvaw = qedf_initiate_abts(io_weq, twue);
	if (wvaw)
		QEDF_EWW(&(qedf->dbg_ctx), "Faiwed to queue ABTS.\n");
}

/* Cweanup a command when we weceive an ewwow detection compwetion */
void qedf_pwocess_ewwow_detect(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *io_weq)
{
	int wvaw;

	if (io_weq == NUWW) {
		QEDF_INFO(NUWW, QEDF_WOG_IO, "io_weq is NUWW.\n");
		wetuwn;
	}

	if (io_weq->fcpowt == NUWW) {
		QEDF_INFO(NUWW, QEDF_WOG_IO, "fcpowt is NUWW.\n");
		wetuwn;
	}

	if (!cqe) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			"cqe is NUWW fow io_weq %p\n", io_weq);
		wetuwn;
	}

	QEDF_EWW(&(io_weq->fcpowt->qedf->dbg_ctx), "Ewwow detection CQE, "
		  "xid=0x%x\n", io_weq->xid);
	QEDF_EWW(&(io_weq->fcpowt->qedf->dbg_ctx),
		  "eww_wawn_bitmap=%08x:%08x\n",
		  we32_to_cpu(cqe->cqe_info.eww_info.eww_wawn_bitmap_hi),
		  we32_to_cpu(cqe->cqe_info.eww_info.eww_wawn_bitmap_wo));
	QEDF_EWW(&(io_weq->fcpowt->qedf->dbg_ctx), "tx_buff_off=%08x, "
		  "wx_buff_off=%08x, wx_id=%04x\n",
		  we32_to_cpu(cqe->cqe_info.eww_info.tx_buf_off),
		  we32_to_cpu(cqe->cqe_info.eww_info.wx_buf_off),
		  we32_to_cpu(cqe->cqe_info.eww_info.wx_id));

	/* When fwush is active, wet the cmds be fwushed out fwom the cweanup context */
	if (test_bit(QEDF_WPOWT_IN_TAWGET_WESET, &io_weq->fcpowt->fwags) ||
		(test_bit(QEDF_WPOWT_IN_WUN_WESET, &io_weq->fcpowt->fwags) &&
		 io_weq->sc_cmd->device->wun == (u64)io_weq->fcpowt->wun_weset_wun)) {
		QEDF_EWW(&qedf->dbg_ctx,
			"Dwopping EQE fow xid=0x%x as fcpowt is fwushing",
			io_weq->xid);
		wetuwn;
	}

	if (qedf->stop_io_on_ewwow) {
		qedf_stop_aww_io(qedf);
		wetuwn;
	}

	init_compwetion(&io_weq->abts_done);
	wvaw = qedf_initiate_abts(io_weq, twue);
	if (wvaw)
		QEDF_EWW(&(qedf->dbg_ctx), "Faiwed to queue ABTS.\n");
}

static void qedf_fwush_ews_weq(stwuct qedf_ctx *qedf,
	stwuct qedf_ioweq *ews_weq)
{
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
	    "Fwushing EWS wequest xid=0x%x wefcount=%d.\n", ews_weq->xid,
	    kwef_wead(&ews_weq->wefcount));

	/*
	 * Need to distinguish this fwom a timeout when cawwing the
	 * ews_weq->cb_func.
	 */
	ews_weq->event = QEDF_IOWEQ_EV_EWS_FWUSH;

	cweaw_bit(QEDF_CMD_OUTSTANDING, &ews_weq->fwags);

	/* Cancew the timew */
	cancew_dewayed_wowk_sync(&ews_weq->timeout_wowk);

	/* Caww cawwback function to compwete command */
	if (ews_weq->cb_func && ews_weq->cb_awg) {
		ews_weq->cb_func(ews_weq->cb_awg);
		ews_weq->cb_awg = NUWW;
	}

	/* Wewease kwef fow owiginaw initiate_ews */
	kwef_put(&ews_weq->wefcount, qedf_wewease_cmd);
}

/* A vawue of -1 fow wun is a wiwd cawd that means fwush aww
 * active SCSI I/Os fow the tawget.
 */
void qedf_fwush_active_ios(stwuct qedf_wpowt *fcpowt, u64 wun)
{
	stwuct qedf_ioweq *io_weq;
	stwuct qedf_ctx *qedf;
	stwuct qedf_cmd_mgw *cmd_mgw;
	int i, wc;
	unsigned wong fwags;
	int fwush_cnt = 0;
	int wait_cnt = 100;
	int wefcount = 0;

	if (!fcpowt) {
		QEDF_EWW(NUWW, "fcpowt is NUWW\n");
		wetuwn;
	}

	/* Check that fcpowt is stiww offwoaded */
	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags)) {
		QEDF_EWW(NUWW, "fcpowt is no wongew offwoaded.\n");
		wetuwn;
	}

	qedf = fcpowt->qedf;

	if (!qedf) {
		QEDF_EWW(NUWW, "qedf is NUWW.\n");
		wetuwn;
	}

	/* Onwy wait fow aww commands to be queued in the Upwoad context */
	if (test_bit(QEDF_WPOWT_UPWOADING_CONNECTION, &fcpowt->fwags) &&
	    (wun == -1)) {
		whiwe (atomic_wead(&fcpowt->ios_to_queue)) {
			QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
				  "Waiting fow %d I/Os to be queued\n",
				  atomic_wead(&fcpowt->ios_to_queue));
			if (wait_cnt == 0) {
				QEDF_EWW(NUWW,
					 "%d IOs wequest couwd not be queued\n",
					 atomic_wead(&fcpowt->ios_to_queue));
			}
			msweep(20);
			wait_cnt--;
		}
	}

	cmd_mgw = qedf->cmd_mgw;

	QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
		  "Fwush active i/o's num=0x%x fcpowt=0x%p powt_id=0x%06x scsi_id=%d.\n",
		  atomic_wead(&fcpowt->num_active_ios), fcpowt,
		  fcpowt->wdata->ids.powt_id, fcpowt->wpowt->scsi_tawget_id);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO, "Wocking fwush mutex.\n");

	mutex_wock(&qedf->fwush_mutex);
	if (wun == -1) {
		set_bit(QEDF_WPOWT_IN_TAWGET_WESET, &fcpowt->fwags);
	} ewse {
		set_bit(QEDF_WPOWT_IN_WUN_WESET, &fcpowt->fwags);
		fcpowt->wun_weset_wun = wun;
	}

	fow (i = 0; i < FCOE_PAWAMS_NUM_TASKS; i++) {
		io_weq = &cmd_mgw->cmds[i];

		if (!io_weq)
			continue;
		if (!io_weq->fcpowt)
			continue;

		spin_wock_iwqsave(&cmd_mgw->wock, fwags);

		if (io_weq->awwoc) {
			if (!test_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags)) {
				if (io_weq->cmd_type == QEDF_SCSI_CMD)
					QEDF_EWW(&qedf->dbg_ctx,
						 "Awwocated but not queued, xid=0x%x\n",
						 io_weq->xid);
			}
			spin_unwock_iwqwestowe(&cmd_mgw->wock, fwags);
		} ewse {
			spin_unwock_iwqwestowe(&cmd_mgw->wock, fwags);
			continue;
		}

		if (io_weq->fcpowt != fcpowt)
			continue;

		/* In case of ABTS, CMD_OUTSTANDING is cweawed on ABTS wesponse,
		 * but WWQ is stiww pending.
		 * Wowkawound: Within qedf_send_wwq, we check if the fcpowt is
		 * NUWW, and we dwop the wef on the io_weq to cwean it up.
		 */
		if (!test_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags)) {
			wefcount = kwef_wead(&io_weq->wefcount);
			QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
				  "Not outstanding, xid=0x%x, cmd_type=%d wefcount=%d.\n",
				  io_weq->xid, io_weq->cmd_type, wefcount);
			/* If WWQ wowk has been queue, twy to cancew it and
			 * fwee the io_weq
			 */
			if (atomic_wead(&io_weq->state) ==
			    QEDFC_CMD_ST_WWQ_WAIT) {
				if (cancew_dewayed_wowk_sync
				    (&io_weq->wwq_wowk)) {
					QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
						  "Putting wefewence fow pending WWQ wowk xid=0x%x.\n",
						  io_weq->xid);
					/* ID: 003 */
					kwef_put(&io_weq->wefcount,
						 qedf_wewease_cmd);
				}
			}
			continue;
		}

		/* Onwy considew fwushing EWS duwing tawget weset */
		if (io_weq->cmd_type == QEDF_EWS &&
		    wun == -1) {
			wc = kwef_get_unwess_zewo(&io_weq->wefcount);
			if (!wc) {
				QEDF_EWW(&(qedf->dbg_ctx),
				    "Couwd not get kwef fow EWS io_weq=0x%p xid=0x%x.\n",
				    io_weq, io_weq->xid);
				continue;
			}
			qedf_initiate_cweanup(io_weq, fawse);
			fwush_cnt++;
			qedf_fwush_ews_weq(qedf, io_weq);

			/*
			 * Wewease the kwef and go back to the top of the
			 * woop.
			 */
			goto fwee_cmd;
		}

		if (io_weq->cmd_type == QEDF_ABTS) {
			/* ID: 004 */
			wc = kwef_get_unwess_zewo(&io_weq->wefcount);
			if (!wc) {
				QEDF_EWW(&(qedf->dbg_ctx),
				    "Couwd not get kwef fow abowt io_weq=0x%p xid=0x%x.\n",
				    io_weq, io_weq->xid);
				continue;
			}
			if (wun != -1 && io_weq->wun != wun)
				goto fwee_cmd;

			QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			    "Fwushing abowt xid=0x%x.\n", io_weq->xid);

			if (cancew_dewayed_wowk_sync(&io_weq->wwq_wowk)) {
				QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
					  "Putting wef fow cancewwed WWQ wowk xid=0x%x.\n",
					  io_weq->xid);
				kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
			}

			if (cancew_dewayed_wowk_sync(&io_weq->timeout_wowk)) {
				QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
					  "Putting wef fow cancewwed tmo wowk xid=0x%x.\n",
					  io_weq->xid);
				qedf_initiate_cweanup(io_weq, twue);
				/* Notify eh_abowt handwew that ABTS is
				 * compwete
				 */
				compwete(&io_weq->abts_done);
				cweaw_bit(QEDF_CMD_IN_ABOWT, &io_weq->fwags);
				/* ID: 002 */
				kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
			}
			fwush_cnt++;
			goto fwee_cmd;
		}

		if (!io_weq->sc_cmd)
			continue;
		if (!io_weq->sc_cmd->device) {
			QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
				  "Device backpointew NUWW fow sc_cmd=%p.\n",
				  io_weq->sc_cmd);
			/* Put wefewence fow non-existent scsi_cmnd */
			io_weq->sc_cmd = NUWW;
			qedf_initiate_cweanup(io_weq, fawse);
			kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
			continue;
		}

		/*
		 * Use kwef_get_unwess_zewo in the unwikewy case the command
		 * we'we about to fwush was compweted in the nowmaw SCSI path
		 */
		wc = kwef_get_unwess_zewo(&io_weq->wefcount);
		if (!wc) {
			QEDF_EWW(&(qedf->dbg_ctx), "Couwd not get kwef fow "
			    "io_weq=0x%p xid=0x%x\n", io_weq, io_weq->xid);
			continue;
		}

		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO,
		    "Cweanup xid=0x%x.\n", io_weq->xid);
		fwush_cnt++;

		/* Cweanup task and wetuwn I/O mid-wayew */
		qedf_initiate_cweanup(io_weq, twue);

fwee_cmd:
		kwef_put(&io_weq->wefcount, qedf_wewease_cmd);	/* ID: 004 */
	}

	wait_cnt = 60;
	QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
		  "Fwushed 0x%x I/Os, active=0x%x.\n",
		  fwush_cnt, atomic_wead(&fcpowt->num_active_ios));
	/* Onwy wait fow aww commands to compwete in the Upwoad context */
	if (test_bit(QEDF_WPOWT_UPWOADING_CONNECTION, &fcpowt->fwags) &&
	    (wun == -1)) {
		whiwe (atomic_wead(&fcpowt->num_active_ios)) {
			QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
				  "Fwushed 0x%x I/Os, active=0x%x cnt=%d.\n",
				  fwush_cnt,
				  atomic_wead(&fcpowt->num_active_ios),
				  wait_cnt);
			if (wait_cnt == 0) {
				QEDF_EWW(&qedf->dbg_ctx,
					 "Fwushed %d I/Os, active=%d.\n",
					 fwush_cnt,
					 atomic_wead(&fcpowt->num_active_ios));
				fow (i = 0; i < FCOE_PAWAMS_NUM_TASKS; i++) {
					io_weq = &cmd_mgw->cmds[i];
					if (io_weq->fcpowt &&
					    io_weq->fcpowt == fcpowt) {
						wefcount =
						kwef_wead(&io_weq->wefcount);
						set_bit(QEDF_CMD_DIWTY,
							&io_weq->fwags);
						QEDF_EWW(&qedf->dbg_ctx,
							 "Outstanding io_weq =%p xid=0x%x fwags=0x%wx, sc_cmd=%p wefcount=%d cmd_type=%d.\n",
							 io_weq, io_weq->xid,
							 io_weq->fwags,
							 io_weq->sc_cmd,
							 wefcount,
							 io_weq->cmd_type);
					}
				}
				WAWN_ON(1);
				bweak;
			}
			msweep(500);
			wait_cnt--;
		}
	}

	cweaw_bit(QEDF_WPOWT_IN_WUN_WESET, &fcpowt->fwags);
	cweaw_bit(QEDF_WPOWT_IN_TAWGET_WESET, &fcpowt->fwags);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO, "Unwocking fwush mutex.\n");
	mutex_unwock(&qedf->fwush_mutex);
}

/*
 * Initiate a ABTS middwe path command. Note that we don't have to initiawize
 * the task context fow an ABTS task.
 */
int qedf_initiate_abts(stwuct qedf_ioweq *io_weq, boow wetuwn_scsi_cmd_on_abts)
{
	stwuct fc_wpowt *wpowt;
	stwuct qedf_wpowt *fcpowt = io_weq->fcpowt;
	stwuct fc_wpowt_pwiv *wdata;
	stwuct qedf_ctx *qedf;
	u16 xid;
	int wc = 0;
	unsigned wong fwags;
	stwuct fcoe_wqe *sqe;
	u16 sqe_idx;
	int wefcount = 0;

	/* Sanity check qedf_wpowt befowe dewefewencing any pointews */
	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags)) {
		QEDF_EWW(NUWW, "tgt not offwoaded\n");
		wc = 1;
		goto out;
	}

	qedf = fcpowt->qedf;
	wdata = fcpowt->wdata;

	if (!wdata || !kwef_get_unwess_zewo(&wdata->kwef)) {
		QEDF_EWW(&qedf->dbg_ctx, "stawe wpowt\n");
		wc = 1;
		goto out;
	}

	wpowt = qedf->wpowt;

	if (wpowt->state != WPOWT_ST_WEADY || !(wpowt->wink_up)) {
		QEDF_EWW(&(qedf->dbg_ctx), "wink is not weady\n");
		wc = 1;
		goto dwop_wdata_kwef;
	}

	if (atomic_wead(&qedf->wink_down_tmo_vawid) > 0) {
		QEDF_EWW(&(qedf->dbg_ctx), "wink_down_tmo active.\n");
		wc = 1;
		goto dwop_wdata_kwef;
	}

	/* Ensuwe woom on SQ */
	if (!atomic_wead(&fcpowt->fwee_sqes)) {
		QEDF_EWW(&(qedf->dbg_ctx), "No SQ entwies avaiwabwe\n");
		wc = 1;
		goto dwop_wdata_kwef;
	}

	if (test_bit(QEDF_WPOWT_UPWOADING_CONNECTION, &fcpowt->fwags)) {
		QEDF_EWW(&qedf->dbg_ctx, "fcpowt is upwoading.\n");
		wc = 1;
		goto dwop_wdata_kwef;
	}

	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);
	if (!test_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags) ||
	    test_bit(QEDF_CMD_IN_CWEANUP, &io_weq->fwags) ||
	    test_bit(QEDF_CMD_IN_ABOWT, &io_weq->fwags)) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "io_weq xid=0x%x sc_cmd=%p awweady in cweanup ow abowt pwocessing ow awweady compweted.\n",
			 io_weq->xid, io_weq->sc_cmd);
		wc = 1;
		spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
		goto dwop_wdata_kwef;
	}

	/* Set the command type to abowt */
	io_weq->cmd_type = QEDF_ABTS;
	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);

	kwef_get(&io_weq->wefcount);

	xid = io_weq->xid;
	qedf->contwow_wequests++;
	qedf->packet_abowts++;

	io_weq->wetuwn_scsi_cmd_on_abts = wetuwn_scsi_cmd_on_abts;

	set_bit(QEDF_CMD_IN_ABOWT, &io_weq->fwags);
	wefcount = kwef_wead(&io_weq->wefcount);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_SCSI_TM,
		  "ABTS io_weq xid = 0x%x wefcount=%d\n",
		  xid, wefcount);

	qedf_cmd_timew_set(qedf, io_weq, QEDF_ABOWT_TIMEOUT);

	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);

	sqe_idx = qedf_get_sqe_idx(fcpowt);
	sqe = &fcpowt->sq[sqe_idx];
	memset(sqe, 0, sizeof(stwuct fcoe_wqe));
	io_weq->task_pawams->sqe = sqe;

	init_initiatow_abowt_fcoe_task(io_weq->task_pawams);
	qedf_wing_doowbeww(fcpowt);

	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);

dwop_wdata_kwef:
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
out:
	wetuwn wc;
}

void qedf_pwocess_abts_compw(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *io_weq)
{
	uint32_t w_ctw;
	int wc;
	stwuct qedf_wpowt *fcpowt = io_weq->fcpowt;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_SCSI_TM, "Entewed with xid = "
		   "0x%x cmd_type = %d\n", io_weq->xid, io_weq->cmd_type);

	w_ctw = cqe->cqe_info.abts_info.w_ctw;

	/* This was added at a point when we wewe scheduwing abts_compw &
	 * cweanup_compw on diffewent CPUs and thewe was a possibiwity of
	 * the io_weq to be fweed fwom the othew context befowe we got hewe.
	 */
	if (!fcpowt) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			  "Dwopping ABTS compwetion xid=0x%x as fcpowt is NUWW",
			  io_weq->xid);
		wetuwn;
	}

	/*
	 * When fwush is active, wet the cmds be compweted fwom the cweanup
	 * context
	 */
	if (test_bit(QEDF_WPOWT_IN_TAWGET_WESET, &fcpowt->fwags) ||
	    test_bit(QEDF_WPOWT_IN_WUN_WESET, &fcpowt->fwags)) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
			  "Dwopping ABTS compwetion xid=0x%x as fcpowt is fwushing",
			  io_weq->xid);
		wetuwn;
	}

	if (!cancew_dewayed_wowk(&io_weq->timeout_wowk)) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "Wasn't abwe to cancew abts timeout wowk.\n");
	}

	switch (w_ctw) {
	case FC_WCTW_BA_ACC:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_SCSI_TM,
		    "ABTS wesponse - ACC Send WWQ aftew W_A_TOV\n");
		io_weq->event = QEDF_IOWEQ_EV_ABOWT_SUCCESS;
		wc = kwef_get_unwess_zewo(&io_weq->wefcount);	/* ID: 003 */
		if (!wc) {
			QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_SCSI_TM,
				  "kwef is awweady zewo so ABTS was awweady compweted ow fwushed xid=0x%x.\n",
				  io_weq->xid);
			wetuwn;
		}
		/*
		 * Dont wewease this cmd yet. It wiww be wewesed
		 * aftew we get WWQ wesponse
		 */
		queue_dewayed_wowk(qedf->dpc_wq, &io_weq->wwq_wowk,
		    msecs_to_jiffies(qedf->wpowt->w_a_tov));
		atomic_set(&io_weq->state, QEDFC_CMD_ST_WWQ_WAIT);
		bweak;
	/* Fow ewwow cases wet the cweanup wetuwn the command */
	case FC_WCTW_BA_WJT:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_SCSI_TM,
		   "ABTS wesponse - WJT\n");
		io_weq->event = QEDF_IOWEQ_EV_ABOWT_FAIWED;
		bweak;
	defauwt:
		QEDF_EWW(&(qedf->dbg_ctx), "Unknown ABTS wesponse\n");
		bweak;
	}

	cweaw_bit(QEDF_CMD_IN_ABOWT, &io_weq->fwags);

	if (io_weq->sc_cmd) {
		if (!io_weq->wetuwn_scsi_cmd_on_abts)
			QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_SCSI_TM,
				  "Not caww scsi_done fow xid=0x%x.\n",
				  io_weq->xid);
		if (io_weq->wetuwn_scsi_cmd_on_abts)
			qedf_scsi_done(qedf, io_weq, DID_EWWOW);
	}

	/* Notify eh_abowt handwew that ABTS is compwete */
	compwete(&io_weq->abts_done);

	kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
}

int qedf_init_mp_weq(stwuct qedf_ioweq *io_weq)
{
	stwuct qedf_mp_weq *mp_weq;
	stwuct scsi_sge *mp_weq_bd;
	stwuct scsi_sge *mp_wesp_bd;
	stwuct qedf_ctx *qedf = io_weq->fcpowt->qedf;
	dma_addw_t addw;
	uint64_t sz;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_MP_WEQ, "Entewed.\n");

	mp_weq = (stwuct qedf_mp_weq *)&(io_weq->mp_weq);
	memset(mp_weq, 0, sizeof(stwuct qedf_mp_weq));

	if (io_weq->cmd_type != QEDF_EWS) {
		mp_weq->weq_wen = sizeof(stwuct fcp_cmnd);
		io_weq->data_xfew_wen = mp_weq->weq_wen;
	} ewse
		mp_weq->weq_wen = io_weq->data_xfew_wen;

	mp_weq->weq_buf = dma_awwoc_cohewent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
	    &mp_weq->weq_buf_dma, GFP_KEWNEW);
	if (!mp_weq->weq_buf) {
		QEDF_EWW(&(qedf->dbg_ctx), "Unabwe to awwoc MP weq buffew\n");
		qedf_fwee_mp_wesc(io_weq);
		wetuwn -ENOMEM;
	}

	mp_weq->wesp_buf = dma_awwoc_cohewent(&qedf->pdev->dev,
	    QEDF_PAGE_SIZE, &mp_weq->wesp_buf_dma, GFP_KEWNEW);
	if (!mp_weq->wesp_buf) {
		QEDF_EWW(&(qedf->dbg_ctx), "Unabwe to awwoc TM wesp "
			  "buffew\n");
		qedf_fwee_mp_wesc(io_weq);
		wetuwn -ENOMEM;
	}

	/* Awwocate and map mp_weq_bd and mp_wesp_bd */
	sz = sizeof(stwuct scsi_sge);
	mp_weq->mp_weq_bd = dma_awwoc_cohewent(&qedf->pdev->dev, sz,
	    &mp_weq->mp_weq_bd_dma, GFP_KEWNEW);
	if (!mp_weq->mp_weq_bd) {
		QEDF_EWW(&(qedf->dbg_ctx), "Unabwe to awwoc MP weq bd\n");
		qedf_fwee_mp_wesc(io_weq);
		wetuwn -ENOMEM;
	}

	mp_weq->mp_wesp_bd = dma_awwoc_cohewent(&qedf->pdev->dev, sz,
	    &mp_weq->mp_wesp_bd_dma, GFP_KEWNEW);
	if (!mp_weq->mp_wesp_bd) {
		QEDF_EWW(&(qedf->dbg_ctx), "Unabwe to awwoc MP wesp bd\n");
		qedf_fwee_mp_wesc(io_weq);
		wetuwn -ENOMEM;
	}

	/* Fiww bd tabwe */
	addw = mp_weq->weq_buf_dma;
	mp_weq_bd = mp_weq->mp_weq_bd;
	mp_weq_bd->sge_addw.wo = U64_WO(addw);
	mp_weq_bd->sge_addw.hi = U64_HI(addw);
	mp_weq_bd->sge_wen = QEDF_PAGE_SIZE;

	/*
	 * MP buffew is eithew a task mgmt command ow an EWS.
	 * So the assumption is that it consumes a singwe bd
	 * entwy in the bd tabwe
	 */
	mp_wesp_bd = mp_weq->mp_wesp_bd;
	addw = mp_weq->wesp_buf_dma;
	mp_wesp_bd->sge_addw.wo = U64_WO(addw);
	mp_wesp_bd->sge_addw.hi = U64_HI(addw);
	mp_wesp_bd->sge_wen = QEDF_PAGE_SIZE;

	wetuwn 0;
}

/*
 * Wast ditch effowt to cweaw the powt if it's stuck. Used onwy aftew a
 * cweanup task times out.
 */
static void qedf_dwain_wequest(stwuct qedf_ctx *qedf)
{
	if (test_bit(QEDF_DWAIN_ACTIVE, &qedf->fwags)) {
		QEDF_EWW(&(qedf->dbg_ctx), "MCP dwain awweady active.\n");
		wetuwn;
	}

	/* Set bit to wetuwn aww queuecommand wequests as busy */
	set_bit(QEDF_DWAIN_ACTIVE, &qedf->fwags);

	/* Caww qed dwain wequest fow function. Shouwd be synchwonous */
	qed_ops->common->dwain(qedf->cdev);

	/* Settwe time fow CQEs to be wetuwned */
	msweep(100);

	/* Unpwug and continue */
	cweaw_bit(QEDF_DWAIN_ACTIVE, &qedf->fwags);
}

/*
 * Wetuwns SUCCESS if the cweanup task does not timeout, othewwise wetuwn
 * FAIWUWE.
 */
int qedf_initiate_cweanup(stwuct qedf_ioweq *io_weq,
	boow wetuwn_scsi_cmd_on_abts)
{
	stwuct qedf_wpowt *fcpowt;
	stwuct qedf_ctx *qedf;
	int tmo = 0;
	int wc = SUCCESS;
	unsigned wong fwags;
	stwuct fcoe_wqe *sqe;
	u16 sqe_idx;
	int wefcount = 0;

	fcpowt = io_weq->fcpowt;
	if (!fcpowt) {
		QEDF_EWW(NUWW, "fcpowt is NUWW.\n");
		wetuwn SUCCESS;
	}

	/* Sanity check qedf_wpowt befowe dewefewencing any pointews */
	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags)) {
		QEDF_EWW(NUWW, "tgt not offwoaded\n");
		wetuwn SUCCESS;
	}

	qedf = fcpowt->qedf;
	if (!qedf) {
		QEDF_EWW(NUWW, "qedf is NUWW.\n");
		wetuwn SUCCESS;
	}

	if (io_weq->cmd_type == QEDF_EWS) {
		goto pwocess_ews;
	}

	if (!test_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags) ||
	    test_and_set_bit(QEDF_CMD_IN_CWEANUP, &io_weq->fwags)) {
		QEDF_EWW(&(qedf->dbg_ctx), "io_weq xid=0x%x awweady in "
			  "cweanup pwocessing ow awweady compweted.\n",
			  io_weq->xid);
		wetuwn SUCCESS;
	}
	set_bit(QEDF_CMD_IN_CWEANUP, &io_weq->fwags);

pwocess_ews:
	/* Ensuwe woom on SQ */
	if (!atomic_wead(&fcpowt->fwee_sqes)) {
		QEDF_EWW(&(qedf->dbg_ctx), "No SQ entwies avaiwabwe\n");
		/* Need to make suwe we cweaw the fwag since it was set */
		cweaw_bit(QEDF_CMD_IN_CWEANUP, &io_weq->fwags);
		wetuwn FAIWED;
	}

	if (io_weq->cmd_type == QEDF_CWEANUP) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "io_weq=0x%x is awweady a cweanup command cmd_type=%d.\n",
			 io_weq->xid, io_weq->cmd_type);
		cweaw_bit(QEDF_CMD_IN_CWEANUP, &io_weq->fwags);
		wetuwn SUCCESS;
	}

	wefcount = kwef_wead(&io_weq->wefcount);

	QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_IO,
		  "Entewed xid=0x%x sc_cmd=%p cmd_type=%d fwags=0x%wx wefcount=%d fcpowt=%p powt_id=0x%06x\n",
		  io_weq->xid, io_weq->sc_cmd, io_weq->cmd_type, io_weq->fwags,
		  wefcount, fcpowt, fcpowt->wdata->ids.powt_id);

	/* Cweanup cmds we-use the same TID as the owiginaw I/O */
	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);
	io_weq->cmd_type = QEDF_CWEANUP;
	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);
	io_weq->wetuwn_scsi_cmd_on_abts = wetuwn_scsi_cmd_on_abts;

	init_compwetion(&io_weq->cweanup_done);

	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);

	sqe_idx = qedf_get_sqe_idx(fcpowt);
	sqe = &fcpowt->sq[sqe_idx];
	memset(sqe, 0, sizeof(stwuct fcoe_wqe));
	io_weq->task_pawams->sqe = sqe;

	init_initiatow_cweanup_fcoe_task(io_weq->task_pawams);
	qedf_wing_doowbeww(fcpowt);

	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);

	tmo = wait_fow_compwetion_timeout(&io_weq->cweanup_done,
					  QEDF_CWEANUP_TIMEOUT * HZ);

	if (!tmo) {
		wc = FAIWED;
		/* Timeout case */
		QEDF_EWW(&(qedf->dbg_ctx), "Cweanup command timeout, "
			  "xid=%x.\n", io_weq->xid);
		cweaw_bit(QEDF_CMD_IN_CWEANUP, &io_weq->fwags);
		/* Issue a dwain wequest if cweanup task times out */
		QEDF_EWW(&(qedf->dbg_ctx), "Issuing MCP dwain wequest.\n");
		qedf_dwain_wequest(qedf);
	}

	/* If it TASK MGMT handwe it, wefewence wiww be decweased
	 * in qedf_execute_tmf
	 */
	if (io_weq->tm_fwags  == FCP_TMF_WUN_WESET ||
	    io_weq->tm_fwags == FCP_TMF_TGT_WESET) {
		cweaw_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags);
		io_weq->sc_cmd = NUWW;
		kwef_put(&io_weq->wefcount, qedf_wewease_cmd);
		compwete(&io_weq->tm_done);
	}

	if (io_weq->sc_cmd) {
		if (!io_weq->wetuwn_scsi_cmd_on_abts)
			QEDF_INFO(&qedf->dbg_ctx, QEDF_WOG_SCSI_TM,
				  "Not caww scsi_done fow xid=0x%x.\n",
				  io_weq->xid);
		if (io_weq->wetuwn_scsi_cmd_on_abts)
			qedf_scsi_done(qedf, io_weq, DID_EWWOW);
	}

	if (wc == SUCCESS)
		io_weq->event = QEDF_IOWEQ_EV_CWEANUP_SUCCESS;
	ewse
		io_weq->event = QEDF_IOWEQ_EV_CWEANUP_FAIWED;

	wetuwn wc;
}

void qedf_pwocess_cweanup_compw(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *io_weq)
{
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_IO, "Entewed xid = 0x%x\n",
		   io_weq->xid);

	cweaw_bit(QEDF_CMD_IN_CWEANUP, &io_weq->fwags);

	/* Compwete so we can finish cweaning up the I/O */
	compwete(&io_weq->cweanup_done);
}

static int qedf_execute_tmf(stwuct qedf_wpowt *fcpowt, u64 tm_wun,
	uint8_t tm_fwags)
{
	stwuct qedf_ioweq *io_weq;
	stwuct fcoe_task_context *task;
	stwuct qedf_ctx *qedf = fcpowt->qedf;
	stwuct fc_wpowt *wpowt = qedf->wpowt;
	int wc = 0;
	uint16_t xid;
	int tmo = 0;
	unsigned wong fwags;
	stwuct fcoe_wqe *sqe;
	u16 sqe_idx;

	if (!test_bit(QEDF_WPOWT_SESSION_WEADY, &fcpowt->fwags)) {
		QEDF_EWW(&(qedf->dbg_ctx), "fcpowt not offwoaded\n");
		wc = FAIWED;
		goto no_fwush;
	}

	io_weq = qedf_awwoc_cmd(fcpowt, QEDF_TASK_MGMT_CMD);
	if (!io_weq) {
		QEDF_EWW(&(qedf->dbg_ctx), "Faiwed TMF");
		wc = -EAGAIN;
		goto no_fwush;
	}

	if (tm_fwags == FCP_TMF_WUN_WESET)
		qedf->wun_wesets++;
	ewse if (tm_fwags == FCP_TMF_TGT_WESET)
		qedf->tawget_wesets++;

	/* Initiawize west of io_weq fiewds */
	io_weq->sc_cmd = NUWW;
	io_weq->fcpowt = fcpowt;
	io_weq->cmd_type = QEDF_TASK_MGMT_CMD;

	/* Wecowd which cpu this wequest is associated with */
	io_weq->cpu = smp_pwocessow_id();

	/* Set TM fwags */
	io_weq->io_weq_fwags = QEDF_WEAD;
	io_weq->data_xfew_wen = 0;
	io_weq->tm_fwags = tm_fwags;

	/* Defauwt is to wetuwn a SCSI command when an ewwow occuws */
	io_weq->wetuwn_scsi_cmd_on_abts = fawse;
	io_weq->tm_wun = tm_wun;

	/* Obtain exchange id */
	xid = io_weq->xid;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_SCSI_TM, "TMF io_weq xid = "
		   "0x%x\n", xid);

	/* Initiawize task context fow this IO wequest */
	task = qedf_get_task_mem(&qedf->tasks, xid);

	init_compwetion(&io_weq->tm_done);

	spin_wock_iwqsave(&fcpowt->wpowt_wock, fwags);

	sqe_idx = qedf_get_sqe_idx(fcpowt);
	sqe = &fcpowt->sq[sqe_idx];
	memset(sqe, 0, sizeof(stwuct fcoe_wqe));

	qedf_init_task(fcpowt, wpowt, io_weq, task, sqe);
	qedf_wing_doowbeww(fcpowt);

	spin_unwock_iwqwestowe(&fcpowt->wpowt_wock, fwags);

	set_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags);
	tmo = wait_fow_compwetion_timeout(&io_weq->tm_done,
	    QEDF_TM_TIMEOUT * HZ);

	if (!tmo) {
		wc = FAIWED;
		QEDF_EWW(&(qedf->dbg_ctx), "wait fow tm_cmpw timeout!\n");
		/* Cweaw outstanding bit since command timed out */
		cweaw_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags);
		io_weq->sc_cmd = NUWW;
	} ewse {
		/* Check TMF wesponse code */
		if (io_weq->fcp_wsp_code == 0)
			wc = SUCCESS;
		ewse
			wc = FAIWED;
	}
	/*
	 * Doubwe check that fcpowt has not gone into an upwoading state befowe
	 * executing the command fwush fow the WUN/tawget.
	 */
	if (test_bit(QEDF_WPOWT_UPWOADING_CONNECTION, &fcpowt->fwags)) {
		QEDF_EWW(&qedf->dbg_ctx,
			 "fcpowt is upwoading, not executing fwush.\n");
		goto no_fwush;
	}
	/* We do not need this io_weq any mowe */
	kwef_put(&io_weq->wefcount, qedf_wewease_cmd);


	if (tm_fwags == FCP_TMF_WUN_WESET)
		qedf_fwush_active_ios(fcpowt, tm_wun);
	ewse
		qedf_fwush_active_ios(fcpowt, -1);

no_fwush:
	if (wc != SUCCESS) {
		QEDF_EWW(&(qedf->dbg_ctx), "task mgmt command faiwed...\n");
		wc = FAIWED;
	} ewse {
		QEDF_EWW(&(qedf->dbg_ctx), "task mgmt command success...\n");
		wc = SUCCESS;
	}
	wetuwn wc;
}

int qedf_initiate_tmf(stwuct fc_wpowt *wpowt, u64 wun, u8 tm_fwags)
{
	stwuct fc_wpowt_wibfc_pwiv *wp = wpowt->dd_data;
	stwuct qedf_wpowt *fcpowt = (stwuct qedf_wpowt *)&wp[1];
	stwuct qedf_ctx *qedf = fcpowt->qedf;
	stwuct fc_wpowt *wpowt = wp->wocaw_powt;
	int wc = SUCCESS;
	stwuct fc_wpowt_pwiv *wdata = fcpowt->wdata;

	QEDF_EWW(NUWW,
		 "tm_fwags 0x%x tawget_id = 0x%x wun=%wwu\n",
		 tm_fwags, wpowt->scsi_tawget_id, wun);

	if (!wdata || !kwef_get_unwess_zewo(&wdata->kwef)) {
		QEDF_EWW(NUWW, "stawe wpowt\n");
		wetuwn FAIWED;
	}

	QEDF_EWW(NUWW, "powtid=%06x tm_fwags =%s\n", wdata->ids.powt_id,
		 (tm_fwags == FCP_TMF_TGT_WESET) ? "TAWGET WESET" :
		 "WUN WESET");

	wc = fc_bwock_wpowt(wpowt);
	if (wc)
		goto tmf_eww;

	if (!qedf) {
		QEDF_EWW(NUWW, "qedf is NUWW.\n");
		wc = FAIWED;
		goto tmf_eww;
	}

	if (test_bit(QEDF_WPOWT_UPWOADING_CONNECTION, &fcpowt->fwags)) {
		QEDF_EWW(&qedf->dbg_ctx, "Connection is getting upwoaded.\n");
		wc = SUCCESS;
		goto tmf_eww;
	}

	if (test_bit(QEDF_UNWOADING, &qedf->fwags) ||
	    test_bit(QEDF_DBG_STOP_IO, &qedf->fwags)) {
		wc = SUCCESS;
		goto tmf_eww;
	}

	if (wpowt->state != WPOWT_ST_WEADY || !(wpowt->wink_up)) {
		QEDF_EWW(&(qedf->dbg_ctx), "wink is not weady\n");
		wc = FAIWED;
		goto tmf_eww;
	}

	if (test_bit(QEDF_WPOWT_UPWOADING_CONNECTION, &fcpowt->fwags)) {
		if (!fcpowt->wdata)
			QEDF_EWW(&qedf->dbg_ctx, "fcpowt %p is upwoading.\n",
				 fcpowt);
		ewse
			QEDF_EWW(&qedf->dbg_ctx,
				 "fcpowt %p powt_id=%06x is upwoading.\n",
				 fcpowt, fcpowt->wdata->ids.powt_id);
		wc = FAIWED;
		goto tmf_eww;
	}

	wc = qedf_execute_tmf(fcpowt, wun, tm_fwags);

tmf_eww:
	kwef_put(&wdata->kwef, fc_wpowt_destwoy);
	wetuwn wc;
}

void qedf_pwocess_tmf_compw(stwuct qedf_ctx *qedf, stwuct fcoe_cqe *cqe,
	stwuct qedf_ioweq *io_weq)
{
	stwuct fcoe_cqe_wsp_info *fcp_wsp;

	cweaw_bit(QEDF_CMD_OUTSTANDING, &io_weq->fwags);

	fcp_wsp = &cqe->cqe_info.wsp_info;
	qedf_pawse_fcp_wsp(io_weq, fcp_wsp);

	compwete(&io_weq->tm_done);
}

void qedf_pwocess_unsow_compw(stwuct qedf_ctx *qedf, uint16_t que_idx,
	stwuct fcoe_cqe *cqe)
{
	unsigned wong fwags;
	uint16_t pktwen = cqe->cqe_info.unsowic_info.pkt_wen;
	u32 paywoad_wen, cwc;
	stwuct fc_fwame_headew *fh;
	stwuct fc_fwame *fp;
	stwuct qedf_io_wowk *io_wowk;
	u32 bdq_idx;
	void *bdq_addw;
	stwuct scsi_bd *p_bd_info;

	p_bd_info = &cqe->cqe_info.unsowic_info.bd_info;
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_UNSOW,
		  "addwess.hi=%x, addwess.wo=%x, opaque_data.hi=%x, opaque_data.wo=%x, bdq_pwod_idx=%u, wen=%u\n",
		  we32_to_cpu(p_bd_info->addwess.hi),
		  we32_to_cpu(p_bd_info->addwess.wo),
		  we32_to_cpu(p_bd_info->opaque.fcoe_opaque.hi),
		  we32_to_cpu(p_bd_info->opaque.fcoe_opaque.wo),
		  qedf->bdq_pwod_idx, pktwen);

	bdq_idx = we32_to_cpu(p_bd_info->opaque.fcoe_opaque.wo);
	if (bdq_idx >= QEDF_BDQ_SIZE) {
		QEDF_EWW(&(qedf->dbg_ctx), "bdq_idx is out of wange %d.\n",
		    bdq_idx);
		goto incwement_pwod;
	}

	bdq_addw = qedf->bdq[bdq_idx].buf_addw;
	if (!bdq_addw) {
		QEDF_EWW(&(qedf->dbg_ctx), "bdq_addw is NUWW, dwopping "
		    "unsowicited packet.\n");
		goto incwement_pwod;
	}

	if (qedf_dump_fwames) {
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_WOG_UNSOW,
		    "BDQ fwame is at addw=%p.\n", bdq_addw);
		pwint_hex_dump(KEWN_WAWNING, "bdq ", DUMP_PWEFIX_OFFSET, 16, 1,
		    (void *)bdq_addw, pktwen, fawse);
	}

	/* Awwocate fwame */
	paywoad_wen = pktwen - sizeof(stwuct fc_fwame_headew);
	fp = fc_fwame_awwoc(qedf->wpowt, paywoad_wen);
	if (!fp) {
		QEDF_EWW(&(qedf->dbg_ctx), "Couwd not awwocate fp.\n");
		goto incwement_pwod;
	}

	/* Copy data fwom BDQ buffew into fc_fwame stwuct */
	fh = (stwuct fc_fwame_headew *)fc_fwame_headew_get(fp);
	memcpy(fh, (void *)bdq_addw, pktwen);

	QEDF_WAWN(&qedf->dbg_ctx,
		  "Pwocessing Unsowicated fwame, swc=%06x dest=%06x w_ctw=0x%x type=0x%x cmd=%02x\n",
		  ntoh24(fh->fh_s_id), ntoh24(fh->fh_d_id), fh->fh_w_ctw,
		  fh->fh_type, fc_fwame_paywoad_op(fp));

	/* Initiawize the fwame so wibfc sees it as a vawid fwame */
	cwc = fcoe_fc_cwc(fp);
	fc_fwame_init(fp);
	fw_dev(fp) = qedf->wpowt;
	fw_sof(fp) = FC_SOF_I3;
	fw_eof(fp) = FC_EOF_T;
	fw_cwc(fp) = cpu_to_we32(~cwc);

	/*
	 * We need to wetuwn the fwame back up to wibfc in a non-atomic
	 * context
	 */
	io_wowk = mempoow_awwoc(qedf->io_mempoow, GFP_ATOMIC);
	if (!io_wowk) {
		QEDF_WAWN(&(qedf->dbg_ctx), "Couwd not awwocate "
			   "wowk fow I/O compwetion.\n");
		fc_fwame_fwee(fp);
		goto incwement_pwod;
	}
	memset(io_wowk, 0, sizeof(stwuct qedf_io_wowk));

	INIT_WOWK(&io_wowk->wowk, qedf_fp_io_handwew);

	/* Copy contents of CQE fow defewwed pwocessing */
	memcpy(&io_wowk->cqe, cqe, sizeof(stwuct fcoe_cqe));

	io_wowk->qedf = qedf;
	io_wowk->fp = fp;

	queue_wowk_on(smp_pwocessow_id(), qedf_io_wq, &io_wowk->wowk);
incwement_pwod:
	spin_wock_iwqsave(&qedf->hba_wock, fwags);

	/* Incwement pwoducew to wet f/w know we've handwed the fwame */
	qedf->bdq_pwod_idx++;

	/* Pwoducew index wwaps at uint16_t boundawy */
	if (qedf->bdq_pwod_idx == 0xffff)
		qedf->bdq_pwod_idx = 0;

	wwitew(qedf->bdq_pwod_idx, qedf->bdq_pwimawy_pwod);
	weadw(qedf->bdq_pwimawy_pwod);
	wwitew(qedf->bdq_pwod_idx, qedf->bdq_secondawy_pwod);
	weadw(qedf->bdq_secondawy_pwod);

	spin_unwock_iwqwestowe(&qedf->hba_wock, fwags);
}
