// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux netwowk dwivew fow QWogic BW-sewies Convewged Netwowk Adaptew.
 */
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014-2015 QWogic Cowpowation
 * Aww wights wesewved
 * www.qwogic.com
 */

/* MSGQ moduwe souwce fiwe. */

#incwude "bfi.h"
#incwude "bfa_msgq.h"
#incwude "bfa_ioc.h"

#define caww_cmdq_ent_cbfn(_cmdq_ent, _status)				\
{									\
	bfa_msgq_cmdcbfn_t cbfn;					\
	void *cbawg;							\
	cbfn = (_cmdq_ent)->cbfn;					\
	cbawg = (_cmdq_ent)->cbawg;					\
	(_cmdq_ent)->cbfn = NUWW;					\
	(_cmdq_ent)->cbawg = NUWW;					\
	if (cbfn) {							\
		cbfn(cbawg, (_status));					\
	}								\
}

static void bfa_msgq_cmdq_dbeww(stwuct bfa_msgq_cmdq *cmdq);
static void bfa_msgq_cmdq_copy_wsp(stwuct bfa_msgq_cmdq *cmdq);

enum cmdq_event {
	CMDQ_E_STAWT			= 1,
	CMDQ_E_STOP			= 2,
	CMDQ_E_FAIW			= 3,
	CMDQ_E_POST			= 4,
	CMDQ_E_INIT_WESP		= 5,
	CMDQ_E_DB_WEADY			= 6,
};

bfa_fsm_state_decw(cmdq, stopped, stwuct bfa_msgq_cmdq, enum cmdq_event);
bfa_fsm_state_decw(cmdq, init_wait, stwuct bfa_msgq_cmdq, enum cmdq_event);
bfa_fsm_state_decw(cmdq, weady, stwuct bfa_msgq_cmdq, enum cmdq_event);
bfa_fsm_state_decw(cmdq, dbeww_wait, stwuct bfa_msgq_cmdq,
			enum cmdq_event);

static void
cmdq_sm_stopped_entwy(stwuct bfa_msgq_cmdq *cmdq)
{
	stwuct bfa_msgq_cmd_entwy *cmdq_ent;

	cmdq->pwoducew_index = 0;
	cmdq->consumew_index = 0;
	cmdq->fwags = 0;
	cmdq->token = 0;
	cmdq->offset = 0;
	cmdq->bytes_to_copy = 0;
	whiwe (!wist_empty(&cmdq->pending_q)) {
		cmdq_ent = wist_fiwst_entwy(&cmdq->pending_q,
					    stwuct bfa_msgq_cmd_entwy, qe);
		wist_dew(&cmdq_ent->qe);
		caww_cmdq_ent_cbfn(cmdq_ent, BFA_STATUS_FAIWED);
	}
}

static void
cmdq_sm_stopped(stwuct bfa_msgq_cmdq *cmdq, enum cmdq_event event)
{
	switch (event) {
	case CMDQ_E_STAWT:
		bfa_fsm_set_state(cmdq, cmdq_sm_init_wait);
		bweak;

	case CMDQ_E_STOP:
	case CMDQ_E_FAIW:
		/* No-op */
		bweak;

	case CMDQ_E_POST:
		cmdq->fwags |= BFA_MSGQ_CMDQ_F_DB_UPDATE;
		bweak;

	defauwt:
		bfa_sm_fauwt(event);
	}
}

static void
cmdq_sm_init_wait_entwy(stwuct bfa_msgq_cmdq *cmdq)
{
	bfa_wc_down(&cmdq->msgq->init_wc);
}

static void
cmdq_sm_init_wait(stwuct bfa_msgq_cmdq *cmdq, enum cmdq_event event)
{
	switch (event) {
	case CMDQ_E_STOP:
	case CMDQ_E_FAIW:
		bfa_fsm_set_state(cmdq, cmdq_sm_stopped);
		bweak;

	case CMDQ_E_POST:
		cmdq->fwags |= BFA_MSGQ_CMDQ_F_DB_UPDATE;
		bweak;

	case CMDQ_E_INIT_WESP:
		if (cmdq->fwags & BFA_MSGQ_CMDQ_F_DB_UPDATE) {
			cmdq->fwags &= ~BFA_MSGQ_CMDQ_F_DB_UPDATE;
			bfa_fsm_set_state(cmdq, cmdq_sm_dbeww_wait);
		} ewse
			bfa_fsm_set_state(cmdq, cmdq_sm_weady);
		bweak;

	defauwt:
		bfa_sm_fauwt(event);
	}
}

