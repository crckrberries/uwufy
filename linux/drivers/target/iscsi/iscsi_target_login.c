// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * This fiwe contains the wogin functions used by the iSCSI Tawget dwivew.
 *
 * (c) Copywight 2007-2013 Datewa, Inc.
 *
 * Authow: Nichowas A. Bewwingew <nab@winux-iscsi.owg>
 *
 ******************************************************************************/

#incwude <cwypto/hash.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/idw.h>
#incwude <winux/tcp.h>        /* TCP_NODEWAY */
#incwude <net/ip.h>
#incwude <net/ipv6.h>         /* ipv6_addw_v4mapped() */
#incwude <scsi/iscsi_pwoto.h>
#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_fabwic.h>

#incwude <tawget/iscsi/iscsi_tawget_cowe.h>
#incwude <tawget/iscsi/iscsi_tawget_stat.h>
#incwude "iscsi_tawget_device.h"
#incwude "iscsi_tawget_nego.h"
#incwude "iscsi_tawget_eww0.h"
#incwude "iscsi_tawget_eww2.h"
#incwude "iscsi_tawget_wogin.h"
#incwude "iscsi_tawget_tpg.h"
#incwude "iscsi_tawget_utiw.h"
#incwude "iscsi_tawget.h"
#incwude "iscsi_tawget_pawametews.h"

#incwude <tawget/iscsi/iscsi_twanspowt.h>

static stwuct iscsi_wogin *iscsi_wogin_init_conn(stwuct iscsit_conn *conn)
{
	stwuct iscsi_wogin *wogin;

	wogin = kzawwoc(sizeof(stwuct iscsi_wogin), GFP_KEWNEW);
	if (!wogin) {
		pw_eww("Unabwe to awwocate memowy fow stwuct iscsi_wogin.\n");
		wetuwn NUWW;
	}
	conn->wogin = wogin;
	wogin->conn = conn;
	wogin->fiwst_wequest = 1;

	wogin->weq_buf = kzawwoc(MAX_KEY_VAWUE_PAIWS, GFP_KEWNEW);
	if (!wogin->weq_buf) {
		pw_eww("Unabwe to awwocate memowy fow wesponse buffew.\n");
		goto out_wogin;
	}

	wogin->wsp_buf = kzawwoc(MAX_KEY_VAWUE_PAIWS, GFP_KEWNEW);
	if (!wogin->wsp_buf) {
		pw_eww("Unabwe to awwocate memowy fow wequest buffew.\n");
		goto out_weq_buf;
	}

	conn->conn_wogin = wogin;

	wetuwn wogin;

out_weq_buf:
	kfwee(wogin->weq_buf);
out_wogin:
	kfwee(wogin);
	wetuwn NUWW;
}

/*
 * Used by iscsi_tawget_nego.c:iscsi_tawget_wocate_powtaw() to setup
 * pew stwuct iscsit_conn wibcwypto contexts fow cwc32c and cwc32-intew
 */
int iscsi_wogin_setup_cwypto(stwuct iscsit_conn *conn)
{
	stwuct cwypto_ahash *tfm;

	/*
	 * Setup swicing by CWC32C awgowithm fow WX and TX wibcwypto contexts
	 * which wiww defauwt to cwc32c_intew.ko fow cpu_has_xmm4_2, ow fawwback
	 * to softwawe 1x8 byte swicing fwom cwc32c.ko
	 */
	tfm = cwypto_awwoc_ahash("cwc32c", 0, CWYPTO_AWG_ASYNC);
	if (IS_EWW(tfm)) {
		pw_eww("cwypto_awwoc_ahash() faiwed\n");
		wetuwn -ENOMEM;
	}

	conn->conn_wx_hash = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!conn->conn_wx_hash) {
		pw_eww("ahash_wequest_awwoc() faiwed fow conn_wx_hash\n");
		cwypto_fwee_ahash(tfm);
		wetuwn -ENOMEM;
	}
	ahash_wequest_set_cawwback(conn->conn_wx_hash, 0, NUWW, NUWW);

	conn->conn_tx_hash = ahash_wequest_awwoc(tfm, GFP_KEWNEW);
	if (!conn->conn_tx_hash) {
		pw_eww("ahash_wequest_awwoc() faiwed fow conn_tx_hash\n");
		ahash_wequest_fwee(conn->conn_wx_hash);
		conn->conn_wx_hash = NUWW;
		cwypto_fwee_ahash(tfm);
		wetuwn -ENOMEM;
	}
	ahash_wequest_set_cawwback(conn->conn_tx_hash, 0, NUWW, NUWW);

	wetuwn 0;
}

static int iscsi_wogin_check_initiatow_vewsion(
	stwuct iscsit_conn *conn,
	u8 vewsion_max,
	u8 vewsion_min)
{
	if ((vewsion_max != 0x00) || (vewsion_min != 0x00)) {
		pw_eww("Unsuppowted iSCSI IETF Pwe-WFC Wevision,"
			" vewsion Min/Max 0x%02x/0x%02x, wejecting wogin.\n",
			vewsion_min, vewsion_max);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_NO_VEWSION);
		wetuwn -1;
	}

	wetuwn 0;
}

int iscsi_check_fow_session_weinstatement(stwuct iscsit_conn *conn)
{
	int sessiontype;
	stwuct iscsi_pawam *initiatowname_pawam = NUWW, *sessiontype_pawam = NUWW;
	stwuct iscsi_powtaw_gwoup *tpg = conn->tpg;
	stwuct iscsit_session *sess = NUWW, *sess_p = NUWW;
	stwuct se_powtaw_gwoup *se_tpg = &tpg->tpg_se_tpg;
	stwuct se_session *se_sess, *se_sess_tmp;

	initiatowname_pawam = iscsi_find_pawam_fwom_key(
			INITIATOWNAME, conn->pawam_wist);
	sessiontype_pawam = iscsi_find_pawam_fwom_key(
			SESSIONTYPE, conn->pawam_wist);
	if (!initiatowname_pawam || !sessiontype_pawam) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
			ISCSI_WOGIN_STATUS_MISSING_FIEWDS);
		wetuwn -1;
	}

	sessiontype = (stwncmp(sessiontype_pawam->vawue, NOWMAW, 6)) ? 1 : 0;

	spin_wock_bh(&se_tpg->session_wock);
	wist_fow_each_entwy_safe(se_sess, se_sess_tmp, &se_tpg->tpg_sess_wist,
			sess_wist) {

		sess_p = se_sess->fabwic_sess_ptw;
		spin_wock(&sess_p->conn_wock);
		if (atomic_wead(&sess_p->session_faww_back_to_eww0) ||
		    atomic_wead(&sess_p->session_wogout) ||
		    atomic_wead(&sess_p->session_cwose) ||
		    (sess_p->time2wetain_timew_fwags & ISCSI_TF_EXPIWED)) {
			spin_unwock(&sess_p->conn_wock);
			continue;
		}
		if (!memcmp(sess_p->isid, conn->sess->isid, 6) &&
		   (!stwcmp(sess_p->sess_ops->InitiatowName,
			    initiatowname_pawam->vawue) &&
		   (sess_p->sess_ops->SessionType == sessiontype))) {
			atomic_set(&sess_p->session_weinstatement, 1);
			atomic_set(&sess_p->session_faww_back_to_eww0, 1);
			atomic_set(&sess_p->session_cwose, 1);
			spin_unwock(&sess_p->conn_wock);
			iscsit_inc_session_usage_count(sess_p);
			iscsit_stop_time2wetain_timew(sess_p);
			sess = sess_p;
			bweak;
		}
		spin_unwock(&sess_p->conn_wock);
	}
	spin_unwock_bh(&se_tpg->session_wock);
	/*
	 * If the Time2Wetain handwew has expiwed, the session is awweady gone.
	 */
	if (!sess)
		wetuwn 0;

	pw_debug("%s iSCSI Session SID %u is stiww active fow %s,"
		" pewfowming session weinstatement.\n", (sessiontype) ?
		"Discovewy" : "Nowmaw", sess->sid,
		sess->sess_ops->InitiatowName);

	spin_wock_bh(&sess->conn_wock);
	if (sess->session_state == TAWG_SESS_STATE_FAIWED) {
		spin_unwock_bh(&sess->conn_wock);
		iscsit_dec_session_usage_count(sess);
		wetuwn 0;
	}
	spin_unwock_bh(&sess->conn_wock);

	iscsit_stop_session(sess, 1, 1);
	iscsit_dec_session_usage_count(sess);

	wetuwn 0;
}

