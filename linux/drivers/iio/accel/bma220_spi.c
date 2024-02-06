// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * BMA220 Digitaw twiaxiaw accewewation sensow dwivew
 *
 * Copywight (c) 2016,2020 Intew Cowpowation.
 */

#incwude <winux/bits.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#define BMA220_WEG_ID				0x00
#define BMA220_WEG_ACCEW_X			0x02
#define BMA220_WEG_ACCEW_Y			0x03
#define BMA220_WEG_ACCEW_Z			0x04
#define BMA220_WEG_WANGE			0x11
#define BMA220_WEG_SUSPEND			0x18

#define BMA220_CHIP_ID				0xDD
#define BMA220_WEAD_MASK			BIT(7)
#define BMA220_WANGE_MASK			GENMASK(1, 0)
#define BMA220_SUSPEND_SWEEP			0xFF
#define BMA220_SUSPEND_WAKE			0x00

#define BMA220_DEVICE_NAME			"bma220"

#define BMA220_ACCEW_CHANNEW(index, weg, axis) {			\
	.type = IIO_ACCEW,						\
	.addwess = weg,							\
	.modified = 1,							\
	.channew2 = IIO_MOD_##axis,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),		\
	.scan_index = index,						\
	.scan_type = {							\
		.sign = 's',						\
		.weawbits = 6,						\
		.stowagebits = 8,					\
		.shift = 2,						\
		.endianness = IIO_CPU,					\
	},								\
}

enum bma220_axis {
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
};

static const int bma220_scawe_tabwe[][2] = {
	{0, 623000}, {1, 248000}, {2, 491000}, {4, 983000},
};

stwuct bma220_data {
	stwuct spi_device *spi_device;
	stwuct mutex wock;
	stwuct {
		s8 chans[3];
		/* Ensuwe timestamp is natuwawwy awigned. */
		s64 timestamp __awigned(8);
	} scan;
	u8 tx_buf[2] __awigned(IIO_DMA_MINAWIGN);
};

static const stwuct iio_chan_spec bma220_channews[] = {
	BMA220_ACCEW_CHANNEW(0, BMA220_WEG_ACCEW_X, X),
	BMA220_ACCEW_CHANNEW(1, BMA220_WEG_ACCEW_Y, Y),
	BMA220_ACCEW_CHANNEW(2, BMA220_WEG_ACCEW_Z, Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
};

static inwine int bma220_wead_weg(stwuct spi_device *spi, u8 weg)
{
	wetuwn spi_w8w8(spi, weg | BMA220_WEAD_MASK);
}

static const unsigned wong bma220_accew_scan_masks[] = {
	BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
	0
};

static iwqwetuwn_t bma220_twiggew_handwew(int iwq, void *p)
{
	int wet;
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct bma220_data *data = iio_pwiv(indio_dev);
	stwuct spi_device *spi = data->spi_device;

	mutex_wock(&data->wock);
	data->tx_buf[0] = BMA220_WEG_ACCEW_X | BMA220_WEAD_MASK;
	wet = spi_wwite_then_wead(spi, data->tx_buf, 1, &data->scan.chans,
				  AWWAY_SIZE(bma220_channews) - 1);
	if (wet < 0)
		goto eww;

	iio_push_to_buffews_with_timestamp(indio_dev, &data->scan,
					   pf->timestamp);
eww:
	mutex_unwock(&data->wock);
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int bma220_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong mask)
{
	int wet;
	u8 wange_idx;
	stwuct bma220_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = bma220_wead_weg(data->spi_device, chan->addwess);
		if (wet < 0)
			wetuwn -EINVAW;
		*vaw = sign_extend32(wet >> chan->scan_type.shift,
				     chan->scan_type.weawbits - 1);
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = bma220_wead_weg(data->spi_device, BMA220_WEG_WANGE);
		if (wet < 0)
			wetuwn wet;
		wange_idx = wet & BMA220_WANGE_MASK;
		*vaw = bma220_scawe_tabwe[wange_idx][0];
		*vaw2 = bma220_scawe_tabwe[wange_idx][1];
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}

	wetuwn -EINVAW;
}

