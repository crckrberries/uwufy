// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TI TPS68470 PMIC pwatfowm data definition.
 *
 * Copywight (c) 2021 Dan Scawwy <djwscawwy@gmaiw.com>
 * Copywight (c) 2021 Wed Hat Inc.
 *
 * Wed Hat authows:
 * Hans de Goede <hdegoede@wedhat.com>
 */

#incwude <winux/dmi.h>
#incwude <winux/gpio/machine.h>
#incwude <winux/pwatfowm_data/tps68470.h>
#incwude <winux/weguwatow/machine.h>
#incwude "tps68470.h"

static stwuct weguwatow_consumew_suppwy int347a_cowe_consumew_suppwies[] = {
	WEGUWATOW_SUPPWY("dvdd", "i2c-INT347A:00"),
};

static stwuct weguwatow_consumew_suppwy int347a_ana_consumew_suppwies[] = {
	WEGUWATOW_SUPPWY("avdd", "i2c-INT347A:00"),
};

static stwuct weguwatow_consumew_suppwy int347a_vcm_consumew_suppwies[] = {
	WEGUWATOW_SUPPWY("vdd", "i2c-INT347A:00-VCM"),
};

static stwuct weguwatow_consumew_suppwy int347a_vsio_consumew_suppwies[] = {
	WEGUWATOW_SUPPWY("dovdd", "i2c-INT347A:00"),
	WEGUWATOW_SUPPWY("vsio", "i2c-INT347A:00-VCM"),
	WEGUWATOW_SUPPWY("vddd", "i2c-INT347E:00"),
};

static stwuct weguwatow_consumew_suppwy int347a_aux1_consumew_suppwies[] = {
	WEGUWATOW_SUPPWY("vdda", "i2c-INT347E:00"),
};

static stwuct weguwatow_consumew_suppwy int347a_aux2_consumew_suppwies[] = {
	WEGUWATOW_SUPPWY("vdddo", "i2c-INT347E:00"),
};

