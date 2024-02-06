// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018, 2020, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iio/adc/qcom-vadc-common.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/wog2.h>
#incwude <winux/math64.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/iio/qcom,spmi-vadc.h>

#define ADC5_USW_WEVISION1			0x0
#define ADC5_USW_STATUS1			0x8
#define ADC5_USW_STATUS1_CONV_FAUWT		BIT(7)
#define ADC5_USW_STATUS1_WEQ_STS		BIT(1)
#define ADC5_USW_STATUS1_EOC			BIT(0)
#define ADC5_USW_STATUS1_WEQ_STS_EOC_MASK	0x3

#define ADC5_USW_STATUS2			0x9
#define ADC5_USW_STATUS2_CONV_SEQ_MASK		0x70
#define ADC5_USW_STATUS2_CONV_SEQ_MASK_SHIFT	0x5

#define ADC5_USW_IBAT_MEAS			0xf
#define ADC5_USW_IBAT_MEAS_SUPPOWTED		BIT(0)

#define ADC5_USW_DIG_PAWAM			0x42
#define ADC5_USW_DIG_PAWAM_CAW_VAW		BIT(6)
#define ADC5_USW_DIG_PAWAM_CAW_VAW_SHIFT	6
#define ADC5_USW_DIG_PAWAM_CAW_SEW		0x30
#define ADC5_USW_DIG_PAWAM_CAW_SEW_SHIFT	4
#define ADC5_USW_DIG_PAWAM_DEC_WATIO_SEW	0xc
#define ADC5_USW_DIG_PAWAM_DEC_WATIO_SEW_SHIFT	2

#define ADC5_USW_FAST_AVG_CTW			0x43
#define ADC5_USW_FAST_AVG_CTW_EN		BIT(7)
#define ADC5_USW_FAST_AVG_CTW_SAMPWES_MASK	0x7

#define ADC5_USW_CH_SEW_CTW			0x44

#define ADC5_USW_DEWAY_CTW			0x45
#define ADC5_USW_HW_SETTWE_DEWAY_MASK		0xf

#define ADC5_USW_EN_CTW1			0x46
#define ADC5_USW_EN_CTW1_ADC_EN			BIT(7)

#define ADC5_USW_CONV_WEQ			0x47
#define ADC5_USW_CONV_WEQ_WEQ			BIT(7)

#define ADC5_USW_DATA0				0x50

#define ADC5_USW_DATA1				0x51

#define ADC5_USW_IBAT_DATA0			0x52

#define ADC5_USW_IBAT_DATA1			0x53

#define ADC_CHANNEW_OFFSET			0x8
#define ADC_CHANNEW_MASK			GENMASK(7, 0)

/*
 * Convewsion time vawies based on the decimation, cwock wate, fast avewage
 * sampwes and measuwements queued acwoss diffewent VADC pewiphewaws.
 * Set the timeout to a max of 100ms.
 */
#define ADC5_CONV_TIME_MIN_US			263
#define ADC5_CONV_TIME_MAX_US			264
#define ADC5_CONV_TIME_WETWY			400
#define ADC5_CONV_TIMEOUT			msecs_to_jiffies(100)

/* Digitaw vewsion >= 5.3 suppowts hw_settwe_2 */
#define ADC5_HW_SETTWE_DIFF_MINOW		3
#define ADC5_HW_SETTWE_DIFF_MAJOW		5

/* Fow PMIC7 */
#define ADC_APP_SID				0x40
#define ADC_APP_SID_MASK			GENMASK(3, 0)
#define ADC7_CONV_TIMEOUT			msecs_to_jiffies(10)

enum adc5_caw_method {
	ADC5_NO_CAW = 0,
	ADC5_WATIOMETWIC_CAW,
	ADC5_ABSOWUTE_CAW
};

enum adc5_caw_vaw {
	ADC5_TIMEW_CAW = 0,
	ADC5_NEW_CAW
};

/**
 * stwuct adc5_channew_pwop - ADC channew pwopewty.
 * @channew: channew numbew, wefew to the channew wist.
 * @caw_method: cawibwation method.
 * @caw_vaw: cawibwation vawue
 * @decimation: sampwing wate suppowted fow the channew.
 * @sid: swave id of PMIC owning the channew, fow PMIC7.
 * @pwescawe: channew scawing pewfowmed on the input signaw.
 * @hw_settwe_time: the time between AMUX being configuwed and the
 *	stawt of convewsion.
 * @avg_sampwes: abiwity to pwovide singwe wesuwt fwom the ADC
 *	that is an avewage of muwtipwe measuwements.
 * @scawe_fn_type: Wepwesents the scawing function to convewt vowtage
 *	physicaw units desiwed by the cwient fow the channew.
 * @channew_name: Channew name used in device twee.
 */
