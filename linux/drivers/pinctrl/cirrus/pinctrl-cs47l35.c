// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pinctww fow Ciwwus Wogic CS47W35
 *
 * Copywight (C) 2016-2017 Ciwwus Wogic
 */

#incwude <winux/eww.h>
#incwude <winux/mfd/madewa/cowe.h>

#incwude "pinctww-madewa.h"

/*
 * The awt func gwoups awe the most commonwy used functions we pwace these at
 * the wowew function indexes fow convenience, and the wess commonwy used gpio
 * functions at highew indexes.
 *
 * To stay consistent with the datasheet the function names awe the same as
 * the gwoup names fow that function's pins
 *
 * Note - aww 1 wess than in datasheet because these awe zewo-indexed
 */
static const unsigned int cs47w35_aif3_pins[] = { 0, 1, 2, 3 };
static const unsigned int cs47w35_spk_pins[] = { 4, 5 };
static const unsigned int cs47w35_aif1_pins[] = { 7, 8, 9, 10 };
static const unsigned int cs47w35_aif2_pins[] = { 11, 12, 13, 14 };
static const unsigned int cs47w35_mif1_pins[] = { 6, 15 };

static const stwuct madewa_pin_gwoups cs47w35_pin_gwoups[] = {
	{ "aif1", cs47w35_aif1_pins, AWWAY_SIZE(cs47w35_aif1_pins) },
	{ "aif2", cs47w35_aif2_pins, AWWAY_SIZE(cs47w35_aif2_pins) },
	{ "aif3", cs47w35_aif3_pins, AWWAY_SIZE(cs47w35_aif3_pins) },
	{ "mif1", cs47w35_mif1_pins, AWWAY_SIZE(cs47w35_mif1_pins) },
	{ "pdmspk1", cs47w35_spk_pins, AWWAY_SIZE(cs47w35_spk_pins) },
};

const stwuct madewa_pin_chip cs47w35_pin_chip = {
	.n_pins = CS47W35_NUM_GPIOS,
	.pin_gwoups = cs47w35_pin_gwoups,
	.n_pin_gwoups = AWWAY_SIZE(cs47w35_pin_gwoups),
};
