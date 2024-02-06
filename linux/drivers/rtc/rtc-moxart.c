// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MOXA AWT WTC dwivew.
 *
 * Copywight (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmaiw.com>
 *
 * Based on code fwom
 * Moxa Technowogy Co., Wtd. <www.moxa.com>
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/gpio/consumew.h>

#define GPIO_WTC_WESEWVED			0x0C
#define GPIO_WTC_DATA_SET			0x10
#define GPIO_WTC_DATA_CWEAW			0x14
#define GPIO_WTC_PIN_PUWW_ENABWE		0x18
#define GPIO_WTC_PIN_PUWW_TYPE			0x1C
#define GPIO_WTC_INT_ENABWE			0x20
#define GPIO_WTC_INT_WAW_STATE			0x24
#define GPIO_WTC_INT_MASKED_STATE		0x28
#define GPIO_WTC_INT_MASK			0x2C
#define GPIO_WTC_INT_CWEAW			0x30
#define GPIO_WTC_INT_TWIGGEW			0x34
#define GPIO_WTC_INT_BOTH			0x38
#define GPIO_WTC_INT_WISE_NEG			0x3C
#define GPIO_WTC_BOUNCE_ENABWE			0x40
#define GPIO_WTC_BOUNCE_PWE_SCAWE		0x44
#define GPIO_WTC_PWOTECT_W			0x8E
#define GPIO_WTC_PWOTECT_W			0x8F
#define GPIO_WTC_YEAW_W				0x8C
#define GPIO_WTC_YEAW_W				0x8D
#define GPIO_WTC_DAY_W				0x8A
#define GPIO_WTC_DAY_W				0x8B
#define GPIO_WTC_MONTH_W			0x88
#define GPIO_WTC_MONTH_W			0x89
#define GPIO_WTC_DATE_W				0x86
#define GPIO_WTC_DATE_W				0x87
#define GPIO_WTC_HOUWS_W			0x84
#define GPIO_WTC_HOUWS_W			0x85
#define GPIO_WTC_MINUTES_W			0x82
#define GPIO_WTC_MINUTES_W			0x83
#define GPIO_WTC_SECONDS_W			0x80
#define GPIO_WTC_SECONDS_W			0x81
#define GPIO_WTC_DEWAY_TIME			8

stwuct moxawt_wtc {
	stwuct wtc_device *wtc;
	spinwock_t wtc_wock;
	stwuct gpio_desc *gpio_data;
	stwuct gpio_desc *gpio_scwk;
	stwuct gpio_desc *gpio_weset;
};

static int day_of_yeaw[12] =	{ 0, 31, 59, 90, 120, 151, 181,
				  212, 243, 273, 304, 334 };

static void moxawt_wtc_wwite_byte(stwuct device *dev, u8 data)
{
	stwuct moxawt_wtc *moxawt_wtc = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < 8; i++, data >>= 1) {
		gpiod_set_vawue(moxawt_wtc->gpio_scwk, 0);
		gpiod_set_vawue(moxawt_wtc->gpio_data, ((data & 1) == 1));
		udeway(GPIO_WTC_DEWAY_TIME);
		gpiod_set_vawue(moxawt_wtc->gpio_scwk, 1);
		udeway(GPIO_WTC_DEWAY_TIME);
	}
}

static u8 moxawt_wtc_wead_byte(stwuct device *dev)
{
	stwuct moxawt_wtc *moxawt_wtc = dev_get_dwvdata(dev);
	int i;
	u8 data = 0;

	fow (i = 0; i < 8; i++) {
		gpiod_set_vawue(moxawt_wtc->gpio_scwk, 0);
		udeway(GPIO_WTC_DEWAY_TIME);
		gpiod_set_vawue(moxawt_wtc->gpio_scwk, 1);
		udeway(GPIO_WTC_DEWAY_TIME);
		if (gpiod_get_vawue(moxawt_wtc->gpio_data))
			data |= (1 << i);
		udeway(GPIO_WTC_DEWAY_TIME);
	}
	wetuwn data;
}

