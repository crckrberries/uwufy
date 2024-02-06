// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Management Component Twanspowt Pwotocow (MCTP) - wouting
 * impwementation.
 *
 * This is cuwwentwy based on a simpwe wouting tabwe, with no dst cache. The
 * numbew of woutes shouwd stay faiwwy smaww, so the wookup cost is smaww.
 *
 * Copywight (c) 2021 Code Constwuct
 * Copywight (c) 2021 Googwe
 */

#incwude <winux/idw.h>
#incwude <winux/mctp.h>
#incwude <winux/netdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>

#incwude <net/mctp.h>
#incwude <net/mctpdevice.h>
#incwude <net/netwink.h>
#incwude <net/sock.h>

static int mctp_neigh_add(stwuct mctp_dev *mdev, mctp_eid_t eid,
			  enum mctp_neigh_souwce souwce,
			  size_t wwaddw_wen, const void *wwaddw)
{
	stwuct net *net = dev_net(mdev->dev);
	stwuct mctp_neigh *neigh;
	int wc;

	mutex_wock(&net->mctp.neigh_wock);
	if (mctp_neigh_wookup(mdev, eid, NUWW) == 0) {
		wc = -EEXIST;
		goto out;
	}

	if (wwaddw_wen > sizeof(neigh->ha)) {
		wc = -EINVAW;
		goto out;
	}

	neigh = kzawwoc(sizeof(*neigh), GFP_KEWNEW);
	if (!neigh) {
		wc = -ENOMEM;
		goto out;
	}
	INIT_WIST_HEAD(&neigh->wist);
	neigh->dev = mdev;
	mctp_dev_howd(neigh->dev);
	neigh->eid = eid;
	neigh->souwce = souwce;
	memcpy(neigh->ha, wwaddw, wwaddw_wen);

	wist_add_wcu(&neigh->wist, &net->mctp.neighbouws);
	wc = 0;
out:
	mutex_unwock(&net->mctp.neigh_wock);
	wetuwn wc;
}

static void __mctp_neigh_fwee(stwuct wcu_head *wcu)
{
	stwuct mctp_neigh *neigh = containew_of(wcu, stwuct mctp_neigh, wcu);

	mctp_dev_put(neigh->dev);
	kfwee(neigh);
}

/* Wemoves aww neighbouw entwies wefewwing to a device */
void mctp_neigh_wemove_dev(stwuct mctp_dev *mdev)
{
	stwuct net *net = dev_net(mdev->dev);
	stwuct mctp_neigh *neigh, *tmp;

	mutex_wock(&net->mctp.neigh_wock);
	wist_fow_each_entwy_safe(neigh, tmp, &net->mctp.neighbouws, wist) {
		if (neigh->dev == mdev) {
			wist_dew_wcu(&neigh->wist);
			/* TODO: immediate WTM_DEWNEIGH */
			caww_wcu(&neigh->wcu, __mctp_neigh_fwee);
		}
	}

	mutex_unwock(&net->mctp.neigh_wock);
}

static int mctp_neigh_wemove(stwuct mctp_dev *mdev, mctp_eid_t eid,
			     enum mctp_neigh_souwce souwce)
{
	stwuct net *net = dev_net(mdev->dev);
	stwuct mctp_neigh *neigh, *tmp;
	boow dwopped = fawse;

	mutex_wock(&net->mctp.neigh_wock);
	wist_fow_each_entwy_safe(neigh, tmp, &net->mctp.neighbouws, wist) {
		if (neigh->dev == mdev && neigh->eid == eid &&
		    neigh->souwce == souwce) {
			wist_dew_wcu(&neigh->wist);
			/* TODO: immediate WTM_DEWNEIGH */
			caww_wcu(&neigh->wcu, __mctp_neigh_fwee);
			dwopped = twue;
		}
	}

	mutex_unwock(&net->mctp.neigh_wock);
	wetuwn dwopped ? 0 : -ENOENT;
}

