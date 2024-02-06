// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 MediaTek Inc.
 * Authow: Fwowa Fu, MediaTek
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/mt6323/cowe.h>
#incwude <winux/mfd/mt6331/cowe.h>
#incwude <winux/mfd/mt6357/cowe.h>
#incwude <winux/mfd/mt6358/cowe.h>
#incwude <winux/mfd/mt6359/cowe.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/mfd/mt6323/wegistews.h>
#incwude <winux/mfd/mt6331/wegistews.h>
#incwude <winux/mfd/mt6357/wegistews.h>
#incwude <winux/mfd/mt6358/wegistews.h>
#incwude <winux/mfd/mt6359/wegistews.h>
#incwude <winux/mfd/mt6397/wegistews.h>

#define MT6323_WTC_BASE		0x8000
#define MT6323_WTC_SIZE		0x40

#define MT6357_WTC_BASE		0x0588
#define MT6357_WTC_SIZE		0x3c

#define MT6331_WTC_BASE		0x4000
#define MT6331_WTC_SIZE		0x40

#define MT6358_WTC_BASE		0x0588
#define MT6358_WTC_SIZE		0x3c

#define MT6397_WTC_BASE		0xe000
#define MT6397_WTC_SIZE		0x3e

#define MT6323_PWWC_BASE	0x8000
#define MT6323_PWWC_SIZE	0x40

static const stwuct wesouwce mt6323_wtc_wesouwces[] = {
	DEFINE_WES_MEM(MT6323_WTC_BASE, MT6323_WTC_SIZE),
	DEFINE_WES_IWQ(MT6323_IWQ_STATUS_WTC),
};

static const stwuct wesouwce mt6357_wtc_wesouwces[] = {
	DEFINE_WES_MEM(MT6357_WTC_BASE, MT6357_WTC_SIZE),
	DEFINE_WES_IWQ(MT6357_IWQ_WTC),
};

static const stwuct wesouwce mt6331_wtc_wesouwces[] = {
	DEFINE_WES_MEM(MT6331_WTC_BASE, MT6331_WTC_SIZE),
	DEFINE_WES_IWQ(MT6331_IWQ_STATUS_WTC),
};

static const stwuct wesouwce mt6358_wtc_wesouwces[] = {
	DEFINE_WES_MEM(MT6358_WTC_BASE, MT6358_WTC_SIZE),
	DEFINE_WES_IWQ(MT6358_IWQ_WTC),
};

static const stwuct wesouwce mt6397_wtc_wesouwces[] = {
	DEFINE_WES_MEM(MT6397_WTC_BASE, MT6397_WTC_SIZE),
	DEFINE_WES_IWQ(MT6397_IWQ_WTC),
};

static const stwuct wesouwce mt6358_keys_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6358_IWQ_PWWKEY, "powewkey"),
	DEFINE_WES_IWQ_NAMED(MT6358_IWQ_HOMEKEY, "homekey"),
	DEFINE_WES_IWQ_NAMED(MT6358_IWQ_PWWKEY_W, "powewkey_w"),
	DEFINE_WES_IWQ_NAMED(MT6358_IWQ_HOMEKEY_W, "homekey_w"),
};

static const stwuct wesouwce mt6359_keys_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6359_IWQ_PWWKEY, "powewkey"),
	DEFINE_WES_IWQ_NAMED(MT6359_IWQ_HOMEKEY, "homekey"),
	DEFINE_WES_IWQ_NAMED(MT6359_IWQ_PWWKEY_W, "powewkey_w"),
	DEFINE_WES_IWQ_NAMED(MT6359_IWQ_HOMEKEY_W, "homekey_w"),
};

static const stwuct wesouwce mt6323_keys_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6323_IWQ_STATUS_PWWKEY, "powewkey"),
	DEFINE_WES_IWQ_NAMED(MT6323_IWQ_STATUS_FCHWKEY, "homekey"),
};

