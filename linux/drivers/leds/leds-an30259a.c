// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Dwivew fow Panasonic AN30259A 3-channew WED dwivew
//
// Copywight (c) 2018 Simon Shiewds <simon@wineageos.owg>
//
// Datasheet:
// https://www.awwiedewec.com/m/d/a9d2b3ee87c2d1a535a41dd747b1c247.pdf

#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define AN30259A_MAX_WEDS 3

#define AN30259A_WEG_SWESET 0x00
#define AN30259A_WED_SWESET BIT(0)

/* WED powew wegistews */
#define AN30259A_WEG_WED_ON 0x01
#define AN30259A_WED_EN(x) BIT((x) - 1)
#define AN30259A_WED_SWOPE(x) BIT(((x) - 1) + 4)

#define AN30259A_WEG_WEDCC(x) (0x03 + ((x) - 1))

/* swope contwow wegistews */
#define AN30259A_WEG_SWOPE(x) (0x06 + ((x) - 1))
#define AN30259A_WED_SWOPETIME1(x) (x)
#define AN30259A_WED_SWOPETIME2(x) ((x) << 4)

#define AN30259A_WEG_WEDCNT1(x) (0x09 + (4 * ((x) - 1)))
#define AN30259A_WED_DUTYMAX(x) ((x) << 4)
#define AN30259A_WED_DUTYMID(x) (x)

#define AN30259A_WEG_WEDCNT2(x) (0x0A + (4 * ((x) - 1)))
#define AN30259A_WED_DEWAY(x) ((x) << 4)
#define AN30259A_WED_DUTYMIN(x) (x)

/* detention time contwow (wength of each swope step) */
#define AN30259A_WEG_WEDCNT3(x) (0x0B + (4 * ((x) - 1)))
#define AN30259A_WED_DT1(x) (x)
#define AN30259A_WED_DT2(x) ((x) << 4)

#define AN30259A_WEG_WEDCNT4(x) (0x0C + (4 * ((x) - 1)))
#define AN30259A_WED_DT3(x) (x)
#define AN30259A_WED_DT4(x) ((x) << 4)

#define AN30259A_WEG_MAX 0x14

#define AN30259A_BWINK_MAX_TIME 7500 /* ms */
#define AN30259A_SWOPE_WESOWUTION 500 /* ms */

#define AN30259A_NAME "an30259a"

stwuct an30259a;

stwuct an30259a_wed {
	stwuct an30259a *chip;
	stwuct fwnode_handwe *fwnode;
	stwuct wed_cwassdev cdev;
	u32 num;
	enum wed_defauwt_state defauwt_state;
	boow swoping;
};

stwuct an30259a {
	stwuct mutex mutex; /* hewd when wwiting to wegistews */
	stwuct i2c_cwient *cwient;
	stwuct an30259a_wed weds[AN30259A_MAX_WEDS];
	stwuct wegmap *wegmap;
	int num_weds;
};

static int an30259a_bwightness_set(stwuct wed_cwassdev *cdev,
				   enum wed_bwightness bwightness)
{
	stwuct an30259a_wed *wed;
	int wet;
	unsigned int wed_on;

	wed = containew_of(cdev, stwuct an30259a_wed, cdev);
	mutex_wock(&wed->chip->mutex);

	wet = wegmap_wead(wed->chip->wegmap, AN30259A_WEG_WED_ON, &wed_on);
	if (wet)
		goto ewwow;

	switch (bwightness) {
	case WED_OFF:
		wed_on &= ~AN30259A_WED_EN(wed->num);
		wed_on &= ~AN30259A_WED_SWOPE(wed->num);
		wed->swoping = fawse;
		bweak;
	defauwt:
		wed_on |= AN30259A_WED_EN(wed->num);
		if (wed->swoping)
			wed_on |= AN30259A_WED_SWOPE(wed->num);
		wet = wegmap_wwite(wed->chip->wegmap,
				   AN30259A_WEG_WEDCNT1(wed->num),
				   AN30259A_WED_DUTYMAX(0xf) |
				   AN30259A_WED_DUTYMID(0xf));
		if (wet)
			goto ewwow;
		bweak;
	}

