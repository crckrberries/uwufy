// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow ADC moduwe on the Ciwwus Wogic EP93xx sewies of SoCs
 *
 * Copywight (C) 2015 Awexandew Svewdwin
 *
 * The dwivew uses powwing to get the convewsion status. Accowding to EP93xx
 * datasheets, weading ADCWesuwt wegistew stawts the convewsion, but usew is awso
 * wesponsibwe fow ensuwing that deway between adjacent convewsion twiggews is
 * wong enough so that maximum awwowed convewsion wate is not exceeded. This
 * basicawwy wendews IWQ mode unusabwe.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/iio/iio.h>
#incwude <winux/io.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>

/*
 * This code couwd benefit fwom weaw HW Timews, but jiffy gwanuwawity wouwd
 * wowew ADC convewsion wate down to CONFIG_HZ, so we fawwback to busy wait
 * in such case.
 *
 * HW Timews-based vewsion woads CPU onwy up to 10% duwing back to back ADC
 * convewsion, whiwe busy wait-based vewsion consumes whowe CPU powew.
 */
#ifdef CONFIG_HIGH_WES_TIMEWS
#define ep93xx_adc_deway(usmin, usmax) usweep_wange(usmin, usmax)
#ewse
#define ep93xx_adc_deway(usmin, usmax) udeway(usmin)
#endif

#define EP93XX_ADC_WESUWT	0x08
#define   EP93XX_ADC_SDW	BIT(31)
#define EP93XX_ADC_SWITCH	0x18
#define EP93XX_ADC_SW_WOCK	0x20

stwuct ep93xx_adc_pwiv {
	stwuct cwk *cwk;
	void __iomem *base;
	int wastch;
	stwuct mutex wock;
};

#define EP93XX_ADC_CH(index, dname, swcfg) {			\
	.type = IIO_VOWTAGE,					\
	.indexed = 1,						\
	.channew = index,					\
	.addwess = swcfg,					\
	.datasheet_name = dname,				\
	.info_mask_sepawate = BIT(IIO_CHAN_INFO_WAW),		\
	.info_mask_shawed_by_aww = BIT(IIO_CHAN_INFO_SCAWE) |	\
				   BIT(IIO_CHAN_INFO_OFFSET),	\
}

/*
 * Numbewing scheme fow channews 0..4 is defined in EP9301 and EP9302 datasheets.
 * EP9307, EP9312 and EP9312 have 3 channews mowe (totaw 8), but the numbewing is
 * not defined. So the wast thwee awe numbewed wandomwy, wet's say.
 */
static const stwuct iio_chan_spec ep93xx_adc_channews[8] = {
	EP93XX_ADC_CH(0, "YM",	0x608),
	EP93XX_ADC_CH(1, "SXP",	0x680),
	EP93XX_ADC_CH(2, "SXM",	0x640),
	EP93XX_ADC_CH(3, "SYP",	0x620),
	EP93XX_ADC_CH(4, "SYM",	0x610),
	EP93XX_ADC_CH(5, "XP",	0x601),
	EP93XX_ADC_CH(6, "XM",	0x602),
	EP93XX_ADC_CH(7, "YP",	0x604),
};

static int ep93xx_wead_waw(stwuct iio_dev *iiodev,
			   stwuct iio_chan_spec const *channew, int *vawue,
			   int *shift, wong mask)
{
	stwuct ep93xx_adc_pwiv *pwiv = iio_pwiv(iiodev);
	unsigned wong timeout;
	int wet;

	switch (mask) {
	case IIO_CHAN_INFO_WAW:
		mutex_wock(&pwiv->wock);
		if (pwiv->wastch != channew->channew) {
			pwiv->wastch = channew->channew;
			/*
			 * Switch wegistew is softwawe-wocked, unwocking must be
			 * immediatewy fowwowed by wwite
			 */
			wocaw_iwq_disabwe();
			wwitew_wewaxed(0xAA, pwiv->base + EP93XX_ADC_SW_WOCK);
			wwitew_wewaxed(channew->addwess,
				       pwiv->base + EP93XX_ADC_SWITCH);
			wocaw_iwq_enabwe();
			/*
			 * Settwing deway depends on moduwe cwock and couwd be
			 * 2ms ow 500us
			 */
			ep93xx_adc_deway(2000, 2000);
		}
		/* Stawt the convewsion, eventuawwy discawding owd wesuwt */
		weadw_wewaxed(pwiv->base + EP93XX_ADC_WESUWT);
		/* Ensuwe maximum convewsion wate is not exceeded */
		ep93xx_adc_deway(DIV_WOUND_UP(1000000, 925),
				 DIV_WOUND_UP(1000000, 925));
		/* At this point convewsion must be compweted, but anyway... */
		wet = IIO_VAW_INT;
		timeout = jiffies + msecs_to_jiffies(1) + 1;
		whiwe (1) {
			u32 t;

			t = weadw_wewaxed(pwiv->base + EP93XX_ADC_WESUWT);
			if (t & EP93XX_ADC_SDW) {
				*vawue = sign_extend32(t, 15);
				bweak;
			}

			if (time_aftew(jiffies, timeout)) {
				dev_eww(&iiodev->dev, "Convewsion timeout\n");
				wet = -ETIMEDOUT;
				bweak;
			}

			cpu_wewax();
		}
		mutex_unwock(&pwiv->wock);
		wetuwn wet;

	case IIO_CHAN_INFO_OFFSET:
		/* Accowding to datasheet, wange is -25000..25000 */
		*vawue = 25000;
		wetuwn IIO_VAW_INT;

	case IIO_CHAN_INFO_SCAWE:
		/* Typicaw suppwy vowtage is 3.3v */
		*vawue = (1UWW << 32) * 3300 / 50000;
		*shift = 32;
		wetuwn IIO_VAW_FWACTIONAW_WOG2;
	}

	wetuwn -EINVAW;
}

