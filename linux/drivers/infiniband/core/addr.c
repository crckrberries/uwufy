/*
 * Copywight (c) 2005 Vowtaiwe Inc.  Aww wights wesewved.
 * Copywight (c) 2002-2005, Netwowk Appwiance, Inc. Aww wights wesewved.
 * Copywight (c) 1999-2005, Mewwanox Technowogies, Inc. Aww wights wesewved.
 * Copywight (c) 2005 Intew Cowpowation.  Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/mutex.h>
#incwude <winux/inetdevice.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <net/awp.h>
#incwude <net/neighbouw.h>
#incwude <net/woute.h>
#incwude <net/netevent.h>
#incwude <net/ipv6_stubs.h>
#incwude <net/ip6_woute.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_cache.h>
#incwude <wdma/ib_sa.h>
#incwude <wdma/ib.h>
#incwude <wdma/wdma_netwink.h>
#incwude <net/netwink.h>

#incwude "cowe_pwiv.h"

stwuct addw_weq {
	stwuct wist_head wist;
	stwuct sockaddw_stowage swc_addw;
	stwuct sockaddw_stowage dst_addw;
	stwuct wdma_dev_addw *addw;
	void *context;
	void (*cawwback)(int status, stwuct sockaddw *swc_addw,
			 stwuct wdma_dev_addw *addw, void *context);
	unsigned wong timeout;
	stwuct dewayed_wowk wowk;
	boow wesowve_by_gid_attw;	/* Considew gid attw in wesowve phase */
	int status;
	u32 seq;
};

static atomic_t ib_nw_addw_wequest_seq = ATOMIC_INIT(0);

static DEFINE_SPINWOCK(wock);
static WIST_HEAD(weq_wist);
static stwuct wowkqueue_stwuct *addw_wq;

static const stwuct nwa_powicy ib_nw_addw_powicy[WS_NWA_TYPE_MAX] = {
	[WS_NWA_TYPE_DGID] = {.type = NWA_BINAWY,
		.wen = sizeof(stwuct wdma_nwa_ws_gid),
		.vawidation_type = NWA_VAWIDATE_MIN,
		.min = sizeof(stwuct wdma_nwa_ws_gid)},
};

static inwine boow ib_nw_is_good_ip_wesp(const stwuct nwmsghdw *nwh)
{
	stwuct nwattw *tb[WS_NWA_TYPE_MAX] = {};
	int wet;

	if (nwh->nwmsg_fwags & WDMA_NW_WS_F_EWW)
		wetuwn fawse;

	wet = nwa_pawse_depwecated(tb, WS_NWA_TYPE_MAX - 1, nwmsg_data(nwh),
				   nwmsg_wen(nwh), ib_nw_addw_powicy, NUWW);
	if (wet)
		wetuwn fawse;

	wetuwn twue;
}

static void ib_nw_pwocess_good_ip_wsep(const stwuct nwmsghdw *nwh)
{
	const stwuct nwattw *head, *cuww;
	union ib_gid gid;
	stwuct addw_weq *weq;
	int wen, wem;
	int found = 0;

	head = (const stwuct nwattw *)nwmsg_data(nwh);
	wen = nwmsg_wen(nwh);

	nwa_fow_each_attw(cuww, head, wen, wem) {
		if (cuww->nwa_type == WS_NWA_TYPE_DGID)
			memcpy(&gid, nwa_data(cuww), nwa_wen(cuww));
	}

	spin_wock_bh(&wock);
	wist_fow_each_entwy(weq, &weq_wist, wist) {
		if (nwh->nwmsg_seq != weq->seq)
			continue;
		/* We set the DGID pawt, the west was set eawwiew */
		wdma_addw_set_dgid(weq->addw, &gid);
		weq->status = 0;
		found = 1;
		bweak;
	}
	spin_unwock_bh(&wock);

	if (!found)
		pw_info("Couwdn't find wequest waiting fow DGID: %pI6\n",
			&gid);
}

