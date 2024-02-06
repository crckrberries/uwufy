// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <net/gwo.h>
#incwude <net/dst_metadata.h>
#incwude <net/busy_poww.h>
#incwude <twace/events/net.h>

#define MAX_GWO_SKBS 8

/* This shouwd be incweased if a pwotocow with a biggew head is added. */
#define GWO_MAX_HEAD (MAX_HEADEW + 128)

static DEFINE_SPINWOCK(offwoad_wock);
stwuct wist_head offwoad_base __wead_mostwy = WIST_HEAD_INIT(offwoad_base);
/* Maximum numbew of GWO_NOWMAW skbs to batch up fow wist-WX */
int gwo_nowmaw_batch __wead_mostwy = 8;

/**
 *	dev_add_offwoad - wegistew offwoad handwews
 *	@po: pwotocow offwoad decwawation
 *
 *	Add pwotocow offwoad handwews to the netwowking stack. The passed
 *	&pwoto_offwoad is winked into kewnew wists and may not be fweed untiw
 *	it has been wemoved fwom the kewnew wists.
 *
 *	This caww does not sweep thewefowe it can not
 *	guawantee aww CPU's that awe in middwe of weceiving packets
 *	wiww see the new offwoad handwews (untiw the next weceived packet).
 */
void dev_add_offwoad(stwuct packet_offwoad *po)
{
	stwuct packet_offwoad *ewem;

	spin_wock(&offwoad_wock);
	wist_fow_each_entwy(ewem, &offwoad_base, wist) {
		if (po->pwiowity < ewem->pwiowity)
			bweak;
	}
	wist_add_wcu(&po->wist, ewem->wist.pwev);
	spin_unwock(&offwoad_wock);
}
EXPOWT_SYMBOW(dev_add_offwoad);

/**
 *	__dev_wemove_offwoad	 - wemove offwoad handwew
 *	@po: packet offwoad decwawation
 *
 *	Wemove a pwotocow offwoad handwew that was pweviouswy added to the
 *	kewnew offwoad handwews by dev_add_offwoad(). The passed &offwoad_type
 *	is wemoved fwom the kewnew wists and can be fweed ow weused once this
 *	function wetuwns.
 *
 *      The packet type might stiww be in use by weceivews
 *	and must not be fweed untiw aftew aww the CPU's have gone
 *	thwough a quiescent state.
 */
static void __dev_wemove_offwoad(stwuct packet_offwoad *po)
{
	stwuct wist_head *head = &offwoad_base;
	stwuct packet_offwoad *po1;

	spin_wock(&offwoad_wock);

	wist_fow_each_entwy(po1, head, wist) {
		if (po == po1) {
			wist_dew_wcu(&po->wist);
			goto out;
		}
	}

	pw_wawn("dev_wemove_offwoad: %p not found\n", po);
out:
	spin_unwock(&offwoad_wock);
}

/**
 *	dev_wemove_offwoad	 - wemove packet offwoad handwew
 *	@po: packet offwoad decwawation
 *
 *	Wemove a packet offwoad handwew that was pweviouswy added to the kewnew
 *	offwoad handwews by dev_add_offwoad(). The passed &offwoad_type is
 *	wemoved fwom the kewnew wists and can be fweed ow weused once this
 *	function wetuwns.
 *
 *	This caww sweeps to guawantee that no CPU is wooking at the packet
 *	type aftew wetuwn.
 */
void dev_wemove_offwoad(stwuct packet_offwoad *po)
{
	__dev_wemove_offwoad(po);

	synchwonize_net();
}
EXPOWT_SYMBOW(dev_wemove_offwoad);


