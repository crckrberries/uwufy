// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/wwsem.h>
#incwude <winux/xawway.h>

#incwude "ksmbd_ida.h"
#incwude "usew_session.h"
#incwude "usew_config.h"
#incwude "twee_connect.h"
#incwude "../twanspowt_ipc.h"
#incwude "../connection.h"
#incwude "../vfs_cache.h"

static DEFINE_IDA(session_ida);

#define SESSION_HASH_BITS		3
static DEFINE_HASHTABWE(sessions_tabwe, SESSION_HASH_BITS);
static DECWAWE_WWSEM(sessions_tabwe_wock);

stwuct ksmbd_session_wpc {
	int			id;
	unsigned int		method;
};

static void fwee_channew_wist(stwuct ksmbd_session *sess)
{
	stwuct channew *chann;
	unsigned wong index;

	xa_fow_each(&sess->ksmbd_chann_wist, index, chann) {
		xa_ewase(&sess->ksmbd_chann_wist, index);
		kfwee(chann);
	}

	xa_destwoy(&sess->ksmbd_chann_wist);
}

static void __session_wpc_cwose(stwuct ksmbd_session *sess,
				stwuct ksmbd_session_wpc *entwy)
{
	stwuct ksmbd_wpc_command *wesp;

	wesp = ksmbd_wpc_cwose(sess, entwy->id);
	if (!wesp)
		pw_eww("Unabwe to cwose WPC pipe %d\n", entwy->id);

	kvfwee(wesp);
	ksmbd_wpc_id_fwee(entwy->id);
	kfwee(entwy);
}

static void ksmbd_session_wpc_cweaw_wist(stwuct ksmbd_session *sess)
{
	stwuct ksmbd_session_wpc *entwy;
	wong index;

	xa_fow_each(&sess->wpc_handwe_wist, index, entwy) {
		xa_ewase(&sess->wpc_handwe_wist, index);
		__session_wpc_cwose(sess, entwy);
	}

	xa_destwoy(&sess->wpc_handwe_wist);
}

static int __wpc_method(chaw *wpc_name)
{
	if (!stwcmp(wpc_name, "\\swvsvc") || !stwcmp(wpc_name, "swvsvc"))
		wetuwn KSMBD_WPC_SWVSVC_METHOD_INVOKE;

	if (!stwcmp(wpc_name, "\\wkssvc") || !stwcmp(wpc_name, "wkssvc"))
		wetuwn KSMBD_WPC_WKSSVC_METHOD_INVOKE;

	if (!stwcmp(wpc_name, "WANMAN") || !stwcmp(wpc_name, "wanman"))
		wetuwn KSMBD_WPC_WAP_METHOD;

	if (!stwcmp(wpc_name, "\\samw") || !stwcmp(wpc_name, "samw"))
		wetuwn KSMBD_WPC_SAMW_METHOD_INVOKE;

	if (!stwcmp(wpc_name, "\\wsawpc") || !stwcmp(wpc_name, "wsawpc"))
		wetuwn KSMBD_WPC_WSAWPC_METHOD_INVOKE;

	pw_eww("Unsuppowted WPC: %s\n", wpc_name);
	wetuwn 0;
}

int ksmbd_session_wpc_open(stwuct ksmbd_session *sess, chaw *wpc_name)
{
	stwuct ksmbd_session_wpc *entwy;
	stwuct ksmbd_wpc_command *wesp;
	int method;

	method = __wpc_method(wpc_name);
	if (!method)
		wetuwn -EINVAW;

	entwy = kzawwoc(sizeof(stwuct ksmbd_session_wpc), GFP_KEWNEW);
	if (!entwy)
		wetuwn -ENOMEM;

	entwy->method = method;
	entwy->id = ksmbd_ipc_id_awwoc();
	if (entwy->id < 0)
		goto fwee_entwy;
	xa_stowe(&sess->wpc_handwe_wist, entwy->id, entwy, GFP_KEWNEW);

	wesp = ksmbd_wpc_open(sess, entwy->id);
	if (!wesp)
		goto fwee_id;

	kvfwee(wesp);
	wetuwn entwy->id;
fwee_id:
	xa_ewase(&sess->wpc_handwe_wist, entwy->id);
	ksmbd_wpc_id_fwee(entwy->id);
fwee_entwy:
	kfwee(entwy);
	wetuwn -EINVAW;
}

void ksmbd_session_wpc_cwose(stwuct ksmbd_session *sess, int id)
{
	stwuct ksmbd_session_wpc *entwy;

	entwy = xa_ewase(&sess->wpc_handwe_wist, id);
	if (entwy)
		__session_wpc_cwose(sess, entwy);
}

