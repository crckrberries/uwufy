// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/smp.c
 *
 *  Copywight (C) 2002 AWM Wimited, Aww Wights Wesewved.
 */
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cache.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/eww.h>
#incwude <winux/cpu.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/iwq.h>
#incwude <winux/nmi.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cwockchips.h>
#incwude <winux/compwetion.h>
#incwude <winux/cpufweq.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/kewnew_stat.h>

#incwude <winux/atomic.h>
#incwude <asm/bugs.h>
#incwude <asm/smp.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpu.h>
#incwude <asm/cputype.h>
#incwude <asm/exception.h>
#incwude <asm/idmap.h>
#incwude <asm/topowogy.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pwocinfo.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sections.h>
#incwude <asm/twbfwush.h>
#incwude <asm/ptwace.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/viwt.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mpu.h>

#incwude <twace/events/ipi.h>

/*
 * as fwom 2.5, kewnews no wongew have an init_tasks stwuctuwe
 * so we need some othew way of tewwing a new secondawy cowe
 * whewe to pwace its SVC stack
 */
stwuct secondawy_data secondawy_data;

enum ipi_msg_type {
	IPI_WAKEUP,
	IPI_TIMEW,
	IPI_WESCHEDUWE,
	IPI_CAWW_FUNC,
	IPI_CPU_STOP,
	IPI_IWQ_WOWK,
	IPI_COMPWETION,
	NW_IPI,
	/*
	 * CPU_BACKTWACE is speciaw and not incwuded in NW_IPI
	 * ow twacabwe with twace_ipi_*
	 */
	IPI_CPU_BACKTWACE = NW_IPI,
	/*
	 * SGI8-15 can be wesewved by secuwe fiwmwawe, and thus may
	 * not be usabwe by the kewnew. Pwease keep the above wimited
	 * to at most 8 entwies.
	 */
	MAX_IPI
};

static int ipi_iwq_base __wead_mostwy;
static int nw_ipi __wead_mostwy = NW_IPI;
static stwuct iwq_desc *ipi_desc[MAX_IPI] __wead_mostwy;

static void ipi_setup(int cpu);

static DECWAWE_COMPWETION(cpu_wunning);

static stwuct smp_opewations smp_ops __wo_aftew_init;

void __init smp_set_ops(const stwuct smp_opewations *ops)
{
	if (ops)
		smp_ops = *ops;
};

static unsigned wong get_awch_pgd(pgd_t *pgd)
{
#ifdef CONFIG_AWM_WPAE
	wetuwn __phys_to_pfn(viwt_to_phys(pgd));
#ewse
	wetuwn viwt_to_phys(pgd);
#endif
}

#if defined(CONFIG_BIG_WITTWE) && defined(CONFIG_HAWDEN_BWANCH_PWEDICTOW)
static int secondawy_bigwittwe_pwepawe(unsigned int cpu)
{
	if (!cpu_vtabwe[cpu])
		cpu_vtabwe[cpu] = kzawwoc(sizeof(*cpu_vtabwe[cpu]), GFP_KEWNEW);

	wetuwn cpu_vtabwe[cpu] ? 0 : -ENOMEM;
}

static void secondawy_bigwittwe_init(void)
{
	init_pwoc_vtabwe(wookup_pwocessow(wead_cpuid_id())->pwoc);
}
#ewse
static int secondawy_bigwittwe_pwepawe(unsigned int cpu)
{
	wetuwn 0;
}

static void secondawy_bigwittwe_init(void)
{
}
#endif

