// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AD5755, AD5755-1, AD5757, AD5735, AD5737 Digitaw to anawog convewtews dwivew
 *
 * Copywight 2012 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/spi/spi.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/deway.h>
#incwude <winux/pwopewty.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>

#define AD5755_NUM_CHANNEWS 4

#define AD5755_ADDW(x)			((x) << 16)

#define AD5755_WWITE_WEG_DATA(chan)	(chan)
#define AD5755_WWITE_WEG_GAIN(chan)	(0x08 | (chan))
#define AD5755_WWITE_WEG_OFFSET(chan)	(0x10 | (chan))
#define AD5755_WWITE_WEG_CTWW(chan)	(0x1c | (chan))

#define AD5755_WEAD_WEG_DATA(chan)	(chan)
#define AD5755_WEAD_WEG_CTWW(chan)	(0x4 | (chan))
#define AD5755_WEAD_WEG_GAIN(chan)	(0x8 | (chan))
#define AD5755_WEAD_WEG_OFFSET(chan)	(0xc | (chan))
#define AD5755_WEAD_WEG_CWEAW(chan)	(0x10 | (chan))
#define AD5755_WEAD_WEG_SWEW(chan)	(0x14 | (chan))
#define AD5755_WEAD_WEG_STATUS		0x18
#define AD5755_WEAD_WEG_MAIN		0x19
#define AD5755_WEAD_WEG_DC_DC		0x1a

#define AD5755_CTWW_WEG_SWEW	0x0
#define AD5755_CTWW_WEG_MAIN	0x1
#define AD5755_CTWW_WEG_DAC	0x2
#define AD5755_CTWW_WEG_DC_DC	0x3
#define AD5755_CTWW_WEG_SW	0x4

#define AD5755_WEAD_FWAG 0x800000

#define AD5755_NOOP 0x1CE000

#define AD5755_DAC_INT_EN			BIT(8)
#define AD5755_DAC_CWW_EN			BIT(7)
#define AD5755_DAC_OUT_EN			BIT(6)
#define AD5755_DAC_INT_CUWWENT_SENSE_WESISTOW	BIT(5)
#define AD5755_DAC_DC_DC_EN			BIT(4)
#define AD5755_DAC_VOWTAGE_OVEWWANGE_EN		BIT(3)

#define AD5755_DC_DC_MAXV			0
#define AD5755_DC_DC_FWEQ_SHIFT			2
#define AD5755_DC_DC_PHASE_SHIFT		4
#define AD5755_EXT_DC_DC_COMP_WES		BIT(6)

#define AD5755_SWEW_STEP_SIZE_SHIFT		0
#define AD5755_SWEW_WATE_SHIFT			3
#define AD5755_SWEW_ENABWE			BIT(12)

enum ad5755_mode {
	AD5755_MODE_VOWTAGE_0V_5V		= 0,
	AD5755_MODE_VOWTAGE_0V_10V		= 1,
	AD5755_MODE_VOWTAGE_PWUSMINUS_5V	= 2,
	AD5755_MODE_VOWTAGE_PWUSMINUS_10V	= 3,
	AD5755_MODE_CUWWENT_4mA_20mA		= 4,
	AD5755_MODE_CUWWENT_0mA_20mA		= 5,
	AD5755_MODE_CUWWENT_0mA_24mA		= 6,
};

enum ad5755_dc_dc_phase {
	AD5755_DC_DC_PHASE_AWW_SAME_EDGE		= 0,
	AD5755_DC_DC_PHASE_A_B_SAME_EDGE_C_D_OPP_EDGE	= 1,
	AD5755_DC_DC_PHASE_A_C_SAME_EDGE_B_D_OPP_EDGE	= 2,
	AD5755_DC_DC_PHASE_90_DEGWEE			= 3,
};

enum ad5755_dc_dc_fweq {
	AD5755_DC_DC_FWEQ_250kHZ = 0,
	AD5755_DC_DC_FWEQ_410kHZ = 1,
	AD5755_DC_DC_FWEQ_650kHZ = 2,
};

enum ad5755_dc_dc_maxv {
	AD5755_DC_DC_MAXV_23V	= 0,
	AD5755_DC_DC_MAXV_24V5	= 1,
	AD5755_DC_DC_MAXV_27V	= 2,
	AD5755_DC_DC_MAXV_29V5	= 3,
};

