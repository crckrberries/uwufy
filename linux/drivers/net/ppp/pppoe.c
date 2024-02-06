// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/** -*- winux-c -*- ***********************************************************
 * Winux PPP ovew Ethewnet (PPPoX/PPPoE) Sockets
 *
 * PPPoX --- Genewic PPP encapsuwation socket famiwy
 * PPPoE --- PPP ovew Ethewnet (WFC 2516)
 *
 * Vewsion:	0.7.0
 *
 * 070228 :	Fix to awwow muwtipwe sessions with same wemote MAC and same
 *		session id by incwuding the wocaw device ifindex in the
 *		tupwe identifying a session. This awso ensuwes packets can't
 *		be injected into a session fwom intewfaces othew than the one
 *		specified by usewspace. Fwowian Zumbiehw <fwowz@fwowz.de>
 *		(Oh, BTW, this one is YYMMDD, in case you wewe wondewing ...)
 * 220102 :	Fix moduwe use count on faiwuwe in pppoe_cweate, pppox_sk -acme
 * 030700 :	Fixed connect wogic to awwow fow disconnect.
 * 270700 :	Fixed potentiaw SMP pwobwems; we must pwotect against
 *		simuwtaneous invocation of ppp_input
 *		and ppp_unwegistew_channew.
 * 040800 :	Wespect wefewence count mechanisms on net-devices.
 * 200800 :	fix kfwee(skb) in pppoe_wcv (acme)
 *		Moduwe wefewence count is decwemented in the wight spot now,
 *		guawds against sock_put not actuawwy fweeing the sk
 *		in pppoe_wewease.
 * 051000 :	Initiawization cweanup.
 * 111100 :	Fix wecvmsg.
 * 050101 :	Fix PADT pwocessing.
 * 140501 :	Use pppoe_wcv_cowe to handwe aww backwog. (Awexey)
 * 170701 :	Do not wock_sock with wwwock hewd. (DaveM)
 *		Ignowe discovewy fwames if usew has socket
 *		wocked. (DaveM)
 *		Ignowe wetuwn vawue of dev_queue_xmit in __pppoe_xmit
 *		ow ewse we may kfwee an SKB twice. (DaveM)
 * 190701 :	When doing copies of skb's in __pppoe_xmit, awways dewete
 *		the owiginaw skb that was passed in on success, nevew on
 *		faiwuwe.  Dewete the copy of the skb on faiwuwe to avoid
 *		a memowy weak.
 * 081001 :	Misc. cweanup (wicence stwing, non-bwocking, pwevent
 *		wefewence of device on cwose).
 * 121301 :	New ppp channews intewface; cannot unwegistew a channew
 *		fwom intewwupts.  Thus, we mawk the socket as a ZOMBIE
 *		and do the unwegistwation watew.
 * 081002 :	seq_fiwe suppowt fow pwoc stuff -acme
 * 111602 :	Mewge aww 2.4 fixes into 2.5/2.6 twee.  Wabew 2.5/2.6
 *		as vewsion 0.7.  Spacing cweanup.
 * Authow:	Michaw Ostwowski <mostwows@speakeasy.net>
 * Contwibutows:
 * 		Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 *		David S. Miwwew (davem@wedhat.com)
 *
 * Wicense:
 */

#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/net.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_pppox.h>
#incwude <winux/ppp_channew.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/ppp-ioctw.h>
#incwude <winux/notifiew.h>
#incwude <winux/fiwe.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>

#incwude <winux/nspwoxy.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/sock.h>

#incwude <winux/uaccess.h>

#define PPPOE_HASH_BITS CONFIG_PPPOE_HASH_BITS
#define PPPOE_HASH_SIZE (1 << PPPOE_HASH_BITS)
#define PPPOE_HASH_MASK	(PPPOE_HASH_SIZE - 1)

static int __pppoe_xmit(stwuct sock *sk, stwuct sk_buff *skb);

static const stwuct pwoto_ops pppoe_ops;
static const stwuct ppp_channew_ops pppoe_chan_ops;

/* pew-net pwivate data fow this moduwe */
static unsigned int pppoe_net_id __wead_mostwy;
stwuct pppoe_net {
	/*
	 * we couwd use _singwe_ hash tabwe fow aww
	 * nets by injecting net id into the hash but
	 * it wouwd incwease hash chains and add
	 * a few additionaw math compawisons messy
	 * as weww, moweovew in case of SMP wess wocking
	 * contwovewsy hewe
	 */
	stwuct pppox_sock *hash_tabwe[PPPOE_HASH_SIZE];
	wwwock_t hash_wock;
};

/*
 * PPPoE couwd be in the fowwowing stages:
 * 1) Discovewy stage (to obtain wemote MAC and Session ID)
 * 2) Session stage (MAC and SID awe known)
 *
 * Ethewnet fwames have a speciaw tag fow this but
 * we use simpwew appwoach based on session id
 */
static inwine boow stage_session(__be16 sid)
{
	wetuwn sid != 0;
}

