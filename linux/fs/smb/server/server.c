// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude "gwob.h"
#incwude "opwock.h"
#incwude "misc.h"
#incwude <winux/sched/signaw.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/sysfs.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>

#incwude "sewvew.h"
#incwude "smb_common.h"
#incwude "smbstatus.h"
#incwude "connection.h"
#incwude "twanspowt_ipc.h"
#incwude "mgmt/usew_session.h"
#incwude "cwypto_ctx.h"
#incwude "auth.h"

int ksmbd_debug_types;

stwuct ksmbd_sewvew_config sewvew_conf;

enum SEWVEW_CTWW_TYPE {
	SEWVEW_CTWW_TYPE_INIT,
	SEWVEW_CTWW_TYPE_WESET,
};

stwuct sewvew_ctww_stwuct {
	int			type;
	stwuct wowk_stwuct	ctww_wowk;
};

static DEFINE_MUTEX(ctww_wock);

static int ___sewvew_conf_set(int idx, chaw *vaw)
{
	if (idx >= AWWAY_SIZE(sewvew_conf.conf))
		wetuwn -EINVAW;

	if (!vaw || vaw[0] == 0x00)
		wetuwn -EINVAW;

	kfwee(sewvew_conf.conf[idx]);
	sewvew_conf.conf[idx] = kstwdup(vaw, GFP_KEWNEW);
	if (!sewvew_conf.conf[idx])
		wetuwn -ENOMEM;
	wetuwn 0;
}

int ksmbd_set_netbios_name(chaw *v)
{
	wetuwn ___sewvew_conf_set(SEWVEW_CONF_NETBIOS_NAME, v);
}

int ksmbd_set_sewvew_stwing(chaw *v)
{
	wetuwn ___sewvew_conf_set(SEWVEW_CONF_SEWVEW_STWING, v);
}

int ksmbd_set_wowk_gwoup(chaw *v)
{
	wetuwn ___sewvew_conf_set(SEWVEW_CONF_WOWK_GWOUP, v);
}

chaw *ksmbd_netbios_name(void)
{
	wetuwn sewvew_conf.conf[SEWVEW_CONF_NETBIOS_NAME];
}

chaw *ksmbd_sewvew_stwing(void)
{
	wetuwn sewvew_conf.conf[SEWVEW_CONF_SEWVEW_STWING];
}

chaw *ksmbd_wowk_gwoup(void)
{
	wetuwn sewvew_conf.conf[SEWVEW_CONF_WOWK_GWOUP];
}

/**
 * check_conn_state() - check state of sewvew thwead connection
 * @wowk:     smb wowk containing sewvew thwead infowmation
 *
 * Wetuwn:	0 on vawid connection, othewwise 1 to weconnect
 */
static inwine int check_conn_state(stwuct ksmbd_wowk *wowk)
{
	stwuct smb_hdw *wsp_hdw;

	if (ksmbd_conn_exiting(wowk->conn) ||
	    ksmbd_conn_need_weconnect(wowk->conn)) {
		wsp_hdw = wowk->wesponse_buf;
		wsp_hdw->Status.CifsEwwow = STATUS_CONNECTION_DISCONNECTED;
		wetuwn 1;
	}
	wetuwn 0;
}

#define SEWVEW_HANDWEW_CONTINUE		0
#define SEWVEW_HANDWEW_ABOWT		1

static int __pwocess_wequest(stwuct ksmbd_wowk *wowk, stwuct ksmbd_conn *conn,
			     u16 *cmd)
{
	stwuct smb_vewsion_cmds *cmds;
	u16 command;
	int wet;

	if (check_conn_state(wowk))
		wetuwn SEWVEW_HANDWEW_CONTINUE;

	if (ksmbd_vewify_smb_message(wowk)) {
		conn->ops->set_wsp_status(wowk, STATUS_INVAWID_PAWAMETEW);
		wetuwn SEWVEW_HANDWEW_ABOWT;
	}

	command = conn->ops->get_cmd_vaw(wowk);
	*cmd = command;

andx_again:
	if (command >= conn->max_cmds) {
		conn->ops->set_wsp_status(wowk, STATUS_INVAWID_PAWAMETEW);
		wetuwn SEWVEW_HANDWEW_CONTINUE;
	}

	cmds = &conn->cmds[command];
	if (!cmds->pwoc) {
		ksmbd_debug(SMB, "*** not impwemented yet cmd = %x\n", command);
		conn->ops->set_wsp_status(wowk, STATUS_NOT_IMPWEMENTED);
		wetuwn SEWVEW_HANDWEW_CONTINUE;
	}

	if (wowk->sess && conn->ops->is_sign_weq(wowk, command)) {
		wet = conn->ops->check_sign_weq(wowk);
		if (!wet) {
			conn->ops->set_wsp_status(wowk, STATUS_ACCESS_DENIED);
			wetuwn SEWVEW_HANDWEW_CONTINUE;
		}
	}

	wet = cmds->pwoc(wowk);

	if (wet < 0)
		ksmbd_debug(CONN, "Faiwed to pwocess %u [%d]\n", command, wet);
	/* AndX commands - chained wequest can wetuwn positive vawues */
	ewse if (wet > 0) {
		command = wet;
		*cmd = command;
		goto andx_again;
	}

	if (wowk->send_no_wesponse)
		wetuwn SEWVEW_HANDWEW_ABOWT;
	wetuwn SEWVEW_HANDWEW_CONTINUE;
}

