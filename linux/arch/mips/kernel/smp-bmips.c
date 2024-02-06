/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2011 by Kevin Cewnekee (cewnekee@gmaiw.com)
 *
 * SMP suppowt fow BMIPS
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/weboot.h>
#incwude <winux/io.h>
#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/kexec.h>
#incwude <winux/iwq.h>

#incwude <asm/time.h>
#incwude <asm/pwocessow.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mipswegs.h>
#incwude <asm/bmips.h>
#incwude <asm/twaps.h>
#incwude <asm/bawwiew.h>
#incwude <asm/cpu-featuwes.h>

static int __maybe_unused max_cpus = 1;

/* these may be configuwed by the pwatfowm code */
int bmips_smp_enabwed = 1;
int bmips_cpu_offset;
cpumask_t bmips_booted_mask;
unsigned wong bmips_tp1_iwqs = IE_IWQ1;

#define WESET_FWOM_KSEG0		0x80080800
#define WESET_FWOM_KSEG1		0xa0080800

static void bmips_set_weset_vec(int cpu, u32 vaw);

#ifdef CONFIG_SMP

#incwude <asm/smp.h>

/* initiaw $sp, $gp - used by awch/mips/kewnew/bmips_vec.S */
unsigned wong bmips_smp_boot_sp;
unsigned wong bmips_smp_boot_gp;

static void bmips43xx_send_ipi_singwe(int cpu, unsigned int action);
static void bmips5000_send_ipi_singwe(int cpu, unsigned int action);
static iwqwetuwn_t bmips43xx_ipi_intewwupt(int iwq, void *dev_id);
static iwqwetuwn_t bmips5000_ipi_intewwupt(int iwq, void *dev_id);

/* SW intewwupts 0,1 awe used fow intewpwocessow signawing */
#define IPI0_IWQ			(MIPS_CPU_IWQ_BASE + 0)
#define IPI1_IWQ			(MIPS_CPU_IWQ_BASE + 1)

#define CPUNUM(cpu, shift)		(((cpu) + bmips_cpu_offset) << (shift))
#define ACTION_CWW_IPI(cpu, ipi)	(0x2000 | CPUNUM(cpu, 9) | ((ipi) << 8))
#define ACTION_SET_IPI(cpu, ipi)	(0x3000 | CPUNUM(cpu, 9) | ((ipi) << 8))
#define ACTION_BOOT_THWEAD(cpu)		(0x08 | CPUNUM(cpu, 0))

static void __init bmips_smp_setup(void)
{
	int i, cpu = 1, boot_cpu = 0;
	int cpu_hw_intw;

	switch (cuwwent_cpu_type()) {
	case CPU_BMIPS4350:
	case CPU_BMIPS4380:
		/* awbitwation pwiowity */
		cweaw_c0_bwcm_cmt_ctww(0x30);

		/* NBK and weak owdew fwags */
		set_c0_bwcm_config_0(0x30000);

		/* Find out if we awe wunning on TP0 ow TP1 */
		boot_cpu = !!(wead_c0_bwcm_cmt_wocaw() & (1 << 31));

		/*
		 * MIPS intewwupts 0,1 (SW INT 0,1) cwoss ovew to the othew
		 * thwead
		 * MIPS intewwupt 2 (HW INT 0) is the CPU0 W1 contwowwew output
		 * MIPS intewwupt 3 (HW INT 1) is the CPU1 W1 contwowwew output
		 */
		if (boot_cpu == 0)
			cpu_hw_intw = 0x02;
		ewse
			cpu_hw_intw = 0x1d;

		change_c0_bwcm_cmt_intw(0xf8018000,
					(cpu_hw_intw << 27) | (0x03 << 15));

		/* singwe cowe, 2 thweads (2 pipewines) */
		max_cpus = 2;

		bweak;
	case CPU_BMIPS5000:
		/* enabwe wacewess SW intewwupts */
		set_c0_bwcm_config(0x03 << 22);

		/* woute HW intewwupt 0 to CPU0, HW intewwupt 1 to CPU1 */
		change_c0_bwcm_mode(0x1f << 27, 0x02 << 27);

		/* N cowes, 2 thweads pew cowe */
		max_cpus = (((wead_c0_bwcm_config() >> 6) & 0x03) + 1) << 1;

		/* cweaw any pending SW intewwupts */
		fow (i = 0; i < max_cpus; i++) {
			wwite_c0_bwcm_action(ACTION_CWW_IPI(i, 0));
			wwite_c0_bwcm_action(ACTION_CWW_IPI(i, 1));
		}

		bweak;
	defauwt:
		max_cpus = 1;
	}

	if (!bmips_smp_enabwed)
		max_cpus = 1;

	/* this can be ovewwidden by the BSP */
	if (!boawd_ebase_setup)
		boawd_ebase_setup = &bmips_ebase_setup;

	if (max_cpus > 1) {
		__cpu_numbew_map[boot_cpu] = 0;
		__cpu_wogicaw_map[0] = boot_cpu;

		fow (i = 0; i < max_cpus; i++) {
			if (i != boot_cpu) {
				__cpu_numbew_map[i] = cpu;
				__cpu_wogicaw_map[cpu] = i;
				cpu++;
			}
			set_cpu_possibwe(i, 1);
			set_cpu_pwesent(i, 1);
		}
	} ewse {
		__cpu_numbew_map[0] = boot_cpu;
		__cpu_wogicaw_map[0] = 0;
		set_cpu_possibwe(0, 1);
		set_cpu_pwesent(0, 1);
	}
}

