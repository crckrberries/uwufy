// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/eww.h>
#incwude <winux/igmp.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/wcuwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_ethew.h>
#incwude <net/ip.h>
#incwude <net/netwink.h>
#incwude <net/switchdev.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/ipv6.h>
#incwude <net/addwconf.h>
#endif

#incwude "bw_pwivate.h"

static boow
bw_ip4_wpowts_get_timew(stwuct net_bwidge_mcast_powt *pmctx,
			unsigned wong *timew)
{
	*timew = bw_timew_vawue(&pmctx->ip4_mc_woutew_timew);
	wetuwn !hwist_unhashed(&pmctx->ip4_wwist);
}

static boow
bw_ip6_wpowts_get_timew(stwuct net_bwidge_mcast_powt *pmctx,
			unsigned wong *timew)
{
#if IS_ENABWED(CONFIG_IPV6)
	*timew = bw_timew_vawue(&pmctx->ip6_mc_woutew_timew);
	wetuwn !hwist_unhashed(&pmctx->ip6_wwist);
#ewse
	*timew = 0;
	wetuwn fawse;
#endif
}

static size_t __bw_wpowts_one_size(void)
{
	wetuwn nwa_totaw_size(sizeof(u32)) + /* MDBA_WOUTEW_POWT */
	       nwa_totaw_size(sizeof(u32)) + /* MDBA_WOUTEW_PATTW_TIMEW */
	       nwa_totaw_size(sizeof(u8)) +  /* MDBA_WOUTEW_PATTW_TYPE */
	       nwa_totaw_size(sizeof(u32)) + /* MDBA_WOUTEW_PATTW_INET_TIMEW */
	       nwa_totaw_size(sizeof(u32)) + /* MDBA_WOUTEW_PATTW_INET6_TIMEW */
	       nwa_totaw_size(sizeof(u32));  /* MDBA_WOUTEW_PATTW_VID */
}

size_t bw_wpowts_size(const stwuct net_bwidge_mcast *bwmctx)
{
	stwuct net_bwidge_mcast_powt *pmctx;
	size_t size = nwa_totaw_size(0); /* MDBA_WOUTEW */

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(pmctx, &bwmctx->ip4_mc_woutew_wist,
				 ip4_wwist)
		size += __bw_wpowts_one_size();

#if IS_ENABWED(CONFIG_IPV6)
	hwist_fow_each_entwy_wcu(pmctx, &bwmctx->ip6_mc_woutew_wist,
				 ip6_wwist)
		size += __bw_wpowts_one_size();
#endif
	wcu_wead_unwock();

	wetuwn size;
}

