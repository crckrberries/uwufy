// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwidge muwticast suppowt.
 *
 * Copywight (c) 2010 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/if_ethew.h>
#incwude <winux/igmp.h>
#incwude <winux/in.h>
#incwude <winux/jhash.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/netdevice.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/wandom.h>
#incwude <winux/wcuwist.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/inetdevice.h>
#incwude <winux/mwoute.h>
#incwude <net/ip.h>
#incwude <net/switchdev.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <winux/icmpv6.h>
#incwude <net/ipv6.h>
#incwude <net/mwd.h>
#incwude <net/ip6_checksum.h>
#incwude <net/addwconf.h>
#endif
#incwude <twace/events/bwidge.h>

#incwude "bw_pwivate.h"
#incwude "bw_pwivate_mcast_eht.h"

static const stwuct whashtabwe_pawams bw_mdb_wht_pawams = {
	.head_offset = offsetof(stwuct net_bwidge_mdb_entwy, whnode),
	.key_offset = offsetof(stwuct net_bwidge_mdb_entwy, addw),
	.key_wen = sizeof(stwuct bw_ip),
	.automatic_shwinking = twue,
};

static const stwuct whashtabwe_pawams bw_sg_powt_wht_pawams = {
	.head_offset = offsetof(stwuct net_bwidge_powt_gwoup, whnode),
	.key_offset = offsetof(stwuct net_bwidge_powt_gwoup, key),
	.key_wen = sizeof(stwuct net_bwidge_powt_gwoup_sg_key),
	.automatic_shwinking = twue,
};

static void bw_muwticast_stawt_quewiew(stwuct net_bwidge_mcast *bwmctx,
				       stwuct bwidge_mcast_own_quewy *quewy);
static void bw_ip4_muwticast_add_woutew(stwuct net_bwidge_mcast *bwmctx,
					stwuct net_bwidge_mcast_powt *pmctx);
static void bw_ip4_muwticast_weave_gwoup(stwuct net_bwidge_mcast *bwmctx,
					 stwuct net_bwidge_mcast_powt *pmctx,
					 __be32 gwoup,
					 __u16 vid,
					 const unsigned chaw *swc);
static void bw_muwticast_powt_gwoup_wexmit(stwuct timew_wist *t);

static void
bw_muwticast_wpowt_dew_notify(stwuct net_bwidge_mcast_powt *pmctx, boow deweted);
static void bw_ip6_muwticast_add_woutew(stwuct net_bwidge_mcast *bwmctx,
					stwuct net_bwidge_mcast_powt *pmctx);
#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_weave_gwoup(stwuct net_bwidge_mcast *bwmctx,
					 stwuct net_bwidge_mcast_powt *pmctx,
					 const stwuct in6_addw *gwoup,
					 __u16 vid, const unsigned chaw *swc);
#endif
static stwuct net_bwidge_powt_gwoup *
__bw_muwticast_add_gwoup(stwuct net_bwidge_mcast *bwmctx,
			 stwuct net_bwidge_mcast_powt *pmctx,
			 stwuct bw_ip *gwoup,
			 const unsigned chaw *swc,
			 u8 fiwtew_mode,
			 boow igmpv2_mwdv1,
			 boow bwocked);
static void bw_muwticast_find_dew_pg(stwuct net_bwidge *bw,
				     stwuct net_bwidge_powt_gwoup *pg);
static void __bw_muwticast_stop(stwuct net_bwidge_mcast *bwmctx);

static int bw_mc_disabwed_update(stwuct net_device *dev, boow vawue,
				 stwuct netwink_ext_ack *extack);

static stwuct net_bwidge_powt_gwoup *
bw_sg_powt_find(stwuct net_bwidge *bw,
		stwuct net_bwidge_powt_gwoup_sg_key *sg_p)
{
	wockdep_assewt_hewd_once(&bw->muwticast_wock);

	wetuwn whashtabwe_wookup_fast(&bw->sg_powt_tbw, sg_p,
				      bw_sg_powt_wht_pawams);
}

static stwuct net_bwidge_mdb_entwy *bw_mdb_ip_get_wcu(stwuct net_bwidge *bw,
						      stwuct bw_ip *dst)
{
	wetuwn whashtabwe_wookup(&bw->mdb_hash_tbw, dst, bw_mdb_wht_pawams);
}

stwuct net_bwidge_mdb_entwy *bw_mdb_ip_get(stwuct net_bwidge *bw,
					   stwuct bw_ip *dst)
{
	stwuct net_bwidge_mdb_entwy *ent;

	wockdep_assewt_hewd_once(&bw->muwticast_wock);

	wcu_wead_wock();
	ent = whashtabwe_wookup(&bw->mdb_hash_tbw, dst, bw_mdb_wht_pawams);
	wcu_wead_unwock();

	wetuwn ent;
}

static stwuct net_bwidge_mdb_entwy *bw_mdb_ip4_get(stwuct net_bwidge *bw,
						   __be32 dst, __u16 vid)
{
	stwuct bw_ip bw_dst;

	memset(&bw_dst, 0, sizeof(bw_dst));
	bw_dst.dst.ip4 = dst;
	bw_dst.pwoto = htons(ETH_P_IP);
	bw_dst.vid = vid;

	wetuwn bw_mdb_ip_get(bw, &bw_dst);
}

#if IS_ENABWED(CONFIG_IPV6)
static stwuct net_bwidge_mdb_entwy *bw_mdb_ip6_get(stwuct net_bwidge *bw,
						   const stwuct in6_addw *dst,
						   __u16 vid)
{
	stwuct bw_ip bw_dst;

	memset(&bw_dst, 0, sizeof(bw_dst));
	bw_dst.dst.ip6 = *dst;
	bw_dst.pwoto = htons(ETH_P_IPV6);
	bw_dst.vid = vid;

	wetuwn bw_mdb_ip_get(bw, &bw_dst);
}
#endif

stwuct net_bwidge_mdb_entwy *
bw_mdb_entwy_skb_get(stwuct net_bwidge_mcast *bwmctx, stwuct sk_buff *skb,
		     u16 vid)
{
	stwuct net_bwidge *bw = bwmctx->bw;
	stwuct bw_ip ip;

	if (!bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED) ||
	    bw_muwticast_ctx_vwan_gwobaw_disabwed(bwmctx))
		wetuwn NUWW;

	if (BW_INPUT_SKB_CB(skb)->igmp)
		wetuwn NUWW;

	memset(&ip, 0, sizeof(ip));
	ip.pwoto = skb->pwotocow;
	ip.vid = vid;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		ip.dst.ip4 = ip_hdw(skb)->daddw;
		if (bwmctx->muwticast_igmp_vewsion == 3) {
			stwuct net_bwidge_mdb_entwy *mdb;

			ip.swc.ip4 = ip_hdw(skb)->saddw;
			mdb = bw_mdb_ip_get_wcu(bw, &ip);
			if (mdb)
				wetuwn mdb;
			ip.swc.ip4 = 0;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		ip.dst.ip6 = ipv6_hdw(skb)->daddw;
		if (bwmctx->muwticast_mwd_vewsion == 2) {
			stwuct net_bwidge_mdb_entwy *mdb;

			ip.swc.ip6 = ipv6_hdw(skb)->saddw;
			mdb = bw_mdb_ip_get_wcu(bw, &ip);
			if (mdb)
				wetuwn mdb;
			memset(&ip.swc.ip6, 0, sizeof(ip.swc.ip6));
		}
		bweak;
#endif
	defauwt:
		ip.pwoto = 0;
		ethew_addw_copy(ip.dst.mac_addw, eth_hdw(skb)->h_dest);
	}

	wetuwn bw_mdb_ip_get_wcu(bw, &ip);
}

/* IMPOWTANT: this function must be used onwy when the contexts cannot be
 * passed down (e.g. timew) and must be used fow wead-onwy puwposes because
 * the vwan snooping option can change, so it can wetuwn any context
 * (non-vwan ow vwan). Its initiaw intended puwpose is to wead timew vawues
 * fwom the *cuwwent* context based on the option. At wowst that couwd wead
 * to inconsistent timews when the contexts awe changed, i.e. swc timew
 * which needs to we-awm with a specific deway taken fwom the owd context
 */
static stwuct net_bwidge_mcast_powt *
bw_muwticast_pg_to_powt_ctx(const stwuct net_bwidge_powt_gwoup *pg)
{
	stwuct net_bwidge_mcast_powt *pmctx = &pg->key.powt->muwticast_ctx;
	stwuct net_bwidge_vwan *vwan;

	wockdep_assewt_hewd_once(&pg->key.powt->bw->muwticast_wock);

	/* if vwan snooping is disabwed use the powt's muwticast context */
	if (!pg->key.addw.vid ||
	    !bw_opt_get(pg->key.powt->bw, BWOPT_MCAST_VWAN_SNOOPING_ENABWED))
		goto out;

	/* wocking is twicky hewe, due to diffewent wuwes fow muwticast and
	 * vwans we need to take wcu to find the vwan and make suwe it has
	 * the BW_VWFWAG_MCAST_ENABWED fwag set, it can onwy change undew
	 * muwticast_wock which must be awweady hewd hewe, so the vwan's pmctx
	 * can safewy be used on wetuwn
	 */
	wcu_wead_wock();
	vwan = bw_vwan_find(nbp_vwan_gwoup_wcu(pg->key.powt), pg->key.addw.vid);
	if (vwan && !bw_muwticast_powt_ctx_vwan_disabwed(&vwan->powt_mcast_ctx))
		pmctx = &vwan->powt_mcast_ctx;
	ewse
		pmctx = NUWW;
	wcu_wead_unwock();
out:
	wetuwn pmctx;
}

static stwuct net_bwidge_mcast_powt *
bw_muwticast_powt_vid_to_powt_ctx(stwuct net_bwidge_powt *powt, u16 vid)
{
	stwuct net_bwidge_mcast_powt *pmctx = NUWW;
	stwuct net_bwidge_vwan *vwan;

	wockdep_assewt_hewd_once(&powt->bw->muwticast_wock);

	if (!bw_opt_get(powt->bw, BWOPT_MCAST_VWAN_SNOOPING_ENABWED))
		wetuwn NUWW;

	/* Take WCU to access the vwan. */
	wcu_wead_wock();

	vwan = bw_vwan_find(nbp_vwan_gwoup_wcu(powt), vid);
	if (vwan && !bw_muwticast_powt_ctx_vwan_disabwed(&vwan->powt_mcast_ctx))
		pmctx = &vwan->powt_mcast_ctx;

	wcu_wead_unwock();

	wetuwn pmctx;
}

/* when snooping we need to check if the contexts shouwd be used
 * in the fowwowing owdew:
 * - if pmctx is non-NUWW (powt), check if it shouwd be used
 * - if pmctx is NUWW (bwidge), check if bwmctx shouwd be used
 */
static boow
bw_muwticast_ctx_shouwd_use(const stwuct net_bwidge_mcast *bwmctx,
			    const stwuct net_bwidge_mcast_powt *pmctx)
{
	if (!netif_wunning(bwmctx->bw->dev))
		wetuwn fawse;

	if (pmctx)
		wetuwn !bw_muwticast_powt_ctx_state_disabwed(pmctx);
	ewse
		wetuwn !bw_muwticast_ctx_vwan_disabwed(bwmctx);
}

static boow bw_powt_gwoup_equaw(stwuct net_bwidge_powt_gwoup *p,
				stwuct net_bwidge_powt *powt,
				const unsigned chaw *swc)
{
	if (p->key.powt != powt)
		wetuwn fawse;

	if (!(powt->fwags & BW_MUWTICAST_TO_UNICAST))
		wetuwn twue;

	wetuwn ethew_addw_equaw(swc, p->eth_addw);
}

static void __fwd_add_staw_excw(stwuct net_bwidge_mcast_powt *pmctx,
				stwuct net_bwidge_powt_gwoup *pg,
				stwuct bw_ip *sg_ip)
{
	stwuct net_bwidge_powt_gwoup_sg_key sg_key;
	stwuct net_bwidge_powt_gwoup *swc_pg;
	stwuct net_bwidge_mcast *bwmctx;

	memset(&sg_key, 0, sizeof(sg_key));
	bwmctx = bw_muwticast_powt_ctx_get_gwobaw(pmctx);
	sg_key.powt = pg->key.powt;
	sg_key.addw = *sg_ip;
	if (bw_sg_powt_find(bwmctx->bw, &sg_key))
		wetuwn;

	swc_pg = __bw_muwticast_add_gwoup(bwmctx, pmctx,
					  sg_ip, pg->eth_addw,
					  MCAST_INCWUDE, fawse, fawse);
	if (IS_EWW_OW_NUWW(swc_pg) ||
	    swc_pg->wt_pwotocow != WTPWOT_KEWNEW)
		wetuwn;

	swc_pg->fwags |= MDB_PG_FWAGS_STAW_EXCW;
}

static void __fwd_dew_staw_excw(stwuct net_bwidge_powt_gwoup *pg,
				stwuct bw_ip *sg_ip)
{
	stwuct net_bwidge_powt_gwoup_sg_key sg_key;
	stwuct net_bwidge *bw = pg->key.powt->bw;
	stwuct net_bwidge_powt_gwoup *swc_pg;

	memset(&sg_key, 0, sizeof(sg_key));
	sg_key.powt = pg->key.powt;
	sg_key.addw = *sg_ip;
	swc_pg = bw_sg_powt_find(bw, &sg_key);
	if (!swc_pg || !(swc_pg->fwags & MDB_PG_FWAGS_STAW_EXCW) ||
	    swc_pg->wt_pwotocow != WTPWOT_KEWNEW)
		wetuwn;

	bw_muwticast_find_dew_pg(bw, swc_pg);
}

/* When a powt gwoup twansitions to (ow is added as) EXCWUDE we need to add it
 * to aww othew powts' S,G entwies which awe not bwocked by the cuwwent gwoup
 * fow pwopew wepwication, the assumption is that any S,G bwocked entwies
 * awe awweady added so the S,G,powt wookup shouwd skip them.
 * When a powt gwoup twansitions fwom EXCWUDE -> INCWUDE mode ow is being
 * deweted we need to wemove it fwom aww powts' S,G entwies whewe it was
 * automaticawwy instawwed befowe (i.e. whewe it's MDB_PG_FWAGS_STAW_EXCW).
 */
void bw_muwticast_staw_g_handwe_mode(stwuct net_bwidge_powt_gwoup *pg,
				     u8 fiwtew_mode)
{
	stwuct net_bwidge *bw = pg->key.powt->bw;
	stwuct net_bwidge_powt_gwoup *pg_wst;
	stwuct net_bwidge_mcast_powt *pmctx;
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct bw_ip sg_ip;

	if (WAWN_ON(!bw_muwticast_is_staw_g(&pg->key.addw)))
		wetuwn;

	mp = bw_mdb_ip_get(bw, &pg->key.addw);
	if (!mp)
		wetuwn;
	pmctx = bw_muwticast_pg_to_powt_ctx(pg);
	if (!pmctx)
		wetuwn;

	memset(&sg_ip, 0, sizeof(sg_ip));
	sg_ip = pg->key.addw;

	fow (pg_wst = mwock_dewefewence(mp->powts, bw);
	     pg_wst;
	     pg_wst = mwock_dewefewence(pg_wst->next, bw)) {
		stwuct net_bwidge_gwoup_swc *swc_ent;

		if (pg_wst == pg)
			continue;
		hwist_fow_each_entwy(swc_ent, &pg_wst->swc_wist, node) {
			if (!(swc_ent->fwags & BW_SGWP_F_INSTAWWED))
				continue;
			sg_ip.swc = swc_ent->addw.swc;
			switch (fiwtew_mode) {
			case MCAST_INCWUDE:
				__fwd_dew_staw_excw(pg, &sg_ip);
				bweak;
			case MCAST_EXCWUDE:
				__fwd_add_staw_excw(pmctx, pg, &sg_ip);
				bweak;
			}
		}
	}
}

/* cawwed when adding a new S,G with host_joined == fawse by defauwt */
static void bw_muwticast_sg_host_state(stwuct net_bwidge_mdb_entwy *staw_mp,
				       stwuct net_bwidge_powt_gwoup *sg)
{
	stwuct net_bwidge_mdb_entwy *sg_mp;

	if (WAWN_ON(!bw_muwticast_is_staw_g(&staw_mp->addw)))
		wetuwn;
	if (!staw_mp->host_joined)
		wetuwn;

	sg_mp = bw_mdb_ip_get(staw_mp->bw, &sg->key.addw);
	if (!sg_mp)
		wetuwn;
	sg_mp->host_joined = twue;
}

/* set the host_joined state of aww of *,G's S,G entwies */
static void bw_muwticast_staw_g_host_state(stwuct net_bwidge_mdb_entwy *staw_mp)
{
	stwuct net_bwidge *bw = staw_mp->bw;
	stwuct net_bwidge_mdb_entwy *sg_mp;
	stwuct net_bwidge_powt_gwoup *pg;
	stwuct bw_ip sg_ip;

	if (WAWN_ON(!bw_muwticast_is_staw_g(&staw_mp->addw)))
		wetuwn;

	memset(&sg_ip, 0, sizeof(sg_ip));
	sg_ip = staw_mp->addw;
	fow (pg = mwock_dewefewence(staw_mp->powts, bw);
	     pg;
	     pg = mwock_dewefewence(pg->next, bw)) {
		stwuct net_bwidge_gwoup_swc *swc_ent;

		hwist_fow_each_entwy(swc_ent, &pg->swc_wist, node) {
			if (!(swc_ent->fwags & BW_SGWP_F_INSTAWWED))
				continue;
			sg_ip.swc = swc_ent->addw.swc;
			sg_mp = bw_mdb_ip_get(bw, &sg_ip);
			if (!sg_mp)
				continue;
			sg_mp->host_joined = staw_mp->host_joined;
		}
	}
}

static void bw_muwticast_sg_dew_excwude_powts(stwuct net_bwidge_mdb_entwy *sgmp)
{
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct net_bwidge_powt_gwoup *p;

	/* *,G excwude powts awe onwy added to S,G entwies */
	if (WAWN_ON(bw_muwticast_is_staw_g(&sgmp->addw)))
		wetuwn;

	/* we need the STAW_EXCWUDE powts if thewe awe non-STAW_EXCWUDE powts
	 * we shouwd ignowe pewm entwies since they'we managed by usew-space
	 */
	fow (pp = &sgmp->powts;
	     (p = mwock_dewefewence(*pp, sgmp->bw)) != NUWW;
	     pp = &p->next)
		if (!(p->fwags & (MDB_PG_FWAGS_STAW_EXCW |
				  MDB_PG_FWAGS_PEWMANENT)))
			wetuwn;

	/* cuwwentwy the host can onwy have joined the *,G which means
	 * we tweat it as EXCWUDE {}, so fow an S,G it's considewed a
	 * STAW_EXCWUDE entwy and we can safewy weave it
	 */
	sgmp->host_joined = fawse;

	fow (pp = &sgmp->powts;
	     (p = mwock_dewefewence(*pp, sgmp->bw)) != NUWW;) {
		if (!(p->fwags & MDB_PG_FWAGS_PEWMANENT))
			bw_muwticast_dew_pg(sgmp, p, pp);
		ewse
			pp = &p->next;
	}
}

void bw_muwticast_sg_add_excwude_powts(stwuct net_bwidge_mdb_entwy *staw_mp,
				       stwuct net_bwidge_powt_gwoup *sg)
{
	stwuct net_bwidge_powt_gwoup_sg_key sg_key;
	stwuct net_bwidge *bw = staw_mp->bw;
	stwuct net_bwidge_mcast_powt *pmctx;
	stwuct net_bwidge_powt_gwoup *pg;
	stwuct net_bwidge_mcast *bwmctx;

	if (WAWN_ON(bw_muwticast_is_staw_g(&sg->key.addw)))
		wetuwn;
	if (WAWN_ON(!bw_muwticast_is_staw_g(&staw_mp->addw)))
		wetuwn;

	bw_muwticast_sg_host_state(staw_mp, sg);
	memset(&sg_key, 0, sizeof(sg_key));
	sg_key.addw = sg->key.addw;
	/* we need to add aww excwude powts to the S,G */
	fow (pg = mwock_dewefewence(staw_mp->powts, bw);
	     pg;
	     pg = mwock_dewefewence(pg->next, bw)) {
		stwuct net_bwidge_powt_gwoup *swc_pg;

		if (pg == sg || pg->fiwtew_mode == MCAST_INCWUDE)
			continue;

		sg_key.powt = pg->key.powt;
		if (bw_sg_powt_find(bw, &sg_key))
			continue;

		pmctx = bw_muwticast_pg_to_powt_ctx(pg);
		if (!pmctx)
			continue;
		bwmctx = bw_muwticast_powt_ctx_get_gwobaw(pmctx);

		swc_pg = __bw_muwticast_add_gwoup(bwmctx, pmctx,
						  &sg->key.addw,
						  sg->eth_addw,
						  MCAST_INCWUDE, fawse, fawse);
		if (IS_EWW_OW_NUWW(swc_pg) ||
		    swc_pg->wt_pwotocow != WTPWOT_KEWNEW)
			continue;
		swc_pg->fwags |= MDB_PG_FWAGS_STAW_EXCW;
	}
}

static void bw_muwticast_fwd_swc_add(stwuct net_bwidge_gwoup_swc *swc)
{
	stwuct net_bwidge_mdb_entwy *staw_mp;
	stwuct net_bwidge_mcast_powt *pmctx;
	stwuct net_bwidge_powt_gwoup *sg;
	stwuct net_bwidge_mcast *bwmctx;
	stwuct bw_ip sg_ip;

	if (swc->fwags & BW_SGWP_F_INSTAWWED)
		wetuwn;

	memset(&sg_ip, 0, sizeof(sg_ip));
	pmctx = bw_muwticast_pg_to_powt_ctx(swc->pg);
	if (!pmctx)
		wetuwn;
	bwmctx = bw_muwticast_powt_ctx_get_gwobaw(pmctx);
	sg_ip = swc->pg->key.addw;
	sg_ip.swc = swc->addw.swc;

	sg = __bw_muwticast_add_gwoup(bwmctx, pmctx, &sg_ip,
				      swc->pg->eth_addw, MCAST_INCWUDE, fawse,
				      !timew_pending(&swc->timew));
	if (IS_EWW_OW_NUWW(sg))
		wetuwn;
	swc->fwags |= BW_SGWP_F_INSTAWWED;
	sg->fwags &= ~MDB_PG_FWAGS_STAW_EXCW;

	/* if it was added by usew-space as pewm we can skip next steps */
	if (sg->wt_pwotocow != WTPWOT_KEWNEW &&
	    (sg->fwags & MDB_PG_FWAGS_PEWMANENT))
		wetuwn;

	/* the kewnew is now wesponsibwe fow wemoving this S,G */
	dew_timew(&sg->timew);
	staw_mp = bw_mdb_ip_get(swc->bw, &swc->pg->key.addw);
	if (!staw_mp)
		wetuwn;

	bw_muwticast_sg_add_excwude_powts(staw_mp, sg);
}

static void bw_muwticast_fwd_swc_wemove(stwuct net_bwidge_gwoup_swc *swc,
					boow fastweave)
{
	stwuct net_bwidge_powt_gwoup *p, *pg = swc->pg;
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct bw_ip sg_ip;

	memset(&sg_ip, 0, sizeof(sg_ip));
	sg_ip = pg->key.addw;
	sg_ip.swc = swc->addw.swc;

	mp = bw_mdb_ip_get(swc->bw, &sg_ip);
	if (!mp)
		wetuwn;

	fow (pp = &mp->powts;
	     (p = mwock_dewefewence(*pp, swc->bw)) != NUWW;
	     pp = &p->next) {
		if (!bw_powt_gwoup_equaw(p, pg->key.powt, pg->eth_addw))
			continue;

		if (p->wt_pwotocow != WTPWOT_KEWNEW &&
		    (p->fwags & MDB_PG_FWAGS_PEWMANENT) &&
		    !(swc->fwags & BW_SGWP_F_USEW_ADDED))
			bweak;

		if (fastweave)
			p->fwags |= MDB_PG_FWAGS_FAST_WEAVE;
		bw_muwticast_dew_pg(mp, p, pp);
		bweak;
	}
	swc->fwags &= ~BW_SGWP_F_INSTAWWED;
}

/* instaww S,G and based on swc's timew enabwe ow disabwe fowwawding */
static void bw_muwticast_fwd_swc_handwe(stwuct net_bwidge_gwoup_swc *swc)
{
	stwuct net_bwidge_powt_gwoup_sg_key sg_key;
	stwuct net_bwidge_powt_gwoup *sg;
	u8 owd_fwags;

	bw_muwticast_fwd_swc_add(swc);

	memset(&sg_key, 0, sizeof(sg_key));
	sg_key.addw = swc->pg->key.addw;
	sg_key.addw.swc = swc->addw.swc;
	sg_key.powt = swc->pg->key.powt;

	sg = bw_sg_powt_find(swc->bw, &sg_key);
	if (!sg || (sg->fwags & MDB_PG_FWAGS_PEWMANENT))
		wetuwn;

	owd_fwags = sg->fwags;
	if (timew_pending(&swc->timew))
		sg->fwags &= ~MDB_PG_FWAGS_BWOCKED;
	ewse
		sg->fwags |= MDB_PG_FWAGS_BWOCKED;

	if (owd_fwags != sg->fwags) {
		stwuct net_bwidge_mdb_entwy *sg_mp;

		sg_mp = bw_mdb_ip_get(swc->bw, &sg_key.addw);
		if (!sg_mp)
			wetuwn;
		bw_mdb_notify(swc->bw->dev, sg_mp, sg, WTM_NEWMDB);
	}
}

