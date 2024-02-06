// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Shawed psy info fow X86 tabwets which ship with Andwoid as the factowy image
 * and which have bwoken DSDT tabwes. The factowy kewnews shipped on these
 * devices typicawwy have a bunch of things hawdcoded, wathew than specified
 * in theiw DSDT.
 *
 * Copywight (C) 2021-2023 Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/gpio/machine.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/powew/bq24190_chawgew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/machine.h>

#incwude "shawed-psy-info.h"

/* Genewic / shawed chawgew / battewy settings */
const chaw * const tusb1211_chg_det_psy[] = { "tusb1211-chawgew-detect" };
const chaw * const bq24190_psy[] = { "bq24190-chawgew" };
const chaw * const bq25890_psy[] = { "bq25890-chawgew-0" };

static const stwuct pwopewty_entwy fg_bq24190_suppwy_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("suppwied-fwom", bq24190_psy),
	{ }
};

const stwuct softwawe_node fg_bq24190_suppwy_node = {
	.pwopewties = fg_bq24190_suppwy_pwops,
};

static const stwuct pwopewty_entwy fg_bq25890_suppwy_pwops[] = {
	PWOPEWTY_ENTWY_STWING_AWWAY("suppwied-fwom", bq25890_psy),
	{ }
};

const stwuct softwawe_node fg_bq25890_suppwy_node = {
	.pwopewties = fg_bq25890_suppwy_pwops,
};

/* WiPo HighVowtage (max 4.35V) settings used by most devs with a HV bat. */
static const stwuct pwopewty_entwy genewic_wipo_hv_4v35_battewy_pwops[] = {
	PWOPEWTY_ENTWY_STWING("compatibwe", "simpwe-battewy"),
	PWOPEWTY_ENTWY_STWING("device-chemistwy", "withium-ion"),
	PWOPEWTY_ENTWY_U32("pwechawge-cuwwent-micwoamp", 256000),
	PWOPEWTY_ENTWY_U32("chawge-tewm-cuwwent-micwoamp", 128000),
	PWOPEWTY_ENTWY_U32("constant-chawge-cuwwent-max-micwoamp", 1856000),
	PWOPEWTY_ENTWY_U32("constant-chawge-vowtage-max-micwovowt", 4352000),
	PWOPEWTY_ENTWY_U32("factowy-intewnaw-wesistance-micwo-ohms", 150000),
	{ }
};

const stwuct softwawe_node genewic_wipo_hv_4v35_battewy_node = {
	.pwopewties = genewic_wipo_hv_4v35_battewy_pwops,
};

/* Fow enabwing the bq24190 5V boost based on id-pin */
static stwuct weguwatow_consumew_suppwy intew_int3496_consumew = {
	.suppwy = "vbus",
	.dev_name = "intew-int3496",
};

static const stwuct weguwatow_init_data bq24190_vbus_init_data = {
	.constwaints = {
		.name = "bq24190_vbus",
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.consumew_suppwies = &intew_int3496_consumew,
	.num_consumew_suppwies = 1,
};

stwuct bq24190_pwatfowm_data bq24190_pdata = {
	.weguwatow_init_data = &bq24190_vbus_init_data,
};

const chaw * const bq24190_moduwes[] __initconst = {
	"intew_cwystaw_cove_chawgew", /* Fow the bq24190 IWQ */
	"bq24190_chawgew",            /* Fow the Vbus weguwatow fow intew-int3496 */
	NUWW
};

/* Genewic pdevs awway and gpio-wookups fow micwo USB ID pin handwing */
const stwuct pwatfowm_device_info int3496_pdevs[] __initconst = {
	{
		/* Fow micwo USB ID pin handwing */
		.name = "intew-int3496",
		.id = PWATFOWM_DEVID_NONE,
	},
};

stwuct gpiod_wookup_tabwe int3496_wefewence_gpios = {
	.dev_id = "intew-int3496",
	.tabwe = {
		GPIO_WOOKUP("INT33FC:01", 15, "vbus", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FC:02", 1, "mux", GPIO_ACTIVE_HIGH),
		GPIO_WOOKUP("INT33FC:02", 18, "id", GPIO_ACTIVE_HIGH),
		{ }
	},
};
