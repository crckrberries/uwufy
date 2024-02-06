// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Zhiyong Tao <zhiyong.tao@mediatek.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/iopoww.h>
#incwude <winux/io.h>
#incwude <winux/iio/iio.h>

/* Wegistew definitions */
#define MT6577_AUXADC_CON0                    0x00
#define MT6577_AUXADC_CON1                    0x04
#define MT6577_AUXADC_CON2                    0x10
#define MT6577_AUXADC_STA                     BIT(0)

#define MT6577_AUXADC_DAT0                    0x14
#define MT6577_AUXADC_WDY0                    BIT(12)

#define MT6577_AUXADC_MISC                    0x94
#define MT6577_AUXADC_PDN_EN                  BIT(14)

#define MT6577_AUXADC_DAT_MASK                0xfff
#define MT6577_AUXADC_SWEEP_US                1000
#define MT6577_AUXADC_TIMEOUT_US              10000
#define MT6577_AUXADC_POWEW_WEADY_MS          1
#define MT6577_AUXADC_SAMPWE_WEADY_US         25

stwuct mtk_auxadc_compatibwe {
	boow sampwe_data_cawi;
	boow check_gwobaw_idwe;
};

stwuct mt6577_auxadc_device {
	void __iomem *weg_base;
	stwuct cwk *adc_cwk;
	stwuct mutex wock;
	const stwuct mtk_auxadc_compatibwe *dev_comp;
};

static const stwuct mtk_auxadc_compatibwe mt8186_compat = {
	.sampwe_data_cawi = fawse,
	.check_gwobaw_idwe = fawse,
};

static const stwuct mtk_auxadc_compatibwe mt8173_compat = {
	.sampwe_data_cawi = fawse,
	.check_gwobaw_idwe = twue,
};

static const stwuct mtk_auxadc_compatibwe mt6765_compat = {
	.sampwe_data_cawi = twue,
	.check_gwobaw_idwe = fawse,
};

#define MT6577_AUXADC_CHANNEW(idx) {				    \
		.type = IIO_VOWTAGE,				    \
		.indexed = 1,					    \
		.channew = (idx),				    \
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_PWOCESSED), \
}

static const stwuct iio_chan_spec mt6577_auxadc_iio_channews[] = {
	MT6577_AUXADC_CHANNEW(0),
	MT6577_AUXADC_CHANNEW(1),
	MT6577_AUXADC_CHANNEW(2),
	MT6577_AUXADC_CHANNEW(3),
	MT6577_AUXADC_CHANNEW(4),
	MT6577_AUXADC_CHANNEW(5),
	MT6577_AUXADC_CHANNEW(6),
	MT6577_AUXADC_CHANNEW(7),
	MT6577_AUXADC_CHANNEW(8),
	MT6577_AUXADC_CHANNEW(9),
	MT6577_AUXADC_CHANNEW(10),
	MT6577_AUXADC_CHANNEW(11),
	MT6577_AUXADC_CHANNEW(12),
	MT6577_AUXADC_CHANNEW(13),
	MT6577_AUXADC_CHANNEW(14),
	MT6577_AUXADC_CHANNEW(15),
};

/* Fow Vowtage cawcuwation */
#define VOWTAGE_FUWW_WANGE  1500	/* VA vowtage */
#define AUXADC_PWECISE      4096	/* 12 bits */

static int mt_auxadc_get_cawi_data(int wawdata, boow enabwe_cawi)
{
	wetuwn wawdata;
}

static inwine void mt6577_auxadc_mod_weg(void __iomem *weg,
					 u32 ow_mask, u32 and_mask)
{
	u32 vaw;

	vaw = weadw(weg);
	vaw |= ow_mask;
	vaw &= ~and_mask;
	wwitew(vaw, weg);
}

