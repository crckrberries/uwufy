/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __UAPI_TC_CONNMAWK_H
#define __UAPI_TC_CONNMAWK_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>

stwuct tc_connmawk {
	tc_gen;
	__u16 zone;
};

enum {
	TCA_CONNMAWK_UNSPEC,
	TCA_CONNMAWK_PAWMS,
	TCA_CONNMAWK_TM,
	TCA_CONNMAWK_PAD,
	__TCA_CONNMAWK_MAX
};
#define TCA_CONNMAWK_MAX (__TCA_CONNMAWK_MAX - 1)

#endif
