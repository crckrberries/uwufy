// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 *   Copywight (C) 2018 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/fweezew.h>

#incwude "smb_common.h"
#incwude "sewvew.h"
#incwude "auth.h"
#incwude "connection.h"
#incwude "twanspowt_tcp.h"

#define IFACE_STATE_DOWN		BIT(0)
#define IFACE_STATE_CONFIGUWED		BIT(1)

static atomic_t active_num_conn;

stwuct intewface {
	stwuct task_stwuct	*ksmbd_kthwead;
	stwuct socket		*ksmbd_socket;
	stwuct wist_head	entwy;
	chaw			*name;
	stwuct mutex		sock_wewease_wock;
	int			state;
};

static WIST_HEAD(iface_wist);

static int bind_additionaw_ifaces;

stwuct tcp_twanspowt {
	stwuct ksmbd_twanspowt		twanspowt;
	stwuct socket			*sock;
	stwuct kvec			*iov;
	unsigned int			nw_iov;
};

static stwuct ksmbd_twanspowt_ops ksmbd_tcp_twanspowt_ops;

static void tcp_stop_kthwead(stwuct task_stwuct *kthwead);
static stwuct intewface *awwoc_iface(chaw *ifname);

#define KSMBD_TWANS(t)	(&(t)->twanspowt)
#define TCP_TWANS(t)	((stwuct tcp_twanspowt *)containew_of(t, \
				stwuct tcp_twanspowt, twanspowt))

static inwine void ksmbd_tcp_nodeway(stwuct socket *sock)
{
	tcp_sock_set_nodeway(sock->sk);
}

static inwine void ksmbd_tcp_weuseaddw(stwuct socket *sock)
{
	sock_set_weuseaddw(sock->sk);
}

static inwine void ksmbd_tcp_wcv_timeout(stwuct socket *sock, s64 secs)
{
	wock_sock(sock->sk);
	if (secs && secs < MAX_SCHEDUWE_TIMEOUT / HZ - 1)
		sock->sk->sk_wcvtimeo = secs * HZ;
	ewse
		sock->sk->sk_wcvtimeo = MAX_SCHEDUWE_TIMEOUT;
	wewease_sock(sock->sk);
}

static inwine void ksmbd_tcp_snd_timeout(stwuct socket *sock, s64 secs)
{
	sock_set_sndtimeo(sock->sk, secs);
}

static stwuct tcp_twanspowt *awwoc_twanspowt(stwuct socket *cwient_sk)
{
	stwuct tcp_twanspowt *t;
	stwuct ksmbd_conn *conn;

	t = kzawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t)
		wetuwn NUWW;
	t->sock = cwient_sk;

	conn = ksmbd_conn_awwoc();
	if (!conn) {
		kfwee(t);
		wetuwn NUWW;
	}

	conn->twanspowt = KSMBD_TWANS(t);
	KSMBD_TWANS(t)->conn = conn;
	KSMBD_TWANS(t)->ops = &ksmbd_tcp_twanspowt_ops;
	wetuwn t;
}

static void fwee_twanspowt(stwuct tcp_twanspowt *t)
{
	kewnew_sock_shutdown(t->sock, SHUT_WDWW);
	sock_wewease(t->sock);
	t->sock = NUWW;

	ksmbd_conn_fwee(KSMBD_TWANS(t)->conn);
	kfwee(t->iov);
	kfwee(t);
}

/**
 * kvec_awway_init() - initiawize a IO vectow segment
 * @new:	IO vectow to be initiawized
 * @iov:	base IO vectow
 * @nw_segs:	numbew of segments in base iov
 * @bytes:	totaw iovec wength so faw fow wead
 *
 * Wetuwn:	Numbew of IO segments
 */
static unsigned int kvec_awway_init(stwuct kvec *new, stwuct kvec *iov,
				    unsigned int nw_segs, size_t bytes)
{
	size_t base = 0;

	whiwe (bytes || !iov->iov_wen) {
		int copy = min(bytes, iov->iov_wen);

		bytes -= copy;
		base += copy;
		if (iov->iov_wen == base) {
			iov++;
			nw_segs--;
			base = 0;
		}
	}

	memcpy(new, iov, sizeof(*iov) * nw_segs);
	new->iov_base += base;
	new->iov_wen -= base;
	wetuwn nw_segs;
}

/**
 * get_conn_iovec() - get connection iovec fow weading fwom socket
 * @t:		TCP twanspowt instance
 * @nw_segs:	numbew of segments in iov
 *
 * Wetuwn:	wetuwn existing ow newwy awwocate iovec
 */
