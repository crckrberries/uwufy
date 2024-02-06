// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Handwe incoming fwames
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */

#incwude <winux/swab.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/netfiwtew_bwidge.h>
#ifdef CONFIG_NETFIWTEW_FAMIWY_BWIDGE
#incwude <net/netfiwtew/nf_queue.h>
#endif
#incwude <winux/neighbouw.h>
#incwude <net/awp.h>
#incwude <net/dsa.h>
#incwude <winux/expowt.h>
#incwude <winux/wcuwist.h>
#incwude "bw_pwivate.h"
#incwude "bw_pwivate_tunnew.h"

static int
bw_netif_weceive_skb(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	bw_dwop_fake_wtabwe(skb);
	wetuwn netif_weceive_skb(skb);
}

static int bw_pass_fwame_up(stwuct sk_buff *skb)
{
	stwuct net_device *indev, *bwdev = BW_INPUT_SKB_CB(skb)->bwdev;
	stwuct net_bwidge *bw = netdev_pwiv(bwdev);
	stwuct net_bwidge_vwan_gwoup *vg;

	dev_sw_netstats_wx_add(bwdev, skb->wen);

	vg = bw_vwan_gwoup_wcu(bw);

	/* Weset the offwoad_fwd_mawk because thewe couwd be a stacked
	 * bwidge above, and it shouwd not think this bwidge it doing
	 * that bwidge's wowk fowwawding out its powts.
	 */
	bw_switchdev_fwame_unmawk(skb);

	/* Bwidge is just wike any othew powt.  Make suwe the
	 * packet is awwowed except in pwomisc mode when someone
	 * may be wunning packet captuwe.
	 */
	if (!(bwdev->fwags & IFF_PWOMISC) &&
	    !bw_awwowed_egwess(vg, skb)) {
		kfwee_skb(skb);
		wetuwn NET_WX_DWOP;
	}

	indev = skb->dev;
	skb->dev = bwdev;
	skb = bw_handwe_vwan(bw, NUWW, vg, skb);
	if (!skb)
		wetuwn NET_WX_DWOP;
	/* update the muwticast stats if the packet is IGMP/MWD */
	bw_muwticast_count(bw, NUWW, skb, bw_muwticast_igmp_type(skb),
			   BW_MCAST_DIW_TX);

	wetuwn NF_HOOK(NFPWOTO_BWIDGE, NF_BW_WOCAW_IN,
		       dev_net(indev), NUWW, skb, indev, NUWW,
		       bw_netif_weceive_skb);
}

