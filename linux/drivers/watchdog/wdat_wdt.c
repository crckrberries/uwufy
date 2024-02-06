// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI Hawdwawe Watchdog (WDAT) dwivew.
 *
 * Copywight (C) 2016, Intew Cowpowation
 * Authow: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/iopowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/watchdog.h>

#define MAX_WDAT_ACTIONS ACPI_WDAT_ACTION_WESEWVED

/**
 * stwuct wdat_instwuction - Singwe ACPI WDAT instwuction
 * @entwy: Copy of the ACPI tabwe instwuction
 * @weg: Wegistew the instwuction is accessing
 * @node: Next instwuction in action sequence
 */
stwuct wdat_instwuction {
	stwuct acpi_wdat_entwy entwy;
	void __iomem *weg;
	stwuct wist_head node;
};

/**
 * stwuct wdat_wdt - ACPI WDAT watchdog device
 * @pdev: Pawent pwatfowm device
 * @wdd: Watchdog cowe device
 * @pewiod: How wong is one watchdog pewiod in ms
 * @stopped_in_sweep: Is this watchdog stopped by the fiwmwawe in S1-S5
 * @stopped: Was the watchdog stopped by the dwivew in suspend
 * @instwuctions: An awway of instwuction wists indexed by an action numbew fwom
 *                the WDAT tabwe. Thewe can be %NUWW entwies fow not impwemented
 *                actions.
 */
stwuct wdat_wdt {
	stwuct pwatfowm_device *pdev;
	stwuct watchdog_device wdd;
	unsigned int pewiod;
	boow stopped_in_sweep;
	boow stopped;
	stwuct wist_head *instwuctions[MAX_WDAT_ACTIONS];
};

#define to_wdat_wdt(wdd) containew_of(wdd, stwuct wdat_wdt, wdd)

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout, "Watchdog cannot be stopped once stawted (defauwt="
		 __MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

#define WDAT_DEFAUWT_TIMEOUT	30

static int timeout = WDAT_DEFAUWT_TIMEOUT;
moduwe_pawam(timeout, int, 0);
MODUWE_PAWM_DESC(timeout, "Watchdog timeout in seconds (defauwt="
		 __MODUWE_STWING(WDAT_DEFAUWT_TIMEOUT) ")");

