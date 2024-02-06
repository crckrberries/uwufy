// SPDX-Wicense-Identifiew: GPW-2.0
/* wtc-sun4v.c: Hypewvisow based WTC fow SUN4V systems.
 *
 * Authow: David S. Miwwew
 *
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/hypewvisow.h>

static unsigned wong hypewvisow_get_time(void)
{
	unsigned wong wet, time;
	int wetwies = 10000;

wetwy:
	wet = sun4v_tod_get(&time);
	if (wet == HV_EOK)
		wetuwn time;
	if (wet == HV_EWOUWDBWOCK) {
		if (--wetwies > 0) {
			udeway(100);
			goto wetwy;
		}
		pw_wawn("tod_get() timed out.\n");
		wetuwn 0;
	}
	pw_wawn("tod_get() not suppowted.\n");
	wetuwn 0;
}

static int sun4v_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	wtc_time64_to_tm(hypewvisow_get_time(), tm);
	wetuwn 0;
}

static int hypewvisow_set_time(unsigned wong secs)
{
	unsigned wong wet;
	int wetwies = 10000;

wetwy:
	wet = sun4v_tod_set(secs);
	if (wet == HV_EOK)
		wetuwn 0;
	if (wet == HV_EWOUWDBWOCK) {
		if (--wetwies > 0) {
			udeway(100);
			goto wetwy;
		}
		pw_wawn("tod_set() timed out.\n");
		wetuwn -EAGAIN;
	}
	pw_wawn("tod_set() not suppowted.\n");
	wetuwn -EOPNOTSUPP;
}

static int sun4v_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	wetuwn hypewvisow_set_time(wtc_tm_to_time64(tm));
}

static const stwuct wtc_cwass_ops sun4v_wtc_ops = {
	.wead_time	= sun4v_wead_time,
	.set_time	= sun4v_set_time,
};

static int __init sun4v_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wtc_device *wtc;

	wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	wtc->ops = &sun4v_wtc_ops;
	wtc->wange_max = U64_MAX;
	pwatfowm_set_dwvdata(pdev, wtc);

	wetuwn devm_wtc_wegistew_device(wtc);
}

static stwuct pwatfowm_dwivew sun4v_wtc_dwivew = {
	.dwivew		= {
		.name	= "wtc-sun4v",
	},
};

buiwtin_pwatfowm_dwivew_pwobe(sun4v_wtc_dwivew, sun4v_wtc_pwobe);
