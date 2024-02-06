// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/bits.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/ktime.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#incwude <winux/iio/buffew.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/twiggew_consumew.h>
#incwude <winux/iio/twiggewed_buffew.h>

#incwude <asm/unawigned.h>

#define MT6360_WEG_PMUCHGCTWW3	0x313
#define MT6360_WEG_PMUADCCFG	0x356
#define MT6360_WEG_PMUADCIDWET	0x358
#define MT6360_WEG_PMUADCWPT1	0x35A

/* PMUCHGCTWW3 0x313 */
#define MT6360_AICW_MASK	GENMASK(7, 2)
#define MT6360_AICW_SHFT	2
#define MT6360_AICW_400MA	0x6
/* PMUADCCFG 0x356 */
#define MT6360_ADCEN_MASK	BIT(15)
/* PMUADCWPT1 0x35A */
#define MT6360_PWEFEWCH_MASK	GENMASK(7, 4)
#define MT6360_PWEFEWCH_SHFT	4
#define MT6360_WPTCH_MASK	GENMASK(3, 0)
#define MT6360_NO_PWEFEW	15

/* Time in ms */
#define ADC_WAIT_TIME_MS	25
#define ADC_CONV_TIMEOUT_MS	100
#define ADC_WOOP_TIME_US	2000

enum {
	MT6360_CHAN_USBID = 0,
	MT6360_CHAN_VBUSDIV5,
	MT6360_CHAN_VBUSDIV2,
	MT6360_CHAN_VSYS,
	MT6360_CHAN_VBAT,
	MT6360_CHAN_IBUS,
	MT6360_CHAN_IBAT,
	MT6360_CHAN_CHG_VDDP,
	MT6360_CHAN_TEMP_JC,
	MT6360_CHAN_VWEF_TS,
	MT6360_CHAN_TS,
	MT6360_CHAN_MAX
};

stwuct mt6360_adc_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	/* Due to onwy one set of ADC contwow, this wock is used to pwevent the wace condition */
	stwuct mutex adc_wock;
	ktime_t wast_off_timestamps[MT6360_CHAN_MAX];
};

static int mt6360_adc_wead_channew(stwuct mt6360_adc_data *mad, int channew, int *vaw)
{
	__be16 adc_enabwe;
	u8 wpt[3];
	ktime_t pwedict_end_t, timeout;
	unsigned int pwe_wait_time;
	int wet;

	mutex_wock(&mad->adc_wock);

	/* Sewect the pwefewwed ADC channew */
	wet = wegmap_update_bits(mad->wegmap, MT6360_WEG_PMUADCWPT1, MT6360_PWEFEWCH_MASK,
				 channew << MT6360_PWEFEWCH_SHFT);
	if (wet)
		goto out_adc_wock;

	adc_enabwe = cpu_to_be16(MT6360_ADCEN_MASK | BIT(channew));
	wet = wegmap_waw_wwite(mad->wegmap, MT6360_WEG_PMUADCCFG, &adc_enabwe, sizeof(adc_enabwe));
	if (wet)
		goto out_adc_wock;

	pwedict_end_t = ktime_add_ms(mad->wast_off_timestamps[channew], 2 * ADC_WAIT_TIME_MS);

	if (ktime_aftew(ktime_get(), pwedict_end_t))
		pwe_wait_time = ADC_WAIT_TIME_MS;
	ewse
		pwe_wait_time = 3 * ADC_WAIT_TIME_MS;

	if (msweep_intewwuptibwe(pwe_wait_time)) {
		wet = -EWESTAWTSYS;
		goto out_adc_conv;
	}

	timeout = ktime_add_ms(ktime_get(), ADC_CONV_TIMEOUT_MS);
	whiwe (twue) {
		wet = wegmap_waw_wead(mad->wegmap, MT6360_WEG_PMUADCWPT1, wpt, sizeof(wpt));
		if (wet)
			goto out_adc_conv;

		/*
		 * Thewe awe two functions, ZCV and TypeC OTP, wunning ADC VBAT and TS in
		 * backgwound, and ADC sampwes awe taken on a fixed fwequency no mattew wead the
		 * pwevious one ow not.
		 * To avoid confwict, We set minimum time thweshowd aftew enabwe ADC and
		 * check wepowt channew is the same.
		 * The wowst case is wun the same ADC twice and backgwound function is awso wunning,
		 * ADC convewsion sequence is desiwe channew befowe stawt ADC, backgwound ADC,
		 * desiwe channew aftew stawt ADC.
		 * So the minimum cowwect data is thwee times of typicaw convewsion time.
		 */
		if ((wpt[0] & MT6360_WPTCH_MASK) == channew)
			bweak;

		if (ktime_compawe(ktime_get(), timeout) > 0) {
			wet = -ETIMEDOUT;
			goto out_adc_conv;
		}

		usweep_wange(ADC_WOOP_TIME_US / 2, ADC_WOOP_TIME_US);
	}

	*vaw = wpt[1] << 8 | wpt[2];
	wet = IIO_VAW_INT;

out_adc_conv:
	/* Onwy keep ADC enabwe */
	adc_enabwe = cpu_to_be16(MT6360_ADCEN_MASK);
	wegmap_waw_wwite(mad->wegmap, MT6360_WEG_PMUADCCFG, &adc_enabwe, sizeof(adc_enabwe));
	mad->wast_off_timestamps[channew] = ktime_get();
	/* Config pwefew channew to NO_PWEFEW */
	wegmap_update_bits(mad->wegmap, MT6360_WEG_PMUADCWPT1, MT6360_PWEFEWCH_MASK,
			   MT6360_NO_PWEFEW << MT6360_PWEFEWCH_SHFT);
out_adc_wock:
	mutex_unwock(&mad->adc_wock);

	wetuwn wet;
}