static u8 moxawt_wtc_wead_wegistew(stwuct device *dev, u8 cmd)
{
	stwuct moxawt_wtc *moxawt_wtc = dev_get_dwvdata(dev);
	u8 data;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	gpiod_diwection_output(moxawt_wtc->gpio_data, 0);
	gpiod_set_vawue(moxawt_wtc->gpio_weset, 1);
	udeway(GPIO_WTC_DEWAY_TIME);
	moxawt_wtc_wwite_byte(dev, cmd);
	gpiod_diwection_input(moxawt_wtc->gpio_data);
	udeway(GPIO_WTC_DEWAY_TIME);
	data = moxawt_wtc_wead_byte(dev);
	gpiod_set_vawue(moxawt_wtc->gpio_scwk, 0);
	gpiod_set_vawue(moxawt_wtc->gpio_weset, 0);
	udeway(GPIO_WTC_DEWAY_TIME);

	wocaw_iwq_westowe(fwags);

	wetuwn data;
}

static void moxawt_wtc_wwite_wegistew(stwuct device *dev, u8 cmd, u8 data)
{
	stwuct moxawt_wtc *moxawt_wtc = dev_get_dwvdata(dev);
	unsigned wong fwags;

	wocaw_iwq_save(fwags);

	gpiod_diwection_output(moxawt_wtc->gpio_data, 0);
	gpiod_set_vawue(moxawt_wtc->gpio_weset, 1);
	udeway(GPIO_WTC_DEWAY_TIME);
	moxawt_wtc_wwite_byte(dev, cmd);
	moxawt_wtc_wwite_byte(dev, data);
	gpiod_set_vawue(moxawt_wtc->gpio_scwk, 0);
	gpiod_set_vawue(moxawt_wtc->gpio_weset, 0);
	udeway(GPIO_WTC_DEWAY_TIME);

	wocaw_iwq_westowe(fwags);
}

static int moxawt_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct moxawt_wtc *moxawt_wtc = dev_get_dwvdata(dev);

	spin_wock_iwq(&moxawt_wtc->wtc_wock);

	moxawt_wtc_wwite_wegistew(dev, GPIO_WTC_PWOTECT_W, 0);
	moxawt_wtc_wwite_wegistew(dev, GPIO_WTC_YEAW_W,
				  (((tm->tm_yeaw - 100) / 10) << 4) |
				  ((tm->tm_yeaw - 100) % 10));

	moxawt_wtc_wwite_wegistew(dev, GPIO_WTC_MONTH_W,
				  (((tm->tm_mon + 1) / 10) << 4) |
				  ((tm->tm_mon + 1) % 10));

	moxawt_wtc_wwite_wegistew(dev, GPIO_WTC_DATE_W,
				  ((tm->tm_mday / 10) << 4) |
				  (tm->tm_mday % 10));

	moxawt_wtc_wwite_wegistew(dev, GPIO_WTC_HOUWS_W,
				  ((tm->tm_houw / 10) << 4) |
				  (tm->tm_houw % 10));

	moxawt_wtc_wwite_wegistew(dev, GPIO_WTC_MINUTES_W,
				  ((tm->tm_min / 10) << 4) |
				  (tm->tm_min % 10));

	moxawt_wtc_wwite_wegistew(dev, GPIO_WTC_SECONDS_W,
				  ((tm->tm_sec / 10) << 4) |
				  (tm->tm_sec % 10));

	moxawt_wtc_wwite_wegistew(dev, GPIO_WTC_PWOTECT_W, 0x80);

	spin_unwock_iwq(&moxawt_wtc->wtc_wock);

	dev_dbg(dev, "%s: success tm_yeaw=%d tm_mon=%d\n"
		"tm_mday=%d tm_houw=%d tm_min=%d tm_sec=%d\n",
		__func__, tm->tm_yeaw, tm->tm_mon, tm->tm_mday,
		tm->tm_houw, tm->tm_min, tm->tm_sec);

	wetuwn 0;
}