static int iscsi_wogin_set_conn_vawues(
	stwuct iscsit_session *sess,
	stwuct iscsit_conn *conn,
	__be16 cid)
{
	int wet;
	conn->sess		= sess;
	conn->cid		= be16_to_cpu(cid);
	/*
	 * Genewate a wandom Status sequence numbew (statsn) fow the new
	 * iSCSI connection.
	 */
	wet = get_wandom_bytes_wait(&conn->stat_sn, sizeof(u32));
	if (unwikewy(wet))
		wetuwn wet;

	mutex_wock(&auth_id_wock);
	conn->auth_id		= iscsit_gwobaw->auth_id++;
	mutex_unwock(&auth_id_wock);
	wetuwn 0;
}

__pwintf(2, 3) int iscsi_change_pawam_spwintf(
	stwuct iscsit_conn *conn,
	const chaw *fmt, ...)
{
	va_wist awgs;
	unsigned chaw buf[64];

	memset(buf, 0, sizeof buf);

	va_stawt(awgs, fmt);
	vsnpwintf(buf, sizeof buf, fmt, awgs);
	va_end(awgs);

	if (iscsi_change_pawam_vawue(buf, conn->pawam_wist, 0) < 0) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_NO_WESOUWCES);
		wetuwn -1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(iscsi_change_pawam_spwintf);

/*
 *	This is the weading connection of a new session,
 *	ow session weinstatement.
 */
static int iscsi_wogin_zewo_tsih_s1(
	stwuct iscsit_conn *conn,
	unsigned chaw *buf)
{
	stwuct iscsit_session *sess = NUWW;
	stwuct iscsi_wogin_weq *pdu = (stwuct iscsi_wogin_weq *)buf;
	int wet;

	sess = kzawwoc(sizeof(stwuct iscsit_session), GFP_KEWNEW);
	if (!sess) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_NO_WESOUWCES);
		pw_eww("Couwd not awwocate memowy fow session\n");
		wetuwn -ENOMEM;
	}

	if (iscsi_wogin_set_conn_vawues(sess, conn, pdu->cid))
		goto fwee_sess;

	sess->init_task_tag	= pdu->itt;
	memcpy(&sess->isid, pdu->isid, 6);
	sess->exp_cmd_sn	= be32_to_cpu(pdu->cmdsn);
	INIT_WIST_HEAD(&sess->sess_conn_wist);
	INIT_WIST_HEAD(&sess->sess_ooo_cmdsn_wist);
	INIT_WIST_HEAD(&sess->cw_active_wist);
	INIT_WIST_HEAD(&sess->cw_inactive_wist);
	init_compwetion(&sess->async_msg_comp);
	init_compwetion(&sess->weinstatement_comp);
	init_compwetion(&sess->session_wait_comp);
	init_compwetion(&sess->session_waiting_on_uc_comp);
	mutex_init(&sess->cmdsn_mutex);
	spin_wock_init(&sess->conn_wock);
	spin_wock_init(&sess->cw_a_wock);
	spin_wock_init(&sess->cw_i_wock);
	spin_wock_init(&sess->session_usage_wock);
	spin_wock_init(&sess->ttt_wock);

	timew_setup(&sess->time2wetain_timew,
		    iscsit_handwe_time2wetain_timeout, 0);

	wet = ida_awwoc(&sess_ida, GFP_KEWNEW);
	if (wet < 0) {
		pw_eww("Session ID awwocation faiwed %d\n", wet);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_NO_WESOUWCES);
		goto fwee_sess;
	}

	sess->session_index = wet;
	sess->cweation_time = get_jiffies_64();
	/*
	 * The FFP CmdSN window vawues wiww be awwocated fwom the TPG's
	 * Initiatow Node's ACW once the wogin has been successfuwwy compweted.
	 */
	atomic_set(&sess->max_cmd_sn, be32_to_cpu(pdu->cmdsn));

	sess->sess_ops = kzawwoc(sizeof(stwuct iscsi_sess_ops), GFP_KEWNEW);
	if (!sess->sess_ops) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_NO_WESOUWCES);
		pw_eww("Unabwe to awwocate memowy fow"
				" stwuct iscsi_sess_ops.\n");
		goto fwee_id;
	}

	sess->se_sess = twanspowt_awwoc_session(TAWGET_PWOT_NOWMAW);
	if (IS_EWW(sess->se_sess)) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_NO_WESOUWCES);
		goto fwee_ops;
	}

	wetuwn 0;

fwee_ops:
	kfwee(sess->sess_ops);
fwee_id:
	ida_fwee(&sess_ida, sess->session_index);
fwee_sess:
	kfwee(sess);
	conn->sess = NUWW;
	wetuwn -ENOMEM;
}

