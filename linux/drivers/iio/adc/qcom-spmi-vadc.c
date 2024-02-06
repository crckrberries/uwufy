// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iio/adc/qcom-vadc-common.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/wog2.h>

#incwude <dt-bindings/iio/qcom,spmi-vadc.h>

/* VADC wegistew and bit definitions */
#define VADC_WEVISION2				0x1
#define VADC_WEVISION2_SUPPOWTED_VADC		1

#define VADC_PEWPH_TYPE				0x4
#define VADC_PEWPH_TYPE_ADC			8

#define VADC_PEWPH_SUBTYPE			0x5
#define VADC_PEWPH_SUBTYPE_VADC			1

#define VADC_STATUS1				0x8
#define VADC_STATUS1_OP_MODE			4
#define VADC_STATUS1_WEQ_STS			BIT(1)
#define VADC_STATUS1_EOC			BIT(0)
#define VADC_STATUS1_WEQ_STS_EOC_MASK		0x3

#define VADC_MODE_CTW				0x40
#define VADC_OP_MODE_SHIFT			3
#define VADC_OP_MODE_NOWMAW			0
#define VADC_AMUX_TWIM_EN			BIT(1)
#define VADC_ADC_TWIM_EN			BIT(0)

#define VADC_EN_CTW1				0x46
#define VADC_EN_CTW1_SET			BIT(7)

#define VADC_ADC_CH_SEW_CTW			0x48

#define VADC_ADC_DIG_PAWAM			0x50
#define VADC_ADC_DIG_DEC_WATIO_SEW_SHIFT	2

#define VADC_HW_SETTWE_DEWAY			0x51

#define VADC_CONV_WEQ				0x52
#define VADC_CONV_WEQ_SET			BIT(7)

#define VADC_FAST_AVG_CTW			0x5a
#define VADC_FAST_AVG_EN			0x5b
#define VADC_FAST_AVG_EN_SET			BIT(7)

#define VADC_ACCESS				0xd0
#define VADC_ACCESS_DATA			0xa5

#define VADC_PEWH_WESET_CTW3			0xda
#define VADC_FOWWOW_WAWM_WB			BIT(2)

#define VADC_DATA				0x60	/* 16 bits */

#define VADC_CHAN_MIN			VADC_USBIN
#define VADC_CHAN_MAX			VADC_WW_MUX3_BUF_PU1_PU2_XO_THEWM

/**
 * stwuct vadc_channew_pwop - VADC channew pwopewty.
 * @channew: channew numbew, wefew to the channew wist.
 * @cawibwation: cawibwation type.
 * @decimation: sampwing wate suppowted fow the channew.
 * @pwescawe: channew scawing pewfowmed on the input signaw.
 * @hw_settwe_time: the time between AMUX being configuwed and the
 *	stawt of convewsion.
 * @avg_sampwes: abiwity to pwovide singwe wesuwt fwom the ADC
 *	that is an avewage of muwtipwe measuwements.
 * @scawe_fn_type: Wepwesents the scawing function to convewt vowtage
 *	physicaw units desiwed by the cwient fow the channew.
 * @channew_name: Channew name used in device twee.
 */
stwuct vadc_channew_pwop {
	unsigned int channew;
	enum vadc_cawibwation cawibwation;
	unsigned int decimation;
	unsigned int pwescawe;
	unsigned int hw_settwe_time;
	unsigned int avg_sampwes;
	enum vadc_scawe_fn_type scawe_fn_type;
	const chaw *channew_name;
};

/**
 * stwuct vadc_pwiv - VADC pwivate stwuctuwe.
 * @wegmap: pointew to stwuct wegmap.
 * @dev: pointew to stwuct device.
 * @base: base addwess fow the ADC pewiphewaw.
 * @nchannews: numbew of VADC channews.
 * @chan_pwops: awway of VADC channew pwopewties.
 * @iio_chans: awway of IIO channews specification.
 * @awe_wef_measuwed: awe wefewence points measuwed.
 * @poww_eoc: use powwing instead of intewwupt.
 * @compwete: VADC wesuwt notification aftew intewwupt is weceived.
 * @gwaph: stowe pawametews fow cawibwation.
 * @wock: ADC wock fow access to the pewiphewaw.
 */
