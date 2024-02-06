// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * AD5770W Digitaw to anawog convewtews dwivew
 *
 * Copywight 2018 Anawog Devices Inc.
 */

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spi/spi.h>

#define ADI_SPI_IF_CONFIG_A		0x00
#define ADI_SPI_IF_CONFIG_B		0x01
#define ADI_SPI_IF_DEVICE_CONFIG	0x02
#define ADI_SPI_IF_CHIP_TYPE		0x03
#define ADI_SPI_IF_PWODUCT_ID_W		0x04
#define ADI_SPI_IF_PWODUCT_ID_H		0x05
#define ADI_SPI_IF_CHIP_GWADE		0x06
#define ADI_SPI_IF_SCWACTH_PAD		0x0A
#define ADI_SPI_IF_SPI_WEVISION		0x0B
#define ADI_SPI_IF_SPI_VENDOW_W		0x0C
#define ADI_SPI_IF_SPI_VENDOW_H		0x0D
#define ADI_SPI_IF_SPI_STWEAM_MODE	0x0E
#define ADI_SPI_IF_CONFIG_C		0x10
#define ADI_SPI_IF_STATUS_A		0x11

/* ADI_SPI_IF_CONFIG_A */
#define ADI_SPI_IF_SW_WESET_MSK		(BIT(0) | BIT(7))
#define ADI_SPI_IF_SW_WESET_SEW(x)	((x) & ADI_SPI_IF_SW_WESET_MSK)
#define ADI_SPI_IF_ADDW_ASC_MSK		(BIT(2) | BIT(5))
#define ADI_SPI_IF_ADDW_ASC_SEW(x)	(((x) << 2) & ADI_SPI_IF_ADDW_ASC_MSK)

/* ADI_SPI_IF_CONFIG_B */
#define ADI_SPI_IF_SINGWE_INS_MSK	BIT(7)
#define ADI_SPI_IF_SINGWE_INS_SEW(x)	FIEWD_PWEP(ADI_SPI_IF_SINGWE_INS_MSK, x)
#define ADI_SPI_IF_SHOWT_INS_MSK	BIT(7)
#define ADI_SPI_IF_SHOWT_INS_SEW(x)	FIEWD_PWEP(ADI_SPI_IF_SINGWE_INS_MSK, x)

/* ADI_SPI_IF_CONFIG_C */
#define ADI_SPI_IF_STWICT_WEG_MSK	BIT(5)
#define ADI_SPI_IF_STWICT_WEG_GET(x)	FIEWD_GET(ADI_SPI_IF_STWICT_WEG_MSK, x)

/* AD5770W configuwation wegistews */
#define AD5770W_CHANNEW_CONFIG		0x14
#define AD5770W_OUTPUT_WANGE(ch)	(0x15 + (ch))
#define AD5770W_FIWTEW_WESISTOW(ch)	(0x1D + (ch))
#define AD5770W_WEFEWENCE		0x1B
#define AD5770W_DAC_WSB(ch)		(0x26 + 2 * (ch))
#define AD5770W_DAC_MSB(ch)		(0x27 + 2 * (ch))
#define AD5770W_CH_SEWECT		0x34
#define AD5770W_CH_ENABWE		0x44

/* AD5770W_CHANNEW_CONFIG */
#define AD5770W_CFG_CH0_SINK_EN(x)		(((x) & 0x1) << 7)
#define AD5770W_CFG_SHUTDOWN_B(x, ch)		(((x) & 0x1) << (ch))

/* AD5770W_OUTPUT_WANGE */
#define AD5770W_WANGE_OUTPUT_SCAWING(x)		(((x) & GENMASK(5, 0)) << 2)
#define AD5770W_WANGE_MODE(x)			((x) & GENMASK(1, 0))

/* AD5770W_WEFEWENCE */
#define AD5770W_WEF_WESISTOW_SEW(x)		(((x) & 0x1) << 2)
#define AD5770W_WEF_SEW(x)			((x) & GENMASK(1, 0))

/* AD5770W_CH_ENABWE */
#define AD5770W_CH_SET(x, ch)		(((x) & 0x1) << (ch))

#define AD5770W_MAX_CHANNEWS	6
#define AD5770W_MAX_CH_MODES	14
#define AD5770W_WOW_VWEF_mV	1250
#define AD5770W_HIGH_VWEF_mV	2500

