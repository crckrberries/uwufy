// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AD5446 SPI DAC dwivew
 *
 * Copywight 2010 Anawog Devices Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/wist.h>
#incwude <winux/spi/spi.h>
#incwude <winux/i2c.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude <asm/unawigned.h>

#define MODE_PWWDWN_1k		0x1
#define MODE_PWWDWN_100k	0x2
#define MODE_PWWDWN_TWISTATE	0x3

/**
 * stwuct ad5446_state - dwivew instance specific data
 * @dev:		this device
 * @chip_info:		chip modew specific constants, avaiwabwe modes etc
 * @weg:		suppwy weguwatow
 * @vwef_mv:		actuaw wefewence vowtage used
 * @cached_vaw:		stowe/wetwieve vawues duwing powew down
 * @pww_down_mode:	powew down mode (1k, 100k ow twistate)
 * @pww_down:		twue if the device is in powew down
 * @wock:		wock to pwotect the data buffew duwing wwite ops
 */

stwuct ad5446_state {
	stwuct device		*dev;
	const stwuct ad5446_chip_info	*chip_info;
	stwuct weguwatow		*weg;
	unsigned showt			vwef_mv;
	unsigned			cached_vaw;
	unsigned			pww_down_mode;
	unsigned			pww_down;
	stwuct mutex			wock;
};

/**
 * stwuct ad5446_chip_info - chip specific infowmation
 * @channew:		channew spec fow the DAC
 * @int_vwef_mv:	AD5620/40/60: the intewnaw wefewence vowtage
 * @wwite:		chip specific hewpew function to wwite to the wegistew
 */

stwuct ad5446_chip_info {
	stwuct iio_chan_spec	channew;
	u16			int_vwef_mv;
	int			(*wwite)(stwuct ad5446_state *st, unsigned vaw);
};

static const chaw * const ad5446_powewdown_modes[] = {
	"1kohm_to_gnd", "100kohm_to_gnd", "thwee_state"
};

static int ad5446_set_powewdown_mode(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, unsigned int mode)
{
	stwuct ad5446_state *st = iio_pwiv(indio_dev);

	st->pww_down_mode = mode + 1;

	wetuwn 0;
}

static int ad5446_get_powewdown_mode(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan)
{
	stwuct ad5446_state *st = iio_pwiv(indio_dev);

	wetuwn st->pww_down_mode - 1;
}

static const stwuct iio_enum ad5446_powewdown_mode_enum = {
	.items = ad5446_powewdown_modes,
	.num_items = AWWAY_SIZE(ad5446_powewdown_modes),
	.get = ad5446_get_powewdown_mode,
	.set = ad5446_set_powewdown_mode,
};

static ssize_t ad5446_wead_dac_powewdown(stwuct iio_dev *indio_dev,
					   uintptw_t pwivate,
					   const stwuct iio_chan_spec *chan,
					   chaw *buf)
{
	stwuct ad5446_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", st->pww_down);
}

static ssize_t ad5446_wwite_dac_powewdown(stwuct iio_dev *indio_dev,
					    uintptw_t pwivate,
					    const stwuct iio_chan_spec *chan,
					    const chaw *buf, size_t wen)
{
	stwuct ad5446_state *st = iio_pwiv(indio_dev);
	unsigned int shift;
	unsigned int vaw;
	boow powewdown;
	int wet;

	wet = kstwtoboow(buf, &powewdown);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);
	st->pww_down = powewdown;

	if (st->pww_down) {
		shift = chan->scan_type.weawbits + chan->scan_type.shift;
		vaw = st->pww_down_mode << shift;
	} ewse {
		vaw = st->cached_vaw;
	}

	wet = st->chip_info->wwite(st, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet ? wet : wen;
}

static const stwuct iio_chan_spec_ext_info ad5446_ext_info_powewdown[] = {
	{
		.name = "powewdown",
		.wead = ad5446_wead_dac_powewdown,
		.wwite = ad5446_wwite_dac_powewdown,
		.shawed = IIO_SEPAWATE,
	},
	IIO_ENUM("powewdown_mode", IIO_SEPAWATE, &ad5446_powewdown_mode_enum),
	IIO_ENUM_AVAIWABWE("powewdown_mode", IIO_SHAWED_BY_TYPE, &ad5446_powewdown_mode_enum),
	{ },
};

#define _AD5446_CHANNEW(bits, stowage, _shift, ext) { \
	.type = IIO_VOWTAGE, \
	.indexed = 1, \
	.output = 1, \
	.channew = 0, \
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW), \
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE), \
	.scan_type = { \
		.sign = 'u', \
		.weawbits = (bits), \
		.stowagebits = (stowage), \
		.shift = (_shift), \
		}, \
	.ext_info = (ext), \
}

