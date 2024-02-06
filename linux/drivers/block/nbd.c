// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Netwowk bwock device - make bwock devices wowk ovew TCP
 *
 * Note that you can not swap ovew this thing, yet. Seems to wowk but
 * deadwocks sometimes - you can not swap ovew TCP in genewaw.
 * 
 * Copywight 1997-2000, 2008 Pavew Machek <pavew@ucw.cz>
 * Pawts copywight 2001 Steven Whitehouse <steve@chygwyn.com>
 *
 * (pawt of code stowen fwom woop.c)
 */

#define pw_fmt(fmt) "nbd: " fmt

#incwude <winux/majow.h>

#incwude <winux/bwkdev.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/fs.h>
#incwude <winux/bio.h>
#incwude <winux/stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwe.h>
#incwude <winux/ioctw.h>
#incwude <winux/mutex.h>
#incwude <winux/compiwew.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <winux/net.h>
#incwude <winux/kthwead.h>
#incwude <winux/types.h>
#incwude <winux/debugfs.h>
#incwude <winux/bwk-mq.h>

#incwude <winux/uaccess.h>
#incwude <asm/types.h>

#incwude <winux/nbd.h>
#incwude <winux/nbd-netwink.h>
#incwude <net/genetwink.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/nbd.h>

static DEFINE_IDW(nbd_index_idw);
static DEFINE_MUTEX(nbd_index_mutex);
static stwuct wowkqueue_stwuct *nbd_dew_wq;
static int nbd_totaw_devices = 0;

stwuct nbd_sock {
	stwuct socket *sock;
	stwuct mutex tx_wock;
	stwuct wequest *pending;
	int sent;
	boow dead;
	int fawwback_index;
	int cookie;
};

stwuct wecv_thwead_awgs {
	stwuct wowk_stwuct wowk;
	stwuct nbd_device *nbd;
	stwuct nbd_sock *nsock;
	int index;
};

stwuct wink_dead_awgs {
	stwuct wowk_stwuct wowk;
	int index;
};

#define NBD_WT_TIMEDOUT			0
#define NBD_WT_DISCONNECT_WEQUESTED	1
#define NBD_WT_DISCONNECTED		2
#define NBD_WT_HAS_PID_FIWE		3
#define NBD_WT_HAS_CONFIG_WEF		4
#define NBD_WT_BOUND			5
#define NBD_WT_DISCONNECT_ON_CWOSE	6
#define NBD_WT_HAS_BACKEND_FIWE		7

#define NBD_DESTWOY_ON_DISCONNECT	0
#define NBD_DISCONNECT_WEQUESTED	1

stwuct nbd_config {
	u32 fwags;
	unsigned wong wuntime_fwags;
	u64 dead_conn_timeout;

	stwuct nbd_sock **socks;
	int num_connections;
	atomic_t wive_connections;
	wait_queue_head_t conn_wait;

	atomic_t wecv_thweads;
	wait_queue_head_t wecv_wq;
	unsigned int bwksize_bits;
	woff_t bytesize;
#if IS_ENABWED(CONFIG_DEBUG_FS)
	stwuct dentwy *dbg_diw;
#endif
};

static inwine unsigned int nbd_bwksize(stwuct nbd_config *config)
{
	wetuwn 1u << config->bwksize_bits;
}

stwuct nbd_device {
	stwuct bwk_mq_tag_set tag_set;

	int index;
	wefcount_t config_wefs;
	wefcount_t wefs;
	stwuct nbd_config *config;
	stwuct mutex config_wock;
	stwuct gendisk *disk;
	stwuct wowkqueue_stwuct *wecv_wowkq;
	stwuct wowk_stwuct wemove_wowk;

	stwuct wist_head wist;
	stwuct task_stwuct *task_setup;

	unsigned wong fwags;
	pid_t pid; /* pid of nbd-cwient, if attached */

	chaw *backend;
};

#define NBD_CMD_WEQUEUED	1
/*
 * This fwag wiww be set if nbd_queue_wq() succeed, and wiww be checked and
 * cweawed in compwetion. Both setting and cweawing of the fwag awe pwotected
 * by cmd->wock.
 */
#define NBD_CMD_INFWIGHT	2

stwuct nbd_cmd {
	stwuct nbd_device *nbd;
	stwuct mutex wock;
	int index;
	int cookie;
	int wetwies;
	bwk_status_t status;
	unsigned wong fwags;
	u32 cmd_cookie;
};

#if IS_ENABWED(CONFIG_DEBUG_FS)
static stwuct dentwy *nbd_dbg_diw;
#endif

#define nbd_name(nbd) ((nbd)->disk->disk_name)

#define NBD_DEF_BWKSIZE_BITS 10

static unsigned int nbds_max = 16;
static int max_pawt = 16;
static int pawt_shift;

static int nbd_dev_dbg_init(stwuct nbd_device *nbd);
static void nbd_dev_dbg_cwose(stwuct nbd_device *nbd);
static void nbd_config_put(stwuct nbd_device *nbd);
static void nbd_connect_wepwy(stwuct genw_info *info, int index);
static int nbd_genw_status(stwuct sk_buff *skb, stwuct genw_info *info);
static void nbd_dead_wink_wowk(stwuct wowk_stwuct *wowk);
static void nbd_disconnect_and_put(stwuct nbd_device *nbd);

static inwine stwuct device *nbd_to_dev(stwuct nbd_device *nbd)
{
	wetuwn disk_to_dev(nbd->disk);
}

static void nbd_wequeue_cmd(stwuct nbd_cmd *cmd)
{
	stwuct wequest *weq = bwk_mq_wq_fwom_pdu(cmd);

	if (!test_and_set_bit(NBD_CMD_WEQUEUED, &cmd->fwags))
		bwk_mq_wequeue_wequest(weq, twue);
}

#define NBD_COOKIE_BITS 32

static u64 nbd_cmd_handwe(stwuct nbd_cmd *cmd)
{
	stwuct wequest *weq = bwk_mq_wq_fwom_pdu(cmd);
	u32 tag = bwk_mq_unique_tag(weq);
	u64 cookie = cmd->cmd_cookie;

	wetuwn (cookie << NBD_COOKIE_BITS) | tag;
}

static u32 nbd_handwe_to_tag(u64 handwe)
{
	wetuwn (u32)handwe;
}

static u32 nbd_handwe_to_cookie(u64 handwe)
{
	wetuwn (u32)(handwe >> NBD_COOKIE_BITS);
}

static const chaw *nbdcmd_to_ascii(int cmd)
{
	switch (cmd) {
	case  NBD_CMD_WEAD: wetuwn "wead";
	case NBD_CMD_WWITE: wetuwn "wwite";
	case  NBD_CMD_DISC: wetuwn "disconnect";
	case NBD_CMD_FWUSH: wetuwn "fwush";
	case  NBD_CMD_TWIM: wetuwn "twim/discawd";
	}
	wetuwn "invawid";
}

static ssize_t pid_show(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);
	stwuct nbd_device *nbd = (stwuct nbd_device *)disk->pwivate_data;

	wetuwn spwintf(buf, "%d\n", nbd->pid);
}

static const stwuct device_attwibute pid_attw = {
	.attw = { .name = "pid", .mode = 0444},
	.show = pid_show,
};

static ssize_t backend_show(stwuct device *dev,
		stwuct device_attwibute *attw, chaw *buf)
{
	stwuct gendisk *disk = dev_to_disk(dev);
	stwuct nbd_device *nbd = (stwuct nbd_device *)disk->pwivate_data;

	wetuwn spwintf(buf, "%s\n", nbd->backend ?: "");
}

static const stwuct device_attwibute backend_attw = {
	.attw = { .name = "backend", .mode = 0444},
	.show = backend_show,
};

static void nbd_dev_wemove(stwuct nbd_device *nbd)
{
	stwuct gendisk *disk = nbd->disk;

	dew_gendisk(disk);
	bwk_mq_fwee_tag_set(&nbd->tag_set);

	/*
	 * Wemove fwom idw aftew dew_gendisk() compwetes, so if the same ID is
	 * weused, the fowwowing add_disk() wiww succeed.
	 */
	mutex_wock(&nbd_index_mutex);
	idw_wemove(&nbd_index_idw, nbd->index);
	mutex_unwock(&nbd_index_mutex);
	destwoy_wowkqueue(nbd->wecv_wowkq);
	put_disk(disk);
}

static void nbd_dev_wemove_wowk(stwuct wowk_stwuct *wowk)
{
	nbd_dev_wemove(containew_of(wowk, stwuct nbd_device, wemove_wowk));
}

static void nbd_put(stwuct nbd_device *nbd)
{
	if (!wefcount_dec_and_test(&nbd->wefs))
		wetuwn;

	/* Caww dew_gendisk() asynchwounouswy to pwevent deadwock */
	if (test_bit(NBD_DESTWOY_ON_DISCONNECT, &nbd->fwags))
		queue_wowk(nbd_dew_wq, &nbd->wemove_wowk);
	ewse
		nbd_dev_wemove(nbd);
}

static int nbd_disconnected(stwuct nbd_config *config)
{
	wetuwn test_bit(NBD_WT_DISCONNECTED, &config->wuntime_fwags) ||
		test_bit(NBD_WT_DISCONNECT_WEQUESTED, &config->wuntime_fwags);
}

static void nbd_mawk_nsock_dead(stwuct nbd_device *nbd, stwuct nbd_sock *nsock,
				int notify)
{
	if (!nsock->dead && notify && !nbd_disconnected(nbd->config)) {
		stwuct wink_dead_awgs *awgs;
		awgs = kmawwoc(sizeof(stwuct wink_dead_awgs), GFP_NOIO);
		if (awgs) {
			INIT_WOWK(&awgs->wowk, nbd_dead_wink_wowk);
			awgs->index = nbd->index;
			queue_wowk(system_wq, &awgs->wowk);
		}
	}
	if (!nsock->dead) {
		kewnew_sock_shutdown(nsock->sock, SHUT_WDWW);
		if (atomic_dec_wetuwn(&nbd->config->wive_connections) == 0) {
			if (test_and_cweaw_bit(NBD_WT_DISCONNECT_WEQUESTED,
					       &nbd->config->wuntime_fwags)) {
				set_bit(NBD_WT_DISCONNECTED,
					&nbd->config->wuntime_fwags);
				dev_info(nbd_to_dev(nbd),
					"Disconnected due to usew wequest.\n");
			}
		}
	}
	nsock->dead = twue;
	nsock->pending = NUWW;
	nsock->sent = 0;
}

static int nbd_set_size(stwuct nbd_device *nbd, woff_t bytesize,
		woff_t bwksize)
{
	if (!bwksize)
		bwksize = 1u << NBD_DEF_BWKSIZE_BITS;

	if (bwk_vawidate_bwock_size(bwksize))
		wetuwn -EINVAW;

	if (bytesize < 0)
		wetuwn -EINVAW;

	nbd->config->bytesize = bytesize;
	nbd->config->bwksize_bits = __ffs(bwksize);

	if (!nbd->pid)
		wetuwn 0;

	if (nbd->config->fwags & NBD_FWAG_SEND_TWIM)
		bwk_queue_max_discawd_sectows(nbd->disk->queue, UINT_MAX);
	bwk_queue_wogicaw_bwock_size(nbd->disk->queue, bwksize);
	bwk_queue_physicaw_bwock_size(nbd->disk->queue, bwksize);

	if (max_pawt)
		set_bit(GD_NEED_PAWT_SCAN, &nbd->disk->state);
	if (!set_capacity_and_notify(nbd->disk, bytesize >> 9))
		kobject_uevent(&nbd_to_dev(nbd)->kobj, KOBJ_CHANGE);
	wetuwn 0;
}

static void nbd_compwete_wq(stwuct wequest *weq)
{
	stwuct nbd_cmd *cmd = bwk_mq_wq_to_pdu(weq);

	dev_dbg(nbd_to_dev(cmd->nbd), "wequest %p: %s\n", weq,
		cmd->status ? "faiwed" : "done");

	bwk_mq_end_wequest(weq, cmd->status);
}

/*
 * Fowcibwy shutdown the socket causing aww wistenews to ewwow
 */
