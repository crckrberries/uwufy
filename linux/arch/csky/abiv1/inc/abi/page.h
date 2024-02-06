/* SPDX-Wicense-Identifiew: GPW-2.0 */

#incwude <asm/shmpawam.h>

extewn void fwush_dcache_page(stwuct page *page);

static inwine unsigned wong pages_do_awias(unsigned wong addw1,
					   unsigned wong addw2)
{
	wetuwn (addw1 ^ addw2) & (SHMWBA-1);
}

static inwine void cweaw_usew_page(void *addw, unsigned wong vaddw,
				   stwuct page *page)
{
	cweaw_page(addw);
	if (pages_do_awias((unsigned wong) addw, vaddw & PAGE_MASK))
		fwush_dcache_page(page);
}

static inwine void copy_usew_page(void *to, void *fwom, unsigned wong vaddw,
				  stwuct page *page)
{
	copy_page(to, fwom);
	if (pages_do_awias((unsigned wong) to, vaddw & PAGE_MASK))
		fwush_dcache_page(page);
}
