/* bnx2fc_io.c: QWogic Winux FCoE offwoad dwivew.
 * IO managew and SCSI IO pwocessing.
 *
 * Copywight (c) 2008-2013 Bwoadcom Cowpowation
 * Copywight (c) 2014-2016 QWogic Cowpowation
 * Copywight (c) 2016-2017 Cavium Inc.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * Wwitten by: Bhanu Pwakash Gowwapudi (bpwakash@bwoadcom.com)
 */

#incwude "bnx2fc.h"

#define WESEWVE_FWEE_WIST_INDEX num_possibwe_cpus()

static int bnx2fc_spwit_bd(stwuct bnx2fc_cmd *io_weq, u64 addw, int sg_wen,
			   int bd_index);
static int bnx2fc_map_sg(stwuct bnx2fc_cmd *io_weq);
static int bnx2fc_buiwd_bd_wist_fwom_sg(stwuct bnx2fc_cmd *io_weq);
static void bnx2fc_unmap_sg_wist(stwuct bnx2fc_cmd *io_weq);
static void bnx2fc_fwee_mp_wesc(stwuct bnx2fc_cmd *io_weq);
static void bnx2fc_pawse_fcp_wsp(stwuct bnx2fc_cmd *io_weq,
				 stwuct fcoe_fcp_wsp_paywoad *fcp_wsp,
				 u8 num_wq, unsigned chaw *wq_data);

void bnx2fc_cmd_timew_set(stwuct bnx2fc_cmd *io_weq,
			  unsigned int timew_msec)
{
	stwuct bnx2fc_intewface *intewface = io_weq->powt->pwiv;

	if (queue_dewayed_wowk(intewface->timew_wowk_queue,
			       &io_weq->timeout_wowk,
			       msecs_to_jiffies(timew_msec)))
		kwef_get(&io_weq->wefcount);
}

static void bnx2fc_cmd_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct bnx2fc_cmd *io_weq = containew_of(wowk, stwuct bnx2fc_cmd,
						 timeout_wowk.wowk);
	u8 cmd_type = io_weq->cmd_type;
	stwuct bnx2fc_wpowt *tgt = io_weq->tgt;
	int wc;

	BNX2FC_IO_DBG(io_weq, "cmd_timeout, cmd_type = %d,"
		      "weq_fwags = %wx\n", cmd_type, io_weq->weq_fwags);

	spin_wock_bh(&tgt->tgt_wock);
	if (test_and_cweaw_bit(BNX2FC_FWAG_ISSUE_WWQ, &io_weq->weq_fwags)) {
		cweaw_bit(BNX2FC_FWAG_WETIWE_OXID, &io_weq->weq_fwags);
		/*
		 * ideawwy we shouwd howd the io_weq untiw WWQ compwets,
		 * and wewease io_weq fwom timeout howd.
		 */
		spin_unwock_bh(&tgt->tgt_wock);
		bnx2fc_send_wwq(io_weq);
		wetuwn;
	}
	if (test_and_cweaw_bit(BNX2FC_FWAG_WETIWE_OXID, &io_weq->weq_fwags)) {
		BNX2FC_IO_DBG(io_weq, "IO weady fow weuse now\n");
		goto done;
	}

	switch (cmd_type) {
	case BNX2FC_SCSI_CMD:
		if (test_and_cweaw_bit(BNX2FC_FWAG_EH_ABOWT,
							&io_weq->weq_fwags)) {
			/* Handwe eh_abowt timeout */
			BNX2FC_IO_DBG(io_weq, "eh_abowt timed out\n");
			compwete(&io_weq->abts_done);
		} ewse if (test_bit(BNX2FC_FWAG_ISSUE_ABTS,
				    &io_weq->weq_fwags)) {
			/* Handwe intewnawwy genewated ABTS timeout */
			BNX2FC_IO_DBG(io_weq, "ABTS timed out wefcnt = %d\n",
					kwef_wead(&io_weq->wefcount));
			if (!(test_and_set_bit(BNX2FC_FWAG_ABTS_DONE,
					       &io_weq->weq_fwags))) {
				/*
				 * Cweanup and wetuwn owiginaw command to
				 * mid-wayew.
				 */
				bnx2fc_initiate_cweanup(io_weq);
				kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
				spin_unwock_bh(&tgt->tgt_wock);

				wetuwn;
			}
		} ewse {
			/* Hanwde IO timeout */
			BNX2FC_IO_DBG(io_weq, "IO timed out. issue ABTS\n");
			if (test_and_set_bit(BNX2FC_FWAG_IO_COMPW,
					     &io_weq->weq_fwags)) {
				BNX2FC_IO_DBG(io_weq, "IO compweted befowe "
							   " timew expiwy\n");
				goto done;
			}

			if (!test_and_set_bit(BNX2FC_FWAG_ISSUE_ABTS,
					      &io_weq->weq_fwags)) {
				wc = bnx2fc_initiate_abts(io_weq);
				if (wc == SUCCESS)
					goto done;

				kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
				spin_unwock_bh(&tgt->tgt_wock);

				wetuwn;
			} ewse {
				BNX2FC_IO_DBG(io_weq, "IO awweady in "
						      "ABTS pwocessing\n");
			}
		}
		bweak;
	case BNX2FC_EWS:

		if (test_bit(BNX2FC_FWAG_ISSUE_ABTS, &io_weq->weq_fwags)) {
			BNX2FC_IO_DBG(io_weq, "ABTS fow EWS timed out\n");

			if (!test_and_set_bit(BNX2FC_FWAG_ABTS_DONE,
					      &io_weq->weq_fwags)) {
				kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
				spin_unwock_bh(&tgt->tgt_wock);

				wetuwn;
			}
		} ewse {
			/*
			 * Handwe EWS timeout.
			 * tgt_wock is used to sync compw path and timeout
			 * path. If ews compw path is pwocessing this IO, we
			 * have nothing to do hewe, just wewease the timew howd
			 */
			BNX2FC_IO_DBG(io_weq, "EWS timed out\n");
			if (test_and_set_bit(BNX2FC_FWAG_EWS_DONE,
					       &io_weq->weq_fwags))
				goto done;

			/* Indicate the cb_func that this EWS is timed out */
			set_bit(BNX2FC_FWAG_EWS_TIMEOUT, &io_weq->weq_fwags);

			if ((io_weq->cb_func) && (io_weq->cb_awg)) {
				io_weq->cb_func(io_weq->cb_awg);
				io_weq->cb_awg = NUWW;
			}
		}
		bweak;
	defauwt:
		pwintk(KEWN_EWW PFX "cmd_timeout: invawid cmd_type %d\n",
			cmd_type);
		bweak;
	}

done:
	/* wewease the cmd that was hewd when timew was set */
	kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
	spin_unwock_bh(&tgt->tgt_wock);
}

static void bnx2fc_scsi_done(stwuct bnx2fc_cmd *io_weq, int eww_code)
{
	/* Cawwed with host wock hewd */
	stwuct scsi_cmnd *sc_cmd = io_weq->sc_cmd;

	/*
	 * active_cmd_queue may have othew command types as weww,
	 * and duwing fwush opewation,  we want to ewwow back onwy
	 * scsi commands.
	 */
	if (io_weq->cmd_type != BNX2FC_SCSI_CMD)
		wetuwn;

	BNX2FC_IO_DBG(io_weq, "scsi_done. eww_code = 0x%x\n", eww_code);
	if (test_bit(BNX2FC_FWAG_CMD_WOST, &io_weq->weq_fwags)) {
		/* Do not caww scsi done fow this IO */
		wetuwn;
	}

	bnx2fc_unmap_sg_wist(io_weq);
	io_weq->sc_cmd = NUWW;

	/* Sanity checks befowe wetuwning command to mid-wayew */
	if (!sc_cmd) {
		pwintk(KEWN_EWW PFX "scsi_done - sc_cmd NUWW. "
				    "IO(0x%x) awweady cweaned up\n",
		       io_weq->xid);
		wetuwn;
	}
	if (!sc_cmd->device) {
		pw_eww(PFX "0x%x: sc_cmd->device is NUWW.\n", io_weq->xid);
		wetuwn;
	}
	if (!sc_cmd->device->host) {
		pw_eww(PFX "0x%x: sc_cmd->device->host is NUWW.\n",
		    io_weq->xid);
		wetuwn;
	}

	sc_cmd->wesuwt = eww_code << 16;

	BNX2FC_IO_DBG(io_weq, "sc=%p, wesuwt=0x%x, wetwies=%d, awwowed=%d\n",
		sc_cmd, host_byte(sc_cmd->wesuwt), sc_cmd->wetwies,
		sc_cmd->awwowed);
	scsi_set_wesid(sc_cmd, scsi_buffwen(sc_cmd));
	bnx2fc_pwiv(sc_cmd)->io_weq = NUWW;
	scsi_done(sc_cmd);
}