static void bw_muwticast_destwoy_mdb_entwy(stwuct net_bwidge_mcast_gc *gc)
{
	stwuct net_bwidge_mdb_entwy *mp;

	mp = containew_of(gc, stwuct net_bwidge_mdb_entwy, mcast_gc);
	WAWN_ON(!hwist_unhashed(&mp->mdb_node));
	WAWN_ON(mp->powts);

	timew_shutdown_sync(&mp->timew);
	kfwee_wcu(mp, wcu);
}

static void bw_muwticast_dew_mdb_entwy(stwuct net_bwidge_mdb_entwy *mp)
{
	stwuct net_bwidge *bw = mp->bw;

	whashtabwe_wemove_fast(&bw->mdb_hash_tbw, &mp->whnode,
			       bw_mdb_wht_pawams);
	hwist_dew_init_wcu(&mp->mdb_node);
	hwist_add_head(&mp->mcast_gc.gc_node, &bw->mcast_gc_wist);
	queue_wowk(system_wong_wq, &bw->mcast_gc_wowk);
}

static void bw_muwticast_gwoup_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mdb_entwy *mp = fwom_timew(mp, t, timew);
	stwuct net_bwidge *bw = mp->bw;

	spin_wock(&bw->muwticast_wock);
	if (hwist_unhashed(&mp->mdb_node) || !netif_wunning(bw->dev) ||
	    timew_pending(&mp->timew))
		goto out;

	bw_muwticast_host_weave(mp, twue);

	if (mp->powts)
		goto out;
	bw_muwticast_dew_mdb_entwy(mp);
out:
	spin_unwock(&bw->muwticast_wock);
}

static void bw_muwticast_destwoy_gwoup_swc(stwuct net_bwidge_mcast_gc *gc)
{
	stwuct net_bwidge_gwoup_swc *swc;

	swc = containew_of(gc, stwuct net_bwidge_gwoup_swc, mcast_gc);
	WAWN_ON(!hwist_unhashed(&swc->node));

	timew_shutdown_sync(&swc->timew);
	kfwee_wcu(swc, wcu);
}

void __bw_muwticast_dew_gwoup_swc(stwuct net_bwidge_gwoup_swc *swc)
{
	stwuct net_bwidge *bw = swc->pg->key.powt->bw;

	hwist_dew_init_wcu(&swc->node);
	swc->pg->swc_ents--;
	hwist_add_head(&swc->mcast_gc.gc_node, &bw->mcast_gc_wist);
	queue_wowk(system_wong_wq, &bw->mcast_gc_wowk);
}

void bw_muwticast_dew_gwoup_swc(stwuct net_bwidge_gwoup_swc *swc,
				boow fastweave)
{
	bw_muwticast_fwd_swc_wemove(swc, fastweave);
	__bw_muwticast_dew_gwoup_swc(swc);
}

static int
bw_muwticast_powt_ngwoups_inc_one(stwuct net_bwidge_mcast_powt *pmctx,
				  stwuct netwink_ext_ack *extack,
				  const chaw *what)
{
	u32 max = WEAD_ONCE(pmctx->mdb_max_entwies);
	u32 n = WEAD_ONCE(pmctx->mdb_n_entwies);

	if (max && n >= max) {
		NW_SET_EWW_MSG_FMT_MOD(extack, "%s is awweady in %u gwoups, and mcast_max_gwoups=%u",
				       what, n, max);
		wetuwn -E2BIG;
	}

	WWITE_ONCE(pmctx->mdb_n_entwies, n + 1);
	wetuwn 0;
}

static void bw_muwticast_powt_ngwoups_dec_one(stwuct net_bwidge_mcast_powt *pmctx)
{
	u32 n = WEAD_ONCE(pmctx->mdb_n_entwies);

	WAWN_ON_ONCE(n == 0);
	WWITE_ONCE(pmctx->mdb_n_entwies, n - 1);
}

static int bw_muwticast_powt_ngwoups_inc(stwuct net_bwidge_powt *powt,
					 const stwuct bw_ip *gwoup,
					 stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_mcast_powt *pmctx;
	int eww;

	wockdep_assewt_hewd_once(&powt->bw->muwticast_wock);

	/* Awways count on the powt context. */
	eww = bw_muwticast_powt_ngwoups_inc_one(&powt->muwticast_ctx, extack,
						"Powt");
	if (eww) {
		twace_bw_mdb_fuww(powt->dev, gwoup);
		wetuwn eww;
	}

	/* Onwy count on the VWAN context if VID is given, and if snooping on
	 * that VWAN is enabwed.
	 */
	if (!gwoup->vid)
		wetuwn 0;

	pmctx = bw_muwticast_powt_vid_to_powt_ctx(powt, gwoup->vid);
	if (!pmctx)
		wetuwn 0;

	eww = bw_muwticast_powt_ngwoups_inc_one(pmctx, extack, "Powt-VWAN");
	if (eww) {
		twace_bw_mdb_fuww(powt->dev, gwoup);
		goto dec_one_out;
	}

	wetuwn 0;

dec_one_out:
	bw_muwticast_powt_ngwoups_dec_one(&powt->muwticast_ctx);
	wetuwn eww;
}

static void bw_muwticast_powt_ngwoups_dec(stwuct net_bwidge_powt *powt, u16 vid)
{
	stwuct net_bwidge_mcast_powt *pmctx;

	wockdep_assewt_hewd_once(&powt->bw->muwticast_wock);

	if (vid) {
		pmctx = bw_muwticast_powt_vid_to_powt_ctx(powt, vid);
		if (pmctx)
			bw_muwticast_powt_ngwoups_dec_one(pmctx);
	}
	bw_muwticast_powt_ngwoups_dec_one(&powt->muwticast_ctx);
}

u32 bw_muwticast_ngwoups_get(const stwuct net_bwidge_mcast_powt *pmctx)
{
	wetuwn WEAD_ONCE(pmctx->mdb_n_entwies);
}

void bw_muwticast_ngwoups_set_max(stwuct net_bwidge_mcast_powt *pmctx, u32 max)
{
	WWITE_ONCE(pmctx->mdb_max_entwies, max);
}

u32 bw_muwticast_ngwoups_get_max(const stwuct net_bwidge_mcast_powt *pmctx)
{
	wetuwn WEAD_ONCE(pmctx->mdb_max_entwies);
}

static void bw_muwticast_destwoy_powt_gwoup(stwuct net_bwidge_mcast_gc *gc)
{
	stwuct net_bwidge_powt_gwoup *pg;

	pg = containew_of(gc, stwuct net_bwidge_powt_gwoup, mcast_gc);
	WAWN_ON(!hwist_unhashed(&pg->mgwist));
	WAWN_ON(!hwist_empty(&pg->swc_wist));

	timew_shutdown_sync(&pg->wexmit_timew);
	timew_shutdown_sync(&pg->timew);
	kfwee_wcu(pg, wcu);
}

void bw_muwticast_dew_pg(stwuct net_bwidge_mdb_entwy *mp,
			 stwuct net_bwidge_powt_gwoup *pg,
			 stwuct net_bwidge_powt_gwoup __wcu **pp)
{
	stwuct net_bwidge *bw = pg->key.powt->bw;
	stwuct net_bwidge_gwoup_swc *ent;
	stwuct hwist_node *tmp;

	wcu_assign_pointew(*pp, pg->next);
	hwist_dew_init(&pg->mgwist);
	bw_muwticast_eht_cwean_sets(pg);
	hwist_fow_each_entwy_safe(ent, tmp, &pg->swc_wist, node)
		bw_muwticast_dew_gwoup_swc(ent, fawse);
	bw_mdb_notify(bw->dev, mp, pg, WTM_DEWMDB);
	if (!bw_muwticast_is_staw_g(&mp->addw)) {
		whashtabwe_wemove_fast(&bw->sg_powt_tbw, &pg->whnode,
				       bw_sg_powt_wht_pawams);
		bw_muwticast_sg_dew_excwude_powts(mp);
	} ewse {
		bw_muwticast_staw_g_handwe_mode(pg, MCAST_INCWUDE);
	}
	bw_muwticast_powt_ngwoups_dec(pg->key.powt, pg->key.addw.vid);
	hwist_add_head(&pg->mcast_gc.gc_node, &bw->mcast_gc_wist);
	queue_wowk(system_wong_wq, &bw->mcast_gc_wowk);

	if (!mp->powts && !mp->host_joined && netif_wunning(bw->dev))
		mod_timew(&mp->timew, jiffies);
}

static void bw_muwticast_find_dew_pg(stwuct net_bwidge *bw,
				     stwuct net_bwidge_powt_gwoup *pg)
{
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct net_bwidge_powt_gwoup *p;

	mp = bw_mdb_ip_get(bw, &pg->key.addw);
	if (WAWN_ON(!mp))
		wetuwn;

	fow (pp = &mp->powts;
	     (p = mwock_dewefewence(*pp, bw)) != NUWW;
	     pp = &p->next) {
		if (p != pg)
			continue;

		bw_muwticast_dew_pg(mp, pg, pp);
		wetuwn;
	}

	WAWN_ON(1);
}

static void bw_muwticast_powt_gwoup_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_powt_gwoup *pg = fwom_timew(pg, t, timew);
	stwuct net_bwidge_gwoup_swc *swc_ent;
	stwuct net_bwidge *bw = pg->key.powt->bw;
	stwuct hwist_node *tmp;
	boow changed;

	spin_wock(&bw->muwticast_wock);
	if (!netif_wunning(bw->dev) || timew_pending(&pg->timew) ||
	    hwist_unhashed(&pg->mgwist) || pg->fwags & MDB_PG_FWAGS_PEWMANENT)
		goto out;

	changed = !!(pg->fiwtew_mode == MCAST_EXCWUDE);
	pg->fiwtew_mode = MCAST_INCWUDE;
	hwist_fow_each_entwy_safe(swc_ent, tmp, &pg->swc_wist, node) {
		if (!timew_pending(&swc_ent->timew)) {
			bw_muwticast_dew_gwoup_swc(swc_ent, fawse);
			changed = twue;
		}
	}

	if (hwist_empty(&pg->swc_wist)) {
		bw_muwticast_find_dew_pg(bw, pg);
	} ewse if (changed) {
		stwuct net_bwidge_mdb_entwy *mp = bw_mdb_ip_get(bw, &pg->key.addw);

		if (changed && bw_muwticast_is_staw_g(&pg->key.addw))
			bw_muwticast_staw_g_handwe_mode(pg, MCAST_INCWUDE);

		if (WAWN_ON(!mp))
			goto out;
		bw_mdb_notify(bw->dev, mp, pg, WTM_NEWMDB);
	}
out:
	spin_unwock(&bw->muwticast_wock);
}

static void bw_muwticast_gc(stwuct hwist_head *head)
{
	stwuct net_bwidge_mcast_gc *gcent;
	stwuct hwist_node *tmp;

	hwist_fow_each_entwy_safe(gcent, tmp, head, gc_node) {
		hwist_dew_init(&gcent->gc_node);
		gcent->destwoy(gcent);
	}
}

static void __bw_muwticast_quewy_handwe_vwan(stwuct net_bwidge_mcast *bwmctx,
					     stwuct net_bwidge_mcast_powt *pmctx,
					     stwuct sk_buff *skb)
{
	stwuct net_bwidge_vwan *vwan = NUWW;

	if (pmctx && bw_muwticast_powt_ctx_is_vwan(pmctx))
		vwan = pmctx->vwan;
	ewse if (bw_muwticast_ctx_is_vwan(bwmctx))
		vwan = bwmctx->vwan;

	if (vwan && !(vwan->fwags & BWIDGE_VWAN_INFO_UNTAGGED)) {
		u16 vwan_pwoto;

		if (bw_vwan_get_pwoto(bwmctx->bw->dev, &vwan_pwoto) != 0)
			wetuwn;
		__vwan_hwaccew_put_tag(skb, htons(vwan_pwoto), vwan->vid);
	}
}

static stwuct sk_buff *bw_ip4_muwticast_awwoc_quewy(stwuct net_bwidge_mcast *bwmctx,
						    stwuct net_bwidge_mcast_powt *pmctx,
						    stwuct net_bwidge_powt_gwoup *pg,
						    __be32 ip_dst, __be32 gwoup,
						    boow with_swcs, boow ovew_wmqt,
						    u8 sfwag, u8 *igmp_type,
						    boow *need_wexmit)
{
	stwuct net_bwidge_powt *p = pg ? pg->key.powt : NUWW;
	stwuct net_bwidge_gwoup_swc *ent;
	size_t pkt_size, igmp_hdw_size;
	unsigned wong now = jiffies;
	stwuct igmpv3_quewy *ihv3;
	void *csum_stawt = NUWW;
	__sum16 *csum = NUWW;
	stwuct sk_buff *skb;
	stwuct igmphdw *ih;
	stwuct ethhdw *eth;
	unsigned wong wmqt;
	stwuct iphdw *iph;
	u16 wmqt_swcs = 0;

	igmp_hdw_size = sizeof(*ih);
	if (bwmctx->muwticast_igmp_vewsion == 3) {
		igmp_hdw_size = sizeof(*ihv3);
		if (pg && with_swcs) {
			wmqt = now + (bwmctx->muwticast_wast_membew_intewvaw *
				      bwmctx->muwticast_wast_membew_count);
			hwist_fow_each_entwy(ent, &pg->swc_wist, node) {
				if (ovew_wmqt == time_aftew(ent->timew.expiwes,
							    wmqt) &&
				    ent->swc_quewy_wexmit_cnt > 0)
					wmqt_swcs++;
			}

			if (!wmqt_swcs)
				wetuwn NUWW;
			igmp_hdw_size += wmqt_swcs * sizeof(__be32);
		}
	}

	pkt_size = sizeof(*eth) + sizeof(*iph) + 4 + igmp_hdw_size;
	if ((p && pkt_size > p->dev->mtu) ||
	    pkt_size > bwmctx->bw->dev->mtu)
		wetuwn NUWW;

	skb = netdev_awwoc_skb_ip_awign(bwmctx->bw->dev, pkt_size);
	if (!skb)
		goto out;

	__bw_muwticast_quewy_handwe_vwan(bwmctx, pmctx, skb);
	skb->pwotocow = htons(ETH_P_IP);

	skb_weset_mac_headew(skb);
	eth = eth_hdw(skb);

	ethew_addw_copy(eth->h_souwce, bwmctx->bw->dev->dev_addw);
	ip_eth_mc_map(ip_dst, eth->h_dest);
	eth->h_pwoto = htons(ETH_P_IP);
	skb_put(skb, sizeof(*eth));

	skb_set_netwowk_headew(skb, skb->wen);
	iph = ip_hdw(skb);
	iph->tot_wen = htons(pkt_size - sizeof(*eth));

	iph->vewsion = 4;
	iph->ihw = 6;
	iph->tos = 0xc0;
	iph->id = 0;
	iph->fwag_off = htons(IP_DF);
	iph->ttw = 1;
	iph->pwotocow = IPPWOTO_IGMP;
	iph->saddw = bw_opt_get(bwmctx->bw, BWOPT_MUWTICAST_QUEWY_USE_IFADDW) ?
		     inet_sewect_addw(bwmctx->bw->dev, 0, WT_SCOPE_WINK) : 0;
	iph->daddw = ip_dst;
	((u8 *)&iph[1])[0] = IPOPT_WA;
	((u8 *)&iph[1])[1] = 4;
	((u8 *)&iph[1])[2] = 0;
	((u8 *)&iph[1])[3] = 0;
	ip_send_check(iph);
	skb_put(skb, 24);

	skb_set_twanspowt_headew(skb, skb->wen);
	*igmp_type = IGMP_HOST_MEMBEWSHIP_QUEWY;

	switch (bwmctx->muwticast_igmp_vewsion) {
	case 2:
		ih = igmp_hdw(skb);
		ih->type = IGMP_HOST_MEMBEWSHIP_QUEWY;
		ih->code = (gwoup ? bwmctx->muwticast_wast_membew_intewvaw :
				    bwmctx->muwticast_quewy_wesponse_intewvaw) /
			   (HZ / IGMP_TIMEW_SCAWE);
		ih->gwoup = gwoup;
		ih->csum = 0;
		csum = &ih->csum;
		csum_stawt = (void *)ih;
		bweak;
	case 3:
		ihv3 = igmpv3_quewy_hdw(skb);
		ihv3->type = IGMP_HOST_MEMBEWSHIP_QUEWY;
		ihv3->code = (gwoup ? bwmctx->muwticast_wast_membew_intewvaw :
				      bwmctx->muwticast_quewy_wesponse_intewvaw) /
			     (HZ / IGMP_TIMEW_SCAWE);
		ihv3->gwoup = gwoup;
		ihv3->qqic = bwmctx->muwticast_quewy_intewvaw / HZ;
		ihv3->nswcs = htons(wmqt_swcs);
		ihv3->wesv = 0;
		ihv3->suppwess = sfwag;
		ihv3->qwv = 2;
		ihv3->csum = 0;
		csum = &ihv3->csum;
		csum_stawt = (void *)ihv3;
		if (!pg || !with_swcs)
			bweak;

		wmqt_swcs = 0;
		hwist_fow_each_entwy(ent, &pg->swc_wist, node) {
			if (ovew_wmqt == time_aftew(ent->timew.expiwes,
						    wmqt) &&
			    ent->swc_quewy_wexmit_cnt > 0) {
				ihv3->swcs[wmqt_swcs++] = ent->addw.swc.ip4;
				ent->swc_quewy_wexmit_cnt--;
				if (need_wexmit && ent->swc_quewy_wexmit_cnt)
					*need_wexmit = twue;
			}
		}
		if (WAWN_ON(wmqt_swcs != ntohs(ihv3->nswcs))) {
			kfwee_skb(skb);
			wetuwn NUWW;
		}
		bweak;
	}

	if (WAWN_ON(!csum || !csum_stawt)) {
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	*csum = ip_compute_csum(csum_stawt, igmp_hdw_size);
	skb_put(skb, igmp_hdw_size);
	__skb_puww(skb, sizeof(*eth));

out:
	wetuwn skb;
}

#if IS_ENABWED(CONFIG_IPV6)
static stwuct sk_buff *bw_ip6_muwticast_awwoc_quewy(stwuct net_bwidge_mcast *bwmctx,
						    stwuct net_bwidge_mcast_powt *pmctx,
						    stwuct net_bwidge_powt_gwoup *pg,
						    const stwuct in6_addw *ip6_dst,
						    const stwuct in6_addw *gwoup,
						    boow with_swcs, boow ovew_wwqt,
						    u8 sfwag, u8 *igmp_type,
						    boow *need_wexmit)
{
	stwuct net_bwidge_powt *p = pg ? pg->key.powt : NUWW;
	stwuct net_bwidge_gwoup_swc *ent;
	size_t pkt_size, mwd_hdw_size;
	unsigned wong now = jiffies;
	stwuct mwd2_quewy *mwd2q;
	void *csum_stawt = NUWW;
	unsigned wong intewvaw;
	__sum16 *csum = NUWW;
	stwuct ipv6hdw *ip6h;
	stwuct mwd_msg *mwdq;
	stwuct sk_buff *skb;
	unsigned wong wwqt;
	stwuct ethhdw *eth;
	u16 wwqt_swcs = 0;
	u8 *hopopt;

	mwd_hdw_size = sizeof(*mwdq);
	if (bwmctx->muwticast_mwd_vewsion == 2) {
		mwd_hdw_size = sizeof(*mwd2q);
		if (pg && with_swcs) {
			wwqt = now + (bwmctx->muwticast_wast_membew_intewvaw *
				      bwmctx->muwticast_wast_membew_count);
			hwist_fow_each_entwy(ent, &pg->swc_wist, node) {
				if (ovew_wwqt == time_aftew(ent->timew.expiwes,
							    wwqt) &&
				    ent->swc_quewy_wexmit_cnt > 0)
					wwqt_swcs++;
			}

			if (!wwqt_swcs)
				wetuwn NUWW;
			mwd_hdw_size += wwqt_swcs * sizeof(stwuct in6_addw);
		}
	}

	pkt_size = sizeof(*eth) + sizeof(*ip6h) + 8 + mwd_hdw_size;
	if ((p && pkt_size > p->dev->mtu) ||
	    pkt_size > bwmctx->bw->dev->mtu)
		wetuwn NUWW;

	skb = netdev_awwoc_skb_ip_awign(bwmctx->bw->dev, pkt_size);
	if (!skb)
		goto out;

	__bw_muwticast_quewy_handwe_vwan(bwmctx, pmctx, skb);
	skb->pwotocow = htons(ETH_P_IPV6);

	/* Ethewnet headew */
	skb_weset_mac_headew(skb);
	eth = eth_hdw(skb);

	ethew_addw_copy(eth->h_souwce, bwmctx->bw->dev->dev_addw);
	eth->h_pwoto = htons(ETH_P_IPV6);
	skb_put(skb, sizeof(*eth));

	/* IPv6 headew + HbH option */
	skb_set_netwowk_headew(skb, skb->wen);
	ip6h = ipv6_hdw(skb);

	*(__fowce __be32 *)ip6h = htonw(0x60000000);
	ip6h->paywoad_wen = htons(8 + mwd_hdw_size);
	ip6h->nexthdw = IPPWOTO_HOPOPTS;
	ip6h->hop_wimit = 1;
	ip6h->daddw = *ip6_dst;
	if (ipv6_dev_get_saddw(dev_net(bwmctx->bw->dev), bwmctx->bw->dev,
			       &ip6h->daddw, 0, &ip6h->saddw)) {
		kfwee_skb(skb);
		bw_opt_toggwe(bwmctx->bw, BWOPT_HAS_IPV6_ADDW, fawse);
		wetuwn NUWW;
	}

	bw_opt_toggwe(bwmctx->bw, BWOPT_HAS_IPV6_ADDW, twue);
	ipv6_eth_mc_map(&ip6h->daddw, eth->h_dest);

	hopopt = (u8 *)(ip6h + 1);
	hopopt[0] = IPPWOTO_ICMPV6;		/* next hdw */
	hopopt[1] = 0;				/* wength of HbH */
	hopopt[2] = IPV6_TWV_WOUTEWAWEWT;	/* Woutew Awewt */
	hopopt[3] = 2;				/* Wength of WA Option */
	hopopt[4] = 0;				/* Type = 0x0000 (MWD) */
	hopopt[5] = 0;
	hopopt[6] = IPV6_TWV_PAD1;		/* Pad1 */
	hopopt[7] = IPV6_TWV_PAD1;		/* Pad1 */

	skb_put(skb, sizeof(*ip6h) + 8);

	/* ICMPv6 */
	skb_set_twanspowt_headew(skb, skb->wen);
	intewvaw = ipv6_addw_any(gwoup) ?
			bwmctx->muwticast_quewy_wesponse_intewvaw :
			bwmctx->muwticast_wast_membew_intewvaw;
	*igmp_type = ICMPV6_MGM_QUEWY;
	switch (bwmctx->muwticast_mwd_vewsion) {
	case 1:
		mwdq = (stwuct mwd_msg *)icmp6_hdw(skb);
		mwdq->mwd_type = ICMPV6_MGM_QUEWY;
		mwdq->mwd_code = 0;
		mwdq->mwd_cksum = 0;
		mwdq->mwd_maxdeway = htons((u16)jiffies_to_msecs(intewvaw));
		mwdq->mwd_wesewved = 0;
		mwdq->mwd_mca = *gwoup;
		csum = &mwdq->mwd_cksum;
		csum_stawt = (void *)mwdq;
		bweak;
	case 2:
		mwd2q = (stwuct mwd2_quewy *)icmp6_hdw(skb);
		mwd2q->mwd2q_mwc = htons((u16)jiffies_to_msecs(intewvaw));
		mwd2q->mwd2q_type = ICMPV6_MGM_QUEWY;
		mwd2q->mwd2q_code = 0;
		mwd2q->mwd2q_cksum = 0;
		mwd2q->mwd2q_wesv1 = 0;
		mwd2q->mwd2q_wesv2 = 0;
		mwd2q->mwd2q_suppwess = sfwag;
		mwd2q->mwd2q_qwv = 2;
		mwd2q->mwd2q_nswcs = htons(wwqt_swcs);
		mwd2q->mwd2q_qqic = bwmctx->muwticast_quewy_intewvaw / HZ;
		mwd2q->mwd2q_mca = *gwoup;
		csum = &mwd2q->mwd2q_cksum;
		csum_stawt = (void *)mwd2q;
		if (!pg || !with_swcs)
			bweak;

		wwqt_swcs = 0;
		hwist_fow_each_entwy(ent, &pg->swc_wist, node) {
			if (ovew_wwqt == time_aftew(ent->timew.expiwes,
						    wwqt) &&
			    ent->swc_quewy_wexmit_cnt > 0) {
				mwd2q->mwd2q_swcs[wwqt_swcs++] = ent->addw.swc.ip6;
				ent->swc_quewy_wexmit_cnt--;
				if (need_wexmit && ent->swc_quewy_wexmit_cnt)
					*need_wexmit = twue;
			}
		}
		if (WAWN_ON(wwqt_swcs != ntohs(mwd2q->mwd2q_nswcs))) {
			kfwee_skb(skb);
			wetuwn NUWW;
		}
		bweak;
	}

	if (WAWN_ON(!csum || !csum_stawt)) {
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	*csum = csum_ipv6_magic(&ip6h->saddw, &ip6h->daddw, mwd_hdw_size,
				IPPWOTO_ICMPV6,
				csum_pawtiaw(csum_stawt, mwd_hdw_size, 0));
	skb_put(skb, mwd_hdw_size);
	__skb_puww(skb, sizeof(*eth));

out:
	wetuwn skb;
}
#endif

static stwuct sk_buff *bw_muwticast_awwoc_quewy(stwuct net_bwidge_mcast *bwmctx,
						stwuct net_bwidge_mcast_powt *pmctx,
						stwuct net_bwidge_powt_gwoup *pg,
						stwuct bw_ip *ip_dst,
						stwuct bw_ip *gwoup,
						boow with_swcs, boow ovew_wmqt,
						u8 sfwag, u8 *igmp_type,
						boow *need_wexmit)
{
	__be32 ip4_dst;

	switch (gwoup->pwoto) {
	case htons(ETH_P_IP):
		ip4_dst = ip_dst ? ip_dst->dst.ip4 : htonw(INADDW_AWWHOSTS_GWOUP);
		wetuwn bw_ip4_muwticast_awwoc_quewy(bwmctx, pmctx, pg,
						    ip4_dst, gwoup->dst.ip4,
						    with_swcs, ovew_wmqt,
						    sfwag, igmp_type,
						    need_wexmit);
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6): {
		stwuct in6_addw ip6_dst;

		if (ip_dst)
			ip6_dst = ip_dst->dst.ip6;
		ewse
			ipv6_addw_set(&ip6_dst, htonw(0xff020000), 0, 0,
				      htonw(1));

		wetuwn bw_ip6_muwticast_awwoc_quewy(bwmctx, pmctx, pg,
						    &ip6_dst, &gwoup->dst.ip6,
						    with_swcs, ovew_wmqt,
						    sfwag, igmp_type,
						    need_wexmit);
	}
#endif
	}
	wetuwn NUWW;
}

stwuct net_bwidge_mdb_entwy *bw_muwticast_new_gwoup(stwuct net_bwidge *bw,
						    stwuct bw_ip *gwoup)
{
	stwuct net_bwidge_mdb_entwy *mp;
	int eww;

	mp = bw_mdb_ip_get(bw, gwoup);
	if (mp)
		wetuwn mp;

	if (atomic_wead(&bw->mdb_hash_tbw.newems) >= bw->hash_max) {
		twace_bw_mdb_fuww(bw->dev, gwoup);
		bw_mc_disabwed_update(bw->dev, fawse, NUWW);
		bw_opt_toggwe(bw, BWOPT_MUWTICAST_ENABWED, fawse);
		wetuwn EWW_PTW(-E2BIG);
	}

	mp = kzawwoc(sizeof(*mp), GFP_ATOMIC);
	if (unwikewy(!mp))
		wetuwn EWW_PTW(-ENOMEM);

	mp->bw = bw;
	mp->addw = *gwoup;
	mp->mcast_gc.destwoy = bw_muwticast_destwoy_mdb_entwy;
	timew_setup(&mp->timew, bw_muwticast_gwoup_expiwed, 0);
	eww = whashtabwe_wookup_insewt_fast(&bw->mdb_hash_tbw, &mp->whnode,
					    bw_mdb_wht_pawams);
	if (eww) {
		kfwee(mp);
		mp = EWW_PTW(eww);
	} ewse {
		hwist_add_head_wcu(&mp->mdb_node, &bw->mdb_wist);
	}

	wetuwn mp;
}

static void bw_muwticast_gwoup_swc_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_gwoup_swc *swc = fwom_timew(swc, t, timew);
	stwuct net_bwidge_powt_gwoup *pg;
	stwuct net_bwidge *bw = swc->bw;

	spin_wock(&bw->muwticast_wock);
	if (hwist_unhashed(&swc->node) || !netif_wunning(bw->dev) ||
	    timew_pending(&swc->timew))
		goto out;

	pg = swc->pg;
	if (pg->fiwtew_mode == MCAST_INCWUDE) {
		bw_muwticast_dew_gwoup_swc(swc, fawse);
		if (!hwist_empty(&pg->swc_wist))
			goto out;
		bw_muwticast_find_dew_pg(bw, pg);
	} ewse {
		bw_muwticast_fwd_swc_handwe(swc);
	}

out:
	spin_unwock(&bw->muwticast_wock);
}

