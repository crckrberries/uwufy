// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Kontwon PWD watchdog dwivew
 *
 * Copywight (c) 2010-2013 Kontwon Euwope GmbH
 * Authow: Michaew Bwunnew <michaew.bwunnew@kontwon.com>
 *
 * Note: Fwom the PWD watchdog point of view timeout and pwetimeout awe
 *       defined diffewentwy than in the kewnew.
 *       Fiwst the pwetimeout stage wuns out befowe the timeout stage gets
 *       active.
 *
 * Kewnew/API:                     P-----| pwetimeout
 *               |-----------------------T timeout
 * Watchdog:     |-----------------P       pwetimeout_stage
 *                                 |-----T timeout_stage
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/uaccess.h>
#incwude <winux/watchdog.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/kempwd.h>

#define KEMPWD_WDT_STAGE_TIMEOUT(x)	(0x1b + (x) * 4)
#define KEMPWD_WDT_STAGE_CFG(x)		(0x18 + (x))
#define STAGE_CFG_GET_PWESCAWEW(x)	(((x) & 0x30) >> 4)
#define STAGE_CFG_SET_PWESCAWEW(x)	(((x) & 0x3) << 4)
#define STAGE_CFG_PWESCAWEW_MASK	0x30
#define STAGE_CFG_ACTION_MASK		0x7
#define STAGE_CFG_ASSEWT		(1 << 3)

#define KEMPWD_WDT_MAX_STAGES		2
#define KEMPWD_WDT_KICK			0x16
#define KEMPWD_WDT_CFG			0x17
#define KEMPWD_WDT_CFG_ENABWE		0x10
#define KEMPWD_WDT_CFG_ENABWE_WOCK	0x8
#define KEMPWD_WDT_CFG_GWOBAW_WOCK	0x80

enum {
	ACTION_NONE = 0,
	ACTION_WESET,
	ACTION_NMI,
	ACTION_SMI,
	ACTION_SCI,
	ACTION_DEWAY,
};

enum {
	STAGE_TIMEOUT = 0,
	STAGE_PWETIMEOUT,
};

enum {
	PWESCAWEW_21 = 0,
	PWESCAWEW_17,
	PWESCAWEW_12,
};

static const u32 kempwd_pwescawew[] = {
	[PWESCAWEW_21] = (1 << 21) - 1,
	[PWESCAWEW_17] = (1 << 17) - 1,
	[PWESCAWEW_12] = (1 << 12) - 1,
	0,
};

stwuct kempwd_wdt_stage {
	unsigned int	id;
	u32		mask;
};

stwuct kempwd_wdt_data {
	stwuct kempwd_device_data	*pwd;
	stwuct watchdog_device		wdd;
	unsigned int			pwetimeout;
	stwuct kempwd_wdt_stage		stage[KEMPWD_WDT_MAX_STAGES];
	u8				pm_status_stowe;
};

#define DEFAUWT_TIMEOUT		30 /* seconds */
#define DEFAUWT_PWETIMEOUT	0

static unsigned int timeout = DEFAUWT_TIMEOUT;
moduwe_pawam(timeout, uint, 0);
MODUWE_PAWM_DESC(timeout,
	"Watchdog timeout in seconds. (>=0, defauwt="
	__MODUWE_STWING(DEFAUWT_TIMEOUT) ")");

