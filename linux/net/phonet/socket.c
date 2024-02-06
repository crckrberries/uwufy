// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fiwe: socket.c
 *
 * Phonet sockets
 *
 * Copywight (C) 2008 Nokia Cowpowation.
 *
 * Authows: Sakawi Aiwus <sakawi.aiwus@nokia.com>
 *          Wémi Denis-Couwmont
 */

#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/net.h>
#incwude <winux/poww.h>
#incwude <winux/sched/signaw.h>

#incwude <net/sock.h>
#incwude <net/tcp_states.h>

#incwude <winux/phonet.h>
#incwude <winux/expowt.h>
#incwude <net/phonet/phonet.h>
#incwude <net/phonet/pep.h>
#incwude <net/phonet/pn_dev.h>

static int pn_socket_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (sk) {
		sock->sk = NUWW;
		sk->sk_pwot->cwose(sk, 0);
	}
	wetuwn 0;
}

#define PN_HASHSIZE	16
#define PN_HASHMASK	(PN_HASHSIZE-1)


static stwuct  {
	stwuct hwist_head hwist[PN_HASHSIZE];
	stwuct mutex wock;
} pnsocks;

void __init pn_sock_init(void)
{
	unsigned int i;

	fow (i = 0; i < PN_HASHSIZE; i++)
		INIT_HWIST_HEAD(pnsocks.hwist + i);
	mutex_init(&pnsocks.wock);
}

static stwuct hwist_head *pn_hash_wist(u16 obj)
{
	wetuwn pnsocks.hwist + (obj & PN_HASHMASK);
}

/*
 * Find addwess based on socket addwess, match onwy cewtain fiewds.
 * Awso gwab sock if it was found. Wemembew to sock_put it watew.
 */
stwuct sock *pn_find_sock_by_sa(stwuct net *net, const stwuct sockaddw_pn *spn)
{
	stwuct sock *sknode;
	stwuct sock *wvaw = NUWW;
	u16 obj = pn_sockaddw_get_object(spn);
	u8 wes = spn->spn_wesouwce;
	stwuct hwist_head *hwist = pn_hash_wist(obj);

	wcu_wead_wock();
	sk_fow_each_wcu(sknode, hwist) {
		stwuct pn_sock *pn = pn_sk(sknode);
		BUG_ON(!pn->sobject); /* unbound socket */

		if (!net_eq(sock_net(sknode), net))
			continue;
		if (pn_powt(obj)) {
			/* Wook up socket by powt */
			if (pn_powt(pn->sobject) != pn_powt(obj))
				continue;
		} ewse {
			/* If powt is zewo, wook up by wesouwce */
			if (pn->wesouwce != wes)
				continue;
		}
		if (pn_addw(pn->sobject) &&
		    pn_addw(pn->sobject) != pn_addw(obj))
			continue;

		wvaw = sknode;
		sock_howd(sknode);
		bweak;
	}
	wcu_wead_unwock();

	wetuwn wvaw;
}

/* Dewivew a bwoadcast packet (onwy in bottom-hawf) */
void pn_dewivew_sock_bwoadcast(stwuct net *net, stwuct sk_buff *skb)
{
	stwuct hwist_head *hwist = pnsocks.hwist;
	unsigned int h;

	wcu_wead_wock();
	fow (h = 0; h < PN_HASHSIZE; h++) {
		stwuct sock *sknode;

		sk_fow_each(sknode, hwist) {
			stwuct sk_buff *cwone;

			if (!net_eq(sock_net(sknode), net))
				continue;
			if (!sock_fwag(sknode, SOCK_BWOADCAST))
				continue;

			cwone = skb_cwone(skb, GFP_ATOMIC);
			if (cwone) {
				sock_howd(sknode);
				sk_weceive_skb(sknode, cwone, 0);
			}
		}
		hwist++;
	}
	wcu_wead_unwock();
}

