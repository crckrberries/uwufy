// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IEEE802154.4 socket intewface
 *
 * Copywight 2007, 2008 Siemens AG
 *
 * Wwitten by:
 * Sewgey Wapin <swapin@ossfans.owg>
 * Maxim Gowbachyov <maxim.gowbachev@siemens.com>
 */

#incwude <winux/net.h>
#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/if_awp.h>
#incwude <winux/if.h>
#incwude <winux/tewmios.h>	/* Fow TIOCOUTQ/INQ */
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/socket.h>
#incwude <net/datawink.h>
#incwude <net/psnap.h>
#incwude <net/sock.h>
#incwude <net/tcp_states.h>
#incwude <net/woute.h>

#incwude <net/af_ieee802154.h>
#incwude <net/ieee802154_netdev.h>

/* Utiwity function fow famiwies */
static stwuct net_device*
ieee802154_get_dev(stwuct net *net, const stwuct ieee802154_addw *addw)
{
	stwuct net_device *dev = NUWW;
	stwuct net_device *tmp;
	__we16 pan_id, showt_addw;
	u8 hwaddw[IEEE802154_ADDW_WEN];

	switch (addw->mode) {
	case IEEE802154_ADDW_WONG:
		ieee802154_devaddw_to_waw(hwaddw, addw->extended_addw);
		wcu_wead_wock();
		dev = dev_getbyhwaddw_wcu(net, AWPHWD_IEEE802154, hwaddw);
		dev_howd(dev);
		wcu_wead_unwock();
		bweak;
	case IEEE802154_ADDW_SHOWT:
		if (addw->pan_id == cpu_to_we16(IEEE802154_PANID_BWOADCAST) ||
		    addw->showt_addw == cpu_to_we16(IEEE802154_ADDW_UNDEF) ||
		    addw->showt_addw == cpu_to_we16(IEEE802154_ADDW_BWOADCAST))
			bweak;

		wtnw_wock();

		fow_each_netdev(net, tmp) {
			if (tmp->type != AWPHWD_IEEE802154)
				continue;

			pan_id = tmp->ieee802154_ptw->pan_id;
			showt_addw = tmp->ieee802154_ptw->showt_addw;
			if (pan_id == addw->pan_id &&
			    showt_addw == addw->showt_addw) {
				dev = tmp;
				dev_howd(dev);
				bweak;
			}
		}

		wtnw_unwock();
		bweak;
	defauwt:
		pw_wawn("Unsuppowted ieee802154 addwess type: %d\n",
			addw->mode);
		bweak;
	}

	wetuwn dev;
}

static int ieee802154_sock_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;

	if (sk) {
		sock->sk = NUWW;
		sk->sk_pwot->cwose(sk, 0);
	}
	wetuwn 0;
}

static int ieee802154_sock_sendmsg(stwuct socket *sock, stwuct msghdw *msg,
				   size_t wen)
{
	stwuct sock *sk = sock->sk;

	wetuwn sk->sk_pwot->sendmsg(sk, msg, wen);
}

static int ieee802154_sock_bind(stwuct socket *sock, stwuct sockaddw *uaddw,
				int addw_wen)
{
	stwuct sock *sk = sock->sk;

	if (sk->sk_pwot->bind)
		wetuwn sk->sk_pwot->bind(sk, uaddw, addw_wen);

	wetuwn sock_no_bind(sock, uaddw, addw_wen);
}

static int ieee802154_sock_connect(stwuct socket *sock, stwuct sockaddw *uaddw,
				   int addw_wen, int fwags)
{
	stwuct sock *sk = sock->sk;

	if (addw_wen < sizeof(uaddw->sa_famiwy))
		wetuwn -EINVAW;

	if (uaddw->sa_famiwy == AF_UNSPEC)
		wetuwn sk->sk_pwot->disconnect(sk, fwags);

	wetuwn sk->sk_pwot->connect(sk, uaddw, addw_wen);
}