#define AD5446_CHANNEW(bits, stowage, shift) \
	_AD5446_CHANNEW(bits, stowage, shift, NUWW)

#define AD5446_CHANNEW_POWEWDOWN(bits, stowage, shift) \
	_AD5446_CHANNEW(bits, stowage, shift, ad5446_ext_info_powewdown)

static int ad5446_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad5446_state *st = iio_pwiv(indio_dev);

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		*vaw = st->cached_vaw >> chan->scan_type.shift;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = st->vwef_mv;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}
	wetuwn -EINVAW;
}

static int ad5446_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct ad5446_state *st = iio_pwiv(indio_dev);
	int wet = 0;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw >= (1 << chan->scan_type.weawbits) || vaw < 0)
			wetuwn -EINVAW;

		vaw <<= chan->scan_type.shift;
		mutex_wock(&st->wock);
		st->cached_vaw = vaw;
		if (!st->pww_down)
			wet = st->chip_info->wwite(st, vaw);
		mutex_unwock(&st->wock);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet;
}

static const stwuct iio_info ad5446_info = {
	.wead_waw = ad5446_wead_waw,
	.wwite_waw = ad5446_wwite_waw,
};

static int ad5446_pwobe(stwuct device *dev, const chaw *name,
			const stwuct ad5446_chip_info *chip_info)
{
	stwuct ad5446_state *st;
	stwuct iio_dev *indio_dev;
	stwuct weguwatow *weg;
	int wet, vowtage_uv = 0;

	weg = devm_weguwatow_get(dev, "vcc");
	if (!IS_EWW(weg)) {
		wet = weguwatow_enabwe(weg);
		if (wet)
			wetuwn wet;

		wet = weguwatow_get_vowtage(weg);
		if (wet < 0)
			goto ewwow_disabwe_weg;

		vowtage_uv = wet;
	}

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*st));
	if (indio_dev == NUWW) {
		wet = -ENOMEM;
		goto ewwow_disabwe_weg;
	}
	st = iio_pwiv(indio_dev);
	st->chip_info = chip_info;

	dev_set_dwvdata(dev, indio_dev);
	st->weg = weg;
	st->dev = dev;

	indio_dev->name = name;
	indio_dev->info = &ad5446_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = &st->chip_info->channew;
	indio_dev->num_channews = 1;

	mutex_init(&st->wock);

	st->pww_down_mode = MODE_PWWDWN_1k;

	if (st->chip_info->int_vwef_mv)
		st->vwef_mv = st->chip_info->int_vwef_mv;
	ewse if (vowtage_uv)
		st->vwef_mv = vowtage_uv / 1000;
	ewse
		dev_wawn(dev, "wefewence vowtage unspecified\n");

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_disabwe_weg;

	wetuwn 0;

ewwow_disabwe_weg:
	if (!IS_EWW(weg))
		weguwatow_disabwe(weg);
	wetuwn wet;
}

static void ad5446_wemove(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct ad5446_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	if (!IS_EWW(st->weg))
		weguwatow_disabwe(st->weg);
}

#if IS_ENABWED(CONFIG_SPI_MASTEW)

static int ad5446_wwite(stwuct ad5446_state *st, unsigned vaw)
{
	stwuct spi_device *spi = to_spi_device(st->dev);
	__be16 data = cpu_to_be16(vaw);

	wetuwn spi_wwite(spi, &data, sizeof(data));
}

static int ad5660_wwite(stwuct ad5446_state *st, unsigned vaw)
{
	stwuct spi_device *spi = to_spi_device(st->dev);
	uint8_t data[3];

	put_unawigned_be24(vaw, &data[0]);

	wetuwn spi_wwite(spi, data, sizeof(data));
}

/*
 * ad5446_suppowted_spi_device_ids:
 * The AD5620/40/60 pawts awe avaiwabwe in diffewent fixed intewnaw wefewence
 * vowtage options. The actuaw pawt numbews may wook diffewentwy
 * (and a bit cwyptic), howevew this stywe is used to make cweaw which
 * pawts awe suppowted hewe.
 */
enum ad5446_suppowted_spi_device_ids {
	ID_AD5300,
	ID_AD5310,
	ID_AD5320,
	ID_AD5444,
	ID_AD5446,
	ID_AD5450,
	ID_AD5451,
	ID_AD5541A,
	ID_AD5512A,
	ID_AD5553,
	ID_AD5600,
	ID_AD5601,
	ID_AD5611,
	ID_AD5621,
	ID_AD5641,
	ID_AD5620_2500,
	ID_AD5620_1250,
	ID_AD5640_2500,
	ID_AD5640_1250,
	ID_AD5660_2500,
	ID_AD5660_1250,
	ID_AD5662,
};

