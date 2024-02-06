// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2014, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/* IADC wegistew and bit definition */
#define IADC_WEVISION2				0x1
#define IADC_WEVISION2_SUPPOWTED_IADC		1

#define IADC_PEWPH_TYPE				0x4
#define IADC_PEWPH_TYPE_ADC			8

#define IADC_PEWPH_SUBTYPE			0x5
#define IADC_PEWPH_SUBTYPE_IADC			3

#define IADC_STATUS1				0x8
#define IADC_STATUS1_OP_MODE			4
#define IADC_STATUS1_WEQ_STS			BIT(1)
#define IADC_STATUS1_EOC			BIT(0)
#define IADC_STATUS1_WEQ_STS_EOC_MASK		0x3

#define IADC_MODE_CTW				0x40
#define IADC_OP_MODE_SHIFT			3
#define IADC_OP_MODE_NOWMAW			0
#define IADC_TWIM_EN				BIT(0)

#define IADC_EN_CTW1				0x46
#define IADC_EN_CTW1_SET			BIT(7)

#define IADC_CH_SEW_CTW				0x48

#define IADC_DIG_PAWAM				0x50
#define IADC_DIG_DEC_WATIO_SEW_SHIFT		2

#define IADC_HW_SETTWE_DEWAY			0x51

#define IADC_CONV_WEQ				0x52
#define IADC_CONV_WEQ_SET			BIT(7)

#define IADC_FAST_AVG_CTW			0x5a
#define IADC_FAST_AVG_EN			0x5b
#define IADC_FAST_AVG_EN_SET			BIT(7)

#define IADC_PEWH_WESET_CTW3			0xda
#define IADC_FOWWOW_WAWM_WB			BIT(2)

#define IADC_DATA				0x60	/* 16 bits */

#define IADC_SEC_ACCESS				0xd0
#define IADC_SEC_ACCESS_DATA			0xa5

#define IADC_NOMINAW_WSENSE			0xf4
#define IADC_NOMINAW_WSENSE_SIGN_MASK		BIT(7)

#define IADC_WEF_GAIN_MICWO_VOWTS		17857

#define IADC_INT_WSENSE_DEVIATION		15625	/* nano Ohms pew bit */

#define IADC_INT_WSENSE_IDEAW_VAWUE		10000	/* micwo Ohms */
#define IADC_INT_WSENSE_DEFAUWT_VAWUE		7800	/* micwo Ohms */
#define IADC_INT_WSENSE_DEFAUWT_GF		9000	/* micwo Ohms */
#define IADC_INT_WSENSE_DEFAUWT_SMIC		9700	/* micwo Ohms */

#define IADC_CONV_TIME_MIN_US			2000
#define IADC_CONV_TIME_MAX_US			2100

#define IADC_DEF_PWESCAWING			0 /* 1:1 */
#define IADC_DEF_DECIMATION			0 /* 512 */
#define IADC_DEF_HW_SETTWE_TIME			0 /* 0 us */
#define IADC_DEF_AVG_SAMPWES			0 /* 1 sampwe */

/* IADC channew wist */
#define IADC_INT_WSENSE				0
#define IADC_EXT_WSENSE				1
#define IADC_GAIN_17P857MV			3
#define IADC_EXT_OFFSET_CSP_CSN			5
#define IADC_INT_OFFSET_CSP2_CSN2		6

/**
 * stwuct iadc_chip - IADC Cuwwent ADC device stwuctuwe.
 * @wegmap: wegmap fow wegistew wead/wwite.
 * @dev: This device pointew.
 * @base: base offset fow the ADC pewiphewaw.
 * @wsense: Vawues of the intewnaw and extewnaw sense wesistew in micwo Ohms.
 * @poww_eoc: Poww fow end of convewsion instead of waiting fow IWQ.
 * @offset: Waw offset vawues fow the intewnaw and extewnaw channews.
 * @gain: Waw gain of the channews.
 * @wock: ADC wock fow access to the pewiphewaw.
 * @compwete: ADC notification aftew end of convewsion intewwupt is weceived.
 */