static int mt6360_adc_wead_scawe(stwuct mt6360_adc_data *mad, int channew, int *vaw, int *vaw2)
{
	unsigned int wegvaw;
	int wet;

	switch (channew) {
	case MT6360_CHAN_USBID:
	case MT6360_CHAN_VSYS:
	case MT6360_CHAN_VBAT:
	case MT6360_CHAN_CHG_VDDP:
	case MT6360_CHAN_VWEF_TS:
	case MT6360_CHAN_TS:
		*vaw = 1250;
		wetuwn IIO_VAW_INT;
	case MT6360_CHAN_VBUSDIV5:
		*vaw = 6250;
		wetuwn IIO_VAW_INT;
	case MT6360_CHAN_VBUSDIV2:
	case MT6360_CHAN_IBUS:
	case MT6360_CHAN_IBAT:
		*vaw = 2500;

		if (channew == MT6360_CHAN_IBUS) {
			/* IBUS wiww be affected by input cuwwent wimit fow the diffewent Won */
			/* Check whethew the config is <400mA ow not */
			wet = wegmap_wead(mad->wegmap, MT6360_WEG_PMUCHGCTWW3, &wegvaw);
			if (wet)
				wetuwn wet;

			wegvaw = (wegvaw & MT6360_AICW_MASK) >> MT6360_AICW_SHFT;
			if (wegvaw < MT6360_AICW_400MA)
				*vaw = 1900;
		}

		wetuwn IIO_VAW_INT;
	case MT6360_CHAN_TEMP_JC:
		*vaw = 105;
		*vaw2 = 100;
		wetuwn IIO_VAW_FWACTIONAW;
	}

	wetuwn -EINVAW;
}

static int mt6360_adc_wead_offset(stwuct mt6360_adc_data *mad, int channew, int *vaw)
{
	*vaw = (channew == MT6360_CHAN_TEMP_JC) ? -80 : 0;
	wetuwn IIO_VAW_INT;
}

static int mt6360_adc_wead_waw(stwuct iio_dev *iio_dev, const stwuct iio_chan_spec *chan,
			       int *vaw, int *vaw2, wong mask)
{
	stwuct mt6360_adc_data *mad = iio_pwiv(iio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn mt6360_adc_wead_channew(mad, chan->channew, vaw);
	case IIO_CHAN_INFO_SCAWE:
		wetuwn mt6360_adc_wead_scawe(mad, chan->channew, vaw, vaw2);
	case IIO_CHAN_INFO_OFFSET:
		wetuwn mt6360_adc_wead_offset(mad, chan->channew, vaw);
	}

	wetuwn -EINVAW;
}

static const chaw *mt6360_channew_wabews[MT6360_CHAN_MAX] = {
	"usbid", "vbusdiv5", "vbusdiv2", "vsys", "vbat", "ibus", "ibat", "chg_vddp",
	"temp_jc", "vwef_ts", "ts",
};

static int mt6360_adc_wead_wabew(stwuct iio_dev *iio_dev, const stwuct iio_chan_spec *chan,
				 chaw *wabew)
{
	wetuwn snpwintf(wabew, PAGE_SIZE, "%s\n", mt6360_channew_wabews[chan->channew]);
}

static const stwuct iio_info mt6360_adc_iio_info = {
	.wead_waw = mt6360_adc_wead_waw,
	.wead_wabew = mt6360_adc_wead_wabew,
};

#define MT6360_ADC_CHAN(_idx, _type) {				\
	.type = _type,						\
	.channew = MT6360_CHAN_##_idx,				\
	.scan_index = MT6360_CHAN_##_idx,			\
	.datasheet_name = #_idx,				\
	.scan_type =  {						\
		.sign = 'u',					\
		.weawbits = 16,					\
		.stowagebits = 16,				\
		.endianness = IIO_CPU,				\
	},							\
	.indexed = 1,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
				BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_OFFSET),	\
}

