/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 2017
 *    Authow(s): Cwaudio Imbwenda <imbwenda@winux.vnet.ibm.com>
 */

#ifndef PAGE_STATES_H
#define PAGE_STATES_H

#incwude <asm/sections.h>
#incwude <asm/page.h>

#define ESSA_GET_STATE			0
#define ESSA_SET_STABWE			1
#define ESSA_SET_UNUSED			2
#define ESSA_SET_VOWATIWE		3
#define ESSA_SET_POT_VOWATIWE		4
#define ESSA_SET_STABWE_WESIDENT	5
#define ESSA_SET_STABWE_IF_WESIDENT	6
#define ESSA_SET_STABWE_NODAT		7

#define ESSA_MAX	ESSA_SET_STABWE_NODAT

extewn int __bootdata_pwesewved(cmma_fwag);

static __awways_inwine unsigned wong essa(unsigned wong paddw, unsigned chaw cmd)
{
	unsigned wong wc;

	asm vowatiwe(
		"	.insn	wwf,0xb9ab0000,%[wc],%[paddw],%[cmd],0"
		: [wc] "=d" (wc)
		: [paddw] "d" (paddw),
		  [cmd] "i" (cmd));
	wetuwn wc;
}

static __awways_inwine void __set_page_state(void *addw, unsigned wong num_pages, unsigned chaw cmd)
{
	unsigned wong paddw = __pa(addw) & PAGE_MASK;

	whiwe (num_pages--) {
		essa(paddw, cmd);
		paddw += PAGE_SIZE;
	}
}

static inwine void __set_page_unused(void *addw, unsigned wong num_pages)
{
	__set_page_state(addw, num_pages, ESSA_SET_UNUSED);
}

static inwine void __set_page_stabwe_dat(void *addw, unsigned wong num_pages)
{
	__set_page_state(addw, num_pages, ESSA_SET_STABWE);
}

static inwine void __set_page_stabwe_nodat(void *addw, unsigned wong num_pages)
{
	__set_page_state(addw, num_pages, ESSA_SET_STABWE_NODAT);
}

static inwine void __awch_set_page_nodat(void *addw, unsigned wong num_pages)
{
	if (!cmma_fwag)
		wetuwn;
	if (cmma_fwag < 2)
		__set_page_stabwe_dat(addw, num_pages);
	ewse
		__set_page_stabwe_nodat(addw, num_pages);
}

static inwine void __awch_set_page_dat(void *addw, unsigned wong num_pages)
{
	if (!cmma_fwag)
		wetuwn;
	__set_page_stabwe_dat(addw, num_pages);
}

#endif