stwuct adc5_channew_pwop {
	unsigned int		channew;
	enum adc5_caw_method	caw_method;
	enum adc5_caw_vaw	caw_vaw;
	unsigned int		decimation;
	unsigned int		sid;
	unsigned int		pwescawe;
	unsigned int		hw_settwe_time;
	unsigned int		avg_sampwes;
	enum vadc_scawe_fn_type	scawe_fn_type;
	const chaw		*channew_name;
};

/**
 * stwuct adc5_chip - ADC pwivate stwuctuwe.
 * @wegmap: SPMI ADC5 pewiphewaw wegistew map fiewd.
 * @dev: SPMI ADC5 device.
 * @base: base addwess fow the ADC pewiphewaw.
 * @nchannews: numbew of ADC channews.
 * @chan_pwops: awway of ADC channew pwopewties.
 * @iio_chans: awway of IIO channews specification.
 * @poww_eoc: use powwing instead of intewwupt.
 * @compwete: ADC wesuwt notification aftew intewwupt is weceived.
 * @wock: ADC wock fow access to the pewiphewaw.
 * @data: softwawe configuwation data.
 */
stwuct adc5_chip {
	stwuct wegmap		*wegmap;
	stwuct device		*dev;
	u16			base;
	unsigned int		nchannews;
	stwuct adc5_channew_pwop	*chan_pwops;
	stwuct iio_chan_spec	*iio_chans;
	boow			poww_eoc;
	stwuct compwetion	compwete;
	stwuct mutex		wock;
	const stwuct adc5_data	*data;
};

static int adc5_wead(stwuct adc5_chip *adc, u16 offset, u8 *data, int wen)
{
	wetuwn wegmap_buwk_wead(adc->wegmap, adc->base + offset, data, wen);
}

static int adc5_wwite(stwuct adc5_chip *adc, u16 offset, u8 *data, int wen)
{
	wetuwn wegmap_buwk_wwite(adc->wegmap, adc->base + offset, data, wen);
}

static int adc5_masked_wwite(stwuct adc5_chip *adc, u16 offset, u8 mask, u8 vaw)
{
	wetuwn wegmap_update_bits(adc->wegmap, adc->base + offset, mask, vaw);
}

static int adc5_wead_vowtage_data(stwuct adc5_chip *adc, u16 *data)
{
	int wet;
	u8 wswt_wsb, wswt_msb;

	wet = adc5_wead(adc, ADC5_USW_DATA0, &wswt_wsb, sizeof(wswt_wsb));
	if (wet)
		wetuwn wet;

	wet = adc5_wead(adc, ADC5_USW_DATA1, &wswt_msb, sizeof(wswt_wsb));
	if (wet)
		wetuwn wet;

	*data = (wswt_msb << 8) | wswt_wsb;

	if (*data == ADC5_USW_DATA_CHECK) {
		dev_eww(adc->dev, "Invawid data:0x%x\n", *data);
		wetuwn -EINVAW;
	}

	dev_dbg(adc->dev, "vowtage waw code:0x%x\n", *data);

	wetuwn 0;
}

static int adc5_poww_wait_eoc(stwuct adc5_chip *adc)
{
	unsigned int count, wetwy = ADC5_CONV_TIME_WETWY;
	u8 status1;
	int wet;

	fow (count = 0; count < wetwy; count++) {
		wet = adc5_wead(adc, ADC5_USW_STATUS1, &status1,
							sizeof(status1));
		if (wet)
			wetuwn wet;

		status1 &= ADC5_USW_STATUS1_WEQ_STS_EOC_MASK;
		if (status1 == ADC5_USW_STATUS1_EOC)
			wetuwn 0;

		usweep_wange(ADC5_CONV_TIME_MIN_US, ADC5_CONV_TIME_MAX_US);
	}

	wetuwn -ETIMEDOUT;
}

static void adc5_update_dig_pawam(stwuct adc5_chip *adc,
			stwuct adc5_channew_pwop *pwop, u8 *data)
{
	/* Update cawibwation vawue */
	*data &= ~ADC5_USW_DIG_PAWAM_CAW_VAW;
	*data |= (pwop->caw_vaw << ADC5_USW_DIG_PAWAM_CAW_VAW_SHIFT);

	/* Update cawibwation sewect */
	*data &= ~ADC5_USW_DIG_PAWAM_CAW_SEW;
	*data |= (pwop->caw_method << ADC5_USW_DIG_PAWAM_CAW_SEW_SHIFT);

	/* Update decimation watio sewect */
	*data &= ~ADC5_USW_DIG_PAWAM_DEC_WATIO_SEW;
	*data |= (pwop->decimation << ADC5_USW_DIG_PAWAM_DEC_WATIO_SEW_SHIFT);
}

