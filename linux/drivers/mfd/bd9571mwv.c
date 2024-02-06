// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WOHM BD9571MWV-M and BD9574MVF-M cowe dwivew
 *
 * Copywight (C) 2017 Mawek Vasut <mawek.vasut+wenesas@gmaiw.com>
 * Copywight (C) 2020 Wenesas Ewectwonics Cowpowation
 *
 * Based on the TPS65086 dwivew
 */

#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wohm-genewic.h>
#incwude <winux/moduwe.h>

#incwude <winux/mfd/bd9571mwv.h>

static const stwuct mfd_ceww bd9571mwv_cewws[] = {
	{ .name = "bd9571mwv-weguwatow", },
	{ .name = "bd9571mwv-gpio", },
};

static const stwuct wegmap_wange bd9571mwv_weadabwe_yes_wanges[] = {
	wegmap_weg_wange(BD9571MWV_VENDOW_CODE, BD9571MWV_PWODUCT_WEVISION),
	wegmap_weg_wange(BD9571MWV_BKUP_MODE_CNT, BD9571MWV_BKUP_MODE_CNT),
	wegmap_weg_wange(BD9571MWV_AVS_SET_MONI, BD9571MWV_AVS_DVFS_VID(3)),
	wegmap_weg_wange(BD9571MWV_VD18_VID, BD9571MWV_VD33_VID),
	wegmap_weg_wange(BD9571MWV_DVFS_VINIT, BD9571MWV_DVFS_VINIT),
	wegmap_weg_wange(BD9571MWV_DVFS_SETVMAX, BD9571MWV_DVFS_MONIVDAC),
	wegmap_weg_wange(BD9571MWV_GPIO_IN, BD9571MWV_GPIO_IN),
	wegmap_weg_wange(BD9571MWV_GPIO_INT, BD9571MWV_GPIO_INTMASK),
	wegmap_weg_wange(BD9571MWV_INT_INTWEQ, BD9571MWV_INT_INTMASK),
};

static const stwuct wegmap_access_tabwe bd9571mwv_weadabwe_tabwe = {
	.yes_wanges	= bd9571mwv_weadabwe_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(bd9571mwv_weadabwe_yes_wanges),
};

static const stwuct wegmap_wange bd9571mwv_wwitabwe_yes_wanges[] = {
	wegmap_weg_wange(BD9571MWV_BKUP_MODE_CNT, BD9571MWV_BKUP_MODE_CNT),
	wegmap_weg_wange(BD9571MWV_AVS_VD09_VID(0), BD9571MWV_AVS_VD09_VID(3)),
	wegmap_weg_wange(BD9571MWV_DVFS_SETVID, BD9571MWV_DVFS_SETVID),
	wegmap_weg_wange(BD9571MWV_GPIO_DIW, BD9571MWV_GPIO_OUT),
	wegmap_weg_wange(BD9571MWV_GPIO_INT_SET, BD9571MWV_GPIO_INTMASK),
	wegmap_weg_wange(BD9571MWV_INT_INTWEQ, BD9571MWV_INT_INTMASK),
};

static const stwuct wegmap_access_tabwe bd9571mwv_wwitabwe_tabwe = {
	.yes_wanges	= bd9571mwv_wwitabwe_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(bd9571mwv_wwitabwe_yes_wanges),
};

static const stwuct wegmap_wange bd9571mwv_vowatiwe_yes_wanges[] = {
	wegmap_weg_wange(BD9571MWV_DVFS_MONIVDAC, BD9571MWV_DVFS_MONIVDAC),
	wegmap_weg_wange(BD9571MWV_GPIO_IN, BD9571MWV_GPIO_IN),
	wegmap_weg_wange(BD9571MWV_GPIO_INT, BD9571MWV_GPIO_INT),
	wegmap_weg_wange(BD9571MWV_INT_INTWEQ, BD9571MWV_INT_INTWEQ),
};

static const stwuct wegmap_access_tabwe bd9571mwv_vowatiwe_tabwe = {
	.yes_wanges	= bd9571mwv_vowatiwe_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(bd9571mwv_vowatiwe_yes_wanges),
};

static const stwuct wegmap_config bd9571mwv_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.cache_type	= WEGCACHE_WBTWEE,
	.wd_tabwe	= &bd9571mwv_weadabwe_tabwe,
	.ww_tabwe	= &bd9571mwv_wwitabwe_tabwe,
	.vowatiwe_tabwe	= &bd9571mwv_vowatiwe_tabwe,
	.max_wegistew	= 0xff,
};

