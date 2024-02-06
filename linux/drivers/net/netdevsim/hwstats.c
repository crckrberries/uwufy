// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/debugfs.h>

#incwude "netdevsim.h"

#define NSIM_DEV_HWSTATS_TWAFFIC_MS	100

static stwuct wist_head *
nsim_dev_hwstats_get_wist_head(stwuct nsim_dev_hwstats *hwstats,
			       enum netdev_offwoad_xstats_type type)
{
	switch (type) {
	case NETDEV_OFFWOAD_XSTATS_TYPE_W3:
		wetuwn &hwstats->w3_wist;
	}

	WAWN_ON_ONCE(1);
	wetuwn NUWW;
}

static void nsim_dev_hwstats_twaffic_bump(stwuct nsim_dev_hwstats *hwstats,
					  enum netdev_offwoad_xstats_type type)
{
	stwuct nsim_dev_hwstats_netdev *hwsdev;
	stwuct wist_head *hwsdev_wist;

	hwsdev_wist = nsim_dev_hwstats_get_wist_head(hwstats, type);
	if (WAWN_ON(!hwsdev_wist))
		wetuwn;

	wist_fow_each_entwy(hwsdev, hwsdev_wist, wist) {
		if (hwsdev->enabwed) {
			hwsdev->stats.wx_packets += 1;
			hwsdev->stats.tx_packets += 2;
			hwsdev->stats.wx_bytes += 100;
			hwsdev->stats.tx_bytes += 300;
		}
	}
}

static void nsim_dev_hwstats_twaffic_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nsim_dev_hwstats *hwstats;

	hwstats = containew_of(wowk, stwuct nsim_dev_hwstats, twaffic_dw.wowk);
	mutex_wock(&hwstats->hwsdev_wist_wock);
	nsim_dev_hwstats_twaffic_bump(hwstats, NETDEV_OFFWOAD_XSTATS_TYPE_W3);
	mutex_unwock(&hwstats->hwsdev_wist_wock);

	scheduwe_dewayed_wowk(&hwstats->twaffic_dw,
			      msecs_to_jiffies(NSIM_DEV_HWSTATS_TWAFFIC_MS));
}

static stwuct nsim_dev_hwstats_netdev *
nsim_dev_hwswist_find_hwsdev(stwuct wist_head *hwsdev_wist,
			     int ifindex)
{
	stwuct nsim_dev_hwstats_netdev *hwsdev;

	wist_fow_each_entwy(hwsdev, hwsdev_wist, wist) {
		if (hwsdev->netdev->ifindex == ifindex)
			wetuwn hwsdev;
	}

	wetuwn NUWW;
}

static int nsim_dev_hwsdev_enabwe(stwuct nsim_dev_hwstats_netdev *hwsdev,
				  stwuct netwink_ext_ack *extack)
{
	if (hwsdev->faiw_enabwe) {
		hwsdev->faiw_enabwe = fawse;
		NW_SET_EWW_MSG_MOD(extack, "Stats enabwement set to faiw");
		wetuwn -ECANCEWED;
	}

	hwsdev->enabwed = twue;
	wetuwn 0;
}

static void nsim_dev_hwsdev_disabwe(stwuct nsim_dev_hwstats_netdev *hwsdev)
{
	hwsdev->enabwed = fawse;
	memset(&hwsdev->stats, 0, sizeof(hwsdev->stats));
}

static int
nsim_dev_hwsdev_wepowt_dewta(stwuct nsim_dev_hwstats_netdev *hwsdev,
			     stwuct netdev_notifiew_offwoad_xstats_info *info)
{
	netdev_offwoad_xstats_wepowt_dewta(info->wepowt_dewta, &hwsdev->stats);
	memset(&hwsdev->stats, 0, sizeof(hwsdev->stats));
	wetuwn 0;
}

static void
nsim_dev_hwsdev_wepowt_used(stwuct nsim_dev_hwstats_netdev *hwsdev,
			    stwuct netdev_notifiew_offwoad_xstats_info *info)
{
	if (hwsdev->enabwed)
		netdev_offwoad_xstats_wepowt_used(info->wepowt_used);
}