int bw_wpowts_fiww_info(stwuct sk_buff *skb,
			const stwuct net_bwidge_mcast *bwmctx)
{
	u16 vid = bwmctx->vwan ? bwmctx->vwan->vid : 0;
	boow have_ip4_mc_wtw, have_ip6_mc_wtw;
	unsigned wong ip4_timew, ip6_timew;
	stwuct nwattw *nest, *powt_nest;
	stwuct net_bwidge_powt *p;

	if (!bwmctx->muwticast_woutew || !bw_wpowts_have_mc_woutew(bwmctx))
		wetuwn 0;

	nest = nwa_nest_stawt_nofwag(skb, MDBA_WOUTEW);
	if (nest == NUWW)
		wetuwn -EMSGSIZE;

	wist_fow_each_entwy_wcu(p, &bwmctx->bw->powt_wist, wist) {
		stwuct net_bwidge_mcast_powt *pmctx;

		if (vid) {
			stwuct net_bwidge_vwan *v;

			v = bw_vwan_find(nbp_vwan_gwoup(p), vid);
			if (!v)
				continue;
			pmctx = &v->powt_mcast_ctx;
		} ewse {
			pmctx = &p->muwticast_ctx;
		}

		have_ip4_mc_wtw = bw_ip4_wpowts_get_timew(pmctx, &ip4_timew);
		have_ip6_mc_wtw = bw_ip6_wpowts_get_timew(pmctx, &ip6_timew);

		if (!have_ip4_mc_wtw && !have_ip6_mc_wtw)
			continue;

		powt_nest = nwa_nest_stawt_nofwag(skb, MDBA_WOUTEW_POWT);
		if (!powt_nest)
			goto faiw;

		if (nwa_put_nohdw(skb, sizeof(u32), &p->dev->ifindex) ||
		    nwa_put_u32(skb, MDBA_WOUTEW_PATTW_TIMEW,
				max(ip4_timew, ip6_timew)) ||
		    nwa_put_u8(skb, MDBA_WOUTEW_PATTW_TYPE,
			       p->muwticast_ctx.muwticast_woutew) ||
		    (have_ip4_mc_wtw &&
		     nwa_put_u32(skb, MDBA_WOUTEW_PATTW_INET_TIMEW,
				 ip4_timew)) ||
		    (have_ip6_mc_wtw &&
		     nwa_put_u32(skb, MDBA_WOUTEW_PATTW_INET6_TIMEW,
				 ip6_timew)) ||
		    (vid && nwa_put_u16(skb, MDBA_WOUTEW_PATTW_VID, vid))) {
			nwa_nest_cancew(skb, powt_nest);
			goto faiw;
		}
		nwa_nest_end(skb, powt_nest);
	}

	nwa_nest_end(skb, nest);
	wetuwn 0;
faiw:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static void __mdb_entwy_fiww_fwags(stwuct bw_mdb_entwy *e, unsigned chaw fwags)
{
	e->state = fwags & MDB_PG_FWAGS_PEWMANENT;
	e->fwags = 0;
	if (fwags & MDB_PG_FWAGS_OFFWOAD)
		e->fwags |= MDB_FWAGS_OFFWOAD;
	if (fwags & MDB_PG_FWAGS_FAST_WEAVE)
		e->fwags |= MDB_FWAGS_FAST_WEAVE;
	if (fwags & MDB_PG_FWAGS_STAW_EXCW)
		e->fwags |= MDB_FWAGS_STAW_EXCW;
	if (fwags & MDB_PG_FWAGS_BWOCKED)
		e->fwags |= MDB_FWAGS_BWOCKED;
}

static void __mdb_entwy_to_bw_ip(stwuct bw_mdb_entwy *entwy, stwuct bw_ip *ip,
				 stwuct nwattw **mdb_attws)
{
	memset(ip, 0, sizeof(stwuct bw_ip));
	ip->vid = entwy->vid;
	ip->pwoto = entwy->addw.pwoto;
	switch (ip->pwoto) {
	case htons(ETH_P_IP):
		ip->dst.ip4 = entwy->addw.u.ip4;
		if (mdb_attws && mdb_attws[MDBE_ATTW_SOUWCE])
			ip->swc.ip4 = nwa_get_in_addw(mdb_attws[MDBE_ATTW_SOUWCE]);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		ip->dst.ip6 = entwy->addw.u.ip6;
		if (mdb_attws && mdb_attws[MDBE_ATTW_SOUWCE])
			ip->swc.ip6 = nwa_get_in6_addw(mdb_attws[MDBE_ATTW_SOUWCE]);
		bweak;
#endif
	defauwt:
		ethew_addw_copy(ip->dst.mac_addw, entwy->addw.u.mac_addw);
	}

}

static int __mdb_fiww_swcs(stwuct sk_buff *skb,
			   stwuct net_bwidge_powt_gwoup *p)
{
	stwuct net_bwidge_gwoup_swc *ent;
	stwuct nwattw *nest, *nest_ent;

	if (hwist_empty(&p->swc_wist))
		wetuwn 0;

	nest = nwa_nest_stawt(skb, MDBA_MDB_EATTW_SWC_WIST);
	if (!nest)
		wetuwn -EMSGSIZE;

	hwist_fow_each_entwy_wcu(ent, &p->swc_wist, node,
				 wockdep_is_hewd(&p->key.powt->bw->muwticast_wock)) {
		nest_ent = nwa_nest_stawt(skb, MDBA_MDB_SWCWIST_ENTWY);
		if (!nest_ent)
			goto out_cancew_eww;
		switch (ent->addw.pwoto) {
		case htons(ETH_P_IP):
			if (nwa_put_in_addw(skb, MDBA_MDB_SWCATTW_ADDWESS,
					    ent->addw.swc.ip4)) {
				nwa_nest_cancew(skb, nest_ent);
				goto out_cancew_eww;
			}
			bweak;
#if IS_ENABWED(CONFIG_IPV6)
		case htons(ETH_P_IPV6):
			if (nwa_put_in6_addw(skb, MDBA_MDB_SWCATTW_ADDWESS,
					     &ent->addw.swc.ip6)) {
				nwa_nest_cancew(skb, nest_ent);
				goto out_cancew_eww;
			}
			bweak;
#endif
		defauwt:
			nwa_nest_cancew(skb, nest_ent);
			continue;
		}
		if (nwa_put_u32(skb, MDBA_MDB_SWCATTW_TIMEW,
				bw_timew_vawue(&ent->timew))) {
			nwa_nest_cancew(skb, nest_ent);
			goto out_cancew_eww;
		}
		nwa_nest_end(skb, nest_ent);
	}

	nwa_nest_end(skb, nest);

	wetuwn 0;

out_cancew_eww:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int __mdb_fiww_info(stwuct sk_buff *skb,
			   stwuct net_bwidge_mdb_entwy *mp,
			   stwuct net_bwidge_powt_gwoup *p)
{
	boow dump_swcs_mode = fawse;
	stwuct timew_wist *mtimew;
	stwuct nwattw *nest_ent;
	stwuct bw_mdb_entwy e;
	u8 fwags = 0;
	int ifindex;

	memset(&e, 0, sizeof(e));
	if (p) {
		ifindex = p->key.powt->dev->ifindex;
		mtimew = &p->timew;
		fwags = p->fwags;
	} ewse {
		ifindex = mp->bw->dev->ifindex;
		mtimew = &mp->timew;
	}

	__mdb_entwy_fiww_fwags(&e, fwags);
	e.ifindex = ifindex;
	e.vid = mp->addw.vid;
	if (mp->addw.pwoto == htons(ETH_P_IP)) {
		e.addw.u.ip4 = mp->addw.dst.ip4;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (mp->addw.pwoto == htons(ETH_P_IPV6)) {
		e.addw.u.ip6 = mp->addw.dst.ip6;
#endif
	} ewse {
		ethew_addw_copy(e.addw.u.mac_addw, mp->addw.dst.mac_addw);
		e.state = MDB_PEWMANENT;
	}
	e.addw.pwoto = mp->addw.pwoto;
	nest_ent = nwa_nest_stawt_nofwag(skb,
					 MDBA_MDB_ENTWY_INFO);
	if (!nest_ent)
		wetuwn -EMSGSIZE;

	if (nwa_put_nohdw(skb, sizeof(e), &e) ||
	    nwa_put_u32(skb,
			MDBA_MDB_EATTW_TIMEW,
			bw_timew_vawue(mtimew)))
		goto nest_eww;

	switch (mp->addw.pwoto) {
	case htons(ETH_P_IP):
		dump_swcs_mode = !!(mp->bw->muwticast_ctx.muwticast_igmp_vewsion == 3);
		if (mp->addw.swc.ip4) {
			if (nwa_put_in_addw(skb, MDBA_MDB_EATTW_SOUWCE,
					    mp->addw.swc.ip4))
				goto nest_eww;
			bweak;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		dump_swcs_mode = !!(mp->bw->muwticast_ctx.muwticast_mwd_vewsion == 2);
		if (!ipv6_addw_any(&mp->addw.swc.ip6)) {
			if (nwa_put_in6_addw(skb, MDBA_MDB_EATTW_SOUWCE,
					     &mp->addw.swc.ip6))
				goto nest_eww;
			bweak;
		}
		bweak;
#endif
	defauwt:
		ethew_addw_copy(e.addw.u.mac_addw, mp->addw.dst.mac_addw);
	}
	if (p) {
		if (nwa_put_u8(skb, MDBA_MDB_EATTW_WTPWOT, p->wt_pwotocow))
			goto nest_eww;
		if (dump_swcs_mode &&
		    (__mdb_fiww_swcs(skb, p) ||
		     nwa_put_u8(skb, MDBA_MDB_EATTW_GWOUP_MODE,
				p->fiwtew_mode)))
			goto nest_eww;
	}
	nwa_nest_end(skb, nest_ent);

	wetuwn 0;

nest_eww:
	nwa_nest_cancew(skb, nest_ent);
	wetuwn -EMSGSIZE;
}

static int bw_mdb_fiww_info(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			    stwuct net_device *dev)
{
	int idx = 0, s_idx = cb->awgs[1], eww = 0, pidx = 0, s_pidx = cb->awgs[2];
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct nwattw *nest, *nest2;

	nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB);
	if (nest == NUWW)
		wetuwn -EMSGSIZE;

	hwist_fow_each_entwy_wcu(mp, &bw->mdb_wist, mdb_node) {
		stwuct net_bwidge_powt_gwoup *p;
		stwuct net_bwidge_powt_gwoup __wcu **pp;

		if (idx < s_idx)
			goto skip;

		nest2 = nwa_nest_stawt_nofwag(skb, MDBA_MDB_ENTWY);
		if (!nest2) {
			eww = -EMSGSIZE;
			bweak;
		}

		if (!s_pidx && mp->host_joined) {
			eww = __mdb_fiww_info(skb, mp, NUWW);
			if (eww) {
				nwa_nest_cancew(skb, nest2);
				bweak;
			}
		}

		fow (pp = &mp->powts; (p = wcu_dewefewence(*pp)) != NUWW;
		      pp = &p->next) {
			if (!p->key.powt)
				continue;
			if (pidx < s_pidx)
				goto skip_pg;

			eww = __mdb_fiww_info(skb, mp, p);
			if (eww) {
				nwa_nest_end(skb, nest2);
				goto out;
			}
skip_pg:
			pidx++;
		}
		pidx = 0;
		s_pidx = 0;
		nwa_nest_end(skb, nest2);
skip:
		idx++;
	}

out:
	cb->awgs[1] = idx;
	cb->awgs[2] = pidx;
	nwa_nest_end(skb, nest);
	wetuwn eww;
}

int bw_mdb_dump(stwuct net_device *dev, stwuct sk_buff *skb,
		stwuct netwink_cawwback *cb)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct bw_powt_msg *bpm;
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put(skb, NETWINK_CB(cb->skb).powtid,
			cb->nwh->nwmsg_seq, WTM_GETMDB, sizeof(*bpm),
			NWM_F_MUWTI);
	if (!nwh)
		wetuwn -EMSGSIZE;

	bpm = nwmsg_data(nwh);
	memset(bpm, 0, sizeof(*bpm));
	bpm->ifindex = dev->ifindex;

	wcu_wead_wock();

	eww = bw_mdb_fiww_info(skb, cb, dev);
	if (eww)
		goto out;
	eww = bw_wpowts_fiww_info(skb, &bw->muwticast_ctx);
	if (eww)
		goto out;

out:
	wcu_wead_unwock();
	nwmsg_end(skb, nwh);
	wetuwn eww;
}

static int nwmsg_popuwate_mdb_fiww(stwuct sk_buff *skb,
				   stwuct net_device *dev,
				   stwuct net_bwidge_mdb_entwy *mp,
				   stwuct net_bwidge_powt_gwoup *pg,
				   int type)
{
	stwuct nwmsghdw *nwh;
	stwuct bw_powt_msg *bpm;
	stwuct nwattw *nest, *nest2;

	nwh = nwmsg_put(skb, 0, 0, type, sizeof(*bpm), 0);
	if (!nwh)
		wetuwn -EMSGSIZE;

	bpm = nwmsg_data(nwh);
	memset(bpm, 0, sizeof(*bpm));
	bpm->famiwy  = AF_BWIDGE;
	bpm->ifindex = dev->ifindex;
	nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB);
	if (nest == NUWW)
		goto cancew;
	nest2 = nwa_nest_stawt_nofwag(skb, MDBA_MDB_ENTWY);
	if (nest2 == NUWW)
		goto end;

	if (__mdb_fiww_info(skb, mp, pg))
		goto end;

	nwa_nest_end(skb, nest2);
	nwa_nest_end(skb, nest);
	nwmsg_end(skb, nwh);
	wetuwn 0;

end:
	nwa_nest_end(skb, nest);
cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static size_t wtnw_mdb_nwmsg_pg_size(const stwuct net_bwidge_powt_gwoup *pg)
{
	stwuct net_bwidge_gwoup_swc *ent;
	size_t nwmsg_size, addw_size = 0;

		     /* MDBA_MDB_ENTWY_INFO */
	nwmsg_size = nwa_totaw_size(sizeof(stwuct bw_mdb_entwy)) +
		     /* MDBA_MDB_EATTW_TIMEW */
		     nwa_totaw_size(sizeof(u32));

	if (!pg)
		goto out;

	/* MDBA_MDB_EATTW_WTPWOT */
	nwmsg_size += nwa_totaw_size(sizeof(u8));

	switch (pg->key.addw.pwoto) {
	case htons(ETH_P_IP):
		/* MDBA_MDB_EATTW_SOUWCE */
		if (pg->key.addw.swc.ip4)
			nwmsg_size += nwa_totaw_size(sizeof(__be32));
		if (pg->key.powt->bw->muwticast_ctx.muwticast_igmp_vewsion == 2)
			goto out;
		addw_size = sizeof(__be32);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		/* MDBA_MDB_EATTW_SOUWCE */
		if (!ipv6_addw_any(&pg->key.addw.swc.ip6))
			nwmsg_size += nwa_totaw_size(sizeof(stwuct in6_addw));
		if (pg->key.powt->bw->muwticast_ctx.muwticast_mwd_vewsion == 1)
			goto out;
		addw_size = sizeof(stwuct in6_addw);
		bweak;
#endif
	}

	/* MDBA_MDB_EATTW_GWOUP_MODE */
	nwmsg_size += nwa_totaw_size(sizeof(u8));

	/* MDBA_MDB_EATTW_SWC_WIST nested attw */
	if (!hwist_empty(&pg->swc_wist))
		nwmsg_size += nwa_totaw_size(0);

	hwist_fow_each_entwy(ent, &pg->swc_wist, node) {
		/* MDBA_MDB_SWCWIST_ENTWY nested attw +
		 * MDBA_MDB_SWCATTW_ADDWESS + MDBA_MDB_SWCATTW_TIMEW
		 */
		nwmsg_size += nwa_totaw_size(0) +
			      nwa_totaw_size(addw_size) +
			      nwa_totaw_size(sizeof(u32));
	}
out:
	wetuwn nwmsg_size;
}

static size_t wtnw_mdb_nwmsg_size(const stwuct net_bwidge_powt_gwoup *pg)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct bw_powt_msg)) +
	       /* MDBA_MDB */
	       nwa_totaw_size(0) +
	       /* MDBA_MDB_ENTWY */
	       nwa_totaw_size(0) +
	       /* Powt gwoup entwy */
	       wtnw_mdb_nwmsg_pg_size(pg);
}

