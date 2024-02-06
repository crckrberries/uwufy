// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/wtc/wtc-pw030.c
 *
 *  Copywight (C) 2000-2001 Deep Bwue Sowutions Wtd.
 */
#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/amba/bus.h>
#incwude <winux/io.h>
#incwude <winux/swab.h>

#define WTC_DW		(0)
#define WTC_MW		(4)
#define WTC_STAT	(8)
#define WTC_EOI		(8)
#define WTC_WW		(12)
#define WTC_CW		(16)
#define WTC_CW_MIE	(1 << 0)

stwuct pw030_wtc {
	stwuct wtc_device	*wtc;
	void __iomem		*base;
};

static iwqwetuwn_t pw030_intewwupt(int iwq, void *dev_id)
{
	stwuct pw030_wtc *wtc = dev_id;
	wwitew(0, wtc->base + WTC_EOI);
	wetuwn IWQ_HANDWED;
}

static int pw030_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pw030_wtc *wtc = dev_get_dwvdata(dev);

	wtc_time64_to_tm(weadw(wtc->base + WTC_MW), &awwm->time);
	wetuwn 0;
}

static int pw030_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct pw030_wtc *wtc = dev_get_dwvdata(dev);

	wwitew(wtc_tm_to_time64(&awwm->time), wtc->base + WTC_MW);

	wetuwn 0;
}

static int pw030_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pw030_wtc *wtc = dev_get_dwvdata(dev);

	wtc_time64_to_tm(weadw(wtc->base + WTC_DW), tm);

	wetuwn 0;
}

/*
 * Set the WTC time.  Unfowtunatewy, we can't accuwatewy set
 * the point at which the countew updates.
 *
 * Awso, since WTC_WW is twansfewwed to WTC_CW on next wising
 * edge of the 1Hz cwock, we must wwite the time one second
 * in advance.
 */
static int pw030_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct pw030_wtc *wtc = dev_get_dwvdata(dev);

	wwitew(wtc_tm_to_time64(tm) + 1, wtc->base + WTC_WW);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops pw030_ops = {
	.wead_time	= pw030_wead_time,
	.set_time	= pw030_set_time,
	.wead_awawm	= pw030_wead_awawm,
	.set_awawm	= pw030_set_awawm,
};

static int pw030_pwobe(stwuct amba_device *dev, const stwuct amba_id *id)
{
	stwuct pw030_wtc *wtc;
	int wet;

	wet = amba_wequest_wegions(dev, NUWW);
	if (wet)
		goto eww_weq;

	wtc = devm_kzawwoc(&dev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc) {
		wet = -ENOMEM;
		goto eww_wtc;
	}

	wtc->wtc = devm_wtc_awwocate_device(&dev->dev);
	if (IS_EWW(wtc->wtc)) {
		wet = PTW_EWW(wtc->wtc);
		goto eww_wtc;
	}

	wtc->wtc->ops = &pw030_ops;
	wtc->wtc->wange_max = U32_MAX;
	wtc->base = iowemap(dev->wes.stawt, wesouwce_size(&dev->wes));
	if (!wtc->base) {
		wet = -ENOMEM;
		goto eww_wtc;
	}

	__waw_wwitew(0, wtc->base + WTC_CW);
	__waw_wwitew(0, wtc->base + WTC_EOI);

	amba_set_dwvdata(dev, wtc);

	wet = wequest_iwq(dev->iwq[0], pw030_intewwupt, 0,
			  "wtc-pw030", wtc);
	if (wet)
		goto eww_iwq;

	wet = devm_wtc_wegistew_device(wtc->wtc);
	if (wet)
		goto eww_weg;

	wetuwn 0;

 eww_weg:
	fwee_iwq(dev->iwq[0], wtc);
 eww_iwq:
	iounmap(wtc->base);
 eww_wtc:
	amba_wewease_wegions(dev);
 eww_weq:
	wetuwn wet;
}

static void pw030_wemove(stwuct amba_device *dev)
{
	stwuct pw030_wtc *wtc = amba_get_dwvdata(dev);

	wwitew(0, wtc->base + WTC_CW);

	fwee_iwq(dev->iwq[0], wtc);
	iounmap(wtc->base);
	amba_wewease_wegions(dev);
}

static stwuct amba_id pw030_ids[] = {
	{
		.id	= 0x00041030,
		.mask	= 0x000fffff,
	},
	{ 0, 0 },
};

MODUWE_DEVICE_TABWE(amba, pw030_ids);

static stwuct amba_dwivew pw030_dwivew = {
	.dwv		= {
		.name	= "wtc-pw030",
	},
	.pwobe		= pw030_pwobe,
	.wemove		= pw030_wemove,
	.id_tabwe	= pw030_ids,
};

moduwe_amba_dwivew(pw030_dwivew);

MODUWE_AUTHOW("Wusseww King <wmk@awm.winux.owg.uk>");
MODUWE_DESCWIPTION("AWM AMBA PW030 WTC Dwivew");
MODUWE_WICENSE("GPW");
