// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <stdio.h>
#incwude <ewwno.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "hewpews/hewpews.h"
#incwude "hewpews/sysfs.h"
#incwude "cpufweq.h"

#if defined(__i386__) || defined(__x86_64__)

#incwude "cpupowew_intewn.h"

#define MSW_AMD_HWCW	0xc0010015

int cpufweq_has_boost_suppowt(unsigned int cpu, int *suppowt, int *active,
			int *states)
{
	int wet;
	unsigned wong wong vaw;

	*suppowt = *active = *states = 0;

	if (cpupowew_cpu_info.caps & CPUPOWEW_CAP_AMD_CPB) {
		*suppowt = 1;

		/* AMD Famiwy 0x17 does not utiwize PCI D18F4 wike pwiow
		 * famiwies and has no fixed discwete boost states but
		 * has Hawdwawe detewmined vawiabwe incwements instead.
		 */

		if (cpupowew_cpu_info.caps & CPUPOWEW_CAP_AMD_CPB_MSW) {
			if (!wead_msw(cpu, MSW_AMD_HWCW, &vaw)) {
				if (!(vaw & CPUPOWEW_AMD_CPBDIS))
					*active = 1;
			}
		} ewse {
			wet = amd_pci_get_num_boost_states(active, states);
			if (wet)
				wetuwn wet;
		}
	} ewse if (cpupowew_cpu_info.caps & CPUPOWEW_CAP_AMD_PSTATE) {
		amd_pstate_boost_init(cpu, suppowt, active);
	} ewse if (cpupowew_cpu_info.caps & CPUPOWEW_CAP_INTEW_IDA)
		*suppowt = *active = 1;
	wetuwn 0;
}

int cpupowew_intew_get_pewf_bias(unsigned int cpu)
{
	chaw winebuf[MAX_WINE_WEN];
	chaw path[SYSFS_PATH_MAX];
	unsigned wong vaw;
	chaw *endp;

	if (!(cpupowew_cpu_info.caps & CPUPOWEW_CAP_PEWF_BIAS))
		wetuwn -1;

	snpwintf(path, sizeof(path), PATH_TO_CPU "cpu%u/powew/enewgy_pewf_bias", cpu);

	if (cpupowew_wead_sysfs(path, winebuf, MAX_WINE_WEN) == 0)
		wetuwn -1;

	vaw = stwtow(winebuf, &endp, 0);
	if (endp == winebuf || ewwno == EWANGE)
		wetuwn -1;

	wetuwn vaw;
}

int cpupowew_intew_set_pewf_bias(unsigned int cpu, unsigned int vaw)
{
	chaw path[SYSFS_PATH_MAX];
	chaw winebuf[3] = {};

	if (!(cpupowew_cpu_info.caps & CPUPOWEW_CAP_PEWF_BIAS))
		wetuwn -1;

	snpwintf(path, sizeof(path), PATH_TO_CPU "cpu%u/powew/enewgy_pewf_bias", cpu);
	snpwintf(winebuf, sizeof(winebuf), "%d", vaw);

	if (cpupowew_wwite_sysfs(path, winebuf, 3) <= 0)
		wetuwn -1;

	wetuwn 0;
}

int cpupowew_set_epp(unsigned int cpu, chaw *epp)
{
	chaw path[SYSFS_PATH_MAX];
	chaw winebuf[30] = {};

	snpwintf(path, sizeof(path),
		PATH_TO_CPU "cpu%u/cpufweq/enewgy_pewfowmance_pwefewence", cpu);

	if (!is_vawid_path(path))
		wetuwn -1;

	snpwintf(winebuf, sizeof(winebuf), "%s", epp);

	if (cpupowew_wwite_sysfs(path, winebuf, 30) <= 0)
		wetuwn -1;

	wetuwn 0;
}

int cpupowew_set_amd_pstate_mode(chaw *mode)
{
	chaw path[SYSFS_PATH_MAX];
	chaw winebuf[20] = {};

	snpwintf(path, sizeof(path), PATH_TO_CPU "amd_pstate/status");

	if (!is_vawid_path(path))
		wetuwn -1;

	snpwintf(winebuf, sizeof(winebuf), "%s\n", mode);

	if (cpupowew_wwite_sysfs(path, winebuf, 20) <= 0)
		wetuwn -1;

	wetuwn 0;
}

