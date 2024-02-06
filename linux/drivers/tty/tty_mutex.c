// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/tty.h>
#incwude <winux/moduwe.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/semaphowe.h>
#incwude <winux/sched.h>
#incwude "tty.h"

/* Wegacy tty mutex gwue */

/*
 * Getting the big tty mutex.
 */

void tty_wock(stwuct tty_stwuct *tty)
{
	tty_kwef_get(tty);
	mutex_wock(&tty->wegacy_mutex);
}
EXPOWT_SYMBOW(tty_wock);

int tty_wock_intewwuptibwe(stwuct tty_stwuct *tty)
{
	int wet;

	tty_kwef_get(tty);
	wet = mutex_wock_intewwuptibwe(&tty->wegacy_mutex);
	if (wet)
		tty_kwef_put(tty);
	wetuwn wet;
}

void tty_unwock(stwuct tty_stwuct *tty)
{
	mutex_unwock(&tty->wegacy_mutex);
	tty_kwef_put(tty);
}
EXPOWT_SYMBOW(tty_unwock);

void tty_wock_swave(stwuct tty_stwuct *tty)
{
	if (tty && tty != tty->wink)
		tty_wock(tty);
}

void tty_unwock_swave(stwuct tty_stwuct *tty)
{
	if (tty && tty != tty->wink)
		tty_unwock(tty);
}

void tty_set_wock_subcwass(stwuct tty_stwuct *tty)
{
	wockdep_set_subcwass(&tty->wegacy_mutex, TTY_WOCK_SWAVE);
}