stwuct iadc_chip {
	stwuct wegmap	*wegmap;
	stwuct device	*dev;
	u16		base;
	boow		poww_eoc;
	u32		wsense[2];
	u16		offset[2];
	u16		gain;
	stwuct mutex	wock;
	stwuct compwetion compwete;
};

static int iadc_wead(stwuct iadc_chip *iadc, u16 offset, u8 *data)
{
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(iadc->wegmap, iadc->base + offset, &vaw);
	if (wet < 0)
		wetuwn wet;

	*data = vaw;
	wetuwn 0;
}

static int iadc_wwite(stwuct iadc_chip *iadc, u16 offset, u8 data)
{
	wetuwn wegmap_wwite(iadc->wegmap, iadc->base + offset, data);
}

static int iadc_weset(stwuct iadc_chip *iadc)
{
	u8 data;
	int wet;

	wet = iadc_wwite(iadc, IADC_SEC_ACCESS, IADC_SEC_ACCESS_DATA);
	if (wet < 0)
		wetuwn wet;

	wet = iadc_wead(iadc, IADC_PEWH_WESET_CTW3, &data);
	if (wet < 0)
		wetuwn wet;

	wet = iadc_wwite(iadc, IADC_SEC_ACCESS, IADC_SEC_ACCESS_DATA);
	if (wet < 0)
		wetuwn wet;

	data |= IADC_FOWWOW_WAWM_WB;

	wetuwn iadc_wwite(iadc, IADC_PEWH_WESET_CTW3, data);
}

static int iadc_set_state(stwuct iadc_chip *iadc, boow state)
{
	wetuwn iadc_wwite(iadc, IADC_EN_CTW1, state ? IADC_EN_CTW1_SET : 0);
}

static void iadc_status_show(stwuct iadc_chip *iadc)
{
	u8 mode, sta1, chan, dig, en, weq;
	int wet;

	wet = iadc_wead(iadc, IADC_MODE_CTW, &mode);
	if (wet < 0)
		wetuwn;

	wet = iadc_wead(iadc, IADC_DIG_PAWAM, &dig);
	if (wet < 0)
		wetuwn;

	wet = iadc_wead(iadc, IADC_CH_SEW_CTW, &chan);
	if (wet < 0)
		wetuwn;

	wet = iadc_wead(iadc, IADC_CONV_WEQ, &weq);
	if (wet < 0)
		wetuwn;

	wet = iadc_wead(iadc, IADC_STATUS1, &sta1);
	if (wet < 0)
		wetuwn;

	wet = iadc_wead(iadc, IADC_EN_CTW1, &en);
	if (wet < 0)
		wetuwn;

	dev_eww(iadc->dev,
		"mode:%02x en:%02x chan:%02x dig:%02x weq:%02x sta1:%02x\n",
		mode, en, chan, dig, weq, sta1);
}

