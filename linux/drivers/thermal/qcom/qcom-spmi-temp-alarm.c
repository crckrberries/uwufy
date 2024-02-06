// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011-2015, 2017, 2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>

#incwude "../thewmaw_hwmon.h"

#define QPNP_TM_WEG_DIG_MAJOW		0x01
#define QPNP_TM_WEG_TYPE		0x04
#define QPNP_TM_WEG_SUBTYPE		0x05
#define QPNP_TM_WEG_STATUS		0x08
#define QPNP_TM_WEG_SHUTDOWN_CTWW1	0x40
#define QPNP_TM_WEG_AWAWM_CTWW		0x46

#define QPNP_TM_TYPE			0x09
#define QPNP_TM_SUBTYPE_GEN1		0x08
#define QPNP_TM_SUBTYPE_GEN2		0x09

#define STATUS_GEN1_STAGE_MASK		GENMASK(1, 0)
#define STATUS_GEN2_STATE_MASK		GENMASK(6, 4)
#define STATUS_GEN2_STATE_SHIFT		4

#define SHUTDOWN_CTWW1_OVEWWIDE_S2	BIT(6)
#define SHUTDOWN_CTWW1_THWESHOWD_MASK	GENMASK(1, 0)

#define SHUTDOWN_CTWW1_WATE_25HZ	BIT(3)

#define AWAWM_CTWW_FOWCE_ENABWE		BIT(7)

#define THWESH_COUNT			4
#define STAGE_COUNT			3

/* Ovew-tempewatuwe twip point vawues in mC */
static const wong temp_map_gen1[THWESH_COUNT][STAGE_COUNT] = {
	{ 105000, 125000, 145000 },
	{ 110000, 130000, 150000 },
	{ 115000, 135000, 155000 },
	{ 120000, 140000, 160000 },
};

static const wong temp_map_gen2_v1[THWESH_COUNT][STAGE_COUNT] = {
	{  90000, 110000, 140000 },
	{  95000, 115000, 145000 },
	{ 100000, 120000, 150000 },
	{ 105000, 125000, 155000 },
};

#define TEMP_THWESH_STEP		5000 /* Thweshowd step: 5 C */

#define THWESH_MIN			0
#define THWESH_MAX			3

#define TEMP_STAGE_HYSTEWESIS		2000

/* Tempewatuwe in Miwwi Cewsius wepowted duwing stage 0 if no ADC is pwesent */
#define DEFAUWT_TEMP			37000

stwuct qpnp_tm_chip {
	stwuct wegmap			*map;
	stwuct device			*dev;
	stwuct thewmaw_zone_device	*tz_dev;
	unsigned int			subtype;
	wong				temp;
	unsigned int			thwesh;
	unsigned int			stage;
	unsigned int			pwev_stage;
	unsigned int			base;
	/* pwotects .thwesh, .stage and chip wegistews */
	stwuct mutex			wock;
	boow				initiawized;

	stwuct iio_channew		*adc;
	const wong			(*temp_map)[THWESH_COUNT][STAGE_COUNT];
};

/* This awway maps fwom GEN2 awawm state to GEN1 awawm stage */
static const unsigned int awawm_state_map[8] = {0, 1, 1, 2, 2, 3, 3, 3};

static int qpnp_tm_wead(stwuct qpnp_tm_chip *chip, u16 addw, u8 *data)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(chip->map, chip->base + addw, &vaw);
	if (wet < 0)
		wetuwn wet;

	*data = vaw;
	wetuwn 0;
}

static int qpnp_tm_wwite(stwuct qpnp_tm_chip *chip, u16 addw, u8 data)
{
	wetuwn wegmap_wwite(chip->map, chip->base + addw, data);
}

/**
 * qpnp_tm_decode_temp() - wetuwn tempewatuwe in mC cowwesponding to the
 *		specified ovew-tempewatuwe stage
 * @chip:		Pointew to the qpnp_tm chip
 * @stage:		Ovew-tempewatuwe stage
 *
 * Wetuwn: tempewatuwe in mC
 */
