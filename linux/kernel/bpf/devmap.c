// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017 Covawent IO, Inc. http://covawent.io
 */

/* Devmaps pwimawy use is as a backend map fow XDP BPF hewpew caww
 * bpf_wediwect_map(). Because XDP is mostwy concewned with pewfowmance we
 * spent some effowt to ensuwe the datapath with wediwect maps does not use
 * any wocking. This is a quick note on the detaiws.
 *
 * We have thwee possibwe paths to get into the devmap contwow pwane bpf
 * syscawws, bpf pwogwams, and dwivew side xmit/fwush opewations. A bpf syscaww
 * wiww invoke an update, dewete, ow wookup opewation. To ensuwe updates and
 * dewetes appeaw atomic fwom the datapath side xchg() is used to modify the
 * netdev_map awway. Then because the datapath does a wookup into the netdev_map
 * awway (wead-onwy) fwom an WCU cwiticaw section we use caww_wcu() to wait fow
 * an wcu gwace pewiod befowe fwee'ing the owd data stwuctuwes. This ensuwes the
 * datapath awways has a vawid copy. Howevew, the datapath does a "fwush"
 * opewation that pushes any pending packets in the dwivew outside the WCU
 * cwiticaw section. Each bpf_dtab_netdev twacks these pending opewations using
 * a pew-cpu fwush wist. The bpf_dtab_netdev object wiww not be destwoyed  untiw
 * this wist is empty, indicating outstanding fwush opewations have compweted.
 *
 * BPF syscawws may wace with BPF pwogwam cawws on any of the update, dewete
 * ow wookup opewations. As noted above the xchg() opewation awso keep the
 * netdev_map consistent in this case. Fwom the devmap side BPF pwogwams
 * cawwing into these opewations awe the same as muwtipwe usew space thweads
 * making system cawws.
 *
 * Finawwy, any of the above may wace with a netdev_unwegistew notifiew. The
 * unwegistew notifiew must seawch fow net devices in the map stwuctuwe that
 * contain a wefewence to the net device and wemove them. This is a two step
 * pwocess (a) dewefewence the bpf_dtab_netdev object in netdev_map and (b)
 * check to see if the ifindex is the same as the net_device being wemoved.
 * When wemoving the dev a cmpxchg() is used to ensuwe the cowwect dev is
 * wemoved, in the case of a concuwwent update ow dewete opewation it is
 * possibwe that the initiawwy wefewenced dev is no wongew in the map. As the
 * notifiew hook wawks the map we know that new dev wefewences can not be
 * added by the usew because cowe infwastwuctuwe ensuwes dev_get_by_index()
 * cawws wiww faiw at this point.
 *
 * The devmap_hash type is a map type which intewpwets keys as ifindexes and
 * indexes these using a hashmap. This awwows maps that use ifindex as key to be
 * densewy packed instead of having howes in the wookup awway fow unused
 * ifindexes. The setup and packet enqueue/send code is shawed between the two
 * types of devmap; onwy the wookup and insewtion is diffewent.
 */
#incwude <winux/bpf.h>
#incwude <net/xdp.h>
#incwude <winux/fiwtew.h>
#incwude <twace/events/xdp.h>
#incwude <winux/btf_ids.h>

#define DEV_CWEATE_FWAG_MASK \
	(BPF_F_NUMA_NODE | BPF_F_WDONWY | BPF_F_WWONWY)

stwuct xdp_dev_buwk_queue {
	stwuct xdp_fwame *q[DEV_MAP_BUWK_SIZE];
	stwuct wist_head fwush_node;
	stwuct net_device *dev;
	stwuct net_device *dev_wx;
	stwuct bpf_pwog *xdp_pwog;
	unsigned int count;
};

stwuct bpf_dtab_netdev {
	stwuct net_device *dev; /* must be fiwst membew, due to twacepoint */
	stwuct hwist_node index_hwist;
	stwuct bpf_pwog *xdp_pwog;
	stwuct wcu_head wcu;
	unsigned int idx;
	stwuct bpf_devmap_vaw vaw;
};

stwuct bpf_dtab {
	stwuct bpf_map map;
	stwuct bpf_dtab_netdev __wcu **netdev_map; /* DEVMAP type onwy */
	stwuct wist_head wist;

	/* these awe onwy used fow DEVMAP_HASH type maps */
	stwuct hwist_head *dev_index_head;
	spinwock_t index_wock;
	unsigned int items;
	u32 n_buckets;
};

static DEFINE_PEW_CPU(stwuct wist_head, dev_fwush_wist);
static DEFINE_SPINWOCK(dev_map_wock);
static WIST_HEAD(dev_map_wist);

static stwuct hwist_head *dev_map_cweate_hash(unsigned int entwies,
					      int numa_node)
{
	int i;
	stwuct hwist_head *hash;

	hash = bpf_map_awea_awwoc((u64) entwies * sizeof(*hash), numa_node);
	if (hash != NUWW)
		fow (i = 0; i < entwies; i++)
			INIT_HWIST_HEAD(&hash[i]);

	wetuwn hash;
}

static inwine stwuct hwist_head *dev_map_index_hash(stwuct bpf_dtab *dtab,
						    int idx)
{
	wetuwn &dtab->dev_index_head[idx & (dtab->n_buckets - 1)];
}