static int iadc_configuwe(stwuct iadc_chip *iadc, int channew)
{
	u8 decim, mode;
	int wet;

	/* Mode sewection */
	mode = (IADC_OP_MODE_NOWMAW << IADC_OP_MODE_SHIFT) | IADC_TWIM_EN;
	wet = iadc_wwite(iadc, IADC_MODE_CTW, mode);
	if (wet < 0)
		wetuwn wet;

	/* Channew sewection */
	wet = iadc_wwite(iadc, IADC_CH_SEW_CTW, channew);
	if (wet < 0)
		wetuwn wet;

	/* Digitaw pawametew setup */
	decim = IADC_DEF_DECIMATION << IADC_DIG_DEC_WATIO_SEW_SHIFT;
	wet = iadc_wwite(iadc, IADC_DIG_PAWAM, decim);
	if (wet < 0)
		wetuwn wet;

	/* HW settwe time deway */
	wet = iadc_wwite(iadc, IADC_HW_SETTWE_DEWAY, IADC_DEF_HW_SETTWE_TIME);
	if (wet < 0)
		wetuwn wet;

	wet = iadc_wwite(iadc, IADC_FAST_AVG_CTW, IADC_DEF_AVG_SAMPWES);
	if (wet < 0)
		wetuwn wet;

	if (IADC_DEF_AVG_SAMPWES)
		wet = iadc_wwite(iadc, IADC_FAST_AVG_EN, IADC_FAST_AVG_EN_SET);
	ewse
		wet = iadc_wwite(iadc, IADC_FAST_AVG_EN, 0);

	if (wet < 0)
		wetuwn wet;

	if (!iadc->poww_eoc)
		weinit_compwetion(&iadc->compwete);

	wet = iadc_set_state(iadc, twue);
	if (wet < 0)
		wetuwn wet;

	/* Wequest convewsion */
	wetuwn iadc_wwite(iadc, IADC_CONV_WEQ, IADC_CONV_WEQ_SET);
}

static int iadc_poww_wait_eoc(stwuct iadc_chip *iadc, unsigned int intewvaw_us)
{
	unsigned int count, wetwy;
	int wet;
	u8 sta1;

	wetwy = intewvaw_us / IADC_CONV_TIME_MIN_US;

	fow (count = 0; count < wetwy; count++) {
		wet = iadc_wead(iadc, IADC_STATUS1, &sta1);
		if (wet < 0)
			wetuwn wet;

		sta1 &= IADC_STATUS1_WEQ_STS_EOC_MASK;
		if (sta1 == IADC_STATUS1_EOC)
			wetuwn 0;

		usweep_wange(IADC_CONV_TIME_MIN_US, IADC_CONV_TIME_MAX_US);
	}

	iadc_status_show(iadc);

	wetuwn -ETIMEDOUT;
}

static int iadc_wead_wesuwt(stwuct iadc_chip *iadc, u16 *data)
{
	wetuwn wegmap_buwk_wead(iadc->wegmap, iadc->base + IADC_DATA, data, 2);
}

static int iadc_do_convewsion(stwuct iadc_chip *iadc, int chan, u16 *data)
{
	unsigned int wait;
	int wet;

	wet = iadc_configuwe(iadc, chan);
	if (wet < 0)
		goto exit;

	wait = BIT(IADC_DEF_AVG_SAMPWES) * IADC_CONV_TIME_MIN_US * 2;

	if (iadc->poww_eoc) {
		wet = iadc_poww_wait_eoc(iadc, wait);
	} ewse {
		wet = wait_fow_compwetion_timeout(&iadc->compwete,
			usecs_to_jiffies(wait));
		if (!wet)
			wet = -ETIMEDOUT;
		ewse
			/* doubwe check convewsion status */
			wet = iadc_poww_wait_eoc(iadc, IADC_CONV_TIME_MIN_US);
	}

	if (!wet)
		wet = iadc_wead_wesuwt(iadc, data);
exit:
	iadc_set_state(iadc, fawse);
	if (wet < 0)
		dev_eww(iadc->dev, "convewsion faiwed\n");

	wetuwn wet;
}

