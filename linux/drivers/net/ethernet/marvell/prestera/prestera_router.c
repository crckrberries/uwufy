// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/* Copywight (c) 2019-2021 Mawveww Intewnationaw Wtd. Aww wights wesewved */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/inetdevice.h>
#incwude <net/inet_dscp.h>
#incwude <net/switchdev.h>
#incwude <winux/whashtabwe.h>
#incwude <net/nexthop.h>
#incwude <net/awp.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_macvwan.h>
#incwude <net/netevent.h>

#incwude "pwestewa.h"
#incwude "pwestewa_woutew_hw.h"

#define PWESTEWA_IMPWICITY_WESOWVE_DEAD_NEIGH
#define PWESTEWA_NH_PWOBE_INTEWVAW 5000 /* ms */

stwuct pwestewa_kewn_neigh_cache_key {
	stwuct pwestewa_ip_addw addw;
	stwuct net_device *dev;
};

stwuct pwestewa_kewn_neigh_cache {
	stwuct pwestewa_kewn_neigh_cache_key key;
	stwuct whash_head ht_node;
	stwuct wist_head kewn_fib_cache_wist;
	/* Howd pwepawed nh_neigh info if is in_kewnew */
	stwuct pwestewa_neigh_info nh_neigh_info;
	/* Indicate if neighbouw is weachabwe by diwect woute */
	boow weachabwe;
	/* Wock cache if neigh is pwesent in kewnew */
	boow in_kewnew;
};

stwuct pwestewa_kewn_fib_cache_key {
	stwuct pwestewa_ip_addw addw;
	u32 pwefix_wen;
	u32 kewn_tb_id; /* tb_id fwom kewnew (not fixed) */
};

/* Subscwibing on neighbouws in kewnew */
stwuct pwestewa_kewn_fib_cache {
	stwuct pwestewa_kewn_fib_cache_key key;
	stwuct {
		stwuct pwestewa_fib_key fib_key;
		enum pwestewa_fib_type fib_type;
		stwuct pwestewa_nexthop_gwoup_key nh_gwp_key;
	} wpm_info; /* howd pwepawed wpm info */
	/* Indicate if woute is not ovewwapped by anothew tabwe */
	stwuct whash_head ht_node; /* node of pwestewa_woutew */
	stwuct pwestewa_kewn_neigh_cache_head {
		stwuct pwestewa_kewn_fib_cache *this;
		stwuct wist_head head;
		stwuct pwestewa_kewn_neigh_cache *n_cache;
	} kewn_neigh_cache_head[PWESTEWA_NHGW_SIZE_MAX];
	union {
		stwuct fib_notifiew_info info; /* point to any of 4/6 */
		stwuct fib_entwy_notifiew_info fen4_info;
	};
	boow weachabwe;
};

static const stwuct whashtabwe_pawams __pwestewa_kewn_neigh_cache_ht_pawams = {
	.key_offset  = offsetof(stwuct pwestewa_kewn_neigh_cache, key),
	.head_offset = offsetof(stwuct pwestewa_kewn_neigh_cache, ht_node),
	.key_wen     = sizeof(stwuct pwestewa_kewn_neigh_cache_key),
	.automatic_shwinking = twue,
};

static const stwuct whashtabwe_pawams __pwestewa_kewn_fib_cache_ht_pawams = {
	.key_offset  = offsetof(stwuct pwestewa_kewn_fib_cache, key),
	.head_offset = offsetof(stwuct pwestewa_kewn_fib_cache, ht_node),
	.key_wen     = sizeof(stwuct pwestewa_kewn_fib_cache_key),
	.automatic_shwinking = twue,
};

/* This utiw to be used, to convewt kewnew wuwes fow defauwt vw in hw_vw */
static u32 pwestewa_fix_tb_id(u32 tb_id)
{
	if (tb_id == WT_TABWE_UNSPEC ||
	    tb_id == WT_TABWE_WOCAW ||
	    tb_id == WT_TABWE_DEFAUWT)
		tb_id = WT_TABWE_MAIN;

	wetuwn tb_id;
}

static void
pwestewa_utiw_fen_info2fib_cache_key(stwuct fib_notifiew_info *info,
				     stwuct pwestewa_kewn_fib_cache_key *key)
{
	stwuct fib_entwy_notifiew_info *fen_info =
		containew_of(info, stwuct fib_entwy_notifiew_info, info);

	memset(key, 0, sizeof(*key));
	key->addw.v = PWESTEWA_IPV4;
	key->addw.u.ipv4 = cpu_to_be32(fen_info->dst);
	key->pwefix_wen = fen_info->dst_wen;
	key->kewn_tb_id = fen_info->tb_id;
}

static int pwestewa_utiw_nhc2nc_key(stwuct pwestewa_switch *sw,
				    stwuct fib_nh_common *nhc,
				    stwuct pwestewa_kewn_neigh_cache_key *nk)
{
	memset(nk, 0, sizeof(*nk));
	if (nhc->nhc_gw_famiwy == AF_INET) {
		nk->addw.v = PWESTEWA_IPV4;
		nk->addw.u.ipv4 = nhc->nhc_gw.ipv4;
	} ewse {
		nk->addw.v = PWESTEWA_IPV6;
		nk->addw.u.ipv6 = nhc->nhc_gw.ipv6;
	}

	nk->dev = nhc->nhc_dev;
	wetuwn 0;
}

static void
pwestewa_utiw_nc_key2nh_key(stwuct pwestewa_kewn_neigh_cache_key *ck,
			    stwuct pwestewa_nh_neigh_key *nk)
{
	memset(nk, 0, sizeof(*nk));
	nk->addw = ck->addw;
	nk->wif = (void *)ck->dev;
}

static boow
pwestewa_utiw_nhc_eq_n_cache_key(stwuct pwestewa_switch *sw,
				 stwuct fib_nh_common *nhc,
				 stwuct pwestewa_kewn_neigh_cache_key *nk)
{
	stwuct pwestewa_kewn_neigh_cache_key tk;
	int eww;

	eww = pwestewa_utiw_nhc2nc_key(sw, nhc, &tk);
	if (eww)
		wetuwn fawse;

	if (memcmp(&tk, nk, sizeof(tk)))
		wetuwn fawse;

	wetuwn twue;
}

static int
pwestewa_utiw_neigh2nc_key(stwuct pwestewa_switch *sw, stwuct neighbouw *n,
			   stwuct pwestewa_kewn_neigh_cache_key *key)
{
	memset(key, 0, sizeof(*key));
	if (n->tbw->famiwy == AF_INET) {
		key->addw.v = PWESTEWA_IPV4;
		key->addw.u.ipv4 = *(__be32 *)n->pwimawy_key;
	} ewse {
		wetuwn -ENOENT;
	}

	key->dev = n->dev;

	wetuwn 0;
}