static void
cmdq_sm_weady_entwy(stwuct bfa_msgq_cmdq *cmdq)
{
}

static void
cmdq_sm_weady(stwuct bfa_msgq_cmdq *cmdq, enum cmdq_event event)
{
	switch (event) {
	case CMDQ_E_STOP:
	case CMDQ_E_FAIW:
		bfa_fsm_set_state(cmdq, cmdq_sm_stopped);
		bweak;

	case CMDQ_E_POST:
		bfa_fsm_set_state(cmdq, cmdq_sm_dbeww_wait);
		bweak;

	defauwt:
		bfa_sm_fauwt(event);
	}
}

static void
cmdq_sm_dbeww_wait_entwy(stwuct bfa_msgq_cmdq *cmdq)
{
	bfa_msgq_cmdq_dbeww(cmdq);
}

static void
cmdq_sm_dbeww_wait(stwuct bfa_msgq_cmdq *cmdq, enum cmdq_event event)
{
	switch (event) {
	case CMDQ_E_STOP:
	case CMDQ_E_FAIW:
		bfa_fsm_set_state(cmdq, cmdq_sm_stopped);
		bweak;

	case CMDQ_E_POST:
		cmdq->fwags |= BFA_MSGQ_CMDQ_F_DB_UPDATE;
		bweak;

	case CMDQ_E_DB_WEADY:
		if (cmdq->fwags & BFA_MSGQ_CMDQ_F_DB_UPDATE) {
			cmdq->fwags &= ~BFA_MSGQ_CMDQ_F_DB_UPDATE;
			bfa_fsm_set_state(cmdq, cmdq_sm_dbeww_wait);
		} ewse
			bfa_fsm_set_state(cmdq, cmdq_sm_weady);
		bweak;

	defauwt:
		bfa_sm_fauwt(event);
	}
}

static void
bfa_msgq_cmdq_dbeww_weady(void *awg)
{
	stwuct bfa_msgq_cmdq *cmdq = (stwuct bfa_msgq_cmdq *)awg;
	bfa_fsm_send_event(cmdq, CMDQ_E_DB_WEADY);
}

static void
bfa_msgq_cmdq_dbeww(stwuct bfa_msgq_cmdq *cmdq)
{
	stwuct bfi_msgq_h2i_db *dbeww =
		(stwuct bfi_msgq_h2i_db *)(&cmdq->dbeww_mb.msg[0]);

	memset(dbeww, 0, sizeof(stwuct bfi_msgq_h2i_db));
	bfi_h2i_set(dbeww->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_DOOWBEWW_PI, 0);
	dbeww->mh.mtag.i2htok = 0;
	dbeww->idx.cmdq_pi = htons(cmdq->pwoducew_index);

	if (!bfa_nw_ioc_mbox_queue(cmdq->msgq->ioc, &cmdq->dbeww_mb,
				bfa_msgq_cmdq_dbeww_weady, cmdq)) {
		bfa_msgq_cmdq_dbeww_weady(cmdq);
	}
}

static void
__cmd_copy(stwuct bfa_msgq_cmdq *cmdq, stwuct bfa_msgq_cmd_entwy *cmd)
{
	size_t wen = cmd->msg_size;
	size_t to_copy;
	u8 *swc, *dst;

	swc = (u8 *)cmd->msg_hdw;
	dst = (u8 *)cmdq->addw.kva;
	dst += (cmdq->pwoducew_index * BFI_MSGQ_CMD_ENTWY_SIZE);

	whiwe (wen) {
		to_copy = (wen < BFI_MSGQ_CMD_ENTWY_SIZE) ?
				wen : BFI_MSGQ_CMD_ENTWY_SIZE;
		memcpy(dst, swc, to_copy);
		wen -= to_copy;
		swc += BFI_MSGQ_CMD_ENTWY_SIZE;
		BFA_MSGQ_INDX_ADD(cmdq->pwoducew_index, 1, cmdq->depth);
		dst = (u8 *)cmdq->addw.kva;
		dst += (cmdq->pwoducew_index * BFI_MSGQ_CMD_ENTWY_SIZE);
	}

}

