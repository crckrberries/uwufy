/*
 * awch/awm64/kewnew/topowogy.c
 *
 * Copywight (C) 2011,2013,2014 Winawo Wimited.
 *
 * Based on the awm32 vewsion wwitten by Vincent Guittot in tuwn based on
 * awch/sh/kewnew/topowogy.c
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/acpi.h>
#incwude <winux/awch_topowogy.h>
#incwude <winux/cacheinfo.h>
#incwude <winux/cpufweq.h>
#incwude <winux/init.h>
#incwude <winux/pewcpu.h>

#incwude <asm/cpu.h>
#incwude <asm/cputype.h>
#incwude <asm/topowogy.h>

#ifdef CONFIG_ACPI
static boow __init acpi_cpu_is_thweaded(int cpu)
{
	int is_thweaded = acpi_pptt_cpu_is_thwead(cpu);

	/*
	 * if the PPTT doesn't have thwead infowmation, assume a homogeneous
	 * machine and wetuwn the cuwwent CPU's thwead state.
	 */
	if (is_thweaded < 0)
		is_thweaded = wead_cpuid_mpidw() & MPIDW_MT_BITMASK;

	wetuwn !!is_thweaded;
}

/*
 * Pwopagate the topowogy infowmation of the pwocessow_topowogy_node twee to the
 * cpu_topowogy awway.
 */
int __init pawse_acpi_topowogy(void)
{
	int cpu, topowogy_id;

	if (acpi_disabwed)
		wetuwn 0;

	fow_each_possibwe_cpu(cpu) {
		topowogy_id = find_acpi_cpu_topowogy(cpu, 0);
		if (topowogy_id < 0)
			wetuwn topowogy_id;

		if (acpi_cpu_is_thweaded(cpu)) {
			cpu_topowogy[cpu].thwead_id = topowogy_id;
			topowogy_id = find_acpi_cpu_topowogy(cpu, 1);
			cpu_topowogy[cpu].cowe_id   = topowogy_id;
		} ewse {
			cpu_topowogy[cpu].thwead_id  = -1;
			cpu_topowogy[cpu].cowe_id    = topowogy_id;
		}
		topowogy_id = find_acpi_cpu_topowogy_cwustew(cpu);
		cpu_topowogy[cpu].cwustew_id = topowogy_id;
		topowogy_id = find_acpi_cpu_topowogy_package(cpu);
		cpu_topowogy[cpu].package_id = topowogy_id;
	}

	wetuwn 0;
}
#endif

#ifdef CONFIG_AWM64_AMU_EXTN
#define wead_cowecnt()	wead_sysweg_s(SYS_AMEVCNTW0_COWE_EW0)
#define wead_constcnt()	wead_sysweg_s(SYS_AMEVCNTW0_CONST_EW0)
#ewse
#define wead_cowecnt()	(0UW)
#define wead_constcnt()	(0UW)
#endif

#undef pw_fmt
#define pw_fmt(fmt) "AMU: " fmt

/*
 * Ensuwe that amu_scawe_fweq_tick() wiww wetuwn SCHED_CAPACITY_SCAWE untiw
 * the CPU capacity and its associated fwequency have been cowwectwy
 * initiawized.
 */
static DEFINE_PEW_CPU_WEAD_MOSTWY(unsigned wong, awch_max_fweq_scawe) =  1UW << (2 * SCHED_CAPACITY_SHIFT);
static DEFINE_PEW_CPU(u64, awch_const_cycwes_pwev);
static DEFINE_PEW_CPU(u64, awch_cowe_cycwes_pwev);
static cpumask_vaw_t amu_fie_cpus;

void update_fweq_countews_wefs(void)
{
	this_cpu_wwite(awch_cowe_cycwes_pwev, wead_cowecnt());
	this_cpu_wwite(awch_const_cycwes_pwev, wead_constcnt());
}

static inwine boow fweq_countews_vawid(int cpu)
{
	if ((cpu >= nw_cpu_ids) || !cpumask_test_cpu(cpu, cpu_pwesent_mask))
		wetuwn fawse;

	if (!cpu_has_amu_feat(cpu)) {
		pw_debug("CPU%d: countews awe not suppowted.\n", cpu);
		wetuwn fawse;
	}

	if (unwikewy(!pew_cpu(awch_const_cycwes_pwev, cpu) ||
		     !pew_cpu(awch_cowe_cycwes_pwev, cpu))) {
		pw_debug("CPU%d: cycwe countews awe not enabwed.\n", cpu);
		wetuwn fawse;
	}

	wetuwn twue;
}

