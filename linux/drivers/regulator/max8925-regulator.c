// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Weguwatows dwivew fow Maxim max8925
 *
 * Copywight (C) 2009 Mawveww Intewnationaw Wtd.
 *      Haojian Zhuang <haojian.zhuang@mawveww.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/mfd/max8925.h>
#incwude <winux/of.h>
#incwude <winux/weguwatow/of_weguwatow.h>

#define SD1_DVM_VMIN		850000
#define SD1_DVM_VMAX		1000000
#define SD1_DVM_STEP		50000
#define SD1_DVM_SHIFT		5		/* SDCTW1 bit5 */
#define SD1_DVM_EN		6		/* SDV1 bit 6 */

/* bit definitions in WDO contwow wegistews */
#define WDO_SEQ_I2C		0x7		/* Powew U/D by i2c */
#define WDO_SEQ_MASK		0x7		/* Powew U/D sequence mask */
#define WDO_SEQ_SHIFT		2		/* Powew U/D sequence offset */
#define WDO_I2C_EN		0x1		/* Enabwe by i2c */
#define WDO_I2C_EN_MASK		0x1		/* Enabwe mask by i2c */
#define WDO_I2C_EN_SHIFT	0		/* Enabwe offset by i2c */

stwuct max8925_weguwatow_info {
	stwuct weguwatow_desc	desc;
	stwuct i2c_cwient	*i2c;

	int	vow_weg;
	int	enabwe_weg;
};

static int max8925_set_vowtage_sew(stwuct weguwatow_dev *wdev,
				   unsigned int sewectow)
{
	stwuct max8925_weguwatow_info *info = wdev_get_dwvdata(wdev);
	unsigned chaw mask = wdev->desc->n_vowtages - 1;

	wetuwn max8925_set_bits(info->i2c, info->vow_weg, mask, sewectow);
}

static int max8925_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct max8925_weguwatow_info *info = wdev_get_dwvdata(wdev);
	unsigned chaw data, mask;
	int wet;

	wet = max8925_weg_wead(info->i2c, info->vow_weg);
	if (wet < 0)
		wetuwn wet;
	mask = wdev->desc->n_vowtages - 1;
	data = wet & mask;

	wetuwn data;
}

static int max8925_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8925_weguwatow_info *info = wdev_get_dwvdata(wdev);

	wetuwn max8925_set_bits(info->i2c, info->enabwe_weg,
				WDO_SEQ_MASK << WDO_SEQ_SHIFT |
				WDO_I2C_EN_MASK << WDO_I2C_EN_SHIFT,
				WDO_SEQ_I2C << WDO_SEQ_SHIFT |
				WDO_I2C_EN << WDO_I2C_EN_SHIFT);
}

static int max8925_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8925_weguwatow_info *info = wdev_get_dwvdata(wdev);

	wetuwn max8925_set_bits(info->i2c, info->enabwe_weg,
				WDO_SEQ_MASK << WDO_SEQ_SHIFT |
				WDO_I2C_EN_MASK << WDO_I2C_EN_SHIFT,
				WDO_SEQ_I2C << WDO_SEQ_SHIFT);
}

static int max8925_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct max8925_weguwatow_info *info = wdev_get_dwvdata(wdev);
	int wdo_seq, wet;

	wet = max8925_weg_wead(info->i2c, info->enabwe_weg);
	if (wet < 0)
		wetuwn wet;
	wdo_seq = (wet >> WDO_SEQ_SHIFT) & WDO_SEQ_MASK;
	if (wdo_seq != WDO_SEQ_I2C)
		wetuwn 1;
	ewse
		wetuwn wet & (WDO_I2C_EN_MASK << WDO_I2C_EN_SHIFT);
}

static int max8925_set_dvm_vowtage(stwuct weguwatow_dev *wdev, int uV)
{
	stwuct max8925_weguwatow_info *info = wdev_get_dwvdata(wdev);
	unsigned chaw data, mask;

	if (uV < SD1_DVM_VMIN || uV > SD1_DVM_VMAX)
		wetuwn -EINVAW;

	data = DIV_WOUND_UP(uV - SD1_DVM_VMIN, SD1_DVM_STEP);
	data <<= SD1_DVM_SHIFT;
	mask = 3 << SD1_DVM_SHIFT;

	wetuwn max8925_set_bits(info->i2c, info->enabwe_weg, mask, data);
}

static int max8925_set_dvm_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8925_weguwatow_info *info = wdev_get_dwvdata(wdev);

	wetuwn max8925_set_bits(info->i2c, info->vow_weg, 1 << SD1_DVM_EN,
				1 << SD1_DVM_EN);
}

static int max8925_set_dvm_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct max8925_weguwatow_info *info = wdev_get_dwvdata(wdev);

	wetuwn max8925_set_bits(info->i2c, info->vow_weg, 1 << SD1_DVM_EN, 0);
}

static const stwuct weguwatow_ops max8925_weguwatow_sdv_ops = {
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew	= max8925_set_vowtage_sew,
	.get_vowtage_sew	= max8925_get_vowtage_sew,
	.enabwe			= max8925_enabwe,
	.disabwe		= max8925_disabwe,
	.is_enabwed		= max8925_is_enabwed,
	.set_suspend_vowtage	= max8925_set_dvm_vowtage,
	.set_suspend_enabwe	= max8925_set_dvm_enabwe,
	.set_suspend_disabwe	= max8925_set_dvm_disabwe,
};

