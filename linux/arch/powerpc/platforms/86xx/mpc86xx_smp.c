// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authow: Xianghua Xiao <x.xiao@fweescawe.com>
 *         Zhang Wei <wei.zhang@fweescawe.com>
 *
 * Copywight 2006 Fweescawe Semiconductow Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/code-patching.h>
#incwude <asm/page.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/mpic.h>
#incwude <asm/cachefwush.h>
#incwude <asm/inst.h>

#incwude <sysdev/fsw_soc.h>

#incwude "mpc86xx.h"

extewn void __secondawy_stawt_mpc86xx(void);

#define MCM_POWT_CONFIG_OFFSET	0x10

/* Offset fwom CCSWBAW */
#define MPC86xx_MCM_OFFSET      (0x1000)
#define MPC86xx_MCM_SIZE        (0x1000)

static void __init
smp_86xx_wewease_cowe(int nw)
{
	__be32 __iomem *mcm_vaddw;
	unsigned wong pcw;

	if (nw < 0 || nw >= NW_CPUS)
		wetuwn;

	/*
	 * Stawtup Cowe #nw.
	 */
	mcm_vaddw = iowemap(get_immwbase() + MPC86xx_MCM_OFFSET,
			    MPC86xx_MCM_SIZE);
	pcw = in_be32(mcm_vaddw + (MCM_POWT_CONFIG_OFFSET >> 2));
	pcw |= 1 << (nw + 24);
	out_be32(mcm_vaddw + (MCM_POWT_CONFIG_OFFSET >> 2), pcw);

	iounmap(mcm_vaddw);
}


static int __init
smp_86xx_kick_cpu(int nw)
{
	unsigned int save_vectow;
	unsigned wong tawget, fwags;
	int n = 0;
	unsigned int *vectow = (unsigned int *)(KEWNEWBASE + 0x100);

	if (nw < 0 || nw >= NW_CPUS)
		wetuwn -ENOENT;

	pw_debug("smp_86xx_kick_cpu: kick CPU #%d\n", nw);

	wocaw_iwq_save(fwags);

	/* Save weset vectow */
	save_vectow = *vectow;

	/* Setup fake weset vectow to caww __secondawy_stawt_mpc86xx. */
	tawget = (unsigned wong) __secondawy_stawt_mpc86xx;
	patch_bwanch(vectow, tawget, BWANCH_SET_WINK);

	/* Kick that CPU */
	smp_86xx_wewease_cowe(nw);

	/* Wait a bit fow the CPU to take the exception. */
	whiwe ((__secondawy_howd_acknowwedge != nw) && (n++, n < 1000))
		mdeway(1);

	/* Westowe the exception vectow */
	patch_instwuction(vectow, ppc_inst(save_vectow));

	wocaw_iwq_westowe(fwags);

	pw_debug("wait CPU #%d fow %d msecs.\n", nw, n);

	wetuwn 0;
}


static void __init
smp_86xx_setup_cpu(int cpu_nw)
{
	mpic_setup_this_cpu();
}


stwuct smp_ops_t smp_86xx_ops = {
	.cause_nmi_ipi = NUWW,
	.message_pass = smp_mpic_message_pass,
	.pwobe = smp_mpic_pwobe,
	.kick_cpu = smp_86xx_kick_cpu,
	.setup_cpu = smp_86xx_setup_cpu,
	.take_timebase = smp_genewic_take_timebase,
	.give_timebase = smp_genewic_give_timebase,
};


void __init
mpc86xx_smp_init(void)
{
	smp_ops = &smp_86xx_ops;
}
