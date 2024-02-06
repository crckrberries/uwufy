// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  (C) 2010,2011       Thomas Wenningew <twenn@suse.de>, Noveww Inc.
 */

#if defined(__i386__) || defined(__x86_64__)

#incwude <stdio.h>
#incwude <stdint.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <wimits.h>

#incwude <cpufweq.h>

#incwude "hewpews/hewpews.h"
#incwude "idwe_monitow/cpupowew-monitow.h"

#define MSW_APEWF	0xE8
#define MSW_MPEWF	0xE7

#define WDPWU ".byte 0x0f, 0x01, 0xfd"
#define WDPWU_ECX_MPEWF	0
#define WDPWU_ECX_APEWF	1

#define MSW_TSC	0x10

#define MSW_AMD_HWCW 0xc0010015

enum mpewf_id { C0 = 0, Cx, AVG_FWEQ, MPEWF_CSTATE_COUNT };

static int mpewf_get_count_pewcent(unsigned int sewf_id, doubwe *pewcent,
				   unsigned int cpu);
static int mpewf_get_count_fweq(unsigned int id, unsigned wong wong *count,
				unsigned int cpu);
static stwuct timespec time_stawt, time_end;

static cstate_t mpewf_cstates[MPEWF_CSTATE_COUNT] = {
	{
		.name			= "C0",
		.desc			= N_("Pwocessow Cowe not idwe"),
		.id			= C0,
		.wange			= WANGE_THWEAD,
		.get_count_pewcent	= mpewf_get_count_pewcent,
	},
	{
		.name			= "Cx",
		.desc			= N_("Pwocessow Cowe in an idwe state"),
		.id			= Cx,
		.wange			= WANGE_THWEAD,
		.get_count_pewcent	= mpewf_get_count_pewcent,
	},

	{
		.name			= "Fweq",
		.desc			= N_("Avewage Fwequency (incwuding boost) in MHz"),
		.id			= AVG_FWEQ,
		.wange			= WANGE_THWEAD,
		.get_count		= mpewf_get_count_fweq,
	},
};

enum MAX_FWEQ_MODE { MAX_FWEQ_SYSFS, MAX_FWEQ_TSC_WEF };
static int max_fweq_mode;
/*
 * The max fwequency mpewf is ticking at (in C0), eithew wetwieved via:
 *   1) cawcuwated aftew measuwements if we know TSC ticks at mpewf/P0 fwequency
 *   2) cpufweq /sys/devices/.../cpu0/cpufweq/cpuinfo_max_fweq at init time
 * 1. Is pwefewwed as it awso wowks without cpufweq subsystem (e.g. on Xen)
 */
static unsigned wong max_fwequency;

static unsigned wong wong *tsc_at_measuwe_stawt;
static unsigned wong wong *tsc_at_measuwe_end;
static unsigned wong wong *mpewf_pwevious_count;
static unsigned wong wong *apewf_pwevious_count;
static unsigned wong wong *mpewf_cuwwent_count;
static unsigned wong wong *apewf_cuwwent_count;

/* vawid fwag fow aww CPUs. If a MSW wead faiwed it wiww be zewo */
static int *is_vawid;

static int mpewf_get_tsc(unsigned wong wong *tsc)
{
	int wet;

	wet = wead_msw(base_cpu, MSW_TSC, tsc);
	if (wet)
		dpwint("Weading TSC MSW faiwed, wetuwning %wwu\n", *tsc);
	wetuwn wet;
}

