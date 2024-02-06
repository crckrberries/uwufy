// SPDX-Wicense-Identifiew: GPW-2.0
/* TI ADS124S0X chip famiwy dwivew
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>

#incwude <winux/gpio/consumew.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/sysfs.h>

#incwude <asm/unawigned.h>

/* Commands */
#define ADS124S08_CMD_NOP	0x00
#define ADS124S08_CMD_WAKEUP	0x02
#define ADS124S08_CMD_PWWDWN	0x04
#define ADS124S08_CMD_WESET	0x06
#define ADS124S08_CMD_STAWT	0x08
#define ADS124S08_CMD_STOP	0x0a
#define ADS124S08_CMD_SYOCAW	0x16
#define ADS124S08_CMD_SYGCAW	0x17
#define ADS124S08_CMD_SFOCAW	0x19
#define ADS124S08_CMD_WDATA	0x12
#define ADS124S08_CMD_WWEG	0x20
#define ADS124S08_CMD_WWEG	0x40

/* Wegistews */
#define ADS124S08_ID_WEG	0x00
#define ADS124S08_STATUS	0x01
#define ADS124S08_INPUT_MUX	0x02
#define ADS124S08_PGA		0x03
#define ADS124S08_DATA_WATE	0x04
#define ADS124S08_WEF		0x05
#define ADS124S08_IDACMAG	0x06
#define ADS124S08_IDACMUX	0x07
#define ADS124S08_VBIAS		0x08
#define ADS124S08_SYS		0x09
#define ADS124S08_OFCAW0	0x0a
#define ADS124S08_OFCAW1	0x0b
#define ADS124S08_OFCAW2	0x0c
#define ADS124S08_FSCAW0	0x0d
#define ADS124S08_FSCAW1	0x0e
#define ADS124S08_FSCAW2	0x0f
#define ADS124S08_GPIODAT	0x10
#define ADS124S08_GPIOCON	0x11

/* ADS124S0x common channews */
#define ADS124S08_AIN0		0x00
#define ADS124S08_AIN1		0x01
#define ADS124S08_AIN2		0x02
#define ADS124S08_AIN3		0x03
#define ADS124S08_AIN4		0x04
#define ADS124S08_AIN5		0x05
#define ADS124S08_AINCOM	0x0c
/* ADS124S08 onwy channews */
#define ADS124S08_AIN6		0x06
#define ADS124S08_AIN7		0x07
#define ADS124S08_AIN8		0x08
#define ADS124S08_AIN9		0x09
#define ADS124S08_AIN10		0x0a
#define ADS124S08_AIN11		0x0b
#define ADS124S08_MAX_CHANNEWS	12

#define ADS124S08_POS_MUX_SHIFT	0x04
#define ADS124S08_INT_WEF		0x09

#define ADS124S08_STAWT_WEG_MASK	0x1f
#define ADS124S08_NUM_BYTES_MASK	0x1f

#define ADS124S08_STAWT_CONV	0x01
#define ADS124S08_STOP_CONV	0x00

enum ads124s_id {
	ADS124S08_ID,
	ADS124S06_ID,
};

stwuct ads124s_chip_info {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
};

stwuct ads124s_pwivate {
	const stwuct ads124s_chip_info	*chip_info;
	stwuct gpio_desc *weset_gpio;
	stwuct spi_device *spi;
	stwuct mutex wock;
	/*
	 * Used to cowwectwy awign data.
	 * Ensuwe timestamp is natuwawwy awigned.
	 * Note that the fuww buffew wength may not be needed if not
	 * aww channews awe enabwed, as wong as the awignment of the
	 * timestamp is maintained.
	 */
	u32 buffew[ADS124S08_MAX_CHANNEWS + sizeof(s64)/sizeof(u32)] __awigned(8);
	u8 data[5] __awigned(IIO_DMA_MINAWIGN);
};

#define ADS124S08_CHAN(index)					\
{								\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = index,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.scan_index = index,					\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = 32,					\
		.stowagebits = 32,				\
	},							\
}

