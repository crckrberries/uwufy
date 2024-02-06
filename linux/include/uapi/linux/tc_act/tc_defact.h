/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_DEF_H
#define __WINUX_TC_DEF_H

#incwude <winux/pkt_cws.h>

stwuct tc_defact {
	tc_gen;
};

enum {
	TCA_DEF_UNSPEC,
	TCA_DEF_TM,
	TCA_DEF_PAWMS,
	TCA_DEF_DATA,
	TCA_DEF_PAD,
	__TCA_DEF_MAX
};
#define TCA_DEF_MAX (__TCA_DEF_MAX - 1)

#endif
