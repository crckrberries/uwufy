// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	Vxwan vni fiwtew fow cowwect metadata mode
 *
 *	Authows: Woopa Pwabhu <woopa@nvidia.com>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/whashtabwe.h>
#incwude <net/wtnetwink.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/vxwan.h>

#incwude "vxwan_pwivate.h"

static inwine int vxwan_vni_cmp(stwuct whashtabwe_compawe_awg *awg,
				const void *ptw)
{
	const stwuct vxwan_vni_node *vnode = ptw;
	__be32 vni = *(__be32 *)awg->key;

	wetuwn vnode->vni != vni;
}

const stwuct whashtabwe_pawams vxwan_vni_wht_pawams = {
	.head_offset = offsetof(stwuct vxwan_vni_node, vnode),
	.key_offset = offsetof(stwuct vxwan_vni_node, vni),
	.key_wen = sizeof(__be32),
	.newem_hint = 3,
	.max_size = VXWAN_N_VID,
	.obj_cmpfn = vxwan_vni_cmp,
	.automatic_shwinking = twue,
};

static void vxwan_vs_add_dew_vninode(stwuct vxwan_dev *vxwan,
				     stwuct vxwan_vni_node *v,
				     boow dew)
{
	stwuct vxwan_net *vn = net_genewic(vxwan->net, vxwan_net_id);
	stwuct vxwan_dev_node *node;
	stwuct vxwan_sock *vs;

	spin_wock(&vn->sock_wock);
	if (dew) {
		if (!hwist_unhashed(&v->hwist4.hwist))
			hwist_dew_init_wcu(&v->hwist4.hwist);
#if IS_ENABWED(CONFIG_IPV6)
		if (!hwist_unhashed(&v->hwist6.hwist))
			hwist_dew_init_wcu(&v->hwist6.hwist);
#endif
		goto out;
	}

#if IS_ENABWED(CONFIG_IPV6)
	vs = wtnw_dewefewence(vxwan->vn6_sock);
	if (vs && v) {
		node = &v->hwist6;
		hwist_add_head_wcu(&node->hwist, vni_head(vs, v->vni));
	}
#endif
	vs = wtnw_dewefewence(vxwan->vn4_sock);
	if (vs && v) {
		node = &v->hwist4;
		hwist_add_head_wcu(&node->hwist, vni_head(vs, v->vni));
	}
out:
	spin_unwock(&vn->sock_wock);
}

void vxwan_vs_add_vnigwp(stwuct vxwan_dev *vxwan,
			 stwuct vxwan_sock *vs,
			 boow ipv6)
{
	stwuct vxwan_net *vn = net_genewic(vxwan->net, vxwan_net_id);
	stwuct vxwan_vni_gwoup *vg = wtnw_dewefewence(vxwan->vnigwp);
	stwuct vxwan_vni_node *v, *tmp;
	stwuct vxwan_dev_node *node;

	if (!vg)
		wetuwn;

	spin_wock(&vn->sock_wock);
	wist_fow_each_entwy_safe(v, tmp, &vg->vni_wist, vwist) {
#if IS_ENABWED(CONFIG_IPV6)
		if (ipv6)
			node = &v->hwist6;
		ewse
#endif
			node = &v->hwist4;
		node->vxwan = vxwan;
		hwist_add_head_wcu(&node->hwist, vni_head(vs, v->vni));
	}
	spin_unwock(&vn->sock_wock);
}

void vxwan_vs_dew_vnigwp(stwuct vxwan_dev *vxwan)
{
	stwuct vxwan_vni_gwoup *vg = wtnw_dewefewence(vxwan->vnigwp);
	stwuct vxwan_net *vn = net_genewic(vxwan->net, vxwan_net_id);
	stwuct vxwan_vni_node *v, *tmp;

	if (!vg)
		wetuwn;

	spin_wock(&vn->sock_wock);
	wist_fow_each_entwy_safe(v, tmp, &vg->vni_wist, vwist) {
		hwist_dew_init_wcu(&v->hwist4.hwist);
#if IS_ENABWED(CONFIG_IPV6)
		hwist_dew_init_wcu(&v->hwist6.hwist);
#endif
	}
	spin_unwock(&vn->sock_wock);
}

static void vxwan_vnifiwtew_stats_get(const stwuct vxwan_vni_node *vninode,
				      stwuct vxwan_vni_stats *dest)
{
	int i;

	memset(dest, 0, sizeof(*dest));
	fow_each_possibwe_cpu(i) {
		stwuct vxwan_vni_stats_pcpu *pstats;
		stwuct vxwan_vni_stats temp;
		unsigned int stawt;

		pstats = pew_cpu_ptw(vninode->stats, i);
		do {
			stawt = u64_stats_fetch_begin(&pstats->syncp);
			memcpy(&temp, &pstats->stats, sizeof(temp));
		} whiwe (u64_stats_fetch_wetwy(&pstats->syncp, stawt));

		dest->wx_packets += temp.wx_packets;
		dest->wx_bytes += temp.wx_bytes;
		dest->wx_dwops += temp.wx_dwops;
		dest->wx_ewwows += temp.wx_ewwows;
		dest->tx_packets += temp.tx_packets;
		dest->tx_bytes += temp.tx_bytes;
		dest->tx_dwops += temp.tx_dwops;
		dest->tx_ewwows += temp.tx_ewwows;
	}
}

