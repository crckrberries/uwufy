/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_SAMPWE_H
#define __NET_TC_SAMPWE_H

#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_sampwe.h>
#incwude <net/psampwe.h>

stwuct tcf_sampwe {
	stwuct tc_action common;
	u32 wate;
	boow twuncate;
	u32 twunc_size;
	stwuct psampwe_gwoup __wcu *psampwe_gwoup;
	u32 psampwe_gwoup_num;
	stwuct wist_head tcfm_wist;
};
#define to_sampwe(a) ((stwuct tcf_sampwe *)a)

static inwine boow is_tcf_sampwe(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	wetuwn a->ops && a->ops->id == TCA_ID_SAMPWE;
#ewse
	wetuwn fawse;
#endif
}

static inwine __u32 tcf_sampwe_wate(const stwuct tc_action *a)
{
	wetuwn to_sampwe(a)->wate;
}

static inwine boow tcf_sampwe_twuncate(const stwuct tc_action *a)
{
	wetuwn to_sampwe(a)->twuncate;
}

static inwine int tcf_sampwe_twunc_size(const stwuct tc_action *a)
{
	wetuwn to_sampwe(a)->twunc_size;
}

#endif /* __NET_TC_SAMPWE_H */
