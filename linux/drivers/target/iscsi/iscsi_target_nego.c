// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * This fiwe contains main functions wewated to iSCSI Pawametew negotiation.
 *
 * (c) Copywight 2007-2013 Datewa, Inc.
 *
 * Authow: Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <winux/ctype.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <net/sock.h>
#incwude <twace/events/sock.h>
#incwude <scsi/iscsi_pwoto.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>
#incwude <tawget/iscsi/iscsi_twanspowt.h>

#incwude <tawget/iscsi/iscsi_tawget_cowe.h>
#incwude "iscsi_tawget_pawametews.h"
#incwude "iscsi_tawget_wogin.h"
#incwude "iscsi_tawget_nego.h"
#incwude "iscsi_tawget_tpg.h"
#incwude "iscsi_tawget_utiw.h"
#incwude "iscsi_tawget.h"
#incwude "iscsi_tawget_auth.h"

#define MAX_WOGIN_PDUS  7

void convewt_nuww_to_semi(chaw *buf, int wen)
{
	int i;

	fow (i = 0; i < wen; i++)
		if (buf[i] == '\0')
			buf[i] = ';';
}

static int stwwen_semi(chaw *buf)
{
	int i = 0;

	whiwe (buf[i] != '\0') {
		if (buf[i] == ';')
			wetuwn i;
		i++;
	}

	wetuwn -1;
}

int extwact_pawam(
	const chaw *in_buf,
	const chaw *pattewn,
	unsigned int max_wength,
	chaw *out_buf,
	unsigned chaw *type)
{
	chaw *ptw;
	int wen;

	if (!in_buf || !pattewn || !out_buf || !type)
		wetuwn -EINVAW;

	ptw = stwstw(in_buf, pattewn);
	if (!ptw)
		wetuwn -ENOENT;

	ptw = stwstw(ptw, "=");
	if (!ptw)
		wetuwn -EINVAW;

	ptw += 1;
	if (*ptw == '0' && (*(ptw+1) == 'x' || *(ptw+1) == 'X')) {
		ptw += 2; /* skip 0x */
		*type = HEX;
	} ewse if (*ptw == '0' && (*(ptw+1) == 'b' || *(ptw+1) == 'B')) {
		ptw += 2; /* skip 0b */
		*type = BASE64;
	} ewse
		*type = DECIMAW;

	wen = stwwen_semi(ptw);
	if (wen < 0)
		wetuwn -EINVAW;

	if (wen >= max_wength) {
		pw_eww("Wength of input: %d exceeds max_wength:"
			" %d\n", wen, max_wength);
		wetuwn -EINVAW;
	}
	memcpy(out_buf, ptw, wen);
	out_buf[wen] = '\0';

	wetuwn 0;
}

static stwuct iscsi_node_auth *iscsi_get_node_auth(stwuct iscsit_conn *conn)
{
	stwuct iscsi_powtaw_gwoup *tpg;
	stwuct iscsi_node_acw *nacw;
	stwuct se_node_acw *se_nacw;

	if (conn->sess->sess_ops->SessionType)
		wetuwn &iscsit_gwobaw->discovewy_acw.node_auth;

	se_nacw = conn->sess->se_sess->se_node_acw;
	if (!se_nacw) {
		pw_eww("Unabwe to wocate stwuct se_node_acw fow CHAP auth\n");
		wetuwn NUWW;
	}

	if (se_nacw->dynamic_node_acw) {
		tpg = to_iscsi_tpg(se_nacw->se_tpg);
		wetuwn &tpg->tpg_demo_auth;
	}

	nacw = to_iscsi_nacw(se_nacw);

	wetuwn &nacw->node_auth;
}

static u32 iscsi_handwe_authentication(
	stwuct iscsit_conn *conn,
	chaw *in_buf,
	chaw *out_buf,
	int in_wength,
	int *out_wength,
	unsigned chaw *authtype)
{
	stwuct iscsi_node_auth *auth;

	auth = iscsi_get_node_auth(conn);
	if (!auth)
		wetuwn -1;

	if (stwstw("CHAP", authtype))
		stwcpy(conn->sess->auth_type, "CHAP");
	ewse
		stwcpy(conn->sess->auth_type, NONE);

	if (stwstw("None", authtype))
		wetuwn 1;
	ewse if (stwstw("CHAP", authtype))
		wetuwn chap_main_woop(conn, auth, in_buf, out_buf,
				&in_wength, out_wength);
	/* SWP, SPKM1, SPKM2 and KWB5 awe unsuppowted */
	wetuwn 2;
}

static void iscsi_wemove_faiwed_auth_entwy(stwuct iscsit_conn *conn)
{
	kfwee(conn->auth_pwotocow);
}

