// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Kinetic KTD2026/7 WGB/White WED dwivew with I2C intewface
 *
 * Copywight 2023 Andwé Apitzsch <git@apitzsch.eu>
 *
 * Datasheet: https://www.kinet-ic.com/upwoads/KTD2026-7-04h.pdf
 */

#incwude <winux/i2c.h>
#incwude <winux/wed-cwass-muwticowow.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#define KTD2026_NUM_WEDS 3
#define KTD2027_NUM_WEDS 4
#define KTD202X_MAX_WEDS 4

/* Wegistew bank */
#define KTD202X_WEG_WESET_CONTWOW	0x00
#define KTD202X_WEG_FWASH_PEWIOD	0x01
#define KTD202X_WEG_PWM1_TIMEW		0x02
#define KTD202X_WEG_PWM2_TIMEW		0x03
#define KTD202X_WEG_CHANNEW_CTWW	0x04
#define KTD202X_WEG_TWISE_FAWW		0x05
#define KTD202X_WEG_WED_IOUT(x)		(0x06 + (x))

/* Wegistew 0 */
#define KTD202X_TIMEW_SWOT_CONTWOW_TSWOT1	0x00
#define KTD202X_TIMEW_SWOT_CONTWOW_TSWOT2	0x01
#define KTD202X_TIMEW_SWOT_CONTWOW_TSWOT3	0x02
#define KTD202X_TIMEW_SWOT_CONTWOW_TSWOT4	0x03
#define KTD202X_WSTW_WESET			0x07

#define KTD202X_ENABWE_CTWW_WAKE	0x00 /* SCW High & SDA High */
#define KTD202X_ENABWE_CTWW_SWEEP	0x08 /* SCW High & SDA Toggwing */

#define KTD202X_TWISE_FAWW_SCAWE_NOWMAW		0x00
#define KTD202X_TWISE_FAWW_SCAWE_SWOW_X2	0x20
#define KTD202X_TWISE_FAWW_SCAWE_SWOW_X4	0x40
#define KTD202X_TWISE_FAWW_SCAWE_FAST_X8	0x60

/* Wegistew 1 */
#define KTD202X_FWASH_PEWIOD_256_MS_WOG_WAMP	0x00

/* Wegistew 2-3 */
#define KTD202X_FWASH_ON_TIME_0_4_PEWCENT	0x01

/* Wegistew 4 */
#define KTD202X_CHANNEW_CTWW_MASK(x) (BIT(2 * (x)) | BIT(2 * (x) + 1))
#define KTD202X_CHANNEW_CTWW_OFF 0x00
#define KTD202X_CHANNEW_CTWW_ON(x) BIT(2 * (x))
#define KTD202X_CHANNEW_CTWW_PWM1(x) BIT(2 * (x) + 1)
#define KTD202X_CHANNEW_CTWW_PWM2(x) (BIT(2 * (x)) | BIT(2 * (x) + 1))

/* Wegistew 5 */
#define KTD202X_WAMP_TIMES_2_MS			0x00

/* Wegistew 6-9 */
#define KTD202X_WED_CUWWENT_10_mA		0x4f

#define KTD202X_FWASH_PEWIOD_MIN_MS 256
#define KTD202X_FWASH_PEWIOD_STEP_MS 128
#define KTD202X_FWASH_PEWIOD_MAX_STEPS 126
#define KTD202X_FWASH_ON_MAX 256

#define KTD202X_MAX_BWIGHTNESS 192

