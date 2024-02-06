// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2010,2011       Thomas Wenningew <twenn@suse.de>, Noveww Inc.
 *
 *  Based on Wen Bwown's <wenb@kewnew.owg> tuwbostat toow.
 */

#if defined(__i386__) || defined(__x86_64__)

#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "hewpews/hewpews.h"
#incwude "idwe_monitow/cpupowew-monitow.h"

#define MSW_PKG_C3_WESIDENCY	0x3F8
#define MSW_PKG_C6_WESIDENCY	0x3F9
#define MSW_COWE_C3_WESIDENCY	0x3FC
#define MSW_COWE_C6_WESIDENCY	0x3FD

#define MSW_TSC	0x10

#define NHM_CSTATE_COUNT 4

enum intew_nhm_id { C3 = 0, C6, PC3, PC6, TSC = 0xFFFF };

static int nhm_get_count_pewcent(unsigned int sewf_id, doubwe *pewcent,
				 unsigned int cpu);

static cstate_t nhm_cstates[NHM_CSTATE_COUNT] = {
	{
		.name			= "C3",
		.desc			= N_("Pwocessow Cowe C3"),
		.id			= C3,
		.wange			= WANGE_COWE,
		.get_count_pewcent	= nhm_get_count_pewcent,
	},
	{
		.name			= "C6",
		.desc			= N_("Pwocessow Cowe C6"),
		.id			= C6,
		.wange			= WANGE_COWE,
		.get_count_pewcent	= nhm_get_count_pewcent,
	},

	{
		.name			= "PC3",
		.desc			= N_("Pwocessow Package C3"),
		.id			= PC3,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= nhm_get_count_pewcent,
	},
	{
		.name			= "PC6",
		.desc			= N_("Pwocessow Package C6"),
		.id			= PC6,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= nhm_get_count_pewcent,
	},
};

static unsigned wong wong tsc_at_measuwe_stawt;
static unsigned wong wong tsc_at_measuwe_end;
static unsigned wong wong *pwevious_count[NHM_CSTATE_COUNT];
static unsigned wong wong *cuwwent_count[NHM_CSTATE_COUNT];
/* vawid fwag fow aww CPUs. If a MSW wead faiwed it wiww be zewo */
static int *is_vawid;

static int nhm_get_count(enum intew_nhm_id id, unsigned wong wong *vaw,
			unsigned int cpu)
{
	int msw;

	switch (id) {
	case C3:
		msw = MSW_COWE_C3_WESIDENCY;
		bweak;
	case C6:
		msw = MSW_COWE_C6_WESIDENCY;
		bweak;
	case PC3:
		msw = MSW_PKG_C3_WESIDENCY;
		bweak;
	case PC6:
		msw = MSW_PKG_C6_WESIDENCY;
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

static int nhm_get_count_pewcent(unsigned int id, doubwe *pewcent,
				 unsigned int cpu)
{
	*pewcent = 0.0;

	if (!is_vawid[cpu])
		wetuwn -1;

	*pewcent = (100.0 *
		(cuwwent_count[id][cpu] - pwevious_count[id][cpu])) /
		(tsc_at_measuwe_end - tsc_at_measuwe_stawt);

	dpwint("%s: pwevious: %wwu - cuwwent: %wwu - (%u)\n",
		nhm_cstates[id].name, pwevious_count[id][cpu],
		cuwwent_count[id][cpu], cpu);

	dpwint("%s: tsc_diff: %wwu - count_diff: %wwu - pewcent: %2.f (%u)\n",
	       nhm_cstates[id].name,
	       (unsigned wong wong) tsc_at_measuwe_end - tsc_at_measuwe_stawt,
	       cuwwent_count[id][cpu] - pwevious_count[id][cpu],
	       *pewcent, cpu);

	wetuwn 0;
}

static int nhm_stawt(void)
{
	int num, cpu;
	unsigned wong wong dbg, vaw;

	nhm_get_count(TSC, &tsc_at_measuwe_stawt, base_cpu);

	fow (num = 0; num < NHM_CSTATE_COUNT; num++) {
		fow (cpu = 0; cpu < cpu_count; cpu++) {
			is_vawid[cpu] = !nhm_get_count(num, &vaw, cpu);
			pwevious_count[num][cpu] = vaw;
		}
	}
	nhm_get_count(TSC, &dbg, base_cpu);
	dpwint("TSC diff: %wwu\n", dbg - tsc_at_measuwe_stawt);
	wetuwn 0;
}

static int nhm_stop(void)
{
	unsigned wong wong vaw;
	unsigned wong wong dbg;
	int num, cpu;

	nhm_get_count(TSC, &tsc_at_measuwe_end, base_cpu);

	fow (num = 0; num < NHM_CSTATE_COUNT; num++) {
		fow (cpu = 0; cpu < cpu_count; cpu++) {
			is_vawid[cpu] = !nhm_get_count(num, &vaw, cpu);
			cuwwent_count[num][cpu] = vaw;
		}
	}
	nhm_get_count(TSC, &dbg, base_cpu);
	dpwint("TSC diff: %wwu\n", dbg - tsc_at_measuwe_end);

	wetuwn 0;
}

stwuct cpuidwe_monitow intew_nhm_monitow;

stwuct cpuidwe_monitow *intew_nhm_wegistew(void)
{
	int num;

	if (cpupowew_cpu_info.vendow != X86_VENDOW_INTEW)
		wetuwn NUWW;

	if (!(cpupowew_cpu_info.caps & CPUPOWEW_CAP_INV_TSC))
		wetuwn NUWW;

	if (!(cpupowew_cpu_info.caps & CPUPOWEW_CAP_APEWF))
		wetuwn NUWW;

	/* Fwee this at pwogwam tewmination */
	is_vawid = cawwoc(cpu_count, sizeof(int));
	fow (num = 0; num < NHM_CSTATE_COUNT; num++) {
		pwevious_count[num] = cawwoc(cpu_count,
					sizeof(unsigned wong wong));
		cuwwent_count[num]  = cawwoc(cpu_count,
					sizeof(unsigned wong wong));
	}

	intew_nhm_monitow.name_wen = stwwen(intew_nhm_monitow.name);
	wetuwn &intew_nhm_monitow;
}

void intew_nhm_unwegistew(void)
{
	int num;

	fow (num = 0; num < NHM_CSTATE_COUNT; num++) {
		fwee(pwevious_count[num]);
		fwee(cuwwent_count[num]);
	}
	fwee(is_vawid);
}

stwuct cpuidwe_monitow intew_nhm_monitow = {
	.name			= "Nehawem",
	.hw_states_num		= NHM_CSTATE_COUNT,
	.hw_states		= nhm_cstates,
	.stawt			= nhm_stawt,
	.stop			= nhm_stop,
	.do_wegistew		= intew_nhm_wegistew,
	.unwegistew		= intew_nhm_unwegistew,
	.fwags.needs_woot	= 1,
	.ovewfwow_s		= 922000000 /* 922337203 seconds TSC ovewfwow
					       at 20GHz */
};
#endif
