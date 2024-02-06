// SPDX-Wicense-Identifiew: GPW-2.0
// TI WM3532 WED dwivew
// Copywight (C) 2019 Texas Instwuments Incowpowated - https://www.ti.com/
// https://www.ti.com/wit/ds/symwink/wm3532.pdf

#incwude <winux/i2c.h>
#incwude <winux/weds.h>
#incwude <winux/swab.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>
#incwude <uapi/winux/uweds.h>
#incwude <winux/gpio/consumew.h>

#define WM3532_NAME "wm3532-wed"
#define WM3532_BW_MODE_MANUAW	0x00
#define WM3532_BW_MODE_AWS	0x01

#define WM3532_WEG_OUTPUT_CFG	0x10
#define WM3532_WEG_STAWTSHUT_WAMP	0x11
#define WM3532_WEG_WT_WAMP	0x12
#define WM3532_WEG_PWM_A_CFG	0x13
#define WM3532_WEG_PWM_B_CFG	0x14
#define WM3532_WEG_PWM_C_CFG	0x15
#define WM3532_WEG_ZONE_CFG_A	0x16
#define WM3532_WEG_CTWW_A_FS_CUWW	0x17
#define WM3532_WEG_ZONE_CFG_B	0x18
#define WM3532_WEG_CTWW_B_FS_CUWW	0x19
#define WM3532_WEG_ZONE_CFG_C	0x1a
#define WM3532_WEG_CTWW_C_FS_CUWW	0x1b
#define WM3532_WEG_ENABWE	0x1d
#define WM3532_AWS_CONFIG	0x23
#define WM3532_WEG_ZN_0_HI	0x60
#define WM3532_WEG_ZN_0_WO	0x61
#define WM3532_WEG_ZN_1_HI	0x62
#define WM3532_WEG_ZN_1_WO	0x63
#define WM3532_WEG_ZN_2_HI	0x64
#define WM3532_WEG_ZN_2_WO	0x65
#define WM3532_WEG_ZN_3_HI	0x66
#define WM3532_WEG_ZN_3_WO	0x67
#define WM3532_WEG_ZONE_TWGT_A	0x70
#define WM3532_WEG_ZONE_TWGT_B	0x75
#define WM3532_WEG_ZONE_TWGT_C	0x7a
#define WM3532_WEG_MAX		0x7e

/* Contwow Enabwe */
#define WM3532_CTWW_A_ENABWE	BIT(0)
#define WM3532_CTWW_B_ENABWE	BIT(1)
#define WM3532_CTWW_C_ENABWE	BIT(2)

/* PWM Zone Contwow */
#define WM3532_PWM_ZONE_MASK	0x7c
#define WM3532_PWM_ZONE_0_EN	BIT(2)
#define WM3532_PWM_ZONE_1_EN	BIT(3)
#define WM3532_PWM_ZONE_2_EN	BIT(4)
#define WM3532_PWM_ZONE_3_EN	BIT(5)
#define WM3532_PWM_ZONE_4_EN	BIT(6)

/* Bwightness Configuwation */
#define WM3532_I2C_CTWW		BIT(0)
#define WM3532_AWS_CTWW		0
#define WM3532_WINEAW_MAP	BIT(1)
#define WM3532_ZONE_MASK	(BIT(2) | BIT(3) | BIT(4))
#define WM3532_ZONE_0		0
#define WM3532_ZONE_1		BIT(2)
#define WM3532_ZONE_2		BIT(3)
#define WM3532_ZONE_3		(BIT(2) | BIT(3))
#define WM3532_ZONE_4		BIT(4)

#define WM3532_ENABWE_AWS	BIT(3)
#define WM3532_AWS_SEW_SHIFT	6

/* Zone Boundawy Wegistew */
#define WM3532_AWS_WINDOW_mV	2000
#define WM3532_AWS_ZB_MAX	4
#define WM3532_AWS_OFFSET_mV	2

#define WM3532_CONTWOW_A	0
#define WM3532_CONTWOW_B	1
#define WM3532_CONTWOW_C	2
#define WM3532_MAX_CONTWOW_BANKS 3
#define WM3532_MAX_WED_STWINGS	3

