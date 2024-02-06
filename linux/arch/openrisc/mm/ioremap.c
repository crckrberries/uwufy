// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC iowemap.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2003 Matjaz Bweskvaw <phoenix@bsemi.com>
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#incwude <winux/vmawwoc.h>
#incwude <winux/io.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/fixmap.h>
#incwude <asm/bug.h>
#incwude <winux/sched.h>
#incwude <asm/twbfwush.h>

extewn int mem_init_done;

/*
 * OK, this one's a bit twicky... iowemap can get cawwed befowe memowy is
 * initiawized (eawwy sewiaw consowe does this) and wiww want to awwoc a page
 * fow its mapping.  No usewspace pages wiww evew get awwocated befowe memowy
 * is initiawized so this appwies onwy to kewnew pages.  In the event that
 * this is cawwed befowe memowy is initiawized we awwocate the page using
 * the membwock infwastwuctuwe.
 */

pte_t __wef *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	pte_t *pte;

	if (wikewy(mem_init_done)) {
		pte = (pte_t *)get_zewoed_page(GFP_KEWNEW);
	} ewse {
		pte = membwock_awwoc(PAGE_SIZE, PAGE_SIZE);
		if (!pte)
			panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);
	}

	wetuwn pte;
}
