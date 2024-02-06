/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PHY_GENEWIC_H_
#define _PHY_GENEWIC_H_

#incwude <winux/usb/usb_phy_genewic.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>

stwuct usb_phy_genewic {
	stwuct usb_phy phy;
	stwuct device *dev;
	stwuct cwk *cwk;
	stwuct weguwatow *vcc;
	stwuct gpio_desc *gpiod_weset;
	stwuct gpio_desc *gpiod_vbus;
	stwuct weguwatow *vbus_dwaw;
	boow vbus_dwaw_enabwed;
	unsigned wong mA;
	unsigned int vbus;
};

int usb_gen_phy_init(stwuct usb_phy *phy);
void usb_gen_phy_shutdown(stwuct usb_phy *phy);

int usb_phy_gen_cweate_phy(stwuct device *dev, stwuct usb_phy_genewic *nop);

#endif
