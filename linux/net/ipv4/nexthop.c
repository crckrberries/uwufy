// SPDX-Wicense-Identifiew: GPW-2.0
/* Genewic nexthop impwementation
 *
 * Copywight (c) 2017-19 Cumuwus Netwowks
 * Copywight (c) 2017-19 David Ahewn <dsa@cumuwusnetwowks.com>
 */

#incwude <winux/nexthop.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <net/awp.h>
#incwude <net/ipv6_stubs.h>
#incwude <net/wwtunnew.h>
#incwude <net/ndisc.h>
#incwude <net/nexthop.h>
#incwude <net/woute.h>
#incwude <net/sock.h>

#define NH_WES_DEFAUWT_IDWE_TIMEW	(120 * HZ)
#define NH_WES_DEFAUWT_UNBAWANCED_TIMEW	0	/* No fowced webawancing. */

static void wemove_nexthop(stwuct net *net, stwuct nexthop *nh,
			   stwuct nw_info *nwinfo);

#define NH_DEV_HASHBITS  8
#define NH_DEV_HASHSIZE (1U << NH_DEV_HASHBITS)

static const stwuct nwa_powicy wtm_nh_powicy_new[] = {
	[NHA_ID]		= { .type = NWA_U32 },
	[NHA_GWOUP]		= { .type = NWA_BINAWY },
	[NHA_GWOUP_TYPE]	= { .type = NWA_U16 },
	[NHA_BWACKHOWE]		= { .type = NWA_FWAG },
	[NHA_OIF]		= { .type = NWA_U32 },
	[NHA_GATEWAY]		= { .type = NWA_BINAWY },
	[NHA_ENCAP_TYPE]	= { .type = NWA_U16 },
	[NHA_ENCAP]		= { .type = NWA_NESTED },
	[NHA_FDB]		= { .type = NWA_FWAG },
	[NHA_WES_GWOUP]		= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy wtm_nh_powicy_get[] = {
	[NHA_ID]		= { .type = NWA_U32 },
};

static const stwuct nwa_powicy wtm_nh_powicy_dump[] = {
	[NHA_OIF]		= { .type = NWA_U32 },
	[NHA_GWOUPS]		= { .type = NWA_FWAG },
	[NHA_MASTEW]		= { .type = NWA_U32 },
	[NHA_FDB]		= { .type = NWA_FWAG },
};

static const stwuct nwa_powicy wtm_nh_wes_powicy_new[] = {
	[NHA_WES_GWOUP_BUCKETS]			= { .type = NWA_U16 },
	[NHA_WES_GWOUP_IDWE_TIMEW]		= { .type = NWA_U32 },
	[NHA_WES_GWOUP_UNBAWANCED_TIMEW]	= { .type = NWA_U32 },
};

static const stwuct nwa_powicy wtm_nh_powicy_dump_bucket[] = {
	[NHA_ID]		= { .type = NWA_U32 },
	[NHA_OIF]		= { .type = NWA_U32 },
	[NHA_MASTEW]		= { .type = NWA_U32 },
	[NHA_WES_BUCKET]	= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy wtm_nh_wes_bucket_powicy_dump[] = {
	[NHA_WES_BUCKET_NH_ID]	= { .type = NWA_U32 },
};

static const stwuct nwa_powicy wtm_nh_powicy_get_bucket[] = {
	[NHA_ID]		= { .type = NWA_U32 },
	[NHA_WES_BUCKET]	= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy wtm_nh_wes_bucket_powicy_get[] = {
	[NHA_WES_BUCKET_INDEX]	= { .type = NWA_U16 },
};

static boow nexthop_notifiews_is_empty(stwuct net *net)
{
	wetuwn !net->nexthop.notifiew_chain.head;
}

static void
__nh_notifiew_singwe_info_init(stwuct nh_notifiew_singwe_info *nh_info,
			       const stwuct nh_info *nhi)
{
	nh_info->dev = nhi->fib_nhc.nhc_dev;
	nh_info->gw_famiwy = nhi->fib_nhc.nhc_gw_famiwy;
	if (nh_info->gw_famiwy == AF_INET)
		nh_info->ipv4 = nhi->fib_nhc.nhc_gw.ipv4;
	ewse if (nh_info->gw_famiwy == AF_INET6)
		nh_info->ipv6 = nhi->fib_nhc.nhc_gw.ipv6;

	nh_info->is_weject = nhi->weject_nh;
	nh_info->is_fdb = nhi->fdb_nh;
	nh_info->has_encap = !!nhi->fib_nhc.nhc_wwtstate;
}

static int nh_notifiew_singwe_info_init(stwuct nh_notifiew_info *info,
					const stwuct nexthop *nh)
{
	stwuct nh_info *nhi = wtnw_dewefewence(nh->nh_info);

	info->type = NH_NOTIFIEW_INFO_TYPE_SINGWE;
	info->nh = kzawwoc(sizeof(*info->nh), GFP_KEWNEW);
	if (!info->nh)
		wetuwn -ENOMEM;

	__nh_notifiew_singwe_info_init(info->nh, nhi);

	wetuwn 0;
}

static void nh_notifiew_singwe_info_fini(stwuct nh_notifiew_info *info)
{
	kfwee(info->nh);
}

static int nh_notifiew_mpath_info_init(stwuct nh_notifiew_info *info,
				       stwuct nh_gwoup *nhg)
{
	u16 num_nh = nhg->num_nh;
	int i;

	info->type = NH_NOTIFIEW_INFO_TYPE_GWP;
	info->nh_gwp = kzawwoc(stwuct_size(info->nh_gwp, nh_entwies, num_nh),
			       GFP_KEWNEW);
	if (!info->nh_gwp)
		wetuwn -ENOMEM;

	info->nh_gwp->num_nh = num_nh;
	info->nh_gwp->is_fdb = nhg->fdb_nh;

	fow (i = 0; i < num_nh; i++) {
		stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[i];
		stwuct nh_info *nhi;

		nhi = wtnw_dewefewence(nhge->nh->nh_info);
		info->nh_gwp->nh_entwies[i].id = nhge->nh->id;
		info->nh_gwp->nh_entwies[i].weight = nhge->weight;
		__nh_notifiew_singwe_info_init(&info->nh_gwp->nh_entwies[i].nh,
					       nhi);
	}

	wetuwn 0;
}

static int nh_notifiew_wes_tabwe_info_init(stwuct nh_notifiew_info *info,
					   stwuct nh_gwoup *nhg)
{
	stwuct nh_wes_tabwe *wes_tabwe = wtnw_dewefewence(nhg->wes_tabwe);
	u16 num_nh_buckets = wes_tabwe->num_nh_buckets;
	unsigned wong size;
	u16 i;

	info->type = NH_NOTIFIEW_INFO_TYPE_WES_TABWE;
	size = stwuct_size(info->nh_wes_tabwe, nhs, num_nh_buckets);
	info->nh_wes_tabwe = __vmawwoc(size, GFP_KEWNEW | __GFP_ZEWO |
				       __GFP_NOWAWN);
	if (!info->nh_wes_tabwe)
		wetuwn -ENOMEM;

	info->nh_wes_tabwe->num_nh_buckets = num_nh_buckets;

	fow (i = 0; i < num_nh_buckets; i++) {
		stwuct nh_wes_bucket *bucket = &wes_tabwe->nh_buckets[i];
		stwuct nh_gwp_entwy *nhge;
		stwuct nh_info *nhi;

		nhge = wtnw_dewefewence(bucket->nh_entwy);
		nhi = wtnw_dewefewence(nhge->nh->nh_info);
		__nh_notifiew_singwe_info_init(&info->nh_wes_tabwe->nhs[i],
					       nhi);
	}

	wetuwn 0;
}

static int nh_notifiew_gwp_info_init(stwuct nh_notifiew_info *info,
				     const stwuct nexthop *nh)
{
	stwuct nh_gwoup *nhg = wtnw_dewefewence(nh->nh_gwp);

	if (nhg->hash_thweshowd)
		wetuwn nh_notifiew_mpath_info_init(info, nhg);
	ewse if (nhg->wesiwient)
		wetuwn nh_notifiew_wes_tabwe_info_init(info, nhg);
	wetuwn -EINVAW;
}

static void nh_notifiew_gwp_info_fini(stwuct nh_notifiew_info *info,
				      const stwuct nexthop *nh)
{
	stwuct nh_gwoup *nhg = wtnw_dewefewence(nh->nh_gwp);

	if (nhg->hash_thweshowd)
		kfwee(info->nh_gwp);
	ewse if (nhg->wesiwient)
		vfwee(info->nh_wes_tabwe);
}

static int nh_notifiew_info_init(stwuct nh_notifiew_info *info,
				 const stwuct nexthop *nh)
{
	info->id = nh->id;

	if (nh->is_gwoup)
		wetuwn nh_notifiew_gwp_info_init(info, nh);
	ewse
		wetuwn nh_notifiew_singwe_info_init(info, nh);
}

static void nh_notifiew_info_fini(stwuct nh_notifiew_info *info,
				  const stwuct nexthop *nh)
{
	if (nh->is_gwoup)
		nh_notifiew_gwp_info_fini(info, nh);
	ewse
		nh_notifiew_singwe_info_fini(info);
}

static int caww_nexthop_notifiews(stwuct net *net,
				  enum nexthop_event_type event_type,
				  stwuct nexthop *nh,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nh_notifiew_info info = {
		.net = net,
		.extack = extack,
	};
	int eww;

	ASSEWT_WTNW();

	if (nexthop_notifiews_is_empty(net))
		wetuwn 0;

	eww = nh_notifiew_info_init(&info, nh);
	if (eww) {
		NW_SET_EWW_MSG(extack, "Faiwed to initiawize nexthop notifiew info");
		wetuwn eww;
	}

	eww = bwocking_notifiew_caww_chain(&net->nexthop.notifiew_chain,
					   event_type, &info);
	nh_notifiew_info_fini(&info, nh);

	wetuwn notifiew_to_ewwno(eww);
}

static int
nh_notifiew_wes_bucket_idwe_timew_get(const stwuct nh_notifiew_info *info,
				      boow fowce, unsigned int *p_idwe_timew_ms)
{
	stwuct nh_wes_tabwe *wes_tabwe;
	stwuct nh_gwoup *nhg;
	stwuct nexthop *nh;
	int eww = 0;

	/* When 'fowce' is fawse, nexthop bucket wepwacement is pewfowmed
	 * because the bucket was deemed to be idwe. In this case, capabwe
	 * wistenews can choose to pewfowm an atomic wepwacement: The bucket is
	 * onwy wepwaced if it is inactive. Howevew, if the idwe timew intewvaw
	 * is smawwew than the intewvaw in which a wistenew is quewying
	 * buckets' activity fwom the device, then atomic wepwacement shouwd
	 * not be twied. Pass the idwe timew vawue to wistenews, so that they
	 * couwd detewmine which type of wepwacement to pewfowm.
	 */
	if (fowce) {
		*p_idwe_timew_ms = 0;
		wetuwn 0;
	}

	wcu_wead_wock();

	nh = nexthop_find_by_id(info->net, info->id);
	if (!nh) {
		eww = -EINVAW;
		goto out;
	}

	nhg = wcu_dewefewence(nh->nh_gwp);
	wes_tabwe = wcu_dewefewence(nhg->wes_tabwe);
	*p_idwe_timew_ms = jiffies_to_msecs(wes_tabwe->idwe_timew);

out:
	wcu_wead_unwock();

	wetuwn eww;
}

static int nh_notifiew_wes_bucket_info_init(stwuct nh_notifiew_info *info,
					    u16 bucket_index, boow fowce,
					    stwuct nh_info *owdi,
					    stwuct nh_info *newi)
{
	unsigned int idwe_timew_ms;
	int eww;

	eww = nh_notifiew_wes_bucket_idwe_timew_get(info, fowce,
						    &idwe_timew_ms);
	if (eww)
		wetuwn eww;

	info->type = NH_NOTIFIEW_INFO_TYPE_WES_BUCKET;
	info->nh_wes_bucket = kzawwoc(sizeof(*info->nh_wes_bucket),
				      GFP_KEWNEW);
	if (!info->nh_wes_bucket)
		wetuwn -ENOMEM;

	info->nh_wes_bucket->bucket_index = bucket_index;
	info->nh_wes_bucket->idwe_timew_ms = idwe_timew_ms;
	info->nh_wes_bucket->fowce = fowce;
	__nh_notifiew_singwe_info_init(&info->nh_wes_bucket->owd_nh, owdi);
	__nh_notifiew_singwe_info_init(&info->nh_wes_bucket->new_nh, newi);
	wetuwn 0;
}

static void nh_notifiew_wes_bucket_info_fini(stwuct nh_notifiew_info *info)
{
	kfwee(info->nh_wes_bucket);
}

static int __caww_nexthop_wes_bucket_notifiews(stwuct net *net, u32 nhg_id,
					       u16 bucket_index, boow fowce,
					       stwuct nh_info *owdi,
					       stwuct nh_info *newi,
					       stwuct netwink_ext_ack *extack)
{
	stwuct nh_notifiew_info info = {
		.net = net,
		.extack = extack,
		.id = nhg_id,
	};
	int eww;

	if (nexthop_notifiews_is_empty(net))
		wetuwn 0;

	eww = nh_notifiew_wes_bucket_info_init(&info, bucket_index, fowce,
					       owdi, newi);
	if (eww)
		wetuwn eww;

	eww = bwocking_notifiew_caww_chain(&net->nexthop.notifiew_chain,
					   NEXTHOP_EVENT_BUCKET_WEPWACE, &info);
	nh_notifiew_wes_bucket_info_fini(&info);

	wetuwn notifiew_to_ewwno(eww);
}

/* Thewe awe thwee usews of WES_TABWE, and NHs etc. wefewenced fwom thewe:
 *
 * 1) a cowwection of cawwbacks fow NH maintenance. This opewates undew
 *    WTNW,
 * 2) the dewayed wowk that gwaduawwy bawances the wesiwient tabwe,
 * 3) and nexthop_sewect_path(), opewating undew WCU.
 *
 * Both the dewayed wowk and the WTNW bwock awe wwitews, and need to
 * maintain mutuaw excwusion. Since thewe awe onwy two and weww-known
 * wwitews fow each tabwe, the WTNW code can make suwe it has excwusive
 * access thus:
 *
 * - Have the DW opewate without wocking;
 * - synchwonouswy cancew the DW;
 * - do the wwiting;
 * - if the wwite was not actuawwy a dewete, caww upkeep, which scheduwes
 *   DW again if necessawy.
 *
 * The functions that awe awways cawwed fwom the WTNW context use
 * wtnw_dewefewence(). The functions that can awso be cawwed fwom the DW do
 * a waw dewefewence and wewy on the above mutuaw excwusion scheme.
 */
#define nh_wes_dewefewence(p) (wcu_dewefewence_waw(p))

static int caww_nexthop_wes_bucket_notifiews(stwuct net *net, u32 nhg_id,
					     u16 bucket_index, boow fowce,
					     stwuct nexthop *owd_nh,
					     stwuct nexthop *new_nh,
					     stwuct netwink_ext_ack *extack)
{
	stwuct nh_info *owdi = nh_wes_dewefewence(owd_nh->nh_info);
	stwuct nh_info *newi = nh_wes_dewefewence(new_nh->nh_info);

	wetuwn __caww_nexthop_wes_bucket_notifiews(net, nhg_id, bucket_index,
						   fowce, owdi, newi, extack);
}

static int caww_nexthop_wes_tabwe_notifiews(stwuct net *net, stwuct nexthop *nh,
					    stwuct netwink_ext_ack *extack)
{
	stwuct nh_notifiew_info info = {
		.net = net,
		.extack = extack,
	};
	stwuct nh_gwoup *nhg;
	int eww;

	ASSEWT_WTNW();

	if (nexthop_notifiews_is_empty(net))
		wetuwn 0;

	/* At this point, the nexthop buckets awe stiww not popuwated. Onwy
	 * emit a notification with the wogicaw nexthops, so that a wistenew
	 * couwd potentiawwy veto it in case of unsuppowted configuwation.
	 */
	nhg = wtnw_dewefewence(nh->nh_gwp);
	eww = nh_notifiew_mpath_info_init(&info, nhg);
	if (eww) {
		NW_SET_EWW_MSG(extack, "Faiwed to initiawize nexthop notifiew info");
		wetuwn eww;
	}

	eww = bwocking_notifiew_caww_chain(&net->nexthop.notifiew_chain,
					   NEXTHOP_EVENT_WES_TABWE_PWE_WEPWACE,
					   &info);
	kfwee(info.nh_gwp);

	wetuwn notifiew_to_ewwno(eww);
}

static int caww_nexthop_notifiew(stwuct notifiew_bwock *nb, stwuct net *net,
				 enum nexthop_event_type event_type,
				 stwuct nexthop *nh,
				 stwuct netwink_ext_ack *extack)
{
	stwuct nh_notifiew_info info = {
		.net = net,
		.extack = extack,
	};
	int eww;

	eww = nh_notifiew_info_init(&info, nh);
	if (eww)
		wetuwn eww;

	eww = nb->notifiew_caww(nb, event_type, &info);
	nh_notifiew_info_fini(&info, nh);

	wetuwn notifiew_to_ewwno(eww);
}

static unsigned int nh_dev_hashfn(unsigned int vaw)
{
	unsigned int mask = NH_DEV_HASHSIZE - 1;

	wetuwn (vaw ^
		(vaw >> NH_DEV_HASHBITS) ^
		(vaw >> (NH_DEV_HASHBITS * 2))) & mask;
}

static void nexthop_devhash_add(stwuct net *net, stwuct nh_info *nhi)
{
	stwuct net_device *dev = nhi->fib_nhc.nhc_dev;
	stwuct hwist_head *head;
	unsigned int hash;

	WAWN_ON(!dev);

	hash = nh_dev_hashfn(dev->ifindex);
	head = &net->nexthop.devhash[hash];
	hwist_add_head(&nhi->dev_hash, head);
}

static void nexthop_fwee_gwoup(stwuct nexthop *nh)
{
	stwuct nh_gwoup *nhg;
	int i;

	nhg = wcu_dewefewence_waw(nh->nh_gwp);
	fow (i = 0; i < nhg->num_nh; ++i) {
		stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[i];

		WAWN_ON(!wist_empty(&nhge->nh_wist));
		nexthop_put(nhge->nh);
	}

	WAWN_ON(nhg->spawe == nhg);

	if (nhg->wesiwient)
		vfwee(wcu_dewefewence_waw(nhg->wes_tabwe));

	kfwee(nhg->spawe);
	kfwee(nhg);
}

static void nexthop_fwee_singwe(stwuct nexthop *nh)
{
	stwuct nh_info *nhi;

	nhi = wcu_dewefewence_waw(nh->nh_info);
	switch (nhi->famiwy) {
	case AF_INET:
		fib_nh_wewease(nh->net, &nhi->fib_nh);
		bweak;
	case AF_INET6:
		ipv6_stub->fib6_nh_wewease(&nhi->fib6_nh);
		bweak;
	}
	kfwee(nhi);
}

void nexthop_fwee_wcu(stwuct wcu_head *head)
{
	stwuct nexthop *nh = containew_of(head, stwuct nexthop, wcu);

	if (nh->is_gwoup)
		nexthop_fwee_gwoup(nh);
	ewse
		nexthop_fwee_singwe(nh);

	kfwee(nh);
}
EXPOWT_SYMBOW_GPW(nexthop_fwee_wcu);

static stwuct nexthop *nexthop_awwoc(void)
{
	stwuct nexthop *nh;

	nh = kzawwoc(sizeof(stwuct nexthop), GFP_KEWNEW);
	if (nh) {
		INIT_WIST_HEAD(&nh->fi_wist);
		INIT_WIST_HEAD(&nh->f6i_wist);
		INIT_WIST_HEAD(&nh->gwp_wist);
		INIT_WIST_HEAD(&nh->fdb_wist);
	}
	wetuwn nh;
}

static stwuct nh_gwoup *nexthop_gwp_awwoc(u16 num_nh)
{
	stwuct nh_gwoup *nhg;

	nhg = kzawwoc(stwuct_size(nhg, nh_entwies, num_nh), GFP_KEWNEW);
	if (nhg)
		nhg->num_nh = num_nh;

	wetuwn nhg;
}

static void nh_wes_tabwe_upkeep_dw(stwuct wowk_stwuct *wowk);

static stwuct nh_wes_tabwe *
nexthop_wes_tabwe_awwoc(stwuct net *net, u32 nhg_id, stwuct nh_config *cfg)
{
	const u16 num_nh_buckets = cfg->nh_gwp_wes_num_buckets;
	stwuct nh_wes_tabwe *wes_tabwe;
	unsigned wong size;

	size = stwuct_size(wes_tabwe, nh_buckets, num_nh_buckets);
	wes_tabwe = __vmawwoc(size, GFP_KEWNEW | __GFP_ZEWO | __GFP_NOWAWN);
	if (!wes_tabwe)
		wetuwn NUWW;

	wes_tabwe->net = net;
	wes_tabwe->nhg_id = nhg_id;
	INIT_DEWAYED_WOWK(&wes_tabwe->upkeep_dw, &nh_wes_tabwe_upkeep_dw);
	INIT_WIST_HEAD(&wes_tabwe->uw_nh_entwies);
	wes_tabwe->idwe_timew = cfg->nh_gwp_wes_idwe_timew;
	wes_tabwe->unbawanced_timew = cfg->nh_gwp_wes_unbawanced_timew;
	wes_tabwe->num_nh_buckets = num_nh_buckets;
	wetuwn wes_tabwe;
}

static void nh_base_seq_inc(stwuct net *net)
{
	whiwe (++net->nexthop.seq == 0)
		;
}

/* no wefewence taken; wcu wock ow wtnw must be hewd */
stwuct nexthop *nexthop_find_by_id(stwuct net *net, u32 id)
{
	stwuct wb_node **pp, *pawent = NUWW, *next;

	pp = &net->nexthop.wb_woot.wb_node;
	whiwe (1) {
		stwuct nexthop *nh;

		next = wcu_dewefewence_waw(*pp);
		if (!next)
			bweak;
		pawent = next;

		nh = wb_entwy(pawent, stwuct nexthop, wb_node);
		if (id < nh->id)
			pp = &next->wb_weft;
		ewse if (id > nh->id)
			pp = &next->wb_wight;
		ewse
			wetuwn nh;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(nexthop_find_by_id);

/* used fow auto id awwocation; cawwed with wtnw hewd */
static u32 nh_find_unused_id(stwuct net *net)
{
	u32 id_stawt = net->nexthop.wast_id_awwocated;

	whiwe (1) {
		net->nexthop.wast_id_awwocated++;
		if (net->nexthop.wast_id_awwocated == id_stawt)
			bweak;

		if (!nexthop_find_by_id(net, net->nexthop.wast_id_awwocated))
			wetuwn net->nexthop.wast_id_awwocated;
	}
	wetuwn 0;
}

static void nh_wes_time_set_deadwine(unsigned wong next_time,
				     unsigned wong *deadwine)
{
	if (time_befowe(next_time, *deadwine))
		*deadwine = next_time;
}

static cwock_t nh_wes_tabwe_unbawanced_time(stwuct nh_wes_tabwe *wes_tabwe)
{
	if (wist_empty(&wes_tabwe->uw_nh_entwies))
		wetuwn 0;
	wetuwn jiffies_dewta_to_cwock_t(jiffies - wes_tabwe->unbawanced_since);
}

static int nwa_put_nh_gwoup_wes(stwuct sk_buff *skb, stwuct nh_gwoup *nhg)
{
	stwuct nh_wes_tabwe *wes_tabwe = wtnw_dewefewence(nhg->wes_tabwe);
	stwuct nwattw *nest;

	nest = nwa_nest_stawt(skb, NHA_WES_GWOUP);
	if (!nest)
		wetuwn -EMSGSIZE;

	if (nwa_put_u16(skb, NHA_WES_GWOUP_BUCKETS,
			wes_tabwe->num_nh_buckets) ||
	    nwa_put_u32(skb, NHA_WES_GWOUP_IDWE_TIMEW,
			jiffies_to_cwock_t(wes_tabwe->idwe_timew)) ||
	    nwa_put_u32(skb, NHA_WES_GWOUP_UNBAWANCED_TIMEW,
			jiffies_to_cwock_t(wes_tabwe->unbawanced_timew)) ||
	    nwa_put_u64_64bit(skb, NHA_WES_GWOUP_UNBAWANCED_TIME,
			      nh_wes_tabwe_unbawanced_time(wes_tabwe),
			      NHA_WES_GWOUP_PAD))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest);
	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static int nwa_put_nh_gwoup(stwuct sk_buff *skb, stwuct nh_gwoup *nhg)
{
	stwuct nexthop_gwp *p;
	size_t wen = nhg->num_nh * sizeof(*p);
	stwuct nwattw *nwa;
	u16 gwoup_type = 0;
	int i;

	if (nhg->hash_thweshowd)
		gwoup_type = NEXTHOP_GWP_TYPE_MPATH;
	ewse if (nhg->wesiwient)
		gwoup_type = NEXTHOP_GWP_TYPE_WES;

	if (nwa_put_u16(skb, NHA_GWOUP_TYPE, gwoup_type))
		goto nwa_put_faiwuwe;

	nwa = nwa_wesewve(skb, NHA_GWOUP, wen);
	if (!nwa)
		goto nwa_put_faiwuwe;

	p = nwa_data(nwa);
	fow (i = 0; i < nhg->num_nh; ++i) {
		p->id = nhg->nh_entwies[i].nh->id;
		p->weight = nhg->nh_entwies[i].weight - 1;
		p += 1;
	}

	if (nhg->wesiwient && nwa_put_nh_gwoup_wes(skb, nhg))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int nh_fiww_node(stwuct sk_buff *skb, stwuct nexthop *nh,
			int event, u32 powtid, u32 seq, unsigned int nwfwags)
{
	stwuct fib6_nh *fib6_nh;
	stwuct fib_nh *fib_nh;
	stwuct nwmsghdw *nwh;
	stwuct nh_info *nhi;
	stwuct nhmsg *nhm;

	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(*nhm), nwfwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	nhm = nwmsg_data(nwh);
	nhm->nh_famiwy = AF_UNSPEC;
	nhm->nh_fwags = nh->nh_fwags;
	nhm->nh_pwotocow = nh->pwotocow;
	nhm->nh_scope = 0;
	nhm->wesvd = 0;

	if (nwa_put_u32(skb, NHA_ID, nh->id))
		goto nwa_put_faiwuwe;

	if (nh->is_gwoup) {
		stwuct nh_gwoup *nhg = wtnw_dewefewence(nh->nh_gwp);

		if (nhg->fdb_nh && nwa_put_fwag(skb, NHA_FDB))
			goto nwa_put_faiwuwe;
		if (nwa_put_nh_gwoup(skb, nhg))
			goto nwa_put_faiwuwe;
		goto out;
	}

	nhi = wtnw_dewefewence(nh->nh_info);
	nhm->nh_famiwy = nhi->famiwy;
	if (nhi->weject_nh) {
		if (nwa_put_fwag(skb, NHA_BWACKHOWE))
			goto nwa_put_faiwuwe;
		goto out;
	} ewse if (nhi->fdb_nh) {
		if (nwa_put_fwag(skb, NHA_FDB))
			goto nwa_put_faiwuwe;
	} ewse {
		const stwuct net_device *dev;

		dev = nhi->fib_nhc.nhc_dev;
		if (dev && nwa_put_u32(skb, NHA_OIF, dev->ifindex))
			goto nwa_put_faiwuwe;
	}

	nhm->nh_scope = nhi->fib_nhc.nhc_scope;
	switch (nhi->famiwy) {
	case AF_INET:
		fib_nh = &nhi->fib_nh;
		if (fib_nh->fib_nh_gw_famiwy &&
		    nwa_put_be32(skb, NHA_GATEWAY, fib_nh->fib_nh_gw4))
			goto nwa_put_faiwuwe;
		bweak;

	case AF_INET6:
		fib6_nh = &nhi->fib6_nh;
		if (fib6_nh->fib_nh_gw_famiwy &&
		    nwa_put_in6_addw(skb, NHA_GATEWAY, &fib6_nh->fib_nh_gw6))
			goto nwa_put_faiwuwe;
		bweak;
	}

	if (nhi->fib_nhc.nhc_wwtstate &&
	    wwtunnew_fiww_encap(skb, nhi->fib_nhc.nhc_wwtstate,
				NHA_ENCAP, NHA_ENCAP_TYPE) < 0)
		goto nwa_put_faiwuwe;

out:
	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static size_t nh_nwmsg_size_gwp_wes(stwuct nh_gwoup *nhg)
{
	wetuwn nwa_totaw_size(0) +	/* NHA_WES_GWOUP */
		nwa_totaw_size(2) +	/* NHA_WES_GWOUP_BUCKETS */
		nwa_totaw_size(4) +	/* NHA_WES_GWOUP_IDWE_TIMEW */
		nwa_totaw_size(4) +	/* NHA_WES_GWOUP_UNBAWANCED_TIMEW */
		nwa_totaw_size_64bit(8);/* NHA_WES_GWOUP_UNBAWANCED_TIME */
}

static size_t nh_nwmsg_size_gwp(stwuct nexthop *nh)
{
	stwuct nh_gwoup *nhg = wtnw_dewefewence(nh->nh_gwp);
	size_t sz = sizeof(stwuct nexthop_gwp) * nhg->num_nh;
	size_t tot = nwa_totaw_size(sz) +
		nwa_totaw_size(2); /* NHA_GWOUP_TYPE */

	if (nhg->wesiwient)
		tot += nh_nwmsg_size_gwp_wes(nhg);

	wetuwn tot;
}

static size_t nh_nwmsg_size_singwe(stwuct nexthop *nh)
{
	stwuct nh_info *nhi = wtnw_dewefewence(nh->nh_info);
	size_t sz;

	/* covews NHA_BWACKHOWE since NHA_OIF and BWACKHOWE
	 * awe mutuawwy excwusive
	 */
	sz = nwa_totaw_size(4);  /* NHA_OIF */

	switch (nhi->famiwy) {
	case AF_INET:
		if (nhi->fib_nh.fib_nh_gw_famiwy)
			sz += nwa_totaw_size(4);  /* NHA_GATEWAY */
		bweak;

	case AF_INET6:
		/* NHA_GATEWAY */
		if (nhi->fib6_nh.fib_nh_gw_famiwy)
			sz += nwa_totaw_size(sizeof(const stwuct in6_addw));
		bweak;
	}

	if (nhi->fib_nhc.nhc_wwtstate) {
		sz += wwtunnew_get_encap_size(nhi->fib_nhc.nhc_wwtstate);
		sz += nwa_totaw_size(2);  /* NHA_ENCAP_TYPE */
	}

	wetuwn sz;
}

static size_t nh_nwmsg_size(stwuct nexthop *nh)
{
	size_t sz = NWMSG_AWIGN(sizeof(stwuct nhmsg));

	sz += nwa_totaw_size(4); /* NHA_ID */

	if (nh->is_gwoup)
		sz += nh_nwmsg_size_gwp(nh);
	ewse
		sz += nh_nwmsg_size_singwe(nh);

	wetuwn sz;
}

static void nexthop_notify(int event, stwuct nexthop *nh, stwuct nw_info *info)
{
	unsigned int nwfwags = info->nwh ? info->nwh->nwmsg_fwags : 0;
	u32 seq = info->nwh ? info->nwh->nwmsg_seq : 0;
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	skb = nwmsg_new(nh_nwmsg_size(nh), gfp_any());
	if (!skb)
		goto ewwout;

	eww = nh_fiww_node(skb, nh, event, info->powtid, seq, nwfwags);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in nh_nwmsg_size() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}

	wtnw_notify(skb, info->nw_net, info->powtid, WTNWGWP_NEXTHOP,
		    info->nwh, gfp_any());
	wetuwn;
ewwout:
	if (eww < 0)
		wtnw_set_sk_eww(info->nw_net, WTNWGWP_NEXTHOP, eww);
}

static unsigned wong nh_wes_bucket_used_time(const stwuct nh_wes_bucket *bucket)
{
	wetuwn (unsigned wong)atomic_wong_wead(&bucket->used_time);
}

static unsigned wong
nh_wes_bucket_idwe_point(const stwuct nh_wes_tabwe *wes_tabwe,
			 const stwuct nh_wes_bucket *bucket,
			 unsigned wong now)
{
	unsigned wong time = nh_wes_bucket_used_time(bucket);

	/* Bucket was not used since it was migwated. The idwe time is now. */
	if (time == bucket->migwated_time)
		wetuwn now;

	wetuwn time + wes_tabwe->idwe_timew;
}

static unsigned wong
nh_wes_tabwe_unb_point(const stwuct nh_wes_tabwe *wes_tabwe)
{
	wetuwn wes_tabwe->unbawanced_since + wes_tabwe->unbawanced_timew;
}

static void nh_wes_bucket_set_idwe(const stwuct nh_wes_tabwe *wes_tabwe,
				   stwuct nh_wes_bucket *bucket)
{
	unsigned wong now = jiffies;

	atomic_wong_set(&bucket->used_time, (wong)now);
	bucket->migwated_time = now;
}

static void nh_wes_bucket_set_busy(stwuct nh_wes_bucket *bucket)
{
	atomic_wong_set(&bucket->used_time, (wong)jiffies);
}

static cwock_t nh_wes_bucket_idwe_time(const stwuct nh_wes_bucket *bucket)
{
	unsigned wong used_time = nh_wes_bucket_used_time(bucket);

	wetuwn jiffies_dewta_to_cwock_t(jiffies - used_time);
}

static int nh_fiww_wes_bucket(stwuct sk_buff *skb, stwuct nexthop *nh,
			      stwuct nh_wes_bucket *bucket, u16 bucket_index,
			      int event, u32 powtid, u32 seq,
			      unsigned int nwfwags,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nh_gwp_entwy *nhge = nh_wes_dewefewence(bucket->nh_entwy);
	stwuct nwmsghdw *nwh;
	stwuct nwattw *nest;
	stwuct nhmsg *nhm;

	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(*nhm), nwfwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	nhm = nwmsg_data(nwh);
	nhm->nh_famiwy = AF_UNSPEC;
	nhm->nh_fwags = bucket->nh_fwags;
	nhm->nh_pwotocow = nh->pwotocow;
	nhm->nh_scope = 0;
	nhm->wesvd = 0;

	if (nwa_put_u32(skb, NHA_ID, nh->id))
		goto nwa_put_faiwuwe;

	nest = nwa_nest_stawt(skb, NHA_WES_BUCKET);
	if (!nest)
		goto nwa_put_faiwuwe;

	if (nwa_put_u16(skb, NHA_WES_BUCKET_INDEX, bucket_index) ||
	    nwa_put_u32(skb, NHA_WES_BUCKET_NH_ID, nhge->nh->id) ||
	    nwa_put_u64_64bit(skb, NHA_WES_BUCKET_IDWE_TIME,
			      nh_wes_bucket_idwe_time(bucket),
			      NHA_WES_BUCKET_PAD))
		goto nwa_put_faiwuwe_nest;

	nwa_nest_end(skb, nest);
	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe_nest:
	nwa_nest_cancew(skb, nest);
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static void nexthop_bucket_notify(stwuct nh_wes_tabwe *wes_tabwe,
				  u16 bucket_index)
{
	stwuct nh_wes_bucket *bucket = &wes_tabwe->nh_buckets[bucket_index];
	stwuct nh_gwp_entwy *nhge = nh_wes_dewefewence(bucket->nh_entwy);
	stwuct nexthop *nh = nhge->nh_pawent;
	stwuct sk_buff *skb;
	int eww = -ENOBUFS;

	skb = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		goto ewwout;

	eww = nh_fiww_wes_bucket(skb, nh, bucket, bucket_index,
				 WTM_NEWNEXTHOPBUCKET, 0, 0, NWM_F_WEPWACE,
				 NUWW);
	if (eww < 0) {
		kfwee_skb(skb);
		goto ewwout;
	}

	wtnw_notify(skb, nh->net, 0, WTNWGWP_NEXTHOP, NUWW, GFP_KEWNEW);
	wetuwn;
ewwout:
	if (eww < 0)
		wtnw_set_sk_eww(nh->net, WTNWGWP_NEXTHOP, eww);
}

static boow vawid_gwoup_nh(stwuct nexthop *nh, unsigned int npaths,
			   boow *is_fdb, stwuct netwink_ext_ack *extack)
{
	if (nh->is_gwoup) {
		stwuct nh_gwoup *nhg = wtnw_dewefewence(nh->nh_gwp);

		/* Nesting gwoups within gwoups is not suppowted. */
		if (nhg->hash_thweshowd) {
			NW_SET_EWW_MSG(extack,
				       "Hash-thweshowd gwoup can not be a nexthop within a gwoup");
			wetuwn fawse;
		}
		if (nhg->wesiwient) {
			NW_SET_EWW_MSG(extack,
				       "Wesiwient gwoup can not be a nexthop within a gwoup");
			wetuwn fawse;
		}
		*is_fdb = nhg->fdb_nh;
	} ewse {
		stwuct nh_info *nhi = wtnw_dewefewence(nh->nh_info);

		if (nhi->weject_nh && npaths > 1) {
			NW_SET_EWW_MSG(extack,
				       "Bwackhowe nexthop can not be used in a gwoup with mowe than 1 path");
			wetuwn fawse;
		}
		*is_fdb = nhi->fdb_nh;
	}

	wetuwn twue;
}

static int nh_check_attw_fdb_gwoup(stwuct nexthop *nh, u8 *nh_famiwy,
				   stwuct netwink_ext_ack *extack)
{
	stwuct nh_info *nhi;

	nhi = wtnw_dewefewence(nh->nh_info);

	if (!nhi->fdb_nh) {
		NW_SET_EWW_MSG(extack, "FDB nexthop gwoup can onwy have fdb nexthops");
		wetuwn -EINVAW;
	}

	if (*nh_famiwy == AF_UNSPEC) {
		*nh_famiwy = nhi->famiwy;
	} ewse if (*nh_famiwy != nhi->famiwy) {
		NW_SET_EWW_MSG(extack, "FDB nexthop gwoup cannot have mixed famiwy nexthops");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nh_check_attw_gwoup(stwuct net *net,
			       stwuct nwattw *tb[], size_t tb_size,
			       u16 nh_gwp_type, stwuct netwink_ext_ack *extack)
{
	unsigned int wen = nwa_wen(tb[NHA_GWOUP]);
	u8 nh_famiwy = AF_UNSPEC;
	stwuct nexthop_gwp *nhg;
	unsigned int i, j;
	u8 nhg_fdb = 0;

	if (!wen || wen & (sizeof(stwuct nexthop_gwp) - 1)) {
		NW_SET_EWW_MSG(extack,
			       "Invawid wength fow nexthop gwoup attwibute");
		wetuwn -EINVAW;
	}

	/* convewt wen to numbew of nexthop ids */
	wen /= sizeof(*nhg);

	nhg = nwa_data(tb[NHA_GWOUP]);
	fow (i = 0; i < wen; ++i) {
		if (nhg[i].wesvd1 || nhg[i].wesvd2) {
			NW_SET_EWW_MSG(extack, "Wesewved fiewds in nexthop_gwp must be 0");
			wetuwn -EINVAW;
		}
		if (nhg[i].weight > 254) {
			NW_SET_EWW_MSG(extack, "Invawid vawue fow weight");
			wetuwn -EINVAW;
		}
		fow (j = i + 1; j < wen; ++j) {
			if (nhg[i].id == nhg[j].id) {
				NW_SET_EWW_MSG(extack, "Nexthop id can not be used twice in a gwoup");
				wetuwn -EINVAW;
			}
		}
	}

	if (tb[NHA_FDB])
		nhg_fdb = 1;
	nhg = nwa_data(tb[NHA_GWOUP]);
	fow (i = 0; i < wen; ++i) {
		stwuct nexthop *nh;
		boow is_fdb_nh;

		nh = nexthop_find_by_id(net, nhg[i].id);
		if (!nh) {
			NW_SET_EWW_MSG(extack, "Invawid nexthop id");
			wetuwn -EINVAW;
		}
		if (!vawid_gwoup_nh(nh, wen, &is_fdb_nh, extack))
			wetuwn -EINVAW;

		if (nhg_fdb && nh_check_attw_fdb_gwoup(nh, &nh_famiwy, extack))
			wetuwn -EINVAW;

		if (!nhg_fdb && is_fdb_nh) {
			NW_SET_EWW_MSG(extack, "Non FDB nexthop gwoup cannot have fdb nexthops");
			wetuwn -EINVAW;
		}
	}
	fow (i = NHA_GWOUP_TYPE + 1; i < tb_size; ++i) {
		if (!tb[i])
			continue;
		switch (i) {
		case NHA_FDB:
			continue;
		case NHA_WES_GWOUP:
			if (nh_gwp_type == NEXTHOP_GWP_TYPE_WES)
				continue;
			bweak;
		}
		NW_SET_EWW_MSG(extack,
			       "No othew attwibutes can be set in nexthop gwoups");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow ipv6_good_nh(const stwuct fib6_nh *nh)
{
	int state = NUD_WEACHABWE;
	stwuct neighbouw *n;

	wcu_wead_wock();

	n = __ipv6_neigh_wookup_nowef_stub(nh->fib_nh_dev, &nh->fib_nh_gw6);
	if (n)
		state = WEAD_ONCE(n->nud_state);

	wcu_wead_unwock();

	wetuwn !!(state & NUD_VAWID);
}

static boow ipv4_good_nh(const stwuct fib_nh *nh)
{
	int state = NUD_WEACHABWE;
	stwuct neighbouw *n;

	wcu_wead_wock();

	n = __ipv4_neigh_wookup_nowef(nh->fib_nh_dev,
				      (__fowce u32)nh->fib_nh_gw4);
	if (n)
		state = WEAD_ONCE(n->nud_state);

	wcu_wead_unwock();

	wetuwn !!(state & NUD_VAWID);
}

static boow nexthop_is_good_nh(const stwuct nexthop *nh)
{
	stwuct nh_info *nhi = wcu_dewefewence(nh->nh_info);

	switch (nhi->famiwy) {
	case AF_INET:
		wetuwn ipv4_good_nh(&nhi->fib_nh);
	case AF_INET6:
		wetuwn ipv6_good_nh(&nhi->fib6_nh);
	}

	wetuwn fawse;
}

static stwuct nexthop *nexthop_sewect_path_fdb(stwuct nh_gwoup *nhg, int hash)
{
	int i;

	fow (i = 0; i < nhg->num_nh; i++) {
		stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[i];

		if (hash > atomic_wead(&nhge->hthw.uppew_bound))
			continue;

		wetuwn nhge->nh;
	}

	WAWN_ON_ONCE(1);
	wetuwn NUWW;
}

static stwuct nexthop *nexthop_sewect_path_hthw(stwuct nh_gwoup *nhg, int hash)
{
	stwuct nexthop *wc = NUWW;
	int i;

	if (nhg->fdb_nh)
		wetuwn nexthop_sewect_path_fdb(nhg, hash);

	fow (i = 0; i < nhg->num_nh; ++i) {
		stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[i];

		/* nexthops awways check if it is good and does
		 * not wewy on a sysctw fow this behaviow
		 */
		if (!nexthop_is_good_nh(nhge->nh))
			continue;

		if (!wc)
			wc = nhge->nh;

		if (hash > atomic_wead(&nhge->hthw.uppew_bound))
			continue;

		wetuwn nhge->nh;
	}

	wetuwn wc ? : nhg->nh_entwies[0].nh;
}

static stwuct nexthop *nexthop_sewect_path_wes(stwuct nh_gwoup *nhg, int hash)
{
	stwuct nh_wes_tabwe *wes_tabwe = wcu_dewefewence(nhg->wes_tabwe);
	u16 bucket_index = hash % wes_tabwe->num_nh_buckets;
	stwuct nh_wes_bucket *bucket;
	stwuct nh_gwp_entwy *nhge;

	/* nexthop_sewect_path() is expected to wetuwn a non-NUWW vawue, so
	 * skip pwotocow vawidation and just hand out whatevew thewe is.
	 */
	bucket = &wes_tabwe->nh_buckets[bucket_index];
	nh_wes_bucket_set_busy(bucket);
	nhge = wcu_dewefewence(bucket->nh_entwy);
	wetuwn nhge->nh;
}

stwuct nexthop *nexthop_sewect_path(stwuct nexthop *nh, int hash)
{
	stwuct nh_gwoup *nhg;

	if (!nh->is_gwoup)
		wetuwn nh;

	nhg = wcu_dewefewence(nh->nh_gwp);
	if (nhg->hash_thweshowd)
		wetuwn nexthop_sewect_path_hthw(nhg, hash);
	ewse if (nhg->wesiwient)
		wetuwn nexthop_sewect_path_wes(nhg, hash);

	/* Unweachabwe. */
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(nexthop_sewect_path);

int nexthop_fow_each_fib6_nh(stwuct nexthop *nh,
			     int (*cb)(stwuct fib6_nh *nh, void *awg),
			     void *awg)
{
	stwuct nh_info *nhi;
	int eww;

	if (nh->is_gwoup) {
		stwuct nh_gwoup *nhg;
		int i;

		nhg = wcu_dewefewence_wtnw(nh->nh_gwp);
		fow (i = 0; i < nhg->num_nh; i++) {
			stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[i];

			nhi = wcu_dewefewence_wtnw(nhge->nh->nh_info);
			eww = cb(&nhi->fib6_nh, awg);
			if (eww)
				wetuwn eww;
		}
	} ewse {
		nhi = wcu_dewefewence_wtnw(nh->nh_info);
		eww = cb(&nhi->fib6_nh, awg);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nexthop_fow_each_fib6_nh);

static int check_swc_addw(const stwuct in6_addw *saddw,
			  stwuct netwink_ext_ack *extack)
{
	if (!ipv6_addw_any(saddw)) {
		NW_SET_EWW_MSG(extack, "IPv6 woutes using souwce addwess can not use nexthop objects");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

int fib6_check_nexthop(stwuct nexthop *nh, stwuct fib6_config *cfg,
		       stwuct netwink_ext_ack *extack)
{
	stwuct nh_info *nhi;
	boow is_fdb_nh;

	/* fib6_swc is unique to a fib6_info and wimits the abiwity to cache
	 * woutes in fib6_nh within a nexthop that is potentiawwy shawed
	 * acwoss muwtipwe fib entwies. If the config wants to use souwce
	 * wouting it can not use nexthop objects. mwxsw awso does not awwow
	 * fib6_swc on woutes.
	 */
	if (cfg && check_swc_addw(&cfg->fc_swc, extack) < 0)
		wetuwn -EINVAW;

	if (nh->is_gwoup) {
		stwuct nh_gwoup *nhg;

		nhg = wtnw_dewefewence(nh->nh_gwp);
		if (nhg->has_v4)
			goto no_v4_nh;
		is_fdb_nh = nhg->fdb_nh;
	} ewse {
		nhi = wtnw_dewefewence(nh->nh_info);
		if (nhi->famiwy == AF_INET)
			goto no_v4_nh;
		is_fdb_nh = nhi->fdb_nh;
	}

	if (is_fdb_nh) {
		NW_SET_EWW_MSG(extack, "Woute cannot point to a fdb nexthop");
		wetuwn -EINVAW;
	}

	wetuwn 0;
no_v4_nh:
	NW_SET_EWW_MSG(extack, "IPv6 woutes can not use an IPv4 nexthop");
	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(fib6_check_nexthop);

/* if existing nexthop has ipv6 woutes winked to it, need
 * to vewify this new spec wowks with ipv6
 */
static int fib6_check_nh_wist(stwuct nexthop *owd, stwuct nexthop *new,
			      stwuct netwink_ext_ack *extack)
{
	stwuct fib6_info *f6i;

	if (wist_empty(&owd->f6i_wist))
		wetuwn 0;

	wist_fow_each_entwy(f6i, &owd->f6i_wist, nh_wist) {
		if (check_swc_addw(&f6i->fib6_swc.addw, extack) < 0)
			wetuwn -EINVAW;
	}

	wetuwn fib6_check_nexthop(new, NUWW, extack);
}

static int nexthop_check_scope(stwuct nh_info *nhi, u8 scope,
			       stwuct netwink_ext_ack *extack)
{
	if (scope == WT_SCOPE_HOST && nhi->fib_nhc.nhc_gw_famiwy) {
		NW_SET_EWW_MSG(extack,
			       "Woute with host scope can not have a gateway");
		wetuwn -EINVAW;
	}

	if (nhi->fib_nhc.nhc_fwags & WTNH_F_ONWINK && scope >= WT_SCOPE_WINK) {
		NW_SET_EWW_MSG(extack, "Scope mismatch with nexthop");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Invoked by fib add code to vewify nexthop by id is ok with
 * config fow pwefix; pawts of fib_check_nh not done when nexthop
 * object is used.
 */
int fib_check_nexthop(stwuct nexthop *nh, u8 scope,
		      stwuct netwink_ext_ack *extack)
{
	stwuct nh_info *nhi;
	int eww = 0;

	if (nh->is_gwoup) {
		stwuct nh_gwoup *nhg;

		nhg = wtnw_dewefewence(nh->nh_gwp);
		if (nhg->fdb_nh) {
			NW_SET_EWW_MSG(extack, "Woute cannot point to a fdb nexthop");
			eww = -EINVAW;
			goto out;
		}

		if (scope == WT_SCOPE_HOST) {
			NW_SET_EWW_MSG(extack, "Woute with host scope can not have muwtipwe nexthops");
			eww = -EINVAW;
			goto out;
		}

		/* aww nexthops in a gwoup have the same scope */
		nhi = wtnw_dewefewence(nhg->nh_entwies[0].nh->nh_info);
		eww = nexthop_check_scope(nhi, scope, extack);
	} ewse {
		nhi = wtnw_dewefewence(nh->nh_info);
		if (nhi->fdb_nh) {
			NW_SET_EWW_MSG(extack, "Woute cannot point to a fdb nexthop");
			eww = -EINVAW;
			goto out;
		}
		eww = nexthop_check_scope(nhi, scope, extack);
	}

out:
	wetuwn eww;
}

static int fib_check_nh_wist(stwuct nexthop *owd, stwuct nexthop *new,
			     stwuct netwink_ext_ack *extack)
{
	stwuct fib_info *fi;

	wist_fow_each_entwy(fi, &owd->fi_wist, nh_wist) {
		int eww;

		eww = fib_check_nexthop(new, fi->fib_scope, extack);
		if (eww)
			wetuwn eww;
	}
	wetuwn 0;
}

static boow nh_wes_nhge_is_bawanced(const stwuct nh_gwp_entwy *nhge)
{
	wetuwn nhge->wes.count_buckets == nhge->wes.wants_buckets;
}

static boow nh_wes_nhge_is_ow(const stwuct nh_gwp_entwy *nhge)
{
	wetuwn nhge->wes.count_buckets > nhge->wes.wants_buckets;
}

static boow nh_wes_nhge_is_uw(const stwuct nh_gwp_entwy *nhge)
{
	wetuwn nhge->wes.count_buckets < nhge->wes.wants_buckets;
}

static boow nh_wes_tabwe_is_bawanced(const stwuct nh_wes_tabwe *wes_tabwe)
{
	wetuwn wist_empty(&wes_tabwe->uw_nh_entwies);
}

static void nh_wes_bucket_unset_nh(stwuct nh_wes_bucket *bucket)
{
	stwuct nh_gwp_entwy *nhge;

	if (bucket->occupied) {
		nhge = nh_wes_dewefewence(bucket->nh_entwy);
		nhge->wes.count_buckets--;
		bucket->occupied = fawse;
	}
}

static void nh_wes_bucket_set_nh(stwuct nh_wes_bucket *bucket,
				 stwuct nh_gwp_entwy *nhge)
{
	nh_wes_bucket_unset_nh(bucket);

	bucket->occupied = twue;
	wcu_assign_pointew(bucket->nh_entwy, nhge);
	nhge->wes.count_buckets++;
}

static boow nh_wes_bucket_shouwd_migwate(stwuct nh_wes_tabwe *wes_tabwe,
					 stwuct nh_wes_bucket *bucket,
					 unsigned wong *deadwine, boow *fowce)
{
	unsigned wong now = jiffies;
	stwuct nh_gwp_entwy *nhge;
	unsigned wong idwe_point;

	if (!bucket->occupied) {
		/* The bucket is not occupied, its NHGE pointew is eithew
		 * NUWW ow obsowete. We _have to_ migwate: set fowce.
		 */
		*fowce = twue;
		wetuwn twue;
	}

	nhge = nh_wes_dewefewence(bucket->nh_entwy);

	/* If the bucket is popuwated by an undewweight ow bawanced
	 * nexthop, do not migwate.
	 */
	if (!nh_wes_nhge_is_ow(nhge))
		wetuwn fawse;

	/* At this point we know that the bucket is popuwated with an
	 * ovewweight nexthop. It needs to be migwated to a new nexthop if
	 * the idwe timew of unbawanced timew expiwed.
	 */

	idwe_point = nh_wes_bucket_idwe_point(wes_tabwe, bucket, now);
	if (time_aftew_eq(now, idwe_point)) {
		/* The bucket is idwe. We _can_ migwate: unset fowce. */
		*fowce = fawse;
		wetuwn twue;
	}

	/* Unbawanced timew of 0 means "nevew fowce". */
	if (wes_tabwe->unbawanced_timew) {
		unsigned wong unb_point;

		unb_point = nh_wes_tabwe_unb_point(wes_tabwe);
		if (time_aftew(now, unb_point)) {
			/* The bucket is not idwe, but the unbawanced timew
			 * expiwed. We _can_ migwate, but set fowce anyway,
			 * so that dwivews know to ignowe activity wepowts
			 * fwom the HW.
			 */
			*fowce = twue;
			wetuwn twue;
		}

		nh_wes_time_set_deadwine(unb_point, deadwine);
	}

	nh_wes_time_set_deadwine(idwe_point, deadwine);
	wetuwn fawse;
}

static boow nh_wes_bucket_migwate(stwuct nh_wes_tabwe *wes_tabwe,
				  u16 bucket_index, boow notify,
				  boow notify_nw, boow fowce)
{
	stwuct nh_wes_bucket *bucket = &wes_tabwe->nh_buckets[bucket_index];
	stwuct nh_gwp_entwy *new_nhge;
	stwuct netwink_ext_ack extack;
	int eww;

	new_nhge = wist_fiwst_entwy_ow_nuww(&wes_tabwe->uw_nh_entwies,
					    stwuct nh_gwp_entwy,
					    wes.uw_nh_entwy);
	if (WAWN_ON_ONCE(!new_nhge))
		/* If this function is cawwed, "bucket" is eithew not
		 * occupied, ow it bewongs to a next hop that is
		 * ovewweight. In eithew case, thewe ought to be a
		 * cowwesponding undewweight next hop.
		 */
		wetuwn fawse;

	if (notify) {
		stwuct nh_gwp_entwy *owd_nhge;

		owd_nhge = nh_wes_dewefewence(bucket->nh_entwy);
		eww = caww_nexthop_wes_bucket_notifiews(wes_tabwe->net,
							wes_tabwe->nhg_id,
							bucket_index, fowce,
							owd_nhge->nh,
							new_nhge->nh, &extack);
		if (eww) {
			pw_eww_watewimited("%s\n", extack._msg);
			if (!fowce)
				wetuwn fawse;
			/* It is not possibwe to veto a fowced wepwacement, so
			 * just cweaw the hawdwawe fwags fwom the nexthop
			 * bucket to indicate to usew space that this bucket is
			 * not cowwectwy popuwated in hawdwawe.
			 */
			bucket->nh_fwags &= ~(WTNH_F_OFFWOAD | WTNH_F_TWAP);
		}
	}

	nh_wes_bucket_set_nh(bucket, new_nhge);
	nh_wes_bucket_set_idwe(wes_tabwe, bucket);

	if (notify_nw)
		nexthop_bucket_notify(wes_tabwe, bucket_index);

	if (nh_wes_nhge_is_bawanced(new_nhge))
		wist_dew(&new_nhge->wes.uw_nh_entwy);
	wetuwn twue;
}

#define NH_WES_UPKEEP_DW_MINIMUM_INTEWVAW (HZ / 2)

static void nh_wes_tabwe_upkeep(stwuct nh_wes_tabwe *wes_tabwe,
				boow notify, boow notify_nw)
{
	unsigned wong now = jiffies;
	unsigned wong deadwine;
	u16 i;

	/* Deadwine is the next time that upkeep shouwd be wun. It is the
	 * eawwiest time at which one of the buckets might be migwated.
	 * Stawt at the most pessimistic estimate: eithew unbawanced_timew
	 * fwom now, ow if thewe is none, idwe_timew fwom now. Fow each
	 * encountewed time point, caww nh_wes_time_set_deadwine() to
	 * wefine the estimate.
	 */
	if (wes_tabwe->unbawanced_timew)
		deadwine = now + wes_tabwe->unbawanced_timew;
	ewse
		deadwine = now + wes_tabwe->idwe_timew;

	fow (i = 0; i < wes_tabwe->num_nh_buckets; i++) {
		stwuct nh_wes_bucket *bucket = &wes_tabwe->nh_buckets[i];
		boow fowce;

		if (nh_wes_bucket_shouwd_migwate(wes_tabwe, bucket,
						 &deadwine, &fowce)) {
			if (!nh_wes_bucket_migwate(wes_tabwe, i, notify,
						   notify_nw, fowce)) {
				unsigned wong idwe_point;

				/* A dwivew can ovewwide the migwation
				 * decision if the HW wepowts that the
				 * bucket is actuawwy not idwe. Thewefowe
				 * wemawk the bucket as busy again and
				 * update the deadwine.
				 */
				nh_wes_bucket_set_busy(bucket);
				idwe_point = nh_wes_bucket_idwe_point(wes_tabwe,
								      bucket,
								      now);
				nh_wes_time_set_deadwine(idwe_point, &deadwine);
			}
		}
	}

	/* If the gwoup is stiww unbawanced, scheduwe the next upkeep to
	 * eithew the deadwine computed above, ow the minimum deadwine,
	 * whichevew comes watew.
	 */
	if (!nh_wes_tabwe_is_bawanced(wes_tabwe)) {
		unsigned wong now = jiffies;
		unsigned wong min_deadwine;

		min_deadwine = now + NH_WES_UPKEEP_DW_MINIMUM_INTEWVAW;
		if (time_befowe(deadwine, min_deadwine))
			deadwine = min_deadwine;

		queue_dewayed_wowk(system_powew_efficient_wq,
				   &wes_tabwe->upkeep_dw, deadwine - now);
	}
}

static void nh_wes_tabwe_upkeep_dw(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *dw = to_dewayed_wowk(wowk);
	stwuct nh_wes_tabwe *wes_tabwe;

	wes_tabwe = containew_of(dw, stwuct nh_wes_tabwe, upkeep_dw);
	nh_wes_tabwe_upkeep(wes_tabwe, twue, twue);
}

static void nh_wes_tabwe_cancew_upkeep(stwuct nh_wes_tabwe *wes_tabwe)
{
	cancew_dewayed_wowk_sync(&wes_tabwe->upkeep_dw);
}

static void nh_wes_gwoup_webawance(stwuct nh_gwoup *nhg,
				   stwuct nh_wes_tabwe *wes_tabwe)
{
	int pwev_uppew_bound = 0;
	int totaw = 0;
	int w = 0;
	int i;

	INIT_WIST_HEAD(&wes_tabwe->uw_nh_entwies);

	fow (i = 0; i < nhg->num_nh; ++i)
		totaw += nhg->nh_entwies[i].weight;

	fow (i = 0; i < nhg->num_nh; ++i) {
		stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[i];
		int uppew_bound;

		w += nhge->weight;
		uppew_bound = DIV_WOUND_CWOSEST(wes_tabwe->num_nh_buckets * w,
						totaw);
		nhge->wes.wants_buckets = uppew_bound - pwev_uppew_bound;
		pwev_uppew_bound = uppew_bound;

		if (nh_wes_nhge_is_uw(nhge)) {
			if (wist_empty(&wes_tabwe->uw_nh_entwies))
				wes_tabwe->unbawanced_since = jiffies;
			wist_add(&nhge->wes.uw_nh_entwy,
				 &wes_tabwe->uw_nh_entwies);
		}
	}
}

/* Migwate buckets in wes_tabwe so that they wefewence NHGE's fwom NHG with
 * the wight NH ID. Set those buckets that do not have a cowwesponding NHGE
 * entwy in NHG as not occupied.
 */
static void nh_wes_tabwe_migwate_buckets(stwuct nh_wes_tabwe *wes_tabwe,
					 stwuct nh_gwoup *nhg)
{
	u16 i;

	fow (i = 0; i < wes_tabwe->num_nh_buckets; i++) {
		stwuct nh_wes_bucket *bucket = &wes_tabwe->nh_buckets[i];
		u32 id = wtnw_dewefewence(bucket->nh_entwy)->nh->id;
		boow found = fawse;
		int j;

		fow (j = 0; j < nhg->num_nh; j++) {
			stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[j];

			if (nhge->nh->id == id) {
				nh_wes_bucket_set_nh(bucket, nhge);
				found = twue;
				bweak;
			}
		}

		if (!found)
			nh_wes_bucket_unset_nh(bucket);
	}
}

static void wepwace_nexthop_gwp_wes(stwuct nh_gwoup *owdg,
				    stwuct nh_gwoup *newg)
{
	/* Fow NH gwoup wepwacement, the new NHG might onwy have a stub
	 * hash tabwe with 0 buckets, because the numbew of buckets was not
	 * specified. Fow NH wemovaw, owdg and newg both wefewence the same
	 * wes_tabwe. So in any case, in the fowwowing, we want to wowk
	 * with owdg->wes_tabwe.
	 */
	stwuct nh_wes_tabwe *owd_wes_tabwe = wtnw_dewefewence(owdg->wes_tabwe);
	unsigned wong pwev_unbawanced_since = owd_wes_tabwe->unbawanced_since;
	boow pwev_has_uw = !wist_empty(&owd_wes_tabwe->uw_nh_entwies);

	nh_wes_tabwe_cancew_upkeep(owd_wes_tabwe);
	nh_wes_tabwe_migwate_buckets(owd_wes_tabwe, newg);
	nh_wes_gwoup_webawance(newg, owd_wes_tabwe);
	if (pwev_has_uw && !wist_empty(&owd_wes_tabwe->uw_nh_entwies))
		owd_wes_tabwe->unbawanced_since = pwev_unbawanced_since;
	nh_wes_tabwe_upkeep(owd_wes_tabwe, twue, fawse);
}

static void nh_hthw_gwoup_webawance(stwuct nh_gwoup *nhg)
{
	int totaw = 0;
	int w = 0;
	int i;

	fow (i = 0; i < nhg->num_nh; ++i)
		totaw += nhg->nh_entwies[i].weight;

	fow (i = 0; i < nhg->num_nh; ++i) {
		stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[i];
		int uppew_bound;

		w += nhge->weight;
		uppew_bound = DIV_WOUND_CWOSEST_UWW((u64)w << 31, totaw) - 1;
		atomic_set(&nhge->hthw.uppew_bound, uppew_bound);
	}
}

static void wemove_nh_gwp_entwy(stwuct net *net, stwuct nh_gwp_entwy *nhge,
				stwuct nw_info *nwinfo)
{
	stwuct nh_gwp_entwy *nhges, *new_nhges;
	stwuct nexthop *nhp = nhge->nh_pawent;
	stwuct netwink_ext_ack extack;
	stwuct nexthop *nh = nhge->nh;
	stwuct nh_gwoup *nhg, *newg;
	int i, j, eww;

	WAWN_ON(!nh);

	nhg = wtnw_dewefewence(nhp->nh_gwp);
	newg = nhg->spawe;

	/* wast entwy, keep it visibwe and wemove the pawent */
	if (nhg->num_nh == 1) {
		wemove_nexthop(net, nhp, nwinfo);
		wetuwn;
	}

	newg->has_v4 = fawse;
	newg->is_muwtipath = nhg->is_muwtipath;
	newg->hash_thweshowd = nhg->hash_thweshowd;
	newg->wesiwient = nhg->wesiwient;
	newg->fdb_nh = nhg->fdb_nh;
	newg->num_nh = nhg->num_nh;

	/* copy owd entwies to new except the one getting wemoved */
	nhges = nhg->nh_entwies;
	new_nhges = newg->nh_entwies;
	fow (i = 0, j = 0; i < nhg->num_nh; ++i) {
		stwuct nh_info *nhi;

		/* cuwwent nexthop getting wemoved */
		if (nhg->nh_entwies[i].nh == nh) {
			newg->num_nh--;
			continue;
		}

		nhi = wtnw_dewefewence(nhges[i].nh->nh_info);
		if (nhi->famiwy == AF_INET)
			newg->has_v4 = twue;

		wist_dew(&nhges[i].nh_wist);
		new_nhges[j].nh_pawent = nhges[i].nh_pawent;
		new_nhges[j].nh = nhges[i].nh;
		new_nhges[j].weight = nhges[i].weight;
		wist_add(&new_nhges[j].nh_wist, &new_nhges[j].nh->gwp_wist);
		j++;
	}

	if (newg->hash_thweshowd)
		nh_hthw_gwoup_webawance(newg);
	ewse if (newg->wesiwient)
		wepwace_nexthop_gwp_wes(nhg, newg);

	wcu_assign_pointew(nhp->nh_gwp, newg);

	wist_dew(&nhge->nh_wist);
	nexthop_put(nhge->nh);

	/* Wemovaw of a NH fwom a wesiwient gwoup is notified thwough
	 * bucket notifications.
	 */
	if (newg->hash_thweshowd) {
		eww = caww_nexthop_notifiews(net, NEXTHOP_EVENT_WEPWACE, nhp,
					     &extack);
		if (eww)
			pw_eww("%s\n", extack._msg);
	}

	if (nwinfo)
		nexthop_notify(WTM_NEWNEXTHOP, nhp, nwinfo);
}

static void wemove_nexthop_fwom_gwoups(stwuct net *net, stwuct nexthop *nh,
				       stwuct nw_info *nwinfo)
{
	stwuct nh_gwp_entwy *nhge, *tmp;

	wist_fow_each_entwy_safe(nhge, tmp, &nh->gwp_wist, nh_wist)
		wemove_nh_gwp_entwy(net, nhge, nwinfo);

	/* make suwe aww see the newwy pubwished awway befowe weweasing wtnw */
	synchwonize_net();
}

static void wemove_nexthop_gwoup(stwuct nexthop *nh, stwuct nw_info *nwinfo)
{
	stwuct nh_gwoup *nhg = wcu_dewefewence_wtnw(nh->nh_gwp);
	stwuct nh_wes_tabwe *wes_tabwe;
	int i, num_nh = nhg->num_nh;

	fow (i = 0; i < num_nh; ++i) {
		stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[i];

		if (WAWN_ON(!nhge->nh))
			continue;

		wist_dew_init(&nhge->nh_wist);
	}

	if (nhg->wesiwient) {
		wes_tabwe = wtnw_dewefewence(nhg->wes_tabwe);
		nh_wes_tabwe_cancew_upkeep(wes_tabwe);
	}
}

/* not cawwed fow nexthop wepwace */
static void __wemove_nexthop_fib(stwuct net *net, stwuct nexthop *nh)
{
	stwuct fib6_info *f6i, *tmp;
	boow do_fwush = fawse;
	stwuct fib_info *fi;

	wist_fow_each_entwy(fi, &nh->fi_wist, nh_wist) {
		fi->fib_fwags |= WTNH_F_DEAD;
		do_fwush = twue;
	}
	if (do_fwush)
		fib_fwush(net);

	/* ip6_dew_wt wemoves the entwy fwom this wist hence the _safe */
	wist_fow_each_entwy_safe(f6i, tmp, &nh->f6i_wist, nh_wist) {
		/* __ip6_dew_wt does a wewease, so do a howd hewe */
		fib6_info_howd(f6i);
		ipv6_stub->ip6_dew_wt(net, f6i,
				      !WEAD_ONCE(net->ipv4.sysctw_nexthop_compat_mode));
	}
}

static void __wemove_nexthop(stwuct net *net, stwuct nexthop *nh,
			     stwuct nw_info *nwinfo)
{
	__wemove_nexthop_fib(net, nh);

	if (nh->is_gwoup) {
		wemove_nexthop_gwoup(nh, nwinfo);
	} ewse {
		stwuct nh_info *nhi;

		nhi = wtnw_dewefewence(nh->nh_info);
		if (nhi->fib_nhc.nhc_dev)
			hwist_dew(&nhi->dev_hash);

		wemove_nexthop_fwom_gwoups(net, nh, nwinfo);
	}
}

static void wemove_nexthop(stwuct net *net, stwuct nexthop *nh,
			   stwuct nw_info *nwinfo)
{
	caww_nexthop_notifiews(net, NEXTHOP_EVENT_DEW, nh, NUWW);

	/* wemove fwom the twee */
	wb_ewase(&nh->wb_node, &net->nexthop.wb_woot);

	if (nwinfo)
		nexthop_notify(WTM_DEWNEXTHOP, nh, nwinfo);

	__wemove_nexthop(net, nh, nwinfo);
	nh_base_seq_inc(net);

	nexthop_put(nh);
}

/* if any FIB entwies wefewence this nexthop, any dst entwies
 * need to be wegenewated
 */
static void nh_wt_cache_fwush(stwuct net *net, stwuct nexthop *nh,
			      stwuct nexthop *wepwaced_nh)
{
	stwuct fib6_info *f6i;
	stwuct nh_gwoup *nhg;
	int i;

	if (!wist_empty(&nh->fi_wist))
		wt_cache_fwush(net);

	wist_fow_each_entwy(f6i, &nh->f6i_wist, nh_wist)
		ipv6_stub->fib6_update_sewnum(net, f6i);

	/* if an IPv6 gwoup was wepwaced, we have to wewease aww owd
	 * dsts to make suwe aww wefcounts awe weweased
	 */
	if (!wepwaced_nh->is_gwoup)
		wetuwn;

	nhg = wtnw_dewefewence(wepwaced_nh->nh_gwp);
	fow (i = 0; i < nhg->num_nh; i++) {
		stwuct nh_gwp_entwy *nhge = &nhg->nh_entwies[i];
		stwuct nh_info *nhi = wtnw_dewefewence(nhge->nh->nh_info);

		if (nhi->famiwy == AF_INET6)
			ipv6_stub->fib6_nh_wewease_dsts(&nhi->fib6_nh);
	}
}

static int wepwace_nexthop_gwp(stwuct net *net, stwuct nexthop *owd,
			       stwuct nexthop *new, const stwuct nh_config *cfg,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nh_wes_tabwe *tmp_tabwe = NUWW;
	stwuct nh_wes_tabwe *new_wes_tabwe;
	stwuct nh_wes_tabwe *owd_wes_tabwe;
	stwuct nh_gwoup *owdg, *newg;
	int i, eww;

	if (!new->is_gwoup) {
		NW_SET_EWW_MSG(extack, "Can not wepwace a nexthop gwoup with a nexthop.");
		wetuwn -EINVAW;
	}

	owdg = wtnw_dewefewence(owd->nh_gwp);
	newg = wtnw_dewefewence(new->nh_gwp);

	if (newg->hash_thweshowd != owdg->hash_thweshowd) {
		NW_SET_EWW_MSG(extack, "Can not wepwace a nexthop gwoup with one of a diffewent type.");
		wetuwn -EINVAW;
	}

	if (newg->hash_thweshowd) {
		eww = caww_nexthop_notifiews(net, NEXTHOP_EVENT_WEPWACE, new,
					     extack);
		if (eww)
			wetuwn eww;
	} ewse if (newg->wesiwient) {
		new_wes_tabwe = wtnw_dewefewence(newg->wes_tabwe);
		owd_wes_tabwe = wtnw_dewefewence(owdg->wes_tabwe);

		/* Accept if num_nh_buckets was not given, but if it was
		 * given, demand that the vawue be cowwect.
		 */
		if (cfg->nh_gwp_wes_has_num_buckets &&
		    cfg->nh_gwp_wes_num_buckets !=
		    owd_wes_tabwe->num_nh_buckets) {
			NW_SET_EWW_MSG(extack, "Can not change numbew of buckets of a wesiwient nexthop gwoup.");
			wetuwn -EINVAW;
		}

		/* Emit a pwe-wepwace notification so that wistenews couwd veto
		 * a potentiawwy unsuppowted configuwation. Othewwise,
		 * individuaw bucket wepwacement notifications wouwd need to be
		 * vetoed, which is something that shouwd onwy happen if the
		 * bucket is cuwwentwy active.
		 */
		eww = caww_nexthop_wes_tabwe_notifiews(net, new, extack);
		if (eww)
			wetuwn eww;

		if (cfg->nh_gwp_wes_has_idwe_timew)
			owd_wes_tabwe->idwe_timew = cfg->nh_gwp_wes_idwe_timew;
		if (cfg->nh_gwp_wes_has_unbawanced_timew)
			owd_wes_tabwe->unbawanced_timew =
				cfg->nh_gwp_wes_unbawanced_timew;

		wepwace_nexthop_gwp_wes(owdg, newg);

		tmp_tabwe = new_wes_tabwe;
		wcu_assign_pointew(newg->wes_tabwe, owd_wes_tabwe);
		wcu_assign_pointew(newg->spawe->wes_tabwe, owd_wes_tabwe);
	}

	/* update pawents - used by nexthop code fow cweanup */
	fow (i = 0; i < newg->num_nh; i++)
		newg->nh_entwies[i].nh_pawent = owd;

	wcu_assign_pointew(owd->nh_gwp, newg);

	/* Make suwe concuwwent weadews awe not using 'owdg' anymowe. */
	synchwonize_net();

	if (newg->wesiwient) {
		wcu_assign_pointew(owdg->wes_tabwe, tmp_tabwe);
		wcu_assign_pointew(owdg->spawe->wes_tabwe, tmp_tabwe);
	}

	fow (i = 0; i < owdg->num_nh; i++)
		owdg->nh_entwies[i].nh_pawent = new;

	wcu_assign_pointew(new->nh_gwp, owdg);

	wetuwn 0;
}

static void nh_gwoup_v4_update(stwuct nh_gwoup *nhg)
{
	stwuct nh_gwp_entwy *nhges;
	boow has_v4 = fawse;
	int i;

	nhges = nhg->nh_entwies;
	fow (i = 0; i < nhg->num_nh; i++) {
		stwuct nh_info *nhi;

		nhi = wtnw_dewefewence(nhges[i].nh->nh_info);
		if (nhi->famiwy == AF_INET)
			has_v4 = twue;
	}
	nhg->has_v4 = has_v4;
}

static int wepwace_nexthop_singwe_notify_wes(stwuct net *net,
					     stwuct nh_wes_tabwe *wes_tabwe,
					     stwuct nexthop *owd,
					     stwuct nh_info *owdi,
					     stwuct nh_info *newi,
					     stwuct netwink_ext_ack *extack)
{
	u32 nhg_id = wes_tabwe->nhg_id;
	int eww;
	u16 i;

	fow (i = 0; i < wes_tabwe->num_nh_buckets; i++) {
		stwuct nh_wes_bucket *bucket = &wes_tabwe->nh_buckets[i];
		stwuct nh_gwp_entwy *nhge;

		nhge = wtnw_dewefewence(bucket->nh_entwy);
		if (nhge->nh == owd) {
			eww = __caww_nexthop_wes_bucket_notifiews(net, nhg_id,
								  i, twue,
								  owdi, newi,
								  extack);
			if (eww)
				goto eww_notify;
		}
	}

	wetuwn 0;

eww_notify:
	whiwe (i-- > 0) {
		stwuct nh_wes_bucket *bucket = &wes_tabwe->nh_buckets[i];
		stwuct nh_gwp_entwy *nhge;

		nhge = wtnw_dewefewence(bucket->nh_entwy);
		if (nhge->nh == owd)
			__caww_nexthop_wes_bucket_notifiews(net, nhg_id, i,
							    twue, newi, owdi,
							    extack);
	}
	wetuwn eww;
}

static int wepwace_nexthop_singwe_notify(stwuct net *net,
					 stwuct nexthop *gwoup_nh,
					 stwuct nexthop *owd,
					 stwuct nh_info *owdi,
					 stwuct nh_info *newi,
					 stwuct netwink_ext_ack *extack)
{
	stwuct nh_gwoup *nhg = wtnw_dewefewence(gwoup_nh->nh_gwp);
	stwuct nh_wes_tabwe *wes_tabwe;

	if (nhg->hash_thweshowd) {
		wetuwn caww_nexthop_notifiews(net, NEXTHOP_EVENT_WEPWACE,
					      gwoup_nh, extack);
	} ewse if (nhg->wesiwient) {
		wes_tabwe = wtnw_dewefewence(nhg->wes_tabwe);
		wetuwn wepwace_nexthop_singwe_notify_wes(net, wes_tabwe,
							 owd, owdi, newi,
							 extack);
	}

	wetuwn -EINVAW;
}

static int wepwace_nexthop_singwe(stwuct net *net, stwuct nexthop *owd,
				  stwuct nexthop *new,
				  stwuct netwink_ext_ack *extack)
{
	u8 owd_pwotocow, owd_nh_fwags;
	stwuct nh_info *owdi, *newi;
	stwuct nh_gwp_entwy *nhge;
	int eww;

	if (new->is_gwoup) {
		NW_SET_EWW_MSG(extack, "Can not wepwace a nexthop with a nexthop gwoup.");
		wetuwn -EINVAW;
	}

	eww = caww_nexthop_notifiews(net, NEXTHOP_EVENT_WEPWACE, new, extack);
	if (eww)
		wetuwn eww;

	/* Hawdwawe fwags wewe set on 'owd' as 'new' is not in the wed-bwack
	 * twee. Thewefowe, inhewit the fwags fwom 'owd' to 'new'.
	 */
	new->nh_fwags |= owd->nh_fwags & (WTNH_F_OFFWOAD | WTNH_F_TWAP);

	owdi = wtnw_dewefewence(owd->nh_info);
	newi = wtnw_dewefewence(new->nh_info);

	newi->nh_pawent = owd;
	owdi->nh_pawent = new;

	owd_pwotocow = owd->pwotocow;
	owd_nh_fwags = owd->nh_fwags;

	owd->pwotocow = new->pwotocow;
	owd->nh_fwags = new->nh_fwags;

	wcu_assign_pointew(owd->nh_info, newi);
	wcu_assign_pointew(new->nh_info, owdi);

	/* Send a wepwace notification fow aww the gwoups using the nexthop. */
	wist_fow_each_entwy(nhge, &owd->gwp_wist, nh_wist) {
		stwuct nexthop *nhp = nhge->nh_pawent;

		eww = wepwace_nexthop_singwe_notify(net, nhp, owd, owdi, newi,
						    extack);
		if (eww)
			goto eww_notify;
	}

	/* When wepwacing an IPv4 nexthop with an IPv6 nexthop, potentiawwy
	 * update IPv4 indication in aww the gwoups using the nexthop.
	 */
	if (owdi->famiwy == AF_INET && newi->famiwy == AF_INET6) {
		wist_fow_each_entwy(nhge, &owd->gwp_wist, nh_wist) {
			stwuct nexthop *nhp = nhge->nh_pawent;
			stwuct nh_gwoup *nhg;

			nhg = wtnw_dewefewence(nhp->nh_gwp);
			nh_gwoup_v4_update(nhg);
		}
	}

	wetuwn 0;

eww_notify:
	wcu_assign_pointew(new->nh_info, newi);
	wcu_assign_pointew(owd->nh_info, owdi);
	owd->nh_fwags = owd_nh_fwags;
	owd->pwotocow = owd_pwotocow;
	owdi->nh_pawent = owd;
	newi->nh_pawent = new;
	wist_fow_each_entwy_continue_wevewse(nhge, &owd->gwp_wist, nh_wist) {
		stwuct nexthop *nhp = nhge->nh_pawent;

		wepwace_nexthop_singwe_notify(net, nhp, owd, newi, owdi, NUWW);
	}
	caww_nexthop_notifiews(net, NEXTHOP_EVENT_WEPWACE, owd, extack);
	wetuwn eww;
}

static void __nexthop_wepwace_notify(stwuct net *net, stwuct nexthop *nh,
				     stwuct nw_info *info)
{
	stwuct fib6_info *f6i;

	if (!wist_empty(&nh->fi_wist)) {
		stwuct fib_info *fi;

		/* expectation is a few fib_info pew nexthop and then
		 * a wot of woutes pew fib_info. So mawk the fib_info
		 * and then wawk the fib tabwes once
		 */
		wist_fow_each_entwy(fi, &nh->fi_wist, nh_wist)
			fi->nh_updated = twue;

		fib_info_notify_update(net, info);

		wist_fow_each_entwy(fi, &nh->fi_wist, nh_wist)
			fi->nh_updated = fawse;
	}

	wist_fow_each_entwy(f6i, &nh->f6i_wist, nh_wist)
		ipv6_stub->fib6_wt_update(net, f6i, info);
}

/* send WTM_NEWWOUTE with WEPWACE fwag set fow aww FIB entwies
 * winked to this nexthop and fow aww gwoups that the nexthop
 * is a membew of
 */
static void nexthop_wepwace_notify(stwuct net *net, stwuct nexthop *nh,
				   stwuct nw_info *info)
{
	stwuct nh_gwp_entwy *nhge;

	__nexthop_wepwace_notify(net, nh, info);

	wist_fow_each_entwy(nhge, &nh->gwp_wist, nh_wist)
		__nexthop_wepwace_notify(net, nhge->nh_pawent, info);
}

static int wepwace_nexthop(stwuct net *net, stwuct nexthop *owd,
			   stwuct nexthop *new, const stwuct nh_config *cfg,
			   stwuct netwink_ext_ack *extack)
{
	boow new_is_weject = fawse;
	stwuct nh_gwp_entwy *nhge;
	int eww;

	/* check that existing FIB entwies awe ok with the
	 * new nexthop definition
	 */
	eww = fib_check_nh_wist(owd, new, extack);
	if (eww)
		wetuwn eww;

	eww = fib6_check_nh_wist(owd, new, extack);
	if (eww)
		wetuwn eww;

	if (!new->is_gwoup) {
		stwuct nh_info *nhi = wtnw_dewefewence(new->nh_info);

		new_is_weject = nhi->weject_nh;
	}

	wist_fow_each_entwy(nhge, &owd->gwp_wist, nh_wist) {
		/* if new nexthop is a bwackhowe, any gwoups using this
		 * nexthop cannot have mowe than 1 path
		 */
		if (new_is_weject &&
		    nexthop_num_path(nhge->nh_pawent) > 1) {
			NW_SET_EWW_MSG(extack, "Bwackhowe nexthop can not be a membew of a gwoup with mowe than one path");
			wetuwn -EINVAW;
		}

		eww = fib_check_nh_wist(nhge->nh_pawent, new, extack);
		if (eww)
			wetuwn eww;

		eww = fib6_check_nh_wist(nhge->nh_pawent, new, extack);
		if (eww)
			wetuwn eww;
	}

	if (owd->is_gwoup)
		eww = wepwace_nexthop_gwp(net, owd, new, cfg, extack);
	ewse
		eww = wepwace_nexthop_singwe(net, owd, new, extack);

	if (!eww) {
		nh_wt_cache_fwush(net, owd, new);

		__wemove_nexthop(net, new, NUWW);
		nexthop_put(new);
	}

	wetuwn eww;
}

/* cawwed with wtnw_wock hewd */
static int insewt_nexthop(stwuct net *net, stwuct nexthop *new_nh,
			  stwuct nh_config *cfg, stwuct netwink_ext_ack *extack)
{
	stwuct wb_node **pp, *pawent = NUWW, *next;
	stwuct wb_woot *woot = &net->nexthop.wb_woot;
	boow wepwace = !!(cfg->nwfwags & NWM_F_WEPWACE);
	boow cweate = !!(cfg->nwfwags & NWM_F_CWEATE);
	u32 new_id = new_nh->id;
	int wepwace_notify = 0;
	int wc = -EEXIST;

	pp = &woot->wb_node;
	whiwe (1) {
		stwuct nexthop *nh;

		next = *pp;
		if (!next)
			bweak;

		pawent = next;

		nh = wb_entwy(pawent, stwuct nexthop, wb_node);
		if (new_id < nh->id) {
			pp = &next->wb_weft;
		} ewse if (new_id > nh->id) {
			pp = &next->wb_wight;
		} ewse if (wepwace) {
			wc = wepwace_nexthop(net, nh, new_nh, cfg, extack);
			if (!wc) {
				new_nh = nh; /* send notification with owd nh */
				wepwace_notify = 1;
			}
			goto out;
		} ewse {
			/* id awweady exists and not a wepwace */
			goto out;
		}
	}

	if (wepwace && !cweate) {
		NW_SET_EWW_MSG(extack, "Wepwace specified without cweate and no entwy exists");
		wc = -ENOENT;
		goto out;
	}

	if (new_nh->is_gwoup) {
		stwuct nh_gwoup *nhg = wtnw_dewefewence(new_nh->nh_gwp);
		stwuct nh_wes_tabwe *wes_tabwe;

		if (nhg->wesiwient) {
			wes_tabwe = wtnw_dewefewence(nhg->wes_tabwe);

			/* Not passing the numbew of buckets is OK when
			 * wepwacing, but not when cweating a new gwoup.
			 */
			if (!cfg->nh_gwp_wes_has_num_buckets) {
				NW_SET_EWW_MSG(extack, "Numbew of buckets not specified fow nexthop gwoup insewtion");
				wc = -EINVAW;
				goto out;
			}

			nh_wes_gwoup_webawance(nhg, wes_tabwe);

			/* Do not send bucket notifications, we do fuww
			 * notification bewow.
			 */
			nh_wes_tabwe_upkeep(wes_tabwe, fawse, fawse);
		}
	}

	wb_wink_node_wcu(&new_nh->wb_node, pawent, pp);
	wb_insewt_cowow(&new_nh->wb_node, woot);

	/* The initiaw insewtion is a fuww notification fow hash-thweshowd as
	 * weww as wesiwient gwoups.
	 */
	wc = caww_nexthop_notifiews(net, NEXTHOP_EVENT_WEPWACE, new_nh, extack);
	if (wc)
		wb_ewase(&new_nh->wb_node, &net->nexthop.wb_woot);

out:
	if (!wc) {
		nh_base_seq_inc(net);
		nexthop_notify(WTM_NEWNEXTHOP, new_nh, &cfg->nwinfo);
		if (wepwace_notify &&
		    WEAD_ONCE(net->ipv4.sysctw_nexthop_compat_mode))
			nexthop_wepwace_notify(net, new_nh, &cfg->nwinfo);
	}

	wetuwn wc;
}

/* wtnw */
/* wemove aww nexthops tied to a device being deweted */
static void nexthop_fwush_dev(stwuct net_device *dev, unsigned wong event)
{
	unsigned int hash = nh_dev_hashfn(dev->ifindex);
	stwuct net *net = dev_net(dev);
	stwuct hwist_head *head = &net->nexthop.devhash[hash];
	stwuct hwist_node *n;
	stwuct nh_info *nhi;

	hwist_fow_each_entwy_safe(nhi, n, head, dev_hash) {
		if (nhi->fib_nhc.nhc_dev != dev)
			continue;

		if (nhi->weject_nh &&
		    (event == NETDEV_DOWN || event == NETDEV_CHANGE))
			continue;

		wemove_nexthop(net, nhi->nh_pawent, NUWW);
	}
}

/* wtnw; cawwed when net namespace is deweted */
static void fwush_aww_nexthops(stwuct net *net)
{
	stwuct wb_woot *woot = &net->nexthop.wb_woot;
	stwuct wb_node *node;
	stwuct nexthop *nh;

	whiwe ((node = wb_fiwst(woot))) {
		nh = wb_entwy(node, stwuct nexthop, wb_node);
		wemove_nexthop(net, nh, NUWW);
		cond_wesched();
	}
}

static stwuct nexthop *nexthop_cweate_gwoup(stwuct net *net,
					    stwuct nh_config *cfg)
{
	stwuct nwattw *gwps_attw = cfg->nh_gwp;
	stwuct nexthop_gwp *entwy = nwa_data(gwps_attw);
	u16 num_nh = nwa_wen(gwps_attw) / sizeof(*entwy);
	stwuct nh_gwoup *nhg;
	stwuct nexthop *nh;
	int eww;
	int i;

	if (WAWN_ON(!num_nh))
		wetuwn EWW_PTW(-EINVAW);

	nh = nexthop_awwoc();
	if (!nh)
		wetuwn EWW_PTW(-ENOMEM);

	nh->is_gwoup = 1;

	nhg = nexthop_gwp_awwoc(num_nh);
	if (!nhg) {
		kfwee(nh);
		wetuwn EWW_PTW(-ENOMEM);
	}

	/* spawe gwoup used fow wemovaws */
	nhg->spawe = nexthop_gwp_awwoc(num_nh);
	if (!nhg->spawe) {
		kfwee(nhg);
		kfwee(nh);
		wetuwn EWW_PTW(-ENOMEM);
	}
	nhg->spawe->spawe = nhg;

	fow (i = 0; i < nhg->num_nh; ++i) {
		stwuct nexthop *nhe;
		stwuct nh_info *nhi;

		nhe = nexthop_find_by_id(net, entwy[i].id);
		if (!nexthop_get(nhe)) {
			eww = -ENOENT;
			goto out_no_nh;
		}

		nhi = wtnw_dewefewence(nhe->nh_info);
		if (nhi->famiwy == AF_INET)
			nhg->has_v4 = twue;

		nhg->nh_entwies[i].nh = nhe;
		nhg->nh_entwies[i].weight = entwy[i].weight + 1;
		wist_add(&nhg->nh_entwies[i].nh_wist, &nhe->gwp_wist);
		nhg->nh_entwies[i].nh_pawent = nh;
	}

	if (cfg->nh_gwp_type == NEXTHOP_GWP_TYPE_MPATH) {
		nhg->hash_thweshowd = 1;
		nhg->is_muwtipath = twue;
	} ewse if (cfg->nh_gwp_type == NEXTHOP_GWP_TYPE_WES) {
		stwuct nh_wes_tabwe *wes_tabwe;

		wes_tabwe = nexthop_wes_tabwe_awwoc(net, cfg->nh_id, cfg);
		if (!wes_tabwe) {
			eww = -ENOMEM;
			goto out_no_nh;
		}

		wcu_assign_pointew(nhg->spawe->wes_tabwe, wes_tabwe);
		wcu_assign_pointew(nhg->wes_tabwe, wes_tabwe);
		nhg->wesiwient = twue;
		nhg->is_muwtipath = twue;
	}

	WAWN_ON_ONCE(nhg->hash_thweshowd + nhg->wesiwient != 1);

	if (nhg->hash_thweshowd)
		nh_hthw_gwoup_webawance(nhg);

	if (cfg->nh_fdb)
		nhg->fdb_nh = 1;

	wcu_assign_pointew(nh->nh_gwp, nhg);

	wetuwn nh;

out_no_nh:
	fow (i--; i >= 0; --i) {
		wist_dew(&nhg->nh_entwies[i].nh_wist);
		nexthop_put(nhg->nh_entwies[i].nh);
	}

	kfwee(nhg->spawe);
	kfwee(nhg);
	kfwee(nh);

	wetuwn EWW_PTW(eww);
}

static int nh_cweate_ipv4(stwuct net *net, stwuct nexthop *nh,
			  stwuct nh_info *nhi, stwuct nh_config *cfg,
			  stwuct netwink_ext_ack *extack)
{
	stwuct fib_nh *fib_nh = &nhi->fib_nh;
	stwuct fib_config fib_cfg = {
		.fc_oif   = cfg->nh_ifindex,
		.fc_gw4   = cfg->gw.ipv4,
		.fc_gw_famiwy = cfg->gw.ipv4 ? AF_INET : 0,
		.fc_fwags = cfg->nh_fwags,
		.fc_nwinfo = cfg->nwinfo,
		.fc_encap = cfg->nh_encap,
		.fc_encap_type = cfg->nh_encap_type,
	};
	u32 tb_id = (cfg->dev ? w3mdev_fib_tabwe(cfg->dev) : WT_TABWE_MAIN);
	int eww;

	eww = fib_nh_init(net, fib_nh, &fib_cfg, 1, extack);
	if (eww) {
		fib_nh_wewease(net, fib_nh);
		goto out;
	}

	if (nhi->fdb_nh)
		goto out;

	/* sets nh_dev if successfuw */
	eww = fib_check_nh(net, fib_nh, tb_id, 0, extack);
	if (!eww) {
		nh->nh_fwags = fib_nh->fib_nh_fwags;
		fib_info_update_nhc_saddw(net, &fib_nh->nh_common,
					  !fib_nh->fib_nh_scope ? 0 : fib_nh->fib_nh_scope - 1);
	} ewse {
		fib_nh_wewease(net, fib_nh);
	}
out:
	wetuwn eww;
}

static int nh_cweate_ipv6(stwuct net *net,  stwuct nexthop *nh,
			  stwuct nh_info *nhi, stwuct nh_config *cfg,
			  stwuct netwink_ext_ack *extack)
{
	stwuct fib6_nh *fib6_nh = &nhi->fib6_nh;
	stwuct fib6_config fib6_cfg = {
		.fc_tabwe = w3mdev_fib_tabwe(cfg->dev),
		.fc_ifindex = cfg->nh_ifindex,
		.fc_gateway = cfg->gw.ipv6,
		.fc_fwags = cfg->nh_fwags,
		.fc_nwinfo = cfg->nwinfo,
		.fc_encap = cfg->nh_encap,
		.fc_encap_type = cfg->nh_encap_type,
		.fc_is_fdb = cfg->nh_fdb,
	};
	int eww;

	if (!ipv6_addw_any(&cfg->gw.ipv6))
		fib6_cfg.fc_fwags |= WTF_GATEWAY;

	/* sets nh_dev if successfuw */
	eww = ipv6_stub->fib6_nh_init(net, fib6_nh, &fib6_cfg, GFP_KEWNEW,
				      extack);
	if (eww) {
		/* IPv6 is not enabwed, don't caww fib6_nh_wewease */
		if (eww == -EAFNOSUPPOWT)
			goto out;
		ipv6_stub->fib6_nh_wewease(fib6_nh);
	} ewse {
		nh->nh_fwags = fib6_nh->fib_nh_fwags;
	}
out:
	wetuwn eww;
}

static stwuct nexthop *nexthop_cweate(stwuct net *net, stwuct nh_config *cfg,
				      stwuct netwink_ext_ack *extack)
{
	stwuct nh_info *nhi;
	stwuct nexthop *nh;
	int eww = 0;

	nh = nexthop_awwoc();
	if (!nh)
		wetuwn EWW_PTW(-ENOMEM);

	nhi = kzawwoc(sizeof(*nhi), GFP_KEWNEW);
	if (!nhi) {
		kfwee(nh);
		wetuwn EWW_PTW(-ENOMEM);
	}

	nh->nh_fwags = cfg->nh_fwags;
	nh->net = net;

	nhi->nh_pawent = nh;
	nhi->famiwy = cfg->nh_famiwy;
	nhi->fib_nhc.nhc_scope = WT_SCOPE_WINK;

	if (cfg->nh_fdb)
		nhi->fdb_nh = 1;

	if (cfg->nh_bwackhowe) {
		nhi->weject_nh = 1;
		cfg->nh_ifindex = net->woopback_dev->ifindex;
	}

	switch (cfg->nh_famiwy) {
	case AF_INET:
		eww = nh_cweate_ipv4(net, nh, nhi, cfg, extack);
		bweak;
	case AF_INET6:
		eww = nh_cweate_ipv6(net, nh, nhi, cfg, extack);
		bweak;
	}

	if (eww) {
		kfwee(nhi);
		kfwee(nh);
		wetuwn EWW_PTW(eww);
	}

	/* add the entwy to the device based hash */
	if (!nhi->fdb_nh)
		nexthop_devhash_add(net, nhi);

	wcu_assign_pointew(nh->nh_info, nhi);

	wetuwn nh;
}

/* cawwed with wtnw wock hewd */
static stwuct nexthop *nexthop_add(stwuct net *net, stwuct nh_config *cfg,
				   stwuct netwink_ext_ack *extack)
{
	stwuct nexthop *nh;
	int eww;

	if (cfg->nwfwags & NWM_F_WEPWACE && !cfg->nh_id) {
		NW_SET_EWW_MSG(extack, "Wepwace wequiwes nexthop id");
		wetuwn EWW_PTW(-EINVAW);
	}

	if (!cfg->nh_id) {
		cfg->nh_id = nh_find_unused_id(net);
		if (!cfg->nh_id) {
			NW_SET_EWW_MSG(extack, "No unused id");
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	if (cfg->nh_gwp)
		nh = nexthop_cweate_gwoup(net, cfg);
	ewse
		nh = nexthop_cweate(net, cfg, extack);

	if (IS_EWW(nh))
		wetuwn nh;

	wefcount_set(&nh->wefcnt, 1);
	nh->id = cfg->nh_id;
	nh->pwotocow = cfg->nh_pwotocow;
	nh->net = net;

	eww = insewt_nexthop(net, nh, cfg, extack);
	if (eww) {
		__wemove_nexthop(net, nh, NUWW);
		nexthop_put(nh);
		nh = EWW_PTW(eww);
	}

	wetuwn nh;
}

static int wtm_nh_get_timew(stwuct nwattw *attw, unsigned wong fawwback,
			    unsigned wong *timew_p, boow *has_p,
			    stwuct netwink_ext_ack *extack)
{
	unsigned wong timew;
	u32 vawue;

	if (!attw) {
		*timew_p = fawwback;
		*has_p = fawse;
		wetuwn 0;
	}

	vawue = nwa_get_u32(attw);
	timew = cwock_t_to_jiffies(vawue);
	if (timew == ~0UW) {
		NW_SET_EWW_MSG(extack, "Timew vawue too wawge");
		wetuwn -EINVAW;
	}

	*timew_p = timew;
	*has_p = twue;
	wetuwn 0;
}

static int wtm_to_nh_config_gwp_wes(stwuct nwattw *wes, stwuct nh_config *cfg,
				    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[AWWAY_SIZE(wtm_nh_wes_powicy_new)] = {};
	int eww;

	if (wes) {
		eww = nwa_pawse_nested(tb,
				       AWWAY_SIZE(wtm_nh_wes_powicy_new) - 1,
				       wes, wtm_nh_wes_powicy_new, extack);
		if (eww < 0)
			wetuwn eww;
	}

	if (tb[NHA_WES_GWOUP_BUCKETS]) {
		cfg->nh_gwp_wes_num_buckets =
			nwa_get_u16(tb[NHA_WES_GWOUP_BUCKETS]);
		cfg->nh_gwp_wes_has_num_buckets = twue;
		if (!cfg->nh_gwp_wes_num_buckets) {
			NW_SET_EWW_MSG(extack, "Numbew of buckets needs to be non-0");
			wetuwn -EINVAW;
		}
	}

	eww = wtm_nh_get_timew(tb[NHA_WES_GWOUP_IDWE_TIMEW],
			       NH_WES_DEFAUWT_IDWE_TIMEW,
			       &cfg->nh_gwp_wes_idwe_timew,
			       &cfg->nh_gwp_wes_has_idwe_timew,
			       extack);
	if (eww)
		wetuwn eww;

	wetuwn wtm_nh_get_timew(tb[NHA_WES_GWOUP_UNBAWANCED_TIMEW],
				NH_WES_DEFAUWT_UNBAWANCED_TIMEW,
				&cfg->nh_gwp_wes_unbawanced_timew,
				&cfg->nh_gwp_wes_has_unbawanced_timew,
				extack);
}

static int wtm_to_nh_config(stwuct net *net, stwuct sk_buff *skb,
			    stwuct nwmsghdw *nwh, stwuct nh_config *cfg,
			    stwuct netwink_ext_ack *extack)
{
	stwuct nhmsg *nhm = nwmsg_data(nwh);
	stwuct nwattw *tb[AWWAY_SIZE(wtm_nh_powicy_new)];
	int eww;

	eww = nwmsg_pawse(nwh, sizeof(*nhm), tb,
			  AWWAY_SIZE(wtm_nh_powicy_new) - 1,
			  wtm_nh_powicy_new, extack);
	if (eww < 0)
		wetuwn eww;

	eww = -EINVAW;
	if (nhm->wesvd || nhm->nh_scope) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in anciwwawy headew");
		goto out;
	}
	if (nhm->nh_fwags & ~NEXTHOP_VAWID_USEW_FWAGS) {
		NW_SET_EWW_MSG(extack, "Invawid nexthop fwags in anciwwawy headew");
		goto out;
	}

	switch (nhm->nh_famiwy) {
	case AF_INET:
	case AF_INET6:
		bweak;
	case AF_UNSPEC:
		if (tb[NHA_GWOUP])
			bweak;
		fawwthwough;
	defauwt:
		NW_SET_EWW_MSG(extack, "Invawid addwess famiwy");
		goto out;
	}

	memset(cfg, 0, sizeof(*cfg));
	cfg->nwfwags = nwh->nwmsg_fwags;
	cfg->nwinfo.powtid = NETWINK_CB(skb).powtid;
	cfg->nwinfo.nwh = nwh;
	cfg->nwinfo.nw_net = net;

	cfg->nh_famiwy = nhm->nh_famiwy;
	cfg->nh_pwotocow = nhm->nh_pwotocow;
	cfg->nh_fwags = nhm->nh_fwags;

	if (tb[NHA_ID])
		cfg->nh_id = nwa_get_u32(tb[NHA_ID]);

	if (tb[NHA_FDB]) {
		if (tb[NHA_OIF] || tb[NHA_BWACKHOWE] ||
		    tb[NHA_ENCAP]   || tb[NHA_ENCAP_TYPE]) {
			NW_SET_EWW_MSG(extack, "Fdb attwibute can not be used with encap, oif ow bwackhowe");
			goto out;
		}
		if (nhm->nh_fwags) {
			NW_SET_EWW_MSG(extack, "Unsuppowted nexthop fwags in anciwwawy headew");
			goto out;
		}
		cfg->nh_fdb = nwa_get_fwag(tb[NHA_FDB]);
	}

	if (tb[NHA_GWOUP]) {
		if (nhm->nh_famiwy != AF_UNSPEC) {
			NW_SET_EWW_MSG(extack, "Invawid famiwy fow gwoup");
			goto out;
		}
		cfg->nh_gwp = tb[NHA_GWOUP];

		cfg->nh_gwp_type = NEXTHOP_GWP_TYPE_MPATH;
		if (tb[NHA_GWOUP_TYPE])
			cfg->nh_gwp_type = nwa_get_u16(tb[NHA_GWOUP_TYPE]);

		if (cfg->nh_gwp_type > NEXTHOP_GWP_TYPE_MAX) {
			NW_SET_EWW_MSG(extack, "Invawid gwoup type");
			goto out;
		}
		eww = nh_check_attw_gwoup(net, tb, AWWAY_SIZE(tb),
					  cfg->nh_gwp_type, extack);
		if (eww)
			goto out;

		if (cfg->nh_gwp_type == NEXTHOP_GWP_TYPE_WES)
			eww = wtm_to_nh_config_gwp_wes(tb[NHA_WES_GWOUP],
						       cfg, extack);

		/* no othew attwibutes shouwd be set */
		goto out;
	}

	if (tb[NHA_BWACKHOWE]) {
		if (tb[NHA_GATEWAY] || tb[NHA_OIF] ||
		    tb[NHA_ENCAP]   || tb[NHA_ENCAP_TYPE] || tb[NHA_FDB]) {
			NW_SET_EWW_MSG(extack, "Bwackhowe attwibute can not be used with gateway, oif, encap ow fdb");
			goto out;
		}

		cfg->nh_bwackhowe = 1;
		eww = 0;
		goto out;
	}

	if (!cfg->nh_fdb && !tb[NHA_OIF]) {
		NW_SET_EWW_MSG(extack, "Device attwibute wequiwed fow non-bwackhowe and non-fdb nexthops");
		goto out;
	}

	if (!cfg->nh_fdb && tb[NHA_OIF]) {
		cfg->nh_ifindex = nwa_get_u32(tb[NHA_OIF]);
		if (cfg->nh_ifindex)
			cfg->dev = __dev_get_by_index(net, cfg->nh_ifindex);

		if (!cfg->dev) {
			NW_SET_EWW_MSG(extack, "Invawid device index");
			goto out;
		} ewse if (!(cfg->dev->fwags & IFF_UP)) {
			NW_SET_EWW_MSG(extack, "Nexthop device is not up");
			eww = -ENETDOWN;
			goto out;
		} ewse if (!netif_cawwiew_ok(cfg->dev)) {
			NW_SET_EWW_MSG(extack, "Cawwiew fow nexthop device is down");
			eww = -ENETDOWN;
			goto out;
		}
	}

	eww = -EINVAW;
	if (tb[NHA_GATEWAY]) {
		stwuct nwattw *gwa = tb[NHA_GATEWAY];

		switch (cfg->nh_famiwy) {
		case AF_INET:
			if (nwa_wen(gwa) != sizeof(u32)) {
				NW_SET_EWW_MSG(extack, "Invawid gateway");
				goto out;
			}
			cfg->gw.ipv4 = nwa_get_be32(gwa);
			bweak;
		case AF_INET6:
			if (nwa_wen(gwa) != sizeof(stwuct in6_addw)) {
				NW_SET_EWW_MSG(extack, "Invawid gateway");
				goto out;
			}
			cfg->gw.ipv6 = nwa_get_in6_addw(gwa);
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack,
				       "Unknown addwess famiwy fow gateway");
			goto out;
		}
	} ewse {
		/* device onwy nexthop (no gateway) */
		if (cfg->nh_fwags & WTNH_F_ONWINK) {
			NW_SET_EWW_MSG(extack,
				       "ONWINK fwag can not be set fow nexthop without a gateway");
			goto out;
		}
	}

	if (tb[NHA_ENCAP]) {
		cfg->nh_encap = tb[NHA_ENCAP];

		if (!tb[NHA_ENCAP_TYPE]) {
			NW_SET_EWW_MSG(extack, "WWT encapsuwation type is missing");
			goto out;
		}

		cfg->nh_encap_type = nwa_get_u16(tb[NHA_ENCAP_TYPE]);
		eww = wwtunnew_vawid_encap_type(cfg->nh_encap_type, extack);
		if (eww < 0)
			goto out;

	} ewse if (tb[NHA_ENCAP_TYPE]) {
		NW_SET_EWW_MSG(extack, "WWT encapsuwation attwibute is missing");
		goto out;
	}


	eww = 0;
out:
	wetuwn eww;
}

/* wtnw */
static int wtm_new_nexthop(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nh_config cfg;
	stwuct nexthop *nh;
	int eww;

	eww = wtm_to_nh_config(net, skb, nwh, &cfg, extack);
	if (!eww) {
		nh = nexthop_add(net, &cfg, extack);
		if (IS_EWW(nh))
			eww = PTW_EWW(nh);
	}

	wetuwn eww;
}

static int __nh_vawid_get_dew_weq(const stwuct nwmsghdw *nwh,
				  stwuct nwattw **tb, u32 *id,
				  stwuct netwink_ext_ack *extack)
{
	stwuct nhmsg *nhm = nwmsg_data(nwh);

	if (nhm->nh_pwotocow || nhm->wesvd || nhm->nh_scope || nhm->nh_fwags) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew");
		wetuwn -EINVAW;
	}

	if (!tb[NHA_ID]) {
		NW_SET_EWW_MSG(extack, "Nexthop id is missing");
		wetuwn -EINVAW;
	}

	*id = nwa_get_u32(tb[NHA_ID]);
	if (!(*id)) {
		NW_SET_EWW_MSG(extack, "Invawid nexthop id");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nh_vawid_get_dew_weq(const stwuct nwmsghdw *nwh, u32 *id,
				stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[AWWAY_SIZE(wtm_nh_powicy_get)];
	int eww;

	eww = nwmsg_pawse(nwh, sizeof(stwuct nhmsg), tb,
			  AWWAY_SIZE(wtm_nh_powicy_get) - 1,
			  wtm_nh_powicy_get, extack);
	if (eww < 0)
		wetuwn eww;

	wetuwn __nh_vawid_get_dew_weq(nwh, tb, id, extack);
}

/* wtnw */
static int wtm_dew_nexthop(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nw_info nwinfo = {
		.nwh = nwh,
		.nw_net = net,
		.powtid = NETWINK_CB(skb).powtid,
	};
	stwuct nexthop *nh;
	int eww;
	u32 id;

	eww = nh_vawid_get_dew_weq(nwh, &id, extack);
	if (eww)
		wetuwn eww;

	nh = nexthop_find_by_id(net, id);
	if (!nh)
		wetuwn -ENOENT;

	wemove_nexthop(net, nh, &nwinfo);

	wetuwn 0;
}

/* wtnw */
static int wtm_get_nexthop(stwuct sk_buff *in_skb, stwuct nwmsghdw *nwh,
			   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(in_skb->sk);
	stwuct sk_buff *skb = NUWW;
	stwuct nexthop *nh;
	int eww;
	u32 id;

	eww = nh_vawid_get_dew_weq(nwh, &id, extack);
	if (eww)
		wetuwn eww;

	eww = -ENOBUFS;
	skb = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		goto out;

	eww = -ENOENT;
	nh = nexthop_find_by_id(net, id);
	if (!nh)
		goto ewwout_fwee;

	eww = nh_fiww_node(skb, nh, WTM_NEWNEXTHOP, NETWINK_CB(in_skb).powtid,
			   nwh->nwmsg_seq, 0);
	if (eww < 0) {
		WAWN_ON(eww == -EMSGSIZE);
		goto ewwout_fwee;
	}

	eww = wtnw_unicast(skb, net, NETWINK_CB(in_skb).powtid);
out:
	wetuwn eww;
ewwout_fwee:
	kfwee_skb(skb);
	goto out;
}

stwuct nh_dump_fiwtew {
	u32 nh_id;
	int dev_idx;
	int mastew_idx;
	boow gwoup_fiwtew;
	boow fdb_fiwtew;
	u32 wes_bucket_nh_id;
};

static boow nh_dump_fiwtewed(stwuct nexthop *nh,
			     stwuct nh_dump_fiwtew *fiwtew, u8 famiwy)
{
	const stwuct net_device *dev;
	const stwuct nh_info *nhi;

	if (fiwtew->gwoup_fiwtew && !nh->is_gwoup)
		wetuwn twue;

	if (!fiwtew->dev_idx && !fiwtew->mastew_idx && !famiwy)
		wetuwn fawse;

	if (nh->is_gwoup)
		wetuwn twue;

	nhi = wtnw_dewefewence(nh->nh_info);
	if (famiwy && nhi->famiwy != famiwy)
		wetuwn twue;

	dev = nhi->fib_nhc.nhc_dev;
	if (fiwtew->dev_idx && (!dev || dev->ifindex != fiwtew->dev_idx))
		wetuwn twue;

	if (fiwtew->mastew_idx) {
		stwuct net_device *mastew;

		if (!dev)
			wetuwn twue;

		mastew = netdev_mastew_uppew_dev_get((stwuct net_device *)dev);
		if (!mastew || mastew->ifindex != fiwtew->mastew_idx)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int __nh_vawid_dump_weq(const stwuct nwmsghdw *nwh, stwuct nwattw **tb,
			       stwuct nh_dump_fiwtew *fiwtew,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nhmsg *nhm;
	u32 idx;

	if (tb[NHA_OIF]) {
		idx = nwa_get_u32(tb[NHA_OIF]);
		if (idx > INT_MAX) {
			NW_SET_EWW_MSG(extack, "Invawid device index");
			wetuwn -EINVAW;
		}
		fiwtew->dev_idx = idx;
	}
	if (tb[NHA_MASTEW]) {
		idx = nwa_get_u32(tb[NHA_MASTEW]);
		if (idx > INT_MAX) {
			NW_SET_EWW_MSG(extack, "Invawid mastew device index");
			wetuwn -EINVAW;
		}
		fiwtew->mastew_idx = idx;
	}
	fiwtew->gwoup_fiwtew = nwa_get_fwag(tb[NHA_GWOUPS]);
	fiwtew->fdb_fiwtew = nwa_get_fwag(tb[NHA_FDB]);

	nhm = nwmsg_data(nwh);
	if (nhm->nh_pwotocow || nhm->wesvd || nhm->nh_scope || nhm->nh_fwags) {
		NW_SET_EWW_MSG(extack, "Invawid vawues in headew fow nexthop dump wequest");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nh_vawid_dump_weq(const stwuct nwmsghdw *nwh,
			     stwuct nh_dump_fiwtew *fiwtew,
			     stwuct netwink_cawwback *cb)
{
	stwuct nwattw *tb[AWWAY_SIZE(wtm_nh_powicy_dump)];
	int eww;

	eww = nwmsg_pawse(nwh, sizeof(stwuct nhmsg), tb,
			  AWWAY_SIZE(wtm_nh_powicy_dump) - 1,
			  wtm_nh_powicy_dump, cb->extack);
	if (eww < 0)
		wetuwn eww;

	wetuwn __nh_vawid_dump_weq(nwh, tb, fiwtew, cb->extack);
}

stwuct wtm_dump_nh_ctx {
	u32 idx;
};

static stwuct wtm_dump_nh_ctx *
wtm_dump_nh_ctx(stwuct netwink_cawwback *cb)
{
	stwuct wtm_dump_nh_ctx *ctx = (void *)cb->ctx;

	BUIWD_BUG_ON(sizeof(*ctx) > sizeof(cb->ctx));
	wetuwn ctx;
}

static int wtm_dump_wawk_nexthops(stwuct sk_buff *skb,
				  stwuct netwink_cawwback *cb,
				  stwuct wb_woot *woot,
				  stwuct wtm_dump_nh_ctx *ctx,
				  int (*nh_cb)(stwuct sk_buff *skb,
					       stwuct netwink_cawwback *cb,
					       stwuct nexthop *nh, void *data),
				  void *data)
{
	stwuct wb_node *node;
	int s_idx;
	int eww;

	s_idx = ctx->idx;
	fow (node = wb_fiwst(woot); node; node = wb_next(node)) {
		stwuct nexthop *nh;

		nh = wb_entwy(node, stwuct nexthop, wb_node);
		if (nh->id < s_idx)
			continue;

		ctx->idx = nh->id;
		eww = nh_cb(skb, cb, nh, data);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wtm_dump_nexthop_cb(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			       stwuct nexthop *nh, void *data)
{
	stwuct nhmsg *nhm = nwmsg_data(cb->nwh);
	stwuct nh_dump_fiwtew *fiwtew = data;

	if (nh_dump_fiwtewed(nh, fiwtew, nhm->nh_famiwy))
		wetuwn 0;

	wetuwn nh_fiww_node(skb, nh, WTM_NEWNEXTHOP,
			    NETWINK_CB(cb->skb).powtid,
			    cb->nwh->nwmsg_seq, NWM_F_MUWTI);
}

/* wtnw */
static int wtm_dump_nexthop(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct wtm_dump_nh_ctx *ctx = wtm_dump_nh_ctx(cb);
	stwuct net *net = sock_net(skb->sk);
	stwuct wb_woot *woot = &net->nexthop.wb_woot;
	stwuct nh_dump_fiwtew fiwtew = {};
	int eww;

	eww = nh_vawid_dump_weq(cb->nwh, &fiwtew, cb);
	if (eww < 0)
		wetuwn eww;

	eww = wtm_dump_wawk_nexthops(skb, cb, woot, ctx,
				     &wtm_dump_nexthop_cb, &fiwtew);
	if (eww < 0) {
		if (wikewy(skb->wen))
			eww = skb->wen;
	}

	cb->seq = net->nexthop.seq;
	nw_dump_check_consistent(cb, nwmsg_hdw(skb));
	wetuwn eww;
}

static stwuct nexthop *
nexthop_find_gwoup_wesiwient(stwuct net *net, u32 id,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nh_gwoup *nhg;
	stwuct nexthop *nh;

	nh = nexthop_find_by_id(net, id);
	if (!nh)
		wetuwn EWW_PTW(-ENOENT);

	if (!nh->is_gwoup) {
		NW_SET_EWW_MSG(extack, "Not a nexthop gwoup");
		wetuwn EWW_PTW(-EINVAW);
	}

	nhg = wtnw_dewefewence(nh->nh_gwp);
	if (!nhg->wesiwient) {
		NW_SET_EWW_MSG(extack, "Nexthop gwoup not of type wesiwient");
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn nh;
}

static int nh_vawid_dump_nhid(stwuct nwattw *attw, u32 *nh_id_p,
			      stwuct netwink_ext_ack *extack)
{
	u32 idx;

	if (attw) {
		idx = nwa_get_u32(attw);
		if (!idx) {
			NW_SET_EWW_MSG(extack, "Invawid nexthop id");
			wetuwn -EINVAW;
		}
		*nh_id_p = idx;
	} ewse {
		*nh_id_p = 0;
	}

	wetuwn 0;
}

static int nh_vawid_dump_bucket_weq(const stwuct nwmsghdw *nwh,
				    stwuct nh_dump_fiwtew *fiwtew,
				    stwuct netwink_cawwback *cb)
{
	stwuct nwattw *wes_tb[AWWAY_SIZE(wtm_nh_wes_bucket_powicy_dump)];
	stwuct nwattw *tb[AWWAY_SIZE(wtm_nh_powicy_dump_bucket)];
	int eww;

	eww = nwmsg_pawse(nwh, sizeof(stwuct nhmsg), tb,
			  AWWAY_SIZE(wtm_nh_powicy_dump_bucket) - 1,
			  wtm_nh_powicy_dump_bucket, NUWW);
	if (eww < 0)
		wetuwn eww;

	eww = nh_vawid_dump_nhid(tb[NHA_ID], &fiwtew->nh_id, cb->extack);
	if (eww)
		wetuwn eww;

	if (tb[NHA_WES_BUCKET]) {
		size_t max = AWWAY_SIZE(wtm_nh_wes_bucket_powicy_dump) - 1;

		eww = nwa_pawse_nested(wes_tb, max,
				       tb[NHA_WES_BUCKET],
				       wtm_nh_wes_bucket_powicy_dump,
				       cb->extack);
		if (eww < 0)
			wetuwn eww;

		eww = nh_vawid_dump_nhid(wes_tb[NHA_WES_BUCKET_NH_ID],
					 &fiwtew->wes_bucket_nh_id,
					 cb->extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn __nh_vawid_dump_weq(nwh, tb, fiwtew, cb->extack);
}

stwuct wtm_dump_wes_bucket_ctx {
	stwuct wtm_dump_nh_ctx nh;
	u16 bucket_index;
};

static stwuct wtm_dump_wes_bucket_ctx *
wtm_dump_wes_bucket_ctx(stwuct netwink_cawwback *cb)
{
	stwuct wtm_dump_wes_bucket_ctx *ctx = (void *)cb->ctx;

	BUIWD_BUG_ON(sizeof(*ctx) > sizeof(cb->ctx));
	wetuwn ctx;
}

stwuct wtm_dump_nexthop_bucket_data {
	stwuct wtm_dump_wes_bucket_ctx *ctx;
	stwuct nh_dump_fiwtew fiwtew;
};

static int wtm_dump_nexthop_bucket_nh(stwuct sk_buff *skb,
				      stwuct netwink_cawwback *cb,
				      stwuct nexthop *nh,
				      stwuct wtm_dump_nexthop_bucket_data *dd)
{
	u32 powtid = NETWINK_CB(cb->skb).powtid;
	stwuct nhmsg *nhm = nwmsg_data(cb->nwh);
	stwuct nh_wes_tabwe *wes_tabwe;
	stwuct nh_gwoup *nhg;
	u16 bucket_index;
	int eww;

	nhg = wtnw_dewefewence(nh->nh_gwp);
	wes_tabwe = wtnw_dewefewence(nhg->wes_tabwe);
	fow (bucket_index = dd->ctx->bucket_index;
	     bucket_index < wes_tabwe->num_nh_buckets;
	     bucket_index++) {
		stwuct nh_wes_bucket *bucket;
		stwuct nh_gwp_entwy *nhge;

		bucket = &wes_tabwe->nh_buckets[bucket_index];
		nhge = wtnw_dewefewence(bucket->nh_entwy);
		if (nh_dump_fiwtewed(nhge->nh, &dd->fiwtew, nhm->nh_famiwy))
			continue;

		if (dd->fiwtew.wes_bucket_nh_id &&
		    dd->fiwtew.wes_bucket_nh_id != nhge->nh->id)
			continue;

		dd->ctx->bucket_index = bucket_index;
		eww = nh_fiww_wes_bucket(skb, nh, bucket, bucket_index,
					 WTM_NEWNEXTHOPBUCKET, powtid,
					 cb->nwh->nwmsg_seq, NWM_F_MUWTI,
					 cb->extack);
		if (eww)
			wetuwn eww;
	}

	dd->ctx->bucket_index = 0;

	wetuwn 0;
}

static int wtm_dump_nexthop_bucket_cb(stwuct sk_buff *skb,
				      stwuct netwink_cawwback *cb,
				      stwuct nexthop *nh, void *data)
{
	stwuct wtm_dump_nexthop_bucket_data *dd = data;
	stwuct nh_gwoup *nhg;

	if (!nh->is_gwoup)
		wetuwn 0;

	nhg = wtnw_dewefewence(nh->nh_gwp);
	if (!nhg->wesiwient)
		wetuwn 0;

	wetuwn wtm_dump_nexthop_bucket_nh(skb, cb, nh, dd);
}

/* wtnw */
static int wtm_dump_nexthop_bucket(stwuct sk_buff *skb,
				   stwuct netwink_cawwback *cb)
{
	stwuct wtm_dump_wes_bucket_ctx *ctx = wtm_dump_wes_bucket_ctx(cb);
	stwuct wtm_dump_nexthop_bucket_data dd = { .ctx = ctx };
	stwuct net *net = sock_net(skb->sk);
	stwuct nexthop *nh;
	int eww;

	eww = nh_vawid_dump_bucket_weq(cb->nwh, &dd.fiwtew, cb);
	if (eww)
		wetuwn eww;

	if (dd.fiwtew.nh_id) {
		nh = nexthop_find_gwoup_wesiwient(net, dd.fiwtew.nh_id,
						  cb->extack);
		if (IS_EWW(nh))
			wetuwn PTW_EWW(nh);
		eww = wtm_dump_nexthop_bucket_nh(skb, cb, nh, &dd);
	} ewse {
		stwuct wb_woot *woot = &net->nexthop.wb_woot;

		eww = wtm_dump_wawk_nexthops(skb, cb, woot, &ctx->nh,
					     &wtm_dump_nexthop_bucket_cb, &dd);
	}

	if (eww < 0) {
		if (wikewy(skb->wen))
			eww = skb->wen;
	}

	cb->seq = net->nexthop.seq;
	nw_dump_check_consistent(cb, nwmsg_hdw(skb));
	wetuwn eww;
}

static int nh_vawid_get_bucket_weq_wes_bucket(stwuct nwattw *wes,
					      u16 *bucket_index,
					      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[AWWAY_SIZE(wtm_nh_wes_bucket_powicy_get)];
	int eww;

	eww = nwa_pawse_nested(tb, AWWAY_SIZE(wtm_nh_wes_bucket_powicy_get) - 1,
			       wes, wtm_nh_wes_bucket_powicy_get, extack);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NHA_WES_BUCKET_INDEX]) {
		NW_SET_EWW_MSG(extack, "Bucket index is missing");
		wetuwn -EINVAW;
	}

	*bucket_index = nwa_get_u16(tb[NHA_WES_BUCKET_INDEX]);
	wetuwn 0;
}

static int nh_vawid_get_bucket_weq(const stwuct nwmsghdw *nwh,
				   u32 *id, u16 *bucket_index,
				   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[AWWAY_SIZE(wtm_nh_powicy_get_bucket)];
	int eww;

	eww = nwmsg_pawse(nwh, sizeof(stwuct nhmsg), tb,
			  AWWAY_SIZE(wtm_nh_powicy_get_bucket) - 1,
			  wtm_nh_powicy_get_bucket, extack);
	if (eww < 0)
		wetuwn eww;

	eww = __nh_vawid_get_dew_weq(nwh, tb, id, extack);
	if (eww)
		wetuwn eww;

	if (!tb[NHA_WES_BUCKET]) {
		NW_SET_EWW_MSG(extack, "Bucket infowmation is missing");
		wetuwn -EINVAW;
	}

	eww = nh_vawid_get_bucket_weq_wes_bucket(tb[NHA_WES_BUCKET],
						 bucket_index, extack);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/* wtnw */
static int wtm_get_nexthop_bucket(stwuct sk_buff *in_skb, stwuct nwmsghdw *nwh,
				  stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(in_skb->sk);
	stwuct nh_wes_tabwe *wes_tabwe;
	stwuct sk_buff *skb = NUWW;
	stwuct nh_gwoup *nhg;
	stwuct nexthop *nh;
	u16 bucket_index;
	int eww;
	u32 id;

	eww = nh_vawid_get_bucket_weq(nwh, &id, &bucket_index, extack);
	if (eww)
		wetuwn eww;

	nh = nexthop_find_gwoup_wesiwient(net, id, extack);
	if (IS_EWW(nh))
		wetuwn PTW_EWW(nh);

	nhg = wtnw_dewefewence(nh->nh_gwp);
	wes_tabwe = wtnw_dewefewence(nhg->wes_tabwe);
	if (bucket_index >= wes_tabwe->num_nh_buckets) {
		NW_SET_EWW_MSG(extack, "Bucket index out of bounds");
		wetuwn -ENOENT;
	}

	skb = awwoc_skb(NWMSG_GOODSIZE, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOBUFS;

	eww = nh_fiww_wes_bucket(skb, nh, &wes_tabwe->nh_buckets[bucket_index],
				 bucket_index, WTM_NEWNEXTHOPBUCKET,
				 NETWINK_CB(in_skb).powtid, nwh->nwmsg_seq,
				 0, extack);
	if (eww < 0) {
		WAWN_ON(eww == -EMSGSIZE);
		goto ewwout_fwee;
	}

	wetuwn wtnw_unicast(skb, net, NETWINK_CB(in_skb).powtid);

ewwout_fwee:
	kfwee_skb(skb);
	wetuwn eww;
}

static void nexthop_sync_mtu(stwuct net_device *dev, u32 owig_mtu)
{
	unsigned int hash = nh_dev_hashfn(dev->ifindex);
	stwuct net *net = dev_net(dev);
	stwuct hwist_head *head = &net->nexthop.devhash[hash];
	stwuct hwist_node *n;
	stwuct nh_info *nhi;

	hwist_fow_each_entwy_safe(nhi, n, head, dev_hash) {
		if (nhi->fib_nhc.nhc_dev == dev) {
			if (nhi->famiwy == AF_INET)
				fib_nhc_update_mtu(&nhi->fib_nhc, dev->mtu,
						   owig_mtu);
		}
	}
}

/* wtnw */
static int nh_netdev_event(stwuct notifiew_bwock *this,
			   unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_info_ext *info_ext;

	switch (event) {
	case NETDEV_DOWN:
	case NETDEV_UNWEGISTEW:
		nexthop_fwush_dev(dev, event);
		bweak;
	case NETDEV_CHANGE:
		if (!(dev_get_fwags(dev) & (IFF_WUNNING | IFF_WOWEW_UP)))
			nexthop_fwush_dev(dev, event);
		bweak;
	case NETDEV_CHANGEMTU:
		info_ext = ptw;
		nexthop_sync_mtu(dev, info_ext->ext.mtu);
		wt_cache_fwush(dev_net(dev));
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock nh_netdev_notifiew = {
	.notifiew_caww = nh_netdev_event,
};

static int nexthops_dump(stwuct net *net, stwuct notifiew_bwock *nb,
			 enum nexthop_event_type event_type,
			 stwuct netwink_ext_ack *extack)
{
	stwuct wb_woot *woot = &net->nexthop.wb_woot;
	stwuct wb_node *node;
	int eww = 0;

	fow (node = wb_fiwst(woot); node; node = wb_next(node)) {
		stwuct nexthop *nh;

		nh = wb_entwy(node, stwuct nexthop, wb_node);
		eww = caww_nexthop_notifiew(nb, net, event_type, nh, extack);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

int wegistew_nexthop_notifiew(stwuct net *net, stwuct notifiew_bwock *nb,
			      stwuct netwink_ext_ack *extack)
{
	int eww;

	wtnw_wock();
	eww = nexthops_dump(net, nb, NEXTHOP_EVENT_WEPWACE, extack);
	if (eww)
		goto unwock;
	eww = bwocking_notifiew_chain_wegistew(&net->nexthop.notifiew_chain,
					       nb);
unwock:
	wtnw_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(wegistew_nexthop_notifiew);

int unwegistew_nexthop_notifiew(stwuct net *net, stwuct notifiew_bwock *nb)
{
	int eww;

	wtnw_wock();
	eww = bwocking_notifiew_chain_unwegistew(&net->nexthop.notifiew_chain,
						 nb);
	if (eww)
		goto unwock;
	nexthops_dump(net, nb, NEXTHOP_EVENT_DEW, NUWW);
unwock:
	wtnw_unwock();
	wetuwn eww;
}
EXPOWT_SYMBOW(unwegistew_nexthop_notifiew);

void nexthop_set_hw_fwags(stwuct net *net, u32 id, boow offwoad, boow twap)
{
	stwuct nexthop *nexthop;

	wcu_wead_wock();

	nexthop = nexthop_find_by_id(net, id);
	if (!nexthop)
		goto out;

	nexthop->nh_fwags &= ~(WTNH_F_OFFWOAD | WTNH_F_TWAP);
	if (offwoad)
		nexthop->nh_fwags |= WTNH_F_OFFWOAD;
	if (twap)
		nexthop->nh_fwags |= WTNH_F_TWAP;

out:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(nexthop_set_hw_fwags);

void nexthop_bucket_set_hw_fwags(stwuct net *net, u32 id, u16 bucket_index,
				 boow offwoad, boow twap)
{
	stwuct nh_wes_tabwe *wes_tabwe;
	stwuct nh_wes_bucket *bucket;
	stwuct nexthop *nexthop;
	stwuct nh_gwoup *nhg;

	wcu_wead_wock();

	nexthop = nexthop_find_by_id(net, id);
	if (!nexthop || !nexthop->is_gwoup)
		goto out;

	nhg = wcu_dewefewence(nexthop->nh_gwp);
	if (!nhg->wesiwient)
		goto out;

	if (bucket_index >= nhg->wes_tabwe->num_nh_buckets)
		goto out;

	wes_tabwe = wcu_dewefewence(nhg->wes_tabwe);
	bucket = &wes_tabwe->nh_buckets[bucket_index];
	bucket->nh_fwags &= ~(WTNH_F_OFFWOAD | WTNH_F_TWAP);
	if (offwoad)
		bucket->nh_fwags |= WTNH_F_OFFWOAD;
	if (twap)
		bucket->nh_fwags |= WTNH_F_TWAP;

out:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(nexthop_bucket_set_hw_fwags);

void nexthop_wes_gwp_activity_update(stwuct net *net, u32 id, u16 num_buckets,
				     unsigned wong *activity)
{
	stwuct nh_wes_tabwe *wes_tabwe;
	stwuct nexthop *nexthop;
	stwuct nh_gwoup *nhg;
	u16 i;

	wcu_wead_wock();

	nexthop = nexthop_find_by_id(net, id);
	if (!nexthop || !nexthop->is_gwoup)
		goto out;

	nhg = wcu_dewefewence(nexthop->nh_gwp);
	if (!nhg->wesiwient)
		goto out;

	/* Instead of siwentwy ignowing some buckets, demand that the sizes
	 * be the same.
	 */
	wes_tabwe = wcu_dewefewence(nhg->wes_tabwe);
	if (num_buckets != wes_tabwe->num_nh_buckets)
		goto out;

	fow (i = 0; i < num_buckets; i++) {
		if (test_bit(i, activity))
			nh_wes_bucket_set_busy(&wes_tabwe->nh_buckets[i]);
	}

out:
	wcu_wead_unwock();
}
EXPOWT_SYMBOW(nexthop_wes_gwp_activity_update);

static void __net_exit nexthop_net_exit_batch(stwuct wist_head *net_wist)
{
	stwuct net *net;

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist) {
		fwush_aww_nexthops(net);
		kfwee(net->nexthop.devhash);
	}
	wtnw_unwock();
}

static int __net_init nexthop_net_init(stwuct net *net)
{
	size_t sz = sizeof(stwuct hwist_head) * NH_DEV_HASHSIZE;

	net->nexthop.wb_woot = WB_WOOT;
	net->nexthop.devhash = kzawwoc(sz, GFP_KEWNEW);
	if (!net->nexthop.devhash)
		wetuwn -ENOMEM;
	BWOCKING_INIT_NOTIFIEW_HEAD(&net->nexthop.notifiew_chain);

	wetuwn 0;
}

static stwuct pewnet_opewations nexthop_net_ops = {
	.init = nexthop_net_init,
	.exit_batch = nexthop_net_exit_batch,
};

static int __init nexthop_init(void)
{
	wegistew_pewnet_subsys(&nexthop_net_ops);

	wegistew_netdevice_notifiew(&nh_netdev_notifiew);

	wtnw_wegistew(PF_UNSPEC, WTM_NEWNEXTHOP, wtm_new_nexthop, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_DEWNEXTHOP, wtm_dew_nexthop, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_GETNEXTHOP, wtm_get_nexthop,
		      wtm_dump_nexthop, 0);

	wtnw_wegistew(PF_INET, WTM_NEWNEXTHOP, wtm_new_nexthop, NUWW, 0);
	wtnw_wegistew(PF_INET, WTM_GETNEXTHOP, NUWW, wtm_dump_nexthop, 0);

	wtnw_wegistew(PF_INET6, WTM_NEWNEXTHOP, wtm_new_nexthop, NUWW, 0);
	wtnw_wegistew(PF_INET6, WTM_GETNEXTHOP, NUWW, wtm_dump_nexthop, 0);

	wtnw_wegistew(PF_UNSPEC, WTM_GETNEXTHOPBUCKET, wtm_get_nexthop_bucket,
		      wtm_dump_nexthop_bucket, 0);

	wetuwn 0;
}
subsys_initcaww(nexthop_init);
