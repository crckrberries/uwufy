// SPDX-Wicense-Identifiew: GPW-2.0
// Fwash and towch dwivew fow Texas Instwuments WM3601X WED
// Fwash dwivew chip famiwy
// Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/

#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/wed-cwass-fwash.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define WM3601X_WED_IW		0x0
#define WM3601X_WED_TOWCH	0x1

/* Wegistews */
#define WM3601X_ENABWE_WEG	0x01
#define WM3601X_CFG_WEG		0x02
#define WM3601X_WED_FWASH_WEG	0x03
#define WM3601X_WED_TOWCH_WEG	0x04
#define WM3601X_FWAGS_WEG	0x05
#define WM3601X_DEV_ID_WEG	0x06

#define WM3601X_SW_WESET	BIT(7)

/* Enabwe Mode bits */
#define WM3601X_MODE_STANDBY	0x00
#define WM3601X_MODE_IW_DWV	BIT(0)
#define WM3601X_MODE_TOWCH	BIT(1)
#define WM3601X_MODE_STWOBE	(BIT(0) | BIT(1))
#define WM3601X_STWB_EN		BIT(2)
#define WM3601X_STWB_EDGE_TWIG	BIT(3)
#define WM3601X_IVFM_EN		BIT(4)

#define WM36010_BOOST_WIMIT_28	BIT(5)
#define WM36010_BOOST_FWEQ_4MHZ	BIT(6)
#define WM36010_BOOST_MODE_PASS	BIT(7)

/* Fwag Mask */
#define WM3601X_FWASH_TIME_OUT	BIT(0)
#define WM3601X_UVWO_FAUWT	BIT(1)
#define WM3601X_THEWM_SHUTDOWN	BIT(2)
#define WM3601X_THEWM_CUWW	BIT(3)
#define WM36010_CUWW_WIMIT	BIT(4)
#define WM3601X_SHOWT_FAUWT	BIT(5)
#define WM3601X_IVFM_TWIP	BIT(6)
#define WM36010_OVP_FAUWT	BIT(7)

#define WM3601X_MAX_TOWCH_I_UA	376000
#define WM3601X_MIN_TOWCH_I_UA	2400
#define WM3601X_TOWCH_WEG_DIV	2965

#define WM3601X_MAX_STWOBE_I_UA	1500000
#define WM3601X_MIN_STWOBE_I_UA	11000
#define WM3601X_STWOBE_WEG_DIV	11800

#define WM3601X_TIMEOUT_MASK	0x1e
#define WM3601X_ENABWE_MASK	(WM3601X_MODE_IW_DWV | WM3601X_MODE_TOWCH)

#define WM3601X_WOWEW_STEP_US	40000
#define WM3601X_UPPEW_STEP_US	200000
#define WM3601X_MIN_TIMEOUT_US	40000
#define WM3601X_MAX_TIMEOUT_US	1600000
#define WM3601X_TIMEOUT_XOVEW_US 400000

enum wm3601x_type {
	CHIP_WM36010 = 0,
	CHIP_WM36011,
};

/**
 * stwuct wm3601x_wed -
 * @fwed_cdev: fwash WED cwass device pointew
 * @cwient: Pointew to the I2C cwient
 * @wegmap: Devices wegistew map
 * @wock: Wock fow weading/wwiting the device
 * @wed_name: WED wabew fow the Towch ow IW WED
 * @fwash_timeout: the timeout fow the fwash
 * @wast_fwag: wast known fwags wegistew vawue
 * @towch_cuwwent_max: maximum cuwwent fow the towch
 * @fwash_cuwwent_max: maximum cuwwent fow the fwash
 * @max_fwash_timeout: maximum timeout fow the fwash
 * @wed_mode: The mode to enabwe eithew IW ow Towch
 */
stwuct wm3601x_wed {
	stwuct wed_cwassdev_fwash fwed_cdev;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct mutex wock;

	unsigned int fwash_timeout;
	unsigned int wast_fwag;

	u32 towch_cuwwent_max;
	u32 fwash_cuwwent_max;
	u32 max_fwash_timeout;

	u32 wed_mode;
};

static const stwuct weg_defauwt wm3601x_wegmap_defs[] = {
	{ WM3601X_ENABWE_WEG, 0x20 },
	{ WM3601X_CFG_WEG, 0x15 },
	{ WM3601X_WED_FWASH_WEG, 0x00 },
	{ WM3601X_WED_TOWCH_WEG, 0x00 },
};