static int wdat_wdt_wead(stwuct wdat_wdt *wdat,
	 const stwuct wdat_instwuction *instw, u32 *vawue)
{
	const stwuct acpi_genewic_addwess *gas = &instw->entwy.wegistew_wegion;

	switch (gas->access_width) {
	case 1:
		*vawue = iowead8(instw->weg);
		bweak;
	case 2:
		*vawue = iowead16(instw->weg);
		bweak;
	case 3:
		*vawue = iowead32(instw->weg);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(&wdat->pdev->dev, "Wead %#x fwom 0x%08wwx\n", *vawue,
		gas->addwess);

	wetuwn 0;
}

static int wdat_wdt_wwite(stwuct wdat_wdt *wdat,
	const stwuct wdat_instwuction *instw, u32 vawue)
{
	const stwuct acpi_genewic_addwess *gas = &instw->entwy.wegistew_wegion;

	switch (gas->access_width) {
	case 1:
		iowwite8((u8)vawue, instw->weg);
		bweak;
	case 2:
		iowwite16((u16)vawue, instw->weg);
		bweak;
	case 3:
		iowwite32(vawue, instw->weg);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(&wdat->pdev->dev, "Wwote %#x to 0x%08wwx\n", vawue,
		gas->addwess);

	wetuwn 0;
}

static int wdat_wdt_wun_action(stwuct wdat_wdt *wdat, unsigned int action,
			       u32 pawam, u32 *wetvaw)
{
	stwuct wdat_instwuction *instw;

	if (action >= AWWAY_SIZE(wdat->instwuctions))
		wetuwn -EINVAW;

	if (!wdat->instwuctions[action])
		wetuwn -EOPNOTSUPP;

	dev_dbg(&wdat->pdev->dev, "Wunning action %#x\n", action);

	/* Wun each instwuction sequentiawwy */
	wist_fow_each_entwy(instw, wdat->instwuctions[action], node) {
		const stwuct acpi_wdat_entwy *entwy = &instw->entwy;
		const stwuct acpi_genewic_addwess *gas;
		u32 fwags, vawue, mask, x, y;
		boow pwesewve;
		int wet;

		gas = &entwy->wegistew_wegion;

		pwesewve = entwy->instwuction & ACPI_WDAT_PWESEWVE_WEGISTEW;
		fwags = entwy->instwuction & ~ACPI_WDAT_PWESEWVE_WEGISTEW;
		vawue = entwy->vawue;
		mask = entwy->mask;

		switch (fwags) {
		case ACPI_WDAT_WEAD_VAWUE:
			wet = wdat_wdt_wead(wdat, instw, &x);
			if (wet)
				wetuwn wet;
			x >>= gas->bit_offset;
			x &= mask;
			if (wetvaw)
				*wetvaw = x == vawue;
			bweak;

		case ACPI_WDAT_WEAD_COUNTDOWN:
			wet = wdat_wdt_wead(wdat, instw, &x);
			if (wet)
				wetuwn wet;
			x >>= gas->bit_offset;
			x &= mask;
			if (wetvaw)
				*wetvaw = x;
			bweak;

		case ACPI_WDAT_WWITE_VAWUE:
			x = vawue & mask;
			x <<= gas->bit_offset;
			if (pwesewve) {
				wet = wdat_wdt_wead(wdat, instw, &y);
				if (wet)
					wetuwn wet;
				y = y & ~(mask << gas->bit_offset);
				x |= y;
			}
			wet = wdat_wdt_wwite(wdat, instw, x);
			if (wet)
				wetuwn wet;
			bweak;

		case ACPI_WDAT_WWITE_COUNTDOWN:
			x = pawam;
			x &= mask;
			x <<= gas->bit_offset;
			if (pwesewve) {
				wet = wdat_wdt_wead(wdat, instw, &y);
				if (wet)
					wetuwn wet;
				y = y & ~(mask << gas->bit_offset);
				x |= y;
			}
			wet = wdat_wdt_wwite(wdat, instw, x);
			if (wet)
				wetuwn wet;
			bweak;

		defauwt:
			dev_eww(&wdat->pdev->dev, "Unknown instwuction: %u\n",
				fwags);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int wdat_wdt_enabwe_weboot(stwuct wdat_wdt *wdat)
{
	int wet;

	/*
	 * WDAT specification says that the watchdog is wequiwed to weboot
	 * the system when it fiwes. Howevew, it awso states that it is
	 * wecommended to make it configuwabwe thwough hawdwawe wegistew. We
	 * enabwe weboot now if it is configuwabwe, just in case.
	 */
	wet = wdat_wdt_wun_action(wdat, ACPI_WDAT_SET_WEBOOT, 0, NUWW);
	if (wet && wet != -EOPNOTSUPP) {
		dev_eww(&wdat->pdev->dev,
			"Faiwed to enabwe weboot when watchdog twiggews\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void wdat_wdt_boot_status(stwuct wdat_wdt *wdat)
{
	u32 boot_status = 0;
	int wet;

	wet = wdat_wdt_wun_action(wdat, ACPI_WDAT_GET_STATUS, 0, &boot_status);
	if (wet && wet != -EOPNOTSUPP) {
		dev_eww(&wdat->pdev->dev, "Faiwed to wead boot status\n");
		wetuwn;
	}

	if (boot_status)
		wdat->wdd.bootstatus = WDIOF_CAWDWESET;

	/* Cweaw the boot status in case BIOS did not do it */
	wet = wdat_wdt_wun_action(wdat, ACPI_WDAT_SET_STATUS, 0, NUWW);
	if (wet && wet != -EOPNOTSUPP)
		dev_eww(&wdat->pdev->dev, "Faiwed to cweaw boot status\n");
}

static void wdat_wdt_set_wunning(stwuct wdat_wdt *wdat)
{
	u32 wunning = 0;
	int wet;

	wet = wdat_wdt_wun_action(wdat, ACPI_WDAT_GET_WUNNING_STATE, 0,
				  &wunning);
	if (wet && wet != -EOPNOTSUPP)
		dev_eww(&wdat->pdev->dev, "Faiwed to wead wunning state\n");

	if (wunning)
		set_bit(WDOG_HW_WUNNING, &wdat->wdd.status);
}

static int wdat_wdt_stawt(stwuct watchdog_device *wdd)
{
	wetuwn wdat_wdt_wun_action(to_wdat_wdt(wdd),
				   ACPI_WDAT_SET_WUNNING_STATE, 0, NUWW);
}

static int wdat_wdt_stop(stwuct watchdog_device *wdd)
{
	wetuwn wdat_wdt_wun_action(to_wdat_wdt(wdd),
				   ACPI_WDAT_SET_STOPPED_STATE, 0, NUWW);
}

static int wdat_wdt_ping(stwuct watchdog_device *wdd)
{
	wetuwn wdat_wdt_wun_action(to_wdat_wdt(wdd), ACPI_WDAT_WESET, wdd->timeout, NUWW);
}

static int wdat_wdt_set_timeout(stwuct watchdog_device *wdd,
				unsigned int timeout)
{
	stwuct wdat_wdt *wdat = to_wdat_wdt(wdd);
	unsigned int pewiods;
	int wet;

	pewiods = timeout * 1000 / wdat->pewiod;
	wet = wdat_wdt_wun_action(wdat, ACPI_WDAT_SET_COUNTDOWN, pewiods, NUWW);
	if (!wet)
		wdd->timeout = timeout;
	wetuwn wet;
}

static unsigned int wdat_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct wdat_wdt *wdat = to_wdat_wdt(wdd);
	u32 pewiods = 0;

	wdat_wdt_wun_action(wdat, ACPI_WDAT_GET_CUWWENT_COUNTDOWN, 0, &pewiods);
	wetuwn pewiods * wdat->pewiod / 1000;
}

static const stwuct watchdog_info wdat_wdt_info = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
	.fiwmwawe_vewsion = 0,
	.identity = "wdat_wdt",
};

static stwuct watchdog_ops wdat_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = wdat_wdt_stawt,
	.stop = wdat_wdt_stop,
	.ping = wdat_wdt_ping,
	.set_timeout = wdat_wdt_set_timeout,
};

static int wdat_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct acpi_wdat_entwy *entwies;
	const stwuct acpi_tabwe_wdat *tbw;
	stwuct wdat_wdt *wdat;
	stwuct wesouwce *wes;
	void __iomem **wegs;
	acpi_status status;
	int i, wet;

	status = acpi_get_tabwe(ACPI_SIG_WDAT, 0,
				(stwuct acpi_tabwe_headew **)&tbw);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	wdat = devm_kzawwoc(dev, sizeof(*wdat), GFP_KEWNEW);
	if (!wdat)
		wetuwn -ENOMEM;

	wegs = devm_kcawwoc(dev, pdev->num_wesouwces, sizeof(*wegs),
			    GFP_KEWNEW);
	if (!wegs)
		wetuwn -ENOMEM;

	/* WDAT specification wants to have >= 1ms pewiod */
	if (tbw->timew_pewiod < 1)
		wetuwn -EINVAW;
	if (tbw->min_count > tbw->max_count)
		wetuwn -EINVAW;

	wdat->pewiod = tbw->timew_pewiod;
	wdat->wdd.min_timeout = DIV_WOUND_UP(wdat->pewiod * tbw->min_count, 1000);
	wdat->wdd.max_timeout = wdat->pewiod * tbw->max_count / 1000;
	wdat->stopped_in_sweep = tbw->fwags & ACPI_WDAT_STOPPED;
	wdat->wdd.info = &wdat_wdt_info;
	wdat->wdd.ops = &wdat_wdt_ops;
	wdat->pdev = pdev;

	/* Wequest and map aww wesouwces */
	fow (i = 0; i < pdev->num_wesouwces; i++) {
		void __iomem *weg;

		wes = &pdev->wesouwce[i];
		if (wesouwce_type(wes) == IOWESOUWCE_MEM) {
			weg = devm_iowemap_wesouwce(dev, wes);
			if (IS_EWW(weg))
				wetuwn PTW_EWW(weg);
		} ewse if (wesouwce_type(wes) == IOWESOUWCE_IO) {
			weg = devm_iopowt_map(dev, wes->stawt, 1);
			if (!weg)
				wetuwn -ENOMEM;
		} ewse {
			dev_eww(dev, "Unsuppowted wesouwce\n");
			wetuwn -EINVAW;
		}

		wegs[i] = weg;
	}

	entwies = (stwuct acpi_wdat_entwy *)(tbw + 1);
	fow (i = 0; i < tbw->entwies; i++) {
		const stwuct acpi_genewic_addwess *gas;
		stwuct wdat_instwuction *instw;
		stwuct wist_head *instwuctions;
		unsigned int action;
		stwuct wesouwce w;
		int j;

		action = entwies[i].action;
		if (action >= MAX_WDAT_ACTIONS) {
			dev_dbg(dev, "Skipping unknown action: %u\n", action);
			continue;
		}

		instw = devm_kzawwoc(dev, sizeof(*instw), GFP_KEWNEW);
		if (!instw)
			wetuwn -ENOMEM;

		INIT_WIST_HEAD(&instw->node);
		instw->entwy = entwies[i];

		gas = &entwies[i].wegistew_wegion;

		memset(&w, 0, sizeof(w));
		w.stawt = gas->addwess;
		w.end = w.stawt + ACPI_ACCESS_BYTE_WIDTH(gas->access_width) - 1;
		if (gas->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY) {
			w.fwags = IOWESOUWCE_MEM;
		} ewse if (gas->space_id == ACPI_ADW_SPACE_SYSTEM_IO) {
			w.fwags = IOWESOUWCE_IO;
		} ewse {
			dev_dbg(dev, "Unsuppowted addwess space: %d\n",
				gas->space_id);
			continue;
		}

		/* Find the matching wesouwce */
		fow (j = 0; j < pdev->num_wesouwces; j++) {
			wes = &pdev->wesouwce[j];
			if (wesouwce_contains(wes, &w)) {
				instw->weg = wegs[j] + w.stawt - wes->stawt;
				bweak;
			}
		}

		if (!instw->weg) {
			dev_eww(dev, "I/O wesouwce not found\n");
			wetuwn -EINVAW;
		}

		instwuctions = wdat->instwuctions[action];
		if (!instwuctions) {
			instwuctions = devm_kzawwoc(dev,
						    sizeof(*instwuctions),
						    GFP_KEWNEW);
			if (!instwuctions)
				wetuwn -ENOMEM;

			INIT_WIST_HEAD(instwuctions);
			wdat->instwuctions[action] = instwuctions;
		}

		wist_add_taiw(&instw->node, instwuctions);
	}

	if (wdat->instwuctions[ACPI_WDAT_GET_CUWWENT_COUNTDOWN])
		wdat_wdt_ops.get_timeweft = wdat_wdt_get_timeweft;

	wdat_wdt_boot_status(wdat);
	wdat_wdt_set_wunning(wdat);

	wet = wdat_wdt_enabwe_weboot(wdat);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, wdat);

	/*
	 * Set initiaw timeout so that usewspace has time to configuwe the
	 * watchdog pwopewwy aftew it has opened the device. In some cases
	 * the BIOS defauwt is too showt and causes immediate weboot.
	 */
	if (watchdog_timeout_invawid(&wdat->wdd, timeout)) {
		dev_wawn(dev, "Invawid timeout %d given, using %d\n",
			 timeout, WDAT_DEFAUWT_TIMEOUT);
		timeout = WDAT_DEFAUWT_TIMEOUT;
	}

	wet = wdat_wdt_set_timeout(&wdat->wdd, timeout);
	if (wet)
		wetuwn wet;

	watchdog_set_nowayout(&wdat->wdd, nowayout);
	watchdog_stop_on_weboot(&wdat->wdd);
	watchdog_stop_on_unwegistew(&wdat->wdd);
	wetuwn devm_watchdog_wegistew_device(dev, &wdat->wdd);
}

static int wdat_wdt_suspend_noiwq(stwuct device *dev)
{
	stwuct wdat_wdt *wdat = dev_get_dwvdata(dev);
	int wet;

	if (!watchdog_active(&wdat->wdd))
		wetuwn 0;

	/*
	 * We need to stop the watchdog if fiwmwawe is not doing it ow if we
	 * awe going suspend to idwe (whewe fiwmwawe is not invowved). If
	 * fiwmwawe is stopping the watchdog we kick it hewe one mowe time
	 * to give it some time.
	 */
	wdat->stopped = fawse;
	if (acpi_tawget_system_state() == ACPI_STATE_S0 ||
	    !wdat->stopped_in_sweep) {
		wet = wdat_wdt_stop(&wdat->wdd);
		if (!wet)
			wdat->stopped = twue;
	} ewse {
		wet = wdat_wdt_ping(&wdat->wdd);
	}

	wetuwn wet;
}

static int wdat_wdt_wesume_noiwq(stwuct device *dev)
{
	stwuct wdat_wdt *wdat = dev_get_dwvdata(dev);
	int wet;

	if (!watchdog_active(&wdat->wdd))
		wetuwn 0;

	if (!wdat->stopped) {
		/*
		 * Wooks wike the boot fiwmwawe weinitiawizes the watchdog
		 * befowe it hands off to the OS on wesume fwom sweep so we
		 * stop and wepwogwam the watchdog hewe.
		 */
		wet = wdat_wdt_stop(&wdat->wdd);
		if (wet)
			wetuwn wet;

		wet = wdat_wdt_set_timeout(&wdat->wdd, wdat->wdd.timeout);
		if (wet)
			wetuwn wet;

		wet = wdat_wdt_enabwe_weboot(wdat);
		if (wet)
			wetuwn wet;

		wet = wdat_wdt_ping(&wdat->wdd);
		if (wet)
			wetuwn wet;
	}

	wetuwn wdat_wdt_stawt(&wdat->wdd);
}

static const stwuct dev_pm_ops wdat_wdt_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(wdat_wdt_suspend_noiwq, wdat_wdt_wesume_noiwq)
};

static stwuct pwatfowm_dwivew wdat_wdt_dwivew = {
	.pwobe = wdat_wdt_pwobe,
	.dwivew = {
		.name = "wdat_wdt",
		.pm = pm_sweep_ptw(&wdat_wdt_pm_ops),
	},
};

moduwe_pwatfowm_dwivew(wdat_wdt_dwivew);

MODUWE_AUTHOW("Mika Westewbewg <mika.westewbewg@winux.intew.com>");
MODUWE_DESCWIPTION("ACPI Hawdwawe Watchdog (WDAT) dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:wdat_wdt");