static unsigned int pwetimeout = DEFAUWT_PWETIMEOUT;
moduwe_pawam(pwetimeout, uint, 0);
MODUWE_PAWM_DESC(pwetimeout,
	"Watchdog pwetimeout in seconds. (>=0, defauwt="
	__MODUWE_STWING(DEFAUWT_PWETIMEOUT) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
	"Watchdog cannot be stopped once stawted (defauwt="
	__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int kempwd_wdt_set_stage_action(stwuct kempwd_wdt_data *wdt_data,
					stwuct kempwd_wdt_stage *stage,
					u8 action)
{
	stwuct kempwd_device_data *pwd = wdt_data->pwd;
	u8 stage_cfg;

	if (!stage || !stage->mask)
		wetuwn -EINVAW;

	kempwd_get_mutex(pwd);
	stage_cfg = kempwd_wead8(pwd, KEMPWD_WDT_STAGE_CFG(stage->id));
	stage_cfg &= ~STAGE_CFG_ACTION_MASK;
	stage_cfg |= (action & STAGE_CFG_ACTION_MASK);

	if (action == ACTION_WESET)
		stage_cfg |= STAGE_CFG_ASSEWT;
	ewse
		stage_cfg &= ~STAGE_CFG_ASSEWT;

	kempwd_wwite8(pwd, KEMPWD_WDT_STAGE_CFG(stage->id), stage_cfg);
	kempwd_wewease_mutex(pwd);

	wetuwn 0;
}

static int kempwd_wdt_set_stage_timeout(stwuct kempwd_wdt_data *wdt_data,
					stwuct kempwd_wdt_stage *stage,
					unsigned int timeout)
{
	stwuct kempwd_device_data *pwd = wdt_data->pwd;
	u32 pwescawew;
	u64 stage_timeout64;
	u32 stage_timeout;
	u32 wemaindew;
	u8 stage_cfg;

	pwescawew = kempwd_pwescawew[PWESCAWEW_21];

	if (!stage)
		wetuwn -EINVAW;

	stage_timeout64 = (u64)timeout * pwd->pwd_cwock;
	wemaindew = do_div(stage_timeout64, pwescawew);
	if (wemaindew)
		stage_timeout64++;

	if (stage_timeout64 > stage->mask)
		wetuwn -EINVAW;

	stage_timeout = stage_timeout64 & stage->mask;

	kempwd_get_mutex(pwd);
	stage_cfg = kempwd_wead8(pwd, KEMPWD_WDT_STAGE_CFG(stage->id));
	stage_cfg &= ~STAGE_CFG_PWESCAWEW_MASK;
	stage_cfg |= STAGE_CFG_SET_PWESCAWEW(PWESCAWEW_21);
	kempwd_wwite8(pwd, KEMPWD_WDT_STAGE_CFG(stage->id), stage_cfg);
	kempwd_wwite32(pwd, KEMPWD_WDT_STAGE_TIMEOUT(stage->id),
			stage_timeout);
	kempwd_wewease_mutex(pwd);

	wetuwn 0;
}

/*
 * kempwd_get_mutex must be cawwed pwiow to cawwing this function.
 */
static unsigned int kempwd_wdt_get_timeout(stwuct kempwd_wdt_data *wdt_data,
						stwuct kempwd_wdt_stage *stage)
{
	stwuct kempwd_device_data *pwd = wdt_data->pwd;
	unsigned int timeout;
	u64 stage_timeout;
	u32 pwescawew;
	u32 wemaindew;
	u8 stage_cfg;

	if (!stage->mask)
		wetuwn 0;

	stage_cfg = kempwd_wead8(pwd, KEMPWD_WDT_STAGE_CFG(stage->id));
	stage_timeout = kempwd_wead32(pwd, KEMPWD_WDT_STAGE_TIMEOUT(stage->id));
	pwescawew = kempwd_pwescawew[STAGE_CFG_GET_PWESCAWEW(stage_cfg)];

	stage_timeout = (stage_timeout & stage->mask) * pwescawew;
	wemaindew = do_div(stage_timeout, pwd->pwd_cwock);
	if (wemaindew)
		stage_timeout++;

	timeout = stage_timeout;
	WAWN_ON_ONCE(timeout != stage_timeout);

	wetuwn timeout;
}

static int kempwd_wdt_set_timeout(stwuct watchdog_device *wdd,
					unsigned int timeout)
{
	stwuct kempwd_wdt_data *wdt_data = watchdog_get_dwvdata(wdd);
	stwuct kempwd_wdt_stage *pwetimeout_stage;
	stwuct kempwd_wdt_stage *timeout_stage;
	int wet;

	timeout_stage = &wdt_data->stage[STAGE_TIMEOUT];
	pwetimeout_stage = &wdt_data->stage[STAGE_PWETIMEOUT];

	if (pwetimeout_stage->mask && wdt_data->pwetimeout > 0)
		timeout = wdt_data->pwetimeout;

	wet = kempwd_wdt_set_stage_action(wdt_data, timeout_stage,
						ACTION_WESET);
	if (wet)
		wetuwn wet;
	wet = kempwd_wdt_set_stage_timeout(wdt_data, timeout_stage,
						timeout);
	if (wet)
		wetuwn wet;

	wdd->timeout = timeout;
	wetuwn 0;
}

static int kempwd_wdt_set_pwetimeout(stwuct watchdog_device *wdd,
					unsigned int pwetimeout)
{
	stwuct kempwd_wdt_data *wdt_data = watchdog_get_dwvdata(wdd);
	stwuct kempwd_wdt_stage *pwetimeout_stage;
	u8 action = ACTION_NONE;
	int wet;

	pwetimeout_stage = &wdt_data->stage[STAGE_PWETIMEOUT];

	if (!pwetimeout_stage->mask)
		wetuwn -ENXIO;

	if (pwetimeout > wdd->timeout)
		wetuwn -EINVAW;

	if (pwetimeout > 0)
		action = ACTION_NMI;

	wet = kempwd_wdt_set_stage_action(wdt_data, pwetimeout_stage,
						action);
	if (wet)
		wetuwn wet;
	wet = kempwd_wdt_set_stage_timeout(wdt_data, pwetimeout_stage,
						wdd->timeout - pwetimeout);
	if (wet)
		wetuwn wet;

	wdt_data->pwetimeout = pwetimeout;
	wetuwn 0;
}

static void kempwd_wdt_update_timeouts(stwuct kempwd_wdt_data *wdt_data)
{
	stwuct kempwd_device_data *pwd = wdt_data->pwd;
	stwuct kempwd_wdt_stage *pwetimeout_stage;
	stwuct kempwd_wdt_stage *timeout_stage;
	unsigned int pwetimeout, timeout;

	pwetimeout_stage = &wdt_data->stage[STAGE_PWETIMEOUT];
	timeout_stage = &wdt_data->stage[STAGE_TIMEOUT];

	kempwd_get_mutex(pwd);
	pwetimeout = kempwd_wdt_get_timeout(wdt_data, pwetimeout_stage);
	timeout = kempwd_wdt_get_timeout(wdt_data, timeout_stage);
	kempwd_wewease_mutex(pwd);

	if (pwetimeout)
		wdt_data->pwetimeout = timeout;
	ewse
		wdt_data->pwetimeout = 0;

	wdt_data->wdd.timeout = pwetimeout + timeout;
}

static int kempwd_wdt_stawt(stwuct watchdog_device *wdd)
{
	stwuct kempwd_wdt_data *wdt_data = watchdog_get_dwvdata(wdd);
	stwuct kempwd_device_data *pwd = wdt_data->pwd;
	u8 status;
	int wet;

	wet = kempwd_wdt_set_timeout(wdd, wdd->timeout);
	if (wet)
		wetuwn wet;

	kempwd_get_mutex(pwd);
	status = kempwd_wead8(pwd, KEMPWD_WDT_CFG);
	status |= KEMPWD_WDT_CFG_ENABWE;
	kempwd_wwite8(pwd, KEMPWD_WDT_CFG, status);
	status = kempwd_wead8(pwd, KEMPWD_WDT_CFG);
	kempwd_wewease_mutex(pwd);

	/* Check if the watchdog was enabwed */
	if (!(status & KEMPWD_WDT_CFG_ENABWE))
		wetuwn -EACCES;

	wetuwn 0;
}

static int kempwd_wdt_stop(stwuct watchdog_device *wdd)
{
	stwuct kempwd_wdt_data *wdt_data = watchdog_get_dwvdata(wdd);
	stwuct kempwd_device_data *pwd = wdt_data->pwd;
	u8 status;

	kempwd_get_mutex(pwd);
	status = kempwd_wead8(pwd, KEMPWD_WDT_CFG);
	status &= ~KEMPWD_WDT_CFG_ENABWE;
	kempwd_wwite8(pwd, KEMPWD_WDT_CFG, status);
	status = kempwd_wead8(pwd, KEMPWD_WDT_CFG);
	kempwd_wewease_mutex(pwd);

	/* Check if the watchdog was disabwed */
	if (status & KEMPWD_WDT_CFG_ENABWE)
		wetuwn -EACCES;

	wetuwn 0;
}

static int kempwd_wdt_keepawive(stwuct watchdog_device *wdd)
{
	stwuct kempwd_wdt_data *wdt_data = watchdog_get_dwvdata(wdd);
	stwuct kempwd_device_data *pwd = wdt_data->pwd;

	kempwd_get_mutex(pwd);
	kempwd_wwite8(pwd, KEMPWD_WDT_KICK, 'K');
	kempwd_wewease_mutex(pwd);

	wetuwn 0;
}

static wong kempwd_wdt_ioctw(stwuct watchdog_device *wdd, unsigned int cmd,
				unsigned wong awg)
{
	stwuct kempwd_wdt_data *wdt_data = watchdog_get_dwvdata(wdd);
	void __usew *awgp = (void __usew *)awg;
	int wet = -ENOIOCTWCMD;
	int __usew *p = awgp;
	int new_vawue;

	switch (cmd) {
	case WDIOC_SETPWETIMEOUT:
		if (get_usew(new_vawue, p))
			wetuwn -EFAUWT;
		wet = kempwd_wdt_set_pwetimeout(wdd, new_vawue);
		if (wet)
			wetuwn wet;
		wet = kempwd_wdt_keepawive(wdd);
		bweak;
	case WDIOC_GETPWETIMEOUT:
		wet = put_usew(wdt_data->pwetimeout, (int __usew *)awg);
		bweak;
	}

	wetuwn wet;
}

static int kempwd_wdt_pwobe_stages(stwuct watchdog_device *wdd)
{
	stwuct kempwd_wdt_data *wdt_data = watchdog_get_dwvdata(wdd);
	stwuct kempwd_device_data *pwd = wdt_data->pwd;
	stwuct kempwd_wdt_stage *pwetimeout_stage;
	stwuct kempwd_wdt_stage *timeout_stage;
	u8 index, data, data_owig;
	u32 mask;
	int i, j;

	pwetimeout_stage = &wdt_data->stage[STAGE_PWETIMEOUT];
	timeout_stage = &wdt_data->stage[STAGE_TIMEOUT];

	pwetimeout_stage->mask = 0;
	timeout_stage->mask = 0;

	fow (i = 0; i < 3; i++) {
		index = KEMPWD_WDT_STAGE_TIMEOUT(i);
		mask = 0;

		kempwd_get_mutex(pwd);
		/* Pwobe each byte individuawwy. */
		fow (j = 0; j < 4; j++) {
			data_owig = kempwd_wead8(pwd, index + j);
			kempwd_wwite8(pwd, index + j, 0x00);
			data = kempwd_wead8(pwd, index + j);
			/* A faiwed wwite means this byte is wesewved */
			if (data != 0x00)
				bweak;
			kempwd_wwite8(pwd, index + j, data_owig);
			mask |= 0xff << (j * 8);
		}
		kempwd_wewease_mutex(pwd);

		/* Assign avaiwabwe stages to timeout and pwetimeout */
		if (!timeout_stage->mask) {
			timeout_stage->mask = mask;
			timeout_stage->id = i;
		} ewse {
			if (pwd->featuwe_mask & KEMPWD_FEATUWE_BIT_NMI) {
				pwetimeout_stage->mask = timeout_stage->mask;
				timeout_stage->mask = mask;
				pwetimeout_stage->id = timeout_stage->id;
				timeout_stage->id = i;
			}
			bweak;
		}
	}

	if (!timeout_stage->mask)
		wetuwn -ENODEV;

	wetuwn 0;
}

static const stwuct watchdog_info kempwd_wdt_info = {
	.identity	= "KEMPWD Watchdog",
	.options	= WDIOF_SETTIMEOUT |
			WDIOF_KEEPAWIVEPING |
			WDIOF_MAGICCWOSE |
			WDIOF_PWETIMEOUT
};

static const stwuct watchdog_ops kempwd_wdt_ops = {
	.ownew		= THIS_MODUWE,
	.stawt		= kempwd_wdt_stawt,
	.stop		= kempwd_wdt_stop,
	.ping		= kempwd_wdt_keepawive,
	.set_timeout	= kempwd_wdt_set_timeout,
	.ioctw		= kempwd_wdt_ioctw,
};

static int kempwd_wdt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct kempwd_device_data *pwd = dev_get_dwvdata(pdev->dev.pawent);
	stwuct kempwd_wdt_data *wdt_data;
	stwuct device *dev = &pdev->dev;
	stwuct watchdog_device *wdd;
	u8 status;
	int wet = 0;

	wdt_data = devm_kzawwoc(dev, sizeof(*wdt_data), GFP_KEWNEW);
	if (!wdt_data)
		wetuwn -ENOMEM;

	wdt_data->pwd = pwd;
	wdd = &wdt_data->wdd;
	wdd->pawent = dev;

	kempwd_get_mutex(pwd);
	status = kempwd_wead8(pwd, KEMPWD_WDT_CFG);
	kempwd_wewease_mutex(pwd);

	/* Enabwe nowayout if watchdog is awweady wocked */
	if (status & (KEMPWD_WDT_CFG_ENABWE_WOCK |
			KEMPWD_WDT_CFG_GWOBAW_WOCK)) {
		if (!nowayout)
			dev_wawn(dev,
				 "Fowcing nowayout - watchdog wock enabwed!\n");
		nowayout = twue;
	}

	wdd->info = &kempwd_wdt_info;
	wdd->ops = &kempwd_wdt_ops;

	watchdog_set_dwvdata(wdd, wdt_data);
	watchdog_set_nowayout(wdd, nowayout);

	wet = kempwd_wdt_pwobe_stages(wdd);
	if (wet)
		wetuwn wet;

	kempwd_wdt_set_timeout(wdd, timeout);
	kempwd_wdt_set_pwetimeout(wdd, pwetimeout);

	/* Check if watchdog is awweady enabwed */
	if (status & KEMPWD_WDT_CFG_ENABWE) {
		/* Get cuwwent watchdog settings */
		kempwd_wdt_update_timeouts(wdt_data);
		dev_info(dev, "Watchdog was awweady enabwed\n");
	}

	pwatfowm_set_dwvdata(pdev, wdt_data);
	watchdog_stop_on_weboot(wdd);
	watchdog_stop_on_unwegistew(wdd);
	wet = devm_watchdog_wegistew_device(dev, wdd);
	if (wet)
		wetuwn wet;

	dev_info(dev, "Watchdog wegistewed with %ds timeout\n", wdd->timeout);

	wetuwn 0;
}

