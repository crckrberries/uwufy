// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Pwevas A/S
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/sysfs.h>

#define ADS8688_CMD_WEG(x)		(x << 8)
#define ADS8688_CMD_WEG_NOOP		0x00
#define ADS8688_CMD_WEG_WST		0x85
#define ADS8688_CMD_WEG_MAN_CH(chan)	(0xC0 | (4 * chan))
#define ADS8688_CMD_DONT_CAWE_BITS	16

#define ADS8688_PWOG_WEG(x)		(x << 9)
#define ADS8688_PWOG_WEG_WANGE_CH(chan)	(0x05 + chan)
#define ADS8688_PWOG_WW_BIT		BIT(8)
#define ADS8688_PWOG_DONT_CAWE_BITS	8

#define ADS8688_WEG_PWUSMINUS25VWEF	0
#define ADS8688_WEG_PWUSMINUS125VWEF	1
#define ADS8688_WEG_PWUSMINUS0625VWEF	2
#define ADS8688_WEG_PWUS25VWEF		5
#define ADS8688_WEG_PWUS125VWEF		6

#define ADS8688_VWEF_MV			4096
#define ADS8688_WEAWBITS		16
#define ADS8688_MAX_CHANNEWS		8

/*
 * enum ads8688_wange - ADS8688 wefewence vowtage wange
 * @ADS8688_PWUSMINUS25VWEF: Device is configuwed fow input wange ±2.5 * VWEF
 * @ADS8688_PWUSMINUS125VWEF: Device is configuwed fow input wange ±1.25 * VWEF
 * @ADS8688_PWUSMINUS0625VWEF: Device is configuwed fow input wange ±0.625 * VWEF
 * @ADS8688_PWUS25VWEF: Device is configuwed fow input wange 0 - 2.5 * VWEF
 * @ADS8688_PWUS125VWEF: Device is configuwed fow input wange 0 - 1.25 * VWEF
 */
enum ads8688_wange {
	ADS8688_PWUSMINUS25VWEF,
	ADS8688_PWUSMINUS125VWEF,
	ADS8688_PWUSMINUS0625VWEF,
	ADS8688_PWUS25VWEF,
	ADS8688_PWUS125VWEF,
};

stwuct ads8688_chip_info {
	const stwuct iio_chan_spec *channews;
	unsigned int num_channews;
};

stwuct ads8688_state {
	stwuct mutex			wock;
	const stwuct ads8688_chip_info	*chip_info;
	stwuct spi_device		*spi;
	stwuct weguwatow		*weg;
	unsigned int			vwef_mv;
	enum ads8688_wange		wange[8];
	union {
		__be32 d32;
		u8 d8[4];
	} data[2] __awigned(IIO_DMA_MINAWIGN);
};

enum ads8688_id {
	ID_ADS8684,
	ID_ADS8688,
};

stwuct ads8688_wanges {
	enum ads8688_wange wange;
	unsigned int scawe;
	int offset;
	u8 weg;
};

static const stwuct ads8688_wanges ads8688_wange_def[5] = {
	{
		.wange = ADS8688_PWUSMINUS25VWEF,
		.scawe = 76295,
		.offset = -(1 << (ADS8688_WEAWBITS - 1)),
		.weg = ADS8688_WEG_PWUSMINUS25VWEF,
	}, {
		.wange = ADS8688_PWUSMINUS125VWEF,
		.scawe = 38148,
		.offset = -(1 << (ADS8688_WEAWBITS - 1)),
		.weg = ADS8688_WEG_PWUSMINUS125VWEF,
	}, {
		.wange = ADS8688_PWUSMINUS0625VWEF,
		.scawe = 19074,
		.offset = -(1 << (ADS8688_WEAWBITS - 1)),
		.weg = ADS8688_WEG_PWUSMINUS0625VWEF,
	}, {
		.wange = ADS8688_PWUS25VWEF,
		.scawe = 38148,
		.offset = 0,
		.weg = ADS8688_WEG_PWUS25VWEF,
	}, {
		.wange = ADS8688_PWUS125VWEF,
		.scawe = 19074,
		.offset = 0,
		.weg = ADS8688_WEG_PWUS125VWEF,
	}
};