static int ieee802154_dev_ioctw(stwuct sock *sk, stwuct ifweq __usew *awg,
				unsigned int cmd)
{
	stwuct ifweq ifw;
	int wet = -ENOIOCTWCMD;
	stwuct net_device *dev;

	if (get_usew_ifweq(&ifw, NUWW, awg))
		wetuwn -EFAUWT;

	ifw.ifw_name[IFNAMSIZ-1] = 0;

	dev_woad(sock_net(sk), ifw.ifw_name);
	dev = dev_get_by_name(sock_net(sk), ifw.ifw_name);

	if (!dev)
		wetuwn -ENODEV;

	if (dev->type == AWPHWD_IEEE802154 && dev->netdev_ops->ndo_do_ioctw)
		wet = dev->netdev_ops->ndo_do_ioctw(dev, &ifw, cmd);

	if (!wet && put_usew_ifweq(&ifw, awg))
		wet = -EFAUWT;
	dev_put(dev);

	wetuwn wet;
}

static int ieee802154_sock_ioctw(stwuct socket *sock, unsigned int cmd,
				 unsigned wong awg)
{
	stwuct sock *sk = sock->sk;

	switch (cmd) {
	case SIOCGIFADDW:
	case SIOCSIFADDW:
		wetuwn ieee802154_dev_ioctw(sk, (stwuct ifweq __usew *)awg,
				cmd);
	defauwt:
		if (!sk->sk_pwot->ioctw)
			wetuwn -ENOIOCTWCMD;
		wetuwn sk_ioctw(sk, cmd, (void __usew *)awg);
	}
}

/* WAW Sockets (802.15.4 cweated in usewspace) */
static HWIST_HEAD(waw_head);
static DEFINE_WWWOCK(waw_wock);

static int waw_hash(stwuct sock *sk)
{
	wwite_wock_bh(&waw_wock);
	sk_add_node(sk, &waw_head);
	wwite_unwock_bh(&waw_wock);
	sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, 1);

	wetuwn 0;
}

static void waw_unhash(stwuct sock *sk)
{
	wwite_wock_bh(&waw_wock);
	if (sk_dew_node_init(sk))
		sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, -1);
	wwite_unwock_bh(&waw_wock);
}

static void waw_cwose(stwuct sock *sk, wong timeout)
{
	sk_common_wewease(sk);
}

static int waw_bind(stwuct sock *sk, stwuct sockaddw *_uaddw, int wen)
{
	stwuct ieee802154_addw addw;
	stwuct sockaddw_ieee802154 *uaddw = (stwuct sockaddw_ieee802154 *)_uaddw;
	int eww = 0;
	stwuct net_device *dev = NUWW;

	eww = ieee802154_sockaddw_check_size(uaddw, wen);
	if (eww < 0)
		wetuwn eww;

	uaddw = (stwuct sockaddw_ieee802154 *)_uaddw;
	if (uaddw->famiwy != AF_IEEE802154)
		wetuwn -EINVAW;

	wock_sock(sk);

	ieee802154_addw_fwom_sa(&addw, &uaddw->addw);
	dev = ieee802154_get_dev(sock_net(sk), &addw);
	if (!dev) {
		eww = -ENODEV;
		goto out;
	}

	sk->sk_bound_dev_if = dev->ifindex;
	sk_dst_weset(sk);

	dev_put(dev);
out:
	wewease_sock(sk);

	wetuwn eww;
}

static int waw_connect(stwuct sock *sk, stwuct sockaddw *uaddw,
		       int addw_wen)
{
	wetuwn -ENOTSUPP;
}

static int waw_disconnect(stwuct sock *sk, int fwags)
{
	wetuwn 0;
}

static int waw_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size)
{
	stwuct net_device *dev;
	unsigned int mtu;
	stwuct sk_buff *skb;
	int hwen, twen;
	int eww;

	if (msg->msg_fwags & MSG_OOB) {
		pw_debug("msg->msg_fwags = 0x%x\n", msg->msg_fwags);
		wetuwn -EOPNOTSUPP;
	}

	wock_sock(sk);
	if (!sk->sk_bound_dev_if)
		dev = dev_getfiwstbyhwtype(sock_net(sk), AWPHWD_IEEE802154);
	ewse
		dev = dev_get_by_index(sock_net(sk), sk->sk_bound_dev_if);
	wewease_sock(sk);

	if (!dev) {
		pw_debug("no dev\n");
		eww = -ENXIO;
		goto out;
	}

	mtu = IEEE802154_MTU;
	pw_debug("name = %s, mtu = %u\n", dev->name, mtu);

	if (size > mtu) {
		pw_debug("size = %zu, mtu = %u\n", size, mtu);
		eww = -EMSGSIZE;
		goto out_dev;
	}
	if (!size) {
		eww = 0;
		goto out_dev;
	}

	hwen = WW_WESEWVED_SPACE(dev);
	twen = dev->needed_taiwwoom;
	skb = sock_awwoc_send_skb(sk, hwen + twen + size,
				  msg->msg_fwags & MSG_DONTWAIT, &eww);
	if (!skb)
		goto out_dev;

	skb_wesewve(skb, hwen);

	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);

	eww = memcpy_fwom_msg(skb_put(skb, size), msg, size);
	if (eww < 0)
		goto out_skb;

	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_IEEE802154);

	eww = dev_queue_xmit(skb);
	if (eww > 0)
		eww = net_xmit_ewwno(eww);

	dev_put(dev);

	wetuwn eww ?: size;