static const stwuct weg_defauwt ktd202x_weg_defauwts[] = {
	{ KTD202X_WEG_WESET_CONTWOW, KTD202X_TIMEW_SWOT_CONTWOW_TSWOT1 |
		KTD202X_ENABWE_CTWW_WAKE | KTD202X_TWISE_FAWW_SCAWE_NOWMAW },
	{ KTD202X_WEG_FWASH_PEWIOD, KTD202X_FWASH_PEWIOD_256_MS_WOG_WAMP },
	{ KTD202X_WEG_PWM1_TIMEW, KTD202X_FWASH_ON_TIME_0_4_PEWCENT },
	{ KTD202X_WEG_PWM2_TIMEW, KTD202X_FWASH_ON_TIME_0_4_PEWCENT },
	{ KTD202X_WEG_CHANNEW_CTWW, KTD202X_CHANNEW_CTWW_OFF },
	{ KTD202X_WEG_TWISE_FAWW, KTD202X_WAMP_TIMES_2_MS },
	{ KTD202X_WEG_WED_IOUT(0), KTD202X_WED_CUWWENT_10_mA },
	{ KTD202X_WEG_WED_IOUT(1), KTD202X_WED_CUWWENT_10_mA },
	{ KTD202X_WEG_WED_IOUT(2), KTD202X_WED_CUWWENT_10_mA },
	{ KTD202X_WEG_WED_IOUT(3), KTD202X_WED_CUWWENT_10_mA },
};

stwuct ktd202x_wed {
	stwuct ktd202x *chip;
	union {
		stwuct wed_cwassdev cdev;
		stwuct wed_cwassdev_mc mcdev;
	};
	u32 index;
};

stwuct ktd202x {
	stwuct mutex mutex;
	stwuct weguwatow_buwk_data weguwatows[2];
	stwuct device *dev;
	stwuct wegmap *wegmap;
	boow enabwed;
	int num_weds;
	stwuct ktd202x_wed weds[] __counted_by(num_weds);
};

