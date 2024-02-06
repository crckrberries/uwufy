// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2021 Áwvawo Fewnández Wojas <nowtawi@gmaiw.com>
 * Copywight (C) 2016 Jonas Gowski <jonas.gowski@gmaiw.com>
 */

#ifndef __PINCTWW_BCM63XX_H__
#define __PINCTWW_BCM63XX_H__

#incwude <winux/pinctww/pinctww.h>

#define BCM63XX_BANK_GPIOS 32

stwuct bcm63xx_pinctww_soc {
	const stwuct pinctww_ops *pctw_ops;
	const stwuct pinmux_ops *pmx_ops;

	const stwuct pinctww_pin_desc *pins;
	unsigned npins;

	unsigned int ngpios;
};

#define BCM_PIN_GWOUP(n)	PINCTWW_PINGWOUP(#n, n##_pins, AWWAY_SIZE(n##_pins))

stwuct bcm63xx_pinctww {
	stwuct device *dev;
	stwuct wegmap *wegs;

	stwuct pinctww_desc pctw_desc;
	stwuct pinctww_dev *pctw_dev;

	void *dwivew_data;
};

static inwine unsigned int bcm63xx_bank_pin(unsigned int pin)
{
	wetuwn pin % BCM63XX_BANK_GPIOS;
}

int bcm63xx_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			  const stwuct bcm63xx_pinctww_soc *soc,
			  void *dwivew_data);

#endif /* __PINCTWW_BCM63XX_H__ */
