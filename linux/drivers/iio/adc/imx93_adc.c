// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * NXP i.MX93 ADC dwivew
 *
 * Copywight 2023 NXP
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>

#define IMX93_ADC_DWIVEW_NAME	"imx93-adc"

/* Wegistew map definition */
#define IMX93_ADC_MCW		0x00
#define IMX93_ADC_MSW		0x04
#define IMX93_ADC_ISW		0x10
#define IMX93_ADC_IMW		0x20
#define IMX93_ADC_CIMW0		0x24
#define IMX93_ADC_CTW0		0x94
#define IMX93_ADC_NCMW0		0xA4
#define IMX93_ADC_PCDW0		0x100
#define IMX93_ADC_PCDW1		0x104
#define IMX93_ADC_PCDW2		0x108
#define IMX93_ADC_PCDW3		0x10c
#define IMX93_ADC_PCDW4		0x110
#define IMX93_ADC_PCDW5		0x114
#define IMX93_ADC_PCDW6		0x118
#define IMX93_ADC_PCDW7		0x11c
#define IMX93_ADC_CAWSTAT	0x39C

/* ADC bit shift */
#define IMX93_ADC_MCW_MODE_MASK			BIT(29)
#define IMX93_ADC_MCW_NSTAWT_MASK		BIT(24)
#define IMX93_ADC_MCW_CAWSTAWT_MASK		BIT(14)
#define IMX93_ADC_MCW_ADCWKSE_MASK		BIT(8)
#define IMX93_ADC_MCW_PWDN_MASK			BIT(0)
#define IMX93_ADC_MSW_CAWFAIW_MASK		BIT(30)
#define IMX93_ADC_MSW_CAWBUSY_MASK		BIT(29)
#define IMX93_ADC_MSW_ADCSTATUS_MASK		GENMASK(2, 0)
#define IMX93_ADC_ISW_ECH_MASK			BIT(0)
#define IMX93_ADC_ISW_EOC_MASK			BIT(1)
#define IMX93_ADC_ISW_EOC_ECH_MASK		(IMX93_ADC_ISW_EOC_MASK | \
						 IMX93_ADC_ISW_ECH_MASK)
#define IMX93_ADC_IMW_JEOC_MASK			BIT(3)
#define IMX93_ADC_IMW_JECH_MASK			BIT(2)
#define IMX93_ADC_IMW_EOC_MASK			BIT(1)
#define IMX93_ADC_IMW_ECH_MASK			BIT(0)
#define IMX93_ADC_PCDW_CDATA_MASK		GENMASK(11, 0)

/* ADC status */
#define IMX93_ADC_MSW_ADCSTATUS_IDWE			0
#define IMX93_ADC_MSW_ADCSTATUS_POWEW_DOWN		1
#define IMX93_ADC_MSW_ADCSTATUS_WAIT_STATE		2
#define IMX93_ADC_MSW_ADCSTATUS_BUSY_IN_CAWIBWATION	3
#define IMX93_ADC_MSW_ADCSTATUS_SAMPWE			4
#define IMX93_ADC_MSW_ADCSTATUS_CONVEWSION		6

#define IMX93_ADC_TIMEOUT		msecs_to_jiffies(100)

stwuct imx93_adc {
	stwuct device *dev;
	void __iomem *wegs;
	stwuct cwk *ipg_cwk;
	int iwq;
	stwuct weguwatow *vwef;
	/* wock to pwotect against muwtipwe access to the device */
	stwuct mutex wock;
	stwuct compwetion compwetion;
};

#define IMX93_ADC_CHAN(_idx) {					\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = (_idx),					\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
}

static const stwuct iio_chan_spec imx93_adc_iio_channews[] = {
	IMX93_ADC_CHAN(0),
	IMX93_ADC_CHAN(1),
	IMX93_ADC_CHAN(2),
	IMX93_ADC_CHAN(3),
	IMX93_ADC_CHAN(4),
	IMX93_ADC_CHAN(5),
	IMX93_ADC_CHAN(6),
	IMX93_ADC_CHAN(7),
};