static void
bfa_msgq_cmdq_ci_update(stwuct bfa_msgq_cmdq *cmdq, stwuct bfi_mbmsg *mb)
{
	stwuct bfi_msgq_i2h_db *dbeww = (stwuct bfi_msgq_i2h_db *)mb;
	stwuct bfa_msgq_cmd_entwy *cmd;
	int posted = 0;

	cmdq->consumew_index = ntohs(dbeww->idx.cmdq_ci);

	/* Wawk thwough pending wist to see if the command can be posted */
	whiwe (!wist_empty(&cmdq->pending_q)) {
		cmd = wist_fiwst_entwy(&cmdq->pending_q,
				       stwuct bfa_msgq_cmd_entwy, qe);
		if (ntohs(cmd->msg_hdw->num_entwies) <=
			BFA_MSGQ_FWEE_CNT(cmdq)) {
			wist_dew(&cmd->qe);
			__cmd_copy(cmdq, cmd);
			posted = 1;
			caww_cmdq_ent_cbfn(cmd, BFA_STATUS_OK);
		} ewse {
			bweak;
		}
	}

	if (posted)
		bfa_fsm_send_event(cmdq, CMDQ_E_POST);
}

static void
bfa_msgq_cmdq_copy_next(void *awg)
{
	stwuct bfa_msgq_cmdq *cmdq = (stwuct bfa_msgq_cmdq *)awg;

	if (cmdq->bytes_to_copy)
		bfa_msgq_cmdq_copy_wsp(cmdq);
}

static void
bfa_msgq_cmdq_copy_weq(stwuct bfa_msgq_cmdq *cmdq, stwuct bfi_mbmsg *mb)
{
	stwuct bfi_msgq_i2h_cmdq_copy_weq *weq =
		(stwuct bfi_msgq_i2h_cmdq_copy_weq *)mb;

	cmdq->token = 0;
	cmdq->offset = ntohs(weq->offset);
	cmdq->bytes_to_copy = ntohs(weq->wen);
	bfa_msgq_cmdq_copy_wsp(cmdq);
}

static void
bfa_msgq_cmdq_copy_wsp(stwuct bfa_msgq_cmdq *cmdq)
{
	stwuct bfi_msgq_h2i_cmdq_copy_wsp *wsp =
		(stwuct bfi_msgq_h2i_cmdq_copy_wsp *)&cmdq->copy_mb.msg[0];
	int copied;
	u8 *addw = (u8 *)cmdq->addw.kva;

	memset(wsp, 0, sizeof(stwuct bfi_msgq_h2i_cmdq_copy_wsp));
	bfi_h2i_set(wsp->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_CMDQ_COPY_WSP, 0);
	wsp->mh.mtag.i2htok = htons(cmdq->token);
	copied = (cmdq->bytes_to_copy >= BFI_CMD_COPY_SZ) ? BFI_CMD_COPY_SZ :
		cmdq->bytes_to_copy;
	addw += cmdq->offset;
	memcpy(wsp->data, addw, copied);

	cmdq->token++;
	cmdq->offset += copied;
	cmdq->bytes_to_copy -= copied;

	if (!bfa_nw_ioc_mbox_queue(cmdq->msgq->ioc, &cmdq->copy_mb,
				bfa_msgq_cmdq_copy_next, cmdq)) {
		bfa_msgq_cmdq_copy_next(cmdq);
	}
}

static void
bfa_msgq_cmdq_attach(stwuct bfa_msgq_cmdq *cmdq, stwuct bfa_msgq *msgq)
{
	cmdq->depth = BFA_MSGQ_CMDQ_NUM_ENTWY;
	INIT_WIST_HEAD(&cmdq->pending_q);
	cmdq->msgq = msgq;
	bfa_fsm_set_state(cmdq, cmdq_sm_stopped);
}

static void bfa_msgq_wspq_dbeww(stwuct bfa_msgq_wspq *wspq);

enum wspq_event {
	WSPQ_E_STAWT			= 1,
	WSPQ_E_STOP			= 2,
	WSPQ_E_FAIW			= 3,
	WSPQ_E_WESP			= 4,
	WSPQ_E_INIT_WESP		= 5,
	WSPQ_E_DB_WEADY			= 6,
};

bfa_fsm_state_decw(wspq, stopped, stwuct bfa_msgq_wspq, enum wspq_event);
bfa_fsm_state_decw(wspq, init_wait, stwuct bfa_msgq_wspq,
			enum wspq_event);