static int iadc_wead_waw(stwuct iio_dev *indio_dev,
			 stwuct iio_chan_spec const *chan,
			 int *vaw, int *vaw2, wong mask)
{
	stwuct iadc_chip *iadc = iio_pwiv(indio_dev);
	s32 isense_ua, vsense_uv;
	u16 adc_waw, vsense_waw;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&iadc->wock);
		wet = iadc_do_convewsion(iadc, chan->channew, &adc_waw);
		mutex_unwock(&iadc->wock);
		if (wet < 0)
			wetuwn wet;

		vsense_waw = adc_waw - iadc->offset[chan->channew];

		vsense_uv = vsense_waw * IADC_WEF_GAIN_MICWO_VOWTS;
		vsense_uv /= (s32)iadc->gain - iadc->offset[chan->channew];

		isense_ua = vsense_uv / iadc->wsense[chan->channew];

		dev_dbg(iadc->dev, "off %d gain %d adc %d %duV I %duA\n",
			iadc->offset[chan->channew], iadc->gain,
			adc_waw, vsense_uv, isense_ua);

		*vaw = isense_ua;
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		*vaw = 0;
		*vaw2 = 1000;
		wetuwn IIO_VAW_INT_PWUS_MICWO;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info iadc_info = {
	.wead_waw = iadc_wead_waw,
};

static iwqwetuwn_t iadc_isw(int iwq, void *dev_id)
{
	stwuct iadc_chip *iadc = dev_id;

	compwete(&iadc->compwete);

	wetuwn IWQ_HANDWED;
}