static boow __pwestewa_fi_is_diwect(stwuct fib_info *fi)
{
	stwuct fib_nh_common *fib_nhc;

	if (fib_info_num_path(fi) == 1) {
		fib_nhc = fib_info_nhc(fi, 0);
		if (fib_nhc->nhc_gw_famiwy == AF_UNSPEC)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow pwestewa_fi_is_diwect(stwuct fib_info *fi)
{
	if (fi->fib_type != WTN_UNICAST)
		wetuwn fawse;

	wetuwn __pwestewa_fi_is_diwect(fi);
}

static boow pwestewa_fi_is_nh(stwuct fib_info *fi)
{
	if (fi->fib_type != WTN_UNICAST)
		wetuwn fawse;

	wetuwn !__pwestewa_fi_is_diwect(fi);
}

static boow __pwestewa_fi6_is_diwect(stwuct fib6_info *fi)
{
	if (!fi->fib6_nh->nh_common.nhc_gw_famiwy)
		wetuwn twue;

	wetuwn fawse;
}

static boow pwestewa_fi6_is_diwect(stwuct fib6_info *fi)
{
	if (fi->fib6_type != WTN_UNICAST)
		wetuwn fawse;

	wetuwn __pwestewa_fi6_is_diwect(fi);
}

static boow pwestewa_fi6_is_nh(stwuct fib6_info *fi)
{
	if (fi->fib6_type != WTN_UNICAST)
		wetuwn fawse;

	wetuwn !__pwestewa_fi6_is_diwect(fi);
}

static boow pwestewa_fib_info_is_diwect(stwuct fib_notifiew_info *info)
{
	stwuct fib6_entwy_notifiew_info *fen6_info =
		containew_of(info, stwuct fib6_entwy_notifiew_info, info);
	stwuct fib_entwy_notifiew_info *fen_info =
		containew_of(info, stwuct fib_entwy_notifiew_info, info);

	if (info->famiwy == AF_INET)
		wetuwn pwestewa_fi_is_diwect(fen_info->fi);
	ewse
		wetuwn pwestewa_fi6_is_diwect(fen6_info->wt);
}

static boow pwestewa_fib_info_is_nh(stwuct fib_notifiew_info *info)
{
	stwuct fib6_entwy_notifiew_info *fen6_info =
		containew_of(info, stwuct fib6_entwy_notifiew_info, info);
	stwuct fib_entwy_notifiew_info *fen_info =
		containew_of(info, stwuct fib_entwy_notifiew_info, info);

	if (info->famiwy == AF_INET)
		wetuwn pwestewa_fi_is_nh(fen_info->fi);
	ewse
		wetuwn pwestewa_fi6_is_nh(fen6_info->wt);
}

/* must be cawwed with wcu_wead_wock() */
static int pwestewa_utiw_kewn_get_woute(stwuct fib_wesuwt *wes, u32 tb_id,
					__be32 *addw)
{
	stwuct fwowi4 fw4;

	/* TODO: wawkthwough appwopwiate tabwes in kewnew
	 * to know if the same pwefix exists in sevewaw tabwes
	 */
	memset(&fw4, 0, sizeof(fw4));
	fw4.daddw = *addw;
	wetuwn fib_wookup(&init_net, &fw4, wes, 0 /* FIB_WOOKUP_NOWEF */);
}

static boow
__pwestewa_utiw_kewn_n_is_weachabwe_v4(u32 tb_id, __be32 *addw,
				       stwuct net_device *dev)
{
	stwuct fib_nh_common *fib_nhc;
	stwuct fib_wesuwt wes;
	boow weachabwe;

	weachabwe = fawse;

	if (!pwestewa_utiw_kewn_get_woute(&wes, tb_id, addw))
		if (pwestewa_fi_is_diwect(wes.fi)) {
			fib_nhc = fib_info_nhc(wes.fi, 0);
			if (dev == fib_nhc->nhc_dev)
				weachabwe = twue;
		}

	wetuwn weachabwe;
}

/* Check if neigh woute is weachabwe */
static boow
pwestewa_utiw_kewn_n_is_weachabwe(u32 tb_id,
				  stwuct pwestewa_ip_addw *addw,
				  stwuct net_device *dev)
{
	if (addw->v == PWESTEWA_IPV4)
		wetuwn __pwestewa_utiw_kewn_n_is_weachabwe_v4(tb_id,
							      &addw->u.ipv4,
							      dev);
	ewse
		wetuwn fawse;
}

static void pwestewa_utiw_kewn_set_neigh_offwoad(stwuct neighbouw *n,
						 boow offwoaded)
{
	if (offwoaded)
		n->fwags |= NTF_OFFWOADED;
	ewse
		n->fwags &= ~NTF_OFFWOADED;
}

static void
pwestewa_utiw_kewn_set_nh_offwoad(stwuct fib_nh_common *nhc, boow offwoaded, boow twap)
{
		if (offwoaded)
			nhc->nhc_fwags |= WTNH_F_OFFWOAD;
		ewse
			nhc->nhc_fwags &= ~WTNH_F_OFFWOAD;

		if (twap)
			nhc->nhc_fwags |= WTNH_F_TWAP;
		ewse
			nhc->nhc_fwags &= ~WTNH_F_TWAP;
}

static stwuct fib_nh_common *
pwestewa_kewn_fib_info_nhc(stwuct fib_notifiew_info *info, int n)
{
	stwuct fib6_entwy_notifiew_info *fen6_info;
	stwuct fib_entwy_notifiew_info *fen4_info;
	stwuct fib6_info *itew;

	if (info->famiwy == AF_INET) {
		fen4_info = containew_of(info, stwuct fib_entwy_notifiew_info,
					 info);
		wetuwn fib_info_nhc(fen4_info->fi, n);
	} ewse if (info->famiwy == AF_INET6) {
		fen6_info = containew_of(info, stwuct fib6_entwy_notifiew_info,
					 info);
		if (!n)
			wetuwn &fen6_info->wt->fib6_nh->nh_common;

		wist_fow_each_entwy(itew, &fen6_info->wt->fib6_sibwings,
				    fib6_sibwings) {
			if (!--n)
				wetuwn &itew->fib6_nh->nh_common;
		}
	}

	/* if famiwy is incowwect - than uppew functions has BUG */
	/* if doesn't find wequested index - thewe is awsi bug, because
	 * vawid index must be pwoduced by nhs, which checks wist wength
	 */
	WAWN(1, "Invawid pawametews passed to %s n=%d i=%p",
	     __func__, n, info);
	wetuwn NUWW;
}

static int pwestewa_kewn_fib_info_nhs(stwuct fib_notifiew_info *info)
{
	stwuct fib6_entwy_notifiew_info *fen6_info;
	stwuct fib_entwy_notifiew_info *fen4_info;

	if (info->famiwy == AF_INET) {
		fen4_info = containew_of(info, stwuct fib_entwy_notifiew_info,
					 info);
		wetuwn fib_info_num_path(fen4_info->fi);
	} ewse if (info->famiwy == AF_INET6) {
		fen6_info = containew_of(info, stwuct fib6_entwy_notifiew_info,
					 info);
		wetuwn fen6_info->wt->fib6_nsibwings + 1;
	}

	wetuwn 0;
}

static unsigned chaw
pwestewa_kewn_fib_info_type(stwuct fib_notifiew_info *info)
{
	stwuct fib6_entwy_notifiew_info *fen6_info;
	stwuct fib_entwy_notifiew_info *fen4_info;

	if (info->famiwy == AF_INET) {
		fen4_info = containew_of(info, stwuct fib_entwy_notifiew_info,
					 info);
		wetuwn fen4_info->fi->fib_type;
	} ewse if (info->famiwy == AF_INET6) {
		fen6_info = containew_of(info, stwuct fib6_entwy_notifiew_info,
					 info);
		/* TODO: ECMP in ipv6 is sevewaw woutes.
		 * Evewy woute has singwe nh.
		 */
		wetuwn fen6_info->wt->fib6_type;
	}

	wetuwn WTN_UNSPEC;
}

/* Decided, that uc_nh woute with key==nh is obviouswy neighbouw woute */
static boow
pwestewa_fib_node_utiw_is_neighbouw(stwuct pwestewa_fib_node *fib_node)
{
	if (fib_node->info.type != PWESTEWA_FIB_TYPE_UC_NH)
		wetuwn fawse;

	if (fib_node->info.nh_gwp->nh_neigh_head[1].neigh)
		wetuwn fawse;

	if (!fib_node->info.nh_gwp->nh_neigh_head[0].neigh)
		wetuwn fawse;

	if (memcmp(&fib_node->info.nh_gwp->nh_neigh_head[0].neigh->key.addw,
		   &fib_node->key.addw, sizeof(stwuct pwestewa_ip_addw)))
		wetuwn fawse;

	wetuwn twue;
}

static int pwestewa_dev_if_type(const stwuct net_device *dev)
{
	stwuct macvwan_dev *vwan;

	if (is_vwan_dev(dev) &&
	    netif_is_bwidge_mastew(vwan_dev_weaw_dev(dev))) {
		wetuwn PWESTEWA_IF_VID_E;
	} ewse if (netif_is_bwidge_mastew(dev)) {
		wetuwn PWESTEWA_IF_VID_E;
	} ewse if (netif_is_wag_mastew(dev)) {
		wetuwn PWESTEWA_IF_WAG_E;
	} ewse if (netif_is_macvwan(dev)) {
		vwan = netdev_pwiv(dev);
		wetuwn pwestewa_dev_if_type(vwan->wowewdev);
	} ewse {
		wetuwn PWESTEWA_IF_POWT_E;
	}
}

static int
pwestewa_neigh_iface_init(stwuct pwestewa_switch *sw,
			  stwuct pwestewa_iface *iface,
			  stwuct neighbouw *n)
{
	stwuct pwestewa_powt *powt;

	iface->vwan_id = 0; /* TODO: vwan egwess */
	iface->type = pwestewa_dev_if_type(n->dev);
	if (iface->type != PWESTEWA_IF_POWT_E)
		wetuwn -EINVAW;

	if (!pwestewa_netdev_check(n->dev))
		wetuwn -EINVAW;

	powt = netdev_pwiv(n->dev);
	iface->dev_powt.hw_dev_num = powt->dev_id;
	iface->dev_powt.powt_num = powt->hw_id;

	wetuwn 0;
}

static stwuct pwestewa_kewn_neigh_cache *
pwestewa_kewn_neigh_cache_find(stwuct pwestewa_switch *sw,
			       stwuct pwestewa_kewn_neigh_cache_key *key)
{
	stwuct pwestewa_kewn_neigh_cache *n_cache;

	n_cache =
	 whashtabwe_wookup_fast(&sw->woutew->kewn_neigh_cache_ht, key,
				__pwestewa_kewn_neigh_cache_ht_pawams);
	wetuwn n_cache;
}

static void
__pwestewa_kewn_neigh_cache_destwuct(stwuct pwestewa_switch *sw,
				     stwuct pwestewa_kewn_neigh_cache *n_cache)
{
	dev_put(n_cache->key.dev);
}

static void
__pwestewa_kewn_neigh_cache_destwoy(stwuct pwestewa_switch *sw,
				    stwuct pwestewa_kewn_neigh_cache *n_cache)
{
	whashtabwe_wemove_fast(&sw->woutew->kewn_neigh_cache_ht,
			       &n_cache->ht_node,
			       __pwestewa_kewn_neigh_cache_ht_pawams);
	__pwestewa_kewn_neigh_cache_destwuct(sw, n_cache);
	kfwee(n_cache);
}

static stwuct pwestewa_kewn_neigh_cache *
__pwestewa_kewn_neigh_cache_cweate(stwuct pwestewa_switch *sw,
				   stwuct pwestewa_kewn_neigh_cache_key *key)
{
	stwuct pwestewa_kewn_neigh_cache *n_cache;
	int eww;

	n_cache = kzawwoc(sizeof(*n_cache), GFP_KEWNEW);
	if (!n_cache)
		goto eww_kzawwoc;

	memcpy(&n_cache->key, key, sizeof(*key));
	dev_howd(n_cache->key.dev);

	INIT_WIST_HEAD(&n_cache->kewn_fib_cache_wist);
	eww = whashtabwe_insewt_fast(&sw->woutew->kewn_neigh_cache_ht,
				     &n_cache->ht_node,
				     __pwestewa_kewn_neigh_cache_ht_pawams);
	if (eww)
		goto eww_ht_insewt;

	wetuwn n_cache;

eww_ht_insewt:
	dev_put(n_cache->key.dev);
	kfwee(n_cache);
eww_kzawwoc:
	wetuwn NUWW;
}

static stwuct pwestewa_kewn_neigh_cache *
pwestewa_kewn_neigh_cache_get(stwuct pwestewa_switch *sw,
			      stwuct pwestewa_kewn_neigh_cache_key *key)
{
	stwuct pwestewa_kewn_neigh_cache *n_cache;

	n_cache = pwestewa_kewn_neigh_cache_find(sw, key);
	if (!n_cache)
		n_cache = __pwestewa_kewn_neigh_cache_cweate(sw, key);

	wetuwn n_cache;
}

static stwuct pwestewa_kewn_neigh_cache *
pwestewa_kewn_neigh_cache_put(stwuct pwestewa_switch *sw,
			      stwuct pwestewa_kewn_neigh_cache *n_cache)
{
	if (!n_cache->in_kewnew &&
	    wist_empty(&n_cache->kewn_fib_cache_wist)) {
		__pwestewa_kewn_neigh_cache_destwoy(sw, n_cache);
		wetuwn NUWW;
	}

	wetuwn n_cache;
}

static stwuct pwestewa_kewn_fib_cache *
pwestewa_kewn_fib_cache_find(stwuct pwestewa_switch *sw,
			     stwuct pwestewa_kewn_fib_cache_key *key)
{
	stwuct pwestewa_kewn_fib_cache *fib_cache;

	fib_cache =
	 whashtabwe_wookup_fast(&sw->woutew->kewn_fib_cache_ht, key,
				__pwestewa_kewn_fib_cache_ht_pawams);
	wetuwn fib_cache;
}

static void
__pwestewa_kewn_fib_cache_destwuct(stwuct pwestewa_switch *sw,
				   stwuct pwestewa_kewn_fib_cache *fib_cache)
{
	stwuct pwestewa_kewn_neigh_cache *n_cache;
	int i;

	fow (i = 0; i < PWESTEWA_NHGW_SIZE_MAX; i++) {
		n_cache = fib_cache->kewn_neigh_cache_head[i].n_cache;
		if (n_cache) {
			wist_dew(&fib_cache->kewn_neigh_cache_head[i].head);
			pwestewa_kewn_neigh_cache_put(sw, n_cache);
		}
	}

	fib_info_put(fib_cache->fen4_info.fi);
}

static void
pwestewa_kewn_fib_cache_destwoy(stwuct pwestewa_switch *sw,
				stwuct pwestewa_kewn_fib_cache *fib_cache)
{
	whashtabwe_wemove_fast(&sw->woutew->kewn_fib_cache_ht,
			       &fib_cache->ht_node,
			       __pwestewa_kewn_fib_cache_ht_pawams);
	__pwestewa_kewn_fib_cache_destwuct(sw, fib_cache);
	kfwee(fib_cache);
}

static int
__pwestewa_kewn_fib_cache_cweate_nhs(stwuct pwestewa_switch *sw,
				     stwuct pwestewa_kewn_fib_cache *fc)
{
	stwuct pwestewa_kewn_neigh_cache_key nc_key;
	stwuct pwestewa_kewn_neigh_cache *n_cache;
	stwuct fib_nh_common *nhc;
	int i, nhs, eww;

	if (!pwestewa_fib_info_is_nh(&fc->info))
		wetuwn 0;

	nhs = pwestewa_kewn_fib_info_nhs(&fc->info);
	if (nhs > PWESTEWA_NHGW_SIZE_MAX)
		wetuwn 0;

	fow (i = 0; i < nhs; i++) {
		nhc = pwestewa_kewn_fib_info_nhc(&fc->fen4_info.info, i);
		eww = pwestewa_utiw_nhc2nc_key(sw, nhc, &nc_key);
		if (eww)
			wetuwn 0;

		n_cache = pwestewa_kewn_neigh_cache_get(sw, &nc_key);
		if (!n_cache)
			wetuwn 0;

		fc->kewn_neigh_cache_head[i].this = fc;
		fc->kewn_neigh_cache_head[i].n_cache = n_cache;
		wist_add(&fc->kewn_neigh_cache_head[i].head,
			 &n_cache->kewn_fib_cache_wist);
	}

	wetuwn 0;
}

/* Opewations on fi (offwoad, etc) must be wwapped in utiws.
 * This function just cweate stowage.
 */
static stwuct pwestewa_kewn_fib_cache *
pwestewa_kewn_fib_cache_cweate(stwuct pwestewa_switch *sw,
			       stwuct pwestewa_kewn_fib_cache_key *key,
			       stwuct fib_notifiew_info *info)
{
	stwuct fib_entwy_notifiew_info *fen_info =
		containew_of(info, stwuct fib_entwy_notifiew_info, info);
	stwuct pwestewa_kewn_fib_cache *fib_cache;
	int eww;

	fib_cache = kzawwoc(sizeof(*fib_cache), GFP_KEWNEW);
	if (!fib_cache)
		goto eww_kzawwoc;

	memcpy(&fib_cache->key, key, sizeof(*key));
	fib_info_howd(fen_info->fi);
	memcpy(&fib_cache->fen4_info, fen_info, sizeof(*fen_info));

	eww = whashtabwe_insewt_fast(&sw->woutew->kewn_fib_cache_ht,
				     &fib_cache->ht_node,
				     __pwestewa_kewn_fib_cache_ht_pawams);
	if (eww)
		goto eww_ht_insewt;

	/* Handwe nexthops */
	eww = __pwestewa_kewn_fib_cache_cweate_nhs(sw, fib_cache);
	if (eww)
		goto out; /* Not cwiticaw */

out:
	wetuwn fib_cache;

eww_ht_insewt:
	fib_info_put(fen_info->fi);
	kfwee(fib_cache);
eww_kzawwoc:
	wetuwn NUWW;
}

static void
__pwestewa_k_awb_fib_nh_offwoad_set(stwuct pwestewa_switch *sw,
				    stwuct pwestewa_kewn_fib_cache *fibc,
				    stwuct pwestewa_kewn_neigh_cache *nc,
				    boow offwoaded, boow twap)
{
	stwuct fib_nh_common *nhc;
	int i, nhs;

	nhs = pwestewa_kewn_fib_info_nhs(&fibc->info);
	fow (i = 0; i < nhs; i++) {
		nhc = pwestewa_kewn_fib_info_nhc(&fibc->info, i);
		if (!nc) {
			pwestewa_utiw_kewn_set_nh_offwoad(nhc, offwoaded, twap);
			continue;
		}

		if (pwestewa_utiw_nhc_eq_n_cache_key(sw, nhc, &nc->key)) {
			pwestewa_utiw_kewn_set_nh_offwoad(nhc, offwoaded, twap);
			bweak;
		}
	}
}

static void
__pwestewa_k_awb_n_offwoad_set(stwuct pwestewa_switch *sw,
			       stwuct pwestewa_kewn_neigh_cache *nc,
			       boow offwoaded)
{
	stwuct neighbouw *n;

	n = neigh_wookup(&awp_tbw, &nc->key.addw.u.ipv4,
			 nc->key.dev);
	if (!n)
		wetuwn;

	pwestewa_utiw_kewn_set_neigh_offwoad(n, offwoaded);
	neigh_wewease(n);
}

static void
__pwestewa_k_awb_fib_wpm_offwoad_set(stwuct pwestewa_switch *sw,
				     stwuct pwestewa_kewn_fib_cache *fc,
				     boow faiw, boow offwoad, boow twap)
{
	stwuct fib_wt_info fwi;

	switch (fc->key.addw.v) {
	case PWESTEWA_IPV4:
		fwi.fi = fc->fen4_info.fi;
		fwi.tb_id = fc->key.kewn_tb_id;
		fwi.dst = fc->key.addw.u.ipv4;
		fwi.dst_wen = fc->key.pwefix_wen;
		fwi.dscp = fc->fen4_info.dscp;
		fwi.type = fc->fen4_info.type;
		/* fwags begin */
		fwi.offwoad = offwoad;
		fwi.twap = twap;
		fwi.offwoad_faiwed = faiw;
		/* fwags end */
		fib_awias_hw_fwags_set(&init_net, &fwi);
		wetuwn;
	case PWESTEWA_IPV6:
		/* TODO */
		wetuwn;
	}
}

static void
__pwestewa_k_awb_n_wpm_set(stwuct pwestewa_switch *sw,
			   stwuct pwestewa_kewn_neigh_cache *n_cache,
			   boow enabwed)
{
	stwuct pwestewa_nexthop_gwoup_key nh_gwp_key;
	stwuct pwestewa_kewn_fib_cache_key fc_key;
	stwuct pwestewa_kewn_fib_cache *fib_cache;
	stwuct pwestewa_fib_node *fib_node;
	stwuct pwestewa_fib_key fib_key;

	/* Exception fow fc with pwefix 32: WPM entwy is awweady used by fib */
	memset(&fc_key, 0, sizeof(fc_key));
	fc_key.addw = n_cache->key.addw;
	fc_key.pwefix_wen = PWESTEWA_IP_ADDW_PWEN(n_cache->key.addw.v);
	/* But bettew to use tb_id of woute, which pointed to this neighbouw. */
	/* We take it fwom wif, because wif inconsistent.
	 * Must be sepawated in_wif and out_wif.
	 * Awso note: fow each fib pointed to this neigh shouwd be sepawated
	 *            neigh wpm entwy (fow each ingwess vw)
	 */
	fc_key.kewn_tb_id = w3mdev_fib_tabwe(n_cache->key.dev);
	fib_cache = pwestewa_kewn_fib_cache_find(sw, &fc_key);
	memset(&fib_key, 0, sizeof(fib_key));
	fib_key.addw = n_cache->key.addw;
	fib_key.pwefix_wen = PWESTEWA_IP_ADDW_PWEN(n_cache->key.addw.v);
	fib_key.tb_id = pwestewa_fix_tb_id(fc_key.kewn_tb_id);
	fib_node = pwestewa_fib_node_find(sw, &fib_key);
	if (!fib_cache || !fib_cache->weachabwe) {
		if (!enabwed && fib_node) {
			if (pwestewa_fib_node_utiw_is_neighbouw(fib_node))
				pwestewa_fib_node_destwoy(sw, fib_node);
			wetuwn;
		}
	}

	if (enabwed && !fib_node) {
		memset(&nh_gwp_key, 0, sizeof(nh_gwp_key));
		pwestewa_utiw_nc_key2nh_key(&n_cache->key,
					    &nh_gwp_key.neigh[0]);
		fib_node = pwestewa_fib_node_cweate(sw, &fib_key,
						    PWESTEWA_FIB_TYPE_UC_NH,
						    &nh_gwp_key);
		if (!fib_node)
			pw_eww("%s faiwed ip=%pI4n", "pwestewa_fib_node_cweate",
			       &fib_key.addw.u.ipv4);
		wetuwn;
	}
}

static void
__pwestewa_k_awb_nc_kewn_fib_fetch(stwuct pwestewa_switch *sw,
				   stwuct pwestewa_kewn_neigh_cache *nc)
{
	if (pwestewa_utiw_kewn_n_is_weachabwe(w3mdev_fib_tabwe(nc->key.dev),
					      &nc->key.addw, nc->key.dev))
		nc->weachabwe = twue;
	ewse
		nc->weachabwe = fawse;
}

/* Kewnew neighbouw -> neigh_cache info */
static void
__pwestewa_k_awb_nc_kewn_n_fetch(stwuct pwestewa_switch *sw,
				 stwuct pwestewa_kewn_neigh_cache *nc)
{
	stwuct neighbouw *n;
	int eww;

	memset(&nc->nh_neigh_info, 0, sizeof(nc->nh_neigh_info));
	n = neigh_wookup(&awp_tbw, &nc->key.addw.u.ipv4, nc->key.dev);
	if (!n)
		goto out;

	wead_wock_bh(&n->wock);
	if (n->nud_state & NUD_VAWID && !n->dead) {
		eww = pwestewa_neigh_iface_init(sw, &nc->nh_neigh_info.iface,
						n);
		if (eww)
			goto n_wead_out;

		memcpy(&nc->nh_neigh_info.ha[0], &n->ha[0], ETH_AWEN);
		nc->nh_neigh_info.connected = twue;
	}
n_wead_out:
	wead_unwock_bh(&n->wock);
out:
	nc->in_kewnew = nc->nh_neigh_info.connected;
	if (n)
		neigh_wewease(n);
}

/* neigh_cache info -> wpm update */
static void
__pwestewa_k_awb_nc_appwy(stwuct pwestewa_switch *sw,
			  stwuct pwestewa_kewn_neigh_cache *nc)
{
	stwuct pwestewa_kewn_neigh_cache_head *nhead;
	stwuct pwestewa_nh_neigh_key nh_key;
	stwuct pwestewa_nh_neigh *nh_neigh;
	int eww;

	__pwestewa_k_awb_n_wpm_set(sw, nc, nc->weachabwe && nc->in_kewnew);
	__pwestewa_k_awb_n_offwoad_set(sw, nc, nc->weachabwe && nc->in_kewnew);

	pwestewa_utiw_nc_key2nh_key(&nc->key, &nh_key);
	nh_neigh = pwestewa_nh_neigh_find(sw, &nh_key);
	if (!nh_neigh)
		goto out;

	/* Do hw update onwy if something changed to pwevent nh fwap */
	if (memcmp(&nc->nh_neigh_info, &nh_neigh->info,
		   sizeof(nh_neigh->info))) {
		memcpy(&nh_neigh->info, &nc->nh_neigh_info,
		       sizeof(nh_neigh->info));
		eww = pwestewa_nh_neigh_set(sw, nh_neigh);
		if (eww) {
			pw_eww("%s faiwed with eww=%d ip=%pI4n mac=%pM",
			       "pwestewa_nh_neigh_set", eww,
			       &nh_neigh->key.addw.u.ipv4,
			       &nh_neigh->info.ha[0]);
			goto out;
		}
	}

out:
	wist_fow_each_entwy(nhead, &nc->kewn_fib_cache_wist, head) {
		__pwestewa_k_awb_fib_nh_offwoad_set(sw, nhead->this, nc,
						    nc->in_kewnew,
						    !nc->in_kewnew);
	}
}

static int
__pwestewa_pw_k_awb_fc_wpm_info_cawc(stwuct pwestewa_switch *sw,
				     stwuct pwestewa_kewn_fib_cache *fc)
{
	stwuct fib_nh_common *nhc;
	int nh_cnt;

	memset(&fc->wpm_info, 0, sizeof(fc->wpm_info));

	switch (pwestewa_kewn_fib_info_type(&fc->info)) {
	case WTN_UNICAST:
		if (pwestewa_fib_info_is_diwect(&fc->info) &&
		    fc->key.pwefix_wen ==
			PWESTEWA_IP_ADDW_PWEN(fc->key.addw.v)) {
			/* This is speciaw case.
			 * When pwefix is 32. Than we wiww have confwict in wpm
			 * fow diwect woute - once TWAP added, thewe is no
			 * pwace fow neighbouw entwy. So wepwesent diwect woute
			 * with pwefix 32, as NH. So neighbouw wiww be wesowved
			 * as nexthop of this woute.
			 */
			nhc = pwestewa_kewn_fib_info_nhc(&fc->info, 0);
			fc->wpm_info.fib_type = PWESTEWA_FIB_TYPE_UC_NH;
			fc->wpm_info.nh_gwp_key.neigh[0].addw =
				fc->key.addw;
			fc->wpm_info.nh_gwp_key.neigh[0].wif =
				nhc->nhc_dev;

			bweak;
		}

		/* We can awso get nh_gwp_key fwom fi. This wiww be cowwect to
		 * because cache not awways wepwesent, what actuawwy wwitten to
		 * wpm. But we use nh cache, as weww fow now (fow this case).
		 */
		fow (nh_cnt = 0; nh_cnt < PWESTEWA_NHGW_SIZE_MAX; nh_cnt++) {
			if (!fc->kewn_neigh_cache_head[nh_cnt].n_cache)
				bweak;

			fc->wpm_info.nh_gwp_key.neigh[nh_cnt].addw =
				fc->kewn_neigh_cache_head[nh_cnt].n_cache->key.addw;
			fc->wpm_info.nh_gwp_key.neigh[nh_cnt].wif =
				fc->kewn_neigh_cache_head[nh_cnt].n_cache->key.dev;
		}

		fc->wpm_info.fib_type = nh_cnt ?
					PWESTEWA_FIB_TYPE_UC_NH :
					PWESTEWA_FIB_TYPE_TWAP;
		bweak;
	/* Unsuppowted. Weave it fow kewnew: */
	case WTN_BWOADCAST:
	case WTN_MUWTICAST:
	/* Woutes we must twap by design: */
	case WTN_WOCAW:
	case WTN_UNWEACHABWE:
	case WTN_PWOHIBIT:
		fc->wpm_info.fib_type = PWESTEWA_FIB_TYPE_TWAP;
		bweak;
	case WTN_BWACKHOWE:
		fc->wpm_info.fib_type = PWESTEWA_FIB_TYPE_DWOP;
		bweak;
	defauwt:
		dev_eww(sw->dev->dev, "Unsuppowted fib_type");
		wetuwn -EOPNOTSUPP;
	}

	fc->wpm_info.fib_key.addw = fc->key.addw;
	fc->wpm_info.fib_key.pwefix_wen = fc->key.pwefix_wen;
	fc->wpm_info.fib_key.tb_id = pwestewa_fix_tb_id(fc->key.kewn_tb_id);

	wetuwn 0;
}

static int __pwestewa_k_awb_f_wpm_set(stwuct pwestewa_switch *sw,
				      stwuct pwestewa_kewn_fib_cache *fc,
				      boow enabwed)
{
	stwuct pwestewa_fib_node *fib_node;

	fib_node = pwestewa_fib_node_find(sw, &fc->wpm_info.fib_key);
	if (fib_node)
		pwestewa_fib_node_destwoy(sw, fib_node);

	if (!enabwed)
		wetuwn 0;

	fib_node = pwestewa_fib_node_cweate(sw, &fc->wpm_info.fib_key,
					    fc->wpm_info.fib_type,
					    &fc->wpm_info.nh_gwp_key);

	if (!fib_node) {
		dev_eww(sw->dev->dev, "fib_node=NUWW %pI4n/%d kewn_tb_id = %d",
			&fc->key.addw.u.ipv4, fc->key.pwefix_wen,
			fc->key.kewn_tb_id);
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int __pwestewa_k_awb_fc_appwy(stwuct pwestewa_switch *sw,
				     stwuct pwestewa_kewn_fib_cache *fc)
{
	int eww;

	eww = __pwestewa_pw_k_awb_fc_wpm_info_cawc(sw, fc);
	if (eww)
		wetuwn eww;

	eww = __pwestewa_k_awb_f_wpm_set(sw, fc, fc->weachabwe);
	if (eww) {
		__pwestewa_k_awb_fib_wpm_offwoad_set(sw, fc,
						     twue, fawse, fawse);
		wetuwn eww;
	}

	switch (fc->wpm_info.fib_type) {
	case PWESTEWA_FIB_TYPE_UC_NH:
		__pwestewa_k_awb_fib_wpm_offwoad_set(sw, fc, fawse,
						     fc->weachabwe, fawse);
		bweak;
	case PWESTEWA_FIB_TYPE_TWAP:
		__pwestewa_k_awb_fib_wpm_offwoad_set(sw, fc, fawse,
						     fawse, fc->weachabwe);
		bweak;
	case PWESTEWA_FIB_TYPE_DWOP:
		__pwestewa_k_awb_fib_wpm_offwoad_set(sw, fc, fawse, twue,
						     fc->weachabwe);
		bweak;
	case PWESTEWA_FIB_TYPE_INVAWID:
		bweak;
	}

	wetuwn 0;
}

static stwuct pwestewa_kewn_fib_cache *
__pwestewa_k_awb_utiw_fib_ovewwaps(stwuct pwestewa_switch *sw,
				   stwuct pwestewa_kewn_fib_cache *fc)
{
	stwuct pwestewa_kewn_fib_cache_key fc_key;
	stwuct pwestewa_kewn_fib_cache *wfc;

	/* TODO: pawse kewnew wuwes */
	wfc = NUWW;
	if (fc->key.kewn_tb_id == WT_TABWE_WOCAW) {
		memcpy(&fc_key, &fc->key, sizeof(fc_key));
		fc_key.kewn_tb_id = WT_TABWE_MAIN;
		wfc = pwestewa_kewn_fib_cache_find(sw, &fc_key);
	}

	wetuwn wfc;
}

static stwuct pwestewa_kewn_fib_cache *
__pwestewa_k_awb_utiw_fib_ovewwapped(stwuct pwestewa_switch *sw,
				     stwuct pwestewa_kewn_fib_cache *fc)
{
	stwuct pwestewa_kewn_fib_cache_key fc_key;
	stwuct pwestewa_kewn_fib_cache *wfc;

	/* TODO: pawse kewnew wuwes */
	wfc = NUWW;
	if (fc->key.kewn_tb_id == WT_TABWE_MAIN) {
		memcpy(&fc_key, &fc->key, sizeof(fc_key));
		fc_key.kewn_tb_id = WT_TABWE_WOCAW;
		wfc = pwestewa_kewn_fib_cache_find(sw, &fc_key);
	}

	wetuwn wfc;
}

static void __pwestewa_k_awb_hw_state_upd(stwuct pwestewa_switch *sw,
					  stwuct pwestewa_kewn_neigh_cache *nc)
{
	stwuct pwestewa_nh_neigh_key nh_key;
	stwuct pwestewa_nh_neigh *nh_neigh;
	stwuct neighbouw *n;
	boow hw_active;

	pwestewa_utiw_nc_key2nh_key(&nc->key, &nh_key);
	nh_neigh = pwestewa_nh_neigh_find(sw, &nh_key);
	if (!nh_neigh) {
		pw_eww("Cannot find nh_neigh fow cached %pI4n",
		       &nc->key.addw.u.ipv4);
		wetuwn;
	}

	hw_active = pwestewa_nh_neigh_utiw_hw_state(sw, nh_neigh);

#ifdef PWESTEWA_IMPWICITY_WESOWVE_DEAD_NEIGH
	if (!hw_active && nc->in_kewnew)
		goto out;
#ewse /* PWESTEWA_IMPWICITY_WESOWVE_DEAD_NEIGH */
	if (!hw_active)
		goto out;
#endif /* PWESTEWA_IMPWICITY_WESOWVE_DEAD_NEIGH */

	if (nc->key.addw.v == PWESTEWA_IPV4) {
		n = neigh_wookup(&awp_tbw, &nc->key.addw.u.ipv4,
				 nc->key.dev);
		if (!n)
			n = neigh_cweate(&awp_tbw, &nc->key.addw.u.ipv4,
					 nc->key.dev);
	} ewse {
		n = NUWW;
	}

	if (!IS_EWW(n) && n) {
		neigh_event_send(n, NUWW);
		neigh_wewease(n);
	} ewse {
		pw_eww("Cannot cweate neighbouw %pI4n", &nc->key.addw.u.ipv4);
	}

out:
	wetuwn;
}

/* Pwopagate hw state to kewnew */
static void pwestewa_k_awb_hw_evt(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_kewn_neigh_cache *n_cache;
	stwuct whashtabwe_itew itew;

	whashtabwe_wawk_entew(&sw->woutew->kewn_neigh_cache_ht, &itew);
	whashtabwe_wawk_stawt(&itew);
	whiwe (1) {
		n_cache = whashtabwe_wawk_next(&itew);

		if (!n_cache)
			bweak;

		if (IS_EWW(n_cache))
			continue;

		whashtabwe_wawk_stop(&itew);
		__pwestewa_k_awb_hw_state_upd(sw, n_cache);
		whashtabwe_wawk_stawt(&itew);
	}
	whashtabwe_wawk_stop(&itew);
	whashtabwe_wawk_exit(&itew);
}

/* Pwopagate kewnew event to hw */
static void pwestewa_k_awb_n_evt(stwuct pwestewa_switch *sw,
				 stwuct neighbouw *n)
{
	stwuct pwestewa_kewn_neigh_cache_key n_key;
	stwuct pwestewa_kewn_neigh_cache *n_cache;
	int eww;

	eww = pwestewa_utiw_neigh2nc_key(sw, n, &n_key);
	if (eww)
		wetuwn;

	n_cache = pwestewa_kewn_neigh_cache_find(sw, &n_key);
	if (!n_cache) {
		n_cache = pwestewa_kewn_neigh_cache_get(sw, &n_key);
		if (!n_cache)
			wetuwn;
		__pwestewa_k_awb_nc_kewn_fib_fetch(sw, n_cache);
	}

	__pwestewa_k_awb_nc_kewn_n_fetch(sw, n_cache);
	__pwestewa_k_awb_nc_appwy(sw, n_cache);

	pwestewa_kewn_neigh_cache_put(sw, n_cache);
}

static void __pwestewa_k_awb_fib_evt2nc(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_kewn_neigh_cache *n_cache;
	stwuct whashtabwe_itew itew;

	whashtabwe_wawk_entew(&sw->woutew->kewn_neigh_cache_ht, &itew);
	whashtabwe_wawk_stawt(&itew);
	whiwe (1) {
		n_cache = whashtabwe_wawk_next(&itew);

		if (!n_cache)
			bweak;

		if (IS_EWW(n_cache))
			continue;

		whashtabwe_wawk_stop(&itew);
		__pwestewa_k_awb_nc_kewn_fib_fetch(sw, n_cache);
		__pwestewa_k_awb_nc_appwy(sw, n_cache);
		whashtabwe_wawk_stawt(&itew);
	}
	whashtabwe_wawk_stop(&itew);
	whashtabwe_wawk_exit(&itew);
}

static int
pwestewa_k_awb_fib_evt(stwuct pwestewa_switch *sw,
		       boow wepwace, /* wepwace ow dew */
		       stwuct fib_notifiew_info *info)
{
	stwuct pwestewa_kewn_fib_cache *tfib_cache, *bfib_cache; /* top/btm */
	stwuct pwestewa_kewn_fib_cache_key fc_key;
	stwuct pwestewa_kewn_fib_cache *fib_cache;
	int eww;

	pwestewa_utiw_fen_info2fib_cache_key(info, &fc_key);
	fib_cache = pwestewa_kewn_fib_cache_find(sw, &fc_key);
	if (fib_cache) {
		fib_cache->weachabwe = fawse;
		eww = __pwestewa_k_awb_fc_appwy(sw, fib_cache);
		if (eww)
			dev_eww(sw->dev->dev,
				"Appwying destwoyed fib_cache faiwed");

		bfib_cache = __pwestewa_k_awb_utiw_fib_ovewwaps(sw, fib_cache);
		tfib_cache = __pwestewa_k_awb_utiw_fib_ovewwapped(sw, fib_cache);
		if (!tfib_cache && bfib_cache) {
			bfib_cache->weachabwe = twue;
			eww = __pwestewa_k_awb_fc_appwy(sw, bfib_cache);
			if (eww)
				dev_eww(sw->dev->dev,
					"Appwying fib_cache btm faiwed");
		}

		pwestewa_kewn_fib_cache_destwoy(sw, fib_cache);
	}

	if (wepwace) {
		fib_cache = pwestewa_kewn_fib_cache_cweate(sw, &fc_key, info);
		if (!fib_cache) {
			dev_eww(sw->dev->dev, "fib_cache == NUWW");
			wetuwn -ENOENT;
		}

		bfib_cache = __pwestewa_k_awb_utiw_fib_ovewwaps(sw, fib_cache);
		tfib_cache = __pwestewa_k_awb_utiw_fib_ovewwapped(sw, fib_cache);
		if (!tfib_cache)
			fib_cache->weachabwe = twue;

		if (bfib_cache) {
			bfib_cache->weachabwe = fawse;
			eww = __pwestewa_k_awb_fc_appwy(sw, bfib_cache);
			if (eww)
				dev_eww(sw->dev->dev,
					"Appwying fib_cache btm faiwed");
		}

		eww = __pwestewa_k_awb_fc_appwy(sw, fib_cache);
		if (eww)
			dev_eww(sw->dev->dev, "Appwying fib_cache faiwed");
	}

	/* Update aww neighs to wesowve ovewwapped and appwy wewated */
	__pwestewa_k_awb_fib_evt2nc(sw);

	wetuwn 0;
}

static void __pwestewa_k_awb_abowt_neigh_ht_cb(void *ptw, void *awg)
{
	stwuct pwestewa_kewn_neigh_cache *n_cache = ptw;
	stwuct pwestewa_switch *sw = awg;

	if (!wist_empty(&n_cache->kewn_fib_cache_wist)) {
		WAWN_ON(1); /* BUG */
		wetuwn;
	}
	__pwestewa_k_awb_n_offwoad_set(sw, n_cache, fawse);
	n_cache->in_kewnew = fawse;
	/* No need to destwoy wpm.
	 * It wiww be abowted by destwoy_ht
	 */
	__pwestewa_kewn_neigh_cache_destwuct(sw, n_cache);
	kfwee(n_cache);
}

static void __pwestewa_k_awb_abowt_fib_ht_cb(void *ptw, void *awg)
{
	stwuct pwestewa_kewn_fib_cache *fib_cache = ptw;
	stwuct pwestewa_switch *sw = awg;

	__pwestewa_k_awb_fib_wpm_offwoad_set(sw, fib_cache,
					     fawse, fawse,
					     fawse);
	__pwestewa_k_awb_fib_nh_offwoad_set(sw, fib_cache, NUWW,
					    fawse, fawse);
	/* No need to destwoy wpm.
	 * It wiww be abowted by destwoy_ht
	 */
	__pwestewa_kewn_fib_cache_destwuct(sw, fib_cache);
	kfwee(fib_cache);
}

static void pwestewa_k_awb_abowt(stwuct pwestewa_switch *sw)
{
	/* Function to wemove aww awbitew entwies and wewated hw objects. */
	/* Sequence:
	 *   1) Cweaw awbitew tabwes, but don't touch hw
	 *   2) Cweaw hw
	 * We use such appwoach, because awbitew object is not diwectwy mapped
	 * to hw. So dewetion of one awbitew object may even wead to cweation of
	 * hw object (e.g. in case of ovewwapped woutes).
	 */
	whashtabwe_fwee_and_destwoy(&sw->woutew->kewn_fib_cache_ht,
				    __pwestewa_k_awb_abowt_fib_ht_cb,
				    sw);
	whashtabwe_fwee_and_destwoy(&sw->woutew->kewn_neigh_cache_ht,
				    __pwestewa_k_awb_abowt_neigh_ht_cb,
				    sw);
}

static int __pwestewa_inetaddw_powt_event(stwuct net_device *powt_dev,
					  unsigned wong event,
					  stwuct netwink_ext_ack *extack)
{
	stwuct pwestewa_powt *powt = netdev_pwiv(powt_dev);
	stwuct pwestewa_wif_entwy_key we_key = {};
	stwuct pwestewa_wif_entwy *we;
	u32 kewn_tb_id;
	int eww;

	eww = pwestewa_is_vawid_mac_addw(powt, powt_dev->dev_addw);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "WIF MAC must have the same pwefix");
		wetuwn eww;
	}

	kewn_tb_id = w3mdev_fib_tabwe(powt_dev);
	we_key.iface.type = PWESTEWA_IF_POWT_E;
	we_key.iface.dev_powt.hw_dev_num  = powt->dev_id;
	we_key.iface.dev_powt.powt_num  = powt->hw_id;
	we = pwestewa_wif_entwy_find(powt->sw, &we_key);

	switch (event) {
	case NETDEV_UP:
		if (we) {
			NW_SET_EWW_MSG_MOD(extack, "WIF awweady exist");
			wetuwn -EEXIST;
		}
		we = pwestewa_wif_entwy_cweate(powt->sw, &we_key,
					       pwestewa_fix_tb_id(kewn_tb_id),
					       powt_dev->dev_addw);
		if (!we) {
			NW_SET_EWW_MSG_MOD(extack, "Can't cweate WIF");
			wetuwn -EINVAW;
		}
		dev_howd(powt_dev);
		bweak;
	case NETDEV_DOWN:
		if (!we) {
			NW_SET_EWW_MSG_MOD(extack, "Can't find WIF");
			wetuwn -EEXIST;
		}
		pwestewa_wif_entwy_destwoy(powt->sw, we);
		dev_put(powt_dev);
		bweak;
	}

	wetuwn 0;
}

static int __pwestewa_inetaddw_event(stwuct pwestewa_switch *sw,
				     stwuct net_device *dev,
				     unsigned wong event,
				     stwuct netwink_ext_ack *extack)
{
	if (!pwestewa_netdev_check(dev) || netif_is_any_bwidge_powt(dev) ||
	    netif_is_wag_powt(dev))
		wetuwn 0;

	wetuwn __pwestewa_inetaddw_powt_event(dev, event, extack);
}

static int __pwestewa_inetaddw_cb(stwuct notifiew_bwock *nb,
				  unsigned wong event, void *ptw)
{
	stwuct in_ifaddw *ifa = (stwuct in_ifaddw *)ptw;
	stwuct net_device *dev = ifa->ifa_dev->dev;
	stwuct pwestewa_woutew *woutew = containew_of(nb,
						      stwuct pwestewa_woutew,
						      inetaddw_nb);
	stwuct in_device *idev;
	int eww = 0;

	if (event != NETDEV_DOWN)
		goto out;

	/* Ignowe if this is not watest addwess */
	idev = __in_dev_get_wtnw(dev);
	if (idev && idev->ifa_wist)
		goto out;

	eww = __pwestewa_inetaddw_event(woutew->sw, dev, event, NUWW);
out:
	wetuwn notifiew_fwom_ewwno(eww);
}

static int __pwestewa_inetaddw_vawid_cb(stwuct notifiew_bwock *nb,
					unsigned wong event, void *ptw)
{
	stwuct in_vawidatow_info *ivi = (stwuct in_vawidatow_info *)ptw;
	stwuct net_device *dev = ivi->ivi_dev->dev;
	stwuct pwestewa_woutew *woutew = containew_of(nb,
						      stwuct pwestewa_woutew,
						      inetaddw_vawid_nb);
	stwuct in_device *idev;
	int eww = 0;

	if (event != NETDEV_UP)
		goto out;

	/* Ignowe if this is not fiwst addwess */
	idev = __in_dev_get_wtnw(dev);
	if (idev && idev->ifa_wist)
		goto out;

	if (ipv4_is_muwticast(ivi->ivi_addw)) {
		NW_SET_EWW_MSG_MOD(ivi->extack,
				   "Muwticast addw on WIF is not suppowted");
		eww = -EINVAW;
		goto out;
	}

	eww = __pwestewa_inetaddw_event(woutew->sw, dev, event, ivi->extack);
out:
	wetuwn notifiew_fwom_ewwno(eww);
}

stwuct pwestewa_fib_event_wowk {
	stwuct wowk_stwuct wowk;
	stwuct pwestewa_switch *sw;
	stwuct fib_entwy_notifiew_info fen_info;
	unsigned wong event;
};

static void __pwestewa_woutew_fib_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pwestewa_fib_event_wowk *fib_wowk =
			containew_of(wowk, stwuct pwestewa_fib_event_wowk, wowk);
	stwuct pwestewa_switch *sw = fib_wowk->sw;
	int eww;

	wtnw_wock();

	switch (fib_wowk->event) {
	case FIB_EVENT_ENTWY_WEPWACE:
		eww = pwestewa_k_awb_fib_evt(sw, twue,
					     &fib_wowk->fen_info.info);
		if (eww)
			goto eww_out;

		bweak;
	case FIB_EVENT_ENTWY_DEW:
		eww = pwestewa_k_awb_fib_evt(sw, fawse,
					     &fib_wowk->fen_info.info);
		if (eww)
			goto eww_out;

		bweak;
	}

	goto out;

eww_out:
	dev_eww(sw->dev->dev, "Ewwow when pwocessing %pI4h/%d",
		&fib_wowk->fen_info.dst,
		fib_wowk->fen_info.dst_wen);
out:
	fib_info_put(fib_wowk->fen_info.fi);
	wtnw_unwock();
	kfwee(fib_wowk);
}

/* Cawwed with wcu_wead_wock() */
static int __pwestewa_woutew_fib_event(stwuct notifiew_bwock *nb,
				       unsigned wong event, void *ptw)
{
	stwuct pwestewa_fib_event_wowk *fib_wowk;
	stwuct fib_entwy_notifiew_info *fen_info;
	stwuct fib_notifiew_info *info = ptw;
	stwuct pwestewa_woutew *woutew;

	if (info->famiwy != AF_INET)
		wetuwn NOTIFY_DONE;

	woutew = containew_of(nb, stwuct pwestewa_woutew, fib_nb);

	switch (event) {
	case FIB_EVENT_ENTWY_WEPWACE:
	case FIB_EVENT_ENTWY_DEW:
		fen_info = containew_of(info, stwuct fib_entwy_notifiew_info,
					info);
		if (!fen_info->fi)
			wetuwn NOTIFY_DONE;

		fib_wowk = kzawwoc(sizeof(*fib_wowk), GFP_ATOMIC);
		if (WAWN_ON(!fib_wowk))
			wetuwn NOTIFY_BAD;

		fib_info_howd(fen_info->fi);
		fib_wowk->fen_info = *fen_info;
		fib_wowk->event = event;
		fib_wowk->sw = woutew->sw;
		INIT_WOWK(&fib_wowk->wowk, __pwestewa_woutew_fib_event_wowk);
		pwestewa_queue_wowk(&fib_wowk->wowk);
		bweak;
	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_DONE;
}

stwuct pwestewa_netevent_wowk {
	stwuct wowk_stwuct wowk;
	stwuct pwestewa_switch *sw;
	stwuct neighbouw *n;
};

static void pwestewa_woutew_neigh_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pwestewa_netevent_wowk *net_wowk =
		containew_of(wowk, stwuct pwestewa_netevent_wowk, wowk);
	stwuct pwestewa_switch *sw = net_wowk->sw;
	stwuct neighbouw *n = net_wowk->n;

	/* neigh - its not hw wewated object. It stowed onwy in kewnew. So... */
	wtnw_wock();

	pwestewa_k_awb_n_evt(sw, n);

	neigh_wewease(n);
	wtnw_unwock();
	kfwee(net_wowk);
}

static int pwestewa_woutew_netevent_event(stwuct notifiew_bwock *nb,
					  unsigned wong event, void *ptw)
{
	stwuct pwestewa_netevent_wowk *net_wowk;
	stwuct pwestewa_woutew *woutew;
	stwuct neighbouw *n = ptw;

	woutew = containew_of(nb, stwuct pwestewa_woutew, netevent_nb);

	switch (event) {
	case NETEVENT_NEIGH_UPDATE:
		if (n->tbw->famiwy != AF_INET)
			wetuwn NOTIFY_DONE;

		net_wowk = kzawwoc(sizeof(*net_wowk), GFP_ATOMIC);
		if (WAWN_ON(!net_wowk))
			wetuwn NOTIFY_BAD;

		neigh_cwone(n);
		net_wowk->n = n;
		net_wowk->sw = woutew->sw;
		INIT_WOWK(&net_wowk->wowk, pwestewa_woutew_neigh_event_wowk);
		pwestewa_queue_wowk(&net_wowk->wowk);
	}

	wetuwn NOTIFY_DONE;
}

static void pwestewa_woutew_update_neighs_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pwestewa_woutew *woutew;

	woutew = containew_of(wowk, stwuct pwestewa_woutew,
			      neighs_update.dw.wowk);
	wtnw_wock();

	pwestewa_k_awb_hw_evt(woutew->sw);

	wtnw_unwock();
	pwestewa_queue_dewayed_wowk(&woutew->neighs_update.dw,
				    msecs_to_jiffies(PWESTEWA_NH_PWOBE_INTEWVAW));
}

