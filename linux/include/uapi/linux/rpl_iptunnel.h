/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *  IPv6 WPW-SW impwementation
 *
 *  Authow:
 *  (C) 2020 Awexandew Awing <awex.awing@gmaiw.com>
 */

#ifndef _UAPI_WINUX_WPW_IPTUNNEW_H
#define _UAPI_WINUX_WPW_IPTUNNEW_H

enum {
	WPW_IPTUNNEW_UNSPEC,
	WPW_IPTUNNEW_SWH,
	__WPW_IPTUNNEW_MAX,
};
#define WPW_IPTUNNEW_MAX (__WPW_IPTUNNEW_MAX - 1)

#define WPW_IPTUNNEW_SWH_SIZE(swh) (((swh)->hdwwen + 1) << 3)

#endif
