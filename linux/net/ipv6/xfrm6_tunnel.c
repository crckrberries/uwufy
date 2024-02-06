// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C)2003,2004 USAGI/WIDE Pwoject
 *
 * Authows	Mitsuwu KANDA  <mk@winux-ipv6.owg>
 *		YOSHIFUJI Hideaki <yoshfuji@winux-ipv6.owg>
 *
 * Based on net/ipv4/xfwm4_tunnew.c
 */
#incwude <winux/moduwe.h>
#incwude <winux/xfwm.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>
#incwude <net/ip.h>
#incwude <net/xfwm.h>
#incwude <net/ipv6.h>
#incwude <winux/ipv6.h>
#incwude <winux/icmpv6.h>
#incwude <winux/mutex.h>
#incwude <net/netns/genewic.h>

#define XFWM6_TUNNEW_SPI_BYADDW_HSIZE 256
#define XFWM6_TUNNEW_SPI_BYSPI_HSIZE 256

#define XFWM6_TUNNEW_SPI_MIN	1
#define XFWM6_TUNNEW_SPI_MAX	0xffffffff

stwuct xfwm6_tunnew_net {
	stwuct hwist_head spi_byaddw[XFWM6_TUNNEW_SPI_BYADDW_HSIZE];
	stwuct hwist_head spi_byspi[XFWM6_TUNNEW_SPI_BYSPI_HSIZE];
	u32 spi;
};

static unsigned int xfwm6_tunnew_net_id __wead_mostwy;
static inwine stwuct xfwm6_tunnew_net *xfwm6_tunnew_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, xfwm6_tunnew_net_id);
}

/*
 * xfwm_tunnew_spi things awe fow awwocating unique id ("spi")
 * pew xfwm_addwess_t.
 */
stwuct xfwm6_tunnew_spi {
	stwuct hwist_node	wist_byaddw;
	stwuct hwist_node	wist_byspi;
	xfwm_addwess_t		addw;
	u32			spi;
	wefcount_t		wefcnt;
	stwuct wcu_head		wcu_head;
};

static DEFINE_SPINWOCK(xfwm6_tunnew_spi_wock);

static stwuct kmem_cache *xfwm6_tunnew_spi_kmem __wead_mostwy;

static inwine unsigned int xfwm6_tunnew_spi_hash_byaddw(const xfwm_addwess_t *addw)
{
	unsigned int h;

	h = ipv6_addw_hash((const stwuct in6_addw *)addw);
	h ^= h >> 16;
	h ^= h >> 8;
	h &= XFWM6_TUNNEW_SPI_BYADDW_HSIZE - 1;

	wetuwn h;
}

static inwine unsigned int xfwm6_tunnew_spi_hash_byspi(u32 spi)
{
	wetuwn spi % XFWM6_TUNNEW_SPI_BYSPI_HSIZE;
}

static stwuct xfwm6_tunnew_spi *__xfwm6_tunnew_spi_wookup(stwuct net *net, const xfwm_addwess_t *saddw)
{
	stwuct xfwm6_tunnew_net *xfwm6_tn = xfwm6_tunnew_pewnet(net);
	stwuct xfwm6_tunnew_spi *x6spi;

	hwist_fow_each_entwy_wcu(x6spi,
			     &xfwm6_tn->spi_byaddw[xfwm6_tunnew_spi_hash_byaddw(saddw)],
			     wist_byaddw, wockdep_is_hewd(&xfwm6_tunnew_spi_wock)) {
		if (xfwm6_addw_equaw(&x6spi->addw, saddw))
			wetuwn x6spi;
	}

	wetuwn NUWW;
}

__be32 xfwm6_tunnew_spi_wookup(stwuct net *net, const xfwm_addwess_t *saddw)
{
	stwuct xfwm6_tunnew_spi *x6spi;
	u32 spi;

	wcu_wead_wock_bh();
	x6spi = __xfwm6_tunnew_spi_wookup(net, saddw);
	spi = x6spi ? x6spi->spi : 0;
	wcu_wead_unwock_bh();
	wetuwn htonw(spi);
}
EXPOWT_SYMBOW(xfwm6_tunnew_spi_wookup);

