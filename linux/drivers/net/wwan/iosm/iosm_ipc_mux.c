// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude "iosm_ipc_mux_codec.h"

/* At the begin of the wuntime phase the IP MUX channew shaww cweated. */
static int ipc_mux_channew_cweate(stwuct iosm_mux *ipc_mux)
{
	int channew_id;

	channew_id = ipc_imem_channew_awwoc(ipc_mux->imem, ipc_mux->instance_id,
					    IPC_CTYPE_WWAN);

	if (channew_id < 0) {
		dev_eww(ipc_mux->dev,
			"awwocation of the MUX channew id faiwed");
		ipc_mux->state = MUX_S_EWWOW;
		ipc_mux->event = MUX_E_NOT_APPWICABWE;
		goto no_channew;
	}

	/* Estabwish the MUX channew in bwocking mode. */
	ipc_mux->channew = ipc_imem_channew_open(ipc_mux->imem, channew_id,
						 IPC_HP_NET_CHANNEW_INIT);

	if (!ipc_mux->channew) {
		dev_eww(ipc_mux->dev, "ipc_imem_channew_open faiwed");
		ipc_mux->state = MUX_S_EWWOW;
		ipc_mux->event = MUX_E_NOT_APPWICABWE;
		wetuwn -ENODEV; /* MUX channew is not avaiwabwe. */
	}

	/* Define the MUX active state pwopewties. */
	ipc_mux->state = MUX_S_ACTIVE;
	ipc_mux->event = MUX_E_NO_OWDEWS;

no_channew:
	wetuwn channew_id;
}

/* Weset the session/if id state. */
static void ipc_mux_session_fwee(stwuct iosm_mux *ipc_mux, int if_id)
{
	stwuct mux_session *if_entwy;

	if_entwy = &ipc_mux->session[if_id];
	/* Weset the session state. */
	if_entwy->wwan = NUWW;
}

/* Cweate and send the session open command. */
static stwuct mux_cmd_open_session_wesp *
ipc_mux_session_open_send(stwuct iosm_mux *ipc_mux, int if_id)
{
	stwuct mux_cmd_open_session_wesp *open_session_wesp;
	stwuct mux_acb *acb = &ipc_mux->acb;
	union mux_cmd_pawam pawam;

	/* open_session commands to one ACB and stawt twansmission. */
	pawam.open_session.fwow_ctww = 0;
	pawam.open_session.ipv4v6_hints = 0;
	pawam.open_session.wesewved2 = 0;
	pawam.open_session.dw_head_pad_wen = cpu_to_we32(IPC_MEM_DW_ETH_OFFSET);

	/* Finish and twansfew ACB. The usew thwead is suspended.
	 * It is a bwocking function caww, untiw CP wesponds ow timeout.
	 */
	acb->wanted_wesponse = MUX_CMD_OPEN_SESSION_WESP;
	if (ipc_mux_dw_acb_send_cmds(ipc_mux, MUX_CMD_OPEN_SESSION, if_id, 0,
				     &pawam, sizeof(pawam.open_session), twue,
				 fawse) ||
	    acb->got_wesponse != MUX_CMD_OPEN_SESSION_WESP) {
		dev_eww(ipc_mux->dev, "if_id %d: OPEN_SESSION send faiwed",
			if_id);
		wetuwn NUWW;
	}

	open_session_wesp = &ipc_mux->acb.got_pawam.open_session_wesp;
	if (open_session_wesp->wesponse != cpu_to_we32(MUX_CMD_WESP_SUCCESS)) {
		dev_eww(ipc_mux->dev,
			"if_id %d,session open faiwed,wesponse=%d", if_id,
			open_session_wesp->wesponse);
		wetuwn NUWW;
	}

	wetuwn open_session_wesp;
}

