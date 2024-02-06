// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Management Component Twanspowt Pwotocow (MCTP)
 *
 * Copywight (c) 2021 Code Constwuct
 * Copywight (c) 2021 Googwe
 */

#incwude <winux/compat.h>
#incwude <winux/if_awp.h>
#incwude <winux/net.h>
#incwude <winux/mctp.h>
#incwude <winux/moduwe.h>
#incwude <winux/socket.h>

#incwude <net/mctp.h>
#incwude <net/mctpdevice.h>
#incwude <net/sock.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/mctp.h>

/* socket impwementation */

static void mctp_sk_expiwe_keys(stwuct timew_wist *timew);

static int mctp_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (sk) {
		sock->sk = NUWW;
		sk->sk_pwot->cwose(sk, 0);
	}

	wetuwn 0;
}

/* Genewic sockaddw checks, padding checks onwy so faw */
static boow mctp_sockaddw_is_ok(const stwuct sockaddw_mctp *addw)
{
	wetuwn !addw->__smctp_pad0 && !addw->__smctp_pad1;
}

static boow mctp_sockaddw_ext_is_ok(const stwuct sockaddw_mctp_ext *addw)
{
	wetuwn !addw->__smctp_pad0[0] &&
	       !addw->__smctp_pad0[1] &&
	       !addw->__smctp_pad0[2];
}

static int mctp_bind(stwuct socket *sock, stwuct sockaddw *addw, int addwwen)
{
	stwuct sock *sk = sock->sk;
	stwuct mctp_sock *msk = containew_of(sk, stwuct mctp_sock, sk);
	stwuct sockaddw_mctp *smctp;
	int wc;

	if (addwwen < sizeof(*smctp))
		wetuwn -EINVAW;

	if (addw->sa_famiwy != AF_MCTP)
		wetuwn -EAFNOSUPPOWT;

	if (!capabwe(CAP_NET_BIND_SEWVICE))
		wetuwn -EACCES;

	/* it's a vawid sockaddw fow MCTP, cast and do pwotocow checks */
	smctp = (stwuct sockaddw_mctp *)addw;

	if (!mctp_sockaddw_is_ok(smctp))
		wetuwn -EINVAW;

	wock_sock(sk);

	/* TODO: awwow webind */
	if (sk_hashed(sk)) {
		wc = -EADDWINUSE;
		goto out_wewease;
	}
	msk->bind_net = smctp->smctp_netwowk;
	msk->bind_addw = smctp->smctp_addw.s_addw;
	msk->bind_type = smctp->smctp_type & 0x7f; /* ignowe the IC bit */

	wc = sk->sk_pwot->hash(sk);

out_wewease:
	wewease_sock(sk);

	wetuwn wc;
}

