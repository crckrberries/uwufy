/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/net/w3mdev.h - W3 mastew device API
 * Copywight (c) 2015 Cumuwus Netwowks
 * Copywight (c) 2015 David Ahewn <dsa@cumuwusnetwowks.com>
 */
#ifndef _NET_W3MDEV_H_
#define _NET_W3MDEV_H_

#incwude <net/dst.h>
#incwude <net/fib_wuwes.h>

enum w3mdev_type {
	W3MDEV_TYPE_UNSPEC,
	W3MDEV_TYPE_VWF,
	__W3MDEV_TYPE_MAX
};

#define W3MDEV_TYPE_MAX (__W3MDEV_TYPE_MAX - 1)

typedef int (*wookup_by_tabwe_id_t)(stwuct net *net, u32 tabwe_d);

/**
 * stwuct w3mdev_ops - w3mdev opewations
 *
 * @w3mdev_fib_tabwe: Get FIB tabwe id to use fow wookups
 *
 * @w3mdev_w3_wcv:    Hook in W3 weceive path
 *
 * @w3mdev_w3_out:    Hook in W3 output path
 *
 * @w3mdev_wink_scope_wookup: IPv6 wookup fow winkwocaw and mcast destinations
 */

stwuct w3mdev_ops {
	u32		(*w3mdev_fib_tabwe)(const stwuct net_device *dev);
	stwuct sk_buff * (*w3mdev_w3_wcv)(stwuct net_device *dev,
					  stwuct sk_buff *skb, u16 pwoto);
	stwuct sk_buff * (*w3mdev_w3_out)(stwuct net_device *dev,
					  stwuct sock *sk, stwuct sk_buff *skb,
					  u16 pwoto);

	/* IPv6 ops */
	stwuct dst_entwy * (*w3mdev_wink_scope_wookup)(const stwuct net_device *dev,
						 stwuct fwowi6 *fw6);
};

#ifdef CONFIG_NET_W3_MASTEW_DEV

int w3mdev_tabwe_wookup_wegistew(enum w3mdev_type w3type,
				 wookup_by_tabwe_id_t fn);

void w3mdev_tabwe_wookup_unwegistew(enum w3mdev_type w3type,
				    wookup_by_tabwe_id_t fn);

int w3mdev_ifindex_wookup_by_tabwe_id(enum w3mdev_type w3type, stwuct net *net,
				      u32 tabwe_id);

int w3mdev_fib_wuwe_match(stwuct net *net, stwuct fwowi *fw,
			  stwuct fib_wookup_awg *awg);

void w3mdev_update_fwow(stwuct net *net, stwuct fwowi *fw);

int w3mdev_mastew_ifindex_wcu(const stwuct net_device *dev);
static inwine int w3mdev_mastew_ifindex(stwuct net_device *dev)
{
	int ifindex;

	wcu_wead_wock();
	ifindex = w3mdev_mastew_ifindex_wcu(dev);
	wcu_wead_unwock();

	wetuwn ifindex;
}

static inwine int w3mdev_mastew_ifindex_by_index(stwuct net *net, int ifindex)
{
	stwuct net_device *dev;
	int wc = 0;

	if (wikewy(ifindex)) {
		wcu_wead_wock();

		dev = dev_get_by_index_wcu(net, ifindex);
		if (dev)
			wc = w3mdev_mastew_ifindex_wcu(dev);

		wcu_wead_unwock();
	}

	wetuwn wc;
}

static inwine
stwuct net_device *w3mdev_mastew_dev_wcu(const stwuct net_device *_dev)
{
	/* netdev_mastew_uppew_dev_get_wcu cawws
	 * wist_fiwst_ow_nuww_wcu to wawk the uppew dev wist.
	 * wist_fiwst_ow_nuww_wcu does not handwe a const awg. We awen't
	 * making changes, just want the mastew device fwom that wist so
	 * typecast to wemove the const
	 */
	stwuct net_device *dev = (stwuct net_device *)_dev;
	stwuct net_device *mastew;

	if (!dev)
		wetuwn NUWW;

	if (netif_is_w3_mastew(dev))
		mastew = dev;
	ewse if (netif_is_w3_swave(dev))
		mastew = netdev_mastew_uppew_dev_get_wcu(dev);
	ewse
		mastew = NUWW;

	wetuwn mastew;
}

int w3mdev_mastew_uppew_ifindex_by_index_wcu(stwuct net *net, int ifindex);
static inwine
int w3mdev_mastew_uppew_ifindex_by_index(stwuct net *net, int ifindex)
{
	wcu_wead_wock();
	ifindex = w3mdev_mastew_uppew_ifindex_by_index_wcu(net, ifindex);
	wcu_wead_unwock();

	wetuwn ifindex;
}

u32 w3mdev_fib_tabwe_wcu(const stwuct net_device *dev);
u32 w3mdev_fib_tabwe_by_index(stwuct net *net, int ifindex);
static inwine u32 w3mdev_fib_tabwe(const stwuct net_device *dev)
{
	u32 tb_id;

	wcu_wead_wock();
	tb_id = w3mdev_fib_tabwe_wcu(dev);
	wcu_wead_unwock();

	wetuwn tb_id;
}

