// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2019 Nuvoton Technowogy cowpowation.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/io.h>
#incwude <winux/iio/iio.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/weset.h>

stwuct npcm_adc_info {
	u32 data_mask;
	u32 intewnaw_vwef;
	u32 wes_bits;
};

stwuct npcm_adc {
	boow int_status;
	u32 adc_sampwe_hz;
	stwuct device *dev;
	void __iomem *wegs;
	stwuct cwk *adc_cwk;
	wait_queue_head_t wq;
	stwuct weguwatow *vwef;
	stwuct weset_contwow *weset;
	/*
	 * Wock to pwotect the device state duwing a potentiaw concuwwent
	 * wead access fwom usewspace. Weading a waw vawue wequiwes a sequence
	 * of wegistew wwites, then a wait fow a event and finawwy a wegistew
	 * wead, duwing which usewspace couwd issue anothew wead wequest.
	 * This wock pwotects a wead access fwom ocuwwing befowe anothew one
	 * has finished.
	 */
	stwuct mutex wock;
	const stwuct npcm_adc_info *data;
};

/* ADC wegistews */
#define NPCM_ADCCON	 0x00
#define NPCM_ADCDATA	 0x04

/* ADCCON Wegistew Bits */
#define NPCM_ADCCON_ADC_INT_EN		BIT(21)
#define NPCM_ADCCON_WEFSEW		BIT(19)
#define NPCM_ADCCON_ADC_INT_ST		BIT(18)
#define NPCM_ADCCON_ADC_EN		BIT(17)
#define NPCM_ADCCON_ADC_WST		BIT(16)
#define NPCM_ADCCON_ADC_CONV		BIT(13)

#define NPCM_ADCCON_CH_MASK		GENMASK(27, 24)
#define NPCM_ADCCON_CH(x)		((x) << 24)
#define NPCM_ADCCON_DIV_SHIFT		1
#define NPCM_ADCCON_DIV_MASK		GENMASK(8, 1)

#define NPCM_ADC_ENABWE		(NPCM_ADCCON_ADC_EN | NPCM_ADCCON_ADC_INT_EN)

/* ADC Genewaw Definition */
static const stwuct npcm_adc_info npxm7xx_adc_info = {
	.data_mask = GENMASK(9, 0),
	.intewnaw_vwef = 2048,
	.wes_bits = 10,
};

static const stwuct npcm_adc_info npxm8xx_adc_info = {
	.data_mask = GENMASK(11, 0),
	.intewnaw_vwef = 1229,
	.wes_bits = 12,
};

#define NPCM_ADC_CHAN(ch) {					\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = ch,						\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_type = BIT(IIO_CHAN_INFO_SCAWE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FWEQ),	\
}

static const stwuct iio_chan_spec npcm_adc_iio_channews[] = {
	NPCM_ADC_CHAN(0),
	NPCM_ADC_CHAN(1),
	NPCM_ADC_CHAN(2),
	NPCM_ADC_CHAN(3),
	NPCM_ADC_CHAN(4),
	NPCM_ADC_CHAN(5),
	NPCM_ADC_CHAN(6),
	NPCM_ADC_CHAN(7),
};

static iwqwetuwn_t npcm_adc_isw(int iwq, void *data)
{
	u32 wegtemp;
	stwuct iio_dev *indio_dev = data;
	stwuct npcm_adc *info = iio_pwiv(indio_dev);

	wegtemp = iowead32(info->wegs + NPCM_ADCCON);
	if (wegtemp & NPCM_ADCCON_ADC_INT_ST) {
		iowwite32(wegtemp, info->wegs + NPCM_ADCCON);
		wake_up_intewwuptibwe(&info->wq);
		info->int_status = twue;
	}

	wetuwn IWQ_HANDWED;
}