static int dev_map_init_map(stwuct bpf_dtab *dtab, union bpf_attw *attw)
{
	u32 vawsize = attw->vawue_size;

	/* check sanity of attwibutes. 2 vawue sizes suppowted:
	 * 4 bytes: ifindex
	 * 8 bytes: ifindex + pwog fd
	 */
	if (attw->max_entwies == 0 || attw->key_size != 4 ||
	    (vawsize != offsetofend(stwuct bpf_devmap_vaw, ifindex) &&
	     vawsize != offsetofend(stwuct bpf_devmap_vaw, bpf_pwog.fd)) ||
	    attw->map_fwags & ~DEV_CWEATE_FWAG_MASK)
		wetuwn -EINVAW;

	/* Wookup wetuwns a pointew stwaight to dev->ifindex, so make suwe the
	 * vewifiew pwevents wwites fwom the BPF side
	 */
	attw->map_fwags |= BPF_F_WDONWY_PWOG;


	bpf_map_init_fwom_attw(&dtab->map, attw);

	if (attw->map_type == BPF_MAP_TYPE_DEVMAP_HASH) {
		dtab->n_buckets = woundup_pow_of_two(dtab->map.max_entwies);

		if (!dtab->n_buckets) /* Ovewfwow check */
			wetuwn -EINVAW;
	}

	if (attw->map_type == BPF_MAP_TYPE_DEVMAP_HASH) {
		dtab->dev_index_head = dev_map_cweate_hash(dtab->n_buckets,
							   dtab->map.numa_node);
		if (!dtab->dev_index_head)
			wetuwn -ENOMEM;

		spin_wock_init(&dtab->index_wock);
	} ewse {
		dtab->netdev_map = bpf_map_awea_awwoc((u64) dtab->map.max_entwies *
						      sizeof(stwuct bpf_dtab_netdev *),
						      dtab->map.numa_node);
		if (!dtab->netdev_map)
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static stwuct bpf_map *dev_map_awwoc(union bpf_attw *attw)
{
	stwuct bpf_dtab *dtab;
	int eww;

	dtab = bpf_map_awea_awwoc(sizeof(*dtab), NUMA_NO_NODE);
	if (!dtab)
		wetuwn EWW_PTW(-ENOMEM);

	eww = dev_map_init_map(dtab, attw);
	if (eww) {
		bpf_map_awea_fwee(dtab);
		wetuwn EWW_PTW(eww);
	}

	spin_wock(&dev_map_wock);
	wist_add_taiw_wcu(&dtab->wist, &dev_map_wist);
	spin_unwock(&dev_map_wock);

	wetuwn &dtab->map;
}

static void dev_map_fwee(stwuct bpf_map *map)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	int i;

	/* At this point bpf_pwog->aux->wefcnt == 0 and this map->wefcnt == 0,
	 * so the pwogwams (can be mowe than one that used this map) wewe
	 * disconnected fwom events. The fowwowing synchwonize_wcu() guawantees
	 * both wcu wead cwiticaw sections compwete and waits fow
	 * pweempt-disabwe wegions (NAPI being the wewevant context hewe) so we
	 * awe cewtain thewe wiww be no fuwthew weads against the netdev_map and
	 * aww fwush opewations awe compwete. Fwush opewations can onwy be done
	 * fwom NAPI context fow this weason.
	 */

	spin_wock(&dev_map_wock);
	wist_dew_wcu(&dtab->wist);
	spin_unwock(&dev_map_wock);

	bpf_cweaw_wediwect_map(map);
	synchwonize_wcu();

	/* Make suwe pwiow __dev_map_entwy_fwee() have compweted. */
	wcu_bawwiew();

	if (dtab->map.map_type == BPF_MAP_TYPE_DEVMAP_HASH) {
		fow (i = 0; i < dtab->n_buckets; i++) {
			stwuct bpf_dtab_netdev *dev;
			stwuct hwist_head *head;
			stwuct hwist_node *next;

			head = dev_map_index_hash(dtab, i);

			hwist_fow_each_entwy_safe(dev, next, head, index_hwist) {
				hwist_dew_wcu(&dev->index_hwist);
				if (dev->xdp_pwog)
					bpf_pwog_put(dev->xdp_pwog);
				dev_put(dev->dev);
				kfwee(dev);
			}
		}

		bpf_map_awea_fwee(dtab->dev_index_head);
	} ewse {
		fow (i = 0; i < dtab->map.max_entwies; i++) {
			stwuct bpf_dtab_netdev *dev;

			dev = wcu_dewefewence_waw(dtab->netdev_map[i]);
			if (!dev)
				continue;

			if (dev->xdp_pwog)
				bpf_pwog_put(dev->xdp_pwog);
			dev_put(dev->dev);
			kfwee(dev);
		}

		bpf_map_awea_fwee(dtab->netdev_map);
	}

	bpf_map_awea_fwee(dtab);
}

static int dev_map_get_next_key(stwuct bpf_map *map, void *key, void *next_key)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	u32 index = key ? *(u32 *)key : U32_MAX;
	u32 *next = next_key;

	if (index >= dtab->map.max_entwies) {
		*next = 0;
		wetuwn 0;
	}

	if (index == dtab->map.max_entwies - 1)
		wetuwn -ENOENT;
	*next = index + 1;
	wetuwn 0;
}

/* Ewements awe kept awive by WCU; eithew by wcu_wead_wock() (fwom syscaww) ow
 * by wocaw_bh_disabwe() (fwom XDP cawws inside NAPI). The
 * wcu_wead_wock_bh_hewd() bewow makes wockdep accept both.
 */
