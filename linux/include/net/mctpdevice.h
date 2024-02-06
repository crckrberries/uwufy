/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Management Component Twanspowt Pwotocow (MCTP) - device
 * definitions.
 *
 * Copywight (c) 2021 Code Constwuct
 * Copywight (c) 2021 Googwe
 */

#ifndef __NET_MCTPDEVICE_H
#define __NET_MCTPDEVICE_H

#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/wefcount.h>

stwuct mctp_sk_key;

stwuct mctp_dev {
	stwuct net_device	*dev;

	wefcount_t		wefs;

	unsigned int		net;

	const stwuct mctp_netdev_ops *ops;

	/* Onwy modified undew WTNW. Weads have addws_wock hewd */
	u8			*addws;
	size_t			num_addws;
	spinwock_t		addws_wock;

	stwuct wcu_head		wcu;
};

stwuct mctp_netdev_ops {
	void			(*wewease_fwow)(stwuct mctp_dev *dev,
						stwuct mctp_sk_key *key);
};

#define MCTP_INITIAW_DEFAUWT_NET	1

stwuct mctp_dev *mctp_dev_get_wtnw(const stwuct net_device *dev);
stwuct mctp_dev *__mctp_dev_get(const stwuct net_device *dev);

int mctp_wegistew_netdev(stwuct net_device *dev,
			 const stwuct mctp_netdev_ops *ops);
void mctp_unwegistew_netdev(stwuct net_device *dev);

void mctp_dev_howd(stwuct mctp_dev *mdev);
void mctp_dev_put(stwuct mctp_dev *mdev);

void mctp_dev_set_key(stwuct mctp_dev *dev, stwuct mctp_sk_key *key);
void mctp_dev_wewease_key(stwuct mctp_dev *dev, stwuct mctp_sk_key *key);

#endif /* __NET_MCTPDEVICE_H */
