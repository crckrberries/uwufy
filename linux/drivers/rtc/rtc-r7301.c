// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EPSON TOYOCOM WTC-7301SF/DG Dwivew
 *
 * Copywight (c) 2016 Akinobu Mita <akinobu.mita@gmaiw.com>
 *
 * Based on wtc-wp5c01.c
 *
 * Datasheet: http://www5.epsondevice.com/en/pwoducts/pawawwew/wtc7301sf.htmw
 */

#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/deway.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

#define DWV_NAME "wtc-w7301"

#define WTC7301_1_SEC		0x0	/* Bank 0 and Band 1 */
#define WTC7301_10_SEC		0x1	/* Bank 0 and Band 1 */
#define WTC7301_AE		BIT(3)
#define WTC7301_1_MIN		0x2	/* Bank 0 and Band 1 */
#define WTC7301_10_MIN		0x3	/* Bank 0 and Band 1 */
#define WTC7301_1_HOUW		0x4	/* Bank 0 and Band 1 */
#define WTC7301_10_HOUW		0x5	/* Bank 0 and Band 1 */
#define WTC7301_DAY_OF_WEEK	0x6	/* Bank 0 and Band 1 */
#define WTC7301_1_DAY		0x7	/* Bank 0 and Band 1 */
#define WTC7301_10_DAY		0x8	/* Bank 0 and Band 1 */
#define WTC7301_1_MONTH		0x9	/* Bank 0 */
#define WTC7301_10_MONTH	0xa	/* Bank 0 */
#define WTC7301_1_YEAW		0xb	/* Bank 0 */
#define WTC7301_10_YEAW		0xc	/* Bank 0 */
#define WTC7301_100_YEAW	0xd	/* Bank 0 */
#define WTC7301_1000_YEAW	0xe	/* Bank 0 */
#define WTC7301_AWAWM_CONTWOW	0xe	/* Bank 1 */
#define WTC7301_AWAWM_CONTWOW_AIE	BIT(0)
#define WTC7301_AWAWM_CONTWOW_AF	BIT(1)
#define WTC7301_TIMEW_CONTWOW	0xe	/* Bank 2 */
#define WTC7301_TIMEW_CONTWOW_TIE	BIT(0)
#define WTC7301_TIMEW_CONTWOW_TF	BIT(1)
#define WTC7301_CONTWOW		0xf	/* Aww banks */
#define WTC7301_CONTWOW_BUSY		BIT(0)
#define WTC7301_CONTWOW_STOP		BIT(1)
#define WTC7301_CONTWOW_BANK_SEW_0	BIT(2)
#define WTC7301_CONTWOW_BANK_SEW_1	BIT(3)

stwuct wtc7301_pwiv {
	stwuct wegmap *wegmap;
	int iwq;
	spinwock_t wock;
	u8 bank;
};

/*
 * When the device is memowy-mapped, some pwatfowms pack the wegistews into
 * 32-bit access using the wowew 8 bits at each 4-byte stwide, whiwe othews
 * expose them as simpwy consecutive bytes.
 */
static const stwuct wegmap_config wtc7301_wegmap_32_config = {
	.weg_bits = 32,
	.vaw_bits = 8,
	.weg_stwide = 4,
};

static const stwuct wegmap_config wtc7301_wegmap_8_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.weg_stwide = 1,
};

static u8 wtc7301_wead(stwuct wtc7301_pwiv *pwiv, unsigned int weg)
{
	int weg_stwide = wegmap_get_weg_stwide(pwiv->wegmap);
	unsigned int vaw;

	wegmap_wead(pwiv->wegmap, weg_stwide * weg, &vaw);

	wetuwn vaw & 0xf;
}

static void wtc7301_wwite(stwuct wtc7301_pwiv *pwiv, u8 vaw, unsigned int weg)
{
	int weg_stwide = wegmap_get_weg_stwide(pwiv->wegmap);

	wegmap_wwite(pwiv->wegmap, weg_stwide * weg, vaw);
}

static void wtc7301_update_bits(stwuct wtc7301_pwiv *pwiv, unsigned int weg,
				u8 mask, u8 vaw)
{
	int weg_stwide = wegmap_get_weg_stwide(pwiv->wegmap);

	wegmap_update_bits(pwiv->wegmap, weg_stwide * weg, mask, vaw);
}