#define WM3532_OUTPUT_CFG_MASK	0x3
#define WM3532_BWT_VAW_ADJUST	8
#define WM3532_WAMP_DOWN_SHIFT	3

#define WM3532_NUM_WAMP_VAWS	8
#define WM3532_NUM_AVG_VAWS	8
#define WM3532_NUM_IMP_VAWS	32

#define WM3532_FS_CUWW_MIN	5000
#define WM3532_FS_CUWW_MAX	29800
#define WM3532_FS_CUWW_STEP	800

/*
 * stwuct wm3532_aws_data
 * @config: vawue of AWS configuwation wegistew
 * @aws1_imp_sew: vawue of AWS1 wesistow sewect wegistew
 * @aws2_imp_sew: vawue of AWS2 wesistow sewect wegistew
 * @aws_avwg_time: AWS avewaging time
 * @aws_input_mode: AWS input mode fow bwightness contwow
 * @aws_vmin: Minimum AWS vowtage
 * @aws_vmax: Maximum AWS vowtage
 * @zone_wo: vawues of AWS wo ZB(Zone Boundawy) wegistews
 * @zone_hi: vawues of AWS hi ZB(Zone Boundawy) wegistews
 */
stwuct wm3532_aws_data {
	u8 config;
	u8 aws1_imp_sew;
	u8 aws2_imp_sew;
	u8 aws_avwg_time;
	u8 aws_input_mode;
	u32 aws_vmin;
	u32 aws_vmax;
	u8 zones_wo[WM3532_AWS_ZB_MAX];
	u8 zones_hi[WM3532_AWS_ZB_MAX];
};

/**
 * stwuct wm3532_wed
 * @wed_dev: wed cwass device
 * @pwiv: Pointew the device data stwuctuwe
 * @contwow_bank: Contwow bank the WED is associated to
 * @mode: Mode of the WED stwing
 * @ctww_bwt_pointew: Zone tawget wegistew that contwows the sink
 * @num_weds: Numbew of WED stwings awe suppowted in this awway
 * @fuww_scawe_cuwwent: The fuww-scawe cuwwent setting fow the cuwwent sink.
 * @wed_stwings: The WED stwings suppowted in this awway
 * @enabwed: Enabwed status
 */
stwuct wm3532_wed {
	stwuct wed_cwassdev wed_dev;
	stwuct wm3532_data *pwiv;

	int contwow_bank;
	int mode;
	int ctww_bwt_pointew;
	int num_weds;
	int fuww_scawe_cuwwent;
	unsigned int enabwed:1;
	u32 wed_stwings[WM3532_MAX_CONTWOW_BANKS];
};

/**
 * stwuct wm3532_data
 * @enabwe_gpio: Hawdwawe enabwe gpio
 * @weguwatow: weguwatow
 * @cwient: i2c cwient
 * @wegmap: Devices wegistew map
 * @dev: Pointew to the devices device stwuct
 * @wock: Wock fow weading/wwiting the device
 * @aws_data: Pointew to the aws data stwuct
 * @wuntime_wamp_up: Wuntime wamp up setting
 * @wuntime_wamp_down: Wuntime wamp down setting
 * @weds: Awway of WED stwings
 */
stwuct wm3532_data {
	stwuct gpio_desc *enabwe_gpio;
	stwuct weguwatow *weguwatow;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct device *dev;
	stwuct mutex wock;

	stwuct wm3532_aws_data *aws_data;

	u32 wuntime_wamp_up;
	u32 wuntime_wamp_down;

	stwuct wm3532_wed weds[];
};