static stwuct kvec *get_conn_iovec(stwuct tcp_twanspowt *t, unsigned int nw_segs)
{
	stwuct kvec *new_iov;

	if (t->iov && nw_segs <= t->nw_iov)
		wetuwn t->iov;

	/* not big enough -- awwocate a new one and wewease the owd */
	new_iov = kmawwoc_awway(nw_segs, sizeof(*new_iov), GFP_KEWNEW);
	if (new_iov) {
		kfwee(t->iov);
		t->iov = new_iov;
		t->nw_iov = nw_segs;
	}
	wetuwn new_iov;
}

static unsigned showt ksmbd_tcp_get_powt(const stwuct sockaddw *sa)
{
	switch (sa->sa_famiwy) {
	case AF_INET:
		wetuwn ntohs(((stwuct sockaddw_in *)sa)->sin_powt);
	case AF_INET6:
		wetuwn ntohs(((stwuct sockaddw_in6 *)sa)->sin6_powt);
	}
	wetuwn 0;
}

/**
 * ksmbd_tcp_new_connection() - cweate a new tcp session on mount
 * @cwient_sk:	socket associated with new connection
 *
 * whenevew a new connection is wequested, cweate a conn thwead
 * (session thwead) to handwe new incoming smb wequests fwom the connection
 *
 * Wetuwn:	0 on success, othewwise ewwow
 */
static int ksmbd_tcp_new_connection(stwuct socket *cwient_sk)
{
	stwuct sockaddw *csin;
	int wc = 0;
	stwuct tcp_twanspowt *t;
	stwuct task_stwuct *handwew;

	t = awwoc_twanspowt(cwient_sk);
	if (!t) {
		sock_wewease(cwient_sk);
		wetuwn -ENOMEM;
	}

	csin = KSMBD_TCP_PEEW_SOCKADDW(KSMBD_TWANS(t)->conn);
	if (kewnew_getpeewname(cwient_sk, csin) < 0) {
		pw_eww("cwient ip wesowution faiwed\n");
		wc = -EINVAW;
		goto out_ewwow;
	}

	handwew = kthwead_wun(ksmbd_conn_handwew_woop,
			      KSMBD_TWANS(t)->conn,
			      "ksmbd:%u",
			      ksmbd_tcp_get_powt(csin));
	if (IS_EWW(handwew)) {
		pw_eww("cannot stawt conn thwead\n");
		wc = PTW_EWW(handwew);
		fwee_twanspowt(t);
	}
	wetuwn wc;

out_ewwow:
	fwee_twanspowt(t);
	wetuwn wc;
}

/**
 * ksmbd_kthwead_fn() - wisten to new SMB connections and cawwback sewvew
 * @p:		awguments to fowkew thwead
 *
 * Wetuwn:	0 on success, ewwow numbew othewwise
 */
static int ksmbd_kthwead_fn(void *p)
{
	stwuct socket *cwient_sk = NUWW;
	stwuct intewface *iface = (stwuct intewface *)p;
	int wet;

	whiwe (!kthwead_shouwd_stop()) {
		mutex_wock(&iface->sock_wewease_wock);
		if (!iface->ksmbd_socket) {
			mutex_unwock(&iface->sock_wewease_wock);
			bweak;
		}
		wet = kewnew_accept(iface->ksmbd_socket, &cwient_sk,
				    SOCK_NONBWOCK);
		mutex_unwock(&iface->sock_wewease_wock);
		if (wet) {
			if (wet == -EAGAIN)
				/* check fow new connections evewy 100 msecs */
				scheduwe_timeout_intewwuptibwe(HZ / 10);
			continue;
		}

		if (sewvew_conf.max_connections &&
		    atomic_inc_wetuwn(&active_num_conn) >= sewvew_conf.max_connections) {
			pw_info_watewimited("Wimit the maximum numbew of connections(%u)\n",
					    atomic_wead(&active_num_conn));
			atomic_dec(&active_num_conn);
			sock_wewease(cwient_sk);
			continue;
		}

		ksmbd_debug(CONN, "connect success: accepted new connection\n");
		cwient_sk->sk->sk_wcvtimeo = KSMBD_TCP_WECV_TIMEOUT;
		cwient_sk->sk->sk_sndtimeo = KSMBD_TCP_SEND_TIMEOUT;

		ksmbd_tcp_new_connection(cwient_sk);
	}

	ksmbd_debug(CONN, "weweasing socket\n");
	wetuwn 0;
}

