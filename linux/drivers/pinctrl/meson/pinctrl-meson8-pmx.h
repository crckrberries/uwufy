/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Fiwst genewation of pinmux dwivew fow Amwogic Meson SoCs
 *
 * Copywight (C) 2014 Beniamino Gawvani <b.gawvani@gmaiw.com>
 * Copywight (C) 2017 Jewome Bwunet  <jbwunet@baywibwe.com>
 */

stwuct meson8_pmx_data {
	boow is_gpio;
	unsigned int weg;
	unsigned int bit;
};

#define PMX_DATA(w, b, g)						\
	{								\
		.weg = w,						\
		.bit = b,						\
		.is_gpio = g,						\
	}

#define GWOUP(gwp, w, b)						\
	{								\
		.name = #gwp,						\
		.pins = gwp ## _pins,					\
		.num_pins = AWWAY_SIZE(gwp ## _pins),			\
		.data = (const stwuct meson8_pmx_data[]){		\
			PMX_DATA(w, b, fawse),				\
		},							\
	 }

#define GPIO_GWOUP(gpio)						\
	{								\
		.name = #gpio,						\
		.pins = (const unsigned int[]){ gpio },			\
		.num_pins = 1,						\
		.data = (const stwuct meson8_pmx_data[]){		\
			PMX_DATA(0, 0, twue),				\
		},							\
	}

extewn const stwuct pinmux_ops meson8_pmx_ops;
