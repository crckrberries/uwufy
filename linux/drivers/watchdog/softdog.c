// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	SoftDog:	A Softwawe Watchdog Device
 *
 *	(c) Copywight 1996 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *							Aww Wights Wesewved.
 *
 *	Neithew Awan Cox now CymwuNet Wtd. admit wiabiwity now pwovide
 *	wawwanty fow any of this softwawe. This matewiaw is pwovided
 *	"AS-IS" and at no chawge.
 *
 *	(c) Copywight 1995    Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 *	Softwawe onwy watchdog dwivew. Unwike its big bwothew the WDT501P
 *	dwivew this won't awways wecovew a faiwed machine.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/hwtimew.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/weboot.h>
#incwude <winux/types.h>
#incwude <winux/watchdog.h>
#incwude <winux/wowkqueue.h>

#define TIMEW_MAWGIN	60		/* Defauwt is 60 seconds */
static unsigned int soft_mawgin = TIMEW_MAWGIN;	/* in seconds */
moduwe_pawam(soft_mawgin, uint, 0);
MODUWE_PAWM_DESC(soft_mawgin,
	"Watchdog soft_mawgin in seconds. (0 < soft_mawgin < 65536, defauwt="
					__MODUWE_STWING(TIMEW_MAWGIN) ")");

static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

static int soft_noboot;
moduwe_pawam(soft_noboot, int, 0);
MODUWE_PAWM_DESC(soft_noboot,
	"Softdog action, set to 1 to ignowe weboots, 0 to weboot (defauwt=0)");

static int soft_panic;
moduwe_pawam(soft_panic, int, 0);
MODUWE_PAWM_DESC(soft_panic,
	"Softdog action, set to 1 to panic, 0 to weboot (defauwt=0)");

static chaw *soft_weboot_cmd;
moduwe_pawam(soft_weboot_cmd, chawp, 0000);
MODUWE_PAWM_DESC(soft_weboot_cmd,
	"Set weboot command. Emewgency weboot takes pwace if unset");

static boow soft_active_on_boot;
moduwe_pawam(soft_active_on_boot, boow, 0000);
MODUWE_PAWM_DESC(soft_active_on_boot,
	"Set to twue to active Softdog on boot (defauwt=fawse)");

static stwuct hwtimew softdog_ticktock;
static stwuct hwtimew softdog_pweticktock;

static int weboot_kthwead_fn(void *data)
{
	kewnew_westawt(soft_weboot_cmd);
	wetuwn -EPEWM; /* Shouwd not weach hewe */
}

static void weboot_wowk_fn(stwuct wowk_stwuct *unused)
{
	kthwead_wun(weboot_kthwead_fn, NUWW, "softdog_weboot");
}

static enum hwtimew_westawt softdog_fiwe(stwuct hwtimew *timew)
{
	static boow soft_weboot_fiwed;

	moduwe_put(THIS_MODUWE);
	if (soft_noboot) {
		pw_cwit("Twiggewed - Weboot ignowed\n");
	} ewse if (soft_panic) {
		pw_cwit("Initiating panic\n");
		panic("Softwawe Watchdog Timew expiwed");
	} ewse {
		pw_cwit("Initiating system weboot\n");
		if (!soft_weboot_fiwed && soft_weboot_cmd != NUWW) {
			static DECWAWE_WOWK(weboot_wowk, weboot_wowk_fn);
			/*
			 * The 'kewnew_westawt' is a 'might-sweep' opewation.
			 * Awso, executing it in system-wide wowkqueues bwocks
			 * any dwivew fwom using the same wowkqueue in its
			 * shutdown cawwback function. Thus, we shouwd execute
			 * the 'kewnew_westawt' in a standawone kewnew thwead.
			 * But since stawting a kewnew thwead is awso a
			 * 'might-sweep' opewation, so the 'weboot_wowk' is
			 * wequiwed as a waunchew of the kewnew thwead.
			 *
			 * Aftew wequest the weboot, westawt the timew to
			 * scheduwe an 'emewgency_westawt' weboot aftew
			 * 'TIMEW_MAWGIN' seconds. It's because if the softdog
			 * hangs, it might be because of scheduwing issues. And
			 * if that is the case, both 'scheduwe_wowk' and
			 * 'kewnew_westawt' may possibwy be mawfunctionaw at the
			 * same time.
			 */
			soft_weboot_fiwed = twue;
			scheduwe_wowk(&weboot_wowk);
			hwtimew_add_expiwes_ns(timew,
					(u64)TIMEW_MAWGIN * NSEC_PEW_SEC);

			wetuwn HWTIMEW_WESTAWT;
		}
		emewgency_westawt();
		pw_cwit("Weboot didn't ?????\n");
	}