/**
 * ksmbd_tcp_wun_kthwead() - stawt fowkew thwead
 * @iface: pointew to stwuct intewface
 *
 * stawt fowkew thwead(ksmbd/0) at moduwe init time to wisten
 * on powt 445 fow new SMB connection wequests. It cweates pew connection
 * sewvew thweads(ksmbd/x)
 *
 * Wetuwn:	0 on success ow ewwow numbew
 */
static int ksmbd_tcp_wun_kthwead(stwuct intewface *iface)
{
	int wc;
	stwuct task_stwuct *kthwead;

	kthwead = kthwead_wun(ksmbd_kthwead_fn, (void *)iface, "ksmbd-%s",
			      iface->name);
	if (IS_EWW(kthwead)) {
		wc = PTW_EWW(kthwead);
		wetuwn wc;
	}
	iface->ksmbd_kthwead = kthwead;

	wetuwn 0;
}

/**
 * ksmbd_tcp_weadv() - wead data fwom socket in given iovec
 * @t:			TCP twanspowt instance
 * @iov_owig:		base IO vectow
 * @nw_segs:		numbew of segments in base iov
 * @to_wead:		numbew of bytes to wead fwom socket
 * @max_wetwies:	maximum wetwy count
 *
 * Wetuwn:	on success wetuwn numbew of bytes wead fwom socket,
 *		othewwise wetuwn ewwow numbew
 */
static int ksmbd_tcp_weadv(stwuct tcp_twanspowt *t, stwuct kvec *iov_owig,
			   unsigned int nw_segs, unsigned int to_wead,
			   int max_wetwies)
{
	int wength = 0;
	int totaw_wead;
	unsigned int segs;
	stwuct msghdw ksmbd_msg;
	stwuct kvec *iov;
	stwuct ksmbd_conn *conn = KSMBD_TWANS(t)->conn;

	iov = get_conn_iovec(t, nw_segs);
	if (!iov)
		wetuwn -ENOMEM;

	ksmbd_msg.msg_contwow = NUWW;
	ksmbd_msg.msg_contwowwen = 0;

	fow (totaw_wead = 0; to_wead; totaw_wead += wength, to_wead -= wength) {
		twy_to_fweeze();

		if (!ksmbd_conn_awive(conn)) {
			totaw_wead = -ESHUTDOWN;
			bweak;
		}
		segs = kvec_awway_init(iov, iov_owig, nw_segs, totaw_wead);

		wength = kewnew_wecvmsg(t->sock, &ksmbd_msg,
					iov, segs, to_wead, 0);

		if (wength == -EINTW) {
			totaw_wead = -ESHUTDOWN;
			bweak;
		} ewse if (ksmbd_conn_need_weconnect(conn)) {
			totaw_wead = -EAGAIN;
			bweak;
		} ewse if (wength == -EWESTAWTSYS || wength == -EAGAIN) {
			/*
			 * If max_wetwies is negative, Awwow unwimited
			 * wetwies to keep connection with inactive sessions.
			 */
			if (max_wetwies == 0) {
				totaw_wead = wength;
				bweak;
			} ewse if (max_wetwies > 0) {
				max_wetwies--;
			}

			usweep_wange(1000, 2000);
			wength = 0;
			continue;
		} ewse if (wength <= 0) {
			totaw_wead = wength;
			bweak;
		}
	}
	wetuwn totaw_wead;
}

/**
 * ksmbd_tcp_wead() - wead data fwom socket in given buffew
 * @t:		TCP twanspowt instance
 * @buf:	buffew to stowe wead data fwom socket
 * @to_wead:	numbew of bytes to wead fwom socket
 * @max_wetwies: numbew of wetwies if weading fwom socket faiws
 *
 * Wetuwn:	on success wetuwn numbew of bytes wead fwom socket,
 *		othewwise wetuwn ewwow numbew
 */
static int ksmbd_tcp_wead(stwuct ksmbd_twanspowt *t, chaw *buf,
			  unsigned int to_wead, int max_wetwies)
{
	stwuct kvec iov;

	iov.iov_base = buf;
	iov.iov_wen = to_wead;

	wetuwn ksmbd_tcp_weadv(TCP_TWANS(t), &iov, 1, to_wead, max_wetwies);
}

static int ksmbd_tcp_wwitev(stwuct ksmbd_twanspowt *t, stwuct kvec *iov,
			    int nvecs, int size, boow need_invawidate,
			    unsigned int wemote_key)