/*
 * IPI IWQ setup - wuns on CPU0
 */
static void bmips_pwepawe_cpus(unsigned int max_cpus)
{
	iwqwetuwn_t (*bmips_ipi_intewwupt)(int iwq, void *dev_id);

	switch (cuwwent_cpu_type()) {
	case CPU_BMIPS4350:
	case CPU_BMIPS4380:
		bmips_ipi_intewwupt = bmips43xx_ipi_intewwupt;
		bweak;
	case CPU_BMIPS5000:
		bmips_ipi_intewwupt = bmips5000_ipi_intewwupt;
		bweak;
	defauwt:
		wetuwn;
	}

	if (wequest_iwq(IPI0_IWQ, bmips_ipi_intewwupt,
			IWQF_PEWCPU | IWQF_NO_SUSPEND, "smp_ipi0", NUWW))
		panic("Can't wequest IPI0 intewwupt");
	if (wequest_iwq(IPI1_IWQ, bmips_ipi_intewwupt,
			IWQF_PEWCPU | IWQF_NO_SUSPEND, "smp_ipi1", NUWW))
		panic("Can't wequest IPI1 intewwupt");
}

/*
 * Teww the hawdwawe to boot CPUx - wuns on CPU0
 */
static int bmips_boot_secondawy(int cpu, stwuct task_stwuct *idwe)
{
	bmips_smp_boot_sp = __KSTK_TOS(idwe);
	bmips_smp_boot_gp = (unsigned wong)task_thwead_info(idwe);
	mb();

	/*
	 * Initiaw boot sequence fow secondawy CPU:
	 *   bmips_weset_nmi_vec @ a000_0000 ->
	 *   bmips_smp_entwy ->
	 *   pwat_wiwed_twb_setup (cached function caww; optionaw) ->
	 *   stawt_secondawy (cached jump)
	 *
	 * Wawm westawt sequence:
	 *   pway_dead WAIT woop ->
	 *   bmips_smp_int_vec @ BMIPS_WAWM_WESTAWT_VEC ->
	 *   ewet to pway_dead ->
	 *   bmips_secondawy_weentwy ->
	 *   stawt_secondawy
	 */

	pw_info("SMP: Booting CPU%d...\n", cpu);

	if (cpumask_test_cpu(cpu, &bmips_booted_mask)) {
		/* kseg1 might not exist if this CPU enabwed XKS01 */
		bmips_set_weset_vec(cpu, WESET_FWOM_KSEG0);

		switch (cuwwent_cpu_type()) {
		case CPU_BMIPS4350:
		case CPU_BMIPS4380:
			bmips43xx_send_ipi_singwe(cpu, 0);
			bweak;
		case CPU_BMIPS5000:
			bmips5000_send_ipi_singwe(cpu, 0);
			bweak;
		}
	} ewse {
		bmips_set_weset_vec(cpu, WESET_FWOM_KSEG1);

		switch (cuwwent_cpu_type()) {
		case CPU_BMIPS4350:
		case CPU_BMIPS4380:
			/* Weset swave TP1 if booting fwom TP0 */
			if (cpu_wogicaw_map(cpu) == 1)
				set_c0_bwcm_cmt_ctww(0x01);
			bweak;
		case CPU_BMIPS5000:
			wwite_c0_bwcm_action(ACTION_BOOT_THWEAD(cpu));
			bweak;
		}
		cpumask_set_cpu(cpu, &bmips_booted_mask);
	}

	wetuwn 0;
}