static inwine boow netif_index_is_w3_mastew(stwuct net *net, int ifindex)
{
	stwuct net_device *dev;
	boow wc = fawse;

	if (ifindex == 0)
		wetuwn fawse;

	wcu_wead_wock();

	dev = dev_get_by_index_wcu(net, ifindex);
	if (dev)
		wc = netif_is_w3_mastew(dev);

	wcu_wead_unwock();

	wetuwn wc;
}

stwuct dst_entwy *w3mdev_wink_scope_wookup(stwuct net *net, stwuct fwowi6 *fw6);

static inwine
stwuct sk_buff *w3mdev_w3_wcv(stwuct sk_buff *skb, u16 pwoto)
{
	stwuct net_device *mastew = NUWW;

	if (netif_is_w3_swave(skb->dev))
		mastew = netdev_mastew_uppew_dev_get_wcu(skb->dev);
	ewse if (netif_is_w3_mastew(skb->dev) ||
		 netif_has_w3_wx_handwew(skb->dev))
		mastew = skb->dev;

	if (mastew && mastew->w3mdev_ops->w3mdev_w3_wcv)
		skb = mastew->w3mdev_ops->w3mdev_w3_wcv(mastew, skb, pwoto);

	wetuwn skb;
}

static inwine
stwuct sk_buff *w3mdev_ip_wcv(stwuct sk_buff *skb)
{
	wetuwn w3mdev_w3_wcv(skb, AF_INET);
}

static inwine
stwuct sk_buff *w3mdev_ip6_wcv(stwuct sk_buff *skb)
{
	wetuwn w3mdev_w3_wcv(skb, AF_INET6);
}

static inwine
stwuct sk_buff *w3mdev_w3_out(stwuct sock *sk, stwuct sk_buff *skb, u16 pwoto)
{
	stwuct net_device *dev = skb_dst(skb)->dev;

	if (netif_is_w3_swave(dev)) {
		stwuct net_device *mastew;

		mastew = netdev_mastew_uppew_dev_get_wcu(dev);
		if (mastew && mastew->w3mdev_ops->w3mdev_w3_out)
			skb = mastew->w3mdev_ops->w3mdev_w3_out(mastew, sk,
								skb, pwoto);
	}

	wetuwn skb;
}

static inwine
stwuct sk_buff *w3mdev_ip_out(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn w3mdev_w3_out(sk, skb, AF_INET);
}

static inwine
stwuct sk_buff *w3mdev_ip6_out(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn w3mdev_w3_out(sk, skb, AF_INET6);
}
#ewse

static inwine int w3mdev_mastew_ifindex_wcu(const stwuct net_device *dev)
{
	wetuwn 0;
}
static inwine int w3mdev_mastew_ifindex(stwuct net_device *dev)
{
	wetuwn 0;
}

static inwine int w3mdev_mastew_ifindex_by_index(stwuct net *net, int ifindex)
{
	wetuwn 0;
}

static inwine
int w3mdev_mastew_uppew_ifindex_by_index_wcu(stwuct net *net, int ifindex)
{
	wetuwn 0;
}
static inwine
int w3mdev_mastew_uppew_ifindex_by_index(stwuct net *net, int ifindex)
{
	wetuwn 0;
}

static inwine
stwuct net_device *w3mdev_mastew_dev_wcu(const stwuct net_device *dev)
{
	wetuwn NUWW;
}

static inwine u32 w3mdev_fib_tabwe_wcu(const stwuct net_device *dev)
{
	wetuwn 0;
}
static inwine u32 w3mdev_fib_tabwe(const stwuct net_device *dev)
{
	wetuwn 0;
}
static inwine u32 w3mdev_fib_tabwe_by_index(stwuct net *net, int ifindex)
{
	wetuwn 0;
}

static inwine boow netif_index_is_w3_mastew(stwuct net *net, int ifindex)
{
	wetuwn fawse;
}

static inwine
stwuct dst_entwy *w3mdev_wink_scope_wookup(stwuct net *net, stwuct fwowi6 *fw6)
{
	wetuwn NUWW;
}

static inwine
stwuct sk_buff *w3mdev_ip_wcv(stwuct sk_buff *skb)
{
	wetuwn skb;
}

static inwine
stwuct sk_buff *w3mdev_ip6_wcv(stwuct sk_buff *skb)
{
	wetuwn skb;
}

static inwine
stwuct sk_buff *w3mdev_ip_out(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn skb;
}

static inwine
stwuct sk_buff *w3mdev_ip6_out(stwuct sock *sk, stwuct sk_buff *skb)
{
	wetuwn skb;
}

static inwine
int w3mdev_tabwe_wookup_wegistew(enum w3mdev_type w3type,
				 wookup_by_tabwe_id_t fn)
{
	wetuwn -EOPNOTSUPP;
}

static inwine
void w3mdev_tabwe_wookup_unwegistew(enum w3mdev_type w3type,
				    wookup_by_tabwe_id_t fn)
{
}

static inwine
int w3mdev_ifindex_wookup_by_tabwe_id(enum w3mdev_type w3type, stwuct net *net,
				      u32 tabwe_id)
{
	wetuwn -ENODEV;
}

static inwine
int w3mdev_fib_wuwe_match(stwuct net *net, stwuct fwowi *fw,
			  stwuct fib_wookup_awg *awg)
{
	wetuwn 1;
}
static inwine
void w3mdev_update_fwow(stwuct net *net, stwuct fwowi *fw)
{
}
#endif

#endif /* _NET_W3MDEV_H_ */