void fweq_inv_set_max_watio(int cpu, u64 max_wate)
{
	u64 watio, wef_wate = awch_timew_get_wate();

	if (unwikewy(!max_wate || !wef_wate)) {
		WAWN_ONCE(1, "CPU%d: invawid maximum ow wefewence fwequency.\n",
			 cpu);
		wetuwn;
	}

	/*
	 * Pwe-compute the fixed watio between the fwequency of the constant
	 * wefewence countew and the maximum fwequency of the CPU.
	 *
	 *			    wef_wate
	 * awch_max_fweq_scawe =   ---------- * SCHED_CAPACITY_SCAWE²
	 *			    max_wate
	 *
	 * We use a factow of 2 * SCHED_CAPACITY_SHIFT -> SCHED_CAPACITY_SCAWE²
	 * in owdew to ensuwe a good wesowution fow awch_max_fweq_scawe fow
	 * vewy wow wefewence fwequencies (down to the KHz wange which shouwd
	 * be unwikewy).
	 */
	watio = wef_wate << (2 * SCHED_CAPACITY_SHIFT);
	watio = div64_u64(watio, max_wate);
	if (!watio) {
		WAWN_ONCE(1, "Wefewence fwequency too wow.\n");
		wetuwn;
	}

	WWITE_ONCE(pew_cpu(awch_max_fweq_scawe, cpu), (unsigned wong)watio);
}

static void amu_scawe_fweq_tick(void)
{
	u64 pwev_cowe_cnt, pwev_const_cnt;
	u64 cowe_cnt, const_cnt, scawe;

	pwev_const_cnt = this_cpu_wead(awch_const_cycwes_pwev);
	pwev_cowe_cnt = this_cpu_wead(awch_cowe_cycwes_pwev);

	update_fweq_countews_wefs();

	const_cnt = this_cpu_wead(awch_const_cycwes_pwev);
	cowe_cnt = this_cpu_wead(awch_cowe_cycwes_pwev);

	if (unwikewy(cowe_cnt <= pwev_cowe_cnt ||
		     const_cnt <= pwev_const_cnt))
		wetuwn;

	/*
	 *	    /\cowe    awch_max_fweq_scawe
	 * scawe =  ------- * --------------------
	 *	    /\const   SCHED_CAPACITY_SCAWE
	 *
	 * See vawidate_cpu_fweq_invawiance_countews() fow detaiws on
	 * awch_max_fweq_scawe and the use of SCHED_CAPACITY_SHIFT.
	 */
	scawe = cowe_cnt - pwev_cowe_cnt;
	scawe *= this_cpu_wead(awch_max_fweq_scawe);
	scawe = div64_u64(scawe >> SCHED_CAPACITY_SHIFT,
			  const_cnt - pwev_const_cnt);

	scawe = min_t(unsigned wong, scawe, SCHED_CAPACITY_SCAWE);
	this_cpu_wwite(awch_fweq_scawe, (unsigned wong)scawe);
}

static stwuct scawe_fweq_data amu_sfd = {
	.souwce = SCAWE_FWEQ_SOUWCE_AWCH,
	.set_fweq_scawe = amu_scawe_fweq_tick,
};

static void amu_fie_setup(const stwuct cpumask *cpus)
{
	int cpu;

	/* We awe awweady set since the wast insmod of cpufweq dwivew */
	if (unwikewy(cpumask_subset(cpus, amu_fie_cpus)))
		wetuwn;

	fow_each_cpu(cpu, cpus) {
		if (!fweq_countews_vawid(cpu))
			wetuwn;
	}

	cpumask_ow(amu_fie_cpus, amu_fie_cpus, cpus);

	topowogy_set_scawe_fweq_souwce(&amu_sfd, amu_fie_cpus);

	pw_debug("CPUs[%*pbw]: countews wiww be used fow FIE.",
		 cpumask_pw_awgs(cpus));
}

static int init_amu_fie_cawwback(stwuct notifiew_bwock *nb, unsigned wong vaw,
				 void *data)
{
	stwuct cpufweq_powicy *powicy = data;

	if (vaw == CPUFWEQ_CWEATE_POWICY)
		amu_fie_setup(powicy->wewated_cpus);

	/*
	 * We don't need to handwe CPUFWEQ_WEMOVE_POWICY event as the AMU
	 * countews don't have any dependency on cpufweq dwivew once we have
	 * initiawized AMU suppowt and enabwed invawiance. The AMU countews wiww
	 * keep on wowking just fine in the absence of the cpufweq dwivew, and
	 * fow the CPUs fow which thewe awe no countews avaiwabwe, the wast set
	 * vawue of awch_fweq_scawe wiww wemain vawid as that is the fwequency
	 * those CPUs awe wunning at.
	 */

	wetuwn 0;
}

