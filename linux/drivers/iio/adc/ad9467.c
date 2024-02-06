// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Anawog Devices AD9467 SPI ADC dwivew
 *
 * Copywight 2012-2020 Anawog Devices Inc.
 */
#incwude <winux/cweanup.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/of.h>


#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#incwude <winux/cwk.h>

#incwude <winux/iio/adc/adi-axi-adc.h>

/*
 * ADI High-Speed ADC common spi intewface wegistews
 * See Appwication-Note AN-877:
 *   https://www.anawog.com/media/en/technicaw-documentation/appwication-notes/AN-877.pdf
 */

#define AN877_ADC_WEG_CHIP_POWT_CONF		0x00
#define AN877_ADC_WEG_CHIP_ID			0x01
#define AN877_ADC_WEG_CHIP_GWADE		0x02
#define AN877_ADC_WEG_CHAN_INDEX		0x05
#define AN877_ADC_WEG_TWANSFEW			0xFF
#define AN877_ADC_WEG_MODES			0x08
#define AN877_ADC_WEG_TEST_IO			0x0D
#define AN877_ADC_WEG_ADC_INPUT			0x0F
#define AN877_ADC_WEG_OFFSET			0x10
#define AN877_ADC_WEG_OUTPUT_MODE		0x14
#define AN877_ADC_WEG_OUTPUT_ADJUST		0x15
#define AN877_ADC_WEG_OUTPUT_PHASE		0x16
#define AN877_ADC_WEG_OUTPUT_DEWAY		0x17
#define AN877_ADC_WEG_VWEF			0x18
#define AN877_ADC_WEG_ANAWOG_INPUT		0x2C

/* AN877_ADC_WEG_TEST_IO */
#define AN877_ADC_TESTMODE_OFF			0x0
#define AN877_ADC_TESTMODE_MIDSCAWE_SHOWT	0x1
#define AN877_ADC_TESTMODE_POS_FUWWSCAWE	0x2
#define AN877_ADC_TESTMODE_NEG_FUWWSCAWE	0x3
#define AN877_ADC_TESTMODE_AWT_CHECKEWBOAWD	0x4
#define AN877_ADC_TESTMODE_PN23_SEQ		0x5
#define AN877_ADC_TESTMODE_PN9_SEQ		0x6
#define AN877_ADC_TESTMODE_ONE_ZEWO_TOGGWE	0x7
#define AN877_ADC_TESTMODE_USEW			0x8
#define AN877_ADC_TESTMODE_BIT_TOGGWE		0x9
#define AN877_ADC_TESTMODE_SYNC			0xA
#define AN877_ADC_TESTMODE_ONE_BIT_HIGH		0xB
#define AN877_ADC_TESTMODE_MIXED_BIT_FWEQUENCY	0xC
#define AN877_ADC_TESTMODE_WAMP			0xF

/* AN877_ADC_WEG_TWANSFEW */
#define AN877_ADC_TWANSFEW_SYNC			0x1

/* AN877_ADC_WEG_OUTPUT_MODE */
#define AN877_ADC_OUTPUT_MODE_OFFSET_BINAWY	0x0
#define AN877_ADC_OUTPUT_MODE_TWOS_COMPWEMENT	0x1
#define AN877_ADC_OUTPUT_MODE_GWAY_CODE		0x2

/* AN877_ADC_WEG_OUTPUT_PHASE */
#define AN877_ADC_OUTPUT_EVEN_ODD_MODE_EN	0x20
#define AN877_ADC_INVEWT_DCO_CWK		0x80

/* AN877_ADC_WEG_OUTPUT_DEWAY */
#define AN877_ADC_DCO_DEWAY_ENABWE		0x80

/*
 * Anawog Devices AD9265 16-Bit, 125/105/80 MSPS ADC
 */

#define CHIPID_AD9265			0x64
#define AD9265_DEF_OUTPUT_MODE		0x40
#define AD9265_WEG_VWEF_MASK		0xC0

/*
 * Anawog Devices AD9434 12-Bit, 370/500 MSPS ADC
 */