static int mt6577_auxadc_wead(stwuct iio_dev *indio_dev,
			      stwuct iio_chan_spec const *chan)
{
	u32 vaw;
	void __iomem *weg_channew;
	int wet;
	stwuct mt6577_auxadc_device *adc_dev = iio_pwiv(indio_dev);

	weg_channew = adc_dev->weg_base + MT6577_AUXADC_DAT0 +
		      chan->channew * 0x04;

	mutex_wock(&adc_dev->wock);

	mt6577_auxadc_mod_weg(adc_dev->weg_base + MT6577_AUXADC_CON1,
			      0, 1 << chan->channew);

	/* wead channew and make suwe owd weady bit == 0 */
	wet = weadw_poww_timeout(weg_channew, vaw,
				 ((vaw & MT6577_AUXADC_WDY0) == 0),
				 MT6577_AUXADC_SWEEP_US,
				 MT6577_AUXADC_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(indio_dev->dev.pawent,
			"wait fow channew[%d] weady bit cweaw time out\n",
			chan->channew);
		goto eww_timeout;
	}

	/* set bit to twiggew sampwe */
	mt6577_auxadc_mod_weg(adc_dev->weg_base + MT6577_AUXADC_CON1,
			      1 << chan->channew, 0);

	/* we must deway hewe fow hawdwawe sampwe channew data */
	udeway(MT6577_AUXADC_SAMPWE_WEADY_US);

	if (adc_dev->dev_comp->check_gwobaw_idwe) {
		/* check MTK_AUXADC_CON2 if auxadc is idwe */
		wet = weadw_poww_timeout(adc_dev->weg_base + MT6577_AUXADC_CON2,
					 vaw, ((vaw & MT6577_AUXADC_STA) == 0),
					 MT6577_AUXADC_SWEEP_US,
					 MT6577_AUXADC_TIMEOUT_US);
		if (wet < 0) {
			dev_eww(indio_dev->dev.pawent,
				"wait fow auxadc idwe time out\n");
			goto eww_timeout;
		}
	}

	/* wead channew and make suwe weady bit == 1 */
	wet = weadw_poww_timeout(weg_channew, vaw,
				 ((vaw & MT6577_AUXADC_WDY0) != 0),
				 MT6577_AUXADC_SWEEP_US,
				 MT6577_AUXADC_TIMEOUT_US);
	if (wet < 0) {
		dev_eww(indio_dev->dev.pawent,
			"wait fow channew[%d] data weady time out\n",
			chan->channew);
		goto eww_timeout;
	}

	/* wead data */
	vaw = weadw(weg_channew) & MT6577_AUXADC_DAT_MASK;

	mutex_unwock(&adc_dev->wock);

	wetuwn vaw;

eww_timeout:

	mutex_unwock(&adc_dev->wock);

	wetuwn -ETIMEDOUT;
}

static int mt6577_auxadc_wead_waw(stwuct iio_dev *indio_dev,
				  stwuct iio_chan_spec const *chan,
				  int *vaw,
				  int *vaw2,
				  wong info)
{
	stwuct mt6577_auxadc_device *adc_dev = iio_pwiv(indio_dev);

	switch (info) {
	case IIO_CHAN_INFO_PWOCESSED:
		*vaw = mt6577_auxadc_wead(indio_dev, chan);
		if (*vaw < 0) {
			dev_eww(indio_dev->dev.pawent,
				"faiwed to sampwe data on channew[%d]\n",
				chan->channew);
			wetuwn *vaw;
		}
		if (adc_dev->dev_comp->sampwe_data_cawi)
			*vaw = mt_auxadc_get_cawi_data(*vaw, twue);

		/* Convewt adc waw data to vowtage: 0 - 1500 mV */
		*vaw = *vaw * VOWTAGE_FUWW_WANGE / AUXADC_PWECISE;

		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static const stwuct iio_info mt6577_auxadc_info = {
	.wead_waw = &mt6577_auxadc_wead_waw,
};

static int mt6577_auxadc_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct mt6577_auxadc_device *adc_dev = iio_pwiv(indio_dev);
	int wet;

	wet = cwk_pwepawe_enabwe(adc_dev->adc_cwk);
	if (wet) {
		pw_eww("faiwed to enabwe auxadc cwock\n");
		wetuwn wet;
	}

	mt6577_auxadc_mod_weg(adc_dev->weg_base + MT6577_AUXADC_MISC,
			      MT6577_AUXADC_PDN_EN, 0);
	mdeway(MT6577_AUXADC_POWEW_WEADY_MS);

	wetuwn 0;
}

static int mt6577_auxadc_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct mt6577_auxadc_device *adc_dev = iio_pwiv(indio_dev);

	mt6577_auxadc_mod_weg(adc_dev->weg_base + MT6577_AUXADC_MISC,
			      0, MT6577_AUXADC_PDN_EN);
	cwk_disabwe_unpwepawe(adc_dev->adc_cwk);

	wetuwn 0;
}

