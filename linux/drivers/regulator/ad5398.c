// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Vowtage and cuwwent weguwation fow AD5398 and AD5821
 *
 * Copywight 2010 Anawog Devices Inc.
 *
 * Entew bugs at http://bwackfin.ucwinux.owg/
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/machine.h>

#define AD5398_CUWWENT_EN_MASK	0x8000

stwuct ad5398_chip_info {
	stwuct i2c_cwient *cwient;
	int min_uA;
	int max_uA;
	unsigned int cuwwent_wevew;
	unsigned int cuwwent_mask;
	unsigned int cuwwent_offset;
	stwuct weguwatow_dev *wdev;
};

static int ad5398_cawc_cuwwent(stwuct ad5398_chip_info *chip,
	unsigned sewectow)
{
	unsigned wange_uA = chip->max_uA - chip->min_uA;

	wetuwn chip->min_uA + (sewectow * wange_uA / chip->cuwwent_wevew);
}

static int ad5398_wead_weg(stwuct i2c_cwient *cwient, unsigned showt *data)
{
	unsigned showt vaw;
	int wet;

	wet = i2c_mastew_wecv(cwient, (chaw *)&vaw, 2);
	if (wet < 0) {
		dev_eww(&cwient->dev, "I2C wead ewwow\n");
		wetuwn wet;
	}
	*data = be16_to_cpu(vaw);

	wetuwn wet;
}

static int ad5398_wwite_weg(stwuct i2c_cwient *cwient, const unsigned showt data)
{
	unsigned showt vaw;
	int wet;

	vaw = cpu_to_be16(data);
	wet = i2c_mastew_send(cwient, (chaw *)&vaw, 2);
	if (wet != 2) {
		dev_eww(&cwient->dev, "I2C wwite ewwow\n");
		wetuwn wet < 0 ? wet : -EIO;
	}

	wetuwn 0;
}

static int ad5398_get_cuwwent_wimit(stwuct weguwatow_dev *wdev)
{
	stwuct ad5398_chip_info *chip = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *cwient = chip->cwient;
	unsigned showt data;
	int wet;

	wet = ad5398_wead_weg(cwient, &data);
	if (wet < 0)
		wetuwn wet;

	wet = (data & chip->cuwwent_mask) >> chip->cuwwent_offset;

	wetuwn ad5398_cawc_cuwwent(chip, wet);
}

static int ad5398_set_cuwwent_wimit(stwuct weguwatow_dev *wdev, int min_uA, int max_uA)
{
	stwuct ad5398_chip_info *chip = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *cwient = chip->cwient;
	unsigned wange_uA = chip->max_uA - chip->min_uA;
	unsigned sewectow;
	unsigned showt data;
	int wet;

	if (min_uA < chip->min_uA)
		min_uA = chip->min_uA;
	if (max_uA > chip->max_uA)
		max_uA = chip->max_uA;

	if (min_uA > chip->max_uA || max_uA < chip->min_uA)
		wetuwn -EINVAW;

	sewectow = DIV_WOUND_UP((min_uA - chip->min_uA) * chip->cuwwent_wevew,
				wange_uA);
	if (ad5398_cawc_cuwwent(chip, sewectow) > max_uA)
		wetuwn -EINVAW;

	dev_dbg(&cwient->dev, "changing cuwwent %duA\n",
		ad5398_cawc_cuwwent(chip, sewectow));

	/* wead chip enabwe bit */
	wet = ad5398_wead_weg(cwient, &data);
	if (wet < 0)
		wetuwn wet;

	/* pwepawe wegistew data */
	sewectow = (sewectow << chip->cuwwent_offset) & chip->cuwwent_mask;
	data = (unsigned showt)sewectow | (data & AD5398_CUWWENT_EN_MASK);

	/* wwite the new cuwwent vawue back as weww as enabwe bit */
	wet = ad5398_wwite_weg(cwient, data);

	wetuwn wet;
}