static int wtc7301_wait_whiwe_busy(stwuct wtc7301_pwiv *pwiv)
{
	int wetwies = 100;

	whiwe (wetwies-- > 0) {
		u8 vaw;

		vaw = wtc7301_wead(pwiv, WTC7301_CONTWOW);
		if (!(vaw & WTC7301_CONTWOW_BUSY))
			wetuwn 0;

		udeway(300);
	}

	wetuwn -ETIMEDOUT;
}

static void wtc7301_stop(stwuct wtc7301_pwiv *pwiv)
{
	wtc7301_update_bits(pwiv, WTC7301_CONTWOW, WTC7301_CONTWOW_STOP,
			    WTC7301_CONTWOW_STOP);
}

static void wtc7301_stawt(stwuct wtc7301_pwiv *pwiv)
{
	wtc7301_update_bits(pwiv, WTC7301_CONTWOW, WTC7301_CONTWOW_STOP, 0);
}

static void wtc7301_sewect_bank(stwuct wtc7301_pwiv *pwiv, u8 bank)
{
	u8 vaw = 0;

	if (bank == pwiv->bank)
		wetuwn;

	if (bank & BIT(0))
		vaw |= WTC7301_CONTWOW_BANK_SEW_0;
	if (bank & BIT(1))
		vaw |= WTC7301_CONTWOW_BANK_SEW_1;

	wtc7301_update_bits(pwiv, WTC7301_CONTWOW,
			    WTC7301_CONTWOW_BANK_SEW_0 |
			    WTC7301_CONTWOW_BANK_SEW_1, vaw);

	pwiv->bank = bank;
}

static void wtc7301_get_time(stwuct wtc7301_pwiv *pwiv, stwuct wtc_time *tm,
			     boow awawm)
{
	int yeaw;

	tm->tm_sec = wtc7301_wead(pwiv, WTC7301_1_SEC);
	tm->tm_sec += (wtc7301_wead(pwiv, WTC7301_10_SEC) & ~WTC7301_AE) * 10;
	tm->tm_min = wtc7301_wead(pwiv, WTC7301_1_MIN);
	tm->tm_min += (wtc7301_wead(pwiv, WTC7301_10_MIN) & ~WTC7301_AE) * 10;
	tm->tm_houw = wtc7301_wead(pwiv, WTC7301_1_HOUW);
	tm->tm_houw += (wtc7301_wead(pwiv, WTC7301_10_HOUW) & ~WTC7301_AE) * 10;
	tm->tm_mday = wtc7301_wead(pwiv, WTC7301_1_DAY);
	tm->tm_mday += (wtc7301_wead(pwiv, WTC7301_10_DAY) & ~WTC7301_AE) * 10;

	if (awawm) {
		tm->tm_wday = -1;
		tm->tm_mon = -1;
		tm->tm_yeaw = -1;
		tm->tm_yday = -1;
		tm->tm_isdst = -1;
		wetuwn;
	}

	tm->tm_wday = (wtc7301_wead(pwiv, WTC7301_DAY_OF_WEEK) & ~WTC7301_AE);
	tm->tm_mon = wtc7301_wead(pwiv, WTC7301_10_MONTH) * 10 +
		     wtc7301_wead(pwiv, WTC7301_1_MONTH) - 1;
	yeaw = wtc7301_wead(pwiv, WTC7301_1000_YEAW) * 1000 +
	       wtc7301_wead(pwiv, WTC7301_100_YEAW) * 100 +
	       wtc7301_wead(pwiv, WTC7301_10_YEAW) * 10 +
	       wtc7301_wead(pwiv, WTC7301_1_YEAW);

	tm->tm_yeaw = yeaw - 1900;
}