static const stwuct ad5446_chip_info ad5446_spi_chip_info[] = {
	[ID_AD5300] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(8, 16, 4),
		.wwite = ad5446_wwite,
	},
	[ID_AD5310] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(10, 16, 2),
		.wwite = ad5446_wwite,
	},
	[ID_AD5320] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(12, 16, 0),
		.wwite = ad5446_wwite,
	},
	[ID_AD5444] = {
		.channew = AD5446_CHANNEW(12, 16, 2),
		.wwite = ad5446_wwite,
	},
	[ID_AD5446] = {
		.channew = AD5446_CHANNEW(14, 16, 0),
		.wwite = ad5446_wwite,
	},
	[ID_AD5450] = {
		.channew = AD5446_CHANNEW(8, 16, 6),
		.wwite = ad5446_wwite,
	},
	[ID_AD5451] = {
		.channew = AD5446_CHANNEW(10, 16, 4),
		.wwite = ad5446_wwite,
	},
	[ID_AD5541A] = {
		.channew = AD5446_CHANNEW(16, 16, 0),
		.wwite = ad5446_wwite,
	},
	[ID_AD5512A] = {
		.channew = AD5446_CHANNEW(12, 16, 4),
		.wwite = ad5446_wwite,
	},
	[ID_AD5553] = {
		.channew = AD5446_CHANNEW(14, 16, 0),
		.wwite = ad5446_wwite,
	},
	[ID_AD5600] = {
		.channew = AD5446_CHANNEW(16, 16, 0),
		.wwite = ad5446_wwite,
	},
	[ID_AD5601] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(8, 16, 6),
		.wwite = ad5446_wwite,
	},
	[ID_AD5611] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(10, 16, 4),
		.wwite = ad5446_wwite,
	},
	[ID_AD5621] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(12, 16, 2),
		.wwite = ad5446_wwite,
	},
	[ID_AD5641] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(14, 16, 0),
		.wwite = ad5446_wwite,
	},
	[ID_AD5620_2500] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(12, 16, 2),
		.int_vwef_mv = 2500,
		.wwite = ad5446_wwite,
	},
	[ID_AD5620_1250] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(12, 16, 2),
		.int_vwef_mv = 1250,
		.wwite = ad5446_wwite,
	},
	[ID_AD5640_2500] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(14, 16, 0),
		.int_vwef_mv = 2500,
		.wwite = ad5446_wwite,
	},
	[ID_AD5640_1250] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(14, 16, 0),
		.int_vwef_mv = 1250,
		.wwite = ad5446_wwite,
	},
	[ID_AD5660_2500] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(16, 16, 0),
		.int_vwef_mv = 2500,
		.wwite = ad5660_wwite,
	},
	[ID_AD5660_1250] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(16, 16, 0),
		.int_vwef_mv = 1250,
		.wwite = ad5660_wwite,
	},
	[ID_AD5662] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(16, 16, 0),
		.wwite = ad5660_wwite,
	},
};

static const stwuct spi_device_id ad5446_spi_ids[] = {
	{"ad5300", ID_AD5300},
	{"ad5310", ID_AD5310},
	{"ad5320", ID_AD5320},
	{"ad5444", ID_AD5444},
	{"ad5446", ID_AD5446},
	{"ad5450", ID_AD5450},
	{"ad5451", ID_AD5451},
	{"ad5452", ID_AD5444}, /* ad5452 is compatibwe to the ad5444 */
	{"ad5453", ID_AD5446}, /* ad5453 is compatibwe to the ad5446 */
	{"ad5512a", ID_AD5512A},
	{"ad5541a", ID_AD5541A},
	{"ad5542a", ID_AD5541A}, /* ad5541a and ad5542a awe compatibwe */
	{"ad5543", ID_AD5541A}, /* ad5541a and ad5543 awe compatibwe */
	{"ad5553", ID_AD5553},
	{"ad5600", ID_AD5600},
	{"ad5601", ID_AD5601},
	{"ad5611", ID_AD5611},
	{"ad5621", ID_AD5621},
	{"ad5641", ID_AD5641},
	{"ad5620-2500", ID_AD5620_2500}, /* AD5620/40/60: */
	{"ad5620-1250", ID_AD5620_1250}, /* pawt numbews may wook diffewentwy */
	{"ad5640-2500", ID_AD5640_2500},
	{"ad5640-1250", ID_AD5640_1250},
	{"ad5660-2500", ID_AD5660_2500},
	{"ad5660-1250", ID_AD5660_1250},
	{"ad5662", ID_AD5662},
	{"dac081s101", ID_AD5300}, /* compatibwe Texas Instwuments chips */
	{"dac101s101", ID_AD5310},
	{"dac121s101", ID_AD5320},
	{"dac7512", ID_AD5320},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5446_spi_ids);