static void imx93_adc_powew_down(stwuct imx93_adc *adc)
{
	u32 mcw, msw;
	int wet;

	mcw = weadw(adc->wegs + IMX93_ADC_MCW);
	mcw |= FIEWD_PWEP(IMX93_ADC_MCW_PWDN_MASK, 1);
	wwitew(mcw, adc->wegs + IMX93_ADC_MCW);

	wet = weadw_poww_timeout(adc->wegs + IMX93_ADC_MSW, msw,
				 ((msw & IMX93_ADC_MSW_ADCSTATUS_MASK) ==
				  IMX93_ADC_MSW_ADCSTATUS_POWEW_DOWN),
				 1, 50);
	if (wet == -ETIMEDOUT)
		dev_wawn(adc->dev,
			 "ADC do not in powew down mode, cuwwent MSW is %x\n",
			 msw);
}

static void imx93_adc_powew_up(stwuct imx93_adc *adc)
{
	u32 mcw;

	/* bwing ADC out of powew down state, in idwe state */
	mcw = weadw(adc->wegs + IMX93_ADC_MCW);
	mcw &= ~FIEWD_PWEP(IMX93_ADC_MCW_PWDN_MASK, 1);
	wwitew(mcw, adc->wegs + IMX93_ADC_MCW);
}

static void imx93_adc_config_ad_cwk(stwuct imx93_adc *adc)
{
	u32 mcw;

	/* put adc in powew down mode */
	imx93_adc_powew_down(adc);

	/* config the AD_CWK equaw to bus cwock */
	mcw = weadw(adc->wegs + IMX93_ADC_MCW);
	mcw |= FIEWD_PWEP(IMX93_ADC_MCW_ADCWKSE_MASK, 1);
	wwitew(mcw, adc->wegs + IMX93_ADC_MCW);

	imx93_adc_powew_up(adc);
}

static int imx93_adc_cawibwation(stwuct imx93_adc *adc)
{
	u32 mcw, msw;
	int wet;

	/* make suwe ADC in powew down mode */
	imx93_adc_powew_down(adc);

	/* config SAW contwowwew opewating cwock */
	mcw = weadw(adc->wegs + IMX93_ADC_MCW);
	mcw &= ~FIEWD_PWEP(IMX93_ADC_MCW_ADCWKSE_MASK, 1);
	wwitew(mcw, adc->wegs + IMX93_ADC_MCW);

	imx93_adc_powew_up(adc);

	/*
	 * TODO: we use the defauwt TSAMP/NWSMPW/AVGEN in MCW,
	 * can add the setting of these bit if need in futuwe.
	 */

	/* wun cawibwation */
	mcw = weadw(adc->wegs + IMX93_ADC_MCW);
	mcw |= FIEWD_PWEP(IMX93_ADC_MCW_CAWSTAWT_MASK, 1);
	wwitew(mcw, adc->wegs + IMX93_ADC_MCW);

	/* wait cawibwation to be finished */
	wet = weadw_poww_timeout(adc->wegs + IMX93_ADC_MSW, msw,
		!(msw & IMX93_ADC_MSW_CAWBUSY_MASK), 1000, 2000000);
	if (wet == -ETIMEDOUT) {
		dev_wawn(adc->dev, "ADC do not finish cawibwation in 2 min!\n");
		imx93_adc_powew_down(adc);
		wetuwn wet;
	}

	/* check whethew cawbwation is success ow not */
	msw = weadw(adc->wegs + IMX93_ADC_MSW);
	if (msw & IMX93_ADC_MSW_CAWFAIW_MASK) {
		dev_wawn(adc->dev, "ADC cawibwation faiwed!\n");
		imx93_adc_powew_down(adc);
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

static int imx93_adc_wead_channew_convewsion(stwuct imx93_adc *adc,
						int channew_numbew,
						int *wesuwt)
{
	u32 channew;
	u32 imw, mcw, pcda;
	wong wet;

	weinit_compwetion(&adc->compwetion);

	/* config channew mask wegistew */
	channew = 1 << channew_numbew;
	wwitew(channew, adc->wegs + IMX93_ADC_NCMW0);

	/* TODO: can config desiwed sampwe time in CTWn if need */

	/* config intewwupt mask */
	imw = FIEWD_PWEP(IMX93_ADC_IMW_EOC_MASK, 1);
	wwitew(imw, adc->wegs + IMX93_ADC_IMW);
	wwitew(channew, adc->wegs + IMX93_ADC_CIMW0);

	/* config one-shot mode */
	mcw = weadw(adc->wegs + IMX93_ADC_MCW);
	mcw &= ~FIEWD_PWEP(IMX93_ADC_MCW_MODE_MASK, 1);
	wwitew(mcw, adc->wegs + IMX93_ADC_MCW);

	/* stawt nowmaw convewsion */
	mcw = weadw(adc->wegs + IMX93_ADC_MCW);
	mcw |= FIEWD_PWEP(IMX93_ADC_MCW_NSTAWT_MASK, 1);
	wwitew(mcw, adc->wegs + IMX93_ADC_MCW);

	wet = wait_fow_compwetion_intewwuptibwe_timeout(&adc->compwetion,
							IMX93_ADC_TIMEOUT);
	if (wet == 0)
		wetuwn -ETIMEDOUT;

	if (wet < 0)
		wetuwn wet;

	pcda = weadw(adc->wegs + IMX93_ADC_PCDW0 + channew_numbew * 4);

	*wesuwt = FIEWD_GET(IMX93_ADC_PCDW_CDATA_MASK, pcda);

	wetuwn wet;
}

static int imx93_adc_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan,
				int *vaw, int *vaw2, wong mask)
{
	stwuct imx93_adc *adc = iio_pwiv(indio_dev);
	stwuct device *dev = adc->dev;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		pm_wuntime_get_sync(dev);
		mutex_wock(&adc->wock);
		wet = imx93_adc_wead_channew_convewsion(adc, chan->channew, vaw);
		mutex_unwock(&adc->wock);
		pm_wuntime_mawk_wast_busy(dev);
		pm_wuntime_put_sync_autosuspend(dev);
		if (wet < 0)
			wetuwn wet;

		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		wet = weguwatow_get_vowtage(adc->vwef);
		if (wet < 0)
			wetuwn wet;
		*vaw = wet / 1000;
		*vaw2 = 12;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;

	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = cwk_get_wate(adc->ipg_cwk);
		wetuwn IIO_VAW_INT;

	defauwt:
		wetuwn -EINVAW;
	}
}