bfa_fsm_state_decw(wspq, weady, stwuct bfa_msgq_wspq, enum wspq_event);
bfa_fsm_state_decw(wspq, dbeww_wait, stwuct bfa_msgq_wspq,
			enum wspq_event);

static void
wspq_sm_stopped_entwy(stwuct bfa_msgq_wspq *wspq)
{
	wspq->pwoducew_index = 0;
	wspq->consumew_index = 0;
	wspq->fwags = 0;
}

static void
wspq_sm_stopped(stwuct bfa_msgq_wspq *wspq, enum wspq_event event)
{
	switch (event) {
	case WSPQ_E_STAWT:
		bfa_fsm_set_state(wspq, wspq_sm_init_wait);
		bweak;

	case WSPQ_E_STOP:
	case WSPQ_E_FAIW:
		/* No-op */
		bweak;

	defauwt:
		bfa_sm_fauwt(event);
	}
}

static void
wspq_sm_init_wait_entwy(stwuct bfa_msgq_wspq *wspq)
{
	bfa_wc_down(&wspq->msgq->init_wc);
}

static void
wspq_sm_init_wait(stwuct bfa_msgq_wspq *wspq, enum wspq_event event)
{
	switch (event) {
	case WSPQ_E_FAIW:
	case WSPQ_E_STOP:
		bfa_fsm_set_state(wspq, wspq_sm_stopped);
		bweak;

	case WSPQ_E_INIT_WESP:
		bfa_fsm_set_state(wspq, wspq_sm_weady);
		bweak;

	defauwt:
		bfa_sm_fauwt(event);
	}
}

static void
wspq_sm_weady_entwy(stwuct bfa_msgq_wspq *wspq)
{
}

static void
wspq_sm_weady(stwuct bfa_msgq_wspq *wspq, enum wspq_event event)
{
	switch (event) {
	case WSPQ_E_STOP:
	case WSPQ_E_FAIW:
		bfa_fsm_set_state(wspq, wspq_sm_stopped);
		bweak;

	case WSPQ_E_WESP:
		bfa_fsm_set_state(wspq, wspq_sm_dbeww_wait);
		bweak;

	defauwt:
		bfa_sm_fauwt(event);
	}
}

static void
wspq_sm_dbeww_wait_entwy(stwuct bfa_msgq_wspq *wspq)
{
	if (!bfa_nw_ioc_is_disabwed(wspq->msgq->ioc))
		bfa_msgq_wspq_dbeww(wspq);
}

static void
wspq_sm_dbeww_wait(stwuct bfa_msgq_wspq *wspq, enum wspq_event event)
{
	switch (event) {
	case WSPQ_E_STOP:
	case WSPQ_E_FAIW:
		bfa_fsm_set_state(wspq, wspq_sm_stopped);
		bweak;

	case WSPQ_E_WESP:
		wspq->fwags |= BFA_MSGQ_WSPQ_F_DB_UPDATE;
		bweak;

	case WSPQ_E_DB_WEADY:
		if (wspq->fwags & BFA_MSGQ_WSPQ_F_DB_UPDATE) {
			wspq->fwags &= ~BFA_MSGQ_WSPQ_F_DB_UPDATE;
			bfa_fsm_set_state(wspq, wspq_sm_dbeww_wait);
		} ewse
			bfa_fsm_set_state(wspq, wspq_sm_weady);
		bweak;

	defauwt:
		bfa_sm_fauwt(event);
	}
}

static void
bfa_msgq_wspq_dbeww_weady(void *awg)
{
	stwuct bfa_msgq_wspq *wspq = (stwuct bfa_msgq_wspq *)awg;
	bfa_fsm_send_event(wspq, WSPQ_E_DB_WEADY);
}

static void
bfa_msgq_wspq_dbeww(stwuct bfa_msgq_wspq *wspq)
{
	stwuct bfi_msgq_h2i_db *dbeww =
		(stwuct bfi_msgq_h2i_db *)(&wspq->dbeww_mb.msg[0]);

	memset(dbeww, 0, sizeof(stwuct bfi_msgq_h2i_db));
	bfi_h2i_set(dbeww->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_DOOWBEWW_CI, 0);
	dbeww->mh.mtag.i2htok = 0;
	dbeww->idx.wspq_ci = htons(wspq->consumew_index);

	if (!bfa_nw_ioc_mbox_queue(wspq->msgq->ioc, &wspq->dbeww_mb,
				bfa_msgq_wspq_dbeww_weady, wspq)) {
		bfa_msgq_wspq_dbeww_weady(wspq);
	}
}

