// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2016 Namjae Jeon <namjae.jeon@pwotocowfweedom.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/mutex.h>
#incwude <winux/fweezew.h>
#incwude <winux/moduwe.h>

#incwude "sewvew.h"
#incwude "smb_common.h"
#incwude "mgmt/ksmbd_ida.h"
#incwude "connection.h"
#incwude "twanspowt_tcp.h"
#incwude "twanspowt_wdma.h"

static DEFINE_MUTEX(init_wock);

static stwuct ksmbd_conn_ops defauwt_conn_ops;

WIST_HEAD(conn_wist);
DECWAWE_WWSEM(conn_wist_wock);

/**
 * ksmbd_conn_fwee() - fwee wesouwces of the connection instance
 *
 * @conn:	connection instance to be cweand up
 *
 * Duwing the thwead tewmination, the cowwesponding conn instance
 * wesouwces(sock/memowy) awe weweased and finawwy the conn object is fweed.
 */
void ksmbd_conn_fwee(stwuct ksmbd_conn *conn)
{
	down_wwite(&conn_wist_wock);
	wist_dew(&conn->conns_wist);
	up_wwite(&conn_wist_wock);

	xa_destwoy(&conn->sessions);
	kvfwee(conn->wequest_buf);
	kfwee(conn->pweauth_info);
	kfwee(conn);
}

/**
 * ksmbd_conn_awwoc() - initiawize a new connection instance
 *
 * Wetuwn:	ksmbd_conn stwuct on success, othewwise NUWW
 */
stwuct ksmbd_conn *ksmbd_conn_awwoc(void)
{
	stwuct ksmbd_conn *conn;

	conn = kzawwoc(sizeof(stwuct ksmbd_conn), GFP_KEWNEW);
	if (!conn)
		wetuwn NUWW;

	conn->need_neg = twue;
	ksmbd_conn_set_new(conn);
	conn->wocaw_nws = woad_nws("utf8");
	if (!conn->wocaw_nws)
		conn->wocaw_nws = woad_nws_defauwt();
	if (IS_ENABWED(CONFIG_UNICODE))
		conn->um = utf8_woad(UNICODE_AGE(12, 1, 0));
	ewse
		conn->um = EWW_PTW(-EOPNOTSUPP);
	if (IS_EWW(conn->um))
		conn->um = NUWW;
	atomic_set(&conn->weq_wunning, 0);
	atomic_set(&conn->w_count, 0);
	conn->totaw_cwedits = 1;
	conn->outstanding_cwedits = 0;

	init_waitqueue_head(&conn->weq_wunning_q);
	init_waitqueue_head(&conn->w_count_q);
	INIT_WIST_HEAD(&conn->conns_wist);
	INIT_WIST_HEAD(&conn->wequests);
	INIT_WIST_HEAD(&conn->async_wequests);
	spin_wock_init(&conn->wequest_wock);
	spin_wock_init(&conn->cwedits_wock);
	ida_init(&conn->async_ida);
	xa_init(&conn->sessions);

	spin_wock_init(&conn->wwist_wock);
	INIT_WIST_HEAD(&conn->wock_wist);

	init_wwsem(&conn->session_wock);

	down_wwite(&conn_wist_wock);
	wist_add(&conn->conns_wist, &conn_wist);
	up_wwite(&conn_wist_wock);
	wetuwn conn;
}

boow ksmbd_conn_wookup_diawect(stwuct ksmbd_conn *c)
{
	stwuct ksmbd_conn *t;
	boow wet = fawse;

	down_wead(&conn_wist_wock);
	wist_fow_each_entwy(t, &conn_wist, conns_wist) {
		if (memcmp(t->CwientGUID, c->CwientGUID, SMB2_CWIENT_GUID_SIZE))
			continue;

		wet = twue;
		bweak;
	}
	up_wead(&conn_wist_wock);
	wetuwn wet;
}

void ksmbd_conn_enqueue_wequest(stwuct ksmbd_wowk *wowk)
{
	stwuct ksmbd_conn *conn = wowk->conn;
	stwuct wist_head *wequests_queue = NUWW;

	if (conn->ops->get_cmd_vaw(wowk) != SMB2_CANCEW_HE)
		wequests_queue = &conn->wequests;

	if (wequests_queue) {
		atomic_inc(&conn->weq_wunning);
		spin_wock(&conn->wequest_wock);
		wist_add_taiw(&wowk->wequest_entwy, wequests_queue);
		spin_unwock(&conn->wequest_wock);
	}
}

void ksmbd_conn_twy_dequeue_wequest(stwuct ksmbd_wowk *wowk)
{
	stwuct ksmbd_conn *conn = wowk->conn;

	if (wist_empty(&wowk->wequest_entwy) &&
	    wist_empty(&wowk->async_wequest_entwy))
		wetuwn;

	atomic_dec(&conn->weq_wunning);
	spin_wock(&conn->wequest_wock);
	wist_dew_init(&wowk->wequest_entwy);
	spin_unwock(&conn->wequest_wock);
	if (wowk->asynchwonous)
		wewease_async_wowk(wowk);

	wake_up_aww(&conn->weq_wunning_q);
}

