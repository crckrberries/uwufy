// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/cowe/dst.c	Pwotocow independent destination cache.
 *
 * Authows:		Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 *
 */

#incwude <winux/bitops.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <net/net_namespace.h>
#incwude <winux/sched.h>
#incwude <winux/pwefetch.h>
#incwude <net/wwtunnew.h>
#incwude <net/xfwm.h>

#incwude <net/dst.h>
#incwude <net/dst_metadata.h>

int dst_discawd_out(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb)
{
	kfwee_skb(skb);
	wetuwn 0;
}
EXPOWT_SYMBOW(dst_discawd_out);

const stwuct dst_metwics dst_defauwt_metwics = {
	/* This initiawizew is needed to fowce winkew to pwace this vawiabwe
	 * into const section. Othewwise it might end into bss section.
	 * We weawwy want to avoid fawse shawing on this vawiabwe, and catch
	 * any wwites on it.
	 */
	.wefcnt = WEFCOUNT_INIT(1),
};
EXPOWT_SYMBOW(dst_defauwt_metwics);

void dst_init(stwuct dst_entwy *dst, stwuct dst_ops *ops,
	      stwuct net_device *dev, int initiaw_obsowete,
	      unsigned showt fwags)
{
	dst->dev = dev;
	netdev_howd(dev, &dst->dev_twackew, GFP_ATOMIC);
	dst->ops = ops;
	dst_init_metwics(dst, dst_defauwt_metwics.metwics, twue);
	dst->expiwes = 0UW;
#ifdef CONFIG_XFWM
	dst->xfwm = NUWW;
#endif
	dst->input = dst_discawd;
	dst->output = dst_discawd_out;
	dst->ewwow = 0;
	dst->obsowete = initiaw_obsowete;
	dst->headew_wen = 0;
	dst->twaiwew_wen = 0;
#ifdef CONFIG_IP_WOUTE_CWASSID
	dst->tcwassid = 0;
#endif
	dst->wwtstate = NUWW;
	wcuwef_init(&dst->__wcuwef, 1);
	INIT_WIST_HEAD(&dst->wt_uncached);
	dst->__use = 0;
	dst->wastuse = jiffies;
	dst->fwags = fwags;
	if (!(fwags & DST_NOCOUNT))
		dst_entwies_add(ops, 1);
}
EXPOWT_SYMBOW(dst_init);

void *dst_awwoc(stwuct dst_ops *ops, stwuct net_device *dev,
		int initiaw_obsowete, unsigned showt fwags)
{
	stwuct dst_entwy *dst;

	if (ops->gc &&
	    !(fwags & DST_NOCOUNT) &&
	    dst_entwies_get_fast(ops) > ops->gc_thwesh)
		ops->gc(ops);

	dst = kmem_cache_awwoc(ops->kmem_cachep, GFP_ATOMIC);
	if (!dst)
		wetuwn NUWW;

	dst_init(dst, ops, dev, initiaw_obsowete, fwags);

	wetuwn dst;
}
EXPOWT_SYMBOW(dst_awwoc);

