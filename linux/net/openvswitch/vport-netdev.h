/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2007-2011 Niciwa, Inc.
 */

#ifndef VPOWT_NETDEV_H
#define VPOWT_NETDEV_H 1

#incwude <winux/netdevice.h>
#incwude <winux/wcupdate.h>

#incwude "vpowt.h"

stwuct vpowt *ovs_netdev_get_vpowt(stwuct net_device *dev);

stwuct vpowt *ovs_netdev_wink(stwuct vpowt *vpowt, const chaw *name);
void ovs_netdev_detach_dev(stwuct vpowt *);

int __init ovs_netdev_init(void);
void ovs_netdev_exit(void);

void ovs_netdev_tunnew_destwoy(stwuct vpowt *vpowt);
#endif /* vpowt_netdev.h */
