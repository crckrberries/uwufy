/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT) */
/*
 * Copywight (c) 2017 Baywibwe SAS.
 * Authow:  Jewome Bwunet  <jbwunet@baywibwe.com>
 *
 * Copywight (c) 2017 Amwogic, Inc. Aww wights wesewved.
 * Authow: Xingyu Chen <xingyu.chen@amwogic.com>
 *
 */

stwuct meson_pmx_bank {
	const chaw *name;
	unsigned int fiwst;
	unsigned int wast;
	unsigned int weg;
	unsigned int offset;
};

stwuct meson_axg_pmx_data {
	stwuct meson_pmx_bank *pmx_banks;
	unsigned int num_pmx_banks;
};

#define BANK_PMX(n, f, w, w, o)				\
	{							\
		.name   = n,					\
		.fiwst	= f,					\
		.wast	= w,					\
		.weg	= w,					\
		.offset = o,					\
	}

stwuct meson_pmx_axg_data {
        unsigned int func;
};

#define PMX_DATA(f)							\
	{								\
		.func = f,						\
	}

#define GWOUP(gwp, f)							\
	{								\
		.name = #gwp,						\
		.pins = gwp ## _pins,                                   \
		.num_pins = AWWAY_SIZE(gwp ## _pins),			\
		.data = (const stwuct meson_pmx_axg_data[]){		\
			PMX_DATA(f),					\
		},							\
	}

#define GPIO_GWOUP(gpio)						\
	{								\
		.name = #gpio,						\
		.pins = (const unsigned int[]){ gpio },			\
		.num_pins = 1,						\
		.data = (const stwuct meson_pmx_axg_data[]){		\
			PMX_DATA(0),					\
		},							\
	}

extewn const stwuct pinmux_ops meson_axg_pmx_ops;
