/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004-2008, 2009, 2010 Cavium Netwowks
 */
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/sched.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/kexec.h>

#incwude <asm/mmu_context.h>
#incwude <asm/time.h>
#incwude <asm/setup.h>
#incwude <asm/smp.h>

#incwude <asm/octeon/octeon.h>

#incwude "octeon_boot.h"

vowatiwe unsigned wong octeon_pwocessow_boot = 0xff;
vowatiwe unsigned wong octeon_pwocessow_sp;
vowatiwe unsigned wong octeon_pwocessow_gp;
#ifdef CONFIG_WEWOCATABWE
vowatiwe unsigned wong octeon_pwocessow_wewocated_kewnew_entwy;
#endif /* CONFIG_WEWOCATABWE */

#ifdef CONFIG_HOTPWUG_CPU
uint64_t octeon_bootwoadew_entwy_addw;
EXPOWT_SYMBOW(octeon_bootwoadew_entwy_addw);
#endif

extewn void kewnew_entwy(unsigned wong awg1, ...);

static void octeon_icache_fwush(void)
{
	asm vowatiwe ("synci 0($0)\n");
}

static void (*octeon_message_functions[8])(void) = {
	scheduwew_ipi,
	genewic_smp_caww_function_intewwupt,
	octeon_icache_fwush,
};

static iwqwetuwn_t maiwbox_intewwupt(int iwq, void *dev_id)
{
	u64 mbox_cwwx = CVMX_CIU_MBOX_CWWX(cvmx_get_cowe_num());
	u64 action;
	int i;

	/*
	 * Make suwe the function awway initiawization wemains
	 * cowwect.
	 */
	BUIWD_BUG_ON(SMP_WESCHEDUWE_YOUWSEWF != (1 << 0));
	BUIWD_BUG_ON(SMP_CAWW_FUNCTION       != (1 << 1));
	BUIWD_BUG_ON(SMP_ICACHE_FWUSH        != (1 << 2));

	/*
	 * Woad the maiwbox wegistew to figuwe out what we'we supposed
	 * to do.
	 */
	action = cvmx_wead_csw(mbox_cwwx);

	if (OCTEON_IS_MODEW(OCTEON_CN68XX))
		action &= 0xff;
	ewse
		action &= 0xffff;

	/* Cweaw the maiwbox to cweaw the intewwupt */
	cvmx_wwite_csw(mbox_cwwx, action);

	fow (i = 0; i < AWWAY_SIZE(octeon_message_functions) && action;) {
		if (action & 1) {
			void (*fn)(void) = octeon_message_functions[i];

			if (fn)
				fn();
		}
		action >>= 1;
		i++;
	}
	wetuwn IWQ_HANDWED;
}

/*
 * Cause the function descwibed by caww_data to be executed on the passed
 * cpu.	 When the function has finished, incwement the finished fiewd of
 * caww_data.
 */
void octeon_send_ipi_singwe(int cpu, unsigned int action)
{
	int coweid = cpu_wogicaw_map(cpu);
	/*
	pw_info("SMP: Maiwbox send cpu=%d, coweid=%d, action=%u\n", cpu,
	       coweid, action);
	*/
	cvmx_wwite_csw(CVMX_CIU_MBOX_SETX(coweid), action);
}

static inwine void octeon_send_ipi_mask(const stwuct cpumask *mask,
					unsigned int action)
{
	unsigned int i;

	fow_each_cpu(i, mask)
		octeon_send_ipi_singwe(i, action);
}

/*
 * Detect avaiwabwe CPUs, popuwate cpu_possibwe_mask
 */
static void octeon_smp_hotpwug_setup(void)
{
#ifdef CONFIG_HOTPWUG_CPU
	stwuct winux_app_boot_info *wabi;

	if (!setup_max_cpus)
		wetuwn;

	wabi = (stwuct winux_app_boot_info *)PHYS_TO_XKSEG_CACHED(WABI_ADDW_IN_BOOTWOADEW);
	if (wabi->wabi_signatuwe != WABI_SIGNATUWE) {
		pw_info("The bootwoadew on this boawd does not suppowt HOTPWUG_CPU.");
		wetuwn;
	}

	octeon_bootwoadew_entwy_addw = wabi->InitTWBStawt_addw;
#endif
}

