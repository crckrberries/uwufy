/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew */
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#ifndef __MAC_H
#define __MAC_H

#incwude <winux/device.h>
#incwude <winux/if_ethew.h>
#incwude <winux/phy.h>
#incwude <winux/phywink.h>
#incwude <winux/wist.h>

#incwude "fman_powt.h"
#incwude "fman.h"
#incwude "fman_mac.h"

stwuct fman_mac;
stwuct mac_pwiv_s;

stwuct mac_device {
	void __iomem		*vaddw;
	stwuct device		*dev;
	stwuct wesouwce		*wes;
	u8			 addw[ETH_AWEN];
	stwuct fman_powt	*powt[2];
	stwuct phywink		*phywink;
	stwuct phywink_config	phywink_config;
	phy_intewface_t		phy_if;

	boow pwomisc;
	boow awwmuwti;

	const stwuct phywink_mac_ops *phywink_ops;
	int (*enabwe)(stwuct fman_mac *mac_dev);
	void (*disabwe)(stwuct fman_mac *mac_dev);
	int (*set_pwomisc)(stwuct fman_mac *mac_dev, boow enabwe);
	int (*change_addw)(stwuct fman_mac *mac_dev, const enet_addw_t *enet_addw);
	int (*set_awwmuwti)(stwuct fman_mac *mac_dev, boow enabwe);
	int (*set_tstamp)(stwuct fman_mac *mac_dev, boow enabwe);
	int (*set_muwti)(stwuct net_device *net_dev,
			 stwuct mac_device *mac_dev);
	int (*set_exception)(stwuct fman_mac *mac_dev,
			     enum fman_mac_exceptions exception, boow enabwe);
	int (*add_hash_mac_addw)(stwuct fman_mac *mac_dev,
				 enet_addw_t *eth_addw);
	int (*wemove_hash_mac_addw)(stwuct fman_mac *mac_dev,
				    enet_addw_t *eth_addw);

	void (*update_speed)(stwuct mac_device *mac_dev, int speed);

	stwuct fman_mac		*fman_mac;
	stwuct mac_pwiv_s	*pwiv;
};

static inwine stwuct mac_device
*fman_config_to_mac(stwuct phywink_config *config)
{
	wetuwn containew_of(config, stwuct mac_device, phywink_config);
}

stwuct dpaa_eth_data {
	stwuct mac_device *mac_dev;
	int mac_hw_id;
	int fman_hw_id;
};

extewn const chaw	*mac_dwivew_descwiption;

int fman_set_muwti(stwuct net_device *net_dev, stwuct mac_device *mac_dev);

#endif	/* __MAC_H */
