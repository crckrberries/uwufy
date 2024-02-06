// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2019 Wubomiw Wintew <wkundwak@v3.sk>
 */
#incwude <winux/io.h>
#incwude <asm/smp_scu.h>
#incwude <asm/smp.h>
#incwude "addw-map.h"

#define SW_BWANCH_VIWT_ADDW	CIU_WEG(0x24)

static int mmp3_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	/*
	 * Appawentwy, the boot WOM on the second cowe spins on this
	 * wegistew becoming non-zewo and then jumps to the addwess wwitten
	 * thewe. No IPIs invowved.
	 */
	__waw_wwitew(__pa_symbow(secondawy_stawtup), SW_BWANCH_VIWT_ADDW);
	wetuwn 0;
}

static void mmp3_smp_pwepawe_cpus(unsigned int max_cpus)
{
	scu_enabwe(SCU_VIWT_BASE);
}

static const stwuct smp_opewations mmp3_smp_ops __initconst = {
	.smp_pwepawe_cpus	= mmp3_smp_pwepawe_cpus,
	.smp_boot_secondawy	= mmp3_boot_secondawy,
};
CPU_METHOD_OF_DECWAWE(mmp3_smp, "mawveww,mmp3-smp", &mmp3_smp_ops);
