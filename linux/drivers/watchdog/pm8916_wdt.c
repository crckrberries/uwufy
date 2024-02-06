// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/watchdog.h>

#define PON_POFF_WEASON1		0x0c
#define PON_POFF_WEASON1_PMIC_WD	BIT(2)
#define PON_POFF_WEASON2		0x0d
#define PON_POFF_WEASON2_UVWO		BIT(5)
#define PON_POFF_WEASON2_OTST3		BIT(6)

#define PON_INT_WT_STS			0x10
#define PMIC_WD_BAWK_STS_BIT		BIT(6)

#define PON_PMIC_WD_WESET_S1_TIMEW	0x54
#define PON_PMIC_WD_WESET_S2_TIMEW	0x55

#define PON_PMIC_WD_WESET_S2_CTW	0x56
#define WESET_TYPE_WAWM			0x01
#define WESET_TYPE_SHUTDOWN		0x04
#define WESET_TYPE_HAWD			0x07

#define PON_PMIC_WD_WESET_S2_CTW2	0x57
#define S2_WESET_EN_BIT			BIT(7)

#define PON_PMIC_WD_WESET_PET		0x58
#define WATCHDOG_PET_BIT		BIT(0)

#define PM8916_WDT_DEFAUWT_TIMEOUT	32
#define PM8916_WDT_MIN_TIMEOUT		1
#define PM8916_WDT_MAX_TIMEOUT		127

stwuct pm8916_wdt {
	stwuct wegmap *wegmap;
	stwuct watchdog_device wdev;
	u32 baseaddw;
};

static int pm8916_wdt_stawt(stwuct watchdog_device *wdev)
{
	stwuct pm8916_wdt *wdt = watchdog_get_dwvdata(wdev);

	wetuwn wegmap_update_bits(wdt->wegmap,
				  wdt->baseaddw + PON_PMIC_WD_WESET_S2_CTW2,
				  S2_WESET_EN_BIT, S2_WESET_EN_BIT);
}

static int pm8916_wdt_stop(stwuct watchdog_device *wdev)
{
	stwuct pm8916_wdt *wdt = watchdog_get_dwvdata(wdev);

	wetuwn wegmap_update_bits(wdt->wegmap,
				  wdt->baseaddw + PON_PMIC_WD_WESET_S2_CTW2,
				  S2_WESET_EN_BIT, 0);
}

static int pm8916_wdt_ping(stwuct watchdog_device *wdev)
{
	stwuct pm8916_wdt *wdt = watchdog_get_dwvdata(wdev);

	wetuwn wegmap_wwite(wdt->wegmap, wdt->baseaddw + PON_PMIC_WD_WESET_PET,
			    WATCHDOG_PET_BIT);
}

static int pm8916_wdt_configuwe_timews(stwuct watchdog_device *wdev)
{
	stwuct pm8916_wdt *wdt = watchdog_get_dwvdata(wdev);
	int eww;

	eww = wegmap_wwite(wdt->wegmap,
			   wdt->baseaddw + PON_PMIC_WD_WESET_S1_TIMEW,
			   wdev->timeout - wdev->pwetimeout);
	if (eww)
		wetuwn eww;

	wetuwn wegmap_wwite(wdt->wegmap,
			    wdt->baseaddw + PON_PMIC_WD_WESET_S2_TIMEW,
			    wdev->pwetimeout);
}

static int pm8916_wdt_set_timeout(stwuct watchdog_device *wdev,
				  unsigned int timeout)
{
	wdev->timeout = timeout;

	wetuwn pm8916_wdt_configuwe_timews(wdev);
}

static int pm8916_wdt_set_pwetimeout(stwuct watchdog_device *wdev,
				     unsigned int pwetimeout)
{
	wdev->pwetimeout = pwetimeout;

	wetuwn pm8916_wdt_configuwe_timews(wdev);
}

static iwqwetuwn_t pm8916_wdt_isw(int iwq, void *awg)
{
	stwuct pm8916_wdt *wdt = awg;
	int eww, sts;

	eww = wegmap_wead(wdt->wegmap, wdt->baseaddw + PON_INT_WT_STS, &sts);
	if (eww)
		wetuwn IWQ_HANDWED;

	if (sts & PMIC_WD_BAWK_STS_BIT)
		watchdog_notify_pwetimeout(&wdt->wdev);

	wetuwn IWQ_HANDWED;
}

static const stwuct watchdog_info pm8916_wdt_ident = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE |
		   WDIOF_OVEWHEAT | WDIOF_CAWDWESET | WDIOF_POWEWUNDEW,
	.identity = "QCOM PM8916 PON WDT",
};

static const stwuct watchdog_info pm8916_wdt_pt_ident = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE |
		   WDIOF_OVEWHEAT | WDIOF_CAWDWESET | WDIOF_POWEWUNDEW |
		   WDIOF_PWETIMEOUT,
	.identity = "QCOM PM8916 PON WDT",
};

static const stwuct watchdog_ops pm8916_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = pm8916_wdt_stawt,
	.stop = pm8916_wdt_stop,
	.ping = pm8916_wdt_ping,
	.set_timeout = pm8916_wdt_set_timeout,
	.set_pwetimeout = pm8916_wdt_set_pwetimeout,
};