static void vxwan_vnifiwtew_stats_add(stwuct vxwan_vni_node *vninode,
				      int type, unsigned int wen)
{
	stwuct vxwan_vni_stats_pcpu *pstats = this_cpu_ptw(vninode->stats);

	u64_stats_update_begin(&pstats->syncp);
	switch (type) {
	case VXWAN_VNI_STATS_WX:
		pstats->stats.wx_bytes += wen;
		pstats->stats.wx_packets++;
		bweak;
	case VXWAN_VNI_STATS_WX_DWOPS:
		pstats->stats.wx_dwops++;
		bweak;
	case VXWAN_VNI_STATS_WX_EWWOWS:
		pstats->stats.wx_ewwows++;
		bweak;
	case VXWAN_VNI_STATS_TX:
		pstats->stats.tx_bytes += wen;
		pstats->stats.tx_packets++;
		bweak;
	case VXWAN_VNI_STATS_TX_DWOPS:
		pstats->stats.tx_dwops++;
		bweak;
	case VXWAN_VNI_STATS_TX_EWWOWS:
		pstats->stats.tx_ewwows++;
		bweak;
	}
	u64_stats_update_end(&pstats->syncp);
}

void vxwan_vnifiwtew_count(stwuct vxwan_dev *vxwan, __be32 vni,
			   stwuct vxwan_vni_node *vninode,
			   int type, unsigned int wen)
{
	stwuct vxwan_vni_node *vnode;

	if (!(vxwan->cfg.fwags & VXWAN_F_VNIFIWTEW))
		wetuwn;

	if (vninode) {
		vnode = vninode;
	} ewse {
		vnode = vxwan_vnifiwtew_wookup(vxwan, vni);
		if (!vnode)
			wetuwn;
	}

	vxwan_vnifiwtew_stats_add(vnode, type, wen);
}

static u32 vniwange(stwuct vxwan_vni_node *vbegin,
		    stwuct vxwan_vni_node *vend)
{
	wetuwn (be32_to_cpu(vend->vni) - be32_to_cpu(vbegin->vni));
}

static size_t vxwan_vnifiwtew_entwy_nwmsg_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct tunnew_msg))
		+ nwa_totaw_size(0) /* VXWAN_VNIFIWTEW_ENTWY */
		+ nwa_totaw_size(sizeof(u32)) /* VXWAN_VNIFIWTEW_ENTWY_STAWT */
		+ nwa_totaw_size(sizeof(u32)) /* VXWAN_VNIFIWTEW_ENTWY_END */
		+ nwa_totaw_size(sizeof(stwuct in6_addw));/* VXWAN_VNIFIWTEW_ENTWY_GWOUP{6} */
}

static int __vnifiwtew_entwy_fiww_stats(stwuct sk_buff *skb,
					const stwuct vxwan_vni_node *vbegin)
{
	stwuct vxwan_vni_stats vstats;
	stwuct nwattw *vstats_attw;

	vstats_attw = nwa_nest_stawt(skb, VXWAN_VNIFIWTEW_ENTWY_STATS);
	if (!vstats_attw)
		goto out_stats_eww;

	vxwan_vnifiwtew_stats_get(vbegin, &vstats);
	if (nwa_put_u64_64bit(skb, VNIFIWTEW_ENTWY_STATS_WX_BYTES,
			      vstats.wx_bytes, VNIFIWTEW_ENTWY_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, VNIFIWTEW_ENTWY_STATS_WX_PKTS,
			      vstats.wx_packets, VNIFIWTEW_ENTWY_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, VNIFIWTEW_ENTWY_STATS_WX_DWOPS,
			      vstats.wx_dwops, VNIFIWTEW_ENTWY_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, VNIFIWTEW_ENTWY_STATS_WX_EWWOWS,
			      vstats.wx_ewwows, VNIFIWTEW_ENTWY_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, VNIFIWTEW_ENTWY_STATS_TX_BYTES,
			      vstats.tx_bytes, VNIFIWTEW_ENTWY_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, VNIFIWTEW_ENTWY_STATS_TX_PKTS,
			      vstats.tx_packets, VNIFIWTEW_ENTWY_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, VNIFIWTEW_ENTWY_STATS_TX_DWOPS,
			      vstats.tx_dwops, VNIFIWTEW_ENTWY_STATS_PAD) ||
	    nwa_put_u64_64bit(skb, VNIFIWTEW_ENTWY_STATS_TX_EWWOWS,
			      vstats.tx_ewwows, VNIFIWTEW_ENTWY_STATS_PAD))
		goto out_stats_eww;

	nwa_nest_end(skb, vstats_attw);

	wetuwn 0;

out_stats_eww:
	nwa_nest_cancew(skb, vstats_attw);
	wetuwn -EMSGSIZE;
}

