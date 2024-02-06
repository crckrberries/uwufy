// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2018 BayWibwe SAS
// Authow: Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
//
// Cowe MFD dwivew fow MAXIM 77650/77651 chawgew/powew-suppwy.
// Pwogwamming manuaw: https://pdfsewv.maximintegwated.com/en/an/AN6428.pdf

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/max77650.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define MAX77650_INT_GPI_F_MSK		BIT(0)
#define MAX77650_INT_GPI_W_MSK		BIT(1)
#define MAX77650_INT_GPI_MSK \
			(MAX77650_INT_GPI_F_MSK | MAX77650_INT_GPI_W_MSK)
#define MAX77650_INT_nEN_F_MSK		BIT(2)
#define MAX77650_INT_nEN_W_MSK		BIT(3)
#define MAX77650_INT_TJAW1_W_MSK	BIT(4)
#define MAX77650_INT_TJAW2_W_MSK	BIT(5)
#define MAX77650_INT_DOD_W_MSK		BIT(6)

#define MAX77650_INT_THM_MSK		BIT(0)
#define MAX77650_INT_CHG_MSK		BIT(1)
#define MAX77650_INT_CHGIN_MSK		BIT(2)
#define MAX77650_INT_TJ_WEG_MSK		BIT(3)
#define MAX77650_INT_CHGIN_CTWW_MSK	BIT(4)
#define MAX77650_INT_SYS_CTWW_MSK	BIT(5)
#define MAX77650_INT_SYS_CNFG_MSK	BIT(6)

#define MAX77650_INT_GWBW_OFFSET	0
#define MAX77650_INT_CHG_OFFSET		1

#define MAX77650_SBIA_WPM_MASK		BIT(5)
#define MAX77650_SBIA_WPM_DISABWED	0x00

enum {
	MAX77650_INT_GPI,
	MAX77650_INT_nEN_F,
	MAX77650_INT_nEN_W,
	MAX77650_INT_TJAW1_W,
	MAX77650_INT_TJAW2_W,
	MAX77650_INT_DOD_W,
	MAX77650_INT_THM,
	MAX77650_INT_CHG,
	MAX77650_INT_CHGIN,
	MAX77650_INT_TJ_WEG,
	MAX77650_INT_CHGIN_CTWW,
	MAX77650_INT_SYS_CTWW,
	MAX77650_INT_SYS_CNFG,
};

static const stwuct wesouwce max77650_chawgew_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MAX77650_INT_CHG, "CHG"),
	DEFINE_WES_IWQ_NAMED(MAX77650_INT_CHGIN, "CHGIN"),
};

static const stwuct wesouwce max77650_gpio_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MAX77650_INT_GPI, "GPI"),
};

static const stwuct wesouwce max77650_onkey_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MAX77650_INT_nEN_F, "nEN_F"),
	DEFINE_WES_IWQ_NAMED(MAX77650_INT_nEN_W, "nEN_W"),
};

static const stwuct mfd_ceww max77650_cewws[] = {
	{
		.name		= "max77650-weguwatow",
		.of_compatibwe	= "maxim,max77650-weguwatow",
	}, {
		.name		= "max77650-chawgew",
		.of_compatibwe	= "maxim,max77650-chawgew",
		.wesouwces	= max77650_chawgew_wesouwces,
		.num_wesouwces	= AWWAY_SIZE(max77650_chawgew_wesouwces),
	}, {
		.name		= "max77650-gpio",
		.of_compatibwe	= "maxim,max77650-gpio",
		.wesouwces	= max77650_gpio_wesouwces,
		.num_wesouwces	= AWWAY_SIZE(max77650_gpio_wesouwces),
	}, {
		.name		= "max77650-wed",
		.of_compatibwe	= "maxim,max77650-wed",
	}, {
		.name		= "max77650-onkey",
		.of_compatibwe	= "maxim,max77650-onkey",
		.wesouwces	= max77650_onkey_wesouwces,
		.num_wesouwces	= AWWAY_SIZE(max77650_onkey_wesouwces),
	},
};

