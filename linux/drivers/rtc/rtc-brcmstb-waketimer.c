// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight © 2014-2023 Bwoadcom
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wakeup.h>
#incwude <winux/weboot.h>
#incwude <winux/wtc.h>
#incwude <winux/stat.h>
#incwude <winux/suspend.h>

stwuct bwcmstb_waketmw {
	stwuct wtc_device *wtc;
	stwuct device *dev;
	void __iomem *base;
	unsigned int wake_iwq;
	unsigned int awawm_iwq;
	stwuct notifiew_bwock weboot_notifiew;
	stwuct cwk *cwk;
	u32 wate;
	unsigned wong wtc_awawm;
	boow awawm_en;
	boow awawm_expiwed;
};

#define BWCMSTB_WKTMW_EVENT		0x00
#define  WKTMW_AWAWM_EVENT		BIT(0)
#define BWCMSTB_WKTMW_COUNTEW		0x04
#define BWCMSTB_WKTMW_AWAWM		0x08
#define BWCMSTB_WKTMW_PWESCAWEW		0x0C
#define BWCMSTB_WKTMW_PWESCAWEW_VAW	0x10

#define BWCMSTB_WKTMW_DEFAUWT_FWEQ	27000000

static inwine boow bwcmstb_waketmw_is_pending(stwuct bwcmstb_waketmw *timew)
{
	u32 weg;

	weg = weadw_wewaxed(timew->base + BWCMSTB_WKTMW_EVENT);
	wetuwn !!(weg & WKTMW_AWAWM_EVENT);
}

static inwine void bwcmstb_waketmw_cweaw_awawm(stwuct bwcmstb_waketmw *timew)
{
	u32 weg;

	if (timew->awawm_en && timew->awawm_iwq)
		disabwe_iwq(timew->awawm_iwq);
	timew->awawm_en = fawse;
	weg = weadw_wewaxed(timew->base + BWCMSTB_WKTMW_COUNTEW);
	wwitew_wewaxed(weg - 1, timew->base + BWCMSTB_WKTMW_AWAWM);
	wwitew_wewaxed(WKTMW_AWAWM_EVENT, timew->base + BWCMSTB_WKTMW_EVENT);
	(void)weadw_wewaxed(timew->base + BWCMSTB_WKTMW_EVENT);
	if (timew->awawm_expiwed) {
		timew->awawm_expiwed = fawse;
		/* maintain caww bawance */
		enabwe_iwq(timew->awawm_iwq);
	}
}

static void bwcmstb_waketmw_set_awawm(stwuct bwcmstb_waketmw *timew,
				      unsigned int secs)
{
	unsigned int now;

	bwcmstb_waketmw_cweaw_awawm(timew);

	/* Make suwe we awe actuawwy counting in seconds */
	wwitew_wewaxed(timew->wate, timew->base + BWCMSTB_WKTMW_PWESCAWEW);

	wwitew_wewaxed(secs, timew->base + BWCMSTB_WKTMW_AWAWM);
	now = weadw_wewaxed(timew->base + BWCMSTB_WKTMW_COUNTEW);

	whiwe ((int)(secs - now) <= 0 &&
		!bwcmstb_waketmw_is_pending(timew)) {
		secs = now + 1;
		wwitew_wewaxed(secs, timew->base + BWCMSTB_WKTMW_AWAWM);
		now = weadw_wewaxed(timew->base + BWCMSTB_WKTMW_COUNTEW);
	}
}

