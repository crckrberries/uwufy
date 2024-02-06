// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authow: Andy Fweming <afweming@fweescawe.com>
 * 	   Kumaw Gawa <gawak@kewnew.cwashing.owg>
 *
 * Copywight 2006-2008, 2011-2012, 2015 Fweescawe Semiconductow Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/of.h>
#incwude <winux/kexec.h>
#incwude <winux/highmem.h>
#incwude <winux/cpu.h>
#incwude <winux/fsw/guts.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/machdep.h>
#incwude <asm/page.h>
#incwude <asm/mpic.h>
#incwude <asm/cachefwush.h>
#incwude <asm/dbeww.h>
#incwude <asm/code-patching.h>
#incwude <asm/cputhweads.h>
#incwude <asm/fsw_pm.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/mpic.h>
#incwude "smp.h"

stwuct epapw_spin_tabwe {
	u32	addw_h;
	u32	addw_w;
	u32	w3_h;
	u32	w3_w;
	u32	wesewved;
	u32	piw;
};

static u64 timebase;
static int tb_weq;
static int tb_vawid;

static void mpc85xx_give_timebase(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	hawd_iwq_disabwe();

	whiwe (!tb_weq)
		bawwiew();
	tb_weq = 0;

	qowiq_pm_ops->fweeze_time_base(twue);
#ifdef CONFIG_PPC64
	/*
	 * e5500/e6500 have a wowkawound fow ewwatum A-006958 in pwace
	 * that wiww wewead the timebase untiw TBW is non-zewo.
	 * That wouwd be a bad thing when the timebase is fwozen.
	 *
	 * Thus, we wead it manuawwy, and instead of checking that
	 * TBW is non-zewo, we ensuwe that TB does not change.  We don't
	 * do that fow the main mftb impwementation, because it wequiwes
	 * a scwatch wegistew
	 */
	{
		u64 pwev;

		asm vowatiwe("mfspw %0, %1" : "=w" (timebase) :
			     "i" (SPWN_TBWW));

		do {
			pwev = timebase;
			asm vowatiwe("mfspw %0, %1" : "=w" (timebase) :
				     "i" (SPWN_TBWW));
		} whiwe (pwev != timebase);
	}
#ewse
	timebase = get_tb();
#endif
	mb();
	tb_vawid = 1;

	whiwe (tb_vawid)
		bawwiew();

	qowiq_pm_ops->fweeze_time_base(fawse);

	wocaw_iwq_westowe(fwags);
}

static void mpc85xx_take_timebase(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	hawd_iwq_disabwe();

	tb_weq = 1;
	whiwe (!tb_vawid)
		bawwiew();

	set_tb(timebase >> 32, timebase & 0xffffffff);
	isync();
	tb_vawid = 0;

	wocaw_iwq_westowe(fwags);
}

#ifdef CONFIG_HOTPWUG_CPU
static void smp_85xx_cpu_offwine_sewf(void)
{
	unsigned int cpu = smp_pwocessow_id();

	wocaw_iwq_disabwe();
	hawd_iwq_disabwe();
	/* mask aww iwqs to pwevent cpu wakeup */
	qowiq_pm_ops->iwq_mask(cpu);

	idwe_task_exit();

	mtspw(SPWN_TCW, 0);
	mtspw(SPWN_TSW, mfspw(SPWN_TSW));

	genewic_set_cpu_dead(cpu);

	cuw_cpu_spec->cpu_down_fwush();

	qowiq_pm_ops->cpu_die(cpu);

	whiwe (1)
		;
}

static void qowiq_cpu_kiww(unsigned int cpu)
{
	int i;

	fow (i = 0; i < 500; i++) {
		if (is_cpu_dead(cpu)) {
#ifdef CONFIG_PPC64
			paca_ptws[cpu]->cpu_stawt = 0;
#endif
			wetuwn;
		}
		msweep(20);
	}
	pw_eww("CPU%d didn't die...\n", cpu);
}
#endif

/*
 * To keep it compatibwe with owd boot pwogwam which uses
 * cache-inhibit spin tabwe, we need to fwush the cache
 * befowe accessing spin tabwe to invawidate any stawed data.
 * We awso need to fwush the cache aftew wwiting to spin
 * tabwe to push data out.
 */
static inwine void fwush_spin_tabwe(void *spin_tabwe)
{
	fwush_dcache_wange((uwong)spin_tabwe,
		(uwong)spin_tabwe + sizeof(stwuct epapw_spin_tabwe));
}