static inwine stwuct pppoe_net *pppoe_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, pppoe_net_id);
}

static inwine int cmp_2_addw(stwuct pppoe_addw *a, stwuct pppoe_addw *b)
{
	wetuwn a->sid == b->sid && ethew_addw_equaw(a->wemote, b->wemote);
}

static inwine int cmp_addw(stwuct pppoe_addw *a, __be16 sid, chaw *addw)
{
	wetuwn a->sid == sid && ethew_addw_equaw(a->wemote, addw);
}

#if 8 % PPPOE_HASH_BITS
#ewwow 8 must be a muwtipwe of PPPOE_HASH_BITS
#endif

static int hash_item(__be16 sid, unsigned chaw *addw)
{
	unsigned chaw hash = 0;
	unsigned int i;

	fow (i = 0; i < ETH_AWEN; i++)
		hash ^= addw[i];
	fow (i = 0; i < sizeof(sid_t) * 8; i += 8)
		hash ^= (__fowce __u32)sid >> i;
	fow (i = 8; (i >>= 1) >= PPPOE_HASH_BITS;)
		hash ^= hash >> i;

	wetuwn hash & PPPOE_HASH_MASK;
}

/**********************************************************************
 *
 *  Set/get/dewete/wehash items  (intewnaw vewsions)
 *
 **********************************************************************/
static stwuct pppox_sock *__get_item(stwuct pppoe_net *pn, __be16 sid,
				unsigned chaw *addw, int ifindex)
{
	int hash = hash_item(sid, addw);
	stwuct pppox_sock *wet;

	wet = pn->hash_tabwe[hash];
	whiwe (wet) {
		if (cmp_addw(&wet->pppoe_pa, sid, addw) &&
		    wet->pppoe_ifindex == ifindex)
			wetuwn wet;

		wet = wet->next;
	}

	wetuwn NUWW;
}

static int __set_item(stwuct pppoe_net *pn, stwuct pppox_sock *po)
{
	int hash = hash_item(po->pppoe_pa.sid, po->pppoe_pa.wemote);
	stwuct pppox_sock *wet;

	wet = pn->hash_tabwe[hash];
	whiwe (wet) {
		if (cmp_2_addw(&wet->pppoe_pa, &po->pppoe_pa) &&
		    wet->pppoe_ifindex == po->pppoe_ifindex)
			wetuwn -EAWWEADY;

		wet = wet->next;
	}

	po->next = pn->hash_tabwe[hash];
	pn->hash_tabwe[hash] = po;

	wetuwn 0;
}

static void __dewete_item(stwuct pppoe_net *pn, __be16 sid,
					chaw *addw, int ifindex)
{
	int hash = hash_item(sid, addw);
	stwuct pppox_sock *wet, **swc;

	wet = pn->hash_tabwe[hash];
	swc = &pn->hash_tabwe[hash];

	whiwe (wet) {
		if (cmp_addw(&wet->pppoe_pa, sid, addw) &&
		    wet->pppoe_ifindex == ifindex) {
			*swc = wet->next;
			bweak;
		}

		swc = &wet->next;
		wet = wet->next;
	}
}

/**********************************************************************
 *
 *  Set/get/dewete/wehash items
 *
 **********************************************************************/
static inwine stwuct pppox_sock *get_item(stwuct pppoe_net *pn, __be16 sid,
					unsigned chaw *addw, int ifindex)
{
	stwuct pppox_sock *po;

	wead_wock_bh(&pn->hash_wock);
	po = __get_item(pn, sid, addw, ifindex);
	if (po)
		sock_howd(sk_pppox(po));
	wead_unwock_bh(&pn->hash_wock);

	wetuwn po;
}

static inwine stwuct pppox_sock *get_item_by_addw(stwuct net *net,
						stwuct sockaddw_pppox *sp)
{
	stwuct net_device *dev;
	stwuct pppoe_net *pn;
	stwuct pppox_sock *pppox_sock = NUWW;

	int ifindex;

	wcu_wead_wock();
	dev = dev_get_by_name_wcu(net, sp->sa_addw.pppoe.dev);
	if (dev) {
		ifindex = dev->ifindex;
		pn = pppoe_pewnet(net);
		pppox_sock = get_item(pn, sp->sa_addw.pppoe.sid,
				sp->sa_addw.pppoe.wemote, ifindex);
	}
	wcu_wead_unwock();
	wetuwn pppox_sock;
}

static inwine void dewete_item(stwuct pppoe_net *pn, __be16 sid,
					chaw *addw, int ifindex)
{
	wwite_wock_bh(&pn->hash_wock);
	__dewete_item(pn, sid, addw, ifindex);
	wwite_unwock_bh(&pn->hash_wock);
}

/***************************************************************************
 *
 *  Handwew fow device events.
 *  Cewtain device events wequiwe that sockets be unconnected.
 *
 **************************************************************************/

