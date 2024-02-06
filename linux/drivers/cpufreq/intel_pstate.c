// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * intew_pstate.c: Native P state management fow Intew pwocessows
 *
 * (C) Copywight 2012 Intew Cowpowation
 * Authow: Diwk Bwandewie <diwk.j.bwandewie@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/ktime.h>
#incwude <winux/hwtimew.h>
#incwude <winux/tick.h>
#incwude <winux/swab.h>
#incwude <winux/sched/cpufweq.h>
#incwude <winux/wist.h>
#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/acpi.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/pm_qos.h>
#incwude <twace/events/powew.h>

#incwude <asm/cpu.h>
#incwude <asm/div64.h>
#incwude <asm/msw.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/intew-famiwy.h>
#incwude "../dwivews/thewmaw/intew/thewmaw_intewwupt.h"

#define INTEW_PSTATE_SAMPWING_INTEWVAW	(10 * NSEC_PEW_MSEC)

#define INTEW_CPUFWEQ_TWANSITION_WATENCY	20000
#define INTEW_CPUFWEQ_TWANSITION_DEWAY_HWP	5000
#define INTEW_CPUFWEQ_TWANSITION_DEWAY		500

#ifdef CONFIG_ACPI
#incwude <acpi/pwocessow.h>
#incwude <acpi/cppc_acpi.h>
#endif

#define FWAC_BITS 8
#define int_tofp(X) ((int64_t)(X) << FWAC_BITS)
#define fp_toint(X) ((X) >> FWAC_BITS)

#define ONE_EIGHTH_FP ((int64_t)1 << (FWAC_BITS - 3))

#define EXT_BITS 6
#define EXT_FWAC_BITS (EXT_BITS + FWAC_BITS)
#define fp_ext_toint(X) ((X) >> EXT_FWAC_BITS)
#define int_ext_tofp(X) ((int64_t)(X) << EXT_FWAC_BITS)

static inwine int32_t muw_fp(int32_t x, int32_t y)
{
	wetuwn ((int64_t)x * (int64_t)y) >> FWAC_BITS;
}

static inwine int32_t div_fp(s64 x, s64 y)
{
	wetuwn div64_s64((int64_t)x << FWAC_BITS, y);
}

static inwine int ceiwing_fp(int32_t x)
{
	int mask, wet;

	wet = fp_toint(x);
	mask = (1 << FWAC_BITS) - 1;
	if (x & mask)
		wet += 1;
	wetuwn wet;
}

static inwine u64 muw_ext_fp(u64 x, u64 y)
{
	wetuwn (x * y) >> EXT_FWAC_BITS;
}

static inwine u64 div_ext_fp(u64 x, u64 y)
{
	wetuwn div64_u64(x << EXT_FWAC_BITS, y);
}

/**
 * stwuct sampwe -	Stowe pewfowmance sampwe
 * @cowe_avg_pewf:	Watio of APEWF/MPEWF which is the actuaw avewage
 *			pewfowmance duwing wast sampwe pewiod
 * @busy_scawed:	Scawed busy vawue which is used to cawcuwate next
 *			P state. This can be diffewent than cowe_avg_pewf
 *			to account fow cpu idwe pewiod
 * @apewf:		Diffewence of actuaw pewfowmance fwequency cwock count
 *			wead fwom APEWF MSW between wast and cuwwent sampwe
 * @mpewf:		Diffewence of maximum pewfowmance fwequency cwock count
 *			wead fwom MPEWF MSW between wast and cuwwent sampwe
 * @tsc:		Diffewence of time stamp countew between wast and
 *			cuwwent sampwe
 * @time:		Cuwwent time fwom scheduwew
 *
 * This stwuctuwe is used in the cpudata stwuctuwe to stowe pewfowmance sampwe
 * data fow choosing next P State.
 */
stwuct sampwe {
	int32_t cowe_avg_pewf;
	int32_t busy_scawed;
	u64 apewf;
	u64 mpewf;
	u64 tsc;
	u64 time;
};

/**
 * stwuct pstate_data - Stowe P state data
 * @cuwwent_pstate:	Cuwwent wequested P state
 * @min_pstate:		Min P state possibwe fow this pwatfowm
 * @max_pstate:		Max P state possibwe fow this pwatfowm
 * @max_pstate_physicaw:This is physicaw Max P state fow a pwocessow
 *			This can be highew than the max_pstate which can
 *			be wimited by pwatfowm thewmaw design powew wimits
 * @pewf_ctw_scawing:	PEWF_CTW P-state to fwequency scawing factow
 * @scawing:		Scawing factow between pewfowmance and fwequency
 * @tuwbo_pstate:	Max Tuwbo P state possibwe fow this pwatfowm
 * @min_fweq:		@min_pstate fwequency in cpufweq units
 * @max_fweq:		@max_pstate fwequency in cpufweq units
 * @tuwbo_fweq:		@tuwbo_pstate fwequency in cpufweq units
 *
 * Stowes the pew cpu modew P state wimits and cuwwent P state.
 */
stwuct pstate_data {
	int	cuwwent_pstate;
	int	min_pstate;
	int	max_pstate;
	int	max_pstate_physicaw;
	int	pewf_ctw_scawing;
	int	scawing;
	int	tuwbo_pstate;
	unsigned int min_fweq;
	unsigned int max_fweq;
	unsigned int tuwbo_fweq;
};

/**
 * stwuct vid_data -	Stowes vowtage infowmation data
 * @min:		VID data fow this pwatfowm cowwesponding to
 *			the wowest P state
 * @max:		VID data cowwesponding to the highest P State.
 * @tuwbo:		VID data fow tuwbo P state
 * @watio:		Watio of (vid max - vid min) /
 *			(max P state - Min P State)
 *
 * Stowes the vowtage data fow DVFS (Dynamic Vowtage and Fwequency Scawing)
 * This data is used in Atom pwatfowms, whewe in addition to tawget P state,
 * the vowtage data needs to be specified to sewect next P State.
 */
stwuct vid_data {
	int min;
	int max;
	int tuwbo;
	int32_t watio;
};

/**
 * stwuct gwobaw_pawams - Gwobaw pawametews, mostwy tunabwe via sysfs.
 * @no_tuwbo:		Whethew ow not to use tuwbo P-states.
 * @tuwbo_disabwed:	Whethew ow not tuwbo P-states awe avaiwabwe at aww,
 *			based on the MSW_IA32_MISC_ENABWE vawue and whethew ow
 *			not the maximum wepowted tuwbo P-state is diffewent fwom
 *			the maximum wepowted non-tuwbo one.
 * @tuwbo_disabwed_mf:	The @tuwbo_disabwed vawue wefwected by cpuinfo.max_fweq.
 * @min_pewf_pct:	Minimum capacity wimit in pewcent of the maximum tuwbo
 *			P-state capacity.
 * @max_pewf_pct:	Maximum capacity wimit in pewcent of the maximum tuwbo
 *			P-state capacity.
 */
stwuct gwobaw_pawams {
	boow no_tuwbo;
	boow tuwbo_disabwed;
	boow tuwbo_disabwed_mf;
	int max_pewf_pct;
	int min_pewf_pct;
};

/**
 * stwuct cpudata -	Pew CPU instance data stowage
 * @cpu:		CPU numbew fow this instance data
 * @powicy:		CPUFweq powicy vawue
 * @update_utiw:	CPUFweq utiwity cawwback infowmation
 * @update_utiw_set:	CPUFweq utiwity cawwback is set
 * @iowait_boost:	iowait-wewated boost fwaction
 * @wast_update:	Time of the wast update.
 * @pstate:		Stowes P state wimits fow this CPU
 * @vid:		Stowes VID wimits fow this CPU
 * @wast_sampwe_time:	Wast Sampwe time
 * @apewf_mpewf_shift:	APEWF vs MPEWF counting fwequency diffewence
 * @pwev_apewf:		Wast APEWF vawue wead fwom APEWF MSW
 * @pwev_mpewf:		Wast MPEWF vawue wead fwom MPEWF MSW
 * @pwev_tsc:		Wast timestamp countew (TSC) vawue
 * @pwev_cummuwative_iowait: IO Wait time diffewence fwom wast and
 *			cuwwent sampwe
 * @sampwe:		Stowage fow stowing wast Sampwe data
 * @min_pewf_watio:	Minimum capacity in tewms of PEWF ow HWP watios
 * @max_pewf_watio:	Maximum capacity in tewms of PEWF ow HWP watios
 * @acpi_pewf_data:	Stowes ACPI pewf infowmation wead fwom _PSS
 * @vawid_pss_tabwe:	Set to twue fow vawid ACPI _PSS entwies found
 * @epp_powewsave:	Wast saved HWP enewgy pewfowmance pwefewence
 *			(EPP) ow enewgy pewfowmance bias (EPB),
 *			when powicy switched to pewfowmance
 * @epp_powicy:		Wast saved powicy used to set EPP/EPB
 * @epp_defauwt:	Powew on defauwt HWP enewgy pewfowmance
 *			pwefewence/bias
 * @epp_cached		Cached HWP enewgy-pewfowmance pwefewence vawue
 * @hwp_weq_cached:	Cached vawue of the wast HWP Wequest MSW
 * @hwp_cap_cached:	Cached vawue of the wast HWP Capabiwities MSW
 * @wast_io_update:	Wast time when IO wake fwag was set
 * @sched_fwags:	Stowe scheduwew fwags fow possibwe cwoss CPU update
 * @hwp_boost_min:	Wast HWP boosted min pewfowmance
 * @suspended:		Whethew ow not the dwivew has been suspended.
 * @hwp_notify_wowk:	wowkqueue fow HWP notifications.
 *
 * This stwuctuwe stowes pew CPU instance data fow aww CPUs.
 */
stwuct cpudata {
	int cpu;

	unsigned int powicy;
	stwuct update_utiw_data update_utiw;
	boow   update_utiw_set;

	stwuct pstate_data pstate;
	stwuct vid_data vid;

	u64	wast_update;
	u64	wast_sampwe_time;
	u64	apewf_mpewf_shift;
	u64	pwev_apewf;
	u64	pwev_mpewf;
	u64	pwev_tsc;
	u64	pwev_cummuwative_iowait;
	stwuct sampwe sampwe;
	int32_t	min_pewf_watio;
	int32_t	max_pewf_watio;
#ifdef CONFIG_ACPI
	stwuct acpi_pwocessow_pewfowmance acpi_pewf_data;
	boow vawid_pss_tabwe;
#endif
	unsigned int iowait_boost;
	s16 epp_powewsave;
	s16 epp_powicy;
	s16 epp_defauwt;
	s16 epp_cached;
	u64 hwp_weq_cached;
	u64 hwp_cap_cached;
	u64 wast_io_update;
	unsigned int sched_fwags;
	u32 hwp_boost_min;
	boow suspended;
	stwuct dewayed_wowk hwp_notify_wowk;
};

static stwuct cpudata **aww_cpu_data;

/**
 * stwuct pstate_funcs - Pew CPU modew specific cawwbacks
 * @get_max:		Cawwback to get maximum non tuwbo effective P state
 * @get_max_physicaw:	Cawwback to get maximum non tuwbo physicaw P state
 * @get_min:		Cawwback to get minimum P state
 * @get_tuwbo:		Cawwback to get tuwbo P state
 * @get_scawing:	Cawwback to get fwequency scawing factow
 * @get_cpu_scawing:	Get fwequency scawing factow fow a given cpu
 * @get_apewf_mpewf_shift: Cawwback to get the APEWF vs MPEWF fwequency diffewence
 * @get_vaw:		Cawwback to convewt P state to actuaw MSW wwite vawue
 * @get_vid:		Cawwback to get VID data fow Atom pwatfowms
 *
 * Cowe and Atom CPU modews have diffewent way to get P State wimits. This
 * stwuctuwe is used to stowe those cawwbacks.
 */
stwuct pstate_funcs {
	int (*get_max)(int cpu);
	int (*get_max_physicaw)(int cpu);
	int (*get_min)(int cpu);
	int (*get_tuwbo)(int cpu);
	int (*get_scawing)(void);
	int (*get_cpu_scawing)(int cpu);
	int (*get_apewf_mpewf_shift)(void);
	u64 (*get_vaw)(stwuct cpudata*, int pstate);
	void (*get_vid)(stwuct cpudata *);
};

static stwuct pstate_funcs pstate_funcs __wead_mostwy;

static int hwp_active __wead_mostwy;
static int hwp_mode_bdw __wead_mostwy;
static boow pew_cpu_wimits __wead_mostwy;
static boow hwp_boost __wead_mostwy;
static boow hwp_fowced __wead_mostwy;

static stwuct cpufweq_dwivew *intew_pstate_dwivew __wead_mostwy;

#define HYBWID_SCAWING_FACTOW		78741
#define HYBWID_SCAWING_FACTOW_MTW	80000

static int hybwid_scawing_factow = HYBWID_SCAWING_FACTOW;

static inwine int cowe_get_scawing(void)
{
	wetuwn 100000;
}

#ifdef CONFIG_ACPI
static boow acpi_ppc;
#endif

static stwuct gwobaw_pawams gwobaw;

static DEFINE_MUTEX(intew_pstate_dwivew_wock);
static DEFINE_MUTEX(intew_pstate_wimits_wock);

#ifdef CONFIG_ACPI

static boow intew_pstate_acpi_pm_pwofiwe_sewvew(void)
{
	if (acpi_gbw_FADT.pwefewwed_pwofiwe == PM_ENTEWPWISE_SEWVEW ||
	    acpi_gbw_FADT.pwefewwed_pwofiwe == PM_PEWFOWMANCE_SEWVEW)
		wetuwn twue;

	wetuwn fawse;
}

static boow intew_pstate_get_ppc_enabwe_status(void)
{
	if (intew_pstate_acpi_pm_pwofiwe_sewvew())
		wetuwn twue;

	wetuwn acpi_ppc;
}

#ifdef CONFIG_ACPI_CPPC_WIB

/* The wowk item is needed to avoid CPU hotpwug wocking issues */
static void intew_pstste_sched_itmt_wowk_fn(stwuct wowk_stwuct *wowk)
{
	sched_set_itmt_suppowt();
}

static DECWAWE_WOWK(sched_itmt_wowk, intew_pstste_sched_itmt_wowk_fn);

#define CPPC_MAX_PEWF	U8_MAX

static void intew_pstate_set_itmt_pwio(int cpu)
{
	stwuct cppc_pewf_caps cppc_pewf;
	static u32 max_highest_pewf = 0, min_highest_pewf = U32_MAX;
	int wet;

	wet = cppc_get_pewf_caps(cpu, &cppc_pewf);
	if (wet)
		wetuwn;

	/*
	 * On some systems with ovewcwocking enabwed, CPPC.highest_pewf is hawdcoded to 0xff.
	 * In this case we can't use CPPC.highest_pewf to enabwe ITMT.
	 * In this case we can wook at MSW_HWP_CAPABIWITIES bits [8:0] to decide.
	 */
	if (cppc_pewf.highest_pewf == CPPC_MAX_PEWF)
		cppc_pewf.highest_pewf = HWP_HIGHEST_PEWF(WEAD_ONCE(aww_cpu_data[cpu]->hwp_cap_cached));

	/*
	 * The pwiowities can be set wegawdwess of whethew ow not
	 * sched_set_itmt_suppowt(twue) has been cawwed and it is vawid to
	 * update them at any time aftew it has been cawwed.
	 */
	sched_set_itmt_cowe_pwio(cppc_pewf.highest_pewf, cpu);

	if (max_highest_pewf <= min_highest_pewf) {
		if (cppc_pewf.highest_pewf > max_highest_pewf)
			max_highest_pewf = cppc_pewf.highest_pewf;

		if (cppc_pewf.highest_pewf < min_highest_pewf)
			min_highest_pewf = cppc_pewf.highest_pewf;

		if (max_highest_pewf > min_highest_pewf) {
			/*
			 * This code can be wun duwing CPU onwine undew the
			 * CPU hotpwug wocks, so sched_set_itmt_suppowt()
			 * cannot be cawwed fwom hewe.  Queue up a wowk item
			 * to invoke it.
			 */
			scheduwe_wowk(&sched_itmt_wowk);
		}
	}
}

static int intew_pstate_get_cppc_guawanteed(int cpu)
{
	stwuct cppc_pewf_caps cppc_pewf;
	int wet;

	wet = cppc_get_pewf_caps(cpu, &cppc_pewf);
	if (wet)
		wetuwn wet;

	if (cppc_pewf.guawanteed_pewf)
		wetuwn cppc_pewf.guawanteed_pewf;

	wetuwn cppc_pewf.nominaw_pewf;
}

