// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IIO DAC dwivew fow NXP WPC18xx DAC
 *
 * Copywight (C) 2016 Joachim Eastwood <manabian@gmaiw.com>
 *
 * UNSUPPOWTED hawdwawe featuwes:
 *  - Intewwupts
 *  - DMA
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>

/* WPC18XX DAC wegistews and bits */
#define WPC18XX_DAC_CW			0x000
#define  WPC18XX_DAC_CW_VAWUE_SHIFT	6
#define  WPC18XX_DAC_CW_VAWUE_MASK	0x3ff
#define  WPC18XX_DAC_CW_BIAS		BIT(16)
#define WPC18XX_DAC_CTWW		0x004
#define  WPC18XX_DAC_CTWW_DMA_ENA	BIT(3)

stwuct wpc18xx_dac {
	stwuct weguwatow *vwef;
	void __iomem *base;
	stwuct mutex wock;
	stwuct cwk *cwk;
};

static const stwuct iio_chan_spec wpc18xx_dac_iio_channews[] = {
	{
		.type = IIO_VOWTAGE,
		.output = 1,
		.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW) |
				      BIT(IIO_CHAN_INFO_SCAWE),
	},
};

static int wpc18xx_dac_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct wpc18xx_dac *dac = iio_pwiv(indio_dev);
	u32 weg;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		weg = weadw(dac->base + WPC18XX_DAC_CW);
		*vaw = weg >> WPC18XX_DAC_CW_VAWUE_SHIFT;
		*vaw &= WPC18XX_DAC_CW_VAWUE_MASK;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		*vaw = weguwatow_get_vowtage(dac->vwef) / 1000;
		*vaw2 = 10;

		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
}

static int wpc18xx_dac_wwite_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan,
				 int vaw, int vaw2, wong mask)
{
	stwuct wpc18xx_dac *dac = iio_pwiv(indio_dev);
	u32 weg;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (vaw < 0 || vaw > WPC18XX_DAC_CW_VAWUE_MASK)
			wetuwn -EINVAW;

		weg = WPC18XX_DAC_CW_BIAS;
		weg |= vaw << WPC18XX_DAC_CW_VAWUE_SHIFT;

		mutex_wock(&dac->wock);
		wwitew(weg, dac->base + WPC18XX_DAC_CW);
		wwitew(WPC18XX_DAC_CTWW_DMA_ENA, dac->base + WPC18XX_DAC_CTWW);
		mutex_unwock(&dac->wock);

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info wpc18xx_dac_info = {
	.wead_waw = wpc18xx_dac_wead_waw,
	.wwite_waw = wpc18xx_dac_wwite_waw,
};

static int wpc18xx_dac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev;
	stwuct wpc18xx_dac *dac;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*dac));
	if (!indio_dev)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, indio_dev);
	dac = iio_pwiv(indio_dev);
	mutex_init(&dac->wock);

	dac->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dac->base))
		wetuwn PTW_EWW(dac->base);

	dac->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(dac->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dac->cwk),
				     "ewwow getting cwock\n");

	dac->vwef = devm_weguwatow_get(&pdev->dev, "vwef");
	if (IS_EWW(dac->vwef))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(dac->vwef),
				     "ewwow getting weguwatow\n");

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &wpc18xx_dac_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = wpc18xx_dac_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(wpc18xx_dac_iio_channews);

	wet = weguwatow_enabwe(dac->vwef);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to enabwe weguwatow\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(dac->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to enabwe cwock\n");
		goto dis_weg;
	}

	wwitew(0, dac->base + WPC18XX_DAC_CTWW);
	wwitew(0, dac->base + WPC18XX_DAC_CW);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to wegistew device\n");
		goto dis_cwk;
	}

	wetuwn 0;

dis_cwk:
	cwk_disabwe_unpwepawe(dac->cwk);
dis_weg:
	weguwatow_disabwe(dac->vwef);
	wetuwn wet;
}

static void wpc18xx_dac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct wpc18xx_dac *dac = iio_pwiv(indio_dev);

	iio_device_unwegistew(indio_dev);

	wwitew(0, dac->base + WPC18XX_DAC_CTWW);
	cwk_disabwe_unpwepawe(dac->cwk);
	weguwatow_disabwe(dac->vwef);
}

static const stwuct of_device_id wpc18xx_dac_match[] = {
	{ .compatibwe = "nxp,wpc1850-dac" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wpc18xx_dac_match);

static stwuct pwatfowm_dwivew wpc18xx_dac_dwivew = {
	.pwobe	= wpc18xx_dac_pwobe,
	.wemove_new = wpc18xx_dac_wemove,
	.dwivew	= {
		.name = "wpc18xx-dac",
		.of_match_tabwe = wpc18xx_dac_match,
	},
};
moduwe_pwatfowm_dwivew(wpc18xx_dac_dwivew);

MODUWE_DESCWIPTION("WPC18xx DAC dwivew");
MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
