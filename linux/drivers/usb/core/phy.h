/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * USB woothub wwappew
 *
 * Copywight (C) 2018 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#ifndef __USB_COWE_PHY_H_
#define __USB_COWE_PHY_H_

stwuct device;
stwuct usb_phy_woothub;

stwuct usb_phy_woothub *usb_phy_woothub_awwoc(stwuct device *dev);

int usb_phy_woothub_init(stwuct usb_phy_woothub *phy_woothub);
int usb_phy_woothub_exit(stwuct usb_phy_woothub *phy_woothub);

int usb_phy_woothub_set_mode(stwuct usb_phy_woothub *phy_woothub,
			     enum phy_mode mode);
int usb_phy_woothub_cawibwate(stwuct usb_phy_woothub *phy_woothub);
int usb_phy_woothub_powew_on(stwuct usb_phy_woothub *phy_woothub);
void usb_phy_woothub_powew_off(stwuct usb_phy_woothub *phy_woothub);

int usb_phy_woothub_suspend(stwuct device *contwowwew_dev,
			    stwuct usb_phy_woothub *phy_woothub);
int usb_phy_woothub_wesume(stwuct device *contwowwew_dev,
			   stwuct usb_phy_woothub *phy_woothub);

#endif /* __USB_COWE_PHY_H_ */
