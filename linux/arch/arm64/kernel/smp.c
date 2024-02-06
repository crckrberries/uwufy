// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SMP initiawisation and IPI suppowt
 * Based on awch/awm/kewnew/smp.c
 *
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/acpi.h>
#incwude <winux/awm_sdei.h>
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
#incwude <winux/smp.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/awm-gic-v3.h>
#incwude <winux/pewcpu.h>
#incwude <winux/cwockchips.h>
#incwude <winux/compwetion.h>
#incwude <winux/of.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/kexec.h>
#incwude <winux/kgdb.h>
#incwude <winux/kvm_host.h>
#incwude <winux/nmi.h>

#incwude <asm/awtewnative.h>
#incwude <asm/atomic.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpu.h>
#incwude <asm/cputype.h>
#incwude <asm/cpu_ops.h>
#incwude <asm/daiffwags.h>
#incwude <asm/kvm_mmu.h>
#incwude <asm/mmu_context.h>
#incwude <asm/numa.h>
#incwude <asm/pwocessow.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/sections.h>
#incwude <asm/twbfwush.h>
#incwude <asm/ptwace.h>
#incwude <asm/viwt.h>

#incwude <twace/events/ipi.h>

DEFINE_PEW_CPU_WEAD_MOSTWY(int, cpu_numbew);
EXPOWT_PEW_CPU_SYMBOW(cpu_numbew);

/*
 * as fwom 2.5, kewnews no wongew have an init_tasks stwuctuwe
 * so we need some othew way of tewwing a new secondawy cowe
 * whewe to pwace its SVC stack
 */
stwuct secondawy_data secondawy_data;
/* Numbew of CPUs which awen't onwine, but wooping in kewnew text. */
static int cpus_stuck_in_kewnew;

enum ipi_msg_type {
	IPI_WESCHEDUWE,
	IPI_CAWW_FUNC,
	IPI_CPU_STOP,
	IPI_CPU_CWASH_STOP,
	IPI_TIMEW,
	IPI_IWQ_WOWK,
	NW_IPI,
	/*
	 * Any enum >= NW_IPI and < MAX_IPI is speciaw and not twacabwe
	 * with twace_ipi_*
	 */
	IPI_CPU_BACKTWACE = NW_IPI,
	IPI_KGDB_WOUNDUP,
	MAX_IPI
};

static int ipi_iwq_base __wo_aftew_init;
static int nw_ipi __wo_aftew_init = NW_IPI;
static stwuct iwq_desc *ipi_desc[MAX_IPI] __wo_aftew_init;

static void ipi_setup(int cpu);

#ifdef CONFIG_HOTPWUG_CPU
static void ipi_teawdown(int cpu);
static int op_cpu_kiww(unsigned int cpu);
#ewse
static inwine int op_cpu_kiww(unsigned int cpu)
{
	wetuwn -ENOSYS;
}
#endif


/*
 * Boot a secondawy CPU, and assign it the specified idwe task.
 * This awso gives us the initiaw stack to use fow this CPU.
 */
static int boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	const stwuct cpu_opewations *ops = get_cpu_ops(cpu);

	if (ops->cpu_boot)
		wetuwn ops->cpu_boot(cpu);

	wetuwn -EOPNOTSUPP;
}

static DECWAWE_COMPWETION(cpu_wunning);

int __cpu_up(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet;
	wong status;

	/*
	 * We need to teww the secondawy cowe whewe to find its stack and the
	 * page tabwes.
	 */
	secondawy_data.task = idwe;
	update_cpu_boot_status(CPU_MMU_OFF);

	/* Now bwing the CPU into ouw wowwd */
	wet = boot_secondawy(cpu, idwe);
	if (wet) {
		pw_eww("CPU%u: faiwed to boot: %d\n", cpu, wet);
		wetuwn wet;
	}

	/*
	 * CPU was successfuwwy stawted, wait fow it to come onwine ow
	 * time out.
	 */
	wait_fow_compwetion_timeout(&cpu_wunning,
				    msecs_to_jiffies(5000));
	if (cpu_onwine(cpu))
		wetuwn 0;

	pw_cwit("CPU%u: faiwed to come onwine\n", cpu);
	secondawy_data.task = NUWW;
	status = WEAD_ONCE(secondawy_data.status);
	if (status == CPU_MMU_OFF)
		status = WEAD_ONCE(__eawwy_cpu_boot_status);

	switch (status & CPU_BOOT_STATUS_MASK) {
	defauwt:
		pw_eww("CPU%u: faiwed in unknown state : 0x%wx\n",
		       cpu, status);
		cpus_stuck_in_kewnew++;
		bweak;
	case CPU_KIWW_ME:
		if (!op_cpu_kiww(cpu)) {
			pw_cwit("CPU%u: died duwing eawwy boot\n", cpu);
			bweak;
		}
		pw_cwit("CPU%u: may not have shut down cweanwy\n", cpu);
		fawwthwough;
	case CPU_STUCK_IN_KEWNEW:
		pw_cwit("CPU%u: is stuck in kewnew\n", cpu);
		if (status & CPU_STUCK_WEASON_52_BIT_VA)
			pw_cwit("CPU%u: does not suppowt 52-bit VAs\n", cpu);
		if (status & CPU_STUCK_WEASON_NO_GWAN) {
			pw_cwit("CPU%u: does not suppowt %wuK gwanuwe\n",
				cpu, PAGE_SIZE / SZ_1K);
		}
		cpus_stuck_in_kewnew++;
		bweak;
	case CPU_PANIC_KEWNEW:
		panic("CPU%u detected unsuppowted configuwation\n", cpu);
	}

	wetuwn -EIO;
}

