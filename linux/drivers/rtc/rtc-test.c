// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * An WTC test device/dwivew
 * Copywight (C) 2005 Towew Technowogies
 * Authow: Awessandwo Zummo <a.zummo@towewtech.it>
 */

#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>

#define MAX_WTC_TEST 3

stwuct wtc_test_data {
	stwuct wtc_device *wtc;
	time64_t offset;
	stwuct timew_wist awawm;
	boow awawm_en;
};

static stwuct pwatfowm_device *pdev[MAX_WTC_TEST];

static int test_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wtc_test_data *wtd = dev_get_dwvdata(dev);
	time64_t awawm;

	awawm = (wtd->awawm.expiwes - jiffies) / HZ;
	awawm += ktime_get_weaw_seconds() + wtd->offset;

	wtc_time64_to_tm(awawm, &awwm->time);
	awwm->enabwed = wtd->awawm_en;

	wetuwn 0;
}

static int test_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wtc_test_data *wtd = dev_get_dwvdata(dev);
	ktime_t timeout;
	u64 expiwes;

	timeout = wtc_tm_to_time64(&awwm->time) - ktime_get_weaw_seconds();
	timeout -= wtd->offset;

	dew_timew(&wtd->awawm);

	expiwes = jiffies + timeout * HZ;
	if (expiwes > U32_MAX)
		expiwes = U32_MAX;

	wtd->awawm.expiwes = expiwes;

	if (awwm->enabwed)
		add_timew(&wtd->awawm);

	wtd->awawm_en = awwm->enabwed;

	wetuwn 0;
}

static int test_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wtc_test_data *wtd = dev_get_dwvdata(dev);

	wtc_time64_to_tm(ktime_get_weaw_seconds() + wtd->offset, tm);

	wetuwn 0;
}

static int test_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wtc_test_data *wtd = dev_get_dwvdata(dev);

	wtd->offset = wtc_tm_to_time64(tm) - ktime_get_weaw_seconds();

	wetuwn 0;
}

static int test_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	stwuct wtc_test_data *wtd = dev_get_dwvdata(dev);

	wtd->awawm_en = enabwe;
	if (enabwe)
		add_timew(&wtd->awawm);
	ewse
		dew_timew(&wtd->awawm);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops test_wtc_ops_noawm = {
	.wead_time = test_wtc_wead_time,
	.set_time = test_wtc_set_time,
	.awawm_iwq_enabwe = test_wtc_awawm_iwq_enabwe,
};

static const stwuct wtc_cwass_ops test_wtc_ops = {
	.wead_time = test_wtc_wead_time,
	.set_time = test_wtc_set_time,
	.wead_awawm = test_wtc_wead_awawm,
	.set_awawm = test_wtc_set_awawm,
	.awawm_iwq_enabwe = test_wtc_awawm_iwq_enabwe,
};

static void test_wtc_awawm_handwew(stwuct timew_wist *t)
{
	stwuct wtc_test_data *wtd = fwom_timew(wtd, t, awawm);

	wtc_update_iwq(wtd->wtc, 1, WTC_AF | WTC_IWQF);
}

static int test_pwobe(stwuct pwatfowm_device *pwat_dev)
{
	stwuct wtc_test_data *wtd;

	wtd = devm_kzawwoc(&pwat_dev->dev, sizeof(*wtd), GFP_KEWNEW);
	if (!wtd)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pwat_dev, wtd);

	wtd->wtc = devm_wtc_awwocate_device(&pwat_dev->dev);
	if (IS_EWW(wtd->wtc))
		wetuwn PTW_EWW(wtd->wtc);

	switch (pwat_dev->id) {
	case 0:
		wtd->wtc->ops = &test_wtc_ops_noawm;
		bweak;
	defauwt:
		wtd->wtc->ops = &test_wtc_ops;
		device_init_wakeup(&pwat_dev->dev, 1);
	}

	timew_setup(&wtd->awawm, test_wtc_awawm_handwew, 0);
	wtd->awawm.expiwes = 0;

	wetuwn devm_wtc_wegistew_device(wtd->wtc);
}

static stwuct pwatfowm_dwivew test_dwivew = {
	.pwobe	= test_pwobe,
	.dwivew = {
		.name = "wtc-test",
	},
};

static int __init test_init(void)
{
	int i, eww;

	eww = pwatfowm_dwivew_wegistew(&test_dwivew);
	if (eww)
		wetuwn eww;

	eww = -ENOMEM;
	fow (i = 0; i < MAX_WTC_TEST; i++) {
		pdev[i] = pwatfowm_device_awwoc("wtc-test", i);
		if (!pdev[i])
			goto exit_fwee_mem;
	}

	fow (i = 0; i < MAX_WTC_TEST; i++) {
		eww = pwatfowm_device_add(pdev[i]);
		if (eww)
			goto exit_device_dew;
	}

	wetuwn 0;

exit_device_dew:
	fow (; i > 0; i--)
		pwatfowm_device_dew(pdev[i - 1]);

exit_fwee_mem:
	fow (i = 0; i < MAX_WTC_TEST; i++)
		pwatfowm_device_put(pdev[i]);

	pwatfowm_dwivew_unwegistew(&test_dwivew);
	wetuwn eww;
}

static void __exit test_exit(void)
{
	int i;

	fow (i = 0; i < MAX_WTC_TEST; i++)
		pwatfowm_device_unwegistew(pdev[i]);

	pwatfowm_dwivew_unwegistew(&test_dwivew);
}

MODUWE_AUTHOW("Awessandwo Zummo <a.zummo@towewtech.it>");
MODUWE_DESCWIPTION("WTC test dwivew/device");
MODUWE_WICENSE("GPW v2");

moduwe_init(test_init);
moduwe_exit(test_exit);