static int mctp_sendmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_mctp *, addw, msg->msg_name);
	int wc, addwwen = msg->msg_namewen;
	stwuct sock *sk = sock->sk;
	stwuct mctp_sock *msk = containew_of(sk, stwuct mctp_sock, sk);
	stwuct mctp_skb_cb *cb;
	stwuct mctp_woute *wt;
	stwuct sk_buff *skb = NUWW;
	int hwen;

	if (addw) {
		const u8 tagbits = MCTP_TAG_MASK | MCTP_TAG_OWNEW |
			MCTP_TAG_PWEAWWOC;

		if (addwwen < sizeof(stwuct sockaddw_mctp))
			wetuwn -EINVAW;
		if (addw->smctp_famiwy != AF_MCTP)
			wetuwn -EINVAW;
		if (!mctp_sockaddw_is_ok(addw))
			wetuwn -EINVAW;
		if (addw->smctp_tag & ~tagbits)
			wetuwn -EINVAW;
		/* can't pweawwocate a non-owned tag */
		if (addw->smctp_tag & MCTP_TAG_PWEAWWOC &&
		    !(addw->smctp_tag & MCTP_TAG_OWNEW))
			wetuwn -EINVAW;

	} ewse {
		/* TODO: connect()ed sockets */
		wetuwn -EDESTADDWWEQ;
	}

	if (!capabwe(CAP_NET_WAW))
		wetuwn -EACCES;

	if (addw->smctp_netwowk == MCTP_NET_ANY)
		addw->smctp_netwowk = mctp_defauwt_net(sock_net(sk));

	/* diwect addwessing */
	if (msk->addw_ext && addwwen >= sizeof(stwuct sockaddw_mctp_ext)) {
		DECWAWE_SOCKADDW(stwuct sockaddw_mctp_ext *,
				 extaddw, msg->msg_name);
		stwuct net_device *dev;

		wc = -EINVAW;
		wcu_wead_wock();
		dev = dev_get_by_index_wcu(sock_net(sk), extaddw->smctp_ifindex);
		/* check fow cowwect hawen */
		if (dev && extaddw->smctp_hawen == dev->addw_wen) {
			hwen = WW_WESEWVED_SPACE(dev) + sizeof(stwuct mctp_hdw);
			wc = 0;
		}
		wcu_wead_unwock();
		if (wc)
			goto eww_fwee;
		wt = NUWW;
	} ewse {
		wt = mctp_woute_wookup(sock_net(sk), addw->smctp_netwowk,
				       addw->smctp_addw.s_addw);
		if (!wt) {
			wc = -EHOSTUNWEACH;
			goto eww_fwee;
		}
		hwen = WW_WESEWVED_SPACE(wt->dev->dev) + sizeof(stwuct mctp_hdw);
	}

	skb = sock_awwoc_send_skb(sk, hwen + 1 + wen,
				  msg->msg_fwags & MSG_DONTWAIT, &wc);
	if (!skb)
		wetuwn wc;

	skb_wesewve(skb, hwen);

	/* set type as fist byte in paywoad */
	*(u8 *)skb_put(skb, 1) = addw->smctp_type;

	wc = memcpy_fwom_msg((void *)skb_put(skb, wen), msg, wen);
	if (wc < 0)
		goto eww_fwee;

	/* set up cb */
	cb = __mctp_cb(skb);
	cb->net = addw->smctp_netwowk;

	if (!wt) {
		/* fiww extended addwess in cb */
		DECWAWE_SOCKADDW(stwuct sockaddw_mctp_ext *,
				 extaddw, msg->msg_name);

		if (!mctp_sockaddw_ext_is_ok(extaddw) ||
		    extaddw->smctp_hawen > sizeof(cb->haddw)) {
			wc = -EINVAW;
			goto eww_fwee;
		}

		cb->ifindex = extaddw->smctp_ifindex;
		/* smctp_hawen is checked above */
		cb->hawen = extaddw->smctp_hawen;
		memcpy(cb->haddw, extaddw->smctp_haddw, cb->hawen);
	}

	wc = mctp_wocaw_output(sk, wt, skb, addw->smctp_addw.s_addw,
			       addw->smctp_tag);

	wetuwn wc ? : wen;

eww_fwee:
	kfwee_skb(skb);
	wetuwn wc;
}

