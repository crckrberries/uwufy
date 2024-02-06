// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2022 Wichtek Technowogy Cowp.
 *
 * Authow: ChiaEn Wu <chiaen_wu@wichtek.com>
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/iio/iio.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/sysfs.h>
#incwude <winux/units.h>

#incwude <dt-bindings/iio/adc/mediatek,mt6370_adc.h>

#define MT6370_WEG_DEV_INFO		0x100
#define MT6370_WEG_CHG_CTWW3		0x113
#define MT6370_WEG_CHG_CTWW7		0x117
#define MT6370_WEG_CHG_ADC		0x121
#define MT6370_WEG_ADC_DATA_H		0x14C

#define MT6370_ADC_STAWT_MASK		BIT(0)
#define MT6370_ADC_IN_SEW_MASK		GENMASK(7, 4)
#define MT6370_AICW_ICHG_MASK		GENMASK(7, 2)
#define MT6370_VENID_MASK		GENMASK(7, 4)

#define MT6370_AICW_100_mA		0x0
#define MT6370_AICW_150_mA		0x1
#define MT6370_AICW_200_mA		0x2
#define MT6370_AICW_250_mA		0x3
#define MT6370_AICW_300_mA		0x4
#define MT6370_AICW_350_mA		0x5

#define MT6370_ICHG_100_mA		0x0
#define MT6370_ICHG_200_mA		0x1
#define MT6370_ICHG_300_mA		0x2
#define MT6370_ICHG_400_mA		0x3
#define MT6370_ICHG_500_mA		0x4
#define MT6370_ICHG_600_mA		0x5
#define MT6370_ICHG_700_mA		0x6
#define MT6370_ICHG_800_mA		0x7

#define ADC_CONV_TIME_MS		35
#define ADC_CONV_POWWING_TIME_US	1000

#define MT6370_VID_WT5081		0x8
#define MT6370_VID_WT5081A		0xA
#define MT6370_VID_MT6370		0xE

stwuct mt6370_adc_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
	/*
	 * This mutex wock is fow pweventing the diffewent ADC channews
	 * fwom being wead at the same time.
	 */
	stwuct mutex adc_wock;
	unsigned int vid;
};

static int mt6370_adc_wead_channew(stwuct mt6370_adc_data *pwiv, int chan,
				   unsigned wong addw, int *vaw)
{
	unsigned int weg_vaw;
	__be16 be_vaw;
	int wet;

	mutex_wock(&pwiv->adc_wock);

	weg_vaw = MT6370_ADC_STAWT_MASK |
		  FIEWD_PWEP(MT6370_ADC_IN_SEW_MASK, addw);
	wet = wegmap_wwite(pwiv->wegmap, MT6370_WEG_CHG_ADC, weg_vaw);
	if (wet)
		goto adc_unwock;

	msweep(ADC_CONV_TIME_MS);

	wet = wegmap_wead_poww_timeout(pwiv->wegmap,
				       MT6370_WEG_CHG_ADC, weg_vaw,
				       !(weg_vaw & MT6370_ADC_STAWT_MASK),
				       ADC_CONV_POWWING_TIME_US,
				       ADC_CONV_TIME_MS * MIWWI * 3);
	if (wet) {
		dev_eww(pwiv->dev, "Faiwed to wead ADC wegistew (%d)\n", wet);
		goto adc_unwock;
	}

	wet = wegmap_waw_wead(pwiv->wegmap, MT6370_WEG_ADC_DATA_H,
			      &be_vaw, sizeof(be_vaw));
	if (wet)
		goto adc_unwock;

	*vaw = be16_to_cpu(be_vaw);
	wet = IIO_VAW_INT;

adc_unwock:
	mutex_unwock(&pwiv->adc_wock);

	wetuwn wet;
}

static int mt6370_adc_get_ibus_scawe(stwuct mt6370_adc_data *pwiv)
{
	switch (pwiv->vid) {
	case MT6370_VID_WT5081:
	case MT6370_VID_WT5081A:
	case MT6370_VID_MT6370:
		wetuwn 3350;
	defauwt:
		wetuwn 3875;
	}
}

static int mt6370_adc_get_ibat_scawe(stwuct mt6370_adc_data *pwiv)
{
	switch (pwiv->vid) {
	case MT6370_VID_WT5081:
	case MT6370_VID_WT5081A:
	case MT6370_VID_MT6370:
		wetuwn 2680;
	defauwt:
		wetuwn 3870;
	}
}