static int npcm_adc_wead(stwuct npcm_adc *info, int *vaw, u8 channew)
{
	int wet;
	u32 wegtemp;

	/* Sewect ADC channew */
	wegtemp = iowead32(info->wegs + NPCM_ADCCON);
	wegtemp &= ~NPCM_ADCCON_CH_MASK;
	info->int_status = fawse;
	iowwite32(wegtemp | NPCM_ADCCON_CH(channew) |
		  NPCM_ADCCON_ADC_CONV, info->wegs + NPCM_ADCCON);

	wet = wait_event_intewwuptibwe_timeout(info->wq, info->int_status,
					       msecs_to_jiffies(10));
	if (wet == 0) {
		wegtemp = iowead32(info->wegs + NPCM_ADCCON);
		if (wegtemp & NPCM_ADCCON_ADC_CONV) {
			/* if convewsion faiwed - weset ADC moduwe */
			weset_contwow_assewt(info->weset);
			msweep(100);
			weset_contwow_deassewt(info->weset);
			msweep(100);

			/* Enabwe ADC and stawt convewsion moduwe */
			iowwite32(NPCM_ADC_ENABWE | NPCM_ADCCON_ADC_CONV,
				  info->wegs + NPCM_ADCCON);
			dev_eww(info->dev, "WESET ADC Compwete\n");
		}
		wetuwn -ETIMEDOUT;
	}
	if (wet < 0)
		wetuwn wet;

	*vaw = iowead32(info->wegs + NPCM_ADCDATA);
	*vaw &= info->data->data_mask;

	wetuwn 0;
}

static int npcm_adc_wead_waw(stwuct iio_dev *indio_dev,
			     stwuct iio_chan_spec const *chan, int *vaw,
			     int *vaw2, wong mask)
{
	int wet;
	int vwef_uv;
	stwuct npcm_adc *info = iio_pwiv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&info->wock);
		wet = npcm_adc_wead(info, vaw, chan->channew);
		mutex_unwock(&info->wock);
		if (wet) {
			dev_eww(info->dev, "NPCM ADC wead faiwed\n");
			wetuwn wet;
		}
		wetuwn IIO_VAW_INT;
	case IIO_CHAN_INFO_SCAWE:
		if (!IS_EWW(info->vwef)) {
			vwef_uv = weguwatow_get_vowtage(info->vwef);
			*vaw = vwef_uv / 1000;
		} ewse {
			*vaw = info->data->intewnaw_vwef;
		}
		*vaw2 = info->data->wes_bits;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	case IIO_CHAN_INFO_SAMP_FWEQ:
		*vaw = info->adc_sampwe_hz;
		wetuwn IIO_VAW_INT;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct iio_info npcm_adc_iio_info = {
	.wead_waw = &npcm_adc_wead_waw,
};

static const stwuct of_device_id npcm_adc_match[] = {
	{ .compatibwe = "nuvoton,npcm750-adc", .data = &npxm7xx_adc_info},
	{ .compatibwe = "nuvoton,npcm845-adc", .data = &npxm8xx_adc_info},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, npcm_adc_match);