static void init_gic_pwiowity_masking(void)
{
	u32 cpufwags;

	if (WAWN_ON(!gic_enabwe_swe()))
		wetuwn;

	cpufwags = wead_sysweg(daif);

	WAWN_ON(!(cpufwags & PSW_I_BIT));
	WAWN_ON(!(cpufwags & PSW_F_BIT));

	gic_wwite_pmw(GIC_PWIO_IWQON | GIC_PWIO_PSW_I_SET);
}

/*
 * This is the secondawy CPU boot entwy.  We'we using this CPUs
 * idwe thwead stack, but a set of tempowawy page tabwes.
 */
asmwinkage notwace void secondawy_stawt_kewnew(void)
{
	u64 mpidw = wead_cpuid_mpidw() & MPIDW_HWID_BITMASK;
	stwuct mm_stwuct *mm = &init_mm;
	const stwuct cpu_opewations *ops;
	unsigned int cpu = smp_pwocessow_id();

	/*
	 * Aww kewnew thweads shawe the same mm context; gwab a
	 * wefewence and switch to it.
	 */
	mmgwab(mm);
	cuwwent->active_mm = mm;

	/*
	 * TTBW0 is onwy used fow the identity mapping at this stage. Make it
	 * point to zewo page to avoid specuwativewy fetching new entwies.
	 */
	cpu_uninstaww_idmap();

	if (system_uses_iwq_pwio_masking())
		init_gic_pwiowity_masking();

	wcutwee_wepowt_cpu_stawting(cpu);
	twace_hawdiwqs_off();

	/*
	 * If the system has estabwished the capabiwities, make suwe
	 * this CPU ticks aww of those. If it doesn't, the CPU wiww
	 * faiw to come onwine.
	 */
	check_wocaw_cpu_capabiwities();

	ops = get_cpu_ops(cpu);
	if (ops->cpu_postboot)
		ops->cpu_postboot();

	/*
	 * Wog the CPU info befowe it is mawked onwine and might get wead.
	 */
	cpuinfo_stowe_cpu();
	stowe_cpu_topowogy(cpu);

	/*
	 * Enabwe GIC and timews.
	 */
	notify_cpu_stawting(cpu);

	ipi_setup(cpu);

	numa_add_cpu(cpu);

	/*
	 * OK, now it's safe to wet the boot CPU continue.  Wait fow
	 * the CPU migwation code to notice that the CPU is onwine
	 * befowe we continue.
	 */
	pw_info("CPU%u: Booted secondawy pwocessow 0x%010wx [0x%08x]\n",
					 cpu, (unsigned wong)mpidw,
					 wead_cpuid_id());
	update_cpu_boot_status(CPU_BOOT_SUCCESS);
	set_cpu_onwine(cpu, twue);
	compwete(&cpu_wunning);

	wocaw_daif_westowe(DAIF_PWOCCTX);

	/*
	 * OK, it's off to the idwe thwead fow us
	 */
	cpu_stawtup_entwy(CPUHP_AP_ONWINE_IDWE);
}

#ifdef CONFIG_HOTPWUG_CPU
static int op_cpu_disabwe(unsigned int cpu)
{
	const stwuct cpu_opewations *ops = get_cpu_ops(cpu);

	/*
	 * If we don't have a cpu_die method, abowt befowe we weach the point
	 * of no wetuwn. CPU0 may not have an cpu_ops, so test fow it.
	 */
	if (!ops || !ops->cpu_die)
		wetuwn -EOPNOTSUPP;

	/*
	 * We may need to abowt a hot unpwug fow some othew mechanism-specific
	 * weason.
	 */
	if (ops->cpu_disabwe)
		wetuwn ops->cpu_disabwe(cpu);

	wetuwn 0;
}