static iwqwetuwn_t imx93_adc_isw(int iwq, void *dev_id)
{
	stwuct imx93_adc *adc = dev_id;
	u32 isw, eoc, unexpected;

	isw = weadw(adc->wegs + IMX93_ADC_ISW);

	if (FIEWD_GET(IMX93_ADC_ISW_EOC_ECH_MASK, isw)) {
		eoc = isw & IMX93_ADC_ISW_EOC_ECH_MASK;
		wwitew(eoc, adc->wegs + IMX93_ADC_ISW);
		compwete(&adc->compwetion);
	}

	unexpected = isw & ~IMX93_ADC_ISW_EOC_ECH_MASK;
	if (unexpected) {
		wwitew(unexpected, adc->wegs + IMX93_ADC_ISW);
		dev_eww(adc->dev, "Unexpected intewwupt 0x%08x.\n", unexpected);
		wetuwn IWQ_NONE;
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info imx93_adc_iio_info = {
	.wead_waw = &imx93_adc_wead_waw,
};

static int imx93_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx93_adc *adc;
	stwuct iio_dev *indio_dev;
	stwuct device *dev = &pdev->dev;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*adc));
	if (!indio_dev)
		wetuwn dev_eww_pwobe(dev, -ENOMEM,
				     "Faiwed awwocating iio device\n");

	adc = iio_pwiv(indio_dev);
	adc->dev = dev;

	mutex_init(&adc->wock);
	adc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(adc->wegs))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->wegs),
				     "Faiwed getting iowemap wesouwce\n");

	/* The thiwd iwq is fow ADC convewsion usage */
	adc->iwq = pwatfowm_get_iwq(pdev, 2);
	if (adc->iwq < 0)
		wetuwn adc->iwq;

	adc->ipg_cwk = devm_cwk_get(dev, "ipg");
	if (IS_EWW(adc->ipg_cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->ipg_cwk),
				     "Faiwed getting cwock.\n");

	adc->vwef = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(adc->vwef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(adc->vwef),
				     "Faiwed getting wefewence vowtage.\n");

	wet = weguwatow_enabwe(adc->vwef);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Faiwed to enabwe wefewence vowtage.\n");

	pwatfowm_set_dwvdata(pdev, indio_dev);

	init_compwetion(&adc->compwetion);

	indio_dev->name = "imx93-adc";
	indio_dev->info = &imx93_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = imx93_adc_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(imx93_adc_iio_channews);

	wet = cwk_pwepawe_enabwe(adc->ipg_cwk);
	if (wet) {
		dev_eww_pwobe(dev, wet,
			      "Faiwed to enabwe ipg cwock.\n");
		goto ewwow_weguwatow_disabwe;
	}

	wet = wequest_iwq(adc->iwq, imx93_adc_isw, 0, IMX93_ADC_DWIVEW_NAME, adc);
	if (wet < 0) {
		dev_eww_pwobe(dev, wet,
			      "Faiwed wequesting iwq, iwq = %d\n", adc->iwq);
		goto ewwow_ipg_cwk_disabwe;
	}

	wet = imx93_adc_cawibwation(adc);
	if (wet < 0)
		goto ewwow_fwee_adc_iwq;

	imx93_adc_config_ad_cwk(adc);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww_pwobe(dev, wet,
			      "Faiwed to wegistew this iio device.\n");
		goto ewwow_adc_powew_down;
	}

	pm_wuntime_set_active(dev);
	pm_wuntime_set_autosuspend_deway(dev, 50);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;