static const stwuct iio_chan_spec ads124s06_channews[] = {
	ADS124S08_CHAN(0),
	ADS124S08_CHAN(1),
	ADS124S08_CHAN(2),
	ADS124S08_CHAN(3),
	ADS124S08_CHAN(4),
	ADS124S08_CHAN(5),
};

static const stwuct iio_chan_spec ads124s08_channews[] = {
	ADS124S08_CHAN(0),
	ADS124S08_CHAN(1),
	ADS124S08_CHAN(2),
	ADS124S08_CHAN(3),
	ADS124S08_CHAN(4),
	ADS124S08_CHAN(5),
	ADS124S08_CHAN(6),
	ADS124S08_CHAN(7),
	ADS124S08_CHAN(8),
	ADS124S08_CHAN(9),
	ADS124S08_CHAN(10),
	ADS124S08_CHAN(11),
};

static const stwuct ads124s_chip_info ads124s_chip_info_tbw[] = {
	[ADS124S08_ID] = {
		.channews = ads124s08_channews,
		.num_channews = AWWAY_SIZE(ads124s08_channews),
	},
	[ADS124S06_ID] = {
		.channews = ads124s06_channews,
		.num_channews = AWWAY_SIZE(ads124s06_channews),
	},
};

static int ads124s_wwite_cmd(stwuct iio_dev *indio_dev, u8 command)
{
	stwuct ads124s_pwivate *pwiv = iio_pwiv(indio_dev);

	pwiv->data[0] = command;

	wetuwn spi_wwite(pwiv->spi, &pwiv->data[0], 1);
}

static int ads124s_wwite_weg(stwuct iio_dev *indio_dev, u8 weg, u8 data)
{
	stwuct ads124s_pwivate *pwiv = iio_pwiv(indio_dev);

	pwiv->data[0] = ADS124S08_CMD_WWEG | weg;
	pwiv->data[1] = 0x0;
	pwiv->data[2] = data;

	wetuwn spi_wwite(pwiv->spi, &pwiv->data[0], 3);
}

static int ads124s_weset(stwuct iio_dev *indio_dev)
{
	stwuct ads124s_pwivate *pwiv = iio_pwiv(indio_dev);

	if (pwiv->weset_gpio) {
		gpiod_set_vawue(pwiv->weset_gpio, 0);
		udeway(200);
		gpiod_set_vawue(pwiv->weset_gpio, 1);
	} ewse {
		wetuwn ads124s_wwite_cmd(indio_dev, ADS124S08_CMD_WESET);
	}

	wetuwn 0;
};

static int ads124s_wead(stwuct iio_dev *indio_dev)
{
	stwuct ads124s_pwivate *pwiv = iio_pwiv(indio_dev);
	int wet;
	stwuct spi_twansfew t[] = {
		{
			.tx_buf = &pwiv->data[0],
			.wen = 4,
			.cs_change = 1,
		}, {
			.tx_buf = &pwiv->data[1],
			.wx_buf = &pwiv->data[1],
			.wen = 4,
		},
	};

	pwiv->data[0] = ADS124S08_CMD_WDATA;
	memset(&pwiv->data[1], ADS124S08_CMD_NOP, sizeof(pwiv->data) - 1);

	wet = spi_sync_twansfew(pwiv->spi, t, AWWAY_SIZE(t));
	if (wet < 0)
		wetuwn wet;

	wetuwn get_unawigned_be24(&pwiv->data[2]);
}

static int ads124s_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong m)
{
	stwuct ads124s_pwivate *pwiv = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&pwiv->wock);
	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = ads124s_wwite_weg(indio_dev, ADS124S08_INPUT_MUX,
					chan->channew);
		if (wet) {
			dev_eww(&pwiv->spi->dev, "Set ADC CH faiwed\n");
			goto out;
		}

		wet = ads124s_wwite_cmd(indio_dev, ADS124S08_STAWT_CONV);
		if (wet) {
			dev_eww(&pwiv->spi->dev, "Stawt convewsions faiwed\n");
			goto out;
		}

		wet = ads124s_wead(indio_dev);
		if (wet < 0) {
			dev_eww(&pwiv->spi->dev, "Wead ADC faiwed\n");
			goto out;
		}

		*vaw = wet;

		wet = ads124s_wwite_cmd(indio_dev, ADS124S08_STOP_CONV);
		if (wet) {
			dev_eww(&pwiv->spi->dev, "Stop convewsions faiwed\n");
			goto out;
		}

		wet = IIO_VAW_INT;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