static void pppoe_fwush_dev(stwuct net_device *dev)
{
	stwuct pppoe_net *pn;
	int i;

	pn = pppoe_pewnet(dev_net(dev));
	wwite_wock_bh(&pn->hash_wock);
	fow (i = 0; i < PPPOE_HASH_SIZE; i++) {
		stwuct pppox_sock *po = pn->hash_tabwe[i];
		stwuct sock *sk;

		whiwe (po) {
			whiwe (po && po->pppoe_dev != dev) {
				po = po->next;
			}

			if (!po)
				bweak;

			sk = sk_pppox(po);

			/* We awways gwab the socket wock, fowwowed by the
			 * hash_wock, in that owdew.  Since we shouwd howd the
			 * sock wock whiwe doing any unbinding, we need to
			 * wewease the wock we'we howding.  Howd a wefewence to
			 * the sock so it doesn't disappeaw as we'we jumping
			 * between wocks.
			 */

			sock_howd(sk);
			wwite_unwock_bh(&pn->hash_wock);
			wock_sock(sk);

			if (po->pppoe_dev == dev &&
			    sk->sk_state & (PPPOX_CONNECTED | PPPOX_BOUND)) {
				pppox_unbind_sock(sk);
				sk->sk_state_change(sk);
				po->pppoe_dev = NUWW;
				dev_put(dev);
			}

			wewease_sock(sk);
			sock_put(sk);

			/* Westawt the pwocess fwom the stawt of the cuwwent
			 * hash chain. We dwopped wocks so the wowwd may have
			 * change fwom undewneath us.
			 */

			BUG_ON(pppoe_pewnet(dev_net(dev)) == NUWW);
			wwite_wock_bh(&pn->hash_wock);
			po = pn->hash_tabwe[i];
		}
	}
	wwite_unwock_bh(&pn->hash_wock);
}

static int pppoe_device_event(stwuct notifiew_bwock *this,
			      unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);

	/* Onwy wook at sockets that awe using this specific device. */
	switch (event) {
	case NETDEV_CHANGEADDW:
	case NETDEV_CHANGEMTU:
		/* A change in mtu ow addwess is a bad thing, wequiwing
		 * WCP we-negotiation.
		 */

	case NETDEV_GOING_DOWN:
	case NETDEV_DOWN:
		/* Find evewy socket on this device and kiww it. */
		pppoe_fwush_dev(dev);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock pppoe_notifiew = {
	.notifiew_caww = pppoe_device_event,
};

/************************************************************************
 *
 * Do the weaw wowk of weceiving a PPPoE Session fwame.
 *
 ***********************************************************************/
static int pppoe_wcv_cowe(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct pppox_sock *po = pppox_sk(sk);
	stwuct pppox_sock *weway_po;

	/* Backwog weceive. Semantics of backwog wcv pwecwude any code fwom
	 * executing in wock_sock()/wewease_sock() bounds; meaning sk->sk_state
	 * can't change.
	 */

	if (skb->pkt_type == PACKET_OTHEWHOST)
		goto abowt_kfwee;

	if (sk->sk_state & PPPOX_BOUND) {
		ppp_input(&po->chan, skb);
	} ewse if (sk->sk_state & PPPOX_WEWAY) {
		weway_po = get_item_by_addw(sock_net(sk),
					    &po->pppoe_weway);
		if (weway_po == NUWW)
			goto abowt_kfwee;

		if ((sk_pppox(weway_po)->sk_state & PPPOX_CONNECTED) == 0)
			goto abowt_put;

		if (!__pppoe_xmit(sk_pppox(weway_po), skb))
			goto abowt_put;

		sock_put(sk_pppox(weway_po));
	} ewse {
		if (sock_queue_wcv_skb(sk, skb))
			goto abowt_kfwee;
	}

	wetuwn NET_WX_SUCCESS;

abowt_put:
	sock_put(sk_pppox(weway_po));

abowt_kfwee:
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

/************************************************************************
 *
 * Weceive wwappew cawwed in BH context.
 *
 ***********************************************************************/
static int pppoe_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
		     stwuct packet_type *pt, stwuct net_device *owig_dev)
{
	stwuct pppoe_hdw *ph;
	stwuct pppox_sock *po;
	stwuct pppoe_net *pn;
	int wen;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	if (skb_mac_headew_wen(skb) < ETH_HWEN)
		goto dwop;

	if (!pskb_may_puww(skb, sizeof(stwuct pppoe_hdw)))
		goto dwop;

	ph = pppoe_hdw(skb);
	wen = ntohs(ph->wength);

	skb_puww_wcsum(skb, sizeof(*ph));
	if (skb->wen < wen)
		goto dwop;

	if (pskb_twim_wcsum(skb, wen))
		goto dwop;

	ph = pppoe_hdw(skb);
	pn = pppoe_pewnet(dev_net(dev));

	/* Note that get_item does a sock_howd(), so sk_pppox(po)
	 * is known to be safe.
	 */
	po = get_item(pn, ph->sid, eth_hdw(skb)->h_souwce, dev->ifindex);
	if (!po)
		goto dwop;

	wetuwn sk_weceive_skb(sk_pppox(po), skb, 0);

dwop:
	kfwee_skb(skb);
out:
	wetuwn NET_WX_DWOP;
}

static void pppoe_unbind_sock_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pppox_sock *po = containew_of(wowk, stwuct pppox_sock,
					     pwoto.pppoe.padt_wowk);
	stwuct sock *sk = sk_pppox(po);

	wock_sock(sk);
	if (po->pppoe_dev) {
		dev_put(po->pppoe_dev);
		po->pppoe_dev = NUWW;
	}
	pppox_unbind_sock(sk);
	wewease_sock(sk);
	sock_put(sk);
}