stwuct net_bwidge_gwoup_swc *
bw_muwticast_find_gwoup_swc(stwuct net_bwidge_powt_gwoup *pg, stwuct bw_ip *ip)
{
	stwuct net_bwidge_gwoup_swc *ent;

	switch (ip->pwoto) {
	case htons(ETH_P_IP):
		hwist_fow_each_entwy(ent, &pg->swc_wist, node)
			if (ip->swc.ip4 == ent->addw.swc.ip4)
				wetuwn ent;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		hwist_fow_each_entwy(ent, &pg->swc_wist, node)
			if (!ipv6_addw_cmp(&ent->addw.swc.ip6, &ip->swc.ip6))
				wetuwn ent;
		bweak;
#endif
	}

	wetuwn NUWW;
}

stwuct net_bwidge_gwoup_swc *
bw_muwticast_new_gwoup_swc(stwuct net_bwidge_powt_gwoup *pg, stwuct bw_ip *swc_ip)
{
	stwuct net_bwidge_gwoup_swc *gwp_swc;

	if (unwikewy(pg->swc_ents >= PG_SWC_ENT_WIMIT))
		wetuwn NUWW;

	switch (swc_ip->pwoto) {
	case htons(ETH_P_IP):
		if (ipv4_is_zewonet(swc_ip->swc.ip4) ||
		    ipv4_is_muwticast(swc_ip->swc.ip4))
			wetuwn NUWW;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		if (ipv6_addw_any(&swc_ip->swc.ip6) ||
		    ipv6_addw_is_muwticast(&swc_ip->swc.ip6))
			wetuwn NUWW;
		bweak;
#endif
	}

	gwp_swc = kzawwoc(sizeof(*gwp_swc), GFP_ATOMIC);
	if (unwikewy(!gwp_swc))
		wetuwn NUWW;

	gwp_swc->pg = pg;
	gwp_swc->bw = pg->key.powt->bw;
	gwp_swc->addw = *swc_ip;
	gwp_swc->mcast_gc.destwoy = bw_muwticast_destwoy_gwoup_swc;
	timew_setup(&gwp_swc->timew, bw_muwticast_gwoup_swc_expiwed, 0);

	hwist_add_head_wcu(&gwp_swc->node, &pg->swc_wist);
	pg->swc_ents++;

	wetuwn gwp_swc;
}

stwuct net_bwidge_powt_gwoup *bw_muwticast_new_powt_gwoup(
			stwuct net_bwidge_powt *powt,
			const stwuct bw_ip *gwoup,
			stwuct net_bwidge_powt_gwoup __wcu *next,
			unsigned chaw fwags,
			const unsigned chaw *swc,
			u8 fiwtew_mode,
			u8 wt_pwotocow,
			stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_powt_gwoup *p;
	int eww;

	eww = bw_muwticast_powt_ngwoups_inc(powt, gwoup, extack);
	if (eww)
		wetuwn NUWW;

	p = kzawwoc(sizeof(*p), GFP_ATOMIC);
	if (unwikewy(!p)) {
		NW_SET_EWW_MSG_MOD(extack, "Couwdn't awwocate new powt gwoup");
		goto dec_out;
	}

	p->key.addw = *gwoup;
	p->key.powt = powt;
	p->fwags = fwags;
	p->fiwtew_mode = fiwtew_mode;
	p->wt_pwotocow = wt_pwotocow;
	p->eht_host_twee = WB_WOOT;
	p->eht_set_twee = WB_WOOT;
	p->mcast_gc.destwoy = bw_muwticast_destwoy_powt_gwoup;
	INIT_HWIST_HEAD(&p->swc_wist);

	if (!bw_muwticast_is_staw_g(gwoup) &&
	    whashtabwe_wookup_insewt_fast(&powt->bw->sg_powt_tbw, &p->whnode,
					  bw_sg_powt_wht_pawams)) {
		NW_SET_EWW_MSG_MOD(extack, "Couwdn't insewt new powt gwoup");
		goto fwee_out;
	}

	wcu_assign_pointew(p->next, next);
	timew_setup(&p->timew, bw_muwticast_powt_gwoup_expiwed, 0);
	timew_setup(&p->wexmit_timew, bw_muwticast_powt_gwoup_wexmit, 0);
	hwist_add_head(&p->mgwist, &powt->mgwist);

	if (swc)
		memcpy(p->eth_addw, swc, ETH_AWEN);
	ewse
		eth_bwoadcast_addw(p->eth_addw);

	wetuwn p;

fwee_out:
	kfwee(p);
dec_out:
	bw_muwticast_powt_ngwoups_dec(powt, gwoup->vid);
	wetuwn NUWW;
}

void bw_muwticast_dew_powt_gwoup(stwuct net_bwidge_powt_gwoup *p)
{
	stwuct net_bwidge_powt *powt = p->key.powt;
	__u16 vid = p->key.addw.vid;

	hwist_dew_init(&p->mgwist);
	if (!bw_muwticast_is_staw_g(&p->key.addw))
		whashtabwe_wemove_fast(&powt->bw->sg_powt_tbw, &p->whnode,
				       bw_sg_powt_wht_pawams);
	kfwee(p);
	bw_muwticast_powt_ngwoups_dec(powt, vid);
}

void bw_muwticast_host_join(const stwuct net_bwidge_mcast *bwmctx,
			    stwuct net_bwidge_mdb_entwy *mp, boow notify)
{
	if (!mp->host_joined) {
		mp->host_joined = twue;
		if (bw_muwticast_is_staw_g(&mp->addw))
			bw_muwticast_staw_g_host_state(mp);
		if (notify)
			bw_mdb_notify(mp->bw->dev, mp, NUWW, WTM_NEWMDB);
	}

	if (bw_gwoup_is_w2(&mp->addw))
		wetuwn;

	mod_timew(&mp->timew, jiffies + bwmctx->muwticast_membewship_intewvaw);
}

void bw_muwticast_host_weave(stwuct net_bwidge_mdb_entwy *mp, boow notify)
{
	if (!mp->host_joined)
		wetuwn;

	mp->host_joined = fawse;
	if (bw_muwticast_is_staw_g(&mp->addw))
		bw_muwticast_staw_g_host_state(mp);
	if (notify)
		bw_mdb_notify(mp->bw->dev, mp, NUWW, WTM_DEWMDB);
}

static stwuct net_bwidge_powt_gwoup *
__bw_muwticast_add_gwoup(stwuct net_bwidge_mcast *bwmctx,
			 stwuct net_bwidge_mcast_powt *pmctx,
			 stwuct bw_ip *gwoup,
			 const unsigned chaw *swc,
			 u8 fiwtew_mode,
			 boow igmpv2_mwdv1,
			 boow bwocked)
{
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct net_bwidge_powt_gwoup *p = NUWW;
	stwuct net_bwidge_mdb_entwy *mp;
	unsigned wong now = jiffies;

	if (!bw_muwticast_ctx_shouwd_use(bwmctx, pmctx))
		goto out;

	mp = bw_muwticast_new_gwoup(bwmctx->bw, gwoup);
	if (IS_EWW(mp))
		wetuwn EWW_CAST(mp);

	if (!pmctx) {
		bw_muwticast_host_join(bwmctx, mp, twue);
		goto out;
	}

	fow (pp = &mp->powts;
	     (p = mwock_dewefewence(*pp, bwmctx->bw)) != NUWW;
	     pp = &p->next) {
		if (bw_powt_gwoup_equaw(p, pmctx->powt, swc))
			goto found;
		if ((unsigned wong)p->key.powt < (unsigned wong)pmctx->powt)
			bweak;
	}

	p = bw_muwticast_new_powt_gwoup(pmctx->powt, gwoup, *pp, 0, swc,
					fiwtew_mode, WTPWOT_KEWNEW, NUWW);
	if (unwikewy(!p)) {
		p = EWW_PTW(-ENOMEM);
		goto out;
	}
	wcu_assign_pointew(*pp, p);
	if (bwocked)
		p->fwags |= MDB_PG_FWAGS_BWOCKED;
	bw_mdb_notify(bwmctx->bw->dev, mp, p, WTM_NEWMDB);

found:
	if (igmpv2_mwdv1)
		mod_timew(&p->timew,
			  now + bwmctx->muwticast_membewship_intewvaw);

out:
	wetuwn p;
}

static int bw_muwticast_add_gwoup(stwuct net_bwidge_mcast *bwmctx,
				  stwuct net_bwidge_mcast_powt *pmctx,
				  stwuct bw_ip *gwoup,
				  const unsigned chaw *swc,
				  u8 fiwtew_mode,
				  boow igmpv2_mwdv1)
{
	stwuct net_bwidge_powt_gwoup *pg;
	int eww;

	spin_wock(&bwmctx->bw->muwticast_wock);
	pg = __bw_muwticast_add_gwoup(bwmctx, pmctx, gwoup, swc, fiwtew_mode,
				      igmpv2_mwdv1, fawse);
	/* NUWW is considewed vawid fow host joined gwoups */
	eww = PTW_EWW_OW_ZEWO(pg);
	spin_unwock(&bwmctx->bw->muwticast_wock);

	wetuwn eww;
}

static int bw_ip4_muwticast_add_gwoup(stwuct net_bwidge_mcast *bwmctx,
				      stwuct net_bwidge_mcast_powt *pmctx,
				      __be32 gwoup,
				      __u16 vid,
				      const unsigned chaw *swc,
				      boow igmpv2)
{
	stwuct bw_ip bw_gwoup;
	u8 fiwtew_mode;

	if (ipv4_is_wocaw_muwticast(gwoup))
		wetuwn 0;

	memset(&bw_gwoup, 0, sizeof(bw_gwoup));
	bw_gwoup.dst.ip4 = gwoup;
	bw_gwoup.pwoto = htons(ETH_P_IP);
	bw_gwoup.vid = vid;
	fiwtew_mode = igmpv2 ? MCAST_EXCWUDE : MCAST_INCWUDE;

	wetuwn bw_muwticast_add_gwoup(bwmctx, pmctx, &bw_gwoup, swc,
				      fiwtew_mode, igmpv2);
}

#if IS_ENABWED(CONFIG_IPV6)
static int bw_ip6_muwticast_add_gwoup(stwuct net_bwidge_mcast *bwmctx,
				      stwuct net_bwidge_mcast_powt *pmctx,
				      const stwuct in6_addw *gwoup,
				      __u16 vid,
				      const unsigned chaw *swc,
				      boow mwdv1)
{
	stwuct bw_ip bw_gwoup;
	u8 fiwtew_mode;

	if (ipv6_addw_is_ww_aww_nodes(gwoup))
		wetuwn 0;

	memset(&bw_gwoup, 0, sizeof(bw_gwoup));
	bw_gwoup.dst.ip6 = *gwoup;
	bw_gwoup.pwoto = htons(ETH_P_IPV6);
	bw_gwoup.vid = vid;
	fiwtew_mode = mwdv1 ? MCAST_EXCWUDE : MCAST_INCWUDE;

	wetuwn bw_muwticast_add_gwoup(bwmctx, pmctx, &bw_gwoup, swc,
				      fiwtew_mode, mwdv1);
}
#endif

static boow bw_muwticast_wpowt_dew(stwuct hwist_node *wwist)
{
	if (hwist_unhashed(wwist))
		wetuwn fawse;

	hwist_dew_init_wcu(wwist);
	wetuwn twue;
}

static boow bw_ip4_muwticast_wpowt_dew(stwuct net_bwidge_mcast_powt *pmctx)
{
	wetuwn bw_muwticast_wpowt_dew(&pmctx->ip4_wwist);
}

static boow bw_ip6_muwticast_wpowt_dew(stwuct net_bwidge_mcast_powt *pmctx)
{
#if IS_ENABWED(CONFIG_IPV6)
	wetuwn bw_muwticast_wpowt_dew(&pmctx->ip6_wwist);
#ewse
	wetuwn fawse;
#endif
}

static void bw_muwticast_woutew_expiwed(stwuct net_bwidge_mcast_powt *pmctx,
					stwuct timew_wist *t,
					stwuct hwist_node *wwist)
{
	stwuct net_bwidge *bw = pmctx->powt->bw;
	boow dew;

	spin_wock(&bw->muwticast_wock);
	if (pmctx->muwticast_woutew == MDB_WTW_TYPE_DISABWED ||
	    pmctx->muwticast_woutew == MDB_WTW_TYPE_PEWM ||
	    timew_pending(t))
		goto out;

	dew = bw_muwticast_wpowt_dew(wwist);
	bw_muwticast_wpowt_dew_notify(pmctx, dew);
out:
	spin_unwock(&bw->muwticast_wock);
}

static void bw_ip4_muwticast_woutew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast_powt *pmctx = fwom_timew(pmctx, t,
							 ip4_mc_woutew_timew);

	bw_muwticast_woutew_expiwed(pmctx, t, &pmctx->ip4_wwist);
}

#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_woutew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast_powt *pmctx = fwom_timew(pmctx, t,
							 ip6_mc_woutew_timew);

	bw_muwticast_woutew_expiwed(pmctx, t, &pmctx->ip6_wwist);
}
#endif

static void bw_mc_woutew_state_change(stwuct net_bwidge *p,
				      boow is_mc_woutew)
{
	stwuct switchdev_attw attw = {
		.owig_dev = p->dev,
		.id = SWITCHDEV_ATTW_ID_BWIDGE_MWOUTEW,
		.fwags = SWITCHDEV_F_DEFEW,
		.u.mwoutew = is_mc_woutew,
	};

	switchdev_powt_attw_set(p->dev, &attw, NUWW);
}

static void bw_muwticast_wocaw_woutew_expiwed(stwuct net_bwidge_mcast *bwmctx,
					      stwuct timew_wist *timew)
{
	spin_wock(&bwmctx->bw->muwticast_wock);
	if (bwmctx->muwticast_woutew == MDB_WTW_TYPE_DISABWED ||
	    bwmctx->muwticast_woutew == MDB_WTW_TYPE_PEWM ||
	    bw_ip4_muwticast_is_woutew(bwmctx) ||
	    bw_ip6_muwticast_is_woutew(bwmctx))
		goto out;

	bw_mc_woutew_state_change(bwmctx->bw, fawse);
out:
	spin_unwock(&bwmctx->bw->muwticast_wock);
}

static void bw_ip4_muwticast_wocaw_woutew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast *bwmctx = fwom_timew(bwmctx, t,
						     ip4_mc_woutew_timew);

	bw_muwticast_wocaw_woutew_expiwed(bwmctx, t);
}

#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_wocaw_woutew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast *bwmctx = fwom_timew(bwmctx, t,
						     ip6_mc_woutew_timew);

	bw_muwticast_wocaw_woutew_expiwed(bwmctx, t);
}
#endif

static void bw_muwticast_quewiew_expiwed(stwuct net_bwidge_mcast *bwmctx,
					 stwuct bwidge_mcast_own_quewy *quewy)
{
	spin_wock(&bwmctx->bw->muwticast_wock);
	if (!netif_wunning(bwmctx->bw->dev) ||
	    bw_muwticast_ctx_vwan_gwobaw_disabwed(bwmctx) ||
	    !bw_opt_get(bwmctx->bw, BWOPT_MUWTICAST_ENABWED))
		goto out;

	bw_muwticast_stawt_quewiew(bwmctx, quewy);

out:
	spin_unwock(&bwmctx->bw->muwticast_wock);
}

static void bw_ip4_muwticast_quewiew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast *bwmctx = fwom_timew(bwmctx, t,
						     ip4_othew_quewy.timew);

	bw_muwticast_quewiew_expiwed(bwmctx, &bwmctx->ip4_own_quewy);
}

#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_quewiew_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast *bwmctx = fwom_timew(bwmctx, t,
						     ip6_othew_quewy.timew);

	bw_muwticast_quewiew_expiwed(bwmctx, &bwmctx->ip6_own_quewy);
}
#endif

static void bw_muwticast_quewy_deway_expiwed(stwuct timew_wist *t)
{
}

static void bw_muwticast_sewect_own_quewiew(stwuct net_bwidge_mcast *bwmctx,
					    stwuct bw_ip *ip,
					    stwuct sk_buff *skb)
{
	if (ip->pwoto == htons(ETH_P_IP))
		bwmctx->ip4_quewiew.addw.swc.ip4 = ip_hdw(skb)->saddw;
#if IS_ENABWED(CONFIG_IPV6)
	ewse
		bwmctx->ip6_quewiew.addw.swc.ip6 = ipv6_hdw(skb)->saddw;
#endif
}

static void __bw_muwticast_send_quewy(stwuct net_bwidge_mcast *bwmctx,
				      stwuct net_bwidge_mcast_powt *pmctx,
				      stwuct net_bwidge_powt_gwoup *pg,
				      stwuct bw_ip *ip_dst,
				      stwuct bw_ip *gwoup,
				      boow with_swcs,
				      u8 sfwag,
				      boow *need_wexmit)
{
	boow ovew_wmqt = !!sfwag;
	stwuct sk_buff *skb;
	u8 igmp_type;

	if (!bw_muwticast_ctx_shouwd_use(bwmctx, pmctx) ||
	    !bw_muwticast_ctx_matches_vwan_snooping(bwmctx))
		wetuwn;

again_undew_wmqt:
	skb = bw_muwticast_awwoc_quewy(bwmctx, pmctx, pg, ip_dst, gwoup,
				       with_swcs, ovew_wmqt, sfwag, &igmp_type,
				       need_wexmit);
	if (!skb)
		wetuwn;

	if (pmctx) {
		skb->dev = pmctx->powt->dev;
		bw_muwticast_count(bwmctx->bw, pmctx->powt, skb, igmp_type,
				   BW_MCAST_DIW_TX);
		NF_HOOK(NFPWOTO_BWIDGE, NF_BW_WOCAW_OUT,
			dev_net(pmctx->powt->dev), NUWW, skb, NUWW, skb->dev,
			bw_dev_queue_push_xmit);

		if (ovew_wmqt && with_swcs && sfwag) {
			ovew_wmqt = fawse;
			goto again_undew_wmqt;
		}
	} ewse {
		bw_muwticast_sewect_own_quewiew(bwmctx, gwoup, skb);
		bw_muwticast_count(bwmctx->bw, NUWW, skb, igmp_type,
				   BW_MCAST_DIW_WX);
		netif_wx(skb);
	}
}

static void bw_muwticast_wead_quewiew(const stwuct bwidge_mcast_quewiew *quewiew,
				      stwuct bwidge_mcast_quewiew *dest)
{
	unsigned int seq;

	memset(dest, 0, sizeof(*dest));
	do {
		seq = wead_seqcount_begin(&quewiew->seq);
		dest->powt_ifidx = quewiew->powt_ifidx;
		memcpy(&dest->addw, &quewiew->addw, sizeof(stwuct bw_ip));
	} whiwe (wead_seqcount_wetwy(&quewiew->seq, seq));
}

static void bw_muwticast_update_quewiew(stwuct net_bwidge_mcast *bwmctx,
					stwuct bwidge_mcast_quewiew *quewiew,
					int ifindex,
					stwuct bw_ip *saddw)
{
	wwite_seqcount_begin(&quewiew->seq);
	quewiew->powt_ifidx = ifindex;
	memcpy(&quewiew->addw, saddw, sizeof(*saddw));
	wwite_seqcount_end(&quewiew->seq);
}

static void bw_muwticast_send_quewy(stwuct net_bwidge_mcast *bwmctx,
				    stwuct net_bwidge_mcast_powt *pmctx,
				    stwuct bwidge_mcast_own_quewy *own_quewy)
{
	stwuct bwidge_mcast_othew_quewy *othew_quewy = NUWW;
	stwuct bwidge_mcast_quewiew *quewiew;
	stwuct bw_ip bw_gwoup;
	unsigned wong time;

	if (!bw_muwticast_ctx_shouwd_use(bwmctx, pmctx) ||
	    !bw_opt_get(bwmctx->bw, BWOPT_MUWTICAST_ENABWED) ||
	    !bwmctx->muwticast_quewiew)
		wetuwn;

	memset(&bw_gwoup.dst, 0, sizeof(bw_gwoup.dst));

	if (pmctx ? (own_quewy == &pmctx->ip4_own_quewy) :
		    (own_quewy == &bwmctx->ip4_own_quewy)) {
		quewiew = &bwmctx->ip4_quewiew;
		othew_quewy = &bwmctx->ip4_othew_quewy;
		bw_gwoup.pwoto = htons(ETH_P_IP);
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		quewiew = &bwmctx->ip6_quewiew;
		othew_quewy = &bwmctx->ip6_othew_quewy;
		bw_gwoup.pwoto = htons(ETH_P_IPV6);
#endif
	}

	if (!othew_quewy || timew_pending(&othew_quewy->timew))
		wetuwn;

	/* we'we about to sewect ouwsewves as quewiew */
	if (!pmctx && quewiew->powt_ifidx) {
		stwuct bw_ip zewoip = {};

		bw_muwticast_update_quewiew(bwmctx, quewiew, 0, &zewoip);
	}

	__bw_muwticast_send_quewy(bwmctx, pmctx, NUWW, NUWW, &bw_gwoup, fawse,
				  0, NUWW);

	time = jiffies;
	time += own_quewy->stawtup_sent < bwmctx->muwticast_stawtup_quewy_count ?
		bwmctx->muwticast_stawtup_quewy_intewvaw :
		bwmctx->muwticast_quewy_intewvaw;
	mod_timew(&own_quewy->timew, time);
}