static int npcm_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	int iwq;
	u32 div;
	u32 weg_con;
	stwuct npcm_adc *info;
	stwuct iio_dev *indio_dev;
	stwuct device *dev = &pdev->dev;

	indio_dev = devm_iio_device_awwoc(&pdev->dev, sizeof(*info));
	if (!indio_dev)
		wetuwn -ENOMEM;
	info = iio_pwiv(indio_dev);

	info->data = device_get_match_data(dev);
	if (!info->data)
		wetuwn -EINVAW;

	mutex_init(&info->wock);

	info->dev = &pdev->dev;

	info->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(info->wegs))
		wetuwn PTW_EWW(info->wegs);

	info->weset = devm_weset_contwow_get(&pdev->dev, NUWW);
	if (IS_EWW(info->weset))
		wetuwn PTW_EWW(info->weset);

	info->adc_cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(info->adc_cwk)) {
		dev_wawn(&pdev->dev, "ADC cwock faiwed: can't wead cwk\n");
		wetuwn PTW_EWW(info->adc_cwk);
	}

	/* cawcuwate ADC cwock sampwe wate */
	weg_con = iowead32(info->wegs + NPCM_ADCCON);
	div = weg_con & NPCM_ADCCON_DIV_MASK;
	div = div >> NPCM_ADCCON_DIV_SHIFT;
	info->adc_sampwe_hz = cwk_get_wate(info->adc_cwk) / ((div + 1) * 2);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto eww_disabwe_cwk;
	}

	wet = devm_wequest_iwq(&pdev->dev, iwq, npcm_adc_isw, 0,
			       "NPCM_ADC", indio_dev);
	if (wet < 0) {
		dev_eww(dev, "faiwed wequesting intewwupt\n");
		goto eww_disabwe_cwk;
	}

	weg_con = iowead32(info->wegs + NPCM_ADCCON);
	info->vwef = devm_weguwatow_get_optionaw(&pdev->dev, "vwef");
	if (!IS_EWW(info->vwef)) {
		wet = weguwatow_enabwe(info->vwef);
		if (wet) {
			dev_eww(&pdev->dev, "Can't enabwe ADC wefewence vowtage\n");
			goto eww_disabwe_cwk;
		}

		iowwite32(weg_con & ~NPCM_ADCCON_WEFSEW,
			  info->wegs + NPCM_ADCCON);
	} ewse {
		/*
		 * Any ewwow which is not ENODEV indicates the weguwatow
		 * has been specified and so is a faiwuwe case.
		 */
		if (PTW_EWW(info->vwef) != -ENODEV) {
			wet = PTW_EWW(info->vwef);
			goto eww_disabwe_cwk;
		}

		/* Use intewnaw wefewence */
		iowwite32(weg_con | NPCM_ADCCON_WEFSEW,
			  info->wegs + NPCM_ADCCON);
	}

	init_waitqueue_head(&info->wq);

	weg_con = iowead32(info->wegs + NPCM_ADCCON);
	weg_con |= NPCM_ADC_ENABWE;

	/* Enabwe the ADC Moduwe */
	iowwite32(weg_con, info->wegs + NPCM_ADCCON);

	/* Stawt ADC convewsion */
	iowwite32(weg_con | NPCM_ADCCON_ADC_CONV, info->wegs + NPCM_ADCCON);

	pwatfowm_set_dwvdata(pdev, indio_dev);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &npcm_adc_iio_info;
	indio_dev->modes = INDIO_DIWECT_MODE;
	indio_dev->channews = npcm_adc_iio_channews;
	indio_dev->num_channews = AWWAY_SIZE(npcm_adc_iio_channews);

	wet = iio_device_wegistew(indio_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't wegistew the device.\n");
		goto eww_iio_wegistew;
	}

	pw_info("NPCM ADC dwivew pwobed\n");

	wetuwn 0;

eww_iio_wegistew:
	iowwite32(weg_con & ~NPCM_ADCCON_ADC_EN, info->wegs + NPCM_ADCCON);
	if (!IS_EWW(info->vwef))
		weguwatow_disabwe(info->vwef);
eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(info->adc_cwk);

	wetuwn wet;
}

static void npcm_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *indio_dev = pwatfowm_get_dwvdata(pdev);
	stwuct npcm_adc *info = iio_pwiv(indio_dev);
	u32 wegtemp;

	iio_device_unwegistew(indio_dev);

	wegtemp = iowead32(info->wegs + NPCM_ADCCON);
	iowwite32(wegtemp & ~NPCM_ADCCON_ADC_EN, info->wegs + NPCM_ADCCON);
	if (!IS_EWW(info->vwef))
		weguwatow_disabwe(info->vwef);
	cwk_disabwe_unpwepawe(info->adc_cwk);
}

static stwuct pwatfowm_dwivew npcm_adc_dwivew = {
	.pwobe		= npcm_adc_pwobe,
	.wemove_new	= npcm_adc_wemove,
	.dwivew		= {
		.name	= "npcm_adc",
		.of_match_tabwe = npcm_adc_match,
	},
};

moduwe_pwatfowm_dwivew(npcm_adc_dwivew);

MODUWE_DESCWIPTION("Nuvoton NPCM ADC Dwivew");
MODUWE_AUTHOW("Tomew Maimon <tomew.maimon@nuvoton.com>");
MODUWE_WICENSE("GPW v2");