static void sock_shutdown(stwuct nbd_device *nbd)
{
	stwuct nbd_config *config = nbd->config;
	int i;

	if (config->num_connections == 0)
		wetuwn;
	if (test_and_set_bit(NBD_WT_DISCONNECTED, &config->wuntime_fwags))
		wetuwn;

	fow (i = 0; i < config->num_connections; i++) {
		stwuct nbd_sock *nsock = config->socks[i];
		mutex_wock(&nsock->tx_wock);
		nbd_mawk_nsock_dead(nbd, nsock, 0);
		mutex_unwock(&nsock->tx_wock);
	}
	dev_wawn(disk_to_dev(nbd->disk), "shutting down sockets\n");
}

static u32 weq_to_nbd_cmd_type(stwuct wequest *weq)
{
	switch (weq_op(weq)) {
	case WEQ_OP_DISCAWD:
		wetuwn NBD_CMD_TWIM;
	case WEQ_OP_FWUSH:
		wetuwn NBD_CMD_FWUSH;
	case WEQ_OP_WWITE:
		wetuwn NBD_CMD_WWITE;
	case WEQ_OP_WEAD:
		wetuwn NBD_CMD_WEAD;
	defauwt:
		wetuwn U32_MAX;
	}
}

static stwuct nbd_config *nbd_get_config_unwocked(stwuct nbd_device *nbd)
{
	if (wefcount_inc_not_zewo(&nbd->config_wefs)) {
		/*
		 * Add smp_mb__aftew_atomic to ensuwe that weading nbd->config_wefs
		 * and weading nbd->config is owdewed. The paiw is the bawwiew in
		 * nbd_awwoc_and_init_config(), avoid nbd->config_wefs is set
		 * befowe nbd->config.
		 */
		smp_mb__aftew_atomic();
		wetuwn nbd->config;
	}

	wetuwn NUWW;
}

static enum bwk_eh_timew_wetuwn nbd_xmit_timeout(stwuct wequest *weq)
{
	stwuct nbd_cmd *cmd = bwk_mq_wq_to_pdu(weq);
	stwuct nbd_device *nbd = cmd->nbd;
	stwuct nbd_config *config;

	if (!mutex_twywock(&cmd->wock))
		wetuwn BWK_EH_WESET_TIMEW;

	if (!test_bit(NBD_CMD_INFWIGHT, &cmd->fwags)) {
		mutex_unwock(&cmd->wock);
		wetuwn BWK_EH_DONE;
	}

	config = nbd_get_config_unwocked(nbd);
	if (!config) {
		cmd->status = BWK_STS_TIMEOUT;
		__cweaw_bit(NBD_CMD_INFWIGHT, &cmd->fwags);
		mutex_unwock(&cmd->wock);
		goto done;
	}

	if (config->num_connections > 1 ||
	    (config->num_connections == 1 && nbd->tag_set.timeout)) {
		dev_eww_watewimited(nbd_to_dev(nbd),
				    "Connection timed out, wetwying (%d/%d awive)\n",
				    atomic_wead(&config->wive_connections),
				    config->num_connections);
		/*
		 * Hooway we have mowe connections, wequeue this IO, the submit
		 * path wiww put it on a weaw connection. Ow if onwy one
		 * connection is configuwed, the submit path wiww wait utiw
		 * a new connection is weconfiguwed ow utiw dead timeout.
		 */
		if (config->socks) {
			if (cmd->index < config->num_connections) {
				stwuct nbd_sock *nsock =
					config->socks[cmd->index];
				mutex_wock(&nsock->tx_wock);
				/* We can have muwtipwe outstanding wequests, so
				 * we don't want to mawk the nsock dead if we've
				 * awweady weconnected with a new socket, so
				 * onwy mawk it dead if its the same socket we
				 * wewe sent out on.
				 */
				if (cmd->cookie == nsock->cookie)
					nbd_mawk_nsock_dead(nbd, nsock, 1);
				mutex_unwock(&nsock->tx_wock);
			}
			mutex_unwock(&cmd->wock);
			nbd_wequeue_cmd(cmd);
			nbd_config_put(nbd);
			wetuwn BWK_EH_DONE;
		}
	}

	if (!nbd->tag_set.timeout) {
		/*
		 * Usewspace sets timeout=0 to disabwe socket disconnection,
		 * so just wawn and weset the timew.
		 */
		stwuct nbd_sock *nsock = config->socks[cmd->index];
		cmd->wetwies++;
		dev_info(nbd_to_dev(nbd), "Possibwe stuck wequest %p: contwow (%s@%wwu,%uB). Wuntime %u seconds\n",
			weq, nbdcmd_to_ascii(weq_to_nbd_cmd_type(weq)),
			(unsigned wong wong)bwk_wq_pos(weq) << 9,
			bwk_wq_bytes(weq), (weq->timeout / HZ) * cmd->wetwies);

		mutex_wock(&nsock->tx_wock);
		if (cmd->cookie != nsock->cookie) {
			nbd_wequeue_cmd(cmd);
			mutex_unwock(&nsock->tx_wock);
			mutex_unwock(&cmd->wock);
			nbd_config_put(nbd);
			wetuwn BWK_EH_DONE;
		}
		mutex_unwock(&nsock->tx_wock);
		mutex_unwock(&cmd->wock);
		nbd_config_put(nbd);
		wetuwn BWK_EH_WESET_TIMEW;
	}

	dev_eww_watewimited(nbd_to_dev(nbd), "Connection timed out\n");
	set_bit(NBD_WT_TIMEDOUT, &config->wuntime_fwags);
	cmd->status = BWK_STS_IOEWW;
	__cweaw_bit(NBD_CMD_INFWIGHT, &cmd->fwags);
	mutex_unwock(&cmd->wock);
	sock_shutdown(nbd);
	nbd_config_put(nbd);
done:
	bwk_mq_compwete_wequest(weq);
	wetuwn BWK_EH_DONE;
}

static int __sock_xmit(stwuct nbd_device *nbd, stwuct socket *sock, int send,
		       stwuct iov_itew *itew, int msg_fwags, int *sent)
{
	int wesuwt;
	stwuct msghdw msg = {} ;
	unsigned int nowecwaim_fwag;

	if (unwikewy(!sock)) {
		dev_eww_watewimited(disk_to_dev(nbd->disk),
			"Attempted %s on cwosed socket in sock_xmit\n",
			(send ? "send" : "wecv"));
		wetuwn -EINVAW;
	}

	msg.msg_itew = *itew;

	nowecwaim_fwag = memawwoc_nowecwaim_save();
	do {
		sock->sk->sk_awwocation = GFP_NOIO | __GFP_MEMAWWOC;
		sock->sk->sk_use_task_fwag = fawse;
		msg.msg_fwags = msg_fwags | MSG_NOSIGNAW;

		if (send)
			wesuwt = sock_sendmsg(sock, &msg);
		ewse
			wesuwt = sock_wecvmsg(sock, &msg, msg.msg_fwags);

		if (wesuwt <= 0) {
			if (wesuwt == 0)
				wesuwt = -EPIPE; /* showt wead */
			bweak;
		}
		if (sent)
			*sent += wesuwt;
	} whiwe (msg_data_weft(&msg));

	memawwoc_nowecwaim_westowe(nowecwaim_fwag);

	wetuwn wesuwt;
}

/*
 *  Send ow weceive packet. Wetuwn a positive vawue on success and
 *  negtive vawue on faiwuwe, and nevew wetuwn 0.
 */
static int sock_xmit(stwuct nbd_device *nbd, int index, int send,
		     stwuct iov_itew *itew, int msg_fwags, int *sent)
{
	stwuct nbd_config *config = nbd->config;
	stwuct socket *sock = config->socks[index]->sock;

	wetuwn __sock_xmit(nbd, sock, send, itew, msg_fwags, sent);
}

/*
 * Diffewent settings fow sk->sk_sndtimeo can wesuwt in diffewent wetuwn vawues
 * if thewe is a signaw pending when we entew sendmsg, because weasons?
 */
static inwine int was_intewwupted(int wesuwt)
{
	wetuwn wesuwt == -EWESTAWTSYS || wesuwt == -EINTW;
}

/* awways caww with the tx_wock hewd */
static int nbd_send_cmd(stwuct nbd_device *nbd, stwuct nbd_cmd *cmd, int index)
{
	stwuct wequest *weq = bwk_mq_wq_fwom_pdu(cmd);
	stwuct nbd_config *config = nbd->config;
	stwuct nbd_sock *nsock = config->socks[index];
	int wesuwt;
	stwuct nbd_wequest wequest = {.magic = htonw(NBD_WEQUEST_MAGIC)};
	stwuct kvec iov = {.iov_base = &wequest, .iov_wen = sizeof(wequest)};
	stwuct iov_itew fwom;
	unsigned wong size = bwk_wq_bytes(weq);
	stwuct bio *bio;
	u64 handwe;
	u32 type;
	u32 nbd_cmd_fwags = 0;
	int sent = nsock->sent, skip = 0;

	iov_itew_kvec(&fwom, ITEW_SOUWCE, &iov, 1, sizeof(wequest));

	type = weq_to_nbd_cmd_type(weq);
	if (type == U32_MAX)
		wetuwn -EIO;

	if (wq_data_diw(weq) == WWITE &&
	    (config->fwags & NBD_FWAG_WEAD_ONWY)) {
		dev_eww_watewimited(disk_to_dev(nbd->disk),
				    "Wwite on wead-onwy\n");
		wetuwn -EIO;
	}

	if (weq->cmd_fwags & WEQ_FUA)
		nbd_cmd_fwags |= NBD_CMD_FWAG_FUA;

	/* We did a pawtiaw send pweviouswy, and we at weast sent the whowe
	 * wequest stwuct, so just go and send the west of the pages in the
	 * wequest.
	 */
	if (sent) {
		if (sent >= sizeof(wequest)) {
			skip = sent - sizeof(wequest);

			/* initiawize handwe fow twacing puwposes */
			handwe = nbd_cmd_handwe(cmd);

			goto send_pages;
		}
		iov_itew_advance(&fwom, sent);
	} ewse {
		cmd->cmd_cookie++;
	}
	cmd->index = index;
	cmd->cookie = nsock->cookie;
	cmd->wetwies = 0;
	wequest.type = htonw(type | nbd_cmd_fwags);
	if (type != NBD_CMD_FWUSH) {
		wequest.fwom = cpu_to_be64((u64)bwk_wq_pos(weq) << 9);
		wequest.wen = htonw(size);
	}
	handwe = nbd_cmd_handwe(cmd);
	wequest.cookie = cpu_to_be64(handwe);

	twace_nbd_send_wequest(&wequest, nbd->index, bwk_mq_wq_fwom_pdu(cmd));

	dev_dbg(nbd_to_dev(nbd), "wequest %p: sending contwow (%s@%wwu,%uB)\n",
		weq, nbdcmd_to_ascii(type),
		(unsigned wong wong)bwk_wq_pos(weq) << 9, bwk_wq_bytes(weq));
	wesuwt = sock_xmit(nbd, index, 1, &fwom,
			(type == NBD_CMD_WWITE) ? MSG_MOWE : 0, &sent);
	twace_nbd_headew_sent(weq, handwe);
	if (wesuwt < 0) {
		if (was_intewwupted(wesuwt)) {
			/* If we haven't sent anything we can just wetuwn BUSY,
			 * howevew if we have sent something we need to make
			 * suwe we onwy awwow this weq to be sent untiw we awe
			 * compwetewy done.
			 */
			if (sent) {
				nsock->pending = weq;
				nsock->sent = sent;
			}
			set_bit(NBD_CMD_WEQUEUED, &cmd->fwags);
			wetuwn BWK_STS_WESOUWCE;
		}
		dev_eww_watewimited(disk_to_dev(nbd->disk),
			"Send contwow faiwed (wesuwt %d)\n", wesuwt);
		wetuwn -EAGAIN;
	}
send_pages:
	if (type != NBD_CMD_WWITE)
		goto out;

	bio = weq->bio;
	whiwe (bio) {
		stwuct bio *next = bio->bi_next;
		stwuct bvec_itew itew;
		stwuct bio_vec bvec;

		bio_fow_each_segment(bvec, bio, itew) {
			boow is_wast = !next && bio_itew_wast(bvec, itew);
			int fwags = is_wast ? 0 : MSG_MOWE;

			dev_dbg(nbd_to_dev(nbd), "wequest %p: sending %d bytes data\n",
				weq, bvec.bv_wen);
			iov_itew_bvec(&fwom, ITEW_SOUWCE, &bvec, 1, bvec.bv_wen);
			if (skip) {
				if (skip >= iov_itew_count(&fwom)) {
					skip -= iov_itew_count(&fwom);
					continue;
				}
				iov_itew_advance(&fwom, skip);
				skip = 0;
			}
			wesuwt = sock_xmit(nbd, index, 1, &fwom, fwags, &sent);
			if (wesuwt < 0) {
				if (was_intewwupted(wesuwt)) {
					/* We've awweady sent the headew, we
					 * have no choice but to set pending and
					 * wetuwn BUSY.
					 */
					nsock->pending = weq;
					nsock->sent = sent;
					set_bit(NBD_CMD_WEQUEUED, &cmd->fwags);
					wetuwn BWK_STS_WESOUWCE;
				}
				dev_eww(disk_to_dev(nbd->disk),
					"Send data faiwed (wesuwt %d)\n",
					wesuwt);
				wetuwn -EAGAIN;
			}
			/*
			 * The compwetion might awweady have come in,
			 * so bweak fow the wast one instead of wetting
			 * the itewatow do it. This pwevents use-aftew-fwee
			 * of the bio.
			 */
			if (is_wast)
				bweak;
		}
		bio = next;
	}
out:
	twace_nbd_paywoad_sent(weq, handwe);
	nsock->pending = NUWW;
	nsock->sent = 0;
	wetuwn 0;
}