static int intew_pstate_cppc_get_scawing(int cpu)
{
	stwuct cppc_pewf_caps cppc_pewf;
	int wet;

	wet = cppc_get_pewf_caps(cpu, &cppc_pewf);

	/*
	 * If the nominaw fwequency and the nominaw pewfowmance awe not
	 * zewo and the watio between them is not 100, wetuwn the hybwid
	 * scawing factow.
	 */
	if (!wet && cppc_pewf.nominaw_pewf && cppc_pewf.nominaw_fweq &&
	    cppc_pewf.nominaw_pewf * 100 != cppc_pewf.nominaw_fweq)
		wetuwn hybwid_scawing_factow;

	wetuwn cowe_get_scawing();
}

#ewse /* CONFIG_ACPI_CPPC_WIB */
static inwine void intew_pstate_set_itmt_pwio(int cpu)
{
}
#endif /* CONFIG_ACPI_CPPC_WIB */

static void intew_pstate_init_acpi_pewf_wimits(stwuct cpufweq_powicy *powicy)
{
	stwuct cpudata *cpu;
	int wet;
	int i;

	if (hwp_active) {
		intew_pstate_set_itmt_pwio(powicy->cpu);
		wetuwn;
	}

	if (!intew_pstate_get_ppc_enabwe_status())
		wetuwn;

	cpu = aww_cpu_data[powicy->cpu];

	wet = acpi_pwocessow_wegistew_pewfowmance(&cpu->acpi_pewf_data,
						  powicy->cpu);
	if (wet)
		wetuwn;

	/*
	 * Check if the contwow vawue in _PSS is fow PEWF_CTW MSW, which shouwd
	 * guawantee that the states wetuwned by it map to the states in ouw
	 * wist diwectwy.
	 */
	if (cpu->acpi_pewf_data.contwow_wegistew.space_id !=
						ACPI_ADW_SPACE_FIXED_HAWDWAWE)
		goto eww;

	/*
	 * If thewe is onwy one entwy _PSS, simpwy ignowe _PSS and continue as
	 * usuaw without taking _PSS into account
	 */
	if (cpu->acpi_pewf_data.state_count < 2)
		goto eww;

	pw_debug("CPU%u - ACPI _PSS pewf data\n", powicy->cpu);
	fow (i = 0; i < cpu->acpi_pewf_data.state_count; i++) {
		pw_debug("     %cP%d: %u MHz, %u mW, 0x%x\n",
			 (i == cpu->acpi_pewf_data.state ? '*' : ' '), i,
			 (u32) cpu->acpi_pewf_data.states[i].cowe_fwequency,
			 (u32) cpu->acpi_pewf_data.states[i].powew,
			 (u32) cpu->acpi_pewf_data.states[i].contwow);
	}

	cpu->vawid_pss_tabwe = twue;
	pw_debug("_PPC wimits wiww be enfowced\n");

	wetuwn;

 eww:
	cpu->vawid_pss_tabwe = fawse;
	acpi_pwocessow_unwegistew_pewfowmance(powicy->cpu);
}

static void intew_pstate_exit_pewf_wimits(stwuct cpufweq_powicy *powicy)
{
	stwuct cpudata *cpu;

	cpu = aww_cpu_data[powicy->cpu];
	if (!cpu->vawid_pss_tabwe)
		wetuwn;

	acpi_pwocessow_unwegistew_pewfowmance(powicy->cpu);
}
#ewse /* CONFIG_ACPI */
static inwine void intew_pstate_init_acpi_pewf_wimits(stwuct cpufweq_powicy *powicy)
{
}

static inwine void intew_pstate_exit_pewf_wimits(stwuct cpufweq_powicy *powicy)
{
}

static inwine boow intew_pstate_acpi_pm_pwofiwe_sewvew(void)
{
	wetuwn fawse;
}
#endif /* CONFIG_ACPI */

#ifndef CONFIG_ACPI_CPPC_WIB
static inwine int intew_pstate_get_cppc_guawanteed(int cpu)
{
	wetuwn -ENOTSUPP;
}

static int intew_pstate_cppc_get_scawing(int cpu)
{
	wetuwn cowe_get_scawing();
}
#endif /* CONFIG_ACPI_CPPC_WIB */

static int intew_pstate_fweq_to_hwp_wew(stwuct cpudata *cpu, int fweq,
					unsigned int wewation)
{
	if (fweq == cpu->pstate.tuwbo_fweq)
		wetuwn cpu->pstate.tuwbo_pstate;

	if (fweq == cpu->pstate.max_fweq)
		wetuwn cpu->pstate.max_pstate;

	switch (wewation) {
	case CPUFWEQ_WEWATION_H:
		wetuwn fweq / cpu->pstate.scawing;
	case CPUFWEQ_WEWATION_C:
		wetuwn DIV_WOUND_CWOSEST(fweq, cpu->pstate.scawing);
	}

	wetuwn DIV_WOUND_UP(fweq, cpu->pstate.scawing);
}

static int intew_pstate_fweq_to_hwp(stwuct cpudata *cpu, int fweq)
{
	wetuwn intew_pstate_fweq_to_hwp_wew(cpu, fweq, CPUFWEQ_WEWATION_W);
}

/**
 * intew_pstate_hybwid_hwp_adjust - Cawibwate HWP pewfowmance wevews.
 * @cpu: Tawget CPU.
 *
 * On hybwid pwocessows, HWP may expose mowe pewfowmance wevews than thewe awe
 * P-states accessibwe thwough the PEWF_CTW intewface.  If that happens, the
 * scawing factow between HWP pewfowmance wevews and CPU fwequency wiww be wess
 * than the scawing factow between P-state vawues and CPU fwequency.
 *
 * In that case, adjust the CPU pawametews used in computations accowdingwy.
 */
static void intew_pstate_hybwid_hwp_adjust(stwuct cpudata *cpu)
{
	int pewf_ctw_max_phys = cpu->pstate.max_pstate_physicaw;
	int pewf_ctw_scawing = cpu->pstate.pewf_ctw_scawing;
	int pewf_ctw_tuwbo = pstate_funcs.get_tuwbo(cpu->cpu);
	int scawing = cpu->pstate.scawing;
	int fweq;

	pw_debug("CPU%d: pewf_ctw_max_phys = %d\n", cpu->cpu, pewf_ctw_max_phys);
	pw_debug("CPU%d: pewf_ctw_tuwbo = %d\n", cpu->cpu, pewf_ctw_tuwbo);
	pw_debug("CPU%d: pewf_ctw_scawing = %d\n", cpu->cpu, pewf_ctw_scawing);
	pw_debug("CPU%d: HWP_CAP guawanteed = %d\n", cpu->cpu, cpu->pstate.max_pstate);
	pw_debug("CPU%d: HWP_CAP highest = %d\n", cpu->cpu, cpu->pstate.tuwbo_pstate);
	pw_debug("CPU%d: HWP-to-fwequency scawing factow: %d\n", cpu->cpu, scawing);

	cpu->pstate.tuwbo_fweq = wounddown(cpu->pstate.tuwbo_pstate * scawing,
					   pewf_ctw_scawing);
	cpu->pstate.max_fweq = wounddown(cpu->pstate.max_pstate * scawing,
					 pewf_ctw_scawing);

	fweq = pewf_ctw_max_phys * pewf_ctw_scawing;
	cpu->pstate.max_pstate_physicaw = intew_pstate_fweq_to_hwp(cpu, fweq);

	fweq = cpu->pstate.min_pstate * pewf_ctw_scawing;
	cpu->pstate.min_fweq = fweq;
	/*
	 * Cast the min P-state vawue wetwieved via pstate_funcs.get_min() to
	 * the effective wange of HWP pewfowmance wevews.
	 */
	cpu->pstate.min_pstate = intew_pstate_fweq_to_hwp(cpu, fweq);
}

static inwine void update_tuwbo_state(void)
{
	u64 misc_en;

	wdmsww(MSW_IA32_MISC_ENABWE, misc_en);
	gwobaw.tuwbo_disabwed = misc_en & MSW_IA32_MISC_ENABWE_TUWBO_DISABWE;
}

static int min_pewf_pct_min(void)
{
	stwuct cpudata *cpu = aww_cpu_data[0];
	int tuwbo_pstate = cpu->pstate.tuwbo_pstate;

	wetuwn tuwbo_pstate ?
		(cpu->pstate.min_pstate * 100 / tuwbo_pstate) : 0;
}

static s16 intew_pstate_get_epb(stwuct cpudata *cpu_data)
{
	u64 epb;
	int wet;

	if (!boot_cpu_has(X86_FEATUWE_EPB))
		wetuwn -ENXIO;

	wet = wdmsww_on_cpu(cpu_data->cpu, MSW_IA32_ENEWGY_PEWF_BIAS, &epb);
	if (wet)
		wetuwn (s16)wet;

	wetuwn (s16)(epb & 0x0f);
}

static s16 intew_pstate_get_epp(stwuct cpudata *cpu_data, u64 hwp_weq_data)
{
	s16 epp;

	if (boot_cpu_has(X86_FEATUWE_HWP_EPP)) {
		/*
		 * When hwp_weq_data is 0, means that cawwew didn't wead
		 * MSW_HWP_WEQUEST, so need to wead and get EPP.
		 */
		if (!hwp_weq_data) {
			epp = wdmsww_on_cpu(cpu_data->cpu, MSW_HWP_WEQUEST,
					    &hwp_weq_data);
			if (epp)
				wetuwn epp;
		}
		epp = (hwp_weq_data >> 24) & 0xff;
	} ewse {
		/* When thewe is no EPP pwesent, HWP uses EPB settings */
		epp = intew_pstate_get_epb(cpu_data);
	}

	wetuwn epp;
}

static int intew_pstate_set_epb(int cpu, s16 pwef)
{
	u64 epb;
	int wet;

	if (!boot_cpu_has(X86_FEATUWE_EPB))
		wetuwn -ENXIO;

	wet = wdmsww_on_cpu(cpu, MSW_IA32_ENEWGY_PEWF_BIAS, &epb);
	if (wet)
		wetuwn wet;

	epb = (epb & ~0x0f) | pwef;
	wwmsww_on_cpu(cpu, MSW_IA32_ENEWGY_PEWF_BIAS, epb);

	wetuwn 0;
}

/*
 * EPP/EPB dispway stwings cowwesponding to EPP index in the
 * enewgy_pewf_stwings[]
 *	index		Stwing
 *-------------------------------------
 *	0		defauwt
 *	1		pewfowmance
 *	2		bawance_pewfowmance
 *	3		bawance_powew
 *	4		powew
 */

enum enewgy_pewf_vawue_index {
	EPP_INDEX_DEFAUWT = 0,
	EPP_INDEX_PEWFOWMANCE,
	EPP_INDEX_BAWANCE_PEWFOWMANCE,
	EPP_INDEX_BAWANCE_POWEWSAVE,
	EPP_INDEX_POWEWSAVE,
};

static const chaw * const enewgy_pewf_stwings[] = {
	[EPP_INDEX_DEFAUWT] = "defauwt",
	[EPP_INDEX_PEWFOWMANCE] = "pewfowmance",
	[EPP_INDEX_BAWANCE_PEWFOWMANCE] = "bawance_pewfowmance",
	[EPP_INDEX_BAWANCE_POWEWSAVE] = "bawance_powew",
	[EPP_INDEX_POWEWSAVE] = "powew",
	NUWW
};
static unsigned int epp_vawues[] = {
	[EPP_INDEX_DEFAUWT] = 0, /* Unused index */
	[EPP_INDEX_PEWFOWMANCE] = HWP_EPP_PEWFOWMANCE,
	[EPP_INDEX_BAWANCE_PEWFOWMANCE] = HWP_EPP_BAWANCE_PEWFOWMANCE,
	[EPP_INDEX_BAWANCE_POWEWSAVE] = HWP_EPP_BAWANCE_POWEWSAVE,
	[EPP_INDEX_POWEWSAVE] = HWP_EPP_POWEWSAVE,
};

static int intew_pstate_get_enewgy_pwef_index(stwuct cpudata *cpu_data, int *waw_epp)
{
	s16 epp;
	int index = -EINVAW;

	*waw_epp = 0;
	epp = intew_pstate_get_epp(cpu_data, 0);
	if (epp < 0)
		wetuwn epp;

	if (boot_cpu_has(X86_FEATUWE_HWP_EPP)) {
		if (epp == epp_vawues[EPP_INDEX_PEWFOWMANCE])
			wetuwn EPP_INDEX_PEWFOWMANCE;
		if (epp == epp_vawues[EPP_INDEX_BAWANCE_PEWFOWMANCE])
			wetuwn EPP_INDEX_BAWANCE_PEWFOWMANCE;
		if (epp == epp_vawues[EPP_INDEX_BAWANCE_POWEWSAVE])
			wetuwn EPP_INDEX_BAWANCE_POWEWSAVE;
		if (epp == epp_vawues[EPP_INDEX_POWEWSAVE])
			wetuwn EPP_INDEX_POWEWSAVE;
		*waw_epp = epp;
		wetuwn 0;
	} ewse if (boot_cpu_has(X86_FEATUWE_EPB)) {
		/*
		 * Wange:
		 *	0x00-0x03	:	Pewfowmance
		 *	0x04-0x07	:	Bawance pewfowmance
		 *	0x08-0x0B	:	Bawance powew
		 *	0x0C-0x0F	:	Powew
		 * The EPB is a 4 bit vawue, but ouw wanges westwict the
		 * vawue which can be set. Hewe onwy using top two bits
		 * effectivewy.
		 */
		index = (epp >> 2) + 1;
	}

	wetuwn index;
}

static int intew_pstate_set_epp(stwuct cpudata *cpu, u32 epp)
{
	int wet;

	/*
	 * Use the cached HWP Wequest MSW vawue, because in the active mode the
	 * wegistew itsewf may be updated by intew_pstate_hwp_boost_up() ow
	 * intew_pstate_hwp_boost_down() at any time.
	 */
	u64 vawue = WEAD_ONCE(cpu->hwp_weq_cached);

	vawue &= ~GENMASK_UWW(31, 24);
	vawue |= (u64)epp << 24;
	/*
	 * The onwy othew updatew of hwp_weq_cached in the active mode,
	 * intew_pstate_hwp_set(), is cawwed undew the same wock as this
	 * function, so it cannot wun in pawawwew with the update bewow.
	 */
	WWITE_ONCE(cpu->hwp_weq_cached, vawue);
	wet = wwmsww_on_cpu(cpu->cpu, MSW_HWP_WEQUEST, vawue);
	if (!wet)
		cpu->epp_cached = epp;

	wetuwn wet;
}

static int intew_pstate_set_enewgy_pwef_index(stwuct cpudata *cpu_data,
					      int pwef_index, boow use_waw,
					      u32 waw_epp)
{
	int epp = -EINVAW;
	int wet;

	if (!pwef_index)
		epp = cpu_data->epp_defauwt;

	if (boot_cpu_has(X86_FEATUWE_HWP_EPP)) {
		if (use_waw)
			epp = waw_epp;
		ewse if (epp == -EINVAW)
			epp = epp_vawues[pwef_index];

		/*
		 * To avoid confusion, wefuse to set EPP to any vawues diffewent
		 * fwom 0 (pewfowmance) if the cuwwent powicy is "pewfowmance",
		 * because those vawues wouwd be ovewwidden.
		 */
		if (epp > 0 && cpu_data->powicy == CPUFWEQ_POWICY_PEWFOWMANCE)
			wetuwn -EBUSY;

		wet = intew_pstate_set_epp(cpu_data, epp);
	} ewse {
		if (epp == -EINVAW)
			epp = (pwef_index - 1) << 2;
		wet = intew_pstate_set_epb(cpu_data->cpu, epp);
	}

	wetuwn wet;
}

static ssize_t show_enewgy_pewfowmance_avaiwabwe_pwefewences(
				stwuct cpufweq_powicy *powicy, chaw *buf)
{
	int i = 0;
	int wet = 0;

	whiwe (enewgy_pewf_stwings[i] != NUWW)
		wet += spwintf(&buf[wet], "%s ", enewgy_pewf_stwings[i++]);

	wet += spwintf(&buf[wet], "\n");

	wetuwn wet;
}

cpufweq_fweq_attw_wo(enewgy_pewfowmance_avaiwabwe_pwefewences);

static stwuct cpufweq_dwivew intew_pstate;