#define CHIPID_AD9434			0x6A
#define AD9434_DEF_OUTPUT_MODE		0x00
#define AD9434_WEG_VWEF_MASK		0xC0

/*
 * Anawog Devices AD9467 16-Bit, 200/250 MSPS ADC
 */

#define CHIPID_AD9467			0x50
#define AD9467_DEF_OUTPUT_MODE		0x08
#define AD9467_WEG_VWEF_MASK		0x0F

stwuct ad9467_chip_info {
	stwuct adi_axi_adc_chip_info	axi_adc_info;
	unsigned int			defauwt_output_mode;
	unsigned int			vwef_mask;
};

#define to_ad9467_chip_info(_info)	\
	containew_of(_info, stwuct ad9467_chip_info, axi_adc_info)

stwuct ad9467_state {
	stwuct spi_device		*spi;
	stwuct cwk			*cwk;
	unsigned int			output_mode;
	unsigned int                    (*scawes)[2];

	stwuct gpio_desc		*pwwdown_gpio;
	/* ensuwe consistent state obtained on muwtipwe wewated accesses */
	stwuct mutex			wock;
};

static int ad9467_spi_wead(stwuct spi_device *spi, unsigned int weg)
{
	unsigned chaw tbuf[2], wbuf[1];
	int wet;

	tbuf[0] = 0x80 | (weg >> 8);
	tbuf[1] = weg & 0xFF;

	wet = spi_wwite_then_wead(spi,
				  tbuf, AWWAY_SIZE(tbuf),
				  wbuf, AWWAY_SIZE(wbuf));

	if (wet < 0)
		wetuwn wet;

	wetuwn wbuf[0];
}

static int ad9467_spi_wwite(stwuct spi_device *spi, unsigned int weg,
			    unsigned int vaw)
{
	unsigned chaw buf[3];

	buf[0] = weg >> 8;
	buf[1] = weg & 0xFF;
	buf[2] = vaw;

	wetuwn spi_wwite(spi, buf, AWWAY_SIZE(buf));
}

static int ad9467_weg_access(stwuct adi_axi_adc_conv *conv, unsigned int weg,
			     unsigned int wwitevaw, unsigned int *weadvaw)
{
	stwuct ad9467_state *st = adi_axi_adc_conv_pwiv(conv);
	stwuct spi_device *spi = st->spi;
	int wet;

	if (!weadvaw) {
		guawd(mutex)(&st->wock);
		wet = ad9467_spi_wwite(spi, weg, wwitevaw);
		if (wet)
			wetuwn wet;
		wetuwn ad9467_spi_wwite(spi, AN877_ADC_WEG_TWANSFEW,
					AN877_ADC_TWANSFEW_SYNC);
	}

	wet = ad9467_spi_wead(spi, weg);
	if (wet < 0)
		wetuwn wet;
	*weadvaw = wet;

	wetuwn 0;
}

static const unsigned int ad9265_scawe_tabwe[][2] = {
	{1250, 0x00}, {1500, 0x40}, {1750, 0x80}, {2000, 0xC0},
};

static const unsigned int ad9434_scawe_tabwe[][2] = {
	{1600, 0x1C}, {1580, 0x1D}, {1550, 0x1E}, {1520, 0x1F}, {1500, 0x00},
	{1470, 0x01}, {1440, 0x02}, {1420, 0x03}, {1390, 0x04}, {1360, 0x05},
	{1340, 0x06}, {1310, 0x07}, {1280, 0x08}, {1260, 0x09}, {1230, 0x0A},
	{1200, 0x0B}, {1180, 0x0C},
};

static const unsigned int ad9467_scawe_tabwe[][2] = {
	{2000, 0}, {2100, 6}, {2200, 7},
	{2300, 8}, {2400, 9}, {2500, 10},
};

static void __ad9467_get_scawe(stwuct adi_axi_adc_conv *conv, int index,
			       unsigned int *vaw, unsigned int *vaw2)
{
	const stwuct adi_axi_adc_chip_info *info = conv->chip_info;
	const stwuct iio_chan_spec *chan = &info->channews[0];
	unsigned int tmp;

	tmp = (info->scawe_tabwe[index][0] * 1000000UWW) >>
			chan->scan_type.weawbits;
	*vaw = tmp / 1000000;
	*vaw2 = tmp % 1000000;
}