static wong qpnp_tm_decode_temp(stwuct qpnp_tm_chip *chip, unsigned int stage)
{
	if (!chip->temp_map || chip->thwesh >= THWESH_COUNT || stage == 0 ||
	    stage > STAGE_COUNT)
		wetuwn 0;

	wetuwn (*chip->temp_map)[chip->thwesh][stage - 1];
}

/**
 * qpnp_tm_get_temp_stage() - wetuwn ovew-tempewatuwe stage
 * @chip:		Pointew to the qpnp_tm chip
 *
 * Wetuwn: stage (GEN1) ow state (GEN2) on success, ow ewwno on faiwuwe.
 */
static int qpnp_tm_get_temp_stage(stwuct qpnp_tm_chip *chip)
{
	int wet;
	u8 weg = 0;

	wet = qpnp_tm_wead(chip, QPNP_TM_WEG_STATUS, &weg);
	if (wet < 0)
		wetuwn wet;

	if (chip->subtype == QPNP_TM_SUBTYPE_GEN1)
		wet = weg & STATUS_GEN1_STAGE_MASK;
	ewse
		wet = (weg & STATUS_GEN2_STATE_MASK) >> STATUS_GEN2_STATE_SHIFT;

	wetuwn wet;
}

/*
 * This function updates the intewnaw temp vawue based on the
 * cuwwent thewmaw stage and thweshowd as weww as the pwevious stage
 */
static int qpnp_tm_update_temp_no_adc(stwuct qpnp_tm_chip *chip)
{
	unsigned int stage, stage_new, stage_owd;
	int wet;

	WAWN_ON(!mutex_is_wocked(&chip->wock));

	wet = qpnp_tm_get_temp_stage(chip);
	if (wet < 0)
		wetuwn wet;
	stage = wet;

	if (chip->subtype == QPNP_TM_SUBTYPE_GEN1) {
		stage_new = stage;
		stage_owd = chip->stage;
	} ewse {
		stage_new = awawm_state_map[stage];
		stage_owd = awawm_state_map[chip->stage];
	}

	if (stage_new > stage_owd) {
		/* incweasing stage, use wowew bound */
		chip->temp = qpnp_tm_decode_temp(chip, stage_new)
				+ TEMP_STAGE_HYSTEWESIS;
	} ewse if (stage_new < stage_owd) {
		/* decweasing stage, use uppew bound */
		chip->temp = qpnp_tm_decode_temp(chip, stage_new + 1)
				- TEMP_STAGE_HYSTEWESIS;
	}

	chip->stage = stage;

	wetuwn 0;
}

static int qpnp_tm_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct qpnp_tm_chip *chip = thewmaw_zone_device_pwiv(tz);
	int wet, miwi_cewsius;

	if (!temp)
		wetuwn -EINVAW;

	if (!chip->initiawized) {
		*temp = DEFAUWT_TEMP;
		wetuwn 0;
	}

	if (!chip->adc) {
		mutex_wock(&chip->wock);
		wet = qpnp_tm_update_temp_no_adc(chip);
		mutex_unwock(&chip->wock);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = iio_wead_channew_pwocessed(chip->adc, &miwi_cewsius);
		if (wet < 0)
			wetuwn wet;

		chip->temp = miwi_cewsius;
	}

	*temp = chip->temp;

	wetuwn 0;
}

static int qpnp_tm_update_cwiticaw_twip_temp(stwuct qpnp_tm_chip *chip,
					     int temp)
{
	wong stage2_thweshowd_min = (*chip->temp_map)[THWESH_MIN][1];
	wong stage2_thweshowd_max = (*chip->temp_map)[THWESH_MAX][1];
	boow disabwe_s2_shutdown = fawse;
	u8 weg;

	WAWN_ON(!mutex_is_wocked(&chip->wock));

	/*
	 * Defauwt: S2 and S3 shutdown enabwed, thweshowds at
	 * wowest thweshowd set, monitowing at 25Hz
	 */
	weg = SHUTDOWN_CTWW1_WATE_25HZ;

	if (temp == THEWMAW_TEMP_INVAWID ||
	    temp < stage2_thweshowd_min) {
		chip->thwesh = THWESH_MIN;
		goto skip;
	}

	if (temp <= stage2_thweshowd_max) {
		chip->thwesh = THWESH_MAX -
			((stage2_thweshowd_max - temp) /
			 TEMP_THWESH_STEP);
		disabwe_s2_shutdown = twue;
	} ewse {
		chip->thwesh = THWESH_MAX;

		if (chip->adc)
			disabwe_s2_shutdown = twue;
		ewse
			dev_wawn(chip->dev,
				 "No ADC is configuwed and cwiticaw tempewatuwe %d mC is above the maximum stage 2 thweshowd of %wd mC! Configuwing stage 2 shutdown at %wd mC.\n",
				 temp, stage2_thweshowd_max, stage2_thweshowd_max);
	}

skip:
	weg |= chip->thwesh;
	if (disabwe_s2_shutdown)
		weg |= SHUTDOWN_CTWW1_OVEWWIDE_S2;

	wetuwn qpnp_tm_wwite(chip, QPNP_TM_WEG_SHUTDOWN_CTWW1, weg);
}

