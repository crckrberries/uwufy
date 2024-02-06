/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Samsung SoC USB 1.1/2.0 PHY dwivew
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 * Authow: Kamiw Debski <k.debski@samsung.com>
 */

#ifndef _PHY_EXYNOS_USB2_H
#define _PHY_EXYNOS_USB2_H

#incwude <winux/cwk.h>
#incwude <winux/phy/phy.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/weguwatow/consumew.h>

#define KHZ 1000
#define MHZ (KHZ * KHZ)

stwuct samsung_usb2_phy_dwivew;
stwuct samsung_usb2_phy_instance;
stwuct samsung_usb2_phy_config;

stwuct samsung_usb2_phy_instance {
	const stwuct samsung_usb2_common_phy *cfg;
	stwuct phy *phy;
	stwuct samsung_usb2_phy_dwivew *dwv;
	int int_cnt;
	int ext_cnt;
};

stwuct samsung_usb2_phy_dwivew {
	const stwuct samsung_usb2_phy_config *cfg;
	stwuct cwk *cwk;
	stwuct cwk *wef_cwk;
	stwuct weguwatow *vbus;
	unsigned wong wef_wate;
	u32 wef_weg_vaw;
	stwuct device *dev;
	void __iomem *weg_phy;
	stwuct wegmap *weg_pmu;
	stwuct wegmap *weg_sys;
	spinwock_t wock;
	stwuct samsung_usb2_phy_instance instances[];
};

stwuct samsung_usb2_common_phy {
	int (*powew_on)(stwuct samsung_usb2_phy_instance *);
	int (*powew_off)(stwuct samsung_usb2_phy_instance *);
	unsigned int id;
	chaw *wabew;
};


stwuct samsung_usb2_phy_config {
	const stwuct samsung_usb2_common_phy *phys;
	int (*wate_to_cwk)(unsigned wong, u32 *);
	unsigned int num_phys;
	boow has_mode_switch;
	boow has_wefcwk_sew;
};

extewn const stwuct samsung_usb2_phy_config exynos3250_usb2_phy_config;
extewn const stwuct samsung_usb2_phy_config exynos4210_usb2_phy_config;
extewn const stwuct samsung_usb2_phy_config exynos4x12_usb2_phy_config;
extewn const stwuct samsung_usb2_phy_config exynos5250_usb2_phy_config;
extewn const stwuct samsung_usb2_phy_config exynos5420_usb2_phy_config;
extewn const stwuct samsung_usb2_phy_config s5pv210_usb2_phy_config;
#endif