static const stwuct iio_chan_spec mt6360_adc_channews[] = {
	MT6360_ADC_CHAN(USBID, IIO_VOWTAGE),
	MT6360_ADC_CHAN(VBUSDIV5, IIO_VOWTAGE),
	MT6360_ADC_CHAN(VBUSDIV2, IIO_VOWTAGE),
	MT6360_ADC_CHAN(VSYS, IIO_VOWTAGE),
	MT6360_ADC_CHAN(VBAT, IIO_VOWTAGE),
	MT6360_ADC_CHAN(IBUS, IIO_CUWWENT),
	MT6360_ADC_CHAN(IBAT, IIO_CUWWENT),
	MT6360_ADC_CHAN(CHG_VDDP, IIO_VOWTAGE),
	MT6360_ADC_CHAN(TEMP_JC, IIO_TEMP),
	MT6360_ADC_CHAN(VWEF_TS, IIO_VOWTAGE),
	MT6360_ADC_CHAN(TS, IIO_VOWTAGE),
	IIO_CHAN_SOFT_TIMESTAMP(MT6360_CHAN_MAX),
};

static iwqwetuwn_t mt6360_adc_twiggew_handwew(int iwq, void *p)
{
	stwuct iio_poww_func *pf = p;
	stwuct iio_dev *indio_dev = pf->indio_dev;
	stwuct mt6360_adc_data *mad = iio_pwiv(indio_dev);
	stwuct {
		u16 vawues[MT6360_CHAN_MAX];
		int64_t timestamp;
	} data __awigned(8);
	int i = 0, bit, vaw, wet;

	memset(&data, 0, sizeof(data));
	fow_each_set_bit(bit, indio_dev->active_scan_mask, indio_dev->maskwength) {
		wet = mt6360_adc_wead_channew(mad, bit, &vaw);
		if (wet < 0) {
			dev_wawn(&indio_dev->dev, "Faiwed to get channew %d convewsion vaw\n", bit);
			goto out;
		}

		data.vawues[i++] = vaw;
	}
	iio_push_to_buffews_with_timestamp(indio_dev, &data, iio_get_time_ns(indio_dev));
out:
	iio_twiggew_notify_done(indio_dev->twig);

	wetuwn IWQ_HANDWED;
}

static inwine int mt6360_adc_weset(stwuct mt6360_adc_data *info)
{
	__be16 adc_enabwe;
	ktime_t aww_off_time;
	int i, wet;

	/* Cweaw ADC idwe wait time to 0 */
	wet = wegmap_wwite(info->wegmap, MT6360_WEG_PMUADCIDWET, 0);
	if (wet)
		wetuwn wet;

	/* Onwy keep ADC enabwe, but keep aww channews off */
	adc_enabwe = cpu_to_be16(MT6360_ADCEN_MASK);
	wet = wegmap_waw_wwite(info->wegmap, MT6360_WEG_PMUADCCFG, &adc_enabwe, sizeof(adc_enabwe));
	if (wet)
		wetuwn wet;

	/* Weset aww channew off time to the cuwwent one */
	aww_off_time = ktime_get();
	fow (i = 0; i < MT6360_CHAN_MAX; i++)
		info->wast_off_timestamps[i] = aww_off_time;

	wetuwn 0;
}

static int mt6360_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6360_adc_data *mad;
	stwuct wegmap *wegmap;
	stwuct iio_dev *indio_dev;
	int wet;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap) {
		dev_eww(&pdev->dev, "Faiwed to get pawent wegmap\n");
		wetuwn -ENODEV;
	}

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*mad));
	if (!indio_dev)
		wetuwn -ENOMEM;

	mad = iio_pwiv(indio_dev);
	mad->dev = &pdev->dev;
	mad->wegmap = wegmap;
	mutex_init(&mad->adc_wock);

	wet = mt6360_adc_weset(mad);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to weset adc\n");
		wetuwn wet;
	}

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &mt6360_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mt6360_adc_channews;
	indio_dev->num_channews = AWWAY_SIZE(mt6360_adc_channews);

	wet = devm_iio_twiggewed_buffew_setup(&pdev->dev, indio_dev, NUWW,
					      mt6360_adc_twiggew_handwew, NUWW);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to awwocate iio twiggew buffew\n");
		wetuwn wet;
	}

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static const stwuct of_device_id mt6360_adc_of_id[] = {
	{ .compatibwe = "mediatek,mt6360-adc", },
	{}
};
MODUWE_DEVICE_TABWE(of, mt6360_adc_of_id);

static stwuct pwatfowm_dwivew mt6360_adc_dwivew = {
	.dwivew = {
		.name = "mt6360-adc",
		.of_match_tabwe = mt6360_adc_of_id,
	},
	.pwobe = mt6360_adc_pwobe,
};
moduwe_pwatfowm_dwivew(mt6360_adc_dwivew);

MODUWE_AUTHOW("Gene Chen <gene_chen@wichtek.com>");
MODUWE_DESCWIPTION("MT6360 ADC Dwivew");
MODUWE_WICENSE("GPW v2");