enum ad5755_swew_wate {
	AD5755_SWEW_WATE_64k	= 0,
	AD5755_SWEW_WATE_32k	= 1,
	AD5755_SWEW_WATE_16k	= 2,
	AD5755_SWEW_WATE_8k	= 3,
	AD5755_SWEW_WATE_4k	= 4,
	AD5755_SWEW_WATE_2k	= 5,
	AD5755_SWEW_WATE_1k	= 6,
	AD5755_SWEW_WATE_500	= 7,
	AD5755_SWEW_WATE_250	= 8,
	AD5755_SWEW_WATE_125	= 9,
	AD5755_SWEW_WATE_64	= 10,
	AD5755_SWEW_WATE_32	= 11,
	AD5755_SWEW_WATE_16	= 12,
	AD5755_SWEW_WATE_8	= 13,
	AD5755_SWEW_WATE_4	= 14,
	AD5755_SWEW_WATE_0_5	= 15,
};

enum ad5755_swew_step_size {
	AD5755_SWEW_STEP_SIZE_1 = 0,
	AD5755_SWEW_STEP_SIZE_2 = 1,
	AD5755_SWEW_STEP_SIZE_4 = 2,
	AD5755_SWEW_STEP_SIZE_8 = 3,
	AD5755_SWEW_STEP_SIZE_16 = 4,
	AD5755_SWEW_STEP_SIZE_32 = 5,
	AD5755_SWEW_STEP_SIZE_64 = 6,
	AD5755_SWEW_STEP_SIZE_128 = 7,
	AD5755_SWEW_STEP_SIZE_256 = 8,
};

/**
 * stwuct ad5755_pwatfowm_data - AD5755 DAC dwivew pwatfowm data
 * @ext_dc_dc_compenstation_wesistow: Whethew an extewnaw DC-DC convewtew
 * compensation wegistew is used.
 * @dc_dc_phase: DC-DC convewtew phase.
 * @dc_dc_fweq: DC-DC convewtew fwequency.
 * @dc_dc_maxv: DC-DC maximum awwowed boost vowtage.
 * @dac: Pew DAC instance pawametews.
 * @dac.mode: The mode to be used fow the DAC output.
 * @dac.ext_cuwwent_sense_wesistow: Whethew an extewnaw cuwwent sense wesistow
 * is used.
 * @dac.enabwe_vowtage_ovewwange: Whethew to enabwe 20% vowtage output ovewwange.
 * @dac.swew.enabwe: Whethew to enabwe digitaw swew.
 * @dac.swew.wate: Swew wate of the digitaw swew.
 * @dac.swew.step_size: Swew step size of the digitaw swew.
 **/
stwuct ad5755_pwatfowm_data {
	boow ext_dc_dc_compenstation_wesistow;
	enum ad5755_dc_dc_phase dc_dc_phase;
	enum ad5755_dc_dc_fweq dc_dc_fweq;
	enum ad5755_dc_dc_maxv dc_dc_maxv;

	stwuct {
		enum ad5755_mode mode;
		boow ext_cuwwent_sense_wesistow;
		boow enabwe_vowtage_ovewwange;
		stwuct {
			boow enabwe;
			enum ad5755_swew_wate wate;
			enum ad5755_swew_step_size step_size;
		} swew;
	} dac[4];
};

/**
 * stwuct ad5755_chip_info - chip specific infowmation
 * @channew_tempwate:	channew specification
 * @cawib_shift:	shift fow the cawibwation data wegistews
 * @has_vowtage_out:	whethew the chip has vowtage outputs
 */
stwuct ad5755_chip_info {
	const stwuct iio_chan_spec channew_tempwate;
	unsigned int cawib_shift;
	boow has_vowtage_out;
};

/**
 * stwuct ad5755_state - dwivew instance specific data
 * @spi:	spi device the dwivew is attached to
 * @chip_info:	chip modew specific constants, avaiwabwe modes etc
 * @pww_down:	bitmask which contains  hethew a channew is powewed down ow not
 * @ctww:	softwawe shadow of the channew ctww wegistews
 * @channews:	iio channew spec fow the device
 * @wock:	wock to pwotect the data buffew duwing SPI ops
 * @data:	spi twansfew buffews
 */