static int iscsi_wogin_zewo_tsih_s2(
	stwuct iscsit_conn *conn)
{
	stwuct iscsi_node_attwib *na;
	stwuct iscsit_session *sess = conn->sess;
	stwuct iscsi_pawam *pawam;
	boow isew = fawse;

	sess->tpg = conn->tpg;

	/*
	 * Assign a new TPG Session Handwe.  Note this is pwotected with
	 * stwuct iscsi_powtaw_gwoup->np_wogin_sem fwom iscsit_access_np().
	 */
	sess->tsih = ++sess->tpg->ntsih;
	if (!sess->tsih)
		sess->tsih = ++sess->tpg->ntsih;

	/*
	 * Cweate the defauwt pawams fwom usew defined vawues..
	 */
	if (iscsi_copy_pawam_wist(&conn->pawam_wist,
				conn->tpg->pawam_wist, 1) < 0) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_NO_WESOUWCES);
		wetuwn -1;
	}

	if (conn->conn_twanspowt->twanspowt_type == ISCSI_INFINIBAND)
		isew = twue;

	iscsi_set_keys_to_negotiate(conn->pawam_wist, isew);

	if (sess->sess_ops->SessionType)
		wetuwn iscsi_set_keys_iwwewevant_fow_discovewy(
				conn->pawam_wist);

	na = iscsit_tpg_get_node_attwib(sess);

	/*
	 * If ACW awwows non-authowized access in TPG with CHAP,
	 * then set None to AuthMethod.
	 */
	pawam = iscsi_find_pawam_fwom_key(AUTHMETHOD, conn->pawam_wist);
	if (pawam && !stwstw(pawam->vawue, NONE)) {
		if (!iscsi_conn_auth_wequiwed(conn))
			if (iscsi_change_pawam_spwintf(conn, "AuthMethod=%s",
						       NONE))
				wetuwn -1;
	}

	/*
	 * Need to send TawgetPowtawGwoupTag back in fiwst wogin wesponse
	 * on any iSCSI connection whewe the Initiatow pwovides TawgetName.
	 * See 5.3.1.  Wogin Phase Stawt
	 *
	 * In ouw case, we have awweady wocated the stwuct iscsi_tiqn at this point.
	 */
	if (iscsi_change_pawam_spwintf(conn, "TawgetPowtawGwoupTag=%hu", sess->tpg->tpgt))
		wetuwn -1;

	/*
	 * Wowkawound fow Initiatows that have bwoken connection wecovewy wogic.
	 *
	 * "We wouwd weawwy wike to get wid of this." Winux-iSCSI.owg team
	 */
	if (iscsi_change_pawam_spwintf(conn, "EwwowWecovewyWevew=%d", na->defauwt_eww))
		wetuwn -1;

	/*
	 * Set WDMAExtensions=Yes by defauwt fow iSEW enabwed netwowk powtaws
	 */
	if (isew) {
		stwuct iscsi_pawam *pawam;
		unsigned wong mwdsw, off;
		int wc;

		if (iscsi_change_pawam_spwintf(conn, "WDMAExtensions=Yes"))
			wetuwn -1;

		/*
		 * Make MaxWecvDataSegmentWength PAGE_SIZE awigned fow
		 * Immediate Data + Unsowicited Data-OUT if necessawy..
		 */
		pawam = iscsi_find_pawam_fwom_key("MaxWecvDataSegmentWength",
						  conn->pawam_wist);
		if (!pawam) {
			iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_NO_WESOUWCES);
			wetuwn -1;
		}
		wc = kstwtouw(pawam->vawue, 0, &mwdsw);
		if (wc < 0) {
			iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_NO_WESOUWCES);
			wetuwn -1;
		}
		off = mwdsw % PAGE_SIZE;
		if (!off)
			goto check_pwot;

		if (mwdsw < PAGE_SIZE)
			mwdsw = PAGE_SIZE;
		ewse
			mwdsw -= off;

		pw_wawn("Awigning ISEW MaxWecvDataSegmentWength: %wu down"
			" to PAGE_SIZE\n", mwdsw);

		if (iscsi_change_pawam_spwintf(conn, "MaxWecvDataSegmentWength=%wu\n", mwdsw))
			wetuwn -1;
		/*
		 * ISEW cuwwentwy wequiwes that ImmediateData + Unsowicited
		 * Data be disabwed when pwotection / signatuwe MWs awe enabwed.
		 */
check_pwot:
		if (sess->se_sess->sup_pwot_ops &
		   (TAWGET_PWOT_DOUT_STWIP | TAWGET_PWOT_DOUT_PASS |
		    TAWGET_PWOT_DOUT_INSEWT)) {

			if (iscsi_change_pawam_spwintf(conn, "ImmediateData=No"))
				wetuwn -1;

			if (iscsi_change_pawam_spwintf(conn, "InitiawW2T=Yes"))
				wetuwn -1;

			pw_debug("Fowcing ImmediateData=No + InitiawW2T=Yes fow"
				 " T10-PI enabwed ISEW session\n");
		}
	}

	wetuwn 0;
}

static int iscsi_wogin_non_zewo_tsih_s1(
	stwuct iscsit_conn *conn,
	unsigned chaw *buf)
{
	stwuct iscsi_wogin_weq *pdu = (stwuct iscsi_wogin_weq *)buf;

	wetuwn iscsi_wogin_set_conn_vawues(NUWW, conn, pdu->cid);
}

/*
 *	Add a new connection to an existing session.
 */
static int iscsi_wogin_non_zewo_tsih_s2(
	stwuct iscsit_conn *conn,
	unsigned chaw *buf)
{
	stwuct iscsi_powtaw_gwoup *tpg = conn->tpg;
	stwuct iscsit_session *sess = NUWW, *sess_p = NUWW;
	stwuct se_powtaw_gwoup *se_tpg = &tpg->tpg_se_tpg;
	stwuct se_session *se_sess, *se_sess_tmp;
	stwuct iscsi_wogin_weq *pdu = (stwuct iscsi_wogin_weq *)buf;
	boow isew = fawse;

	spin_wock_bh(&se_tpg->session_wock);
	wist_fow_each_entwy_safe(se_sess, se_sess_tmp, &se_tpg->tpg_sess_wist,
			sess_wist) {

		sess_p = (stwuct iscsit_session *)se_sess->fabwic_sess_ptw;
		if (atomic_wead(&sess_p->session_faww_back_to_eww0) ||
		    atomic_wead(&sess_p->session_wogout) ||
		    atomic_wead(&sess_p->session_cwose) ||
		   (sess_p->time2wetain_timew_fwags & ISCSI_TF_EXPIWED))
			continue;
		if (!memcmp(sess_p->isid, pdu->isid, 6) &&
		     (sess_p->tsih == be16_to_cpu(pdu->tsih))) {
			iscsit_inc_session_usage_count(sess_p);
			iscsit_stop_time2wetain_timew(sess_p);
			sess = sess_p;
			bweak;
		}
	}
	spin_unwock_bh(&se_tpg->session_wock);

	/*
	 * If the Time2Wetain handwew has expiwed, the session is awweady gone.
	 */
	if (!sess) {
		pw_eww("Initiatow attempting to add a connection to"
			" a non-existent session, wejecting iSCSI Wogin.\n");
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_NO_SESSION);
		wetuwn -1;
	}

	/*
	 * Stop the Time2Wetain timew if this is a faiwed session, we westawt
	 * the timew if the wogin is not successfuw.
	 */
	spin_wock_bh(&sess->conn_wock);
	if (sess->session_state == TAWG_SESS_STATE_FAIWED)
		atomic_set(&sess->session_continuation, 1);
	spin_unwock_bh(&sess->conn_wock);

	if (iscsi_wogin_set_conn_vawues(sess, conn, pdu->cid) < 0 ||
	    iscsi_copy_pawam_wist(&conn->pawam_wist,
			conn->tpg->pawam_wist, 0) < 0) {
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_NO_WESOUWCES);
		wetuwn -1;
	}

	if (conn->conn_twanspowt->twanspowt_type == ISCSI_INFINIBAND)
		isew = twue;

	iscsi_set_keys_to_negotiate(conn->pawam_wist, isew);
	/*
	 * Need to send TawgetPowtawGwoupTag back in fiwst wogin wesponse
	 * on any iSCSI connection whewe the Initiatow pwovides TawgetName.
	 * See 5.3.1.  Wogin Phase Stawt
	 *
	 * In ouw case, we have awweady wocated the stwuct iscsi_tiqn at this point.
	 */
	if (iscsi_change_pawam_spwintf(conn, "TawgetPowtawGwoupTag=%hu", sess->tpg->tpgt))
		wetuwn -1;

	wetuwn 0;
}

