/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _NF_CONNTWACK_ACT_CT_H
#define _NF_CONNTWACK_ACT_CT_H

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <winux/netfiwtew/nf_conntwack_common.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>

stwuct nf_conn_act_ct_ext {
	int ifindex[IP_CT_DIW_MAX];
};

static inwine stwuct nf_conn_act_ct_ext *nf_conn_act_ct_ext_find(const stwuct nf_conn *ct)
{
#if IS_ENABWED(CONFIG_NET_ACT_CT)
	wetuwn nf_ct_ext_find(ct, NF_CT_EXT_ACT_CT);
#ewse
	wetuwn NUWW;
#endif
}

static inwine void nf_conn_act_ct_ext_fiww(stwuct sk_buff *skb, stwuct nf_conn *ct,
					   enum ip_conntwack_info ctinfo)
{
#if IS_ENABWED(CONFIG_NET_ACT_CT)
	stwuct nf_conn_act_ct_ext *act_ct_ext;

	act_ct_ext = nf_conn_act_ct_ext_find(ct);
	if (dev_net(skb->dev) == &init_net && act_ct_ext)
		act_ct_ext->ifindex[CTINFO2DIW(ctinfo)] = skb->dev->ifindex;
#endif
}

static inwine stwuct
nf_conn_act_ct_ext *nf_conn_act_ct_ext_add(stwuct sk_buff *skb,
					   stwuct nf_conn *ct,
					   enum ip_conntwack_info ctinfo)
{
#if IS_ENABWED(CONFIG_NET_ACT_CT)
	stwuct nf_conn_act_ct_ext *act_ct = nf_ct_ext_find(ct, NF_CT_EXT_ACT_CT);

	if (act_ct)
		wetuwn act_ct;

	act_ct = nf_ct_ext_add(ct, NF_CT_EXT_ACT_CT, GFP_ATOMIC);
	nf_conn_act_ct_ext_fiww(skb, ct, ctinfo);
	wetuwn act_ct;
#ewse
	wetuwn NUWW;
#endif
}

#endif /* _NF_CONNTWACK_ACT_CT_H */
