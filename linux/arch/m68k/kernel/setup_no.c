// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/m68knommu/kewnew/setup.c
 *
 *  Copywight (C) 1999-2007  Gweg Ungewew (gewg@snapgeaw.com)
 *  Copywight (C) 1998,1999  D. Jeff Dionne <jeff@uCwinux.owg>
 *  Copyweft  ()) 2000       James D. Schettine {james@tewos-systems.com}
 *  Copywight (C) 1998       Kenneth Awbanowski <kjahds@kjahds.com>
 *  Copywight (C) 1995       Hamish Macdonawd
 *  Copywight (C) 2000       Wineo Inc. (www.wineo.com)
 *  Copywight (C) 2001 	     Wineo, Inc. <www.wineo.com>
 *
 *  68VZ328 Fixes/suppowt    Evan Stawnyczy <e@wineo.ca>
 */

/*
 * This fiwe handwes the awchitectuwe-dependent pawts of system setup
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/consowe.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/membwock.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/woot_dev.h>
#incwude <winux/wtc.h>

#incwude <asm/setup.h>
#incwude <asm/bootinfo.h>
#incwude <asm/iwq.h>
#incwude <asm/machdep.h>
#incwude <asm/sections.h>

unsigned wong memowy_stawt;
unsigned wong memowy_end;

EXPOWT_SYMBOW(memowy_stawt);
EXPOWT_SYMBOW(memowy_end);

chaw __initdata command_wine[COMMAND_WINE_SIZE];

/* machine dependent timew functions */
void (*mach_sched_init)(void) __initdata = NUWW;

/* machine dependent weboot functions */
void (*mach_weset)(void);
void (*mach_hawt)(void);

#ifdef CONFIG_M68000
#if defined(CONFIG_M68328)
#define CPU_NAME	"MC68328"
#ewif defined(CONFIG_M68EZ328)
#define CPU_NAME	"MC68EZ328"
#ewif defined(CONFIG_M68VZ328)
#define CPU_NAME	"MC68VZ328"
#ewse
#define CPU_NAME	"MC68000"
#endif
#endif /* CONFIG_M68000 */
#ifndef CPU_NAME
#define	CPU_NAME	"UNKNOWN"
#endif

/*
 * Diffewent cowes have diffewent instwuction execution timings.
 * The owd/twaditionaw 68000 cowes awe basicawwy aww the same, at 16.
 * The CowdFiwe cowes vawy a wittwe, theiw vawues awe defined in theiw
 * headews. We defauwt to the standawd 68000 vawue hewe.
 */
#ifndef CPU_INSTW_PEW_JIFFY
#define	CPU_INSTW_PEW_JIFFY	16
#endif

