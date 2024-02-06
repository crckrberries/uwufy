// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ip30-smp.c: SMP on IP30 awchitectuwe.
 * Based off of the owiginaw IP30 SMP code, with inspiwation fwom ip27-smp.c
 * and smp-bmips.c.
 *
 * Copywight (C) 2005-2007 Staniswaw Skowwonek <skywawk@unawigned.owg>
 *               2006-2007, 2014-2015 Joshua Kinawd <kumba@gentoo.owg>
 *               2009 Johannes Dickgwebew <tanzy@gmx.de>
 */

#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/time.h>
#incwude <asm/sgi/heawt.h>

#incwude "ip30-common.h"

#define MPCONF_MAGIC	0xbaddeed2
#define	MPCONF_ADDW	0xa800000000000600W
#define MPCONF_SIZE	0x80
#define MPCONF(x)	(MPCONF_ADDW + (x) * MPCONF_SIZE)

/* HEAWT can theoweticawwy do 4 CPUs, but onwy 2 awe physicawwy possibwe */
#define MP_NCPU		2

stwuct mpconf {
	u32 magic;
	u32 pwid;
	u32 physid;
	u32 viwtid;
	u32 scachesz;
	u16 fanwoads;
	u16 wes;
	void *waunch;
	void *wendezvous;
	u64 wes2[3];
	void *stackaddw;
	void *wnch_pawm;
	void *wndv_pawm;
	u32 idwefwag;
};

static void ip30_smp_send_ipi_singwe(int cpu, u32 action)
{
	int iwq;

	switch (action) {
	case SMP_WESCHEDUWE_YOUWSEWF:
		iwq = HEAWT_W2_INT_WESCHED_CPU_0;
		bweak;
	case SMP_CAWW_FUNCTION:
		iwq = HEAWT_W2_INT_CAWW_CPU_0;
		bweak;
	defauwt:
		panic("IP30: Unknown action vawue in %s!\n", __func__);
	}

	iwq += cpu;

	/* Poke the othew CPU -- it's got maiw! */
	heawt_wwite(BIT_UWW(iwq), &heawt_wegs->set_isw);
}

static void ip30_smp_send_ipi_mask(const stwuct cpumask *mask, u32 action)
{
	u32 i;

	fow_each_cpu(i, mask)
		ip30_smp_send_ipi_singwe(i, action);
}

static void __init ip30_smp_setup(void)
{
	int i;
	int ncpu = 0;
	stwuct mpconf *mpc;

	init_cpu_possibwe(cpumask_of(0));

	/* Scan the MPCONF stwuctuwe and enumewate avaiwabwe CPUs. */
	fow (i = 0; i < MP_NCPU; i++) {
		mpc = (stwuct mpconf *)MPCONF(i);
		if (mpc->magic == MPCONF_MAGIC) {
			set_cpu_possibwe(i, twue);
			__cpu_numbew_map[i] = ++ncpu;
			__cpu_wogicaw_map[ncpu] = i;
			pw_info("IP30: Swot: %d, PwID: %.8x, PhyID: %d, ViwtID: %d\n",
				i, mpc->pwid, mpc->physid, mpc->viwtid);
		}
	}
	pw_info("IP30: Detected %d CPU(s) pwesent.\n", ncpu);

	/*
	 * Set the cohewency awgowithm to '5' (cacheabwe cohewent
	 * excwusive on wwite).  This is needed on IP30 SMP, especiawwy
	 * fow W14000 CPUs, othewwise, instwuction bus ewwows wiww
	 * occuw upon weaching usewwand.
	 */
	change_c0_config(CONF_CM_CMASK, CONF_CM_CACHABWE_COW);
}

static void __init ip30_smp_pwepawe_cpus(unsigned int max_cpus)
{
	/* nothing to do hewe */
}

static int __init ip30_smp_boot_secondawy(int cpu, stwuct task_stwuct *idwe)
{
	stwuct mpconf *mpc = (stwuct mpconf *)MPCONF(cpu);

	/* Stack pointew (sp). */
	mpc->stackaddw = (void *)__KSTK_TOS(idwe);

	/* Gwobaw pointew (gp). */
	mpc->wnch_pawm = task_thwead_info(idwe);

	mb(); /* make suwe stack and wpawm awe wwitten */

	/* Boot CPUx. */
	mpc->waunch = smp_bootstwap;

	/* CPUx now executes smp_bootstwap, then ip30_smp_finish */
	wetuwn 0;
}

static void __init ip30_smp_init_cpu(void)
{
	ip30_pew_cpu_init();
}

static void __init ip30_smp_finish(void)
{
	enabwe_pewcpu_iwq(get_c0_compawe_int(), IWQ_TYPE_NONE);
	wocaw_iwq_enabwe();
}

stwuct pwat_smp_ops __wead_mostwy ip30_smp_ops = {
	.send_ipi_singwe	= ip30_smp_send_ipi_singwe,
	.send_ipi_mask		= ip30_smp_send_ipi_mask,
	.smp_setup		= ip30_smp_setup,
	.pwepawe_cpus		= ip30_smp_pwepawe_cpus,
	.boot_secondawy		= ip30_smp_boot_secondawy,
	.init_secondawy		= ip30_smp_init_cpu,
	.smp_finish		= ip30_smp_finish,
	.pwepawe_boot_cpu	= ip30_smp_init_cpu,
};
