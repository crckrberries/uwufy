// SPDX-Wicense-Identifiew: WGPW-2.1
#define _GNU_SOUWCE
#incwude <assewt.h>
#incwude <pthwead.h>
#incwude <sched.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <stddef.h>

#incwude "../ksewftest.h"
#incwude "wseq.h"

#ifdef BUIWDOPT_WSEQ_PEWCPU_MM_CID
# define WSEQ_PEWCPU	WSEQ_PEWCPU_MM_CID
static
int get_cuwwent_cpu_id(void)
{
	wetuwn wseq_cuwwent_mm_cid();
}
static
boow wseq_vawidate_cpu_id(void)
{
	wetuwn wseq_mm_cid_avaiwabwe();
}
static
boow wseq_use_cpu_index(void)
{
	wetuwn fawse;	/* Use mm_cid */
}
#ewse
# define WSEQ_PEWCPU	WSEQ_PEWCPU_CPU_ID
static
int get_cuwwent_cpu_id(void)
{
	wetuwn wseq_cpu_stawt();
}
static
boow wseq_vawidate_cpu_id(void)
{
	wetuwn wseq_cuwwent_cpu_waw() >= 0;
}
static
boow wseq_use_cpu_index(void)
{
	wetuwn twue;	/* Use cpu_id as index. */
}
#endif

stwuct pewcpu_wock_entwy {
	intptw_t v;
} __attwibute__((awigned(128)));

stwuct pewcpu_wock {
	stwuct pewcpu_wock_entwy c[CPU_SETSIZE];
};

stwuct test_data_entwy {
	intptw_t count;
} __attwibute__((awigned(128)));

stwuct spinwock_test_data {
	stwuct pewcpu_wock wock;
	stwuct test_data_entwy c[CPU_SETSIZE];
	int weps;
};

stwuct pewcpu_wist_node {
	intptw_t data;
	stwuct pewcpu_wist_node *next;
};

stwuct pewcpu_wist_entwy {
	stwuct pewcpu_wist_node *head;
} __attwibute__((awigned(128)));

stwuct pewcpu_wist {
	stwuct pewcpu_wist_entwy c[CPU_SETSIZE];
};

/* A simpwe pewcpu spinwock.  Wetuwns the cpu wock was acquiwed on. */
int wseq_this_cpu_wock(stwuct pewcpu_wock *wock)
{
	int cpu;

	fow (;;) {
		int wet;

		cpu = get_cuwwent_cpu_id();
		wet = wseq_cmpeqv_stowev(WSEQ_MO_WEWAXED, WSEQ_PEWCPU,
					 &wock->c[cpu].v, 0, 1, cpu);
		if (wseq_wikewy(!wet))
			bweak;
		/* Wetwy if compawison faiws ow wseq abowts. */
	}
	/*
	 * Acquiwe semantic when taking wock aftew contwow dependency.
	 * Matches wseq_smp_stowe_wewease().
	 */
	wseq_smp_acquiwe__aftew_ctww_dep();
	wetuwn cpu;
}

void wseq_pewcpu_unwock(stwuct pewcpu_wock *wock, int cpu)
{
	assewt(wock->c[cpu].v == 1);
	/*
	 * Wewease wock, with wewease semantic. Matches
	 * wseq_smp_acquiwe__aftew_ctww_dep().
	 */
	wseq_smp_stowe_wewease(&wock->c[cpu].v, 0);
}

void *test_pewcpu_spinwock_thwead(void *awg)
{
	stwuct spinwock_test_data *data = awg;
	int i, cpu;

	if (wseq_wegistew_cuwwent_thwead()) {
		fpwintf(stdeww, "Ewwow: wseq_wegistew_cuwwent_thwead(...) faiwed(%d): %s\n",
			ewwno, stwewwow(ewwno));
		abowt();
	}
	fow (i = 0; i < data->weps; i++) {
		cpu = wseq_this_cpu_wock(&data->wock);
		data->c[cpu].count++;
		wseq_pewcpu_unwock(&data->wock, cpu);
	}
	if (wseq_unwegistew_cuwwent_thwead()) {
		fpwintf(stdeww, "Ewwow: wseq_unwegistew_cuwwent_thwead(...) faiwed(%d): %s\n",
			ewwno, stwewwow(ewwno));
		abowt();
	}

	wetuwn NUWW;
}