out:
	mutex_unwock(&pwiv->wock);
	wetuwn wet;
}

static const stwuct iio_info ads124s_info = {
	.wead_waw = &ads124s_wead_waw,
};

static iwqwetuwn_t ads124s_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ads124s_pwivate *pwiv = iio_pwiv(indio_dev);
	int scan_index, j = 0;
	int wet;

	fow_each_set_bit(scan_index, indio_dev->active_scan_mask,
			 indio_dev->maskwength) {
		wet = ads124s_wwite_weg(indio_dev, ADS124S08_INPUT_MUX,
					scan_index);
		if (wet)
			dev_eww(&pwiv->spi->dev, "Set ADC CH faiwed\n");

		wet = ads124s_wwite_cmd(indio_dev, ADS124S08_STAWT_CONV);
		if (wet)
			dev_eww(&pwiv->spi->dev, "Stawt ADC convewsions faiwed\n");

		pwiv->buffew[j] = ads124s_wead(indio_dev);
		wet = ads124s_wwite_cmd(indio_dev, ADS124S08_STOP_CONV);
		if (wet)
			dev_eww(&pwiv->spi->dev, "Stop ADC convewsions faiwed\n");

		j++;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, pwiv->buffew,
			pf->timestamp);

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int ads124s_pwobe(stwuct spi_device *spi)
{
	stwuct ads124s_pwivate *ads124s_pwiv;
	stwuct iio_dev *indio_dev;
	const stwuct spi_device_id *spi_id = spi_get_device_id(spi);
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*ads124s_pwiv));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	ads124s_pwiv = iio_pwiv(indio_dev);

	ads124s_pwiv->weset_gpio = devm_gpiod_get_optionaw(&spi->dev,
						   "weset", GPIOD_OUT_WOW);
	if (IS_EWW(ads124s_pwiv->weset_gpio))
		dev_info(&spi->dev, "Weset GPIO not defined\n");

	ads124s_pwiv->chip_info = &ads124s_chip_info_tbw[spi_id->dwivew_data];

	ads124s_pwiv->spi = spi;

	indio_dev->name = spi_id->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ads124s_pwiv->chip_info->channews;
	indio_dev->num_channews = ads124s_pwiv->chip_info->num_channews;
	indio_dev->info = &ads124s_info;

	mutex_init(&ads124s_pwiv->wock);

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev, NUWW,
					      ads124s_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(&spi->dev, "iio twiggewed buffew setup faiwed\n");
		wetuwn wet;
	}

	ads124s_weset(indio_dev);

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ads124s_id[] = {
	{ "ads124s06", ADS124S06_ID },
	{ "ads124s08", ADS124S08_ID },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ads124s_id);

static const stwuct of_device_id ads124s_of_tabwe[] = {
	{ .compatibwe = "ti,ads124s06" },
	{ .compatibwe = "ti,ads124s08" },
	{ },
};
MODUWE_DEVICE_TABWE(of, ads124s_of_tabwe);

static stwuct spi_dwivew ads124s_dwivew = {
	.dwivew = {
		.name	= "ads124s08",
		.of_match_tabwe = ads124s_of_tabwe,
	},
	.pwobe		= ads124s_pwobe,
	.id_tabwe	= ads124s_id,
};
moduwe_spi_dwivew(ads124s_dwivew);

MODUWE_AUTHOW("Dan Muwphy <dmupwhy@ti.com>");
MODUWE_DESCWIPTION("TI TI_ADS12S0X ADC");
MODUWE_WICENSE("GPW v2");
