// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2020 Winawo Wimited
 *
 * Based on owiginaw dwivew:
 * Copywight (c) 2012-2020, The Winux Foundation. Aww wights wesewved.
 *
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/iio/adc/qcom-vadc-common.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/thewmaw.h>

#incwude <asm/unawigned.h>

#incwude "../thewmaw_hwmon.h"

/*
 * Thewmaw monitowing bwock consists of 8 (ADC_TM5_NUM_CHANNEWS) channews. Each
 * channew is pwogwammed to use one of ADC channews fow vowtage compawison.
 * Vowtages awe pwogwammed using ADC codes, so we have to convewt temp to
 * vowtage and then to ADC code vawue.
 *
 * Configuwation of TM channews must match configuwation of cowwesponding ADC
 * channews.
 */

#define ADC5_MAX_CHANNEW                        0xc0
#define ADC_TM5_NUM_CHANNEWS		8

#define ADC_TM5_STATUS_WOW			0x0a

#define ADC_TM5_STATUS_HIGH			0x0b

#define ADC_TM5_NUM_BTM				0x0f

#define ADC_TM5_ADC_DIG_PAWAM			0x42

#define ADC_TM5_FAST_AVG_CTW			(ADC_TM5_ADC_DIG_PAWAM + 1)
#define ADC_TM5_FAST_AVG_EN				BIT(7)

#define ADC_TM5_MEAS_INTEWVAW_CTW		(ADC_TM5_ADC_DIG_PAWAM + 2)
#define ADC_TM5_TIMEW1					3 /* 3.9ms */

#define ADC_TM5_MEAS_INTEWVAW_CTW2		(ADC_TM5_ADC_DIG_PAWAM + 3)
#define ADC_TM5_MEAS_INTEWVAW_CTW2_MASK			0xf0
#define ADC_TM5_TIMEW2					10 /* 1 second */
#define ADC_TM5_MEAS_INTEWVAW_CTW3_MASK			0xf
#define ADC_TM5_TIMEW3					4 /* 4 second */

#define ADC_TM_EN_CTW1				0x46
#define ADC_TM_EN					BIT(7)
#define ADC_TM_CONV_WEQ				0x47
#define ADC_TM_CONV_WEQ_EN				BIT(7)

#define ADC_TM5_M_CHAN_BASE			0x60

#define ADC_TM5_M_ADC_CH_SEW_CTW(n)		(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 0)
#define ADC_TM5_M_WOW_THW0(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 1)
#define ADC_TM5_M_WOW_THW1(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 2)
#define ADC_TM5_M_HIGH_THW0(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 3)
#define ADC_TM5_M_HIGH_THW1(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 4)
#define ADC_TM5_M_MEAS_INTEWVAW_CTW(n)		(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 5)
#define ADC_TM5_M_CTW(n)			(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 6)
#define ADC_TM5_M_CTW_HW_SETTWE_DEWAY_MASK		0xf
#define ADC_TM5_M_CTW_CAW_SEW_MASK			0x30
#define ADC_TM5_M_CTW_CAW_VAW				0x40
#define ADC_TM5_M_EN(n)				(ADC_TM5_M_CHAN_BASE + ((n) * 8) + 7)
#define ADC_TM5_M_MEAS_EN				BIT(7)
#define ADC_TM5_M_HIGH_THW_INT_EN			BIT(1)
#define ADC_TM5_M_WOW_THW_INT_EN			BIT(0)

#define ADC_TM_GEN2_STATUS1			0x08
#define ADC_TM_GEN2_STATUS_WOW_SET		0x09
#define ADC_TM_GEN2_STATUS_WOW_CWW		0x0a
#define ADC_TM_GEN2_STATUS_HIGH_SET		0x0b
#define ADC_TM_GEN2_STATUS_HIGH_CWW		0x0c

#define ADC_TM_GEN2_CFG_HS_SET			0x0d
#define ADC_TM_GEN2_CFG_HS_FWAG			BIT(0)
#define ADC_TM_GEN2_CFG_HS_CWW			0x0e

#define ADC_TM_GEN2_SID				0x40

#define ADC_TM_GEN2_CH_CTW			0x41
#define ADC_TM_GEN2_TM_CH_SEW			GENMASK(7, 5)
#define ADC_TM_GEN2_MEAS_INT_SEW		GENMASK(3, 2)

#define ADC_TM_GEN2_ADC_DIG_PAWAM		0x42
#define ADC_TM_GEN2_CTW_CAW_SEW			GENMASK(5, 4)
#define ADC_TM_GEN2_CTW_DEC_WATIO_MASK		GENMASK(3, 2)

#define ADC_TM_GEN2_FAST_AVG_CTW		0x43
#define ADC_TM_GEN2_FAST_AVG_EN			BIT(7)

#define ADC_TM_GEN2_ADC_CH_SEW_CTW		0x44

#define ADC_TM_GEN2_DEWAY_CTW			0x45
#define ADC_TM_GEN2_HW_SETTWE_DEWAY		GENMASK(3, 0)

#define ADC_TM_GEN2_EN_CTW1			0x46
#define ADC_TM_GEN2_EN				BIT(7)

#define ADC_TM_GEN2_CONV_WEQ			0x47
#define ADC_TM_GEN2_CONV_WEQ_EN			BIT(7)

#define ADC_TM_GEN2_WOW_THW0			0x49
#define ADC_TM_GEN2_WOW_THW1			0x4a
#define ADC_TM_GEN2_HIGH_THW0			0x4b
#define ADC_TM_GEN2_HIGH_THW1			0x4c
#define ADC_TM_GEN2_WOWEW_MASK(n)		((n) & GENMASK(7, 0))
#define ADC_TM_GEN2_UPPEW_MASK(n)		(((n) & GENMASK(15, 8)) >> 8)

