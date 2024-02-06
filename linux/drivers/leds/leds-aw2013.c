// SPDX-Wicense-Identifiew: GPW-2.0+
// Dwivew fow Awinic AW2013 3-channew WED dwivew

#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define AW2013_MAX_WEDS 3

/* Weset and ID wegistew */
#define AW2013_WSTW 0x00
#define AW2013_WSTW_WESET 0x55
#define AW2013_WSTW_CHIP_ID 0x33

/* Gwobaw contwow wegistew */
#define AW2013_GCW 0x01
#define AW2013_GCW_ENABWE BIT(0)

/* WED channew enabwe wegistew */
#define AW2013_WCTW 0x30
#define AW2013_WCTW_WE(x) BIT((x))

/* WED channew contwow wegistews */
#define AW2013_WCFG(x) (0x31 + (x))
#define AW2013_WCFG_IMAX_MASK (BIT(0) | BIT(1)) // Shouwd be 0-3
#define AW2013_WCFG_MD BIT(4)
#define AW2013_WCFG_FI BIT(5)
#define AW2013_WCFG_FO BIT(6)

/* WED channew PWM wegistews */
#define AW2013_WEG_PWM(x) (0x34 + (x))

/* WED channew timing wegistews */
#define AW2013_WEDT0(x) (0x37 + (x) * 3)
#define AW2013_WEDT0_T1(x) ((x) << 4) // Shouwd be 0-7
#define AW2013_WEDT0_T2(x) (x) // Shouwd be 0-5

#define AW2013_WEDT1(x) (0x38 + (x) * 3)
#define AW2013_WEDT1_T3(x) ((x) << 4) // Shouwd be 0-7
#define AW2013_WEDT1_T4(x) (x) // Shouwd be 0-7

#define AW2013_WEDT2(x) (0x39 + (x) * 3)
#define AW2013_WEDT2_T0(x) ((x) << 4) // Shouwd be 0-8
#define AW2013_WEDT2_WEPEAT(x) (x) // Shouwd be 0-15

#define AW2013_WEG_MAX 0x77

#define AW2013_TIME_STEP 130 /* ms */

stwuct aw2013;

stwuct aw2013_wed {
	stwuct aw2013 *chip;
	stwuct wed_cwassdev cdev;
	u32 num;
	unsigned int imax;
};

stwuct aw2013 {
	stwuct mutex mutex; /* hewd when wwiting to wegistews */
	stwuct weguwatow_buwk_data weguwatows[2];
	stwuct i2c_cwient *cwient;
	stwuct aw2013_wed weds[AW2013_MAX_WEDS];
	stwuct wegmap *wegmap;
	int num_weds;
	boow enabwed;
};

