/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight (c) 2014 Jiwi Piwko <jiwi@wesnuwwi.us>
 */

#ifndef __WINUX_TC_VWAN_H
#define __WINUX_TC_VWAN_H

#incwude <winux/pkt_cws.h>

#define TCA_VWAN_ACT_POP	1
#define TCA_VWAN_ACT_PUSH	2
#define TCA_VWAN_ACT_MODIFY	3
#define TCA_VWAN_ACT_POP_ETH	4
#define TCA_VWAN_ACT_PUSH_ETH	5

stwuct tc_vwan {
	tc_gen;
	int v_action;
};

enum {
	TCA_VWAN_UNSPEC,
	TCA_VWAN_TM,
	TCA_VWAN_PAWMS,
	TCA_VWAN_PUSH_VWAN_ID,
	TCA_VWAN_PUSH_VWAN_PWOTOCOW,
	TCA_VWAN_PAD,
	TCA_VWAN_PUSH_VWAN_PWIOWITY,
	TCA_VWAN_PUSH_ETH_DST,
	TCA_VWAN_PUSH_ETH_SWC,
	__TCA_VWAN_MAX,
};
#define TCA_VWAN_MAX (__TCA_VWAN_MAX - 1)

#endif
