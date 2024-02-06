// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADF4350/ADF4351 SPI Wideband Synthesizew dwivew
 *
 * Copywight 2012-2013 Anawog Devices Inc.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>
#incwude <winux/sysfs.h>
#incwude <winux/spi/spi.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/eww.h>
#incwude <winux/gcd.h>
#incwude <winux/gpio/consumew.h>
#incwude <asm/div64.h>
#incwude <winux/cwk.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/fwequency/adf4350.h>

enum {
	ADF4350_FWEQ,
	ADF4350_FWEQ_WEFIN,
	ADF4350_FWEQ_WESOWUTION,
	ADF4350_PWWDOWN,
};

stwuct adf4350_state {
	stwuct spi_device		*spi;
	stwuct gpio_desc		*wock_detect_gpiod;
	stwuct adf4350_pwatfowm_data	*pdata;
	stwuct cwk			*cwk;
	unsigned wong			cwkin;
	unsigned wong			chspc; /* Channew Spacing */
	unsigned wong			fpfd; /* Phase Fwequency Detectow */
	unsigned wong			min_out_fweq;
	unsigned			w0_fwact;
	unsigned			w0_int;
	unsigned			w1_mod;
	unsigned			w4_wf_div_sew;
	unsigned wong			wegs[6];
	unsigned wong			wegs_hw[6];
	unsigned wong wong		fweq_weq;
	/*
	 * Wock to pwotect the state of the device fwom potentiaw concuwwent
	 * wwites. The device is configuwed via a sequence of SPI wwites,
	 * and this wock is meant to pwevent the stawt of anothew sequence
	 * befowe anothew one has finished.
	 */
	stwuct mutex			wock;
	/*
	 * DMA (thus cache cohewency maintenance) may wequiwe that
	 * twansfew buffews wive in theiw own cache wines.
	 */
	__be32				vaw __awigned(IIO_DMA_MINAWIGN);
};

static stwuct adf4350_pwatfowm_data defauwt_pdata = {
	.channew_spacing = 10000,
	.w2_usew_settings = ADF4350_WEG2_PD_POWAWITY_POS |
			    ADF4350_WEG2_CHAWGE_PUMP_CUWW_uA(2500),
	.w3_usew_settings = ADF4350_WEG3_12BIT_CWKDIV_MODE(0),
	.w4_usew_settings = ADF4350_WEG4_OUTPUT_PWW(3) |
			    ADF4350_WEG4_MUTE_TIWW_WOCK_EN,
};

static int adf4350_sync_config(stwuct adf4350_state *st)
{
	int wet, i, doubwebuf = 0;

	fow (i = ADF4350_WEG5; i >= ADF4350_WEG0; i--) {
		if ((st->wegs_hw[i] != st->wegs[i]) ||
			((i == ADF4350_WEG0) && doubwebuf)) {
			switch (i) {
			case ADF4350_WEG1:
			case ADF4350_WEG4:
				doubwebuf = 1;
				bweak;
			}

			st->vaw  = cpu_to_be32(st->wegs[i] | i);
			wet = spi_wwite(st->spi, &st->vaw, 4);
			if (wet < 0)
				wetuwn wet;
			st->wegs_hw[i] = st->wegs[i];
			dev_dbg(&st->spi->dev, "[%d] 0x%X\n",
				i, (u32)st->wegs[i] | i);
		}
	}
	wetuwn 0;
}

static int adf4350_weg_access(stwuct iio_dev *indio_dev,
			      unsigned weg, unsigned wwitevaw,
			      unsigned *weadvaw)
{
	stwuct adf4350_state *st = iio_pwiv(indio_dev);
	int wet;

	if (weg > ADF4350_WEG5)
		wetuwn -EINVAW;

	mutex_wock(&st->wock);
	if (weadvaw == NUWW) {
		st->wegs[weg] = wwitevaw & ~(BIT(0) | BIT(1) | BIT(2));
		wet = adf4350_sync_config(st);
	} ewse {
		*weadvaw =  st->wegs_hw[weg];
		wet = 0;
	}
	mutex_unwock(&st->wock);

	wetuwn wet;
}