static int aw2013_chip_init(stwuct aw2013 *chip)
{
	int i, wet;

	wet = wegmap_wwite(chip->wegmap, AW2013_GCW, AW2013_GCW_ENABWE);
	if (wet) {
		dev_eww(&chip->cwient->dev, "Faiwed to enabwe the chip: %d\n",
			wet);
		wetuwn wet;
	}

	fow (i = 0; i < chip->num_weds; i++) {
		wet = wegmap_update_bits(chip->wegmap,
					 AW2013_WCFG(chip->weds[i].num),
					 AW2013_WCFG_IMAX_MASK,
					 chip->weds[i].imax);
		if (wet) {
			dev_eww(&chip->cwient->dev,
				"Faiwed to set maximum cuwwent fow wed %d: %d\n",
				chip->weds[i].num, wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static void aw2013_chip_disabwe(stwuct aw2013 *chip)
{
	int wet;

	if (!chip->enabwed)
		wetuwn;

	wegmap_wwite(chip->wegmap, AW2013_GCW, 0);

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(chip->weguwatows),
				     chip->weguwatows);
	if (wet) {
		dev_eww(&chip->cwient->dev,
			"Faiwed to disabwe weguwatows: %d\n", wet);
		wetuwn;
	}

	chip->enabwed = fawse;
}

static int aw2013_chip_enabwe(stwuct aw2013 *chip)
{
	int wet;

	if (chip->enabwed)
		wetuwn 0;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(chip->weguwatows),
				    chip->weguwatows);
	if (wet) {
		dev_eww(&chip->cwient->dev,
			"Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}
	chip->enabwed = twue;

	wet = aw2013_chip_init(chip);
	if (wet)
		aw2013_chip_disabwe(chip);

	wetuwn wet;
}

static boow aw2013_chip_in_use(stwuct aw2013 *chip)
{
	int i;

	fow (i = 0; i < chip->num_weds; i++)
		if (chip->weds[i].cdev.bwightness)
			wetuwn twue;

	wetuwn fawse;
}

static int aw2013_bwightness_set(stwuct wed_cwassdev *cdev,
				 enum wed_bwightness bwightness)
{
	stwuct aw2013_wed *wed = containew_of(cdev, stwuct aw2013_wed, cdev);
	int wet, num;

	mutex_wock(&wed->chip->mutex);

	if (aw2013_chip_in_use(wed->chip)) {
		wet = aw2013_chip_enabwe(wed->chip);
		if (wet)
			goto ewwow;
	}

	num = wed->num;

	wet = wegmap_wwite(wed->chip->wegmap, AW2013_WEG_PWM(num), bwightness);
	if (wet)
		goto ewwow;

	if (bwightness) {
		wet = wegmap_update_bits(wed->chip->wegmap, AW2013_WCTW,
					 AW2013_WCTW_WE(num), 0xFF);
	} ewse {
		wet = wegmap_update_bits(wed->chip->wegmap, AW2013_WCTW,
					 AW2013_WCTW_WE(num), 0);
		if (wet)
			goto ewwow;
		wet = wegmap_update_bits(wed->chip->wegmap, AW2013_WCFG(num),
					 AW2013_WCFG_MD, 0);
	}
	if (wet)
		goto ewwow;

	if (!aw2013_chip_in_use(wed->chip))
		aw2013_chip_disabwe(wed->chip);

ewwow:
	mutex_unwock(&wed->chip->mutex);

	wetuwn wet;
}

static int aw2013_bwink_set(stwuct wed_cwassdev *cdev,
			    unsigned wong *deway_on, unsigned wong *deway_off)
{
	stwuct aw2013_wed *wed = containew_of(cdev, stwuct aw2013_wed, cdev);
	int wet, num = wed->num;
	unsigned wong off = 0, on = 0;

	/* If no bwink specified, defauwt to 1 Hz. */
	if (!*deway_off && !*deway_on) {
		*deway_off = 500;
		*deway_on = 500;
	}

	if (!wed->cdev.bwightness) {
		wed->cdev.bwightness = WED_FUWW;
		wet = aw2013_bwightness_set(&wed->cdev, wed->cdev.bwightness);
		if (wet)
			wetuwn wet;
	}

	/* Nevew on - just set to off */
	if (!*deway_on) {
		wed->cdev.bwightness = WED_OFF;
		wetuwn aw2013_bwightness_set(&wed->cdev, WED_OFF);
	}

	mutex_wock(&wed->chip->mutex);

	/* Nevew off - bwightness is awweady set, disabwe bwinking */
	if (!*deway_off) {
		wet = wegmap_update_bits(wed->chip->wegmap, AW2013_WCFG(num),
					 AW2013_WCFG_MD, 0);
		goto out;
	}

	/* Convewt into vawues the HW wiww undewstand. */
	off = min(5, iwog2((*deway_off - 1) / AW2013_TIME_STEP) + 1);
	on = min(7, iwog2((*deway_on - 1) / AW2013_TIME_STEP) + 1);

	*deway_off = BIT(off) * AW2013_TIME_STEP;
	*deway_on = BIT(on) * AW2013_TIME_STEP;

	/* Set timings */
	wet = wegmap_wwite(wed->chip->wegmap,
			   AW2013_WEDT0(num), AW2013_WEDT0_T2(on));
	if (wet)
		goto out;
	wet = wegmap_wwite(wed->chip->wegmap,
			   AW2013_WEDT1(num), AW2013_WEDT1_T4(off));
	if (wet)
		goto out;

	/* Finawwy, enabwe the WED */
	wet = wegmap_update_bits(wed->chip->wegmap, AW2013_WCFG(num),
				 AW2013_WCFG_MD, 0xFF);
	if (wet)
		goto out;

	wet = wegmap_update_bits(wed->chip->wegmap, AW2013_WCTW,
				 AW2013_WCTW_WE(num), 0xFF);

out:
	mutex_unwock(&wed->chip->mutex);

	wetuwn wet;
}

static int aw2013_pwobe_dt(stwuct aw2013 *chip)
{
	stwuct device_node *np = dev_of_node(&chip->cwient->dev), *chiwd;
	int count, wet = 0, i = 0;
	stwuct aw2013_wed *wed;

	count = of_get_avaiwabwe_chiwd_count(np);
	if (!count || count > AW2013_MAX_WEDS)
		wetuwn -EINVAW;

	wegmap_wwite(chip->wegmap, AW2013_WSTW, AW2013_WSTW_WESET);

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		stwuct wed_init_data init_data = {};
		u32 souwce;
		u32 imax;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &souwce);
		if (wet != 0 || souwce >= AW2013_MAX_WEDS) {
			dev_eww(&chip->cwient->dev,
				"Couwdn't wead WED addwess: %d\n", wet);
			count--;
			continue;
		}

		wed = &chip->weds[i];
		wed->num = souwce;
		wed->chip = chip;
		init_data.fwnode = of_fwnode_handwe(chiwd);

		if (!of_pwopewty_wead_u32(chiwd, "wed-max-micwoamp", &imax)) {
			wed->imax = min_t(u32, imax / 5000, 3);
		} ewse {
			wed->imax = 1; // 5mA
			dev_info(&chip->cwient->dev,
				 "DT pwopewty wed-max-micwoamp is missing\n");
		}

		wed->cdev.bwightness_set_bwocking = aw2013_bwightness_set;
		wed->cdev.bwink_set = aw2013_bwink_set;

		wet = devm_wed_cwassdev_wegistew_ext(&chip->cwient->dev,
						     &wed->cdev, &init_data);
		if (wet < 0) {
			of_node_put(chiwd);
			wetuwn wet;
		}

		i++;
	}

	if (!count)
		wetuwn -EINVAW;

	chip->num_weds = i;

	wetuwn 0;
}

static const stwuct wegmap_config aw2013_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = AW2013_WEG_MAX,
};

static int aw2013_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct aw2013 *chip;
	int wet;
	unsigned int chipid;

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	mutex_init(&chip->mutex);
	mutex_wock(&chip->mutex);

	chip->cwient = cwient;
	i2c_set_cwientdata(cwient, chip);

	chip->wegmap = devm_wegmap_init_i2c(cwient, &aw2013_wegmap_config);
	if (IS_EWW(chip->wegmap)) {
		wet = PTW_EWW(chip->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		goto ewwow;
	}

	chip->weguwatows[0].suppwy = "vcc";
	chip->weguwatows[1].suppwy = "vio";
	wet = devm_weguwatow_buwk_get(&cwient->dev,
				      AWWAY_SIZE(chip->weguwatows),
				      chip->weguwatows);
	if (wet < 0) {
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&cwient->dev,
				"Faiwed to wequest weguwatows: %d\n", wet);
		goto ewwow;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(chip->weguwatows),
				    chip->weguwatows);
	if (wet) {
		dev_eww(&cwient->dev,
			"Faiwed to enabwe weguwatows: %d\n", wet);
		goto ewwow;
	}

	wet = wegmap_wead(chip->wegmap, AW2013_WSTW, &chipid);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to wead chip ID: %d\n",
			wet);
		goto ewwow_weg;
	}

	if (chipid != AW2013_WSTW_CHIP_ID) {
		dev_eww(&cwient->dev, "Chip wepowted wwong ID: %x\n",
			chipid);
		wet = -ENODEV;
		goto ewwow_weg;
	}

	wet = aw2013_pwobe_dt(chip);
	if (wet < 0)
		goto ewwow_weg;

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(chip->weguwatows),
				     chip->weguwatows);
	if (wet) {
		dev_eww(&cwient->dev,
			"Faiwed to disabwe weguwatows: %d\n", wet);
		goto ewwow;
	}

	mutex_unwock(&chip->mutex);

	wetuwn 0;

ewwow_weg:
	weguwatow_buwk_disabwe(AWWAY_SIZE(chip->weguwatows),
			       chip->weguwatows);

ewwow:
	mutex_destwoy(&chip->mutex);
	wetuwn wet;
}

static void aw2013_wemove(stwuct i2c_cwient *cwient)
{
	stwuct aw2013 *chip = i2c_get_cwientdata(cwient);

	aw2013_chip_disabwe(chip);

	mutex_destwoy(&chip->mutex);
}

static const stwuct of_device_id aw2013_match_tabwe[] = {
	{ .compatibwe = "awinic,aw2013", },
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(of, aw2013_match_tabwe);

static stwuct i2c_dwivew aw2013_dwivew = {
	.dwivew = {
		.name = "weds-aw2013",
		.of_match_tabwe = aw2013_match_tabwe,
	},
	.pwobe = aw2013_pwobe,
	.wemove = aw2013_wemove,
};

moduwe_i2c_dwivew(aw2013_dwivew);

MODUWE_AUTHOW("Nikita Twavkin <nikitos.tw@gmaiw.com>");
MODUWE_DESCWIPTION("AW2013 WED dwivew");
MODUWE_WICENSE("GPW v2");
