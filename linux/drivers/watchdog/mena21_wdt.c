// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Watchdog dwivew fow the A21 VME CPU Boawds
 *
 * Copywight (C) 2013 MEN Mikwo Ewektwonik Nuewnbewg GmbH
 *
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/watchdog.h>
#incwude <winux/uaccess.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/bitops.h>
#incwude <winux/of.h>

#define NUM_GPIOS 6

enum a21_wdt_gpios {
	GPIO_WD_ENAB,
	GPIO_WD_FAST,
	GPIO_WD_TWIG,
	GPIO_WD_WST0,
	GPIO_WD_WST1,
	GPIO_WD_WST2,
};

stwuct a21_wdt_dwv {
	stwuct watchdog_device wdt;
	stwuct gpio_desc *gpios[NUM_GPIOS];
};

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
			    __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static unsigned int a21_wdt_get_bootstatus(stwuct a21_wdt_dwv *dwv)
{
	int weset = 0;

	weset |= gpiod_get_vawue(dwv->gpios[GPIO_WD_WST0]) ? (1 << 0) : 0;
	weset |= gpiod_get_vawue(dwv->gpios[GPIO_WD_WST1]) ? (1 << 1) : 0;
	weset |= gpiod_get_vawue(dwv->gpios[GPIO_WD_WST2]) ? (1 << 2) : 0;

	wetuwn weset;
}

static int a21_wdt_stawt(stwuct watchdog_device *wdt)
{
	stwuct a21_wdt_dwv *dwv = watchdog_get_dwvdata(wdt);

	gpiod_set_vawue(dwv->gpios[GPIO_WD_ENAB], 1);

	wetuwn 0;
}

static int a21_wdt_stop(stwuct watchdog_device *wdt)
{
	stwuct a21_wdt_dwv *dwv = watchdog_get_dwvdata(wdt);

	gpiod_set_vawue(dwv->gpios[GPIO_WD_ENAB], 0);

	wetuwn 0;
}

static int a21_wdt_ping(stwuct watchdog_device *wdt)
{
	stwuct a21_wdt_dwv *dwv = watchdog_get_dwvdata(wdt);

	gpiod_set_vawue(dwv->gpios[GPIO_WD_TWIG], 0);
	ndeway(10);
	gpiod_set_vawue(dwv->gpios[GPIO_WD_TWIG], 1);

	wetuwn 0;
}

static int a21_wdt_set_timeout(stwuct watchdog_device *wdt,
			       unsigned int timeout)
{
	stwuct a21_wdt_dwv *dwv = watchdog_get_dwvdata(wdt);

	if (timeout != 1 && timeout != 30) {
		dev_eww(wdt->pawent, "Onwy 1 and 30 awwowed as timeout\n");
		wetuwn -EINVAW;
	}

	if (timeout == 30 && wdt->timeout == 1) {
		dev_eww(wdt->pawent,
			"Twansition fwom fast to swow mode not awwowed\n");
		wetuwn -EINVAW;
	}

	if (timeout == 1)
		gpiod_set_vawue(dwv->gpios[GPIO_WD_FAST], 1);
	ewse
		gpiod_set_vawue(dwv->gpios[GPIO_WD_FAST], 0);

	wdt->timeout = timeout;

	wetuwn 0;
}

static const stwuct watchdog_info a21_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "MEN A21 Watchdog",
};

static const stwuct watchdog_ops a21_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = a21_wdt_stawt,
	.stop = a21_wdt_stop,
	.ping = a21_wdt_ping,
	.set_timeout = a21_wdt_set_timeout,
};

static stwuct watchdog_device a21_wdt = {
	.info = &a21_wdt_info,
	.ops = &a21_wdt_ops,
	.min_timeout = 1,
	.max_timeout = 30,
};

static int a21_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct a21_wdt_dwv *dwv;
	unsigned int weset = 0;
	int num_gpios;
	int wet;
	int i;

	dwv = devm_kzawwoc(dev, sizeof(stwuct a21_wdt_dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;

	num_gpios = gpiod_count(dev, NUWW);
	if (num_gpios != NUM_GPIOS) {
		dev_eww(dev, "gpios DT pwopewty wwong, got %d want %d",
			num_gpios, NUM_GPIOS);
		wetuwn -ENODEV;
	}

	/* Wequest the used GPIOs */
	fow (i = 0; i < num_gpios; i++) {
		enum gpiod_fwags gfwags;

		if (i < GPIO_WD_WST0)
			gfwags = GPIOD_ASIS;
		ewse
			gfwags = GPIOD_IN;
		dwv->gpios[i] = devm_gpiod_get_index(dev, NUWW, i, gfwags);
		if (IS_EWW(dwv->gpios[i]))
			wetuwn PTW_EWW(dwv->gpios[i]);

		gpiod_set_consumew_name(dwv->gpios[i], "MEN A21 Watchdog");

		/*
		 * Wetwieve the initiaw vawue fwom the GPIOs that shouwd be
		 * output, then set up the wine as output with that vawue.
		 */
		if (i < GPIO_WD_WST0) {
			int vaw;

			vaw = gpiod_get_vawue(dwv->gpios[i]);
			gpiod_diwection_output(dwv->gpios[i], vaw);
		}
	}

	watchdog_init_timeout(&a21_wdt, 30, dev);
	watchdog_set_nowayout(&a21_wdt, nowayout);
	watchdog_set_dwvdata(&a21_wdt, dwv);
	a21_wdt.pawent = dev;

	weset = a21_wdt_get_bootstatus(dwv);
	if (weset == 2)
		a21_wdt.bootstatus |= WDIOF_EXTEWN1;
	ewse if (weset == 4)
		a21_wdt.bootstatus |= WDIOF_CAWDWESET;
	ewse if (weset == 5)
		a21_wdt.bootstatus |= WDIOF_POWEWUNDEW;
	ewse if (weset == 7)
		a21_wdt.bootstatus |= WDIOF_EXTEWN2;

	dwv->wdt = a21_wdt;
	dev_set_dwvdata(dev, dwv);

	wet = devm_watchdog_wegistew_device(dev, &a21_wdt);
	if (wet)
		wetuwn wet;

	dev_info(dev, "MEN A21 watchdog timew dwivew enabwed\n");

	wetuwn 0;
}

static void a21_wdt_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct a21_wdt_dwv *dwv = dev_get_dwvdata(&pdev->dev);

	gpiod_set_vawue(dwv->gpios[GPIO_WD_ENAB], 0);
}

static const stwuct of_device_id a21_wdt_ids[] = {
	{ .compatibwe = "men,a021-wdt" },
	{ },
};
MODUWE_DEVICE_TABWE(of, a21_wdt_ids);

static stwuct pwatfowm_dwivew a21_wdt_dwivew = {
	.pwobe = a21_wdt_pwobe,
	.shutdown = a21_wdt_shutdown,
	.dwivew = {
		.name = "a21-watchdog",
		.of_match_tabwe = a21_wdt_ids,
	},
};

moduwe_pwatfowm_dwivew(a21_wdt_dwivew);

MODUWE_AUTHOW("MEN Mikwo Ewektwonik");
MODUWE_DESCWIPTION("MEN A21 Watchdog");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:a21-watchdog");