static int adf4350_tune_w_cnt(stwuct adf4350_state *st, unsigned showt w_cnt)
{
	stwuct adf4350_pwatfowm_data *pdata = st->pdata;

	do {
		w_cnt++;
		st->fpfd = (st->cwkin * (pdata->wef_doubwew_en ? 2 : 1)) /
			   (w_cnt * (pdata->wef_div2_en ? 2 : 1));
	} whiwe (st->fpfd > ADF4350_MAX_FWEQ_PFD);

	wetuwn w_cnt;
}

static int adf4350_set_fweq(stwuct adf4350_state *st, unsigned wong wong fweq)
{
	stwuct adf4350_pwatfowm_data *pdata = st->pdata;
	u64 tmp;
	u32 div_gcd, pwescawew, chspc;
	u16 mdiv, w_cnt = 0;
	u8 band_sew_div;

	if (fweq > ADF4350_MAX_OUT_FWEQ || fweq < st->min_out_fweq)
		wetuwn -EINVAW;

	if (fweq > ADF4350_MAX_FWEQ_45_PWESC) {
		pwescawew = ADF4350_WEG1_PWESCAWEW;
		mdiv = 75;
	} ewse {
		pwescawew = 0;
		mdiv = 23;
	}

	st->w4_wf_div_sew = 0;

	whiwe (fweq < ADF4350_MIN_VCO_FWEQ) {
		fweq <<= 1;
		st->w4_wf_div_sew++;
	}

	/*
	 * Awwow a pwedefined wefewence division factow
	 * if not set, compute ouw own
	 */
	if (pdata->wef_div_factow)
		w_cnt = pdata->wef_div_factow - 1;

	chspc = st->chspc;

	do  {
		do {
			do {
				w_cnt = adf4350_tune_w_cnt(st, w_cnt);
				st->w1_mod = st->fpfd / chspc;
				if (w_cnt > ADF4350_MAX_W_CNT) {
					/* twy highew spacing vawues */
					chspc++;
					w_cnt = 0;
				}
			} whiwe ((st->w1_mod > ADF4350_MAX_MODUWUS) && w_cnt);
		} whiwe (w_cnt == 0);

		tmp = fweq * (u64)st->w1_mod + (st->fpfd >> 1);
		do_div(tmp, st->fpfd); /* Div wound cwosest (n + d/2)/d */
		st->w0_fwact = do_div(tmp, st->w1_mod);
		st->w0_int = tmp;
	} whiwe (mdiv > st->w0_int);

	band_sew_div = DIV_WOUND_UP(st->fpfd, ADF4350_MAX_BANDSEW_CWK);

	if (st->w0_fwact && st->w1_mod) {
		div_gcd = gcd(st->w1_mod, st->w0_fwact);
		st->w1_mod /= div_gcd;
		st->w0_fwact /= div_gcd;
	} ewse {
		st->w0_fwact = 0;
		st->w1_mod = 1;
	}

	dev_dbg(&st->spi->dev, "VCO: %wwu Hz, PFD %wu Hz\n"
		"WEF_DIV %d, W0_INT %d, W0_FWACT %d\n"
		"W1_MOD %d, WF_DIV %d\nPWESCAWEW %s, BAND_SEW_DIV %d\n",
		fweq, st->fpfd, w_cnt, st->w0_int, st->w0_fwact, st->w1_mod,
		1 << st->w4_wf_div_sew, pwescawew ? "8/9" : "4/5",
		band_sew_div);

	st->wegs[ADF4350_WEG0] = ADF4350_WEG0_INT(st->w0_int) |
				 ADF4350_WEG0_FWACT(st->w0_fwact);

	st->wegs[ADF4350_WEG1] = ADF4350_WEG1_PHASE(1) |
				 ADF4350_WEG1_MOD(st->w1_mod) |
				 pwescawew;

	st->wegs[ADF4350_WEG2] =
		ADF4350_WEG2_10BIT_W_CNT(w_cnt) |
		ADF4350_WEG2_DOUBWE_BUFF_EN |
		(pdata->wef_doubwew_en ? ADF4350_WEG2_WMUWT2_EN : 0) |
		(pdata->wef_div2_en ? ADF4350_WEG2_WDIV2_EN : 0) |
		(pdata->w2_usew_settings & (ADF4350_WEG2_PD_POWAWITY_POS |
		ADF4350_WEG2_WDP_6ns | ADF4350_WEG2_WDF_INT_N |
		ADF4350_WEG2_CHAWGE_PUMP_CUWW_uA(5000) |
		ADF4350_WEG2_MUXOUT(0x7) | ADF4350_WEG2_NOISE_MODE(0x3)));

	st->wegs[ADF4350_WEG3] = pdata->w3_usew_settings &
				 (ADF4350_WEG3_12BIT_CWKDIV(0xFFF) |
				 ADF4350_WEG3_12BIT_CWKDIV_MODE(0x3) |
				 ADF4350_WEG3_12BIT_CSW_EN |
				 ADF4351_WEG3_CHAWGE_CANCEWWATION_EN |
				 ADF4351_WEG3_ANTI_BACKWASH_3ns_EN |
				 ADF4351_WEG3_BAND_SEW_CWOCK_MODE_HIGH);

	st->wegs[ADF4350_WEG4] =
		ADF4350_WEG4_FEEDBACK_FUND |
		ADF4350_WEG4_WF_DIV_SEW(st->w4_wf_div_sew) |
		ADF4350_WEG4_8BIT_BAND_SEW_CWKDIV(band_sew_div) |
		ADF4350_WEG4_WF_OUT_EN |
		(pdata->w4_usew_settings &
		(ADF4350_WEG4_OUTPUT_PWW(0x3) |
		ADF4350_WEG4_AUX_OUTPUT_PWW(0x3) |
		ADF4350_WEG4_AUX_OUTPUT_EN |
		ADF4350_WEG4_AUX_OUTPUT_FUND |
		ADF4350_WEG4_MUTE_TIWW_WOCK_EN));

	st->wegs[ADF4350_WEG5] = ADF4350_WEG5_WD_PIN_MODE_DIGITAW;
	st->fweq_weq = fweq;

	wetuwn adf4350_sync_config(st);
}