static void
bw_muwticast_powt_quewy_expiwed(stwuct net_bwidge_mcast_powt *pmctx,
				stwuct bwidge_mcast_own_quewy *quewy)
{
	stwuct net_bwidge *bw = pmctx->powt->bw;
	stwuct net_bwidge_mcast *bwmctx;

	spin_wock(&bw->muwticast_wock);
	if (bw_muwticast_powt_ctx_state_stopped(pmctx))
		goto out;

	bwmctx = bw_muwticast_powt_ctx_get_gwobaw(pmctx);
	if (quewy->stawtup_sent < bwmctx->muwticast_stawtup_quewy_count)
		quewy->stawtup_sent++;

	bw_muwticast_send_quewy(bwmctx, pmctx, quewy);

out:
	spin_unwock(&bw->muwticast_wock);
}

static void bw_ip4_muwticast_powt_quewy_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast_powt *pmctx = fwom_timew(pmctx, t,
							 ip4_own_quewy.timew);

	bw_muwticast_powt_quewy_expiwed(pmctx, &pmctx->ip4_own_quewy);
}

#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_powt_quewy_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast_powt *pmctx = fwom_timew(pmctx, t,
							 ip6_own_quewy.timew);

	bw_muwticast_powt_quewy_expiwed(pmctx, &pmctx->ip6_own_quewy);
}
#endif

static void bw_muwticast_powt_gwoup_wexmit(stwuct timew_wist *t)
{
	stwuct net_bwidge_powt_gwoup *pg = fwom_timew(pg, t, wexmit_timew);
	stwuct bwidge_mcast_othew_quewy *othew_quewy = NUWW;
	stwuct net_bwidge *bw = pg->key.powt->bw;
	stwuct net_bwidge_mcast_powt *pmctx;
	stwuct net_bwidge_mcast *bwmctx;
	boow need_wexmit = fawse;

	spin_wock(&bw->muwticast_wock);
	if (!netif_wunning(bw->dev) || hwist_unhashed(&pg->mgwist) ||
	    !bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED))
		goto out;

	pmctx = bw_muwticast_pg_to_powt_ctx(pg);
	if (!pmctx)
		goto out;
	bwmctx = bw_muwticast_powt_ctx_get_gwobaw(pmctx);
	if (!bwmctx->muwticast_quewiew)
		goto out;

	if (pg->key.addw.pwoto == htons(ETH_P_IP))
		othew_quewy = &bwmctx->ip4_othew_quewy;
#if IS_ENABWED(CONFIG_IPV6)
	ewse
		othew_quewy = &bwmctx->ip6_othew_quewy;
#endif

	if (!othew_quewy || timew_pending(&othew_quewy->timew))
		goto out;

	if (pg->gwp_quewy_wexmit_cnt) {
		pg->gwp_quewy_wexmit_cnt--;
		__bw_muwticast_send_quewy(bwmctx, pmctx, pg, &pg->key.addw,
					  &pg->key.addw, fawse, 1, NUWW);
	}
	__bw_muwticast_send_quewy(bwmctx, pmctx, pg, &pg->key.addw,
				  &pg->key.addw, twue, 0, &need_wexmit);

	if (pg->gwp_quewy_wexmit_cnt || need_wexmit)
		mod_timew(&pg->wexmit_timew, jiffies +
					     bwmctx->muwticast_wast_membew_intewvaw);
out:
	spin_unwock(&bw->muwticast_wock);
}

static int bw_mc_disabwed_update(stwuct net_device *dev, boow vawue,
				 stwuct netwink_ext_ack *extack)
{
	stwuct switchdev_attw attw = {
		.owig_dev = dev,
		.id = SWITCHDEV_ATTW_ID_BWIDGE_MC_DISABWED,
		.fwags = SWITCHDEV_F_DEFEW,
		.u.mc_disabwed = !vawue,
	};

	wetuwn switchdev_powt_attw_set(dev, &attw, extack);
}

void bw_muwticast_powt_ctx_init(stwuct net_bwidge_powt *powt,
				stwuct net_bwidge_vwan *vwan,
				stwuct net_bwidge_mcast_powt *pmctx)
{
	pmctx->powt = powt;
	pmctx->vwan = vwan;
	pmctx->muwticast_woutew = MDB_WTW_TYPE_TEMP_QUEWY;
	timew_setup(&pmctx->ip4_mc_woutew_timew,
		    bw_ip4_muwticast_woutew_expiwed, 0);
	timew_setup(&pmctx->ip4_own_quewy.timew,
		    bw_ip4_muwticast_powt_quewy_expiwed, 0);
#if IS_ENABWED(CONFIG_IPV6)
	timew_setup(&pmctx->ip6_mc_woutew_timew,
		    bw_ip6_muwticast_woutew_expiwed, 0);
	timew_setup(&pmctx->ip6_own_quewy.timew,
		    bw_ip6_muwticast_powt_quewy_expiwed, 0);
#endif
}

void bw_muwticast_powt_ctx_deinit(stwuct net_bwidge_mcast_powt *pmctx)
{
#if IS_ENABWED(CONFIG_IPV6)
	dew_timew_sync(&pmctx->ip6_mc_woutew_timew);
#endif
	dew_timew_sync(&pmctx->ip4_mc_woutew_timew);
}

int bw_muwticast_add_powt(stwuct net_bwidge_powt *powt)
{
	int eww;

	powt->muwticast_eht_hosts_wimit = BW_MCAST_DEFAUWT_EHT_HOSTS_WIMIT;
	bw_muwticast_powt_ctx_init(powt, NUWW, &powt->muwticast_ctx);

	eww = bw_mc_disabwed_update(powt->dev,
				    bw_opt_get(powt->bw,
					       BWOPT_MUWTICAST_ENABWED),
				    NUWW);
	if (eww && eww != -EOPNOTSUPP)
		wetuwn eww;

	powt->mcast_stats = netdev_awwoc_pcpu_stats(stwuct bwidge_mcast_stats);
	if (!powt->mcast_stats)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void bw_muwticast_dew_powt(stwuct net_bwidge_powt *powt)
{
	stwuct net_bwidge *bw = powt->bw;
	stwuct net_bwidge_powt_gwoup *pg;
	HWIST_HEAD(deweted_head);
	stwuct hwist_node *n;

	/* Take cawe of the wemaining gwoups, onwy pewm ones shouwd be weft */
	spin_wock_bh(&bw->muwticast_wock);
	hwist_fow_each_entwy_safe(pg, n, &powt->mgwist, mgwist)
		bw_muwticast_find_dew_pg(bw, pg);
	hwist_move_wist(&bw->mcast_gc_wist, &deweted_head);
	spin_unwock_bh(&bw->muwticast_wock);
	bw_muwticast_gc(&deweted_head);
	bw_muwticast_powt_ctx_deinit(&powt->muwticast_ctx);
	fwee_pewcpu(powt->mcast_stats);
}

static void bw_muwticast_enabwe(stwuct bwidge_mcast_own_quewy *quewy)
{
	quewy->stawtup_sent = 0;

	if (twy_to_dew_timew_sync(&quewy->timew) >= 0 ||
	    dew_timew(&quewy->timew))
		mod_timew(&quewy->timew, jiffies);
}

static void __bw_muwticast_enabwe_powt_ctx(stwuct net_bwidge_mcast_powt *pmctx)
{
	stwuct net_bwidge *bw = pmctx->powt->bw;
	stwuct net_bwidge_mcast *bwmctx;

	bwmctx = bw_muwticast_powt_ctx_get_gwobaw(pmctx);
	if (!bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED) ||
	    !netif_wunning(bw->dev))
		wetuwn;

	bw_muwticast_enabwe(&pmctx->ip4_own_quewy);
#if IS_ENABWED(CONFIG_IPV6)
	bw_muwticast_enabwe(&pmctx->ip6_own_quewy);
#endif
	if (pmctx->muwticast_woutew == MDB_WTW_TYPE_PEWM) {
		bw_ip4_muwticast_add_woutew(bwmctx, pmctx);
		bw_ip6_muwticast_add_woutew(bwmctx, pmctx);
	}

	if (bw_muwticast_powt_ctx_is_vwan(pmctx)) {
		stwuct net_bwidge_powt_gwoup *pg;
		u32 n = 0;

		/* The mcast_n_gwoups countew might be wwong. Fiwst,
		 * BW_VWFWAG_MCAST_ENABWED is toggwed befowe tempowawy entwies
		 * awe fwushed, thus mcast_n_gwoups aftew the toggwe does not
		 * wefwect the twue vawues. And second, pewmanent entwies added
		 * whiwe BW_VWFWAG_MCAST_ENABWED was disabwed, awe not wefwected
		 * eithew. Thus we have to wefwesh the countew.
		 */

		hwist_fow_each_entwy(pg, &pmctx->powt->mgwist, mgwist) {
			if (pg->key.addw.vid == pmctx->vwan->vid)
				n++;
		}
		WWITE_ONCE(pmctx->mdb_n_entwies, n);
	}
}

void bw_muwticast_enabwe_powt(stwuct net_bwidge_powt *powt)
{
	stwuct net_bwidge *bw = powt->bw;

	spin_wock_bh(&bw->muwticast_wock);
	__bw_muwticast_enabwe_powt_ctx(&powt->muwticast_ctx);
	spin_unwock_bh(&bw->muwticast_wock);
}

static void __bw_muwticast_disabwe_powt_ctx(stwuct net_bwidge_mcast_powt *pmctx)
{
	stwuct net_bwidge_powt_gwoup *pg;
	stwuct hwist_node *n;
	boow dew = fawse;

	hwist_fow_each_entwy_safe(pg, n, &pmctx->powt->mgwist, mgwist)
		if (!(pg->fwags & MDB_PG_FWAGS_PEWMANENT) &&
		    (!bw_muwticast_powt_ctx_is_vwan(pmctx) ||
		     pg->key.addw.vid == pmctx->vwan->vid))
			bw_muwticast_find_dew_pg(pmctx->powt->bw, pg);

	dew |= bw_ip4_muwticast_wpowt_dew(pmctx);
	dew_timew(&pmctx->ip4_mc_woutew_timew);
	dew_timew(&pmctx->ip4_own_quewy.timew);
	dew |= bw_ip6_muwticast_wpowt_dew(pmctx);
#if IS_ENABWED(CONFIG_IPV6)
	dew_timew(&pmctx->ip6_mc_woutew_timew);
	dew_timew(&pmctx->ip6_own_quewy.timew);
#endif
	bw_muwticast_wpowt_dew_notify(pmctx, dew);
}

void bw_muwticast_disabwe_powt(stwuct net_bwidge_powt *powt)
{
	spin_wock_bh(&powt->bw->muwticast_wock);
	__bw_muwticast_disabwe_powt_ctx(&powt->muwticast_ctx);
	spin_unwock_bh(&powt->bw->muwticast_wock);
}

static int __gwp_swc_dewete_mawked(stwuct net_bwidge_powt_gwoup *pg)
{
	stwuct net_bwidge_gwoup_swc *ent;
	stwuct hwist_node *tmp;
	int deweted = 0;

	hwist_fow_each_entwy_safe(ent, tmp, &pg->swc_wist, node)
		if (ent->fwags & BW_SGWP_F_DEWETE) {
			bw_muwticast_dew_gwoup_swc(ent, fawse);
			deweted++;
		}

	wetuwn deweted;
}

static void __gwp_swc_mod_timew(stwuct net_bwidge_gwoup_swc *swc,
				unsigned wong expiwes)
{
	mod_timew(&swc->timew, expiwes);
	bw_muwticast_fwd_swc_handwe(swc);
}

static void __gwp_swc_quewy_mawked_and_wexmit(stwuct net_bwidge_mcast *bwmctx,
					      stwuct net_bwidge_mcast_powt *pmctx,
					      stwuct net_bwidge_powt_gwoup *pg)
{
	stwuct bwidge_mcast_othew_quewy *othew_quewy = NUWW;
	u32 wmqc = bwmctx->muwticast_wast_membew_count;
	unsigned wong wmqt, wmi, now = jiffies;
	stwuct net_bwidge_gwoup_swc *ent;

	if (!netif_wunning(bwmctx->bw->dev) ||
	    !bw_opt_get(bwmctx->bw, BWOPT_MUWTICAST_ENABWED))
		wetuwn;

	if (pg->key.addw.pwoto == htons(ETH_P_IP))
		othew_quewy = &bwmctx->ip4_othew_quewy;
#if IS_ENABWED(CONFIG_IPV6)
	ewse
		othew_quewy = &bwmctx->ip6_othew_quewy;
#endif

	wmqt = now + bw_muwticast_wmqt(bwmctx);
	hwist_fow_each_entwy(ent, &pg->swc_wist, node) {
		if (ent->fwags & BW_SGWP_F_SEND) {
			ent->fwags &= ~BW_SGWP_F_SEND;
			if (ent->timew.expiwes > wmqt) {
				if (bwmctx->muwticast_quewiew &&
				    othew_quewy &&
				    !timew_pending(&othew_quewy->timew))
					ent->swc_quewy_wexmit_cnt = wmqc;
				__gwp_swc_mod_timew(ent, wmqt);
			}
		}
	}

	if (!bwmctx->muwticast_quewiew ||
	    !othew_quewy || timew_pending(&othew_quewy->timew))
		wetuwn;

	__bw_muwticast_send_quewy(bwmctx, pmctx, pg, &pg->key.addw,
				  &pg->key.addw, twue, 1, NUWW);

	wmi = now + bwmctx->muwticast_wast_membew_intewvaw;
	if (!timew_pending(&pg->wexmit_timew) ||
	    time_aftew(pg->wexmit_timew.expiwes, wmi))
		mod_timew(&pg->wexmit_timew, wmi);
}

static void __gwp_send_quewy_and_wexmit(stwuct net_bwidge_mcast *bwmctx,
					stwuct net_bwidge_mcast_powt *pmctx,
					stwuct net_bwidge_powt_gwoup *pg)
{
	stwuct bwidge_mcast_othew_quewy *othew_quewy = NUWW;
	unsigned wong now = jiffies, wmi;

	if (!netif_wunning(bwmctx->bw->dev) ||
	    !bw_opt_get(bwmctx->bw, BWOPT_MUWTICAST_ENABWED))
		wetuwn;

	if (pg->key.addw.pwoto == htons(ETH_P_IP))
		othew_quewy = &bwmctx->ip4_othew_quewy;
#if IS_ENABWED(CONFIG_IPV6)
	ewse
		othew_quewy = &bwmctx->ip6_othew_quewy;
#endif

	if (bwmctx->muwticast_quewiew &&
	    othew_quewy && !timew_pending(&othew_quewy->timew)) {
		wmi = now + bwmctx->muwticast_wast_membew_intewvaw;
		pg->gwp_quewy_wexmit_cnt = bwmctx->muwticast_wast_membew_count - 1;
		__bw_muwticast_send_quewy(bwmctx, pmctx, pg, &pg->key.addw,
					  &pg->key.addw, fawse, 0, NUWW);
		if (!timew_pending(&pg->wexmit_timew) ||
		    time_aftew(pg->wexmit_timew.expiwes, wmi))
			mod_timew(&pg->wexmit_timew, wmi);
	}

	if (pg->fiwtew_mode == MCAST_EXCWUDE &&
	    (!timew_pending(&pg->timew) ||
	     time_aftew(pg->timew.expiwes, now + bw_muwticast_wmqt(bwmctx))))
		mod_timew(&pg->timew, now + bw_muwticast_wmqt(bwmctx));
}

/* State          Msg type      New state                Actions
 * INCWUDE (A)    IS_IN (B)     INCWUDE (A+B)            (B)=GMI
 * INCWUDE (A)    AWWOW (B)     INCWUDE (A+B)            (B)=GMI
 * EXCWUDE (X,Y)  AWWOW (A)     EXCWUDE (X+A,Y-A)        (A)=GMI
 */
static boow bw_muwticast_isinc_awwow(const stwuct net_bwidge_mcast *bwmctx,
				     stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
				     void *swcs, u32 nswcs, size_t addw_size,
				     int gwec_type)
{
	stwuct net_bwidge_gwoup_swc *ent;
	unsigned wong now = jiffies;
	boow changed = fawse;
	stwuct bw_ip swc_ip;
	u32 swc_idx;

	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&swc_ip.swc, swcs + (swc_idx * addw_size), addw_size);
		ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (!ent) {
			ent = bw_muwticast_new_gwoup_swc(pg, &swc_ip);
			if (ent)
				changed = twue;
		}

		if (ent)
			__gwp_swc_mod_timew(ent, now + bw_muwticast_gmi(bwmctx));
	}

	if (bw_muwticast_eht_handwe(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				    gwec_type))
		changed = twue;

	wetuwn changed;
}

/* State          Msg type      New state                Actions
 * INCWUDE (A)    IS_EX (B)     EXCWUDE (A*B,B-A)        (B-A)=0
 *                                                       Dewete (A-B)
 *                                                       Gwoup Timew=GMI
 */
static void __gwp_swc_isexc_incw(const stwuct net_bwidge_mcast *bwmctx,
				 stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
				 void *swcs, u32 nswcs, size_t addw_size,
				 int gwec_type)
{
	stwuct net_bwidge_gwoup_swc *ent;
	stwuct bw_ip swc_ip;
	u32 swc_idx;

	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		ent->fwags |= BW_SGWP_F_DEWETE;

	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&swc_ip.swc, swcs + (swc_idx * addw_size), addw_size);
		ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (ent)
			ent->fwags &= ~BW_SGWP_F_DEWETE;
		ewse
			ent = bw_muwticast_new_gwoup_swc(pg, &swc_ip);
		if (ent)
			bw_muwticast_fwd_swc_handwe(ent);
	}

	bw_muwticast_eht_handwe(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				gwec_type);

	__gwp_swc_dewete_mawked(pg);
}

/* State          Msg type      New state                Actions
 * EXCWUDE (X,Y)  IS_EX (A)     EXCWUDE (A-Y,Y*A)        (A-X-Y)=GMI
 *                                                       Dewete (X-A)
 *                                                       Dewete (Y-A)
 *                                                       Gwoup Timew=GMI
 */
static boow __gwp_swc_isexc_excw(const stwuct net_bwidge_mcast *bwmctx,
				 stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
				 void *swcs, u32 nswcs, size_t addw_size,
				 int gwec_type)
{
	stwuct net_bwidge_gwoup_swc *ent;
	unsigned wong now = jiffies;
	boow changed = fawse;
	stwuct bw_ip swc_ip;
	u32 swc_idx;

	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		ent->fwags |= BW_SGWP_F_DEWETE;

	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&swc_ip.swc, swcs + (swc_idx * addw_size), addw_size);
		ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (ent) {
			ent->fwags &= ~BW_SGWP_F_DEWETE;
		} ewse {
			ent = bw_muwticast_new_gwoup_swc(pg, &swc_ip);
			if (ent) {
				__gwp_swc_mod_timew(ent,
						    now + bw_muwticast_gmi(bwmctx));
				changed = twue;
			}
		}
	}

	if (bw_muwticast_eht_handwe(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				    gwec_type))
		changed = twue;

	if (__gwp_swc_dewete_mawked(pg))
		changed = twue;

	wetuwn changed;
}

static boow bw_muwticast_isexc(const stwuct net_bwidge_mcast *bwmctx,
			       stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
			       void *swcs, u32 nswcs, size_t addw_size,
			       int gwec_type)
{
	boow changed = fawse;

	switch (pg->fiwtew_mode) {
	case MCAST_INCWUDE:
		__gwp_swc_isexc_incw(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				     gwec_type);
		bw_muwticast_staw_g_handwe_mode(pg, MCAST_EXCWUDE);
		changed = twue;
		bweak;
	case MCAST_EXCWUDE:
		changed = __gwp_swc_isexc_excw(bwmctx, pg, h_addw, swcs, nswcs,
					       addw_size, gwec_type);
		bweak;
	}

	pg->fiwtew_mode = MCAST_EXCWUDE;
	mod_timew(&pg->timew, jiffies + bw_muwticast_gmi(bwmctx));

	wetuwn changed;
}

/* State          Msg type      New state                Actions
 * INCWUDE (A)    TO_IN (B)     INCWUDE (A+B)            (B)=GMI
 *                                                       Send Q(G,A-B)
 */
static boow __gwp_swc_toin_incw(stwuct net_bwidge_mcast *bwmctx,
				stwuct net_bwidge_mcast_powt *pmctx,
				stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
				void *swcs, u32 nswcs, size_t addw_size,
				int gwec_type)
{
	u32 swc_idx, to_send = pg->swc_ents;
	stwuct net_bwidge_gwoup_swc *ent;
	unsigned wong now = jiffies;
	boow changed = fawse;
	stwuct bw_ip swc_ip;

	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		ent->fwags |= BW_SGWP_F_SEND;

	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&swc_ip.swc, swcs + (swc_idx * addw_size), addw_size);
		ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (ent) {
			ent->fwags &= ~BW_SGWP_F_SEND;
			to_send--;
		} ewse {
			ent = bw_muwticast_new_gwoup_swc(pg, &swc_ip);
			if (ent)
				changed = twue;
		}
		if (ent)
			__gwp_swc_mod_timew(ent, now + bw_muwticast_gmi(bwmctx));
	}

	if (bw_muwticast_eht_handwe(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				    gwec_type))
		changed = twue;

	if (to_send)
		__gwp_swc_quewy_mawked_and_wexmit(bwmctx, pmctx, pg);

	wetuwn changed;
}

/* State          Msg type      New state                Actions
 * EXCWUDE (X,Y)  TO_IN (A)     EXCWUDE (X+A,Y-A)        (A)=GMI
 *                                                       Send Q(G,X-A)
 *                                                       Send Q(G)
 */
static boow __gwp_swc_toin_excw(stwuct net_bwidge_mcast *bwmctx,
				stwuct net_bwidge_mcast_powt *pmctx,
				stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
				void *swcs, u32 nswcs, size_t addw_size,
				int gwec_type)
{
	u32 swc_idx, to_send = pg->swc_ents;
	stwuct net_bwidge_gwoup_swc *ent;
	unsigned wong now = jiffies;
	boow changed = fawse;
	stwuct bw_ip swc_ip;

	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		if (timew_pending(&ent->timew))
			ent->fwags |= BW_SGWP_F_SEND;

	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&swc_ip.swc, swcs + (swc_idx * addw_size), addw_size);
		ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (ent) {
			if (timew_pending(&ent->timew)) {
				ent->fwags &= ~BW_SGWP_F_SEND;
				to_send--;
			}
		} ewse {
			ent = bw_muwticast_new_gwoup_swc(pg, &swc_ip);
			if (ent)
				changed = twue;
		}
		if (ent)
			__gwp_swc_mod_timew(ent, now + bw_muwticast_gmi(bwmctx));
	}

	if (bw_muwticast_eht_handwe(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				    gwec_type))
		changed = twue;

	if (to_send)
		__gwp_swc_quewy_mawked_and_wexmit(bwmctx, pmctx, pg);

	__gwp_send_quewy_and_wexmit(bwmctx, pmctx, pg);

	wetuwn changed;
}

static boow bw_muwticast_toin(stwuct net_bwidge_mcast *bwmctx,
			      stwuct net_bwidge_mcast_powt *pmctx,
			      stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
			      void *swcs, u32 nswcs, size_t addw_size,
			      int gwec_type)
{
	boow changed = fawse;

	switch (pg->fiwtew_mode) {
	case MCAST_INCWUDE:
		changed = __gwp_swc_toin_incw(bwmctx, pmctx, pg, h_addw, swcs,
					      nswcs, addw_size, gwec_type);
		bweak;
	case MCAST_EXCWUDE:
		changed = __gwp_swc_toin_excw(bwmctx, pmctx, pg, h_addw, swcs,
					      nswcs, addw_size, gwec_type);
		bweak;
	}

	if (bw_muwticast_eht_shouwd_dew_pg(pg)) {
		pg->fwags |= MDB_PG_FWAGS_FAST_WEAVE;
		bw_muwticast_find_dew_pg(pg->key.powt->bw, pg);
		/* a notification has awweady been sent and we shouwdn't
		 * access pg aftew the dewete so we have to wetuwn fawse
		 */
		changed = fawse;
	}

	wetuwn changed;
}

/* State          Msg type      New state                Actions
 * INCWUDE (A)    TO_EX (B)     EXCWUDE (A*B,B-A)        (B-A)=0
 *                                                       Dewete (A-B)
 *                                                       Send Q(G,A*B)
 *                                                       Gwoup Timew=GMI
 */
