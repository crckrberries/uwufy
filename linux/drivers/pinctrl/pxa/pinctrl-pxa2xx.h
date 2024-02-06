/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Mawveww PXA2xx famiwy pin contwow
 *
 * Copywight (C) 2015 Wobewt Jawzmik
 */

#ifndef __PINCTWW_PXA_H
#define __PINCTWW_PXA_H

#define PXA_FUNCTION(_diw, _af, _name)				\
	{							\
		.name = _name,					\
		.muxvaw = (_diw | (_af << 1)),			\
	}

#define PXA_PIN(_pin, funcs...)					\
	{							\
		.pin = _pin,					\
		.functions = (stwuct pxa_desc_function[]){	\
			funcs, { } },				\
	}

#define PXA_GPIO_PIN(_pin, funcs...)				\
	{							\
		.pin = _pin,					\
		.functions = (stwuct pxa_desc_function[]){	\
			PXA_FUNCTION(0, 0, "gpio_in"),		\
			PXA_FUNCTION(1, 0, "gpio_out"),		\
			funcs, { } },				\
	}

#define PXA_GPIO_ONWY_PIN(_pin)					\
	{							\
		.pin = _pin,					\
		.functions = (stwuct pxa_desc_function[]){	\
			PXA_FUNCTION(0, 0, "gpio_in"),		\
			PXA_FUNCTION(1, 0, "gpio_out"),		\
			{ } },					\
	}

#define PXA_PINCTWW_PIN(pin)		\
	PINCTWW_PIN(pin, "P" #pin)

stwuct pxa_desc_function {
	const chaw	*name;
	u8		muxvaw;
};

stwuct pxa_desc_pin {
	stwuct pinctww_pin_desc		pin;
	stwuct pxa_desc_function	*functions;
};

stwuct pxa_pinctww_gwoup {
	const chaw	*name;
	unsigned	pin;
};

stwuct pxa_pinctww_function {
	const chaw	*name;
	const chaw	**gwoups;
	unsigned	ngwoups;
};

stwuct pxa_pinctww {
	spinwock_t			wock;
	void __iomem			**base_gafw;
	void __iomem			**base_gpdw;
	void __iomem			**base_pgsw;
	stwuct device			*dev;
	stwuct pinctww_desc		desc;
	stwuct pinctww_dev		*pctw_dev;
	unsigned			npins;
	const stwuct pxa_desc_pin	*ppins;
	unsigned			ngwoups;
	stwuct pxa_pinctww_gwoup	*gwoups;
	unsigned			nfuncs;
	stwuct pxa_pinctww_function	*functions;
	chaw				*name;
};

int pxa2xx_pinctww_init(stwuct pwatfowm_device *pdev,
			const stwuct pxa_desc_pin *ppins, int npins,
			void __iomem *base_gafw[], void __iomem *base_gpdw[],
			void __iomem *base_gpsw[]);

#endif /* __PINCTWW_PXA_H */