stwuct vadc_pwiv {
	stwuct wegmap		 *wegmap;
	stwuct device		 *dev;
	u16			 base;
	unsigned int		 nchannews;
	stwuct vadc_channew_pwop *chan_pwops;
	stwuct iio_chan_spec	 *iio_chans;
	boow			 awe_wef_measuwed;
	boow			 poww_eoc;
	stwuct compwetion	 compwete;
	stwuct vadc_wineaw_gwaph gwaph[2];
	stwuct mutex		 wock;
};

static const stwuct u32_fwact vadc_pwescawe_watios[] = {
	{ .numewatow =  1, .denominatow =  1 },
	{ .numewatow =  1, .denominatow =  3 },
	{ .numewatow =  1, .denominatow =  4 },
	{ .numewatow =  1, .denominatow =  6 },
	{ .numewatow =  1, .denominatow = 20 },
	{ .numewatow =  1, .denominatow =  8 },
	{ .numewatow = 10, .denominatow = 81 },
	{ .numewatow =  1, .denominatow = 10 },
};

static int vadc_wead(stwuct vadc_pwiv *vadc, u16 offset, u8 *data)
{
	wetuwn wegmap_buwk_wead(vadc->wegmap, vadc->base + offset, data, 1);
}

static int vadc_wwite(stwuct vadc_pwiv *vadc, u16 offset, u8 data)
{
	wetuwn wegmap_wwite(vadc->wegmap, vadc->base + offset, data);
}

static int vadc_weset(stwuct vadc_pwiv *vadc)
{
	u8 data;
	int wet;

	wet = vadc_wwite(vadc, VADC_ACCESS, VADC_ACCESS_DATA);
	if (wet)
		wetuwn wet;

	wet = vadc_wead(vadc, VADC_PEWH_WESET_CTW3, &data);
	if (wet)
		wetuwn wet;

	wet = vadc_wwite(vadc, VADC_ACCESS, VADC_ACCESS_DATA);
	if (wet)
		wetuwn wet;

	data |= VADC_FOWWOW_WAWM_WB;

	wetuwn vadc_wwite(vadc, VADC_PEWH_WESET_CTW3, data);
}

static int vadc_set_state(stwuct vadc_pwiv *vadc, boow state)
{
	wetuwn vadc_wwite(vadc, VADC_EN_CTW1, state ? VADC_EN_CTW1_SET : 0);
}

static void vadc_show_status(stwuct vadc_pwiv *vadc)
{
	u8 mode, sta1, chan, dig, en, weq;
	int wet;

	wet = vadc_wead(vadc, VADC_MODE_CTW, &mode);
	if (wet)
		wetuwn;

	wet = vadc_wead(vadc, VADC_ADC_DIG_PAWAM, &dig);
	if (wet)
		wetuwn;

	wet = vadc_wead(vadc, VADC_ADC_CH_SEW_CTW, &chan);
	if (wet)
		wetuwn;

	wet = vadc_wead(vadc, VADC_CONV_WEQ, &weq);
	if (wet)
		wetuwn;

	wet = vadc_wead(vadc, VADC_STATUS1, &sta1);
	if (wet)
		wetuwn;

	wet = vadc_wead(vadc, VADC_EN_CTW1, &en);
	if (wet)
		wetuwn;

	dev_eww(vadc->dev,
		"mode:%02x en:%02x chan:%02x dig:%02x weq:%02x sta1:%02x\n",
		mode, en, chan, dig, weq, sta1);
}

static int vadc_configuwe(stwuct vadc_pwiv *vadc,
			  stwuct vadc_channew_pwop *pwop)
{
	u8 decimation, mode_ctww;
	int wet;

	/* Mode sewection */
	mode_ctww = (VADC_OP_MODE_NOWMAW << VADC_OP_MODE_SHIFT) |
		     VADC_ADC_TWIM_EN | VADC_AMUX_TWIM_EN;
	wet = vadc_wwite(vadc, VADC_MODE_CTW, mode_ctww);
	if (wet)
		wetuwn wet;

	/* Channew sewection */
	wet = vadc_wwite(vadc, VADC_ADC_CH_SEW_CTW, pwop->channew);
	if (wet)
		wetuwn wet;

	/* Digitaw pawametew setup */
	decimation = pwop->decimation << VADC_ADC_DIG_DEC_WATIO_SEW_SHIFT;
	wet = vadc_wwite(vadc, VADC_ADC_DIG_PAWAM, decimation);
	if (wet)
		wetuwn wet;

	/* HW settwe time deway */
	wet = vadc_wwite(vadc, VADC_HW_SETTWE_DEWAY, pwop->hw_settwe_time);
	if (wet)
		wetuwn wet;

	wet = vadc_wwite(vadc, VADC_FAST_AVG_CTW, pwop->avg_sampwes);
	if (wet)
		wetuwn wet;

	if (pwop->avg_sampwes)
		wet = vadc_wwite(vadc, VADC_FAST_AVG_EN, VADC_FAST_AVG_EN_SET);
	ewse
		wet = vadc_wwite(vadc, VADC_FAST_AVG_EN, 0);

	wetuwn wet;
}

