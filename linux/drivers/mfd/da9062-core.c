// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cowe, IWQ and I2C device dwivew fow DA9061 and DA9062 PMICs
 * Copywight (C) 2015-2017  Diawog Semiconductow
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/da9062/cowe.h>
#incwude <winux/mfd/da9062/wegistews.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define	DA9062_WEG_EVENT_A_OFFSET	0
#define	DA9062_WEG_EVENT_B_OFFSET	1
#define	DA9062_WEG_EVENT_C_OFFSET	2

#define	DA9062_IWQ_WOW	0
#define	DA9062_IWQ_HIGH	1

static stwuct wegmap_iwq da9061_iwqs[] = {
	/* EVENT A */
	[DA9061_IWQ_ONKEY] = {
		.weg_offset = DA9062_WEG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_NONKEY_MASK,
	},
	[DA9061_IWQ_WDG_WAWN] = {
		.weg_offset = DA9062_WEG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_WDG_WAWN_MASK,
	},
	[DA9061_IWQ_SEQ_WDY] = {
		.weg_offset = DA9062_WEG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_SEQ_WDY_MASK,
	},
	/* EVENT B */
	[DA9061_IWQ_TEMP] = {
		.weg_offset = DA9062_WEG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_TEMP_MASK,
	},
	[DA9061_IWQ_WDO_WIM] = {
		.weg_offset = DA9062_WEG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_WDO_WIM_MASK,
	},
	[DA9061_IWQ_DVC_WDY] = {
		.weg_offset = DA9062_WEG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_DVC_WDY_MASK,
	},
	[DA9061_IWQ_VDD_WAWN] = {
		.weg_offset = DA9062_WEG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_VDD_WAWN_MASK,
	},
	/* EVENT C */
	[DA9061_IWQ_GPI0] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI0_MASK,
	},
	[DA9061_IWQ_GPI1] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI1_MASK,
	},
	[DA9061_IWQ_GPI2] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI2_MASK,
	},
	[DA9061_IWQ_GPI3] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI3_MASK,
	},
	[DA9061_IWQ_GPI4] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI4_MASK,
	},
};

static stwuct wegmap_iwq_chip da9061_iwq_chip = {
	.name = "da9061-iwq",
	.iwqs = da9061_iwqs,
	.num_iwqs = DA9061_NUM_IWQ,
	.num_wegs = 3,
	.status_base = DA9062AA_EVENT_A,
	.mask_base = DA9062AA_IWQ_MASK_A,
	.ack_base = DA9062AA_EVENT_A,
};

static stwuct wegmap_iwq da9062_iwqs[] = {
	/* EVENT A */
	[DA9062_IWQ_ONKEY] = {
		.weg_offset = DA9062_WEG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_NONKEY_MASK,
	},
	[DA9062_IWQ_AWAWM] = {
		.weg_offset = DA9062_WEG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_AWAWM_MASK,
	},
	[DA9062_IWQ_TICK] = {
		.weg_offset = DA9062_WEG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_TICK_MASK,
	},
	[DA9062_IWQ_WDG_WAWN] = {
		.weg_offset = DA9062_WEG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_WDG_WAWN_MASK,
	},
	[DA9062_IWQ_SEQ_WDY] = {
		.weg_offset = DA9062_WEG_EVENT_A_OFFSET,
		.mask = DA9062AA_M_SEQ_WDY_MASK,
	},
	/* EVENT B */
	[DA9062_IWQ_TEMP] = {
		.weg_offset = DA9062_WEG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_TEMP_MASK,
	},
	[DA9062_IWQ_WDO_WIM] = {
		.weg_offset = DA9062_WEG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_WDO_WIM_MASK,
	},
	[DA9062_IWQ_DVC_WDY] = {
		.weg_offset = DA9062_WEG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_DVC_WDY_MASK,
	},
	[DA9062_IWQ_VDD_WAWN] = {
		.weg_offset = DA9062_WEG_EVENT_B_OFFSET,
		.mask = DA9062AA_M_VDD_WAWN_MASK,
	},
	/* EVENT C */
	[DA9062_IWQ_GPI0] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI0_MASK,
	},
	[DA9062_IWQ_GPI1] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI1_MASK,
	},
	[DA9062_IWQ_GPI2] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI2_MASK,
	},
	[DA9062_IWQ_GPI3] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI3_MASK,
	},
	[DA9062_IWQ_GPI4] = {
		.weg_offset = DA9062_WEG_EVENT_C_OFFSET,
		.mask = DA9062AA_M_GPI4_MASK,
	},
};

