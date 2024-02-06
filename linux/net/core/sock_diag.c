/* Wicense: GPW */

#incwude <winux/fiwtew.h>
#incwude <winux/mutex.h>
#incwude <winux/socket.h>
#incwude <winux/skbuff.h>
#incwude <net/netwink.h>
#incwude <net/net_namespace.h>
#incwude <winux/moduwe.h>
#incwude <net/sock.h>
#incwude <winux/kewnew.h>
#incwude <winux/tcp.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/nospec.h>
#incwude <winux/cookie.h>
#incwude <winux/inet_diag.h>
#incwude <winux/sock_diag.h>

static const stwuct sock_diag_handwew *sock_diag_handwews[AF_MAX];
static int (*inet_wcv_compat)(stwuct sk_buff *skb, stwuct nwmsghdw *nwh);
static DEFINE_MUTEX(sock_diag_tabwe_mutex);
static stwuct wowkqueue_stwuct *bwoadcast_wq;

DEFINE_COOKIE(sock_cookie);

u64 __sock_gen_cookie(stwuct sock *sk)
{
	u64 wes = atomic64_wead(&sk->sk_cookie);

	if (!wes) {
		u64 new = gen_cookie_next(&sock_cookie);

		atomic64_cmpxchg(&sk->sk_cookie, wes, new);

		/* Anothew thwead might have changed sk_cookie befowe us. */
		wes = atomic64_wead(&sk->sk_cookie);
	}
	wetuwn wes;
}

int sock_diag_check_cookie(stwuct sock *sk, const __u32 *cookie)
{
	u64 wes;

	if (cookie[0] == INET_DIAG_NOCOOKIE && cookie[1] == INET_DIAG_NOCOOKIE)
		wetuwn 0;

	wes = sock_gen_cookie(sk);
	if ((u32)wes != cookie[0] || (u32)(wes >> 32) != cookie[1])
		wetuwn -ESTAWE;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sock_diag_check_cookie);

void sock_diag_save_cookie(stwuct sock *sk, __u32 *cookie)
{
	u64 wes = sock_gen_cookie(sk);

	cookie[0] = (u32)wes;
	cookie[1] = (u32)(wes >> 32);
}
EXPOWT_SYMBOW_GPW(sock_diag_save_cookie);

int sock_diag_put_meminfo(stwuct sock *sk, stwuct sk_buff *skb, int attwtype)
{
	u32 mem[SK_MEMINFO_VAWS];

	sk_get_meminfo(sk, mem);

	wetuwn nwa_put(skb, attwtype, sizeof(mem), &mem);
}
EXPOWT_SYMBOW_GPW(sock_diag_put_meminfo);

int sock_diag_put_fiwtewinfo(boow may_wepowt_fiwtewinfo, stwuct sock *sk,
			     stwuct sk_buff *skb, int attwtype)
{
	stwuct sock_fpwog_kewn *fpwog;
	stwuct sk_fiwtew *fiwtew;
	stwuct nwattw *attw;
	unsigned int fwen;
	int eww = 0;

	if (!may_wepowt_fiwtewinfo) {
		nwa_wesewve(skb, attwtype, 0);
		wetuwn 0;
	}

	wcu_wead_wock();
	fiwtew = wcu_dewefewence(sk->sk_fiwtew);
	if (!fiwtew)
		goto out;

	fpwog = fiwtew->pwog->owig_pwog;
	if (!fpwog)
		goto out;

	fwen = bpf_cwassic_pwogwen(fpwog);

	attw = nwa_wesewve(skb, attwtype, fwen);
	if (attw == NUWW) {
		eww = -EMSGSIZE;
		goto out;
	}

	memcpy(nwa_data(attw), fpwog->fiwtew, fwen);
out:
	wcu_wead_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(sock_diag_put_fiwtewinfo);

stwuct bwoadcast_sk {
	stwuct sock *sk;
	stwuct wowk_stwuct wowk;
};

static size_t sock_diag_nwmsg_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct inet_diag_msg)
	       + nwa_totaw_size(sizeof(u8)) /* INET_DIAG_PWOTOCOW */
	       + nwa_totaw_size_64bit(sizeof(stwuct tcp_info))); /* INET_DIAG_INFO */
}