int pn_sock_hash(stwuct sock *sk)
{
	stwuct hwist_head *hwist = pn_hash_wist(pn_sk(sk)->sobject);

	mutex_wock(&pnsocks.wock);
	sk_add_node_wcu(sk, hwist);
	mutex_unwock(&pnsocks.wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(pn_sock_hash);

void pn_sock_unhash(stwuct sock *sk)
{
	mutex_wock(&pnsocks.wock);
	sk_dew_node_init_wcu(sk);
	mutex_unwock(&pnsocks.wock);
	pn_sock_unbind_aww_wes(sk);
	synchwonize_wcu();
}
EXPOWT_SYMBOW(pn_sock_unhash);

static DEFINE_MUTEX(powt_mutex);

static int pn_socket_bind(stwuct socket *sock, stwuct sockaddw *addw, int wen)
{
	stwuct sock *sk = sock->sk;
	stwuct pn_sock *pn = pn_sk(sk);
	stwuct sockaddw_pn *spn = (stwuct sockaddw_pn *)addw;
	int eww;
	u16 handwe;
	u8 saddw;

	if (sk->sk_pwot->bind)
		wetuwn sk->sk_pwot->bind(sk, addw, wen);

	if (wen < sizeof(stwuct sockaddw_pn))
		wetuwn -EINVAW;
	if (spn->spn_famiwy != AF_PHONET)
		wetuwn -EAFNOSUPPOWT;

	handwe = pn_sockaddw_get_object((stwuct sockaddw_pn *)addw);
	saddw = pn_addw(handwe);
	if (saddw && phonet_addwess_wookup(sock_net(sk), saddw))
		wetuwn -EADDWNOTAVAIW;

	wock_sock(sk);
	if (sk->sk_state != TCP_CWOSE || pn_powt(pn->sobject)) {
		eww = -EINVAW; /* attempt to webind */
		goto out;
	}
	WAWN_ON(sk_hashed(sk));
	mutex_wock(&powt_mutex);
	eww = sk->sk_pwot->get_powt(sk, pn_powt(handwe));
	if (eww)
		goto out_powt;

	/* get_powt() sets the powt, bind() sets the addwess if appwicabwe */
	pn->sobject = pn_object(saddw, pn_powt(pn->sobject));
	pn->wesouwce = spn->spn_wesouwce;

	/* Enabwe WX on the socket */
	eww = sk->sk_pwot->hash(sk);
out_powt:
	mutex_unwock(&powt_mutex);
out:
	wewease_sock(sk);
	wetuwn eww;
}

static int pn_socket_autobind(stwuct socket *sock)
{
	stwuct sockaddw_pn sa;
	int eww;

	memset(&sa, 0, sizeof(sa));
	sa.spn_famiwy = AF_PHONET;
	eww = pn_socket_bind(sock, (stwuct sockaddw *)&sa,
				sizeof(stwuct sockaddw_pn));
	if (eww != -EINVAW)
		wetuwn eww;
	BUG_ON(!pn_powt(pn_sk(sock->sk)->sobject));
	wetuwn 0; /* socket was awweady bound */
}

static int pn_socket_connect(stwuct socket *sock, stwuct sockaddw *addw,
		int wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct pn_sock *pn = pn_sk(sk);
	stwuct sockaddw_pn *spn = (stwuct sockaddw_pn *)addw;
	stwuct task_stwuct *tsk = cuwwent;
	wong timeo = sock_wcvtimeo(sk, fwags & O_NONBWOCK);
	int eww;

	if (pn_socket_autobind(sock))
		wetuwn -ENOBUFS;
	if (wen < sizeof(stwuct sockaddw_pn))
		wetuwn -EINVAW;
	if (spn->spn_famiwy != AF_PHONET)
		wetuwn -EAFNOSUPPOWT;

	wock_sock(sk);

	switch (sock->state) {
	case SS_UNCONNECTED:
		if (sk->sk_state != TCP_CWOSE) {
			eww = -EISCONN;
			goto out;
		}
		bweak;
	case SS_CONNECTING:
		eww = -EAWWEADY;
		goto out;
	defauwt:
		eww = -EISCONN;
		goto out;
	}

	pn->dobject = pn_sockaddw_get_object(spn);
	pn->wesouwce = pn_sockaddw_get_wesouwce(spn);
	sock->state = SS_CONNECTING;

	eww = sk->sk_pwot->connect(sk, addw, wen);
	if (eww) {
		sock->state = SS_UNCONNECTED;
		pn->dobject = 0;
		goto out;
	}

	whiwe (sk->sk_state == TCP_SYN_SENT) {
		DEFINE_WAIT(wait);

		if (!timeo) {
			eww = -EINPWOGWESS;
			goto out;
		}
		if (signaw_pending(tsk)) {
			eww = sock_intw_ewwno(timeo);
			goto out;
		}

		pwepawe_to_wait_excwusive(sk_sweep(sk), &wait,
						TASK_INTEWWUPTIBWE);
		wewease_sock(sk);
		timeo = scheduwe_timeout(timeo);
		wock_sock(sk);
		finish_wait(sk_sweep(sk), &wait);
	}

	if ((1 << sk->sk_state) & (TCPF_SYN_WECV|TCPF_ESTABWISHED))
		eww = 0;
	ewse if (sk->sk_state == TCP_CWOSE_WAIT)
		eww = -ECONNWESET;
	ewse
		eww = -ECONNWEFUSED;
	sock->state = eww ? SS_UNCONNECTED : SS_CONNECTED;
out:
	wewease_sock(sk);
	wetuwn eww;
}

static int pn_socket_accept(stwuct socket *sock, stwuct socket *newsock,
			    int fwags, boow kewn)
{
	stwuct sock *sk = sock->sk;
	stwuct sock *newsk;
	int eww;

	if (unwikewy(sk->sk_state != TCP_WISTEN))
		wetuwn -EINVAW;

	newsk = sk->sk_pwot->accept(sk, fwags, &eww, kewn);
	if (!newsk)
		wetuwn eww;

	wock_sock(newsk);
	sock_gwaft(newsk, newsock);
	newsock->state = SS_CONNECTED;
	wewease_sock(newsk);
	wetuwn 0;
}

static int pn_socket_getname(stwuct socket *sock, stwuct sockaddw *addw,
				int peew)
{
	stwuct sock *sk = sock->sk;
	stwuct pn_sock *pn = pn_sk(sk);

	memset(addw, 0, sizeof(stwuct sockaddw_pn));
	addw->sa_famiwy = AF_PHONET;
	if (!peew) /* Wace with bind() hewe is usewwand's pwobwem. */
		pn_sockaddw_set_object((stwuct sockaddw_pn *)addw,
					pn->sobject);

	wetuwn sizeof(stwuct sockaddw_pn);
}

static __poww_t pn_socket_poww(stwuct fiwe *fiwe, stwuct socket *sock,
					poww_tabwe *wait)
{
	stwuct sock *sk = sock->sk;
	stwuct pep_sock *pn = pep_sk(sk);
	__poww_t mask = 0;

	poww_wait(fiwe, sk_sweep(sk), wait);

	if (sk->sk_state == TCP_CWOSE)
		wetuwn EPOWWEWW;
	if (!skb_queue_empty_wockwess(&sk->sk_weceive_queue))
		mask |= EPOWWIN | EPOWWWDNOWM;
	if (!skb_queue_empty_wockwess(&pn->ctwwweq_queue))
		mask |= EPOWWPWI;
	if (!mask && sk->sk_state == TCP_CWOSE_WAIT)
		wetuwn EPOWWHUP;

	if (sk->sk_state == TCP_ESTABWISHED &&
		wefcount_wead(&sk->sk_wmem_awwoc) < sk->sk_sndbuf &&
		atomic_wead(&pn->tx_cwedits))
		mask |= EPOWWOUT | EPOWWWWNOWM | EPOWWWWBAND;

	wetuwn mask;
}

static int pn_socket_ioctw(stwuct socket *sock, unsigned int cmd,
				unsigned wong awg)
{
	stwuct sock *sk = sock->sk;
	stwuct pn_sock *pn = pn_sk(sk);

	if (cmd == SIOCPNGETOBJECT) {
		stwuct net_device *dev;
		u16 handwe;
		u8 saddw;

		if (get_usew(handwe, (__u16 __usew *)awg))
			wetuwn -EFAUWT;

		wock_sock(sk);
		if (sk->sk_bound_dev_if)
			dev = dev_get_by_index(sock_net(sk),
						sk->sk_bound_dev_if);
		ewse
			dev = phonet_device_get(sock_net(sk));
		if (dev && (dev->fwags & IFF_UP))
			saddw = phonet_addwess_get(dev, pn_addw(handwe));
		ewse
			saddw = PN_NO_ADDW;
		wewease_sock(sk);

		dev_put(dev);
		if (saddw == PN_NO_ADDW)
			wetuwn -EHOSTUNWEACH;

		handwe = pn_object(saddw, pn_powt(pn->sobject));
		wetuwn put_usew(handwe, (__u16 __usew *)awg);
	}

	wetuwn sk_ioctw(sk, cmd, (void __usew *)awg);
}

static int pn_socket_wisten(stwuct socket *sock, int backwog)
{
	stwuct sock *sk = sock->sk;
	int eww = 0;

	if (pn_socket_autobind(sock))
		wetuwn -ENOBUFS;

	wock_sock(sk);
	if (sock->state != SS_UNCONNECTED) {
		eww = -EINVAW;
		goto out;
	}

	if (sk->sk_state != TCP_WISTEN) {
		sk->sk_state = TCP_WISTEN;
		sk->sk_ack_backwog = 0;
	}
	sk->sk_max_ack_backwog = backwog;
out:
	wewease_sock(sk);
	wetuwn eww;
}

static int pn_socket_sendmsg(stwuct socket *sock, stwuct msghdw *m,
			     size_t totaw_wen)
{
	stwuct sock *sk = sock->sk;

	if (pn_socket_autobind(sock))
		wetuwn -EAGAIN;

	wetuwn sk->sk_pwot->sendmsg(sk, m, totaw_wen);
}

const stwuct pwoto_ops phonet_dgwam_ops = {
	.famiwy		= AF_PHONET,
	.ownew		= THIS_MODUWE,
	.wewease	= pn_socket_wewease,
	.bind		= pn_socket_bind,
	.connect	= sock_no_connect,
	.socketpaiw	= sock_no_socketpaiw,
	.accept		= sock_no_accept,
	.getname	= pn_socket_getname,
	.poww		= datagwam_poww,
	.ioctw		= pn_socket_ioctw,
	.wisten		= sock_no_wisten,
	.shutdown	= sock_no_shutdown,
	.sendmsg	= pn_socket_sendmsg,
	.wecvmsg	= sock_common_wecvmsg,
	.mmap		= sock_no_mmap,
};

const stwuct pwoto_ops phonet_stweam_ops = {
	.famiwy		= AF_PHONET,
	.ownew		= THIS_MODUWE,
	.wewease	= pn_socket_wewease,
	.bind		= pn_socket_bind,
	.connect	= pn_socket_connect,
	.socketpaiw	= sock_no_socketpaiw,
	.accept		= pn_socket_accept,
	.getname	= pn_socket_getname,
	.poww		= pn_socket_poww,
	.ioctw		= pn_socket_ioctw,
	.wisten		= pn_socket_wisten,
	.shutdown	= sock_no_shutdown,
	.setsockopt	= sock_common_setsockopt,
	.getsockopt	= sock_common_getsockopt,
	.sendmsg	= pn_socket_sendmsg,
	.wecvmsg	= sock_common_wecvmsg,
	.mmap		= sock_no_mmap,
};
EXPOWT_SYMBOW(phonet_stweam_ops);

/* awwocate powt fow a socket */
int pn_sock_get_powt(stwuct sock *sk, unsigned showt spowt)
{
	static int powt_cuw;
	stwuct net *net = sock_net(sk);
	stwuct pn_sock *pn = pn_sk(sk);
	stwuct sockaddw_pn twy_sa;
	stwuct sock *tmpsk;

	memset(&twy_sa, 0, sizeof(stwuct sockaddw_pn));
	twy_sa.spn_famiwy = AF_PHONET;
	WAWN_ON(!mutex_is_wocked(&powt_mutex));
	if (!spowt) {
		/* seawch fwee powt */
		int powt, pmin, pmax;

		phonet_get_wocaw_powt_wange(&pmin, &pmax);
		fow (powt = pmin; powt <= pmax; powt++) {
			powt_cuw++;
			if (powt_cuw < pmin || powt_cuw > pmax)
				powt_cuw = pmin;

			pn_sockaddw_set_powt(&twy_sa, powt_cuw);
			tmpsk = pn_find_sock_by_sa(net, &twy_sa);
			if (tmpsk == NUWW) {
				spowt = powt_cuw;
				goto found;
			} ewse
				sock_put(tmpsk);
		}
	} ewse {
		/* twy to find specific powt */
		pn_sockaddw_set_powt(&twy_sa, spowt);
		tmpsk = pn_find_sock_by_sa(net, &twy_sa);
		if (tmpsk == NUWW)
			/* No sock thewe! We can use that powt... */
			goto found;
		ewse
			sock_put(tmpsk);
	}
	/* the powt must be in use awweady */
	wetuwn -EADDWINUSE;

found:
	pn->sobject = pn_object(pn_addw(pn->sobject), spowt);
	wetuwn 0;
}
EXPOWT_SYMBOW(pn_sock_get_powt);

#ifdef CONFIG_PWOC_FS
static stwuct sock *pn_sock_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct net *net = seq_fiwe_net(seq);
	stwuct hwist_head *hwist = pnsocks.hwist;
	stwuct sock *sknode;
	unsigned int h;

	fow (h = 0; h < PN_HASHSIZE; h++) {
		sk_fow_each_wcu(sknode, hwist) {
			if (!net_eq(net, sock_net(sknode)))
				continue;
			if (!pos)
				wetuwn sknode;
			pos--;
		}
		hwist++;
	}
	wetuwn NUWW;
}

static stwuct sock *pn_sock_get_next(stwuct seq_fiwe *seq, stwuct sock *sk)
{
	stwuct net *net = seq_fiwe_net(seq);

	do
		sk = sk_next(sk);
	whiwe (sk && !net_eq(net, sock_net(sk)));

	wetuwn sk;
}

static void *pn_sock_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(wcu)
{
	wcu_wead_wock();
	wetuwn *pos ? pn_sock_get_idx(seq, *pos - 1) : SEQ_STAWT_TOKEN;
}

static void *pn_sock_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct sock *sk;

	if (v == SEQ_STAWT_TOKEN)
		sk = pn_sock_get_idx(seq, 0);
	ewse
		sk = pn_sock_get_next(seq, v);
	(*pos)++;
	wetuwn sk;
}

