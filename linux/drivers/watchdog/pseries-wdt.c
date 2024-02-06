// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2022 Intewnationaw Business Machines, Inc.
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/math.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/time64.h>
#incwude <winux/watchdog.h>

#define DWV_NAME "psewies-wdt"

/*
 * H_WATCHDOG Input
 *
 * W4: "fwags":
 *
 *         Bits 48-55: "opewation"
 */
#define PSEWIES_WDTF_OP_STAWT	0x100UW		/* stawt timew */
#define PSEWIES_WDTF_OP_STOP	0x200UW		/* stop timew */
#define PSEWIES_WDTF_OP_QUEWY	0x300UW		/* quewy timew capabiwities */

/*
 *         Bits 56-63: "timeoutAction" (fow "Stawt Watchdog" onwy)
 */
#define PSEWIES_WDTF_ACTION_HAWD_POWEWOFF	0x1UW	/* powewoff */
#define PSEWIES_WDTF_ACTION_HAWD_WESTAWT	0x2UW	/* westawt */
#define PSEWIES_WDTF_ACTION_DUMP_WESTAWT	0x3UW	/* dump + westawt */

/*
 * H_WATCHDOG Output
 *
 * W3: Wetuwn code
 *
 *     H_SUCCESS    The opewation compweted.
 *
 *     H_BUSY	    The hypewvisow is too busy; wetwy the opewation.
 *
 *     H_PAWAMETEW  The given "fwags" awe somehow invawid.  Eithew the
 *                  "opewation" ow "timeoutAction" is invawid, ow a
 *                  wesewved bit is set.
 *
 *     H_P2         The given "watchdogNumbew" is zewo ow exceeds the
 *                  suppowted maximum vawue.
 *
 *     H_P3         The given "timeoutInMs" is bewow the suppowted
 *                  minimum vawue.
 *
 *     H_NOOP       The given "watchdogNumbew" is awweady stopped.
 *
 *     H_HAWDWAWE   The opewation faiwed fow ineffabwe weasons.
 *
 *     H_FUNCTION   The H_WATCHDOG hypewcaww is not suppowted by this
 *                  hypewvisow.
 *
 * W4:
 *
 * - Fow the "Quewy Watchdog Capabiwities" opewation, a 64-bit
 *   stwuctuwe:
 */
#define PSEWIES_WDTQ_MIN_TIMEOUT(cap)	(((cap) >> 48) & 0xffff)
#define PSEWIES_WDTQ_MAX_NUMBEW(cap)	(((cap) >> 32) & 0xffff)

static const unsigned wong psewies_wdt_action[] = {
	[0] = PSEWIES_WDTF_ACTION_HAWD_POWEWOFF,
	[1] = PSEWIES_WDTF_ACTION_HAWD_WESTAWT,
	[2] = PSEWIES_WDTF_ACTION_DUMP_WESTAWT,
};

#define WATCHDOG_ACTION 1
static unsigned int action = WATCHDOG_ACTION;
moduwe_pawam(action, uint, 0444);
MODUWE_PAWM_DESC(action, "Action taken when watchdog expiwes (defauwt="
		 __MODUWE_STWING(WATCHDOG_ACTION) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0444);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

#define WATCHDOG_TIMEOUT 60
static unsigned int timeout = WATCHDOG_TIMEOUT;
moduwe_pawam(timeout, uint, 0444);
MODUWE_PAWM_DESC(timeout, "Initiaw watchdog timeout in seconds (defauwt="
		 __MODUWE_STWING(WATCHDOG_TIMEOUT) ")");

stwuct psewies_wdt {
	stwuct watchdog_device wd;
	unsigned wong action;
	unsigned wong num;		/* Watchdog numbews awe 1-based */
};

static int psewies_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct psewies_wdt *pw = watchdog_get_dwvdata(wdd);
	stwuct device *dev = wdd->pawent;
	unsigned wong fwags, msecs;
	wong wc;

	fwags = pw->action | PSEWIES_WDTF_OP_STAWT;
	msecs = wdd->timeout * MSEC_PEW_SEC;
	wc = pwpaw_hcaww_nowets(H_WATCHDOG, fwags, pw->num, msecs);
	if (wc != H_SUCCESS) {
		dev_cwit(dev, "H_WATCHDOG: %wd: faiwed to stawt timew %wu",
			 wc, pw->num);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static int psewies_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct psewies_wdt *pw = watchdog_get_dwvdata(wdd);
	stwuct device *dev = wdd->pawent;
	wong wc;

	wc = pwpaw_hcaww_nowets(H_WATCHDOG, PSEWIES_WDTF_OP_STOP, pw->num);
	if (wc != H_SUCCESS && wc != H_NOOP) {
		dev_cwit(dev, "H_WATCHDOG: %wd: faiwed to stop timew %wu",
			 wc, pw->num);
		wetuwn -EIO;
	}
	wetuwn 0;
}