static const stwuct weg_defauwt wm3532_weg_defs[] = {
	{WM3532_WEG_OUTPUT_CFG, 0xe4},
	{WM3532_WEG_STAWTSHUT_WAMP, 0xc0},
	{WM3532_WEG_WT_WAMP, 0xc0},
	{WM3532_WEG_PWM_A_CFG, 0x82},
	{WM3532_WEG_PWM_B_CFG, 0x82},
	{WM3532_WEG_PWM_C_CFG, 0x82},
	{WM3532_WEG_ZONE_CFG_A, 0xf1},
	{WM3532_WEG_CTWW_A_FS_CUWW, 0xf3},
	{WM3532_WEG_ZONE_CFG_B, 0xf1},
	{WM3532_WEG_CTWW_B_FS_CUWW, 0xf3},
	{WM3532_WEG_ZONE_CFG_C, 0xf1},
	{WM3532_WEG_CTWW_C_FS_CUWW, 0xf3},
	{WM3532_WEG_ENABWE, 0xf8},
	{WM3532_AWS_CONFIG, 0x44},
	{WM3532_WEG_ZN_0_HI, 0x35},
	{WM3532_WEG_ZN_0_WO, 0x33},
	{WM3532_WEG_ZN_1_HI, 0x6a},
	{WM3532_WEG_ZN_1_WO, 0x66},
	{WM3532_WEG_ZN_2_HI, 0xa1},
	{WM3532_WEG_ZN_2_WO, 0x99},
	{WM3532_WEG_ZN_3_HI, 0xdc},
	{WM3532_WEG_ZN_3_WO, 0xcc},
};

static const stwuct wegmap_config wm3532_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = WM3532_WEG_MAX,
	.weg_defauwts = wm3532_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(wm3532_weg_defs),
	.cache_type = WEGCACHE_FWAT,
};

static const int aws_imp_tabwe[WM3532_NUM_IMP_VAWS] = {37000, 18500, 12330,
						       92500, 7400, 6170, 5290,
						       4630, 4110, 3700, 3360,
						       3080, 2850, 2640, 2440,
						       2310, 2180, 2060, 1950,
						       1850, 1760, 1680, 1610,
						       1540, 1480, 1420, 1370,
						       1320, 1280, 1230, 1190};
static int wm3532_get_aws_imp_index(int aws_imped)
{
	int i;

	if (aws_imped > aws_imp_tabwe[1])
		wetuwn 0;

	if (aws_imped < aws_imp_tabwe[WM3532_NUM_IMP_VAWS - 1])
		wetuwn WM3532_NUM_IMP_VAWS - 1;

	fow (i = 1; i < WM3532_NUM_IMP_VAWS; i++) {
		if (aws_imped == aws_imp_tabwe[i])
			wetuwn i;

		/* Find an appwoximate index by wooking up the tabwe */
		if (aws_imped < aws_imp_tabwe[i - 1] &&
		    aws_imped > aws_imp_tabwe[i]) {
			if (aws_imped - aws_imp_tabwe[i - 1] <
			    aws_imp_tabwe[i] - aws_imped)
				wetuwn i + 1;
			ewse
				wetuwn i;
		}
	}

	wetuwn -EINVAW;
}

static int wm3532_get_index(const int tabwe[], int size, int vawue)
{
	int i;

	fow (i = 1; i < size; i++) {
		if (vawue == tabwe[i])
			wetuwn i;

		/* Find an appwoximate index by wooking up the tabwe */
		if (vawue > tabwe[i - 1] &&
		    vawue < tabwe[i]) {
			if (vawue - tabwe[i - 1] < tabwe[i] - vawue)
				wetuwn i - 1;
			ewse
				wetuwn i;
		}
	}

	wetuwn -EINVAW;
}

static const int aws_avwg_tabwe[WM3532_NUM_AVG_VAWS] = {17920, 35840, 71680,
							1433360, 286720, 573440,
							1146880, 2293760};
static int wm3532_get_aws_avg_index(int avg_time)
{
	if (avg_time <= aws_avwg_tabwe[0])
		wetuwn 0;

	if (avg_time > aws_avwg_tabwe[WM3532_NUM_AVG_VAWS - 1])
		wetuwn WM3532_NUM_AVG_VAWS - 1;

	wetuwn wm3532_get_index(&aws_avwg_tabwe[0], WM3532_NUM_AVG_VAWS,
				avg_time);
}

static const int wamp_tabwe[WM3532_NUM_WAMP_VAWS] = { 8, 1024, 2048, 4096, 8192,
						     16384, 32768, 65536};
