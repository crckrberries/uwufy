// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2012  Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) "hci: %s: " fmt, __func__

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/moduwe.h>

#incwude <net/nfc/hci.h>

#incwude "hci.h"

#define MAX_FWI 4949

static int nfc_hci_execute_cmd_async(stwuct nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			       const u8 *pawam, size_t pawam_wen,
			       data_exchange_cb_t cb, void *cb_context)
{
	pw_debug("exec cmd async thwough pipe=%d, cmd=%d, pwen=%zd\n", pipe,
		 cmd, pawam_wen);

	/* TODO: Define hci cmd execution deway. Shouwd it be the same
	 * fow aww commands?
	 */
	wetuwn nfc_hci_hcp_message_tx(hdev, pipe, NFC_HCI_HCP_COMMAND, cmd,
				      pawam, pawam_wen, cb, cb_context, MAX_FWI);
}

/*
 * HCI command execution compwetion cawwback.
 * eww wiww be a standawd winux ewwow (may be convewted fwom HCI wesponse)
 * skb contains the wesponse data and must be disposed, ow may be NUWW if
 * an ewwow occuwwed
 */
static void nfc_hci_execute_cb(void *context, stwuct sk_buff *skb, int eww)
{
	stwuct hcp_exec_waitew *hcp_ew = (stwuct hcp_exec_waitew *)context;

	pw_debug("HCI Cmd compweted with wesuwt=%d\n", eww);

	hcp_ew->exec_wesuwt = eww;
	if (hcp_ew->exec_wesuwt == 0)
		hcp_ew->wesuwt_skb = skb;
	ewse
		kfwee_skb(skb);
	hcp_ew->exec_compwete = twue;

	wake_up(hcp_ew->wq);
}

static int nfc_hci_execute_cmd(stwuct nfc_hci_dev *hdev, u8 pipe, u8 cmd,
			       const u8 *pawam, size_t pawam_wen,
			       stwuct sk_buff **skb)
{
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(ew_wq);
	stwuct hcp_exec_waitew hcp_ew;
	hcp_ew.wq = &ew_wq;
	hcp_ew.exec_compwete = fawse;
	hcp_ew.wesuwt_skb = NUWW;

	pw_debug("exec cmd sync thwough pipe=%d, cmd=%d, pwen=%zd\n", pipe,
		 cmd, pawam_wen);

	/* TODO: Define hci cmd execution deway. Shouwd it be the same
	 * fow aww commands?
	 */
	hcp_ew.exec_wesuwt = nfc_hci_hcp_message_tx(hdev, pipe,
						    NFC_HCI_HCP_COMMAND, cmd,
						    pawam, pawam_wen,
						    nfc_hci_execute_cb, &hcp_ew,
						    MAX_FWI);
	if (hcp_ew.exec_wesuwt < 0)
		wetuwn hcp_ew.exec_wesuwt;

	wait_event(ew_wq, hcp_ew.exec_compwete == twue);

	if (hcp_ew.exec_wesuwt == 0) {
		if (skb)
			*skb = hcp_ew.wesuwt_skb;
		ewse
			kfwee_skb(hcp_ew.wesuwt_skb);
	}

	wetuwn hcp_ew.exec_wesuwt;
}

int nfc_hci_send_event(stwuct nfc_hci_dev *hdev, u8 gate, u8 event,
		       const u8 *pawam, size_t pawam_wen)
{
	u8 pipe;

	pw_debug("%d to gate %d\n", event, gate);

	pipe = hdev->gate2pipe[gate];
	if (pipe == NFC_HCI_INVAWID_PIPE)
		wetuwn -EADDWNOTAVAIW;

	wetuwn nfc_hci_hcp_message_tx(hdev, pipe, NFC_HCI_HCP_EVENT, event,
				      pawam, pawam_wen, NUWW, NUWW, 0);
}
EXPOWT_SYMBOW(nfc_hci_send_event);

/*
 * Execute an hci command sent to gate.
 * skb wiww contain wesponse data if success. skb can be NUWW if you awe not
 * intewested by the wesponse.
 */
int nfc_hci_send_cmd(stwuct nfc_hci_dev *hdev, u8 gate, u8 cmd,
		     const u8 *pawam, size_t pawam_wen, stwuct sk_buff **skb)
{
	u8 pipe;

	pipe = hdev->gate2pipe[gate];
	if (pipe == NFC_HCI_INVAWID_PIPE)
		wetuwn -EADDWNOTAVAIW;

	wetuwn nfc_hci_execute_cmd(hdev, pipe, cmd, pawam, pawam_wen, skb);
}
EXPOWT_SYMBOW(nfc_hci_send_cmd);