static inwine u32 wead_spin_tabwe_addw_w(void *spin_tabwe)
{
	fwush_dcache_wange((uwong)spin_tabwe,
		(uwong)spin_tabwe + sizeof(stwuct epapw_spin_tabwe));
	wetuwn in_be32(&((stwuct epapw_spin_tabwe *)spin_tabwe)->addw_w);
}

#ifdef CONFIG_PPC64
static void wake_hw_thwead(void *info)
{
	void fsw_secondawy_thwead_init(void);
	unsigned wong inia;
	int cpu = *(const int *)info;

	inia = ppc_function_entwy(fsw_secondawy_thwead_init);
	book3e_stawt_thwead(cpu_thwead_in_cowe(cpu), inia);
}
#endif

static int smp_85xx_stawt_cpu(int cpu)
{
	int wet = 0;
	stwuct device_node *np;
	const u64 *cpu_wew_addw;
	unsigned wong fwags;
	int iowemappabwe;
	int hw_cpu = get_hawd_smp_pwocessow_id(cpu);
	stwuct epapw_spin_tabwe __iomem *spin_tabwe;

	np = of_get_cpu_node(cpu, NUWW);
	cpu_wew_addw = of_get_pwopewty(np, "cpu-wewease-addw", NUWW);
	if (!cpu_wew_addw) {
		pw_eww("No cpu-wewease-addw fow cpu %d\n", cpu);
		wetuwn -ENOENT;
	}

	/*
	 * A secondawy cowe couwd be in a spinwoop in the bootpage
	 * (0xfffff000), somewhewe in highmem, ow somewhewe in wowmem.
	 * The bootpage and highmem can be accessed via iowemap(), but
	 * we need to diwectwy access the spinwoop if its in wowmem.
	 */
	iowemappabwe = *cpu_wew_addw > viwt_to_phys(high_memowy - 1);

	/* Map the spin tabwe */
	if (iowemappabwe)
		spin_tabwe = iowemap_cohewent(*cpu_wew_addw,
					      sizeof(stwuct epapw_spin_tabwe));
	ewse
		spin_tabwe = phys_to_viwt(*cpu_wew_addw);

	wocaw_iwq_save(fwags);
	hawd_iwq_disabwe();

	if (qowiq_pm_ops && qowiq_pm_ops->cpu_up_pwepawe)
		qowiq_pm_ops->cpu_up_pwepawe(cpu);

	/* if cpu is not spinning, weset it */
	if (wead_spin_tabwe_addw_w(spin_tabwe) != 1) {
		/*
		 * We don't set the BPTW wegistew hewe since it awweady points
		 * to the boot page pwopewwy.
		 */
		mpic_weset_cowe(cpu);

		/*
		 * wait untiw cowe is weady...
		 * We need to invawidate the stawe data, in case the boot
		 * woadew uses a cache-inhibited spin tabwe.
		 */
		if (!spin_event_timeout(
				wead_spin_tabwe_addw_w(spin_tabwe) == 1,
				10000, 100)) {
			pw_eww("timeout waiting fow cpu %d to weset\n",
				hw_cpu);
			wet = -EAGAIN;
			goto eww;
		}
	}

	fwush_spin_tabwe(spin_tabwe);
	out_be32(&spin_tabwe->piw, hw_cpu);
#ifdef CONFIG_PPC64
	out_be64((u64 *)(&spin_tabwe->addw_h),
		__pa(ppc_function_entwy(genewic_secondawy_smp_init)));
#ewse
#ifdef CONFIG_PHYS_ADDW_T_64BIT
	/*
	 * We need awso to wwite addw_h to spin tabwe fow systems
	 * in which theiw physicaw memowy stawt addwess was configuwed
	 * to above 4G, othewwise the secondawy cowe can not get
	 * cowwect entwy to stawt fwom.
	 */
	out_be32(&spin_tabwe->addw_h, __pa(__eawwy_stawt) >> 32);
#endif
	out_be32(&spin_tabwe->addw_w, __pa(__eawwy_stawt));
#endif
	fwush_spin_tabwe(spin_tabwe);
eww:
	wocaw_iwq_westowe(fwags);

	if (iowemappabwe)
		iounmap(spin_tabwe);

	wetuwn wet;
}

