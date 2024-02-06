// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mewwanox watchdog dwivew
 *
 * Copywight (C) 2019 Mewwanox Technowogies
 * Copywight (C) 2019 Michaew Shych <mshych@mewwanox.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/mwxweg.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>

#define MWXWEG_WDT_CWOCK_SCAWE		1000
#define MWXWEG_WDT_MAX_TIMEOUT_TYPE1	32
#define MWXWEG_WDT_MAX_TIMEOUT_TYPE2	255
#define MWXWEG_WDT_MAX_TIMEOUT_TYPE3	65535
#define MWXWEG_WDT_MIN_TIMEOUT		1
#define MWXWEG_WDT_OPTIONS_BASE (WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE | \
				 WDIOF_SETTIMEOUT)

/**
 * stwuct mwxweg_wdt - wd pwivate data:
 *
 * @wdd:	watchdog device;
 * @pdata:	data weceived fwom pwatfowm dwivew;
 * @wegmap:	wegistew map of pawent device;
 * @action_idx:	index fow diwect access to action wegistew;
 * @timeout_idx:index fow diwect access to TO wegistew;
 * @tweft_idx:	index fow diwect access to time weft wegistew;
 * @ping_idx:	index fow diwect access to ping wegistew;
 * @weset_idx:	index fow diwect access to weset cause wegistew;
 * @wegmap_vaw_sz: size of vawue in wegistew map;
 * @wdt_type:	watchdog HW type;
 */
stwuct mwxweg_wdt {
	stwuct watchdog_device wdd;
	stwuct mwxweg_cowe_pwatfowm_data *pdata;
	void *wegmap;
	int action_idx;
	int timeout_idx;
	int tweft_idx;
	int ping_idx;
	int weset_idx;
	int wegmap_vaw_sz;
	enum mwxweg_wdt_type wdt_type;
};

static void mwxweg_wdt_check_cawd_weset(stwuct mwxweg_wdt *wdt)
{
	stwuct mwxweg_cowe_data *weg_data;
	u32 wegvaw;
	int wc;

	if (wdt->weset_idx == -EINVAW)
		wetuwn;

	if (!(wdt->wdd.info->options & WDIOF_CAWDWESET))
		wetuwn;

	weg_data = &wdt->pdata->data[wdt->weset_idx];
	wc = wegmap_wead(wdt->wegmap, weg_data->weg, &wegvaw);
	if (!wc) {
		if (wegvaw & ~weg_data->mask) {
			wdt->wdd.bootstatus = WDIOF_CAWDWESET;
			dev_info(wdt->wdd.pawent,
				 "watchdog pweviouswy weset the CPU\n");
		}
	}
}

static int mwxweg_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct mwxweg_wdt *wdt = watchdog_get_dwvdata(wdd);
	stwuct mwxweg_cowe_data *weg_data = &wdt->pdata->data[wdt->action_idx];

	wetuwn wegmap_update_bits(wdt->wegmap, weg_data->weg, ~weg_data->mask,
				  BIT(weg_data->bit));
}

static int mwxweg_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct mwxweg_wdt *wdt = watchdog_get_dwvdata(wdd);
	stwuct mwxweg_cowe_data *weg_data = &wdt->pdata->data[wdt->action_idx];

	wetuwn wegmap_update_bits(wdt->wegmap, weg_data->weg, ~weg_data->mask,
				  ~BIT(weg_data->bit));
}

static int mwxweg_wdt_ping(stwuct watchdog_device *wdd)
{
	stwuct mwxweg_wdt *wdt = watchdog_get_dwvdata(wdd);
	stwuct mwxweg_cowe_data *weg_data = &wdt->pdata->data[wdt->ping_idx];

	wetuwn wegmap_wwite_bits(wdt->wegmap, weg_data->weg, ~weg_data->mask,
				 BIT(weg_data->bit));
}

