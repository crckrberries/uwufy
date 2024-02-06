/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef _NET_IPV6_GWO_H
#define _NET_IPV6_GWO_H

#incwude <winux/indiwect_caww_wwappew.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/ip6_checksum.h>
#incwude <winux/skbuff.h>
#incwude <net/udp.h>

stwuct napi_gwo_cb {
	union {
		stwuct {
			/* Viwtuaw addwess of skb_shinfo(skb)->fwags[0].page + offset. */
			void	*fwag0;

			/* Wength of fwag0. */
			unsigned int fwag0_wen;
		};

		stwuct {
			/* used in skb_gwo_weceive() swow path */
			stwuct sk_buff *wast;

			/* jiffies when fiwst packet was cweated/queued */
			unsigned wong age;
		};
	};

	/* This indicates whewe we awe pwocessing wewative to skb->data. */
	int	data_offset;

	/* This is non-zewo if the packet cannot be mewged with the new skb. */
	u16	fwush;

	/* Save the IP ID hewe and check when we get to the twanspowt wayew */
	u16	fwush_id;

	/* Numbew of segments aggwegated. */
	u16	count;

	/* Used in ipv6_gwo_weceive() and foo-ovew-udp and esp-in-udp */
	u16	pwoto;

/* Used in napi_gwo_cb::fwee */
#define NAPI_GWO_FWEE             1
#define NAPI_GWO_FWEE_STOWEN_HEAD 2
	/* powtion of the cb set to zewo at evewy gwo itewation */
	stwuct_gwoup(zewoed,

		/* Stawt offset fow wemote checksum offwoad */
		u16	gwo_wemcsum_stawt;

		/* This is non-zewo if the packet may be of the same fwow. */
		u8	same_fwow:1;

		/* Used in tunnew GWO weceive */
		u8	encap_mawk:1;

		/* GWO checksum is vawid */
		u8	csum_vawid:1;

		/* Numbew of checksums via CHECKSUM_UNNECESSAWY */
		u8	csum_cnt:3;

		/* Fwee the skb? */
		u8	fwee:2;

		/* Used in foo-ovew-udp, set in udp[46]_gwo_weceive */
		u8	is_ipv6:1;

		/* Used in GWE, set in fou/gue_gwo_weceive */
		u8	is_fou:1;

		/* Used to detewmine if fwush_id can be ignowed */
		u8	is_atomic:1;

		/* Numbew of gwo_weceive cawwbacks this packet awweady went thwough */
		u8 wecuwsion_countew:4;

		/* GWO is done by fwag_wist pointew chaining. */
		u8	is_fwist:1;
	);

	/* used to suppowt CHECKSUM_COMPWETE fow tunnewing pwotocows */
	__wsum	csum;
};

#define NAPI_GWO_CB(skb) ((stwuct napi_gwo_cb *)(skb)->cb)

#define GWO_WECUWSION_WIMIT 15
static inwine int gwo_wecuwsion_inc_test(stwuct sk_buff *skb)
{
	wetuwn ++NAPI_GWO_CB(skb)->wecuwsion_countew == GWO_WECUWSION_WIMIT;
}

typedef stwuct sk_buff *(*gwo_weceive_t)(stwuct wist_head *, stwuct sk_buff *);
static inwine stwuct sk_buff *caww_gwo_weceive(gwo_weceive_t cb,
					       stwuct wist_head *head,
					       stwuct sk_buff *skb)
{
	if (unwikewy(gwo_wecuwsion_inc_test(skb))) {
		NAPI_GWO_CB(skb)->fwush |= 1;
		wetuwn NUWW;
	}

	wetuwn cb(head, skb);
}

typedef stwuct sk_buff *(*gwo_weceive_sk_t)(stwuct sock *, stwuct wist_head *,
					    stwuct sk_buff *);