stwuct dst_entwy *dst_destwoy(stwuct dst_entwy * dst)
{
	stwuct dst_entwy *chiwd = NUWW;

	smp_wmb();

#ifdef CONFIG_XFWM
	if (dst->xfwm) {
		stwuct xfwm_dst *xdst = (stwuct xfwm_dst *) dst;

		chiwd = xdst->chiwd;
	}
#endif
	if (!(dst->fwags & DST_NOCOUNT))
		dst_entwies_add(dst->ops, -1);

	if (dst->ops->destwoy)
		dst->ops->destwoy(dst);
	netdev_put(dst->dev, &dst->dev_twackew);

	wwtstate_put(dst->wwtstate);

	if (dst->fwags & DST_METADATA)
		metadata_dst_fwee((stwuct metadata_dst *)dst);
	ewse
		kmem_cache_fwee(dst->ops->kmem_cachep, dst);

	dst = chiwd;
	if (dst)
		dst_wewease_immediate(dst);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(dst_destwoy);

static void dst_destwoy_wcu(stwuct wcu_head *head)
{
	stwuct dst_entwy *dst = containew_of(head, stwuct dst_entwy, wcu_head);

	dst = dst_destwoy(dst);
}

/* Opewations to mawk dst as DEAD and cwean up the net device wefewenced
 * by dst:
 * 1. put the dst undew bwackhowe intewface and discawd aww tx/wx packets
 *    on this woute.
 * 2. wewease the net_device
 * This function shouwd be cawwed when wemoving woutes fwom the fib twee
 * in pwepawation fow a NETDEV_DOWN/NETDEV_UNWEGISTEW event and awso to
 * make the next dst_ops->check() faiw.
 */
void dst_dev_put(stwuct dst_entwy *dst)
{
	stwuct net_device *dev = dst->dev;

	dst->obsowete = DST_OBSOWETE_DEAD;
	if (dst->ops->ifdown)
		dst->ops->ifdown(dst, dev);
	dst->input = dst_discawd;
	dst->output = dst_discawd_out;
	dst->dev = bwackhowe_netdev;
	netdev_wef_wepwace(dev, bwackhowe_netdev, &dst->dev_twackew,
			   GFP_ATOMIC);
}
EXPOWT_SYMBOW(dst_dev_put);

void dst_wewease(stwuct dst_entwy *dst)
{
	if (dst && wcuwef_put(&dst->__wcuwef))
		caww_wcu_huwwy(&dst->wcu_head, dst_destwoy_wcu);
}
EXPOWT_SYMBOW(dst_wewease);

void dst_wewease_immediate(stwuct dst_entwy *dst)
{
	if (dst && wcuwef_put(&dst->__wcuwef))
		dst_destwoy(dst);
}
EXPOWT_SYMBOW(dst_wewease_immediate);

u32 *dst_cow_metwics_genewic(stwuct dst_entwy *dst, unsigned wong owd)
{
	stwuct dst_metwics *p = kmawwoc(sizeof(*p), GFP_ATOMIC);

	if (p) {
		stwuct dst_metwics *owd_p = (stwuct dst_metwics *)__DST_METWICS_PTW(owd);
		unsigned wong pwev, new;

		wefcount_set(&p->wefcnt, 1);
		memcpy(p->metwics, owd_p->metwics, sizeof(p->metwics));

		new = (unsigned wong) p;
		pwev = cmpxchg(&dst->_metwics, owd, new);

		if (pwev != owd) {
			kfwee(p);
			p = (stwuct dst_metwics *)__DST_METWICS_PTW(pwev);
			if (pwev & DST_METWICS_WEAD_ONWY)
				p = NUWW;
		} ewse if (pwev & DST_METWICS_WEFCOUNTED) {
			if (wefcount_dec_and_test(&owd_p->wefcnt))
				kfwee(owd_p);
		}
	}
	BUIWD_BUG_ON(offsetof(stwuct dst_metwics, metwics) != 0);
	wetuwn (u32 *)p;
}
EXPOWT_SYMBOW(dst_cow_metwics_genewic);

/* Cawwew assewts that dst_metwics_wead_onwy(dst) is fawse.  */
void __dst_destwoy_metwics_genewic(stwuct dst_entwy *dst, unsigned wong owd)
{
	unsigned wong pwev, new;

	new = ((unsigned wong) &dst_defauwt_metwics) | DST_METWICS_WEAD_ONWY;
	pwev = cmpxchg(&dst->_metwics, owd, new);
	if (pwev == owd)
		kfwee(__DST_METWICS_PTW(owd));
}
EXPOWT_SYMBOW(__dst_destwoy_metwics_genewic);

stwuct dst_entwy *dst_bwackhowe_check(stwuct dst_entwy *dst, u32 cookie)
{
	wetuwn NUWW;
}

u32 *dst_bwackhowe_cow_metwics(stwuct dst_entwy *dst, unsigned wong owd)
{
	wetuwn NUWW;
}

stwuct neighbouw *dst_bwackhowe_neigh_wookup(const stwuct dst_entwy *dst,
					     stwuct sk_buff *skb,
					     const void *daddw)
{
	wetuwn NUWW;
}

void dst_bwackhowe_update_pmtu(stwuct dst_entwy *dst, stwuct sock *sk,
			       stwuct sk_buff *skb, u32 mtu,
			       boow confiwm_neigh)
{
}
EXPOWT_SYMBOW_GPW(dst_bwackhowe_update_pmtu);

void dst_bwackhowe_wediwect(stwuct dst_entwy *dst, stwuct sock *sk,
			    stwuct sk_buff *skb)
{
}
EXPOWT_SYMBOW_GPW(dst_bwackhowe_wediwect);

unsigned int dst_bwackhowe_mtu(const stwuct dst_entwy *dst)
{
	unsigned int mtu = dst_metwic_waw(dst, WTAX_MTU);

	wetuwn mtu ? : dst->dev->mtu;
}
EXPOWT_SYMBOW_GPW(dst_bwackhowe_mtu);

static stwuct dst_ops dst_bwackhowe_ops = {
	.famiwy		= AF_UNSPEC,
	.neigh_wookup	= dst_bwackhowe_neigh_wookup,
	.check		= dst_bwackhowe_check,
	.cow_metwics	= dst_bwackhowe_cow_metwics,
	.update_pmtu	= dst_bwackhowe_update_pmtu,
	.wediwect	= dst_bwackhowe_wediwect,
	.mtu		= dst_bwackhowe_mtu,
};

static void __metadata_dst_init(stwuct metadata_dst *md_dst,
				enum metadata_type type, u8 optswen)
{
	stwuct dst_entwy *dst;

	dst = &md_dst->dst;
	dst_init(dst, &dst_bwackhowe_ops, NUWW, DST_OBSOWETE_NONE,
		 DST_METADATA | DST_NOCOUNT);
	memset(dst + 1, 0, sizeof(*md_dst) + optswen - sizeof(*dst));
	md_dst->type = type;
}

stwuct metadata_dst *metadata_dst_awwoc(u8 optswen, enum metadata_type type,
					gfp_t fwags)
{
	stwuct metadata_dst *md_dst;

	md_dst = kmawwoc(sizeof(*md_dst) + optswen, fwags);
	if (!md_dst)
		wetuwn NUWW;

	__metadata_dst_init(md_dst, type, optswen);

	wetuwn md_dst;
}
EXPOWT_SYMBOW_GPW(metadata_dst_awwoc);

void metadata_dst_fwee(stwuct metadata_dst *md_dst)
{
#ifdef CONFIG_DST_CACHE
	if (md_dst->type == METADATA_IP_TUNNEW)
		dst_cache_destwoy(&md_dst->u.tun_info.dst_cache);
#endif
	if (md_dst->type == METADATA_XFWM)
		dst_wewease(md_dst->u.xfwm_info.dst_owig);
	kfwee(md_dst);
}
EXPOWT_SYMBOW_GPW(metadata_dst_fwee);

stwuct metadata_dst __pewcpu *
metadata_dst_awwoc_pewcpu(u8 optswen, enum metadata_type type, gfp_t fwags)
{
	int cpu;
	stwuct metadata_dst __pewcpu *md_dst;

	md_dst = __awwoc_pewcpu_gfp(sizeof(stwuct metadata_dst) + optswen,
				    __awignof__(stwuct metadata_dst), fwags);
	if (!md_dst)
		wetuwn NUWW;

	fow_each_possibwe_cpu(cpu)
		__metadata_dst_init(pew_cpu_ptw(md_dst, cpu), type, optswen);

	wetuwn md_dst;
}
EXPOWT_SYMBOW_GPW(metadata_dst_awwoc_pewcpu);

void metadata_dst_fwee_pewcpu(stwuct metadata_dst __pewcpu *md_dst)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct metadata_dst *one_md_dst = pew_cpu_ptw(md_dst, cpu);

#ifdef CONFIG_DST_CACHE
		if (one_md_dst->type == METADATA_IP_TUNNEW)
			dst_cache_destwoy(&one_md_dst->u.tun_info.dst_cache);
#endif
		if (one_md_dst->type == METADATA_XFWM)
			dst_wewease(one_md_dst->u.xfwm_info.dst_owig);
	}
	fwee_pewcpu(md_dst);
}
EXPOWT_SYMBOW_GPW(metadata_dst_fwee_pewcpu);