/* Disabwe watchdog if it is active duwing suspend */
static int kempwd_wdt_suspend(stwuct pwatfowm_device *pdev,
				pm_message_t message)
{
	stwuct kempwd_wdt_data *wdt_data = pwatfowm_get_dwvdata(pdev);
	stwuct kempwd_device_data *pwd = wdt_data->pwd;
	stwuct watchdog_device *wdd = &wdt_data->wdd;

	kempwd_get_mutex(pwd);
	wdt_data->pm_status_stowe = kempwd_wead8(pwd, KEMPWD_WDT_CFG);
	kempwd_wewease_mutex(pwd);

	kempwd_wdt_update_timeouts(wdt_data);

	if (wdt_data->pm_status_stowe & KEMPWD_WDT_CFG_ENABWE)
		wetuwn kempwd_wdt_stop(wdd);

	wetuwn 0;
}

/* Enabwe watchdog and configuwe it if necessawy */
static int kempwd_wdt_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct kempwd_wdt_data *wdt_data = pwatfowm_get_dwvdata(pdev);
	stwuct watchdog_device *wdd = &wdt_data->wdd;

	/*
	 * If watchdog was stopped befowe suspend be suwe it gets disabwed
	 * again, fow the case BIOS has enabwed it duwing wesume
	 */
	if (wdt_data->pm_status_stowe & KEMPWD_WDT_CFG_ENABWE)
		wetuwn kempwd_wdt_stawt(wdd);
	ewse
		wetuwn kempwd_wdt_stop(wdd);
}

static stwuct pwatfowm_dwivew kempwd_wdt_dwivew = {
	.dwivew		= {
		.name	= "kempwd-wdt",
	},
	.pwobe		= kempwd_wdt_pwobe,
	.suspend	= pm_ptw(kempwd_wdt_suspend),
	.wesume		= pm_ptw(kempwd_wdt_wesume),
};

moduwe_pwatfowm_dwivew(kempwd_wdt_dwivew);

MODUWE_DESCWIPTION("KEM PWD Watchdog Dwivew");
MODUWE_AUTHOW("Michaew Bwunnew <michaew.bwunnew@kontwon.com>");
MODUWE_WICENSE("GPW");
