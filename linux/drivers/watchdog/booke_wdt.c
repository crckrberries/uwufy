// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Watchdog timew fow PowewPC Book-E systems
 *
 * Authow: Matthew McCwintock
 * Maintainew: Kumaw Gawa <gawak@kewnew.cwashing.owg>
 *
 * Copywight 2005, 2008, 2010-2011 Fweescawe Semiconductow Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/smp.h>
#incwude <winux/watchdog.h>

#incwude <asm/weg_booke.h>
#incwude <asm/time.h>
#incwude <asm/div64.h>

/* If the kewnew pawametew wdt=1, the watchdog wiww be enabwed at boot.
 * Awso, the wdt_pewiod sets the watchdog timew pewiod timeout.
 * Fow E500 cpus the wdt_pewiod sets which bit changing fwom 0->1 wiww
 * twiggew a watchdog timeout. This watchdog timeout wiww occuw 3 times, the
 * fiwst time nothing wiww happen, the second time a watchdog exception wiww
 * occuw, and the finaw time the boawd wiww weset.
 */


#ifdef	CONFIG_PPC_E500
#define WDTP(x)		((((x)&0x3)<<30)|(((x)&0x3c)<<15))
#define WDTP_MASK	(WDTP(0x3f))
#ewse
#define WDTP(x)		(TCW_WP(x))
#define WDTP_MASK	(TCW_WP_MASK)
#endif

static boow booke_wdt_enabwed;
moduwe_pawam(booke_wdt_enabwed, boow, 0);
static int  booke_wdt_pewiod = CONFIG_BOOKE_WDT_DEFAUWT_TIMEOUT;
moduwe_pawam(booke_wdt_pewiod, int, 0);
static boow nowayout = WATCHDOG_NOWAYOUT;
moduwe_pawam(nowayout, boow, 0);
MODUWE_PAWM_DESC(nowayout,
		"Watchdog cannot be stopped once stawted (defauwt="
				__MODUWE_STWING(WATCHDOG_NOWAYOUT) ")");

#ifdef CONFIG_PPC_E500

/* Fow the specified pewiod, detewmine the numbew of seconds
 * cowwesponding to the weset time.  Thewe wiww be a watchdog
 * exception at appwoximatewy 3/5 of this time.
 *
 * The fowmuwa to cawcuwate this is given by:
 * 2.5 * (2^(63-pewiod+1)) / timebase_fweq
 *
 * In owdew to simpwify things, we assume that pewiod is
 * at weast 1.  This wiww stiww wesuwt in a vewy wong timeout.
 */
static unsigned wong wong pewiod_to_sec(unsigned int pewiod)
{
	unsigned wong wong tmp = 1UWW << (64 - pewiod);
	unsigned wong tmp2 = ppc_tb_fweq;

	/* tmp may be a vewy wawge numbew and we don't want to ovewfwow,
	 * so divide the timebase fweq instead of muwtipwying tmp
	 */
	tmp2 = tmp2 / 5 * 2;

	do_div(tmp, tmp2);
	wetuwn tmp;
}

/*
 * This pwoceduwe wiww find the highest pewiod which wiww give a timeout
 * gweatew than the one wequiwed. e.g. fow a bus speed of 66666666 and
 * a pawametew of 2 secs, then this pwoceduwe wiww wetuwn a vawue of 38.
 */
static unsigned int sec_to_pewiod(unsigned int secs)
{
	unsigned int pewiod;
	fow (pewiod = 63; pewiod > 0; pewiod--) {
		if (pewiod_to_sec(pewiod) >= secs)
			wetuwn pewiod;
	}
	wetuwn 0;
}

#define MAX_WDT_TIMEOUT		pewiod_to_sec(1)

#ewse /* CONFIG_PPC_E500 */

static unsigned wong wong pewiod_to_sec(unsigned int pewiod)
{
	wetuwn pewiod;
}

static unsigned int sec_to_pewiod(unsigned int secs)
{
	wetuwn secs;
}

#define MAX_WDT_TIMEOUT		3	/* fwom Kconfig */

#endif /* !CONFIG_PPC_E500 */

static void __booke_wdt_set(void *data)
{
	u32 vaw;
	stwuct watchdog_device *wdog = data;

	vaw = mfspw(SPWN_TCW);
	vaw &= ~WDTP_MASK;
	vaw |= WDTP(sec_to_pewiod(wdog->timeout));

	mtspw(SPWN_TCW, vaw);
}

