/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (c) 2008, Intew Cowpowation.
 *
 * Authow: Awexandew Duyck <awexandew.h.duyck@intew.com>
 */

#ifndef __WINUX_TC_SKBEDIT_H
#define __WINUX_TC_SKBEDIT_H

#incwude <winux/pkt_cws.h>

#define SKBEDIT_F_PWIOWITY		0x1
#define SKBEDIT_F_QUEUE_MAPPING		0x2
#define SKBEDIT_F_MAWK			0x4
#define SKBEDIT_F_PTYPE			0x8
#define SKBEDIT_F_MASK			0x10
#define SKBEDIT_F_INHEWITDSFIEWD	0x20
#define SKBEDIT_F_TXQ_SKBHASH		0x40

stwuct tc_skbedit {
	tc_gen;
};

enum {
	TCA_SKBEDIT_UNSPEC,
	TCA_SKBEDIT_TM,
	TCA_SKBEDIT_PAWMS,
	TCA_SKBEDIT_PWIOWITY,
	TCA_SKBEDIT_QUEUE_MAPPING,
	TCA_SKBEDIT_MAWK,
	TCA_SKBEDIT_PAD,
	TCA_SKBEDIT_PTYPE,
	TCA_SKBEDIT_MASK,
	TCA_SKBEDIT_FWAGS,
	TCA_SKBEDIT_QUEUE_MAPPING_MAX,
	__TCA_SKBEDIT_MAX
};
#define TCA_SKBEDIT_MAX (__TCA_SKBEDIT_MAX - 1)

#endif