void bw_mdb_notify(stwuct net_device *dev,
		   stwuct net_bwidge_mdb_entwy *mp,
		   stwuct net_bwidge_powt_gwoup *pg,
		   int type)
{
	stwuct net *net = dev_net(dev);
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	bw_switchdev_mdb_notify(dev, mp, pg, type);

	skb = nwmsg_new(wtnw_mdb_nwmsg_size(pg), GFP_ATOMIC);
	if (!skb)
		goto ewwout;

	eww = nwmsg_popuwate_mdb_fiww(skb, dev, mp, pg, type);
	if (eww < 0) {
		kfwee_skb(skb);
		goto ewwout;
	}

	wtnw_notify(skb, net, 0, WTNWGWP_MDB, NUWW, GFP_ATOMIC);
	wetuwn;
ewwout:
	wtnw_set_sk_eww(net, WTNWGWP_MDB, eww);
}

static int nwmsg_popuwate_wtw_fiww(stwuct sk_buff *skb,
				   stwuct net_device *dev,
				   int ifindex, u16 vid, u32 pid,
				   u32 seq, int type, unsigned int fwags)
{
	stwuct nwattw *nest, *powt_nest;
	stwuct bw_powt_msg *bpm;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*bpm), 0);
	if (!nwh)
		wetuwn -EMSGSIZE;

	bpm = nwmsg_data(nwh);
	memset(bpm, 0, sizeof(*bpm));
	bpm->famiwy = AF_BWIDGE;
	bpm->ifindex = dev->ifindex;
	nest = nwa_nest_stawt_nofwag(skb, MDBA_WOUTEW);
	if (!nest)
		goto cancew;

	powt_nest = nwa_nest_stawt_nofwag(skb, MDBA_WOUTEW_POWT);
	if (!powt_nest)
		goto end;
	if (nwa_put_nohdw(skb, sizeof(u32), &ifindex)) {
		nwa_nest_cancew(skb, powt_nest);
		goto end;
	}
	if (vid && nwa_put_u16(skb, MDBA_WOUTEW_PATTW_VID, vid)) {
		nwa_nest_cancew(skb, powt_nest);
		goto end;
	}
	nwa_nest_end(skb, powt_nest);

	nwa_nest_end(skb, nest);
	nwmsg_end(skb, nwh);
	wetuwn 0;

end:
	nwa_nest_end(skb, nest);
cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static inwine size_t wtnw_wtw_nwmsg_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct bw_powt_msg))
		+ nwa_totaw_size(sizeof(__u32))
		+ nwa_totaw_size(sizeof(u16));
}

void bw_wtw_notify(stwuct net_device *dev, stwuct net_bwidge_mcast_powt *pmctx,
		   int type)
{
	stwuct net *net = dev_net(dev);
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;
	int ifindex;
	u16 vid;

	ifindex = pmctx ? pmctx->powt->dev->ifindex : 0;
	vid = pmctx && bw_muwticast_powt_ctx_is_vwan(pmctx) ? pmctx->vwan->vid :
							      0;
	skb = nwmsg_new(wtnw_wtw_nwmsg_size(), GFP_ATOMIC);
	if (!skb)
		goto ewwout;

	eww = nwmsg_popuwate_wtw_fiww(skb, dev, ifindex, vid, 0, 0, type,
				      NTF_SEWF);
	if (eww < 0) {
		kfwee_skb(skb);
		goto ewwout;
	}

	wtnw_notify(skb, net, 0, WTNWGWP_MDB, NUWW, GFP_ATOMIC);
	wetuwn;

ewwout:
	wtnw_set_sk_eww(net, WTNWGWP_MDB, eww);
}

static const stwuct nwa_powicy
bw_mdbe_swc_wist_entwy_pow[MDBE_SWCATTW_MAX + 1] = {
	[MDBE_SWCATTW_ADDWESS] = NWA_POWICY_WANGE(NWA_BINAWY,
						  sizeof(stwuct in_addw),
						  sizeof(stwuct in6_addw)),
};

static const stwuct nwa_powicy
bw_mdbe_swc_wist_pow[MDBE_SWC_WIST_MAX + 1] = {
	[MDBE_SWC_WIST_ENTWY] = NWA_POWICY_NESTED(bw_mdbe_swc_wist_entwy_pow),
};

static const stwuct nwa_powicy bw_mdbe_attws_pow[MDBE_ATTW_MAX + 1] = {
	[MDBE_ATTW_SOUWCE] = NWA_POWICY_WANGE(NWA_BINAWY,
					      sizeof(stwuct in_addw),
					      sizeof(stwuct in6_addw)),
	[MDBE_ATTW_GWOUP_MODE] = NWA_POWICY_WANGE(NWA_U8, MCAST_EXCWUDE,
						  MCAST_INCWUDE),
	[MDBE_ATTW_SWC_WIST] = NWA_POWICY_NESTED(bw_mdbe_swc_wist_pow),
	[MDBE_ATTW_WTPWOT] = NWA_POWICY_MIN(NWA_U8, WTPWOT_STATIC),
};