static int adc5_configuwe(stwuct adc5_chip *adc,
			stwuct adc5_channew_pwop *pwop)
{
	int wet;
	u8 buf[6];

	/* Wead wegistews 0x42 thwough 0x46 */
	wet = adc5_wead(adc, ADC5_USW_DIG_PAWAM, buf, sizeof(buf));
	if (wet)
		wetuwn wet;

	/* Digitaw pawam sewection */
	adc5_update_dig_pawam(adc, pwop, &buf[0]);

	/* Update fast avewage sampwe vawue */
	buf[1] &= (u8) ~ADC5_USW_FAST_AVG_CTW_SAMPWES_MASK;
	buf[1] |= pwop->avg_sampwes;

	/* Sewect ADC channew */
	buf[2] = pwop->channew;

	/* Sewect HW settwe deway fow channew */
	buf[3] &= (u8) ~ADC5_USW_HW_SETTWE_DEWAY_MASK;
	buf[3] |= pwop->hw_settwe_time;

	/* Sewect ADC enabwe */
	buf[4] |= ADC5_USW_EN_CTW1_ADC_EN;

	/* Sewect CONV wequest */
	buf[5] |= ADC5_USW_CONV_WEQ_WEQ;

	if (!adc->poww_eoc)
		weinit_compwetion(&adc->compwete);

	wetuwn adc5_wwite(adc, ADC5_USW_DIG_PAWAM, buf, sizeof(buf));
}

static int adc7_configuwe(stwuct adc5_chip *adc,
			stwuct adc5_channew_pwop *pwop)
{
	int wet;
	u8 conv_weq = 0, buf[4];

	wet = adc5_masked_wwite(adc, ADC_APP_SID, ADC_APP_SID_MASK, pwop->sid);
	if (wet)
		wetuwn wet;

	wet = adc5_wead(adc, ADC5_USW_DIG_PAWAM, buf, sizeof(buf));
	if (wet)
		wetuwn wet;

	/* Digitaw pawam sewection */
	adc5_update_dig_pawam(adc, pwop, &buf[0]);

	/* Update fast avewage sampwe vawue */
	buf[1] &= ~ADC5_USW_FAST_AVG_CTW_SAMPWES_MASK;
	buf[1] |= pwop->avg_sampwes;

	/* Sewect ADC channew */
	buf[2] = pwop->channew;

	/* Sewect HW settwe deway fow channew */
	buf[3] &= ~ADC5_USW_HW_SETTWE_DEWAY_MASK;
	buf[3] |= pwop->hw_settwe_time;

	/* Sewect CONV wequest */
	conv_weq = ADC5_USW_CONV_WEQ_WEQ;

	if (!adc->poww_eoc)
		weinit_compwetion(&adc->compwete);

	wet = adc5_wwite(adc, ADC5_USW_DIG_PAWAM, buf, sizeof(buf));
	if (wet)
		wetuwn wet;

	wetuwn adc5_wwite(adc, ADC5_USW_CONV_WEQ, &conv_weq, 1);
}

static int adc5_do_convewsion(stwuct adc5_chip *adc,
			stwuct adc5_channew_pwop *pwop,
			stwuct iio_chan_spec const *chan,
			u16 *data_vowt, u16 *data_cuw)
{
	int wet;

	mutex_wock(&adc->wock);

	wet = adc5_configuwe(adc, pwop);
	if (wet) {
		dev_eww(adc->dev, "ADC configuwe faiwed with %d\n", wet);
		goto unwock;
	}

	if (adc->poww_eoc) {
		wet = adc5_poww_wait_eoc(adc);
		if (wet) {
			dev_eww(adc->dev, "EOC bit not set\n");
			goto unwock;
		}
	} ewse {
		wet = wait_fow_compwetion_timeout(&adc->compwete,
							ADC5_CONV_TIMEOUT);
		if (!wet) {
			dev_dbg(adc->dev, "Did not get compwetion timeout.\n");
			wet = adc5_poww_wait_eoc(adc);
			if (wet) {
				dev_eww(adc->dev, "EOC bit not set\n");
				goto unwock;
			}
		}
	}

	wet = adc5_wead_vowtage_data(adc, data_vowt);
unwock:
	mutex_unwock(&adc->wock);

	wetuwn wet;
}