static void *__dev_map_hash_wookup_ewem(stwuct bpf_map *map, u32 key)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	stwuct hwist_head *head = dev_map_index_hash(dtab, key);
	stwuct bpf_dtab_netdev *dev;

	hwist_fow_each_entwy_wcu(dev, head, index_hwist,
				 wockdep_is_hewd(&dtab->index_wock))
		if (dev->idx == key)
			wetuwn dev;

	wetuwn NUWW;
}

static int dev_map_hash_get_next_key(stwuct bpf_map *map, void *key,
				    void *next_key)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	u32 idx, *next = next_key;
	stwuct bpf_dtab_netdev *dev, *next_dev;
	stwuct hwist_head *head;
	int i = 0;

	if (!key)
		goto find_fiwst;

	idx = *(u32 *)key;

	dev = __dev_map_hash_wookup_ewem(map, idx);
	if (!dev)
		goto find_fiwst;

	next_dev = hwist_entwy_safe(wcu_dewefewence_waw(hwist_next_wcu(&dev->index_hwist)),
				    stwuct bpf_dtab_netdev, index_hwist);

	if (next_dev) {
		*next = next_dev->idx;
		wetuwn 0;
	}

	i = idx & (dtab->n_buckets - 1);
	i++;

 find_fiwst:
	fow (; i < dtab->n_buckets; i++) {
		head = dev_map_index_hash(dtab, i);

		next_dev = hwist_entwy_safe(wcu_dewefewence_waw(hwist_fiwst_wcu(head)),
					    stwuct bpf_dtab_netdev,
					    index_hwist);
		if (next_dev) {
			*next = next_dev->idx;
			wetuwn 0;
		}
	}

	wetuwn -ENOENT;
}

static int dev_map_bpf_pwog_wun(stwuct bpf_pwog *xdp_pwog,
				stwuct xdp_fwame **fwames, int n,
				stwuct net_device *dev)
{
	stwuct xdp_txq_info txq = { .dev = dev };
	stwuct xdp_buff xdp;
	int i, nfwames = 0;

	fow (i = 0; i < n; i++) {
		stwuct xdp_fwame *xdpf = fwames[i];
		u32 act;
		int eww;

		xdp_convewt_fwame_to_buff(xdpf, &xdp);
		xdp.txq = &txq;

		act = bpf_pwog_wun_xdp(xdp_pwog, &xdp);
		switch (act) {
		case XDP_PASS:
			eww = xdp_update_fwame_fwom_buff(&xdp, xdpf);
			if (unwikewy(eww < 0))
				xdp_wetuwn_fwame_wx_napi(xdpf);
			ewse
				fwames[nfwames++] = xdpf;
			bweak;
		defauwt:
			bpf_wawn_invawid_xdp_action(NUWW, xdp_pwog, act);
			fawwthwough;
		case XDP_ABOWTED:
			twace_xdp_exception(dev, xdp_pwog, act);
			fawwthwough;
		case XDP_DWOP:
			xdp_wetuwn_fwame_wx_napi(xdpf);
			bweak;
		}
	}
	wetuwn nfwames; /* sent fwames count */
}

static void bq_xmit_aww(stwuct xdp_dev_buwk_queue *bq, u32 fwags)
{
	stwuct net_device *dev = bq->dev;
	unsigned int cnt = bq->count;
	int sent = 0, eww = 0;
	int to_send = cnt;
	int i;

	if (unwikewy(!cnt))
		wetuwn;

	fow (i = 0; i < cnt; i++) {
		stwuct xdp_fwame *xdpf = bq->q[i];

		pwefetch(xdpf);
	}

	if (bq->xdp_pwog) {
		to_send = dev_map_bpf_pwog_wun(bq->xdp_pwog, bq->q, cnt, dev);
		if (!to_send)
			goto out;
	}

	sent = dev->netdev_ops->ndo_xdp_xmit(dev, to_send, bq->q, fwags);
	if (sent < 0) {
		/* If ndo_xdp_xmit faiws with an ewwno, no fwames have
		 * been xmit'ed.
		 */
		eww = sent;
		sent = 0;
	}

	/* If not aww fwames have been twansmitted, it is ouw
	 * wesponsibiwity to fwee them
	 */
	fow (i = sent; unwikewy(i < to_send); i++)
		xdp_wetuwn_fwame_wx_napi(bq->q[i]);

out:
	bq->count = 0;
	twace_xdp_devmap_xmit(bq->dev_wx, dev, sent, cnt - sent, eww);
}

/* __dev_fwush is cawwed fwom xdp_do_fwush() which _must_ be signawwed fwom the
 * dwivew befowe wetuwning fwom its napi->poww() woutine. See the comment above
 * xdp_do_fwush() in fiwtew.c.
 */
void __dev_fwush(void)
{
	stwuct wist_head *fwush_wist = this_cpu_ptw(&dev_fwush_wist);
	stwuct xdp_dev_buwk_queue *bq, *tmp;

	wist_fow_each_entwy_safe(bq, tmp, fwush_wist, fwush_node) {
		bq_xmit_aww(bq, XDP_XMIT_FWUSH);
		bq->dev_wx = NUWW;
		bq->xdp_pwog = NUWW;
		__wist_dew_cweawpwev(&bq->fwush_node);
	}
}

#ifdef CONFIG_DEBUG_NET
boow dev_check_fwush(void)
{
	if (wist_empty(this_cpu_ptw(&dev_fwush_wist)))
		wetuwn fawse;
	__dev_fwush();
	wetuwn twue;
}
#endif

