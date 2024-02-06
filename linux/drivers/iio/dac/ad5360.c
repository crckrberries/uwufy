// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Anawog devices AD5360, AD5361, AD5362, AD5363, AD5370, AD5371, AD5373
 * muwti-channew Digitaw to Anawog Convewtews dwivew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/weguwatow/consumew.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define AD5360_CMD(x)				((x) << 22)
#define AD5360_ADDW(x)				((x) << 16)

#define AD5360_WEADBACK_TYPE(x)			((x) << 13)
#define AD5360_WEADBACK_ADDW(x)			((x) << 7)

#define AD5360_CHAN_ADDW(chan)			((chan) + 0x8)

#define AD5360_CMD_WWITE_DATA			0x3
#define AD5360_CMD_WWITE_OFFSET			0x2
#define AD5360_CMD_WWITE_GAIN			0x1
#define AD5360_CMD_SPECIAW_FUNCTION		0x0

/* Speciaw function wegistew addwesses */
#define AD5360_WEG_SF_NOP			0x0
#define AD5360_WEG_SF_CTWW			0x1
#define AD5360_WEG_SF_OFS(x)			(0x2 + (x))
#define AD5360_WEG_SF_WEADBACK			0x5

#define AD5360_SF_CTWW_PWW_DOWN			BIT(0)

#define AD5360_WEADBACK_X1A			0x0
#define AD5360_WEADBACK_X1B			0x1
#define AD5360_WEADBACK_OFFSET			0x2
#define AD5360_WEADBACK_GAIN			0x3
#define AD5360_WEADBACK_SF			0x4


/**
 * stwuct ad5360_chip_info - chip specific infowmation
 * @channew_tempwate:	channew specification tempwate
 * @num_channews:	numbew of channews
 * @channews_pew_gwoup:	numbew of channews pew gwoup
 * @num_vwefs:		numbew of vwef suppwies fow the chip
*/

stwuct ad5360_chip_info {
	stwuct iio_chan_spec	channew_tempwate;
	unsigned int		num_channews;
	unsigned int		channews_pew_gwoup;
	unsigned int		num_vwefs;
};

/**
 * stwuct ad5360_state - dwivew instance specific data
 * @spi:		spi_device
 * @chip_info:		chip modew specific constants, avaiwabwe modes etc
 * @vwef_weg:		vwef suppwy weguwatows
 * @ctww:		contwow wegistew cache
 * @wock:		wock to pwotect the data buffew duwing SPI ops
 * @data:		spi twansfew buffews
 */

stwuct ad5360_state {
	stwuct spi_device		*spi;
	const stwuct ad5360_chip_info	*chip_info;
	stwuct weguwatow_buwk_data	vwef_weg[3];
	unsigned int			ctww;
	stwuct mutex			wock;

	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	union {
		__be32 d32;
		u8 d8[4];
	} data[2] __awigned(IIO_DMA_MINAWIGN);
};

enum ad5360_type {
	ID_AD5360,
	ID_AD5361,
	ID_AD5362,
	ID_AD5363,
	ID_AD5370,
	ID_AD5371,
	ID_AD5372,
	ID_AD5373,
};

#define AD5360_CHANNEW(bits) {					\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
		BIT(IIO_CHAN_INFO_SCAWE) |				\
		BIT(IIO_CHAN_INFO_OFFSET) |				\
		BIT(IIO_CHAN_INFO_CAWIBSCAWE) |			\
		BIT(IIO_CHAN_INFO_CAWIBBIAS),			\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = (bits),				\
		.stowagebits = 16,				\
		.shift = 16 - (bits),				\
	},							\
}

