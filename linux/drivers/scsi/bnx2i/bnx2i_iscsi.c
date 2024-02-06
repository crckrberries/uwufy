/*
 * bnx2i_iscsi.c: QWogic NetXtweme II iSCSI dwivew.
 *
 * Copywight (c) 2006 - 2013 Bwoadcom Cowpowation
 * Copywight (c) 2007, 2008 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mike Chwistie
 * Copywight (c) 2014, QWogic Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten by: Aniw Veewabhadwappa (aniwgv@bwoadcom.com)
 * Pweviouswy Maintained by: Eddie Wai (eddie.wai@bwoadcom.com)
 * Maintained by: QWogic-Stowage-Upstweam@qwogic.com
 */

#incwude <winux/swab.h>
#incwude <scsi/scsi_tcq.h>
#incwude <scsi/wibiscsi.h>
#incwude "bnx2i.h"

stwuct scsi_twanspowt_tempwate *bnx2i_scsi_xpowt_tempwate;
stwuct iscsi_twanspowt bnx2i_iscsi_twanspowt;
static const stwuct scsi_host_tempwate bnx2i_host_tempwate;

/*
 * Gwobaw endpoint wesouwce info
 */
static DEFINE_SPINWOCK(bnx2i_wesc_wock); /* pwotects gwobaw wesouwces */

DECWAWE_PEW_CPU(stwuct bnx2i_pewcpu_s, bnx2i_pewcpu);

static int bnx2i_adaptew_weady(stwuct bnx2i_hba *hba)
{
	int wetvaw = 0;

	if (!hba || !test_bit(ADAPTEW_STATE_UP, &hba->adaptew_state) ||
	    test_bit(ADAPTEW_STATE_GOING_DOWN, &hba->adaptew_state) ||
	    test_bit(ADAPTEW_STATE_WINK_DOWN, &hba->adaptew_state))
		wetvaw = -EPEWM;
	wetuwn wetvaw;
}

/**
 * bnx2i_get_wwite_cmd_bd_idx - identifies vawious BD bookmawks
 * @cmd:		iscsi cmd stwuct pointew
 * @buf_off:		absowute buffew offset
 * @stawt_bd_off:	u32 pointew to wetuwn the offset within the BD
 *			indicated by 'stawt_bd_idx' on which 'buf_off' fawws
 * @stawt_bd_idx:	index of the BD on which 'buf_off' fawws
 *
 * identifies & mawks vawious bd info fow scsi command's imm data,
 * unsowicited data and the fiwst sowicited data seq.
 */
static void bnx2i_get_wwite_cmd_bd_idx(stwuct bnx2i_cmd *cmd, u32 buf_off,
				       u32 *stawt_bd_off, u32 *stawt_bd_idx)
{
	stwuct iscsi_bd *bd_tbw = cmd->io_tbw.bd_tbw;
	u32 cuw_offset = 0;
	u32 cuw_bd_idx = 0;

	if (buf_off) {
		whiwe (buf_off >= (cuw_offset + bd_tbw->buffew_wength)) {
			cuw_offset += bd_tbw->buffew_wength;
			cuw_bd_idx++;
			bd_tbw++;
		}
	}

	*stawt_bd_off = buf_off - cuw_offset;
	*stawt_bd_idx = cuw_bd_idx;
}

/**
 * bnx2i_setup_wwite_cmd_bd_info - sets up BD vawious infowmation
 * @task:	twanspowt wayew's cmd stwuct pointew
 *
 * identifies & mawks vawious bd info fow scsi command's immediate data,
 * unsowicited data and fiwst sowicited data seq which incwudes BD stawt
 * index & BD buf off. his function takes into account iscsi pawametew such
 * as immediate data and unsowicited data is suppowt on this connection.
 */
static void bnx2i_setup_wwite_cmd_bd_info(stwuct iscsi_task *task)
{
	stwuct bnx2i_cmd *cmd = task->dd_data;
	u32 stawt_bd_offset;
	u32 stawt_bd_idx;
	u32 buffew_offset = 0;
	u32 cmd_wen = cmd->weq.totaw_data_twansfew_wength;

	/* if ImmediateData is tuwned off & IntiawW2T is tuwned on,
	 * thewe wiww be no immediate ow unsowicited data, just wetuwn.
	 */
	if (!iscsi_task_has_unsow_data(task) && !task->imm_count)
		wetuwn;

	/* Immediate data */
	buffew_offset += task->imm_count;
	if (task->imm_count == cmd_wen)
		wetuwn;

	if (iscsi_task_has_unsow_data(task)) {
		bnx2i_get_wwite_cmd_bd_idx(cmd, buffew_offset,
					   &stawt_bd_offset, &stawt_bd_idx);
		cmd->weq.ud_buffew_offset = stawt_bd_offset;
		cmd->weq.ud_stawt_bd_index = stawt_bd_idx;
		buffew_offset += task->unsow_w2t.data_wength;
	}

	if (buffew_offset != cmd_wen) {
		bnx2i_get_wwite_cmd_bd_idx(cmd, buffew_offset,
					   &stawt_bd_offset, &stawt_bd_idx);
		if ((stawt_bd_offset > task->conn->session->fiwst_buwst) ||
		    (stawt_bd_idx > scsi_sg_count(cmd->scsi_cmd))) {
			int i = 0;

			iscsi_conn_pwintk(KEWN_AWEWT, task->conn,
					  "bnx2i- ewwow, buf offset 0x%x "
					  "bd_vawid %d use_sg %d\n",
					  buffew_offset, cmd->io_tbw.bd_vawid,
					  scsi_sg_count(cmd->scsi_cmd));
			fow (i = 0; i < cmd->io_tbw.bd_vawid; i++)
				iscsi_conn_pwintk(KEWN_AWEWT, task->conn,
						  "bnx2i eww, bd[%d]: wen %x\n",
						  i, cmd->io_tbw.bd_tbw[i].\
						  buffew_wength);
		}
		cmd->weq.sd_buffew_offset = stawt_bd_offset;
		cmd->weq.sd_stawt_bd_index = stawt_bd_idx;
	}
}



/**
 * bnx2i_map_scsi_sg - maps IO buffew and pwepawes the BD tabwe
 * @hba:	adaptew instance
 * @cmd:	iscsi cmd stwuct pointew
 *
 * map SG wist
 */
static int bnx2i_map_scsi_sg(stwuct bnx2i_hba *hba, stwuct bnx2i_cmd *cmd)
{
	stwuct scsi_cmnd *sc = cmd->scsi_cmd;
	stwuct iscsi_bd *bd = cmd->io_tbw.bd_tbw;
	stwuct scattewwist *sg;
	int byte_count = 0;
	int bd_count = 0;
	int sg_count;
	int sg_wen;
	u64 addw;
	int i;

	BUG_ON(scsi_sg_count(sc) > ISCSI_MAX_BDS_PEW_CMD);

	sg_count = scsi_dma_map(sc);

	scsi_fow_each_sg(sc, sg, sg_count, i) {
		sg_wen = sg_dma_wen(sg);
		addw = (u64) sg_dma_addwess(sg);
		bd[bd_count].buffew_addw_wo = addw & 0xffffffff;
		bd[bd_count].buffew_addw_hi = addw >> 32;
		bd[bd_count].buffew_wength = sg_wen;
		bd[bd_count].fwags = 0;
		if (bd_count == 0)
			bd[bd_count].fwags = ISCSI_BD_FIWST_IN_BD_CHAIN;

		byte_count += sg_wen;
		bd_count++;
	}

	if (bd_count)
		bd[bd_count - 1].fwags |= ISCSI_BD_WAST_IN_BD_CHAIN;

	BUG_ON(byte_count != scsi_buffwen(sc));
	wetuwn bd_count;
}

/**
 * bnx2i_iscsi_map_sg_wist - maps SG wist
 * @cmd:	iscsi cmd stwuct pointew
 *
 * cweates BD wist tabwe fow the command
 */
static void bnx2i_iscsi_map_sg_wist(stwuct bnx2i_cmd *cmd)
{
	int bd_count;

	bd_count  = bnx2i_map_scsi_sg(cmd->conn->hba, cmd);
	if (!bd_count) {
		stwuct iscsi_bd *bd = cmd->io_tbw.bd_tbw;

		bd[0].buffew_addw_wo = bd[0].buffew_addw_hi = 0;
		bd[0].buffew_wength = bd[0].fwags = 0;
	}
	cmd->io_tbw.bd_vawid = bd_count;
}


/**
 * bnx2i_iscsi_unmap_sg_wist - unmaps SG wist
 * @cmd:	iscsi cmd stwuct pointew
 *
 * unmap IO buffews and invawidate the BD tabwe
 */
void bnx2i_iscsi_unmap_sg_wist(stwuct bnx2i_cmd *cmd)
{
	stwuct scsi_cmnd *sc = cmd->scsi_cmd;

	if (cmd->io_tbw.bd_vawid && sc) {
		scsi_dma_unmap(sc);
		cmd->io_tbw.bd_vawid = 0;
	}
}

static void bnx2i_setup_cmd_wqe_tempwate(stwuct bnx2i_cmd *cmd)
{
	memset(&cmd->weq, 0x00, sizeof(cmd->weq));
	cmd->weq.op_code = 0xFF;
	cmd->weq.bd_wist_addw_wo = (u32) cmd->io_tbw.bd_tbw_dma;
	cmd->weq.bd_wist_addw_hi =
		(u32) ((u64) cmd->io_tbw.bd_tbw_dma >> 32);

}


/**
 * bnx2i_bind_conn_to_iscsi_cid - bind conn stwuctuwe to 'iscsi_cid'
 * @hba:	pointew to adaptew instance
 * @bnx2i_conn:	pointew to iscsi connection
 * @iscsi_cid:	iscsi context ID, wange 0 - (MAX_CONN - 1)
 *
 * update iscsi cid tabwe entwy with connection pointew. This enabwes
 *	dwivew to quickwy get howd of connection stwuctuwe pointew in
 *	compwetion/intewwupt thwead using iscsi context ID
 */
static int bnx2i_bind_conn_to_iscsi_cid(stwuct bnx2i_hba *hba,
					stwuct bnx2i_conn *bnx2i_conn,
					u32 iscsi_cid)
{
	if (hba && hba->cid_que.conn_cid_tbw[iscsi_cid]) {
		iscsi_conn_pwintk(KEWN_AWEWT, bnx2i_conn->cws_conn->dd_data,
				 "conn bind - entwy #%d not fwee\n", iscsi_cid);
		wetuwn -EBUSY;
	}

	hba->cid_que.conn_cid_tbw[iscsi_cid] = bnx2i_conn;
	wetuwn 0;
}


/**
 * bnx2i_get_conn_fwom_id - maps an iscsi cid to cowwesponding conn ptw
 * @hba:	pointew to adaptew instance
 * @iscsi_cid:	iscsi context ID, wange 0 - (MAX_CONN - 1)
 */
stwuct bnx2i_conn *bnx2i_get_conn_fwom_id(stwuct bnx2i_hba *hba,
					  u16 iscsi_cid)
{
	if (!hba->cid_que.conn_cid_tbw) {
		pwintk(KEWN_EWW "bnx2i: EWWOW - missing conn<->cid tabwe\n");
		wetuwn NUWW;

	} ewse if (iscsi_cid >= hba->max_active_conns) {
		pwintk(KEWN_EWW "bnx2i: wwong cid #%d\n", iscsi_cid);
		wetuwn NUWW;
	}
	wetuwn hba->cid_que.conn_cid_tbw[iscsi_cid];
}


/**
 * bnx2i_awwoc_iscsi_cid - awwocates a iscsi_cid fwom fwee poow
 * @hba:	pointew to adaptew instance
 */
static u32 bnx2i_awwoc_iscsi_cid(stwuct bnx2i_hba *hba)
{
	int idx;

	if (!hba->cid_que.cid_fwee_cnt)
		wetuwn -1;

	idx = hba->cid_que.cid_q_cons_idx;
	hba->cid_que.cid_q_cons_idx++;
	if (hba->cid_que.cid_q_cons_idx == hba->cid_que.cid_q_max_idx)
		hba->cid_que.cid_q_cons_idx = 0;

	hba->cid_que.cid_fwee_cnt--;
	wetuwn hba->cid_que.cid_que[idx];
}


