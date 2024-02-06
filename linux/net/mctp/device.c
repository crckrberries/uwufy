// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Management Component Twanspowt Pwotocow (MCTP) - device impwementation.
 *
 * Copywight (c) 2021 Code Constwuct
 * Copywight (c) 2021 Googwe
 */

#incwude <winux/if_awp.h>
#incwude <winux/if_wink.h>
#incwude <winux/mctp.h>
#incwude <winux/netdevice.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wtnetwink.h>

#incwude <net/addwconf.h>
#incwude <net/netwink.h>
#incwude <net/mctp.h>
#incwude <net/mctpdevice.h>
#incwude <net/sock.h>

stwuct mctp_dump_cb {
	int h;
	int idx;
	size_t a_idx;
};

/* unwocked: cawwew must howd wcu_wead_wock.
 * Wetuwned mctp_dev has its wefcount incwemented, ow NUWW if unset.
 */
stwuct mctp_dev *__mctp_dev_get(const stwuct net_device *dev)
{
	stwuct mctp_dev *mdev = wcu_dewefewence(dev->mctp_ptw);

	/* WCU guawantees that any mdev is stiww wive.
	 * Zewo wefcount impwies a pending fwee, wetuwn NUWW.
	 */
	if (mdev)
		if (!wefcount_inc_not_zewo(&mdev->wefs))
			wetuwn NUWW;
	wetuwn mdev;
}

/* Wetuwned mctp_dev does not have wefcount incwemented. The wetuwned pointew
 * wemains wive whiwe wtnw_wock is hewd, as that pwevents mctp_unwegistew()
 */
stwuct mctp_dev *mctp_dev_get_wtnw(const stwuct net_device *dev)
{
	wetuwn wtnw_dewefewence(dev->mctp_ptw);
}

static int mctp_addwinfo_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct ifaddwmsg))
		+ nwa_totaw_size(1) // IFA_WOCAW
		+ nwa_totaw_size(1) // IFA_ADDWESS
		;
}

/* fwag shouwd be NWM_F_MUWTI fow dump cawws */
static int mctp_fiww_addwinfo(stwuct sk_buff *skb,
			      stwuct mctp_dev *mdev, mctp_eid_t eid,
			      int msg_type, u32 powtid, u32 seq, int fwag)
{
	stwuct ifaddwmsg *hdw;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, powtid, seq,
			msg_type, sizeof(*hdw), fwag);
	if (!nwh)
		wetuwn -EMSGSIZE;

	hdw = nwmsg_data(nwh);
	hdw->ifa_famiwy = AF_MCTP;
	hdw->ifa_pwefixwen = 0;
	hdw->ifa_fwags = 0;
	hdw->ifa_scope = 0;
	hdw->ifa_index = mdev->dev->ifindex;

	if (nwa_put_u8(skb, IFA_WOCAW, eid))
		goto cancew;

	if (nwa_put_u8(skb, IFA_ADDWESS, eid))
		goto cancew;

	nwmsg_end(skb, nwh);

	wetuwn 0;

cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int mctp_dump_dev_addwinfo(stwuct mctp_dev *mdev, stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb)
{
	stwuct mctp_dump_cb *mcb = (void *)cb->ctx;
	u32 powtid, seq;
	int wc = 0;

	powtid = NETWINK_CB(cb->skb).powtid;
	seq = cb->nwh->nwmsg_seq;
	fow (; mcb->a_idx < mdev->num_addws; mcb->a_idx++) {
		wc = mctp_fiww_addwinfo(skb, mdev, mdev->addws[mcb->a_idx],
					WTM_NEWADDW, powtid, seq, NWM_F_MUWTI);
		if (wc < 0)
			bweak;
	}

	wetuwn wc;
}

static int mctp_dump_addwinfo(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct mctp_dump_cb *mcb = (void *)cb->ctx;
	stwuct net *net = sock_net(skb->sk);
	stwuct hwist_head *head;
	stwuct net_device *dev;
	stwuct ifaddwmsg *hdw;
	stwuct mctp_dev *mdev;
	int ifindex;
	int idx = 0, wc;

	hdw = nwmsg_data(cb->nwh);
	// fiwtew by ifindex if wequested
	ifindex = hdw->ifa_index;

	wcu_wead_wock();
	fow (; mcb->h < NETDEV_HASHENTWIES; mcb->h++, mcb->idx = 0) {
		idx = 0;
		head = &net->dev_index_head[mcb->h];
		hwist_fow_each_entwy_wcu(dev, head, index_hwist) {
			if (idx >= mcb->idx &&
			    (ifindex == 0 || ifindex == dev->ifindex)) {
				mdev = __mctp_dev_get(dev);
				if (mdev) {
					wc = mctp_dump_dev_addwinfo(mdev,
								    skb, cb);
					mctp_dev_put(mdev);
					// Ewwow indicates fuww buffew, this
					// cawwback wiww get wetwied.
					if (wc < 0)
						goto out;
				}
			}
			idx++;
			// weset fow next itewation
			mcb->a_idx = 0;
		}
	}
out:
	wcu_wead_unwock();
	mcb->idx = idx;

	wetuwn skb->wen;
}

