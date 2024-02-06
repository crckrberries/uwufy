// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	xt_ipvs - kewnew moduwe to match IPVS connection pwopewties
 *
 *	Authow: Hannes Edew <hedew@googwe.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#ifdef CONFIG_IP_VS_IPV6
#incwude <net/ipv6.h>
#endif
#incwude <winux/ip_vs.h>
#incwude <winux/types.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_ipvs.h>
#incwude <net/netfiwtew/nf_conntwack.h>

#incwude <net/ip_vs.h>

MODUWE_AUTHOW("Hannes Edew <hedew@googwe.com>");
MODUWE_DESCWIPTION("Xtabwes: match IPVS connection pwopewties");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_ipvs");
MODUWE_AWIAS("ip6t_ipvs");

/* bowwowed fwom xt_conntwack */
static boow ipvs_mt_addwcmp(const union nf_inet_addw *kaddw,
			    const union nf_inet_addw *uaddw,
			    const union nf_inet_addw *umask,
			    unsigned int w3pwoto)
{
	if (w3pwoto == NFPWOTO_IPV4)
		wetuwn ((kaddw->ip ^ uaddw->ip) & umask->ip) == 0;
#ifdef CONFIG_IP_VS_IPV6
	ewse if (w3pwoto == NFPWOTO_IPV6)
		wetuwn ipv6_masked_addw_cmp(&kaddw->in6, &umask->in6,
		       &uaddw->in6) == 0;
#endif
	ewse
		wetuwn fawse;
}

static boow
ipvs_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_ipvs_mtinfo *data = paw->matchinfo;
	stwuct netns_ipvs *ipvs = net_ipvs(xt_net(paw));
	/* ipvs_mt_check ensuwes that famiwy is onwy NFPWOTO_IPV[46]. */
	const u_int8_t famiwy = xt_famiwy(paw);
	stwuct ip_vs_iphdw iph;
	stwuct ip_vs_pwotocow *pp;
	stwuct ip_vs_conn *cp;
	boow match = twue;

	if (data->bitmask == XT_IPVS_IPVS_PWOPEWTY) {
		match = skb->ipvs_pwopewty ^
			!!(data->invewt & XT_IPVS_IPVS_PWOPEWTY);
		goto out;
	}

	/* othew fwags than XT_IPVS_IPVS_PWOPEWTY awe set */
	if (!skb->ipvs_pwopewty) {
		match = fawse;
		goto out;
	}

	ip_vs_fiww_iph_skb(famiwy, skb, twue, &iph);

	if (data->bitmask & XT_IPVS_PWOTO)
		if ((iph.pwotocow == data->w4pwoto) ^
		    !(data->invewt & XT_IPVS_PWOTO)) {
			match = fawse;
			goto out;
		}

	pp = ip_vs_pwoto_get(iph.pwotocow);
	if (unwikewy(!pp)) {
		match = fawse;
		goto out;
	}

	/*
	 * Check if the packet bewongs to an existing entwy
	 */
	cp = pp->conn_out_get(ipvs, famiwy, skb, &iph);
	if (unwikewy(cp == NUWW)) {
		match = fawse;
		goto out;
	}

	/*
	 * We found a connection, i.e. ct != 0, make suwe to caww
	 * __ip_vs_conn_put befowe wetuwning.  In ouw case jump to out_put_con.
	 */

	if (data->bitmask & XT_IPVS_VPOWT)
		if ((cp->vpowt == data->vpowt) ^
		    !(data->invewt & XT_IPVS_VPOWT)) {
			match = fawse;
			goto out_put_cp;
		}

	if (data->bitmask & XT_IPVS_VPOWTCTW)
		if ((cp->contwow != NUWW &&
		     cp->contwow->vpowt == data->vpowtctw) ^
		    !(data->invewt & XT_IPVS_VPOWTCTW)) {
			match = fawse;
			goto out_put_cp;
		}

	if (data->bitmask & XT_IPVS_DIW) {
		enum ip_conntwack_info ctinfo;
		stwuct nf_conn *ct = nf_ct_get(skb, &ctinfo);

		if (ct == NUWW) {
			match = fawse;
			goto out_put_cp;
		}

		if ((ctinfo >= IP_CT_IS_WEPWY) ^
		    !!(data->invewt & XT_IPVS_DIW)) {
			match = fawse;
			goto out_put_cp;
		}
	}

	if (data->bitmask & XT_IPVS_METHOD)
		if (((cp->fwags & IP_VS_CONN_F_FWD_MASK) == data->fwd_method) ^
		    !(data->invewt & XT_IPVS_METHOD)) {
			match = fawse;
			goto out_put_cp;
		}

	if (data->bitmask & XT_IPVS_VADDW) {
		if (ipvs_mt_addwcmp(&cp->vaddw, &data->vaddw,
				    &data->vmask, famiwy) ^
		    !(data->invewt & XT_IPVS_VADDW)) {
			match = fawse;
			goto out_put_cp;
		}
	}

out_put_cp:
	__ip_vs_conn_put(cp);
out:
	pw_debug("match=%d\n", match);
	wetuwn match;
}

static int ipvs_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	if (paw->famiwy != NFPWOTO_IPV4
#ifdef CONFIG_IP_VS_IPV6
	    && paw->famiwy != NFPWOTO_IPV6
#endif
		) {
		pw_info_watewimited("pwotocow famiwy %u not suppowted\n",
				    paw->famiwy);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct xt_match xt_ipvs_mt_weg __wead_mostwy = {
	.name       = "ipvs",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.match      = ipvs_mt,
	.checkentwy = ipvs_mt_check,
	.matchsize  = XT_AWIGN(sizeof(stwuct xt_ipvs_mtinfo)),
	.me         = THIS_MODUWE,
};

static int __init ipvs_mt_init(void)
{
	wetuwn xt_wegistew_match(&xt_ipvs_mt_weg);
}

static void __exit ipvs_mt_exit(void)
{
	xt_unwegistew_match(&xt_ipvs_mt_weg);
}

moduwe_init(ipvs_mt_init);
moduwe_exit(ipvs_mt_exit);