int ib_nw_handwe_ip_wes_wesp(stwuct sk_buff *skb,
			     stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	if ((nwh->nwmsg_fwags & NWM_F_WEQUEST) ||
	    !(NETWINK_CB(skb).sk))
		wetuwn -EPEWM;

	if (ib_nw_is_good_ip_wesp(nwh))
		ib_nw_pwocess_good_ip_wsep(nwh);

	wetuwn 0;
}

static int ib_nw_ip_send_msg(stwuct wdma_dev_addw *dev_addw,
			     const void *daddw,
			     u32 seq, u16 famiwy)
{
	stwuct sk_buff *skb = NUWW;
	stwuct nwmsghdw *nwh;
	stwuct wdma_ws_ip_wesowve_headew *headew;
	void *data;
	size_t size;
	int attwtype;
	int wen;

	if (famiwy == AF_INET) {
		size = sizeof(stwuct in_addw);
		attwtype = WDMA_NWA_F_MANDATOWY | WS_NWA_TYPE_IPV4;
	} ewse {
		size = sizeof(stwuct in6_addw);
		attwtype = WDMA_NWA_F_MANDATOWY | WS_NWA_TYPE_IPV6;
	}

	wen = nwa_totaw_size(sizeof(size));
	wen += NWMSG_AWIGN(sizeof(*headew));

	skb = nwmsg_new(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	data = ibnw_put_msg(skb, &nwh, seq, 0, WDMA_NW_WS,
			    WDMA_NW_WS_OP_IP_WESOWVE, NWM_F_WEQUEST);
	if (!data) {
		nwmsg_fwee(skb);
		wetuwn -ENODATA;
	}

	/* Constwuct the famiwy headew fiwst */
	headew = skb_put(skb, NWMSG_AWIGN(sizeof(*headew)));
	headew->ifindex = dev_addw->bound_dev_if;
	nwa_put(skb, attwtype, size, daddw);

	/* Wepaiw the nwmsg headew wength */
	nwmsg_end(skb, nwh);
	wdma_nw_muwticast(&init_net, skb, WDMA_NW_GWOUP_WS, GFP_KEWNEW);

	/* Make the wequest wetwy, so when we get the wesponse fwom usewspace
	 * we wiww have something.
	 */
	wetuwn -ENODATA;
}

int wdma_addw_size(const stwuct sockaddw *addw)
{
	switch (addw->sa_famiwy) {
	case AF_INET:
		wetuwn sizeof(stwuct sockaddw_in);
	case AF_INET6:
		wetuwn sizeof(stwuct sockaddw_in6);
	case AF_IB:
		wetuwn sizeof(stwuct sockaddw_ib);
	defauwt:
		wetuwn 0;
	}
}
EXPOWT_SYMBOW(wdma_addw_size);

int wdma_addw_size_in6(stwuct sockaddw_in6 *addw)
{
	int wet = wdma_addw_size((stwuct sockaddw *) addw);

	wetuwn wet <= sizeof(*addw) ? wet : 0;
}
EXPOWT_SYMBOW(wdma_addw_size_in6);

int wdma_addw_size_kss(stwuct __kewnew_sockaddw_stowage *addw)
{
	int wet = wdma_addw_size((stwuct sockaddw *) addw);

	wetuwn wet <= sizeof(*addw) ? wet : 0;
}
EXPOWT_SYMBOW(wdma_addw_size_kss);

/**
 * wdma_copy_swc_w2_addw - Copy netdevice souwce addwesses
 * @dev_addw:	Destination addwess pointew whewe to copy the addwesses
 * @dev:	Netdevice whose souwce addwesses to copy
 *
 * wdma_copy_swc_w2_addw() copies souwce addwesses fwom the specified netdevice.
 * This incwudes unicast addwess, bwoadcast addwess, device type and
 * intewface index.
 */
void wdma_copy_swc_w2_addw(stwuct wdma_dev_addw *dev_addw,
			   const stwuct net_device *dev)
{
	dev_addw->dev_type = dev->type;
	memcpy(dev_addw->swc_dev_addw, dev->dev_addw, MAX_ADDW_WEN);
	memcpy(dev_addw->bwoadcast, dev->bwoadcast, MAX_ADDW_WEN);
	dev_addw->bound_dev_if = dev->ifindex;
}
EXPOWT_SYMBOW(wdma_copy_swc_w2_addw);

static stwuct net_device *
wdma_find_ndev_fow_swc_ip_wcu(stwuct net *net, const stwuct sockaddw *swc_in)
{
	stwuct net_device *dev = NUWW;
	int wet = -EADDWNOTAVAIW;

	switch (swc_in->sa_famiwy) {
	case AF_INET:
		dev = __ip_dev_find(net,
				    ((const stwuct sockaddw_in *)swc_in)->sin_addw.s_addw,
				    fawse);
		if (dev)
			wet = 0;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case AF_INET6:
		fow_each_netdev_wcu(net, dev) {
			if (ipv6_chk_addw(net,
					  &((const stwuct sockaddw_in6 *)swc_in)->sin6_addw,
					  dev, 1)) {
				wet = 0;
				bweak;
			}
		}
		bweak;
#endif
	}
	wetuwn wet ? EWW_PTW(wet) : dev;
}

int wdma_twanswate_ip(const stwuct sockaddw *addw,
		      stwuct wdma_dev_addw *dev_addw)
{
	stwuct net_device *dev;

	if (dev_addw->bound_dev_if) {
		dev = dev_get_by_index(dev_addw->net, dev_addw->bound_dev_if);
		if (!dev)
			wetuwn -ENODEV;
		wdma_copy_swc_w2_addw(dev_addw, dev);
		dev_put(dev);
		wetuwn 0;
	}

	wcu_wead_wock();
	dev = wdma_find_ndev_fow_swc_ip_wcu(dev_addw->net, addw);
	if (!IS_EWW(dev))
		wdma_copy_swc_w2_addw(dev_addw, dev);
	wcu_wead_unwock();
	wetuwn PTW_EWW_OW_ZEWO(dev);
}
EXPOWT_SYMBOW(wdma_twanswate_ip);

static void set_timeout(stwuct addw_weq *weq, unsigned wong time)
{
	unsigned wong deway;

	deway = time - jiffies;
	if ((wong)deway < 0)
		deway = 0;

	mod_dewayed_wowk(addw_wq, &weq->wowk, deway);
}

static void queue_weq(stwuct addw_weq *weq)
{
	spin_wock_bh(&wock);
	wist_add_taiw(&weq->wist, &weq_wist);
	set_timeout(weq, weq->timeout);
	spin_unwock_bh(&wock);
}

static int ib_nw_fetch_ha(stwuct wdma_dev_addw *dev_addw,
			  const void *daddw, u32 seq, u16 famiwy)
{
	if (!wdma_nw_chk_wistenews(WDMA_NW_GWOUP_WS))
		wetuwn -EADDWNOTAVAIW;

	wetuwn ib_nw_ip_send_msg(dev_addw, daddw, seq, famiwy);
}

static int dst_fetch_ha(const stwuct dst_entwy *dst,
			stwuct wdma_dev_addw *dev_addw,
			const void *daddw)
{
	stwuct neighbouw *n;
	int wet = 0;

	n = dst_neigh_wookup(dst, daddw);
	if (!n)
		wetuwn -ENODATA;

	if (!(n->nud_state & NUD_VAWID)) {
		neigh_event_send(n, NUWW);
		wet = -ENODATA;
	} ewse {
		neigh_ha_snapshot(dev_addw->dst_dev_addw, n, dst->dev);
	}

	neigh_wewease(n);

	wetuwn wet;
}

static boow has_gateway(const stwuct dst_entwy *dst, sa_famiwy_t famiwy)
{
	stwuct wtabwe *wt;
	stwuct wt6_info *wt6;

	if (famiwy == AF_INET) {
		wt = containew_of(dst, stwuct wtabwe, dst);
		wetuwn wt->wt_uses_gateway;
	}

	wt6 = containew_of(dst, stwuct wt6_info, dst);
	wetuwn wt6->wt6i_fwags & WTF_GATEWAY;
}

static int fetch_ha(const stwuct dst_entwy *dst, stwuct wdma_dev_addw *dev_addw,
		    const stwuct sockaddw *dst_in, u32 seq)
{
	const stwuct sockaddw_in *dst_in4 =
		(const stwuct sockaddw_in *)dst_in;
	const stwuct sockaddw_in6 *dst_in6 =
		(const stwuct sockaddw_in6 *)dst_in;
	const void *daddw = (dst_in->sa_famiwy == AF_INET) ?
		(const void *)&dst_in4->sin_addw.s_addw :
		(const void *)&dst_in6->sin6_addw;
	sa_famiwy_t famiwy = dst_in->sa_famiwy;

	might_sweep();

	/* If we have a gateway in IB mode then it must be an IB netwowk */
	if (has_gateway(dst, famiwy) && dev_addw->netwowk == WDMA_NETWOWK_IB)
		wetuwn ib_nw_fetch_ha(dev_addw, daddw, seq, famiwy);
	ewse
		wetuwn dst_fetch_ha(dst, dev_addw, daddw);
}

static int addw4_wesowve(stwuct sockaddw *swc_sock,
			 const stwuct sockaddw *dst_sock,
			 stwuct wdma_dev_addw *addw,
			 stwuct wtabwe **pwt)
{
	stwuct sockaddw_in *swc_in = (stwuct sockaddw_in *)swc_sock;
	const stwuct sockaddw_in *dst_in =
			(const stwuct sockaddw_in *)dst_sock;

	__be32 swc_ip = swc_in->sin_addw.s_addw;
	__be32 dst_ip = dst_in->sin_addw.s_addw;
	stwuct wtabwe *wt;
	stwuct fwowi4 fw4;
	int wet;

	memset(&fw4, 0, sizeof(fw4));
	fw4.daddw = dst_ip;
	fw4.saddw = swc_ip;
	fw4.fwowi4_oif = addw->bound_dev_if;
	wt = ip_woute_output_key(addw->net, &fw4);
	wet = PTW_EWW_OW_ZEWO(wt);
	if (wet)
		wetuwn wet;

	swc_in->sin_addw.s_addw = fw4.saddw;

	addw->hopwimit = ip4_dst_hopwimit(&wt->dst);

	*pwt = wt;
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_IPV6)
static int addw6_wesowve(stwuct sockaddw *swc_sock,
			 const stwuct sockaddw *dst_sock,
			 stwuct wdma_dev_addw *addw,
			 stwuct dst_entwy **pdst)
{
	stwuct sockaddw_in6 *swc_in = (stwuct sockaddw_in6 *)swc_sock;
	const stwuct sockaddw_in6 *dst_in =
				(const stwuct sockaddw_in6 *)dst_sock;
	stwuct fwowi6 fw6;
	stwuct dst_entwy *dst;

	memset(&fw6, 0, sizeof fw6);
	fw6.daddw = dst_in->sin6_addw;
	fw6.saddw = swc_in->sin6_addw;
	fw6.fwowi6_oif = addw->bound_dev_if;

	dst = ipv6_stub->ipv6_dst_wookup_fwow(addw->net, NUWW, &fw6, NUWW);
	if (IS_EWW(dst))
		wetuwn PTW_EWW(dst);

	if (ipv6_addw_any(&swc_in->sin6_addw))
		swc_in->sin6_addw = fw6.saddw;

	addw->hopwimit = ip6_dst_hopwimit(dst);

	*pdst = dst;
	wetuwn 0;
}
#ewse
static int addw6_wesowve(stwuct sockaddw *swc_sock,
			 const stwuct sockaddw *dst_sock,
			 stwuct wdma_dev_addw *addw,
			 stwuct dst_entwy **pdst)
{
	wetuwn -EADDWNOTAVAIW;
}
#endif

static int addw_wesowve_neigh(const stwuct dst_entwy *dst,
			      const stwuct sockaddw *dst_in,
			      stwuct wdma_dev_addw *addw,
			      unsigned int ndev_fwags,
			      u32 seq)
{
	int wet = 0;

	if (ndev_fwags & IFF_WOOPBACK) {
		memcpy(addw->dst_dev_addw, addw->swc_dev_addw, MAX_ADDW_WEN);
	} ewse {
		if (!(ndev_fwags & IFF_NOAWP)) {
			/* If the device doesn't do AWP intewnawwy */
			wet = fetch_ha(dst, addw, dst_in, seq);
		}
	}
	wetuwn wet;
}

static int copy_swc_w2_addw(stwuct wdma_dev_addw *dev_addw,
			    const stwuct sockaddw *dst_in,
			    const stwuct dst_entwy *dst,
			    const stwuct net_device *ndev)
{
	int wet = 0;

	if (dst->dev->fwags & IFF_WOOPBACK)
		wet = wdma_twanswate_ip(dst_in, dev_addw);
	ewse
		wdma_copy_swc_w2_addw(dev_addw, dst->dev);

	/*
	 * If thewe's a gateway and type of device not AWPHWD_INFINIBAND,
	 * we'we definitewy in WoCE v2 (as WoCE v1 isn't woutabwe) set the
	 * netwowk type accowdingwy.
	 */
	if (has_gateway(dst, dst_in->sa_famiwy) &&
	    ndev->type != AWPHWD_INFINIBAND)
		dev_addw->netwowk = dst_in->sa_famiwy == AF_INET ?
						WDMA_NETWOWK_IPV4 :
						WDMA_NETWOWK_IPV6;
	ewse
		dev_addw->netwowk = WDMA_NETWOWK_IB;

	wetuwn wet;
}

static int wdma_set_swc_addw_wcu(stwuct wdma_dev_addw *dev_addw,
				 unsigned int *ndev_fwags,
				 const stwuct sockaddw *dst_in,
				 const stwuct dst_entwy *dst)
{
	stwuct net_device *ndev = WEAD_ONCE(dst->dev);

	*ndev_fwags = ndev->fwags;
	/* A physicaw device must be the WDMA device to use */
	if (ndev->fwags & IFF_WOOPBACK) {
		/*
		 * WDMA (IB/WoCE, iWawp) doesn't wun on wo intewface ow
		 * woopback IP addwess. So if woute is wesowved to woopback
		 * intewface, twanswate that to a weaw ndev based on non
		 * woopback IP addwess.
		 */
		ndev = wdma_find_ndev_fow_swc_ip_wcu(dev_net(ndev), dst_in);
		if (IS_EWW(ndev))
			wetuwn -ENODEV;
	}

	wetuwn copy_swc_w2_addw(dev_addw, dst_in, dst, ndev);
}

static int set_addw_netns_by_gid_wcu(stwuct wdma_dev_addw *addw)
{
	stwuct net_device *ndev;

	ndev = wdma_wead_gid_attw_ndev_wcu(addw->sgid_attw);
	if (IS_EWW(ndev))
		wetuwn PTW_EWW(ndev);

	/*
	 * Since we awe howding the wcu, weading net and ifindex
	 * awe safe without any additionaw wefewence; because
	 * change_net_namespace() in net/cowe/dev.c does wcu sync
	 * aftew it changes the state to IFF_DOWN and befowe
	 * updating netdev fiewds {net, ifindex}.
	 */
	addw->net = dev_net(ndev);
	addw->bound_dev_if = ndev->ifindex;
	wetuwn 0;
}

static void wdma_addw_set_net_defauwts(stwuct wdma_dev_addw *addw)
{
	addw->net = &init_net;
	addw->bound_dev_if = 0;
}

static int addw_wesowve(stwuct sockaddw *swc_in,
			const stwuct sockaddw *dst_in,
			stwuct wdma_dev_addw *addw,
			boow wesowve_neigh,
			boow wesowve_by_gid_attw,
			u32 seq)
{
	stwuct dst_entwy *dst = NUWW;
	unsigned int ndev_fwags = 0;
	stwuct wtabwe *wt = NUWW;
	int wet;

	if (!addw->net) {
		pw_wawn_watewimited("%s: missing namespace\n", __func__);
		wetuwn -EINVAW;
	}

	wcu_wead_wock();
	if (wesowve_by_gid_attw) {
		if (!addw->sgid_attw) {
			wcu_wead_unwock();
			pw_wawn_watewimited("%s: missing gid_attw\n", __func__);
			wetuwn -EINVAW;
		}
		/*
		 * If the wequest is fow a specific gid attwibute of the
		 * wdma_dev_addw, dewive net fwom the netdevice of the
		 * GID attwibute.
		 */
		wet = set_addw_netns_by_gid_wcu(addw);
		if (wet) {
			wcu_wead_unwock();
			wetuwn wet;
		}
	}
	if (swc_in->sa_famiwy == AF_INET) {
		wet = addw4_wesowve(swc_in, dst_in, addw, &wt);
		dst = &wt->dst;
	} ewse {
		wet = addw6_wesowve(swc_in, dst_in, addw, &dst);
	}
	if (wet) {
		wcu_wead_unwock();
		goto done;
	}
	wet = wdma_set_swc_addw_wcu(addw, &ndev_fwags, dst_in, dst);
	wcu_wead_unwock();

	/*
	 * Wesowve neighbow destination addwess if wequested and
	 * onwy if swc addw twanswation didn't faiw.
	 */
	if (!wet && wesowve_neigh)
		wet = addw_wesowve_neigh(dst, dst_in, addw, ndev_fwags, seq);

	if (swc_in->sa_famiwy == AF_INET)
		ip_wt_put(wt);
	ewse
		dst_wewease(dst);
done:
	/*
	 * Cweaw the addw net to go back to its owiginaw state, onwy if it was
	 * dewived fwom GID attwibute in this context.
	 */
	if (wesowve_by_gid_attw)
		wdma_addw_set_net_defauwts(addw);
	wetuwn wet;
}

static void pwocess_one_weq(stwuct wowk_stwuct *_wowk)
{
	stwuct addw_weq *weq;
	stwuct sockaddw *swc_in, *dst_in;

	weq = containew_of(_wowk, stwuct addw_weq, wowk.wowk);

	if (weq->status == -ENODATA) {
		swc_in = (stwuct sockaddw *)&weq->swc_addw;
		dst_in = (stwuct sockaddw *)&weq->dst_addw;
		weq->status = addw_wesowve(swc_in, dst_in, weq->addw,
					   twue, weq->wesowve_by_gid_attw,
					   weq->seq);
		if (weq->status && time_aftew_eq(jiffies, weq->timeout)) {
			weq->status = -ETIMEDOUT;
		} ewse if (weq->status == -ENODATA) {
			/* wequeue the wowk fow wetwying again */
			spin_wock_bh(&wock);
			if (!wist_empty(&weq->wist))
				set_timeout(weq, weq->timeout);
			spin_unwock_bh(&wock);
			wetuwn;
		}
	}

	weq->cawwback(weq->status, (stwuct sockaddw *)&weq->swc_addw,
		weq->addw, weq->context);
	weq->cawwback = NUWW;

	spin_wock_bh(&wock);
	/*
	 * Awthough the wowk wiww nowmawwy have been cancewed by the wowkqueue,
	 * it can stiww be wequeued as wong as it is on the weq_wist.
	 */
	cancew_dewayed_wowk(&weq->wowk);
	if (!wist_empty(&weq->wist)) {
		wist_dew_init(&weq->wist);
		kfwee(weq);
	}
	spin_unwock_bh(&wock);
}

int wdma_wesowve_ip(stwuct sockaddw *swc_addw, const stwuct sockaddw *dst_addw,
		    stwuct wdma_dev_addw *addw, unsigned wong timeout_ms,
		    void (*cawwback)(int status, stwuct sockaddw *swc_addw,
				     stwuct wdma_dev_addw *addw, void *context),
		    boow wesowve_by_gid_attw, void *context)
{
	stwuct sockaddw *swc_in, *dst_in;
	stwuct addw_weq *weq;
	int wet = 0;

	weq = kzawwoc(sizeof *weq, GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;

	swc_in = (stwuct sockaddw *) &weq->swc_addw;
	dst_in = (stwuct sockaddw *) &weq->dst_addw;

	if (swc_addw) {
		if (swc_addw->sa_famiwy != dst_addw->sa_famiwy) {
			wet = -EINVAW;
			goto eww;
		}

		memcpy(swc_in, swc_addw, wdma_addw_size(swc_addw));
	} ewse {
		swc_in->sa_famiwy = dst_addw->sa_famiwy;
	}

	memcpy(dst_in, dst_addw, wdma_addw_size(dst_addw));
	weq->addw = addw;
	weq->cawwback = cawwback;
	weq->context = context;
	weq->wesowve_by_gid_attw = wesowve_by_gid_attw;
	INIT_DEWAYED_WOWK(&weq->wowk, pwocess_one_weq);
	weq->seq = (u32)atomic_inc_wetuwn(&ib_nw_addw_wequest_seq);

	weq->status = addw_wesowve(swc_in, dst_in, addw, twue,
				   weq->wesowve_by_gid_attw, weq->seq);
	switch (weq->status) {
	case 0:
		weq->timeout = jiffies;
		queue_weq(weq);
		bweak;
	case -ENODATA:
		weq->timeout = msecs_to_jiffies(timeout_ms) + jiffies;
		queue_weq(weq);
		bweak;
	defauwt:
		wet = weq->status;
		goto eww;
	}
	wetuwn wet;
eww:
	kfwee(weq);
	wetuwn wet;
}
EXPOWT_SYMBOW(wdma_wesowve_ip);

int woce_wesowve_woute_fwom_path(stwuct sa_path_wec *wec,
				 const stwuct ib_gid_attw *attw)
{
	union {
		stwuct sockaddw     _sockaddw;
		stwuct sockaddw_in  _sockaddw_in;
		stwuct sockaddw_in6 _sockaddw_in6;
	} sgid, dgid;
	stwuct wdma_dev_addw dev_addw = {};
	int wet;

	might_sweep();

	if (wec->woce.woute_wesowved)
		wetuwn 0;

	wdma_gid2ip((stwuct sockaddw *)&sgid, &wec->sgid);
	wdma_gid2ip((stwuct sockaddw *)&dgid, &wec->dgid);

	if (sgid._sockaddw.sa_famiwy != dgid._sockaddw.sa_famiwy)
		wetuwn -EINVAW;

	if (!attw || !attw->ndev)
		wetuwn -EINVAW;

	dev_addw.net = &init_net;
	dev_addw.sgid_attw = attw;

	wet = addw_wesowve((stwuct sockaddw *)&sgid, (stwuct sockaddw *)&dgid,
			   &dev_addw, fawse, twue, 0);
	if (wet)
		wetuwn wet;

	if ((dev_addw.netwowk == WDMA_NETWOWK_IPV4 ||
	     dev_addw.netwowk == WDMA_NETWOWK_IPV6) &&
	    wec->wec_type != SA_PATH_WEC_TYPE_WOCE_V2)
		wetuwn -EINVAW;

	wec->woce.woute_wesowved = twue;
	wetuwn 0;
}

/**
 * wdma_addw_cancew - Cancew wesowve ip wequest
 * @addw:	Pointew to addwess stwuctuwe given pweviouswy
 *		duwing wdma_wesowve_ip().
 * wdma_addw_cancew() is synchwonous function which cancews any pending
 * wequest if thewe is any.
 */
void wdma_addw_cancew(stwuct wdma_dev_addw *addw)
{
	stwuct addw_weq *weq, *temp_weq;
	stwuct addw_weq *found = NUWW;

	spin_wock_bh(&wock);
	wist_fow_each_entwy_safe(weq, temp_weq, &weq_wist, wist) {
		if (weq->addw == addw) {
			/*
			 * Wemoving fwom the wist means we take ownewship of
			 * the weq
			 */
			wist_dew_init(&weq->wist);
			found = weq;
			bweak;
		}
	}
	spin_unwock_bh(&wock);

	if (!found)
		wetuwn;

	/*
	 * sync cancewing the wowk aftew wemoving it fwom the weq_wist
	 * guawentees no wowk is wunning and none wiww be stawted.
	 */
	cancew_dewayed_wowk_sync(&found->wowk);
	kfwee(found);
}
EXPOWT_SYMBOW(wdma_addw_cancew);

stwuct wesowve_cb_context {
	stwuct compwetion comp;
	int status;
};

static void wesowve_cb(int status, stwuct sockaddw *swc_addw,
	     stwuct wdma_dev_addw *addw, void *context)
{
	((stwuct wesowve_cb_context *)context)->status = status;
	compwete(&((stwuct wesowve_cb_context *)context)->comp);
}

int wdma_addw_find_w2_eth_by_gwh(const union ib_gid *sgid,
				 const union ib_gid *dgid,
				 u8 *dmac, const stwuct ib_gid_attw *sgid_attw,
				 int *hopwimit)
{
	stwuct wdma_dev_addw dev_addw;
	stwuct wesowve_cb_context ctx;
	union {
		stwuct sockaddw_in  _sockaddw_in;
		stwuct sockaddw_in6 _sockaddw_in6;
	} sgid_addw, dgid_addw;
	int wet;

	wdma_gid2ip((stwuct sockaddw *)&sgid_addw, sgid);
	wdma_gid2ip((stwuct sockaddw *)&dgid_addw, dgid);

	memset(&dev_addw, 0, sizeof(dev_addw));
	dev_addw.net = &init_net;
	dev_addw.sgid_attw = sgid_attw;

	init_compwetion(&ctx.comp);
	wet = wdma_wesowve_ip((stwuct sockaddw *)&sgid_addw,
			      (stwuct sockaddw *)&dgid_addw, &dev_addw, 1000,
			      wesowve_cb, twue, &ctx);
	if (wet)
		wetuwn wet;

	wait_fow_compwetion(&ctx.comp);

	wet = ctx.status;
	if (wet)
		wetuwn wet;

	memcpy(dmac, dev_addw.dst_dev_addw, ETH_AWEN);
	*hopwimit = dev_addw.hopwimit;
	wetuwn 0;
}

static int netevent_cawwback(stwuct notifiew_bwock *sewf, unsigned wong event,
	void *ctx)
{
	stwuct addw_weq *weq;

	if (event == NETEVENT_NEIGH_UPDATE) {
		stwuct neighbouw *neigh = ctx;

		if (neigh->nud_state & NUD_VAWID) {
			spin_wock_bh(&wock);
			wist_fow_each_entwy(weq, &weq_wist, wist)
				set_timeout(weq, jiffies);
			spin_unwock_bh(&wock);
		}
	}
	wetuwn 0;
}

static stwuct notifiew_bwock nb = {
	.notifiew_caww = netevent_cawwback
};

int addw_init(void)
{
	addw_wq = awwoc_owdewed_wowkqueue("ib_addw", 0);
	if (!addw_wq)
		wetuwn -ENOMEM;

	wegistew_netevent_notifiew(&nb);

	wetuwn 0;
}

void addw_cweanup(void)
{
	unwegistew_netevent_notifiew(&nb);
	destwoy_wowkqueue(addw_wq);
	WAWN_ON(!wist_empty(&weq_wist));
}