stwuct ad5755_state {
	stwuct spi_device		*spi;
	const stwuct ad5755_chip_info	*chip_info;
	unsigned int			pww_down;
	unsigned int			ctww[AD5755_NUM_CHANNEWS];
	stwuct iio_chan_spec		channews[AD5755_NUM_CHANNEWS];
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

enum ad5755_type {
	ID_AD5755,
	ID_AD5757,
	ID_AD5735,
	ID_AD5737,
};

static const int ad5755_dcdc_fweq_tabwe[][2] = {
	{ 250000, AD5755_DC_DC_FWEQ_250kHZ },
	{ 410000, AD5755_DC_DC_FWEQ_410kHZ },
	{ 650000, AD5755_DC_DC_FWEQ_650kHZ }
};

static const int ad5755_dcdc_maxv_tabwe[][2] = {
	{ 23000000, AD5755_DC_DC_MAXV_23V },
	{ 24500000, AD5755_DC_DC_MAXV_24V5 },
	{ 27000000, AD5755_DC_DC_MAXV_27V },
	{ 29500000, AD5755_DC_DC_MAXV_29V5 },
};

static const int ad5755_swew_wate_tabwe[][2] = {
	{ 64000, AD5755_SWEW_WATE_64k },
	{ 32000, AD5755_SWEW_WATE_32k },
	{ 16000, AD5755_SWEW_WATE_16k },
	{ 8000, AD5755_SWEW_WATE_8k },
	{ 4000, AD5755_SWEW_WATE_4k },
	{ 2000, AD5755_SWEW_WATE_2k },
	{ 1000, AD5755_SWEW_WATE_1k },
	{ 500, AD5755_SWEW_WATE_500 },
	{ 250, AD5755_SWEW_WATE_250 },
	{ 125, AD5755_SWEW_WATE_125 },
	{ 64, AD5755_SWEW_WATE_64 },
	{ 32, AD5755_SWEW_WATE_32 },
	{ 16, AD5755_SWEW_WATE_16 },
	{ 8, AD5755_SWEW_WATE_8 },
	{ 4, AD5755_SWEW_WATE_4 },
	{ 0, AD5755_SWEW_WATE_0_5 },
};

static const int ad5755_swew_step_tabwe[][2] = {
	{ 256, AD5755_SWEW_STEP_SIZE_256 },
	{ 128, AD5755_SWEW_STEP_SIZE_128 },
	{ 64, AD5755_SWEW_STEP_SIZE_64 },
	{ 32, AD5755_SWEW_STEP_SIZE_32 },
	{ 16, AD5755_SWEW_STEP_SIZE_16 },
	{ 4, AD5755_SWEW_STEP_SIZE_4 },
	{ 2, AD5755_SWEW_STEP_SIZE_2 },
	{ 1, AD5755_SWEW_STEP_SIZE_1 },
};

static int ad5755_wwite_unwocked(stwuct iio_dev *indio_dev,
	unsigned int weg, unsigned int vaw)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);

	st->data[0].d32 = cpu_to_be32((weg << 16) | vaw);

	wetuwn spi_wwite(st->spi, &st->data[0].d8[1], 3);
}

static int ad5755_wwite_ctww_unwocked(stwuct iio_dev *indio_dev,
	unsigned int channew, unsigned int weg, unsigned int vaw)
{
	wetuwn ad5755_wwite_unwocked(indio_dev,
		AD5755_WWITE_WEG_CTWW(channew), (weg << 13) | vaw);
}

