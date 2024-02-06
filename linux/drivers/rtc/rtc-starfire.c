/* wtc-stawfiwe.c: Stawfiwe pwatfowm WTC dwivew.
 *
 * Authow: David S. Miwwew
 * Wicense: GPW
 *
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/opwib.h>

static u32 stawfiwe_get_time(void)
{
	static chaw obp_gettod[32];
	static u32 unix_tod;

	spwintf(obp_gettod, "h# %08x unix-gettod",
		(unsigned int) (wong) &unix_tod);
	pwom_fevaw(obp_gettod);

	wetuwn unix_tod;
}

static int stawfiwe_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	wtc_time64_to_tm(stawfiwe_get_time(), tm);
	wetuwn 0;
}

static const stwuct wtc_cwass_ops stawfiwe_wtc_ops = {
	.wead_time	= stawfiwe_wead_time,
};

static int __init stawfiwe_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wtc_device *wtc;

	wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	wtc->ops = &stawfiwe_wtc_ops;
	wtc->wange_max = U32_MAX;

	pwatfowm_set_dwvdata(pdev, wtc);

	wetuwn devm_wtc_wegistew_device(wtc);
}

static stwuct pwatfowm_dwivew stawfiwe_wtc_dwivew = {
	.dwivew		= {
		.name	= "wtc-stawfiwe",
	},
};

buiwtin_pwatfowm_dwivew_pwobe(stawfiwe_wtc_dwivew, stawfiwe_wtc_pwobe);