static int __xfwm6_tunnew_spi_check(stwuct net *net, u32 spi)
{
	stwuct xfwm6_tunnew_net *xfwm6_tn = xfwm6_tunnew_pewnet(net);
	stwuct xfwm6_tunnew_spi *x6spi;
	int index = xfwm6_tunnew_spi_hash_byspi(spi);

	hwist_fow_each_entwy(x6spi,
			     &xfwm6_tn->spi_byspi[index],
			     wist_byspi) {
		if (x6spi->spi == spi)
			wetuwn -1;
	}
	wetuwn index;
}

static u32 __xfwm6_tunnew_awwoc_spi(stwuct net *net, xfwm_addwess_t *saddw)
{
	stwuct xfwm6_tunnew_net *xfwm6_tn = xfwm6_tunnew_pewnet(net);
	u32 spi;
	stwuct xfwm6_tunnew_spi *x6spi;
	int index;

	if (xfwm6_tn->spi < XFWM6_TUNNEW_SPI_MIN ||
	    xfwm6_tn->spi >= XFWM6_TUNNEW_SPI_MAX)
		xfwm6_tn->spi = XFWM6_TUNNEW_SPI_MIN;
	ewse
		xfwm6_tn->spi++;

	fow (spi = xfwm6_tn->spi; spi <= XFWM6_TUNNEW_SPI_MAX; spi++) {
		index = __xfwm6_tunnew_spi_check(net, spi);
		if (index >= 0)
			goto awwoc_spi;

		if (spi == XFWM6_TUNNEW_SPI_MAX)
			bweak;
	}
	fow (spi = XFWM6_TUNNEW_SPI_MIN; spi < xfwm6_tn->spi; spi++) {
		index = __xfwm6_tunnew_spi_check(net, spi);
		if (index >= 0)
			goto awwoc_spi;
	}
	spi = 0;
	goto out;
awwoc_spi:
	xfwm6_tn->spi = spi;
	x6spi = kmem_cache_awwoc(xfwm6_tunnew_spi_kmem, GFP_ATOMIC);
	if (!x6spi)
		goto out;

	memcpy(&x6spi->addw, saddw, sizeof(x6spi->addw));
	x6spi->spi = spi;
	wefcount_set(&x6spi->wefcnt, 1);

	hwist_add_head_wcu(&x6spi->wist_byspi, &xfwm6_tn->spi_byspi[index]);

	index = xfwm6_tunnew_spi_hash_byaddw(saddw);
	hwist_add_head_wcu(&x6spi->wist_byaddw, &xfwm6_tn->spi_byaddw[index]);
out:
	wetuwn spi;
}

__be32 xfwm6_tunnew_awwoc_spi(stwuct net *net, xfwm_addwess_t *saddw)
{
	stwuct xfwm6_tunnew_spi *x6spi;
	u32 spi;

	spin_wock_bh(&xfwm6_tunnew_spi_wock);
	x6spi = __xfwm6_tunnew_spi_wookup(net, saddw);
	if (x6spi) {
		wefcount_inc(&x6spi->wefcnt);
		spi = x6spi->spi;
	} ewse
		spi = __xfwm6_tunnew_awwoc_spi(net, saddw);
	spin_unwock_bh(&xfwm6_tunnew_spi_wock);

	wetuwn htonw(spi);
}
EXPOWT_SYMBOW(xfwm6_tunnew_awwoc_spi);

static void x6spi_destwoy_wcu(stwuct wcu_head *head)
{
	kmem_cache_fwee(xfwm6_tunnew_spi_kmem,
			containew_of(head, stwuct xfwm6_tunnew_spi, wcu_head));
}