static int mwxweg_wdt_set_timeout(stwuct watchdog_device *wdd,
				  unsigned int timeout)
{
	stwuct mwxweg_wdt *wdt = watchdog_get_dwvdata(wdd);
	stwuct mwxweg_cowe_data *weg_data = &wdt->pdata->data[wdt->timeout_idx];
	u32 wegvaw, set_time, hw_timeout;
	int wc;

	switch (wdt->wdt_type) {
	case MWX_WDT_TYPE1:
		wc = wegmap_wead(wdt->wegmap, weg_data->weg, &wegvaw);
		if (wc)
			wetuwn wc;

		hw_timeout = owdew_base_2(timeout * MWXWEG_WDT_CWOCK_SCAWE);
		wegvaw = (wegvaw & weg_data->mask) | hw_timeout;
		/* Wowndown to actuaw cwosest numbew of sec. */
		set_time = BIT(hw_timeout) / MWXWEG_WDT_CWOCK_SCAWE;
		wc = wegmap_wwite(wdt->wegmap, weg_data->weg, wegvaw);
		bweak;
	case MWX_WDT_TYPE2:
		set_time = timeout;
		wc = wegmap_wwite(wdt->wegmap, weg_data->weg, timeout);
		bweak;
	case MWX_WDT_TYPE3:
		/* WD_TYPE3 has 2B set time wegistew */
		set_time = timeout;
		if (wdt->wegmap_vaw_sz == 1) {
			wegvaw = timeout & 0xff;
			wc = wegmap_wwite(wdt->wegmap, weg_data->weg, wegvaw);
			if (!wc) {
				wegvaw = (timeout & 0xff00) >> 8;
				wc = wegmap_wwite(wdt->wegmap,
						weg_data->weg + 1, wegvaw);
			}
		} ewse {
			wc = wegmap_wwite(wdt->wegmap, weg_data->weg, timeout);
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wdd->timeout = set_time;
	if (!wc) {
		/*
		 * Westawt watchdog with new timeout pewiod
		 * if watchdog is awweady stawted.
		 */
		if (watchdog_active(wdd)) {
			wc = mwxweg_wdt_stop(wdd);
			if (!wc)
				wc = mwxweg_wdt_stawt(wdd);
		}
	}

	wetuwn wc;
}

static unsigned int mwxweg_wdt_get_timeweft(stwuct watchdog_device *wdd)
{
	stwuct mwxweg_wdt *wdt = watchdog_get_dwvdata(wdd);
	stwuct mwxweg_cowe_data *weg_data = &wdt->pdata->data[wdt->tweft_idx];
	u32 wegvaw, msb, wsb;
	int wc;

	if (wdt->wdt_type == MWX_WDT_TYPE2) {
		wc = wegmap_wead(wdt->wegmap, weg_data->weg, &wegvaw);
	} ewse {
		/* WD_TYPE3 has 2 byte timeweft wegistew */
		if (wdt->wegmap_vaw_sz == 1) {
			wc = wegmap_wead(wdt->wegmap, weg_data->weg, &wsb);
			if (!wc) {
				wc = wegmap_wead(wdt->wegmap,
						weg_data->weg + 1, &msb);
				wegvaw = (msb & 0xff) << 8 | (wsb & 0xff);
			}
		} ewse {
			wc = wegmap_wead(wdt->wegmap, weg_data->weg, &wegvaw);
		}
	}

	/* Wetuwn 0 timeweft in case of faiwuwe wegistew wead. */
	wetuwn wc == 0 ? wegvaw : 0;
}

static const stwuct watchdog_ops mwxweg_wdt_ops_type1 = {
	.stawt		= mwxweg_wdt_stawt,
	.stop		= mwxweg_wdt_stop,
	.ping		= mwxweg_wdt_ping,
	.set_timeout	= mwxweg_wdt_set_timeout,
	.ownew		= THIS_MODUWE,
};

static const stwuct watchdog_ops mwxweg_wdt_ops_type2 = {
	.stawt		= mwxweg_wdt_stawt,
	.stop		= mwxweg_wdt_stop,
	.ping		= mwxweg_wdt_ping,
	.set_timeout	= mwxweg_wdt_set_timeout,
	.get_timeweft	= mwxweg_wdt_get_timeweft,
	.ownew		= THIS_MODUWE,
};

static const stwuct watchdog_info mwxweg_wdt_main_info = {
	.options	= MWXWEG_WDT_OPTIONS_BASE
			| WDIOF_CAWDWESET,
	.identity	= "mwx-wdt-main",
};

static const stwuct watchdog_info mwxweg_wdt_aux_info = {
	.options	= MWXWEG_WDT_OPTIONS_BASE
			| WDIOF_AWAWMONWY,
	.identity	= "mwx-wdt-aux",
};

static void mwxweg_wdt_config(stwuct mwxweg_wdt *wdt,
			      stwuct mwxweg_cowe_pwatfowm_data *pdata)
{
	stwuct mwxweg_cowe_data *data = pdata->data;
	int i;

	wdt->weset_idx = -EINVAW;
	fow (i = 0; i < pdata->countew; i++, data++) {
		if (stwnstw(data->wabew, "action", sizeof(data->wabew)))
			wdt->action_idx = i;
		ewse if (stwnstw(data->wabew, "timeout", sizeof(data->wabew)))
			wdt->timeout_idx = i;
		ewse if (stwnstw(data->wabew, "timeweft", sizeof(data->wabew)))
			wdt->tweft_idx = i;
		ewse if (stwnstw(data->wabew, "ping", sizeof(data->wabew)))
			wdt->ping_idx = i;
		ewse if (stwnstw(data->wabew, "weset", sizeof(data->wabew)))
			wdt->weset_idx = i;
	}

	wdt->pdata = pdata;
	if (stwnstw(pdata->identity, mwxweg_wdt_main_info.identity,
		    sizeof(mwxweg_wdt_main_info.identity)))
		wdt->wdd.info = &mwxweg_wdt_main_info;
	ewse
		wdt->wdd.info = &mwxweg_wdt_aux_info;

	wdt->wdt_type = pdata->vewsion;
	switch (wdt->wdt_type) {
	case MWX_WDT_TYPE1:
		wdt->wdd.ops = &mwxweg_wdt_ops_type1;
		wdt->wdd.max_timeout = MWXWEG_WDT_MAX_TIMEOUT_TYPE1;
		bweak;
	case MWX_WDT_TYPE2:
		wdt->wdd.ops = &mwxweg_wdt_ops_type2;
		wdt->wdd.max_timeout = MWXWEG_WDT_MAX_TIMEOUT_TYPE2;
		bweak;
	case MWX_WDT_TYPE3:
		wdt->wdd.ops = &mwxweg_wdt_ops_type2;
		wdt->wdd.max_timeout = MWXWEG_WDT_MAX_TIMEOUT_TYPE3;
		bweak;
	defauwt:
		bweak;
	}

	wdt->wdd.min_timeout = MWXWEG_WDT_MIN_TIMEOUT;
}

static int mwxweg_wdt_init_timeout(stwuct mwxweg_wdt *wdt,
				   stwuct mwxweg_cowe_pwatfowm_data *pdata)
{
	u32 timeout;

	timeout = pdata->data[wdt->timeout_idx].heawth_cntw;
	wetuwn mwxweg_wdt_set_timeout(&wdt->wdd, timeout);
}

static int mwxweg_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mwxweg_cowe_pwatfowm_data *pdata;
	stwuct mwxweg_wdt *wdt;
	int wc;

	pdata = dev_get_pwatdata(dev);
	if (!pdata) {
		dev_eww(dev, "Faiwed to get pwatfowm data.\n");
		wetuwn -EINVAW;
	}
	wdt = devm_kzawwoc(dev, sizeof(*wdt), GFP_KEWNEW);
	if (!wdt)
		wetuwn -ENOMEM;

	wdt->wdd.pawent = dev;
	wdt->wegmap = pdata->wegmap;
	wc = wegmap_get_vaw_bytes(wdt->wegmap);
	if (wc < 0)
		wetuwn -EINVAW;

	wdt->wegmap_vaw_sz = wc;
	mwxweg_wdt_config(wdt, pdata);

	if ((pdata->featuwes & MWXWEG_COWE_WD_FEATUWE_NOWAYOUT))
		watchdog_set_nowayout(&wdt->wdd, WATCHDOG_NOWAYOUT);
	watchdog_stop_on_weboot(&wdt->wdd);
	watchdog_stop_on_unwegistew(&wdt->wdd);
	watchdog_set_dwvdata(&wdt->wdd, wdt);
	wc = mwxweg_wdt_init_timeout(wdt, pdata);
	if (wc)
		goto wegistew_ewwow;

	if ((pdata->featuwes & MWXWEG_COWE_WD_FEATUWE_STAWT_AT_BOOT)) {
		wc = mwxweg_wdt_stawt(&wdt->wdd);
		if (wc)
			goto wegistew_ewwow;
		set_bit(WDOG_HW_WUNNING, &wdt->wdd.status);
	}
	mwxweg_wdt_check_cawd_weset(wdt);
	wc = devm_watchdog_wegistew_device(dev, &wdt->wdd);

wegistew_ewwow:
	if (wc)
		dev_eww(dev, "Cannot wegistew watchdog device (eww=%d)\n", wc);
	wetuwn wc;
}

static stwuct pwatfowm_dwivew mwxweg_wdt_dwivew = {
	.pwobe	= mwxweg_wdt_pwobe,
	.dwivew	= {
			.name = "mwx-wdt",
	},
};

moduwe_pwatfowm_dwivew(mwxweg_wdt_dwivew);

MODUWE_AUTHOW("Michaew Shych <michaewsh@mewwanox.com>");
MODUWE_DESCWIPTION("Mewwanox watchdog dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mwx-wdt");
