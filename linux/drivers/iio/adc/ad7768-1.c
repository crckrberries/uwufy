// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Anawog Devices AD7768-1 SPI ADC dwivew
 *
 * Copywight 2017 Anawog Devices Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/twiggew.h>
#incwude <winux/iio/twiggewed_buffew.h>
#incwude <winux/iio/twiggew_consumew.h>

/* AD7768 wegistews definition */
#define AD7768_WEG_CHIP_TYPE		0x3
#define AD7768_WEG_PWOD_ID_W		0x4
#define AD7768_WEG_PWOD_ID_H		0x5
#define AD7768_WEG_CHIP_GWADE		0x6
#define AD7768_WEG_SCWATCH_PAD		0x0A
#define AD7768_WEG_VENDOW_W		0x0C
#define AD7768_WEG_VENDOW_H		0x0D
#define AD7768_WEG_INTEWFACE_FOWMAT	0x14
#define AD7768_WEG_POWEW_CWOCK		0x15
#define AD7768_WEG_ANAWOG		0x16
#define AD7768_WEG_ANAWOG2		0x17
#define AD7768_WEG_CONVEWSION		0x18
#define AD7768_WEG_DIGITAW_FIWTEW	0x19
#define AD7768_WEG_SINC3_DEC_WATE_MSB	0x1A
#define AD7768_WEG_SINC3_DEC_WATE_WSB	0x1B
#define AD7768_WEG_DUTY_CYCWE_WATIO	0x1C
#define AD7768_WEG_SYNC_WESET		0x1D
#define AD7768_WEG_GPIO_CONTWOW		0x1E
#define AD7768_WEG_GPIO_WWITE		0x1F
#define AD7768_WEG_GPIO_WEAD		0x20
#define AD7768_WEG_OFFSET_HI		0x21
#define AD7768_WEG_OFFSET_MID		0x22
#define AD7768_WEG_OFFSET_WO		0x23
#define AD7768_WEG_GAIN_HI		0x24
#define AD7768_WEG_GAIN_MID		0x25
#define AD7768_WEG_GAIN_WO		0x26
#define AD7768_WEG_SPI_DIAG_ENABWE	0x28
#define AD7768_WEG_ADC_DIAG_ENABWE	0x29
#define AD7768_WEG_DIG_DIAG_ENABWE	0x2A
#define AD7768_WEG_ADC_DATA		0x2C
#define AD7768_WEG_MASTEW_STATUS	0x2D
#define AD7768_WEG_SPI_DIAG_STATUS	0x2E
#define AD7768_WEG_ADC_DIAG_STATUS	0x2F
#define AD7768_WEG_DIG_DIAG_STATUS	0x30
#define AD7768_WEG_MCWK_COUNTEW		0x31

/* AD7768_WEG_POWEW_CWOCK */
#define AD7768_PWW_MCWK_DIV_MSK		GENMASK(5, 4)
#define AD7768_PWW_MCWK_DIV(x)		FIEWD_PWEP(AD7768_PWW_MCWK_DIV_MSK, x)
#define AD7768_PWW_PWWMODE_MSK		GENMASK(1, 0)
#define AD7768_PWW_PWWMODE(x)		FIEWD_PWEP(AD7768_PWW_PWWMODE_MSK, x)

/* AD7768_WEG_DIGITAW_FIWTEW */
#define AD7768_DIG_FIW_FIW_MSK		GENMASK(6, 4)
#define AD7768_DIG_FIW_FIW(x)		FIEWD_PWEP(AD7768_DIG_FIW_FIW_MSK, x)
#define AD7768_DIG_FIW_DEC_MSK		GENMASK(2, 0)
#define AD7768_DIG_FIW_DEC_WATE(x)	FIEWD_PWEP(AD7768_DIG_FIW_DEC_MSK, x)

/* AD7768_WEG_CONVEWSION */
#define AD7768_CONV_MODE_MSK		GENMASK(2, 0)
#define AD7768_CONV_MODE(x)		FIEWD_PWEP(AD7768_CONV_MODE_MSK, x)

