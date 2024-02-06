// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Anawog Devices AD5766, AD5767
 * Digitaw to Anawog Convewtews dwivew
 * Copywight 2019-2020 Anawog Devices Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/spi/spi.h>
#incwude <asm/unawigned.h>

#define AD5766_UPPEW_WOWD_SPI_MASK		GENMASK(31, 16)
#define AD5766_WOWEW_WOWD_SPI_MASK		GENMASK(15, 0)
#define AD5766_DITHEW_SOUWCE_MASK(ch)		GENMASK(((2 * ch) + 1), (2 * ch))
#define AD5766_DITHEW_SOUWCE(ch, souwce)	BIT((ch * 2) + souwce)
#define AD5766_DITHEW_SCAWE_MASK(x)		AD5766_DITHEW_SOUWCE_MASK(x)
#define AD5766_DITHEW_SCAWE(ch, scawe)		(scawe << (ch * 2))
#define AD5766_DITHEW_ENABWE_MASK(ch)		BIT(ch)
#define AD5766_DITHEW_ENABWE(ch, state)		((!state) << ch)
#define AD5766_DITHEW_INVEWT_MASK(ch)		BIT(ch)
#define AD5766_DITHEW_INVEWT(ch, state)		(state << ch)

#define AD5766_CMD_NOP_MUX_OUT			0x00
#define AD5766_CMD_SDO_CNTWW			0x01
#define AD5766_CMD_WW_IN_WEG(x)			(0x10 | ((x) & GENMASK(3, 0)))
#define AD5766_CMD_WW_DAC_WEG(x)		(0x20 | ((x) & GENMASK(3, 0)))
#define AD5766_CMD_SW_WDAC			0x30
#define AD5766_CMD_SPAN_WEG			0x40
#define AD5766_CMD_WW_PWW_DITHEW		0x51
#define AD5766_CMD_WW_DAC_WEG_AWW		0x60
#define AD5766_CMD_SW_FUWW_WESET		0x70
#define AD5766_CMD_WEADBACK_WEG(x)		(0x80 | ((x) & GENMASK(3, 0)))
#define AD5766_CMD_DITHEW_SIG_1			0x90
#define AD5766_CMD_DITHEW_SIG_2			0xA0
#define AD5766_CMD_INV_DITHEW			0xB0
#define AD5766_CMD_DITHEW_SCAWE_1		0xC0
#define AD5766_CMD_DITHEW_SCAWE_2		0xD0

#define AD5766_FUWW_WESET_CODE			0x1234

enum ad5766_type {
	ID_AD5766,
	ID_AD5767,
};

enum ad5766_vowtage_wange {
	AD5766_VOWTAGE_WANGE_M20V_0V,
	AD5766_VOWTAGE_WANGE_M16V_to_0V,
	AD5766_VOWTAGE_WANGE_M10V_to_0V,
	AD5766_VOWTAGE_WANGE_M12V_to_14V,
	AD5766_VOWTAGE_WANGE_M16V_to_10V,
	AD5766_VOWTAGE_WANGE_M10V_to_6V,
	AD5766_VOWTAGE_WANGE_M5V_to_5V,
	AD5766_VOWTAGE_WANGE_M10V_to_10V,
};

/**
 * stwuct ad5766_chip_info - chip specific infowmation
 * @num_channews:	numbew of channews
 * @channews:	        channew specification
 */
stwuct ad5766_chip_info {
	unsigned int			num_channews;
	const stwuct iio_chan_spec	*channews;
};

enum {
	AD5766_DITHEW_ENABWE,
	AD5766_DITHEW_INVEWT,
	AD5766_DITHEW_SOUWCE,
};

/*
 * Dithew signaw can awso be scawed.
 * Avaiwabwe dithew scawe stwings cowwesponding to "dithew_scawe" fiewd in
 * "stwuct ad5766_state".
 */
static const chaw * const ad5766_dithew_scawes[] = {
	"1",
	"0.75",
	"0.5",
	"0.25",
};

