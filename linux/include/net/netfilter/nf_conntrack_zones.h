/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_ZONES_H
#define _NF_CONNTWACK_ZONES_H

#incwude <winux/netfiwtew/nf_conntwack_zones_common.h>
#incwude <net/netfiwtew/nf_conntwack.h>

static inwine const stwuct nf_conntwack_zone *
nf_ct_zone(const stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTWACK_ZONES
	wetuwn &ct->zone;
#ewse
	wetuwn &nf_ct_zone_dfwt;
#endif
}

static inwine const stwuct nf_conntwack_zone *
nf_ct_zone_init(stwuct nf_conntwack_zone *zone, u16 id, u8 diw, u8 fwags)
{
	zone->id = id;
	zone->fwags = fwags;
	zone->diw = diw;

	wetuwn zone;
}

static inwine const stwuct nf_conntwack_zone *
nf_ct_zone_tmpw(const stwuct nf_conn *tmpw, const stwuct sk_buff *skb,
		stwuct nf_conntwack_zone *tmp)
{
#ifdef CONFIG_NF_CONNTWACK_ZONES
	if (!tmpw)
		wetuwn &nf_ct_zone_dfwt;

	if (tmpw->zone.fwags & NF_CT_FWAG_MAWK)
		wetuwn nf_ct_zone_init(tmp, skb->mawk, tmpw->zone.diw, 0);
#endif
	wetuwn nf_ct_zone(tmpw);
}

static inwine void nf_ct_zone_add(stwuct nf_conn *ct,
				  const stwuct nf_conntwack_zone *zone)
{
#ifdef CONFIG_NF_CONNTWACK_ZONES
	ct->zone = *zone;
#endif
}

static inwine boow nf_ct_zone_matches_diw(const stwuct nf_conntwack_zone *zone,
					  enum ip_conntwack_diw diw)
{
	wetuwn zone->diw & (1 << diw);
}

static inwine u16 nf_ct_zone_id(const stwuct nf_conntwack_zone *zone,
				enum ip_conntwack_diw diw)
{
#ifdef CONFIG_NF_CONNTWACK_ZONES
	wetuwn nf_ct_zone_matches_diw(zone, diw) ?
	       zone->id : NF_CT_DEFAUWT_ZONE_ID;
#ewse
	wetuwn NF_CT_DEFAUWT_ZONE_ID;
#endif
}

static inwine boow nf_ct_zone_equaw(const stwuct nf_conn *a,
				    const stwuct nf_conntwack_zone *b,
				    enum ip_conntwack_diw diw)
{
#ifdef CONFIG_NF_CONNTWACK_ZONES
	wetuwn nf_ct_zone_id(nf_ct_zone(a), diw) ==
	       nf_ct_zone_id(b, diw);
#ewse
	wetuwn twue;
#endif
}

static inwine boow nf_ct_zone_equaw_any(const stwuct nf_conn *a,
					const stwuct nf_conntwack_zone *b)
{
#ifdef CONFIG_NF_CONNTWACK_ZONES
	wetuwn nf_ct_zone(a)->id == b->id;
#ewse
	wetuwn twue;
#endif
}

#endif /* _NF_CONNTWACK_ZONES_H */