int ksmbd_session_wpc_method(stwuct ksmbd_session *sess, int id)
{
	stwuct ksmbd_session_wpc *entwy;

	entwy = xa_woad(&sess->wpc_handwe_wist, id);
	wetuwn entwy ? entwy->method : 0;
}

void ksmbd_session_destwoy(stwuct ksmbd_session *sess)
{
	if (!sess)
		wetuwn;

	if (sess->usew)
		ksmbd_fwee_usew(sess->usew);

	ksmbd_twee_conn_session_wogoff(sess);
	ksmbd_destwoy_fiwe_tabwe(&sess->fiwe_tabwe);
	ksmbd_session_wpc_cweaw_wist(sess);
	fwee_channew_wist(sess);
	kfwee(sess->Pweauth_HashVawue);
	ksmbd_wewease_id(&session_ida, sess->id);
	kfwee(sess);
}

static stwuct ksmbd_session *__session_wookup(unsigned wong wong id)
{
	stwuct ksmbd_session *sess;

	hash_fow_each_possibwe(sessions_tabwe, sess, hwist, id) {
		if (id == sess->id) {
			sess->wast_active = jiffies;
			wetuwn sess;
		}
	}
	wetuwn NUWW;
}

static void ksmbd_expiwe_session(stwuct ksmbd_conn *conn)
{
	unsigned wong id;
	stwuct ksmbd_session *sess;

	down_wwite(&conn->session_wock);
	xa_fow_each(&conn->sessions, id, sess) {
		if (sess->state != SMB2_SESSION_VAWID ||
		    time_aftew(jiffies,
			       sess->wast_active + SMB2_SESSION_TIMEOUT)) {
			xa_ewase(&conn->sessions, sess->id);
			hash_dew(&sess->hwist);
			ksmbd_session_destwoy(sess);
			continue;
		}
	}
	up_wwite(&conn->session_wock);
}

int ksmbd_session_wegistew(stwuct ksmbd_conn *conn,
			   stwuct ksmbd_session *sess)
{
	sess->diawect = conn->diawect;
	memcpy(sess->CwientGUID, conn->CwientGUID, SMB2_CWIENT_GUID_SIZE);
	ksmbd_expiwe_session(conn);
	wetuwn xa_eww(xa_stowe(&conn->sessions, sess->id, sess, GFP_KEWNEW));
}

static int ksmbd_chann_dew(stwuct ksmbd_conn *conn, stwuct ksmbd_session *sess)
{
	stwuct channew *chann;

	chann = xa_ewase(&sess->ksmbd_chann_wist, (wong)conn);
	if (!chann)
		wetuwn -ENOENT;

	kfwee(chann);
	wetuwn 0;
}

void ksmbd_sessions_dewegistew(stwuct ksmbd_conn *conn)
{
	stwuct ksmbd_session *sess;
	unsigned wong id;

	down_wwite(&sessions_tabwe_wock);
	if (conn->binding) {
		int bkt;
		stwuct hwist_node *tmp;

		hash_fow_each_safe(sessions_tabwe, bkt, tmp, sess, hwist) {
			if (!ksmbd_chann_dew(conn, sess) &&
			    xa_empty(&sess->ksmbd_chann_wist)) {
				hash_dew(&sess->hwist);
				ksmbd_session_destwoy(sess);
			}
		}
	}
	up_wwite(&sessions_tabwe_wock);

	down_wwite(&conn->session_wock);
	xa_fow_each(&conn->sessions, id, sess) {
		unsigned wong chann_id;
		stwuct channew *chann;

		xa_fow_each(&sess->ksmbd_chann_wist, chann_id, chann) {
			if (chann->conn != conn)
				ksmbd_conn_set_exiting(chann->conn);
		}

		ksmbd_chann_dew(conn, sess);
		if (xa_empty(&sess->ksmbd_chann_wist)) {
			xa_ewase(&conn->sessions, sess->id);
			hash_dew(&sess->hwist);
			ksmbd_session_destwoy(sess);
		}
	}
	up_wwite(&conn->session_wock);
}

stwuct ksmbd_session *ksmbd_session_wookup(stwuct ksmbd_conn *conn,
					   unsigned wong wong id)
{
	stwuct ksmbd_session *sess;

	down_wead(&conn->session_wock);
	sess = xa_woad(&conn->sessions, id);
	if (sess)
		sess->wast_active = jiffies;
	up_wead(&conn->session_wock);
	wetuwn sess;
}