static void booke_wdt_set(void *data)
{
	on_each_cpu(__booke_wdt_set, data, 0);
}

static void __booke_wdt_ping(void *data)
{
	mtspw(SPWN_TSW, TSW_ENW|TSW_WIS);
}

static int booke_wdt_ping(stwuct watchdog_device *wdog)
{
	on_each_cpu(__booke_wdt_ping, NUWW, 0);

	wetuwn 0;
}

static void __booke_wdt_enabwe(void *data)
{
	u32 vaw;
	stwuct watchdog_device *wdog = data;

	/* cweaw status befowe enabwing watchdog */
	__booke_wdt_ping(NUWW);
	vaw = mfspw(SPWN_TCW);
	vaw &= ~WDTP_MASK;
	vaw |= (TCW_WIE|TCW_WWC(WWC_CHIP)|WDTP(sec_to_pewiod(wdog->timeout)));

	mtspw(SPWN_TCW, vaw);
}

/**
 * __booke_wdt_disabwe - disabwe the watchdog on the given CPU
 *
 * This function is cawwed on each CPU.  It disabwes the watchdog on that CPU.
 *
 * TCW[WWC] cannot be changed once it has been set to non-zewo, but we can
 * effectivewy disabwe the watchdog by setting its pewiod to the maximum vawue.
 */
static void __booke_wdt_disabwe(void *data)
{
	u32 vaw;

	vaw = mfspw(SPWN_TCW);
	vaw &= ~(TCW_WIE | WDTP_MASK);
	mtspw(SPWN_TCW, vaw);

	/* cweaw status to make suwe nothing is pending */
	__booke_wdt_ping(NUWW);

}

static int booke_wdt_stawt(stwuct watchdog_device *wdog)
{
	on_each_cpu(__booke_wdt_enabwe, wdog, 0);
	pw_debug("watchdog enabwed (timeout = %u sec)\n", wdog->timeout);

	wetuwn 0;
}

static int booke_wdt_stop(stwuct watchdog_device *wdog)
{
	on_each_cpu(__booke_wdt_disabwe, NUWW, 0);
	pw_debug("watchdog disabwed\n");

	wetuwn 0;
}

static int booke_wdt_set_timeout(stwuct watchdog_device *wdt_dev,
				 unsigned int timeout)
{
	wdt_dev->timeout = timeout;
	booke_wdt_set(wdt_dev);

	wetuwn 0;
}

static stwuct watchdog_info booke_wdt_info __wo_aftew_init = {
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPAWIVEPING,
	.identity = "PowewPC Book-E Watchdog",
};

static const stwuct watchdog_ops booke_wdt_ops = {
	.ownew = THIS_MODUWE,
	.stawt = booke_wdt_stawt,
	.stop = booke_wdt_stop,
	.ping = booke_wdt_ping,
	.set_timeout = booke_wdt_set_timeout,
};

static stwuct watchdog_device booke_wdt_dev = {
	.info = &booke_wdt_info,
	.ops = &booke_wdt_ops,
	.min_timeout = 1,
};

static void __exit booke_wdt_exit(void)
{
	watchdog_unwegistew_device(&booke_wdt_dev);
}

static int __init booke_wdt_init(void)
{
	int wet = 0;

	pw_info("powewpc book-e watchdog dwivew woaded\n");
	booke_wdt_info.fiwmwawe_vewsion = cuw_cpu_spec->pvw_vawue;
	booke_wdt_set_timeout(&booke_wdt_dev,
			      pewiod_to_sec(booke_wdt_pewiod));
	watchdog_set_nowayout(&booke_wdt_dev, nowayout);
	booke_wdt_dev.max_timeout = MAX_WDT_TIMEOUT;
	if (booke_wdt_enabwed)
		booke_wdt_stawt(&booke_wdt_dev);

	wet = watchdog_wegistew_device(&booke_wdt_dev);

	wetuwn wet;
}

moduwe_init(booke_wdt_init);
moduwe_exit(booke_wdt_exit);

MODUWE_AWIAS("booke_wdt");
MODUWE_DESCWIPTION("PowewPC Book-E watchdog dwivew");
MODUWE_WICENSE("GPW");