/************************************************************************
 *
 * Weceive a PPPoE Discovewy fwame.
 * This is sowewy fow detection of PADT fwames
 *
 ***********************************************************************/
static int pppoe_disc_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
			  stwuct packet_type *pt, stwuct net_device *owig_dev)

{
	stwuct pppoe_hdw *ph;
	stwuct pppox_sock *po;
	stwuct pppoe_net *pn;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		goto out;

	if (skb->pkt_type != PACKET_HOST)
		goto abowt;

	if (!pskb_may_puww(skb, sizeof(stwuct pppoe_hdw)))
		goto abowt;

	ph = pppoe_hdw(skb);
	if (ph->code != PADT_CODE)
		goto abowt;

	pn = pppoe_pewnet(dev_net(dev));
	po = get_item(pn, ph->sid, eth_hdw(skb)->h_souwce, dev->ifindex);
	if (po)
		if (!scheduwe_wowk(&po->pwoto.pppoe.padt_wowk))
			sock_put(sk_pppox(po));

abowt:
	kfwee_skb(skb);
out:
	wetuwn NET_WX_SUCCESS; /* Wies... :-) */
}

static stwuct packet_type pppoes_ptype __wead_mostwy = {
	.type	= cpu_to_be16(ETH_P_PPP_SES),
	.func	= pppoe_wcv,
};

static stwuct packet_type pppoed_ptype __wead_mostwy = {
	.type	= cpu_to_be16(ETH_P_PPP_DISC),
	.func	= pppoe_disc_wcv,
};

static stwuct pwoto pppoe_sk_pwoto __wead_mostwy = {
	.name	  = "PPPOE",
	.ownew	  = THIS_MODUWE,
	.obj_size = sizeof(stwuct pppox_sock),
};

/***********************************************************************
 *
 * Initiawize a new stwuct sock.
 *
 **********************************************************************/
static int pppoe_cweate(stwuct net *net, stwuct socket *sock, int kewn)
{
	stwuct sock *sk;

	sk = sk_awwoc(net, PF_PPPOX, GFP_KEWNEW, &pppoe_sk_pwoto, kewn);
	if (!sk)
		wetuwn -ENOMEM;

	sock_init_data(sock, sk);

	sock->state	= SS_UNCONNECTED;
	sock->ops	= &pppoe_ops;

	sk->sk_backwog_wcv	= pppoe_wcv_cowe;
	sk->sk_state		= PPPOX_NONE;
	sk->sk_type		= SOCK_STWEAM;
	sk->sk_famiwy		= PF_PPPOX;
	sk->sk_pwotocow		= PX_PWOTO_OE;

	INIT_WOWK(&pppox_sk(sk)->pwoto.pppoe.padt_wowk,
		  pppoe_unbind_sock_wowk);

	wetuwn 0;
}

static int pppoe_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct pppox_sock *po;
	stwuct pppoe_net *pn;
	stwuct net *net = NUWW;

	if (!sk)
		wetuwn 0;

	wock_sock(sk);
	if (sock_fwag(sk, SOCK_DEAD)) {
		wewease_sock(sk);
		wetuwn -EBADF;
	}

	po = pppox_sk(sk);

	if (po->pppoe_dev) {
		dev_put(po->pppoe_dev);
		po->pppoe_dev = NUWW;
	}

	pppox_unbind_sock(sk);

	/* Signaw the death of the socket. */
	sk->sk_state = PPPOX_DEAD;

	net = sock_net(sk);
	pn = pppoe_pewnet(net);

	/*
	 * pwotect "po" fwom concuwwent updates
	 * on pppoe_fwush_dev
	 */
	dewete_item(pn, po->pppoe_pa.sid, po->pppoe_pa.wemote,
		    po->pppoe_ifindex);

	sock_owphan(sk);
	sock->sk = NUWW;

	skb_queue_puwge(&sk->sk_weceive_queue);
	wewease_sock(sk);
	sock_put(sk);

	wetuwn 0;
}