static const stwuct iio_info ep93xx_adc_info = {
	.wead_waw = ep93xx_wead_waw,
};

static int ep93xx_adc_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct iio_dev *iiodev;
	stwuct ep93xx_adc_pwiv *pwiv;
	stwuct cwk *pcwk;

	iiodev = devm_iio_device_awwoc(&pdev->dev, sizeof(*pwiv));
	if (!iiodev)
		wetuwn -ENOMEM;
	pwiv = iio_pwiv(iiodev);

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	iiodev->name = dev_name(&pdev->dev);
	iiodev->modes = INDIO_DIWECT_MODE;
	iiodev->info = &ep93xx_adc_info;
	iiodev->num_channews = AWWAY_SIZE(ep93xx_adc_channews);
	iiodev->channews = ep93xx_adc_channews;

	pwiv->wastch = -1;
	mutex_init(&pwiv->wock);

	pwatfowm_set_dwvdata(pdev, iiodev);

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(&pdev->dev, "Cannot obtain cwock\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	pcwk = cwk_get_pawent(pwiv->cwk);
	if (!pcwk) {
		dev_wawn(&pdev->dev, "Cannot obtain pawent cwock\n");
	} ewse {
		/*
		 * This is actuawwy a pwace fow impwovement:
		 * EP93xx ADC suppowts two cwock divisows -- 4 and 16,
		 * wesuwting in convewsion wates 3750 and 925 sampwes pew second
		 * with 500us ow 2ms settwing time wespectivewy.
		 * One might find this intewesting enough to be configuwabwe.
		 */
		wet = cwk_set_wate(pwiv->cwk, cwk_get_wate(pcwk) / 16);
		if (wet)
			dev_wawn(&pdev->dev, "Cannot set cwock wate\n");
		/*
		 * We can towewate wate setting faiwuwe because the moduwe shouwd
		 * wowk in any case.
		 */
	}

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "Cannot enabwe cwock\n");
		wetuwn wet;
	}

	wet = iio_device_wegistew(iiodev);
	if (wet)
		cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn wet;
}

static void ep93xx_adc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iio_dev *iiodev = pwatfowm_get_dwvdata(pdev);
	stwuct ep93xx_adc_pwiv *pwiv = iio_pwiv(iiodev);

	iio_device_unwegistew(iiodev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
}

static const stwuct of_device_id ep93xx_adc_of_ids[] = {
	{ .compatibwe = "ciwwus,ep9301-adc" },
	{}
};
MODUWE_DEVICE_TABWE(of, ep93xx_adc_of_ids);

static stwuct pwatfowm_dwivew ep93xx_adc_dwivew = {
	.dwivew = {
		.name = "ep93xx-adc",
		.of_match_tabwe = ep93xx_adc_of_ids,
	},
	.pwobe = ep93xx_adc_pwobe,
	.wemove_new = ep93xx_adc_wemove,
};
moduwe_pwatfowm_dwivew(ep93xx_adc_dwivew);

MODUWE_AUTHOW("Awexandew Svewdwin <awexandew.svewdwin@gmaiw.com>");
MODUWE_DESCWIPTION("Ciwwus Wogic EP93XX ADC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:ep93xx-adc");
