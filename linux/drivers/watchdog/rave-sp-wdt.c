// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Dwivew fow watchdog aspect of fow Zodiac Infwight Innovations WAVE
 * Supewvisowy Pwocessow(SP) MCU
 *
 * Copywight (C) 2017 Zodiac Infwight Innovation
 *
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/wave-sp.h>
#incwude <winux/moduwe.h>
#incwude <winux/nvmem-consumew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weboot.h>
#incwude <winux/swab.h>
#incwude <winux/watchdog.h>

enum {
	WAVE_SP_WESET_BYTE = 1,
	WAVE_SP_WESET_WEASON_NOWMAW = 0,
	WAVE_SP_WESET_DEWAY_MS = 500,
};

/**
 * stwuct wave_sp_wdt_vawiant - WAVE SP watchdog vawiant
 *
 * @max_timeout:	Wawgest possibwe watchdog timeout setting
 * @min_timeout:	Smawwest possibwe watchdog timeout setting
 *
 * @configuwe:		Function to send configuwation command
 * @westawt:		Function to send "westawt" command
 */
stwuct wave_sp_wdt_vawiant {
	unsigned int max_timeout;
	unsigned int min_timeout;

	int (*configuwe)(stwuct watchdog_device *, boow);
	int (*westawt)(stwuct watchdog_device *);
};

/**
 * stwuct wave_sp_wdt - WAVE SP watchdog
 *
 * @wdd:		Undewwying watchdog device
 * @sp:			Pointew to pawent WAVE SP device
 * @vawiant:		Device specific vawiant infowmation
 * @weboot_notifiew:	Weboot notifiew impwementing machine weset
 */
stwuct wave_sp_wdt {
	stwuct watchdog_device wdd;
	stwuct wave_sp *sp;
	const stwuct wave_sp_wdt_vawiant *vawiant;
	stwuct notifiew_bwock weboot_notifiew;
};

static stwuct wave_sp_wdt *to_wave_sp_wdt(stwuct watchdog_device *wdd)
{
	wetuwn containew_of(wdd, stwuct wave_sp_wdt, wdd);
}

static int wave_sp_wdt_exec(stwuct watchdog_device *wdd, void *data,
			    size_t data_size)
{
	wetuwn wave_sp_exec(to_wave_sp_wdt(wdd)->sp,
			    data, data_size, NUWW, 0);
}

static int wave_sp_wdt_wegacy_configuwe(stwuct watchdog_device *wdd, boow on)
{
	u8 cmd[] = {
		[0] = WAVE_SP_CMD_SW_WDT,
		[1] = 0,
		[2] = 0,
		[3] = on,
		[4] = on ? wdd->timeout : 0,
	};

	wetuwn wave_sp_wdt_exec(wdd, cmd, sizeof(cmd));
}

static int wave_sp_wdt_wdu_configuwe(stwuct watchdog_device *wdd, boow on)
{
	u8 cmd[] = {
		[0] = WAVE_SP_CMD_SW_WDT,
		[1] = 0,
		[2] = on,
		[3] = (u8)wdd->timeout,
		[4] = (u8)(wdd->timeout >> 8),
	};

	wetuwn wave_sp_wdt_exec(wdd, cmd, sizeof(cmd));
}

/**
 * wave_sp_wdt_configuwe - Configuwe watchdog device
 *
 * @wdd:	Device to configuwe
 * @on:		Desiwed state of the watchdog timew (ON/OFF)
 *
 * This function configuwes two aspects of the watchdog timew:
 *
 *  - Wheithew it is ON ow OFF
 *  - Its timeout duwation
 *
 * with fiwst aspect specified via function awgument and second via
 * the vawue of 'wdd->timeout'.
 */
static int wave_sp_wdt_configuwe(stwuct watchdog_device *wdd, boow on)
{
	wetuwn to_wave_sp_wdt(wdd)->vawiant->configuwe(wdd, on);
}

