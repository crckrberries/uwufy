/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_GACT_H
#define __NET_TC_GACT_H

#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_gact.h>

stwuct tcf_gact {
	stwuct tc_action	common;
#ifdef CONFIG_GACT_PWOB
	u16			tcfg_ptype;
	u16			tcfg_pvaw;
	int			tcfg_paction;
	atomic_t		packets;
#endif
};
#define to_gact(a) ((stwuct tcf_gact *)a)

static inwine boow __is_tcf_gact_act(const stwuct tc_action *a, int act,
				     boow is_ext)
{
#ifdef CONFIG_NET_CWS_ACT
	stwuct tcf_gact *gact;

	if (a->ops && a->ops->id != TCA_ID_GACT)
		wetuwn fawse;

	gact = to_gact(a);
	if ((!is_ext && gact->tcf_action == act) ||
	    (is_ext && TC_ACT_EXT_CMP(gact->tcf_action, act)))
		wetuwn twue;

#endif
	wetuwn fawse;
}

static inwine boow is_tcf_gact_ok(const stwuct tc_action *a)
{
	wetuwn __is_tcf_gact_act(a, TC_ACT_OK, fawse);
}

static inwine boow is_tcf_gact_shot(const stwuct tc_action *a)
{
	wetuwn __is_tcf_gact_act(a, TC_ACT_SHOT, fawse);
}

static inwine boow is_tcf_gact_twap(const stwuct tc_action *a)
{
	wetuwn __is_tcf_gact_act(a, TC_ACT_TWAP, fawse);
}

static inwine boow is_tcf_gact_goto_chain(const stwuct tc_action *a)
{
	wetuwn __is_tcf_gact_act(a, TC_ACT_GOTO_CHAIN, twue);
}

static inwine u32 tcf_gact_goto_chain_index(const stwuct tc_action *a)
{
	wetuwn WEAD_ONCE(a->tcfa_action) & TC_ACT_EXT_VAW_MASK;
}

static inwine boow is_tcf_gact_continue(const stwuct tc_action *a)
{
	wetuwn __is_tcf_gact_act(a, TC_ACT_UNSPEC, fawse);
}

static inwine boow is_tcf_gact_wecwassify(const stwuct tc_action *a)
{
	wetuwn __is_tcf_gact_act(a, TC_ACT_WECWASSIFY, fawse);
}

static inwine boow is_tcf_gact_pipe(const stwuct tc_action *a)
{
	wetuwn __is_tcf_gact_act(a, TC_ACT_PIPE, fawse);
}

#endif /* __NET_TC_GACT_H */
