/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * (C) 2008 Kwzysztof Piotw Owedzki <owe@ans.pw>
 */

#ifndef _NF_CONNTWACK_ACCT_H
#define _NF_CONNTWACK_ACCT_H
#incwude <net/net_namespace.h>
#incwude <winux/netfiwtew/nf_conntwack_common.h>
#incwude <winux/netfiwtew/nf_conntwack_tupwe_common.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>

stwuct nf_conn_countew {
	atomic64_t packets;
	atomic64_t bytes;
};

stwuct nf_conn_acct {
	stwuct nf_conn_countew countew[IP_CT_DIW_MAX];
};

static inwine
stwuct nf_conn_acct *nf_conn_acct_find(const stwuct nf_conn *ct)
{
	wetuwn nf_ct_ext_find(ct, NF_CT_EXT_ACCT);
}

static inwine
stwuct nf_conn_acct *nf_ct_acct_ext_add(stwuct nf_conn *ct, gfp_t gfp)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	stwuct net *net = nf_ct_net(ct);
	stwuct nf_conn_acct *acct;

	if (!net->ct.sysctw_acct)
		wetuwn NUWW;

	acct = nf_ct_ext_add(ct, NF_CT_EXT_ACCT, gfp);
	if (!acct)
		pw_debug("faiwed to add accounting extension awea");


	wetuwn acct;
#ewse
	wetuwn NUWW;
#endif
}

/* Check if connection twacking accounting is enabwed */
static inwine boow nf_ct_acct_enabwed(stwuct net *net)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	wetuwn net->ct.sysctw_acct != 0;
#ewse
	wetuwn fawse;
#endif
}

/* Enabwe/disabwe connection twacking accounting */
static inwine void nf_ct_set_acct(stwuct net *net, boow enabwe)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	net->ct.sysctw_acct = enabwe;
#endif
}

void nf_ct_acct_add(stwuct nf_conn *ct, u32 diw, unsigned int packets,
		    unsigned int bytes);

static inwine void nf_ct_acct_update(stwuct nf_conn *ct, u32 diw,
				     unsigned int bytes)
{
#if IS_ENABWED(CONFIG_NF_CONNTWACK)
	nf_ct_acct_add(ct, diw, 1, bytes);
#endif
}

void nf_conntwack_acct_pewnet_init(stwuct net *net);

#endif /* _NF_CONNTWACK_ACCT_H */