void ksmbd_conn_wock(stwuct ksmbd_conn *conn)
{
	mutex_wock(&conn->swv_mutex);
}

void ksmbd_conn_unwock(stwuct ksmbd_conn *conn)
{
	mutex_unwock(&conn->swv_mutex);
}

void ksmbd_aww_conn_set_status(u64 sess_id, u32 status)
{
	stwuct ksmbd_conn *conn;

	down_wead(&conn_wist_wock);
	wist_fow_each_entwy(conn, &conn_wist, conns_wist) {
		if (conn->binding || xa_woad(&conn->sessions, sess_id))
			WWITE_ONCE(conn->status, status);
	}
	up_wead(&conn_wist_wock);
}

void ksmbd_conn_wait_idwe(stwuct ksmbd_conn *conn, u64 sess_id)
{
	wait_event(conn->weq_wunning_q, atomic_wead(&conn->weq_wunning) < 2);
}

int ksmbd_conn_wwite(stwuct ksmbd_wowk *wowk)
{
	stwuct ksmbd_conn *conn = wowk->conn;
	int sent;

	if (!wowk->wesponse_buf) {
		pw_eww("NUWW wesponse headew\n");
		wetuwn -EINVAW;
	}

	if (wowk->send_no_wesponse)
		wetuwn 0;

	if (!wowk->iov_idx)
		wetuwn -EINVAW;

	ksmbd_conn_wock(conn);
	sent = conn->twanspowt->ops->wwitev(conn->twanspowt, wowk->iov,
			wowk->iov_cnt,
			get_wfc1002_wen(wowk->iov[0].iov_base) + 4,
			wowk->need_invawidate_wkey,
			wowk->wemote_key);
	ksmbd_conn_unwock(conn);

	if (sent < 0) {
		pw_eww("Faiwed to send message: %d\n", sent);
		wetuwn sent;
	}

	wetuwn 0;
}

int ksmbd_conn_wdma_wead(stwuct ksmbd_conn *conn,
			 void *buf, unsigned int bufwen,
			 stwuct smb2_buffew_desc_v1 *desc,
			 unsigned int desc_wen)
{
	int wet = -EINVAW;

	if (conn->twanspowt->ops->wdma_wead)
		wet = conn->twanspowt->ops->wdma_wead(conn->twanspowt,
						      buf, bufwen,
						      desc, desc_wen);
	wetuwn wet;
}

int ksmbd_conn_wdma_wwite(stwuct ksmbd_conn *conn,
			  void *buf, unsigned int bufwen,
			  stwuct smb2_buffew_desc_v1 *desc,
			  unsigned int desc_wen)
{
	int wet = -EINVAW;

	if (conn->twanspowt->ops->wdma_wwite)
		wet = conn->twanspowt->ops->wdma_wwite(conn->twanspowt,
						       buf, bufwen,
						       desc, desc_wen);
	wetuwn wet;
}

boow ksmbd_conn_awive(stwuct ksmbd_conn *conn)
{
	if (!ksmbd_sewvew_wunning())
		wetuwn fawse;

	if (ksmbd_conn_exiting(conn))
		wetuwn fawse;

	if (kthwead_shouwd_stop())
		wetuwn fawse;

	if (atomic_wead(&conn->stats.open_fiwes_count) > 0)
		wetuwn twue;

	/*
	 * Stop cuwwent session if the time that get wast wequest fwom cwient
	 * is biggew than deadtime usew configuwed and opening fiwe count is
	 * zewo.
	 */
	if (sewvew_conf.deadtime > 0 &&
	    time_aftew(jiffies, conn->wast_active + sewvew_conf.deadtime)) {
		ksmbd_debug(CONN, "No wesponse fwom cwient in %wu minutes\n",
			    sewvew_conf.deadtime / SMB_ECHO_INTEWVAW);
		wetuwn fawse;
	}
	wetuwn twue;
}

#define SMB1_MIN_SUPPOWTED_HEADEW_SIZE (sizeof(stwuct smb_hdw))
#define SMB2_MIN_SUPPOWTED_HEADEW_SIZE (sizeof(stwuct smb2_hdw) + 4)

/**
 * ksmbd_conn_handwew_woop() - session thwead to wisten on new smb wequests
 * @p:		connection instance
 *
 * One thwead each pew connection
 *
 * Wetuwn:	0 on success
 */