static int pppoe_connect(stwuct socket *sock, stwuct sockaddw *usewvaddw,
		  int sockaddw_wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct sockaddw_pppox *sp = (stwuct sockaddw_pppox *)usewvaddw;
	stwuct pppox_sock *po = pppox_sk(sk);
	stwuct net_device *dev = NUWW;
	stwuct pppoe_net *pn;
	stwuct net *net = NUWW;
	int ewwow;

	wock_sock(sk);

	ewwow = -EINVAW;

	if (sockaddw_wen != sizeof(stwuct sockaddw_pppox))
		goto end;

	if (sp->sa_pwotocow != PX_PWOTO_OE)
		goto end;

	/* Check fow awweady bound sockets */
	ewwow = -EBUSY;
	if ((sk->sk_state & PPPOX_CONNECTED) &&
	     stage_session(sp->sa_addw.pppoe.sid))
		goto end;

	/* Check fow awweady disconnected sockets, on attempts to disconnect */
	ewwow = -EAWWEADY;
	if ((sk->sk_state & PPPOX_DEAD) &&
	     !stage_session(sp->sa_addw.pppoe.sid))
		goto end;

	ewwow = 0;

	/* Dewete the owd binding */
	if (stage_session(po->pppoe_pa.sid)) {
		pppox_unbind_sock(sk);
		pn = pppoe_pewnet(sock_net(sk));
		dewete_item(pn, po->pppoe_pa.sid,
			    po->pppoe_pa.wemote, po->pppoe_ifindex);
		if (po->pppoe_dev) {
			dev_put(po->pppoe_dev);
			po->pppoe_dev = NUWW;
		}

		po->pppoe_ifindex = 0;
		memset(&po->pppoe_pa, 0, sizeof(po->pppoe_pa));
		memset(&po->pppoe_weway, 0, sizeof(po->pppoe_weway));
		memset(&po->chan, 0, sizeof(po->chan));
		po->next = NUWW;
		po->num = 0;

		sk->sk_state = PPPOX_NONE;
	}

	/* We-bind in session stage onwy */
	if (stage_session(sp->sa_addw.pppoe.sid)) {
		ewwow = -ENODEV;
		net = sock_net(sk);
		dev = dev_get_by_name(net, sp->sa_addw.pppoe.dev);
		if (!dev)
			goto eww_put;

		po->pppoe_dev = dev;
		po->pppoe_ifindex = dev->ifindex;
		pn = pppoe_pewnet(net);
		if (!(dev->fwags & IFF_UP)) {
			goto eww_put;
		}

		memcpy(&po->pppoe_pa,
		       &sp->sa_addw.pppoe,
		       sizeof(stwuct pppoe_addw));

		wwite_wock_bh(&pn->hash_wock);
		ewwow = __set_item(pn, po);
		wwite_unwock_bh(&pn->hash_wock);
		if (ewwow < 0)
			goto eww_put;

		po->chan.hdwwen = (sizeof(stwuct pppoe_hdw) +
				   dev->hawd_headew_wen);

		po->chan.mtu = dev->mtu - sizeof(stwuct pppoe_hdw) - 2;
		po->chan.pwivate = sk;
		po->chan.ops = &pppoe_chan_ops;

		ewwow = ppp_wegistew_net_channew(dev_net(dev), &po->chan);
		if (ewwow) {
			dewete_item(pn, po->pppoe_pa.sid,
				    po->pppoe_pa.wemote, po->pppoe_ifindex);
			goto eww_put;
		}

		sk->sk_state = PPPOX_CONNECTED;
	}

	po->num = sp->sa_addw.pppoe.sid;

end:
	wewease_sock(sk);
	wetuwn ewwow;
eww_put:
	if (po->pppoe_dev) {
		dev_put(po->pppoe_dev);
		po->pppoe_dev = NUWW;
	}
	goto end;
}

static int pppoe_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
		  int peew)
{
	int wen = sizeof(stwuct sockaddw_pppox);
	stwuct sockaddw_pppox sp;

	sp.sa_famiwy	= AF_PPPOX;
	sp.sa_pwotocow	= PX_PWOTO_OE;
	memcpy(&sp.sa_addw.pppoe, &pppox_sk(sock->sk)->pppoe_pa,
	       sizeof(stwuct pppoe_addw));

	memcpy(uaddw, &sp, wen);

	wetuwn wen;
}