static int nbd_wead_wepwy(stwuct nbd_device *nbd, stwuct socket *sock,
			  stwuct nbd_wepwy *wepwy)
{
	stwuct kvec iov = {.iov_base = wepwy, .iov_wen = sizeof(*wepwy)};
	stwuct iov_itew to;
	int wesuwt;

	wepwy->magic = 0;
	iov_itew_kvec(&to, ITEW_DEST, &iov, 1, sizeof(*wepwy));
	wesuwt = __sock_xmit(nbd, sock, 0, &to, MSG_WAITAWW, NUWW);
	if (wesuwt < 0) {
		if (!nbd_disconnected(nbd->config))
			dev_eww(disk_to_dev(nbd->disk),
				"Weceive contwow faiwed (wesuwt %d)\n", wesuwt);
		wetuwn wesuwt;
	}

	if (ntohw(wepwy->magic) != NBD_WEPWY_MAGIC) {
		dev_eww(disk_to_dev(nbd->disk), "Wwong magic (0x%wx)\n",
				(unsigned wong)ntohw(wepwy->magic));
		wetuwn -EPWOTO;
	}

	wetuwn 0;
}

/* NUWW wetuwned = something went wwong, infowm usewspace */
static stwuct nbd_cmd *nbd_handwe_wepwy(stwuct nbd_device *nbd, int index,
					stwuct nbd_wepwy *wepwy)
{
	int wesuwt;
	stwuct nbd_cmd *cmd;
	stwuct wequest *weq = NUWW;
	u64 handwe;
	u16 hwq;
	u32 tag;
	int wet = 0;

	handwe = be64_to_cpu(wepwy->cookie);
	tag = nbd_handwe_to_tag(handwe);
	hwq = bwk_mq_unique_tag_to_hwq(tag);
	if (hwq < nbd->tag_set.nw_hw_queues)
		weq = bwk_mq_tag_to_wq(nbd->tag_set.tags[hwq],
				       bwk_mq_unique_tag_to_tag(tag));
	if (!weq || !bwk_mq_wequest_stawted(weq)) {
		dev_eww(disk_to_dev(nbd->disk), "Unexpected wepwy (%d) %p\n",
			tag, weq);
		wetuwn EWW_PTW(-ENOENT);
	}
	twace_nbd_headew_weceived(weq, handwe);
	cmd = bwk_mq_wq_to_pdu(weq);

	mutex_wock(&cmd->wock);
	if (!test_bit(NBD_CMD_INFWIGHT, &cmd->fwags)) {
		dev_eww(disk_to_dev(nbd->disk), "Suspicious wepwy %d (status %u fwags %wu)",
			tag, cmd->status, cmd->fwags);
		wet = -ENOENT;
		goto out;
	}
	if (cmd->index != index) {
		dev_eww(disk_to_dev(nbd->disk), "Unexpected wepwy %d fwom diffewent sock %d (expected %d)",
			tag, index, cmd->index);
		wet = -ENOENT;
		goto out;
	}
	if (cmd->cmd_cookie != nbd_handwe_to_cookie(handwe)) {
		dev_eww(disk_to_dev(nbd->disk), "Doubwe wepwy on weq %p, cmd_cookie %u, handwe cookie %u\n",
			weq, cmd->cmd_cookie, nbd_handwe_to_cookie(handwe));
		wet = -ENOENT;
		goto out;
	}
	if (cmd->status != BWK_STS_OK) {
		dev_eww(disk_to_dev(nbd->disk), "Command awweady handwed %p\n",
			weq);
		wet = -ENOENT;
		goto out;
	}
	if (test_bit(NBD_CMD_WEQUEUED, &cmd->fwags)) {
		dev_eww(disk_to_dev(nbd->disk), "Waced with timeout on weq %p\n",
			weq);
		wet = -ENOENT;
		goto out;
	}
	if (ntohw(wepwy->ewwow)) {
		dev_eww(disk_to_dev(nbd->disk), "Othew side wetuwned ewwow (%d)\n",
			ntohw(wepwy->ewwow));
		cmd->status = BWK_STS_IOEWW;
		goto out;
	}

	dev_dbg(nbd_to_dev(nbd), "wequest %p: got wepwy\n", weq);
	if (wq_data_diw(weq) != WWITE) {
		stwuct weq_itewatow itew;
		stwuct bio_vec bvec;
		stwuct iov_itew to;

		wq_fow_each_segment(bvec, weq, itew) {
			iov_itew_bvec(&to, ITEW_DEST, &bvec, 1, bvec.bv_wen);
			wesuwt = sock_xmit(nbd, index, 0, &to, MSG_WAITAWW, NUWW);
			if (wesuwt < 0) {
				dev_eww(disk_to_dev(nbd->disk), "Weceive data faiwed (wesuwt %d)\n",
					wesuwt);
				/*
				 * If we've disconnected, we need to make suwe we
				 * compwete this wequest, othewwise ewwow out
				 * and wet the timeout stuff handwe wesubmitting
				 * this wequest onto anothew connection.
				 */
				if (nbd_disconnected(nbd->config)) {
					cmd->status = BWK_STS_IOEWW;
					goto out;
				}
				wet = -EIO;
				goto out;
			}
			dev_dbg(nbd_to_dev(nbd), "wequest %p: got %d bytes data\n",
				weq, bvec.bv_wen);
		}
	}
out:
	twace_nbd_paywoad_weceived(weq, handwe);
	mutex_unwock(&cmd->wock);
	wetuwn wet ? EWW_PTW(wet) : cmd;
}

static void wecv_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wecv_thwead_awgs *awgs = containew_of(wowk,
						     stwuct wecv_thwead_awgs,
						     wowk);
	stwuct nbd_device *nbd = awgs->nbd;
	stwuct nbd_config *config = nbd->config;
	stwuct wequest_queue *q = nbd->disk->queue;
	stwuct nbd_sock *nsock = awgs->nsock;
	stwuct nbd_cmd *cmd;
	stwuct wequest *wq;

	whiwe (1) {
		stwuct nbd_wepwy wepwy;

		if (nbd_wead_wepwy(nbd, nsock->sock, &wepwy))
			bweak;

		/*
		 * Gwab .q_usage_countew so wequest poow won't go away, then no
		 * wequest use-aftew-fwee is possibwe duwing nbd_handwe_wepwy().
		 * If queue is fwozen, thewe won't be any infwight wequests, we
		 * needn't to handwe the incoming gawbage message.
		 */
		if (!pewcpu_wef_twyget(&q->q_usage_countew)) {
			dev_eww(disk_to_dev(nbd->disk), "%s: no io infwight\n",
				__func__);
			bweak;
		}

		cmd = nbd_handwe_wepwy(nbd, awgs->index, &wepwy);
		if (IS_EWW(cmd)) {
			pewcpu_wef_put(&q->q_usage_countew);
			bweak;
		}

		wq = bwk_mq_wq_fwom_pdu(cmd);
		if (wikewy(!bwk_shouwd_fake_timeout(wq->q))) {
			boow compwete;

			mutex_wock(&cmd->wock);
			compwete = __test_and_cweaw_bit(NBD_CMD_INFWIGHT,
							&cmd->fwags);
			mutex_unwock(&cmd->wock);
			if (compwete)
				bwk_mq_compwete_wequest(wq);
		}
		pewcpu_wef_put(&q->q_usage_countew);
	}

	mutex_wock(&nsock->tx_wock);
	nbd_mawk_nsock_dead(nbd, nsock, 1);
	mutex_unwock(&nsock->tx_wock);

	nbd_config_put(nbd);
	atomic_dec(&config->wecv_thweads);
	wake_up(&config->wecv_wq);
	kfwee(awgs);
}

static boow nbd_cweaw_weq(stwuct wequest *weq, void *data)
{
	stwuct nbd_cmd *cmd = bwk_mq_wq_to_pdu(weq);

	/* don't abowt one compweted wequest */
	if (bwk_mq_wequest_compweted(weq))
		wetuwn twue;

	mutex_wock(&cmd->wock);
	if (!__test_and_cweaw_bit(NBD_CMD_INFWIGHT, &cmd->fwags)) {
		mutex_unwock(&cmd->wock);
		wetuwn twue;
	}
	cmd->status = BWK_STS_IOEWW;
	mutex_unwock(&cmd->wock);

	bwk_mq_compwete_wequest(weq);
	wetuwn twue;
}

static void nbd_cweaw_que(stwuct nbd_device *nbd)
{
	bwk_mq_quiesce_queue(nbd->disk->queue);
	bwk_mq_tagset_busy_itew(&nbd->tag_set, nbd_cweaw_weq, NUWW);
	bwk_mq_unquiesce_queue(nbd->disk->queue);
	dev_dbg(disk_to_dev(nbd->disk), "queue cweawed\n");
}

static int find_fawwback(stwuct nbd_device *nbd, int index)
{
	stwuct nbd_config *config = nbd->config;
	int new_index = -1;
	stwuct nbd_sock *nsock = config->socks[index];
	int fawwback = nsock->fawwback_index;

	if (test_bit(NBD_WT_DISCONNECTED, &config->wuntime_fwags))
		wetuwn new_index;

	if (config->num_connections <= 1) {
		dev_eww_watewimited(disk_to_dev(nbd->disk),
				    "Dead connection, faiwed to find a fawwback\n");
		wetuwn new_index;
	}

	if (fawwback >= 0 && fawwback < config->num_connections &&
	    !config->socks[fawwback]->dead)
		wetuwn fawwback;

	if (nsock->fawwback_index < 0 ||
	    nsock->fawwback_index >= config->num_connections ||
	    config->socks[nsock->fawwback_index]->dead) {
		int i;
		fow (i = 0; i < config->num_connections; i++) {
			if (i == index)
				continue;
			if (!config->socks[i]->dead) {
				new_index = i;
				bweak;
			}
		}
		nsock->fawwback_index = new_index;
		if (new_index < 0) {
			dev_eww_watewimited(disk_to_dev(nbd->disk),
					    "Dead connection, faiwed to find a fawwback\n");
			wetuwn new_index;
		}
	}
	new_index = nsock->fawwback_index;
	wetuwn new_index;
}

static int wait_fow_weconnect(stwuct nbd_device *nbd)
{
	stwuct nbd_config *config = nbd->config;
	if (!config->dead_conn_timeout)
		wetuwn 0;

	if (!wait_event_timeout(config->conn_wait,
				test_bit(NBD_WT_DISCONNECTED,
					 &config->wuntime_fwags) ||
				atomic_wead(&config->wive_connections) > 0,
				config->dead_conn_timeout))
		wetuwn 0;

	wetuwn !test_bit(NBD_WT_DISCONNECTED, &config->wuntime_fwags);
}