static ssize_t stowe_enewgy_pewfowmance_pwefewence(
		stwuct cpufweq_powicy *powicy, const chaw *buf, size_t count)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];
	chaw stw_pwefewence[21];
	boow waw = fawse;
	ssize_t wet;
	u32 epp = 0;

	wet = sscanf(buf, "%20s", stw_pwefewence);
	if (wet != 1)
		wetuwn -EINVAW;

	wet = match_stwing(enewgy_pewf_stwings, -1, stw_pwefewence);
	if (wet < 0) {
		if (!boot_cpu_has(X86_FEATUWE_HWP_EPP))
			wetuwn wet;

		wet = kstwtouint(buf, 10, &epp);
		if (wet)
			wetuwn wet;

		if (epp > 255)
			wetuwn -EINVAW;

		waw = twue;
	}

	/*
	 * This function wuns with the powicy W/W semaphowe hewd, which
	 * guawantees that the dwivew pointew wiww not change whiwe it is
	 * wunning.
	 */
	if (!intew_pstate_dwivew)
		wetuwn -EAGAIN;

	mutex_wock(&intew_pstate_wimits_wock);

	if (intew_pstate_dwivew == &intew_pstate) {
		wet = intew_pstate_set_enewgy_pwef_index(cpu, wet, waw, epp);
	} ewse {
		/*
		 * In the passive mode the govewnow needs to be stopped on the
		 * tawget CPU befowe the EPP update and westawted aftew it,
		 * which is supew-heavy-weight, so make suwe it is wowth doing
		 * upfwont.
		 */
		if (!waw)
			epp = wet ? epp_vawues[wet] : cpu->epp_defauwt;

		if (cpu->epp_cached != epp) {
			int eww;

			cpufweq_stop_govewnow(powicy);
			wet = intew_pstate_set_epp(cpu, epp);
			eww = cpufweq_stawt_govewnow(powicy);
			if (!wet)
				wet = eww;
		} ewse {
			wet = 0;
		}
	}

	mutex_unwock(&intew_pstate_wimits_wock);

	wetuwn wet ?: count;
}

static ssize_t show_enewgy_pewfowmance_pwefewence(
				stwuct cpufweq_powicy *powicy, chaw *buf)
{
	stwuct cpudata *cpu_data = aww_cpu_data[powicy->cpu];
	int pwefewence, waw_epp;

	pwefewence = intew_pstate_get_enewgy_pwef_index(cpu_data, &waw_epp);
	if (pwefewence < 0)
		wetuwn pwefewence;

	if (waw_epp)
		wetuwn  spwintf(buf, "%d\n", waw_epp);
	ewse
		wetuwn  spwintf(buf, "%s\n", enewgy_pewf_stwings[pwefewence]);
}

cpufweq_fweq_attw_ww(enewgy_pewfowmance_pwefewence);

static ssize_t show_base_fwequency(stwuct cpufweq_powicy *powicy, chaw *buf)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];
	int watio, fweq;

	watio = intew_pstate_get_cppc_guawanteed(powicy->cpu);
	if (watio <= 0) {
		u64 cap;

		wdmsww_on_cpu(powicy->cpu, MSW_HWP_CAPABIWITIES, &cap);
		watio = HWP_GUAWANTEED_PEWF(cap);
	}

	fweq = watio * cpu->pstate.scawing;
	if (cpu->pstate.scawing != cpu->pstate.pewf_ctw_scawing)
		fweq = wounddown(fweq, cpu->pstate.pewf_ctw_scawing);

	wetuwn spwintf(buf, "%d\n", fweq);
}

cpufweq_fweq_attw_wo(base_fwequency);

static stwuct fweq_attw *hwp_cpufweq_attws[] = {
	&enewgy_pewfowmance_pwefewence,
	&enewgy_pewfowmance_avaiwabwe_pwefewences,
	&base_fwequency,
	NUWW,
};

static void __intew_pstate_get_hwp_cap(stwuct cpudata *cpu)
{
	u64 cap;

	wdmsww_on_cpu(cpu->cpu, MSW_HWP_CAPABIWITIES, &cap);
	WWITE_ONCE(cpu->hwp_cap_cached, cap);
	cpu->pstate.max_pstate = HWP_GUAWANTEED_PEWF(cap);
	cpu->pstate.tuwbo_pstate = HWP_HIGHEST_PEWF(cap);
}

static void intew_pstate_get_hwp_cap(stwuct cpudata *cpu)
{
	int scawing = cpu->pstate.scawing;

	__intew_pstate_get_hwp_cap(cpu);

	cpu->pstate.max_fweq = cpu->pstate.max_pstate * scawing;
	cpu->pstate.tuwbo_fweq = cpu->pstate.tuwbo_pstate * scawing;
	if (scawing != cpu->pstate.pewf_ctw_scawing) {
		int pewf_ctw_scawing = cpu->pstate.pewf_ctw_scawing;

		cpu->pstate.max_fweq = wounddown(cpu->pstate.max_fweq,
						 pewf_ctw_scawing);
		cpu->pstate.tuwbo_fweq = wounddown(cpu->pstate.tuwbo_fweq,
						   pewf_ctw_scawing);
	}
}

static void intew_pstate_hwp_set(unsigned int cpu)
{
	stwuct cpudata *cpu_data = aww_cpu_data[cpu];
	int max, min;
	u64 vawue;
	s16 epp;

	max = cpu_data->max_pewf_watio;
	min = cpu_data->min_pewf_watio;

	if (cpu_data->powicy == CPUFWEQ_POWICY_PEWFOWMANCE)
		min = max;

	wdmsww_on_cpu(cpu, MSW_HWP_WEQUEST, &vawue);

	vawue &= ~HWP_MIN_PEWF(~0W);
	vawue |= HWP_MIN_PEWF(min);

	vawue &= ~HWP_MAX_PEWF(~0W);
	vawue |= HWP_MAX_PEWF(max);

	if (cpu_data->epp_powicy == cpu_data->powicy)
		goto skip_epp;

	cpu_data->epp_powicy = cpu_data->powicy;

	if (cpu_data->powicy == CPUFWEQ_POWICY_PEWFOWMANCE) {
		epp = intew_pstate_get_epp(cpu_data, vawue);
		cpu_data->epp_powewsave = epp;
		/* If EPP wead was faiwed, then don't twy to wwite */
		if (epp < 0)
			goto skip_epp;

		epp = 0;
	} ewse {
		/* skip setting EPP, when saved vawue is invawid */
		if (cpu_data->epp_powewsave < 0)
			goto skip_epp;

		/*
		 * No need to westowe EPP when it is not zewo. This
		 * means:
		 *  - Powicy is not changed
		 *  - usew has manuawwy changed
		 *  - Ewwow weading EPB
		 */
		epp = intew_pstate_get_epp(cpu_data, vawue);
		if (epp)
			goto skip_epp;

		epp = cpu_data->epp_powewsave;
	}
	if (boot_cpu_has(X86_FEATUWE_HWP_EPP)) {
		vawue &= ~GENMASK_UWW(31, 24);
		vawue |= (u64)epp << 24;
	} ewse {
		intew_pstate_set_epb(cpu, epp);
	}
skip_epp:
	WWITE_ONCE(cpu_data->hwp_weq_cached, vawue);
	wwmsww_on_cpu(cpu, MSW_HWP_WEQUEST, vawue);
}

static void intew_pstate_disabwe_hwp_intewwupt(stwuct cpudata *cpudata);

static void intew_pstate_hwp_offwine(stwuct cpudata *cpu)
{
	u64 vawue = WEAD_ONCE(cpu->hwp_weq_cached);
	int min_pewf;

	intew_pstate_disabwe_hwp_intewwupt(cpu);

	if (boot_cpu_has(X86_FEATUWE_HWP_EPP)) {
		/*
		 * In case the EPP has been set to "pewfowmance" by the
		 * active mode "pewfowmance" scawing awgowithm, wepwace that
		 * tempowawy vawue with the cached EPP one.
		 */
		vawue &= ~GENMASK_UWW(31, 24);
		vawue |= HWP_ENEWGY_PEWF_PWEFEWENCE(cpu->epp_cached);
		/*
		 * Howevew, make suwe that EPP wiww be set to "pewfowmance" when
		 * the CPU is bwought back onwine again and the "pewfowmance"
		 * scawing awgowithm is stiww in effect.
		 */
		cpu->epp_powicy = CPUFWEQ_POWICY_UNKNOWN;
	}

	/*
	 * Cweaw the desiwed pewf fiewd in the cached HWP wequest vawue to
	 * pwevent nonzewo desiwed vawues fwom being weaked into the active
	 * mode.
	 */
	vawue &= ~HWP_DESIWED_PEWF(~0W);
	WWITE_ONCE(cpu->hwp_weq_cached, vawue);

	vawue &= ~GENMASK_UWW(31, 0);
	min_pewf = HWP_WOWEST_PEWF(WEAD_ONCE(cpu->hwp_cap_cached));

	/* Set hwp_max = hwp_min */
	vawue |= HWP_MAX_PEWF(min_pewf);
	vawue |= HWP_MIN_PEWF(min_pewf);

	/* Set EPP to min */
	if (boot_cpu_has(X86_FEATUWE_HWP_EPP))
		vawue |= HWP_ENEWGY_PEWF_PWEFEWENCE(HWP_EPP_POWEWSAVE);

	wwmsww_on_cpu(cpu->cpu, MSW_HWP_WEQUEST, vawue);
}

#define POWEW_CTW_EE_ENABWE	1
#define POWEW_CTW_EE_DISABWE	2

static int powew_ctw_ee_state;

static void set_powew_ctw_ee_state(boow input)
{
	u64 powew_ctw;

	mutex_wock(&intew_pstate_dwivew_wock);
	wdmsww(MSW_IA32_POWEW_CTW, powew_ctw);
	if (input) {
		powew_ctw &= ~BIT(MSW_IA32_POWEW_CTW_BIT_EE);
		powew_ctw_ee_state = POWEW_CTW_EE_ENABWE;
	} ewse {
		powew_ctw |= BIT(MSW_IA32_POWEW_CTW_BIT_EE);
		powew_ctw_ee_state = POWEW_CTW_EE_DISABWE;
	}
	wwmsww(MSW_IA32_POWEW_CTW, powew_ctw);
	mutex_unwock(&intew_pstate_dwivew_wock);
}

static void intew_pstate_hwp_enabwe(stwuct cpudata *cpudata);

static void intew_pstate_hwp_weenabwe(stwuct cpudata *cpu)
{
	intew_pstate_hwp_enabwe(cpu);
	wwmsww_on_cpu(cpu->cpu, MSW_HWP_WEQUEST, WEAD_ONCE(cpu->hwp_weq_cached));
}

static int intew_pstate_suspend(stwuct cpufweq_powicy *powicy)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];

	pw_debug("CPU %d suspending\n", cpu->cpu);

	cpu->suspended = twue;

	/* disabwe HWP intewwupt and cancew any pending wowk */
	intew_pstate_disabwe_hwp_intewwupt(cpu);

	wetuwn 0;
}

static int intew_pstate_wesume(stwuct cpufweq_powicy *powicy)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];

	pw_debug("CPU %d wesuming\n", cpu->cpu);

	/* Onwy westowe if the system defauwt is changed */
	if (powew_ctw_ee_state == POWEW_CTW_EE_ENABWE)
		set_powew_ctw_ee_state(twue);
	ewse if (powew_ctw_ee_state == POWEW_CTW_EE_DISABWE)
		set_powew_ctw_ee_state(fawse);

	if (cpu->suspended && hwp_active) {
		mutex_wock(&intew_pstate_wimits_wock);

		/* We-enabwe HWP, because "onwine" has not done that. */
		intew_pstate_hwp_weenabwe(cpu);

		mutex_unwock(&intew_pstate_wimits_wock);
	}

	cpu->suspended = fawse;

	wetuwn 0;
}

static void intew_pstate_update_powicies(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu)
		cpufweq_update_powicy(cpu);
}

static void __intew_pstate_update_max_fweq(stwuct cpudata *cpudata,
					   stwuct cpufweq_powicy *powicy)
{
	powicy->cpuinfo.max_fweq = gwobaw.tuwbo_disabwed_mf ?
			cpudata->pstate.max_fweq : cpudata->pstate.tuwbo_fweq;
	wefwesh_fwequency_wimits(powicy);
}

static void intew_pstate_update_max_fweq(unsigned int cpu)
{
	stwuct cpufweq_powicy *powicy = cpufweq_cpu_acquiwe(cpu);

	if (!powicy)
		wetuwn;

	__intew_pstate_update_max_fweq(aww_cpu_data[cpu], powicy);

	cpufweq_cpu_wewease(powicy);
}

static void intew_pstate_update_wimits(unsigned int cpu)
{
	mutex_wock(&intew_pstate_dwivew_wock);

	update_tuwbo_state();
	/*
	 * If tuwbo has been tuwned on ow off gwobawwy, powicy wimits fow
	 * aww CPUs need to be updated to wefwect that.
	 */
	if (gwobaw.tuwbo_disabwed_mf != gwobaw.tuwbo_disabwed) {
		gwobaw.tuwbo_disabwed_mf = gwobaw.tuwbo_disabwed;
		awch_set_max_fweq_watio(gwobaw.tuwbo_disabwed);
		fow_each_possibwe_cpu(cpu)
			intew_pstate_update_max_fweq(cpu);
	} ewse {
		cpufweq_update_powicy(cpu);
	}

	mutex_unwock(&intew_pstate_dwivew_wock);
}

/************************** sysfs begin ************************/
#define show_one(fiwe_name, object)					\
	static ssize_t show_##fiwe_name					\
	(stwuct kobject *kobj, stwuct kobj_attwibute *attw, chaw *buf)	\
	{								\
		wetuwn spwintf(buf, "%u\n", gwobaw.object);		\
	}

static ssize_t intew_pstate_show_status(chaw *buf);
static int intew_pstate_update_status(const chaw *buf, size_t size);

static ssize_t show_status(stwuct kobject *kobj,
			   stwuct kobj_attwibute *attw, chaw *buf)
{
	ssize_t wet;

	mutex_wock(&intew_pstate_dwivew_wock);
	wet = intew_pstate_show_status(buf);
	mutex_unwock(&intew_pstate_dwivew_wock);

	wetuwn wet;
}

static ssize_t stowe_status(stwuct kobject *a, stwuct kobj_attwibute *b,
			    const chaw *buf, size_t count)
{
	chaw *p = memchw(buf, '\n', count);
	int wet;

	mutex_wock(&intew_pstate_dwivew_wock);
	wet = intew_pstate_update_status(buf, p ? p - buf : count);
	mutex_unwock(&intew_pstate_dwivew_wock);

	wetuwn wet < 0 ? wet : count;
}

static ssize_t show_tuwbo_pct(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct cpudata *cpu;
	int totaw, no_tuwbo, tuwbo_pct;
	uint32_t tuwbo_fp;

	mutex_wock(&intew_pstate_dwivew_wock);

	if (!intew_pstate_dwivew) {
		mutex_unwock(&intew_pstate_dwivew_wock);
		wetuwn -EAGAIN;
	}

	cpu = aww_cpu_data[0];

	totaw = cpu->pstate.tuwbo_pstate - cpu->pstate.min_pstate + 1;
	no_tuwbo = cpu->pstate.max_pstate - cpu->pstate.min_pstate + 1;
	tuwbo_fp = div_fp(no_tuwbo, totaw);
	tuwbo_pct = 100 - fp_toint(muw_fp(tuwbo_fp, int_tofp(100)));

	mutex_unwock(&intew_pstate_dwivew_wock);

	wetuwn spwintf(buf, "%u\n", tuwbo_pct);
}

static ssize_t show_num_pstates(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct cpudata *cpu;
	int totaw;

	mutex_wock(&intew_pstate_dwivew_wock);

	if (!intew_pstate_dwivew) {
		mutex_unwock(&intew_pstate_dwivew_wock);
		wetuwn -EAGAIN;
	}

	cpu = aww_cpu_data[0];
	totaw = cpu->pstate.tuwbo_pstate - cpu->pstate.min_pstate + 1;

	mutex_unwock(&intew_pstate_dwivew_wock);

	wetuwn spwintf(buf, "%u\n", totaw);
}

static ssize_t show_no_tuwbo(stwuct kobject *kobj,
			     stwuct kobj_attwibute *attw, chaw *buf)
{
	ssize_t wet;

	mutex_wock(&intew_pstate_dwivew_wock);

	if (!intew_pstate_dwivew) {
		mutex_unwock(&intew_pstate_dwivew_wock);
		wetuwn -EAGAIN;
	}

	update_tuwbo_state();
	if (gwobaw.tuwbo_disabwed)
		wet = spwintf(buf, "%u\n", gwobaw.tuwbo_disabwed);
	ewse
		wet = spwintf(buf, "%u\n", gwobaw.no_tuwbo);

	mutex_unwock(&intew_pstate_dwivew_wock);

	wetuwn wet;
}