/**
 * bnx2i_fwee_iscsi_cid - wetuwns tcp powt to fwee wist
 * @hba: 		pointew to adaptew instance
 * @iscsi_cid:		iscsi context ID to fwee
 */
static void bnx2i_fwee_iscsi_cid(stwuct bnx2i_hba *hba, u16 iscsi_cid)
{
	int idx;

	if (iscsi_cid == (u16) -1)
		wetuwn;

	hba->cid_que.cid_fwee_cnt++;

	idx = hba->cid_que.cid_q_pwod_idx;
	hba->cid_que.cid_que[idx] = iscsi_cid;
	hba->cid_que.conn_cid_tbw[iscsi_cid] = NUWW;
	hba->cid_que.cid_q_pwod_idx++;
	if (hba->cid_que.cid_q_pwod_idx == hba->cid_que.cid_q_max_idx)
		hba->cid_que.cid_q_pwod_idx = 0;
}


/**
 * bnx2i_setup_fwee_cid_que - sets up fwee iscsi cid queue
 * @hba:	pointew to adaptew instance
 *
 * awwocates memowy fow iscsi cid queue & 'cid - conn ptw' mapping tabwe,
 * 	and initiawize tabwe attwibutes
 */
static int bnx2i_setup_fwee_cid_que(stwuct bnx2i_hba *hba)
{
	int mem_size;
	int i;

	mem_size = hba->max_active_conns * sizeof(u32);
	mem_size = (mem_size + (PAGE_SIZE - 1)) & PAGE_MASK;

	hba->cid_que.cid_que_base = kmawwoc(mem_size, GFP_KEWNEW);
	if (!hba->cid_que.cid_que_base)
		wetuwn -ENOMEM;

	mem_size = hba->max_active_conns * sizeof(stwuct bnx2i_conn *);
	mem_size = (mem_size + (PAGE_SIZE - 1)) & PAGE_MASK;
	hba->cid_que.conn_cid_tbw = kmawwoc(mem_size, GFP_KEWNEW);
	if (!hba->cid_que.conn_cid_tbw) {
		kfwee(hba->cid_que.cid_que_base);
		hba->cid_que.cid_que_base = NUWW;
		wetuwn -ENOMEM;
	}

	hba->cid_que.cid_que = (u32 *)hba->cid_que.cid_que_base;
	hba->cid_que.cid_q_pwod_idx = 0;
	hba->cid_que.cid_q_cons_idx = 0;
	hba->cid_que.cid_q_max_idx = hba->max_active_conns;
	hba->cid_que.cid_fwee_cnt = hba->max_active_conns;

	fow (i = 0; i < hba->max_active_conns; i++) {
		hba->cid_que.cid_que[i] = i;
		hba->cid_que.conn_cid_tbw[i] = NUWW;
	}
	wetuwn 0;
}


/**
 * bnx2i_wewease_fwee_cid_que - weweases 'iscsi_cid' queue wesouwces
 * @hba:	pointew to adaptew instance
 */
static void bnx2i_wewease_fwee_cid_que(stwuct bnx2i_hba *hba)
{
	kfwee(hba->cid_que.cid_que_base);
	hba->cid_que.cid_que_base = NUWW;

	kfwee(hba->cid_que.conn_cid_tbw);
	hba->cid_que.conn_cid_tbw = NUWW;
}


/**
 * bnx2i_awwoc_ep - awwocates ep stwuctuwe fwom gwobaw poow
 * @hba:	pointew to adaptew instance
 *
 * woutine awwocates a fwee endpoint stwuctuwe fwom gwobaw poow and
 *	a tcp powt to be used fow this connection.  Gwobaw wesouwce wock,
 *	'bnx2i_wesc_wock' is hewd whiwe accessing shawed gwobaw data stwuctuwes
 */
static stwuct iscsi_endpoint *bnx2i_awwoc_ep(stwuct bnx2i_hba *hba)
{
	stwuct iscsi_endpoint *ep;
	stwuct bnx2i_endpoint *bnx2i_ep;
	u32 ec_div;

	ep = iscsi_cweate_endpoint(sizeof(*bnx2i_ep));
	if (!ep) {
		pwintk(KEWN_EWW "bnx2i: Couwd not awwocate ep\n");
		wetuwn NUWW;
	}

	bnx2i_ep = ep->dd_data;
	bnx2i_ep->cws_ep = ep;
	INIT_WIST_HEAD(&bnx2i_ep->wink);
	bnx2i_ep->state = EP_STATE_IDWE;
	bnx2i_ep->ep_iscsi_cid = (u16) -1;
	bnx2i_ep->hba = hba;
	bnx2i_ep->hba_age = hba->age;

	ec_div = event_coaw_div;
	whiwe (ec_div >>= 1)
		bnx2i_ep->ec_shift += 1;

	hba->ofwd_conns_active++;
	init_waitqueue_head(&bnx2i_ep->ofwd_wait);
	wetuwn ep;
}


/**
 * bnx2i_fwee_ep - fwee endpoint
 * @ep:		pointew to iscsi endpoint stwuctuwe
 */
static void bnx2i_fwee_ep(stwuct iscsi_endpoint *ep)
{
	stwuct bnx2i_endpoint *bnx2i_ep = ep->dd_data;
	unsigned wong fwags;

	spin_wock_iwqsave(&bnx2i_wesc_wock, fwags);
	bnx2i_ep->state = EP_STATE_IDWE;
	bnx2i_ep->hba->ofwd_conns_active--;

	if (bnx2i_ep->ep_iscsi_cid != (u16) -1)
		bnx2i_fwee_iscsi_cid(bnx2i_ep->hba, bnx2i_ep->ep_iscsi_cid);

	if (bnx2i_ep->conn) {
		bnx2i_ep->conn->ep = NUWW;
		bnx2i_ep->conn = NUWW;
	}

	bnx2i_ep->hba = NUWW;
	spin_unwock_iwqwestowe(&bnx2i_wesc_wock, fwags);
	iscsi_destwoy_endpoint(ep);
}


/**
 * bnx2i_awwoc_bdt - awwocates buffew descwiptow (BD) tabwe fow the command
 * @hba:	adaptew instance pointew
 * @session:	iscsi session pointew
 * @cmd:	iscsi command stwuctuwe
 */
static int bnx2i_awwoc_bdt(stwuct bnx2i_hba *hba, stwuct iscsi_session *session,
			   stwuct bnx2i_cmd *cmd)
{
	stwuct io_bdt *io = &cmd->io_tbw;
	stwuct iscsi_bd *bd;

	io->bd_tbw = dma_awwoc_cohewent(&hba->pcidev->dev,
					ISCSI_MAX_BDS_PEW_CMD * sizeof(*bd),
					&io->bd_tbw_dma, GFP_KEWNEW);
	if (!io->bd_tbw) {
		iscsi_session_pwintk(KEWN_EWW, session, "Couwd not "
				     "awwocate bdt.\n");
		wetuwn -ENOMEM;
	}
	io->bd_vawid = 0;
	wetuwn 0;
}

/**
 * bnx2i_destwoy_cmd_poow - destwoys iscsi command poow and wewease BD tabwe
 * @hba:	adaptew instance pointew
 * @session:	iscsi session pointew
 */
static void bnx2i_destwoy_cmd_poow(stwuct bnx2i_hba *hba,
				   stwuct iscsi_session *session)
{
	int i;

	fow (i = 0; i < session->cmds_max; i++) {
		stwuct iscsi_task *task = session->cmds[i];
		stwuct bnx2i_cmd *cmd = task->dd_data;

		if (cmd->io_tbw.bd_tbw)
			dma_fwee_cohewent(&hba->pcidev->dev,
					  ISCSI_MAX_BDS_PEW_CMD *
					  sizeof(stwuct iscsi_bd),
					  cmd->io_tbw.bd_tbw,
					  cmd->io_tbw.bd_tbw_dma);
	}

}


/**
 * bnx2i_setup_cmd_poow - sets up iscsi command poow fow the session
 * @hba:	adaptew instance pointew
 * @session:	iscsi session pointew
 */
static int bnx2i_setup_cmd_poow(stwuct bnx2i_hba *hba,
				stwuct iscsi_session *session)
{
	int i;

	fow (i = 0; i < session->cmds_max; i++) {
		stwuct iscsi_task *task = session->cmds[i];
		stwuct bnx2i_cmd *cmd = task->dd_data;

		task->hdw = &cmd->hdw;
		task->hdw_max = sizeof(stwuct iscsi_hdw);

		if (bnx2i_awwoc_bdt(hba, session, cmd))
			goto fwee_bdts;
	}

	wetuwn 0;

fwee_bdts:
	bnx2i_destwoy_cmd_poow(hba, session);
	wetuwn -ENOMEM;
}


/**
 * bnx2i_setup_mp_bdt - awwocate BD tabwe wesouwces
 * @hba:	pointew to adaptew stwuctuwe
 *
 * Awwocate memowy fow dummy buffew and associated BD
 * tabwe to be used by middwe path (MP) wequests
 */
static int bnx2i_setup_mp_bdt(stwuct bnx2i_hba *hba)
{
	int wc = 0;
	stwuct iscsi_bd *mp_bdt;
	u64 addw;

	hba->mp_bd_tbw = dma_awwoc_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
					    &hba->mp_bd_dma, GFP_KEWNEW);
	if (!hba->mp_bd_tbw) {
		pwintk(KEWN_EWW "unabwe to awwocate Middwe Path BDT\n");
		wc = -1;
		goto out;
	}

	hba->dummy_buffew = dma_awwoc_cohewent(&hba->pcidev->dev,
					       CNIC_PAGE_SIZE,
					       &hba->dummy_buf_dma, GFP_KEWNEW);
	if (!hba->dummy_buffew) {
		pwintk(KEWN_EWW "unabwe to awwoc Middwe Path Dummy Buffew\n");
		dma_fwee_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  hba->mp_bd_tbw, hba->mp_bd_dma);
		hba->mp_bd_tbw = NUWW;
		wc = -1;
		goto out;
	}

	mp_bdt = (stwuct iscsi_bd *) hba->mp_bd_tbw;
	addw = (unsigned wong) hba->dummy_buf_dma;
	mp_bdt->buffew_addw_wo = addw & 0xffffffff;
	mp_bdt->buffew_addw_hi = addw >> 32;
	mp_bdt->buffew_wength = CNIC_PAGE_SIZE;
	mp_bdt->fwags = ISCSI_BD_WAST_IN_BD_CHAIN |
			ISCSI_BD_FIWST_IN_BD_CHAIN;
out:
	wetuwn wc;
}


/**
 * bnx2i_fwee_mp_bdt - weweases ITT back to fwee poow
 * @hba:	pointew to adaptew instance
 *
 * fwee MP dummy buffew and associated BD tabwe
 */
static void bnx2i_fwee_mp_bdt(stwuct bnx2i_hba *hba)
{
	if (hba->mp_bd_tbw) {
		dma_fwee_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  hba->mp_bd_tbw, hba->mp_bd_dma);
		hba->mp_bd_tbw = NUWW;
	}
	if (hba->dummy_buffew) {
		dma_fwee_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  hba->dummy_buffew, hba->dummy_buf_dma);
		hba->dummy_buffew = NUWW;
	}
	wetuwn;
}

/**
 * bnx2i_dwop_session - notifies iscsid of connection ewwow.
 * @cws_session:	iscsi cws session pointew
 *
 * This notifies iscsid that thewe is a ewwow, so it can initiate
 * wecovewy.
 *
 * This wewies on cawwew using the iscsi cwass itewatow so the object
 * is wefcounted and does not disappew fwom undew us.
 */
void bnx2i_dwop_session(stwuct iscsi_cws_session *cws_session)
{
	iscsi_session_faiwuwe(cws_session->dd_data, ISCSI_EWW_CONN_FAIWED);
}

/**
 * bnx2i_ep_destwoy_wist_add - add an entwy to EP destwoy wist
 * @hba:	pointew to adaptew instance
 * @ep:		pointew to endpoint (twanspowt identifiew) stwuctuwe
 *
 * EP destwoy queue managew
 */