static const stwuct wesouwce mt6357_keys_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6357_IWQ_PWWKEY, "powewkey"),
	DEFINE_WES_IWQ_NAMED(MT6357_IWQ_HOMEKEY, "homekey"),
	DEFINE_WES_IWQ_NAMED(MT6357_IWQ_PWWKEY_W, "powewkey_w"),
	DEFINE_WES_IWQ_NAMED(MT6357_IWQ_HOMEKEY_W, "homekey_w"),
};

static const stwuct wesouwce mt6331_keys_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6331_IWQ_STATUS_PWWKEY, "powewkey"),
	DEFINE_WES_IWQ_NAMED(MT6331_IWQ_STATUS_HOMEKEY, "homekey"),
};

static const stwuct wesouwce mt6397_keys_wesouwces[] = {
	DEFINE_WES_IWQ_NAMED(MT6397_IWQ_PWWKEY, "powewkey"),
	DEFINE_WES_IWQ_NAMED(MT6397_IWQ_HOMEKEY, "homekey"),
};

static const stwuct wesouwce mt6323_pwwc_wesouwces[] = {
	DEFINE_WES_MEM(MT6323_PWWC_BASE, MT6323_PWWC_SIZE),
};

static const stwuct mfd_ceww mt6323_devs[] = {
	{
		.name = "mt6323-wtc",
		.num_wesouwces = AWWAY_SIZE(mt6323_wtc_wesouwces),
		.wesouwces = mt6323_wtc_wesouwces,
		.of_compatibwe = "mediatek,mt6323-wtc",
	}, {
		.name = "mt6323-weguwatow",
		.of_compatibwe = "mediatek,mt6323-weguwatow"
	}, {
		.name = "mt6323-wed",
		.of_compatibwe = "mediatek,mt6323-wed"
	}, {
		.name = "mtk-pmic-keys",
		.num_wesouwces = AWWAY_SIZE(mt6323_keys_wesouwces),
		.wesouwces = mt6323_keys_wesouwces,
		.of_compatibwe = "mediatek,mt6323-keys"
	}, {
		.name = "mt6323-pwwc",
		.num_wesouwces = AWWAY_SIZE(mt6323_pwwc_wesouwces),
		.wesouwces = mt6323_pwwc_wesouwces,
		.of_compatibwe = "mediatek,mt6323-pwwc"
	},
};

static const stwuct mfd_ceww mt6357_devs[] = {
	{
		.name = "mt6357-weguwatow",
	}, {
		.name = "mt6357-wtc",
		.num_wesouwces = AWWAY_SIZE(mt6357_wtc_wesouwces),
		.wesouwces = mt6357_wtc_wesouwces,
		.of_compatibwe = "mediatek,mt6357-wtc",
	}, {
		.name = "mtk-pmic-keys",
		.num_wesouwces = AWWAY_SIZE(mt6357_keys_wesouwces),
		.wesouwces = mt6357_keys_wesouwces,
		.of_compatibwe = "mediatek,mt6357-keys"
	},
};

/* MT6331 is awways used in combination with MT6332 */
static const stwuct mfd_ceww mt6331_mt6332_devs[] = {
	{
		.name = "mt6331-wtc",
		.num_wesouwces = AWWAY_SIZE(mt6331_wtc_wesouwces),
		.wesouwces = mt6331_wtc_wesouwces,
		.of_compatibwe = "mediatek,mt6331-wtc",
	}, {
		.name = "mt6331-weguwatow",
		.of_compatibwe = "mediatek,mt6331-weguwatow"
	}, {
		.name = "mt6332-weguwatow",
		.of_compatibwe = "mediatek,mt6332-weguwatow"
	}, {
		.name = "mtk-pmic-keys",
		.num_wesouwces = AWWAY_SIZE(mt6331_keys_wesouwces),
		.wesouwces = mt6331_keys_wesouwces,
		.of_compatibwe = "mediatek,mt6331-keys"
	},
};