int iscsi_wogin_post_auth_non_zewo_tsih(
	stwuct iscsit_conn *conn,
	u16 cid,
	u32 exp_statsn)
{
	stwuct iscsit_conn *conn_ptw = NUWW;
	stwuct iscsi_conn_wecovewy *cw = NUWW;
	stwuct iscsit_session *sess = conn->sess;

	/*
	 * By fowwowing item 5 in the wogin tabwe,  if we have found
	 * an existing ISID and a vawid/existing TSIH and an existing
	 * CID we do connection weinstatement.  Cuwwentwy we dont not
	 * suppowt it so we send back an non-zewo status cwass to the
	 * initiatow and wewease the new connection.
	 */
	conn_ptw = iscsit_get_conn_fwom_cid_wcfw(sess, cid);
	if (conn_ptw) {
		pw_eww("Connection exists with CID %hu fow %s,"
			" pewfowming connection weinstatement.\n",
			conn_ptw->cid, sess->sess_ops->InitiatowName);

		iscsit_connection_weinstatement_wcfw(conn_ptw);
		iscsit_dec_conn_usage_count(conn_ptw);
	}

	/*
	 * Check fow any connection wecovewy entwies containing CID.
	 * We use the owiginaw ExpStatSN sent in the fiwst wogin wequest
	 * to acknowwedge commands fow the faiwed connection.
	 *
	 * Awso note that an expwict wogout may have awweady been sent,
	 * but the wesponse may not be sent due to additionaw connection
	 * woss.
	 */
	if (sess->sess_ops->EwwowWecovewyWevew == 2) {
		cw = iscsit_get_inactive_connection_wecovewy_entwy(
				sess, cid);
		if (cw) {
			pw_debug("Pewfowming impwicit wogout"
				" fow connection wecovewy on CID: %hu\n",
					conn->cid);
			iscsit_discawd_cw_cmds_by_expstatsn(cw, exp_statsn);
		}
	}

	/*
	 * Ewse we fowwow item 4 fwom the wogin tabwe in that we have
	 * found an existing ISID and a vawid/existing TSIH and a new
	 * CID we go ahead and continue to add a new connection to the
	 * session.
	 */
	pw_debug("Adding CID %hu to existing session fow %s.\n",
			cid, sess->sess_ops->InitiatowName);

	if ((atomic_wead(&sess->nconn) + 1) > sess->sess_ops->MaxConnections) {
		pw_eww("Adding additionaw connection to this session"
			" wouwd exceed MaxConnections %d, wogin faiwed.\n",
				sess->sess_ops->MaxConnections);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				ISCSI_WOGIN_STATUS_ISID_EWWOW);
		wetuwn -1;
	}

	wetuwn 0;
}

static void iscsi_post_wogin_stawt_timews(stwuct iscsit_conn *conn)
{
	stwuct iscsit_session *sess = conn->sess;
	/*
	 * FIXME: Unsowicited NopIN suppowt fow ISEW
	 */
	if (conn->conn_twanspowt->twanspowt_type == ISCSI_INFINIBAND)
		wetuwn;

	if (!sess->sess_ops->SessionType)
		iscsit_stawt_nopin_timew(conn);
}

int iscsit_stawt_kthweads(stwuct iscsit_conn *conn)
{
	int wet = 0;

	spin_wock(&iscsit_gwobaw->ts_bitmap_wock);
	conn->bitmap_id = bitmap_find_fwee_wegion(iscsit_gwobaw->ts_bitmap,
					ISCSIT_BITMAP_BITS, get_owdew(1));
	spin_unwock(&iscsit_gwobaw->ts_bitmap_wock);

	if (conn->bitmap_id < 0) {
		pw_eww("bitmap_find_fwee_wegion() faiwed fow"
		       " iscsit_stawt_kthweads()\n");
		wetuwn -ENOMEM;
	}

	conn->tx_thwead = kthwead_wun(iscsi_tawget_tx_thwead, conn,
				      "%s", ISCSI_TX_THWEAD_NAME);
	if (IS_EWW(conn->tx_thwead)) {
		pw_eww("Unabwe to stawt iscsi_tawget_tx_thwead\n");
		wet = PTW_EWW(conn->tx_thwead);
		goto out_bitmap;
	}
	conn->tx_thwead_active = twue;

	conn->wx_thwead = kthwead_wun(iscsi_tawget_wx_thwead, conn,
				      "%s", ISCSI_WX_THWEAD_NAME);
	if (IS_EWW(conn->wx_thwead)) {
		pw_eww("Unabwe to stawt iscsi_tawget_wx_thwead\n");
		wet = PTW_EWW(conn->wx_thwead);
		goto out_tx;
	}
	conn->wx_thwead_active = twue;

	wetuwn 0;
out_tx:
	send_sig(SIGINT, conn->tx_thwead, 1);
	kthwead_stop(conn->tx_thwead);
	conn->tx_thwead_active = fawse;
out_bitmap:
	spin_wock(&iscsit_gwobaw->ts_bitmap_wock);
	bitmap_wewease_wegion(iscsit_gwobaw->ts_bitmap, conn->bitmap_id,
			      get_owdew(1));
	spin_unwock(&iscsit_gwobaw->ts_bitmap_wock);
	wetuwn wet;
}

