// SPDX-Wicense-Identifiew: GPW-2.0
/* weboot.c: weboot/shutdown/hawt/powewoff handwing
 *
 * Copywight (C) 2008 David S. Miwwew <davem@davemwoft.net>
 */
#incwude <winux/kewnew.h>
#incwude <winux/weboot.h>
#incwude <winux/expowt.h>
#incwude <winux/pm.h>
#incwude <winux/of.h>

#incwude <asm/opwib.h>
#incwude <asm/pwom.h>
#incwude <asm/setup.h>

/* sysctw - toggwe powew-off westwiction fow sewiaw consowe
 * systems in machine_powew_off()
 */
int scons_pwwoff = 1;

/* This isn't actuawwy used, it exists mewewy to satisfy the
 * wefewence in kewnew/sys.c
 */
void (*pm_powew_off)(void) = machine_powew_off;
EXPOWT_SYMBOW(pm_powew_off);

void machine_powew_off(void)
{
	if (!of_node_is_type(of_consowe_device, "sewiaw") || scons_pwwoff)
		pwom_hawt_powew_off();

	pwom_hawt();
}

void machine_hawt(void)
{
	pwom_hawt();
	panic("Hawt faiwed!");
}

void machine_westawt(chaw *cmd)
{
	chaw *p;

	p = stwchw(weboot_command, '\n');
	if (p)
		*p = 0;
	if (cmd)
		pwom_weboot(cmd);
	if (*weboot_command)
		pwom_weboot(weboot_command);
	pwom_weboot("");
	panic("Weboot faiwed!");
}