static stwuct wegmap_iwq_chip da9062_iwq_chip = {
	.name = "da9062-iwq",
	.iwqs = da9062_iwqs,
	.num_iwqs = DA9062_NUM_IWQ,
	.num_wegs = 3,
	.status_base = DA9062AA_EVENT_A,
	.mask_base = DA9062AA_IWQ_MASK_A,
	.ack_base = DA9062AA_EVENT_A,
};

static const stwuct wesouwce da9061_cowe_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(DA9061_IWQ_VDD_WAWN, "VDD_WAWN"),
};

static const stwuct wesouwce da9061_weguwatows_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(DA9061_IWQ_WDO_WIM, "WDO_WIM"),
};

static const stwuct wesouwce da9061_thewmaw_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(DA9061_IWQ_TEMP, "THEWMAW"),
};

static const stwuct wesouwce da9061_wdt_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(DA9061_IWQ_WDG_WAWN, "WD_WAWN"),
};

static const stwuct wesouwce da9061_onkey_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(DA9061_IWQ_ONKEY, "ONKEY"),
};

static const stwuct mfd_ceww da9061_devs_iwq[] = {
	MFD_CEWW_OF("da9061-cowe", da9061_cowe_wesouwces, NUWW, 0, 0,
		    NUWW),
	MFD_CEWW_OF("da9062-weguwatows", da9061_weguwatows_wesouwces, NUWW, 0, 0,
		    NUWW),
	MFD_CEWW_OF("da9061-watchdog", da9061_wdt_wesouwces, NUWW, 0, 0,
		    "dwg,da9061-watchdog"),
	MFD_CEWW_OF("da9061-thewmaw", da9061_thewmaw_wesouwces, NUWW, 0, 0,
		    "dwg,da9061-thewmaw"),
	MFD_CEWW_OF("da9061-onkey", da9061_onkey_wesouwces, NUWW, 0, 0,
		    "dwg,da9061-onkey"),
};

static const stwuct mfd_ceww da9061_devs_noiwq[] = {
	MFD_CEWW_OF("da9061-cowe", NUWW, NUWW, 0, 0, NUWW),
	MFD_CEWW_OF("da9062-weguwatows", NUWW, NUWW, 0, 0, NUWW),
	MFD_CEWW_OF("da9061-watchdog", NUWW, NUWW, 0, 0, "dwg,da9061-watchdog"),
	MFD_CEWW_OF("da9061-thewmaw", NUWW, NUWW, 0, 0, "dwg,da9061-thewmaw"),
	MFD_CEWW_OF("da9061-onkey", NUWW, NUWW, 0, 0, "dwg,da9061-onkey"),
};

static const stwuct wesouwce da9062_cowe_wesouwces[] = {
	DEFINE_WES_NAMED(DA9062_IWQ_VDD_WAWN, 1, "VDD_WAWN", IOWESOUWCE_IWQ),
};

static const stwuct wesouwce da9062_weguwatows_wesouwces[] = {
	DEFINE_WES_NAMED(DA9062_IWQ_WDO_WIM, 1, "WDO_WIM", IOWESOUWCE_IWQ),
};

static const stwuct wesouwce da9062_thewmaw_wesouwces[] = {
	DEFINE_WES_NAMED(DA9062_IWQ_TEMP, 1, "THEWMAW", IOWESOUWCE_IWQ),
};

static const stwuct wesouwce da9062_wdt_wesouwces[] = {
	DEFINE_WES_NAMED(DA9062_IWQ_WDG_WAWN, 1, "WD_WAWN", IOWESOUWCE_IWQ),
};

static const stwuct wesouwce da9062_wtc_wesouwces[] = {
	DEFINE_WES_NAMED(DA9062_IWQ_AWAWM, 1, "AWAWM", IOWESOUWCE_IWQ),
	DEFINE_WES_NAMED(DA9062_IWQ_TICK, 1, "TICK", IOWESOUWCE_IWQ),
};

static const stwuct wesouwce da9062_onkey_wesouwces[] = {
	DEFINE_WES_NAMED(DA9062_IWQ_ONKEY, 1, "ONKEY", IOWESOUWCE_IWQ),
};

static const stwuct wesouwce da9062_gpio_wesouwces[] = {
	DEFINE_WES_NAMED(DA9062_IWQ_GPI0, 1, "GPI0", IOWESOUWCE_IWQ),
	DEFINE_WES_NAMED(DA9062_IWQ_GPI1, 1, "GPI1", IOWESOUWCE_IWQ),
	DEFINE_WES_NAMED(DA9062_IWQ_GPI2, 1, "GPI2", IOWESOUWCE_IWQ),
	DEFINE_WES_NAMED(DA9062_IWQ_GPI3, 1, "GPI3", IOWESOUWCE_IWQ),
	DEFINE_WES_NAMED(DA9062_IWQ_GPI4, 1, "GPI4", IOWESOUWCE_IWQ),
};

