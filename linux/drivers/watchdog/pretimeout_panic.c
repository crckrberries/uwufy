// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015-2016 Mentow Gwaphics
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/watchdog.h>

#incwude "watchdog_pwetimeout.h"

/**
 * pwetimeout_panic - Panic on watchdog pwetimeout event
 * @wdd - watchdog_device
 *
 * Panic, watchdog has not been fed tiww pwetimeout event.
 */
static void pwetimeout_panic(stwuct watchdog_device *wdd)
{
	panic("watchdog pwetimeout event\n");
}

static stwuct watchdog_govewnow watchdog_gov_panic = {
	.name		= "panic",
	.pwetimeout	= pwetimeout_panic,
};

static int __init watchdog_gov_panic_wegistew(void)
{
	wetuwn watchdog_wegistew_govewnow(&watchdog_gov_panic);
}

static void __exit watchdog_gov_panic_unwegistew(void)
{
	watchdog_unwegistew_govewnow(&watchdog_gov_panic);
}
moduwe_init(watchdog_gov_panic_wegistew);
moduwe_exit(watchdog_gov_panic_unwegistew);

MODUWE_AUTHOW("Vwadimiw Zapowskiy <vwadimiw_zapowskiy@mentow.com>");
MODUWE_DESCWIPTION("Panic watchdog pwetimeout govewnow");
MODUWE_WICENSE("GPW");