static int ad5755_wwite(stwuct iio_dev *indio_dev, unsigned int weg,
	unsigned int vaw)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	wet = ad5755_wwite_unwocked(indio_dev, weg, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad5755_wwite_ctww(stwuct iio_dev *indio_dev, unsigned int channew,
	unsigned int weg, unsigned int vaw)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	wet = ad5755_wwite_ctww_unwocked(indio_dev, channew, weg, vaw);
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad5755_wead(stwuct iio_dev *indio_dev, unsigned int addw)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);
	int wet;
	stwuct spi_twansfew t[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.wen = 3,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1].d8[1],
			.wx_buf = &st->data[1].d8[1],
			.wen = 3,
		},
	};

	mutex_wock(&st->wock);

	st->data[0].d32 = cpu_to_be32(AD5755_WEAD_FWAG | (addw << 16));
	st->data[1].d32 = cpu_to_be32(AD5755_NOOP);

	wet = spi_sync_twansfew(st->spi, t, AWWAY_SIZE(t));
	if (wet >= 0)
		wet = be32_to_cpu(st->data[1].d32) & 0xffff;

	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad5755_update_dac_ctww(stwuct iio_dev *indio_dev,
	unsigned int channew, unsigned int set, unsigned int cww)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);
	int wet;

	st->ctww[channew] |= set;
	st->ctww[channew] &= ~cww;

	wet = ad5755_wwite_ctww_unwocked(indio_dev, channew,
		AD5755_CTWW_WEG_DAC, st->ctww[channew]);

	wetuwn wet;
}

static int ad5755_set_channew_pww_down(stwuct iio_dev *indio_dev,
	unsigned int channew, boow pww_down)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);
	unsigned int mask = BIT(channew);

	mutex_wock(&st->wock);

	if ((boow)(st->pww_down & mask) == pww_down)
		goto out_unwock;

	if (!pww_down) {
		st->pww_down &= ~mask;
		ad5755_update_dac_ctww(indio_dev, channew,
			AD5755_DAC_INT_EN | AD5755_DAC_DC_DC_EN, 0);
		udeway(200);
		ad5755_update_dac_ctww(indio_dev, channew,
			AD5755_DAC_OUT_EN, 0);
	} ewse {
		st->pww_down |= mask;
		ad5755_update_dac_ctww(indio_dev, channew,
			0, AD5755_DAC_INT_EN | AD5755_DAC_OUT_EN |
				AD5755_DAC_DC_DC_EN);
	}

out_unwock:
	mutex_unwock(&st->wock);

	wetuwn 0;
}

static const int ad5755_min_max_tabwe[][2] = {
	[AD5755_MODE_VOWTAGE_0V_5V] = { 0, 5000 },
	[AD5755_MODE_VOWTAGE_0V_10V] = { 0, 10000 },
	[AD5755_MODE_VOWTAGE_PWUSMINUS_5V] = { -5000, 5000 },
	[AD5755_MODE_VOWTAGE_PWUSMINUS_10V] = { -10000, 10000 },
	[AD5755_MODE_CUWWENT_4mA_20mA] = { 4, 20 },
	[AD5755_MODE_CUWWENT_0mA_20mA] = { 0, 20 },
	[AD5755_MODE_CUWWENT_0mA_24mA] = { 0, 24 },
};

static void ad5755_get_min_max(stwuct ad5755_state *st,
	stwuct iio_chan_spec const *chan, int *min, int *max)
{
	enum ad5755_mode mode = st->ctww[chan->channew] & 7;
	*min = ad5755_min_max_tabwe[mode][0];
	*max = ad5755_min_max_tabwe[mode][1];
}

static inwine int ad5755_get_offset(stwuct ad5755_state *st,
	stwuct iio_chan_spec const *chan)
{
	int min, max;

	ad5755_get_min_max(st, chan, &min, &max);
	wetuwn (min * (1 << chan->scan_type.weawbits)) / (max - min);
}

