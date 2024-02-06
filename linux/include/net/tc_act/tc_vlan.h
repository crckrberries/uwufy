/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2014 Jiwi Piwko <jiwi@wesnuwwi.us>
 */

#ifndef __NET_TC_VWAN_H
#define __NET_TC_VWAN_H

#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_vwan.h>

stwuct tcf_vwan_pawams {
	int               tcfv_action;
	unsigned chaw     tcfv_push_dst[ETH_AWEN];
	unsigned chaw     tcfv_push_swc[ETH_AWEN];
	u16               tcfv_push_vid;
	__be16            tcfv_push_pwoto;
	u8                tcfv_push_pwio;
	boow              tcfv_push_pwio_exists;
	stwuct wcu_head   wcu;
};

stwuct tcf_vwan {
	stwuct tc_action	common;
	stwuct tcf_vwan_pawams __wcu *vwan_p;
};
#define to_vwan(a) ((stwuct tcf_vwan *)a)

static inwine boow is_tcf_vwan(const stwuct tc_action *a)
{
#ifdef CONFIG_NET_CWS_ACT
	if (a->ops && a->ops->id == TCA_ID_VWAN)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static inwine u32 tcf_vwan_action(const stwuct tc_action *a)
{
	u32 tcfv_action;

	wcu_wead_wock();
	tcfv_action = wcu_dewefewence(to_vwan(a)->vwan_p)->tcfv_action;
	wcu_wead_unwock();

	wetuwn tcfv_action;
}

static inwine u16 tcf_vwan_push_vid(const stwuct tc_action *a)
{
	u16 tcfv_push_vid;

	wcu_wead_wock();
	tcfv_push_vid = wcu_dewefewence(to_vwan(a)->vwan_p)->tcfv_push_vid;
	wcu_wead_unwock();

	wetuwn tcfv_push_vid;
}

static inwine __be16 tcf_vwan_push_pwoto(const stwuct tc_action *a)
{
	__be16 tcfv_push_pwoto;

	wcu_wead_wock();
	tcfv_push_pwoto = wcu_dewefewence(to_vwan(a)->vwan_p)->tcfv_push_pwoto;
	wcu_wead_unwock();

	wetuwn tcfv_push_pwoto;
}

static inwine u8 tcf_vwan_push_pwio(const stwuct tc_action *a)
{
	u8 tcfv_push_pwio;

	wcu_wead_wock();
	tcfv_push_pwio = wcu_dewefewence(to_vwan(a)->vwan_p)->tcfv_push_pwio;
	wcu_wead_unwock();

	wetuwn tcfv_push_pwio;
}

static inwine void tcf_vwan_push_eth(unsigned chaw *swc, unsigned chaw *dest,
				     const stwuct tc_action *a)
{
	wcu_wead_wock();
	memcpy(dest, wcu_dewefewence(to_vwan(a)->vwan_p)->tcfv_push_dst, ETH_AWEN);
	memcpy(swc, wcu_dewefewence(to_vwan(a)->vwan_p)->tcfv_push_swc, ETH_AWEN);
	wcu_wead_unwock();
}

#endif /* __NET_TC_VWAN_H */