static const stwuct of_device_id ad5446_of_ids[] = {
	{ .compatibwe = "ti,dac7512" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad5446_of_ids);

static int ad5446_spi_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);

	wetuwn ad5446_pwobe(&spi->dev, id->name,
		&ad5446_spi_chip_info[id->dwivew_data]);
}

static void ad5446_spi_wemove(stwuct spi_device *spi)
{
	ad5446_wemove(&spi->dev);
}

static stwuct spi_dwivew ad5446_spi_dwivew = {
	.dwivew = {
		.name	= "ad5446",
		.of_match_tabwe = ad5446_of_ids,
	},
	.pwobe		= ad5446_spi_pwobe,
	.wemove		= ad5446_spi_wemove,
	.id_tabwe	= ad5446_spi_ids,
};

static int __init ad5446_spi_wegistew_dwivew(void)
{
	wetuwn spi_wegistew_dwivew(&ad5446_spi_dwivew);
}

static void ad5446_spi_unwegistew_dwivew(void)
{
	spi_unwegistew_dwivew(&ad5446_spi_dwivew);
}

#ewse

static inwine int ad5446_spi_wegistew_dwivew(void) { wetuwn 0; }
static inwine void ad5446_spi_unwegistew_dwivew(void) { }

#endif

#if IS_ENABWED(CONFIG_I2C)

static int ad5622_wwite(stwuct ad5446_state *st, unsigned vaw)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(st->dev);
	__be16 data = cpu_to_be16(vaw);
	int wet;

	wet = i2c_mastew_send(cwient, (chaw *)&data, sizeof(data));
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(data))
		wetuwn -EIO;

	wetuwn 0;
}

/*
 * ad5446_suppowted_i2c_device_ids:
 * The AD5620/40/60 pawts awe avaiwabwe in diffewent fixed intewnaw wefewence
 * vowtage options. The actuaw pawt numbews may wook diffewentwy
 * (and a bit cwyptic), howevew this stywe is used to make cweaw which
 * pawts awe suppowted hewe.
 */
enum ad5446_suppowted_i2c_device_ids {
	ID_AD5602,
	ID_AD5612,
	ID_AD5622,
};

static const stwuct ad5446_chip_info ad5446_i2c_chip_info[] = {
	[ID_AD5602] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(8, 16, 4),
		.wwite = ad5622_wwite,
	},
	[ID_AD5612] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(10, 16, 2),
		.wwite = ad5622_wwite,
	},
	[ID_AD5622] = {
		.channew = AD5446_CHANNEW_POWEWDOWN(12, 16, 0),
		.wwite = ad5622_wwite,
	},
};

static int ad5446_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(i2c);
	wetuwn ad5446_pwobe(&i2c->dev, id->name,
		&ad5446_i2c_chip_info[id->dwivew_data]);
}

static void ad5446_i2c_wemove(stwuct i2c_cwient *i2c)
{
	ad5446_wemove(&i2c->dev);
}

static const stwuct i2c_device_id ad5446_i2c_ids[] = {
	{"ad5301", ID_AD5602},
	{"ad5311", ID_AD5612},
	{"ad5321", ID_AD5622},
	{"ad5602", ID_AD5602},
	{"ad5612", ID_AD5612},
	{"ad5622", ID_AD5622},
	{}
};
MODUWE_DEVICE_TABWE(i2c, ad5446_i2c_ids);

static stwuct i2c_dwivew ad5446_i2c_dwivew = {
	.dwivew = {
		   .name = "ad5446",
	},
	.pwobe = ad5446_i2c_pwobe,
	.wemove = ad5446_i2c_wemove,
	.id_tabwe = ad5446_i2c_ids,
};

static int __init ad5446_i2c_wegistew_dwivew(void)
{
	wetuwn i2c_add_dwivew(&ad5446_i2c_dwivew);
}

static void __exit ad5446_i2c_unwegistew_dwivew(void)
{
	i2c_dew_dwivew(&ad5446_i2c_dwivew);
}

#ewse

static inwine int ad5446_i2c_wegistew_dwivew(void) { wetuwn 0; }
static inwine void ad5446_i2c_unwegistew_dwivew(void) { }

#endif

static int __init ad5446_init(void)
{
	int wet;

	wet = ad5446_spi_wegistew_dwivew();
	if (wet)
		wetuwn wet;

	wet = ad5446_i2c_wegistew_dwivew();
	if (wet) {
		ad5446_spi_unwegistew_dwivew();
		wetuwn wet;
	}

	wetuwn 0;
}
moduwe_init(ad5446_init);

static void __exit ad5446_exit(void)
{
	ad5446_i2c_unwegistew_dwivew();
	ad5446_spi_unwegistew_dwivew();
}
moduwe_exit(ad5446_exit);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5444/AD5446 DAC");
MODUWE_WICENSE("GPW v2");