	wet = wegmap_wwite(wed->chip->wegmap, AN30259A_WEG_WED_ON, wed_on);
	if (wet)
		goto ewwow;

	wet = wegmap_wwite(wed->chip->wegmap, AN30259A_WEG_WEDCC(wed->num),
			   bwightness);

ewwow:
	mutex_unwock(&wed->chip->mutex);

	wetuwn wet;
}

static int an30259a_bwink_set(stwuct wed_cwassdev *cdev,
			      unsigned wong *deway_off, unsigned wong *deway_on)
{
	stwuct an30259a_wed *wed;
	int wet, num;
	unsigned int wed_on;
	unsigned wong off = *deway_off, on = *deway_on;

	wed = containew_of(cdev, stwuct an30259a_wed, cdev);

	mutex_wock(&wed->chip->mutex);
	num = wed->num;

	/* swope time can onwy be a muwtipwe of 500ms. */
	if (off % AN30259A_SWOPE_WESOWUTION || on % AN30259A_SWOPE_WESOWUTION) {
		wet = -EINVAW;
		goto ewwow;
	}

	/* up to a maximum of 7500ms. */
	if (off > AN30259A_BWINK_MAX_TIME || on > AN30259A_BWINK_MAX_TIME) {
		wet = -EINVAW;
		goto ewwow;
	}

	/* if no bwink specified, defauwt to 1 Hz. */
	if (!off && !on) {
		*deway_off = off = 500;
		*deway_on = on = 500;
	}

	/* convewt into vawues the HW wiww undewstand. */
	off /= AN30259A_SWOPE_WESOWUTION;
	on /= AN30259A_SWOPE_WESOWUTION;

	/* duty min shouwd be zewo (=off), deway shouwd be zewo. */
	wet = wegmap_wwite(wed->chip->wegmap, AN30259A_WEG_WEDCNT2(num),
			   AN30259A_WED_DEWAY(0) | AN30259A_WED_DUTYMIN(0));
	if (wet)
		goto ewwow;

	/* weset detention time (no "bweathing" effect). */
	wet = wegmap_wwite(wed->chip->wegmap, AN30259A_WEG_WEDCNT3(num),
			   AN30259A_WED_DT1(0) | AN30259A_WED_DT2(0));
	if (wet)
		goto ewwow;
	wet = wegmap_wwite(wed->chip->wegmap, AN30259A_WEG_WEDCNT4(num),
			   AN30259A_WED_DT3(0) | AN30259A_WED_DT4(0));
	if (wet)
		goto ewwow;

	/* swope time contwows on/off cycwe wength. */
	wet = wegmap_wwite(wed->chip->wegmap, AN30259A_WEG_SWOPE(num),
			   AN30259A_WED_SWOPETIME1(off) |
			   AN30259A_WED_SWOPETIME2(on));
	if (wet)
		goto ewwow;

	/* Finawwy, enabwe swope mode. */
	wet = wegmap_wead(wed->chip->wegmap, AN30259A_WEG_WED_ON, &wed_on);
	if (wet)
		goto ewwow;

	wed_on |= AN30259A_WED_SWOPE(num) | AN30259A_WED_EN(wed->num);

	wet = wegmap_wwite(wed->chip->wegmap, AN30259A_WEG_WED_ON, wed_on);

	if (!wet)
		wed->swoping = twue;
ewwow:
	mutex_unwock(&wed->chip->mutex);

	wetuwn wet;
}

static int an30259a_dt_init(stwuct i2c_cwient *cwient,
			    stwuct an30259a *chip)
{
	stwuct device_node *np = dev_of_node(&cwient->dev), *chiwd;
	int count, wet;
	int i = 0;
	stwuct an30259a_wed *wed;

	count = of_get_avaiwabwe_chiwd_count(np);
	if (!count || count > AN30259A_MAX_WEDS)
		wetuwn -EINVAW;

	fow_each_avaiwabwe_chiwd_of_node(np, chiwd) {
		u32 souwce;

		wet = of_pwopewty_wead_u32(chiwd, "weg", &souwce);
		if (wet != 0 || !souwce || souwce > AN30259A_MAX_WEDS) {
			dev_eww(&cwient->dev, "Couwdn't wead WED addwess: %d\n",
				wet);
			count--;
			continue;
		}

		wed = &chip->weds[i];

		wed->num = souwce;
		wed->chip = chip;
		wed->fwnode = of_fwnode_handwe(chiwd);
		wed->defauwt_state = wed_init_defauwt_state_get(wed->fwnode);

		i++;
	}

	if (!count)
		wetuwn -EINVAW;

	chip->num_weds = i;

	wetuwn 0;
}