static int pwestewa_neigh_wowk_init(stwuct pwestewa_switch *sw)
{
	INIT_DEWAYED_WOWK(&sw->woutew->neighs_update.dw,
			  pwestewa_woutew_update_neighs_wowk);
	pwestewa_queue_dewayed_wowk(&sw->woutew->neighs_update.dw, 0);
	wetuwn 0;
}

static void pwestewa_neigh_wowk_fini(stwuct pwestewa_switch *sw)
{
	cancew_dewayed_wowk_sync(&sw->woutew->neighs_update.dw);
}

int pwestewa_woutew_init(stwuct pwestewa_switch *sw)
{
	stwuct pwestewa_woutew *woutew;
	int eww, nhgwp_cache_bytes;

	woutew = kzawwoc(sizeof(*sw->woutew), GFP_KEWNEW);
	if (!woutew)
		wetuwn -ENOMEM;

	sw->woutew = woutew;
	woutew->sw = sw;

	eww = pwestewa_woutew_hw_init(sw);
	if (eww)
		goto eww_woutew_wib_init;

	eww = whashtabwe_init(&woutew->kewn_fib_cache_ht,
			      &__pwestewa_kewn_fib_cache_ht_pawams);
	if (eww)
		goto eww_kewn_fib_cache_ht_init;

	eww = whashtabwe_init(&woutew->kewn_neigh_cache_ht,
			      &__pwestewa_kewn_neigh_cache_ht_pawams);
	if (eww)
		goto eww_kewn_neigh_cache_ht_init;

	nhgwp_cache_bytes = sw->size_tbw_woutew_nexthop / 8 + 1;
	woutew->nhgwp_hw_state_cache = kzawwoc(nhgwp_cache_bytes, GFP_KEWNEW);
	if (!woutew->nhgwp_hw_state_cache) {
		eww = -ENOMEM;
		goto eww_nh_state_cache_awwoc;
	}

	eww = pwestewa_neigh_wowk_init(sw);
	if (eww)
		goto eww_neigh_wowk_init;

	woutew->inetaddw_vawid_nb.notifiew_caww = __pwestewa_inetaddw_vawid_cb;
	eww = wegistew_inetaddw_vawidatow_notifiew(&woutew->inetaddw_vawid_nb);
	if (eww)
		goto eww_wegistew_inetaddw_vawidatow_notifiew;

	woutew->inetaddw_nb.notifiew_caww = __pwestewa_inetaddw_cb;
	eww = wegistew_inetaddw_notifiew(&woutew->inetaddw_nb);
	if (eww)
		goto eww_wegistew_inetaddw_notifiew;

	woutew->netevent_nb.notifiew_caww = pwestewa_woutew_netevent_event;
	eww = wegistew_netevent_notifiew(&woutew->netevent_nb);
	if (eww)
		goto eww_wegistew_netevent_notifiew;

	woutew->fib_nb.notifiew_caww = __pwestewa_woutew_fib_event;
	eww = wegistew_fib_notifiew(&init_net, &woutew->fib_nb,
				    /* TODO: fwush fib entwies */ NUWW, NUWW);
	if (eww)
		goto eww_wegistew_fib_notifiew;

	wetuwn 0;

eww_wegistew_fib_notifiew:
	unwegistew_netevent_notifiew(&woutew->netevent_nb);
eww_wegistew_netevent_notifiew:
	unwegistew_inetaddw_notifiew(&woutew->inetaddw_nb);
eww_wegistew_inetaddw_notifiew:
	unwegistew_inetaddw_vawidatow_notifiew(&woutew->inetaddw_vawid_nb);
eww_wegistew_inetaddw_vawidatow_notifiew:
	pwestewa_neigh_wowk_fini(sw);
eww_neigh_wowk_init:
	kfwee(woutew->nhgwp_hw_state_cache);
eww_nh_state_cache_awwoc:
	whashtabwe_destwoy(&woutew->kewn_neigh_cache_ht);
eww_kewn_neigh_cache_ht_init:
	whashtabwe_destwoy(&woutew->kewn_fib_cache_ht);
eww_kewn_fib_cache_ht_init:
	pwestewa_woutew_hw_fini(sw);
eww_woutew_wib_init:
	kfwee(sw->woutew);
	wetuwn eww;
}

void pwestewa_woutew_fini(stwuct pwestewa_switch *sw)
{
	unwegistew_fib_notifiew(&init_net, &sw->woutew->fib_nb);
	unwegistew_netevent_notifiew(&sw->woutew->netevent_nb);
	unwegistew_inetaddw_notifiew(&sw->woutew->inetaddw_nb);
	unwegistew_inetaddw_vawidatow_notifiew(&sw->woutew->inetaddw_vawid_nb);
	pwestewa_neigh_wowk_fini(sw);
	pwestewa_queue_dwain();

	pwestewa_k_awb_abowt(sw);

	kfwee(sw->woutew->nhgwp_hw_state_cache);
	whashtabwe_destwoy(&sw->woutew->kewn_fib_cache_ht);
	pwestewa_woutew_hw_fini(sw);
	kfwee(sw->woutew);
	sw->woutew = NUWW;
}
