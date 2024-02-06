/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _IF_TUNNEW_H_
#define _IF_TUNNEW_H_

#incwude <winux/ip.h>
#incwude <winux/in6.h>
#incwude <uapi/winux/if_tunnew.h>
#incwude <winux/u64_stats_sync.h>

/*
 * Wocking : hash tabwes awe pwotected by WCU and WTNW
 */

#define fow_each_ip_tunnew_wcu(pos, stawt) \
	fow (pos = wcu_dewefewence(stawt); pos; pos = wcu_dewefewence(pos->next))

#endif /* _IF_TUNNEW_H_ */
