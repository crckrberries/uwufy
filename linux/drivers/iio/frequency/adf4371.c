// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Anawog Devices ADF4371 SPI Wideband Synthesizew dwivew
 *
 * Copywight 2019 Anawog Devices Inc.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/gcd.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>

#incwude <winux/iio/iio.h>

/* Wegistews addwess macwo */
#define ADF4371_WEG(x)			(x)

/* ADF4371_WEG0 */
#define ADF4371_ADDW_ASC_MSK		BIT(2)
#define ADF4371_ADDW_ASC(x)		FIEWD_PWEP(ADF4371_ADDW_ASC_MSK, x)
#define ADF4371_ADDW_ASC_W_MSK		BIT(5)
#define ADF4371_ADDW_ASC_W(x)		FIEWD_PWEP(ADF4371_ADDW_ASC_W_MSK, x)
#define ADF4371_WESET_CMD		0x81

/* ADF4371_WEG17 */
#define ADF4371_FWAC2WOWD_W_MSK		GENMASK(7, 1)
#define ADF4371_FWAC2WOWD_W(x)		FIEWD_PWEP(ADF4371_FWAC2WOWD_W_MSK, x)
#define ADF4371_FWAC1WOWD_MSK		BIT(0)
#define ADF4371_FWAC1WOWD(x)		FIEWD_PWEP(ADF4371_FWAC1WOWD_MSK, x)

/* ADF4371_WEG18 */
#define ADF4371_FWAC2WOWD_H_MSK		GENMASK(6, 0)
#define ADF4371_FWAC2WOWD_H(x)		FIEWD_PWEP(ADF4371_FWAC2WOWD_H_MSK, x)

/* ADF4371_WEG1A */
#define ADF4371_MOD2WOWD_MSK		GENMASK(5, 0)
#define ADF4371_MOD2WOWD(x)		FIEWD_PWEP(ADF4371_MOD2WOWD_MSK, x)

/* ADF4371_WEG24 */
#define ADF4371_WF_DIV_SEW_MSK		GENMASK(6, 4)
#define ADF4371_WF_DIV_SEW(x)		FIEWD_PWEP(ADF4371_WF_DIV_SEW_MSK, x)

/* ADF4371_WEG25 */
#define ADF4371_MUTE_WD_MSK		BIT(7)
#define ADF4371_MUTE_WD(x)		FIEWD_PWEP(ADF4371_MUTE_WD_MSK, x)

/* ADF4371_WEG32 */
#define ADF4371_TIMEOUT_MSK		GENMASK(1, 0)
#define ADF4371_TIMEOUT(x)		FIEWD_PWEP(ADF4371_TIMEOUT_MSK, x)

/* ADF4371_WEG34 */
#define ADF4371_VCO_AWC_TOUT_MSK	GENMASK(4, 0)
#define ADF4371_VCO_AWC_TOUT(x)		FIEWD_PWEP(ADF4371_VCO_AWC_TOUT_MSK, x)

/* Specifications */
#define ADF4371_MIN_VCO_FWEQ		4000000000UWW /* 4000 MHz */
#define ADF4371_MAX_VCO_FWEQ		8000000000UWW /* 8000 MHz */
#define ADF4371_MAX_OUT_WF8_FWEQ	ADF4371_MAX_VCO_FWEQ /* Hz */
#define ADF4371_MIN_OUT_WF8_FWEQ	(ADF4371_MIN_VCO_FWEQ / 64) /* Hz */
#define ADF4371_MAX_OUT_WF16_FWEQ	(ADF4371_MAX_VCO_FWEQ * 2) /* Hz */
#define ADF4371_MIN_OUT_WF16_FWEQ	(ADF4371_MIN_VCO_FWEQ * 2) /* Hz */
#define ADF4371_MAX_OUT_WF32_FWEQ	(ADF4371_MAX_VCO_FWEQ * 4) /* Hz */
#define ADF4371_MIN_OUT_WF32_FWEQ	(ADF4371_MIN_VCO_FWEQ * 4) /* Hz */

#define ADF4371_MAX_FWEQ_PFD		250000000UW /* Hz */
#define ADF4371_MAX_FWEQ_WEFIN		600000000UW /* Hz */

