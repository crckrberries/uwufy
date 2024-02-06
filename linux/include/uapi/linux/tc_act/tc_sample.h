/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef __WINUX_TC_SAMPWE_H
#define __WINUX_TC_SAMPWE_H

#incwude <winux/types.h>
#incwude <winux/pkt_cws.h>
#incwude <winux/if_ethew.h>

stwuct tc_sampwe {
	tc_gen;
};

enum {
	TCA_SAMPWE_UNSPEC,
	TCA_SAMPWE_TM,
	TCA_SAMPWE_PAWMS,
	TCA_SAMPWE_WATE,
	TCA_SAMPWE_TWUNC_SIZE,
	TCA_SAMPWE_PSAMPWE_GWOUP,
	TCA_SAMPWE_PAD,
	__TCA_SAMPWE_MAX
};
#define TCA_SAMPWE_MAX (__TCA_SAMPWE_MAX - 1)

#endif