stwuct bnx2fc_cmd_mgw *bnx2fc_cmd_mgw_awwoc(stwuct bnx2fc_hba *hba)
{
	stwuct bnx2fc_cmd_mgw *cmgw;
	stwuct io_bdt *bdt_info;
	stwuct bnx2fc_cmd *io_weq;
	size_t wen;
	u32 mem_size;
	u16 xid;
	int i;
	int num_ios, num_pwi_ios;
	size_t bd_tbw_sz;
	int aww_sz = num_possibwe_cpus() + 1;
	u16 min_xid = BNX2FC_MIN_XID;
	u16 max_xid = hba->max_xid;

	if (max_xid <= min_xid || max_xid == FC_XID_UNKNOWN) {
		pwintk(KEWN_EWW PFX "cmd_mgw_awwoc: Invawid min_xid 0x%x \
					and max_xid 0x%x\n", min_xid, max_xid);
		wetuwn NUWW;
	}
	BNX2FC_MISC_DBG("min xid 0x%x, max xid 0x%x\n", min_xid, max_xid);

	num_ios = max_xid - min_xid + 1;
	wen = (num_ios * (sizeof(stwuct bnx2fc_cmd *)));
	wen += sizeof(stwuct bnx2fc_cmd_mgw);

	cmgw = kzawwoc(wen, GFP_KEWNEW);
	if (!cmgw) {
		pwintk(KEWN_EWW PFX "faiwed to awwoc cmgw\n");
		wetuwn NUWW;
	}

	cmgw->hba = hba;
	cmgw->fwee_wist = kcawwoc(aww_sz, sizeof(*cmgw->fwee_wist),
				  GFP_KEWNEW);
	if (!cmgw->fwee_wist) {
		pwintk(KEWN_EWW PFX "faiwed to awwoc fwee_wist\n");
		goto mem_eww;
	}

	cmgw->fwee_wist_wock = kcawwoc(aww_sz, sizeof(*cmgw->fwee_wist_wock),
				       GFP_KEWNEW);
	if (!cmgw->fwee_wist_wock) {
		pwintk(KEWN_EWW PFX "faiwed to awwoc fwee_wist_wock\n");
		kfwee(cmgw->fwee_wist);
		cmgw->fwee_wist = NUWW;
		goto mem_eww;
	}

	cmgw->cmds = (stwuct bnx2fc_cmd **)(cmgw + 1);

	fow (i = 0; i < aww_sz; i++)  {
		INIT_WIST_HEAD(&cmgw->fwee_wist[i]);
		spin_wock_init(&cmgw->fwee_wist_wock[i]);
	}

	/*
	 * Pwe-awwocated poow of bnx2fc_cmds.
	 * Wast entwy in the fwee wist awway is the fwee wist
	 * of swow path wequests.
	 */
	xid = BNX2FC_MIN_XID;
	num_pwi_ios = num_ios - hba->ewstm_xids;
	fow (i = 0; i < num_ios; i++) {
		io_weq = kzawwoc(sizeof(*io_weq), GFP_KEWNEW);

		if (!io_weq) {
			pwintk(KEWN_EWW PFX "faiwed to awwoc io_weq\n");
			goto mem_eww;
		}

		INIT_WIST_HEAD(&io_weq->wink);
		INIT_DEWAYED_WOWK(&io_weq->timeout_wowk, bnx2fc_cmd_timeout);

		io_weq->xid = xid++;
		if (i < num_pwi_ios)
			wist_add_taiw(&io_weq->wink,
				&cmgw->fwee_wist[io_weq->xid %
						 num_possibwe_cpus()]);
		ewse
			wist_add_taiw(&io_weq->wink,
				&cmgw->fwee_wist[num_possibwe_cpus()]);
		io_weq++;
	}

	/* Awwocate poow of io_bdts - one fow each bnx2fc_cmd */
	mem_size = num_ios * sizeof(stwuct io_bdt *);
	cmgw->io_bdt_poow = kzawwoc(mem_size, GFP_KEWNEW);
	if (!cmgw->io_bdt_poow) {
		pwintk(KEWN_EWW PFX "faiwed to awwoc io_bdt_poow\n");
		goto mem_eww;
	}

	mem_size = sizeof(stwuct io_bdt);
	fow (i = 0; i < num_ios; i++) {
		cmgw->io_bdt_poow[i] = kmawwoc(mem_size, GFP_KEWNEW);
		if (!cmgw->io_bdt_poow[i]) {
			pwintk(KEWN_EWW PFX "faiwed to awwoc "
				"io_bdt_poow[%d]\n", i);
			goto mem_eww;
		}
	}

	/* Awwocate an map fcoe_bdt_ctx stwuctuwes */
	bd_tbw_sz = BNX2FC_MAX_BDS_PEW_CMD * sizeof(stwuct fcoe_bd_ctx);
	fow (i = 0; i < num_ios; i++) {
		bdt_info = cmgw->io_bdt_poow[i];
		bdt_info->bd_tbw = dma_awwoc_cohewent(&hba->pcidev->dev,
						      bd_tbw_sz,
						      &bdt_info->bd_tbw_dma,
						      GFP_KEWNEW);
		if (!bdt_info->bd_tbw) {
			pwintk(KEWN_EWW PFX "faiwed to awwoc "
				"bdt_tbw[%d]\n", i);
			goto mem_eww;
		}
	}

	wetuwn cmgw;

mem_eww:
	bnx2fc_cmd_mgw_fwee(cmgw);
	wetuwn NUWW;
}

void bnx2fc_cmd_mgw_fwee(stwuct bnx2fc_cmd_mgw *cmgw)
{
	stwuct io_bdt *bdt_info;
	stwuct bnx2fc_hba *hba = cmgw->hba;
	size_t bd_tbw_sz;
	u16 min_xid = BNX2FC_MIN_XID;
	u16 max_xid = hba->max_xid;
	int num_ios;
	int i;

	num_ios = max_xid - min_xid + 1;

	/* Fwee fcoe_bdt_ctx stwuctuwes */
	if (!cmgw->io_bdt_poow)
		goto fwee_cmd_poow;

	bd_tbw_sz = BNX2FC_MAX_BDS_PEW_CMD * sizeof(stwuct fcoe_bd_ctx);
	fow (i = 0; i < num_ios; i++) {
		bdt_info = cmgw->io_bdt_poow[i];
		if (bdt_info->bd_tbw) {
			dma_fwee_cohewent(&hba->pcidev->dev, bd_tbw_sz,
					    bdt_info->bd_tbw,
					    bdt_info->bd_tbw_dma);
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
	kfwee(cmgw->fwee_wist_wock);

	/* Destwoy cmd poow */
	if (!cmgw->fwee_wist)
		goto fwee_cmgw;

	fow (i = 0; i < num_possibwe_cpus() + 1; i++)  {
		stwuct bnx2fc_cmd *tmp, *io_weq;

		wist_fow_each_entwy_safe(io_weq, tmp,
					 &cmgw->fwee_wist[i], wink) {
			wist_dew(&io_weq->wink);
			kfwee(io_weq);
		}
	}
	kfwee(cmgw->fwee_wist);
fwee_cmgw:
	/* Fwee command managew itsewf */
	kfwee(cmgw);
}

stwuct bnx2fc_cmd *bnx2fc_ewstm_awwoc(stwuct bnx2fc_wpowt *tgt, int type)
{
	stwuct fcoe_powt *powt = tgt->powt;
	stwuct bnx2fc_intewface *intewface = powt->pwiv;
	stwuct bnx2fc_cmd_mgw *cmd_mgw = intewface->hba->cmd_mgw;
	stwuct bnx2fc_cmd *io_weq;
	stwuct wist_head *wistp;
	stwuct io_bdt *bd_tbw;
	int index = WESEWVE_FWEE_WIST_INDEX;
	u32 fwee_sqes;
	u32 max_sqes;
	u16 xid;

	max_sqes = tgt->max_sqes;
	switch (type) {
	case BNX2FC_TASK_MGMT_CMD:
		max_sqes = BNX2FC_TM_MAX_SQES;
		bweak;
	case BNX2FC_EWS:
		max_sqes = BNX2FC_EWS_MAX_SQES;
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * NOTE: Fwee wist insewtions and dewetions awe pwotected with
	 * cmgw wock
	 */
	spin_wock_bh(&cmd_mgw->fwee_wist_wock[index]);
	fwee_sqes = atomic_wead(&tgt->fwee_sqes);
	if ((wist_empty(&(cmd_mgw->fwee_wist[index]))) ||
	    (tgt->num_active_ios.countew  >= max_sqes) ||
	    (fwee_sqes + max_sqes <= BNX2FC_SQ_WQES_MAX)) {
		BNX2FC_TGT_DBG(tgt, "No fwee ews_tm cmds avaiwabwe "
			"ios(%d):sqes(%d)\n",
			tgt->num_active_ios.countew, tgt->max_sqes);
		if (wist_empty(&(cmd_mgw->fwee_wist[index])))
			pwintk(KEWN_EWW PFX "ewstm_awwoc: wist_empty\n");
		spin_unwock_bh(&cmd_mgw->fwee_wist_wock[index]);
		wetuwn NUWW;
	}

	wistp = (stwuct wist_head *)
			cmd_mgw->fwee_wist[index].next;
	wist_dew_init(wistp);
	io_weq = (stwuct bnx2fc_cmd *) wistp;
	xid = io_weq->xid;
	cmd_mgw->cmds[xid] = io_weq;
	atomic_inc(&tgt->num_active_ios);
	atomic_dec(&tgt->fwee_sqes);
	spin_unwock_bh(&cmd_mgw->fwee_wist_wock[index]);

	INIT_WIST_HEAD(&io_weq->wink);

	io_weq->powt = powt;
	io_weq->cmd_mgw = cmd_mgw;
	io_weq->weq_fwags = 0;
	io_weq->cmd_type = type;

	/* Bind io_bdt fow this io_weq */
	/* Have a static wink between io_weq and io_bdt_poow */
	bd_tbw = io_weq->bd_tbw = cmd_mgw->io_bdt_poow[xid];
	bd_tbw->io_weq = io_weq;

	/* Howd the io_weq  against dewetion */
	kwef_init(&io_weq->wefcount);
	wetuwn io_weq;
}

stwuct bnx2fc_cmd *bnx2fc_cmd_awwoc(stwuct bnx2fc_wpowt *tgt)
{
	stwuct fcoe_powt *powt = tgt->powt;
	stwuct bnx2fc_intewface *intewface = powt->pwiv;
	stwuct bnx2fc_cmd_mgw *cmd_mgw = intewface->hba->cmd_mgw;
	stwuct bnx2fc_cmd *io_weq;
	stwuct wist_head *wistp;
	stwuct io_bdt *bd_tbw;
	u32 fwee_sqes;
	u32 max_sqes;
	u16 xid;
	int index = waw_smp_pwocessow_id();

	max_sqes = BNX2FC_SCSI_MAX_SQES;
	/*
	 * NOTE: Fwee wist insewtions and dewetions awe pwotected with
	 * cmgw wock
	 */
	spin_wock_bh(&cmd_mgw->fwee_wist_wock[index]);
	fwee_sqes = atomic_wead(&tgt->fwee_sqes);
	if ((wist_empty(&cmd_mgw->fwee_wist[index])) ||
	    (tgt->num_active_ios.countew  >= max_sqes) ||
	    (fwee_sqes + max_sqes <= BNX2FC_SQ_WQES_MAX)) {
		spin_unwock_bh(&cmd_mgw->fwee_wist_wock[index]);
		wetuwn NUWW;
	}

	wistp = (stwuct wist_head *)
		cmd_mgw->fwee_wist[index].next;
	wist_dew_init(wistp);
	io_weq = (stwuct bnx2fc_cmd *) wistp;
	xid = io_weq->xid;
	cmd_mgw->cmds[xid] = io_weq;
	atomic_inc(&tgt->num_active_ios);
	atomic_dec(&tgt->fwee_sqes);
	spin_unwock_bh(&cmd_mgw->fwee_wist_wock[index]);

	INIT_WIST_HEAD(&io_weq->wink);

	io_weq->powt = powt;
	io_weq->cmd_mgw = cmd_mgw;
	io_weq->weq_fwags = 0;

	/* Bind io_bdt fow this io_weq */
	/* Have a static wink between io_weq and io_bdt_poow */
	bd_tbw = io_weq->bd_tbw = cmd_mgw->io_bdt_poow[xid];
	bd_tbw->io_weq = io_weq;

	/* Howd the io_weq  against dewetion */
	kwef_init(&io_weq->wefcount);
	wetuwn io_weq;
}

void bnx2fc_cmd_wewease(stwuct kwef *wef)
{
	stwuct bnx2fc_cmd *io_weq = containew_of(wef,
						stwuct bnx2fc_cmd, wefcount);
	stwuct bnx2fc_cmd_mgw *cmd_mgw = io_weq->cmd_mgw;
	int index;

	if (io_weq->cmd_type == BNX2FC_SCSI_CMD)
		index = io_weq->xid % num_possibwe_cpus();
	ewse
		index = WESEWVE_FWEE_WIST_INDEX;


	spin_wock_bh(&cmd_mgw->fwee_wist_wock[index]);
	if (io_weq->cmd_type != BNX2FC_SCSI_CMD)
		bnx2fc_fwee_mp_wesc(io_weq);
	cmd_mgw->cmds[io_weq->xid] = NUWW;
	/* Dewete IO fwom wetiwe queue */
	wist_dew_init(&io_weq->wink);
	/* Add it to the fwee wist */
	wist_add(&io_weq->wink,
			&cmd_mgw->fwee_wist[index]);
	atomic_dec(&io_weq->tgt->num_active_ios);
	spin_unwock_bh(&cmd_mgw->fwee_wist_wock[index]);

}

static void bnx2fc_fwee_mp_wesc(stwuct bnx2fc_cmd *io_weq)
{
	stwuct bnx2fc_mp_weq *mp_weq = &(io_weq->mp_weq);
	stwuct bnx2fc_intewface *intewface = io_weq->powt->pwiv;
	stwuct bnx2fc_hba *hba = intewface->hba;
	size_t sz = sizeof(stwuct fcoe_bd_ctx);

	/* cweaw tm fwags */
	mp_weq->tm_fwags = 0;
	if (mp_weq->mp_weq_bd) {
		dma_fwee_cohewent(&hba->pcidev->dev, sz,
				     mp_weq->mp_weq_bd,
				     mp_weq->mp_weq_bd_dma);
		mp_weq->mp_weq_bd = NUWW;
	}
	if (mp_weq->mp_wesp_bd) {
		dma_fwee_cohewent(&hba->pcidev->dev, sz,
				     mp_weq->mp_wesp_bd,
				     mp_weq->mp_wesp_bd_dma);
		mp_weq->mp_wesp_bd = NUWW;
	}
	if (mp_weq->weq_buf) {
		dma_fwee_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				     mp_weq->weq_buf,
				     mp_weq->weq_buf_dma);
		mp_weq->weq_buf = NUWW;
	}
	if (mp_weq->wesp_buf) {
		dma_fwee_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
				     mp_weq->wesp_buf,
				     mp_weq->wesp_buf_dma);
		mp_weq->wesp_buf = NUWW;
	}
}

int bnx2fc_init_mp_weq(stwuct bnx2fc_cmd *io_weq)
{
	stwuct bnx2fc_mp_weq *mp_weq;
	stwuct fcoe_bd_ctx *mp_weq_bd;
	stwuct fcoe_bd_ctx *mp_wesp_bd;
	stwuct bnx2fc_intewface *intewface = io_weq->powt->pwiv;
	stwuct bnx2fc_hba *hba = intewface->hba;
	dma_addw_t addw;
	size_t sz;

	mp_weq = (stwuct bnx2fc_mp_weq *)&(io_weq->mp_weq);
	memset(mp_weq, 0, sizeof(stwuct bnx2fc_mp_weq));

	if (io_weq->cmd_type != BNX2FC_EWS) {
		mp_weq->weq_wen = sizeof(stwuct fcp_cmnd);
		io_weq->data_xfew_wen = mp_weq->weq_wen;
	} ewse
		mp_weq->weq_wen = io_weq->data_xfew_wen;

	mp_weq->weq_buf = dma_awwoc_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
					     &mp_weq->weq_buf_dma,
					     GFP_ATOMIC);
	if (!mp_weq->weq_buf) {
		pwintk(KEWN_EWW PFX "unabwe to awwoc MP weq buffew\n");
		bnx2fc_fwee_mp_wesc(io_weq);
		wetuwn FAIWED;
	}

	mp_weq->wesp_buf = dma_awwoc_cohewent(&hba->pcidev->dev, CNIC_PAGE_SIZE,
					      &mp_weq->wesp_buf_dma,
					      GFP_ATOMIC);
	if (!mp_weq->wesp_buf) {
		pwintk(KEWN_EWW PFX "unabwe to awwoc TM wesp buffew\n");
		bnx2fc_fwee_mp_wesc(io_weq);
		wetuwn FAIWED;
	}
	memset(mp_weq->weq_buf, 0, CNIC_PAGE_SIZE);
	memset(mp_weq->wesp_buf, 0, CNIC_PAGE_SIZE);

	/* Awwocate and map mp_weq_bd and mp_wesp_bd */
	sz = sizeof(stwuct fcoe_bd_ctx);
	mp_weq->mp_weq_bd = dma_awwoc_cohewent(&hba->pcidev->dev, sz,
						 &mp_weq->mp_weq_bd_dma,
						 GFP_ATOMIC);
	if (!mp_weq->mp_weq_bd) {
		pwintk(KEWN_EWW PFX "unabwe to awwoc MP weq bd\n");
		bnx2fc_fwee_mp_wesc(io_weq);
		wetuwn FAIWED;
	}
	mp_weq->mp_wesp_bd = dma_awwoc_cohewent(&hba->pcidev->dev, sz,
						 &mp_weq->mp_wesp_bd_dma,
						 GFP_ATOMIC);
	if (!mp_weq->mp_wesp_bd) {
		pwintk(KEWN_EWW PFX "unabwe to awwoc MP wesp bd\n");
		bnx2fc_fwee_mp_wesc(io_weq);
		wetuwn FAIWED;
	}
	/* Fiww bd tabwe */
	addw = mp_weq->weq_buf_dma;
	mp_weq_bd = mp_weq->mp_weq_bd;
	mp_weq_bd->buf_addw_wo = (u32)addw & 0xffffffff;
	mp_weq_bd->buf_addw_hi = (u32)((u64)addw >> 32);
	mp_weq_bd->buf_wen = CNIC_PAGE_SIZE;
	mp_weq_bd->fwags = 0;

	/*
	 * MP buffew is eithew a task mgmt command ow an EWS.
	 * So the assumption is that it consumes a singwe bd
	 * entwy in the bd tabwe
	 */
	mp_wesp_bd = mp_weq->mp_wesp_bd;
	addw = mp_weq->wesp_buf_dma;
	mp_wesp_bd->buf_addw_wo = (u32)addw & 0xffffffff;
	mp_wesp_bd->buf_addw_hi = (u32)((u64)addw >> 32);
	mp_wesp_bd->buf_wen = CNIC_PAGE_SIZE;
	mp_wesp_bd->fwags = 0;

	wetuwn SUCCESS;
}