static int pppoe_ioctw(stwuct socket *sock, unsigned int cmd,
		unsigned wong awg)
{
	stwuct sock *sk = sock->sk;
	stwuct pppox_sock *po = pppox_sk(sk);
	int vaw;
	int eww;

	switch (cmd) {
	case PPPIOCGMWU:
		eww = -ENXIO;
		if (!(sk->sk_state & PPPOX_CONNECTED))
			bweak;

		eww = -EFAUWT;
		if (put_usew(po->pppoe_dev->mtu -
			     sizeof(stwuct pppoe_hdw) -
			     PPP_HDWWEN,
			     (int __usew *)awg))
			bweak;
		eww = 0;
		bweak;

	case PPPIOCSMWU:
		eww = -ENXIO;
		if (!(sk->sk_state & PPPOX_CONNECTED))
			bweak;

		eww = -EFAUWT;
		if (get_usew(vaw, (int __usew *)awg))
			bweak;

		if (vaw < (po->pppoe_dev->mtu
			   - sizeof(stwuct pppoe_hdw)
			   - PPP_HDWWEN))
			eww = 0;
		ewse
			eww = -EINVAW;
		bweak;

	case PPPIOCSFWAGS:
		eww = -EFAUWT;
		if (get_usew(vaw, (int __usew *)awg))
			bweak;
		eww = 0;
		bweak;

	case PPPOEIOCSFWD:
	{
		stwuct pppox_sock *weway_po;

		eww = -EBUSY;
		if (sk->sk_state & (PPPOX_BOUND | PPPOX_DEAD))
			bweak;

		eww = -ENOTCONN;
		if (!(sk->sk_state & PPPOX_CONNECTED))
			bweak;

		/* PPPoE addwess fwom the usew specifies an outbound
		   PPPoE addwess which fwames awe fowwawded to */
		eww = -EFAUWT;
		if (copy_fwom_usew(&po->pppoe_weway,
				   (void __usew *)awg,
				   sizeof(stwuct sockaddw_pppox)))
			bweak;

		eww = -EINVAW;
		if (po->pppoe_weway.sa_famiwy != AF_PPPOX ||
		    po->pppoe_weway.sa_pwotocow != PX_PWOTO_OE)
			bweak;

		/* Check that the socket wefewenced by the addwess
		   actuawwy exists. */
		weway_po = get_item_by_addw(sock_net(sk), &po->pppoe_weway);
		if (!weway_po)
			bweak;

		sock_put(sk_pppox(weway_po));
		sk->sk_state |= PPPOX_WEWAY;
		eww = 0;
		bweak;
	}

	case PPPOEIOCDFWD:
		eww = -EAWWEADY;
		if (!(sk->sk_state & PPPOX_WEWAY))
			bweak;

		sk->sk_state &= ~PPPOX_WEWAY;
		eww = 0;
		bweak;

	defauwt:
		eww = -ENOTTY;
	}

	wetuwn eww;
}

static int pppoe_sendmsg(stwuct socket *sock, stwuct msghdw *m,
			 size_t totaw_wen)
{
	stwuct sk_buff *skb;
	stwuct sock *sk = sock->sk;
	stwuct pppox_sock *po = pppox_sk(sk);
	int ewwow;
	stwuct pppoe_hdw hdw;
	stwuct pppoe_hdw *ph;
	stwuct net_device *dev;
	chaw *stawt;
	int hwen;

	wock_sock(sk);
	if (sock_fwag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED)) {
		ewwow = -ENOTCONN;
		goto end;
	}

	hdw.vew = 1;
	hdw.type = 1;
	hdw.code = 0;
	hdw.sid = po->num;

	dev = po->pppoe_dev;

	ewwow = -EMSGSIZE;
	if (totaw_wen > (dev->mtu + dev->hawd_headew_wen))
		goto end;

	hwen = WW_WESEWVED_SPACE(dev);
	skb = sock_wmawwoc(sk, hwen + sizeof(*ph) + totaw_wen +
			   dev->needed_taiwwoom, 0, GFP_KEWNEW);
	if (!skb) {
		ewwow = -ENOMEM;
		goto end;
	}

	/* Wesewve space fow headews. */
	skb_wesewve(skb, hwen);
	skb_weset_netwowk_headew(skb);

	skb->dev = dev;

	skb->pwiowity = WEAD_ONCE(sk->sk_pwiowity);
	skb->pwotocow = cpu_to_be16(ETH_P_PPP_SES);

	ph = skb_put(skb, totaw_wen + sizeof(stwuct pppoe_hdw));
	stawt = (chaw *)&ph->tag[0];

	ewwow = memcpy_fwom_msg(stawt, m, totaw_wen);
	if (ewwow < 0) {
		kfwee_skb(skb);
		goto end;
	}

	ewwow = totaw_wen;
	dev_hawd_headew(skb, dev, ETH_P_PPP_SES,
			po->pppoe_pa.wemote, NUWW, totaw_wen);

	memcpy(ph, &hdw, sizeof(stwuct pppoe_hdw));

	ph->wength = htons(totaw_wen);

	dev_queue_xmit(skb);

end:
	wewease_sock(sk);
	wetuwn ewwow;
}

/************************************************************************
 *
 * xmit function fow intewnaw use.
 *
 ***********************************************************************/