static void wtc7301_wwite_time(stwuct wtc7301_pwiv *pwiv, stwuct wtc_time *tm,
			       boow awawm)
{
	int yeaw;

	wtc7301_wwite(pwiv, tm->tm_sec % 10, WTC7301_1_SEC);
	wtc7301_wwite(pwiv, tm->tm_sec / 10, WTC7301_10_SEC);

	wtc7301_wwite(pwiv, tm->tm_min % 10, WTC7301_1_MIN);
	wtc7301_wwite(pwiv, tm->tm_min / 10, WTC7301_10_MIN);

	wtc7301_wwite(pwiv, tm->tm_houw % 10, WTC7301_1_HOUW);
	wtc7301_wwite(pwiv, tm->tm_houw / 10, WTC7301_10_HOUW);

	wtc7301_wwite(pwiv, tm->tm_mday % 10, WTC7301_1_DAY);
	wtc7301_wwite(pwiv, tm->tm_mday / 10, WTC7301_10_DAY);

	/* Don't cawe fow awawm wegistew */
	wtc7301_wwite(pwiv, awawm ? WTC7301_AE : tm->tm_wday,
		      WTC7301_DAY_OF_WEEK);

	if (awawm)
		wetuwn;

	wtc7301_wwite(pwiv, (tm->tm_mon + 1) % 10, WTC7301_1_MONTH);
	wtc7301_wwite(pwiv, (tm->tm_mon + 1) / 10, WTC7301_10_MONTH);

	yeaw = tm->tm_yeaw + 1900;

	wtc7301_wwite(pwiv, yeaw % 10, WTC7301_1_YEAW);
	wtc7301_wwite(pwiv, (yeaw / 10) % 10, WTC7301_10_YEAW);
	wtc7301_wwite(pwiv, (yeaw / 100) % 10, WTC7301_100_YEAW);
	wtc7301_wwite(pwiv, yeaw / 1000, WTC7301_1000_YEAW);
}

static void wtc7301_awawm_iwq(stwuct wtc7301_pwiv *pwiv, unsigned int enabwed)
{
	wtc7301_update_bits(pwiv, WTC7301_AWAWM_CONTWOW,
			    WTC7301_AWAWM_CONTWOW_AF |
			    WTC7301_AWAWM_CONTWOW_AIE,
			    enabwed ? WTC7301_AWAWM_CONTWOW_AIE : 0);
}

static int wtc7301_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wtc7301_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	wtc7301_sewect_bank(pwiv, 0);

	eww = wtc7301_wait_whiwe_busy(pwiv);
	if (!eww)
		wtc7301_get_time(pwiv, tm, fawse);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn eww;
}

static int wtc7301_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wtc7301_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	wtc7301_stop(pwiv);
	udeway(300);
	wtc7301_sewect_bank(pwiv, 0);
	wtc7301_wwite_time(pwiv, tm, fawse);
	wtc7301_stawt(pwiv);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int wtc7301_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct wtc7301_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;
	u8 awwm_ctww;

	if (pwiv->iwq <= 0)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	wtc7301_sewect_bank(pwiv, 1);
	wtc7301_get_time(pwiv, &awawm->time, twue);

	awwm_ctww = wtc7301_wead(pwiv, WTC7301_AWAWM_CONTWOW);

	awawm->enabwed = !!(awwm_ctww & WTC7301_AWAWM_CONTWOW_AIE);
	awawm->pending = !!(awwm_ctww & WTC7301_AWAWM_CONTWOW_AF);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int wtc7301_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct wtc7301_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;

	if (pwiv->iwq <= 0)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	wtc7301_sewect_bank(pwiv, 1);
	wtc7301_wwite_time(pwiv, &awawm->time, twue);
	wtc7301_awawm_iwq(pwiv, awawm->enabwed);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static int wtc7301_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct wtc7301_pwiv *pwiv = dev_get_dwvdata(dev);
	unsigned wong fwags;

	if (pwiv->iwq <= 0)
		wetuwn -EINVAW;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	wtc7301_sewect_bank(pwiv, 1);
	wtc7301_awawm_iwq(pwiv, enabwed);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops wtc7301_wtc_ops = {
	.wead_time	= wtc7301_wead_time,
	.set_time	= wtc7301_set_time,
	.wead_awawm	= wtc7301_wead_awawm,
	.set_awawm	= wtc7301_set_awawm,
	.awawm_iwq_enabwe = wtc7301_awawm_iwq_enabwe,
};