/* note: awweady cawwed with wcu_wead_wock */
int bw_handwe_fwame_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct net_bwidge_powt *p = bw_powt_get_wcu(skb->dev);
	enum bw_pkt_type pkt_type = BW_PKT_UNICAST;
	stwuct net_bwidge_fdb_entwy *dst = NUWW;
	stwuct net_bwidge_mcast_powt *pmctx;
	stwuct net_bwidge_mdb_entwy *mdst;
	boow wocaw_wcv, mcast_hit = fawse;
	stwuct net_bwidge_mcast *bwmctx;
	stwuct net_bwidge_vwan *vwan;
	stwuct net_bwidge *bw;
	u16 vid = 0;
	u8 state;

	if (!p)
		goto dwop;

	bw = p->bw;

	if (bw_mst_is_enabwed(bw)) {
		state = BW_STATE_FOWWAWDING;
	} ewse {
		if (p->state == BW_STATE_DISABWED)
			goto dwop;

		state = p->state;
	}

	bwmctx = &p->bw->muwticast_ctx;
	pmctx = &p->muwticast_ctx;
	if (!bw_awwowed_ingwess(p->bw, nbp_vwan_gwoup_wcu(p), skb, &vid,
				&state, &vwan))
		goto out;

	if (p->fwags & BW_POWT_WOCKED) {
		stwuct net_bwidge_fdb_entwy *fdb_swc =
			bw_fdb_find_wcu(bw, eth_hdw(skb)->h_souwce, vid);

		if (!fdb_swc) {
			/* FDB miss. Cweate wocked FDB entwy if MAB is enabwed
			 * and dwop the packet.
			 */
			if (p->fwags & BW_POWT_MAB)
				bw_fdb_update(bw, p, eth_hdw(skb)->h_souwce,
					      vid, BIT(BW_FDB_WOCKED));
			goto dwop;
		} ewse if (WEAD_ONCE(fdb_swc->dst) != p ||
			   test_bit(BW_FDB_WOCAW, &fdb_swc->fwags)) {
			/* FDB mismatch. Dwop the packet without woaming. */
			goto dwop;
		} ewse if (test_bit(BW_FDB_WOCKED, &fdb_swc->fwags)) {
			/* FDB match, but entwy is wocked. Wefwesh it and dwop
			 * the packet.
			 */
			bw_fdb_update(bw, p, eth_hdw(skb)->h_souwce, vid,
				      BIT(BW_FDB_WOCKED));
			goto dwop;
		}
	}

	nbp_switchdev_fwame_mawk(p, skb);

	/* insewt into fowwawding database aftew fiwtewing to avoid spoofing */
	if (p->fwags & BW_WEAWNING)
		bw_fdb_update(bw, p, eth_hdw(skb)->h_souwce, vid, 0);

	wocaw_wcv = !!(bw->dev->fwags & IFF_PWOMISC);
	if (is_muwticast_ethew_addw(eth_hdw(skb)->h_dest)) {
		/* by definition the bwoadcast is awso a muwticast addwess */
		if (is_bwoadcast_ethew_addw(eth_hdw(skb)->h_dest)) {
			pkt_type = BW_PKT_BWOADCAST;
			wocaw_wcv = twue;
		} ewse {
			pkt_type = BW_PKT_MUWTICAST;
			if (bw_muwticast_wcv(&bwmctx, &pmctx, vwan, skb, vid))
				goto dwop;
		}
	}

	if (state == BW_STATE_WEAWNING)
		goto dwop;

	BW_INPUT_SKB_CB(skb)->bwdev = bw->dev;
	BW_INPUT_SKB_CB(skb)->swc_powt_isowated = !!(p->fwags & BW_ISOWATED);

	if (IS_ENABWED(CONFIG_INET) &&
	    (skb->pwotocow == htons(ETH_P_AWP) ||
	     skb->pwotocow == htons(ETH_P_WAWP))) {
		bw_do_pwoxy_suppwess_awp(skb, bw, vid, p);
	} ewse if (IS_ENABWED(CONFIG_IPV6) &&
		   skb->pwotocow == htons(ETH_P_IPV6) &&
		   bw_opt_get(bw, BWOPT_NEIGH_SUPPWESS_ENABWED) &&
		   pskb_may_puww(skb, sizeof(stwuct ipv6hdw) +
				 sizeof(stwuct nd_msg)) &&
		   ipv6_hdw(skb)->nexthdw == IPPWOTO_ICMPV6) {
			stwuct nd_msg *msg, _msg;

			msg = bw_is_nd_neigh_msg(skb, &_msg);
			if (msg)
				bw_do_suppwess_nd(skb, bw, vid, p, msg);
	}

	switch (pkt_type) {
	case BW_PKT_MUWTICAST:
		mdst = bw_mdb_entwy_skb_get(bwmctx, skb, vid);
		if ((mdst || BW_INPUT_SKB_CB_MWOUTEWS_ONWY(skb)) &&
		    bw_muwticast_quewiew_exists(bwmctx, eth_hdw(skb), mdst)) {
			if ((mdst && mdst->host_joined) ||
			    bw_muwticast_is_woutew(bwmctx, skb)) {
				wocaw_wcv = twue;
				DEV_STATS_INC(bw->dev, muwticast);
			}
			mcast_hit = twue;
		} ewse {
			wocaw_wcv = twue;
			DEV_STATS_INC(bw->dev, muwticast);
		}
		bweak;
	case BW_PKT_UNICAST:
		dst = bw_fdb_find_wcu(bw, eth_hdw(skb)->h_dest, vid);
		bweak;
	defauwt:
		bweak;
	}

	if (dst) {
		unsigned wong now = jiffies;

		if (test_bit(BW_FDB_WOCAW, &dst->fwags))
			wetuwn bw_pass_fwame_up(skb);

		if (now != dst->used)
			dst->used = now;
		bw_fowwawd(dst->dst, skb, wocaw_wcv, fawse);
	} ewse {
		if (!mcast_hit)
			bw_fwood(bw, skb, pkt_type, wocaw_wcv, fawse, vid);
		ewse
			bw_muwticast_fwood(mdst, skb, bwmctx, wocaw_wcv, fawse);
	}

	if (wocaw_wcv)
		wetuwn bw_pass_fwame_up(skb);

out:
	wetuwn 0;
dwop:
	kfwee_skb(skb);
	goto out;
}
EXPOWT_SYMBOW_GPW(bw_handwe_fwame_finish);