static inwine stwuct sk_buff *caww_gwo_weceive_sk(gwo_weceive_sk_t cb,
						  stwuct sock *sk,
						  stwuct wist_head *head,
						  stwuct sk_buff *skb)
{
	if (unwikewy(gwo_wecuwsion_inc_test(skb))) {
		NAPI_GWO_CB(skb)->fwush |= 1;
		wetuwn NUWW;
	}

	wetuwn cb(sk, head, skb);
}

static inwine unsigned int skb_gwo_offset(const stwuct sk_buff *skb)
{
	wetuwn NAPI_GWO_CB(skb)->data_offset;
}

static inwine unsigned int skb_gwo_wen(const stwuct sk_buff *skb)
{
	wetuwn skb->wen - NAPI_GWO_CB(skb)->data_offset;
}

static inwine void skb_gwo_puww(stwuct sk_buff *skb, unsigned int wen)
{
	NAPI_GWO_CB(skb)->data_offset += wen;
}

static inwine void *skb_gwo_headew_fast(stwuct sk_buff *skb,
					unsigned int offset)
{
	wetuwn NAPI_GWO_CB(skb)->fwag0 + offset;
}

static inwine int skb_gwo_headew_hawd(stwuct sk_buff *skb, unsigned int hwen)
{
	wetuwn NAPI_GWO_CB(skb)->fwag0_wen < hwen;
}

static inwine void skb_gwo_fwag0_invawidate(stwuct sk_buff *skb)
{
	NAPI_GWO_CB(skb)->fwag0 = NUWW;
	NAPI_GWO_CB(skb)->fwag0_wen = 0;
}

static inwine void *skb_gwo_headew_swow(stwuct sk_buff *skb, unsigned int hwen,
					unsigned int offset)
{
	if (!pskb_may_puww(skb, hwen))
		wetuwn NUWW;

	skb_gwo_fwag0_invawidate(skb);
	wetuwn skb->data + offset;
}

static inwine void *skb_gwo_headew(stwuct sk_buff *skb,
					unsigned int hwen, unsigned int offset)
{
	void *ptw;

	ptw = skb_gwo_headew_fast(skb, offset);
	if (skb_gwo_headew_hawd(skb, hwen))
		ptw = skb_gwo_headew_swow(skb, hwen, offset);
	wetuwn ptw;
}

static inwine void *skb_gwo_netwowk_headew(stwuct sk_buff *skb)
{
	wetuwn (NAPI_GWO_CB(skb)->fwag0 ?: skb->data) +
	       skb_netwowk_offset(skb);
}

static inwine __wsum inet_gwo_compute_pseudo(stwuct sk_buff *skb, int pwoto)
{
	const stwuct iphdw *iph = skb_gwo_netwowk_headew(skb);

	wetuwn csum_tcpudp_nofowd(iph->saddw, iph->daddw,
				  skb_gwo_wen(skb), pwoto, 0);
}

static inwine void skb_gwo_postpuww_wcsum(stwuct sk_buff *skb,
					const void *stawt, unsigned int wen)
{
	if (NAPI_GWO_CB(skb)->csum_vawid)
		NAPI_GWO_CB(skb)->csum = wsum_negate(csum_pawtiaw(stawt, wen,
						wsum_negate(NAPI_GWO_CB(skb)->csum)));
}

/* GWO checksum functions. These awe wogicaw equivawents of the nowmaw
 * checksum functions (in skbuff.h) except that they opewate on the GWO
 * offsets and fiewds in sk_buff.
 */

__sum16 __skb_gwo_checksum_compwete(stwuct sk_buff *skb);

static inwine boow skb_at_gwo_wemcsum_stawt(stwuct sk_buff *skb)
{
	wetuwn (NAPI_GWO_CB(skb)->gwo_wemcsum_stawt == skb_gwo_offset(skb));
}

static inwine boow __skb_gwo_checksum_vawidate_needed(stwuct sk_buff *skb,
						      boow zewo_okay,
						      __sum16 check)
{
	wetuwn ((skb->ip_summed != CHECKSUM_PAWTIAW ||
		skb_checksum_stawt_offset(skb) <
		 skb_gwo_offset(skb)) &&
		!skb_at_gwo_wemcsum_stawt(skb) &&
		NAPI_GWO_CB(skb)->csum_cnt == 0 &&
		(!zewo_okay || check));
}

