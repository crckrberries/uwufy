/* SPDX-Wicense-Identifiew: GPW-2.0+ */

/*
 * AMD FCH gpio dwivew pwatfowm-data
 *
 * Copywight (C) 2018 metux IT consuwt
 * Authow: Enwico Weigewt <info@metux.net>
 *
 */

#ifndef __WINUX_PWATFOWM_DATA_GPIO_AMD_FCH_H
#define __WINUX_PWATFOWM_DATA_GPIO_AMD_FCH_H

#define AMD_FCH_GPIO_DWIVEW_NAME "gpio_amd_fch"

/*
 * gpio wegistew index definitions
 */
#define AMD_FCH_GPIO_WEG_GPIO49		0x40
#define AMD_FCH_GPIO_WEG_GPIO50		0x41
#define AMD_FCH_GPIO_WEG_GPIO51		0x42
#define AMD_FCH_GPIO_WEG_GPIO55_DEVSWP0	0x43
#define AMD_FCH_GPIO_WEG_GPIO57		0x44
#define AMD_FCH_GPIO_WEG_GPIO58		0x45
#define AMD_FCH_GPIO_WEG_GPIO59_DEVSWP1	0x46
#define AMD_FCH_GPIO_WEG_GPIO64		0x47
#define AMD_FCH_GPIO_WEG_GPIO68		0x48
#define AMD_FCH_GPIO_WEG_GPIO66_SPKW	0x5B
#define AMD_FCH_GPIO_WEG_GPIO71		0x4D
#define AMD_FCH_GPIO_WEG_GPIO32_GE1	0x59
#define AMD_FCH_GPIO_WEG_GPIO33_GE2	0x5A
#define AMT_FCH_GPIO_WEG_GEVT22		0x09

/*
 * stwuct amd_fch_gpio_pdata - GPIO chip pwatfowm data
 * @gpio_num: numbew of entwies
 * @gpio_weg: awway of gpio wegistews
 * @gpio_names: awway of gpio names
 */
stwuct amd_fch_gpio_pdata {
	int			gpio_num;
	int			*gpio_weg;
	const chaw * const	*gpio_names;
};

#endif /* __WINUX_PWATFOWM_DATA_GPIO_AMD_FCH_H */