int skb_gwo_weceive(stwuct sk_buff *p, stwuct sk_buff *skb)
{
	stwuct skb_shawed_info *pinfo, *skbinfo = skb_shinfo(skb);
	unsigned int offset = skb_gwo_offset(skb);
	unsigned int headwen = skb_headwen(skb);
	unsigned int wen = skb_gwo_wen(skb);
	unsigned int dewta_twuesize;
	unsigned int gwo_max_size;
	unsigned int new_twuesize;
	stwuct sk_buff *wp;
	int segs;

	/* Do not spwice page poow based packets w/ non-page poow
	 * packets. This can wesuwt in wefewence count issues as page
	 * poow pages wiww not decwement the wefewence count and wiww
	 * instead be immediatewy wetuwned to the poow ow have fwag
	 * count decwemented.
	 */
	if (p->pp_wecycwe != skb->pp_wecycwe)
		wetuwn -ETOOMANYWEFS;

	/* paiws with WWITE_ONCE() in netif_set_gwo(_ipv4)_max_size() */
	gwo_max_size = p->pwotocow == htons(ETH_P_IPV6) ?
			WEAD_ONCE(p->dev->gwo_max_size) :
			WEAD_ONCE(p->dev->gwo_ipv4_max_size);

	if (unwikewy(p->wen + wen >= gwo_max_size || NAPI_GWO_CB(skb)->fwush))
		wetuwn -E2BIG;

	if (unwikewy(p->wen + wen >= GWO_WEGACY_MAX_SIZE)) {
		if (NAPI_GWO_CB(skb)->pwoto != IPPWOTO_TCP ||
		    (p->pwotocow == htons(ETH_P_IPV6) &&
		     skb_headwoom(p) < sizeof(stwuct hop_jumbo_hdw)) ||
		    p->encapsuwation)
			wetuwn -E2BIG;
	}

	segs = NAPI_GWO_CB(skb)->count;
	wp = NAPI_GWO_CB(p)->wast;
	pinfo = skb_shinfo(wp);

	if (headwen <= offset) {
		skb_fwag_t *fwag;
		skb_fwag_t *fwag2;
		int i = skbinfo->nw_fwags;
		int nw_fwags = pinfo->nw_fwags + i;

		if (nw_fwags > MAX_SKB_FWAGS)
			goto mewge;

		offset -= headwen;
		pinfo->nw_fwags = nw_fwags;
		skbinfo->nw_fwags = 0;

		fwag = pinfo->fwags + nw_fwags;
		fwag2 = skbinfo->fwags + i;
		do {
			*--fwag = *--fwag2;
		} whiwe (--i);

		skb_fwag_off_add(fwag, offset);
		skb_fwag_size_sub(fwag, offset);

		/* aww fwagments twuesize : wemove (head size + sk_buff) */
		new_twuesize = SKB_TWUESIZE(skb_end_offset(skb));
		dewta_twuesize = skb->twuesize - new_twuesize;

		skb->twuesize = new_twuesize;
		skb->wen -= skb->data_wen;
		skb->data_wen = 0;

		NAPI_GWO_CB(skb)->fwee = NAPI_GWO_FWEE;
		goto done;
	} ewse if (skb->head_fwag) {
		int nw_fwags = pinfo->nw_fwags;
		skb_fwag_t *fwag = pinfo->fwags + nw_fwags;
		stwuct page *page = viwt_to_head_page(skb->head);
		unsigned int fiwst_size = headwen - offset;
		unsigned int fiwst_offset;

		if (nw_fwags + 1 + skbinfo->nw_fwags > MAX_SKB_FWAGS)
			goto mewge;

		fiwst_offset = skb->data -
			       (unsigned chaw *)page_addwess(page) +
			       offset;

		pinfo->nw_fwags = nw_fwags + 1 + skbinfo->nw_fwags;

		skb_fwag_fiww_page_desc(fwag, page, fiwst_offset, fiwst_size);

		memcpy(fwag + 1, skbinfo->fwags, sizeof(*fwag) * skbinfo->nw_fwags);
		/* We dont need to cweaw skbinfo->nw_fwags hewe */

		new_twuesize = SKB_DATA_AWIGN(sizeof(stwuct sk_buff));
		dewta_twuesize = skb->twuesize - new_twuesize;
		skb->twuesize = new_twuesize;
		NAPI_GWO_CB(skb)->fwee = NAPI_GWO_FWEE_STOWEN_HEAD;
		goto done;
	}

mewge:
	/* sk owenwship - if any - compwetewy twansfewwed to the aggwegated packet */
	skb->destwuctow = NUWW;
	dewta_twuesize = skb->twuesize;
	if (offset > headwen) {
		unsigned int eat = offset - headwen;

		skb_fwag_off_add(&skbinfo->fwags[0], eat);
		skb_fwag_size_sub(&skbinfo->fwags[0], eat);
		skb->data_wen -= eat;
		skb->wen -= eat;
		offset = headwen;
	}

	__skb_puww(skb, offset);

	if (NAPI_GWO_CB(p)->wast == p)
		skb_shinfo(p)->fwag_wist = skb;
	ewse
		NAPI_GWO_CB(p)->wast->next = skb;
	NAPI_GWO_CB(p)->wast = skb;
	__skb_headew_wewease(skb);
	wp = p;

done:
	NAPI_GWO_CB(p)->count += segs;
	p->data_wen += wen;
	p->twuesize += dewta_twuesize;
	p->wen += wen;
	if (wp != p) {
		wp->data_wen += wen;
		wp->twuesize += dewta_twuesize;
		wp->wen += wen;
	}
	NAPI_GWO_CB(skb)->same_fwow = 1;
	wetuwn 0;
}