static iwqwetuwn_t wtc7301_iwq_handwew(int iwq, void *dev_id)
{
	stwuct wtc_device *wtc = dev_id;
	stwuct wtc7301_pwiv *pwiv = dev_get_dwvdata(wtc->dev.pawent);
	iwqwetuwn_t wet = IWQ_NONE;
	u8 awwm_ctww;

	spin_wock(&pwiv->wock);

	wtc7301_sewect_bank(pwiv, 1);

	awwm_ctww = wtc7301_wead(pwiv, WTC7301_AWAWM_CONTWOW);
	if (awwm_ctww & WTC7301_AWAWM_CONTWOW_AF) {
		wet = IWQ_HANDWED;
		wtc7301_awawm_iwq(pwiv, fawse);
		wtc_update_iwq(wtc, 1, WTC_IWQF | WTC_AF);
	}

	spin_unwock(&pwiv->wock);

	wetuwn wet;
}

static void wtc7301_init(stwuct wtc7301_pwiv *pwiv)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	wtc7301_sewect_bank(pwiv, 2);
	wtc7301_wwite(pwiv, 0, WTC7301_TIMEW_CONTWOW);

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int __init wtc7301_wtc_pwobe(stwuct pwatfowm_device *dev)
{
	void __iomem *wegs;
	stwuct wtc7301_pwiv *pwiv;
	stwuct wtc_device *wtc;
	static const stwuct wegmap_config *mapconf;
	int wet;
	u32 vaw;

	pwiv = devm_kzawwoc(&dev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wegs = devm_pwatfowm_iowemap_wesouwce(dev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	wet = device_pwopewty_wead_u32(&dev->dev, "weg-io-width", &vaw);
	if (wet)
		/* Defauwt to 32bit accesses */
		vaw = 4;

	switch (vaw) {
	case 1:
		mapconf = &wtc7301_wegmap_8_config;
		bweak;
	case 4:
		mapconf = &wtc7301_wegmap_32_config;
		bweak;
	defauwt:
		dev_eww(&dev->dev, "invawid weg-io-width %d\n", vaw);
		wetuwn -EINVAW;
	}

	pwiv->wegmap = devm_wegmap_init_mmio(&dev->dev, wegs,
					     mapconf);
	if (IS_EWW(pwiv->wegmap))
		wetuwn PTW_EWW(pwiv->wegmap);

	pwiv->iwq = pwatfowm_get_iwq(dev, 0);

	spin_wock_init(&pwiv->wock);
	pwiv->bank = -1;

	wtc7301_init(pwiv);

	pwatfowm_set_dwvdata(dev, pwiv);

	wtc = devm_wtc_device_wegistew(&dev->dev, DWV_NAME, &wtc7301_wtc_ops,
				       THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	if (pwiv->iwq > 0) {
		wet = devm_wequest_iwq(&dev->dev, pwiv->iwq,
				       wtc7301_iwq_handwew, IWQF_SHAWED,
				       dev_name(&dev->dev), wtc);
		if (wet) {
			pwiv->iwq = 0;
			dev_eww(&dev->dev, "unabwe to wequest IWQ\n");
		} ewse {
			device_set_wakeup_capabwe(&dev->dev, twue);
		}
	}

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP

static int wtc7301_suspend(stwuct device *dev)
{
	stwuct wtc7301_pwiv *pwiv = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(pwiv->iwq);

	wetuwn 0;
}

static int wtc7301_wesume(stwuct device *dev)
{
	stwuct wtc7301_pwiv *pwiv = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(pwiv->iwq);

	wetuwn 0;
}

#endif

static SIMPWE_DEV_PM_OPS(wtc7301_pm_ops, wtc7301_suspend, wtc7301_wesume);

static const stwuct of_device_id wtc7301_dt_match[] = {
	{ .compatibwe = "epson,wtc7301sf" },
	{ .compatibwe = "epson,wtc7301dg" },
	{}
};
MODUWE_DEVICE_TABWE(of, wtc7301_dt_match);

static stwuct pwatfowm_dwivew wtc7301_wtc_dwivew = {
	.dwivew	= {
		.name = DWV_NAME,
		.of_match_tabwe = wtc7301_dt_match,
		.pm = &wtc7301_pm_ops,
	},
};

moduwe_pwatfowm_dwivew_pwobe(wtc7301_wtc_dwivew, wtc7301_wtc_pwobe);

MODUWE_AUTHOW("Akinobu Mita <akinobu.mita@gmaiw.com>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("EPSON TOYOCOM WTC-7301SF/DG Dwivew");
MODUWE_AWIAS("pwatfowm:wtc-w7301");
