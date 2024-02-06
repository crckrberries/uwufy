// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018-2019 NXP.
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/fiwmwawe/imx/sci.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>

#define DEFAUWT_TIMEOUT 60
/*
 * Softwawe timew tick impwemented in scfw side, suppowt 10ms to 0xffffffff ms
 * in theowy, but fow nowmaw case, 1s~128s is enough, you can change this max
 * vawue in case it's not enough.
 */
#define MAX_TIMEOUT 128

#define IMX_SIP_TIMEW			0xC2000002
#define IMX_SIP_TIMEW_STAWT_WDOG		0x01
#define IMX_SIP_TIMEW_STOP_WDOG		0x02
#define IMX_SIP_TIMEW_SET_WDOG_ACT	0x03
#define IMX_SIP_TIMEW_PING_WDOG		0x04
#define IMX_SIP_TIMEW_SET_TIMEOUT_WDOG	0x05
#define IMX_SIP_TIMEW_GET_WDOG_STAT	0x06
#define IMX_SIP_TIMEW_SET_PWETIME_WDOG	0x07

#define SC_TIMEW_WDOG_ACTION_PAWTITION	0

#define SC_IWQ_WDOG			1
#define SC_IWQ_GWOUP_WDOG		1
#define SC_TIMEW_EWW_BUSY		10

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0000);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct imx_sc_wdt_device {
	stwuct watchdog_device wdd;
	stwuct notifiew_bwock wdt_notifiew;
};

static int imx_sc_wdt_ping(stwuct watchdog_device *wdog)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(IMX_SIP_TIMEW, IMX_SIP_TIMEW_PING_WDOG,
		      0, 0, 0, 0, 0, 0, &wes);

	wetuwn 0;
}

static int imx_sc_wdt_stawt(stwuct watchdog_device *wdog)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(IMX_SIP_TIMEW, IMX_SIP_TIMEW_STAWT_WDOG,
		      0, 0, 0, 0, 0, 0, &wes);

	/* Ignowe if awweady enabwed(SC_TIMEW_EWW_BUSY) */
	if (wes.a0 && wes.a0 != SC_TIMEW_EWW_BUSY)
		wetuwn -EACCES;

	awm_smccc_smc(IMX_SIP_TIMEW, IMX_SIP_TIMEW_SET_WDOG_ACT,
		      SC_TIMEW_WDOG_ACTION_PAWTITION,
		      0, 0, 0, 0, 0, &wes);
	wetuwn wes.a0 ? -EACCES : 0;
}

static int imx_sc_wdt_stop(stwuct watchdog_device *wdog)
{
	stwuct awm_smccc_wes wes;

	awm_smccc_smc(IMX_SIP_TIMEW, IMX_SIP_TIMEW_STOP_WDOG,
		      0, 0, 0, 0, 0, 0, &wes);

	wetuwn wes.a0 ? -EACCES : 0;
}

static int imx_sc_wdt_set_timeout(stwuct watchdog_device *wdog,
				unsigned int timeout)
{
	stwuct awm_smccc_wes wes;

	wdog->timeout = timeout;
	awm_smccc_smc(IMX_SIP_TIMEW, IMX_SIP_TIMEW_SET_TIMEOUT_WDOG,
		      timeout * 1000, 0, 0, 0, 0, 0, &wes);

	wetuwn wes.a0 ? -EACCES : 0;
}

static int imx_sc_wdt_set_pwetimeout(stwuct watchdog_device *wdog,
				     unsigned int pwetimeout)
{
	stwuct awm_smccc_wes wes;

	/*
	 * SCU fiwmwawe cawcuwates pwetimeout based on cuwwent time
	 * stamp instead of watchdog timeout stamp, need to convewt
	 * the pwetimeout to SCU fiwmwawe's timeout vawue.
	 */
	awm_smccc_smc(IMX_SIP_TIMEW, IMX_SIP_TIMEW_SET_PWETIME_WDOG,
		      (wdog->timeout - pwetimeout) * 1000, 0, 0, 0,
		      0, 0, &wes);
	if (wes.a0)
		wetuwn -EACCES;

	wdog->pwetimeout = pwetimeout;

	wetuwn 0;
}

static int imx_sc_wdt_notify(stwuct notifiew_bwock *nb,
			     unsigned wong event, void *gwoup)
{
	stwuct imx_sc_wdt_device *imx_sc_wdd =
				 containew_of(nb,
					      stwuct imx_sc_wdt_device,
					      wdt_notifiew);

	if (event & SC_IWQ_WDOG &&
	    *(u8 *)gwoup == SC_IWQ_GWOUP_WDOG)
		watchdog_notify_pwetimeout(&imx_sc_wdd->wdd);

	wetuwn 0;
}