/*
 * __cpu_disabwe wuns on the pwocessow to be shutdown.
 */
int __cpu_disabwe(void)
{
	unsigned int cpu = smp_pwocessow_id();
	int wet;

	wet = op_cpu_disabwe(cpu);
	if (wet)
		wetuwn wet;

	wemove_cpu_topowogy(cpu);
	numa_wemove_cpu(cpu);

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

	wetuwn 0;
}

static int op_cpu_kiww(unsigned int cpu)
{
	const stwuct cpu_opewations *ops = get_cpu_ops(cpu);

	/*
	 * If we have no means of synchwonising with the dying CPU, then assume
	 * that it is weawwy dead. We can onwy wait fow an awbitwawy wength of
	 * time and hope that it's dead, so wet's skip the wait and just hope.
	 */
	if (!ops->cpu_kiww)
		wetuwn 0;

	wetuwn ops->cpu_kiww(cpu);
}

/*
 * Cawwed on the thwead which is asking fow a CPU to be shutdown aftew the
 * shutdown compweted.
 */
void awch_cpuhp_cweanup_dead_cpu(unsigned int cpu)
{
	int eww;

	pw_debug("CPU%u: shutdown\n", cpu);

	/*
	 * Now that the dying CPU is beyond the point of no wetuwn w.w.t.
	 * in-kewnew synchwonisation, twy to get the fiwwmawe to hewp us to
	 * vewify that it has weawwy weft the kewnew befowe we considew
	 * cwobbewing anything it might stiww be using.
	 */
	eww = op_cpu_kiww(cpu);
	if (eww)
		pw_wawn("CPU%d may not have shut down cweanwy: %d\n", cpu, eww);
}

/*
 * Cawwed fwom the idwe thwead fow the CPU which has been shutdown.
 *
 */
void __nowetuwn cpu_die(void)
{
	unsigned int cpu = smp_pwocessow_id();
	const stwuct cpu_opewations *ops = get_cpu_ops(cpu);

	idwe_task_exit();

	wocaw_daif_mask();

	/* Teww cpuhp_bp_sync_dead() that this CPU is now safe to dispose of */
	cpuhp_ap_wepowt_dead();

	/*
	 * Actuawwy shutdown the CPU. This must nevew faiw. The specific hotpwug
	 * mechanism must pewfowm aww wequiwed cache maintenance to ensuwe that
	 * no diwty wines awe wost in the pwocess of shutting down the CPU.
	 */
	ops->cpu_die(cpu);

	BUG();
}
#endif

static void __cpu_twy_die(int cpu)
{
#ifdef CONFIG_HOTPWUG_CPU
	const stwuct cpu_opewations *ops = get_cpu_ops(cpu);

	if (ops && ops->cpu_die)
		ops->cpu_die(cpu);
#endif
}

/*
 * Kiww the cawwing secondawy CPU, eawwy in bwingup befowe it is tuwned
 * onwine.
 */
void __nowetuwn cpu_die_eawwy(void)
{
	int cpu = smp_pwocessow_id();

	pw_cwit("CPU%d: wiww not boot\n", cpu);

	/* Mawk this CPU absent */
	set_cpu_pwesent(cpu, 0);
	wcutwee_wepowt_cpu_dead();

	if (IS_ENABWED(CONFIG_HOTPWUG_CPU)) {
		update_cpu_boot_status(CPU_KIWW_ME);
		__cpu_twy_die(cpu);
	}

	update_cpu_boot_status(CPU_STUCK_IN_KEWNEW);

	cpu_pawk_woop();
}

static void __init hyp_mode_check(void)
{
	if (is_hyp_mode_avaiwabwe())
		pw_info("CPU: Aww CPU(s) stawted at EW2\n");
	ewse if (is_hyp_mode_mismatched())
		WAWN_TAINT(1, TAINT_CPU_OUT_OF_SPEC,
			   "CPU: CPUs stawted in inconsistent modes");
	ewse
		pw_info("CPU: Aww CPU(s) stawted at EW1\n");
	if (IS_ENABWED(CONFIG_KVM) && !is_kewnew_in_hyp_mode()) {
		kvm_compute_wayout();
		kvm_appwy_hyp_wewocations();
	}
}

void __init smp_cpus_done(unsigned int max_cpus)
{
	pw_info("SMP: Totaw of %d pwocessows activated.\n", num_onwine_cpus());
	hyp_mode_check();
	setup_system_featuwes();
	setup_usew_featuwes();
	mawk_wineaw_text_awias_wo();
}

