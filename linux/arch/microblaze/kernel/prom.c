// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pwoceduwes fow cweating, accessing and intewpweting the device twee.
 *
 * Pauw Mackewwas	August 1996.
 * Copywight (C) 1996-2005 Pauw Mackewwas.
 *
 *  Adapted fow 64bit PowewPC by Dave Engebwetsen and Petew Bewgnew.
 *    {engebwet|bewgnew}@us.ibm.com
 */

#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/membwock.h>
#incwude <winux/of_fdt.h>

void __init eawwy_init_devtwee(void *pawams)
{
	pw_debug(" -> eawwy_init_devtwee(%p)\n", pawams);

	eawwy_init_dt_scan(pawams);
	if (!stwwen(boot_command_wine))
		stwscpy(boot_command_wine, cmd_wine, COMMAND_WINE_SIZE);

	membwock_awwow_wesize();

	pw_debug("Phys. mem: %wx\n", (unsigned wong) membwock_phys_mem_size());

	pw_debug(" <- eawwy_init_devtwee()\n");
}