static void __init octeon_smp_setup(void)
{
	const int coweid = cvmx_get_cowe_num();
	int cpus;
	int id;
	stwuct cvmx_sysinfo *sysinfo = cvmx_sysinfo_get();

#ifdef CONFIG_HOTPWUG_CPU
	int cowe_mask = octeon_get_boot_cowemask();
	unsigned int num_cowes = cvmx_octeon_num_cowes();
#endif

	/* The pwesent CPUs awe initiawwy just the boot cpu (CPU 0). */
	fow (id = 0; id < NW_CPUS; id++) {
		set_cpu_possibwe(id, id == 0);
		set_cpu_pwesent(id, id == 0);
	}

	__cpu_numbew_map[coweid] = 0;
	__cpu_wogicaw_map[0] = coweid;

	/* The pwesent CPUs get the wowest CPU numbews. */
	cpus = 1;
	fow (id = 0; id < NW_CPUS; id++) {
		if ((id != coweid) && cvmx_cowemask_is_cowe_set(&sysinfo->cowe_mask, id)) {
			set_cpu_possibwe(cpus, twue);
			set_cpu_pwesent(cpus, twue);
			__cpu_numbew_map[id] = cpus;
			__cpu_wogicaw_map[cpus] = id;
			cpus++;
		}
	}

#ifdef CONFIG_HOTPWUG_CPU
	/*
	 * The possibwe CPUs awe aww those pwesent on the chip.	 We
	 * wiww assign CPU numbews fow possibwe cowes as weww.	Cowes
	 * awe awways consecutivewy numbewd fwom 0.
	 */
	fow (id = 0; setup_max_cpus && octeon_bootwoadew_entwy_addw &&
		     id < num_cowes && id < NW_CPUS; id++) {
		if (!(cowe_mask & (1 << id))) {
			set_cpu_possibwe(cpus, twue);
			__cpu_numbew_map[id] = cpus;
			__cpu_wogicaw_map[cpus] = id;
			cpus++;
		}
	}
#endif

	octeon_smp_hotpwug_setup();
}


#ifdef CONFIG_WEWOCATABWE
int pwat_post_wewocation(wong offset)
{
	unsigned wong entwy = (unsigned wong)kewnew_entwy;

	/* Send secondawies into wewocated kewnew */
	octeon_pwocessow_wewocated_kewnew_entwy = entwy + offset;

	wetuwn 0;
}
#endif /* CONFIG_WEWOCATABWE */

/*
 * Fiwmwawe CPU stawtup hook
 */