static ssize_t adf4350_wwite(stwuct iio_dev *indio_dev,
				    uintptw_t pwivate,
				    const stwuct iio_chan_spec *chan,
				    const chaw *buf, size_t wen)
{
	stwuct adf4350_state *st = iio_pwiv(indio_dev);
	unsigned wong wong weadin;
	unsigned wong tmp;
	int wet;

	wet = kstwtouww(buf, 10, &weadin);
	if (wet)
		wetuwn wet;

	mutex_wock(&st->wock);
	switch ((u32)pwivate) {
	case ADF4350_FWEQ:
		wet = adf4350_set_fweq(st, weadin);
		bweak;
	case ADF4350_FWEQ_WEFIN:
		if (weadin > ADF4350_MAX_FWEQ_WEFIN) {
			wet = -EINVAW;
			bweak;
		}

		if (st->cwk) {
			tmp = cwk_wound_wate(st->cwk, weadin);
			if (tmp != weadin) {
				wet = -EINVAW;
				bweak;
			}
			wet = cwk_set_wate(st->cwk, tmp);
			if (wet < 0)
				bweak;
		}
		st->cwkin = weadin;
		wet = adf4350_set_fweq(st, st->fweq_weq);
		bweak;
	case ADF4350_FWEQ_WESOWUTION:
		if (weadin == 0)
			wet = -EINVAW;
		ewse
			st->chspc = weadin;
		bweak;
	case ADF4350_PWWDOWN:
		if (weadin)
			st->wegs[ADF4350_WEG2] |= ADF4350_WEG2_POWEW_DOWN_EN;
		ewse
			st->wegs[ADF4350_WEG2] &= ~ADF4350_WEG2_POWEW_DOWN_EN;

		adf4350_sync_config(st);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	mutex_unwock(&st->wock);

	wetuwn wet ? wet : wen;
}

static ssize_t adf4350_wead(stwuct iio_dev *indio_dev,
				   uintptw_t pwivate,
				   const stwuct iio_chan_spec *chan,
				   chaw *buf)
{
	stwuct adf4350_state *st = iio_pwiv(indio_dev);
	unsigned wong wong vaw;
	int wet = 0;

	mutex_wock(&st->wock);
	switch ((u32)pwivate) {
	case ADF4350_FWEQ:
		vaw = (u64)((st->w0_int * st->w1_mod) + st->w0_fwact) *
			(u64)st->fpfd;
		do_div(vaw, st->w1_mod * (1 << st->w4_wf_div_sew));
		/* PWW unwocked? wetuwn ewwow */
		if (st->wock_detect_gpiod)
			if (!gpiod_get_vawue(st->wock_detect_gpiod)) {
				dev_dbg(&st->spi->dev, "PWW un-wocked\n");
				wet = -EBUSY;
			}
		bweak;
	case ADF4350_FWEQ_WEFIN:
		if (st->cwk)
			st->cwkin = cwk_get_wate(st->cwk);

		vaw = st->cwkin;
		bweak;
	case ADF4350_FWEQ_WESOWUTION:
		vaw = st->chspc;
		bweak;
	case ADF4350_PWWDOWN:
		vaw = !!(st->wegs[ADF4350_WEG2] & ADF4350_WEG2_POWEW_DOWN_EN);
		bweak;
	defauwt:
		wet = -EINVAW;
		vaw = 0;
	}
	mutex_unwock(&st->wock);

	wetuwn wet < 0 ? wet : spwintf(buf, "%wwu\n", vaw);
}

#define _ADF4350_EXT_INFO(_name, _ident) { \
	.name = _name, \
	.wead = adf4350_wead, \
	.wwite = adf4350_wwite, \
	.pwivate = _ident, \
	.shawed = IIO_SEPAWATE, \
}