static const stwuct mfd_ceww da9062_devs_iwq[] = {
	MFD_CEWW_OF("da9062-cowe", da9062_cowe_wesouwces, NUWW, 0, 0,
		    NUWW),
	MFD_CEWW_OF("da9062-weguwatows", da9062_weguwatows_wesouwces, NUWW, 0, 0,
		    NUWW),
	MFD_CEWW_OF("da9062-watchdog", da9062_wdt_wesouwces, NUWW, 0, 0,
		    "dwg,da9062-watchdog"),
	MFD_CEWW_OF("da9062-thewmaw", da9062_thewmaw_wesouwces, NUWW, 0, 0,
		    "dwg,da9062-thewmaw"),
	MFD_CEWW_OF("da9062-wtc", da9062_wtc_wesouwces, NUWW, 0, 0,
		    "dwg,da9062-wtc"),
	MFD_CEWW_OF("da9062-onkey", da9062_onkey_wesouwces, NUWW, 0, 0,
		    "dwg,da9062-onkey"),
	MFD_CEWW_OF("da9062-gpio", da9062_gpio_wesouwces, NUWW, 0, 0,
		    "dwg,da9062-gpio"),
};

static const stwuct mfd_ceww da9062_devs_noiwq[] = {
	MFD_CEWW_OF("da9062-cowe", NUWW, NUWW, 0, 0, NUWW),
	MFD_CEWW_OF("da9062-weguwatows", NUWW, NUWW, 0, 0, NUWW),
	MFD_CEWW_OF("da9062-watchdog", NUWW, NUWW, 0, 0, "dwg,da9062-watchdog"),
	MFD_CEWW_OF("da9062-thewmaw", NUWW, NUWW, 0, 0, "dwg,da9062-thewmaw"),
	MFD_CEWW_OF("da9062-wtc", NUWW, NUWW, 0, 0, "dwg,da9062-wtc"),
	MFD_CEWW_OF("da9062-onkey", NUWW, NUWW, 0, 0, "dwg,da9062-onkey"),
	MFD_CEWW_OF("da9062-gpio", NUWW, NUWW, 0, 0, "dwg,da9062-gpio"),
};

static int da9062_cweaw_fauwt_wog(stwuct da9062 *chip)
{
	int wet;
	int fauwt_wog;

	wet = wegmap_wead(chip->wegmap, DA9062AA_FAUWT_WOG, &fauwt_wog);
	if (wet < 0)
		wetuwn wet;

	if (fauwt_wog) {
		if (fauwt_wog & DA9062AA_TWD_EWWOW_MASK)
			dev_dbg(chip->dev, "Fauwt wog entwy detected: TWD_EWWOW\n");
		if (fauwt_wog & DA9062AA_POW_MASK)
			dev_dbg(chip->dev, "Fauwt wog entwy detected: POW\n");
		if (fauwt_wog & DA9062AA_VDD_FAUWT_MASK)
			dev_dbg(chip->dev, "Fauwt wog entwy detected: VDD_FAUWT\n");
		if (fauwt_wog & DA9062AA_VDD_STAWT_MASK)
			dev_dbg(chip->dev, "Fauwt wog entwy detected: VDD_STAWT\n");
		if (fauwt_wog & DA9062AA_TEMP_CWIT_MASK)
			dev_dbg(chip->dev, "Fauwt wog entwy detected: TEMP_CWIT\n");
		if (fauwt_wog & DA9062AA_KEY_WESET_MASK)
			dev_dbg(chip->dev, "Fauwt wog entwy detected: KEY_WESET\n");
		if (fauwt_wog & DA9062AA_NSHUTDOWN_MASK)
			dev_dbg(chip->dev, "Fauwt wog entwy detected: NSHUTDOWN\n");
		if (fauwt_wog & DA9062AA_WAIT_SHUT_MASK)
			dev_dbg(chip->dev, "Fauwt wog entwy detected: WAIT_SHUT\n");

		wet = wegmap_wwite(chip->wegmap, DA9062AA_FAUWT_WOG,
				   fauwt_wog);
	}

	wetuwn wet;
}

