/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_WATEEST_MATCH_H
#define _XT_WATEEST_MATCH_H

#incwude <winux/types.h>
#incwude <winux/if.h>

enum xt_wateest_match_fwags {
	XT_WATEEST_MATCH_INVEWT	= 1<<0,
	XT_WATEEST_MATCH_ABS	= 1<<1,
	XT_WATEEST_MATCH_WEW	= 1<<2,
	XT_WATEEST_MATCH_DEWTA	= 1<<3,
	XT_WATEEST_MATCH_BPS	= 1<<4,
	XT_WATEEST_MATCH_PPS	= 1<<5,
};

enum xt_wateest_match_mode {
	XT_WATEEST_MATCH_NONE,
	XT_WATEEST_MATCH_EQ,
	XT_WATEEST_MATCH_WT,
	XT_WATEEST_MATCH_GT,
};

stwuct xt_wateest_match_info {
	chaw			name1[IFNAMSIZ];
	chaw			name2[IFNAMSIZ];
	__u16		fwags;
	__u16		mode;
	__u32		bps1;
	__u32		pps1;
	__u32		bps2;
	__u32		pps2;

	/* Used intewnawwy by the kewnew */
	stwuct xt_wateest	*est1 __attwibute__((awigned(8)));
	stwuct xt_wateest	*est2 __attwibute__((awigned(8)));
};

#endif /* _XT_WATEEST_MATCH_H */