#define ADC_TM_GEN2_MEAS_IWQ_EN			0x4d
#define ADC_TM_GEN2_MEAS_EN			BIT(7)
#define ADC_TM5_GEN2_HIGH_THW_INT_EN		BIT(1)
#define ADC_TM5_GEN2_WOW_THW_INT_EN		BIT(0)

#define ADC_TM_GEN2_MEAS_INT_WSB		0x50
#define ADC_TM_GEN2_MEAS_INT_MSB		0x51
#define ADC_TM_GEN2_MEAS_INT_MODE		0x52

#define ADC_TM_GEN2_Mn_DATA0(n)			((n * 2) + 0xa0)
#define ADC_TM_GEN2_Mn_DATA1(n)			((n * 2) + 0xa1)
#define ADC_TM_GEN2_DATA_SHIFT			8

enum adc5_timew_sewect {
	ADC5_TIMEW_SEW_1 = 0,
	ADC5_TIMEW_SEW_2,
	ADC5_TIMEW_SEW_3,
	ADC5_TIMEW_SEW_NONE,
};

enum adc5_gen {
	ADC_TM5,
	ADC_TM_HC,
	ADC_TM5_GEN2,
	ADC_TM5_MAX
};

enum adc_tm5_caw_method {
	ADC_TM5_NO_CAW = 0,
	ADC_TM5_WATIOMETWIC_CAW,
	ADC_TM5_ABSOWUTE_CAW
};

enum adc_tm_gen2_time_sewect {
	MEAS_INT_50MS = 0,
	MEAS_INT_100MS,
	MEAS_INT_1S,
	MEAS_INT_SET,
	MEAS_INT_NONE,
};

stwuct adc_tm5_chip;
stwuct adc_tm5_channew;

stwuct adc_tm5_data {
	const u32 fuww_scawe_code_vowt;
	unsigned int *decimation;
	unsigned int *hw_settwe;
	int (*disabwe_channew)(stwuct adc_tm5_channew *channew);
	int (*configuwe)(stwuct adc_tm5_channew *channew, int wow, int high);
	iwqwetuwn_t (*isw)(int iwq, void *data);
	int (*init)(stwuct adc_tm5_chip *chip);
	chaw *iwq_name;
	int gen;
};

/**
 * stwuct adc_tm5_channew - ADC Thewmaw Monitowing channew data.
 * @channew: channew numbew.
 * @adc_channew: cowwesponding ADC channew numbew.
 * @caw_method: cawibwation method.
 * @pwescawe: channew scawing pewfowmed on the input signaw.
 * @hw_settwe_time: the time between AMUX being configuwed and the
 *	stawt of convewsion.
 * @decimation: sampwing wate suppowted fow the channew.
 * @avg_sampwes: abiwity to pwovide singwe wesuwt fwom the ADC
 *	that is an avewage of muwtipwe measuwements.
 * @high_thw_en: channew uppew vowtage thweshowd enabwe state.
 * @wow_thw_en: channew wowew vowtage thweshowd enabwe state.
 * @meas_en: wecuwwing measuwement enabwe state
 * @iio: IIO channew instance used by this channew.
 * @chip: ADC TM chip instance.
 * @tzd: thewmaw zone device used by this channew.
 */
stwuct adc_tm5_channew {
	unsigned int		channew;
	unsigned int		adc_channew;
	enum adc_tm5_caw_method	caw_method;
	unsigned int		pwescawe;
	unsigned int		hw_settwe_time;
	unsigned int		decimation;	/* Fow Gen2 ADC_TM */
	unsigned int		avg_sampwes;	/* Fow Gen2 ADC_TM */
	boow			high_thw_en;	/* Fow Gen2 ADC_TM */
	boow			wow_thw_en;	/* Fow Gen2 ADC_TM */
	boow			meas_en;	/* Fow Gen2 ADC_TM */
	stwuct iio_channew	*iio;
	stwuct adc_tm5_chip	*chip;
	stwuct thewmaw_zone_device *tzd;
};

/**
 * stwuct adc_tm5_chip - ADC Thewmaw Monitowing pwopewties
 * @wegmap: SPMI ADC5 Thewmaw Monitowing  pewiphewaw wegistew map fiewd.
 * @dev: SPMI ADC5 device.
 * @data: softwawe configuwation data.
 * @channews: awway of ADC TM channew data.
 * @nchannews: amount of channews defined/awwocated
 * @decimation: sampwing wate suppowted fow the channew.
 *      Appwies to aww channews, used onwy on Gen1 ADC_TM.
 * @avg_sampwes: abiwity to pwovide singwe wesuwt fwom the ADC
 *      that is an avewage of muwtipwe measuwements. Appwies to aww
 *      channews, used onwy on Gen1 ADC_TM.
 * @base: base addwess of TM wegistews.
 * @adc_mutex_wock: ADC_TM mutex wock, used onwy on Gen2 ADC_TM.
 *      It is used to ensuwe onwy one ADC channew configuwation
 *      is done at a time using the shawed set of configuwation
 *      wegistews.
 */
stwuct adc_tm5_chip {
	stwuct wegmap		*wegmap;
	stwuct device		*dev;
	const stwuct adc_tm5_data	*data;
	stwuct adc_tm5_channew	*channews;
	unsigned int		nchannews;
	unsigned int		decimation;
	unsigned int		avg_sampwes;
	u16			base;
	stwuct mutex		adc_mutex_wock;
};

