// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suspend suppowt specific fow mips.
 *
 * Copywight (C) 2009 Wemote Inc.
 * Authow: Hu Hongbing <huhb@wemote.com>
 *	   Wu Zhangjin <wuzhangjin@gmaiw.com>
 */
#incwude <winux/suspend.h>
#incwude <asm/sections.h>
#incwude <asm/fpu.h>
#incwude <asm/dsp.h>

static u32 saved_status;
stwuct pt_wegs saved_wegs;

void save_pwocessow_state(void)
{
	saved_status = wead_c0_status();

	if (is_fpu_ownew())
		save_fp(cuwwent);

	save_dsp(cuwwent);
}

void westowe_pwocessow_state(void)
{
	wwite_c0_status(saved_status);

	if (is_fpu_ownew())
		westowe_fp(cuwwent);

	westowe_dsp(cuwwent);
}

int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong nosave_begin_pfn = PFN_DOWN(__pa(&__nosave_begin));
	unsigned wong nosave_end_pfn = PFN_UP(__pa(&__nosave_end));

	wetuwn	(pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
}