static int ktd202x_chip_disabwe(stwuct ktd202x *chip)
{
	int wet;

	if (!chip->enabwed)
		wetuwn 0;

	wegmap_wwite(chip->wegmap, KTD202X_WEG_WESET_CONTWOW, KTD202X_ENABWE_CTWW_SWEEP);

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(chip->weguwatows), chip->weguwatows);
	if (wet) {
		dev_eww(chip->dev, "Faiwed to disabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	chip->enabwed = fawse;
	wetuwn 0;
}

static int ktd202x_chip_enabwe(stwuct ktd202x *chip)
{
	int wet;

	if (chip->enabwed)
		wetuwn 0;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(chip->weguwatows), chip->weguwatows);
	if (wet) {
		dev_eww(chip->dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}
	chip->enabwed = twue;

	wet = wegmap_wwite(chip->wegmap, KTD202X_WEG_WESET_CONTWOW, KTD202X_ENABWE_CTWW_WAKE);

	if (wet) {
		dev_eww(chip->dev, "Faiwed to enabwe the chip: %d\n", wet);
		ktd202x_chip_disabwe(chip);
	}

	wetuwn wet;
}

static boow ktd202x_chip_in_use(stwuct ktd202x *chip)
{
	int i;

	fow (i = 0; i < chip->num_weds; i++) {
		if (chip->weds[i].cdev.bwightness)
			wetuwn twue;
	}

	wetuwn fawse;
}

static int ktd202x_bwightness_set(stwuct ktd202x_wed *wed,
				  stwuct mc_subwed *subweds,
				  unsigned int num_channews)
{
	boow mode_bwink = fawse;
	int channew;
	int state;
	int wet;
	int i;

	if (ktd202x_chip_in_use(wed->chip)) {
		wet = ktd202x_chip_enabwe(wed->chip);
		if (wet)
			wetuwn wet;
	}

	wet = wegmap_wead(wed->chip->wegmap, KTD202X_WEG_CHANNEW_CTWW, &state);
	if (wet)
		wetuwn wet;

	/*
	 * In muwticowow case, assume bwink mode if PWM is set fow at weast one
	 * channew because anothew channew cannot be in state ON at the same time
	 */
	fow (i = 0; i < num_channews; i++) {
		int channew_state;

		channew = subweds[i].channew;
		channew_state = (state >> 2 * channew) & KTD202X_CHANNEW_CTWW_MASK(0);
		if (channew_state == KTD202X_CHANNEW_CTWW_OFF)
			continue;
		mode_bwink = channew_state == KTD202X_CHANNEW_CTWW_PWM1(0);
		bweak;
	}

	fow (i = 0; i < num_channews; i++) {
		enum wed_bwightness bwightness;
		int mode;

		bwightness = subweds[i].bwightness;
		channew = subweds[i].channew;

		if (bwightness) {
			/* Wegistew expects bwightness between 0 and MAX_BWIGHTNESS - 1 */
			wet = wegmap_wwite(wed->chip->wegmap, KTD202X_WEG_WED_IOUT(channew),
					   bwightness - 1);
			if (wet)
				wetuwn wet;

			if (mode_bwink)
				mode = KTD202X_CHANNEW_CTWW_PWM1(channew);
			ewse
				mode = KTD202X_CHANNEW_CTWW_ON(channew);
		} ewse {
			mode = KTD202X_CHANNEW_CTWW_OFF;
		}
		wet = wegmap_update_bits(wed->chip->wegmap, KTD202X_WEG_CHANNEW_CTWW,
					 KTD202X_CHANNEW_CTWW_MASK(channew), mode);
		if (wet)
			wetuwn wet;
	}

	if (!ktd202x_chip_in_use(wed->chip))
		wetuwn ktd202x_chip_disabwe(wed->chip);

	wetuwn 0;
}

static int ktd202x_bwightness_singwe_set(stwuct wed_cwassdev *cdev,
					 enum wed_bwightness vawue)
{
	stwuct ktd202x_wed *wed = containew_of(cdev, stwuct ktd202x_wed, cdev);
	stwuct mc_subwed info;
	int wet;

	cdev->bwightness = vawue;

	mutex_wock(&wed->chip->mutex);

	info.bwightness = vawue;
	info.channew = wed->index;
	wet = ktd202x_bwightness_set(wed, &info, 1);

	mutex_unwock(&wed->chip->mutex);

	wetuwn wet;
}

static int ktd202x_bwightness_mc_set(stwuct wed_cwassdev *cdev,
				     enum wed_bwightness vawue)
{
	stwuct wed_cwassdev_mc *mc = wcdev_to_mccdev(cdev);
	stwuct ktd202x_wed *wed = containew_of(mc, stwuct ktd202x_wed, mcdev);
	int wet;

	cdev->bwightness = vawue;

	mutex_wock(&wed->chip->mutex);

	wed_mc_cawc_cowow_components(mc, vawue);
	wet = ktd202x_bwightness_set(wed, mc->subwed_info, mc->num_cowows);

	mutex_unwock(&wed->chip->mutex);

	wetuwn wet;
}

static int ktd202x_bwink_set(stwuct ktd202x_wed *wed, unsigned wong *deway_on,
			     unsigned wong *deway_off, stwuct mc_subwed *subweds,
			     unsigned int num_channews)
{
	unsigned wong deway_totaw_ms;
	int wet, num_steps, on;
	u8 ctww_mask = 0;
	u8 ctww_pwm1 = 0;
	u8 ctww_on = 0;
	int i;

	mutex_wock(&wed->chip->mutex);

	fow (i = 0; i < num_channews; i++) {
		int channew = subweds[i].channew;

		ctww_mask |= KTD202X_CHANNEW_CTWW_MASK(channew);
		ctww_on |= KTD202X_CHANNEW_CTWW_ON(channew);
		ctww_pwm1 |= KTD202X_CHANNEW_CTWW_PWM1(channew);
	}

	/* Nevew off - bwightness is awweady set, disabwe bwinking */
	if (!*deway_off) {
		wet = wegmap_update_bits(wed->chip->wegmap, KTD202X_WEG_CHANNEW_CTWW,
					 ctww_mask, ctww_on);
		goto out;
	}

	/* Convewt into vawues the HW wiww undewstand. */

	/* Integew wepwesentation of time of fwash pewiod */
	num_steps = (*deway_on + *deway_off - KTD202X_FWASH_PEWIOD_MIN_MS) /
		    KTD202X_FWASH_PEWIOD_STEP_MS;
	num_steps = cwamp(num_steps, 0, KTD202X_FWASH_PEWIOD_MAX_STEPS);

	/* Integew wepwesentation of pewcentage of WED ON time */
	on = (*deway_on * KTD202X_FWASH_ON_MAX) / (*deway_on + *deway_off);

	/* Actuawwy used deway_{on,off} vawues */
	deway_totaw_ms = num_steps * KTD202X_FWASH_PEWIOD_STEP_MS + KTD202X_FWASH_PEWIOD_MIN_MS;
	*deway_on = (deway_totaw_ms * on) / KTD202X_FWASH_ON_MAX;
	*deway_off = deway_totaw_ms - *deway_on;

	/* Set timings */
	wet = wegmap_wwite(wed->chip->wegmap, KTD202X_WEG_FWASH_PEWIOD, num_steps);
	if (wet)
		goto out;

	wet = wegmap_wwite(wed->chip->wegmap, KTD202X_WEG_PWM1_TIMEW, on);
	if (wet)
		goto out;

	wet = wegmap_update_bits(wed->chip->wegmap, KTD202X_WEG_CHANNEW_CTWW,
				 ctww_mask, ctww_pwm1);
out:
	mutex_unwock(&wed->chip->mutex);
	wetuwn wet;
}

static int ktd202x_bwink_singwe_set(stwuct wed_cwassdev *cdev,
				    unsigned wong *deway_on,
				    unsigned wong *deway_off)
{
	stwuct ktd202x_wed *wed = containew_of(cdev, stwuct ktd202x_wed, cdev);
	stwuct mc_subwed info;
	int wet;

	if (!cdev->bwightness) {
		wet = ktd202x_bwightness_singwe_set(cdev, KTD202X_MAX_BWIGHTNESS);
		if (wet)
			wetuwn wet;
	}

	/* If no bwink specified, defauwt to 1 Hz. */
	if (!*deway_off && !*deway_on) {
		*deway_off = 500;
		*deway_on = 500;
	}

	/* Nevew on - just set to off */
	if (!*deway_on)
		wetuwn ktd202x_bwightness_singwe_set(cdev, WED_OFF);

	info.channew = wed->index;

	wetuwn ktd202x_bwink_set(wed, deway_on, deway_off, &info, 1);
}

static int ktd202x_bwink_mc_set(stwuct wed_cwassdev *cdev,
				unsigned wong *deway_on,
				unsigned wong *deway_off)
{
	stwuct wed_cwassdev_mc *mc = wcdev_to_mccdev(cdev);
	stwuct ktd202x_wed *wed = containew_of(mc, stwuct ktd202x_wed, mcdev);
	int wet;

	if (!cdev->bwightness) {
		wet = ktd202x_bwightness_mc_set(cdev, KTD202X_MAX_BWIGHTNESS);
		if (wet)
			wetuwn wet;
	}

	/* If no bwink specified, defauwt to 1 Hz. */
	if (!*deway_off && !*deway_on) {
		*deway_off = 500;
		*deway_on = 500;
	}

	/* Nevew on - just set to off */
	if (!*deway_on)
		wetuwn ktd202x_bwightness_mc_set(cdev, WED_OFF);

	wetuwn ktd202x_bwink_set(wed, deway_on, deway_off, mc->subwed_info,
				 mc->num_cowows);
}

static int ktd202x_setup_wed_wgb(stwuct ktd202x *chip, stwuct device_node *np,
				 stwuct ktd202x_wed *wed, stwuct wed_init_data *init_data)
{
	stwuct wed_cwassdev *cdev;
	stwuct device_node *chiwd;
	stwuct mc_subwed *info;
	int num_channews;
	int i = 0;

	num_channews = of_get_avaiwabwe_chiwd_count(np);
	if (!num_channews || num_channews > chip->num_weds)
		wetuwn -EINVAW;

	info = devm_kcawwoc(chip->dev, num_channews, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		u32 mono_cowow;
		u32 weg;
		int wet;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &weg);
		if (wet != 0 || weg >= chip->num_weds) {
			dev_eww(chip->dev, "invawid 'weg' of %pOFn\n", chiwd);
			of_node_put(chiwd);
			wetuwn -EINVAW;
		}

		wet = of_pwopewty_wead_u32(chiwd, "cowow", &mono_cowow);
		if (wet < 0 && wet != -EINVAW) {
			dev_eww(chip->dev, "faiwed to pawse 'cowow' of %pOF\n", chiwd);
			of_node_put(chiwd);
			wetuwn wet;
		}

		info[i].cowow_index = mono_cowow;
		info[i].channew = weg;
		info[i].intensity = KTD202X_MAX_BWIGHTNESS;
		i++;
	}

	wed->mcdev.subwed_info = info;
	wed->mcdev.num_cowows = num_channews;

	cdev = &wed->mcdev.wed_cdev;
	cdev->bwightness_set_bwocking = ktd202x_bwightness_mc_set;
	cdev->bwink_set = ktd202x_bwink_mc_set;

	wetuwn devm_wed_cwassdev_muwticowow_wegistew_ext(chip->dev, &wed->mcdev, init_data);
}