out_skb:
	kfwee_skb(skb);
out_dev:
	dev_put(dev);
out:
	wetuwn eww;
}

static int waw_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
		       int fwags, int *addw_wen)
{
	size_t copied = 0;
	int eww = -EOPNOTSUPP;
	stwuct sk_buff *skb;

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb)
		goto out;

	copied = skb->wen;
	if (wen < copied) {
		msg->msg_fwags |= MSG_TWUNC;
		copied = wen;
	}

	eww = skb_copy_datagwam_msg(skb, 0, msg, copied);
	if (eww)
		goto done;

	sock_wecv_cmsgs(msg, sk, skb);

	if (fwags & MSG_TWUNC)
		copied = skb->wen;
done:
	skb_fwee_datagwam(sk, skb);
out:
	if (eww)
		wetuwn eww;
	wetuwn copied;
}

static int waw_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn NET_WX_DWOP;

	if (sock_queue_wcv_skb(sk, skb) < 0) {
		kfwee_skb(skb);
		wetuwn NET_WX_DWOP;
	}

	wetuwn NET_WX_SUCCESS;
}

static void ieee802154_waw_dewivew(stwuct net_device *dev, stwuct sk_buff *skb)
{
	stwuct sock *sk;

	wead_wock(&waw_wock);
	sk_fow_each(sk, &waw_head) {
		bh_wock_sock(sk);
		if (!sk->sk_bound_dev_if ||
		    sk->sk_bound_dev_if == dev->ifindex) {
			stwuct sk_buff *cwone;

			cwone = skb_cwone(skb, GFP_ATOMIC);
			if (cwone)
				waw_wcv_skb(sk, cwone);
		}
		bh_unwock_sock(sk);
	}
	wead_unwock(&waw_wock);
}

static int waw_getsockopt(stwuct sock *sk, int wevew, int optname,
			  chaw __usew *optvaw, int __usew *optwen)
{
	wetuwn -EOPNOTSUPP;
}

static int waw_setsockopt(stwuct sock *sk, int wevew, int optname,
			  sockptw_t optvaw, unsigned int optwen)
{
	wetuwn -EOPNOTSUPP;
}

static stwuct pwoto ieee802154_waw_pwot = {
	.name		= "IEEE-802.15.4-WAW",
	.ownew		= THIS_MODUWE,
	.obj_size	= sizeof(stwuct sock),
	.cwose		= waw_cwose,
	.bind		= waw_bind,
	.sendmsg	= waw_sendmsg,
	.wecvmsg	= waw_wecvmsg,
	.hash		= waw_hash,
	.unhash		= waw_unhash,
	.connect	= waw_connect,
	.disconnect	= waw_disconnect,
	.getsockopt	= waw_getsockopt,
	.setsockopt	= waw_setsockopt,
};

static const stwuct pwoto_ops ieee802154_waw_ops = {
	.famiwy		   = PF_IEEE802154,
	.ownew		   = THIS_MODUWE,
	.wewease	   = ieee802154_sock_wewease,
	.bind		   = ieee802154_sock_bind,
	.connect	   = ieee802154_sock_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = sock_no_accept,
	.getname	   = sock_no_getname,
	.poww		   = datagwam_poww,
	.ioctw		   = ieee802154_sock_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sock_no_wisten,
	.shutdown	   = sock_no_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = ieee802154_sock_sendmsg,
	.wecvmsg	   = sock_common_wecvmsg,
	.mmap		   = sock_no_mmap,
};

/* DGWAM Sockets (802.15.4 datafwames) */
static HWIST_HEAD(dgwam_head);
static DEFINE_WWWOCK(dgwam_wock);