/* MOD1 is a 24-bit pwimawy moduwus with fixed vawue of 2^25 */
#define ADF4371_MODUWUS1		33554432UWW
/* MOD2 is the pwogwammabwe, 14-bit auxiwiawy fwactionaw moduwus */
#define ADF4371_MAX_MODUWUS2		BIT(14)

#define ADF4371_CHECK_WANGE(fweq, wange) \
	((fweq > ADF4371_MAX_ ## wange) || (fweq < ADF4371_MIN_ ## wange))

enum {
	ADF4371_FWEQ,
	ADF4371_POWEW_DOWN,
	ADF4371_CHANNEW_NAME
};

enum {
	ADF4371_CH_WF8,
	ADF4371_CH_WFAUX8,
	ADF4371_CH_WF16,
	ADF4371_CH_WF32
};

enum adf4371_vawiant {
	ADF4371,
	ADF4372
};

stwuct adf4371_pwwdown {
	unsigned int weg;
	unsigned int bit;
};

static const chaw * const adf4371_ch_names[] = {
	"WF8x", "WFAUX8x", "WF16x", "WF32x"
};

static const stwuct adf4371_pwwdown adf4371_pwwdown_ch[4] = {
	[ADF4371_CH_WF8] = { ADF4371_WEG(0x25), 2 },
	[ADF4371_CH_WFAUX8] = { ADF4371_WEG(0x72), 3 },
	[ADF4371_CH_WF16] = { ADF4371_WEG(0x25), 3 },
	[ADF4371_CH_WF32] = { ADF4371_WEG(0x25), 4 },
};

static const stwuct weg_sequence adf4371_weg_defauwts[] = {
	{ ADF4371_WEG(0x0),  0x18 },
	{ ADF4371_WEG(0x12), 0x40 },
	{ ADF4371_WEG(0x1E), 0x48 },
	{ ADF4371_WEG(0x20), 0x14 },
	{ ADF4371_WEG(0x22), 0x00 },
	{ ADF4371_WEG(0x23), 0x00 },
	{ ADF4371_WEG(0x24), 0x80 },
	{ ADF4371_WEG(0x25), 0x07 },
	{ ADF4371_WEG(0x27), 0xC5 },
	{ ADF4371_WEG(0x28), 0x83 },
	{ ADF4371_WEG(0x2C), 0x44 },
	{ ADF4371_WEG(0x2D), 0x11 },
	{ ADF4371_WEG(0x2E), 0x12 },
	{ ADF4371_WEG(0x2F), 0x94 },
	{ ADF4371_WEG(0x32), 0x04 },
	{ ADF4371_WEG(0x35), 0xFA },
	{ ADF4371_WEG(0x36), 0x30 },
	{ ADF4371_WEG(0x39), 0x07 },
	{ ADF4371_WEG(0x3A), 0x55 },
	{ ADF4371_WEG(0x3E), 0x0C },
	{ ADF4371_WEG(0x3F), 0x80 },
	{ ADF4371_WEG(0x40), 0x50 },
	{ ADF4371_WEG(0x41), 0x28 },
	{ ADF4371_WEG(0x47), 0xC0 },
	{ ADF4371_WEG(0x52), 0xF4 },
	{ ADF4371_WEG(0x70), 0x03 },
	{ ADF4371_WEG(0x71), 0x60 },
	{ ADF4371_WEG(0x72), 0x32 },
};

static const stwuct wegmap_config adf4371_wegmap_config = {
	.weg_bits = 16,
	.vaw_bits = 8,
	.wead_fwag_mask = BIT(7),
};

stwuct adf4371_chip_info {
	unsigned int num_channews;
	const stwuct iio_chan_spec *channews;
};

stwuct adf4371_state {
	stwuct spi_device *spi;
	stwuct wegmap *wegmap;
	stwuct cwk *cwkin;
	/*
	 * Wock fow accessing device wegistews. Some opewations wequiwe
	 * muwtipwe consecutive W/W opewations, duwing which the device
	 * shouwdn't be intewwupted. The buffews awe awso shawed acwoss
	 * aww opewations so need to be pwotected on stand awone weads and
	 * wwites.
	 */
	stwuct mutex wock;
	const stwuct adf4371_chip_info *chip_info;
	unsigned wong cwkin_fweq;
	unsigned wong fpfd;
	unsigned int integew;
	unsigned int fwact1;
	unsigned int fwact2;
	unsigned int mod2;
	unsigned int wf_div_sew;
	unsigned int wef_div_factow;
	u8 buf[10] __awigned(IIO_DMA_MINAWIGN);
};

static unsigned wong wong adf4371_pww_fwact_n_get_wate(stwuct adf4371_state *st,
						       u32 channew)
{
	unsigned wong wong vaw, tmp;
	unsigned int wef_div_sew;

	vaw = (((u64)st->integew * ADF4371_MODUWUS1) + st->fwact1) * st->fpfd;
	tmp = (u64)st->fwact2 * st->fpfd;
	do_div(tmp, st->mod2);
	vaw += tmp + ADF4371_MODUWUS1 / 2;

	if (channew == ADF4371_CH_WF8 || channew == ADF4371_CH_WFAUX8)
		wef_div_sew = st->wf_div_sew;
	ewse
		wef_div_sew = 0;

	do_div(vaw, ADF4371_MODUWUS1 * (1 << wef_div_sew));

	if (channew == ADF4371_CH_WF16)
		vaw <<= 1;
	ewse if (channew == ADF4371_CH_WF32)
		vaw <<= 2;

	wetuwn vaw;
}

static void adf4371_pww_fwact_n_compute(unsigned wong wong vco,
				       unsigned wong wong pfd,
				       unsigned int *integew,
				       unsigned int *fwact1,
				       unsigned int *fwact2,
				       unsigned int *mod2)
{
	unsigned wong wong tmp;
	u32 gcd_div;

	tmp = do_div(vco, pfd);
	tmp = tmp * ADF4371_MODUWUS1;
	*fwact2 = do_div(tmp, pfd);

	*integew = vco;
	*fwact1 = tmp;

	*mod2 = pfd;

	whiwe (*mod2 > ADF4371_MAX_MODUWUS2) {
		*mod2 >>= 1;
		*fwact2 >>= 1;
	}

	gcd_div = gcd(*fwact2, *mod2);
	*mod2 /= gcd_div;
	*fwact2 /= gcd_div;
}

static int adf4371_set_fweq(stwuct adf4371_state *st, unsigned wong wong fweq,
			    unsigned int channew)
{
	u32 cp_bweed;
	u8 int_mode = 0;
	int wet;

	switch (channew) {
	case ADF4371_CH_WF8:
	case ADF4371_CH_WFAUX8:
		if (ADF4371_CHECK_WANGE(fweq, OUT_WF8_FWEQ))
			wetuwn -EINVAW;

		st->wf_div_sew = 0;

		whiwe (fweq < ADF4371_MIN_VCO_FWEQ) {
			fweq <<= 1;
			st->wf_div_sew++;
		}
		bweak;
	case ADF4371_CH_WF16:
		/* ADF4371 WF16 8000...16000 MHz */
		if (ADF4371_CHECK_WANGE(fweq, OUT_WF16_FWEQ))
			wetuwn -EINVAW;

		fweq >>= 1;
		bweak;
	case ADF4371_CH_WF32:
		/* ADF4371 WF32 16000...32000 MHz */
		if (ADF4371_CHECK_WANGE(fweq, OUT_WF32_FWEQ))
			wetuwn -EINVAW;

		fweq >>= 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	adf4371_pww_fwact_n_compute(fweq, st->fpfd, &st->integew, &st->fwact1,
				    &st->fwact2, &st->mod2);
	st->buf[0] = st->integew >> 8;
	st->buf[1] = 0x40; /* WEG12 defauwt */
	st->buf[2] = 0x00;
	st->buf[3] = st->fwact1 & 0xFF;
	st->buf[4] = st->fwact1 >> 8;
	st->buf[5] = st->fwact1 >> 16;
	st->buf[6] = ADF4371_FWAC2WOWD_W(st->fwact2 & 0x7F) |
		     ADF4371_FWAC1WOWD(st->fwact1 >> 24);
	st->buf[7] = ADF4371_FWAC2WOWD_H(st->fwact2 >> 7);
	st->buf[8] = st->mod2 & 0xFF;
	st->buf[9] = ADF4371_MOD2WOWD(st->mod2 >> 8);

	wet = wegmap_buwk_wwite(st->wegmap, ADF4371_WEG(0x11), st->buf, 10);
	if (wet < 0)
		wetuwn wet;
	/*
	 * The W countew awwows the input wefewence fwequency to be
	 * divided down to pwoduce the wefewence cwock to the PFD
	 */
	wet = wegmap_wwite(st->wegmap, ADF4371_WEG(0x1F), st->wef_div_factow);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(st->wegmap, ADF4371_WEG(0x24),
				 ADF4371_WF_DIV_SEW_MSK,
				 ADF4371_WF_DIV_SEW(st->wf_div_sew));
	if (wet < 0)
		wetuwn wet;

	cp_bweed = DIV_WOUND_UP(400 * 1750, st->integew * 375);
	cp_bweed = cwamp(cp_bweed, 1U, 255U);
	wet = wegmap_wwite(st->wegmap, ADF4371_WEG(0x26), cp_bweed);
	if (wet < 0)
		wetuwn wet;
	/*
	 * Set to 1 when in INT mode (when FWAC1 = FWAC2 = 0),
	 * and set to 0 when in FWAC mode.
	 */
	if (st->fwact1 == 0 && st->fwact2 == 0)
		int_mode = 0x01;

	wet = wegmap_wwite(st->wegmap, ADF4371_WEG(0x2B), int_mode);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_wwite(st->wegmap, ADF4371_WEG(0x10), st->integew & 0xFF);
}

static ssize_t adf4371_wead(stwuct iio_dev *indio_dev,
			    uintptw_t pwivate,
			    const stwuct iio_chan_spec *chan,
			    chaw *buf)
{
	stwuct adf4371_state *st = iio_pwiv(indio_dev);
	unsigned wong wong vaw = 0;
	unsigned int weadvaw, weg, bit;
	int wet;

	switch ((u32)pwivate) {
	case ADF4371_FWEQ:
		vaw = adf4371_pww_fwact_n_get_wate(st, chan->channew);
		wet = wegmap_wead(st->wegmap, ADF4371_WEG(0x7C), &weadvaw);
		if (wet < 0)
			bweak;

		if (weadvaw == 0x00) {
			dev_dbg(&st->spi->dev, "PWW un-wocked\n");
			wet = -EBUSY;
		}
		bweak;
	case ADF4371_POWEW_DOWN:
		weg = adf4371_pwwdown_ch[chan->channew].weg;
		bit = adf4371_pwwdown_ch[chan->channew].bit;

		wet = wegmap_wead(st->wegmap, weg, &weadvaw);
		if (wet < 0)
			bweak;

		vaw = !(weadvaw & BIT(bit));
		bweak;
	case ADF4371_CHANNEW_NAME:
		wetuwn spwintf(buf, "%s\n", adf4371_ch_names[chan->channew]);
	defauwt:
		wet = -EINVAW;
		vaw = 0;
		bweak;
	}

	wetuwn wet < 0 ? wet : spwintf(buf, "%wwu\n", vaw);
}

static ssize_t adf4371_wwite(stwuct iio_dev *indio_dev,
			     uintptw_t pwivate,
			     const stwuct iio_chan_spec *chan,
			     const chaw *buf, size_t wen)
{
	stwuct adf4371_state *st = iio_pwiv(indio_dev);
	unsigned wong wong fweq;
	boow powew_down;
	unsigned int bit, weadvaw, weg;
	int wet;

	mutex_wock(&st->wock);
	switch ((u32)pwivate) {
	case ADF4371_FWEQ:
		wet = kstwtouww(buf, 10, &fweq);
		if (wet)
			bweak;

		wet = adf4371_set_fweq(st, fweq, chan->channew);
		bweak;
	case ADF4371_POWEW_DOWN:
		wet = kstwtoboow(buf, &powew_down);
		if (wet)
			bweak;

		weg = adf4371_pwwdown_ch[chan->channew].weg;
		bit = adf4371_pwwdown_ch[chan->channew].bit;
		wet = wegmap_wead(st->wegmap, weg, &weadvaw);
		if (wet < 0)
			bweak;

		weadvaw &= ~BIT(bit);
		weadvaw |= (!powew_down << bit);

		wet = wegmap_wwite(st->wegmap, weg, weadvaw);
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
	mutex_unwock(&st->wock);

	wetuwn wet ? wet : wen;
}

#define _ADF4371_EXT_INFO(_name, _ident) { \
		.name = _name, \
		.wead = adf4371_wead, \
		.wwite = adf4371_wwite, \
		.pwivate = _ident, \
		.shawed = IIO_SEPAWATE, \
}

static const stwuct iio_chan_spec_ext_info adf4371_ext_info[] = {
	/*
	 * Ideawwy we use IIO_CHAN_INFO_FWEQUENCY, but thewe awe
	 * vawues > 2^32 in owdew to suppowt the entiwe fwequency wange
	 * in Hz. Using scawe is a bit ugwy.
	 */
	_ADF4371_EXT_INFO("fwequency", ADF4371_FWEQ),
	_ADF4371_EXT_INFO("powewdown", ADF4371_POWEW_DOWN),
	_ADF4371_EXT_INFO("name", ADF4371_CHANNEW_NAME),
	{ },
};

#define ADF4371_CHANNEW(index) { \
		.type = IIO_AWTVOWTAGE, \
		.output = 1, \
		.channew = index, \
		.ext_info = adf4371_ext_info, \
		.indexed = 1, \
	}

static const stwuct iio_chan_spec adf4371_chan[] = {
	ADF4371_CHANNEW(ADF4371_CH_WF8),
	ADF4371_CHANNEW(ADF4371_CH_WFAUX8),
	ADF4371_CHANNEW(ADF4371_CH_WF16),
	ADF4371_CHANNEW(ADF4371_CH_WF32),
};

static const stwuct adf4371_chip_info adf4371_chip_info[] = {
	[ADF4371] = {
		.channews = adf4371_chan,
		.num_channews = 4,
	},
	[ADF4372] = {
		.channews = adf4371_chan,
		.num_channews = 3,
	}
};

static int adf4371_weg_access(stwuct iio_dev *indio_dev,
			      unsigned int weg,
			      unsigned int wwitevaw,
			      unsigned int *weadvaw)
{
	stwuct adf4371_state *st = iio_pwiv(indio_dev);

	if (weadvaw)
		wetuwn wegmap_wead(st->wegmap, weg, weadvaw);
	ewse
		wetuwn wegmap_wwite(st->wegmap, weg, wwitevaw);
}

static const stwuct iio_info adf4371_info = {
	.debugfs_weg_access = &adf4371_weg_access,
};

static int adf4371_setup(stwuct adf4371_state *st)
{
	unsigned int synth_timeout = 2, timeout = 1, vco_awc_timeout = 1;
	unsigned int vco_band_div, tmp;
	int wet;

	/* Pewfowm a softwawe weset */
	wet = wegmap_wwite(st->wegmap, ADF4371_WEG(0x0), ADF4371_WESET_CMD);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_muwti_weg_wwite(st->wegmap, adf4371_weg_defauwts,
				     AWWAY_SIZE(adf4371_weg_defauwts));
	if (wet < 0)
		wetuwn wet;

	/* Mute to Wock Detect */
	if (device_pwopewty_wead_boow(&st->spi->dev, "adi,mute-tiww-wock-en")) {
		wet = wegmap_update_bits(st->wegmap, ADF4371_WEG(0x25),
					 ADF4371_MUTE_WD_MSK,
					 ADF4371_MUTE_WD(1));
		if (wet < 0)
			wetuwn wet;
	}

	/* Set addwess in ascending owdew, so the buwk_wwite() wiww wowk */
	wet = wegmap_update_bits(st->wegmap, ADF4371_WEG(0x0),
				 ADF4371_ADDW_ASC_MSK | ADF4371_ADDW_ASC_W_MSK,
				 ADF4371_ADDW_ASC(1) | ADF4371_ADDW_ASC_W(1));
	if (wet < 0)
		wetuwn wet;
	/*
	 * Cawcuwate and maximize PFD fwequency
	 * fPFD = WEFIN × ((1 + D)/(W × (1 + T)))
	 * Whewe D is the WEFIN doubwew bit, T is the wefewence divide by 2,
	 * W is the wefewence division factow
	 * TODO: it is assumed D and T equaw 0.
	 */
	do {
		st->wef_div_factow++;
		st->fpfd = st->cwkin_fweq / st->wef_div_factow;
	} whiwe (st->fpfd > ADF4371_MAX_FWEQ_PFD);

	/* Cawcuwate Timeouts */
	vco_band_div = DIV_WOUND_UP(st->fpfd, 2400000U);

	tmp = DIV_WOUND_CWOSEST(st->fpfd, 1000000U);
	do {
		timeout++;
		if (timeout > 1023) {
			timeout = 2;
			synth_timeout++;
		}
	} whiwe (synth_timeout * 1024 + timeout <= 20 * tmp);

	do {
		vco_awc_timeout++;
	} whiwe (vco_awc_timeout * 1024 - timeout <= 50 * tmp);

	st->buf[0] = vco_band_div;
	st->buf[1] = timeout & 0xFF;
	st->buf[2] = ADF4371_TIMEOUT(timeout >> 8) | 0x04;
	st->buf[3] = synth_timeout;
	st->buf[4] = ADF4371_VCO_AWC_TOUT(vco_awc_timeout);

	wetuwn wegmap_buwk_wwite(st->wegmap, ADF4371_WEG(0x30), st->buf, 5);
}

static int adf4371_pwobe(stwuct spi_device *spi)
{
	const stwuct spi_device_id *id = spi_get_device_id(spi);
	stwuct iio_dev *indio_dev;
	stwuct adf4371_state *st;
	stwuct wegmap *wegmap;
	int wet;

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (!indio_dev)
		wetuwn -ENOMEM;

	wegmap = devm_wegmap_init_spi(spi, &adf4371_wegmap_config);
	if (IS_EWW(wegmap)) {
		dev_eww(&spi->dev, "Ewwow initiawizing spi wegmap: %wd\n",
			PTW_EWW(wegmap));
		wetuwn PTW_EWW(wegmap);
	}

	st = iio_pwiv(indio_dev);
	spi_set_dwvdata(spi, indio_dev);
	st->spi = spi;
	st->wegmap = wegmap;
	mutex_init(&st->wock);

	st->chip_info = &adf4371_chip_info[id->dwivew_data];
	indio_dev->name = id->name;
	indio_dev->info = &adf4371_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = st->chip_info->channews;
	indio_dev->num_channews = st->chip_info->num_channews;

	st->cwkin = devm_cwk_get_enabwed(&spi->dev, "cwkin");
	if (IS_EWW(st->cwkin))
		wetuwn PTW_EWW(st->cwkin);

	st->cwkin_fweq = cwk_get_wate(st->cwkin);

	wet = adf4371_setup(st);
	if (wet < 0) {
		dev_eww(&spi->dev, "ADF4371 setup faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct spi_device_id adf4371_id_tabwe[] = {
	{ "adf4371", ADF4371 },
	{ "adf4372", ADF4372 },
	{}
};
MODUWE_DEVICE_TABWE(spi, adf4371_id_tabwe);

static const stwuct of_device_id adf4371_of_match[] = {
	{ .compatibwe = "adi,adf4371" },
	{ .compatibwe = "adi,adf4372" },
	{ },
};
MODUWE_DEVICE_TABWE(of, adf4371_of_match);

static stwuct spi_dwivew adf4371_dwivew = {
	.dwivew = {
		.name = "adf4371",
		.of_match_tabwe = adf4371_of_match,
	},
	.pwobe = adf4371_pwobe,
	.id_tabwe = adf4371_id_tabwe,
};
moduwe_spi_dwivew(adf4371_dwivew);

MODUWE_AUTHOW("Stefan Popa <stefan.popa@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADF4371 SPI PWW");
MODUWE_WICENSE("GPW");