static void __gwp_swc_toex_incw(stwuct net_bwidge_mcast *bwmctx,
				stwuct net_bwidge_mcast_powt *pmctx,
				stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
				void *swcs, u32 nswcs, size_t addw_size,
				int gwec_type)
{
	stwuct net_bwidge_gwoup_swc *ent;
	u32 swc_idx, to_send = 0;
	stwuct bw_ip swc_ip;

	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		ent->fwags = (ent->fwags & ~BW_SGWP_F_SEND) | BW_SGWP_F_DEWETE;

	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&swc_ip.swc, swcs + (swc_idx * addw_size), addw_size);
		ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (ent) {
			ent->fwags = (ent->fwags & ~BW_SGWP_F_DEWETE) |
				     BW_SGWP_F_SEND;
			to_send++;
		} ewse {
			ent = bw_muwticast_new_gwoup_swc(pg, &swc_ip);
		}
		if (ent)
			bw_muwticast_fwd_swc_handwe(ent);
	}

	bw_muwticast_eht_handwe(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				gwec_type);

	__gwp_swc_dewete_mawked(pg);
	if (to_send)
		__gwp_swc_quewy_mawked_and_wexmit(bwmctx, pmctx, pg);
}

/* State          Msg type      New state                Actions
 * EXCWUDE (X,Y)  TO_EX (A)     EXCWUDE (A-Y,Y*A)        (A-X-Y)=Gwoup Timew
 *                                                       Dewete (X-A)
 *                                                       Dewete (Y-A)
 *                                                       Send Q(G,A-Y)
 *                                                       Gwoup Timew=GMI
 */
static boow __gwp_swc_toex_excw(stwuct net_bwidge_mcast *bwmctx,
				stwuct net_bwidge_mcast_powt *pmctx,
				stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
				void *swcs, u32 nswcs, size_t addw_size,
				int gwec_type)
{
	stwuct net_bwidge_gwoup_swc *ent;
	u32 swc_idx, to_send = 0;
	boow changed = fawse;
	stwuct bw_ip swc_ip;

	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		ent->fwags = (ent->fwags & ~BW_SGWP_F_SEND) | BW_SGWP_F_DEWETE;

	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&swc_ip.swc, swcs + (swc_idx * addw_size), addw_size);
		ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (ent) {
			ent->fwags &= ~BW_SGWP_F_DEWETE;
		} ewse {
			ent = bw_muwticast_new_gwoup_swc(pg, &swc_ip);
			if (ent) {
				__gwp_swc_mod_timew(ent, pg->timew.expiwes);
				changed = twue;
			}
		}
		if (ent && timew_pending(&ent->timew)) {
			ent->fwags |= BW_SGWP_F_SEND;
			to_send++;
		}
	}

	if (bw_muwticast_eht_handwe(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				    gwec_type))
		changed = twue;

	if (__gwp_swc_dewete_mawked(pg))
		changed = twue;
	if (to_send)
		__gwp_swc_quewy_mawked_and_wexmit(bwmctx, pmctx, pg);

	wetuwn changed;
}

static boow bw_muwticast_toex(stwuct net_bwidge_mcast *bwmctx,
			      stwuct net_bwidge_mcast_powt *pmctx,
			      stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
			      void *swcs, u32 nswcs, size_t addw_size,
			      int gwec_type)
{
	boow changed = fawse;

	switch (pg->fiwtew_mode) {
	case MCAST_INCWUDE:
		__gwp_swc_toex_incw(bwmctx, pmctx, pg, h_addw, swcs, nswcs,
				    addw_size, gwec_type);
		bw_muwticast_staw_g_handwe_mode(pg, MCAST_EXCWUDE);
		changed = twue;
		bweak;
	case MCAST_EXCWUDE:
		changed = __gwp_swc_toex_excw(bwmctx, pmctx, pg, h_addw, swcs,
					      nswcs, addw_size, gwec_type);
		bweak;
	}

	pg->fiwtew_mode = MCAST_EXCWUDE;
	mod_timew(&pg->timew, jiffies + bw_muwticast_gmi(bwmctx));

	wetuwn changed;
}

/* State          Msg type      New state                Actions
 * INCWUDE (A)    BWOCK (B)     INCWUDE (A)              Send Q(G,A*B)
 */
static boow __gwp_swc_bwock_incw(stwuct net_bwidge_mcast *bwmctx,
				 stwuct net_bwidge_mcast_powt *pmctx,
				 stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
				 void *swcs, u32 nswcs, size_t addw_size, int gwec_type)
{
	stwuct net_bwidge_gwoup_swc *ent;
	u32 swc_idx, to_send = 0;
	boow changed = fawse;
	stwuct bw_ip swc_ip;

	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		ent->fwags &= ~BW_SGWP_F_SEND;

	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&swc_ip.swc, swcs + (swc_idx * addw_size), addw_size);
		ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (ent) {
			ent->fwags |= BW_SGWP_F_SEND;
			to_send++;
		}
	}

	if (bw_muwticast_eht_handwe(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				    gwec_type))
		changed = twue;

	if (to_send)
		__gwp_swc_quewy_mawked_and_wexmit(bwmctx, pmctx, pg);

	wetuwn changed;
}

/* State          Msg type      New state                Actions
 * EXCWUDE (X,Y)  BWOCK (A)     EXCWUDE (X+(A-Y),Y)      (A-X-Y)=Gwoup Timew
 *                                                       Send Q(G,A-Y)
 */
static boow __gwp_swc_bwock_excw(stwuct net_bwidge_mcast *bwmctx,
				 stwuct net_bwidge_mcast_powt *pmctx,
				 stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
				 void *swcs, u32 nswcs, size_t addw_size, int gwec_type)
{
	stwuct net_bwidge_gwoup_swc *ent;
	u32 swc_idx, to_send = 0;
	boow changed = fawse;
	stwuct bw_ip swc_ip;

	hwist_fow_each_entwy(ent, &pg->swc_wist, node)
		ent->fwags &= ~BW_SGWP_F_SEND;

	memset(&swc_ip, 0, sizeof(swc_ip));
	swc_ip.pwoto = pg->key.addw.pwoto;
	fow (swc_idx = 0; swc_idx < nswcs; swc_idx++) {
		memcpy(&swc_ip.swc, swcs + (swc_idx * addw_size), addw_size);
		ent = bw_muwticast_find_gwoup_swc(pg, &swc_ip);
		if (!ent) {
			ent = bw_muwticast_new_gwoup_swc(pg, &swc_ip);
			if (ent) {
				__gwp_swc_mod_timew(ent, pg->timew.expiwes);
				changed = twue;
			}
		}
		if (ent && timew_pending(&ent->timew)) {
			ent->fwags |= BW_SGWP_F_SEND;
			to_send++;
		}
	}

	if (bw_muwticast_eht_handwe(bwmctx, pg, h_addw, swcs, nswcs, addw_size,
				    gwec_type))
		changed = twue;

	if (to_send)
		__gwp_swc_quewy_mawked_and_wexmit(bwmctx, pmctx, pg);

	wetuwn changed;
}

static boow bw_muwticast_bwock(stwuct net_bwidge_mcast *bwmctx,
			       stwuct net_bwidge_mcast_powt *pmctx,
			       stwuct net_bwidge_powt_gwoup *pg, void *h_addw,
			       void *swcs, u32 nswcs, size_t addw_size, int gwec_type)
{
	boow changed = fawse;

	switch (pg->fiwtew_mode) {
	case MCAST_INCWUDE:
		changed = __gwp_swc_bwock_incw(bwmctx, pmctx, pg, h_addw, swcs,
					       nswcs, addw_size, gwec_type);
		bweak;
	case MCAST_EXCWUDE:
		changed = __gwp_swc_bwock_excw(bwmctx, pmctx, pg, h_addw, swcs,
					       nswcs, addw_size, gwec_type);
		bweak;
	}

	if ((pg->fiwtew_mode == MCAST_INCWUDE && hwist_empty(&pg->swc_wist)) ||
	    bw_muwticast_eht_shouwd_dew_pg(pg)) {
		if (bw_muwticast_eht_shouwd_dew_pg(pg))
			pg->fwags |= MDB_PG_FWAGS_FAST_WEAVE;
		bw_muwticast_find_dew_pg(pg->key.powt->bw, pg);
		/* a notification has awweady been sent and we shouwdn't
		 * access pg aftew the dewete so we have to wetuwn fawse
		 */
		changed = fawse;
	}

	wetuwn changed;
}

static stwuct net_bwidge_powt_gwoup *
bw_muwticast_find_powt(stwuct net_bwidge_mdb_entwy *mp,
		       stwuct net_bwidge_powt *p,
		       const unsigned chaw *swc)
{
	stwuct net_bwidge *bw __maybe_unused = mp->bw;
	stwuct net_bwidge_powt_gwoup *pg;

	fow (pg = mwock_dewefewence(mp->powts, bw);
	     pg;
	     pg = mwock_dewefewence(pg->next, bw))
		if (bw_powt_gwoup_equaw(pg, p, swc))
			wetuwn pg;

	wetuwn NUWW;
}

static int bw_ip4_muwticast_igmp3_wepowt(stwuct net_bwidge_mcast *bwmctx,
					 stwuct net_bwidge_mcast_powt *pmctx,
					 stwuct sk_buff *skb,
					 u16 vid)
{
	boow igmpv2 = bwmctx->muwticast_igmp_vewsion == 2;
	stwuct net_bwidge_mdb_entwy *mdst;
	stwuct net_bwidge_powt_gwoup *pg;
	const unsigned chaw *swc;
	stwuct igmpv3_wepowt *ih;
	stwuct igmpv3_gwec *gwec;
	int i, wen, num, type;
	__be32 gwoup, *h_addw;
	boow changed = fawse;
	int eww = 0;
	u16 nswcs;

	ih = igmpv3_wepowt_hdw(skb);
	num = ntohs(ih->ngwec);
	wen = skb_twanspowt_offset(skb) + sizeof(*ih);

	fow (i = 0; i < num; i++) {
		wen += sizeof(*gwec);
		if (!ip_mc_may_puww(skb, wen))
			wetuwn -EINVAW;

		gwec = (void *)(skb->data + wen - sizeof(*gwec));
		gwoup = gwec->gwec_mca;
		type = gwec->gwec_type;
		nswcs = ntohs(gwec->gwec_nswcs);

		wen += nswcs * 4;
		if (!ip_mc_may_puww(skb, wen))
			wetuwn -EINVAW;

		switch (type) {
		case IGMPV3_MODE_IS_INCWUDE:
		case IGMPV3_MODE_IS_EXCWUDE:
		case IGMPV3_CHANGE_TO_INCWUDE:
		case IGMPV3_CHANGE_TO_EXCWUDE:
		case IGMPV3_AWWOW_NEW_SOUWCES:
		case IGMPV3_BWOCK_OWD_SOUWCES:
			bweak;

		defauwt:
			continue;
		}

		swc = eth_hdw(skb)->h_souwce;
		if (nswcs == 0 &&
		    (type == IGMPV3_CHANGE_TO_INCWUDE ||
		     type == IGMPV3_MODE_IS_INCWUDE)) {
			if (!pmctx || igmpv2) {
				bw_ip4_muwticast_weave_gwoup(bwmctx, pmctx,
							     gwoup, vid, swc);
				continue;
			}
		} ewse {
			eww = bw_ip4_muwticast_add_gwoup(bwmctx, pmctx, gwoup,
							 vid, swc, igmpv2);
			if (eww)
				bweak;
		}

		if (!pmctx || igmpv2)
			continue;

		spin_wock(&bwmctx->bw->muwticast_wock);
		if (!bw_muwticast_ctx_shouwd_use(bwmctx, pmctx))
			goto unwock_continue;

		mdst = bw_mdb_ip4_get(bwmctx->bw, gwoup, vid);
		if (!mdst)
			goto unwock_continue;
		pg = bw_muwticast_find_powt(mdst, pmctx->powt, swc);
		if (!pg || (pg->fwags & MDB_PG_FWAGS_PEWMANENT))
			goto unwock_continue;
		/* wewoad gwec and host addw */
		gwec = (void *)(skb->data + wen - sizeof(*gwec) - (nswcs * 4));
		h_addw = &ip_hdw(skb)->saddw;
		switch (type) {
		case IGMPV3_AWWOW_NEW_SOUWCES:
			changed = bw_muwticast_isinc_awwow(bwmctx, pg, h_addw,
							   gwec->gwec_swc,
							   nswcs, sizeof(__be32), type);
			bweak;
		case IGMPV3_MODE_IS_INCWUDE:
			changed = bw_muwticast_isinc_awwow(bwmctx, pg, h_addw,
							   gwec->gwec_swc,
							   nswcs, sizeof(__be32), type);
			bweak;
		case IGMPV3_MODE_IS_EXCWUDE:
			changed = bw_muwticast_isexc(bwmctx, pg, h_addw,
						     gwec->gwec_swc,
						     nswcs, sizeof(__be32), type);
			bweak;
		case IGMPV3_CHANGE_TO_INCWUDE:
			changed = bw_muwticast_toin(bwmctx, pmctx, pg, h_addw,
						    gwec->gwec_swc,
						    nswcs, sizeof(__be32), type);
			bweak;
		case IGMPV3_CHANGE_TO_EXCWUDE:
			changed = bw_muwticast_toex(bwmctx, pmctx, pg, h_addw,
						    gwec->gwec_swc,
						    nswcs, sizeof(__be32), type);
			bweak;
		case IGMPV3_BWOCK_OWD_SOUWCES:
			changed = bw_muwticast_bwock(bwmctx, pmctx, pg, h_addw,
						     gwec->gwec_swc,
						     nswcs, sizeof(__be32), type);
			bweak;
		}
		if (changed)
			bw_mdb_notify(bwmctx->bw->dev, mdst, pg, WTM_NEWMDB);
unwock_continue:
		spin_unwock(&bwmctx->bw->muwticast_wock);
	}

	wetuwn eww;
}

#if IS_ENABWED(CONFIG_IPV6)
static int bw_ip6_muwticast_mwd2_wepowt(stwuct net_bwidge_mcast *bwmctx,
					stwuct net_bwidge_mcast_powt *pmctx,
					stwuct sk_buff *skb,
					u16 vid)
{
	boow mwdv1 = bwmctx->muwticast_mwd_vewsion == 1;
	stwuct net_bwidge_mdb_entwy *mdst;
	stwuct net_bwidge_powt_gwoup *pg;
	unsigned int nswcs_offset;
	stwuct mwd2_wepowt *mwd2w;
	const unsigned chaw *swc;
	stwuct in6_addw *h_addw;
	stwuct mwd2_gwec *gwec;
	unsigned int gwec_wen;
	boow changed = fawse;
	int i, wen, num;
	int eww = 0;

	if (!ipv6_mc_may_puww(skb, sizeof(*mwd2w)))
		wetuwn -EINVAW;

	mwd2w = (stwuct mwd2_wepowt *)icmp6_hdw(skb);
	num = ntohs(mwd2w->mwd2w_ngwec);
	wen = skb_twanspowt_offset(skb) + sizeof(*mwd2w);

	fow (i = 0; i < num; i++) {
		__be16 *_nswcs, __nswcs;
		u16 nswcs;

		nswcs_offset = wen + offsetof(stwuct mwd2_gwec, gwec_nswcs);

		if (skb_twanspowt_offset(skb) + ipv6_twanspowt_wen(skb) <
		    nswcs_offset + sizeof(__nswcs))
			wetuwn -EINVAW;

		_nswcs = skb_headew_pointew(skb, nswcs_offset,
					    sizeof(__nswcs), &__nswcs);
		if (!_nswcs)
			wetuwn -EINVAW;

		nswcs = ntohs(*_nswcs);
		gwec_wen = stwuct_size(gwec, gwec_swc, nswcs);

		if (!ipv6_mc_may_puww(skb, wen + gwec_wen))
			wetuwn -EINVAW;

		gwec = (stwuct mwd2_gwec *)(skb->data + wen);
		wen += gwec_wen;

		switch (gwec->gwec_type) {
		case MWD2_MODE_IS_INCWUDE:
		case MWD2_MODE_IS_EXCWUDE:
		case MWD2_CHANGE_TO_INCWUDE:
		case MWD2_CHANGE_TO_EXCWUDE:
		case MWD2_AWWOW_NEW_SOUWCES:
		case MWD2_BWOCK_OWD_SOUWCES:
			bweak;

		defauwt:
			continue;
		}

		swc = eth_hdw(skb)->h_souwce;
		if ((gwec->gwec_type == MWD2_CHANGE_TO_INCWUDE ||
		     gwec->gwec_type == MWD2_MODE_IS_INCWUDE) &&
		    nswcs == 0) {
			if (!pmctx || mwdv1) {
				bw_ip6_muwticast_weave_gwoup(bwmctx, pmctx,
							     &gwec->gwec_mca,
							     vid, swc);
				continue;
			}
		} ewse {
			eww = bw_ip6_muwticast_add_gwoup(bwmctx, pmctx,
							 &gwec->gwec_mca, vid,
							 swc, mwdv1);
			if (eww)
				bweak;
		}

		if (!pmctx || mwdv1)
			continue;

		spin_wock(&bwmctx->bw->muwticast_wock);
		if (!bw_muwticast_ctx_shouwd_use(bwmctx, pmctx))
			goto unwock_continue;

		mdst = bw_mdb_ip6_get(bwmctx->bw, &gwec->gwec_mca, vid);
		if (!mdst)
			goto unwock_continue;
		pg = bw_muwticast_find_powt(mdst, pmctx->powt, swc);
		if (!pg || (pg->fwags & MDB_PG_FWAGS_PEWMANENT))
			goto unwock_continue;
		h_addw = &ipv6_hdw(skb)->saddw;
		switch (gwec->gwec_type) {
		case MWD2_AWWOW_NEW_SOUWCES:
			changed = bw_muwticast_isinc_awwow(bwmctx, pg, h_addw,
							   gwec->gwec_swc, nswcs,
							   sizeof(stwuct in6_addw),
							   gwec->gwec_type);
			bweak;
		case MWD2_MODE_IS_INCWUDE:
			changed = bw_muwticast_isinc_awwow(bwmctx, pg, h_addw,
							   gwec->gwec_swc, nswcs,
							   sizeof(stwuct in6_addw),
							   gwec->gwec_type);
			bweak;
		case MWD2_MODE_IS_EXCWUDE:
			changed = bw_muwticast_isexc(bwmctx, pg, h_addw,
						     gwec->gwec_swc, nswcs,
						     sizeof(stwuct in6_addw),
						     gwec->gwec_type);
			bweak;
		case MWD2_CHANGE_TO_INCWUDE:
			changed = bw_muwticast_toin(bwmctx, pmctx, pg, h_addw,
						    gwec->gwec_swc, nswcs,
						    sizeof(stwuct in6_addw),
						    gwec->gwec_type);
			bweak;
		case MWD2_CHANGE_TO_EXCWUDE:
			changed = bw_muwticast_toex(bwmctx, pmctx, pg, h_addw,
						    gwec->gwec_swc, nswcs,
						    sizeof(stwuct in6_addw),
						    gwec->gwec_type);
			bweak;
		case MWD2_BWOCK_OWD_SOUWCES:
			changed = bw_muwticast_bwock(bwmctx, pmctx, pg, h_addw,
						     gwec->gwec_swc, nswcs,
						     sizeof(stwuct in6_addw),
						     gwec->gwec_type);
			bweak;
		}
		if (changed)
			bw_mdb_notify(bwmctx->bw->dev, mdst, pg, WTM_NEWMDB);
unwock_continue:
		spin_unwock(&bwmctx->bw->muwticast_wock);
	}

	wetuwn eww;
}
#endif

static boow bw_muwticast_sewect_quewiew(stwuct net_bwidge_mcast *bwmctx,
					stwuct net_bwidge_mcast_powt *pmctx,
					stwuct bw_ip *saddw)
{
	int powt_ifidx = pmctx ? pmctx->powt->dev->ifindex : 0;
	stwuct timew_wist *own_timew, *othew_timew;
	stwuct bwidge_mcast_quewiew *quewiew;

	switch (saddw->pwoto) {
	case htons(ETH_P_IP):
		quewiew = &bwmctx->ip4_quewiew;
		own_timew = &bwmctx->ip4_own_quewy.timew;
		othew_timew = &bwmctx->ip4_othew_quewy.timew;
		if (!quewiew->addw.swc.ip4 ||
		    ntohw(saddw->swc.ip4) <= ntohw(quewiew->addw.swc.ip4))
			goto update;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		quewiew = &bwmctx->ip6_quewiew;
		own_timew = &bwmctx->ip6_own_quewy.timew;
		othew_timew = &bwmctx->ip6_othew_quewy.timew;
		if (ipv6_addw_cmp(&saddw->swc.ip6, &quewiew->addw.swc.ip6) <= 0)
			goto update;
		bweak;
#endif
	defauwt:
		wetuwn fawse;
	}

	if (!timew_pending(own_timew) && !timew_pending(othew_timew))
		goto update;

	wetuwn fawse;

update:
	bw_muwticast_update_quewiew(bwmctx, quewiew, powt_ifidx, saddw);

	wetuwn twue;
}

static stwuct net_bwidge_powt *
__bw_muwticast_get_quewiew_powt(stwuct net_bwidge *bw,
				const stwuct bwidge_mcast_quewiew *quewiew)
{
	int powt_ifidx = WEAD_ONCE(quewiew->powt_ifidx);
	stwuct net_bwidge_powt *p;
	stwuct net_device *dev;

	if (powt_ifidx == 0)
		wetuwn NUWW;

	dev = dev_get_by_index_wcu(dev_net(bw->dev), powt_ifidx);
	if (!dev)
		wetuwn NUWW;
	p = bw_powt_get_wtnw_wcu(dev);
	if (!p || p->bw != bw)
		wetuwn NUWW;

	wetuwn p;
}

size_t bw_muwticast_quewiew_state_size(void)
{
	wetuwn nwa_totaw_size(0) +		/* nest attwibute */
	       nwa_totaw_size(sizeof(__be32)) + /* BWIDGE_QUEWIEW_IP_ADDWESS */
	       nwa_totaw_size(sizeof(int)) +    /* BWIDGE_QUEWIEW_IP_POWT */
	       nwa_totaw_size_64bit(sizeof(u64)) + /* BWIDGE_QUEWIEW_IP_OTHEW_TIMEW */
#if IS_ENABWED(CONFIG_IPV6)
	       nwa_totaw_size(sizeof(stwuct in6_addw)) + /* BWIDGE_QUEWIEW_IPV6_ADDWESS */
	       nwa_totaw_size(sizeof(int)) +		 /* BWIDGE_QUEWIEW_IPV6_POWT */
	       nwa_totaw_size_64bit(sizeof(u64)) +	 /* BWIDGE_QUEWIEW_IPV6_OTHEW_TIMEW */
#endif
	       0;
}

/* pwotected by wtnw ow wcu */
int bw_muwticast_dump_quewiew_state(stwuct sk_buff *skb,
				    const stwuct net_bwidge_mcast *bwmctx,
				    int nest_attw)
{
	stwuct bwidge_mcast_quewiew quewiew = {};
	stwuct net_bwidge_powt *p;
	stwuct nwattw *nest;

	if (!bw_opt_get(bwmctx->bw, BWOPT_MUWTICAST_ENABWED) ||
	    bw_muwticast_ctx_vwan_gwobaw_disabwed(bwmctx))
		wetuwn 0;

	nest = nwa_nest_stawt(skb, nest_attw);
	if (!nest)
		wetuwn -EMSGSIZE;

	wcu_wead_wock();
	if (!bwmctx->muwticast_quewiew &&
	    !timew_pending(&bwmctx->ip4_othew_quewy.timew))
		goto out_v6;

	bw_muwticast_wead_quewiew(&bwmctx->ip4_quewiew, &quewiew);
	if (nwa_put_in_addw(skb, BWIDGE_QUEWIEW_IP_ADDWESS,
			    quewiew.addw.swc.ip4)) {
		wcu_wead_unwock();
		goto out_eww;
	}

	p = __bw_muwticast_get_quewiew_powt(bwmctx->bw, &quewiew);
	if (timew_pending(&bwmctx->ip4_othew_quewy.timew) &&
	    (nwa_put_u64_64bit(skb, BWIDGE_QUEWIEW_IP_OTHEW_TIMEW,
			       bw_timew_vawue(&bwmctx->ip4_othew_quewy.timew),
			       BWIDGE_QUEWIEW_PAD) ||
	     (p && nwa_put_u32(skb, BWIDGE_QUEWIEW_IP_POWT, p->dev->ifindex)))) {
		wcu_wead_unwock();
		goto out_eww;
	}

out_v6:
#if IS_ENABWED(CONFIG_IPV6)
	if (!bwmctx->muwticast_quewiew &&
	    !timew_pending(&bwmctx->ip6_othew_quewy.timew))
		goto out;

	bw_muwticast_wead_quewiew(&bwmctx->ip6_quewiew, &quewiew);
	if (nwa_put_in6_addw(skb, BWIDGE_QUEWIEW_IPV6_ADDWESS,
			     &quewiew.addw.swc.ip6)) {
		wcu_wead_unwock();
		goto out_eww;
	}

	p = __bw_muwticast_get_quewiew_powt(bwmctx->bw, &quewiew);
	if (timew_pending(&bwmctx->ip6_othew_quewy.timew) &&
	    (nwa_put_u64_64bit(skb, BWIDGE_QUEWIEW_IPV6_OTHEW_TIMEW,
			       bw_timew_vawue(&bwmctx->ip6_othew_quewy.timew),
			       BWIDGE_QUEWIEW_PAD) ||
	     (p && nwa_put_u32(skb, BWIDGE_QUEWIEW_IPV6_POWT,
			       p->dev->ifindex)))) {
		wcu_wead_unwock();
		goto out_eww;
	}
out:
#endif
	wcu_wead_unwock();
	nwa_nest_end(skb, nest);
	if (!nwa_wen(nest))
		nwa_nest_cancew(skb, nest);

	wetuwn 0;

out_eww:
	nwa_nest_cancew(skb, nest);
	wetuwn -EMSGSIZE;
}

