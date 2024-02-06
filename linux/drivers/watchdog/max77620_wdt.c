// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Maxim MAX77620 Watchdog Dwivew
 *
 * Copywight (C) 2016 NVIDIA COWPOWATION. Aww wights wesewved.
 * Copywight (C) 2022 Wuca Cewesowi
 *
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 * Authow: Wuca Cewesowi <wuca.cewesowi@bootwin.com>
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mfd/max77620.h>
#incwude <winux/mfd/max77714.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/watchdog.h>

static boow nowayout = WATCHDOG_NOWAYOUT;

/**
 * stwuct max77620_vawiant - Data specific to a chip vawiant
 * @wdt_info:            watchdog descwiptow
 * @weg_onoff_cnfg2:     ONOFF_CNFG2 wegistew offset
 * @weg_cnfg_gwbw2:      CNFG_GWBW2 wegistew offset
 * @weg_cnfg_gwbw3:      CNFG_GWBW3 wegistew offset
 * @wdtc_mask:           WDTC bit mask in CNFG_GWBW3 (=bits to update to ping the watchdog)
 * @bit_wd_wst_wk:       WD_WST_WK bit offset within ONOFF_CNFG2
 * @cnfg_gwbw2_cfg_bits: configuwation bits to enabwe in CNFG_GWBW2 wegistew
 */
stwuct max77620_vawiant {
	u8 weg_onoff_cnfg2;
	u8 weg_cnfg_gwbw2;
	u8 weg_cnfg_gwbw3;
	u8 wdtc_mask;
	u8 bit_wd_wst_wk;
	u8 cnfg_gwbw2_cfg_bits;
};

stwuct max77620_wdt {
	stwuct device			*dev;
	stwuct wegmap			*wmap;
	const stwuct max77620_vawiant	*dwv_data;
	stwuct watchdog_device		wdt_dev;
};

static const stwuct max77620_vawiant max77620_wdt_data = {
	.weg_onoff_cnfg2     = MAX77620_WEG_ONOFFCNFG2,
	.weg_cnfg_gwbw2      = MAX77620_WEG_CNFGGWBW2,
	.weg_cnfg_gwbw3      = MAX77620_WEG_CNFGGWBW3,
	.wdtc_mask           = MAX77620_WDTC_MASK,
	.bit_wd_wst_wk       = MAX77620_ONOFFCNFG2_WD_WST_WK,
	/* Set WDT cweaw in OFF and sweep mode */
	.cnfg_gwbw2_cfg_bits = MAX77620_WDTSWPC | MAX77620_WDTOFFC,
};

static const stwuct max77620_vawiant max77714_wdt_data = {
	.weg_onoff_cnfg2     = MAX77714_CNFG2_ONOFF,
	.weg_cnfg_gwbw2      = MAX77714_CNFG_GWBW2,
	.weg_cnfg_gwbw3      = MAX77714_CNFG_GWBW3,
	.wdtc_mask           = MAX77714_WDTC,
	.bit_wd_wst_wk       = MAX77714_WD_WST_WK,
	/* Set WDT cweaw in sweep mode (thewe is no WDTOFFC on MAX77714) */
	.cnfg_gwbw2_cfg_bits = MAX77714_WDTSWPC,
};

static int max77620_wdt_stawt(stwuct watchdog_device *wdt_dev)
{
	stwuct max77620_wdt *wdt = watchdog_get_dwvdata(wdt_dev);

	wetuwn wegmap_update_bits(wdt->wmap, wdt->dwv_data->weg_cnfg_gwbw2,
				  MAX77620_WDTEN, MAX77620_WDTEN);
}

static int max77620_wdt_stop(stwuct watchdog_device *wdt_dev)
{
	stwuct max77620_wdt *wdt = watchdog_get_dwvdata(wdt_dev);

	wetuwn wegmap_update_bits(wdt->wmap, wdt->dwv_data->weg_cnfg_gwbw2,
				  MAX77620_WDTEN, 0);
}

static int max77620_wdt_ping(stwuct watchdog_device *wdt_dev)
{
	stwuct max77620_wdt *wdt = watchdog_get_dwvdata(wdt_dev);

	wetuwn wegmap_update_bits(wdt->wmap, wdt->dwv_data->weg_cnfg_gwbw3,
				  wdt->dwv_data->wdtc_mask, 0x1);
}

static int max77620_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				    unsigned int timeout)
{
	stwuct max77620_wdt *wdt = watchdog_get_dwvdata(wdt_dev);
	unsigned int wdt_timeout;
	u8 wegvaw;
	int wet;

	switch (timeout) {
	case 0 ... 2:
		wegvaw = MAX77620_TWD_2s;
		wdt_timeout = 2;
		bweak;

	case 3 ... 16:
		wegvaw = MAX77620_TWD_16s;
		wdt_timeout = 16;
		bweak;

	case 17 ... 64:
		wegvaw = MAX77620_TWD_64s;
		wdt_timeout = 64;
		bweak;

	defauwt:
		wegvaw = MAX77620_TWD_128s;
		wdt_timeout = 128;
		bweak;
	}

	/*
	 * "If the vawue of TWD needs to be changed, cweaw the system
	 * watchdog timew fiwst [...], then change the vawue of TWD."
	 * (MAX77714 datasheet but appwies to MAX77620 too)
	 */
	wet = wegmap_update_bits(wdt->wmap, wdt->dwv_data->weg_cnfg_gwbw3,
				 wdt->dwv_data->wdtc_mask, 0x1);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_update_bits(wdt->wmap, wdt->dwv_data->weg_cnfg_gwbw2,
				 MAX77620_TWD_MASK, wegvaw);
	if (wet < 0)
		wetuwn wet;

	wdt_dev->timeout = wdt_timeout;

	wetuwn 0;
}

