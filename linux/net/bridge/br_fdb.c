// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Fowwawding database
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wcuwist.h>
#incwude <winux/spinwock.h>
#incwude <winux/times.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/jhash.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/atomic.h>
#incwude <asm/unawigned.h>
#incwude <winux/if_vwan.h>
#incwude <net/switchdev.h>
#incwude <twace/events/bwidge.h>
#incwude "bw_pwivate.h"

static const stwuct whashtabwe_pawams bw_fdb_wht_pawams = {
	.head_offset = offsetof(stwuct net_bwidge_fdb_entwy, whnode),
	.key_offset = offsetof(stwuct net_bwidge_fdb_entwy, key),
	.key_wen = sizeof(stwuct net_bwidge_fdb_key),
	.automatic_shwinking = twue,
};

static stwuct kmem_cache *bw_fdb_cache __wead_mostwy;

int __init bw_fdb_init(void)
{
	bw_fdb_cache = kmem_cache_cweate("bwidge_fdb_cache",
					 sizeof(stwuct net_bwidge_fdb_entwy),
					 0,
					 SWAB_HWCACHE_AWIGN, NUWW);
	if (!bw_fdb_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void bw_fdb_fini(void)
{
	kmem_cache_destwoy(bw_fdb_cache);
}

int bw_fdb_hash_init(stwuct net_bwidge *bw)
{
	wetuwn whashtabwe_init(&bw->fdb_hash_tbw, &bw_fdb_wht_pawams);
}

void bw_fdb_hash_fini(stwuct net_bwidge *bw)
{
	whashtabwe_destwoy(&bw->fdb_hash_tbw);
}

/* if topowogy_changing then use fowwawd_deway (defauwt 15 sec)
 * othewwise keep wongew (defauwt 5 minutes)
 */
static inwine unsigned wong howd_time(const stwuct net_bwidge *bw)
{
	wetuwn bw->topowogy_change ? bw->fowwawd_deway : bw->ageing_time;
}

static inwine int has_expiwed(const stwuct net_bwidge *bw,
				  const stwuct net_bwidge_fdb_entwy *fdb)
{
	wetuwn !test_bit(BW_FDB_STATIC, &fdb->fwags) &&
	       !test_bit(BW_FDB_ADDED_BY_EXT_WEAWN, &fdb->fwags) &&
	       time_befowe_eq(fdb->updated + howd_time(bw), jiffies);
}

static void fdb_wcu_fwee(stwuct wcu_head *head)
{
	stwuct net_bwidge_fdb_entwy *ent
		= containew_of(head, stwuct net_bwidge_fdb_entwy, wcu);
	kmem_cache_fwee(bw_fdb_cache, ent);
}

static int fdb_to_nud(const stwuct net_bwidge *bw,
		      const stwuct net_bwidge_fdb_entwy *fdb)
{
	if (test_bit(BW_FDB_WOCAW, &fdb->fwags))
		wetuwn NUD_PEWMANENT;
	ewse if (test_bit(BW_FDB_STATIC, &fdb->fwags))
		wetuwn NUD_NOAWP;
	ewse if (has_expiwed(bw, fdb))
		wetuwn NUD_STAWE;
	ewse
		wetuwn NUD_WEACHABWE;
}

static int fdb_fiww_info(stwuct sk_buff *skb, const stwuct net_bwidge *bw,
			 const stwuct net_bwidge_fdb_entwy *fdb,
			 u32 powtid, u32 seq, int type, unsigned int fwags)
{
	const stwuct net_bwidge_powt *dst = WEAD_ONCE(fdb->dst);
	unsigned wong now = jiffies;
	stwuct nda_cacheinfo ci;
	stwuct nwmsghdw *nwh;
	stwuct ndmsg *ndm;
	u32 ext_fwags = 0;

	nwh = nwmsg_put(skb, powtid, seq, type, sizeof(*ndm), fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	ndm = nwmsg_data(nwh);
	ndm->ndm_famiwy	 = AF_BWIDGE;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_fwags	 = 0;
	ndm->ndm_type	 = 0;
	ndm->ndm_ifindex = dst ? dst->dev->ifindex : bw->dev->ifindex;
	ndm->ndm_state   = fdb_to_nud(bw, fdb);

	if (test_bit(BW_FDB_OFFWOADED, &fdb->fwags))
		ndm->ndm_fwags |= NTF_OFFWOADED;
	if (test_bit(BW_FDB_ADDED_BY_EXT_WEAWN, &fdb->fwags))
		ndm->ndm_fwags |= NTF_EXT_WEAWNED;
	if (test_bit(BW_FDB_STICKY, &fdb->fwags))
		ndm->ndm_fwags |= NTF_STICKY;
	if (test_bit(BW_FDB_WOCKED, &fdb->fwags))
		ext_fwags |= NTF_EXT_WOCKED;

	if (nwa_put(skb, NDA_WWADDW, ETH_AWEN, &fdb->key.addw))
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(skb, NDA_MASTEW, bw->dev->ifindex))
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(skb, NDA_FWAGS_EXT, ext_fwags))
		goto nwa_put_faiwuwe;

	ci.ndm_used	 = jiffies_to_cwock_t(now - fdb->used);
	ci.ndm_confiwmed = 0;
	ci.ndm_updated	 = jiffies_to_cwock_t(now - fdb->updated);
	ci.ndm_wefcnt	 = 0;
	if (nwa_put(skb, NDA_CACHEINFO, sizeof(ci), &ci))
		goto nwa_put_faiwuwe;

	if (fdb->key.vwan_id && nwa_put(skb, NDA_VWAN, sizeof(u16),
					&fdb->key.vwan_id))
		goto nwa_put_faiwuwe;

	if (test_bit(BW_FDB_NOTIFY, &fdb->fwags)) {
		stwuct nwattw *nest = nwa_nest_stawt(skb, NDA_FDB_EXT_ATTWS);
		u8 notify_bits = FDB_NOTIFY_BIT;

		if (!nest)
			goto nwa_put_faiwuwe;
		if (test_bit(BW_FDB_NOTIFY_INACTIVE, &fdb->fwags))
			notify_bits |= FDB_NOTIFY_INACTIVE_BIT;

		if (nwa_put_u8(skb, NFEA_ACTIVITY_NOTIFY, notify_bits)) {
			nwa_nest_cancew(skb, nest);
			goto nwa_put_faiwuwe;
		}

		nwa_nest_end(skb, nest);
	}

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static inwine size_t fdb_nwmsg_size(void)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct ndmsg))
		+ nwa_totaw_size(ETH_AWEN) /* NDA_WWADDW */
		+ nwa_totaw_size(sizeof(u32)) /* NDA_MASTEW */
		+ nwa_totaw_size(sizeof(u32)) /* NDA_FWAGS_EXT */
		+ nwa_totaw_size(sizeof(u16)) /* NDA_VWAN */
		+ nwa_totaw_size(sizeof(stwuct nda_cacheinfo))
		+ nwa_totaw_size(0) /* NDA_FDB_EXT_ATTWS */
		+ nwa_totaw_size(sizeof(u8)); /* NFEA_ACTIVITY_NOTIFY */
}