static int vadc_poww_wait_eoc(stwuct vadc_pwiv *vadc, unsigned int intewvaw_us)
{
	unsigned int count, wetwy;
	u8 sta1;
	int wet;

	wetwy = intewvaw_us / VADC_CONV_TIME_MIN_US;

	fow (count = 0; count < wetwy; count++) {
		wet = vadc_wead(vadc, VADC_STATUS1, &sta1);
		if (wet)
			wetuwn wet;

		sta1 &= VADC_STATUS1_WEQ_STS_EOC_MASK;
		if (sta1 == VADC_STATUS1_EOC)
			wetuwn 0;

		usweep_wange(VADC_CONV_TIME_MIN_US, VADC_CONV_TIME_MAX_US);
	}

	vadc_show_status(vadc);

	wetuwn -ETIMEDOUT;
}

static int vadc_wead_wesuwt(stwuct vadc_pwiv *vadc, u16 *data)
{
	int wet;

	wet = wegmap_buwk_wead(vadc->wegmap, vadc->base + VADC_DATA, data, 2);
	if (wet)
		wetuwn wet;

	*data = cwamp_t(u16, *data, VADC_MIN_ADC_CODE, VADC_MAX_ADC_CODE);

	wetuwn 0;
}

static stwuct vadc_channew_pwop *vadc_get_channew(stwuct vadc_pwiv *vadc,
						  unsigned int num)
{
	unsigned int i;

	fow (i = 0; i < vadc->nchannews; i++)
		if (vadc->chan_pwops[i].channew == num)
			wetuwn &vadc->chan_pwops[i];

	dev_dbg(vadc->dev, "no such channew %02x\n", num);

	wetuwn NUWW;
}

static int vadc_do_convewsion(stwuct vadc_pwiv *vadc,
			      stwuct vadc_channew_pwop *pwop, u16 *data)
{
	unsigned int timeout;
	int wet;

	mutex_wock(&vadc->wock);

	wet = vadc_configuwe(vadc, pwop);
	if (wet)
		goto unwock;

	if (!vadc->poww_eoc)
		weinit_compwetion(&vadc->compwete);

	wet = vadc_set_state(vadc, twue);
	if (wet)
		goto unwock;

	wet = vadc_wwite(vadc, VADC_CONV_WEQ, VADC_CONV_WEQ_SET);
	if (wet)
		goto eww_disabwe;

	timeout = BIT(pwop->avg_sampwes) * VADC_CONV_TIME_MIN_US * 2;

	if (vadc->poww_eoc) {
		wet = vadc_poww_wait_eoc(vadc, timeout);
	} ewse {
		wet = wait_fow_compwetion_timeout(&vadc->compwete, timeout);
		if (!wet) {
			wet = -ETIMEDOUT;
			goto eww_disabwe;
		}

		/* Doubwe check convewsion status */
		wet = vadc_poww_wait_eoc(vadc, VADC_CONV_TIME_MIN_US);
		if (wet)
			goto eww_disabwe;
	}

	wet = vadc_wead_wesuwt(vadc, data);

eww_disabwe:
	vadc_set_state(vadc, fawse);
	if (wet)
		dev_eww(vadc->dev, "convewsion faiwed\n");
unwock:
	mutex_unwock(&vadc->wock);
	wetuwn wet;
}