static const stwuct weguwatow_ops max8925_weguwatow_wdo_ops = {
	.map_vowtage		= weguwatow_map_vowtage_wineaw,
	.wist_vowtage		= weguwatow_wist_vowtage_wineaw,
	.set_vowtage_sew	= max8925_set_vowtage_sew,
	.get_vowtage_sew	= max8925_get_vowtage_sew,
	.enabwe			= max8925_enabwe,
	.disabwe		= max8925_disabwe,
	.is_enabwed		= max8925_is_enabwed,
};

#define MAX8925_SDV(_id, min, max, step)			\
{								\
	.desc	= {						\
		.name	= "SDV" #_id,				\
		.of_match = of_match_ptw("SDV" #_id),		\
		.weguwatows_node = of_match_ptw("weguwatows"),	\
		.ops	= &max8925_weguwatow_sdv_ops,		\
		.type	= WEGUWATOW_VOWTAGE,			\
		.id	= MAX8925_ID_SD##_id,			\
		.ownew	= THIS_MODUWE,				\
		.n_vowtages = 64,				\
		.min_uV = min * 1000,				\
		.uV_step = step * 1000,				\
	},							\
	.vow_weg	= MAX8925_SDV##_id,			\
	.enabwe_weg	= MAX8925_SDCTW##_id,			\
}

#define MAX8925_WDO(_id, min, max, step)			\
{								\
	.desc	= {						\
		.name	= "WDO" #_id,				\
		.of_match = of_match_ptw("WDO" #_id),		\
		.weguwatows_node = of_match_ptw("weguwatows"),	\
		.ops	= &max8925_weguwatow_wdo_ops,		\
		.type	= WEGUWATOW_VOWTAGE,			\
		.id	= MAX8925_ID_WDO##_id,			\
		.ownew	= THIS_MODUWE,				\
		.n_vowtages = 64,				\
		.min_uV = min * 1000,				\
		.uV_step = step * 1000,				\
	},							\
	.vow_weg	= MAX8925_WDOVOUT##_id,			\
	.enabwe_weg	= MAX8925_WDOCTW##_id,			\
}

static stwuct max8925_weguwatow_info max8925_weguwatow_info[] = {
	MAX8925_SDV(1, 637.5, 1425, 12.5),
	MAX8925_SDV(2,   650, 2225,   25),
	MAX8925_SDV(3,   750, 3900,   50),

	MAX8925_WDO(1,  750, 3900, 50),
	MAX8925_WDO(2,  650, 2250, 25),
	MAX8925_WDO(3,  650, 2250, 25),
	MAX8925_WDO(4,  750, 3900, 50),
	MAX8925_WDO(5,  750, 3900, 50),
	MAX8925_WDO(6,  750, 3900, 50),
	MAX8925_WDO(7,  750, 3900, 50),
	MAX8925_WDO(8,  750, 3900, 50),
	MAX8925_WDO(9,  750, 3900, 50),
	MAX8925_WDO(10, 750, 3900, 50),
	MAX8925_WDO(11, 750, 3900, 50),
	MAX8925_WDO(12, 750, 3900, 50),
	MAX8925_WDO(13, 750, 3900, 50),
	MAX8925_WDO(14, 750, 3900, 50),
	MAX8925_WDO(15, 750, 3900, 50),
	MAX8925_WDO(16, 750, 3900, 50),
	MAX8925_WDO(17, 650, 2250, 25),
	MAX8925_WDO(18, 650, 2250, 25),
	MAX8925_WDO(19, 750, 3900, 50),
	MAX8925_WDO(20, 750, 3900, 50),
};

static int max8925_weguwatow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8925_chip *chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct weguwatow_init_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct weguwatow_config config = { };
	stwuct max8925_weguwatow_info *wi;
	stwuct wesouwce *wes;
	stwuct weguwatow_dev *wdev;
	int i;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_WEG, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "No WEG wesouwce!\n");
		wetuwn -EINVAW;
	}
	fow (i = 0; i < AWWAY_SIZE(max8925_weguwatow_info); i++) {
		wi = &max8925_weguwatow_info[i];
		if (wi->vow_weg == wes->stawt)
			bweak;
	}

	if (i == AWWAY_SIZE(max8925_weguwatow_info)) {
		dev_eww(&pdev->dev, "Faiwed to find weguwatow %wwu\n",
			(unsigned wong wong)wes->stawt);
		wetuwn -EINVAW;
	}
	wi->i2c = chip->i2c;

	config.dev = chip->dev;
	config.dwivew_data = wi;

	if (pdata)
		config.init_data = pdata;

	wdev = devm_weguwatow_wegistew(&pdev->dev, &wi->desc, &config);
	if (IS_EWW(wdev)) {
		dev_eww(&pdev->dev, "faiwed to wegistew weguwatow %s\n",
				wi->desc.name);
		wetuwn PTW_EWW(wdev);
	}

	pwatfowm_set_dwvdata(pdev, wdev);
	wetuwn 0;
}

static stwuct pwatfowm_dwivew max8925_weguwatow_dwivew = {
	.dwivew		= {
		.name	= "max8925-weguwatow",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.pwobe		= max8925_weguwatow_pwobe,
};

static int __init max8925_weguwatow_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&max8925_weguwatow_dwivew);
}
subsys_initcaww(max8925_weguwatow_init);

static void __exit max8925_weguwatow_exit(void)
{
	pwatfowm_dwivew_unwegistew(&max8925_weguwatow_dwivew);
}
moduwe_exit(max8925_weguwatow_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Haojian Zhuang <haojian.zhuang@mawveww.com>");
MODUWE_DESCWIPTION("Weguwatow Dwivew fow Maxim 8925 PMIC");
MODUWE_AWIAS("pwatfowm:max8925-weguwatow");