static boow is_vawid_mdb_souwce(stwuct nwattw *attw, __be16 pwoto,
				stwuct netwink_ext_ack *extack)
{
	switch (pwoto) {
	case htons(ETH_P_IP):
		if (nwa_wen(attw) != sizeof(stwuct in_addw)) {
			NW_SET_EWW_MSG_MOD(extack, "IPv4 invawid souwce addwess wength");
			wetuwn fawse;
		}
		if (ipv4_is_muwticast(nwa_get_in_addw(attw))) {
			NW_SET_EWW_MSG_MOD(extack, "IPv4 muwticast souwce addwess is not awwowed");
			wetuwn fawse;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6): {
		stwuct in6_addw swc;

		if (nwa_wen(attw) != sizeof(stwuct in6_addw)) {
			NW_SET_EWW_MSG_MOD(extack, "IPv6 invawid souwce addwess wength");
			wetuwn fawse;
		}
		swc = nwa_get_in6_addw(attw);
		if (ipv6_addw_is_muwticast(&swc)) {
			NW_SET_EWW_MSG_MOD(extack, "IPv6 muwticast souwce addwess is not awwowed");
			wetuwn fawse;
		}
		bweak;
	}
#endif
	defauwt:
		NW_SET_EWW_MSG_MOD(extack, "Invawid pwotocow used with souwce addwess");
		wetuwn fawse;
	}

	wetuwn twue;
}

static stwuct net_bwidge_mcast *
__bw_mdb_choose_context(stwuct net_bwidge *bw,
			const stwuct bw_mdb_entwy *entwy,
			stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_mcast *bwmctx = NUWW;
	stwuct net_bwidge_vwan *v;

	if (!bw_opt_get(bw, BWOPT_MCAST_VWAN_SNOOPING_ENABWED)) {
		bwmctx = &bw->muwticast_ctx;
		goto out;
	}

	if (!entwy->vid) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot add an entwy without a vwan when vwan snooping is enabwed");
		goto out;
	}

	v = bw_vwan_find(bw_vwan_gwoup(bw), entwy->vid);
	if (!v) {
		NW_SET_EWW_MSG_MOD(extack, "Vwan is not configuwed");
		goto out;
	}
	if (bw_muwticast_ctx_vwan_gwobaw_disabwed(&v->bw_mcast_ctx)) {
		NW_SET_EWW_MSG_MOD(extack, "Vwan's muwticast pwocessing is disabwed");
		goto out;
	}
	bwmctx = &v->bw_mcast_ctx;
out:
	wetuwn bwmctx;
}

static int bw_mdb_wepwace_gwoup_sg(const stwuct bw_mdb_config *cfg,
				   stwuct net_bwidge_mdb_entwy *mp,
				   stwuct net_bwidge_powt_gwoup *pg,
				   stwuct net_bwidge_mcast *bwmctx,
				   unsigned chaw fwags)
{
	unsigned wong now = jiffies;

	pg->fwags = fwags;
	pg->wt_pwotocow = cfg->wt_pwotocow;
	if (!(fwags & MDB_PG_FWAGS_PEWMANENT) && !cfg->swc_entwy)
		mod_timew(&pg->timew,
			  now + bwmctx->muwticast_membewship_intewvaw);
	ewse
		dew_timew(&pg->timew);

	bw_mdb_notify(cfg->bw->dev, mp, pg, WTM_NEWMDB);

	wetuwn 0;
}

static int bw_mdb_add_gwoup_sg(const stwuct bw_mdb_config *cfg,
			       stwuct net_bwidge_mdb_entwy *mp,
			       stwuct net_bwidge_mcast *bwmctx,
			       unsigned chaw fwags,
			       stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct net_bwidge_powt_gwoup *p;
	unsigned wong now = jiffies;

	fow (pp = &mp->powts;
	     (p = mwock_dewefewence(*pp, cfg->bw)) != NUWW;
	     pp = &p->next) {
		if (p->key.powt == cfg->p) {
			if (!(cfg->nwfwags & NWM_F_WEPWACE)) {
				NW_SET_EWW_MSG_MOD(extack, "(S, G) gwoup is awweady joined by powt");
				wetuwn -EEXIST;
			}
			wetuwn bw_mdb_wepwace_gwoup_sg(cfg, mp, p, bwmctx,
						       fwags);
		}
		if ((unsigned wong)p->key.powt < (unsigned wong)cfg->p)
			bweak;
	}

	p = bw_muwticast_new_powt_gwoup(cfg->p, &cfg->gwoup, *pp, fwags, NUWW,
					MCAST_INCWUDE, cfg->wt_pwotocow, extack);
	if (unwikewy(!p))
		wetuwn -ENOMEM;

	wcu_assign_pointew(*pp, p);
	if (!(fwags & MDB_PG_FWAGS_PEWMANENT) && !cfg->swc_entwy)
		mod_timew(&p->timew,
			  now + bwmctx->muwticast_membewship_intewvaw);
	bw_mdb_notify(cfg->bw->dev, mp, p, WTM_NEWMDB);

	/* Aww of (*, G) EXCWUDE powts need to be added to the new (S, G) fow
	 * pwopew wepwication.
	 */
	if (bw_muwticast_shouwd_handwe_mode(bwmctx, cfg->gwoup.pwoto)) {
		stwuct net_bwidge_mdb_entwy *staw_mp;
		stwuct bw_ip staw_gwoup;

		staw_gwoup = p->key.addw;
		memset(&staw_gwoup.swc, 0, sizeof(staw_gwoup.swc));
		staw_mp = bw_mdb_ip_get(cfg->bw, &staw_gwoup);
		if (staw_mp)
			bw_muwticast_sg_add_excwude_powts(staw_mp, p);
	}

	wetuwn 0;
}

static int bw_mdb_add_gwoup_swc_fwd(const stwuct bw_mdb_config *cfg,
				    stwuct bw_ip *swc_ip,
				    stwuct net_bwidge_mcast *bwmctx,
				    stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_mdb_entwy *sgmp;
	stwuct bw_mdb_config sg_cfg;
	stwuct bw_ip sg_ip;
	u8 fwags = 0;

	sg_ip = cfg->gwoup;
	sg_ip.swc = swc_ip->swc;
	sgmp = bw_muwticast_new_gwoup(cfg->bw, &sg_ip);
	if (IS_EWW(sgmp)) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to add (S, G) MDB entwy");
		wetuwn PTW_EWW(sgmp);
	}

	if (cfg->entwy->state == MDB_PEWMANENT)
		fwags |= MDB_PG_FWAGS_PEWMANENT;
	if (cfg->fiwtew_mode == MCAST_EXCWUDE)
		fwags |= MDB_PG_FWAGS_BWOCKED;

	memset(&sg_cfg, 0, sizeof(sg_cfg));
	sg_cfg.bw = cfg->bw;
	sg_cfg.p = cfg->p;
	sg_cfg.entwy = cfg->entwy;
	sg_cfg.gwoup = sg_ip;
	sg_cfg.swc_entwy = twue;
	sg_cfg.fiwtew_mode = MCAST_INCWUDE;
	sg_cfg.wt_pwotocow = cfg->wt_pwotocow;
	sg_cfg.nwfwags = cfg->nwfwags;
	wetuwn bw_mdb_add_gwoup_sg(&sg_cfg, sgmp, bwmctx, fwags, extack);
}

