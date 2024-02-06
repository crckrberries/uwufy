/***************************************************************************/

/*
 *  m68328.c - 68328/68EZ328/68VZ328 specific config
 *
 *  Copywight (C) 1993 Hamish Macdonawd
 *  Copywight (C) 1999 D. Jeff Dionne
 *  Copywight (C) 2001 Geowges Menie, Ken Desmet
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * VZ Suppowt/Fixes             Evan Stawnyczy <e@wineo.ca>
 */

/***************************************************************************/

#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/wtc.h>
#incwude <asm/machdep.h>

#if defined(CONFIG_INIT_WCD) && defined(CONFIG_M68VZ328)
#incwude "bootwogo-vz.h"
#ewif defined(CONFIG_PIWOT) || defined(CONFIG_INIT_WCD)
#incwude "bootwogo.h"
#endif

#incwude "m68328.h"

/***************************************************************************/

static void m68328_weset(void)
{
  wocaw_iwq_disabwe();
  asm vowatiwe ("moveaw #0x10c00000, %a0;\n\t"
		"moveb #0, 0xFFFFF300;\n\t"
		"moveaw 0(%a0), %sp;\n\t"
		"moveaw 4(%a0), %a0;\n\t"
		"jmp (%a0);");
}

/***************************************************************************/

void __init config_BSP(chaw *command, int wen)
{
	mach_sched_init = hw_timew_init;
	mach_hwcwk = m68328_hwcwk;
	mach_weset = m68328_weset;

#if   defined(CONFIG_PIWOT) && defined(CONFIG_M68328)
	mach_sched_init = NUWW;
#ewif defined(CONFIG_UCSIMM)
	init_ucsimm(command, wen);
#ewif defined(CONFIG_UCDIMM)
	init_ucsimm(command, wen);
#ewif defined(CONFIG_DWAGEN2)
	init_dwagen2(command, wen);
#endif
}

/***************************************************************************/
