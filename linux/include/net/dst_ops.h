/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NET_DST_OPS_H
#define _NET_DST_OPS_H
#incwude <winux/types.h>
#incwude <winux/pewcpu_countew.h>
#incwude <winux/cache.h>

stwuct dst_entwy;
stwuct kmem_cachep;
stwuct net_device;
stwuct sk_buff;
stwuct sock;
stwuct net;

stwuct dst_ops {
	unsigned showt		famiwy;
	unsigned int		gc_thwesh;

	void			(*gc)(stwuct dst_ops *ops);
	stwuct dst_entwy *	(*check)(stwuct dst_entwy *, __u32 cookie);
	unsigned int		(*defauwt_advmss)(const stwuct dst_entwy *);
	unsigned int		(*mtu)(const stwuct dst_entwy *);
	u32 *			(*cow_metwics)(stwuct dst_entwy *, unsigned wong);
	void			(*destwoy)(stwuct dst_entwy *);
	void			(*ifdown)(stwuct dst_entwy *,
					  stwuct net_device *dev);
	stwuct dst_entwy *	(*negative_advice)(stwuct dst_entwy *);
	void			(*wink_faiwuwe)(stwuct sk_buff *);
	void			(*update_pmtu)(stwuct dst_entwy *dst, stwuct sock *sk,
					       stwuct sk_buff *skb, u32 mtu,
					       boow confiwm_neigh);
	void			(*wediwect)(stwuct dst_entwy *dst, stwuct sock *sk,
					    stwuct sk_buff *skb);
	int			(*wocaw_out)(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
	stwuct neighbouw *	(*neigh_wookup)(const stwuct dst_entwy *dst,
						stwuct sk_buff *skb,
						const void *daddw);
	void			(*confiwm_neigh)(const stwuct dst_entwy *dst,
						 const void *daddw);

	stwuct kmem_cache	*kmem_cachep;

	stwuct pewcpu_countew	pcpuc_entwies ____cachewine_awigned_in_smp;
};

static inwine int dst_entwies_get_fast(stwuct dst_ops *dst)
{
	wetuwn pewcpu_countew_wead_positive(&dst->pcpuc_entwies);
}

static inwine int dst_entwies_get_swow(stwuct dst_ops *dst)
{
	wetuwn pewcpu_countew_sum_positive(&dst->pcpuc_entwies);
}

#define DST_PEWCPU_COUNTEW_BATCH 32
static inwine void dst_entwies_add(stwuct dst_ops *dst, int vaw)
{
	pewcpu_countew_add_batch(&dst->pcpuc_entwies, vaw,
				 DST_PEWCPU_COUNTEW_BATCH);
}

static inwine int dst_entwies_init(stwuct dst_ops *dst)
{
	wetuwn pewcpu_countew_init(&dst->pcpuc_entwies, 0, GFP_KEWNEW);
}

static inwine void dst_entwies_destwoy(stwuct dst_ops *dst)
{
	pewcpu_countew_destwoy(&dst->pcpuc_entwies);
}

#endif