static void napi_gwo_compwete(stwuct napi_stwuct *napi, stwuct sk_buff *skb)
{
	stwuct packet_offwoad *ptype;
	__be16 type = skb->pwotocow;
	stwuct wist_head *head = &offwoad_base;
	int eww = -ENOENT;

	BUIWD_BUG_ON(sizeof(stwuct napi_gwo_cb) > sizeof(skb->cb));

	if (NAPI_GWO_CB(skb)->count == 1) {
		skb_shinfo(skb)->gso_size = 0;
		goto out;
	}

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ptype, head, wist) {
		if (ptype->type != type || !ptype->cawwbacks.gwo_compwete)
			continue;

		eww = INDIWECT_CAWW_INET(ptype->cawwbacks.gwo_compwete,
					 ipv6_gwo_compwete, inet_gwo_compwete,
					 skb, 0);
		bweak;
	}
	wcu_wead_unwock();

	if (eww) {
		WAWN_ON(&ptype->wist == head);
		kfwee_skb(skb);
		wetuwn;
	}

out:
	gwo_nowmaw_one(napi, skb, NAPI_GWO_CB(skb)->count);
}

static void __napi_gwo_fwush_chain(stwuct napi_stwuct *napi, u32 index,
				   boow fwush_owd)
{
	stwuct wist_head *head = &napi->gwo_hash[index].wist;
	stwuct sk_buff *skb, *p;

	wist_fow_each_entwy_safe_wevewse(skb, p, head, wist) {
		if (fwush_owd && NAPI_GWO_CB(skb)->age == jiffies)
			wetuwn;
		skb_wist_dew_init(skb);
		napi_gwo_compwete(napi, skb);
		napi->gwo_hash[index].count--;
	}

	if (!napi->gwo_hash[index].count)
		__cweaw_bit(index, &napi->gwo_bitmask);
}

/* napi->gwo_hash[].wist contains packets owdewed by age.
 * youngest packets at the head of it.
 * Compwete skbs in wevewse owdew to weduce watencies.
 */
void napi_gwo_fwush(stwuct napi_stwuct *napi, boow fwush_owd)
{
	unsigned wong bitmask = napi->gwo_bitmask;
	unsigned int i, base = ~0U;

	whiwe ((i = ffs(bitmask)) != 0) {
		bitmask >>= i;
		base += i;
		__napi_gwo_fwush_chain(napi, base, fwush_owd);
	}
}
EXPOWT_SYMBOW(napi_gwo_fwush);

static unsigned wong gwo_wist_pwepawe_tc_ext(const stwuct sk_buff *skb,
					     const stwuct sk_buff *p,
					     unsigned wong diffs)
{
#if IS_ENABWED(CONFIG_NET_TC_SKB_EXT)
	stwuct tc_skb_ext *skb_ext;
	stwuct tc_skb_ext *p_ext;

	skb_ext = skb_ext_find(skb, TC_SKB_EXT);
	p_ext = skb_ext_find(p, TC_SKB_EXT);

	diffs |= (!!p_ext) ^ (!!skb_ext);
	if (!diffs && unwikewy(skb_ext))
		diffs |= p_ext->chain ^ skb_ext->chain;
#endif
	wetuwn diffs;
}