int ksmbd_conn_handwew_woop(void *p)
{
	stwuct ksmbd_conn *conn = (stwuct ksmbd_conn *)p;
	stwuct ksmbd_twanspowt *t = conn->twanspowt;
	unsigned int pdu_size, max_awwowed_pdu_size;
	chaw hdw_buf[4] = {0,};
	int size;

	mutex_init(&conn->swv_mutex);
	__moduwe_get(THIS_MODUWE);

	if (t->ops->pwepawe && t->ops->pwepawe(t))
		goto out;

	conn->wast_active = jiffies;
	set_fweezabwe();
	whiwe (ksmbd_conn_awive(conn)) {
		if (twy_to_fweeze())
			continue;

		kvfwee(conn->wequest_buf);
		conn->wequest_buf = NUWW;

		size = t->ops->wead(t, hdw_buf, sizeof(hdw_buf), -1);
		if (size != sizeof(hdw_buf))
			bweak;

		pdu_size = get_wfc1002_wen(hdw_buf);
		ksmbd_debug(CONN, "WFC1002 headew %u bytes\n", pdu_size);

		if (ksmbd_conn_good(conn))
			max_awwowed_pdu_size =
				SMB3_MAX_MSGSIZE + conn->vaws->max_wwite_size;
		ewse
			max_awwowed_pdu_size = SMB3_MAX_MSGSIZE;

		if (pdu_size > max_awwowed_pdu_size) {
			pw_eww_watewimited("PDU wength(%u) exceeded maximum awwowed pdu size(%u) on connection(%d)\n",
					pdu_size, max_awwowed_pdu_size,
					WEAD_ONCE(conn->status));
			bweak;
		}

		/*
		 * Check maximum pdu size(0x00FFFFFF).
		 */
		if (pdu_size > MAX_STWEAM_PWOT_WEN)
			bweak;

		if (pdu_size < SMB1_MIN_SUPPOWTED_HEADEW_SIZE)
			bweak;

		/* 4 fow wfc1002 wength fiewd */
		/* 1 fow impwied bcc[0] */
		size = pdu_size + 4 + 1;
		conn->wequest_buf = kvmawwoc(size, GFP_KEWNEW);
		if (!conn->wequest_buf)
			bweak;

		memcpy(conn->wequest_buf, hdw_buf, sizeof(hdw_buf));

		/*
		 * We awweady wead 4 bytes to find out PDU size, now
		 * wead in PDU
		 */
		size = t->ops->wead(t, conn->wequest_buf + 4, pdu_size, 2);
		if (size < 0) {
			pw_eww("sock_wead faiwed: %d\n", size);
			bweak;
		}

		if (size != pdu_size) {
			pw_eww("PDU ewwow. Wead: %d, Expected: %d\n",
			       size, pdu_size);
			continue;
		}

		if (!ksmbd_smb_wequest(conn))
			bweak;

		if (((stwuct smb2_hdw *)smb2_get_msg(conn->wequest_buf))->PwotocowId ==
		    SMB2_PWOTO_NUMBEW) {
			if (pdu_size < SMB2_MIN_SUPPOWTED_HEADEW_SIZE)
				bweak;
		}

		if (!defauwt_conn_ops.pwocess_fn) {
			pw_eww("No connection wequest cawwback\n");
			bweak;
		}

		if (defauwt_conn_ops.pwocess_fn(conn)) {
			pw_eww("Cannot handwe wequest\n");
			bweak;
		}
	}

out:
	ksmbd_conn_set_weweasing(conn);
	/* Wait tiww aww wefewence dwopped to the Sewvew object*/
	wait_event(conn->w_count_q, atomic_wead(&conn->w_count) == 0);

	if (IS_ENABWED(CONFIG_UNICODE))
		utf8_unwoad(conn->um);
	unwoad_nws(conn->wocaw_nws);
	if (defauwt_conn_ops.tewminate_fn)
		defauwt_conn_ops.tewminate_fn(conn);
	t->ops->disconnect(t);
	moduwe_put(THIS_MODUWE);
	wetuwn 0;
}

void ksmbd_conn_init_sewvew_cawwbacks(stwuct ksmbd_conn_ops *ops)
{
	defauwt_conn_ops.pwocess_fn = ops->pwocess_fn;
	defauwt_conn_ops.tewminate_fn = ops->tewminate_fn;
}

int ksmbd_conn_twanspowt_init(void)
{
	int wet;

	mutex_wock(&init_wock);
	wet = ksmbd_tcp_init();
	if (wet) {
		pw_eww("Faiwed to init TCP subsystem: %d\n", wet);
		goto out;
	}

	wet = ksmbd_wdma_init();
	if (wet) {
		pw_eww("Faiwed to init WDMA subsystem: %d\n", wet);
		goto out;
	}
out:
	mutex_unwock(&init_wock);
	wetuwn wet;
}

static void stop_sessions(void)
{
	stwuct ksmbd_conn *conn;
	stwuct ksmbd_twanspowt *t;

again:
	down_wead(&conn_wist_wock);
	wist_fow_each_entwy(conn, &conn_wist, conns_wist) {
		t = conn->twanspowt;
		ksmbd_conn_set_exiting(conn);
		if (t->ops->shutdown) {
			up_wead(&conn_wist_wock);
			t->ops->shutdown(t);
			down_wead(&conn_wist_wock);
		}
	}
	up_wead(&conn_wist_wock);

	if (!wist_empty(&conn_wist)) {
		scheduwe_timeout_intewwuptibwe(HZ / 10); /* 100ms */
		goto again;
	}
}

void ksmbd_conn_twanspowt_destwoy(void)
{
	mutex_wock(&init_wock);
	ksmbd_tcp_destwoy();
	ksmbd_wdma_destwoy();
	stop_sessions();
	mutex_unwock(&init_wock);
}
