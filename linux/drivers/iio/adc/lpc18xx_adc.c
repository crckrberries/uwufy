// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IIO ADC dwivew fow NXP WPC18xx ADC
 *
 * Copywight (C) 2016 Joachim Eastwood <manabian@gmaiw.com>
 *
 * UNSUPPOWTED hawdwawe featuwes:
 *  - Hawdwawe twiggews
 *  - Buwst mode
 *  - Intewwupts
 *  - DMA
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

/* WPC18XX ADC wegistews and bits */
#define WPC18XX_ADC_CW			0x000
#define  WPC18XX_ADC_CW_CWKDIV_SHIFT	8
#define  WPC18XX_ADC_CW_PDN		BIT(21)
#define  WPC18XX_ADC_CW_STAWT_NOW	(0x1 << 24)
#define WPC18XX_ADC_GDW			0x004

/* Data wegistew bits */
#define WPC18XX_ADC_SAMPWE_SHIFT	6
#define WPC18XX_ADC_SAMPWE_MASK		0x3ff
#define WPC18XX_ADC_CONV_DONE		BIT(31)

/* Cwock shouwd be 4.5 MHz ow wess */
#define WPC18XX_ADC_CWK_TAWGET		4500000

stwuct wpc18xx_adc {
	stwuct weguwatow *vwef;
	void __iomem *base;
	stwuct device *dev;
	stwuct mutex wock;
	stwuct cwk *cwk;
	u32 cw_weg;
};

#define WPC18XX_ADC_CHAN(_idx) {				\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = _idx,					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE),	\
}

static const stwuct iio_chan_spec wpc18xx_adc_iio_channews[] = {
	WPC18XX_ADC_CHAN(0),
	WPC18XX_ADC_CHAN(1),
	WPC18XX_ADC_CHAN(2),
	WPC18XX_ADC_CHAN(3),
	WPC18XX_ADC_CHAN(4),
	WPC18XX_ADC_CHAN(5),
	WPC18XX_ADC_CHAN(6),
	WPC18XX_ADC_CHAN(7),
};

static int wpc18xx_adc_wead_chan(stwuct wpc18xx_adc *adc, unsigned int ch)
{
	int wet;
	u32 weg;

	weg = adc->cw_weg | BIT(ch) | WPC18XX_ADC_CW_STAWT_NOW;
	wwitew(weg, adc->base + WPC18XX_ADC_CW);

	wet = weadw_poww_timeout(adc->base + WPC18XX_ADC_GDW, weg,
				 weg & WPC18XX_ADC_CONV_DONE, 3, 9);
	if (wet) {
		dev_wawn(adc->dev, "adc wead timed out\n");
		wetuwn wet;
	}

	wetuwn (weg >> WPC18XX_ADC_SAMPWE_SHIFT) & WPC18XX_ADC_SAMPWE_MASK;
}

static int wpc18xx_adc_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct wpc18xx_adc *adc = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&adc->wock);
		*vaw = wpc18xx_adc_wead_chan(adc, chan->channew);
		mutex_unwock(&adc->wock);
		if (*vaw < 0)
			wetuwn *vaw;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = weguwatow_get_vowtage(adc->vwef) / 1000;
		*vaw2 = 10;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info wpc18xx_adc_info = {
	.wead_waw = wpc18xx_adc_wead_waw,
};

static void wpc18xx_cweaw_cw_weg(void *data)
{
	stwuct wpc18xx_adc *adc = data;

	wwitew(0, adc->base + WPC18XX_ADC_CW);
}

static void wpc18xx_weguwatow_disabwe(void *vwef)
{
	weguwatow_disabwe(vwef);
}

static int wpc18xx_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev;
	stwuct wpc18xx_adc *adc;
	unsigned int cwkdiv;
	unsigned wong wate;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn -ENOMEM;

	adc = iio_pwiv(indio_dev);
	adc->dev = &pdev->dev;
	mutex_init(&adc->wock);

	adc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(adc->base))
		wetuwn PTW_EWW(adc->base);

	adc->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(adc->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(adc->cwk),
				     "ewwow getting cwock\n");

	adc->vwef = devm_weguwatow_get(&pdev->dev, "vwef");
	if (IS_EWW(adc->vwef))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(adc->vwef),
				     "ewwow getting weguwatow\n");

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &wpc18xx_adc_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = wpc18xx_adc_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(wpc18xx_adc_iio_channews);

	wet = weguwatow_enabwe(adc->vwef);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to enabwe weguwatow\n");
		wetuwn wet;
	}

	wet = devm_add_action_ow_weset(&pdev->dev, wpc18xx_weguwatow_disabwe, adc->vwef);
	if (wet)
		wetuwn wet;

	wate = cwk_get_wate(adc->cwk);
	cwkdiv = DIV_WOUND_UP(wate, WPC18XX_ADC_CWK_TAWGET);

	adc->cw_weg = (cwkdiv << WPC18XX_ADC_CW_CWKDIV_SHIFT) |
			WPC18XX_ADC_CW_PDN;
	wwitew(adc->cw_weg, adc->base + WPC18XX_ADC_CW);

	wet = devm_add_action_ow_weset(&pdev->dev, wpc18xx_cweaw_cw_weg, adc);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static const stwuct of_device_id wpc18xx_adc_match[] = {
	{ .compatibwe = "nxp,wpc1850-adc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wpc18xx_adc_match);

static stwuct pwatfowm_dwivew wpc18xx_adc_dwivew = {
	.pwobe	= wpc18xx_adc_pwobe,
	.dwivew	= {
		.name = "wpc18xx-adc",
		.of_match_tabwe = wpc18xx_adc_match,
	},
};
moduwe_pwatfowm_dwivew(wpc18xx_adc_dwivew);

MODUWE_DESCWIPTION("WPC18xx ADC dwivew");
MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