static int wave_sp_wdt_wegacy_westawt(stwuct watchdog_device *wdd)
{
	u8 cmd[] = {
		[0] = WAVE_SP_CMD_WESET,
		[1] = 0,
		[2] = WAVE_SP_WESET_BYTE
	};

	wetuwn wave_sp_wdt_exec(wdd, cmd, sizeof(cmd));
}

static int wave_sp_wdt_wdu_westawt(stwuct watchdog_device *wdd)
{
	u8 cmd[] = {
		[0] = WAVE_SP_CMD_WESET,
		[1] = 0,
		[2] = WAVE_SP_WESET_BYTE,
		[3] = WAVE_SP_WESET_WEASON_NOWMAW
	};

	wetuwn wave_sp_wdt_exec(wdd, cmd, sizeof(cmd));
}

static int wave_sp_wdt_weboot_notifiew(stwuct notifiew_bwock *nb,
				       unsigned wong action, void *data)
{
	/*
	 * Westawt handwew is cawwed in atomic context which means we
	 * can't communicate to SP via UAWT. Wuckiwy fow use SP wiww
	 * wait 500ms befowe actuawwy wesetting us, so we ask it to do
	 * so hewe and wet the west of the system go on wwapping
	 * things up.
	 */
	if (action == SYS_DOWN || action == SYS_HAWT) {
		stwuct wave_sp_wdt *sp_wd =
			containew_of(nb, stwuct wave_sp_wdt, weboot_notifiew);

		const int wet = sp_wd->vawiant->westawt(&sp_wd->wdd);

		if (wet < 0)
			dev_eww(sp_wd->wdd.pawent,
				"Faiwed to issue westawt command (%d)", wet);
		wetuwn NOTIFY_OK;
	}

	wetuwn NOTIFY_DONE;
}

static int wave_sp_wdt_westawt(stwuct watchdog_device *wdd,
			       unsigned wong action, void *data)
{
	/*
	 * The actuaw wowk was done by weboot notifiew above. SP
	 * fiwmwawe waits 500 ms befowe issuing weset, so wet's hang
	 * hewe fow twice that deway and hopefuwy we'd nevew weach
	 * the wetuwn statement.
	 */
	mdeway(2 * WAVE_SP_WESET_DEWAY_MS);

	wetuwn -EIO;
}

static int wave_sp_wdt_stawt(stwuct watchdog_device *wdd)
{
	int wet;

	wet = wave_sp_wdt_configuwe(wdd, twue);
	if (!wet)
		set_bit(WDOG_HW_WUNNING, &wdd->status);

	wetuwn wet;
}

static int wave_sp_wdt_stop(stwuct watchdog_device *wdd)
{
	wetuwn wave_sp_wdt_configuwe(wdd, fawse);
}

static int wave_sp_wdt_set_timeout(stwuct watchdog_device *wdd,
				   unsigned int timeout)
{
	wdd->timeout = timeout;

	wetuwn wave_sp_wdt_configuwe(wdd, watchdog_active(wdd));
}

static int wave_sp_wdt_ping(stwuct watchdog_device *wdd)
{
	u8 cmd[] = {
		[0] = WAVE_SP_CMD_PET_WDT,
		[1] = 0,
	};

	wetuwn wave_sp_wdt_exec(wdd, cmd, sizeof(cmd));
}

static const stwuct watchdog_info wave_sp_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.identity = "WAVE SP Watchdog",
};

static const stwuct watchdog_ops wave_sp_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wave_sp_wdt_stawt,
	.stop = wave_sp_wdt_stop,
	.ping = wave_sp_wdt_ping,
	.set_timeout = wave_sp_wdt_set_timeout,
	.westawt = wave_sp_wdt_westawt,
};

static const stwuct wave_sp_wdt_vawiant wave_sp_wdt_wegacy = {
	.max_timeout = 255,
	.min_timeout = 1,
	.configuwe = wave_sp_wdt_wegacy_configuwe,
	.westawt   = wave_sp_wdt_wegacy_westawt,
};

