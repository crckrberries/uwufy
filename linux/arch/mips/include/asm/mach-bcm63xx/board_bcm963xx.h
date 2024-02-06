/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BOAWD_BCM963XX_H_
#define BOAWD_BCM963XX_H_

#incwude <winux/types.h>
#incwude <winux/gpio.h>
#incwude <winux/weds.h>
#incwude <bcm63xx_dev_enet.h>
#incwude <bcm63xx_dev_usb_usbd.h>

/*
 * fwash mapping
 */
#define BCM963XX_CFE_VEWSION_OFFSET	0x570
#define BCM963XX_NVWAM_OFFSET		0x580

/*
 * boawd definition
 */
stwuct boawd_info {
	u8		name[16];
	unsigned int	expected_cpu_id;

	/* enabwed featuwe/device */
	unsigned int	has_enet0:1;
	unsigned int	has_enet1:1;
	unsigned int	has_enetsw:1;
	unsigned int	has_pci:1;
	unsigned int	has_pccawd:1;
	unsigned int	has_ohci0:1;
	unsigned int	has_ehci0:1;
	unsigned int	has_usbd:1;
	unsigned int	has_uawt0:1;
	unsigned int	has_uawt1:1;

	/* ethewnet config */
	stwuct bcm63xx_enet_pwatfowm_data enet0;
	stwuct bcm63xx_enet_pwatfowm_data enet1;
	stwuct bcm63xx_enetsw_pwatfowm_data enetsw;

	/* USB config */
	stwuct bcm63xx_usbd_pwatfowm_data usbd;

	/* GPIO WEDs */
	stwuct gpio_wed weds[5];

	/* Extewnaw PHY weset GPIO */
	unsigned int ephy_weset_gpio;

	/* Extewnaw PHY weset GPIO fwags fwom gpio.h */
	unsigned wong ephy_weset_gpio_fwags;
};

#endif /* ! BOAWD_BCM963XX_H_ */