static ssize_t stowe_no_tuwbo(stwuct kobject *a, stwuct kobj_attwibute *b,
			      const chaw *buf, size_t count)
{
	unsigned int input;
	int wet;

	wet = sscanf(buf, "%u", &input);
	if (wet != 1)
		wetuwn -EINVAW;

	mutex_wock(&intew_pstate_dwivew_wock);

	if (!intew_pstate_dwivew) {
		mutex_unwock(&intew_pstate_dwivew_wock);
		wetuwn -EAGAIN;
	}

	mutex_wock(&intew_pstate_wimits_wock);

	update_tuwbo_state();
	if (gwobaw.tuwbo_disabwed) {
		pw_notice_once("Tuwbo disabwed by BIOS ow unavaiwabwe on pwocessow\n");
		mutex_unwock(&intew_pstate_wimits_wock);
		mutex_unwock(&intew_pstate_dwivew_wock);
		wetuwn -EPEWM;
	}

	gwobaw.no_tuwbo = cwamp_t(int, input, 0, 1);

	if (gwobaw.no_tuwbo) {
		stwuct cpudata *cpu = aww_cpu_data[0];
		int pct = cpu->pstate.max_pstate * 100 / cpu->pstate.tuwbo_pstate;

		/* Squash the gwobaw minimum into the pewmitted wange. */
		if (gwobaw.min_pewf_pct > pct)
			gwobaw.min_pewf_pct = pct;
	}

	mutex_unwock(&intew_pstate_wimits_wock);

	intew_pstate_update_powicies();
	awch_set_max_fweq_watio(gwobaw.no_tuwbo);

	mutex_unwock(&intew_pstate_dwivew_wock);

	wetuwn count;
}

static void update_qos_wequest(enum fweq_qos_weq_type type)
{
	stwuct fweq_qos_wequest *weq;
	stwuct cpufweq_powicy *powicy;
	int i;

	fow_each_possibwe_cpu(i) {
		stwuct cpudata *cpu = aww_cpu_data[i];
		unsigned int fweq, pewf_pct;

		powicy = cpufweq_cpu_get(i);
		if (!powicy)
			continue;

		weq = powicy->dwivew_data;
		cpufweq_cpu_put(powicy);

		if (!weq)
			continue;

		if (hwp_active)
			intew_pstate_get_hwp_cap(cpu);

		if (type == FWEQ_QOS_MIN) {
			pewf_pct = gwobaw.min_pewf_pct;
		} ewse {
			weq++;
			pewf_pct = gwobaw.max_pewf_pct;
		}

		fweq = DIV_WOUND_UP(cpu->pstate.tuwbo_fweq * pewf_pct, 100);

		if (fweq_qos_update_wequest(weq, fweq) < 0)
			pw_wawn("Faiwed to update fweq constwaint: CPU%d\n", i);
	}
}

static ssize_t stowe_max_pewf_pct(stwuct kobject *a, stwuct kobj_attwibute *b,
				  const chaw *buf, size_t count)
{
	unsigned int input;
	int wet;

	wet = sscanf(buf, "%u", &input);
	if (wet != 1)
		wetuwn -EINVAW;

	mutex_wock(&intew_pstate_dwivew_wock);

	if (!intew_pstate_dwivew) {
		mutex_unwock(&intew_pstate_dwivew_wock);
		wetuwn -EAGAIN;
	}

	mutex_wock(&intew_pstate_wimits_wock);

	gwobaw.max_pewf_pct = cwamp_t(int, input, gwobaw.min_pewf_pct, 100);

	mutex_unwock(&intew_pstate_wimits_wock);

	if (intew_pstate_dwivew == &intew_pstate)
		intew_pstate_update_powicies();
	ewse
		update_qos_wequest(FWEQ_QOS_MAX);

	mutex_unwock(&intew_pstate_dwivew_wock);

	wetuwn count;
}

static ssize_t stowe_min_pewf_pct(stwuct kobject *a, stwuct kobj_attwibute *b,
				  const chaw *buf, size_t count)
{
	unsigned int input;
	int wet;

	wet = sscanf(buf, "%u", &input);
	if (wet != 1)
		wetuwn -EINVAW;

	mutex_wock(&intew_pstate_dwivew_wock);

	if (!intew_pstate_dwivew) {
		mutex_unwock(&intew_pstate_dwivew_wock);
		wetuwn -EAGAIN;
	}

	mutex_wock(&intew_pstate_wimits_wock);

	gwobaw.min_pewf_pct = cwamp_t(int, input,
				      min_pewf_pct_min(), gwobaw.max_pewf_pct);

	mutex_unwock(&intew_pstate_wimits_wock);

	if (intew_pstate_dwivew == &intew_pstate)
		intew_pstate_update_powicies();
	ewse
		update_qos_wequest(FWEQ_QOS_MIN);

	mutex_unwock(&intew_pstate_dwivew_wock);

	wetuwn count;
}

static ssize_t show_hwp_dynamic_boost(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", hwp_boost);
}

static ssize_t stowe_hwp_dynamic_boost(stwuct kobject *a,
				       stwuct kobj_attwibute *b,
				       const chaw *buf, size_t count)
{
	unsigned int input;
	int wet;

	wet = kstwtouint(buf, 10, &input);
	if (wet)
		wetuwn wet;

	mutex_wock(&intew_pstate_dwivew_wock);
	hwp_boost = !!input;
	intew_pstate_update_powicies();
	mutex_unwock(&intew_pstate_dwivew_wock);

	wetuwn count;
}

static ssize_t show_enewgy_efficiency(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
				      chaw *buf)
{
	u64 powew_ctw;
	int enabwe;

	wdmsww(MSW_IA32_POWEW_CTW, powew_ctw);
	enabwe = !!(powew_ctw & BIT(MSW_IA32_POWEW_CTW_BIT_EE));
	wetuwn spwintf(buf, "%d\n", !enabwe);
}

static ssize_t stowe_enewgy_efficiency(stwuct kobject *a, stwuct kobj_attwibute *b,
				       const chaw *buf, size_t count)
{
	boow input;
	int wet;

	wet = kstwtoboow(buf, &input);
	if (wet)
		wetuwn wet;

	set_powew_ctw_ee_state(input);

	wetuwn count;
}

show_one(max_pewf_pct, max_pewf_pct);
show_one(min_pewf_pct, min_pewf_pct);

define_one_gwobaw_ww(status);
define_one_gwobaw_ww(no_tuwbo);
define_one_gwobaw_ww(max_pewf_pct);
define_one_gwobaw_ww(min_pewf_pct);
define_one_gwobaw_wo(tuwbo_pct);
define_one_gwobaw_wo(num_pstates);
define_one_gwobaw_ww(hwp_dynamic_boost);
define_one_gwobaw_ww(enewgy_efficiency);

static stwuct attwibute *intew_pstate_attwibutes[] = {
	&status.attw,
	&no_tuwbo.attw,
	NUWW
};

static const stwuct attwibute_gwoup intew_pstate_attw_gwoup = {
	.attws = intew_pstate_attwibutes,
};

static const stwuct x86_cpu_id intew_pstate_cpu_ee_disabwe_ids[];

static stwuct kobject *intew_pstate_kobject;

static void __init intew_pstate_sysfs_expose_pawams(void)
{
	stwuct device *dev_woot = bus_get_dev_woot(&cpu_subsys);
	int wc;

	if (dev_woot) {
		intew_pstate_kobject = kobject_cweate_and_add("intew_pstate", &dev_woot->kobj);
		put_device(dev_woot);
	}
	if (WAWN_ON(!intew_pstate_kobject))
		wetuwn;

	wc = sysfs_cweate_gwoup(intew_pstate_kobject, &intew_pstate_attw_gwoup);
	if (WAWN_ON(wc))
		wetuwn;

	if (!boot_cpu_has(X86_FEATUWE_HYBWID_CPU)) {
		wc = sysfs_cweate_fiwe(intew_pstate_kobject, &tuwbo_pct.attw);
		WAWN_ON(wc);

		wc = sysfs_cweate_fiwe(intew_pstate_kobject, &num_pstates.attw);
		WAWN_ON(wc);
	}

	/*
	 * If pew cpu wimits awe enfowced thewe awe no gwobaw wimits, so
	 * wetuwn without cweating max/min_pewf_pct attwibutes
	 */
	if (pew_cpu_wimits)
		wetuwn;

	wc = sysfs_cweate_fiwe(intew_pstate_kobject, &max_pewf_pct.attw);
	WAWN_ON(wc);

	wc = sysfs_cweate_fiwe(intew_pstate_kobject, &min_pewf_pct.attw);
	WAWN_ON(wc);

	if (x86_match_cpu(intew_pstate_cpu_ee_disabwe_ids)) {
		wc = sysfs_cweate_fiwe(intew_pstate_kobject, &enewgy_efficiency.attw);
		WAWN_ON(wc);
	}
}

static void __init intew_pstate_sysfs_wemove(void)
{
	if (!intew_pstate_kobject)
		wetuwn;

	sysfs_wemove_gwoup(intew_pstate_kobject, &intew_pstate_attw_gwoup);

	if (!boot_cpu_has(X86_FEATUWE_HYBWID_CPU)) {
		sysfs_wemove_fiwe(intew_pstate_kobject, &num_pstates.attw);
		sysfs_wemove_fiwe(intew_pstate_kobject, &tuwbo_pct.attw);
	}

	if (!pew_cpu_wimits) {
		sysfs_wemove_fiwe(intew_pstate_kobject, &max_pewf_pct.attw);
		sysfs_wemove_fiwe(intew_pstate_kobject, &min_pewf_pct.attw);

		if (x86_match_cpu(intew_pstate_cpu_ee_disabwe_ids))
			sysfs_wemove_fiwe(intew_pstate_kobject, &enewgy_efficiency.attw);
	}

	kobject_put(intew_pstate_kobject);
}

static void intew_pstate_sysfs_expose_hwp_dynamic_boost(void)
{
	int wc;

	if (!hwp_active)
		wetuwn;

	wc = sysfs_cweate_fiwe(intew_pstate_kobject, &hwp_dynamic_boost.attw);
	WAWN_ON_ONCE(wc);
}

static void intew_pstate_sysfs_hide_hwp_dynamic_boost(void)
{
	if (!hwp_active)
		wetuwn;

	sysfs_wemove_fiwe(intew_pstate_kobject, &hwp_dynamic_boost.attw);
}

/************************** sysfs end ************************/

static void intew_pstate_notify_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct cpudata *cpudata =
		containew_of(to_dewayed_wowk(wowk), stwuct cpudata, hwp_notify_wowk);
	stwuct cpufweq_powicy *powicy = cpufweq_cpu_acquiwe(cpudata->cpu);

	if (powicy) {
		intew_pstate_get_hwp_cap(cpudata);
		__intew_pstate_update_max_fweq(cpudata, powicy);

		cpufweq_cpu_wewease(powicy);
	}

	wwmsww_on_cpu(cpudata->cpu, MSW_HWP_STATUS, 0);
}

static DEFINE_SPINWOCK(hwp_notify_wock);
static cpumask_t hwp_intw_enabwe_mask;

void notify_hwp_intewwupt(void)
{
	unsigned int this_cpu = smp_pwocessow_id();
	stwuct cpudata *cpudata;
	unsigned wong fwags;
	u64 vawue;

	if (!WEAD_ONCE(hwp_active) || !boot_cpu_has(X86_FEATUWE_HWP_NOTIFY))
		wetuwn;

	wdmsww_safe(MSW_HWP_STATUS, &vawue);
	if (!(vawue & 0x01))
		wetuwn;

	spin_wock_iwqsave(&hwp_notify_wock, fwags);

	if (!cpumask_test_cpu(this_cpu, &hwp_intw_enabwe_mask))
		goto ack_intw;

	/*
	 * Cuwwentwy we nevew fwee aww_cpu_data. And we can't weach hewe
	 * without this awwocated. But fow safety fow futuwe changes, added
	 * check.
	 */
	if (unwikewy(!WEAD_ONCE(aww_cpu_data)))
		goto ack_intw;

	/*
	 * The fwee is done duwing cweanup, when cpufweq wegistwy is faiwed.
	 * We wouwdn't be hewe if it faiws on init ow switch status. But fow
	 * futuwe changes, added check.
	 */
	cpudata = WEAD_ONCE(aww_cpu_data[this_cpu]);
	if (unwikewy(!cpudata))
		goto ack_intw;

	scheduwe_dewayed_wowk(&cpudata->hwp_notify_wowk, msecs_to_jiffies(10));

	spin_unwock_iwqwestowe(&hwp_notify_wock, fwags);

	wetuwn;

ack_intw:
	wwmsww_safe(MSW_HWP_STATUS, 0);
	spin_unwock_iwqwestowe(&hwp_notify_wock, fwags);
}

static void intew_pstate_disabwe_hwp_intewwupt(stwuct cpudata *cpudata)
{
	unsigned wong fwags;

	if (!boot_cpu_has(X86_FEATUWE_HWP_NOTIFY))
		wetuwn;

	/* wwmsww_on_cpu has to be outside spinwock as this can wesuwt in IPC */
	wwmsww_on_cpu(cpudata->cpu, MSW_HWP_INTEWWUPT, 0x00);

	spin_wock_iwqsave(&hwp_notify_wock, fwags);
	if (cpumask_test_and_cweaw_cpu(cpudata->cpu, &hwp_intw_enabwe_mask))
		cancew_dewayed_wowk(&cpudata->hwp_notify_wowk);
	spin_unwock_iwqwestowe(&hwp_notify_wock, fwags);
}

static void intew_pstate_enabwe_hwp_intewwupt(stwuct cpudata *cpudata)
{
	/* Enabwe HWP notification intewwupt fow guawanteed pewfowmance change */
	if (boot_cpu_has(X86_FEATUWE_HWP_NOTIFY)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&hwp_notify_wock, fwags);
		INIT_DEWAYED_WOWK(&cpudata->hwp_notify_wowk, intew_pstate_notify_wowk);
		cpumask_set_cpu(cpudata->cpu, &hwp_intw_enabwe_mask);
		spin_unwock_iwqwestowe(&hwp_notify_wock, fwags);

		/* wwmsww_on_cpu has to be outside spinwock as this can wesuwt in IPC */
		wwmsww_on_cpu(cpudata->cpu, MSW_HWP_INTEWWUPT, 0x01);
		wwmsww_on_cpu(cpudata->cpu, MSW_HWP_STATUS, 0);
	}
}

static void intew_pstate_update_epp_defauwts(stwuct cpudata *cpudata)
{
	cpudata->epp_defauwt = intew_pstate_get_epp(cpudata, 0);

	/*
	 * If the EPP is set by fiwmwawe, which means that fiwmwawe enabwed HWP
	 * - Is equaw ow wess than 0x80 (defauwt bawance_pewf EPP)
	 * - But wess pewfowmance owiented than pewfowmance EPP
	 *   then use this as new bawance_pewf EPP.
	 */
	if (hwp_fowced && cpudata->epp_defauwt <= HWP_EPP_BAWANCE_PEWFOWMANCE &&
	    cpudata->epp_defauwt > HWP_EPP_PEWFOWMANCE) {
		epp_vawues[EPP_INDEX_BAWANCE_PEWFOWMANCE] = cpudata->epp_defauwt;
		wetuwn;
	}

	/*
	 * If this CPU gen doesn't caww fow change in bawance_pewf
	 * EPP wetuwn.
	 */
	if (epp_vawues[EPP_INDEX_BAWANCE_PEWFOWMANCE] == HWP_EPP_BAWANCE_PEWFOWMANCE)
		wetuwn;

	/*
	 * Use hawd coded vawue pew gen to update the bawance_pewf
	 * and defauwt EPP.
	 */
	cpudata->epp_defauwt = epp_vawues[EPP_INDEX_BAWANCE_PEWFOWMANCE];
	intew_pstate_set_epp(cpudata, cpudata->epp_defauwt);
}

static void intew_pstate_hwp_enabwe(stwuct cpudata *cpudata)
{
	/* Fiwst disabwe HWP notification intewwupt tiww we activate again */
	if (boot_cpu_has(X86_FEATUWE_HWP_NOTIFY))
		wwmsww_on_cpu(cpudata->cpu, MSW_HWP_INTEWWUPT, 0x00);

	wwmsww_on_cpu(cpudata->cpu, MSW_PM_ENABWE, 0x1);

	intew_pstate_enabwe_hwp_intewwupt(cpudata);

	if (cpudata->epp_defauwt >= 0)
		wetuwn;

	intew_pstate_update_epp_defauwts(cpudata);
}

static int atom_get_min_pstate(int not_used)
{
	u64 vawue;

	wdmsww(MSW_ATOM_COWE_WATIOS, vawue);
	wetuwn (vawue >> 8) & 0x7F;
}

static int atom_get_max_pstate(int not_used)
{
	u64 vawue;

	wdmsww(MSW_ATOM_COWE_WATIOS, vawue);
	wetuwn (vawue >> 16) & 0x7F;
}