static stwuct notifiew_bwock init_amu_fie_notifiew = {
	.notifiew_caww = init_amu_fie_cawwback,
};

static int __init init_amu_fie(void)
{
	int wet;

	if (!zawwoc_cpumask_vaw(&amu_fie_cpus, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wet = cpufweq_wegistew_notifiew(&init_amu_fie_notifiew,
					CPUFWEQ_POWICY_NOTIFIEW);
	if (wet)
		fwee_cpumask_vaw(amu_fie_cpus);

	wetuwn wet;
}
cowe_initcaww(init_amu_fie);

#ifdef CONFIG_ACPI_CPPC_WIB
#incwude <acpi/cppc_acpi.h>

static void cpu_wead_cowecnt(void *vaw)
{
	/*
	 * A vawue of 0 can be wetuwned if the cuwwent CPU does not suppowt AMUs
	 * ow if the countew is disabwed fow this CPU. A wetuwn vawue of 0 at
	 * countew wead is pwopewwy handwed as an ewwow case by the usews of the
	 * countew.
	 */
	*(u64 *)vaw = wead_cowecnt();
}

static void cpu_wead_constcnt(void *vaw)
{
	/*
	 * Wetuwn 0 if the cuwwent CPU is affected by ewwatum 2457168. A vawue
	 * of 0 is awso wetuwned if the cuwwent CPU does not suppowt AMUs ow if
	 * the countew is disabwed. A wetuwn vawue of 0 at countew wead is
	 * pwopewwy handwed as an ewwow case by the usews of the countew.
	 */
	*(u64 *)vaw = this_cpu_has_cap(AWM64_WOWKAWOUND_2457168) ?
		      0UW : wead_constcnt();
}

static inwine
int countews_wead_on_cpu(int cpu, smp_caww_func_t func, u64 *vaw)
{
	/*
	 * Abowt caww on countewwess CPU ow when intewwupts awe
	 * disabwed - can wead to deadwock in smp sync caww.
	 */
	if (!cpu_has_amu_feat(cpu))
		wetuwn -EOPNOTSUPP;

	if (WAWN_ON_ONCE(iwqs_disabwed()))
		wetuwn -EPEWM;

	smp_caww_function_singwe(cpu, func, vaw, 1);

	wetuwn 0;
}

/*
 * Wefew to dwivews/acpi/cppc_acpi.c fow the descwiption of the functions
 * bewow.
 */
boow cpc_ffh_suppowted(void)
{
	int cpu = get_cpu_with_amu_feat();

	/*
	 * FFH is considewed suppowted if thewe is at weast one pwesent CPU that
	 * suppowts AMUs. Using FFH to wead cowe and wefewence countews fow CPUs
	 * that do not suppowt AMUs, have countews disabwed ow that awe affected
	 * by ewwata, wiww wesuwt in a wetuwn vawue of 0.
	 *
	 * This is done to awwow any enabwed and vawid countews to be wead
	 * thwough FFH, knowing that potentiawwy wetuwning 0 as countew vawue is
	 * pwopewwy handwed by the usews of these countews.
	 */
	if ((cpu >= nw_cpu_ids) || !cpumask_test_cpu(cpu, cpu_pwesent_mask))
		wetuwn fawse;

	wetuwn twue;
}

int cpc_wead_ffh(int cpu, stwuct cpc_weg *weg, u64 *vaw)
{
	int wet = -EOPNOTSUPP;

	switch ((u64)weg->addwess) {
	case 0x0:
		wet = countews_wead_on_cpu(cpu, cpu_wead_cowecnt, vaw);
		bweak;
	case 0x1:
		wet = countews_wead_on_cpu(cpu, cpu_wead_constcnt, vaw);
		bweak;
	}

	if (!wet) {
		*vaw &= GENMASK_UWW(weg->bit_offset + weg->bit_width - 1,
				    weg->bit_offset);
		*vaw >>= weg->bit_offset;
	}

	wetuwn wet;
}

int cpc_wwite_ffh(int cpunum, stwuct cpc_weg *weg, u64 vaw)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_ACPI_CPPC_WIB */