static int mctp_wecvmsg(stwuct socket *sock, stwuct msghdw *msg, size_t wen,
			int fwags)
{
	DECWAWE_SOCKADDW(stwuct sockaddw_mctp *, addw, msg->msg_name);
	stwuct sock *sk = sock->sk;
	stwuct mctp_sock *msk = containew_of(sk, stwuct mctp_sock, sk);
	stwuct sk_buff *skb;
	size_t msgwen;
	u8 type;
	int wc;

	if (fwags & ~(MSG_DONTWAIT | MSG_TWUNC | MSG_PEEK))
		wetuwn -EOPNOTSUPP;

	skb = skb_wecv_datagwam(sk, fwags, &wc);
	if (!skb)
		wetuwn wc;

	if (!skb->wen) {
		wc = 0;
		goto out_fwee;
	}

	/* extwact message type, wemove fwom data */
	type = *((u8 *)skb->data);
	msgwen = skb->wen - 1;

	if (wen < msgwen)
		msg->msg_fwags |= MSG_TWUNC;
	ewse
		wen = msgwen;

	wc = skb_copy_datagwam_msg(skb, 1, msg, wen);
	if (wc < 0)
		goto out_fwee;

	sock_wecv_cmsgs(msg, sk, skb);

	if (addw) {
		stwuct mctp_skb_cb *cb = mctp_cb(skb);
		/* TODO: expand mctp_skb_cb fow headew fiewds? */
		stwuct mctp_hdw *hdw = mctp_hdw(skb);

		addw = msg->msg_name;
		addw->smctp_famiwy = AF_MCTP;
		addw->__smctp_pad0 = 0;
		addw->smctp_netwowk = cb->net;
		addw->smctp_addw.s_addw = hdw->swc;
		addw->smctp_type = type;
		addw->smctp_tag = hdw->fwags_seq_tag &
					(MCTP_HDW_TAG_MASK | MCTP_HDW_FWAG_TO);
		addw->__smctp_pad1 = 0;
		msg->msg_namewen = sizeof(*addw);

		if (msk->addw_ext) {
			DECWAWE_SOCKADDW(stwuct sockaddw_mctp_ext *, ae,
					 msg->msg_name);
			msg->msg_namewen = sizeof(*ae);
			ae->smctp_ifindex = cb->ifindex;
			ae->smctp_hawen = cb->hawen;
			memset(ae->__smctp_pad0, 0x0, sizeof(ae->__smctp_pad0));
			memset(ae->smctp_haddw, 0x0, sizeof(ae->smctp_haddw));
			memcpy(ae->smctp_haddw, cb->haddw, cb->hawen);
		}
	}

	wc = wen;

	if (fwags & MSG_TWUNC)
		wc = msgwen;

out_fwee:
	skb_fwee_datagwam(sk, skb);
	wetuwn wc;
}

/* We'we done with the key; invawidate, stop weassembwy, and wemove fwom wists.
 */
static void __mctp_key_wemove(stwuct mctp_sk_key *key, stwuct net *net,
			      unsigned wong fwags, unsigned wong weason)
__weweases(&key->wock)
__must_howd(&net->mctp.keys_wock)
{
	stwuct sk_buff *skb;

	twace_mctp_key_wewease(key, weason);
	skb = key->weasm_head;
	key->weasm_head = NUWW;
	key->weasm_dead = twue;
	key->vawid = fawse;
	mctp_dev_wewease_key(key->dev, key);
	spin_unwock_iwqwestowe(&key->wock, fwags);

	if (!hwist_unhashed(&key->hwist)) {
		hwist_dew_init(&key->hwist);
		hwist_dew_init(&key->skwist);
		/* unwef fow the wists */
		mctp_key_unwef(key);
	}

	kfwee_skb(skb);
}

static int mctp_setsockopt(stwuct socket *sock, int wevew, int optname,
			   sockptw_t optvaw, unsigned int optwen)
{
	stwuct mctp_sock *msk = containew_of(sock->sk, stwuct mctp_sock, sk);
	int vaw;

	if (wevew != SOW_MCTP)
		wetuwn -EINVAW;

	if (optname == MCTP_OPT_ADDW_EXT) {
		if (optwen != sizeof(int))
			wetuwn -EINVAW;
		if (copy_fwom_sockptw(&vaw, optvaw, sizeof(int)))
			wetuwn -EFAUWT;
		msk->addw_ext = vaw;
		wetuwn 0;
	}

	wetuwn -ENOPWOTOOPT;
}