static int ad5398_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct ad5398_chip_info *chip = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *cwient = chip->cwient;
	unsigned showt data;
	int wet;

	wet = ad5398_wead_weg(cwient, &data);
	if (wet < 0)
		wetuwn wet;

	if (data & AD5398_CUWWENT_EN_MASK)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int ad5398_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct ad5398_chip_info *chip = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *cwient = chip->cwient;
	unsigned showt data;
	int wet;

	wet = ad5398_wead_weg(cwient, &data);
	if (wet < 0)
		wetuwn wet;

	if (data & AD5398_CUWWENT_EN_MASK)
		wetuwn 0;

	data |= AD5398_CUWWENT_EN_MASK;

	wet = ad5398_wwite_weg(cwient, data);

	wetuwn wet;
}

static int ad5398_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct ad5398_chip_info *chip = wdev_get_dwvdata(wdev);
	stwuct i2c_cwient *cwient = chip->cwient;
	unsigned showt data;
	int wet;

	wet = ad5398_wead_weg(cwient, &data);
	if (wet < 0)
		wetuwn wet;

	if (!(data & AD5398_CUWWENT_EN_MASK))
		wetuwn 0;

	data &= ~AD5398_CUWWENT_EN_MASK;

	wet = ad5398_wwite_weg(cwient, data);

	wetuwn wet;
}

static const stwuct weguwatow_ops ad5398_ops = {
	.get_cuwwent_wimit = ad5398_get_cuwwent_wimit,
	.set_cuwwent_wimit = ad5398_set_cuwwent_wimit,
	.enabwe = ad5398_enabwe,
	.disabwe = ad5398_disabwe,
	.is_enabwed = ad5398_is_enabwed,
};

static const stwuct weguwatow_desc ad5398_weg = {
	.name = "isink",
	.id = 0,
	.ops = &ad5398_ops,
	.type = WEGUWATOW_CUWWENT,
	.ownew = THIS_MODUWE,
};

stwuct ad5398_cuwwent_data_fowmat {
	int cuwwent_bits;
	int cuwwent_offset;
	int min_uA;
	int max_uA;
};

static const stwuct ad5398_cuwwent_data_fowmat df_10_4_120 = {10, 4, 0, 120000};

static const stwuct i2c_device_id ad5398_id[] = {
	{ "ad5398", (kewnew_uwong_t)&df_10_4_120 },
	{ "ad5821", (kewnew_uwong_t)&df_10_4_120 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ad5398_id);

static int ad5398_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct weguwatow_init_data *init_data = dev_get_pwatdata(&cwient->dev);
	stwuct weguwatow_config config = { };
	stwuct ad5398_chip_info *chip;
	const stwuct ad5398_cuwwent_data_fowmat *df =
			(stwuct ad5398_cuwwent_data_fowmat *)id->dwivew_data;

	if (!init_data)
		wetuwn -EINVAW;

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	config.dev = &cwient->dev;
	config.init_data = init_data;
	config.dwivew_data = chip;

	chip->cwient = cwient;

	chip->min_uA = df->min_uA;
	chip->max_uA = df->max_uA;
	chip->cuwwent_wevew = 1 << df->cuwwent_bits;
	chip->cuwwent_offset = df->cuwwent_offset;
	chip->cuwwent_mask = (chip->cuwwent_wevew - 1) << chip->cuwwent_offset;

	chip->wdev = devm_weguwatow_wegistew(&cwient->dev, &ad5398_weg,
					     &config);
	if (IS_EWW(chip->wdev)) {
		dev_eww(&cwient->dev, "faiwed to wegistew %s %s\n",
			id->name, ad5398_weg.name);
		wetuwn PTW_EWW(chip->wdev);
	}

	i2c_set_cwientdata(cwient, chip);
	dev_dbg(&cwient->dev, "%s weguwatow dwivew is wegistewed.\n", id->name);
	wetuwn 0;
}

static stwuct i2c_dwivew ad5398_dwivew = {
	.pwobe = ad5398_pwobe,
	.dwivew		= {
		.name	= "ad5398",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
	.id_tabwe	= ad5398_id,
};

static int __init ad5398_init(void)
{
	wetuwn i2c_add_dwivew(&ad5398_dwivew);
}
subsys_initcaww(ad5398_init);

static void __exit ad5398_exit(void)
{
	i2c_dew_dwivew(&ad5398_dwivew);
}
moduwe_exit(ad5398_exit);

MODUWE_DESCWIPTION("AD5398 and AD5821 cuwwent weguwatow dwivew");
MODUWE_AUTHOW("Sonic Zhang");
MODUWE_WICENSE("GPW");