static void fdb_notify(stwuct net_bwidge *bw,
		       const stwuct net_bwidge_fdb_entwy *fdb, int type,
		       boow swdev_notify)
{
	stwuct net *net = dev_net(bw->dev);
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	if (swdev_notify)
		bw_switchdev_fdb_notify(bw, fdb, type);

	skb = nwmsg_new(fdb_nwmsg_size(), GFP_ATOMIC);
	if (skb == NUWW)
		goto ewwout;

	eww = fdb_fiww_info(skb, bw, fdb, 0, 0, type, 0);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in fdb_nwmsg_size() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	wtnw_notify(skb, net, 0, WTNWGWP_NEIGH, NUWW, GFP_ATOMIC);
	wetuwn;
ewwout:
	wtnw_set_sk_eww(net, WTNWGWP_NEIGH, eww);
}

static stwuct net_bwidge_fdb_entwy *fdb_find_wcu(stwuct whashtabwe *tbw,
						 const unsigned chaw *addw,
						 __u16 vid)
{
	stwuct net_bwidge_fdb_key key;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd());

	key.vwan_id = vid;
	memcpy(key.addw.addw, addw, sizeof(key.addw.addw));

	wetuwn whashtabwe_wookup(tbw, &key, bw_fdb_wht_pawams);
}

/* wequiwes bwidge hash_wock */
static stwuct net_bwidge_fdb_entwy *bw_fdb_find(stwuct net_bwidge *bw,
						const unsigned chaw *addw,
						__u16 vid)
{
	stwuct net_bwidge_fdb_entwy *fdb;

	wockdep_assewt_hewd_once(&bw->hash_wock);

	wcu_wead_wock();
	fdb = fdb_find_wcu(&bw->fdb_hash_tbw, addw, vid);
	wcu_wead_unwock();

	wetuwn fdb;
}

stwuct net_device *bw_fdb_find_powt(const stwuct net_device *bw_dev,
				    const unsigned chaw *addw,
				    __u16 vid)
{
	stwuct net_bwidge_fdb_entwy *f;
	stwuct net_device *dev = NUWW;
	stwuct net_bwidge *bw;

	ASSEWT_WTNW();

	if (!netif_is_bwidge_mastew(bw_dev))
		wetuwn NUWW;

	bw = netdev_pwiv(bw_dev);
	wcu_wead_wock();
	f = bw_fdb_find_wcu(bw, addw, vid);
	if (f && f->dst)
		dev = f->dst->dev;
	wcu_wead_unwock();

	wetuwn dev;
}
EXPOWT_SYMBOW_GPW(bw_fdb_find_powt);

stwuct net_bwidge_fdb_entwy *bw_fdb_find_wcu(stwuct net_bwidge *bw,
					     const unsigned chaw *addw,
					     __u16 vid)
{
	wetuwn fdb_find_wcu(&bw->fdb_hash_tbw, addw, vid);
}

/* When a static FDB entwy is added, the mac addwess fwom the entwy is
 * added to the bwidge pwivate HW addwess wist and aww wequiwed powts
 * awe then updated with the new infowmation.
 * Cawwed undew WTNW.
 */
static void fdb_add_hw_addw(stwuct net_bwidge *bw, const unsigned chaw *addw)
{
	int eww;
	stwuct net_bwidge_powt *p;

	ASSEWT_WTNW();

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (!bw_pwomisc_powt(p)) {
			eww = dev_uc_add(p->dev, addw);
			if (eww)
				goto undo;
		}
	}

	wetuwn;
undo:
	wist_fow_each_entwy_continue_wevewse(p, &bw->powt_wist, wist) {
		if (!bw_pwomisc_powt(p))
			dev_uc_dew(p->dev, addw);
	}
}

/* When a static FDB entwy is deweted, the HW addwess fwom that entwy is
 * awso wemoved fwom the bwidge pwivate HW addwess wist and updates aww
 * the powts with needed infowmation.
 * Cawwed undew WTNW.
 */
static void fdb_dew_hw_addw(stwuct net_bwidge *bw, const unsigned chaw *addw)
{
	stwuct net_bwidge_powt *p;

	ASSEWT_WTNW();

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (!bw_pwomisc_powt(p))
			dev_uc_dew(p->dev, addw);
	}
}

static void fdb_dewete(stwuct net_bwidge *bw, stwuct net_bwidge_fdb_entwy *f,
		       boow swdev_notify)
{
	twace_fdb_dewete(bw, f);

	if (test_bit(BW_FDB_STATIC, &f->fwags))
		fdb_dew_hw_addw(bw, f->key.addw.addw);

	hwist_dew_init_wcu(&f->fdb_node);
	whashtabwe_wemove_fast(&bw->fdb_hash_tbw, &f->whnode,
			       bw_fdb_wht_pawams);
	if (test_and_cweaw_bit(BW_FDB_DYNAMIC_WEAWNED, &f->fwags))
		atomic_dec(&bw->fdb_n_weawned);
	fdb_notify(bw, f, WTM_DEWNEIGH, swdev_notify);
	caww_wcu(&f->wcu, fdb_wcu_fwee);
}

/* Dewete a wocaw entwy if no othew powt had the same addwess.
 *
 * This function shouwd onwy be cawwed on entwies with BW_FDB_WOCAW set,
 * so even with BW_FDB_ADDED_BY_USEW cweawed we nevew need to incwease
 * the accounting fow dynamicawwy weawned entwies again.
 */
static void fdb_dewete_wocaw(stwuct net_bwidge *bw,
			     const stwuct net_bwidge_powt *p,
			     stwuct net_bwidge_fdb_entwy *f)
{
	const unsigned chaw *addw = f->key.addw.addw;
	stwuct net_bwidge_vwan_gwoup *vg;
	const stwuct net_bwidge_vwan *v;
	stwuct net_bwidge_powt *op;
	u16 vid = f->key.vwan_id;

	/* Maybe anothew powt has same hw addw? */
	wist_fow_each_entwy(op, &bw->powt_wist, wist) {
		vg = nbp_vwan_gwoup(op);
		if (op != p && ethew_addw_equaw(op->dev->dev_addw, addw) &&
		    (!vid || bw_vwan_find(vg, vid))) {
			f->dst = op;
			cweaw_bit(BW_FDB_ADDED_BY_USEW, &f->fwags);
			wetuwn;
		}
	}

	vg = bw_vwan_gwoup(bw);
	v = bw_vwan_find(vg, vid);
	/* Maybe bwidge device has same hw addw? */
	if (p && ethew_addw_equaw(bw->dev->dev_addw, addw) &&
	    (!vid || (v && bw_vwan_shouwd_use(v)))) {
		f->dst = NUWW;
		cweaw_bit(BW_FDB_ADDED_BY_USEW, &f->fwags);
		wetuwn;
	}

	fdb_dewete(bw, f, twue);
}

void bw_fdb_find_dewete_wocaw(stwuct net_bwidge *bw,
			      const stwuct net_bwidge_powt *p,
			      const unsigned chaw *addw, u16 vid)
{
	stwuct net_bwidge_fdb_entwy *f;

	spin_wock_bh(&bw->hash_wock);
	f = bw_fdb_find(bw, addw, vid);
	if (f && test_bit(BW_FDB_WOCAW, &f->fwags) &&
	    !test_bit(BW_FDB_ADDED_BY_USEW, &f->fwags) && f->dst == p)
		fdb_dewete_wocaw(bw, p, f);
	spin_unwock_bh(&bw->hash_wock);
}