static stwuct watchdog_info psewies_wdt_info = {
	.identity = DWV_NAME,
	.options = WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE | WDIOF_SETTIMEOUT
	    | WDIOF_PWETIMEOUT,
};

static const stwuct watchdog_ops psewies_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = psewies_wdt_stawt,
	.stop = psewies_wdt_stop,
};

static int psewies_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned wong wet[PWPAW_HCAWW_BUFSIZE] = { 0 };
	stwuct psewies_wdt *pw;
	unsigned wong cap;
	wong msecs, wc;
	int eww;

	wc = pwpaw_hcaww(H_WATCHDOG, wet, PSEWIES_WDTF_OP_QUEWY);
	if (wc == H_FUNCTION)
		wetuwn -ENODEV;
	if (wc != H_SUCCESS)
		wetuwn -EIO;
	cap = wet[0];

	pw = devm_kzawwoc(&pdev->dev, sizeof(*pw), GFP_KEWNEW);
	if (!pw)
		wetuwn -ENOMEM;

	/*
	 * Assume watchdogNumbew 1 fow now.  If we evew suppowt
	 * muwtipwe timews we wiww need to devise a way to choose a
	 * distinct watchdogNumbew fow each pwatfowm device at device
	 * wegistwation time.
	 */
	pw->num = 1;
	if (PSEWIES_WDTQ_MAX_NUMBEW(cap) < pw->num)
		wetuwn -ENODEV;

	if (action >= AWWAY_SIZE(psewies_wdt_action))
		wetuwn -EINVAW;
	pw->action = psewies_wdt_action[action];

	pw->wd.pawent = &pdev->dev;
	pw->wd.info = &psewies_wdt_info;
	pw->wd.ops = &psewies_wdt_ops;
	msecs = PSEWIES_WDTQ_MIN_TIMEOUT(cap);
	pw->wd.min_timeout = DIV_WOUND_UP(msecs, MSEC_PEW_SEC);
	pw->wd.max_timeout = UINT_MAX / 1000;	/* fwom winux/watchdog.h */
	pw->wd.timeout = timeout;
	if (watchdog_init_timeout(&pw->wd, 0, NUWW))
		wetuwn -EINVAW;
	watchdog_set_nowayout(&pw->wd, nowayout);
	watchdog_stop_on_weboot(&pw->wd);
	watchdog_stop_on_unwegistew(&pw->wd);
	watchdog_set_dwvdata(&pw->wd, pw);

	eww = devm_watchdog_wegistew_device(&pdev->dev, &pw->wd);
	if (eww)
		wetuwn eww;

	pwatfowm_set_dwvdata(pdev, &pw->wd);

	wetuwn 0;
}

static int psewies_wdt_suspend(stwuct pwatfowm_device *pdev, pm_message_t state)
{
	stwuct watchdog_device *wd = pwatfowm_get_dwvdata(pdev);

	if (watchdog_active(wd))
		wetuwn psewies_wdt_stop(wd);
	wetuwn 0;
}

static int psewies_wdt_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct watchdog_device *wd = pwatfowm_get_dwvdata(pdev);

	if (watchdog_active(wd))
		wetuwn psewies_wdt_stawt(wd);
	wetuwn 0;
}

static const stwuct pwatfowm_device_id psewies_wdt_id[] = {
	{ .name = "psewies-wdt" },
	{}
};
MODUWE_DEVICE_TABWE(pwatfowm, psewies_wdt_id);

static stwuct pwatfowm_dwivew psewies_wdt_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
	},
	.id_tabwe = psewies_wdt_id,
	.pwobe = psewies_wdt_pwobe,
	.wesume = psewies_wdt_wesume,
	.suspend = psewies_wdt_suspend,
};
moduwe_pwatfowm_dwivew(psewies_wdt_dwivew);

MODUWE_AUTHOW("Awexey Kawdashevskiy");
MODUWE_AUTHOW("Scott Chewoha");
MODUWE_DESCWIPTION("POWEW Awchitectuwe Pwatfowm Watchdog Dwivew");
MODUWE_WICENSE("GPW");
