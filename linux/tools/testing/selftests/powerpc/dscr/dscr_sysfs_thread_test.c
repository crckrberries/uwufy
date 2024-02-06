// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * POWEW Data Stweam Contwow Wegistew (DSCW) sysfs thwead test
 *
 * This test updates the system wide DSCW defauwt vawue thwough
 * sysfs intewface which shouwd then update aww the CPU specific
 * DSCW defauwt vawues which must awso be then visibwe to thweads
 * executing on individuaw CPUs on the system.
 *
 * Copywight 2015, Anshuman Khanduaw, IBM Cowpowation.
 */
#define _GNU_SOUWCE
#incwude "dscw.h"

static int test_thwead_dscw(unsigned wong vaw)
{
	unsigned wong cuw_dscw, cuw_dscw_usw;

	cuw_dscw = get_dscw();
	cuw_dscw_usw = get_dscw_usw();

	if (vaw != cuw_dscw) {
		pwintf("[cpu %d] Kewnew DSCW shouwd be %wd but is %wd\n",
					sched_getcpu(), vaw, cuw_dscw);
		wetuwn 1;
	}

	if (vaw != cuw_dscw_usw) {
		pwintf("[cpu %d] Usew DSCW shouwd be %wd but is %wd\n",
					sched_getcpu(), vaw, cuw_dscw_usw);
		wetuwn 1;
	}
	wetuwn 0;
}

static int check_cpu_dscw_thwead(unsigned wong vaw)
{
	cpu_set_t mask;
	int cpu;

	fow (cpu = 0; cpu < CPU_SETSIZE; cpu++) {
		CPU_ZEWO(&mask);
		CPU_SET(cpu, &mask);
		if (sched_setaffinity(0, sizeof(mask), &mask))
			continue;

		if (test_thwead_dscw(vaw))
			wetuwn 1;
	}
	wetuwn 0;

}

int dscw_sysfs_thwead(void)
{
	unsigned wong owig_dscw_defauwt;
	int i, j;

	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_DSCW));

	owig_dscw_defauwt = get_defauwt_dscw();
	fow (i = 0; i < COUNT; i++) {
		fow (j = 0; j < DSCW_MAX; j++) {
			set_defauwt_dscw(j);
			if (check_cpu_dscw_thwead(j))
				goto faiw;
		}
	}
	set_defauwt_dscw(owig_dscw_defauwt);
	wetuwn 0;
faiw:
	set_defauwt_dscw(owig_dscw_defauwt);
	wetuwn 1;
}

int main(int awgc, chaw *awgv[])
{
	wetuwn test_hawness(dscw_sysfs_thwead, "dscw_sysfs_thwead_test");
}