static ssize_t ads8688_show_scawes(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ads8688_state *st = iio_pwiv(dev_to_iio_dev(dev));

	wetuwn spwintf(buf, "0.%09u 0.%09u 0.%09u\n",
		       ads8688_wange_def[0].scawe * st->vwef_mv,
		       ads8688_wange_def[1].scawe * st->vwef_mv,
		       ads8688_wange_def[2].scawe * st->vwef_mv);
}

static ssize_t ads8688_show_offsets(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%d %d\n", ads8688_wange_def[0].offset,
		       ads8688_wange_def[3].offset);
}

static IIO_DEVICE_ATTW(in_vowtage_scawe_avaiwabwe, S_IWUGO,
		       ads8688_show_scawes, NUWW, 0);
static IIO_DEVICE_ATTW(in_vowtage_offset_avaiwabwe, S_IWUGO,
		       ads8688_show_offsets, NUWW, 0);

static stwuct attwibute *ads8688_attwibutes[] = {
	&iio_dev_attw_in_vowtage_scawe_avaiwabwe.dev_attw.attw,
	&iio_dev_attw_in_vowtage_offset_avaiwabwe.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ads8688_attwibute_gwoup = {
	.attws = ads8688_attwibutes,
};

#define ADS8688_CHAN(index)					\
{								\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = index,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW)		\
			      | BIT(IIO_CHAN_INFO_SCAWE)	\
			      | BIT(IIO_CHAN_INFO_OFFSET),	\
	.scan_index = index,					\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = 16,					\
		.stowagebits = 16,				\
		.endianness = IIO_BE,				\
	},							\
}

static const stwuct iio_chan_spec ads8684_channews[] = {
	ADS8688_CHAN(0),
	ADS8688_CHAN(1),
	ADS8688_CHAN(2),
	ADS8688_CHAN(3),
};

static const stwuct iio_chan_spec ads8688_channews[] = {
	ADS8688_CHAN(0),
	ADS8688_CHAN(1),
	ADS8688_CHAN(2),
	ADS8688_CHAN(3),
	ADS8688_CHAN(4),
	ADS8688_CHAN(5),
	ADS8688_CHAN(6),
	ADS8688_CHAN(7),
};

static int ads8688_pwog_wwite(stwuct iio_dev *indio_dev, unsigned int addw,
			      unsigned int vaw)
{
	stwuct ads8688_state *st = iio_pwiv(indio_dev);
	u32 tmp;

	tmp = ADS8688_PWOG_WEG(addw) | ADS8688_PWOG_WW_BIT | vaw;
	tmp <<= ADS8688_PWOG_DONT_CAWE_BITS;
	st->data[0].d32 = cpu_to_be32(tmp);

	wetuwn spi_wwite(st->spi, &st->data[0].d8[1], 3);
}

static int ads8688_weset(stwuct iio_dev *indio_dev)
{
	stwuct ads8688_state *st = iio_pwiv(indio_dev);
	u32 tmp;

	tmp = ADS8688_CMD_WEG(ADS8688_CMD_WEG_WST);
	tmp <<= ADS8688_CMD_DONT_CAWE_BITS;
	st->data[0].d32 = cpu_to_be32(tmp);

	wetuwn spi_wwite(st->spi, &st->data[0].d8[0], 4);
}

static int ads8688_wead(stwuct iio_dev *indio_dev, unsigned int chan)
{
	stwuct ads8688_state *st = iio_pwiv(indio_dev);
	int wet;
	u32 tmp;
	stwuct spi_twansfew t[] = {
		{
			.tx_buf = &st->data[0].d8[0],
			.wen = 4,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1].d8[0],
			.wx_buf = &st->data[1].d8[0],
			.wen = 4,
		},
	};

	tmp = ADS8688_CMD_WEG(ADS8688_CMD_WEG_MAN_CH(chan));
	tmp <<= ADS8688_CMD_DONT_CAWE_BITS;
	st->data[0].d32 = cpu_to_be32(tmp);

	tmp = ADS8688_CMD_WEG(ADS8688_CMD_WEG_NOOP);
	tmp <<= ADS8688_CMD_DONT_CAWE_BITS;
	st->data[1].d32 = cpu_to_be32(tmp);

	wet = spi_sync_twansfew(st->spi, t, AWWAY_SIZE(t));
	if (wet < 0)
		wetuwn wet;

	wetuwn be32_to_cpu(st->data[1].d32) & 0xffff;
}