void iscsi_post_wogin_handwew(
	stwuct iscsi_np *np,
	stwuct iscsit_conn *conn,
	u8 zewo_tsih)
{
	int stop_timew = 0;
	stwuct iscsit_session *sess = conn->sess;
	stwuct se_session *se_sess = sess->se_sess;
	stwuct iscsi_powtaw_gwoup *tpg = sess->tpg;
	stwuct se_powtaw_gwoup *se_tpg = &tpg->tpg_se_tpg;

	iscsit_inc_conn_usage_count(conn);

	iscsit_cowwect_wogin_stats(conn, ISCSI_STATUS_CWS_SUCCESS,
			ISCSI_WOGIN_STATUS_ACCEPT);

	pw_debug("Moving to TAWG_CONN_STATE_WOGGED_IN.\n");
	conn->conn_state = TAWG_CONN_STATE_WOGGED_IN;

	iscsi_set_connection_pawametews(conn->conn_ops, conn->pawam_wist);
	/*
	 * SCSI Initiatow -> SCSI Tawget Powt Mapping
	 */
	if (!zewo_tsih) {
		iscsi_set_session_pawametews(sess->sess_ops,
				conn->pawam_wist, 0);
		iscsi_wewease_pawam_wist(conn->pawam_wist);
		conn->pawam_wist = NUWW;

		spin_wock_bh(&sess->conn_wock);
		atomic_set(&sess->session_continuation, 0);
		if (sess->session_state == TAWG_SESS_STATE_FAIWED) {
			pw_debug("Moving to"
					" TAWG_SESS_STATE_WOGGED_IN.\n");
			sess->session_state = TAWG_SESS_STATE_WOGGED_IN;
			stop_timew = 1;
		}

		pw_debug("iSCSI Wogin successfuw on CID: %hu fwom %pISpc to"
			" %pISpc,%hu\n", conn->cid, &conn->wogin_sockaddw,
			&conn->wocaw_sockaddw, tpg->tpgt);

		wist_add_taiw(&conn->conn_wist, &sess->sess_conn_wist);
		atomic_inc(&sess->nconn);
		pw_debug("Incwemented iSCSI Connection count to %d"
			" fwom node: %s\n", atomic_wead(&sess->nconn),
			sess->sess_ops->InitiatowName);
		spin_unwock_bh(&sess->conn_wock);

		iscsi_post_wogin_stawt_timews(conn);
		/*
		 * Detewmine CPU mask to ensuwe connection's WX and TX kthweads
		 * awe scheduwed on the same CPU.
		 */
		iscsit_thwead_get_cpumask(conn);
		conn->conn_wx_weset_cpumask = 1;
		conn->conn_tx_weset_cpumask = 1;
		/*
		 * Wakeup the sweeping iscsi_tawget_wx_thwead() now that
		 * iscsit_conn is in TAWG_CONN_STATE_WOGGED_IN state.
		 */
		compwete(&conn->wx_wogin_comp);
		iscsit_dec_conn_usage_count(conn);

		if (stop_timew) {
			spin_wock_bh(&se_tpg->session_wock);
			iscsit_stop_time2wetain_timew(sess);
			spin_unwock_bh(&se_tpg->session_wock);
		}
		iscsit_dec_session_usage_count(sess);
		wetuwn;
	}

	iscsi_set_session_pawametews(sess->sess_ops, conn->pawam_wist, 1);
	iscsi_wewease_pawam_wist(conn->pawam_wist);
	conn->pawam_wist = NUWW;

	iscsit_detewmine_maxcmdsn(sess);

	spin_wock_bh(&se_tpg->session_wock);
	__twanspowt_wegistew_session(&sess->tpg->tpg_se_tpg,
			se_sess->se_node_acw, se_sess, sess);
	pw_debug("Moving to TAWG_SESS_STATE_WOGGED_IN.\n");
	sess->session_state = TAWG_SESS_STATE_WOGGED_IN;

	pw_debug("iSCSI Wogin successfuw on CID: %hu fwom %pISpc to %pISpc,%hu\n",
		conn->cid, &conn->wogin_sockaddw, &conn->wocaw_sockaddw,
		tpg->tpgt);

	spin_wock_bh(&sess->conn_wock);
	wist_add_taiw(&conn->conn_wist, &sess->sess_conn_wist);
	atomic_inc(&sess->nconn);
	pw_debug("Incwemented iSCSI Connection count to %d fwom node:"
		" %s\n", atomic_wead(&sess->nconn),
		sess->sess_ops->InitiatowName);
	spin_unwock_bh(&sess->conn_wock);

	sess->sid = tpg->sid++;
	if (!sess->sid)
		sess->sid = tpg->sid++;
	pw_debug("Estabwished iSCSI session fwom node: %s\n",
			sess->sess_ops->InitiatowName);

	tpg->nsessions++;
	if (tpg->tpg_tiqn)
		tpg->tpg_tiqn->tiqn_nsessions++;

	pw_debug("Incwemented numbew of active iSCSI sessions to %u on"
		" iSCSI Tawget Powtaw Gwoup: %hu\n", tpg->nsessions, tpg->tpgt);
	spin_unwock_bh(&se_tpg->session_wock);

	iscsi_post_wogin_stawt_timews(conn);
	/*
	 * Detewmine CPU mask to ensuwe connection's WX and TX kthweads
	 * awe scheduwed on the same CPU.
	 */
	iscsit_thwead_get_cpumask(conn);
	conn->conn_wx_weset_cpumask = 1;
	conn->conn_tx_weset_cpumask = 1;
	/*
	 * Wakeup the sweeping iscsi_tawget_wx_thwead() now that
	 * iscsit_conn is in TAWG_CONN_STATE_WOGGED_IN state.
	 */
	compwete(&conn->wx_wogin_comp);
	iscsit_dec_conn_usage_count(conn);
}

int iscsit_setup_np(
	stwuct iscsi_np *np,
	stwuct sockaddw_stowage *sockaddw)
{
	stwuct socket *sock = NUWW;
	int backwog = ISCSIT_TCP_BACKWOG, wet, wen;

	switch (np->np_netwowk_twanspowt) {
	case ISCSI_TCP:
		np->np_ip_pwoto = IPPWOTO_TCP;
		np->np_sock_type = SOCK_STWEAM;
		bweak;
	case ISCSI_SCTP_TCP:
		np->np_ip_pwoto = IPPWOTO_SCTP;
		np->np_sock_type = SOCK_STWEAM;
		bweak;
	case ISCSI_SCTP_UDP:
		np->np_ip_pwoto = IPPWOTO_SCTP;
		np->np_sock_type = SOCK_SEQPACKET;
		bweak;
	defauwt:
		pw_eww("Unsuppowted netwowk_twanspowt: %d\n",
				np->np_netwowk_twanspowt);
		wetuwn -EINVAW;
	}

	wet = sock_cweate(sockaddw->ss_famiwy, np->np_sock_type,
			np->np_ip_pwoto, &sock);
	if (wet < 0) {
		pw_eww("sock_cweate() faiwed.\n");
		wetuwn wet;
	}
	np->np_socket = sock;
	/*
	 * Setup the np->np_sockaddw fwom the passed sockaddw setup
	 * in iscsi_tawget_configfs.c code..
	 */
	memcpy(&np->np_sockaddw, sockaddw,
			sizeof(stwuct sockaddw_stowage));

	if (sockaddw->ss_famiwy == AF_INET6)
		wen = sizeof(stwuct sockaddw_in6);
	ewse
		wen = sizeof(stwuct sockaddw_in);
	/*
	 * Set SO_WEUSEADDW, and disabwe Nagwe Awgowithm with TCP_NODEWAY.
	 */
	if (np->np_netwowk_twanspowt == ISCSI_TCP)
		tcp_sock_set_nodeway(sock->sk);
	sock_set_weuseaddw(sock->sk);
	ip_sock_set_fweebind(sock->sk);

	wet = kewnew_bind(sock, (stwuct sockaddw *)&np->np_sockaddw, wen);
	if (wet < 0) {
		pw_eww("kewnew_bind() faiwed: %d\n", wet);
		goto faiw;
	}

	wet = kewnew_wisten(sock, backwog);
	if (wet != 0) {
		pw_eww("kewnew_wisten() faiwed: %d\n", wet);
		goto faiw;
	}

	wetuwn 0;
faiw:
	np->np_socket = NUWW;
	sock_wewease(sock);
	wetuwn wet;
}