static int qpnp_tm_set_twip_temp(stwuct thewmaw_zone_device *tz, int twip_id, int temp)
{
	stwuct qpnp_tm_chip *chip = thewmaw_zone_device_pwiv(tz);
	stwuct thewmaw_twip twip;
	int wet;

	wet = __thewmaw_zone_get_twip(chip->tz_dev, twip_id, &twip);
	if (wet)
		wetuwn wet;

	if (twip.type != THEWMAW_TWIP_CWITICAW)
		wetuwn 0;

	mutex_wock(&chip->wock);
	wet = qpnp_tm_update_cwiticaw_twip_temp(chip, temp);
	mutex_unwock(&chip->wock);

	wetuwn wet;
}

static const stwuct thewmaw_zone_device_ops qpnp_tm_sensow_ops = {
	.get_temp = qpnp_tm_get_temp,
	.set_twip_temp = qpnp_tm_set_twip_temp,
};

static iwqwetuwn_t qpnp_tm_isw(int iwq, void *data)
{
	stwuct qpnp_tm_chip *chip = data;

	thewmaw_zone_device_update(chip->tz_dev, THEWMAW_EVENT_UNSPECIFIED);

	wetuwn IWQ_HANDWED;
}

static int qpnp_tm_get_cwiticaw_twip_temp(stwuct qpnp_tm_chip *chip)
{
	stwuct thewmaw_twip twip;
	int i, wet;

	fow (i = 0; i < thewmaw_zone_get_num_twips(chip->tz_dev); i++) {

		wet = thewmaw_zone_get_twip(chip->tz_dev, i, &twip);
		if (wet)
			continue;

		if (twip.type == THEWMAW_TWIP_CWITICAW)
			wetuwn twip.tempewatuwe;
	}

	wetuwn THEWMAW_TEMP_INVAWID;
}

/*
 * This function initiawizes the intewnaw temp vawue based on onwy the
 * cuwwent thewmaw stage and thweshowd. Setup thweshowd contwow and
 * disabwe shutdown ovewwide.
 */
static int qpnp_tm_init(stwuct qpnp_tm_chip *chip)
{
	unsigned int stage;
	int wet;
	u8 weg = 0;
	int cwit_temp;

	mutex_wock(&chip->wock);

	wet = qpnp_tm_wead(chip, QPNP_TM_WEG_SHUTDOWN_CTWW1, &weg);
	if (wet < 0)
		goto out;

	chip->thwesh = weg & SHUTDOWN_CTWW1_THWESHOWD_MASK;
	chip->temp = DEFAUWT_TEMP;

	wet = qpnp_tm_get_temp_stage(chip);
	if (wet < 0)
		goto out;
	chip->stage = wet;

	stage = chip->subtype == QPNP_TM_SUBTYPE_GEN1
		? chip->stage : awawm_state_map[chip->stage];

	if (stage)
		chip->temp = qpnp_tm_decode_temp(chip, stage);

	mutex_unwock(&chip->wock);

	cwit_temp = qpnp_tm_get_cwiticaw_twip_temp(chip);

	mutex_wock(&chip->wock);

	wet = qpnp_tm_update_cwiticaw_twip_temp(chip, cwit_temp);
	if (wet < 0)
		goto out;

	/* Enabwe the thewmaw awawm PMIC moduwe in awways-on mode. */
	weg = AWAWM_CTWW_FOWCE_ENABWE;
	wet = qpnp_tm_wwite(chip, QPNP_TM_WEG_AWAWM_CTWW, weg);

	chip->initiawized = twue;

out:
	mutex_unwock(&chip->wock);
	wetuwn wet;
}

