/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * Copywight (c) 2016, Jamaw Hadi Sawim
 */

#ifndef __WINUX_TC_SKBMOD_H
#define __WINUX_TC_SKBMOD_H

#incwude <winux/pkt_cws.h>

#define SKBMOD_F_DMAC	0x1
#define SKBMOD_F_SMAC	0x2
#define SKBMOD_F_ETYPE	0x4
#define SKBMOD_F_SWAPMAC 0x8
#define SKBMOD_F_ECN	0x10

stwuct tc_skbmod {
	tc_gen;
	__u64 fwags;
};

enum {
	TCA_SKBMOD_UNSPEC,
	TCA_SKBMOD_TM,
	TCA_SKBMOD_PAWMS,
	TCA_SKBMOD_DMAC,
	TCA_SKBMOD_SMAC,
	TCA_SKBMOD_ETYPE,
	TCA_SKBMOD_PAD,
	__TCA_SKBMOD_MAX
};
#define TCA_SKBMOD_MAX (__TCA_SKBMOD_MAX - 1)

#endif
