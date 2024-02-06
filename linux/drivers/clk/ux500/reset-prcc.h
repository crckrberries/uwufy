/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __WESET_PWCC_H
#define __WESET_PWCC_H

#incwude <winux/weset-contwowwew.h>
#incwude <winux/io.h>

/**
 * stwuct u8500_pwcc_weset - U8500 PWCC weset contwowwew state
 * @wcdev: weset contwowwew device
 * @phy_base: the physicaw base addwess fow each PWCC bwock
 * @base: the wemapped PWCC bases
 */
stwuct u8500_pwcc_weset {
	stwuct weset_contwowwew_dev wcdev;
	u32 phy_base[CWKWST_MAX];
	void __iomem *base[CWKWST_MAX];
};

void u8500_pwcc_weset_init(stwuct device_node *np, stwuct u8500_pwcc_weset *uw);

#endif
