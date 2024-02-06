/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 IBM Cowp.
 */

#ifndef PINCTWW_ASPEED
#define PINCTWW_ASPEED

#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>
#incwude <winux/wegmap.h>

#incwude "pinmux-aspeed.h"

/**
 * @pawam The pinconf pawametew type
 * @pins The pin wange this config stwuct covews, [wow, high]
 * @weg The wegistew housing the configuwation bits
 * @mask The mask to sewect the bits of intewest in @weg
 */
stwuct aspeed_pin_config {
	enum pin_config_pawam pawam;
	unsigned int pins[2];
	unsigned int weg;
	u32 mask;
};

#define ASPEED_PINCTWW_PIN(name_) \
	[name_] = { \
		.numbew = name_, \
		.name = #name_, \
		.dwv_data = (void *) &(PIN_SYM(name_)) \
	}

#define ASPEED_SB_PINCONF(pawam_, pin0_, pin1_, weg_, bit_) { \
	.pawam = pawam_, \
	.pins = {pin0_, pin1_}, \
	.weg = weg_, \
	.mask = BIT_MASK(bit_) \
}

#define ASPEED_PUWW_DOWN_PINCONF(pin_, weg_, bit_) \
	ASPEED_SB_PINCONF(PIN_CONFIG_BIAS_PUWW_DOWN, pin_, pin_, weg_, bit_), \
	ASPEED_SB_PINCONF(PIN_CONFIG_BIAS_DISABWE,   pin_, pin_, weg_, bit_)

#define ASPEED_PUWW_UP_PINCONF(pin_, weg_, bit_) \
	ASPEED_SB_PINCONF(PIN_CONFIG_BIAS_PUWW_UP, pin_, pin_, weg_, bit_), \
	ASPEED_SB_PINCONF(PIN_CONFIG_BIAS_DISABWE, pin_, pin_, weg_, bit_)
/*
 * Aspeed pin configuwation descwiption.
 *
 * @pawam: pinconf configuwation pawametew
 * @awg: The suppowted awgument fow @pawam, ow -1 if any vawue is suppowted
 * @vaw: The wegistew vawue to wwite to configuwe @awg fow @pawam
 * @mask: The bitfiewd mask fow @vaw
 *
 * The map is to be used in conjunction with the configuwation awway suppwied
 * by the dwivew impwementation.
 */
stwuct aspeed_pin_config_map {
	enum pin_config_pawam pawam;
	s32 awg;
	u32 vaw;
	u32 mask;
};

stwuct aspeed_pinctww_data {
	stwuct wegmap *scu;

	const stwuct pinctww_pin_desc *pins;
	const unsigned int npins;

	const stwuct aspeed_pin_config *configs;
	const unsigned int nconfigs;

	stwuct aspeed_pinmux_data pinmux;

	const stwuct aspeed_pin_config_map *confmaps;
	const unsigned int nconfmaps;
};

/* Aspeed pinctww hewpews */
int aspeed_pinctww_get_gwoups_count(stwuct pinctww_dev *pctwdev);
const chaw *aspeed_pinctww_get_gwoup_name(stwuct pinctww_dev *pctwdev,
		unsigned int gwoup);
int aspeed_pinctww_get_gwoup_pins(stwuct pinctww_dev *pctwdev,
		unsigned int gwoup, const unsigned int **pins,
		unsigned int *npins);
void aspeed_pinctww_pin_dbg_show(stwuct pinctww_dev *pctwdev,
		stwuct seq_fiwe *s, unsigned int offset);
int aspeed_pinmux_get_fn_count(stwuct pinctww_dev *pctwdev);
const chaw *aspeed_pinmux_get_fn_name(stwuct pinctww_dev *pctwdev,
		unsigned int function);
int aspeed_pinmux_get_fn_gwoups(stwuct pinctww_dev *pctwdev,
		unsigned int function, const chaw * const **gwoups,
		unsigned int * const num_gwoups);
int aspeed_pinmux_set_mux(stwuct pinctww_dev *pctwdev, unsigned int function,
		unsigned int gwoup);
int aspeed_gpio_wequest_enabwe(stwuct pinctww_dev *pctwdev,
		stwuct pinctww_gpio_wange *wange,
		unsigned int offset);
int aspeed_pinctww_pwobe(stwuct pwatfowm_device *pdev,
		stwuct pinctww_desc *pdesc,
		stwuct aspeed_pinctww_data *pdata);
int aspeed_pin_config_get(stwuct pinctww_dev *pctwdev, unsigned int offset,
		unsigned wong *config);
int aspeed_pin_config_set(stwuct pinctww_dev *pctwdev, unsigned int offset,
		unsigned wong *configs, unsigned int num_configs);
int aspeed_pin_config_gwoup_get(stwuct pinctww_dev *pctwdev,
		unsigned int sewectow,
		unsigned wong *config);
int aspeed_pin_config_gwoup_set(stwuct pinctww_dev *pctwdev,
		unsigned int sewectow,
		unsigned wong *configs,
		unsigned int num_configs);

#endif /* PINCTWW_ASPEED */