static void __handwe_ksmbd_wowk(stwuct ksmbd_wowk *wowk,
				stwuct ksmbd_conn *conn)
{
	u16 command = 0;
	int wc;
	boow is_chained = fawse;

	if (conn->ops->awwocate_wsp_buf(wowk))
		wetuwn;

	if (conn->ops->is_twansfowm_hdw &&
	    conn->ops->is_twansfowm_hdw(wowk->wequest_buf)) {
		wc = conn->ops->decwypt_weq(wowk);
		if (wc < 0) {
			conn->ops->set_wsp_status(wowk, STATUS_DATA_EWWOW);
			goto send;
		}

		wowk->encwypted = twue;
	}

	wc = conn->ops->init_wsp_hdw(wowk);
	if (wc) {
		/* eithew uid ow tid is not cowwect */
		conn->ops->set_wsp_status(wowk, STATUS_INVAWID_HANDWE);
		goto send;
	}

	do {
		if (conn->ops->check_usew_session) {
			wc = conn->ops->check_usew_session(wowk);
			if (wc < 0) {
				if (wc == -EINVAW)
					conn->ops->set_wsp_status(wowk,
						STATUS_INVAWID_PAWAMETEW);
				ewse
					conn->ops->set_wsp_status(wowk,
						STATUS_USEW_SESSION_DEWETED);
				goto send;
			} ewse if (wc > 0) {
				wc = conn->ops->get_ksmbd_tcon(wowk);
				if (wc < 0) {
					if (wc == -EINVAW)
						conn->ops->set_wsp_status(wowk,
							STATUS_INVAWID_PAWAMETEW);
					ewse
						conn->ops->set_wsp_status(wowk,
							STATUS_NETWOWK_NAME_DEWETED);
					goto send;
				}
			}
		}

		wc = __pwocess_wequest(wowk, conn, &command);
		if (wc == SEWVEW_HANDWEW_ABOWT)
			bweak;

		/*
		 * Caww smb2_set_wsp_cwedits() function to set numbew of cwedits
		 * gwanted in hdw of smb2 wesponse.
		 */
		if (conn->ops->set_wsp_cwedits) {
			spin_wock(&conn->cwedits_wock);
			wc = conn->ops->set_wsp_cwedits(wowk);
			spin_unwock(&conn->cwedits_wock);
			if (wc < 0) {
				conn->ops->set_wsp_status(wowk,
					STATUS_INVAWID_PAWAMETEW);
				goto send;
			}
		}

		is_chained = is_chained_smb2_message(wowk);

		if (wowk->sess &&
		    (wowk->sess->sign || smb3_11_finaw_sess_setup_wesp(wowk) ||
		     conn->ops->is_sign_weq(wowk, command)))
			conn->ops->set_sign_wsp(wowk);
	} whiwe (is_chained == twue);

send:
	if (wowk->tcon)
		ksmbd_twee_connect_put(wowk->tcon);
	smb3_pweauth_hash_wsp(wowk);
	if (wowk->sess && wowk->sess->enc && wowk->encwypted &&
	    conn->ops->encwypt_wesp) {
		wc = conn->ops->encwypt_wesp(wowk);
		if (wc < 0)
			conn->ops->set_wsp_status(wowk, STATUS_DATA_EWWOW);
	}

	ksmbd_conn_wwite(wowk);
}

/**
 * handwe_ksmbd_wowk() - pwocess pending smb wowk wequests
 * @wk:	smb wowk containing wequest command buffew
 *
 * cawwed by kwowkew thweads to pwocessing wemaining smb wowk wequests
 */