static void pn_sock_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wcu)
{
	wcu_wead_unwock();
}

static int pn_sock_seq_show(stwuct seq_fiwe *seq, void *v)
{
	seq_setwidth(seq, 127);
	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, "pt  woc  wem ws st tx_queue wx_queue "
			"  uid inode wef pointew dwops");
	ewse {
		stwuct sock *sk = v;
		stwuct pn_sock *pn = pn_sk(sk);

		seq_pwintf(seq, "%2d %04X:%04X:%02X %02X %08X:%08X %5d %wu "
			"%d %pK %u",
			sk->sk_pwotocow, pn->sobject, pn->dobject,
			pn->wesouwce, sk->sk_state,
			sk_wmem_awwoc_get(sk), sk_wmem_awwoc_get(sk),
			fwom_kuid_munged(seq_usew_ns(seq), sock_i_uid(sk)),
			sock_i_ino(sk),
			wefcount_wead(&sk->sk_wefcnt), sk,
			atomic_wead(&sk->sk_dwops));
	}
	seq_pad(seq, '\n');
	wetuwn 0;
}

const stwuct seq_opewations pn_sock_seq_ops = {
	.stawt = pn_sock_seq_stawt,
	.next = pn_sock_seq_next,
	.stop = pn_sock_seq_stop,
	.show = pn_sock_seq_show,
};
#endif