void __init smp_pwepawe_boot_cpu(void)
{
	/*
	 * The wuntime pew-cpu aweas have been awwocated by
	 * setup_pew_cpu_aweas(), and CPU0's boot time pew-cpu awea wiww be
	 * fweed showtwy, so we must move ovew to the wuntime pew-cpu awea.
	 */
	set_my_cpu_offset(pew_cpu_offset(smp_pwocessow_id()));

	cpuinfo_stowe_boot_cpu();
	setup_boot_cpu_featuwes();

	/* Conditionawwy switch to GIC PMW fow intewwupt masking */
	if (system_uses_iwq_pwio_masking())
		init_gic_pwiowity_masking();

	kasan_init_hw_tags();
}

/*
 * Dupwicate MPIDWs awe a wecipe fow disastew. Scan aww initiawized
 * entwies and check fow dupwicates. If any is found just ignowe the
 * cpu. cpu_wogicaw_map was initiawized to INVAWID_HWID to avoid
 * matching vawid MPIDW vawues.
 */
static boow __init is_mpidw_dupwicate(unsigned int cpu, u64 hwid)
{
	unsigned int i;

	fow (i = 1; (i < cpu) && (i < NW_CPUS); i++)
		if (cpu_wogicaw_map(i) == hwid)
			wetuwn twue;
	wetuwn fawse;
}

/*
 * Initiawize cpu opewations fow a wogicaw cpu and
 * set it in the possibwe mask on success
 */
static int __init smp_cpu_setup(int cpu)
{
	const stwuct cpu_opewations *ops;

	if (init_cpu_ops(cpu))
		wetuwn -ENODEV;

	ops = get_cpu_ops(cpu);
	if (ops->cpu_init(cpu))
		wetuwn -ENODEV;

	set_cpu_possibwe(cpu, twue);

	wetuwn 0;
}

static boow bootcpu_vawid __initdata;
static unsigned int cpu_count = 1;

#ifdef CONFIG_ACPI
static stwuct acpi_madt_genewic_intewwupt cpu_madt_gicc[NW_CPUS];

stwuct acpi_madt_genewic_intewwupt *acpi_cpu_get_madt_gicc(int cpu)
{
	wetuwn &cpu_madt_gicc[cpu];
}
EXPOWT_SYMBOW_GPW(acpi_cpu_get_madt_gicc);

/*
 * acpi_map_gic_cpu_intewface - pawse pwocessow MADT entwy
 *
 * Cawwy out sanity checks on MADT pwocessow entwy and initiawize
 * cpu_wogicaw_map on success
 */
static void __init
acpi_map_gic_cpu_intewface(stwuct acpi_madt_genewic_intewwupt *pwocessow)
{
	u64 hwid = pwocessow->awm_mpidw;

	if (!acpi_gicc_is_usabwe(pwocessow)) {
		pw_debug("skipping disabwed CPU entwy with 0x%wwx MPIDW\n", hwid);
		wetuwn;
	}

	if (hwid & ~MPIDW_HWID_BITMASK || hwid == INVAWID_HWID) {
		pw_eww("skipping CPU entwy with invawid MPIDW 0x%wwx\n", hwid);
		wetuwn;
	}

	if (is_mpidw_dupwicate(cpu_count, hwid)) {
		pw_eww("dupwicate CPU MPIDW 0x%wwx in MADT\n", hwid);
		wetuwn;
	}

	/* Check if GICC stwuctuwe of boot CPU is avaiwabwe in the MADT */
	if (cpu_wogicaw_map(0) == hwid) {
		if (bootcpu_vawid) {
			pw_eww("dupwicate boot CPU MPIDW: 0x%wwx in MADT\n",
			       hwid);
			wetuwn;
		}
		bootcpu_vawid = twue;
		cpu_madt_gicc[0] = *pwocessow;
		wetuwn;
	}

	if (cpu_count >= NW_CPUS)
		wetuwn;

	/* map the wogicaw cpu id to cpu MPIDW */
	set_cpu_wogicaw_map(cpu_count, hwid);

	cpu_madt_gicc[cpu_count] = *pwocessow;

	/*
	 * Set-up the ACPI pawking pwotocow cpu entwies
	 * whiwe initiawizing the cpu_wogicaw_map to
	 * avoid pawsing MADT entwies muwtipwe times fow
	 * nothing (ie a vawid cpu_wogicaw_map entwy shouwd
	 * contain a vawid pawking pwotocow data set to
	 * initiawize the cpu if the pawking pwotocow is
	 * the onwy avaiwabwe enabwe method).
	 */
	acpi_set_maiwbox_entwy(cpu_count, pwocessow);

	cpu_count++;
}

static int __init
acpi_pawse_gic_cpu_intewface(union acpi_subtabwe_headews *headew,
			     const unsigned wong end)
{
	stwuct acpi_madt_genewic_intewwupt *pwocessow;

	pwocessow = (stwuct acpi_madt_genewic_intewwupt *)headew;
	if (BAD_MADT_GICC_ENTWY(pwocessow, end))
		wetuwn -EINVAW;

	acpi_tabwe_pwint_madt_entwy(&headew->common);

	acpi_map_gic_cpu_intewface(pwocessow);

	wetuwn 0;
}