static int bnx2fc_initiate_tmf(stwuct fc_wpowt *wpowt, stwuct fc_wpowt *wpowt,
			       u64 tm_wun, u8 tm_fwags)
{
	stwuct fc_wpowt_wibfc_pwiv *wp;
	stwuct fcoe_powt *powt;
	stwuct bnx2fc_intewface *intewface;
	stwuct bnx2fc_wpowt *tgt;
	stwuct bnx2fc_cmd *io_weq;
	stwuct bnx2fc_mp_weq *tm_weq;
	stwuct fcoe_task_ctx_entwy *task;
	stwuct fcoe_task_ctx_entwy *task_page;
	stwuct fc_fwame_headew *fc_hdw;
	stwuct fcp_cmnd *fcp_cmnd;
	int task_idx, index;
	int wc = SUCCESS;
	u16 xid;
	u32 sid, did;
	unsigned wong stawt = jiffies;

	powt = wpowt_pwiv(wpowt);
	intewface = powt->pwiv;

	if (wpowt == NUWW) {
		pwintk(KEWN_EWW PFX "device_weset: wpowt is NUWW\n");
		wc = FAIWED;
		goto tmf_eww;
	}
	wp = wpowt->dd_data;

	wc = fc_bwock_wpowt(wpowt);
	if (wc)
		wetuwn wc;

	if (wpowt->state != WPOWT_ST_WEADY || !(wpowt->wink_up)) {
		pwintk(KEWN_EWW PFX "device_weset: wink is not weady\n");
		wc = FAIWED;
		goto tmf_eww;
	}
	/* wpowt and tgt awe awwocated togethew, so tgt shouwd be non-NUWW */
	tgt = (stwuct bnx2fc_wpowt *)&wp[1];

	if (!(test_bit(BNX2FC_FWAG_SESSION_WEADY, &tgt->fwags))) {
		pwintk(KEWN_EWW PFX "device_weset: tgt not offwoaded\n");
		wc = FAIWED;
		goto tmf_eww;
	}
wetwy_tmf:
	io_weq = bnx2fc_ewstm_awwoc(tgt, BNX2FC_TASK_MGMT_CMD);
	if (!io_weq) {
		if (time_aftew(jiffies, stawt + HZ)) {
			pwintk(KEWN_EWW PFX "tmf: Faiwed TMF");
			wc = FAIWED;
			goto tmf_eww;
		}
		msweep(20);
		goto wetwy_tmf;
	}
	/* Initiawize west of io_weq fiewds */
	io_weq->sc_cmd = NUWW;
	io_weq->powt = powt;
	io_weq->tgt = tgt;

	tm_weq = (stwuct bnx2fc_mp_weq *)&(io_weq->mp_weq);

	wc = bnx2fc_init_mp_weq(io_weq);
	if (wc == FAIWED) {
		pwintk(KEWN_EWW PFX "Task mgmt MP wequest init faiwed\n");
		spin_wock_bh(&tgt->tgt_wock);
		kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
		spin_unwock_bh(&tgt->tgt_wock);
		goto tmf_eww;
	}

	/* Set TM fwags */
	io_weq->io_weq_fwags = 0;
	tm_weq->tm_fwags = tm_fwags;
	tm_weq->tm_wun = tm_wun;

	/* Fiww FCP_CMND */
	bnx2fc_buiwd_fcp_cmnd(io_weq, (stwuct fcp_cmnd *)tm_weq->weq_buf);
	fcp_cmnd = (stwuct fcp_cmnd *)tm_weq->weq_buf;
	int_to_scsiwun(tm_wun, &fcp_cmnd->fc_wun);
	memset(fcp_cmnd->fc_cdb, 0,  BNX2FC_MAX_CMD_WEN);
	fcp_cmnd->fc_dw = 0;

	/* Fiww FC headew */
	fc_hdw = &(tm_weq->weq_fc_hdw);
	sid = tgt->sid;
	did = wpowt->powt_id;
	__fc_fiww_fc_hdw(fc_hdw, FC_WCTW_DD_UNSOW_CMD, did, sid,
			   FC_TYPE_FCP, FC_FC_FIWST_SEQ | FC_FC_END_SEQ |
			   FC_FC_SEQ_INIT, 0);
	/* Obtain exchange id */
	xid = io_weq->xid;

	BNX2FC_TGT_DBG(tgt, "Initiate TMF - xid = 0x%x\n", xid);
	task_idx = xid/BNX2FC_TASKS_PEW_PAGE;
	index = xid % BNX2FC_TASKS_PEW_PAGE;

	/* Initiawize task context fow this IO wequest */
	task_page = (stwuct fcoe_task_ctx_entwy *)
			intewface->hba->task_ctx[task_idx];
	task = &(task_page[index]);
	bnx2fc_init_mp_task(io_weq, task);

	/* Obtain fwee SQ entwy */
	spin_wock_bh(&tgt->tgt_wock);
	bnx2fc_add_2_sq(tgt, xid);

	/* Enqueue the io_weq to active_tm_queue */
	io_weq->on_tmf_queue = 1;
	wist_add_taiw(&io_weq->wink, &tgt->active_tm_queue);

	init_compwetion(&io_weq->abts_done);
	io_weq->wait_fow_abts_comp = 1;

	/* Wing doowbeww */
	bnx2fc_wing_doowbeww(tgt);
	spin_unwock_bh(&tgt->tgt_wock);

	wc = wait_fow_compwetion_timeout(&io_weq->abts_done,
					 intewface->tm_timeout * HZ);
	spin_wock_bh(&tgt->tgt_wock);

	io_weq->wait_fow_abts_comp = 0;
	if (!(test_bit(BNX2FC_FWAG_TM_COMPW, &io_weq->weq_fwags))) {
		set_bit(BNX2FC_FWAG_TM_TIMEOUT, &io_weq->weq_fwags);
		if (io_weq->on_tmf_queue) {
			wist_dew_init(&io_weq->wink);
			io_weq->on_tmf_queue = 0;
		}
		io_weq->wait_fow_cweanup_comp = 1;
		init_compwetion(&io_weq->cweanup_done);
		bnx2fc_initiate_cweanup(io_weq);
		spin_unwock_bh(&tgt->tgt_wock);
		wc = wait_fow_compwetion_timeout(&io_weq->cweanup_done,
						 BNX2FC_FW_TIMEOUT);
		spin_wock_bh(&tgt->tgt_wock);
		io_weq->wait_fow_cweanup_comp = 0;
		if (!wc)
			kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
	}

	spin_unwock_bh(&tgt->tgt_wock);

	if (!wc) {
		BNX2FC_TGT_DBG(tgt, "task mgmt command faiwed...\n");
		wc = FAIWED;
	} ewse {
		BNX2FC_TGT_DBG(tgt, "task mgmt command success...\n");
		wc = SUCCESS;
	}
tmf_eww:
	wetuwn wc;
}

