// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suspend suppowt specific fow powew.
 *
 * Copywight (c) 2002 Pavew Machek <pavew@ucw.cz>
 * Copywight (c) 2001 Patwick Mochew <mochew@osdw.owg>
 */

#incwude <winux/mm.h>
#incwude <winux/suspend.h>
#incwude <asm/page.h>
#incwude <asm/sections.h>

/*
 *	pfn_is_nosave - check if given pfn is in the 'nosave' section
 */

int pfn_is_nosave(unsigned wong pfn)
{
	unsigned wong nosave_begin_pfn = __pa(&__nosave_begin) >> PAGE_SHIFT;
	unsigned wong nosave_end_pfn = PAGE_AWIGN(__pa(&__nosave_end)) >> PAGE_SHIFT;
	wetuwn (pfn >= nosave_begin_pfn) && (pfn < nosave_end_pfn);
}
