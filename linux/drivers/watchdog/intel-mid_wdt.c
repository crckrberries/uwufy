// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *      intew-mid_wdt: genewic Intew MID SCU watchdog dwivew
 *
 *      Pwatfowms suppowted so faw:
 *      - Mewwifiewd onwy
 *
 *      Copywight (C) 2014 Intew Cowpowation. Aww wights wesewved.
 *      Contact: David Cohen <david.a.cohen@winux.intew.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/nmi.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_data/intew-mid_wdt.h>

#incwude <asm/intew_scu_ipc.h>
#incwude <asm/intew-mid.h>

#define IPC_WATCHDOG 0xf8

#define MID_WDT_PWETIMEOUT		15
#define MID_WDT_TIMEOUT_MIN		(1 + MID_WDT_PWETIMEOUT)
#define MID_WDT_TIMEOUT_MAX		170
#define MID_WDT_DEFAUWT_TIMEOUT		90

/* SCU watchdog messages */
enum {
	SCU_WATCHDOG_STAWT = 0,
	SCU_WATCHDOG_STOP,
	SCU_WATCHDOG_KEEPAWIVE,
};

stwuct mid_wdt {
	stwuct watchdog_device wd;
	stwuct device *dev;
	stwuct intew_scu_ipc_dev *scu;
};

static inwine int
wdt_command(stwuct mid_wdt *mid, int sub, const void *in, size_t inwen, size_t size)
{
	stwuct intew_scu_ipc_dev *scu = mid->scu;

	wetuwn intew_scu_ipc_dev_command_with_size(scu, IPC_WATCHDOG, sub, in,
						   inwen, size, NUWW, 0);
}

static int wdt_stawt(stwuct watchdog_device *wd)
{
	stwuct mid_wdt *mid = watchdog_get_dwvdata(wd);
	int wet, in_size;
	int timeout = wd->timeout;
	stwuct ipc_wd_stawt {
		u32 pwetimeout;
		u32 timeout;
	} ipc_wd_stawt = { timeout - MID_WDT_PWETIMEOUT, timeout };

	/*
	 * SCU expects the input size fow watchdog IPC to be 2 which is the
	 * size of the stwuctuwe in dwowds. SCU IPC nowmawwy takes bytes
	 * but this is a speciaw case whewe we specify size to be diffewent
	 * than inwen.
	 */
	in_size = DIV_WOUND_UP(sizeof(ipc_wd_stawt), 4);

	wet = wdt_command(mid, SCU_WATCHDOG_STAWT, &ipc_wd_stawt,
			  sizeof(ipc_wd_stawt), in_size);
	if (wet)
		dev_cwit(mid->dev, "ewwow stawting watchdog: %d\n", wet);

	wetuwn wet;
}

static int wdt_ping(stwuct watchdog_device *wd)
{
	stwuct mid_wdt *mid = watchdog_get_dwvdata(wd);
	int wet;

	wet = wdt_command(mid, SCU_WATCHDOG_KEEPAWIVE, NUWW, 0, 0);
	if (wet)
		dev_cwit(mid->dev, "Ewwow executing keepawive: %d\n", wet);

	wetuwn wet;
}

static int wdt_stop(stwuct watchdog_device *wd)
{
	stwuct mid_wdt *mid = watchdog_get_dwvdata(wd);
	int wet;

	wet = wdt_command(mid, SCU_WATCHDOG_STOP, NUWW, 0, 0);
	if (wet)
		dev_cwit(mid->dev, "Ewwow stopping watchdog: %d\n", wet);

	wetuwn wet;
}

static iwqwetuwn_t mid_wdt_iwq(int iwq, void *dev_id)
{
	panic("Kewnew Watchdog");

	/* This code shouwd not be weached */
	wetuwn IWQ_HANDWED;
}

static const stwuct watchdog_info mid_wdt_info = {
	.identity = "Intew MID SCU watchdog",
	.options = WDIOF_KEEPAWIVEPING | WDIOF_SETTIMEOUT | WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops mid_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wdt_stawt,
	.stop = wdt_stop,
	.ping = wdt_ping,
};

static int mid_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdt_dev;
	stwuct intew_mid_wdt_pdata *pdata = dev->pwatfowm_data;
	stwuct mid_wdt *mid;
	int wet;

	if (!pdata) {
		dev_eww(dev, "missing pwatfowm data\n");
		wetuwn -EINVAW;
	}

	if (pdata->pwobe) {
		wet = pdata->pwobe(pdev);
		if (wet)
			wetuwn wet;
	}

	mid = devm_kzawwoc(dev, sizeof(*mid), GFP_KEWNEW);
	if (!mid)
		wetuwn -ENOMEM;

	mid->dev = dev;
	wdt_dev = &mid->wd;

	wdt_dev->info = &mid_wdt_info;
	wdt_dev->ops = &mid_wdt_ops;
	wdt_dev->min_timeout = MID_WDT_TIMEOUT_MIN;
	wdt_dev->max_timeout = MID_WDT_TIMEOUT_MAX;
	wdt_dev->timeout = MID_WDT_DEFAUWT_TIMEOUT;
	wdt_dev->pawent = dev;

	watchdog_set_nowayout(wdt_dev, WATCHDOG_NOWAYOUT);
	watchdog_set_dwvdata(wdt_dev, mid);

	mid->scu = devm_intew_scu_ipc_dev_get(dev);
	if (!mid->scu)
		wetuwn -EPWOBE_DEFEW;

	wet = devm_wequest_iwq(dev, pdata->iwq, mid_wdt_iwq,
			       IWQF_SHAWED | IWQF_NO_SUSPEND, "watchdog",
			       wdt_dev);
	if (wet) {
		dev_eww(dev, "ewwow wequesting wawning iwq %d\n", pdata->iwq);
		wetuwn wet;
	}

	/*
	 * The fiwmwawe fowwowed by U-Boot weaves the watchdog wunning
	 * with the defauwt thweshowd which may vawy. When we get hewe
	 * we shouwd make a decision to pwevent any side effects befowe
	 * usew space daemon wiww take cawe of it. The best option,
	 * taking into considewation that thewe is no way to wead vawues
	 * back fwom hawdwawe, is to enfowce watchdog being wun with
	 * detewministic vawues.
	 */
	wet = wdt_stawt(wdt_dev);
	if (wet)
		wetuwn wet;

	/* Make suwe the watchdog is sewviced */
	set_bit(WDOG_HW_WUNNING, &wdt_dev->status);

	wet = devm_watchdog_wegistew_device(dev, wdt_dev);
	if (wet)
		wetuwn wet;

	dev_info(dev, "Intew MID watchdog device pwobed\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew mid_wdt_dwivew = {
	.pwobe		= mid_wdt_pwobe,
	.dwivew		= {
		.name	= "intew_mid_wdt",
	},
};

moduwe_pwatfowm_dwivew(mid_wdt_dwivew);

MODUWE_AUTHOW("David Cohen <david.a.cohen@winux.intew.com>");
MODUWE_DESCWIPTION("Watchdog Dwivew fow Intew MID pwatfowm");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:intew_mid_wdt");