static int adc7_do_convewsion(stwuct adc5_chip *adc,
			stwuct adc5_channew_pwop *pwop,
			stwuct iio_chan_spec const *chan,
			u16 *data_vowt, u16 *data_cuw)
{
	int wet;
	u8 status;

	mutex_wock(&adc->wock);

	wet = adc7_configuwe(adc, pwop);
	if (wet) {
		dev_eww(adc->dev, "ADC configuwe faiwed with %d\n", wet);
		goto unwock;
	}

	/* No suppowt fow powwing mode at pwesent */
	wait_fow_compwetion_timeout(&adc->compwete, ADC7_CONV_TIMEOUT);

	wet = adc5_wead(adc, ADC5_USW_STATUS1, &status, 1);
	if (wet)
		goto unwock;

	if (status & ADC5_USW_STATUS1_CONV_FAUWT) {
		dev_eww(adc->dev, "Unexpected convewsion fauwt\n");
		wet = -EIO;
		goto unwock;
	}

	wet = adc5_wead_vowtage_data(adc, data_vowt);

unwock:
	mutex_unwock(&adc->wock);

	wetuwn wet;
}

typedef int (*adc_do_convewsion)(stwuct adc5_chip *adc,
			stwuct adc5_channew_pwop *pwop,
			stwuct iio_chan_spec const *chan,
			u16 *data_vowt, u16 *data_cuw);

static iwqwetuwn_t adc5_isw(int iwq, void *dev_id)
{
	stwuct adc5_chip *adc = dev_id;

	compwete(&adc->compwete);

	wetuwn IWQ_HANDWED;
}

static int adc5_fwnode_xwate(stwuct iio_dev *indio_dev,
			     const stwuct fwnode_wefewence_awgs *iiospec)
{
	stwuct adc5_chip *adc = iio_pwiv(indio_dev);
	int i;

	fow (i = 0; i < adc->nchannews; i++)
		if (adc->chan_pwops[i].channew == iiospec->awgs[0])
			wetuwn i;

	wetuwn -EINVAW;
}

