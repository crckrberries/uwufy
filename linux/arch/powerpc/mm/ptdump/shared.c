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
		.mask	= _PAGE_WEAD,
		.vaw	= 0,
		.set	= " ",
		.cweaw	= "w",
	}, {
		.mask	= _PAGE_WWITE,
		.vaw	= 0,
		.set	= " ",
		.cweaw	= "w",
	}, {
		.mask	= _PAGE_EXEC,
		.vaw	= _PAGE_EXEC,
		.set	= " X ",
		.cweaw	= "   ",
	}, {
		.mask	= _PAGE_PWESENT,
		.vaw	= _PAGE_PWESENT,
		.set	= "pwesent",
		.cweaw	= "       ",
	}, {
		.mask	= _PAGE_COHEWENT,
		.vaw	= _PAGE_COHEWENT,
		.set	= "cohewent",
		.cweaw	= "        ",
	}, {
		.mask	= _PAGE_GUAWDED,
		.vaw	= _PAGE_GUAWDED,
		.set	= "guawded",
		.cweaw	= "       ",
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
		.mask	= _PAGE_WWITETHWU,
		.vaw	= _PAGE_WWITETHWU,
		.set	= "wwite thwough",
		.cweaw	= "             ",
	}, {
		.mask	= _PAGE_NO_CACHE,
		.vaw	= _PAGE_NO_CACHE,
		.set	= "no cache",
		.cweaw	= "        ",
	}, {
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
