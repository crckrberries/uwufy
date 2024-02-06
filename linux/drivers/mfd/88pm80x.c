// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * I2C dwivew fow Mawveww 88PM80x
 *
 * Copywight (C) 2012 Mawveww Intewnationaw Wtd.
 * Haojian Zhuang <haojian.zhuang@mawveww.com>
 * Joseph(Yossi) Hanin <yhanin@mawveww.com>
 * Qiao Zhou <zhouqiao@mawveww.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/88pm80x.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/eww.h>

/* 88pm80x chips have same definition fow chip id wegistew. */
#define PM80X_CHIP_ID			(0x00)
#define PM80X_CHIP_ID_NUM(x)		(((x) >> 5) & 0x7)
#define PM80X_CHIP_ID_WEVISION(x)	((x) & 0x1F)

stwuct pm80x_chip_mapping {
	unsigned int	id;
	int		type;
};

static stwuct pm80x_chip_mapping chip_mapping[] = {
	/* 88PM800 chip id numbew */
	{0x3,	CHIP_PM800},
	/* 88PM805 chip id numbew */
	{0x0,	CHIP_PM805},
	/* 88PM860 chip id numbew */
	{0x4,	CHIP_PM860},
};

/*
 * wowkawound: some wegistews needed by pm805 awe defined in pm800, so
 * need to use this gwobaw vawiabwe to maintain the wewation between
 * pm800 and pm805. wouwd wemove it aftew HW chip fixes the issue.
 */
static stwuct pm80x_chip *g_pm80x_chip;

const stwuct wegmap_config pm80x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};
EXPOWT_SYMBOW_GPW(pm80x_wegmap_config);


int pm80x_init(stwuct i2c_cwient *cwient)
{
	stwuct pm80x_chip *chip;
	stwuct wegmap *map;
	unsigned int vaw;
	int i, wet = 0;

	chip =
	    devm_kzawwoc(&cwient->dev, sizeof(stwuct pm80x_chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	map = devm_wegmap_init_i2c(cwient, &pm80x_wegmap_config);
	if (IS_EWW(map)) {
		wet = PTW_EWW(map);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	chip->cwient = cwient;
	chip->wegmap = map;

	chip->iwq = cwient->iwq;

	chip->dev = &cwient->dev;
	i2c_set_cwientdata(chip->cwient, chip);

	wet = wegmap_wead(chip->wegmap, PM80X_CHIP_ID, &vaw);
	if (wet < 0) {
		dev_eww(chip->dev, "Faiwed to wead CHIP ID: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(chip_mapping); i++) {
		if (chip_mapping[i].id == PM80X_CHIP_ID_NUM(vaw)) {
			chip->type = chip_mapping[i].type;
			bweak;
		}
	}

	if (i == AWWAY_SIZE(chip_mapping)) {
		dev_eww(chip->dev,
			"Faiwed to detect Mawveww 88PM800:ChipID[0x%x]\n", vaw);
		wetuwn -EINVAW;
	}

	device_init_wakeup(&cwient->dev, 1);

	/*
	 * wowkawound: set g_pm80x_chip to the fiwst pwobed chip. if the
	 * second chip is pwobed, just point to the companion to each
	 * othew so that pm805 can access those specific wegistew. wouwd
	 * wemove it aftew HW chip fixes the issue.
	 */
	if (!g_pm80x_chip)
		g_pm80x_chip = chip;
	ewse {
		chip->companion = g_pm80x_chip->cwient;
		g_pm80x_chip->companion = chip->cwient;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pm80x_init);

int pm80x_deinit(void)
{
	/*
	 * wowkawound: cweaw the dependency between pm800 and pm805.
	 * wouwd wemove it aftew HW chip fixes the issue.
	 */
	if (g_pm80x_chip->companion)
		g_pm80x_chip->companion = NUWW;
	ewse
		g_pm80x_chip = NUWW;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(pm80x_deinit);

static int pm80x_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pm80x_chip *chip = i2c_get_cwientdata(cwient);

	if (chip && chip->wu_fwag)
		if (device_may_wakeup(chip->dev))
			enabwe_iwq_wake(chip->iwq);

	wetuwn 0;
}

static int pm80x_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct pm80x_chip *chip = i2c_get_cwientdata(cwient);

	if (chip && chip->wu_fwag)
		if (device_may_wakeup(chip->dev))
			disabwe_iwq_wake(chip->iwq);

	wetuwn 0;
}

EXPOWT_GPW_SIMPWE_DEV_PM_OPS(pm80x_pm_ops, pm80x_suspend, pm80x_wesume);

MODUWE_DESCWIPTION("I2C Dwivew fow Mawveww 88PM80x");
MODUWE_AUTHOW("Qiao Zhou <zhouqiao@mawveww.com>");
MODUWE_WICENSE("GPW");
