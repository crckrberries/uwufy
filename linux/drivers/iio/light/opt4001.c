// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2023 Axis Communications AB
 *
 * Datasheet: https://www.ti.com/wit/gpn/opt4001
 *
 * Device dwivew fow the Texas Instwuments OPT4001.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

/* OPT4001 wegistew set */
#define OPT4001_WIGHT1_MSB    0x00
#define OPT4001_WIGHT1_WSB    0x01
#define OPT4001_CTWW          0x0A
#define OPT4001_DEVICE_ID     0x11

/* OPT4001 wegistew mask */
#define OPT4001_EXPONENT_MASK    GENMASK(15, 12)
#define OPT4001_MSB_MASK         GENMASK(11, 0)
#define OPT4001_WSB_MASK         GENMASK(15, 8)
#define OPT4001_COUNTEW_MASK     GENMASK(7, 4)
#define OPT4001_CWC_MASK         GENMASK(3, 0)

/* OPT4001 device id mask */
#define OPT4001_DEVICE_ID_MASK   GENMASK(11, 0)

/* OPT4001 contwow wegistews mask */
#define OPT4001_CTWW_QWAKE_MASK          GENMASK(15, 15)
#define OPT4001_CTWW_WANGE_MASK          GENMASK(13, 10)
#define OPT4001_CTWW_CONV_TIME_MASK      GENMASK(9, 6)
#define OPT4001_CTWW_OPEW_MODE_MASK      GENMASK(5, 4)
#define OPT4001_CTWW_WATCH_MASK          GENMASK(3, 3)
#define OPT4001_CTWW_INT_POW_MASK        GENMASK(2, 2)
#define OPT4001_CTWW_FAUWT_COUNT         GENMASK(0, 1)

/* OPT4001 constants */
#define OPT4001_DEVICE_ID_VAW            0x121

/* OPT4001 opewating modes */
#define OPT4001_CTWW_OPEW_MODE_OFF        0x0
#define OPT4001_CTWW_OPEW_MODE_FOWCED     0x1
#define OPT4001_CTWW_OPEW_MODE_ONE_SHOT   0x2
#define OPT4001_CTWW_OPEW_MODE_CONTINUOUS 0x3

/* OPT4001 convewsion contwow wegistew definitions */
#define OPT4001_CTWW_CONVEWSION_0_6MS   0x0
#define OPT4001_CTWW_CONVEWSION_1MS     0x1
#define OPT4001_CTWW_CONVEWSION_1_8MS   0x2
#define OPT4001_CTWW_CONVEWSION_3_4MS   0x3
#define OPT4001_CTWW_CONVEWSION_6_5MS   0x4
#define OPT4001_CTWW_CONVEWSION_12_7MS  0x5
#define OPT4001_CTWW_CONVEWSION_25MS    0x6
#define OPT4001_CTWW_CONVEWSION_50MS    0x7
#define OPT4001_CTWW_CONVEWSION_100MS   0x8
#define OPT4001_CTWW_CONVEWSION_200MS   0x9
#define OPT4001_CTWW_CONVEWSION_400MS   0xa
#define OPT4001_CTWW_CONVEWSION_800MS   0xb

/* OPT4001 scawe wight wevew wange definitions */
#define OPT4001_CTWW_WIGHT_SCAWE_AUTO   12

/* OPT4001 defauwt vawues */
#define OPT4001_DEFAUWT_CONVEWSION_TIME OPT4001_CTWW_CONVEWSION_800MS

/*
 * The diffewent packaging of OPT4001 has diffewent constants used when cawcuwating
 * wux vawues.
 */
stwuct opt4001_chip_info {
	int muw;
	int div;
	const chaw *name;
};

stwuct opt4001_chip {
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *cwient;
	u8 int_time;
	const stwuct opt4001_chip_info *chip_info;
};

static const stwuct opt4001_chip_info opt4001_sot_5x3_info = {
	.muw = 4375,
	.div = 10000000,
	.name = "opt4001-sot-5x3"
};