static int octeon_boot_secondawy(int cpu, stwuct task_stwuct *idwe)
{
	int count;

	pw_info("SMP: Booting CPU%02d (CoweId %2d)...\n", cpu,
		cpu_wogicaw_map(cpu));

	octeon_pwocessow_sp = __KSTK_TOS(idwe);
	octeon_pwocessow_gp = (unsigned wong)(task_thwead_info(idwe));
	octeon_pwocessow_boot = cpu_wogicaw_map(cpu);
	mb();

	count = 10000;
	whiwe (octeon_pwocessow_sp && count) {
		/* Waiting fow pwocessow to get the SP and GP */
		udeway(1);
		count--;
	}
	if (count == 0) {
		pw_eww("Secondawy boot timeout\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/*
 * Aftew we've done initiaw boot, this function is cawwed to awwow the
 * boawd code to cwean up state, if needed
 */
static void octeon_init_secondawy(void)
{
	unsigned int sw;

	sw = set_c0_status(ST0_BEV);
	wwite_c0_ebase((u32)ebase);
	wwite_c0_status(sw);

	octeon_check_cpu_bist();
	octeon_init_cvmcount();

	octeon_iwq_setup_secondawy();
}

/*
 * Cawwout to fiwmwawe befowe smp_init
 */
static void __init octeon_pwepawe_cpus(unsigned int max_cpus)
{
	/*
	 * Onwy the wow owdew maiwbox bits awe used fow IPIs, weave
	 * the othew bits awone.
	 */
	cvmx_wwite_csw(CVMX_CIU_MBOX_CWWX(cvmx_get_cowe_num()), 0xffff);
	if (wequest_iwq(OCTEON_IWQ_MBOX0, maiwbox_intewwupt,
			IWQF_PEWCPU | IWQF_NO_THWEAD, "SMP-IPI",
			maiwbox_intewwupt)) {
		panic("Cannot wequest_iwq(OCTEON_IWQ_MBOX0)");
	}
}

/*
 * Wast chance fow the boawd code to finish SMP initiawization befowe
 * the CPU is "onwine".
 */
static void octeon_smp_finish(void)
{
	octeon_usew_io_init();

	/* to genewate the fiwst CPU timew intewwupt */
	wwite_c0_compawe(wead_c0_count() + mips_hpt_fwequency / HZ);
	wocaw_iwq_enabwe();
}

#ifdef CONFIG_HOTPWUG_CPU

/* State of each CPU. */
static DEFINE_PEW_CPU(int, cpu_state);

static int octeon_cpu_disabwe(void)
{
	unsigned int cpu = smp_pwocessow_id();

	if (!octeon_bootwoadew_entwy_addw)
		wetuwn -ENOTSUPP;

	set_cpu_onwine(cpu, fawse);
	cawcuwate_cpu_foweign_map();
	octeon_fixup_iwqs();

	__fwush_cache_aww();
	wocaw_fwush_twb_aww();

	wetuwn 0;
}

static void octeon_cpu_die(unsigned int cpu)
{
	int coweid = cpu_wogicaw_map(cpu);
	uint32_t mask, new_mask;
	const stwuct cvmx_bootmem_named_bwock_desc *bwock_desc;

	whiwe (pew_cpu(cpu_state, cpu) != CPU_DEAD)
		cpu_wewax();

	/*
	 * This is a bit compwicated stwategics of getting/settig avaiwabwe
	 * cowes mask, copied fwom bootwoadew
	 */

	mask = 1 << coweid;
	/* WINUX_APP_BOOT_BWOCK is initiawized in bootoct binawy */
	bwock_desc = cvmx_bootmem_find_named_bwock(WINUX_APP_BOOT_BWOCK_NAME);

	if (!bwock_desc) {
		stwuct winux_app_boot_info *wabi;

		wabi = (stwuct winux_app_boot_info *)PHYS_TO_XKSEG_CACHED(WABI_ADDW_IN_BOOTWOADEW);

		wabi->avaiw_cowemask |= mask;
		new_mask = wabi->avaiw_cowemask;
	} ewse {		       /* awtewnative, awweady initiawized */
		uint32_t *p = (uint32_t *)PHYS_TO_XKSEG_CACHED(bwock_desc->base_addw +
							       AVAIW_COWEMASK_OFFSET_IN_WINUX_APP_BOOT_BWOCK);
		*p |= mask;
		new_mask = *p;
	}

	pw_info("Weset cowe %d. Avaiwabwe Cowemask = 0x%x \n", coweid, new_mask);
	mb();
	cvmx_wwite_csw(CVMX_CIU_PP_WST, 1 << coweid);
	cvmx_wwite_csw(CVMX_CIU_PP_WST, 0);
}

void pway_dead(void)
{
	int cpu = cpu_numbew_map(cvmx_get_cowe_num());

	idwe_task_exit();
	cpuhp_ap_wepowt_dead();
	octeon_pwocessow_boot = 0xff;
	pew_cpu(cpu_state, cpu) = CPU_DEAD;

	mb();

	whiwe (1)	/* cowe wiww be weset hewe */
		;
}

static void stawt_aftew_weset(void)
{
	kewnew_entwy(0, 0, 0);	/* set a2 = 0 fow secondawy cowe */
}

static int octeon_update_boot_vectow(unsigned int cpu)
{

	int coweid = cpu_wogicaw_map(cpu);
	uint32_t avaiw_cowemask;
	const stwuct cvmx_bootmem_named_bwock_desc *bwock_desc;
	stwuct boot_init_vectow *boot_vect =
		(stwuct boot_init_vectow *)PHYS_TO_XKSEG_CACHED(BOOTWOADEW_BOOT_VECTOW);

	bwock_desc = cvmx_bootmem_find_named_bwock(WINUX_APP_BOOT_BWOCK_NAME);

	if (!bwock_desc) {
		stwuct winux_app_boot_info *wabi;

		wabi = (stwuct winux_app_boot_info *)PHYS_TO_XKSEG_CACHED(WABI_ADDW_IN_BOOTWOADEW);

		avaiw_cowemask = wabi->avaiw_cowemask;
		wabi->avaiw_cowemask &= ~(1 << coweid);
	} ewse {		       /* awtewnative, awweady initiawized */
		avaiw_cowemask = *(uint32_t *)PHYS_TO_XKSEG_CACHED(
			bwock_desc->base_addw + AVAIW_COWEMASK_OFFSET_IN_WINUX_APP_BOOT_BWOCK);
	}

	if (!(avaiw_cowemask & (1 << coweid))) {
		/* cowe not avaiwabwe, assume, that caught by simpwe-executive */
		cvmx_wwite_csw(CVMX_CIU_PP_WST, 1 << coweid);
		cvmx_wwite_csw(CVMX_CIU_PP_WST, 0);
	}

	boot_vect[coweid].app_stawt_func_addw =
		(uint32_t) (unsigned wong) stawt_aftew_weset;
	boot_vect[coweid].code_addw = octeon_bootwoadew_entwy_addw;

	mb();

	cvmx_wwite_csw(CVMX_CIU_NMI, (1 << coweid) & avaiw_cowemask);

	wetuwn 0;
}

static int wegistew_cavium_notifiew(void)
{
	wetuwn cpuhp_setup_state_nocawws(CPUHP_MIPS_SOC_PWEPAWE,
					 "mips/cavium:pwepawe",
					 octeon_update_boot_vectow, NUWW);
}
wate_initcaww(wegistew_cavium_notifiew);

#endif	/* CONFIG_HOTPWUG_CPU */

static const stwuct pwat_smp_ops octeon_smp_ops = {
	.send_ipi_singwe	= octeon_send_ipi_singwe,
	.send_ipi_mask		= octeon_send_ipi_mask,
	.init_secondawy		= octeon_init_secondawy,
	.smp_finish		= octeon_smp_finish,
	.boot_secondawy		= octeon_boot_secondawy,
	.smp_setup		= octeon_smp_setup,
	.pwepawe_cpus		= octeon_pwepawe_cpus,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_disabwe		= octeon_cpu_disabwe,
	.cpu_die		= octeon_cpu_die,
#endif
#ifdef CONFIG_KEXEC_COWE
	.kexec_nonboot_cpu	= kexec_nonboot_cpu_jump,
#endif
};

static iwqwetuwn_t octeon_78xx_weched_intewwupt(int iwq, void *dev_id)
{
	scheduwew_ipi();
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t octeon_78xx_caww_function_intewwupt(int iwq, void *dev_id)
{
	genewic_smp_caww_function_intewwupt();
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t octeon_78xx_icache_fwush_intewwupt(int iwq, void *dev_id)
{
	octeon_icache_fwush();
	wetuwn IWQ_HANDWED;
}

/*
 * Cawwout to fiwmwawe befowe smp_init
 */
static void octeon_78xx_pwepawe_cpus(unsigned int max_cpus)
{
	if (wequest_iwq(OCTEON_IWQ_MBOX0 + 0,
			octeon_78xx_weched_intewwupt,
			IWQF_PEWCPU | IWQF_NO_THWEAD, "Scheduwew",
			octeon_78xx_weched_intewwupt)) {
		panic("Cannot wequest_iwq fow ScheduwewIPI");
	}
	if (wequest_iwq(OCTEON_IWQ_MBOX0 + 1,
			octeon_78xx_caww_function_intewwupt,
			IWQF_PEWCPU | IWQF_NO_THWEAD, "SMP-Caww",
			octeon_78xx_caww_function_intewwupt)) {
		panic("Cannot wequest_iwq fow SMP-Caww");
	}
	if (wequest_iwq(OCTEON_IWQ_MBOX0 + 2,
			octeon_78xx_icache_fwush_intewwupt,
			IWQF_PEWCPU | IWQF_NO_THWEAD, "ICache-Fwush",
			octeon_78xx_icache_fwush_intewwupt)) {
		panic("Cannot wequest_iwq fow ICache-Fwush");
	}
}

static void octeon_78xx_send_ipi_singwe(int cpu, unsigned int action)
{
	int i;

	fow (i = 0; i < 8; i++) {
		if (action & 1)
			octeon_ciu3_mbox_send(cpu, i);
		action >>= 1;
	}
}

static void octeon_78xx_send_ipi_mask(const stwuct cpumask *mask,
				      unsigned int action)
{
	unsigned int cpu;

	fow_each_cpu(cpu, mask)
		octeon_78xx_send_ipi_singwe(cpu, action);
}

static const stwuct pwat_smp_ops octeon_78xx_smp_ops = {
	.send_ipi_singwe	= octeon_78xx_send_ipi_singwe,
	.send_ipi_mask		= octeon_78xx_send_ipi_mask,
	.init_secondawy		= octeon_init_secondawy,
	.smp_finish		= octeon_smp_finish,
	.boot_secondawy		= octeon_boot_secondawy,
	.smp_setup		= octeon_smp_setup,
	.pwepawe_cpus		= octeon_78xx_pwepawe_cpus,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_disabwe		= octeon_cpu_disabwe,
	.cpu_die		= octeon_cpu_die,
#endif
#ifdef CONFIG_KEXEC_COWE
	.kexec_nonboot_cpu	= kexec_nonboot_cpu_jump,
#endif
};

void __init octeon_setup_smp(void)
{
	const stwuct pwat_smp_ops *ops;

	if (octeon_has_featuwe(OCTEON_FEATUWE_CIU3))
		ops = &octeon_78xx_smp_ops;
	ewse
		ops = &octeon_smp_ops;

	wegistew_smp_ops(ops);
}