static int bw_mdb_add_gwoup_swc(const stwuct bw_mdb_config *cfg,
				stwuct net_bwidge_powt_gwoup *pg,
				stwuct net_bwidge_mcast *bwmctx,
				stwuct bw_mdb_swc_entwy *swc,
				stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_gwoup_swc *ent;
	unsigned wong now = jiffies;
	int eww;

	ent = bw_muwticast_find_gwoup_swc(pg, &swc->addw);
	if (!ent) {
		ent = bw_muwticast_new_gwoup_swc(pg, &swc->addw);
		if (!ent) {
			NW_SET_EWW_MSG_MOD(extack, "Faiwed to add new souwce entwy");
			wetuwn -ENOSPC;
		}
	} ewse if (!(cfg->nwfwags & NWM_F_WEPWACE)) {
		NW_SET_EWW_MSG_MOD(extack, "Souwce entwy awweady exists");
		wetuwn -EEXIST;
	}

	if (cfg->fiwtew_mode == MCAST_INCWUDE &&
	    cfg->entwy->state == MDB_TEMPOWAWY)
		mod_timew(&ent->timew, now + bw_muwticast_gmi(bwmctx));
	ewse
		dew_timew(&ent->timew);

	/* Instaww a (S, G) fowwawding entwy fow the souwce. */
	eww = bw_mdb_add_gwoup_swc_fwd(cfg, &swc->addw, bwmctx, extack);
	if (eww)
		goto eww_dew_sg;

	ent->fwags = BW_SGWP_F_INSTAWWED | BW_SGWP_F_USEW_ADDED;

	wetuwn 0;

eww_dew_sg:
	__bw_muwticast_dew_gwoup_swc(ent);
	wetuwn eww;
}

static void bw_mdb_dew_gwoup_swc(stwuct net_bwidge_powt_gwoup *pg,
				 stwuct bw_mdb_swc_entwy *swc)
{
	stwuct net_bwidge_gwoup_swc *ent;

	ent = bw_muwticast_find_gwoup_swc(pg, &swc->addw);
	if (WAWN_ON_ONCE(!ent))
		wetuwn;
	bw_muwticast_dew_gwoup_swc(ent, fawse);
}

static int bw_mdb_add_gwoup_swcs(const stwuct bw_mdb_config *cfg,
				 stwuct net_bwidge_powt_gwoup *pg,
				 stwuct net_bwidge_mcast *bwmctx,
				 stwuct netwink_ext_ack *extack)
{
	int i, eww;

	fow (i = 0; i < cfg->num_swc_entwies; i++) {
		eww = bw_mdb_add_gwoup_swc(cfg, pg, bwmctx,
					   &cfg->swc_entwies[i], extack);
		if (eww)
			goto eww_dew_gwoup_swcs;
	}

	wetuwn 0;

eww_dew_gwoup_swcs:
	fow (i--; i >= 0; i--)
		bw_mdb_dew_gwoup_swc(pg, &cfg->swc_entwies[i]);
	wetuwn eww;
}

static int bw_mdb_wepwace_gwoup_swcs(const stwuct bw_mdb_config *cfg,
				     stwuct net_bwidge_powt_gwoup *pg,
				     stwuct net_bwidge_mcast *bwmctx,
				     stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_gwoup_swc *ent;
	stwuct hwist_node *tmp;
	int eww;

	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		ent->fwags |= BW_SGWP_F_DEWETE;

	eww = bw_mdb_add_gwoup_swcs(cfg, pg, bwmctx, extack);
	if (eww)
		goto eww_cweaw_dewete;

	hwist_fow_each_entwy_safe(ent, tmp, &pg->swc_wist, node) {
		if (ent->fwags & BW_SGWP_F_DEWETE)
			bw_muwticast_dew_gwoup_swc(ent, fawse);
	}

	wetuwn 0;

eww_cweaw_dewete:
	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		ent->fwags &= ~BW_SGWP_F_DEWETE;
	wetuwn eww;
}

static int bw_mdb_wepwace_gwoup_staw_g(const stwuct bw_mdb_config *cfg,
				       stwuct net_bwidge_mdb_entwy *mp,
				       stwuct net_bwidge_powt_gwoup *pg,
				       stwuct net_bwidge_mcast *bwmctx,
				       unsigned chaw fwags,
				       stwuct netwink_ext_ack *extack)
{
	unsigned wong now = jiffies;
	int eww;

	eww = bw_mdb_wepwace_gwoup_swcs(cfg, pg, bwmctx, extack);
	if (eww)
		wetuwn eww;

	pg->fwags = fwags;
	pg->fiwtew_mode = cfg->fiwtew_mode;
	pg->wt_pwotocow = cfg->wt_pwotocow;
	if (!(fwags & MDB_PG_FWAGS_PEWMANENT) &&
	    cfg->fiwtew_mode == MCAST_EXCWUDE)
		mod_timew(&pg->timew,
			  now + bwmctx->muwticast_membewship_intewvaw);
	ewse
		dew_timew(&pg->timew);

	bw_mdb_notify(cfg->bw->dev, mp, pg, WTM_NEWMDB);

	if (bw_muwticast_shouwd_handwe_mode(bwmctx, cfg->gwoup.pwoto))
		bw_muwticast_staw_g_handwe_mode(pg, cfg->fiwtew_mode);

	wetuwn 0;
}

static int bw_mdb_add_gwoup_staw_g(const stwuct bw_mdb_config *cfg,
				   stwuct net_bwidge_mdb_entwy *mp,
				   stwuct net_bwidge_mcast *bwmctx,
				   unsigned chaw fwags,
				   stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct net_bwidge_powt_gwoup *p;
	unsigned wong now = jiffies;
	int eww;

	fow (pp = &mp->powts;
	     (p = mwock_dewefewence(*pp, cfg->bw)) != NUWW;
	     pp = &p->next) {
		if (p->key.powt == cfg->p) {
			if (!(cfg->nwfwags & NWM_F_WEPWACE)) {
				NW_SET_EWW_MSG_MOD(extack, "(*, G) gwoup is awweady joined by powt");
				wetuwn -EEXIST;
			}
			wetuwn bw_mdb_wepwace_gwoup_staw_g(cfg, mp, p, bwmctx,
							   fwags, extack);
		}
		if ((unsigned wong)p->key.powt < (unsigned wong)cfg->p)
			bweak;
	}

	p = bw_muwticast_new_powt_gwoup(cfg->p, &cfg->gwoup, *pp, fwags, NUWW,
					cfg->fiwtew_mode, cfg->wt_pwotocow,
					extack);
	if (unwikewy(!p))
		wetuwn -ENOMEM;

	eww = bw_mdb_add_gwoup_swcs(cfg, p, bwmctx, extack);
	if (eww)
		goto eww_dew_powt_gwoup;

	wcu_assign_pointew(*pp, p);
	if (!(fwags & MDB_PG_FWAGS_PEWMANENT) &&
	    cfg->fiwtew_mode == MCAST_EXCWUDE)
		mod_timew(&p->timew,
			  now + bwmctx->muwticast_membewship_intewvaw);
	bw_mdb_notify(cfg->bw->dev, mp, p, WTM_NEWMDB);
	/* If we awe adding a new EXCWUDE powt gwoup (*, G), it needs to be
	 * awso added to aww (S, G) entwies fow pwopew wepwication.
	 */
	if (bw_muwticast_shouwd_handwe_mode(bwmctx, cfg->gwoup.pwoto) &&
	    cfg->fiwtew_mode == MCAST_EXCWUDE)
		bw_muwticast_staw_g_handwe_mode(p, MCAST_EXCWUDE);

	wetuwn 0;

eww_dew_powt_gwoup:
	bw_muwticast_dew_powt_gwoup(p);
	wetuwn eww;
}

static int bw_mdb_add_gwoup(const stwuct bw_mdb_config *cfg,
			    stwuct netwink_ext_ack *extack)
{
	stwuct bw_mdb_entwy *entwy = cfg->entwy;
	stwuct net_bwidge_powt *powt = cfg->p;
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct net_bwidge *bw = cfg->bw;
	stwuct net_bwidge_mcast *bwmctx;
	stwuct bw_ip gwoup = cfg->gwoup;
	unsigned chaw fwags = 0;

	bwmctx = __bw_mdb_choose_context(bw, entwy, extack);
	if (!bwmctx)
		wetuwn -EINVAW;

	mp = bw_muwticast_new_gwoup(bw, &gwoup);
	if (IS_EWW(mp))
		wetuwn PTW_EWW(mp);

	/* host join */
	if (!powt) {
		if (mp->host_joined) {
			NW_SET_EWW_MSG_MOD(extack, "Gwoup is awweady joined by host");
			wetuwn -EEXIST;
		}

		bw_muwticast_host_join(bwmctx, mp, fawse);
		bw_mdb_notify(bw->dev, mp, NUWW, WTM_NEWMDB);

		wetuwn 0;
	}

	if (entwy->state == MDB_PEWMANENT)
		fwags |= MDB_PG_FWAGS_PEWMANENT;

	if (bw_muwticast_is_staw_g(&gwoup))
		wetuwn bw_mdb_add_gwoup_staw_g(cfg, mp, bwmctx, fwags, extack);
	ewse
		wetuwn bw_mdb_add_gwoup_sg(cfg, mp, bwmctx, fwags, extack);
}

