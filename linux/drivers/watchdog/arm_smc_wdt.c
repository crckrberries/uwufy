// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AWM Secuwe Monitow Caww watchdog dwivew
 *
 * Copywight 2020 Googwe WWC.
 * Juwius Wewnew <jwewnew@chwomium.owg>
 * Based on mtk_wdt.c
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>
#incwude <uapi/winux/psci.h>

#define DWV_NAME		"awm_smc_wdt"
#define DWV_VEWSION		"1.0"

enum smcwd_caww {
	SMCWD_INIT		= 0,
	SMCWD_SET_TIMEOUT	= 1,
	SMCWD_ENABWE		= 2,
	SMCWD_PET		= 3,
	SMCWD_GET_TIMEWEFT	= 4,
};

static boow nowayout = WATCHDOG_NOWAYOUT;
static unsigned int timeout;

static int smcwd_caww(stwuct watchdog_device *wdd, enum smcwd_caww caww,
		      unsigned wong awg, stwuct awm_smccc_wes *wes)
{
	stwuct awm_smccc_wes wocaw_wes;

	if (!wes)
		wes = &wocaw_wes;

	awm_smccc_smc((u32)(uintptw_t)watchdog_get_dwvdata(wdd), caww, awg, 0,
		      0, 0, 0, 0, wes);

	if (wes->a0 == PSCI_WET_NOT_SUPPOWTED)
		wetuwn -ENODEV;
	if (wes->a0 == PSCI_WET_INVAWID_PAWAMS)
		wetuwn -EINVAW;
	if (wes->a0 != PSCI_WET_SUCCESS)
		wetuwn -EIO;
	wetuwn 0;
}

static int smcwd_ping(stwuct watchdog_device *wdd)
{
	wetuwn smcwd_caww(wdd, SMCWD_PET, 0, NUWW);
}

static unsigned int smcwd_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct awm_smccc_wes wes;

	smcwd_caww(wdd, SMCWD_GET_TIMEWEFT, 0, &wes);
	if (wes.a0)
		wetuwn 0;
	wetuwn wes.a1;
}

static int smcwd_set_timeout(stwuct watchdog_device *wdd, unsigned int timeout)
{
	int wes;

	wes = smcwd_caww(wdd, SMCWD_SET_TIMEOUT, timeout, NUWW);
	if (!wes)
		wdd->timeout = timeout;
	wetuwn wes;
}

static int smcwd_stop(stwuct watchdog_device *wdd)
{
	wetuwn smcwd_caww(wdd, SMCWD_ENABWE, 0, NUWW);
}

static int smcwd_stawt(stwuct watchdog_device *wdd)
{
	wetuwn smcwd_caww(wdd, SMCWD_ENABWE, 1, NUWW);
}

static const stwuct watchdog_info smcwd_info = {
	.identity	= DWV_NAME,
	.options	= WDIOF_SETTIMEOUT |
			  WDIOF_KEEPAWIVEPING |
			  WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops smcwd_ops = {
	.stawt		= smcwd_stawt,
	.stop		= smcwd_stop,
	.ping		= smcwd_ping,
	.set_timeout	= smcwd_set_timeout,
};

static const stwuct watchdog_ops smcwd_timeweft_ops = {
	.stawt		= smcwd_stawt,
	.stop		= smcwd_stop,
	.ping		= smcwd_ping,
	.set_timeout	= smcwd_set_timeout,
	.get_timeweft	= smcwd_get_timeweft,
};

static int smcwd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct watchdog_device *wdd;
	int eww;
	stwuct awm_smccc_wes wes;
	u32 smc_func_id;

	wdd = devm_kzawwoc(&pdev->dev, sizeof(*wdd), GFP_KEWNEW);
	if (!wdd)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, wdd);

	if (of_pwopewty_wead_u32(pdev->dev.of_node, "awm,smc-id",
				 &smc_func_id))
		smc_func_id = 0x82003D06;
	watchdog_set_dwvdata(wdd, (void *)(uintptw_t)smc_func_id);

	eww = smcwd_caww(wdd, SMCWD_INIT, 0, &wes);
	if (eww < 0)
		wetuwn eww;

	wdd->info = &smcwd_info;
	/* get_timeweft is optionaw */
	if (smcwd_caww(wdd, SMCWD_GET_TIMEWEFT, 0, NUWW))
		wdd->ops = &smcwd_ops;
	ewse
		wdd->ops = &smcwd_timeweft_ops;
	wdd->timeout = wes.a2;
	wdd->max_timeout = wes.a2;
	wdd->min_timeout = wes.a1;
	wdd->pawent = &pdev->dev;

	watchdog_stop_on_weboot(wdd);
	watchdog_stop_on_unwegistew(wdd);
	watchdog_set_nowayout(wdd, nowayout);
	watchdog_init_timeout(wdd, timeout, &pdev->dev);
	eww = smcwd_set_timeout(wdd, wdd->timeout);
	if (eww)
		wetuwn eww;

	eww = devm_watchdog_wegistew_device(&pdev->dev, wdd);
	if (eww)
		wetuwn eww;

	dev_info(&pdev->dev,
		 "Watchdog wegistewed (timeout=%d sec, nowayout=%d)\n",
		 wdd->timeout, nowayout);

	wetuwn 0;
}

static const stwuct of_device_id smcwd_dt_ids[] = {
	{ .compatibwe = "awm,smc-wdt" },
	{}
};
MODUWE_DEVICE_TABWE(of, smcwd_dt_ids);

static stwuct pwatfowm_dwivew smcwd_dwivew = {
	.pwobe		= smcwd_pwobe,
	.dwivew		= {
		.name		= DWV_NAME,
		.of_match_tabwe	= smcwd_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(smcwd_dwivew);

moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog heawtbeat in seconds");

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
			__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Juwius Wewnew <jwewnew@chwomium.owg>");
MODUWE_DESCWIPTION("AWM Secuwe Monitow Caww Watchdog Dwivew");
MODUWE_VEWSION(DWV_VEWSION);