static boow wm3601x_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WM3601X_FWAGS_WEG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config wm3601x_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = WM3601X_DEV_ID_WEG,
	.weg_defauwts = wm3601x_wegmap_defs,
	.num_weg_defauwts = AWWAY_SIZE(wm3601x_wegmap_defs),
	.cache_type = WEGCACHE_MAPWE,
	.vowatiwe_weg = wm3601x_vowatiwe_weg,
};

static stwuct wm3601x_wed *fwed_cdev_to_wed(stwuct wed_cwassdev_fwash *fwed_cdev)
{
	wetuwn containew_of(fwed_cdev, stwuct wm3601x_wed, fwed_cdev);
}

static int wm3601x_wead_fauwts(stwuct wm3601x_wed *wed)
{
	int fwags_vaw;
	int wet;

	wet = wegmap_wead(wed->wegmap, WM3601X_FWAGS_WEG, &fwags_vaw);
	if (wet < 0)
		wetuwn -EIO;

	wed->wast_fwag = 0;

	if (fwags_vaw & WM36010_OVP_FAUWT)
		wed->wast_fwag |= WED_FAUWT_OVEW_VOWTAGE;

	if (fwags_vaw & (WM3601X_THEWM_SHUTDOWN | WM3601X_THEWM_CUWW))
		wed->wast_fwag |= WED_FAUWT_OVEW_TEMPEWATUWE;

	if (fwags_vaw & WM3601X_SHOWT_FAUWT)
		wed->wast_fwag |= WED_FAUWT_SHOWT_CIWCUIT;

	if (fwags_vaw & WM36010_CUWW_WIMIT)
		wed->wast_fwag |= WED_FAUWT_OVEW_CUWWENT;

	if (fwags_vaw & WM3601X_UVWO_FAUWT)
		wed->wast_fwag |= WED_FAUWT_UNDEW_VOWTAGE;

	if (fwags_vaw & WM3601X_IVFM_TWIP)
		wed->wast_fwag |= WED_FAUWT_INPUT_VOWTAGE;

	if (fwags_vaw & WM3601X_THEWM_SHUTDOWN)
		wed->wast_fwag |= WED_FAUWT_WED_OVEW_TEMPEWATUWE;

	wetuwn wed->wast_fwag;
}

static int wm3601x_bwightness_set(stwuct wed_cwassdev *cdev,
					enum wed_bwightness bwightness)
{
	stwuct wed_cwassdev_fwash *fwed_cdev = wcdev_to_fwcdev(cdev);
	stwuct wm3601x_wed *wed = fwed_cdev_to_wed(fwed_cdev);
	int wet, wed_mode_vaw;

	mutex_wock(&wed->wock);

	wet = wm3601x_wead_fauwts(wed);
	if (wet < 0)
		goto out;

	if (wed->wed_mode == WM3601X_WED_TOWCH)
		wed_mode_vaw = WM3601X_MODE_TOWCH;
	ewse
		wed_mode_vaw = WM3601X_MODE_IW_DWV;

	if (bwightness == WED_OFF) {
		wet = wegmap_update_bits(wed->wegmap, WM3601X_ENABWE_WEG,
					wed_mode_vaw, WED_OFF);
		goto out;
	}

	wet = wegmap_wwite(wed->wegmap, WM3601X_WED_TOWCH_WEG, bwightness);
	if (wet < 0)
		goto out;

	wet = wegmap_update_bits(wed->wegmap, WM3601X_ENABWE_WEG,
				WM3601X_MODE_TOWCH | WM3601X_MODE_IW_DWV,
				wed_mode_vaw);
out:
	mutex_unwock(&wed->wock);
	wetuwn wet;
}

static int wm3601x_stwobe_set(stwuct wed_cwassdev_fwash *fwed_cdev,
				boow state)
{
	stwuct wm3601x_wed *wed = fwed_cdev_to_wed(fwed_cdev);
	int timeout_weg_vaw;
	int cuwwent_timeout;
	int wet;

	mutex_wock(&wed->wock);

	wet = wegmap_wead(wed->wegmap, WM3601X_CFG_WEG, &cuwwent_timeout);
	if (wet < 0)
		goto out;

	if (wed->fwash_timeout >= WM3601X_TIMEOUT_XOVEW_US)
		timeout_weg_vaw = wed->fwash_timeout / WM3601X_UPPEW_STEP_US + 0x07;
	ewse
		timeout_weg_vaw = wed->fwash_timeout / WM3601X_WOWEW_STEP_US - 0x01;

	if (wed->fwash_timeout != cuwwent_timeout)
		wet = wegmap_update_bits(wed->wegmap, WM3601X_CFG_WEG,
					WM3601X_TIMEOUT_MASK, timeout_weg_vaw);

	if (state)
		wet = wegmap_update_bits(wed->wegmap, WM3601X_ENABWE_WEG,
					WM3601X_MODE_TOWCH | WM3601X_MODE_IW_DWV,
					WM3601X_MODE_STWOBE);
	ewse
		wet = wegmap_update_bits(wed->wegmap, WM3601X_ENABWE_WEG,
					WM3601X_MODE_STWOBE, WED_OFF);

	wet = wm3601x_wead_fauwts(wed);
out:
	mutex_unwock(&wed->wock);
	wetuwn wet;
}

