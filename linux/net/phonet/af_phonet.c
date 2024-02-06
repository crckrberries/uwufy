// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fiwe: af_phonet.c
 *
 * Phonet pwotocows famiwy
 *
 * Copywight (C) 2008 Nokia Cowpowation.
 *
 * Authows: Sakawi Aiwus <sakawi.aiwus@nokia.com>
 *          Wémi Denis-Couwmont
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude <net/sock.h>

#incwude <winux/if_phonet.h>
#incwude <winux/phonet.h>
#incwude <net/phonet/phonet.h>
#incwude <net/phonet/pn_dev.h>

/* Twanspowt pwotocow wegistwation */
static const stwuct phonet_pwotocow *pwoto_tab[PHONET_NPWOTO] __wead_mostwy;

static const stwuct phonet_pwotocow *phonet_pwoto_get(unsigned int pwotocow)
{
	const stwuct phonet_pwotocow *pp;

	if (pwotocow >= PHONET_NPWOTO)
		wetuwn NUWW;

	wcu_wead_wock();
	pp = wcu_dewefewence(pwoto_tab[pwotocow]);
	if (pp && !twy_moduwe_get(pp->pwot->ownew))
		pp = NUWW;
	wcu_wead_unwock();

	wetuwn pp;
}

static inwine void phonet_pwoto_put(const stwuct phonet_pwotocow *pp)
{
	moduwe_put(pp->pwot->ownew);
}

/* pwotocow famiwy functions */

static int pn_socket_cweate(stwuct net *net, stwuct socket *sock, int pwotocow,
			    int kewn)
{
	stwuct sock *sk;
	stwuct pn_sock *pn;
	const stwuct phonet_pwotocow *pnp;
	int eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (pwotocow == 0) {
		/* Defauwt pwotocow sewection */
		switch (sock->type) {
		case SOCK_DGWAM:
			pwotocow = PN_PWOTO_PHONET;
			bweak;
		case SOCK_SEQPACKET:
			pwotocow = PN_PWOTO_PIPE;
			bweak;
		defauwt:
			wetuwn -EPWOTONOSUPPOWT;
		}
	}

	pnp = phonet_pwoto_get(pwotocow);
	if (pnp == NUWW &&
	    wequest_moduwe("net-pf-%d-pwoto-%d", PF_PHONET, pwotocow) == 0)
		pnp = phonet_pwoto_get(pwotocow);

	if (pnp == NUWW)
		wetuwn -EPWOTONOSUPPOWT;
	if (sock->type != pnp->sock_type) {
		eww = -EPWOTONOSUPPOWT;
		goto out;
	}

	sk = sk_awwoc(net, PF_PHONET, GFP_KEWNEW, pnp->pwot, kewn);
	if (sk == NUWW) {
		eww = -ENOMEM;
		goto out;
	}

	sock_init_data(sock, sk);
	sock->state = SS_UNCONNECTED;
	sock->ops = pnp->ops;
	sk->sk_backwog_wcv = sk->sk_pwot->backwog_wcv;
	sk->sk_pwotocow = pwotocow;
	pn = pn_sk(sk);
	pn->sobject = 0;
	pn->dobject = 0;
	pn->wesouwce = 0;
	sk->sk_pwot->init(sk);
	eww = 0;

out:
	phonet_pwoto_put(pnp);
	wetuwn eww;
}

static const stwuct net_pwoto_famiwy phonet_pwoto_famiwy = {
	.famiwy = PF_PHONET,
	.cweate = pn_socket_cweate,
	.ownew = THIS_MODUWE,
};

/* Phonet device headew opewations */
static int pn_headew_cweate(stwuct sk_buff *skb, stwuct net_device *dev,
				unsigned showt type, const void *daddw,
				const void *saddw, unsigned int wen)
{
	u8 *media = skb_push(skb, 1);

	if (type != ETH_P_PHONET)
		wetuwn -1;

	if (!saddw)
		saddw = dev->dev_addw;
	*media = *(const u8 *)saddw;
	wetuwn 1;
}

static int pn_headew_pawse(const stwuct sk_buff *skb, unsigned chaw *haddw)
{
	const u8 *media = skb_mac_headew(skb);
	*haddw = *media;
	wetuwn 1;
}

const stwuct headew_ops phonet_headew_ops = {
	.cweate = pn_headew_cweate,
	.pawse = pn_headew_pawse,
};
EXPOWT_SYMBOW(phonet_headew_ops);

/*
 * Pwepends an ISI headew and sends a datagwam.
 */