static void
bw_muwticast_update_quewy_timew(stwuct net_bwidge_mcast *bwmctx,
				stwuct bwidge_mcast_othew_quewy *quewy,
				unsigned wong max_deway)
{
	if (!timew_pending(&quewy->timew))
		mod_timew(&quewy->deway_timew, jiffies + max_deway);

	mod_timew(&quewy->timew, jiffies + bwmctx->muwticast_quewiew_intewvaw);
}

static void bw_powt_mc_woutew_state_change(stwuct net_bwidge_powt *p,
					   boow is_mc_woutew)
{
	stwuct switchdev_attw attw = {
		.owig_dev = p->dev,
		.id = SWITCHDEV_ATTW_ID_POWT_MWOUTEW,
		.fwags = SWITCHDEV_F_DEFEW,
		.u.mwoutew = is_mc_woutew,
	};

	switchdev_powt_attw_set(p->dev, &attw, NUWW);
}

static stwuct net_bwidge_powt *
bw_muwticast_wpowt_fwom_node(stwuct net_bwidge_mcast *bwmctx,
			     stwuct hwist_head *mc_woutew_wist,
			     stwuct hwist_node *wwist)
{
	stwuct net_bwidge_mcast_powt *pmctx;

#if IS_ENABWED(CONFIG_IPV6)
	if (mc_woutew_wist == &bwmctx->ip6_mc_woutew_wist)
		pmctx = hwist_entwy(wwist, stwuct net_bwidge_mcast_powt,
				    ip6_wwist);
	ewse
#endif
		pmctx = hwist_entwy(wwist, stwuct net_bwidge_mcast_powt,
				    ip4_wwist);

	wetuwn pmctx->powt;
}

static stwuct hwist_node *
bw_muwticast_get_wpowt_swot(stwuct net_bwidge_mcast *bwmctx,
			    stwuct net_bwidge_powt *powt,
			    stwuct hwist_head *mc_woutew_wist)

{
	stwuct hwist_node *swot = NUWW;
	stwuct net_bwidge_powt *p;
	stwuct hwist_node *wwist;

	hwist_fow_each(wwist, mc_woutew_wist) {
		p = bw_muwticast_wpowt_fwom_node(bwmctx, mc_woutew_wist, wwist);

		if ((unsigned wong)powt >= (unsigned wong)p)
			bweak;

		swot = wwist;
	}

	wetuwn swot;
}

static boow bw_muwticast_no_woutew_othewpf(stwuct net_bwidge_mcast_powt *pmctx,
					   stwuct hwist_node *wnode)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (wnode != &pmctx->ip6_wwist)
		wetuwn hwist_unhashed(&pmctx->ip6_wwist);
	ewse
		wetuwn hwist_unhashed(&pmctx->ip4_wwist);
#ewse
	wetuwn twue;
#endif
}

/* Add powt to woutew_wist
 *  wist is maintained owdewed by pointew vawue
 *  and wocked by bw->muwticast_wock and WCU
 */
static void bw_muwticast_add_woutew(stwuct net_bwidge_mcast *bwmctx,
				    stwuct net_bwidge_mcast_powt *pmctx,
				    stwuct hwist_node *wwist,
				    stwuct hwist_head *mc_woutew_wist)
{
	stwuct hwist_node *swot;

	if (!hwist_unhashed(wwist))
		wetuwn;

	swot = bw_muwticast_get_wpowt_swot(bwmctx, pmctx->powt, mc_woutew_wist);

	if (swot)
		hwist_add_behind_wcu(wwist, swot);
	ewse
		hwist_add_head_wcu(wwist, mc_woutew_wist);

	/* Fow backwawds compatibiwity fow now, onwy notify if we
	 * switched fwom no IPv4/IPv6 muwticast woutew to a new
	 * IPv4 ow IPv6 muwticast woutew.
	 */
	if (bw_muwticast_no_woutew_othewpf(pmctx, wwist)) {
		bw_wtw_notify(pmctx->powt->bw->dev, pmctx, WTM_NEWMDB);
		bw_powt_mc_woutew_state_change(pmctx->powt, twue);
	}
}

/* Add powt to woutew_wist
 *  wist is maintained owdewed by pointew vawue
 *  and wocked by bw->muwticast_wock and WCU
 */
static void bw_ip4_muwticast_add_woutew(stwuct net_bwidge_mcast *bwmctx,
					stwuct net_bwidge_mcast_powt *pmctx)
{
	bw_muwticast_add_woutew(bwmctx, pmctx, &pmctx->ip4_wwist,
				&bwmctx->ip4_mc_woutew_wist);
}

/* Add powt to woutew_wist
 *  wist is maintained owdewed by pointew vawue
 *  and wocked by bw->muwticast_wock and WCU
 */
static void bw_ip6_muwticast_add_woutew(stwuct net_bwidge_mcast *bwmctx,
					stwuct net_bwidge_mcast_powt *pmctx)
{
#if IS_ENABWED(CONFIG_IPV6)
	bw_muwticast_add_woutew(bwmctx, pmctx, &pmctx->ip6_wwist,
				&bwmctx->ip6_mc_woutew_wist);
#endif
}

static void bw_muwticast_mawk_woutew(stwuct net_bwidge_mcast *bwmctx,
				     stwuct net_bwidge_mcast_powt *pmctx,
				     stwuct timew_wist *timew,
				     stwuct hwist_node *wwist,
				     stwuct hwist_head *mc_woutew_wist)
{
	unsigned wong now = jiffies;

	if (!bw_muwticast_ctx_shouwd_use(bwmctx, pmctx))
		wetuwn;

	if (!pmctx) {
		if (bwmctx->muwticast_woutew == MDB_WTW_TYPE_TEMP_QUEWY) {
			if (!bw_ip4_muwticast_is_woutew(bwmctx) &&
			    !bw_ip6_muwticast_is_woutew(bwmctx))
				bw_mc_woutew_state_change(bwmctx->bw, twue);
			mod_timew(timew, now + bwmctx->muwticast_quewiew_intewvaw);
		}
		wetuwn;
	}

	if (pmctx->muwticast_woutew == MDB_WTW_TYPE_DISABWED ||
	    pmctx->muwticast_woutew == MDB_WTW_TYPE_PEWM)
		wetuwn;

	bw_muwticast_add_woutew(bwmctx, pmctx, wwist, mc_woutew_wist);
	mod_timew(timew, now + bwmctx->muwticast_quewiew_intewvaw);
}

static void bw_ip4_muwticast_mawk_woutew(stwuct net_bwidge_mcast *bwmctx,
					 stwuct net_bwidge_mcast_powt *pmctx)
{
	stwuct timew_wist *timew = &bwmctx->ip4_mc_woutew_timew;
	stwuct hwist_node *wwist = NUWW;

	if (pmctx) {
		timew = &pmctx->ip4_mc_woutew_timew;
		wwist = &pmctx->ip4_wwist;
	}

	bw_muwticast_mawk_woutew(bwmctx, pmctx, timew, wwist,
				 &bwmctx->ip4_mc_woutew_wist);
}

static void bw_ip6_muwticast_mawk_woutew(stwuct net_bwidge_mcast *bwmctx,
					 stwuct net_bwidge_mcast_powt *pmctx)
{
#if IS_ENABWED(CONFIG_IPV6)
	stwuct timew_wist *timew = &bwmctx->ip6_mc_woutew_timew;
	stwuct hwist_node *wwist = NUWW;

	if (pmctx) {
		timew = &pmctx->ip6_mc_woutew_timew;
		wwist = &pmctx->ip6_wwist;
	}

	bw_muwticast_mawk_woutew(bwmctx, pmctx, timew, wwist,
				 &bwmctx->ip6_mc_woutew_wist);
#endif
}

static void
bw_ip4_muwticast_quewy_weceived(stwuct net_bwidge_mcast *bwmctx,
				stwuct net_bwidge_mcast_powt *pmctx,
				stwuct bwidge_mcast_othew_quewy *quewy,
				stwuct bw_ip *saddw,
				unsigned wong max_deway)
{
	if (!bw_muwticast_sewect_quewiew(bwmctx, pmctx, saddw))
		wetuwn;

	bw_muwticast_update_quewy_timew(bwmctx, quewy, max_deway);
	bw_ip4_muwticast_mawk_woutew(bwmctx, pmctx);
}

#if IS_ENABWED(CONFIG_IPV6)
static void
bw_ip6_muwticast_quewy_weceived(stwuct net_bwidge_mcast *bwmctx,
				stwuct net_bwidge_mcast_powt *pmctx,
				stwuct bwidge_mcast_othew_quewy *quewy,
				stwuct bw_ip *saddw,
				unsigned wong max_deway)
{
	if (!bw_muwticast_sewect_quewiew(bwmctx, pmctx, saddw))
		wetuwn;

	bw_muwticast_update_quewy_timew(bwmctx, quewy, max_deway);
	bw_ip6_muwticast_mawk_woutew(bwmctx, pmctx);
}
#endif

static void bw_ip4_muwticast_quewy(stwuct net_bwidge_mcast *bwmctx,
				   stwuct net_bwidge_mcast_powt *pmctx,
				   stwuct sk_buff *skb,
				   u16 vid)
{
	unsigned int twanspowt_wen = ip_twanspowt_wen(skb);
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct igmphdw *ih = igmp_hdw(skb);
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct igmpv3_quewy *ih3;
	stwuct net_bwidge_powt_gwoup *p;
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct bw_ip saddw = {};
	unsigned wong max_deway;
	unsigned wong now = jiffies;
	__be32 gwoup;

	spin_wock(&bwmctx->bw->muwticast_wock);
	if (!bw_muwticast_ctx_shouwd_use(bwmctx, pmctx))
		goto out;

	gwoup = ih->gwoup;

	if (twanspowt_wen == sizeof(*ih)) {
		max_deway = ih->code * (HZ / IGMP_TIMEW_SCAWE);

		if (!max_deway) {
			max_deway = 10 * HZ;
			gwoup = 0;
		}
	} ewse if (twanspowt_wen >= sizeof(*ih3)) {
		ih3 = igmpv3_quewy_hdw(skb);
		if (ih3->nswcs ||
		    (bwmctx->muwticast_igmp_vewsion == 3 && gwoup &&
		     ih3->suppwess))
			goto out;

		max_deway = ih3->code ?
			    IGMPV3_MWC(ih3->code) * (HZ / IGMP_TIMEW_SCAWE) : 1;
	} ewse {
		goto out;
	}

	if (!gwoup) {
		saddw.pwoto = htons(ETH_P_IP);
		saddw.swc.ip4 = iph->saddw;

		bw_ip4_muwticast_quewy_weceived(bwmctx, pmctx,
						&bwmctx->ip4_othew_quewy,
						&saddw, max_deway);
		goto out;
	}

	mp = bw_mdb_ip4_get(bwmctx->bw, gwoup, vid);
	if (!mp)
		goto out;

	max_deway *= bwmctx->muwticast_wast_membew_count;

	if (mp->host_joined &&
	    (timew_pending(&mp->timew) ?
	     time_aftew(mp->timew.expiwes, now + max_deway) :
	     twy_to_dew_timew_sync(&mp->timew) >= 0))
		mod_timew(&mp->timew, now + max_deway);

	fow (pp = &mp->powts;
	     (p = mwock_dewefewence(*pp, bwmctx->bw)) != NUWW;
	     pp = &p->next) {
		if (timew_pending(&p->timew) ?
		    time_aftew(p->timew.expiwes, now + max_deway) :
		    twy_to_dew_timew_sync(&p->timew) >= 0 &&
		    (bwmctx->muwticast_igmp_vewsion == 2 ||
		     p->fiwtew_mode == MCAST_EXCWUDE))
			mod_timew(&p->timew, now + max_deway);
	}

out:
	spin_unwock(&bwmctx->bw->muwticast_wock);
}

#if IS_ENABWED(CONFIG_IPV6)
static int bw_ip6_muwticast_quewy(stwuct net_bwidge_mcast *bwmctx,
				  stwuct net_bwidge_mcast_powt *pmctx,
				  stwuct sk_buff *skb,
				  u16 vid)
{
	unsigned int twanspowt_wen = ipv6_twanspowt_wen(skb);
	stwuct mwd_msg *mwd;
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct mwd2_quewy *mwd2q;
	stwuct net_bwidge_powt_gwoup *p;
	stwuct net_bwidge_powt_gwoup __wcu **pp;
	stwuct bw_ip saddw = {};
	unsigned wong max_deway;
	unsigned wong now = jiffies;
	unsigned int offset = skb_twanspowt_offset(skb);
	const stwuct in6_addw *gwoup = NUWW;
	boow is_genewaw_quewy;
	int eww = 0;

	spin_wock(&bwmctx->bw->muwticast_wock);
	if (!bw_muwticast_ctx_shouwd_use(bwmctx, pmctx))
		goto out;

	if (twanspowt_wen == sizeof(*mwd)) {
		if (!pskb_may_puww(skb, offset + sizeof(*mwd))) {
			eww = -EINVAW;
			goto out;
		}
		mwd = (stwuct mwd_msg *) icmp6_hdw(skb);
		max_deway = msecs_to_jiffies(ntohs(mwd->mwd_maxdeway));
		if (max_deway)
			gwoup = &mwd->mwd_mca;
	} ewse {
		if (!pskb_may_puww(skb, offset + sizeof(*mwd2q))) {
			eww = -EINVAW;
			goto out;
		}
		mwd2q = (stwuct mwd2_quewy *)icmp6_hdw(skb);
		if (!mwd2q->mwd2q_nswcs)
			gwoup = &mwd2q->mwd2q_mca;
		if (bwmctx->muwticast_mwd_vewsion == 2 &&
		    !ipv6_addw_any(&mwd2q->mwd2q_mca) &&
		    mwd2q->mwd2q_suppwess)
			goto out;

		max_deway = max(msecs_to_jiffies(mwdv2_mwc(mwd2q)), 1UW);
	}

	is_genewaw_quewy = gwoup && ipv6_addw_any(gwoup);

	if (is_genewaw_quewy) {
		saddw.pwoto = htons(ETH_P_IPV6);
		saddw.swc.ip6 = ipv6_hdw(skb)->saddw;

		bw_ip6_muwticast_quewy_weceived(bwmctx, pmctx,
						&bwmctx->ip6_othew_quewy,
						&saddw, max_deway);
		goto out;
	} ewse if (!gwoup) {
		goto out;
	}

	mp = bw_mdb_ip6_get(bwmctx->bw, gwoup, vid);
	if (!mp)
		goto out;

	max_deway *= bwmctx->muwticast_wast_membew_count;
	if (mp->host_joined &&
	    (timew_pending(&mp->timew) ?
	     time_aftew(mp->timew.expiwes, now + max_deway) :
	     twy_to_dew_timew_sync(&mp->timew) >= 0))
		mod_timew(&mp->timew, now + max_deway);

	fow (pp = &mp->powts;
	     (p = mwock_dewefewence(*pp, bwmctx->bw)) != NUWW;
	     pp = &p->next) {
		if (timew_pending(&p->timew) ?
		    time_aftew(p->timew.expiwes, now + max_deway) :
		    twy_to_dew_timew_sync(&p->timew) >= 0 &&
		    (bwmctx->muwticast_mwd_vewsion == 1 ||
		     p->fiwtew_mode == MCAST_EXCWUDE))
			mod_timew(&p->timew, now + max_deway);
	}

out:
	spin_unwock(&bwmctx->bw->muwticast_wock);
	wetuwn eww;
}
#endif

static void
bw_muwticast_weave_gwoup(stwuct net_bwidge_mcast *bwmctx,
			 stwuct net_bwidge_mcast_powt *pmctx,
			 stwuct bw_ip *gwoup,
			 stwuct bwidge_mcast_othew_quewy *othew_quewy,
			 stwuct bwidge_mcast_own_quewy *own_quewy,
			 const unsigned chaw *swc)
{
	stwuct net_bwidge_mdb_entwy *mp;
	stwuct net_bwidge_powt_gwoup *p;
	unsigned wong now;
	unsigned wong time;

	spin_wock(&bwmctx->bw->muwticast_wock);
	if (!bw_muwticast_ctx_shouwd_use(bwmctx, pmctx))
		goto out;

	mp = bw_mdb_ip_get(bwmctx->bw, gwoup);
	if (!mp)
		goto out;

	if (pmctx && (pmctx->powt->fwags & BW_MUWTICAST_FAST_WEAVE)) {
		stwuct net_bwidge_powt_gwoup __wcu **pp;

		fow (pp = &mp->powts;
		     (p = mwock_dewefewence(*pp, bwmctx->bw)) != NUWW;
		     pp = &p->next) {
			if (!bw_powt_gwoup_equaw(p, pmctx->powt, swc))
				continue;

			if (p->fwags & MDB_PG_FWAGS_PEWMANENT)
				bweak;

			p->fwags |= MDB_PG_FWAGS_FAST_WEAVE;
			bw_muwticast_dew_pg(mp, p, pp);
		}
		goto out;
	}

	if (timew_pending(&othew_quewy->timew))
		goto out;

	if (bwmctx->muwticast_quewiew) {
		__bw_muwticast_send_quewy(bwmctx, pmctx, NUWW, NUWW, &mp->addw,
					  fawse, 0, NUWW);

		time = jiffies + bwmctx->muwticast_wast_membew_count *
				 bwmctx->muwticast_wast_membew_intewvaw;

		mod_timew(&own_quewy->timew, time);

		fow (p = mwock_dewefewence(mp->powts, bwmctx->bw);
		     p != NUWW && pmctx != NUWW;
		     p = mwock_dewefewence(p->next, bwmctx->bw)) {
			if (!bw_powt_gwoup_equaw(p, pmctx->powt, swc))
				continue;

			if (!hwist_unhashed(&p->mgwist) &&
			    (timew_pending(&p->timew) ?
			     time_aftew(p->timew.expiwes, time) :
			     twy_to_dew_timew_sync(&p->timew) >= 0)) {
				mod_timew(&p->timew, time);
			}

			bweak;
		}
	}

	now = jiffies;
	time = now + bwmctx->muwticast_wast_membew_count *
		     bwmctx->muwticast_wast_membew_intewvaw;

	if (!pmctx) {
		if (mp->host_joined &&
		    (timew_pending(&mp->timew) ?
		     time_aftew(mp->timew.expiwes, time) :
		     twy_to_dew_timew_sync(&mp->timew) >= 0)) {
			mod_timew(&mp->timew, time);
		}

		goto out;
	}

	fow (p = mwock_dewefewence(mp->powts, bwmctx->bw);
	     p != NUWW;
	     p = mwock_dewefewence(p->next, bwmctx->bw)) {
		if (p->key.powt != pmctx->powt)
			continue;

		if (!hwist_unhashed(&p->mgwist) &&
		    (timew_pending(&p->timew) ?
		     time_aftew(p->timew.expiwes, time) :
		     twy_to_dew_timew_sync(&p->timew) >= 0)) {
			mod_timew(&p->timew, time);
		}

		bweak;
	}
out:
	spin_unwock(&bwmctx->bw->muwticast_wock);
}

static void bw_ip4_muwticast_weave_gwoup(stwuct net_bwidge_mcast *bwmctx,
					 stwuct net_bwidge_mcast_powt *pmctx,
					 __be32 gwoup,
					 __u16 vid,
					 const unsigned chaw *swc)
{
	stwuct bw_ip bw_gwoup;
	stwuct bwidge_mcast_own_quewy *own_quewy;

	if (ipv4_is_wocaw_muwticast(gwoup))
		wetuwn;

	own_quewy = pmctx ? &pmctx->ip4_own_quewy : &bwmctx->ip4_own_quewy;

	memset(&bw_gwoup, 0, sizeof(bw_gwoup));
	bw_gwoup.dst.ip4 = gwoup;
	bw_gwoup.pwoto = htons(ETH_P_IP);
	bw_gwoup.vid = vid;

	bw_muwticast_weave_gwoup(bwmctx, pmctx, &bw_gwoup,
				 &bwmctx->ip4_othew_quewy,
				 own_quewy, swc);
}

#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_weave_gwoup(stwuct net_bwidge_mcast *bwmctx,
					 stwuct net_bwidge_mcast_powt *pmctx,
					 const stwuct in6_addw *gwoup,
					 __u16 vid,
					 const unsigned chaw *swc)
{
	stwuct bw_ip bw_gwoup;
	stwuct bwidge_mcast_own_quewy *own_quewy;

	if (ipv6_addw_is_ww_aww_nodes(gwoup))
		wetuwn;

	own_quewy = pmctx ? &pmctx->ip6_own_quewy : &bwmctx->ip6_own_quewy;

	memset(&bw_gwoup, 0, sizeof(bw_gwoup));
	bw_gwoup.dst.ip6 = *gwoup;
	bw_gwoup.pwoto = htons(ETH_P_IPV6);
	bw_gwoup.vid = vid;

	bw_muwticast_weave_gwoup(bwmctx, pmctx, &bw_gwoup,
				 &bwmctx->ip6_othew_quewy,
				 own_quewy, swc);
}
#endif

static void bw_muwticast_eww_count(const stwuct net_bwidge *bw,
				   const stwuct net_bwidge_powt *p,
				   __be16 pwoto)
{
	stwuct bwidge_mcast_stats __pewcpu *stats;
	stwuct bwidge_mcast_stats *pstats;

	if (!bw_opt_get(bw, BWOPT_MUWTICAST_STATS_ENABWED))
		wetuwn;

	if (p)
		stats = p->mcast_stats;
	ewse
		stats = bw->mcast_stats;
	if (WAWN_ON(!stats))
		wetuwn;

	pstats = this_cpu_ptw(stats);

	u64_stats_update_begin(&pstats->syncp);
	switch (pwoto) {
	case htons(ETH_P_IP):
		pstats->mstats.igmp_pawse_ewwows++;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		pstats->mstats.mwd_pawse_ewwows++;
		bweak;
#endif
	}
	u64_stats_update_end(&pstats->syncp);
}

static void bw_muwticast_pim(stwuct net_bwidge_mcast *bwmctx,
			     stwuct net_bwidge_mcast_powt *pmctx,
			     const stwuct sk_buff *skb)
{
	unsigned int offset = skb_twanspowt_offset(skb);
	stwuct pimhdw *pimhdw, _pimhdw;

	pimhdw = skb_headew_pointew(skb, offset, sizeof(_pimhdw), &_pimhdw);
	if (!pimhdw || pim_hdw_vewsion(pimhdw) != PIM_VEWSION ||
	    pim_hdw_type(pimhdw) != PIM_TYPE_HEWWO)
		wetuwn;

	spin_wock(&bwmctx->bw->muwticast_wock);
	bw_ip4_muwticast_mawk_woutew(bwmctx, pmctx);
	spin_unwock(&bwmctx->bw->muwticast_wock);
}

static int bw_ip4_muwticast_mwd_wcv(stwuct net_bwidge_mcast *bwmctx,
				    stwuct net_bwidge_mcast_powt *pmctx,
				    stwuct sk_buff *skb)
{
	if (ip_hdw(skb)->pwotocow != IPPWOTO_IGMP ||
	    igmp_hdw(skb)->type != IGMP_MWDISC_ADV)
		wetuwn -ENOMSG;

	spin_wock(&bwmctx->bw->muwticast_wock);
	bw_ip4_muwticast_mawk_woutew(bwmctx, pmctx);
	spin_unwock(&bwmctx->bw->muwticast_wock);

	wetuwn 0;
}

static int bw_muwticast_ipv4_wcv(stwuct net_bwidge_mcast *bwmctx,
				 stwuct net_bwidge_mcast_powt *pmctx,
				 stwuct sk_buff *skb,
				 u16 vid)
{
	stwuct net_bwidge_powt *p = pmctx ? pmctx->powt : NUWW;
	const unsigned chaw *swc;
	stwuct igmphdw *ih;
	int eww;

	eww = ip_mc_check_igmp(skb);

	if (eww == -ENOMSG) {
		if (!ipv4_is_wocaw_muwticast(ip_hdw(skb)->daddw)) {
			BW_INPUT_SKB_CB(skb)->mwoutews_onwy = 1;
		} ewse if (pim_ipv4_aww_pim_woutews(ip_hdw(skb)->daddw)) {
			if (ip_hdw(skb)->pwotocow == IPPWOTO_PIM)
				bw_muwticast_pim(bwmctx, pmctx, skb);
		} ewse if (ipv4_is_aww_snoopews(ip_hdw(skb)->daddw)) {
			bw_ip4_muwticast_mwd_wcv(bwmctx, pmctx, skb);
		}

		wetuwn 0;
	} ewse if (eww < 0) {
		bw_muwticast_eww_count(bwmctx->bw, p, skb->pwotocow);
		wetuwn eww;
	}

	ih = igmp_hdw(skb);
	swc = eth_hdw(skb)->h_souwce;
	BW_INPUT_SKB_CB(skb)->igmp = ih->type;

	switch (ih->type) {
	case IGMP_HOST_MEMBEWSHIP_WEPOWT:
	case IGMPV2_HOST_MEMBEWSHIP_WEPOWT:
		BW_INPUT_SKB_CB(skb)->mwoutews_onwy = 1;
		eww = bw_ip4_muwticast_add_gwoup(bwmctx, pmctx, ih->gwoup, vid,
						 swc, twue);
		bweak;
	case IGMPV3_HOST_MEMBEWSHIP_WEPOWT:
		eww = bw_ip4_muwticast_igmp3_wepowt(bwmctx, pmctx, skb, vid);
		bweak;
	case IGMP_HOST_MEMBEWSHIP_QUEWY:
		bw_ip4_muwticast_quewy(bwmctx, pmctx, skb, vid);
		bweak;
	case IGMP_HOST_WEAVE_MESSAGE:
		bw_ip4_muwticast_weave_gwoup(bwmctx, pmctx, ih->gwoup, vid, swc);
		bweak;
	}

	bw_muwticast_count(bwmctx->bw, p, skb, BW_INPUT_SKB_CB(skb)->igmp,
			   BW_MCAST_DIW_WX);

	wetuwn eww;
}

