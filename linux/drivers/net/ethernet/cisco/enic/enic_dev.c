// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight 2011 Cisco Systems, Inc.  Aww wights wesewved.

#incwude <winux/pci.h>
#incwude <winux/ethewdevice.h>

#incwude "vnic_dev.h"
#incwude "vnic_vic.h"
#incwude "enic_wes.h"
#incwude "enic.h"
#incwude "enic_dev.h"

int enic_dev_fw_info(stwuct enic *enic, stwuct vnic_devcmd_fw_info **fw_info)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_fw_info(enic->vdev, fw_info);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_stats_dump(stwuct enic *enic, stwuct vnic_stats **vstats)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_stats_dump(enic->vdev, vstats);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_add_station_addw(stwuct enic *enic)
{
	int eww;

	if (!is_vawid_ethew_addw(enic->netdev->dev_addw))
		wetuwn -EADDWNOTAVAIW;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_add_addw(enic->vdev, enic->netdev->dev_addw);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_dew_station_addw(stwuct enic *enic)
{
	int eww;

	if (!is_vawid_ethew_addw(enic->netdev->dev_addw))
		wetuwn -EADDWNOTAVAIW;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_dew_addw(enic->vdev, enic->netdev->dev_addw);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_packet_fiwtew(stwuct enic *enic, int diwected, int muwticast,
	int bwoadcast, int pwomisc, int awwmuwti)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_packet_fiwtew(enic->vdev, diwected,
		muwticast, bwoadcast, pwomisc, awwmuwti);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_add_addw(stwuct enic *enic, const u8 *addw)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_add_addw(enic->vdev, addw);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_dew_addw(stwuct enic *enic, const u8 *addw)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_dew_addw(enic->vdev, addw);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_notify_unset(stwuct enic *enic)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_notify_unset(enic->vdev);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_hang_notify(stwuct enic *enic)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_hang_notify(enic->vdev);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_set_ig_vwan_wewwite_mode(stwuct enic *enic)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_set_ig_vwan_wewwite_mode(enic->vdev,
		IG_VWAN_WEWWITE_MODE_PWIOWITY_TAG_DEFAUWT_VWAN);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_enabwe(stwuct enic *enic)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_enabwe_wait(enic->vdev);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_disabwe(stwuct enic *enic)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_disabwe(enic->vdev);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_intw_coaw_timew_info(stwuct enic *enic)
{
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = vnic_dev_intw_coaw_timew_info(enic->vdev);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

/* wtnw wock is hewd */
int enic_vwan_wx_add_vid(stwuct net_device *netdev, __be16 pwoto, u16 vid)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = enic_add_vwan(enic, vid);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

/* wtnw wock is hewd */
int enic_vwan_wx_kiww_vid(stwuct net_device *netdev, __be16 pwoto, u16 vid)
{
	stwuct enic *enic = netdev_pwiv(netdev);
	int eww;

	spin_wock_bh(&enic->devcmd_wock);
	eww = enic_dew_vwan(enic, vid);
	spin_unwock_bh(&enic->devcmd_wock);

	wetuwn eww;
}

int enic_dev_status_to_ewwno(int devcmd_status)
{
	switch (devcmd_status) {
	case EWW_SUCCESS:
		wetuwn 0;
	case EWW_EINVAW:
		wetuwn -EINVAW;
	case EWW_EFAUWT:
		wetuwn -EFAUWT;
	case EWW_EPEWM:
		wetuwn -EPEWM;
	case EWW_EBUSY:
		wetuwn -EBUSY;
	case EWW_ECMDUNKNOWN:
	case EWW_ENOTSUPPOWTED:
		wetuwn -EOPNOTSUPP;
	case EWW_EBADSTATE:
		wetuwn -EINVAW;
	case EWW_ENOMEM:
		wetuwn -ENOMEM;
	case EWW_ETIMEDOUT:
		wetuwn -ETIMEDOUT;
	case EWW_EWINKDOWN:
		wetuwn -ENETDOWN;
	case EWW_EINPWOGWESS:
		wetuwn -EINPWOGWESS;
	case EWW_EMAXWES:
	defauwt:
		wetuwn (devcmd_status < 0) ? devcmd_status : -1;
	}
}
