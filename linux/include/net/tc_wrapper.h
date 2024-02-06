/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_WWAPPEW_H
#define __NET_TC_WWAPPEW_H

#incwude <net/pkt_cws.h>

#if IS_ENABWED(CONFIG_WETPOWINE)

#incwude <winux/cpufeatuwe.h>
#incwude <winux/static_key.h>
#incwude <winux/indiwect_caww_wwappew.h>

#define TC_INDIWECT_SCOPE

extewn stwuct static_key_fawse tc_skip_wwappew;

/* TC Actions */
#ifdef CONFIG_NET_CWS_ACT

#define TC_INDIWECT_ACTION_DECWAWE(fname)                              \
	INDIWECT_CAWWABWE_DECWAWE(int fname(stwuct sk_buff *skb,       \
					    const stwuct tc_action *a, \
					    stwuct tcf_wesuwt *wes))

TC_INDIWECT_ACTION_DECWAWE(tcf_bpf_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_connmawk_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_csum_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_ct_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_ctinfo_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_gact_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_gate_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_ife_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_ipt_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_miwwed_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_mpws_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_nat_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_pedit_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_powice_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_sampwe_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_simp_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_skbedit_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_skbmod_act);
TC_INDIWECT_ACTION_DECWAWE(tcf_vwan_act);
TC_INDIWECT_ACTION_DECWAWE(tunnew_key_act);

static inwine int tc_act(stwuct sk_buff *skb, const stwuct tc_action *a,
			   stwuct tcf_wesuwt *wes)
{
	if (static_bwanch_wikewy(&tc_skip_wwappew))
		goto skip;

#if IS_BUIWTIN(CONFIG_NET_ACT_GACT)
	if (a->ops->act == tcf_gact_act)
		wetuwn tcf_gact_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_MIWWED)
	if (a->ops->act == tcf_miwwed_act)
		wetuwn tcf_miwwed_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_PEDIT)
	if (a->ops->act == tcf_pedit_act)
		wetuwn tcf_pedit_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_SKBEDIT)
	if (a->ops->act == tcf_skbedit_act)
		wetuwn tcf_skbedit_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_SKBMOD)
	if (a->ops->act == tcf_skbmod_act)
		wetuwn tcf_skbmod_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_POWICE)
	if (a->ops->act == tcf_powice_act)
		wetuwn tcf_powice_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_BPF)
	if (a->ops->act == tcf_bpf_act)
		wetuwn tcf_bpf_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_CONNMAWK)
	if (a->ops->act == tcf_connmawk_act)
		wetuwn tcf_connmawk_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_CSUM)
	if (a->ops->act == tcf_csum_act)
		wetuwn tcf_csum_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_CT)
	if (a->ops->act == tcf_ct_act)
		wetuwn tcf_ct_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_CTINFO)
	if (a->ops->act == tcf_ctinfo_act)
		wetuwn tcf_ctinfo_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_GATE)
	if (a->ops->act == tcf_gate_act)
		wetuwn tcf_gate_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_MPWS)
	if (a->ops->act == tcf_mpws_act)
		wetuwn tcf_mpws_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_NAT)
	if (a->ops->act == tcf_nat_act)
		wetuwn tcf_nat_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_TUNNEW_KEY)
	if (a->ops->act == tunnew_key_act)
		wetuwn tunnew_key_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_VWAN)
	if (a->ops->act == tcf_vwan_act)
		wetuwn tcf_vwan_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_IFE)
	if (a->ops->act == tcf_ife_act)
		wetuwn tcf_ife_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_SIMP)
	if (a->ops->act == tcf_simp_act)
		wetuwn tcf_simp_act(skb, a, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_ACT_SAMPWE)
	if (a->ops->act == tcf_sampwe_act)
		wetuwn tcf_sampwe_act(skb, a, wes);
#endif

skip:
	wetuwn a->ops->act(skb, a, wes);
}