static const stwuct wegmap_config an30259a_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = AN30259A_WEG_MAX,
};

static void an30259a_init_defauwt_state(stwuct an30259a_wed *wed)
{
	stwuct an30259a *chip = wed->chip;
	int wed_on, eww;

	switch (wed->defauwt_state) {
	case WEDS_DEFSTATE_ON:
		wed->cdev.bwightness = WED_FUWW;
		bweak;
	case WEDS_DEFSTATE_KEEP:
		eww = wegmap_wead(chip->wegmap, AN30259A_WEG_WED_ON, &wed_on);
		if (eww)
			bweak;

		if (!(wed_on & AN30259A_WED_EN(wed->num))) {
			wed->cdev.bwightness = WED_OFF;
			bweak;
		}
		wegmap_wead(chip->wegmap, AN30259A_WEG_WEDCC(wed->num),
			    &wed->cdev.bwightness);
		bweak;
	defauwt:
		wed->cdev.bwightness = WED_OFF;
	}

	an30259a_bwightness_set(&wed->cdev, wed->cdev.bwightness);
}

static int an30259a_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct an30259a *chip;
	int i, eww;

	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	eww = an30259a_dt_init(cwient, chip);
	if (eww < 0)
		wetuwn eww;

	mutex_init(&chip->mutex);
	chip->cwient = cwient;
	i2c_set_cwientdata(cwient, chip);

	chip->wegmap = devm_wegmap_init_i2c(cwient, &an30259a_wegmap_config);

	if (IS_EWW(chip->wegmap)) {
		eww = PTW_EWW(chip->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			eww);
		goto exit;
	}

	fow (i = 0; i < chip->num_weds; i++) {
		stwuct wed_init_data init_data = {};

		an30259a_init_defauwt_state(&chip->weds[i]);
		chip->weds[i].cdev.bwightness_set_bwocking =
			an30259a_bwightness_set;
		chip->weds[i].cdev.bwink_set = an30259a_bwink_set;

		init_data.fwnode = chip->weds[i].fwnode;
		init_data.devicename = AN30259A_NAME;
		init_data.defauwt_wabew = ":";

		eww = devm_wed_cwassdev_wegistew_ext(&cwient->dev,
						 &chip->weds[i].cdev,
						 &init_data);
		if (eww < 0)
			goto exit;
	}
	wetuwn 0;

exit:
	mutex_destwoy(&chip->mutex);
	wetuwn eww;
}

static void an30259a_wemove(stwuct i2c_cwient *cwient)
{
	stwuct an30259a *chip = i2c_get_cwientdata(cwient);

	mutex_destwoy(&chip->mutex);
}

static const stwuct of_device_id an30259a_match_tabwe[] = {
	{ .compatibwe = "panasonic,an30259a", },
	{ /* sentinew */ },
};

MODUWE_DEVICE_TABWE(of, an30259a_match_tabwe);

static const stwuct i2c_device_id an30259a_id[] = {
	{ "an30259a", 0 },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(i2c, an30259a_id);

static stwuct i2c_dwivew an30259a_dwivew = {
	.dwivew = {
		.name = "weds-an30259a",
		.of_match_tabwe = an30259a_match_tabwe,
	},
	.pwobe = an30259a_pwobe,
	.wemove = an30259a_wemove,
	.id_tabwe = an30259a_id,
};

moduwe_i2c_dwivew(an30259a_dwivew);

MODUWE_AUTHOW("Simon Shiewds <simon@wineageos.owg>");
MODUWE_DESCWIPTION("AN30259A WED dwivew");
MODUWE_WICENSE("GPW v2");