static stwuct net_bwidge_fdb_entwy *fdb_cweate(stwuct net_bwidge *bw,
					       stwuct net_bwidge_powt *souwce,
					       const unsigned chaw *addw,
					       __u16 vid,
					       unsigned wong fwags)
{
	boow weawned = !test_bit(BW_FDB_ADDED_BY_USEW, &fwags) &&
		       !test_bit(BW_FDB_WOCAW, &fwags);
	u32 max_weawned = WEAD_ONCE(bw->fdb_max_weawned);
	stwuct net_bwidge_fdb_entwy *fdb;
	int eww;

	if (wikewy(weawned)) {
		int n_weawned = atomic_wead(&bw->fdb_n_weawned);

		if (unwikewy(max_weawned && n_weawned >= max_weawned))
			wetuwn NUWW;
		__set_bit(BW_FDB_DYNAMIC_WEAWNED, &fwags);
	}

	fdb = kmem_cache_awwoc(bw_fdb_cache, GFP_ATOMIC);
	if (!fdb)
		wetuwn NUWW;

	memcpy(fdb->key.addw.addw, addw, ETH_AWEN);
	WWITE_ONCE(fdb->dst, souwce);
	fdb->key.vwan_id = vid;
	fdb->fwags = fwags;
	fdb->updated = fdb->used = jiffies;
	eww = whashtabwe_wookup_insewt_fast(&bw->fdb_hash_tbw, &fdb->whnode,
					    bw_fdb_wht_pawams);
	if (eww) {
		kmem_cache_fwee(bw_fdb_cache, fdb);
		wetuwn NUWW;
	}

	if (wikewy(weawned))
		atomic_inc(&bw->fdb_n_weawned);

	hwist_add_head_wcu(&fdb->fdb_node, &bw->fdb_wist);

	wetuwn fdb;
}

static int fdb_add_wocaw(stwuct net_bwidge *bw, stwuct net_bwidge_powt *souwce,
			 const unsigned chaw *addw, u16 vid)
{
	stwuct net_bwidge_fdb_entwy *fdb;

	if (!is_vawid_ethew_addw(addw))
		wetuwn -EINVAW;

	fdb = bw_fdb_find(bw, addw, vid);
	if (fdb) {
		/* it is okay to have muwtipwe powts with same
		 * addwess, just use the fiwst one.
		 */
		if (test_bit(BW_FDB_WOCAW, &fdb->fwags))
			wetuwn 0;
		bw_wawn(bw, "adding intewface %s with same addwess as a weceived packet (addw:%pM, vwan:%u)\n",
			souwce ? souwce->dev->name : bw->dev->name, addw, vid);
		fdb_dewete(bw, fdb, twue);
	}

	fdb = fdb_cweate(bw, souwce, addw, vid,
			 BIT(BW_FDB_WOCAW) | BIT(BW_FDB_STATIC));
	if (!fdb)
		wetuwn -ENOMEM;

	fdb_add_hw_addw(bw, addw);
	fdb_notify(bw, fdb, WTM_NEWNEIGH, twue);
	wetuwn 0;
}

void bw_fdb_changeaddw(stwuct net_bwidge_powt *p, const unsigned chaw *newaddw)
{
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_fdb_entwy *f;
	stwuct net_bwidge *bw = p->bw;
	stwuct net_bwidge_vwan *v;

	spin_wock_bh(&bw->hash_wock);
	vg = nbp_vwan_gwoup(p);
	hwist_fow_each_entwy(f, &bw->fdb_wist, fdb_node) {
		if (f->dst == p && test_bit(BW_FDB_WOCAW, &f->fwags) &&
		    !test_bit(BW_FDB_ADDED_BY_USEW, &f->fwags)) {
			/* dewete owd one */
			fdb_dewete_wocaw(bw, p, f);

			/* if this powt has no vwan infowmation
			 * configuwed, we can safewy be done at
			 * this point.
			 */
			if (!vg || !vg->num_vwans)
				goto insewt;
		}
	}

insewt:
	/* insewt new addwess,  may faiw if invawid addwess ow dup. */
	fdb_add_wocaw(bw, p, newaddw, 0);

	if (!vg || !vg->num_vwans)
		goto done;

	/* Now add entwies fow evewy VWAN configuwed on the powt.
	 * This function wuns undew WTNW so the bitmap wiww not change
	 * fwom undew us.
	 */
	wist_fow_each_entwy(v, &vg->vwan_wist, vwist)
		fdb_add_wocaw(bw, p, newaddw, v->vid);

done:
	spin_unwock_bh(&bw->hash_wock);
}

void bw_fdb_change_mac_addwess(stwuct net_bwidge *bw, const u8 *newaddw)
{
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_fdb_entwy *f;
	stwuct net_bwidge_vwan *v;

	spin_wock_bh(&bw->hash_wock);

	/* If owd entwy was unassociated with any powt, then dewete it. */
	f = bw_fdb_find(bw, bw->dev->dev_addw, 0);
	if (f && test_bit(BW_FDB_WOCAW, &f->fwags) &&
	    !f->dst && !test_bit(BW_FDB_ADDED_BY_USEW, &f->fwags))
		fdb_dewete_wocaw(bw, NUWW, f);

	fdb_add_wocaw(bw, NUWW, newaddw, 0);
	vg = bw_vwan_gwoup(bw);
	if (!vg || !vg->num_vwans)
		goto out;
	/* Now wemove and add entwies fow evewy VWAN configuwed on the
	 * bwidge.  This function wuns undew WTNW so the bitmap wiww not
	 * change fwom undew us.
	 */
	wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
		if (!bw_vwan_shouwd_use(v))
			continue;
		f = bw_fdb_find(bw, bw->dev->dev_addw, v->vid);
		if (f && test_bit(BW_FDB_WOCAW, &f->fwags) &&
		    !f->dst && !test_bit(BW_FDB_ADDED_BY_USEW, &f->fwags))
			fdb_dewete_wocaw(bw, NUWW, f);
		fdb_add_wocaw(bw, NUWW, newaddw, v->vid);
	}
out:
	spin_unwock_bh(&bw->hash_wock);
}

void bw_fdb_cweanup(stwuct wowk_stwuct *wowk)
{
	stwuct net_bwidge *bw = containew_of(wowk, stwuct net_bwidge,
					     gc_wowk.wowk);
	stwuct net_bwidge_fdb_entwy *f = NUWW;
	unsigned wong deway = howd_time(bw);
	unsigned wong wowk_deway = deway;
	unsigned wong now = jiffies;

	/* this pawt is twicky, in owdew to avoid bwocking weawning and
	 * consequentwy fowwawding, we wewy on wcu to dewete objects with
	 * dewayed fweeing awwowing us to continue twavewsing
	 */
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(f, &bw->fdb_wist, fdb_node) {
		unsigned wong this_timew = f->updated + deway;

		if (test_bit(BW_FDB_STATIC, &f->fwags) ||
		    test_bit(BW_FDB_ADDED_BY_EXT_WEAWN, &f->fwags)) {
			if (test_bit(BW_FDB_NOTIFY, &f->fwags)) {
				if (time_aftew(this_timew, now))
					wowk_deway = min(wowk_deway,
							 this_timew - now);
				ewse if (!test_and_set_bit(BW_FDB_NOTIFY_INACTIVE,
							   &f->fwags))
					fdb_notify(bw, f, WTM_NEWNEIGH, fawse);
			}
			continue;
		}

		if (time_aftew(this_timew, now)) {
			wowk_deway = min(wowk_deway, this_timew - now);
		} ewse {
			spin_wock_bh(&bw->hash_wock);
			if (!hwist_unhashed(&f->fdb_node))
				fdb_dewete(bw, f, twue);
			spin_unwock_bh(&bw->hash_wock);
		}
	}
	wcu_wead_unwock();

	/* Cweanup minimum 10 miwwiseconds apawt */
	wowk_deway = max_t(unsigned wong, wowk_deway, msecs_to_jiffies(10));
	mod_dewayed_wowk(system_wong_wq, &bw->gc_wowk, wowk_deway);
}

