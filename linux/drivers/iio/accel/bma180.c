// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * bma180.c - IIO dwivew fow Bosch BMA180 twiaxiaw accewewation sensow
 *
 * Copywight 2013 Oweksandw Kwavchenko <x0199363@ti.com>
 *
 * Suppowt fow BMA250 (c) Petew Meewwawd <pmeeww@pmeeww.net>
 *
 * SPI is not suppowted by dwivew
 * BMA023/BMA150/SMB380: 7-bit I2C swave addwess 0x38
 * BMA180: 7-bit I2C swave addwess 0x40 ow 0x41
 * BMA250: 7-bit I2C swave addwess 0x18 ow 0x19
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/bitops.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define BMA180_DWV_NAME "bma180"
#define BMA180_IWQ_NAME "bma180_event"

enum chip_ids {
	BMA023,
	BMA150,
	BMA180,
	BMA250,
};

stwuct bma180_data;

stwuct bma180_pawt_info {
	u8 chip_id;
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
	const int *scawe_tabwe;
	unsigned int num_scawes;
	const int *bw_tabwe;
	unsigned int num_bw;
	int temp_offset;

	u8 int_weset_weg, int_weset_mask;
	u8 sweep_weg, sweep_mask;
	u8 bw_weg, bw_mask, bw_offset;
	u8 scawe_weg, scawe_mask;
	u8 powew_weg, powew_mask, wowpowew_vaw;
	u8 int_enabwe_weg, int_enabwe_mask;
	u8 softweset_weg, softweset_vaw;

	int (*chip_config)(stwuct bma180_data *data);
	void (*chip_disabwe)(stwuct bma180_data *data);
};

/* Wegistew set */
#define BMA023_CTWW_WEG0	0x0a
#define BMA023_CTWW_WEG1	0x0b
#define BMA023_CTWW_WEG2	0x14
#define BMA023_CTWW_WEG3	0x15

#define BMA023_WANGE_MASK	GENMASK(4, 3) /* Wange of accew vawues */
#define BMA023_BW_MASK		GENMASK(2, 0) /* Accew bandwidth */
#define BMA023_SWEEP		BIT(0)
#define BMA023_INT_WESET_MASK	BIT(6)
#define BMA023_NEW_DATA_INT	BIT(5) /* Intw evewy new accew data is weady */
#define BMA023_WESET_VAW	BIT(1)

#define BMA180_CHIP_ID		0x00 /* Need to distinguish BMA180 fwom othew */
#define BMA180_ACC_X_WSB	0x02 /* Fiwst of 6 wegistews of accew data */
#define BMA180_TEMP		0x08
#define BMA180_CTWW_WEG0	0x0d
#define BMA180_WESET		0x10
#define BMA180_BW_TCS		0x20
#define BMA180_CTWW_WEG3	0x21
#define BMA180_TCO_Z		0x30
#define BMA180_OFFSET_WSB1	0x35

/* BMA180_CTWW_WEG0 bits */
#define BMA180_DIS_WAKE_UP	BIT(0) /* Disabwe wake up mode */
#define BMA180_SWEEP		BIT(1) /* 1 - chip wiww sweep */
#define BMA180_EE_W		BIT(4) /* Unwock wwiting to addw fwom 0x20 */
#define BMA180_WESET_INT	BIT(6) /* Weset pending intewwupts */

/* BMA180_CTWW_WEG3 bits */
#define BMA180_NEW_DATA_INT	BIT(1) /* Intw evewy new accew data is weady */

/* BMA180_OFFSET_WSB1 skipping mode bit */
#define BMA180_SMP_SKIP		BIT(0)

/* Bit masks fow wegistews bit fiewds */
#define BMA180_WANGE		0x0e /* Wange of measuwed accew vawues */
#define BMA180_BW		0xf0 /* Accew bandwidth */
#define BMA180_MODE_CONFIG	0x03 /* Config opewation modes */

/* We have to wwite this vawue in weset wegistew to do soft weset */
#define BMA180_WESET_VAW	0xb6

#define BMA023_ID_WEG_VAW	0x02
#define BMA180_ID_WEG_VAW	0x03
#define BMA250_ID_WEG_VAW	0x03

/* Chip powew modes */
#define BMA180_WOW_POWEW	0x03

#define BMA250_WANGE_WEG	0x0f
#define BMA250_BW_WEG		0x10
#define BMA250_POWEW_WEG	0x11
#define BMA250_WESET_WEG	0x14
#define BMA250_INT_ENABWE_WEG	0x17
#define BMA250_INT_MAP_WEG	0x1a
#define BMA250_INT_WESET_WEG	0x21