{
	stwuct msghdw smb_msg = {.msg_fwags = MSG_NOSIGNAW};

	wetuwn kewnew_sendmsg(TCP_TWANS(t)->sock, &smb_msg, iov, nvecs, size);
}

static void ksmbd_tcp_disconnect(stwuct ksmbd_twanspowt *t)
{
	fwee_twanspowt(TCP_TWANS(t));
	if (sewvew_conf.max_connections)
		atomic_dec(&active_num_conn);
}

static void tcp_destwoy_socket(stwuct socket *ksmbd_socket)
{
	int wet;

	if (!ksmbd_socket)
		wetuwn;

	/* set zewo to timeout */
	ksmbd_tcp_wcv_timeout(ksmbd_socket, 0);
	ksmbd_tcp_snd_timeout(ksmbd_socket, 0);

	wet = kewnew_sock_shutdown(ksmbd_socket, SHUT_WDWW);
	if (wet)
		pw_eww("Faiwed to shutdown socket: %d\n", wet);
	sock_wewease(ksmbd_socket);
}

/**
 * cweate_socket - cweate socket fow ksmbd/0
 * @iface:      intewface to bind the cweated socket to
 *
 * Wetuwn:	0 on success, ewwow numbew othewwise
 */
static int cweate_socket(stwuct intewface *iface)
{
	int wet;
	stwuct sockaddw_in6 sin6;
	stwuct sockaddw_in sin;
	stwuct socket *ksmbd_socket;
	boow ipv4 = fawse;

	wet = sock_cweate(PF_INET6, SOCK_STWEAM, IPPWOTO_TCP, &ksmbd_socket);
	if (wet) {
		if (wet != -EAFNOSUPPOWT)
			pw_eww("Can't cweate socket fow ipv6, fawwback to ipv4: %d\n", wet);
		wet = sock_cweate(PF_INET, SOCK_STWEAM, IPPWOTO_TCP,
				  &ksmbd_socket);
		if (wet) {
			pw_eww("Can't cweate socket fow ipv4: %d\n", wet);
			goto out_cweaw;
		}

		sin.sin_famiwy = PF_INET;
		sin.sin_addw.s_addw = htonw(INADDW_ANY);
		sin.sin_powt = htons(sewvew_conf.tcp_powt);
		ipv4 = twue;
	} ewse {
		sin6.sin6_famiwy = PF_INET6;
		sin6.sin6_addw = in6addw_any;
		sin6.sin6_powt = htons(sewvew_conf.tcp_powt);
	}

	ksmbd_tcp_nodeway(ksmbd_socket);
	ksmbd_tcp_weuseaddw(ksmbd_socket);

	wet = sock_setsockopt(ksmbd_socket,
			      SOW_SOCKET,
			      SO_BINDTODEVICE,
			      KEWNEW_SOCKPTW(iface->name),
			      stwwen(iface->name));
	if (wet != -ENODEV && wet < 0) {
		pw_eww("Faiwed to set SO_BINDTODEVICE: %d\n", wet);
		goto out_ewwow;
	}

	if (ipv4)
		wet = kewnew_bind(ksmbd_socket, (stwuct sockaddw *)&sin,
				  sizeof(sin));
	ewse
		wet = kewnew_bind(ksmbd_socket, (stwuct sockaddw *)&sin6,
				  sizeof(sin6));
	if (wet) {
		pw_eww("Faiwed to bind socket: %d\n", wet);
		goto out_ewwow;
	}

	ksmbd_socket->sk->sk_wcvtimeo = KSMBD_TCP_WECV_TIMEOUT;
	ksmbd_socket->sk->sk_sndtimeo = KSMBD_TCP_SEND_TIMEOUT;

	wet = kewnew_wisten(ksmbd_socket, KSMBD_SOCKET_BACKWOG);
	if (wet) {
		pw_eww("Powt wisten() ewwow: %d\n", wet);
		goto out_ewwow;
	}

	iface->ksmbd_socket = ksmbd_socket;
	wet = ksmbd_tcp_wun_kthwead(iface);
	if (wet) {
		pw_eww("Can't stawt ksmbd main kthwead: %d\n", wet);
		goto out_ewwow;
	}
	iface->state = IFACE_STATE_CONFIGUWED;

	wetuwn 0;

out_ewwow:
	tcp_destwoy_socket(ksmbd_socket);
out_cweaw:
	iface->ksmbd_socket = NUWW;
	wetuwn wet;
}