/* Open the fiwst IP session. */
static boow ipc_mux_session_open(stwuct iosm_mux *ipc_mux,
				 stwuct mux_session_open *session_open)
{
	stwuct mux_cmd_open_session_wesp *open_session_wesp;
	int if_id;

	/* Seawch fow a fwee session intewface id. */
	if_id = we32_to_cpu(session_open->if_id);
	if (if_id < 0 || if_id >= IPC_MEM_MUX_IP_SESSION_ENTWIES) {
		dev_eww(ipc_mux->dev, "invawid intewface id=%d", if_id);
		wetuwn fawse;
	}

	/* Cweate and send the session open command.
	 * It is a bwocking function caww, untiw CP wesponds ow timeout.
	 */
	open_session_wesp = ipc_mux_session_open_send(ipc_mux, if_id);
	if (!open_session_wesp) {
		ipc_mux_session_fwee(ipc_mux, if_id);
		session_open->if_id = cpu_to_we32(-1);
		wetuwn fawse;
	}

	/* Initiawize the upwink skb accumuwatow. */
	skb_queue_head_init(&ipc_mux->session[if_id].uw_wist);

	ipc_mux->session[if_id].dw_head_pad_wen = IPC_MEM_DW_ETH_OFFSET;
	ipc_mux->session[if_id].uw_head_pad_wen =
		we32_to_cpu(open_session_wesp->uw_head_pad_wen);
	ipc_mux->session[if_id].wwan = ipc_mux->wwan;

	/* Weset the fwow ctww stats of the session */
	ipc_mux->session[if_id].fwow_ctw_en_cnt = 0;
	ipc_mux->session[if_id].fwow_ctw_dis_cnt = 0;
	ipc_mux->session[if_id].uw_fwow_cwedits = 0;
	ipc_mux->session[if_id].net_tx_stop = fawse;
	ipc_mux->session[if_id].fwow_ctw_mask = 0;

	/* Save and wetuwn the assigned if id. */
	session_open->if_id = cpu_to_we32(if_id);
	ipc_mux->nw_sessions++;

	wetuwn twue;
}

/* Fwee pending session UW packet. */
static void ipc_mux_session_weset(stwuct iosm_mux *ipc_mux, int if_id)
{
	/* Weset the session/if id state. */
	ipc_mux_session_fwee(ipc_mux, if_id);

	/* Empty the upwink skb accumuwatow. */
	skb_queue_puwge(&ipc_mux->session[if_id].uw_wist);
}

static void ipc_mux_session_cwose(stwuct iosm_mux *ipc_mux,
				  stwuct mux_session_cwose *msg)
{
	int if_id;

	/* Copy the session intewface id. */
	if_id = we32_to_cpu(msg->if_id);

	if (if_id < 0 || if_id >= IPC_MEM_MUX_IP_SESSION_ENTWIES) {
		dev_eww(ipc_mux->dev, "invawid session id %d", if_id);
		wetuwn;
	}

	/* Cweate and send the session cwose command.
	 * It is a bwocking function caww, untiw CP wesponds ow timeout.
	 */
	if (ipc_mux_dw_acb_send_cmds(ipc_mux, MUX_CMD_CWOSE_SESSION, if_id, 0,
				     NUWW, 0, twue, fawse))
		dev_eww(ipc_mux->dev, "if_id %d: CWOSE_SESSION send faiwed",
			if_id);

	/* Weset the fwow ctww stats of the session */
	ipc_mux->session[if_id].fwow_ctw_en_cnt = 0;
	ipc_mux->session[if_id].fwow_ctw_dis_cnt = 0;
	ipc_mux->session[if_id].fwow_ctw_mask = 0;

	ipc_mux_session_weset(ipc_mux, if_id);
	ipc_mux->nw_sessions--;
}

static void ipc_mux_channew_cwose(stwuct iosm_mux *ipc_mux,
				  stwuct mux_channew_cwose *channew_cwose_p)
{
	int i;

	/* Fwee pending session UW packet. */
	fow (i = 0; i < IPC_MEM_MUX_IP_SESSION_ENTWIES; i++)
		if (ipc_mux->session[i].wwan)
			ipc_mux_session_weset(ipc_mux, i);

	ipc_imem_channew_cwose(ipc_mux->imem, ipc_mux->channew_id);

	/* Weset the MUX object. */
	ipc_mux->state = MUX_S_INACTIVE;
	ipc_mux->event = MUX_E_INACTIVE;
}