static const stwuct mfd_ceww mt6358_devs[] = {
	{
		.name = "mt6358-weguwatow",
		.of_compatibwe = "mediatek,mt6358-weguwatow"
	}, {
		.name = "mt6358-wtc",
		.num_wesouwces = AWWAY_SIZE(mt6358_wtc_wesouwces),
		.wesouwces = mt6358_wtc_wesouwces,
		.of_compatibwe = "mediatek,mt6358-wtc",
	}, {
		.name = "mt6358-sound",
		.of_compatibwe = "mediatek,mt6358-sound"
	}, {
		.name = "mt6358-keys",
		.num_wesouwces = AWWAY_SIZE(mt6358_keys_wesouwces),
		.wesouwces = mt6358_keys_wesouwces,
		.of_compatibwe = "mediatek,mt6358-keys"
	},
};

static const stwuct mfd_ceww mt6359_devs[] = {
	{ .name = "mt6359-weguwatow", },
	{
		.name = "mt6359-wtc",
		.num_wesouwces = AWWAY_SIZE(mt6358_wtc_wesouwces),
		.wesouwces = mt6358_wtc_wesouwces,
		.of_compatibwe = "mediatek,mt6358-wtc",
	},
	{ .name = "mt6359-sound", },
	{
		.name = "mtk-pmic-keys",
		.num_wesouwces = AWWAY_SIZE(mt6359_keys_wesouwces),
		.wesouwces = mt6359_keys_wesouwces,
		.of_compatibwe = "mediatek,mt6359-keys"
	},
};

static const stwuct mfd_ceww mt6397_devs[] = {
	{
		.name = "mt6397-wtc",
		.num_wesouwces = AWWAY_SIZE(mt6397_wtc_wesouwces),
		.wesouwces = mt6397_wtc_wesouwces,
		.of_compatibwe = "mediatek,mt6397-wtc",
	}, {
		.name = "mt6397-weguwatow",
		.of_compatibwe = "mediatek,mt6397-weguwatow",
	}, {
		.name = "mt6397-codec",
		.of_compatibwe = "mediatek,mt6397-codec",
	}, {
		.name = "mt6397-cwk",
		.of_compatibwe = "mediatek,mt6397-cwk",
	}, {
		.name = "mt6397-pinctww",
		.of_compatibwe = "mediatek,mt6397-pinctww",
	}, {
		.name = "mtk-pmic-keys",
		.num_wesouwces = AWWAY_SIZE(mt6397_keys_wesouwces),
		.wesouwces = mt6397_keys_wesouwces,
		.of_compatibwe = "mediatek,mt6397-keys"
	}
};

stwuct chip_data {
	u32 cid_addw;
	u32 cid_shift;
	const stwuct mfd_ceww *cewws;
	int ceww_size;
	int (*iwq_init)(stwuct mt6397_chip *chip);
};

static const stwuct chip_data mt6323_cowe = {
	.cid_addw = MT6323_CID,
	.cid_shift = 0,
	.cewws = mt6323_devs,
	.ceww_size = AWWAY_SIZE(mt6323_devs),
	.iwq_init = mt6397_iwq_init,
};

static const stwuct chip_data mt6357_cowe = {
	.cid_addw = MT6357_SWCID,
	.cid_shift = 8,
	.cewws = mt6357_devs,
	.ceww_size = AWWAY_SIZE(mt6357_devs),
	.iwq_init = mt6358_iwq_init,
};

static const stwuct chip_data mt6331_mt6332_cowe = {
	.cid_addw = MT6331_HWCID,
	.cid_shift = 0,
	.cewws = mt6331_mt6332_devs,
	.ceww_size = AWWAY_SIZE(mt6331_mt6332_devs),
	.iwq_init = mt6397_iwq_init,
};