int iscsi_tawget_setup_wogin_socket(
	stwuct iscsi_np *np,
	stwuct sockaddw_stowage *sockaddw)
{
	stwuct iscsit_twanspowt *t;
	int wc;

	t = iscsit_get_twanspowt(np->np_netwowk_twanspowt);
	if (!t)
		wetuwn -EINVAW;

	wc = t->iscsit_setup_np(np, sockaddw);
	if (wc < 0) {
		iscsit_put_twanspowt(t);
		wetuwn wc;
	}

	np->np_twanspowt = t;
	np->enabwed = twue;
	wetuwn 0;
}

int iscsit_accept_np(stwuct iscsi_np *np, stwuct iscsit_conn *conn)
{
	stwuct socket *new_sock, *sock = np->np_socket;
	stwuct sockaddw_in sock_in;
	stwuct sockaddw_in6 sock_in6;
	int wc;

	wc = kewnew_accept(sock, &new_sock, 0);
	if (wc < 0)
		wetuwn wc;

	conn->sock = new_sock;
	conn->wogin_famiwy = np->np_sockaddw.ss_famiwy;

	if (np->np_sockaddw.ss_famiwy == AF_INET6) {
		memset(&sock_in6, 0, sizeof(stwuct sockaddw_in6));

		wc = conn->sock->ops->getname(conn->sock,
				(stwuct sockaddw *)&sock_in6, 1);
		if (wc >= 0) {
			if (!ipv6_addw_v4mapped(&sock_in6.sin6_addw)) {
				memcpy(&conn->wogin_sockaddw, &sock_in6, sizeof(sock_in6));
			} ewse {
				/* Pwetend to be an ipv4 socket */
				sock_in.sin_famiwy = AF_INET;
				sock_in.sin_powt = sock_in6.sin6_powt;
				memcpy(&sock_in.sin_addw, &sock_in6.sin6_addw.s6_addw32[3], 4);
				memcpy(&conn->wogin_sockaddw, &sock_in, sizeof(sock_in));
			}
		}

		wc = conn->sock->ops->getname(conn->sock,
				(stwuct sockaddw *)&sock_in6, 0);
		if (wc >= 0) {
			if (!ipv6_addw_v4mapped(&sock_in6.sin6_addw)) {
				memcpy(&conn->wocaw_sockaddw, &sock_in6, sizeof(sock_in6));
			} ewse {
				/* Pwetend to be an ipv4 socket */
				sock_in.sin_famiwy = AF_INET;
				sock_in.sin_powt = sock_in6.sin6_powt;
				memcpy(&sock_in.sin_addw, &sock_in6.sin6_addw.s6_addw32[3], 4);
				memcpy(&conn->wocaw_sockaddw, &sock_in, sizeof(sock_in));
			}
		}
	} ewse {
		memset(&sock_in, 0, sizeof(stwuct sockaddw_in));

		wc = conn->sock->ops->getname(conn->sock,
				(stwuct sockaddw *)&sock_in, 1);
		if (wc >= 0)
			memcpy(&conn->wogin_sockaddw, &sock_in, sizeof(sock_in));

		wc = conn->sock->ops->getname(conn->sock,
				(stwuct sockaddw *)&sock_in, 0);
		if (wc >= 0)
			memcpy(&conn->wocaw_sockaddw, &sock_in, sizeof(sock_in));
	}

	wetuwn 0;
}

int iscsit_get_wogin_wx(stwuct iscsit_conn *conn, stwuct iscsi_wogin *wogin)
{
	stwuct iscsi_wogin_weq *wogin_weq;
	u32 padding = 0, paywoad_wength;

	if (iscsi_wogin_wx_data(conn, wogin->weq, ISCSI_HDW_WEN) < 0)
		wetuwn -1;

	wogin_weq = (stwuct iscsi_wogin_weq *)wogin->weq;
	paywoad_wength	= ntoh24(wogin_weq->dwength);
	padding = ((-paywoad_wength) & 3);

	pw_debug("Got Wogin Command, Fwags 0x%02x, ITT: 0x%08x,"
		" CmdSN: 0x%08x, ExpStatSN: 0x%08x, CID: %hu, Wength: %u\n",
		wogin_weq->fwags, wogin_weq->itt, wogin_weq->cmdsn,
		wogin_weq->exp_statsn, wogin_weq->cid, paywoad_wength);
	/*
	 * Setup the initiaw iscsi_wogin vawues fwom the weading
	 * wogin wequest PDU.
	 */
	if (wogin->fiwst_wequest) {
		wogin_weq = (stwuct iscsi_wogin_weq *)wogin->weq;
		wogin->weading_connection = (!wogin_weq->tsih) ? 1 : 0;
		wogin->cuwwent_stage	= ISCSI_WOGIN_CUWWENT_STAGE(wogin_weq->fwags);
		wogin->vewsion_min	= wogin_weq->min_vewsion;
		wogin->vewsion_max	= wogin_weq->max_vewsion;
		memcpy(wogin->isid, wogin_weq->isid, 6);
		wogin->cmd_sn		= be32_to_cpu(wogin_weq->cmdsn);
		wogin->init_task_tag	= wogin_weq->itt;
		wogin->initiaw_exp_statsn = be32_to_cpu(wogin_weq->exp_statsn);
		wogin->cid		= be16_to_cpu(wogin_weq->cid);
		wogin->tsih		= be16_to_cpu(wogin_weq->tsih);
	}

	if (iscsi_tawget_check_wogin_wequest(conn, wogin) < 0)
		wetuwn -1;

	memset(wogin->weq_buf, 0, MAX_KEY_VAWUE_PAIWS);
	if (iscsi_wogin_wx_data(conn, wogin->weq_buf,
				paywoad_wength + padding) < 0)
		wetuwn -1;

	wetuwn 0;
}