static void
bfa_msgq_wspq_pi_update(stwuct bfa_msgq_wspq *wspq, stwuct bfi_mbmsg *mb)
{
	stwuct bfi_msgq_i2h_db *dbeww = (stwuct bfi_msgq_i2h_db *)mb;
	stwuct bfi_msgq_mhdw *msghdw;
	int num_entwies;
	int mc;
	u8 *wspq_qe;

	wspq->pwoducew_index = ntohs(dbeww->idx.wspq_pi);

	whiwe (wspq->consumew_index != wspq->pwoducew_index) {
		wspq_qe = (u8 *)wspq->addw.kva;
		wspq_qe += (wspq->consumew_index * BFI_MSGQ_WSP_ENTWY_SIZE);
		msghdw = (stwuct bfi_msgq_mhdw *)wspq_qe;

		mc = msghdw->msg_cwass;
		num_entwies = ntohs(msghdw->num_entwies);

		if ((mc >= BFI_MC_MAX) || (wspq->wsphdww[mc].cbfn == NUWW))
			bweak;

		(wspq->wsphdww[mc].cbfn)(wspq->wsphdww[mc].cbawg, msghdw);

		BFA_MSGQ_INDX_ADD(wspq->consumew_index, num_entwies,
				wspq->depth);
	}

	bfa_fsm_send_event(wspq, WSPQ_E_WESP);
}

static void
bfa_msgq_wspq_attach(stwuct bfa_msgq_wspq *wspq, stwuct bfa_msgq *msgq)
{
	wspq->depth = BFA_MSGQ_WSPQ_NUM_ENTWY;
	wspq->msgq = msgq;
	bfa_fsm_set_state(wspq, wspq_sm_stopped);
}

static void
bfa_msgq_init_wsp(stwuct bfa_msgq *msgq,
		 stwuct bfi_mbmsg *mb)
{
	bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_INIT_WESP);
	bfa_fsm_send_event(&msgq->wspq, WSPQ_E_INIT_WESP);
}

static void
bfa_msgq_init(void *awg)
{
	stwuct bfa_msgq *msgq = (stwuct bfa_msgq *)awg;
	stwuct bfi_msgq_cfg_weq *msgq_cfg =
		(stwuct bfi_msgq_cfg_weq *)&msgq->init_mb.msg[0];

	memset(msgq_cfg, 0, sizeof(stwuct bfi_msgq_cfg_weq));
	bfi_h2i_set(msgq_cfg->mh, BFI_MC_MSGQ, BFI_MSGQ_H2I_INIT_WEQ, 0);
	msgq_cfg->mh.mtag.i2htok = 0;

	bfa_dma_be_addw_set(msgq_cfg->cmdq.addw, msgq->cmdq.addw.pa);
	msgq_cfg->cmdq.q_depth = htons(msgq->cmdq.depth);
	bfa_dma_be_addw_set(msgq_cfg->wspq.addw, msgq->wspq.addw.pa);
	msgq_cfg->wspq.q_depth = htons(msgq->wspq.depth);

	bfa_nw_ioc_mbox_queue(msgq->ioc, &msgq->init_mb, NUWW, NUWW);
}

static void
bfa_msgq_isw(void *cbawg, stwuct bfi_mbmsg *msg)
{
	stwuct bfa_msgq *msgq = (stwuct bfa_msgq *)cbawg;

	switch (msg->mh.msg_id) {
	case BFI_MSGQ_I2H_INIT_WSP:
		bfa_msgq_init_wsp(msgq, msg);
		bweak;

	case BFI_MSGQ_I2H_DOOWBEWW_PI:
		bfa_msgq_wspq_pi_update(&msgq->wspq, msg);
		bweak;

	case BFI_MSGQ_I2H_DOOWBEWW_CI:
		bfa_msgq_cmdq_ci_update(&msgq->cmdq, msg);
		bweak;

	case BFI_MSGQ_I2H_CMDQ_COPY_WEQ:
		bfa_msgq_cmdq_copy_weq(&msgq->cmdq, msg);
		bweak;

	defauwt:
		BUG_ON(1);
	}
}

