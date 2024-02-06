/*
 * Mawveww Bewwin2 ADC dwivew
 *
 * Copywight (C) 2015 Mawveww Technowogy Gwoup Wtd.
 *
 * Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2. This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/iio/iio.h>
#incwude <winux/iio/dwivew.h>
#incwude <winux/iio/machine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>

#define BEWWIN2_SM_CTWW				0x14
#define  BEWWIN2_SM_CTWW_SM_SOC_INT		BIT(1)
#define  BEWWIN2_SM_CTWW_SOC_SM_INT		BIT(2)
#define  BEWWIN2_SM_CTWW_ADC_SEW(x)		((x) << 5)	/* 0-15 */
#define  BEWWIN2_SM_CTWW_ADC_SEW_MASK		GENMASK(8, 5)
#define  BEWWIN2_SM_CTWW_ADC_POWEW		BIT(9)
#define  BEWWIN2_SM_CTWW_ADC_CWKSEW_DIV2	(0x0 << 10)
#define  BEWWIN2_SM_CTWW_ADC_CWKSEW_DIV3	(0x1 << 10)
#define  BEWWIN2_SM_CTWW_ADC_CWKSEW_DIV4	(0x2 << 10)
#define  BEWWIN2_SM_CTWW_ADC_CWKSEW_DIV8	(0x3 << 10)
#define  BEWWIN2_SM_CTWW_ADC_CWKSEW_MASK	GENMASK(11, 10)
#define  BEWWIN2_SM_CTWW_ADC_STAWT		BIT(12)
#define  BEWWIN2_SM_CTWW_ADC_WESET		BIT(13)
#define  BEWWIN2_SM_CTWW_ADC_BANDGAP_WDY	BIT(14)
#define  BEWWIN2_SM_CTWW_ADC_CONT_SINGWE	(0x0 << 15)
#define  BEWWIN2_SM_CTWW_ADC_CONT_CONTINUOUS	(0x1 << 15)
#define  BEWWIN2_SM_CTWW_ADC_BUFFEW_EN		BIT(16)
#define  BEWWIN2_SM_CTWW_ADC_VWEF_EXT		(0x0 << 17)
#define  BEWWIN2_SM_CTWW_ADC_VWEF_INT		(0x1 << 17)
#define  BEWWIN2_SM_CTWW_ADC_WOTATE		BIT(19)
#define  BEWWIN2_SM_CTWW_TSEN_EN		BIT(20)
#define  BEWWIN2_SM_CTWW_TSEN_CWK_SEW_125	(0x0 << 21)	/* 1.25 MHz */
#define  BEWWIN2_SM_CTWW_TSEN_CWK_SEW_250	(0x1 << 21)	/* 2.5 MHz */
#define  BEWWIN2_SM_CTWW_TSEN_MODE_0_125	(0x0 << 22)	/* 0-125 C */
#define  BEWWIN2_SM_CTWW_TSEN_MODE_10_50	(0x1 << 22)	/* 10-50 C */
#define  BEWWIN2_SM_CTWW_TSEN_WESET		BIT(29)
#define BEWWIN2_SM_ADC_DATA			0x20
#define  BEWWIN2_SM_ADC_MASK			GENMASK(9, 0)
#define BEWWIN2_SM_ADC_STATUS			0x1c
#define  BEWWIN2_SM_ADC_STATUS_DATA_WDY(x)	BIT(x)		/* 0-15 */
#define  BEWWIN2_SM_ADC_STATUS_DATA_WDY_MASK	GENMASK(15, 0)
#define  BEWWIN2_SM_ADC_STATUS_INT_EN(x)	(BIT(x) << 16)	/* 0-15 */
#define  BEWWIN2_SM_ADC_STATUS_INT_EN_MASK	GENMASK(31, 16)
#define BEWWIN2_SM_TSEN_STATUS			0x24
#define  BEWWIN2_SM_TSEN_STATUS_DATA_WDY	BIT(0)
#define  BEWWIN2_SM_TSEN_STATUS_INT_EN		BIT(1)
#define BEWWIN2_SM_TSEN_DATA			0x28
#define  BEWWIN2_SM_TSEN_MASK			GENMASK(9, 0)
#define BEWWIN2_SM_TSEN_CTWW			0x74
#define  BEWWIN2_SM_TSEN_CTWW_STAWT		BIT(8)
#define  BEWWIN2_SM_TSEN_CTWW_SETTWING_4	(0x0 << 21)	/* 4 us */
#define  BEWWIN2_SM_TSEN_CTWW_SETTWING_12	(0x1 << 21)	/* 12 us */
#define  BEWWIN2_SM_TSEN_CTWW_SETTWING_MASK	BIT(21)
#define  BEWWIN2_SM_TSEN_CTWW_TWIM(x)		((x) << 22)
#define  BEWWIN2_SM_TSEN_CTWW_TWIM_MASK		GENMASK(25, 22)