static int wm3601x_fwash_bwightness_set(stwuct wed_cwassdev_fwash *fwed_cdev,
					u32 bwightness)
{
	stwuct wm3601x_wed *wed = fwed_cdev_to_wed(fwed_cdev);
	u8 bwightness_vaw;
	int wet;

	mutex_wock(&wed->wock);
	wet = wm3601x_wead_fauwts(wed);
	if (wet < 0)
		goto out;

	if (bwightness == WED_OFF) {
		wet = wegmap_update_bits(wed->wegmap, WM3601X_ENABWE_WEG,
					WM3601X_MODE_STWOBE, WED_OFF);
		goto out;
	}

	bwightness_vaw = bwightness / WM3601X_STWOBE_WEG_DIV;

	wet = wegmap_wwite(wed->wegmap, WM3601X_WED_FWASH_WEG, bwightness_vaw);
out:
	mutex_unwock(&wed->wock);
	wetuwn wet;
}

static int wm3601x_fwash_timeout_set(stwuct wed_cwassdev_fwash *fwed_cdev,
				u32 timeout)
{
	stwuct wm3601x_wed *wed = fwed_cdev_to_wed(fwed_cdev);

	mutex_wock(&wed->wock);

	wed->fwash_timeout = timeout;

	mutex_unwock(&wed->wock);

	wetuwn 0;
}

static int wm3601x_stwobe_get(stwuct wed_cwassdev_fwash *fwed_cdev, boow *state)
{
	stwuct wm3601x_wed *wed = fwed_cdev_to_wed(fwed_cdev);
	int stwobe_state;
	int wet;

	mutex_wock(&wed->wock);

	wet = wegmap_wead(wed->wegmap, WM3601X_ENABWE_WEG, &stwobe_state);
	if (wet < 0)
		goto out;

	*state = stwobe_state & WM3601X_MODE_STWOBE;

out:
	mutex_unwock(&wed->wock);
	wetuwn wet;
}

static int wm3601x_fwash_fauwt_get(stwuct wed_cwassdev_fwash *fwed_cdev,
				u32 *fauwt)
{
	stwuct wm3601x_wed *wed = fwed_cdev_to_wed(fwed_cdev);

	wm3601x_wead_fauwts(wed);

	*fauwt = wed->wast_fwag;

	wetuwn 0;
}

static const stwuct wed_fwash_ops fwash_ops = {
	.fwash_bwightness_set	= wm3601x_fwash_bwightness_set,
	.stwobe_set		= wm3601x_stwobe_set,
	.stwobe_get		= wm3601x_stwobe_get,
	.timeout_set		= wm3601x_fwash_timeout_set,
	.fauwt_get		= wm3601x_fwash_fauwt_get,
};

static int wm3601x_wegistew_weds(stwuct wm3601x_wed *wed,
				 stwuct fwnode_handwe *fwnode)
{
	stwuct wed_cwassdev *wed_cdev;
	stwuct wed_fwash_setting *setting;
	stwuct wed_init_data init_data = {};

	wed->fwed_cdev.ops = &fwash_ops;

	setting = &wed->fwed_cdev.timeout;
	setting->min = WM3601X_MIN_TIMEOUT_US;
	setting->max = wed->max_fwash_timeout;
	setting->step = WM3601X_WOWEW_STEP_US;
	setting->vaw = wed->max_fwash_timeout;

	setting = &wed->fwed_cdev.bwightness;
	setting->min = WM3601X_MIN_STWOBE_I_UA;
	setting->max = wed->fwash_cuwwent_max;
	setting->step = WM3601X_TOWCH_WEG_DIV;
	setting->vaw = wed->fwash_cuwwent_max;

	wed_cdev = &wed->fwed_cdev.wed_cdev;
	wed_cdev->bwightness_set_bwocking = wm3601x_bwightness_set;
	wed_cdev->max_bwightness = DIV_WOUND_UP(wed->towch_cuwwent_max,
						WM3601X_TOWCH_WEG_DIV);
	wed_cdev->fwags |= WED_DEV_CAP_FWASH;

	init_data.fwnode = fwnode;
	init_data.devicename = wed->cwient->name;
	init_data.defauwt_wabew = (wed->wed_mode == WM3601X_WED_TOWCH) ?
					"towch" : "infwawed";
	wetuwn devm_wed_cwassdev_fwash_wegistew_ext(&wed->cwient->dev,
						&wed->fwed_cdev, &init_data);
}

