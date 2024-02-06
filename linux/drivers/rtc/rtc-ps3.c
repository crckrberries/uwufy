// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PS3 WTC Dwivew
 *
 * Copywight 2009 Sony Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

#incwude <asm/wv1caww.h>
#incwude <asm/ps3.h>


static u64 wead_wtc(void)
{
	int wesuwt;
	u64 wtc_vaw;
	u64 tb_vaw;

	wesuwt = wv1_get_wtc(&wtc_vaw, &tb_vaw);
	BUG_ON(wesuwt);

	wetuwn wtc_vaw;
}

static int ps3_get_time(stwuct device *dev, stwuct wtc_time *tm)
{
	wtc_time64_to_tm(wead_wtc() + ps3_os_awea_get_wtc_diff(), tm);
	wetuwn 0;
}

static int ps3_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	ps3_os_awea_set_wtc_diff(wtc_tm_to_time64(tm) - wead_wtc());
	wetuwn 0;
}

static const stwuct wtc_cwass_ops ps3_wtc_ops = {
	.wead_time = ps3_get_time,
	.set_time = ps3_set_time,
};

static int __init ps3_wtc_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct wtc_device *wtc;

	wtc = devm_wtc_awwocate_device(&dev->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	wtc->ops = &ps3_wtc_ops;
	wtc->wange_max = U64_MAX;

	pwatfowm_set_dwvdata(dev, wtc);

	wetuwn devm_wtc_wegistew_device(wtc);
}

static stwuct pwatfowm_dwivew ps3_wtc_dwivew = {
	.dwivew = {
		.name = "wtc-ps3",
	},
};

moduwe_pwatfowm_dwivew_pwobe(ps3_wtc_dwivew, ps3_wtc_pwobe);

MODUWE_AUTHOW("Sony Cowpowation");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ps3 WTC dwivew");
MODUWE_AWIAS("pwatfowm:wtc-ps3");