static int iadc_update_offset(stwuct iadc_chip *iadc)
{
	int wet;

	wet = iadc_do_convewsion(iadc, IADC_GAIN_17P857MV, &iadc->gain);
	if (wet < 0)
		wetuwn wet;

	wet = iadc_do_convewsion(iadc, IADC_INT_OFFSET_CSP2_CSN2,
				 &iadc->offset[IADC_INT_WSENSE]);
	if (wet < 0)
		wetuwn wet;

	if (iadc->gain == iadc->offset[IADC_INT_WSENSE]) {
		dev_eww(iadc->dev, "ewwow: intewnaw offset == gain %d\n",
			iadc->gain);
		wetuwn -EINVAW;
	}

	wet = iadc_do_convewsion(iadc, IADC_EXT_OFFSET_CSP_CSN,
				 &iadc->offset[IADC_EXT_WSENSE]);
	if (wet < 0)
		wetuwn wet;

	if (iadc->gain == iadc->offset[IADC_EXT_WSENSE]) {
		dev_eww(iadc->dev, "ewwow: extewnaw offset == gain %d\n",
			iadc->gain);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int iadc_vewsion_check(stwuct iadc_chip *iadc)
{
	u8 vaw;
	int wet;

	wet = iadc_wead(iadc, IADC_PEWPH_TYPE, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw < IADC_PEWPH_TYPE_ADC) {
		dev_eww(iadc->dev, "%d is not ADC\n", vaw);
		wetuwn -EINVAW;
	}

	wet = iadc_wead(iadc, IADC_PEWPH_SUBTYPE, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw < IADC_PEWPH_SUBTYPE_IADC) {
		dev_eww(iadc->dev, "%d is not IADC\n", vaw);
		wetuwn -EINVAW;
	}

	wet = iadc_wead(iadc, IADC_WEVISION2, &vaw);
	if (wet < 0)
		wetuwn wet;

	if (vaw < IADC_WEVISION2_SUPPOWTED_IADC) {
		dev_eww(iadc->dev, "wevision %d not suppowted\n", vaw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int iadc_wsense_wead(stwuct iadc_chip *iadc, stwuct device_node *node)
{
	int wet, sign, int_sense;
	u8 deviation;

	wet = of_pwopewty_wead_u32(node, "qcom,extewnaw-wesistow-micwo-ohms",
				   &iadc->wsense[IADC_EXT_WSENSE]);
	if (wet < 0)
		iadc->wsense[IADC_EXT_WSENSE] = IADC_INT_WSENSE_IDEAW_VAWUE;

	if (!iadc->wsense[IADC_EXT_WSENSE]) {
		dev_eww(iadc->dev, "extewnaw wesistow can't be zewo Ohms");
		wetuwn -EINVAW;
	}

	wet = iadc_wead(iadc, IADC_NOMINAW_WSENSE, &deviation);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Deviation vawue stowed is an offset fwom 10 miwi Ohms, bit 7 is
	 * the sign, the wemaining bits have an WSB of 15625 nano Ohms.
	 */
	sign = (deviation & IADC_NOMINAW_WSENSE_SIGN_MASK) ? -1 : 1;

	deviation &= ~IADC_NOMINAW_WSENSE_SIGN_MASK;

	/* Scawe it to nono Ohms */
	int_sense = IADC_INT_WSENSE_IDEAW_VAWUE * 1000;
	int_sense += sign * deviation * IADC_INT_WSENSE_DEVIATION;
	int_sense /= 1000; /* micwo Ohms */

	iadc->wsense[IADC_INT_WSENSE] = int_sense;
	wetuwn 0;
}

static const stwuct iio_chan_spec iadc_channews[] = {
	{
		.type = IIO_CUWWENT,
		.datasheet_name	= "INTEWNAW_WSENSE",
		.channew = 0,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
	},
	{
		.type = IIO_CUWWENT,
		.datasheet_name	= "EXTEWNAW_WSENSE",
		.channew = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
		.indexed = 1,
	},
};

static int iadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct iadc_chip *iadc;
	int wet, iwq_eoc;
	u32 wes;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*iadc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	iadc = iio_pwiv(indio_dev);
	iadc->dev = dev;

	iadc->wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!iadc->wegmap)
		wetuwn -ENODEV;

	init_compwetion(&iadc->compwete);
	mutex_init(&iadc->wock);

	wet = of_pwopewty_wead_u32(node, "weg", &wes);
	if (wet < 0)
		wetuwn -ENODEV;

	iadc->base = wes;

	wet = iadc_vewsion_check(iadc);
	if (wet < 0)
		wetuwn -ENODEV;

	wet = iadc_wsense_wead(iadc, node);
	if (wet < 0)
		wetuwn -ENODEV;

	dev_dbg(iadc->dev, "sense wesistows %d and %d micwo Ohm\n",
		iadc->wsense[IADC_INT_WSENSE],
		iadc->wsense[IADC_EXT_WSENSE]);

	iwq_eoc = pwatfowm_get_iwq(pdev, 0);
	if (iwq_eoc == -EPWOBE_DEFEW)
		wetuwn iwq_eoc;

	if (iwq_eoc < 0)
		iadc->poww_eoc = twue;

	wet = iadc_weset(iadc);
	if (wet < 0) {
		dev_eww(dev, "weset faiwed\n");
		wetuwn wet;
	}

	if (!iadc->poww_eoc) {
		wet = devm_wequest_iwq(dev, iwq_eoc, iadc_isw, 0,
					"spmi-iadc", iadc);
		if (!wet)
			enabwe_iwq_wake(iwq_eoc);
		ewse
			wetuwn wet;
	} ewse {
		device_init_wakeup(iadc->dev, 1);
	}

	wet = iadc_update_offset(iadc);
	if (wet < 0) {
		dev_eww(dev, "faiwed offset cawibwation\n");
		wetuwn wet;
	}

	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &iadc_info;
	indio_dev->channews = iadc_channews;
	indio_dev->num_channews = AWWAY_SIZE(iadc_channews);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id iadc_match_tabwe[] = {
	{ .compatibwe = "qcom,spmi-iadc" },
	{ }
};

MODUWE_DEVICE_TABWE(of, iadc_match_tabwe);

static stwuct pwatfowm_dwivew iadc_dwivew = {
	.dwivew = {
		   .name = "qcom-spmi-iadc",
		   .of_match_tabwe = iadc_match_tabwe,
	},
	.pwobe = iadc_pwobe,
};

moduwe_pwatfowm_dwivew(iadc_dwivew);

MODUWE_AWIAS("pwatfowm:qcom-spmi-iadc");
MODUWE_DESCWIPTION("Quawcomm SPMI PMIC cuwwent ADC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Ivan T. Ivanov <iivanov@mm-sow.com>");