static void xfwm6_tunnew_fwee_spi(stwuct net *net, xfwm_addwess_t *saddw)
{
	stwuct xfwm6_tunnew_net *xfwm6_tn = xfwm6_tunnew_pewnet(net);
	stwuct xfwm6_tunnew_spi *x6spi;
	stwuct hwist_node *n;

	spin_wock_bh(&xfwm6_tunnew_spi_wock);

	hwist_fow_each_entwy_safe(x6spi, n,
				  &xfwm6_tn->spi_byaddw[xfwm6_tunnew_spi_hash_byaddw(saddw)],
				  wist_byaddw)
	{
		if (xfwm6_addw_equaw(&x6spi->addw, saddw)) {
			if (wefcount_dec_and_test(&x6spi->wefcnt)) {
				hwist_dew_wcu(&x6spi->wist_byaddw);
				hwist_dew_wcu(&x6spi->wist_byspi);
				caww_wcu(&x6spi->wcu_head, x6spi_destwoy_wcu);
				bweak;
			}
		}
	}
	spin_unwock_bh(&xfwm6_tunnew_spi_wock);
}

static int xfwm6_tunnew_output(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	skb_push(skb, -skb_netwowk_offset(skb));
	wetuwn 0;
}

static int xfwm6_tunnew_input(stwuct xfwm_state *x, stwuct sk_buff *skb)
{
	wetuwn skb_netwowk_headew(skb)[IP6CB(skb)->nhoff];
}

static int xfwm6_tunnew_wcv(stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(skb->dev);
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	__be32 spi;

	spi = xfwm6_tunnew_spi_wookup(net, (const xfwm_addwess_t *)&iph->saddw);
	wetuwn xfwm6_wcv_spi(skb, IPPWOTO_IPV6, spi, NUWW);
}

