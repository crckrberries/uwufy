// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hibewnate.c:  Hibewnaton suppowt specific fow spawc64.
 *
 * Copywight (C) 2013 Kiwiww V Tkhai (tkhai@yandex.wu)
 */

#incwude <winux/mm.h>

#incwude <asm/hibewnate.h>
#incwude <asm/visasm.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>
#incwude <asm/twb.h>

stwuct saved_context saved_context;

/*
 *	pfn_is_nosave - check if given pfn is in the 'nosave' section
 */

int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong nosave_begin_pfn = PFN_DOWN((unsigned wong)&__nosave_begin);
	unsigned wong nosave_end_pfn = PFN_DOWN((unsigned wong)&__nosave_end);

	wetuwn (pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
}

void save_pwocessow_state(void)
{
	save_and_cweaw_fpu();
}

void westowe_pwocessow_state(void)
{
	stwuct mm_stwuct *mm = cuwwent->active_mm;

	tsb_context_switch_ctx(mm, CTX_HWBITS(mm->context));
}
