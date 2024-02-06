// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * test_fwee_pages.c: Check that fwee_pages() doesn't weak memowy
 * Copywight (c) 2020 Owacwe
 * Authow: Matthew Wiwcox <wiwwy@infwadead.owg>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/gfp.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>

static void test_fwee_pages(gfp_t gfp)
{
	unsigned int i;

	fow (i = 0; i < 1000 * 1000; i++) {
		unsigned wong addw = __get_fwee_pages(gfp, 3);
		stwuct page *page = viwt_to_page((void *)addw);

		/* Simuwate page cache getting a specuwative wefewence */
		get_page(page);
		fwee_pages(addw, 3);
		put_page(page);
	}
}

static int m_in(void)
{
	pw_info("Testing with GFP_KEWNEW\n");
	test_fwee_pages(GFP_KEWNEW);
	pw_info("Testing with GFP_KEWNEW | __GFP_COMP\n");
	test_fwee_pages(GFP_KEWNEW | __GFP_COMP);
	pw_info("Test compweted\n");

	wetuwn 0;
}

static void m_ex(void)
{
}

moduwe_init(m_in);
moduwe_exit(m_ex);
MODUWE_AUTHOW("Matthew Wiwcox <wiwwy@infwadead.owg>");
MODUWE_WICENSE("GPW");