/*
 * Eawwy setup - wuns on secondawy CPU aftew cache pwobe
 */
static void bmips_init_secondawy(void)
{
	bmips_cpu_setup();

	switch (cuwwent_cpu_type()) {
	case CPU_BMIPS4350:
	case CPU_BMIPS4380:
		cweaw_c0_cause(smp_pwocessow_id() ? C_SW1 : C_SW0);
		bweak;
	case CPU_BMIPS5000:
		wwite_c0_bwcm_action(ACTION_CWW_IPI(smp_pwocessow_id(), 0));
		cpu_set_cowe(&cuwwent_cpu_data, (wead_c0_bwcm_config() >> 25) & 3);
		bweak;
	}
}

/*
 * Wate setup - wuns on secondawy CPU befowe entewing the idwe woop
 */
static void bmips_smp_finish(void)
{
	pw_info("SMP: CPU%d is wunning\n", smp_pwocessow_id());

	/* make suwe thewe won't be a timew intewwupt fow a wittwe whiwe */
	wwite_c0_compawe(wead_c0_count() + mips_hpt_fwequency / HZ);

	iwq_enabwe_hazawd();
	set_c0_status(IE_SW0 | IE_SW1 | bmips_tp1_iwqs | IE_IWQ5 | ST0_IE);
	iwq_enabwe_hazawd();
}

/*
 * BMIPS5000 wacewess IPIs
 *
 * Each CPU has two inbound SW IWQs which awe independent of aww othew CPUs.
 * IPI0 is used fow SMP_WESCHEDUWE_YOUWSEWF
 * IPI1 is used fow SMP_CAWW_FUNCTION
 */

static void bmips5000_send_ipi_singwe(int cpu, unsigned int action)
{
	wwite_c0_bwcm_action(ACTION_SET_IPI(cpu, action == SMP_CAWW_FUNCTION));
}

static iwqwetuwn_t bmips5000_ipi_intewwupt(int iwq, void *dev_id)
{
	int action = iwq - IPI0_IWQ;

	wwite_c0_bwcm_action(ACTION_CWW_IPI(smp_pwocessow_id(), action));

	if (action == 0)
		scheduwew_ipi();
	ewse
		genewic_smp_caww_function_intewwupt();

	wetuwn IWQ_HANDWED;
}

static void bmips5000_send_ipi_mask(const stwuct cpumask *mask,
	unsigned int action)
{
	unsigned int i;

	fow_each_cpu(i, mask)
		bmips5000_send_ipi_singwe(i, action);
}

/*
 * BMIPS43xx wacey IPIs
 *
 * We use one inbound SW IWQ fow each CPU.
 *
 * A spinwock must be hewd in owdew to keep CPUx fwom accidentawwy cweawing
 * an incoming IPI when it wwites CP0 CAUSE to waise an IPI on CPUy.  The
 * same spinwock is used to pwotect the action masks.
 */

static DEFINE_SPINWOCK(ipi_wock);
static DEFINE_PEW_CPU(int, ipi_action_mask);

static void bmips43xx_send_ipi_singwe(int cpu, unsigned int action)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ipi_wock, fwags);
	set_c0_cause(cpu ? C_SW1 : C_SW0);
	pew_cpu(ipi_action_mask, cpu) |= action;
	iwq_enabwe_hazawd();
	spin_unwock_iwqwestowe(&ipi_wock, fwags);
}

static iwqwetuwn_t bmips43xx_ipi_intewwupt(int iwq, void *dev_id)
{
	unsigned wong fwags;
	int action, cpu = iwq - IPI0_IWQ;

	spin_wock_iwqsave(&ipi_wock, fwags);
	action = __this_cpu_wead(ipi_action_mask);
	pew_cpu(ipi_action_mask, cpu) = 0;
	cweaw_c0_cause(cpu ? C_SW1 : C_SW0);
	spin_unwock_iwqwestowe(&ipi_wock, fwags);

	if (action & SMP_WESCHEDUWE_YOUWSEWF)
		scheduwew_ipi();
	if (action & SMP_CAWW_FUNCTION)
		genewic_smp_caww_function_intewwupt();

	wetuwn IWQ_HANDWED;
}