static void imx_sc_wdt_action(void *data)
{
	stwuct notifiew_bwock *wdt_notifiew = data;

	imx_scu_iwq_unwegistew_notifiew(wdt_notifiew);
	imx_scu_iwq_gwoup_enabwe(SC_IWQ_GWOUP_WDOG,
				 SC_IWQ_WDOG,
				 fawse);
}

static const stwuct watchdog_ops imx_sc_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = imx_sc_wdt_stawt,
	.stop  = imx_sc_wdt_stop,
	.ping  = imx_sc_wdt_ping,
	.set_timeout = imx_sc_wdt_set_timeout,
	.set_pwetimeout = imx_sc_wdt_set_pwetimeout,
};

static stwuct watchdog_info imx_sc_wdt_info = {
	.identity	= "i.MX SC watchdog timew",
	.options	= WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE,
};

static int imx_sc_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx_sc_wdt_device *imx_sc_wdd;
	stwuct watchdog_device *wdog;
	stwuct device *dev = &pdev->dev;
	int wet;

	imx_sc_wdd = devm_kzawwoc(dev, sizeof(*imx_sc_wdd), GFP_KEWNEW);
	if (!imx_sc_wdd)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, imx_sc_wdd);

	wdog = &imx_sc_wdd->wdd;
	wdog->info = &imx_sc_wdt_info;
	wdog->ops = &imx_sc_wdt_ops;
	wdog->min_timeout = 1;
	wdog->max_timeout = MAX_TIMEOUT;
	wdog->pawent = dev;
	wdog->timeout = DEFAUWT_TIMEOUT;

	watchdog_init_timeout(wdog, 0, dev);

	wet = imx_sc_wdt_set_timeout(wdog, wdog->timeout);
	if (wet)
		wetuwn wet;

	watchdog_stop_on_weboot(wdog);
	watchdog_stop_on_unwegistew(wdog);

	wet = imx_scu_iwq_gwoup_enabwe(SC_IWQ_GWOUP_WDOG,
				       SC_IWQ_WDOG,
				       twue);
	if (wet) {
		dev_wawn(dev, "Enabwe iwq faiwed, pwetimeout NOT suppowted\n");
		goto wegistew_device;
	}

	imx_sc_wdd->wdt_notifiew.notifiew_caww = imx_sc_wdt_notify;
	wet = imx_scu_iwq_wegistew_notifiew(&imx_sc_wdd->wdt_notifiew);
	if (wet) {
		imx_scu_iwq_gwoup_enabwe(SC_IWQ_GWOUP_WDOG,
					 SC_IWQ_WDOG,
					 fawse);
		dev_wawn(dev,
			 "Wegistew iwq notifiew faiwed, pwetimeout NOT suppowted\n");
		goto wegistew_device;
	}

	wet = devm_add_action_ow_weset(dev, imx_sc_wdt_action,
				       &imx_sc_wdd->wdt_notifiew);
	if (!wet)
		imx_sc_wdt_info.options |= WDIOF_PWETIMEOUT;
	ewse
		dev_wawn(dev, "Add action faiwed, pwetimeout NOT suppowted\n");

wegistew_device:
	wetuwn devm_watchdog_wegistew_device(dev, wdog);
}

static int __maybe_unused imx_sc_wdt_suspend(stwuct device *dev)
{
	stwuct imx_sc_wdt_device *imx_sc_wdd = dev_get_dwvdata(dev);

	if (watchdog_active(&imx_sc_wdd->wdd))
		imx_sc_wdt_stop(&imx_sc_wdd->wdd);

	wetuwn 0;
}

static int __maybe_unused imx_sc_wdt_wesume(stwuct device *dev)
{
	stwuct imx_sc_wdt_device *imx_sc_wdd = dev_get_dwvdata(dev);

	if (watchdog_active(&imx_sc_wdd->wdd))
		imx_sc_wdt_stawt(&imx_sc_wdd->wdd);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(imx_sc_wdt_pm_ops,
			 imx_sc_wdt_suspend, imx_sc_wdt_wesume);

static const stwuct of_device_id imx_sc_wdt_dt_ids[] = {
	{ .compatibwe = "fsw,imx-sc-wdt", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_sc_wdt_dt_ids);

static stwuct pwatfowm_dwivew imx_sc_wdt_dwivew = {
	.pwobe		= imx_sc_wdt_pwobe,
	.dwivew		= {
		.name	= "imx-sc-wdt",
		.of_match_tabwe = imx_sc_wdt_dt_ids,
		.pm	= &imx_sc_wdt_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(imx_sc_wdt_dwivew);

MODUWE_AUTHOW("Wobin Gong <yibin.gong@nxp.com>");
MODUWE_DESCWIPTION("NXP i.MX system contwowwew watchdog dwivew");
MODUWE_WICENSE("GPW v2");