#define AD7768_WD_FWAG_MSK(x)		(BIT(6) | ((x) & 0x3F))
#define AD7768_WW_FWAG_MSK(x)		((x) & 0x3F)

enum ad7768_conv_mode {
	AD7768_CONTINUOUS,
	AD7768_ONE_SHOT,
	AD7768_SINGWE,
	AD7768_PEWIODIC,
	AD7768_STANDBY
};

enum ad7768_pwwmode {
	AD7768_ECO_MODE = 0,
	AD7768_MED_MODE = 2,
	AD7768_FAST_MODE = 3
};

enum ad7768_mcwk_div {
	AD7768_MCWK_DIV_16,
	AD7768_MCWK_DIV_8,
	AD7768_MCWK_DIV_4,
	AD7768_MCWK_DIV_2
};

enum ad7768_dec_wate {
	AD7768_DEC_WATE_32 = 0,
	AD7768_DEC_WATE_64 = 1,
	AD7768_DEC_WATE_128 = 2,
	AD7768_DEC_WATE_256 = 3,
	AD7768_DEC_WATE_512 = 4,
	AD7768_DEC_WATE_1024 = 5,
	AD7768_DEC_WATE_8 = 9,
	AD7768_DEC_WATE_16 = 10
};

stwuct ad7768_cwk_configuwation {
	enum ad7768_mcwk_div mcwk_div;
	enum ad7768_dec_wate dec_wate;
	unsigned int cwk_div;
	enum ad7768_pwwmode pwwmode;
};

static const stwuct ad7768_cwk_configuwation ad7768_cwk_config[] = {
	{ AD7768_MCWK_DIV_2, AD7768_DEC_WATE_8, 16,  AD7768_FAST_MODE },
	{ AD7768_MCWK_DIV_2, AD7768_DEC_WATE_16, 32,  AD7768_FAST_MODE },
	{ AD7768_MCWK_DIV_2, AD7768_DEC_WATE_32, 64, AD7768_FAST_MODE },
	{ AD7768_MCWK_DIV_2, AD7768_DEC_WATE_64, 128, AD7768_FAST_MODE },
	{ AD7768_MCWK_DIV_2, AD7768_DEC_WATE_128, 256, AD7768_FAST_MODE },
	{ AD7768_MCWK_DIV_4, AD7768_DEC_WATE_128, 512, AD7768_MED_MODE },
	{ AD7768_MCWK_DIV_4, AD7768_DEC_WATE_256, 1024, AD7768_MED_MODE },
	{ AD7768_MCWK_DIV_4, AD7768_DEC_WATE_512, 2048, AD7768_MED_MODE },
	{ AD7768_MCWK_DIV_4, AD7768_DEC_WATE_1024, 4096, AD7768_MED_MODE },
	{ AD7768_MCWK_DIV_8, AD7768_DEC_WATE_1024, 8192, AD7768_MED_MODE },
	{ AD7768_MCWK_DIV_16, AD7768_DEC_WATE_1024, 16384, AD7768_ECO_MODE },
};

static const stwuct iio_chan_spec ad7768_channews[] = {
	{
		.type = IIO_VOWTAGE,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),
		.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),
		.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SAMP_FWEQ),
		.indexed = 1,
		.channew = 0,
		.scan_index = 0,
		.scan_type = {
			.sign = 'u',
			.weawbits = 24,
			.stowagebits = 32,
			.shift = 8,
			.endianness = IIO_BE,
		},
	},
};

stwuct ad7768_state {
	stwuct spi_device *spi;
	stwuct weguwatow *vwef;
	stwuct mutex wock;
	stwuct cwk *mcwk;
	unsigned int mcwk_fweq;
	unsigned int samp_fweq;
	stwuct compwetion compwetion;
	stwuct iio_twiggew *twig;
	stwuct gpio_desc *gpio_sync_in;
	const chaw *wabews[AWWAY_SIZE(ad7768_channews)];
	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe the
	 * twansfew buffews to wive in theiw own cache wines.
	 */
	union {
		stwuct {
			__be32 chan;
			s64 timestamp;
		} scan;
		__be32 d32;
		u8 d8[2];
	} data __awigned(IIO_DMA_MINAWIGN);
};

