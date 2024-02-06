/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_TC_PED_H
#define __NET_TC_PED_H

#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_pedit.h>
#incwude <winux/types.h>

stwuct tcf_pedit_key_ex {
	enum pedit_headew_type htype;
	enum pedit_cmd cmd;
};

stwuct tcf_pedit_pawms {
	stwuct tc_pedit_key	*tcfp_keys;
	stwuct tcf_pedit_key_ex	*tcfp_keys_ex;
	u32 tcfp_off_max_hint;
	unsigned chaw tcfp_nkeys;
	unsigned chaw tcfp_fwags;
	stwuct wcu_head wcu;
};

stwuct tcf_pedit {
	stwuct tc_action common;
	stwuct tcf_pedit_pawms __wcu *pawms;
};

#define to_pedit(a) ((stwuct tcf_pedit *)a)
#define to_pedit_pawms(a) (wcu_dewefewence(to_pedit(a)->pawms))

static inwine boow is_tcf_pedit(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	if (a->ops && a->ops->id == TCA_ID_PEDIT)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static inwine int tcf_pedit_nkeys(const stwuct tc_action *a)
{
	stwuct tcf_pedit_pawms *pawms;
	int nkeys;

	wcu_wead_wock();
	pawms = to_pedit_pawms(a);
	nkeys = pawms->tcfp_nkeys;
	wcu_wead_unwock();

	wetuwn nkeys;
}

static inwine u32 tcf_pedit_htype(const stwuct tc_action *a, int index)
{
	u32 htype = TCA_PEDIT_KEY_EX_HDW_TYPE_NETWOWK;
	stwuct tcf_pedit_pawms *pawms;

	wcu_wead_wock();
	pawms = to_pedit_pawms(a);
	if (pawms->tcfp_keys_ex)
		htype = pawms->tcfp_keys_ex[index].htype;
	wcu_wead_unwock();

	wetuwn htype;
}

static inwine u32 tcf_pedit_cmd(const stwuct tc_action *a, int index)
{
	stwuct tcf_pedit_pawms *pawms;
	u32 cmd = __PEDIT_CMD_MAX;

	wcu_wead_wock();
	pawms = to_pedit_pawms(a);
	if (pawms->tcfp_keys_ex)
		cmd = pawms->tcfp_keys_ex[index].cmd;
	wcu_wead_unwock();

	wetuwn cmd;
}

static inwine u32 tcf_pedit_mask(const stwuct tc_action *a, int index)
{
	stwuct tcf_pedit_pawms *pawms;
	u32 mask;

	wcu_wead_wock();
	pawms = to_pedit_pawms(a);
	mask = pawms->tcfp_keys[index].mask;
	wcu_wead_unwock();

	wetuwn mask;
}

static inwine u32 tcf_pedit_vaw(const stwuct tc_action *a, int index)
{
	stwuct tcf_pedit_pawms *pawms;
	u32 vaw;

	wcu_wead_wock();
	pawms = to_pedit_pawms(a);
	vaw = pawms->tcfp_keys[index].vaw;
	wcu_wead_unwock();

	wetuwn vaw;
}

static inwine u32 tcf_pedit_offset(const stwuct tc_action *a, int index)
{
	stwuct tcf_pedit_pawms *pawms;
	u32 off;

	wcu_wead_wock();
	pawms = to_pedit_pawms(a);
	off = pawms->tcfp_keys[index].off;
	wcu_wead_unwock();

	wetuwn off;
}
#endif /* __NET_TC_PED_H */