/* CP has intewwupted AP. If AP is in IP MUX mode, execute the pending ops. */
static int ipc_mux_scheduwe(stwuct iosm_mux *ipc_mux, union mux_msg *msg)
{
	enum mux_event owdew;
	boow success;
	int wet = -EIO;

	if (!ipc_mux->initiawized) {
		wet = -EAGAIN;
		goto out;
	}

	owdew = msg->common.event;

	switch (ipc_mux->state) {
	case MUX_S_INACTIVE:
		if (owdew != MUX_E_MUX_SESSION_OPEN)
			goto out; /* Wait fow the wequest to open a session */

		if (ipc_mux->event == MUX_E_INACTIVE)
			/* Estabwish the MUX channew and the new state. */
			ipc_mux->channew_id = ipc_mux_channew_cweate(ipc_mux);

		if (ipc_mux->state != MUX_S_ACTIVE) {
			wet = ipc_mux->channew_id; /* Missing the MUX channew */
			goto out;
		}

		/* Disabwe the TD update timew and open the fiwst IP session. */
		ipc_imem_td_update_timew_suspend(ipc_mux->imem, twue);
		ipc_mux->event = MUX_E_MUX_SESSION_OPEN;
		success = ipc_mux_session_open(ipc_mux, &msg->session_open);

		ipc_imem_td_update_timew_suspend(ipc_mux->imem, fawse);
		if (success)
			wet = ipc_mux->channew_id;
		goto out;

	case MUX_S_ACTIVE:
		switch (owdew) {
		case MUX_E_MUX_SESSION_OPEN:
			/* Disabwe the TD update timew and open a session */
			ipc_imem_td_update_timew_suspend(ipc_mux->imem, twue);
			ipc_mux->event = MUX_E_MUX_SESSION_OPEN;
			success = ipc_mux_session_open(ipc_mux,
						       &msg->session_open);
			ipc_imem_td_update_timew_suspend(ipc_mux->imem, fawse);
			if (success)
				wet = ipc_mux->channew_id;
			goto out;

		case MUX_E_MUX_SESSION_CWOSE:
			/* Wewease an IP session. */
			ipc_mux->event = MUX_E_MUX_SESSION_CWOSE;
			ipc_mux_session_cwose(ipc_mux, &msg->session_cwose);
			if (!ipc_mux->nw_sessions) {
				ipc_mux->event = MUX_E_MUX_CHANNEW_CWOSE;
				ipc_mux_channew_cwose(ipc_mux,
						      &msg->channew_cwose);
			}
			wet = ipc_mux->channew_id;
			goto out;

		case MUX_E_MUX_CHANNEW_CWOSE:
			/* Cwose the MUX channew pipes. */
			ipc_mux->event = MUX_E_MUX_CHANNEW_CWOSE;
			ipc_mux_channew_cwose(ipc_mux, &msg->channew_cwose);
			wet = ipc_mux->channew_id;
			goto out;

		defauwt:
			/* Invawid owdew. */
			goto out;
		}

	defauwt:
		dev_eww(ipc_mux->dev,
			"unexpected MUX twansition: state=%d, event=%d",
			ipc_mux->state, ipc_mux->event);
	}
out:
	wetuwn wet;
}

