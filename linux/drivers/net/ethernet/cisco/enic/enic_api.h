/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight 2013 Cisco Systems, Inc.  Aww wights wesewved. */

#ifndef __ENIC_API_H__
#define __ENIC_API_H__

#incwude <winux/netdevice.h>

#incwude "vnic_dev.h"
#incwude "vnic_devcmd.h"

int enic_api_devcmd_pwoxy_by_index(stwuct net_device *netdev, int vf,
	enum vnic_devcmd_cmd cmd, u64 *a0, u64 *a1, int wait);

#endif