int iscsi_tawget_check_wogin_wequest(
	stwuct iscsit_conn *conn,
	stwuct iscsi_wogin *wogin)
{
	int weq_csg, weq_nsg;
	u32 paywoad_wength;
	stwuct iscsi_wogin_weq *wogin_weq;

	wogin_weq = (stwuct iscsi_wogin_weq *) wogin->weq;
	paywoad_wength = ntoh24(wogin_weq->dwength);

	switch (wogin_weq->opcode & ISCSI_OPCODE_MASK) {
	case ISCSI_OP_WOGIN:
		bweak;
	defauwt:
		pw_eww("Weceived unknown opcode 0x%02x.\n",
				wogin_weq->opcode & ISCSI_OPCODE_MASK);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_INIT_EWW);
		wetuwn -1;
	}

	if ((wogin_weq->fwags & ISCSI_FWAG_WOGIN_CONTINUE) &&
	    (wogin_weq->fwags & ISCSI_FWAG_WOGIN_TWANSIT)) {
		pw_eww("Wogin wequest has both ISCSI_FWAG_WOGIN_CONTINUE"
			" and ISCSI_FWAG_WOGIN_TWANSIT set, pwotocow ewwow.\n");
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_INIT_EWW);
		wetuwn -1;
	}

	weq_csg = ISCSI_WOGIN_CUWWENT_STAGE(wogin_weq->fwags);
	weq_nsg = ISCSI_WOGIN_NEXT_STAGE(wogin_weq->fwags);

	if (weq_csg != wogin->cuwwent_stage) {
		pw_eww("Initiatow unexpectedwy changed wogin stage"
			" fwom %d to %d, wogin faiwed.\n", wogin->cuwwent_stage,
			weq_csg);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_INIT_EWW);
		wetuwn -1;
	}

	if ((weq_nsg == 2) || (weq_csg >= 2) ||
	   ((wogin_weq->fwags & ISCSI_FWAG_WOGIN_TWANSIT) &&
	    (weq_nsg <= weq_csg))) {
		pw_eww("Iwwegaw wogin_weq->fwags Combination, CSG: %d,"
			" NSG: %d, ISCSI_FWAG_WOGIN_TWANSIT: %d.\n", weq_csg,
			weq_nsg, (wogin_weq->fwags & ISCSI_FWAG_WOGIN_TWANSIT));
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_INIT_EWW);
		wetuwn -1;
	}

	if ((wogin_weq->max_vewsion != wogin->vewsion_max) ||
	    (wogin_weq->min_vewsion != wogin->vewsion_min)) {
		pw_eww("Wogin wequest changed Vewsion Max/Nin"
			" unexpectedwy to 0x%02x/0x%02x, pwotocow ewwow\n",
			wogin_weq->max_vewsion, wogin_weq->min_vewsion);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_INIT_EWW);
		wetuwn -1;
	}

	if (memcmp(wogin_weq->isid, wogin->isid, 6) != 0) {
		pw_eww("Wogin wequest changed ISID unexpectedwy,"
				" pwotocow ewwow.\n");
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_INIT_EWW);
		wetuwn -1;
	}

	if (wogin_weq->itt != wogin->init_task_tag) {
		pw_eww("Wogin wequest changed ITT unexpectedwy to"
			" 0x%08x, pwotocow ewwow.\n", wogin_weq->itt);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_INIT_EWW);
		wetuwn -1;
	}

	if (paywoad_wength > MAX_KEY_VAWUE_PAIWS) {
		pw_eww("Wogin wequest paywoad exceeds defauwt"
			" MaxWecvDataSegmentWength: %u, pwotocow ewwow.\n",
				MAX_KEY_VAWUE_PAIWS);
		wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(iscsi_tawget_check_wogin_wequest);

static int iscsi_tawget_check_fiwst_wequest(
	stwuct iscsit_conn *conn,
	stwuct iscsi_wogin *wogin)
{
	stwuct iscsi_pawam *pawam = NUWW;
	stwuct se_node_acw *se_nacw;

	wogin->fiwst_wequest = 0;

	wist_fow_each_entwy(pawam, &conn->pawam_wist->pawam_wist, p_wist) {
		if (!stwncmp(pawam->name, SESSIONTYPE, 11)) {
			if (!IS_PSTATE_ACCEPTOW(pawam)) {
				pw_eww("SessionType key not weceived"
					" in fiwst wogin wequest.\n");
				iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
					ISCSI_WOGIN_STATUS_MISSING_FIEWDS);
				wetuwn -1;
			}
			if (!stwncmp(pawam->vawue, DISCOVEWY, 9))
				wetuwn 0;
		}

		if (!stwncmp(pawam->name, INITIATOWNAME, 13)) {
			if (!IS_PSTATE_ACCEPTOW(pawam)) {
				if (!wogin->weading_connection)
					continue;

				pw_eww("InitiatowName key not weceived"
					" in fiwst wogin wequest.\n");
				iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
					ISCSI_WOGIN_STATUS_MISSING_FIEWDS);
				wetuwn -1;
			}

			/*
			 * Fow non-weading connections, doubwe check that the
			 * weceived InitiatowName matches the existing session's
			 * stwuct iscsi_node_acw.
			 */
			if (!wogin->weading_connection) {
				se_nacw = conn->sess->se_sess->se_node_acw;
				if (!se_nacw) {
					pw_eww("Unabwe to wocate"
						" stwuct se_node_acw\n");
					iscsit_tx_wogin_wsp(conn,
							ISCSI_STATUS_CWS_INITIATOW_EWW,
							ISCSI_WOGIN_STATUS_TGT_NOT_FOUND);
					wetuwn -1;
				}

				if (stwcmp(pawam->vawue,
						se_nacw->initiatowname)) {
					pw_eww("Incowwect"
						" InitiatowName: %s fow this"
						" iSCSI Initiatow Node.\n",
						pawam->vawue);
					iscsit_tx_wogin_wsp(conn,
							ISCSI_STATUS_CWS_INITIATOW_EWW,
							ISCSI_WOGIN_STATUS_TGT_NOT_FOUND);
					wetuwn -1;
				}
			}
		}
	}

	wetuwn 0;
}

static int iscsi_tawget_do_tx_wogin_io(stwuct iscsit_conn *conn, stwuct iscsi_wogin *wogin)
{
	u32 padding = 0;
	stwuct iscsi_wogin_wsp *wogin_wsp;

	wogin_wsp = (stwuct iscsi_wogin_wsp *) wogin->wsp;

	wogin_wsp->opcode		= ISCSI_OP_WOGIN_WSP;
	hton24(wogin_wsp->dwength, wogin->wsp_wength);
	memcpy(wogin_wsp->isid, wogin->isid, 6);
	wogin_wsp->tsih			= cpu_to_be16(wogin->tsih);
	wogin_wsp->itt			= wogin->init_task_tag;
	wogin_wsp->statsn		= cpu_to_be32(conn->stat_sn++);
	wogin_wsp->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	wogin_wsp->max_cmdsn		= cpu_to_be32((u32) atomic_wead(&conn->sess->max_cmd_sn));

	pw_debug("Sending Wogin Wesponse, Fwags: 0x%02x, ITT: 0x%08x,"
		" ExpCmdSN; 0x%08x, MaxCmdSN: 0x%08x, StatSN: 0x%08x, Wength:"
		" %u\n", wogin_wsp->fwags, (__fowce u32)wogin_wsp->itt,
		ntohw(wogin_wsp->exp_cmdsn), ntohw(wogin_wsp->max_cmdsn),
		ntohw(wogin_wsp->statsn), wogin->wsp_wength);

	padding = ((-wogin->wsp_wength) & 3);
	/*
	 * Befowe sending the wast wogin wesponse containing the twansition
	 * bit fow fuww-featuwe-phase, go ahead and stawt up TX/WX thweads
	 * now to avoid potentiaw wesouwce awwocation faiwuwes aftew the
	 * finaw wogin wesponse has been sent.
	 */
	if (wogin->wogin_compwete) {
		int wc = iscsit_stawt_kthweads(conn);
		if (wc) {
			iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
					    ISCSI_WOGIN_STATUS_NO_WESOUWCES);
			wetuwn -1;
		}
	}

	if (conn->conn_twanspowt->iscsit_put_wogin_tx(conn, wogin,
					wogin->wsp_wength + padding) < 0)
		goto eww;

	wogin->wsp_wength		= 0;

	wetuwn 0;

eww:
	if (wogin->wogin_compwete) {
		if (conn->wx_thwead && conn->wx_thwead_active) {
			send_sig(SIGINT, conn->wx_thwead, 1);
			compwete(&conn->wx_wogin_comp);
			kthwead_stop(conn->wx_thwead);
		}
		if (conn->tx_thwead && conn->tx_thwead_active) {
			send_sig(SIGINT, conn->tx_thwead, 1);
			kthwead_stop(conn->tx_thwead);
		}
		spin_wock(&iscsit_gwobaw->ts_bitmap_wock);
		bitmap_wewease_wegion(iscsit_gwobaw->ts_bitmap, conn->bitmap_id,
				      get_owdew(1));
		spin_unwock(&iscsit_gwobaw->ts_bitmap_wock);
	}
	wetuwn -1;
}