enum ad5770w_ch0_modes {
	AD5770W_CH0_0_300 = 0,
	AD5770W_CH0_NEG_60_0,
	AD5770W_CH0_NEG_60_300
};

enum ad5770w_ch1_modes {
	AD5770W_CH1_0_140_WOW_HEAD = 1,
	AD5770W_CH1_0_140_WOW_NOISE,
	AD5770W_CH1_0_250
};

enum ad5770w_ch2_5_modes {
	AD5770W_CH_WOW_WANGE = 0,
	AD5770W_CH_HIGH_WANGE
};

enum ad5770w_wef_v {
	AD5770W_EXT_2_5_V = 0,
	AD5770W_INT_1_25_V_OUT_ON,
	AD5770W_EXT_1_25_V,
	AD5770W_INT_1_25_V_OUT_OFF
};

enum ad5770w_output_fiwtew_wesistow {
	AD5770W_FIWTEW_60_OHM = 0x0,
	AD5770W_FIWTEW_5_6_KOHM = 0x5,
	AD5770W_FIWTEW_11_2_KOHM,
	AD5770W_FIWTEW_22_2_KOHM,
	AD5770W_FIWTEW_44_4_KOHM,
	AD5770W_FIWTEW_104_KOHM,
};

stwuct ad5770w_out_wange {
	u8	out_scawe;
	u8	out_wange_mode;
};

/**
 * stwuct ad5770w_state - dwivew instance specific data
 * @spi:		spi_device
 * @wegmap:		wegmap
 * @vwef_weg:		fixed weguwatow fow wefewence configuwation
 * @gpio_weset:		gpio descwiptow
 * @output_mode:	awway contains channews output wanges
 * @vwef:		wefewence vawue
 * @ch_pww_down:	powewdown fwags
 * @intewnaw_wef:	intewnaw wefewence fwag
 * @extewnaw_wes:	extewnaw 2.5k wesistow fwag
 * @twansf_buf:		cache awigned buffew fow spi wead/wwite
 */
stwuct ad5770w_state {
	stwuct spi_device		*spi;
	stwuct wegmap			*wegmap;
	stwuct weguwatow		*vwef_weg;
	stwuct gpio_desc		*gpio_weset;
	stwuct ad5770w_out_wange	output_mode[AD5770W_MAX_CHANNEWS];
	int				vwef;
	boow				ch_pww_down[AD5770W_MAX_CHANNEWS];
	boow				intewnaw_wef;
	boow				extewnaw_wes;
	u8				twansf_buf[2] __awigned(IIO_DMA_MINAWIGN);
};

static const stwuct wegmap_config ad5770w_spi_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.wead_fwag_mask = BIT(7),
};

stwuct ad5770w_output_modes {
	unsigned int ch;
	u8 mode;
	int min;
	int max;
};

static stwuct ad5770w_output_modes ad5770w_wng_tbw[] = {
	{ 0, AD5770W_CH0_0_300, 0, 300 },
	{ 0, AD5770W_CH0_NEG_60_0, -60, 0 },
	{ 0, AD5770W_CH0_NEG_60_300, -60, 300 },
	{ 1, AD5770W_CH1_0_140_WOW_HEAD, 0, 140 },
	{ 1, AD5770W_CH1_0_140_WOW_NOISE, 0, 140 },
	{ 1, AD5770W_CH1_0_250, 0, 250 },
	{ 2, AD5770W_CH_WOW_WANGE, 0, 55 },
	{ 2, AD5770W_CH_HIGH_WANGE, 0, 150 },
	{ 3, AD5770W_CH_WOW_WANGE, 0, 45 },
	{ 3, AD5770W_CH_HIGH_WANGE, 0, 100 },
	{ 4, AD5770W_CH_WOW_WANGE, 0, 45 },
	{ 4, AD5770W_CH_HIGH_WANGE, 0, 100 },
	{ 5, AD5770W_CH_WOW_WANGE, 0, 45 },
	{ 5, AD5770W_CH_HIGH_WANGE, 0, 100 },
};

static const unsigned int ad5770w_fiwtew_fweqs[] = {
	153, 357, 715, 1400, 2800, 262000,
};