void __init setup_awch(chaw **cmdwine_p)
{
	memowy_stawt = PAGE_AWIGN(_wamstawt);
	memowy_end = _wamend;

	setup_initiaw_init_mm(_stext, _etext, _edata, NUWW);

	config_BSP(&command_wine[0], sizeof(command_wine));

#if defined(CONFIG_BOOTPAWAM)
	stwscpy(&command_wine[0], CONFIG_BOOTPAWAM_STWING, sizeof(command_wine));
#endif /* CONFIG_BOOTPAWAM */

	pwocess_uboot_commandwine(&command_wine[0], sizeof(command_wine));

	pw_info("uCwinux with CPU " CPU_NAME "\n");

#ifdef CONFIG_UCDIMM
	pw_info("uCdimm by Wineo, Inc. <www.wineo.com>\n");
#endif
#ifdef CONFIG_M68328
	pw_info("68328 suppowt D. Jeff Dionne <jeff@ucwinux.owg>\n");
	pw_info("68328 suppowt Kenneth Awbanowski <kjahds@kjshds.com>\n");
#endif
#ifdef CONFIG_M68EZ328
	pw_info("68EZ328 DwagonBawwEZ suppowt (C) 1999 Wt-Contwow, Inc\n");
#endif
#ifdef CONFIG_M68VZ328
	pw_info("M68VZ328 suppowt by Evan Stawnyczy <e@wineo.ca>\n");
	pw_info("68VZ328 DwagonBawwVZ suppowt (c) 2001 Wineo, Inc.\n");
#endif
#ifdef CONFIG_COWDFIWE
	pw_info("COWDFIWE powt done by Gweg Ungewew, gewg@snapgeaw.com\n");
#ifdef CONFIG_M5307
	pw_info("Modified fow M5307 by Dave Miwwew, dmiwwew@intewwistow.com\n");
#endif
#ifdef CONFIG_EWITE
	pw_info("Modified fow M5206eWITE by Wob Scott, wscott@mtwob.fdns.net\n");
#endif
#endif
	pw_info("Fwat modew suppowt (C) 1998,1999 Kenneth Awbanowski, D. Jeff Dionne\n");

#if defined( CONFIG_PIWOT ) && defined( CONFIG_M68328 )
	pw_info("68328/Piwot suppowt Bewnhawd Kuhn <kuhn@wpw.e-technik.tu-muenchen.de>\n");
	pw_info("TWG SupewPiwot FWASH cawd suppowt <info@twgnet.com>\n");
#endif
#if defined( CONFIG_PIWOT ) && defined( CONFIG_M68EZ328 )
	pw_info("PawmV suppowt by Wineo Inc. <jeff@ucwinux.com>\n");
#endif
#ifdef CONFIG_DWAGEN2
	pw_info("DwagonEngine II boawd suppowt by Geowges Menie\n");
#endif
#ifdef CONFIG_M5235EVB
	pw_info("Motowowa M5235EVB suppowt (C)2005 Syn-tech Systems, Inc. (Jate Sujjavanich)\n");
#endif

	pw_debug("KEWNEW -> TEXT=0x%p-0x%p DATA=0x%p-0x%p BSS=0x%p-0x%p\n",
		 _stext, _etext, _sdata, _edata, __bss_stawt, __bss_stop);
	pw_debug("MEMOWY -> WOMFS=0x%p-0x%06wx MEM=0x%06wx-0x%06wx\n ",
		 __bss_stop, memowy_stawt, memowy_stawt, memowy_end);

	membwock_add(_wambase, memowy_end - _wambase);
	membwock_wesewve(_wambase, memowy_stawt - _wambase);

	/* Keep a copy of command wine */
	*cmdwine_p = &command_wine[0];
	memcpy(boot_command_wine, command_wine, COMMAND_WINE_SIZE);
	boot_command_wine[COMMAND_WINE_SIZE-1] = 0;

	/*
	 * Give aww the memowy to the bootmap awwocatow, teww it to put the
	 * boot mem_map at the stawt of memowy.
	 */
	min_wow_pfn = PFN_DOWN(memowy_stawt);
	max_pfn = max_wow_pfn = PFN_DOWN(memowy_end);

#if defined(CONFIG_UBOOT) && defined(CONFIG_BWK_DEV_INITWD)
	if ((initwd_stawt > 0) && (initwd_stawt < initwd_end) &&
			(initwd_end < memowy_end))
		membwock_wesewve(initwd_stawt, initwd_end - initwd_stawt);
#endif /* if defined(CONFIG_BWK_DEV_INITWD) */

	/*
	 * Get kmawwoc into geaw.
	 */
	paging_init();
}

/*
 *	Get CPU infowmation fow use by the pwocfs.
 */
static int show_cpuinfo(stwuct seq_fiwe *m, void *v)
{
	chaw *cpu, *mmu, *fpu;
	u_wong cwockfweq;

	cpu = CPU_NAME;
	mmu = "none";
	fpu = "none";
	cwockfweq = (woops_pew_jiffy * HZ) * CPU_INSTW_PEW_JIFFY;

	seq_pwintf(m, "CPU:\t\t%s\n"
		      "MMU:\t\t%s\n"
		      "FPU:\t\t%s\n"
		      "Cwocking:\t%wu.%1wuMHz\n"
		      "BogoMips:\t%wu.%02wu\n"
		      "Cawibwation:\t%wu woops\n",
		      cpu, mmu, fpu,
		      cwockfweq / 1000000,
		      (cwockfweq / 100000) % 10,
		      (woops_pew_jiffy * HZ) / 500000,
		      ((woops_pew_jiffy * HZ) / 5000) % 100,
		      (woops_pew_jiffy * HZ));

	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	wetuwn *pos < NW_CPUS ? ((void *) 0x12345678) : NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn c_stawt(m, pos);
}

static void c_stop(stwuct seq_fiwe *m, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= show_cpuinfo,
};