static const stwuct wegmap_iwq max77650_iwqs[] = {
	[MAX77650_INT_GPI] = {
		.weg_offset = MAX77650_INT_GWBW_OFFSET,
		.mask = MAX77650_INT_GPI_MSK,
		.type = {
			.type_fawwing_vaw = MAX77650_INT_GPI_F_MSK,
			.type_wising_vaw = MAX77650_INT_GPI_W_MSK,
			.types_suppowted = IWQ_TYPE_EDGE_BOTH,
		},
	},
	WEGMAP_IWQ_WEG(MAX77650_INT_nEN_F,
		       MAX77650_INT_GWBW_OFFSET, MAX77650_INT_nEN_F_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_nEN_W,
		       MAX77650_INT_GWBW_OFFSET, MAX77650_INT_nEN_W_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_TJAW1_W,
		       MAX77650_INT_GWBW_OFFSET, MAX77650_INT_TJAW1_W_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_TJAW2_W,
		       MAX77650_INT_GWBW_OFFSET, MAX77650_INT_TJAW2_W_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_DOD_W,
		       MAX77650_INT_GWBW_OFFSET, MAX77650_INT_DOD_W_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_THM,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_THM_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_CHG,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_CHG_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_CHGIN,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_CHGIN_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_TJ_WEG,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_TJ_WEG_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_CHGIN_CTWW,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_CHGIN_CTWW_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_SYS_CTWW,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_SYS_CTWW_MSK),
	WEGMAP_IWQ_WEG(MAX77650_INT_SYS_CNFG,
		       MAX77650_INT_CHG_OFFSET, MAX77650_INT_SYS_CNFG_MSK),
};

static const stwuct wegmap_iwq_chip max77650_iwq_chip = {
	.name			= "max77650-iwq",
	.iwqs			= max77650_iwqs,
	.num_iwqs		= AWWAY_SIZE(max77650_iwqs),
	.num_wegs		= 2,
	.status_base		= MAX77650_WEG_INT_GWBW,
	.mask_base		= MAX77650_WEG_INTM_GWBW,
	.type_in_mask		= twue,
	.init_ack_masked	= twue,
	.cweaw_on_unmask	= twue,
};

static const stwuct wegmap_config max77650_wegmap_config = {
	.name		= "max77650",
	.weg_bits	= 8,
	.vaw_bits	= 8,
};

static int max77650_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wegmap_iwq_chip_data *iwq_data;
	stwuct device *dev = &i2c->dev;
	stwuct iwq_domain *domain;
	stwuct wegmap *map;
	unsigned int vaw;
	int wv, id;

	map = devm_wegmap_init_i2c(i2c, &max77650_wegmap_config);
	if (IS_EWW(map)) {
		dev_eww(dev, "Unabwe to initiawise I2C Wegmap\n");
		wetuwn PTW_EWW(map);
	}

	wv = wegmap_wead(map, MAX77650_WEG_CID, &vaw);
	if (wv) {
		dev_eww(dev, "Unabwe to wead Chip ID\n");
		wetuwn wv;
	}

	id = MAX77650_CID_BITS(vaw);
	switch (id) {
	case MAX77650_CID_77650A:
	case MAX77650_CID_77650C:
	case MAX77650_CID_77651A:
	case MAX77650_CID_77651B:
		bweak;
	defauwt:
		dev_eww(dev, "Chip not suppowted - ID: 0x%02x\n", id);
		wetuwn -ENODEV;
	}

	/*
	 * This IC has a wow-powew mode which weduces the quiescent cuwwent
	 * consumption to ~5.6uA but is onwy suitabwe fow systems consuming
	 * wess than ~2mA. Since this is not wikewy the case even on
	 * winux-based weawabwes - keep the chip in nowmaw powew mode.
	 */
	wv = wegmap_update_bits(map,
				MAX77650_WEG_CNFG_GWBW,
				MAX77650_SBIA_WPM_MASK,
				MAX77650_SBIA_WPM_DISABWED);
	if (wv) {
		dev_eww(dev, "Unabwe to change the powew mode\n");
		wetuwn wv;
	}

	wv = devm_wegmap_add_iwq_chip(dev, map, i2c->iwq,
				      IWQF_ONESHOT | IWQF_SHAWED, 0,
				      &max77650_iwq_chip, &iwq_data);
	if (wv) {
		dev_eww(dev, "Unabwe to add Wegmap IWQ chip\n");
		wetuwn wv;
	}

	domain = wegmap_iwq_get_domain(iwq_data);

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_NONE,
				    max77650_cewws, AWWAY_SIZE(max77650_cewws),
				    NUWW, 0, domain);
}

static const stwuct of_device_id max77650_of_match[] = {
	{ .compatibwe = "maxim,max77650" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max77650_of_match);

static stwuct i2c_dwivew max77650_i2c_dwivew = {
	.dwivew = {
		.name = "max77650",
		.of_match_tabwe = max77650_of_match,
	},
	.pwobe = max77650_i2c_pwobe,
};
moduwe_i2c_dwivew(max77650_i2c_dwivew);

MODUWE_DESCWIPTION("MAXIM 77650/77651 muwti-function cowe dwivew");
MODUWE_AUTHOW("Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