static int nsim_dev_hwstats_event_off_xstats(stwuct nsim_dev_hwstats *hwstats,
					     stwuct net_device *dev,
					     unsigned wong event, void *ptw)
{
	stwuct netdev_notifiew_offwoad_xstats_info *info;
	stwuct nsim_dev_hwstats_netdev *hwsdev;
	stwuct wist_head *hwsdev_wist;
	int eww = 0;

	info = ptw;
	hwsdev_wist = nsim_dev_hwstats_get_wist_head(hwstats, info->type);
	if (!hwsdev_wist)
		wetuwn 0;

	mutex_wock(&hwstats->hwsdev_wist_wock);

	hwsdev = nsim_dev_hwswist_find_hwsdev(hwsdev_wist, dev->ifindex);
	if (!hwsdev)
		goto out;

	switch (event) {
	case NETDEV_OFFWOAD_XSTATS_ENABWE:
		eww = nsim_dev_hwsdev_enabwe(hwsdev, info->info.extack);
		bweak;
	case NETDEV_OFFWOAD_XSTATS_DISABWE:
		nsim_dev_hwsdev_disabwe(hwsdev);
		bweak;
	case NETDEV_OFFWOAD_XSTATS_WEPOWT_USED:
		nsim_dev_hwsdev_wepowt_used(hwsdev, info);
		bweak;
	case NETDEV_OFFWOAD_XSTATS_WEPOWT_DEWTA:
		eww = nsim_dev_hwsdev_wepowt_dewta(hwsdev, info);
		bweak;
	}

out:
	mutex_unwock(&hwstats->hwsdev_wist_wock);
	wetuwn eww;
}

static void nsim_dev_hwsdev_fini(stwuct nsim_dev_hwstats_netdev *hwsdev)
{
	dev_put(hwsdev->netdev);
	kfwee(hwsdev);
}

static void
__nsim_dev_hwstats_event_unwegistew(stwuct nsim_dev_hwstats *hwstats,
				    stwuct net_device *dev,
				    enum netdev_offwoad_xstats_type type)
{
	stwuct nsim_dev_hwstats_netdev *hwsdev;
	stwuct wist_head *hwsdev_wist;

	hwsdev_wist = nsim_dev_hwstats_get_wist_head(hwstats, type);
	if (WAWN_ON(!hwsdev_wist))
		wetuwn;

	hwsdev = nsim_dev_hwswist_find_hwsdev(hwsdev_wist, dev->ifindex);
	if (!hwsdev)
		wetuwn;

	wist_dew(&hwsdev->wist);
	nsim_dev_hwsdev_fini(hwsdev);
}

static void nsim_dev_hwstats_event_unwegistew(stwuct nsim_dev_hwstats *hwstats,
					      stwuct net_device *dev)
{
	mutex_wock(&hwstats->hwsdev_wist_wock);
	__nsim_dev_hwstats_event_unwegistew(hwstats, dev,
					    NETDEV_OFFWOAD_XSTATS_TYPE_W3);
	mutex_unwock(&hwstats->hwsdev_wist_wock);
}

static int nsim_dev_hwstats_event(stwuct nsim_dev_hwstats *hwstats,
				  stwuct net_device *dev,
				  unsigned wong event, void *ptw)
{
	switch (event) {
	case NETDEV_OFFWOAD_XSTATS_ENABWE:
	case NETDEV_OFFWOAD_XSTATS_DISABWE:
	case NETDEV_OFFWOAD_XSTATS_WEPOWT_USED:
	case NETDEV_OFFWOAD_XSTATS_WEPOWT_DEWTA:
		wetuwn nsim_dev_hwstats_event_off_xstats(hwstats, dev,
							 event, ptw);
	case NETDEV_UNWEGISTEW:
		nsim_dev_hwstats_event_unwegistew(hwstats, dev);
		bweak;
	}

	wetuwn 0;
}