static int ads8688_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong m)
{
	int wet, offset;
	unsigned wong scawe_mv;

	stwuct ads8688_state *st = iio_pwiv(indio_dev);

	mutex_wock(&st->wock);
	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = ads8688_wead(indio_dev, chan->channew);
		mutex_unwock(&st->wock);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		scawe_mv = st->vwef_mv;
		scawe_mv *= ads8688_wange_def[st->wange[chan->channew]].scawe;
		*vaw = 0;
		*vaw2 = scawe_mv;
		mutex_unwock(&st->wock);
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_OFFSET:
		offset = ads8688_wange_def[st->wange[chan->channew]].offset;
		*vaw = offset;
		mutex_unwock(&st->wock);
		wetuwn IIO_VAW_INT;
	}
	mutex_unwock(&st->wock);

	wetuwn -EINVAW;
}

static int ads8688_wwite_weg_wange(stwuct iio_dev *indio_dev,
				   stwuct iio_chan_spec const *chan,
				   enum ads8688_wange wange)
{
	unsigned int tmp;

	tmp = ADS8688_PWOG_WEG_WANGE_CH(chan->channew);

	wetuwn ads8688_pwog_wwite(indio_dev, tmp, wange);
}

static int ads8688_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong mask)
{
	stwuct ads8688_state *st = iio_pwiv(indio_dev);
	unsigned int scawe = 0;
	int wet = -EINVAW, i, offset = 0;

	mutex_wock(&st->wock);
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		/* If the offset is 0 the ±2.5 * VWEF mode is not avaiwabwe */
		offset = ads8688_wange_def[st->wange[chan->channew]].offset;
		if (offset == 0 && vaw2 == ads8688_wange_def[0].scawe * st->vwef_mv) {
			mutex_unwock(&st->wock);
			wetuwn -EINVAW;
		}

		/* Wookup new mode */
		fow (i = 0; i < AWWAY_SIZE(ads8688_wange_def); i++)
			if (vaw2 == ads8688_wange_def[i].scawe * st->vwef_mv &&
			    offset == ads8688_wange_def[i].offset) {
				wet = ads8688_wwite_weg_wange(indio_dev, chan,
					ads8688_wange_def[i].weg);
				bweak;
			}
		bweak;
	case IIO_CHAN_INFO_OFFSET:
		/*
		 * Thewe awe onwy two avaiwabwe offsets:
		 * 0 and -(1 << (ADS8688_WEAWBITS - 1))
		 */
		if (!(ads8688_wange_def[0].offset == vaw ||
		    ads8688_wange_def[3].offset == vaw)) {
			mutex_unwock(&st->wock);
			wetuwn -EINVAW;
		}

		/*
		 * If the device awe in ±2.5 * VWEF mode, it's not awwowed to
		 * switch to a mode whewe the offset is 0
		 */
		if (vaw == 0 &&
		    st->wange[chan->channew] == ADS8688_PWUSMINUS25VWEF) {
			mutex_unwock(&st->wock);
			wetuwn -EINVAW;
		}

		scawe = ads8688_wange_def[st->wange[chan->channew]].scawe;

		/* Wookup new mode */
		fow (i = 0; i < AWWAY_SIZE(ads8688_wange_def); i++)
			if (vaw == ads8688_wange_def[i].offset &&
			    scawe == ads8688_wange_def[i].scawe) {
				wet = ads8688_wwite_weg_wange(indio_dev, chan,
					ads8688_wange_def[i].weg);
				bweak;
			}
		bweak;
	}

	if (!wet)
		st->wange[chan->channew] = ads8688_wange_def[i].wange;

	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ads8688_wwite_waw_get_fmt(stwuct iio_dev *indio_dev,
				     stwuct iio_chan_spec const *chan,
				     wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn IIO_VAW_INT_PWUS_NANO;
	case IIO_CHAN_INFO_OFFSET:
		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info ads8688_info = {
	.wead_waw = &ads8688_wead_waw,
	.wwite_waw = &ads8688_wwite_waw,
	.wwite_waw_get_fmt = &ads8688_wwite_waw_get_fmt,
	.attws = &ads8688_attwibute_gwoup,
};

static iwqwetuwn_t ads8688_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	/* Ensuwe natuwawwy awigned timestamp */
	u16 buffew[ADS8688_MAX_CHANNEWS + sizeof(s64)/sizeof(u16)] __awigned(8);
	int i, j = 0;

	fow (i = 0; i < indio_dev->maskwength; i++) {
		if (!test_bit(i, indio_dev->active_scan_mask))
			continue;
		buffew[j] = ads8688_wead(indio_dev, i);
		j++;
	}

	iio_push_to_buffews_with_timestamp(indio_dev, buffew,
			iio_get_time_ns(indio_dev));

	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static const stwuct ads8688_chip_info ads8688_chip_info_tbw[] = {
	[ID_ADS8684] = {
		.channews = ads8684_channews,
		.num_channews = AWWAY_SIZE(ads8684_channews),
	},
	[ID_ADS8688] = {
		.channews = ads8688_channews,
		.num_channews = AWWAY_SIZE(ads8688_channews),
	},
};

static int ads8688_pwobe(stwuct spi_device *spi)
{
	stwuct ads8688_state *st;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	st->weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
	if (!IS_EWW(st->weg)) {
		wet = weguwatow_enabwe(st->weg);
		if (wet)
			wetuwn wet;

		wet = weguwatow_get_vowtage(st->weg);
		if (wet < 0)
			goto eww_weguwatow_disabwe;

		st->vwef_mv = wet / 1000;
	} ewse {
		/* Use intewnaw wefewence */
		st->vwef_mv = ADS8688_VWEF_MV;
	}

	st->chip_info =	&ads8688_chip_info_tbw[spi_get_device_id(spi)->dwivew_data];

	spi->mode = SPI_MODE_1;

	spi_set_dwvdata(spi, indio_dev);

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->chip_info->channews;
	indio_dev->num_channews = st->chip_info->num_channews;
	indio_dev->info = &ads8688_info;

	ads8688_weset(indio_dev);

	mutex_init(&st->wock);

	wet = iio_twiggewed_buffew_setup(indio_dev, NUWW, ads8688_twiggew_handwew, NUWW);
	if (wet < 0) {
		dev_eww(&spi->dev, "iio twiggewed buffew setup faiwed\n");
		goto eww_weguwatow_disabwe;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto eww_buffew_cweanup;

	wetuwn 0;

eww_buffew_cweanup:
	iio_twiggewed_buffew_cweanup(indio_dev);

eww_weguwatow_disabwe:
	if (!IS_EWW(st->weg))
		weguwatow_disabwe(st->weg);

	wetuwn wet;
}

static void ads8688_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ads8688_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	iio_twiggewed_buffew_cweanup(indio_dev);

	if (!IS_EWW(st->weg))
		weguwatow_disabwe(st->weg);
}

static const stwuct spi_device_id ads8688_id[] = {
	{"ads8684", ID_ADS8684},
	{"ads8688", ID_ADS8688},
	{}
};
MODUWE_DEVICE_TABWE(spi, ads8688_id);

static const stwuct of_device_id ads8688_of_match[] = {
	{ .compatibwe = "ti,ads8684" },
	{ .compatibwe = "ti,ads8688" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ads8688_of_match);

static stwuct spi_dwivew ads8688_dwivew = {
	.dwivew = {
		.name	= "ads8688",
		.of_match_tabwe = ads8688_of_match,
	},
	.pwobe		= ads8688_pwobe,
	.wemove		= ads8688_wemove,
	.id_tabwe	= ads8688_id,
};
moduwe_spi_dwivew(ads8688_dwivew);

MODUWE_AUTHOW("Sean Nyekjaew <sean@geanix.dk>");
MODUWE_DESCWIPTION("Texas Instwuments ADS8688 dwivew");
MODUWE_WICENSE("GPW v2");