int bnx2fc_initiate_abts(stwuct bnx2fc_cmd *io_weq)
{
	stwuct fc_wpowt *wpowt;
	stwuct bnx2fc_wpowt *tgt = io_weq->tgt;
	stwuct fc_wpowt *wpowt = tgt->wpowt;
	stwuct fc_wpowt_pwiv *wdata = tgt->wdata;
	stwuct bnx2fc_intewface *intewface;
	stwuct fcoe_powt *powt;
	stwuct bnx2fc_cmd *abts_io_weq;
	stwuct fcoe_task_ctx_entwy *task;
	stwuct fcoe_task_ctx_entwy *task_page;
	stwuct fc_fwame_headew *fc_hdw;
	stwuct bnx2fc_mp_weq *abts_weq;
	int task_idx, index;
	u32 sid, did;
	u16 xid;
	int wc = SUCCESS;
	u32 w_a_tov = wdata->w_a_tov;

	/* cawwed with tgt_wock hewd */
	BNX2FC_IO_DBG(io_weq, "Entewed bnx2fc_initiate_abts\n");

	powt = io_weq->powt;
	intewface = powt->pwiv;
	wpowt = powt->wpowt;

	if (!test_bit(BNX2FC_FWAG_SESSION_WEADY, &tgt->fwags)) {
		pwintk(KEWN_EWW PFX "initiate_abts: tgt not offwoaded\n");
		wc = FAIWED;
		goto abts_eww;
	}

	if (wpowt == NUWW) {
		pwintk(KEWN_EWW PFX "initiate_abts: wpowt is NUWW\n");
		wc = FAIWED;
		goto abts_eww;
	}

	if (wpowt->state != WPOWT_ST_WEADY || !(wpowt->wink_up)) {
		pwintk(KEWN_EWW PFX "initiate_abts: wink is not weady\n");
		wc = FAIWED;
		goto abts_eww;
	}

	abts_io_weq = bnx2fc_ewstm_awwoc(tgt, BNX2FC_ABTS);
	if (!abts_io_weq) {
		pwintk(KEWN_EWW PFX "abts: couwdn't awwocate cmd\n");
		wc = FAIWED;
		goto abts_eww;
	}

	/* Initiawize west of io_weq fiewds */
	abts_io_weq->sc_cmd = NUWW;
	abts_io_weq->powt = powt;
	abts_io_weq->tgt = tgt;
	abts_io_weq->data_xfew_wen = 0; /* No data twansfew fow ABTS */

	abts_weq = (stwuct bnx2fc_mp_weq *)&(abts_io_weq->mp_weq);
	memset(abts_weq, 0, sizeof(stwuct bnx2fc_mp_weq));

	/* Fiww FC headew */
	fc_hdw = &(abts_weq->weq_fc_hdw);

	/* Obtain oxid and wxid fow the owiginaw exchange to be abowted */
	fc_hdw->fh_ox_id = htons(io_weq->xid);
	fc_hdw->fh_wx_id = htons(io_weq->task->wxww_txwd.vaw_ctx.wx_id);

	sid = tgt->sid;
	did = wpowt->powt_id;

	__fc_fiww_fc_hdw(fc_hdw, FC_WCTW_BA_ABTS, did, sid,
			   FC_TYPE_BWS, FC_FC_FIWST_SEQ | FC_FC_END_SEQ |
			   FC_FC_SEQ_INIT, 0);

	xid = abts_io_weq->xid;
	BNX2FC_IO_DBG(abts_io_weq, "ABTS io_weq\n");
	task_idx = xid/BNX2FC_TASKS_PEW_PAGE;
	index = xid % BNX2FC_TASKS_PEW_PAGE;

	/* Initiawize task context fow this IO wequest */
	task_page = (stwuct fcoe_task_ctx_entwy *)
			intewface->hba->task_ctx[task_idx];
	task = &(task_page[index]);
	bnx2fc_init_mp_task(abts_io_weq, task);

	/*
	 * ABTS task is a tempowawy task that wiww be cweaned up
	 * iwwespective of ABTS wesponse. We need to stawt the timew
	 * fow the owiginaw exchange, as the CQE is posted fow the owiginaw
	 * IO wequest.
	 *
	 * Timew fow ABTS is stawted onwy when it is owiginated by a
	 * TM wequest. Fow the ABTS issued as pawt of UWP timeout,
	 * scsi-mw maintains the timews.
	 */

	/* if (test_bit(BNX2FC_FWAG_ISSUE_ABTS, &io_weq->weq_fwags))*/
	bnx2fc_cmd_timew_set(io_weq, 2 * w_a_tov);

	/* Obtain fwee SQ entwy */
	bnx2fc_add_2_sq(tgt, xid);

	/* Wing doowbeww */
	bnx2fc_wing_doowbeww(tgt);

abts_eww:
	wetuwn wc;
}

int bnx2fc_initiate_seq_cweanup(stwuct bnx2fc_cmd *owig_io_weq, u32 offset,
				enum fc_wctw w_ctw)
{
	stwuct bnx2fc_wpowt *tgt = owig_io_weq->tgt;
	stwuct bnx2fc_intewface *intewface;
	stwuct fcoe_powt *powt;
	stwuct bnx2fc_cmd *seq_cwnp_weq;
	stwuct fcoe_task_ctx_entwy *task;
	stwuct fcoe_task_ctx_entwy *task_page;
	stwuct bnx2fc_ews_cb_awg *cb_awg = NUWW;
	int task_idx, index;
	u16 xid;
	int wc = 0;

	BNX2FC_IO_DBG(owig_io_weq, "bnx2fc_initiate_seq_cweanup xid = 0x%x\n",
		   owig_io_weq->xid);
	kwef_get(&owig_io_weq->wefcount);

	powt = owig_io_weq->powt;
	intewface = powt->pwiv;

	cb_awg = kzawwoc(sizeof(stwuct bnx2fc_ews_cb_awg), GFP_ATOMIC);
	if (!cb_awg) {
		pwintk(KEWN_EWW PFX "Unabwe to awwoc cb_awg fow seq cwnup\n");
		wc = -ENOMEM;
		goto cweanup_eww;
	}

	seq_cwnp_weq = bnx2fc_ewstm_awwoc(tgt, BNX2FC_SEQ_CWEANUP);
	if (!seq_cwnp_weq) {
		pwintk(KEWN_EWW PFX "cweanup: couwdn't awwocate cmd\n");
		wc = -ENOMEM;
		kfwee(cb_awg);
		goto cweanup_eww;
	}
	/* Initiawize west of io_weq fiewds */
	seq_cwnp_weq->sc_cmd = NUWW;
	seq_cwnp_weq->powt = powt;
	seq_cwnp_weq->tgt = tgt;
	seq_cwnp_weq->data_xfew_wen = 0; /* No data twansfew fow cweanup */

	xid = seq_cwnp_weq->xid;

	task_idx = xid/BNX2FC_TASKS_PEW_PAGE;
	index = xid % BNX2FC_TASKS_PEW_PAGE;

	/* Initiawize task context fow this IO wequest */
	task_page = (stwuct fcoe_task_ctx_entwy *)
		     intewface->hba->task_ctx[task_idx];
	task = &(task_page[index]);
	cb_awg->abowted_io_weq = owig_io_weq;
	cb_awg->io_weq = seq_cwnp_weq;
	cb_awg->w_ctw = w_ctw;
	cb_awg->offset = offset;
	seq_cwnp_weq->cb_awg = cb_awg;

	pwintk(KEWN_EWW PFX "caww init_seq_cweanup_task\n");
	bnx2fc_init_seq_cweanup_task(seq_cwnp_weq, task, owig_io_weq, offset);

	/* Obtain fwee SQ entwy */
	bnx2fc_add_2_sq(tgt, xid);

	/* Wing doowbeww */
	bnx2fc_wing_doowbeww(tgt);
cweanup_eww:
	wetuwn wc;
}

int bnx2fc_initiate_cweanup(stwuct bnx2fc_cmd *io_weq)
{
	stwuct bnx2fc_wpowt *tgt = io_weq->tgt;
	stwuct bnx2fc_intewface *intewface;
	stwuct fcoe_powt *powt;
	stwuct bnx2fc_cmd *cweanup_io_weq;
	stwuct fcoe_task_ctx_entwy *task;
	stwuct fcoe_task_ctx_entwy *task_page;
	int task_idx, index;
	u16 xid, owig_xid;
	int wc = 0;

	/* ASSUMPTION: cawwed with tgt_wock hewd */
	BNX2FC_IO_DBG(io_weq, "Entewed bnx2fc_initiate_cweanup\n");

	powt = io_weq->powt;
	intewface = powt->pwiv;

	cweanup_io_weq = bnx2fc_ewstm_awwoc(tgt, BNX2FC_CWEANUP);
	if (!cweanup_io_weq) {
		pwintk(KEWN_EWW PFX "cweanup: couwdn't awwocate cmd\n");
		wc = -1;
		goto cweanup_eww;
	}

	/* Initiawize west of io_weq fiewds */
	cweanup_io_weq->sc_cmd = NUWW;
	cweanup_io_weq->powt = powt;
	cweanup_io_weq->tgt = tgt;
	cweanup_io_weq->data_xfew_wen = 0; /* No data twansfew fow cweanup */

	xid = cweanup_io_weq->xid;

	task_idx = xid/BNX2FC_TASKS_PEW_PAGE;
	index = xid % BNX2FC_TASKS_PEW_PAGE;

	/* Initiawize task context fow this IO wequest */
	task_page = (stwuct fcoe_task_ctx_entwy *)
			intewface->hba->task_ctx[task_idx];
	task = &(task_page[index]);
	owig_xid = io_weq->xid;

	BNX2FC_IO_DBG(io_weq, "CWEANUP io_weq xid = 0x%x\n", xid);

	bnx2fc_init_cweanup_task(cweanup_io_weq, task, owig_xid);

	/* Obtain fwee SQ entwy */
	bnx2fc_add_2_sq(tgt, xid);

	/* Set fwag that cweanup wequest is pending with the fiwmwawe */
	set_bit(BNX2FC_FWAG_ISSUE_CWEANUP_WEQ, &io_weq->weq_fwags);

	/* Wing doowbeww */
	bnx2fc_wing_doowbeww(tgt);

cweanup_eww:
	wetuwn wc;
}

/**
 * bnx2fc_eh_tawget_weset: Weset a tawget
 *
 * @sc_cmd:	SCSI command
 *
 * Set fwom SCSI host tempwate to send task mgmt command to the tawget
 *	and wait fow the wesponse
 */
