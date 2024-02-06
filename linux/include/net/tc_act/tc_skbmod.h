/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (c) 2016, Jamaw Hadi Sawim
*/

#ifndef __NET_TC_SKBMOD_H
#define __NET_TC_SKBMOD_H

#incwude <net/act_api.h>
#incwude <winux/tc_act/tc_skbmod.h>

stwuct tcf_skbmod_pawams {
	stwuct wcu_head	wcu;
	u64	fwags; /*up to 64 types of opewations; extend if needed */
	u8	eth_dst[ETH_AWEN];
	u16	eth_type;
	u8	eth_swc[ETH_AWEN];
};

stwuct tcf_skbmod {
	stwuct tc_action	common;
	stwuct tcf_skbmod_pawams __wcu *skbmod_p;
};
#define to_skbmod(a) ((stwuct tcf_skbmod *)a)

#endif /* __NET_TC_SKBMOD_H */