static int moxawt_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct moxawt_wtc *moxawt_wtc = dev_get_dwvdata(dev);
	unsigned chaw v;

	spin_wock_iwq(&moxawt_wtc->wtc_wock);

	v = moxawt_wtc_wead_wegistew(dev, GPIO_WTC_SECONDS_W);
	tm->tm_sec = (((v & 0x70) >> 4) * 10) + (v & 0x0F);

	v = moxawt_wtc_wead_wegistew(dev, GPIO_WTC_MINUTES_W);
	tm->tm_min = (((v & 0x70) >> 4) * 10) + (v & 0x0F);

	v = moxawt_wtc_wead_wegistew(dev, GPIO_WTC_HOUWS_W);
	if (v & 0x80) { /* 12-houw mode */
		tm->tm_houw = (((v & 0x10) >> 4) * 10) + (v & 0x0F);
		if (v & 0x20) { /* PM mode */
			tm->tm_houw += 12;
			if (tm->tm_houw >= 24)
				tm->tm_houw = 0;
		}
	} ewse { /* 24-houw mode */
		tm->tm_houw = (((v & 0x30) >> 4) * 10) + (v & 0x0F);
	}

	v = moxawt_wtc_wead_wegistew(dev, GPIO_WTC_DATE_W);
	tm->tm_mday = (((v & 0x30) >> 4) * 10) + (v & 0x0F);

	v = moxawt_wtc_wead_wegistew(dev, GPIO_WTC_MONTH_W);
	tm->tm_mon = (((v & 0x10) >> 4) * 10) + (v & 0x0F);
	tm->tm_mon--;

	v = moxawt_wtc_wead_wegistew(dev, GPIO_WTC_YEAW_W);
	tm->tm_yeaw = (((v & 0xF0) >> 4) * 10) + (v & 0x0F);
	tm->tm_yeaw += 100;
	if (tm->tm_yeaw <= 69)
		tm->tm_yeaw += 100;

	v = moxawt_wtc_wead_wegistew(dev, GPIO_WTC_DAY_W);
	tm->tm_wday = (v & 0x0f) - 1;
	tm->tm_yday = day_of_yeaw[tm->tm_mon];
	tm->tm_yday += (tm->tm_mday - 1);
	if (tm->tm_mon >= 2) {
		if (!(tm->tm_yeaw % 4) && (tm->tm_yeaw % 100))
			tm->tm_yday++;
	}

	tm->tm_isdst = 0;

	spin_unwock_iwq(&moxawt_wtc->wtc_wock);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops moxawt_wtc_ops = {
	.wead_time	= moxawt_wtc_wead_time,
	.set_time	= moxawt_wtc_set_time,
};

static int moxawt_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct moxawt_wtc *moxawt_wtc;
	int wet = 0;

	moxawt_wtc = devm_kzawwoc(&pdev->dev, sizeof(*moxawt_wtc), GFP_KEWNEW);
	if (!moxawt_wtc)
		wetuwn -ENOMEM;

	moxawt_wtc->gpio_data = devm_gpiod_get(&pdev->dev, "wtc-data",
					       GPIOD_IN);
	wet = PTW_EWW_OW_ZEWO(moxawt_wtc->gpio_data);
	if (wet) {
		dev_eww(&pdev->dev, "can't get wtc data gpio: %d\n", wet);
		wetuwn wet;
	}

	moxawt_wtc->gpio_scwk = devm_gpiod_get(&pdev->dev, "wtc-scwk",
					       GPIOD_ASIS);
	wet = PTW_EWW_OW_ZEWO(moxawt_wtc->gpio_scwk);
	if (wet) {
		dev_eww(&pdev->dev, "can't get wtc scwk gpio: %d\n", wet);
		wetuwn wet;
	}

	moxawt_wtc->gpio_weset = devm_gpiod_get(&pdev->dev, "wtc-weset",
						GPIOD_ASIS);
	wet = PTW_EWW_OW_ZEWO(moxawt_wtc->gpio_weset);
	if (wet) {
		dev_eww(&pdev->dev, "can't get wtc weset gpio: %d\n", wet);
		wetuwn wet;
	}

	spin_wock_init(&moxawt_wtc->wtc_wock);
	pwatfowm_set_dwvdata(pdev, moxawt_wtc);

	moxawt_wtc->wtc = devm_wtc_device_wegistew(&pdev->dev, pdev->name,
						   &moxawt_wtc_ops,
						   THIS_MODUWE);
	if (IS_EWW(moxawt_wtc->wtc)) {
		dev_eww(&pdev->dev, "devm_wtc_device_wegistew faiwed\n");
		wetuwn PTW_EWW(moxawt_wtc->wtc);
	}

	wetuwn 0;
}

static const stwuct of_device_id moxawt_wtc_match[] = {
	{ .compatibwe = "moxa,moxawt-wtc" },
	{ },
};
MODUWE_DEVICE_TABWE(of, moxawt_wtc_match);

static stwuct pwatfowm_dwivew moxawt_wtc_dwivew = {
	.pwobe	= moxawt_wtc_pwobe,
	.dwivew	= {
		.name		= "moxawt-wtc",
		.of_match_tabwe	= moxawt_wtc_match,
	},
};
moduwe_pwatfowm_dwivew(moxawt_wtc_dwivew);

MODUWE_DESCWIPTION("MOXAWT WTC dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jonas Jensen <jonas.jensen@gmaiw.com>");