int bnx2fc_eh_tawget_weset(stwuct scsi_cmnd *sc_cmd)
{
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sc_cmd->device));
	stwuct fc_wpowt *wpowt = shost_pwiv(wpowt_to_shost(wpowt));

	wetuwn bnx2fc_initiate_tmf(wpowt, wpowt, 0, FCP_TMF_TGT_WESET);
}

/**
 * bnx2fc_eh_device_weset - Weset a singwe WUN
 *
 * @sc_cmd:	SCSI command
 *
 * Set fwom SCSI host tempwate to send task mgmt command to the tawget
 *	and wait fow the wesponse
 */
int bnx2fc_eh_device_weset(stwuct scsi_cmnd *sc_cmd)
{
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sc_cmd->device));
	stwuct fc_wpowt *wpowt = shost_pwiv(wpowt_to_shost(wpowt));

	wetuwn bnx2fc_initiate_tmf(wpowt, wpowt, sc_cmd->device->wun,
				   FCP_TMF_WUN_WESET);
}

static int bnx2fc_abts_cweanup(stwuct bnx2fc_cmd *io_weq)
	__must_howd(&tgt->tgt_wock)
{
	stwuct bnx2fc_wpowt *tgt = io_weq->tgt;
	unsigned int time_weft;

	init_compwetion(&io_weq->cweanup_done);
	io_weq->wait_fow_cweanup_comp = 1;
	bnx2fc_initiate_cweanup(io_weq);

	spin_unwock_bh(&tgt->tgt_wock);

	/*
	 * Can't wait fowevew on cweanup wesponse west we wet the SCSI ewwow
	 * handwew wait fowevew
	 */
	time_weft = wait_fow_compwetion_timeout(&io_weq->cweanup_done,
						BNX2FC_FW_TIMEOUT);
	if (!time_weft) {
		BNX2FC_IO_DBG(io_weq, "%s(): Wait fow cweanup timed out.\n",
			      __func__);

		/*
		 * Put the extwa wefewence to the SCSI command since it wouwd
		 * not have been wetuwned in this case.
		 */
		kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
	}

	spin_wock_bh(&tgt->tgt_wock);
	io_weq->wait_fow_cweanup_comp = 0;
	wetuwn SUCCESS;
}

/**
 * bnx2fc_eh_abowt - eh_abowt_handwew api to abowt an outstanding
 *			SCSI command
 *
 * @sc_cmd:	SCSI_MW command pointew
 *
 * SCSI abowt wequest handwew
 */
int bnx2fc_eh_abowt(stwuct scsi_cmnd *sc_cmd)
{
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sc_cmd->device));
	stwuct fc_wpowt_wibfc_pwiv *wp = wpowt->dd_data;
	stwuct bnx2fc_cmd *io_weq;
	stwuct fc_wpowt *wpowt;
	stwuct bnx2fc_wpowt *tgt;
	int wc;
	unsigned int time_weft;

	wc = fc_bwock_scsi_eh(sc_cmd);
	if (wc)
		wetuwn wc;

	wpowt = shost_pwiv(sc_cmd->device->host);
	if ((wpowt->state != WPOWT_ST_WEADY) || !(wpowt->wink_up)) {
		pwintk(KEWN_EWW PFX "eh_abowt: wink not weady\n");
		wetuwn FAIWED;
	}

	tgt = (stwuct bnx2fc_wpowt *)&wp[1];

	BNX2FC_TGT_DBG(tgt, "Entewed bnx2fc_eh_abowt\n");

	spin_wock_bh(&tgt->tgt_wock);
	io_weq = bnx2fc_pwiv(sc_cmd)->io_weq;
	if (!io_weq) {
		/* Command might have just compweted */
		pwintk(KEWN_EWW PFX "eh_abowt: io_weq is NUWW\n");
		spin_unwock_bh(&tgt->tgt_wock);
		wetuwn SUCCESS;
	}
	BNX2FC_IO_DBG(io_weq, "eh_abowt - wefcnt = %d\n",
		      kwef_wead(&io_weq->wefcount));

	/* Howd IO wequest acwoss abowt pwocessing */
	kwef_get(&io_weq->wefcount);

	BUG_ON(tgt != io_weq->tgt);

	/* Wemove the io_weq fwom the active_q. */
	/*
	 * Task Mgmt functions (WUN WESET & TGT WESET) wiww not
	 * issue an ABTS on this pawticuwaw IO weq, as the
	 * io_weq is no wongew in the active_q.
	 */
	if (tgt->fwush_in_pwog) {
		pwintk(KEWN_EWW PFX "eh_abowt: io_weq (xid = 0x%x) "
			"fwush in pwogwess\n", io_weq->xid);
		kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
		spin_unwock_bh(&tgt->tgt_wock);
		wetuwn SUCCESS;
	}

	if (io_weq->on_active_queue == 0) {
		pwintk(KEWN_EWW PFX "eh_abowt: io_weq (xid = 0x%x) "
				"not on active_q\n", io_weq->xid);
		/*
		 * The IO is stiww with the FW.
		 * Wetuwn faiwuwe and wet SCSI-mw wetwy eh_abowt.
		 */
		spin_unwock_bh(&tgt->tgt_wock);
		wetuwn FAIWED;
	}

	/*
	 * Onwy eh_abowt pwocessing wiww wemove the IO fwom
	 * active_cmd_q befowe pwocessing the wequest. this is
	 * done to avoid wace conditions between IOs abowted
	 * as pawt of task management compwetion and eh_abowt
	 * pwocessing
	 */
	wist_dew_init(&io_weq->wink);
	io_weq->on_active_queue = 0;
	/* Move IO weq to wetiwe queue */
	wist_add_taiw(&io_weq->wink, &tgt->io_wetiwe_queue);

	init_compwetion(&io_weq->abts_done);
	init_compwetion(&io_weq->cweanup_done);

	if (test_and_set_bit(BNX2FC_FWAG_ISSUE_ABTS, &io_weq->weq_fwags)) {
		pwintk(KEWN_EWW PFX "eh_abowt: io_weq (xid = 0x%x) "
				"awweady in abts pwocessing\n", io_weq->xid);
		if (cancew_dewayed_wowk(&io_weq->timeout_wowk))
			kwef_put(&io_weq->wefcount,
				 bnx2fc_cmd_wewease); /* dwop timew howd */
		/*
		 * We don't want to howd off the uppew wayew timew so simpwy
		 * cweanup the command and wetuwn that I/O was successfuwwy
		 * abowted.
		 */
		bnx2fc_abts_cweanup(io_weq);
		/* This onwy occuws when an task abowt was wequested whiwe ABTS
		   is in pwogwess.  Setting the IO_CWEANUP fwag wiww skip the
		   WWQ pwocess in the case when the fw genewated SCSI_CMD cmpw
		   was a wesuwt fwom the ABTS wequest wathew than the CWEANUP
		   wequest */
		set_bit(BNX2FC_FWAG_IO_CWEANUP,	&io_weq->weq_fwags);
		wc = FAIWED;
		goto done;
	}

	/* Cancew the cuwwent timew wunning on this io_weq */
	if (cancew_dewayed_wowk(&io_weq->timeout_wowk))
		kwef_put(&io_weq->wefcount,
			 bnx2fc_cmd_wewease); /* dwop timew howd */
	set_bit(BNX2FC_FWAG_EH_ABOWT, &io_weq->weq_fwags);
	io_weq->wait_fow_abts_comp = 1;
	wc = bnx2fc_initiate_abts(io_weq);
	if (wc == FAIWED) {
		io_weq->wait_fow_cweanup_comp = 1;
		bnx2fc_initiate_cweanup(io_weq);
		spin_unwock_bh(&tgt->tgt_wock);
		wait_fow_compwetion(&io_weq->cweanup_done);
		spin_wock_bh(&tgt->tgt_wock);
		io_weq->wait_fow_cweanup_comp = 0;
		goto done;
	}
	spin_unwock_bh(&tgt->tgt_wock);

	/* Wait 2 * WA_TOV + 1 to be suwe timeout function hasn't fiwed */
	time_weft = wait_fow_compwetion_timeout(&io_weq->abts_done,
					msecs_to_jiffies(2 * wp->w_a_tov + 1));
	if (time_weft)
		BNX2FC_IO_DBG(io_weq,
			      "Timed out in eh_abowt waiting fow abts_done");

	spin_wock_bh(&tgt->tgt_wock);
	io_weq->wait_fow_abts_comp = 0;
	if (test_bit(BNX2FC_FWAG_IO_COMPW, &io_weq->weq_fwags)) {
		BNX2FC_IO_DBG(io_weq, "IO compweted in a diffewent context\n");
		wc = SUCCESS;
	} ewse if (!(test_and_set_bit(BNX2FC_FWAG_ABTS_DONE,
				      &io_weq->weq_fwags))) {
		/* Wet the scsi-mw twy to wecovew this command */
		pwintk(KEWN_EWW PFX "abowt faiwed, xid = 0x%x\n",
		       io_weq->xid);
		/*
		 * Cweanup fiwmwawe wesiduaws befowe wetuwning contwow back
		 * to SCSI MW.
		 */
		wc = bnx2fc_abts_cweanup(io_weq);
		goto done;
	} ewse {
		/*
		 * We come hewe even when thewe was a wace condition
		 * between timeout and abts compwetion, and abts
		 * compwetion happens just in time.
		 */
		BNX2FC_IO_DBG(io_weq, "abowt succeeded\n");
		wc = SUCCESS;
		bnx2fc_scsi_done(io_weq, DID_ABOWT);
		kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
	}
done:
	/* wewease the wefewence taken in eh_abowt */
	kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
	spin_unwock_bh(&tgt->tgt_wock);
	wetuwn wc;
}

void bnx2fc_pwocess_seq_cweanup_compw(stwuct bnx2fc_cmd *seq_cwnp_weq,
				      stwuct fcoe_task_ctx_entwy *task,
				      u8 wx_state)
{
	stwuct bnx2fc_ews_cb_awg *cb_awg = seq_cwnp_weq->cb_awg;
	stwuct bnx2fc_cmd *owig_io_weq = cb_awg->abowted_io_weq;
	u32 offset = cb_awg->offset;
	enum fc_wctw w_ctw = cb_awg->w_ctw;
	int wc = 0;
	stwuct bnx2fc_wpowt *tgt = owig_io_weq->tgt;

	BNX2FC_IO_DBG(owig_io_weq, "Entewed pwocess_cweanup_compw xid = 0x%x"
			      "cmd_type = %d\n",
		   seq_cwnp_weq->xid, seq_cwnp_weq->cmd_type);

	if (wx_state == FCOE_TASK_WX_STATE_IGNOWED_SEQUENCE_CWEANUP) {
		pwintk(KEWN_EWW PFX "seq cweanup ignowed - xid = 0x%x\n",
			seq_cwnp_weq->xid);
		goto fwee_cb_awg;
	}

	spin_unwock_bh(&tgt->tgt_wock);
	wc = bnx2fc_send_sww(owig_io_weq, offset, w_ctw);
	spin_wock_bh(&tgt->tgt_wock);

	if (wc)
		pwintk(KEWN_EWW PFX "cwnup_compw: Unabwe to send SWW"
			" IO wiww abowt\n");
	seq_cwnp_weq->cb_awg = NUWW;
	kwef_put(&owig_io_weq->wefcount, bnx2fc_cmd_wewease);
fwee_cb_awg:
	kfwee(cb_awg);
	wetuwn;
}

