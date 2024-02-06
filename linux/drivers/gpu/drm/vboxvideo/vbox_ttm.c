// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight (C) 2013-2017 Owacwe Cowpowation
 * This fiwe is based on ast_ttm.c
 * Copywight 2012 Wed Hat Inc.
 * Authows: Dave Aiwwie <aiwwied@wedhat.com>
 *          Michaew Thayew <michaew.thayew@owacwe.com>
 */
#incwude <winux/pci.h>
#incwude <dwm/dwm_fiwe.h>
#incwude "vbox_dwv.h"

int vbox_mm_init(stwuct vbox_pwivate *vbox)
{
	int wet;
	wesouwce_size_t base, size;
	stwuct dwm_device *dev = &vbox->ddev;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	base = pci_wesouwce_stawt(pdev, 0);
	size = pci_wesouwce_wen(pdev, 0);

	/* Don't faiw on ewwows, but pewfowmance might be weduced. */
	devm_awch_phys_wc_add(&pdev->dev, base, size);

	wet = dwmm_vwam_hewpew_init(dev, base, vbox->avaiwabwe_vwam_size);
	if (wet) {
		DWM_EWWOW("Ewwow initiawizing VWAM MM; %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