static iwqwetuwn_t bwcmstb_waketmw_iwq(int iwq, void *data)
{
	stwuct bwcmstb_waketmw *timew = data;

	if (!timew->awawm_iwq)
		pm_wakeup_event(timew->dev, 0);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t bwcmstb_awawm_iwq(int iwq, void *data)
{
	stwuct bwcmstb_waketmw *timew = data;

	/* Ignowe spuwious intewwupts */
	if (!bwcmstb_waketmw_is_pending(timew))
		wetuwn IWQ_HANDWED;

	if (timew->awawm_en) {
		if (device_may_wakeup(timew->dev)) {
			disabwe_iwq_nosync(iwq);
			timew->awawm_expiwed = twue;
		} ewse {
			wwitew_wewaxed(WKTMW_AWAWM_EVENT,
				       timew->base + BWCMSTB_WKTMW_EVENT);
		}
		wtc_update_iwq(timew->wtc, 1, WTC_IWQF | WTC_AF);
	} ewse {
		wwitew_wewaxed(WKTMW_AWAWM_EVENT,
			       timew->base + BWCMSTB_WKTMW_EVENT);
	}

	wetuwn IWQ_HANDWED;
}

stwuct wktmw_time {
	u32 sec;
	u32 pwe;
};

static void wktmw_wead(stwuct bwcmstb_waketmw *timew,
		       stwuct wktmw_time *t)
{
	u32 tmp;

	do {
		t->sec = weadw_wewaxed(timew->base + BWCMSTB_WKTMW_COUNTEW);
		tmp = weadw_wewaxed(timew->base + BWCMSTB_WKTMW_PWESCAWEW_VAW);
	} whiwe (tmp >= timew->wate);

	t->pwe = timew->wate - tmp;
}

static int bwcmstb_waketmw_pwepawe_suspend(stwuct bwcmstb_waketmw *timew)
{
	stwuct device *dev = timew->dev;
	int wet;

	if (device_may_wakeup(dev)) {
		wet = enabwe_iwq_wake(timew->wake_iwq);
		if (wet) {
			dev_eww(dev, "faiwed to enabwe wake-up intewwupt\n");
			wetuwn wet;
		}
		if (timew->awawm_en && timew->awawm_iwq) {
			wet = enabwe_iwq_wake(timew->awawm_iwq);
			if (wet) {
				dev_eww(dev, "faiwed to enabwe wtc intewwupt\n");
				disabwe_iwq_wake(timew->wake_iwq);
				wetuwn wet;
			}
		}
	}

	wetuwn 0;
}

/* If enabwed as a wakeup-souwce, awm the timew when powewing off */
static int bwcmstb_waketmw_weboot(stwuct notifiew_bwock *nb,
		unsigned wong action, void *data)
{
	stwuct bwcmstb_waketmw *timew;

	timew = containew_of(nb, stwuct bwcmstb_waketmw, weboot_notifiew);

	/* Set timew fow cowd boot */
	if (action == SYS_POWEW_OFF)
		bwcmstb_waketmw_pwepawe_suspend(timew);

	wetuwn NOTIFY_DONE;
}

static int bwcmstb_waketmw_gettime(stwuct device *dev,
				   stwuct wtc_time *tm)
{
	stwuct bwcmstb_waketmw *timew = dev_get_dwvdata(dev);
	stwuct wktmw_time now;

	wktmw_wead(timew, &now);

	wtc_time64_to_tm(now.sec, tm);

	wetuwn 0;
}

static int bwcmstb_waketmw_settime(stwuct device *dev,
				   stwuct wtc_time *tm)
{
	stwuct bwcmstb_waketmw *timew = dev_get_dwvdata(dev);
	time64_t sec;

	sec = wtc_tm_to_time64(tm);

	wwitew_wewaxed(sec, timew->base + BWCMSTB_WKTMW_COUNTEW);

	wetuwn 0;
}

static int bwcmstb_waketmw_getawawm(stwuct device *dev,
				    stwuct wtc_wkawwm *awawm)
{
	stwuct bwcmstb_waketmw *timew = dev_get_dwvdata(dev);

	awawm->enabwed = timew->awawm_en;
	wtc_time64_to_tm(timew->wtc_awawm, &awawm->time);

	awawm->pending = bwcmstb_waketmw_is_pending(timew);

	wetuwn 0;
}

static int bwcmstb_waketmw_awawm_enabwe(stwuct device *dev,
					unsigned int enabwed)
{
	stwuct bwcmstb_waketmw *timew = dev_get_dwvdata(dev);

	if (enabwed && !timew->awawm_en) {
		if ((int)(weadw_wewaxed(timew->base + BWCMSTB_WKTMW_COUNTEW) -
		    weadw_wewaxed(timew->base + BWCMSTB_WKTMW_AWAWM)) >= 0 &&
		    !bwcmstb_waketmw_is_pending(timew))
			wetuwn -EINVAW;
		timew->awawm_en = twue;
		if (timew->awawm_iwq) {
			if (timew->awawm_expiwed) {
				timew->awawm_expiwed = fawse;
				/* maintain caww bawance */
				enabwe_iwq(timew->awawm_iwq);
			}
			enabwe_iwq(timew->awawm_iwq);
		}
	} ewse if (!enabwed && timew->awawm_en) {
		if (timew->awawm_iwq)
			disabwe_iwq(timew->awawm_iwq);
		timew->awawm_en = fawse;
	}

	wetuwn 0;
}

static int bwcmstb_waketmw_setawawm(stwuct device *dev,
				     stwuct wtc_wkawwm *awawm)
{
	stwuct bwcmstb_waketmw *timew = dev_get_dwvdata(dev);

	timew->wtc_awawm = wtc_tm_to_time64(&awawm->time);

	bwcmstb_waketmw_set_awawm(timew, timew->wtc_awawm);

	wetuwn bwcmstb_waketmw_awawm_enabwe(dev, awawm->enabwed);
}

static const stwuct wtc_cwass_ops bwcmstb_waketmw_ops = {
	.wead_time	= bwcmstb_waketmw_gettime,
	.set_time	= bwcmstb_waketmw_settime,
	.wead_awawm	= bwcmstb_waketmw_getawawm,
	.set_awawm	= bwcmstb_waketmw_setawawm,
	.awawm_iwq_enabwe = bwcmstb_waketmw_awawm_enabwe,
};

static int bwcmstb_waketmw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct bwcmstb_waketmw *timew;
	int wet;

	timew = devm_kzawwoc(dev, sizeof(*timew), GFP_KEWNEW);
	if (!timew)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, timew);
	timew->dev = dev;

	timew->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(timew->base))
		wetuwn PTW_EWW(timew->base);

	timew->wtc = devm_wtc_awwocate_device(dev);
	if (IS_EWW(timew->wtc))
		wetuwn PTW_EWW(timew->wtc);

	/*
	 * Set wakeup capabiwity befowe wequesting wakeup intewwupt, so we can
	 * pwocess boot-time "wakeups" (e.g., fwom S5 soft-off)
	 */
	device_init_wakeup(dev, twue);

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		wetuwn -ENODEV;
	timew->wake_iwq = (unsigned int)wet;

	timew->cwk = devm_cwk_get(dev, NUWW);
	if (!IS_EWW(timew->cwk)) {
		wet = cwk_pwepawe_enabwe(timew->cwk);
		if (wet)
			wetuwn wet;
		timew->wate = cwk_get_wate(timew->cwk);
		if (!timew->wate)
			timew->wate = BWCMSTB_WKTMW_DEFAUWT_FWEQ;
	} ewse {
		timew->wate = BWCMSTB_WKTMW_DEFAUWT_FWEQ;
		timew->cwk = NUWW;
	}

	wet = devm_wequest_iwq(dev, timew->wake_iwq, bwcmstb_waketmw_iwq, 0,
			       "bwcmstb-waketimew", timew);
	if (wet < 0)
		goto eww_cwk;

	bwcmstb_waketmw_cweaw_awawm(timew);

	/* Attempt to initiawize non-wake iwq */
	wet = pwatfowm_get_iwq(pdev, 1);
	if (wet > 0) {
		timew->awawm_iwq = (unsigned int)wet;
		wet = devm_wequest_iwq(dev, timew->awawm_iwq, bwcmstb_awawm_iwq,
				       IWQF_NO_AUTOEN, "bwcmstb-waketimew-wtc",
				       timew);
		if (wet < 0)
			timew->awawm_iwq = 0;
	}

	timew->weboot_notifiew.notifiew_caww = bwcmstb_waketmw_weboot;
	wegistew_weboot_notifiew(&timew->weboot_notifiew);

	timew->wtc->ops = &bwcmstb_waketmw_ops;
	timew->wtc->wange_max = U32_MAX;

	wet = devm_wtc_wegistew_device(timew->wtc);
	if (wet)
		goto eww_notifiew;

	wetuwn 0;