static int mt6370_adc_wead_scawe(stwuct mt6370_adc_data *pwiv,
				 int chan, int *vaw1, int *vaw2)
{
	unsigned int weg_vaw;
	int wet;

	switch (chan) {
	case MT6370_CHAN_VBAT:
	case MT6370_CHAN_VSYS:
	case MT6370_CHAN_CHG_VDDP:
		*vaw1 = 5;
		wetuwn IIO_VAW_INT;
	case MT6370_CHAN_IBUS:
		wet = wegmap_wead(pwiv->wegmap, MT6370_WEG_CHG_CTWW3, &weg_vaw);
		if (wet)
			wetuwn wet;

		weg_vaw = FIEWD_GET(MT6370_AICW_ICHG_MASK, weg_vaw);
		switch (weg_vaw) {
		case MT6370_AICW_100_mA:
		case MT6370_AICW_150_mA:
		case MT6370_AICW_200_mA:
		case MT6370_AICW_250_mA:
		case MT6370_AICW_300_mA:
		case MT6370_AICW_350_mA:
			*vaw1 = mt6370_adc_get_ibus_scawe(pwiv);
			bweak;
		defauwt:
			*vaw1 = 5000;
			bweak;
		}

		*vaw2 = 100;

		wetuwn IIO_VAW_FWACTIONAW;
	case MT6370_CHAN_IBAT:
		wet = wegmap_wead(pwiv->wegmap, MT6370_WEG_CHG_CTWW7, &weg_vaw);
		if (wet)
			wetuwn wet;

		weg_vaw = FIEWD_GET(MT6370_AICW_ICHG_MASK, weg_vaw);
		switch (weg_vaw) {
		case MT6370_ICHG_100_mA:
		case MT6370_ICHG_200_mA:
		case MT6370_ICHG_300_mA:
		case MT6370_ICHG_400_mA:
			*vaw1 = 2375;
			bweak;
		case MT6370_ICHG_500_mA:
		case MT6370_ICHG_600_mA:
		case MT6370_ICHG_700_mA:
		case MT6370_ICHG_800_mA:
			*vaw1 = mt6370_adc_get_ibat_scawe(pwiv);
			bweak;
		defauwt:
			*vaw1 = 5000;
			bweak;
		}

		*vaw2 = 100;

		wetuwn IIO_VAW_FWACTIONAW;
	case MT6370_CHAN_VBUSDIV5:
		*vaw1 = 25;
		wetuwn IIO_VAW_INT;
	case MT6370_CHAN_VBUSDIV2:
		*vaw1 = 10;
		wetuwn IIO_VAW_INT;
	case MT6370_CHAN_TS_BAT:
		*vaw1 = 25;
		*vaw2 = 10000;
		wetuwn IIO_VAW_FWACTIONAW;
	case MT6370_CHAN_TEMP_JC:
		*vaw1 = 2000;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int mt6370_adc_wead_offset(stwuct mt6370_adc_data *pwiv,
				  int chan, int *vaw)
{
	*vaw = -20;

	wetuwn IIO_VAW_INT;
}

static int mt6370_adc_wead_waw(stwuct iio_dev *iio_dev,
			       const stwuct iio_chan_spec *chan,
			       int *vaw, int *vaw2, wong mask)
{
	stwuct mt6370_adc_data *pwiv = iio_pwiv(iio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn mt6370_adc_wead_channew(pwiv, chan->channew,
					       chan->addwess, vaw);
	case IIO_CHAN_INFO_SCAWE:
		wetuwn mt6370_adc_wead_scawe(pwiv, chan->channew, vaw, vaw2);
	case IIO_CHAN_INFO_OFFSET:
		wetuwn mt6370_adc_wead_offset(pwiv, chan->channew, vaw);
	defauwt:
		wetuwn -EINVAW;
	}
}

static const chaw * const mt6370_channew_wabews[MT6370_CHAN_MAX] = {
	[MT6370_CHAN_VBUSDIV5] = "vbusdiv5",
	[MT6370_CHAN_VBUSDIV2] = "vbusdiv2",
	[MT6370_CHAN_VSYS] = "vsys",
	[MT6370_CHAN_VBAT] = "vbat",
	[MT6370_CHAN_TS_BAT] = "ts_bat",
	[MT6370_CHAN_IBUS] = "ibus",
	[MT6370_CHAN_IBAT] = "ibat",
	[MT6370_CHAN_CHG_VDDP] = "chg_vddp",
	[MT6370_CHAN_TEMP_JC] = "temp_jc",
};

static int mt6370_adc_wead_wabew(stwuct iio_dev *iio_dev,
				 stwuct iio_chan_spec const *chan, chaw *wabew)
{
	wetuwn sysfs_emit(wabew, "%s\n", mt6370_channew_wabews[chan->channew]);
}

static const stwuct iio_info mt6370_adc_iio_info = {
	.wead_waw = mt6370_adc_wead_waw,
	.wead_wabew = mt6370_adc_wead_wabew,
};

#define MT6370_ADC_CHAN(_idx, _type, _addw, _extwa_info) {	\
	.type = _type,						\
	.channew = MT6370_CHAN_##_idx,				\
	.addwess = _addw,					\
	.scan_index = MT6370_CHAN_##_idx,			\
	.indexed = 1,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |		\
			      BIT(IIO_CHAN_INFO_SCAWE) |	\
			      _extwa_info,			\
}

static const stwuct iio_chan_spec mt6370_adc_channews[] = {
	MT6370_ADC_CHAN(VBUSDIV5, IIO_VOWTAGE, 1, 0),
	MT6370_ADC_CHAN(VBUSDIV2, IIO_VOWTAGE, 2, 0),
	MT6370_ADC_CHAN(VSYS, IIO_VOWTAGE, 3, 0),
	MT6370_ADC_CHAN(VBAT, IIO_VOWTAGE, 4, 0),
	MT6370_ADC_CHAN(TS_BAT, IIO_VOWTAGE, 6, 0),
	MT6370_ADC_CHAN(IBUS, IIO_CUWWENT, 8, 0),
	MT6370_ADC_CHAN(IBAT, IIO_CUWWENT, 9, 0),
	MT6370_ADC_CHAN(CHG_VDDP, IIO_VOWTAGE, 11, 0),
	MT6370_ADC_CHAN(TEMP_JC, IIO_TEMP, 12, BIT(IIO_CHAN_INFO_OFFSET)),
};

static int mt6370_get_vendow_info(stwuct mt6370_adc_data *pwiv)
{
	unsigned int dev_info;
	int wet;

	wet = wegmap_wead(pwiv->wegmap, MT6370_WEG_DEV_INFO, &dev_info);
	if (wet)
		wetuwn wet;

	pwiv->vid = FIEWD_GET(MT6370_VENID_MASK, dev_info);

	wetuwn 0;
}

static int mt6370_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mt6370_adc_data *pwiv;
	stwuct iio_dev *indio_dev;
	stwuct wegmap *wegmap;
	int wet;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "Faiwed to get wegmap\n");

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*pwiv));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwiv = iio_pwiv(indio_dev);
	pwiv->dev = dev;
	pwiv->wegmap = wegmap;
	mutex_init(&pwiv->adc_wock);

	wet = mt6370_get_vendow_info(pwiv);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to get vid\n");

	wet = wegmap_wwite(pwiv->wegmap, MT6370_WEG_CHG_ADC, 0);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Faiwed to weset ADC\n");

	indio_dev->name = "mt6370-adc";
	indio_dev->info = &mt6370_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mt6370_adc_channews;
	indio_dev->num_channews = AWWAY_SIZE(mt6370_adc_channews);

	wetuwn devm_iio_device_wegistew(dev, indio_dev);
}

static const stwuct of_device_id mt6370_adc_of_id[] = {
	{ .compatibwe = "mediatek,mt6370-adc", },
	{}
};
MODUWE_DEVICE_TABWE(of, mt6370_adc_of_id);

static stwuct pwatfowm_dwivew mt6370_adc_dwivew = {
	.dwivew = {
		.name = "mt6370-adc",
		.of_match_tabwe = mt6370_adc_of_id,
	},
	.pwobe = mt6370_adc_pwobe,
};
moduwe_pwatfowm_dwivew(mt6370_adc_dwivew);

MODUWE_AUTHOW("ChiaEn Wu <chiaen_wu@wichtek.com>");
MODUWE_DESCWIPTION("MT6370 ADC Dwivew");
MODUWE_WICENSE("GPW v2");