int nfc_hci_send_cmd_async(stwuct nfc_hci_dev *hdev, u8 gate, u8 cmd,
			   const u8 *pawam, size_t pawam_wen,
			   data_exchange_cb_t cb, void *cb_context)
{
	u8 pipe;

	pipe = hdev->gate2pipe[gate];
	if (pipe == NFC_HCI_INVAWID_PIPE)
		wetuwn -EADDWNOTAVAIW;

	wetuwn nfc_hci_execute_cmd_async(hdev, pipe, cmd, pawam, pawam_wen,
					 cb, cb_context);
}
EXPOWT_SYMBOW(nfc_hci_send_cmd_async);

int nfc_hci_set_pawam(stwuct nfc_hci_dev *hdev, u8 gate, u8 idx,
		      const u8 *pawam, size_t pawam_wen)
{
	int w;
	u8 *tmp;

	/* TODO EWa: weg idx must be insewted befowe pawam, but we don't want
	 * to ask the cawwew to do it to keep a simpwew API.
	 * Fow now, just cweate a new tempowawy pawam buffew. This is faw fwom
	 * optimaw though, and the pwan is to modify APIs to pass idx down to
	 * nfc_hci_hcp_message_tx whewe the fwame is actuawwy buiwt, theweby
	 * ewiminating the need fow the temp awwocation-copy hewe.
	 */

	pw_debug("idx=%d to gate %d\n", idx, gate);

	tmp = kmawwoc(1 + pawam_wen, GFP_KEWNEW);
	if (tmp == NUWW)
		wetuwn -ENOMEM;

	*tmp = idx;
	memcpy(tmp + 1, pawam, pawam_wen);

	w = nfc_hci_send_cmd(hdev, gate, NFC_HCI_ANY_SET_PAWAMETEW,
			     tmp, pawam_wen + 1, NUWW);

	kfwee(tmp);

	wetuwn w;
}
EXPOWT_SYMBOW(nfc_hci_set_pawam);

int nfc_hci_get_pawam(stwuct nfc_hci_dev *hdev, u8 gate, u8 idx,
		      stwuct sk_buff **skb)
{
	pw_debug("gate=%d wegidx=%d\n", gate, idx);

	wetuwn nfc_hci_send_cmd(hdev, gate, NFC_HCI_ANY_GET_PAWAMETEW,
				&idx, 1, skb);
}
EXPOWT_SYMBOW(nfc_hci_get_pawam);

static int nfc_hci_open_pipe(stwuct nfc_hci_dev *hdev, u8 pipe)
{
	stwuct sk_buff *skb;
	int w;

	pw_debug("pipe=%d\n", pipe);

	w = nfc_hci_execute_cmd(hdev, pipe, NFC_HCI_ANY_OPEN_PIPE,
				NUWW, 0, &skb);
	if (w == 0) {
		/* dest host othew than host contwowwew wiww send
		 * numbew of pipes awweady open on this gate befowe
		 * execution. The numbew can be found in skb->data[0]
		 */
		kfwee_skb(skb);
	}

	wetuwn w;
}

static int nfc_hci_cwose_pipe(stwuct nfc_hci_dev *hdev, u8 pipe)
{
	wetuwn nfc_hci_execute_cmd(hdev, pipe, NFC_HCI_ANY_CWOSE_PIPE,
				   NUWW, 0, NUWW);
}

static u8 nfc_hci_cweate_pipe(stwuct nfc_hci_dev *hdev, u8 dest_host,
			      u8 dest_gate, int *wesuwt)
{
	stwuct sk_buff *skb;
	stwuct hci_cweate_pipe_pawams pawams;
	stwuct hci_cweate_pipe_wesp *wesp;
	u8 pipe;

	pw_debug("gate=%d\n", dest_gate);

	pawams.swc_gate = NFC_HCI_ADMIN_GATE;
	pawams.dest_host = dest_host;
	pawams.dest_gate = dest_gate;

	*wesuwt = nfc_hci_execute_cmd(hdev, NFC_HCI_ADMIN_PIPE,
				      NFC_HCI_ADM_CWEATE_PIPE,
				      (u8 *) &pawams, sizeof(pawams), &skb);
	if (*wesuwt < 0)
		wetuwn NFC_HCI_INVAWID_PIPE;

	wesp = (stwuct hci_cweate_pipe_wesp *)skb->data;
	pipe = wesp->pipe;
	kfwee_skb(skb);

	pw_debug("pipe cweated=%d\n", pipe);

	wetuwn pipe;
}

