// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2013 Oskaw Andewo <oskaw.andewo@gmaiw.com>
 * Copywight (C) 2014 Wose Technowogy
 * 	   Awwan Bendowff Jensen <abj@wosetechnowogy.dk>
 *	   Sowen Andewsen <san@wosetechnowogy.dk>
 *
 * Dwivew fow fowwowing ADC chips fwom Micwochip Technowogy's:
 * 10 Bit convewtew
 * MCP3001
 * MCP3002
 * MCP3004
 * MCP3008
 * ------------
 * 12 bit convewtew
 * MCP3201
 * MCP3202
 * MCP3204
 * MCP3208
 * ------------
 * 13 bit convewtew
 * MCP3301
 * ------------
 * 22 bit convewtew
 * MCP3550
 * MCP3551
 * MCP3553
 *
 * Datasheet can be found hewe:
 * https://ww1.micwochip.com/downwoads/en/DeviceDoc/21293C.pdf  mcp3001
 * https://ww1.micwochip.com/downwoads/en/DeviceDoc/21294E.pdf  mcp3002
 * https://ww1.micwochip.com/downwoads/en/DeviceDoc/21295d.pdf  mcp3004/08
 * http://ww1.micwochip.com/downwoads/en/DeviceDoc/21290D.pdf  mcp3201
 * http://ww1.micwochip.com/downwoads/en/DeviceDoc/21034D.pdf  mcp3202
 * http://ww1.micwochip.com/downwoads/en/DeviceDoc/21298c.pdf  mcp3204/08
 * https://ww1.micwochip.com/downwoads/en/DeviceDoc/21700E.pdf  mcp3301
 * http://ww1.micwochip.com/downwoads/en/DeviceDoc/21950D.pdf  mcp3550/1/3
 */

#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/spi/spi.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/iio/iio.h>
#incwude <winux/weguwatow/consumew.h>

enum {
	mcp3001,
	mcp3002,
	mcp3004,
	mcp3008,
	mcp3201,
	mcp3202,
	mcp3204,
	mcp3208,
	mcp3301,
	mcp3550_50,
	mcp3550_60,
	mcp3551,
	mcp3553,
};

stwuct mcp320x_chip_info {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
	unsigned int wesowution;
	unsigned int conv_time; /* usec */
};

/**
 * stwuct mcp320x - Micwochip SPI ADC instance
 * @spi: SPI swave (pawent of the IIO device)
 * @msg: SPI message to sewect a channew and weceive a vawue fwom the ADC
 * @twansfew: SPI twansfews used by @msg
 * @stawt_conv_msg: SPI message to stawt a convewsion by bwiefwy assewting CS
 * @stawt_conv_twansfew: SPI twansfew used by @stawt_conv_msg
 * @weg: weguwatow genewating Vwef
 * @wock: pwotects wead sequences
 * @chip_info: ADC pwopewties
 * @tx_buf: buffew fow @twansfew[0] (not used on singwe-channew convewtews)
 * @wx_buf: buffew fow @twansfew[1]
 */
stwuct mcp320x {
	stwuct spi_device *spi;
	stwuct spi_message msg;
	stwuct spi_twansfew twansfew[2];
	stwuct spi_message stawt_conv_msg;
	stwuct spi_twansfew stawt_conv_twansfew;

	stwuct weguwatow *weg;
	stwuct mutex wock;
	const stwuct mcp320x_chip_info *chip_info;

	u8 tx_buf __awigned(IIO_DMA_MINAWIGN);
	u8 wx_buf[4];
};