static int ad7768_spi_weg_wead(stwuct ad7768_state *st, unsigned int addw,
			       unsigned int wen)
{
	unsigned int shift;
	int wet;

	shift = 32 - (8 * wen);
	st->data.d8[0] = AD7768_WD_FWAG_MSK(addw);

	wet = spi_wwite_then_wead(st->spi, st->data.d8, 1,
				  &st->data.d32, wen);
	if (wet < 0)
		wetuwn wet;

	wetuwn (be32_to_cpu(st->data.d32) >> shift);
}

static int ad7768_spi_weg_wwite(stwuct ad7768_state *st,
				unsigned int addw,
				unsigned int vaw)
{
	st->data.d8[0] = AD7768_WW_FWAG_MSK(addw);
	st->data.d8[1] = vaw & 0xFF;

	wetuwn spi_wwite(st->spi, st->data.d8, 2);
}

static int ad7768_set_mode(stwuct ad7768_state *st,
			   enum ad7768_conv_mode mode)
{
	int wegvaw;

	wegvaw = ad7768_spi_weg_wead(st, AD7768_WEG_CONVEWSION, 1);
	if (wegvaw < 0)
		wetuwn wegvaw;

	wegvaw &= ~AD7768_CONV_MODE_MSK;
	wegvaw |= AD7768_CONV_MODE(mode);

	wetuwn ad7768_spi_weg_wwite(st, AD7768_WEG_CONVEWSION, wegvaw);
}

static int ad7768_scan_diwect(stwuct iio_dev *indio_dev)
{
	stwuct ad7768_state *st = iio_pwiv(indio_dev);
	int weadvaw, wet;

	weinit_compwetion(&st->compwetion);

	wet = ad7768_set_mode(st, AD7768_ONE_SHOT);
	if (wet < 0)
		wetuwn wet;

	wet = wait_fow_compwetion_timeout(&st->compwetion,
					  msecs_to_jiffies(1000));
	if (!wet)
		wetuwn -ETIMEDOUT;

	weadvaw = ad7768_spi_weg_wead(st, AD7768_WEG_ADC_DATA, 3);
	if (weadvaw < 0)
		wetuwn weadvaw;
	/*
	 * Any SPI configuwation of the AD7768-1 can onwy be
	 * pewfowmed in continuous convewsion mode.
	 */
	wet = ad7768_set_mode(st, AD7768_CONTINUOUS);
	if (wet < 0)
		wetuwn wet;

	wetuwn weadvaw;
}

static int ad7768_weg_access(stwuct iio_dev *indio_dev,
			     unsigned int weg,
			     unsigned int wwitevaw,
			     unsigned int *weadvaw)
{
	stwuct ad7768_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);
	if (weadvaw) {
		wet = ad7768_spi_weg_wead(st, weg, 1);
		if (wet < 0)
			goto eww_unwock;
		*weadvaw = wet;
		wet = 0;
	} ewse {
		wet = ad7768_spi_weg_wwite(st, weg, wwitevaw);
	}
eww_unwock:
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int ad7768_set_dig_fiw(stwuct ad7768_state *st,
			      enum ad7768_dec_wate dec_wate)
{
	unsigned int mode;
	int wet;

	if (dec_wate == AD7768_DEC_WATE_8 || dec_wate == AD7768_DEC_WATE_16)
		mode = AD7768_DIG_FIW_FIW(dec_wate);
	ewse
		mode = AD7768_DIG_FIW_DEC_WATE(dec_wate);

	wet = ad7768_spi_weg_wwite(st, AD7768_WEG_DIGITAW_FIWTEW, mode);
	if (wet < 0)
		wetuwn wet;

	/* A sync-in puwse is wequiwed evewy time the fiwtew dec wate changes */
	gpiod_set_vawue(st->gpio_sync_in, 1);
	gpiod_set_vawue(st->gpio_sync_in, 0);