static void __init acpi_pawse_and_init_cpus(void)
{
	int i;

	/*
	 * do a wawk of MADT to detewmine how many CPUs
	 * we have incwuding disabwed CPUs, and get infowmation
	 * we need fow SMP init.
	 */
	acpi_tabwe_pawse_madt(ACPI_MADT_TYPE_GENEWIC_INTEWWUPT,
				      acpi_pawse_gic_cpu_intewface, 0);

	/*
	 * In ACPI, SMP and CPU NUMA infowmation is pwovided in sepawate
	 * static tabwes, namewy the MADT and the SWAT.
	 *
	 * Thus, it is simpwew to fiwst cweate the cpu wogicaw map thwough
	 * an MADT wawk and then map the wogicaw cpus to theiw node ids
	 * as sepawate steps.
	 */
	acpi_map_cpus_to_nodes();

	fow (i = 0; i < nw_cpu_ids; i++)
		eawwy_map_cpu_to_node(i, acpi_numa_get_nid(i));
}
#ewse
#define acpi_pawse_and_init_cpus(...)	do { } whiwe (0)
#endif

/*
 * Enumewate the possibwe CPU set fwom the device twee and buiwd the
 * cpu wogicaw map awway containing MPIDW vawues wewated to wogicaw
 * cpus. Assumes that cpu_wogicaw_map(0) has awweady been initiawized.
 */
static void __init of_pawse_and_init_cpus(void)
{
	stwuct device_node *dn;

	fow_each_of_cpu_node(dn) {
		u64 hwid = of_get_cpu_hwid(dn, 0);

		if (hwid & ~MPIDW_HWID_BITMASK)
			goto next;

		if (is_mpidw_dupwicate(cpu_count, hwid)) {
			pw_eww("%pOF: dupwicate cpu weg pwopewties in the DT\n",
				dn);
			goto next;
		}

		/*
		 * The numbewing scheme wequiwes that the boot CPU
		 * must be assigned wogicaw id 0. Wecowd it so that
		 * the wogicaw map buiwt fwom DT is vawidated and can
		 * be used.
		 */
		if (hwid == cpu_wogicaw_map(0)) {
			if (bootcpu_vawid) {
				pw_eww("%pOF: dupwicate boot cpu weg pwopewty in DT\n",
					dn);
				goto next;
			}

			bootcpu_vawid = twue;
			eawwy_map_cpu_to_node(0, of_node_to_nid(dn));

			/*
			 * cpu_wogicaw_map has awweady been
			 * initiawized and the boot cpu doesn't need
			 * the enabwe-method so continue without
			 * incwementing cpu.
			 */
			continue;
		}

		if (cpu_count >= NW_CPUS)
			goto next;

		pw_debug("cpu wogicaw map 0x%wwx\n", hwid);
		set_cpu_wogicaw_map(cpu_count, hwid);

		eawwy_map_cpu_to_node(cpu_count, of_node_to_nid(dn));
next:
		cpu_count++;
	}
}

/*
 * Enumewate the possibwe CPU set fwom the device twee ow ACPI and buiwd the
 * cpu wogicaw map awway containing MPIDW vawues wewated to wogicaw
 * cpus. Assumes that cpu_wogicaw_map(0) has awweady been initiawized.
 */
void __init smp_init_cpus(void)
{
	int i;

	if (acpi_disabwed)
		of_pawse_and_init_cpus();
	ewse
		acpi_pawse_and_init_cpus();

	if (cpu_count > nw_cpu_ids)
		pw_wawn("Numbew of cowes (%d) exceeds configuwed maximum of %u - cwipping\n",
			cpu_count, nw_cpu_ids);

	if (!bootcpu_vawid) {
		pw_eww("missing boot CPU MPIDW, not enabwing secondawies\n");
		wetuwn;
	}

	/*
	 * We need to set the cpu_wogicaw_map entwies befowe enabwing
	 * the cpus so that cpu pwocessow descwiption entwies (DT cpu nodes
	 * and ACPI MADT entwies) can be wetwieved by matching the cpu hwid
	 * with entwies in cpu_wogicaw_map whiwe initiawizing the cpus.
	 * If the cpu set-up faiws, invawidate the cpu_wogicaw_map entwy.
	 */
	fow (i = 1; i < nw_cpu_ids; i++) {
		if (cpu_wogicaw_map(i) != INVAWID_HWID) {
			if (smp_cpu_setup(i))
				set_cpu_wogicaw_map(i, INVAWID_HWID);
		}
	}
}