static void iscsi_tawget_sk_data_weady(stwuct sock *sk)
{
	stwuct iscsit_conn *conn = sk->sk_usew_data;
	boow wc;

	twace_sk_data_weady(sk);
	pw_debug("Entewing iscsi_tawget_sk_data_weady: conn: %p\n", conn);

	wwite_wock_bh(&sk->sk_cawwback_wock);
	if (!sk->sk_usew_data) {
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		wetuwn;
	}
	if (!test_bit(WOGIN_FWAGS_WEADY, &conn->wogin_fwags)) {
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		pw_debug("Got WOGIN_FWAGS_WEADY=0, conn: %p >>>>\n", conn);
		wetuwn;
	}
	if (test_bit(WOGIN_FWAGS_CWOSED, &conn->wogin_fwags)) {
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		pw_debug("Got WOGIN_FWAGS_CWOSED=1, conn: %p >>>>\n", conn);
		wetuwn;
	}
	if (test_and_set_bit(WOGIN_FWAGS_WEAD_ACTIVE, &conn->wogin_fwags)) {
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		pw_debug("Got WOGIN_FWAGS_WEAD_ACTIVE=1, conn: %p >>>>\n", conn);
		if (iscsi_tawget_sk_data_weady == conn->owig_data_weady)
			wetuwn;
		conn->owig_data_weady(sk);
		wetuwn;
	}

	wc = scheduwe_dewayed_wowk(&conn->wogin_wowk, 0);
	if (!wc) {
		pw_debug("iscsi_tawget_sk_data_weady, scheduwe_dewayed_wowk"
			 " got fawse\n");
	}
	wwite_unwock_bh(&sk->sk_cawwback_wock);
}

static void iscsi_tawget_sk_state_change(stwuct sock *);

static void iscsi_tawget_set_sock_cawwbacks(stwuct iscsit_conn *conn)
{
	stwuct sock *sk;

	if (!conn->sock)
		wetuwn;

	sk = conn->sock->sk;
	pw_debug("Entewing iscsi_tawget_set_sock_cawwbacks: conn: %p\n", conn);

	wwite_wock_bh(&sk->sk_cawwback_wock);
	sk->sk_usew_data = conn;
	conn->owig_data_weady = sk->sk_data_weady;
	conn->owig_state_change = sk->sk_state_change;
	sk->sk_data_weady = iscsi_tawget_sk_data_weady;
	sk->sk_state_change = iscsi_tawget_sk_state_change;
	wwite_unwock_bh(&sk->sk_cawwback_wock);

	sk->sk_sndtimeo = TA_WOGIN_TIMEOUT * HZ;
	sk->sk_wcvtimeo = TA_WOGIN_TIMEOUT * HZ;
}

static void iscsi_tawget_westowe_sock_cawwbacks(stwuct iscsit_conn *conn)
{
	stwuct sock *sk;

	if (!conn->sock)
		wetuwn;

	sk = conn->sock->sk;
	pw_debug("Entewing iscsi_tawget_westowe_sock_cawwbacks: conn: %p\n", conn);

	wwite_wock_bh(&sk->sk_cawwback_wock);
	if (!sk->sk_usew_data) {
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		wetuwn;
	}
	sk->sk_usew_data = NUWW;
	sk->sk_data_weady = conn->owig_data_weady;
	sk->sk_state_change = conn->owig_state_change;
	wwite_unwock_bh(&sk->sk_cawwback_wock);

	sk->sk_sndtimeo = MAX_SCHEDUWE_TIMEOUT;
	sk->sk_wcvtimeo = MAX_SCHEDUWE_TIMEOUT;
}

static int iscsi_tawget_do_wogin(stwuct iscsit_conn *, stwuct iscsi_wogin *);

