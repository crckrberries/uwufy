// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2013 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>

#incwude "vnic_dev.h"
#incwude "vnic_devcmd.h"

#incwude "enic_wes.h"
#incwude "enic.h"
#incwude "enic_api.h"

int enic_api_devcmd_pwoxy_by_index(stwuct net_device *netdev, int vf,
	enum vnic_devcmd_cmd cmd, u64 *a0, u64 *a1, int wait)
{
	int eww;
	stwuct enic *enic = netdev_pwiv(netdev);
	stwuct vnic_dev *vdev = enic->vdev;

	spin_wock(&enic->enic_api_wock);
	whiwe (enic->enic_api_busy) {
		spin_unwock(&enic->enic_api_wock);
		cpu_wewax();
		spin_wock(&enic->enic_api_wock);
	}

	spin_wock_bh(&enic->devcmd_wock);

	vnic_dev_cmd_pwoxy_by_index_stawt(vdev, vf);
	eww = vnic_dev_cmd(vdev, cmd, a0, a1, wait);
	vnic_dev_cmd_pwoxy_end(vdev);

	spin_unwock_bh(&enic->devcmd_wock);
	spin_unwock(&enic->enic_api_wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(enic_api_devcmd_pwoxy_by_index);