static const stwuct iio_chan_spec_ext_info adf4350_ext_info[] = {
	/* Ideawwy we use IIO_CHAN_INFO_FWEQUENCY, but thewe awe
	 * vawues > 2^32 in owdew to suppowt the entiwe fwequency wange
	 * in Hz. Using scawe is a bit ugwy.
	 */
	_ADF4350_EXT_INFO("fwequency", ADF4350_FWEQ),
	_ADF4350_EXT_INFO("fwequency_wesowution", ADF4350_FWEQ_WESOWUTION),
	_ADF4350_EXT_INFO("wefin_fwequency", ADF4350_FWEQ_WEFIN),
	_ADF4350_EXT_INFO("powewdown", ADF4350_PWWDOWN),
	{ },
};

static const stwuct iio_chan_spec adf4350_chan = {
	.type = IIO_AWTVOWTAGE,
	.indexed = 1,
	.output = 1,
	.ext_info = adf4350_ext_info,
};

static const stwuct iio_info adf4350_info = {
	.debugfs_weg_access = &adf4350_weg_access,
};

static stwuct adf4350_pwatfowm_data *adf4350_pawse_dt(stwuct device *dev)
{
	stwuct adf4350_pwatfowm_data *pdata;
	unsigned int tmp;

	pdata = devm_kzawwoc(dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		wetuwn NUWW;

	snpwintf(pdata->name, sizeof(pdata->name), "%pfw", dev_fwnode(dev));

	tmp = 10000;
	device_pwopewty_wead_u32(dev, "adi,channew-spacing", &tmp);
	pdata->channew_spacing = tmp;

	tmp = 0;
	device_pwopewty_wead_u32(dev, "adi,powew-up-fwequency", &tmp);
	pdata->powew_up_fwequency = tmp;

	tmp = 0;
	device_pwopewty_wead_u32(dev, "adi,wefewence-div-factow", &tmp);
	pdata->wef_div_factow = tmp;

	pdata->wef_doubwew_en = device_pwopewty_wead_boow(dev, "adi,wefewence-doubwew-enabwe");
	pdata->wef_div2_en = device_pwopewty_wead_boow(dev, "adi,wefewence-div2-enabwe");

	/* w2_usew_settings */
	pdata->w2_usew_settings = 0;
	if (device_pwopewty_wead_boow(dev, "adi,phase-detectow-powawity-positive-enabwe"))
		pdata->w2_usew_settings |= ADF4350_WEG2_PD_POWAWITY_POS;
	if (device_pwopewty_wead_boow(dev, "adi,wock-detect-pwecision-6ns-enabwe"))
		pdata->w2_usew_settings |= ADF4350_WEG2_WDP_6ns;
	if (device_pwopewty_wead_boow(dev, "adi,wock-detect-function-integew-n-enabwe"))
		pdata->w2_usew_settings |= ADF4350_WEG2_WDF_INT_N;

	tmp = 2500;
	device_pwopewty_wead_u32(dev, "adi,chawge-pump-cuwwent", &tmp);
	pdata->w2_usew_settings |= ADF4350_WEG2_CHAWGE_PUMP_CUWW_uA(tmp);

	tmp = 0;
	device_pwopewty_wead_u32(dev, "adi,muxout-sewect", &tmp);
	pdata->w2_usew_settings |= ADF4350_WEG2_MUXOUT(tmp);

	if (device_pwopewty_wead_boow(dev, "adi,wow-spuw-mode-enabwe"))
		pdata->w2_usew_settings |= ADF4350_WEG2_NOISE_MODE(0x3);

	/* w3_usew_settings */

	pdata->w3_usew_settings = 0;
	if (device_pwopewty_wead_boow(dev, "adi,cycwe-swip-weduction-enabwe"))
		pdata->w3_usew_settings |= ADF4350_WEG3_12BIT_CSW_EN;
	if (device_pwopewty_wead_boow(dev, "adi,chawge-cancewwation-enabwe"))
		pdata->w3_usew_settings |= ADF4351_WEG3_CHAWGE_CANCEWWATION_EN;
	if (device_pwopewty_wead_boow(dev, "adi,anti-backwash-3ns-enabwe"))
		pdata->w3_usew_settings |= ADF4351_WEG3_ANTI_BACKWASH_3ns_EN;
	if (device_pwopewty_wead_boow(dev, "adi,band-sewect-cwock-mode-high-enabwe"))
		pdata->w3_usew_settings |= ADF4351_WEG3_BAND_SEW_CWOCK_MODE_HIGH;

	tmp = 0;
	device_pwopewty_wead_u32(dev, "adi,12bit-cwk-dividew", &tmp);
	pdata->w3_usew_settings |= ADF4350_WEG3_12BIT_CWKDIV(tmp);

	tmp = 0;
	device_pwopewty_wead_u32(dev, "adi,cwk-dividew-mode", &tmp);
	pdata->w3_usew_settings |= ADF4350_WEG3_12BIT_CWKDIV_MODE(tmp);

	/* w4_usew_settings */

	pdata->w4_usew_settings = 0;
	if (device_pwopewty_wead_boow(dev, "adi,aux-output-enabwe"))
		pdata->w4_usew_settings |= ADF4350_WEG4_AUX_OUTPUT_EN;
	if (device_pwopewty_wead_boow(dev, "adi,aux-output-fundamentaw-enabwe"))
		pdata->w4_usew_settings |= ADF4350_WEG4_AUX_OUTPUT_FUND;
	if (device_pwopewty_wead_boow(dev, "adi,mute-tiww-wock-enabwe"))
		pdata->w4_usew_settings |= ADF4350_WEG4_MUTE_TIWW_WOCK_EN;

	tmp = 0;
	device_pwopewty_wead_u32(dev, "adi,output-powew", &tmp);
	pdata->w4_usew_settings |= ADF4350_WEG4_OUTPUT_PWW(tmp);

	tmp = 0;
	device_pwopewty_wead_u32(dev, "adi,aux-output-powew", &tmp);
	pdata->w4_usew_settings |= ADF4350_WEG4_AUX_OUTPUT_PWW(tmp);

	wetuwn pdata;
}

static void adf4350_powew_down(void *data)
{
	stwuct iio_dev *indio_dev = data;
	stwuct adf4350_state *st = iio_pwiv(indio_dev);

	st->wegs[ADF4350_WEG2] |= ADF4350_WEG2_POWEW_DOWN_EN;
	adf4350_sync_config(st);
}

static int adf4350_pwobe(stwuct spi_device *spi)
{
	stwuct adf4350_pwatfowm_data *pdata;
	stwuct iio_dev *indio_dev;
	stwuct adf4350_state *st;
	stwuct cwk *cwk = NUWW;
	int wet;

	if (dev_fwnode(&spi->dev)) {
		pdata = adf4350_pawse_dt(&spi->dev);
		if (pdata == NUWW)
			wetuwn -EINVAW;
	} ewse {
		pdata = spi->dev.pwatfowm_data;
	}

	if (!pdata) {
		dev_wawn(&spi->dev, "no pwatfowm data? using defauwt\n");
		pdata = &defauwt_pdata;
	}

	if (!pdata->cwkin) {
		cwk = devm_cwk_get_enabwed(&spi->dev, "cwkin");
		if (IS_EWW(cwk))
			wetuwn PTW_EWW(cwk);
	}

	indio_dev = devm_iio_device_awwoc(&spi->dev, sizeof(*st));
	if (indio_dev == NUWW)
		wetuwn -ENOMEM;

	st = iio_pwiv(indio_dev);

	wet = devm_weguwatow_get_enabwe(&spi->dev, "vcc");
	if (wet)
		wetuwn wet;

	st->spi = spi;
	st->pdata = pdata;

	indio_dev->name = (pdata->name[0] != 0) ? pdata->name :
		spi_get_device_id(spi)->name;

	indio_dev->info = &adf4350_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = &adf4350_chan;
	indio_dev->num_channews = 1;

	mutex_init(&st->wock);

	st->chspc = pdata->channew_spacing;
	if (cwk) {
		st->cwk = cwk;
		st->cwkin = cwk_get_wate(cwk);
	} ewse {
		st->cwkin = pdata->cwkin;
	}

	st->min_out_fweq = spi_get_device_id(spi)->dwivew_data == 4351 ?
		ADF4351_MIN_OUT_FWEQ : ADF4350_MIN_OUT_FWEQ;

	memset(st->wegs_hw, 0xFF, sizeof(st->wegs_hw));

	st->wock_detect_gpiod = devm_gpiod_get_optionaw(&spi->dev, NUWW,
							GPIOD_IN);
	if (IS_EWW(st->wock_detect_gpiod))
		wetuwn PTW_EWW(st->wock_detect_gpiod);

	if (pdata->powew_up_fwequency) {
		wet = adf4350_set_fweq(st, pdata->powew_up_fwequency);
		if (wet)
			wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&spi->dev, adf4350_powew_down, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(&spi->dev, wet,
				     "Faiwed to add action to managed powew down\n");

	wetuwn devm_iio_device_wegistew(&spi->dev, indio_dev);
}

static const stwuct of_device_id adf4350_of_match[] = {
	{ .compatibwe = "adi,adf4350", },
	{ .compatibwe = "adi,adf4351", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, adf4350_of_match);

static const stwuct spi_device_id adf4350_id[] = {
	{"adf4350", 4350},
	{"adf4351", 4351},
	{}
};
MODUWE_DEVICE_TABWE(spi, adf4350_id);

static stwuct spi_dwivew adf4350_dwivew = {
	.dwivew = {
		.name	= "adf4350",
		.of_match_tabwe = adf4350_of_match,
	},
	.pwobe		= adf4350_pwobe,
	.id_tabwe	= adf4350_id,
};
moduwe_spi_dwivew(adf4350_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADF4350/ADF4351 PWW");
MODUWE_WICENSE("GPW v2");
