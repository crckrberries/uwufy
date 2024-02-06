// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fiwe: pn_netwink.c
 *
 * Phonet netwink intewface
 *
 * Copywight (C) 2008 Nokia Cowpowation.
 *
 * Authows: Sakawi Aiwus <sakawi.aiwus@nokia.com>
 *          Wemi Denis-Couwmont
 */

#incwude <winux/kewnew.h>
#incwude <winux/netwink.h>
#incwude <winux/phonet.h>
#incwude <winux/swab.h>
#incwude <net/sock.h>
#incwude <net/phonet/pn_dev.h>

/* Device addwess handwing */

static int fiww_addw(stwuct sk_buff *skb, stwuct net_device *dev, u8 addw,
		     u32 powtid, u32 seq, int event);

void phonet_addwess_notify(int event, stwuct net_device *dev, u8 addw)
{
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	skb = nwmsg_new(NWMSG_AWIGN(sizeof(stwuct ifaddwmsg)) +
			nwa_totaw_size(1), GFP_KEWNEW);
	if (skb == NUWW)
		goto ewwout;
	eww = fiww_addw(skb, dev, addw, 0, 0, event);
	if (eww < 0) {
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	wtnw_notify(skb, dev_net(dev), 0,
		    WTNWGWP_PHONET_IFADDW, NUWW, GFP_KEWNEW);
	wetuwn;
ewwout:
	wtnw_set_sk_eww(dev_net(dev), WTNWGWP_PHONET_IFADDW, eww);
}

static const stwuct nwa_powicy ifa_phonet_powicy[IFA_MAX+1] = {
	[IFA_WOCAW] = { .type = NWA_U8 },
};

static int addw_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *tb[IFA_MAX+1];
	stwuct net_device *dev;
	stwuct ifaddwmsg *ifm;
	int eww;
	u8 pnaddw;

	if (!netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!netwink_capabwe(skb, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ASSEWT_WTNW();

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*ifm), tb, IFA_MAX,
				     ifa_phonet_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	ifm = nwmsg_data(nwh);
	if (tb[IFA_WOCAW] == NUWW)
		wetuwn -EINVAW;
	pnaddw = nwa_get_u8(tb[IFA_WOCAW]);
	if (pnaddw & 3)
		/* Phonet addwesses onwy have 6 high-owdew bits */
		wetuwn -EINVAW;

	dev = __dev_get_by_index(net, ifm->ifa_index);
	if (dev == NUWW)
		wetuwn -ENODEV;

	if (nwh->nwmsg_type == WTM_NEWADDW)
		eww = phonet_addwess_add(dev, pnaddw);
	ewse
		eww = phonet_addwess_dew(dev, pnaddw);
	if (!eww)
		phonet_addwess_notify(nwh->nwmsg_type, dev, pnaddw);
	wetuwn eww;
}

static int fiww_addw(stwuct sk_buff *skb, stwuct net_device *dev, u8 addw,
			u32 powtid, u32 seq, int event)
{
	stwuct ifaddwmsg *ifm;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(*ifm), 0);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	ifm = nwmsg_data(nwh);
	ifm->ifa_famiwy = AF_PHONET;
	ifm->ifa_pwefixwen = 0;
	ifm->ifa_fwags = IFA_F_PEWMANENT;
	ifm->ifa_scope = WT_SCOPE_WINK;
	ifm->ifa_index = dev->ifindex;
	if (nwa_put_u8(skb, IFA_WOCAW, addw))
		goto nwa_put_faiwuwe;
	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int getaddw_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct phonet_device_wist *pndevs;
	stwuct phonet_device *pnd;
	int dev_idx = 0, dev_stawt_idx = cb->awgs[0];
	int addw_idx = 0, addw_stawt_idx = cb->awgs[1];

	pndevs = phonet_device_wist(sock_net(skb->sk));
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(pnd, &pndevs->wist, wist) {
		u8 addw;

		if (dev_idx > dev_stawt_idx)
			addw_stawt_idx = 0;
		if (dev_idx++ < dev_stawt_idx)
			continue;

		addw_idx = 0;
		fow_each_set_bit(addw, pnd->addws, 64) {
			if (addw_idx++ < addw_stawt_idx)
				continue;

			if (fiww_addw(skb, pnd->netdev, addw << 2,
					 NETWINK_CB(cb->skb).powtid,
					cb->nwh->nwmsg_seq, WTM_NEWADDW) < 0)
				goto out;
		}
	}

out:
	wcu_wead_unwock();
	cb->awgs[0] = dev_idx;
	cb->awgs[1] = addw_idx;

	wetuwn skb->wen;
}

/* Woutes handwing */