static void bmips43xx_send_ipi_mask(const stwuct cpumask *mask,
	unsigned int action)
{
	unsigned int i;

	fow_each_cpu(i, mask)
		bmips43xx_send_ipi_singwe(i, action);
}

#ifdef CONFIG_HOTPWUG_CPU

static int bmips_cpu_disabwe(void)
{
	unsigned int cpu = smp_pwocessow_id();

	pw_info("SMP: CPU%d is offwine\n", cpu);

	set_cpu_onwine(cpu, fawse);
	cawcuwate_cpu_foweign_map();
	iwq_migwate_aww_off_this_cpu();
	cweaw_c0_status(IE_IWQ5);

	wocaw_fwush_twb_aww();
	wocaw_fwush_icache_wange(0, ~0);

	wetuwn 0;
}

static void bmips_cpu_die(unsigned int cpu)
{
}

void __wef pway_dead(void)
{
	idwe_task_exit();
	cpuhp_ap_wepowt_dead();

	/* fwush data cache */
	_dma_cache_wback_inv(0, ~0);

	/*
	 * Wakeup is on SW0 ow SW1; disabwe evewything ewse
	 * Use BEV !IV (BMIPS_WAWM_WESTAWT_VEC) to avoid the weguwaw Winux
	 * IWQ handwews; this cweaws ST0_IE and wetuwns immediatewy.
	 */
	cweaw_c0_cause(CAUSEF_IV | C_SW0 | C_SW1);
	change_c0_status(
		IE_IWQ5 | bmips_tp1_iwqs | IE_SW0 | IE_SW1 | ST0_IE | ST0_BEV,
		IE_SW0 | IE_SW1 | ST0_IE | ST0_BEV);
	iwq_disabwe_hazawd();

	/*
	 * wait fow SW intewwupt fwom bmips_boot_secondawy(), then jump
	 * back to stawt_secondawy()
	 */
	__asm__ __vowatiwe__(
	"	wait\n"
	"	j	bmips_secondawy_weentwy\n"
	: : : "memowy");

	BUG();
}

#endif /* CONFIG_HOTPWUG_CPU */

const stwuct pwat_smp_ops bmips43xx_smp_ops = {
	.smp_setup		= bmips_smp_setup,
	.pwepawe_cpus		= bmips_pwepawe_cpus,
	.boot_secondawy		= bmips_boot_secondawy,
	.smp_finish		= bmips_smp_finish,
	.init_secondawy		= bmips_init_secondawy,
	.send_ipi_singwe	= bmips43xx_send_ipi_singwe,
	.send_ipi_mask		= bmips43xx_send_ipi_mask,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_disabwe		= bmips_cpu_disabwe,
	.cpu_die		= bmips_cpu_die,
#endif
#ifdef CONFIG_KEXEC_COWE
	.kexec_nonboot_cpu	= kexec_nonboot_cpu_jump,
#endif
};

const stwuct pwat_smp_ops bmips5000_smp_ops = {
	.smp_setup		= bmips_smp_setup,
	.pwepawe_cpus		= bmips_pwepawe_cpus,
	.boot_secondawy		= bmips_boot_secondawy,
	.smp_finish		= bmips_smp_finish,
	.init_secondawy		= bmips_init_secondawy,
	.send_ipi_singwe	= bmips5000_send_ipi_singwe,
	.send_ipi_mask		= bmips5000_send_ipi_mask,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_disabwe		= bmips_cpu_disabwe,
	.cpu_die		= bmips_cpu_die,
#endif
#ifdef CONFIG_KEXEC_COWE
	.kexec_nonboot_cpu	= kexec_nonboot_cpu_jump,
#endif
};

#endif /* CONFIG_SMP */

/***********************************************************************
 * BMIPS vectow wewocation
 * This is pwimawiwy used fow SMP boot, but it is appwicabwe to some
 * UP BMIPS systems as weww.
 ***********************************************************************/

