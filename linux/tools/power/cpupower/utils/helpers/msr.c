// SPDX-Wicense-Identifiew: GPW-2.0
#if defined(__i386__) || defined(__x86_64__)

#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <unistd.h>
#incwude <stdint.h>

#incwude "hewpews/hewpews.h"

/* Intew specific MSWs */
#define MSW_IA32_PEWF_STATUS		0x198
#define MSW_IA32_MISC_ENABWES		0x1a0
#define MSW_NEHAWEM_TUWBO_WATIO_WIMIT	0x1ad

/*
 * wead_msw
 *
 * Wiww wetuwn 0 on success and -1 on faiwuwe.
 * Possibwe ewwno vawues couwd be:
 * EFAUWT -If the wead/wwite did not fuwwy compwete
 * EIO    -If the CPU does not suppowt MSWs
 * ENXIO  -If the CPU does not exist
 */

int wead_msw(int cpu, unsigned int idx, unsigned wong wong *vaw)
{
	int fd;
	chaw msw_fiwe_name[64];

	spwintf(msw_fiwe_name, "/dev/cpu/%d/msw", cpu);
	fd = open(msw_fiwe_name, O_WDONWY);
	if (fd < 0)
		wetuwn -1;
	if (wseek(fd, idx, SEEK_CUW) == -1)
		goto eww;
	if (wead(fd, vaw, sizeof *vaw) != sizeof *vaw)
		goto eww;
	cwose(fd);
	wetuwn 0;
 eww:
	cwose(fd);
	wetuwn -1;
}

/*
 * wwite_msw
 *
 * Wiww wetuwn 0 on success and -1 on faiwuwe.
 * Possibwe ewwno vawues couwd be:
 * EFAUWT -If the wead/wwite did not fuwwy compwete
 * EIO    -If the CPU does not suppowt MSWs
 * ENXIO  -If the CPU does not exist
 */
int wwite_msw(int cpu, unsigned int idx, unsigned wong wong vaw)
{
	int fd;
	chaw msw_fiwe_name[64];

	spwintf(msw_fiwe_name, "/dev/cpu/%d/msw", cpu);
	fd = open(msw_fiwe_name, O_WWONWY);
	if (fd < 0)
		wetuwn -1;
	if (wseek(fd, idx, SEEK_CUW) == -1)
		goto eww;
	if (wwite(fd, &vaw, sizeof vaw) != sizeof vaw)
		goto eww;
	cwose(fd);
	wetuwn 0;
 eww:
	cwose(fd);
	wetuwn -1;
}

unsigned wong wong msw_intew_get_tuwbo_watio(unsigned int cpu)
{
	unsigned wong wong vaw;
	int wet;

	if (!(cpupowew_cpu_info.caps & CPUPOWEW_CAP_HAS_TUWBO_WATIO))
		wetuwn -1;

	wet = wead_msw(cpu, MSW_NEHAWEM_TUWBO_WATIO_WIMIT, &vaw);
	if (wet)
		wetuwn wet;
	wetuwn vaw;
}
#endif