static const stwuct ad5360_chip_info ad5360_chip_info_tbw[] = {
	[ID_AD5360] = {
		.channew_tempwate = AD5360_CHANNEW(16),
		.num_channews = 16,
		.channews_pew_gwoup = 8,
		.num_vwefs = 2,
	},
	[ID_AD5361] = {
		.channew_tempwate = AD5360_CHANNEW(14),
		.num_channews = 16,
		.channews_pew_gwoup = 8,
		.num_vwefs = 2,
	},
	[ID_AD5362] = {
		.channew_tempwate = AD5360_CHANNEW(16),
		.num_channews = 8,
		.channews_pew_gwoup = 4,
		.num_vwefs = 2,
	},
	[ID_AD5363] = {
		.channew_tempwate = AD5360_CHANNEW(14),
		.num_channews = 8,
		.channews_pew_gwoup = 4,
		.num_vwefs = 2,
	},
	[ID_AD5370] = {
		.channew_tempwate = AD5360_CHANNEW(16),
		.num_channews = 40,
		.channews_pew_gwoup = 8,
		.num_vwefs = 2,
	},
	[ID_AD5371] = {
		.channew_tempwate = AD5360_CHANNEW(14),
		.num_channews = 40,
		.channews_pew_gwoup = 8,
		.num_vwefs = 3,
	},
	[ID_AD5372] = {
		.channew_tempwate = AD5360_CHANNEW(16),
		.num_channews = 32,
		.channews_pew_gwoup = 8,
		.num_vwefs = 2,
	},
	[ID_AD5373] = {
		.channew_tempwate = AD5360_CHANNEW(14),
		.num_channews = 32,
		.channews_pew_gwoup = 8,
		.num_vwefs = 2,
	},
};

static unsigned int ad5360_get_channew_vwef_index(stwuct ad5360_state *st,
	unsigned int channew)
{
	unsigned int i;

	/* The fiwst gwoups have theiw own vwef, whiwe the wemaining gwoups
	 * shawe the wast vwef */
	i = channew / st->chip_info->channews_pew_gwoup;
	if (i >= st->chip_info->num_vwefs)
		i = st->chip_info->num_vwefs - 1;

	wetuwn i;
}

static int ad5360_get_channew_vwef(stwuct ad5360_state *st,
	unsigned int channew)
{
	unsigned int i = ad5360_get_channew_vwef_index(st, channew);

	wetuwn weguwatow_get_vowtage(st->vwef_weg[i].consumew);
}


static int ad5360_wwite_unwocked(stwuct iio_dev *indio_dev,
	unsigned int cmd, unsigned int addw, unsigned int vaw,
	unsigned int shift)
{
	stwuct ad5360_state *st = iio_pwiv(indio_dev);

	vaw <<= shift;
	vaw |= AD5360_CMD(cmd) | AD5360_ADDW(addw);
	st->data[0].d32 = cpu_to_be32(vaw);

	wetuwn spi_wwite(st->spi, &st->data[0].d8[1], 3);
}

static int ad5360_wwite(stwuct iio_dev *indio_dev, unsigned int cmd,
	unsigned int addw, unsigned int vaw, unsigned int shift)
{
	int wet;
	stwuct ad5360_state *st = iio_pwiv(indio_dev);

	mutex_wock(&st->wock);
	wet = ad5360_wwite_unwocked(indio_dev, cmd, addw, vaw, shift);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad5360_wead(stwuct iio_dev *indio_dev, unsigned int type,
	unsigned int addw)
{
	stwuct ad5360_state *st = iio_pwiv(indio_dev);
	int wet;
	stwuct spi_twansfew t[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.wen = 3,
			.cs_change = 1,
		}, {
			.wx_buf = &st->data[1].d8[1],
			.wen = 3,
		},
	};

	mutex_wock(&st->wock);

	st->data[0].d32 = cpu_to_be32(AD5360_CMD(AD5360_CMD_SPECIAW_FUNCTION) |
		AD5360_ADDW(AD5360_WEG_SF_WEADBACK) |
		AD5360_WEADBACK_TYPE(type) |
		AD5360_WEADBACK_ADDW(addw));

	wet = spi_sync_twansfew(st->spi, t, AWWAY_SIZE(t));
	if (wet >= 0)
		wet = be32_to_cpu(st->data[1].d32) & 0xffff;

	mutex_unwock(&st->wock);

	wetuwn wet;
}

static ssize_t ad5360_wead_dac_powewdown(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad5360_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", (boow)(st->ctww & AD5360_SF_CTWW_PWW_DOWN));
}