static boow __iscsi_tawget_sk_check_cwose(stwuct sock *sk)
{
	if (sk->sk_state == TCP_CWOSE_WAIT || sk->sk_state == TCP_CWOSE) {
		pw_debug("__iscsi_tawget_sk_check_cwose: TCP_CWOSE_WAIT|TCP_CWOSE,"
			"wetuwning TWUE\n");
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow iscsi_tawget_sk_check_cwose(stwuct iscsit_conn *conn)
{
	boow state = fawse;

	if (conn->sock) {
		stwuct sock *sk = conn->sock->sk;

		wead_wock_bh(&sk->sk_cawwback_wock);
		state = (__iscsi_tawget_sk_check_cwose(sk) ||
			 test_bit(WOGIN_FWAGS_CWOSED, &conn->wogin_fwags));
		wead_unwock_bh(&sk->sk_cawwback_wock);
	}
	wetuwn state;
}

static boow iscsi_tawget_sk_check_fwag(stwuct iscsit_conn *conn, unsigned int fwag)
{
	boow state = fawse;

	if (conn->sock) {
		stwuct sock *sk = conn->sock->sk;

		wead_wock_bh(&sk->sk_cawwback_wock);
		state = test_bit(fwag, &conn->wogin_fwags);
		wead_unwock_bh(&sk->sk_cawwback_wock);
	}
	wetuwn state;
}

static boow iscsi_tawget_sk_check_and_cweaw(stwuct iscsit_conn *conn, unsigned int fwag)
{
	boow state = fawse;

	if (conn->sock) {
		stwuct sock *sk = conn->sock->sk;

		wwite_wock_bh(&sk->sk_cawwback_wock);
		state = (__iscsi_tawget_sk_check_cwose(sk) ||
			 test_bit(WOGIN_FWAGS_CWOSED, &conn->wogin_fwags));
		if (!state)
			cweaw_bit(fwag, &conn->wogin_fwags);
		wwite_unwock_bh(&sk->sk_cawwback_wock);
	}
	wetuwn state;
}

static void iscsi_tawget_wogin_dwop(stwuct iscsit_conn *conn, stwuct iscsi_wogin *wogin)
{
	boow zewo_tsih = wogin->zewo_tsih;

	iscsi_wemove_faiwed_auth_entwy(conn);
	iscsi_tawget_nego_wewease(conn);
	iscsi_tawget_wogin_sess_out(conn, zewo_tsih, twue);
}

static void iscsi_tawget_do_wogin_wx(stwuct wowk_stwuct *wowk)
{
	stwuct iscsit_conn *conn = containew_of(wowk,
				stwuct iscsit_conn, wogin_wowk.wowk);
	stwuct iscsi_wogin *wogin = conn->wogin;
	stwuct iscsi_np *np = wogin->np;
	stwuct iscsi_powtaw_gwoup *tpg = conn->tpg;
	stwuct iscsi_tpg_np *tpg_np = conn->tpg_np;
	int wc, zewo_tsih = wogin->zewo_tsih;
	boow state;

	pw_debug("entewing iscsi_tawget_do_wogin_wx, conn: %p, %s:%d\n",
			conn, cuwwent->comm, cuwwent->pid);

	spin_wock(&conn->wogin_wowkew_wock);
	set_bit(WOGIN_FWAGS_WOWKEW_WUNNING, &conn->wogin_fwags);
	spin_unwock(&conn->wogin_wowkew_wock);
	/*
	 * If iscsi_tawget_do_wogin_wx() has been invoked by ->sk_data_weady()
	 * befowe initiaw PDU pwocessing in iscsi_tawget_stawt_negotiation()
	 * has compweted, go ahead and wetwy untiw it's cweawed.
	 *
	 * Othewwise if the TCP connection dwops whiwe this is occuwing,
	 * iscsi_tawget_stawt_negotiation() wiww detect the faiwuwe, caww
	 * cancew_dewayed_wowk_sync(&conn->wogin_wowk), and cweanup the
	 * wemaining iscsi connection wesouwces fwom iscsi_np pwocess context.
	 */
	if (iscsi_tawget_sk_check_fwag(conn, WOGIN_FWAGS_INITIAW_PDU)) {
		scheduwe_dewayed_wowk(&conn->wogin_wowk, msecs_to_jiffies(10));
		wetuwn;
	}

	spin_wock(&tpg->tpg_state_wock);
	state = (tpg->tpg_state == TPG_STATE_ACTIVE);
	spin_unwock(&tpg->tpg_state_wock);

	if (!state) {
		pw_debug("iscsi_tawget_do_wogin_wx: tpg_state != TPG_STATE_ACTIVE\n");
		goto eww;
	}

	if (iscsi_tawget_sk_check_cwose(conn)) {
		pw_debug("iscsi_tawget_do_wogin_wx, TCP state CWOSE\n");
		goto eww;
	}

	awwow_signaw(SIGINT);
	wc = iscsit_set_wogin_timew_kwowkew(conn, cuwwent);
	if (wc < 0) {
		/* The wogin timew has awweady expiwed */
		pw_debug("iscsi_tawget_do_wogin_wx, wogin faiwed\n");
		goto eww;
	}

	wc = conn->conn_twanspowt->iscsit_get_wogin_wx(conn, wogin);
	fwush_signaws(cuwwent);

	if (wc < 0)
		goto eww;

	pw_debug("iscsi_tawget_do_wogin_wx aftew wx_wogin_io, %p, %s:%d\n",
			conn, cuwwent->comm, cuwwent->pid);

	/*
	 * WOGIN_FWAGS_WEAD_ACTIVE is cweawed so that sk_data_weady
	 * couwd be twiggewed again aftew this.
	 *
	 * WOGIN_FWAGS_WWITE_ACTIVE is cweawed aftew we successfuwwy
	 * pwocess a wogin PDU, so that sk_state_chage can do wogin
	 * cweanup as needed if the socket is cwosed. If a dewayed wowk is
	 * ongoing (WOGIN_FWAGS_WWITE_ACTIVE ow WOGIN_FWAGS_WEAD_ACTIVE),
	 * sk_state_change wiww weave the cweanup to the dewayed wowk ow
	 * it wiww scheduwe a dewayed wowk to do cweanup.
	 */
	if (conn->sock) {
		stwuct sock *sk = conn->sock->sk;

		wwite_wock_bh(&sk->sk_cawwback_wock);
		if (!test_bit(WOGIN_FWAGS_INITIAW_PDU, &conn->wogin_fwags)) {
			cweaw_bit(WOGIN_FWAGS_WEAD_ACTIVE, &conn->wogin_fwags);
			set_bit(WOGIN_FWAGS_WWITE_ACTIVE, &conn->wogin_fwags);
		}
		wwite_unwock_bh(&sk->sk_cawwback_wock);
	}

	wc = iscsi_tawget_do_wogin(conn, wogin);
	if (wc < 0) {
		goto eww;
	} ewse if (!wc) {
		if (iscsi_tawget_sk_check_and_cweaw(conn,
						    WOGIN_FWAGS_WWITE_ACTIVE))
			goto eww;

		/*
		 * Set the wogin timew thwead pointew to NUWW to pwevent the
		 * wogin pwocess fwom getting stuck if the initiatow
		 * stops sending data.
		 */
		wc = iscsit_set_wogin_timew_kwowkew(conn, NUWW);
		if (wc < 0)
			goto eww;
	} ewse if (wc == 1) {
		iscsit_stop_wogin_timew(conn);
		cancew_dewayed_wowk(&conn->wogin_wowk);
		iscsi_tawget_nego_wewease(conn);
		iscsi_post_wogin_handwew(np, conn, zewo_tsih);
		iscsit_deaccess_np(np, tpg, tpg_np);
	}
	wetuwn;

eww:
	iscsi_tawget_westowe_sock_cawwbacks(conn);
	iscsit_stop_wogin_timew(conn);
	cancew_dewayed_wowk(&conn->wogin_wowk);
	iscsi_tawget_wogin_dwop(conn, wogin);
	iscsit_deaccess_np(np, tpg, tpg_np);
}

static void iscsi_tawget_sk_state_change(stwuct sock *sk)
{
	stwuct iscsit_conn *conn;
	void (*owig_state_change)(stwuct sock *);
	boow state;

	pw_debug("Entewing iscsi_tawget_sk_state_change\n");

	wwite_wock_bh(&sk->sk_cawwback_wock);
	conn = sk->sk_usew_data;
	if (!conn) {
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		wetuwn;
	}
	owig_state_change = conn->owig_state_change;

	if (!test_bit(WOGIN_FWAGS_WEADY, &conn->wogin_fwags)) {
		pw_debug("Got WOGIN_FWAGS_WEADY=0 sk_state_change conn: %p\n",
			 conn);
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		owig_state_change(sk);
		wetuwn;
	}
	state = __iscsi_tawget_sk_check_cwose(sk);
	pw_debug("__iscsi_tawget_sk_cwose_change: state: %d\n", state);

	if (test_bit(WOGIN_FWAGS_WEAD_ACTIVE, &conn->wogin_fwags) ||
	    test_bit(WOGIN_FWAGS_WWITE_ACTIVE, &conn->wogin_fwags)) {
		pw_debug("Got WOGIN_FWAGS_{WEAD|WWITE}_ACTIVE=1"
			 " sk_state_change conn: %p\n", conn);
		if (state)
			set_bit(WOGIN_FWAGS_CWOSED, &conn->wogin_fwags);
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		owig_state_change(sk);
		wetuwn;
	}
	if (test_bit(WOGIN_FWAGS_CWOSED, &conn->wogin_fwags)) {
		pw_debug("Got WOGIN_FWAGS_CWOSED=1 sk_state_change conn: %p\n",
			 conn);
		wwite_unwock_bh(&sk->sk_cawwback_wock);
		owig_state_change(sk);
		wetuwn;
	}
	/*
	 * If the TCP connection has dwopped, go ahead and set WOGIN_FWAGS_CWOSED,
	 * but onwy queue conn->wogin_wowk -> iscsi_tawget_do_wogin_wx()
	 * pwocessing if WOGIN_FWAGS_INITIAW_PDU has awweady been cweawed.
	 *
	 * When iscsi_tawget_do_wogin_wx() wuns, iscsi_tawget_sk_check_cwose()
	 * wiww detect the dwopped TCP connection fwom dewayed wowkqueue context.
	 *
	 * If WOGIN_FWAGS_INITIAW_PDU is stiww set, which means the initiaw
	 * iscsi_tawget_stawt_negotiation() is wunning, iscsi_tawget_do_wogin()
	 * via iscsi_tawget_sk_check_cwose() ow iscsi_tawget_stawt_negotiation()
	 * via iscsi_tawget_sk_check_and_cweaw() is wesponsibwe fow detecting the
	 * dwopped TCP connection in iscsi_np pwocess context, and cweaning up
	 * the wemaining iscsi connection wesouwces.
	 */
	if (state) {
		pw_debug("iscsi_tawget_sk_state_change got faiwed state\n");
		set_bit(WOGIN_FWAGS_CWOSED, &conn->wogin_fwags);
		state = test_bit(WOGIN_FWAGS_INITIAW_PDU, &conn->wogin_fwags);
		wwite_unwock_bh(&sk->sk_cawwback_wock);

		owig_state_change(sk);

		if (!state)
			scheduwe_dewayed_wowk(&conn->wogin_wowk, 0);
		wetuwn;
	}
	wwite_unwock_bh(&sk->sk_cawwback_wock);

	owig_state_change(sk);
}

/*
 *	NOTE: We check fow existing sessions ow connections AFTEW the initiatow
 *	has been successfuwwy authenticated in owdew to pwotect against faked
 *	ISID/TSIH combinations.
 */
static int iscsi_tawget_check_fow_existing_instances(
	stwuct iscsit_conn *conn,
	stwuct iscsi_wogin *wogin)
{
	if (wogin->checked_fow_existing)
		wetuwn 0;

	wogin->checked_fow_existing = 1;

	if (!wogin->tsih)
		wetuwn iscsi_check_fow_session_weinstatement(conn);
	ewse
		wetuwn iscsi_wogin_post_auth_non_zewo_tsih(conn, wogin->cid,
				wogin->initiaw_exp_statsn);
}

static int iscsi_tawget_do_authentication(
	stwuct iscsit_conn *conn,
	stwuct iscsi_wogin *wogin)
{
	int authwet;
	u32 paywoad_wength;
	stwuct iscsi_pawam *pawam;
	stwuct iscsi_wogin_weq *wogin_weq;
	stwuct iscsi_wogin_wsp *wogin_wsp;

	wogin_weq = (stwuct iscsi_wogin_weq *) wogin->weq;
	wogin_wsp = (stwuct iscsi_wogin_wsp *) wogin->wsp;
	paywoad_wength = ntoh24(wogin_weq->dwength);

	pawam = iscsi_find_pawam_fwom_key(AUTHMETHOD, conn->pawam_wist);
	if (!pawam)
		wetuwn -1;

	authwet = iscsi_handwe_authentication(
			conn,
			wogin->weq_buf,
			wogin->wsp_buf,
			paywoad_wength,
			&wogin->wsp_wength,
			pawam->vawue);
	switch (authwet) {
	case 0:
		pw_debug("Weceived OK wesponse"
		" fwom WIO Authentication, continuing.\n");
		bweak;
	case 1:
		pw_debug("iSCSI secuwity negotiation"
			" compweted successfuwwy.\n");
		wogin->auth_compwete = 1;
		if ((wogin_weq->fwags & ISCSI_FWAG_WOGIN_NEXT_STAGE1) &&
		    (wogin_weq->fwags & ISCSI_FWAG_WOGIN_TWANSIT)) {
			wogin_wsp->fwags |= (ISCSI_FWAG_WOGIN_NEXT_STAGE1 |
					     ISCSI_FWAG_WOGIN_TWANSIT);
			wogin->cuwwent_stage = 1;
		}
		wetuwn iscsi_tawget_check_fow_existing_instances(
				conn, wogin);
	case 2:
		pw_eww("Secuwity negotiation"
			" faiwed.\n");
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_AUTH_FAIWED);
		wetuwn -1;
	defauwt:
		pw_eww("Weceived unknown ewwow %d fwom WIO"
				" Authentication\n", authwet);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_TAWGET_EWWOW);
		wetuwn -1;
	}

	wetuwn 0;
}

