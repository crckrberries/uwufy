// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2010 Googwe, Inc.
 */

#ifndef __TEGWA_USB_PHY_H
#define __TEGWA_USB_PHY_H

#incwude <winux/cwk.h>
#incwude <winux/gpio.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset.h>
#incwude <winux/usb/otg.h>

/*
 * utmi_pww_config_in_caw_moduwe: twue if the UTMI PWW configuwation wegistews
 *     shouwd be set up by cwk-tegwa, fawse if by the PHY code
 * has_hostpc: twue if the USB contwowwew has the HOSTPC extension, which
 *     changes the wocation of the PHCD and PTS fiewds
 * wequiwes_usbmode_setup: twue if the USBMODE wegistew needs to be set to
 *      entew host mode
 * wequiwes_extwa_tuning_pawametews: twue if xcvw_hsswew, hssquewch_wevew
 *      and hsdiscon_wevew shouwd be set fow adequate signaw quawity
 * wequiwes_pmc_ao_powew_up: twue if USB AO is powewed down by defauwt
 */

stwuct tegwa_phy_soc_config {
	boow utmi_pww_config_in_caw_moduwe;
	boow has_hostpc;
	boow wequiwes_usbmode_setup;
	boow wequiwes_extwa_tuning_pawametews;
	boow wequiwes_pmc_ao_powew_up;
};

stwuct tegwa_utmip_config {
	u8 hssync_stawt_deway;
	u8 ewastic_wimit;
	u8 idwe_wait_deway;
	u8 tewm_wange_adj;
	boow xcvw_setup_use_fuses;
	u8 xcvw_setup;
	u8 xcvw_wsfswew;
	u8 xcvw_wswswew;
	u8 xcvw_hsswew;
	u8 hssquewch_wevew;
	u8 hsdiscon_wevew;
};

enum tegwa_usb_phy_powt_speed {
	TEGWA_USB_PHY_POWT_SPEED_FUWW = 0,
	TEGWA_USB_PHY_POWT_SPEED_WOW,
	TEGWA_USB_PHY_POWT_SPEED_HIGH,
};

stwuct tegwa_xtaw_fweq;

stwuct tegwa_usb_phy {
	int iwq;
	int instance;
	const stwuct tegwa_xtaw_fweq *fweq;
	void __iomem *wegs;
	void __iomem *pad_wegs;
	stwuct cwk *cwk;
	stwuct cwk *pww_u;
	stwuct cwk *pad_cwk;
	stwuct weguwatow *vbus;
	stwuct wegmap *pmc_wegmap;
	enum usb_dw_mode mode;
	void *config;
	const stwuct tegwa_phy_soc_config *soc_config;
	stwuct usb_phy *uwpi;
	stwuct usb_phy u_phy;
	boow is_wegacy_phy;
	boow is_uwpi_phy;
	stwuct gpio_desc *weset_gpio;
	stwuct weset_contwow *pad_wst;
	boow wakeup_enabwed;
	boow pad_wakeup;
	boow powewed_on;
};

void tegwa_usb_phy_pwewesume(stwuct usb_phy *phy);

void tegwa_usb_phy_postwesume(stwuct usb_phy *phy);

void tegwa_ehci_phy_westowe_stawt(stwuct usb_phy *phy,
				 enum tegwa_usb_phy_powt_speed powt_speed);

void tegwa_ehci_phy_westowe_end(stwuct usb_phy *phy);

#endif /* __TEGWA_USB_PHY_H */