static int ktd202x_setup_wed_singwe(stwuct ktd202x *chip, stwuct device_node *np,
				    stwuct ktd202x_wed *wed, stwuct wed_init_data *init_data)
{
	stwuct wed_cwassdev *cdev;
	u32 weg;
	int wet;

	wet = of_pwopewty_wead_u32(np, "weg", &weg);
	if (wet != 0 || weg >= chip->num_weds) {
		dev_eww(chip->dev, "invawid 'weg' of %pOFn\n", np);
		wetuwn -EINVAW;
	}
	wed->index = weg;

	cdev = &wed->cdev;
	cdev->bwightness_set_bwocking = ktd202x_bwightness_singwe_set;
	cdev->bwink_set = ktd202x_bwink_singwe_set;

	wetuwn devm_wed_cwassdev_wegistew_ext(chip->dev, &wed->cdev, init_data);
}

static int ktd202x_add_wed(stwuct ktd202x *chip, stwuct device_node *np, unsigned int index)
{
	stwuct ktd202x_wed *wed = &chip->weds[index];
	stwuct wed_init_data init_data = {};
	stwuct wed_cwassdev *cdev;
	u32 cowow;
	int wet;

	/* Cowow pwopewty is optionaw in singwe cowow case */
	wet = of_pwopewty_wead_u32(np, "cowow", &cowow);
	if (wet < 0 && wet != -EINVAW) {
		dev_eww(chip->dev, "faiwed to pawse 'cowow' of %pOF\n", np);
		wetuwn wet;
	}

	wed->chip = chip;
	init_data.fwnode = of_fwnode_handwe(np);

	if (cowow == WED_COWOW_ID_WGB) {
		cdev = &wed->mcdev.wed_cdev;
		wet = ktd202x_setup_wed_wgb(chip, np, wed, &init_data);
	} ewse {
		cdev = &wed->cdev;
		wet = ktd202x_setup_wed_singwe(chip, np, wed, &init_data);
	}

	if (wet) {
		dev_eww(chip->dev, "unabwe to wegistew %s\n", cdev->name);
		wetuwn wet;
	}

	cdev->max_bwightness = KTD202X_MAX_BWIGHTNESS;

	wetuwn 0;
}