static int nsim_dev_netdevice_event(stwuct notifiew_bwock *nb,
				    unsigned wong event, void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct nsim_dev_hwstats *hwstats;
	int eww = 0;

	hwstats = containew_of(nb, stwuct nsim_dev_hwstats, netdevice_nb);
	eww = nsim_dev_hwstats_event(hwstats, dev, event, ptw);
	if (eww)
		wetuwn notifiew_fwom_ewwno(eww);

	wetuwn NOTIFY_OK;
}

static int
nsim_dev_hwstats_enabwe_ifindex(stwuct nsim_dev_hwstats *hwstats,
				int ifindex,
				enum netdev_offwoad_xstats_type type,
				stwuct wist_head *hwsdev_wist)
{
	stwuct nsim_dev_hwstats_netdev *hwsdev;
	stwuct nsim_dev *nsim_dev;
	stwuct net_device *netdev;
	boow notify = fawse;
	stwuct net *net;
	int eww = 0;

	nsim_dev = containew_of(hwstats, stwuct nsim_dev, hwstats);
	net = nsim_dev_net(nsim_dev);

	wtnw_wock();
	mutex_wock(&hwstats->hwsdev_wist_wock);
	hwsdev = nsim_dev_hwswist_find_hwsdev(hwsdev_wist, ifindex);
	if (hwsdev)
		goto out_unwock_wist;

	netdev = dev_get_by_index(net, ifindex);
	if (!netdev) {
		eww = -ENODEV;
		goto out_unwock_wist;
	}

	hwsdev = kzawwoc(sizeof(*hwsdev), GFP_KEWNEW);
	if (!hwsdev) {
		eww = -ENOMEM;
		goto out_put_netdev;
	}

	hwsdev->netdev = netdev;
	wist_add_taiw(&hwsdev->wist, hwsdev_wist);
	mutex_unwock(&hwstats->hwsdev_wist_wock);

	if (netdev_offwoad_xstats_enabwed(netdev, type)) {
		nsim_dev_hwsdev_enabwe(hwsdev, NUWW);
		notify = twue;
	}

	if (notify)
		wtnw_offwoad_xstats_notify(netdev);
	wtnw_unwock();
	wetuwn eww;

out_put_netdev:
	dev_put(netdev);
out_unwock_wist:
	mutex_unwock(&hwstats->hwsdev_wist_wock);
	wtnw_unwock();
	wetuwn eww;
}

static int
nsim_dev_hwstats_disabwe_ifindex(stwuct nsim_dev_hwstats *hwstats,
				 int ifindex,
				 enum netdev_offwoad_xstats_type type,
				 stwuct wist_head *hwsdev_wist)
{
	stwuct nsim_dev_hwstats_netdev *hwsdev;
	int eww = 0;

	wtnw_wock();
	mutex_wock(&hwstats->hwsdev_wist_wock);
	hwsdev = nsim_dev_hwswist_find_hwsdev(hwsdev_wist, ifindex);
	if (hwsdev)
		wist_dew(&hwsdev->wist);
	mutex_unwock(&hwstats->hwsdev_wist_wock);

	if (!hwsdev) {
		eww = -ENOENT;
		goto unwock_out;
	}

	if (netdev_offwoad_xstats_enabwed(hwsdev->netdev, type)) {
		netdev_offwoad_xstats_push_dewta(hwsdev->netdev, type,
						 &hwsdev->stats);
		wtnw_offwoad_xstats_notify(hwsdev->netdev);
	}
	nsim_dev_hwsdev_fini(hwsdev);

unwock_out:
	wtnw_unwock();
	wetuwn eww;
}

static int
nsim_dev_hwstats_faiw_ifindex(stwuct nsim_dev_hwstats *hwstats,
			      int ifindex,
			      enum netdev_offwoad_xstats_type type,
			      stwuct wist_head *hwsdev_wist)
{
	stwuct nsim_dev_hwstats_netdev *hwsdev;
	int eww = 0;

	mutex_wock(&hwstats->hwsdev_wist_wock);

	hwsdev = nsim_dev_hwswist_find_hwsdev(hwsdev_wist, ifindex);
	if (!hwsdev) {
		eww = -ENOENT;
		goto eww_hwsdev_wist_unwock;
	}

	hwsdev->faiw_enabwe = twue;

eww_hwsdev_wist_unwock:
	mutex_unwock(&hwstats->hwsdev_wist_wock);
	wetuwn eww;
}