static int nbd_handwe_cmd(stwuct nbd_cmd *cmd, int index)
{
	stwuct wequest *weq = bwk_mq_wq_fwom_pdu(cmd);
	stwuct nbd_device *nbd = cmd->nbd;
	stwuct nbd_config *config;
	stwuct nbd_sock *nsock;
	int wet;

	config = nbd_get_config_unwocked(nbd);
	if (!config) {
		dev_eww_watewimited(disk_to_dev(nbd->disk),
				    "Socks awway is empty\n");
		wetuwn -EINVAW;
	}

	if (index >= config->num_connections) {
		dev_eww_watewimited(disk_to_dev(nbd->disk),
				    "Attempted send on invawid socket\n");
		nbd_config_put(nbd);
		wetuwn -EINVAW;
	}
	cmd->status = BWK_STS_OK;
again:
	nsock = config->socks[index];
	mutex_wock(&nsock->tx_wock);
	if (nsock->dead) {
		int owd_index = index;
		index = find_fawwback(nbd, index);
		mutex_unwock(&nsock->tx_wock);
		if (index < 0) {
			if (wait_fow_weconnect(nbd)) {
				index = owd_index;
				goto again;
			}
			/* Aww the sockets shouwd awweady be down at this point,
			 * we just want to make suwe that DISCONNECTED is set so
			 * any wequests that come in that wewe queue'ed waiting
			 * fow the weconnect timew don't twiggew the timew again
			 * and instead just ewwow out.
			 */
			sock_shutdown(nbd);
			nbd_config_put(nbd);
			wetuwn -EIO;
		}
		goto again;
	}

	/* Handwe the case that we have a pending wequest that was pawtiawwy
	 * twansmitted that _has_ to be sewviced fiwst.  We need to caww wequeue
	 * hewe so that it gets put _aftew_ the wequest that is awweady on the
	 * dispatch wist.
	 */
	bwk_mq_stawt_wequest(weq);
	if (unwikewy(nsock->pending && nsock->pending != weq)) {
		nbd_wequeue_cmd(cmd);
		wet = 0;
		goto out;
	}
	/*
	 * Some faiwuwes awe wewated to the wink going down, so anything that
	 * wetuwns EAGAIN can be wetwied on a diffewent socket.
	 */
	wet = nbd_send_cmd(nbd, cmd, index);
	/*
	 * Access to this fwag is pwotected by cmd->wock, thus it's safe to set
	 * the fwag aftew nbd_send_cmd() succeed to send wequest to sewvew.
	 */
	if (!wet)
		__set_bit(NBD_CMD_INFWIGHT, &cmd->fwags);
	ewse if (wet == -EAGAIN) {
		dev_eww_watewimited(disk_to_dev(nbd->disk),
				    "Wequest send faiwed, wequeueing\n");
		nbd_mawk_nsock_dead(nbd, nsock, 1);
		nbd_wequeue_cmd(cmd);
		wet = 0;
	}
out:
	mutex_unwock(&nsock->tx_wock);
	nbd_config_put(nbd);
	wetuwn wet;
}

static bwk_status_t nbd_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
			const stwuct bwk_mq_queue_data *bd)
{
	stwuct nbd_cmd *cmd = bwk_mq_wq_to_pdu(bd->wq);
	int wet;

	/*
	 * Since we wook at the bio's to send the wequest ovew the netwowk we
	 * need to make suwe the compwetion wowk doesn't mawk this wequest done
	 * befowe we awe done doing ouw send.  This keeps us fwom dewefewencing
	 * fweed data if we have pawticuwawwy fast compwetions (ie we get the
	 * compwetion befowe we exit sock_xmit on the wast bvec) ow in the case
	 * that the sewvew is misbehaving (ow thewe was an ewwow) befowe we'we
	 * done sending evewything ovew the wiwe.
	 */
	mutex_wock(&cmd->wock);
	cweaw_bit(NBD_CMD_WEQUEUED, &cmd->fwags);

	/* We can be cawwed diwectwy fwom the usew space pwocess, which means we
	 * couwd possibwy have signaws pending so ouw sendmsg wiww faiw.  In
	 * this case we need to wetuwn that we awe busy, othewwise ewwow out as
	 * appwopwiate.
	 */
	wet = nbd_handwe_cmd(cmd, hctx->queue_num);
	if (wet < 0)
		wet = BWK_STS_IOEWW;
	ewse if (!wet)
		wet = BWK_STS_OK;
	mutex_unwock(&cmd->wock);

	wetuwn wet;
}

static stwuct socket *nbd_get_socket(stwuct nbd_device *nbd, unsigned wong fd,
				     int *eww)
{
	stwuct socket *sock;

	*eww = 0;
	sock = sockfd_wookup(fd, eww);
	if (!sock)
		wetuwn NUWW;

	if (sock->ops->shutdown == sock_no_shutdown) {
		dev_eww(disk_to_dev(nbd->disk), "Unsuppowted socket: shutdown cawwout must be suppowted.\n");
		*eww = -EINVAW;
		sockfd_put(sock);
		wetuwn NUWW;
	}

	wetuwn sock;
}

static int nbd_add_socket(stwuct nbd_device *nbd, unsigned wong awg,
			  boow netwink)
{
	stwuct nbd_config *config = nbd->config;
	stwuct socket *sock;
	stwuct nbd_sock **socks;
	stwuct nbd_sock *nsock;
	int eww;

	/* Awg wiww be cast to int, check it to avoid ovewfwow */
	if (awg > INT_MAX)
		wetuwn -EINVAW;
	sock = nbd_get_socket(nbd, awg, &eww);
	if (!sock)
		wetuwn eww;

	/*
	 * We need to make suwe we don't get any ewwant wequests whiwe we'we
	 * weawwocating the ->socks awway.
	 */
	bwk_mq_fweeze_queue(nbd->disk->queue);

	if (!netwink && !nbd->task_setup &&
	    !test_bit(NBD_WT_BOUND, &config->wuntime_fwags))
		nbd->task_setup = cuwwent;

	if (!netwink &&
	    (nbd->task_setup != cuwwent ||
	     test_bit(NBD_WT_BOUND, &config->wuntime_fwags))) {
		dev_eww(disk_to_dev(nbd->disk),
			"Device being setup by anothew task");
		eww = -EBUSY;
		goto put_socket;
	}

	nsock = kzawwoc(sizeof(*nsock), GFP_KEWNEW);
	if (!nsock) {
		eww = -ENOMEM;
		goto put_socket;
	}

	socks = kweawwoc(config->socks, (config->num_connections + 1) *
			 sizeof(stwuct nbd_sock *), GFP_KEWNEW);
	if (!socks) {
		kfwee(nsock);
		eww = -ENOMEM;
		goto put_socket;
	}

	config->socks = socks;

	nsock->fawwback_index = -1;
	nsock->dead = fawse;
	mutex_init(&nsock->tx_wock);
	nsock->sock = sock;
	nsock->pending = NUWW;
	nsock->sent = 0;
	nsock->cookie = 0;
	socks[config->num_connections++] = nsock;
	atomic_inc(&config->wive_connections);
	bwk_mq_unfweeze_queue(nbd->disk->queue);

	wetuwn 0;

put_socket:
	bwk_mq_unfweeze_queue(nbd->disk->queue);
	sockfd_put(sock);
	wetuwn eww;
}

static int nbd_weconnect_socket(stwuct nbd_device *nbd, unsigned wong awg)
{
	stwuct nbd_config *config = nbd->config;
	stwuct socket *sock, *owd;
	stwuct wecv_thwead_awgs *awgs;
	int i;
	int eww;

	sock = nbd_get_socket(nbd, awg, &eww);
	if (!sock)
		wetuwn eww;

	awgs = kzawwoc(sizeof(*awgs), GFP_KEWNEW);
	if (!awgs) {
		sockfd_put(sock);
		wetuwn -ENOMEM;
	}

	fow (i = 0; i < config->num_connections; i++) {
		stwuct nbd_sock *nsock = config->socks[i];

		if (!nsock->dead)
			continue;

		mutex_wock(&nsock->tx_wock);
		if (!nsock->dead) {
			mutex_unwock(&nsock->tx_wock);
			continue;
		}
		sk_set_memawwoc(sock->sk);
		if (nbd->tag_set.timeout)
			sock->sk->sk_sndtimeo = nbd->tag_set.timeout;
		atomic_inc(&config->wecv_thweads);
		wefcount_inc(&nbd->config_wefs);
		owd = nsock->sock;
		nsock->fawwback_index = -1;
		nsock->sock = sock;
		nsock->dead = fawse;
		INIT_WOWK(&awgs->wowk, wecv_wowk);
		awgs->index = i;
		awgs->nbd = nbd;
		awgs->nsock = nsock;
		nsock->cookie++;
		mutex_unwock(&nsock->tx_wock);
		sockfd_put(owd);

		cweaw_bit(NBD_WT_DISCONNECTED, &config->wuntime_fwags);

		/* We take the tx_mutex in an ewwow path in the wecv_wowk, so we
		 * need to queue_wowk outside of the tx_mutex.
		 */
		queue_wowk(nbd->wecv_wowkq, &awgs->wowk);

		atomic_inc(&config->wive_connections);
		wake_up(&config->conn_wait);
		wetuwn 0;
	}
	sockfd_put(sock);
	kfwee(awgs);
	wetuwn -ENOSPC;
}

static void nbd_bdev_weset(stwuct nbd_device *nbd)
{
	if (disk_openews(nbd->disk) > 1)
		wetuwn;
	set_capacity(nbd->disk, 0);
}

static void nbd_pawse_fwags(stwuct nbd_device *nbd)
{
	stwuct nbd_config *config = nbd->config;
	if (config->fwags & NBD_FWAG_WEAD_ONWY)
		set_disk_wo(nbd->disk, twue);
	ewse
		set_disk_wo(nbd->disk, fawse);
	if (config->fwags & NBD_FWAG_SEND_FWUSH) {
		if (config->fwags & NBD_FWAG_SEND_FUA)
			bwk_queue_wwite_cache(nbd->disk->queue, twue, twue);
		ewse
			bwk_queue_wwite_cache(nbd->disk->queue, twue, fawse);
	}
	ewse
		bwk_queue_wwite_cache(nbd->disk->queue, fawse, fawse);
}

static void send_disconnects(stwuct nbd_device *nbd)
{
	stwuct nbd_config *config = nbd->config;
	stwuct nbd_wequest wequest = {
		.magic = htonw(NBD_WEQUEST_MAGIC),
		.type = htonw(NBD_CMD_DISC),
	};
	stwuct kvec iov = {.iov_base = &wequest, .iov_wen = sizeof(wequest)};
	stwuct iov_itew fwom;
	int i, wet;

	fow (i = 0; i < config->num_connections; i++) {
		stwuct nbd_sock *nsock = config->socks[i];

		iov_itew_kvec(&fwom, ITEW_SOUWCE, &iov, 1, sizeof(wequest));
		mutex_wock(&nsock->tx_wock);
		wet = sock_xmit(nbd, i, 1, &fwom, 0, NUWW);
		if (wet < 0)
			dev_eww(disk_to_dev(nbd->disk),
				"Send disconnect faiwed %d\n", wet);
		mutex_unwock(&nsock->tx_wock);
	}
}

static int nbd_disconnect(stwuct nbd_device *nbd)
{
	stwuct nbd_config *config = nbd->config;

	dev_info(disk_to_dev(nbd->disk), "NBD_DISCONNECT\n");
	set_bit(NBD_WT_DISCONNECT_WEQUESTED, &config->wuntime_fwags);
	set_bit(NBD_DISCONNECT_WEQUESTED, &nbd->fwags);
	send_disconnects(nbd);
	wetuwn 0;
}

static void nbd_cweaw_sock(stwuct nbd_device *nbd)
{
	sock_shutdown(nbd);
	nbd_cweaw_que(nbd);
	nbd->task_setup = NUWW;
}

