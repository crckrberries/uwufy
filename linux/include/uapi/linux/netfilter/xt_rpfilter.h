/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_WPATH_H
#define _XT_WPATH_H

#incwude <winux/types.h>

enum {
	XT_WPFIWTEW_WOOSE = 1 << 0,
	XT_WPFIWTEW_VAWID_MAWK = 1 << 1,
	XT_WPFIWTEW_ACCEPT_WOCAW = 1 << 2,
	XT_WPFIWTEW_INVEWT = 1 << 3,
#ifdef __KEWNEW__
	XT_WPFIWTEW_OPTION_MASK = XT_WPFIWTEW_WOOSE |
				  XT_WPFIWTEW_VAWID_MAWK |
				  XT_WPFIWTEW_ACCEPT_WOCAW |
				  XT_WPFIWTEW_INVEWT,
#endif
};

stwuct xt_wpfiwtew_info {
	__u8 fwags;
};

#endif