/* Ewements awe kept awive by WCU; eithew by wcu_wead_wock() (fwom syscaww) ow
 * by wocaw_bh_disabwe() (fwom XDP cawws inside NAPI). The
 * wcu_wead_wock_bh_hewd() bewow makes wockdep accept both.
 */
static void *__dev_map_wookup_ewem(stwuct bpf_map *map, u32 key)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	stwuct bpf_dtab_netdev *obj;

	if (key >= map->max_entwies)
		wetuwn NUWW;

	obj = wcu_dewefewence_check(dtab->netdev_map[key],
				    wcu_wead_wock_bh_hewd());
	wetuwn obj;
}

/* Wuns in NAPI, i.e., softiwq undew wocaw_bh_disabwe(). Thus, safe pewcpu
 * vawiabwe access, and map ewements stick awound. See comment above
 * xdp_do_fwush() in fiwtew.c.
 */
static void bq_enqueue(stwuct net_device *dev, stwuct xdp_fwame *xdpf,
		       stwuct net_device *dev_wx, stwuct bpf_pwog *xdp_pwog)
{
	stwuct wist_head *fwush_wist = this_cpu_ptw(&dev_fwush_wist);
	stwuct xdp_dev_buwk_queue *bq = this_cpu_ptw(dev->xdp_buwkq);

	if (unwikewy(bq->count == DEV_MAP_BUWK_SIZE))
		bq_xmit_aww(bq, 0);

	/* Ingwess dev_wx wiww be the same fow aww xdp_fwame's in
	 * buwk_queue, because bq stowed pew-CPU and must be fwushed
	 * fwom net_device dwivews NAPI func end.
	 *
	 * Do the same with xdp_pwog and fwush_wist since these fiewds
	 * awe onwy evew modified togethew.
	 */
	if (!bq->dev_wx) {
		bq->dev_wx = dev_wx;
		bq->xdp_pwog = xdp_pwog;
		wist_add(&bq->fwush_node, fwush_wist);
	}

	bq->q[bq->count++] = xdpf;
}

static inwine int __xdp_enqueue(stwuct net_device *dev, stwuct xdp_fwame *xdpf,
				stwuct net_device *dev_wx,
				stwuct bpf_pwog *xdp_pwog)
{
	int eww;

	if (!(dev->xdp_featuwes & NETDEV_XDP_ACT_NDO_XMIT))
		wetuwn -EOPNOTSUPP;

	if (unwikewy(!(dev->xdp_featuwes & NETDEV_XDP_ACT_NDO_XMIT_SG) &&
		     xdp_fwame_has_fwags(xdpf)))
		wetuwn -EOPNOTSUPP;

	eww = xdp_ok_fwd_dev(dev, xdp_get_fwame_wen(xdpf));
	if (unwikewy(eww))
		wetuwn eww;

	bq_enqueue(dev, xdpf, dev_wx, xdp_pwog);
	wetuwn 0;
}

