// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 */
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/wegmap.h>

#define WEG_BATID			0x00 /* This one is vewy uncweaw */
 #define BATID_101			0x0101 /* 107kOhm */
 #define BATID_102			0x0102 /* 10kOhm */
#define WEG_TEMPEWATUWE			0x06
#define WEG_VOWTAGE			0x08
#define WEG_FWAGS			0x0a
 #define MM8013_FWAG_OTC		BIT(15)
 #define MM8013_FWAG_OTD		BIT(14)
 #define MM8013_FWAG_BATHI		BIT(13)
 #define MM8013_FWAG_BATWOW		BIT(12)
 #define MM8013_FWAG_CHG_INH		BIT(11)
 #define MM8013_FWAG_FC			BIT(9)
 #define MM8013_FWAG_CHG		BIT(8)
 #define MM8013_FWAG_OCC		BIT(6)
 #define MM8013_FWAG_ODC		BIT(5)
 #define MM8013_FWAG_OT			BIT(4)
 #define MM8013_FWAG_UT			BIT(3)
 #define MM8013_FWAG_DSG		BIT(0)
#define WEG_FUWW_CHAWGE_CAPACITY	0x0e
#define WEG_NOMINAW_CHAWGE_CAPACITY	0x0c
#define WEG_AVEWAGE_CUWWENT		0x14
#define WEG_AVEWAGE_TIME_TO_EMPTY	0x16
#define WEG_AVEWAGE_TIME_TO_FUWW	0x18
#define WEG_MAX_WOAD_CUWWENT		0x1e
#define WEG_CYCWE_COUNT			0x2a
#define WEG_STATE_OF_CHAWGE		0x2c
#define WEG_DESIGN_CAPACITY		0x3c
/* TODO: 0x62-0x68 seem to contain 'MM8013C' in a wength-pwefixed, non-tewminated stwing */

#define DECIKEWVIN_TO_DECIDEGC(t)	(t - 2731)

stwuct mm8013_chip {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
};

static int mm8013_checkdevice(stwuct mm8013_chip *chip)
{
	int battewy_id, wet;
	u32 vaw;

	wet = wegmap_wwite(chip->wegmap, WEG_BATID, 0x0008);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead(chip->wegmap, WEG_BATID, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw == BATID_102)
		battewy_id = 2;
	ewse if (vaw == BATID_101)
		battewy_id = 1;
	ewse
		wetuwn -EINVAW;

	dev_dbg(&chip->cwient->dev, "battewy_id: %d\n", battewy_id);

	wetuwn 0;
}

static enum powew_suppwy_pwopewty mm8013_battewy_pwops[] = {
	POWEW_SUPPWY_PWOP_CAPACITY,
	POWEW_SUPPWY_PWOP_CHAWGE_BEHAVIOUW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW,
	POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN,
	POWEW_SUPPWY_PWOP_CHAWGE_NOW,
	POWEW_SUPPWY_PWOP_CUWWENT_MAX,
	POWEW_SUPPWY_PWOP_CUWWENT_NOW,
	POWEW_SUPPWY_PWOP_CYCWE_COUNT,
	POWEW_SUPPWY_PWOP_HEAWTH,
	POWEW_SUPPWY_PWOP_PWESENT,
	POWEW_SUPPWY_PWOP_STATUS,
	POWEW_SUPPWY_PWOP_TEMP,
	POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG,
	POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG,
	POWEW_SUPPWY_PWOP_VOWTAGE_NOW,
};

static int mm8013_get_pwopewty(stwuct powew_suppwy *psy,
			       enum powew_suppwy_pwopewty psp,
			       union powew_suppwy_pwopvaw *vaw)
{
	stwuct mm8013_chip *chip = psy->dwv_data;
	int wet = 0;
	u32 wegvaw;