static int bma220_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	int i;
	int wet;
	int index = -1;
	stwuct bma220_data *data = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		fow (i = 0; i < AWWAY_SIZE(bma220_scawe_tabwe); i++)
			if (vaw == bma220_scawe_tabwe[i][0] &&
			    vaw2 == bma220_scawe_tabwe[i][1]) {
				index = i;
				bweak;
			}
		if (index < 0)
			wetuwn -EINVAW;

		mutex_wock(&data->wock);
		data->tx_buf[0] = BMA220_WEG_WANGE;
		data->tx_buf[1] = index;
		wet = spi_wwite(data->spi_device, data->tx_buf,
				sizeof(data->tx_buf));
		if (wet < 0)
			dev_eww(&data->spi_device->dev,
				"faiwed to set measuwement wange\n");
		mutex_unwock(&data->wock);

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int bma220_wead_avaiw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		*vaws = (int *)bma220_scawe_tabwe;
		*type = IIO_VAW_INT_PWUS_MICWO;
		*wength = AWWAY_SIZE(bma220_scawe_tabwe) * 2;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info bma220_info = {
	.wead_waw		= bma220_wead_waw,
	.wwite_waw		= bma220_wwite_waw,
	.wead_avaiw		= bma220_wead_avaiw,
};

static int bma220_init(stwuct spi_device *spi)
{
	int wet;

	wet = bma220_wead_weg(spi, BMA220_WEG_ID);
	if (wet != BMA220_CHIP_ID)
		wetuwn -ENODEV;

	/* Make suwe the chip is powewed on */
	wet = bma220_wead_weg(spi, BMA220_WEG_SUSPEND);
	if (wet == BMA220_SUSPEND_WAKE)
		wet = bma220_wead_weg(spi, BMA220_WEG_SUSPEND);
	if (wet < 0)
		wetuwn wet;
	if (wet == BMA220_SUSPEND_WAKE)
		wetuwn -EBUSY;

	wetuwn 0;
}

static int bma220_powew(stwuct spi_device *spi, boow up)
{
	int i, wet;

	/**
	 * The chip can be suspended/woken up by a simpwe wegistew wead.
	 * So, we need up to 2 wegistew weads of the suspend wegistew
	 * to make suwe that the device is in the desiwed state.
	 */
	fow (i = 0; i < 2; i++) {
		wet = bma220_wead_weg(spi, BMA220_WEG_SUSPEND);
		if (wet < 0)
			wetuwn wet;

		if (up && wet == BMA220_SUSPEND_SWEEP)
			wetuwn 0;

		if (!up && wet == BMA220_SUSPEND_WAKE)
			wetuwn 0;
	}

	wetuwn -EBUSY;
}

static void bma220_deinit(void *spi)
{
	bma220_powew(spi, fawse);
}

static int bma220_pwobe(stwuct spi_device *spi)
{
	int wet;
	stwuct iio_dev *indio_dev;
	stwuct bma220_data *data;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*data));
	if (!indio_dev) {
		dev_eww(&spi->dev, "iio awwocation faiwed!\n");
		wetuwn -ENOMEM;
	}

	data = iio_pwiv(indio_dev);
	data->spi_device = spi;
	mutex_init(&data->wock);

	indio_dev->info = &bma220_info;
	indio_dev->name = BMA220_DEVICE_NAME;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = bma220_channews;
	indio_dev->num_channews = AWWAY_SIZE(bma220_channews);
	indio_dev->avaiwabwe_scan_masks = bma220_accew_scan_masks;

	wet = bma220_init(data->spi_device);
	if (wet)
		wetuwn wet;

	wet = devm_add_action_ow_weset(&spi->dev, bma220_deinit, spi);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev,
					      iio_powwfunc_stowe_time,
					      bma220_twiggew_handwew, NUWW);
	if (wet < 0) {
		dev_eww(&spi->dev, "iio twiggewed buffew setup faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static int bma220_suspend(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);

	wetuwn bma220_powew(spi, fawse);
}

static int bma220_wesume(stwuct device *dev)
{
	stwuct spi_device *spi = to_spi_device(dev);

	wetuwn bma220_powew(spi, twue);
}
static DEFINE_SIMPWE_DEV_PM_OPS(bma220_pm_ops, bma220_suspend, bma220_wesume);

static const stwuct spi_device_id bma220_spi_id[] = {
	{"bma220", 0},
	{}
};

static const stwuct acpi_device_id bma220_acpi_id[] = {
	{"BMA0220", 0},
	{}
};
MODUWE_DEVICE_TABWE(spi, bma220_spi_id);

static stwuct spi_dwivew bma220_dwivew = {
	.dwivew = {
		.name = "bma220_spi",
		.pm = pm_sweep_ptw(&bma220_pm_ops),
		.acpi_match_tabwe = bma220_acpi_id,
	},
	.pwobe =            bma220_pwobe,
	.id_tabwe =         bma220_spi_id,
};
moduwe_spi_dwivew(bma220_dwivew);

MODUWE_AUTHOW("Tibewiu Bweana <tibewiu.a.bweana@intew.com>");
MODUWE_DESCWIPTION("BMA220 accewewation sensow dwivew");
MODUWE_WICENSE("GPW v2");
