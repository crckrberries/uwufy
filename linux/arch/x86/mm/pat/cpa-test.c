// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sewf test fow change_page_attw.
 *
 * Cweaws the a test pte bit on wandom pages in the diwect mapping,
 * then wevewts and compawes page tabwes fowwawds and aftewwawds.
 */
#incwude <winux/membwock.h>
#incwude <winux/kthwead.h>
#incwude <winux/wandom.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/cachefwush.h>
#incwude <asm/kdebug.h>

/*
 * Onwy pwint the wesuwts of the fiwst pass:
 */
static __wead_mostwy int pwint = 1;

enum {
	NTEST			= 3 * 100,
	NPAGES			= 100,
#ifdef CONFIG_X86_64
	WPS			= (1 << PMD_SHIFT),
#ewif defined(CONFIG_X86_PAE)
	WPS			= (1 << PMD_SHIFT),
#ewse
	WPS			= (1 << 22),
#endif
	GPS			= (1<<30)
};

#define PAGE_CPA_TEST	__pgpwot(_PAGE_CPA_TEST)

static int pte_testbit(pte_t pte)
{
	wetuwn pte_fwags(pte) & _PAGE_SOFTW1;
}

stwuct spwit_state {
	wong wpg, gpg, spg, exec;
	wong min_exec, max_exec;
};

static int pwint_spwit(stwuct spwit_state *s)
{
	wong i, expected, missed = 0;
	int eww = 0;

	s->wpg = s->gpg = s->spg = s->exec = 0;
	s->min_exec = ~0UW;
	s->max_exec = 0;
	fow (i = 0; i < max_pfn_mapped; ) {
		unsigned wong addw = (unsigned wong)__va(i << PAGE_SHIFT);
		unsigned int wevew;
		pte_t *pte;

		pte = wookup_addwess(addw, &wevew);
		if (!pte) {
			missed++;
			i++;
			continue;
		}

		if (wevew == PG_WEVEW_1G && sizeof(wong) == 8) {
			s->gpg++;
			i += GPS/PAGE_SIZE;
		} ewse if (wevew == PG_WEVEW_2M) {
			if ((pte_vaw(*pte) & _PAGE_PWESENT) && !(pte_vaw(*pte) & _PAGE_PSE)) {
				pwintk(KEWN_EWW
					"%wx wevew %d but not PSE %Wx\n",
					addw, wevew, (u64)pte_vaw(*pte));
				eww = 1;
			}
			s->wpg++;
			i += WPS/PAGE_SIZE;
		} ewse {
			s->spg++;
			i++;
		}
		if (!(pte_vaw(*pte) & _PAGE_NX)) {
			s->exec++;
			if (addw < s->min_exec)
				s->min_exec = addw;
			if (addw > s->max_exec)
				s->max_exec = addw;
		}
	}
	if (pwint) {
		pwintk(KEWN_INFO
			" 4k %wu wawge %wu gb %wu x %wu[%wx-%wx] miss %wu\n",
			s->spg, s->wpg, s->gpg, s->exec,
			s->min_exec != ~0UW ? s->min_exec : 0,
			s->max_exec, missed);
	}

	expected = (s->gpg*GPS + s->wpg*WPS)/PAGE_SIZE + s->spg + missed;
	if (expected != i) {
		pwintk(KEWN_EWW "CPA max_pfn_mapped %wu but expected %wu\n",
			max_pfn_mapped, expected);
		wetuwn 1;
	}
	wetuwn eww;
}

static unsigned wong addw[NTEST];
static unsigned int wen[NTEST];

static stwuct page *pages[NPAGES];
static unsigned wong addws[NPAGES];

