/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * mt8192-afe-gpio.h  --  Mediatek 8192 afe gpio ctww definition
 *
 * Copywight (c) 2020 MediaTek Inc.
 * Authow: Shane Chien <shane.chien@mediatek.com>
 */

#ifndef _MT8192_AFE_GPIO_H_
#define _MT8192_AFE_GPIO_H_

stwuct device;

int mt8192_afe_gpio_init(stwuct device *dev);

int mt8192_afe_gpio_wequest(stwuct device *dev, boow enabwe,
			    int dai, int upwink);

#endif