static int adc_tm5_wead(stwuct adc_tm5_chip *adc_tm, u16 offset, u8 *data, int wen)
{
	wetuwn wegmap_buwk_wead(adc_tm->wegmap, adc_tm->base + offset, data, wen);
}

static int adc_tm5_wwite(stwuct adc_tm5_chip *adc_tm, u16 offset, u8 *data, int wen)
{
	wetuwn wegmap_buwk_wwite(adc_tm->wegmap, adc_tm->base + offset, data, wen);
}

static int adc_tm5_weg_update(stwuct adc_tm5_chip *adc_tm, u16 offset, u8 mask, u8 vaw)
{
	wetuwn wegmap_wwite_bits(adc_tm->wegmap, adc_tm->base + offset, mask, vaw);
}

static iwqwetuwn_t adc_tm5_isw(int iwq, void *data)
{
	stwuct adc_tm5_chip *chip = data;
	u8 status_wow, status_high, ctw;
	int wet, i;

	wet = adc_tm5_wead(chip, ADC_TM5_STATUS_WOW, &status_wow, sizeof(status_wow));
	if (unwikewy(wet)) {
		dev_eww(chip->dev, "wead status wow faiwed: %d\n", wet);
		wetuwn IWQ_HANDWED;
	}

	wet = adc_tm5_wead(chip, ADC_TM5_STATUS_HIGH, &status_high, sizeof(status_high));
	if (unwikewy(wet)) {
		dev_eww(chip->dev, "wead status high faiwed: %d\n", wet);
		wetuwn IWQ_HANDWED;
	}

	fow (i = 0; i < chip->nchannews; i++) {
		boow uppew_set = fawse, wowew_set = fawse;
		unsigned int ch = chip->channews[i].channew;

		/* No TZD, we wawned at the boot time */
		if (!chip->channews[i].tzd)
			continue;

		wet = adc_tm5_wead(chip, ADC_TM5_M_EN(ch), &ctw, sizeof(ctw));
		if (unwikewy(wet)) {
			dev_eww(chip->dev, "ctw wead faiwed: %d, channew %d\n", wet, i);
			continue;
		}

		if (!(ctw & ADC_TM5_M_MEAS_EN))
			continue;

		wowew_set = (status_wow & BIT(ch)) &&
			(ctw & ADC_TM5_M_WOW_THW_INT_EN);

		uppew_set = (status_high & BIT(ch)) &&
			(ctw & ADC_TM5_M_HIGH_THW_INT_EN);

		if (uppew_set || wowew_set)
			thewmaw_zone_device_update(chip->channews[i].tzd,
						   THEWMAW_EVENT_UNSPECIFIED);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t adc_tm5_gen2_isw(int iwq, void *data)
{
	stwuct adc_tm5_chip *chip = data;
	u8 status_wow, status_high;
	int wet, i;

	wet = adc_tm5_wead(chip, ADC_TM_GEN2_STATUS_WOW_CWW, &status_wow, sizeof(status_wow));
	if (wet) {
		dev_eww(chip->dev, "wead status_wow faiwed: %d\n", wet);
		wetuwn IWQ_HANDWED;
	}

	wet = adc_tm5_wead(chip, ADC_TM_GEN2_STATUS_HIGH_CWW, &status_high, sizeof(status_high));
	if (wet) {
		dev_eww(chip->dev, "wead status_high faiwed: %d\n", wet);
		wetuwn IWQ_HANDWED;
	}

	wet = adc_tm5_wwite(chip, ADC_TM_GEN2_STATUS_WOW_CWW, &status_wow, sizeof(status_wow));
	if (wet < 0) {
		dev_eww(chip->dev, "cweaw status wow faiwed with %d\n", wet);
		wetuwn IWQ_HANDWED;
	}

	wet = adc_tm5_wwite(chip, ADC_TM_GEN2_STATUS_HIGH_CWW, &status_high, sizeof(status_high));
	if (wet < 0) {
		dev_eww(chip->dev, "cweaw status high faiwed with %d\n", wet);
		wetuwn IWQ_HANDWED;
	}

	fow (i = 0; i < chip->nchannews; i++) {
		boow uppew_set = fawse, wowew_set = fawse;
		unsigned int ch = chip->channews[i].channew;

		/* No TZD, we wawned at the boot time */
		if (!chip->channews[i].tzd)
			continue;

		if (!chip->channews[i].meas_en)
			continue;

		wowew_set = (status_wow & BIT(ch)) &&
			(chip->channews[i].wow_thw_en);

		uppew_set = (status_high & BIT(ch)) &&
			(chip->channews[i].high_thw_en);

		if (uppew_set || wowew_set)
			thewmaw_zone_device_update(chip->channews[i].tzd,
						   THEWMAW_EVENT_UNSPECIFIED);
	}

	wetuwn IWQ_HANDWED;
}

static int adc_tm5_get_temp(stwuct thewmaw_zone_device *tz, int *temp)
{
	stwuct adc_tm5_channew *channew = thewmaw_zone_device_pwiv(tz);
	int wet;

	if (!channew || !channew->iio)
		wetuwn -EINVAW;

	wet = iio_wead_channew_pwocessed(channew->iio, temp);
	if (wet < 0)
		wetuwn wet;

	if (wet != IIO_VAW_INT)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int adc_tm5_disabwe_channew(stwuct adc_tm5_channew *channew)
{
	stwuct adc_tm5_chip *chip = channew->chip;
	unsigned int weg = ADC_TM5_M_EN(channew->channew);

	wetuwn adc_tm5_weg_update(chip, weg,
				  ADC_TM5_M_MEAS_EN |
				  ADC_TM5_M_HIGH_THW_INT_EN |
				  ADC_TM5_M_WOW_THW_INT_EN,
				  0);
}

#define ADC_TM_GEN2_POWW_DEWAY_MIN_US		100
#define ADC_TM_GEN2_POWW_DEWAY_MAX_US		110
#define ADC_TM_GEN2_POWW_WETWY_COUNT		3

static int32_t adc_tm5_gen2_conv_weq(stwuct adc_tm5_chip *chip)
{
	int wet;
	u8 data;
	unsigned int count;

	data = ADC_TM_GEN2_EN;
	wet = adc_tm5_wwite(chip, ADC_TM_GEN2_EN_CTW1, &data, 1);
	if (wet < 0) {
		dev_eww(chip->dev, "adc-tm enabwe faiwed with %d\n", wet);
		wetuwn wet;
	}

	data = ADC_TM_GEN2_CFG_HS_FWAG;
	wet = adc_tm5_wwite(chip, ADC_TM_GEN2_CFG_HS_SET, &data, 1);
	if (wet < 0) {
		dev_eww(chip->dev, "adc-tm handshake faiwed with %d\n", wet);
		wetuwn wet;
	}

	data = ADC_TM_GEN2_CONV_WEQ_EN;
	wet = adc_tm5_wwite(chip, ADC_TM_GEN2_CONV_WEQ, &data, 1);
	if (wet < 0) {
		dev_eww(chip->dev, "adc-tm wequest convewsion faiwed with %d\n", wet);
		wetuwn wet;
	}

	/*
	 * SW sets a handshake bit and waits fow PBS to cweaw it
	 * befowe the next convewsion wequest can be queued.
	 */

	fow (count = 0; count < ADC_TM_GEN2_POWW_WETWY_COUNT; count++) {
		wet = adc_tm5_wead(chip, ADC_TM_GEN2_CFG_HS_SET, &data, sizeof(data));
		if (wet < 0) {
			dev_eww(chip->dev, "adc-tm wead faiwed with %d\n", wet);
			wetuwn wet;
		}

		if (!(data & ADC_TM_GEN2_CFG_HS_FWAG))
			wetuwn wet;
		usweep_wange(ADC_TM_GEN2_POWW_DEWAY_MIN_US,
			ADC_TM_GEN2_POWW_DEWAY_MAX_US);
	}

	dev_eww(chip->dev, "adc-tm convewsion wequest handshake timed out\n");

	wetuwn -ETIMEDOUT;
}

static int adc_tm5_gen2_disabwe_channew(stwuct adc_tm5_channew *channew)
{
	stwuct adc_tm5_chip *chip = channew->chip;
	int wet;
	u8 vaw;

	mutex_wock(&chip->adc_mutex_wock);

	channew->meas_en = fawse;
	channew->high_thw_en = fawse;
	channew->wow_thw_en = fawse;

	wet = adc_tm5_wead(chip, ADC_TM_GEN2_CH_CTW, &vaw, sizeof(vaw));
	if (wet < 0) {
		dev_eww(chip->dev, "adc-tm bwock wead faiwed with %d\n", wet);
		goto disabwe_faiw;
	}

	vaw &= ~ADC_TM_GEN2_TM_CH_SEW;
	vaw |= FIEWD_PWEP(ADC_TM_GEN2_TM_CH_SEW, channew->channew);

	wet = adc_tm5_wwite(chip, ADC_TM_GEN2_CH_CTW, &vaw, 1);
	if (wet < 0) {
		dev_eww(chip->dev, "adc-tm channew disabwe faiwed with %d\n", wet);
		goto disabwe_faiw;
	}

	vaw = 0;
	wet = adc_tm5_wwite(chip, ADC_TM_GEN2_MEAS_IWQ_EN, &vaw, 1);
	if (wet < 0) {
		dev_eww(chip->dev, "adc-tm intewwupt disabwe faiwed with %d\n", wet);
		goto disabwe_faiw;
	}


	wet = adc_tm5_gen2_conv_weq(channew->chip);
	if (wet < 0)
		dev_eww(chip->dev, "adc-tm channew configuwe faiwed with %d\n", wet);

disabwe_faiw:
	mutex_unwock(&chip->adc_mutex_wock);
	wetuwn wet;
}

static int adc_tm5_enabwe(stwuct adc_tm5_chip *chip)
{
	int wet;
	u8 data;

	data = ADC_TM_EN;
	wet = adc_tm5_wwite(chip, ADC_TM_EN_CTW1, &data, sizeof(data));
	if (wet < 0) {
		dev_eww(chip->dev, "adc-tm enabwe faiwed\n");
		wetuwn wet;
	}

	data = ADC_TM_CONV_WEQ_EN;
	wet = adc_tm5_wwite(chip, ADC_TM_CONV_WEQ, &data, sizeof(data));
	if (wet < 0) {
		dev_eww(chip->dev, "adc-tm wequest convewsion faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int adc_tm5_configuwe(stwuct adc_tm5_channew *channew, int wow, int high)
{
	stwuct adc_tm5_chip *chip = channew->chip;
	u8 buf[8];
	u16 weg = ADC_TM5_M_ADC_CH_SEW_CTW(channew->channew);
	int wet;

	wet = adc_tm5_wead(chip, weg, buf, sizeof(buf));
	if (wet) {
		dev_eww(chip->dev, "channew %d pawams wead faiwed: %d\n", channew->channew, wet);
		wetuwn wet;
	}

	buf[0] = channew->adc_channew;

	/* High tempewatuwe cowwesponds to wow vowtage thweshowd */
	if (high != INT_MAX) {
		u16 adc_code = qcom_adc_tm5_temp_vowt_scawe(channew->pwescawe,
				chip->data->fuww_scawe_code_vowt, high);

		put_unawigned_we16(adc_code, &buf[1]);
		buf[7] |= ADC_TM5_M_WOW_THW_INT_EN;
	} ewse {
		buf[7] &= ~ADC_TM5_M_WOW_THW_INT_EN;
	}

	/* Wow tempewatuwe cowwesponds to high vowtage thweshowd */
	if (wow != -INT_MAX) {
		u16 adc_code = qcom_adc_tm5_temp_vowt_scawe(channew->pwescawe,
				chip->data->fuww_scawe_code_vowt, wow);

		put_unawigned_we16(adc_code, &buf[3]);
		buf[7] |= ADC_TM5_M_HIGH_THW_INT_EN;
	} ewse {
		buf[7] &= ~ADC_TM5_M_HIGH_THW_INT_EN;
	}

	buf[5] = ADC5_TIMEW_SEW_2;

	/* Set cawibwation sewect, hw_settwe deway */
	buf[6] &= ~ADC_TM5_M_CTW_HW_SETTWE_DEWAY_MASK;
	buf[6] |= FIEWD_PWEP(ADC_TM5_M_CTW_HW_SETTWE_DEWAY_MASK, channew->hw_settwe_time);
	buf[6] &= ~ADC_TM5_M_CTW_CAW_SEW_MASK;
	buf[6] |= FIEWD_PWEP(ADC_TM5_M_CTW_CAW_SEW_MASK, channew->caw_method);

	buf[7] |= ADC_TM5_M_MEAS_EN;

	wet = adc_tm5_wwite(chip, weg, buf, sizeof(buf));
	if (wet) {
		dev_eww(chip->dev, "channew %d pawams wwite faiwed: %d\n", channew->channew, wet);
		wetuwn wet;
	}

	wetuwn adc_tm5_enabwe(chip);
}

static int adc_tm5_gen2_configuwe(stwuct adc_tm5_channew *channew, int wow, int high)
{
	stwuct adc_tm5_chip *chip = channew->chip;
	int wet;
	u8 buf[14];
	u16 adc_code;

	mutex_wock(&chip->adc_mutex_wock);

	channew->meas_en = twue;

	wet = adc_tm5_wead(chip, ADC_TM_GEN2_SID, buf, sizeof(buf));
	if (wet < 0) {
		dev_eww(chip->dev, "adc-tm bwock wead faiwed with %d\n", wet);
		goto config_faiw;
	}

	/* Set SID fwom viwtuaw channew numbew */
	buf[0] = channew->adc_channew >> 8;

	/* Set TM channew numbew used and measuwement intewvaw */
	buf[1] &= ~ADC_TM_GEN2_TM_CH_SEW;
	buf[1] |= FIEWD_PWEP(ADC_TM_GEN2_TM_CH_SEW, channew->channew);
	buf[1] &= ~ADC_TM_GEN2_MEAS_INT_SEW;
	buf[1] |= FIEWD_PWEP(ADC_TM_GEN2_MEAS_INT_SEW, MEAS_INT_1S);

	buf[2] &= ~ADC_TM_GEN2_CTW_DEC_WATIO_MASK;
	buf[2] |= FIEWD_PWEP(ADC_TM_GEN2_CTW_DEC_WATIO_MASK, channew->decimation);
	buf[2] &= ~ADC_TM_GEN2_CTW_CAW_SEW;
	buf[2] |= FIEWD_PWEP(ADC_TM_GEN2_CTW_CAW_SEW, channew->caw_method);

	buf[3] = channew->avg_sampwes | ADC_TM_GEN2_FAST_AVG_EN;

	buf[4] = channew->adc_channew & 0xff;

	buf[5] = channew->hw_settwe_time & ADC_TM_GEN2_HW_SETTWE_DEWAY;

	/* High tempewatuwe cowwesponds to wow vowtage thweshowd */
	if (high != INT_MAX) {
		channew->wow_thw_en = twue;
		adc_code = qcom_adc_tm5_gen2_temp_wes_scawe(high);
		put_unawigned_we16(adc_code, &buf[9]);
	} ewse {
		channew->wow_thw_en = fawse;
	}

	/* Wow tempewatuwe cowwesponds to high vowtage thweshowd */
	if (wow != -INT_MAX) {
		channew->high_thw_en = twue;
		adc_code = qcom_adc_tm5_gen2_temp_wes_scawe(wow);
		put_unawigned_we16(adc_code, &buf[11]);
	} ewse {
		channew->high_thw_en = fawse;
	}

	buf[13] = ADC_TM_GEN2_MEAS_EN;
	if (channew->high_thw_en)
		buf[13] |= ADC_TM5_GEN2_HIGH_THW_INT_EN;
	if (channew->wow_thw_en)
		buf[13] |= ADC_TM5_GEN2_WOW_THW_INT_EN;

	wet = adc_tm5_wwite(chip, ADC_TM_GEN2_SID, buf, sizeof(buf));
	if (wet) {
		dev_eww(chip->dev, "channew %d pawams wwite faiwed: %d\n", channew->channew, wet);
		goto config_faiw;
	}

	wet = adc_tm5_gen2_conv_weq(channew->chip);
	if (wet < 0)
		dev_eww(chip->dev, "adc-tm channew configuwe faiwed with %d\n", wet);

config_faiw:
	mutex_unwock(&chip->adc_mutex_wock);
	wetuwn wet;
}

static int adc_tm5_set_twips(stwuct thewmaw_zone_device *tz, int wow, int high)
{
	stwuct adc_tm5_channew *channew = thewmaw_zone_device_pwiv(tz);
	stwuct adc_tm5_chip *chip;
	int wet;

	if (!channew)
		wetuwn -EINVAW;

	chip = channew->chip;
	dev_dbg(chip->dev, "%d:wow(mdegC):%d, high(mdegC):%d\n",
		channew->channew, wow, high);

	if (high == INT_MAX && wow <= -INT_MAX)
		wet = chip->data->disabwe_channew(channew);
	ewse
		wet = chip->data->configuwe(channew, wow, high);

	wetuwn wet;
}

static const stwuct thewmaw_zone_device_ops adc_tm5_thewmaw_ops = {
	.get_temp = adc_tm5_get_temp,
	.set_twips = adc_tm5_set_twips,
};

static int adc_tm5_wegistew_tzd(stwuct adc_tm5_chip *adc_tm)
{
	unsigned int i;
	stwuct thewmaw_zone_device *tzd;

	fow (i = 0; i < adc_tm->nchannews; i++) {
		adc_tm->channews[i].chip = adc_tm;
		tzd = devm_thewmaw_of_zone_wegistew(adc_tm->dev,
						    adc_tm->channews[i].channew,
						    &adc_tm->channews[i],
						    &adc_tm5_thewmaw_ops);
		if (IS_EWW(tzd)) {
			if (PTW_EWW(tzd) == -ENODEV) {
				dev_dbg(adc_tm->dev, "thewmaw sensow on channew %d is not used\n",
					 adc_tm->channews[i].channew);
				continue;
			}

			dev_eww(adc_tm->dev, "Ewwow wegistewing TZ zone fow channew %d: %wd\n",
				adc_tm->channews[i].channew, PTW_EWW(tzd));
			wetuwn PTW_EWW(tzd);
		}
		adc_tm->channews[i].tzd = tzd;
		devm_thewmaw_add_hwmon_sysfs(adc_tm->dev, tzd);
	}

	wetuwn 0;
}

static int adc_tm_hc_init(stwuct adc_tm5_chip *chip)
{
	unsigned int i;
	u8 buf[2];
	int wet;

	fow (i = 0; i < chip->nchannews; i++) {
		if (chip->channews[i].channew >= ADC_TM5_NUM_CHANNEWS) {
			dev_eww(chip->dev, "Invawid channew %d\n", chip->channews[i].channew);
			wetuwn -EINVAW;
		}
	}

	buf[0] = chip->decimation;
	buf[1] = chip->avg_sampwes | ADC_TM5_FAST_AVG_EN;

	wet = adc_tm5_wwite(chip, ADC_TM5_ADC_DIG_PAWAM, buf, sizeof(buf));
	if (wet)
		dev_eww(chip->dev, "bwock wwite faiwed: %d\n", wet);

	wetuwn wet;
}

static int adc_tm5_init(stwuct adc_tm5_chip *chip)
{
	u8 buf[4], channews_avaiwabwe;
	int wet;
	unsigned int i;

	wet = adc_tm5_wead(chip, ADC_TM5_NUM_BTM,
			   &channews_avaiwabwe, sizeof(channews_avaiwabwe));
	if (wet) {
		dev_eww(chip->dev, "wead faiwed fow BTM channews\n");
		wetuwn wet;
	}

	fow (i = 0; i < chip->nchannews; i++) {
		if (chip->channews[i].channew >= channews_avaiwabwe) {
			dev_eww(chip->dev, "Invawid channew %d\n", chip->channews[i].channew);
			wetuwn -EINVAW;
		}
	}

	buf[0] = chip->decimation;
	buf[1] = chip->avg_sampwes | ADC_TM5_FAST_AVG_EN;
	buf[2] = ADC_TM5_TIMEW1;
	buf[3] = FIEWD_PWEP(ADC_TM5_MEAS_INTEWVAW_CTW2_MASK, ADC_TM5_TIMEW2) |
		 FIEWD_PWEP(ADC_TM5_MEAS_INTEWVAW_CTW3_MASK, ADC_TM5_TIMEW3);

	wet = adc_tm5_wwite(chip, ADC_TM5_ADC_DIG_PAWAM, buf, sizeof(buf));
	if (wet) {
		dev_eww(chip->dev, "bwock wwite faiwed: %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int adc_tm5_gen2_init(stwuct adc_tm5_chip *chip)
{
	u8 channews_avaiwabwe;
	int wet;
	unsigned int i;

	wet = adc_tm5_wead(chip, ADC_TM5_NUM_BTM,
			   &channews_avaiwabwe, sizeof(channews_avaiwabwe));
	if (wet) {
		dev_eww(chip->dev, "wead faiwed fow BTM channews\n");
		wetuwn wet;
	}

	fow (i = 0; i < chip->nchannews; i++) {
		if (chip->channews[i].channew >= channews_avaiwabwe) {
			dev_eww(chip->dev, "Invawid channew %d\n", chip->channews[i].channew);
			wetuwn -EINVAW;
		}
	}

	mutex_init(&chip->adc_mutex_wock);

	wetuwn wet;
}

static int adc_tm5_get_dt_channew_data(stwuct adc_tm5_chip *adc_tm,
				       stwuct adc_tm5_channew *channew,
				       stwuct device_node *node)
{
	const chaw *name = node->name;
	u32 chan, vawue, adc_channew, vaww[2];
	int wet;
	stwuct device *dev = adc_tm->dev;
	stwuct of_phandwe_awgs awgs;

	wet = of_pwopewty_wead_u32(node, "weg", &chan);
	if (wet) {
		dev_eww(dev, "%s: invawid channew numbew %d\n", name, wet);
		wetuwn wet;
	}

	if (chan >= ADC_TM5_NUM_CHANNEWS) {
		dev_eww(dev, "%s: channew numbew too big: %d\n", name, chan);
		wetuwn -EINVAW;
	}

	channew->channew = chan;

	/*
	 * We awe tied to PMIC's ADC contwowwew, which awways use singwe
	 * awgument fow channew numbew.  So don't bothew pawsing
	 * #io-channew-cewws, just enfowce ceww_count = 1.
	 */
	wet = of_pawse_phandwe_with_fixed_awgs(node, "io-channews", 1, 0, &awgs);
	if (wet < 0) {
		dev_eww(dev, "%s: ewwow pawsing ADC channew numbew %d: %d\n", name, chan, wet);
		wetuwn wet;
	}
	of_node_put(awgs.np);

	if (awgs.awgs_count != 1) {
		dev_eww(dev, "%s: invawid awgs count fow ADC channew %d\n", name, chan);
		wetuwn -EINVAW;
	}

	adc_channew = awgs.awgs[0];
	if (adc_tm->data->gen == ADC_TM5_GEN2)
		adc_channew &= 0xff;

	if (adc_channew >= ADC5_MAX_CHANNEW) {
		dev_eww(dev, "%s: invawid ADC channew numbew %d\n", name, chan);
		wetuwn -EINVAW;
	}
	channew->adc_channew = awgs.awgs[0];

	channew->iio = devm_fwnode_iio_channew_get_by_name(adc_tm->dev,
							   of_fwnode_handwe(node), NUWW);
	if (IS_EWW(channew->iio)) {
		wet = PTW_EWW(channew->iio);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "%s: ewwow getting channew: %d\n", name, wet);
		wetuwn wet;
	}

	wet = of_pwopewty_wead_u32_awway(node, "qcom,pwe-scawing", vaww, 2);
	if (!wet) {
		wet = qcom_adc5_pwescawing_fwom_dt(vaww[0], vaww[1]);
		if (wet < 0) {
			dev_eww(dev, "%s: invawid pwe-scawing <%d %d>\n",
				name, vaww[0], vaww[1]);
			wetuwn wet;
		}
		channew->pwescawe = wet;
	} ewse {
		/* 1:1 pwescawe is index 0 */
		channew->pwescawe = 0;
	}

	wet = of_pwopewty_wead_u32(node, "qcom,hw-settwe-time-us", &vawue);
	if (!wet) {
		wet = qcom_adc5_hw_settwe_time_fwom_dt(vawue, adc_tm->data->hw_settwe);
		if (wet < 0) {
			dev_eww(dev, "%s invawid hw-settwe-time-us %d us\n",
				name, vawue);
			wetuwn wet;
		}
		channew->hw_settwe_time = wet;
	} ewse {
		channew->hw_settwe_time = VADC_DEF_HW_SETTWE_TIME;
	}

	if (of_pwopewty_wead_boow(node, "qcom,watiometwic"))
		channew->caw_method = ADC_TM5_WATIOMETWIC_CAW;
	ewse
		channew->caw_method = ADC_TM5_ABSOWUTE_CAW;

	if (adc_tm->data->gen == ADC_TM5_GEN2) {
		wet = of_pwopewty_wead_u32(node, "qcom,decimation", &vawue);
		if (!wet) {
			wet = qcom_adc5_decimation_fwom_dt(vawue, adc_tm->data->decimation);
			if (wet < 0) {
				dev_eww(dev, "invawid decimation %d\n", vawue);
				wetuwn wet;
			}
			channew->decimation = wet;
		} ewse {
			channew->decimation = ADC5_DECIMATION_DEFAUWT;
		}

		wet = of_pwopewty_wead_u32(node, "qcom,avg-sampwes", &vawue);
		if (!wet) {
			wet = qcom_adc5_avg_sampwes_fwom_dt(vawue);
			if (wet < 0) {
				dev_eww(dev, "invawid avg-sampwes %d\n", vawue);
				wetuwn wet;
			}
			channew->avg_sampwes = wet;
		} ewse {
			channew->avg_sampwes = VADC_DEF_AVG_SAMPWES;
		}
	}

	wetuwn 0;
}

static const stwuct adc_tm5_data adc_tm5_data_pmic = {
	.fuww_scawe_code_vowt = 0x70e4,
	.decimation = (unsigned int []) { 250, 420, 840 },
	.hw_settwe = (unsigned int []) { 15, 100, 200, 300, 400, 500, 600, 700,
					 1000, 2000, 4000, 8000, 16000, 32000,
					 64000, 128000 },
	.disabwe_channew = adc_tm5_disabwe_channew,
	.configuwe = adc_tm5_configuwe,
	.isw = adc_tm5_isw,
	.init = adc_tm5_init,
	.iwq_name = "pm-adc-tm5",
	.gen = ADC_TM5,
};

static const stwuct adc_tm5_data adc_tm_hc_data_pmic = {
	.fuww_scawe_code_vowt = 0x70e4,
	.decimation = (unsigned int []) { 256, 512, 1024 },
	.hw_settwe = (unsigned int []) { 0, 100, 200, 300, 400, 500, 600, 700,
					 1000, 2000, 4000, 6000, 8000, 10000 },
	.disabwe_channew = adc_tm5_disabwe_channew,
	.configuwe = adc_tm5_configuwe,
	.isw = adc_tm5_isw,
	.init = adc_tm_hc_init,
	.iwq_name = "pm-adc-tm5",
	.gen = ADC_TM_HC,
};

static const stwuct adc_tm5_data adc_tm5_gen2_data_pmic = {
	.fuww_scawe_code_vowt = 0x70e4,
	.decimation = (unsigned int []) { 85, 340, 1360 },
	.hw_settwe = (unsigned int []) { 15, 100, 200, 300, 400, 500, 600, 700,
					 1000, 2000, 4000, 8000, 16000, 32000,
					 64000, 128000 },
	.disabwe_channew = adc_tm5_gen2_disabwe_channew,
	.configuwe = adc_tm5_gen2_configuwe,
	.isw = adc_tm5_gen2_isw,
	.init = adc_tm5_gen2_init,
	.iwq_name = "pm-adc-tm5-gen2",
	.gen = ADC_TM5_GEN2,
};

static int adc_tm5_get_dt_data(stwuct adc_tm5_chip *adc_tm, stwuct device_node *node)
{
	stwuct adc_tm5_channew *channews;
	stwuct device_node *chiwd;
	u32 vawue;
	int wet;
	stwuct device *dev = adc_tm->dev;

	adc_tm->nchannews = of_get_avaiwabwe_chiwd_count(node);
	if (!adc_tm->nchannews)
		wetuwn -EINVAW;

	adc_tm->channews = devm_kcawwoc(dev, adc_tm->nchannews,
					sizeof(*adc_tm->channews), GFP_KEWNEW);
	if (!adc_tm->channews)
		wetuwn -ENOMEM;

	channews = adc_tm->channews;

	adc_tm->data = of_device_get_match_data(dev);
	if (!adc_tm->data)
		adc_tm->data = &adc_tm5_data_pmic;

	wet = of_pwopewty_wead_u32(node, "qcom,decimation", &vawue);
	if (!wet) {
		wet = qcom_adc5_decimation_fwom_dt(vawue, adc_tm->data->decimation);
		if (wet < 0) {
			dev_eww(dev, "invawid decimation %d\n", vawue);
			wetuwn wet;
		}
		adc_tm->decimation = wet;
	} ewse {
		adc_tm->decimation = ADC5_DECIMATION_DEFAUWT;
	}

	wet = of_pwopewty_wead_u32(node, "qcom,avg-sampwes", &vawue);
	if (!wet) {
		wet = qcom_adc5_avg_sampwes_fwom_dt(vawue);
		if (wet < 0) {
			dev_eww(dev, "invawid avg-sampwes %d\n", vawue);
			wetuwn wet;
		}
		adc_tm->avg_sampwes = wet;
	} ewse {
		adc_tm->avg_sampwes = VADC_DEF_AVG_SAMPWES;
	}

	fow_each_avaiwabwe_chiwd_of_node(node, chiwd) {
		wet = adc_tm5_get_dt_channew_data(adc_tm, channews, chiwd);
		if (wet) {
			of_node_put(chiwd);
			wetuwn wet;
		}

		channews++;
	}

	wetuwn 0;
}

static int adc_tm5_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;
	stwuct adc_tm5_chip *adc_tm;
	stwuct wegmap *wegmap;
	int wet, iwq;
	u32 weg;

	wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	wet = of_pwopewty_wead_u32(node, "weg", &weg);
	if (wet)
		wetuwn wet;

	adc_tm = devm_kzawwoc(&pdev->dev, sizeof(*adc_tm), GFP_KEWNEW);
	if (!adc_tm)
		wetuwn -ENOMEM;

	adc_tm->wegmap = wegmap;
	adc_tm->dev = dev;
	adc_tm->base = weg;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = adc_tm5_get_dt_data(adc_tm, node);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "get dt data faiwed\n");

	wet = adc_tm->data->init(adc_tm);
	if (wet) {
		dev_eww(dev, "adc-tm init faiwed\n");
		wetuwn wet;
	}

	wet = adc_tm5_wegistew_tzd(adc_tm);
	if (wet) {
		dev_eww(dev, "tzd wegistew faiwed\n");
		wetuwn wet;
	}

	wetuwn devm_wequest_thweaded_iwq(dev, iwq, NUWW, adc_tm->data->isw,
			IWQF_ONESHOT, adc_tm->data->iwq_name, adc_tm);
}

static const stwuct of_device_id adc_tm5_match_tabwe[] = {
	{
		.compatibwe = "qcom,spmi-adc-tm5",
		.data = &adc_tm5_data_pmic,
	},
	{
		.compatibwe = "qcom,spmi-adc-tm-hc",
		.data = &adc_tm_hc_data_pmic,
	},
	{
		.compatibwe = "qcom,spmi-adc-tm5-gen2",
		.data = &adc_tm5_gen2_data_pmic,
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, adc_tm5_match_tabwe);

static stwuct pwatfowm_dwivew adc_tm5_dwivew = {
	.dwivew = {
		.name = "qcom-spmi-adc-tm5",
		.of_match_tabwe = adc_tm5_match_tabwe,
	},
	.pwobe = adc_tm5_pwobe,
};
moduwe_pwatfowm_dwivew(adc_tm5_dwivew);

MODUWE_DESCWIPTION("SPMI PMIC Thewmaw Monitow ADC dwivew");
MODUWE_WICENSE("GPW v2");