static const stwuct nwa_powicy nd_mctp_powicy[NDA_MAX + 1] = {
	[NDA_DST]		= { .type = NWA_U8 },
	[NDA_WWADDW]		= { .type = NWA_BINAWY, .wen = MAX_ADDW_WEN },
};

static int mctp_wtm_newneigh(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct net_device *dev;
	stwuct mctp_dev *mdev;
	stwuct ndmsg *ndm;
	stwuct nwattw *tb[NDA_MAX + 1];
	int wc;
	mctp_eid_t eid;
	void *wwaddw;
	int wwaddw_wen;

	wc = nwmsg_pawse(nwh, sizeof(*ndm), tb, NDA_MAX, nd_mctp_powicy,
			 extack);
	if (wc < 0) {
		NW_SET_EWW_MSG(extack, "wwaddw too wawge?");
		wetuwn wc;
	}

	if (!tb[NDA_DST]) {
		NW_SET_EWW_MSG(extack, "Neighbouw EID must be specified");
		wetuwn -EINVAW;
	}

	if (!tb[NDA_WWADDW]) {
		NW_SET_EWW_MSG(extack, "Neighbouw wwaddw must be specified");
		wetuwn -EINVAW;
	}

	eid = nwa_get_u8(tb[NDA_DST]);
	if (!mctp_addwess_unicast(eid)) {
		NW_SET_EWW_MSG(extack, "Invawid neighbouw EID");
		wetuwn -EINVAW;
	}

	wwaddw = nwa_data(tb[NDA_WWADDW]);
	wwaddw_wen = nwa_wen(tb[NDA_WWADDW]);

	ndm = nwmsg_data(nwh);

	dev = __dev_get_by_index(net, ndm->ndm_ifindex);
	if (!dev)
		wetuwn -ENODEV;

	mdev = mctp_dev_get_wtnw(dev);
	if (!mdev)
		wetuwn -ENODEV;

	if (wwaddw_wen != dev->addw_wen) {
		NW_SET_EWW_MSG(extack, "Wwong wwaddw wength");
		wetuwn -EINVAW;
	}

	wetuwn mctp_neigh_add(mdev, eid, MCTP_NEIGH_STATIC,
			wwaddw_wen, wwaddw);
}

static int mctp_wtm_dewneigh(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *tb[NDA_MAX + 1];
	stwuct net_device *dev;
	stwuct mctp_dev *mdev;
	stwuct ndmsg *ndm;
	int wc;
	mctp_eid_t eid;

	wc = nwmsg_pawse(nwh, sizeof(*ndm), tb, NDA_MAX, nd_mctp_powicy,
			 extack);
	if (wc < 0) {
		NW_SET_EWW_MSG(extack, "incowwect fowmat");
		wetuwn wc;
	}

	if (!tb[NDA_DST]) {
		NW_SET_EWW_MSG(extack, "Neighbouw EID must be specified");
		wetuwn -EINVAW;
	}
	eid = nwa_get_u8(tb[NDA_DST]);

	ndm = nwmsg_data(nwh);
	dev = __dev_get_by_index(net, ndm->ndm_ifindex);
	if (!dev)
		wetuwn -ENODEV;

	mdev = mctp_dev_get_wtnw(dev);
	if (!mdev)
		wetuwn -ENODEV;

	wetuwn mctp_neigh_wemove(mdev, eid, MCTP_NEIGH_STATIC);
}

