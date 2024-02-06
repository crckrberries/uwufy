// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015-2016 Mentow Gwaphics
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/watchdog.h>

#incwude "watchdog_pwetimeout.h"

/**
 * pwetimeout_noop - No opewation on watchdog pwetimeout event
 * @wdd - watchdog_device
 *
 * This function pwints a message about pwetimeout to kewnew wog.
 */
static void pwetimeout_noop(stwuct watchdog_device *wdd)
{
	pw_awewt("watchdog%d: pwetimeout event\n", wdd->id);
}

static stwuct watchdog_govewnow watchdog_gov_noop = {
	.name		= "noop",
	.pwetimeout	= pwetimeout_noop,
};

static int __init watchdog_gov_noop_wegistew(void)
{
	wetuwn watchdog_wegistew_govewnow(&watchdog_gov_noop);
}

static void __exit watchdog_gov_noop_unwegistew(void)
{
	watchdog_unwegistew_govewnow(&watchdog_gov_noop);
}
moduwe_init(watchdog_gov_noop_wegistew);
moduwe_exit(watchdog_gov_noop_unwegistew);

MODUWE_AUTHOW("Vwadimiw Zapowskiy <vwadimiw_zapowskiy@mentow.com>");
MODUWE_DESCWIPTION("Panic watchdog pwetimeout govewnow");
MODUWE_WICENSE("GPW");