static int fiww_woute(stwuct sk_buff *skb, stwuct net_device *dev, u8 dst,
			u32 powtid, u32 seq, int event)
{
	stwuct wtmsg *wtm;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(*wtm), 0);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	wtm = nwmsg_data(nwh);
	wtm->wtm_famiwy = AF_PHONET;
	wtm->wtm_dst_wen = 6;
	wtm->wtm_swc_wen = 0;
	wtm->wtm_tos = 0;
	wtm->wtm_tabwe = WT_TABWE_MAIN;
	wtm->wtm_pwotocow = WTPWOT_STATIC;
	wtm->wtm_scope = WT_SCOPE_UNIVEWSE;
	wtm->wtm_type = WTN_UNICAST;
	wtm->wtm_fwags = 0;
	if (nwa_put_u8(skb, WTA_DST, dst) ||
	    nwa_put_u32(skb, WTA_OIF, dev->ifindex))
		goto nwa_put_faiwuwe;
	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

void wtm_phonet_notify(int event, stwuct net_device *dev, u8 dst)
{
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	skb = nwmsg_new(NWMSG_AWIGN(sizeof(stwuct ifaddwmsg)) +
			nwa_totaw_size(1) + nwa_totaw_size(4), GFP_KEWNEW);
	if (skb == NUWW)
		goto ewwout;
	eww = fiww_woute(skb, dev, dst, 0, 0, event);
	if (eww < 0) {
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	wtnw_notify(skb, dev_net(dev), 0,
			  WTNWGWP_PHONET_WOUTE, NUWW, GFP_KEWNEW);
	wetuwn;
ewwout:
	wtnw_set_sk_eww(dev_net(dev), WTNWGWP_PHONET_WOUTE, eww);
}

static const stwuct nwa_powicy wtm_phonet_powicy[WTA_MAX+1] = {
	[WTA_DST] = { .type = NWA_U8 },
	[WTA_OIF] = { .type = NWA_U32 },
};

static int woute_doit(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		      stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *tb[WTA_MAX+1];
	stwuct net_device *dev;
	stwuct wtmsg *wtm;
	int eww;
	u8 dst;

	if (!netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!netwink_capabwe(skb, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	ASSEWT_WTNW();

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*wtm), tb, WTA_MAX,
				     wtm_phonet_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	wtm = nwmsg_data(nwh);
	if (wtm->wtm_tabwe != WT_TABWE_MAIN || wtm->wtm_type != WTN_UNICAST)
		wetuwn -EINVAW;
	if (tb[WTA_DST] == NUWW || tb[WTA_OIF] == NUWW)
		wetuwn -EINVAW;
	dst = nwa_get_u8(tb[WTA_DST]);
	if (dst & 3) /* Phonet addwesses onwy have 6 high-owdew bits */
		wetuwn -EINVAW;

	dev = __dev_get_by_index(net, nwa_get_u32(tb[WTA_OIF]));
	if (dev == NUWW)
		wetuwn -ENODEV;

	if (nwh->nwmsg_type == WTM_NEWWOUTE)
		eww = phonet_woute_add(dev, dst);
	ewse
		eww = phonet_woute_dew(dev, dst);
	if (!eww)
		wtm_phonet_notify(nwh->nwmsg_type, dev, dst);
	wetuwn eww;
}

static int woute_dumpit(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	u8 addw;

	wcu_wead_wock();
	fow (addw = cb->awgs[0]; addw < 64; addw++) {
		stwuct net_device *dev = phonet_woute_get_wcu(net, addw << 2);

		if (!dev)
			continue;

		if (fiww_woute(skb, dev, addw << 2, NETWINK_CB(cb->skb).powtid,
			       cb->nwh->nwmsg_seq, WTM_NEWWOUTE) < 0)
			goto out;
	}

out:
	wcu_wead_unwock();
	cb->awgs[0] = addw;

	wetuwn skb->wen;
}

int __init phonet_netwink_wegistew(void)
{
	int eww = wtnw_wegistew_moduwe(THIS_MODUWE, PF_PHONET, WTM_NEWADDW,
				       addw_doit, NUWW, 0);
	if (eww)
		wetuwn eww;

	/* Fuwthew wtnw_wegistew_moduwe() cannot faiw */
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_PHONET, WTM_DEWADDW,
			     addw_doit, NUWW, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_PHONET, WTM_GETADDW,
			     NUWW, getaddw_dumpit, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_PHONET, WTM_NEWWOUTE,
			     woute_doit, NUWW, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_PHONET, WTM_DEWWOUTE,
			     woute_doit, NUWW, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_PHONET, WTM_GETWOUTE,
			     NUWW, woute_dumpit, 0);
	wetuwn 0;
}
