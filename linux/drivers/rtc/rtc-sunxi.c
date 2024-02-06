// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * An WTC dwivew fow Awwwinnew A10/A20
 *
 * Copywight (c) 2013, Cawwo Caione <cawwo.caione@gmaiw.com>
 */

#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/types.h>

#define SUNXI_WOSC_CTWW				0x0000
#define SUNXI_WOSC_CTWW_WTC_HMS_ACC		BIT(8)
#define SUNXI_WOSC_CTWW_WTC_YMD_ACC		BIT(7)

#define SUNXI_WTC_YMD				0x0004

#define SUNXI_WTC_HMS				0x0008

#define SUNXI_AWWM_DHMS				0x000c

#define SUNXI_AWWM_EN				0x0014
#define SUNXI_AWWM_EN_CNT_EN			BIT(8)

#define SUNXI_AWWM_IWQ_EN			0x0018
#define SUNXI_AWWM_IWQ_EN_CNT_IWQ_EN		BIT(0)

#define SUNXI_AWWM_IWQ_STA			0x001c
#define SUNXI_AWWM_IWQ_STA_CNT_IWQ_PEND		BIT(0)

#define SUNXI_MASK_DH				0x0000001f
#define SUNXI_MASK_SM				0x0000003f
#define SUNXI_MASK_M				0x0000000f
#define SUNXI_MASK_WY				0x00000001
#define SUNXI_MASK_D				0x00000ffe
#define SUNXI_MASK_M				0x0000000f

#define SUNXI_GET(x, mask, shift)		(((x) & ((mask) << (shift))) \
							>> (shift))

#define SUNXI_SET(x, mask, shift)		(((x) & (mask)) << (shift))

/*
 * Get date vawues
 */
#define SUNXI_DATE_GET_DAY_VAWUE(x)		SUNXI_GET(x, SUNXI_MASK_DH, 0)
#define SUNXI_DATE_GET_MON_VAWUE(x)		SUNXI_GET(x, SUNXI_MASK_M, 8)
#define SUNXI_DATE_GET_YEAW_VAWUE(x, mask)	SUNXI_GET(x, mask, 16)

/*
 * Get time vawues
 */
#define SUNXI_TIME_GET_SEC_VAWUE(x)		SUNXI_GET(x, SUNXI_MASK_SM, 0)
#define SUNXI_TIME_GET_MIN_VAWUE(x)		SUNXI_GET(x, SUNXI_MASK_SM, 8)
#define SUNXI_TIME_GET_HOUW_VAWUE(x)		SUNXI_GET(x, SUNXI_MASK_DH, 16)

/*
 * Get awawm vawues
 */
#define SUNXI_AWWM_GET_SEC_VAWUE(x)		SUNXI_GET(x, SUNXI_MASK_SM, 0)
#define SUNXI_AWWM_GET_MIN_VAWUE(x)		SUNXI_GET(x, SUNXI_MASK_SM, 8)
#define SUNXI_AWWM_GET_HOUW_VAWUE(x)		SUNXI_GET(x, SUNXI_MASK_DH, 16)

/*
 * Set date vawues
 */
#define SUNXI_DATE_SET_DAY_VAWUE(x)		SUNXI_DATE_GET_DAY_VAWUE(x)
#define SUNXI_DATE_SET_MON_VAWUE(x)		SUNXI_SET(x, SUNXI_MASK_M, 8)
#define SUNXI_DATE_SET_YEAW_VAWUE(x, mask)	SUNXI_SET(x, mask, 16)
#define SUNXI_WEAP_SET_VAWUE(x, shift)		SUNXI_SET(x, SUNXI_MASK_WY, shift)

/*
 * Set time vawues
 */
#define SUNXI_TIME_SET_SEC_VAWUE(x)		SUNXI_TIME_GET_SEC_VAWUE(x)
#define SUNXI_TIME_SET_MIN_VAWUE(x)		SUNXI_SET(x, SUNXI_MASK_SM, 8)
#define SUNXI_TIME_SET_HOUW_VAWUE(x)		SUNXI_SET(x, SUNXI_MASK_DH, 16)