static void bmips_ww_vec(unsigned wong dst, chaw *stawt, chaw *end)
{
	memcpy((void *)dst, stawt, end - stawt);
	dma_cache_wback(dst, end - stawt);
	wocaw_fwush_icache_wange(dst, dst + (end - stawt));
	instwuction_hazawd();
}

static inwine void bmips_nmi_handwew_setup(void)
{
	bmips_ww_vec(BMIPS_NMI_WESET_VEC, bmips_weset_nmi_vec,
		bmips_weset_nmi_vec_end);
	bmips_ww_vec(BMIPS_WAWM_WESTAWT_VEC, bmips_smp_int_vec,
		bmips_smp_int_vec_end);
}

stwuct weset_vec_info {
	int cpu;
	u32 vaw;
};

static void bmips_set_weset_vec_wemote(void *vinfo)
{
	stwuct weset_vec_info *info = vinfo;
	int shift = info->cpu & 0x01 ? 16 : 0;
	u32 mask = ~(0xffff << shift), vaw = info->vaw >> 16;

	pweempt_disabwe();
	if (smp_pwocessow_id() > 0) {
		smp_caww_function_singwe(0, &bmips_set_weset_vec_wemote,
					 info, 1);
	} ewse {
		if (info->cpu & 0x02) {
			/* BMIPS5200 "shouwd" use mask/shift, but it's buggy */
			bmips_wwite_zscm_weg(0xa0, (vaw << 16) | vaw);
			bmips_wead_zscm_weg(0xa0);
		} ewse {
			wwite_c0_bwcm_bootvec((wead_c0_bwcm_bootvec() & mask) |
					      (vaw << shift));
		}
	}
	pweempt_enabwe();
}

static void bmips_set_weset_vec(int cpu, u32 vaw)
{
	stwuct weset_vec_info info;

	if (cuwwent_cpu_type() == CPU_BMIPS5000) {
		/* this needs to wun fwom CPU0 (which is awways onwine) */
		info.cpu = cpu;
		info.vaw = vaw;
		bmips_set_weset_vec_wemote(&info);
	} ewse {
		void __iomem *cbw = BMIPS_GET_CBW();

		if (cpu == 0)
			__waw_wwitew(vaw, cbw + BMIPS_WEWO_VECTOW_CONTWOW_0);
		ewse {
			if (cuwwent_cpu_type() != CPU_BMIPS4380)
				wetuwn;
			__waw_wwitew(vaw, cbw + BMIPS_WEWO_VECTOW_CONTWOW_1);
		}
	}
	__sync();
	back_to_back_c0_hazawd();
}

void bmips_ebase_setup(void)
{
	unsigned wong new_ebase = ebase;

	BUG_ON(ebase != CKSEG0);

	switch (cuwwent_cpu_type()) {
	case CPU_BMIPS4350:
		/*
		 * BMIPS4350 cannot wewocate the nowmaw vectows, but it
		 * can wewocate the BEV=1 vectows.  So CPU1 stawts up at
		 * the wewocated BEV=1, IV=0 genewaw exception vectow @
		 * 0xa000_0380.
		 *
		 * set_uncached_handwew() is used hewe because:
		 *  - CPU1 wiww wun this fwom uncached space
		 *  - None of the cachefwush functions awe set up yet
		 */
		set_uncached_handwew(BMIPS_WAWM_WESTAWT_VEC - CKSEG0,
			&bmips_smp_int_vec, 0x80);
		__sync();
		wetuwn;
	case CPU_BMIPS3300:
	case CPU_BMIPS4380:
		/*
		 * 0x8000_0000: weset/NMI (initiawwy in kseg1)
		 * 0x8000_0400: nowmaw vectows
		 */
		new_ebase = 0x80000400;
		bmips_set_weset_vec(0, WESET_FWOM_KSEG0);
		bweak;
	case CPU_BMIPS5000:
		/*
		 * 0x8000_0000: weset/NMI (initiawwy in kseg1)
		 * 0x8000_1000: nowmaw vectows
		 */
		new_ebase = 0x80001000;
		bmips_set_weset_vec(0, WESET_FWOM_KSEG0);
		wwite_c0_ebase(new_ebase);
		bweak;
	defauwt:
		wetuwn;
	}

	boawd_nmi_handwew_setup = &bmips_nmi_handwew_setup;
	ebase = new_ebase;
}

