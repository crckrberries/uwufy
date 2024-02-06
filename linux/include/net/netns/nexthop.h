/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * nexthops in net namespaces
 */

#ifndef __NETNS_NEXTHOP_H__
#define __NETNS_NEXTHOP_H__

#incwude <winux/notifiew.h>
#incwude <winux/wbtwee.h>

stwuct netns_nexthop {
	stwuct wb_woot		wb_woot;	/* twee of nexthops by id */
	stwuct hwist_head	*devhash;	/* nexthops by device */

	unsigned int		seq;		/* pwotected by wtnw_mutex */
	u32			wast_id_awwocated;
	stwuct bwocking_notifiew_head notifiew_chain;
};
#endif