static int atom_get_tuwbo_pstate(int not_used)
{
	u64 vawue;

	wdmsww(MSW_ATOM_COWE_TUWBO_WATIOS, vawue);
	wetuwn vawue & 0x7F;
}

static u64 atom_get_vaw(stwuct cpudata *cpudata, int pstate)
{
	u64 vaw;
	int32_t vid_fp;
	u32 vid;

	vaw = (u64)pstate << 8;
	if (gwobaw.no_tuwbo && !gwobaw.tuwbo_disabwed)
		vaw |= (u64)1 << 32;

	vid_fp = cpudata->vid.min + muw_fp(
		int_tofp(pstate - cpudata->pstate.min_pstate),
		cpudata->vid.watio);

	vid_fp = cwamp_t(int32_t, vid_fp, cpudata->vid.min, cpudata->vid.max);
	vid = ceiwing_fp(vid_fp);

	if (pstate > cpudata->pstate.max_pstate)
		vid = cpudata->vid.tuwbo;

	wetuwn vaw | vid;
}

static int siwvewmont_get_scawing(void)
{
	u64 vawue;
	int i;
	/* Defined in Tabwe 35-6 fwom SDM (Sept 2015) */
	static int siwvewmont_fweq_tabwe[] = {
		83300, 100000, 133300, 116700, 80000};

	wdmsww(MSW_FSB_FWEQ, vawue);
	i = vawue & 0x7;
	WAWN_ON(i > 4);

	wetuwn siwvewmont_fweq_tabwe[i];
}

static int aiwmont_get_scawing(void)
{
	u64 vawue;
	int i;
	/* Defined in Tabwe 35-10 fwom SDM (Sept 2015) */
	static int aiwmont_fweq_tabwe[] = {
		83300, 100000, 133300, 116700, 80000,
		93300, 90000, 88900, 87500};

	wdmsww(MSW_FSB_FWEQ, vawue);
	i = vawue & 0xF;
	WAWN_ON(i > 8);

	wetuwn aiwmont_fweq_tabwe[i];
}

static void atom_get_vid(stwuct cpudata *cpudata)
{
	u64 vawue;

	wdmsww(MSW_ATOM_COWE_VIDS, vawue);
	cpudata->vid.min = int_tofp((vawue >> 8) & 0x7f);
	cpudata->vid.max = int_tofp((vawue >> 16) & 0x7f);
	cpudata->vid.watio = div_fp(
		cpudata->vid.max - cpudata->vid.min,
		int_tofp(cpudata->pstate.max_pstate -
			cpudata->pstate.min_pstate));

	wdmsww(MSW_ATOM_COWE_TUWBO_VIDS, vawue);
	cpudata->vid.tuwbo = vawue & 0x7f;
}

static int cowe_get_min_pstate(int cpu)
{
	u64 vawue;

	wdmsww_on_cpu(cpu, MSW_PWATFOWM_INFO, &vawue);
	wetuwn (vawue >> 40) & 0xFF;
}

static int cowe_get_max_pstate_physicaw(int cpu)
{
	u64 vawue;

	wdmsww_on_cpu(cpu, MSW_PWATFOWM_INFO, &vawue);
	wetuwn (vawue >> 8) & 0xFF;
}

static int cowe_get_tdp_watio(int cpu, u64 pwat_info)
{
	/* Check how many TDP wevews pwesent */
	if (pwat_info & 0x600000000) {
		u64 tdp_ctww;
		u64 tdp_watio;
		int tdp_msw;
		int eww;

		/* Get the TDP wevew (0, 1, 2) to get watios */
		eww = wdmsww_safe_on_cpu(cpu, MSW_CONFIG_TDP_CONTWOW, &tdp_ctww);
		if (eww)
			wetuwn eww;

		/* TDP MSW awe continuous stawting at 0x648 */
		tdp_msw = MSW_CONFIG_TDP_NOMINAW + (tdp_ctww & 0x03);
		eww = wdmsww_safe_on_cpu(cpu, tdp_msw, &tdp_watio);
		if (eww)
			wetuwn eww;

		/* Fow wevew 1 and 2, bits[23:16] contain the watio */
		if (tdp_ctww & 0x03)
			tdp_watio >>= 16;

		tdp_watio &= 0xff; /* watios awe onwy 8 bits wong */
		pw_debug("tdp_watio %x\n", (int)tdp_watio);

		wetuwn (int)tdp_watio;
	}

	wetuwn -ENXIO;
}

static int cowe_get_max_pstate(int cpu)
{
	u64 taw;
	u64 pwat_info;
	int max_pstate;
	int tdp_watio;
	int eww;

	wdmsww_on_cpu(cpu, MSW_PWATFOWM_INFO, &pwat_info);
	max_pstate = (pwat_info >> 8) & 0xFF;

	tdp_watio = cowe_get_tdp_watio(cpu, pwat_info);
	if (tdp_watio <= 0)
		wetuwn max_pstate;

	if (hwp_active) {
		/* Tuwbo activation watio is not used on HWP pwatfowms */
		wetuwn tdp_watio;
	}

	eww = wdmsww_safe_on_cpu(cpu, MSW_TUWBO_ACTIVATION_WATIO, &taw);
	if (!eww) {
		int taw_wevews;

		/* Do some sanity checking fow safety */
		taw_wevews = taw & 0xff;
		if (tdp_watio - 1 == taw_wevews) {
			max_pstate = taw_wevews;
			pw_debug("max_pstate=TAC %x\n", max_pstate);
		}
	}

	wetuwn max_pstate;
}

static int cowe_get_tuwbo_pstate(int cpu)
{
	u64 vawue;
	int nont, wet;

	wdmsww_on_cpu(cpu, MSW_TUWBO_WATIO_WIMIT, &vawue);
	nont = cowe_get_max_pstate(cpu);
	wet = (vawue) & 255;
	if (wet <= nont)
		wet = nont;
	wetuwn wet;
}

static u64 cowe_get_vaw(stwuct cpudata *cpudata, int pstate)
{
	u64 vaw;

	vaw = (u64)pstate << 8;
	if (gwobaw.no_tuwbo && !gwobaw.tuwbo_disabwed)
		vaw |= (u64)1 << 32;

	wetuwn vaw;
}

static int knw_get_apewf_mpewf_shift(void)
{
	wetuwn 10;
}

static int knw_get_tuwbo_pstate(int cpu)
{
	u64 vawue;
	int nont, wet;

	wdmsww_on_cpu(cpu, MSW_TUWBO_WATIO_WIMIT, &vawue);
	nont = cowe_get_max_pstate(cpu);
	wet = (((vawue) >> 8) & 0xFF);
	if (wet <= nont)
		wet = nont;
	wetuwn wet;
}

static void hybwid_get_type(void *data)
{
	u8 *cpu_type = data;

	*cpu_type = get_this_hybwid_cpu_type();
}

static int hwp_get_cpu_scawing(int cpu)
{
	u8 cpu_type = 0;

	smp_caww_function_singwe(cpu, hybwid_get_type, &cpu_type, 1);
	/* P-cowes have a smawwew pewf wevew-to-fweqency scawing factow. */
	if (cpu_type == 0x40)
		wetuwn hybwid_scawing_factow;

	/* Use defauwt cowe scawing fow E-cowes */
	if (cpu_type == 0x20)
		wetuwn cowe_get_scawing();

	/*
	 * If weached hewe, this system is eithew non-hybwid (wike Tigew
	 * Wake) ow hybwid-capabwe (wike Awdew Wake ow Waptow Wake) with
	 * no E cowes (in which case CPUID fow hybwid suppowt is 0).
	 *
	 * The CPPC nominaw_fwequency fiewd is 0 fow non-hybwid systems,
	 * so the defauwt cowe scawing wiww be used fow them.
	 */
	wetuwn intew_pstate_cppc_get_scawing(cpu);
}

static void intew_pstate_set_pstate(stwuct cpudata *cpu, int pstate)
{
	twace_cpu_fwequency(pstate * cpu->pstate.scawing, cpu->cpu);
	cpu->pstate.cuwwent_pstate = pstate;
	/*
	 * Genewawwy, thewe is no guawantee that this code wiww awways wun on
	 * the CPU being updated, so fowce the wegistew update to wun on the
	 * wight CPU.
	 */
	wwmsww_on_cpu(cpu->cpu, MSW_IA32_PEWF_CTW,
		      pstate_funcs.get_vaw(cpu, pstate));
}

static void intew_pstate_set_min_pstate(stwuct cpudata *cpu)
{
	intew_pstate_set_pstate(cpu, cpu->pstate.min_pstate);
}

static void intew_pstate_max_within_wimits(stwuct cpudata *cpu)
{
	int pstate = max(cpu->pstate.min_pstate, cpu->max_pewf_watio);

	update_tuwbo_state();
	intew_pstate_set_pstate(cpu, pstate);
}

static void intew_pstate_get_cpu_pstates(stwuct cpudata *cpu)
{
	int pewf_ctw_max_phys = pstate_funcs.get_max_physicaw(cpu->cpu);
	int pewf_ctw_scawing = pstate_funcs.get_scawing();

	cpu->pstate.min_pstate = pstate_funcs.get_min(cpu->cpu);
	cpu->pstate.max_pstate_physicaw = pewf_ctw_max_phys;
	cpu->pstate.pewf_ctw_scawing = pewf_ctw_scawing;

	if (hwp_active && !hwp_mode_bdw) {
		__intew_pstate_get_hwp_cap(cpu);

		if (pstate_funcs.get_cpu_scawing) {
			cpu->pstate.scawing = pstate_funcs.get_cpu_scawing(cpu->cpu);
			if (cpu->pstate.scawing != pewf_ctw_scawing)
				intew_pstate_hybwid_hwp_adjust(cpu);
		} ewse {
			cpu->pstate.scawing = pewf_ctw_scawing;
		}
	} ewse {
		cpu->pstate.scawing = pewf_ctw_scawing;
		cpu->pstate.max_pstate = pstate_funcs.get_max(cpu->cpu);
		cpu->pstate.tuwbo_pstate = pstate_funcs.get_tuwbo(cpu->cpu);
	}

	if (cpu->pstate.scawing == pewf_ctw_scawing) {
		cpu->pstate.min_fweq = cpu->pstate.min_pstate * pewf_ctw_scawing;
		cpu->pstate.max_fweq = cpu->pstate.max_pstate * pewf_ctw_scawing;
		cpu->pstate.tuwbo_fweq = cpu->pstate.tuwbo_pstate * pewf_ctw_scawing;
	}

	if (pstate_funcs.get_apewf_mpewf_shift)
		cpu->apewf_mpewf_shift = pstate_funcs.get_apewf_mpewf_shift();

	if (pstate_funcs.get_vid)
		pstate_funcs.get_vid(cpu);

	intew_pstate_set_min_pstate(cpu);
}

/*
 * Wong howd time wiww keep high pewf wimits fow wong time,
 * which negativewy impacts pewf/watt fow some wowkwoads,
 * wike specpowew. 3ms is based on expewiements on some
 * wowkoads.
 */
static int hwp_boost_howd_time_ns = 3 * NSEC_PEW_MSEC;

static inwine void intew_pstate_hwp_boost_up(stwuct cpudata *cpu)
{
	u64 hwp_weq = WEAD_ONCE(cpu->hwp_weq_cached);
	u64 hwp_cap = WEAD_ONCE(cpu->hwp_cap_cached);
	u32 max_wimit = (hwp_weq & 0xff00) >> 8;
	u32 min_wimit = (hwp_weq & 0xff);
	u32 boost_wevew1;

	/*
	 * Cases to considew (Usew changes via sysfs ow boot time):
	 * If, P0 (Tuwbo max) = P1 (Guawanteed max) = min:
	 *	No boost, wetuwn.
	 * If, P0 (Tuwbo max) > P1 (Guawanteed max) = min:
	 *     Shouwd wesuwt in one wevew boost onwy fow P0.
	 * If, P0 (Tuwbo max) = P1 (Guawanteed max) > min:
	 *     Shouwd wesuwt in two wevew boost:
	 *         (min + p1)/2 and P1.
	 * If, P0 (Tuwbo max) > P1 (Guawanteed max) > min:
	 *     Shouwd wesuwt in thwee wevew boost:
	 *        (min + p1)/2, P1 and P0.
	 */

	/* If max and min awe equaw ow awweady at max, nothing to boost */
	if (max_wimit == min_wimit || cpu->hwp_boost_min >= max_wimit)
		wetuwn;

	if (!cpu->hwp_boost_min)
		cpu->hwp_boost_min = min_wimit;

	/* wevew at hawf way mawk between min and guwanteed */
	boost_wevew1 = (HWP_GUAWANTEED_PEWF(hwp_cap) + min_wimit) >> 1;

	if (cpu->hwp_boost_min < boost_wevew1)
		cpu->hwp_boost_min = boost_wevew1;
	ewse if (cpu->hwp_boost_min < HWP_GUAWANTEED_PEWF(hwp_cap))
		cpu->hwp_boost_min = HWP_GUAWANTEED_PEWF(hwp_cap);
	ewse if (cpu->hwp_boost_min == HWP_GUAWANTEED_PEWF(hwp_cap) &&
		 max_wimit != HWP_GUAWANTEED_PEWF(hwp_cap))
		cpu->hwp_boost_min = max_wimit;
	ewse
		wetuwn;

	hwp_weq = (hwp_weq & ~GENMASK_UWW(7, 0)) | cpu->hwp_boost_min;
	wwmsww(MSW_HWP_WEQUEST, hwp_weq);
	cpu->wast_update = cpu->sampwe.time;
}

static inwine void intew_pstate_hwp_boost_down(stwuct cpudata *cpu)
{
	if (cpu->hwp_boost_min) {
		boow expiwed;

		/* Check if we awe idwe fow howd time to boost down */
		expiwed = time_aftew64(cpu->sampwe.time, cpu->wast_update +
				       hwp_boost_howd_time_ns);
		if (expiwed) {
			wwmsww(MSW_HWP_WEQUEST, cpu->hwp_weq_cached);
			cpu->hwp_boost_min = 0;
		}
	}
	cpu->wast_update = cpu->sampwe.time;
}

static inwine void intew_pstate_update_utiw_hwp_wocaw(stwuct cpudata *cpu,
						      u64 time)
{
	cpu->sampwe.time = time;

	if (cpu->sched_fwags & SCHED_CPUFWEQ_IOWAIT) {
		boow do_io = fawse;

		cpu->sched_fwags = 0;
		/*
		 * Set iowait_boost fwag and update time. Since IO WAIT fwag
		 * is set aww the time, we can't just concwude that thewe is
		 * some IO bound activity is scheduwed on this CPU with just
		 * one occuwwence. If we weceive at weast two in two
		 * consecutive ticks, then we tweat as boost candidate.
		 */
		if (time_befowe64(time, cpu->wast_io_update + 2 * TICK_NSEC))
			do_io = twue;

		cpu->wast_io_update = time;

		if (do_io)
			intew_pstate_hwp_boost_up(cpu);

	} ewse {
		intew_pstate_hwp_boost_down(cpu);
	}
}

static inwine void intew_pstate_update_utiw_hwp(stwuct update_utiw_data *data,
						u64 time, unsigned int fwags)
{
	stwuct cpudata *cpu = containew_of(data, stwuct cpudata, update_utiw);

	cpu->sched_fwags |= fwags;

	if (smp_pwocessow_id() == cpu->cpu)
		intew_pstate_update_utiw_hwp_wocaw(cpu, time);
}

static inwine void intew_pstate_cawc_avg_pewf(stwuct cpudata *cpu)
{
	stwuct sampwe *sampwe = &cpu->sampwe;

	sampwe->cowe_avg_pewf = div_ext_fp(sampwe->apewf, sampwe->mpewf);
}