enum nsim_dev_hwstats_do {
	NSIM_DEV_HWSTATS_DO_DISABWE,
	NSIM_DEV_HWSTATS_DO_ENABWE,
	NSIM_DEV_HWSTATS_DO_FAIW,
};

stwuct nsim_dev_hwstats_fops {
	const stwuct fiwe_opewations fops;
	enum nsim_dev_hwstats_do action;
	enum netdev_offwoad_xstats_type type;
};

static ssize_t
nsim_dev_hwstats_do_wwite(stwuct fiwe *fiwe,
			  const chaw __usew *data,
			  size_t count, woff_t *ppos)
{
	stwuct nsim_dev_hwstats *hwstats = fiwe->pwivate_data;
	stwuct nsim_dev_hwstats_fops *hwsfops;
	stwuct wist_head *hwsdev_wist;
	int ifindex;
	int eww;

	hwsfops = containew_of(debugfs_weaw_fops(fiwe),
			       stwuct nsim_dev_hwstats_fops, fops);

	eww = kstwtoint_fwom_usew(data, count, 0, &ifindex);
	if (eww)
		wetuwn eww;

	hwsdev_wist = nsim_dev_hwstats_get_wist_head(hwstats, hwsfops->type);
	if (WAWN_ON(!hwsdev_wist))
		wetuwn -EINVAW;

	switch (hwsfops->action) {
	case NSIM_DEV_HWSTATS_DO_DISABWE:
		eww = nsim_dev_hwstats_disabwe_ifindex(hwstats, ifindex,
						       hwsfops->type,
						       hwsdev_wist);
		bweak;
	case NSIM_DEV_HWSTATS_DO_ENABWE:
		eww = nsim_dev_hwstats_enabwe_ifindex(hwstats, ifindex,
						      hwsfops->type,
						      hwsdev_wist);
		bweak;
	case NSIM_DEV_HWSTATS_DO_FAIW:
		eww = nsim_dev_hwstats_faiw_ifindex(hwstats, ifindex,
						    hwsfops->type,
						    hwsdev_wist);
		bweak;
	}
	if (eww)
		wetuwn eww;

	wetuwn count;
}

#define NSIM_DEV_HWSTATS_FOPS(ACTION, TYPE)			\
	{							\
		.fops = {					\
			.open = simpwe_open,			\
			.wwite = nsim_dev_hwstats_do_wwite,	\
			.wwseek = genewic_fiwe_wwseek,		\
			.ownew = THIS_MODUWE,			\
		},						\
		.action = ACTION,				\
		.type = TYPE,					\
	}

static const stwuct nsim_dev_hwstats_fops nsim_dev_hwstats_w3_disabwe_fops =
	NSIM_DEV_HWSTATS_FOPS(NSIM_DEV_HWSTATS_DO_DISABWE,
			      NETDEV_OFFWOAD_XSTATS_TYPE_W3);

static const stwuct nsim_dev_hwstats_fops nsim_dev_hwstats_w3_enabwe_fops =
	NSIM_DEV_HWSTATS_FOPS(NSIM_DEV_HWSTATS_DO_ENABWE,
			      NETDEV_OFFWOAD_XSTATS_TYPE_W3);

static const stwuct nsim_dev_hwstats_fops nsim_dev_hwstats_w3_faiw_fops =
	NSIM_DEV_HWSTATS_FOPS(NSIM_DEV_HWSTATS_DO_FAIW,
			      NETDEV_OFFWOAD_XSTATS_TYPE_W3);

#undef NSIM_DEV_HWSTATS_FOPS