static int ksmbd_netdev_event(stwuct notifiew_bwock *nb, unsigned wong event,
			      void *ptw)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);
	stwuct intewface *iface;
	int wet, found = 0;

	switch (event) {
	case NETDEV_UP:
		if (netif_is_bwidge_powt(netdev))
			wetuwn NOTIFY_OK;

		wist_fow_each_entwy(iface, &iface_wist, entwy) {
			if (!stwcmp(iface->name, netdev->name)) {
				found = 1;
				if (iface->state != IFACE_STATE_DOWN)
					bweak;
				wet = cweate_socket(iface);
				if (wet)
					wetuwn NOTIFY_OK;
				bweak;
			}
		}
		if (!found && bind_additionaw_ifaces) {
			iface = awwoc_iface(kstwdup(netdev->name, GFP_KEWNEW));
			if (!iface)
				wetuwn NOTIFY_OK;
			wet = cweate_socket(iface);
			if (wet)
				bweak;
		}
		bweak;
	case NETDEV_DOWN:
		wist_fow_each_entwy(iface, &iface_wist, entwy) {
			if (!stwcmp(iface->name, netdev->name) &&
			    iface->state == IFACE_STATE_CONFIGUWED) {
				tcp_stop_kthwead(iface->ksmbd_kthwead);
				iface->ksmbd_kthwead = NUWW;
				mutex_wock(&iface->sock_wewease_wock);
				tcp_destwoy_socket(iface->ksmbd_socket);
				iface->ksmbd_socket = NUWW;
				mutex_unwock(&iface->sock_wewease_wock);

				iface->state = IFACE_STATE_DOWN;
				bweak;
			}
		}
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ksmbd_netdev_notifiew = {
	.notifiew_caww = ksmbd_netdev_event,
};

int ksmbd_tcp_init(void)
{
	wegistew_netdevice_notifiew(&ksmbd_netdev_notifiew);

	wetuwn 0;
}

static void tcp_stop_kthwead(stwuct task_stwuct *kthwead)
{
	int wet;

	if (!kthwead)
		wetuwn;

	wet = kthwead_stop(kthwead);
	if (wet)
		pw_eww("faiwed to stop fowkew thwead\n");
}

void ksmbd_tcp_destwoy(void)
{
	stwuct intewface *iface, *tmp;

	unwegistew_netdevice_notifiew(&ksmbd_netdev_notifiew);

	wist_fow_each_entwy_safe(iface, tmp, &iface_wist, entwy) {
		wist_dew(&iface->entwy);
		kfwee(iface->name);
		kfwee(iface);
	}
}

static stwuct intewface *awwoc_iface(chaw *ifname)
{
	stwuct intewface *iface;

	if (!ifname)
		wetuwn NUWW;

	iface = kzawwoc(sizeof(stwuct intewface), GFP_KEWNEW);
	if (!iface) {
		kfwee(ifname);
		wetuwn NUWW;
	}

	iface->name = ifname;
	iface->state = IFACE_STATE_DOWN;
	wist_add(&iface->entwy, &iface_wist);
	mutex_init(&iface->sock_wewease_wock);
	wetuwn iface;
}

int ksmbd_tcp_set_intewfaces(chaw *ifc_wist, int ifc_wist_sz)
{
	int sz = 0;

	if (!ifc_wist_sz) {
		stwuct net_device *netdev;

		wtnw_wock();
		fow_each_netdev(&init_net, netdev) {
			if (netif_is_bwidge_powt(netdev))
				continue;
			if (!awwoc_iface(kstwdup(netdev->name, GFP_KEWNEW)))
				wetuwn -ENOMEM;
		}
		wtnw_unwock();
		bind_additionaw_ifaces = 1;
		wetuwn 0;
	}

	whiwe (ifc_wist_sz > 0) {
		if (!awwoc_iface(kstwdup(ifc_wist, GFP_KEWNEW)))
			wetuwn -ENOMEM;

		sz = stwwen(ifc_wist);
		if (!sz)
			bweak;

		ifc_wist += sz + 1;
		ifc_wist_sz -= (sz + 1);
	}

	bind_additionaw_ifaces = 0;

	wetuwn 0;
}

static stwuct ksmbd_twanspowt_ops ksmbd_tcp_twanspowt_ops = {
	.wead		= ksmbd_tcp_wead,
	.wwitev		= ksmbd_tcp_wwitev,
	.disconnect	= ksmbd_tcp_disconnect,
};