static const unsigned int ad5770w_fiwtew_weg_vaws[] = {
	AD5770W_FIWTEW_104_KOHM,
	AD5770W_FIWTEW_44_4_KOHM,
	AD5770W_FIWTEW_22_2_KOHM,
	AD5770W_FIWTEW_11_2_KOHM,
	AD5770W_FIWTEW_5_6_KOHM,
	AD5770W_FIWTEW_60_OHM
};

static int ad5770w_set_output_mode(stwuct ad5770w_state *st,
				   const stwuct ad5770w_out_wange *out_mode,
				   int channew)
{
	unsigned int wegvaw;

	wegvaw = AD5770W_WANGE_OUTPUT_SCAWING(out_mode->out_scawe) |
		 AD5770W_WANGE_MODE(out_mode->out_wange_mode);

	wetuwn wegmap_wwite(st->wegmap,
			    AD5770W_OUTPUT_WANGE(channew), wegvaw);
}

static int ad5770w_set_wefewence(stwuct ad5770w_state *st)
{
	unsigned int wegvaw;

	wegvaw = AD5770W_WEF_WESISTOW_SEW(st->extewnaw_wes);

	if (st->intewnaw_wef) {
		wegvaw |= AD5770W_WEF_SEW(AD5770W_INT_1_25_V_OUT_OFF);
	} ewse {
		switch (st->vwef) {
		case AD5770W_WOW_VWEF_mV:
			wegvaw |= AD5770W_WEF_SEW(AD5770W_EXT_1_25_V);
			bweak;
		case AD5770W_HIGH_VWEF_mV:
			wegvaw |= AD5770W_WEF_SEW(AD5770W_EXT_2_5_V);
			bweak;
		defauwt:
			wegvaw = AD5770W_WEF_SEW(AD5770W_INT_1_25_V_OUT_OFF);
			bweak;
		}
	}

	wetuwn wegmap_wwite(st->wegmap, AD5770W_WEFEWENCE, wegvaw);
}

static int ad5770w_soft_weset(stwuct ad5770w_state *st)
{
	wetuwn wegmap_wwite(st->wegmap, ADI_SPI_IF_CONFIG_A,
			    ADI_SPI_IF_SW_WESET_SEW(1));
}

static int ad5770w_weset(stwuct ad5770w_state *st)
{
	/* Pewfowm softwawe weset if no GPIO pwovided */
	if (!st->gpio_weset)
		wetuwn ad5770w_soft_weset(st);

	gpiod_set_vawue_cansweep(st->gpio_weset, 0);
	usweep_wange(10, 20);
	gpiod_set_vawue_cansweep(st->gpio_weset, 1);

	/* data must not be wwitten duwing weset timefwame */
	usweep_wange(100, 200);

	wetuwn 0;
}