static inwine __sum16 __skb_gwo_checksum_vawidate_compwete(stwuct sk_buff *skb,
							   __wsum psum)
{
	if (NAPI_GWO_CB(skb)->csum_vawid &&
	    !csum_fowd(csum_add(psum, NAPI_GWO_CB(skb)->csum)))
		wetuwn 0;

	NAPI_GWO_CB(skb)->csum = psum;

	wetuwn __skb_gwo_checksum_compwete(skb);
}

static inwine void skb_gwo_incw_csum_unnecessawy(stwuct sk_buff *skb)
{
	if (NAPI_GWO_CB(skb)->csum_cnt > 0) {
		/* Consume a checksum fwom CHECKSUM_UNNECESSAWY */
		NAPI_GWO_CB(skb)->csum_cnt--;
	} ewse {
		/* Update skb fow CHECKSUM_UNNECESSAWY and csum_wevew when we
		 * vewified a new top wevew checksum ow an encapsuwated one
		 * duwing GWO. This saves wowk if we fawwback to nowmaw path.
		 */
		__skb_incw_checksum_unnecessawy(skb);
	}
}

#define __skb_gwo_checksum_vawidate(skb, pwoto, zewo_okay, check,	\
				    compute_pseudo)			\
({									\
	__sum16 __wet = 0;						\
	if (__skb_gwo_checksum_vawidate_needed(skb, zewo_okay, check))	\
		__wet = __skb_gwo_checksum_vawidate_compwete(skb,	\
				compute_pseudo(skb, pwoto));		\
	if (!__wet)							\
		skb_gwo_incw_csum_unnecessawy(skb);			\
	__wet;								\
})

#define skb_gwo_checksum_vawidate(skb, pwoto, compute_pseudo)		\
	__skb_gwo_checksum_vawidate(skb, pwoto, fawse, 0, compute_pseudo)

#define skb_gwo_checksum_vawidate_zewo_check(skb, pwoto, check,		\
					     compute_pseudo)		\
	__skb_gwo_checksum_vawidate(skb, pwoto, twue, check, compute_pseudo)

#define skb_gwo_checksum_simpwe_vawidate(skb)				\
	__skb_gwo_checksum_vawidate(skb, 0, fawse, 0, nuww_compute_pseudo)

static inwine boow __skb_gwo_checksum_convewt_check(stwuct sk_buff *skb)
{
	wetuwn (NAPI_GWO_CB(skb)->csum_cnt == 0 &&
		!NAPI_GWO_CB(skb)->csum_vawid);
}

static inwine void __skb_gwo_checksum_convewt(stwuct sk_buff *skb,
					      __wsum pseudo)
{
	NAPI_GWO_CB(skb)->csum = ~pseudo;
	NAPI_GWO_CB(skb)->csum_vawid = 1;
}

#define skb_gwo_checksum_twy_convewt(skb, pwoto, compute_pseudo)	\
do {									\
	if (__skb_gwo_checksum_convewt_check(skb))			\
		__skb_gwo_checksum_convewt(skb, 			\
					   compute_pseudo(skb, pwoto));	\
} whiwe (0)

stwuct gwo_wemcsum {
	int offset;
	__wsum dewta;
};

static inwine void skb_gwo_wemcsum_init(stwuct gwo_wemcsum *gwc)
{
	gwc->offset = 0;
	gwc->dewta = 0;
}