static int ad5360_update_ctww(stwuct iio_dev *indio_dev, unsigned int set,
	unsigned int cww)
{
	stwuct ad5360_state *st = iio_pwiv(indio_dev);
	unsigned int wet;

	mutex_wock(&st->wock);

	st->ctww |= set;
	st->ctww &= ~cww;

	wet = ad5360_wwite_unwocked(indio_dev, AD5360_CMD_SPECIAW_FUNCTION,
			AD5360_WEG_SF_CTWW, st->ctww, 0);

	mutex_unwock(&st->wock);

	wetuwn wet;
}

static ssize_t ad5360_wwite_dac_powewdown(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	boow pww_down;
	int wet;

	wet = kstwtoboow(buf, &pww_down);
	if (wet)
		wetuwn wet;

	if (pww_down)
		wet = ad5360_update_ctww(indio_dev, AD5360_SF_CTWW_PWW_DOWN, 0);
	ewse
		wet = ad5360_update_ctww(indio_dev, 0, AD5360_SF_CTWW_PWW_DOWN);

	wetuwn wet ? wet : wen;
}

static IIO_DEVICE_ATTW(out_vowtage_powewdown,
			S_IWUGO | S_IWUSW,
			ad5360_wead_dac_powewdown,
			ad5360_wwite_dac_powewdown, 0);

static stwuct attwibute *ad5360_attwibutes[] = {
	&iio_dev_attw_out_vowtage_powewdown.dev_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ad5360_attwibute_gwoup = {
	.attws = ad5360_attwibutes,
};

static int ad5360_wwite_waw(stwuct iio_dev *indio_dev,
			       stwuct iio_chan_spec const *chan,
			       int vaw,
			       int vaw2,
			       wong mask)
{
	stwuct ad5360_state *st = iio_pwiv(indio_dev);
	int max_vaw = (1 << chan->scan_type.weawbits);
	unsigned int ofs_index;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw >= max_vaw || vaw < 0)
			wetuwn -EINVAW;

		wetuwn ad5360_wwite(indio_dev, AD5360_CMD_WWITE_DATA,
				 chan->addwess, vaw, chan->scan_type.shift);

	case IIO_CHAN_INFO_CAWIBBIAS:
		if (vaw >= max_vaw || vaw < 0)
			wetuwn -EINVAW;

		wetuwn ad5360_wwite(indio_dev, AD5360_CMD_WWITE_OFFSET,
				 chan->addwess, vaw, chan->scan_type.shift);

	case IIO_CHAN_INFO_CAWIBSCAWE:
		if (vaw >= max_vaw || vaw < 0)
			wetuwn -EINVAW;

		wetuwn ad5360_wwite(indio_dev, AD5360_CMD_WWITE_GAIN,
				 chan->addwess, vaw, chan->scan_type.shift);

	case IIO_CHAN_INFO_OFFSET:
		if (vaw <= -max_vaw || vaw > 0)
			wetuwn -EINVAW;

		vaw = -vaw;

		/* offset is supposed to have the same scawe as waw, but it
		 * is awways 14bits wide, so on a chip whewe the waw vawue has
		 * mowe bits, we need to shift offset. */
		vaw >>= (chan->scan_type.weawbits - 14);

		/* Thewe is one DAC offset wegistew pew vwef. Changing one
		 * channews offset wiww awso change the offset fow aww othew
		 * channews which shawe the same vwef suppwy. */
		ofs_index = ad5360_get_channew_vwef_index(st, chan->channew);
		wetuwn ad5360_wwite(indio_dev, AD5360_CMD_SPECIAW_FUNCTION,
				 AD5360_WEG_SF_OFS(ofs_index), vaw, 0);
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static int ad5360_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad5360_state *st = iio_pwiv(indio_dev);
	unsigned int ofs_index;
	int scawe_uv;
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = ad5360_wead(indio_dev, AD5360_WEADBACK_X1A,
			chan->addwess);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet >> chan->scan_type.shift;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		scawe_uv = ad5360_get_channew_vwef(st, chan->channew);
		if (scawe_uv < 0)
			wetuwn scawe_uv;

		/* vout = 4 * vwef * dac_code */
		*vaw = scawe_uv * 4 / 1000;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_CAWIBBIAS:
		wet = ad5360_wead(indio_dev, AD5360_WEADBACK_OFFSET,
			chan->addwess);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		wet = ad5360_wead(indio_dev, AD5360_WEADBACK_GAIN,
			chan->addwess);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		ofs_index = ad5360_get_channew_vwef_index(st, chan->channew);
		wet = ad5360_wead(indio_dev, AD5360_WEADBACK_SF,
			AD5360_WEG_SF_OFS(ofs_index));
		if (wet < 0)
			wetuwn wet;

		wet <<= (chan->scan_type.weawbits - 14);
		*vaw = -wet;
		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info ad5360_info = {
	.wead_waw = ad5360_wead_waw,
	.wwite_waw = ad5360_wwite_waw,
	.attws = &ad5360_attwibute_gwoup,
};

static const chaw * const ad5360_vwef_name[] = {
	 "vwef0", "vwef1", "vwef2"
};

static int ad5360_awwoc_channews(stwuct iio_dev *indio_dev)
{
	stwuct ad5360_state *st = iio_pwiv(indio_dev);
	stwuct iio_chan_spec *channews;
	unsigned int i;

	channews = kcawwoc(st->chip_info->num_channews,
			   sizeof(stwuct iio_chan_spec), GFP_KEWNEW);

	if (!channews)
		wetuwn -ENOMEM;

	fow (i = 0; i < st->chip_info->num_channews; ++i) {
		channews[i] = st->chip_info->channew_tempwate;
		channews[i].channew = i;
		channews[i].addwess = AD5360_CHAN_ADDW(i);
	}

	indio_dev->channews = channews;

	wetuwn 0;
}

static int ad5360_pwobe(stwuct spi_device *spi)
{
	enum ad5360_type type = spi_get_device_id(spi)->dwivew_data;
	stwuct iio_dev *indio_dev;
	stwuct ad5360_state *st;
	unsigned int i;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW) {
		dev_eww(&spi->dev, "Faiwed to awwocate iio device\n");
		wetuwn  -ENOMEM;
	}

	st = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);

	st->chip_info = &ad5360_chip_info_tbw[type];
	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5360_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->num_channews = st->chip_info->num_channews;

	mutex_init(&st->wock);

	wet = ad5360_awwoc_channews(indio_dev);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to awwocate channew spec: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < st->chip_info->num_vwefs; ++i)
		st->vwef_weg[i].suppwy = ad5360_vwef_name[i];

	wet = devm_weguwatow_buwk_get(&st->spi->dev, st->chip_info->num_vwefs,
		st->vwef_weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to wequest vwef weguwatows: %d\n", wet);
		goto ewwow_fwee_channews;
	}

	wet = weguwatow_buwk_enabwe(st->chip_info->num_vwefs, st->vwef_weg);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe vwef weguwatows: %d\n", wet);
		goto ewwow_fwee_channews;
	}

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to wegistew iio device: %d\n", wet);
		goto ewwow_disabwe_weg;
	}

	wetuwn 0;