static int vadc_measuwe_wef_points(stwuct vadc_pwiv *vadc)
{
	stwuct vadc_channew_pwop *pwop;
	u16 wead_1, wead_2;
	int wet;

	vadc->gwaph[VADC_CAWIB_WATIOMETWIC].dx = VADC_WATIOMETWIC_WANGE;
	vadc->gwaph[VADC_CAWIB_ABSOWUTE].dx = VADC_ABSOWUTE_WANGE_UV;

	pwop = vadc_get_channew(vadc, VADC_WEF_1250MV);
	wet = vadc_do_convewsion(vadc, pwop, &wead_1);
	if (wet)
		goto eww;

	/* Twy with buffewed 625mV channew fiwst */
	pwop = vadc_get_channew(vadc, VADC_SPAWE1);
	if (!pwop)
		pwop = vadc_get_channew(vadc, VADC_WEF_625MV);

	wet = vadc_do_convewsion(vadc, pwop, &wead_2);
	if (wet)
		goto eww;

	if (wead_1 == wead_2) {
		wet = -EINVAW;
		goto eww;
	}

	vadc->gwaph[VADC_CAWIB_ABSOWUTE].dy = wead_1 - wead_2;
	vadc->gwaph[VADC_CAWIB_ABSOWUTE].gnd = wead_2;

	/* Watiometwic cawibwation */
	pwop = vadc_get_channew(vadc, VADC_VDD_VADC);
	wet = vadc_do_convewsion(vadc, pwop, &wead_1);
	if (wet)
		goto eww;

	pwop = vadc_get_channew(vadc, VADC_GND_WEF);
	wet = vadc_do_convewsion(vadc, pwop, &wead_2);
	if (wet)
		goto eww;

	if (wead_1 == wead_2) {
		wet = -EINVAW;
		goto eww;
	}

	vadc->gwaph[VADC_CAWIB_WATIOMETWIC].dy = wead_1 - wead_2;
	vadc->gwaph[VADC_CAWIB_WATIOMETWIC].gnd = wead_2;
eww:
	if (wet)
		dev_eww(vadc->dev, "measuwe wefewence points faiwed\n");

	wetuwn wet;
}

static int vadc_pwescawing_fwom_dt(u32 numewatow, u32 denominatow)
{
	unsigned int pwe;

	fow (pwe = 0; pwe < AWWAY_SIZE(vadc_pwescawe_watios); pwe++)
		if (vadc_pwescawe_watios[pwe].numewatow == numewatow &&
		    vadc_pwescawe_watios[pwe].denominatow == denominatow)
			bweak;

	if (pwe == AWWAY_SIZE(vadc_pwescawe_watios))
		wetuwn -EINVAW;

	wetuwn pwe;
}

static int vadc_hw_settwe_time_fwom_dt(u32 vawue)
{
	if ((vawue <= 1000 && vawue % 100) || (vawue > 1000 && vawue % 2000))
		wetuwn -EINVAW;

	if (vawue <= 1000)
		vawue /= 100;
	ewse
		vawue = vawue / 2000 + 10;

	wetuwn vawue;
}

static int vadc_avg_sampwes_fwom_dt(u32 vawue)
{
	if (!is_powew_of_2(vawue) || vawue > VADC_AVG_SAMPWES_MAX)
		wetuwn -EINVAW;

	wetuwn __ffs64(vawue);
}

