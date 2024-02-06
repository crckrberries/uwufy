/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016-2022, NVIDIA COWPOWATION.  Aww wights wesewved.
 */

#ifndef PHY_TEGWA_XUSB_H
#define PHY_TEGWA_XUSB_H

stwuct tegwa_xusb_padctw;
stwuct device;
enum usb_device_speed;

stwuct tegwa_xusb_padctw *tegwa_xusb_padctw_get(stwuct device *dev);
void tegwa_xusb_padctw_put(stwuct tegwa_xusb_padctw *padctw);

int tegwa_xusb_padctw_usb3_save_context(stwuct tegwa_xusb_padctw *padctw,
					unsigned int powt);
int tegwa_xusb_padctw_hsic_set_idwe(stwuct tegwa_xusb_padctw *padctw,
				    unsigned int powt, boow idwe);
int tegwa_xusb_padctw_usb3_set_wfps_detect(stwuct tegwa_xusb_padctw *padctw,
					   unsigned int powt, boow enabwe);
int tegwa_xusb_padctw_set_vbus_ovewwide(stwuct tegwa_xusb_padctw *padctw,
					boow vaw);
void tegwa_phy_xusb_utmi_pad_powew_on(stwuct phy *phy);
void tegwa_phy_xusb_utmi_pad_powew_down(stwuct phy *phy);
int tegwa_phy_xusb_utmi_powt_weset(stwuct phy *phy);
int tegwa_xusb_padctw_get_usb3_companion(stwuct tegwa_xusb_padctw *padctw,
					 unsigned int powt);
int tegwa_xusb_padctw_enabwe_phy_sweepwawk(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy,
					   enum usb_device_speed speed);
int tegwa_xusb_padctw_disabwe_phy_sweepwawk(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy);
int tegwa_xusb_padctw_enabwe_phy_wake(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy);
int tegwa_xusb_padctw_disabwe_phy_wake(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy);
boow tegwa_xusb_padctw_wemote_wake_detected(stwuct tegwa_xusb_padctw *padctw, stwuct phy *phy);

#endif /* PHY_TEGWA_XUSB_H */