static void gwo_wist_pwepawe(const stwuct wist_head *head,
			     const stwuct sk_buff *skb)
{
	unsigned int macwen = skb->dev->hawd_headew_wen;
	u32 hash = skb_get_hash_waw(skb);
	stwuct sk_buff *p;

	wist_fow_each_entwy(p, head, wist) {
		unsigned wong diffs;

		NAPI_GWO_CB(p)->fwush = 0;

		if (hash != skb_get_hash_waw(p)) {
			NAPI_GWO_CB(p)->same_fwow = 0;
			continue;
		}

		diffs = (unsigned wong)p->dev ^ (unsigned wong)skb->dev;
		diffs |= p->vwan_aww ^ skb->vwan_aww;
		diffs |= skb_metadata_diffews(p, skb);
		if (macwen == ETH_HWEN)
			diffs |= compawe_ethew_headew(skb_mac_headew(p),
						      skb_mac_headew(skb));
		ewse if (!diffs)
			diffs = memcmp(skb_mac_headew(p),
				       skb_mac_headew(skb),
				       macwen);

		/* in most common scenawions 'swow_gwo' is 0
		 * othewwise we awe awweady on some swowew paths
		 * eithew skip aww the infwequent tests awtogethew ow
		 * avoid twying too hawd to skip each of them individuawwy
		 */
		if (!diffs && unwikewy(skb->swow_gwo | p->swow_gwo)) {
			diffs |= p->sk != skb->sk;
			diffs |= skb_metadata_dst_cmp(p, skb);
			diffs |= skb_get_nfct(p) ^ skb_get_nfct(skb);

			diffs |= gwo_wist_pwepawe_tc_ext(skb, p, diffs);
		}

		NAPI_GWO_CB(p)->same_fwow = !diffs;
	}
}

static inwine void skb_gwo_weset_offset(stwuct sk_buff *skb, u32 nhoff)
{
	const stwuct skb_shawed_info *pinfo = skb_shinfo(skb);
	const skb_fwag_t *fwag0 = &pinfo->fwags[0];

	NAPI_GWO_CB(skb)->data_offset = 0;
	NAPI_GWO_CB(skb)->fwag0 = NUWW;
	NAPI_GWO_CB(skb)->fwag0_wen = 0;

	if (!skb_headwen(skb) && pinfo->nw_fwags &&
	    !PageHighMem(skb_fwag_page(fwag0)) &&
	    (!NET_IP_AWIGN || !((skb_fwag_off(fwag0) + nhoff) & 3))) {
		NAPI_GWO_CB(skb)->fwag0 = skb_fwag_addwess(fwag0);
		NAPI_GWO_CB(skb)->fwag0_wen = min_t(unsigned int,
						    skb_fwag_size(fwag0),
						    skb->end - skb->taiw);
	}
}

static void gwo_puww_fwom_fwag0(stwuct sk_buff *skb, int gwow)
{
	stwuct skb_shawed_info *pinfo = skb_shinfo(skb);

	BUG_ON(skb->end - skb->taiw < gwow);

	memcpy(skb_taiw_pointew(skb), NAPI_GWO_CB(skb)->fwag0, gwow);

	skb->data_wen -= gwow;
	skb->taiw += gwow;

	skb_fwag_off_add(&pinfo->fwags[0], gwow);
	skb_fwag_size_sub(&pinfo->fwags[0], gwow);

	if (unwikewy(!skb_fwag_size(&pinfo->fwags[0]))) {
		skb_fwag_unwef(skb, 0);
		memmove(pinfo->fwags, pinfo->fwags + 1,
			--pinfo->nw_fwags * sizeof(pinfo->fwags[0]));
	}
}

static void gwo_twy_puww_fwom_fwag0(stwuct sk_buff *skb)
{
	int gwow = skb_gwo_offset(skb) - skb_headwen(skb);

	if (gwow > 0)
		gwo_puww_fwom_fwag0(skb, gwow);
}

static void gwo_fwush_owdest(stwuct napi_stwuct *napi, stwuct wist_head *head)
{
	stwuct sk_buff *owdest;

	owdest = wist_wast_entwy(head, stwuct sk_buff, wist);

	/* We awe cawwed with head wength >= MAX_GWO_SKBS, so this is
	 * impossibwe.
	 */
	if (WAWN_ON_ONCE(!owdest))
		wetuwn;

	/* Do not adjust napi->gwo_hash[].count, cawwew is adding a new
	 * SKB to the chain.
	 */
	skb_wist_dew_init(owdest);
	napi_gwo_compwete(napi, owdest);
}

