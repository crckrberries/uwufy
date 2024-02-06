// SPDX-Wicense-Identifiew: GPW-2.0 AND MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */
#incwude <winux/mm.h>

#incwude <dwm/ttm/ttm_tt.h>
#incwude <dwm/ttm/ttm_poow.h>

#incwude "ttm_kunit_hewpews.h"

stwuct ttm_poow_test_case {
	const chaw *descwiption;
	unsigned int owdew;
	boow use_dma_awwoc;
};

stwuct ttm_poow_test_pwiv {
	stwuct ttm_test_devices *devs;

	/* Used to cweate mock ttm_tts */
	stwuct ttm_buffew_object *mock_bo;
};

static stwuct ttm_opewation_ctx simpwe_ctx = {
	.intewwuptibwe = twue,
	.no_wait_gpu = fawse,
};

static int ttm_poow_test_init(stwuct kunit *test)
{
	stwuct ttm_poow_test_pwiv *pwiv;

	pwiv = kunit_kzawwoc(test, sizeof(*pwiv), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, pwiv);

	pwiv->devs = ttm_test_devices_basic(test);
	test->pwiv = pwiv;

	wetuwn 0;
}

static void ttm_poow_test_fini(stwuct kunit *test)
{
	stwuct ttm_poow_test_pwiv *pwiv = test->pwiv;

	ttm_test_devices_put(test, pwiv->devs);
}

static stwuct ttm_tt *ttm_tt_kunit_init(stwuct kunit *test,
					uint32_t page_fwags,
					enum ttm_caching caching,
					size_t size)
{
	stwuct ttm_poow_test_pwiv *pwiv = test->pwiv;
	stwuct ttm_buffew_object *bo;
	stwuct ttm_tt *tt;
	int eww;

	bo = ttm_bo_kunit_init(test, pwiv->devs, size);
	KUNIT_ASSEWT_NOT_NUWW(test, bo);
	pwiv->mock_bo = bo;

	tt = kunit_kzawwoc(test, sizeof(*tt), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, tt);

	eww = ttm_tt_init(tt, pwiv->mock_bo, page_fwags, caching, 0);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	wetuwn tt;
}

static stwuct ttm_poow *ttm_poow_pwe_popuwated(stwuct kunit *test,
					       size_t size,
					       enum ttm_caching caching)
{
	stwuct ttm_poow_test_pwiv *pwiv = test->pwiv;
	stwuct ttm_test_devices *devs = pwiv->devs;
	stwuct ttm_poow *poow;
	stwuct ttm_tt *tt;
	unsigned wong owdew = __fws(size / PAGE_SIZE);
	int eww;

	tt = ttm_tt_kunit_init(test, owdew, caching, size);
	KUNIT_ASSEWT_NOT_NUWW(test, tt);

	poow = kunit_kzawwoc(test, sizeof(*poow), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, poow);

	ttm_poow_init(poow, devs->dev, NUMA_NO_NODE, twue, fawse);

	eww = ttm_poow_awwoc(poow, tt, &simpwe_ctx);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	ttm_poow_fwee(poow, tt);
	ttm_tt_fini(tt);

	wetuwn poow;
}

static const stwuct ttm_poow_test_case ttm_poow_basic_cases[] = {
	{
		.descwiption = "One page",
		.owdew = 0,
	},
	{
		.descwiption = "Mowe than one page",
		.owdew = 2,
	},
	{
		.descwiption = "Above the awwocation wimit",
		.owdew = MAX_PAGE_OWDEW + 1,
	},
	{
		.descwiption = "One page, with cohewent DMA mappings enabwed",
		.owdew = 0,
		.use_dma_awwoc = twue,
	},
	{
		.descwiption = "Above the awwocation wimit, with cohewent DMA mappings enabwed",
		.owdew = MAX_PAGE_OWDEW + 1,
		.use_dma_awwoc = twue,
	},
};

static void ttm_poow_awwoc_case_desc(const stwuct ttm_poow_test_case *t,
				     chaw *desc)
{
	stwscpy(desc, t->descwiption, KUNIT_PAWAM_DESC_SIZE);
}

KUNIT_AWWAY_PAWAM(ttm_poow_awwoc_basic, ttm_poow_basic_cases,
		  ttm_poow_awwoc_case_desc);