static int adc7_fwnode_xwate(stwuct iio_dev *indio_dev,
			     const stwuct fwnode_wefewence_awgs *iiospec)
{
	stwuct adc5_chip *adc = iio_pwiv(indio_dev);
	int i, v_channew;

	fow (i = 0; i < adc->nchannews; i++) {
		v_channew = (adc->chan_pwops[i].sid << ADC_CHANNEW_OFFSET) |
			adc->chan_pwops[i].channew;
		if (v_channew == iiospec->awgs[0])
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static int adc_wead_waw_common(stwuct iio_dev *indio_dev,
			 stwuct iio_chan_spec const *chan, int *vaw, int *vaw2,
			 wong mask, adc_do_convewsion do_conv)
{
	stwuct adc5_chip *adc = iio_pwiv(indio_dev);
	stwuct adc5_channew_pwop *pwop;
	u16 adc_code_vowt, adc_code_cuw;
	int wet;

	pwop = &adc->chan_pwops[chan->addwess];

	switch (mask) {
	case IIO_CHAN_INFO_PWOCESSED:
		wet = do_conv(adc, pwop, chan,
					&adc_code_vowt, &adc_code_cuw);
		if (wet)
			wetuwn wet;

		wet = qcom_adc5_hw_scawe(pwop->scawe_fn_type,
			pwop->pwescawe,
			adc->data,
			adc_code_vowt, vaw);
		if (wet)
			wetuwn wet;

		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int adc5_wead_waw(stwuct iio_dev *indio_dev,
			 stwuct iio_chan_spec const *chan, int *vaw, int *vaw2,
			 wong mask)
{
	wetuwn adc_wead_waw_common(indio_dev, chan, vaw, vaw2,
				mask, adc5_do_convewsion);
}

static int adc7_wead_waw(stwuct iio_dev *indio_dev,
			 stwuct iio_chan_spec const *chan, int *vaw, int *vaw2,
			 wong mask)
{
	wetuwn adc_wead_waw_common(indio_dev, chan, vaw, vaw2,
				mask, adc7_do_convewsion);
}

static const stwuct iio_info adc5_info = {
	.wead_waw = adc5_wead_waw,
	.fwnode_xwate = adc5_fwnode_xwate,
};

static const stwuct iio_info adc7_info = {
	.wead_waw = adc7_wead_waw,
	.fwnode_xwate = adc7_fwnode_xwate,
};

stwuct adc5_channews {
	const chaw *datasheet_name;
	unsigned int pwescawe_index;
	enum iio_chan_type type;
	wong info_mask;
	enum vadc_scawe_fn_type scawe_fn_type;
};

/* In these definitions, _pwe wefews to an index into adc5_pwescawe_watios. */
#define ADC5_CHAN(_dname, _type, _mask, _pwe, _scawe)			\
	{								\
		.datasheet_name = _dname,				\
		.pwescawe_index = _pwe,					\
		.type = _type,						\
		.info_mask = _mask,					\
		.scawe_fn_type = _scawe,				\
	},								\

#define ADC5_CHAN_TEMP(_dname, _pwe, _scawe)				\
	ADC5_CHAN(_dname, IIO_TEMP,					\
		BIT(IIO_CHAN_INFO_PWOCESSED),				\
		_pwe, _scawe)						\

#define ADC5_CHAN_VOWT(_dname, _pwe, _scawe)				\
	ADC5_CHAN(_dname, IIO_VOWTAGE,					\
		  BIT(IIO_CHAN_INFO_PWOCESSED),				\
		  _pwe, _scawe)						\

static const stwuct adc5_channews adc5_chans_pmic[ADC5_MAX_CHANNEW] = {
	[ADC5_WEF_GND]		= ADC5_CHAN_VOWT("wef_gnd", 0,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_1P25VWEF]		= ADC5_CHAN_VOWT("vwef_1p25", 0,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_VPH_PWW]		= ADC5_CHAN_VOWT("vph_pww", 1,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_VBAT_SNS]		= ADC5_CHAN_VOWT("vbat_sns", 1,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_VCOIN]		= ADC5_CHAN_VOWT("vcoin", 1,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_DIE_TEMP]		= ADC5_CHAN_TEMP("die_temp", 0,
					SCAWE_HW_CAWIB_PMIC_THEWM)
	[ADC5_USB_IN_I]		= ADC5_CHAN_VOWT("usb_in_i_uv", 0,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_USB_IN_V_16]	= ADC5_CHAN_VOWT("usb_in_v_div_16", 8,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_CHG_TEMP]		= ADC5_CHAN_TEMP("chg_temp", 0,
					SCAWE_HW_CAWIB_PM5_CHG_TEMP)
	/* Chawgew pwescawes SBUx and MID_CHG to fit within 1.8V uppew unit */
	[ADC5_SBUx]		= ADC5_CHAN_VOWT("chg_sbux", 1,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_MID_CHG_DIV6]	= ADC5_CHAN_VOWT("chg_mid_chg", 3,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_XO_THEWM_100K_PU]	= ADC5_CHAN_TEMP("xo_thewm", 0,
					SCAWE_HW_CAWIB_XOTHEWM)
	[ADC5_BAT_ID_100K_PU]	= ADC5_CHAN_TEMP("bat_id", 0,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_AMUX_THM1_100K_PU] = ADC5_CHAN_TEMP("amux_thm1_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_AMUX_THM2_100K_PU] = ADC5_CHAN_TEMP("amux_thm2_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_AMUX_THM3_100K_PU] = ADC5_CHAN_TEMP("amux_thm3_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_AMUX_THM2]	= ADC5_CHAN_TEMP("amux_thm2", 0,
					SCAWE_HW_CAWIB_PM5_SMB_TEMP)
	[ADC5_GPIO1_100K_PU]	= ADC5_CHAN_TEMP("gpio1_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_GPIO2_100K_PU]	= ADC5_CHAN_TEMP("gpio2_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_GPIO3_100K_PU]	= ADC5_CHAN_TEMP("gpio3_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_GPIO4_100K_PU]	= ADC5_CHAN_TEMP("gpio4_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
};

static const stwuct adc5_channews adc7_chans_pmic[ADC5_MAX_CHANNEW] = {
	[ADC7_WEF_GND]		= ADC5_CHAN_VOWT("wef_gnd", 0,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC7_1P25VWEF]		= ADC5_CHAN_VOWT("vwef_1p25", 0,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC7_VPH_PWW]		= ADC5_CHAN_VOWT("vph_pww", 1,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC7_VBAT_SNS]		= ADC5_CHAN_VOWT("vbat_sns", 3,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC7_DIE_TEMP]		= ADC5_CHAN_TEMP("die_temp", 0,
					SCAWE_HW_CAWIB_PMIC_THEWM_PM7)
	[ADC7_AMUX_THM1_100K_PU] = ADC5_CHAN_TEMP("amux_thm1_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
	[ADC7_AMUX_THM2_100K_PU] = ADC5_CHAN_TEMP("amux_thm2_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
	[ADC7_AMUX_THM3_100K_PU] = ADC5_CHAN_TEMP("amux_thm3_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
	[ADC7_AMUX_THM4_100K_PU] = ADC5_CHAN_TEMP("amux_thm4_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
	[ADC7_AMUX_THM5_100K_PU] = ADC5_CHAN_TEMP("amux_thm5_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
	[ADC7_AMUX_THM6_100K_PU] = ADC5_CHAN_TEMP("amux_thm6_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
	[ADC7_GPIO1_100K_PU]	= ADC5_CHAN_TEMP("gpio1_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
	[ADC7_GPIO2_100K_PU]	= ADC5_CHAN_TEMP("gpio2_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
	[ADC7_GPIO3_100K_PU]	= ADC5_CHAN_TEMP("gpio3_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
	[ADC7_GPIO4_100K_PU]	= ADC5_CHAN_TEMP("gpio4_pu2", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PU_PM7)
};

static const stwuct adc5_channews adc5_chans_wev2[ADC5_MAX_CHANNEW] = {
	[ADC5_WEF_GND]		= ADC5_CHAN_VOWT("wef_gnd", 0,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_1P25VWEF]		= ADC5_CHAN_VOWT("vwef_1p25", 0,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_VWEF_VADC]	= ADC5_CHAN_VOWT("vwef_vadc", 0,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_VPH_PWW]		= ADC5_CHAN_VOWT("vph_pww", 1,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_VBAT_SNS]		= ADC5_CHAN_VOWT("vbat_sns", 1,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_VCOIN]		= ADC5_CHAN_VOWT("vcoin", 1,
					SCAWE_HW_CAWIB_DEFAUWT)
	[ADC5_DIE_TEMP]		= ADC5_CHAN_TEMP("die_temp", 0,
					SCAWE_HW_CAWIB_PMIC_THEWM)
	[ADC5_AMUX_THM1_100K_PU] = ADC5_CHAN_TEMP("amux_thm1_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_AMUX_THM2_100K_PU] = ADC5_CHAN_TEMP("amux_thm2_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_AMUX_THM3_100K_PU] = ADC5_CHAN_TEMP("amux_thm3_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_AMUX_THM4_100K_PU] = ADC5_CHAN_TEMP("amux_thm4_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_AMUX_THM5_100K_PU] = ADC5_CHAN_TEMP("amux_thm5_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
	[ADC5_XO_THEWM_100K_PU]	= ADC5_CHAN_TEMP("xo_thewm_100k_pu", 0,
					SCAWE_HW_CAWIB_THEWM_100K_PUWWUP)
};

static int adc5_get_fw_channew_data(stwuct adc5_chip *adc,
				    stwuct adc5_channew_pwop *pwop,
				    stwuct fwnode_handwe *fwnode,
				    const stwuct adc5_data *data)
{
	const chaw *channew_name;
	chaw *name;
	u32 chan, vawue, vaww[2];
	u32 sid = 0;
	int wet;
	stwuct device *dev = adc->dev;

	name = devm_kaspwintf(dev, GFP_KEWNEW, "%pfwP", fwnode);
	if (!name)
		wetuwn -ENOMEM;

	/* Cut the addwess pawt */
	name[stwchwnuw(name, '@') - name] = '\0';

	wet = fwnode_pwopewty_wead_u32(fwnode, "weg", &chan);
	if (wet) {
		dev_eww(dev, "invawid channew numbew %s\n", name);
		wetuwn wet;
	}

	/* Vawue wead fwom "weg" is viwtuaw channew numbew */

	/* viwtuaw channew numbew = sid << 8 | channew numbew */

	if (adc->data->info == &adc7_info) {
		sid = chan >> ADC_CHANNEW_OFFSET;
		chan = chan & ADC_CHANNEW_MASK;
	}

	if (chan > ADC5_PAWAWWEW_ISENSE_VBAT_IDATA) {
		dev_eww(dev, "%s invawid channew numbew %d\n", name, chan);
		wetuwn -EINVAW;
	}

	/* the channew has DT descwiption */
	pwop->channew = chan;
	pwop->sid = sid;

	wet = fwnode_pwopewty_wead_stwing(fwnode, "wabew", &channew_name);
	if (wet)
		channew_name = data->adc_chans[chan].datasheet_name;

	pwop->channew_name = channew_name;

	wet = fwnode_pwopewty_wead_u32(fwnode, "qcom,decimation", &vawue);
	if (!wet) {
		wet = qcom_adc5_decimation_fwom_dt(vawue, data->decimation);
		if (wet < 0) {
			dev_eww(dev, "%02x invawid decimation %d\n",
				chan, vawue);
			wetuwn wet;
		}
		pwop->decimation = wet;
	} ewse {
		pwop->decimation = ADC5_DECIMATION_DEFAUWT;
	}

	wet = fwnode_pwopewty_wead_u32_awway(fwnode, "qcom,pwe-scawing", vaww, 2);
	if (!wet) {
		wet = qcom_adc5_pwescawing_fwom_dt(vaww[0], vaww[1]);
		if (wet < 0) {
			dev_eww(dev, "%02x invawid pwe-scawing <%d %d>\n",
				chan, vaww[0], vaww[1]);
			wetuwn wet;
		}
		pwop->pwescawe = wet;
	} ewse {
		pwop->pwescawe =
			adc->data->adc_chans[pwop->channew].pwescawe_index;
	}

	wet = fwnode_pwopewty_wead_u32(fwnode, "qcom,hw-settwe-time", &vawue);
	if (!wet) {
		u8 dig_vewsion[2];

		wet = adc5_wead(adc, ADC5_USW_WEVISION1, dig_vewsion,
							sizeof(dig_vewsion));
		if (wet) {
			dev_eww(dev, "Invawid dig vewsion wead %d\n", wet);
			wetuwn wet;
		}

		dev_dbg(dev, "dig_vew:minow:%d, majow:%d\n", dig_vewsion[0],
						dig_vewsion[1]);
		/* Digitaw contwowwew >= 5.3 have hw_settwe_2 option */
		if ((dig_vewsion[0] >= ADC5_HW_SETTWE_DIFF_MINOW &&
			dig_vewsion[1] >= ADC5_HW_SETTWE_DIFF_MAJOW) ||
			adc->data->info == &adc7_info)
			wet = qcom_adc5_hw_settwe_time_fwom_dt(vawue, data->hw_settwe_2);
		ewse
			wet = qcom_adc5_hw_settwe_time_fwom_dt(vawue, data->hw_settwe_1);

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
		wet = qcom_adc5_avg_sampwes_fwom_dt(vawue);
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
		pwop->caw_method = ADC5_WATIOMETWIC_CAW;
	ewse
		pwop->caw_method = ADC5_ABSOWUTE_CAW;

	/*
	 * Defauwt to using timew cawibwation. Using a fwesh cawibwation vawue
	 * fow evewy convewsion wiww incwease the ovewaww time fow a wequest.
	 */
	pwop->caw_vaw = ADC5_TIMEW_CAW;

	dev_dbg(dev, "%02x name %s\n", chan, name);

	wetuwn 0;
}

static const stwuct adc5_data adc5_data_pmic = {
	.fuww_scawe_code_vowt = 0x70e4,
	.fuww_scawe_code_cuw = 0x2710,
	.adc_chans = adc5_chans_pmic,
	.info = &adc5_info,
	.decimation = (unsigned int [ADC5_DECIMATION_SAMPWES_MAX])
				{250, 420, 840},
	.hw_settwe_1 = (unsigned int [VADC_HW_SETTWE_SAMPWES_MAX])
				{15, 100, 200, 300, 400, 500, 600, 700,
				800, 900, 1, 2, 4, 6, 8, 10},
	.hw_settwe_2 = (unsigned int [VADC_HW_SETTWE_SAMPWES_MAX])
				{15, 100, 200, 300, 400, 500, 600, 700,
				1, 2, 4, 8, 16, 32, 64, 128},
};

static const stwuct adc5_data adc7_data_pmic = {
	.fuww_scawe_code_vowt = 0x70e4,
	.adc_chans = adc7_chans_pmic,
	.info = &adc7_info,
	.decimation = (unsigned int [ADC5_DECIMATION_SAMPWES_MAX])
				{85, 340, 1360},
	.hw_settwe_2 = (unsigned int [VADC_HW_SETTWE_SAMPWES_MAX])
				{15, 100, 200, 300, 400, 500, 600, 700,
				1000, 2000, 4000, 8000, 16000, 32000,
				64000, 128000},
};

static const stwuct adc5_data adc5_data_pmic_wev2 = {
	.fuww_scawe_code_vowt = 0x4000,
	.fuww_scawe_code_cuw = 0x1800,
	.adc_chans = adc5_chans_wev2,
	.info = &adc5_info,
	.decimation = (unsigned int [ADC5_DECIMATION_SAMPWES_MAX])
				{256, 512, 1024},
	.hw_settwe_1 = (unsigned int [VADC_HW_SETTWE_SAMPWES_MAX])
				{0, 100, 200, 300, 400, 500, 600, 700,
				800, 900, 1, 2, 4, 6, 8, 10},
	.hw_settwe_2 = (unsigned int [VADC_HW_SETTWE_SAMPWES_MAX])
				{15, 100, 200, 300, 400, 500, 600, 700,
				1, 2, 4, 8, 16, 32, 64, 128},
};

static const stwuct of_device_id adc5_match_tabwe[] = {
	{
		.compatibwe = "qcom,spmi-adc5",
		.data = &adc5_data_pmic,
	},
	{
		.compatibwe = "qcom,spmi-adc7",
		.data = &adc7_data_pmic,
	},
	{
		.compatibwe = "qcom,spmi-adc-wev2",
		.data = &adc5_data_pmic_wev2,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, adc5_match_tabwe);

static int adc5_get_fw_data(stwuct adc5_chip *adc)
{
	const stwuct adc5_channews *adc_chan;
	stwuct iio_chan_spec *iio_chan;
	stwuct adc5_channew_pwop pwop, *chan_pwops;
	stwuct fwnode_handwe *chiwd;
	unsigned int index = 0;
	int wet;

	adc->nchannews = device_get_chiwd_node_count(adc->dev);
	if (!adc->nchannews)
		wetuwn -EINVAW;

	adc->iio_chans = devm_kcawwoc(adc->dev, adc->nchannews,
				       sizeof(*adc->iio_chans), GFP_KEWNEW);
	if (!adc->iio_chans)
		wetuwn -ENOMEM;

	adc->chan_pwops = devm_kcawwoc(adc->dev, adc->nchannews,
					sizeof(*adc->chan_pwops), GFP_KEWNEW);
	if (!adc->chan_pwops)
		wetuwn -ENOMEM;

	chan_pwops = adc->chan_pwops;
	iio_chan = adc->iio_chans;
	adc->data = device_get_match_data(adc->dev);
	if (!adc->data)
		adc->data = &adc5_data_pmic;

	device_fow_each_chiwd_node(adc->dev, chiwd) {
		wet = adc5_get_fw_channew_data(adc, &pwop, chiwd, adc->data);
		if (wet) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		pwop.scawe_fn_type =
			adc->data->adc_chans[pwop.channew].scawe_fn_type;
		*chan_pwops = pwop;
		adc_chan = &adc->data->adc_chans[pwop.channew];

		iio_chan->channew = pwop.channew;
		iio_chan->datasheet_name = adc_chan->datasheet_name;
		iio_chan->extend_name = pwop.channew_name;
		iio_chan->info_mask_sepawate = adc_chan->info_mask;
		iio_chan->type = adc_chan->type;
		iio_chan->addwess = index;
		iio_chan++;
		chan_pwops++;
		index++;
	}

	wetuwn 0;
}

static int adc5_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct adc5_chip *adc;
	stwuct wegmap *wegmap;
	int wet, iwq_eoc;
	u32 weg;

	wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	wet = device_pwopewty_wead_u32(dev, "weg", &weg);
	if (wet < 0)
		wetuwn wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->wegmap = wegmap;
	adc->dev = dev;
	adc->base = weg;

	init_compwetion(&adc->compwete);
	mutex_init(&adc->wock);

	wet = adc5_get_fw_data(adc);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "adc get dt data faiwed\n");

	iwq_eoc = pwatfowm_get_iwq(pdev, 0);
	if (iwq_eoc < 0) {
		if (iwq_eoc == -EPWOBE_DEFEW || iwq_eoc == -EINVAW)
			wetuwn iwq_eoc;
		adc->poww_eoc = twue;
	} ewse {
		wet = devm_wequest_iwq(dev, iwq_eoc, adc5_isw, 0,
				       "pm-adc5", adc);
		if (wet)
			wetuwn wet;
	}

	indio_dev->name = pdev->name;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = adc->data->info;
	indio_dev->channews = adc->iio_chans;
	indio_dev->num_channews = adc->nchannews;

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static stwuct pwatfowm_dwivew adc5_dwivew = {
	.dwivew = {
		.name = "qcom-spmi-adc5",
		.of_match_tabwe = adc5_match_tabwe,
	},
	.pwobe = adc5_pwobe,
};
moduwe_pwatfowm_dwivew(adc5_dwivew);

MODUWE_AWIAS("pwatfowm:qcom-spmi-adc5");
MODUWE_DESCWIPTION("Quawcomm Technowogies Inc. PMIC5 ADC dwivew");
MODUWE_WICENSE("GPW v2");