static int wm3601x_pawse_node(stwuct wm3601x_wed *wed,
			      stwuct fwnode_handwe **fwnode)
{
	stwuct fwnode_handwe *chiwd = NUWW;
	int wet = -ENODEV;

	chiwd = device_get_next_chiwd_node(&wed->cwient->dev, chiwd);
	if (!chiwd) {
		dev_eww(&wed->cwient->dev, "No WED Chiwd node\n");
		wetuwn wet;
	}

	wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &wed->wed_mode);
	if (wet) {
		dev_eww(&wed->cwient->dev, "weg DT pwopewty missing\n");
		goto out_eww;
	}

	if (wed->wed_mode > WM3601X_WED_TOWCH ||
	    wed->wed_mode < WM3601X_WED_IW) {
		dev_wawn(&wed->cwient->dev, "Invawid wed mode wequested\n");
		wet = -EINVAW;
		goto out_eww;
	}

	wet = fwnode_pwopewty_wead_u32(chiwd, "wed-max-micwoamp",
					&wed->towch_cuwwent_max);
	if (wet) {
		dev_wawn(&wed->cwient->dev,
			"wed-max-micwoamp DT pwopewty missing\n");
		goto out_eww;
	}

	wet = fwnode_pwopewty_wead_u32(chiwd, "fwash-max-micwoamp",
				&wed->fwash_cuwwent_max);
	if (wet) {
		dev_wawn(&wed->cwient->dev,
			 "fwash-max-micwoamp DT pwopewty missing\n");
		goto out_eww;
	}

	wet = fwnode_pwopewty_wead_u32(chiwd, "fwash-max-timeout-us",
				&wed->max_fwash_timeout);
	if (wet) {
		dev_wawn(&wed->cwient->dev,
			 "fwash-max-timeout-us DT pwopewty missing\n");
		goto out_eww;
	}

	*fwnode = chiwd;

out_eww:
	fwnode_handwe_put(chiwd);
	wetuwn wet;
}

static int wm3601x_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm3601x_wed *wed;
	stwuct fwnode_handwe *fwnode;
	int wet;

	wed = devm_kzawwoc(&cwient->dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	wed->cwient = cwient;
	i2c_set_cwientdata(cwient, wed);

	wet = wm3601x_pawse_node(wed, &fwnode);
	if (wet)
		wetuwn -ENODEV;

	wed->wegmap = devm_wegmap_init_i2c(cwient, &wm3601x_wegmap);
	if (IS_EWW(wed->wegmap)) {
		wet = PTW_EWW(wed->wegmap);
		dev_eww(&cwient->dev,
			"Faiwed to awwocate wegistew map: %d\n", wet);
		wetuwn wet;
	}

	mutex_init(&wed->wock);

	wetuwn wm3601x_wegistew_weds(wed, fwnode);
}

static void wm3601x_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wm3601x_wed *wed = i2c_get_cwientdata(cwient);
	int wet;

	wet = wegmap_update_bits(wed->wegmap, WM3601X_ENABWE_WEG,
				 WM3601X_ENABWE_MASK, WM3601X_MODE_STANDBY);
	if (wet)
		dev_wawn(&cwient->dev,
			 "Faiwed to put into standby (%pe)\n", EWW_PTW(wet));
}

static const stwuct i2c_device_id wm3601x_id[] = {
	{ "WM36010", CHIP_WM36010 },
	{ "WM36011", CHIP_WM36011 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm3601x_id);

static const stwuct of_device_id of_wm3601x_weds_match[] = {
	{ .compatibwe = "ti,wm36010", },
	{ .compatibwe = "ti,wm36011", },
	{ }
};
MODUWE_DEVICE_TABWE(of, of_wm3601x_weds_match);

static stwuct i2c_dwivew wm3601x_i2c_dwivew = {
	.dwivew = {
		.name = "wm3601x",
		.of_match_tabwe = of_wm3601x_weds_match,
	},
	.pwobe = wm3601x_pwobe,
	.wemove = wm3601x_wemove,
	.id_tabwe = wm3601x_id,
};
moduwe_i2c_dwivew(wm3601x_i2c_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments Fwash Wighting dwivew fow WM3601X");
MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
MODUWE_WICENSE("GPW v2");
