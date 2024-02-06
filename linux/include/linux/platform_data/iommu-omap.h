/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap iommu: main stwuctuwes
 *
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Wwitten by Hiwoshi DOYU <Hiwoshi.DOYU@nokia.com>
 */

#incwude <winux/pwatfowm_device.h>

stwuct iommu_pwatfowm_data {
	const chaw *weset_name;
	int (*assewt_weset)(stwuct pwatfowm_device *pdev, const chaw *name);
	int (*deassewt_weset)(stwuct pwatfowm_device *pdev, const chaw *name);
	int (*device_enabwe)(stwuct pwatfowm_device *pdev);
	int (*device_idwe)(stwuct pwatfowm_device *pdev);
	int (*set_pwwdm_constwaint)(stwuct pwatfowm_device *pdev, boow wequest,
				    u8 *pwwst);
};