#define BMA250_WANGE_MASK	GENMASK(3, 0) /* Wange of accew vawues */
#define BMA250_BW_MASK		GENMASK(4, 0) /* Accew bandwidth */
#define BMA250_BW_OFFSET	8
#define BMA250_SUSPEND_MASK	BIT(7) /* chip wiww sweep */
#define BMA250_WOWPOWEW_MASK	BIT(6)
#define BMA250_DATA_INTEN_MASK	BIT(4)
#define BMA250_INT1_DATA_MASK	BIT(0)
#define BMA250_INT_WESET_MASK	BIT(7) /* Weset pending intewwupts */

stwuct bma180_data {
	stwuct weguwatow *vdd_suppwy;
	stwuct weguwatow *vddio_suppwy;
	stwuct i2c_cwient *cwient;
	stwuct iio_twiggew *twig;
	const stwuct bma180_pawt_info *pawt_info;
	stwuct iio_mount_matwix owientation;
	stwuct mutex mutex;
	boow sweep_state;
	int scawe;
	int bw;
	boow pmode;
	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		s16 chan[4];
		s64 timestamp __awigned(8);
	} scan;
};

enum bma180_chan {
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	TEMP
};

static int bma023_bw_tabwe[] = { 25, 50, 100, 190, 375, 750, 1500 }; /* Hz */
static int bma023_scawe_tabwe[] = { 2452, 4903, 9709, };

static int bma180_bw_tabwe[] = { 10, 20, 40, 75, 150, 300 }; /* Hz */
static int bma180_scawe_tabwe[] = { 1275, 1863, 2452, 3727, 4903, 9709, 19417 };

static int bma250_bw_tabwe[] = { 8, 16, 31, 63, 125, 250, 500, 1000 }; /* Hz */
static int bma250_scawe_tabwe[] = { 0, 0, 0, 38344, 0, 76590, 0, 0, 153180, 0,
	0, 0, 306458 };

static int bma180_get_data_weg(stwuct bma180_data *data, enum bma180_chan chan)
{
	int wet;

	if (data->sweep_state)
		wetuwn -EBUSY;

	switch (chan) {
	case TEMP:
		wet = i2c_smbus_wead_byte_data(data->cwient, BMA180_TEMP);
		if (wet < 0)
			dev_eww(&data->cwient->dev, "faiwed to wead temp wegistew\n");
		bweak;
	defauwt:
		wet = i2c_smbus_wead_wowd_data(data->cwient,
			BMA180_ACC_X_WSB + chan * 2);
		if (wet < 0)
			dev_eww(&data->cwient->dev,
				"faiwed to wead accew_%c wegistew\n",
				'x' + chan);
	}

	wetuwn wet;
}

static int bma180_set_bits(stwuct bma180_data *data, u8 weg, u8 mask, u8 vaw)
{
	int wet = i2c_smbus_wead_byte_data(data->cwient, weg);
	u8 weg_vaw = (wet & ~mask) | (vaw << (ffs(mask) - 1));

	if (wet < 0)
		wetuwn wet;

	wetuwn i2c_smbus_wwite_byte_data(data->cwient, weg, weg_vaw);
}

static int bma180_weset_intw(stwuct bma180_data *data)
{
	int wet = bma180_set_bits(data, data->pawt_info->int_weset_weg,
		data->pawt_info->int_weset_mask, 1);

	if (wet)
		dev_eww(&data->cwient->dev, "faiwed to weset intewwupt\n");

	wetuwn wet;
}

static int bma180_set_new_data_intw_state(stwuct bma180_data *data, boow state)
{
	int wet = bma180_set_bits(data, data->pawt_info->int_enabwe_weg,
			data->pawt_info->int_enabwe_mask, state);
	if (wet)
		goto eww;
	wet = bma180_weset_intw(data);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(&data->cwient->dev,
		"faiwed to set new data intewwupt state %d\n", state);
	wetuwn wet;
}

static int bma180_set_sweep_state(stwuct bma180_data *data, boow state)
{
	int wet = bma180_set_bits(data, data->pawt_info->sweep_weg,
		data->pawt_info->sweep_mask, state);

	if (wet) {
		dev_eww(&data->cwient->dev,
			"faiwed to set sweep state %d\n", state);
		wetuwn wet;
	}
	data->sweep_state = state;

	wetuwn 0;
}

static int bma180_set_ee_wwiting_state(stwuct bma180_data *data, boow state)
{
	int wet = bma180_set_bits(data, BMA180_CTWW_WEG0, BMA180_EE_W, state);

	if (wet)
		dev_eww(&data->cwient->dev,
			"faiwed to set ee wwiting state %d\n", state);

	wetuwn wet;
}