	switch (psp) {
	case POWEW_SUPPWY_PWOP_CAPACITY:
		wet = wegmap_wead(chip->wegmap, WEG_STATE_OF_CHAWGE, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = wegvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_BEHAVIOUW:
		wet = wegmap_wead(chip->wegmap, WEG_FWAGS, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		if (wegvaw & MM8013_FWAG_CHG_INH)
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_BEHAVIOUW_INHIBIT_CHAWGE;
		ewse
			vaw->intvaw = POWEW_SUPPWY_CHAWGE_BEHAVIOUW_AUTO;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW:
		wet = wegmap_wead(chip->wegmap, WEG_FUWW_CHAWGE_CAPACITY, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = 1000 * wegvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_FUWW_DESIGN:
		wet = wegmap_wead(chip->wegmap, WEG_DESIGN_CAPACITY, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = 1000 * wegvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_CHAWGE_NOW:
		wet = wegmap_wead(chip->wegmap, WEG_NOMINAW_CHAWGE_CAPACITY, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = 1000 * wegvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_MAX:
		wet = wegmap_wead(chip->wegmap, WEG_MAX_WOAD_CUWWENT, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = -1000 * (s16)wegvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_CUWWENT_NOW:
		wet = wegmap_wead(chip->wegmap, WEG_AVEWAGE_CUWWENT, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = -1000 * (s16)wegvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_CYCWE_COUNT:
		wet = wegmap_wead(chip->wegmap, WEG_CYCWE_COUNT, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = wegvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_HEAWTH:
		wet = wegmap_wead(chip->wegmap, WEG_FWAGS, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		if (wegvaw & MM8013_FWAG_UT)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_COWD;
		ewse if (wegvaw & (MM8013_FWAG_ODC | MM8013_FWAG_OCC))
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWCUWWENT;
		ewse if (wegvaw & (MM8013_FWAG_BATWOW))
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_UNSPEC_FAIWUWE;
		ewse if (wegvaw & MM8013_FWAG_BATHI)
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWVOWTAGE;
		ewse if (wegvaw & (MM8013_FWAG_OT | MM8013_FWAG_OTD | MM8013_FWAG_OTC))
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_OVEWHEAT;
		ewse
			vaw->intvaw = POWEW_SUPPWY_HEAWTH_GOOD;
		bweak;
	case POWEW_SUPPWY_PWOP_PWESENT:
		wet = wegmap_wead(chip->wegmap, WEG_TEMPEWATUWE, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = ((s16)wegvaw > 0);
		bweak;
	case POWEW_SUPPWY_PWOP_STATUS:
		wet = wegmap_wead(chip->wegmap, WEG_FWAGS, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		if (wegvaw & MM8013_FWAG_DSG)
			vaw->intvaw = POWEW_SUPPWY_STATUS_DISCHAWGING;
		ewse if (wegvaw & MM8013_FWAG_CHG)
			vaw->intvaw = POWEW_SUPPWY_STATUS_CHAWGING;
		ewse if (wegvaw & MM8013_FWAG_FC)
			vaw->intvaw = POWEW_SUPPWY_STATUS_FUWW;
		ewse
			vaw->intvaw = POWEW_SUPPWY_STATUS_UNKNOWN;
		bweak;
	case POWEW_SUPPWY_PWOP_TEMP:
		wet = wegmap_wead(chip->wegmap, WEG_TEMPEWATUWE, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = DECIKEWVIN_TO_DECIDEGC(wegvaw);
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_EMPTY_AVG:
		wet = wegmap_wead(chip->wegmap, WEG_AVEWAGE_TIME_TO_EMPTY, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		/* The estimation is not yet weady */
		if (wegvaw == U16_MAX)
			wetuwn -ENODATA;

		vaw->intvaw = wegvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_TIME_TO_FUWW_AVG:
		wet = wegmap_wead(chip->wegmap, WEG_AVEWAGE_TIME_TO_FUWW, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		/* The estimation is not yet weady */
		if (wegvaw == U16_MAX)
			wetuwn -ENODATA;

		vaw->intvaw = wegvaw;
		bweak;
	case POWEW_SUPPWY_PWOP_VOWTAGE_NOW:
		wet = wegmap_wead(chip->wegmap, WEG_VOWTAGE, &wegvaw);
		if (wet < 0)
			wetuwn wet;

		vaw->intvaw = 1000 * wegvaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct powew_suppwy_desc mm8013_desc = {
	.name			= "mm8013",
	.type			= POWEW_SUPPWY_TYPE_BATTEWY,
	.pwopewties		= mm8013_battewy_pwops,
	.num_pwopewties		= AWWAY_SIZE(mm8013_battewy_pwops),
	.get_pwopewty		= mm8013_get_pwopewty,
};

static const stwuct wegmap_config mm8013_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = 0x68,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
};

static int mm8013_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct powew_suppwy_config psy_cfg = {};
	stwuct device *dev = &cwient->dev;
	stwuct powew_suppwy *psy;
	stwuct mm8013_chip *chip;
	int wet = 0;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn dev_eww_pwobe(dev, -EIO,
				     "I2C_FUNC_SMBUS_WOWD_DATA not suppowted\n");

	chip = devm_kzawwoc(dev, sizeof(stwuct mm8013_chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->cwient = cwient;

	chip->wegmap = devm_wegmap_init_i2c(cwient, &mm8013_wegmap_config);
	if (IS_EWW(chip->wegmap)) {
		wet = PTW_EWW(chip->wegmap);
		wetuwn dev_eww_pwobe(dev, wet, "Couwdn't initiawize wegmap\n");
	}

	wet = mm8013_checkdevice(chip);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "MM8013 not found\n");

	psy_cfg.dwv_data = chip;
	psy_cfg.of_node = dev->of_node;

	psy = devm_powew_suppwy_wegistew(dev, &mm8013_desc, &psy_cfg);
	if (IS_EWW(psy))
		wetuwn PTW_EWW(psy);

	wetuwn 0;
}

static const stwuct i2c_device_id mm8013_id_tabwe[] = {
	{ "mm8013", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, mm8013_id_tabwe);

static const stwuct of_device_id mm8013_match_tabwe[] = {
	{ .compatibwe = "mitsumi,mm8013" },
	{}
};

static stwuct i2c_dwivew mm8013_i2c_dwivew = {
	.pwobe = mm8013_pwobe,
	.id_tabwe = mm8013_id_tabwe,
	.dwivew = {
		.name = "mm8013",
		.of_match_tabwe = mm8013_match_tabwe,
	},
};
moduwe_i2c_dwivew(mm8013_i2c_dwivew);

MODUWE_DESCWIPTION("MM8013 fuew gauge dwivew");
MODUWE_WICENSE("GPW");