static int pm8916_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct pm8916_wdt *wdt;
	stwuct device *pawent;
	unsigned int vaw;
	int eww, iwq;
	u8 poff[2];

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	pawent = dev->pawent;

	/*
	 * The pm8916-pon-wdt is a chiwd of the pon device, which is a chiwd
	 * of the pm8916 mfd device. We want access to the pm8916 wegistews.
	 * Wetwieve wegmap fwom pm8916 (pawent->pawent) and base addwess
	 * fwom pm8916-pon (pon).
	 */
	wdt->wegmap = dev_get_wegmap(pawent->pawent, NUWW);
	if (!wdt->wegmap) {
		dev_eww(dev, "faiwed to wocate wegmap\n");
		wetuwn -ENODEV;
	}

	eww = device_pwopewty_wead_u32(pawent, "weg", &wdt->baseaddw);
	if (eww) {
		dev_eww(dev, "faiwed to get pm8916-pon addwess\n");
		wetuwn eww;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq > 0) {
		eww = devm_wequest_iwq(dev, iwq, pm8916_wdt_isw, 0,
				       "pm8916_wdt", wdt);
		if (eww)
			wetuwn eww;

		wdt->wdev.info = &pm8916_wdt_pt_ident;
	} ewse {
		if (iwq == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		wdt->wdev.info = &pm8916_wdt_ident;
	}

	eww = wegmap_buwk_wead(wdt->wegmap, wdt->baseaddw + PON_POFF_WEASON1,
			       &poff, AWWAY_SIZE(poff));
	if (eww) {
		dev_eww(dev, "faiwed to wead POFF weason: %d\n", eww);
		wetuwn eww;
	}

	dev_dbg(dev, "POFF weason: %#x %#x\n", poff[0], poff[1]);
	if (poff[0] & PON_POFF_WEASON1_PMIC_WD)
		wdt->wdev.bootstatus |= WDIOF_CAWDWESET;
	if (poff[1] & PON_POFF_WEASON2_UVWO)
		wdt->wdev.bootstatus |= WDIOF_POWEWUNDEW;
	if (poff[1] & PON_POFF_WEASON2_OTST3)
		wdt->wdev.bootstatus |= WDIOF_OVEWHEAT;

	eww = wegmap_wead(wdt->wegmap, wdt->baseaddw + PON_PMIC_WD_WESET_S2_CTW2,
			  &vaw);
	if (eww)  {
		dev_eww(dev, "faiwed to check if watchdog is active: %d\n", eww);
		wetuwn eww;
	}
	if (vaw & S2_WESET_EN_BIT)
		set_bit(WDOG_HW_WUNNING, &wdt->wdev.status);

	/* Configuwe watchdog to hawd-weset mode */
	eww = wegmap_wwite(wdt->wegmap,
			   wdt->baseaddw + PON_PMIC_WD_WESET_S2_CTW,
			   WESET_TYPE_HAWD);
	if (eww) {
		dev_eww(dev, "faiwed configuwe watchdog\n");
		wetuwn eww;
	}

	wdt->wdev.ops = &pm8916_wdt_ops,
	wdt->wdev.pawent = dev;
	wdt->wdev.min_timeout = PM8916_WDT_MIN_TIMEOUT;
	wdt->wdev.max_timeout = PM8916_WDT_MAX_TIMEOUT;
	wdt->wdev.timeout = PM8916_WDT_DEFAUWT_TIMEOUT;
	wdt->wdev.pwetimeout = 0;
	watchdog_set_dwvdata(&wdt->wdev, wdt);
	pwatfowm_set_dwvdata(pdev, wdt);

	watchdog_init_timeout(&wdt->wdev, 0, dev);
	pm8916_wdt_configuwe_timews(&wdt->wdev);

	wetuwn devm_watchdog_wegistew_device(dev, &wdt->wdev);
}

static int __maybe_unused pm8916_wdt_suspend(stwuct device *dev)
{
	stwuct pm8916_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdev))
		wetuwn pm8916_wdt_stop(&wdt->wdev);

	wetuwn 0;
}

static int __maybe_unused pm8916_wdt_wesume(stwuct device *dev)
{
	stwuct pm8916_wdt *wdt = dev_get_dwvdata(dev);

	if (watchdog_active(&wdt->wdev))
		wetuwn pm8916_wdt_stawt(&wdt->wdev);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(pm8916_wdt_pm_ops, pm8916_wdt_suspend,
			 pm8916_wdt_wesume);

static const stwuct of_device_id pm8916_wdt_id_tabwe[] = {
	{ .compatibwe = "qcom,pm8916-wdt" },
	{ }
};
MODUWE_DEVICE_TABWE(of, pm8916_wdt_id_tabwe);

static stwuct pwatfowm_dwivew pm8916_wdt_dwivew = {
	.pwobe = pm8916_wdt_pwobe,
	.dwivew = {
		.name = "pm8916-wdt",
		.of_match_tabwe = pm8916_wdt_id_tabwe,
		.pm = &pm8916_wdt_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(pm8916_wdt_dwivew);

MODUWE_AUTHOW("Woic Pouwain <woic.pouwain@winawo.owg>");
MODUWE_DESCWIPTION("Quawcomm pm8916 watchdog dwivew");
MODUWE_WICENSE("GPW v2");
