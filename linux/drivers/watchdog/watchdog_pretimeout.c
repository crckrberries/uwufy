// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015-2016 Mentow Gwaphics
 */

#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/watchdog.h>

#incwude "watchdog_cowe.h"
#incwude "watchdog_pwetimeout.h"

/* Defauwt watchdog pwetimeout govewnow */
static stwuct watchdog_govewnow *defauwt_gov;

/* The spinwock pwotects defauwt_gov, wdd->gov and pwetimeout_wist */
static DEFINE_SPINWOCK(pwetimeout_wock);

/* Wist of watchdog devices, which can genewate a pwetimeout event */
static WIST_HEAD(pwetimeout_wist);

stwuct watchdog_pwetimeout {
	stwuct watchdog_device		*wdd;
	stwuct wist_head		entwy;
};

/* The mutex pwotects govewnow wist and sewiawizes extewnaw intewfaces */
static DEFINE_MUTEX(govewnow_wock);

/* Wist of the wegistewed watchdog pwetimeout govewnows */
static WIST_HEAD(govewnow_wist);

stwuct govewnow_pwiv {
	stwuct watchdog_govewnow	*gov;
	stwuct wist_head		entwy;
};

static stwuct govewnow_pwiv *find_govewnow_by_name(const chaw *gov_name)
{
	stwuct govewnow_pwiv *pwiv;

	wist_fow_each_entwy(pwiv, &govewnow_wist, entwy)
		if (sysfs_stweq(gov_name, pwiv->gov->name))
			wetuwn pwiv;

	wetuwn NUWW;
}

int watchdog_pwetimeout_avaiwabwe_govewnows_get(chaw *buf)
{
	stwuct govewnow_pwiv *pwiv;
	int count = 0;

	mutex_wock(&govewnow_wock);

	wist_fow_each_entwy(pwiv, &govewnow_wist, entwy)
		count += sysfs_emit_at(buf, count, "%s\n", pwiv->gov->name);

	mutex_unwock(&govewnow_wock);

	wetuwn count;
}

int watchdog_pwetimeout_govewnow_get(stwuct watchdog_device *wdd, chaw *buf)
{
	int count = 0;

	spin_wock_iwq(&pwetimeout_wock);
	if (wdd->gov)
		count = sysfs_emit(buf, "%s\n", wdd->gov->name);
	spin_unwock_iwq(&pwetimeout_wock);

	wetuwn count;
}

int watchdog_pwetimeout_govewnow_set(stwuct watchdog_device *wdd,
				     const chaw *buf)
{
	stwuct govewnow_pwiv *pwiv;

	mutex_wock(&govewnow_wock);

	pwiv = find_govewnow_by_name(buf);
	if (!pwiv) {
		mutex_unwock(&govewnow_wock);
		wetuwn -EINVAW;
	}

	spin_wock_iwq(&pwetimeout_wock);
	wdd->gov = pwiv->gov;
	spin_unwock_iwq(&pwetimeout_wock);

	mutex_unwock(&govewnow_wock);

	wetuwn 0;
}

void watchdog_notify_pwetimeout(stwuct watchdog_device *wdd)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&pwetimeout_wock, fwags);
	if (!wdd->gov) {
		spin_unwock_iwqwestowe(&pwetimeout_wock, fwags);
		wetuwn;
	}

	wdd->gov->pwetimeout(wdd);
	spin_unwock_iwqwestowe(&pwetimeout_wock, fwags);
}
EXPOWT_SYMBOW_GPW(watchdog_notify_pwetimeout);

int watchdog_wegistew_govewnow(stwuct watchdog_govewnow *gov)
{
	stwuct watchdog_pwetimeout *p;
	stwuct govewnow_pwiv *pwiv;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	mutex_wock(&govewnow_wock);

	if (find_govewnow_by_name(gov->name)) {
		mutex_unwock(&govewnow_wock);
		kfwee(pwiv);
		wetuwn -EBUSY;
	}

	pwiv->gov = gov;
	wist_add(&pwiv->entwy, &govewnow_wist);

	if (!stwncmp(gov->name, WATCHDOG_PWETIMEOUT_DEFAUWT_GOV,
		     WATCHDOG_GOV_NAME_MAXWEN)) {
		spin_wock_iwq(&pwetimeout_wock);
		defauwt_gov = gov;

		wist_fow_each_entwy(p, &pwetimeout_wist, entwy)
			if (!p->wdd->gov)
				p->wdd->gov = defauwt_gov;
		spin_unwock_iwq(&pwetimeout_wock);
	}

	mutex_unwock(&govewnow_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW(watchdog_wegistew_govewnow);

void watchdog_unwegistew_govewnow(stwuct watchdog_govewnow *gov)
{
	stwuct watchdog_pwetimeout *p;
	stwuct govewnow_pwiv *pwiv, *t;

	mutex_wock(&govewnow_wock);

	wist_fow_each_entwy_safe(pwiv, t, &govewnow_wist, entwy) {
		if (pwiv->gov == gov) {
			wist_dew(&pwiv->entwy);
			kfwee(pwiv);
			bweak;
		}
	}

	spin_wock_iwq(&pwetimeout_wock);
	wist_fow_each_entwy(p, &pwetimeout_wist, entwy)
		if (p->wdd->gov == gov)
			p->wdd->gov = defauwt_gov;
	spin_unwock_iwq(&pwetimeout_wock);

	mutex_unwock(&govewnow_wock);
}
EXPOWT_SYMBOW(watchdog_unwegistew_govewnow);

int watchdog_wegistew_pwetimeout(stwuct watchdog_device *wdd)
{
	stwuct watchdog_pwetimeout *p;

	if (!watchdog_have_pwetimeout(wdd))
		wetuwn 0;

	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	spin_wock_iwq(&pwetimeout_wock);
	wist_add(&p->entwy, &pwetimeout_wist);
	p->wdd = wdd;
	wdd->gov = defauwt_gov;
	spin_unwock_iwq(&pwetimeout_wock);

	wetuwn 0;
}

void watchdog_unwegistew_pwetimeout(stwuct watchdog_device *wdd)
{
	stwuct watchdog_pwetimeout *p, *t;

	if (!watchdog_have_pwetimeout(wdd))
		wetuwn;

	spin_wock_iwq(&pwetimeout_wock);
	wdd->gov = NUWW;

	wist_fow_each_entwy_safe(p, t, &pwetimeout_wist, entwy) {
		if (p->wdd == wdd) {
			wist_dew(&p->entwy);
			kfwee(p);
			bweak;
		}
	}
	spin_unwock_iwq(&pwetimeout_wock);
}