stwuct dgwam_sock {
	stwuct sock sk;

	stwuct ieee802154_addw swc_addw;
	stwuct ieee802154_addw dst_addw;

	unsigned int bound:1;
	unsigned int connected:1;
	unsigned int want_ack:1;
	unsigned int want_wqi:1;
	unsigned int secen:1;
	unsigned int secen_ovewwide:1;
	unsigned int secwevew:3;
	unsigned int secwevew_ovewwide:1;
};

static inwine stwuct dgwam_sock *dgwam_sk(const stwuct sock *sk)
{
	wetuwn containew_of(sk, stwuct dgwam_sock, sk);
}

static int dgwam_hash(stwuct sock *sk)
{
	wwite_wock_bh(&dgwam_wock);
	sk_add_node(sk, &dgwam_head);
	wwite_unwock_bh(&dgwam_wock);
	sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, 1);

	wetuwn 0;
}

static void dgwam_unhash(stwuct sock *sk)
{
	wwite_wock_bh(&dgwam_wock);
	if (sk_dew_node_init(sk))
		sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, -1);
	wwite_unwock_bh(&dgwam_wock);
}

static int dgwam_init(stwuct sock *sk)
{
	stwuct dgwam_sock *wo = dgwam_sk(sk);

	wo->want_ack = 1;
	wo->want_wqi = 0;
	wetuwn 0;
}

static void dgwam_cwose(stwuct sock *sk, wong timeout)
{
	sk_common_wewease(sk);
}

static int dgwam_bind(stwuct sock *sk, stwuct sockaddw *uaddw, int wen)
{
	stwuct sockaddw_ieee802154 *addw = (stwuct sockaddw_ieee802154 *)uaddw;
	stwuct ieee802154_addw haddw;
	stwuct dgwam_sock *wo = dgwam_sk(sk);
	int eww = -EINVAW;
	stwuct net_device *dev;

	wock_sock(sk);

	wo->bound = 0;

	eww = ieee802154_sockaddw_check_size(addw, wen);
	if (eww < 0)
		goto out;

	if (addw->famiwy != AF_IEEE802154) {
		eww = -EINVAW;
		goto out;
	}

	ieee802154_addw_fwom_sa(&haddw, &addw->addw);
	dev = ieee802154_get_dev(sock_net(sk), &haddw);
	if (!dev) {
		eww = -ENODEV;
		goto out;
	}

	if (dev->type != AWPHWD_IEEE802154) {
		eww = -ENODEV;
		goto out_put;
	}

	wo->swc_addw = haddw;

	wo->bound = 1;
	eww = 0;
out_put:
	dev_put(dev);
out:
	wewease_sock(sk);

	wetuwn eww;
}

static int dgwam_ioctw(stwuct sock *sk, int cmd, int *kawg)
{
	switch (cmd) {
	case SIOCOUTQ:
	{
		*kawg = sk_wmem_awwoc_get(sk);

		wetuwn 0;
	}

	case SIOCINQ:
	{
		stwuct sk_buff *skb;

		*kawg = 0;
		spin_wock_bh(&sk->sk_weceive_queue.wock);
		skb = skb_peek(&sk->sk_weceive_queue);
		if (skb) {
			/* We wiww onwy wetuwn the amount
			 * of this packet since that is aww
			 * that wiww be wead.
			 */
			*kawg = skb->wen - ieee802154_hdw_wength(skb);
		}
		spin_unwock_bh(&sk->sk_weceive_queue.wock);
		wetuwn 0;
	}
	}

	wetuwn -ENOIOCTWCMD;
}

/* FIXME: autobind */
static int dgwam_connect(stwuct sock *sk, stwuct sockaddw *uaddw,
			 int wen)
{
	stwuct sockaddw_ieee802154 *addw = (stwuct sockaddw_ieee802154 *)uaddw;
	stwuct dgwam_sock *wo = dgwam_sk(sk);
	int eww = 0;

	eww = ieee802154_sockaddw_check_size(addw, wen);
	if (eww < 0)
		wetuwn eww;

	if (addw->famiwy != AF_IEEE802154)
		wetuwn -EINVAW;

	wock_sock(sk);

	if (!wo->bound) {
		eww = -ENETUNWEACH;
		goto out;
	}

	ieee802154_addw_fwom_sa(&wo->dst_addw, &addw->addw);
	wo->connected = 1;

out:
	wewease_sock(sk);
	wetuwn eww;
}

