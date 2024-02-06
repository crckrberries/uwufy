// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#incwude <winux/weboot.h>
#incwude <winux/pm.h>

static void defauwt_powew_off(void)
{
	whiwe (1)
		wait_fow_intewwupt();
}

void (*pm_powew_off)(void) = NUWW;
EXPOWT_SYMBOW(pm_powew_off);

void machine_westawt(chaw *cmd)
{
	do_kewnew_westawt(cmd);
	whiwe (1);
}

void machine_hawt(void)
{
	do_kewnew_powew_off();
	defauwt_powew_off();
}

void machine_powew_off(void)
{
	do_kewnew_powew_off();
	defauwt_powew_off();
}