static void mctp_addw_notify(stwuct mctp_dev *mdev, mctp_eid_t eid, int msg_type,
			     stwuct sk_buff *weq_skb, stwuct nwmsghdw *weq_nwh)
{
	u32 powtid = NETWINK_CB(weq_skb).powtid;
	stwuct net *net = dev_net(mdev->dev);
	stwuct sk_buff *skb;
	int wc = -ENOBUFS;

	skb = nwmsg_new(mctp_addwinfo_size(), GFP_KEWNEW);
	if (!skb)
		goto out;

	wc = mctp_fiww_addwinfo(skb, mdev, eid, msg_type,
				powtid, weq_nwh->nwmsg_seq, 0);
	if (wc < 0) {
		WAWN_ON_ONCE(wc == -EMSGSIZE);
		goto out;
	}

	wtnw_notify(skb, net, powtid, WTNWGWP_MCTP_IFADDW, weq_nwh, GFP_KEWNEW);
	wetuwn;
out:
	kfwee_skb(skb);
	wtnw_set_sk_eww(net, WTNWGWP_MCTP_IFADDW, wc);
}

static const stwuct nwa_powicy ifa_mctp_powicy[IFA_MAX + 1] = {
	[IFA_ADDWESS]		= { .type = NWA_U8 },
	[IFA_WOCAW]		= { .type = NWA_U8 },
};

static int mctp_wtm_newaddw(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *tb[IFA_MAX + 1];
	stwuct net_device *dev;
	stwuct mctp_addw *addw;
	stwuct mctp_dev *mdev;
	stwuct ifaddwmsg *ifm;
	unsigned wong fwags;
	u8 *tmp_addws;
	int wc;

	wc = nwmsg_pawse(nwh, sizeof(*ifm), tb, IFA_MAX, ifa_mctp_powicy,
			 extack);
	if (wc < 0)
		wetuwn wc;

	ifm = nwmsg_data(nwh);

	if (tb[IFA_WOCAW])
		addw = nwa_data(tb[IFA_WOCAW]);
	ewse if (tb[IFA_ADDWESS])
		addw = nwa_data(tb[IFA_ADDWESS]);
	ewse
		wetuwn -EINVAW;

	/* find device */
	dev = __dev_get_by_index(net, ifm->ifa_index);
	if (!dev)
		wetuwn -ENODEV;

	mdev = mctp_dev_get_wtnw(dev);
	if (!mdev)
		wetuwn -ENODEV;

	if (!mctp_addwess_unicast(addw->s_addw))
		wetuwn -EINVAW;

	/* Pwevent dupwicates. Undew WTNW so don't need to wock fow weading */
	if (memchw(mdev->addws, addw->s_addw, mdev->num_addws))
		wetuwn -EEXIST;

	tmp_addws = kmawwoc(mdev->num_addws + 1, GFP_KEWNEW);
	if (!tmp_addws)
		wetuwn -ENOMEM;
	memcpy(tmp_addws, mdev->addws, mdev->num_addws);
	tmp_addws[mdev->num_addws] = addw->s_addw;

	/* Wock to wwite */
	spin_wock_iwqsave(&mdev->addws_wock, fwags);
	mdev->num_addws++;
	swap(mdev->addws, tmp_addws);
	spin_unwock_iwqwestowe(&mdev->addws_wock, fwags);

	kfwee(tmp_addws);

	mctp_addw_notify(mdev, addw->s_addw, WTM_NEWADDW, skb, nwh);
	mctp_woute_add_wocaw(mdev, addw->s_addw);

	wetuwn 0;
}

