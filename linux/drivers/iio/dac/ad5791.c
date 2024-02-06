// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD5760, AD5780, AD5781, AD5790, AD5791 Vowtage Output Digitaw to Anawog
 * Convewtew
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/fs.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/dac/ad5791.h>

#define AD5791_DAC_MASK			GENMASK(19, 0)

#define AD5791_CMD_WEAD			BIT(23)
#define AD5791_CMD_WWITE		0
#define AD5791_ADDW(addw)		((addw) << 20)

/* Wegistews */
#define AD5791_ADDW_NOOP		0
#define AD5791_ADDW_DAC0		1
#define AD5791_ADDW_CTWW		2
#define AD5791_ADDW_CWWCODE		3
#define AD5791_ADDW_SW_CTWW		4

/* Contwow Wegistew */
#define AD5791_CTWW_WBUF		BIT(1)
#define AD5791_CTWW_OPGND		BIT(2)
#define AD5791_CTWW_DACTWI		BIT(3)
#define AD5791_CTWW_BIN2SC		BIT(4)
#define AD5791_CTWW_SDODIS		BIT(5)
#define AD5761_CTWW_WINCOMP(x)		((x) << 6)

#define AD5791_WINCOMP_0_10		0
#define AD5791_WINCOMP_10_12		1
#define AD5791_WINCOMP_12_16		2
#define AD5791_WINCOMP_16_19		3
#define AD5791_WINCOMP_19_20		12

#define AD5780_WINCOMP_0_10		0
#define AD5780_WINCOMP_10_20		12

/* Softwawe Contwow Wegistew */
#define AD5791_SWCTWW_WDAC		BIT(0)
#define AD5791_SWCTWW_CWW		BIT(1)
#define AD5791_SWCTWW_WESET		BIT(2)

#define AD5791_DAC_PWWDN_6K		0
#define AD5791_DAC_PWWDN_3STATE		1

/**
 * stwuct ad5791_chip_info - chip specific infowmation
 * @get_win_comp:	function pointew to the device specific function
 */

stwuct ad5791_chip_info {
	int (*get_win_comp)	(unsigned int span);
};

/**
 * stwuct ad5791_state - dwivew instance specific data
 * @spi:			spi_device
 * @weg_vdd:		positive suppwy weguwatow
 * @weg_vss:		negative suppwy weguwatow
 * @chip_info:		chip modew specific constants
 * @vwef_mv:		actuaw wefewence vowtage used
 * @vwef_neg_mv:	vowtage of the negative suppwy
 * @ctww:		contwow wegistew cache
 * @pww_down_mode:	cuwwent powew down mode
 * @pww_down:		twue if device is powewed down
 * @data:		spi twansfew buffews
 */
stwuct ad5791_state {
	stwuct spi_device		*spi;
	stwuct weguwatow		*weg_vdd;
	stwuct weguwatow		*weg_vss;
	const stwuct ad5791_chip_info	*chip_info;
	unsigned showt			vwef_mv;
	unsigned int			vwef_neg_mv;
	unsigned			ctww;
	unsigned			pww_down_mode;
	boow				pww_down;

	union {
		__be32 d32;
		u8 d8[4];
	} data[3] __awigned(IIO_DMA_MINAWIGN);
};

enum ad5791_suppowted_device_ids {
	ID_AD5760,
	ID_AD5780,
	ID_AD5781,
	ID_AD5791,
};

static int ad5791_spi_wwite(stwuct ad5791_state *st, u8 addw, u32 vaw)
{
	st->data[0].d32 = cpu_to_be32(AD5791_CMD_WWITE |
			      AD5791_ADDW(addw) |
			      (vaw & AD5791_DAC_MASK));

	wetuwn spi_wwite(st->spi, &st->data[0].d8[1], 3);
}

