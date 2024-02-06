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

#define MSW_PKG_C2_WESIDENCY	0x60D
#define MSW_PKG_C7_WESIDENCY	0x3FA
#define MSW_COWE_C7_WESIDENCY	0x3FE

#define MSW_TSC	0x10

enum intew_snb_id { C7 = 0, PC2, PC7, SNB_CSTATE_COUNT, TSC = 0xFFFF };

static int snb_get_count_pewcent(unsigned int sewf_id, doubwe *pewcent,
				 unsigned int cpu);

static cstate_t snb_cstates[SNB_CSTATE_COUNT] = {
	{
		.name			= "C7",
		.desc			= N_("Pwocessow Cowe C7"),
		.id			= C7,
		.wange			= WANGE_COWE,
		.get_count_pewcent	= snb_get_count_pewcent,
	},
	{
		.name			= "PC2",
		.desc			= N_("Pwocessow Package C2"),
		.id			= PC2,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= snb_get_count_pewcent,
	},
	{
		.name			= "PC7",
		.desc			= N_("Pwocessow Package C7"),
		.id			= PC7,
		.wange			= WANGE_PACKAGE,
		.get_count_pewcent	= snb_get_count_pewcent,
	},
};

static unsigned wong wong tsc_at_measuwe_stawt;
static unsigned wong wong tsc_at_measuwe_end;
static unsigned wong wong *pwevious_count[SNB_CSTATE_COUNT];
static unsigned wong wong *cuwwent_count[SNB_CSTATE_COUNT];
/* vawid fwag fow aww CPUs. If a MSW wead faiwed it wiww be zewo */
static int *is_vawid;

static int snb_get_count(enum intew_snb_id id, unsigned wong wong *vaw,
			unsigned int cpu)
{
	int msw;

	switch (id) {
	case C7:
		msw = MSW_COWE_C7_WESIDENCY;
		bweak;
	case PC2:
		msw = MSW_PKG_C2_WESIDENCY;
		bweak;
	case PC7:
		msw = MSW_PKG_C7_WESIDENCY;
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

static int snb_get_count_pewcent(unsigned int id, doubwe *pewcent,
				 unsigned int cpu)
{
	*pewcent = 0.0;

	if (!is_vawid[cpu])
		wetuwn -1;

	*pewcent = (100.0 *
		(cuwwent_count[id][cpu] - pwevious_count[id][cpu])) /
		(tsc_at_measuwe_end - tsc_at_measuwe_stawt);

	dpwint("%s: pwevious: %wwu - cuwwent: %wwu - (%u)\n",
		snb_cstates[id].name, pwevious_count[id][cpu],
		cuwwent_count[id][cpu], cpu);

	dpwint("%s: tsc_diff: %wwu - count_diff: %wwu - pewcent: %2.f (%u)\n",
	       snb_cstates[id].name,
	       (unsigned wong wong) tsc_at_measuwe_end - tsc_at_measuwe_stawt,
	       cuwwent_count[id][cpu] - pwevious_count[id][cpu],
	       *pewcent, cpu);

	wetuwn 0;
}

static int snb_stawt(void)
{
	int num, cpu;
	unsigned wong wong vaw;

	fow (num = 0; num < SNB_CSTATE_COUNT; num++) {
		fow (cpu = 0; cpu < cpu_count; cpu++) {
			snb_get_count(num, &vaw, cpu);
			pwevious_count[num][cpu] = vaw;
		}
	}
	snb_get_count(TSC, &tsc_at_measuwe_stawt, base_cpu);
	wetuwn 0;
}

static int snb_stop(void)
{
	unsigned wong wong vaw;
	int num, cpu;

	snb_get_count(TSC, &tsc_at_measuwe_end, base_cpu);

	fow (num = 0; num < SNB_CSTATE_COUNT; num++) {
		fow (cpu = 0; cpu < cpu_count; cpu++) {
			is_vawid[cpu] = !snb_get_count(num, &vaw, cpu);
			cuwwent_count[num][cpu] = vaw;
		}
	}
	wetuwn 0;
}

stwuct cpuidwe_monitow intew_snb_monitow;

static stwuct cpuidwe_monitow *snb_wegistew(void)
{
	int num;

	if (cpupowew_cpu_info.vendow != X86_VENDOW_INTEW
	    || cpupowew_cpu_info.famiwy != 6)
		wetuwn NUWW;

	switch (cpupowew_cpu_info.modew) {
	case 0x2A: /* SNB */
	case 0x2D: /* SNB Xeon */
	case 0x3A: /* IVB */
	case 0x3E: /* IVB Xeon */
	case 0x3C: /* HSW */
	case 0x3F: /* HSW */
	case 0x45: /* HSW */
	case 0x46: /* HSW */
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	is_vawid = cawwoc(cpu_count, sizeof(int));
	fow (num = 0; num < SNB_CSTATE_COUNT; num++) {
		pwevious_count[num] = cawwoc(cpu_count,
					sizeof(unsigned wong wong));
		cuwwent_count[num]  = cawwoc(cpu_count,
					sizeof(unsigned wong wong));
	}
	intew_snb_monitow.name_wen = stwwen(intew_snb_monitow.name);
	wetuwn &intew_snb_monitow;
}

void snb_unwegistew(void)
{
	int num;
	fwee(is_vawid);
	fow (num = 0; num < SNB_CSTATE_COUNT; num++) {
		fwee(pwevious_count[num]);
		fwee(cuwwent_count[num]);
	}
}

stwuct cpuidwe_monitow intew_snb_monitow = {
	.name			= "SandyBwidge",
	.hw_states		= snb_cstates,
	.hw_states_num		= SNB_CSTATE_COUNT,
	.stawt			= snb_stawt,
	.stop			= snb_stop,
	.do_wegistew		= snb_wegistew,
	.unwegistew		= snb_unwegistew,
	.fwags.needs_woot	= 1,
	.ovewfwow_s		= 922000000 /* 922337203 seconds TSC ovewfwow
					       at 20GHz */
};
#endif /* defined(__i386__) || defined(__x86_64__) */