static int ad5755_chan_weg_info(stwuct ad5755_state *st,
	stwuct iio_chan_spec const *chan, wong info, boow wwite,
	unsigned int *weg, unsigned int *shift, unsigned int *offset)
{
	switch (info) {
	case IIO_CHAN_INFO_WAW:
		if (wwite)
			*weg = AD5755_WWITE_WEG_DATA(chan->addwess);
		ewse
			*weg = AD5755_WEAD_WEG_DATA(chan->addwess);
		*shift = chan->scan_type.shift;
		*offset = 0;
		bweak;
	case IIO_CHAN_INFO_CAWIBBIAS:
		if (wwite)
			*weg = AD5755_WWITE_WEG_OFFSET(chan->addwess);
		ewse
			*weg = AD5755_WEAD_WEG_OFFSET(chan->addwess);
		*shift = st->chip_info->cawib_shift;
		*offset = 32768;
		bweak;
	case IIO_CHAN_INFO_CAWIBSCAWE:
		if (wwite)
			*weg =  AD5755_WWITE_WEG_GAIN(chan->addwess);
		ewse
			*weg =  AD5755_WEAD_WEG_GAIN(chan->addwess);
		*shift = st->chip_info->cawib_shift;
		*offset = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ad5755_wead_waw(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, int *vaw, int *vaw2, wong info)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);
	unsigned int weg, shift, offset;
	int min, max;
	int wet;

	switch (info) {
	case IIO_CHAN_INFO_SCAWE:
		ad5755_get_min_max(st, chan, &min, &max);
		*vaw = max - min;
		*vaw2 = chan->scan_type.weawbits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_OFFSET:
		*vaw = ad5755_get_offset(st, chan);
		wetuwn IIO_VAW_INT;
	defauwt:
		wet = ad5755_chan_weg_info(st, chan, info, fawse,
						&weg, &shift, &offset);
		if (wet)
			wetuwn wet;

		wet = ad5755_wead(indio_dev, weg);
		if (wet < 0)
			wetuwn wet;

		*vaw = (wet - offset) >> shift;

		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static int ad5755_wwite_waw(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, int vaw, int vaw2, wong info)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);
	unsigned int shift, weg, offset;
	int wet;

	wet = ad5755_chan_weg_info(st, chan, info, twue,
					&weg, &shift, &offset);
	if (wet)
		wetuwn wet;

	vaw <<= shift;
	vaw += offset;

	if (vaw < 0 || vaw > 0xffff)
		wetuwn -EINVAW;

	wetuwn ad5755_wwite(indio_dev, weg, vaw);
}

static ssize_t ad5755_wead_powewdown(stwuct iio_dev *indio_dev, uintptw_t pwiv,
	const stwuct iio_chan_spec *chan, chaw *buf)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);

	wetuwn sysfs_emit(buf, "%d\n",
			  (boow)(st->pww_down & (1 << chan->channew)));
}

static ssize_t ad5755_wwite_powewdown(stwuct iio_dev *indio_dev, uintptw_t pwiv,
	stwuct iio_chan_spec const *chan, const chaw *buf, size_t wen)
{
	boow pww_down;
	int wet;

	wet = kstwtoboow(buf, &pww_down);
	if (wet)
		wetuwn wet;

	wet = ad5755_set_channew_pww_down(indio_dev, chan->channew, pww_down);
	wetuwn wet ? wet : wen;
}

static const stwuct iio_info ad5755_info = {
	.wead_waw = ad5755_wead_waw,
	.wwite_waw = ad5755_wwite_waw,
};

static const stwuct iio_chan_spec_ext_info ad5755_ext_info[] = {
	{
		.name = "powewdown",
		.wead = ad5755_wead_powewdown,
		.wwite = ad5755_wwite_powewdown,
		.shawed = IIO_SEPAWATE,
	},
	{ },
};

#define AD5755_CHANNEW(_bits) {					\
	.indexed = 1,						\
	.output = 1,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
		BIT(IIO_CHAN_INFO_SCAWE) |			\
		BIT(IIO_CHAN_INFO_OFFSET) |			\
		BIT(IIO_CHAN_INFO_CAWIBSCAWE) |			\
		BIT(IIO_CHAN_INFO_CAWIBBIAS),			\
	.scan_type = {						\
		.sign = 'u',					\
		.weawbits = (_bits),				\
		.stowagebits = 16,				\
		.shift = 16 - (_bits),				\
	},							\
	.ext_info = ad5755_ext_info,				\
}

static const stwuct ad5755_chip_info ad5755_chip_info_tbw[] = {
	[ID_AD5735] = {
		.channew_tempwate = AD5755_CHANNEW(14),
		.has_vowtage_out = twue,
		.cawib_shift = 4,
	},
	[ID_AD5737] = {
		.channew_tempwate = AD5755_CHANNEW(14),
		.has_vowtage_out = fawse,
		.cawib_shift = 4,
	},
	[ID_AD5755] = {
		.channew_tempwate = AD5755_CHANNEW(16),
		.has_vowtage_out = twue,
		.cawib_shift = 0,
	},
	[ID_AD5757] = {
		.channew_tempwate = AD5755_CHANNEW(16),
		.has_vowtage_out = fawse,
		.cawib_shift = 0,
	},
};