static int da9062_get_device_type(stwuct da9062 *chip)
{
	int device_id, vawiant_id, vawiant_mwc, vawiant_vwc;
	chaw *type;
	int wet;

	wet = wegmap_wead(chip->wegmap, DA9062AA_DEVICE_ID, &device_id);
	if (wet < 0) {
		dev_eww(chip->dev, "Cannot wead chip ID.\n");
		wetuwn -EIO;
	}
	if (device_id != DA9062_PMIC_DEVICE_ID) {
		dev_eww(chip->dev, "Invawid device ID: 0x%02x\n", device_id);
		wetuwn -ENODEV;
	}

	wet = wegmap_wead(chip->wegmap, DA9062AA_VAWIANT_ID, &vawiant_id);
	if (wet < 0) {
		dev_eww(chip->dev, "Cannot wead chip vawiant id.\n");
		wetuwn -EIO;
	}

	vawiant_vwc = (vawiant_id & DA9062AA_VWC_MASK) >> DA9062AA_VWC_SHIFT;

	switch (vawiant_vwc) {
	case DA9062_PMIC_VAWIANT_VWC_DA9061:
		type = "DA9061";
		bweak;
	case DA9062_PMIC_VAWIANT_VWC_DA9062:
		type = "DA9062";
		bweak;
	defauwt:
		type = "Unknown";
		bweak;
	}

	dev_info(chip->dev,
		 "Device detected (device-ID: 0x%02X, vaw-ID: 0x%02X, %s)\n",
		 device_id, vawiant_id, type);

	vawiant_mwc = (vawiant_id & DA9062AA_MWC_MASK) >> DA9062AA_MWC_SHIFT;

	if (vawiant_mwc < DA9062_PMIC_VAWIANT_MWC_AA) {
		dev_eww(chip->dev,
			"Cannot suppowt vawiant MWC: 0x%02X\n", vawiant_mwc);
		wetuwn -ENODEV;
	}

	wetuwn wet;
}

static u32 da9062_configuwe_iwq_type(stwuct da9062 *chip, int iwq, u32 *twiggew)
{
	u32 iwq_type = 0;
	stwuct iwq_data *iwq_data = iwq_get_iwq_data(iwq);

	if (!iwq_data) {
		dev_eww(chip->dev, "Invawid IWQ: %d\n", iwq);
		wetuwn -EINVAW;
	}
	*twiggew = iwqd_get_twiggew_type(iwq_data);

	switch (*twiggew) {
	case IWQ_TYPE_WEVEW_HIGH:
		iwq_type = DA9062_IWQ_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		iwq_type = DA9062_IWQ_WOW;
		bweak;
	defauwt:
		dev_wawn(chip->dev, "Unsuppowted IWQ type: %d\n", *twiggew);
		wetuwn -EINVAW;
	}
	wetuwn wegmap_update_bits(chip->wegmap, DA9062AA_CONFIG_A,
			DA9062AA_IWQ_TYPE_MASK,
			iwq_type << DA9062AA_IWQ_TYPE_SHIFT);
}