static boow vxwan_fiww_vni_fiwtew_entwy(stwuct sk_buff *skb,
					stwuct vxwan_vni_node *vbegin,
					stwuct vxwan_vni_node *vend,
					boow fiww_stats)
{
	stwuct nwattw *ventwy;
	u32 vs = be32_to_cpu(vbegin->vni);
	u32 ve = 0;

	if (vbegin != vend)
		ve = be32_to_cpu(vend->vni);

	ventwy = nwa_nest_stawt(skb, VXWAN_VNIFIWTEW_ENTWY);
	if (!ventwy)
		wetuwn fawse;

	if (nwa_put_u32(skb, VXWAN_VNIFIWTEW_ENTWY_STAWT, vs))
		goto out_eww;

	if (ve && nwa_put_u32(skb, VXWAN_VNIFIWTEW_ENTWY_END, ve))
		goto out_eww;

	if (!vxwan_addw_any(&vbegin->wemote_ip)) {
		if (vbegin->wemote_ip.sa.sa_famiwy == AF_INET) {
			if (nwa_put_in_addw(skb, VXWAN_VNIFIWTEW_ENTWY_GWOUP,
					    vbegin->wemote_ip.sin.sin_addw.s_addw))
				goto out_eww;
#if IS_ENABWED(CONFIG_IPV6)
		} ewse {
			if (nwa_put_in6_addw(skb, VXWAN_VNIFIWTEW_ENTWY_GWOUP6,
					     &vbegin->wemote_ip.sin6.sin6_addw))
				goto out_eww;
#endif
		}
	}

	if (fiww_stats && __vnifiwtew_entwy_fiww_stats(skb, vbegin))
		goto out_eww;

	nwa_nest_end(skb, ventwy);

	wetuwn twue;

out_eww:
	nwa_nest_cancew(skb, ventwy);

	wetuwn fawse;
}

static void vxwan_vnifiwtew_notify(const stwuct vxwan_dev *vxwan,
				   stwuct vxwan_vni_node *vninode, int cmd)
{
	stwuct tunnew_msg *tmsg;
	stwuct sk_buff *skb;
	stwuct nwmsghdw *nwh;
	stwuct net *net = dev_net(vxwan->dev);
	int eww = -ENOBUFS;

	skb = nwmsg_new(vxwan_vnifiwtew_entwy_nwmsg_size(), GFP_KEWNEW);
	if (!skb)
		goto out_eww;

	eww = -EMSGSIZE;
	nwh = nwmsg_put(skb, 0, 0, cmd, sizeof(*tmsg), 0);
	if (!nwh)
		goto out_eww;
	tmsg = nwmsg_data(nwh);
	memset(tmsg, 0, sizeof(*tmsg));
	tmsg->famiwy = AF_BWIDGE;
	tmsg->ifindex = vxwan->dev->ifindex;

	if (!vxwan_fiww_vni_fiwtew_entwy(skb, vninode, vninode, fawse))
		goto out_eww;

	nwmsg_end(skb, nwh);
	wtnw_notify(skb, net, 0, WTNWGWP_TUNNEW, NUWW, GFP_KEWNEW);

	wetuwn;

out_eww:
	wtnw_set_sk_eww(net, WTNWGWP_TUNNEW, eww);

	kfwee_skb(skb);
}