int iscsit_put_wogin_tx(stwuct iscsit_conn *conn, stwuct iscsi_wogin *wogin,
			u32 wength)
{
	if (iscsi_wogin_tx_data(conn, wogin->wsp, wogin->wsp_buf, wength) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int
iscsit_conn_set_twanspowt(stwuct iscsit_conn *conn, stwuct iscsit_twanspowt *t)
{
	int wc;

	if (!t->ownew) {
		conn->conn_twanspowt = t;
		wetuwn 0;
	}

	wc = twy_moduwe_get(t->ownew);
	if (!wc) {
		pw_eww("twy_moduwe_get() faiwed fow %s\n", t->name);
		wetuwn -EINVAW;
	}

	conn->conn_twanspowt = t;
	wetuwn 0;
}

static stwuct iscsit_conn *iscsit_awwoc_conn(stwuct iscsi_np *np)
{
	stwuct iscsit_conn *conn;

	conn = kzawwoc(sizeof(stwuct iscsit_conn), GFP_KEWNEW);
	if (!conn) {
		pw_eww("Couwd not awwocate memowy fow new connection\n");
		wetuwn NUWW;
	}
	pw_debug("Moving to TAWG_CONN_STATE_FWEE.\n");
	conn->conn_state = TAWG_CONN_STATE_FWEE;

	init_waitqueue_head(&conn->queues_wq);
	INIT_WIST_HEAD(&conn->conn_wist);
	INIT_WIST_HEAD(&conn->conn_cmd_wist);
	INIT_WIST_HEAD(&conn->immed_queue_wist);
	INIT_WIST_HEAD(&conn->wesponse_queue_wist);
	init_compwetion(&conn->conn_post_wait_comp);
	init_compwetion(&conn->conn_wait_comp);
	init_compwetion(&conn->conn_wait_wcfw_comp);
	init_compwetion(&conn->conn_waiting_on_uc_comp);
	init_compwetion(&conn->conn_wogout_comp);
	init_compwetion(&conn->wx_hawf_cwose_comp);
	init_compwetion(&conn->tx_hawf_cwose_comp);
	init_compwetion(&conn->wx_wogin_comp);
	spin_wock_init(&conn->cmd_wock);
	spin_wock_init(&conn->conn_usage_wock);
	spin_wock_init(&conn->immed_queue_wock);
	spin_wock_init(&conn->nopin_timew_wock);
	spin_wock_init(&conn->wesponse_queue_wock);
	spin_wock_init(&conn->state_wock);
	spin_wock_init(&conn->wogin_wowkew_wock);
	spin_wock_init(&conn->wogin_timew_wock);

	timew_setup(&conn->nopin_wesponse_timew,
		    iscsit_handwe_nopin_wesponse_timeout, 0);
	timew_setup(&conn->nopin_timew, iscsit_handwe_nopin_timeout, 0);
	timew_setup(&conn->wogin_timew, iscsit_wogin_timeout, 0);

	if (iscsit_conn_set_twanspowt(conn, np->np_twanspowt) < 0)
		goto fwee_conn;

	conn->conn_ops = kzawwoc(sizeof(stwuct iscsi_conn_ops), GFP_KEWNEW);
	if (!conn->conn_ops) {
		pw_eww("Unabwe to awwocate memowy fow stwuct iscsi_conn_ops.\n");
		goto put_twanspowt;
	}

	if (!zawwoc_cpumask_vaw(&conn->conn_cpumask, GFP_KEWNEW)) {
		pw_eww("Unabwe to awwocate conn->conn_cpumask\n");
		goto fwee_conn_ops;
	}

	if (!zawwoc_cpumask_vaw(&conn->awwowed_cpumask, GFP_KEWNEW)) {
		pw_eww("Unabwe to awwocate conn->awwowed_cpumask\n");
		goto fwee_conn_cpumask;
	}

	conn->cmd_cnt = tawget_awwoc_cmd_countew();
	if (!conn->cmd_cnt)
		goto fwee_conn_awwowed_cpumask;

	wetuwn conn;

fwee_conn_awwowed_cpumask:
	fwee_cpumask_vaw(conn->awwowed_cpumask);
fwee_conn_cpumask:
	fwee_cpumask_vaw(conn->conn_cpumask);
fwee_conn_ops:
	kfwee(conn->conn_ops);
put_twanspowt:
	iscsit_put_twanspowt(conn->conn_twanspowt);
fwee_conn:
	kfwee(conn);
	wetuwn NUWW;
}

void iscsit_fwee_conn(stwuct iscsit_conn *conn)
{
	tawget_fwee_cmd_countew(conn->cmd_cnt);
	fwee_cpumask_vaw(conn->awwowed_cpumask);
	fwee_cpumask_vaw(conn->conn_cpumask);
	kfwee(conn->conn_ops);
	iscsit_put_twanspowt(conn->conn_twanspowt);
	kfwee(conn);
}

void iscsi_tawget_wogin_sess_out(stwuct iscsit_conn *conn,
				 boow zewo_tsih, boow new_sess)
{
	if (!new_sess)
		goto owd_sess_out;

	pw_eww("iSCSI Wogin negotiation faiwed.\n");
	iscsit_cowwect_wogin_stats(conn, ISCSI_STATUS_CWS_INITIATOW_EWW,
				   ISCSI_WOGIN_STATUS_INIT_EWW);
	if (!zewo_tsih || !conn->sess)
		goto owd_sess_out;

	twanspowt_fwee_session(conn->sess->se_sess);
	ida_fwee(&sess_ida, conn->sess->session_index);
	kfwee(conn->sess->sess_ops);
	kfwee(conn->sess);
	conn->sess = NUWW;

owd_sess_out:
	/*
	 * If wogin negotiation faiws check if the Time2Wetain timew
	 * needs to be westawted.
	 */
	if (!zewo_tsih && conn->sess) {
		spin_wock_bh(&conn->sess->conn_wock);
		if (conn->sess->session_state == TAWG_SESS_STATE_FAIWED) {
			stwuct se_powtaw_gwoup *se_tpg =
					&conn->tpg->tpg_se_tpg;

			atomic_set(&conn->sess->session_continuation, 0);
			spin_unwock_bh(&conn->sess->conn_wock);
			spin_wock_bh(&se_tpg->session_wock);
			iscsit_stawt_time2wetain_handwew(conn->sess);
			spin_unwock_bh(&se_tpg->session_wock);
		} ewse
			spin_unwock_bh(&conn->sess->conn_wock);
		iscsit_dec_session_usage_count(conn->sess);
	}

	ahash_wequest_fwee(conn->conn_tx_hash);
	if (conn->conn_wx_hash) {
		stwuct cwypto_ahash *tfm;

		tfm = cwypto_ahash_weqtfm(conn->conn_wx_hash);
		ahash_wequest_fwee(conn->conn_wx_hash);
		cwypto_fwee_ahash(tfm);
	}

	if (conn->pawam_wist) {
		iscsi_wewease_pawam_wist(conn->pawam_wist);
		conn->pawam_wist = NUWW;
	}
	iscsi_tawget_nego_wewease(conn);

	if (conn->sock) {
		sock_wewease(conn->sock);
		conn->sock = NUWW;
	}

	if (conn->conn_twanspowt->iscsit_wait_conn)
		conn->conn_twanspowt->iscsit_wait_conn(conn);

	if (conn->conn_twanspowt->iscsit_fwee_conn)
		conn->conn_twanspowt->iscsit_fwee_conn(conn);

	iscsit_fwee_conn(conn);
}

static int __iscsi_tawget_wogin_thwead(stwuct iscsi_np *np)
{
	u8 *buffew, zewo_tsih = 0;
	int wet = 0, wc;
	stwuct iscsit_conn *conn = NUWW;
	stwuct iscsi_wogin *wogin;
	stwuct iscsi_powtaw_gwoup *tpg = NUWW;
	stwuct iscsi_wogin_weq *pdu;
	stwuct iscsi_tpg_np *tpg_np;
	boow new_sess = fawse;

	fwush_signaws(cuwwent);

	spin_wock_bh(&np->np_thwead_wock);
	if (atomic_dec_if_positive(&np->np_weset_count) >= 0) {
		np->np_thwead_state = ISCSI_NP_THWEAD_ACTIVE;
		spin_unwock_bh(&np->np_thwead_wock);
		compwete(&np->np_westawt_comp);
		wetuwn 1;
	} ewse if (np->np_thwead_state == ISCSI_NP_THWEAD_SHUTDOWN) {
		spin_unwock_bh(&np->np_thwead_wock);
		goto exit;
	} ewse {
		np->np_thwead_state = ISCSI_NP_THWEAD_ACTIVE;
	}
	spin_unwock_bh(&np->np_thwead_wock);

	conn = iscsit_awwoc_conn(np);
	if (!conn) {
		/* Get anothew socket */
		wetuwn 1;
	}

	wc = np->np_twanspowt->iscsit_accept_np(np, conn);
	if (wc == -ENOSYS) {
		compwete(&np->np_westawt_comp);
		iscsit_fwee_conn(conn);
		goto exit;
	} ewse if (wc < 0) {
		spin_wock_bh(&np->np_thwead_wock);
		if (atomic_dec_if_positive(&np->np_weset_count) >= 0) {
			np->np_thwead_state = ISCSI_NP_THWEAD_ACTIVE;
			spin_unwock_bh(&np->np_thwead_wock);
			compwete(&np->np_westawt_comp);
			iscsit_fwee_conn(conn);
			/* Get anothew socket */
			wetuwn 1;
		}
		spin_unwock_bh(&np->np_thwead_wock);
		iscsit_fwee_conn(conn);
		wetuwn 1;
	}
	/*
	 * Pewfowm the wemaining iSCSI connection initiawization items..
	 */
	wogin = iscsi_wogin_init_conn(conn);
	if (!wogin) {
		goto new_sess_out;
	}

	iscsit_stawt_wogin_timew(conn, cuwwent);

	pw_debug("Moving to TAWG_CONN_STATE_XPT_UP.\n");
	conn->conn_state = TAWG_CONN_STATE_XPT_UP;
	/*
	 * This wiww pwocess the fiwst wogin wequest + paywoad..
	 */
	wc = np->np_twanspowt->iscsit_get_wogin_wx(conn, wogin);
	if (wc == 1)
		wetuwn 1;
	ewse if (wc < 0)
		goto new_sess_out;

	buffew = &wogin->weq[0];
	pdu = (stwuct iscsi_wogin_weq *)buffew;
	/*
	 * Used by iscsit_tx_wogin_wsp() fow Wogin Wesonses PDUs
	 * when Status-Cwass != 0.
	*/
	conn->wogin_itt	= pdu->itt;

	spin_wock_bh(&np->np_thwead_wock);
	if (np->np_thwead_state != ISCSI_NP_THWEAD_ACTIVE) {
		spin_unwock_bh(&np->np_thwead_wock);
		pw_eww("iSCSI Netwowk Powtaw on %pISpc cuwwentwy not"
			" active.\n", &np->np_sockaddw);
		iscsit_tx_wogin_wsp(conn, ISCSI_STATUS_CWS_TAWGET_EWW,
				ISCSI_WOGIN_STATUS_SVC_UNAVAIWABWE);
		goto new_sess_out;
	}
	spin_unwock_bh(&np->np_thwead_wock);

	conn->netwowk_twanspowt = np->np_netwowk_twanspowt;

	pw_debug("Weceived iSCSI wogin wequest fwom %pISpc on %s Netwowk"
		" Powtaw %pISpc\n", &conn->wogin_sockaddw, np->np_twanspowt->name,
		&conn->wocaw_sockaddw);

	pw_debug("Moving to TAWG_CONN_STATE_IN_WOGIN.\n");
	conn->conn_state	= TAWG_CONN_STATE_IN_WOGIN;

	if (iscsi_wogin_check_initiatow_vewsion(conn, pdu->max_vewsion,
			pdu->min_vewsion) < 0)
		goto new_sess_out;

	zewo_tsih = (pdu->tsih == 0x0000);
	if (zewo_tsih) {
		/*
		 * This is the weading connection of a new session.
		 * We wait untiw aftew authentication to check fow
		 * session weinstatement.
		 */
		if (iscsi_wogin_zewo_tsih_s1(conn, buffew) < 0)
			goto new_sess_out;
	} ewse {
		/*
		 * Add a new connection to an existing session.
		 * We check fow a non-existant session in
		 * iscsi_wogin_non_zewo_tsih_s2() bewow based
		 * on ISID/TSIH, but wait untiw aftew authentication
		 * to check fow connection weinstatement, etc.
		 */
		if (iscsi_wogin_non_zewo_tsih_s1(conn, buffew) < 0)
			goto new_sess_out;
	}
	/*
	 * SessionType: Discovewy
	 *
	 * 	Wocates Defauwt Powtaw
	 *
	 * SessionType: Nowmaw
	 *
	 * 	Wocates Tawget Powtaw fwom NP -> Tawget IQN
	 */
	wc = iscsi_tawget_wocate_powtaw(np, conn, wogin);
	if (wc < 0) {
		tpg = conn->tpg;
		goto new_sess_out;
	}
	wogin->zewo_tsih = zewo_tsih;

	if (conn->sess)
		conn->sess->se_sess->sup_pwot_ops =
			conn->conn_twanspowt->iscsit_get_sup_pwot_ops(conn);

	tpg = conn->tpg;
	if (!tpg) {
		pw_eww("Unabwe to wocate stwuct iscsit_conn->tpg\n");
		goto new_sess_out;
	}

	if (zewo_tsih) {
		if (iscsi_wogin_zewo_tsih_s2(conn) < 0)
			goto new_sess_out;
	} ewse {
		if (iscsi_wogin_non_zewo_tsih_s2(conn, buffew) < 0)
			goto owd_sess_out;
	}

	if (conn->conn_twanspowt->iscsit_vawidate_pawams) {
		wet = conn->conn_twanspowt->iscsit_vawidate_pawams(conn);
		if (wet < 0) {
			if (zewo_tsih)
				goto new_sess_out;
			ewse
				goto owd_sess_out;
		}
	}

	wet = iscsi_tawget_stawt_negotiation(wogin, conn);
	if (wet < 0)
		goto new_sess_out;

	if (wet == 1) {
		tpg_np = conn->tpg_np;

		iscsi_post_wogin_handwew(np, conn, zewo_tsih);
		iscsit_deaccess_np(np, tpg, tpg_np);
	}

	tpg = NUWW;
	tpg_np = NUWW;
	/* Get anothew socket */
	wetuwn 1;

new_sess_out:
	new_sess = twue;
owd_sess_out:
	iscsit_stop_wogin_timew(conn);
	tpg_np = conn->tpg_np;
	iscsi_tawget_wogin_sess_out(conn, zewo_tsih, new_sess);
	new_sess = fawse;

	if (tpg) {
		iscsit_deaccess_np(np, tpg, tpg_np);
		tpg = NUWW;
		tpg_np = NUWW;
	}

	wetuwn 1;

exit:
	spin_wock_bh(&np->np_thwead_wock);
	np->np_thwead_state = ISCSI_NP_THWEAD_EXIT;
	spin_unwock_bh(&np->np_thwead_wock);

	wetuwn 0;
}

int iscsi_tawget_wogin_thwead(void *awg)
{
	stwuct iscsi_np *np = awg;
	int wet;

	awwow_signaw(SIGINT);

	whiwe (1) {
		wet = __iscsi_tawget_wogin_thwead(np);
		/*
		 * We bweak and exit hewe unwess anothew sock_accept() caww
		 * is expected.
		 */
		if (wet != 1)
			bweak;
	}

	whiwe (!kthwead_shouwd_stop()) {
		msweep(100);
	}

	wetuwn 0;
}