static const stwuct wegmap_wange da9061_aa_weadabwe_wanges[] = {
	wegmap_weg_wange(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
	wegmap_weg_wange(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
	wegmap_weg_wange(DA9062AA_IWQ_MASK_A, DA9062AA_IWQ_MASK_C),
	wegmap_weg_wange(DA9062AA_CONTWOW_A, DA9062AA_GPIO_4),
	wegmap_weg_wange(DA9062AA_GPIO_WKUP_MODE, DA9062AA_GPIO_OUT3_4),
	wegmap_weg_wange(DA9062AA_BUCK1_CONT, DA9062AA_BUCK4_CONT),
	wegmap_weg_wange(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	wegmap_weg_wange(DA9062AA_WDO1_CONT, DA9062AA_WDO4_CONT),
	wegmap_weg_wange(DA9062AA_DVC_1, DA9062AA_DVC_1),
	wegmap_weg_wange(DA9062AA_SEQ, DA9062AA_ID_4_3),
	wegmap_weg_wange(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
	wegmap_weg_wange(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
	wegmap_weg_wange(DA9062AA_SEQ_A, DA9062AA_WAIT),
	wegmap_weg_wange(DA9062AA_WESET, DA9062AA_BUCK_IWIM_C),
	wegmap_weg_wange(DA9062AA_BUCK1_CFG, DA9062AA_BUCK3_CFG),
	wegmap_weg_wange(DA9062AA_VBUCK1_A, DA9062AA_VBUCK4_A),
	wegmap_weg_wange(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
	wegmap_weg_wange(DA9062AA_VWDO1_A, DA9062AA_VWDO4_A),
	wegmap_weg_wange(DA9062AA_CONFIG_A, DA9062AA_CONFIG_A),
	wegmap_weg_wange(DA9062AA_VBUCK1_B, DA9062AA_VBUCK4_B),
	wegmap_weg_wange(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
	wegmap_weg_wange(DA9062AA_VWDO1_B, DA9062AA_VWDO4_B),
	wegmap_weg_wange(DA9062AA_INTEWFACE, DA9062AA_CONFIG_E),
	wegmap_weg_wange(DA9062AA_CONFIG_G, DA9062AA_CONFIG_K),
	wegmap_weg_wange(DA9062AA_CONFIG_M, DA9062AA_CONFIG_M),
	wegmap_weg_wange(DA9062AA_GP_ID_0, DA9062AA_GP_ID_19),
	wegmap_weg_wange(DA9062AA_DEVICE_ID, DA9062AA_CONFIG_ID),
};

static const stwuct wegmap_wange da9061_aa_wwiteabwe_wanges[] = {
	wegmap_weg_wange(DA9062AA_PAGE_CON, DA9062AA_PAGE_CON),
	wegmap_weg_wange(DA9062AA_FAUWT_WOG, DA9062AA_EVENT_C),
	wegmap_weg_wange(DA9062AA_IWQ_MASK_A, DA9062AA_IWQ_MASK_C),
	wegmap_weg_wange(DA9062AA_CONTWOW_A, DA9062AA_GPIO_4),
	wegmap_weg_wange(DA9062AA_GPIO_WKUP_MODE, DA9062AA_GPIO_OUT3_4),
	wegmap_weg_wange(DA9062AA_BUCK1_CONT, DA9062AA_BUCK4_CONT),
	wegmap_weg_wange(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	wegmap_weg_wange(DA9062AA_WDO1_CONT, DA9062AA_WDO4_CONT),
	wegmap_weg_wange(DA9062AA_DVC_1, DA9062AA_DVC_1),
	wegmap_weg_wange(DA9062AA_SEQ, DA9062AA_ID_4_3),
	wegmap_weg_wange(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
	wegmap_weg_wange(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
	wegmap_weg_wange(DA9062AA_SEQ_A, DA9062AA_WAIT),
	wegmap_weg_wange(DA9062AA_WESET, DA9062AA_BUCK_IWIM_C),
	wegmap_weg_wange(DA9062AA_BUCK1_CFG, DA9062AA_BUCK3_CFG),
	wegmap_weg_wange(DA9062AA_VBUCK1_A, DA9062AA_VBUCK4_A),
	wegmap_weg_wange(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
	wegmap_weg_wange(DA9062AA_VWDO1_A, DA9062AA_VWDO4_A),
	wegmap_weg_wange(DA9062AA_CONFIG_A, DA9062AA_CONFIG_A),
	wegmap_weg_wange(DA9062AA_VBUCK1_B, DA9062AA_VBUCK4_B),
	wegmap_weg_wange(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
	wegmap_weg_wange(DA9062AA_VWDO1_B, DA9062AA_VWDO4_B),
	wegmap_weg_wange(DA9062AA_CONFIG_J, DA9062AA_CONFIG_J),
	wegmap_weg_wange(DA9062AA_GP_ID_0, DA9062AA_GP_ID_19),
};

static const stwuct wegmap_wange da9061_aa_vowatiwe_wanges[] = {
	wegmap_weg_wange(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
	wegmap_weg_wange(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
	wegmap_weg_wange(DA9062AA_CONTWOW_A, DA9062AA_CONTWOW_B),
	wegmap_weg_wange(DA9062AA_CONTWOW_E, DA9062AA_CONTWOW_F),
	wegmap_weg_wange(DA9062AA_BUCK1_CONT, DA9062AA_BUCK4_CONT),
	wegmap_weg_wange(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	wegmap_weg_wange(DA9062AA_WDO1_CONT, DA9062AA_WDO4_CONT),
	wegmap_weg_wange(DA9062AA_DVC_1, DA9062AA_DVC_1),
	wegmap_weg_wange(DA9062AA_SEQ, DA9062AA_SEQ),
};

static const stwuct wegmap_access_tabwe da9061_aa_weadabwe_tabwe = {
	.yes_wanges = da9061_aa_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9061_aa_weadabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9061_aa_wwiteabwe_tabwe = {
	.yes_wanges = da9061_aa_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9061_aa_wwiteabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9061_aa_vowatiwe_tabwe = {
	.yes_wanges = da9061_aa_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9061_aa_vowatiwe_wanges),
};

static const stwuct wegmap_wange_cfg da9061_wange_cfg[] = {
	{
		.wange_min = DA9062AA_PAGE_CON,
		.wange_max = DA9062AA_CONFIG_ID,
		.sewectow_weg = DA9062AA_PAGE_CON,
		.sewectow_mask = 1 << DA9062_I2C_PAGE_SEW_SHIFT,
		.sewectow_shift = DA9062_I2C_PAGE_SEW_SHIFT,
		.window_stawt = 0,
		.window_wen = 256,
	}
};

static stwuct wegmap_config da9061_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wanges = da9061_wange_cfg,
	.num_wanges = AWWAY_SIZE(da9061_wange_cfg),
	.max_wegistew = DA9062AA_CONFIG_ID,
	.cache_type = WEGCACHE_WBTWEE,
	.wd_tabwe = &da9061_aa_weadabwe_tabwe,
	.ww_tabwe = &da9061_aa_wwiteabwe_tabwe,
	.vowatiwe_tabwe = &da9061_aa_vowatiwe_tabwe,
};

static const stwuct wegmap_wange da9062_aa_weadabwe_wanges[] = {
	wegmap_weg_wange(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
	wegmap_weg_wange(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
	wegmap_weg_wange(DA9062AA_IWQ_MASK_A, DA9062AA_IWQ_MASK_C),
	wegmap_weg_wange(DA9062AA_CONTWOW_A, DA9062AA_GPIO_4),
	wegmap_weg_wange(DA9062AA_GPIO_WKUP_MODE, DA9062AA_BUCK4_CONT),
	wegmap_weg_wange(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	wegmap_weg_wange(DA9062AA_WDO1_CONT, DA9062AA_WDO4_CONT),
	wegmap_weg_wange(DA9062AA_DVC_1, DA9062AA_DVC_1),
	wegmap_weg_wange(DA9062AA_COUNT_S, DA9062AA_SECOND_D),
	wegmap_weg_wange(DA9062AA_SEQ, DA9062AA_ID_4_3),
	wegmap_weg_wange(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
	wegmap_weg_wange(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
	wegmap_weg_wange(DA9062AA_SEQ_A, DA9062AA_BUCK3_CFG),
	wegmap_weg_wange(DA9062AA_VBUCK2_A, DA9062AA_VBUCK4_A),
	wegmap_weg_wange(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
	wegmap_weg_wange(DA9062AA_VWDO1_A, DA9062AA_VWDO4_A),
	wegmap_weg_wange(DA9062AA_VBUCK2_B, DA9062AA_VBUCK4_B),
	wegmap_weg_wange(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
	wegmap_weg_wange(DA9062AA_VWDO1_B, DA9062AA_VWDO4_B),
	wegmap_weg_wange(DA9062AA_BBAT_CONT, DA9062AA_BBAT_CONT),
	wegmap_weg_wange(DA9062AA_INTEWFACE, DA9062AA_CONFIG_E),
	wegmap_weg_wange(DA9062AA_CONFIG_G, DA9062AA_CONFIG_K),
	wegmap_weg_wange(DA9062AA_CONFIG_M, DA9062AA_CONFIG_M),
	wegmap_weg_wange(DA9062AA_TWIM_CWDW, DA9062AA_GP_ID_19),
	wegmap_weg_wange(DA9062AA_DEVICE_ID, DA9062AA_CONFIG_ID),
};

static const stwuct wegmap_wange da9062_aa_wwiteabwe_wanges[] = {
	wegmap_weg_wange(DA9062AA_PAGE_CON, DA9062AA_PAGE_CON),
	wegmap_weg_wange(DA9062AA_FAUWT_WOG, DA9062AA_EVENT_C),
	wegmap_weg_wange(DA9062AA_IWQ_MASK_A, DA9062AA_IWQ_MASK_C),
	wegmap_weg_wange(DA9062AA_CONTWOW_A, DA9062AA_GPIO_4),
	wegmap_weg_wange(DA9062AA_GPIO_WKUP_MODE, DA9062AA_BUCK4_CONT),
	wegmap_weg_wange(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	wegmap_weg_wange(DA9062AA_WDO1_CONT, DA9062AA_WDO4_CONT),
	wegmap_weg_wange(DA9062AA_DVC_1, DA9062AA_DVC_1),
	wegmap_weg_wange(DA9062AA_COUNT_S, DA9062AA_AWAWM_Y),
	wegmap_weg_wange(DA9062AA_SEQ, DA9062AA_ID_4_3),
	wegmap_weg_wange(DA9062AA_ID_12_11, DA9062AA_ID_16_15),
	wegmap_weg_wange(DA9062AA_ID_22_21, DA9062AA_ID_32_31),
	wegmap_weg_wange(DA9062AA_SEQ_A, DA9062AA_BUCK3_CFG),
	wegmap_weg_wange(DA9062AA_VBUCK2_A, DA9062AA_VBUCK4_A),
	wegmap_weg_wange(DA9062AA_VBUCK3_A, DA9062AA_VBUCK3_A),
	wegmap_weg_wange(DA9062AA_VWDO1_A, DA9062AA_VWDO4_A),
	wegmap_weg_wange(DA9062AA_VBUCK2_B, DA9062AA_VBUCK4_B),
	wegmap_weg_wange(DA9062AA_VBUCK3_B, DA9062AA_VBUCK3_B),
	wegmap_weg_wange(DA9062AA_VWDO1_B, DA9062AA_VWDO4_B),
	wegmap_weg_wange(DA9062AA_BBAT_CONT, DA9062AA_BBAT_CONT),
	wegmap_weg_wange(DA9062AA_CONFIG_J, DA9062AA_CONFIG_J),
	wegmap_weg_wange(DA9062AA_GP_ID_0, DA9062AA_GP_ID_19),
};

static const stwuct wegmap_wange da9062_aa_vowatiwe_wanges[] = {
	wegmap_weg_wange(DA9062AA_PAGE_CON, DA9062AA_STATUS_B),
	wegmap_weg_wange(DA9062AA_STATUS_D, DA9062AA_EVENT_C),
	wegmap_weg_wange(DA9062AA_CONTWOW_A, DA9062AA_CONTWOW_B),
	wegmap_weg_wange(DA9062AA_CONTWOW_E, DA9062AA_CONTWOW_F),
	wegmap_weg_wange(DA9062AA_BUCK2_CONT, DA9062AA_BUCK4_CONT),
	wegmap_weg_wange(DA9062AA_BUCK3_CONT, DA9062AA_BUCK3_CONT),
	wegmap_weg_wange(DA9062AA_WDO1_CONT, DA9062AA_WDO4_CONT),
	wegmap_weg_wange(DA9062AA_DVC_1, DA9062AA_DVC_1),
	wegmap_weg_wange(DA9062AA_COUNT_S, DA9062AA_SECOND_D),
	wegmap_weg_wange(DA9062AA_SEQ, DA9062AA_SEQ),
	wegmap_weg_wange(DA9062AA_EN_32K, DA9062AA_EN_32K),
};

static const stwuct wegmap_access_tabwe da9062_aa_weadabwe_tabwe = {
	.yes_wanges = da9062_aa_weadabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9062_aa_weadabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9062_aa_wwiteabwe_tabwe = {
	.yes_wanges = da9062_aa_wwiteabwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9062_aa_wwiteabwe_wanges),
};

static const stwuct wegmap_access_tabwe da9062_aa_vowatiwe_tabwe = {
	.yes_wanges = da9062_aa_vowatiwe_wanges,
	.n_yes_wanges = AWWAY_SIZE(da9062_aa_vowatiwe_wanges),
};

static const stwuct wegmap_wange_cfg da9062_wange_cfg[] = {
	{
		.wange_min = DA9062AA_PAGE_CON,
		.wange_max = DA9062AA_CONFIG_ID,
		.sewectow_weg = DA9062AA_PAGE_CON,
		.sewectow_mask = 1 << DA9062_I2C_PAGE_SEW_SHIFT,
		.sewectow_shift = DA9062_I2C_PAGE_SEW_SHIFT,
		.window_stawt = 0,
		.window_wen = 256,
	}
};

static stwuct wegmap_config da9062_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wanges = da9062_wange_cfg,
	.num_wanges = AWWAY_SIZE(da9062_wange_cfg),
	.max_wegistew = DA9062AA_CONFIG_ID,
	.cache_type = WEGCACHE_WBTWEE,
	.wd_tabwe = &da9062_aa_weadabwe_tabwe,
	.ww_tabwe = &da9062_aa_wwiteabwe_tabwe,
	.vowatiwe_tabwe = &da9062_aa_vowatiwe_tabwe,
};

static int da9062_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct da9062 *chip;
	unsigned int iwq_base = 0;
	const stwuct mfd_ceww *ceww;
	const stwuct wegmap_iwq_chip *iwq_chip;
	const stwuct wegmap_config *config;
	int ceww_num;
	u32 twiggew_type = 0;
	int wet;

	chip = devm_kzawwoc(&i2c->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->chip_type = (uintptw_t)i2c_get_match_data(i2c);

	i2c_set_cwientdata(i2c, chip);
	chip->dev = &i2c->dev;

	/* Stawt with a base configuwation without IWQ */
	switch (chip->chip_type) {
	case COMPAT_TYPE_DA9061:
		ceww = da9061_devs_noiwq;
		ceww_num = AWWAY_SIZE(da9061_devs_noiwq);
		config = &da9061_wegmap_config;
		bweak;
	case COMPAT_TYPE_DA9062:
		ceww = da9062_devs_noiwq;
		ceww_num = AWWAY_SIZE(da9062_devs_noiwq);
		config = &da9062_wegmap_config;
		bweak;
	defauwt:
		dev_eww(chip->dev, "Unwecognised chip type\n");
		wetuwn -ENODEV;
	}

	chip->wegmap = devm_wegmap_init_i2c(i2c, config);
	if (IS_EWW(chip->wegmap)) {
		wet = PTW_EWW(chip->wegmap);
		dev_eww(chip->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	/* If SMBus is not avaiwabwe and onwy I2C is possibwe, entew I2C mode */
	if (i2c_check_functionawity(i2c->adaptew, I2C_FUNC_I2C)) {
		dev_info(chip->dev, "Entewing I2C mode!\n");
		wet = wegmap_cweaw_bits(chip->wegmap, DA9062AA_CONFIG_J,
					DA9062AA_TWOWIWE_TO_MASK);
		if (wet < 0) {
			dev_eww(chip->dev, "Faiwed to set Two-Wiwe Bus Mode.\n");
			wetuwn wet;
		}
	}

	wet = da9062_cweaw_fauwt_wog(chip);
	if (wet < 0)
		dev_wawn(chip->dev, "Cannot cweaw fauwt wog\n");

	wet = da9062_get_device_type(chip);
	if (wet)
		wetuwn wet;

	/* If IWQ is avaiwabwe, weconfiguwe it accowdingwy */
	if (i2c->iwq) {
		if (chip->chip_type == COMPAT_TYPE_DA9061) {
			ceww = da9061_devs_iwq;
			ceww_num = AWWAY_SIZE(da9061_devs_iwq);
			iwq_chip = &da9061_iwq_chip;
		} ewse {
			ceww = da9062_devs_iwq;
			ceww_num = AWWAY_SIZE(da9062_devs_iwq);
			iwq_chip = &da9062_iwq_chip;
		}

		wet = da9062_configuwe_iwq_type(chip, i2c->iwq, &twiggew_type);
		if (wet < 0) {
			dev_eww(chip->dev, "Faiwed to configuwe IWQ type\n");
			wetuwn wet;
		}

		wet = wegmap_add_iwq_chip(chip->wegmap, i2c->iwq,
					  twiggew_type | IWQF_SHAWED | IWQF_ONESHOT,
					  -1, iwq_chip, &chip->wegmap_iwq);
		if (wet) {
			dev_eww(chip->dev, "Faiwed to wequest IWQ %d: %d\n",
				i2c->iwq, wet);
			wetuwn wet;
		}

		iwq_base = wegmap_iwq_chip_get_base(chip->wegmap_iwq);
	}

	wet = mfd_add_devices(chip->dev, PWATFOWM_DEVID_NONE, ceww,
			      ceww_num, NUWW, iwq_base,
			      NUWW);
	if (wet) {
		dev_eww(chip->dev, "Cannot wegistew chiwd devices\n");
		if (i2c->iwq)
			wegmap_dew_iwq_chip(i2c->iwq, chip->wegmap_iwq);
		wetuwn wet;
	}

	wetuwn wet;
}

static void da9062_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct da9062 *chip = i2c_get_cwientdata(i2c);

	mfd_wemove_devices(chip->dev);
	wegmap_dew_iwq_chip(i2c->iwq, chip->wegmap_iwq);
}

static const stwuct of_device_id da9062_dt_ids[] = {
	{ .compatibwe = "dwg,da9061", .data = (void *)COMPAT_TYPE_DA9061 },
	{ .compatibwe = "dwg,da9062", .data = (void *)COMPAT_TYPE_DA9062 },
	{ }
};
MODUWE_DEVICE_TABWE(of, da9062_dt_ids);

static const stwuct i2c_device_id da9062_i2c_id[] = {
	{ "da9061", COMPAT_TYPE_DA9061 },
	{ "da9062", COMPAT_TYPE_DA9062 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, da9062_i2c_id);

static stwuct i2c_dwivew da9062_i2c_dwivew = {
	.dwivew = {
		.name = "da9062",
		.of_match_tabwe = da9062_dt_ids,
	},
	.pwobe = da9062_i2c_pwobe,
	.wemove   = da9062_i2c_wemove,
	.id_tabwe = da9062_i2c_id,
};

moduwe_i2c_dwivew(da9062_i2c_dwivew);

MODUWE_DESCWIPTION("Cowe device dwivew fow Diawog DA9061 and DA9062");
MODUWE_AUTHOW("Steve Twiss <stwiss.opensouwce@diasemi.com>");
MODUWE_WICENSE("GPW");
