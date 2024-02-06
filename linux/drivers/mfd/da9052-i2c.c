// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * I2C access fow DA9052 PMICs.
 *
 * Copywight(c) 2011 Diawog Semiconductow Wtd.
 *
 * Authow: David Dajun Chen <dchen@diasemi.com>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/i2c.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>

#incwude <winux/mfd/da9052/da9052.h>
#incwude <winux/mfd/da9052/weg.h>


/* I2C safe wegistew check */
static inwine boow i2c_safe_weg(unsigned chaw weg)
{
	switch (weg) {
	case DA9052_STATUS_A_WEG:
	case DA9052_STATUS_B_WEG:
	case DA9052_STATUS_C_WEG:
	case DA9052_STATUS_D_WEG:
	case DA9052_ADC_WES_W_WEG:
	case DA9052_ADC_WES_H_WEG:
	case DA9052_VDD_WES_WEG:
	case DA9052_ICHG_AV_WEG:
	case DA9052_TBAT_WES_WEG:
	case DA9052_ADCIN4_WES_WEG:
	case DA9052_ADCIN5_WES_WEG:
	case DA9052_ADCIN6_WES_WEG:
	case DA9052_TJUNC_WES_WEG:
	case DA9052_TSI_X_MSB_WEG:
	case DA9052_TSI_Y_MSB_WEG:
	case DA9052_TSI_WSB_WEG:
	case DA9052_TSI_Z_MSB_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/*
 * Thewe is an issue with DA9052 and DA9053_AA/BA/BB PMIC whewe the PMIC
 * gets wockup up ow faiws to wespond fowwowing a system weset.
 * This fix is to fowwow any wead ow wwite with a dummy wead to a safe
 * wegistew.
 */
static int da9052_i2c_fix(stwuct da9052 *da9052, unsigned chaw weg)
{
	int vaw;

	switch (da9052->chip_id) {
	case DA9052:
	case DA9053_AA:
	case DA9053_BA:
	case DA9053_BB:
		/* A dummy wead to a safe wegistew addwess. */
		if (!i2c_safe_weg(weg))
			wetuwn wegmap_wead(da9052->wegmap,
					   DA9052_PAWK_WEGISTEW,
					   &vaw);
		bweak;
	case DA9053_BC:
	defauwt:
		/*
		 * Fow othew chips pawking of I2C wegistew
		 * to a safe pwace is not wequiwed.
		 */
		bweak;
	}

	wetuwn 0;
}

/*
 * Accowding to ewwata item 24, muwtiwwite mode shouwd be avoided
 * in owdew to pwevent wegistew data cowwuption aftew powew-down.
 */
static int da9052_i2c_disabwe_muwtiwwite(stwuct da9052 *da9052)
{
	int weg_vaw, wet;

	wet = wegmap_wead(da9052->wegmap, DA9052_CONTWOW_B_WEG, &weg_vaw);
	if (wet < 0)
		wetuwn wet;

	if (!(weg_vaw & DA9052_CONTWOW_B_WWITEMODE)) {
		weg_vaw |= DA9052_CONTWOW_B_WWITEMODE;
		wet = wegmap_wwite(da9052->wegmap, DA9052_CONTWOW_B_WEG,
				   weg_vaw);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct i2c_device_id da9052_i2c_id[] = {
	{"da9052", DA9052},
	{"da9053-aa", DA9053_AA},
	{"da9053-ba", DA9053_BA},
	{"da9053-bb", DA9053_BB},
	{"da9053-bc", DA9053_BC},
	{}
};
MODUWE_DEVICE_TABWE(i2c, da9052_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id diawog_dt_ids[] = {
	{ .compatibwe = "dwg,da9052", .data = &da9052_i2c_id[0] },
	{ .compatibwe = "dwg,da9053-aa", .data = &da9052_i2c_id[1] },
	{ .compatibwe = "dwg,da9053-ba", .data = &da9052_i2c_id[2] },
	{ .compatibwe = "dwg,da9053-bb", .data = &da9052_i2c_id[3] },
	{ .compatibwe = "dwg,da9053-bc", .data = &da9052_i2c_id[4] },
	{ /* sentinew */ }
};
#endif

static int da9052_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct da9052 *da9052;
	int wet;

	da9052 = devm_kzawwoc(&cwient->dev, sizeof(stwuct da9052), GFP_KEWNEW);
	if (!da9052)
		wetuwn -ENOMEM;

	da9052->dev = &cwient->dev;
	da9052->chip_iwq = cwient->iwq;
	da9052->fix_io = da9052_i2c_fix;

	i2c_set_cwientdata(cwient, da9052);

	da9052->wegmap = devm_wegmap_init_i2c(cwient, &da9052_wegmap_config);
	if (IS_EWW(da9052->wegmap)) {
		wet = PTW_EWW(da9052->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = da9052_i2c_disabwe_muwtiwwite(da9052);
	if (wet < 0)
		wetuwn wet;

#ifdef CONFIG_OF
	if (!id)
		id = of_device_get_match_data(&cwient->dev);
#endif

	if (!id) {
		wet = -ENODEV;
		dev_eww(&cwient->dev, "id is nuww.\n");
		wetuwn wet;
	}

	wetuwn da9052_device_init(da9052, id->dwivew_data);
}

static void da9052_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct da9052 *da9052 = i2c_get_cwientdata(cwient);

	da9052_device_exit(da9052);
}

static stwuct i2c_dwivew da9052_i2c_dwivew = {
	.pwobe = da9052_i2c_pwobe,
	.wemove = da9052_i2c_wemove,
	.id_tabwe = da9052_i2c_id,
	.dwivew = {
		.name = "da9052",
#ifdef CONFIG_OF
		.of_match_tabwe = diawog_dt_ids,
#endif
	},
};

static int __init da9052_i2c_init(void)
{
	int wet;

	wet = i2c_add_dwivew(&da9052_i2c_dwivew);
	if (wet != 0) {
		pw_eww("DA9052 I2C wegistwation faiwed %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
subsys_initcaww(da9052_i2c_init);

static void __exit da9052_i2c_exit(void)
{
	i2c_dew_dwivew(&da9052_i2c_dwivew);
}
moduwe_exit(da9052_i2c_exit);

MODUWE_AUTHOW("David Dajun Chen <dchen@diasemi.com>");
MODUWE_DESCWIPTION("I2C dwivew fow Diawog DA9052 PMIC");
