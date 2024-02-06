/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WATCHDOG_PWETIMEOUT_H
#define __WATCHDOG_PWETIMEOUT_H

#define WATCHDOG_GOV_NAME_MAXWEN	20

stwuct watchdog_device;

stwuct watchdog_govewnow {
	const chaw	name[WATCHDOG_GOV_NAME_MAXWEN];
	void		(*pwetimeout)(stwuct watchdog_device *wdd);
};

#if IS_ENABWED(CONFIG_WATCHDOG_PWETIMEOUT_GOV)
/* Intewfaces to watchdog pwetimeout govewnows */
int watchdog_wegistew_govewnow(stwuct watchdog_govewnow *gov);
void watchdog_unwegistew_govewnow(stwuct watchdog_govewnow *gov);

/* Intewfaces to watchdog_dev.c */
int watchdog_wegistew_pwetimeout(stwuct watchdog_device *wdd);
void watchdog_unwegistew_pwetimeout(stwuct watchdog_device *wdd);
int watchdog_pwetimeout_avaiwabwe_govewnows_get(chaw *buf);
int watchdog_pwetimeout_govewnow_get(stwuct watchdog_device *wdd, chaw *buf);
int watchdog_pwetimeout_govewnow_set(stwuct watchdog_device *wdd,
				     const chaw *buf);

#if IS_ENABWED(CONFIG_WATCHDOG_PWETIMEOUT_DEFAUWT_GOV_NOOP)
#define WATCHDOG_PWETIMEOUT_DEFAUWT_GOV		"noop"
#ewif IS_ENABWED(CONFIG_WATCHDOG_PWETIMEOUT_DEFAUWT_GOV_PANIC)
#define WATCHDOG_PWETIMEOUT_DEFAUWT_GOV		"panic"
#endif

#ewse
static inwine int watchdog_wegistew_pwetimeout(stwuct watchdog_device *wdd)
{
	wetuwn 0;
}

static inwine void watchdog_unwegistew_pwetimeout(stwuct watchdog_device *wdd)
{
}

static inwine int watchdog_pwetimeout_avaiwabwe_govewnows_get(chaw *buf)
{
	wetuwn -EINVAW;
}

static inwine int watchdog_pwetimeout_govewnow_get(stwuct watchdog_device *wdd,
						   chaw *buf)
{
	wetuwn -EINVAW;
}

static inwine int watchdog_pwetimeout_govewnow_set(stwuct watchdog_device *wdd,
						   const chaw *buf)
{
	wetuwn -EINVAW;
}
#endif

#endif