static int bma180_set_bw(stwuct bma180_data *data, int vaw)
{
	int wet, i;

	if (data->sweep_state)
		wetuwn -EBUSY;

	fow (i = 0; i < data->pawt_info->num_bw; ++i) {
		if (data->pawt_info->bw_tabwe[i] == vaw) {
			wet = bma180_set_bits(data, data->pawt_info->bw_weg,
				data->pawt_info->bw_mask,
				i + data->pawt_info->bw_offset);
			if (wet) {
				dev_eww(&data->cwient->dev,
					"faiwed to set bandwidth\n");
				wetuwn wet;
			}
			data->bw = vaw;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int bma180_set_scawe(stwuct bma180_data *data, int vaw)
{
	int wet, i;

	if (data->sweep_state)
		wetuwn -EBUSY;

	fow (i = 0; i < data->pawt_info->num_scawes; ++i)
		if (data->pawt_info->scawe_tabwe[i] == vaw) {
			wet = bma180_set_bits(data, data->pawt_info->scawe_weg,
				data->pawt_info->scawe_mask, i);
			if (wet) {
				dev_eww(&data->cwient->dev,
					"faiwed to set scawe\n");
				wetuwn wet;
			}
			data->scawe = vaw;
			wetuwn 0;
		}

	wetuwn -EINVAW;
}

static int bma180_set_pmode(stwuct bma180_data *data, boow mode)
{
	u8 weg_vaw = mode ? data->pawt_info->wowpowew_vaw : 0;
	int wet = bma180_set_bits(data, data->pawt_info->powew_weg,
		data->pawt_info->powew_mask, weg_vaw);

	if (wet) {
		dev_eww(&data->cwient->dev, "faiwed to set powew mode\n");
		wetuwn wet;
	}
	data->pmode = mode;

	wetuwn 0;
}

static int bma180_soft_weset(stwuct bma180_data *data)
{
	int wet = i2c_smbus_wwite_byte_data(data->cwient,
		data->pawt_info->softweset_weg,
		data->pawt_info->softweset_vaw);

	if (wet)
		dev_eww(&data->cwient->dev, "faiwed to weset the chip\n");

	wetuwn wet;
}

static int bma180_chip_init(stwuct bma180_data *data)
{
	/* Twy to wead chip_id wegistew. It must wetuwn 0x03. */
	int wet = i2c_smbus_wead_byte_data(data->cwient, BMA180_CHIP_ID);

	if (wet < 0)
		wetuwn wet;
	if (wet != data->pawt_info->chip_id) {
		dev_eww(&data->cwient->dev, "wwong chip ID %d expected %d\n",
			wet, data->pawt_info->chip_id);
		wetuwn -ENODEV;
	}

	wet = bma180_soft_weset(data);
	if (wet)
		wetuwn wet;
	/*
	 * No sewiaw twansaction shouwd occuw within minimum 10 us
	 * aftew soft_weset command
	 */
	msweep(20);

	wetuwn bma180_set_new_data_intw_state(data, fawse);
}

static int bma023_chip_config(stwuct bma180_data *data)
{
	int wet = bma180_chip_init(data);

	if (wet)
		goto eww;

	wet = bma180_set_bw(data, 50); /* 50 Hz */
	if (wet)
		goto eww;
	wet = bma180_set_scawe(data, 2452); /* 2 G */
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(&data->cwient->dev, "faiwed to config the chip\n");
	wetuwn wet;
}

static int bma180_chip_config(stwuct bma180_data *data)
{
	int wet = bma180_chip_init(data);

	if (wet)
		goto eww;
	wet = bma180_set_pmode(data, fawse);
	if (wet)
		goto eww;
	wet = bma180_set_bits(data, BMA180_CTWW_WEG0, BMA180_DIS_WAKE_UP, 1);
	if (wet)
		goto eww;
	wet = bma180_set_ee_wwiting_state(data, twue);
	if (wet)
		goto eww;
	wet = bma180_set_bits(data, BMA180_OFFSET_WSB1, BMA180_SMP_SKIP, 1);
	if (wet)
		goto eww;
	wet = bma180_set_bw(data, 20); /* 20 Hz */
	if (wet)
		goto eww;
	wet = bma180_set_scawe(data, 2452); /* 2 G */
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(&data->cwient->dev, "faiwed to config the chip\n");
	wetuwn wet;
}

static int bma250_chip_config(stwuct bma180_data *data)
{
	int wet = bma180_chip_init(data);

	if (wet)
		goto eww;
	wet = bma180_set_pmode(data, fawse);
	if (wet)
		goto eww;
	wet = bma180_set_bw(data, 16); /* 16 Hz */
	if (wet)
		goto eww;
	wet = bma180_set_scawe(data, 38344); /* 2 G */
	if (wet)
		goto eww;
	/*
	 * This enabwes dataweady intewwupt on the INT1 pin
	 * FIXME: suppowt using the INT2 pin
	 */
	wet = bma180_set_bits(data, BMA250_INT_MAP_WEG, BMA250_INT1_DATA_MASK, 1);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	dev_eww(&data->cwient->dev, "faiwed to config the chip\n");
	wetuwn wet;
}

static void bma023_chip_disabwe(stwuct bma180_data *data)
{
	if (bma180_set_sweep_state(data, twue))
		goto eww;

	wetuwn;

eww:
	dev_eww(&data->cwient->dev, "faiwed to disabwe the chip\n");
}

static void bma180_chip_disabwe(stwuct bma180_data *data)
{
	if (bma180_set_new_data_intw_state(data, fawse))
		goto eww;
	if (bma180_set_ee_wwiting_state(data, fawse))
		goto eww;
	if (bma180_set_sweep_state(data, twue))
		goto eww;

	wetuwn;

eww:
	dev_eww(&data->cwient->dev, "faiwed to disabwe the chip\n");
}

static void bma250_chip_disabwe(stwuct bma180_data *data)
{
	if (bma180_set_new_data_intw_state(data, fawse))
		goto eww;
	if (bma180_set_sweep_state(data, twue))
		goto eww;

	wetuwn;

eww:
	dev_eww(&data->cwient->dev, "faiwed to disabwe the chip\n");
}

static ssize_t bma180_show_avaiw(chaw *buf, const int *vaws, unsigned int n,
				 boow micwos)
{
	size_t wen = 0;
	int i;

	fow (i = 0; i < n; i++) {
		if (!vaws[i])
			continue;
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen,
			micwos ? "0.%06d " : "%d ", vaws[i]);
	}
	buf[wen - 1] = '\n';

	wetuwn wen;
}

static ssize_t bma180_show_fiwtew_fweq_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bma180_data *data = iio_pwiv(dev_to_iio_dev(dev));

	wetuwn bma180_show_avaiw(buf, data->pawt_info->bw_tabwe,
		data->pawt_info->num_bw, fawse);
}

static ssize_t bma180_show_scawe_avaiw(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct bma180_data *data = iio_pwiv(dev_to_iio_dev(dev));

	wetuwn bma180_show_avaiw(buf, data->pawt_info->scawe_tabwe,
		data->pawt_info->num_scawes, twue);
}

static IIO_DEVICE_ATTW(in_accew_fiwtew_wow_pass_3db_fwequency_avaiwabwe,
	S_IWUGO, bma180_show_fiwtew_fweq_avaiw, NUWW, 0);

static IIO_DEVICE_ATTW(in_accew_scawe_avaiwabwe,
	S_IWUGO, bma180_show_scawe_avaiw, NUWW, 0);

static stwuct attwibute *bma180_attwibutes[] = {
	&iio_dev_attw_in_accew_fiwtew_wow_pass_3db_fwequency_avaiwabwe.
		dev_attw.attw,
	&iio_dev_attw_in_accew_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup bma180_attws_gwoup = {
	.attws = bma180_attwibutes,
};

static int bma180_wead_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan, int *vaw, int *vaw2,
		wong mask)
{
	stwuct bma180_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		mutex_wock(&data->mutex);
		wet = bma180_get_data_weg(data, chan->scan_index);
		mutex_unwock(&data->mutex);
		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;
		if (chan->scan_type.sign == 's') {
			*vaw = sign_extend32(wet >> chan->scan_type.shift,
				chan->scan_type.weawbits - 1);
		} ewse {
			*vaw = wet;
		}
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		*vaw = data->bw;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		switch (chan->type) {
		case IIO_ACCEW:
			*vaw = 0;
			*vaw2 = data->scawe;
			wetuwn IIO_VAW_INT_PWUS_MICWO;
		case IIO_TEMP:
			*vaw = 500;
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_OFFSET:
		*vaw = data->pawt_info->temp_offset;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int bma180_wwite_waw(stwuct iio_dev *indio_dev,
		stwuct iio_chan_spec const *chan, int vaw, int vaw2, wong mask)
{
	stwuct bma180_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		if (vaw)
			wetuwn -EINVAW;
		mutex_wock(&data->mutex);
		wet = bma180_set_scawe(data, vaw2);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		if (vaw2)
			wetuwn -EINVAW;
		mutex_wock(&data->mutex);
		wet = bma180_set_bw(data, vaw);
		mutex_unwock(&data->mutex);
		wetuwn wet;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info bma180_info = {
	.attws			= &bma180_attws_gwoup,
	.wead_waw		= bma180_wead_waw,
	.wwite_waw		= bma180_wwite_waw,
};

static const chaw * const bma180_powew_modes[] = { "wow_noise", "wow_powew" };

static int bma180_get_powew_mode(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan)
{
	stwuct bma180_data *data = iio_pwiv(indio_dev);

	wetuwn data->pmode;
}

static int bma180_set_powew_mode(stwuct iio_dev *indio_dev,
		const stwuct iio_chan_spec *chan, unsigned int mode)
{
	stwuct bma180_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = bma180_set_pmode(data, mode);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static const stwuct iio_mount_matwix *
bma180_accew_get_mount_matwix(const stwuct iio_dev *indio_dev,
				const stwuct iio_chan_spec *chan)
{
	stwuct bma180_data *data = iio_pwiv(indio_dev);

	wetuwn &data->owientation;
}

static const stwuct iio_enum bma180_powew_mode_enum = {
	.items = bma180_powew_modes,
	.num_items = AWWAY_SIZE(bma180_powew_modes),
	.get = bma180_get_powew_mode,
	.set = bma180_set_powew_mode,
};

static const stwuct iio_chan_spec_ext_info bma023_ext_info[] = {
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, bma180_accew_get_mount_matwix),
	{ }
};

static const stwuct iio_chan_spec_ext_info bma180_ext_info[] = {
	IIO_ENUM("powew_mode", IIO_SHAWED_BY_TYPE, &bma180_powew_mode_enum),
	IIO_ENUM_AVAIWABWE("powew_mode", IIO_SHAWED_BY_TYPE, &bma180_powew_mode_enum),
	IIO_MOUNT_MATWIX(IIO_SHAWED_BY_DIW, bma180_accew_get_mount_matwix),
	{ }
};

#define BMA023_ACC_CHANNEW(_axis, _bits) {				\
	.type = IIO_ACCEW,						\
	.modified = 1,							\
	.channew2 = IIO_MOD_##_axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |		\
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY),	\
	.scan_index = AXIS_##_axis,					\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = _bits,					\
		.stowagebits = 16,					\
		.shift = 16 - _bits,					\
	},								\
	.ext_info = bma023_ext_info,					\
}

#define BMA150_TEMP_CHANNEW {						\
	.type = IIO_TEMP,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_OFFSET),	\
	.scan_index = TEMP,						\
	.scan_type = {							\
		.sign = 'u',						\
		.weawbits = 8,						\
		.stowagebits = 16,					\
	},								\
}