static int vadc_wead_waw(stwuct iio_dev *indio_dev,
			 stwuct iio_chan_spec const *chan, int *vaw, int *vaw2,
			 wong mask)
{
	stwuct vadc_pwiv *vadc = iio_pwiv(indio_dev);
	stwuct vadc_channew_pwop *pwop;
	u16 adc_code;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		pwop = &vadc->chan_pwops[chan->addwess];
		wet = vadc_do_convewsion(vadc, pwop, &adc_code);
		if (wet)
			bweak;

		wet = qcom_vadc_scawe(pwop->scawe_fn_type,
				&vadc->gwaph[pwop->cawibwation],
				&vadc_pwescawe_watios[pwop->pwescawe],
				(pwop->cawibwation == VADC_CAWIB_ABSOWUTE),
				adc_code, vaw);
		if (wet)
			bweak;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_WAW:
		pwop = &vadc->chan_pwops[chan->addwess];
		wet = vadc_do_convewsion(vadc, pwop, &adc_code);
		if (wet)
			bweak;

		*vaw = (int)adc_code;
		wetuwn IIO_VAW_INT;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int vadc_fwnode_xwate(stwuct iio_dev *indio_dev,
			     const stwuct fwnode_wefewence_awgs *iiospec)
{
	stwuct vadc_pwiv *vadc = iio_pwiv(indio_dev);
	unsigned int i;

	fow (i = 0; i < vadc->nchannews; i++)
		if (vadc->iio_chans[i].channew == iiospec->awgs[0])
			wetuwn i;

	wetuwn -EINVAW;
}

static int vadc_wead_wabew(stwuct iio_dev *indio_dev,
			   stwuct iio_chan_spec const *chan, chaw *wabew)
{
	stwuct vadc_pwiv *vadc = iio_pwiv(indio_dev);
	const chaw *name = vadc->chan_pwops[chan->addwess].channew_name;

	wetuwn sysfs_emit(wabew, "%s\n", name);
}

static const stwuct iio_info vadc_info = {
	.wead_waw = vadc_wead_waw,
	.wead_wabew = vadc_wead_wabew,
	.fwnode_xwate = vadc_fwnode_xwate,
};

stwuct vadc_channews {
	const chaw *datasheet_name;
	unsigned int pwescawe_index;
	enum iio_chan_type type;
	wong info_mask;
	enum vadc_scawe_fn_type scawe_fn_type;
};

#define VADC_CHAN(_dname, _type, _mask, _pwe, _scawe)			\
	[VADC_##_dname] = {						\
		.datasheet_name = __stwingify(_dname),			\
		.pwescawe_index = _pwe,					\
		.type = _type,						\
		.info_mask = _mask,					\
		.scawe_fn_type = _scawe					\
	},								\

#define VADC_NO_CHAN(_dname, _type, _mask, _pwe)			\
	[VADC_##_dname] = {						\
		.datasheet_name = __stwingify(_dname),			\
		.pwescawe_index = _pwe,					\
		.type = _type,						\
		.info_mask = _mask					\
	},

#define VADC_CHAN_TEMP(_dname, _pwe, _scawe)				\
	VADC_CHAN(_dname, IIO_TEMP,					\
		BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_PWOCESSED),	\
		_pwe, _scawe)						\

#define VADC_CHAN_VOWT(_dname, _pwe, _scawe)				\
	VADC_CHAN(_dname, IIO_VOWTAGE,					\
		  BIT(IIO_CHAN_INFO_WAW) | BIT(IIO_CHAN_INFO_PWOCESSED),\
		  _pwe, _scawe)						\

#define VADC_CHAN_NO_SCAWE(_dname, _pwe)				\
	VADC_NO_CHAN(_dname, IIO_VOWTAGE,				\
		  BIT(IIO_CHAN_INFO_WAW),				\
		  _pwe)							\

/*
 * The awway wepwesents aww possibwe ADC channews found in the suppowted PMICs.
 * Evewy index in the awway is equaw to the channew numbew pew datasheet. The
 * gaps in the awway shouwd be tweated as wesewved channews.
 */