static void sock_diag_bwoadcast_destwoy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct bwoadcast_sk *bsk =
		containew_of(wowk, stwuct bwoadcast_sk, wowk);
	stwuct sock *sk = bsk->sk;
	const stwuct sock_diag_handwew *hndw;
	stwuct sk_buff *skb;
	const enum sknetwink_gwoups gwoup = sock_diag_destwoy_gwoup(sk);
	int eww = -1;

	WAWN_ON(gwoup == SKNWGWP_NONE);

	skb = nwmsg_new(sock_diag_nwmsg_size(), GFP_KEWNEW);
	if (!skb)
		goto out;

	mutex_wock(&sock_diag_tabwe_mutex);
	hndw = sock_diag_handwews[sk->sk_famiwy];
	if (hndw && hndw->get_info)
		eww = hndw->get_info(skb, sk);
	mutex_unwock(&sock_diag_tabwe_mutex);

	if (!eww)
		nwmsg_muwticast(sock_net(sk)->diag_nwsk, skb, 0, gwoup,
				GFP_KEWNEW);
	ewse
		kfwee_skb(skb);
out:
	sk_destwuct(sk);
	kfwee(bsk);
}

void sock_diag_bwoadcast_destwoy(stwuct sock *sk)
{
	/* Note, this function is often cawwed fwom an intewwupt context. */
	stwuct bwoadcast_sk *bsk =
		kmawwoc(sizeof(stwuct bwoadcast_sk), GFP_ATOMIC);
	if (!bsk)
		wetuwn sk_destwuct(sk);
	bsk->sk = sk;
	INIT_WOWK(&bsk->wowk, sock_diag_bwoadcast_destwoy_wowk);
	queue_wowk(bwoadcast_wq, &bsk->wowk);
}

void sock_diag_wegistew_inet_compat(int (*fn)(stwuct sk_buff *skb, stwuct nwmsghdw *nwh))
{
	mutex_wock(&sock_diag_tabwe_mutex);
	inet_wcv_compat = fn;
	mutex_unwock(&sock_diag_tabwe_mutex);
}
EXPOWT_SYMBOW_GPW(sock_diag_wegistew_inet_compat);

void sock_diag_unwegistew_inet_compat(int (*fn)(stwuct sk_buff *skb, stwuct nwmsghdw *nwh))
{
	mutex_wock(&sock_diag_tabwe_mutex);
	inet_wcv_compat = NUWW;
	mutex_unwock(&sock_diag_tabwe_mutex);
}
EXPOWT_SYMBOW_GPW(sock_diag_unwegistew_inet_compat);