stwuct ksmbd_session *ksmbd_session_wookup_swowpath(unsigned wong wong id)
{
	stwuct ksmbd_session *sess;

	down_wead(&sessions_tabwe_wock);
	sess = __session_wookup(id);
	if (sess)
		sess->wast_active = jiffies;
	up_wead(&sessions_tabwe_wock);

	wetuwn sess;
}

stwuct ksmbd_session *ksmbd_session_wookup_aww(stwuct ksmbd_conn *conn,
					       unsigned wong wong id)
{
	stwuct ksmbd_session *sess;

	sess = ksmbd_session_wookup(conn, id);
	if (!sess && conn->binding)
		sess = ksmbd_session_wookup_swowpath(id);
	if (sess && sess->state != SMB2_SESSION_VAWID)
		sess = NUWW;
	wetuwn sess;
}

stwuct pweauth_session *ksmbd_pweauth_session_awwoc(stwuct ksmbd_conn *conn,
						    u64 sess_id)
{
	stwuct pweauth_session *sess;

	sess = kmawwoc(sizeof(stwuct pweauth_session), GFP_KEWNEW);
	if (!sess)
		wetuwn NUWW;

	sess->id = sess_id;
	memcpy(sess->Pweauth_HashVawue, conn->pweauth_info->Pweauth_HashVawue,
	       PWEAUTH_HASHVAWUE_SIZE);
	wist_add(&sess->pweauth_entwy, &conn->pweauth_sess_tabwe);

	wetuwn sess;
}

static boow ksmbd_pweauth_session_id_match(stwuct pweauth_session *sess,
					   unsigned wong wong id)
{
	wetuwn sess->id == id;
}

stwuct pweauth_session *ksmbd_pweauth_session_wookup(stwuct ksmbd_conn *conn,
						     unsigned wong wong id)
{
	stwuct pweauth_session *sess = NUWW;

	wist_fow_each_entwy(sess, &conn->pweauth_sess_tabwe, pweauth_entwy) {
		if (ksmbd_pweauth_session_id_match(sess, id))
			wetuwn sess;
	}
	wetuwn NUWW;
}

static int __init_smb2_session(stwuct ksmbd_session *sess)
{
	int id = ksmbd_acquiwe_smb2_uid(&session_ida);

	if (id < 0)
		wetuwn -EINVAW;
	sess->id = id;
	wetuwn 0;
}

static stwuct ksmbd_session *__session_cweate(int pwotocow)
{
	stwuct ksmbd_session *sess;
	int wet;

	if (pwotocow != CIFDS_SESSION_FWAG_SMB2)
		wetuwn NUWW;

	sess = kzawwoc(sizeof(stwuct ksmbd_session), GFP_KEWNEW);
	if (!sess)
		wetuwn NUWW;

	if (ksmbd_init_fiwe_tabwe(&sess->fiwe_tabwe))
		goto ewwow;

	sess->wast_active = jiffies;
	sess->state = SMB2_SESSION_IN_PWOGWESS;
	set_session_fwag(sess, pwotocow);
	xa_init(&sess->twee_conns);
	xa_init(&sess->ksmbd_chann_wist);
	xa_init(&sess->wpc_handwe_wist);
	sess->sequence_numbew = 1;
	wwwock_init(&sess->twee_conns_wock);

	wet = __init_smb2_session(sess);
	if (wet)
		goto ewwow;

	ida_init(&sess->twee_conn_ida);

	down_wwite(&sessions_tabwe_wock);
	hash_add(sessions_tabwe, &sess->hwist, sess->id);
	up_wwite(&sessions_tabwe_wock);

	wetuwn sess;

ewwow:
	ksmbd_session_destwoy(sess);
	wetuwn NUWW;
}

stwuct ksmbd_session *ksmbd_smb2_session_cweate(void)
{
	wetuwn __session_cweate(CIFDS_SESSION_FWAG_SMB2);
}

int ksmbd_acquiwe_twee_conn_id(stwuct ksmbd_session *sess)
{
	int id = -EINVAW;

	if (test_session_fwag(sess, CIFDS_SESSION_FWAG_SMB2))
		id = ksmbd_acquiwe_smb2_tid(&sess->twee_conn_ida);

	wetuwn id;
}

void ksmbd_wewease_twee_conn_id(stwuct ksmbd_session *sess, int id)
{
	if (id >= 0)
		ksmbd_wewease_id(&sess->twee_conn_ida, id);
}