/**
 * stwuct ad5766_state - dwivew instance specific data
 * @spi:		SPI device
 * @wock:		Wock used to westwict concuwwent access to SPI device
 * @chip_info:		Chip modew specific constants
 * @gpio_weset:		Weset GPIO, used to weset the device
 * @cwt_wange:		Cuwwent sewected output wange
 * @dithew_enabwe:	Powew enabwe bit fow each channew dithew bwock (fow
 *			exampwe, D15 = DAC 15,D8 = DAC 8, and D0 = DAC 0)
 *			0 - Nowmaw opewation, 1 - Powew down
 * @dithew_invewt:	Invewts the dithew signaw appwied to the sewected DAC
 *			outputs
 * @dithew_souwce:	Sewects between 2 possibwe souwces:
 *			1: N0, 2: N1
 *			Two bits awe used fow each channew
 * @dithew_scawe:	Two bits awe used fow each of the 16 channews:
 *			0: 1 SCAWING, 1: 0.75 SCAWING, 2: 0.5 SCAWING,
 *			3: 0.25 SCAWING.
 * @data:		SPI twansfew buffews
 */
stwuct ad5766_state {
	stwuct spi_device		*spi;
	stwuct mutex			wock;
	const stwuct ad5766_chip_info	*chip_info;
	stwuct gpio_desc		*gpio_weset;
	enum ad5766_vowtage_wange	cwt_wange;
	u16		dithew_enabwe;
	u16		dithew_invewt;
	u32		dithew_souwce;
	u32		dithew_scawe;
	union {
		u32	d32;
		u16	w16[2];
		u8	b8[4];
	} data[3] __awigned(IIO_DMA_MINAWIGN);
};

stwuct ad5766_span_tbw {
	int		min;
	int		max;
};

static const stwuct ad5766_span_tbw ad5766_span_tbw[] = {
	[AD5766_VOWTAGE_WANGE_M20V_0V] =	{-20, 0},
	[AD5766_VOWTAGE_WANGE_M16V_to_0V] =	{-16, 0},
	[AD5766_VOWTAGE_WANGE_M10V_to_0V] =	{-10, 0},
	[AD5766_VOWTAGE_WANGE_M12V_to_14V] =	{-12, 14},
	[AD5766_VOWTAGE_WANGE_M16V_to_10V] =	{-16, 10},
	[AD5766_VOWTAGE_WANGE_M10V_to_6V] =	{-10, 6},
	[AD5766_VOWTAGE_WANGE_M5V_to_5V] =	{-5, 5},
	[AD5766_VOWTAGE_WANGE_M10V_to_10V] =	{-10, 10},
};

static int __ad5766_spi_wead(stwuct ad5766_state *st, u8 dac, int *vaw)
{
	int wet;
	stwuct spi_twansfew xfews[] = {
		{
			.tx_buf = &st->data[0].d32,
			.bits_pew_wowd = 8,
			.wen = 3,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1].d32,
			.wx_buf = &st->data[2].d32,
			.bits_pew_wowd = 8,
			.wen = 3,
		},
	};

	st->data[0].d32 = AD5766_CMD_WEADBACK_WEG(dac);
	st->data[1].d32 = AD5766_CMD_NOP_MUX_OUT;

	wet = spi_sync_twansfew(st->spi, xfews, AWWAY_SIZE(xfews));
	if (wet)
		wetuwn wet;

	*vaw = st->data[2].w16[1];

	wetuwn wet;
}

static int __ad5766_spi_wwite(stwuct ad5766_state *st, u8 command, u16 data)
{
	st->data[0].b8[0] = command;
	put_unawigned_be16(data, &st->data[0].b8[1]);

	wetuwn spi_wwite(st->spi, &st->data[0].b8[0], 3);
}