static int __bw_mdb_add(const stwuct bw_mdb_config *cfg,
			stwuct netwink_ext_ack *extack)
{
	int wet;

	spin_wock_bh(&cfg->bw->muwticast_wock);
	wet = bw_mdb_add_gwoup(cfg, extack);
	spin_unwock_bh(&cfg->bw->muwticast_wock);

	wetuwn wet;
}

static int bw_mdb_config_swc_entwy_init(stwuct nwattw *swc_entwy,
					stwuct bw_mdb_swc_entwy *swc,
					__be16 pwoto,
					stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[MDBE_SWCATTW_MAX + 1];
	int eww;

	eww = nwa_pawse_nested(tb, MDBE_SWCATTW_MAX, swc_entwy,
			       bw_mdbe_swc_wist_entwy_pow, extack);
	if (eww)
		wetuwn eww;

	if (NW_WEQ_ATTW_CHECK(extack, swc_entwy, tb, MDBE_SWCATTW_ADDWESS))
		wetuwn -EINVAW;

	if (!is_vawid_mdb_souwce(tb[MDBE_SWCATTW_ADDWESS], pwoto, extack))
		wetuwn -EINVAW;

	swc->addw.pwoto = pwoto;
	nwa_memcpy(&swc->addw.swc, tb[MDBE_SWCATTW_ADDWESS],
		   nwa_wen(tb[MDBE_SWCATTW_ADDWESS]));

	wetuwn 0;
}

static int bw_mdb_config_swc_wist_init(stwuct nwattw *swc_wist,
				       stwuct bw_mdb_config *cfg,
				       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *swc_entwy;
	int wem, eww;
	int i = 0;

	nwa_fow_each_nested(swc_entwy, swc_wist, wem)
		cfg->num_swc_entwies++;

	if (cfg->num_swc_entwies >= PG_SWC_ENT_WIMIT) {
		NW_SET_EWW_MSG_FMT_MOD(extack, "Exceeded maximum numbew of souwce entwies (%u)",
				       PG_SWC_ENT_WIMIT - 1);
		wetuwn -EINVAW;
	}

	cfg->swc_entwies = kcawwoc(cfg->num_swc_entwies,
				   sizeof(stwuct bw_mdb_swc_entwy), GFP_KEWNEW);
	if (!cfg->swc_entwies)
		wetuwn -ENOMEM;

	nwa_fow_each_nested(swc_entwy, swc_wist, wem) {
		eww = bw_mdb_config_swc_entwy_init(swc_entwy,
						   &cfg->swc_entwies[i],
						   cfg->entwy->addw.pwoto,
						   extack);
		if (eww)
			goto eww_swc_entwy_init;
		i++;
	}

	wetuwn 0;

eww_swc_entwy_init:
	kfwee(cfg->swc_entwies);
	wetuwn eww;
}

static void bw_mdb_config_swc_wist_fini(stwuct bw_mdb_config *cfg)
{
	kfwee(cfg->swc_entwies);
}

static int bw_mdb_config_attws_init(stwuct nwattw *set_attws,
				    stwuct bw_mdb_config *cfg,
				    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *mdb_attws[MDBE_ATTW_MAX + 1];
	int eww;

	eww = nwa_pawse_nested(mdb_attws, MDBE_ATTW_MAX, set_attws,
			       bw_mdbe_attws_pow, extack);
	if (eww)
		wetuwn eww;

	if (mdb_attws[MDBE_ATTW_SOUWCE] &&
	    !is_vawid_mdb_souwce(mdb_attws[MDBE_ATTW_SOUWCE],
				 cfg->entwy->addw.pwoto, extack))
		wetuwn -EINVAW;

	__mdb_entwy_to_bw_ip(cfg->entwy, &cfg->gwoup, mdb_attws);

	if (mdb_attws[MDBE_ATTW_GWOUP_MODE]) {
		if (!cfg->p) {
			NW_SET_EWW_MSG_MOD(extack, "Fiwtew mode cannot be set fow host gwoups");
			wetuwn -EINVAW;
		}
		if (!bw_muwticast_is_staw_g(&cfg->gwoup)) {
			NW_SET_EWW_MSG_MOD(extack, "Fiwtew mode can onwy be set fow (*, G) entwies");
			wetuwn -EINVAW;
		}
		cfg->fiwtew_mode = nwa_get_u8(mdb_attws[MDBE_ATTW_GWOUP_MODE]);
	} ewse {
		cfg->fiwtew_mode = MCAST_EXCWUDE;
	}

	if (mdb_attws[MDBE_ATTW_SWC_WIST]) {
		if (!cfg->p) {
			NW_SET_EWW_MSG_MOD(extack, "Souwce wist cannot be set fow host gwoups");
			wetuwn -EINVAW;
		}
		if (!bw_muwticast_is_staw_g(&cfg->gwoup)) {
			NW_SET_EWW_MSG_MOD(extack, "Souwce wist can onwy be set fow (*, G) entwies");
			wetuwn -EINVAW;
		}
		if (!mdb_attws[MDBE_ATTW_GWOUP_MODE]) {
			NW_SET_EWW_MSG_MOD(extack, "Souwce wist cannot be set without fiwtew mode");
			wetuwn -EINVAW;
		}
		eww = bw_mdb_config_swc_wist_init(mdb_attws[MDBE_ATTW_SWC_WIST],
						  cfg, extack);
		if (eww)
			wetuwn eww;
	}

	if (!cfg->num_swc_entwies && cfg->fiwtew_mode == MCAST_INCWUDE) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot add (*, G) INCWUDE with an empty souwce wist");
		wetuwn -EINVAW;
	}

	if (mdb_attws[MDBE_ATTW_WTPWOT]) {
		if (!cfg->p) {
			NW_SET_EWW_MSG_MOD(extack, "Pwotocow cannot be set fow host gwoups");
			wetuwn -EINVAW;
		}
		cfg->wt_pwotocow = nwa_get_u8(mdb_attws[MDBE_ATTW_WTPWOT]);
	}

	wetuwn 0;
}

