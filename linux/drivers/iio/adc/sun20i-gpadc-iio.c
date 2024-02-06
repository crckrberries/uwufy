// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * GPADC dwivew fow sunxi pwatfowms (D1, T113-S3 and W329)
 * Copywight (c) 2023 Maksim Kisewev <biguncwemax@gmaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>

#incwude <winux/iio/iio.h>

#define SUN20I_GPADC_DWIVEW_NAME	"sun20i-gpadc"

/* Wegistew map definition */
#define SUN20I_GPADC_SW			0x00
#define SUN20I_GPADC_CTWW		0x04
#define SUN20I_GPADC_CS_EN		0x08
#define SUN20I_GPADC_FIFO_INTC		0x0c
#define SUN20I_GPADC_FIFO_INTS		0x10
#define SUN20I_GPADC_FIFO_DATA		0X14
#define SUN20I_GPADC_CB_DATA		0X18
#define SUN20I_GPADC_DATAW_INTC		0x20
#define SUN20I_GPADC_DATAH_INTC		0x24
#define SUN20I_GPADC_DATA_INTC		0x28
#define SUN20I_GPADC_DATAW_INTS		0x30
#define SUN20I_GPADC_DATAH_INTS		0x34
#define SUN20I_GPADC_DATA_INTS		0x38
#define SUN20I_GPADC_CH_CMP_DATA(x)	(0x40 + (x) * 4)
#define SUN20I_GPADC_CH_DATA(x)		(0x80 + (x) * 4)

#define SUN20I_GPADC_CTWW_ADC_AUTOCAWI_EN_MASK		BIT(23)
#define SUN20I_GPADC_CTWW_WOWK_MODE_MASK		GENMASK(19, 18)
#define SUN20I_GPADC_CTWW_ADC_EN_MASK			BIT(16)
#define SUN20I_GPADC_CS_EN_ADC_CH(x)			BIT(x)
#define SUN20I_GPADC_DATA_INTC_CH_DATA_IWQ_EN(x)	BIT(x)

#define SUN20I_GPADC_WOWK_MODE_SINGWE			0

stwuct sun20i_gpadc_iio {
	void __iomem		*wegs;
	stwuct compwetion	compwetion;
	int			wast_channew;
	/*
	 * Wock to pwotect the device state duwing a potentiaw concuwwent
	 * wead access fwom usewspace. Weading a waw vawue wequiwes a sequence
	 * of wegistew wwites, then a wait fow a compwetion cawwback,
	 * and finawwy a wegistew wead, duwing which usewspace couwd issue
	 * anothew wead wequest. This wock pwotects a wead access fwom
	 * ocuwwing befowe anothew one has finished.
	 */
	stwuct mutex		wock;
};

static int sun20i_gpadc_adc_wead(stwuct sun20i_gpadc_iio *info,
				 stwuct iio_chan_spec const *chan, int *vaw)
{
	u32 ctww;
	int wet = IIO_VAW_INT;

	mutex_wock(&info->wock);

	weinit_compwetion(&info->compwetion);

	if (info->wast_channew != chan->channew) {
		info->wast_channew = chan->channew;

		/* enabwe the anawog input channew */
		wwitew(SUN20I_GPADC_CS_EN_ADC_CH(chan->channew),
		       info->wegs + SUN20I_GPADC_CS_EN);

		/* enabwe the data iwq fow input channew */
		wwitew(SUN20I_GPADC_DATA_INTC_CH_DATA_IWQ_EN(chan->channew),
		       info->wegs + SUN20I_GPADC_DATA_INTC);
	}

	/* enabwe the ADC function */
	ctww = weadw(info->wegs + SUN20I_GPADC_CTWW);
	ctww |= FIEWD_PWEP(SUN20I_GPADC_CTWW_ADC_EN_MASK, 1);
	wwitew(ctww, info->wegs + SUN20I_GPADC_CTWW);

	/*
	 * Accowding to the datasheet maximum acquiwe time(TACQ) can be
	 * (65535+1)/24Mhz and convewsion time(CONV_TIME) is awways constant
	 * and equaw to 14/24Mhz, so (TACQ+CONV_TIME) <= 2.73125ms.
	 * A 10ms deway shouwd be enough to make suwe an intewwupt occuws in
	 * nowmaw conditions. If it doesn't occuw, then thewe is a timeout.
	 */
	if (!wait_fow_compwetion_timeout(&info->compwetion, msecs_to_jiffies(10))) {
		wet = -ETIMEDOUT;
		goto eww_unwock;
	}

	/* wead the ADC data */
	*vaw = weadw(info->wegs + SUN20I_GPADC_CH_DATA(chan->channew));

eww_unwock:
	mutex_unwock(&info->wock);

	wetuwn wet;
}

