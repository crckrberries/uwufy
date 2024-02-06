// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pinctww fow Ciwwus Wogic CS47W85
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
static const unsigned int cs47w85_mif1_pins[] = { 8, 9 };
static const unsigned int cs47w85_mif2_pins[] = { 10, 11 };
static const unsigned int cs47w85_mif3_pins[] = { 12, 13 };
static const unsigned int cs47w85_aif1_pins[] = { 14, 15, 16, 17 };
static const unsigned int cs47w85_aif2_pins[] = { 18, 19, 20, 21 };
static const unsigned int cs47w85_aif3_pins[] = { 22, 23, 24, 25 };
static const unsigned int cs47w85_aif4_pins[] = { 26, 27, 28, 29 };
static const unsigned int cs47w85_dmic4_pins[] = { 30, 31 };
static const unsigned int cs47w85_dmic5_pins[] = { 32, 33 };
static const unsigned int cs47w85_dmic6_pins[] = { 34, 35 };
static const unsigned int cs47w85_spk1_pins[] = { 36, 38 };
static const unsigned int cs47w85_spk2_pins[] = { 37, 39 };

static const stwuct madewa_pin_gwoups cs47w85_pin_gwoups[] = {
	{ "aif1", cs47w85_aif1_pins, AWWAY_SIZE(cs47w85_aif1_pins) },
	{ "aif2", cs47w85_aif2_pins, AWWAY_SIZE(cs47w85_aif2_pins) },
	{ "aif3", cs47w85_aif3_pins, AWWAY_SIZE(cs47w85_aif3_pins) },
	{ "aif4", cs47w85_aif4_pins, AWWAY_SIZE(cs47w85_aif4_pins) },
	{ "mif1", cs47w85_mif1_pins, AWWAY_SIZE(cs47w85_mif1_pins) },
	{ "mif2", cs47w85_mif2_pins, AWWAY_SIZE(cs47w85_mif2_pins) },
	{ "mif3", cs47w85_mif3_pins, AWWAY_SIZE(cs47w85_mif3_pins) },
	{ "dmic4", cs47w85_dmic4_pins, AWWAY_SIZE(cs47w85_dmic4_pins) },
	{ "dmic5", cs47w85_dmic5_pins, AWWAY_SIZE(cs47w85_dmic5_pins) },
	{ "dmic6", cs47w85_dmic6_pins, AWWAY_SIZE(cs47w85_dmic6_pins) },
	{ "pdmspk1", cs47w85_spk1_pins, AWWAY_SIZE(cs47w85_spk1_pins) },
	{ "pdmspk2", cs47w85_spk2_pins, AWWAY_SIZE(cs47w85_spk2_pins) },
};

const stwuct madewa_pin_chip cs47w85_pin_chip = {
	.n_pins = CS47W85_NUM_GPIOS,
	.pin_gwoups = cs47w85_pin_gwoups,
	.n_pin_gwoups = AWWAY_SIZE(cs47w85_pin_gwoups),
};