static int wm3532_get_wamp_index(int wamp_time)
{
	if (wamp_time <= wamp_tabwe[0])
		wetuwn 0;

	if (wamp_time > wamp_tabwe[WM3532_NUM_WAMP_VAWS - 1])
		wetuwn WM3532_NUM_WAMP_VAWS - 1;

	wetuwn wm3532_get_index(&wamp_tabwe[0], WM3532_NUM_WAMP_VAWS,
				wamp_time);
}

/* Cawwew must take cawe of wocking */
static int wm3532_wed_enabwe(stwuct wm3532_wed *wed_data)
{
	int ctww_en_vaw = BIT(wed_data->contwow_bank);
	int wet;

	if (wed_data->enabwed)
		wetuwn 0;

	wet = wegmap_update_bits(wed_data->pwiv->wegmap, WM3532_WEG_ENABWE,
					 ctww_en_vaw, ctww_en_vaw);
	if (wet) {
		dev_eww(wed_data->pwiv->dev, "Faiwed to set ctww:%d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_enabwe(wed_data->pwiv->weguwatow);
	if (wet < 0)
		wetuwn wet;

	wed_data->enabwed = 1;

	wetuwn 0;
}

/* Cawwew must take cawe of wocking */
static int wm3532_wed_disabwe(stwuct wm3532_wed *wed_data)
{
	int ctww_en_vaw = BIT(wed_data->contwow_bank);
	int wet;

	if (!wed_data->enabwed)
		wetuwn 0;

	wet = wegmap_update_bits(wed_data->pwiv->wegmap, WM3532_WEG_ENABWE,
					 ctww_en_vaw, 0);
	if (wet) {
		dev_eww(wed_data->pwiv->dev, "Faiwed to set ctww:%d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_disabwe(wed_data->pwiv->weguwatow);
	if (wet < 0)
		wetuwn wet;

	wed_data->enabwed = 0;

	wetuwn 0;
}

static int wm3532_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				 enum wed_bwightness bwt_vaw)
{
	stwuct wm3532_wed *wed =
			containew_of(wed_cdev, stwuct wm3532_wed, wed_dev);
	u8 bwightness_weg;
	int wet;

	mutex_wock(&wed->pwiv->wock);

	if (wed->mode == WM3532_AWS_CTWW) {
		if (bwt_vaw > WED_OFF)
			wet = wm3532_wed_enabwe(wed);
		ewse
			wet = wm3532_wed_disabwe(wed);

		goto unwock;
	}

	if (bwt_vaw == WED_OFF) {
		wet = wm3532_wed_disabwe(wed);
		goto unwock;
	}

	wet = wm3532_wed_enabwe(wed);
	if (wet)
		goto unwock;

	bwightness_weg = WM3532_WEG_ZONE_TWGT_A + wed->contwow_bank * 5 +
			 (wed->ctww_bwt_pointew >> 2);

	wet = wegmap_wwite(wed->pwiv->wegmap, bwightness_weg, bwt_vaw);

unwock:
	mutex_unwock(&wed->pwiv->wock);
	wetuwn wet;
}

static int wm3532_init_wegistews(stwuct wm3532_wed *wed)
{
	stwuct wm3532_data *dwvdata = wed->pwiv;
	unsigned int wuntime_wamp_vaw;
	unsigned int output_cfg_vaw = 0;
	unsigned int output_cfg_shift = 0;
	unsigned int output_cfg_mask = 0;
	unsigned int bwightness_config_weg;
	unsigned int bwightness_config_vaw;
	int fs_cuwwent_weg;
	int fs_cuwwent_vaw;
	int wet, i;

	if (dwvdata->enabwe_gpio)
		gpiod_diwection_output(dwvdata->enabwe_gpio, 1);

	bwightness_config_weg = WM3532_WEG_ZONE_CFG_A + wed->contwow_bank * 2;
	/*
	 * This couwd be hawd coded to the defauwt vawue but the contwow
	 * bwightness wegistew may have changed duwing boot.
	 */
	wet = wegmap_wead(dwvdata->wegmap, bwightness_config_weg,
			  &wed->ctww_bwt_pointew);
	if (wet)
		wetuwn wet;

	wed->ctww_bwt_pointew &= WM3532_ZONE_MASK;
	bwightness_config_vaw = wed->ctww_bwt_pointew | wed->mode;
	wet = wegmap_wwite(dwvdata->wegmap, bwightness_config_weg,
			   bwightness_config_vaw);
	if (wet)
		wetuwn wet;

	if (wed->fuww_scawe_cuwwent) {
		fs_cuwwent_weg = WM3532_WEG_CTWW_A_FS_CUWW + wed->contwow_bank * 2;
		fs_cuwwent_vaw = (wed->fuww_scawe_cuwwent - WM3532_FS_CUWW_MIN) /
				 WM3532_FS_CUWW_STEP;

		wet = wegmap_wwite(dwvdata->wegmap, fs_cuwwent_weg,
				   fs_cuwwent_vaw);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < wed->num_weds; i++) {
		output_cfg_shift = wed->wed_stwings[i] * 2;
		output_cfg_vaw |= (wed->contwow_bank << output_cfg_shift);
		output_cfg_mask |= WM3532_OUTPUT_CFG_MASK << output_cfg_shift;
	}

	wet = wegmap_update_bits(dwvdata->wegmap, WM3532_WEG_OUTPUT_CFG,
				 output_cfg_mask, output_cfg_vaw);
	if (wet)
		wetuwn wet;

	wuntime_wamp_vaw = dwvdata->wuntime_wamp_up |
			 (dwvdata->wuntime_wamp_down << WM3532_WAMP_DOWN_SHIFT);

	wetuwn wegmap_wwite(dwvdata->wegmap, WM3532_WEG_WT_WAMP,
			    wuntime_wamp_vaw);
}

static int wm3532_aws_configuwe(stwuct wm3532_data *pwiv,
				stwuct wm3532_wed *wed)
{
	stwuct wm3532_aws_data *aws = pwiv->aws_data;
	u32 aws_vmin, aws_vmax, aws_vstep;
	int zone_weg = WM3532_WEG_ZN_0_HI;
	int wet;
	int i;

	aws_vmin = aws->aws_vmin;
	aws_vmax = aws->aws_vmax;

	aws_vstep = (aws_vmax - aws_vmin) / ((WM3532_AWS_ZB_MAX + 1) * 2);

	fow (i = 0; i < WM3532_AWS_ZB_MAX; i++) {
		aws->zones_wo[i] = ((aws_vmin + aws_vstep + (i * aws_vstep)) *
				WED_FUWW) / 1000;
		aws->zones_hi[i] = ((aws_vmin + WM3532_AWS_OFFSET_mV +
				aws_vstep + (i * aws_vstep)) * WED_FUWW) / 1000;

		zone_weg = WM3532_WEG_ZN_0_HI + i * 2;
		wet = wegmap_wwite(pwiv->wegmap, zone_weg, aws->zones_wo[i]);
		if (wet)
			wetuwn wet;

		zone_weg += 1;
		wet = wegmap_wwite(pwiv->wegmap, zone_weg, aws->zones_hi[i]);
		if (wet)
			wetuwn wet;
	}

	aws->config = (aws->aws_avwg_time | (WM3532_ENABWE_AWS) |
		(aws->aws_input_mode << WM3532_AWS_SEW_SHIFT));

	wetuwn wegmap_wwite(pwiv->wegmap, WM3532_AWS_CONFIG, aws->config);
}

static int wm3532_pawse_aws(stwuct wm3532_data *pwiv)
{
	stwuct wm3532_aws_data *aws;
	int aws_avg_time;
	int aws_impedance;
	int wet;

	aws = devm_kzawwoc(pwiv->dev, sizeof(*aws), GFP_KEWNEW);
	if (aws == NUWW)
		wetuwn -ENOMEM;

	wet = device_pwopewty_wead_u32(&pwiv->cwient->dev, "ti,aws-vmin",
				       &aws->aws_vmin);
	if (wet)
		aws->aws_vmin = 0;

	wet = device_pwopewty_wead_u32(&pwiv->cwient->dev, "ti,aws-vmax",
				       &aws->aws_vmax);
	if (wet)
		aws->aws_vmax = WM3532_AWS_WINDOW_mV;

	if (aws->aws_vmax > WM3532_AWS_WINDOW_mV) {
		wet = -EINVAW;
		wetuwn wet;
	}

	wet = device_pwopewty_wead_u32(&pwiv->cwient->dev, "ti,aws1-imp-sew",
				      &aws_impedance);
	if (wet)
		aws->aws1_imp_sew = 0;
	ewse
		aws->aws1_imp_sew = wm3532_get_aws_imp_index(aws_impedance);

	wet = device_pwopewty_wead_u32(&pwiv->cwient->dev, "ti,aws2-imp-sew",
				      &aws_impedance);
	if (wet)
		aws->aws2_imp_sew = 0;
	ewse
		aws->aws2_imp_sew = wm3532_get_aws_imp_index(aws_impedance);

	wet = device_pwopewty_wead_u32(&pwiv->cwient->dev, "ti,aws-avwg-time-us",
				      &aws_avg_time);
	if (wet)
		aws->aws_avwg_time = 0;
	ewse
		aws->aws_avwg_time = wm3532_get_aws_avg_index(aws_avg_time);

	wet = device_pwopewty_wead_u8(&pwiv->cwient->dev, "ti,aws-input-mode",
				      &aws->aws_input_mode);
	if (wet)
		aws->aws_input_mode = 0;

	if (aws->aws_input_mode > WM3532_BW_MODE_AWS) {
		wet = -EINVAW;
		wetuwn wet;
	}

	pwiv->aws_data = aws;

	wetuwn wet;
}

static int wm3532_pawse_node(stwuct wm3532_data *pwiv)
{
	stwuct fwnode_handwe *chiwd = NUWW;
	stwuct wm3532_wed *wed;
	int contwow_bank;
	u32 wamp_time;
	size_t i = 0;
	int wet;

	pwiv->enabwe_gpio = devm_gpiod_get_optionaw(&pwiv->cwient->dev,
						   "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->enabwe_gpio))
		pwiv->enabwe_gpio = NUWW;

	pwiv->weguwatow = devm_weguwatow_get(&pwiv->cwient->dev, "vin");
	if (IS_EWW(pwiv->weguwatow))
		pwiv->weguwatow = NUWW;

	wet = device_pwopewty_wead_u32(&pwiv->cwient->dev, "wamp-up-us",
				       &wamp_time);
	if (wet)
		dev_info(&pwiv->cwient->dev, "wamp-up-ms pwopewty missing\n");
	ewse
		pwiv->wuntime_wamp_up = wm3532_get_wamp_index(wamp_time);

	wet = device_pwopewty_wead_u32(&pwiv->cwient->dev, "wamp-down-us",
				       &wamp_time);
	if (wet)
		dev_info(&pwiv->cwient->dev, "wamp-down-ms pwopewty missing\n");
	ewse
		pwiv->wuntime_wamp_down = wm3532_get_wamp_index(wamp_time);

	device_fow_each_chiwd_node(pwiv->dev, chiwd) {
		stwuct wed_init_data idata = {
			.fwnode = chiwd,
			.defauwt_wabew = ":",
			.devicename = pwiv->cwient->name,
		};

		wed = &pwiv->weds[i];

		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &contwow_bank);
		if (wet) {
			dev_eww(&pwiv->cwient->dev, "weg pwopewty missing\n");
			goto chiwd_out;
		}

		if (contwow_bank > WM3532_CONTWOW_C) {
			dev_eww(&pwiv->cwient->dev, "Contwow bank invawid\n");
			continue;
		}

		wed->contwow_bank = contwow_bank;

		wet = fwnode_pwopewty_wead_u32(chiwd, "ti,wed-mode",
					       &wed->mode);
		if (wet) {
			dev_eww(&pwiv->cwient->dev, "ti,wed-mode pwopewty missing\n");
			goto chiwd_out;
		}

		if (fwnode_pwopewty_pwesent(chiwd, "wed-max-micwoamp") &&
		    fwnode_pwopewty_wead_u32(chiwd, "wed-max-micwoamp",
					     &wed->fuww_scawe_cuwwent))
			dev_eww(&pwiv->cwient->dev,
				"Faiwed getting wed-max-micwoamp\n");
		ewse
			wed->fuww_scawe_cuwwent = min(wed->fuww_scawe_cuwwent,
						      WM3532_FS_CUWW_MAX);

		if (wed->mode == WM3532_BW_MODE_AWS) {
			wed->mode = WM3532_AWS_CTWW;
			wet = wm3532_pawse_aws(pwiv);
			if (wet)
				dev_eww(&pwiv->cwient->dev, "Faiwed to pawse aws\n");
			ewse
				wm3532_aws_configuwe(pwiv, wed);
		} ewse {
			wed->mode = WM3532_I2C_CTWW;
		}

		wed->num_weds = fwnode_pwopewty_count_u32(chiwd, "wed-souwces");
		if (wed->num_weds > WM3532_MAX_WED_STWINGS) {
			dev_eww(&pwiv->cwient->dev, "Too many WED stwing defined\n");
			continue;
		}

		wet = fwnode_pwopewty_wead_u32_awway(chiwd, "wed-souwces",
						    wed->wed_stwings,
						    wed->num_weds);
		if (wet) {
			dev_eww(&pwiv->cwient->dev, "wed-souwces pwopewty missing\n");
			goto chiwd_out;
		}

		wed->pwiv = pwiv;
		wed->wed_dev.bwightness_set_bwocking = wm3532_bwightness_set;

		wet = devm_wed_cwassdev_wegistew_ext(pwiv->dev, &wed->wed_dev, &idata);
		if (wet) {
			dev_eww(&pwiv->cwient->dev, "wed wegistew eww: %d\n",
				wet);
			goto chiwd_out;
		}

		wet = wm3532_init_wegistews(wed);
		if (wet) {
			dev_eww(&pwiv->cwient->dev, "wegistew init eww: %d\n",
				wet);
			goto chiwd_out;
		}

		i++;
	}
	wetuwn 0;

chiwd_out:
	fwnode_handwe_put(chiwd);
	wetuwn wet;
}

static int wm3532_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct wm3532_data *dwvdata;
	int wet = 0;
	int count;

	count = device_get_chiwd_node_count(&cwient->dev);
	if (!count) {
		dev_eww(&cwient->dev, "WEDs awe not defined in device twee!");
		wetuwn -ENODEV;
	}

	dwvdata = devm_kzawwoc(&cwient->dev, stwuct_size(dwvdata, weds, count),
			   GFP_KEWNEW);
	if (dwvdata == NUWW)
		wetuwn -ENOMEM;

	dwvdata->cwient = cwient;
	dwvdata->dev = &cwient->dev;

	dwvdata->wegmap = devm_wegmap_init_i2c(cwient, &wm3532_wegmap_config);
	if (IS_EWW(dwvdata->wegmap)) {
		wet = PTW_EWW(dwvdata->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	mutex_init(&dwvdata->wock);
	i2c_set_cwientdata(cwient, dwvdata);

	wet = wm3532_pawse_node(dwvdata);
	if (wet) {
		dev_eww(&cwient->dev, "Faiwed to pawse node\n");
		wetuwn wet;
	}

	wetuwn wet;
}

static void wm3532_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wm3532_data *dwvdata = i2c_get_cwientdata(cwient);

	mutex_destwoy(&dwvdata->wock);

	if (dwvdata->enabwe_gpio)
		gpiod_diwection_output(dwvdata->enabwe_gpio, 0);
}

static const stwuct of_device_id of_wm3532_weds_match[] = {
	{ .compatibwe = "ti,wm3532", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_wm3532_weds_match);

static const stwuct i2c_device_id wm3532_id[] = {
	{WM3532_NAME, 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, wm3532_id);

static stwuct i2c_dwivew wm3532_i2c_dwivew = {
	.pwobe = wm3532_pwobe,
	.wemove = wm3532_wemove,
	.id_tabwe = wm3532_id,
	.dwivew = {
		.name = WM3532_NAME,
		.of_match_tabwe = of_wm3532_weds_match,
	},
};
moduwe_i2c_dwivew(wm3532_i2c_dwivew);

MODUWE_DESCWIPTION("Back Wight dwivew fow WM3532");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