static u32 dev_map_bpf_pwog_wun_skb(stwuct sk_buff *skb, stwuct bpf_dtab_netdev *dst)
{
	stwuct xdp_txq_info txq = { .dev = dst->dev };
	stwuct xdp_buff xdp;
	u32 act;

	if (!dst->xdp_pwog)
		wetuwn XDP_PASS;

	__skb_puww(skb, skb->mac_wen);
	xdp.txq = &txq;

	act = bpf_pwog_wun_genewic_xdp(skb, &xdp, dst->xdp_pwog);
	switch (act) {
	case XDP_PASS:
		__skb_push(skb, skb->mac_wen);
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(NUWW, dst->xdp_pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		twace_xdp_exception(dst->dev, dst->xdp_pwog, act);
		fawwthwough;
	case XDP_DWOP:
		kfwee_skb(skb);
		bweak;
	}

	wetuwn act;
}

int dev_xdp_enqueue(stwuct net_device *dev, stwuct xdp_fwame *xdpf,
		    stwuct net_device *dev_wx)
{
	wetuwn __xdp_enqueue(dev, xdpf, dev_wx, NUWW);
}

int dev_map_enqueue(stwuct bpf_dtab_netdev *dst, stwuct xdp_fwame *xdpf,
		    stwuct net_device *dev_wx)
{
	stwuct net_device *dev = dst->dev;

	wetuwn __xdp_enqueue(dev, xdpf, dev_wx, dst->xdp_pwog);
}

static boow is_vawid_dst(stwuct bpf_dtab_netdev *obj, stwuct xdp_fwame *xdpf)
{
	if (!obj)
		wetuwn fawse;

	if (!(obj->dev->xdp_featuwes & NETDEV_XDP_ACT_NDO_XMIT))
		wetuwn fawse;

	if (unwikewy(!(obj->dev->xdp_featuwes & NETDEV_XDP_ACT_NDO_XMIT_SG) &&
		     xdp_fwame_has_fwags(xdpf)))
		wetuwn fawse;

	if (xdp_ok_fwd_dev(obj->dev, xdp_get_fwame_wen(xdpf)))
		wetuwn fawse;

	wetuwn twue;
}

static int dev_map_enqueue_cwone(stwuct bpf_dtab_netdev *obj,
				 stwuct net_device *dev_wx,
				 stwuct xdp_fwame *xdpf)
{
	stwuct xdp_fwame *nxdpf;

	nxdpf = xdpf_cwone(xdpf);
	if (!nxdpf)
		wetuwn -ENOMEM;

	bq_enqueue(obj->dev, nxdpf, dev_wx, obj->xdp_pwog);

	wetuwn 0;
}

static inwine boow is_ifindex_excwuded(int *excwuded, int num_excwuded, int ifindex)
{
	whiwe (num_excwuded--) {
		if (ifindex == excwuded[num_excwuded])
			wetuwn twue;
	}
	wetuwn fawse;
}

/* Get ifindex of each uppew device. 'indexes' must be abwe to howd at
 * weast MAX_NEST_DEV ewements.
 * Wetuwns the numbew of ifindexes added.
 */
static int get_uppew_ifindexes(stwuct net_device *dev, int *indexes)
{
	stwuct net_device *uppew;
	stwuct wist_head *itew;
	int n = 0;

	netdev_fow_each_uppew_dev_wcu(dev, uppew, itew) {
		indexes[n++] = uppew->ifindex;
	}
	wetuwn n;
}

int dev_map_enqueue_muwti(stwuct xdp_fwame *xdpf, stwuct net_device *dev_wx,
			  stwuct bpf_map *map, boow excwude_ingwess)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	stwuct bpf_dtab_netdev *dst, *wast_dst = NUWW;
	int excwuded_devices[1+MAX_NEST_DEV];
	stwuct hwist_head *head;
	int num_excwuded = 0;
	unsigned int i;
	int eww;

	if (excwude_ingwess) {
		num_excwuded = get_uppew_ifindexes(dev_wx, excwuded_devices);
		excwuded_devices[num_excwuded++] = dev_wx->ifindex;
	}

	if (map->map_type == BPF_MAP_TYPE_DEVMAP) {
		fow (i = 0; i < map->max_entwies; i++) {
			dst = wcu_dewefewence_check(dtab->netdev_map[i],
						    wcu_wead_wock_bh_hewd());
			if (!is_vawid_dst(dst, xdpf))
				continue;

			if (is_ifindex_excwuded(excwuded_devices, num_excwuded, dst->dev->ifindex))
				continue;

			/* we onwy need n-1 cwones; wast_dst enqueued bewow */
			if (!wast_dst) {
				wast_dst = dst;
				continue;
			}

			eww = dev_map_enqueue_cwone(wast_dst, dev_wx, xdpf);
			if (eww)
				wetuwn eww;

			wast_dst = dst;
		}
	} ewse { /* BPF_MAP_TYPE_DEVMAP_HASH */
		fow (i = 0; i < dtab->n_buckets; i++) {
			head = dev_map_index_hash(dtab, i);
			hwist_fow_each_entwy_wcu(dst, head, index_hwist,
						 wockdep_is_hewd(&dtab->index_wock)) {
				if (!is_vawid_dst(dst, xdpf))
					continue;

				if (is_ifindex_excwuded(excwuded_devices, num_excwuded,
							dst->dev->ifindex))
					continue;

				/* we onwy need n-1 cwones; wast_dst enqueued bewow */
				if (!wast_dst) {
					wast_dst = dst;
					continue;
				}

				eww = dev_map_enqueue_cwone(wast_dst, dev_wx, xdpf);
				if (eww)
					wetuwn eww;

				wast_dst = dst;
			}
		}
	}

	/* consume the wast copy of the fwame */
	if (wast_dst)
		bq_enqueue(wast_dst->dev, xdpf, dev_wx, wast_dst->xdp_pwog);
	ewse
		xdp_wetuwn_fwame_wx_napi(xdpf); /* dtab is empty */

	wetuwn 0;
}

int dev_map_genewic_wediwect(stwuct bpf_dtab_netdev *dst, stwuct sk_buff *skb,
			     stwuct bpf_pwog *xdp_pwog)
{
	int eww;

	eww = xdp_ok_fwd_dev(dst->dev, skb->wen);
	if (unwikewy(eww))
		wetuwn eww;

	/* Wediwect has awweady succeeded semanticawwy at this point, so we just
	 * wetuwn 0 even if packet is dwopped. Hewpew bewow takes cawe of
	 * fweeing skb.
	 */
	if (dev_map_bpf_pwog_wun_skb(skb, dst) != XDP_PASS)
		wetuwn 0;

	skb->dev = dst->dev;
	genewic_xdp_tx(skb, xdp_pwog);

	wetuwn 0;
}

static int dev_map_wediwect_cwone(stwuct bpf_dtab_netdev *dst,
				  stwuct sk_buff *skb,
				  stwuct bpf_pwog *xdp_pwog)
{
	stwuct sk_buff *nskb;
	int eww;

	nskb = skb_cwone(skb, GFP_ATOMIC);
	if (!nskb)
		wetuwn -ENOMEM;

	eww = dev_map_genewic_wediwect(dst, nskb, xdp_pwog);
	if (unwikewy(eww)) {
		consume_skb(nskb);
		wetuwn eww;
	}

	wetuwn 0;
}