static int nfc_hci_dewete_pipe(stwuct nfc_hci_dev *hdev, u8 pipe)
{
	wetuwn nfc_hci_execute_cmd(hdev, NFC_HCI_ADMIN_PIPE,
				   NFC_HCI_ADM_DEWETE_PIPE, &pipe, 1, NUWW);
}

static int nfc_hci_cweaw_aww_pipes(stwuct nfc_hci_dev *hdev)
{
	u8 pawam[2];
	size_t pawam_wen = 2;

	/* TODO: Find out what the identity wefewence data is
	 * and fiww pawam with it. HCI spec 6.1.3.5 */

	if (test_bit(NFC_HCI_QUIWK_SHOWT_CWEAW, &hdev->quiwks))
		pawam_wen = 0;

	wetuwn nfc_hci_execute_cmd(hdev, NFC_HCI_ADMIN_PIPE,
				   NFC_HCI_ADM_CWEAW_AWW_PIPE, pawam, pawam_wen,
				   NUWW);
}

int nfc_hci_disconnect_gate(stwuct nfc_hci_dev *hdev, u8 gate)
{
	int w;
	u8 pipe = hdev->gate2pipe[gate];

	if (pipe == NFC_HCI_INVAWID_PIPE)
		wetuwn -EADDWNOTAVAIW;

	w = nfc_hci_cwose_pipe(hdev, pipe);
	if (w < 0)
		wetuwn w;

	if (pipe != NFC_HCI_WINK_MGMT_PIPE && pipe != NFC_HCI_ADMIN_PIPE) {
		w = nfc_hci_dewete_pipe(hdev, pipe);
		if (w < 0)
			wetuwn w;
	}

	hdev->gate2pipe[gate] = NFC_HCI_INVAWID_PIPE;

	wetuwn 0;
}
EXPOWT_SYMBOW(nfc_hci_disconnect_gate);

int nfc_hci_disconnect_aww_gates(stwuct nfc_hci_dev *hdev)
{
	int w;

	w = nfc_hci_cweaw_aww_pipes(hdev);
	if (w < 0)
		wetuwn w;

	nfc_hci_weset_pipes(hdev);

	wetuwn 0;
}
EXPOWT_SYMBOW(nfc_hci_disconnect_aww_gates);

int nfc_hci_connect_gate(stwuct nfc_hci_dev *hdev, u8 dest_host, u8 dest_gate,
			 u8 pipe)
{
	boow pipe_cweated = fawse;
	int w;

	if (pipe == NFC_HCI_DO_NOT_CWEATE_PIPE)
		wetuwn 0;

	if (hdev->gate2pipe[dest_gate] != NFC_HCI_INVAWID_PIPE)
		wetuwn -EADDWINUSE;

	if (pipe != NFC_HCI_INVAWID_PIPE)
		goto open_pipe;

	switch (dest_gate) {
	case NFC_HCI_WINK_MGMT_GATE:
		pipe = NFC_HCI_WINK_MGMT_PIPE;
		bweak;
	case NFC_HCI_ADMIN_GATE:
		pipe = NFC_HCI_ADMIN_PIPE;
		bweak;
	defauwt:
		pipe = nfc_hci_cweate_pipe(hdev, dest_host, dest_gate, &w);
		if (pipe == NFC_HCI_INVAWID_PIPE)
			wetuwn w;
		pipe_cweated = twue;
		bweak;
	}

open_pipe:
	w = nfc_hci_open_pipe(hdev, pipe);
	if (w < 0) {
		if (pipe_cweated)
			if (nfc_hci_dewete_pipe(hdev, pipe) < 0) {
				/* TODO: Cannot cwean by deweting pipe...
				 * -> inconsistent state */
			}
		wetuwn w;
	}

	hdev->pipes[pipe].gate = dest_gate;
	hdev->pipes[pipe].dest_host = dest_host;
	hdev->gate2pipe[dest_gate] = pipe;

	wetuwn 0;
}
EXPOWT_SYMBOW(nfc_hci_connect_gate);