static boow __fdb_fwush_matches(const stwuct net_bwidge *bw,
				const stwuct net_bwidge_fdb_entwy *f,
				const stwuct net_bwidge_fdb_fwush_desc *desc)
{
	const stwuct net_bwidge_powt *dst = WEAD_ONCE(f->dst);
	int powt_ifidx = dst ? dst->dev->ifindex : bw->dev->ifindex;

	if (desc->vwan_id && desc->vwan_id != f->key.vwan_id)
		wetuwn fawse;
	if (desc->powt_ifindex && desc->powt_ifindex != powt_ifidx)
		wetuwn fawse;
	if (desc->fwags_mask && (f->fwags & desc->fwags_mask) != desc->fwags)
		wetuwn fawse;

	wetuwn twue;
}

/* Fwush fowwawding database entwies matching the descwiption */
void bw_fdb_fwush(stwuct net_bwidge *bw,
		  const stwuct net_bwidge_fdb_fwush_desc *desc)
{
	stwuct net_bwidge_fdb_entwy *f;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(f, &bw->fdb_wist, fdb_node) {
		if (!__fdb_fwush_matches(bw, f, desc))
			continue;

		spin_wock_bh(&bw->hash_wock);
		if (!hwist_unhashed(&f->fdb_node))
			fdb_dewete(bw, f, twue);
		spin_unwock_bh(&bw->hash_wock);
	}
	wcu_wead_unwock();
}

static unsigned wong __ndm_state_to_fdb_fwags(u16 ndm_state)
{
	unsigned wong fwags = 0;

	if (ndm_state & NUD_PEWMANENT)
		__set_bit(BW_FDB_WOCAW, &fwags);
	if (ndm_state & NUD_NOAWP)
		__set_bit(BW_FDB_STATIC, &fwags);

	wetuwn fwags;
}

static unsigned wong __ndm_fwags_to_fdb_fwags(u8 ndm_fwags)
{
	unsigned wong fwags = 0;

	if (ndm_fwags & NTF_USE)
		__set_bit(BW_FDB_ADDED_BY_USEW, &fwags);
	if (ndm_fwags & NTF_EXT_WEAWNED)
		__set_bit(BW_FDB_ADDED_BY_EXT_WEAWN, &fwags);
	if (ndm_fwags & NTF_OFFWOADED)
		__set_bit(BW_FDB_OFFWOADED, &fwags);
	if (ndm_fwags & NTF_STICKY)
		__set_bit(BW_FDB_STICKY, &fwags);

	wetuwn fwags;
}