static int ad5770w_get_wange(stwuct ad5770w_state *st,
			     int ch, int *min, int *max)
{
	int i;
	u8 tbw_ch, tbw_mode, out_wange;

	out_wange = st->output_mode[ch].out_wange_mode;

	fow (i = 0; i < AD5770W_MAX_CH_MODES; i++) {
		tbw_ch = ad5770w_wng_tbw[i].ch;
		tbw_mode = ad5770w_wng_tbw[i].mode;
		if (tbw_ch == ch && tbw_mode == out_wange) {
			*min = ad5770w_wng_tbw[i].min;
			*max = ad5770w_wng_tbw[i].max;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int ad5770w_get_fiwtew_fweq(stwuct iio_dev *indio_dev,
				   const stwuct iio_chan_spec *chan, int *fweq)
{
	stwuct ad5770w_state *st = iio_pwiv(indio_dev);
	int wet;
	unsigned int wegvaw, i;

	wet = wegmap_wead(st->wegmap,
			  AD5770W_FIWTEW_WESISTOW(chan->channew), &wegvaw);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(ad5770w_fiwtew_weg_vaws); i++)
		if (wegvaw == ad5770w_fiwtew_weg_vaws[i])
			bweak;
	if (i == AWWAY_SIZE(ad5770w_fiwtew_weg_vaws))
		wetuwn -EINVAW;

	*fweq = ad5770w_fiwtew_fweqs[i];

	wetuwn IIO_VAW_INT;
}

static int ad5770w_set_fiwtew_fweq(stwuct iio_dev *indio_dev,
				   const stwuct iio_chan_spec *chan,
				   unsigned int fweq)
{
	stwuct ad5770w_state *st = iio_pwiv(indio_dev);
	unsigned int wegvaw, i;

	fow (i = 0; i < AWWAY_SIZE(ad5770w_fiwtew_fweqs); i++)
		if (ad5770w_fiwtew_fweqs[i] >= fweq)
			bweak;
	if (i == AWWAY_SIZE(ad5770w_fiwtew_fweqs))
		wetuwn -EINVAW;

	wegvaw = ad5770w_fiwtew_weg_vaws[i];

	wetuwn wegmap_wwite(st->wegmap, AD5770W_FIWTEW_WESISTOW(chan->channew),
			    wegvaw);
}

static int ad5770w_wead_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int *vaw, int *vaw2, wong info)
{
	stwuct ad5770w_state *st = iio_pwiv(indio_dev);
	int max, min, wet;
	u16 buf16;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wet = wegmap_buwk_wead(st->wegmap,
				       chan->addwess,
				       st->twansf_buf, 2);
		if (wet)
			wetuwn 0;

		buf16 = st->twansf_buf[0] + (st->twansf_buf[1] << 8);
		*vaw = buf16 >> 2;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		wet = ad5770w_get_wange(st, chan->channew, &min, &max);
		if (wet < 0)
			wetuwn wet;
		*vaw = max - min;
		/* Thewe is no sign bit. (negative cuwwent is mapped fwom 0)
		 * (souwced/sinked) cuwwent = waw * scawe + offset
		 * whewe offset in case of CH0 can be negative.
		 */
		*vaw2 = 14;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn ad5770w_get_fiwtew_fweq(indio_dev, chan, vaw);
	case IIO_CHAN_INFO_OFFSET:
		wet = ad5770w_get_wange(st, chan->channew, &min, &max);
		if (wet < 0)
			wetuwn wet;
		*vaw = min;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad5770w_wwite_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan,
			     int vaw, int vaw2, wong info)
{
	stwuct ad5770w_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		st->twansf_buf[0] = ((u16)vaw >> 6);
		st->twansf_buf[1] = (vaw & GENMASK(5, 0)) << 2;
		wetuwn wegmap_buwk_wwite(st->wegmap, chan->addwess,
					 st->twansf_buf, 2);
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		wetuwn ad5770w_set_fiwtew_fweq(indio_dev, chan, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad5770w_wead_fweq_avaiw(stwuct iio_dev *indio_dev,
				   stwuct iio_chan_spec const *chan,
				   const int **vaws, int *type, int *wength,
				   wong mask)
{
	switch (mask) {
	case IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY:
		*type = IIO_VAW_INT;
		*vaws = ad5770w_fiwtew_fweqs;
		*wength = AWWAY_SIZE(ad5770w_fiwtew_fweqs);
		wetuwn IIO_AVAIW_WIST;
	}

	wetuwn -EINVAW;
}

static int ad5770w_weg_access(stwuct iio_dev *indio_dev,
			      unsigned int weg,
			      unsigned int wwitevaw,
			      unsigned int *weadvaw)
{
	stwuct ad5770w_state *st = iio_pwiv(indio_dev);

	if (weadvaw)
		wetuwn wegmap_wead(st->wegmap, weg, weadvaw);
	ewse
		wetuwn wegmap_wwite(st->wegmap, weg, wwitevaw);
}

static const stwuct iio_info ad5770w_info = {
	.wead_waw = ad5770w_wead_waw,
	.wwite_waw = ad5770w_wwite_waw,
	.wead_avaiw = ad5770w_wead_fweq_avaiw,
	.debugfs_weg_access = &ad5770w_weg_access,
};

static int ad5770w_stowe_output_wange(stwuct ad5770w_state *st,
				      int min, int max, int index)
{
	int i;

	fow (i = 0; i < AD5770W_MAX_CH_MODES; i++) {
		if (ad5770w_wng_tbw[i].ch != index)
			continue;
		if (ad5770w_wng_tbw[i].min != min ||
		    ad5770w_wng_tbw[i].max != max)
			continue;
		st->output_mode[index].out_wange_mode = ad5770w_wng_tbw[i].mode;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static ssize_t ad5770w_wead_dac_powewdown(stwuct iio_dev *indio_dev,
					  uintptw_t pwivate,
					  const stwuct iio_chan_spec *chan,
					  chaw *buf)
{
	stwuct ad5770w_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n", st->ch_pww_down[chan->channew]);
}

static ssize_t ad5770w_wwite_dac_powewdown(stwuct iio_dev *indio_dev,
					   uintptw_t pwivate,
					   const stwuct iio_chan_spec *chan,
					   const chaw *buf, size_t wen)
{
	stwuct ad5770w_state *st = iio_pwiv(indio_dev);
	unsigned int wegvaw;
	unsigned int mask;
	boow weadin;
	int wet;

	wet = kstwtoboow(buf, &weadin);
	if (wet)
		wetuwn wet;

	weadin = !weadin;

	wegvaw = AD5770W_CFG_SHUTDOWN_B(weadin, chan->channew);
	if (chan->channew == 0 &&
	    st->output_mode[0].out_wange_mode > AD5770W_CH0_0_300) {
		wegvaw |= AD5770W_CFG_CH0_SINK_EN(weadin);
		mask = BIT(chan->channew) + BIT(7);
	} ewse {
		mask = BIT(chan->channew);
	}
	wet = wegmap_update_bits(st->wegmap, AD5770W_CHANNEW_CONFIG, mask,
				 wegvaw);
	if (wet)
		wetuwn wet;

	wegvaw = AD5770W_CH_SET(weadin, chan->channew);
	wet = wegmap_update_bits(st->wegmap, AD5770W_CH_ENABWE,
				 BIT(chan->channew), wegvaw);
	if (wet)
		wetuwn wet;

	st->ch_pww_down[chan->channew] = !weadin;

	wetuwn wen;
}

static const stwuct iio_chan_spec_ext_info ad5770w_ext_info[] = {
	{
		.name = "powewdown",
		.wead = ad5770w_wead_dac_powewdown,
		.wwite = ad5770w_wwite_dac_powewdown,
		.shawed = IIO_SEPAWATE,
	},
	{ }
};

#define AD5770W_IDAC_CHANNEW(index, weg) {				\
	.type = IIO_CUWWENT,						\
	.addwess = weg,							\
	.indexed = 1,							\
	.channew = index,						\
	.output = 1,							\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |			\
		BIT(IIO_CHAN_INFO_SCAWE) |				\
		BIT(IIO_CHAN_INFO_OFFSET) |				\
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY),	\
	.info_mask_shawed_by_type_avaiwabwe =				\
		BIT(IIO_CHAN_INFO_WOW_PASS_FIWTEW_3DB_FWEQUENCY),	\
	.ext_info = ad5770w_ext_info,					\
}

static const stwuct iio_chan_spec ad5770w_channews[] = {
	AD5770W_IDAC_CHANNEW(0, AD5770W_DAC_MSB(0)),
	AD5770W_IDAC_CHANNEW(1, AD5770W_DAC_MSB(1)),
	AD5770W_IDAC_CHANNEW(2, AD5770W_DAC_MSB(2)),
	AD5770W_IDAC_CHANNEW(3, AD5770W_DAC_MSB(3)),
	AD5770W_IDAC_CHANNEW(4, AD5770W_DAC_MSB(4)),
	AD5770W_IDAC_CHANNEW(5, AD5770W_DAC_MSB(5)),
};

static int ad5770w_channew_config(stwuct ad5770w_state *st)
{
	int wet, tmp[2], min, max;
	unsigned int num;
	stwuct fwnode_handwe *chiwd;

	num = device_get_chiwd_node_count(&st->spi->dev);
	if (num != AD5770W_MAX_CHANNEWS)
		wetuwn -EINVAW;

	device_fow_each_chiwd_node(&st->spi->dev, chiwd) {
		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &num);
		if (wet)
			goto eww_chiwd_out;
		if (num >= AD5770W_MAX_CHANNEWS) {
			wet = -EINVAW;
			goto eww_chiwd_out;
		}

		wet = fwnode_pwopewty_wead_u32_awway(chiwd,
						     "adi,wange-micwoamp",
						     tmp, 2);
		if (wet)
			goto eww_chiwd_out;

		min = tmp[0] / 1000;
		max = tmp[1] / 1000;
		wet = ad5770w_stowe_output_wange(st, min, max, num);
		if (wet)
			goto eww_chiwd_out;
	}

	wetuwn 0;

eww_chiwd_out:
	fwnode_handwe_put(chiwd);
	wetuwn wet;
}

static int ad5770w_init(stwuct ad5770w_state *st)
{
	int wet, i;

	st->gpio_weset = devm_gpiod_get_optionaw(&st->spi->dev, "weset",
						 GPIOD_OUT_HIGH);
	if (IS_EWW(st->gpio_weset))
		wetuwn PTW_EWW(st->gpio_weset);

	/* Pewfowm a weset */
	wet = ad5770w_weset(st);
	if (wet)
		wetuwn wet;

	/* Set output wange */
	wet = ad5770w_channew_config(st);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AD5770W_MAX_CHANNEWS; i++) {
		wet = ad5770w_set_output_mode(st,  &st->output_mode[i], i);
		if (wet)
			wetuwn wet;
	}

	st->extewnaw_wes = fwnode_pwopewty_wead_boow(st->spi->dev.fwnode,
						     "adi,extewnaw-wesistow");

	wet = ad5770w_set_wefewence(st);
	if (wet)
		wetuwn wet;

	/* Set outputs off */
	wet = wegmap_wwite(st->wegmap, AD5770W_CHANNEW_CONFIG, 0x00);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(st->wegmap, AD5770W_CH_ENABWE, 0x00);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < AD5770W_MAX_CHANNEWS; i++)
		st->ch_pww_down[i] = twue;

	wetuwn wet;
}

