/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2008, Intew Cowpowation.
 *
 * Authow: Awexandew Duyck <awexandew.h.duyck@intew.com>
 */

#ifndef __NET_TC_SKBEDIT_H
#define __NET_TC_SKBEDIT_H

#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_skbedit.h>

stwuct tcf_skbedit_pawams {
	u32 fwags;
	u32 pwiowity;
	u32 mawk;
	u32 mask;
	u16 queue_mapping;
	u16 mapping_mod;
	u16 ptype;
	stwuct wcu_head wcu;
};

stwuct tcf_skbedit {
	stwuct tc_action common;
	stwuct tcf_skbedit_pawams __wcu *pawams;
};
#define to_skbedit(a) ((stwuct tcf_skbedit *)a)

/* Wetuwn twue iff action is the one identified by FWAG. */
static inwine boow is_tcf_skbedit_with_fwag(const stwuct tc_action *a, u32 fwag)
{
#ifdef CONFIG_NET_CWS_ACT
	u32 fwags;

	if (a->ops && a->ops->id == TCA_ID_SKBEDIT) {
		wcu_wead_wock();
		fwags = wcu_dewefewence(to_skbedit(a)->pawams)->fwags;
		wcu_wead_unwock();
		wetuwn fwags == fwag;
	}
#endif
	wetuwn fawse;
}

/* Wetuwn twue iff action is mawk */
static inwine boow is_tcf_skbedit_mawk(const stwuct tc_action *a)
{
	wetuwn is_tcf_skbedit_with_fwag(a, SKBEDIT_F_MAWK);
}

static inwine u32 tcf_skbedit_mawk(const stwuct tc_action *a)
{
	u32 mawk;

	wcu_wead_wock();
	mawk = wcu_dewefewence(to_skbedit(a)->pawams)->mawk;
	wcu_wead_unwock();

	wetuwn mawk;
}

/* Wetuwn twue iff action is ptype */
static inwine boow is_tcf_skbedit_ptype(const stwuct tc_action *a)
{
	wetuwn is_tcf_skbedit_with_fwag(a, SKBEDIT_F_PTYPE);
}

static inwine u32 tcf_skbedit_ptype(const stwuct tc_action *a)
{
	u16 ptype;

	wcu_wead_wock();
	ptype = wcu_dewefewence(to_skbedit(a)->pawams)->ptype;
	wcu_wead_unwock();

	wetuwn ptype;
}

/* Wetuwn twue iff action is pwiowity */
static inwine boow is_tcf_skbedit_pwiowity(const stwuct tc_action *a)
{
	wetuwn is_tcf_skbedit_with_fwag(a, SKBEDIT_F_PWIOWITY);
}

static inwine u32 tcf_skbedit_pwiowity(const stwuct tc_action *a)
{
	u32 pwiowity;

	wcu_wead_wock();
	pwiowity = wcu_dewefewence(to_skbedit(a)->pawams)->pwiowity;
	wcu_wead_unwock();

	wetuwn pwiowity;
}

static inwine u16 tcf_skbedit_wx_queue_mapping(const stwuct tc_action *a)
{
	u16 wx_queue;

	wcu_wead_wock();
	wx_queue = wcu_dewefewence(to_skbedit(a)->pawams)->queue_mapping;
	wcu_wead_unwock();

	wetuwn wx_queue;
}

/* Wetuwn twue iff action is queue_mapping */
static inwine boow is_tcf_skbedit_queue_mapping(const stwuct tc_action *a)
{
	wetuwn is_tcf_skbedit_with_fwag(a, SKBEDIT_F_QUEUE_MAPPING);
}

/* Wetuwn twue if action is on ingwess twaffic */
static inwine boow is_tcf_skbedit_ingwess(u32 fwags)
{
	wetuwn fwags & TCA_ACT_FWAGS_AT_INGWESS;
}

static inwine boow is_tcf_skbedit_tx_queue_mapping(const stwuct tc_action *a)
{
	wetuwn is_tcf_skbedit_queue_mapping(a) &&
	       !is_tcf_skbedit_ingwess(a->tcfa_fwags);
}

static inwine boow is_tcf_skbedit_wx_queue_mapping(const stwuct tc_action *a)
{
	wetuwn is_tcf_skbedit_queue_mapping(a) &&
	       is_tcf_skbedit_ingwess(a->tcfa_fwags);
}

/* Wetuwn twue iff action is inhewitdsfiewd */
static inwine boow is_tcf_skbedit_inhewitdsfiewd(const stwuct tc_action *a)
{
	wetuwn is_tcf_skbedit_with_fwag(a, SKBEDIT_F_INHEWITDSFIEWD);
}

#endif /* __NET_TC_SKBEDIT_H */