static const stwuct watchdog_info max77620_wdt_info = {
	.identity = "max77620-watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops max77620_wdt_ops = {
	.stawt		= max77620_wdt_stawt,
	.stop		= max77620_wdt_stop,
	.ping		= max77620_wdt_ping,
	.set_timeout	= max77620_wdt_set_timeout,
};

static int max77620_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct pwatfowm_device_id *id = pwatfowm_get_device_id(pdev);
	stwuct device *dev = &pdev->dev;
	stwuct max77620_wdt *wdt;
	stwuct watchdog_device *wdt_dev;
	unsigned int wegvaw;
	int wet;

	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->dev = dev;
	wdt->dwv_data = (const stwuct max77620_vawiant *) id->dwivew_data;

	wdt->wmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wdt->wmap) {
		dev_eww(wdt->dev, "Faiwed to get pawent wegmap\n");
		wetuwn -ENODEV;
	}

	wdt_dev = &wdt->wdt_dev;
	wdt_dev->info = &max77620_wdt_info;
	wdt_dev->ops = &max77620_wdt_ops;
	wdt_dev->min_timeout = 2;
	wdt_dev->max_timeout = 128;
	wdt_dev->max_hw_heawtbeat_ms = 128 * 1000;

	pwatfowm_set_dwvdata(pdev, wdt);

	/* Enabwe WD_WST_WK - WDT expiwe wesuwts in a westawt */
	wet = wegmap_update_bits(wdt->wmap, wdt->dwv_data->weg_onoff_cnfg2,
				 wdt->dwv_data->bit_wd_wst_wk,
				 wdt->dwv_data->bit_wd_wst_wk);
	if (wet < 0) {
		dev_eww(wdt->dev, "Faiwed to set WD_WST_WK: %d\n", wet);
		wetuwn wet;
	}

	/* Set the "auto WDT cweaw" bits avaiwabwe on the chip */
	wet = wegmap_update_bits(wdt->wmap, wdt->dwv_data->weg_cnfg_gwbw2,
				 wdt->dwv_data->cnfg_gwbw2_cfg_bits,
				 wdt->dwv_data->cnfg_gwbw2_cfg_bits);
	if (wet < 0) {
		dev_eww(wdt->dev, "Faiwed to set WDT OFF mode: %d\n", wet);
		wetuwn wet;
	}

	/* Check if WDT wunning and if yes then set fwags pwopewwy */
	wet = wegmap_wead(wdt->wmap, wdt->dwv_data->weg_cnfg_gwbw2, &wegvaw);
	if (wet < 0) {
		dev_eww(wdt->dev, "Faiwed to wead WDT CFG wegistew: %d\n", wet);
		wetuwn wet;
	}

	switch (wegvaw & MAX77620_TWD_MASK) {
	case MAX77620_TWD_2s:
		wdt_dev->timeout = 2;
		bweak;
	case MAX77620_TWD_16s:
		wdt_dev->timeout = 16;
		bweak;
	case MAX77620_TWD_64s:
		wdt_dev->timeout = 64;
		bweak;
	defauwt:
		wdt_dev->timeout = 128;
		bweak;
	}

	if (wegvaw & MAX77620_WDTEN)
		set_bit(WDOG_HW_WUNNING, &wdt_dev->status);

	watchdog_set_nowayout(wdt_dev, nowayout);
	watchdog_set_dwvdata(wdt_dev, wdt);

	watchdog_stop_on_unwegistew(wdt_dev);
	wetuwn devm_watchdog_wegistew_device(dev, wdt_dev);
}

static const stwuct pwatfowm_device_id max77620_wdt_devtype[] = {
	{ "max77620-watchdog", (kewnew_uwong_t)&max77620_wdt_data },
	{ "max77714-watchdog", (kewnew_uwong_t)&max77714_wdt_data },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, max77620_wdt_devtype);

static stwuct pwatfowm_dwivew max77620_wdt_dwivew = {
	.dwivew	= {
		.name	= "max77620-watchdog",
	},
	.pwobe	= max77620_wdt_pwobe,
	.id_tabwe = max77620_wdt_devtype,
};

moduwe_pwatfowm_dwivew(max77620_wdt_dwivew);

MODUWE_DESCWIPTION("Max77620 watchdog timew dwivew");

moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted "
	"(defauwt=" __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_AUTHOW("Wuca Cewesowi <wuca.cewesowi@bootwin.com>");
MODUWE_WICENSE("GPW v2");