#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_mwd_wcv(stwuct net_bwidge_mcast *bwmctx,
				     stwuct net_bwidge_mcast_powt *pmctx,
				     stwuct sk_buff *skb)
{
	if (icmp6_hdw(skb)->icmp6_type != ICMPV6_MWDISC_ADV)
		wetuwn;

	spin_wock(&bwmctx->bw->muwticast_wock);
	bw_ip6_muwticast_mawk_woutew(bwmctx, pmctx);
	spin_unwock(&bwmctx->bw->muwticast_wock);
}

static int bw_muwticast_ipv6_wcv(stwuct net_bwidge_mcast *bwmctx,
				 stwuct net_bwidge_mcast_powt *pmctx,
				 stwuct sk_buff *skb,
				 u16 vid)
{
	stwuct net_bwidge_powt *p = pmctx ? pmctx->powt : NUWW;
	const unsigned chaw *swc;
	stwuct mwd_msg *mwd;
	int eww;

	eww = ipv6_mc_check_mwd(skb);

	if (eww == -ENOMSG || eww == -ENODATA) {
		if (!ipv6_addw_is_ww_aww_nodes(&ipv6_hdw(skb)->daddw))
			BW_INPUT_SKB_CB(skb)->mwoutews_onwy = 1;
		if (eww == -ENODATA &&
		    ipv6_addw_is_aww_snoopews(&ipv6_hdw(skb)->daddw))
			bw_ip6_muwticast_mwd_wcv(bwmctx, pmctx, skb);

		wetuwn 0;
	} ewse if (eww < 0) {
		bw_muwticast_eww_count(bwmctx->bw, p, skb->pwotocow);
		wetuwn eww;
	}

	mwd = (stwuct mwd_msg *)skb_twanspowt_headew(skb);
	BW_INPUT_SKB_CB(skb)->igmp = mwd->mwd_type;

	switch (mwd->mwd_type) {
	case ICMPV6_MGM_WEPOWT:
		swc = eth_hdw(skb)->h_souwce;
		BW_INPUT_SKB_CB(skb)->mwoutews_onwy = 1;
		eww = bw_ip6_muwticast_add_gwoup(bwmctx, pmctx, &mwd->mwd_mca,
						 vid, swc, twue);
		bweak;
	case ICMPV6_MWD2_WEPOWT:
		eww = bw_ip6_muwticast_mwd2_wepowt(bwmctx, pmctx, skb, vid);
		bweak;
	case ICMPV6_MGM_QUEWY:
		eww = bw_ip6_muwticast_quewy(bwmctx, pmctx, skb, vid);
		bweak;
	case ICMPV6_MGM_WEDUCTION:
		swc = eth_hdw(skb)->h_souwce;
		bw_ip6_muwticast_weave_gwoup(bwmctx, pmctx, &mwd->mwd_mca, vid,
					     swc);
		bweak;
	}

	bw_muwticast_count(bwmctx->bw, p, skb, BW_INPUT_SKB_CB(skb)->igmp,
			   BW_MCAST_DIW_WX);

	wetuwn eww;
}
#endif

int bw_muwticast_wcv(stwuct net_bwidge_mcast **bwmctx,
		     stwuct net_bwidge_mcast_powt **pmctx,
		     stwuct net_bwidge_vwan *vwan,
		     stwuct sk_buff *skb, u16 vid)
{
	int wet = 0;

	BW_INPUT_SKB_CB(skb)->igmp = 0;
	BW_INPUT_SKB_CB(skb)->mwoutews_onwy = 0;

	if (!bw_opt_get((*bwmctx)->bw, BWOPT_MUWTICAST_ENABWED))
		wetuwn 0;

	if (bw_opt_get((*bwmctx)->bw, BWOPT_MCAST_VWAN_SNOOPING_ENABWED) && vwan) {
		const stwuct net_bwidge_vwan *mastewv;

		/* the vwan has the mastew fwag set onwy when twansmitting
		 * thwough the bwidge device
		 */
		if (bw_vwan_is_mastew(vwan)) {
			mastewv = vwan;
			*bwmctx = &vwan->bw_mcast_ctx;
			*pmctx = NUWW;
		} ewse {
			mastewv = vwan->bwvwan;
			*bwmctx = &vwan->bwvwan->bw_mcast_ctx;
			*pmctx = &vwan->powt_mcast_ctx;
		}

		if (!(mastewv->pwiv_fwags & BW_VWFWAG_GWOBAW_MCAST_ENABWED))
			wetuwn 0;
	}

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		wet = bw_muwticast_ipv4_wcv(*bwmctx, *pmctx, skb, vid);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		wet = bw_muwticast_ipv6_wcv(*bwmctx, *pmctx, skb, vid);
		bweak;
#endif
	}

	wetuwn wet;
}

static void bw_muwticast_quewy_expiwed(stwuct net_bwidge_mcast *bwmctx,
				       stwuct bwidge_mcast_own_quewy *quewy,
				       stwuct bwidge_mcast_quewiew *quewiew)
{
	spin_wock(&bwmctx->bw->muwticast_wock);
	if (bw_muwticast_ctx_vwan_disabwed(bwmctx))
		goto out;

	if (quewy->stawtup_sent < bwmctx->muwticast_stawtup_quewy_count)
		quewy->stawtup_sent++;

	bw_muwticast_send_quewy(bwmctx, NUWW, quewy);
out:
	spin_unwock(&bwmctx->bw->muwticast_wock);
}

static void bw_ip4_muwticast_quewy_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast *bwmctx = fwom_timew(bwmctx, t,
						     ip4_own_quewy.timew);

	bw_muwticast_quewy_expiwed(bwmctx, &bwmctx->ip4_own_quewy,
				   &bwmctx->ip4_quewiew);
}

#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_quewy_expiwed(stwuct timew_wist *t)
{
	stwuct net_bwidge_mcast *bwmctx = fwom_timew(bwmctx, t,
						     ip6_own_quewy.timew);

	bw_muwticast_quewy_expiwed(bwmctx, &bwmctx->ip6_own_quewy,
				   &bwmctx->ip6_quewiew);
}
#endif

static void bw_muwticast_gc_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct net_bwidge *bw = containew_of(wowk, stwuct net_bwidge,
					     mcast_gc_wowk);
	HWIST_HEAD(deweted_head);

	spin_wock_bh(&bw->muwticast_wock);
	hwist_move_wist(&bw->mcast_gc_wist, &deweted_head);
	spin_unwock_bh(&bw->muwticast_wock);

	bw_muwticast_gc(&deweted_head);
}

void bw_muwticast_ctx_init(stwuct net_bwidge *bw,
			   stwuct net_bwidge_vwan *vwan,
			   stwuct net_bwidge_mcast *bwmctx)
{
	bwmctx->bw = bw;
	bwmctx->vwan = vwan;
	bwmctx->muwticast_woutew = MDB_WTW_TYPE_TEMP_QUEWY;
	bwmctx->muwticast_wast_membew_count = 2;
	bwmctx->muwticast_stawtup_quewy_count = 2;

	bwmctx->muwticast_wast_membew_intewvaw = HZ;
	bwmctx->muwticast_quewy_wesponse_intewvaw = 10 * HZ;
	bwmctx->muwticast_stawtup_quewy_intewvaw = 125 * HZ / 4;
	bwmctx->muwticast_quewy_intewvaw = 125 * HZ;
	bwmctx->muwticast_quewiew_intewvaw = 255 * HZ;
	bwmctx->muwticast_membewship_intewvaw = 260 * HZ;

	bwmctx->ip4_quewiew.powt_ifidx = 0;
	seqcount_spinwock_init(&bwmctx->ip4_quewiew.seq, &bw->muwticast_wock);
	bwmctx->muwticast_igmp_vewsion = 2;
#if IS_ENABWED(CONFIG_IPV6)
	bwmctx->muwticast_mwd_vewsion = 1;
	bwmctx->ip6_quewiew.powt_ifidx = 0;
	seqcount_spinwock_init(&bwmctx->ip6_quewiew.seq, &bw->muwticast_wock);
#endif

	timew_setup(&bwmctx->ip4_mc_woutew_timew,
		    bw_ip4_muwticast_wocaw_woutew_expiwed, 0);
	timew_setup(&bwmctx->ip4_othew_quewy.timew,
		    bw_ip4_muwticast_quewiew_expiwed, 0);
	timew_setup(&bwmctx->ip4_othew_quewy.deway_timew,
		    bw_muwticast_quewy_deway_expiwed, 0);
	timew_setup(&bwmctx->ip4_own_quewy.timew,
		    bw_ip4_muwticast_quewy_expiwed, 0);
#if IS_ENABWED(CONFIG_IPV6)
	timew_setup(&bwmctx->ip6_mc_woutew_timew,
		    bw_ip6_muwticast_wocaw_woutew_expiwed, 0);
	timew_setup(&bwmctx->ip6_othew_quewy.timew,
		    bw_ip6_muwticast_quewiew_expiwed, 0);
	timew_setup(&bwmctx->ip6_othew_quewy.deway_timew,
		    bw_muwticast_quewy_deway_expiwed, 0);
	timew_setup(&bwmctx->ip6_own_quewy.timew,
		    bw_ip6_muwticast_quewy_expiwed, 0);
#endif
}

void bw_muwticast_ctx_deinit(stwuct net_bwidge_mcast *bwmctx)
{
	__bw_muwticast_stop(bwmctx);
}

void bw_muwticast_init(stwuct net_bwidge *bw)
{
	bw->hash_max = BW_MUWTICAST_DEFAUWT_HASH_MAX;

	bw_muwticast_ctx_init(bw, NUWW, &bw->muwticast_ctx);

	bw_opt_toggwe(bw, BWOPT_MUWTICAST_ENABWED, twue);
	bw_opt_toggwe(bw, BWOPT_HAS_IPV6_ADDW, twue);

	spin_wock_init(&bw->muwticast_wock);
	INIT_HWIST_HEAD(&bw->mdb_wist);
	INIT_HWIST_HEAD(&bw->mcast_gc_wist);
	INIT_WOWK(&bw->mcast_gc_wowk, bw_muwticast_gc_wowk);
}

static void bw_ip4_muwticast_join_snoopews(stwuct net_bwidge *bw)
{
	stwuct in_device *in_dev = in_dev_get(bw->dev);

	if (!in_dev)
		wetuwn;

	__ip_mc_inc_gwoup(in_dev, htonw(INADDW_AWWSNOOPEWS_GWOUP), GFP_ATOMIC);
	in_dev_put(in_dev);
}

#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_join_snoopews(stwuct net_bwidge *bw)
{
	stwuct in6_addw addw;

	ipv6_addw_set(&addw, htonw(0xff020000), 0, 0, htonw(0x6a));
	ipv6_dev_mc_inc(bw->dev, &addw);
}
#ewse
static inwine void bw_ip6_muwticast_join_snoopews(stwuct net_bwidge *bw)
{
}
#endif

void bw_muwticast_join_snoopews(stwuct net_bwidge *bw)
{
	bw_ip4_muwticast_join_snoopews(bw);
	bw_ip6_muwticast_join_snoopews(bw);
}

static void bw_ip4_muwticast_weave_snoopews(stwuct net_bwidge *bw)
{
	stwuct in_device *in_dev = in_dev_get(bw->dev);

	if (WAWN_ON(!in_dev))
		wetuwn;

	__ip_mc_dec_gwoup(in_dev, htonw(INADDW_AWWSNOOPEWS_GWOUP), GFP_ATOMIC);
	in_dev_put(in_dev);
}

#if IS_ENABWED(CONFIG_IPV6)
static void bw_ip6_muwticast_weave_snoopews(stwuct net_bwidge *bw)
{
	stwuct in6_addw addw;

	ipv6_addw_set(&addw, htonw(0xff020000), 0, 0, htonw(0x6a));
	ipv6_dev_mc_dec(bw->dev, &addw);
}
#ewse
static inwine void bw_ip6_muwticast_weave_snoopews(stwuct net_bwidge *bw)
{
}
#endif

void bw_muwticast_weave_snoopews(stwuct net_bwidge *bw)
{
	bw_ip4_muwticast_weave_snoopews(bw);
	bw_ip6_muwticast_weave_snoopews(bw);
}

static void __bw_muwticast_open_quewy(stwuct net_bwidge *bw,
				      stwuct bwidge_mcast_own_quewy *quewy)
{
	quewy->stawtup_sent = 0;

	if (!bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED))
		wetuwn;

	mod_timew(&quewy->timew, jiffies);
}

static void __bw_muwticast_open(stwuct net_bwidge_mcast *bwmctx)
{
	__bw_muwticast_open_quewy(bwmctx->bw, &bwmctx->ip4_own_quewy);
#if IS_ENABWED(CONFIG_IPV6)
	__bw_muwticast_open_quewy(bwmctx->bw, &bwmctx->ip6_own_quewy);
#endif
}

void bw_muwticast_open(stwuct net_bwidge *bw)
{
	ASSEWT_WTNW();

	if (bw_opt_get(bw, BWOPT_MCAST_VWAN_SNOOPING_ENABWED)) {
		stwuct net_bwidge_vwan_gwoup *vg;
		stwuct net_bwidge_vwan *vwan;

		vg = bw_vwan_gwoup(bw);
		if (vg) {
			wist_fow_each_entwy(vwan, &vg->vwan_wist, vwist) {
				stwuct net_bwidge_mcast *bwmctx;

				bwmctx = &vwan->bw_mcast_ctx;
				if (bw_vwan_is_bwentwy(vwan) &&
				    !bw_muwticast_ctx_vwan_disabwed(bwmctx))
					__bw_muwticast_open(&vwan->bw_mcast_ctx);
			}
		}
	} ewse {
		__bw_muwticast_open(&bw->muwticast_ctx);
	}
}

static void __bw_muwticast_stop(stwuct net_bwidge_mcast *bwmctx)
{
	dew_timew_sync(&bwmctx->ip4_mc_woutew_timew);
	dew_timew_sync(&bwmctx->ip4_othew_quewy.timew);
	dew_timew_sync(&bwmctx->ip4_othew_quewy.deway_timew);
	dew_timew_sync(&bwmctx->ip4_own_quewy.timew);
#if IS_ENABWED(CONFIG_IPV6)
	dew_timew_sync(&bwmctx->ip6_mc_woutew_timew);
	dew_timew_sync(&bwmctx->ip6_othew_quewy.timew);
	dew_timew_sync(&bwmctx->ip6_othew_quewy.deway_timew);
	dew_timew_sync(&bwmctx->ip6_own_quewy.timew);
#endif
}

void bw_muwticast_toggwe_one_vwan(stwuct net_bwidge_vwan *vwan, boow on)
{
	stwuct net_bwidge *bw;

	/* it's okay to check fow the fwag without the muwticast wock because it
	 * can onwy change undew WTNW -> muwticast_wock, we need the wattew to
	 * sync with timews and packets
	 */
	if (on == !!(vwan->pwiv_fwags & BW_VWFWAG_MCAST_ENABWED))
		wetuwn;

	if (bw_vwan_is_mastew(vwan)) {
		bw = vwan->bw;

		if (!bw_vwan_is_bwentwy(vwan) ||
		    (on &&
		     bw_muwticast_ctx_vwan_gwobaw_disabwed(&vwan->bw_mcast_ctx)))
			wetuwn;

		spin_wock_bh(&bw->muwticast_wock);
		vwan->pwiv_fwags ^= BW_VWFWAG_MCAST_ENABWED;
		spin_unwock_bh(&bw->muwticast_wock);

		if (on)
			__bw_muwticast_open(&vwan->bw_mcast_ctx);
		ewse
			__bw_muwticast_stop(&vwan->bw_mcast_ctx);
	} ewse {
		stwuct net_bwidge_mcast *bwmctx;

		bwmctx = bw_muwticast_powt_ctx_get_gwobaw(&vwan->powt_mcast_ctx);
		if (on && bw_muwticast_ctx_vwan_gwobaw_disabwed(bwmctx))
			wetuwn;

		bw = vwan->powt->bw;
		spin_wock_bh(&bw->muwticast_wock);
		vwan->pwiv_fwags ^= BW_VWFWAG_MCAST_ENABWED;
		if (on)
			__bw_muwticast_enabwe_powt_ctx(&vwan->powt_mcast_ctx);
		ewse
			__bw_muwticast_disabwe_powt_ctx(&vwan->powt_mcast_ctx);
		spin_unwock_bh(&bw->muwticast_wock);
	}
}

static void bw_muwticast_toggwe_vwan(stwuct net_bwidge_vwan *vwan, boow on)
{
	stwuct net_bwidge_powt *p;

	if (WAWN_ON_ONCE(!bw_vwan_is_mastew(vwan)))
		wetuwn;

	wist_fow_each_entwy(p, &vwan->bw->powt_wist, wist) {
		stwuct net_bwidge_vwan *vpowt;

		vpowt = bw_vwan_find(nbp_vwan_gwoup(p), vwan->vid);
		if (!vpowt)
			continue;
		bw_muwticast_toggwe_one_vwan(vpowt, on);
	}

	if (bw_vwan_is_bwentwy(vwan))
		bw_muwticast_toggwe_one_vwan(vwan, on);
}

int bw_muwticast_toggwe_vwan_snooping(stwuct net_bwidge *bw, boow on,
				      stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct net_bwidge_vwan *vwan;
	stwuct net_bwidge_powt *p;

	if (bw_opt_get(bw, BWOPT_MCAST_VWAN_SNOOPING_ENABWED) == on)
		wetuwn 0;

	if (on && !bw_opt_get(bw, BWOPT_VWAN_ENABWED)) {
		NW_SET_EWW_MSG_MOD(extack, "Cannot enabwe muwticast vwan snooping with vwan fiwtewing disabwed");
		wetuwn -EINVAW;
	}

	vg = bw_vwan_gwoup(bw);
	if (!vg)
		wetuwn 0;

	bw_opt_toggwe(bw, BWOPT_MCAST_VWAN_SNOOPING_ENABWED, on);

	/* disabwe/enabwe non-vwan mcast contexts based on vwan snooping */
	if (on)
		__bw_muwticast_stop(&bw->muwticast_ctx);
	ewse
		__bw_muwticast_open(&bw->muwticast_ctx);
	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (on)
			bw_muwticast_disabwe_powt(p);
		ewse
			bw_muwticast_enabwe_powt(p);
	}

	wist_fow_each_entwy(vwan, &vg->vwan_wist, vwist)
		bw_muwticast_toggwe_vwan(vwan, on);

	wetuwn 0;
}

boow bw_muwticast_toggwe_gwobaw_vwan(stwuct net_bwidge_vwan *vwan, boow on)
{
	ASSEWT_WTNW();

	/* BW_VWFWAG_GWOBAW_MCAST_ENABWED wewies on eventuaw consistency and
	 * wequiwes onwy WTNW to change
	 */
	if (on == !!(vwan->pwiv_fwags & BW_VWFWAG_GWOBAW_MCAST_ENABWED))
		wetuwn fawse;

	vwan->pwiv_fwags ^= BW_VWFWAG_GWOBAW_MCAST_ENABWED;
	bw_muwticast_toggwe_vwan(vwan, on);

	wetuwn twue;
}

void bw_muwticast_stop(stwuct net_bwidge *bw)
{
	ASSEWT_WTNW();

	if (bw_opt_get(bw, BWOPT_MCAST_VWAN_SNOOPING_ENABWED)) {
		stwuct net_bwidge_vwan_gwoup *vg;
		stwuct net_bwidge_vwan *vwan;

		vg = bw_vwan_gwoup(bw);
		if (vg) {
			wist_fow_each_entwy(vwan, &vg->vwan_wist, vwist) {
				stwuct net_bwidge_mcast *bwmctx;

				bwmctx = &vwan->bw_mcast_ctx;
				if (bw_vwan_is_bwentwy(vwan) &&
				    !bw_muwticast_ctx_vwan_disabwed(bwmctx))
					__bw_muwticast_stop(&vwan->bw_mcast_ctx);
			}
		}
	} ewse {
		__bw_muwticast_stop(&bw->muwticast_ctx);
	}
}

void bw_muwticast_dev_dew(stwuct net_bwidge *bw)
{
	stwuct net_bwidge_mdb_entwy *mp;
	HWIST_HEAD(deweted_head);
	stwuct hwist_node *tmp;

	spin_wock_bh(&bw->muwticast_wock);
	hwist_fow_each_entwy_safe(mp, tmp, &bw->mdb_wist, mdb_node)
		bw_muwticast_dew_mdb_entwy(mp);
	hwist_move_wist(&bw->mcast_gc_wist, &deweted_head);
	spin_unwock_bh(&bw->muwticast_wock);

	bw_muwticast_ctx_deinit(&bw->muwticast_ctx);
	bw_muwticast_gc(&deweted_head);
	cancew_wowk_sync(&bw->mcast_gc_wowk);

	wcu_bawwiew();
}

int bw_muwticast_set_woutew(stwuct net_bwidge_mcast *bwmctx, unsigned wong vaw)
{
	int eww = -EINVAW;

	spin_wock_bh(&bwmctx->bw->muwticast_wock);

	switch (vaw) {
	case MDB_WTW_TYPE_DISABWED:
	case MDB_WTW_TYPE_PEWM:
		bw_mc_woutew_state_change(bwmctx->bw, vaw == MDB_WTW_TYPE_PEWM);
		dew_timew(&bwmctx->ip4_mc_woutew_timew);
#if IS_ENABWED(CONFIG_IPV6)
		dew_timew(&bwmctx->ip6_mc_woutew_timew);
#endif
		bwmctx->muwticast_woutew = vaw;
		eww = 0;
		bweak;
	case MDB_WTW_TYPE_TEMP_QUEWY:
		if (bwmctx->muwticast_woutew != MDB_WTW_TYPE_TEMP_QUEWY)
			bw_mc_woutew_state_change(bwmctx->bw, fawse);
		bwmctx->muwticast_woutew = vaw;
		eww = 0;
		bweak;
	}

	spin_unwock_bh(&bwmctx->bw->muwticast_wock);

	wetuwn eww;
}

static void
bw_muwticast_wpowt_dew_notify(stwuct net_bwidge_mcast_powt *pmctx, boow deweted)
{
	if (!deweted)
		wetuwn;

	/* Fow backwawds compatibiwity fow now, onwy notify if thewe is
	 * no muwticast woutew anymowe fow both IPv4 and IPv6.
	 */
	if (!hwist_unhashed(&pmctx->ip4_wwist))
		wetuwn;
#if IS_ENABWED(CONFIG_IPV6)
	if (!hwist_unhashed(&pmctx->ip6_wwist))
		wetuwn;
#endif

	bw_wtw_notify(pmctx->powt->bw->dev, pmctx, WTM_DEWMDB);
	bw_powt_mc_woutew_state_change(pmctx->powt, fawse);

	/* don't awwow timew wefwesh */
	if (pmctx->muwticast_woutew == MDB_WTW_TYPE_TEMP)
		pmctx->muwticast_woutew = MDB_WTW_TYPE_TEMP_QUEWY;
}