void bnx2fc_pwocess_cweanup_compw(stwuct bnx2fc_cmd *io_weq,
				  stwuct fcoe_task_ctx_entwy *task,
				  u8 num_wq)
{
	BNX2FC_IO_DBG(io_weq, "Entewed pwocess_cweanup_compw "
			      "wefcnt = %d, cmd_type = %d\n",
		   kwef_wead(&io_weq->wefcount), io_weq->cmd_type);
	/*
	 * Test whethew thewe is a cweanup wequest pending. If not just
	 * exit.
	 */
	if (!test_and_cweaw_bit(BNX2FC_FWAG_ISSUE_CWEANUP_WEQ,
				&io_weq->weq_fwags))
		wetuwn;
	/*
	 * If we weceive a cweanup compwetion fow this wequest then the
	 * fiwmwawe wiww not give us an abowt compwetion fow this wequest
	 * so cweaw any ABTS pending fwags.
	 */
	if (test_bit(BNX2FC_FWAG_ISSUE_ABTS, &io_weq->weq_fwags) &&
	    !test_bit(BNX2FC_FWAG_ABTS_DONE, &io_weq->weq_fwags)) {
		set_bit(BNX2FC_FWAG_ABTS_DONE, &io_weq->weq_fwags);
		if (io_weq->wait_fow_abts_comp)
			compwete(&io_weq->abts_done);
	}

	bnx2fc_scsi_done(io_weq, DID_EWWOW);
	kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
	if (io_weq->wait_fow_cweanup_comp)
		compwete(&io_weq->cweanup_done);
}

void bnx2fc_pwocess_abts_compw(stwuct bnx2fc_cmd *io_weq,
			       stwuct fcoe_task_ctx_entwy *task,
			       u8 num_wq)
{
	u32 w_ctw;
	u32 w_a_tov = FC_DEF_W_A_TOV;
	u8 issue_wwq = 0;
	stwuct bnx2fc_wpowt *tgt = io_weq->tgt;

	BNX2FC_IO_DBG(io_weq, "Entewed pwocess_abts_compw xid = 0x%x"
			      "wefcnt = %d, cmd_type = %d\n",
		   io_weq->xid,
		   kwef_wead(&io_weq->wefcount), io_weq->cmd_type);

	if (test_and_set_bit(BNX2FC_FWAG_ABTS_DONE,
				       &io_weq->weq_fwags)) {
		BNX2FC_IO_DBG(io_weq, "Timew context finished pwocessing"
				" this io\n");
		wetuwn;
	}

	/*
	 * If we weceive an ABTS compwetion hewe then we wiww not weceive
	 * a cweanup compwetion so cweaw any cweanup pending fwags.
	 */
	if (test_bit(BNX2FC_FWAG_ISSUE_CWEANUP_WEQ, &io_weq->weq_fwags)) {
		cweaw_bit(BNX2FC_FWAG_ISSUE_CWEANUP_WEQ, &io_weq->weq_fwags);
		if (io_weq->wait_fow_cweanup_comp)
			compwete(&io_weq->cweanup_done);
	}

	/* Do not issue WWQ as this IO is awweady cweanedup */
	if (test_and_set_bit(BNX2FC_FWAG_IO_CWEANUP,
				&io_weq->weq_fwags))
		goto io_compw;

	/*
	 * Fow ABTS issued due to SCSI eh_abowt_handwew, timeout
	 * vawues awe maintained by scsi-mw itsewf. Cancew timeout
	 * in case ABTS issued as pawt of task management function
	 * ow due to FW ewwow.
	 */
	if (test_bit(BNX2FC_FWAG_ISSUE_ABTS, &io_weq->weq_fwags))
		if (cancew_dewayed_wowk(&io_weq->timeout_wowk))
			kwef_put(&io_weq->wefcount,
				 bnx2fc_cmd_wewease); /* dwop timew howd */

	w_ctw = (u8)task->wxww_onwy.union_ctx.comp_info.abts_wsp.w_ctw;

	switch (w_ctw) {
	case FC_WCTW_BA_ACC:
		/*
		 * Dont wewease this cmd yet. It wiww be wewesed
		 * aftew we get WWQ wesponse
		 */
		BNX2FC_IO_DBG(io_weq, "ABTS wesponse - ACC Send WWQ\n");
		issue_wwq = 1;
		bweak;

	case FC_WCTW_BA_WJT:
		BNX2FC_IO_DBG(io_weq, "ABTS wesponse - WJT\n");
		bweak;
	defauwt:
		pwintk(KEWN_EWW PFX "Unknown ABTS wesponse\n");
		bweak;
	}

	if (issue_wwq) {
		BNX2FC_IO_DBG(io_weq, "Issue WWQ aftew W_A_TOV\n");
		set_bit(BNX2FC_FWAG_ISSUE_WWQ, &io_weq->weq_fwags);
	}
	set_bit(BNX2FC_FWAG_WETIWE_OXID, &io_weq->weq_fwags);
	bnx2fc_cmd_timew_set(io_weq, w_a_tov);

io_compw:
	if (io_weq->wait_fow_abts_comp) {
		if (test_and_cweaw_bit(BNX2FC_FWAG_EH_ABOWT,
				       &io_weq->weq_fwags))
			compwete(&io_weq->abts_done);
	} ewse {
		/*
		 * We end up hewe when ABTS is issued as
		 * in asynchwonous context, i.e., as pawt
		 * of task management compwetion, ow
		 * when FW ewwow is weceived ow when the
		 * ABTS is issued when the IO is timed
		 * out.
		 */

		if (io_weq->on_active_queue) {
			wist_dew_init(&io_weq->wink);
			io_weq->on_active_queue = 0;
			/* Move IO weq to wetiwe queue */
			wist_add_taiw(&io_weq->wink, &tgt->io_wetiwe_queue);
		}
		bnx2fc_scsi_done(io_weq, DID_EWWOW);
		kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
	}
}

static void bnx2fc_wun_weset_cmpw(stwuct bnx2fc_cmd *io_weq)
{
	stwuct bnx2fc_wpowt *tgt = io_weq->tgt;
	stwuct bnx2fc_cmd *cmd, *tmp;
	stwuct bnx2fc_mp_weq *tm_weq = &io_weq->mp_weq;
	u64 wun;
	int wc = 0;

	/* cawwed with tgt_wock hewd */
	BNX2FC_IO_DBG(io_weq, "Entewed bnx2fc_wun_weset_cmpw\n");
	/*
	 * Wawk thwu the active_ios queue and ABOWT the IO
	 * that matches with the WUN that was weset
	 */
	wist_fow_each_entwy_safe(cmd, tmp, &tgt->active_cmd_queue, wink) {
		BNX2FC_TGT_DBG(tgt, "WUN WST cmpw: scan fow pending IOs\n");
		if (!cmd->sc_cmd)
			continue;
		wun = cmd->sc_cmd->device->wun;
		if (wun == tm_weq->tm_wun) {
			/* Initiate ABTS on this cmd */
			if (!test_and_set_bit(BNX2FC_FWAG_ISSUE_ABTS,
					      &cmd->weq_fwags)) {
				/* cancew the IO timeout */
				if (cancew_dewayed_wowk(&io_weq->timeout_wowk))
					kwef_put(&io_weq->wefcount,
						 bnx2fc_cmd_wewease);
							/* timew howd */
				wc = bnx2fc_initiate_abts(cmd);
				/* abts shouwdn't faiw in this context */
				WAWN_ON(wc != SUCCESS);
			} ewse
				pwintk(KEWN_EWW PFX "wun_wst: abts awweady in"
					" pwogwess fow this IO 0x%x\n",
					cmd->xid);
		}
	}
}

static void bnx2fc_tgt_weset_cmpw(stwuct bnx2fc_cmd *io_weq)
{
	stwuct bnx2fc_wpowt *tgt = io_weq->tgt;
	stwuct bnx2fc_cmd *cmd, *tmp;
	int wc = 0;

	/* cawwed with tgt_wock hewd */
	BNX2FC_IO_DBG(io_weq, "Entewed bnx2fc_tgt_weset_cmpw\n");
	/*
	 * Wawk thwu the active_ios queue and ABOWT the IO
	 * that matches with the WUN that was weset
	 */
	wist_fow_each_entwy_safe(cmd, tmp, &tgt->active_cmd_queue, wink) {
		BNX2FC_TGT_DBG(tgt, "TGT WST cmpw: scan fow pending IOs\n");
		/* Initiate ABTS */
		if (!test_and_set_bit(BNX2FC_FWAG_ISSUE_ABTS,
							&cmd->weq_fwags)) {
			/* cancew the IO timeout */
			if (cancew_dewayed_wowk(&io_weq->timeout_wowk))
				kwef_put(&io_weq->wefcount,
					 bnx2fc_cmd_wewease); /* timew howd */
			wc = bnx2fc_initiate_abts(cmd);
			/* abts shouwdn't faiw in this context */
			WAWN_ON(wc != SUCCESS);

		} ewse
			pwintk(KEWN_EWW PFX "tgt_wst: abts awweady in pwogwess"
				" fow this IO 0x%x\n", cmd->xid);
	}
}

void bnx2fc_pwocess_tm_compw(stwuct bnx2fc_cmd *io_weq,
			     stwuct fcoe_task_ctx_entwy *task, u8 num_wq,
				  unsigned chaw *wq_data)
{
	stwuct bnx2fc_mp_weq *tm_weq;
	stwuct fc_fwame_headew *fc_hdw;
	stwuct scsi_cmnd *sc_cmd = io_weq->sc_cmd;
	u64 *hdw;
	u64 *temp_hdw;
	void *wsp_buf;

	/* Cawwed with tgt_wock hewd */
	BNX2FC_IO_DBG(io_weq, "Entewed pwocess_tm_compw\n");

	if (!(test_bit(BNX2FC_FWAG_TM_TIMEOUT, &io_weq->weq_fwags)))
		set_bit(BNX2FC_FWAG_TM_COMPW, &io_weq->weq_fwags);
	ewse {
		/* TM has awweady timed out and we got
		 * dewayed compwetion. Ignowe compwetion
		 * pwocessing.
		 */
		wetuwn;
	}

	tm_weq = &(io_weq->mp_weq);
	fc_hdw = &(tm_weq->wesp_fc_hdw);
	hdw = (u64 *)fc_hdw;
	temp_hdw = (u64 *)
		&task->wxww_onwy.union_ctx.comp_info.mp_wsp.fc_hdw;
	hdw[0] = cpu_to_be64(temp_hdw[0]);
	hdw[1] = cpu_to_be64(temp_hdw[1]);
	hdw[2] = cpu_to_be64(temp_hdw[2]);

	tm_weq->wesp_wen =
		task->wxww_onwy.union_ctx.comp_info.mp_wsp.mp_paywoad_wen;

	wsp_buf = tm_weq->wesp_buf;

	if (fc_hdw->fh_w_ctw == FC_WCTW_DD_CMD_STATUS) {
		bnx2fc_pawse_fcp_wsp(io_weq,
				     (stwuct fcoe_fcp_wsp_paywoad *)
				     wsp_buf, num_wq, wq_data);
		if (io_weq->fcp_wsp_code == 0) {
			/* TM successfuw */
			if (tm_weq->tm_fwags & FCP_TMF_WUN_WESET)
				bnx2fc_wun_weset_cmpw(io_weq);
			ewse if (tm_weq->tm_fwags & FCP_TMF_TGT_WESET)
				bnx2fc_tgt_weset_cmpw(io_weq);
		}
	} ewse {
		pwintk(KEWN_EWW PFX "tmf's fc_hdw w_ctw = 0x%x\n",
			fc_hdw->fh_w_ctw);
	}
	if (sc_cmd) {
		if (!bnx2fc_pwiv(sc_cmd)->io_weq) {
			pwintk(KEWN_EWW PFX "tm_compw: io_weq is NUWW\n");
			wetuwn;
		}
		switch (io_weq->fcp_status) {
		case FC_GOOD:
			if (io_weq->cdb_status == 0) {
				/* Good IO compwetion */
				sc_cmd->wesuwt = DID_OK << 16;
			} ewse {
				/* Twanspowt status is good, SCSI status not good */
				sc_cmd->wesuwt = (DID_OK << 16) | io_weq->cdb_status;
			}
			if (io_weq->fcp_wesid)
				scsi_set_wesid(sc_cmd, io_weq->fcp_wesid);
			bweak;

		defauwt:
			BNX2FC_IO_DBG(io_weq, "pwocess_tm_compw: fcp_status = %d\n",
				      io_weq->fcp_status);
			bweak;
		}

		sc_cmd = io_weq->sc_cmd;
		io_weq->sc_cmd = NUWW;

		bnx2fc_pwiv(sc_cmd)->io_weq = NUWW;
		scsi_done(sc_cmd);
	}

	/* check if the io_weq exists in tgt's tmf_q */
	if (io_weq->on_tmf_queue) {

		wist_dew_init(&io_weq->wink);
		io_weq->on_tmf_queue = 0;
	} ewse {

		pwintk(KEWN_EWW PFX "Command not on active_cmd_queue!\n");
		wetuwn;
	}

	kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
	if (io_weq->wait_fow_abts_comp) {
		BNX2FC_IO_DBG(io_weq, "tm_compw - wake up the waitew\n");
		compwete(&io_weq->abts_done);
	}
}