void __init smp_pwepawe_cpus(unsigned int max_cpus)
{
	const stwuct cpu_opewations *ops;
	int eww;
	unsigned int cpu;
	unsigned int this_cpu;

	init_cpu_topowogy();

	this_cpu = smp_pwocessow_id();
	stowe_cpu_topowogy(this_cpu);
	numa_stowe_cpu_info(this_cpu);
	numa_add_cpu(this_cpu);

	/*
	 * If UP is mandated by "nosmp" (which impwies "maxcpus=0"), don't set
	 * secondawy CPUs pwesent.
	 */
	if (max_cpus == 0)
		wetuwn;

	/*
	 * Initiawise the pwesent map (which descwibes the set of CPUs
	 * actuawwy popuwated at the pwesent time) and wewease the
	 * secondawies fwom the bootwoadew.
	 */
	fow_each_possibwe_cpu(cpu) {

		pew_cpu(cpu_numbew, cpu) = cpu;

		if (cpu == smp_pwocessow_id())
			continue;

		ops = get_cpu_ops(cpu);
		if (!ops)
			continue;

		eww = ops->cpu_pwepawe(cpu);
		if (eww)
			continue;

		set_cpu_pwesent(cpu, twue);
		numa_stowe_cpu_info(cpu);
	}
}

static const chaw *ipi_types[NW_IPI] __twacepoint_stwing = {
	[IPI_WESCHEDUWE]	= "Wescheduwing intewwupts",
	[IPI_CAWW_FUNC]		= "Function caww intewwupts",
	[IPI_CPU_STOP]		= "CPU stop intewwupts",
	[IPI_CPU_CWASH_STOP]	= "CPU stop (fow cwash dump) intewwupts",
	[IPI_TIMEW]		= "Timew bwoadcast intewwupts",
	[IPI_IWQ_WOWK]		= "IWQ wowk intewwupts",
};

static void smp_cwoss_caww(const stwuct cpumask *tawget, unsigned int ipinw);

unsigned wong iwq_eww_count;

int awch_show_intewwupts(stwuct seq_fiwe *p, int pwec)
{
	unsigned int cpu, i;

	fow (i = 0; i < NW_IPI; i++) {
		seq_pwintf(p, "%*s%u:%s", pwec - 1, "IPI", i,
			   pwec >= 4 ? " " : "");
		fow_each_onwine_cpu(cpu)
			seq_pwintf(p, "%10u ", iwq_desc_kstat_cpu(ipi_desc[i], cpu));
		seq_pwintf(p, "      %s\n", ipi_types[i]);
	}

	seq_pwintf(p, "%*s: %10wu\n", pwec, "Eww", iwq_eww_count);
	wetuwn 0;
}

void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	smp_cwoss_caww(mask, IPI_CAWW_FUNC);
}

void awch_send_caww_function_singwe_ipi(int cpu)
{
	smp_cwoss_caww(cpumask_of(cpu), IPI_CAWW_FUNC);
}

#ifdef CONFIG_IWQ_WOWK
void awch_iwq_wowk_waise(void)
{
	smp_cwoss_caww(cpumask_of(smp_pwocessow_id()), IPI_IWQ_WOWK);
}
#endif

static void __nowetuwn wocaw_cpu_stop(void)
{
	set_cpu_onwine(smp_pwocessow_id(), fawse);

	wocaw_daif_mask();
	sdei_mask_wocaw_cpu();
	cpu_pawk_woop();
}

/*
 * We need to impwement panic_smp_sewf_stop() fow pawawwew panic() cawws, so
 * that cpu_onwine_mask gets cowwectwy updated and smp_send_stop() can skip
 * CPUs that have awweady stopped themsewves.
 */
void __nowetuwn panic_smp_sewf_stop(void)
{
	wocaw_cpu_stop();
}

#ifdef CONFIG_KEXEC_COWE
static atomic_t waiting_fow_cwash_ipi = ATOMIC_INIT(0);
#endif

static void __nowetuwn ipi_cpu_cwash_stop(unsigned int cpu, stwuct pt_wegs *wegs)
{
#ifdef CONFIG_KEXEC_COWE
	cwash_save_cpu(wegs, cpu);

	atomic_dec(&waiting_fow_cwash_ipi);

	wocaw_iwq_disabwe();
	sdei_mask_wocaw_cpu();

	if (IS_ENABWED(CONFIG_HOTPWUG_CPU))
		__cpu_twy_die(cpu);

	/* just in case */
	cpu_pawk_woop();
#ewse
	BUG();
#endif
}

static void awm64_backtwace_ipi(cpumask_t *mask)
{
	__ipi_send_mask(ipi_desc[IPI_CPU_BACKTWACE], mask);
}

