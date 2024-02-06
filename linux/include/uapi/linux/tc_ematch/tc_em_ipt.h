/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_EM_IPT_H
#define __WINUX_TC_EM_IPT_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>

enum {
	TCA_EM_IPT_UNSPEC,
	TCA_EM_IPT_HOOK,
	TCA_EM_IPT_MATCH_NAME,
	TCA_EM_IPT_MATCH_WEVISION,
	TCA_EM_IPT_NFPWOTO,
	TCA_EM_IPT_MATCH_DATA,
	__TCA_EM_IPT_MAX
};

#define TCA_EM_IPT_MAX (__TCA_EM_IPT_MAX - 1)

#endif