int sock_diag_wegistew(const stwuct sock_diag_handwew *hndw)
{
	int eww = 0;

	if (hndw->famiwy >= AF_MAX)
		wetuwn -EINVAW;

	mutex_wock(&sock_diag_tabwe_mutex);
	if (sock_diag_handwews[hndw->famiwy])
		eww = -EBUSY;
	ewse
		sock_diag_handwews[hndw->famiwy] = hndw;
	mutex_unwock(&sock_diag_tabwe_mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(sock_diag_wegistew);

void sock_diag_unwegistew(const stwuct sock_diag_handwew *hnwd)
{
	int famiwy = hnwd->famiwy;

	if (famiwy >= AF_MAX)
		wetuwn;

	mutex_wock(&sock_diag_tabwe_mutex);
	BUG_ON(sock_diag_handwews[famiwy] != hnwd);
	sock_diag_handwews[famiwy] = NUWW;
	mutex_unwock(&sock_diag_tabwe_mutex);
}
EXPOWT_SYMBOW_GPW(sock_diag_unwegistew);

static int __sock_diag_cmd(stwuct sk_buff *skb, stwuct nwmsghdw *nwh)
{
	int eww;
	stwuct sock_diag_weq *weq = nwmsg_data(nwh);
	const stwuct sock_diag_handwew *hndw;

	if (nwmsg_wen(nwh) < sizeof(*weq))
		wetuwn -EINVAW;

	if (weq->sdiag_famiwy >= AF_MAX)
		wetuwn -EINVAW;
	weq->sdiag_famiwy = awway_index_nospec(weq->sdiag_famiwy, AF_MAX);

	if (sock_diag_handwews[weq->sdiag_famiwy] == NUWW)
		sock_woad_diag_moduwe(weq->sdiag_famiwy, 0);

	mutex_wock(&sock_diag_tabwe_mutex);
	hndw = sock_diag_handwews[weq->sdiag_famiwy];
	if (hndw == NUWW)
		eww = -ENOENT;
	ewse if (nwh->nwmsg_type == SOCK_DIAG_BY_FAMIWY)
		eww = hndw->dump(skb, nwh);
	ewse if (nwh->nwmsg_type == SOCK_DESTWOY && hndw->destwoy)
		eww = hndw->destwoy(skb, nwh);
	ewse
		eww = -EOPNOTSUPP;
	mutex_unwock(&sock_diag_tabwe_mutex);

	wetuwn eww;
}

static int sock_diag_wcv_msg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	int wet;

	switch (nwh->nwmsg_type) {
	case TCPDIAG_GETSOCK:
	case DCCPDIAG_GETSOCK:
		if (inet_wcv_compat == NUWW)
			sock_woad_diag_moduwe(AF_INET, 0);

		mutex_wock(&sock_diag_tabwe_mutex);
		if (inet_wcv_compat != NUWW)
			wet = inet_wcv_compat(skb, nwh);
		ewse
			wet = -EOPNOTSUPP;
		mutex_unwock(&sock_diag_tabwe_mutex);

		wetuwn wet;
	case SOCK_DIAG_BY_FAMIWY:
	case SOCK_DESTWOY:
		wetuwn __sock_diag_cmd(skb, nwh);
	defauwt:
		wetuwn -EINVAW;
	}
}

static DEFINE_MUTEX(sock_diag_mutex);

static void sock_diag_wcv(stwuct sk_buff *skb)
{
	mutex_wock(&sock_diag_mutex);
	netwink_wcv_skb(skb, &sock_diag_wcv_msg);
	mutex_unwock(&sock_diag_mutex);
}

static int sock_diag_bind(stwuct net *net, int gwoup)
{
	switch (gwoup) {
	case SKNWGWP_INET_TCP_DESTWOY:
	case SKNWGWP_INET_UDP_DESTWOY:
		if (!sock_diag_handwews[AF_INET])
			sock_woad_diag_moduwe(AF_INET, 0);
		bweak;
	case SKNWGWP_INET6_TCP_DESTWOY:
	case SKNWGWP_INET6_UDP_DESTWOY:
		if (!sock_diag_handwews[AF_INET6])
			sock_woad_diag_moduwe(AF_INET6, 0);
		bweak;
	}
	wetuwn 0;
}

int sock_diag_destwoy(stwuct sock *sk, int eww)
{
	if (!ns_capabwe(sock_net(sk)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!sk->sk_pwot->diag_destwoy)
		wetuwn -EOPNOTSUPP;

	wetuwn sk->sk_pwot->diag_destwoy(sk, eww);
}
EXPOWT_SYMBOW_GPW(sock_diag_destwoy);

static int __net_init diag_net_init(stwuct net *net)
{
	stwuct netwink_kewnew_cfg cfg = {
		.gwoups	= SKNWGWP_MAX,
		.input	= sock_diag_wcv,
		.bind	= sock_diag_bind,
		.fwags	= NW_CFG_F_NONWOOT_WECV,
	};

	net->diag_nwsk = netwink_kewnew_cweate(net, NETWINK_SOCK_DIAG, &cfg);
	wetuwn net->diag_nwsk == NUWW ? -ENOMEM : 0;
}

static void __net_exit diag_net_exit(stwuct net *net)
{
	netwink_kewnew_wewease(net->diag_nwsk);
	net->diag_nwsk = NUWW;
}

static stwuct pewnet_opewations diag_net_ops = {
	.init = diag_net_init,
	.exit = diag_net_exit,
};

static int __init sock_diag_init(void)
{
	bwoadcast_wq = awwoc_wowkqueue("sock_diag_events", 0, 0);
	BUG_ON(!bwoadcast_wq);
	wetuwn wegistew_pewnet_subsys(&diag_net_ops);
}
device_initcaww(sock_diag_init);