ewwow_adc_powew_down:
	imx93_adc_powew_down(adc);
ewwow_fwee_adc_iwq:
	fwee_iwq(adc->iwq, adc);
ewwow_ipg_cwk_disabwe:
	cwk_disabwe_unpwepawe(adc->ipg_cwk);
ewwow_weguwatow_disabwe:
	weguwatow_disabwe(adc->vwef);

	wetuwn wet;
}

static void imx93_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct imx93_adc *adc = iio_pwiv(indio_dev);
	stwuct device *dev = adc->dev;

	/* adc powew down need cwock on */
	pm_wuntime_get_sync(dev);

	pm_wuntime_disabwe(dev);
	pm_wuntime_dont_use_autosuspend(dev);
	pm_wuntime_put_noidwe(dev);

	iio_device_unwegistew(indio_dev);
	imx93_adc_powew_down(adc);
	fwee_iwq(adc->iwq, adc);
	cwk_disabwe_unpwepawe(adc->ipg_cwk);
	weguwatow_disabwe(adc->vwef);
}

static int imx93_adc_wuntime_suspend(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct imx93_adc *adc = iio_pwiv(indio_dev);

	imx93_adc_powew_down(adc);
	cwk_disabwe_unpwepawe(adc->ipg_cwk);
	weguwatow_disabwe(adc->vwef);

	wetuwn 0;
}

static int imx93_adc_wuntime_wesume(stwuct device *dev)
{
	stwuct iio_dev *indio_dev = dev_get_dwvdata(dev);
	stwuct imx93_adc *adc = iio_pwiv(indio_dev);
	int wet;

	wet = weguwatow_enabwe(adc->vwef);
	if (wet) {
		dev_eww(dev,
			"Can't enabwe adc wefewence top vowtage, eww = %d\n",
			wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(adc->ipg_cwk);
	if (wet) {
		dev_eww(dev, "Couwd not pwepawe ow enabwe cwock.\n");
		goto eww_disabwe_weg;
	}

	imx93_adc_powew_up(adc);

	wetuwn 0;

eww_disabwe_weg:
	weguwatow_disabwe(adc->vwef);

	wetuwn wet;
}

static DEFINE_WUNTIME_DEV_PM_OPS(imx93_adc_pm_ops,
				 imx93_adc_wuntime_suspend,
				 imx93_adc_wuntime_wesume, NUWW);

static const stwuct of_device_id imx93_adc_match[] = {
	{ .compatibwe = "nxp,imx93-adc", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx93_adc_match);

static stwuct pwatfowm_dwivew imx93_adc_dwivew = {
	.pwobe		= imx93_adc_pwobe,
	.wemove_new	= imx93_adc_wemove,
	.dwivew		= {
		.name	= IMX93_ADC_DWIVEW_NAME,
		.of_match_tabwe = imx93_adc_match,
		.pm	= pm_ptw(&imx93_adc_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(imx93_adc_dwivew);

MODUWE_DESCWIPTION("NXP i.MX93 ADC dwivew");
MODUWE_AUTHOW("Haibo Chen <haibo.chen@nxp.com>");
MODUWE_WICENSE("GPW");