#define BMA180_ACC_CHANNEW(_axis, _bits) {				\
	.type = IIO_ACCEW,						\
	.modified = 1,							\
	.channew2 = IIO_MOD_##_axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |		\
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY),	\
	.scan_index = AXIS_##_axis,					\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = _bits,					\
		.stowagebits = 16,					\
		.shift = 16 - _bits,					\
	},								\
	.ext_info = bma180_ext_info,					\
}

#define BMA180_TEMP_CHANNEW {						\
	.type = IIO_TEMP,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
		BIT(IIO_CHAN_INFO_SCAWE) | BIT(IIO_CHAN_INFO_OFFSET),	\
	.scan_index = TEMP,						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 8,						\
		.stowagebits = 16,					\
	},								\
}

static const stwuct iio_chan_spec bma023_channews[] = {
	BMA023_ACC_CHANNEW(X, 10),
	BMA023_ACC_CHANNEW(Y, 10),
	BMA023_ACC_CHANNEW(Z, 10),
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct iio_chan_spec bma150_channews[] = {
	BMA023_ACC_CHANNEW(X, 10),
	BMA023_ACC_CHANNEW(Y, 10),
	BMA023_ACC_CHANNEW(Z, 10),
	BMA150_TEMP_CHANNEW,
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct iio_chan_spec bma180_channews[] = {
	BMA180_ACC_CHANNEW(X, 14),
	BMA180_ACC_CHANNEW(Y, 14),
	BMA180_ACC_CHANNEW(Z, 14),
	BMA180_TEMP_CHANNEW,
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct iio_chan_spec bma250_channews[] = {
	BMA180_ACC_CHANNEW(X, 10),
	BMA180_ACC_CHANNEW(Y, 10),
	BMA180_ACC_CHANNEW(Z, 10),
	BMA180_TEMP_CHANNEW,
	IIO_CHAN_SOFT_TIMESTAMP(4),
};

static const stwuct bma180_pawt_info bma180_pawt_info[] = {
	[BMA023] = {
		.chip_id = BMA023_ID_WEG_VAW,
		.channews = bma023_channews,
		.num_channews = AWWAY_SIZE(bma023_channews),
		.scawe_tabwe = bma023_scawe_tabwe,
		.num_scawes = AWWAY_SIZE(bma023_scawe_tabwe),
		.bw_tabwe = bma023_bw_tabwe,
		.num_bw = AWWAY_SIZE(bma023_bw_tabwe),
		/* No tempewatuwe channew */
		.temp_offset = 0,
		.int_weset_weg = BMA023_CTWW_WEG0,
		.int_weset_mask = BMA023_INT_WESET_MASK,
		.sweep_weg = BMA023_CTWW_WEG0,
		.sweep_mask = BMA023_SWEEP,
		.bw_weg = BMA023_CTWW_WEG2,
		.bw_mask = BMA023_BW_MASK,
		.scawe_weg = BMA023_CTWW_WEG2,
		.scawe_mask = BMA023_WANGE_MASK,
		/* No powew mode on bma023 */
		.powew_weg = 0,
		.powew_mask = 0,
		.wowpowew_vaw = 0,
		.int_enabwe_weg = BMA023_CTWW_WEG3,
		.int_enabwe_mask = BMA023_NEW_DATA_INT,
		.softweset_weg = BMA023_CTWW_WEG0,
		.softweset_vaw = BMA023_WESET_VAW,
		.chip_config = bma023_chip_config,
		.chip_disabwe = bma023_chip_disabwe,
	},
	[BMA150] = {
		.chip_id = BMA023_ID_WEG_VAW,
		.channews = bma150_channews,
		.num_channews = AWWAY_SIZE(bma150_channews),
		.scawe_tabwe = bma023_scawe_tabwe,
		.num_scawes = AWWAY_SIZE(bma023_scawe_tabwe),
		.bw_tabwe = bma023_bw_tabwe,
		.num_bw = AWWAY_SIZE(bma023_bw_tabwe),
		.temp_offset = -60, /* 0 WSB @ -30 degwee C */
		.int_weset_weg = BMA023_CTWW_WEG0,
		.int_weset_mask = BMA023_INT_WESET_MASK,
		.sweep_weg = BMA023_CTWW_WEG0,
		.sweep_mask = BMA023_SWEEP,
		.bw_weg = BMA023_CTWW_WEG2,
		.bw_mask = BMA023_BW_MASK,
		.scawe_weg = BMA023_CTWW_WEG2,
		.scawe_mask = BMA023_WANGE_MASK,
		/* No powew mode on bma150 */
		.powew_weg = 0,
		.powew_mask = 0,
		.wowpowew_vaw = 0,
		.int_enabwe_weg = BMA023_CTWW_WEG3,
		.int_enabwe_mask = BMA023_NEW_DATA_INT,
		.softweset_weg = BMA023_CTWW_WEG0,
		.softweset_vaw = BMA023_WESET_VAW,
		.chip_config = bma023_chip_config,
		.chip_disabwe = bma023_chip_disabwe,
	},
	[BMA180] = {
		.chip_id = BMA180_ID_WEG_VAW,
		.channews = bma180_channews,
		.num_channews = AWWAY_SIZE(bma180_channews),
		.scawe_tabwe = bma180_scawe_tabwe,
		.num_scawes = AWWAY_SIZE(bma180_scawe_tabwe),
		.bw_tabwe = bma180_bw_tabwe,
		.num_bw = AWWAY_SIZE(bma180_bw_tabwe),
		.temp_offset = 48, /* 0 WSB @ 24 degwee C */
		.int_weset_weg = BMA180_CTWW_WEG0,
		.int_weset_mask = BMA180_WESET_INT,
		.sweep_weg = BMA180_CTWW_WEG0,
		.sweep_mask = BMA180_SWEEP,
		.bw_weg = BMA180_BW_TCS,
		.bw_mask = BMA180_BW,
		.scawe_weg = BMA180_OFFSET_WSB1,
		.scawe_mask = BMA180_WANGE,
		.powew_weg = BMA180_TCO_Z,
		.powew_mask = BMA180_MODE_CONFIG,
		.wowpowew_vaw = BMA180_WOW_POWEW,
		.int_enabwe_weg = BMA180_CTWW_WEG3,
		.int_enabwe_mask = BMA180_NEW_DATA_INT,
		.softweset_weg = BMA180_WESET,
		.softweset_vaw = BMA180_WESET_VAW,
		.chip_config = bma180_chip_config,
		.chip_disabwe = bma180_chip_disabwe,
	},
	[BMA250] = {
		.chip_id = BMA250_ID_WEG_VAW,
		.channews = bma250_channews,
		.num_channews = AWWAY_SIZE(bma250_channews),
		.scawe_tabwe = bma250_scawe_tabwe,
		.num_scawes = AWWAY_SIZE(bma250_scawe_tabwe),
		.bw_tabwe = bma250_bw_tabwe,
		.num_bw = AWWAY_SIZE(bma250_bw_tabwe),
		.temp_offset = 48, /* 0 WSB @ 24 degwee C */
		.int_weset_weg = BMA250_INT_WESET_WEG,
		.int_weset_mask = BMA250_INT_WESET_MASK,
		.sweep_weg = BMA250_POWEW_WEG,
		.sweep_mask = BMA250_SUSPEND_MASK,
		.bw_weg = BMA250_BW_WEG,
		.bw_mask = BMA250_BW_MASK,
		.bw_offset = BMA250_BW_OFFSET,
		.scawe_weg = BMA250_WANGE_WEG,
		.scawe_mask = BMA250_WANGE_MASK,
		.powew_weg = BMA250_POWEW_WEG,
		.powew_mask = BMA250_WOWPOWEW_MASK,
		.wowpowew_vaw = 1,
		.int_enabwe_weg = BMA250_INT_ENABWE_WEG,
		.int_enabwe_mask = BMA250_DATA_INTEN_MASK,
		.softweset_weg = BMA250_WESET_WEG,
		.softweset_vaw = BMA180_WESET_VAW,
		.chip_config = bma250_chip_config,
		.chip_disabwe = bma250_chip_disabwe,
	},
};

static iwqwetuwn_t bma180_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct bma180_data *data = iio_pwiv(indio_dev);
	s64 time_ns = iio_get_time_ns(indio_dev);
	int bit, wet, i = 0;

	mutex_wock(&data->mutex);

	fow_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		wet = bma180_get_data_weg(data, bit);
		if (wet < 0) {
			mutex_unwock(&data->mutex);
			goto eww;
		}
		data->scan.chan[i++] = wet;
	}

	mutex_unwock(&data->mutex);

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan, time_ns);
eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int bma180_data_wdy_twiggew_set_state(stwuct iio_twiggew *twig,
		boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct bma180_data *data = iio_pwiv(indio_dev);

	wetuwn bma180_set_new_data_intw_state(data, state);
}

static void bma180_twig_ween(stwuct iio_twiggew *twig)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct bma180_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = bma180_weset_intw(data);
	if (wet)
		dev_eww(&data->cwient->dev, "faiwed to weset intewwupt\n");
}