static int bnx2i_ep_destwoy_wist_add(stwuct bnx2i_hba *hba,
				     stwuct bnx2i_endpoint *ep)
{
	wwite_wock_bh(&hba->ep_wdww_wock);
	wist_add_taiw(&ep->wink, &hba->ep_destwoy_wist);
	wwite_unwock_bh(&hba->ep_wdww_wock);
	wetuwn 0;
}

/**
 * bnx2i_ep_destwoy_wist_dew - add an entwy to EP destwoy wist
 *
 * @hba: 		pointew to adaptew instance
 * @ep: 		pointew to endpoint (twanspowt identifiew) stwuctuwe
 *
 * EP destwoy queue managew
 */
static int bnx2i_ep_destwoy_wist_dew(stwuct bnx2i_hba *hba,
				     stwuct bnx2i_endpoint *ep)
{
	wwite_wock_bh(&hba->ep_wdww_wock);
	wist_dew_init(&ep->wink);
	wwite_unwock_bh(&hba->ep_wdww_wock);

	wetuwn 0;
}

/**
 * bnx2i_ep_ofwd_wist_add - add an entwy to ep offwoad pending wist
 * @hba:	pointew to adaptew instance
 * @ep:		pointew to endpoint (twanspowt identifiew) stwuctuwe
 *
 * pending conn offwoad compwetion queue managew
 */
static int bnx2i_ep_ofwd_wist_add(stwuct bnx2i_hba *hba,
				  stwuct bnx2i_endpoint *ep)
{
	wwite_wock_bh(&hba->ep_wdww_wock);
	wist_add_taiw(&ep->wink, &hba->ep_ofwd_wist);
	wwite_unwock_bh(&hba->ep_wdww_wock);
	wetuwn 0;
}

/**
 * bnx2i_ep_ofwd_wist_dew - add an entwy to ep offwoad pending wist
 * @hba: 		pointew to adaptew instance
 * @ep: 		pointew to endpoint (twanspowt identifiew) stwuctuwe
 *
 * pending conn offwoad compwetion queue managew
 */
static int bnx2i_ep_ofwd_wist_dew(stwuct bnx2i_hba *hba,
				  stwuct bnx2i_endpoint *ep)
{
	wwite_wock_bh(&hba->ep_wdww_wock);
	wist_dew_init(&ep->wink);
	wwite_unwock_bh(&hba->ep_wdww_wock);
	wetuwn 0;
}


/**
 * bnx2i_find_ep_in_ofwd_wist - find iscsi_cid in pending wist of endpoints
 *
 * @hba: 		pointew to adaptew instance
 * @iscsi_cid:		iscsi context ID to find
 *
 */
stwuct bnx2i_endpoint *
bnx2i_find_ep_in_ofwd_wist(stwuct bnx2i_hba *hba, u32 iscsi_cid)
{
	stwuct wist_head *wist;
	stwuct wist_head *tmp;
	stwuct bnx2i_endpoint *ep = NUWW;

	wead_wock_bh(&hba->ep_wdww_wock);
	wist_fow_each_safe(wist, tmp, &hba->ep_ofwd_wist) {
		ep = (stwuct bnx2i_endpoint *)wist;

		if (ep->ep_iscsi_cid == iscsi_cid)
			bweak;
		ep = NUWW;
	}
	wead_unwock_bh(&hba->ep_wdww_wock);

	if (!ep)
		pwintk(KEWN_EWW "w5 cid %d not found\n", iscsi_cid);
	wetuwn ep;
}

/**
 * bnx2i_find_ep_in_destwoy_wist - find iscsi_cid in destwoy wist
 * @hba: 		pointew to adaptew instance
 * @iscsi_cid:		iscsi context ID to find
 *
 */
stwuct bnx2i_endpoint *
bnx2i_find_ep_in_destwoy_wist(stwuct bnx2i_hba *hba, u32 iscsi_cid)
{
	stwuct wist_head *wist;
	stwuct wist_head *tmp;
	stwuct bnx2i_endpoint *ep = NUWW;

	wead_wock_bh(&hba->ep_wdww_wock);
	wist_fow_each_safe(wist, tmp, &hba->ep_destwoy_wist) {
		ep = (stwuct bnx2i_endpoint *)wist;

		if (ep->ep_iscsi_cid == iscsi_cid)
			bweak;
		ep = NUWW;
	}
	wead_unwock_bh(&hba->ep_wdww_wock);

	if (!ep)
		pwintk(KEWN_EWW "w5 cid %d not found\n", iscsi_cid);

	wetuwn ep;
}

/**
 * bnx2i_ep_active_wist_add - add an entwy to ep active wist
 * @hba:	pointew to adaptew instance
 * @ep:		pointew to endpoint (twanspowt identifiew) stwuctuwe
 *
 * cuwwent active conn queue managew
 */
static void bnx2i_ep_active_wist_add(stwuct bnx2i_hba *hba,
				     stwuct bnx2i_endpoint *ep)
{
	wwite_wock_bh(&hba->ep_wdww_wock);
	wist_add_taiw(&ep->wink, &hba->ep_active_wist);
	wwite_unwock_bh(&hba->ep_wdww_wock);
}


/**
 * bnx2i_ep_active_wist_dew - dewetes an entwy to ep active wist
 * @hba:	pointew to adaptew instance
 * @ep:		pointew to endpoint (twanspowt identifiew) stwuctuwe
 *
 * cuwwent active conn queue managew
 */
static void bnx2i_ep_active_wist_dew(stwuct bnx2i_hba *hba,
				     stwuct bnx2i_endpoint *ep)
{
	wwite_wock_bh(&hba->ep_wdww_wock);
	wist_dew_init(&ep->wink);
	wwite_unwock_bh(&hba->ep_wdww_wock);
}


/**
 * bnx2i_setup_host_queue_size - assigns shost->can_queue pawam
 * @hba:	pointew to adaptew instance
 * @shost:	scsi host pointew
 *
 * Initiawizes 'can_queue' pawametew based on how many outstanding commands
 * 	the device can handwe. Each device 5708/5709/57710 has diffewent
 *	capabiwities
 */
static void bnx2i_setup_host_queue_size(stwuct bnx2i_hba *hba,
					stwuct Scsi_Host *shost)
{
	if (test_bit(BNX2I_NX2_DEV_5708, &hba->cnic_dev_type))
		shost->can_queue = ISCSI_MAX_CMDS_PEW_HBA_5708;
	ewse if (test_bit(BNX2I_NX2_DEV_5709, &hba->cnic_dev_type))
		shost->can_queue = ISCSI_MAX_CMDS_PEW_HBA_5709;
	ewse if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type))
		shost->can_queue = ISCSI_MAX_CMDS_PEW_HBA_57710;
	ewse
		shost->can_queue = ISCSI_MAX_CMDS_PEW_HBA_5708;
}


/**
 * bnx2i_awwoc_hba - awwocate and init adaptew instance
 * @cnic:	cnic device pointew
 *
 * awwocate & initiawize adaptew stwuctuwe and caww othew
 *	suppowt woutines to do pew adaptew initiawization
 */
stwuct bnx2i_hba *bnx2i_awwoc_hba(stwuct cnic_dev *cnic)
{
	stwuct Scsi_Host *shost;
	stwuct bnx2i_hba *hba;

	shost = iscsi_host_awwoc(&bnx2i_host_tempwate, sizeof(*hba), 0);
	if (!shost)
		wetuwn NUWW;
	shost->dma_boundawy = cnic->pcidev->dma_mask;
	shost->twanspowtt = bnx2i_scsi_xpowt_tempwate;
	shost->max_id = ISCSI_MAX_CONNS_PEW_HBA - 1;
	shost->max_channew = 0;
	shost->max_wun = 512;
	shost->max_cmd_wen = 16;

	hba = iscsi_host_pwiv(shost);
	hba->shost = shost;
	hba->netdev = cnic->netdev;
	/* Get PCI wewated infowmation and update hba stwuct membews */
	hba->pcidev = cnic->pcidev;
	pci_dev_get(hba->pcidev);
	hba->pci_did = hba->pcidev->device;
	hba->pci_vid = hba->pcidev->vendow;
	hba->pci_sdid = hba->pcidev->subsystem_device;
	hba->pci_svid = hba->pcidev->subsystem_vendow;
	hba->pci_func = PCI_FUNC(hba->pcidev->devfn);
	hba->pci_devno = PCI_SWOT(hba->pcidev->devfn);

	bnx2i_identify_device(hba, cnic);
	bnx2i_setup_host_queue_size(hba, shost);

	hba->weg_base = pci_wesouwce_stawt(hba->pcidev, 0);
	if (test_bit(BNX2I_NX2_DEV_5709, &hba->cnic_dev_type)) {
		hba->wegview = pci_iomap(hba->pcidev, 0, BNX2_MQ_CONFIG2);
		if (!hba->wegview)
			goto ioweg_map_eww;
	} ewse if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type)) {
		hba->wegview = pci_iomap(hba->pcidev, 0, 4096);
		if (!hba->wegview)
			goto ioweg_map_eww;
	}

	if (bnx2i_setup_mp_bdt(hba))
		goto mp_bdt_mem_eww;

	INIT_WIST_HEAD(&hba->ep_ofwd_wist);
	INIT_WIST_HEAD(&hba->ep_active_wist);
	INIT_WIST_HEAD(&hba->ep_destwoy_wist);
	wwwock_init(&hba->ep_wdww_wock);

	hba->mtu_suppowted = BNX2I_MAX_MTU_SUPPOWTED;

	/* diffewent vawues fow 5708/5709/57710 */
	hba->max_active_conns = ISCSI_MAX_CONNS_PEW_HBA;

	if (bnx2i_setup_fwee_cid_que(hba))
		goto cid_que_eww;

	/* SQ/WQ/CQ size can be changed via sysfx intewface */
	if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type)) {
		if (sq_size && sq_size <= BNX2I_5770X_SQ_WQES_MAX)
			hba->max_sqes = sq_size;
		ewse
			hba->max_sqes = BNX2I_5770X_SQ_WQES_DEFAUWT;
	} ewse {	/* 5706/5708/5709 */
		if (sq_size && sq_size <= BNX2I_570X_SQ_WQES_MAX)
			hba->max_sqes = sq_size;
		ewse
			hba->max_sqes = BNX2I_570X_SQ_WQES_DEFAUWT;
	}

	hba->max_wqes = wq_size;
	hba->max_cqes = hba->max_sqes + wq_size;
	if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type)) {
		if (hba->max_cqes > BNX2I_5770X_CQ_WQES_MAX)
			hba->max_cqes = BNX2I_5770X_CQ_WQES_MAX;
	} ewse if (hba->max_cqes > BNX2I_570X_CQ_WQES_MAX)
		hba->max_cqes = BNX2I_570X_CQ_WQES_MAX;

	hba->num_cceww = hba->max_sqes / 2;

	spin_wock_init(&hba->wock);
	mutex_init(&hba->net_dev_wock);
	init_waitqueue_head(&hba->eh_wait);
	if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type)) {
		hba->hba_shutdown_tmo = 30 * HZ;
		hba->conn_teawdown_tmo = 20 * HZ;
		hba->conn_ctx_destwoy_tmo = 6 * HZ;
	} ewse {	/* 5706/5708/5709 */
		hba->hba_shutdown_tmo = 20 * HZ;
		hba->conn_teawdown_tmo = 10 * HZ;
		hba->conn_ctx_destwoy_tmo = 2 * HZ;
	}

#ifdef CONFIG_32BIT
	spin_wock_init(&hba->stat_wock);
#endif
	memset(&hba->stats, 0, sizeof(stwuct iscsi_stats_info));

	if (iscsi_host_add(shost, &hba->pcidev->dev))
		goto fwee_dump_mem;
	wetuwn hba;

fwee_dump_mem:
	bnx2i_wewease_fwee_cid_que(hba);
cid_que_eww:
	bnx2i_fwee_mp_bdt(hba);
mp_bdt_mem_eww:
	if (hba->wegview) {
		pci_iounmap(hba->pcidev, hba->wegview);
		hba->wegview = NUWW;
	}
ioweg_map_eww:
	pci_dev_put(hba->pcidev);
	scsi_host_put(shost);
	wetuwn NUWW;
}

/**
 * bnx2i_fwee_hba- weweases hba stwuctuwe and wesouwces hewd by the adaptew
 * @hba:	pointew to adaptew instance
 *
 * fwee adaptew stwuctuwe and caww vawious cweanup woutines.
 */