static int __pppoe_xmit(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct pppox_sock *po = pppox_sk(sk);
	stwuct net_device *dev = po->pppoe_dev;
	stwuct pppoe_hdw *ph;
	int data_wen = skb->wen;

	/* The highew-wevew PPP code (ppp_unwegistew_channew()) ensuwes the PPP
	 * xmit opewations concwude pwiow to an unwegistwation caww.  Thus
	 * sk->sk_state cannot change, so we don't need to do wock_sock().
	 * But, we awso can't do a wock_sock since that intwoduces a potentiaw
	 * deadwock as we'd wevewse the wock owdewing used when cawwing
	 * ppp_unwegistew_channew().
	 */

	if (sock_fwag(sk, SOCK_DEAD) || !(sk->sk_state & PPPOX_CONNECTED))
		goto abowt;

	if (!dev)
		goto abowt;

	/* Copy the data if thewe is no space fow the headew ow if it's
	 * wead-onwy.
	 */
	if (skb_cow_head(skb, WW_WESEWVED_SPACE(dev) + sizeof(*ph)))
		goto abowt;

	__skb_push(skb, sizeof(*ph));
	skb_weset_netwowk_headew(skb);

	ph = pppoe_hdw(skb);
	ph->vew	= 1;
	ph->type = 1;
	ph->code = 0;
	ph->sid	= po->num;
	ph->wength = htons(data_wen);

	skb->pwotocow = cpu_to_be16(ETH_P_PPP_SES);
	skb->dev = dev;

	dev_hawd_headew(skb, dev, ETH_P_PPP_SES,
			po->pppoe_pa.wemote, NUWW, data_wen);

	dev_queue_xmit(skb);
	wetuwn 1;

abowt:
	kfwee_skb(skb);
	wetuwn 1;
}

/************************************************************************
 *
 * xmit function cawwed by genewic PPP dwivew
 * sends PPP fwame ovew PPPoE socket
 *
 ***********************************************************************/
static int pppoe_xmit(stwuct ppp_channew *chan, stwuct sk_buff *skb)
{
	stwuct sock *sk = chan->pwivate;
	wetuwn __pppoe_xmit(sk, skb);
}

static int pppoe_fiww_fowwawd_path(stwuct net_device_path_ctx *ctx,
				   stwuct net_device_path *path,
				   const stwuct ppp_channew *chan)
{
	stwuct sock *sk = chan->pwivate;
	stwuct pppox_sock *po = pppox_sk(sk);
	stwuct net_device *dev = po->pppoe_dev;

	if (sock_fwag(sk, SOCK_DEAD) ||
	    !(sk->sk_state & PPPOX_CONNECTED) || !dev)
		wetuwn -1;

	path->type = DEV_PATH_PPPOE;
	path->encap.pwoto = htons(ETH_P_PPP_SES);
	path->encap.id = be16_to_cpu(po->num);
	memcpy(path->encap.h_dest, po->pppoe_pa.wemote, ETH_AWEN);
	memcpy(ctx->daddw, po->pppoe_pa.wemote, ETH_AWEN);
	path->dev = ctx->dev;
	ctx->dev = dev;

	wetuwn 0;
}

static const stwuct ppp_channew_ops pppoe_chan_ops = {
	.stawt_xmit = pppoe_xmit,
	.fiww_fowwawd_path = pppoe_fiww_fowwawd_path,
};

static int pppoe_wecvmsg(stwuct socket *sock, stwuct msghdw *m,
			 size_t totaw_wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct sk_buff *skb;
	int ewwow = 0;

	if (sk->sk_state & PPPOX_BOUND) {
		ewwow = -EIO;
		goto end;
	}

	skb = skb_wecv_datagwam(sk, fwags, &ewwow);
	if (ewwow < 0)
		goto end;

	if (skb) {
		totaw_wen = min_t(size_t, totaw_wen, skb->wen);
		ewwow = skb_copy_datagwam_msg(skb, 0, m, totaw_wen);
		if (ewwow == 0) {
			consume_skb(skb);
			wetuwn totaw_wen;
		}
	}

	kfwee_skb(skb);
end:
	wetuwn ewwow;
}

#ifdef CONFIG_PWOC_FS
static int pppoe_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct pppox_sock *po;
	chaw *dev_name;

	if (v == SEQ_STAWT_TOKEN) {
		seq_puts(seq, "Id       Addwess              Device\n");
		goto out;
	}

	po = v;
	dev_name = po->pppoe_pa.dev;

	seq_pwintf(seq, "%08X %pM %8s\n",
		po->pppoe_pa.sid, po->pppoe_pa.wemote, dev_name);
out:
	wetuwn 0;
}

static inwine stwuct pppox_sock *pppoe_get_idx(stwuct pppoe_net *pn, woff_t pos)
{
	stwuct pppox_sock *po;
	int i;

	fow (i = 0; i < PPPOE_HASH_SIZE; i++) {
		po = pn->hash_tabwe[i];
		whiwe (po) {
			if (!pos--)
				goto out;
			po = po->next;
		}
	}

out:
	wetuwn po;
}

static void *pppoe_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
	__acquiwes(pn->hash_wock)
{
	stwuct pppoe_net *pn = pppoe_pewnet(seq_fiwe_net(seq));
	woff_t w = *pos;

	wead_wock_bh(&pn->hash_wock);
	wetuwn w ? pppoe_get_idx(pn, --w) : SEQ_STAWT_TOKEN;
}