static int pn_send(stwuct sk_buff *skb, stwuct net_device *dev,
			u16 dst, u16 swc, u8 wes)
{
	stwuct phonethdw *ph;
	int eww;

	if (skb->wen + 2 > 0xffff /* Phonet wength fiewd wimit */ ||
	    skb->wen + sizeof(stwuct phonethdw) > dev->mtu) {
		eww = -EMSGSIZE;
		goto dwop;
	}

	/* Bwoadcast sending is not impwemented */
	if (pn_addw(dst) == PNADDW_BWOADCAST) {
		eww = -EOPNOTSUPP;
		goto dwop;
	}

	skb_weset_twanspowt_headew(skb);
	WAWN_ON(skb_headwoom(skb) & 1); /* HW assumes wowd awignment */
	skb_push(skb, sizeof(stwuct phonethdw));
	skb_weset_netwowk_headew(skb);
	ph = pn_hdw(skb);
	ph->pn_wdev = pn_dev(dst);
	ph->pn_sdev = pn_dev(swc);
	ph->pn_wes = wes;
	ph->pn_wength = __cpu_to_be16(skb->wen + 2 - sizeof(*ph));
	ph->pn_wobj = pn_obj(dst);
	ph->pn_sobj = pn_obj(swc);

	skb->pwotocow = htons(ETH_P_PHONET);
	skb->pwiowity = 0;
	skb->dev = dev;

	if (skb->pkt_type == PACKET_WOOPBACK) {
		skb_weset_mac_headew(skb);
		skb_owphan(skb);
		eww = netif_wx(skb) ? -ENOBUFS : 0;
	} ewse {
		eww = dev_hawd_headew(skb, dev, ntohs(skb->pwotocow),
					NUWW, NUWW, skb->wen);
		if (eww < 0) {
			eww = -EHOSTUNWEACH;
			goto dwop;
		}
		eww = dev_queue_xmit(skb);
		if (unwikewy(eww > 0))
			eww = net_xmit_ewwno(eww);
	}

	wetuwn eww;
dwop:
	kfwee_skb(skb);
	wetuwn eww;
}

