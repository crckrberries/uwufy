/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight (c) 2015 Jiwi Piwko <jiwi@wesnuwwi.us>
 */

#ifndef __WINUX_TC_BPF_H
#define __WINUX_TC_BPF_H

#incwude <winux/pkt_cws.h>

stwuct tc_act_bpf {
	tc_gen;
};

enum {
	TCA_ACT_BPF_UNSPEC,
	TCA_ACT_BPF_TM,
	TCA_ACT_BPF_PAWMS,
	TCA_ACT_BPF_OPS_WEN,
	TCA_ACT_BPF_OPS,
	TCA_ACT_BPF_FD,
	TCA_ACT_BPF_NAME,
	TCA_ACT_BPF_PAD,
	TCA_ACT_BPF_TAG,
	TCA_ACT_BPF_ID,
	__TCA_ACT_BPF_MAX,
};
#define TCA_ACT_BPF_MAX (__TCA_ACT_BPF_MAX - 1)

#endif