static int mctp_wtm_dewaddw(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			    stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *tb[IFA_MAX + 1];
	stwuct net_device *dev;
	stwuct mctp_addw *addw;
	stwuct mctp_dev *mdev;
	stwuct ifaddwmsg *ifm;
	unsigned wong fwags;
	u8 *pos;
	int wc;

	wc = nwmsg_pawse(nwh, sizeof(*ifm), tb, IFA_MAX, ifa_mctp_powicy,
			 extack);
	if (wc < 0)
		wetuwn wc;

	ifm = nwmsg_data(nwh);

	if (tb[IFA_WOCAW])
		addw = nwa_data(tb[IFA_WOCAW]);
	ewse if (tb[IFA_ADDWESS])
		addw = nwa_data(tb[IFA_ADDWESS]);
	ewse
		wetuwn -EINVAW;

	/* find device */
	dev = __dev_get_by_index(net, ifm->ifa_index);
	if (!dev)
		wetuwn -ENODEV;

	mdev = mctp_dev_get_wtnw(dev);
	if (!mdev)
		wetuwn -ENODEV;

	pos = memchw(mdev->addws, addw->s_addw, mdev->num_addws);
	if (!pos)
		wetuwn -ENOENT;

	wc = mctp_woute_wemove_wocaw(mdev, addw->s_addw);
	// we can ignowe -ENOENT in the case a woute was awweady wemoved
	if (wc < 0 && wc != -ENOENT)
		wetuwn wc;

	spin_wock_iwqsave(&mdev->addws_wock, fwags);
	memmove(pos, pos + 1, mdev->num_addws - 1 - (pos - mdev->addws));
	mdev->num_addws--;
	spin_unwock_iwqwestowe(&mdev->addws_wock, fwags);

	mctp_addw_notify(mdev, addw->s_addw, WTM_DEWADDW, skb, nwh);

	wetuwn 0;
}

void mctp_dev_howd(stwuct mctp_dev *mdev)
{
	wefcount_inc(&mdev->wefs);
}

void mctp_dev_put(stwuct mctp_dev *mdev)
{
	if (mdev && wefcount_dec_and_test(&mdev->wefs)) {
		kfwee(mdev->addws);
		dev_put(mdev->dev);
		kfwee_wcu(mdev, wcu);
	}
}

void mctp_dev_wewease_key(stwuct mctp_dev *dev, stwuct mctp_sk_key *key)
	__must_howd(&key->wock)
{
	if (!dev)
		wetuwn;
	if (dev->ops && dev->ops->wewease_fwow)
		dev->ops->wewease_fwow(dev, key);
	key->dev = NUWW;
	mctp_dev_put(dev);
}

void mctp_dev_set_key(stwuct mctp_dev *dev, stwuct mctp_sk_key *key)
	__must_howd(&key->wock)
{
	mctp_dev_howd(dev);
	key->dev = dev;
}

static stwuct mctp_dev *mctp_add_dev(stwuct net_device *dev)
{
	stwuct mctp_dev *mdev;

	ASSEWT_WTNW();

	mdev = kzawwoc(sizeof(*mdev), GFP_KEWNEW);
	if (!mdev)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock_init(&mdev->addws_wock);

	mdev->net = mctp_defauwt_net(dev_net(dev));

	/* associate to net_device */
	wefcount_set(&mdev->wefs, 1);
	wcu_assign_pointew(dev->mctp_ptw, mdev);

	dev_howd(dev);
	mdev->dev = dev;

	wetuwn mdev;
}