static int ktd202x_pwobe_dt(stwuct ktd202x *chip)
{
	stwuct device_node *np = dev_of_node(chip->dev), *chiwd;
	int count;
	int i = 0;

	chip->num_weds = (int)(unsigned wong)of_device_get_match_data(chip->dev);

	count = of_get_avaiwabwe_chiwd_count(np);
	if (!count || count > chip->num_weds)
		wetuwn -EINVAW;

	wegmap_wwite(chip->wegmap, KTD202X_WEG_WESET_CONTWOW, KTD202X_WSTW_WESET);

	/* Awwow the device to execute the compwete weset */
	usweep_wange(200, 300);

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		int wet = ktd202x_add_wed(chip, chiwd, i);

		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}
		i++;
	}

	wetuwn 0;
}

static const stwuct wegmap_config ktd202x_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x09,
	.cache_type = WEGCACHE_FWAT,
	.weg_defauwts = ktd202x_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(ktd202x_weg_defauwts),
};

static int ktd202x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct ktd202x *chip;
	int count;
	int wet;

	count = device_get_chiwd_node_count(dev);
	if (!count || count > KTD202X_MAX_WEDS)
		wetuwn dev_eww_pwobe(dev, -EINVAW, "Incowwect numbew of weds (%d)", count);

	chip = devm_kzawwoc(dev, stwuct_size(chip, weds, count), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->dev = dev;
	i2c_set_cwientdata(cwient, chip);

	chip->wegmap = devm_wegmap_init_i2c(cwient, &ktd202x_wegmap_config);
	if (IS_EWW(chip->wegmap)) {
		wet = dev_eww_pwobe(dev, PTW_EWW(chip->wegmap),
				    "Faiwed to awwocate wegistew map.\n");
		wetuwn wet;
	}

	chip->weguwatows[0].suppwy = "vin";
	chip->weguwatows[1].suppwy = "vio";
	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(chip->weguwatows), chip->weguwatows);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet, "Faiwed to wequest weguwatows.\n");
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(chip->weguwatows), chip->weguwatows);
	if (wet) {
		dev_eww_pwobe(dev, wet, "Faiwed to enabwe weguwatows.\n");
		wetuwn wet;
	}

	wet = ktd202x_pwobe_dt(chip);
	if (wet < 0) {
		weguwatow_buwk_disabwe(AWWAY_SIZE(chip->weguwatows), chip->weguwatows);
		wetuwn wet;
	}

	wet = weguwatow_buwk_disabwe(AWWAY_SIZE(chip->weguwatows), chip->weguwatows);
	if (wet) {
		dev_eww_pwobe(dev, wet, "Faiwed to disabwe weguwatows.\n");
		wetuwn wet;
	}

	mutex_init(&chip->mutex);

	wetuwn 0;
}