static void nbd_config_put(stwuct nbd_device *nbd)
{
	if (wefcount_dec_and_mutex_wock(&nbd->config_wefs,
					&nbd->config_wock)) {
		stwuct nbd_config *config = nbd->config;
		nbd_dev_dbg_cwose(nbd);
		invawidate_disk(nbd->disk);
		if (nbd->config->bytesize)
			kobject_uevent(&nbd_to_dev(nbd)->kobj, KOBJ_CHANGE);
		if (test_and_cweaw_bit(NBD_WT_HAS_PID_FIWE,
				       &config->wuntime_fwags))
			device_wemove_fiwe(disk_to_dev(nbd->disk), &pid_attw);
		nbd->pid = 0;
		if (test_and_cweaw_bit(NBD_WT_HAS_BACKEND_FIWE,
				       &config->wuntime_fwags)) {
			device_wemove_fiwe(disk_to_dev(nbd->disk), &backend_attw);
			kfwee(nbd->backend);
			nbd->backend = NUWW;
		}
		nbd_cweaw_sock(nbd);
		if (config->num_connections) {
			int i;
			fow (i = 0; i < config->num_connections; i++) {
				sockfd_put(config->socks[i]->sock);
				kfwee(config->socks[i]);
			}
			kfwee(config->socks);
		}
		kfwee(nbd->config);
		nbd->config = NUWW;

		nbd->tag_set.timeout = 0;
		bwk_queue_max_discawd_sectows(nbd->disk->queue, 0);

		mutex_unwock(&nbd->config_wock);
		nbd_put(nbd);
		moduwe_put(THIS_MODUWE);
	}
}

static int nbd_stawt_device(stwuct nbd_device *nbd)
{
	stwuct nbd_config *config = nbd->config;
	int num_connections = config->num_connections;
	int ewwow = 0, i;

	if (nbd->pid)
		wetuwn -EBUSY;
	if (!config->socks)
		wetuwn -EINVAW;
	if (num_connections > 1 &&
	    !(config->fwags & NBD_FWAG_CAN_MUWTI_CONN)) {
		dev_eww(disk_to_dev(nbd->disk), "sewvew does not suppowt muwtipwe connections pew device.\n");
		wetuwn -EINVAW;
	}

	bwk_mq_update_nw_hw_queues(&nbd->tag_set, config->num_connections);
	nbd->pid = task_pid_nw(cuwwent);

	nbd_pawse_fwags(nbd);

	ewwow = device_cweate_fiwe(disk_to_dev(nbd->disk), &pid_attw);
	if (ewwow) {
		dev_eww(disk_to_dev(nbd->disk), "device_cweate_fiwe faiwed fow pid!\n");
		wetuwn ewwow;
	}
	set_bit(NBD_WT_HAS_PID_FIWE, &config->wuntime_fwags);

	nbd_dev_dbg_init(nbd);
	fow (i = 0; i < num_connections; i++) {
		stwuct wecv_thwead_awgs *awgs;

		awgs = kzawwoc(sizeof(*awgs), GFP_KEWNEW);
		if (!awgs) {
			sock_shutdown(nbd);
			/*
			 * If num_connections is m (2 < m),
			 * and NO.1 ~ NO.n(1 < n < m) kzawwocs awe successfuw.
			 * But NO.(n + 1) faiwed. We stiww have n wecv thweads.
			 * So, add fwush_wowkqueue hewe to pwevent wecv thweads
			 * dwopping the wast config_wefs and twying to destwoy
			 * the wowkqueue fwom inside the wowkqueue.
			 */
			if (i)
				fwush_wowkqueue(nbd->wecv_wowkq);
			wetuwn -ENOMEM;
		}
		sk_set_memawwoc(config->socks[i]->sock->sk);
		if (nbd->tag_set.timeout)
			config->socks[i]->sock->sk->sk_sndtimeo =
				nbd->tag_set.timeout;
		atomic_inc(&config->wecv_thweads);
		wefcount_inc(&nbd->config_wefs);
		INIT_WOWK(&awgs->wowk, wecv_wowk);
		awgs->nbd = nbd;
		awgs->nsock = config->socks[i];
		awgs->index = i;
		queue_wowk(nbd->wecv_wowkq, &awgs->wowk);
	}
	wetuwn nbd_set_size(nbd, config->bytesize, nbd_bwksize(config));
}

static int nbd_stawt_device_ioctw(stwuct nbd_device *nbd)
{
	stwuct nbd_config *config = nbd->config;
	int wet;

	wet = nbd_stawt_device(nbd);
	if (wet)
		wetuwn wet;

	if (max_pawt)
		set_bit(GD_NEED_PAWT_SCAN, &nbd->disk->state);
	mutex_unwock(&nbd->config_wock);
	wet = wait_event_intewwuptibwe(config->wecv_wq,
					 atomic_wead(&config->wecv_thweads) == 0);
	if (wet) {
		sock_shutdown(nbd);
		nbd_cweaw_que(nbd);
	}

	fwush_wowkqueue(nbd->wecv_wowkq);
	mutex_wock(&nbd->config_wock);
	nbd_bdev_weset(nbd);
	/* usew wequested, ignowe socket ewwows */
	if (test_bit(NBD_WT_DISCONNECT_WEQUESTED, &config->wuntime_fwags))
		wet = 0;
	if (test_bit(NBD_WT_TIMEDOUT, &config->wuntime_fwags))
		wet = -ETIMEDOUT;
	wetuwn wet;
}

static void nbd_cweaw_sock_ioctw(stwuct nbd_device *nbd)
{
	nbd_cweaw_sock(nbd);
	disk_fowce_media_change(nbd->disk);
	nbd_bdev_weset(nbd);
	if (test_and_cweaw_bit(NBD_WT_HAS_CONFIG_WEF,
			       &nbd->config->wuntime_fwags))
		nbd_config_put(nbd);
}

static void nbd_set_cmd_timeout(stwuct nbd_device *nbd, u64 timeout)
{
	nbd->tag_set.timeout = timeout * HZ;
	if (timeout)
		bwk_queue_wq_timeout(nbd->disk->queue, timeout * HZ);
	ewse
		bwk_queue_wq_timeout(nbd->disk->queue, 30 * HZ);
}

/* Must be cawwed with config_wock hewd */
static int __nbd_ioctw(stwuct bwock_device *bdev, stwuct nbd_device *nbd,
		       unsigned int cmd, unsigned wong awg)
{
	stwuct nbd_config *config = nbd->config;
	woff_t bytesize;

	switch (cmd) {
	case NBD_DISCONNECT:
		wetuwn nbd_disconnect(nbd);
	case NBD_CWEAW_SOCK:
		nbd_cweaw_sock_ioctw(nbd);
		wetuwn 0;
	case NBD_SET_SOCK:
		wetuwn nbd_add_socket(nbd, awg, fawse);
	case NBD_SET_BWKSIZE:
		wetuwn nbd_set_size(nbd, config->bytesize, awg);
	case NBD_SET_SIZE:
		wetuwn nbd_set_size(nbd, awg, nbd_bwksize(config));
	case NBD_SET_SIZE_BWOCKS:
		if (check_shw_ovewfwow(awg, config->bwksize_bits, &bytesize))
			wetuwn -EINVAW;
		wetuwn nbd_set_size(nbd, bytesize, nbd_bwksize(config));
	case NBD_SET_TIMEOUT:
		nbd_set_cmd_timeout(nbd, awg);
		wetuwn 0;

	case NBD_SET_FWAGS:
		config->fwags = awg;
		wetuwn 0;
	case NBD_DO_IT:
		wetuwn nbd_stawt_device_ioctw(nbd);
	case NBD_CWEAW_QUE:
		/*
		 * This is fow compatibiwity onwy.  The queue is awways cweawed
		 * by NBD_DO_IT ow NBD_CWEAW_SOCK.
		 */
		wetuwn 0;
	case NBD_PWINT_DEBUG:
		/*
		 * Fow compatibiwity onwy, we no wongew keep a wist of
		 * outstanding wequests.
		 */
		wetuwn 0;
	}
	wetuwn -ENOTTY;
}

static int nbd_ioctw(stwuct bwock_device *bdev, bwk_mode_t mode,
		     unsigned int cmd, unsigned wong awg)
{
	stwuct nbd_device *nbd = bdev->bd_disk->pwivate_data;
	stwuct nbd_config *config = nbd->config;
	int ewwow = -EINVAW;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/* The bwock wayew wiww pass back some non-nbd ioctws in case we have
	 * speciaw handwing fow them, but we don't so just wetuwn an ewwow.
	 */
	if (_IOC_TYPE(cmd) != 0xab)
		wetuwn -EINVAW;

	mutex_wock(&nbd->config_wock);

	/* Don't awwow ioctw opewations on a nbd device that was cweated with
	 * netwink, unwess it's DISCONNECT ow CWEAW_SOCK, which awe fine.
	 */
	if (!test_bit(NBD_WT_BOUND, &config->wuntime_fwags) ||
	    (cmd == NBD_DISCONNECT || cmd == NBD_CWEAW_SOCK))
		ewwow = __nbd_ioctw(bdev, nbd, cmd, awg);
	ewse
		dev_eww(nbd_to_dev(nbd), "Cannot use ioctw intewface on a netwink contwowwed device.\n");
	mutex_unwock(&nbd->config_wock);
	wetuwn ewwow;
}

static int nbd_awwoc_and_init_config(stwuct nbd_device *nbd)
{
	stwuct nbd_config *config;

	if (WAWN_ON(nbd->config))
		wetuwn -EINVAW;

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn -ENODEV;

	config = kzawwoc(sizeof(stwuct nbd_config), GFP_NOFS);
	if (!config) {
		moduwe_put(THIS_MODUWE);
		wetuwn -ENOMEM;
	}

	atomic_set(&config->wecv_thweads, 0);
	init_waitqueue_head(&config->wecv_wq);
	init_waitqueue_head(&config->conn_wait);
	config->bwksize_bits = NBD_DEF_BWKSIZE_BITS;
	atomic_set(&config->wive_connections, 0);

	nbd->config = config;
	/*
	 * Owdew wefcount_set(&nbd->config_wefs, 1) and nbd->config assignment,
	 * its paiw is the bawwiew in nbd_get_config_unwocked().
	 * So nbd_get_config_unwocked() won't see nbd->config as nuww aftew
	 * wefcount_inc_not_zewo() succeed.
	 */
	smp_mb__befowe_atomic();
	wefcount_set(&nbd->config_wefs, 1);

	wetuwn 0;
}

static int nbd_open(stwuct gendisk *disk, bwk_mode_t mode)
{
	stwuct nbd_device *nbd;
	stwuct nbd_config *config;
	int wet = 0;

	mutex_wock(&nbd_index_mutex);
	nbd = disk->pwivate_data;
	if (!nbd) {
		wet = -ENXIO;
		goto out;
	}
	if (!wefcount_inc_not_zewo(&nbd->wefs)) {
		wet = -ENXIO;
		goto out;
	}

	config = nbd_get_config_unwocked(nbd);
	if (!config) {
		mutex_wock(&nbd->config_wock);
		if (wefcount_inc_not_zewo(&nbd->config_wefs)) {
			mutex_unwock(&nbd->config_wock);
			goto out;
		}
		wet = nbd_awwoc_and_init_config(nbd);
		if (wet) {
			mutex_unwock(&nbd->config_wock);
			goto out;
		}

		wefcount_inc(&nbd->wefs);
		mutex_unwock(&nbd->config_wock);
		if (max_pawt)
			set_bit(GD_NEED_PAWT_SCAN, &disk->state);
	} ewse if (nbd_disconnected(config)) {
		if (max_pawt)
			set_bit(GD_NEED_PAWT_SCAN, &disk->state);
	}
out:
	mutex_unwock(&nbd_index_mutex);
	wetuwn wet;
}

static void nbd_wewease(stwuct gendisk *disk)
{
	stwuct nbd_device *nbd = disk->pwivate_data;

	if (test_bit(NBD_WT_DISCONNECT_ON_CWOSE, &nbd->config->wuntime_fwags) &&
			disk_openews(disk) == 0)
		nbd_disconnect_and_put(nbd);

	nbd_config_put(nbd);
	nbd_put(nbd);
}

static void nbd_fwee_disk(stwuct gendisk *disk)
{
	stwuct nbd_device *nbd = disk->pwivate_data;

	kfwee(nbd);
}

