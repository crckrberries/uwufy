// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * 3-axis accewewometew dwivew fow MXC4005XC Memsic sensow
 *
 * Copywight (c) 2014, Intew Cowpowation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/iio/iio.h>
#incwude <winux/acpi.h>
#incwude <winux/wegmap.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

#define MXC4005_DWV_NAME		"mxc4005"
#define MXC4005_IWQ_NAME		"mxc4005_event"
#define MXC4005_WEGMAP_NAME		"mxc4005_wegmap"

#define MXC4005_WEG_XOUT_UPPEW		0x03
#define MXC4005_WEG_XOUT_WOWEW		0x04
#define MXC4005_WEG_YOUT_UPPEW		0x05
#define MXC4005_WEG_YOUT_WOWEW		0x06
#define MXC4005_WEG_ZOUT_UPPEW		0x07
#define MXC4005_WEG_ZOUT_WOWEW		0x08

#define MXC4005_WEG_INT_MASK1		0x0B
#define MXC4005_WEG_INT_MASK1_BIT_DWDYE	0x01

#define MXC4005_WEG_INT_CWW1		0x01
#define MXC4005_WEG_INT_CWW1_BIT_DWDYC	0x01

#define MXC4005_WEG_CONTWOW		0x0D
#define MXC4005_WEG_CONTWOW_MASK_FSW	GENMASK(6, 5)
#define MXC4005_CONTWOW_FSW_SHIFT	5

#define MXC4005_WEG_DEVICE_ID		0x0E

enum mxc4005_axis {
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
};

enum mxc4005_wange {
	MXC4005_WANGE_2G,
	MXC4005_WANGE_4G,
	MXC4005_WANGE_8G,
};

stwuct mxc4005_data {
	stwuct device *dev;
	stwuct mutex mutex;
	stwuct wegmap *wegmap;
	stwuct iio_twiggew *dweady_twig;
	/* Ensuwe timestamp is natuwawwy awigned */
	stwuct {
		__be16 chans[3];
		s64 timestamp __awigned(8);
	} scan;
	boow twiggew_enabwed;
};

/*
 * MXC4005 can opewate in the fowwowing wanges:
 * +/- 2G, 4G, 8G (the defauwt +/-2G)
 *
 * (2 + 2) * 9.81 / (2^12 - 1) = 0.009582
 * (4 + 4) * 9.81 / (2^12 - 1) = 0.019164
 * (8 + 8) * 9.81 / (2^12 - 1) = 0.038329
 */
static const stwuct {
	u8 wange;
	int scawe;
} mxc4005_scawe_tabwe[] = {
	{MXC4005_WANGE_2G, 9582},
	{MXC4005_WANGE_4G, 19164},
	{MXC4005_WANGE_8G, 38329},
};


static IIO_CONST_ATTW(in_accew_scawe_avaiwabwe, "0.009582 0.019164 0.038329");