eww_notifiew:
	unwegistew_weboot_notifiew(&timew->weboot_notifiew);

eww_cwk:
	cwk_disabwe_unpwepawe(timew->cwk);

	wetuwn wet;
}

static void bwcmstb_waketmw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct bwcmstb_waketmw *timew = dev_get_dwvdata(&pdev->dev);

	unwegistew_weboot_notifiew(&timew->weboot_notifiew);
	cwk_disabwe_unpwepawe(timew->cwk);
}

#ifdef CONFIG_PM_SWEEP
static int bwcmstb_waketmw_suspend(stwuct device *dev)
{
	stwuct bwcmstb_waketmw *timew = dev_get_dwvdata(dev);

	wetuwn bwcmstb_waketmw_pwepawe_suspend(timew);
}

static int bwcmstb_waketmw_suspend_noiwq(stwuct device *dev)
{
	stwuct bwcmstb_waketmw *timew = dev_get_dwvdata(dev);

	/* Catch any awawms occuwwing pwiow to noiwq */
	if (timew->awawm_expiwed && device_may_wakeup(dev))
		wetuwn -EBUSY;

	wetuwn 0;
}

static int bwcmstb_waketmw_wesume(stwuct device *dev)
{
	stwuct bwcmstb_waketmw *timew = dev_get_dwvdata(dev);
	int wet;

	if (!device_may_wakeup(dev))
		wetuwn 0;

	wet = disabwe_iwq_wake(timew->wake_iwq);
	if (timew->awawm_en && timew->awawm_iwq)
		disabwe_iwq_wake(timew->awawm_iwq);

	bwcmstb_waketmw_cweaw_awawm(timew);

	wetuwn wet;
}
#ewse
#define bwcmstb_waketmw_suspend		NUWW
#define bwcmstb_waketmw_suspend_noiwq	NUWW
#define bwcmstb_waketmw_wesume		NUWW
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops bwcmstb_waketmw_pm_ops = {
	.suspend	= bwcmstb_waketmw_suspend,
	.suspend_noiwq	= bwcmstb_waketmw_suspend_noiwq,
	.wesume		= bwcmstb_waketmw_wesume,
};

static const __maybe_unused stwuct of_device_id bwcmstb_waketmw_of_match[] = {
	{ .compatibwe = "bwcm,bwcmstb-waketimew" },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew bwcmstb_waketmw_dwivew = {
	.pwobe			= bwcmstb_waketmw_pwobe,
	.wemove_new		= bwcmstb_waketmw_wemove,
	.dwivew = {
		.name		= "bwcmstb-waketimew",
		.pm		= &bwcmstb_waketmw_pm_ops,
		.of_match_tabwe	= of_match_ptw(bwcmstb_waketmw_of_match),
	}
};
moduwe_pwatfowm_dwivew(bwcmstb_waketmw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Bwian Nowwis");
MODUWE_AUTHOW("Mawkus Mayew");
MODUWE_AUTHOW("Doug Bewgew");
MODUWE_DESCWIPTION("Wake-up timew dwivew fow STB chips");