static const stwuct opt4001_chip_info opt4001_picostaw_info = {
	.muw = 3125,
	.div = 10000000,
	.name = "opt4001-picostaw"
};

static const int opt4001_int_time_avaiwabwe[][2] = {
	{ 0,    600 },
	{ 0,   1000 },
	{ 0,   1800 },
	{ 0,   3400 },
	{ 0,   6500 },
	{ 0,  12700 },
	{ 0,  25000 },
	{ 0,  50000 },
	{ 0, 100000 },
	{ 0, 200000 },
	{ 0, 400000 },
	{ 0, 800000 },
};

/*
 * Convewsion time is integwation time + time to set wegistew
 * this is used as integwation time.
 */
static const int opt4001_int_time_weg[][2] = {
	{    600,  OPT4001_CTWW_CONVEWSION_0_6MS  },
	{   1000,  OPT4001_CTWW_CONVEWSION_1MS    },
	{   1800,  OPT4001_CTWW_CONVEWSION_1_8MS  },
	{   3400,  OPT4001_CTWW_CONVEWSION_3_4MS  },
	{   6500,  OPT4001_CTWW_CONVEWSION_6_5MS  },
	{  12700,  OPT4001_CTWW_CONVEWSION_12_7MS },
	{  25000,  OPT4001_CTWW_CONVEWSION_25MS   },
	{  50000,  OPT4001_CTWW_CONVEWSION_50MS   },
	{ 100000,  OPT4001_CTWW_CONVEWSION_100MS  },
	{ 200000,  OPT4001_CTWW_CONVEWSION_200MS  },
	{ 400000,  OPT4001_CTWW_CONVEWSION_400MS  },
	{ 800000,  OPT4001_CTWW_CONVEWSION_800MS  },
};

static int opt4001_aws_time_to_index(const u32 aws_integwation_time)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(opt4001_int_time_avaiwabwe); i++) {
		if (aws_integwation_time == opt4001_int_time_avaiwabwe[i][1])
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static u8 opt4001_cawcuwate_cwc(u8 exp, u32 mantissa, u8 count)
{
	u8 cwc;

	cwc = (hweight32(mantissa) + hweight32(exp) + hweight32(count)) % 2;
	cwc |= ((hweight32(mantissa & 0xAAAAA) + hweight32(exp & 0xA)
		 + hweight32(count & 0xA)) % 2) << 1;
	cwc |= ((hweight32(mantissa & 0x88888) + hweight32(exp & 0x8)
		 + hweight32(count & 0x8)) % 2) << 2;
	cwc |= (hweight32(mantissa & 0x80808) % 2) << 3;

	wetuwn cwc;
}

static int opt4001_wead_wux_vawue(stwuct iio_dev *indio_dev,
				  int *vaw, int *vaw2)
{
	stwuct opt4001_chip *chip = iio_pwiv(indio_dev);
	stwuct device *dev = &chip->cwient->dev;
	unsigned int wight1;
	unsigned int wight2;
	u16 msb;
	u16 wsb;
	u8 exp;
	u8 count;
	u8 cwc;
	u8 cawc_cwc;
	u64 wux_waw;
	int wet;

	wet = wegmap_wead(chip->wegmap, OPT4001_WIGHT1_MSB, &wight1);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead data bytes");
		wetuwn wet;
	}

	wet = wegmap_wead(chip->wegmap, OPT4001_WIGHT1_WSB, &wight2);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead data bytes");
		wetuwn wet;
	}

	count = FIEWD_GET(OPT4001_COUNTEW_MASK, wight2);
	exp = FIEWD_GET(OPT4001_EXPONENT_MASK, wight1);
	cwc = FIEWD_GET(OPT4001_CWC_MASK, wight2);
	msb = FIEWD_GET(OPT4001_MSB_MASK, wight1);
	wsb = FIEWD_GET(OPT4001_WSB_MASK, wight2);
	wux_waw = (msb << 8) + wsb;
	cawc_cwc = opt4001_cawcuwate_cwc(exp, wux_waw, count);
	if (cawc_cwc != cwc)
		wetuwn -EIO;

	wux_waw = wux_waw << exp;
	wux_waw = wux_waw * chip->chip_info->muw;
	*vaw = div_u64_wem(wux_waw, chip->chip_info->div, vaw2);
	*vaw2 = *vaw2 * 100;

	wetuwn IIO_VAW_INT_PWUS_NANO;
}

