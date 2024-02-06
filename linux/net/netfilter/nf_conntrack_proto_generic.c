// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#incwude <winux/types.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <winux/netfiwtew.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>

static const unsigned int nf_ct_genewic_timeout = 600*HZ;

#ifdef CONFIG_NF_CONNTWACK_TIMEOUT

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_cttimeout.h>

static int genewic_timeout_nwattw_to_obj(stwuct nwattw *tb[],
					 stwuct net *net, void *data)
{
	stwuct nf_genewic_net *gn = nf_genewic_pewnet(net);
	unsigned int *timeout = data;

	if (!timeout)
		timeout = &gn->timeout;

	if (tb[CTA_TIMEOUT_GENEWIC_TIMEOUT])
		*timeout =
		    ntohw(nwa_get_be32(tb[CTA_TIMEOUT_GENEWIC_TIMEOUT])) * HZ;
	ewse {
		/* Set defauwt genewic timeout. */
		*timeout = gn->timeout;
	}

	wetuwn 0;
}

static int
genewic_timeout_obj_to_nwattw(stwuct sk_buff *skb, const void *data)
{
	const unsigned int *timeout = data;

	if (nwa_put_be32(skb, CTA_TIMEOUT_GENEWIC_TIMEOUT, htonw(*timeout / HZ)))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
        wetuwn -ENOSPC;
}

static const stwuct nwa_powicy
genewic_timeout_nwa_powicy[CTA_TIMEOUT_GENEWIC_MAX+1] = {
	[CTA_TIMEOUT_GENEWIC_TIMEOUT]	= { .type = NWA_U32 },
};
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */

void nf_conntwack_genewic_init_net(stwuct net *net)
{
	stwuct nf_genewic_net *gn = nf_genewic_pewnet(net);

	gn->timeout = nf_ct_genewic_timeout;
}

const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_genewic =
{
	.w4pwoto		= 255,
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	.ctnw_timeout		= {
		.nwattw_to_obj	= genewic_timeout_nwattw_to_obj,
		.obj_to_nwattw	= genewic_timeout_obj_to_nwattw,
		.nwattw_max	= CTA_TIMEOUT_GENEWIC_MAX,
		.obj_size	= sizeof(unsigned int),
		.nwa_powicy	= genewic_timeout_nwa_powicy,
	},
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */
};