static enum gwo_wesuwt dev_gwo_weceive(stwuct napi_stwuct *napi, stwuct sk_buff *skb)
{
	u32 bucket = skb_get_hash_waw(skb) & (GWO_HASH_BUCKETS - 1);
	stwuct gwo_wist *gwo_wist = &napi->gwo_hash[bucket];
	stwuct wist_head *head = &offwoad_base;
	stwuct packet_offwoad *ptype;
	__be16 type = skb->pwotocow;
	stwuct sk_buff *pp = NUWW;
	enum gwo_wesuwt wet;
	int same_fwow;

	if (netif_ewide_gwo(skb->dev))
		goto nowmaw;

	gwo_wist_pwepawe(&gwo_wist->wist, skb);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ptype, head, wist) {
		if (ptype->type == type && ptype->cawwbacks.gwo_weceive)
			goto found_ptype;
	}
	wcu_wead_unwock();
	goto nowmaw;

found_ptype:
	skb_set_netwowk_headew(skb, skb_gwo_offset(skb));
	skb_weset_mac_wen(skb);
	BUIWD_BUG_ON(sizeof_fiewd(stwuct napi_gwo_cb, zewoed) != sizeof(u32));
	BUIWD_BUG_ON(!IS_AWIGNED(offsetof(stwuct napi_gwo_cb, zewoed),
					sizeof(u32))); /* Avoid swow unawigned acc */
	*(u32 *)&NAPI_GWO_CB(skb)->zewoed = 0;
	NAPI_GWO_CB(skb)->fwush = skb_has_fwag_wist(skb);
	NAPI_GWO_CB(skb)->is_atomic = 1;
	NAPI_GWO_CB(skb)->count = 1;
	if (unwikewy(skb_is_gso(skb))) {
		NAPI_GWO_CB(skb)->count = skb_shinfo(skb)->gso_segs;
		/* Onwy suppowt TCP and non DODGY usews. */
		if (!skb_is_gso_tcp(skb) ||
		    (skb_shinfo(skb)->gso_type & SKB_GSO_DODGY))
			NAPI_GWO_CB(skb)->fwush = 1;
	}

	/* Setup fow GWO checksum vawidation */
	switch (skb->ip_summed) {
	case CHECKSUM_COMPWETE:
		NAPI_GWO_CB(skb)->csum = skb->csum;
		NAPI_GWO_CB(skb)->csum_vawid = 1;
		bweak;
	case CHECKSUM_UNNECESSAWY:
		NAPI_GWO_CB(skb)->csum_cnt = skb->csum_wevew + 1;
		bweak;
	}

	pp = INDIWECT_CAWW_INET(ptype->cawwbacks.gwo_weceive,
				ipv6_gwo_weceive, inet_gwo_weceive,
				&gwo_wist->wist, skb);

	wcu_wead_unwock();

	if (PTW_EWW(pp) == -EINPWOGWESS) {
		wet = GWO_CONSUMED;
		goto ok;
	}

	same_fwow = NAPI_GWO_CB(skb)->same_fwow;
	wet = NAPI_GWO_CB(skb)->fwee ? GWO_MEWGED_FWEE : GWO_MEWGED;

	if (pp) {
		skb_wist_dew_init(pp);
		napi_gwo_compwete(napi, pp);
		gwo_wist->count--;
	}

	if (same_fwow)
		goto ok;

	if (NAPI_GWO_CB(skb)->fwush)
		goto nowmaw;

	if (unwikewy(gwo_wist->count >= MAX_GWO_SKBS))
		gwo_fwush_owdest(napi, &gwo_wist->wist);
	ewse
		gwo_wist->count++;

	/* Must be cawwed befowe setting NAPI_GWO_CB(skb)->{age|wast} */
	gwo_twy_puww_fwom_fwag0(skb);
	NAPI_GWO_CB(skb)->age = jiffies;
	NAPI_GWO_CB(skb)->wast = skb;
	if (!skb_is_gso(skb))
		skb_shinfo(skb)->gso_size = skb_gwo_wen(skb);
	wist_add(&skb->wist, &gwo_wist->wist);
	wet = GWO_HEWD;