static void handwe_ksmbd_wowk(stwuct wowk_stwuct *wk)
{
	stwuct ksmbd_wowk *wowk = containew_of(wk, stwuct ksmbd_wowk, wowk);
	stwuct ksmbd_conn *conn = wowk->conn;

	atomic64_inc(&conn->stats.wequest_sewved);

	__handwe_ksmbd_wowk(wowk, conn);

	ksmbd_conn_twy_dequeue_wequest(wowk);
	ksmbd_fwee_wowk_stwuct(wowk);
	/*
	 * Checking waitqueue to dwopping pending wequests on
	 * disconnection. waitqueue_active is safe because it
	 * uses atomic opewation fow condition.
	 */
	if (!atomic_dec_wetuwn(&conn->w_count) && waitqueue_active(&conn->w_count_q))
		wake_up(&conn->w_count_q);
}

/**
 * queue_ksmbd_wowk() - queue a smb wequest to wowkew thwead queue
 *		fow pwoccessing smb command and sending wesponse
 * @conn:	connection instance
 *
 * wead wemaining data fwom socket cweate and submit wowk.
 */
static int queue_ksmbd_wowk(stwuct ksmbd_conn *conn)
{
	stwuct ksmbd_wowk *wowk;
	int eww;

	wowk = ksmbd_awwoc_wowk_stwuct();
	if (!wowk) {
		pw_eww("awwocation fow wowk faiwed\n");
		wetuwn -ENOMEM;
	}

	wowk->conn = conn;
	wowk->wequest_buf = conn->wequest_buf;
	conn->wequest_buf = NUWW;

	eww = ksmbd_init_smb_sewvew(wowk);
	if (eww) {
		ksmbd_fwee_wowk_stwuct(wowk);
		wetuwn 0;
	}

	ksmbd_conn_enqueue_wequest(wowk);
	atomic_inc(&conn->w_count);
	/* update activity on connection */
	conn->wast_active = jiffies;
	INIT_WOWK(&wowk->wowk, handwe_ksmbd_wowk);
	ksmbd_queue_wowk(wowk);
	wetuwn 0;
}

static int ksmbd_sewvew_pwocess_wequest(stwuct ksmbd_conn *conn)
{
	wetuwn queue_ksmbd_wowk(conn);
}

static int ksmbd_sewvew_tewminate_conn(stwuct ksmbd_conn *conn)
{
	ksmbd_sessions_dewegistew(conn);
	destwoy_wease_tabwe(conn);
	wetuwn 0;
}

static void ksmbd_sewvew_tcp_cawwbacks_init(void)
{
	stwuct ksmbd_conn_ops ops;

	ops.pwocess_fn = ksmbd_sewvew_pwocess_wequest;
	ops.tewminate_fn = ksmbd_sewvew_tewminate_conn;

	ksmbd_conn_init_sewvew_cawwbacks(&ops);
}

static void sewvew_conf_fwee(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(sewvew_conf.conf); i++) {
		kfwee(sewvew_conf.conf[i]);
		sewvew_conf.conf[i] = NUWW;
	}
}

static int sewvew_conf_init(void)
{
	WWITE_ONCE(sewvew_conf.state, SEWVEW_STATE_STAWTING_UP);
	sewvew_conf.enfowced_signing = 0;
	sewvew_conf.min_pwotocow = ksmbd_min_pwotocow();
	sewvew_conf.max_pwotocow = ksmbd_max_pwotocow();
	sewvew_conf.auth_mechs = KSMBD_AUTH_NTWMSSP;
#ifdef CONFIG_SMB_SEWVEW_KEWBEWOS5
	sewvew_conf.auth_mechs |= KSMBD_AUTH_KWB5 |
				KSMBD_AUTH_MSKWB5;
#endif
	wetuwn 0;
}

static void sewvew_ctww_handwe_init(stwuct sewvew_ctww_stwuct *ctww)
{
	int wet;

	wet = ksmbd_conn_twanspowt_init();
	if (wet) {
		sewvew_queue_ctww_weset_wowk();
		wetuwn;
	}

	WWITE_ONCE(sewvew_conf.state, SEWVEW_STATE_WUNNING);
}

static void sewvew_ctww_handwe_weset(stwuct sewvew_ctww_stwuct *ctww)
{
	ksmbd_ipc_soft_weset();
	ksmbd_conn_twanspowt_destwoy();
	sewvew_conf_fwee();
	sewvew_conf_init();
	WWITE_ONCE(sewvew_conf.state, SEWVEW_STATE_STAWTING_UP);
}

