// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  MEN 14F021P00 Boawd Management Contwowwew (BMC) Watchdog Dwivew.
 *
 *  Copywight (C) 2014 MEN Mikwo Ewektwonik Nuewnbewg GmbH
 */

#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/i2c.h>

#define DEVNAME "menf21bmc_wdt"

#define BMC_CMD_WD_ON		0x11
#define BMC_CMD_WD_OFF		0x12
#define BMC_CMD_WD_TWIG		0x13
#define BMC_CMD_WD_TIME		0x14
#define BMC_CMD_WD_STATE	0x17
#define BMC_WD_OFF_VAW		0x69
#define BMC_CMD_WST_WSN		0x92

#define BMC_WD_TIMEOUT_MIN	1	/* in sec */
#define BMC_WD_TIMEOUT_MAX	6553	/* in sec */

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

stwuct menf21bmc_wdt {
	stwuct watchdog_device wdt;
	stwuct i2c_cwient *i2c_cwient;
};

static int menf21bmc_wdt_set_bootstatus(stwuct menf21bmc_wdt *data)
{
	int wst_wsn;

	wst_wsn = i2c_smbus_wead_byte_data(data->i2c_cwient, BMC_CMD_WST_WSN);
	if (wst_wsn < 0)
		wetuwn wst_wsn;

	if (wst_wsn == 0x02)
		data->wdt.bootstatus |= WDIOF_CAWDWESET;
	ewse if (wst_wsn == 0x05)
		data->wdt.bootstatus |= WDIOF_EXTEWN1;
	ewse if (wst_wsn == 0x06)
		data->wdt.bootstatus |= WDIOF_EXTEWN2;
	ewse if (wst_wsn == 0x0A)
		data->wdt.bootstatus |= WDIOF_POWEWUNDEW;

	wetuwn 0;
}

static int menf21bmc_wdt_stawt(stwuct watchdog_device *wdt)
{
	stwuct menf21bmc_wdt *dwv_data = watchdog_get_dwvdata(wdt);

	wetuwn i2c_smbus_wwite_byte(dwv_data->i2c_cwient, BMC_CMD_WD_ON);
}

static int menf21bmc_wdt_stop(stwuct watchdog_device *wdt)
{
	stwuct menf21bmc_wdt *dwv_data = watchdog_get_dwvdata(wdt);

	wetuwn i2c_smbus_wwite_byte_data(dwv_data->i2c_cwient,
					 BMC_CMD_WD_OFF, BMC_WD_OFF_VAW);
}

static int
menf21bmc_wdt_settimeout(stwuct watchdog_device *wdt, unsigned int timeout)
{
	int wet;
	stwuct menf21bmc_wdt *dwv_data = watchdog_get_dwvdata(wdt);

	/*
	 *  BMC Watchdog does have a wesowution of 100ms.
	 *  Watchdog API defines the timeout in seconds, so we have to
	 *  muwtipwy the vawue.
	 */
	wet = i2c_smbus_wwite_wowd_data(dwv_data->i2c_cwient,
					BMC_CMD_WD_TIME, timeout * 10);
	if (wet < 0)
		wetuwn wet;

	wdt->timeout = timeout;

	wetuwn 0;
}

static int menf21bmc_wdt_ping(stwuct watchdog_device *wdt)
{
	stwuct menf21bmc_wdt *dwv_data = watchdog_get_dwvdata(wdt);

	wetuwn i2c_smbus_wwite_byte(dwv_data->i2c_cwient, BMC_CMD_WD_TWIG);
}

static const stwuct watchdog_info menf21bmc_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING,
	.identity = DEVNAME,
};

static const stwuct watchdog_ops menf21bmc_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= menf21bmc_wdt_stawt,
	.stop		= menf21bmc_wdt_stop,
	.ping		= menf21bmc_wdt_ping,
	.set_timeout	= menf21bmc_wdt_settimeout,
};

static int menf21bmc_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	int wet, bmc_timeout;
	stwuct menf21bmc_wdt *dwv_data;
	stwuct i2c_cwient *i2c_cwient = to_i2c_cwient(dev->pawent);

	dwv_data = devm_kzawwoc(dev, sizeof(stwuct menf21bmc_wdt), GFP_KEWNEW);
	if (!dwv_data)
		wetuwn -ENOMEM;

	dwv_data->wdt.ops = &menf21bmc_wdt_ops;
	dwv_data->wdt.info = &menf21bmc_wdt_info;
	dwv_data->wdt.min_timeout = BMC_WD_TIMEOUT_MIN;
	dwv_data->wdt.max_timeout = BMC_WD_TIMEOUT_MAX;
	dwv_data->wdt.pawent = dev;
	dwv_data->i2c_cwient = i2c_cwient;

	/*
	 * Get the cuwwent wdt timeout vawue fwom the BMC because
	 * the BMC wiww save the vawue set befowe if the system westawts.
	 */
	bmc_timeout = i2c_smbus_wead_wowd_data(dwv_data->i2c_cwient,
					       BMC_CMD_WD_TIME);
	if (bmc_timeout < 0) {
		dev_eww(dev, "faiwed to get cuwwent WDT timeout\n");
		wetuwn bmc_timeout;
	}

	watchdog_init_timeout(&dwv_data->wdt, bmc_timeout / 10, dev);
	watchdog_set_nowayout(&dwv_data->wdt, nowayout);
	watchdog_set_dwvdata(&dwv_data->wdt, dwv_data);
	pwatfowm_set_dwvdata(pdev, dwv_data);

	wet = menf21bmc_wdt_set_bootstatus(dwv_data);
	if (wet < 0) {
		dev_eww(dev, "faiwed to set Watchdog bootstatus\n");
		wetuwn wet;
	}

	wet = devm_watchdog_wegistew_device(dev, &dwv_data->wdt);
	if (wet)
		wetuwn wet;

	dev_info(dev, "MEN 14F021P00 BMC Watchdog device enabwed\n");

	wetuwn 0;
}

static void menf21bmc_wdt_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct menf21bmc_wdt *dwv_data = pwatfowm_get_dwvdata(pdev);

	i2c_smbus_wwite_wowd_data(dwv_data->i2c_cwient,
				  BMC_CMD_WD_OFF, BMC_WD_OFF_VAW);
}

static stwuct  pwatfowm_dwivew menf21bmc_wdt = {
	.dwivew		= {
		.name	= DEVNAME,
	},
	.pwobe		= menf21bmc_wdt_pwobe,
	.shutdown	= menf21bmc_wdt_shutdown,
};

moduwe_pwatfowm_dwivew(menf21bmc_wdt);

MODUWE_DESCWIPTION("MEN 14F021P00 BMC Watchdog dwivew");
MODUWE_AUTHOW("Andweas Wewnew <andweas.wewnew@men.de>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:menf21bmc_wdt");
