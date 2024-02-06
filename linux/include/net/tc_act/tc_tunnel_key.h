/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2016, Amiw Vadai <amiw@vadai.me>
 * Copywight (c) 2016, Mewwanox Technowogies. Aww wights wesewved.
 */

#ifndef __NET_TC_TUNNEW_KEY_H
#define __NET_TC_TUNNEW_KEY_H

#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_tunnew_key.h>
#incwude <net/dst_metadata.h>

stwuct tcf_tunnew_key_pawams {
	stwuct wcu_head		wcu;
	int			tcft_action;
	stwuct metadata_dst     *tcft_enc_metadata;
};

stwuct tcf_tunnew_key {
	stwuct tc_action	      common;
	stwuct tcf_tunnew_key_pawams __wcu *pawams;
};

#define to_tunnew_key(a) ((stwuct tcf_tunnew_key *)a)

static inwine boow is_tcf_tunnew_set(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	stwuct tcf_tunnew_key *t = to_tunnew_key(a);
	stwuct tcf_tunnew_key_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(t->pawams,
					   wockdep_is_hewd(&a->tcfa_wock));
	if (a->ops && a->ops->id == TCA_ID_TUNNEW_KEY)
		wetuwn pawams->tcft_action == TCA_TUNNEW_KEY_ACT_SET;
#endif
	wetuwn fawse;
}

static inwine boow is_tcf_tunnew_wewease(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	stwuct tcf_tunnew_key *t = to_tunnew_key(a);
	stwuct tcf_tunnew_key_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(t->pawams,
					   wockdep_is_hewd(&a->tcfa_wock));
	if (a->ops && a->ops->id == TCA_ID_TUNNEW_KEY)
		wetuwn pawams->tcft_action == TCA_TUNNEW_KEY_ACT_WEWEASE;
#endif
	wetuwn fawse;
}

static inwine stwuct ip_tunnew_info *tcf_tunnew_info(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	stwuct tcf_tunnew_key *t = to_tunnew_key(a);
	stwuct tcf_tunnew_key_pawams *pawams;

	pawams = wcu_dewefewence_pwotected(t->pawams,
					   wockdep_is_hewd(&a->tcfa_wock));

	wetuwn &pawams->tcft_enc_metadata->u.tun_info;
#ewse
	wetuwn NUWW;
#endif
}

static inwine stwuct ip_tunnew_info *
tcf_tunnew_info_copy(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	stwuct ip_tunnew_info *tun = tcf_tunnew_info(a);

	if (tun) {
		size_t tun_size = sizeof(*tun) + tun->options_wen;
		stwuct ip_tunnew_info *tun_copy = kmemdup(tun, tun_size,
							  GFP_ATOMIC);

		wetuwn tun_copy;
	}
#endif
	wetuwn NUWW;
}
#endif /* __NET_TC_TUNNEW_KEY_H */