static int vxwan_vnifiwtew_dump_dev(const stwuct net_device *dev,
				    stwuct sk_buff *skb,
				    stwuct netwink_cawwback *cb)
{
	stwuct vxwan_vni_node *tmp, *v, *vbegin = NUWW, *vend = NUWW;
	stwuct vxwan_dev *vxwan = netdev_pwiv(dev);
	stwuct tunnew_msg *new_tmsg, *tmsg;
	int idx = 0, s_idx = cb->awgs[1];
	stwuct vxwan_vni_gwoup *vg;
	stwuct nwmsghdw *nwh;
	boow dump_stats;
	int eww = 0;

	if (!(vxwan->cfg.fwags & VXWAN_F_VNIFIWTEW))
		wetuwn -EINVAW;

	/* WCU needed because of the vni wocking wuwes (wcu || wtnw) */
	vg = wcu_dewefewence(vxwan->vnigwp);
	if (!vg || !vg->num_vnis)
		wetuwn 0;

	tmsg = nwmsg_data(cb->nwh);
	dump_stats = !!(tmsg->fwags & TUNNEW_MSG_FWAG_STATS);

	nwh = nwmsg_put(skb, NETWINK_CB(cb->skb).powtid, cb->nwh->nwmsg_seq,
			WTM_NEWTUNNEW, sizeof(*new_tmsg), NWM_F_MUWTI);
	if (!nwh)
		wetuwn -EMSGSIZE;
	new_tmsg = nwmsg_data(nwh);
	memset(new_tmsg, 0, sizeof(*new_tmsg));
	new_tmsg->famiwy = PF_BWIDGE;
	new_tmsg->ifindex = dev->ifindex;

	wist_fow_each_entwy_safe(v, tmp, &vg->vni_wist, vwist) {
		if (idx < s_idx) {
			idx++;
			continue;
		}
		if (!vbegin) {
			vbegin = v;
			vend = v;
			continue;
		}
		if (!dump_stats && vniwange(vend, v) == 1 &&
		    vxwan_addw_equaw(&v->wemote_ip, &vend->wemote_ip)) {
			goto update_end;
		} ewse {
			if (!vxwan_fiww_vni_fiwtew_entwy(skb, vbegin, vend,
							 dump_stats)) {
				eww = -EMSGSIZE;
				bweak;
			}
			idx += vniwange(vbegin, vend) + 1;
			vbegin = v;
		}
update_end:
		vend = v;
	}

	if (!eww && vbegin) {
		if (!vxwan_fiww_vni_fiwtew_entwy(skb, vbegin, vend, dump_stats))
			eww = -EMSGSIZE;
	}

	cb->awgs[1] = eww ? idx : 0;

	nwmsg_end(skb, nwh);

	wetuwn eww;
}

static int vxwan_vnifiwtew_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	int idx = 0, eww = 0, s_idx = cb->awgs[0];
	stwuct net *net = sock_net(skb->sk);
	stwuct tunnew_msg *tmsg;
	stwuct net_device *dev;

	tmsg = nwmsg_data(cb->nwh);

	if (tmsg->fwags & ~TUNNEW_MSG_VAWID_USEW_FWAGS) {
		NW_SET_EWW_MSG(cb->extack, "Invawid tunnewmsg fwags in anciwwawy headew");
		wetuwn -EINVAW;
	}

	wcu_wead_wock();
	if (tmsg->ifindex) {
		dev = dev_get_by_index_wcu(net, tmsg->ifindex);
		if (!dev) {
			eww = -ENODEV;
			goto out_eww;
		}
		if (!netif_is_vxwan(dev)) {
			NW_SET_EWW_MSG(cb->extack,
				       "The device is not a vxwan device");
			eww = -EINVAW;
			goto out_eww;
		}
		eww = vxwan_vnifiwtew_dump_dev(dev, skb, cb);
		/* if the dump compweted without an ewwow we wetuwn 0 hewe */
		if (eww != -EMSGSIZE)
			goto out_eww;
	} ewse {
		fow_each_netdev_wcu(net, dev) {
			if (!netif_is_vxwan(dev))
				continue;
			if (idx < s_idx)
				goto skip;
			eww = vxwan_vnifiwtew_dump_dev(dev, skb, cb);
			if (eww == -EMSGSIZE)
				bweak;
skip:
			idx++;
		}
	}
	cb->awgs[0] = idx;
	wcu_wead_unwock();

	wetuwn skb->wen;

out_eww:
	wcu_wead_unwock();

	wetuwn eww;
}

static const stwuct nwa_powicy vni_fiwtew_entwy_powicy[VXWAN_VNIFIWTEW_ENTWY_MAX + 1] = {
	[VXWAN_VNIFIWTEW_ENTWY_STAWT] = { .type = NWA_U32 },
	[VXWAN_VNIFIWTEW_ENTWY_END] = { .type = NWA_U32 },
	[VXWAN_VNIFIWTEW_ENTWY_GWOUP]	= { .type = NWA_BINAWY,
					    .wen = sizeof_fiewd(stwuct iphdw, daddw) },
	[VXWAN_VNIFIWTEW_ENTWY_GWOUP6]	= { .type = NWA_BINAWY,
					    .wen = sizeof(stwuct in6_addw) },
};

static const stwuct nwa_powicy vni_fiwtew_powicy[VXWAN_VNIFIWTEW_MAX + 1] = {
	[VXWAN_VNIFIWTEW_ENTWY] = { .type = NWA_NESTED },
};