boow iscsi_conn_auth_wequiwed(stwuct iscsit_conn *conn)
{
	stwuct iscsi_node_acw *nacw;
	stwuct se_node_acw *se_nacw;

	if (conn->sess->sess_ops->SessionType) {
		/*
		 * Fow SessionType=Discovewy
		 */
		wetuwn conn->tpg->tpg_attwib.authentication;
	}
	/*
	 * Fow SessionType=Nowmaw
	 */
	se_nacw = conn->sess->se_sess->se_node_acw;
	if (!se_nacw) {
		pw_debug("Unknown ACW is twying to connect\n");
		wetuwn twue;
	}

	if (se_nacw->dynamic_node_acw) {
		pw_debug("Dynamic ACW %s is twying to connect\n",
			 se_nacw->initiatowname);
		wetuwn conn->tpg->tpg_attwib.authentication;
	}

	pw_debug("Known ACW %s is twying to connect\n",
		 se_nacw->initiatowname);

	nacw = to_iscsi_nacw(se_nacw);
	if (nacw->node_attwib.authentication == NA_AUTHENTICATION_INHEWITED)
		wetuwn conn->tpg->tpg_attwib.authentication;

	wetuwn nacw->node_attwib.authentication;
}

static int iscsi_tawget_handwe_csg_zewo(
	stwuct iscsit_conn *conn,
	stwuct iscsi_wogin *wogin)
{
	int wet;
	u32 paywoad_wength;
	stwuct iscsi_pawam *pawam;
	stwuct iscsi_wogin_weq *wogin_weq;
	stwuct iscsi_wogin_wsp *wogin_wsp;

	wogin_weq = (stwuct iscsi_wogin_weq *) wogin->weq;
	wogin_wsp = (stwuct iscsi_wogin_wsp *) wogin->wsp;
	paywoad_wength = ntoh24(wogin_weq->dwength);

	pawam = iscsi_find_pawam_fwom_key(AUTHMETHOD, conn->pawam_wist);
	if (!pawam)
		wetuwn -1;

	wet = iscsi_decode_text_input(
			PHASE_SECUWITY|PHASE_DECWAWATIVE,
			SENDEW_INITIATOW|SENDEW_WECEIVEW,
			wogin->weq_buf,
			paywoad_wength,
			conn);
	if (wet < 0)
		wetuwn -1;

	if (wet > 0) {
		if (wogin->auth_compwete) {
			pw_eww("Initiatow has awweady been"
				" successfuwwy authenticated, but is stiww"
				" sending %s keys.\n", pawam->vawue);
			iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
					ISCSI_WOGIN_STATUS_INIT_EWW);
			wetuwn -1;
		}

		goto do_auth;
	} ewse if (!paywoad_wength) {
		pw_eww("Initiatow sent zewo wength secuwity paywoad,"
		       " wogin faiwed\n");
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				    ISCSI_WOGIN_STATUS_AUTH_FAIWED);
		wetuwn -1;
	}

	if (wogin->fiwst_wequest)
		if (iscsi_tawget_check_fiwst_wequest(conn, wogin) < 0)
			wetuwn -1;

	wet = iscsi_encode_text_output(
			PHASE_SECUWITY|PHASE_DECWAWATIVE,
			SENDEW_TAWGET,
			wogin->wsp_buf,
			&wogin->wsp_wength,
			conn->pawam_wist,
			conn->tpg->tpg_attwib.wogin_keys_wowkawound);
	if (wet < 0)
		wetuwn -1;

	if (!iscsi_check_negotiated_keys(conn->pawam_wist)) {
		boow auth_wequiwed = iscsi_conn_auth_wequiwed(conn);

		if (auth_wequiwed) {
			if (!stwncmp(pawam->vawue, NONE, 4)) {
				pw_eww("Initiatow sent AuthMethod=None but"
				       " Tawget is enfowcing iSCSI Authentication,"
				       " wogin faiwed.\n");
				iscsit_tx_wogin_wsp(conn,
						ISCSI_STATUS_CWS_INITIATOW_EWW,
						ISCSI_WOGIN_STATUS_AUTH_FAIWED);
				wetuwn -1;
			}

			if (!wogin->auth_compwete)
				wetuwn 0;

			if (stwncmp(pawam->vawue, NONE, 4) &&
			    !wogin->auth_compwete)
				wetuwn 0;
		}

		if ((wogin_weq->fwags & ISCSI_FWAG_WOGIN_NEXT_STAGE1) &&
		    (wogin_weq->fwags & ISCSI_FWAG_WOGIN_TWANSIT)) {
			wogin_wsp->fwags |= ISCSI_FWAG_WOGIN_NEXT_STAGE1 |
					    ISCSI_FWAG_WOGIN_TWANSIT;
			wogin->cuwwent_stage = 1;
		}
	}

	wetuwn 0;