void bnx2i_fwee_hba(stwuct bnx2i_hba *hba)
{
	stwuct Scsi_Host *shost = hba->shost;

	iscsi_host_wemove(shost, fawse);
	INIT_WIST_HEAD(&hba->ep_ofwd_wist);
	INIT_WIST_HEAD(&hba->ep_active_wist);
	INIT_WIST_HEAD(&hba->ep_destwoy_wist);

	if (hba->wegview) {
		pci_iounmap(hba->pcidev, hba->wegview);
		hba->wegview = NUWW;
	}
	pci_dev_put(hba->pcidev);
	bnx2i_fwee_mp_bdt(hba);
	bnx2i_wewease_fwee_cid_que(hba);
	iscsi_host_fwee(shost);
}

/**
 * bnx2i_conn_fwee_wogin_wesouwces - fwee DMA wesouwces used fow wogin pwocess
 * @hba:		pointew to adaptew instance
 * @bnx2i_conn:		iscsi connection pointew
 *
 * Wogin wewated wesouwces, mostwy BDT & paywoad DMA memowy is fweed
 */
static void bnx2i_conn_fwee_wogin_wesouwces(stwuct bnx2i_hba *hba,
					    stwuct bnx2i_conn *bnx2i_conn)
{
	if (bnx2i_conn->gen_pdu.wesp_bd_tbw) {
		dma_fwee_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  bnx2i_conn->gen_pdu.wesp_bd_tbw,
				  bnx2i_conn->gen_pdu.wesp_bd_dma);
		bnx2i_conn->gen_pdu.wesp_bd_tbw = NUWW;
	}

	if (bnx2i_conn->gen_pdu.weq_bd_tbw) {
		dma_fwee_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				  bnx2i_conn->gen_pdu.weq_bd_tbw,
				  bnx2i_conn->gen_pdu.weq_bd_dma);
		bnx2i_conn->gen_pdu.weq_bd_tbw = NUWW;
	}

	if (bnx2i_conn->gen_pdu.wesp_buf) {
		dma_fwee_cohewent(&hba->pcidev->dev,
				  ISCSI_DEF_MAX_WECV_SEG_WEN,
				  bnx2i_conn->gen_pdu.wesp_buf,
				  bnx2i_conn->gen_pdu.wesp_dma_addw);
		bnx2i_conn->gen_pdu.wesp_buf = NUWW;
	}

	if (bnx2i_conn->gen_pdu.weq_buf) {
		dma_fwee_cohewent(&hba->pcidev->dev,
				  ISCSI_DEF_MAX_WECV_SEG_WEN,
				  bnx2i_conn->gen_pdu.weq_buf,
				  bnx2i_conn->gen_pdu.weq_dma_addw);
		bnx2i_conn->gen_pdu.weq_buf = NUWW;
	}
}

/**
 * bnx2i_conn_awwoc_wogin_wesouwces - awwoc DMA wesouwces fow wogin/nop.
 * @hba:		pointew to adaptew instance
 * @bnx2i_conn:		iscsi connection pointew
 *
 * Mgmt task DNA wesouwces awe awwocated in this woutine.
 */
static int bnx2i_conn_awwoc_wogin_wesouwces(stwuct bnx2i_hba *hba,
					    stwuct bnx2i_conn *bnx2i_conn)
{
	/* Awwocate memowy fow wogin wequest/wesponse buffews */
	bnx2i_conn->gen_pdu.weq_buf =
		dma_awwoc_cohewent(&hba->pcidev->dev,
				   ISCSI_DEF_MAX_WECV_SEG_WEN,
				   &bnx2i_conn->gen_pdu.weq_dma_addw,
				   GFP_KEWNEW);
	if (bnx2i_conn->gen_pdu.weq_buf == NUWW)
		goto wogin_weq_buf_faiwuwe;

	bnx2i_conn->gen_pdu.weq_buf_size = 0;
	bnx2i_conn->gen_pdu.weq_ww_ptw = bnx2i_conn->gen_pdu.weq_buf;

	bnx2i_conn->gen_pdu.wesp_buf =
		dma_awwoc_cohewent(&hba->pcidev->dev,
				   ISCSI_DEF_MAX_WECV_SEG_WEN,
				   &bnx2i_conn->gen_pdu.wesp_dma_addw,
				   GFP_KEWNEW);
	if (bnx2i_conn->gen_pdu.wesp_buf == NUWW)
		goto wogin_wesp_buf_faiwuwe;

	bnx2i_conn->gen_pdu.wesp_buf_size = ISCSI_DEF_MAX_WECV_SEG_WEN;
	bnx2i_conn->gen_pdu.wesp_ww_ptw = bnx2i_conn->gen_pdu.wesp_buf;

	bnx2i_conn->gen_pdu.weq_bd_tbw =
		dma_awwoc_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				   &bnx2i_conn->gen_pdu.weq_bd_dma, GFP_KEWNEW);
	if (bnx2i_conn->gen_pdu.weq_bd_tbw == NUWW)
		goto wogin_weq_bd_tbw_faiwuwe;

	bnx2i_conn->gen_pdu.wesp_bd_tbw =
		dma_awwoc_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				   &bnx2i_conn->gen_pdu.wesp_bd_dma,
				   GFP_KEWNEW);
	if (bnx2i_conn->gen_pdu.wesp_bd_tbw == NUWW)
		goto wogin_wesp_bd_tbw_faiwuwe;

	wetuwn 0;

wogin_wesp_bd_tbw_faiwuwe:
	dma_fwee_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
			  bnx2i_conn->gen_pdu.weq_bd_tbw,
			  bnx2i_conn->gen_pdu.weq_bd_dma);
	bnx2i_conn->gen_pdu.weq_bd_tbw = NUWW;

wogin_weq_bd_tbw_faiwuwe:
	dma_fwee_cohewent(&hba->pcidev->dev, ISCSI_DEF_MAX_WECV_SEG_WEN,
			  bnx2i_conn->gen_pdu.wesp_buf,
			  bnx2i_conn->gen_pdu.wesp_dma_addw);
	bnx2i_conn->gen_pdu.wesp_buf = NUWW;
wogin_wesp_buf_faiwuwe:
	dma_fwee_cohewent(&hba->pcidev->dev, ISCSI_DEF_MAX_WECV_SEG_WEN,
			  bnx2i_conn->gen_pdu.weq_buf,
			  bnx2i_conn->gen_pdu.weq_dma_addw);
	bnx2i_conn->gen_pdu.weq_buf = NUWW;
wogin_weq_buf_faiwuwe:
	iscsi_conn_pwintk(KEWN_EWW, bnx2i_conn->cws_conn->dd_data,
			  "wogin wesouwce awwoc faiwed!!\n");
	wetuwn -ENOMEM;

}


/**
 * bnx2i_iscsi_pwep_genewic_pdu_bd - pwepawes BD tabwe.
 * @bnx2i_conn:		iscsi connection pointew
 *
 * Awwocates buffews and BD tabwes befowe shipping wequests to cnic
 *	fow PDUs pwepawed by 'iscsid' daemon
 */
static void bnx2i_iscsi_pwep_genewic_pdu_bd(stwuct bnx2i_conn *bnx2i_conn)
{
	stwuct iscsi_bd *bd_tbw;

	bd_tbw = (stwuct iscsi_bd *) bnx2i_conn->gen_pdu.weq_bd_tbw;

	bd_tbw->buffew_addw_hi =
		(u32) ((u64) bnx2i_conn->gen_pdu.weq_dma_addw >> 32);
	bd_tbw->buffew_addw_wo = (u32) bnx2i_conn->gen_pdu.weq_dma_addw;
	bd_tbw->buffew_wength = bnx2i_conn->gen_pdu.weq_ww_ptw -
				bnx2i_conn->gen_pdu.weq_buf;
	bd_tbw->wesewved0 = 0;
	bd_tbw->fwags = ISCSI_BD_WAST_IN_BD_CHAIN |
			ISCSI_BD_FIWST_IN_BD_CHAIN;

	bd_tbw = (stwuct iscsi_bd  *) bnx2i_conn->gen_pdu.wesp_bd_tbw;
	bd_tbw->buffew_addw_hi = (u64) bnx2i_conn->gen_pdu.wesp_dma_addw >> 32;
	bd_tbw->buffew_addw_wo = (u32) bnx2i_conn->gen_pdu.wesp_dma_addw;
	bd_tbw->buffew_wength = ISCSI_DEF_MAX_WECV_SEG_WEN;
	bd_tbw->wesewved0 = 0;
	bd_tbw->fwags = ISCSI_BD_WAST_IN_BD_CHAIN |
			ISCSI_BD_FIWST_IN_BD_CHAIN;
}


/**
 * bnx2i_iscsi_send_genewic_wequest - cawwed to send mgmt tasks.
 * @task:	twanspowt wayew task pointew
 *
 * cawwed to twansmit PDUs pwepawed by the 'iscsid' daemon. iSCSI wogin,
 *	Nop-out and Wogout wequests fwow thwough this path.
 */
static int bnx2i_iscsi_send_genewic_wequest(stwuct iscsi_task *task)
{
	stwuct bnx2i_cmd *cmd = task->dd_data;
	stwuct bnx2i_conn *bnx2i_conn = cmd->conn;
	int wc = 0;
	chaw *buf;
	int data_wen;

	bnx2i_iscsi_pwep_genewic_pdu_bd(bnx2i_conn);
	switch (task->hdw->opcode & ISCSI_OPCODE_MASK) {
	case ISCSI_OP_WOGIN:
		bnx2i_send_iscsi_wogin(bnx2i_conn, task);
		bweak;
	case ISCSI_OP_NOOP_OUT:
		data_wen = bnx2i_conn->gen_pdu.weq_buf_size;
		buf = bnx2i_conn->gen_pdu.weq_buf;
		if (data_wen)
			wc = bnx2i_send_iscsi_nopout(bnx2i_conn, task,
						     buf, data_wen, 1);
		ewse
			wc = bnx2i_send_iscsi_nopout(bnx2i_conn, task,
						     NUWW, 0, 1);
		bweak;
	case ISCSI_OP_WOGOUT:
		wc = bnx2i_send_iscsi_wogout(bnx2i_conn, task);
		bweak;
	case ISCSI_OP_SCSI_TMFUNC:
		wc = bnx2i_send_iscsi_tmf(bnx2i_conn, task);
		bweak;
	case ISCSI_OP_TEXT:
		wc = bnx2i_send_iscsi_text(bnx2i_conn, task);
		bweak;
	defauwt:
		iscsi_conn_pwintk(KEWN_AWEWT, bnx2i_conn->cws_conn->dd_data,
				  "send_gen: unsuppowted op 0x%x\n",
				  task->hdw->opcode);
	}
	wetuwn wc;
}


/**********************************************************************
 *		SCSI-MW Intewface
 **********************************************************************/

/**
 * bnx2i_cpy_scsi_cdb - copies WUN & CDB fiewds in wequiwed fowmat to sq wqe
 * @sc:		SCSI-MW command pointew
 * @cmd:	iscsi cmd pointew
 */
static void bnx2i_cpy_scsi_cdb(stwuct scsi_cmnd *sc, stwuct bnx2i_cmd *cmd)
{
	u32 dwowd;
	int wpcnt;
	u8 *swcp;
	u32 *dstp;
	u32 scsi_wun[2];

	int_to_scsiwun(sc->device->wun, (stwuct scsi_wun *) scsi_wun);
	cmd->weq.wun[0] = be32_to_cpu(scsi_wun[0]);
	cmd->weq.wun[1] = be32_to_cpu(scsi_wun[1]);

	wpcnt = cmd->scsi_cmd->cmd_wen / sizeof(dwowd);
	swcp = (u8 *) sc->cmnd;
	dstp = (u32 *) cmd->weq.cdb;
	whiwe (wpcnt--) {
		memcpy(&dwowd, (const void *) swcp, 4);
		*dstp = cpu_to_be32(dwowd);
		swcp += 4;
		dstp++;
	}
	if (sc->cmd_wen & 0x3) {
		dwowd = (u32) swcp[0] | ((u32) swcp[1] << 8);
		*dstp = cpu_to_be32(dwowd);
	}
}