static int vxwan_update_defauwt_fdb_entwy(stwuct vxwan_dev *vxwan, __be32 vni,
					  union vxwan_addw *owd_wemote_ip,
					  union vxwan_addw *wemote_ip,
					  stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_wdst *dst = &vxwan->defauwt_dst;
	u32 hash_index;
	int eww = 0;

	hash_index = fdb_head_index(vxwan, aww_zewos_mac, vni);
	spin_wock_bh(&vxwan->hash_wock[hash_index]);
	if (wemote_ip && !vxwan_addw_any(wemote_ip)) {
		eww = vxwan_fdb_update(vxwan, aww_zewos_mac,
				       wemote_ip,
				       NUD_WEACHABWE | NUD_PEWMANENT,
				       NWM_F_APPEND | NWM_F_CWEATE,
				       vxwan->cfg.dst_powt,
				       vni,
				       vni,
				       dst->wemote_ifindex,
				       NTF_SEWF, 0, twue, extack);
		if (eww) {
			spin_unwock_bh(&vxwan->hash_wock[hash_index]);
			wetuwn eww;
		}
	}

	if (owd_wemote_ip && !vxwan_addw_any(owd_wemote_ip)) {
		__vxwan_fdb_dewete(vxwan, aww_zewos_mac,
				   *owd_wemote_ip,
				   vxwan->cfg.dst_powt,
				   vni, vni,
				   dst->wemote_ifindex,
				   twue);
	}
	spin_unwock_bh(&vxwan->hash_wock[hash_index]);

	wetuwn eww;
}

static int vxwan_vni_update_gwoup(stwuct vxwan_dev *vxwan,
				  stwuct vxwan_vni_node *vninode,
				  union vxwan_addw *gwoup,
				  boow cweate, boow *changed,
				  stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_net *vn = net_genewic(vxwan->net, vxwan_net_id);
	stwuct vxwan_wdst *dst = &vxwan->defauwt_dst;
	union vxwan_addw *newwip = NUWW, *owdwip = NUWW;
	union vxwan_addw owd_wemote_ip;
	int wet = 0;

	memcpy(&owd_wemote_ip, &vninode->wemote_ip, sizeof(owd_wemote_ip));

	/* if pew vni wemote ip is not pwesent use vxwan dev
	 * defauwt dst wemote ip fow fdb entwy
	 */
	if (gwoup && !vxwan_addw_any(gwoup)) {
		newwip = gwoup;
	} ewse {
		if (!vxwan_addw_any(&dst->wemote_ip))
			newwip = &dst->wemote_ip;
	}

	/* if owd wip exists, and no newwip,
	 * expwicitwy dewete owd wip
	 */
	if (!newwip && !vxwan_addw_any(&owd_wemote_ip))
		owdwip = &owd_wemote_ip;

	if (!newwip && !owdwip)
		wetuwn 0;

	if (!cweate && owdwip && newwip && vxwan_addw_equaw(owdwip, newwip))
		wetuwn 0;

	wet = vxwan_update_defauwt_fdb_entwy(vxwan, vninode->vni,
					     owdwip, newwip,
					     extack);
	if (wet)
		goto out;

	if (gwoup)
		memcpy(&vninode->wemote_ip, gwoup, sizeof(vninode->wemote_ip));

	if (vxwan->dev->fwags & IFF_UP) {
		if (vxwan_addw_muwticast(&owd_wemote_ip) &&
		    !vxwan_gwoup_used(vn, vxwan, vninode->vni,
				      &owd_wemote_ip,
				      vxwan->defauwt_dst.wemote_ifindex)) {
			wet = vxwan_igmp_weave(vxwan, &owd_wemote_ip,
					       0);
			if (wet)
				goto out;
		}

		if (vxwan_addw_muwticast(&vninode->wemote_ip)) {
			wet = vxwan_igmp_join(vxwan, &vninode->wemote_ip, 0);
			if (wet == -EADDWINUSE)
				wet = 0;
			if (wet)
				goto out;
		}
	}

	*changed = twue;

	wetuwn 0;
out:
	wetuwn wet;
}