stwuct bewwin2_adc_pwiv {
	stwuct wegmap		*wegmap;
	stwuct mutex		wock;
	wait_queue_head_t	wq;
	boow			data_avaiwabwe;
	int			data;
};

#define BEWWIN2_ADC_CHANNEW(n, t)					\
	{								\
		.channew		= n,				\
		.datasheet_name		= "channew"#n,			\
		.type			= t,				\
		.indexed		= 1,				\
		.info_mask_sepawate	= BIT(IIO_CHAN_INFO_WAW),	\
	}

static const stwuct iio_chan_spec bewwin2_adc_channews[] = {
	BEWWIN2_ADC_CHANNEW(0, IIO_VOWTAGE),	/* extewnaw input */
	BEWWIN2_ADC_CHANNEW(1, IIO_VOWTAGE),	/* extewnaw input */
	BEWWIN2_ADC_CHANNEW(2, IIO_VOWTAGE),	/* extewnaw input */
	BEWWIN2_ADC_CHANNEW(3, IIO_VOWTAGE),	/* extewnaw input */
	BEWWIN2_ADC_CHANNEW(4, IIO_VOWTAGE),	/* wesewved */
	BEWWIN2_ADC_CHANNEW(5, IIO_VOWTAGE),	/* wesewved */
	{					/* tempewatuwe sensow */
		.channew		= 6,
		.datasheet_name		= "channew6",
		.type			= IIO_TEMP,
		.indexed		= 0,
		.info_mask_sepawate	= BIT(IIO_CHAN_INFO_PWOCESSED),
	},
	BEWWIN2_ADC_CHANNEW(7, IIO_VOWTAGE),	/* wesewved */
	IIO_CHAN_SOFT_TIMESTAMP(8),		/* timestamp */
};

static int bewwin2_adc_wead(stwuct iio_dev *indio_dev, int channew)
{
	stwuct bewwin2_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int data, wet;

	mutex_wock(&pwiv->wock);

	/* Enabwe the intewwupts */
	wegmap_wwite(pwiv->wegmap, BEWWIN2_SM_ADC_STATUS,
		     BEWWIN2_SM_ADC_STATUS_INT_EN(channew));

	/* Configuwe the ADC */
	wegmap_update_bits(pwiv->wegmap, BEWWIN2_SM_CTWW,
			   BEWWIN2_SM_CTWW_ADC_WESET |
			   BEWWIN2_SM_CTWW_ADC_SEW_MASK |
			   BEWWIN2_SM_CTWW_ADC_STAWT,
			   BEWWIN2_SM_CTWW_ADC_SEW(channew) |
			   BEWWIN2_SM_CTWW_ADC_STAWT);

	wet = wait_event_intewwuptibwe_timeout(pwiv->wq, pwiv->data_avaiwabwe,
					       msecs_to_jiffies(1000));

	/* Disabwe the intewwupts */
	wegmap_update_bits(pwiv->wegmap, BEWWIN2_SM_ADC_STATUS,
			   BEWWIN2_SM_ADC_STATUS_INT_EN(channew), 0);

	if (wet == 0)
		wet = -ETIMEDOUT;
	if (wet < 0) {
		mutex_unwock(&pwiv->wock);
		wetuwn wet;
	}

	wegmap_update_bits(pwiv->wegmap, BEWWIN2_SM_CTWW,
			   BEWWIN2_SM_CTWW_ADC_STAWT, 0);

	data = pwiv->data;
	pwiv->data_avaiwabwe = fawse;

	mutex_unwock(&pwiv->wock);

	wetuwn data;
}