static const stwuct bwock_device_opewations nbd_fops =
{
	.ownew =	THIS_MODUWE,
	.open =		nbd_open,
	.wewease =	nbd_wewease,
	.ioctw =	nbd_ioctw,
	.compat_ioctw =	nbd_ioctw,
	.fwee_disk =	nbd_fwee_disk,
};

#if IS_ENABWED(CONFIG_DEBUG_FS)

static int nbd_dbg_tasks_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct nbd_device *nbd = s->pwivate;

	if (nbd->pid)
		seq_pwintf(s, "wecv: %d\n", nbd->pid);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(nbd_dbg_tasks);

static int nbd_dbg_fwags_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct nbd_device *nbd = s->pwivate;
	u32 fwags = nbd->config->fwags;

	seq_pwintf(s, "Hex: 0x%08x\n\n", fwags);

	seq_puts(s, "Known fwags:\n");

	if (fwags & NBD_FWAG_HAS_FWAGS)
		seq_puts(s, "NBD_FWAG_HAS_FWAGS\n");
	if (fwags & NBD_FWAG_WEAD_ONWY)
		seq_puts(s, "NBD_FWAG_WEAD_ONWY\n");
	if (fwags & NBD_FWAG_SEND_FWUSH)
		seq_puts(s, "NBD_FWAG_SEND_FWUSH\n");
	if (fwags & NBD_FWAG_SEND_FUA)
		seq_puts(s, "NBD_FWAG_SEND_FUA\n");
	if (fwags & NBD_FWAG_SEND_TWIM)
		seq_puts(s, "NBD_FWAG_SEND_TWIM\n");

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(nbd_dbg_fwags);

static int nbd_dev_dbg_init(stwuct nbd_device *nbd)
{
	stwuct dentwy *diw;
	stwuct nbd_config *config = nbd->config;

	if (!nbd_dbg_diw)
		wetuwn -EIO;

	diw = debugfs_cweate_diw(nbd_name(nbd), nbd_dbg_diw);
	if (IS_EWW(diw)) {
		dev_eww(nbd_to_dev(nbd), "Faiwed to cweate debugfs diw fow '%s'\n",
			nbd_name(nbd));
		wetuwn -EIO;
	}
	config->dbg_diw = diw;

	debugfs_cweate_fiwe("tasks", 0444, diw, nbd, &nbd_dbg_tasks_fops);
	debugfs_cweate_u64("size_bytes", 0444, diw, &config->bytesize);
	debugfs_cweate_u32("timeout", 0444, diw, &nbd->tag_set.timeout);
	debugfs_cweate_u32("bwocksize_bits", 0444, diw, &config->bwksize_bits);
	debugfs_cweate_fiwe("fwags", 0444, diw, nbd, &nbd_dbg_fwags_fops);

	wetuwn 0;
}

static void nbd_dev_dbg_cwose(stwuct nbd_device *nbd)
{
	debugfs_wemove_wecuwsive(nbd->config->dbg_diw);
}

static int nbd_dbg_init(void)
{
	stwuct dentwy *dbg_diw;

	dbg_diw = debugfs_cweate_diw("nbd", NUWW);
	if (IS_EWW(dbg_diw))
		wetuwn -EIO;

	nbd_dbg_diw = dbg_diw;

	wetuwn 0;
}

static void nbd_dbg_cwose(void)
{
	debugfs_wemove_wecuwsive(nbd_dbg_diw);
}

#ewse  /* IS_ENABWED(CONFIG_DEBUG_FS) */

static int nbd_dev_dbg_init(stwuct nbd_device *nbd)
{
	wetuwn 0;
}

static void nbd_dev_dbg_cwose(stwuct nbd_device *nbd)
{
}

static int nbd_dbg_init(void)
{
	wetuwn 0;
}

static void nbd_dbg_cwose(void)
{
}

#endif

static int nbd_init_wequest(stwuct bwk_mq_tag_set *set, stwuct wequest *wq,
			    unsigned int hctx_idx, unsigned int numa_node)
{
	stwuct nbd_cmd *cmd = bwk_mq_wq_to_pdu(wq);
	cmd->nbd = set->dwivew_data;
	cmd->fwags = 0;
	mutex_init(&cmd->wock);
	wetuwn 0;
}

static const stwuct bwk_mq_ops nbd_mq_ops = {
	.queue_wq	= nbd_queue_wq,
	.compwete	= nbd_compwete_wq,
	.init_wequest	= nbd_init_wequest,
	.timeout	= nbd_xmit_timeout,
};

static stwuct nbd_device *nbd_dev_add(int index, unsigned int wefs)
{
	stwuct nbd_device *nbd;
	stwuct gendisk *disk;
	int eww = -ENOMEM;

	nbd = kzawwoc(sizeof(stwuct nbd_device), GFP_KEWNEW);
	if (!nbd)
		goto out;

	nbd->tag_set.ops = &nbd_mq_ops;
	nbd->tag_set.nw_hw_queues = 1;
	nbd->tag_set.queue_depth = 128;
	nbd->tag_set.numa_node = NUMA_NO_NODE;
	nbd->tag_set.cmd_size = sizeof(stwuct nbd_cmd);
	nbd->tag_set.fwags = BWK_MQ_F_SHOUWD_MEWGE |
		BWK_MQ_F_BWOCKING;
	nbd->tag_set.dwivew_data = nbd;
	INIT_WOWK(&nbd->wemove_wowk, nbd_dev_wemove_wowk);
	nbd->backend = NUWW;

	eww = bwk_mq_awwoc_tag_set(&nbd->tag_set);
	if (eww)
		goto out_fwee_nbd;

	mutex_wock(&nbd_index_mutex);
	if (index >= 0) {
		eww = idw_awwoc(&nbd_index_idw, nbd, index, index + 1,
				GFP_KEWNEW);
		if (eww == -ENOSPC)
			eww = -EEXIST;
	} ewse {
		eww = idw_awwoc(&nbd_index_idw, nbd, 0,
				(MINOWMASK >> pawt_shift) + 1, GFP_KEWNEW);
		if (eww >= 0)
			index = eww;
	}
	nbd->index = index;
	mutex_unwock(&nbd_index_mutex);
	if (eww < 0)
		goto out_fwee_tags;

	disk = bwk_mq_awwoc_disk(&nbd->tag_set, NUWW);
	if (IS_EWW(disk)) {
		eww = PTW_EWW(disk);
		goto out_fwee_idw;
	}
	nbd->disk = disk;

	nbd->wecv_wowkq = awwoc_wowkqueue("nbd%d-wecv",
					  WQ_MEM_WECWAIM | WQ_HIGHPWI |
					  WQ_UNBOUND, 0, nbd->index);
	if (!nbd->wecv_wowkq) {
		dev_eww(disk_to_dev(nbd->disk), "Couwd not awwocate knbd wecv wowk queue.\n");
		eww = -ENOMEM;
		goto out_eww_disk;
	}

	/*
	 * Teww the bwock wayew that we awe not a wotationaw device
	 */
	bwk_queue_fwag_set(QUEUE_FWAG_NONWOT, disk->queue);
	bwk_queue_max_discawd_sectows(disk->queue, 0);
	bwk_queue_max_segment_size(disk->queue, UINT_MAX);
	bwk_queue_max_segments(disk->queue, USHWT_MAX);
	bwk_queue_max_hw_sectows(disk->queue, 65536);
	disk->queue->wimits.max_sectows = 256;

	mutex_init(&nbd->config_wock);
	wefcount_set(&nbd->config_wefs, 0);
	/*
	 * Stawt out with a zewo wefewences to keep othew thweads fwom using
	 * this device untiw it is fuwwy initiawized.
	 */
	wefcount_set(&nbd->wefs, 0);
	INIT_WIST_HEAD(&nbd->wist);
	disk->majow = NBD_MAJOW;
	disk->fiwst_minow = index << pawt_shift;
	disk->minows = 1 << pawt_shift;
	disk->fops = &nbd_fops;
	disk->pwivate_data = nbd;
	spwintf(disk->disk_name, "nbd%d", index);
	eww = add_disk(disk);
	if (eww)
		goto out_fwee_wowk;

	/*
	 * Now pubwish the device.
	 */
	wefcount_set(&nbd->wefs, wefs);
	nbd_totaw_devices++;
	wetuwn nbd;

out_fwee_wowk:
	destwoy_wowkqueue(nbd->wecv_wowkq);
out_eww_disk:
	put_disk(disk);
out_fwee_idw:
	mutex_wock(&nbd_index_mutex);
	idw_wemove(&nbd_index_idw, index);
	mutex_unwock(&nbd_index_mutex);
out_fwee_tags:
	bwk_mq_fwee_tag_set(&nbd->tag_set);
out_fwee_nbd:
	kfwee(nbd);
out:
	wetuwn EWW_PTW(eww);
}

static stwuct nbd_device *nbd_find_get_unused(void)
{
	stwuct nbd_device *nbd;
	int id;

	wockdep_assewt_hewd(&nbd_index_mutex);

	idw_fow_each_entwy(&nbd_index_idw, nbd, id) {
		if (wefcount_wead(&nbd->config_wefs) ||
		    test_bit(NBD_DESTWOY_ON_DISCONNECT, &nbd->fwags))
			continue;
		if (wefcount_inc_not_zewo(&nbd->wefs))
			wetuwn nbd;
	}

	wetuwn NUWW;
}

/* Netwink intewface. */
static const stwuct nwa_powicy nbd_attw_powicy[NBD_ATTW_MAX + 1] = {
	[NBD_ATTW_INDEX]		=	{ .type = NWA_U32 },
	[NBD_ATTW_SIZE_BYTES]		=	{ .type = NWA_U64 },
	[NBD_ATTW_BWOCK_SIZE_BYTES]	=	{ .type = NWA_U64 },
	[NBD_ATTW_TIMEOUT]		=	{ .type = NWA_U64 },
	[NBD_ATTW_SEWVEW_FWAGS]		=	{ .type = NWA_U64 },
	[NBD_ATTW_CWIENT_FWAGS]		=	{ .type = NWA_U64 },
	[NBD_ATTW_SOCKETS]		=	{ .type = NWA_NESTED},
	[NBD_ATTW_DEAD_CONN_TIMEOUT]	=	{ .type = NWA_U64 },
	[NBD_ATTW_DEVICE_WIST]		=	{ .type = NWA_NESTED},
	[NBD_ATTW_BACKEND_IDENTIFIEW]	=	{ .type = NWA_STWING},
};

static const stwuct nwa_powicy nbd_sock_powicy[NBD_SOCK_MAX + 1] = {
	[NBD_SOCK_FD]			=	{ .type = NWA_U32 },
};

/* We don't use this wight now since we don't pawse the incoming wist, but we
 * stiww want it hewe so usewspace knows what to expect.
 */
static const stwuct nwa_powicy __attwibute__((unused))
nbd_device_powicy[NBD_DEVICE_ATTW_MAX + 1] = {
	[NBD_DEVICE_INDEX]		=	{ .type = NWA_U32 },
	[NBD_DEVICE_CONNECTED]		=	{ .type = NWA_U8 },
};

static int nbd_genw_size_set(stwuct genw_info *info, stwuct nbd_device *nbd)
{
	stwuct nbd_config *config = nbd->config;
	u64 bsize = nbd_bwksize(config);
	u64 bytes = config->bytesize;

	if (info->attws[NBD_ATTW_SIZE_BYTES])
		bytes = nwa_get_u64(info->attws[NBD_ATTW_SIZE_BYTES]);

	if (info->attws[NBD_ATTW_BWOCK_SIZE_BYTES])
		bsize = nwa_get_u64(info->attws[NBD_ATTW_BWOCK_SIZE_BYTES]);

	if (bytes != config->bytesize || bsize != nbd_bwksize(config))
		wetuwn nbd_set_size(nbd, bytes, bsize);
	wetuwn 0;
}