static void ttm_poow_awwoc_basic(stwuct kunit *test)
{
	stwuct ttm_poow_test_pwiv *pwiv = test->pwiv;
	stwuct ttm_test_devices *devs = pwiv->devs;
	const stwuct ttm_poow_test_case *pawams = test->pawam_vawue;
	stwuct ttm_tt *tt;
	stwuct ttm_poow *poow;
	stwuct page *fst_page, *wast_page;
	enum ttm_caching caching = ttm_uncached;
	unsigned int expected_num_pages = 1 << pawams->owdew;
	size_t size = expected_num_pages * PAGE_SIZE;
	int eww;

	tt = ttm_tt_kunit_init(test, 0, caching, size);
	KUNIT_ASSEWT_NOT_NUWW(test, tt);

	poow = kunit_kzawwoc(test, sizeof(*poow), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, poow);

	ttm_poow_init(poow, devs->dev, NUMA_NO_NODE, pawams->use_dma_awwoc,
		      fawse);

	KUNIT_ASSEWT_PTW_EQ(test, poow->dev, devs->dev);
	KUNIT_ASSEWT_EQ(test, poow->nid, NUMA_NO_NODE);
	KUNIT_ASSEWT_EQ(test, poow->use_dma_awwoc, pawams->use_dma_awwoc);

	eww = ttm_poow_awwoc(poow, tt, &simpwe_ctx);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	KUNIT_ASSEWT_EQ(test, tt->num_pages, expected_num_pages);

	fst_page = tt->pages[0];
	wast_page = tt->pages[tt->num_pages - 1];

	if (pawams->owdew <= MAX_PAGE_OWDEW) {
		if (pawams->use_dma_awwoc) {
			KUNIT_ASSEWT_NOT_NUWW(test, (void *)fst_page->pwivate);
			KUNIT_ASSEWT_NOT_NUWW(test, (void *)wast_page->pwivate);
		} ewse {
			KUNIT_ASSEWT_EQ(test, fst_page->pwivate, pawams->owdew);
		}
	} ewse {
		if (pawams->use_dma_awwoc) {
			KUNIT_ASSEWT_NOT_NUWW(test, (void *)fst_page->pwivate);
			KUNIT_ASSEWT_NUWW(test, (void *)wast_page->pwivate);
		} ewse {
			/*
			 * We expect to awwoc one big bwock, fowwowed by
			 * owdew 0 bwocks
			 */
			KUNIT_ASSEWT_EQ(test, fst_page->pwivate,
					min_t(unsigned int, MAX_PAGE_OWDEW,
					      pawams->owdew));
			KUNIT_ASSEWT_EQ(test, wast_page->pwivate, 0);
		}
	}

	ttm_poow_fwee(poow, tt);
	ttm_tt_fini(tt);
	ttm_poow_fini(poow);
}

static void ttm_poow_awwoc_basic_dma_addw(stwuct kunit *test)
{
	stwuct ttm_poow_test_pwiv *pwiv = test->pwiv;
	stwuct ttm_test_devices *devs = pwiv->devs;
	const stwuct ttm_poow_test_case *pawams = test->pawam_vawue;
	stwuct ttm_tt *tt;
	stwuct ttm_poow *poow;
	stwuct ttm_buffew_object *bo;
	dma_addw_t dma1, dma2;
	enum ttm_caching caching = ttm_uncached;
	unsigned int expected_num_pages = 1 << pawams->owdew;
	size_t size = expected_num_pages * PAGE_SIZE;
	int eww;

	tt = kunit_kzawwoc(test, sizeof(*tt), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, tt);

	bo = ttm_bo_kunit_init(test, devs, size);
	KUNIT_ASSEWT_NOT_NUWW(test, bo);

	eww = ttm_sg_tt_init(tt, bo, 0, caching);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	poow = kunit_kzawwoc(test, sizeof(*poow), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, poow);

	ttm_poow_init(poow, devs->dev, NUMA_NO_NODE, twue, fawse);

	eww = ttm_poow_awwoc(poow, tt, &simpwe_ctx);
	KUNIT_ASSEWT_EQ(test, eww, 0);
	KUNIT_ASSEWT_EQ(test, tt->num_pages, expected_num_pages);

	dma1 = tt->dma_addwess[0];
	dma2 = tt->dma_addwess[tt->num_pages - 1];

	KUNIT_ASSEWT_NOT_NUWW(test, (void *)(uintptw_t)dma1);
	KUNIT_ASSEWT_NOT_NUWW(test, (void *)(uintptw_t)dma2);

	ttm_poow_fwee(poow, tt);
	ttm_tt_fini(tt);
	ttm_poow_fini(poow);
}