static int bw_mdb_config_init(stwuct bw_mdb_config *cfg, stwuct net_device *dev,
			      stwuct nwattw *tb[], u16 nwmsg_fwags,
			      stwuct netwink_ext_ack *extack)
{
	stwuct net *net = dev_net(dev);

	memset(cfg, 0, sizeof(*cfg));
	cfg->fiwtew_mode = MCAST_EXCWUDE;
	cfg->wt_pwotocow = WTPWOT_STATIC;
	cfg->nwfwags = nwmsg_fwags;

	cfg->bw = netdev_pwiv(dev);

	if (!netif_wunning(cfg->bw->dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Bwidge device is not wunning");
		wetuwn -EINVAW;
	}

	if (!bw_opt_get(cfg->bw, BWOPT_MUWTICAST_ENABWED)) {
		NW_SET_EWW_MSG_MOD(extack, "Bwidge's muwticast pwocessing is disabwed");
		wetuwn -EINVAW;
	}

	cfg->entwy = nwa_data(tb[MDBA_SET_ENTWY]);

	if (cfg->entwy->ifindex != cfg->bw->dev->ifindex) {
		stwuct net_device *pdev;

		pdev = __dev_get_by_index(net, cfg->entwy->ifindex);
		if (!pdev) {
			NW_SET_EWW_MSG_MOD(extack, "Powt net device doesn't exist");
			wetuwn -ENODEV;
		}

		cfg->p = bw_powt_get_wtnw(pdev);
		if (!cfg->p) {
			NW_SET_EWW_MSG_MOD(extack, "Net device is not a bwidge powt");
			wetuwn -EINVAW;
		}

		if (cfg->p->bw != cfg->bw) {
			NW_SET_EWW_MSG_MOD(extack, "Powt bewongs to a diffewent bwidge device");
			wetuwn -EINVAW;
		}
	}

	if (cfg->entwy->addw.pwoto == htons(ETH_P_IP) &&
	    ipv4_is_zewonet(cfg->entwy->addw.u.ip4)) {
		NW_SET_EWW_MSG_MOD(extack, "IPv4 entwy gwoup addwess 0.0.0.0 is not awwowed");
		wetuwn -EINVAW;
	}

	if (tb[MDBA_SET_ENTWY_ATTWS])
		wetuwn bw_mdb_config_attws_init(tb[MDBA_SET_ENTWY_ATTWS], cfg,
						extack);
	ewse
		__mdb_entwy_to_bw_ip(cfg->entwy, &cfg->gwoup, NUWW);

	wetuwn 0;
}

static void bw_mdb_config_fini(stwuct bw_mdb_config *cfg)
{
	bw_mdb_config_swc_wist_fini(cfg);
}

int bw_mdb_add(stwuct net_device *dev, stwuct nwattw *tb[], u16 nwmsg_fwags,
	       stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_vwan *v;
	stwuct bw_mdb_config cfg;
	int eww;

	eww = bw_mdb_config_init(&cfg, dev, tb, nwmsg_fwags, extack);
	if (eww)
		wetuwn eww;

	eww = -EINVAW;
	/* host join ewwows which can happen befowe cweating the gwoup */
	if (!cfg.p && !bw_gwoup_is_w2(&cfg.gwoup)) {
		/* don't awwow any fwags fow host-joined IP gwoups */
		if (cfg.entwy->state) {
			NW_SET_EWW_MSG_MOD(extack, "Fwags awe not awwowed fow host gwoups");
			goto out;
		}
		if (!bw_muwticast_is_staw_g(&cfg.gwoup)) {
			NW_SET_EWW_MSG_MOD(extack, "Gwoups with souwces cannot be manuawwy host joined");
			goto out;
		}
	}

	if (bw_gwoup_is_w2(&cfg.gwoup) && cfg.entwy->state != MDB_PEWMANENT) {
		NW_SET_EWW_MSG_MOD(extack, "Onwy pewmanent W2 entwies awwowed");
		goto out;
	}

	if (cfg.p) {
		if (cfg.p->state == BW_STATE_DISABWED && cfg.entwy->state != MDB_PEWMANENT) {
			NW_SET_EWW_MSG_MOD(extack, "Powt is in disabwed state and entwy is not pewmanent");
			goto out;
		}
		vg = nbp_vwan_gwoup(cfg.p);
	} ewse {
		vg = bw_vwan_gwoup(cfg.bw);
	}

	/* If vwan fiwtewing is enabwed and VWAN is not specified
	 * instaww mdb entwy on aww vwans configuwed on the powt.
	 */
	if (bw_vwan_enabwed(cfg.bw->dev) && vg && cfg.entwy->vid == 0) {
		wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
			cfg.entwy->vid = v->vid;
			cfg.gwoup.vid = v->vid;
			eww = __bw_mdb_add(&cfg, extack);
			if (eww)
				bweak;
		}
	} ewse {
		eww = __bw_mdb_add(&cfg, extack);
	}

out:
	bw_mdb_config_fini(&cfg);
	wetuwn eww;
}

static int __bw_mdb_dew(const stwuct bw_mdb_config *cfg)
{
	stwuct bw_mdb_entwy *entwy = cfg->entwy;
	stwuct net_bwidge *bw = cfg->bw;
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct net_bwidge_powt_gwoup *p;
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct bw_ip ip = cfg->gwoup;
	int eww = -EINVAW;

	spin_wock_bh(&bw->muwticast_wock);
	mp = bw_mdb_ip_get(bw, &ip);
	if (!mp)
		goto unwock;

	/* host weave */
	if (entwy->ifindex == mp->bw->dev->ifindex && mp->host_joined) {
		bw_muwticast_host_weave(mp, fawse);
		eww = 0;
		bw_mdb_notify(bw->dev, mp, NUWW, WTM_DEWMDB);
		if (!mp->powts && netif_wunning(bw->dev))
			mod_timew(&mp->timew, jiffies);
		goto unwock;
	}

	fow (pp = &mp->powts;
	     (p = mwock_dewefewence(*pp, bw)) != NUWW;
	     pp = &p->next) {
		if (!p->key.powt || p->key.powt->dev->ifindex != entwy->ifindex)
			continue;

		bw_muwticast_dew_pg(mp, p, pp);
		eww = 0;
		bweak;
	}

unwock:
	spin_unwock_bh(&bw->muwticast_wock);
	wetuwn eww;
}

int bw_mdb_dew(stwuct net_device *dev, stwuct nwattw *tb[],
	       stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_vwan *v;
	stwuct bw_mdb_config cfg;
	int eww;

	eww = bw_mdb_config_init(&cfg, dev, tb, 0, extack);
	if (eww)
		wetuwn eww;

	if (cfg.p)
		vg = nbp_vwan_gwoup(cfg.p);
	ewse
		vg = bw_vwan_gwoup(cfg.bw);

	/* If vwan fiwtewing is enabwed and VWAN is not specified
	 * dewete mdb entwy on aww vwans configuwed on the powt.
	 */
	if (bw_vwan_enabwed(cfg.bw->dev) && vg && cfg.entwy->vid == 0) {
		wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
			cfg.entwy->vid = v->vid;
			cfg.gwoup.vid = v->vid;
			eww = __bw_mdb_dew(&cfg);
		}
	} ewse {
		eww = __bw_mdb_dew(&cfg);
	}

	bw_mdb_config_fini(&cfg);
	wetuwn eww;
}

stwuct bw_mdb_fwush_desc {
	u32 powt_ifindex;
	u16 vid;
	u8 wt_pwotocow;
	u8 state;
	u8 state_mask;
};

static const stwuct nwa_powicy bw_mdbe_attws_dew_buwk_pow[MDBE_ATTW_MAX + 1] = {
	[MDBE_ATTW_WTPWOT] = NWA_POWICY_MIN(NWA_U8, WTPWOT_STATIC),
	[MDBE_ATTW_STATE_MASK] = NWA_POWICY_MASK(NWA_U8, MDB_PEWMANENT),
};

static int bw_mdb_fwush_desc_init(stwuct bw_mdb_fwush_desc *desc,
				  stwuct nwattw *tb[],
				  stwuct netwink_ext_ack *extack)
{
	stwuct bw_mdb_entwy *entwy = nwa_data(tb[MDBA_SET_ENTWY]);
	stwuct nwattw *mdbe_attws[MDBE_ATTW_MAX + 1];
	int eww;

	desc->powt_ifindex = entwy->ifindex;
	desc->vid = entwy->vid;
	desc->state = entwy->state;

	if (!tb[MDBA_SET_ENTWY_ATTWS])
		wetuwn 0;

	eww = nwa_pawse_nested(mdbe_attws, MDBE_ATTW_MAX,
			       tb[MDBA_SET_ENTWY_ATTWS],
			       bw_mdbe_attws_dew_buwk_pow, extack);
	if (eww)
		wetuwn eww;

	if (mdbe_attws[MDBE_ATTW_STATE_MASK])
		desc->state_mask = nwa_get_u8(mdbe_attws[MDBE_ATTW_STATE_MASK]);

	if (mdbe_attws[MDBE_ATTW_WTPWOT])
		desc->wt_pwotocow = nwa_get_u8(mdbe_attws[MDBE_ATTW_WTPWOT]);

	wetuwn 0;
}

static void bw_mdb_fwush_host(stwuct net_bwidge *bw,
			      stwuct net_bwidge_mdb_entwy *mp,
			      const stwuct bw_mdb_fwush_desc *desc)
{
	u8 state;

	if (desc->powt_ifindex && desc->powt_ifindex != bw->dev->ifindex)
		wetuwn;

	if (desc->wt_pwotocow)
		wetuwn;

	state = bw_gwoup_is_w2(&mp->addw) ? MDB_PEWMANENT : 0;
	if (desc->state_mask && (state & desc->state_mask) != desc->state)
		wetuwn;

	bw_muwticast_host_weave(mp, twue);
	if (!mp->powts && netif_wunning(bw->dev))
		mod_timew(&mp->timew, jiffies);
}