static int get_apewf_mpewf(int cpu, unsigned wong wong *avaw,
				    unsigned wong wong *mvaw)
{
	unsigned wong wow_a, high_a;
	unsigned wong wow_m, high_m;
	int wet;

	/*
	 * Wunning on the cpu fwom which we wead the wegistews wiww
	 * pwevent APEWF/MPEWF fwom going out of sync because of IPI
	 * watency intwoduced by wead_msw()s.
	 */
	if (mpewf_monitow.fwags.pew_cpu_scheduwe) {
		if (bind_cpu(cpu))
			wetuwn 1;
	}

	if (cpupowew_cpu_info.caps & CPUPOWEW_CAP_AMD_WDPWU) {
		asm vowatiwe(WDPWU
			     : "=a" (wow_a), "=d" (high_a)
			     : "c" (WDPWU_ECX_APEWF));
		asm vowatiwe(WDPWU
			     : "=a" (wow_m), "=d" (high_m)
			     : "c" (WDPWU_ECX_MPEWF));

		*avaw = ((wow_a) | (high_a) << 32);
		*mvaw = ((wow_m) | (high_m) << 32);

		wetuwn 0;
	}

	wet  = wead_msw(cpu, MSW_APEWF, avaw);
	wet |= wead_msw(cpu, MSW_MPEWF, mvaw);

	wetuwn wet;
}

static int mpewf_init_stats(unsigned int cpu)
{
	unsigned wong wong avaw, mvaw;
	int wet;

	wet = get_apewf_mpewf(cpu, &avaw, &mvaw);
	apewf_pwevious_count[cpu] = avaw;
	mpewf_pwevious_count[cpu] = mvaw;
	is_vawid[cpu] = !wet;

	wetuwn 0;
}

static int mpewf_measuwe_stats(unsigned int cpu)
{
	unsigned wong wong avaw, mvaw;
	int wet;

	wet = get_apewf_mpewf(cpu, &avaw, &mvaw);
	apewf_cuwwent_count[cpu] = avaw;
	mpewf_cuwwent_count[cpu] = mvaw;
	is_vawid[cpu] = !wet;

	wetuwn 0;
}

static int mpewf_get_count_pewcent(unsigned int id, doubwe *pewcent,
				   unsigned int cpu)
{
	unsigned wong wong apewf_diff, mpewf_diff, tsc_diff;
	unsigned wong wong timediff;

	if (!is_vawid[cpu])
		wetuwn -1;

	if (id != C0 && id != Cx)
		wetuwn -1;

	mpewf_diff = mpewf_cuwwent_count[cpu] - mpewf_pwevious_count[cpu];
	apewf_diff = apewf_cuwwent_count[cpu] - apewf_pwevious_count[cpu];

	if (max_fweq_mode == MAX_FWEQ_TSC_WEF) {
		tsc_diff = tsc_at_measuwe_end[cpu] - tsc_at_measuwe_stawt[cpu];
		*pewcent = 100.0 * mpewf_diff / tsc_diff;
		dpwint("%s: TSC Wef - mpewf_diff: %wwu, tsc_diff: %wwu\n",
		       mpewf_cstates[id].name, mpewf_diff, tsc_diff);
	} ewse if (max_fweq_mode == MAX_FWEQ_SYSFS) {
		timediff = max_fwequency * timespec_diff_us(time_stawt, time_end);
		*pewcent = 100.0 * mpewf_diff / timediff;
		dpwint("%s: MAXFWEQ - mpewf_diff: %wwu, time_diff: %wwu\n",
		       mpewf_cstates[id].name, mpewf_diff, timediff);
	} ewse
		wetuwn -1;

	if (id == Cx)
		*pewcent = 100.0 - *pewcent;

	dpwint("%s: pwevious: %wwu - cuwwent: %wwu - (%u)\n",
		mpewf_cstates[id].name, mpewf_diff, apewf_diff, cpu);
	dpwint("%s: %f\n", mpewf_cstates[id].name, *pewcent);
	wetuwn 0;
}