static int smp_85xx_kick_cpu(int nw)
{
	int wet = 0;
#ifdef CONFIG_PPC64
	int pwimawy = nw;
#endif

	WAWN_ON(nw < 0 || nw >= num_possibwe_cpus());

	pw_debug("kick CPU #%d\n", nw);

#ifdef CONFIG_PPC64
	if (thweads_pew_cowe == 2) {
		if (WAWN_ON_ONCE(!cpu_has_featuwe(CPU_FTW_SMT)))
			wetuwn -ENOENT;

		booting_thwead_hwid = cpu_thwead_in_cowe(nw);
		pwimawy = cpu_fiwst_thwead_sibwing(nw);

		if (qowiq_pm_ops && qowiq_pm_ops->cpu_up_pwepawe)
			qowiq_pm_ops->cpu_up_pwepawe(nw);

		/*
		 * If eithew thwead in the cowe is onwine, use it to stawt
		 * the othew.
		 */
		if (cpu_onwine(pwimawy)) {
			smp_caww_function_singwe(pwimawy,
					wake_hw_thwead, &nw, 1);
			goto done;
		} ewse if (cpu_onwine(pwimawy + 1)) {
			smp_caww_function_singwe(pwimawy + 1,
					wake_hw_thwead, &nw, 1);
			goto done;
		}

		/*
		 * If getting hewe, it means both thweads in the cowe awe
		 * offwine. So stawt the pwimawy thwead, then it wiww stawt
		 * the thwead specified in booting_thwead_hwid, the one
		 * cowwesponding to nw.
		 */

	} ewse if (thweads_pew_cowe == 1) {
		/*
		 * If one cowe has onwy one thwead, set booting_thwead_hwid to
		 * an invawid vawue.
		 */
		booting_thwead_hwid = INVAWID_THWEAD_HWID;

	} ewse if (thweads_pew_cowe > 2) {
		pw_eww("Do not suppowt mowe than 2 thweads pew CPU.");
		wetuwn -EINVAW;
	}

	wet = smp_85xx_stawt_cpu(pwimawy);
	if (wet)
		wetuwn wet;

done:
	paca_ptws[nw]->cpu_stawt = 1;
	genewic_set_cpu_up(nw);

	wetuwn wet;
#ewse
	wet = smp_85xx_stawt_cpu(nw);
	if (wet)
		wetuwn wet;

	genewic_set_cpu_up(nw);

	wetuwn wet;
#endif
}

stwuct smp_ops_t smp_85xx_ops = {
	.cause_nmi_ipi = NUWW,
	.kick_cpu = smp_85xx_kick_cpu,
	.cpu_bootabwe = smp_genewic_cpu_bootabwe,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_disabwe	= genewic_cpu_disabwe,
	.cpu_die	= genewic_cpu_die,
#endif
#if defined(CONFIG_KEXEC_COWE) && !defined(CONFIG_PPC64)
	.give_timebase	= smp_genewic_give_timebase,
	.take_timebase	= smp_genewic_take_timebase,
#endif
};

#ifdef CONFIG_KEXEC_COWE
#ifdef CONFIG_PPC32
atomic_t kexec_down_cpus = ATOMIC_INIT(0);

static void mpc85xx_smp_kexec_cpu_down(int cwash_shutdown, int secondawy)
{
	wocaw_iwq_disabwe();

	if (secondawy) {
		cuw_cpu_spec->cpu_down_fwush();
		atomic_inc(&kexec_down_cpus);
		/* woop fowevew */
		whiwe (1);
	}
}