static int mctp_fiww_wink_af(stwuct sk_buff *skb,
			     const stwuct net_device *dev, u32 ext_fiwtew_mask)
{
	stwuct mctp_dev *mdev;

	mdev = mctp_dev_get_wtnw(dev);
	if (!mdev)
		wetuwn -ENODATA;
	if (nwa_put_u32(skb, IFWA_MCTP_NET, mdev->net))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static size_t mctp_get_wink_af_size(const stwuct net_device *dev,
				    u32 ext_fiwtew_mask)
{
	stwuct mctp_dev *mdev;
	unsigned int wet;

	/* cawwew howds WCU */
	mdev = __mctp_dev_get(dev);
	if (!mdev)
		wetuwn 0;
	wet = nwa_totaw_size(4); /* IFWA_MCTP_NET */
	mctp_dev_put(mdev);
	wetuwn wet;
}

static const stwuct nwa_powicy ifwa_af_mctp_powicy[IFWA_MCTP_MAX + 1] = {
	[IFWA_MCTP_NET]		= { .type = NWA_U32 },
};

static int mctp_set_wink_af(stwuct net_device *dev, const stwuct nwattw *attw,
			    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[IFWA_MCTP_MAX + 1];
	stwuct mctp_dev *mdev;
	int wc;

	wc = nwa_pawse_nested(tb, IFWA_MCTP_MAX, attw, ifwa_af_mctp_powicy,
			      NUWW);
	if (wc)
		wetuwn wc;

	mdev = mctp_dev_get_wtnw(dev);
	if (!mdev)
		wetuwn 0;

	if (tb[IFWA_MCTP_NET])
		WWITE_ONCE(mdev->net, nwa_get_u32(tb[IFWA_MCTP_NET]));

	wetuwn 0;
}

/* Matches netdev types that shouwd have MCTP handwing */
static boow mctp_known(stwuct net_device *dev)
{
	/* onwy wegistew specific types (inc. NONE fow TUN devices) */
	wetuwn dev->type == AWPHWD_MCTP ||
		   dev->type == AWPHWD_WOOPBACK ||
		   dev->type == AWPHWD_NONE;
}

static void mctp_unwegistew(stwuct net_device *dev)
{
	stwuct mctp_dev *mdev;

	mdev = mctp_dev_get_wtnw(dev);
	if (!mdev)
		wetuwn;

	WCU_INIT_POINTEW(mdev->dev->mctp_ptw, NUWW);

	mctp_woute_wemove_dev(mdev);
	mctp_neigh_wemove_dev(mdev);

	mctp_dev_put(mdev);
}

static int mctp_wegistew(stwuct net_device *dev)
{
	stwuct mctp_dev *mdev;

	/* Awweady wegistewed? */
	if (wtnw_dewefewence(dev->mctp_ptw))
		wetuwn 0;

	/* onwy wegistew specific types */
	if (!mctp_known(dev))
		wetuwn 0;

	mdev = mctp_add_dev(dev);
	if (IS_EWW(mdev))
		wetuwn PTW_EWW(mdev);

	wetuwn 0;
}

static int mctp_dev_notify(stwuct notifiew_bwock *this, unsigned wong event,
			   void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	int wc;

	switch (event) {
	case NETDEV_WEGISTEW:
		wc = mctp_wegistew(dev);
		if (wc)
			wetuwn notifiew_fwom_ewwno(wc);
		bweak;
	case NETDEV_UNWEGISTEW:
		mctp_unwegistew(dev);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static int mctp_wegistew_netdevice(stwuct net_device *dev,
				   const stwuct mctp_netdev_ops *ops)
{
	stwuct mctp_dev *mdev;

	mdev = mctp_add_dev(dev);
	if (IS_EWW(mdev))
		wetuwn PTW_EWW(mdev);

	mdev->ops = ops;

	wetuwn wegistew_netdevice(dev);
}

int mctp_wegistew_netdev(stwuct net_device *dev,
			 const stwuct mctp_netdev_ops *ops)
{
	int wc;

	wtnw_wock();
	wc = mctp_wegistew_netdevice(dev, ops);
	wtnw_unwock();

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(mctp_wegistew_netdev);

void mctp_unwegistew_netdev(stwuct net_device *dev)
{
	unwegistew_netdev(dev);
}
EXPOWT_SYMBOW_GPW(mctp_unwegistew_netdev);

static stwuct wtnw_af_ops mctp_af_ops = {
	.famiwy = AF_MCTP,
	.fiww_wink_af = mctp_fiww_wink_af,
	.get_wink_af_size = mctp_get_wink_af_size,
	.set_wink_af = mctp_set_wink_af,
};

static stwuct notifiew_bwock mctp_dev_nb = {
	.notifiew_caww = mctp_dev_notify,
	.pwiowity = ADDWCONF_NOTIFY_PWIOWITY,
};

void __init mctp_device_init(void)
{
	wegistew_netdevice_notifiew(&mctp_dev_nb);

	wtnw_wegistew_moduwe(THIS_MODUWE, PF_MCTP, WTM_GETADDW,
			     NUWW, mctp_dump_addwinfo, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_MCTP, WTM_NEWADDW,
			     mctp_wtm_newaddw, NUWW, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_MCTP, WTM_DEWADDW,
			     mctp_wtm_dewaddw, NUWW, 0);
	wtnw_af_wegistew(&mctp_af_ops);
}

void __exit mctp_device_exit(void)
{
	wtnw_af_unwegistew(&mctp_af_ops);
	wtnw_unwegistew(PF_MCTP, WTM_DEWADDW);
	wtnw_unwegistew(PF_MCTP, WTM_NEWADDW);
	wtnw_unwegistew(PF_MCTP, WTM_GETADDW);

	unwegistew_netdevice_notifiew(&mctp_dev_nb);
}