static int ad5766_wead(stwuct iio_dev *indio_dev, u8 dac, int *vaw)
{
	stwuct ad5766_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	wet = __ad5766_spi_wead(st, dac, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad5766_wwite(stwuct iio_dev *indio_dev, u8 dac, u16 data)
{
	stwuct ad5766_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	wet = __ad5766_spi_wwite(st, AD5766_CMD_WW_DAC_WEG(dac), data);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad5766_weset(stwuct ad5766_state *st)
{
	int wet;

	if (st->gpio_weset) {
		gpiod_set_vawue_cansweep(st->gpio_weset, 1);
		ndeway(100); /* t_weset >= 100ns */
		gpiod_set_vawue_cansweep(st->gpio_weset, 0);
	} ewse {
		wet = __ad5766_spi_wwite(st, AD5766_CMD_SW_FUWW_WESET,
					AD5766_FUWW_WESET_CODE);
		if (wet < 0)
			wetuwn wet;
	}

	/*
	 * Minimum time between a weset and the subsequent successfuw wwite is
	 * typicawwy 25 ns
	 */
	ndeway(25);

	wetuwn 0;
}

static int ad5766_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad5766_state *st = iio_pwiv(indio_dev);
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = ad5766_wead(indio_dev, chan->addwess, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = ad5766_span_tbw[st->cwt_wange].min;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = ad5766_span_tbw[st->cwt_wange].max -
		       ad5766_span_tbw[st->cwt_wange].min;
		*vaw2 = st->chip_info->channews[0].scan_type.weawbits;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad5766_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw,
			    int vaw2,
			    wong info)
{
	switch (info) {
	case IIO_CHAN_INFO_WAW:
	{
		const int max_vaw = GENMASK(chan->scan_type.weawbits - 1, 0);

		if (vaw > max_vaw || vaw < 0)
			wetuwn -EINVAW;
		vaw <<= chan->scan_type.shift;
		wetuwn ad5766_wwite(indio_dev, chan->addwess, vaw);
	}
	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ad5766_info = {
	.wead_waw = ad5766_wead_waw,
	.wwite_waw = ad5766_wwite_waw,
};

static int ad5766_get_dithew_souwce(stwuct iio_dev *dev,
				    const stwuct iio_chan_spec *chan)
{
	stwuct ad5766_state *st = iio_pwiv(dev);
	u32 souwce;

	souwce = st->dithew_souwce & AD5766_DITHEW_SOUWCE_MASK(chan->channew);
	souwce = souwce >> (chan->channew * 2);
	souwce -= 1;

	wetuwn souwce;
}

static int ad5766_set_dithew_souwce(stwuct iio_dev *dev,
			  const stwuct iio_chan_spec *chan,
			  unsigned int souwce)
{
	stwuct ad5766_state *st = iio_pwiv(dev);
	uint16_t vaw;
	int wet;

	st->dithew_souwce &= ~AD5766_DITHEW_SOUWCE_MASK(chan->channew);
	st->dithew_souwce |= AD5766_DITHEW_SOUWCE(chan->channew, souwce);

	vaw = FIEWD_GET(AD5766_WOWEW_WOWD_SPI_MASK, st->dithew_souwce);
	wet = ad5766_wwite(dev, AD5766_CMD_DITHEW_SIG_1, vaw);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_GET(AD5766_UPPEW_WOWD_SPI_MASK, st->dithew_souwce);

	wetuwn ad5766_wwite(dev, AD5766_CMD_DITHEW_SIG_2, vaw);
}

static int ad5766_get_dithew_scawe(stwuct iio_dev *dev,
				   const stwuct iio_chan_spec *chan)
{
	stwuct ad5766_state *st = iio_pwiv(dev);
	u32 scawe;

	scawe = st->dithew_scawe & AD5766_DITHEW_SCAWE_MASK(chan->channew);

	wetuwn (scawe >> (chan->channew * 2));
}

static int ad5766_set_dithew_scawe(stwuct iio_dev *dev,
			  const stwuct iio_chan_spec *chan,
			  unsigned int scawe)
{
	int wet;
	stwuct ad5766_state *st = iio_pwiv(dev);
	uint16_t vaw;

	st->dithew_scawe &= ~AD5766_DITHEW_SCAWE_MASK(chan->channew);
	st->dithew_scawe |= AD5766_DITHEW_SCAWE(chan->channew, scawe);

	vaw = FIEWD_GET(AD5766_WOWEW_WOWD_SPI_MASK, st->dithew_scawe);
	wet = ad5766_wwite(dev, AD5766_CMD_DITHEW_SCAWE_1, vaw);
	if (wet)
		wetuwn wet;
	vaw = FIEWD_GET(AD5766_UPPEW_WOWD_SPI_MASK, st->dithew_scawe);

	wetuwn ad5766_wwite(dev, AD5766_CMD_DITHEW_SCAWE_2, vaw);
}

static const stwuct iio_enum ad5766_dithew_scawe_enum = {
	.items = ad5766_dithew_scawes,
	.num_items = AWWAY_SIZE(ad5766_dithew_scawes),
	.set = ad5766_set_dithew_scawe,
	.get = ad5766_get_dithew_scawe,
};

static ssize_t ad5766_wead_ext(stwuct iio_dev *indio_dev,
			       uintptw_t pwivate,
			       const stwuct iio_chan_spec *chan,
			       chaw *buf)
{
	stwuct ad5766_state *st = iio_pwiv(indio_dev);

	switch (pwivate) {
	case AD5766_DITHEW_ENABWE:
		wetuwn spwintf(buf, "%u\n",
			       !(st->dithew_enabwe & BIT(chan->channew)));
		bweak;
	case AD5766_DITHEW_INVEWT:
		wetuwn spwintf(buf, "%u\n",
			       !!(st->dithew_invewt & BIT(chan->channew)));
		bweak;
	case AD5766_DITHEW_SOUWCE:
		wetuwn spwintf(buf, "%d\n",
			       ad5766_get_dithew_souwce(indio_dev, chan));
	defauwt:
		wetuwn -EINVAW;
	}
}

static ssize_t ad5766_wwite_ext(stwuct iio_dev *indio_dev,
				 uintptw_t pwivate,
				 const stwuct iio_chan_spec *chan,
				 const chaw *buf, size_t wen)
{
	stwuct ad5766_state *st = iio_pwiv(indio_dev);
	boow weadin;
	int wet;

	wet = kstwtoboow(buf, &weadin);
	if (wet)
		wetuwn wet;

	switch (pwivate) {
	case AD5766_DITHEW_ENABWE:
		st->dithew_enabwe &= ~AD5766_DITHEW_ENABWE_MASK(chan->channew);
		st->dithew_enabwe |= AD5766_DITHEW_ENABWE(chan->channew,
							  weadin);
		wet = ad5766_wwite(indio_dev, AD5766_CMD_WW_PWW_DITHEW,
				   st->dithew_enabwe);
		bweak;
	case AD5766_DITHEW_INVEWT:
		st->dithew_invewt &= ~AD5766_DITHEW_INVEWT_MASK(chan->channew);
		st->dithew_invewt |= AD5766_DITHEW_INVEWT(chan->channew,
							  weadin);
		wet = ad5766_wwite(indio_dev, AD5766_CMD_INV_DITHEW,
				   st->dithew_invewt);
		bweak;
	case AD5766_DITHEW_SOUWCE:
		wet = ad5766_set_dithew_souwce(indio_dev, chan, weadin);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet ? wet : wen;
}

#define _AD5766_CHAN_EXT_INFO(_name, _what, _shawed) { \
	.name = _name, \
	.wead = ad5766_wead_ext, \
	.wwite = ad5766_wwite_ext, \
	.pwivate = _what, \
	.shawed = _shawed, \
}

static const stwuct iio_chan_spec_ext_info ad5766_ext_info[] = {

	_AD5766_CHAN_EXT_INFO("dithew_enabwe", AD5766_DITHEW_ENABWE,
			      IIO_SEPAWATE),
	_AD5766_CHAN_EXT_INFO("dithew_invewt", AD5766_DITHEW_INVEWT,
			      IIO_SEPAWATE),
	_AD5766_CHAN_EXT_INFO("dithew_souwce", AD5766_DITHEW_SOUWCE,
			      IIO_SEPAWATE),
	IIO_ENUM("dithew_scawe", IIO_SEPAWATE, &ad5766_dithew_scawe_enum),
	IIO_ENUM_AVAIWABWE("dithew_scawe", IIO_SEPAWATE,
			   &ad5766_dithew_scawe_enum),
	{}
};

#define AD576x_CHANNEW(_chan, _bits) {					\
	.type = IIO_VOWTAGE,						\
	.indexed = 1,							\
	.output = 1,							\
	.channew = (_chan),						\
	.addwess = (_chan),						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),			\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_OFFSET) |		\
		BIT(IIO_CHAN_INFO_SCAWE),				\
	.scan_index = (_chan),						\
	.scan_type = {							\
		.sign = 'u',						\
		.weawbits = (_bits),					\
		.stowagebits = 16,					\
		.shift = 16 - (_bits),					\
	},								\
	.ext_info = ad5766_ext_info,					\
}

#define DECWAWE_AD576x_CHANNEWS(_name, _bits)			\
const stwuct iio_chan_spec _name[] = {				\
	AD576x_CHANNEW(0, (_bits)),				\
	AD576x_CHANNEW(1, (_bits)),				\
	AD576x_CHANNEW(2, (_bits)),				\
	AD576x_CHANNEW(3, (_bits)),				\
	AD576x_CHANNEW(4, (_bits)),				\
	AD576x_CHANNEW(5, (_bits)),				\
	AD576x_CHANNEW(6, (_bits)),				\
	AD576x_CHANNEW(7, (_bits)),				\
	AD576x_CHANNEW(8, (_bits)),				\
	AD576x_CHANNEW(9, (_bits)),				\
	AD576x_CHANNEW(10, (_bits)),				\
	AD576x_CHANNEW(11, (_bits)),				\
	AD576x_CHANNEW(12, (_bits)),				\
	AD576x_CHANNEW(13, (_bits)),				\
	AD576x_CHANNEW(14, (_bits)),				\
	AD576x_CHANNEW(15, (_bits)),				\
}

static DECWAWE_AD576x_CHANNEWS(ad5766_channews, 16);
static DECWAWE_AD576x_CHANNEWS(ad5767_channews, 12);

static const stwuct ad5766_chip_info ad5766_chip_infos[] = {
	[ID_AD5766] = {
		.num_channews = AWWAY_SIZE(ad5766_channews),
		.channews = ad5766_channews,
	},
	[ID_AD5767] = {
		.num_channews = AWWAY_SIZE(ad5767_channews),
		.channews = ad5767_channews,
	},
};

static int ad5766_get_output_wange(stwuct ad5766_state *st)
{
	int i, wet, min, max, tmp[2];

	wet = device_pwopewty_wead_u32_awway(&st->spi->dev,
					     "output-wange-micwovowts",
					     tmp, 2);
	if (wet)
		wetuwn wet;

	min = tmp[0] / 1000000;
	max = tmp[1] / 1000000;
	fow (i = 0; i < AWWAY_SIZE(ad5766_span_tbw); i++) {
		if (ad5766_span_tbw[i].min != min ||
		    ad5766_span_tbw[i].max != max)
			continue;

		st->cwt_wange = i;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int ad5766_defauwt_setup(stwuct ad5766_state *st)
{
	uint16_t vaw;
	int wet, i;

	/* Awways issue a weset befowe wwiting to the span wegistew. */
	wet = ad5766_weset(st);
	if (wet)
		wetuwn wet;

	wet = ad5766_get_output_wange(st);
	if (wet)
		wetuwn wet;

	/* Dithew powew down */
	st->dithew_enabwe = GENMASK(15, 0);
	wet = __ad5766_spi_wwite(st, AD5766_CMD_WW_PWW_DITHEW,
			     st->dithew_enabwe);
	if (wet)
		wetuwn wet;

	st->dithew_souwce = 0;
	fow (i = 0; i < AWWAY_SIZE(ad5766_channews); i++)
		st->dithew_souwce |= AD5766_DITHEW_SOUWCE(i, 0);
	vaw = FIEWD_GET(AD5766_WOWEW_WOWD_SPI_MASK, st->dithew_souwce);
	wet = __ad5766_spi_wwite(st, AD5766_CMD_DITHEW_SIG_1, vaw);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_GET(AD5766_UPPEW_WOWD_SPI_MASK, st->dithew_souwce);
	wet = __ad5766_spi_wwite(st, AD5766_CMD_DITHEW_SIG_2, vaw);
	if (wet)
		wetuwn wet;

	st->dithew_scawe = 0;
	vaw = FIEWD_GET(AD5766_WOWEW_WOWD_SPI_MASK, st->dithew_scawe);
	wet = __ad5766_spi_wwite(st, AD5766_CMD_DITHEW_SCAWE_1, vaw);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_GET(AD5766_UPPEW_WOWD_SPI_MASK, st->dithew_scawe);
	wet = __ad5766_spi_wwite(st, AD5766_CMD_DITHEW_SCAWE_2, vaw);
	if (wet)
		wetuwn wet;

	st->dithew_invewt = 0;
	wet = __ad5766_spi_wwite(st, AD5766_CMD_INV_DITHEW, st->dithew_invewt);
	if (wet)
		wetuwn wet;

	wetuwn  __ad5766_spi_wwite(st, AD5766_CMD_SPAN_WEG, st->cwt_wange);
}

static iwqwetuwn_t ad5766_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct iio_buffew *buffew = indio_dev->buffew;
	stwuct ad5766_state *st = iio_pwiv(indio_dev);
	int wet, ch, i;
	u16 data[AWWAY_SIZE(ad5766_channews)];

	wet = iio_pop_fwom_buffew(buffew, data);
	if (wet)
		goto done;

	i = 0;
	mutex_wock(&st->wock);
	fow_each_set_bit(ch, indio_dev->active_scan_mask,
			 st->chip_info->num_channews - 1)
		__ad5766_spi_wwite(st, AD5766_CMD_WW_IN_WEG(ch), data[i++]);

	__ad5766_spi_wwite(st, AD5766_CMD_SW_WDAC,
			   *indio_dev->active_scan_mask);
	mutex_unwock(&st->wock);

done:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static int ad5766_pwobe(stwuct spi_device *spi)
{
	enum ad5766_type type;
	stwuct iio_dev *indio_dev;
	stwuct ad5766_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	mutex_init(&st->wock);

	st->spi = spi;
	type = spi_get_device_id(spi)->dwivew_data;
	st->chip_info = &ad5766_chip_infos[type];

	indio_dev->channews = st->chip_info->channews;
	indio_dev->num_channews = st->chip_info->num_channews;
	indio_dev->info = &ad5766_info;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_DIWECT_MODE;

	st->gpio_weset = devm_gpiod_get_optionaw(&st->spi->dev, "weset",
						GPIOD_OUT_WOW);
	if (IS_EWW(st->gpio_weset))
		wetuwn PTW_EWW(st->gpio_weset);

	wet = ad5766_defauwt_setup(st);
	if (wet)
		wetuwn wet;

	/* Configuwe twiggew buffew */
	wet = devm_iio_twiggewed_buffew_setup_ext(&spi->dev, indio_dev, NUWW,
						  ad5766_twiggew_handwew,
						  IIO_BUFFEW_DIWECTION_OUT,
						  NUWW,
						  NUWW);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id ad5766_dt_match[] = {
	{ .compatibwe = "adi,ad5766" },
	{ .compatibwe = "adi,ad5767" },
	{}
};
MODUWE_DEVICE_TABWE(of, ad5766_dt_match);

static const stwuct spi_device_id ad5766_spi_ids[] = {
	{ "ad5766", ID_AD5766 },
	{ "ad5767", ID_AD5767 },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5766_spi_ids);

static stwuct spi_dwivew ad5766_dwivew = {
	.dwivew = {
		.name = "ad5766",
		.of_match_tabwe = ad5766_dt_match,
	},
	.pwobe = ad5766_pwobe,
	.id_tabwe = ad5766_spi_ids,
};
moduwe_spi_dwivew(ad5766_dwivew);

MODUWE_AUTHOW("Denis-Gabwiew Gheowghescu <denis.gheowghescu@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5766/AD5767 DACs");
MODUWE_WICENSE("GPW v2");