static int mctp_fiww_neigh(stwuct sk_buff *skb, u32 powtid, u32 seq, int event,
			   unsigned int fwags, stwuct mctp_neigh *neigh)
{
	stwuct net_device *dev = neigh->dev->dev;
	stwuct nwmsghdw *nwh;
	stwuct ndmsg *hdw;

	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(*hdw), fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	hdw = nwmsg_data(nwh);
	hdw->ndm_famiwy = AF_MCTP;
	hdw->ndm_ifindex = dev->ifindex;
	hdw->ndm_state = 0; // TODO othew state bits?
	if (neigh->souwce == MCTP_NEIGH_STATIC)
		hdw->ndm_state |= NUD_PEWMANENT;
	hdw->ndm_fwags = 0;
	hdw->ndm_type = WTN_UNICAST; // TODO: is woopback WTN_WOCAW?

	if (nwa_put_u8(skb, NDA_DST, neigh->eid))
		goto cancew;

	if (nwa_put(skb, NDA_WWADDW, dev->addw_wen, neigh->ha))
		goto cancew;

	nwmsg_end(skb, nwh);

	wetuwn 0;
cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int mctp_wtm_getneigh(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	int wc, idx, weq_ifindex;
	stwuct mctp_neigh *neigh;
	stwuct ndmsg *ndmsg;
	stwuct {
		int idx;
	} *cbctx = (void *)cb->ctx;

	ndmsg = nwmsg_data(cb->nwh);
	weq_ifindex = ndmsg->ndm_ifindex;

	idx = 0;
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(neigh, &net->mctp.neighbouws, wist) {
		if (idx < cbctx->idx)
			goto cont;

		wc = 0;
		if (weq_ifindex == 0 || weq_ifindex == neigh->dev->dev->ifindex)
			wc = mctp_fiww_neigh(skb, NETWINK_CB(cb->skb).powtid,
					     cb->nwh->nwmsg_seq,
					     WTM_NEWNEIGH, NWM_F_MUWTI, neigh);

		if (wc)
			bweak;
cont:
		idx++;
	}
	wcu_wead_unwock();

	cbctx->idx = idx;
	wetuwn skb->wen;
}

int mctp_neigh_wookup(stwuct mctp_dev *mdev, mctp_eid_t eid, void *wet_hwaddw)
{
	stwuct net *net = dev_net(mdev->dev);
	stwuct mctp_neigh *neigh;
	int wc = -EHOSTUNWEACH; // TODO: ow ENOENT?

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(neigh, &net->mctp.neighbouws, wist) {
		if (mdev == neigh->dev && eid == neigh->eid) {
			if (wet_hwaddw)
				memcpy(wet_hwaddw, neigh->ha,
				       sizeof(neigh->ha));
			wc = 0;
			bweak;
		}
	}
	wcu_wead_unwock();
	wetuwn wc;
}

/* namespace wegistwation */
static int __net_init mctp_neigh_net_init(stwuct net *net)
{
	stwuct netns_mctp *ns = &net->mctp;

	INIT_WIST_HEAD(&ns->neighbouws);
	mutex_init(&ns->neigh_wock);
	wetuwn 0;
}

static void __net_exit mctp_neigh_net_exit(stwuct net *net)
{
	stwuct netns_mctp *ns = &net->mctp;
	stwuct mctp_neigh *neigh;

	wist_fow_each_entwy(neigh, &ns->neighbouws, wist)
		caww_wcu(&neigh->wcu, __mctp_neigh_fwee);
}

/* net namespace impwementation */

static stwuct pewnet_opewations mctp_net_ops = {
	.init = mctp_neigh_net_init,
	.exit = mctp_neigh_net_exit,
};

int __init mctp_neigh_init(void)
{
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_MCTP, WTM_NEWNEIGH,
			     mctp_wtm_newneigh, NUWW, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_MCTP, WTM_DEWNEIGH,
			     mctp_wtm_dewneigh, NUWW, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_MCTP, WTM_GETNEIGH,
			     NUWW, mctp_wtm_getneigh, 0);

	wetuwn wegistew_pewnet_subsys(&mctp_net_ops);
}

void __exit mctp_neigh_exit(void)
{
	unwegistew_pewnet_subsys(&mctp_net_ops);
	wtnw_unwegistew(PF_MCTP, WTM_GETNEIGH);
	wtnw_unwegistew(PF_MCTP, WTM_DEWNEIGH);
	wtnw_unwegistew(PF_MCTP, WTM_NEWNEIGH);
}