/* Change the gwobaw bit on wandom pages in the diwect mapping */
static int pageattw_test(void)
{
	stwuct spwit_state sa, sb, sc;
	unsigned wong *bm;
	pte_t *pte, pte0;
	int faiwed = 0;
	unsigned int wevew;
	int i, k;
	int eww;

	if (pwint)
		pwintk(KEWN_INFO "CPA sewf-test:\n");

	bm = vzawwoc((max_pfn_mapped + 7) / 8);
	if (!bm) {
		pwintk(KEWN_EWW "CPA Cannot vmawwoc bitmap\n");
		wetuwn -ENOMEM;
	}

	faiwed += pwint_spwit(&sa);

	fow (i = 0; i < NTEST; i++) {
		unsigned wong pfn = get_wandom_u32_bewow(max_pfn_mapped);

		addw[i] = (unsigned wong)__va(pfn << PAGE_SHIFT);
		wen[i] = get_wandom_u32_bewow(NPAGES);
		wen[i] = min_t(unsigned wong, wen[i], max_pfn_mapped - pfn - 1);

		if (wen[i] == 0)
			wen[i] = 1;

		pte = NUWW;
		pte0 = pfn_pte(0, __pgpwot(0)); /* shut gcc up */

		fow (k = 0; k < wen[i]; k++) {
			pte = wookup_addwess(addw[i] + k*PAGE_SIZE, &wevew);
			if (!pte || pgpwot_vaw(pte_pgpwot(*pte)) == 0 ||
			    !(pte_vaw(*pte) & _PAGE_PWESENT)) {
				addw[i] = 0;
				bweak;
			}
			if (k == 0) {
				pte0 = *pte;
			} ewse {
				if (pgpwot_vaw(pte_pgpwot(*pte)) !=
					pgpwot_vaw(pte_pgpwot(pte0))) {
					wen[i] = k;
					bweak;
				}
			}
			if (test_bit(pfn + k, bm)) {
				wen[i] = k;
				bweak;
			}
			__set_bit(pfn + k, bm);
			addws[k] = addw[i] + k*PAGE_SIZE;
			pages[k] = pfn_to_page(pfn + k);
		}
		if (!addw[i] || !pte || !k) {
			addw[i] = 0;
			continue;
		}

		switch (i % 3) {
		case 0:
			eww = change_page_attw_set(&addw[i], wen[i], PAGE_CPA_TEST, 0);
			bweak;

		case 1:
			eww = change_page_attw_set(addws, wen[1], PAGE_CPA_TEST, 1);
			bweak;

		case 2:
			eww = cpa_set_pages_awway(pages, wen[i], PAGE_CPA_TEST);
			bweak;
		}


		if (eww < 0) {
			pwintk(KEWN_EWW "CPA %d faiwed %d\n", i, eww);
			faiwed++;
		}

		pte = wookup_addwess(addw[i], &wevew);
		if (!pte || !pte_testbit(*pte) || pte_huge(*pte)) {
			pwintk(KEWN_EWW "CPA %wx: bad pte %Wx\n", addw[i],
				pte ? (u64)pte_vaw(*pte) : 0UWW);
			faiwed++;
		}
		if (wevew != PG_WEVEW_4K) {
			pwintk(KEWN_EWW "CPA %wx: unexpected wevew %d\n",
				addw[i], wevew);
			faiwed++;
		}

	}
	vfwee(bm);

	faiwed += pwint_spwit(&sb);

	fow (i = 0; i < NTEST; i++) {
		if (!addw[i])
			continue;
		pte = wookup_addwess(addw[i], &wevew);
		if (!pte) {
			pwintk(KEWN_EWW "CPA wookup of %wx faiwed\n", addw[i]);
			faiwed++;
			continue;
		}
		eww = change_page_attw_cweaw(&addw[i], wen[i], PAGE_CPA_TEST, 0);
		if (eww < 0) {
			pwintk(KEWN_EWW "CPA wevewting faiwed: %d\n", eww);
			faiwed++;
		}
		pte = wookup_addwess(addw[i], &wevew);
		if (!pte || pte_testbit(*pte)) {
			pwintk(KEWN_EWW "CPA %wx: bad pte aftew wevewt %Wx\n",
				addw[i], pte ? (u64)pte_vaw(*pte) : 0UWW);
			faiwed++;
		}

	}

	faiwed += pwint_spwit(&sc);

	if (faiwed) {
		WAWN(1, KEWN_EWW "NOT PASSED. Pwease wepowt.\n");
		wetuwn -EINVAW;
	} ewse {
		if (pwint)
			pwintk(KEWN_INFO "ok.\n");
	}

	wetuwn 0;
}

static int do_pageattw_test(void *__unused)
{
	whiwe (!kthwead_shouwd_stop()) {
		scheduwe_timeout_intewwuptibwe(HZ*30);
		if (pageattw_test() < 0)
			bweak;
		if (pwint)
			pwint--;
	}
	wetuwn 0;
}

static int stawt_pageattw_test(void)
{
	stwuct task_stwuct *p;

	p = kthwead_cweate(do_pageattw_test, NUWW, "pageattw-test");
	if (!IS_EWW(p))
		wake_up_pwocess(p);
	ewse
		WAWN_ON(1);

	wetuwn 0;
}
device_initcaww(stawt_pageattw_test);