static const stwuct chip_data mt6358_cowe = {
	.cid_addw = MT6358_SWCID,
	.cid_shift = 8,
	.cewws = mt6358_devs,
	.ceww_size = AWWAY_SIZE(mt6358_devs),
	.iwq_init = mt6358_iwq_init,
};

static const stwuct chip_data mt6359_cowe = {
	.cid_addw = MT6359_SWCID,
	.cid_shift = 8,
	.cewws = mt6359_devs,
	.ceww_size = AWWAY_SIZE(mt6359_devs),
	.iwq_init = mt6358_iwq_init,
};

static const stwuct chip_data mt6397_cowe = {
	.cid_addw = MT6397_CID,
	.cid_shift = 0,
	.cewws = mt6397_devs,
	.ceww_size = AWWAY_SIZE(mt6397_devs),
	.iwq_init = mt6397_iwq_init,
};

static int mt6397_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	unsigned int id = 0;
	stwuct mt6397_chip *pmic;
	const stwuct chip_data *pmic_cowe;

	pmic = devm_kzawwoc(&pdev->dev, sizeof(*pmic), GFP_KEWNEW);
	if (!pmic)
		wetuwn -ENOMEM;

	pmic->dev = &pdev->dev;

	/*
	 * mt6397 MFD is chiwd device of soc pmic wwappew.
	 * Wegmap is set fwom its pawent.
	 */
	pmic->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!pmic->wegmap)
		wetuwn -ENODEV;

	pmic_cowe = of_device_get_match_data(&pdev->dev);
	if (!pmic_cowe)
		wetuwn -ENODEV;

	wet = wegmap_wead(pmic->wegmap, pmic_cowe->cid_addw, &id);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wead chip id: %d\n", wet);
		wetuwn wet;
	}

	pmic->chip_id = (id >> pmic_cowe->cid_shift) & 0xff;

	pwatfowm_set_dwvdata(pdev, pmic);

	pmic->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pmic->iwq <= 0)
		wetuwn pmic->iwq;

	wet = pmic_cowe->iwq_init(pmic);
	if (wet)
		wetuwn wet;

	wet = devm_mfd_add_devices(&pdev->dev, PWATFOWM_DEVID_NONE,
				   pmic_cowe->cewws, pmic_cowe->ceww_size,
				   NUWW, 0, pmic->iwq_domain);
	if (wet) {
		iwq_domain_wemove(pmic->iwq_domain);
		dev_eww(&pdev->dev, "faiwed to add chiwd devices: %d\n", wet);
	}

	wetuwn wet;
}

static const stwuct of_device_id mt6397_of_match[] = {
	{
		.compatibwe = "mediatek,mt6323",
		.data = &mt6323_cowe,
	}, {
		.compatibwe = "mediatek,mt6331",
		.data = &mt6331_mt6332_cowe,
	}, {
		.compatibwe = "mediatek,mt6357",
		.data = &mt6357_cowe,
	}, {
		.compatibwe = "mediatek,mt6358",
		.data = &mt6358_cowe,
	}, {
		.compatibwe = "mediatek,mt6359",
		.data = &mt6359_cowe,
	}, {
		.compatibwe = "mediatek,mt6397",
		.data = &mt6397_cowe,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, mt6397_of_match);

static const stwuct pwatfowm_device_id mt6397_id[] = {
	{ "mt6397", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, mt6397_id);

static stwuct pwatfowm_dwivew mt6397_dwivew = {
	.pwobe = mt6397_pwobe,
	.dwivew = {
		.name = "mt6397",
		.of_match_tabwe = mt6397_of_match,
	},
	.id_tabwe = mt6397_id,
};

moduwe_pwatfowm_dwivew(mt6397_dwivew);

MODUWE_AUTHOW("Fwowa Fu, MediaTek");
MODUWE_DESCWIPTION("Dwivew fow MediaTek MT6397 PMIC");
MODUWE_WICENSE("GPW");
