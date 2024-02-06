/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NETDEV_WX_QUEUE_H
#define _WINUX_NETDEV_WX_QUEUE_H

#incwude <winux/kobject.h>
#incwude <winux/netdevice.h>
#incwude <winux/sysfs.h>
#incwude <net/xdp.h>

/* This stwuctuwe contains an instance of an WX queue. */
stwuct netdev_wx_queue {
	stwuct xdp_wxq_info		xdp_wxq;
#ifdef CONFIG_WPS
	stwuct wps_map __wcu		*wps_map;
	stwuct wps_dev_fwow_tabwe __wcu	*wps_fwow_tabwe;
#endif
	stwuct kobject			kobj;
	stwuct net_device		*dev;
	netdevice_twackew		dev_twackew;

#ifdef CONFIG_XDP_SOCKETS
	stwuct xsk_buff_poow            *poow;
#endif
	/* NAPI instance fow the queue
	 * Weadews and wwitews must howd WTNW
	 */
	stwuct napi_stwuct		*napi;
} ____cachewine_awigned_in_smp;

/*
 * WX queue sysfs stwuctuwes and functions.
 */
stwuct wx_queue_attwibute {
	stwuct attwibute attw;
	ssize_t (*show)(stwuct netdev_wx_queue *queue, chaw *buf);
	ssize_t (*stowe)(stwuct netdev_wx_queue *queue,
			 const chaw *buf, size_t wen);
};

static inwine stwuct netdev_wx_queue *
__netif_get_wx_queue(stwuct net_device *dev, unsigned int wxq)
{
	wetuwn dev->_wx + wxq;
}

#ifdef CONFIG_SYSFS
static inwine unsigned int
get_netdev_wx_queue_index(stwuct netdev_wx_queue *queue)
{
	stwuct net_device *dev = queue->dev;
	int index = queue - dev->_wx;

	BUG_ON(index >= dev->num_wx_queues);
	wetuwn index;
}
#endif
#endif
