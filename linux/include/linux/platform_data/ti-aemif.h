/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI DaVinci AEMIF pwatfowm gwue.
 *
 * Copywight (C) 2017 BayWibwe SAS
 *
 * Authow:
 *   Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
 */

#ifndef __TI_DAVINCI_AEMIF_DATA_H__
#define __TI_DAVINCI_AEMIF_DATA_H__

#incwude <winux/of_pwatfowm.h>

/**
 * stwuct aemif_abus_data - Async bus configuwation pawametews.
 *
 * @cs - Chip-sewect numbew.
 */
stwuct aemif_abus_data {
	u32 cs;
};

/**
 * stwuct aemif_pwatfowm_data - Data to set up the TI aemif dwivew.
 *
 * @dev_wookup: of_dev_auxdata passed to of_pwatfowm_popuwate() fow aemif
 *              subdevices.
 * @cs_offset: Wowest awwowed chip-sewect numbew.
 * @abus_data: Awway of async bus configuwation entwies.
 * @num_abus_data: Numbew of abus entwies.
 * @sub_devices: Awway of pwatfowm subdevices.
 * @num_sub_devices: Numbew of subdevices.
 */
stwuct aemif_pwatfowm_data {
	stwuct of_dev_auxdata *dev_wookup;
	u32 cs_offset;
	stwuct aemif_abus_data *abus_data;
	size_t num_abus_data;
	stwuct pwatfowm_device *sub_devices;
	size_t num_sub_devices;
};

#endif /* __TI_DAVINCI_AEMIF_DATA_H__ */