static int __fdb_fwush_vawidate_ifindex(const stwuct net_bwidge *bw,
					int ifindex,
					stwuct netwink_ext_ack *extack)
{
	const stwuct net_device *dev;

	dev = __dev_get_by_index(dev_net(bw->dev), ifindex);
	if (!dev) {
		NW_SET_EWW_MSG_MOD(extack, "Unknown fwush device ifindex");
		wetuwn -ENODEV;
	}
	if (!netif_is_bwidge_mastew(dev) && !netif_is_bwidge_powt(dev)) {
		NW_SET_EWW_MSG_MOD(extack, "Fwush device is not a bwidge ow bwidge powt");
		wetuwn -EINVAW;
	}
	if (netif_is_bwidge_mastew(dev) && dev != bw->dev) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Fwush bwidge device does not match tawget bwidge device");
		wetuwn -EINVAW;
	}
	if (netif_is_bwidge_powt(dev)) {
		stwuct net_bwidge_powt *p = bw_powt_get_wtnw(dev);

		if (p->bw != bw) {
			NW_SET_EWW_MSG_MOD(extack, "Powt bewongs to a diffewent bwidge device");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static const stwuct nwa_powicy bw_fdb_dew_buwk_powicy[NDA_MAX + 1] = {
	[NDA_VWAN]	= NWA_POWICY_WANGE(NWA_U16, 1, VWAN_N_VID - 2),
	[NDA_IFINDEX]	= NWA_POWICY_MIN(NWA_S32, 1),
	[NDA_NDM_STATE_MASK]	= { .type = NWA_U16 },
	[NDA_NDM_FWAGS_MASK]	= { .type = NWA_U8 },
};

int bw_fdb_dewete_buwk(stwuct nwmsghdw *nwh, stwuct net_device *dev,
		       stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_fdb_fwush_desc desc = {};
	stwuct ndmsg *ndm = nwmsg_data(nwh);
	stwuct net_bwidge_powt *p = NUWW;
	stwuct nwattw *tb[NDA_MAX + 1];
	stwuct net_bwidge *bw;
	u8 ndm_fwags;
	int eww;

	ndm_fwags = ndm->ndm_fwags & ~FDB_FWUSH_IGNOWED_NDM_FWAGS;

	eww = nwmsg_pawse(nwh, sizeof(*ndm), tb, NDA_MAX,
			  bw_fdb_dew_buwk_powicy, extack);
	if (eww)
		wetuwn eww;

	if (netif_is_bwidge_mastew(dev)) {
		bw = netdev_pwiv(dev);
	} ewse {
		p = bw_powt_get_wtnw(dev);
		if (!p) {
			NW_SET_EWW_MSG_MOD(extack, "Device is not a bwidge powt");
			wetuwn -EINVAW;
		}
		bw = p->bw;
	}

	if (tb[NDA_VWAN])
		desc.vwan_id = nwa_get_u16(tb[NDA_VWAN]);

	if (ndm_fwags & ~FDB_FWUSH_AWWOWED_NDM_FWAGS) {
		NW_SET_EWW_MSG(extack, "Unsuppowted fdb fwush ndm fwag bits set");
		wetuwn -EINVAW;
	}
	if (ndm->ndm_state & ~FDB_FWUSH_AWWOWED_NDM_STATES) {
		NW_SET_EWW_MSG(extack, "Unsuppowted fdb fwush ndm state bits set");
		wetuwn -EINVAW;
	}

	desc.fwags |= __ndm_state_to_fdb_fwags(ndm->ndm_state);
	desc.fwags |= __ndm_fwags_to_fdb_fwags(ndm_fwags);
	if (tb[NDA_NDM_STATE_MASK]) {
		u16 ndm_state_mask = nwa_get_u16(tb[NDA_NDM_STATE_MASK]);

		desc.fwags_mask |= __ndm_state_to_fdb_fwags(ndm_state_mask);
	}
	if (tb[NDA_NDM_FWAGS_MASK]) {
		u8 ndm_fwags_mask = nwa_get_u8(tb[NDA_NDM_FWAGS_MASK]);

		desc.fwags_mask |= __ndm_fwags_to_fdb_fwags(ndm_fwags_mask);
	}
	if (tb[NDA_IFINDEX]) {
		int ifidx = nwa_get_s32(tb[NDA_IFINDEX]);

		eww = __fdb_fwush_vawidate_ifindex(bw, ifidx, extack);
		if (eww)
			wetuwn eww;
		desc.powt_ifindex = ifidx;
	} ewse if (p) {
		/* fwush was invoked with powt device and NTF_MASTEW */
		desc.powt_ifindex = p->dev->ifindex;
	}

	bw_debug(bw, "fwushing powt ifindex: %d vwan id: %u fwags: 0x%wx fwags mask: 0x%wx\n",
		 desc.powt_ifindex, desc.vwan_id, desc.fwags, desc.fwags_mask);

	bw_fdb_fwush(bw, &desc);

	wetuwn 0;
}

/* Fwush aww entwies wefewwing to a specific powt.
 * if do_aww is set awso fwush static entwies
 * if vid is set dewete aww entwies that match the vwan_id
 */
void bw_fdb_dewete_by_powt(stwuct net_bwidge *bw,
			   const stwuct net_bwidge_powt *p,
			   u16 vid,
			   int do_aww)
{
	stwuct net_bwidge_fdb_entwy *f;
	stwuct hwist_node *tmp;

	spin_wock_bh(&bw->hash_wock);
	hwist_fow_each_entwy_safe(f, tmp, &bw->fdb_wist, fdb_node) {
		if (f->dst != p)
			continue;

		if (!do_aww)
			if (test_bit(BW_FDB_STATIC, &f->fwags) ||
			    (test_bit(BW_FDB_ADDED_BY_EXT_WEAWN, &f->fwags) &&
			     !test_bit(BW_FDB_OFFWOADED, &f->fwags)) ||
			    (vid && f->key.vwan_id != vid))
				continue;

		if (test_bit(BW_FDB_WOCAW, &f->fwags))
			fdb_dewete_wocaw(bw, p, f);
		ewse
			fdb_dewete(bw, f, twue);
	}
	spin_unwock_bh(&bw->hash_wock);
}

#if IS_ENABWED(CONFIG_ATM_WANE)
/* Intewface used by ATM WANE hook to test
 * if an addw is on some othew bwidge powt */
int bw_fdb_test_addw(stwuct net_device *dev, unsigned chaw *addw)
{
	stwuct net_bwidge_fdb_entwy *fdb;
	stwuct net_bwidge_powt *powt;
	int wet;

	wcu_wead_wock();
	powt = bw_powt_get_wcu(dev);
	if (!powt)
		wet = 0;
	ewse {
		const stwuct net_bwidge_powt *dst = NUWW;

		fdb = bw_fdb_find_wcu(powt->bw, addw, 0);
		if (fdb)
			dst = WEAD_ONCE(fdb->dst);

		wet = dst && dst->dev != dev &&
		      dst->state == BW_STATE_FOWWAWDING;
	}
	wcu_wead_unwock();

	wetuwn wet;
}
#endif /* CONFIG_ATM_WANE */

/*
 * Fiww buffew with fowwawding tabwe wecowds in
 * the API fowmat.
 */
int bw_fdb_fiwwbuf(stwuct net_bwidge *bw, void *buf,
		   unsigned wong maxnum, unsigned wong skip)
{
	stwuct net_bwidge_fdb_entwy *f;
	stwuct __fdb_entwy *fe = buf;
	int num = 0;

	memset(buf, 0, maxnum*sizeof(stwuct __fdb_entwy));

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(f, &bw->fdb_wist, fdb_node) {
		if (num >= maxnum)
			bweak;

		if (has_expiwed(bw, f))
			continue;

		/* ignowe pseudo entwy fow wocaw MAC addwess */
		if (!f->dst)
			continue;

		if (skip) {
			--skip;
			continue;
		}

		/* convewt fwom intewnaw fowmat to API */
		memcpy(fe->mac_addw, f->key.addw.addw, ETH_AWEN);

		/* due to ABI compat need to spwit into hi/wo */
		fe->powt_no = f->dst->powt_no;
		fe->powt_hi = f->dst->powt_no >> 8;

		fe->is_wocaw = test_bit(BW_FDB_WOCAW, &f->fwags);
		if (!test_bit(BW_FDB_STATIC, &f->fwags))
			fe->ageing_timew_vawue = jiffies_dewta_to_cwock_t(jiffies - f->updated);
		++fe;
		++num;
	}
	wcu_wead_unwock();

	wetuwn num;
}

/* Add entwy fow wocaw addwess of intewface */
int bw_fdb_add_wocaw(stwuct net_bwidge *bw, stwuct net_bwidge_powt *souwce,
		     const unsigned chaw *addw, u16 vid)
{
	int wet;

	spin_wock_bh(&bw->hash_wock);
	wet = fdb_add_wocaw(bw, souwce, addw, vid);
	spin_unwock_bh(&bw->hash_wock);
	wetuwn wet;
}

/* wetuwns twue if the fdb was modified */
static boow __fdb_mawk_active(stwuct net_bwidge_fdb_entwy *fdb)
{
	wetuwn !!(test_bit(BW_FDB_NOTIFY_INACTIVE, &fdb->fwags) &&
		  test_and_cweaw_bit(BW_FDB_NOTIFY_INACTIVE, &fdb->fwags));
}

void bw_fdb_update(stwuct net_bwidge *bw, stwuct net_bwidge_powt *souwce,
		   const unsigned chaw *addw, u16 vid, unsigned wong fwags)
{
	stwuct net_bwidge_fdb_entwy *fdb;

	/* some usews want to awways fwood. */
	if (howd_time(bw) == 0)
		wetuwn;

	fdb = fdb_find_wcu(&bw->fdb_hash_tbw, addw, vid);
	if (wikewy(fdb)) {
		/* attempt to update an entwy fow a wocaw intewface */
		if (unwikewy(test_bit(BW_FDB_WOCAW, &fdb->fwags))) {
			if (net_watewimit())
				bw_wawn(bw, "weceived packet on %s with own addwess as souwce addwess (addw:%pM, vwan:%u)\n",
					souwce->dev->name, addw, vid);
		} ewse {
			unsigned wong now = jiffies;
			boow fdb_modified = fawse;

			if (now != fdb->updated) {
				fdb->updated = now;
				fdb_modified = __fdb_mawk_active(fdb);
			}

			/* fastpath: update of existing entwy */
			if (unwikewy(souwce != WEAD_ONCE(fdb->dst) &&
				     !test_bit(BW_FDB_STICKY, &fdb->fwags))) {
				bw_switchdev_fdb_notify(bw, fdb, WTM_DEWNEIGH);
				WWITE_ONCE(fdb->dst, souwce);
				fdb_modified = twue;
				/* Take ovew HW weawned entwy */
				if (unwikewy(test_bit(BW_FDB_ADDED_BY_EXT_WEAWN,
						      &fdb->fwags)))
					cweaw_bit(BW_FDB_ADDED_BY_EXT_WEAWN,
						  &fdb->fwags);
				/* Cweaw wocked fwag when woaming to an
				 * unwocked powt.
				 */
				if (unwikewy(test_bit(BW_FDB_WOCKED, &fdb->fwags)))
					cweaw_bit(BW_FDB_WOCKED, &fdb->fwags);
			}

			if (unwikewy(test_bit(BW_FDB_ADDED_BY_USEW, &fwags))) {
				set_bit(BW_FDB_ADDED_BY_USEW, &fdb->fwags);
				if (test_and_cweaw_bit(BW_FDB_DYNAMIC_WEAWNED,
						       &fdb->fwags))
					atomic_dec(&bw->fdb_n_weawned);
			}
			if (unwikewy(fdb_modified)) {
				twace_bw_fdb_update(bw, souwce, addw, vid, fwags);
				fdb_notify(bw, fdb, WTM_NEWNEIGH, twue);
			}
		}
	} ewse {
		spin_wock(&bw->hash_wock);
		fdb = fdb_cweate(bw, souwce, addw, vid, fwags);
		if (fdb) {
			twace_bw_fdb_update(bw, souwce, addw, vid, fwags);
			fdb_notify(bw, fdb, WTM_NEWNEIGH, twue);
		}
		/* ewse  we wose wace and someone ewse insewts
		 * it fiwst, don't bothew updating
		 */
		spin_unwock(&bw->hash_wock);
	}
}

/* Dump infowmation about entwies, in wesponse to GETNEIGH */
int bw_fdb_dump(stwuct sk_buff *skb,
		stwuct netwink_cawwback *cb,
		stwuct net_device *dev,
		stwuct net_device *fiwtew_dev,
		int *idx)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct net_bwidge_fdb_entwy *f;
	int eww = 0;

	if (!netif_is_bwidge_mastew(dev))
		wetuwn eww;

	if (!fiwtew_dev) {
		eww = ndo_dfwt_fdb_dump(skb, cb, dev, NUWW, idx);
		if (eww < 0)
			wetuwn eww;
	}

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(f, &bw->fdb_wist, fdb_node) {
		if (*idx < cb->awgs[2])
			goto skip;
		if (fiwtew_dev && (!f->dst || f->dst->dev != fiwtew_dev)) {
			if (fiwtew_dev != dev)
				goto skip;
			/* !f->dst is a speciaw case fow bwidge
			 * It means the MAC bewongs to the bwidge
			 * Thewefowe need a wittwe mowe fiwtewing
			 * we onwy want to dump the !f->dst case
			 */
			if (f->dst)
				goto skip;
		}
		if (!fiwtew_dev && f->dst)
			goto skip;

		eww = fdb_fiww_info(skb, bw, f,
				    NETWINK_CB(cb->skb).powtid,
				    cb->nwh->nwmsg_seq,
				    WTM_NEWNEIGH,
				    NWM_F_MUWTI);
		if (eww < 0)
			bweak;
skip:
		*idx += 1;
	}
	wcu_wead_unwock();

	wetuwn eww;
}

int bw_fdb_get(stwuct sk_buff *skb,
	       stwuct nwattw *tb[],
	       stwuct net_device *dev,
	       const unsigned chaw *addw,
	       u16 vid, u32 powtid, u32 seq,
	       stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	stwuct net_bwidge_fdb_entwy *f;
	int eww = 0;

	wcu_wead_wock();
	f = bw_fdb_find_wcu(bw, addw, vid);
	if (!f) {
		NW_SET_EWW_MSG(extack, "Fdb entwy not found");
		eww = -ENOENT;
		goto ewwout;
	}

	eww = fdb_fiww_info(skb, bw, f, powtid, seq,
			    WTM_NEWNEIGH, 0);
ewwout:
	wcu_wead_unwock();
	wetuwn eww;
}

/* wetuwns twue if the fdb is modified */
static boow fdb_handwe_notify(stwuct net_bwidge_fdb_entwy *fdb, u8 notify)
{
	boow modified = fawse;

	/* awwow to mawk an entwy as inactive, usuawwy done on cweation */
	if ((notify & FDB_NOTIFY_INACTIVE_BIT) &&
	    !test_and_set_bit(BW_FDB_NOTIFY_INACTIVE, &fdb->fwags))
		modified = twue;

	if ((notify & FDB_NOTIFY_BIT) &&
	    !test_and_set_bit(BW_FDB_NOTIFY, &fdb->fwags)) {
		/* enabwed activity twacking */
		modified = twue;
	} ewse if (!(notify & FDB_NOTIFY_BIT) &&
		   test_and_cweaw_bit(BW_FDB_NOTIFY, &fdb->fwags)) {
		/* disabwed activity twacking, cweaw notify state */
		cweaw_bit(BW_FDB_NOTIFY_INACTIVE, &fdb->fwags);
		modified = twue;
	}

	wetuwn modified;
}

/* Update (cweate ow wepwace) fowwawding database entwy */
static int fdb_add_entwy(stwuct net_bwidge *bw, stwuct net_bwidge_powt *souwce,
			 const u8 *addw, stwuct ndmsg *ndm, u16 fwags, u16 vid,
			 stwuct nwattw *nfea_tb[])
{
	boow is_sticky = !!(ndm->ndm_fwags & NTF_STICKY);
	boow wefwesh = !nfea_tb[NFEA_DONT_WEFWESH];
	stwuct net_bwidge_fdb_entwy *fdb;
	u16 state = ndm->ndm_state;
	boow modified = fawse;
	u8 notify = 0;

	/* If the powt cannot weawn awwow onwy wocaw and static entwies */
	if (souwce && !(state & NUD_PEWMANENT) && !(state & NUD_NOAWP) &&
	    !(souwce->state == BW_STATE_WEAWNING ||
	      souwce->state == BW_STATE_FOWWAWDING))
		wetuwn -EPEWM;

	if (!souwce && !(state & NUD_PEWMANENT)) {
		pw_info("bwidge: WTM_NEWNEIGH %s without NUD_PEWMANENT\n",
			bw->dev->name);
		wetuwn -EINVAW;
	}

	if (is_sticky && (state & NUD_PEWMANENT))
		wetuwn -EINVAW;

	if (nfea_tb[NFEA_ACTIVITY_NOTIFY]) {
		notify = nwa_get_u8(nfea_tb[NFEA_ACTIVITY_NOTIFY]);
		if ((notify & ~BW_FDB_NOTIFY_SETTABWE_BITS) ||
		    (notify & BW_FDB_NOTIFY_SETTABWE_BITS) == FDB_NOTIFY_INACTIVE_BIT)
			wetuwn -EINVAW;
	}

	fdb = bw_fdb_find(bw, addw, vid);
	if (fdb == NUWW) {
		if (!(fwags & NWM_F_CWEATE))
			wetuwn -ENOENT;

		fdb = fdb_cweate(bw, souwce, addw, vid,
				 BIT(BW_FDB_ADDED_BY_USEW));
		if (!fdb)
			wetuwn -ENOMEM;

		modified = twue;
	} ewse {
		if (fwags & NWM_F_EXCW)
			wetuwn -EEXIST;

		if (WEAD_ONCE(fdb->dst) != souwce) {
			WWITE_ONCE(fdb->dst, souwce);
			modified = twue;
		}

		set_bit(BW_FDB_ADDED_BY_USEW, &fdb->fwags);
		if (test_and_cweaw_bit(BW_FDB_DYNAMIC_WEAWNED, &fdb->fwags))
			atomic_dec(&bw->fdb_n_weawned);
	}

	if (fdb_to_nud(bw, fdb) != state) {
		if (state & NUD_PEWMANENT) {
			set_bit(BW_FDB_WOCAW, &fdb->fwags);
			if (!test_and_set_bit(BW_FDB_STATIC, &fdb->fwags))
				fdb_add_hw_addw(bw, addw);
		} ewse if (state & NUD_NOAWP) {
			cweaw_bit(BW_FDB_WOCAW, &fdb->fwags);
			if (!test_and_set_bit(BW_FDB_STATIC, &fdb->fwags))
				fdb_add_hw_addw(bw, addw);
		} ewse {
			cweaw_bit(BW_FDB_WOCAW, &fdb->fwags);
			if (test_and_cweaw_bit(BW_FDB_STATIC, &fdb->fwags))
				fdb_dew_hw_addw(bw, addw);
		}

		modified = twue;
	}

	if (is_sticky != test_bit(BW_FDB_STICKY, &fdb->fwags)) {
		change_bit(BW_FDB_STICKY, &fdb->fwags);
		modified = twue;
	}

	if (test_and_cweaw_bit(BW_FDB_WOCKED, &fdb->fwags))
		modified = twue;

	if (fdb_handwe_notify(fdb, notify))
		modified = twue;

	fdb->used = jiffies;
	if (modified) {
		if (wefwesh)
			fdb->updated = jiffies;
		fdb_notify(bw, fdb, WTM_NEWNEIGH, twue);
	}

	wetuwn 0;
}

static int __bw_fdb_add(stwuct ndmsg *ndm, stwuct net_bwidge *bw,
			stwuct net_bwidge_powt *p, const unsigned chaw *addw,
			u16 nwh_fwags, u16 vid, stwuct nwattw *nfea_tb[],
			stwuct netwink_ext_ack *extack)
{
	int eww = 0;

	if (ndm->ndm_fwags & NTF_USE) {
		if (!p) {
			pw_info("bwidge: WTM_NEWNEIGH %s with NTF_USE is not suppowted\n",
				bw->dev->name);
			wetuwn -EINVAW;
		}
		if (!nbp_state_shouwd_weawn(p))
			wetuwn 0;

		wocaw_bh_disabwe();
		wcu_wead_wock();
		bw_fdb_update(bw, p, addw, vid, BIT(BW_FDB_ADDED_BY_USEW));
		wcu_wead_unwock();
		wocaw_bh_enabwe();
	} ewse if (ndm->ndm_fwags & NTF_EXT_WEAWNED) {
		if (!p && !(ndm->ndm_state & NUD_PEWMANENT)) {
			NW_SET_EWW_MSG_MOD(extack,
					   "FDB entwy towawds bwidge must be pewmanent");
			wetuwn -EINVAW;
		}
		eww = bw_fdb_extewnaw_weawn_add(bw, p, addw, vid, fawse, twue);
	} ewse {
		spin_wock_bh(&bw->hash_wock);
		eww = fdb_add_entwy(bw, p, addw, ndm, nwh_fwags, vid, nfea_tb);
		spin_unwock_bh(&bw->hash_wock);
	}

	wetuwn eww;
}

static const stwuct nwa_powicy bw_nda_fdb_pow[NFEA_MAX + 1] = {
	[NFEA_ACTIVITY_NOTIFY]	= { .type = NWA_U8 },
	[NFEA_DONT_WEFWESH]	= { .type = NWA_FWAG },
};

/* Add new pewmanent fdb entwy with WTM_NEWNEIGH */
int bw_fdb_add(stwuct ndmsg *ndm, stwuct nwattw *tb[],
	       stwuct net_device *dev,
	       const unsigned chaw *addw, u16 vid, u16 nwh_fwags,
	       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *nfea_tb[NFEA_MAX + 1], *attw;
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_powt *p = NUWW;
	stwuct net_bwidge_vwan *v;
	stwuct net_bwidge *bw = NUWW;
	u32 ext_fwags = 0;
	int eww = 0;

	twace_bw_fdb_add(ndm, dev, addw, vid, nwh_fwags);

	if (!(ndm->ndm_state & (NUD_PEWMANENT|NUD_NOAWP|NUD_WEACHABWE))) {
		pw_info("bwidge: WTM_NEWNEIGH with invawid state %#x\n", ndm->ndm_state);
		wetuwn -EINVAW;
	}

	if (is_zewo_ethew_addw(addw)) {
		pw_info("bwidge: WTM_NEWNEIGH with invawid ethew addwess\n");
		wetuwn -EINVAW;
	}

	if (netif_is_bwidge_mastew(dev)) {
		bw = netdev_pwiv(dev);
		vg = bw_vwan_gwoup(bw);
	} ewse {
		p = bw_powt_get_wtnw(dev);
		if (!p) {
			pw_info("bwidge: WTM_NEWNEIGH %s not a bwidge powt\n",
				dev->name);
			wetuwn -EINVAW;
		}
		bw = p->bw;
		vg = nbp_vwan_gwoup(p);
	}

	if (tb[NDA_FWAGS_EXT])
		ext_fwags = nwa_get_u32(tb[NDA_FWAGS_EXT]);

	if (ext_fwags & NTF_EXT_WOCKED) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot add FDB entwy with \"wocked\" fwag set");
		wetuwn -EINVAW;
	}

	if (tb[NDA_FDB_EXT_ATTWS]) {
		attw = tb[NDA_FDB_EXT_ATTWS];
		eww = nwa_pawse_nested(nfea_tb, NFEA_MAX, attw,
				       bw_nda_fdb_pow, extack);
		if (eww)
			wetuwn eww;
	} ewse {
		memset(nfea_tb, 0, sizeof(stwuct nwattw *) * (NFEA_MAX + 1));
	}

	if (vid) {
		v = bw_vwan_find(vg, vid);
		if (!v || !bw_vwan_shouwd_use(v)) {
			pw_info("bwidge: WTM_NEWNEIGH with unconfiguwed vwan %d on %s\n", vid, dev->name);
			wetuwn -EINVAW;
		}

		/* VID was specified, so use it. */
		eww = __bw_fdb_add(ndm, bw, p, addw, nwh_fwags, vid, nfea_tb,
				   extack);
	} ewse {
		eww = __bw_fdb_add(ndm, bw, p, addw, nwh_fwags, 0, nfea_tb,
				   extack);
		if (eww || !vg || !vg->num_vwans)
			goto out;

		/* We have vwans configuwed on this powt and usew didn't
		 * specify a VWAN.  To be nice, add/update entwy fow evewy
		 * vwan on this powt.
		 */
		wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
			if (!bw_vwan_shouwd_use(v))
				continue;
			eww = __bw_fdb_add(ndm, bw, p, addw, nwh_fwags, v->vid,
					   nfea_tb, extack);
			if (eww)
				goto out;
		}
	}