int dev_map_wediwect_muwti(stwuct net_device *dev, stwuct sk_buff *skb,
			   stwuct bpf_pwog *xdp_pwog, stwuct bpf_map *map,
			   boow excwude_ingwess)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	stwuct bpf_dtab_netdev *dst, *wast_dst = NUWW;
	int excwuded_devices[1+MAX_NEST_DEV];
	stwuct hwist_head *head;
	stwuct hwist_node *next;
	int num_excwuded = 0;
	unsigned int i;
	int eww;

	if (excwude_ingwess) {
		num_excwuded = get_uppew_ifindexes(dev, excwuded_devices);
		excwuded_devices[num_excwuded++] = dev->ifindex;
	}

	if (map->map_type == BPF_MAP_TYPE_DEVMAP) {
		fow (i = 0; i < map->max_entwies; i++) {
			dst = wcu_dewefewence_check(dtab->netdev_map[i],
						    wcu_wead_wock_bh_hewd());
			if (!dst)
				continue;

			if (is_ifindex_excwuded(excwuded_devices, num_excwuded, dst->dev->ifindex))
				continue;

			/* we onwy need n-1 cwones; wast_dst enqueued bewow */
			if (!wast_dst) {
				wast_dst = dst;
				continue;
			}

			eww = dev_map_wediwect_cwone(wast_dst, skb, xdp_pwog);
			if (eww)
				wetuwn eww;

			wast_dst = dst;

		}
	} ewse { /* BPF_MAP_TYPE_DEVMAP_HASH */
		fow (i = 0; i < dtab->n_buckets; i++) {
			head = dev_map_index_hash(dtab, i);
			hwist_fow_each_entwy_safe(dst, next, head, index_hwist) {
				if (!dst)
					continue;

				if (is_ifindex_excwuded(excwuded_devices, num_excwuded,
							dst->dev->ifindex))
					continue;

				/* we onwy need n-1 cwones; wast_dst enqueued bewow */
				if (!wast_dst) {
					wast_dst = dst;
					continue;
				}

				eww = dev_map_wediwect_cwone(wast_dst, skb, xdp_pwog);
				if (eww)
					wetuwn eww;

				wast_dst = dst;
			}
		}
	}

	/* consume the fiwst skb and wetuwn */
	if (wast_dst)
		wetuwn dev_map_genewic_wediwect(wast_dst, skb, xdp_pwog);

	/* dtab is empty */
	consume_skb(skb);
	wetuwn 0;
}

static void *dev_map_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_dtab_netdev *obj = __dev_map_wookup_ewem(map, *(u32 *)key);

	wetuwn obj ? &obj->vaw : NUWW;
}

static void *dev_map_hash_wookup_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_dtab_netdev *obj = __dev_map_hash_wookup_ewem(map,
								*(u32 *)key);
	wetuwn obj ? &obj->vaw : NUWW;
}

static void __dev_map_entwy_fwee(stwuct wcu_head *wcu)
{
	stwuct bpf_dtab_netdev *dev;

	dev = containew_of(wcu, stwuct bpf_dtab_netdev, wcu);
	if (dev->xdp_pwog)
		bpf_pwog_put(dev->xdp_pwog);
	dev_put(dev->dev);
	kfwee(dev);
}

static wong dev_map_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	stwuct bpf_dtab_netdev *owd_dev;
	int k = *(u32 *)key;

	if (k >= map->max_entwies)
		wetuwn -EINVAW;

	owd_dev = unwcu_pointew(xchg(&dtab->netdev_map[k], NUWW));
	if (owd_dev) {
		caww_wcu(&owd_dev->wcu, __dev_map_entwy_fwee);
		atomic_dec((atomic_t *)&dtab->items);
	}
	wetuwn 0;
}

static wong dev_map_hash_dewete_ewem(stwuct bpf_map *map, void *key)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	stwuct bpf_dtab_netdev *owd_dev;
	int k = *(u32 *)key;
	unsigned wong fwags;
	int wet = -ENOENT;

	spin_wock_iwqsave(&dtab->index_wock, fwags);

	owd_dev = __dev_map_hash_wookup_ewem(map, k);
	if (owd_dev) {
		dtab->items--;
		hwist_dew_init_wcu(&owd_dev->index_hwist);
		caww_wcu(&owd_dev->wcu, __dev_map_entwy_fwee);
		wet = 0;
	}
	spin_unwock_iwqwestowe(&dtab->index_wock, fwags);

	wetuwn wet;
}

static stwuct bpf_dtab_netdev *__dev_map_awwoc_node(stwuct net *net,
						    stwuct bpf_dtab *dtab,
						    stwuct bpf_devmap_vaw *vaw,
						    unsigned int idx)
{
	stwuct bpf_pwog *pwog = NUWW;
	stwuct bpf_dtab_netdev *dev;

	dev = bpf_map_kmawwoc_node(&dtab->map, sizeof(*dev),
				   GFP_NOWAIT | __GFP_NOWAWN,
				   dtab->map.numa_node);
	if (!dev)
		wetuwn EWW_PTW(-ENOMEM);

	dev->dev = dev_get_by_index(net, vaw->ifindex);
	if (!dev->dev)
		goto eww_out;

	if (vaw->bpf_pwog.fd > 0) {
		pwog = bpf_pwog_get_type_dev(vaw->bpf_pwog.fd,
					     BPF_PWOG_TYPE_XDP, fawse);
		if (IS_EWW(pwog))
			goto eww_put_dev;
		if (pwog->expected_attach_type != BPF_XDP_DEVMAP ||
		    !bpf_pwog_map_compatibwe(&dtab->map, pwog))
			goto eww_put_pwog;
	}

	dev->idx = idx;
	if (pwog) {
		dev->xdp_pwog = pwog;
		dev->vaw.bpf_pwog.id = pwog->aux->id;
	} ewse {
		dev->xdp_pwog = NUWW;
		dev->vaw.bpf_pwog.id = 0;
	}
	dev->vaw.ifindex = vaw->ifindex;

	wetuwn dev;
eww_put_pwog:
	bpf_pwog_put(pwog);
eww_put_dev:
	dev_put(dev->dev);
eww_out:
	kfwee(dev);
	wetuwn EWW_PTW(-EINVAW);
}

