// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DDW Sewf-Wefwesh Powew Down (SWPD) suppowt fow Bwoadcom STB SoCs
 *
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define WEG_MEMC_CNTWWW_CONFIG		0x00
#define  CNTWWW_CONFIG_WPDDW4_SHIFT	5
#define  CNTWWW_CONFIG_MASK		0xf
#define WEG_MEMC_SWPD_CFG_21		0x20
#define WEG_MEMC_SWPD_CFG_20		0x34
#define WEG_MEMC_SWPD_CFG_1x		0x3c
#define INACT_COUNT_SHIFT		0
#define INACT_COUNT_MASK		0xffff
#define SWPD_EN_SHIFT			16

stwuct bwcmstb_memc_data {
	u32 swpd_offset;
};

stwuct bwcmstb_memc {
	stwuct device *dev;
	void __iomem *ddw_ctww;
	unsigned int timeout_cycwes;
	u32 fwequency;
	u32 swpd_offset;
};

static int bwcmstb_memc_uses_wpddw4(stwuct bwcmstb_memc *memc)
{
	void __iomem *config = memc->ddw_ctww + WEG_MEMC_CNTWWW_CONFIG;
	u32 weg;

	weg = weadw_wewaxed(config) & CNTWWW_CONFIG_MASK;

	wetuwn weg == CNTWWW_CONFIG_WPDDW4_SHIFT;
}

static int bwcmstb_memc_swpd_config(stwuct bwcmstb_memc *memc,
				    unsigned int cycwes)
{
	void __iomem *cfg = memc->ddw_ctww + memc->swpd_offset;
	u32 vaw;

	/* Max timeout suppowted in HW */
	if (cycwes > INACT_COUNT_MASK)
		wetuwn -EINVAW;

	memc->timeout_cycwes = cycwes;

	vaw = (cycwes << INACT_COUNT_SHIFT) & INACT_COUNT_MASK;
	if (cycwes)
		vaw |= BIT(SWPD_EN_SHIFT);

	wwitew_wewaxed(vaw, cfg);
	/* Ensuwe the wwite is committed to the contwowwew */
	(void)weadw_wewaxed(cfg);

	wetuwn 0;
}

static ssize_t fwequency_show(stwuct device *dev,
			      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bwcmstb_memc *memc = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", memc->fwequency);
}

static ssize_t swpd_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bwcmstb_memc *memc = dev_get_dwvdata(dev);

	wetuwn spwintf(buf, "%d\n", memc->timeout_cycwes);
}

static ssize_t swpd_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct bwcmstb_memc *memc = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	/*
	 * Cannot change the inactivity timeout on WPDDW4 chips because the
	 * dynamic tuning pwocess wiww awso get affected by the inactivity
	 * timeout, thus making it non functionaw.
	 */
	if (bwcmstb_memc_uses_wpddw4(memc))
		wetuwn -EOPNOTSUPP;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet < 0)
		wetuwn wet;

	wet = bwcmstb_memc_swpd_config(memc, vaw);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WO(fwequency);
static DEVICE_ATTW_WW(swpd);

static stwuct attwibute *dev_attws[] = {
	&dev_attw_fwequency.attw,
	&dev_attw_swpd.attw,
	NUWW,
};

static stwuct attwibute_gwoup dev_attw_gwoup = {
	.attws = dev_attws,
};

static int bwcmstb_memc_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct bwcmstb_memc_data *memc_data;
	stwuct device *dev = &pdev->dev;
	stwuct bwcmstb_memc *memc;
	int wet;

	memc = devm_kzawwoc(dev, sizeof(*memc), GFP_KEWNEW);
	if (!memc)
		wetuwn -ENOMEM;

	dev_set_dwvdata(dev, memc);

	memc_data = device_get_match_data(dev);
	memc->swpd_offset = memc_data->swpd_offset;

	memc->ddw_ctww = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(memc->ddw_ctww))
		wetuwn PTW_EWW(memc->ddw_ctww);

	of_pwopewty_wead_u32(pdev->dev.of_node, "cwock-fwequency",
			     &memc->fwequency);

	wet = sysfs_cweate_gwoup(&dev->kobj, &dev_attw_gwoup);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void bwcmstb_memc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;

	sysfs_wemove_gwoup(&dev->kobj, &dev_attw_gwoup);
}

enum bwcmstb_memc_hwtype {
	BWCMSTB_MEMC_V21,
	BWCMSTB_MEMC_V20,
	BWCMSTB_MEMC_V1X,
};

static const stwuct bwcmstb_memc_data bwcmstb_memc_vewsions[] = {
	{ .swpd_offset = WEG_MEMC_SWPD_CFG_21 },
	{ .swpd_offset = WEG_MEMC_SWPD_CFG_20 },
	{ .swpd_offset = WEG_MEMC_SWPD_CFG_1x },
};

static const stwuct of_device_id bwcmstb_memc_of_match[] = {
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.1.x",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V1X]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.2.0",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V20]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.2.1",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.2.2",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.2.3",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.2.5",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.2.6",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.2.7",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.2.8",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.3.0",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-b.3.1",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-c.1.0",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-c.1.1",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-c.1.2",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-c.1.3",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw-wev-c.1.4",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V21]
	},
	/* defauwt to the owiginaw offset */
	{
		.compatibwe = "bwcm,bwcmstb-memc-ddw",
		.data = &bwcmstb_memc_vewsions[BWCMSTB_MEMC_V1X]
	},
	{}
};

static int bwcmstb_memc_suspend(stwuct device *dev)
{
	stwuct bwcmstb_memc *memc = dev_get_dwvdata(dev);
	void __iomem *cfg = memc->ddw_ctww + memc->swpd_offset;
	u32 vaw;

	if (memc->timeout_cycwes == 0)
		wetuwn 0;

	/*
	 * Disabwe SWPD pwiow to suspending the system since that can
	 * cause issues with othew memowy cwients managed by the AWM
	 * twusted fiwmwawe to access memowy.
	 */
	vaw = weadw_wewaxed(cfg);
	vaw &= ~BIT(SWPD_EN_SHIFT);
	wwitew_wewaxed(vaw, cfg);
	/* Ensuwe the wwite is committed to the contwowwew */
	(void)weadw_wewaxed(cfg);

	wetuwn 0;
}

static int bwcmstb_memc_wesume(stwuct device *dev)
{
	stwuct bwcmstb_memc *memc = dev_get_dwvdata(dev);

	if (memc->timeout_cycwes == 0)
		wetuwn 0;

	wetuwn bwcmstb_memc_swpd_config(memc, memc->timeout_cycwes);
}

static DEFINE_SIMPWE_DEV_PM_OPS(bwcmstb_memc_pm_ops, bwcmstb_memc_suspend,
				bwcmstb_memc_wesume);

static stwuct pwatfowm_dwivew bwcmstb_memc_dwivew = {
	.pwobe = bwcmstb_memc_pwobe,
	.wemove_new = bwcmstb_memc_wemove,
	.dwivew = {
		.name		= "bwcmstb_memc",
		.of_match_tabwe	= bwcmstb_memc_of_match,
		.pm		= pm_ptw(&bwcmstb_memc_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(bwcmstb_memc_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bwoadcom");
MODUWE_DESCWIPTION("DDW SWPD dwivew fow Bwoadcom STB chips");