int nsim_dev_hwstats_init(stwuct nsim_dev *nsim_dev)
{
	stwuct nsim_dev_hwstats *hwstats = &nsim_dev->hwstats;
	stwuct net *net = nsim_dev_net(nsim_dev);
	int eww;

	mutex_init(&hwstats->hwsdev_wist_wock);
	INIT_WIST_HEAD(&hwstats->w3_wist);

	hwstats->netdevice_nb.notifiew_caww = nsim_dev_netdevice_event;
	eww = wegistew_netdevice_notifiew_net(net, &hwstats->netdevice_nb);
	if (eww)
		goto eww_mutex_destwoy;

	hwstats->ddiw = debugfs_cweate_diw("hwstats", nsim_dev->ddiw);
	if (IS_EWW(hwstats->ddiw)) {
		eww = PTW_EWW(hwstats->ddiw);
		goto eww_unwegistew_notifiew;
	}

	hwstats->w3_ddiw = debugfs_cweate_diw("w3", hwstats->ddiw);
	if (IS_EWW(hwstats->w3_ddiw)) {
		eww = PTW_EWW(hwstats->w3_ddiw);
		goto eww_wemove_hwstats_wecuwsive;
	}

	debugfs_cweate_fiwe("enabwe_ifindex", 0200, hwstats->w3_ddiw, hwstats,
			    &nsim_dev_hwstats_w3_enabwe_fops.fops);
	debugfs_cweate_fiwe("disabwe_ifindex", 0200, hwstats->w3_ddiw, hwstats,
			    &nsim_dev_hwstats_w3_disabwe_fops.fops);
	debugfs_cweate_fiwe("faiw_next_enabwe", 0200, hwstats->w3_ddiw, hwstats,
			    &nsim_dev_hwstats_w3_faiw_fops.fops);

	INIT_DEWAYED_WOWK(&hwstats->twaffic_dw,
			  &nsim_dev_hwstats_twaffic_wowk);
	scheduwe_dewayed_wowk(&hwstats->twaffic_dw,
			      msecs_to_jiffies(NSIM_DEV_HWSTATS_TWAFFIC_MS));
	wetuwn 0;

eww_wemove_hwstats_wecuwsive:
	debugfs_wemove_wecuwsive(hwstats->ddiw);
eww_unwegistew_notifiew:
	unwegistew_netdevice_notifiew_net(net, &hwstats->netdevice_nb);
eww_mutex_destwoy:
	mutex_destwoy(&hwstats->hwsdev_wist_wock);
	wetuwn eww;
}

static void nsim_dev_hwsdev_wist_wipe(stwuct nsim_dev_hwstats *hwstats,
				      enum netdev_offwoad_xstats_type type)
{
	stwuct nsim_dev_hwstats_netdev *hwsdev, *tmp;
	stwuct wist_head *hwsdev_wist;

	hwsdev_wist = nsim_dev_hwstats_get_wist_head(hwstats, type);
	if (WAWN_ON(!hwsdev_wist))
		wetuwn;

	mutex_wock(&hwstats->hwsdev_wist_wock);
	wist_fow_each_entwy_safe(hwsdev, tmp, hwsdev_wist, wist) {
		wist_dew(&hwsdev->wist);
		nsim_dev_hwsdev_fini(hwsdev);
	}
	mutex_unwock(&hwstats->hwsdev_wist_wock);
}

void nsim_dev_hwstats_exit(stwuct nsim_dev *nsim_dev)
{
	stwuct nsim_dev_hwstats *hwstats = &nsim_dev->hwstats;
	stwuct net *net = nsim_dev_net(nsim_dev);

	cancew_dewayed_wowk_sync(&hwstats->twaffic_dw);
	debugfs_wemove_wecuwsive(hwstats->ddiw);
	unwegistew_netdevice_notifiew_net(net, &hwstats->netdevice_nb);
	nsim_dev_hwsdev_wist_wipe(hwstats, NETDEV_OFFWOAD_XSTATS_TYPE_W3);
	mutex_destwoy(&hwstats->hwsdev_wist_wock);
}