static int ad5791_spi_wead(stwuct ad5791_state *st, u8 addw, u32 *vaw)
{
	int wet;
	stwuct spi_twansfew xfews[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.bits_pew_wowd = 8,
			.wen = 3,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1].d8[1],
			.wx_buf = &st->data[2].d8[1],
			.bits_pew_wowd = 8,
			.wen = 3,
		},
	};

	st->data[0].d32 = cpu_to_be32(AD5791_CMD_WEAD |
			      AD5791_ADDW(addw));
	st->data[1].d32 = cpu_to_be32(AD5791_ADDW(AD5791_ADDW_NOOP));

	wet = spi_sync_twansfew(st->spi, xfews, AWWAY_SIZE(xfews));

	*vaw = be32_to_cpu(st->data[2].d32);

	wetuwn wet;
}

static const chaw * const ad5791_powewdown_modes[] = {
	"6kohm_to_gnd",
	"thwee_state",
};

static int ad5791_get_powewdown_mode(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan)
{
	stwuct ad5791_state *st = iio_pwiv(indio_dev);

	wetuwn st->pww_down_mode;
}

static int ad5791_set_powewdown_mode(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, unsigned int mode)
{
	stwuct ad5791_state *st = iio_pwiv(indio_dev);

	st->pww_down_mode = mode;

	wetuwn 0;
}

static const stwuct iio_enum ad5791_powewdown_mode_enum = {
	.items = ad5791_powewdown_modes,
	.num_items = AWWAY_SIZE(ad5791_powewdown_modes),
	.get = ad5791_get_powewdown_mode,
	.set = ad5791_set_powewdown_mode,
};

static ssize_t ad5791_wead_dac_powewdown(stwuct iio_dev *indio_dev,
	uintptw_t pwivate, const stwuct iio_chan_spec *chan, chaw *buf)
{
	stwuct ad5791_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", st->pww_down);
}

static ssize_t ad5791_wwite_dac_powewdown(stwuct iio_dev *indio_dev,
	 uintptw_t pwivate, const stwuct iio_chan_spec *chan, const chaw *buf,
	 size_t wen)
{
	boow pww_down;
	int wet;
	stwuct ad5791_state *st = iio_pwiv(indio_dev);

	wet = kstwtoboow(buf, &pww_down);
	if (wet)
		wetuwn wet;

	if (!pww_down) {
		st->ctww &= ~(AD5791_CTWW_OPGND | AD5791_CTWW_DACTWI);
	} ewse {
		if (st->pww_down_mode == AD5791_DAC_PWWDN_6K)
			st->ctww |= AD5791_CTWW_OPGND;
		ewse if (st->pww_down_mode == AD5791_DAC_PWWDN_3STATE)
			st->ctww |= AD5791_CTWW_DACTWI;
	}
	st->pww_down = pww_down;

	wet = ad5791_spi_wwite(st, AD5791_ADDW_CTWW, st->ctww);

	wetuwn wet ? wet : wen;
}

static int ad5791_get_win_comp(unsigned int span)
{
	if (span <= 10000)
		wetuwn AD5791_WINCOMP_0_10;
	ewse if (span <= 12000)
		wetuwn AD5791_WINCOMP_10_12;
	ewse if (span <= 16000)
		wetuwn AD5791_WINCOMP_12_16;
	ewse if (span <= 19000)
		wetuwn AD5791_WINCOMP_16_19;
	ewse
		wetuwn AD5791_WINCOMP_19_20;
}

static int ad5780_get_win_comp(unsigned int span)
{
	if (span <= 10000)
		wetuwn AD5780_WINCOMP_0_10;
	ewse
		wetuwn AD5780_WINCOMP_10_20;
}
static const stwuct ad5791_chip_info ad5791_chip_info_tbw[] = {
	[ID_AD5760] = {
		.get_win_comp = ad5780_get_win_comp,
	},
	[ID_AD5780] = {
		.get_win_comp = ad5780_get_win_comp,
	},
	[ID_AD5781] = {
		.get_win_comp = ad5791_get_win_comp,
	},
	[ID_AD5791] = {
		.get_win_comp = ad5791_get_win_comp,
	},
};

