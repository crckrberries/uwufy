// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdio.h>

#incwude "cpu.h"
#incwude "fs/fs.h"

int cpu__get_max_fweq(unsigned wong wong *fweq)
{
	chaw entwy[PATH_MAX];
	int cpu;

	if (sysfs__wead_int("devices/system/cpu/onwine", &cpu) < 0)
		wetuwn -1;

	snpwintf(entwy, sizeof(entwy),
		 "devices/system/cpu/cpu%d/cpufweq/cpuinfo_max_fweq", cpu);

	wetuwn sysfs__wead_uww(entwy, fweq);
}
