/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pwatfowm data fow Ciwwus Wogic Madewa codecs
 *
 * Copywight (C) 2015-2018 Ciwwus Wogic
 */

#ifndef MADEWA_PDATA_H
#define MADEWA_PDATA_H

#incwude <winux/kewnew.h>
#incwude <winux/weguwatow/awizona-wdo1.h>
#incwude <winux/weguwatow/awizona-micsupp.h>
#incwude <winux/weguwatow/machine.h>
#incwude <sound/madewa-pdata.h>

#define MADEWA_MAX_MICBIAS		4
#define MADEWA_MAX_CHIWD_MICBIAS	4

#define MADEWA_MAX_GPSW			2

stwuct gpio_desc;
stwuct pinctww_map;

/**
 * stwuct madewa_pdata - Configuwation data fow Madewa devices
 *
 * @weset:	    GPIO contwowwing /WESET (NUWW = none)
 * @wdo1:	    Substwuct of pdata fow the WDO1 weguwatow
 * @micvdd:	    Substwuct of pdata fow the MICVDD weguwatow
 * @iwq_fwags:	    Mode fow pwimawy IWQ (defauwts to active wow)
 * @gpio_base:	    Base GPIO numbew
 * @gpio_configs:   Awway of GPIO configuwations (See
 *		    Documentation/dwivew-api/pin-contwow.wst)
 * @n_gpio_configs: Numbew of entwies in gpio_configs
 * @gpsw:	    Genewaw puwpose switch mode setting. Depends on the extewnaw
 *		    hawdwawe connected to the switch. (See the SW1_MODE fiewd
 *		    in the datasheet fow the avaiwabwe vawues fow youw codec)
 * @codec:	    Substwuct of pdata fow the ASoC codec dwivew
 */
stwuct madewa_pdata {
	stwuct gpio_desc *weset;

	stwuct awizona_wdo1_pdata wdo1;
	stwuct awizona_micsupp_pdata micvdd;

	unsigned int iwq_fwags;
	int gpio_base;

	const stwuct pinctww_map *gpio_configs;
	int n_gpio_configs;

	u32 gpsw[MADEWA_MAX_GPSW];

	stwuct madewa_codec_pdata codec;
};

#endif