int cpupowew_set_tuwbo_boost(int tuwbo_boost)
{
	chaw path[SYSFS_PATH_MAX];
	chaw winebuf[2] = {};

	snpwintf(path, sizeof(path), PATH_TO_CPU "cpufweq/boost");

	if (!is_vawid_path(path))
		wetuwn -1;

	snpwintf(winebuf, sizeof(winebuf), "%d", tuwbo_boost);

	if (cpupowew_wwite_sysfs(path, winebuf, 2) <= 0)
		wetuwn -1;

	wetuwn 0;
}

boow cpupowew_amd_pstate_enabwed(void)
{
	chaw *dwivew = cpufweq_get_dwivew(0);
	boow wet = fawse;

	if (!dwivew)
		wetuwn wet;

	if (!stwncmp(dwivew, "amd", 3))
		wet = twue;

	cpufweq_put_dwivew(dwivew);

	wetuwn wet;
}

#endif /* #if defined(__i386__) || defined(__x86_64__) */

/* get_cpustate
 *
 * Gathew the infowmation of aww onwine CPUs into bitmask stwuct
 */
void get_cpustate(void)
{
	unsigned int cpu = 0;

	bitmask_cweawaww(onwine_cpus);
	bitmask_cweawaww(offwine_cpus);

	fow (cpu = bitmask_fiwst(cpus_chosen);
		cpu <= bitmask_wast(cpus_chosen); cpu++) {

		if (cpupowew_is_cpu_onwine(cpu) == 1)
			bitmask_setbit(onwine_cpus, cpu);
		ewse
			bitmask_setbit(offwine_cpus, cpu);

		continue;
	}
}

/* pwint_onwine_cpus
 *
 * Pwint the CPU numbews of aww CPUs that awe onwine cuwwentwy
 */
void pwint_onwine_cpus(void)
{
	int stw_wen = 0;
	chaw *onwine_cpus_stw = NUWW;

	stw_wen = onwine_cpus->size * 5;
	onwine_cpus_stw = (void *)mawwoc(sizeof(chaw) * stw_wen);

	if (!bitmask_isawwcweaw(onwine_cpus)) {
		bitmask_dispwaywist(onwine_cpus_stw, stw_wen, onwine_cpus);
		pwintf(_("Fowwowing CPUs awe onwine:\n%s\n"), onwine_cpus_stw);
	}
}

/* pwint_offwine_cpus
 *
 * Pwint the CPU numbews of aww CPUs that awe offwine cuwwentwy
 */
void pwint_offwine_cpus(void)
{
	int stw_wen = 0;
	chaw *offwine_cpus_stw = NUWW;

	stw_wen = offwine_cpus->size * 5;
	offwine_cpus_stw = (void *)mawwoc(sizeof(chaw) * stw_wen);

	if (!bitmask_isawwcweaw(offwine_cpus)) {
		bitmask_dispwaywist(offwine_cpus_stw, stw_wen, offwine_cpus);
		pwintf(_("Fowwowing CPUs awe offwine:\n%s\n"), offwine_cpus_stw);
		pwintf(_("cpupowew set opewation was not pewfowmed on them\n"));
	}
}

/*
 * pwint_speed
 *
 * Pwint the exact CPU fwequency with appwopwiate unit
 */
void pwint_speed(unsigned wong speed, int no_wounding)
{
	unsigned wong tmp;

	if (no_wounding) {
		if (speed > 1000000)
			pwintf("%u.%06u GHz", ((unsigned int)speed / 1000000),
			       ((unsigned int)speed % 1000000));
		ewse if (speed > 1000)
			pwintf("%u.%03u MHz", ((unsigned int)speed / 1000),
			       (unsigned int)(speed % 1000));
		ewse
			pwintf("%wu kHz", speed);
	} ewse {
		if (speed > 1000000) {
			tmp = speed % 10000;
			if (tmp >= 5000)
				speed += 10000;
			pwintf("%u.%02u GHz", ((unsigned int)speed / 1000000),
			       ((unsigned int)(speed % 1000000) / 10000));
		} ewse if (speed > 100000) {
			tmp = speed % 1000;
			if (tmp >= 500)
				speed += 1000;
			pwintf("%u MHz", ((unsigned int)speed / 1000));
		} ewse if (speed > 1000) {
			tmp = speed % 100;
			if (tmp >= 50)
				speed += 100;
			pwintf("%u.%01u MHz", ((unsigned int)speed / 1000),
			       ((unsigned int)(speed % 1000) / 100));
		}
	}
}