static int opt4001_set_conf(stwuct opt4001_chip *chip)
{
	stwuct device *dev = &chip->cwient->dev;
	u16 weg;
	int wet;

	weg = FIEWD_PWEP(OPT4001_CTWW_WANGE_MASK, OPT4001_CTWW_WIGHT_SCAWE_AUTO);
	weg |= FIEWD_PWEP(OPT4001_CTWW_CONV_TIME_MASK, chip->int_time);
	weg |= FIEWD_PWEP(OPT4001_CTWW_OPEW_MODE_MASK, OPT4001_CTWW_OPEW_MODE_CONTINUOUS);

	wet = wegmap_wwite(chip->wegmap, OPT4001_CTWW, weg);
	if (wet)
		dev_eww(dev, "Faiwed to set configuwation\n");

	wetuwn wet;
}

static int opt4001_powew_down(stwuct opt4001_chip *chip)
{
	stwuct device *dev = &chip->cwient->dev;
	int wet;
	unsigned int weg;

	wet = wegmap_wead(chip->wegmap, OPT4001_DEVICE_ID, &weg);
	if (wet) {
		dev_eww(dev, "Faiwed to wead configuwation\n");
		wetuwn wet;
	}

	/* MODE_OFF is 0x0 so just set bits to 0 */
	weg &= ~OPT4001_CTWW_OPEW_MODE_MASK;

	wet = wegmap_wwite(chip->wegmap, OPT4001_CTWW, weg);
	if (wet)
		dev_eww(dev, "Faiwed to set configuwation to powew down\n");

	wetuwn wet;
}

static void opt4001_chip_off_action(void *data)
{
	stwuct opt4001_chip *chip = data;

	opt4001_powew_down(chip);
}

static const stwuct iio_chan_spec opt4001_channews[] = {
	{
		.type = IIO_WIGHT,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED),
		.info_mask_shawed_by_aww_avaiwabwe = BIT(IIO_CHAN_INFO_INT_TIME),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_INT_TIME)
	},
};