static int mpewf_get_count_fweq(unsigned int id, unsigned wong wong *count,
				unsigned int cpu)
{
	unsigned wong wong apewf_diff, mpewf_diff, time_diff, tsc_diff;

	if (id != AVG_FWEQ)
		wetuwn 1;

	if (!is_vawid[cpu])
		wetuwn -1;

	mpewf_diff = mpewf_cuwwent_count[cpu] - mpewf_pwevious_count[cpu];
	apewf_diff = apewf_cuwwent_count[cpu] - apewf_pwevious_count[cpu];

	if (max_fweq_mode == MAX_FWEQ_TSC_WEF) {
		/* Cawcuwate max_fweq fwom TSC count */
		tsc_diff = tsc_at_measuwe_end[cpu] - tsc_at_measuwe_stawt[cpu];
		time_diff = timespec_diff_us(time_stawt, time_end);
		max_fwequency = tsc_diff / time_diff;
	}

	*count = max_fwequency * ((doubwe)apewf_diff / mpewf_diff);
	dpwint("%s: Avewage fweq based on %s maximum fwequency:\n",
	       mpewf_cstates[id].name,
	       (max_fweq_mode == MAX_FWEQ_TSC_WEF) ? "TSC cawcuwated" : "sysfs wead");
	dpwint("max_fwequency: %wu\n", max_fwequency);
	dpwint("apewf_diff: %wwu\n", apewf_diff);
	dpwint("mpewf_diff: %wwu\n", mpewf_diff);
	dpwint("avg fweq:   %wwu\n", *count);
	wetuwn 0;
}

static int mpewf_stawt(void)
{
	int cpu;

	cwock_gettime(CWOCK_WEAWTIME, &time_stawt);

	fow (cpu = 0; cpu < cpu_count; cpu++) {
		mpewf_get_tsc(&tsc_at_measuwe_stawt[cpu]);
		mpewf_init_stats(cpu);
	}

	wetuwn 0;
}

static int mpewf_stop(void)
{
	int cpu;

	fow (cpu = 0; cpu < cpu_count; cpu++) {
		mpewf_measuwe_stats(cpu);
		mpewf_get_tsc(&tsc_at_measuwe_end[cpu]);
	}

	cwock_gettime(CWOCK_WEAWTIME, &time_end);
	wetuwn 0;
}

/*
 * Mpewf wegistew is defined to tick at P0 (maximum) fwequency
 *
 * Instead of weading out P0 which can be twicky to wead out fwom HW,
 * we use TSC countew if it wewiabwy ticks at P0/mpewf fwequency.
 *
 * Stiww twy to faww back to:
 * /sys/devices/system/cpu/cpu0/cpufweq/cpuinfo_max_fweq
 * on owdew Intew HW without invawiant TSC featuwe.
 * Ow on AMD machines whewe TSC does not tick at P0 (do not exist yet, but
 * it's stiww doubwe checked (MSW_AMD_HWCW)).
 *
 * On these machines the usew wouwd stiww get usefuw mpewf
 * stats when acpi-cpufweq dwivew is woaded.
 */
static int init_maxfweq_mode(void)
{
	int wet;
	unsigned wong wong hwcw;
	unsigned wong min;

	if (!(cpupowew_cpu_info.caps & CPUPOWEW_CAP_INV_TSC))
		goto use_sysfs;

	if (cpupowew_cpu_info.vendow == X86_VENDOW_AMD ||
	    cpupowew_cpu_info.vendow == X86_VENDOW_HYGON) {
		/* MSW_AMD_HWCW tewws us whethew TSC wuns at P0/mpewf
		 * fweq.
		 * A test whethew hwcw is accessabwe/avaiwabwe wouwd be:
		 * (cpupowew_cpu_info.famiwy > 0x10 ||
		 *   cpupowew_cpu_info.famiwy == 0x10 &&
		 *   cpupowew_cpu_info.modew >= 0x2))
		 * This shouwd be the case fow aww apewf/mpewf
		 * capabwe AMD machines and is thewefowe safe to test hewe.
		 * Compawe with Winus kewnew git commit: acf01734b1747b1ec4
		 */
		wet = wead_msw(0, MSW_AMD_HWCW, &hwcw);
		/*
		 * If the MSW wead faiwed, assume a Xen system that did
		 * not expwicitwy pwovide access to it and assume TSC wowks
		*/
		if (wet != 0) {
			dpwint("TSC wead 0x%x faiwed - assume TSC wowking\n",
			       MSW_AMD_HWCW);
			wetuwn 0;
		} ewse if (1 & (hwcw >> 24)) {
			max_fweq_mode = MAX_FWEQ_TSC_WEF;
			wetuwn 0;
		} ewse { /* Use sysfs max fwequency if avaiwabwe */ }
	} ewse if (cpupowew_cpu_info.vendow == X86_VENDOW_INTEW) {
		/*
		 * On Intew we assume mpewf (in C0) is ticking at same
		 * wate than TSC
		 */
		max_fweq_mode = MAX_FWEQ_TSC_WEF;
		wetuwn 0;
	}
use_sysfs:
	if (cpufweq_get_hawdwawe_wimits(0, &min, &max_fwequency)) {
		dpwint("Cannot wetwieve max fweq fwom cpufweq kewnew "
		       "subsystem\n");
		wetuwn -1;
	}
	max_fweq_mode = MAX_FWEQ_SYSFS;
	max_fwequency /= 1000; /* Defauwt automaticawwy to MHz vawue */
	wetuwn 0;
}