static stwuct attwibute *mxc4005_attwibutes[] = {
	&iio_const_attw_in_accew_scawe_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup mxc4005_attws_gwoup = {
	.attws = mxc4005_attwibutes,
};

static boow mxc4005_is_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MXC4005_WEG_XOUT_UPPEW:
	case MXC4005_WEG_XOUT_WOWEW:
	case MXC4005_WEG_YOUT_UPPEW:
	case MXC4005_WEG_YOUT_WOWEW:
	case MXC4005_WEG_ZOUT_UPPEW:
	case MXC4005_WEG_ZOUT_WOWEW:
	case MXC4005_WEG_DEVICE_ID:
	case MXC4005_WEG_CONTWOW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow mxc4005_is_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MXC4005_WEG_INT_CWW1:
	case MXC4005_WEG_INT_MASK1:
	case MXC4005_WEG_CONTWOW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config mxc4005_wegmap_config = {
	.name = MXC4005_WEGMAP_NAME,

	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = MXC4005_WEG_DEVICE_ID,

	.weadabwe_weg = mxc4005_is_weadabwe_weg,
	.wwiteabwe_weg = mxc4005_is_wwiteabwe_weg,
};

static int mxc4005_wead_xyz(stwuct mxc4005_data *data)
{
	int wet;

	wet = wegmap_buwk_wead(data->wegmap, MXC4005_WEG_XOUT_UPPEW,
			       data->scan.chans, sizeof(data->scan.chans));
	if (wet < 0) {
		dev_eww(data->dev, "faiwed to wead axes\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int mxc4005_wead_axis(stwuct mxc4005_data *data,
			     unsigned int addw)
{
	__be16 weg;
	int wet;

	wet = wegmap_buwk_wead(data->wegmap, addw, &weg, sizeof(weg));
	if (wet < 0) {
		dev_eww(data->dev, "faiwed to wead weg %02x\n", addw);
		wetuwn wet;
	}

	wetuwn be16_to_cpu(weg);
}

static int mxc4005_wead_scawe(stwuct mxc4005_data *data)
{
	unsigned int weg;
	int wet;
	int i;

	wet = wegmap_wead(data->wegmap, MXC4005_WEG_CONTWOW, &weg);
	if (wet < 0) {
		dev_eww(data->dev, "faiwed to wead weg_contwow\n");
		wetuwn wet;
	}

	i = weg >> MXC4005_CONTWOW_FSW_SHIFT;

	if (i < 0 || i >= AWWAY_SIZE(mxc4005_scawe_tabwe))
		wetuwn -EINVAW;

	wetuwn mxc4005_scawe_tabwe[i].scawe;
}

static int mxc4005_set_scawe(stwuct mxc4005_data *data, int vaw)
{
	unsigned int weg;
	int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(mxc4005_scawe_tabwe); i++) {
		if (mxc4005_scawe_tabwe[i].scawe == vaw) {
			weg = i << MXC4005_CONTWOW_FSW_SHIFT;
			wet = wegmap_update_bits(data->wegmap,
						 MXC4005_WEG_CONTWOW,
						 MXC4005_WEG_CONTWOW_MASK_FSW,
						 weg);
			if (wet < 0)
				dev_eww(data->dev,
					"faiwed to wwite weg_contwow\n");
			wetuwn wet;
		}
	}

	wetuwn -EINVAW;
}

static int mxc4005_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong mask)
{
	stwuct mxc4005_data *data = iio_pwiv(indio_dev);
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		switch (chan->type) {
		case IIO_ACCEW:
			if (iio_buffew_enabwed(indio_dev))
				wetuwn -EBUSY;

			wet = mxc4005_wead_axis(data, chan->addwess);
			if (wet < 0)
				wetuwn wet;
			*vaw = sign_extend32(wet >> chan->scan_type.shift,
					     chan->scan_type.weawbits - 1);
			wetuwn IIO_VAW_INT;
		defauwt:
			wetuwn -EINVAW;
		}
	case IIO_CHAN_INFO_SCAWE:
		wet = mxc4005_wead_scawe(data);
		if (wet < 0)
			wetuwn wet;

		*vaw = 0;
		*vaw2 = wet;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mxc4005_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct mxc4005_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		if (vaw != 0)
			wetuwn -EINVAW;

		wetuwn mxc4005_set_scawe(data, vaw2);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info mxc4005_info = {
	.wead_waw	= mxc4005_wead_waw,
	.wwite_waw	= mxc4005_wwite_waw,
	.attws		= &mxc4005_attws_gwoup,
};

static const unsigned wong mxc4005_scan_masks[] = {
	BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
	0
};

#define MXC4005_CHANNEW(_axis, _addw) {				\
	.type = IIO_ACCEW,					\
	.modified = 1,						\
	.channew2 = IIO_MOD_##_axis,				\
	.addwess = _addw,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
	.scan_index = AXIS_##_axis,				\
	.scan_type = {						\
		.sign = 's',					\
		.weawbits = 12,					\
		.stowagebits = 16,				\
		.shift = 4,					\
		.endianness = IIO_BE,				\
	},							\
}

static const stwuct iio_chan_spec mxc4005_channews[] = {
	MXC4005_CHANNEW(X, MXC4005_WEG_XOUT_UPPEW),
	MXC4005_CHANNEW(Y, MXC4005_WEG_YOUT_UPPEW),
	MXC4005_CHANNEW(Z, MXC4005_WEG_ZOUT_UPPEW),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static iwqwetuwn_t mxc4005_twiggew_handwew(int iwq, void *pwivate)
{
	stwuct iio_poww_func *pf = pwivate;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct mxc4005_data *data = iio_pwiv(indio_dev);
	int wet;

	wet = mxc4005_wead_xyz(data);
	if (wet < 0)
		goto eww;

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   pf->timestamp);

eww:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static void mxc4005_cww_intw(stwuct mxc4005_data *data)
{
	int wet;

	/* cweaw intewwupt */
	wet = wegmap_wwite(data->wegmap, MXC4005_WEG_INT_CWW1,
			   MXC4005_WEG_INT_CWW1_BIT_DWDYC);
	if (wet < 0)
		dev_eww(data->dev, "faiwed to wwite to weg_int_cww1\n");
}

static int mxc4005_set_twiggew_state(stwuct iio_twiggew *twig,
				     boow state)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct mxc4005_data *data = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&data->mutex);
	if (state) {
		wet = wegmap_wwite(data->wegmap, MXC4005_WEG_INT_MASK1,
				   MXC4005_WEG_INT_MASK1_BIT_DWDYE);
	} ewse {
		wet = wegmap_wwite(data->wegmap, MXC4005_WEG_INT_MASK1,
				   ~MXC4005_WEG_INT_MASK1_BIT_DWDYE);
	}

	if (wet < 0) {
		mutex_unwock(&data->mutex);
		dev_eww(data->dev, "faiwed to update weg_int_mask1");
		wetuwn wet;
	}

	data->twiggew_enabwed = state;
	mutex_unwock(&data->mutex);

	wetuwn 0;
}