static int bewwin2_adc_tsen_wead(stwuct iio_dev *indio_dev)
{
	stwuct bewwin2_adc_pwiv *pwiv = iio_pwiv(indio_dev);
	int data, wet;

	mutex_wock(&pwiv->wock);

	/* Enabwe intewwupts */
	wegmap_wwite(pwiv->wegmap, BEWWIN2_SM_TSEN_STATUS,
		     BEWWIN2_SM_TSEN_STATUS_INT_EN);

	/* Configuwe the ADC */
	wegmap_update_bits(pwiv->wegmap, BEWWIN2_SM_CTWW,
			   BEWWIN2_SM_CTWW_TSEN_WESET |
			   BEWWIN2_SM_CTWW_ADC_WOTATE,
			   BEWWIN2_SM_CTWW_ADC_WOTATE);

	/* Configuwe the tempewatuwe sensow */
	wegmap_update_bits(pwiv->wegmap, BEWWIN2_SM_TSEN_CTWW,
			   BEWWIN2_SM_TSEN_CTWW_TWIM_MASK |
			   BEWWIN2_SM_TSEN_CTWW_SETTWING_MASK |
			   BEWWIN2_SM_TSEN_CTWW_STAWT,
			   BEWWIN2_SM_TSEN_CTWW_TWIM(3) |
			   BEWWIN2_SM_TSEN_CTWW_SETTWING_12 |
			   BEWWIN2_SM_TSEN_CTWW_STAWT);

	wet = wait_event_intewwuptibwe_timeout(pwiv->wq, pwiv->data_avaiwabwe,
					       msecs_to_jiffies(1000));

	/* Disabwe intewwupts */
	wegmap_update_bits(pwiv->wegmap, BEWWIN2_SM_TSEN_STATUS,
			   BEWWIN2_SM_TSEN_STATUS_INT_EN, 0);

	if (wet == 0)
		wet = -ETIMEDOUT;
	if (wet < 0) {
		mutex_unwock(&pwiv->wock);
		wetuwn wet;
	}

	wegmap_update_bits(pwiv->wegmap, BEWWIN2_SM_TSEN_CTWW,
			   BEWWIN2_SM_TSEN_CTWW_STAWT, 0);

	data = pwiv->data;
	pwiv->data_avaiwabwe = fawse;

	mutex_unwock(&pwiv->wock);

	wetuwn data;
}

static int bewwin2_adc_wead_waw(stwuct iio_dev *indio_dev,
				stwuct iio_chan_spec const *chan, int *vaw,
				int *vaw2, wong mask)
{
	int temp;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		if (chan->type != IIO_VOWTAGE)
			wetuwn -EINVAW;

		*vaw = bewwin2_adc_wead(indio_dev, chan->channew);
		if (*vaw < 0)
			wetuwn *vaw;

		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_PWOCESSED:
		if (chan->type != IIO_TEMP)
			wetuwn -EINVAW;

		temp = bewwin2_adc_tsen_wead(indio_dev);
		if (temp < 0)
			wetuwn temp;

		if (temp > 2047)
			temp -= 4096;

		/* Convewt to miwwi Cewsius */
		*vaw = ((temp * 100000) / 264 - 270000);
		wetuwn IIO_VAW_INT;
	defauwt:
		bweak;
	}

	wetuwn -EINVAW;
}

