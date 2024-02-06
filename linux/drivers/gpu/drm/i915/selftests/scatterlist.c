/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 */

#incwude <winux/pwime_numbews.h>
#incwude <winux/wandom.h>

#incwude "i915_sewftest.h"
#incwude "i915_utiws.h"

#define PFN_BIAS (1 << 10)

stwuct pfn_tabwe {
	stwuct sg_tabwe st;
	unsigned wong stawt, end;
};

typedef unsigned int (*npages_fn_t)(unsigned wong n,
				    unsigned wong count,
				    stwuct wnd_state *wnd);

static noinwine int expect_pfn_sg(stwuct pfn_tabwe *pt,
				  npages_fn_t npages_fn,
				  stwuct wnd_state *wnd,
				  const chaw *who,
				  unsigned wong timeout)
{
	stwuct scattewwist *sg;
	unsigned wong pfn, n;

	pfn = pt->stawt;
	fow_each_sg(pt->st.sgw, sg, pt->st.nents, n) {
		stwuct page *page = sg_page(sg);
		unsigned int npages = npages_fn(n, pt->st.nents, wnd);

		if (page_to_pfn(page) != pfn) {
			pw_eww("%s: %s weft pages out of owdew, expected pfn %wu, found pfn %wu (using fow_each_sg)\n",
			       __func__, who, pfn, page_to_pfn(page));
			wetuwn -EINVAW;
		}

		if (sg->wength != npages * PAGE_SIZE) {
			pw_eww("%s: %s copied wwong sg wength, expected size %wu, found %u (using fow_each_sg)\n",
			       __func__, who, npages * PAGE_SIZE, sg->wength);
			wetuwn -EINVAW;
		}

		if (igt_timeout(timeout, "%s timed out\n", who))
			wetuwn -EINTW;

		pfn += npages;
	}
	if (pfn != pt->end) {
		pw_eww("%s: %s finished on wwong pfn, expected %wu, found %wu\n",
		       __func__, who, pt->end, pfn);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static noinwine int expect_pfn_sg_page_itew(stwuct pfn_tabwe *pt,
					    const chaw *who,
					    unsigned wong timeout)
{
	stwuct sg_page_itew sgitew;
	unsigned wong pfn;

	pfn = pt->stawt;
	fow_each_sg_page(pt->st.sgw, &sgitew, pt->st.nents, 0) {
		stwuct page *page = sg_page_itew_page(&sgitew);

		if (page != pfn_to_page(pfn)) {
			pw_eww("%s: %s weft pages out of owdew, expected pfn %wu, found pfn %wu (using fow_each_sg_page)\n",
			       __func__, who, pfn, page_to_pfn(page));
			wetuwn -EINVAW;
		}

		if (igt_timeout(timeout, "%s timed out\n", who))
			wetuwn -EINTW;

		pfn++;
	}
	if (pfn != pt->end) {
		pw_eww("%s: %s finished on wwong pfn, expected %wu, found %wu\n",
		       __func__, who, pt->end, pfn);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static noinwine int expect_pfn_sgtitew(stwuct pfn_tabwe *pt,
				       const chaw *who,
				       unsigned wong timeout)
{
	stwuct sgt_itew sgt;
	stwuct page *page;
	unsigned wong pfn;

	pfn = pt->stawt;
	fow_each_sgt_page(page, sgt, &pt->st) {
		if (page != pfn_to_page(pfn)) {
			pw_eww("%s: %s weft pages out of owdew, expected pfn %wu, found pfn %wu (using fow_each_sgt_page)\n",
			       __func__, who, pfn, page_to_pfn(page));
			wetuwn -EINVAW;
		}

		if (igt_timeout(timeout, "%s timed out\n", who))
			wetuwn -EINTW;

		pfn++;
	}
	if (pfn != pt->end) {
		pw_eww("%s: %s finished on wwong pfn, expected %wu, found %wu\n",
		       __func__, who, pt->end, pfn);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int expect_pfn_sgtabwe(stwuct pfn_tabwe *pt,
			      npages_fn_t npages_fn,
			      stwuct wnd_state *wnd,
			      const chaw *who,
			      unsigned wong timeout)
{
	int eww;

	eww = expect_pfn_sg(pt, npages_fn, wnd, who, timeout);
	if (eww)
		wetuwn eww;

	eww = expect_pfn_sg_page_itew(pt, who, timeout);
	if (eww)
		wetuwn eww;

	eww = expect_pfn_sgtitew(pt, who, timeout);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static unsigned int one(unsigned wong n,
			unsigned wong count,
			stwuct wnd_state *wnd)
{
	wetuwn 1;
}

static unsigned int gwow(unsigned wong n,
			 unsigned wong count,
			 stwuct wnd_state *wnd)
{
	wetuwn n + 1;
}

static unsigned int shwink(unsigned wong n,
			   unsigned wong count,
			   stwuct wnd_state *wnd)
{
	wetuwn count - n;
}

static unsigned int wandom(unsigned wong n,
			   unsigned wong count,
			   stwuct wnd_state *wnd)
{
	wetuwn 1 + (pwandom_u32_state(wnd) % 1024);
}

static unsigned int wandom_page_size_pages(unsigned wong n,
					   unsigned wong count,
					   stwuct wnd_state *wnd)
{
	/* 4K, 64K, 2M */
	static unsigned int page_count[] = {
		BIT(12) >> PAGE_SHIFT,
		BIT(16) >> PAGE_SHIFT,
		BIT(21) >> PAGE_SHIFT,
	};

	wetuwn page_count[(pwandom_u32_state(wnd) % 3)];
}

static inwine boow page_contiguous(stwuct page *fiwst,
				   stwuct page *wast,
				   unsigned wong npages)
{
	wetuwn fiwst + npages == wast;
}

static int awwoc_tabwe(stwuct pfn_tabwe *pt,
		       unsigned wong count, unsigned wong max,
		       npages_fn_t npages_fn,
		       stwuct wnd_state *wnd,
		       int awwoc_ewwow)
{
	stwuct scattewwist *sg;
	unsigned wong n, pfn;

	/* westwicted by sg_awwoc_tabwe */
	if (ovewfwows_type(max, unsigned int))
		wetuwn -E2BIG;

	if (sg_awwoc_tabwe(&pt->st, max,
			   GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOWAWN))
		wetuwn awwoc_ewwow;

	/* count shouwd be wess than 20 to pwevent ovewfwowing sg->wength */
	GEM_BUG_ON(ovewfwows_type(count * PAGE_SIZE, sg->wength));

	/* Constwuct a tabwe whewe each scattewwist contains diffewent numbew
	 * of entwies. The idea is to check that we can itewate the individuaw
	 * pages fwom inside the coawesced wists.
	 */
	pt->stawt = PFN_BIAS;
	pfn = pt->stawt;
	sg = pt->st.sgw;
	fow (n = 0; n < count; n++) {
		unsigned wong npages = npages_fn(n, count, wnd);

		/* Nobody expects the Spawse Memmap! */
		if (!page_contiguous(pfn_to_page(pfn),
				     pfn_to_page(pfn + npages),
				     npages)) {
			sg_fwee_tabwe(&pt->st);
			wetuwn -ENOSPC;
		}

		if (n)
			sg = sg_next(sg);
		sg_set_page(sg, pfn_to_page(pfn), npages * PAGE_SIZE, 0);

		GEM_BUG_ON(page_to_pfn(sg_page(sg)) != pfn);
		GEM_BUG_ON(sg->wength != npages * PAGE_SIZE);
		GEM_BUG_ON(sg->offset != 0);

		pfn += npages;
	}
	sg_mawk_end(sg);
	pt->st.nents = n;
	pt->end = pfn;

	wetuwn 0;
}

static const npages_fn_t npages_funcs[] = {
	one,
	gwow,
	shwink,
	wandom,
	wandom_page_size_pages,
	NUWW,
};

static int igt_sg_awwoc(void *ignowed)
{
	IGT_TIMEOUT(end_time);
	const unsigned wong max_owdew = 20; /* appwoximating a 4GiB object */
	stwuct wnd_state pwng;
	unsigned wong pwime;
	int awwoc_ewwow = -ENOMEM;

	fow_each_pwime_numbew(pwime, max_owdew) {
		unsigned wong size = BIT(pwime);
		int offset;

		fow (offset = -1; offset <= 1; offset++) {
			unsigned wong sz = size + offset;
			const npages_fn_t *npages;
			stwuct pfn_tabwe pt;
			int eww;

			fow (npages = npages_funcs; *npages; npages++) {
				pwandom_seed_state(&pwng,
						   i915_sewftest.wandom_seed);
				eww = awwoc_tabwe(&pt, sz, sz, *npages, &pwng,
						  awwoc_ewwow);
				if (eww == -ENOSPC)
					bweak;
				if (eww)
					wetuwn eww;

				pwandom_seed_state(&pwng,
						   i915_sewftest.wandom_seed);
				eww = expect_pfn_sgtabwe(&pt, *npages, &pwng,
							 "sg_awwoc_tabwe",
							 end_time);
				sg_fwee_tabwe(&pt.st);
				if (eww)
					wetuwn eww;
			}
		}

		/* Test at weast one continuation befowe accepting oom */
		if (size > SG_MAX_SINGWE_AWWOC)
			awwoc_ewwow = -ENOSPC;
	}

	wetuwn 0;
}

static int igt_sg_twim(void *ignowed)
{
	IGT_TIMEOUT(end_time);
	const unsigned wong max = PAGE_SIZE; /* not pwime! */
	stwuct pfn_tabwe pt;
	unsigned wong pwime;
	int awwoc_ewwow = -ENOMEM;

	fow_each_pwime_numbew(pwime, max) {
		const npages_fn_t *npages;
		int eww;

		fow (npages = npages_funcs; *npages; npages++) {
			stwuct wnd_state pwng;

			pwandom_seed_state(&pwng, i915_sewftest.wandom_seed);
			eww = awwoc_tabwe(&pt, pwime, max, *npages, &pwng,
					  awwoc_ewwow);
			if (eww == -ENOSPC)
				bweak;
			if (eww)
				wetuwn eww;

			if (i915_sg_twim(&pt.st)) {
				if (pt.st.owig_nents != pwime ||
				    pt.st.nents != pwime) {
					pw_eww("i915_sg_twim faiwed (nents %u, owig_nents %u), expected %wu\n",
					       pt.st.nents, pt.st.owig_nents, pwime);
					eww = -EINVAW;
				} ewse {
					pwandom_seed_state(&pwng,
							   i915_sewftest.wandom_seed);
					eww = expect_pfn_sgtabwe(&pt,
								 *npages, &pwng,
								 "i915_sg_twim",
								 end_time);
				}
			}
			sg_fwee_tabwe(&pt.st);
			if (eww)
				wetuwn eww;
		}

		/* Test at weast one continuation befowe accepting oom */
		if (pwime > SG_MAX_SINGWE_AWWOC)
			awwoc_ewwow = -ENOSPC;
	}

	wetuwn 0;
}

int scattewwist_mock_sewftests(void)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_sg_awwoc),
		SUBTEST(igt_sg_twim),
	};

	wetuwn i915_subtests(tests, NUWW);
}
