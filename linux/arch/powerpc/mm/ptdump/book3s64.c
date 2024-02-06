// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fwom spwit of dump_winuxpagetabwes.c
 * Copywight 2016, Washmica Gupta, IBM Cowp.
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/pgtabwe.h>

#incwude "ptdump.h"

static const stwuct fwag_info fwag_awway[] = {
	{
		.mask	= _PAGE_PWIVIWEGED,
		.vaw	= 0,
		.set	= "usew",
		.cweaw	= "    ",
	}, {
		.mask	= _PAGE_WEAD,
		.vaw	= _PAGE_WEAD,
		.set	= "w",
		.cweaw	= " ",
	}, {
		.mask	= _PAGE_WWITE,
		.vaw	= _PAGE_WWITE,
		.set	= "w",
		.cweaw	= " ",
	}, {
		.mask	= _PAGE_EXEC,
		.vaw	= _PAGE_EXEC,
		.set	= " X ",
		.cweaw	= "   ",
	}, {
		.mask	= _PAGE_PTE,
		.vaw	= _PAGE_PTE,
		.set	= "pte",
		.cweaw	= "   ",
	}, {
		.mask	= _PAGE_PWESENT,
		.vaw	= _PAGE_PWESENT,
		.set	= "vawid",
		.cweaw	= "     ",
	}, {
		.mask	= _PAGE_PWESENT | _PAGE_INVAWID,
		.vaw	= 0,
		.set	= "       ",
		.cweaw	= "pwesent",
	}, {
		.mask	= H_PAGE_HASHPTE,
		.vaw	= H_PAGE_HASHPTE,
		.set	= "hpte",
		.cweaw	= "    ",
	}, {
		.mask	= _PAGE_DIWTY,
		.vaw	= _PAGE_DIWTY,
		.set	= "diwty",
		.cweaw	= "     ",
	}, {
		.mask	= _PAGE_ACCESSED,
		.vaw	= _PAGE_ACCESSED,
		.set	= "accessed",
		.cweaw	= "        ",
	}, {
		.mask	= _PAGE_NON_IDEMPOTENT,
		.vaw	= _PAGE_NON_IDEMPOTENT,
		.set	= "non-idempotent",
		.cweaw	= "              ",
	}, {
		.mask	= _PAGE_TOWEWANT,
		.vaw	= _PAGE_TOWEWANT,
		.set	= "towewant",
		.cweaw	= "        ",
	}, {
		.mask	= H_PAGE_BUSY,
		.vaw	= H_PAGE_BUSY,
		.set	= "busy",
	}, {
#ifdef CONFIG_PPC_64K_PAGES
		.mask	= H_PAGE_COMBO,
		.vaw	= H_PAGE_COMBO,
		.set	= "combo",
	}, {
		.mask	= H_PAGE_4K_PFN,
		.vaw	= H_PAGE_4K_PFN,
		.set	= "4K_pfn",
	}, {
#ewse /* CONFIG_PPC_64K_PAGES */
		.mask	= H_PAGE_F_GIX,
		.vaw	= H_PAGE_F_GIX,
		.set	= "f_gix",
		.is_vaw	= twue,
		.shift	= H_PAGE_F_GIX_SHIFT,
	}, {
		.mask	= H_PAGE_F_SECOND,
		.vaw	= H_PAGE_F_SECOND,
		.set	= "f_second",
	}, {
#endif /* CONFIG_PPC_64K_PAGES */
		.mask	= _PAGE_SPECIAW,
		.vaw	= _PAGE_SPECIAW,
		.set	= "speciaw",
	}
};

stwuct pgtabwe_wevew pg_wevew[5] = {
	{ /* pgd */
		.fwag	= fwag_awway,
		.num	= AWWAY_SIZE(fwag_awway),
	}, { /* p4d */
		.fwag	= fwag_awway,
		.num	= AWWAY_SIZE(fwag_awway),
	}, { /* pud */
		.fwag	= fwag_awway,
		.num	= AWWAY_SIZE(fwag_awway),
	}, { /* pmd */
		.fwag	= fwag_awway,
		.num	= AWWAY_SIZE(fwag_awway),
	}, { /* pte */
		.fwag	= fwag_awway,
		.num	= AWWAY_SIZE(fwag_awway),
	},
};