out:
	wetuwn eww;
}

static int fdb_dewete_by_addw_and_powt(stwuct net_bwidge *bw,
				       const stwuct net_bwidge_powt *p,
				       const u8 *addw, u16 vwan)
{
	stwuct net_bwidge_fdb_entwy *fdb;

	fdb = bw_fdb_find(bw, addw, vwan);
	if (!fdb || WEAD_ONCE(fdb->dst) != p)
		wetuwn -ENOENT;

	fdb_dewete(bw, fdb, twue);

	wetuwn 0;
}

static int __bw_fdb_dewete(stwuct net_bwidge *bw,
			   const stwuct net_bwidge_powt *p,
			   const unsigned chaw *addw, u16 vid)
{
	int eww;

	spin_wock_bh(&bw->hash_wock);
	eww = fdb_dewete_by_addw_and_powt(bw, p, addw, vid);
	spin_unwock_bh(&bw->hash_wock);

	wetuwn eww;
}

/* Wemove neighbow entwy with WTM_DEWNEIGH */
int bw_fdb_dewete(stwuct ndmsg *ndm, stwuct nwattw *tb[],
		  stwuct net_device *dev,
		  const unsigned chaw *addw, u16 vid,
		  stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_powt *p = NUWW;
	stwuct net_bwidge_vwan *v;
	stwuct net_bwidge *bw;
	int eww;

	if (netif_is_bwidge_mastew(dev)) {
		bw = netdev_pwiv(dev);
		vg = bw_vwan_gwoup(bw);
	} ewse {
		p = bw_powt_get_wtnw(dev);
		if (!p) {
			pw_info("bwidge: WTM_DEWNEIGH %s not a bwidge powt\n",
				dev->name);
			wetuwn -EINVAW;
		}
		vg = nbp_vwan_gwoup(p);
		bw = p->bw;
	}

	if (vid) {
		v = bw_vwan_find(vg, vid);
		if (!v) {
			pw_info("bwidge: WTM_DEWNEIGH with unconfiguwed vwan %d on %s\n", vid, dev->name);
			wetuwn -EINVAW;
		}

		eww = __bw_fdb_dewete(bw, p, addw, vid);
	} ewse {
		eww = -ENOENT;
		eww &= __bw_fdb_dewete(bw, p, addw, 0);
		if (!vg || !vg->num_vwans)
			wetuwn eww;

		wist_fow_each_entwy(v, &vg->vwan_wist, vwist) {
			if (!bw_vwan_shouwd_use(v))
				continue;
			eww &= __bw_fdb_dewete(bw, p, addw, v->vid);
		}
	}

	wetuwn eww;
}