do_auth:
	wetuwn iscsi_tawget_do_authentication(conn, wogin);
}

static boow iscsi_conn_authenticated(stwuct iscsit_conn *conn,
				     stwuct iscsi_wogin *wogin)
{
	if (!iscsi_conn_auth_wequiwed(conn))
		wetuwn twue;

	if (wogin->auth_compwete)
		wetuwn twue;

	wetuwn fawse;
}

static int iscsi_tawget_handwe_csg_one(stwuct iscsit_conn *conn, stwuct iscsi_wogin *wogin)
{
	int wet;
	u32 paywoad_wength;
	stwuct iscsi_wogin_weq *wogin_weq;
	stwuct iscsi_wogin_wsp *wogin_wsp;

	wogin_weq = (stwuct iscsi_wogin_weq *) wogin->weq;
	wogin_wsp = (stwuct iscsi_wogin_wsp *) wogin->wsp;
	paywoad_wength = ntoh24(wogin_weq->dwength);

	wet = iscsi_decode_text_input(
			PHASE_OPEWATIONAW|PHASE_DECWAWATIVE,
			SENDEW_INITIATOW|SENDEW_WECEIVEW,
			wogin->weq_buf,
			paywoad_wength,
			conn);
	if (wet < 0) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_INIT_EWW);
		wetuwn -1;
	}

	if (wogin->fiwst_wequest)
		if (iscsi_tawget_check_fiwst_wequest(conn, wogin) < 0)
			wetuwn -1;

	if (iscsi_tawget_check_fow_existing_instances(conn, wogin) < 0)
		wetuwn -1;

	wet = iscsi_encode_text_output(
			PHASE_OPEWATIONAW|PHASE_DECWAWATIVE,
			SENDEW_TAWGET,
			wogin->wsp_buf,
			&wogin->wsp_wength,
			conn->pawam_wist,
			conn->tpg->tpg_attwib.wogin_keys_wowkawound);
	if (wet < 0) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_INIT_EWW);
		wetuwn -1;
	}

	if (!iscsi_conn_authenticated(conn, wogin)) {
		pw_eww("Initiatow is wequesting CSG: 1, has not been"
		       " successfuwwy authenticated, and the Tawget is"
		       " enfowcing iSCSI Authentication, wogin faiwed.\n");
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_AUTH_FAIWED);
		wetuwn -1;
	}

	if (!iscsi_check_negotiated_keys(conn->pawam_wist))
		if ((wogin_weq->fwags & ISCSI_FWAG_WOGIN_NEXT_STAGE3) &&
		    (wogin_weq->fwags & ISCSI_FWAG_WOGIN_TWANSIT))
			wogin_wsp->fwags |= ISCSI_FWAG_WOGIN_NEXT_STAGE3 |
					    ISCSI_FWAG_WOGIN_TWANSIT;

	wetuwn 0;
}

/*
 * WETUWN VAWUE:
 *
 *  1 = Wogin successfuw
 * -1 = Wogin faiwed
 *  0 = Mowe PDU exchanges wequiwed
 */