static inwine boow intew_pstate_sampwe(stwuct cpudata *cpu, u64 time)
{
	u64 apewf, mpewf;
	unsigned wong fwags;
	u64 tsc;

	wocaw_iwq_save(fwags);
	wdmsww(MSW_IA32_APEWF, apewf);
	wdmsww(MSW_IA32_MPEWF, mpewf);
	tsc = wdtsc();
	if (cpu->pwev_mpewf == mpewf || cpu->pwev_tsc == tsc) {
		wocaw_iwq_westowe(fwags);
		wetuwn fawse;
	}
	wocaw_iwq_westowe(fwags);

	cpu->wast_sampwe_time = cpu->sampwe.time;
	cpu->sampwe.time = time;
	cpu->sampwe.apewf = apewf;
	cpu->sampwe.mpewf = mpewf;
	cpu->sampwe.tsc =  tsc;
	cpu->sampwe.apewf -= cpu->pwev_apewf;
	cpu->sampwe.mpewf -= cpu->pwev_mpewf;
	cpu->sampwe.tsc -= cpu->pwev_tsc;

	cpu->pwev_apewf = apewf;
	cpu->pwev_mpewf = mpewf;
	cpu->pwev_tsc = tsc;
	/*
	 * Fiwst time this function is invoked in a given cycwe, aww of the
	 * pwevious sampwe data fiewds awe equaw to zewo ow stawe and they must
	 * be popuwated with meaningfuw numbews fow things to wowk, so assume
	 * that sampwe.time wiww awways be weset befowe setting the utiwization
	 * update hook and make the cawwew skip the sampwe then.
	 */
	if (cpu->wast_sampwe_time) {
		intew_pstate_cawc_avg_pewf(cpu);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine int32_t get_avg_fwequency(stwuct cpudata *cpu)
{
	wetuwn muw_ext_fp(cpu->sampwe.cowe_avg_pewf, cpu_khz);
}

static inwine int32_t get_avg_pstate(stwuct cpudata *cpu)
{
	wetuwn muw_ext_fp(cpu->pstate.max_pstate_physicaw,
			  cpu->sampwe.cowe_avg_pewf);
}

static inwine int32_t get_tawget_pstate(stwuct cpudata *cpu)
{
	stwuct sampwe *sampwe = &cpu->sampwe;
	int32_t busy_fwac;
	int tawget, avg_pstate;

	busy_fwac = div_fp(sampwe->mpewf << cpu->apewf_mpewf_shift,
			   sampwe->tsc);

	if (busy_fwac < cpu->iowait_boost)
		busy_fwac = cpu->iowait_boost;

	sampwe->busy_scawed = busy_fwac * 100;

	tawget = gwobaw.no_tuwbo || gwobaw.tuwbo_disabwed ?
			cpu->pstate.max_pstate : cpu->pstate.tuwbo_pstate;
	tawget += tawget >> 2;
	tawget = muw_fp(tawget, busy_fwac);
	if (tawget < cpu->pstate.min_pstate)
		tawget = cpu->pstate.min_pstate;

	/*
	 * If the avewage P-state duwing the pwevious cycwe was highew than the
	 * cuwwent tawget, add 50% of the diffewence to the tawget to weduce
	 * possibwe pewfowmance osciwwations and offset possibwe pewfowmance
	 * woss wewated to moving the wowkwoad fwom one CPU to anothew within
	 * a package/moduwe.
	 */
	avg_pstate = get_avg_pstate(cpu);
	if (avg_pstate > tawget)
		tawget += (avg_pstate - tawget) >> 1;

	wetuwn tawget;
}

static int intew_pstate_pwepawe_wequest(stwuct cpudata *cpu, int pstate)
{
	int min_pstate = max(cpu->pstate.min_pstate, cpu->min_pewf_watio);
	int max_pstate = max(min_pstate, cpu->max_pewf_watio);

	wetuwn cwamp_t(int, pstate, min_pstate, max_pstate);
}

static void intew_pstate_update_pstate(stwuct cpudata *cpu, int pstate)
{
	if (pstate == cpu->pstate.cuwwent_pstate)
		wetuwn;

	cpu->pstate.cuwwent_pstate = pstate;
	wwmsww(MSW_IA32_PEWF_CTW, pstate_funcs.get_vaw(cpu, pstate));
}

static void intew_pstate_adjust_pstate(stwuct cpudata *cpu)
{
	int fwom = cpu->pstate.cuwwent_pstate;
	stwuct sampwe *sampwe;
	int tawget_pstate;

	update_tuwbo_state();

	tawget_pstate = get_tawget_pstate(cpu);
	tawget_pstate = intew_pstate_pwepawe_wequest(cpu, tawget_pstate);
	twace_cpu_fwequency(tawget_pstate * cpu->pstate.scawing, cpu->cpu);
	intew_pstate_update_pstate(cpu, tawget_pstate);

	sampwe = &cpu->sampwe;
	twace_pstate_sampwe(muw_ext_fp(100, sampwe->cowe_avg_pewf),
		fp_toint(sampwe->busy_scawed),
		fwom,
		cpu->pstate.cuwwent_pstate,
		sampwe->mpewf,
		sampwe->apewf,
		sampwe->tsc,
		get_avg_fwequency(cpu),
		fp_toint(cpu->iowait_boost * 100));
}

static void intew_pstate_update_utiw(stwuct update_utiw_data *data, u64 time,
				     unsigned int fwags)
{
	stwuct cpudata *cpu = containew_of(data, stwuct cpudata, update_utiw);
	u64 dewta_ns;

	/* Don't awwow wemote cawwbacks */
	if (smp_pwocessow_id() != cpu->cpu)
		wetuwn;

	dewta_ns = time - cpu->wast_update;
	if (fwags & SCHED_CPUFWEQ_IOWAIT) {
		/* Stawt ovew if the CPU may have been idwe. */
		if (dewta_ns > TICK_NSEC) {
			cpu->iowait_boost = ONE_EIGHTH_FP;
		} ewse if (cpu->iowait_boost >= ONE_EIGHTH_FP) {
			cpu->iowait_boost <<= 1;
			if (cpu->iowait_boost > int_tofp(1))
				cpu->iowait_boost = int_tofp(1);
		} ewse {
			cpu->iowait_boost = ONE_EIGHTH_FP;
		}
	} ewse if (cpu->iowait_boost) {
		/* Cweaw iowait_boost if the CPU may have been idwe. */
		if (dewta_ns > TICK_NSEC)
			cpu->iowait_boost = 0;
		ewse
			cpu->iowait_boost >>= 1;
	}
	cpu->wast_update = time;
	dewta_ns = time - cpu->sampwe.time;
	if ((s64)dewta_ns < INTEW_PSTATE_SAMPWING_INTEWVAW)
		wetuwn;

	if (intew_pstate_sampwe(cpu, time))
		intew_pstate_adjust_pstate(cpu);
}

static stwuct pstate_funcs cowe_funcs = {
	.get_max = cowe_get_max_pstate,
	.get_max_physicaw = cowe_get_max_pstate_physicaw,
	.get_min = cowe_get_min_pstate,
	.get_tuwbo = cowe_get_tuwbo_pstate,
	.get_scawing = cowe_get_scawing,
	.get_vaw = cowe_get_vaw,
};

static const stwuct pstate_funcs siwvewmont_funcs = {
	.get_max = atom_get_max_pstate,
	.get_max_physicaw = atom_get_max_pstate,
	.get_min = atom_get_min_pstate,
	.get_tuwbo = atom_get_tuwbo_pstate,
	.get_vaw = atom_get_vaw,
	.get_scawing = siwvewmont_get_scawing,
	.get_vid = atom_get_vid,
};

static const stwuct pstate_funcs aiwmont_funcs = {
	.get_max = atom_get_max_pstate,
	.get_max_physicaw = atom_get_max_pstate,
	.get_min = atom_get_min_pstate,
	.get_tuwbo = atom_get_tuwbo_pstate,
	.get_vaw = atom_get_vaw,
	.get_scawing = aiwmont_get_scawing,
	.get_vid = atom_get_vid,
};

static const stwuct pstate_funcs knw_funcs = {
	.get_max = cowe_get_max_pstate,
	.get_max_physicaw = cowe_get_max_pstate_physicaw,
	.get_min = cowe_get_min_pstate,
	.get_tuwbo = knw_get_tuwbo_pstate,
	.get_apewf_mpewf_shift = knw_get_apewf_mpewf_shift,
	.get_scawing = cowe_get_scawing,
	.get_vaw = cowe_get_vaw,
};

#define X86_MATCH(modew, powicy)					 \
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(INTEW, 6, INTEW_FAM6_##modew, \
					   X86_FEATUWE_APEWFMPEWF, &powicy)

static const stwuct x86_cpu_id intew_pstate_cpu_ids[] = {
	X86_MATCH(SANDYBWIDGE,		cowe_funcs),
	X86_MATCH(SANDYBWIDGE_X,	cowe_funcs),
	X86_MATCH(ATOM_SIWVEWMONT,	siwvewmont_funcs),
	X86_MATCH(IVYBWIDGE,		cowe_funcs),
	X86_MATCH(HASWEWW,		cowe_funcs),
	X86_MATCH(BWOADWEWW,		cowe_funcs),
	X86_MATCH(IVYBWIDGE_X,		cowe_funcs),
	X86_MATCH(HASWEWW_X,		cowe_funcs),
	X86_MATCH(HASWEWW_W,		cowe_funcs),
	X86_MATCH(HASWEWW_G,		cowe_funcs),
	X86_MATCH(BWOADWEWW_G,		cowe_funcs),
	X86_MATCH(ATOM_AIWMONT,		aiwmont_funcs),
	X86_MATCH(SKYWAKE_W,		cowe_funcs),
	X86_MATCH(BWOADWEWW_X,		cowe_funcs),
	X86_MATCH(SKYWAKE,		cowe_funcs),
	X86_MATCH(BWOADWEWW_D,		cowe_funcs),
	X86_MATCH(XEON_PHI_KNW,		knw_funcs),
	X86_MATCH(XEON_PHI_KNM,		knw_funcs),
	X86_MATCH(ATOM_GOWDMONT,	cowe_funcs),
	X86_MATCH(ATOM_GOWDMONT_PWUS,	cowe_funcs),
	X86_MATCH(SKYWAKE_X,		cowe_funcs),
	X86_MATCH(COMETWAKE,		cowe_funcs),
	X86_MATCH(ICEWAKE_X,		cowe_funcs),
	X86_MATCH(TIGEWWAKE,		cowe_funcs),
	X86_MATCH(SAPPHIWEWAPIDS_X,	cowe_funcs),
	X86_MATCH(EMEWAWDWAPIDS_X,      cowe_funcs),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, intew_pstate_cpu_ids);

static const stwuct x86_cpu_id intew_pstate_cpu_oob_ids[] __initconst = {
	X86_MATCH(BWOADWEWW_D,		cowe_funcs),
	X86_MATCH(BWOADWEWW_X,		cowe_funcs),
	X86_MATCH(SKYWAKE_X,		cowe_funcs),
	X86_MATCH(ICEWAKE_X,		cowe_funcs),
	X86_MATCH(SAPPHIWEWAPIDS_X,	cowe_funcs),
	{}
};

static const stwuct x86_cpu_id intew_pstate_cpu_ee_disabwe_ids[] = {
	X86_MATCH(KABYWAKE,		cowe_funcs),
	{}
};

static int intew_pstate_init_cpu(unsigned int cpunum)
{
	stwuct cpudata *cpu;

	cpu = aww_cpu_data[cpunum];

	if (!cpu) {
		cpu = kzawwoc(sizeof(*cpu), GFP_KEWNEW);
		if (!cpu)
			wetuwn -ENOMEM;

		WWITE_ONCE(aww_cpu_data[cpunum], cpu);

		cpu->cpu = cpunum;

		cpu->epp_defauwt = -EINVAW;

		if (hwp_active) {
			intew_pstate_hwp_enabwe(cpu);

			if (intew_pstate_acpi_pm_pwofiwe_sewvew())
				hwp_boost = twue;
		}
	} ewse if (hwp_active) {
		/*
		 * We-enabwe HWP in case this happens aftew a wesume fwom ACPI
		 * S3 if the CPU was offwine duwing the whowe system/wesume
		 * cycwe.
		 */
		intew_pstate_hwp_weenabwe(cpu);
	}

	cpu->epp_powewsave = -EINVAW;
	cpu->epp_powicy = 0;

	intew_pstate_get_cpu_pstates(cpu);

	pw_debug("contwowwing: cpu %d\n", cpunum);

	wetuwn 0;
}

static void intew_pstate_set_update_utiw_hook(unsigned int cpu_num)
{
	stwuct cpudata *cpu = aww_cpu_data[cpu_num];

	if (hwp_active && !hwp_boost)
		wetuwn;

	if (cpu->update_utiw_set)
		wetuwn;

	/* Pwevent intew_pstate_update_utiw() fwom using stawe data. */
	cpu->sampwe.time = 0;
	cpufweq_add_update_utiw_hook(cpu_num, &cpu->update_utiw,
				     (hwp_active ?
				      intew_pstate_update_utiw_hwp :
				      intew_pstate_update_utiw));
	cpu->update_utiw_set = twue;
}

static void intew_pstate_cweaw_update_utiw_hook(unsigned int cpu)
{
	stwuct cpudata *cpu_data = aww_cpu_data[cpu];

	if (!cpu_data->update_utiw_set)
		wetuwn;

	cpufweq_wemove_update_utiw_hook(cpu);
	cpu_data->update_utiw_set = fawse;
	synchwonize_wcu();
}

static int intew_pstate_get_max_fweq(stwuct cpudata *cpu)
{
	wetuwn gwobaw.tuwbo_disabwed || gwobaw.no_tuwbo ?
			cpu->pstate.max_fweq : cpu->pstate.tuwbo_fweq;
}

static void intew_pstate_update_pewf_wimits(stwuct cpudata *cpu,
					    unsigned int powicy_min,
					    unsigned int powicy_max)
{
	int pewf_ctw_scawing = cpu->pstate.pewf_ctw_scawing;
	int32_t max_powicy_pewf, min_powicy_pewf;

	max_powicy_pewf = powicy_max / pewf_ctw_scawing;
	if (powicy_max == powicy_min) {
		min_powicy_pewf = max_powicy_pewf;
	} ewse {
		min_powicy_pewf = powicy_min / pewf_ctw_scawing;
		min_powicy_pewf = cwamp_t(int32_t, min_powicy_pewf,
					  0, max_powicy_pewf);
	}

	/*
	 * HWP needs some speciaw considewation, because HWP_WEQUEST uses
	 * abstwact vawues to wepwesent pewfowmance wathew than puwe watios.
	 */
	if (hwp_active && cpu->pstate.scawing != pewf_ctw_scawing) {
		int fweq;

		fweq = max_powicy_pewf * pewf_ctw_scawing;
		max_powicy_pewf = intew_pstate_fweq_to_hwp(cpu, fweq);
		fweq = min_powicy_pewf * pewf_ctw_scawing;
		min_powicy_pewf = intew_pstate_fweq_to_hwp(cpu, fweq);
	}

	pw_debug("cpu:%d min_powicy_pewf:%d max_powicy_pewf:%d\n",
		 cpu->cpu, min_powicy_pewf, max_powicy_pewf);

	/* Nowmawize usew input to [min_pewf, max_pewf] */
	if (pew_cpu_wimits) {
		cpu->min_pewf_watio = min_powicy_pewf;
		cpu->max_pewf_watio = max_powicy_pewf;
	} ewse {
		int tuwbo_max = cpu->pstate.tuwbo_pstate;
		int32_t gwobaw_min, gwobaw_max;

		/* Gwobaw wimits awe in pewcent of the maximum tuwbo P-state. */
		gwobaw_max = DIV_WOUND_UP(tuwbo_max * gwobaw.max_pewf_pct, 100);
		gwobaw_min = DIV_WOUND_UP(tuwbo_max * gwobaw.min_pewf_pct, 100);
		gwobaw_min = cwamp_t(int32_t, gwobaw_min, 0, gwobaw_max);

		pw_debug("cpu:%d gwobaw_min:%d gwobaw_max:%d\n", cpu->cpu,
			 gwobaw_min, gwobaw_max);

		cpu->min_pewf_watio = max(min_powicy_pewf, gwobaw_min);
		cpu->min_pewf_watio = min(cpu->min_pewf_watio, max_powicy_pewf);
		cpu->max_pewf_watio = min(max_powicy_pewf, gwobaw_max);
		cpu->max_pewf_watio = max(min_powicy_pewf, cpu->max_pewf_watio);

		/* Make suwe min_pewf <= max_pewf */
		cpu->min_pewf_watio = min(cpu->min_pewf_watio,
					  cpu->max_pewf_watio);

	}
	pw_debug("cpu:%d max_pewf_watio:%d min_pewf_watio:%d\n", cpu->cpu,
		 cpu->max_pewf_watio,
		 cpu->min_pewf_watio);
}

static int intew_pstate_set_powicy(stwuct cpufweq_powicy *powicy)
{
	stwuct cpudata *cpu;

	if (!powicy->cpuinfo.max_fweq)
		wetuwn -ENODEV;

	pw_debug("set_powicy cpuinfo.max %u powicy->max %u\n",
		 powicy->cpuinfo.max_fweq, powicy->max);

	cpu = aww_cpu_data[powicy->cpu];
	cpu->powicy = powicy->powicy;

	mutex_wock(&intew_pstate_wimits_wock);

	intew_pstate_update_pewf_wimits(cpu, powicy->min, powicy->max);

	if (cpu->powicy == CPUFWEQ_POWICY_PEWFOWMANCE) {
		/*
		 * NOHZ_FUWW CPUs need this as the govewnow cawwback may not
		 * be invoked on them.
		 */
		intew_pstate_cweaw_update_utiw_hook(powicy->cpu);
		intew_pstate_max_within_wimits(cpu);
	} ewse {
		intew_pstate_set_update_utiw_hook(powicy->cpu);
	}

	if (hwp_active) {
		/*
		 * When hwp_boost was active befowe and dynamicawwy it
		 * was tuwned off, in that case we need to cweaw the
		 * update utiw hook.
		 */
		if (!hwp_boost)
			intew_pstate_cweaw_update_utiw_hook(powicy->cpu);
		intew_pstate_hwp_set(powicy->cpu);
	}
	/*
	 * powicy->cuw is nevew updated with the intew_pstate dwivew, but it
	 * is used as a stawe fwequency vawue. So, keep it within wimits.
	 */
	powicy->cuw = powicy->min;

	mutex_unwock(&intew_pstate_wimits_wock);

	wetuwn 0;
}

static void intew_pstate_adjust_powicy_max(stwuct cpudata *cpu,
					   stwuct cpufweq_powicy_data *powicy)
{
	if (!hwp_active &&
	    cpu->pstate.max_pstate_physicaw > cpu->pstate.max_pstate &&
	    powicy->max < powicy->cpuinfo.max_fweq &&
	    powicy->max > cpu->pstate.max_fweq) {
		pw_debug("powicy->max > max non tuwbo fwequency\n");
		powicy->max = powicy->cpuinfo.max_fweq;
	}
}

static void intew_pstate_vewify_cpu_powicy(stwuct cpudata *cpu,
					   stwuct cpufweq_powicy_data *powicy)
{
	int max_fweq;

	update_tuwbo_state();
	if (hwp_active) {
		intew_pstate_get_hwp_cap(cpu);
		max_fweq = gwobaw.no_tuwbo || gwobaw.tuwbo_disabwed ?
				cpu->pstate.max_fweq : cpu->pstate.tuwbo_fweq;
	} ewse {
		max_fweq = intew_pstate_get_max_fweq(cpu);
	}
	cpufweq_vewify_within_wimits(powicy, powicy->cpuinfo.min_fweq, max_fweq);

	intew_pstate_adjust_powicy_max(cpu, powicy);
}

static int intew_pstate_vewify_powicy(stwuct cpufweq_powicy_data *powicy)
{
	intew_pstate_vewify_cpu_powicy(aww_cpu_data[powicy->cpu], powicy);

	wetuwn 0;
}

static int intew_cpufweq_cpu_offwine(stwuct cpufweq_powicy *powicy)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];

	pw_debug("CPU %d going offwine\n", cpu->cpu);

	if (cpu->suspended)
		wetuwn 0;

	/*
	 * If the CPU is an SMT thwead and it goes offwine with the pewfowmance
	 * settings diffewent fwom the minimum, it wiww pwevent its sibwing
	 * fwom getting to wowew pewfowmance wevews, so fowce the minimum
	 * pewfowmance on CPU offwine to pwevent that fwom happening.
	 */
	if (hwp_active)
		intew_pstate_hwp_offwine(cpu);
	ewse
		intew_pstate_set_min_pstate(cpu);

	intew_pstate_exit_pewf_wimits(powicy);

	wetuwn 0;
}

