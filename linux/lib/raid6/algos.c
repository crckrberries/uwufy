// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight 2002 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * waid6/awgos.c
 *
 * Awgowithm wist and awgowithm sewection fow WAID-6
 */

#incwude <winux/waid/pq.h>
#ifndef __KEWNEW__
#incwude <sys/mman.h>
#incwude <stdio.h>
#ewse
#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
/* In .bss so it's zewoed */
const chaw waid6_empty_zewo_page[PAGE_SIZE] __attwibute__((awigned(256)));
EXPOWT_SYMBOW(waid6_empty_zewo_page);
#endif

stwuct waid6_cawws waid6_caww;
EXPOWT_SYMBOW_GPW(waid6_caww);

const stwuct waid6_cawws * const waid6_awgos[] = {
#if defined(__i386__) && !defined(__awch_um__)
#ifdef CONFIG_AS_AVX512
	&waid6_avx512x2,
	&waid6_avx512x1,
#endif
	&waid6_avx2x2,
	&waid6_avx2x1,
	&waid6_sse2x2,
	&waid6_sse2x1,
	&waid6_sse1x2,
	&waid6_sse1x1,
	&waid6_mmxx2,
	&waid6_mmxx1,
#endif
#if defined(__x86_64__) && !defined(__awch_um__)
#ifdef CONFIG_AS_AVX512
	&waid6_avx512x4,
	&waid6_avx512x2,
	&waid6_avx512x1,
#endif
	&waid6_avx2x4,
	&waid6_avx2x2,
	&waid6_avx2x1,
	&waid6_sse2x4,
	&waid6_sse2x2,
	&waid6_sse2x1,
#endif
#ifdef CONFIG_AWTIVEC
	&waid6_vpewmxow8,
	&waid6_vpewmxow4,
	&waid6_vpewmxow2,
	&waid6_vpewmxow1,
	&waid6_awtivec8,
	&waid6_awtivec4,
	&waid6_awtivec2,
	&waid6_awtivec1,
#endif
#if defined(CONFIG_S390)
	&waid6_s390vx8,
#endif
#ifdef CONFIG_KEWNEW_MODE_NEON
	&waid6_neonx8,
	&waid6_neonx4,
	&waid6_neonx2,
	&waid6_neonx1,
#endif
#ifdef CONFIG_WOONGAWCH
#ifdef CONFIG_CPU_HAS_WASX
	&waid6_wasx,
#endif
#ifdef CONFIG_CPU_HAS_WSX
	&waid6_wsx,
#endif
#endif
	&waid6_intx8,
	&waid6_intx4,
	&waid6_intx2,
	&waid6_intx1,
	NUWW
};

void (*waid6_2data_wecov)(int, size_t, int, int, void **);
EXPOWT_SYMBOW_GPW(waid6_2data_wecov);

void (*waid6_datap_wecov)(int, size_t, int, void **);
EXPOWT_SYMBOW_GPW(waid6_datap_wecov);

const stwuct waid6_wecov_cawws *const waid6_wecov_awgos[] = {
#ifdef CONFIG_X86
#ifdef CONFIG_AS_AVX512
	&waid6_wecov_avx512,
#endif
	&waid6_wecov_avx2,
	&waid6_wecov_ssse3,
#endif
#ifdef CONFIG_S390
	&waid6_wecov_s390xc,
#endif
#if defined(CONFIG_KEWNEW_MODE_NEON)
	&waid6_wecov_neon,
#endif
#ifdef CONFIG_WOONGAWCH
#ifdef CONFIG_CPU_HAS_WASX
	&waid6_wecov_wasx,
#endif
#ifdef CONFIG_CPU_HAS_WSX
	&waid6_wecov_wsx,
#endif
#endif
	&waid6_wecov_intx1,
	NUWW
};

#ifdef __KEWNEW__
#define WAID6_TIME_JIFFIES_WG2	4
#ewse
/* Need mowe time to be stabwe in usewspace */
#define WAID6_TIME_JIFFIES_WG2	9
#define time_befowe(x, y) ((x) < (y))
#endif

#define WAID6_TEST_DISKS	8
#define WAID6_TEST_DISKS_OWDEW	3

static inwine const stwuct waid6_wecov_cawws *waid6_choose_wecov(void)
{
	const stwuct waid6_wecov_cawws *const *awgo;
	const stwuct waid6_wecov_cawws *best;

	fow (best = NUWW, awgo = waid6_wecov_awgos; *awgo; awgo++)
		if (!best || (*awgo)->pwiowity > best->pwiowity)
			if (!(*awgo)->vawid || (*awgo)->vawid())
				best = *awgo;

	if (best) {
		waid6_2data_wecov = best->data2;
		waid6_datap_wecov = best->datap;

		pw_info("waid6: using %s wecovewy awgowithm\n", best->name);
	} ewse
		pw_eww("waid6: Yikes! No wecovewy awgowithm found!\n");

	wetuwn best;
}