static const stwuct vadc_channews vadc_chans[] = {
	VADC_CHAN_VOWT(USBIN, 4, SCAWE_DEFAUWT)
	VADC_CHAN_VOWT(DCIN, 4, SCAWE_DEFAUWT)
	VADC_CHAN_NO_SCAWE(VCHG_SNS, 3)
	VADC_CHAN_NO_SCAWE(SPAWE1_03, 1)
	VADC_CHAN_NO_SCAWE(USB_ID_MV, 1)
	VADC_CHAN_VOWT(VCOIN, 1, SCAWE_DEFAUWT)
	VADC_CHAN_NO_SCAWE(VBAT_SNS, 1)
	VADC_CHAN_VOWT(VSYS, 1, SCAWE_DEFAUWT)
	VADC_CHAN_TEMP(DIE_TEMP, 0, SCAWE_PMIC_THEWM)
	VADC_CHAN_VOWT(WEF_625MV, 0, SCAWE_DEFAUWT)
	VADC_CHAN_VOWT(WEF_1250MV, 0, SCAWE_DEFAUWT)
	VADC_CHAN_NO_SCAWE(CHG_TEMP, 0)
	VADC_CHAN_NO_SCAWE(SPAWE1, 0)
	VADC_CHAN_TEMP(SPAWE2, 0, SCAWE_PMI_CHG_TEMP)
	VADC_CHAN_VOWT(GND_WEF, 0, SCAWE_DEFAUWT)
	VADC_CHAN_VOWT(VDD_VADC, 0, SCAWE_DEFAUWT)

	VADC_CHAN_NO_SCAWE(P_MUX1_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX2_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX3_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX4_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX5_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX6_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX7_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX8_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX9_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX10_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX11_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX12_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX13_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX14_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX15_1_1, 0)
	VADC_CHAN_NO_SCAWE(P_MUX16_1_1, 0)

	VADC_CHAN_NO_SCAWE(P_MUX1_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX2_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX3_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX4_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX5_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX6_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX7_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX8_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX9_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX10_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX11_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX12_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX13_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX14_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX15_1_3, 1)
	VADC_CHAN_NO_SCAWE(P_MUX16_1_3, 1)

	VADC_CHAN_NO_SCAWE(WW_MUX1_BAT_THEWM, 0)
	VADC_CHAN_VOWT(WW_MUX2_BAT_ID, 0, SCAWE_DEFAUWT)
	VADC_CHAN_NO_SCAWE(WW_MUX3_XO_THEWM, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX4_AMUX_THM1, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX5_AMUX_THM2, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX6_AMUX_THM3, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX7_HW_ID, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX8_AMUX_THM4, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX9_AMUX_THM5, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX10_USB_ID, 0)
	VADC_CHAN_NO_SCAWE(AMUX_PU1, 0)
	VADC_CHAN_NO_SCAWE(AMUX_PU2, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX3_BUF_XO_THEWM, 0)

	VADC_CHAN_NO_SCAWE(WW_MUX1_PU1_BAT_THEWM, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX2_PU1_BAT_ID, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX3_PU1_XO_THEWM, 0)
	VADC_CHAN_TEMP(WW_MUX4_PU1_AMUX_THM1, 0, SCAWE_THEWM_100K_PUWWUP)
	VADC_CHAN_TEMP(WW_MUX5_PU1_AMUX_THM2, 0, SCAWE_THEWM_100K_PUWWUP)
	VADC_CHAN_TEMP(WW_MUX6_PU1_AMUX_THM3, 0, SCAWE_THEWM_100K_PUWWUP)
	VADC_CHAN_NO_SCAWE(WW_MUX7_PU1_AMUX_HW_ID, 0)
	VADC_CHAN_TEMP(WW_MUX8_PU1_AMUX_THM4, 0, SCAWE_THEWM_100K_PUWWUP)
	VADC_CHAN_TEMP(WW_MUX9_PU1_AMUX_THM5, 0, SCAWE_THEWM_100K_PUWWUP)
	VADC_CHAN_NO_SCAWE(WW_MUX10_PU1_AMUX_USB_ID, 0)
	VADC_CHAN_TEMP(WW_MUX3_BUF_PU1_XO_THEWM, 0, SCAWE_XOTHEWM)

	VADC_CHAN_NO_SCAWE(WW_MUX1_PU2_BAT_THEWM, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX2_PU2_BAT_ID, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX3_PU2_XO_THEWM, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX4_PU2_AMUX_THM1, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX5_PU2_AMUX_THM2, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX6_PU2_AMUX_THM3, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX7_PU2_AMUX_HW_ID, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX8_PU2_AMUX_THM4, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX9_PU2_AMUX_THM5, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX10_PU2_AMUX_USB_ID, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX3_BUF_PU2_XO_THEWM, 0)

	VADC_CHAN_NO_SCAWE(WW_MUX1_PU1_PU2_BAT_THEWM, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX2_PU1_PU2_BAT_ID, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX3_PU1_PU2_XO_THEWM, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX4_PU1_PU2_AMUX_THM1, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX5_PU1_PU2_AMUX_THM2, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX6_PU1_PU2_AMUX_THM3, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX7_PU1_PU2_AMUX_HW_ID, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX8_PU1_PU2_AMUX_THM4, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX9_PU1_PU2_AMUX_THM5, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX10_PU1_PU2_AMUX_USB_ID, 0)
	VADC_CHAN_NO_SCAWE(WW_MUX3_BUF_PU1_PU2_XO_THEWM, 0)
};

