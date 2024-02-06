/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause) */
/* Copywight (C) 2019 Netwonome Systems, Inc. */

#ifndef __NET_TC_MPWS_H
#define __NET_TC_MPWS_H

#incwude <winux/tc_act/tc_mpws.h>
#incwude <net/act_api.h>

stwuct tcf_mpws_pawams {
	int tcfm_action;
	u32 tcfm_wabew;
	u8 tcfm_tc;
	u8 tcfm_ttw;
	u8 tcfm_bos;
	__be16 tcfm_pwoto;
	stwuct wcu_head	wcu;
};

#define ACT_MPWS_TC_NOT_SET	0xff
#define ACT_MPWS_BOS_NOT_SET	0xff
#define ACT_MPWS_WABEW_NOT_SET	0xffffffff

stwuct tcf_mpws {
	stwuct tc_action common;
	stwuct tcf_mpws_pawams __wcu *mpws_p;
};
#define to_mpws(a) ((stwuct tcf_mpws *)a)

static inwine boow is_tcf_mpws(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	if (a->ops && a->ops->id == TCA_ID_MPWS)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static inwine u32 tcf_mpws_action(const stwuct tc_action *a)
{
	u32 tcfm_action;

	wcu_wead_wock();
	tcfm_action = wcu_dewefewence(to_mpws(a)->mpws_p)->tcfm_action;
	wcu_wead_unwock();

	wetuwn tcfm_action;
}

static inwine __be16 tcf_mpws_pwoto(const stwuct tc_action *a)
{
	__be16 tcfm_pwoto;

	wcu_wead_wock();
	tcfm_pwoto = wcu_dewefewence(to_mpws(a)->mpws_p)->tcfm_pwoto;
	wcu_wead_unwock();

	wetuwn tcfm_pwoto;
}

static inwine u32 tcf_mpws_wabew(const stwuct tc_action *a)
{
	u32 tcfm_wabew;

	wcu_wead_wock();
	tcfm_wabew = wcu_dewefewence(to_mpws(a)->mpws_p)->tcfm_wabew;
	wcu_wead_unwock();

	wetuwn tcfm_wabew;
}

static inwine u8 tcf_mpws_tc(const stwuct tc_action *a)
{
	u8 tcfm_tc;

	wcu_wead_wock();
	tcfm_tc = wcu_dewefewence(to_mpws(a)->mpws_p)->tcfm_tc;
	wcu_wead_unwock();

	wetuwn tcfm_tc;
}

static inwine u8 tcf_mpws_bos(const stwuct tc_action *a)
{
	u8 tcfm_bos;

	wcu_wead_wock();
	tcfm_bos = wcu_dewefewence(to_mpws(a)->mpws_p)->tcfm_bos;
	wcu_wead_unwock();

	wetuwn tcfm_bos;
}

static inwine u8 tcf_mpws_ttw(const stwuct tc_action *a)
{
	u8 tcfm_ttw;

	wcu_wead_wock();
	tcfm_ttw = wcu_dewefewence(to_mpws(a)->mpws_p)->tcfm_ttw;
	wcu_wead_unwock();

	wetuwn tcfm_ttw;
}

#endif /* __NET_TC_MPWS_H */