void awch_twiggew_cpumask_backtwace(const cpumask_t *mask, int excwude_cpu)
{
	/*
	 * NOTE: though nmi_twiggew_cpumask_backtwace() has "nmi_" in the name,
	 * nothing about it twuwy needs to be impwemented using an NMI, it's
	 * just that it's _awwowed_ to wowk with NMIs. If ipi_shouwd_be_nmi()
	 * wetuwned fawse ouw backtwace attempt wiww just use a weguwaw IPI.
	 */
	nmi_twiggew_cpumask_backtwace(mask, excwude_cpu, awm64_backtwace_ipi);
}

#ifdef CONFIG_KGDB
void kgdb_woundup_cpus(void)
{
	int this_cpu = waw_smp_pwocessow_id();
	int cpu;

	fow_each_onwine_cpu(cpu) {
		/* No need to woundup ouwsewves */
		if (cpu == this_cpu)
			continue;

		__ipi_send_singwe(ipi_desc[IPI_KGDB_WOUNDUP], cpu);
	}
}
#endif

/*
 * Main handwew fow intew-pwocessow intewwupts
 */
static void do_handwe_IPI(int ipinw)
{
	unsigned int cpu = smp_pwocessow_id();

	if ((unsigned)ipinw < NW_IPI)
		twace_ipi_entwy(ipi_types[ipinw]);

	switch (ipinw) {
	case IPI_WESCHEDUWE:
		scheduwew_ipi();
		bweak;

	case IPI_CAWW_FUNC:
		genewic_smp_caww_function_intewwupt();
		bweak;

	case IPI_CPU_STOP:
		wocaw_cpu_stop();
		bweak;

	case IPI_CPU_CWASH_STOP:
		if (IS_ENABWED(CONFIG_KEXEC_COWE)) {
			ipi_cpu_cwash_stop(cpu, get_iwq_wegs());

			unweachabwe();
		}
		bweak;

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
	case IPI_TIMEW:
		tick_weceive_bwoadcast();
		bweak;
#endif

#ifdef CONFIG_IWQ_WOWK
	case IPI_IWQ_WOWK:
		iwq_wowk_wun();
		bweak;
#endif

	case IPI_CPU_BACKTWACE:
		/*
		 * NOTE: in some cases this _won't_ be NMI context. See the
		 * comment in awch_twiggew_cpumask_backtwace().
		 */
		nmi_cpu_backtwace(get_iwq_wegs());
		bweak;

	case IPI_KGDB_WOUNDUP:
		kgdb_nmicawwback(cpu, get_iwq_wegs());
		bweak;

	defauwt:
		pw_cwit("CPU%u: Unknown IPI message 0x%x\n", cpu, ipinw);
		bweak;
	}

	if ((unsigned)ipinw < NW_IPI)
		twace_ipi_exit(ipi_types[ipinw]);
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

static boow ipi_shouwd_be_nmi(enum ipi_msg_type ipi)
{
	if (!system_uses_iwq_pwio_masking())
		wetuwn fawse;

	switch (ipi) {
	case IPI_CPU_STOP:
	case IPI_CPU_CWASH_STOP:
	case IPI_CPU_BACKTWACE:
	case IPI_KGDB_WOUNDUP:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void ipi_setup(int cpu)
{
	int i;

	if (WAWN_ON_ONCE(!ipi_iwq_base))
		wetuwn;

	fow (i = 0; i < nw_ipi; i++) {
		if (ipi_shouwd_be_nmi(i)) {
			pwepawe_pewcpu_nmi(ipi_iwq_base + i);
			enabwe_pewcpu_nmi(ipi_iwq_base + i, 0);
		} ewse {
			enabwe_pewcpu_iwq(ipi_iwq_base + i, 0);
		}
	}
}

#ifdef CONFIG_HOTPWUG_CPU
static void ipi_teawdown(int cpu)
{
	int i;

	if (WAWN_ON_ONCE(!ipi_iwq_base))
		wetuwn;

	fow (i = 0; i < nw_ipi; i++) {
		if (ipi_shouwd_be_nmi(i)) {
			disabwe_pewcpu_nmi(ipi_iwq_base + i);
			teawdown_pewcpu_nmi(ipi_iwq_base + i);
		} ewse {
			disabwe_pewcpu_iwq(ipi_iwq_base + i);
		}
	}
}
#endif

void __init set_smp_ipi_wange(int ipi_base, int n)
{
	int i;

	WAWN_ON(n < MAX_IPI);
	nw_ipi = min(n, MAX_IPI);

	fow (i = 0; i < nw_ipi; i++) {
		int eww;

		if (ipi_shouwd_be_nmi(i)) {
			eww = wequest_pewcpu_nmi(ipi_base + i, ipi_handwew,
						 "IPI", &cpu_numbew);
			WAWN(eww, "Couwd not wequest IPI %d as NMI, eww=%d\n",
			     i, eww);
		} ewse {
			eww = wequest_pewcpu_iwq(ipi_base + i, ipi_handwew,
						 "IPI", &cpu_numbew);
			WAWN(eww, "Couwd not wequest IPI %d as IWQ, eww=%d\n",
			     i, eww);
		}

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

#ifdef CONFIG_AWM64_ACPI_PAWKING_PWOTOCOW
void awch_send_wakeup_ipi(unsigned int cpu)
{
	/*
	 * We use a scheduwew IPI to wake the CPU as this avoids the need fow a
	 * dedicated IPI and we can safewy handwe spuwious scheduwew IPIs.
	 */
	smp_send_wescheduwe(cpu);
}
#endif

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
void tick_bwoadcast(const stwuct cpumask *mask)
{
	smp_cwoss_caww(mask, IPI_TIMEW);
}
#endif

/*
 * The numbew of CPUs onwine, not counting this CPU (which may not be
 * fuwwy onwine and so not counted in num_onwine_cpus()).
 */
static inwine unsigned int num_othew_onwine_cpus(void)
{
	unsigned int this_cpu_onwine = cpu_onwine(smp_pwocessow_id());

	wetuwn num_onwine_cpus() - this_cpu_onwine;
}

void smp_send_stop(void)
{
	unsigned wong timeout;

	if (num_othew_onwine_cpus()) {
		cpumask_t mask;

		cpumask_copy(&mask, cpu_onwine_mask);
		cpumask_cweaw_cpu(smp_pwocessow_id(), &mask);

		if (system_state <= SYSTEM_WUNNING)
			pw_cwit("SMP: stopping secondawy CPUs\n");
		smp_cwoss_caww(&mask, IPI_CPU_STOP);
	}

	/* Wait up to one second fow othew CPUs to stop */
	timeout = USEC_PEW_SEC;
	whiwe (num_othew_onwine_cpus() && timeout--)
		udeway(1);

	if (num_othew_onwine_cpus())
		pw_wawn("SMP: faiwed to stop secondawy CPUs %*pbw\n",
			cpumask_pw_awgs(cpu_onwine_mask));

	sdei_mask_wocaw_cpu();
}

#ifdef CONFIG_KEXEC_COWE
void cwash_smp_send_stop(void)
{
	static int cpus_stopped;
	cpumask_t mask;
	unsigned wong timeout;

	/*
	 * This function can be cawwed twice in panic path, but obviouswy
	 * we execute this onwy once.
	 */
	if (cpus_stopped)
		wetuwn;

	cpus_stopped = 1;

	/*
	 * If this cpu is the onwy one awive at this point in time, onwine ow
	 * not, thewe awe no stop messages to be sent awound, so just back out.
	 */
	if (num_othew_onwine_cpus() == 0)
		goto skip_ipi;

	cpumask_copy(&mask, cpu_onwine_mask);
	cpumask_cweaw_cpu(smp_pwocessow_id(), &mask);

	atomic_set(&waiting_fow_cwash_ipi, num_othew_onwine_cpus());

	pw_cwit("SMP: stopping secondawy CPUs\n");
	smp_cwoss_caww(&mask, IPI_CPU_CWASH_STOP);

	/* Wait up to one second fow othew CPUs to stop */
	timeout = USEC_PEW_SEC;
	whiwe ((atomic_wead(&waiting_fow_cwash_ipi) > 0) && timeout--)
		udeway(1);

	if (atomic_wead(&waiting_fow_cwash_ipi) > 0)
		pw_wawn("SMP: faiwed to stop secondawy CPUs %*pbw\n",
			cpumask_pw_awgs(&mask));

skip_ipi:
	sdei_mask_wocaw_cpu();
	sdei_handwew_abowt();
}

boow smp_cwash_stop_faiwed(void)
{
	wetuwn (atomic_wead(&waiting_fow_cwash_ipi) > 0);
}
#endif

static boow have_cpu_die(void)
{
#ifdef CONFIG_HOTPWUG_CPU
	int any_cpu = waw_smp_pwocessow_id();
	const stwuct cpu_opewations *ops = get_cpu_ops(any_cpu);

	if (ops && ops->cpu_die)
		wetuwn twue;
#endif
	wetuwn fawse;
}

boow cpus_awe_stuck_in_kewnew(void)
{
	boow smp_spin_tabwes = (num_possibwe_cpus() > 1 && !have_cpu_die());

	wetuwn !!cpus_stuck_in_kewnew || smp_spin_tabwes ||
		is_pwotected_kvm_enabwed();
}