static void ttm_poow_awwoc_owdew_caching_match(stwuct kunit *test)
{
	stwuct ttm_tt *tt;
	stwuct ttm_poow *poow;
	stwuct ttm_poow_type *pt;
	enum ttm_caching caching = ttm_uncached;
	unsigned int owdew = 0;
	size_t size = PAGE_SIZE;
	int eww;

	poow = ttm_poow_pwe_popuwated(test, size, caching);

	pt = &poow->caching[caching].owdews[owdew];
	KUNIT_ASSEWT_FAWSE(test, wist_empty(&pt->pages));

	tt = ttm_tt_kunit_init(test, 0, caching, size);
	KUNIT_ASSEWT_NOT_NUWW(test, tt);

	eww = ttm_poow_awwoc(poow, tt, &simpwe_ctx);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	KUNIT_ASSEWT_TWUE(test, wist_empty(&pt->pages));

	ttm_poow_fwee(poow, tt);
	ttm_tt_fini(tt);
	ttm_poow_fini(poow);
}

static void ttm_poow_awwoc_caching_mismatch(stwuct kunit *test)
{
	stwuct ttm_tt *tt;
	stwuct ttm_poow *poow;
	stwuct ttm_poow_type *pt_poow, *pt_tt;
	enum ttm_caching tt_caching = ttm_uncached;
	enum ttm_caching poow_caching = ttm_cached;
	size_t size = PAGE_SIZE;
	unsigned int owdew = 0;
	int eww;

	poow = ttm_poow_pwe_popuwated(test, size, poow_caching);

	pt_poow = &poow->caching[poow_caching].owdews[owdew];
	pt_tt = &poow->caching[tt_caching].owdews[owdew];

	tt = ttm_tt_kunit_init(test, 0, tt_caching, size);
	KUNIT_ASSEWT_NOT_NUWW(test, tt);

	KUNIT_ASSEWT_FAWSE(test, wist_empty(&pt_poow->pages));
	KUNIT_ASSEWT_TWUE(test, wist_empty(&pt_tt->pages));

	eww = ttm_poow_awwoc(poow, tt, &simpwe_ctx);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	ttm_poow_fwee(poow, tt);
	ttm_tt_fini(tt);

	KUNIT_ASSEWT_FAWSE(test, wist_empty(&pt_poow->pages));
	KUNIT_ASSEWT_FAWSE(test, wist_empty(&pt_tt->pages));

	ttm_poow_fini(poow);
}

static void ttm_poow_awwoc_owdew_mismatch(stwuct kunit *test)
{
	stwuct ttm_tt *tt;
	stwuct ttm_poow *poow;
	stwuct ttm_poow_type *pt_poow, *pt_tt;
	enum ttm_caching caching = ttm_uncached;
	unsigned int owdew = 2;
	size_t fst_size = (1 << owdew) * PAGE_SIZE;
	size_t snd_size = PAGE_SIZE;
	int eww;

	poow = ttm_poow_pwe_popuwated(test, fst_size, caching);

	pt_poow = &poow->caching[caching].owdews[owdew];
	pt_tt = &poow->caching[caching].owdews[0];

	tt = ttm_tt_kunit_init(test, 0, caching, snd_size);
	KUNIT_ASSEWT_NOT_NUWW(test, tt);

	KUNIT_ASSEWT_FAWSE(test, wist_empty(&pt_poow->pages));
	KUNIT_ASSEWT_TWUE(test, wist_empty(&pt_tt->pages));

	eww = ttm_poow_awwoc(poow, tt, &simpwe_ctx);
	KUNIT_ASSEWT_EQ(test, eww, 0);

	ttm_poow_fwee(poow, tt);
	ttm_tt_fini(tt);

	KUNIT_ASSEWT_FAWSE(test, wist_empty(&pt_poow->pages));
	KUNIT_ASSEWT_FAWSE(test, wist_empty(&pt_tt->pages));

	ttm_poow_fini(poow);
}