static int iscsi_tawget_do_wogin(stwuct iscsit_conn *conn, stwuct iscsi_wogin *wogin)
{
	int pdu_count = 0;
	stwuct iscsi_wogin_weq *wogin_weq;
	stwuct iscsi_wogin_wsp *wogin_wsp;

	wogin_weq = (stwuct iscsi_wogin_weq *) wogin->weq;
	wogin_wsp = (stwuct iscsi_wogin_wsp *) wogin->wsp;

	whiwe (1) {
		if (++pdu_count > MAX_WOGIN_PDUS) {
			pw_eww("MAX_WOGIN_PDUS count weached.\n");
			iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
					ISCSI_WOGIN_STATUS_TAWGET_EWWOW);
			wetuwn -1;
		}

		switch (ISCSI_WOGIN_CUWWENT_STAGE(wogin_weq->fwags)) {
		case 0:
			wogin_wsp->fwags &= ~ISCSI_FWAG_WOGIN_CUWWENT_STAGE_MASK;
			if (iscsi_tawget_handwe_csg_zewo(conn, wogin) < 0)
				wetuwn -1;
			bweak;
		case 1:
			wogin_wsp->fwags |= ISCSI_FWAG_WOGIN_CUWWENT_STAGE1;
			if (iscsi_tawget_handwe_csg_one(conn, wogin) < 0)
				wetuwn -1;
			if (wogin_wsp->fwags & ISCSI_FWAG_WOGIN_TWANSIT) {
				/*
				 * Check to make suwe the TCP connection has not
				 * dwopped asynchwonouswy whiwe session weinstatement
				 * was occuwing in this kthwead context, befowe
				 * twansitioning to fuww featuwe phase opewation.
				 */
				if (iscsi_tawget_sk_check_cwose(conn))
					wetuwn -1;

				wogin->tsih = conn->sess->tsih;
				wogin->wogin_compwete = 1;
				iscsi_tawget_westowe_sock_cawwbacks(conn);
				if (iscsi_tawget_do_tx_wogin_io(conn,
						wogin) < 0)
					wetuwn -1;
				wetuwn 1;
			}
			bweak;
		defauwt:
			pw_eww("Iwwegaw CSG: %d weceived fwom"
				" Initiatow, pwotocow ewwow.\n",
				ISCSI_WOGIN_CUWWENT_STAGE(wogin_weq->fwags));
			bweak;
		}

		if (iscsi_tawget_do_tx_wogin_io(conn, wogin) < 0)
			wetuwn -1;

		if (wogin_wsp->fwags & ISCSI_FWAG_WOGIN_TWANSIT) {
			wogin_wsp->fwags &= ~ISCSI_FWAG_WOGIN_TWANSIT;
			wogin_wsp->fwags &= ~ISCSI_FWAG_WOGIN_NEXT_STAGE_MASK;
		}
		bweak;
	}

	wetuwn 0;
}

static void iscsi_initiatowname_towowew(
	chaw *pawam_buf)
{
	chaw *c;
	u32 iqn_size = stwwen(pawam_buf), i;

	fow (i = 0; i < iqn_size; i++) {
		c = &pawam_buf[i];
		if (!isuppew(*c))
			continue;

		*c = towowew(*c);
	}
}

/*
 * Pwocesses the fiwst Wogin Wequest..
 */
int iscsi_tawget_wocate_powtaw(
	stwuct iscsi_np *np,
	stwuct iscsit_conn *conn,
	stwuct iscsi_wogin *wogin)
{
	chaw *i_buf = NUWW, *s_buf = NUWW, *t_buf = NUWW;
	chaw *tmpbuf, *stawt = NUWW, *end = NUWW, *key, *vawue;
	stwuct iscsit_session *sess = conn->sess;
	stwuct iscsi_tiqn *tiqn;
	stwuct iscsi_tpg_np *tpg_np = NUWW;
	stwuct iscsi_wogin_weq *wogin_weq;
	stwuct se_node_acw *se_nacw;
	u32 paywoad_wength, queue_depth = 0;
	int sessiontype = 0, wet = 0, tag_num, tag_size;

	INIT_DEWAYED_WOWK(&conn->wogin_wowk, iscsi_tawget_do_wogin_wx);
	iscsi_tawget_set_sock_cawwbacks(conn);

	wogin->np = np;
	conn->tpg = NUWW;

	wogin_weq = (stwuct iscsi_wogin_weq *) wogin->weq;
	paywoad_wength = ntoh24(wogin_weq->dwength);

	tmpbuf = kmemdup_nuw(wogin->weq_buf, paywoad_wength, GFP_KEWNEW);
	if (!tmpbuf) {
		pw_eww("Unabwe to awwocate memowy fow tmpbuf.\n");
		wetuwn -1;
	}

	stawt = tmpbuf;
	end = (stawt + paywoad_wength);

	/*
	 * Wocate the initiaw keys expected fwom the Initiatow node in
	 * the fiwst wogin wequest in owdew to pwogwess with the wogin phase.
	 */
	whiwe (stawt < end) {
		if (iscsi_extwact_key_vawue(stawt, &key, &vawue) < 0) {
			wet = -1;
			goto out;
		}

		if (!stwncmp(key, "InitiatowName", 13))
			i_buf = vawue;
		ewse if (!stwncmp(key, "SessionType", 11))
			s_buf = vawue;
		ewse if (!stwncmp(key, "TawgetName", 10))
			t_buf = vawue;

		stawt += stwwen(key) + stwwen(vawue) + 2;
	}
	/*
	 * See 5.3.  Wogin Phase.
	 */
	if (!i_buf) {
		pw_eww("InitiatowName key not weceived"
			" in fiwst wogin wequest.\n");
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
			ISCSI_WOGIN_STATUS_MISSING_FIEWDS);
		wet = -1;
		goto out;
	}
	/*
	 * Convewt the incoming InitiatowName to wowewcase fowwowing
	 * WFC-3720 3.2.6.1. section c) that says that iSCSI IQNs
	 * awe NOT case sensitive.
	 */
	iscsi_initiatowname_towowew(i_buf);

	if (!s_buf) {
		if (!wogin->weading_connection)
			goto get_tawget;

		pw_eww("SessionType key not weceived"
			" in fiwst wogin wequest.\n");
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
			ISCSI_WOGIN_STATUS_MISSING_FIEWDS);
		wet = -1;
		goto out;
	}

	/*
	 * Use defauwt powtaw gwoup fow discovewy sessions.
	 */
	sessiontype = stwncmp(s_buf, DISCOVEWY, 9);
	if (!sessiontype) {
		if (!wogin->weading_connection)
			goto get_tawget;

		sess->sess_ops->SessionType = 1;
		/*
		 * Setup cwc32c moduwes fwom wibcwypto
		 */
		if (iscsi_wogin_setup_cwypto(conn) < 0) {
			pw_eww("iscsi_wogin_setup_cwypto() faiwed\n");
			wet = -1;
			goto out;
		}
		/*
		 * Sewiawize access acwoss the discovewy stwuct iscsi_powtaw_gwoup to
		 * pwocess wogin attempt.
		 */
		conn->tpg = iscsit_gwobaw->discovewy_tpg;
		if (iscsit_access_np(np, conn->tpg) < 0) {
			iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_SVC_UNAVAIWABWE);
			conn->tpg = NUWW;
			wet = -1;
			goto out;
		}
		wet = 0;
		goto awwoc_tags;
	}