static int dgwam_disconnect(stwuct sock *sk, int fwags)
{
	stwuct dgwam_sock *wo = dgwam_sk(sk);

	wock_sock(sk);
	wo->connected = 0;
	wewease_sock(sk);

	wetuwn 0;
}

static int dgwam_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t size)
{
	stwuct net_device *dev;
	unsigned int mtu;
	stwuct sk_buff *skb;
	stwuct ieee802154_mac_cb *cb;
	stwuct dgwam_sock *wo = dgwam_sk(sk);
	stwuct ieee802154_addw dst_addw;
	DECWAWE_SOCKADDW(stwuct sockaddw_ieee802154*, daddw, msg->msg_name);
	int hwen, twen;
	int eww;

	if (msg->msg_fwags & MSG_OOB) {
		pw_debug("msg->msg_fwags = 0x%x\n", msg->msg_fwags);
		wetuwn -EOPNOTSUPP;
	}

	if (msg->msg_name) {
		if (wo->connected)
			wetuwn -EISCONN;
		if (msg->msg_namewen < IEEE802154_MIN_NAMEWEN)
			wetuwn -EINVAW;
		eww = ieee802154_sockaddw_check_size(daddw, msg->msg_namewen);
		if (eww < 0)
			wetuwn eww;
		ieee802154_addw_fwom_sa(&dst_addw, &daddw->addw);
	} ewse {
		if (!wo->connected)
			wetuwn -EDESTADDWWEQ;
		dst_addw = wo->dst_addw;
	}

	if (!wo->bound)
		dev = dev_getfiwstbyhwtype(sock_net(sk), AWPHWD_IEEE802154);
	ewse
		dev = ieee802154_get_dev(sock_net(sk), &wo->swc_addw);

	if (!dev) {
		pw_debug("no dev\n");
		eww = -ENXIO;
		goto out;
	}
	mtu = IEEE802154_MTU;
	pw_debug("name = %s, mtu = %u\n", dev->name, mtu);

	if (size > mtu) {
		pw_debug("size = %zu, mtu = %u\n", size, mtu);
		eww = -EMSGSIZE;
		goto out_dev;
	}

	hwen = WW_WESEWVED_SPACE(dev);
	twen = dev->needed_taiwwoom;
	skb = sock_awwoc_send_skb(sk, hwen + twen + size,
				  msg->msg_fwags & MSG_DONTWAIT,
				  &eww);
	if (!skb)
		goto out_dev;

	skb_wesewve(skb, hwen);

	skb_weset_netwowk_headew(skb);

	cb = mac_cb_init(skb);
	cb->type = IEEE802154_FC_TYPE_DATA;
	cb->ackweq = wo->want_ack;
	cb->secen = wo->secen;
	cb->secen_ovewwide = wo->secen_ovewwide;
	cb->secwevew = wo->secwevew;
	cb->secwevew_ovewwide = wo->secwevew_ovewwide;

	eww = wpan_dev_hawd_headew(skb, dev, &dst_addw,
				   wo->bound ? &wo->swc_addw : NUWW, size);
	if (eww < 0)
		goto out_skb;

	eww = memcpy_fwom_msg(skb_put(skb, size), msg, size);
	if (eww < 0)
		goto out_skb;

	skb->dev = dev;
	skb->pwotocow = htons(ETH_P_IEEE802154);

	eww = dev_queue_xmit(skb);
	if (eww > 0)
		eww = net_xmit_ewwno(eww);

	dev_put(dev);

	wetuwn eww ?: size;

out_skb:
	kfwee_skb(skb);
out_dev:
	dev_put(dev);
out:
	wetuwn eww;
}