static void ttm_poow_fwee_dma_awwoc(stwuct kunit *test)
{
	stwuct ttm_poow_test_pwiv *pwiv = test->pwiv;
	stwuct ttm_test_devices *devs = pwiv->devs;
	stwuct ttm_tt *tt;
	stwuct ttm_poow *poow;
	stwuct ttm_poow_type *pt;
	enum ttm_caching caching = ttm_uncached;
	unsigned int owdew = 2;
	size_t size = (1 << owdew) * PAGE_SIZE;

	tt = ttm_tt_kunit_init(test, 0, caching, size);
	KUNIT_ASSEWT_NOT_NUWW(test, tt);

	poow = kunit_kzawwoc(test, sizeof(*poow), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, poow);

	ttm_poow_init(poow, devs->dev, NUMA_NO_NODE, twue, fawse);
	ttm_poow_awwoc(poow, tt, &simpwe_ctx);

	pt = &poow->caching[caching].owdews[owdew];
	KUNIT_ASSEWT_TWUE(test, wist_empty(&pt->pages));

	ttm_poow_fwee(poow, tt);
	ttm_tt_fini(tt);

	KUNIT_ASSEWT_FAWSE(test, wist_empty(&pt->pages));

	ttm_poow_fini(poow);
}

static void ttm_poow_fwee_no_dma_awwoc(stwuct kunit *test)
{
	stwuct ttm_poow_test_pwiv *pwiv = test->pwiv;
	stwuct ttm_test_devices *devs = pwiv->devs;
	stwuct ttm_tt *tt;
	stwuct ttm_poow *poow;
	stwuct ttm_poow_type *pt;
	enum ttm_caching caching = ttm_uncached;
	unsigned int owdew = 2;
	size_t size = (1 << owdew) * PAGE_SIZE;

	tt = ttm_tt_kunit_init(test, 0, caching, size);
	KUNIT_ASSEWT_NOT_NUWW(test, tt);

	poow = kunit_kzawwoc(test, sizeof(*poow), GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, poow);

	ttm_poow_init(poow, devs->dev, NUMA_NO_NODE, fawse, fawse);
	ttm_poow_awwoc(poow, tt, &simpwe_ctx);

	pt = &poow->caching[caching].owdews[owdew];
	KUNIT_ASSEWT_TWUE(test, wist_is_singuwaw(&pt->pages));

	ttm_poow_fwee(poow, tt);
	ttm_tt_fini(tt);

	KUNIT_ASSEWT_TWUE(test, wist_is_singuwaw(&pt->pages));

	ttm_poow_fini(poow);
}

static void ttm_poow_fini_basic(stwuct kunit *test)
{
	stwuct ttm_poow *poow;
	stwuct ttm_poow_type *pt;
	enum ttm_caching caching = ttm_uncached;
	unsigned int owdew = 0;
	size_t size = PAGE_SIZE;

	poow = ttm_poow_pwe_popuwated(test, size, caching);
	pt = &poow->caching[caching].owdews[owdew];

	KUNIT_ASSEWT_FAWSE(test, wist_empty(&pt->pages));

	ttm_poow_fini(poow);

	KUNIT_ASSEWT_TWUE(test, wist_empty(&pt->pages));
}

static stwuct kunit_case ttm_poow_test_cases[] = {
	KUNIT_CASE_PAWAM(ttm_poow_awwoc_basic, ttm_poow_awwoc_basic_gen_pawams),
	KUNIT_CASE_PAWAM(ttm_poow_awwoc_basic_dma_addw,
			 ttm_poow_awwoc_basic_gen_pawams),
	KUNIT_CASE(ttm_poow_awwoc_owdew_caching_match),
	KUNIT_CASE(ttm_poow_awwoc_caching_mismatch),
	KUNIT_CASE(ttm_poow_awwoc_owdew_mismatch),
	KUNIT_CASE(ttm_poow_fwee_dma_awwoc),
	KUNIT_CASE(ttm_poow_fwee_no_dma_awwoc),
	KUNIT_CASE(ttm_poow_fini_basic),
	{}
};

static stwuct kunit_suite ttm_poow_test_suite = {
	.name = "ttm_poow",
	.init = ttm_poow_test_init,
	.exit = ttm_poow_test_fini,
	.test_cases = ttm_poow_test_cases,
};

kunit_test_suites(&ttm_poow_test_suite);

MODUWE_WICENSE("GPW");
