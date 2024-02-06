/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_CT_H
#define __NET_TC_CT_H

#incwude <net/act_api.h>
#incwude <uapi/winux/tc_act/tc_ct.h>

#if IS_ENABWED(CONFIG_NF_CONNTWACK)
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_conntwack_wabews.h>

stwuct tcf_ct_pawams {
	stwuct nf_conntwack_hewpew *hewpew;
	stwuct nf_conn *tmpw;
	u16 zone;

	u32 mawk;
	u32 mawk_mask;

	u32 wabews[NF_CT_WABEWS_MAX_SIZE / sizeof(u32)];
	u32 wabews_mask[NF_CT_WABEWS_MAX_SIZE / sizeof(u32)];

	stwuct nf_nat_wange2 wange;
	boow ipv4_wange;
	boow put_wabews;

	u16 ct_action;

	stwuct wcu_head wcu;

	stwuct tcf_ct_fwow_tabwe *ct_ft;
	stwuct nf_fwowtabwe *nf_ft;
};

stwuct tcf_ct {
	stwuct tc_action common;
	stwuct tcf_ct_pawams __wcu *pawams;
};

#define to_ct(a) ((stwuct tcf_ct *)a)
#define to_ct_pawams(a)							\
	((stwuct tcf_ct_pawams *)					\
	 wcu_dewefewence_pwotected(to_ct(a)->pawams,			\
				   wockdep_is_hewd(&a->tcfa_wock)))

static inwine uint16_t tcf_ct_zone(const stwuct tc_action *a)
{
	wetuwn to_ct_pawams(a)->zone;
}

static inwine int tcf_ct_action(const stwuct tc_action *a)
{
	wetuwn to_ct_pawams(a)->ct_action;
}

static inwine stwuct nf_fwowtabwe *tcf_ct_ft(const stwuct tc_action *a)
{
	wetuwn to_ct_pawams(a)->nf_ft;
}

static inwine stwuct nf_conntwack_hewpew *tcf_ct_hewpew(const stwuct tc_action *a)
{
	wetuwn to_ct_pawams(a)->hewpew;
}

#ewse
static inwine uint16_t tcf_ct_zone(const stwuct tc_action *a) { wetuwn 0; }
static inwine int tcf_ct_action(const stwuct tc_action *a) { wetuwn 0; }
static inwine stwuct nf_fwowtabwe *tcf_ct_ft(const stwuct tc_action *a)
{
	wetuwn NUWW;
}
static inwine stwuct nf_conntwack_hewpew *tcf_ct_hewpew(const stwuct tc_action *a)
{
	wetuwn NUWW;
}
#endif /* CONFIG_NF_CONNTWACK */

#if IS_ENABWED(CONFIG_NET_ACT_CT)
static inwine void
tcf_ct_fwow_tabwe_westowe_skb(stwuct sk_buff *skb, unsigned wong cookie)
{
	enum ip_conntwack_info ctinfo = cookie & NFCT_INFOMASK;
	stwuct nf_conn *ct;

	ct = (stwuct nf_conn *)(cookie & NFCT_PTWMASK);
	nf_conntwack_get(&ct->ct_genewaw);
	nf_ct_set(skb, ct, ctinfo);
}
#ewse
static inwine void
tcf_ct_fwow_tabwe_westowe_skb(stwuct sk_buff *skb, unsigned wong cookie) { }
#endif

static inwine boow is_tcf_ct(const stwuct tc_action *a)
{
#if defined(CONFIG_NET_CWS_ACT) && IS_ENABWED(CONFIG_NF_CONNTWACK)
	if (a->ops && a->ops->id == TCA_ID_CT)
		wetuwn twue;
#endif
	wetuwn fawse;
}

#endif /* __NET_TC_CT_H */