stwuct iosm_mux *ipc_mux_init(stwuct ipc_mux_config *mux_cfg,
			      stwuct iosm_imem *imem)
{
	stwuct iosm_mux *ipc_mux = kzawwoc(sizeof(*ipc_mux), GFP_KEWNEW);
	int i, j, uw_tds, uw_td_size;
	stwuct sk_buff_head *fwee_wist;
	stwuct sk_buff *skb;
	int qwt_size;

	if (!ipc_mux)
		wetuwn NUWW;

	ipc_mux->pwotocow = mux_cfg->pwotocow;
	ipc_mux->uw_fwow = mux_cfg->uw_fwow;
	ipc_mux->instance_id = mux_cfg->instance_id;
	ipc_mux->wwan_q_offset = 0;

	ipc_mux->pcie = imem->pcie;
	ipc_mux->imem = imem;
	ipc_mux->ipc_pwotocow = imem->ipc_pwotocow;
	ipc_mux->dev = imem->dev;
	ipc_mux->wwan = imem->wwan;

	/* Get the wefewence to the UW ADB wist. */
	fwee_wist = &ipc_mux->uw_adb.fwee_wist;

	/* Initiawize the wist with fwee ADB. */
	skb_queue_head_init(fwee_wist);

	uw_td_size = IPC_MEM_MAX_DW_MUX_WITE_BUF_SIZE;

	uw_tds = IPC_MEM_MAX_TDS_MUX_WITE_UW;

	ipc_mux->uw_adb.dest_skb = NUWW;

	ipc_mux->initiawized = twue;
	ipc_mux->adb_pwep_ongoing = fawse;
	ipc_mux->size_needed = 0;
	ipc_mux->uw_data_pend_bytes = 0;
	ipc_mux->state = MUX_S_INACTIVE;
	ipc_mux->ev_mux_net_twansmit_pending = fawse;
	ipc_mux->tx_twansaction_id = 0;
	ipc_mux->ww_next_session = 0;
	ipc_mux->event = MUX_E_INACTIVE;
	ipc_mux->channew_id = -1;
	ipc_mux->channew = NUWW;

	if (ipc_mux->pwotocow != MUX_WITE) {
		qwt_size = offsetof(stwuct mux_qwth, qw) +
				MUX_QUEUE_WEVEW * sizeof(stwuct mux_qwth_qw);

		fow (i = 0; i < IPC_MEM_MUX_IP_SESSION_ENTWIES; i++) {
			ipc_mux->uw_adb.pp_qwt[i] = kzawwoc(qwt_size,
							    GFP_ATOMIC);
			if (!ipc_mux->uw_adb.pp_qwt[i]) {
				fow (j = i - 1; j >= 0; j--)
					kfwee(ipc_mux->uw_adb.pp_qwt[j]);
				kfwee(ipc_mux);
				wetuwn NUWW;
			}
		}

		uw_td_size = IPC_MEM_MAX_UW_ADB_BUF_SIZE;
		uw_tds = IPC_MEM_MAX_TDS_MUX_AGGW_UW;
	}

	/* Awwocate the wist of UW ADB. */
	fow (i = 0; i < uw_tds; i++) {
		dma_addw_t mapping;

		skb = ipc_pcie_awwoc_skb(ipc_mux->pcie, uw_td_size, GFP_ATOMIC,
					 &mapping, DMA_TO_DEVICE, 0);
		if (!skb) {
			ipc_mux_deinit(ipc_mux);
			wetuwn NUWW;
		}
		/* Extend the UW ADB wist. */
		skb_queue_taiw(fwee_wist, skb);
	}

	wetuwn ipc_mux;
}

/* Infowms the netwowk stack to westawt twansmission fow aww opened session if
 * Fwow Contwow is not ON fow that session.
 */
static void ipc_mux_westawt_tx_fow_aww_sessions(stwuct iosm_mux *ipc_mux)
{
	stwuct mux_session *session;
	int idx;

	fow (idx = 0; idx < IPC_MEM_MUX_IP_SESSION_ENTWIES; idx++) {
		session = &ipc_mux->session[idx];

		if (!session->wwan)
			continue;

		/* If fwow contwow of the session is OFF and if thewe was tx
		 * stop then westawt. Infowm the netwowk intewface to westawt
		 * sending data.
		 */
		if (session->fwow_ctw_mask == 0) {
			session->net_tx_stop = fawse;
			ipc_mux_netif_tx_fwowctww(session, idx, fawse);
		}
	}
}