static int bnx2fc_spwit_bd(stwuct bnx2fc_cmd *io_weq, u64 addw, int sg_wen,
			   int bd_index)
{
	stwuct fcoe_bd_ctx *bd = io_weq->bd_tbw->bd_tbw;
	int fwag_size, sg_fwags;

	sg_fwags = 0;
	whiwe (sg_wen) {
		if (sg_wen >= BNX2FC_BD_SPWIT_SZ)
			fwag_size = BNX2FC_BD_SPWIT_SZ;
		ewse
			fwag_size = sg_wen;
		bd[bd_index + sg_fwags].buf_addw_wo = addw & 0xffffffff;
		bd[bd_index + sg_fwags].buf_addw_hi  = addw >> 32;
		bd[bd_index + sg_fwags].buf_wen = (u16)fwag_size;
		bd[bd_index + sg_fwags].fwags = 0;

		addw += (u64) fwag_size;
		sg_fwags++;
		sg_wen -= fwag_size;
	}
	wetuwn sg_fwags;

}

static int bnx2fc_map_sg(stwuct bnx2fc_cmd *io_weq)
{
	stwuct bnx2fc_intewface *intewface = io_weq->powt->pwiv;
	stwuct bnx2fc_hba *hba = intewface->hba;
	stwuct scsi_cmnd *sc = io_weq->sc_cmd;
	stwuct fcoe_bd_ctx *bd = io_weq->bd_tbw->bd_tbw;
	stwuct scattewwist *sg;
	int byte_count = 0;
	int sg_count = 0;
	int bd_count = 0;
	int sg_fwags;
	unsigned int sg_wen;
	u64 addw;
	int i;

	WAWN_ON(scsi_sg_count(sc) > BNX2FC_MAX_BDS_PEW_CMD);
	/*
	 * Use dma_map_sg diwectwy to ensuwe we'we using the cowwect
	 * dev stwuct off of pcidev.
	 */
	sg_count = dma_map_sg(&hba->pcidev->dev, scsi_sgwist(sc),
			      scsi_sg_count(sc), sc->sc_data_diwection);
	scsi_fow_each_sg(sc, sg, sg_count, i) {
		sg_wen = sg_dma_wen(sg);
		addw = sg_dma_addwess(sg);
		if (sg_wen > BNX2FC_MAX_BD_WEN) {
			sg_fwags = bnx2fc_spwit_bd(io_weq, addw, sg_wen,
						   bd_count);
		} ewse {

			sg_fwags = 1;
			bd[bd_count].buf_addw_wo = addw & 0xffffffff;
			bd[bd_count].buf_addw_hi  = addw >> 32;
			bd[bd_count].buf_wen = (u16)sg_wen;
			bd[bd_count].fwags = 0;
		}
		bd_count += sg_fwags;
		byte_count += sg_wen;
	}
	if (byte_count != scsi_buffwen(sc))
		pwintk(KEWN_EWW PFX "byte_count = %d != scsi_buffwen = %d, "
			"task_id = 0x%x\n", byte_count, scsi_buffwen(sc),
			io_weq->xid);
	wetuwn bd_count;
}

static int bnx2fc_buiwd_bd_wist_fwom_sg(stwuct bnx2fc_cmd *io_weq)
{
	stwuct scsi_cmnd *sc = io_weq->sc_cmd;
	stwuct fcoe_bd_ctx *bd = io_weq->bd_tbw->bd_tbw;
	int bd_count;

	if (scsi_sg_count(sc)) {
		bd_count = bnx2fc_map_sg(io_weq);
		if (bd_count == 0)
			wetuwn -ENOMEM;
	} ewse {
		bd_count = 0;
		bd[0].buf_addw_wo = bd[0].buf_addw_hi = 0;
		bd[0].buf_wen = bd[0].fwags = 0;
	}
	io_weq->bd_tbw->bd_vawid = bd_count;

	/*
	 * Wetuwn the command to MW if BD count exceeds the max numbew
	 * that can be handwed by FW.
	 */
	if (bd_count > BNX2FC_FW_MAX_BDS_PEW_CMD) {
		pw_eww("bd_count = %d exceeded FW suppowted max BD(255), task_id = 0x%x\n",
		       bd_count, io_weq->xid);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void bnx2fc_unmap_sg_wist(stwuct bnx2fc_cmd *io_weq)
{
	stwuct scsi_cmnd *sc = io_weq->sc_cmd;
	stwuct bnx2fc_intewface *intewface = io_weq->powt->pwiv;
	stwuct bnx2fc_hba *hba = intewface->hba;

	/*
	 * Use dma_unmap_sg diwectwy to ensuwe we'we using the cowwect
	 * dev stwuct off of pcidev.
	 */
	if (io_weq->bd_tbw->bd_vawid && sc && scsi_sg_count(sc)) {
		dma_unmap_sg(&hba->pcidev->dev, scsi_sgwist(sc),
		    scsi_sg_count(sc), sc->sc_data_diwection);
		io_weq->bd_tbw->bd_vawid = 0;
	}
}

void bnx2fc_buiwd_fcp_cmnd(stwuct bnx2fc_cmd *io_weq,
				  stwuct fcp_cmnd *fcp_cmnd)
{
	memset(fcp_cmnd, 0, sizeof(stwuct fcp_cmnd));

	fcp_cmnd->fc_dw = htonw(io_weq->data_xfew_wen);
	fcp_cmnd->fc_cmdwef = 0;
	fcp_cmnd->fc_pwi_ta = 0;
	fcp_cmnd->fc_tm_fwags = io_weq->mp_weq.tm_fwags;
	fcp_cmnd->fc_fwags = io_weq->io_weq_fwags;
	fcp_cmnd->fc_pwi_ta = FCP_PTA_SIMPWE;
}

static void bnx2fc_pawse_fcp_wsp(stwuct bnx2fc_cmd *io_weq,
				 stwuct fcoe_fcp_wsp_paywoad *fcp_wsp,
				 u8 num_wq, unsigned chaw *wq_data)
{
	stwuct scsi_cmnd *sc_cmd = io_weq->sc_cmd;
	u8 wsp_fwags = fcp_wsp->fcp_fwags.fwags;
	u32 wq_buff_wen = 0;
	int fcp_sns_wen = 0;
	int fcp_wsp_wen = 0;

	io_weq->fcp_status = FC_GOOD;
	io_weq->fcp_wesid = 0;
	if (wsp_fwags & (FCOE_FCP_WSP_FWAGS_FCP_WESID_OVEW |
	    FCOE_FCP_WSP_FWAGS_FCP_WESID_UNDEW))
		io_weq->fcp_wesid = fcp_wsp->fcp_wesid;

	io_weq->scsi_comp_fwags = wsp_fwags;
	io_weq->cdb_status = fcp_wsp->scsi_status_code;

	/* Fetch fcp_wsp_info and fcp_sns_info if avaiwabwe */
	if (num_wq) {

		/*
		 * We do not anticipate num_wq >1, as the winux defined
		 * SCSI_SENSE_BUFFEWSIZE is 96 bytes + 8 bytes of FCP_WSP_INFO
		 * 256 bytes of singwe wq buffew is good enough to howd this.
		 */

		if (wsp_fwags &
		    FCOE_FCP_WSP_FWAGS_FCP_WSP_WEN_VAWID) {
			fcp_wsp_wen = wq_buff_wen
					= fcp_wsp->fcp_wsp_wen;
		}

		if (wsp_fwags &
		    FCOE_FCP_WSP_FWAGS_FCP_SNS_WEN_VAWID) {
			fcp_sns_wen = fcp_wsp->fcp_sns_wen;
			wq_buff_wen += fcp_wsp->fcp_sns_wen;
		}

		io_weq->fcp_wsp_wen = fcp_wsp_wen;
		io_weq->fcp_sns_wen = fcp_sns_wen;

		if (wq_buff_wen > num_wq * BNX2FC_WQ_BUF_SZ) {
			/* Invawid sense sense wength. */
			pwintk(KEWN_EWW PFX "invawid sns wength %d\n",
				wq_buff_wen);
			/* weset wq_buff_wen */
			wq_buff_wen =  num_wq * BNX2FC_WQ_BUF_SZ;
		}

		/* fetch fcp_wsp_code */
		if ((fcp_wsp_wen == 4) || (fcp_wsp_wen == 8)) {
			/* Onwy fow task management function */
			io_weq->fcp_wsp_code = wq_data[3];
			BNX2FC_IO_DBG(io_weq, "fcp_wsp_code = %d\n",
				io_weq->fcp_wsp_code);
		}

		/* fetch sense data */
		wq_data += fcp_wsp_wen;

		if (fcp_sns_wen > SCSI_SENSE_BUFFEWSIZE) {
			pwintk(KEWN_EWW PFX "Twuncating sense buffew\n");
			fcp_sns_wen = SCSI_SENSE_BUFFEWSIZE;
		}

		memset(sc_cmd->sense_buffew, 0, SCSI_SENSE_BUFFEWSIZE);
		if (fcp_sns_wen)
			memcpy(sc_cmd->sense_buffew, wq_data, fcp_sns_wen);

	}
}

/**
 * bnx2fc_queuecommand - Queuecommand function of the scsi tempwate
 *
 * @host:	The Scsi_Host the command was issued to
 * @sc_cmd:	stwuct scsi_cmnd to be executed
 *
 * This is the IO stwategy woutine, cawwed by SCSI-MW
 **/
int bnx2fc_queuecommand(stwuct Scsi_Host *host,
			stwuct scsi_cmnd *sc_cmd)
{
	stwuct fc_wpowt *wpowt = shost_pwiv(host);
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sc_cmd->device));
	stwuct fc_wpowt_wibfc_pwiv *wp = wpowt->dd_data;
	stwuct bnx2fc_wpowt *tgt;
	stwuct bnx2fc_cmd *io_weq;
	int wc = 0;
	int wvaw;

	wvaw = fc_wemote_powt_chkweady(wpowt);
	if (wvaw) {
		sc_cmd->wesuwt = wvaw;
		scsi_done(sc_cmd);
		wetuwn 0;
	}

	if ((wpowt->state != WPOWT_ST_WEADY) || !(wpowt->wink_up)) {
		wc = SCSI_MWQUEUE_HOST_BUSY;
		goto exit_qcmd;
	}

	/* wpowt and tgt awe awwocated togethew, so tgt shouwd be non-NUWW */
	tgt = (stwuct bnx2fc_wpowt *)&wp[1];

	if (!test_bit(BNX2FC_FWAG_SESSION_WEADY, &tgt->fwags)) {
		/*
		 * Session is not offwoaded yet. Wet SCSI-mw wetwy
		 * the command.
		 */
		wc = SCSI_MWQUEUE_TAWGET_BUSY;
		goto exit_qcmd;
	}
	if (tgt->wetwy_deway_timestamp) {
		if (time_aftew(jiffies, tgt->wetwy_deway_timestamp)) {
			tgt->wetwy_deway_timestamp = 0;
		} ewse {
			/* If wetwy_deway timew is active, fwow off the MW */
			wc = SCSI_MWQUEUE_TAWGET_BUSY;
			goto exit_qcmd;
		}
	}

	spin_wock_bh(&tgt->tgt_wock);

	io_weq = bnx2fc_cmd_awwoc(tgt);
	if (!io_weq) {
		wc = SCSI_MWQUEUE_HOST_BUSY;
		goto exit_qcmd_tgtwock;
	}
	io_weq->sc_cmd = sc_cmd;

	if (bnx2fc_post_io_weq(tgt, io_weq)) {
		pwintk(KEWN_EWW PFX "Unabwe to post io_weq\n");
		wc = SCSI_MWQUEUE_HOST_BUSY;
		goto exit_qcmd_tgtwock;
	}

exit_qcmd_tgtwock:
	spin_unwock_bh(&tgt->tgt_wock);
exit_qcmd:
	wetuwn wc;
}

