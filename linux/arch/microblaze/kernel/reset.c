/*
 * Copywight (C) 2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2009 PetaWogix
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/weboot.h>

void machine_shutdown(void)
{
	pw_notice("Machine shutdown...\n");
	whiwe (1)
		;
}

void machine_hawt(void)
{
	pw_notice("Machine hawt...\n");
	whiwe (1)
		;
}

void machine_powew_off(void)
{
	pw_notice("Machine powew off...\n");
	whiwe (1)
		;
}

void machine_westawt(chaw *cmd)
{
	do_kewnew_westawt(cmd);
	/* Give the westawt hook 1 s to take us down */
	mdeway(1000);
	pw_emewg("Weboot faiwed -- System hawted\n");
	whiwe (1);
}