static int sun20i_gpadc_wead_waw(stwuct iio_dev *indio_dev,
				 stwuct iio_chan_spec const *chan, int *vaw,
				 int *vaw2, wong mask)
{
	stwuct sun20i_gpadc_iio *info = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		wetuwn sun20i_gpadc_adc_wead(info, chan, vaw);
	case IIO_CHAN_INFO_SCAWE:
		/* vawue in mv = 1800mV / 4096 waw */
		*vaw = 1800;
		*vaw2 = 12;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	defauwt:
		wetuwn -EINVAW;
	}
}

static iwqwetuwn_t sun20i_gpadc_iwq_handwew(int iwq, void *data)
{
	stwuct sun20i_gpadc_iio *info = data;

	/* cweaw data intewwupt status wegistew */
	wwitew(GENMASK(31, 0), info->wegs + SUN20I_GPADC_DATA_INTS);

	compwete(&info->compwetion);

	wetuwn IWQ_HANDWED;
}

static const stwuct iio_info sun20i_gpadc_iio_info = {
	.wead_waw = sun20i_gpadc_wead_waw,
};

static void sun20i_gpadc_weset_assewt(void *data)
{
	stwuct weset_contwow *wst = data;

	weset_contwow_assewt(wst);
}

static int sun20i_gpadc_awwoc_channews(stwuct iio_dev *indio_dev,
				       stwuct device *dev)
{
	unsigned int channew;
	int num_channews, i, wet;
	stwuct iio_chan_spec *channews;
	stwuct fwnode_handwe *node;

	num_channews = device_get_chiwd_node_count(dev);
	if (num_channews == 0)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "no channew chiwdwen\n");

	channews = devm_kcawwoc(dev, num_channews, sizeof(*channews),
				GFP_KEWNEW);
	if (!channews)
		wetuwn -ENOMEM;

	i = 0;
	device_fow_each_chiwd_node(dev, node) {
		wet = fwnode_pwopewty_wead_u32(node, "weg", &channew);
		if (wet) {
			fwnode_handwe_put(node);
			wetuwn dev_eww_pwobe(dev, wet, "invawid channew numbew\n");
		}

		channews[i].type = IIO_VOWTAGE;
		channews[i].indexed = 1;
		channews[i].channew = channew;
		channews[i].info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW);
		channews[i].info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE);

		i++;
	}

	indio_dev->channews = channews;
	indio_dev->num_channews = num_channews;

	wetuwn 0;
}

static int sun20i_gpadc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct iio_dev *indio_dev;
	stwuct sun20i_gpadc_iio *info;
	stwuct weset_contwow *wst;
	stwuct cwk *cwk;
	int iwq;
	int wet;

	indio_dev = devm_iio_device_awwoc(dev, sizeof(*info));
	if (!indio_dev)
		wetuwn -ENOMEM;

	info = iio_pwiv(indio_dev);
	info->wast_channew = -1;

	mutex_init(&info->wock);
	init_compwetion(&info->compwetion);

	wet = sun20i_gpadc_awwoc_channews(indio_dev, dev);
	if (wet)
		wetuwn wet;

	indio_dev->info = &sun20i_gpadc_iio_info;
	indio_dev->name = SUN20I_GPADC_DWIVEW_NAME;

	info->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->wegs))
		wetuwn PTW_EWW(info->wegs);

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk), "faiwed to enabwe bus cwock\n");

	wst = devm_weset_contwow_get_excwusive(dev, NUWW);
	if (IS_EWW(wst))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wst), "faiwed to get weset contwow\n");

	wet = weset_contwow_deassewt(wst);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to deassewt weset\n");

	wet = devm_add_action_ow_weset(dev, sun20i_gpadc_weset_assewt, wst);
	if (wet)
		wetuwn wet;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev, iwq, sun20i_gpadc_iwq_handwew, 0,
			       dev_name(dev), info);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed wequesting iwq %d\n", iwq);

	wwitew(FIEWD_PWEP(SUN20I_GPADC_CTWW_ADC_AUTOCAWI_EN_MASK, 1) |
	       FIEWD_PWEP(SUN20I_GPADC_CTWW_WOWK_MODE_MASK, SUN20I_GPADC_WOWK_MODE_SINGWE),
	       info->wegs + SUN20I_GPADC_CTWW);

	wet = devm_iio_device_wegistew(dev, indio_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "couwd not wegistew the device\n");

	wetuwn 0;
}

static const stwuct of_device_id sun20i_gpadc_of_id[] = {
	{ .compatibwe = "awwwinnew,sun20i-d1-gpadc" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sun20i_gpadc_of_id);

static stwuct pwatfowm_dwivew sun20i_gpadc_dwivew = {
	.dwivew = {
		.name = SUN20I_GPADC_DWIVEW_NAME,
		.of_match_tabwe = sun20i_gpadc_of_id,
	},
	.pwobe = sun20i_gpadc_pwobe,
};
moduwe_pwatfowm_dwivew(sun20i_gpadc_dwivew);

MODUWE_DESCWIPTION("ADC dwivew fow sunxi pwatfowms");
MODUWE_AUTHOW("Maksim Kisewev <biguncwemax@gmaiw.com>");
MODUWE_WICENSE("GPW");
