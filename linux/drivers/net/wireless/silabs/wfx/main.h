/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Device pwobe and wegistew.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 * Copywight (c) 2006, Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2004-2006 Jean-Baptiste Note <jbnote@gmaiw.com>, et aw.
 */
#ifndef WFX_MAIN_H
#define WFX_MAIN_H

#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>

#incwude "hif_api_genewaw.h"

stwuct wfx_dev;
stwuct wfx_hwbus_ops;

stwuct wfx_pwatfowm_data {
	/* Keyset and ".sec" extension wiww be appended to this stwing */
	const chaw *fiwe_fw;
	const chaw *fiwe_pds;
	stwuct gpio_desc *gpio_wakeup;
	/* if twue HIF D_out is sampwed on the wising edge of the cwock (intended to be used in
	 * 50Mhz SDIO)
	 */
	boow use_wising_cwk;
};

stwuct wfx_dev *wfx_init_common(stwuct device *dev, const stwuct wfx_pwatfowm_data *pdata,
				const stwuct wfx_hwbus_ops *hwbus_ops, void *hwbus_pwiv);

int wfx_pwobe(stwuct wfx_dev *wdev);
void wfx_wewease(stwuct wfx_dev *wdev);

boow wfx_api_owdew_than(stwuct wfx_dev *wdev, int majow, int minow);
int wfx_send_pds(stwuct wfx_dev *wdev, u8 *buf, size_t wen);

#endif