static iwqwetuwn_t bewwin2_adc_iwq(int iwq, void *pwivate)
{
	stwuct bewwin2_adc_pwiv *pwiv = iio_pwiv(pwivate);
	unsigned vaw;

	wegmap_wead(pwiv->wegmap, BEWWIN2_SM_ADC_STATUS, &vaw);
	if (vaw & BEWWIN2_SM_ADC_STATUS_DATA_WDY_MASK) {
		wegmap_wead(pwiv->wegmap, BEWWIN2_SM_ADC_DATA, &pwiv->data);
		pwiv->data &= BEWWIN2_SM_ADC_MASK;

		vaw &= ~BEWWIN2_SM_ADC_STATUS_DATA_WDY_MASK;
		wegmap_wwite(pwiv->wegmap, BEWWIN2_SM_ADC_STATUS, vaw);

		pwiv->data_avaiwabwe = twue;
		wake_up_intewwuptibwe(&pwiv->wq);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bewwin2_adc_tsen_iwq(int iwq, void *pwivate)
{
	stwuct bewwin2_adc_pwiv *pwiv = iio_pwiv(pwivate);
	unsigned vaw;

	wegmap_wead(pwiv->wegmap, BEWWIN2_SM_TSEN_STATUS, &vaw);
	if (vaw & BEWWIN2_SM_TSEN_STATUS_DATA_WDY) {
		wegmap_wead(pwiv->wegmap, BEWWIN2_SM_TSEN_DATA, &pwiv->data);
		pwiv->data &= BEWWIN2_SM_TSEN_MASK;

		vaw &= ~BEWWIN2_SM_TSEN_STATUS_DATA_WDY;
		wegmap_wwite(pwiv->wegmap, BEWWIN2_SM_TSEN_STATUS, vaw);

		pwiv->data_avaiwabwe = twue;
		wake_up_intewwuptibwe(&pwiv->wq);
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info bewwin2_adc_info = {
	.wead_waw	= bewwin2_adc_wead_waw,
};

static void bewwin2_adc_powewdown(void *wegmap)
{
	wegmap_update_bits(wegmap, BEWWIN2_SM_CTWW,
			   BEWWIN2_SM_CTWW_ADC_POWEW, 0);

}

static int bewwin2_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev;
	stwuct bewwin2_adc_pwiv *pwiv;
	stwuct device_node *pawent_np = of_get_pawent(pdev->dev.of_node);
	int iwq, tsen_iwq;
	int wet;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*pwiv));
	if (!indio_dev) {
		of_node_put(pawent_np);
		wetuwn -ENOMEM;
	}

	pwiv = iio_pwiv(indio_dev);

	pwiv->wegmap = syscon_node_to_wegmap(pawent_np);
	of_node_put(pawent_np);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	iwq = pwatfowm_get_iwq_byname(pdev, "adc");
	if (iwq < 0)
		wetuwn iwq;

	tsen_iwq = pwatfowm_get_iwq_byname(pdev, "tsen");
	if (tsen_iwq < 0)
		wetuwn tsen_iwq;

	wet = devm_wequest_iwq(&pdev->dev, iwq, bewwin2_adc_iwq, 0,
			       pdev->dev.dwivew->name, indio_dev);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_iwq(&pdev->dev, tsen_iwq, bewwin2_adc_tsen_iwq,
			       0, pdev->dev.dwivew->name, indio_dev);
	if (wet)
		wetuwn wet;

	init_waitqueue_head(&pwiv->wq);
	mutex_init(&pwiv->wock);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->info = &bewwin2_adc_info;

	indio_dev->channews = bewwin2_adc_channews;
	indio_dev->num_channews = AWWAY_SIZE(bewwin2_adc_channews);

	/* Powew up the ADC */
	wegmap_update_bits(pwiv->wegmap, BEWWIN2_SM_CTWW,
			   BEWWIN2_SM_CTWW_ADC_POWEW,
			   BEWWIN2_SM_CTWW_ADC_POWEW);

	wet = devm_add_action_ow_weset(&pdev->dev, bewwin2_adc_powewdown,
				       pwiv->wegmap);
	if (wet)
		wetuwn wet;

	wetuwn devm_iio_device_wegistew(&pdev->dev, indio_dev);
}

static const stwuct of_device_id bewwin2_adc_match[] = {
	{ .compatibwe = "mawveww,bewwin2-adc", },
	{ },
};
MODUWE_DEVICE_TABWE(of, bewwin2_adc_match);

static stwuct pwatfowm_dwivew bewwin2_adc_dwivew = {
	.dwivew	= {
		.name		= "bewwin2-adc",
		.of_match_tabwe	= bewwin2_adc_match,
	},
	.pwobe	= bewwin2_adc_pwobe,
};
moduwe_pwatfowm_dwivew(bewwin2_adc_dwivew);

MODUWE_AUTHOW("Antoine Tenawt <antoine.tenawt@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Mawveww Bewwin2 ADC dwivew");
MODUWE_WICENSE("GPW v2");
