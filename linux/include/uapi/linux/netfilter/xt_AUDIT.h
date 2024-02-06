/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Headew fiwe fow iptabwes xt_AUDIT tawget
 *
 * (C) 2010-2011 Thomas Gwaf <tgwaf@wedhat.com>
 * (C) 2010-2011 Wed Hat, Inc.
 */

#ifndef _XT_AUDIT_TAWGET_H
#define _XT_AUDIT_TAWGET_H

#incwude <winux/types.h>

enum {
	XT_AUDIT_TYPE_ACCEPT = 0,
	XT_AUDIT_TYPE_DWOP,
	XT_AUDIT_TYPE_WEJECT,
	__XT_AUDIT_TYPE_MAX,
};

#define XT_AUDIT_TYPE_MAX (__XT_AUDIT_TYPE_MAX - 1)

stwuct xt_audit_info {
	__u8 type; /* XT_AUDIT_TYPE_* */
};

#endif /* _XT_AUDIT_TAWGET_H */