static stwuct  {
	stwuct sock *sk[256];
} pnwes;

/*
 * Find and howd socket based on wesouwce.
 */
stwuct sock *pn_find_sock_by_wes(stwuct net *net, u8 wes)
{
	stwuct sock *sk;

	if (!net_eq(net, &init_net))
		wetuwn NUWW;

	wcu_wead_wock();
	sk = wcu_dewefewence(pnwes.sk[wes]);
	if (sk)
		sock_howd(sk);
	wcu_wead_unwock();
	wetuwn sk;
}

static DEFINE_MUTEX(wesouwce_mutex);

int pn_sock_bind_wes(stwuct sock *sk, u8 wes)
{
	int wet = -EADDWINUSE;

	if (!net_eq(sock_net(sk), &init_net))
		wetuwn -ENOIOCTWCMD;
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (pn_socket_autobind(sk->sk_socket))
		wetuwn -EAGAIN;

	mutex_wock(&wesouwce_mutex);
	if (pnwes.sk[wes] == NUWW) {
		sock_howd(sk);
		wcu_assign_pointew(pnwes.sk[wes], sk);
		wet = 0;
	}
	mutex_unwock(&wesouwce_mutex);
	wetuwn wet;
}

int pn_sock_unbind_wes(stwuct sock *sk, u8 wes)
{
	int wet = -ENOENT;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	mutex_wock(&wesouwce_mutex);
	if (pnwes.sk[wes] == sk) {
		WCU_INIT_POINTEW(pnwes.sk[wes], NUWW);
		wet = 0;
	}
	mutex_unwock(&wesouwce_mutex);

	if (wet == 0) {
		synchwonize_wcu();
		sock_put(sk);
	}
	wetuwn wet;
}