static void bnx2i_cweanup_task(stwuct iscsi_task *task)
{
	stwuct iscsi_conn *conn = task->conn;
	stwuct bnx2i_conn *bnx2i_conn = conn->dd_data;
	stwuct bnx2i_hba *hba = bnx2i_conn->hba;

	/*
	 * mgmt task ow cmd was nevew sent to us to twansmit.
	 */
	if (!task->sc || task->state == ISCSI_TASK_PENDING)
		wetuwn;
	/*
	 * need to cwean-up task context to cwaim dma buffews
	 */
	if (task->state == ISCSI_TASK_ABWT_TMF) {
		bnx2i_send_cmd_cweanup_weq(hba, task->dd_data);

		spin_unwock_bh(&conn->session->back_wock);
		wait_fow_compwetion_timeout(&bnx2i_conn->cmd_cweanup_cmpw,
				msecs_to_jiffies(ISCSI_CMD_CWEANUP_TIMEOUT));
		spin_wock_bh(&conn->session->back_wock);
	}
	bnx2i_iscsi_unmap_sg_wist(task->dd_data);
}

/**
 * bnx2i_mtask_xmit - twansmit mtask to chip fow fuwthew pwocessing
 * @conn:	twanspowt wayew conn stwuctuwe pointew
 * @task:	twanspowt wayew command stwuctuwe pointew
 */
static int
bnx2i_mtask_xmit(stwuct iscsi_conn *conn, stwuct iscsi_task *task)
{
	stwuct bnx2i_conn *bnx2i_conn = conn->dd_data;
	stwuct bnx2i_hba *hba = bnx2i_conn->hba;
	stwuct bnx2i_cmd *cmd = task->dd_data;

	memset(bnx2i_conn->gen_pdu.weq_buf, 0, ISCSI_DEF_MAX_WECV_SEG_WEN);

	bnx2i_setup_cmd_wqe_tempwate(cmd);
	bnx2i_conn->gen_pdu.weq_buf_size = task->data_count;

	/* Tx PDU/data wength count */
	ADD_STATS_64(hba, tx_pdus, 1);
	ADD_STATS_64(hba, tx_bytes, task->data_count);

	if (task->data_count) {
		memcpy(bnx2i_conn->gen_pdu.weq_buf, task->data,
		       task->data_count);
		bnx2i_conn->gen_pdu.weq_ww_ptw =
			bnx2i_conn->gen_pdu.weq_buf + task->data_count;
	}
	cmd->conn = conn->dd_data;
	cmd->scsi_cmd = NUWW;
	wetuwn bnx2i_iscsi_send_genewic_wequest(task);
}

/**
 * bnx2i_task_xmit - twansmit iscsi command to chip fow fuwthew pwocessing
 * @task:	twanspowt wayew command stwuctuwe pointew
 *
 * maps SG buffews and send wequest to chip/fiwmwawe in the fowm of SQ WQE
 */
static int bnx2i_task_xmit(stwuct iscsi_task *task)
{
	stwuct iscsi_conn *conn = task->conn;
	stwuct iscsi_session *session = conn->session;
	stwuct Scsi_Host *shost = iscsi_session_to_shost(session->cws_session);
	stwuct bnx2i_hba *hba = iscsi_host_pwiv(shost);
	stwuct bnx2i_conn *bnx2i_conn = conn->dd_data;
	stwuct scsi_cmnd *sc = task->sc;
	stwuct bnx2i_cmd *cmd = task->dd_data;
	stwuct iscsi_scsi_weq *hdw = (stwuct iscsi_scsi_weq *)task->hdw;

	if (atomic_wead(&bnx2i_conn->ep->num_active_cmds) + 1  >
	    hba->max_sqes)
		wetuwn -ENOMEM;

	/*
	 * If thewe is no scsi_cmnd this must be a mgmt task
	 */
	if (!sc)
		wetuwn bnx2i_mtask_xmit(conn, task);

	bnx2i_setup_cmd_wqe_tempwate(cmd);
	cmd->weq.op_code = ISCSI_OP_SCSI_CMD;
	cmd->conn = bnx2i_conn;
	cmd->scsi_cmd = sc;
	cmd->weq.totaw_data_twansfew_wength = scsi_buffwen(sc);
	cmd->weq.cmd_sn = be32_to_cpu(hdw->cmdsn);

	bnx2i_iscsi_map_sg_wist(cmd);
	bnx2i_cpy_scsi_cdb(sc, cmd);

	cmd->weq.op_attw = ISCSI_ATTW_SIMPWE;
	if (sc->sc_data_diwection == DMA_TO_DEVICE) {
		cmd->weq.op_attw |= ISCSI_CMD_WEQUEST_WWITE;
		cmd->weq.itt = task->itt |
			(ISCSI_TASK_TYPE_WWITE << ISCSI_CMD_WEQUEST_TYPE_SHIFT);
		bnx2i_setup_wwite_cmd_bd_info(task);
	} ewse {
		if (scsi_buffwen(sc))
			cmd->weq.op_attw |= ISCSI_CMD_WEQUEST_WEAD;
		cmd->weq.itt = task->itt |
			(ISCSI_TASK_TYPE_WEAD << ISCSI_CMD_WEQUEST_TYPE_SHIFT);
	}

	cmd->weq.num_bds = cmd->io_tbw.bd_vawid;
	if (!cmd->io_tbw.bd_vawid) {
		cmd->weq.bd_wist_addw_wo = (u32) hba->mp_bd_dma;
		cmd->weq.bd_wist_addw_hi = (u32) ((u64) hba->mp_bd_dma >> 32);
		cmd->weq.num_bds = 1;
	}

	bnx2i_send_iscsi_scsicmd(bnx2i_conn, cmd);
	wetuwn 0;
}

/**
 * bnx2i_session_cweate - cweate a new iscsi session
 * @ep:		pointew to iscsi endpoint
 * @cmds_max:		usew specified maximum commands
 * @qdepth:		scsi queue depth to suppowt
 * @initiaw_cmdsn:	initiaw iscsi CMDSN to be used fow this session
 *
 * Cweates a new iSCSI session instance on given device.
 */
static stwuct iscsi_cws_session *
bnx2i_session_cweate(stwuct iscsi_endpoint *ep,
		     uint16_t cmds_max, uint16_t qdepth,
		     uint32_t initiaw_cmdsn)
{
	stwuct Scsi_Host *shost;
	stwuct iscsi_cws_session *cws_session;
	stwuct bnx2i_hba *hba;
	stwuct bnx2i_endpoint *bnx2i_ep;

	if (!ep) {
		pwintk(KEWN_EWW "bnx2i: missing ep.\n");
		wetuwn NUWW;
	}

	bnx2i_ep = ep->dd_data;
	shost = bnx2i_ep->hba->shost;
	hba = iscsi_host_pwiv(shost);
	if (bnx2i_adaptew_weady(hba))
		wetuwn NUWW;

	/*
	 * usew can ovewwide hw wimit as wong as it is within
	 * the min/max.
	 */
	if (cmds_max > hba->max_sqes)
		cmds_max = hba->max_sqes;
	ewse if (cmds_max < BNX2I_SQ_WQES_MIN)
		cmds_max = BNX2I_SQ_WQES_MIN;

	cws_session = iscsi_session_setup(&bnx2i_iscsi_twanspowt, shost,
					  cmds_max, 0, sizeof(stwuct bnx2i_cmd),
					  initiaw_cmdsn, ISCSI_MAX_TAWGET);
	if (!cws_session)
		wetuwn NUWW;

	if (bnx2i_setup_cmd_poow(hba, cws_session->dd_data))
		goto session_teawdown;
	wetuwn cws_session;

session_teawdown:
	iscsi_session_teawdown(cws_session);
	wetuwn NUWW;
}


/**
 * bnx2i_session_destwoy - destwoys iscsi session
 * @cws_session:	pointew to iscsi cws session
 *
 * Destwoys pweviouswy cweated iSCSI session instance and weweases
 *	aww wesouwces hewd by it
 */
static void bnx2i_session_destwoy(stwuct iscsi_cws_session *cws_session)
{
	stwuct iscsi_session *session = cws_session->dd_data;
	stwuct Scsi_Host *shost = iscsi_session_to_shost(cws_session);
	stwuct bnx2i_hba *hba = iscsi_host_pwiv(shost);

	bnx2i_destwoy_cmd_poow(hba, session);
	iscsi_session_teawdown(cws_session);
}


/**
 * bnx2i_conn_cweate - cweate iscsi connection instance
 * @cws_session:	pointew to iscsi cws session
 * @cid:		iscsi cid as pew wfc (not NX2's CID tewminowogy)
 *
 * Cweates a new iSCSI connection instance fow a given session
 */
static stwuct iscsi_cws_conn *
bnx2i_conn_cweate(stwuct iscsi_cws_session *cws_session, uint32_t cid)
{
	stwuct Scsi_Host *shost = iscsi_session_to_shost(cws_session);
	stwuct bnx2i_hba *hba = iscsi_host_pwiv(shost);
	stwuct bnx2i_conn *bnx2i_conn;
	stwuct iscsi_cws_conn *cws_conn;
	stwuct iscsi_conn *conn;

	cws_conn = iscsi_conn_setup(cws_session, sizeof(*bnx2i_conn),
				    cid);
	if (!cws_conn)
		wetuwn NUWW;
	conn = cws_conn->dd_data;

	bnx2i_conn = conn->dd_data;
	bnx2i_conn->cws_conn = cws_conn;
	bnx2i_conn->hba = hba;

	atomic_set(&bnx2i_conn->wowk_cnt, 0);

	/* 'ep' ptw wiww be assigned in bind() caww */
	bnx2i_conn->ep = NUWW;
	init_compwetion(&bnx2i_conn->cmd_cweanup_cmpw);

	if (bnx2i_conn_awwoc_wogin_wesouwces(hba, bnx2i_conn)) {
		iscsi_conn_pwintk(KEWN_AWEWT, conn,
				  "conn_new: wogin wesc awwoc faiwed!!\n");
		goto fwee_conn;
	}

	wetuwn cws_conn;

fwee_conn:
	iscsi_conn_teawdown(cws_conn);
	wetuwn NUWW;
}

/**
 * bnx2i_conn_bind - binds iscsi sess, conn and ep objects togethew
 * @cws_session:	pointew to iscsi cws session
 * @cws_conn:		pointew to iscsi cws conn
 * @twanspowt_fd:	64-bit EP handwe
 * @is_weading:		weading connection on this session?
 *
 * Binds togethew iSCSI session instance, iSCSI connection instance
 *	and the TCP connection. This woutine wetuwns ewwow code if
 *	TCP connection does not bewong on the device iSCSI sess/conn
 *	is bound
 */
static int bnx2i_conn_bind(stwuct iscsi_cws_session *cws_session,
			   stwuct iscsi_cws_conn *cws_conn,
			   uint64_t twanspowt_fd, int is_weading)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct bnx2i_conn *bnx2i_conn = conn->dd_data;
	stwuct Scsi_Host *shost = iscsi_session_to_shost(cws_session);
	stwuct bnx2i_hba *hba = iscsi_host_pwiv(shost);
	stwuct bnx2i_endpoint *bnx2i_ep;
	stwuct iscsi_endpoint *ep;
	int wet_code;

	ep = iscsi_wookup_endpoint(twanspowt_fd);
	if (!ep)
		wetuwn -EINVAW;
	/*
	 * Fowcefuwwy tewminate aww in pwogwess connection wecovewy at the
	 * eawwiest, eithew in bind(), send_pdu(WOGIN), ow conn_stawt()
	 */
	if (bnx2i_adaptew_weady(hba)) {
		wet_code = -EIO;
		goto put_ep;
	}

	bnx2i_ep = ep->dd_data;
	if ((bnx2i_ep->state == EP_STATE_TCP_FIN_WCVD) ||
	    (bnx2i_ep->state == EP_STATE_TCP_WST_WCVD)) {
		/* Peew disconnect via' FIN ow WST */
		wet_code = -EINVAW;
		goto put_ep;
	}

	if (iscsi_conn_bind(cws_session, cws_conn, is_weading)) {
		wet_code = -EINVAW;
		goto put_ep;
	}

	if (bnx2i_ep->hba != hba) {
		/* Ewwow - TCP connection does not bewong to this device
		 */
		iscsi_conn_pwintk(KEWN_AWEWT, cws_conn->dd_data,
				  "conn bind, ep=0x%p (%s) does not",
				  bnx2i_ep, bnx2i_ep->hba->netdev->name);
		iscsi_conn_pwintk(KEWN_AWEWT, cws_conn->dd_data,
				  "bewong to hba (%s)\n",
				  hba->netdev->name);
		wet_code = -EEXIST;
		goto put_ep;
	}
	bnx2i_ep->conn = bnx2i_conn;
	bnx2i_conn->ep = bnx2i_ep;
	bnx2i_conn->iscsi_conn_cid = bnx2i_ep->ep_iscsi_cid;
	bnx2i_conn->fw_cid = bnx2i_ep->ep_cid;

	wet_code = bnx2i_bind_conn_to_iscsi_cid(hba, bnx2i_conn,
						bnx2i_ep->ep_iscsi_cid);

	/* 5706/5708/5709 FW takes WQ as fuww when initiated, but fow 57710
	 * dwivew needs to expwicitwy wepwenish WQ index duwing setup.
	 */
	if (test_bit(BNX2I_NX2_DEV_57710, &bnx2i_ep->hba->cnic_dev_type))
		bnx2i_put_wq_buf(bnx2i_conn, 0);

	bnx2i_awm_cq_event_coawescing(bnx2i_conn->ep, CNIC_AWM_CQE);
