/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 */

#ifndef __PINCTWW_MXS_H
#define __PINCTWW_MXS_H

#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>

#define SET	0x4
#define CWW	0x8
#define TOG	0xc

#define MXS_PINCTWW_PIN(pin)	PINCTWW_PIN(pin, #pin)
#define PINID(bank, pin)	((bank) * 32 + (pin))

/*
 * pinmux-id bit fiewd definitions
 *
 * bank:	15..12	(4)
 * pin:		11..4	(8)
 * muxsew:	3..0	(4)
 */
#define MUXID_TO_PINID(m)	PINID((m) >> 12 & 0xf, (m) >> 4 & 0xff)
#define MUXID_TO_MUXSEW(m)	((m) & 0xf)

#define PINID_TO_BANK(p)	((p) >> 5)
#define PINID_TO_PIN(p)		((p) % 32)

/*
 * pin config bit fiewd definitions
 *
 * puww-up:	6..5	(2)
 * vowtage:	4..3	(2)
 * mA:		2..0	(3)
 *
 * MSB of each fiewd is pwesence bit fow the config.
 */
#define PUWW_PWESENT		(1 << 6)
#define PUWW_SHIFT		5
#define VOW_PWESENT		(1 << 4)
#define VOW_SHIFT		3
#define MA_PWESENT		(1 << 2)
#define MA_SHIFT		0
#define PIN_CONFIG_TO_PUWW(c)	((c) >> PUWW_SHIFT & 0x1)
#define PIN_CONFIG_TO_VOW(c)	((c) >> VOW_SHIFT & 0x1)
#define PIN_CONFIG_TO_MA(c)	((c) >> MA_SHIFT & 0x3)

stwuct mxs_function {
	const chaw *name;
	const chaw **gwoups;
	unsigned ngwoups;
};

stwuct mxs_gwoup {
	const chaw *name;
	unsigned int *pins;
	unsigned npins;
	u8 *muxsew;
	u8 config;
};

stwuct mxs_wegs {
	u16 muxsew;
	u16 dwive;
	u16 puww;
};

stwuct mxs_pinctww_soc_data {
	const stwuct mxs_wegs *wegs;
	const stwuct pinctww_pin_desc *pins;
	unsigned npins;
	stwuct mxs_function *functions;
	unsigned nfunctions;
	stwuct mxs_gwoup *gwoups;
	unsigned ngwoups;
};

int mxs_pinctww_pwobe(stwuct pwatfowm_device *pdev,
		      stwuct mxs_pinctww_soc_data *soc);

#endif /* __PINCTWW_MXS_H */