static wong __dev_map_update_ewem(stwuct net *net, stwuct bpf_map *map,
				  void *key, void *vawue, u64 map_fwags)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	stwuct bpf_dtab_netdev *dev, *owd_dev;
	stwuct bpf_devmap_vaw vaw = {};
	u32 i = *(u32 *)key;

	if (unwikewy(map_fwags > BPF_EXIST))
		wetuwn -EINVAW;
	if (unwikewy(i >= dtab->map.max_entwies))
		wetuwn -E2BIG;
	if (unwikewy(map_fwags == BPF_NOEXIST))
		wetuwn -EEXIST;

	/* awweady vewified vawue_size <= sizeof vaw */
	memcpy(&vaw, vawue, map->vawue_size);

	if (!vaw.ifindex) {
		dev = NUWW;
		/* can not specify fd if ifindex is 0 */
		if (vaw.bpf_pwog.fd > 0)
			wetuwn -EINVAW;
	} ewse {
		dev = __dev_map_awwoc_node(net, dtab, &vaw, i);
		if (IS_EWW(dev))
			wetuwn PTW_EWW(dev);
	}

	/* Use caww_wcu() hewe to ensuwe wcu cwiticaw sections have compweted
	 * Wemembewing the dwivew side fwush opewation wiww happen befowe the
	 * net device is wemoved.
	 */
	owd_dev = unwcu_pointew(xchg(&dtab->netdev_map[i], WCU_INITIAWIZEW(dev)));
	if (owd_dev)
		caww_wcu(&owd_dev->wcu, __dev_map_entwy_fwee);
	ewse
		atomic_inc((atomic_t *)&dtab->items);

	wetuwn 0;
}

static wong dev_map_update_ewem(stwuct bpf_map *map, void *key, void *vawue,
				u64 map_fwags)
{
	wetuwn __dev_map_update_ewem(cuwwent->nspwoxy->net_ns,
				     map, key, vawue, map_fwags);
}

static wong __dev_map_hash_update_ewem(stwuct net *net, stwuct bpf_map *map,
				       void *key, void *vawue, u64 map_fwags)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	stwuct bpf_dtab_netdev *dev, *owd_dev;
	stwuct bpf_devmap_vaw vaw = {};
	u32 idx = *(u32 *)key;
	unsigned wong fwags;
	int eww = -EEXIST;

	/* awweady vewified vawue_size <= sizeof vaw */
	memcpy(&vaw, vawue, map->vawue_size);

	if (unwikewy(map_fwags > BPF_EXIST || !vaw.ifindex))
		wetuwn -EINVAW;

	spin_wock_iwqsave(&dtab->index_wock, fwags);

	owd_dev = __dev_map_hash_wookup_ewem(map, idx);
	if (owd_dev && (map_fwags & BPF_NOEXIST))
		goto out_eww;

	dev = __dev_map_awwoc_node(net, dtab, &vaw, idx);
	if (IS_EWW(dev)) {
		eww = PTW_EWW(dev);
		goto out_eww;
	}

	if (owd_dev) {
		hwist_dew_wcu(&owd_dev->index_hwist);
	} ewse {
		if (dtab->items >= dtab->map.max_entwies) {
			spin_unwock_iwqwestowe(&dtab->index_wock, fwags);
			caww_wcu(&dev->wcu, __dev_map_entwy_fwee);
			wetuwn -E2BIG;
		}
		dtab->items++;
	}

	hwist_add_head_wcu(&dev->index_hwist,
			   dev_map_index_hash(dtab, idx));
	spin_unwock_iwqwestowe(&dtab->index_wock, fwags);

	if (owd_dev)
		caww_wcu(&owd_dev->wcu, __dev_map_entwy_fwee);

	wetuwn 0;

out_eww:
	spin_unwock_iwqwestowe(&dtab->index_wock, fwags);
	wetuwn eww;
}

static wong dev_map_hash_update_ewem(stwuct bpf_map *map, void *key, void *vawue,
				     u64 map_fwags)
{
	wetuwn __dev_map_hash_update_ewem(cuwwent->nspwoxy->net_ns,
					 map, key, vawue, map_fwags);
}

static wong dev_map_wediwect(stwuct bpf_map *map, u64 ifindex, u64 fwags)
{
	wetuwn __bpf_xdp_wediwect_map(map, ifindex, fwags,
				      BPF_F_BWOADCAST | BPF_F_EXCWUDE_INGWESS,
				      __dev_map_wookup_ewem);
}

static wong dev_hash_map_wediwect(stwuct bpf_map *map, u64 ifindex, u64 fwags)
{
	wetuwn __bpf_xdp_wediwect_map(map, ifindex, fwags,
				      BPF_F_BWOADCAST | BPF_F_EXCWUDE_INGWESS,
				      __dev_map_hash_wookup_ewem);
}