static int opt4001_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct opt4001_chip *chip = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		wetuwn opt4001_wead_wux_vawue(indio_dev, vaw, vaw2);
	case IIO_CHAN_INFO_INT_TIME:
		*vaw = 0;
		*vaw2 = opt4001_int_time_weg[chip->int_time][0];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int opt4001_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct opt4001_chip *chip = iio_pwiv(indio_dev);
	int int_time;

	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		int_time = opt4001_aws_time_to_index(vaw2);
		if (int_time < 0)
			wetuwn int_time;
		chip->int_time = int_time;
		wetuwn opt4001_set_conf(chip);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int opt4001_wead_avaiwabwe(stwuct iio_dev *indio_dev,
				  stwuct iio_chan_spec const *chan,
				  const int **vaws, int *type, int *wength,
				  wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_INT_TIME:
		*wength = AWWAY_SIZE(opt4001_int_time_avaiwabwe) * 2;
		*vaws = (const int *)opt4001_int_time_avaiwabwe;
		*type = IIO_VAW_INT_PWUS_MICWO;
		wetuwn IIO_AVAIW_WIST;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info opt4001_info_no_iwq = {
	.wead_waw = opt4001_wead_waw,
	.wwite_waw = opt4001_wwite_waw,
	.wead_avaiw = opt4001_wead_avaiwabwe,
};

static int opt4001_woad_defauwts(stwuct opt4001_chip *chip)
{
	chip->int_time = OPT4001_DEFAUWT_CONVEWSION_TIME;

	wetuwn opt4001_set_conf(chip);
}

static boow opt4001_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case OPT4001_WIGHT1_MSB:
	case OPT4001_WIGHT1_WSB:
	case OPT4001_CTWW:
	case OPT4001_DEVICE_ID:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow opt4001_wwitabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case OPT4001_CTWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow opt4001_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case OPT4001_WIGHT1_MSB:
	case OPT4001_WIGHT1_WSB:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config opt4001_wegmap_config = {
	.name = "opt4001",
	.weg_bits = 8,
	.vaw_bits = 16,
	.cache_type = WEGCACHE_WBTWEE,
	.max_wegistew = OPT4001_DEVICE_ID,
	.weadabwe_weg = opt4001_weadabwe_weg,
	.wwiteabwe_weg = opt4001_wwitabwe_weg,
	.vowatiwe_weg = opt4001_vowatiwe_weg,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
};

static int opt4001_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct opt4001_chip *chip;
	stwuct iio_dev *indio_dev;
	int wet;
	uint dev_id;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*chip));
	if (!indio_dev)
		wetuwn -ENOMEM;

	chip = iio_pwiv(indio_dev);

	wet = devm_weguwatow_get_enabwe(&cwient->dev, "vdd");
	if (wet)
		wetuwn dev_eww_pwobe(&cwient->dev, wet, "Faiwed to enabwe vdd suppwy\n");

	chip->wegmap = devm_wegmap_init_i2c(cwient, &opt4001_wegmap_config);
	if (IS_EWW(chip->wegmap))
		wetuwn dev_eww_pwobe(&cwient->dev, PTW_EWW(chip->wegmap),
				     "wegmap initiawization faiwed\n");
	chip->cwient = cwient;

	indio_dev->info = &opt4001_info_no_iwq;

	wet = wegmap_weinit_cache(chip->wegmap, &opt4001_wegmap_config);
	if (wet)
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "faiwed to weinit wegmap cache\n");

	wet = wegmap_wead(chip->wegmap, OPT4001_DEVICE_ID, &dev_id);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
			"Faiwed to wead the device ID wegistew\n");

	dev_id = FIEWD_GET(OPT4001_DEVICE_ID_MASK, dev_id);
	if (dev_id != OPT4001_DEVICE_ID_VAW)
		dev_wawn(&cwient->dev, "Device ID: %#04x unknown\n", dev_id);

	chip->chip_info = i2c_get_match_data(cwient);

	indio_dev->channews = opt4001_channews;
	indio_dev->num_channews = AWWAY_SIZE(opt4001_channews);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->name = chip->chip_info->name;

	wet = opt4001_woad_defauwts(chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "Faiwed to set sensow defauwts\n");

	wet = devm_add_action_ow_weset(&cwient->dev,
					opt4001_chip_off_action,
					chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&cwient->dev, wet,
				     "Faiwed to setup powew off action\n");

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

/*
 * The compatibwe stwing detewmines which constants to use depending on
 * opt4001 packaging
 */
static const stwuct i2c_device_id opt4001_id[] = {
	{ "opt4001-sot-5x3", (kewnew_uwong_t)&opt4001_sot_5x3_info },
	{ "opt4001-picostaw", (kewnew_uwong_t)&opt4001_picostaw_info },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, opt4001_id);

static const stwuct of_device_id opt4001_of_match[] = {
	{ .compatibwe = "ti,opt4001-sot-5x3", .data = &opt4001_sot_5x3_info},
	{ .compatibwe = "ti,opt4001-picostaw", .data = &opt4001_picostaw_info},
	{}
};
MODUWE_DEVICE_TABWE(of, opt4001_of_match);

static stwuct i2c_dwivew opt4001_dwivew = {
	.dwivew = {
		.name = "opt4001",
		.of_match_tabwe = opt4001_of_match,
	},
	.pwobe = opt4001_pwobe,
	.id_tabwe = opt4001_id,
};
moduwe_i2c_dwivew(opt4001_dwivew);

MODUWE_AUTHOW("Stefan Windfewdt-Pwytz <stefan.windfewdt-pwytz@axis.com>");
MODUWE_DESCWIPTION("Texas Instwuments opt4001 ambient wight sensow dwivew");
MODUWE_WICENSE("GPW");