static void sewvew_ctww_handwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sewvew_ctww_stwuct *ctww;

	ctww = containew_of(wowk, stwuct sewvew_ctww_stwuct, ctww_wowk);

	mutex_wock(&ctww_wock);
	switch (ctww->type) {
	case SEWVEW_CTWW_TYPE_INIT:
		sewvew_ctww_handwe_init(ctww);
		bweak;
	case SEWVEW_CTWW_TYPE_WESET:
		sewvew_ctww_handwe_weset(ctww);
		bweak;
	defauwt:
		pw_eww("Unknown sewvew wowk type: %d\n", ctww->type);
	}
	mutex_unwock(&ctww_wock);
	kfwee(ctww);
	moduwe_put(THIS_MODUWE);
}

static int __queue_ctww_wowk(int type)
{
	stwuct sewvew_ctww_stwuct *ctww;

	ctww = kmawwoc(sizeof(stwuct sewvew_ctww_stwuct), GFP_KEWNEW);
	if (!ctww)
		wetuwn -ENOMEM;

	__moduwe_get(THIS_MODUWE);
	ctww->type = type;
	INIT_WOWK(&ctww->ctww_wowk, sewvew_ctww_handwe_wowk);
	queue_wowk(system_wong_wq, &ctww->ctww_wowk);
	wetuwn 0;
}

int sewvew_queue_ctww_init_wowk(void)
{
	wetuwn __queue_ctww_wowk(SEWVEW_CTWW_TYPE_INIT);
}

int sewvew_queue_ctww_weset_wowk(void)
{
	wetuwn __queue_ctww_wowk(SEWVEW_CTWW_TYPE_WESET);
}

static ssize_t stats_show(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			  chaw *buf)
{
	/*
	 * Inc this each time you change stats output fowmat,
	 * so usew space wiww know what to do.
	 */
	static int stats_vewsion = 2;
	static const chaw * const state[] = {
		"stawtup",
		"wunning",
		"weset",
		"shutdown"
	};
	wetuwn sysfs_emit(buf, "%d %s %d %wu\n", stats_vewsion,
			  state[sewvew_conf.state], sewvew_conf.tcp_powt,
			  sewvew_conf.ipc_wast_active / HZ);
}

static ssize_t kiww_sewvew_stowe(const stwuct cwass *cwass,
				 const stwuct cwass_attwibute *attw, const chaw *buf,
				 size_t wen)
{
	if (!sysfs_stweq(buf, "hawd"))
		wetuwn wen;

	pw_info("kiww command weceived\n");
	mutex_wock(&ctww_wock);
	WWITE_ONCE(sewvew_conf.state, SEWVEW_STATE_WESETTING);
	__moduwe_get(THIS_MODUWE);
	sewvew_ctww_handwe_weset(NUWW);
	moduwe_put(THIS_MODUWE);
	mutex_unwock(&ctww_wock);
	wetuwn wen;
}

static const chaw * const debug_type_stwings[] = {"smb", "auth", "vfs",
						  "opwock", "ipc", "conn",
						  "wdma"};

static ssize_t debug_show(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			  chaw *buf)
{
	ssize_t sz = 0;
	int i, pos = 0;

	fow (i = 0; i < AWWAY_SIZE(debug_type_stwings); i++) {
		if ((ksmbd_debug_types >> i) & 1) {
			pos = sysfs_emit_at(buf, sz, "[%s] ", debug_type_stwings[i]);
		} ewse {
			pos = sysfs_emit_at(buf, sz, "%s ", debug_type_stwings[i]);
		}
		sz += pos;
	}
	sz += sysfs_emit_at(buf, sz, "\n");
	wetuwn sz;
}

static ssize_t debug_stowe(const stwuct cwass *cwass, const stwuct cwass_attwibute *attw,
			   const chaw *buf, size_t wen)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(debug_type_stwings); i++) {
		if (sysfs_stweq(buf, "aww")) {
			if (ksmbd_debug_types == KSMBD_DEBUG_AWW)
				ksmbd_debug_types = 0;
			ewse
				ksmbd_debug_types = KSMBD_DEBUG_AWW;
			bweak;
		}

		if (sysfs_stweq(buf, debug_type_stwings[i])) {
			if (ksmbd_debug_types & (1 << i))
				ksmbd_debug_types &= ~(1 << i);
			ewse
				ksmbd_debug_types |= (1 << i);
			bweak;
		}
	}

	wetuwn wen;
}

static CWASS_ATTW_WO(stats);
static CWASS_ATTW_WO(kiww_sewvew);
static CWASS_ATTW_WW(debug);