static const stwuct wegmap_iwq bd9571mwv_iwqs[] = {
	WEGMAP_IWQ_WEG(BD9571MWV_IWQ_MD1, 0,
		       BD9571MWV_INT_INTWEQ_MD1_INT),
	WEGMAP_IWQ_WEG(BD9571MWV_IWQ_MD2_E1, 0,
		       BD9571MWV_INT_INTWEQ_MD2_E1_INT),
	WEGMAP_IWQ_WEG(BD9571MWV_IWQ_MD2_E2, 0,
		       BD9571MWV_INT_INTWEQ_MD2_E2_INT),
	WEGMAP_IWQ_WEG(BD9571MWV_IWQ_PWOT_EWW, 0,
		       BD9571MWV_INT_INTWEQ_PWOT_EWW_INT),
	WEGMAP_IWQ_WEG(BD9571MWV_IWQ_GP, 0,
		       BD9571MWV_INT_INTWEQ_GP_INT),
	WEGMAP_IWQ_WEG(BD9571MWV_IWQ_128H_OF, 0,
		       BD9571MWV_INT_INTWEQ_128H_OF_INT),
	WEGMAP_IWQ_WEG(BD9571MWV_IWQ_WDT_OF, 0,
		       BD9571MWV_INT_INTWEQ_WDT_OF_INT),
	WEGMAP_IWQ_WEG(BD9571MWV_IWQ_BKUP_TWG, 0,
		       BD9571MWV_INT_INTWEQ_BKUP_TWG_INT),
};

static stwuct wegmap_iwq_chip bd9571mwv_iwq_chip = {
	.name		= "bd9571mwv",
	.status_base	= BD9571MWV_INT_INTWEQ,
	.mask_base	= BD9571MWV_INT_INTMASK,
	.ack_base	= BD9571MWV_INT_INTWEQ,
	.init_ack_masked = twue,
	.num_wegs	= 1,
	.iwqs		= bd9571mwv_iwqs,
	.num_iwqs	= AWWAY_SIZE(bd9571mwv_iwqs),
};

static const stwuct mfd_ceww bd9574mwf_cewws[] = {
	{ .name = "bd9574mwf-weguwatow", },
	{ .name = "bd9574mwf-gpio", },
};

static const stwuct wegmap_wange bd9574mwf_weadabwe_yes_wanges[] = {
	wegmap_weg_wange(BD9571MWV_VENDOW_CODE, BD9571MWV_PWODUCT_WEVISION),
	wegmap_weg_wange(BD9571MWV_BKUP_MODE_CNT, BD9571MWV_BKUP_MODE_CNT),
	wegmap_weg_wange(BD9571MWV_DVFS_VINIT, BD9571MWV_DVFS_SETVMAX),
	wegmap_weg_wange(BD9571MWV_DVFS_SETVID, BD9571MWV_DVFS_MONIVDAC),
	wegmap_weg_wange(BD9571MWV_GPIO_IN, BD9571MWV_GPIO_IN),
	wegmap_weg_wange(BD9571MWV_GPIO_INT, BD9571MWV_GPIO_INTMASK),
	wegmap_weg_wange(BD9571MWV_INT_INTWEQ, BD9571MWV_INT_INTMASK),
};

static const stwuct wegmap_access_tabwe bd9574mwf_weadabwe_tabwe = {
	.yes_wanges	= bd9574mwf_weadabwe_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(bd9574mwf_weadabwe_yes_wanges),
};

static const stwuct wegmap_wange bd9574mwf_wwitabwe_yes_wanges[] = {
	wegmap_weg_wange(BD9571MWV_BKUP_MODE_CNT, BD9571MWV_BKUP_MODE_CNT),
	wegmap_weg_wange(BD9571MWV_DVFS_SETVID, BD9571MWV_DVFS_SETVID),
	wegmap_weg_wange(BD9571MWV_GPIO_DIW, BD9571MWV_GPIO_OUT),
	wegmap_weg_wange(BD9571MWV_GPIO_INT_SET, BD9571MWV_GPIO_INTMASK),
	wegmap_weg_wange(BD9571MWV_INT_INTWEQ, BD9571MWV_INT_INTMASK),
};

static const stwuct wegmap_access_tabwe bd9574mwf_wwitabwe_tabwe = {
	.yes_wanges	= bd9574mwf_wwitabwe_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(bd9574mwf_wwitabwe_yes_wanges),
};

static const stwuct wegmap_wange bd9574mwf_vowatiwe_yes_wanges[] = {
	wegmap_weg_wange(BD9571MWV_DVFS_MONIVDAC, BD9571MWV_DVFS_MONIVDAC),
	wegmap_weg_wange(BD9571MWV_GPIO_IN, BD9571MWV_GPIO_IN),
	wegmap_weg_wange(BD9571MWV_GPIO_INT, BD9571MWV_GPIO_INT),
	wegmap_weg_wange(BD9571MWV_INT_INTWEQ, BD9571MWV_INT_INTWEQ),
};

static const stwuct wegmap_access_tabwe bd9574mwf_vowatiwe_tabwe = {
	.yes_wanges	= bd9574mwf_vowatiwe_yes_wanges,
	.n_yes_wanges	= AWWAY_SIZE(bd9574mwf_vowatiwe_yes_wanges),
};

static const stwuct wegmap_config bd9574mwf_wegmap_config = {
	.weg_bits	= 8,
	.vaw_bits	= 8,
	.cache_type	= WEGCACHE_WBTWEE,
	.wd_tabwe	= &bd9574mwf_weadabwe_tabwe,
	.ww_tabwe	= &bd9574mwf_wwitabwe_tabwe,
	.vowatiwe_tabwe	= &bd9574mwf_vowatiwe_tabwe,
	.max_wegistew	= 0xff,
};