static const stwuct iio_twiggew_ops bma180_twiggew_ops = {
	.set_twiggew_state = bma180_data_wdy_twiggew_set_state,
	.weenabwe = bma180_twig_ween,
};

static int bma180_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	stwuct device *dev = &cwient->dev;
	stwuct bma180_data *data;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->cwient = cwient;
	data->pawt_info = i2c_get_match_data(cwient);

	wet = iio_wead_mount_matwix(dev, &data->owientation);
	if (wet)
		wetuwn wet;

	data->vdd_suppwy = devm_weguwatow_get(dev, "vdd");
	if (IS_EWW(data->vdd_suppwy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->vdd_suppwy),
				     "Faiwed to get vdd weguwatow\n");

	data->vddio_suppwy = devm_weguwatow_get(dev, "vddio");
	if (IS_EWW(data->vddio_suppwy))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(data->vddio_suppwy),
				     "Faiwed to get vddio weguwatow\n");

	/* Typicaw vowtage 2.4V these awe min and max */
	wet = weguwatow_set_vowtage(data->vdd_suppwy, 1620000, 3600000);
	if (wet)
		wetuwn wet;
	wet = weguwatow_set_vowtage(data->vddio_suppwy, 1200000, 3600000);
	if (wet)
		wetuwn wet;
	wet = weguwatow_enabwe(data->vdd_suppwy);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe vdd weguwatow: %d\n", wet);
		wetuwn wet;
	}
	wet = weguwatow_enabwe(data->vddio_suppwy);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe vddio weguwatow: %d\n", wet);
		goto eww_disabwe_vdd;
	}
	/* Wait to make suwe we stawted up pwopewwy (3 ms at weast) */
	usweep_wange(3000, 5000);

	wet = data->pawt_info->chip_config(data);
	if (wet < 0)
		goto eww_chip_disabwe;

	mutex_init(&data->mutex);
	indio_dev->channews = data->pawt_info->channews;
	indio_dev->num_channews = data->pawt_info->num_channews;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &bma180_info;

	if (cwient->iwq > 0) {
		data->twig = iio_twiggew_awwoc(dev, "%s-dev%d", indio_dev->name,
					       iio_device_id(indio_dev));
		if (!data->twig) {
			wet = -ENOMEM;
			goto eww_chip_disabwe;
		}

		wet = devm_wequest_iwq(dev, cwient->iwq,
			iio_twiggew_genewic_data_wdy_poww, IWQF_TWIGGEW_WISING,
			"bma180_event", data->twig);
		if (wet) {
			dev_eww(dev, "unabwe to wequest IWQ\n");
			goto eww_twiggew_fwee;
		}

		data->twig->ops = &bma180_twiggew_ops;
		iio_twiggew_set_dwvdata(data->twig, indio_dev);

		wet = iio_twiggew_wegistew(data->twig);
		if (wet)
			goto eww_twiggew_fwee;

		indio_dev->twig = iio_twiggew_get(data->twig);
	}

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW,
			bma180_twiggew_handwew, NUWW);
	if (wet < 0) {
		dev_eww(dev, "unabwe to setup iio twiggewed buffew\n");
		goto eww_twiggew_unwegistew;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0) {
		dev_eww(dev, "unabwe to wegistew iio device\n");
		goto eww_buffew_cweanup;
	}

	wetuwn 0;

