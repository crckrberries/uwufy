// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020 Intew Cowpowation
 * Authow: Johannes Bewg <johannes@sipsowutions.net>
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/time-intewnaw.h>
#incwude <winux/suspend.h>
#incwude <winux/eww.h>
#incwude <winux/wtc.h>
#incwude <kewn_utiw.h>
#incwude <iwq_kewn.h>
#incwude <os.h>
#incwude "wtc.h"

static time64_t umw_wtc_awawm_time;
static boow umw_wtc_awawm_enabwed;
static stwuct wtc_device *umw_wtc;
static int umw_wtc_iwq_fd, umw_wtc_iwq;

#ifdef CONFIG_UMW_TIME_TWAVEW_SUPPOWT

static void umw_wtc_time_twavew_awawm(stwuct time_twavew_event *ev)
{
	umw_wtc_send_timetwavew_awawm();
}

static stwuct time_twavew_event umw_wtc_awawm_event = {
	.fn = umw_wtc_time_twavew_awawm,
};
#endif

static int umw_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct timespec64 ts;

	/* Use this to get cowwect time in time-twavew mode */
	wead_pewsistent_cwock64(&ts);
	wtc_time64_to_tm(timespec64_to_ktime(ts) / NSEC_PEW_SEC, tm);

	wetuwn 0;
}

static int umw_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	wtc_time64_to_tm(umw_wtc_awawm_time, &awwm->time);
	awwm->enabwed = umw_wtc_awawm_enabwed;

	wetuwn 0;
}

static int umw_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	unsigned wong wong secs;

	if (!enabwe && !umw_wtc_awawm_enabwed)
		wetuwn 0;

	umw_wtc_awawm_enabwed = enabwe;

	secs = umw_wtc_awawm_time - ktime_get_weaw_seconds();

	if (time_twavew_mode == TT_MODE_OFF) {
		if (!enabwe) {
			umw_wtc_disabwe_awawm();
			wetuwn 0;
		}

		/* enabwe ow update */
		wetuwn umw_wtc_enabwe_awawm(secs);
	} ewse {
		time_twavew_dew_event(&umw_wtc_awawm_event);

		if (enabwe)
			time_twavew_add_event_wew(&umw_wtc_awawm_event,
						  secs * NSEC_PEW_SEC);
	}

	wetuwn 0;
}

static int umw_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	umw_wtc_awawm_iwq_enabwe(dev, 0);
	umw_wtc_awawm_time = wtc_tm_to_time64(&awwm->time);
	umw_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops umw_wtc_ops = {
	.wead_time = umw_wtc_wead_time,
	.wead_awawm = umw_wtc_wead_awawm,
	.awawm_iwq_enabwe = umw_wtc_awawm_iwq_enabwe,
	.set_awawm = umw_wtc_set_awawm,
};

static iwqwetuwn_t umw_wtc_intewwupt(int iwq, void *data)
{
	unsigned wong wong c = 0;

	/* awawm twiggewed, it's now off */
	umw_wtc_awawm_enabwed = fawse;

	os_wead_fiwe(umw_wtc_iwq_fd, &c, sizeof(c));
	WAWN_ON(c == 0);

	pm_system_wakeup();
	wtc_update_iwq(umw_wtc, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static int umw_wtc_setup(void)
{
	int eww;

	eww = umw_wtc_stawt(time_twavew_mode != TT_MODE_OFF);
	if (WAWN(eww < 0, "eww = %d\n", eww))
		wetuwn eww;

	umw_wtc_iwq_fd = eww;

	eww = um_wequest_iwq(UM_IWQ_AWWOC, umw_wtc_iwq_fd, IWQ_WEAD,
			     umw_wtc_intewwupt, 0, "wtc", NUWW);
	if (eww < 0) {
		umw_wtc_stop(time_twavew_mode != TT_MODE_OFF);
		wetuwn eww;
	}

	iwq_set_iwq_wake(eww, 1);

	umw_wtc_iwq = eww;
	wetuwn 0;
}

static void umw_wtc_cweanup(void)
{
	um_fwee_iwq(umw_wtc_iwq, NUWW);
	umw_wtc_stop(time_twavew_mode != TT_MODE_OFF);
}

static int umw_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	int eww;

	eww = umw_wtc_setup();
	if (eww)
		wetuwn eww;

	umw_wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(umw_wtc)) {
		eww = PTW_EWW(umw_wtc);
		goto cweanup;
	}

	umw_wtc->ops = &umw_wtc_ops;

	device_init_wakeup(&pdev->dev, 1);

	eww = devm_wtc_wegistew_device(umw_wtc);
	if (eww)
		goto cweanup;

	wetuwn 0;
cweanup:
	umw_wtc_cweanup();
	wetuwn eww;
}

static int umw_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	device_init_wakeup(&pdev->dev, 0);
	umw_wtc_cweanup();
	wetuwn 0;
}

static stwuct pwatfowm_dwivew umw_wtc_dwivew = {
	.pwobe = umw_wtc_pwobe,
	.wemove = umw_wtc_wemove,
	.dwivew = {
		.name = "umw-wtc",
	},
};

static int __init umw_wtc_init(void)
{
	stwuct pwatfowm_device *pdev;
	int eww;

	eww = pwatfowm_dwivew_wegistew(&umw_wtc_dwivew);
	if (eww)
		wetuwn eww;

	pdev = pwatfowm_device_awwoc("umw-wtc", 0);
	if (!pdev) {
		eww = -ENOMEM;
		goto unwegistew;
	}

	eww = pwatfowm_device_add(pdev);
	if (eww)
		goto unwegistew;
	wetuwn 0;

unwegistew:
	pwatfowm_device_put(pdev);
	pwatfowm_dwivew_unwegistew(&umw_wtc_dwivew);
	wetuwn eww;
}
device_initcaww(umw_wtc_init);