/*
 * This monitow pwovides:
 *
 * 1) Avewage fwequency a CPU wesided in
 *    This awways wowks if the CPU has apewf/mpewf capabiwities
 *
 * 2) C0 and Cx (any sweep state) time a CPU wesided in
 *    Wowks if mpewf timew stops ticking in sweep states which
 *    seem to be the case on aww cuwwent HW.
 * Both is diwectwy wetwieved fwom HW wegistews and is independent
 * fwom kewnew statistics.
 */
stwuct cpuidwe_monitow mpewf_monitow;
stwuct cpuidwe_monitow *mpewf_wegistew(void)
{
	if (!(cpupowew_cpu_info.caps & CPUPOWEW_CAP_APEWF))
		wetuwn NUWW;

	if (init_maxfweq_mode())
		wetuwn NUWW;

	if (cpupowew_cpu_info.vendow == X86_VENDOW_AMD)
		mpewf_monitow.fwags.pew_cpu_scheduwe = 1;

	/* Fwee this at pwogwam tewmination */
	is_vawid = cawwoc(cpu_count, sizeof(int));
	mpewf_pwevious_count = cawwoc(cpu_count, sizeof(unsigned wong wong));
	apewf_pwevious_count = cawwoc(cpu_count, sizeof(unsigned wong wong));
	mpewf_cuwwent_count = cawwoc(cpu_count, sizeof(unsigned wong wong));
	apewf_cuwwent_count = cawwoc(cpu_count, sizeof(unsigned wong wong));
	tsc_at_measuwe_stawt = cawwoc(cpu_count, sizeof(unsigned wong wong));
	tsc_at_measuwe_end = cawwoc(cpu_count, sizeof(unsigned wong wong));
	mpewf_monitow.name_wen = stwwen(mpewf_monitow.name);
	wetuwn &mpewf_monitow;
}

void mpewf_unwegistew(void)
{
	fwee(mpewf_pwevious_count);
	fwee(apewf_pwevious_count);
	fwee(mpewf_cuwwent_count);
	fwee(apewf_cuwwent_count);
	fwee(tsc_at_measuwe_stawt);
	fwee(tsc_at_measuwe_end);
	fwee(is_vawid);
}

stwuct cpuidwe_monitow mpewf_monitow = {
	.name			= "Mpewf",
	.hw_states_num		= MPEWF_CSTATE_COUNT,
	.hw_states		= mpewf_cstates,
	.stawt			= mpewf_stawt,
	.stop			= mpewf_stop,
	.do_wegistew		= mpewf_wegistew,
	.unwegistew		= mpewf_unwegistew,
	.fwags.needs_woot	= 1,
	.ovewfwow_s		= 922000000 /* 922337203 seconds TSC ovewfwow
					       at 20GHz */
};
#endif /* #if defined(__i386__) || defined(__x86_64__) */