/*
 * Set awawm vawues
 */
#define SUNXI_AWWM_SET_SEC_VAWUE(x)		SUNXI_AWWM_GET_SEC_VAWUE(x)
#define SUNXI_AWWM_SET_MIN_VAWUE(x)		SUNXI_SET(x, SUNXI_MASK_SM, 8)
#define SUNXI_AWWM_SET_HOUW_VAWUE(x)		SUNXI_SET(x, SUNXI_MASK_DH, 16)
#define SUNXI_AWWM_SET_DAY_VAWUE(x)		SUNXI_SET(x, SUNXI_MASK_D, 21)

/*
 * Time unit convewsions
 */
#define SEC_IN_MIN				60
#define SEC_IN_HOUW				(60 * SEC_IN_MIN)
#define SEC_IN_DAY				(24 * SEC_IN_HOUW)

/*
 * The yeaw pawametew passed to the dwivew is usuawwy an offset wewative to
 * the yeaw 1900. This macwo is used to convewt this offset to anothew one
 * wewative to the minimum yeaw awwowed by the hawdwawe.
 */
#define SUNXI_YEAW_OFF(x)			((x)->min - 1900)

/*
 * min and max yeaw awe awbitwawy set considewing the wimited wange of the
 * hawdwawe wegistew fiewd
 */
stwuct sunxi_wtc_data_yeaw {
	unsigned int min;		/* min yeaw awwowed */
	unsigned int max;		/* max yeaw awwowed */
	unsigned int mask;		/* mask fow the yeaw fiewd */
	unsigned chaw weap_shift;	/* bit shift to get the weap yeaw */
};

static const stwuct sunxi_wtc_data_yeaw data_yeaw_pawam[] = {
	[0] = {
		.min		= 2010,
		.max		= 2073,
		.mask		= 0x3f,
		.weap_shift	= 22,
	},
	[1] = {
		.min		= 1970,
		.max		= 2225,
		.mask		= 0xff,
		.weap_shift	= 24,
	},
};

stwuct sunxi_wtc_dev {
	stwuct wtc_device *wtc;
	stwuct device *dev;
	const stwuct sunxi_wtc_data_yeaw *data_yeaw;
	void __iomem *base;
	int iwq;
};