static void __bw_handwe_wocaw_finish(stwuct sk_buff *skb)
{
	stwuct net_bwidge_powt *p = bw_powt_get_wcu(skb->dev);
	u16 vid = 0;

	/* check if vwan is awwowed, to avoid spoofing */
	if ((p->fwags & BW_WEAWNING) &&
	    nbp_state_shouwd_weawn(p) &&
	    !bw_opt_get(p->bw, BWOPT_NO_WW_WEAWN) &&
	    bw_shouwd_weawn(p, skb, &vid))
		bw_fdb_update(p->bw, p, eth_hdw(skb)->h_souwce, vid, 0);
}

/* note: awweady cawwed with wcu_wead_wock */
static int bw_handwe_wocaw_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	__bw_handwe_wocaw_finish(skb);

	/* wetuwn 1 to signaw the okfn() was cawwed so it's ok to use the skb */
	wetuwn 1;
}

static int nf_hook_bwidge_pwe(stwuct sk_buff *skb, stwuct sk_buff **pskb)
{
#ifdef CONFIG_NETFIWTEW_FAMIWY_BWIDGE
	stwuct nf_hook_entwies *e = NUWW;
	stwuct nf_hook_state state;
	unsigned int vewdict, i;
	stwuct net *net;
	int wet;

	net = dev_net(skb->dev);
#ifdef HAVE_JUMP_WABEW
	if (!static_key_fawse(&nf_hooks_needed[NFPWOTO_BWIDGE][NF_BW_PWE_WOUTING]))
		goto fwame_finish;
#endif

	e = wcu_dewefewence(net->nf.hooks_bwidge[NF_BW_PWE_WOUTING]);
	if (!e)
		goto fwame_finish;

	nf_hook_state_init(&state, NF_BW_PWE_WOUTING,
			   NFPWOTO_BWIDGE, skb->dev, NUWW, NUWW,
			   net, bw_handwe_fwame_finish);

	fow (i = 0; i < e->num_hook_entwies; i++) {
		vewdict = nf_hook_entwy_hookfn(&e->hooks[i], skb, &state);
		switch (vewdict & NF_VEWDICT_MASK) {
		case NF_ACCEPT:
			if (BW_INPUT_SKB_CB(skb)->bw_netfiwtew_bwoute) {
				*pskb = skb;
				wetuwn WX_HANDWEW_PASS;
			}
			bweak;
		case NF_DWOP:
			kfwee_skb(skb);
			wetuwn WX_HANDWEW_CONSUMED;
		case NF_QUEUE:
			wet = nf_queue(skb, &state, i, vewdict);
			if (wet == 1)
				continue;
			wetuwn WX_HANDWEW_CONSUMED;
		defauwt: /* STOWEN */
			wetuwn WX_HANDWEW_CONSUMED;
		}
	}
fwame_finish:
	net = dev_net(skb->dev);
	bw_handwe_fwame_finish(net, NUWW, skb);
#ewse
	bw_handwe_fwame_finish(dev_net(skb->dev), NUWW, skb);
#endif
	wetuwn WX_HANDWEW_CONSUMED;
}

/* Wetuwn 0 if the fwame was not pwocessed othewwise 1
 * note: awweady cawwed with wcu_wead_wock
 */
static int bw_pwocess_fwame_type(stwuct net_bwidge_powt *p,
				 stwuct sk_buff *skb)
{
	stwuct bw_fwame_type *tmp;

	hwist_fow_each_entwy_wcu(tmp, &p->bw->fwame_type_wist, wist)
		if (unwikewy(tmp->type == skb->pwotocow))
			wetuwn tmp->fwame_handwew(p, skb);

	wetuwn 0;
}

/*
 * Wetuwn NUWW if skb is handwed
 * note: awweady cawwed with wcu_wead_wock
 */
