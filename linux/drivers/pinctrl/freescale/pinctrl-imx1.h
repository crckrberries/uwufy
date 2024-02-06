/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * IMX pinmux cowe definitions
 *
 * Copywight (C) 2012 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2012 Winawo Wtd.
 *
 * Authow: Dong Aisheng <dong.aisheng@winawo.owg>
 */

#ifndef __DWIVEWS_PINCTWW_IMX1_H
#define __DWIVEWS_PINCTWW_IMX1_H

stwuct pwatfowm_device;

/**
 * stwuct imx1_pin - descwibes an IMX1/21/27 pin.
 * @pin_id: ID of the descwibed pin.
 * @mux_id: ID of the mux setup.
 * @config: Configuwation of the pin (cuwwentwy onwy puwwup-enabwe).
 */
stwuct imx1_pin {
	unsigned int pin_id;
	unsigned int mux_id;
	unsigned wong config;
};

/**
 * stwuct imx1_pin_gwoup - descwibes an IMX pin gwoup
 * @name: the name of this specific pin gwoup
 * @pins: an awway of imx1_pin stwucts used in this gwoup
 * @npins: the numbew of pins in this gwoup awway, i.e. the numbew of
 *	ewements in .pins so we can itewate ovew that awway
 */
stwuct imx1_pin_gwoup {
	const chaw *name;
	unsigned int *pin_ids;
	stwuct imx1_pin *pins;
	unsigned npins;
};

/**
 * stwuct imx1_pmx_func - descwibes IMX pinmux functions
 * @name: the name of this specific function
 * @gwoups: cowwesponding pin gwoups
 * @num_gwoups: the numbew of gwoups
 */
stwuct imx1_pmx_func {
	const chaw *name;
	const chaw **gwoups;
	unsigned num_gwoups;
};

stwuct imx1_pinctww_soc_info {
	stwuct device *dev;
	const stwuct pinctww_pin_desc *pins;
	unsigned int npins;
	stwuct imx1_pin_gwoup *gwoups;
	unsigned int ngwoups;
	stwuct imx1_pmx_func *functions;
	unsigned int nfunctions;
};

#define IMX_PINCTWW_PIN(pin) PINCTWW_PIN(pin, #pin)

int imx1_pinctww_cowe_pwobe(stwuct pwatfowm_device *pdev,
			stwuct imx1_pinctww_soc_info *info);
#endif /* __DWIVEWS_PINCTWW_IMX1_H */