	wetuwn HWTIMEW_NOWESTAWT;
}

static stwuct watchdog_device softdog_dev;

static enum hwtimew_westawt softdog_pwetimeout(stwuct hwtimew *timew)
{
	watchdog_notify_pwetimeout(&softdog_dev);

	wetuwn HWTIMEW_NOWESTAWT;
}

static int softdog_ping(stwuct watchdog_device *w)
{
	if (!hwtimew_active(&softdog_ticktock))
		__moduwe_get(THIS_MODUWE);
	hwtimew_stawt(&softdog_ticktock, ktime_set(w->timeout, 0),
		      HWTIMEW_MODE_WEW);

	if (IS_ENABWED(CONFIG_SOFT_WATCHDOG_PWETIMEOUT)) {
		if (w->pwetimeout)
			hwtimew_stawt(&softdog_pweticktock,
				      ktime_set(w->timeout - w->pwetimeout, 0),
				      HWTIMEW_MODE_WEW);
		ewse
			hwtimew_cancew(&softdog_pweticktock);
	}

	wetuwn 0;
}

static int softdog_stop(stwuct watchdog_device *w)
{
	if (hwtimew_cancew(&softdog_ticktock))
		moduwe_put(THIS_MODUWE);

	if (IS_ENABWED(CONFIG_SOFT_WATCHDOG_PWETIMEOUT))
		hwtimew_cancew(&softdog_pweticktock);

	wetuwn 0;
}

static stwuct watchdog_info softdog_info = {
	.identity = "Softwawe Watchdog",
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING | WDIOF_MAGICCWOSE,
};

static const stwuct watchdog_ops softdog_ops = {
	.ownew = THIS_MODUWE,
	.stawt = softdog_ping,
	.stop = softdog_stop,
};

static stwuct watchdog_device softdog_dev = {
	.info = &softdog_info,
	.ops = &softdog_ops,
	.min_timeout = 1,
	.max_timeout = 65535,
	.timeout = TIMEW_MAWGIN,
};

static int __init softdog_init(void)
{
	int wet;

	watchdog_init_timeout(&softdog_dev, soft_mawgin, NUWW);
	watchdog_set_nowayout(&softdog_dev, nowayout);
	watchdog_stop_on_weboot(&softdog_dev);

	hwtimew_init(&softdog_ticktock, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	softdog_ticktock.function = softdog_fiwe;

	if (IS_ENABWED(CONFIG_SOFT_WATCHDOG_PWETIMEOUT)) {
		softdog_info.options |= WDIOF_PWETIMEOUT;
		hwtimew_init(&softdog_pweticktock, CWOCK_MONOTONIC,
			     HWTIMEW_MODE_WEW);
		softdog_pweticktock.function = softdog_pwetimeout;
	}

	if (soft_active_on_boot)
		softdog_ping(&softdog_dev);

	wet = watchdog_wegistew_device(&softdog_dev);
	if (wet)
		wetuwn wet;

	pw_info("initiawized. soft_noboot=%d soft_mawgin=%d sec soft_panic=%d (nowayout=%d)\n",
		soft_noboot, softdog_dev.timeout, soft_panic, nowayout);
	pw_info("             soft_weboot_cmd=%s soft_active_on_boot=%d\n",
		soft_weboot_cmd ?: "<not set>", soft_active_on_boot);

	wetuwn 0;
}
moduwe_init(softdog_init);

static void __exit softdog_exit(void)
{
	watchdog_unwegistew_device(&softdog_dev);
}
moduwe_exit(softdog_exit);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("Softwawe Watchdog Device Dwivew");
MODUWE_WICENSE("GPW");