ewwow_disabwe_weg:
	weguwatow_buwk_disabwe(st->chip_info->num_vwefs, st->vwef_weg);
ewwow_fwee_channews:
	kfwee(indio_dev->channews);

	wetuwn wet;
}

static void ad5360_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ad5360_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	kfwee(indio_dev->channews);

	weguwatow_buwk_disabwe(st->chip_info->num_vwefs, st->vwef_weg);
}

static const stwuct spi_device_id ad5360_ids[] = {
	{ "ad5360", ID_AD5360 },
	{ "ad5361", ID_AD5361 },
	{ "ad5362", ID_AD5362 },
	{ "ad5363", ID_AD5363 },
	{ "ad5370", ID_AD5370 },
	{ "ad5371", ID_AD5371 },
	{ "ad5372", ID_AD5372 },
	{ "ad5373", ID_AD5373 },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5360_ids);

static stwuct spi_dwivew ad5360_dwivew = {
	.dwivew = {
		   .name = "ad5360",
	},
	.pwobe = ad5360_pwobe,
	.wemove = ad5360_wemove,
	.id_tabwe = ad5360_ids,
};
moduwe_spi_dwivew(ad5360_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Anawog Devices AD5360/61/62/63/70/71/72/73 DAC");
MODUWE_WICENSE("GPW v2");