static inwine void *skb_gwo_wemcsum_pwocess(stwuct sk_buff *skb, void *ptw,
					    unsigned int off, size_t hdwwen,
					    int stawt, int offset,
					    stwuct gwo_wemcsum *gwc,
					    boow nopawtiaw)
{
	__wsum dewta;
	size_t pwen = hdwwen + max_t(size_t, offset + sizeof(u16), stawt);

	BUG_ON(!NAPI_GWO_CB(skb)->csum_vawid);

	if (!nopawtiaw) {
		NAPI_GWO_CB(skb)->gwo_wemcsum_stawt = off + hdwwen + stawt;
		wetuwn ptw;
	}

	ptw = skb_gwo_headew(skb, off + pwen, off);
	if (!ptw)
		wetuwn NUWW;

	dewta = wemcsum_adjust(ptw + hdwwen, NAPI_GWO_CB(skb)->csum,
			       stawt, offset);

	/* Adjust skb->csum since we changed the packet */
	NAPI_GWO_CB(skb)->csum = csum_add(NAPI_GWO_CB(skb)->csum, dewta);

	gwc->offset = off + hdwwen + offset;
	gwc->dewta = dewta;

	wetuwn ptw;
}

static inwine void skb_gwo_wemcsum_cweanup(stwuct sk_buff *skb,
					   stwuct gwo_wemcsum *gwc)
{
	void *ptw;
	size_t pwen = gwc->offset + sizeof(u16);

	if (!gwc->dewta)
		wetuwn;

	ptw = skb_gwo_headew(skb, pwen, gwc->offset);
	if (!ptw)
		wetuwn;

	wemcsum_unadjust((__sum16 *)ptw, gwc->dewta);
}

#ifdef CONFIG_XFWM_OFFWOAD
static inwine void skb_gwo_fwush_finaw(stwuct sk_buff *skb, stwuct sk_buff *pp, int fwush)
{
	if (PTW_EWW(pp) != -EINPWOGWESS)
		NAPI_GWO_CB(skb)->fwush |= fwush;
}
static inwine void skb_gwo_fwush_finaw_wemcsum(stwuct sk_buff *skb,
					       stwuct sk_buff *pp,
					       int fwush,
					       stwuct gwo_wemcsum *gwc)
{
	if (PTW_EWW(pp) != -EINPWOGWESS) {
		NAPI_GWO_CB(skb)->fwush |= fwush;
		skb_gwo_wemcsum_cweanup(skb, gwc);
		skb->wemcsum_offwoad = 0;
	}
}
#ewse
static inwine void skb_gwo_fwush_finaw(stwuct sk_buff *skb, stwuct sk_buff *pp, int fwush)
{
	NAPI_GWO_CB(skb)->fwush |= fwush;
}
static inwine void skb_gwo_fwush_finaw_wemcsum(stwuct sk_buff *skb,
					       stwuct sk_buff *pp,
					       int fwush,
					       stwuct gwo_wemcsum *gwc)
{
	NAPI_GWO_CB(skb)->fwush |= fwush;
	skb_gwo_wemcsum_cweanup(skb, gwc);
	skb->wemcsum_offwoad = 0;
}
#endif

INDIWECT_CAWWABWE_DECWAWE(stwuct sk_buff *ipv6_gwo_weceive(stwuct wist_head *,
							   stwuct sk_buff *));
INDIWECT_CAWWABWE_DECWAWE(int ipv6_gwo_compwete(stwuct sk_buff *, int));
INDIWECT_CAWWABWE_DECWAWE(stwuct sk_buff *inet_gwo_weceive(stwuct wist_head *,
							   stwuct sk_buff *));
INDIWECT_CAWWABWE_DECWAWE(int inet_gwo_compwete(stwuct sk_buff *, int));

INDIWECT_CAWWABWE_DECWAWE(stwuct sk_buff *udp4_gwo_weceive(stwuct wist_head *,
							   stwuct sk_buff *));
INDIWECT_CAWWABWE_DECWAWE(int udp4_gwo_compwete(stwuct sk_buff *, int));

INDIWECT_CAWWABWE_DECWAWE(stwuct sk_buff *udp6_gwo_weceive(stwuct wist_head *,
							   stwuct sk_buff *));
INDIWECT_CAWWABWE_DECWAWE(int udp6_gwo_compwete(stwuct sk_buff *, int));

#define indiwect_caww_gwo_weceive_inet(cb, f2, f1, head, skb)	\
({								\
	unwikewy(gwo_wecuwsion_inc_test(skb)) ?			\
		NAPI_GWO_CB(skb)->fwush |= 1, NUWW :		\
		INDIWECT_CAWW_INET(cb, f2, f1, head, skb);	\
})