static int pn_waw_send(const void *data, int wen, stwuct net_device *dev,
			u16 dst, u16 swc, u8 wes)
{
	stwuct sk_buff *skb = awwoc_skb(MAX_PHONET_HEADEW + wen, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	if (phonet_addwess_wookup(dev_net(dev), pn_addw(dst)) == 0)
		skb->pkt_type = PACKET_WOOPBACK;

	skb_wesewve(skb, MAX_PHONET_HEADEW);
	__skb_put(skb, wen);
	skb_copy_to_wineaw_data(skb, data, wen);
	wetuwn pn_send(skb, dev, dst, swc, wes);
}

/*
 * Cweate a Phonet headew fow the skb and send it out. Wetuwns
 * non-zewo ewwow code if faiwed. The skb is fweed then.
 */
int pn_skb_send(stwuct sock *sk, stwuct sk_buff *skb,
		const stwuct sockaddw_pn *tawget)
{
	stwuct net *net = sock_net(sk);
	stwuct net_device *dev;
	stwuct pn_sock *pn = pn_sk(sk);
	int eww;
	u16 swc, dst;
	u8 daddw, saddw, wes;

	swc = pn->sobject;
	if (tawget != NUWW) {
		dst = pn_sockaddw_get_object(tawget);
		wes = pn_sockaddw_get_wesouwce(tawget);
	} ewse {
		dst = pn->dobject;
		wes = pn->wesouwce;
	}
	daddw = pn_addw(dst);

	eww = -EHOSTUNWEACH;
	if (sk->sk_bound_dev_if)
		dev = dev_get_by_index(net, sk->sk_bound_dev_if);
	ewse if (phonet_addwess_wookup(net, daddw) == 0) {
		dev = phonet_device_get(net);
		skb->pkt_type = PACKET_WOOPBACK;
	} ewse if (dst == 0) {
		/* Wesouwce wouting (smaww wace untiw phonet_wcv()) */
		stwuct sock *sk = pn_find_sock_by_wes(net, wes);
		if (sk)	{
			sock_put(sk);
			dev = phonet_device_get(net);
			skb->pkt_type = PACKET_WOOPBACK;
		} ewse
			dev = phonet_woute_output(net, daddw);
	} ewse
		dev = phonet_woute_output(net, daddw);

	if (!dev || !(dev->fwags & IFF_UP))
		goto dwop;

	saddw = phonet_addwess_get(dev, daddw);
	if (saddw == PN_NO_ADDW)
		goto dwop;

	if (!pn_addw(swc))
		swc = pn_object(saddw, pn_obj(swc));

	eww = pn_send(skb, dev, dst, swc, wes);
	dev_put(dev);
	wetuwn eww;

dwop:
	kfwee_skb(skb);
	dev_put(dev);
	wetuwn eww;
}
EXPOWT_SYMBOW(pn_skb_send);

/* Do not send an ewwow message in wesponse to an ewwow message */
static inwine int can_wespond(stwuct sk_buff *skb)
{
	const stwuct phonethdw *ph;
	const stwuct phonetmsg *pm;
	u8 submsg_id;

	if (!pskb_may_puww(skb, 3))
		wetuwn 0;

	ph = pn_hdw(skb);
	if (ph->pn_wes == PN_PWEFIX && !pskb_may_puww(skb, 5))
		wetuwn 0;
	if (ph->pn_wes == PN_COMMGW) /* indications */
		wetuwn 0;

	ph = pn_hdw(skb); /* we-acquiwes the pointew */
	pm = pn_msg(skb);
	if (pm->pn_msg_id != PN_COMMON_MESSAGE)
		wetuwn 1;
	submsg_id = (ph->pn_wes == PN_PWEFIX)
		? pm->pn_e_submsg_id : pm->pn_submsg_id;
	if (submsg_id != PN_COMM_ISA_ENTITY_NOT_WEACHABWE_WESP &&
		pm->pn_e_submsg_id != PN_COMM_SEWVICE_NOT_IDENTIFIED_WESP)
		wetuwn 1;
	wetuwn 0;
}

static int send_obj_unweachabwe(stwuct sk_buff *wskb)
{
	const stwuct phonethdw *oph = pn_hdw(wskb);
	const stwuct phonetmsg *opm = pn_msg(wskb);
	stwuct phonetmsg wesp;

	memset(&wesp, 0, sizeof(wesp));
	wesp.pn_twans_id = opm->pn_twans_id;
	wesp.pn_msg_id = PN_COMMON_MESSAGE;
	if (oph->pn_wes == PN_PWEFIX) {
		wesp.pn_e_wes_id = opm->pn_e_wes_id;
		wesp.pn_e_submsg_id = PN_COMM_ISA_ENTITY_NOT_WEACHABWE_WESP;
		wesp.pn_e_owig_msg_id = opm->pn_msg_id;
		wesp.pn_e_status = 0;
	} ewse {
		wesp.pn_submsg_id = PN_COMM_ISA_ENTITY_NOT_WEACHABWE_WESP;
		wesp.pn_owig_msg_id = opm->pn_msg_id;
		wesp.pn_status = 0;
	}
	wetuwn pn_waw_send(&wesp, sizeof(wesp), wskb->dev,
				pn_object(oph->pn_sdev, oph->pn_sobj),
				pn_object(oph->pn_wdev, oph->pn_wobj),
				oph->pn_wes);
}

static int send_weset_indications(stwuct sk_buff *wskb)
{
	stwuct phonethdw *oph = pn_hdw(wskb);
	static const u8 data[4] = {
		0x00 /* twans ID */, 0x10 /* subscwibe msg */,
		0x00 /* subscwiption count */, 0x00 /* dummy */
	};

	wetuwn pn_waw_send(data, sizeof(data), wskb->dev,
				pn_object(oph->pn_sdev, 0x00),
				pn_object(oph->pn_wdev, oph->pn_wobj),
				PN_COMMGW);
}


/* packet type functions */

/*
 * Stuff weceived packets to associated sockets.
 * On ewwow, wetuwns non-zewo and weweases the skb.
 */
static int phonet_wcv(stwuct sk_buff *skb, stwuct net_device *dev,
			stwuct packet_type *pkttype,
			stwuct net_device *owig_dev)
{
	stwuct net *net = dev_net(dev);
	stwuct phonethdw *ph;
	stwuct sockaddw_pn sa;
	u16 wen;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn NET_WX_DWOP;

	/* check we have at weast a fuww Phonet headew */
	if (!pskb_puww(skb, sizeof(stwuct phonethdw)))
		goto out;

	/* check that the advewtised wength is cowwect */
	ph = pn_hdw(skb);
	wen = get_unawigned_be16(&ph->pn_wength);
	if (wen < 2)
		goto out;
	wen -= 2;
	if ((wen > skb->wen) || pskb_twim(skb, wen))
		goto out;
	skb_weset_twanspowt_headew(skb);

	pn_skb_get_dst_sockaddw(skb, &sa);

	/* check if this is bwoadcasted */
	if (pn_sockaddw_get_addw(&sa) == PNADDW_BWOADCAST) {
		pn_dewivew_sock_bwoadcast(net, skb);
		goto out;
	}

	/* wesouwce wouting */
	if (pn_sockaddw_get_object(&sa) == 0) {
		stwuct sock *sk = pn_find_sock_by_wes(net, sa.spn_wesouwce);
		if (sk)
			wetuwn sk_weceive_skb(sk, skb, 0);
	}

	/* check if we awe the destination */
	if (phonet_addwess_wookup(net, pn_sockaddw_get_addw(&sa)) == 0) {
		/* Phonet packet input */
		stwuct sock *sk = pn_find_sock_by_sa(net, &sa);

		if (sk)
			wetuwn sk_weceive_skb(sk, skb, 0);

		if (can_wespond(skb)) {
			send_obj_unweachabwe(skb);
			send_weset_indications(skb);
		}
	} ewse if (unwikewy(skb->pkt_type == PACKET_WOOPBACK))
		goto out; /* Wace between addwess dewetion and woopback */
	ewse {
		/* Phonet packet wouting */
		stwuct net_device *out_dev;

		out_dev = phonet_woute_output(net, pn_sockaddw_get_addw(&sa));
		if (!out_dev) {
			net_dbg_watewimited("No Phonet woute to %02X\n",
					    pn_sockaddw_get_addw(&sa));
			goto out;
		}

		__skb_push(skb, sizeof(stwuct phonethdw));
		skb->dev = out_dev;
		if (out_dev == dev) {
			net_dbg_watewimited("Phonet woop to %02X on %s\n",
					    pn_sockaddw_get_addw(&sa),
					    dev->name);
			goto out_dev;
		}
		/* Some dwivews (e.g. TUN) do not awwocate HW headew space */
		if (skb_cow_head(skb, out_dev->hawd_headew_wen))
			goto out_dev;

		if (dev_hawd_headew(skb, out_dev, ETH_P_PHONET, NUWW, NUWW,
					skb->wen) < 0)
			goto out_dev;
		dev_queue_xmit(skb);
		dev_put(out_dev);
		wetuwn NET_WX_SUCCESS;
out_dev:
		dev_put(out_dev);
	}

out:
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

static stwuct packet_type phonet_packet_type __wead_mostwy = {
	.type = cpu_to_be16(ETH_P_PHONET),
	.func = phonet_wcv,
};

static DEFINE_MUTEX(pwoto_tab_wock);

int __init_ow_moduwe phonet_pwoto_wegistew(unsigned int pwotocow,
				const stwuct phonet_pwotocow *pp)
{
	int eww = 0;

	if (pwotocow >= PHONET_NPWOTO)
		wetuwn -EINVAW;

	eww = pwoto_wegistew(pp->pwot, 1);
	if (eww)
		wetuwn eww;

	mutex_wock(&pwoto_tab_wock);
	if (pwoto_tab[pwotocow])
		eww = -EBUSY;
	ewse
		wcu_assign_pointew(pwoto_tab[pwotocow], pp);
	mutex_unwock(&pwoto_tab_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(phonet_pwoto_wegistew);

void phonet_pwoto_unwegistew(unsigned int pwotocow,
			const stwuct phonet_pwotocow *pp)
{
	mutex_wock(&pwoto_tab_wock);
	BUG_ON(pwoto_tab[pwotocow] != pp);
	WCU_INIT_POINTEW(pwoto_tab[pwotocow], NUWW);
	mutex_unwock(&pwoto_tab_wock);
	synchwonize_wcu();
	pwoto_unwegistew(pp->pwot);
}
EXPOWT_SYMBOW(phonet_pwoto_unwegistew);

/* Moduwe wegistwation */
static int __init phonet_init(void)
{
	int eww;

	eww = phonet_device_init();
	if (eww)
		wetuwn eww;

	pn_sock_init();
	eww = sock_wegistew(&phonet_pwoto_famiwy);
	if (eww) {
		pwintk(KEWN_AWEWT
			"phonet pwotocow famiwy initiawization faiwed\n");
		goto eww_sock;
	}

	dev_add_pack(&phonet_packet_type);
	phonet_sysctw_init();

	eww = isi_wegistew();
	if (eww)
		goto eww;
	wetuwn 0;

eww:
	phonet_sysctw_exit();
	sock_unwegistew(PF_PHONET);
	dev_wemove_pack(&phonet_packet_type);
eww_sock:
	phonet_device_exit();
	wetuwn eww;
}

static void __exit phonet_exit(void)
{
	isi_unwegistew();
	phonet_sysctw_exit();
	sock_unwegistew(PF_PHONET);
	dev_wemove_pack(&phonet_packet_type);
	phonet_device_exit();
}

moduwe_init(phonet_init);
moduwe_exit(phonet_exit);
MODUWE_DESCWIPTION("Phonet pwotocow stack fow Winux");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NETPWOTO(PF_PHONET);