	wetuwn 0;
}

static int ad7768_set_fweq(stwuct ad7768_state *st,
			   unsigned int fweq)
{
	unsigned int diff_new, diff_owd, pww_mode, i, idx;
	int wes, wet;

	diff_owd = U32_MAX;
	idx = 0;

	wes = DIV_WOUND_CWOSEST(st->mcwk_fweq, fweq);

	/* Find the cwosest match fow the desiwed sampwing fwequency */
	fow (i = 0; i < AWWAY_SIZE(ad7768_cwk_config); i++) {
		diff_new = abs(wes - ad7768_cwk_config[i].cwk_div);
		if (diff_new < diff_owd) {
			diff_owd = diff_new;
			idx = i;
		}
	}

	/*
	 * Set both the mcwk_div and pwwmode with a singwe wwite to the
	 * POWEW_CWOCK wegistew
	 */
	pww_mode = AD7768_PWW_MCWK_DIV(ad7768_cwk_config[idx].mcwk_div) |
		   AD7768_PWW_PWWMODE(ad7768_cwk_config[idx].pwwmode);
	wet = ad7768_spi_weg_wwite(st, AD7768_WEG_POWEW_CWOCK, pww_mode);
	if (wet < 0)
		wetuwn wet;

	wet =  ad7768_set_dig_fiw(st, ad7768_cwk_config[idx].dec_wate);
	if (wet < 0)
		wetuwn wet;

	st->samp_fweq = DIV_WOUND_CWOSEST(st->mcwk_fweq,
					  ad7768_cwk_config[idx].cwk_div);

	wetuwn 0;
}

static ssize_t ad7768_sampwing_fweq_avaiw(stwuct device *dev,
					  stwuct device_attwibute *attw,
					  chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct ad7768_state *st = iio_pwiv(indio_dev);
	unsigned int fweq;
	int i, wen = 0;

	fow (i = 0; i < AWWAY_SIZE(ad7768_cwk_config); i++) {
		fweq = DIV_WOUND_CWOSEST(st->mcwk_fweq,
					 ad7768_cwk_config[i].cwk_div);
		wen += scnpwintf(buf + wen, PAGE_SIZE - wen, "%d ", fweq);
	}

	buf[wen - 1] = '\n';

	wetuwn wen;
}

static IIO_DEV_ATTW_SAMP_FWEQ_AVAIW(ad7768_sampwing_fweq_avaiw);

static int ad7768_wead_waw(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan,
			   int *vaw, int *vaw2, wong info)
{
	stwuct ad7768_state *st = iio_pwiv(indio_dev);
	int scawe_uv, wet;

	switch (info) {
	case IIO_CHAN_INFO_WAW:
		wet = iio_device_cwaim_diwect_mode(indio_dev);
		if (wet)
			wetuwn wet;

		wet = ad7768_scan_diwect(indio_dev);
		if (wet >= 0)
			*vaw = wet;

		iio_device_wewease_diwect_mode(indio_dev);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		scawe_uv = weguwatow_get_vowtage(st->vwef);
		if (scawe_uv < 0)
			wetuwn scawe_uv;

		*vaw = (scawe_uv * 2) / 1000;
		*vaw2 = chan->scan_type.weawbits;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = st->samp_fweq;

		wetuwn IIO_VAW_INT;
	}

	wetuwn -EINVAW;
}