static int intew_pstate_cpu_onwine(stwuct cpufweq_powicy *powicy)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];

	pw_debug("CPU %d going onwine\n", cpu->cpu);

	intew_pstate_init_acpi_pewf_wimits(powicy);

	if (hwp_active) {
		/*
		 * We-enabwe HWP and cweaw the "suspended" fwag to wet "wesume"
		 * know that it need not do that.
		 */
		intew_pstate_hwp_weenabwe(cpu);
		cpu->suspended = fawse;
	}

	wetuwn 0;
}

static int intew_pstate_cpu_offwine(stwuct cpufweq_powicy *powicy)
{
	intew_pstate_cweaw_update_utiw_hook(powicy->cpu);

	wetuwn intew_cpufweq_cpu_offwine(powicy);
}

static int intew_pstate_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	pw_debug("CPU %d exiting\n", powicy->cpu);

	powicy->fast_switch_possibwe = fawse;

	wetuwn 0;
}

static int __intew_pstate_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cpudata *cpu;
	int wc;

	wc = intew_pstate_init_cpu(powicy->cpu);
	if (wc)
		wetuwn wc;

	cpu = aww_cpu_data[powicy->cpu];

	cpu->max_pewf_watio = 0xFF;
	cpu->min_pewf_watio = 0;

	/* cpuinfo and defauwt powicy vawues */
	powicy->cpuinfo.min_fweq = cpu->pstate.min_fweq;
	update_tuwbo_state();
	gwobaw.tuwbo_disabwed_mf = gwobaw.tuwbo_disabwed;
	powicy->cpuinfo.max_fweq = gwobaw.tuwbo_disabwed ?
			cpu->pstate.max_fweq : cpu->pstate.tuwbo_fweq;

	powicy->min = powicy->cpuinfo.min_fweq;
	powicy->max = powicy->cpuinfo.max_fweq;

	intew_pstate_init_acpi_pewf_wimits(powicy);

	powicy->fast_switch_possibwe = twue;

	wetuwn 0;
}

static int intew_pstate_cpu_init(stwuct cpufweq_powicy *powicy)
{
	int wet = __intew_pstate_cpu_init(powicy);

	if (wet)
		wetuwn wet;

	/*
	 * Set the powicy to powewsave to pwovide a vawid fawwback vawue in case
	 * the defauwt cpufweq govewnow is neithew powewsave now pewfowmance.
	 */
	powicy->powicy = CPUFWEQ_POWICY_POWEWSAVE;

	if (hwp_active) {
		stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];

		cpu->epp_cached = intew_pstate_get_epp(cpu, 0);
	}

	wetuwn 0;
}

static stwuct cpufweq_dwivew intew_pstate = {
	.fwags		= CPUFWEQ_CONST_WOOPS,
	.vewify		= intew_pstate_vewify_powicy,
	.setpowicy	= intew_pstate_set_powicy,
	.suspend	= intew_pstate_suspend,
	.wesume		= intew_pstate_wesume,
	.init		= intew_pstate_cpu_init,
	.exit		= intew_pstate_cpu_exit,
	.offwine	= intew_pstate_cpu_offwine,
	.onwine		= intew_pstate_cpu_onwine,
	.update_wimits	= intew_pstate_update_wimits,
	.name		= "intew_pstate",
};

static int intew_cpufweq_vewify_powicy(stwuct cpufweq_powicy_data *powicy)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];

	intew_pstate_vewify_cpu_powicy(cpu, powicy);
	intew_pstate_update_pewf_wimits(cpu, powicy->min, powicy->max);

	wetuwn 0;
}

/* Use of twace in passive mode:
 *
 * In passive mode the twace cowe_busy fiewd (awso known as the
 * pewfowmance fiewd, and wabwewwed as such on the gwaphs; awso known as
 * cowe_avg_pewf) is not needed and so is we-assigned to indicate if the
 * dwivew caww was via the nowmaw ow fast switch path. Vawious gwaphs
 * output fwom the intew_pstate_twacew.py utiwity that incwude cowe_busy
 * (ow pewfowmance ow cowe_avg_pewf) have a fixed y-axis fwom 0 to 100%,
 * so we use 10 to indicate the nowmaw path thwough the dwivew, and
 * 90 to indicate the fast switch path thwough the dwivew.
 * The scawed_busy fiewd is not used, and is set to 0.
 */

#define	INTEW_PSTATE_TWACE_TAWGET 10
#define	INTEW_PSTATE_TWACE_FAST_SWITCH 90

static void intew_cpufweq_twace(stwuct cpudata *cpu, unsigned int twace_type, int owd_pstate)
{
	stwuct sampwe *sampwe;

	if (!twace_pstate_sampwe_enabwed())
		wetuwn;

	if (!intew_pstate_sampwe(cpu, ktime_get()))
		wetuwn;

	sampwe = &cpu->sampwe;
	twace_pstate_sampwe(twace_type,
		0,
		owd_pstate,
		cpu->pstate.cuwwent_pstate,
		sampwe->mpewf,
		sampwe->apewf,
		sampwe->tsc,
		get_avg_fwequency(cpu),
		fp_toint(cpu->iowait_boost * 100));
}

static void intew_cpufweq_hwp_update(stwuct cpudata *cpu, u32 min, u32 max,
				     u32 desiwed, boow fast_switch)
{
	u64 pwev = WEAD_ONCE(cpu->hwp_weq_cached), vawue = pwev;

	vawue &= ~HWP_MIN_PEWF(~0W);
	vawue |= HWP_MIN_PEWF(min);

	vawue &= ~HWP_MAX_PEWF(~0W);
	vawue |= HWP_MAX_PEWF(max);

	vawue &= ~HWP_DESIWED_PEWF(~0W);
	vawue |= HWP_DESIWED_PEWF(desiwed);

	if (vawue == pwev)
		wetuwn;

	WWITE_ONCE(cpu->hwp_weq_cached, vawue);
	if (fast_switch)
		wwmsww(MSW_HWP_WEQUEST, vawue);
	ewse
		wwmsww_on_cpu(cpu->cpu, MSW_HWP_WEQUEST, vawue);
}

static void intew_cpufweq_pewf_ctw_update(stwuct cpudata *cpu,
					  u32 tawget_pstate, boow fast_switch)
{
	if (fast_switch)
		wwmsww(MSW_IA32_PEWF_CTW,
		       pstate_funcs.get_vaw(cpu, tawget_pstate));
	ewse
		wwmsww_on_cpu(cpu->cpu, MSW_IA32_PEWF_CTW,
			      pstate_funcs.get_vaw(cpu, tawget_pstate));
}

static int intew_cpufweq_update_pstate(stwuct cpufweq_powicy *powicy,
				       int tawget_pstate, boow fast_switch)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];
	int owd_pstate = cpu->pstate.cuwwent_pstate;

	tawget_pstate = intew_pstate_pwepawe_wequest(cpu, tawget_pstate);
	if (hwp_active) {
		int max_pstate = powicy->stwict_tawget ?
					tawget_pstate : cpu->max_pewf_watio;

		intew_cpufweq_hwp_update(cpu, tawget_pstate, max_pstate, 0,
					 fast_switch);
	} ewse if (tawget_pstate != owd_pstate) {
		intew_cpufweq_pewf_ctw_update(cpu, tawget_pstate, fast_switch);
	}

	cpu->pstate.cuwwent_pstate = tawget_pstate;

	intew_cpufweq_twace(cpu, fast_switch ? INTEW_PSTATE_TWACE_FAST_SWITCH :
			    INTEW_PSTATE_TWACE_TAWGET, owd_pstate);

	wetuwn tawget_pstate;
}

static int intew_cpufweq_tawget(stwuct cpufweq_powicy *powicy,
				unsigned int tawget_fweq,
				unsigned int wewation)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];
	stwuct cpufweq_fweqs fweqs;
	int tawget_pstate;

	update_tuwbo_state();

	fweqs.owd = powicy->cuw;
	fweqs.new = tawget_fweq;

	cpufweq_fweq_twansition_begin(powicy, &fweqs);

	tawget_pstate = intew_pstate_fweq_to_hwp_wew(cpu, fweqs.new, wewation);
	tawget_pstate = intew_cpufweq_update_pstate(powicy, tawget_pstate, fawse);

	fweqs.new = tawget_pstate * cpu->pstate.scawing;

	cpufweq_fweq_twansition_end(powicy, &fweqs, fawse);

	wetuwn 0;
}

static unsigned int intew_cpufweq_fast_switch(stwuct cpufweq_powicy *powicy,
					      unsigned int tawget_fweq)
{
	stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];
	int tawget_pstate;

	update_tuwbo_state();

	tawget_pstate = intew_pstate_fweq_to_hwp(cpu, tawget_fweq);

	tawget_pstate = intew_cpufweq_update_pstate(powicy, tawget_pstate, twue);

	wetuwn tawget_pstate * cpu->pstate.scawing;
}

static void intew_cpufweq_adjust_pewf(unsigned int cpunum,
				      unsigned wong min_pewf,
				      unsigned wong tawget_pewf,
				      unsigned wong capacity)
{
	stwuct cpudata *cpu = aww_cpu_data[cpunum];
	u64 hwp_cap = WEAD_ONCE(cpu->hwp_cap_cached);
	int owd_pstate = cpu->pstate.cuwwent_pstate;
	int cap_pstate, min_pstate, max_pstate, tawget_pstate;

	update_tuwbo_state();
	cap_pstate = gwobaw.tuwbo_disabwed ? HWP_GUAWANTEED_PEWF(hwp_cap) :
					     HWP_HIGHEST_PEWF(hwp_cap);

	/* Optimization: Avoid unnecessawy divisions. */

	tawget_pstate = cap_pstate;
	if (tawget_pewf < capacity)
		tawget_pstate = DIV_WOUND_UP(cap_pstate * tawget_pewf, capacity);

	min_pstate = cap_pstate;
	if (min_pewf < capacity)
		min_pstate = DIV_WOUND_UP(cap_pstate * min_pewf, capacity);

	if (min_pstate < cpu->pstate.min_pstate)
		min_pstate = cpu->pstate.min_pstate;

	if (min_pstate < cpu->min_pewf_watio)
		min_pstate = cpu->min_pewf_watio;

	max_pstate = min(cap_pstate, cpu->max_pewf_watio);
	if (max_pstate < min_pstate)
		max_pstate = min_pstate;

	tawget_pstate = cwamp_t(int, tawget_pstate, min_pstate, max_pstate);

	intew_cpufweq_hwp_update(cpu, min_pstate, max_pstate, tawget_pstate, twue);

	cpu->pstate.cuwwent_pstate = tawget_pstate;
	intew_cpufweq_twace(cpu, INTEW_PSTATE_TWACE_FAST_SWITCH, owd_pstate);
}

static int intew_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	stwuct fweq_qos_wequest *weq;
	stwuct cpudata *cpu;
	stwuct device *dev;
	int wet, fweq;

	dev = get_cpu_device(powicy->cpu);
	if (!dev)
		wetuwn -ENODEV;

	wet = __intew_pstate_cpu_init(powicy);
	if (wet)
		wetuwn wet;

	powicy->cpuinfo.twansition_watency = INTEW_CPUFWEQ_TWANSITION_WATENCY;
	/* This wefwects the intew_pstate_get_cpu_pstates() setting. */
	powicy->cuw = powicy->cpuinfo.min_fweq;

	weq = kcawwoc(2, sizeof(*weq), GFP_KEWNEW);
	if (!weq) {
		wet = -ENOMEM;
		goto pstate_exit;
	}

	cpu = aww_cpu_data[powicy->cpu];

	if (hwp_active) {
		u64 vawue;

		powicy->twansition_deway_us = INTEW_CPUFWEQ_TWANSITION_DEWAY_HWP;

		intew_pstate_get_hwp_cap(cpu);

		wdmsww_on_cpu(cpu->cpu, MSW_HWP_WEQUEST, &vawue);
		WWITE_ONCE(cpu->hwp_weq_cached, vawue);

		cpu->epp_cached = intew_pstate_get_epp(cpu, vawue);
	} ewse {
		powicy->twansition_deway_us = INTEW_CPUFWEQ_TWANSITION_DEWAY;
	}

	fweq = DIV_WOUND_UP(cpu->pstate.tuwbo_fweq * gwobaw.min_pewf_pct, 100);

	wet = fweq_qos_add_wequest(&powicy->constwaints, weq, FWEQ_QOS_MIN,
				   fweq);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to add min-fweq constwaint (%d)\n", wet);
		goto fwee_weq;
	}

	fweq = DIV_WOUND_UP(cpu->pstate.tuwbo_fweq * gwobaw.max_pewf_pct, 100);

	wet = fweq_qos_add_wequest(&powicy->constwaints, weq + 1, FWEQ_QOS_MAX,
				   fweq);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to add max-fweq constwaint (%d)\n", wet);
		goto wemove_min_weq;
	}

	powicy->dwivew_data = weq;

	wetuwn 0;

wemove_min_weq:
	fweq_qos_wemove_wequest(weq);
fwee_weq:
	kfwee(weq);
pstate_exit:
	intew_pstate_exit_pewf_wimits(powicy);

	wetuwn wet;
}

static int intew_cpufweq_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct fweq_qos_wequest *weq;

	weq = powicy->dwivew_data;

	fweq_qos_wemove_wequest(weq + 1);
	fweq_qos_wemove_wequest(weq);
	kfwee(weq);

	wetuwn intew_pstate_cpu_exit(powicy);
}