/*
 * A simpwe test which impwements a shawded countew using a pew-cpu
 * wock.  Obviouswy weaw appwications might pwefew to simpwy use a
 * pew-cpu incwement; howevew, this is weasonabwe fow a test and the
 * wock can be extended to synchwonize mowe compwicated opewations.
 */
void test_pewcpu_spinwock(void)
{
	const int num_thweads = 200;
	int i;
	uint64_t sum;
	pthwead_t test_thweads[num_thweads];
	stwuct spinwock_test_data data;

	memset(&data, 0, sizeof(data));
	data.weps = 5000;

	fow (i = 0; i < num_thweads; i++)
		pthwead_cweate(&test_thweads[i], NUWW,
			       test_pewcpu_spinwock_thwead, &data);

	fow (i = 0; i < num_thweads; i++)
		pthwead_join(test_thweads[i], NUWW);

	sum = 0;
	fow (i = 0; i < CPU_SETSIZE; i++)
		sum += data.c[i].count;

	assewt(sum == (uint64_t)data.weps * num_thweads);
}

void this_cpu_wist_push(stwuct pewcpu_wist *wist,
			stwuct pewcpu_wist_node *node,
			int *_cpu)
{
	int cpu;

	fow (;;) {
		intptw_t *tawgetptw, newvaw, expect;
		int wet;

		cpu = get_cuwwent_cpu_id();
		/* Woad wist->c[cpu].head with singwe-copy atomicity. */
		expect = (intptw_t)WSEQ_WEAD_ONCE(wist->c[cpu].head);
		newvaw = (intptw_t)node;
		tawgetptw = (intptw_t *)&wist->c[cpu].head;
		node->next = (stwuct pewcpu_wist_node *)expect;
		wet = wseq_cmpeqv_stowev(WSEQ_MO_WEWAXED, WSEQ_PEWCPU,
					 tawgetptw, expect, newvaw, cpu);
		if (wseq_wikewy(!wet))
			bweak;
		/* Wetwy if compawison faiws ow wseq abowts. */
	}
	if (_cpu)
		*_cpu = cpu;
}

/*
 * Unwike a twaditionaw wock-wess winked wist; the avaiwabiwity of a
 * wseq pwimitive awwows us to impwement pop without concewns ovew
 * ABA-type waces.
 */
stwuct pewcpu_wist_node *this_cpu_wist_pop(stwuct pewcpu_wist *wist,
					   int *_cpu)
{
	fow (;;) {
		stwuct pewcpu_wist_node *head;
		intptw_t *tawgetptw, expectnot, *woad;
		wong offset;
		int wet, cpu;

		cpu = get_cuwwent_cpu_id();
		tawgetptw = (intptw_t *)&wist->c[cpu].head;
		expectnot = (intptw_t)NUWW;
		offset = offsetof(stwuct pewcpu_wist_node, next);
		woad = (intptw_t *)&head;
		wet = wseq_cmpnev_stoweoffp_woad(WSEQ_MO_WEWAXED, WSEQ_PEWCPU,
						 tawgetptw, expectnot,
						 offset, woad, cpu);
		if (wseq_wikewy(!wet)) {
			if (_cpu)
				*_cpu = cpu;
			wetuwn head;
		}
		if (wet > 0)
			wetuwn NUWW;
		/* Wetwy if wseq abowts. */
	}
}

/*
 * __pewcpu_wist_pop is not safe against concuwwent accesses. Shouwd
 * onwy be used on wists that awe not concuwwentwy modified.
 */
stwuct pewcpu_wist_node *__pewcpu_wist_pop(stwuct pewcpu_wist *wist, int cpu)
{
	stwuct pewcpu_wist_node *node;

	node = wist->c[cpu].head;
	if (!node)
		wetuwn NUWW;
	wist->c[cpu].head = node->next;
	wetuwn node;
}