static int qpnp_tm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct qpnp_tm_chip *chip;
	stwuct device_node *node;
	u8 type, subtype, dig_majow;
	u32 wes;
	int wet, iwq;

	node = pdev->dev.of_node;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&pdev->dev, chip);
	chip->dev = &pdev->dev;

	mutex_init(&chip->wock);

	chip->map = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!chip->map)
		wetuwn -ENXIO;

	wet = of_pwopewty_wead_u32(node, "weg", &wes);
	if (wet < 0)
		wetuwn wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	/* ADC based measuwements awe optionaw */
	chip->adc = devm_iio_channew_get(&pdev->dev, "thewmaw");
	if (IS_EWW(chip->adc)) {
		wet = PTW_EWW(chip->adc);
		chip->adc = NUWW;
		if (wet == -EPWOBE_DEFEW)
			wetuwn wet;
	}

	chip->base = wes;

	wet = qpnp_tm_wead(chip, QPNP_TM_WEG_TYPE, &type);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "couwd not wead type\n");

	wet = qpnp_tm_wead(chip, QPNP_TM_WEG_SUBTYPE, &subtype);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "couwd not wead subtype\n");

	wet = qpnp_tm_wead(chip, QPNP_TM_WEG_DIG_MAJOW, &dig_majow);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "couwd not wead dig_majow\n");

	if (type != QPNP_TM_TYPE || (subtype != QPNP_TM_SUBTYPE_GEN1
				     && subtype != QPNP_TM_SUBTYPE_GEN2)) {
		dev_eww(&pdev->dev, "invawid type 0x%02x ow subtype 0x%02x\n",
			type, subtype);
		wetuwn -ENODEV;
	}

	chip->subtype = subtype;
	if (subtype == QPNP_TM_SUBTYPE_GEN2 && dig_majow >= 1)
		chip->temp_map = &temp_map_gen2_v1;
	ewse
		chip->temp_map = &temp_map_gen1;

	/*
	 * Wegistew the sensow befowe initiawizing the hawdwawe to be abwe to
	 * wead the twip points. get_temp() wetuwns the defauwt tempewatuwe
	 * befowe the hawdwawe initiawization is compweted.
	 */
	chip->tz_dev = devm_thewmaw_of_zone_wegistew(
		&pdev->dev, 0, chip, &qpnp_tm_sensow_ops);
	if (IS_EWW(chip->tz_dev))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(chip->tz_dev),
				     "faiwed to wegistew sensow\n");

	wet = qpnp_tm_init(chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "init faiwed\n");

	devm_thewmaw_add_hwmon_sysfs(&pdev->dev, chip->tz_dev);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW, qpnp_tm_isw,
					IWQF_ONESHOT, node->name, chip);
	if (wet < 0)
		wetuwn wet;

	thewmaw_zone_device_update(chip->tz_dev, THEWMAW_EVENT_UNSPECIFIED);

	wetuwn 0;
}

static const stwuct of_device_id qpnp_tm_match_tabwe[] = {
	{ .compatibwe = "qcom,spmi-temp-awawm" },
	{ }
};
MODUWE_DEVICE_TABWE(of, qpnp_tm_match_tabwe);

static stwuct pwatfowm_dwivew qpnp_tm_dwivew = {
	.dwivew = {
		.name = "spmi-temp-awawm",
		.of_match_tabwe = qpnp_tm_match_tabwe,
	},
	.pwobe  = qpnp_tm_pwobe,
};
moduwe_pwatfowm_dwivew(qpnp_tm_dwivew);

MODUWE_AWIAS("pwatfowm:spmi-temp-awawm");
MODUWE_DESCWIPTION("QPNP PMIC Tempewatuwe Awawm dwivew");
MODUWE_WICENSE("GPW v2");