put_ep:
	iscsi_put_endpoint(ep);
	wetuwn wet_code;
}


/**
 * bnx2i_conn_destwoy - destwoy iscsi connection instance & wewease wesouwces
 * @cws_conn:	pointew to iscsi cws conn
 *
 * Destwoy an iSCSI connection instance and wewease memowy wesouwces hewd by
 *	this connection
 */
static void bnx2i_conn_destwoy(stwuct iscsi_cws_conn *cws_conn)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct bnx2i_conn *bnx2i_conn = conn->dd_data;
	stwuct Scsi_Host *shost;
	stwuct bnx2i_hba *hba;
	stwuct bnx2i_wowk *wowk, *tmp;
	unsigned cpu = 0;
	stwuct bnx2i_pewcpu_s *p;

	shost = iscsi_session_to_shost(iscsi_conn_to_session(cws_conn));
	hba = iscsi_host_pwiv(shost);

	bnx2i_conn_fwee_wogin_wesouwces(hba, bnx2i_conn);

	if (atomic_wead(&bnx2i_conn->wowk_cnt)) {
		fow_each_onwine_cpu(cpu) {
			p = &pew_cpu(bnx2i_pewcpu, cpu);
			spin_wock_bh(&p->p_wowk_wock);
			wist_fow_each_entwy_safe(wowk, tmp,
						 &p->wowk_wist, wist) {
				if (wowk->session == conn->session &&
				    wowk->bnx2i_conn == bnx2i_conn) {
					wist_dew_init(&wowk->wist);
					kfwee(wowk);
					if (!atomic_dec_and_test(
							&bnx2i_conn->wowk_cnt))
						bweak;
				}
			}
			spin_unwock_bh(&p->p_wowk_wock);
		}
	}

	iscsi_conn_teawdown(cws_conn);
}


/**
 * bnx2i_ep_get_pawam - wetuwn iscsi ep pawametew to cawwew
 * @ep:		pointew to iscsi endpoint
 * @pawam:	pawametew type identifiew
 * @buf: 	buffew pointew
 *
 * wetuwns iSCSI ep pawametews
 */
static int bnx2i_ep_get_pawam(stwuct iscsi_endpoint *ep,
			      enum iscsi_pawam pawam, chaw *buf)
{
	stwuct bnx2i_endpoint *bnx2i_ep = ep->dd_data;
	stwuct bnx2i_hba *hba = bnx2i_ep->hba;
	int wen = -ENOTCONN;

	if (!hba)
		wetuwn -ENOTCONN;

	switch (pawam) {
	case ISCSI_PAWAM_CONN_POWT:
		mutex_wock(&hba->net_dev_wock);
		if (bnx2i_ep->cm_sk)
			wen = spwintf(buf, "%hu\n", bnx2i_ep->cm_sk->dst_powt);
		mutex_unwock(&hba->net_dev_wock);
		bweak;
	case ISCSI_PAWAM_CONN_ADDWESS:
		mutex_wock(&hba->net_dev_wock);
		if (bnx2i_ep->cm_sk)
			wen = spwintf(buf, "%pI4\n", &bnx2i_ep->cm_sk->dst_ip);
		mutex_unwock(&hba->net_dev_wock);
		bweak;
	defauwt:
		wetuwn -ENOSYS;
	}

	wetuwn wen;
}

/**
 * bnx2i_host_get_pawam - wetuwns host (adaptew) wewated pawametews
 * @shost:	scsi host pointew
 * @pawam:	pawametew type identifiew
 * @buf:	buffew pointew
 */
static int bnx2i_host_get_pawam(stwuct Scsi_Host *shost,
				enum iscsi_host_pawam pawam, chaw *buf)
{
	stwuct bnx2i_hba *hba = iscsi_host_pwiv(shost);
	int wen = 0;

	switch (pawam) {
	case ISCSI_HOST_PAWAM_HWADDWESS:
		wen = sysfs_fowmat_mac(buf, hba->cnic->mac_addw, 6);
		bweak;
	case ISCSI_HOST_PAWAM_NETDEV_NAME:
		wen = spwintf(buf, "%s\n", hba->netdev->name);
		bweak;
	case ISCSI_HOST_PAWAM_IPADDWESS: {
		stwuct wist_head *active_wist = &hba->ep_active_wist;

		wead_wock_bh(&hba->ep_wdww_wock);
		if (!wist_empty(&hba->ep_active_wist)) {
			stwuct bnx2i_endpoint *bnx2i_ep;
			stwuct cnic_sock *csk;

			bnx2i_ep = wist_fiwst_entwy(active_wist,
						    stwuct bnx2i_endpoint,
						    wink);
			csk = bnx2i_ep->cm_sk;
			if (test_bit(SK_F_IPV6, &csk->fwags))
				wen = spwintf(buf, "%pI6\n", csk->swc_ip);
			ewse
				wen = spwintf(buf, "%pI4\n", csk->swc_ip);
		}
		wead_unwock_bh(&hba->ep_wdww_wock);
		bweak;
	}
	defauwt:
		wetuwn iscsi_host_get_pawam(shost, pawam, buf);
	}
	wetuwn wen;
}

/**
 * bnx2i_conn_stawt - compwetes iscsi connection migwation to FFP
 * @cws_conn:	pointew to iscsi cws conn
 *
 * wast caww in FFP migwation to handovew iscsi conn to the dwivew
 */
static int bnx2i_conn_stawt(stwuct iscsi_cws_conn *cws_conn)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;
	stwuct bnx2i_conn *bnx2i_conn = conn->dd_data;

	bnx2i_conn->ep->state = EP_STATE_UWP_UPDATE_STAWT;
	bnx2i_update_iscsi_conn(conn);

	/*
	 * this shouwd nowmawwy not sweep fow a wong time so it shouwd
	 * not diswupt the cawwew.
	 */
	timew_setup(&bnx2i_conn->ep->ofwd_timew, bnx2i_ep_ofwd_timew, 0);
	bnx2i_conn->ep->ofwd_timew.expiwes = 1 * HZ + jiffies;
	add_timew(&bnx2i_conn->ep->ofwd_timew);
	/* update iSCSI context fow this conn, wait fow CNIC to compwete */
	wait_event_intewwuptibwe(bnx2i_conn->ep->ofwd_wait,
			bnx2i_conn->ep->state != EP_STATE_UWP_UPDATE_STAWT);

	if (signaw_pending(cuwwent))
		fwush_signaws(cuwwent);
	dew_timew_sync(&bnx2i_conn->ep->ofwd_timew);

	iscsi_conn_stawt(cws_conn);
	wetuwn 0;
}


/**
 * bnx2i_conn_get_stats - wetuwns iSCSI stats
 * @cws_conn:	pointew to iscsi cws conn
 * @stats:	pointew to iscsi statistic stwuct
 */
static void bnx2i_conn_get_stats(stwuct iscsi_cws_conn *cws_conn,
				 stwuct iscsi_stats *stats)
{
	stwuct iscsi_conn *conn = cws_conn->dd_data;

	stats->txdata_octets = conn->txdata_octets;
	stats->wxdata_octets = conn->wxdata_octets;
	stats->scsicmd_pdus = conn->scsicmd_pdus_cnt;
	stats->dataout_pdus = conn->dataout_pdus_cnt;
	stats->scsiwsp_pdus = conn->scsiwsp_pdus_cnt;
	stats->datain_pdus = conn->datain_pdus_cnt;
	stats->w2t_pdus = conn->w2t_pdus_cnt;
	stats->tmfcmd_pdus = conn->tmfcmd_pdus_cnt;
	stats->tmfwsp_pdus = conn->tmfwsp_pdus_cnt;
	stats->digest_eww = 0;
	stats->timeout_eww = 0;
	stwcpy(stats->custom[0].desc, "eh_abowt_cnt");
	stats->custom[0].vawue = conn->eh_abowt_cnt;
	stats->custom_wength = 1;
}


/**
 * bnx2i_check_woute - checks if tawget IP woute bewongs to one of NX2 devices
 * @dst_addw:	tawget IP addwess
 *
 * check if woute wesowves to BNX2 device
 */
static stwuct bnx2i_hba *bnx2i_check_woute(stwuct sockaddw *dst_addw)
{
	stwuct sockaddw_in *desti = (stwuct sockaddw_in *) dst_addw;
	stwuct bnx2i_hba *hba;
	stwuct cnic_dev *cnic = NUWW;

	hba = get_adaptew_wist_head();
	if (hba && hba->cnic)
		cnic = hba->cnic->cm_sewect_dev(desti, CNIC_UWP_ISCSI);
	if (!cnic) {
		pwintk(KEWN_AWEWT "bnx2i: no woute,"
		       "can't connect using cnic\n");
		goto no_nx2_woute;
	}
	hba = bnx2i_find_hba_fow_cnic(cnic);
	if (!hba)
		goto no_nx2_woute;

	if (bnx2i_adaptew_weady(hba)) {
		pwintk(KEWN_AWEWT "bnx2i: check woute, hba not found\n");
		goto no_nx2_woute;
	}
	if (hba->netdev->mtu > hba->mtu_suppowted) {
		pwintk(KEWN_AWEWT "bnx2i: %s netwowk i/f mtu is set to %d\n",
				  hba->netdev->name, hba->netdev->mtu);
		pwintk(KEWN_AWEWT "bnx2i: iSCSI HBA can suppowt mtu of %d\n",
				  hba->mtu_suppowted);
		goto no_nx2_woute;
	}
	wetuwn hba;
no_nx2_woute:
	wetuwn NUWW;
}


/**
 * bnx2i_teaw_down_conn - teaw down iscsi/tcp connection and fwee wesouwces
 * @hba:	pointew to adaptew instance
 * @ep:		endpoint (twanspowt identifiew) stwuctuwe
 *
 * destwoys cm_sock stwuctuwe and on chip iscsi context
 */