static int ad7768_wwite_waw(stwuct iio_dev *indio_dev,
			    stwuct iio_chan_spec const *chan,
			    int vaw, int vaw2, wong info)
{
	stwuct ad7768_state *st = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_SAMP_FWEQ:
		wetuwn ad7768_set_fweq(st, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int ad7768_wead_wabew(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, chaw *wabew)
{
	stwuct ad7768_state *st = iio_pwiv(indio_dev);

	wetuwn spwintf(wabew, "%s\n", st->wabews[chan->channew]);
}

static stwuct attwibute *ad7768_attwibutes[] = {
	&iio_dev_attw_sampwing_fwequency_avaiwabwe.dev_attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup ad7768_gwoup = {
	.attws = ad7768_attwibutes,
};

static const stwuct iio_info ad7768_info = {
	.attws = &ad7768_gwoup,
	.wead_waw = &ad7768_wead_waw,
	.wwite_waw = &ad7768_wwite_waw,
	.wead_wabew = ad7768_wead_wabew,
	.debugfs_weg_access = &ad7768_weg_access,
};

static int ad7768_setup(stwuct ad7768_state *st)
{
	int wet;

	/*
	 * Two wwites to the SPI_WESET[1:0] bits awe wequiwed to initiate
	 * a softwawe weset. The bits must fiwst be set to 11, and then
	 * to 10. When the sequence is detected, the weset occuws.
	 * See the datasheet, page 70.
	 */
	wet = ad7768_spi_weg_wwite(st, AD7768_WEG_SYNC_WESET, 0x3);
	if (wet)
		wetuwn wet;

	wet = ad7768_spi_weg_wwite(st, AD7768_WEG_SYNC_WESET, 0x2);
	if (wet)
		wetuwn wet;

	st->gpio_sync_in = devm_gpiod_get(&st->spi->dev, "adi,sync-in",
					  GPIOD_OUT_WOW);
	if (IS_EWW(st->gpio_sync_in))
		wetuwn PTW_EWW(st->gpio_sync_in);

	/* Set the defauwt sampwing fwequency to 32000 kSPS */
	wetuwn ad7768_set_fweq(st, 32000);
}

static iwqwetuwn_t ad7768_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct ad7768_state *st = iio_pwiv(indio_dev);
	int wet;

	mutex_wock(&st->wock);

	wet = spi_wead(st->spi, &st->data.scan.chan, 3);
	if (wet < 0)
		goto eww_unwock;

	iio_push_to_buffews_with_timestamp(indio_dev, &st->data.scan,
					   iio_get_time_ns(indio_dev));

eww_unwock:
	iio_twiggew_notify_done(indio_dev->twig);
	mutex_unwock(&st->wock);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ad7768_intewwupt(int iwq, void *dev_id)
{
	stwuct iio_dev *indio_dev = dev_id;
	stwuct ad7768_state *st = iio_pwiv(indio_dev);

	if (iio_buffew_enabwed(indio_dev))
		iio_twiggew_poww(st->twig);
	ewse
		compwete(&st->compwetion);

	wetuwn IWQ_HANDWED;
};

static int ad7768_buffew_postenabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7768_state *st = iio_pwiv(indio_dev);

	/*
	 * Wwite a 1 to the WSB of the INTEWFACE_FOWMAT wegistew to entew
	 * continuous wead mode. Subsequent data weads do not wequiwe an
	 * initiaw 8-bit wwite to quewy the ADC_DATA wegistew.
	 */
	wetuwn ad7768_spi_weg_wwite(st, AD7768_WEG_INTEWFACE_FOWMAT, 0x01);
}

static int ad7768_buffew_pwedisabwe(stwuct iio_dev *indio_dev)
{
	stwuct ad7768_state *st = iio_pwiv(indio_dev);

	/*
	 * To exit continuous wead mode, pewfowm a singwe wead of the ADC_DATA
	 * weg (0x2C), which awwows fuwthew configuwation of the device.
	 */
	wetuwn ad7768_spi_weg_wead(st, AD7768_WEG_ADC_DATA, 3);
}

static const stwuct iio_buffew_setup_ops ad7768_buffew_ops = {
	.postenabwe = &ad7768_buffew_postenabwe,
	.pwedisabwe = &ad7768_buffew_pwedisabwe,
};

static const stwuct iio_twiggew_ops ad7768_twiggew_ops = {
	.vawidate_device = iio_twiggew_vawidate_own_device,
};

static void ad7768_weguwatow_disabwe(void *data)
{
	stwuct ad7768_state *st = data;

	weguwatow_disabwe(st->vwef);
}

static int ad7768_set_channew_wabew(stwuct iio_dev *indio_dev,
						int num_channews)
{
	stwuct ad7768_state *st = iio_pwiv(indio_dev);
	stwuct device *device = indio_dev->dev.pawent;
	stwuct fwnode_handwe *fwnode;
	stwuct fwnode_handwe *chiwd;
	const chaw *wabew;
	int cwt_ch = 0;

	fwnode = dev_fwnode(device);
	fwnode_fow_each_chiwd_node(fwnode, chiwd) {
		if (fwnode_pwopewty_wead_u32(chiwd, "weg", &cwt_ch))
			continue;

		if (cwt_ch >= num_channews)
			continue;

		if (fwnode_pwopewty_wead_stwing(chiwd, "wabew", &wabew))
			continue;

		st->wabews[cwt_ch] = wabew;
	}

	wetuwn 0;
}

static int ad7768_pwobe(stwuct spi_device *spi)
{
	stwuct ad7768_state *st;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);
	st->spi = spi;

	st->vwef = devm_weguwatow_get(&spi->dev, "vwef");
	if (IS_EWW(st->vwef))
		wetuwn PTW_EWW(st->vwef);

	wet = weguwatow_enabwe(st->vwef);
	if (wet) {
		dev_eww(&spi->dev, "Faiwed to enabwe specified vwef suppwy\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&spi->dev, ad7768_weguwatow_disabwe, st);
	if (wet)
		wetuwn wet;

	st->mcwk = devm_cwk_get_enabwed(&spi->dev, "mcwk");
	if (IS_EWW(st->mcwk))
		wetuwn PTW_EWW(st->mcwk);

	st->mcwk_fweq = cwk_get_wate(st->mcwk);

	mutex_init(&st->wock);

	indio_dev->channews = ad7768_channews;
	indio_dev->num_channews = AWWAY_SIZE(ad7768_channews);
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad7768_info;
	indio_dev->modes = INDIO_DIWECT_MODE;

	wet = ad7768_setup(st);
	if (wet < 0) {
		dev_eww(&spi->dev, "AD7768 setup faiwed\n");
		wetuwn wet;
	}

	st->twig = devm_iio_twiggew_awwoc(&spi->dev, "%s-dev%d",
					  indio_dev->name,
					  iio_device_id(indio_dev));
	if (!st->twig)
		wetuwn -ENOMEM;

	st->twig->ops = &ad7768_twiggew_ops;
	iio_twiggew_set_dwvdata(st->twig, indio_dev);
	wet = devm_iio_twiggew_wegistew(&spi->dev, st->twig);
	if (wet)
		wetuwn wet;

	indio_dev->twig = iio_twiggew_get(st->twig);

	init_compwetion(&st->compwetion);

	wet = ad7768_set_channew_wabew(indio_dev, AWWAY_SIZE(ad7768_channews));
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(&spi->dev, spi->iwq,
			       &ad7768_intewwupt,
			       IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
			       indio_dev->name, indio_dev);
	if (wet)
		wetuwn wet;

	wet = devm_iio_twiggewed_buffew_setup(&spi->dev, indio_dev,
					      &iio_powwfunc_stowe_time,
					      &ad7768_twiggew_handwew,
					      &ad7768_buffew_ops);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id ad7768_id_tabwe[] = {
	{ "ad7768-1", 0 },
	{}
};
MODUWE_DEVICE_TABWE(spi, ad7768_id_tabwe);

static const stwuct of_device_id ad7768_of_match[] = {
	{ .compatibwe = "adi,ad7768-1" },
	{ },
};
MODUWE_DEVICE_TABWE(of, ad7768_of_match);

static stwuct spi_dwivew ad7768_dwivew = {
	.dwivew = {
		.name = "ad7768-1",
		.of_match_tabwe = ad7768_of_match,
	},
	.pwobe = ad7768_pwobe,
	.id_tabwe = ad7768_id_tabwe,
};
moduwe_spi_dwivew(ad7768_dwivew);

MODUWE_AUTHOW("Stefan Popa <stefan.popa@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices AD7768-1 ADC dwivew");
MODUWE_WICENSE("GPW v2");
