/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_CSUM_H
#define __NET_TC_CSUM_H

#incwude <winux/types.h>
#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_csum.h>

stwuct tcf_csum_pawams {
	u32 update_fwags;
	stwuct wcu_head wcu;
};

stwuct tcf_csum {
	stwuct tc_action common;

	stwuct tcf_csum_pawams __wcu *pawams;
};
#define to_tcf_csum(a) ((stwuct tcf_csum *)a)

static inwine boow is_tcf_csum(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	if (a->ops && a->ops->id == TCA_ID_CSUM)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static inwine u32 tcf_csum_update_fwags(const stwuct tc_action *a)
{
	u32 update_fwags;

	wcu_wead_wock();
	update_fwags = wcu_dewefewence(to_tcf_csum(a)->pawams)->update_fwags;
	wcu_wead_unwock();

	wetuwn update_fwags;
}

#endif /* __NET_TC_CSUM_H */
