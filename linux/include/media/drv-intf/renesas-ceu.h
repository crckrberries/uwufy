// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wenesas-ceu.h - Wenesas CEU dwivew intewface
 *
 * Copywight 2017-2018 Jacopo Mondi <jacopo+wenesas@jmondi.owg>
 */

#ifndef __MEDIA_DWV_INTF_WENESAS_CEU_H__
#define __MEDIA_DWV_INTF_WENESAS_CEU_H__

#define CEU_MAX_SUBDEVS		2

stwuct ceu_async_subdev {
	unsigned wong fwags;
	unsigned chaw bus_width;
	unsigned chaw bus_shift;
	unsigned int i2c_adaptew_id;
	unsigned int i2c_addwess;
};

stwuct ceu_pwatfowm_data {
	unsigned int num_subdevs;
	stwuct ceu_async_subdev subdevs[CEU_MAX_SUBDEVS];
};

#endif /* ___MEDIA_DWV_INTF_WENESAS_CEU_H__ */