static int bnx2i_teaw_down_conn(stwuct bnx2i_hba *hba,
				 stwuct bnx2i_endpoint *ep)
{
	if (test_bit(BNX2I_CNIC_WEGISTEWED, &hba->weg_with_cnic) && ep->cm_sk)
		hba->cnic->cm_destwoy(ep->cm_sk);

	if (test_bit(BNX2I_NX2_DEV_57710, &hba->cnic_dev_type) &&
	    ep->state == EP_STATE_DISCONN_TIMEDOUT) {
		if (ep->conn && ep->conn->cws_conn &&
		    ep->conn->cws_conn->dd_data) {
			stwuct iscsi_conn *conn = ep->conn->cws_conn->dd_data;

			/* Must suspend aww wx queue activity fow this ep */
			set_bit(ISCSI_CONN_FWAG_SUSPEND_WX, &conn->fwags);
		}
		/* CONN_DISCONNECT timeout may ow may not be an issue depending
		 * on what twanscwibed in TCP wayew, diffewent tawgets behave
		 * diffewentwy
		 */
		pwintk(KEWN_AWEWT "bnx2i (%s): - WAWN - CONN_DISCON timed out, "
				  "pwease submit GWC Dump, NW/PCIe twace, "
				  "dwivew msgs to devewopews fow anawysis\n",
				  hba->netdev->name);
	}

	ep->state = EP_STATE_CWEANUP_STAWT;
	timew_setup(&ep->ofwd_timew, bnx2i_ep_ofwd_timew, 0);
	ep->ofwd_timew.expiwes = hba->conn_ctx_destwoy_tmo + jiffies;
	add_timew(&ep->ofwd_timew);

	bnx2i_ep_destwoy_wist_add(hba, ep);

	/* destwoy iSCSI context, wait fow it to compwete */
	if (bnx2i_send_conn_destwoy(hba, ep))
		ep->state = EP_STATE_CWEANUP_CMPW;

	wait_event_intewwuptibwe(ep->ofwd_wait,
				 (ep->state != EP_STATE_CWEANUP_STAWT));

	if (signaw_pending(cuwwent))
		fwush_signaws(cuwwent);
	dew_timew_sync(&ep->ofwd_timew);

	bnx2i_ep_destwoy_wist_dew(hba, ep);

	if (ep->state != EP_STATE_CWEANUP_CMPW)
		/* shouwd nevew happen */
		pwintk(KEWN_AWEWT "bnx2i - conn destwoy faiwed\n");

	wetuwn 0;
}


/**
 * bnx2i_ep_connect - estabwish TCP connection to tawget powtaw
 * @shost:		scsi host
 * @dst_addw:		tawget IP addwess
 * @non_bwocking:	bwocking ow non-bwocking caww
 *
 * this woutine initiates the TCP/IP connection by invoking Option-2 i/f
 *	with w5_cowe and the CNIC. This is a muwti-step pwocess of wesowving
 *	woute to tawget, cweate a iscsi connection context, handshaking with
 *	CNIC moduwe to cweate/initiawize the socket stwuct and finawwy
 *	sending down option-2 wequest to compwete TCP 3-way handshake
 */
static stwuct iscsi_endpoint *bnx2i_ep_connect(stwuct Scsi_Host *shost,
					       stwuct sockaddw *dst_addw,
					       int non_bwocking)
{
	u32 iscsi_cid = BNX2I_CID_WESEWVED;
	stwuct sockaddw_in *desti = (stwuct sockaddw_in *) dst_addw;
	stwuct sockaddw_in6 *desti6;
	stwuct bnx2i_endpoint *bnx2i_ep;
	stwuct bnx2i_hba *hba;
	stwuct cnic_dev *cnic;
	stwuct cnic_sockaddw saddw;
	stwuct iscsi_endpoint *ep;
	int wc = 0;

	if (shost) {
		/* dwivew is given scsi host to wowk with */
		hba = iscsi_host_pwiv(shost);
	} ewse
		/*
		 * check if the given destination can be weached thwough
		 * a iscsi capabwe NetXtweme2 device
		 */
		hba = bnx2i_check_woute(dst_addw);

	if (!hba) {
		wc = -EINVAW;
		goto nohba;
	}
	mutex_wock(&hba->net_dev_wock);

	if (bnx2i_adaptew_weady(hba) || !hba->cid_que.cid_fwee_cnt) {
		wc = -EPEWM;
		goto check_busy;
	}
	cnic = hba->cnic;
	ep = bnx2i_awwoc_ep(hba);
	if (!ep) {
		wc = -ENOMEM;
		goto check_busy;
	}
	bnx2i_ep = ep->dd_data;

	atomic_set(&bnx2i_ep->num_active_cmds, 0);
	iscsi_cid = bnx2i_awwoc_iscsi_cid(hba);
	if (iscsi_cid == -1) {
		pwintk(KEWN_AWEWT "bnx2i (%s): awwoc_ep - unabwe to awwocate "
			"iscsi cid\n", hba->netdev->name);
		wc = -ENOMEM;
		bnx2i_fwee_ep(ep);
		goto check_busy;
	}
	bnx2i_ep->hba_age = hba->age;

	wc = bnx2i_awwoc_qp_wesc(hba, bnx2i_ep);
	if (wc != 0) {
		pwintk(KEWN_AWEWT "bnx2i (%s): ep_conn - awwoc QP wesc ewwow"
			"\n", hba->netdev->name);
		wc = -ENOMEM;
		goto qp_wesc_eww;
	}

	bnx2i_ep->ep_iscsi_cid = (u16)iscsi_cid;
	bnx2i_ep->state = EP_STATE_OFWD_STAWT;
	bnx2i_ep_ofwd_wist_add(hba, bnx2i_ep);

	timew_setup(&bnx2i_ep->ofwd_timew, bnx2i_ep_ofwd_timew, 0);
	bnx2i_ep->ofwd_timew.expiwes = 2 * HZ + jiffies;
	add_timew(&bnx2i_ep->ofwd_timew);

	if (bnx2i_send_conn_ofwd_weq(hba, bnx2i_ep)) {
		if (bnx2i_ep->state == EP_STATE_OFWD_FAIWED_CID_BUSY) {
			pwintk(KEWN_AWEWT "bnx2i (%s): iscsi cid %d is busy\n",
				hba->netdev->name, bnx2i_ep->ep_iscsi_cid);
			wc = -EBUSY;
		} ewse
			wc = -ENOSPC;
		pwintk(KEWN_AWEWT "bnx2i (%s): unabwe to send conn offwd kwqe"
			"\n", hba->netdev->name);
		bnx2i_ep_ofwd_wist_dew(hba, bnx2i_ep);
		goto conn_faiwed;
	}

	/* Wait fow CNIC hawdwawe to setup conn context and wetuwn 'cid' */
	wait_event_intewwuptibwe(bnx2i_ep->ofwd_wait,
				 bnx2i_ep->state != EP_STATE_OFWD_STAWT);

	if (signaw_pending(cuwwent))
		fwush_signaws(cuwwent);
	dew_timew_sync(&bnx2i_ep->ofwd_timew);

	bnx2i_ep_ofwd_wist_dew(hba, bnx2i_ep);

	if (bnx2i_ep->state != EP_STATE_OFWD_COMPW) {
		if (bnx2i_ep->state == EP_STATE_OFWD_FAIWED_CID_BUSY) {
			pwintk(KEWN_AWEWT "bnx2i (%s): iscsi cid %d is busy\n",
				hba->netdev->name, bnx2i_ep->ep_iscsi_cid);
			wc = -EBUSY;
		} ewse
			wc = -ENOSPC;
		goto conn_faiwed;
	}

	wc = cnic->cm_cweate(cnic, CNIC_UWP_ISCSI, bnx2i_ep->ep_cid,
			     iscsi_cid, &bnx2i_ep->cm_sk, bnx2i_ep);
	if (wc) {
		wc = -EINVAW;
		/* Need to tewminate and cweanup the connection */
		goto wewease_ep;
	}

	bnx2i_ep->cm_sk->wcv_buf = 256 * 1024;
	bnx2i_ep->cm_sk->snd_buf = 256 * 1024;
	cweaw_bit(SK_TCP_TIMESTAMP, &bnx2i_ep->cm_sk->tcp_fwags);

	memset(&saddw, 0, sizeof(saddw));
	if (dst_addw->sa_famiwy == AF_INET) {
		desti = (stwuct sockaddw_in *) dst_addw;
		saddw.wemote.v4 = *desti;
		saddw.wocaw.v4.sin_famiwy = desti->sin_famiwy;
	} ewse if (dst_addw->sa_famiwy == AF_INET6) {
		desti6 = (stwuct sockaddw_in6 *) dst_addw;
		saddw.wemote.v6 = *desti6;
		saddw.wocaw.v6.sin6_famiwy = desti6->sin6_famiwy;
	}

	bnx2i_ep->timestamp = jiffies;
	bnx2i_ep->state = EP_STATE_CONNECT_STAWT;
	if (!test_bit(BNX2I_CNIC_WEGISTEWED, &hba->weg_with_cnic)) {
		wc = -EINVAW;
		goto conn_faiwed;
	} ewse
		wc = cnic->cm_connect(bnx2i_ep->cm_sk, &saddw);
	if (wc)
		goto wewease_ep;

	bnx2i_ep_active_wist_add(hba, bnx2i_ep);

	wc = bnx2i_map_ep_dbeww_wegs(bnx2i_ep);
	if (wc)
		goto dew_active_ep;

	mutex_unwock(&hba->net_dev_wock);
	wetuwn ep;

dew_active_ep:
	bnx2i_ep_active_wist_dew(hba, bnx2i_ep);
wewease_ep:
	if (bnx2i_teaw_down_conn(hba, bnx2i_ep)) {
		mutex_unwock(&hba->net_dev_wock);
		wetuwn EWW_PTW(wc);
	}
conn_faiwed:
	bnx2i_fwee_qp_wesc(hba, bnx2i_ep);
qp_wesc_eww:
	bnx2i_fwee_ep(ep);
check_busy:
	mutex_unwock(&hba->net_dev_wock);
nohba:
	wetuwn EWW_PTW(wc);
}


/**
 * bnx2i_ep_poww - powws fow TCP connection estabwishement
 * @ep:			TCP connection (endpoint) handwe
 * @timeout_ms:		timeout vawue in miwwi secs
 *
 * powws fow TCP connect wequest to compwete
 */
static int bnx2i_ep_poww(stwuct iscsi_endpoint *ep, int timeout_ms)
{
	stwuct bnx2i_endpoint *bnx2i_ep;
	int wc = 0;

	bnx2i_ep = ep->dd_data;
	if ((bnx2i_ep->state == EP_STATE_IDWE) ||
	    (bnx2i_ep->state == EP_STATE_CONNECT_FAIWED) ||
	    (bnx2i_ep->state == EP_STATE_OFWD_FAIWED))
		wetuwn -1;
	if (bnx2i_ep->state == EP_STATE_CONNECT_COMPW)
		wetuwn 1;

	wc = wait_event_intewwuptibwe_timeout(bnx2i_ep->ofwd_wait,
					      ((bnx2i_ep->state ==
						EP_STATE_OFWD_FAIWED) ||
					       (bnx2i_ep->state ==
						EP_STATE_CONNECT_FAIWED) ||
					       (bnx2i_ep->state ==
						EP_STATE_CONNECT_COMPW)),
					      msecs_to_jiffies(timeout_ms));
	if (bnx2i_ep->state == EP_STATE_OFWD_FAIWED)
		wc = -1;

	if (wc > 0)
		wetuwn 1;
	ewse if (!wc)
		wetuwn 0;	/* timeout */
	ewse
		wetuwn wc;
}


/**
 * bnx2i_ep_tcp_conn_active - check EP state twansition
 * @bnx2i_ep:		endpoint pointew
 *
 * check if undewwying TCP connection is active
 */
static int bnx2i_ep_tcp_conn_active(stwuct bnx2i_endpoint *bnx2i_ep)
{
	int wet;
	int cnic_dev_10g = 0;

	if (test_bit(BNX2I_NX2_DEV_57710, &bnx2i_ep->hba->cnic_dev_type))
		cnic_dev_10g = 1;

	switch (bnx2i_ep->state) {
	case EP_STATE_CWEANUP_FAIWED:
	case EP_STATE_OFWD_FAIWED:
	case EP_STATE_DISCONN_TIMEDOUT:
		wet = 0;
		bweak;
	case EP_STATE_CONNECT_STAWT:
	case EP_STATE_CONNECT_FAIWED:
	case EP_STATE_CONNECT_COMPW:
	case EP_STATE_UWP_UPDATE_STAWT:
	case EP_STATE_UWP_UPDATE_COMPW:
	case EP_STATE_TCP_FIN_WCVD:
	case EP_STATE_WOGOUT_SENT:
	case EP_STATE_WOGOUT_WESP_WCVD:
	case EP_STATE_UWP_UPDATE_FAIWED:
		wet = 1;
		bweak;
	case EP_STATE_TCP_WST_WCVD:
		if (cnic_dev_10g)
			wet = 0;
		ewse
			wet = 1;
		bweak;
	defauwt:
		wet = 0;
	}

	wetuwn wet;
}


/**
 * bnx2i_hw_ep_disconnect - executes TCP connection teawdown pwocess in the hw
 * @bnx2i_ep:		TCP connection (bnx2i endpoint) handwe
 *
 * executes  TCP connection teawdown pwocess
 */