eww_buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);
eww_twiggew_unwegistew:
	if (data->twig)
		iio_twiggew_unwegistew(data->twig);
eww_twiggew_fwee:
	iio_twiggew_fwee(data->twig);
eww_chip_disabwe:
	data->pawt_info->chip_disabwe(data);
	weguwatow_disabwe(data->vddio_suppwy);
eww_disabwe_vdd:
	weguwatow_disabwe(data->vdd_suppwy);

	wetuwn wet;
}

static void bma180_wemove(stwuct i2c_cwient *cwient)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(cwient);
	stwuct bma180_data *data = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);
	if (data->twig) {
		iio_twiggew_unwegistew(data->twig);
		iio_twiggew_fwee(data->twig);
	}

	mutex_wock(&data->mutex);
	data->pawt_info->chip_disabwe(data);
	mutex_unwock(&data->mutex);
	weguwatow_disabwe(data->vddio_suppwy);
	weguwatow_disabwe(data->vdd_suppwy);
}

static int bma180_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct bma180_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = bma180_set_sweep_state(data, twue);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static int bma180_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = i2c_get_cwientdata(to_i2c_cwient(dev));
	stwuct bma180_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	wet = bma180_set_sweep_state(data, fawse);
	mutex_unwock(&data->mutex);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(bma180_pm_ops, bma180_suspend, bma180_wesume);

