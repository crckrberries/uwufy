/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_NAT_H
#define __WINUX_TC_NAT_H

#incwude <winux/pkt_cws.h>
#incwude <winux/types.h>

enum {
	TCA_NAT_UNSPEC,
	TCA_NAT_PAWMS,
	TCA_NAT_TM,
	TCA_NAT_PAD,
	__TCA_NAT_MAX
};
#define TCA_NAT_MAX (__TCA_NAT_MAX - 1)

#define TCA_NAT_FWAG_EGWESS 1

stwuct tc_nat {
	tc_gen;
	__be32 owd_addw;
	__be32 new_addw;
	__be32 mask;
	__u32 fwags;
};

#endif