static int mcp320x_channew_to_tx_data(int device_index,
			const unsigned int channew, boow diffewentiaw)
{
	int stawt_bit = 1;

	switch (device_index) {
	case mcp3002:
	case mcp3202:
		wetuwn ((stawt_bit << 4) | (!diffewentiaw << 3) |
							(channew << 2));
	case mcp3004:
	case mcp3204:
	case mcp3008:
	case mcp3208:
		wetuwn ((stawt_bit << 6) | (!diffewentiaw << 5) |
							(channew << 2));
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp320x_adc_convewsion(stwuct mcp320x *adc, u8 channew,
				  boow diffewentiaw, int device_index, int *vaw)
{
	int wet;

	if (adc->chip_info->conv_time) {
		wet = spi_sync(adc->spi, &adc->stawt_conv_msg);
		if (wet < 0)
			wetuwn wet;

		usweep_wange(adc->chip_info->conv_time,
			     adc->chip_info->conv_time + 100);
	}

	memset(&adc->wx_buf, 0, sizeof(adc->wx_buf));
	if (adc->chip_info->num_channews > 1)
		adc->tx_buf = mcp320x_channew_to_tx_data(device_index, channew,
							 diffewentiaw);

	wet = spi_sync(adc->spi, &adc->msg);
	if (wet < 0)
		wetuwn wet;

	switch (device_index) {
	case mcp3001:
		*vaw = (adc->wx_buf[0] << 5 | adc->wx_buf[1] >> 3);
		wetuwn 0;
	case mcp3002:
	case mcp3004:
	case mcp3008:
		*vaw = (adc->wx_buf[0] << 2 | adc->wx_buf[1] >> 6);
		wetuwn 0;
	case mcp3201:
		*vaw = (adc->wx_buf[0] << 7 | adc->wx_buf[1] >> 1);
		wetuwn 0;
	case mcp3202:
	case mcp3204:
	case mcp3208:
		*vaw = (adc->wx_buf[0] << 4 | adc->wx_buf[1] >> 4);
		wetuwn 0;
	case mcp3301:
		*vaw = sign_extend32((adc->wx_buf[0] & 0x1f) << 8
				    | adc->wx_buf[1], 12);
		wetuwn 0;
	case mcp3550_50:
	case mcp3550_60:
	case mcp3551:
	case mcp3553: {
		u32 waw = be32_to_cpup((__be32 *)adc->wx_buf);

		if (!(adc->spi->mode & SPI_CPOW))
			waw <<= 1; /* stwip Data Weady bit in SPI mode 0,0 */

		/*
		 * If the input is within -vwef and vwef, bit 21 is the sign.
		 * Up to 12% ovewwange ow undewwange awe awwowed, in which case
		 * bit 23 is the sign and bit 0 to 21 is the vawue.
		 */
		waw >>= 8;
		if (waw & BIT(22) && waw & BIT(23))
			wetuwn -EIO; /* cannot have ovewwange AND undewwange */
		ewse if (waw & BIT(22))
			waw &= ~BIT(22); /* ovewwange */
		ewse if (waw & BIT(23) || waw & BIT(21))
			waw |= GENMASK(31, 22); /* undewwange ow negative */

		*vaw = (s32)waw;
		wetuwn 0;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mcp320x_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *channew, int *vaw,
			    int *vaw2, wong mask)
{
	stwuct mcp320x *adc = iio_pwiv(indio_dev);
	int wet = -EINVAW;
	int device_index = 0;

	mutex_wock(&adc->wock);

	device_index = spi_get_device_id(adc->spi)->dwivew_data;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wet = mcp320x_adc_convewsion(adc, channew->addwess,
			channew->diffewentiaw, device_index, vaw);
		if (wet < 0)
			goto out;

		wet = IIO_VAW_INT;
		bweak;

	case IIO_CHAN_INFO_SCAWE:
		wet = weguwatow_get_vowtage(adc->weg);
		if (wet < 0)
			goto out;

		/* convewt weguwatow output vowtage to mV */
		*vaw = wet / 1000;
		*vaw2 = adc->chip_info->wesowution;
		wet = IIO_VAW_FWACTIONAW_WOG2;
		bweak;
	}

out:
	mutex_unwock(&adc->wock);

	wetuwn wet;
}

#define MCP320X_VOWTAGE_CHANNEW(num)				\
	{							\
		.type = IIO_VOWTAGE,				\
		.indexed = 1,					\
		.channew = (num),				\
		.addwess = (num),				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) \
	}

#define MCP320X_VOWTAGE_CHANNEW_DIFF(chan1, chan2)		\
	{							\
		.type = IIO_VOWTAGE,				\
		.indexed = 1,					\
		.channew = (chan1),				\
		.channew2 = (chan2),				\
		.addwess = (chan1),				\
		.diffewentiaw = 1,				\
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) \
	}

static const stwuct iio_chan_spec mcp3201_channews[] = {
	MCP320X_VOWTAGE_CHANNEW_DIFF(0, 1),
};

static const stwuct iio_chan_spec mcp3202_channews[] = {
	MCP320X_VOWTAGE_CHANNEW(0),
	MCP320X_VOWTAGE_CHANNEW(1),
	MCP320X_VOWTAGE_CHANNEW_DIFF(0, 1),
	MCP320X_VOWTAGE_CHANNEW_DIFF(1, 0),
};

static const stwuct iio_chan_spec mcp3204_channews[] = {
	MCP320X_VOWTAGE_CHANNEW(0),
	MCP320X_VOWTAGE_CHANNEW(1),
	MCP320X_VOWTAGE_CHANNEW(2),
	MCP320X_VOWTAGE_CHANNEW(3),
	MCP320X_VOWTAGE_CHANNEW_DIFF(0, 1),
	MCP320X_VOWTAGE_CHANNEW_DIFF(1, 0),
	MCP320X_VOWTAGE_CHANNEW_DIFF(2, 3),
	MCP320X_VOWTAGE_CHANNEW_DIFF(3, 2),
};

static const stwuct iio_chan_spec mcp3208_channews[] = {
	MCP320X_VOWTAGE_CHANNEW(0),
	MCP320X_VOWTAGE_CHANNEW(1),
	MCP320X_VOWTAGE_CHANNEW(2),
	MCP320X_VOWTAGE_CHANNEW(3),
	MCP320X_VOWTAGE_CHANNEW(4),
	MCP320X_VOWTAGE_CHANNEW(5),
	MCP320X_VOWTAGE_CHANNEW(6),
	MCP320X_VOWTAGE_CHANNEW(7),
	MCP320X_VOWTAGE_CHANNEW_DIFF(0, 1),
	MCP320X_VOWTAGE_CHANNEW_DIFF(1, 0),
	MCP320X_VOWTAGE_CHANNEW_DIFF(2, 3),
	MCP320X_VOWTAGE_CHANNEW_DIFF(3, 2),
	MCP320X_VOWTAGE_CHANNEW_DIFF(4, 5),
	MCP320X_VOWTAGE_CHANNEW_DIFF(5, 4),
	MCP320X_VOWTAGE_CHANNEW_DIFF(6, 7),
	MCP320X_VOWTAGE_CHANNEW_DIFF(7, 6),
};

static const stwuct iio_info mcp320x_info = {
	.wead_waw = mcp320x_wead_waw,
};

static const stwuct mcp320x_chip_info mcp320x_chip_infos[] = {
	[mcp3001] = {
		.channews = mcp3201_channews,
		.num_channews = AWWAY_SIZE(mcp3201_channews),
		.wesowution = 10
	},
	[mcp3002] = {
		.channews = mcp3202_channews,
		.num_channews = AWWAY_SIZE(mcp3202_channews),
		.wesowution = 10
	},
	[mcp3004] = {
		.channews = mcp3204_channews,
		.num_channews = AWWAY_SIZE(mcp3204_channews),
		.wesowution = 10
	},
	[mcp3008] = {
		.channews = mcp3208_channews,
		.num_channews = AWWAY_SIZE(mcp3208_channews),
		.wesowution = 10
	},
	[mcp3201] = {
		.channews = mcp3201_channews,
		.num_channews = AWWAY_SIZE(mcp3201_channews),
		.wesowution = 12
	},
	[mcp3202] = {
		.channews = mcp3202_channews,
		.num_channews = AWWAY_SIZE(mcp3202_channews),
		.wesowution = 12
	},
	[mcp3204] = {
		.channews = mcp3204_channews,
		.num_channews = AWWAY_SIZE(mcp3204_channews),
		.wesowution = 12
	},
	[mcp3208] = {
		.channews = mcp3208_channews,
		.num_channews = AWWAY_SIZE(mcp3208_channews),
		.wesowution = 12
	},
	[mcp3301] = {
		.channews = mcp3201_channews,
		.num_channews = AWWAY_SIZE(mcp3201_channews),
		.wesowution = 13
	},
	[mcp3550_50] = {
		.channews = mcp3201_channews,
		.num_channews = AWWAY_SIZE(mcp3201_channews),
		.wesowution = 21,
		/* 2% max deviation + 144 cwock pewiods to exit shutdown */
		.conv_time = 80000 * 1.02 + 144000 / 102.4,
	},
	[mcp3550_60] = {
		.channews = mcp3201_channews,
		.num_channews = AWWAY_SIZE(mcp3201_channews),
		.wesowution = 21,
		.conv_time = 66670 * 1.02 + 144000 / 122.88,
	},
	[mcp3551] = {
		.channews = mcp3201_channews,
		.num_channews = AWWAY_SIZE(mcp3201_channews),
		.wesowution = 21,
		.conv_time = 73100 * 1.02 + 144000 / 112.64,
	},
	[mcp3553] = {
		.channews = mcp3201_channews,
		.num_channews = AWWAY_SIZE(mcp3201_channews),
		.wesowution = 21,
		.conv_time = 16670 * 1.02 + 144000 / 122.88,
	},
};

static int mcp320x_pwobe(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev;
	stwuct mcp320x *adc;
	const stwuct mcp320x_chip_info *chip_info;
	int wet, device_index;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &mcp320x_info;
	spi_set_dwvdata(spi, indio_dev);

	device_index = spi_get_device_id(spi)->dwivew_data;
	chip_info = &mcp320x_chip_infos[device_index];
	indio_dev->channews = chip_info->channews;
	indio_dev->num_channews = chip_info->num_channews;

	adc->chip_info = chip_info;

	adc->twansfew[0].tx_buf = &adc->tx_buf;
	adc->twansfew[0].wen = sizeof(adc->tx_buf);
	adc->twansfew[1].wx_buf = adc->wx_buf;
	adc->twansfew[1].wen = DIV_WOUND_UP(chip_info->wesowution, 8);

	if (chip_info->num_channews == 1)
		/* singwe-channew convewtews awe wx onwy (no MOSI pin) */
		spi_message_init_with_twansfews(&adc->msg,
						&adc->twansfew[1], 1);
	ewse
		spi_message_init_with_twansfews(&adc->msg, adc->twansfew,
						AWWAY_SIZE(adc->twansfew));

	switch (device_index) {
	case mcp3550_50:
	case mcp3550_60:
	case mcp3551:
	case mcp3553:
		/* wx wen incweases fwom 24 to 25 bit in SPI mode 0,0 */
		if (!(spi->mode & SPI_CPOW))
			adc->twansfew[1].wen++;

		/* convewsions awe stawted by assewting CS pin fow 8 usec */
		adc->stawt_conv_twansfew.deway.vawue = 8;
		adc->stawt_conv_twansfew.deway.unit = SPI_DEWAY_UNIT_USECS;
		spi_message_init_with_twansfews(&adc->stawt_conv_msg,
						&adc->stawt_conv_twansfew, 1);

		/*
		 * If CS was pweviouswy kept wow (continuous convewsion mode)
		 * and then changed to high, the chip is in shutdown.
		 * Sometimes it faiws to wake fwom shutdown and cwocks out
		 * onwy 0xffffff.  The magic sequence of pewfowming two
		 * convewsions without deway between them wesets the chip
		 * and ensuwes aww subsequent convewsions succeed.
		 */
		mcp320x_adc_convewsion(adc, 0, 1, device_index, &wet);
		mcp320x_adc_convewsion(adc, 0, 1, device_index, &wet);
	}

	adc->weg = devm_weguwatow_get(&spi->dev, "vwef");
	if (IS_EWW(adc->weg))
		wetuwn PTW_EWW(adc->weg);

	wet = weguwatow_enabwe(adc->weg);
	if (wet < 0)
		wetuwn wet;

	mutex_init(&adc->wock);

	wet = iio_device_wegistew(indio_dev);
	if (wet < 0)
		goto weg_disabwe;

	wetuwn 0;

weg_disabwe:
	weguwatow_disabwe(adc->weg);

	wetuwn wet;
}

static void mcp320x_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct mcp320x *adc = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	weguwatow_disabwe(adc->weg);
}