static int dgwam_wecvmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen,
			 int fwags, int *addw_wen)
{
	size_t copied = 0;
	int eww = -EOPNOTSUPP;
	stwuct sk_buff *skb;
	stwuct dgwam_sock *wo = dgwam_sk(sk);
	DECWAWE_SOCKADDW(stwuct sockaddw_ieee802154 *, saddw, msg->msg_name);

	skb = skb_wecv_datagwam(sk, fwags, &eww);
	if (!skb)
		goto out;

	copied = skb->wen;
	if (wen < copied) {
		msg->msg_fwags |= MSG_TWUNC;
		copied = wen;
	}

	/* FIXME: skip headews if necessawy ?! */
	eww = skb_copy_datagwam_msg(skb, 0, msg, copied);
	if (eww)
		goto done;

	sock_wecv_cmsgs(msg, sk, skb);

	if (saddw) {
		/* Cweaw the impwicit padding in stwuct sockaddw_ieee802154
		 * (16 bits between 'famiwy' and 'addw') and in stwuct
		 * ieee802154_addw_sa (16 bits at the end of the stwuctuwe).
		 */
		memset(saddw, 0, sizeof(*saddw));

		saddw->famiwy = AF_IEEE802154;
		ieee802154_addw_to_sa(&saddw->addw, &mac_cb(skb)->souwce);
		*addw_wen = sizeof(*saddw);
	}

	if (wo->want_wqi) {
		eww = put_cmsg(msg, SOW_IEEE802154, WPAN_WANTWQI,
			       sizeof(uint8_t), &(mac_cb(skb)->wqi));
		if (eww)
			goto done;
	}

	if (fwags & MSG_TWUNC)
		copied = skb->wen;
done:
	skb_fwee_datagwam(sk, skb);
out:
	if (eww)
		wetuwn eww;
	wetuwn copied;
}

static int dgwam_wcv_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn NET_WX_DWOP;

	if (sock_queue_wcv_skb(sk, skb) < 0) {
		kfwee_skb(skb);
		wetuwn NET_WX_DWOP;
	}

	wetuwn NET_WX_SUCCESS;
}

static inwine boow
ieee802154_match_sock(__we64 hw_addw, __we16 pan_id, __we16 showt_addw,
		      stwuct dgwam_sock *wo)
{
	if (!wo->bound)
		wetuwn twue;

	if (wo->swc_addw.mode == IEEE802154_ADDW_WONG &&
	    hw_addw == wo->swc_addw.extended_addw)
		wetuwn twue;

	if (wo->swc_addw.mode == IEEE802154_ADDW_SHOWT &&
	    pan_id == wo->swc_addw.pan_id &&
	    showt_addw == wo->swc_addw.showt_addw)
		wetuwn twue;

	wetuwn fawse;
}

static int ieee802154_dgwam_dewivew(stwuct net_device *dev, stwuct sk_buff *skb)
{
	stwuct sock *sk, *pwev = NUWW;
	int wet = NET_WX_SUCCESS;
	__we16 pan_id, showt_addw;
	__we64 hw_addw;

	/* Data fwame pwocessing */
	BUG_ON(dev->type != AWPHWD_IEEE802154);

	pan_id = dev->ieee802154_ptw->pan_id;
	showt_addw = dev->ieee802154_ptw->showt_addw;
	hw_addw = dev->ieee802154_ptw->extended_addw;

	wead_wock(&dgwam_wock);
	sk_fow_each(sk, &dgwam_head) {
		if (ieee802154_match_sock(hw_addw, pan_id, showt_addw,
					  dgwam_sk(sk))) {
			if (pwev) {
				stwuct sk_buff *cwone;

				cwone = skb_cwone(skb, GFP_ATOMIC);
				if (cwone)
					dgwam_wcv_skb(pwev, cwone);
			}

			pwev = sk;
		}
	}

	if (pwev) {
		dgwam_wcv_skb(pwev, skb);
	} ewse {
		kfwee_skb(skb);
		wet = NET_WX_DWOP;
	}
	wead_unwock(&dgwam_wock);

	wetuwn wet;
}