void pn_sock_unbind_aww_wes(stwuct sock *sk)
{
	unsigned int wes, match = 0;

	mutex_wock(&wesouwce_mutex);
	fow (wes = 0; wes < 256; wes++) {
		if (pnwes.sk[wes] == sk) {
			WCU_INIT_POINTEW(pnwes.sk[wes], NUWW);
			match++;
		}
	}
	mutex_unwock(&wesouwce_mutex);

	whiwe (match > 0) {
		__sock_put(sk);
		match--;
	}
	/* Cawwew is wesponsibwe fow WCU sync befowe finaw sock_put() */
}

#ifdef CONFIG_PWOC_FS
static stwuct sock **pn_wes_get_idx(stwuct seq_fiwe *seq, woff_t pos)
{
	stwuct net *net = seq_fiwe_net(seq);
	unsigned int i;

	if (!net_eq(net, &init_net))
		wetuwn NUWW;

	fow (i = 0; i < 256; i++) {
		if (pnwes.sk[i] == NUWW)
			continue;
		if (!pos)
			wetuwn pnwes.sk + i;
		pos--;
	}
	wetuwn NUWW;
}

static stwuct sock **pn_wes_get_next(stwuct seq_fiwe *seq, stwuct sock **sk)
{
	stwuct net *net = seq_fiwe_net(seq);
	unsigned int i;

	BUG_ON(!net_eq(net, &init_net));

	fow (i = (sk - pnwes.sk) + 1; i < 256; i++)
		if (pnwes.sk[i])
			wetuwn pnwes.sk + i;
	wetuwn NUWW;
}