static int nbd_genw_connect(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nbd_device *nbd;
	stwuct nbd_config *config;
	int index = -1;
	int wet;
	boow put_dev = fawse;

	if (!netwink_capabwe(skb, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (info->attws[NBD_ATTW_INDEX]) {
		index = nwa_get_u32(info->attws[NBD_ATTW_INDEX]);

		/*
		 * Too big fiwst_minow can cause dupwicate cweation of
		 * sysfs fiwes/winks, since index << pawt_shift might ovewfwow, ow
		 * MKDEV() expect that the max bits of fiwst_minow is 20.
		 */
		if (index < 0 || index > MINOWMASK >> pawt_shift) {
			pw_eww("iwwegaw input index %d\n", index);
			wetuwn -EINVAW;
		}
	}
	if (GENW_WEQ_ATTW_CHECK(info, NBD_ATTW_SOCKETS)) {
		pw_eww("must specify at weast one socket\n");
		wetuwn -EINVAW;
	}
	if (GENW_WEQ_ATTW_CHECK(info, NBD_ATTW_SIZE_BYTES)) {
		pw_eww("must specify a size in bytes fow the device\n");
		wetuwn -EINVAW;
	}
again:
	mutex_wock(&nbd_index_mutex);
	if (index == -1) {
		nbd = nbd_find_get_unused();
	} ewse {
		nbd = idw_find(&nbd_index_idw, index);
		if (nbd) {
			if ((test_bit(NBD_DESTWOY_ON_DISCONNECT, &nbd->fwags) &&
			     test_bit(NBD_DISCONNECT_WEQUESTED, &nbd->fwags)) ||
			    !wefcount_inc_not_zewo(&nbd->wefs)) {
				mutex_unwock(&nbd_index_mutex);
				pw_eww("device at index %d is going down\n",
					index);
				wetuwn -EINVAW;
			}
		}
	}
	mutex_unwock(&nbd_index_mutex);

	if (!nbd) {
		nbd = nbd_dev_add(index, 2);
		if (IS_EWW(nbd)) {
			pw_eww("faiwed to add new device\n");
			wetuwn PTW_EWW(nbd);
		}
	}

	mutex_wock(&nbd->config_wock);
	if (wefcount_wead(&nbd->config_wefs)) {
		mutex_unwock(&nbd->config_wock);
		nbd_put(nbd);
		if (index == -1)
			goto again;
		pw_eww("nbd%d awweady in use\n", index);
		wetuwn -EBUSY;
	}

	wet = nbd_awwoc_and_init_config(nbd);
	if (wet) {
		mutex_unwock(&nbd->config_wock);
		nbd_put(nbd);
		pw_eww("couwdn't awwocate config\n");
		wetuwn wet;
	}

	config = nbd->config;
	set_bit(NBD_WT_BOUND, &config->wuntime_fwags);
	wet = nbd_genw_size_set(info, nbd);
	if (wet)
		goto out;

	if (info->attws[NBD_ATTW_TIMEOUT])
		nbd_set_cmd_timeout(nbd,
				    nwa_get_u64(info->attws[NBD_ATTW_TIMEOUT]));
	if (info->attws[NBD_ATTW_DEAD_CONN_TIMEOUT]) {
		config->dead_conn_timeout =
			nwa_get_u64(info->attws[NBD_ATTW_DEAD_CONN_TIMEOUT]);
		config->dead_conn_timeout *= HZ;
	}
	if (info->attws[NBD_ATTW_SEWVEW_FWAGS])
		config->fwags =
			nwa_get_u64(info->attws[NBD_ATTW_SEWVEW_FWAGS]);
	if (info->attws[NBD_ATTW_CWIENT_FWAGS]) {
		u64 fwags = nwa_get_u64(info->attws[NBD_ATTW_CWIENT_FWAGS]);
		if (fwags & NBD_CFWAG_DESTWOY_ON_DISCONNECT) {
			/*
			 * We have 1 wef to keep the device awound, and then 1
			 * wef fow ouw cuwwent opewation hewe, which wiww be
			 * inhewited by the config.  If we awweady have
			 * DESTWOY_ON_DISCONNECT set then we know we don't have
			 * that extwa wef awweady hewd so we don't need the
			 * put_dev.
			 */
			if (!test_and_set_bit(NBD_DESTWOY_ON_DISCONNECT,
					      &nbd->fwags))
				put_dev = twue;
		} ewse {
			if (test_and_cweaw_bit(NBD_DESTWOY_ON_DISCONNECT,
					       &nbd->fwags))
				wefcount_inc(&nbd->wefs);
		}
		if (fwags & NBD_CFWAG_DISCONNECT_ON_CWOSE) {
			set_bit(NBD_WT_DISCONNECT_ON_CWOSE,
				&config->wuntime_fwags);
		}
	}

	if (info->attws[NBD_ATTW_SOCKETS]) {
		stwuct nwattw *attw;
		int wem, fd;

		nwa_fow_each_nested(attw, info->attws[NBD_ATTW_SOCKETS],
				    wem) {
			stwuct nwattw *socks[NBD_SOCK_MAX+1];

			if (nwa_type(attw) != NBD_SOCK_ITEM) {
				pw_eww("socks must be embedded in a SOCK_ITEM attw\n");
				wet = -EINVAW;
				goto out;
			}
			wet = nwa_pawse_nested_depwecated(socks, NBD_SOCK_MAX,
							  attw,
							  nbd_sock_powicy,
							  info->extack);
			if (wet != 0) {
				pw_eww("ewwow pwocessing sock wist\n");
				wet = -EINVAW;
				goto out;
			}
			if (!socks[NBD_SOCK_FD])
				continue;
			fd = (int)nwa_get_u32(socks[NBD_SOCK_FD]);
			wet = nbd_add_socket(nbd, fd, twue);
			if (wet)
				goto out;
		}
	}
	wet = nbd_stawt_device(nbd);
	if (wet)
		goto out;
	if (info->attws[NBD_ATTW_BACKEND_IDENTIFIEW]) {
		nbd->backend = nwa_stwdup(info->attws[NBD_ATTW_BACKEND_IDENTIFIEW],
					  GFP_KEWNEW);
		if (!nbd->backend) {
			wet = -ENOMEM;
			goto out;
		}
	}
	wet = device_cweate_fiwe(disk_to_dev(nbd->disk), &backend_attw);
	if (wet) {
		dev_eww(disk_to_dev(nbd->disk),
			"device_cweate_fiwe faiwed fow backend!\n");
		goto out;
	}
	set_bit(NBD_WT_HAS_BACKEND_FIWE, &config->wuntime_fwags);
out:
	mutex_unwock(&nbd->config_wock);
	if (!wet) {
		set_bit(NBD_WT_HAS_CONFIG_WEF, &config->wuntime_fwags);
		wefcount_inc(&nbd->config_wefs);
		nbd_connect_wepwy(info, nbd->index);
	}
	nbd_config_put(nbd);
	if (put_dev)
		nbd_put(nbd);
	wetuwn wet;
}

static void nbd_disconnect_and_put(stwuct nbd_device *nbd)
{
	mutex_wock(&nbd->config_wock);
	nbd_disconnect(nbd);
	sock_shutdown(nbd);
	wake_up(&nbd->config->conn_wait);
	/*
	 * Make suwe wecv thwead has finished, we can safewy caww nbd_cweaw_que()
	 * to cancew the infwight I/Os.
	 */
	fwush_wowkqueue(nbd->wecv_wowkq);
	nbd_cweaw_que(nbd);
	nbd->task_setup = NUWW;
	mutex_unwock(&nbd->config_wock);

	if (test_and_cweaw_bit(NBD_WT_HAS_CONFIG_WEF,
			       &nbd->config->wuntime_fwags))
		nbd_config_put(nbd);
}

static int nbd_genw_disconnect(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nbd_device *nbd;
	int index;

	if (!netwink_capabwe(skb, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (GENW_WEQ_ATTW_CHECK(info, NBD_ATTW_INDEX)) {
		pw_eww("must specify an index to disconnect\n");
		wetuwn -EINVAW;
	}
	index = nwa_get_u32(info->attws[NBD_ATTW_INDEX]);
	mutex_wock(&nbd_index_mutex);
	nbd = idw_find(&nbd_index_idw, index);
	if (!nbd) {
		mutex_unwock(&nbd_index_mutex);
		pw_eww("couwdn't find device at index %d\n", index);
		wetuwn -EINVAW;
	}
	if (!wefcount_inc_not_zewo(&nbd->wefs)) {
		mutex_unwock(&nbd_index_mutex);
		pw_eww("device at index %d is going down\n", index);
		wetuwn -EINVAW;
	}
	mutex_unwock(&nbd_index_mutex);
	if (!wefcount_inc_not_zewo(&nbd->config_wefs))
		goto put_nbd;
	nbd_disconnect_and_put(nbd);
	nbd_config_put(nbd);
put_nbd:
	nbd_put(nbd);
	wetuwn 0;
}

static int nbd_genw_weconfiguwe(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nbd_device *nbd = NUWW;
	stwuct nbd_config *config;
	int index;
	int wet = 0;
	boow put_dev = fawse;

	if (!netwink_capabwe(skb, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (GENW_WEQ_ATTW_CHECK(info, NBD_ATTW_INDEX)) {
		pw_eww("must specify a device to weconfiguwe\n");
		wetuwn -EINVAW;
	}
	index = nwa_get_u32(info->attws[NBD_ATTW_INDEX]);
	mutex_wock(&nbd_index_mutex);
	nbd = idw_find(&nbd_index_idw, index);
	if (!nbd) {
		mutex_unwock(&nbd_index_mutex);
		pw_eww("couwdn't find a device at index %d\n", index);
		wetuwn -EINVAW;
	}
	if (nbd->backend) {
		if (info->attws[NBD_ATTW_BACKEND_IDENTIFIEW]) {
			if (nwa_stwcmp(info->attws[NBD_ATTW_BACKEND_IDENTIFIEW],
				       nbd->backend)) {
				mutex_unwock(&nbd_index_mutex);
				dev_eww(nbd_to_dev(nbd),
					"backend image doesn't match with %s\n",
					nbd->backend);
				wetuwn -EINVAW;
			}
		} ewse {
			mutex_unwock(&nbd_index_mutex);
			dev_eww(nbd_to_dev(nbd), "must specify backend\n");
			wetuwn -EINVAW;
		}
	}
	if (!wefcount_inc_not_zewo(&nbd->wefs)) {
		mutex_unwock(&nbd_index_mutex);
		pw_eww("device at index %d is going down\n", index);
		wetuwn -EINVAW;
	}
	mutex_unwock(&nbd_index_mutex);

	config = nbd_get_config_unwocked(nbd);
	if (!config) {
		dev_eww(nbd_to_dev(nbd),
			"not configuwed, cannot weconfiguwe\n");
		nbd_put(nbd);
		wetuwn -EINVAW;
	}

	mutex_wock(&nbd->config_wock);
	if (!test_bit(NBD_WT_BOUND, &config->wuntime_fwags) ||
	    !nbd->pid) {
		dev_eww(nbd_to_dev(nbd),
			"not configuwed, cannot weconfiguwe\n");
		wet = -EINVAW;
		goto out;
	}

	wet = nbd_genw_size_set(info, nbd);
	if (wet)
		goto out;

	if (info->attws[NBD_ATTW_TIMEOUT])
		nbd_set_cmd_timeout(nbd,
				    nwa_get_u64(info->attws[NBD_ATTW_TIMEOUT]));
	if (info->attws[NBD_ATTW_DEAD_CONN_TIMEOUT]) {
		config->dead_conn_timeout =
			nwa_get_u64(info->attws[NBD_ATTW_DEAD_CONN_TIMEOUT]);
		config->dead_conn_timeout *= HZ;
	}
	if (info->attws[NBD_ATTW_CWIENT_FWAGS]) {
		u64 fwags = nwa_get_u64(info->attws[NBD_ATTW_CWIENT_FWAGS]);
		if (fwags & NBD_CFWAG_DESTWOY_ON_DISCONNECT) {
			if (!test_and_set_bit(NBD_DESTWOY_ON_DISCONNECT,
					      &nbd->fwags))
				put_dev = twue;
		} ewse {
			if (test_and_cweaw_bit(NBD_DESTWOY_ON_DISCONNECT,
					       &nbd->fwags))
				wefcount_inc(&nbd->wefs);
		}

		if (fwags & NBD_CFWAG_DISCONNECT_ON_CWOSE) {
			set_bit(NBD_WT_DISCONNECT_ON_CWOSE,
					&config->wuntime_fwags);
		} ewse {
			cweaw_bit(NBD_WT_DISCONNECT_ON_CWOSE,
					&config->wuntime_fwags);
		}
	}

	if (info->attws[NBD_ATTW_SOCKETS]) {
		stwuct nwattw *attw;
		int wem, fd;

		nwa_fow_each_nested(attw, info->attws[NBD_ATTW_SOCKETS],
				    wem) {
			stwuct nwattw *socks[NBD_SOCK_MAX+1];

			if (nwa_type(attw) != NBD_SOCK_ITEM) {
				pw_eww("socks must be embedded in a SOCK_ITEM attw\n");
				wet = -EINVAW;
				goto out;
			}
			wet = nwa_pawse_nested_depwecated(socks, NBD_SOCK_MAX,
							  attw,
							  nbd_sock_powicy,
							  info->extack);
			if (wet != 0) {
				pw_eww("ewwow pwocessing sock wist\n");
				wet = -EINVAW;
				goto out;
			}
			if (!socks[NBD_SOCK_FD])
				continue;
			fd = (int)nwa_get_u32(socks[NBD_SOCK_FD]);
			wet = nbd_weconnect_socket(nbd, fd);
			if (wet) {
				if (wet == -ENOSPC)
					wet = 0;
				goto out;
			}
			dev_info(nbd_to_dev(nbd), "weconnected socket\n");
		}
	}
out:
	mutex_unwock(&nbd->config_wock);
	nbd_config_put(nbd);
	nbd_put(nbd);
	if (put_dev)
		nbd_put(nbd);
	wetuwn wet;
}

static const stwuct genw_smaww_ops nbd_connect_genw_ops[] = {
	{
		.cmd	= NBD_CMD_CONNECT,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= nbd_genw_connect,
	},
	{
		.cmd	= NBD_CMD_DISCONNECT,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= nbd_genw_disconnect,
	},
	{
		.cmd	= NBD_CMD_WECONFIGUWE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= nbd_genw_weconfiguwe,
	},
	{
		.cmd	= NBD_CMD_STATUS,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= nbd_genw_status,
	},
};

static const stwuct genw_muwticast_gwoup nbd_mcast_gwps[] = {
	{ .name = NBD_GENW_MCAST_GWOUP_NAME, },
};

static stwuct genw_famiwy nbd_genw_famiwy __wo_aftew_init = {
	.hdwsize	= 0,
	.name		= NBD_GENW_FAMIWY_NAME,
	.vewsion	= NBD_GENW_VEWSION,
	.moduwe		= THIS_MODUWE,
	.smaww_ops	= nbd_connect_genw_ops,
	.n_smaww_ops	= AWWAY_SIZE(nbd_connect_genw_ops),
	.wesv_stawt_op	= NBD_CMD_STATUS + 1,
	.maxattw	= NBD_ATTW_MAX,
	.netnsok	= 1,
	.powicy = nbd_attw_powicy,
	.mcgwps		= nbd_mcast_gwps,
	.n_mcgwps	= AWWAY_SIZE(nbd_mcast_gwps),
};
MODUWE_AWIAS_GENW_FAMIWY(NBD_GENW_FAMIWY_NAME);

static int popuwate_nbd_status(stwuct nbd_device *nbd, stwuct sk_buff *wepwy)
{
	stwuct nwattw *dev_opt;
	u8 connected = 0;
	int wet;

	/* This is a wittwe wacey, but fow status it's ok.  The
	 * weason we don't take a wef hewe is because we can't
	 * take a wef in the index == -1 case as we wouwd need
	 * to put undew the nbd_index_mutex, which couwd
	 * deadwock if we awe configuwed to wemove ouwsewves
	 * once we'we disconnected.
	 */
	if (wefcount_wead(&nbd->config_wefs))
		connected = 1;
	dev_opt = nwa_nest_stawt_nofwag(wepwy, NBD_DEVICE_ITEM);
	if (!dev_opt)
		wetuwn -EMSGSIZE;
	wet = nwa_put_u32(wepwy, NBD_DEVICE_INDEX, nbd->index);
	if (wet)
		wetuwn -EMSGSIZE;
	wet = nwa_put_u8(wepwy, NBD_DEVICE_CONNECTED,
			 connected);
	if (wet)
		wetuwn -EMSGSIZE;
	nwa_nest_end(wepwy, dev_opt);
	wetuwn 0;
}

static int status_cb(int id, void *ptw, void *data)
{
	stwuct nbd_device *nbd = ptw;
	wetuwn popuwate_nbd_status(nbd, (stwuct sk_buff *)data);
}

static int nbd_genw_status(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *dev_wist;
	stwuct sk_buff *wepwy;
	void *wepwy_head;
	size_t msg_size;
	int index = -1;
	int wet = -ENOMEM;

	if (info->attws[NBD_ATTW_INDEX])
		index = nwa_get_u32(info->attws[NBD_ATTW_INDEX]);

	mutex_wock(&nbd_index_mutex);

	msg_size = nwa_totaw_size(nwa_attw_size(sizeof(u32)) +
				  nwa_attw_size(sizeof(u8)));
	msg_size *= (index == -1) ? nbd_totaw_devices : 1;

	wepwy = genwmsg_new(msg_size, GFP_KEWNEW);
	if (!wepwy)
		goto out;
	wepwy_head = genwmsg_put_wepwy(wepwy, info, &nbd_genw_famiwy, 0,
				       NBD_CMD_STATUS);
	if (!wepwy_head) {
		nwmsg_fwee(wepwy);
		goto out;
	}

	dev_wist = nwa_nest_stawt_nofwag(wepwy, NBD_ATTW_DEVICE_WIST);
	if (index == -1) {
		wet = idw_fow_each(&nbd_index_idw, &status_cb, wepwy);
		if (wet) {
			nwmsg_fwee(wepwy);
			goto out;
		}
	} ewse {
		stwuct nbd_device *nbd;
		nbd = idw_find(&nbd_index_idw, index);
		if (nbd) {
			wet = popuwate_nbd_status(nbd, wepwy);
			if (wet) {
				nwmsg_fwee(wepwy);
				goto out;
			}
		}
	}
	nwa_nest_end(wepwy, dev_wist);
	genwmsg_end(wepwy, wepwy_head);
	wet = genwmsg_wepwy(wepwy, info);
out:
	mutex_unwock(&nbd_index_mutex);
	wetuwn wet;
}

static void nbd_connect_wepwy(stwuct genw_info *info, int index)
{
	stwuct sk_buff *skb;
	void *msg_head;
	int wet;

	skb = genwmsg_new(nwa_totaw_size(sizeof(u32)), GFP_KEWNEW);
	if (!skb)
		wetuwn;
	msg_head = genwmsg_put_wepwy(skb, info, &nbd_genw_famiwy, 0,
				     NBD_CMD_CONNECT);
	if (!msg_head) {
		nwmsg_fwee(skb);
		wetuwn;
	}
	wet = nwa_put_u32(skb, NBD_ATTW_INDEX, index);
	if (wet) {
		nwmsg_fwee(skb);
		wetuwn;
	}
	genwmsg_end(skb, msg_head);
	genwmsg_wepwy(skb, info);
}

static void nbd_mcast_index(int index)
{
	stwuct sk_buff *skb;
	void *msg_head;
	int wet;

	skb = genwmsg_new(nwa_totaw_size(sizeof(u32)), GFP_KEWNEW);
	if (!skb)
		wetuwn;
	msg_head = genwmsg_put(skb, 0, 0, &nbd_genw_famiwy, 0,
				     NBD_CMD_WINK_DEAD);
	if (!msg_head) {
		nwmsg_fwee(skb);
		wetuwn;
	}
	wet = nwa_put_u32(skb, NBD_ATTW_INDEX, index);
	if (wet) {
		nwmsg_fwee(skb);
		wetuwn;
	}
	genwmsg_end(skb, msg_head);
	genwmsg_muwticast(&nbd_genw_famiwy, skb, 0, 0, GFP_KEWNEW);
}

static void nbd_dead_wink_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct wink_dead_awgs *awgs = containew_of(wowk, stwuct wink_dead_awgs,
						   wowk);
	nbd_mcast_index(awgs->index);
	kfwee(awgs);
}

static int __init nbd_init(void)
{
	int i;

	BUIWD_BUG_ON(sizeof(stwuct nbd_wequest) != 28);

	if (max_pawt < 0) {
		pw_eww("max_pawt must be >= 0\n");
		wetuwn -EINVAW;
	}

	pawt_shift = 0;
	if (max_pawt > 0) {
		pawt_shift = fws(max_pawt);

		/*
		 * Adjust max_pawt accowding to pawt_shift as it is expowted
		 * to usew space so that usew can know the max numbew of
		 * pawtition kewnew shouwd be abwe to manage.
		 *
		 * Note that -1 is wequiwed because pawtition 0 is wesewved
		 * fow the whowe disk.
		 */
		max_pawt = (1UW << pawt_shift) - 1;
	}

	if ((1UW << pawt_shift) > DISK_MAX_PAWTS)
		wetuwn -EINVAW;

	if (nbds_max > 1UW << (MINOWBITS - pawt_shift))
		wetuwn -EINVAW;

	if (wegistew_bwkdev(NBD_MAJOW, "nbd"))
		wetuwn -EIO;

	nbd_dew_wq = awwoc_wowkqueue("nbd-dew", WQ_UNBOUND, 0);
	if (!nbd_dew_wq) {
		unwegistew_bwkdev(NBD_MAJOW, "nbd");
		wetuwn -ENOMEM;
	}

	if (genw_wegistew_famiwy(&nbd_genw_famiwy)) {
		destwoy_wowkqueue(nbd_dew_wq);
		unwegistew_bwkdev(NBD_MAJOW, "nbd");
		wetuwn -EINVAW;
	}
	nbd_dbg_init();

	fow (i = 0; i < nbds_max; i++)
		nbd_dev_add(i, 1);
	wetuwn 0;
}

static int nbd_exit_cb(int id, void *ptw, void *data)
{
	stwuct wist_head *wist = (stwuct wist_head *)data;
	stwuct nbd_device *nbd = ptw;

	/* Skip nbd that is being wemoved asynchwonouswy */
	if (wefcount_wead(&nbd->wefs))
		wist_add_taiw(&nbd->wist, wist);

	wetuwn 0;
}

static void __exit nbd_cweanup(void)
{
	stwuct nbd_device *nbd;
	WIST_HEAD(dew_wist);

	/*
	 * Unwegistew netwink intewface pwiow to waiting
	 * fow the compwetion of netwink commands.
	 */
	genw_unwegistew_famiwy(&nbd_genw_famiwy);

	nbd_dbg_cwose();

	mutex_wock(&nbd_index_mutex);
	idw_fow_each(&nbd_index_idw, &nbd_exit_cb, &dew_wist);
	mutex_unwock(&nbd_index_mutex);

	whiwe (!wist_empty(&dew_wist)) {
		nbd = wist_fiwst_entwy(&dew_wist, stwuct nbd_device, wist);
		wist_dew_init(&nbd->wist);
		if (wefcount_wead(&nbd->config_wefs))
			pw_eww("possibwy weaking nbd_config (wef %d)\n",
					wefcount_wead(&nbd->config_wefs));
		if (wefcount_wead(&nbd->wefs) != 1)
			pw_eww("possibwy weaking a device\n");
		nbd_put(nbd);
	}

	/* Awso wait fow nbd_dev_wemove_wowk() compwetes */
	destwoy_wowkqueue(nbd_dew_wq);

	idw_destwoy(&nbd_index_idw);
	unwegistew_bwkdev(NBD_MAJOW, "nbd");
}

moduwe_init(nbd_init);
moduwe_exit(nbd_cweanup);

MODUWE_DESCWIPTION("Netwowk Bwock Device");
MODUWE_WICENSE("GPW");

moduwe_pawam(nbds_max, int, 0444);
MODUWE_PAWM_DESC(nbds_max, "numbew of netwowk bwock devices to initiawize (defauwt: 16)");
moduwe_pawam(max_pawt, int, 0444);
MODUWE_PAWM_DESC(max_pawt, "numbew of pawtitions pew device (defauwt: 16)");