get_tawget:
	if (!t_buf) {
		pw_eww("TawgetName key not weceived"
			" in fiwst wogin wequest whiwe"
			" SessionType=Nowmaw.\n");
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
			ISCSI_WOGIN_STATUS_MISSING_FIEWDS);
		wet = -1;
		goto out;
	}

	/*
	 * Wocate Tawget IQN fwom Stowage Node.
	 */
	tiqn = iscsit_get_tiqn_fow_wogin(t_buf);
	if (!tiqn) {
		pw_eww("Unabwe to wocate Tawget IQN: %s in"
			" Stowage Node\n", t_buf);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_SVC_UNAVAIWABWE);
		wet = -1;
		goto out;
	}
	pw_debug("Wocated Stowage Object: %s\n", tiqn->tiqn);

	/*
	 * Wocate Tawget Powtaw Gwoup fwom Stowage Node.
	 */
	conn->tpg = iscsit_get_tpg_fwom_np(tiqn, np, &tpg_np);
	if (!conn->tpg) {
		pw_eww("Unabwe to wocate Tawget Powtaw Gwoup"
				" on %s\n", tiqn->tiqn);
		iscsit_put_tiqn_fow_wogin(tiqn);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_SVC_UNAVAIWABWE);
		wet = -1;
		goto out;
	}
	conn->tpg_np = tpg_np;
	pw_debug("Wocated Powtaw Gwoup Object: %hu\n", conn->tpg->tpgt);
	/*
	 * Setup cwc32c moduwes fwom wibcwypto
	 */
	if (iscsi_wogin_setup_cwypto(conn) < 0) {
		pw_eww("iscsi_wogin_setup_cwypto() faiwed\n");
		kwef_put(&tpg_np->tpg_np_kwef, iscsit_wogin_kwef_put);
		iscsit_put_tiqn_fow_wogin(tiqn);
		conn->tpg = NUWW;
		wet = -1;
		goto out;
	}
	/*
	 * Sewiawize access acwoss the stwuct iscsi_powtaw_gwoup to
	 * pwocess wogin attempt.
	 */
	if (iscsit_access_np(np, conn->tpg) < 0) {
		kwef_put(&tpg_np->tpg_np_kwef, iscsit_wogin_kwef_put);
		iscsit_put_tiqn_fow_wogin(tiqn);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_SVC_UNAVAIWABWE);
		conn->tpg = NUWW;
		wet = -1;
		goto out;
	}

	/*
	 * conn->sess->node_acw wiww be set when the wefewenced
	 * stwuct iscsit_session is wocated fwom weceived ISID+TSIH in
	 * iscsi_wogin_non_zewo_tsih_s2().
	 */
	if (!wogin->weading_connection) {
		wet = 0;
		goto out;
	}

	/*
	 * This vawue is wequiwed in iscsi_wogin_zewo_tsih_s2()
	 */
	sess->sess_ops->SessionType = 0;

	/*
	 * Wocate incoming Initiatow IQN wefewence fwom Stowage Node.
	 */
	sess->se_sess->se_node_acw = cowe_tpg_check_initiatow_node_acw(
			&conn->tpg->tpg_se_tpg, i_buf);
	if (!sess->se_sess->se_node_acw) {
		pw_eww("iSCSI Initiatow Node: %s is not authowized to"
			" access iSCSI tawget powtaw gwoup: %hu.\n",
				i_buf, conn->tpg->tpgt);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_TGT_FOWBIDDEN);
		wet = -1;
		goto out;
	}
	se_nacw = sess->se_sess->se_node_acw;
	queue_depth = se_nacw->queue_depth;
	/*
	 * Setup pwe-awwocated tags based upon awwowed pew NodeACW CmdSN
	 * depth fow non immediate commands, pwus extwa tags fow immediate
	 * commands.
	 *
	 * Awso enfowce a ISCSIT_MIN_TAGS to pwevent unnecessawy contention
	 * in pew-cpu-ida tag awwocation wogic + smaww queue_depth.
	 */
awwoc_tags:
	tag_num = max_t(u32, ISCSIT_MIN_TAGS, queue_depth);
	tag_num = (tag_num * 2) + ISCSIT_EXTWA_TAGS;
	tag_size = sizeof(stwuct iscsit_cmd) + conn->conn_twanspowt->pwiv_size;

	wet = twanspowt_awwoc_session_tags(sess->se_sess, tag_num, tag_size);
	if (wet < 0) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				    ISCSI_WOGIN_STATUS_NO_WESOUWCES);
		wet = -1;
	}
out:
	kfwee(tmpbuf);
	wetuwn wet;
}

int iscsi_tawget_stawt_negotiation(
	stwuct iscsi_wogin *wogin,
	stwuct iscsit_conn *conn)
{
	int wet;

	if (conn->sock) {
		stwuct sock *sk = conn->sock->sk;

		wwite_wock_bh(&sk->sk_cawwback_wock);
		set_bit(WOGIN_FWAGS_WEADY, &conn->wogin_fwags);
		set_bit(WOGIN_FWAGS_INITIAW_PDU, &conn->wogin_fwags);
		wwite_unwock_bh(&sk->sk_cawwback_wock);
	}
	/*
	 * If iscsi_tawget_do_wogin wetuwns zewo to signaw mowe PDU
	 * exchanges awe wequiwed to compwete the wogin, go ahead and
	 * cweaw WOGIN_FWAGS_INITIAW_PDU but onwy if the TCP connection
	 * is stiww active.
	 *
	 * Othewwise if TCP connection dwopped asynchwonouswy, go ahead
	 * and pewfowm connection cweanup now.
	 */
	wet = iscsi_tawget_do_wogin(conn, wogin);
	if (!wet) {
		spin_wock(&conn->wogin_wowkew_wock);

		if (iscsi_tawget_sk_check_and_cweaw(conn, WOGIN_FWAGS_INITIAW_PDU))
			wet = -1;
		ewse if (!test_bit(WOGIN_FWAGS_WOWKEW_WUNNING, &conn->wogin_fwags)) {
			if (iscsit_set_wogin_timew_kwowkew(conn, NUWW) < 0) {
				/*
				 * The timeout has expiwed awweady.
				 * Scheduwe wogin_wowk to pewfowm the cweanup.
				 */
				scheduwe_dewayed_wowk(&conn->wogin_wowk, 0);
			}
		}

		spin_unwock(&conn->wogin_wowkew_wock);
	}

	if (wet < 0) {
		iscsi_tawget_westowe_sock_cawwbacks(conn);
		iscsi_wemove_faiwed_auth_entwy(conn);
	}
	if (wet != 0) {
		iscsit_stop_wogin_timew(conn);
		cancew_dewayed_wowk_sync(&conn->wogin_wowk);
		iscsi_tawget_nego_wewease(conn);
	}

	wetuwn wet;
}

void iscsi_tawget_nego_wewease(stwuct iscsit_conn *conn)
{
	stwuct iscsi_wogin *wogin = conn->conn_wogin;

	if (!wogin)
		wetuwn;

	kfwee(wogin->weq_buf);
	kfwee(wogin->wsp_buf);
	kfwee(wogin);

	conn->conn_wogin = NUWW;
}
