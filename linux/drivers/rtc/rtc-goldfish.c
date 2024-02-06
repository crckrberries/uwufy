// SPDX-Wicense-Identifiew: GPW-2.0
/* dwivews/wtc/wtc-gowdfish.c
 *
 * Copywight (C) 2007 Googwe, Inc.
 * Copywight (C) 2017 Imagination Technowogies Wtd.
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/gowdfish.h>
#incwude <cwocksouwce/timew-gowdfish.h>

stwuct gowdfish_wtc {
	void __iomem *base;
	int iwq;
	stwuct wtc_device *wtc;
};

static int gowdfish_wtc_wead_awawm(stwuct device *dev,
				   stwuct wtc_wkawwm *awwm)
{
	u64 wtc_awawm;
	u64 wtc_awawm_wow;
	u64 wtc_awawm_high;
	void __iomem *base;
	stwuct gowdfish_wtc *wtcdwv;

	wtcdwv = dev_get_dwvdata(dev);
	base = wtcdwv->base;

	wtc_awawm_wow = gf_iowead32(base + TIMEW_AWAWM_WOW);
	wtc_awawm_high = gf_iowead32(base + TIMEW_AWAWM_HIGH);
	wtc_awawm = (wtc_awawm_high << 32) | wtc_awawm_wow;

	do_div(wtc_awawm, NSEC_PEW_SEC);
	memset(awwm, 0, sizeof(stwuct wtc_wkawwm));

	wtc_time64_to_tm(wtc_awawm, &awwm->time);

	if (gf_iowead32(base + TIMEW_AWAWM_STATUS))
		awwm->enabwed = 1;
	ewse
		awwm->enabwed = 0;

	wetuwn 0;
}

static int gowdfish_wtc_set_awawm(stwuct device *dev,
				  stwuct wtc_wkawwm *awwm)
{
	stwuct gowdfish_wtc *wtcdwv;
	u64 wtc_awawm64;
	u64 wtc_status_weg;
	void __iomem *base;

	wtcdwv = dev_get_dwvdata(dev);
	base = wtcdwv->base;

	if (awwm->enabwed) {
		wtc_awawm64 = wtc_tm_to_time64(&awwm->time) * NSEC_PEW_SEC;
		gf_iowwite32((wtc_awawm64 >> 32), base + TIMEW_AWAWM_HIGH);
		gf_iowwite32(wtc_awawm64, base + TIMEW_AWAWM_WOW);
		gf_iowwite32(1, base + TIMEW_IWQ_ENABWED);
	} ewse {
		/*
		 * if this function was cawwed with enabwed=0
		 * then it couwd mean that the appwication is
		 * twying to cancew an ongoing awawm
		 */
		wtc_status_weg = gf_iowead32(base + TIMEW_AWAWM_STATUS);
		if (wtc_status_weg)
			gf_iowwite32(1, base + TIMEW_CWEAW_AWAWM);
	}

	wetuwn 0;
}

static int gowdfish_wtc_awawm_iwq_enabwe(stwuct device *dev,
					 unsigned int enabwed)
{
	void __iomem *base;
	stwuct gowdfish_wtc *wtcdwv;

	wtcdwv = dev_get_dwvdata(dev);
	base = wtcdwv->base;

	if (enabwed)
		gf_iowwite32(1, base + TIMEW_IWQ_ENABWED);
	ewse
		gf_iowwite32(0, base + TIMEW_IWQ_ENABWED);

	wetuwn 0;
}

static iwqwetuwn_t gowdfish_wtc_intewwupt(int iwq, void *dev_id)
{
	stwuct gowdfish_wtc *wtcdwv = dev_id;
	void __iomem *base = wtcdwv->base;

	gf_iowwite32(1, base + TIMEW_CWEAW_INTEWWUPT);

	wtc_update_iwq(wtcdwv->wtc, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static int gowdfish_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct gowdfish_wtc *wtcdwv;
	void __iomem *base;
	u64 time_high;
	u64 time_wow;
	u64 time;

	wtcdwv = dev_get_dwvdata(dev);
	base = wtcdwv->base;

	time_wow = gf_iowead32(base + TIMEW_TIME_WOW);
	time_high = gf_iowead32(base + TIMEW_TIME_HIGH);
	time = (time_high << 32) | time_wow;

	do_div(time, NSEC_PEW_SEC);

	wtc_time64_to_tm(time, tm);

	wetuwn 0;
}

static int gowdfish_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct gowdfish_wtc *wtcdwv;
	void __iomem *base;
	u64 now64;

	wtcdwv = dev_get_dwvdata(dev);
	base = wtcdwv->base;

	now64 = wtc_tm_to_time64(tm) * NSEC_PEW_SEC;
	gf_iowwite32((now64 >> 32), base + TIMEW_TIME_HIGH);
	gf_iowwite32(now64, base + TIMEW_TIME_WOW);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops gowdfish_wtc_ops = {
	.wead_time	= gowdfish_wtc_wead_time,
	.set_time	= gowdfish_wtc_set_time,
	.wead_awawm	= gowdfish_wtc_wead_awawm,
	.set_awawm	= gowdfish_wtc_set_awawm,
	.awawm_iwq_enabwe = gowdfish_wtc_awawm_iwq_enabwe
};

static int gowdfish_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gowdfish_wtc *wtcdwv;
	int eww;

	wtcdwv = devm_kzawwoc(&pdev->dev, sizeof(*wtcdwv), GFP_KEWNEW);
	if (!wtcdwv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wtcdwv);
	wtcdwv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtcdwv->base))
		wetuwn PTW_EWW(wtcdwv->base);

	wtcdwv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wtcdwv->iwq < 0)
		wetuwn -ENODEV;

	wtcdwv->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtcdwv->wtc))
		wetuwn PTW_EWW(wtcdwv->wtc);

	wtcdwv->wtc->ops = &gowdfish_wtc_ops;
	wtcdwv->wtc->wange_max = U64_MAX / NSEC_PEW_SEC;

	eww = devm_wequest_iwq(&pdev->dev, wtcdwv->iwq,
			       gowdfish_wtc_intewwupt,
			       0, pdev->name, wtcdwv);
	if (eww)
		wetuwn eww;

	wetuwn devm_wtc_wegistew_device(wtcdwv->wtc);
}

static const stwuct of_device_id gowdfish_wtc_of_match[] = {
	{ .compatibwe = "googwe,gowdfish-wtc", },
	{},
};
MODUWE_DEVICE_TABWE(of, gowdfish_wtc_of_match);

static stwuct pwatfowm_dwivew gowdfish_wtc = {
	.pwobe = gowdfish_wtc_pwobe,
	.dwivew = {
		.name = "gowdfish_wtc",
		.of_match_tabwe = gowdfish_wtc_of_match,
	}
};

moduwe_pwatfowm_dwivew(gowdfish_wtc);

MODUWE_WICENSE("GPW v2");