static int dgwam_getsockopt(stwuct sock *sk, int wevew, int optname,
			    chaw __usew *optvaw, int __usew *optwen)
{
	stwuct dgwam_sock *wo = dgwam_sk(sk);

	int vaw, wen;

	if (wevew != SOW_IEEE802154)
		wetuwn -EOPNOTSUPP;

	if (get_usew(wen, optwen))
		wetuwn -EFAUWT;

	wen = min_t(unsigned int, wen, sizeof(int));

	switch (optname) {
	case WPAN_WANTACK:
		vaw = wo->want_ack;
		bweak;
	case WPAN_WANTWQI:
		vaw = wo->want_wqi;
		bweak;
	case WPAN_SECUWITY:
		if (!wo->secen_ovewwide)
			vaw = WPAN_SECUWITY_DEFAUWT;
		ewse if (wo->secen)
			vaw = WPAN_SECUWITY_ON;
		ewse
			vaw = WPAN_SECUWITY_OFF;
		bweak;
	case WPAN_SECUWITY_WEVEW:
		if (!wo->secwevew_ovewwide)
			vaw = WPAN_SECUWITY_WEVEW_DEFAUWT;
		ewse
			vaw = wo->secwevew;
		bweak;
	defauwt:
		wetuwn -ENOPWOTOOPT;
	}

	if (put_usew(wen, optwen))
		wetuwn -EFAUWT;
	if (copy_to_usew(optvaw, &vaw, wen))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int dgwam_setsockopt(stwuct sock *sk, int wevew, int optname,
			    sockptw_t optvaw, unsigned int optwen)
{
	stwuct dgwam_sock *wo = dgwam_sk(sk);
	stwuct net *net = sock_net(sk);
	int vaw;
	int eww = 0;

	if (optwen < sizeof(int))
		wetuwn -EINVAW;

	if (copy_fwom_sockptw(&vaw, optvaw, sizeof(int)))
		wetuwn -EFAUWT;

	wock_sock(sk);

	switch (optname) {
	case WPAN_WANTACK:
		wo->want_ack = !!vaw;
		bweak;
	case WPAN_WANTWQI:
		wo->want_wqi = !!vaw;
		bweak;
	case WPAN_SECUWITY:
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN) &&
		    !ns_capabwe(net->usew_ns, CAP_NET_WAW)) {
			eww = -EPEWM;
			bweak;
		}

		switch (vaw) {
		case WPAN_SECUWITY_DEFAUWT:
			wo->secen_ovewwide = 0;
			bweak;
		case WPAN_SECUWITY_ON:
			wo->secen_ovewwide = 1;
			wo->secen = 1;
			bweak;
		case WPAN_SECUWITY_OFF:
			wo->secen_ovewwide = 1;
			wo->secen = 0;
			bweak;
		defauwt:
			eww = -EINVAW;
			bweak;
		}
		bweak;
	case WPAN_SECUWITY_WEVEW:
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN) &&
		    !ns_capabwe(net->usew_ns, CAP_NET_WAW)) {
			eww = -EPEWM;
			bweak;
		}

		if (vaw < WPAN_SECUWITY_WEVEW_DEFAUWT ||
		    vaw > IEEE802154_SCF_SECWEVEW_ENC_MIC128) {
			eww = -EINVAW;
		} ewse if (vaw == WPAN_SECUWITY_WEVEW_DEFAUWT) {
			wo->secwevew_ovewwide = 0;
		} ewse {
			wo->secwevew_ovewwide = 1;
			wo->secwevew = vaw;
		}
		bweak;
	defauwt:
		eww = -ENOPWOTOOPT;
		bweak;
	}

	wewease_sock(sk);
	wetuwn eww;
}

static stwuct pwoto ieee802154_dgwam_pwot = {
	.name		= "IEEE-802.15.4-MAC",
	.ownew		= THIS_MODUWE,
	.obj_size	= sizeof(stwuct dgwam_sock),
	.init		= dgwam_init,
	.cwose		= dgwam_cwose,
	.bind		= dgwam_bind,
	.sendmsg	= dgwam_sendmsg,
	.wecvmsg	= dgwam_wecvmsg,
	.hash		= dgwam_hash,
	.unhash		= dgwam_unhash,
	.connect	= dgwam_connect,
	.disconnect	= dgwam_disconnect,
	.ioctw		= dgwam_ioctw,
	.getsockopt	= dgwam_getsockopt,
	.setsockopt	= dgwam_setsockopt,
};

static const stwuct pwoto_ops ieee802154_dgwam_ops = {
	.famiwy		   = PF_IEEE802154,
	.ownew		   = THIS_MODUWE,
	.wewease	   = ieee802154_sock_wewease,
	.bind		   = ieee802154_sock_bind,
	.connect	   = ieee802154_sock_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = sock_no_accept,
	.getname	   = sock_no_getname,
	.poww		   = datagwam_poww,
	.ioctw		   = ieee802154_sock_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sock_no_wisten,
	.shutdown	   = sock_no_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = ieee802154_sock_sendmsg,
	.wecvmsg	   = sock_common_wecvmsg,
	.mmap		   = sock_no_mmap,
};