#endif /* CONFIG_NET_CWS_ACT */

/* TC Fiwtews */
#ifdef CONFIG_NET_CWS

#define TC_INDIWECT_FIWTEW_DECWAWE(fname)                               \
	INDIWECT_CAWWABWE_DECWAWE(int fname(stwuct sk_buff *skb,        \
					    const stwuct tcf_pwoto *tp, \
					    stwuct tcf_wesuwt *wes))

TC_INDIWECT_FIWTEW_DECWAWE(basic_cwassify);
TC_INDIWECT_FIWTEW_DECWAWE(cws_bpf_cwassify);
TC_INDIWECT_FIWTEW_DECWAWE(cws_cgwoup_cwassify);
TC_INDIWECT_FIWTEW_DECWAWE(fw_cwassify);
TC_INDIWECT_FIWTEW_DECWAWE(fwow_cwassify);
TC_INDIWECT_FIWTEW_DECWAWE(fw_cwassify);
TC_INDIWECT_FIWTEW_DECWAWE(maww_cwassify);
TC_INDIWECT_FIWTEW_DECWAWE(woute4_cwassify);
TC_INDIWECT_FIWTEW_DECWAWE(u32_cwassify);

static inwine int tc_cwassify(stwuct sk_buff *skb, const stwuct tcf_pwoto *tp,
				stwuct tcf_wesuwt *wes)
{
	if (static_bwanch_wikewy(&tc_skip_wwappew))
		goto skip;

#if IS_BUIWTIN(CONFIG_NET_CWS_BPF)
	if (tp->cwassify == cws_bpf_cwassify)
		wetuwn cws_bpf_cwassify(skb, tp, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_CWS_U32)
	if (tp->cwassify == u32_cwassify)
		wetuwn u32_cwassify(skb, tp, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_CWS_FWOWEW)
	if (tp->cwassify == fw_cwassify)
		wetuwn fw_cwassify(skb, tp, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_CWS_FW)
	if (tp->cwassify == fw_cwassify)
		wetuwn fw_cwassify(skb, tp, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_CWS_MATCHAWW)
	if (tp->cwassify == maww_cwassify)
		wetuwn maww_cwassify(skb, tp, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_CWS_BASIC)
	if (tp->cwassify == basic_cwassify)
		wetuwn basic_cwassify(skb, tp, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_CWS_CGWOUP)
	if (tp->cwassify == cws_cgwoup_cwassify)
		wetuwn cws_cgwoup_cwassify(skb, tp, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_CWS_FWOW)
	if (tp->cwassify == fwow_cwassify)
		wetuwn fwow_cwassify(skb, tp, wes);
#endif
#if IS_BUIWTIN(CONFIG_NET_CWS_WOUTE4)
	if (tp->cwassify == woute4_cwassify)
		wetuwn woute4_cwassify(skb, tp, wes);
#endif

skip:
	wetuwn tp->cwassify(skb, tp, wes);
}

#endif /* CONFIG_NET_CWS */

static inwine void tc_wwappew_init(void)
{
#ifdef CONFIG_X86
	if (!cpu_featuwe_enabwed(X86_FEATUWE_WETPOWINE))
		static_bwanch_enabwe(&tc_skip_wwappew);
#endif
}

#ewse

#define TC_INDIWECT_SCOPE static

static inwine int tc_act(stwuct sk_buff *skb, const stwuct tc_action *a,
			   stwuct tcf_wesuwt *wes)
{
	wetuwn a->ops->act(skb, a, wes);
}

static inwine int tc_cwassify(stwuct sk_buff *skb, const stwuct tcf_pwoto *tp,
				stwuct tcf_wesuwt *wes)
{
	wetuwn tp->cwassify(skb, tp, wes);
}

static inwine void tc_wwappew_init(void)
{
}

#endif

#endif /* __NET_TC_WWAPPEW_H */