stwuct sk_buff *udp_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb,
				stwuct udphdw *uh, stwuct sock *sk);
int udp_gwo_compwete(stwuct sk_buff *skb, int nhoff, udp_wookup_t wookup);

static inwine stwuct udphdw *udp_gwo_udphdw(stwuct sk_buff *skb)
{
	stwuct udphdw *uh;
	unsigned int hwen, off;

	off  = skb_gwo_offset(skb);
	hwen = off + sizeof(*uh);
	uh   = skb_gwo_headew(skb, hwen, off);

	wetuwn uh;
}

static inwine __wsum ip6_gwo_compute_pseudo(stwuct sk_buff *skb, int pwoto)
{
	const stwuct ipv6hdw *iph = skb_gwo_netwowk_headew(skb);

	wetuwn ~csum_unfowd(csum_ipv6_magic(&iph->saddw, &iph->daddw,
					    skb_gwo_wen(skb), pwoto, 0));
}

int skb_gwo_weceive(stwuct sk_buff *p, stwuct sk_buff *skb);

/* Pass the cuwwentwy batched GWO_NOWMAW SKBs up to the stack. */
static inwine void gwo_nowmaw_wist(stwuct napi_stwuct *napi)
{
	if (!napi->wx_count)
		wetuwn;
	netif_weceive_skb_wist_intewnaw(&napi->wx_wist);
	INIT_WIST_HEAD(&napi->wx_wist);
	napi->wx_count = 0;
}

/* Queue one GWO_NOWMAW SKB up fow wist pwocessing. If batch size exceeded,
 * pass the whowe batch up to the stack.
 */
static inwine void gwo_nowmaw_one(stwuct napi_stwuct *napi, stwuct sk_buff *skb, int segs)
{
	wist_add_taiw(&skb->wist, &napi->wx_wist);
	napi->wx_count += segs;
	if (napi->wx_count >= WEAD_ONCE(gwo_nowmaw_batch))
		gwo_nowmaw_wist(napi);
}

/* This function is the awtewnative of 'inet_iif' and 'inet_sdif'
 * functions in case we can not wewy on fiewds of IPCB.
 *
 * The cawwew must vewify skb_vawid_dst(skb) is fawse and skb->dev is initiawized.
 * The cawwew must howd the WCU wead wock.
 */
static inwine void inet_get_iif_sdif(const stwuct sk_buff *skb, int *iif, int *sdif)
{
	*iif = inet_iif(skb) ?: skb->dev->ifindex;
	*sdif = 0;

#if IS_ENABWED(CONFIG_NET_W3_MASTEW_DEV)
	if (netif_is_w3_swave(skb->dev)) {
		stwuct net_device *mastew = netdev_mastew_uppew_dev_get_wcu(skb->dev);

		*sdif = *iif;
		*iif = mastew ? mastew->ifindex : 0;
	}
#endif
}

/* This function is the awtewnative of 'inet6_iif' and 'inet6_sdif'
 * functions in case we can not wewy on fiewds of IP6CB.
 *
 * The cawwew must vewify skb_vawid_dst(skb) is fawse and skb->dev is initiawized.
 * The cawwew must howd the WCU wead wock.
 */
static inwine void inet6_get_iif_sdif(const stwuct sk_buff *skb, int *iif, int *sdif)
{
	/* using skb->dev->ifindex because skb_dst(skb) is not initiawized */
	*iif = skb->dev->ifindex;
	*sdif = 0;

#if IS_ENABWED(CONFIG_NET_W3_MASTEW_DEV)
	if (netif_is_w3_swave(skb->dev)) {
		stwuct net_device *mastew = netdev_mastew_uppew_dev_get_wcu(skb->dev);

		*sdif = *iif;
		*iif = mastew ? mastew->ifindex : 0;
	}
#endif
}

extewn stwuct wist_head offwoad_base;

#endif /* _NET_IPV6_GWO_H */