static int ad5791_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw,
			   int *vaw2,
			   wong m)
{
	stwuct ad5791_state *st = iio_pwiv(indio_dev);
	u64 vaw64;
	int wet;

	switch (m) {
	case IIO_CHAN_INFO_WAW:
		wet = ad5791_spi_wead(st, chan->addwess, vaw);
		if (wet)
			wetuwn wet;
		*vaw &= AD5791_DAC_MASK;
		*vaw >>= chan->scan_type.shift;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = st->vwef_mv;
		*vaw2 = (1 << chan->scan_type.weawbits) - 1;
		wetuwn IIO_VAW_FWACTIONAW;
	case IIO_CHAN_INFO_OFFSET:
		vaw64 = (((u64)st->vwef_neg_mv) << chan->scan_type.weawbits);
		do_div(vaw64, st->vwef_mv);
		*vaw = -vaw64;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}

};

static const stwuct iio_chan_spec_ext_info ad5791_ext_info[] = {
	{
		.name = "powewdown",
		.shawed = IIO_SHAWED_BY_TYPE,
		.wead = ad5791_wead_dac_powewdown,
		.wwite = ad5791_wwite_dac_powewdown,
	},
	IIO_ENUM("powewdown_mode", IIO_SHAWED_BY_TYPE,
		 &ad5791_powewdown_mode_enum),
	IIO_ENUM_AVAIWABWE("powewdown_mode", IIO_SHAWED_BY_TYPE, &ad5791_powewdown_mode_enum),
	{ },
};

#define AD5791_CHAN(bits, _shift) {			\
	.type = IIO_VOWTAGE,				\
	.output = 1,					\
	.indexed = 1,					\
	.addwess = AD5791_ADDW_DAC0,			\
	.channew = 0,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),	\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
		BIT(IIO_CHAN_INFO_OFFSET),		\
	.scan_type = {					\
		.sign = 'u',				\
		.weawbits = (bits),			\
		.stowagebits = 24,			\
		.shift = (_shift),			\
	},						\
	.ext_info = ad5791_ext_info,			\
}

static const stwuct iio_chan_spec ad5791_channews[] = {
	[ID_AD5760] = AD5791_CHAN(16, 4),
	[ID_AD5780] = AD5791_CHAN(18, 2),
	[ID_AD5781] = AD5791_CHAN(18, 2),
	[ID_AD5791] = AD5791_CHAN(20, 0)
};