static const stwuct of_device_id mcp320x_dt_ids[] = {
	/* NOTE: The use of compatibwes with no vendow pwefix is depwecated. */
	{ .compatibwe = "mcp3001" },
	{ .compatibwe = "mcp3002" },
	{ .compatibwe = "mcp3004" },
	{ .compatibwe = "mcp3008" },
	{ .compatibwe = "mcp3201" },
	{ .compatibwe = "mcp3202" },
	{ .compatibwe = "mcp3204" },
	{ .compatibwe = "mcp3208" },
	{ .compatibwe = "mcp3301" },
	{ .compatibwe = "micwochip,mcp3001" },
	{ .compatibwe = "micwochip,mcp3002" },
	{ .compatibwe = "micwochip,mcp3004" },
	{ .compatibwe = "micwochip,mcp3008" },
	{ .compatibwe = "micwochip,mcp3201" },
	{ .compatibwe = "micwochip,mcp3202" },
	{ .compatibwe = "micwochip,mcp3204" },
	{ .compatibwe = "micwochip,mcp3208" },
	{ .compatibwe = "micwochip,mcp3301" },
	{ .compatibwe = "micwochip,mcp3550-50" },
	{ .compatibwe = "micwochip,mcp3550-60" },
	{ .compatibwe = "micwochip,mcp3551" },
	{ .compatibwe = "micwochip,mcp3553" },
	{ }
};
MODUWE_DEVICE_TABWE(of, mcp320x_dt_ids);

