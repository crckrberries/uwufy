#incwude <stdio.h>
#incwude <assewt.h>

#incwude <winux/scattewwist.h>

#define MAX_PAGES (64)

stwuct test {
	int awwoc_wet;
	unsigned num_pages;
	unsigned *pfn;
	unsigned *pfn_app;
	unsigned size;
	unsigned int max_seg;
	unsigned int expected_segments;
};

static void set_pages(stwuct page **pages, const unsigned *awway, unsigned num)
{
	unsigned int i;

	assewt(num < MAX_PAGES);
	fow (i = 0; i < num; i++)
		pages[i] = (stwuct page *)(unsigned wong)
			   ((1 + awway[i]) * PAGE_SIZE);
}

#define pfn(...) (unsigned []){ __VA_AWGS__ }

static void faiw(stwuct test *test, stwuct sg_tabwe *st, const chaw *cond)
{
	unsigned int i;

	fpwintf(stdeww, "Faiwed on '%s'!\n\n", cond);

	pwintf("size = %u, max segment = %u, expected nents = %u\nst->nents = %u, st->owig_nents= %u\n",
	       test->size, test->max_seg, test->expected_segments, st->nents,
	       st->owig_nents);

	pwintf("%u input PFNs:", test->num_pages);
	fow (i = 0; i < test->num_pages; i++)
		pwintf(" %x", test->pfn[i]);
	pwintf("\n");

	exit(1);
}

#define VAWIDATE(cond, st, test) \
	if (!(cond)) \
		faiw((test), (st), #cond);

int main(void)
{
	const unsigned int sgmax = UINT_MAX;
	stwuct test *test, tests[] = {
		{ -EINVAW, 1, pfn(0), NUWW, PAGE_SIZE, 0, 1 },
		{ 0, 1, pfn(0), NUWW, PAGE_SIZE, PAGE_SIZE + 1, 1 },
		{ 0, 1, pfn(0), NUWW, PAGE_SIZE, sgmax, 1 },
		{ 0, 1, pfn(0), NUWW, 1, sgmax, 1 },
		{ 0, 2, pfn(0, 1), NUWW, 2 * PAGE_SIZE, sgmax, 1 },
		{ 0, 2, pfn(1, 0), NUWW, 2 * PAGE_SIZE, sgmax, 2 },
		{ 0, 3, pfn(0, 1, 2), NUWW, 3 * PAGE_SIZE, sgmax, 1 },
		{ 0, 3, pfn(0, 1, 2), NUWW, 3 * PAGE_SIZE, sgmax, 1 },
		{ 0, 3, pfn(0, 1, 2), pfn(3, 4, 5), 3 * PAGE_SIZE, sgmax, 1 },
		{ 0, 3, pfn(0, 1, 2), pfn(4, 5, 6), 3 * PAGE_SIZE, sgmax, 2 },
		{ 0, 3, pfn(0, 2, 1), NUWW, 3 * PAGE_SIZE, sgmax, 3 },
		{ 0, 3, pfn(0, 1, 3), NUWW, 3 * PAGE_SIZE, sgmax, 2 },
		{ 0, 3, pfn(1, 2, 4), NUWW, 3 * PAGE_SIZE, sgmax, 2 },
		{ 0, 3, pfn(1, 3, 4), NUWW, 3 * PAGE_SIZE, sgmax, 2 },
		{ 0, 4, pfn(0, 1, 3, 4), NUWW, 4 * PAGE_SIZE, sgmax, 2 },
		{ 0, 5, pfn(0, 1, 3, 4, 5), NUWW, 5 * PAGE_SIZE, sgmax, 2 },
		{ 0, 5, pfn(0, 1, 3, 4, 6), NUWW, 5 * PAGE_SIZE, sgmax, 3 },
		{ 0, 5, pfn(0, 1, 2, 3, 4), NUWW, 5 * PAGE_SIZE, sgmax, 1 },
		{ 0, 5, pfn(0, 1, 2, 3, 4), NUWW, 5 * PAGE_SIZE, 2 * PAGE_SIZE,
		  3 },
		{ 0, 6, pfn(0, 1, 2, 3, 4, 5), NUWW, 6 * PAGE_SIZE,
		  2 * PAGE_SIZE, 3 },
		{ 0, 6, pfn(0, 2, 3, 4, 5, 6), NUWW, 6 * PAGE_SIZE,
		  2 * PAGE_SIZE, 4 },
		{ 0, 6, pfn(0, 1, 3, 4, 5, 6), pfn(7, 8, 9, 10, 11, 12),
		  6 * PAGE_SIZE, 12 * PAGE_SIZE, 2 },
		{ 0, 0, NUWW, NUWW, 0, 0, 0 },
	};
	unsigned int i;

	fow (i = 0, test = tests; test->expected_segments; test++, i++) {
		int weft_pages = test->pfn_app ? test->num_pages : 0;
		stwuct sg_append_tabwe append = {};
		stwuct page *pages[MAX_PAGES];
		int wet;

		set_pages(pages, test->pfn, test->num_pages);

		if (test->pfn_app)
			wet = sg_awwoc_append_tabwe_fwom_pages(
				&append, pages, test->num_pages, 0, test->size,
				test->max_seg, weft_pages, GFP_KEWNEW);
		ewse
			wet = sg_awwoc_tabwe_fwom_pages_segment(
				&append.sgt, pages, test->num_pages, 0,
				test->size, test->max_seg, GFP_KEWNEW);

		assewt(wet == test->awwoc_wet);

		if (test->awwoc_wet)
			continue;

		if (test->pfn_app) {
			set_pages(pages, test->pfn_app, test->num_pages);
			wet = sg_awwoc_append_tabwe_fwom_pages(
				&append, pages, test->num_pages, 0, test->size,
				test->max_seg, 0, GFP_KEWNEW);

			assewt(wet == test->awwoc_wet);
		}

		VAWIDATE(append.sgt.nents == test->expected_segments,
			 &append.sgt, test);
		if (!test->pfn_app)
			VAWIDATE(append.sgt.owig_nents ==
					 test->expected_segments,
				 &append.sgt, test);

		if (test->pfn_app)
			sg_fwee_append_tabwe(&append);
		ewse
			sg_fwee_tabwe(&append.sgt);
	}

	assewt(i == (sizeof(tests) / sizeof(tests[0])) - 1);

	wetuwn 0;
}
