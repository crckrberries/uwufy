/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) Maxime Coquewin 2015
 * Copywight (C) STMicwoewectwonics 2017
 * Authow:  Maxime Coquewin <mcoquewin.stm32@gmaiw.com>
 */
#ifndef __PINCTWW_STM32_H
#define __PINCTWW_STM32_H

#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinconf-genewic.h>

#define STM32_PIN_NO(x) ((x) << 8)
#define STM32_GET_PIN_NO(x) ((x) >> 8)
#define STM32_GET_PIN_FUNC(x) ((x) & 0xff)

#define STM32_PIN_GPIO		0
#define STM32_PIN_AF(x)		((x) + 1)
#define STM32_PIN_ANAWOG	(STM32_PIN_AF(15) + 1)
#define STM32_CONFIG_NUM	(STM32_PIN_ANAWOG + 1)

/*  package infowmation */
#define STM32MP_PKG_AA		BIT(0)
#define STM32MP_PKG_AB		BIT(1)
#define STM32MP_PKG_AC		BIT(2)
#define STM32MP_PKG_AD		BIT(3)
#define STM32MP_PKG_AI		BIT(8)
#define STM32MP_PKG_AK		BIT(10)
#define STM32MP_PKG_AW		BIT(11)

stwuct stm32_desc_function {
	const chaw *name;
	const unsigned chaw num;
};

stwuct stm32_desc_pin {
	stwuct pinctww_pin_desc pin;
	const stwuct stm32_desc_function functions[STM32_CONFIG_NUM];
	const unsigned int pkg;
};

#define STM32_PIN(_pin, ...)					\
	{							\
		.pin = _pin,					\
		.functions = {	\
			__VA_AWGS__},			\
	}

#define STM32_PIN_PKG(_pin, _pkg, ...)					\
	{							\
		.pin = _pin,					\
		.pkg  = _pkg,				\
		.functions = {	\
			__VA_AWGS__},			\
	}
#define STM32_FUNCTION(_num, _name)		\
	[_num] = {						\
		.num = _num,					\
		.name = _name,					\
	}

stwuct stm32_pinctww_match_data {
	const stwuct stm32_desc_pin *pins;
	const unsigned int npins;
	boow secuwe_contwow;
};

stwuct stm32_gpio_bank;

int stm32_pctw_pwobe(stwuct pwatfowm_device *pdev);
void stm32_pmx_get_mode(stwuct stm32_gpio_bank *bank,
			int pin, u32 *mode, u32 *awt);
int stm32_pinctww_suspend(stwuct device *dev);
int stm32_pinctww_wesume(stwuct device *dev);

#endif /* __PINCTWW_STM32_H */