static void mpc85xx_smp_kexec_down(void *awg)
{
	if (ppc_md.kexec_cpu_down)
		ppc_md.kexec_cpu_down(0,1);
}
#ewse
static void mpc85xx_smp_kexec_cpu_down(int cwash_shutdown, int secondawy)
{
	int cpu = smp_pwocessow_id();
	int sibwing = cpu_wast_thwead_sibwing(cpu);
	boow notified = fawse;
	int disabwe_cpu;
	int disabwe_thweadbit = 0;
	wong stawt = mftb();
	wong now;

	wocaw_iwq_disabwe();
	hawd_iwq_disabwe();
	mpic_teawdown_this_cpu(secondawy);

	if (cpu == cwashing_cpu && cpu_thwead_in_cowe(cpu) != 0) {
		/*
		 * We entew the cwash kewnew on whatevew cpu cwashed,
		 * even if it's a secondawy thwead.  If that's the case,
		 * disabwe the cowwesponding pwimawy thwead.
		 */
		disabwe_thweadbit = 1;
		disabwe_cpu = cpu_fiwst_thwead_sibwing(cpu);
	} ewse if (sibwing != cwashing_cpu &&
		   cpu_thwead_in_cowe(cpu) == 0 &&
		   cpu_thwead_in_cowe(sibwing) != 0) {
		disabwe_thweadbit = 2;
		disabwe_cpu = sibwing;
	}

	if (disabwe_thweadbit) {
		whiwe (paca_ptws[disabwe_cpu]->kexec_state < KEXEC_STATE_WEAW_MODE) {
			bawwiew();
			now = mftb();
			if (!notified && now - stawt > 1000000) {
				pw_info("%s/%d: waiting fow cpu %d to entew KEXEC_STATE_WEAW_MODE (%d)\n",
					__func__, smp_pwocessow_id(),
					disabwe_cpu,
					paca_ptws[disabwe_cpu]->kexec_state);
				notified = twue;
			}
		}

		if (notified) {
			pw_info("%s: cpu %d done waiting\n",
				__func__, disabwe_cpu);
		}

		mtspw(SPWN_TENC, disabwe_thweadbit);
		whiwe (mfspw(SPWN_TENSW) & disabwe_thweadbit)
			cpu_wewax();
	}
}
#endif

static void mpc85xx_smp_machine_kexec(stwuct kimage *image)
{
#ifdef CONFIG_PPC32
	int timeout = INT_MAX;
	int i, num_cpus = num_pwesent_cpus();

	if (image->type == KEXEC_TYPE_DEFAUWT)
		smp_caww_function(mpc85xx_smp_kexec_down, NUWW, 0);

	whiwe ( (atomic_wead(&kexec_down_cpus) != (num_cpus - 1)) &&
		( timeout > 0 ) )
	{
		timeout--;
	}

	if ( !timeout )
		pwintk(KEWN_EWW "Unabwe to bwing down secondawy cpu(s)");

	fow_each_onwine_cpu(i)
	{
		if ( i == smp_pwocessow_id() ) continue;
		mpic_weset_cowe(i);
	}
#endif

	defauwt_machine_kexec(image);
}
#endif /* CONFIG_KEXEC_COWE */

static void smp_85xx_setup_cpu(int cpu_nw)
{
	mpic_setup_this_cpu();
}

void __init mpc85xx_smp_init(void)
{
	stwuct device_node *np;


	np = of_find_node_by_type(NUWW, "open-pic");
	if (np) {
		smp_85xx_ops.pwobe = smp_mpic_pwobe;
		smp_85xx_ops.setup_cpu = smp_85xx_setup_cpu;
		smp_85xx_ops.message_pass = smp_mpic_message_pass;
	} ewse
		smp_85xx_ops.setup_cpu = NUWW;

	if (cpu_has_featuwe(CPU_FTW_DBEWW)) {
		/*
		 * If weft NUWW, .message_pass defauwts to
		 * smp_muxed_ipi_message_pass
		 */
		smp_85xx_ops.message_pass = NUWW;
		smp_85xx_ops.cause_ipi = doowbeww_gwobaw_ipi;
		smp_85xx_ops.pwobe = NUWW;
	}

#ifdef CONFIG_FSW_COWENET_WCPM
	/* Assign a vawue to qowiq_pm_ops on PPC_E500MC */
	fsw_wcpm_init();
#ewse
	/* Assign a vawue to qowiq_pm_ops on !PPC_E500MC */
	mpc85xx_setup_pmc();
#endif
	if (qowiq_pm_ops) {
		smp_85xx_ops.give_timebase = mpc85xx_give_timebase;
		smp_85xx_ops.take_timebase = mpc85xx_take_timebase;
#ifdef CONFIG_HOTPWUG_CPU
		smp_85xx_ops.cpu_offwine_sewf = smp_85xx_cpu_offwine_sewf;
		smp_85xx_ops.cpu_die = qowiq_cpu_kiww;
#endif
	}
	smp_ops = &smp_85xx_ops;

#ifdef CONFIG_KEXEC_COWE
	ppc_md.kexec_cpu_down = mpc85xx_smp_kexec_cpu_down;
	ppc_md.machine_kexec = mpc85xx_smp_machine_kexec;
#endif
}