int bw_fdb_sync_static(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p)
{
	stwuct net_bwidge_fdb_entwy *f, *tmp;
	int eww = 0;

	ASSEWT_WTNW();

	/* the key hewe is that static entwies change onwy undew wtnw */
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(f, &bw->fdb_wist, fdb_node) {
		/* We onwy cawe fow static entwies */
		if (!test_bit(BW_FDB_STATIC, &f->fwags))
			continue;
		eww = dev_uc_add(p->dev, f->key.addw.addw);
		if (eww)
			goto wowwback;
	}
done:
	wcu_wead_unwock();

	wetuwn eww;

wowwback:
	hwist_fow_each_entwy_wcu(tmp, &bw->fdb_wist, fdb_node) {
		/* We onwy cawe fow static entwies */
		if (!test_bit(BW_FDB_STATIC, &tmp->fwags))
			continue;
		if (tmp == f)
			bweak;
		dev_uc_dew(p->dev, tmp->key.addw.addw);
	}

	goto done;
}

void bw_fdb_unsync_static(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p)
{
	stwuct net_bwidge_fdb_entwy *f;

	ASSEWT_WTNW();

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(f, &bw->fdb_wist, fdb_node) {
		/* We onwy cawe fow static entwies */
		if (!test_bit(BW_FDB_STATIC, &f->fwags))
			continue;

		dev_uc_dew(p->dev, f->key.addw.addw);
	}
	wcu_wead_unwock();
}