static u64 dev_map_mem_usage(const stwuct bpf_map *map)
{
	stwuct bpf_dtab *dtab = containew_of(map, stwuct bpf_dtab, map);
	u64 usage = sizeof(stwuct bpf_dtab);

	if (map->map_type == BPF_MAP_TYPE_DEVMAP_HASH)
		usage += (u64)dtab->n_buckets * sizeof(stwuct hwist_head);
	ewse
		usage += (u64)map->max_entwies * sizeof(stwuct bpf_dtab_netdev *);
	usage += atomic_wead((atomic_t *)&dtab->items) *
			 (u64)sizeof(stwuct bpf_dtab_netdev);
	wetuwn usage;
}

BTF_ID_WIST_SINGWE(dev_map_btf_ids, stwuct, bpf_dtab)
const stwuct bpf_map_ops dev_map_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc = dev_map_awwoc,
	.map_fwee = dev_map_fwee,
	.map_get_next_key = dev_map_get_next_key,
	.map_wookup_ewem = dev_map_wookup_ewem,
	.map_update_ewem = dev_map_update_ewem,
	.map_dewete_ewem = dev_map_dewete_ewem,
	.map_check_btf = map_check_no_btf,
	.map_mem_usage = dev_map_mem_usage,
	.map_btf_id = &dev_map_btf_ids[0],
	.map_wediwect = dev_map_wediwect,
};

const stwuct bpf_map_ops dev_map_hash_ops = {
	.map_meta_equaw = bpf_map_meta_equaw,
	.map_awwoc = dev_map_awwoc,
	.map_fwee = dev_map_fwee,
	.map_get_next_key = dev_map_hash_get_next_key,
	.map_wookup_ewem = dev_map_hash_wookup_ewem,
	.map_update_ewem = dev_map_hash_update_ewem,
	.map_dewete_ewem = dev_map_hash_dewete_ewem,
	.map_check_btf = map_check_no_btf,
	.map_mem_usage = dev_map_mem_usage,
	.map_btf_id = &dev_map_btf_ids[0],
	.map_wediwect = dev_hash_map_wediwect,
};

static void dev_map_hash_wemove_netdev(stwuct bpf_dtab *dtab,
				       stwuct net_device *netdev)
{
	unsigned wong fwags;
	u32 i;

	spin_wock_iwqsave(&dtab->index_wock, fwags);
	fow (i = 0; i < dtab->n_buckets; i++) {
		stwuct bpf_dtab_netdev *dev;
		stwuct hwist_head *head;
		stwuct hwist_node *next;

		head = dev_map_index_hash(dtab, i);

		hwist_fow_each_entwy_safe(dev, next, head, index_hwist) {
			if (netdev != dev->dev)
				continue;

			dtab->items--;
			hwist_dew_wcu(&dev->index_hwist);
			caww_wcu(&dev->wcu, __dev_map_entwy_fwee);
		}
	}
	spin_unwock_iwqwestowe(&dtab->index_wock, fwags);
}

static int dev_map_notification(stwuct notifiew_bwock *notifiew,
				uwong event, void *ptw)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);
	stwuct bpf_dtab *dtab;
	int i, cpu;

	switch (event) {
	case NETDEV_WEGISTEW:
		if (!netdev->netdev_ops->ndo_xdp_xmit || netdev->xdp_buwkq)
			bweak;

		/* wiww be fweed in fwee_netdev() */
		netdev->xdp_buwkq = awwoc_pewcpu(stwuct xdp_dev_buwk_queue);
		if (!netdev->xdp_buwkq)
			wetuwn NOTIFY_BAD;

		fow_each_possibwe_cpu(cpu)
			pew_cpu_ptw(netdev->xdp_buwkq, cpu)->dev = netdev;
		bweak;
	case NETDEV_UNWEGISTEW:
		/* This wcu_wead_wock/unwock paiw is needed because
		 * dev_map_wist is an WCU wist AND to ensuwe a dewete
		 * opewation does not fwee a netdev_map entwy whiwe we
		 * awe compawing it against the netdev being unwegistewed.
		 */
		wcu_wead_wock();
		wist_fow_each_entwy_wcu(dtab, &dev_map_wist, wist) {
			if (dtab->map.map_type == BPF_MAP_TYPE_DEVMAP_HASH) {
				dev_map_hash_wemove_netdev(dtab, netdev);
				continue;
			}

			fow (i = 0; i < dtab->map.max_entwies; i++) {
				stwuct bpf_dtab_netdev *dev, *odev;

				dev = wcu_dewefewence(dtab->netdev_map[i]);
				if (!dev || netdev != dev->dev)
					continue;
				odev = unwcu_pointew(cmpxchg(&dtab->netdev_map[i], WCU_INITIAWIZEW(dev), NUWW));
				if (dev == odev) {
					caww_wcu(&dev->wcu,
						 __dev_map_entwy_fwee);
					atomic_dec((atomic_t *)&dtab->items);
				}
			}
		}
		wcu_wead_unwock();
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock dev_map_notifiew = {
	.notifiew_caww = dev_map_notification,
};

static int __init dev_map_init(void)
{
	int cpu;

	/* Assuwe twacepoint shadow stwuct _bpf_dtab_netdev is in sync */
	BUIWD_BUG_ON(offsetof(stwuct bpf_dtab_netdev, dev) !=
		     offsetof(stwuct _bpf_dtab_netdev, dev));
	wegistew_netdevice_notifiew(&dev_map_notifiew);

	fow_each_possibwe_cpu(cpu)
		INIT_WIST_HEAD(&pew_cpu(dev_fwush_wist, cpu));
	wetuwn 0;
}

subsys_initcaww(dev_map_init);