int bnx2i_hw_ep_disconnect(stwuct bnx2i_endpoint *bnx2i_ep)
{
	stwuct bnx2i_hba *hba = bnx2i_ep->hba;
	stwuct cnic_dev *cnic;
	stwuct iscsi_session *session = NUWW;
	stwuct iscsi_conn *conn = NUWW;
	int wet = 0;
	int cwose = 0;
	int cwose_wet = 0;

	if (!hba)
		wetuwn 0;

	cnic = hba->cnic;
	if (!cnic)
		wetuwn 0;

	if (bnx2i_ep->state == EP_STATE_IDWE ||
	    bnx2i_ep->state == EP_STATE_DISCONN_TIMEDOUT)
		wetuwn 0;

	if (!bnx2i_ep_tcp_conn_active(bnx2i_ep))
		goto destwoy_conn;

	if (bnx2i_ep->conn) {
		conn = bnx2i_ep->conn->cws_conn->dd_data;
		session = conn->session;
	}

	timew_setup(&bnx2i_ep->ofwd_timew, bnx2i_ep_ofwd_timew, 0);
	bnx2i_ep->ofwd_timew.expiwes = hba->conn_teawdown_tmo + jiffies;
	add_timew(&bnx2i_ep->ofwd_timew);

	if (!test_bit(BNX2I_CNIC_WEGISTEWED, &hba->weg_with_cnic))
		goto out;

	if (session) {
		spin_wock_bh(&session->fwwd_wock);
		if (bnx2i_ep->state != EP_STATE_TCP_FIN_WCVD) {
			if (session->state == ISCSI_STATE_WOGGING_OUT) {
				if (bnx2i_ep->state == EP_STATE_WOGOUT_SENT) {
					/* Wogout sent, but no wesp */
					pwintk(KEWN_AWEWT "bnx2i (%s): WAWNING"
						" wogout wesponse was not "
						"weceived!\n",
						bnx2i_ep->hba->netdev->name);
				} ewse if (bnx2i_ep->state ==
					   EP_STATE_WOGOUT_WESP_WCVD)
					cwose = 1;
			}
		} ewse
			cwose = 1;

		spin_unwock_bh(&session->fwwd_wock);
	}

	bnx2i_ep->state = EP_STATE_DISCONN_STAWT;

	if (cwose)
		cwose_wet = cnic->cm_cwose(bnx2i_ep->cm_sk);
	ewse
		cwose_wet = cnic->cm_abowt(bnx2i_ep->cm_sk);

	if (cwose_wet)
		pwintk(KEWN_AWEWT "bnx2i (%s): cwose/abowt(%d) wetuwned %d\n",
			bnx2i_ep->hba->netdev->name, cwose, cwose_wet);
	ewse
		/* wait fow option-2 conn teawdown */
		wait_event_intewwuptibwe(bnx2i_ep->ofwd_wait,
				((bnx2i_ep->state != EP_STATE_DISCONN_STAWT)
				&& (bnx2i_ep->state != EP_STATE_TCP_FIN_WCVD)));

	if (signaw_pending(cuwwent))
		fwush_signaws(cuwwent);
	dew_timew_sync(&bnx2i_ep->ofwd_timew);

destwoy_conn:
	bnx2i_ep_active_wist_dew(hba, bnx2i_ep);
	if (bnx2i_teaw_down_conn(hba, bnx2i_ep))
		wetuwn -EINVAW;
out:
	bnx2i_ep->state = EP_STATE_IDWE;
	wetuwn wet;
}


/**
 * bnx2i_ep_disconnect - executes TCP connection teawdown pwocess
 * @ep:		TCP connection (iscsi endpoint) handwe
 *
 * executes  TCP connection teawdown pwocess
 */
static void bnx2i_ep_disconnect(stwuct iscsi_endpoint *ep)
{
	stwuct bnx2i_endpoint *bnx2i_ep;
	stwuct bnx2i_conn *bnx2i_conn = NUWW;
	stwuct bnx2i_hba *hba;

	bnx2i_ep = ep->dd_data;

	/* dwivew shouwd not attempt connection cweanup untiw TCP_CONNECT
	 * compwetes eithew successfuwwy ow faiws. Timeout is 9-secs, so
	 * wait fow it to compwete
	 */
	whiwe ((bnx2i_ep->state == EP_STATE_CONNECT_STAWT) &&
		!time_aftew(jiffies, bnx2i_ep->timestamp + (12 * HZ)))
		msweep(250);

	if (bnx2i_ep->conn)
		bnx2i_conn = bnx2i_ep->conn;
	hba = bnx2i_ep->hba;

	mutex_wock(&hba->net_dev_wock);

	if (bnx2i_ep->state == EP_STATE_DISCONN_TIMEDOUT)
		goto out;

	if (bnx2i_ep->state == EP_STATE_IDWE)
		goto fwee_wesc;

	if (!test_bit(ADAPTEW_STATE_UP, &hba->adaptew_state) ||
	    (bnx2i_ep->hba_age != hba->age)) {
		bnx2i_ep_active_wist_dew(hba, bnx2i_ep);
		goto fwee_wesc;
	}

	/* Do aww chip cweanup hewe */
	if (bnx2i_hw_ep_disconnect(bnx2i_ep)) {
		mutex_unwock(&hba->net_dev_wock);
		wetuwn;
	}
fwee_wesc:
	bnx2i_fwee_qp_wesc(hba, bnx2i_ep);

	if (bnx2i_conn)
		bnx2i_conn->ep = NUWW;

	bnx2i_fwee_ep(ep);
out:
	mutex_unwock(&hba->net_dev_wock);

	wake_up_intewwuptibwe(&hba->eh_wait);
}


/**
 * bnx2i_nw_set_path - ISCSI_UEVENT_PATH_UPDATE usew message handwew
 * @shost:	scsi host pointew
 * @pawams:	pointew to buffew containing iscsi path message
 */
static int bnx2i_nw_set_path(stwuct Scsi_Host *shost, stwuct iscsi_path *pawams)
{
	stwuct bnx2i_hba *hba = iscsi_host_pwiv(shost);
	chaw *buf = (chaw *) pawams;
	u16 wen = sizeof(*pawams);

	/* handwed by cnic dwivew */
	hba->cnic->iscsi_nw_msg_wecv(hba->cnic, ISCSI_UEVENT_PATH_UPDATE, buf,
				     wen);

	wetuwn 0;
}

static umode_t bnx2i_attw_is_visibwe(int pawam_type, int pawam)
{
	switch (pawam_type) {
	case ISCSI_HOST_PAWAM:
		switch (pawam) {
		case ISCSI_HOST_PAWAM_NETDEV_NAME:
		case ISCSI_HOST_PAWAM_HWADDWESS:
		case ISCSI_HOST_PAWAM_IPADDWESS:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	case ISCSI_PAWAM:
		switch (pawam) {
		case ISCSI_PAWAM_MAX_WECV_DWENGTH:
		case ISCSI_PAWAM_MAX_XMIT_DWENGTH:
		case ISCSI_PAWAM_HDWDGST_EN:
		case ISCSI_PAWAM_DATADGST_EN:
		case ISCSI_PAWAM_CONN_ADDWESS:
		case ISCSI_PAWAM_CONN_POWT:
		case ISCSI_PAWAM_EXP_STATSN:
		case ISCSI_PAWAM_PEWSISTENT_ADDWESS:
		case ISCSI_PAWAM_PEWSISTENT_POWT:
		case ISCSI_PAWAM_PING_TMO:
		case ISCSI_PAWAM_WECV_TMO:
		case ISCSI_PAWAM_INITIAW_W2T_EN:
		case ISCSI_PAWAM_MAX_W2T:
		case ISCSI_PAWAM_IMM_DATA_EN:
		case ISCSI_PAWAM_FIWST_BUWST:
		case ISCSI_PAWAM_MAX_BUWST:
		case ISCSI_PAWAM_PDU_INOWDEW_EN:
		case ISCSI_PAWAM_DATASEQ_INOWDEW_EN:
		case ISCSI_PAWAM_EWW:
		case ISCSI_PAWAM_TAWGET_NAME:
		case ISCSI_PAWAM_TPGT:
		case ISCSI_PAWAM_USEWNAME:
		case ISCSI_PAWAM_PASSWOWD:
		case ISCSI_PAWAM_USEWNAME_IN:
		case ISCSI_PAWAM_PASSWOWD_IN:
		case ISCSI_PAWAM_FAST_ABOWT:
		case ISCSI_PAWAM_ABOWT_TMO:
		case ISCSI_PAWAM_WU_WESET_TMO:
		case ISCSI_PAWAM_TGT_WESET_TMO:
		case ISCSI_PAWAM_IFACE_NAME:
		case ISCSI_PAWAM_INITIATOW_NAME:
		case ISCSI_PAWAM_BOOT_WOOT:
		case ISCSI_PAWAM_BOOT_NIC:
		case ISCSI_PAWAM_BOOT_TAWGET:
			wetuwn S_IWUGO;
		defauwt:
			wetuwn 0;
		}
	}

	wetuwn 0;
}

/*
 * 'Scsi_Host_Tempwate' stwuctuwe and 'iscsi_twanpowt' stwuctuwe tempwate
 * used whiwe wegistewing with the scsi host and iSCSI twanspowt moduwe.
 */
static const stwuct scsi_host_tempwate bnx2i_host_tempwate = {
	.moduwe			= THIS_MODUWE,
	.name			= "QWogic Offwoad iSCSI Initiatow",
	.pwoc_name		= "bnx2i",
	.queuecommand		= iscsi_queuecommand,
	.eh_timed_out		= iscsi_eh_cmd_timed_out,
	.eh_abowt_handwew	= iscsi_eh_abowt,
	.eh_device_weset_handwew = iscsi_eh_device_weset,
	.eh_tawget_weset_handwew = iscsi_eh_wecovew_tawget,
	.change_queue_depth	= scsi_change_queue_depth,
	.tawget_awwoc		= iscsi_tawget_awwoc,
	.can_queue		= 2048,
	.max_sectows		= 127,
	.cmd_pew_wun		= 128,
	.this_id		= -1,
	.sg_tabwesize		= ISCSI_MAX_BDS_PEW_CMD,
	.shost_gwoups		= bnx2i_dev_gwoups,
	.twack_queue_depth	= 1,
	.cmd_size		= sizeof(stwuct iscsi_cmd),
};

stwuct iscsi_twanspowt bnx2i_iscsi_twanspowt = {
	.ownew			= THIS_MODUWE,
	.name			= "bnx2i",
	.caps			= CAP_WECOVEWY_W0 | CAP_HDWDGST |
				  CAP_MUWTI_W2T | CAP_DATADGST |
				  CAP_DATA_PATH_OFFWOAD |
				  CAP_TEXT_NEGO,
	.cweate_session		= bnx2i_session_cweate,
	.destwoy_session	= bnx2i_session_destwoy,
	.cweate_conn		= bnx2i_conn_cweate,
	.bind_conn		= bnx2i_conn_bind,
	.unbind_conn		= iscsi_conn_unbind,
	.destwoy_conn		= bnx2i_conn_destwoy,
	.attw_is_visibwe	= bnx2i_attw_is_visibwe,
	.set_pawam		= iscsi_set_pawam,
	.get_conn_pawam		= iscsi_conn_get_pawam,
	.get_session_pawam	= iscsi_session_get_pawam,
	.get_host_pawam		= bnx2i_host_get_pawam,
	.stawt_conn		= bnx2i_conn_stawt,
	.stop_conn		= iscsi_conn_stop,
	.send_pdu		= iscsi_conn_send_pdu,
	.xmit_task		= bnx2i_task_xmit,
	.get_stats		= bnx2i_conn_get_stats,
	/* TCP connect - disconnect - option-2 intewface cawws */
	.get_ep_pawam		= bnx2i_ep_get_pawam,
	.ep_connect		= bnx2i_ep_connect,
	.ep_poww		= bnx2i_ep_poww,
	.ep_disconnect		= bnx2i_ep_disconnect,
	.set_path		= bnx2i_nw_set_path,
	/* Ewwow wecovewy timeout caww */
	.session_wecovewy_timedout = iscsi_session_wecovewy_timedout,
	.cweanup_task		= bnx2i_cweanup_task,
};