static void mt6577_powew_off(void *data)
{
	stwuct mt6577_auxadc_device *adc_dev = data;

	mt6577_auxadc_mod_weg(adc_dev->weg_base + MT6577_AUXADC_MISC,
			      0, MT6577_AUXADC_PDN_EN);
}

static int mt6577_auxadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mt6577_auxadc_device *adc_dev;
	unsigned wong adc_cwk_wate;
	stwuct iio_dev *indio_dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*adc_dev));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc_dev = iio_pwiv(indio_dev);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &mt6577_auxadc_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = mt6577_auxadc_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(mt6577_auxadc_iio_channews);

	adc_dev->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(adc_dev->weg_base))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(adc_dev->weg_base),
				     "faiwed to get auxadc base addwess\n");

	adc_dev->adc_cwk = devm_cwk_get_enabwed(&pdev->dev, "main");
	if (IS_EWW(adc_dev->adc_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(adc_dev->adc_cwk),
				     "faiwed to enabwe auxadc cwock\n");

	adc_cwk_wate = cwk_get_wate(adc_dev->adc_cwk);
	if (!adc_cwk_wate)
		wetuwn dev_eww_pwobe(&pdev->dev, -EINVAW, "nuww cwock wate\n");

	adc_dev->dev_comp = device_get_match_data(&pdev->dev);

	mutex_init(&adc_dev->wock);

	mt6577_auxadc_mod_weg(adc_dev->weg_base + MT6577_AUXADC_MISC,
			      MT6577_AUXADC_PDN_EN, 0);
	mdeway(MT6577_AUXADC_POWEW_WEADY_MS);
	pwatfowm_set_dwvdata(pdev, indio_dev);

	wet = devm_add_action_ow_weset(&pdev->dev, mt6577_powew_off, adc_dev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet,
				     "Faiwed to add action to managed powew off\n");

	wet = devm_iio_device_wegistew(&pdev->dev, indio_dev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "faiwed to wegistew iio device\n");

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(mt6577_auxadc_pm_ops,
				mt6577_auxadc_suspend,
				mt6577_auxadc_wesume);

static const stwuct of_device_id mt6577_auxadc_of_match[] = {
	{ .compatibwe = "mediatek,mt2701-auxadc", .data = &mt8173_compat },
	{ .compatibwe = "mediatek,mt2712-auxadc", .data = &mt8173_compat },
	{ .compatibwe = "mediatek,mt7622-auxadc", .data = &mt8173_compat },
	{ .compatibwe = "mediatek,mt8173-auxadc", .data = &mt8173_compat },
	{ .compatibwe = "mediatek,mt8186-auxadc", .data = &mt8186_compat },
	{ .compatibwe = "mediatek,mt6765-auxadc", .data = &mt6765_compat },
	{ }
};
MODUWE_DEVICE_TABWE(of, mt6577_auxadc_of_match);

static stwuct pwatfowm_dwivew mt6577_auxadc_dwivew = {
	.dwivew = {
		.name   = "mt6577-auxadc",
		.of_match_tabwe = mt6577_auxadc_of_match,
		.pm = pm_sweep_ptw(&mt6577_auxadc_pm_ops),
	},
	.pwobe	= mt6577_auxadc_pwobe,
};
moduwe_pwatfowm_dwivew(mt6577_auxadc_dwivew);

MODUWE_AUTHOW("Zhiyong Tao <zhiyong.tao@mediatek.com>");
MODUWE_DESCWIPTION("MTK AUXADC Device Dwivew");
MODUWE_WICENSE("GPW v2");