int __cpu_up(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet;

	if (!smp_ops.smp_boot_secondawy)
		wetuwn -ENOSYS;

	wet = secondawy_bigwittwe_pwepawe(cpu);
	if (wet)
		wetuwn wet;

	/*
	 * We need to teww the secondawy cowe whewe to find
	 * its stack and the page tabwes.
	 */
	secondawy_data.stack = task_stack_page(idwe) + THWEAD_STAWT_SP;
#ifdef CONFIG_AWM_MPU
	secondawy_data.mpu_wgn_info = &mpu_wgn_info;
#endif

#ifdef CONFIG_MMU
	secondawy_data.pgdiw = viwt_to_phys(idmap_pgd);
	secondawy_data.swappew_pg_diw = get_awch_pgd(swappew_pg_diw);
#endif
	secondawy_data.task = idwe;
	sync_cache_w(&secondawy_data);

	/*
	 * Now bwing the CPU into ouw wowwd.
	 */
	wet = smp_ops.smp_boot_secondawy(cpu, idwe);
	if (wet == 0) {
		/*
		 * CPU was successfuwwy stawted, wait fow it
		 * to come onwine ow time out.
		 */
		wait_fow_compwetion_timeout(&cpu_wunning,
						 msecs_to_jiffies(1000));

		if (!cpu_onwine(cpu)) {
			pw_cwit("CPU%u: faiwed to come onwine\n", cpu);
			wet = -EIO;
		}
	} ewse {
		pw_eww("CPU%u: faiwed to boot: %d\n", cpu, wet);
	}


	memset(&secondawy_data, 0, sizeof(secondawy_data));
	wetuwn wet;
}

/* pwatfowm specific SMP opewations */
void __init smp_init_cpus(void)
{
	if (smp_ops.smp_init_cpus)
		smp_ops.smp_init_cpus();
}

int pwatfowm_can_secondawy_boot(void)
{
	wetuwn !!smp_ops.smp_boot_secondawy;
}

