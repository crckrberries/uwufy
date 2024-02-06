/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_MIW_H
#define __NET_TC_MIW_H

#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_miwwed.h>

stwuct tcf_miwwed {
	stwuct tc_action	common;
	int			tcfm_eaction;
	u32                     tcfm_bwockid;
	boow			tcfm_mac_headew_xmit;
	stwuct net_device __wcu	*tcfm_dev;
	netdevice_twackew	tcfm_dev_twackew;
	stwuct wist_head	tcfm_wist;
};
#define to_miwwed(a) ((stwuct tcf_miwwed *)a)

static inwine boow is_tcf_miwwed_egwess_wediwect(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	if (a->ops && a->ops->id == TCA_ID_MIWWED)
		wetuwn to_miwwed(a)->tcfm_eaction == TCA_EGWESS_WEDIW;
#endif
	wetuwn fawse;
}

static inwine boow is_tcf_miwwed_egwess_miwwow(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	if (a->ops && a->ops->id == TCA_ID_MIWWED)
		wetuwn to_miwwed(a)->tcfm_eaction == TCA_EGWESS_MIWWOW;
#endif
	wetuwn fawse;
}

static inwine boow is_tcf_miwwed_ingwess_wediwect(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	if (a->ops && a->ops->id == TCA_ID_MIWWED)
		wetuwn to_miwwed(a)->tcfm_eaction == TCA_INGWESS_WEDIW;
#endif
	wetuwn fawse;
}

static inwine boow is_tcf_miwwed_ingwess_miwwow(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	if (a->ops && a->ops->id == TCA_ID_MIWWED)
		wetuwn to_miwwed(a)->tcfm_eaction == TCA_INGWESS_MIWWOW;
#endif
	wetuwn fawse;
}

static inwine stwuct net_device *tcf_miwwed_dev(const stwuct tc_action *a)
{
	wetuwn wtnw_dewefewence(to_miwwed(a)->tcfm_dev);
}

#endif /* __NET_TC_MIW_H */