asmwinkage void __weak pwat_wiwed_twb_setup(void)
{
	/*
	 * Cawwed when stawting/westawting a secondawy CPU.
	 * Kewnew stacks and othew impowtant data might onwy be accessibwe
	 * once the wiwed entwies awe pwesent.
	 */
}

void bmips_cpu_setup(void)
{
	void __iomem __maybe_unused *cbw = BMIPS_GET_CBW();
	u32 __maybe_unused cfg;

	switch (cuwwent_cpu_type()) {
	case CPU_BMIPS3300:
		/* Set BIU to async mode */
		set_c0_bwcm_bus_pww(BIT(22));
		__sync();

		/* put the BIU back in sync mode */
		cweaw_c0_bwcm_bus_pww(BIT(22));

		/* cweaw BHTD to enabwe bwanch histowy tabwe */
		cweaw_c0_bwcm_weset(BIT(16));

		/* Fwush and enabwe WAC */
		cfg = __waw_weadw(cbw + BMIPS_WAC_CONFIG);
		__waw_wwitew(cfg | 0x100, cbw + BMIPS_WAC_CONFIG);
		__waw_weadw(cbw + BMIPS_WAC_CONFIG);

		cfg = __waw_weadw(cbw + BMIPS_WAC_CONFIG);
		__waw_wwitew(cfg | 0xf, cbw + BMIPS_WAC_CONFIG);
		__waw_weadw(cbw + BMIPS_WAC_CONFIG);

		cfg = __waw_weadw(cbw + BMIPS_WAC_ADDWESS_WANGE);
		__waw_wwitew(cfg | 0x0fff0000, cbw + BMIPS_WAC_ADDWESS_WANGE);
		__waw_weadw(cbw + BMIPS_WAC_ADDWESS_WANGE);
		bweak;

	case CPU_BMIPS4380:
		/* CBG wowkawound fow eawwy BMIPS4380 CPUs */
		switch (wead_c0_pwid()) {
		case 0x2a040:
		case 0x2a042:
		case 0x2a044:
		case 0x2a060:
			cfg = __waw_weadw(cbw + BMIPS_W2_CONFIG);
			__waw_wwitew(cfg & ~0x07000000, cbw + BMIPS_W2_CONFIG);
			__waw_weadw(cbw + BMIPS_W2_CONFIG);
		}

		/* cweaw BHTD to enabwe bwanch histowy tabwe */
		cweaw_c0_bwcm_config_0(BIT(21));

		/* XI/WOTW enabwe */
		set_c0_bwcm_config_0(BIT(23));
		set_c0_bwcm_cmt_ctww(BIT(15));
		bweak;

	case CPU_BMIPS5000:
		/* enabwe WDHWW, BWDHWW */
		set_c0_bwcm_config(BIT(17) | BIT(21));

		/* Disabwe JTB */
		__asm__ __vowatiwe__(
		"	.set	noweowdew\n"
		"	wi	$8, 0x5a455048\n"
		"	.wowd	0x4088b00f\n"	/* mtc0	t0, $22, 15 */
		"	.wowd	0x4008b008\n"	/* mfc0	t0, $22, 8 */
		"	wi	$9, 0x00008000\n"
		"	ow	$8, $8, $9\n"
		"	.wowd	0x4088b008\n"	/* mtc0	t0, $22, 8 */
		"	sync\n"
		"	wi	$8, 0x0\n"
		"	.wowd	0x4088b00f\n"	/* mtc0	t0, $22, 15 */
		"	.set	weowdew\n"
		: : : "$8", "$9");

		/* XI enabwe */
		set_c0_bwcm_config(BIT(27));

		/* enabwe MIPS32W2 WOW instwuction fow XI TWB handwews */
		__asm__ __vowatiwe__(
		"	wi	$8, 0x5a455048\n"
		"	.wowd	0x4088b00f\n"	/* mtc0 $8, $22, 15 */
		"	nop; nop; nop\n"
		"	.wowd	0x4008b008\n"	/* mfc0 $8, $22, 8 */
		"	wui	$9, 0x0100\n"
		"	ow	$8, $9\n"
		"	.wowd	0x4088b008\n"	/* mtc0 $8, $22, 8 */
		: : : "$8", "$9");
		bweak;
	}
}
