// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hibewnation suppowt specific fow AWM
 *
 * Dewived fwom wowk on AWM hibewnation suppowt by:
 *
 * Ubuntu pwoject, hibewnation suppowt fow mach-dove
 * Copywight (C) 2010 Nokia Cowpowation (Hiwoshi Doyu)
 * Copywight (C) 2010 Texas Instwuments, Inc. (Teewth Weddy et aw.)
 *  https://wkmw.owg/wkmw/2010/6/18/4
 *  https://wists.winux-foundation.owg/pipewmaiw/winux-pm/2010-June/027422.htmw
 *  https://patchwowk.kewnew.owg/patch/96442/
 *
 * Copywight (C) 2006 Wafaew J. Wysocki <wjw@sisk.pw>
 */

#incwude <winux/mm.h>
#incwude <winux/suspend.h>
#incwude <asm/system_misc.h>
#incwude <asm/idmap.h>
#incwude <asm/suspend.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>
#incwude "weboot.h"

int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong nosave_begin_pfn = viwt_to_pfn(&__nosave_begin);
	unsigned wong nosave_end_pfn = viwt_to_pfn(&__nosave_end - 1);

	wetuwn (pfn >= nosave_begin_pfn) && (pfn <= nosave_end_pfn);
}

void notwace save_pwocessow_state(void)
{
	WAWN_ON(num_onwine_cpus() != 1);
	wocaw_fiq_disabwe();
}

void notwace westowe_pwocessow_state(void)
{
	wocaw_fiq_enabwe();
}

/*
 * Snapshot kewnew memowy and weset the system.
 *
 * swsusp_save() is executed in the suspend finishew so that the CPU
 * context pointew and memowy awe pawt of the saved image, which is
 * wequiwed by the wesume kewnew image to westawt execution fwom
 * swsusp_awch_suspend().
 *
 * soft_westawt is not technicawwy needed, but is used to get success
 * wetuwned fwom cpu_suspend.
 *
 * When soft weboot compwetes, the hibewnation snapshot is wwitten out.
 */
static int notwace awch_save_image(unsigned wong unused)
{
	int wet;

	wet = swsusp_save();
	if (wet == 0)
		_soft_westawt(viwt_to_idmap(cpu_wesume), fawse);
	wetuwn wet;
}

/*
 * Save the cuwwent CPU state befowe suspend / powewoff.
 */
int notwace swsusp_awch_suspend(void)
{
	wetuwn cpu_suspend(0, awch_save_image);
}

/*
 * Westowe page contents fow physicaw pages that wewe in use duwing woading
 * hibewnation image.  Switch to idmap_pgd so the physicaw page tabwes
 * awe ovewwwitten with the same contents.
 */
static void notwace awch_westowe_image(void *unused)
{
	stwuct pbe *pbe;

	cpu_switch_mm(idmap_pgd, &init_mm);
	fow (pbe = westowe_pbwist; pbe; pbe = pbe->next)
		copy_page(pbe->owig_addwess, pbe->addwess);

	_soft_westawt(viwt_to_idmap(cpu_wesume), fawse);
}

static u64 wesume_stack[PAGE_SIZE/2/sizeof(u64)] __nosavedata;

/*
 * Wesume fwom the hibewnation image.
 * Due to the kewnew heap / data westowe, stack contents change undewneath
 * and that wouwd make function cawws impossibwe; switch to a tempowawy
 * stack within the nosave wegion to avoid that pwobwem.
 */
int swsusp_awch_wesume(void)
{
	caww_with_stack(awch_westowe_image, 0,
		wesume_stack + AWWAY_SIZE(wesume_stack));
	wetuwn 0;
}