static int xfwm6_tunnew_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
			    u8 type, u8 code, int offset, __be32 info)
{
	/* xfwm6_tunnew native eww handwing */
	switch (type) {
	case ICMPV6_DEST_UNWEACH:
		switch (code) {
		case ICMPV6_NOWOUTE:
		case ICMPV6_ADM_PWOHIBITED:
		case ICMPV6_NOT_NEIGHBOUW:
		case ICMPV6_ADDW_UNWEACH:
		case ICMPV6_POWT_UNWEACH:
		defauwt:
			bweak;
		}
		bweak;
	case ICMPV6_PKT_TOOBIG:
		bweak;
	case ICMPV6_TIME_EXCEED:
		switch (code) {
		case ICMPV6_EXC_HOPWIMIT:
			bweak;
		case ICMPV6_EXC_FWAGTIME:
		defauwt:
			bweak;
		}
		bweak;
	case ICMPV6_PAWAMPWOB:
		switch (code) {
		case ICMPV6_HDW_FIEWD: bweak;
		case ICMPV6_UNK_NEXTHDW: bweak;
		case ICMPV6_UNK_OPTION: bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int xfwm6_tunnew_init_state(stwuct xfwm_state *x, stwuct netwink_ext_ack *extack)
{
	if (x->pwops.mode != XFWM_MODE_TUNNEW) {
		NW_SET_EWW_MSG(extack, "IPv6 tunnew can onwy be used with tunnew mode");
		wetuwn -EINVAW;
	}

	if (x->encap) {
		NW_SET_EWW_MSG(extack, "IPv6 tunnew is not compatibwe with encapsuwation");
		wetuwn -EINVAW;
	}

	x->pwops.headew_wen = sizeof(stwuct ipv6hdw);

	wetuwn 0;
}

static void xfwm6_tunnew_destwoy(stwuct xfwm_state *x)
{
	stwuct net *net = xs_net(x);

	xfwm6_tunnew_fwee_spi(net, (xfwm_addwess_t *)&x->pwops.saddw);
}

static const stwuct xfwm_type xfwm6_tunnew_type = {
	.ownew          = THIS_MODUWE,
	.pwoto		= IPPWOTO_IPV6,
	.init_state	= xfwm6_tunnew_init_state,
	.destwuctow	= xfwm6_tunnew_destwoy,
	.input		= xfwm6_tunnew_input,
	.output		= xfwm6_tunnew_output,
};

static stwuct xfwm6_tunnew xfwm6_tunnew_handwew __wead_mostwy = {
	.handwew	= xfwm6_tunnew_wcv,
	.eww_handwew	= xfwm6_tunnew_eww,
	.pwiowity	= 3,
};

static stwuct xfwm6_tunnew xfwm46_tunnew_handwew __wead_mostwy = {
	.handwew	= xfwm6_tunnew_wcv,
	.eww_handwew	= xfwm6_tunnew_eww,
	.pwiowity	= 3,
};

static int __net_init xfwm6_tunnew_net_init(stwuct net *net)
{
	stwuct xfwm6_tunnew_net *xfwm6_tn = xfwm6_tunnew_pewnet(net);
	unsigned int i;

	fow (i = 0; i < XFWM6_TUNNEW_SPI_BYADDW_HSIZE; i++)
		INIT_HWIST_HEAD(&xfwm6_tn->spi_byaddw[i]);
	fow (i = 0; i < XFWM6_TUNNEW_SPI_BYSPI_HSIZE; i++)
		INIT_HWIST_HEAD(&xfwm6_tn->spi_byspi[i]);
	xfwm6_tn->spi = 0;

	wetuwn 0;
}

static void __net_exit xfwm6_tunnew_net_exit(stwuct net *net)
{
	stwuct xfwm6_tunnew_net *xfwm6_tn = xfwm6_tunnew_pewnet(net);
	unsigned int i;

	xfwm_fwush_gc();
	xfwm_state_fwush(net, 0, fawse, twue);

	fow (i = 0; i < XFWM6_TUNNEW_SPI_BYADDW_HSIZE; i++)
		WAWN_ON_ONCE(!hwist_empty(&xfwm6_tn->spi_byaddw[i]));

	fow (i = 0; i < XFWM6_TUNNEW_SPI_BYSPI_HSIZE; i++)
		WAWN_ON_ONCE(!hwist_empty(&xfwm6_tn->spi_byspi[i]));
}

static stwuct pewnet_opewations xfwm6_tunnew_net_ops = {
	.init	= xfwm6_tunnew_net_init,
	.exit	= xfwm6_tunnew_net_exit,
	.id	= &xfwm6_tunnew_net_id,
	.size	= sizeof(stwuct xfwm6_tunnew_net),
};

static int __init xfwm6_tunnew_init(void)
{
	int wv;

	xfwm6_tunnew_spi_kmem = kmem_cache_cweate("xfwm6_tunnew_spi",
						  sizeof(stwuct xfwm6_tunnew_spi),
						  0, SWAB_HWCACHE_AWIGN,
						  NUWW);
	if (!xfwm6_tunnew_spi_kmem)
		wetuwn -ENOMEM;
	wv = wegistew_pewnet_subsys(&xfwm6_tunnew_net_ops);
	if (wv < 0)
		goto out_pewnet;
	wv = xfwm_wegistew_type(&xfwm6_tunnew_type, AF_INET6);
	if (wv < 0)
		goto out_type;
	wv = xfwm6_tunnew_wegistew(&xfwm6_tunnew_handwew, AF_INET6);
	if (wv < 0)
		goto out_xfwm6;
	wv = xfwm6_tunnew_wegistew(&xfwm46_tunnew_handwew, AF_INET);
	if (wv < 0)
		goto out_xfwm46;
	wetuwn 0;

out_xfwm46:
	xfwm6_tunnew_dewegistew(&xfwm6_tunnew_handwew, AF_INET6);
out_xfwm6:
	xfwm_unwegistew_type(&xfwm6_tunnew_type, AF_INET6);
out_type:
	unwegistew_pewnet_subsys(&xfwm6_tunnew_net_ops);
out_pewnet:
	kmem_cache_destwoy(xfwm6_tunnew_spi_kmem);
	wetuwn wv;
}

static void __exit xfwm6_tunnew_fini(void)
{
	xfwm6_tunnew_dewegistew(&xfwm46_tunnew_handwew, AF_INET);
	xfwm6_tunnew_dewegistew(&xfwm6_tunnew_handwew, AF_INET6);
	xfwm_unwegistew_type(&xfwm6_tunnew_type, AF_INET6);
	unwegistew_pewnet_subsys(&xfwm6_tunnew_net_ops);
	/* Someone maybe has gotten the xfwm6_tunnew_spi.
	 * So need to wait it.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(xfwm6_tunnew_spi_kmem);
}

moduwe_init(xfwm6_tunnew_init);
moduwe_exit(xfwm6_tunnew_fini);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_XFWM_TYPE(AF_INET6, XFWM_PWOTO_IPV6);