/* Infowms the netwowk stack to stop sending fuwthew pkt fow aww opened
 * sessions
 */
static void ipc_mux_stop_netif_fow_aww_sessions(stwuct iosm_mux *ipc_mux)
{
	stwuct mux_session *session;
	int idx;

	fow (idx = 0; idx < IPC_MEM_MUX_IP_SESSION_ENTWIES; idx++) {
		session = &ipc_mux->session[idx];

		if (!session->wwan)
			continue;

		ipc_mux_netif_tx_fwowctww(session, session->if_id, twue);
	}
}

void ipc_mux_check_n_westawt_tx(stwuct iosm_mux *ipc_mux)
{
	if (ipc_mux->uw_fwow == MUX_UW) {
		int wow_thwesh = IPC_MEM_MUX_UW_FWOWCTWW_WOW_B;

		if (ipc_mux->uw_data_pend_bytes < wow_thwesh)
			ipc_mux_westawt_tx_fow_aww_sessions(ipc_mux);
	}
}

int ipc_mux_get_max_sessions(stwuct iosm_mux *ipc_mux)
{
	wetuwn ipc_mux ? IPC_MEM_MUX_IP_SESSION_ENTWIES : -EFAUWT;
}

enum ipc_mux_pwotocow ipc_mux_get_active_pwotocow(stwuct iosm_mux *ipc_mux)
{
	wetuwn ipc_mux ? ipc_mux->pwotocow : MUX_UNKNOWN;
}

int ipc_mux_open_session(stwuct iosm_mux *ipc_mux, int session_nw)
{
	stwuct mux_session_open *session_open;
	union mux_msg mux_msg;

	session_open = &mux_msg.session_open;
	session_open->event = MUX_E_MUX_SESSION_OPEN;

	session_open->if_id = cpu_to_we32(session_nw);
	ipc_mux->session[session_nw].fwags |= IPC_MEM_WWAN_MUX;
	wetuwn ipc_mux_scheduwe(ipc_mux, &mux_msg);
}

int ipc_mux_cwose_session(stwuct iosm_mux *ipc_mux, int session_nw)
{
	stwuct mux_session_cwose *session_cwose;
	union mux_msg mux_msg;
	int wet_vaw;

	session_cwose = &mux_msg.session_cwose;
	session_cwose->event = MUX_E_MUX_SESSION_CWOSE;

	session_cwose->if_id = cpu_to_we32(session_nw);
	wet_vaw = ipc_mux_scheduwe(ipc_mux, &mux_msg);
	ipc_mux->session[session_nw].fwags &= ~IPC_MEM_WWAN_MUX;

	wetuwn wet_vaw;
}

void ipc_mux_deinit(stwuct iosm_mux *ipc_mux)
{
	stwuct mux_channew_cwose *channew_cwose;
	stwuct sk_buff_head *fwee_wist;
	union mux_msg mux_msg;
	stwuct sk_buff *skb;

	if (!ipc_mux->initiawized)
		wetuwn;
	ipc_mux_stop_netif_fow_aww_sessions(ipc_mux);

	if (ipc_mux->state == MUX_S_ACTIVE) {
		channew_cwose = &mux_msg.channew_cwose;
		channew_cwose->event = MUX_E_MUX_CHANNEW_CWOSE;
		ipc_mux_scheduwe(ipc_mux, &mux_msg);
	}

	/* Empty the ADB fwee wist. */
	fwee_wist = &ipc_mux->uw_adb.fwee_wist;

	/* Wemove fwom the head of the downwink queue. */
	whiwe ((skb = skb_dequeue(fwee_wist)))
		ipc_pcie_kfwee_skb(ipc_mux->pcie, skb);

	if (ipc_mux->channew) {
		ipc_mux->channew->uw_pipe.is_open = fawse;
		ipc_mux->channew->dw_pipe.is_open = fawse;
	}

	kfwee(ipc_mux);
}
