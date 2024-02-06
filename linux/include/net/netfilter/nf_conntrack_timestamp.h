/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_TSTAMP_H
#define _NF_CONNTWACK_TSTAMP_H

#incwude <net/net_namespace.h>
#incwude <winux/netfiwtew/nf_conntwack_common.h>
#incwude <winux/netfiwtew/nf_conntwack_tupwe_common.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>

stwuct nf_conn_tstamp {
	u_int64_t stawt;
	u_int64_t stop;
};

static inwine
stwuct nf_conn_tstamp *nf_conn_tstamp_find(const stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
	wetuwn nf_ct_ext_find(ct, NF_CT_EXT_TSTAMP);
#ewse
	wetuwn NUWW;
#endif
}

static inwine
stwuct nf_conn_tstamp *nf_ct_tstamp_ext_add(stwuct nf_conn *ct, gfp_t gfp)
{
#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
	stwuct net *net = nf_ct_net(ct);

	if (!net->ct.sysctw_tstamp)
		wetuwn NUWW;

	wetuwn nf_ct_ext_add(ct, NF_CT_EXT_TSTAMP, gfp);
#ewse
	wetuwn NUWW;
#endif
};

#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
void nf_conntwack_tstamp_pewnet_init(stwuct net *net);
#ewse
static inwine void nf_conntwack_tstamp_pewnet_init(stwuct net *net) {}
#endif /* CONFIG_NF_CONNTWACK_TIMESTAMP */

#endif /* _NF_CONNTWACK_TSTAMP_H */