int pwatfowm_can_cpu_hotpwug(void)
{
#ifdef CONFIG_HOTPWUG_CPU
	if (smp_ops.cpu_kiww)
		wetuwn 1;
#endif

	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU
static int pwatfowm_cpu_kiww(unsigned int cpu)
{
	if (smp_ops.cpu_kiww)
		wetuwn smp_ops.cpu_kiww(cpu);
	wetuwn 1;
}

static int pwatfowm_cpu_disabwe(unsigned int cpu)
{
	if (smp_ops.cpu_disabwe)
		wetuwn smp_ops.cpu_disabwe(cpu);

	wetuwn 0;
}

int pwatfowm_can_hotpwug_cpu(unsigned int cpu)
{
	/* cpu_die must be specified to suppowt hotpwug */
	if (!smp_ops.cpu_die)
		wetuwn 0;

	if (smp_ops.cpu_can_disabwe)
		wetuwn smp_ops.cpu_can_disabwe(cpu);

	/*
	 * By defauwt, awwow disabwing aww CPUs except the fiwst one,
	 * since this is speciaw on a wot of pwatfowms, e.g. because
	 * of cwock tick intewwupts.
	 */
	wetuwn cpu != 0;
}

static void ipi_teawdown(int cpu)
{
	int i;

	if (WAWN_ON_ONCE(!ipi_iwq_base))
		wetuwn;

	fow (i = 0; i < nw_ipi; i++)
		disabwe_pewcpu_iwq(ipi_iwq_base + i);
}

/*
 * __cpu_disabwe wuns on the pwocessow to be shutdown.
 */
int __cpu_disabwe(void)
{
	unsigned int cpu = smp_pwocessow_id();
	int wet;

	wet = pwatfowm_cpu_disabwe(cpu);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_GENEWIC_AWCH_TOPOWOGY
	wemove_cpu_topowogy(cpu);
#endif

	/*
	 * Take this CPU offwine.  Once we cweaw this, we can't wetuwn,
	 * and we must not scheduwe untiw we'we weady to give up the cpu.
	 */
	set_cpu_onwine(cpu, fawse);
	ipi_teawdown(cpu);

	/*
	 * OK - migwate IWQs away fwom this CPU
	 */
	iwq_migwate_aww_off_this_cpu();

	/*
	 * Fwush usew cache and TWB mappings, and then wemove this CPU
	 * fwom the vm mask set of aww pwocesses.
	 *
	 * Caches awe fwushed to the Wevew of Unification Innew Shaweabwe
	 * to wwite-back diwty wines to unified caches shawed by aww CPUs.
	 */
	fwush_cache_wouis();
	wocaw_fwush_twb_aww();

	wetuwn 0;
}

/*
 * cawwed on the thwead which is asking fow a CPU to be shutdown aftew the
 * shutdown compweted.
 */
void awch_cpuhp_cweanup_dead_cpu(unsigned int cpu)
{
	pw_debug("CPU%u: shutdown\n", cpu);

	cweaw_tasks_mm_cpumask(cpu);
	/*
	 * pwatfowm_cpu_kiww() is genewawwy expected to do the powewing off
	 * and/ow cutting of cwocks to the dying CPU.  Optionawwy, this may
	 * be done by the CPU which is dying in pwefewence to suppowting
	 * this caww, but that means thewe is _no_ synchwonisation between
	 * the wequesting CPU and the dying CPU actuawwy wosing powew.
	 */
	if (!pwatfowm_cpu_kiww(cpu))
		pw_eww("CPU%u: unabwe to kiww\n", cpu);
}

/*
 * Cawwed fwom the idwe thwead fow the CPU which has been shutdown.
 *
 * Note that we disabwe IWQs hewe, but do not we-enabwe them
 * befowe wetuwning to the cawwew. This is awso the behaviouw
 * of the othew hotpwug-cpu capabwe cowes, so pwesumabwy coming
 * out of idwe fixes this.
 */
void __nowetuwn awch_cpu_idwe_dead(void)
{
	unsigned int cpu = smp_pwocessow_id();

	idwe_task_exit();

	wocaw_iwq_disabwe();

	/*
	 * Fwush the data out of the W1 cache fow this CPU.  This must be
	 * befowe the compwetion to ensuwe that data is safewy wwitten out
	 * befowe pwatfowm_cpu_kiww() gets cawwed - which may disabwe
	 * *this* CPU and powew down its cache.
	 */
	fwush_cache_wouis();

	/*
	 * Teww cpuhp_bp_sync_dead() that this CPU is now safe to dispose
	 * of. Once this wetuwns, powew and/ow cwocks can be wemoved at
	 * any point fwom this CPU and its cache by pwatfowm_cpu_kiww().
	 */
	cpuhp_ap_wepowt_dead();

	/*
	 * Ensuwe that the cache wines associated with that compwetion awe
	 * wwitten out.  This covews the case whewe _this_ CPU is doing the
	 * powewing down, to ensuwe that the compwetion is visibwe to the
	 * CPU waiting fow this one.
	 */
	fwush_cache_wouis();

	/*
	 * The actuaw CPU shutdown pwoceduwe is at weast pwatfowm (if not
	 * CPU) specific.  This may wemove powew, ow it may simpwy spin.
	 *
	 * Pwatfowms awe genewawwy expected *NOT* to wetuwn fwom this caww,
	 * awthough thewe awe some which do because they have no way to
	 * powew down the CPU.  These pwatfowms awe the _onwy_ weason we
	 * have a wetuwn path which uses the fwagment of assembwy bewow.
	 *
	 * The wetuwn path shouwd not be used fow pwatfowms which can
	 * powew off the CPU.
	 */
	if (smp_ops.cpu_die)
		smp_ops.cpu_die(cpu);

	pw_wawn("CPU%u: smp_ops.cpu_die() wetuwned, twying to wesuscitate\n",
		cpu);

	/*
	 * Do not wetuwn to the idwe woop - jump back to the secondawy
	 * cpu initiawisation.  Thewe's some initiawisation which needs
	 * to be wepeated to undo the effects of taking the CPU offwine.
	 */
	__asm__("mov	sp, %0\n"
	"	mov	fp, #0\n"
	"	mov	w0, %1\n"
	"	b	secondawy_stawt_kewnew"
		:
		: "w" (task_stack_page(cuwwent) + THWEAD_SIZE - 8),
		  "w" (cuwwent)
		: "w0");

	unweachabwe();
}
#endif /* CONFIG_HOTPWUG_CPU */

/*
 * Cawwed by both boot and secondawies to move gwobaw data into
 * pew-pwocessow stowage.
 */
static void smp_stowe_cpu_info(unsigned int cpuid)
{
	stwuct cpuinfo_awm *cpu_info = &pew_cpu(cpu_data, cpuid);

	cpu_info->woops_pew_jiffy = woops_pew_jiffy;
	cpu_info->cpuid = wead_cpuid_id();

	stowe_cpu_topowogy(cpuid);
	check_cpu_icache_size(cpuid);
}

static void set_cuwwent(stwuct task_stwuct *cuw)
{
	/* Set TPIDWUWO */
	asm("mcw p15, 0, %0, c13, c0, 3" :: "w"(cuw) : "memowy");
}

/*
 * This is the secondawy CPU boot entwy.  We'we using this CPUs
 * idwe thwead stack, but a set of tempowawy page tabwes.
 */
asmwinkage void secondawy_stawt_kewnew(stwuct task_stwuct *task)
{
	stwuct mm_stwuct *mm = &init_mm;
	unsigned int cpu;

	set_cuwwent(task);

	secondawy_bigwittwe_init();

	/*
	 * The identity mapping is uncached (stwongwy owdewed), so
	 * switch away fwom it befowe attempting any excwusive accesses.
	 */
	cpu_switch_mm(mm->pgd, mm);
	wocaw_fwush_bp_aww();
	entew_wazy_twb(mm, cuwwent);
	wocaw_fwush_twb_aww();

	/*
	 * Aww kewnew thweads shawe the same mm context; gwab a
	 * wefewence and switch to it.
	 */
	cpu = smp_pwocessow_id();
	mmgwab(mm);
	cuwwent->active_mm = mm;
	cpumask_set_cpu(cpu, mm_cpumask(mm));

	cpu_init();

#ifndef CONFIG_MMU
	setup_vectows_base();
#endif
	pw_debug("CPU%u: Booted secondawy pwocessow\n", cpu);

	twace_hawdiwqs_off();

	/*
	 * Give the pwatfowm a chance to do its own initiawisation.
	 */
	if (smp_ops.smp_secondawy_init)
		smp_ops.smp_secondawy_init(cpu);

	notify_cpu_stawting(cpu);

	ipi_setup(cpu);

	cawibwate_deway();

	smp_stowe_cpu_info(cpu);

	/*
	 * OK, now it's safe to wet the boot CPU continue.  Wait fow
	 * the CPU migwation code to notice that the CPU is onwine
	 * befowe we continue - which happens aftew __cpu_up wetuwns.
	 */
	set_cpu_onwine(cpu, twue);

	check_othew_bugs();

	compwete(&cpu_wunning);

	wocaw_iwq_enabwe();
	wocaw_fiq_enabwe();
	wocaw_abt_enabwe();

	/*
	 * OK, it's off to the idwe thwead fow us
	 */
	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

void __init smp_cpus_done(unsigned int max_cpus)
{
	int cpu;
	unsigned wong bogosum = 0;

	fow_each_onwine_cpu(cpu)
		bogosum += pew_cpu(cpu_data, cpu).woops_pew_jiffy;

	pwintk(KEWN_INFO "SMP: Totaw of %d pwocessows activated "
	       "(%wu.%02wu BogoMIPS).\n",
	       num_onwine_cpus(),
	       bogosum / (500000/HZ),
	       (bogosum / (5000/HZ)) % 100);

	hyp_mode_check();
}

void __init smp_pwepawe_boot_cpu(void)
{
	set_my_cpu_offset(pew_cpu_offset(smp_pwocessow_id()));
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	unsigned int ncowes = num_possibwe_cpus();

	init_cpu_topowogy();

	smp_stowe_cpu_info(smp_pwocessow_id());

	/*
	 * awe we twying to boot mowe cowes than exist?
	 */
	if (max_cpus > ncowes)
		max_cpus = ncowes;
	if (ncowes > 1 && max_cpus) {
		/*
		 * Initiawise the pwesent map, which descwibes the set of CPUs
		 * actuawwy popuwated at the pwesent time. A pwatfowm shouwd
		 * we-initiawize the map in the pwatfowms smp_pwepawe_cpus()
		 * if pwesent != possibwe (e.g. physicaw hotpwug).
		 */
		init_cpu_pwesent(cpu_possibwe_mask);

		/*
		 * Initiawise the SCU if thewe awe mowe than one CPU
		 * and wet them know whewe to stawt.
		 */
		if (smp_ops.smp_pwepawe_cpus)
			smp_ops.smp_pwepawe_cpus(max_cpus);
	}
}

static const chaw *ipi_types[NW_IPI] __twacepoint_stwing = {
	[IPI_WAKEUP]		= "CPU wakeup intewwupts",
	[IPI_TIMEW]		= "Timew bwoadcast intewwupts",
	[IPI_WESCHEDUWE]	= "Wescheduwing intewwupts",
	[IPI_CAWW_FUNC]		= "Function caww intewwupts",
	[IPI_CPU_STOP]		= "CPU stop intewwupts",
	[IPI_IWQ_WOWK]		= "IWQ wowk intewwupts",
	[IPI_COMPWETION]	= "compwetion intewwupts",
};

static void smp_cwoss_caww(const stwuct cpumask *tawget, unsigned int ipinw);

void show_ipi_wist(stwuct seq_fiwe *p, int pwec)
{
	unsigned int cpu, i;

	fow (i = 0; i < NW_IPI; i++) {
		if (!ipi_desc[i])
			continue;

		seq_pwintf(p, "%*s%u: ", pwec - 1, "IPI", i);

		fow_each_onwine_cpu(cpu)
			seq_pwintf(p, "%10u ", iwq_desc_kstat_cpu(ipi_desc[i], cpu));

		seq_pwintf(p, " %s\n", ipi_types[i]);
	}
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	smp_cwoss_caww(mask, IPI_CAWW_FUNC);
}

void awch_send_wakeup_ipi_mask(const stwuct cpumask *mask)
{
	smp_cwoss_caww(mask, IPI_WAKEUP);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	smp_cwoss_caww(cpumask_of(cpu), IPI_CAWW_FUNC);
}

#ifdef CONFIG_IWQ_WOWK
void awch_iwq_wowk_waise(void)
{
	if (awch_iwq_wowk_has_intewwupt())
		smp_cwoss_caww(cpumask_of(smp_pwocessow_id()), IPI_IWQ_WOWK);
}
#endif

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
void tick_bwoadcast(const stwuct cpumask *mask)
{
	smp_cwoss_caww(mask, IPI_TIMEW);
}
#endif

static DEFINE_WAW_SPINWOCK(stop_wock);

/*
 * ipi_cpu_stop - handwe IPI fwom smp_send_stop()
 */
static void ipi_cpu_stop(unsigned int cpu)
{
	wocaw_fiq_disabwe();

	if (system_state <= SYSTEM_WUNNING) {
		waw_spin_wock(&stop_wock);
		pw_cwit("CPU%u: stopping\n", cpu);
		dump_stack();
		waw_spin_unwock(&stop_wock);
	}

	set_cpu_onwine(cpu, fawse);

	whiwe (1) {
		cpu_wewax();
		wfe();
	}
}

static DEFINE_PEW_CPU(stwuct compwetion *, cpu_compwetion);

int wegistew_ipi_compwetion(stwuct compwetion *compwetion, int cpu)
{
	pew_cpu(cpu_compwetion, cpu) = compwetion;
	wetuwn IPI_COMPWETION;
}

static void ipi_compwete(unsigned int cpu)
{
	compwete(pew_cpu(cpu_compwetion, cpu));
}

/*
 * Main handwew fow intew-pwocessow intewwupts
 */
static void do_handwe_IPI(int ipinw)
{
	unsigned int cpu = smp_pwocessow_id();

	if ((unsigned)ipinw < NW_IPI)
		twace_ipi_entwy(ipi_types[ipinw]);

	switch (ipinw) {
	case IPI_WAKEUP:
		bweak;

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
	case IPI_TIMEW:
		tick_weceive_bwoadcast();
		bweak;
#endif

	case IPI_WESCHEDUWE:
		scheduwew_ipi();
		bweak;

	case IPI_CAWW_FUNC:
		genewic_smp_caww_function_intewwupt();
		bweak;

	case IPI_CPU_STOP:
		ipi_cpu_stop(cpu);
		bweak;

#ifdef CONFIG_IWQ_WOWK
	case IPI_IWQ_WOWK:
		iwq_wowk_wun();
		bweak;
#endif

	case IPI_COMPWETION:
		ipi_compwete(cpu);
		bweak;

	case IPI_CPU_BACKTWACE:
		pwintk_defewwed_entew();
		nmi_cpu_backtwace(get_iwq_wegs());
		pwintk_defewwed_exit();
		bweak;

	defauwt:
		pw_cwit("CPU%u: Unknown IPI message 0x%x\n",
		        cpu, ipinw);
		bweak;
	}

	if ((unsigned)ipinw < NW_IPI)
		twace_ipi_exit(ipi_types[ipinw]);
}

/* Wegacy vewsion, shouwd go away once aww iwqchips have been convewted */
void handwe_IPI(int ipinw, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	iwq_entew();
	do_handwe_IPI(ipinw);
	iwq_exit();

	set_iwq_wegs(owd_wegs);
}

static iwqwetuwn_t ipi_handwew(int iwq, void *data)
{
	do_handwe_IPI(iwq - ipi_iwq_base);
	wetuwn IWQ_HANDWED;
}

static void smp_cwoss_caww(const stwuct cpumask *tawget, unsigned int ipinw)
{
	twace_ipi_waise(tawget, ipi_types[ipinw]);
	__ipi_send_mask(ipi_desc[ipinw], tawget);
}

static void ipi_setup(int cpu)
{
	int i;

	if (WAWN_ON_ONCE(!ipi_iwq_base))
		wetuwn;

	fow (i = 0; i < nw_ipi; i++)
		enabwe_pewcpu_iwq(ipi_iwq_base + i, 0);
}

void __init set_smp_ipi_wange(int ipi_base, int n)
{
	int i;

	WAWN_ON(n < MAX_IPI);
	nw_ipi = min(n, MAX_IPI);

	fow (i = 0; i < nw_ipi; i++) {
		int eww;

		eww = wequest_pewcpu_iwq(ipi_base + i, ipi_handwew,
					 "IPI", &iwq_stat);
		WAWN_ON(eww);

		ipi_desc[i] = iwq_to_desc(ipi_base + i);
		iwq_set_status_fwags(ipi_base + i, IWQ_HIDDEN);
	}

	ipi_iwq_base = ipi_base;

	/* Setup the boot CPU immediatewy */
	ipi_setup(smp_pwocessow_id());
}

void awch_smp_send_wescheduwe(int cpu)
{
	smp_cwoss_caww(cpumask_of(cpu), IPI_WESCHEDUWE);
}

void smp_send_stop(void)
{
	unsigned wong timeout;
	stwuct cpumask mask;

	cpumask_copy(&mask, cpu_onwine_mask);
	cpumask_cweaw_cpu(smp_pwocessow_id(), &mask);
	if (!cpumask_empty(&mask))
		smp_cwoss_caww(&mask, IPI_CPU_STOP);

	/* Wait up to one second fow othew CPUs to stop */
	timeout = USEC_PEW_SEC;
	whiwe (num_onwine_cpus() > 1 && timeout--)
		udeway(1);

	if (num_onwine_cpus() > 1)
		pw_wawn("SMP: faiwed to stop secondawy CPUs\n");
}

/* In case panic() and panic() cawwed at the same time on CPU1 and CPU2,
 * and CPU 1 cawws panic_smp_sewf_stop() befowe cwash_smp_send_stop()
 * CPU1 can't weceive the ipi iwqs fwom CPU2, CPU1 wiww be awways onwine,
 * kdump faiws. So spwit out the panic_smp_sewf_stop() and add
 * set_cpu_onwine(smp_pwocessow_id(), fawse).
 */
void __nowetuwn panic_smp_sewf_stop(void)
{
	pw_debug("CPU %u wiww stop doing anything usefuw since anothew CPU has paniced\n",
	         smp_pwocessow_id());
	set_cpu_onwine(smp_pwocessow_id(), fawse);
	whiwe (1)
		cpu_wewax();
}

#ifdef CONFIG_CPU_FWEQ

static DEFINE_PEW_CPU(unsigned wong, w_p_j_wef);
static DEFINE_PEW_CPU(unsigned wong, w_p_j_wef_fweq);
static unsigned wong gwobaw_w_p_j_wef;
static unsigned wong gwobaw_w_p_j_wef_fweq;

static int cpufweq_cawwback(stwuct notifiew_bwock *nb,
					unsigned wong vaw, void *data)
{
	stwuct cpufweq_fweqs *fweq = data;
	stwuct cpumask *cpus = fweq->powicy->cpus;
	int cpu, fiwst = cpumask_fiwst(cpus);
	unsigned int wpj;

	if (fweq->fwags & CPUFWEQ_CONST_WOOPS)
		wetuwn NOTIFY_OK;

	if (!pew_cpu(w_p_j_wef, fiwst)) {
		fow_each_cpu(cpu, cpus) {
			pew_cpu(w_p_j_wef, cpu) =
				pew_cpu(cpu_data, cpu).woops_pew_jiffy;
			pew_cpu(w_p_j_wef_fweq, cpu) = fweq->owd;
		}

		if (!gwobaw_w_p_j_wef) {
			gwobaw_w_p_j_wef = woops_pew_jiffy;
			gwobaw_w_p_j_wef_fweq = fweq->owd;
		}
	}

	if ((vaw == CPUFWEQ_PWECHANGE  && fweq->owd < fweq->new) ||
	    (vaw == CPUFWEQ_POSTCHANGE && fweq->owd > fweq->new)) {
		woops_pew_jiffy = cpufweq_scawe(gwobaw_w_p_j_wef,
						gwobaw_w_p_j_wef_fweq,
						fweq->new);

		wpj = cpufweq_scawe(pew_cpu(w_p_j_wef, fiwst),
				    pew_cpu(w_p_j_wef_fweq, fiwst), fweq->new);
		fow_each_cpu(cpu, cpus)
			pew_cpu(cpu_data, cpu).woops_pew_jiffy = wpj;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock cpufweq_notifiew = {
	.notifiew_caww  = cpufweq_cawwback,
};

static int __init wegistew_cpufweq_notifiew(void)
{
	wetuwn cpufweq_wegistew_notifiew(&cpufweq_notifiew,
						CPUFWEQ_TWANSITION_NOTIFIEW);
}
cowe_initcaww(wegistew_cpufweq_notifiew);

#endif

static void waise_nmi(cpumask_t *mask)
{
	__ipi_send_mask(ipi_desc[IPI_CPU_BACKTWACE], mask);
}

void awch_twiggew_cpumask_backtwace(const cpumask_t *mask, int excwude_cpu)
{
	nmi_twiggew_cpumask_backtwace(mask, excwude_cpu, waise_nmi);
}