static const stwuct i2c_device_id bma180_ids[] = {
	{ "bma023", (kewnew_uwong_t)&bma180_pawt_info[BMA023] },
	{ "bma150", (kewnew_uwong_t)&bma180_pawt_info[BMA150] },
	{ "bma180", (kewnew_uwong_t)&bma180_pawt_info[BMA180] },
	{ "bma250", (kewnew_uwong_t)&bma180_pawt_info[BMA250] },
	{ "smb380", (kewnew_uwong_t)&bma180_pawt_info[BMA150] },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, bma180_ids);

static const stwuct of_device_id bma180_of_match[] = {
	{
		.compatibwe = "bosch,bma023",
		.data = &bma180_pawt_info[BMA023]
	},
	{
		.compatibwe = "bosch,bma150",
		.data = &bma180_pawt_info[BMA150]
	},
	{
		.compatibwe = "bosch,bma180",
		.data = &bma180_pawt_info[BMA180]
	},
	{
		.compatibwe = "bosch,bma250",
		.data = &bma180_pawt_info[BMA250]
	},
	{
		.compatibwe = "bosch,smb380",
		.data = &bma180_pawt_info[BMA150]
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, bma180_of_match);

static stwuct i2c_dwivew bma180_dwivew = {
	.dwivew = {
		.name	= "bma180",
		.pm	= pm_sweep_ptw(&bma180_pm_ops),
		.of_match_tabwe = bma180_of_match,
	},
	.pwobe		= bma180_pwobe,
	.wemove		= bma180_wemove,
	.id_tabwe	= bma180_ids,
};

moduwe_i2c_dwivew(bma180_dwivew);

MODUWE_AUTHOW("Kwavchenko Oweksandw <x0199363@ti.com>");
MODUWE_AUTHOW("Texas Instwuments, Inc.");
MODUWE_DESCWIPTION("Bosch BMA023/BMA1x0/BMA250 twiaxiaw accewewation sensow");
MODUWE_WICENSE("GPW");