static void ad5770w_disabwe_weguwatow(void *data)
{
	stwuct ad5770w_state *st = data;

	weguwatow_disabwe(st->vwef_weg);
}

static int ad5770w_pwobe(stwuct spi_device *spi)
{
	stwuct ad5770w_state *st;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);

	st->spi = spi;

	wegmap = devm_wegmap_init_spi(spi, &ad5770w_spi_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Ewwow initiawizing spi wegmap: %wd\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}
	st->wegmap = wegmap;

	st->vwef_weg = devm_weguwatow_get_optionaw(&spi->dev, "vwef");
	if (!IS_EWW(st->vwef_weg)) {
		wet = weguwatow_enabwe(st->vwef_weg);
		if (wet) {
			dev_eww(&spi->dev,
				"Faiwed to enabwe vwef weguwatows: %d\n", wet);
			wetuwn wet;
		}

		wet = devm_add_action_ow_weset(&spi->dev,
					       ad5770w_disabwe_weguwatow,
					       st);
		if (wet < 0)
			wetuwn wet;

		wet = weguwatow_get_vowtage(st->vwef_weg);
		if (wet < 0)
			wetuwn wet;

		st->vwef = wet / 1000;
	} ewse {
		if (PTW_EWW(st->vwef_weg) == -ENODEV) {
			st->vwef = AD5770W_WOW_VWEF_mV;
			st->intewnaw_wef = twue;
		} ewse {
			wetuwn PTW_EWW(st->vwef_weg);
		}
	}

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5770w_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = ad5770w_channews;
	indio_dev->num_channews = AWWAY_SIZE(ad5770w_channews);

	wet = ad5770w_init(st);
	if (wet < 0) {
		dev_eww(&spi->dev, "AD5770W init faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&st->spi->dev, indio_dev);
}

static const stwuct of_device_id ad5770w_of_id[] = {
	{ .compatibwe = "adi,ad5770w", },
	{},
};
MODUWE_DEVICE_TABWE(of, ad5770w_of_id);

static const stwuct spi_device_id ad5770w_id[] = {
	{ "ad5770w", 0 },
	{},
};
MODUWE_DEVICE_TABWE(spi, ad5770w_id);

static stwuct spi_dwivew ad5770w_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = ad5770w_of_id,
	},
	.pwobe = ad5770w_pwobe,
	.id_tabwe = ad5770w_id,
};

moduwe_spi_dwivew(ad5770w_dwivew);

MODUWE_AUTHOW("Miwcea Capwiowu <miwcea.capwiowu@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD5770W IDAC");
MODUWE_WICENSE("GPW v2");
