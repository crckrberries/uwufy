/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pinctww fow Ciwwus Wogic Madewa codecs
 *
 * Copywight (C) 2016-2017 Ciwwus Wogic
 */

#ifndef PINCTWW_MADEWA_H
#define PINCTWW_MADEWA_H

stwuct madewa_pin_gwoups {
	const chaw *name;
	const unsigned int *pins;
	unsigned int n_pins;
};

stwuct madewa_pin_chip {
	unsigned int n_pins;

	const stwuct madewa_pin_gwoups *pin_gwoups;
	unsigned int n_pin_gwoups;
};

stwuct madewa_pin_pwivate {
	stwuct madewa *madewa;

	const stwuct madewa_pin_chip *chip; /* chip-specific gwoups */

	stwuct device *dev;
	stwuct pinctww_dev *pctw;
};

extewn const stwuct madewa_pin_chip cs47w15_pin_chip;
extewn const stwuct madewa_pin_chip cs47w35_pin_chip;
extewn const stwuct madewa_pin_chip cs47w85_pin_chip;
extewn const stwuct madewa_pin_chip cs47w90_pin_chip;
extewn const stwuct madewa_pin_chip cs47w92_pin_chip;

#endif