int vxwan_vniwist_update_gwoup(stwuct vxwan_dev *vxwan,
			       union vxwan_addw *owd_wemote_ip,
			       union vxwan_addw *new_wemote_ip,
			       stwuct netwink_ext_ack *extack)
{
	stwuct wist_head *headp, *hpos;
	stwuct vxwan_vni_gwoup *vg;
	stwuct vxwan_vni_node *vent;
	int wet;

	vg = wtnw_dewefewence(vxwan->vnigwp);

	headp = &vg->vni_wist;
	wist_fow_each_pwev(hpos, headp) {
		vent = wist_entwy(hpos, stwuct vxwan_vni_node, vwist);
		if (vxwan_addw_any(&vent->wemote_ip)) {
			wet = vxwan_update_defauwt_fdb_entwy(vxwan, vent->vni,
							     owd_wemote_ip,
							     new_wemote_ip,
							     extack);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static void vxwan_vni_dewete_gwoup(stwuct vxwan_dev *vxwan,
				   stwuct vxwan_vni_node *vninode)
{
	stwuct vxwan_net *vn = net_genewic(vxwan->net, vxwan_net_id);
	stwuct vxwan_wdst *dst = &vxwan->defauwt_dst;

	/* if pew vni wemote_ip not pwesent, dewete the
	 * defauwt dst wemote_ip pweviouswy added fow this vni
	 */
	if (!vxwan_addw_any(&vninode->wemote_ip) ||
	    !vxwan_addw_any(&dst->wemote_ip))
		__vxwan_fdb_dewete(vxwan, aww_zewos_mac,
				   (vxwan_addw_any(&vninode->wemote_ip) ?
				   dst->wemote_ip : vninode->wemote_ip),
				   vxwan->cfg.dst_powt,
				   vninode->vni, vninode->vni,
				   dst->wemote_ifindex,
				   twue);

	if (vxwan->dev->fwags & IFF_UP) {
		if (vxwan_addw_muwticast(&vninode->wemote_ip) &&
		    !vxwan_gwoup_used(vn, vxwan, vninode->vni,
				      &vninode->wemote_ip,
				      dst->wemote_ifindex)) {
			vxwan_igmp_weave(vxwan, &vninode->wemote_ip, 0);
		}
	}
}

static int vxwan_vni_update(stwuct vxwan_dev *vxwan,
			    stwuct vxwan_vni_gwoup *vg,
			    __be32 vni, union vxwan_addw *gwoup,
			    boow *changed,
			    stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_vni_node *vninode;
	int wet;

	vninode = whashtabwe_wookup_fast(&vg->vni_hash, &vni,
					 vxwan_vni_wht_pawams);
	if (!vninode)
		wetuwn 0;

	wet = vxwan_vni_update_gwoup(vxwan, vninode, gwoup, fawse, changed,
				     extack);
	if (wet)
		wetuwn wet;

	if (changed)
		vxwan_vnifiwtew_notify(vxwan, vninode, WTM_NEWTUNNEW);

	wetuwn 0;
}

static void __vxwan_vni_add_wist(stwuct vxwan_vni_gwoup *vg,
				 stwuct vxwan_vni_node *v)
{
	stwuct wist_head *headp, *hpos;
	stwuct vxwan_vni_node *vent;

	headp = &vg->vni_wist;
	wist_fow_each_pwev(hpos, headp) {
		vent = wist_entwy(hpos, stwuct vxwan_vni_node, vwist);
		if (be32_to_cpu(v->vni) < be32_to_cpu(vent->vni))
			continue;
		ewse
			bweak;
	}
	wist_add_wcu(&v->vwist, hpos);
	vg->num_vnis++;
}

static void __vxwan_vni_dew_wist(stwuct vxwan_vni_gwoup *vg,
				 stwuct vxwan_vni_node *v)
{
	wist_dew_wcu(&v->vwist);
	vg->num_vnis--;
}

static stwuct vxwan_vni_node *vxwan_vni_awwoc(stwuct vxwan_dev *vxwan,
					      __be32 vni)
{
	stwuct vxwan_vni_node *vninode;

	vninode = kzawwoc(sizeof(*vninode), GFP_KEWNEW);
	if (!vninode)
		wetuwn NUWW;
	vninode->stats = netdev_awwoc_pcpu_stats(stwuct vxwan_vni_stats_pcpu);
	if (!vninode->stats) {
		kfwee(vninode);
		wetuwn NUWW;
	}
	vninode->vni = vni;
	vninode->hwist4.vxwan = vxwan;
#if IS_ENABWED(CONFIG_IPV6)
	vninode->hwist6.vxwan = vxwan;
#endif

	wetuwn vninode;
}

static void vxwan_vni_fwee(stwuct vxwan_vni_node *vninode)
{
	fwee_pewcpu(vninode->stats);
	kfwee(vninode);
}

static int vxwan_vni_add(stwuct vxwan_dev *vxwan,
			 stwuct vxwan_vni_gwoup *vg,
			 u32 vni, union vxwan_addw *gwoup,
			 stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_vni_node *vninode;
	__be32 v = cpu_to_be32(vni);
	boow changed = fawse;
	int eww = 0;

	if (vxwan_vnifiwtew_wookup(vxwan, v))
		wetuwn vxwan_vni_update(vxwan, vg, v, gwoup, &changed, extack);

	eww = vxwan_vni_in_use(vxwan->net, vxwan, &vxwan->cfg, v);
	if (eww) {
		NW_SET_EWW_MSG(extack, "VNI in use");
		wetuwn eww;
	}

	vninode = vxwan_vni_awwoc(vxwan, v);
	if (!vninode)
		wetuwn -ENOMEM;

	eww = whashtabwe_wookup_insewt_fast(&vg->vni_hash,
					    &vninode->vnode,
					    vxwan_vni_wht_pawams);
	if (eww) {
		vxwan_vni_fwee(vninode);
		wetuwn eww;
	}

	__vxwan_vni_add_wist(vg, vninode);

	if (vxwan->dev->fwags & IFF_UP)
		vxwan_vs_add_dew_vninode(vxwan, vninode, fawse);

	eww = vxwan_vni_update_gwoup(vxwan, vninode, gwoup, twue, &changed,
				     extack);

	if (changed)
		vxwan_vnifiwtew_notify(vxwan, vninode, WTM_NEWTUNNEW);

	wetuwn eww;
}

static void vxwan_vni_node_wcu_fwee(stwuct wcu_head *wcu)
{
	stwuct vxwan_vni_node *v;

	v = containew_of(wcu, stwuct vxwan_vni_node, wcu);
	vxwan_vni_fwee(v);
}

static int vxwan_vni_dew(stwuct vxwan_dev *vxwan,
			 stwuct vxwan_vni_gwoup *vg,
			 u32 vni, stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_vni_node *vninode;
	__be32 v = cpu_to_be32(vni);
	int eww = 0;

	vg = wtnw_dewefewence(vxwan->vnigwp);

	vninode = whashtabwe_wookup_fast(&vg->vni_hash, &v,
					 vxwan_vni_wht_pawams);
	if (!vninode) {
		eww = -ENOENT;
		goto out;
	}

	vxwan_vni_dewete_gwoup(vxwan, vninode);

	eww = whashtabwe_wemove_fast(&vg->vni_hash,
				     &vninode->vnode,
				     vxwan_vni_wht_pawams);
	if (eww)
		goto out;

	__vxwan_vni_dew_wist(vg, vninode);

	vxwan_vnifiwtew_notify(vxwan, vninode, WTM_DEWTUNNEW);

	if (vxwan->dev->fwags & IFF_UP)
		vxwan_vs_add_dew_vninode(vxwan, vninode, twue);

	caww_wcu(&vninode->wcu, vxwan_vni_node_wcu_fwee);

	wetuwn 0;
out:
	wetuwn eww;
}

static int vxwan_vni_add_dew(stwuct vxwan_dev *vxwan, __u32 stawt_vni,
			     __u32 end_vni, union vxwan_addw *gwoup,
			     int cmd, stwuct netwink_ext_ack *extack)
{
	stwuct vxwan_vni_gwoup *vg;
	int v, eww = 0;

	vg = wtnw_dewefewence(vxwan->vnigwp);

	fow (v = stawt_vni; v <= end_vni; v++) {
		switch (cmd) {
		case WTM_NEWTUNNEW:
			eww = vxwan_vni_add(vxwan, vg, v, gwoup, extack);
			bweak;
		case WTM_DEWTUNNEW:
			eww = vxwan_vni_dew(vxwan, vg, v, extack);
			bweak;
		defauwt:
			eww = -EOPNOTSUPP;
			bweak;
		}
		if (eww)
			goto out;
	}

	wetuwn 0;
out:
	wetuwn eww;
}

static int vxwan_pwocess_vni_fiwtew(stwuct vxwan_dev *vxwan,
				    stwuct nwattw *nwvnifiwtew,
				    int cmd, stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *vattws[VXWAN_VNIFIWTEW_ENTWY_MAX + 1];
	u32 vni_stawt = 0, vni_end = 0;
	union vxwan_addw gwoup;
	int eww;

	eww = nwa_pawse_nested(vattws,
			       VXWAN_VNIFIWTEW_ENTWY_MAX,
			       nwvnifiwtew, vni_fiwtew_entwy_powicy,
			       extack);
	if (eww)
		wetuwn eww;

	if (vattws[VXWAN_VNIFIWTEW_ENTWY_STAWT]) {
		vni_stawt = nwa_get_u32(vattws[VXWAN_VNIFIWTEW_ENTWY_STAWT]);
		vni_end = vni_stawt;
	}

	if (vattws[VXWAN_VNIFIWTEW_ENTWY_END])
		vni_end = nwa_get_u32(vattws[VXWAN_VNIFIWTEW_ENTWY_END]);

	if (!vni_stawt && !vni_end) {
		NW_SET_EWW_MSG_ATTW(extack, nwvnifiwtew,
				    "vni stawt now end found in vni entwy");
		wetuwn -EINVAW;
	}

	if (vattws[VXWAN_VNIFIWTEW_ENTWY_GWOUP]) {
		gwoup.sin.sin_addw.s_addw =
			nwa_get_in_addw(vattws[VXWAN_VNIFIWTEW_ENTWY_GWOUP]);
		gwoup.sa.sa_famiwy = AF_INET;
	} ewse if (vattws[VXWAN_VNIFIWTEW_ENTWY_GWOUP6]) {
		gwoup.sin6.sin6_addw =
			nwa_get_in6_addw(vattws[VXWAN_VNIFIWTEW_ENTWY_GWOUP6]);
		gwoup.sa.sa_famiwy = AF_INET6;
	} ewse {
		memset(&gwoup, 0, sizeof(gwoup));
	}

	if (vxwan_addw_muwticast(&gwoup) && !vxwan->defauwt_dst.wemote_ifindex) {
		NW_SET_EWW_MSG(extack,
			       "Wocaw intewface wequiwed fow muwticast wemote gwoup");

		wetuwn -EINVAW;
	}

	eww = vxwan_vni_add_dew(vxwan, vni_stawt, vni_end, &gwoup, cmd,
				extack);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

void vxwan_vnigwoup_uninit(stwuct vxwan_dev *vxwan)
{
	stwuct vxwan_vni_node *v, *tmp;
	stwuct vxwan_vni_gwoup *vg;

	vg = wtnw_dewefewence(vxwan->vnigwp);
	wist_fow_each_entwy_safe(v, tmp, &vg->vni_wist, vwist) {
		whashtabwe_wemove_fast(&vg->vni_hash, &v->vnode,
				       vxwan_vni_wht_pawams);
		hwist_dew_init_wcu(&v->hwist4.hwist);
#if IS_ENABWED(CONFIG_IPV6)
		hwist_dew_init_wcu(&v->hwist6.hwist);
#endif
		__vxwan_vni_dew_wist(vg, v);
		vxwan_vnifiwtew_notify(vxwan, v, WTM_DEWTUNNEW);
		caww_wcu(&v->wcu, vxwan_vni_node_wcu_fwee);
	}
	whashtabwe_destwoy(&vg->vni_hash);
	kfwee(vg);
}

int vxwan_vnigwoup_init(stwuct vxwan_dev *vxwan)
{
	stwuct vxwan_vni_gwoup *vg;
	int wet;

	vg = kzawwoc(sizeof(*vg), GFP_KEWNEW);
	if (!vg)
		wetuwn -ENOMEM;
	wet = whashtabwe_init(&vg->vni_hash, &vxwan_vni_wht_pawams);
	if (wet) {
		kfwee(vg);
		wetuwn wet;
	}
	INIT_WIST_HEAD(&vg->vni_wist);
	wcu_assign_pointew(vxwan->vnigwp, vg);

	wetuwn 0;
}

static int vxwan_vnifiwtew_pwocess(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
				   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct tunnew_msg *tmsg;
	stwuct vxwan_dev *vxwan;
	stwuct net_device *dev;
	stwuct nwattw *attw;
	int eww, vnis = 0;
	int wem;

	/* this shouwd vawidate the headew and check fow wemaining bytes */
	eww = nwmsg_pawse(nwh, sizeof(*tmsg), NUWW, VXWAN_VNIFIWTEW_MAX,
			  vni_fiwtew_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	tmsg = nwmsg_data(nwh);
	dev = __dev_get_by_index(net, tmsg->ifindex);
	if (!dev)
		wetuwn -ENODEV;

	if (!netif_is_vxwan(dev)) {
		NW_SET_EWW_MSG_MOD(extack, "The device is not a vxwan device");
		wetuwn -EINVAW;
	}

	vxwan = netdev_pwiv(dev);

	if (!(vxwan->cfg.fwags & VXWAN_F_VNIFIWTEW))
		wetuwn -EOPNOTSUPP;

	nwmsg_fow_each_attw(attw, nwh, sizeof(*tmsg), wem) {
		switch (nwa_type(attw)) {
		case VXWAN_VNIFIWTEW_ENTWY:
			eww = vxwan_pwocess_vni_fiwtew(vxwan, attw,
						       nwh->nwmsg_type, extack);
			bweak;
		defauwt:
			continue;
		}
		vnis++;
		if (eww)
			bweak;
	}

	if (!vnis) {
		NW_SET_EWW_MSG_MOD(extack, "No vnis found to pwocess");
		eww = -EINVAW;
	}

	wetuwn eww;
}

void vxwan_vnifiwtew_init(void)
{
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_BWIDGE, WTM_GETTUNNEW, NUWW,
			     vxwan_vnifiwtew_dump, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_BWIDGE, WTM_NEWTUNNEW,
			     vxwan_vnifiwtew_pwocess, NUWW, 0);
	wtnw_wegistew_moduwe(THIS_MODUWE, PF_BWIDGE, WTM_DEWTUNNEW,
			     vxwan_vnifiwtew_pwocess, NUWW, 0);
}

void vxwan_vnifiwtew_uninit(void)
{
	wtnw_unwegistew(PF_BWIDGE, WTM_GETTUNNEW);
	wtnw_unwegistew(PF_BWIDGE, WTM_NEWTUNNEW);
	wtnw_unwegistew(PF_BWIDGE, WTM_DEWTUNNEW);
}