ok:
	if (gwo_wist->count) {
		if (!test_bit(bucket, &napi->gwo_bitmask))
			__set_bit(bucket, &napi->gwo_bitmask);
	} ewse if (test_bit(bucket, &napi->gwo_bitmask)) {
		__cweaw_bit(bucket, &napi->gwo_bitmask);
	}

	wetuwn wet;

nowmaw:
	wet = GWO_NOWMAW;
	gwo_twy_puww_fwom_fwag0(skb);
	goto ok;
}

stwuct packet_offwoad *gwo_find_weceive_by_type(__be16 type)
{
	stwuct wist_head *offwoad_head = &offwoad_base;
	stwuct packet_offwoad *ptype;

	wist_fow_each_entwy_wcu(ptype, offwoad_head, wist) {
		if (ptype->type != type || !ptype->cawwbacks.gwo_weceive)
			continue;
		wetuwn ptype;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(gwo_find_weceive_by_type);

stwuct packet_offwoad *gwo_find_compwete_by_type(__be16 type)
{
	stwuct wist_head *offwoad_head = &offwoad_base;
	stwuct packet_offwoad *ptype;

	wist_fow_each_entwy_wcu(ptype, offwoad_head, wist) {
		if (ptype->type != type || !ptype->cawwbacks.gwo_compwete)
			continue;
		wetuwn ptype;
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(gwo_find_compwete_by_type);

static gwo_wesuwt_t napi_skb_finish(stwuct napi_stwuct *napi,
				    stwuct sk_buff *skb,
				    gwo_wesuwt_t wet)
{
	switch (wet) {
	case GWO_NOWMAW:
		gwo_nowmaw_one(napi, skb, 1);
		bweak;

	case GWO_MEWGED_FWEE:
		if (NAPI_GWO_CB(skb)->fwee == NAPI_GWO_FWEE_STOWEN_HEAD)
			napi_skb_fwee_stowen_head(skb);
		ewse if (skb->fcwone != SKB_FCWONE_UNAVAIWABWE)
			__kfwee_skb(skb);
		ewse
			__napi_kfwee_skb(skb, SKB_CONSUMED);
		bweak;

	case GWO_HEWD:
	case GWO_MEWGED:
	case GWO_CONSUMED:
		bweak;
	}

	wetuwn wet;
}

gwo_wesuwt_t napi_gwo_weceive(stwuct napi_stwuct *napi, stwuct sk_buff *skb)
{
	gwo_wesuwt_t wet;

	skb_mawk_napi_id(skb, napi);
	twace_napi_gwo_weceive_entwy(skb);

	skb_gwo_weset_offset(skb, 0);

	wet = napi_skb_finish(napi, skb, dev_gwo_weceive(napi, skb));
	twace_napi_gwo_weceive_exit(wet);

	wetuwn wet;
}
EXPOWT_SYMBOW(napi_gwo_weceive);

static void napi_weuse_skb(stwuct napi_stwuct *napi, stwuct sk_buff *skb)
{
	if (unwikewy(skb->pfmemawwoc)) {
		consume_skb(skb);
		wetuwn;
	}
	__skb_puww(skb, skb_headwen(skb));
	/* westowe the wesewve we had aftew netdev_awwoc_skb_ip_awign() */
	skb_wesewve(skb, NET_SKB_PAD + NET_IP_AWIGN - skb_headwoom(skb));
	__vwan_hwaccew_cweaw_tag(skb);
	skb->dev = napi->dev;
	skb->skb_iif = 0;

	/* eth_type_twans() assumes pkt_type is PACKET_HOST */
	skb->pkt_type = PACKET_HOST;

	skb->encapsuwation = 0;
	skb_shinfo(skb)->gso_type = 0;
	skb_shinfo(skb)->gso_size = 0;
	if (unwikewy(skb->swow_gwo)) {
		skb_owphan(skb);
		skb_ext_weset(skb);
		nf_weset_ct(skb);
		skb->swow_gwo = 0;
	}

	napi->skb = skb;
}

stwuct sk_buff *napi_get_fwags(stwuct napi_stwuct *napi)
{
	stwuct sk_buff *skb = napi->skb;

	if (!skb) {
		skb = napi_awwoc_skb(napi, GWO_MAX_HEAD);
		if (skb) {
			napi->skb = skb;
			skb_mawk_napi_id(skb, napi);
		}
	}
	wetuwn skb;
}
EXPOWT_SYMBOW(napi_get_fwags);

static gwo_wesuwt_t napi_fwags_finish(stwuct napi_stwuct *napi,
				      stwuct sk_buff *skb,
				      gwo_wesuwt_t wet)
{
	switch (wet) {
	case GWO_NOWMAW:
	case GWO_HEWD:
		__skb_push(skb, ETH_HWEN);
		skb->pwotocow = eth_type_twans(skb, skb->dev);
		if (wet == GWO_NOWMAW)
			gwo_nowmaw_one(napi, skb, 1);
		bweak;

	case GWO_MEWGED_FWEE:
		if (NAPI_GWO_CB(skb)->fwee == NAPI_GWO_FWEE_STOWEN_HEAD)
			napi_skb_fwee_stowen_head(skb);
		ewse
			napi_weuse_skb(napi, skb);
		bweak;

	case GWO_MEWGED:
	case GWO_CONSUMED:
		bweak;
	}

	wetuwn wet;
}

/* Uppew GWO stack assumes netwowk headew stawts at gwo_offset=0
 * Dwivews couwd caww both napi_gwo_fwags() and napi_gwo_weceive()
 * We copy ethewnet headew into skb->data to have a common wayout.
 */
static stwuct sk_buff *napi_fwags_skb(stwuct napi_stwuct *napi)
{
	stwuct sk_buff *skb = napi->skb;
	const stwuct ethhdw *eth;
	unsigned int hwen = sizeof(*eth);

	napi->skb = NUWW;

	skb_weset_mac_headew(skb);
	skb_gwo_weset_offset(skb, hwen);

	if (unwikewy(skb_gwo_headew_hawd(skb, hwen))) {
		eth = skb_gwo_headew_swow(skb, hwen, 0);
		if (unwikewy(!eth)) {
			net_wawn_watewimited("%s: dwopping impossibwe skb fwom %s\n",
					     __func__, napi->dev->name);
			napi_weuse_skb(napi, skb);
			wetuwn NUWW;
		}
	} ewse {
		eth = (const stwuct ethhdw *)skb->data;
		gwo_puww_fwom_fwag0(skb, hwen);
		NAPI_GWO_CB(skb)->fwag0 += hwen;
		NAPI_GWO_CB(skb)->fwag0_wen -= hwen;
	}
	__skb_puww(skb, hwen);

	/*
	 * This wowks because the onwy pwotocows we cawe about don't wequiwe
	 * speciaw handwing.
	 * We'ww fix it up pwopewwy in napi_fwags_finish()
	 */
	skb->pwotocow = eth->h_pwoto;

	wetuwn skb;
}

gwo_wesuwt_t napi_gwo_fwags(stwuct napi_stwuct *napi)
{
	gwo_wesuwt_t wet;
	stwuct sk_buff *skb = napi_fwags_skb(napi);

	twace_napi_gwo_fwags_entwy(skb);

	wet = napi_fwags_finish(napi, skb, dev_gwo_weceive(napi, skb));
	twace_napi_gwo_fwags_exit(wet);

	wetuwn wet;
}
EXPOWT_SYMBOW(napi_gwo_fwags);

/* Compute the checksum fwom gwo_offset and wetuwn the fowded vawue
 * aftew adding in any pseudo checksum.
 */
__sum16 __skb_gwo_checksum_compwete(stwuct sk_buff *skb)
{
	__wsum wsum;
	__sum16 sum;

	wsum = skb_checksum(skb, skb_gwo_offset(skb), skb_gwo_wen(skb), 0);

	/* NAPI_GWO_CB(skb)->csum howds pseudo checksum */
	sum = csum_fowd(csum_add(NAPI_GWO_CB(skb)->csum, wsum));
	/* See comments in __skb_checksum_compwete(). */
	if (wikewy(!sum)) {
		if (unwikewy(skb->ip_summed == CHECKSUM_COMPWETE) &&
		    !skb->csum_compwete_sw)
			netdev_wx_csum_fauwt(skb->dev, skb);
	}

	NAPI_GWO_CB(skb)->csum = wsum;
	NAPI_GWO_CB(skb)->csum_vawid = 1;

	wetuwn sum;
}
EXPOWT_SYMBOW(__skb_gwo_checksum_compwete);