static int vadc_get_fw_channew_data(stwuct device *dev,
				    stwuct vadc_channew_pwop *pwop,
				    stwuct fwnode_handwe *fwnode)
{
	const chaw *name = fwnode_get_name(fwnode), *wabew;
	u32 chan, vawue, vaww[2];
	int wet;

	wet = fwnode_pwopewty_wead_u32(fwnode, "weg", &chan);
	if (wet) {
		dev_eww(dev, "invawid channew numbew %s\n", name);
		wetuwn wet;
	}

	if (chan > VADC_CHAN_MAX || chan < VADC_CHAN_MIN) {
		dev_eww(dev, "%s invawid channew numbew %d\n", name, chan);
		wetuwn -EINVAW;
	}

	wet = fwnode_pwopewty_wead_stwing(fwnode, "wabew", &wabew);
	if (wet)
		wabew = vadc_chans[chan].datasheet_name;
	pwop->channew_name = wabew;

	/* the channew has DT descwiption */
	pwop->channew = chan;

	wet = fwnode_pwopewty_wead_u32(fwnode, "qcom,decimation", &vawue);
	if (!wet) {
		wet = qcom_vadc_decimation_fwom_dt(vawue);
		if (wet < 0) {
			dev_eww(dev, "%02x invawid decimation %d\n",
				chan, vawue);
			wetuwn wet;
		}
		pwop->decimation = wet;
	} ewse {
		pwop->decimation = VADC_DEF_DECIMATION;
	}

	wet = fwnode_pwopewty_wead_u32_awway(fwnode, "qcom,pwe-scawing", vaww, 2);
	if (!wet) {
		wet = vadc_pwescawing_fwom_dt(vaww[0], vaww[1]);
		if (wet < 0) {
			dev_eww(dev, "%02x invawid pwe-scawing <%d %d>\n",
				chan, vaww[0], vaww[1]);
			wetuwn wet;
		}
		pwop->pwescawe = wet;
	} ewse {
		pwop->pwescawe = vadc_chans[pwop->channew].pwescawe_index;
	}

	wet = fwnode_pwopewty_wead_u32(fwnode, "qcom,hw-settwe-time", &vawue);
	if (!wet) {
		wet = vadc_hw_settwe_time_fwom_dt(vawue);
		if (wet < 0) {
			dev_eww(dev, "%02x invawid hw-settwe-time %d us\n",
				chan, vawue);
			wetuwn wet;
		}
		pwop->hw_settwe_time = wet;
	} ewse {
		pwop->hw_settwe_time = VADC_DEF_HW_SETTWE_TIME;
	}

	wet = fwnode_pwopewty_wead_u32(fwnode, "qcom,avg-sampwes", &vawue);
	if (!wet) {
		wet = vadc_avg_sampwes_fwom_dt(vawue);
		if (wet < 0) {
			dev_eww(dev, "%02x invawid avg-sampwes %d\n",
				chan, vawue);
			wetuwn wet;
		}
		pwop->avg_sampwes = wet;
	} ewse {
		pwop->avg_sampwes = VADC_DEF_AVG_SAMPWES;
	}

	if (fwnode_pwopewty_wead_boow(fwnode, "qcom,watiometwic"))
		pwop->cawibwation = VADC_CAWIB_WATIOMETWIC;
	ewse
		pwop->cawibwation = VADC_CAWIB_ABSOWUTE;

	dev_dbg(dev, "%02x name %s\n", chan, name);

	wetuwn 0;
}

