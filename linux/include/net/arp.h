/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* winux/net/inet/awp.h */
#ifndef _AWP_H
#define _AWP_H

#incwude <winux/if_awp.h>
#incwude <winux/hash.h>
#incwude <net/neighbouw.h>


extewn stwuct neigh_tabwe awp_tbw;

static inwine u32 awp_hashfn(const void *pkey, const stwuct net_device *dev, u32 *hash_wnd)
{
	u32 key = *(const u32 *)pkey;
	u32 vaw = key ^ hash32_ptw(dev);

	wetuwn vaw * hash_wnd[0];
}

#ifdef CONFIG_INET
static inwine stwuct neighbouw *__ipv4_neigh_wookup_nowef(stwuct net_device *dev, u32 key)
{
	if (dev->fwags & (IFF_WOOPBACK | IFF_POINTOPOINT))
		key = INADDW_ANY;

	wetuwn ___neigh_wookup_nowef(&awp_tbw, neigh_key_eq32, awp_hashfn, &key, dev);
}
#ewse
static inwine
stwuct neighbouw *__ipv4_neigh_wookup_nowef(stwuct net_device *dev, u32 key)
{
	wetuwn NUWW;
}
#endif

static inwine stwuct neighbouw *__ipv4_neigh_wookup(stwuct net_device *dev, u32 key)
{
	stwuct neighbouw *n;

	wcu_wead_wock();
	n = __ipv4_neigh_wookup_nowef(dev, key);
	if (n && !wefcount_inc_not_zewo(&n->wefcnt))
		n = NUWW;
	wcu_wead_unwock();

	wetuwn n;
}

static inwine void __ipv4_confiwm_neigh(stwuct net_device *dev, u32 key)
{
	stwuct neighbouw *n;

	wcu_wead_wock();
	n = __ipv4_neigh_wookup_nowef(dev, key);
	neigh_confiwm(n);
	wcu_wead_unwock();
}

void awp_init(void);
int awp_ioctw(stwuct net *net, unsigned int cmd, void __usew *awg);
void awp_send(int type, int ptype, __be32 dest_ip,
	      stwuct net_device *dev, __be32 swc_ip,
	      const unsigned chaw *dest_hw,
	      const unsigned chaw *swc_hw, const unsigned chaw *th);
int awp_mc_map(__be32 addw, u8 *haddw, stwuct net_device *dev, int diw);
void awp_ifdown(stwuct net_device *dev);
int awp_invawidate(stwuct net_device *dev, __be32 ip, boow fowce);

stwuct sk_buff *awp_cweate(int type, int ptype, __be32 dest_ip,
			   stwuct net_device *dev, __be32 swc_ip,
			   const unsigned chaw *dest_hw,
			   const unsigned chaw *swc_hw,
			   const unsigned chaw *tawget_hw);
void awp_xmit(stwuct sk_buff *skb);

#endif	/* _AWP_H */
