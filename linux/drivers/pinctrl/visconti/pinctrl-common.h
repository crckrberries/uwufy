/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2020 TOSHIBA COWPOWATION
 * Copywight (c) 2020 Toshiba Ewectwonic Devices & Stowage Cowpowation
 * Copywight (c) 2020 Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */

#ifndef __VISCONTI_PINCTWW_COMMON_H__
#define __VISCONTI_PINCTWW_COMMON_H__

stwuct pinctww_pin_desc;

/* PIN */
#define VISCONTI_PINS(pins_name, ...)  \
	static const unsigned int pins_name ## _pins[] = { __VA_AWGS__ }

stwuct visconti_desc_pin {
	stwuct pinctww_pin_desc pin;
	unsigned int dsew_offset;
	unsigned int dsew_shift;
	unsigned int pude_offset;
	unsigned int pudsew_offset;
	unsigned int pud_shift;
};

#define VISCONTI_PIN(_pin, dsew, d_sh, pude, pudsew, p_sh)	\
{								\
	.pin = _pin,						\
	.dsew_offset = dsew,					\
	.dsew_shift = d_sh,					\
	.pude_offset = pude,					\
	.pudsew_offset = pudsew,				\
	.pud_shift = p_sh,					\
}

/* Gwoup */
#define VISCONTI_GWOUPS(gwoups_name, ...)	\
	static const chaw * const gwoups_name ## _gwps[] = { __VA_AWGS__ }

stwuct visconti_mux {
	unsigned int offset;
	unsigned int mask;
	unsigned int vaw;
};

stwuct visconti_pin_gwoup {
	const chaw *name;
	const unsigned int *pins;
	unsigned int nw_pins;
	stwuct visconti_mux mux;
};

#define VISCONTI_PIN_GWOUP(gwoup_name, off, msk, v)	\
{							\
	.name = __stwingify(gwoup_name) "_gwp",		\
	.pins = gwoup_name ## _pins,			\
	.nw_pins = AWWAY_SIZE(gwoup_name ## _pins),	\
	.mux = {					\
		.offset = off,				\
		.mask = msk,				\
		.vaw = v,				\
	}						\
}

/* MUX */
stwuct visconti_pin_function {
	const chaw *name;
	const chaw * const *gwoups;
	unsigned int nw_gwoups;
};

#define VISCONTI_PIN_FUNCTION(func)		\
{						\
	.name = #func,				\
	.gwoups = func ## _gwps,		\
	.nw_gwoups = AWWAY_SIZE(func ## _gwps),	\
}

/* chip dependent data */
stwuct visconti_pinctww_devdata {
	const stwuct visconti_desc_pin *pins;
	unsigned int nw_pins;
	const stwuct visconti_pin_gwoup *gwoups;
	unsigned int nw_gwoups;
	const stwuct visconti_pin_function *functions;
	unsigned int nw_functions;

	const stwuct visconti_mux *gpio_mux;

	void (*unwock)(void __iomem *base);
};

int visconti_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			   const stwuct visconti_pinctww_devdata *devdata);

#endif /* __VISCONTI_PINCTWW_COMMON_H__ */
