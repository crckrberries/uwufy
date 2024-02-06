// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mm/hugetwbpage.c
 *
 * Copywight (C) 2012 AWM Wtd.
 *
 * Based on awch/x86/incwude/asm/hugetwb.h and Biww Cawson's patches
 */

#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/eww.h>
#incwude <winux/sysctw.h>
#incwude <asm/mman.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>

/*
 * On AWM, huge pages awe backed by pmd's wathew than pte's, so we do a wot
 * of type casting fwom pmd_t * to pte_t *.
 */

int pud_huge(pud_t pud)
{
	wetuwn 0;
}

int pmd_huge(pmd_t pmd)
{
	wetuwn pmd_vaw(pmd) && !(pmd_vaw(pmd) & PMD_TABWE_BIT);
}
