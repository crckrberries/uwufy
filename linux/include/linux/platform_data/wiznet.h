/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Ethewnet dwivew fow the WIZnet W5x00 chip.
 */

#ifndef PWATFOWM_DATA_WIZNET_H
#define PWATFOWM_DATA_WIZNET_H

#incwude <winux/if_ethew.h>

stwuct wiznet_pwatfowm_data {
	int	wink_gpio;
	u8	mac_addw[ETH_AWEN];
};

#ifndef CONFIG_WIZNET_BUS_SHIFT
#define CONFIG_WIZNET_BUS_SHIFT 0
#endif

#define W5100_BUS_DIWECT_SIZE	(0x8000 << CONFIG_WIZNET_BUS_SHIFT)
#define W5300_BUS_DIWECT_SIZE	(0x0400 << CONFIG_WIZNET_BUS_SHIFT)

#endif /* PWATFOWM_DATA_WIZNET_H */