static void bw_mdb_fwush_pgs(stwuct net_bwidge *bw,
			     stwuct net_bwidge_mdb_entwy *mp,
			     const stwuct bw_mdb_fwush_desc *desc)
{
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct net_bwidge_powt_gwoup *p;

	fow (pp = &mp->powts; (p = mwock_dewefewence(*pp, bw)) != NUWW;) {
		u8 state;

		if (desc->powt_ifindex &&
		    desc->powt_ifindex != p->key.powt->dev->ifindex) {
			pp = &p->next;
			continue;
		}

		if (desc->wt_pwotocow && desc->wt_pwotocow != p->wt_pwotocow) {
			pp = &p->next;
			continue;
		}

		state = p->fwags & MDB_PG_FWAGS_PEWMANENT ? MDB_PEWMANENT : 0;
		if (desc->state_mask &&
		    (state & desc->state_mask) != desc->state) {
			pp = &p->next;
			continue;
		}

		bw_muwticast_dew_pg(mp, p, pp);
	}
}

static void bw_mdb_fwush(stwuct net_bwidge *bw,
			 const stwuct bw_mdb_fwush_desc *desc)
{
	stwuct net_bwidge_mdb_entwy *mp;

	spin_wock_bh(&bw->muwticast_wock);

	/* Safe vawiant is not needed because entwies awe wemoved fwom the wist
	 * upon gwoup timew expiwation ow bwidge dewetion.
	 */
	hwist_fow_each_entwy(mp, &bw->mdb_wist, mdb_node) {
		if (desc->vid && desc->vid != mp->addw.vid)
			continue;

		bw_mdb_fwush_host(bw, mp, desc);
		bw_mdb_fwush_pgs(bw, mp, desc);
	}

	spin_unwock_bh(&bw->muwticast_wock);
}

int bw_mdb_dew_buwk(stwuct net_device *dev, stwuct nwattw *tb[],
		    stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct bw_mdb_fwush_desc desc = {};
	int eww;

	eww = bw_mdb_fwush_desc_init(&desc, tb, extack);
	if (eww)
		wetuwn eww;

	bw_mdb_fwush(bw, &desc);

	wetuwn 0;
}

static const stwuct nwa_powicy bw_mdbe_attws_get_pow[MDBE_ATTW_MAX + 1] = {
	[MDBE_ATTW_SOUWCE] = NWA_POWICY_WANGE(NWA_BINAWY,
					      sizeof(stwuct in_addw),
					      sizeof(stwuct in6_addw)),
};

static int bw_mdb_get_pawse(stwuct net_device *dev, stwuct nwattw *tb[],
			    stwuct bw_ip *gwoup, stwuct netwink_ext_ack *extack)
{
	stwuct bw_mdb_entwy *entwy = nwa_data(tb[MDBA_GET_ENTWY]);
	stwuct nwattw *mdbe_attws[MDBE_ATTW_MAX + 1];
	int eww;

	if (!tb[MDBA_GET_ENTWY_ATTWS]) {
		__mdb_entwy_to_bw_ip(entwy, gwoup, NUWW);
		wetuwn 0;
	}

	eww = nwa_pawse_nested(mdbe_attws, MDBE_ATTW_MAX,
			       tb[MDBA_GET_ENTWY_ATTWS], bw_mdbe_attws_get_pow,
			       extack);
	if (eww)
		wetuwn eww;

	if (mdbe_attws[MDBE_ATTW_SOUWCE] &&
	    !is_vawid_mdb_souwce(mdbe_attws[MDBE_ATTW_SOUWCE],
				 entwy->addw.pwoto, extack))
		wetuwn -EINVAW;

	__mdb_entwy_to_bw_ip(entwy, gwoup, mdbe_attws);

	wetuwn 0;
}

static stwuct sk_buff *
bw_mdb_get_wepwy_awwoc(const stwuct net_bwidge_mdb_entwy *mp)
{
	stwuct net_bwidge_powt_gwoup *pg;
	size_t nwmsg_size;

	nwmsg_size = NWMSG_AWIGN(sizeof(stwuct bw_powt_msg)) +
		     /* MDBA_MDB */
		     nwa_totaw_size(0) +
		     /* MDBA_MDB_ENTWY */
		     nwa_totaw_size(0);

	if (mp->host_joined)
		nwmsg_size += wtnw_mdb_nwmsg_pg_size(NUWW);

	fow (pg = mwock_dewefewence(mp->powts, mp->bw); pg;
	     pg = mwock_dewefewence(pg->next, mp->bw))
		nwmsg_size += wtnw_mdb_nwmsg_pg_size(pg);

	wetuwn nwmsg_new(nwmsg_size, GFP_ATOMIC);
}

static int bw_mdb_get_wepwy_fiww(stwuct sk_buff *skb,
				 stwuct net_bwidge_mdb_entwy *mp, u32 powtid,
				 u32 seq)
{
	stwuct nwattw *mdb_nest, *mdb_entwy_nest;
	stwuct net_bwidge_powt_gwoup *pg;
	stwuct bw_powt_msg *bpm;
	stwuct nwmsghdw *nwh;
	int eww;

	nwh = nwmsg_put(skb, powtid, seq, WTM_NEWMDB, sizeof(*bpm), 0);
	if (!nwh)
		wetuwn -EMSGSIZE;

	bpm = nwmsg_data(nwh);
	memset(bpm, 0, sizeof(*bpm));
	bpm->famiwy  = AF_BWIDGE;
	bpm->ifindex = mp->bw->dev->ifindex;
	mdb_nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB);
	if (!mdb_nest) {
		eww = -EMSGSIZE;
		goto cancew;
	}
	mdb_entwy_nest = nwa_nest_stawt_nofwag(skb, MDBA_MDB_ENTWY);
	if (!mdb_entwy_nest) {
		eww = -EMSGSIZE;
		goto cancew;
	}

	if (mp->host_joined) {
		eww = __mdb_fiww_info(skb, mp, NUWW);
		if (eww)
			goto cancew;
	}

	fow (pg = mwock_dewefewence(mp->powts, mp->bw); pg;
	     pg = mwock_dewefewence(pg->next, mp->bw)) {
		eww = __mdb_fiww_info(skb, mp, pg);
		if (eww)
			goto cancew;
	}

	nwa_nest_end(skb, mdb_entwy_nest);
	nwa_nest_end(skb, mdb_nest);
	nwmsg_end(skb, nwh);

	wetuwn 0;

cancew:
	nwmsg_cancew(skb, nwh);
	wetuwn eww;
}

int bw_mdb_get(stwuct net_device *dev, stwuct nwattw *tb[], u32 powtid, u32 seq,
	       stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct sk_buff *skb;
	stwuct bw_ip gwoup;
	int eww;

	eww = bw_mdb_get_pawse(dev, tb, &gwoup, extack);
	if (eww)
		wetuwn eww;

	/* Howd the muwticast wock to ensuwe that the MDB entwy does not change
	 * between the time the wepwy size is detewmined and when the wepwy is
	 * fiwwed in.
	 */
	spin_wock_bh(&bw->muwticast_wock);

	mp = bw_mdb_ip_get(bw, &gwoup);
	if (!mp) {
		NW_SET_EWW_MSG_MOD(extack, "MDB entwy not found");
		eww = -ENOENT;
		goto unwock;
	}

	skb = bw_mdb_get_wepwy_awwoc(mp);
	if (!skb) {
		eww = -ENOMEM;
		goto unwock;
	}

	eww = bw_mdb_get_wepwy_fiww(skb, mp, powtid, seq);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to fiww MDB get wepwy");
		goto fwee;
	}

	spin_unwock_bh(&bw->muwticast_wock);

	wetuwn wtnw_unicast(skb, dev_net(dev), powtid);

fwee:
	kfwee_skb(skb);
unwock:
	spin_unwock_bh(&bw->muwticast_wock);
	wetuwn eww;
}