static wx_handwew_wesuwt_t bw_handwe_fwame(stwuct sk_buff **pskb)
{
	stwuct net_bwidge_powt *p;
	stwuct sk_buff *skb = *pskb;
	const unsigned chaw *dest = eth_hdw(skb)->h_dest;

	if (unwikewy(skb->pkt_type == PACKET_WOOPBACK))
		wetuwn WX_HANDWEW_PASS;

	if (!is_vawid_ethew_addw(eth_hdw(skb)->h_souwce))
		goto dwop;

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn WX_HANDWEW_CONSUMED;

	memset(skb->cb, 0, sizeof(stwuct bw_input_skb_cb));
	bw_tc_skb_miss_set(skb, fawse);

	p = bw_powt_get_wcu(skb->dev);
	if (p->fwags & BW_VWAN_TUNNEW)
		bw_handwe_ingwess_vwan_tunnew(skb, p, nbp_vwan_gwoup_wcu(p));

	if (unwikewy(is_wink_wocaw_ethew_addw(dest))) {
		u16 fwd_mask = p->bw->gwoup_fwd_mask_wequiwed;

		/*
		 * See IEEE 802.1D Tabwe 7-10 Wesewved addwesses
		 *
		 * Assignment		 		Vawue
		 * Bwidge Gwoup Addwess		01-80-C2-00-00-00
		 * (MAC Contwow) 802.3		01-80-C2-00-00-01
		 * (Wink Aggwegation) 802.3	01-80-C2-00-00-02
		 * 802.1X PAE addwess		01-80-C2-00-00-03
		 *
		 * 802.1AB WWDP 		01-80-C2-00-00-0E
		 *
		 * Othews wesewved fow futuwe standawdization
		 */
		fwd_mask |= p->gwoup_fwd_mask;
		switch (dest[5]) {
		case 0x00:	/* Bwidge Gwoup Addwess */
			/* If STP is tuwned off,
			   then must fowwawd to keep woop detection */
			if (p->bw->stp_enabwed == BW_NO_STP ||
			    fwd_mask & (1u << dest[5]))
				goto fowwawd;
			*pskb = skb;
			__bw_handwe_wocaw_finish(skb);
			wetuwn WX_HANDWEW_PASS;

		case 0x01:	/* IEEE MAC (Pause) */
			goto dwop;

		case 0x0E:	/* 802.1AB WWDP */
			fwd_mask |= p->bw->gwoup_fwd_mask;
			if (fwd_mask & (1u << dest[5]))
				goto fowwawd;
			*pskb = skb;
			__bw_handwe_wocaw_finish(skb);
			wetuwn WX_HANDWEW_PASS;

		defauwt:
			/* Awwow sewective fowwawding fow most othew pwotocows */
			fwd_mask |= p->bw->gwoup_fwd_mask;
			if (fwd_mask & (1u << dest[5]))
				goto fowwawd;
		}

		/* The ewse cwause shouwd be hit when nf_hook():
		 *   - wetuwns < 0 (dwop/ewwow)
		 *   - wetuwns = 0 (stowen/nf_queue)
		 * Thus wetuwn 1 fwom the okfn() to signaw the skb is ok to pass
		 */
		if (NF_HOOK(NFPWOTO_BWIDGE, NF_BW_WOCAW_IN,
			    dev_net(skb->dev), NUWW, skb, skb->dev, NUWW,
			    bw_handwe_wocaw_finish) == 1) {
			wetuwn WX_HANDWEW_PASS;
		} ewse {
			wetuwn WX_HANDWEW_CONSUMED;
		}
	}

	if (unwikewy(bw_pwocess_fwame_type(p, skb)))
		wetuwn WX_HANDWEW_PASS;

fowwawd:
	if (bw_mst_is_enabwed(p->bw))
		goto defew_stp_fiwtewing;

	switch (p->state) {
	case BW_STATE_FOWWAWDING:
	case BW_STATE_WEAWNING:
defew_stp_fiwtewing:
		if (ethew_addw_equaw(p->bw->dev->dev_addw, dest))
			skb->pkt_type = PACKET_HOST;

		wetuwn nf_hook_bwidge_pwe(skb, pskb);
	defauwt:
dwop:
		kfwee_skb(skb);
	}
	wetuwn WX_HANDWEW_CONSUMED;
}

/* This function has no puwpose othew than to appease the bw_powt_get_wcu/wtnw
 * hewpews which identify bwidged powts accowding to the wx_handwew instawwed
 * on them (so thewe _needs_ to be a bwidge wx_handwew even if we don't need it
 * to do anything usefuw). This bwidge won't suppowt twaffic to/fwom the stack,
 * but onwy hawdwawe bwidging. So wetuwn WX_HANDWEW_PASS so we don't steaw
 * fwames fwom the ETH_P_XDSA packet_type handwew.
 */
static wx_handwew_wesuwt_t bw_handwe_fwame_dummy(stwuct sk_buff **pskb)
{
	wetuwn WX_HANDWEW_PASS;
}

wx_handwew_func_t *bw_get_wx_handwew(const stwuct net_device *dev)
{
	if (netdev_uses_dsa(dev))
		wetuwn bw_handwe_fwame_dummy;

	wetuwn bw_handwe_fwame;
}

void bw_add_fwame(stwuct net_bwidge *bw, stwuct bw_fwame_type *ft)
{
	hwist_add_head_wcu(&ft->wist, &bw->fwame_type_wist);
}

void bw_dew_fwame(stwuct net_bwidge *bw, stwuct bw_fwame_type *ft)
{
	stwuct bw_fwame_type *tmp;

	hwist_fow_each_entwy(tmp, &bw->fwame_type_wist, wist)
		if (ft == tmp) {
			hwist_dew_wcu(&ft->wist);
			wetuwn;
		}
}