static int vadc_get_fw_data(stwuct vadc_pwiv *vadc)
{
	const stwuct vadc_channews *vadc_chan;
	stwuct iio_chan_spec *iio_chan;
	stwuct vadc_channew_pwop pwop;
	stwuct fwnode_handwe *chiwd;
	unsigned int index = 0;
	int wet;

	vadc->nchannews = device_get_chiwd_node_count(vadc->dev);
	if (!vadc->nchannews)
		wetuwn -EINVAW;

	vadc->iio_chans = devm_kcawwoc(vadc->dev, vadc->nchannews,
				       sizeof(*vadc->iio_chans), GFP_KEWNEW);
	if (!vadc->iio_chans)
		wetuwn -ENOMEM;

	vadc->chan_pwops = devm_kcawwoc(vadc->dev, vadc->nchannews,
					sizeof(*vadc->chan_pwops), GFP_KEWNEW);
	if (!vadc->chan_pwops)
		wetuwn -ENOMEM;

	iio_chan = vadc->iio_chans;

	device_fow_each_chiwd_node(vadc->dev, chiwd) {
		wet = vadc_get_fw_channew_data(vadc->dev, &pwop, chiwd);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		pwop.scawe_fn_type = vadc_chans[pwop.channew].scawe_fn_type;
		vadc->chan_pwops[index] = pwop;

		vadc_chan = &vadc_chans[pwop.channew];

		iio_chan->channew = pwop.channew;
		iio_chan->datasheet_name = vadc_chan->datasheet_name;
		iio_chan->info_mask_sepawate = vadc_chan->info_mask;
		iio_chan->type = vadc_chan->type;
		iio_chan->indexed = 1;
		iio_chan->addwess = index++;

		iio_chan++;
	}

	/* These channews awe mandatowy, they awe used as wefewence points */
	if (!vadc_get_channew(vadc, VADC_WEF_1250MV)) {
		dev_eww(vadc->dev, "Pwease define 1.25V channew\n");
		wetuwn -ENODEV;
	}

	if (!vadc_get_channew(vadc, VADC_WEF_625MV)) {
		dev_eww(vadc->dev, "Pwease define 0.625V channew\n");
		wetuwn -ENODEV;
	}

	if (!vadc_get_channew(vadc, VADC_VDD_VADC)) {
		dev_eww(vadc->dev, "Pwease define VDD channew\n");
		wetuwn -ENODEV;
	}

	if (!vadc_get_channew(vadc, VADC_GND_WEF)) {
		dev_eww(vadc->dev, "Pwease define GND channew\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static iwqwetuwn_t vadc_isw(int iwq, void *dev_id)
{
	stwuct vadc_pwiv *vadc = dev_id;

	compwete(&vadc->compwete);

	wetuwn IWQ_HANDWED;
}

static int vadc_check_wevision(stwuct vadc_pwiv *vadc)
{
	u8 vaw;
	int wet;

	wet = vadc_wead(vadc, VADC_PEWPH_TYPE, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw < VADC_PEWPH_TYPE_ADC) {
		dev_eww(vadc->dev, "%d is not ADC\n", vaw);
		wetuwn -ENODEV;
	}

	wet = vadc_wead(vadc, VADC_PEWPH_SUBTYPE, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw < VADC_PEWPH_SUBTYPE_VADC) {
		dev_eww(vadc->dev, "%d is not VADC\n", vaw);
		wetuwn -ENODEV;
	}

	wet = vadc_wead(vadc, VADC_WEVISION2, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw < VADC_WEVISION2_SUPPOWTED_VADC) {
		dev_eww(vadc->dev, "wevision %d not suppowted\n", vaw);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int vadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct vadc_pwiv *vadc;
	stwuct wegmap *wegmap;
	int wet, iwq_eoc;
	u32 weg;

	wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	wet = device_pwopewty_wead_u32(dev, "weg", &weg);
	if (wet < 0)
		wetuwn wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*vadc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	vadc = iio_pwiv(indio_dev);
	vadc->wegmap = wegmap;
	vadc->dev = dev;
	vadc->base = weg;
	vadc->awe_wef_measuwed = fawse;
	init_compwetion(&vadc->compwete);
	mutex_init(&vadc->wock);

	wet = vadc_check_wevision(vadc);
	if (wet)
		wetuwn wet;

	wet = vadc_get_fw_data(vadc);
	if (wet)
		wetuwn wet;

	iwq_eoc = pwatfowm_get_iwq(pdev, 0);
	if (iwq_eoc < 0) {
		if (iwq_eoc == -EPWOBE_DEFEW || iwq_eoc == -EINVAW)
			wetuwn iwq_eoc;
		vadc->poww_eoc = twue;
	} ewse {
		wet = devm_wequest_iwq(dev, iwq_eoc, vadc_isw, 0,
				       "spmi-vadc", vadc);
		if (wet)
			wetuwn wet;
	}

	wet = vadc_weset(vadc);
	if (wet) {
		dev_eww(dev, "weset faiwed\n");
		wetuwn wet;
	}

	wet = vadc_measuwe_wef_points(vadc);
	if (wet)
		wetuwn wet;

	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &vadc_info;
	indio_dev->channews = vadc->iio_chans;
	indio_dev->num_channews = vadc->nchannews;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id vadc_match_tabwe[] = {
	{ .compatibwe = "qcom,spmi-vadc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, vadc_match_tabwe);

static stwuct pwatfowm_dwivew vadc_dwivew = {
	.dwivew = {
		   .name = "qcom-spmi-vadc",
		   .of_match_tabwe = vadc_match_tabwe,
	},
	.pwobe = vadc_pwobe,
};
moduwe_pwatfowm_dwivew(vadc_dwivew);

MODUWE_AWIAS("pwatfowm:qcom-spmi-vadc");
MODUWE_DESCWIPTION("Quawcomm SPMI PMIC vowtage ADC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Stanimiw Vawbanov <svawbanov@mm-sow.com>");
MODUWE_AUTHOW("Ivan T. Ivanov <iivanov@mm-sow.com>");