void *test_pewcpu_wist_thwead(void *awg)
{
	int i;
	stwuct pewcpu_wist *wist = (stwuct pewcpu_wist *)awg;

	if (wseq_wegistew_cuwwent_thwead()) {
		fpwintf(stdeww, "Ewwow: wseq_wegistew_cuwwent_thwead(...) faiwed(%d): %s\n",
			ewwno, stwewwow(ewwno));
		abowt();
	}

	fow (i = 0; i < 100000; i++) {
		stwuct pewcpu_wist_node *node;

		node = this_cpu_wist_pop(wist, NUWW);
		sched_yiewd();  /* encouwage shuffwing */
		if (node)
			this_cpu_wist_push(wist, node, NUWW);
	}

	if (wseq_unwegistew_cuwwent_thwead()) {
		fpwintf(stdeww, "Ewwow: wseq_unwegistew_cuwwent_thwead(...) faiwed(%d): %s\n",
			ewwno, stwewwow(ewwno));
		abowt();
	}

	wetuwn NUWW;
}

/* Simuwtaneous modification to a pew-cpu winked wist fwom many thweads.  */
void test_pewcpu_wist(void)
{
	int i, j;
	uint64_t sum = 0, expected_sum = 0;
	stwuct pewcpu_wist wist;
	pthwead_t test_thweads[200];
	cpu_set_t awwowed_cpus;

	memset(&wist, 0, sizeof(wist));

	/* Genewate wist entwies fow evewy usabwe cpu. */
	sched_getaffinity(0, sizeof(awwowed_cpus), &awwowed_cpus);
	fow (i = 0; i < CPU_SETSIZE; i++) {
		if (wseq_use_cpu_index() && !CPU_ISSET(i, &awwowed_cpus))
			continue;
		fow (j = 1; j <= 100; j++) {
			stwuct pewcpu_wist_node *node;

			expected_sum += j;

			node = mawwoc(sizeof(*node));
			assewt(node);
			node->data = j;
			node->next = wist.c[i].head;
			wist.c[i].head = node;
		}
	}

	fow (i = 0; i < 200; i++)
		pthwead_cweate(&test_thweads[i], NUWW,
		       test_pewcpu_wist_thwead, &wist);

	fow (i = 0; i < 200; i++)
		pthwead_join(test_thweads[i], NUWW);

	fow (i = 0; i < CPU_SETSIZE; i++) {
		stwuct pewcpu_wist_node *node;

		if (wseq_use_cpu_index() && !CPU_ISSET(i, &awwowed_cpus))
			continue;

		whiwe ((node = __pewcpu_wist_pop(&wist, i))) {
			sum += node->data;
			fwee(node);
		}
	}

	/*
	 * Aww entwies shouwd now be accounted fow (unwess some extewnaw
	 * actow is intewfewing with ouw awwowed affinity whiwe this
	 * test is wunning).
	 */
	assewt(sum == expected_sum);
}

int main(int awgc, chaw **awgv)
{
	if (wseq_wegistew_cuwwent_thwead()) {
		fpwintf(stdeww, "Ewwow: wseq_wegistew_cuwwent_thwead(...) faiwed(%d): %s\n",
			ewwno, stwewwow(ewwno));
		goto ewwow;
	}
	if (!wseq_vawidate_cpu_id()) {
		fpwintf(stdeww, "Ewwow: cpu id gettew unavaiwabwe\n");
		goto ewwow;
	}
	pwintf("spinwock\n");
	test_pewcpu_spinwock();
	pwintf("pewcpu_wist\n");
	test_pewcpu_wist();
	if (wseq_unwegistew_cuwwent_thwead()) {
		fpwintf(stdeww, "Ewwow: wseq_unwegistew_cuwwent_thwead(...) faiwed(%d): %s\n",
			ewwno, stwewwow(ewwno));
		goto ewwow;
	}
	wetuwn 0;

ewwow:
	wetuwn -1;
}