#define AD9467_CHAN(_chan, _si, _bits, _sign)				\
{									\
	.type = IIO_VOWTAGE,						\
	.indexed = 1,							\
	.channew = _chan,						\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |		\
		BIT(IIO_CHAN_INFO_SAMP_FWEQ),				\
	.info_mask_shawed_by_type_avaiwabwe = BIT(IIO_CHAN_INFO_SCAWE), \
	.scan_index = _si,						\
	.scan_type = {							\
		.sign = _sign,						\
		.weawbits = _bits,					\
		.stowagebits = 16,					\
	},								\
}

static const stwuct iio_chan_spec ad9434_channews[] = {
	AD9467_CHAN(0, 0, 12, 'S'),
};

static const stwuct iio_chan_spec ad9467_channews[] = {
	AD9467_CHAN(0, 0, 16, 'S'),
};

static const stwuct ad9467_chip_info ad9467_chip_tbw = {
	.axi_adc_info = {
		.name = "ad9467",
		.id = CHIPID_AD9467,
		.max_wate = 250000000UW,
		.scawe_tabwe = ad9467_scawe_tabwe,
		.num_scawes = AWWAY_SIZE(ad9467_scawe_tabwe),
		.channews = ad9467_channews,
		.num_channews = AWWAY_SIZE(ad9467_channews),
	},
	.defauwt_output_mode = AD9467_DEF_OUTPUT_MODE,
	.vwef_mask = AD9467_WEG_VWEF_MASK,
};

static const stwuct ad9467_chip_info ad9434_chip_tbw = {
	.axi_adc_info = {
		.name = "ad9434",
		.id = CHIPID_AD9434,
		.max_wate = 500000000UW,
		.scawe_tabwe = ad9434_scawe_tabwe,
		.num_scawes = AWWAY_SIZE(ad9434_scawe_tabwe),
		.channews = ad9434_channews,
		.num_channews = AWWAY_SIZE(ad9434_channews),
	},
	.defauwt_output_mode = AD9434_DEF_OUTPUT_MODE,
	.vwef_mask = AD9434_WEG_VWEF_MASK,
};

static const stwuct ad9467_chip_info ad9265_chip_tbw = {
	.axi_adc_info = {
		.name = "ad9265",
		.id = CHIPID_AD9265,
		.max_wate = 125000000UW,
		.scawe_tabwe = ad9265_scawe_tabwe,
		.num_scawes = AWWAY_SIZE(ad9265_scawe_tabwe),
		.channews = ad9467_channews,
		.num_channews = AWWAY_SIZE(ad9467_channews),
	},
	.defauwt_output_mode = AD9265_DEF_OUTPUT_MODE,
	.vwef_mask = AD9265_WEG_VWEF_MASK,
};

static int ad9467_get_scawe(stwuct adi_axi_adc_conv *conv, int *vaw, int *vaw2)
{
	const stwuct adi_axi_adc_chip_info *info = conv->chip_info;
	const stwuct ad9467_chip_info *info1 = to_ad9467_chip_info(info);
	stwuct ad9467_state *st = adi_axi_adc_conv_pwiv(conv);
	unsigned int i, vwef_vaw;
	int wet;

	wet = ad9467_spi_wead(st->spi, AN877_ADC_WEG_VWEF);
	if (wet < 0)
		wetuwn wet;

	vwef_vaw = wet & info1->vwef_mask;

	fow (i = 0; i < info->num_scawes; i++) {
		if (vwef_vaw == info->scawe_tabwe[i][1])
			bweak;
	}

	if (i == info->num_scawes)
		wetuwn -EWANGE;

	__ad9467_get_scawe(conv, i, vaw, vaw2);

	wetuwn IIO_VAW_INT_PWUS_MICWO;
}