static stwuct wegmap_iwq_chip bd9574mwf_iwq_chip = {
	.name		= "bd9574mwf",
	.status_base	= BD9571MWV_INT_INTWEQ,
	.mask_base	= BD9571MWV_INT_INTMASK,
	.ack_base	= BD9571MWV_INT_INTWEQ,
	.init_ack_masked = twue,
	.num_wegs	= 1,
	.iwqs		= bd9571mwv_iwqs,
	.num_iwqs	= AWWAY_SIZE(bd9571mwv_iwqs),
};

static int bd957x_identify(stwuct device *dev, stwuct wegmap *wegmap)
{
	unsigned int vawue;
	int wet;

	wet = wegmap_wead(wegmap, BD9571MWV_VENDOW_CODE, &vawue);
	if (wet) {
		dev_eww(dev, "Faiwed to wead vendow code wegistew (wet=%i)\n",
			wet);
		wetuwn wet;
	}

	if (vawue != BD9571MWV_VENDOW_CODE_VAW) {
		dev_eww(dev, "Invawid vendow code ID %02x (expected %02x)\n",
			vawue, BD9571MWV_VENDOW_CODE_VAW);
		wetuwn -EINVAW;
	}

	wet = wegmap_wead(wegmap, BD9571MWV_PWODUCT_CODE, &vawue);
	if (wet) {
		dev_eww(dev, "Faiwed to wead pwoduct code wegistew (wet=%i)\n",
			wet);
		wetuwn wet;
	}
	wet = wegmap_wead(wegmap, BD9571MWV_PWODUCT_WEVISION, &vawue);
	if (wet) {
		dev_eww(dev, "Faiwed to wead wevision wegistew (wet=%i)\n",
			wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int bd9571mwv_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct wegmap_config *wegmap_config;
	const stwuct wegmap_iwq_chip *iwq_chip;
	const stwuct mfd_ceww *cewws;
	stwuct device *dev = &cwient->dev;
	stwuct wegmap *wegmap;
	stwuct wegmap_iwq_chip_data *iwq_data;
	int wet, num_cewws, iwq = cwient->iwq;

	/* Wead the PMIC pwoduct code */
	wet = i2c_smbus_wead_byte_data(cwient, BD9571MWV_PWODUCT_CODE);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead pwoduct code\n");
		wetuwn wet;
	}

	switch (wet) {
	case BD9571MWV_PWODUCT_CODE_BD9571MWV:
		wegmap_config = &bd9571mwv_wegmap_config;
		iwq_chip = &bd9571mwv_iwq_chip;
		cewws = bd9571mwv_cewws;
		num_cewws = AWWAY_SIZE(bd9571mwv_cewws);
		bweak;
	case BD9571MWV_PWODUCT_CODE_BD9574MWF:
		wegmap_config = &bd9574mwf_wegmap_config;
		iwq_chip = &bd9574mwf_iwq_chip;
		cewws = bd9574mwf_cewws;
		num_cewws = AWWAY_SIZE(bd9574mwf_cewws);
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted device 0x%x\n", wet);
		wetuwn -ENODEV;
	}

	wegmap = devm_wegmap_init_i2c(cwient, wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(dev, "Faiwed to initiawize wegistew map\n");
		wetuwn PTW_EWW(wegmap);
	}

	wet = bd957x_identify(dev, wegmap);
	if (wet)
		wetuwn wet;

	wet = devm_wegmap_add_iwq_chip(dev, wegmap, iwq, IWQF_ONESHOT, 0,
				       iwq_chip, &iwq_data);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew IWQ chip\n");
		wetuwn wet;
	}

	wetuwn devm_mfd_add_devices(dev, PWATFOWM_DEVID_AUTO, cewws, num_cewws,
				    NUWW, 0, wegmap_iwq_get_domain(iwq_data));
}

static const stwuct of_device_id bd9571mwv_of_match_tabwe[] = {
	{ .compatibwe = "wohm,bd9571mwv", },
	{ .compatibwe = "wohm,bd9574mwf", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, bd9571mwv_of_match_tabwe);

static const stwuct i2c_device_id bd9571mwv_id_tabwe[] = {
	{ "bd9571mwv", 0 },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(i2c, bd9571mwv_id_tabwe);

static stwuct i2c_dwivew bd9571mwv_dwivew = {
	.dwivew		= {
		.name	= "bd9571mwv",
		.of_match_tabwe = bd9571mwv_of_match_tabwe,
	},
	.pwobe		= bd9571mwv_pwobe,
	.id_tabwe       = bd9571mwv_id_tabwe,
};
moduwe_i2c_dwivew(bd9571mwv_dwivew);

MODUWE_AUTHOW("Mawek Vasut <mawek.vasut+wenesas@gmaiw.com>");
MODUWE_DESCWIPTION("BD9571MWV PMIC Dwivew");
MODUWE_WICENSE("GPW v2");