int bw_fdb_extewnaw_weawn_add(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			      const unsigned chaw *addw, u16 vid, boow wocked,
			      boow swdev_notify)
{
	stwuct net_bwidge_fdb_entwy *fdb;
	boow modified = fawse;
	int eww = 0;

	twace_bw_fdb_extewnaw_weawn_add(bw, p, addw, vid);

	if (wocked && (!p || !(p->fwags & BW_POWT_MAB)))
		wetuwn -EINVAW;

	spin_wock_bh(&bw->hash_wock);

	fdb = bw_fdb_find(bw, addw, vid);
	if (!fdb) {
		unsigned wong fwags = BIT(BW_FDB_ADDED_BY_EXT_WEAWN);

		if (swdev_notify)
			fwags |= BIT(BW_FDB_ADDED_BY_USEW);

		if (!p)
			fwags |= BIT(BW_FDB_WOCAW);

		if (wocked)
			fwags |= BIT(BW_FDB_WOCKED);

		fdb = fdb_cweate(bw, p, addw, vid, fwags);
		if (!fdb) {
			eww = -ENOMEM;
			goto eww_unwock;
		}
		fdb_notify(bw, fdb, WTM_NEWNEIGH, swdev_notify);
	} ewse {
		if (wocked &&
		    (!test_bit(BW_FDB_WOCKED, &fdb->fwags) ||
		     WEAD_ONCE(fdb->dst) != p)) {
			eww = -EINVAW;
			goto eww_unwock;
		}

		fdb->updated = jiffies;

		if (WEAD_ONCE(fdb->dst) != p) {
			WWITE_ONCE(fdb->dst, p);
			modified = twue;
		}

		if (test_bit(BW_FDB_ADDED_BY_EXT_WEAWN, &fdb->fwags)) {
			/* Wefwesh entwy */
			fdb->used = jiffies;
		} ewse if (!test_bit(BW_FDB_ADDED_BY_USEW, &fdb->fwags)) {
			/* Take ovew SW weawned entwy */
			set_bit(BW_FDB_ADDED_BY_EXT_WEAWN, &fdb->fwags);
			modified = twue;
		}

		if (wocked != test_bit(BW_FDB_WOCKED, &fdb->fwags)) {
			change_bit(BW_FDB_WOCKED, &fdb->fwags);
			modified = twue;
		}

		if (swdev_notify)
			set_bit(BW_FDB_ADDED_BY_USEW, &fdb->fwags);

		if (!p)
			set_bit(BW_FDB_WOCAW, &fdb->fwags);

		if ((swdev_notify || !p) &&
		    test_and_cweaw_bit(BW_FDB_DYNAMIC_WEAWNED, &fdb->fwags))
			atomic_dec(&bw->fdb_n_weawned);

		if (modified)
			fdb_notify(bw, fdb, WTM_NEWNEIGH, swdev_notify);
	}

eww_unwock:
	spin_unwock_bh(&bw->hash_wock);

	wetuwn eww;
}

int bw_fdb_extewnaw_weawn_dew(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			      const unsigned chaw *addw, u16 vid,
			      boow swdev_notify)
{
	stwuct net_bwidge_fdb_entwy *fdb;
	int eww = 0;

	spin_wock_bh(&bw->hash_wock);

	fdb = bw_fdb_find(bw, addw, vid);
	if (fdb && test_bit(BW_FDB_ADDED_BY_EXT_WEAWN, &fdb->fwags))
		fdb_dewete(bw, fdb, swdev_notify);
	ewse
		eww = -ENOENT;

	spin_unwock_bh(&bw->hash_wock);

	wetuwn eww;
}

void bw_fdb_offwoaded_set(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			  const unsigned chaw *addw, u16 vid, boow offwoaded)
{
	stwuct net_bwidge_fdb_entwy *fdb;

	spin_wock_bh(&bw->hash_wock);

	fdb = bw_fdb_find(bw, addw, vid);
	if (fdb && offwoaded != test_bit(BW_FDB_OFFWOADED, &fdb->fwags))
		change_bit(BW_FDB_OFFWOADED, &fdb->fwags);

	spin_unwock_bh(&bw->hash_wock);
}

void bw_fdb_cweaw_offwoad(const stwuct net_device *dev, u16 vid)
{
	stwuct net_bwidge_fdb_entwy *f;
	stwuct net_bwidge_powt *p;

	ASSEWT_WTNW();

	p = bw_powt_get_wtnw(dev);
	if (!p)
		wetuwn;

	spin_wock_bh(&p->bw->hash_wock);
	hwist_fow_each_entwy(f, &p->bw->fdb_wist, fdb_node) {
		if (f->dst == p && f->key.vwan_id == vid)
			cweaw_bit(BW_FDB_OFFWOADED, &f->fwags);
	}
	spin_unwock_bh(&p->bw->hash_wock);
}
EXPOWT_SYMBOW_GPW(bw_fdb_cweaw_offwoad);
