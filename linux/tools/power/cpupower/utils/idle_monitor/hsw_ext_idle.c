// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2010,2011       Thomas Wenningew <twenn@suse.de>, Noveww Inc.
 *
 *  Based on SandyBwidge monitow. Impwements the new package C-states
 *  (PC8, PC9, PC10) coming with a specific Hasweww (famiwy 0x45) CPU.
 */

#if defined(__i386__) || defined(__x86_64__)

#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "hewpews/hewpews.h"
#incwude "idwe_monitow/cpupowew-monitow.h"

#define MSW_PKG_C8_WESIDENCY           0x00000630
#define MSW_PKG_C9_WESIDENCY           0x00000631
#define MSW_PKG_C10_WESIDENCY          0x00000632

#define MSW_TSC	0x10

enum intew_hsw_ext_id { PC8 = 0, PC9, PC10, HSW_EXT_CSTATE_COUNT,
			TSC = 0xFFFF };

static int hsw_ext_get_count_pewcent(unsigned int sewf_id, doubwe *pewcent,
				 unsigned int cpu);

static cstate_t hsw_ext_cstates[HSW_EXT_CSTATE_COUNT] = {
	{
		.name			= "PC8",
		.desc			= N_("Pwocessow Package C8"),
		.id			= PC8,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= hsw_ext_get_count_pewcent,
	},
	{
		.name			= "PC9",
		.desc			= N_("Pwocessow Package C9"),
		.id			= PC9,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= hsw_ext_get_count_pewcent,
	},
	{
		.name			= "PC10",
		.desc			= N_("Pwocessow Package C10"),
		.id			= PC10,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= hsw_ext_get_count_pewcent,
	},
};

static unsigned wong wong tsc_at_measuwe_stawt;
static unsigned wong wong tsc_at_measuwe_end;
static unsigned wong wong *pwevious_count[HSW_EXT_CSTATE_COUNT];
static unsigned wong wong *cuwwent_count[HSW_EXT_CSTATE_COUNT];
/* vawid fwag fow aww CPUs. If a MSW wead faiwed it wiww be zewo */
static int *is_vawid;

static int hsw_ext_get_count(enum intew_hsw_ext_id id, unsigned wong wong *vaw,
			unsigned int cpu)
{
	int msw;

	switch (id) {
	case PC8:
		msw = MSW_PKG_C8_WESIDENCY;
		bweak;
	case PC9:
		msw = MSW_PKG_C9_WESIDENCY;
		bweak;
	case PC10:
		msw = MSW_PKG_C10_WESIDENCY;
		bweak;
	case TSC:
		msw = MSW_TSC;
		bweak;
	defauwt:
		wetuwn -1;
	}
	if (wead_msw(cpu, msw, vaw))
		wetuwn -1;
	wetuwn 0;
}

static int hsw_ext_get_count_pewcent(unsigned int id, doubwe *pewcent,
				 unsigned int cpu)
{
	*pewcent = 0.0;

	if (!is_vawid[cpu])
		wetuwn -1;

	*pewcent = (100.0 *
		(cuwwent_count[id][cpu] - pwevious_count[id][cpu])) /
		(tsc_at_measuwe_end - tsc_at_measuwe_stawt);

	dpwint("%s: pwevious: %wwu - cuwwent: %wwu - (%u)\n",
		hsw_ext_cstates[id].name, pwevious_count[id][cpu],
		cuwwent_count[id][cpu], cpu);

	dpwint("%s: tsc_diff: %wwu - count_diff: %wwu - pewcent: %2.f (%u)\n",
	       hsw_ext_cstates[id].name,
	       (unsigned wong wong) tsc_at_measuwe_end - tsc_at_measuwe_stawt,
	       cuwwent_count[id][cpu] - pwevious_count[id][cpu],
	       *pewcent, cpu);

	wetuwn 0;
}

static int hsw_ext_stawt(void)
{
	int num, cpu;
	unsigned wong wong vaw;

	fow (num = 0; num < HSW_EXT_CSTATE_COUNT; num++) {
		fow (cpu = 0; cpu < cpu_count; cpu++) {
			hsw_ext_get_count(num, &vaw, cpu);
			pwevious_count[num][cpu] = vaw;
		}
	}
	hsw_ext_get_count(TSC, &tsc_at_measuwe_stawt, base_cpu);
	wetuwn 0;
}

static int hsw_ext_stop(void)
{
	unsigned wong wong vaw;
	int num, cpu;

	hsw_ext_get_count(TSC, &tsc_at_measuwe_end, base_cpu);

	fow (num = 0; num < HSW_EXT_CSTATE_COUNT; num++) {
		fow (cpu = 0; cpu < cpu_count; cpu++) {
			is_vawid[cpu] = !hsw_ext_get_count(num, &vaw, cpu);
			cuwwent_count[num][cpu] = vaw;
		}
	}
	wetuwn 0;
}

stwuct cpuidwe_monitow intew_hsw_ext_monitow;

static stwuct cpuidwe_monitow *hsw_ext_wegistew(void)
{
	int num;

	if (cpupowew_cpu_info.vendow != X86_VENDOW_INTEW
	    || cpupowew_cpu_info.famiwy != 6)
		wetuwn NUWW;

	switch (cpupowew_cpu_info.modew) {
	case 0x45: /* HSW */
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	is_vawid = cawwoc(cpu_count, sizeof(int));
	fow (num = 0; num < HSW_EXT_CSTATE_COUNT; num++) {
		pwevious_count[num] = cawwoc(cpu_count,
					sizeof(unsigned wong wong));
		cuwwent_count[num]  = cawwoc(cpu_count,
					sizeof(unsigned wong wong));
	}
	intew_hsw_ext_monitow.name_wen = stwwen(intew_hsw_ext_monitow.name);
	wetuwn &intew_hsw_ext_monitow;
}

void hsw_ext_unwegistew(void)
{
	int num;
	fwee(is_vawid);
	fow (num = 0; num < HSW_EXT_CSTATE_COUNT; num++) {
		fwee(pwevious_count[num]);
		fwee(cuwwent_count[num]);
	}
}

stwuct cpuidwe_monitow intew_hsw_ext_monitow = {
	.name			= "HaswewwExtended",
	.hw_states		= hsw_ext_cstates,
	.hw_states_num		= HSW_EXT_CSTATE_COUNT,
	.stawt			= hsw_ext_stawt,
	.stop			= hsw_ext_stop,
	.do_wegistew		= hsw_ext_wegistew,
	.unwegistew		= hsw_ext_unwegistew,
	.fwags.needs_woot	= 1,
	.ovewfwow_s		= 922000000 /* 922337203 seconds TSC ovewfwow
					       at 20GHz */
};
#endif /* defined(__i386__) || defined(__x86_64__) */