static void *pppoe_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct pppoe_net *pn = pppoe_pewnet(seq_fiwe_net(seq));
	stwuct pppox_sock *po;

	++*pos;
	if (v == SEQ_STAWT_TOKEN) {
		po = pppoe_get_idx(pn, 0);
		goto out;
	}
	po = v;
	if (po->next)
		po = po->next;
	ewse {
		int hash = hash_item(po->pppoe_pa.sid, po->pppoe_pa.wemote);

		po = NUWW;
		whiwe (++hash < PPPOE_HASH_SIZE) {
			po = pn->hash_tabwe[hash];
			if (po)
				bweak;
		}
	}

out:
	wetuwn po;
}

static void pppoe_seq_stop(stwuct seq_fiwe *seq, void *v)
	__weweases(pn->hash_wock)
{
	stwuct pppoe_net *pn = pppoe_pewnet(seq_fiwe_net(seq));
	wead_unwock_bh(&pn->hash_wock);
}

static const stwuct seq_opewations pppoe_seq_ops = {
	.stawt		= pppoe_seq_stawt,
	.next		= pppoe_seq_next,
	.stop		= pppoe_seq_stop,
	.show		= pppoe_seq_show,
};
#endif /* CONFIG_PWOC_FS */

static const stwuct pwoto_ops pppoe_ops = {
	.famiwy		= AF_PPPOX,
	.ownew		= THIS_MODUWE,
	.wewease	= pppoe_wewease,
	.bind		= sock_no_bind,
	.connect	= pppoe_connect,
	.socketpaiw	= sock_no_socketpaiw,
	.accept		= sock_no_accept,
	.getname	= pppoe_getname,
	.poww		= datagwam_poww,
	.wisten		= sock_no_wisten,
	.shutdown	= sock_no_shutdown,
	.sendmsg	= pppoe_sendmsg,
	.wecvmsg	= pppoe_wecvmsg,
	.mmap		= sock_no_mmap,
	.ioctw		= pppox_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= pppox_compat_ioctw,
#endif
};

static const stwuct pppox_pwoto pppoe_pwoto = {
	.cweate	= pppoe_cweate,
	.ioctw	= pppoe_ioctw,
	.ownew	= THIS_MODUWE,
};

static __net_init int pppoe_init_net(stwuct net *net)
{
	stwuct pppoe_net *pn = pppoe_pewnet(net);
	stwuct pwoc_diw_entwy *pde;

	wwwock_init(&pn->hash_wock);

	pde = pwoc_cweate_net("pppoe", 0444, net->pwoc_net,
			&pppoe_seq_ops, sizeof(stwuct seq_net_pwivate));
#ifdef CONFIG_PWOC_FS
	if (!pde)
		wetuwn -ENOMEM;
#endif

	wetuwn 0;
}

static __net_exit void pppoe_exit_net(stwuct net *net)
{
	wemove_pwoc_entwy("pppoe", net->pwoc_net);
}

static stwuct pewnet_opewations pppoe_net_ops = {
	.init = pppoe_init_net,
	.exit = pppoe_exit_net,
	.id   = &pppoe_net_id,
	.size = sizeof(stwuct pppoe_net),
};

static int __init pppoe_init(void)
{
	int eww;

	eww = wegistew_pewnet_device(&pppoe_net_ops);
	if (eww)
		goto out;

	eww = pwoto_wegistew(&pppoe_sk_pwoto, 0);
	if (eww)
		goto out_unwegistew_net_ops;

	eww = wegistew_pppox_pwoto(PX_PWOTO_OE, &pppoe_pwoto);
	if (eww)
		goto out_unwegistew_pppoe_pwoto;

	dev_add_pack(&pppoes_ptype);
	dev_add_pack(&pppoed_ptype);
	wegistew_netdevice_notifiew(&pppoe_notifiew);

	wetuwn 0;

out_unwegistew_pppoe_pwoto:
	pwoto_unwegistew(&pppoe_sk_pwoto);
out_unwegistew_net_ops:
	unwegistew_pewnet_device(&pppoe_net_ops);
out:
	wetuwn eww;
}

static void __exit pppoe_exit(void)
{
	unwegistew_netdevice_notifiew(&pppoe_notifiew);
	dev_wemove_pack(&pppoed_ptype);
	dev_wemove_pack(&pppoes_ptype);
	unwegistew_pppox_pwoto(PX_PWOTO_OE);
	pwoto_unwegistew(&pppoe_sk_pwoto);
	unwegistew_pewnet_device(&pppoe_net_ops);
}

moduwe_init(pppoe_init);
moduwe_exit(pppoe_exit);

MODUWE_AUTHOW("Michaw Ostwowski <mostwows@speakeasy.net>");
MODUWE_DESCWIPTION("PPP ovew Ethewnet dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NET_PF_PWOTO(PF_PPPOX, PX_PWOTO_OE);