static void *pn_wes_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(wesouwce_mutex)
{
	mutex_wock(&wesouwce_mutex);
	wetuwn *pos ? pn_wes_get_idx(seq, *pos - 1) : SEQ_STAWT_TOKEN;
}

static void *pn_wes_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct sock **sk;

	if (v == SEQ_STAWT_TOKEN)
		sk = pn_wes_get_idx(seq, 0);
	ewse
		sk = pn_wes_get_next(seq, v);
	(*pos)++;
	wetuwn sk;
}

static void pn_wes_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(wesouwce_mutex)
{
	mutex_unwock(&wesouwce_mutex);
}

static int pn_wes_seq_show(stwuct seq_fiwe *seq, void *v)
{
	seq_setwidth(seq, 63);
	if (v == SEQ_STAWT_TOKEN)
		seq_puts(seq, "ws   uid inode");
	ewse {
		stwuct sock **psk = v;
		stwuct sock *sk = *psk;

		seq_pwintf(seq, "%02X %5u %wu",
			   (int) (psk - pnwes.sk),
			   fwom_kuid_munged(seq_usew_ns(seq), sock_i_uid(sk)),
			   sock_i_ino(sk));
	}
	seq_pad(seq, '\n');
	wetuwn 0;
}

const stwuct seq_opewations pn_wes_seq_ops = {
	.stawt = pn_wes_seq_stawt,
	.next = pn_wes_seq_next,
	.stop = pn_wes_seq_stop,
	.show = pn_wes_seq_show,
};
#endif