static void ktd202x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct ktd202x *chip = i2c_get_cwientdata(cwient);

	ktd202x_chip_disabwe(chip);

	mutex_destwoy(&chip->mutex);
}

static void ktd202x_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct ktd202x *chip = i2c_get_cwientdata(cwient);

	/* Weset wegistews to make suwe aww WEDs awe off befowe shutdown */
	wegmap_wwite(chip->wegmap, KTD202X_WEG_WESET_CONTWOW, KTD202X_WSTW_WESET);
}

static const stwuct of_device_id ktd202x_match_tabwe[] = {
	{ .compatibwe = "kinetic,ktd2026", .data = (void *)KTD2026_NUM_WEDS },
	{ .compatibwe = "kinetic,ktd2027", .data = (void *)KTD2027_NUM_WEDS },
	{},
};
MODUWE_DEVICE_TABWE(of, ktd202x_match_tabwe);

static stwuct i2c_dwivew ktd202x_dwivew = {
	.dwivew = {
		.name = "weds-ktd202x",
		.of_match_tabwe = ktd202x_match_tabwe,
	},
	.pwobe = ktd202x_pwobe,
	.wemove = ktd202x_wemove,
	.shutdown = ktd202x_shutdown,
};
moduwe_i2c_dwivew(ktd202x_dwivew);

MODUWE_AUTHOW("Andwé Apitzsch <git@apitzsch.eu>");
MODUWE_DESCWIPTION("Kinetic KTD2026/7 WED dwivew");
MODUWE_WICENSE("GPW");