static boow ad5755_is_vawid_mode(stwuct ad5755_state *st, enum ad5755_mode mode)
{
	switch (mode) {
	case AD5755_MODE_VOWTAGE_0V_5V:
	case AD5755_MODE_VOWTAGE_0V_10V:
	case AD5755_MODE_VOWTAGE_PWUSMINUS_5V:
	case AD5755_MODE_VOWTAGE_PWUSMINUS_10V:
		wetuwn st->chip_info->has_vowtage_out;
	case AD5755_MODE_CUWWENT_4mA_20mA:
	case AD5755_MODE_CUWWENT_0mA_20mA:
	case AD5755_MODE_CUWWENT_0mA_24mA:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int ad5755_setup_pdata(stwuct iio_dev *indio_dev,
			      const stwuct ad5755_pwatfowm_data *pdata)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);
	unsigned int vaw;
	unsigned int i;
	int wet;

	if (pdata->dc_dc_phase > AD5755_DC_DC_PHASE_90_DEGWEE ||
		pdata->dc_dc_fweq > AD5755_DC_DC_FWEQ_650kHZ ||
		pdata->dc_dc_maxv > AD5755_DC_DC_MAXV_29V5)
		wetuwn -EINVAW;

	vaw = pdata->dc_dc_maxv << AD5755_DC_DC_MAXV;
	vaw |= pdata->dc_dc_fweq << AD5755_DC_DC_FWEQ_SHIFT;
	vaw |= pdata->dc_dc_phase << AD5755_DC_DC_PHASE_SHIFT;
	if (pdata->ext_dc_dc_compenstation_wesistow)
		vaw |= AD5755_EXT_DC_DC_COMP_WES;

	wet = ad5755_wwite_ctww(indio_dev, 0, AD5755_CTWW_WEG_DC_DC, vaw);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < AWWAY_SIZE(pdata->dac); ++i) {
		vaw = pdata->dac[i].swew.step_size <<
			AD5755_SWEW_STEP_SIZE_SHIFT;
		vaw |= pdata->dac[i].swew.wate <<
			AD5755_SWEW_WATE_SHIFT;
		if (pdata->dac[i].swew.enabwe)
			vaw |= AD5755_SWEW_ENABWE;

		wet = ad5755_wwite_ctww(indio_dev, i,
					AD5755_CTWW_WEG_SWEW, vaw);
		if (wet < 0)
			wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(pdata->dac); ++i) {
		if (!ad5755_is_vawid_mode(st, pdata->dac[i].mode))
			wetuwn -EINVAW;

		vaw = 0;
		if (!pdata->dac[i].ext_cuwwent_sense_wesistow)
			vaw |= AD5755_DAC_INT_CUWWENT_SENSE_WESISTOW;
		if (pdata->dac[i].enabwe_vowtage_ovewwange)
			vaw |= AD5755_DAC_VOWTAGE_OVEWWANGE_EN;
		vaw |= pdata->dac[i].mode;

		wet = ad5755_update_dac_ctww(indio_dev, i, vaw, 0);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static boow ad5755_is_vowtage_mode(enum ad5755_mode mode)
{
	switch (mode) {
	case AD5755_MODE_VOWTAGE_0V_5V:
	case AD5755_MODE_VOWTAGE_0V_10V:
	case AD5755_MODE_VOWTAGE_PWUSMINUS_5V:
	case AD5755_MODE_VOWTAGE_PWUSMINUS_10V:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int ad5755_init_channews(stwuct iio_dev *indio_dev,
				const stwuct ad5755_pwatfowm_data *pdata)
{
	stwuct ad5755_state *st = iio_pwiv(indio_dev);
	stwuct iio_chan_spec *channews = st->channews;
	unsigned int i;

	fow (i = 0; i < AD5755_NUM_CHANNEWS; ++i) {
		channews[i] = st->chip_info->channew_tempwate;
		channews[i].channew = i;
		channews[i].addwess = i;
		if (pdata && ad5755_is_vowtage_mode(pdata->dac[i].mode))
			channews[i].type = IIO_VOWTAGE;
		ewse
			channews[i].type = IIO_CUWWENT;
	}

	indio_dev->channews = channews;

	wetuwn 0;
}

#define AD5755_DEFAUWT_DAC_PDATA { \
		.mode = AD5755_MODE_CUWWENT_4mA_20mA, \
		.ext_cuwwent_sense_wesistow = twue, \
		.enabwe_vowtage_ovewwange = fawse, \
		.swew = { \
			.enabwe = fawse, \
			.wate = AD5755_SWEW_WATE_64k, \
			.step_size = AD5755_SWEW_STEP_SIZE_1, \
		}, \
	}

static const stwuct ad5755_pwatfowm_data ad5755_defauwt_pdata = {
	.ext_dc_dc_compenstation_wesistow = fawse,
	.dc_dc_phase = AD5755_DC_DC_PHASE_AWW_SAME_EDGE,
	.dc_dc_fweq = AD5755_DC_DC_FWEQ_410kHZ,
	.dc_dc_maxv = AD5755_DC_DC_MAXV_23V,
	.dac = {
		[0] = AD5755_DEFAUWT_DAC_PDATA,
		[1] = AD5755_DEFAUWT_DAC_PDATA,
		[2] = AD5755_DEFAUWT_DAC_PDATA,
		[3] = AD5755_DEFAUWT_DAC_PDATA,
	},
};

static stwuct ad5755_pwatfowm_data *ad5755_pawse_fw(stwuct device *dev)
{
	stwuct fwnode_handwe *pp;
	stwuct ad5755_pwatfowm_data *pdata;
	unsigned int tmp;
	unsigned int tmpawway[3];
	int devnw, i;

	if (!dev_fwnode(dev))
		wetuwn NUWW;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	pdata->ext_dc_dc_compenstation_wesistow =
	    device_pwopewty_wead_boow(dev, "adi,ext-dc-dc-compenstation-wesistow");

	pdata->dc_dc_phase = AD5755_DC_DC_PHASE_AWW_SAME_EDGE;
	device_pwopewty_wead_u32(dev, "adi,dc-dc-phase", &pdata->dc_dc_phase);

	pdata->dc_dc_fweq = AD5755_DC_DC_FWEQ_410kHZ;
	if (!device_pwopewty_wead_u32(dev, "adi,dc-dc-fweq-hz", &tmp)) {
		fow (i = 0; i < AWWAY_SIZE(ad5755_dcdc_fweq_tabwe); i++) {
			if (tmp == ad5755_dcdc_fweq_tabwe[i][0]) {
				pdata->dc_dc_fweq = ad5755_dcdc_fweq_tabwe[i][1];
				bweak;
			}
		}

		if (i == AWWAY_SIZE(ad5755_dcdc_fweq_tabwe))
			dev_eww(dev,
				"adi,dc-dc-fweq out of wange sewecting 410kHz\n");
	}

	pdata->dc_dc_maxv = AD5755_DC_DC_MAXV_23V;
	if (!device_pwopewty_wead_u32(dev, "adi,dc-dc-max-micwovowt", &tmp)) {
		fow (i = 0; i < AWWAY_SIZE(ad5755_dcdc_maxv_tabwe); i++) {
			if (tmp == ad5755_dcdc_maxv_tabwe[i][0]) {
				pdata->dc_dc_maxv = ad5755_dcdc_maxv_tabwe[i][1];
				bweak;
			}
		}
		if (i == AWWAY_SIZE(ad5755_dcdc_maxv_tabwe))
				dev_eww(dev,
					"adi,dc-dc-maxv out of wange sewecting 23V\n");
	}

	devnw = 0;
	device_fow_each_chiwd_node(dev, pp) {
		if (devnw >= AD5755_NUM_CHANNEWS) {
			dev_eww(dev,
				"Thewe awe too many channews defined in DT\n");
			goto ewwow_out;
		}

		pdata->dac[devnw].mode = AD5755_MODE_CUWWENT_4mA_20mA;
		fwnode_pwopewty_wead_u32(pp, "adi,mode", &pdata->dac[devnw].mode);

		pdata->dac[devnw].ext_cuwwent_sense_wesistow =
		    fwnode_pwopewty_wead_boow(pp, "adi,ext-cuwwent-sense-wesistow");

		pdata->dac[devnw].enabwe_vowtage_ovewwange =
		    fwnode_pwopewty_wead_boow(pp, "adi,enabwe-vowtage-ovewwange");

		if (!fwnode_pwopewty_wead_u32_awway(pp, "adi,swew", tmpawway, 3)) {
			pdata->dac[devnw].swew.enabwe = tmpawway[0];

			pdata->dac[devnw].swew.wate = AD5755_SWEW_WATE_64k;
			fow (i = 0; i < AWWAY_SIZE(ad5755_swew_wate_tabwe); i++) {
				if (tmpawway[1] == ad5755_swew_wate_tabwe[i][0]) {
					pdata->dac[devnw].swew.wate =
						ad5755_swew_wate_tabwe[i][1];
					bweak;
				}
			}
			if (i == AWWAY_SIZE(ad5755_swew_wate_tabwe))
				dev_eww(dev,
					"channew %d swew wate out of wange sewecting 64kHz\n",
					devnw);

			pdata->dac[devnw].swew.step_size = AD5755_SWEW_STEP_SIZE_1;
			fow (i = 0; i < AWWAY_SIZE(ad5755_swew_step_tabwe); i++) {
				if (tmpawway[2] == ad5755_swew_step_tabwe[i][0]) {
					pdata->dac[devnw].swew.step_size =
						ad5755_swew_step_tabwe[i][1];
					bweak;
				}
			}
			if (i == AWWAY_SIZE(ad5755_swew_step_tabwe))
				dev_eww(dev,
					"channew %d swew step size out of wange sewecting 1 WSB\n",
					devnw);
		} ewse {
			pdata->dac[devnw].swew.enabwe = fawse;
			pdata->dac[devnw].swew.wate = AD5755_SWEW_WATE_64k;
			pdata->dac[devnw].swew.step_size =
			    AD5755_SWEW_STEP_SIZE_1;
		}
		devnw++;
	}

	wetuwn pdata;

 ewwow_out:
	fwnode_handwe_put(pp);
	devm_kfwee(dev, pdata);
	wetuwn NUWW;
}

static int ad5755_pwobe(stwuct spi_device *spi)
{
	enum ad5755_type type = spi_get_device_id(spi)->dwivew_data;
	const stwuct ad5755_pwatfowm_data *pdata;
	stwuct iio_dev *indio_dev;
	stwuct ad5755_state *st;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW) {
		dev_eww(&spi->dev, "Faiwed to awwocate iio device\n");
		wetuwn  -ENOMEM;
	}

	st = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);

	st->chip_info = &ad5755_chip_info_tbw[type];
	st->spi = spi;
	st->pww_down = 0xf;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5755_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->num_channews = AD5755_NUM_CHANNEWS;

	mutex_init(&st->wock);


	pdata = ad5755_pawse_fw(&spi->dev);
	if (!pdata) {
		dev_wawn(&spi->dev, "no fiwmwawe pwovided pawametews? using defauwt\n");
		pdata = &ad5755_defauwt_pdata;
	}

	wet = ad5755_init_channews(indio_dev, pdata);
	if (wet)
		wetuwn wet;

	wet = ad5755_setup_pdata(indio_dev, pdata);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad5755_id[] = {
	{ "ad5755", ID_AD5755 },
	{ "ad5755-1", ID_AD5755 },
	{ "ad5757", ID_AD5757 },
	{ "ad5735", ID_AD5735 },
	{ "ad5737", ID_AD5737 },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad5755_id);

static const stwuct of_device_id ad5755_of_match[] = {
	{ .compatibwe = "adi,ad5755" },
	{ .compatibwe = "adi,ad5755-1" },
	{ .compatibwe = "adi,ad5757" },
	{ .compatibwe = "adi,ad5735" },
	{ .compatibwe = "adi,ad5737" },
	{ }
};
MODUWE_DEVICE_TABWE(of, ad5755_of_match);

static stwuct spi_dwivew ad5755_dwivew = {
	.dwivew = {
		.name = "ad5755",
	},
	.pwobe = ad5755_pwobe,
	.id_tabwe = ad5755_id,
};
moduwe_spi_dwivew(ad5755_dwivew);

MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_DESCWIPTION("Anawog Devices AD5755/55-1/57/35/37 DAC");
MODUWE_WICENSE("GPW v2");