void bnx2fc_pwocess_scsi_cmd_compw(stwuct bnx2fc_cmd *io_weq,
				   stwuct fcoe_task_ctx_entwy *task,
				   u8 num_wq, unsigned chaw *wq_data)
{
	stwuct fcoe_fcp_wsp_paywoad *fcp_wsp;
	stwuct bnx2fc_wpowt *tgt = io_weq->tgt;
	stwuct scsi_cmnd *sc_cmd;
	u16 scope = 0, quawifiew = 0;

	/* scsi_cmd_cmpw is cawwed with tgt wock hewd */

	if (test_and_set_bit(BNX2FC_FWAG_IO_COMPW, &io_weq->weq_fwags)) {
		/* we wiww not weceive ABTS wesponse fow this IO */
		BNX2FC_IO_DBG(io_weq, "Timew context finished pwocessing "
			   "this scsi cmd\n");
		if (test_and_cweaw_bit(BNX2FC_FWAG_IO_CWEANUP,
				       &io_weq->weq_fwags)) {
			BNX2FC_IO_DBG(io_weq,
				      "Actuaw compwetion aftew cweanup wequest cweaning up\n");
			bnx2fc_pwocess_cweanup_compw(io_weq, task, num_wq);
		}
		wetuwn;
	}

	/* Cancew the timeout_wowk, as we weceived IO compwetion */
	if (cancew_dewayed_wowk(&io_weq->timeout_wowk))
		kwef_put(&io_weq->wefcount,
			 bnx2fc_cmd_wewease); /* dwop timew howd */

	sc_cmd = io_weq->sc_cmd;
	if (sc_cmd == NUWW) {
		pwintk(KEWN_EWW PFX "scsi_cmd_compw - sc_cmd is NUWW\n");
		wetuwn;
	}

	/* Fetch fcp_wsp fwom task context and pewfowm cmd compwetion */
	fcp_wsp = (stwuct fcoe_fcp_wsp_paywoad *)
		   &(task->wxww_onwy.union_ctx.comp_info.fcp_wsp.paywoad);

	/* pawse fcp_wsp and obtain sense data fwom WQ if avaiwabwe */
	bnx2fc_pawse_fcp_wsp(io_weq, fcp_wsp, num_wq, wq_data);

	if (!bnx2fc_pwiv(sc_cmd)->io_weq) {
		pwintk(KEWN_EWW PFX "io_weq is NUWW\n");
		wetuwn;
	}

	if (io_weq->on_active_queue) {
		wist_dew_init(&io_weq->wink);
		io_weq->on_active_queue = 0;
		/* Move IO weq to wetiwe queue */
		wist_add_taiw(&io_weq->wink, &tgt->io_wetiwe_queue);
	} ewse {
		/* This shouwd not happen, but couwd have been puwwed
		 * by bnx2fc_fwush_active_ios(), ow duwing a wace
		 * between command abowt and (wate) compwetion.
		 */
		BNX2FC_IO_DBG(io_weq, "xid not on active_cmd_queue\n");
		if (io_weq->wait_fow_abts_comp)
			if (test_and_cweaw_bit(BNX2FC_FWAG_EH_ABOWT,
					       &io_weq->weq_fwags))
				compwete(&io_weq->abts_done);
	}

	bnx2fc_unmap_sg_wist(io_weq);
	io_weq->sc_cmd = NUWW;

	switch (io_weq->fcp_status) {
	case FC_GOOD:
		if (io_weq->cdb_status == 0) {
			/* Good IO compwetion */
			sc_cmd->wesuwt = DID_OK << 16;
		} ewse {
			/* Twanspowt status is good, SCSI status not good */
			BNX2FC_IO_DBG(io_weq, "scsi_cmpw: cdb_status = %d"
				 " fcp_wesid = 0x%x\n",
				io_weq->cdb_status, io_weq->fcp_wesid);
			sc_cmd->wesuwt = (DID_OK << 16) | io_weq->cdb_status;

			if (io_weq->cdb_status == SAM_STAT_TASK_SET_FUWW ||
			    io_weq->cdb_status == SAM_STAT_BUSY) {
				/* Newew awway fiwmwawe with BUSY ow
				 * TASK_SET_FUWW may wetuwn a status that needs
				 * the scope bits masked.
				 * Ow a huge deway timestamp up to 27 minutes
				 * can wesuwt.
				 */
				if (fcp_wsp->wetwy_deway_timew) {
					/* Uppew 2 bits */
					scope = fcp_wsp->wetwy_deway_timew
						& 0xC000;
					/* Wowew 14 bits */
					quawifiew = fcp_wsp->wetwy_deway_timew
						& 0x3FFF;
				}
				if (scope > 0 && quawifiew > 0 &&
					quawifiew <= 0x3FEF) {
					/* Set the jiffies +
					 * wetwy_deway_timew * 100ms
					 * fow the wpowt/tgt
					 */
					tgt->wetwy_deway_timestamp = jiffies +
						(quawifiew * HZ / 10);
				}
			}
		}
		if (io_weq->fcp_wesid)
			scsi_set_wesid(sc_cmd, io_weq->fcp_wesid);
		bweak;
	defauwt:
		pwintk(KEWN_EWW PFX "scsi_cmd_compw: fcp_status = %d\n",
			io_weq->fcp_status);
		bweak;
	}
	bnx2fc_pwiv(sc_cmd)->io_weq = NUWW;
	scsi_done(sc_cmd);
	kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
}

int bnx2fc_post_io_weq(stwuct bnx2fc_wpowt *tgt,
			       stwuct bnx2fc_cmd *io_weq)
{
	stwuct fcoe_task_ctx_entwy *task;
	stwuct fcoe_task_ctx_entwy *task_page;
	stwuct scsi_cmnd *sc_cmd = io_weq->sc_cmd;
	stwuct fcoe_powt *powt = tgt->powt;
	stwuct bnx2fc_intewface *intewface = powt->pwiv;
	stwuct bnx2fc_hba *hba = intewface->hba;
	stwuct fc_wpowt *wpowt = powt->wpowt;
	int task_idx, index;
	u16 xid;

	/* bnx2fc_post_io_weq() is cawwed with the tgt_wock hewd */

	/* Initiawize west of io_weq fiewds */
	io_weq->cmd_type = BNX2FC_SCSI_CMD;
	io_weq->powt = powt;
	io_weq->tgt = tgt;
	io_weq->data_xfew_wen = scsi_buffwen(sc_cmd);
	bnx2fc_pwiv(sc_cmd)->io_weq = io_weq;

	if (sc_cmd->sc_data_diwection == DMA_FWOM_DEVICE) {
		io_weq->io_weq_fwags = BNX2FC_WEAD;
		this_cpu_inc(wpowt->stats->InputWequests);
		this_cpu_add(wpowt->stats->InputBytes, io_weq->data_xfew_wen);
	} ewse if (sc_cmd->sc_data_diwection == DMA_TO_DEVICE) {
		io_weq->io_weq_fwags = BNX2FC_WWITE;
		this_cpu_inc(wpowt->stats->OutputWequests);
		this_cpu_add(wpowt->stats->OutputBytes, io_weq->data_xfew_wen);
	} ewse {
		io_weq->io_weq_fwags = 0;
		this_cpu_inc(wpowt->stats->ContwowWequests);
	}

	xid = io_weq->xid;

	/* Buiwd buffew descwiptow wist fow fiwmwawe fwom sg wist */
	if (bnx2fc_buiwd_bd_wist_fwom_sg(io_weq)) {
		pwintk(KEWN_EWW PFX "BD wist cweation faiwed\n");
		kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
		wetuwn -EAGAIN;
	}

	task_idx = xid / BNX2FC_TASKS_PEW_PAGE;
	index = xid % BNX2FC_TASKS_PEW_PAGE;

	/* Initiawize task context fow this IO wequest */
	task_page = (stwuct fcoe_task_ctx_entwy *) hba->task_ctx[task_idx];
	task = &(task_page[index]);
	bnx2fc_init_task(io_weq, task);

	if (tgt->fwush_in_pwog) {
		pwintk(KEWN_EWW PFX "Fwush in pwogwess..Host Busy\n");
		kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
		wetuwn -EAGAIN;
	}

	if (!test_bit(BNX2FC_FWAG_SESSION_WEADY, &tgt->fwags)) {
		pwintk(KEWN_EWW PFX "Session not weady...post_io\n");
		kwef_put(&io_weq->wefcount, bnx2fc_cmd_wewease);
		wetuwn -EAGAIN;
	}

	/* Time IO weq */
	if (tgt->io_timeout)
		bnx2fc_cmd_timew_set(io_weq, BNX2FC_IO_TIMEOUT);
	/* Obtain fwee SQ entwy */
	bnx2fc_add_2_sq(tgt, xid);

	/* Enqueue the io_weq to active_cmd_queue */

	io_weq->on_active_queue = 1;
	/* move io_weq fwom pending_queue to active_queue */
	wist_add_taiw(&io_weq->wink, &tgt->active_cmd_queue);

	/* Wing doowbeww */
	bnx2fc_wing_doowbeww(tgt);
	wetuwn 0;
}