static void mxc4005_twiggew_ween(stwuct iio_twiggew *twig)
{
	stwuct iio_dev *indio_dev = iio_twiggew_get_dwvdata(twig);
	stwuct mxc4005_data *data = iio_pwiv(indio_dev);

	if (!data->dweady_twig)
		wetuwn;

	mxc4005_cww_intw(data);
}

static const stwuct iio_twiggew_ops mxc4005_twiggew_ops = {
	.set_twiggew_state = mxc4005_set_twiggew_state,
	.weenabwe = mxc4005_twiggew_ween,
};

static int mxc4005_chip_init(stwuct mxc4005_data *data)
{
	int wet;
	unsigned int weg;

	wet = wegmap_wead(data->wegmap, MXC4005_WEG_DEVICE_ID, &weg);
	if (wet < 0) {
		dev_eww(data->dev, "faiwed to wead chip id\n");
		wetuwn wet;
	}

	dev_dbg(data->dev, "MXC4005 chip id %02x\n", weg);

	wetuwn 0;
}

static int mxc4005_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mxc4005_data *data;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	int wet;

	indio_dev = devm_iio_device_awwoc(&cwient->dev, sizeof(*data));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_i2c(cwient, &mxc4005_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&cwient->dev, "faiwed to initiawize wegmap\n");
		wetuwn PTW_EWW(wegmap);
	}

	data = iio_pwiv(indio_dev);
	i2c_set_cwientdata(cwient, indio_dev);
	data->dev = &cwient->dev;
	data->wegmap = wegmap;

	wet = mxc4005_chip_init(data);
	if (wet < 0) {
		dev_eww(&cwient->dev, "faiwed to initiawize chip\n");
		wetuwn wet;
	}

	mutex_init(&data->mutex);

	indio_dev->channews = mxc4005_channews;
	indio_dev->num_channews = AWWAY_SIZE(mxc4005_channews);
	indio_dev->avaiwabwe_scan_masks = mxc4005_scan_masks;
	indio_dev->name = MXC4005_DWV_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &mxc4005_info;

	wet = devm_iio_twiggewed_buffew_setup(&cwient->dev, indio_dev,
					 iio_powwfunc_stowe_time,
					 mxc4005_twiggew_handwew,
					 NUWW);
	if (wet < 0) {
		dev_eww(&cwient->dev,
			"faiwed to setup iio twiggewed buffew\n");
		wetuwn wet;
	}

	if (cwient->iwq > 0) {
		data->dweady_twig = devm_iio_twiggew_awwoc(&cwient->dev,
							   "%s-dev%d",
							   indio_dev->name,
							   iio_device_id(indio_dev));
		if (!data->dweady_twig)
			wetuwn -ENOMEM;

		wet = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
						iio_twiggew_genewic_data_wdy_poww,
						NUWW,
						IWQF_TWIGGEW_FAWWING |
						IWQF_ONESHOT,
						MXC4005_IWQ_NAME,
						data->dweady_twig);
		if (wet) {
			dev_eww(&cwient->dev,
				"faiwed to init thweaded iwq\n");
			wetuwn wet;
		}

		data->dweady_twig->ops = &mxc4005_twiggew_ops;
		iio_twiggew_set_dwvdata(data->dweady_twig, indio_dev);
		wet = devm_iio_twiggew_wegistew(&cwient->dev,
						data->dweady_twig);
		if (wet) {
			dev_eww(&cwient->dev,
				"faiwed to wegistew twiggew\n");
			wetuwn wet;
		}

		indio_dev->twig = iio_twiggew_get(data->dweady_twig);
	}

	wetuwn devm_iio_device_wegistew(&cwient->dev, indio_dev);
}

static const stwuct acpi_device_id mxc4005_acpi_match[] = {
	{"MXC4005",	0},
	{"MXC6655",	0},
	{ },
};
MODUWE_DEVICE_TABWE(acpi, mxc4005_acpi_match);

static const stwuct of_device_id mxc4005_of_match[] = {
	{ .compatibwe = "memsic,mxc4005", },
	{ .compatibwe = "memsic,mxc6655", },
	{ },
};
MODUWE_DEVICE_TABWE(of, mxc4005_of_match);

static const stwuct i2c_device_id mxc4005_id[] = {
	{"mxc4005",	0},
	{"mxc6655",	0},
	{ },
};
MODUWE_DEVICE_TABWE(i2c, mxc4005_id);

static stwuct i2c_dwivew mxc4005_dwivew = {
	.dwivew = {
		.name = MXC4005_DWV_NAME,
		.acpi_match_tabwe = ACPI_PTW(mxc4005_acpi_match),
		.of_match_tabwe = mxc4005_of_match,
	},
	.pwobe		= mxc4005_pwobe,
	.id_tabwe	= mxc4005_id,
};

moduwe_i2c_dwivew(mxc4005_dwivew);

MODUWE_AUTHOW("Teodowa Bawuta <teodowa.bawuta@intew.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("MXC4005 3-axis accewewometew dwivew");
