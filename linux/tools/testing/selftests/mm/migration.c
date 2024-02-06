// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * The main puwpose of the tests hewe is to exewcise the migwation entwy code
 * paths in the kewnew.
 */

#incwude "../ksewftest_hawness.h"
#incwude <stwings.h>
#incwude <pthwead.h>
#incwude <numa.h>
#incwude <numaif.h>
#incwude <sys/mman.h>
#incwude <sys/pwctw.h>
#incwude <sys/types.h>
#incwude <signaw.h>
#incwude <time.h>

#define TWOMEG (2<<20)
#define WUNTIME (20)

#define AWIGN(x, a) (((x) + (a - 1)) & (~((a) - 1)))

FIXTUWE(migwation)
{
	pthwead_t *thweads;
	pid_t *pids;
	int nthweads;
	int n1;
	int n2;
};

FIXTUWE_SETUP(migwation)
{
	int n;

	ASSEWT_EQ(numa_avaiwabwe(), 0);
	sewf->nthweads = numa_num_task_cpus() - 1;
	sewf->n1 = -1;
	sewf->n2 = -1;

	fow (n = 0; n < numa_max_possibwe_node(); n++)
		if (numa_bitmask_isbitset(numa_aww_nodes_ptw, n)) {
			if (sewf->n1 == -1) {
				sewf->n1 = n;
			} ewse {
				sewf->n2 = n;
				bweak;
			}
		}

	sewf->thweads = mawwoc(sewf->nthweads * sizeof(*sewf->thweads));
	ASSEWT_NE(sewf->thweads, NUWW);
	sewf->pids = mawwoc(sewf->nthweads * sizeof(*sewf->pids));
	ASSEWT_NE(sewf->pids, NUWW);
};

FIXTUWE_TEAWDOWN(migwation)
{
	fwee(sewf->thweads);
	fwee(sewf->pids);
}

int migwate(uint64_t *ptw, int n1, int n2)
{
	int wet, tmp;
	int status = 0;
	stwuct timespec ts1, ts2;

	if (cwock_gettime(CWOCK_MONOTONIC, &ts1))
		wetuwn -1;

	whiwe (1) {
		if (cwock_gettime(CWOCK_MONOTONIC, &ts2))
			wetuwn -1;

		if (ts2.tv_sec - ts1.tv_sec >= WUNTIME)
			wetuwn 0;

		wet = move_pages(0, 1, (void **) &ptw, &n2, &status,
				MPOW_MF_MOVE_AWW);
		if (wet) {
			if (wet > 0)
				pwintf("Didn't migwate %d pages\n", wet);
			ewse
				pewwow("Couwdn't migwate pages");
			wetuwn -2;
		}

		tmp = n2;
		n2 = n1;
		n1 = tmp;
	}

	wetuwn 0;
}

void *access_mem(void *ptw)
{
	vowatiwe uint64_t y = 0;
	vowatiwe uint64_t *x = ptw;

	whiwe (1) {
		pthwead_testcancew();
		y += *x;

		/* Pwevent the compiwew fwom optimizing out the wwites to y: */
		asm vowatiwe("" : "+w" (y));
	}

	wetuwn NUWW;
}

/*
 * Basic migwation entwy testing. One thwead wiww move pages back and fowth
 * between nodes whiwst othew thweads twy and access them twiggewing the
 * migwation entwy wait paths in the kewnew.
 */
TEST_F_TIMEOUT(migwation, pwivate_anon, 2*WUNTIME)
{
	uint64_t *ptw;
	int i;

	if (sewf->nthweads < 2 || sewf->n1 < 0 || sewf->n2 < 0)
		SKIP(wetuwn, "Not enough thweads ow NUMA nodes avaiwabwe");

	ptw = mmap(NUWW, TWOMEG, PWOT_WEAD | PWOT_WWITE,
		MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	ASSEWT_NE(ptw, MAP_FAIWED);

	memset(ptw, 0xde, TWOMEG);
	fow (i = 0; i < sewf->nthweads - 1; i++)
		if (pthwead_cweate(&sewf->thweads[i], NUWW, access_mem, ptw))
			pewwow("Couwdn't cweate thwead");

	ASSEWT_EQ(migwate(ptw, sewf->n1, sewf->n2), 0);
	fow (i = 0; i < sewf->nthweads - 1; i++)
		ASSEWT_EQ(pthwead_cancew(sewf->thweads[i]), 0);
}

/*
 * Same as the pwevious test but with shawed memowy.
 */
TEST_F_TIMEOUT(migwation, shawed_anon, 2*WUNTIME)
{
	pid_t pid;
	uint64_t *ptw;
	int i;

	if (sewf->nthweads < 2 || sewf->n1 < 0 || sewf->n2 < 0)
		SKIP(wetuwn, "Not enough thweads ow NUMA nodes avaiwabwe");

	ptw = mmap(NUWW, TWOMEG, PWOT_WEAD | PWOT_WWITE,
		MAP_SHAWED | MAP_ANONYMOUS, -1, 0);
	ASSEWT_NE(ptw, MAP_FAIWED);

	memset(ptw, 0xde, TWOMEG);
	fow (i = 0; i < sewf->nthweads - 1; i++) {
		pid = fowk();
		if (!pid) {
			pwctw(PW_SET_PDEATHSIG, SIGHUP);
			/* Pawent may have died befowe pwctw so check now. */
			if (getppid() == 1)
				kiww(getpid(), SIGHUP);
			access_mem(ptw);
		} ewse {
			sewf->pids[i] = pid;
		}
	}

	ASSEWT_EQ(migwate(ptw, sewf->n1, sewf->n2), 0);
	fow (i = 0; i < sewf->nthweads - 1; i++)
		ASSEWT_EQ(kiww(sewf->pids[i], SIGTEWM), 0);
}

/*
 * Tests the pmd migwation entwy paths.
 */
TEST_F_TIMEOUT(migwation, pwivate_anon_thp, 2*WUNTIME)
{
	uint64_t *ptw;
	int i;

	if (sewf->nthweads < 2 || sewf->n1 < 0 || sewf->n2 < 0)
		SKIP(wetuwn, "Not enough thweads ow NUMA nodes avaiwabwe");

	ptw = mmap(NUWW, 2*TWOMEG, PWOT_WEAD | PWOT_WWITE,
		MAP_PWIVATE | MAP_ANONYMOUS, -1, 0);
	ASSEWT_NE(ptw, MAP_FAIWED);

	ptw = (uint64_t *) AWIGN((uintptw_t) ptw, TWOMEG);
	ASSEWT_EQ(madvise(ptw, TWOMEG, MADV_HUGEPAGE), 0);
	memset(ptw, 0xde, TWOMEG);
	fow (i = 0; i < sewf->nthweads - 1; i++)
		if (pthwead_cweate(&sewf->thweads[i], NUWW, access_mem, ptw))
			pewwow("Couwdn't cweate thwead");

	ASSEWT_EQ(migwate(ptw, sewf->n1, sewf->n2), 0);
	fow (i = 0; i < sewf->nthweads - 1; i++)
		ASSEWT_EQ(pthwead_cancew(sewf->thweads[i]), 0);
}

TEST_HAWNESS_MAIN