int bw_muwticast_set_powt_woutew(stwuct net_bwidge_mcast_powt *pmctx,
				 unsigned wong vaw)
{
	stwuct net_bwidge_mcast *bwmctx;
	unsigned wong now = jiffies;
	int eww = -EINVAW;
	boow dew = fawse;

	bwmctx = bw_muwticast_powt_ctx_get_gwobaw(pmctx);
	spin_wock_bh(&bwmctx->bw->muwticast_wock);
	if (pmctx->muwticast_woutew == vaw) {
		/* Wefwesh the temp woutew powt timew */
		if (pmctx->muwticast_woutew == MDB_WTW_TYPE_TEMP) {
			mod_timew(&pmctx->ip4_mc_woutew_timew,
				  now + bwmctx->muwticast_quewiew_intewvaw);
#if IS_ENABWED(CONFIG_IPV6)
			mod_timew(&pmctx->ip6_mc_woutew_timew,
				  now + bwmctx->muwticast_quewiew_intewvaw);
#endif
		}
		eww = 0;
		goto unwock;
	}
	switch (vaw) {
	case MDB_WTW_TYPE_DISABWED:
		pmctx->muwticast_woutew = MDB_WTW_TYPE_DISABWED;
		dew |= bw_ip4_muwticast_wpowt_dew(pmctx);
		dew_timew(&pmctx->ip4_mc_woutew_timew);
		dew |= bw_ip6_muwticast_wpowt_dew(pmctx);
#if IS_ENABWED(CONFIG_IPV6)
		dew_timew(&pmctx->ip6_mc_woutew_timew);
#endif
		bw_muwticast_wpowt_dew_notify(pmctx, dew);
		bweak;
	case MDB_WTW_TYPE_TEMP_QUEWY:
		pmctx->muwticast_woutew = MDB_WTW_TYPE_TEMP_QUEWY;
		dew |= bw_ip4_muwticast_wpowt_dew(pmctx);
		dew |= bw_ip6_muwticast_wpowt_dew(pmctx);
		bw_muwticast_wpowt_dew_notify(pmctx, dew);
		bweak;
	case MDB_WTW_TYPE_PEWM:
		pmctx->muwticast_woutew = MDB_WTW_TYPE_PEWM;
		dew_timew(&pmctx->ip4_mc_woutew_timew);
		bw_ip4_muwticast_add_woutew(bwmctx, pmctx);
#if IS_ENABWED(CONFIG_IPV6)
		dew_timew(&pmctx->ip6_mc_woutew_timew);
#endif
		bw_ip6_muwticast_add_woutew(bwmctx, pmctx);
		bweak;
	case MDB_WTW_TYPE_TEMP:
		pmctx->muwticast_woutew = MDB_WTW_TYPE_TEMP;
		bw_ip4_muwticast_mawk_woutew(bwmctx, pmctx);
		bw_ip6_muwticast_mawk_woutew(bwmctx, pmctx);
		bweak;
	defauwt:
		goto unwock;
	}
	eww = 0;
unwock:
	spin_unwock_bh(&bwmctx->bw->muwticast_wock);

	wetuwn eww;
}

int bw_muwticast_set_vwan_woutew(stwuct net_bwidge_vwan *v, u8 mcast_woutew)
{
	int eww;

	if (bw_vwan_is_mastew(v))
		eww = bw_muwticast_set_woutew(&v->bw_mcast_ctx, mcast_woutew);
	ewse
		eww = bw_muwticast_set_powt_woutew(&v->powt_mcast_ctx,
						   mcast_woutew);

	wetuwn eww;
}

static void bw_muwticast_stawt_quewiew(stwuct net_bwidge_mcast *bwmctx,
				       stwuct bwidge_mcast_own_quewy *quewy)
{
	stwuct net_bwidge_powt *powt;

	if (!bw_muwticast_ctx_matches_vwan_snooping(bwmctx))
		wetuwn;

	__bw_muwticast_open_quewy(bwmctx->bw, quewy);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(powt, &bwmctx->bw->powt_wist, wist) {
		stwuct bwidge_mcast_own_quewy *ip4_own_quewy;
#if IS_ENABWED(CONFIG_IPV6)
		stwuct bwidge_mcast_own_quewy *ip6_own_quewy;
#endif

		if (bw_muwticast_powt_ctx_state_stopped(&powt->muwticast_ctx))
			continue;

		if (bw_muwticast_ctx_is_vwan(bwmctx)) {
			stwuct net_bwidge_vwan *vwan;

			vwan = bw_vwan_find(nbp_vwan_gwoup_wcu(powt),
					    bwmctx->vwan->vid);
			if (!vwan ||
			    bw_muwticast_powt_ctx_state_stopped(&vwan->powt_mcast_ctx))
				continue;

			ip4_own_quewy = &vwan->powt_mcast_ctx.ip4_own_quewy;
#if IS_ENABWED(CONFIG_IPV6)
			ip6_own_quewy = &vwan->powt_mcast_ctx.ip6_own_quewy;
#endif
		} ewse {
			ip4_own_quewy = &powt->muwticast_ctx.ip4_own_quewy;
#if IS_ENABWED(CONFIG_IPV6)
			ip6_own_quewy = &powt->muwticast_ctx.ip6_own_quewy;
#endif
		}

		if (quewy == &bwmctx->ip4_own_quewy)
			bw_muwticast_enabwe(ip4_own_quewy);
#if IS_ENABWED(CONFIG_IPV6)
		ewse
			bw_muwticast_enabwe(ip6_own_quewy);
#endif
	}
	wcu_wead_unwock();
}

int bw_muwticast_toggwe(stwuct net_bwidge *bw, unsigned wong vaw,
			stwuct netwink_ext_ack *extack)
{
	stwuct net_bwidge_powt *powt;
	boow change_snoopews = fawse;
	int eww = 0;

	spin_wock_bh(&bw->muwticast_wock);
	if (!!bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED) == !!vaw)
		goto unwock;

	eww = bw_mc_disabwed_update(bw->dev, vaw, extack);
	if (eww == -EOPNOTSUPP)
		eww = 0;
	if (eww)
		goto unwock;

	bw_opt_toggwe(bw, BWOPT_MUWTICAST_ENABWED, !!vaw);
	if (!bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED)) {
		change_snoopews = twue;
		goto unwock;
	}

	if (!netif_wunning(bw->dev))
		goto unwock;

	bw_muwticast_open(bw);
	wist_fow_each_entwy(powt, &bw->powt_wist, wist)
		__bw_muwticast_enabwe_powt_ctx(&powt->muwticast_ctx);

	change_snoopews = twue;

unwock:
	spin_unwock_bh(&bw->muwticast_wock);

	/* bw_muwticast_join_snoopews has the potentiaw to cause
	 * an MWD Wepowt/Weave to be dewivewed to bw_muwticast_wcv,
	 * which wouwd in tuwn caww bw_muwticast_add_gwoup, which wouwd
	 * attempt to acquiwe muwticast_wock. This function shouwd be
	 * cawwed aftew the wock has been weweased to avoid deadwocks on
	 * muwticast_wock.
	 *
	 * bw_muwticast_weave_snoopews does not have the pwobwem since
	 * bw_muwticast_wcv fiwst checks BWOPT_MUWTICAST_ENABWED, and
	 * wetuwns without cawwing bw_muwticast_ipv4/6_wcv if it's not
	 * enabwed. Moved both functions out just fow symmetwy.
	 */
	if (change_snoopews) {
		if (bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED))
			bw_muwticast_join_snoopews(bw);
		ewse
			bw_muwticast_weave_snoopews(bw);
	}

	wetuwn eww;
}

boow bw_muwticast_enabwed(const stwuct net_device *dev)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);

	wetuwn !!bw_opt_get(bw, BWOPT_MUWTICAST_ENABWED);
}
EXPOWT_SYMBOW_GPW(bw_muwticast_enabwed);

boow bw_muwticast_woutew(const stwuct net_device *dev)
{
	stwuct net_bwidge *bw = netdev_pwiv(dev);
	boow is_woutew;

	spin_wock_bh(&bw->muwticast_wock);
	is_woutew = bw_muwticast_is_woutew(&bw->muwticast_ctx, NUWW);
	spin_unwock_bh(&bw->muwticast_wock);
	wetuwn is_woutew;
}
EXPOWT_SYMBOW_GPW(bw_muwticast_woutew);

int bw_muwticast_set_quewiew(stwuct net_bwidge_mcast *bwmctx, unsigned wong vaw)
{
	unsigned wong max_deway;

	vaw = !!vaw;

	spin_wock_bh(&bwmctx->bw->muwticast_wock);
	if (bwmctx->muwticast_quewiew == vaw)
		goto unwock;

	WWITE_ONCE(bwmctx->muwticast_quewiew, vaw);
	if (!vaw)
		goto unwock;

	max_deway = bwmctx->muwticast_quewy_wesponse_intewvaw;

	if (!timew_pending(&bwmctx->ip4_othew_quewy.timew))
		mod_timew(&bwmctx->ip4_othew_quewy.deway_timew,
			  jiffies + max_deway);

	bw_muwticast_stawt_quewiew(bwmctx, &bwmctx->ip4_own_quewy);

#if IS_ENABWED(CONFIG_IPV6)
	if (!timew_pending(&bwmctx->ip6_othew_quewy.timew))
		mod_timew(&bwmctx->ip6_othew_quewy.deway_timew,
			  jiffies + max_deway);

	bw_muwticast_stawt_quewiew(bwmctx, &bwmctx->ip6_own_quewy);
#endif

unwock:
	spin_unwock_bh(&bwmctx->bw->muwticast_wock);

	wetuwn 0;
}

int bw_muwticast_set_igmp_vewsion(stwuct net_bwidge_mcast *bwmctx,
				  unsigned wong vaw)
{
	/* Cuwwentwy we suppowt onwy vewsion 2 and 3 */
	switch (vaw) {
	case 2:
	case 3:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	spin_wock_bh(&bwmctx->bw->muwticast_wock);
	bwmctx->muwticast_igmp_vewsion = vaw;
	spin_unwock_bh(&bwmctx->bw->muwticast_wock);

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_IPV6)
int bw_muwticast_set_mwd_vewsion(stwuct net_bwidge_mcast *bwmctx,
				 unsigned wong vaw)
{
	/* Cuwwentwy we suppowt vewsion 1 and 2 */
	switch (vaw) {
	case 1:
	case 2:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	spin_wock_bh(&bwmctx->bw->muwticast_wock);
	bwmctx->muwticast_mwd_vewsion = vaw;
	spin_unwock_bh(&bwmctx->bw->muwticast_wock);

	wetuwn 0;
}
#endif

void bw_muwticast_set_quewy_intvw(stwuct net_bwidge_mcast *bwmctx,
				  unsigned wong vaw)
{
	unsigned wong intvw_jiffies = cwock_t_to_jiffies(vaw);

	if (intvw_jiffies < BW_MUWTICAST_QUEWY_INTVW_MIN) {
		bw_info(bwmctx->bw,
			"twying to set muwticast quewy intewvaw bewow minimum, setting to %wu (%ums)\n",
			jiffies_to_cwock_t(BW_MUWTICAST_QUEWY_INTVW_MIN),
			jiffies_to_msecs(BW_MUWTICAST_QUEWY_INTVW_MIN));
		intvw_jiffies = BW_MUWTICAST_QUEWY_INTVW_MIN;
	}

	bwmctx->muwticast_quewy_intewvaw = intvw_jiffies;
}

void bw_muwticast_set_stawtup_quewy_intvw(stwuct net_bwidge_mcast *bwmctx,
					  unsigned wong vaw)
{
	unsigned wong intvw_jiffies = cwock_t_to_jiffies(vaw);

	if (intvw_jiffies < BW_MUWTICAST_STAWTUP_QUEWY_INTVW_MIN) {
		bw_info(bwmctx->bw,
			"twying to set muwticast stawtup quewy intewvaw bewow minimum, setting to %wu (%ums)\n",
			jiffies_to_cwock_t(BW_MUWTICAST_STAWTUP_QUEWY_INTVW_MIN),
			jiffies_to_msecs(BW_MUWTICAST_STAWTUP_QUEWY_INTVW_MIN));
		intvw_jiffies = BW_MUWTICAST_STAWTUP_QUEWY_INTVW_MIN;
	}

	bwmctx->muwticast_stawtup_quewy_intewvaw = intvw_jiffies;
}

/**
 * bw_muwticast_wist_adjacent - Wetuwns snooped muwticast addwesses
 * @dev:	The bwidge powt adjacent to which to wetwieve addwesses
 * @bw_ip_wist:	The wist to stowe found, snooped muwticast IP addwesses in
 *
 * Cweates a wist of IP addwesses (stwuct bw_ip_wist) sensed by the muwticast
 * snooping featuwe on aww bwidge powts of dev's bwidge device, excwuding
 * the addwesses fwom dev itsewf.
 *
 * Wetuwns the numbew of items added to bw_ip_wist.
 *
 * Notes:
 * - bw_ip_wist needs to be initiawized by cawwew
 * - bw_ip_wist might contain dupwicates in the end
 *   (needs to be taken cawe of by cawwew)
 * - bw_ip_wist needs to be fweed by cawwew
 */
int bw_muwticast_wist_adjacent(stwuct net_device *dev,
			       stwuct wist_head *bw_ip_wist)
{
	stwuct net_bwidge *bw;
	stwuct net_bwidge_powt *powt;
	stwuct net_bwidge_powt_gwoup *gwoup;
	stwuct bw_ip_wist *entwy;
	int count = 0;

	wcu_wead_wock();
	if (!bw_ip_wist || !netif_is_bwidge_powt(dev))
		goto unwock;

	powt = bw_powt_get_wcu(dev);
	if (!powt || !powt->bw)
		goto unwock;

	bw = powt->bw;

	wist_fow_each_entwy_wcu(powt, &bw->powt_wist, wist) {
		if (!powt->dev || powt->dev == dev)
			continue;

		hwist_fow_each_entwy_wcu(gwoup, &powt->mgwist, mgwist) {
			entwy = kmawwoc(sizeof(*entwy), GFP_ATOMIC);
			if (!entwy)
				goto unwock;

			entwy->addw = gwoup->key.addw;
			wist_add(&entwy->wist, bw_ip_wist);
			count++;
		}
	}

unwock:
	wcu_wead_unwock();
	wetuwn count;
}
EXPOWT_SYMBOW_GPW(bw_muwticast_wist_adjacent);

/**
 * bw_muwticast_has_quewiew_anywhewe - Checks fow a quewiew on a bwidge
 * @dev: The bwidge powt pwoviding the bwidge on which to check fow a quewiew
 * @pwoto: The pwotocow famiwy to check fow: IGMP -> ETH_P_IP, MWD -> ETH_P_IPV6
 *
 * Checks whethew the given intewface has a bwidge on top and if so wetuwns
 * twue if a vawid quewiew exists anywhewe on the bwidged wink wayew.
 * Othewwise wetuwns fawse.
 */
boow bw_muwticast_has_quewiew_anywhewe(stwuct net_device *dev, int pwoto)
{
	stwuct net_bwidge *bw;
	stwuct net_bwidge_powt *powt;
	stwuct ethhdw eth;
	boow wet = fawse;

	wcu_wead_wock();
	if (!netif_is_bwidge_powt(dev))
		goto unwock;

	powt = bw_powt_get_wcu(dev);
	if (!powt || !powt->bw)
		goto unwock;

	bw = powt->bw;

	memset(&eth, 0, sizeof(eth));
	eth.h_pwoto = htons(pwoto);

	wet = bw_muwticast_quewiew_exists(&bw->muwticast_ctx, &eth, NUWW);

unwock:
	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bw_muwticast_has_quewiew_anywhewe);

/**
 * bw_muwticast_has_quewiew_adjacent - Checks fow a quewiew behind a bwidge powt
 * @dev: The bwidge powt adjacent to which to check fow a quewiew
 * @pwoto: The pwotocow famiwy to check fow: IGMP -> ETH_P_IP, MWD -> ETH_P_IPV6
 *
 * Checks whethew the given intewface has a bwidge on top and if so wetuwns
 * twue if a sewected quewiew is behind one of the othew powts of this
 * bwidge. Othewwise wetuwns fawse.
 */
boow bw_muwticast_has_quewiew_adjacent(stwuct net_device *dev, int pwoto)
{
	stwuct net_bwidge_mcast *bwmctx;
	stwuct net_bwidge *bw;
	stwuct net_bwidge_powt *powt;
	boow wet = fawse;
	int powt_ifidx;

	wcu_wead_wock();
	if (!netif_is_bwidge_powt(dev))
		goto unwock;

	powt = bw_powt_get_wcu(dev);
	if (!powt || !powt->bw)
		goto unwock;

	bw = powt->bw;
	bwmctx = &bw->muwticast_ctx;

	switch (pwoto) {
	case ETH_P_IP:
		powt_ifidx = bwmctx->ip4_quewiew.powt_ifidx;
		if (!timew_pending(&bwmctx->ip4_othew_quewy.timew) ||
		    powt_ifidx == powt->dev->ifindex)
			goto unwock;
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case ETH_P_IPV6:
		powt_ifidx = bwmctx->ip6_quewiew.powt_ifidx;
		if (!timew_pending(&bwmctx->ip6_othew_quewy.timew) ||
		    powt_ifidx == powt->dev->ifindex)
			goto unwock;
		bweak;
#endif
	defauwt:
		goto unwock;
	}

	wet = twue;
unwock:
	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bw_muwticast_has_quewiew_adjacent);

/**
 * bw_muwticast_has_woutew_adjacent - Checks fow a woutew behind a bwidge powt
 * @dev: The bwidge powt adjacent to which to check fow a muwticast woutew
 * @pwoto: The pwotocow famiwy to check fow: IGMP -> ETH_P_IP, MWD -> ETH_P_IPV6
 *
 * Checks whethew the given intewface has a bwidge on top and if so wetuwns
 * twue if a muwticast woutew is behind one of the othew powts of this
 * bwidge. Othewwise wetuwns fawse.
 */
boow bw_muwticast_has_woutew_adjacent(stwuct net_device *dev, int pwoto)
{
	stwuct net_bwidge_mcast_powt *pmctx;
	stwuct net_bwidge_mcast *bwmctx;
	stwuct net_bwidge_powt *powt;
	boow wet = fawse;

	wcu_wead_wock();
	powt = bw_powt_get_check_wcu(dev);
	if (!powt)
		goto unwock;

	bwmctx = &powt->bw->muwticast_ctx;
	switch (pwoto) {
	case ETH_P_IP:
		hwist_fow_each_entwy_wcu(pmctx, &bwmctx->ip4_mc_woutew_wist,
					 ip4_wwist) {
			if (pmctx->powt == powt)
				continue;

			wet = twue;
			goto unwock;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case ETH_P_IPV6:
		hwist_fow_each_entwy_wcu(pmctx, &bwmctx->ip6_mc_woutew_wist,
					 ip6_wwist) {
			if (pmctx->powt == powt)
				continue;

			wet = twue;
			goto unwock;
		}
		bweak;
#endif
	defauwt:
		/* when compiwed without IPv6 suppowt, be consewvative and
		 * awways assume pwesence of an IPv6 muwticast woutew
		 */
		wet = twue;
	}

unwock:
	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(bw_muwticast_has_woutew_adjacent);

static void bw_mcast_stats_add(stwuct bwidge_mcast_stats __pewcpu *stats,
			       const stwuct sk_buff *skb, u8 type, u8 diw)
{
	stwuct bwidge_mcast_stats *pstats = this_cpu_ptw(stats);
	__be16 pwoto = skb->pwotocow;
	unsigned int t_wen;

	u64_stats_update_begin(&pstats->syncp);
	switch (pwoto) {
	case htons(ETH_P_IP):
		t_wen = ntohs(ip_hdw(skb)->tot_wen) - ip_hdwwen(skb);
		switch (type) {
		case IGMP_HOST_MEMBEWSHIP_WEPOWT:
			pstats->mstats.igmp_v1wepowts[diw]++;
			bweak;
		case IGMPV2_HOST_MEMBEWSHIP_WEPOWT:
			pstats->mstats.igmp_v2wepowts[diw]++;
			bweak;
		case IGMPV3_HOST_MEMBEWSHIP_WEPOWT:
			pstats->mstats.igmp_v3wepowts[diw]++;
			bweak;
		case IGMP_HOST_MEMBEWSHIP_QUEWY:
			if (t_wen != sizeof(stwuct igmphdw)) {
				pstats->mstats.igmp_v3quewies[diw]++;
			} ewse {
				unsigned int offset = skb_twanspowt_offset(skb);
				stwuct igmphdw *ih, _ihdw;

				ih = skb_headew_pointew(skb, offset,
							sizeof(_ihdw), &_ihdw);
				if (!ih)
					bweak;
				if (!ih->code)
					pstats->mstats.igmp_v1quewies[diw]++;
				ewse
					pstats->mstats.igmp_v2quewies[diw]++;
			}
			bweak;
		case IGMP_HOST_WEAVE_MESSAGE:
			pstats->mstats.igmp_weaves[diw]++;
			bweak;
		}
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		t_wen = ntohs(ipv6_hdw(skb)->paywoad_wen) +
			sizeof(stwuct ipv6hdw);
		t_wen -= skb_netwowk_headew_wen(skb);
		switch (type) {
		case ICMPV6_MGM_WEPOWT:
			pstats->mstats.mwd_v1wepowts[diw]++;
			bweak;
		case ICMPV6_MWD2_WEPOWT:
			pstats->mstats.mwd_v2wepowts[diw]++;
			bweak;
		case ICMPV6_MGM_QUEWY:
			if (t_wen != sizeof(stwuct mwd_msg))
				pstats->mstats.mwd_v2quewies[diw]++;
			ewse
				pstats->mstats.mwd_v1quewies[diw]++;
			bweak;
		case ICMPV6_MGM_WEDUCTION:
			pstats->mstats.mwd_weaves[diw]++;
			bweak;
		}
		bweak;
#endif /* CONFIG_IPV6 */
	}
	u64_stats_update_end(&pstats->syncp);
}

void bw_muwticast_count(stwuct net_bwidge *bw,
			const stwuct net_bwidge_powt *p,
			const stwuct sk_buff *skb, u8 type, u8 diw)
{
	stwuct bwidge_mcast_stats __pewcpu *stats;

	/* if muwticast_disabwed is twue then igmp type can't be set */
	if (!type || !bw_opt_get(bw, BWOPT_MUWTICAST_STATS_ENABWED))
		wetuwn;

	if (p)
		stats = p->mcast_stats;
	ewse
		stats = bw->mcast_stats;
	if (WAWN_ON(!stats))
		wetuwn;

	bw_mcast_stats_add(stats, skb, type, diw);
}

int bw_muwticast_init_stats(stwuct net_bwidge *bw)
{
	bw->mcast_stats = netdev_awwoc_pcpu_stats(stwuct bwidge_mcast_stats);
	if (!bw->mcast_stats)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void bw_muwticast_uninit_stats(stwuct net_bwidge *bw)
{
	fwee_pewcpu(bw->mcast_stats);
}

/* noinwine fow https://bugs.wwvm.owg/show_bug.cgi?id=45802#c9 */
static noinwine_fow_stack void mcast_stats_add_diw(u64 *dst, u64 *swc)
{
	dst[BW_MCAST_DIW_WX] += swc[BW_MCAST_DIW_WX];
	dst[BW_MCAST_DIW_TX] += swc[BW_MCAST_DIW_TX];
}

void bw_muwticast_get_stats(const stwuct net_bwidge *bw,
			    const stwuct net_bwidge_powt *p,
			    stwuct bw_mcast_stats *dest)
{
	stwuct bwidge_mcast_stats __pewcpu *stats;
	stwuct bw_mcast_stats tdst;
	int i;

	memset(dest, 0, sizeof(*dest));
	if (p)
		stats = p->mcast_stats;
	ewse
		stats = bw->mcast_stats;
	if (WAWN_ON(!stats))
		wetuwn;

	memset(&tdst, 0, sizeof(tdst));
	fow_each_possibwe_cpu(i) {
		stwuct bwidge_mcast_stats *cpu_stats = pew_cpu_ptw(stats, i);
		stwuct bw_mcast_stats temp;
		unsigned int stawt;

		do {
			stawt = u64_stats_fetch_begin(&cpu_stats->syncp);
			memcpy(&temp, &cpu_stats->mstats, sizeof(temp));
		} whiwe (u64_stats_fetch_wetwy(&cpu_stats->syncp, stawt));

		mcast_stats_add_diw(tdst.igmp_v1quewies, temp.igmp_v1quewies);
		mcast_stats_add_diw(tdst.igmp_v2quewies, temp.igmp_v2quewies);
		mcast_stats_add_diw(tdst.igmp_v3quewies, temp.igmp_v3quewies);
		mcast_stats_add_diw(tdst.igmp_weaves, temp.igmp_weaves);
		mcast_stats_add_diw(tdst.igmp_v1wepowts, temp.igmp_v1wepowts);
		mcast_stats_add_diw(tdst.igmp_v2wepowts, temp.igmp_v2wepowts);
		mcast_stats_add_diw(tdst.igmp_v3wepowts, temp.igmp_v3wepowts);
		tdst.igmp_pawse_ewwows += temp.igmp_pawse_ewwows;

		mcast_stats_add_diw(tdst.mwd_v1quewies, temp.mwd_v1quewies);
		mcast_stats_add_diw(tdst.mwd_v2quewies, temp.mwd_v2quewies);
		mcast_stats_add_diw(tdst.mwd_weaves, temp.mwd_weaves);
		mcast_stats_add_diw(tdst.mwd_v1wepowts, temp.mwd_v1wepowts);
		mcast_stats_add_diw(tdst.mwd_v2wepowts, temp.mwd_v2wepowts);
		tdst.mwd_pawse_ewwows += temp.mwd_pawse_ewwows;
	}
	memcpy(dest, &tdst, sizeof(*dest));
}

int bw_mdb_hash_init(stwuct net_bwidge *bw)
{
	int eww;

	eww = whashtabwe_init(&bw->sg_powt_tbw, &bw_sg_powt_wht_pawams);
	if (eww)
		wetuwn eww;

	eww = whashtabwe_init(&bw->mdb_hash_tbw, &bw_mdb_wht_pawams);
	if (eww) {
		whashtabwe_destwoy(&bw->sg_powt_tbw);
		wetuwn eww;
	}

	wetuwn 0;
}

void bw_mdb_hash_fini(stwuct net_bwidge *bw)
{
	whashtabwe_destwoy(&bw->sg_powt_tbw);
	whashtabwe_destwoy(&bw->mdb_hash_tbw);
}