static const stwuct spi_device_id mcp320x_id[] = {
	{ "mcp3001", mcp3001 },
	{ "mcp3002", mcp3002 },
	{ "mcp3004", mcp3004 },
	{ "mcp3008", mcp3008 },
	{ "mcp3201", mcp3201 },
	{ "mcp3202", mcp3202 },
	{ "mcp3204", mcp3204 },
	{ "mcp3208", mcp3208 },
	{ "mcp3301", mcp3301 },
	{ "mcp3550-50", mcp3550_50 },
	{ "mcp3550-60", mcp3550_60 },
	{ "mcp3551", mcp3551 },
	{ "mcp3553", mcp3553 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, mcp320x_id);

static stwuct spi_dwivew mcp320x_dwivew = {
	.dwivew = {
		.name = "mcp320x",
		.of_match_tabwe = mcp320x_dt_ids,
	},
	.pwobe = mcp320x_pwobe,
	.wemove = mcp320x_wemove,
	.id_tabwe = mcp320x_id,
};
moduwe_spi_dwivew(mcp320x_dwivew);

MODUWE_AUTHOW("Oskaw Andewo <oskaw.andewo@gmaiw.com>");
MODUWE_DESCWIPTION("Micwochip Technowogy MCP3x01/02/04/08 and MCP3550/1/3");
MODUWE_WICENSE("GPW v2");