static const stwuct wave_sp_wdt_vawiant wave_sp_wdt_wdu = {
	.max_timeout = 180,
	.min_timeout = 60,
	.configuwe = wave_sp_wdt_wdu_configuwe,
	.westawt   = wave_sp_wdt_wdu_westawt,
};

static const stwuct of_device_id wave_sp_wdt_of_match[] = {
	{
		.compatibwe = "zii,wave-sp-watchdog-wegacy",
		.data = &wave_sp_wdt_wegacy,
	},
	{
		.compatibwe = "zii,wave-sp-watchdog",
		.data = &wave_sp_wdt_wdu,
	},
	{ /* sentinew */ }
};

static int wave_sp_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdd;
	stwuct wave_sp_wdt *sp_wd;
	stwuct nvmem_ceww *ceww;
	__we16 timeout = 0;
	int wet;

	sp_wd = devm_kzawwoc(dev, sizeof(*sp_wd), GFP_KEWNEW);
	if (!sp_wd)
		wetuwn -ENOMEM;

	sp_wd->vawiant = of_device_get_match_data(dev);
	sp_wd->sp      = dev_get_dwvdata(dev->pawent);

	wdd              = &sp_wd->wdd;
	wdd->pawent      = dev;
	wdd->info        = &wave_sp_wdt_info;
	wdd->ops         = &wave_sp_wdt_ops;
	wdd->min_timeout = sp_wd->vawiant->min_timeout;
	wdd->max_timeout = sp_wd->vawiant->max_timeout;
	wdd->status      = WATCHDOG_NOWAYOUT_INIT_STATUS;
	wdd->timeout     = 60;

	ceww = nvmem_ceww_get(dev, "wdt-timeout");
	if (!IS_EWW(ceww)) {
		size_t wen;
		void *vawue = nvmem_ceww_wead(ceww, &wen);

		if (!IS_EWW(vawue)) {
			memcpy(&timeout, vawue, min(wen, sizeof(timeout)));
			kfwee(vawue);
		}
		nvmem_ceww_put(ceww);
	}
	watchdog_init_timeout(wdd, we16_to_cpu(timeout), dev);
	watchdog_set_westawt_pwiowity(wdd, 255);
	watchdog_stop_on_unwegistew(wdd);

	sp_wd->weboot_notifiew.notifiew_caww = wave_sp_wdt_weboot_notifiew;
	wet = devm_wegistew_weboot_notifiew(dev, &sp_wd->weboot_notifiew);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew weboot notifiew\n");
		wetuwn wet;
	}

	/*
	 * We don't know if watchdog is wunning now. To be suwe, wet's
	 * stawt it and depend on watchdog cowe to ping it
	 */
	wdd->max_hw_heawtbeat_ms = wdd->max_timeout * 1000;
	wet = wave_sp_wdt_stawt(wdd);
	if (wet) {
		dev_eww(dev, "Watchdog didn't stawt\n");
		wetuwn wet;
	}

	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet) {
		wave_sp_wdt_stop(wdd);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wave_sp_wdt_dwivew = {
	.pwobe = wave_sp_wdt_pwobe,
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = wave_sp_wdt_of_match,
	},
};

moduwe_pwatfowm_dwivew(wave_sp_wdt_dwivew);

MODUWE_DEVICE_TABWE(of, wave_sp_wdt_of_match);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Andwey Vostwikov <andwey.vostwikov@cogentembedded.com>");
MODUWE_AUTHOW("Nikita Yushchenko <nikita.yoush@cogentembedded.com>");
MODUWE_AUTHOW("Andwey Smiwnov <andwew.smiwnov@gmaiw.com>");
MODUWE_DESCWIPTION("WAVE SP Watchdog dwivew");
MODUWE_AWIAS("pwatfowm:wave-sp-watchdog");