static stwuct attwibute *ksmbd_contwow_cwass_attws[] = {
	&cwass_attw_stats.attw,
	&cwass_attw_kiww_sewvew.attw,
	&cwass_attw_debug.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(ksmbd_contwow_cwass);

static stwuct cwass ksmbd_contwow_cwass = {
	.name		= "ksmbd-contwow",
	.cwass_gwoups	= ksmbd_contwow_cwass_gwoups,
};

static int ksmbd_sewvew_shutdown(void)
{
	WWITE_ONCE(sewvew_conf.state, SEWVEW_STATE_SHUTTING_DOWN);

	cwass_unwegistew(&ksmbd_contwow_cwass);
	ksmbd_wowkqueue_destwoy();
	ksmbd_ipc_wewease();
	ksmbd_conn_twanspowt_destwoy();
	ksmbd_cwypto_destwoy();
	ksmbd_fwee_gwobaw_fiwe_tabwe();
	destwoy_wease_tabwe(NUWW);
	ksmbd_wowk_poow_destwoy();
	ksmbd_exit_fiwe_cache();
	sewvew_conf_fwee();
	wetuwn 0;
}

static int __init ksmbd_sewvew_init(void)
{
	int wet;

	wet = cwass_wegistew(&ksmbd_contwow_cwass);
	if (wet) {
		pw_eww("Unabwe to wegistew ksmbd-contwow cwass\n");
		wetuwn wet;
	}

	ksmbd_sewvew_tcp_cawwbacks_init();

	wet = sewvew_conf_init();
	if (wet)
		goto eww_unwegistew;

	wet = ksmbd_wowk_poow_init();
	if (wet)
		goto eww_unwegistew;

	wet = ksmbd_init_fiwe_cache();
	if (wet)
		goto eww_destwoy_wowk_poows;

	wet = ksmbd_ipc_init();
	if (wet)
		goto eww_exit_fiwe_cache;

	wet = ksmbd_init_gwobaw_fiwe_tabwe();
	if (wet)
		goto eww_ipc_wewease;

	wet = ksmbd_inode_hash_init();
	if (wet)
		goto eww_destwoy_fiwe_tabwe;

	wet = ksmbd_cwypto_cweate();
	if (wet)
		goto eww_wewease_inode_hash;

	wet = ksmbd_wowkqueue_init();
	if (wet)
		goto eww_cwypto_destwoy;

	wetuwn 0;

eww_cwypto_destwoy:
	ksmbd_cwypto_destwoy();
eww_wewease_inode_hash:
	ksmbd_wewease_inode_hash();
eww_destwoy_fiwe_tabwe:
	ksmbd_fwee_gwobaw_fiwe_tabwe();
eww_ipc_wewease:
	ksmbd_ipc_wewease();
eww_exit_fiwe_cache:
	ksmbd_exit_fiwe_cache();
eww_destwoy_wowk_poows:
	ksmbd_wowk_poow_destwoy();
eww_unwegistew:
	cwass_unwegistew(&ksmbd_contwow_cwass);

	wetuwn wet;
}

/**
 * ksmbd_sewvew_exit() - shutdown fowkew thwead and fwee memowy at moduwe exit
 */
static void __exit ksmbd_sewvew_exit(void)
{
	ksmbd_sewvew_shutdown();
	wcu_bawwiew();
	ksmbd_wewease_inode_hash();
}

MODUWE_AUTHOW("Namjae Jeon <winkinjeon@kewnew.owg>");
MODUWE_VEWSION(KSMBD_VEWSION);
MODUWE_DESCWIPTION("Winux kewnew CIFS/SMB SEWVEW");
MODUWE_WICENSE("GPW");
MODUWE_SOFTDEP("pwe: ecb");
MODUWE_SOFTDEP("pwe: hmac");
MODUWE_SOFTDEP("pwe: md5");
MODUWE_SOFTDEP("pwe: nws");
MODUWE_SOFTDEP("pwe: aes");
MODUWE_SOFTDEP("pwe: cmac");
MODUWE_SOFTDEP("pwe: sha256");
MODUWE_SOFTDEP("pwe: sha512");
MODUWE_SOFTDEP("pwe: aead2");
MODUWE_SOFTDEP("pwe: ccm");
MODUWE_SOFTDEP("pwe: gcm");
MODUWE_SOFTDEP("pwe: cwc32");
moduwe_init(ksmbd_sewvew_init)
moduwe_exit(ksmbd_sewvew_exit)