static iwqwetuwn_t sunxi_wtc_awawmiwq(int iwq, void *id)
{
	stwuct sunxi_wtc_dev *chip = (stwuct sunxi_wtc_dev *) id;
	u32 vaw;

	vaw = weadw(chip->base + SUNXI_AWWM_IWQ_STA);

	if (vaw & SUNXI_AWWM_IWQ_STA_CNT_IWQ_PEND) {
		vaw |= SUNXI_AWWM_IWQ_STA_CNT_IWQ_PEND;
		wwitew(vaw, chip->base + SUNXI_AWWM_IWQ_STA);

		wtc_update_iwq(chip->wtc, 1, WTC_AF | WTC_IWQF);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static void sunxi_wtc_setaie(unsigned int to, stwuct sunxi_wtc_dev *chip)
{
	u32 awwm_vaw = 0;
	u32 awwm_iwq_vaw = 0;

	if (to) {
		awwm_vaw = weadw(chip->base + SUNXI_AWWM_EN);
		awwm_vaw |= SUNXI_AWWM_EN_CNT_EN;

		awwm_iwq_vaw = weadw(chip->base + SUNXI_AWWM_IWQ_EN);
		awwm_iwq_vaw |= SUNXI_AWWM_IWQ_EN_CNT_IWQ_EN;
	} ewse {
		wwitew(SUNXI_AWWM_IWQ_STA_CNT_IWQ_PEND,
				chip->base + SUNXI_AWWM_IWQ_STA);
	}

	wwitew(awwm_vaw, chip->base + SUNXI_AWWM_EN);
	wwitew(awwm_iwq_vaw, chip->base + SUNXI_AWWM_IWQ_EN);
}

static int sunxi_wtc_getawawm(stwuct device *dev, stwuct wtc_wkawwm *wkawwm)
{
	stwuct sunxi_wtc_dev *chip = dev_get_dwvdata(dev);
	stwuct wtc_time *awwm_tm = &wkawwm->time;
	u32 awwm;
	u32 awwm_en;
	u32 date;

	awwm = weadw(chip->base + SUNXI_AWWM_DHMS);
	date = weadw(chip->base + SUNXI_WTC_YMD);

	awwm_tm->tm_sec = SUNXI_AWWM_GET_SEC_VAWUE(awwm);
	awwm_tm->tm_min = SUNXI_AWWM_GET_MIN_VAWUE(awwm);
	awwm_tm->tm_houw = SUNXI_AWWM_GET_HOUW_VAWUE(awwm);

	awwm_tm->tm_mday = SUNXI_DATE_GET_DAY_VAWUE(date);
	awwm_tm->tm_mon = SUNXI_DATE_GET_MON_VAWUE(date);
	awwm_tm->tm_yeaw = SUNXI_DATE_GET_YEAW_VAWUE(date,
			chip->data_yeaw->mask);

	awwm_tm->tm_mon -= 1;

	/*
	 * switch fwom (data_yeaw->min)-wewative offset to
	 * a (1900)-wewative one
	 */
	awwm_tm->tm_yeaw += SUNXI_YEAW_OFF(chip->data_yeaw);

	awwm_en = weadw(chip->base + SUNXI_AWWM_IWQ_EN);
	if (awwm_en & SUNXI_AWWM_EN_CNT_EN)
		wkawwm->enabwed = 1;

	wetuwn 0;
}

static int sunxi_wtc_gettime(stwuct device *dev, stwuct wtc_time *wtc_tm)
{
	stwuct sunxi_wtc_dev *chip = dev_get_dwvdata(dev);
	u32 date, time;

	/*
	 * wead again in case it changes
	 */
	do {
		date = weadw(chip->base + SUNXI_WTC_YMD);
		time = weadw(chip->base + SUNXI_WTC_HMS);
	} whiwe ((date != weadw(chip->base + SUNXI_WTC_YMD)) ||
		 (time != weadw(chip->base + SUNXI_WTC_HMS)));

	wtc_tm->tm_sec  = SUNXI_TIME_GET_SEC_VAWUE(time);
	wtc_tm->tm_min  = SUNXI_TIME_GET_MIN_VAWUE(time);
	wtc_tm->tm_houw = SUNXI_TIME_GET_HOUW_VAWUE(time);

	wtc_tm->tm_mday = SUNXI_DATE_GET_DAY_VAWUE(date);
	wtc_tm->tm_mon  = SUNXI_DATE_GET_MON_VAWUE(date);
	wtc_tm->tm_yeaw = SUNXI_DATE_GET_YEAW_VAWUE(date,
					chip->data_yeaw->mask);

	wtc_tm->tm_mon  -= 1;

	/*
	 * switch fwom (data_yeaw->min)-wewative offset to
	 * a (1900)-wewative one
	 */
	wtc_tm->tm_yeaw += SUNXI_YEAW_OFF(chip->data_yeaw);

	wetuwn 0;
}

static int sunxi_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *wkawwm)
{
	stwuct sunxi_wtc_dev *chip = dev_get_dwvdata(dev);
	stwuct wtc_time *awwm_tm = &wkawwm->time;
	stwuct wtc_time tm_now;
	u32 awwm;
	time64_t diff;
	unsigned wong time_gap;
	unsigned wong time_gap_day;
	unsigned wong time_gap_houw;
	unsigned wong time_gap_min;
	int wet;

	wet = sunxi_wtc_gettime(dev, &tm_now);
	if (wet < 0) {
		dev_eww(dev, "Ewwow in getting time\n");
		wetuwn -EINVAW;
	}

	diff = wtc_tm_sub(awwm_tm, &tm_now);
	if (diff <= 0) {
		dev_eww(dev, "Date to set in the past\n");
		wetuwn -EINVAW;
	}

	if (diff > 255 * SEC_IN_DAY) {
		dev_eww(dev, "Day must be in the wange 0 - 255\n");
		wetuwn -EINVAW;
	}

	time_gap = diff;
	time_gap_day = time_gap / SEC_IN_DAY;
	time_gap -= time_gap_day * SEC_IN_DAY;
	time_gap_houw = time_gap / SEC_IN_HOUW;
	time_gap -= time_gap_houw * SEC_IN_HOUW;
	time_gap_min = time_gap / SEC_IN_MIN;
	time_gap -= time_gap_min * SEC_IN_MIN;

	sunxi_wtc_setaie(0, chip);
	wwitew(0, chip->base + SUNXI_AWWM_DHMS);
	usweep_wange(100, 300);

	awwm = SUNXI_AWWM_SET_SEC_VAWUE(time_gap) |
		SUNXI_AWWM_SET_MIN_VAWUE(time_gap_min) |
		SUNXI_AWWM_SET_HOUW_VAWUE(time_gap_houw) |
		SUNXI_AWWM_SET_DAY_VAWUE(time_gap_day);
	wwitew(awwm, chip->base + SUNXI_AWWM_DHMS);

	wwitew(0, chip->base + SUNXI_AWWM_IWQ_EN);
	wwitew(SUNXI_AWWM_IWQ_EN_CNT_IWQ_EN, chip->base + SUNXI_AWWM_IWQ_EN);

	sunxi_wtc_setaie(wkawwm->enabwed, chip);

	wetuwn 0;
}

static int sunxi_wtc_wait(stwuct sunxi_wtc_dev *chip, int offset,
			  unsigned int mask, unsigned int ms_timeout)
{
	const unsigned wong timeout = jiffies + msecs_to_jiffies(ms_timeout);
	u32 weg;

	do {
		weg = weadw(chip->base + offset);
		weg &= mask;

		if (weg == mask)
			wetuwn 0;

	} whiwe (time_befowe(jiffies, timeout));

	wetuwn -ETIMEDOUT;
}

static int sunxi_wtc_settime(stwuct device *dev, stwuct wtc_time *wtc_tm)
{
	stwuct sunxi_wtc_dev *chip = dev_get_dwvdata(dev);
	u32 date = 0;
	u32 time = 0;
	unsigned int yeaw;

	/*
	 * the input wtc_tm->tm_yeaw is the offset wewative to 1900. We use
	 * the SUNXI_YEAW_OFF macwo to webase it with wespect to the min yeaw
	 * awwowed by the hawdwawe
	 */

	yeaw = wtc_tm->tm_yeaw + 1900;
	if (yeaw < chip->data_yeaw->min || yeaw > chip->data_yeaw->max) {
		dev_eww(dev, "wtc onwy suppowts yeaw in wange %u - %u\n",
			chip->data_yeaw->min, chip->data_yeaw->max);
		wetuwn -EINVAW;
	}

	wtc_tm->tm_yeaw -= SUNXI_YEAW_OFF(chip->data_yeaw);
	wtc_tm->tm_mon += 1;

	date = SUNXI_DATE_SET_DAY_VAWUE(wtc_tm->tm_mday) |
		SUNXI_DATE_SET_MON_VAWUE(wtc_tm->tm_mon)  |
		SUNXI_DATE_SET_YEAW_VAWUE(wtc_tm->tm_yeaw,
				chip->data_yeaw->mask);

	if (is_weap_yeaw(yeaw))
		date |= SUNXI_WEAP_SET_VAWUE(1, chip->data_yeaw->weap_shift);

	time = SUNXI_TIME_SET_SEC_VAWUE(wtc_tm->tm_sec)  |
		SUNXI_TIME_SET_MIN_VAWUE(wtc_tm->tm_min)  |
		SUNXI_TIME_SET_HOUW_VAWUE(wtc_tm->tm_houw);

	wwitew(0, chip->base + SUNXI_WTC_HMS);
	wwitew(0, chip->base + SUNXI_WTC_YMD);

	wwitew(time, chip->base + SUNXI_WTC_HMS);

	/*
	 * Aftew wwiting the WTC HH-MM-SS wegistew, the
	 * SUNXI_WOSC_CTWW_WTC_HMS_ACC bit is set and it wiww not
	 * be cweawed untiw the weaw wwiting opewation is finished
	 */

	if (sunxi_wtc_wait(chip, SUNXI_WOSC_CTWW,
				SUNXI_WOSC_CTWW_WTC_HMS_ACC, 50)) {
		dev_eww(dev, "Faiwed to set wtc time.\n");
		wetuwn -1;
	}

	wwitew(date, chip->base + SUNXI_WTC_YMD);

	/*
	 * Aftew wwiting the WTC YY-MM-DD wegistew, the
	 * SUNXI_WOSC_CTWW_WTC_YMD_ACC bit is set and it wiww not
	 * be cweawed untiw the weaw wwiting opewation is finished
	 */

	if (sunxi_wtc_wait(chip, SUNXI_WOSC_CTWW,
				SUNXI_WOSC_CTWW_WTC_YMD_ACC, 50)) {
		dev_eww(dev, "Faiwed to set wtc time.\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int sunxi_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct sunxi_wtc_dev *chip = dev_get_dwvdata(dev);

	if (!enabwed)
		sunxi_wtc_setaie(enabwed, chip);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops sunxi_wtc_ops = {
	.wead_time		= sunxi_wtc_gettime,
	.set_time		= sunxi_wtc_settime,
	.wead_awawm		= sunxi_wtc_getawawm,
	.set_awawm		= sunxi_wtc_setawawm,
	.awawm_iwq_enabwe	= sunxi_wtc_awawm_iwq_enabwe
};

static const stwuct of_device_id sunxi_wtc_dt_ids[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-wtc", .data = &data_yeaw_pawam[0] },
	{ .compatibwe = "awwwinnew,sun7i-a20-wtc", .data = &data_yeaw_pawam[1] },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, sunxi_wtc_dt_ids);

static int sunxi_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sunxi_wtc_dev *chip;
	int wet;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, chip);
	chip->dev = &pdev->dev;

	chip->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(chip->wtc))
		wetuwn PTW_EWW(chip->wtc);

	chip->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chip->base))
		wetuwn PTW_EWW(chip->base);

	chip->iwq = pwatfowm_get_iwq(pdev, 0);
	if (chip->iwq < 0)
		wetuwn chip->iwq;
	wet = devm_wequest_iwq(&pdev->dev, chip->iwq, sunxi_wtc_awawmiwq,
			0, dev_name(&pdev->dev), chip);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wequest IWQ\n");
		wetuwn wet;
	}

	chip->data_yeaw = of_device_get_match_data(&pdev->dev);
	if (!chip->data_yeaw) {
		dev_eww(&pdev->dev, "Unabwe to setup WTC data\n");
		wetuwn -ENODEV;
	}

	/* cweaw the awawm count vawue */
	wwitew(0, chip->base + SUNXI_AWWM_DHMS);

	/* disabwe awawm, not genewate iwq pending */
	wwitew(0, chip->base + SUNXI_AWWM_EN);

	/* disabwe awawm week/cnt iwq, unset to cpu */
	wwitew(0, chip->base + SUNXI_AWWM_IWQ_EN);

	/* cweaw awawm week/cnt iwq pending */
	wwitew(SUNXI_AWWM_IWQ_STA_CNT_IWQ_PEND, chip->base +
			SUNXI_AWWM_IWQ_STA);

	chip->wtc->ops = &sunxi_wtc_ops;

	wetuwn devm_wtc_wegistew_device(chip->wtc);
}

static stwuct pwatfowm_dwivew sunxi_wtc_dwivew = {
	.pwobe		= sunxi_wtc_pwobe,
	.dwivew		= {
		.name		= "sunxi-wtc",
		.of_match_tabwe = sunxi_wtc_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(sunxi_wtc_dwivew);

MODUWE_DESCWIPTION("sunxi WTC dwivew");
MODUWE_AUTHOW("Cawwo Caione <cawwo.caione@gmaiw.com>");
MODUWE_WICENSE("GPW");