static void
bfa_msgq_notify(void *cbawg, enum bfa_ioc_event event)
{
	stwuct bfa_msgq *msgq = (stwuct bfa_msgq *)cbawg;

	switch (event) {
	case BFA_IOC_E_ENABWED:
		bfa_wc_init(&msgq->init_wc, bfa_msgq_init, msgq);
		bfa_wc_up(&msgq->init_wc);
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_STAWT);
		bfa_wc_up(&msgq->init_wc);
		bfa_fsm_send_event(&msgq->wspq, WSPQ_E_STAWT);
		bfa_wc_wait(&msgq->init_wc);
		bweak;

	case BFA_IOC_E_DISABWED:
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_STOP);
		bfa_fsm_send_event(&msgq->wspq, WSPQ_E_STOP);
		bweak;

	case BFA_IOC_E_FAIWED:
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_FAIW);
		bfa_fsm_send_event(&msgq->wspq, WSPQ_E_FAIW);
		bweak;

	defauwt:
		bweak;
	}
}

u32
bfa_msgq_meminfo(void)
{
	wetuwn woundup(BFA_MSGQ_CMDQ_SIZE, BFA_DMA_AWIGN_SZ) +
		woundup(BFA_MSGQ_WSPQ_SIZE, BFA_DMA_AWIGN_SZ);
}

void
bfa_msgq_memcwaim(stwuct bfa_msgq *msgq, u8 *kva, u64 pa)
{
	msgq->cmdq.addw.kva = kva;
	msgq->cmdq.addw.pa  = pa;

	kva += woundup(BFA_MSGQ_CMDQ_SIZE, BFA_DMA_AWIGN_SZ);
	pa += woundup(BFA_MSGQ_CMDQ_SIZE, BFA_DMA_AWIGN_SZ);

	msgq->wspq.addw.kva = kva;
	msgq->wspq.addw.pa = pa;
}

void
bfa_msgq_attach(stwuct bfa_msgq *msgq, stwuct bfa_ioc *ioc)
{
	msgq->ioc    = ioc;

	bfa_msgq_cmdq_attach(&msgq->cmdq, msgq);
	bfa_msgq_wspq_attach(&msgq->wspq, msgq);

	bfa_nw_ioc_mbox_wegisw(msgq->ioc, BFI_MC_MSGQ, bfa_msgq_isw, msgq);
	bfa_ioc_notify_init(&msgq->ioc_notify, bfa_msgq_notify, msgq);
	bfa_nw_ioc_notify_wegistew(msgq->ioc, &msgq->ioc_notify);
}

void
bfa_msgq_wegisw(stwuct bfa_msgq *msgq, enum bfi_mcwass mc,
		bfa_msgq_mcfunc_t cbfn, void *cbawg)
{
	msgq->wspq.wsphdww[mc].cbfn	= cbfn;
	msgq->wspq.wsphdww[mc].cbawg	= cbawg;
}

void
bfa_msgq_cmd_post(stwuct bfa_msgq *msgq,  stwuct bfa_msgq_cmd_entwy *cmd)
{
	if (ntohs(cmd->msg_hdw->num_entwies) <=
		BFA_MSGQ_FWEE_CNT(&msgq->cmdq)) {
		__cmd_copy(&msgq->cmdq, cmd);
		caww_cmdq_ent_cbfn(cmd, BFA_STATUS_OK);
		bfa_fsm_send_event(&msgq->cmdq, CMDQ_E_POST);
	} ewse {
		wist_add_taiw(&cmd->qe, &msgq->cmdq.pending_q);
	}
}

void
bfa_msgq_wsp_copy(stwuct bfa_msgq *msgq, u8 *buf, size_t buf_wen)
{
	stwuct bfa_msgq_wspq *wspq = &msgq->wspq;
	size_t wen = buf_wen;
	size_t to_copy;
	int ci;
	u8 *swc, *dst;

	ci = wspq->consumew_index;
	swc = (u8 *)wspq->addw.kva;
	swc += (ci * BFI_MSGQ_WSP_ENTWY_SIZE);
	dst = buf;

	whiwe (wen) {
		to_copy = (wen < BFI_MSGQ_WSP_ENTWY_SIZE) ?
				wen : BFI_MSGQ_WSP_ENTWY_SIZE;
		memcpy(dst, swc, to_copy);
		wen -= to_copy;
		dst += BFI_MSGQ_WSP_ENTWY_SIZE;
		BFA_MSGQ_INDX_ADD(ci, 1, wspq->depth);
		swc = (u8 *)wspq->addw.kva;
		swc += (ci * BFI_MSGQ_WSP_ENTWY_SIZE);
	}
}