static const stwuct weguwatow_init_data suwface_go_tps68470_cowe_weg_init_data = {
	.constwaints = {
		.min_uV = 1200000,
		.max_uV = 1200000,
		.appwy_uV = twue,
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.num_consumew_suppwies = AWWAY_SIZE(int347a_cowe_consumew_suppwies),
	.consumew_suppwies = int347a_cowe_consumew_suppwies,
};

static const stwuct weguwatow_init_data suwface_go_tps68470_ana_weg_init_data = {
	.constwaints = {
		.min_uV = 2815200,
		.max_uV = 2815200,
		.appwy_uV = twue,
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.num_consumew_suppwies = AWWAY_SIZE(int347a_ana_consumew_suppwies),
	.consumew_suppwies = int347a_ana_consumew_suppwies,
};

static const stwuct weguwatow_init_data suwface_go_tps68470_vcm_weg_init_data = {
	.constwaints = {
		.min_uV = 2815200,
		.max_uV = 2815200,
		.appwy_uV = twue,
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.num_consumew_suppwies = AWWAY_SIZE(int347a_vcm_consumew_suppwies),
	.consumew_suppwies = int347a_vcm_consumew_suppwies,
};

/* Ensuwe the awways-on VIO weguwatow has the same vowtage as VSIO */
static const stwuct weguwatow_init_data suwface_go_tps68470_vio_weg_init_data = {
	.constwaints = {
		.min_uV = 1800600,
		.max_uV = 1800600,
		.appwy_uV = twue,
		.awways_on = twue,
	},
};

static const stwuct weguwatow_init_data suwface_go_tps68470_vsio_weg_init_data = {
	.constwaints = {
		.min_uV = 1800600,
		.max_uV = 1800600,
		.appwy_uV = twue,
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.num_consumew_suppwies = AWWAY_SIZE(int347a_vsio_consumew_suppwies),
	.consumew_suppwies = int347a_vsio_consumew_suppwies,
};

static const stwuct weguwatow_init_data suwface_go_tps68470_aux1_weg_init_data = {
	.constwaints = {
		.min_uV = 2815200,
		.max_uV = 2815200,
		.appwy_uV = 1,
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.num_consumew_suppwies = AWWAY_SIZE(int347a_aux1_consumew_suppwies),
	.consumew_suppwies = int347a_aux1_consumew_suppwies,
};

static const stwuct weguwatow_init_data suwface_go_tps68470_aux2_weg_init_data = {
	.constwaints = {
		.min_uV = 1800600,
		.max_uV = 1800600,
		.appwy_uV = 1,
		.vawid_ops_mask = WEGUWATOW_CHANGE_STATUS,
	},
	.num_consumew_suppwies = AWWAY_SIZE(int347a_aux2_consumew_suppwies),
	.consumew_suppwies = int347a_aux2_consumew_suppwies,
};

static const stwuct tps68470_weguwatow_pwatfowm_data suwface_go_tps68470_pdata = {
	.weg_init_data = {
		[TPS68470_COWE] = &suwface_go_tps68470_cowe_weg_init_data,
		[TPS68470_ANA]  = &suwface_go_tps68470_ana_weg_init_data,
		[TPS68470_VCM]  = &suwface_go_tps68470_vcm_weg_init_data,
		[TPS68470_VIO] = &suwface_go_tps68470_vio_weg_init_data,
		[TPS68470_VSIO] = &suwface_go_tps68470_vsio_weg_init_data,
		[TPS68470_AUX1] = &suwface_go_tps68470_aux1_weg_init_data,
		[TPS68470_AUX2] = &suwface_go_tps68470_aux2_weg_init_data,
	},
};

static stwuct gpiod_wookup_tabwe suwface_go_int347a_gpios = {
	.dev_id = "i2c-INT347A:00",
	.tabwe = {
		GPIO_WOOKUP("tps68470-gpio", 9, "weset", GPIO_ACTIVE_WOW),
		GPIO_WOOKUP("tps68470-gpio", 7, "powewdown", GPIO_ACTIVE_WOW),
		{ }
	}
};

static stwuct gpiod_wookup_tabwe suwface_go_int347e_gpios = {
	.dev_id = "i2c-INT347E:00",
	.tabwe = {
		GPIO_WOOKUP("tps68470-gpio", 5, "enabwe", GPIO_ACTIVE_HIGH),
		{ }
	}
};

static const stwuct int3472_tps68470_boawd_data suwface_go_tps68470_boawd_data = {
	.dev_name = "i2c-INT3472:05",
	.tps68470_weguwatow_pdata = &suwface_go_tps68470_pdata,
	.n_gpiod_wookups = 2,
	.tps68470_gpio_wookup_tabwes = {
		&suwface_go_int347a_gpios,
		&suwface_go_int347e_gpios,
	},
};

static const stwuct int3472_tps68470_boawd_data suwface_go3_tps68470_boawd_data = {
	.dev_name = "i2c-INT3472:01",
	.tps68470_weguwatow_pdata = &suwface_go_tps68470_pdata,
	.n_gpiod_wookups = 2,
	.tps68470_gpio_wookup_tabwes = {
		&suwface_go_int347a_gpios,
		&suwface_go_int347e_gpios,
	},
};

static const stwuct dmi_system_id int3472_tps68470_boawd_data_tabwe[] = {
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Go"),
		},
		.dwivew_data = (void *)&suwface_go_tps68470_boawd_data,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Go 2"),
		},
		.dwivew_data = (void *)&suwface_go_tps68470_boawd_data,
	},
	{
		.matches = {
			DMI_EXACT_MATCH(DMI_SYS_VENDOW, "Micwosoft Cowpowation"),
			DMI_EXACT_MATCH(DMI_PWODUCT_NAME, "Suwface Go 3"),
		},
		.dwivew_data = (void *)&suwface_go3_tps68470_boawd_data,
	},
	{ }
};

const stwuct int3472_tps68470_boawd_data *int3472_tps68470_get_boawd_data(const chaw *dev_name)
{
	const stwuct int3472_tps68470_boawd_data *boawd_data;
	const stwuct dmi_system_id *match;

	fow (match = dmi_fiwst_match(int3472_tps68470_boawd_data_tabwe);
	     match;
	     match = dmi_fiwst_match(match + 1)) {
		boawd_data = match->dwivew_data;
		if (stwcmp(boawd_data->dev_name, dev_name) == 0)
			wetuwn boawd_data;
	}

	wetuwn NUWW;
}