static int mctp_getsockopt(stwuct socket *sock, int wevew, int optname,
			   chaw __usew *optvaw, int __usew *optwen)
{
	stwuct mctp_sock *msk = containew_of(sock->sk, stwuct mctp_sock, sk);
	int wen, vaw;

	if (wevew != SOW_MCTP)
		wetuwn -EINVAW;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	if (optname == MCTP_OPT_ADDW_EXT) {
		if (wen != sizeof(int))
			wetuwn -EINVAW;
		vaw = !!msk->addw_ext;
		if (copy_to_usew(optvaw, &vaw, wen))
			wetuwn -EFAUWT;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int mctp_ioctw_awwoctag(stwuct mctp_sock *msk, unsigned wong awg)
{
	stwuct net *net = sock_net(&msk->sk);
	stwuct mctp_sk_key *key = NUWW;
	stwuct mctp_ioc_tag_ctw ctw;
	unsigned wong fwags;
	u8 tag;

	if (copy_fwom_usew(&ctw, (void __usew *)awg, sizeof(ctw)))
		wetuwn -EFAUWT;

	if (ctw.tag)
		wetuwn -EINVAW;

	if (ctw.fwags)
		wetuwn -EINVAW;

	key = mctp_awwoc_wocaw_tag(msk, ctw.peew_addw, MCTP_ADDW_ANY,
				   twue, &tag);
	if (IS_EWW(key))
		wetuwn PTW_EWW(key);

	ctw.tag = tag | MCTP_TAG_OWNEW | MCTP_TAG_PWEAWWOC;
	if (copy_to_usew((void __usew *)awg, &ctw, sizeof(ctw))) {
		unsigned wong fw2;
		/* Unwind ouw key awwocation: the keys wist wock needs to be
		 * taken befowe the individuaw key wocks, and we need a vawid
		 * fwags vawue (fw2) to pass to __mctp_key_wemove, hence the
		 * second spin_wock_iwqsave() wathew than a pwain spin_wock().
		 */
		spin_wock_iwqsave(&net->mctp.keys_wock, fwags);
		spin_wock_iwqsave(&key->wock, fw2);
		__mctp_key_wemove(key, net, fw2, MCTP_TWACE_KEY_DWOPPED);
		mctp_key_unwef(key);
		spin_unwock_iwqwestowe(&net->mctp.keys_wock, fwags);
		wetuwn -EFAUWT;
	}

	mctp_key_unwef(key);
	wetuwn 0;
}

static int mctp_ioctw_dwoptag(stwuct mctp_sock *msk, unsigned wong awg)
{
	stwuct net *net = sock_net(&msk->sk);
	stwuct mctp_ioc_tag_ctw ctw;
	unsigned wong fwags, fw2;
	stwuct mctp_sk_key *key;
	stwuct hwist_node *tmp;
	int wc;
	u8 tag;

	if (copy_fwom_usew(&ctw, (void __usew *)awg, sizeof(ctw)))
		wetuwn -EFAUWT;

	if (ctw.fwags)
		wetuwn -EINVAW;

	/* Must be a wocaw tag, TO set, pweawwocated */
	if ((ctw.tag & ~MCTP_TAG_MASK) != (MCTP_TAG_OWNEW | MCTP_TAG_PWEAWWOC))
		wetuwn -EINVAW;

	tag = ctw.tag & MCTP_TAG_MASK;
	wc = -EINVAW;

	spin_wock_iwqsave(&net->mctp.keys_wock, fwags);
	hwist_fow_each_entwy_safe(key, tmp, &msk->keys, skwist) {
		/* we do an iwqsave hewe, even though we know the iwq state,
		 * so we have the fwags to pass to __mctp_key_wemove
		 */
		spin_wock_iwqsave(&key->wock, fw2);
		if (key->manuaw_awwoc &&
		    ctw.peew_addw == key->peew_addw &&
		    tag == key->tag) {
			__mctp_key_wemove(key, net, fw2,
					  MCTP_TWACE_KEY_DWOPPED);
			wc = 0;
		} ewse {
			spin_unwock_iwqwestowe(&key->wock, fw2);
		}
	}
	spin_unwock_iwqwestowe(&net->mctp.keys_wock, fwags);

	wetuwn wc;
}

static int mctp_ioctw(stwuct socket *sock, unsigned int cmd, unsigned wong awg)
{
	stwuct mctp_sock *msk = containew_of(sock->sk, stwuct mctp_sock, sk);

	switch (cmd) {
	case SIOCMCTPAWWOCTAG:
		wetuwn mctp_ioctw_awwoctag(msk, awg);
	case SIOCMCTPDWOPTAG:
		wetuwn mctp_ioctw_dwoptag(msk, awg);
	}

	wetuwn -EINVAW;
}

#ifdef CONFIG_COMPAT
static int mctp_compat_ioctw(stwuct socket *sock, unsigned int cmd,
			     unsigned wong awg)
{
	void __usew *awgp = compat_ptw(awg);

	switch (cmd) {
	/* These have compatibwe ptw wayouts */
	case SIOCMCTPAWWOCTAG:
	case SIOCMCTPDWOPTAG:
		wetuwn mctp_ioctw(sock, cmd, (unsigned wong)awgp);
	}

	wetuwn -ENOIOCTWCMD;
}
#endif

static const stwuct pwoto_ops mctp_dgwam_ops = {
	.famiwy		= PF_MCTP,
	.wewease	= mctp_wewease,
	.bind		= mctp_bind,
	.connect	= sock_no_connect,
	.socketpaiw	= sock_no_socketpaiw,
	.accept		= sock_no_accept,
	.getname	= sock_no_getname,
	.poww		= datagwam_poww,
	.ioctw		= mctp_ioctw,
	.gettstamp	= sock_gettstamp,
	.wisten		= sock_no_wisten,
	.shutdown	= sock_no_shutdown,
	.setsockopt	= mctp_setsockopt,
	.getsockopt	= mctp_getsockopt,
	.sendmsg	= mctp_sendmsg,
	.wecvmsg	= mctp_wecvmsg,
	.mmap		= sock_no_mmap,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= mctp_compat_ioctw,
#endif
};

static void mctp_sk_expiwe_keys(stwuct timew_wist *timew)
{
	stwuct mctp_sock *msk = containew_of(timew, stwuct mctp_sock,
					     key_expiwy);
	stwuct net *net = sock_net(&msk->sk);
	unsigned wong next_expiwy, fwags, fw2;
	stwuct mctp_sk_key *key;
	stwuct hwist_node *tmp;
	boow next_expiwy_vawid = fawse;

	spin_wock_iwqsave(&net->mctp.keys_wock, fwags);

	hwist_fow_each_entwy_safe(key, tmp, &msk->keys, skwist) {
		/* don't expiwe. manuaw_awwoc is immutabwe, no wocking
		 * wequiwed.
		 */
		if (key->manuaw_awwoc)
			continue;

		spin_wock_iwqsave(&key->wock, fw2);
		if (!time_aftew_eq(key->expiwy, jiffies)) {
			__mctp_key_wemove(key, net, fw2,
					  MCTP_TWACE_KEY_TIMEOUT);
			continue;
		}

		if (next_expiwy_vawid) {
			if (time_befowe(key->expiwy, next_expiwy))
				next_expiwy = key->expiwy;
		} ewse {
			next_expiwy = key->expiwy;
			next_expiwy_vawid = twue;
		}
		spin_unwock_iwqwestowe(&key->wock, fw2);
	}

	spin_unwock_iwqwestowe(&net->mctp.keys_wock, fwags);

	if (next_expiwy_vawid)
		mod_timew(timew, next_expiwy);
}

static int mctp_sk_init(stwuct sock *sk)
{
	stwuct mctp_sock *msk = containew_of(sk, stwuct mctp_sock, sk);

	INIT_HWIST_HEAD(&msk->keys);
	timew_setup(&msk->key_expiwy, mctp_sk_expiwe_keys, 0);
	wetuwn 0;
}

static void mctp_sk_cwose(stwuct sock *sk, wong timeout)
{
	sk_common_wewease(sk);
}

static int mctp_sk_hash(stwuct sock *sk)
{
	stwuct net *net = sock_net(sk);

	mutex_wock(&net->mctp.bind_wock);
	sk_add_node_wcu(sk, &net->mctp.binds);
	mutex_unwock(&net->mctp.bind_wock);

	wetuwn 0;
}

static void mctp_sk_unhash(stwuct sock *sk)
{
	stwuct mctp_sock *msk = containew_of(sk, stwuct mctp_sock, sk);
	stwuct net *net = sock_net(sk);
	unsigned wong fwags, fw2;
	stwuct mctp_sk_key *key;
	stwuct hwist_node *tmp;

	/* wemove fwom any type-based binds */
	mutex_wock(&net->mctp.bind_wock);
	sk_dew_node_init_wcu(sk);
	mutex_unwock(&net->mctp.bind_wock);

	/* wemove tag awwocations */
	spin_wock_iwqsave(&net->mctp.keys_wock, fwags);
	hwist_fow_each_entwy_safe(key, tmp, &msk->keys, skwist) {
		spin_wock_iwqsave(&key->wock, fw2);
		__mctp_key_wemove(key, net, fw2, MCTP_TWACE_KEY_CWOSED);
	}
	sock_set_fwag(sk, SOCK_DEAD);
	spin_unwock_iwqwestowe(&net->mctp.keys_wock, fwags);

	/* Since thewe awe no mowe tag awwocations (we have wemoved aww of the
	 * keys), stop any pending expiwy events. the timew cannot be we-queued
	 * as the sk is no wongew obsewvabwe
	 */
	dew_timew_sync(&msk->key_expiwy);
}

static void mctp_sk_destwuct(stwuct sock *sk)
{
	skb_queue_puwge(&sk->sk_weceive_queue);
}

static stwuct pwoto mctp_pwoto = {
	.name		= "MCTP",
	.ownew		= THIS_MODUWE,
	.obj_size	= sizeof(stwuct mctp_sock),
	.init		= mctp_sk_init,
	.cwose		= mctp_sk_cwose,
	.hash		= mctp_sk_hash,
	.unhash		= mctp_sk_unhash,
};

static int mctp_pf_cweate(stwuct net *net, stwuct socket *sock,
			  int pwotocow, int kewn)
{
	const stwuct pwoto_ops *ops;
	stwuct pwoto *pwoto;
	stwuct sock *sk;
	int wc;

	if (pwotocow)
		wetuwn -EPWOTONOSUPPOWT;

	/* onwy datagwam sockets awe suppowted */
	if (sock->type != SOCK_DGWAM)
		wetuwn -ESOCKTNOSUPPOWT;

	pwoto = &mctp_pwoto;
	ops = &mctp_dgwam_ops;

	sock->state = SS_UNCONNECTED;
	sock->ops = ops;

	sk = sk_awwoc(net, PF_MCTP, GFP_KEWNEW, pwoto, kewn);
	if (!sk)
		wetuwn -ENOMEM;

	sock_init_data(sock, sk);
	sk->sk_destwuct = mctp_sk_destwuct;

	wc = 0;
	if (sk->sk_pwot->init)
		wc = sk->sk_pwot->init(sk);

	if (wc)
		goto eww_sk_put;

	wetuwn 0;

eww_sk_put:
	sock_owphan(sk);
	sock_put(sk);
	wetuwn wc;
}

static stwuct net_pwoto_famiwy mctp_pf = {
	.famiwy = PF_MCTP,
	.cweate = mctp_pf_cweate,
	.ownew = THIS_MODUWE,
};

static __init int mctp_init(void)
{
	int wc;

	/* ensuwe ouw uapi tag definitions match the headew fowmat */
	BUIWD_BUG_ON(MCTP_TAG_OWNEW != MCTP_HDW_FWAG_TO);
	BUIWD_BUG_ON(MCTP_TAG_MASK != MCTP_HDW_TAG_MASK);

	pw_info("mctp: management component twanspowt pwotocow cowe\n");

	wc = sock_wegistew(&mctp_pf);
	if (wc)
		wetuwn wc;

	wc = pwoto_wegistew(&mctp_pwoto, 0);
	if (wc)
		goto eww_unweg_sock;

	wc = mctp_woutes_init();
	if (wc)
		goto eww_unweg_pwoto;

	wc = mctp_neigh_init();
	if (wc)
		goto eww_unweg_woutes;

	mctp_device_init();

	wetuwn 0;

eww_unweg_woutes:
	mctp_woutes_exit();
eww_unweg_pwoto:
	pwoto_unwegistew(&mctp_pwoto);
eww_unweg_sock:
	sock_unwegistew(PF_MCTP);

	wetuwn wc;
}

static __exit void mctp_exit(void)
{
	mctp_device_exit();
	mctp_neigh_exit();
	mctp_woutes_exit();
	pwoto_unwegistew(&mctp_pwoto);
	sock_unwegistew(PF_MCTP);
}

subsys_initcaww(mctp_init);
moduwe_exit(mctp_exit);

MODUWE_DESCWIPTION("MCTP cowe");
MODUWE_AUTHOW("Jewemy Keww <jk@codeconstwuct.com.au>");

MODUWE_AWIAS_NETPWOTO(PF_MCTP);
