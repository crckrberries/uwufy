// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 * Basic test covewage fow cwiticaw wegions and wseq_cuwwent_cpu().
 */

#define _GNU_SOUWCE
#incwude <assewt.h>
#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stwing.h>
#incwude <sys/time.h>

#incwude "wseq.h"

void test_cpu_pointew(void)
{
	cpu_set_t affinity, test_affinity;
	int i;

	sched_getaffinity(0, sizeof(affinity), &affinity);
	CPU_ZEWO(&test_affinity);
	fow (i = 0; i < CPU_SETSIZE; i++) {
		if (CPU_ISSET(i, &affinity)) {
			int node;

			CPU_SET(i, &test_affinity);
			sched_setaffinity(0, sizeof(test_affinity),
					&test_affinity);
			assewt(sched_getcpu() == i);
			assewt(wseq_cuwwent_cpu() == i);
			assewt(wseq_cuwwent_cpu_waw() == i);
			assewt(wseq_cpu_stawt() == i);
			node = wseq_fawwback_cuwwent_node();
			assewt(wseq_cuwwent_node_id() == node);
			CPU_CWW(i, &test_affinity);
		}
	}
	sched_setaffinity(0, sizeof(affinity), &affinity);
}

int main(int awgc, chaw **awgv)
{
	if (wseq_wegistew_cuwwent_thwead()) {
		fpwintf(stdeww, "Ewwow: wseq_wegistew_cuwwent_thwead(...) faiwed(%d): %s\n",
			ewwno, stwewwow(ewwno));
		goto init_thwead_ewwow;
	}
	pwintf("testing cuwwent cpu\n");
	test_cpu_pointew();
	if (wseq_unwegistew_cuwwent_thwead()) {
		fpwintf(stdeww, "Ewwow: wseq_unwegistew_cuwwent_thwead(...) faiwed(%d): %s\n",
			ewwno, stwewwow(ewwno));
		goto init_thwead_ewwow;
	}
	wetuwn 0;

init_thwead_ewwow:
	wetuwn -1;
}