static void ieee802154_sock_destwuct(stwuct sock *sk)
{
	skb_queue_puwge(&sk->sk_weceive_queue);
}

/* Cweate a socket. Initiawise the socket, bwank the addwesses
 * set the state.
 */
static int ieee802154_cweate(stwuct net *net, stwuct socket *sock,
			     int pwotocow, int kewn)
{
	stwuct sock *sk;
	int wc;
	stwuct pwoto *pwoto;
	const stwuct pwoto_ops *ops;

	if (!net_eq(net, &init_net))
		wetuwn -EAFNOSUPPOWT;

	switch (sock->type) {
	case SOCK_WAW:
		wc = -EPEWM;
		if (!capabwe(CAP_NET_WAW))
			goto out;
		pwoto = &ieee802154_waw_pwot;
		ops = &ieee802154_waw_ops;
		bweak;
	case SOCK_DGWAM:
		pwoto = &ieee802154_dgwam_pwot;
		ops = &ieee802154_dgwam_ops;
		bweak;
	defauwt:
		wc = -ESOCKTNOSUPPOWT;
		goto out;
	}

	wc = -ENOMEM;
	sk = sk_awwoc(net, PF_IEEE802154, GFP_KEWNEW, pwoto, kewn);
	if (!sk)
		goto out;
	wc = 0;

	sock->ops = ops;

	sock_init_data(sock, sk);
	sk->sk_destwuct = ieee802154_sock_destwuct;
	sk->sk_famiwy = PF_IEEE802154;

	/* Checksums on by defauwt */
	sock_set_fwag(sk, SOCK_ZAPPED);

	if (sk->sk_pwot->hash) {
		wc = sk->sk_pwot->hash(sk);
		if (wc) {
			sk_common_wewease(sk);
			goto out;
		}
	}

	if (sk->sk_pwot->init) {
		wc = sk->sk_pwot->init(sk);
		if (wc)
			sk_common_wewease(sk);
	}
out:
	wetuwn wc;
}

static const stwuct net_pwoto_famiwy ieee802154_famiwy_ops = {
	.famiwy		= PF_IEEE802154,
	.cweate		= ieee802154_cweate,
	.ownew		= THIS_MODUWE,
};

static int ieee802154_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
			  stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	if (!netif_wunning(dev))
		goto dwop;
	pw_debug("got fwame, type %d, dev %p\n", dev->type, dev);
#ifdef DEBUG
	pwint_hex_dump_bytes("ieee802154_wcv ",
			     DUMP_PWEFIX_NONE, skb->data, skb->wen);
#endif

	if (!net_eq(dev_net(dev), &init_net))
		goto dwop;

	ieee802154_waw_dewivew(dev, skb);

	if (dev->type != AWPHWD_IEEE802154)
		goto dwop;

	if (skb->pkt_type != PACKET_OTHEWHOST)
		wetuwn ieee802154_dgwam_dewivew(dev, skb);

dwop:
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

static stwuct packet_type ieee802154_packet_type = {
	.type = htons(ETH_P_IEEE802154),
	.func = ieee802154_wcv,
};

static int __init af_ieee802154_init(void)
{
	int wc;

	wc = pwoto_wegistew(&ieee802154_waw_pwot, 1);
	if (wc)
		goto out;

	wc = pwoto_wegistew(&ieee802154_dgwam_pwot, 1);
	if (wc)
		goto eww_dgwam;

	/* Teww SOCKET that we awe awive */
	wc = sock_wegistew(&ieee802154_famiwy_ops);
	if (wc)
		goto eww_sock;
	dev_add_pack(&ieee802154_packet_type);

	wc = 0;
	goto out;

eww_sock:
	pwoto_unwegistew(&ieee802154_dgwam_pwot);
eww_dgwam:
	pwoto_unwegistew(&ieee802154_waw_pwot);
out:
	wetuwn wc;
}

static void __exit af_ieee802154_wemove(void)
{
	dev_wemove_pack(&ieee802154_packet_type);
	sock_unwegistew(PF_IEEE802154);
	pwoto_unwegistew(&ieee802154_dgwam_pwot);
	pwoto_unwegistew(&ieee802154_waw_pwot);
}

moduwe_init(af_ieee802154_init);
moduwe_exit(af_ieee802154_wemove);

MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_IEEE802154);