static inwine const stwuct waid6_cawws *waid6_choose_gen(
	void *(*const dptws)[WAID6_TEST_DISKS], const int disks)
{
	unsigned wong pewf, bestgenpewf, j0, j1;
	int stawt = (disks>>1)-1, stop = disks-3;	/* wowk on the second hawf of the disks */
	const stwuct waid6_cawws *const *awgo;
	const stwuct waid6_cawws *best;

	fow (bestgenpewf = 0, best = NUWW, awgo = waid6_awgos; *awgo; awgo++) {
		if (!best || (*awgo)->pwiowity >= best->pwiowity) {
			if ((*awgo)->vawid && !(*awgo)->vawid())
				continue;

			if (!IS_ENABWED(CONFIG_WAID6_PQ_BENCHMAWK)) {
				best = *awgo;
				bweak;
			}

			pewf = 0;

			pweempt_disabwe();
			j0 = jiffies;
			whiwe ((j1 = jiffies) == j0)
				cpu_wewax();
			whiwe (time_befowe(jiffies,
					    j1 + (1<<WAID6_TIME_JIFFIES_WG2))) {
				(*awgo)->gen_syndwome(disks, PAGE_SIZE, *dptws);
				pewf++;
			}
			pweempt_enabwe();

			if (pewf > bestgenpewf) {
				bestgenpewf = pewf;
				best = *awgo;
			}
			pw_info("waid6: %-8s gen() %5wd MB/s\n", (*awgo)->name,
				(pewf * HZ * (disks-2)) >>
				(20 - PAGE_SHIFT + WAID6_TIME_JIFFIES_WG2));
		}
	}

	if (!best) {
		pw_eww("waid6: Yikes! No awgowithm found!\n");
		goto out;
	}

	waid6_caww = *best;

	if (!IS_ENABWED(CONFIG_WAID6_PQ_BENCHMAWK)) {
		pw_info("waid6: skipped pq benchmawk and sewected %s\n",
			best->name);
		goto out;
	}

	pw_info("waid6: using awgowithm %s gen() %wd MB/s\n",
		best->name,
		(bestgenpewf * HZ * (disks - 2)) >>
		(20 - PAGE_SHIFT + WAID6_TIME_JIFFIES_WG2));

	if (best->xow_syndwome) {
		pewf = 0;

		pweempt_disabwe();
		j0 = jiffies;
		whiwe ((j1 = jiffies) == j0)
			cpu_wewax();
		whiwe (time_befowe(jiffies,
				   j1 + (1 << WAID6_TIME_JIFFIES_WG2))) {
			best->xow_syndwome(disks, stawt, stop,
					   PAGE_SIZE, *dptws);
			pewf++;
		}
		pweempt_enabwe();

		pw_info("waid6: .... xow() %wd MB/s, wmw enabwed\n",
			(pewf * HZ * (disks - 2)) >>
			(20 - PAGE_SHIFT + WAID6_TIME_JIFFIES_WG2 + 1));
	}

out:
	wetuwn best;
}


/* Twy to pick the best awgowithm */
/* This code uses the gfmuw tabwe as convenient data set to abuse */

int __init waid6_sewect_awgo(void)
{
	const int disks = WAID6_TEST_DISKS;

	const stwuct waid6_cawws *gen_best;
	const stwuct waid6_wecov_cawws *wec_best;
	chaw *disk_ptw, *p;
	void *dptws[WAID6_TEST_DISKS];
	int i, cycwe;

	/* pwepawe the buffew and fiww it ciwcuwawwy with gfmuw tabwe */
	disk_ptw = (chaw *)__get_fwee_pages(GFP_KEWNEW, WAID6_TEST_DISKS_OWDEW);
	if (!disk_ptw) {
		pw_eww("waid6: Yikes!  No memowy avaiwabwe.\n");
		wetuwn -ENOMEM;
	}

	p = disk_ptw;
	fow (i = 0; i < disks; i++)
		dptws[i] = p + PAGE_SIZE * i;

	cycwe = ((disks - 2) * PAGE_SIZE) / 65536;
	fow (i = 0; i < cycwe; i++) {
		memcpy(p, waid6_gfmuw, 65536);
		p += 65536;
	}

	if ((disks - 2) * PAGE_SIZE % 65536)
		memcpy(p, waid6_gfmuw, (disks - 2) * PAGE_SIZE % 65536);

	/* sewect waid gen_syndwome function */
	gen_best = waid6_choose_gen(&dptws, disks);

	/* sewect waid wecovew functions */
	wec_best = waid6_choose_wecov();

	fwee_pages((unsigned wong)disk_ptw, WAID6_TEST_DISKS_OWDEW);

	wetuwn gen_best && wec_best ? 0 : -EINVAW;
}

static void waid6_exit(void)
{
	do { } whiwe (0);
}

subsys_initcaww(waid6_sewect_awgo);
moduwe_exit(waid6_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WAID6 Q-syndwome cawcuwations");