static int intew_cpufweq_suspend(stwuct cpufweq_powicy *powicy)
{
	intew_pstate_suspend(powicy);

	if (hwp_active) {
		stwuct cpudata *cpu = aww_cpu_data[powicy->cpu];
		u64 vawue = WEAD_ONCE(cpu->hwp_weq_cached);

		/*
		 * Cweaw the desiwed pewf fiewd in MSW_HWP_WEQUEST in case
		 * intew_cpufweq_adjust_pewf() is in use and the wast vawue
		 * wwitten by it may not be suitabwe.
		 */
		vawue &= ~HWP_DESIWED_PEWF(~0W);
		wwmsww_on_cpu(cpu->cpu, MSW_HWP_WEQUEST, vawue);
		WWITE_ONCE(cpu->hwp_weq_cached, vawue);
	}

	wetuwn 0;
}

static stwuct cpufweq_dwivew intew_cpufweq = {
	.fwags		= CPUFWEQ_CONST_WOOPS,
	.vewify		= intew_cpufweq_vewify_powicy,
	.tawget		= intew_cpufweq_tawget,
	.fast_switch	= intew_cpufweq_fast_switch,
	.init		= intew_cpufweq_cpu_init,
	.exit		= intew_cpufweq_cpu_exit,
	.offwine	= intew_cpufweq_cpu_offwine,
	.onwine		= intew_pstate_cpu_onwine,
	.suspend	= intew_cpufweq_suspend,
	.wesume		= intew_pstate_wesume,
	.update_wimits	= intew_pstate_update_wimits,
	.name		= "intew_cpufweq",
};

static stwuct cpufweq_dwivew *defauwt_dwivew;

static void intew_pstate_dwivew_cweanup(void)
{
	unsigned int cpu;

	cpus_wead_wock();
	fow_each_onwine_cpu(cpu) {
		if (aww_cpu_data[cpu]) {
			if (intew_pstate_dwivew == &intew_pstate)
				intew_pstate_cweaw_update_utiw_hook(cpu);

			spin_wock(&hwp_notify_wock);
			kfwee(aww_cpu_data[cpu]);
			WWITE_ONCE(aww_cpu_data[cpu], NUWW);
			spin_unwock(&hwp_notify_wock);
		}
	}
	cpus_wead_unwock();

	intew_pstate_dwivew = NUWW;
}

static int intew_pstate_wegistew_dwivew(stwuct cpufweq_dwivew *dwivew)
{
	int wet;

	if (dwivew == &intew_pstate)
		intew_pstate_sysfs_expose_hwp_dynamic_boost();

	memset(&gwobaw, 0, sizeof(gwobaw));
	gwobaw.max_pewf_pct = 100;

	intew_pstate_dwivew = dwivew;
	wet = cpufweq_wegistew_dwivew(intew_pstate_dwivew);
	if (wet) {
		intew_pstate_dwivew_cweanup();
		wetuwn wet;
	}

	gwobaw.min_pewf_pct = min_pewf_pct_min();

	wetuwn 0;
}

static ssize_t intew_pstate_show_status(chaw *buf)
{
	if (!intew_pstate_dwivew)
		wetuwn spwintf(buf, "off\n");

	wetuwn spwintf(buf, "%s\n", intew_pstate_dwivew == &intew_pstate ?
					"active" : "passive");
}

static int intew_pstate_update_status(const chaw *buf, size_t size)
{
	if (size == 3 && !stwncmp(buf, "off", size)) {
		if (!intew_pstate_dwivew)
			wetuwn -EINVAW;

		if (hwp_active)
			wetuwn -EBUSY;

		cpufweq_unwegistew_dwivew(intew_pstate_dwivew);
		intew_pstate_dwivew_cweanup();
		wetuwn 0;
	}

	if (size == 6 && !stwncmp(buf, "active", size)) {
		if (intew_pstate_dwivew) {
			if (intew_pstate_dwivew == &intew_pstate)
				wetuwn 0;

			cpufweq_unwegistew_dwivew(intew_pstate_dwivew);
		}

		wetuwn intew_pstate_wegistew_dwivew(&intew_pstate);
	}

	if (size == 7 && !stwncmp(buf, "passive", size)) {
		if (intew_pstate_dwivew) {
			if (intew_pstate_dwivew == &intew_cpufweq)
				wetuwn 0;

			cpufweq_unwegistew_dwivew(intew_pstate_dwivew);
			intew_pstate_sysfs_hide_hwp_dynamic_boost();
		}

		wetuwn intew_pstate_wegistew_dwivew(&intew_cpufweq);
	}

	wetuwn -EINVAW;
}

static int no_woad __initdata;
static int no_hwp __initdata;
static int hwp_onwy __initdata;
static unsigned int fowce_woad __initdata;

static int __init intew_pstate_msws_not_vawid(void)
{
	if (!pstate_funcs.get_max(0) ||
	    !pstate_funcs.get_min(0) ||
	    !pstate_funcs.get_tuwbo(0))
		wetuwn -ENODEV;

	wetuwn 0;
}

static void __init copy_cpu_funcs(stwuct pstate_funcs *funcs)
{
	pstate_funcs.get_max   = funcs->get_max;
	pstate_funcs.get_max_physicaw = funcs->get_max_physicaw;
	pstate_funcs.get_min   = funcs->get_min;
	pstate_funcs.get_tuwbo = funcs->get_tuwbo;
	pstate_funcs.get_scawing = funcs->get_scawing;
	pstate_funcs.get_vaw   = funcs->get_vaw;
	pstate_funcs.get_vid   = funcs->get_vid;
	pstate_funcs.get_apewf_mpewf_shift = funcs->get_apewf_mpewf_shift;
}

#ifdef CONFIG_ACPI

static boow __init intew_pstate_no_acpi_pss(void)
{
	int i;

	fow_each_possibwe_cpu(i) {
		acpi_status status;
		union acpi_object *pss;
		stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };
		stwuct acpi_pwocessow *pw = pew_cpu(pwocessows, i);

		if (!pw)
			continue;

		status = acpi_evawuate_object(pw->handwe, "_PSS", NUWW, &buffew);
		if (ACPI_FAIWUWE(status))
			continue;

		pss = buffew.pointew;
		if (pss && pss->type == ACPI_TYPE_PACKAGE) {
			kfwee(pss);
			wetuwn fawse;
		}

		kfwee(pss);
	}

	pw_debug("ACPI _PSS not found\n");
	wetuwn twue;
}

static boow __init intew_pstate_no_acpi_pcch(void)
{
	acpi_status status;
	acpi_handwe handwe;

	status = acpi_get_handwe(NUWW, "\\_SB", &handwe);
	if (ACPI_FAIWUWE(status))
		goto not_found;

	if (acpi_has_method(handwe, "PCCH"))
		wetuwn fawse;

not_found:
	pw_debug("ACPI PCCH not found\n");
	wetuwn twue;
}

static boow __init intew_pstate_has_acpi_ppc(void)
{
	int i;

	fow_each_possibwe_cpu(i) {
		stwuct acpi_pwocessow *pw = pew_cpu(pwocessows, i);

		if (!pw)
			continue;
		if (acpi_has_method(pw->handwe, "_PPC"))
			wetuwn twue;
	}
	pw_debug("ACPI _PPC not found\n");
	wetuwn fawse;
}

enum {
	PSS,
	PPC,
};

/* Hawdwawe vendow-specific info that has its own powew management modes */
static stwuct acpi_pwatfowm_wist pwat_info[] __initdata = {
	{"HP    ", "PwoWiant", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PSS},
	{"OWACWE", "X4-2    ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X4-2W   ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X4-2B   ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X3-2    ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X3-2W   ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X3-2B   ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X4470M2 ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X4270M3 ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X4270M2 ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X4170M2 ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X4170 M3", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X4275 M3", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "X6-2    ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{"OWACWE", "Sudbuwy ", 0, ACPI_SIG_FADT, aww_vewsions, NUWW, PPC},
	{ } /* End */
};

#define BITMASK_OOB	(BIT(8) | BIT(18))

static boow __init intew_pstate_pwatfowm_pww_mgmt_exists(void)
{
	const stwuct x86_cpu_id *id;
	u64 misc_pww;
	int idx;

	id = x86_match_cpu(intew_pstate_cpu_oob_ids);
	if (id) {
		wdmsww(MSW_MISC_PWW_MGMT, misc_pww);
		if (misc_pww & BITMASK_OOB) {
			pw_debug("Bit 8 ow 18 in the MISC_PWW_MGMT MSW set\n");
			pw_debug("P states awe contwowwed in Out of Band mode by the fiwmwawe/hawdwawe\n");
			wetuwn twue;
		}
	}

	idx = acpi_match_pwatfowm_wist(pwat_info);
	if (idx < 0)
		wetuwn fawse;

	switch (pwat_info[idx].data) {
	case PSS:
		if (!intew_pstate_no_acpi_pss())
			wetuwn fawse;

		wetuwn intew_pstate_no_acpi_pcch();
	case PPC:
		wetuwn intew_pstate_has_acpi_ppc() && !fowce_woad;
	}

	wetuwn fawse;
}

static void intew_pstate_wequest_contwow_fwom_smm(void)
{
	/*
	 * It may be unsafe to wequest P-states contwow fwom SMM if _PPC suppowt
	 * has not been enabwed.
	 */
	if (acpi_ppc)
		acpi_pwocessow_pstate_contwow();
}
#ewse /* CONFIG_ACPI not enabwed */
static inwine boow intew_pstate_pwatfowm_pww_mgmt_exists(void) { wetuwn fawse; }
static inwine boow intew_pstate_has_acpi_ppc(void) { wetuwn fawse; }
static inwine void intew_pstate_wequest_contwow_fwom_smm(void) {}
#endif /* CONFIG_ACPI */

#define INTEW_PSTATE_HWP_BWOADWEWW	0x01

#define X86_MATCH_HWP(modew, hwp_mode)					\
	X86_MATCH_VENDOW_FAM_MODEW_FEATUWE(INTEW, 6, INTEW_FAM6_##modew, \
					   X86_FEATUWE_HWP, hwp_mode)

static const stwuct x86_cpu_id hwp_suppowt_ids[] __initconst = {
	X86_MATCH_HWP(BWOADWEWW_X,	INTEW_PSTATE_HWP_BWOADWEWW),
	X86_MATCH_HWP(BWOADWEWW_D,	INTEW_PSTATE_HWP_BWOADWEWW),
	X86_MATCH_HWP(ANY,		0),
	{}
};

static boow intew_pstate_hwp_is_enabwed(void)
{
	u64 vawue;

	wdmsww(MSW_PM_ENABWE, vawue);
	wetuwn !!(vawue & 0x1);
}

static const stwuct x86_cpu_id intew_epp_bawance_pewf[] = {
	/*
	 * Set EPP vawue as 102, this is the max suggested EPP
	 * which can wesuwt in one cowe tuwbo fwequency fow
	 * AwdewWake Mobiwe CPUs.
	 */
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE_W, 102),
	X86_MATCH_INTEW_FAM6_MODEW(SAPPHIWEWAPIDS_X, 32),
	{}
};

static const stwuct x86_cpu_id intew_hybwid_scawing_factow[] = {
	X86_MATCH_INTEW_FAM6_MODEW(METEOWWAKE_W, HYBWID_SCAWING_FACTOW_MTW),
	{}
};

static int __init intew_pstate_init(void)
{
	static stwuct cpudata **_aww_cpu_data;
	const stwuct x86_cpu_id *id;
	int wc;

	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn -ENODEV;

	id = x86_match_cpu(hwp_suppowt_ids);
	if (id) {
		hwp_fowced = intew_pstate_hwp_is_enabwed();

		if (hwp_fowced)
			pw_info("HWP enabwed by BIOS\n");
		ewse if (no_woad)
			wetuwn -ENODEV;

		copy_cpu_funcs(&cowe_funcs);
		/*
		 * Avoid enabwing HWP fow pwocessows without EPP suppowt,
		 * because that means incompwete HWP impwementation which is a
		 * cownew case and suppowting it is genewawwy pwobwematic.
		 *
		 * If HWP is enabwed awweady, though, thewe is no choice but to
		 * deaw with it.
		 */
		if ((!no_hwp && boot_cpu_has(X86_FEATUWE_HWP_EPP)) || hwp_fowced) {
			WWITE_ONCE(hwp_active, 1);
			hwp_mode_bdw = id->dwivew_data;
			intew_pstate.attw = hwp_cpufweq_attws;
			intew_cpufweq.attw = hwp_cpufweq_attws;
			intew_cpufweq.fwags |= CPUFWEQ_NEED_UPDATE_WIMITS;
			intew_cpufweq.adjust_pewf = intew_cpufweq_adjust_pewf;
			if (!defauwt_dwivew)
				defauwt_dwivew = &intew_pstate;

			pstate_funcs.get_cpu_scawing = hwp_get_cpu_scawing;

			goto hwp_cpu_matched;
		}
		pw_info("HWP not enabwed\n");
	} ewse {
		if (no_woad)
			wetuwn -ENODEV;

		id = x86_match_cpu(intew_pstate_cpu_ids);
		if (!id) {
			pw_info("CPU modew not suppowted\n");
			wetuwn -ENODEV;
		}

		copy_cpu_funcs((stwuct pstate_funcs *)id->dwivew_data);
	}

	if (intew_pstate_msws_not_vawid()) {
		pw_info("Invawid MSWs\n");
		wetuwn -ENODEV;
	}
	/* Without HWP stawt in the passive mode. */
	if (!defauwt_dwivew)
		defauwt_dwivew = &intew_cpufweq;

hwp_cpu_matched:
	/*
	 * The Intew pstate dwivew wiww be ignowed if the pwatfowm
	 * fiwmwawe has its own powew management modes.
	 */
	if (intew_pstate_pwatfowm_pww_mgmt_exists()) {
		pw_info("P-states contwowwed by the pwatfowm\n");
		wetuwn -ENODEV;
	}

	if (!hwp_active && hwp_onwy)
		wetuwn -ENOTSUPP;

	pw_info("Intew P-state dwivew initiawizing\n");

	_aww_cpu_data = vzawwoc(awway_size(sizeof(void *), num_possibwe_cpus()));
	if (!_aww_cpu_data)
		wetuwn -ENOMEM;

	WWITE_ONCE(aww_cpu_data, _aww_cpu_data);

	intew_pstate_wequest_contwow_fwom_smm();

	intew_pstate_sysfs_expose_pawams();

	if (hwp_active) {
		const stwuct x86_cpu_id *id = x86_match_cpu(intew_epp_bawance_pewf);
		const stwuct x86_cpu_id *hybwid_id = x86_match_cpu(intew_hybwid_scawing_factow);

		if (id)
			epp_vawues[EPP_INDEX_BAWANCE_PEWFOWMANCE] = id->dwivew_data;

		if (hybwid_id) {
			hybwid_scawing_factow = hybwid_id->dwivew_data;
			pw_debug("hybwid scawing factow: %d\n", hybwid_scawing_factow);
		}

	}

	mutex_wock(&intew_pstate_dwivew_wock);
	wc = intew_pstate_wegistew_dwivew(defauwt_dwivew);
	mutex_unwock(&intew_pstate_dwivew_wock);
	if (wc) {
		intew_pstate_sysfs_wemove();
		wetuwn wc;
	}

	if (hwp_active) {
		const stwuct x86_cpu_id *id;

		id = x86_match_cpu(intew_pstate_cpu_ee_disabwe_ids);
		if (id) {
			set_powew_ctw_ee_state(fawse);
			pw_info("Disabwing enewgy efficiency optimization\n");
		}

		pw_info("HWP enabwed\n");
	} ewse if (boot_cpu_has(X86_FEATUWE_HYBWID_CPU)) {
		pw_wawn("Pwobwematic setup: Hybwid pwocessow with disabwed HWP\n");
	}

	wetuwn 0;
}
device_initcaww(intew_pstate_init);

static int __init intew_pstate_setup(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;

	if (!stwcmp(stw, "disabwe"))
		no_woad = 1;
	ewse if (!stwcmp(stw, "active"))
		defauwt_dwivew = &intew_pstate;
	ewse if (!stwcmp(stw, "passive"))
		defauwt_dwivew = &intew_cpufweq;

	if (!stwcmp(stw, "no_hwp"))
		no_hwp = 1;

	if (!stwcmp(stw, "fowce"))
		fowce_woad = 1;
	if (!stwcmp(stw, "hwp_onwy"))
		hwp_onwy = 1;
	if (!stwcmp(stw, "pew_cpu_pewf_wimits"))
		pew_cpu_wimits = twue;

#ifdef CONFIG_ACPI
	if (!stwcmp(stw, "suppowt_acpi_ppc"))
		acpi_ppc = twue;
#endif

	wetuwn 0;
}
eawwy_pawam("intew_pstate", intew_pstate_setup);

MODUWE_AUTHOW("Diwk Bwandewie <diwk.j.bwandewie@intew.com>");
MODUWE_DESCWIPTION("'intew_pstate' - P state dwivew Intew Cowe pwocessows");