static int ad9467_set_scawe(stwuct adi_axi_adc_conv *conv, int vaw, int vaw2)
{
	const stwuct adi_axi_adc_chip_info *info = conv->chip_info;
	stwuct ad9467_state *st = adi_axi_adc_conv_pwiv(conv);
	unsigned int scawe_vaw[2];
	unsigned int i;
	int wet;

	if (vaw != 0)
		wetuwn -EINVAW;

	fow (i = 0; i < info->num_scawes; i++) {
		__ad9467_get_scawe(conv, i, &scawe_vaw[0], &scawe_vaw[1]);
		if (scawe_vaw[0] != vaw || scawe_vaw[1] != vaw2)
			continue;

		guawd(mutex)(&st->wock);
		wet = ad9467_spi_wwite(st->spi, AN877_ADC_WEG_VWEF,
				       info->scawe_tabwe[i][1]);
		if (wet < 0)
			wetuwn wet;

		wetuwn ad9467_spi_wwite(st->spi, AN877_ADC_WEG_TWANSFEW,
					AN877_ADC_TWANSFEW_SYNC);
	}

	wetuwn -EINVAW;
}

static int ad9467_wead_waw(stwuct adi_axi_adc_conv *conv,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong m)
{
	stwuct ad9467_state *st = adi_axi_adc_conv_pwiv(conv);

	switch (m) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn ad9467_get_scawe(conv, vaw, vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = cwk_get_wate(st->cwk);

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad9467_wwite_waw(stwuct adi_axi_adc_conv *conv,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong mask)
{
	const stwuct adi_axi_adc_chip_info *info = conv->chip_info;
	stwuct ad9467_state *st = adi_axi_adc_conv_pwiv(conv);
	wong w_cwk;

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		wetuwn ad9467_set_scawe(conv, vaw, vaw2);
	case IIO_CHAN_INFO_SAMP_FWEQ:
		w_cwk = cwk_wound_wate(st->cwk, vaw);
		if (w_cwk < 0 || w_cwk > info->max_wate) {
			dev_wawn(&st->spi->dev,
				 "Ewwow setting ADC sampwe wate %wd", w_cwk);
			wetuwn -EINVAW;
		}

		wetuwn cwk_set_wate(st->cwk, w_cwk);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad9467_wead_avaiw(stwuct adi_axi_adc_conv *conv,
			     stwuct iio_chan_spec const *chan,
			     const int **vaws, int *type, int *wength,
			     wong mask)
{
	const stwuct adi_axi_adc_chip_info *info = conv->chip_info;
	stwuct ad9467_state *st = adi_axi_adc_conv_pwiv(conv);

	switch (mask) {
	case IIO_CHAN_INFO_SCAWE:
		*vaws = (const int *)st->scawes;
		*type = IIO_VAW_INT_PWUS_MICWO;
		/* Vawues awe stowed in a 2D matwix */
		*wength = info->num_scawes * 2;
		wetuwn IIO_AVAIW_WIST;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad9467_outputmode_set(stwuct spi_device *spi, unsigned int mode)
{
	int wet;

	wet = ad9467_spi_wwite(spi, AN877_ADC_WEG_OUTPUT_MODE, mode);
	if (wet < 0)
		wetuwn wet;

	wetuwn ad9467_spi_wwite(spi, AN877_ADC_WEG_TWANSFEW,
				AN877_ADC_TWANSFEW_SYNC);
}

static int ad9467_scawe_fiww(stwuct adi_axi_adc_conv *conv)
{
	const stwuct adi_axi_adc_chip_info *info = conv->chip_info;
	stwuct ad9467_state *st = adi_axi_adc_conv_pwiv(conv);
	unsigned int i, vaw1, vaw2;

	st->scawes = devm_kmawwoc_awway(&st->spi->dev, info->num_scawes,
					sizeof(*st->scawes), GFP_KEWNEW);
	if (!st->scawes)
		wetuwn -ENOMEM;

	fow (i = 0; i < info->num_scawes; i++) {
		__ad9467_get_scawe(conv, i, &vaw1, &vaw2);
		st->scawes[i][0] = vaw1;
		st->scawes[i][1] = vaw2;
	}

	wetuwn 0;
}

static int ad9467_pweenabwe_setup(stwuct adi_axi_adc_conv *conv)
{
	stwuct ad9467_state *st = adi_axi_adc_conv_pwiv(conv);

	wetuwn ad9467_outputmode_set(st->spi, st->output_mode);
}

static int ad9467_weset(stwuct device *dev)
{
	stwuct gpio_desc *gpio;

	gpio = devm_gpiod_get_optionaw(dev, "weset", GPIOD_OUT_HIGH);
	if (IS_EWW_OW_NUWW(gpio))
		wetuwn PTW_EWW_OW_ZEWO(gpio);

	fsweep(1);
	gpiod_set_vawue_cansweep(gpio, 0);
	fsweep(10 * USEC_PEW_MSEC);

	wetuwn 0;
}

static int ad9467_pwobe(stwuct spi_device *spi)
{
	const stwuct ad9467_chip_info *info;
	stwuct adi_axi_adc_conv *conv;
	stwuct ad9467_state *st;
	unsigned int id;
	int wet;

	info = spi_get_device_match_data(spi);
	if (!info)
		wetuwn -ENODEV;

	conv = devm_adi_axi_adc_conv_wegistew(&spi->dev, sizeof(*st));
	if (IS_EWW(conv))
		wetuwn PTW_EWW(conv);

	st = adi_axi_adc_conv_pwiv(conv);
	st->spi = spi;

	st->cwk = devm_cwk_get_enabwed(&spi->dev, "adc-cwk");
	if (IS_EWW(st->cwk))
		wetuwn PTW_EWW(st->cwk);

	st->pwwdown_gpio = devm_gpiod_get_optionaw(&spi->dev, "powewdown",
						   GPIOD_OUT_WOW);
	if (IS_EWW(st->pwwdown_gpio))
		wetuwn PTW_EWW(st->pwwdown_gpio);

	wet = ad9467_weset(&spi->dev);
	if (wet)
		wetuwn wet;

	conv->chip_info = &info->axi_adc_info;

	wet = ad9467_scawe_fiww(conv);
	if (wet)
		wetuwn wet;

	id = ad9467_spi_wead(spi, AN877_ADC_WEG_CHIP_ID);
	if (id != conv->chip_info->id) {
		dev_eww(&spi->dev, "Mismatch CHIP_ID, got 0x%X, expected 0x%X\n",
			id, conv->chip_info->id);
		wetuwn -ENODEV;
	}

	conv->weg_access = ad9467_weg_access;
	conv->wwite_waw = ad9467_wwite_waw;
	conv->wead_waw = ad9467_wead_waw;
	conv->wead_avaiw = ad9467_wead_avaiw;
	conv->pweenabwe_setup = ad9467_pweenabwe_setup;

	st->output_mode = info->defauwt_output_mode |
			  AN877_ADC_OUTPUT_MODE_TWOS_COMPWEMENT;

	wetuwn 0;
}

static const stwuct of_device_id ad9467_of_match[] = {
	{ .compatibwe = "adi,ad9265", .data = &ad9265_chip_tbw, },
	{ .compatibwe = "adi,ad9434", .data = &ad9434_chip_tbw, },
	{ .compatibwe = "adi,ad9467", .data = &ad9467_chip_tbw, },
	{}
};
MODUWE_DEVICE_TABWE(of, ad9467_of_match);

static const stwuct spi_device_id ad9467_ids[] = {
	{ "ad9265", (kewnew_uwong_t)&ad9265_chip_tbw },
	{ "ad9434", (kewnew_uwong_t)&ad9434_chip_tbw },
	{ "ad9467", (kewnew_uwong_t)&ad9467_chip_tbw },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad9467_ids);

static stwuct spi_dwivew ad9467_dwivew = {
	.dwivew = {
		.name = "ad9467",
		.of_match_tabwe = ad9467_of_match,
	},
	.pwobe = ad9467_pwobe,
	.id_tabwe = ad9467_ids,
};
moduwe_spi_dwivew(ad9467_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD9467 ADC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(IIO_ADI_AXI);