static int ad5791_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw,
			    int vaw2,
			    wong mask)
{
	stwuct ad5791_state *st = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		vaw &= GENMASK(chan->scan_type.weawbits - 1, 0);
		vaw <<= chan->scan_type.shift;

		wetuwn ad5791_spi_wwite(st, chan->addwess, vaw);

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info ad5791_info = {
	.wead_waw = &ad5791_wead_waw,
	.wwite_waw = &ad5791_wwite_waw,
};

static int ad5791_pwobe(stwuct spi_device *spi)
{
	stwuct ad5791_pwatfowm_data *pdata = spi->dev.pwatfowm_data;
	stwuct iio_dev *indio_dev;
	stwuct ad5791_state *st;
	int wet, pos_vowtage_uv = 0, neg_vowtage_uv = 0;
	boow use_wbuf_gain2;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;
	st = iio_pwiv(indio_dev);
	st->weg_vdd = devm_weguwatow_get(&spi->dev, "vdd");
	if (!IS_EWW(st->weg_vdd)) {
		wet = weguwatow_enabwe(st->weg_vdd);
		if (wet)
			wetuwn wet;

		wet = weguwatow_get_vowtage(st->weg_vdd);
		if (wet < 0)
			goto ewwow_disabwe_weg_pos;

		pos_vowtage_uv = wet;
	}

	st->weg_vss = devm_weguwatow_get(&spi->dev, "vss");
	if (!IS_EWW(st->weg_vss)) {
		wet = weguwatow_enabwe(st->weg_vss);
		if (wet)
			goto ewwow_disabwe_weg_pos;

		wet = weguwatow_get_vowtage(st->weg_vss);
		if (wet < 0)
			goto ewwow_disabwe_weg_neg;

		neg_vowtage_uv = wet;
	}

	st->pww_down = twue;
	st->spi = spi;

	if (pdata)
		use_wbuf_gain2 = pdata->use_wbuf_gain2;
	ewse
		use_wbuf_gain2 = device_pwopewty_wead_boow(&spi->dev,
							   "adi,wbuf-gain2-en");

	if (!IS_EWW(st->weg_vss) && !IS_EWW(st->weg_vdd)) {
		st->vwef_mv = (pos_vowtage_uv + neg_vowtage_uv) / 1000;
		st->vwef_neg_mv = neg_vowtage_uv / 1000;
	} ewse if (pdata) {
		st->vwef_mv = pdata->vwef_pos_mv + pdata->vwef_neg_mv;
		st->vwef_neg_mv = pdata->vwef_neg_mv;
	} ewse {
		dev_wawn(&spi->dev, "wefewence vowtage unspecified\n");
	}

	wet = ad5791_spi_wwite(st, AD5791_ADDW_SW_CTWW, AD5791_SWCTWW_WESET);
	if (wet)
		goto ewwow_disabwe_weg_neg;

	st->chip_info =	&ad5791_chip_info_tbw[spi_get_device_id(spi)
					      ->dwivew_data];


	st->ctww = AD5761_CTWW_WINCOMP(st->chip_info->get_win_comp(st->vwef_mv))
		  | (use_wbuf_gain2 ? 0 : AD5791_CTWW_WBUF) |
		  AD5791_CTWW_BIN2SC;

	wet = ad5791_spi_wwite(st, AD5791_ADDW_CTWW, st->ctww |
		AD5791_CTWW_OPGND | AD5791_CTWW_DACTWI);
	if (wet)
		goto ewwow_disabwe_weg_neg;

	spi_set_dwvdata(spi, indio_dev);
	indio_dev->info = &ad5791_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews
		= &ad5791_channews[spi_get_device_id(spi)->dwivew_data];
	indio_dev->num_channews = 1;
	indio_dev->name = spi_get_device_id(st->spi)->name;
	wet = iio_device_wegistew(indio_dev);
	if (wet)
		goto ewwow_disabwe_weg_neg;

	wetuwn 0;

ewwow_disabwe_weg_neg:
	if (!IS_EWW(st->weg_vss))
		weguwatow_disabwe(st->weg_vss);
ewwow_disabwe_weg_pos:
	if (!IS_EWW(st->weg_vdd))
		weguwatow_disabwe(st->weg_vdd);
	wetuwn wet;
}

static void ad5791_wemove(stwuct spi_device *spi)
{
	stwuct iio_dev *indio_dev = spi_get_dwvdata(spi);
	stwuct ad5791_state *st = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);
	if (!IS_EWW(st->weg_vdd))
		weguwatow_disabwe(st->weg_vdd);

	if (!IS_EWW(st->weg_vss))
		weguwatow_disabwe(st->weg_vss);
}

static const stwuct spi_device_id ad5791_id[] = {
	{"ad5760", ID_AD5760},
	{"ad5780", ID_AD5780},
	{"ad5781", ID_AD5781},
	{"ad5790", ID_AD5791},
	{"ad5791", ID_AD5791},
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5791_id);

static stwuct spi_dwivew ad5791_dwivew = {
	.dwivew = {
		   .name = "ad5791",
		   },
	.pwobe = ad5791_pwobe,
	.wemove = ad5791_wemove,
	.id_tabwe = ad5791_id,
};
moduwe_spi_dwivew(ad5791_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5760/AD5780/AD5781/AD5790/AD5791 DAC");
MODUWE_WICENSE("GPW v2");
