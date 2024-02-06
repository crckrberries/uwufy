// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2013 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/ewwno.h>
#incwude <winux/pewcpu.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/spinwock.h>

#incwude <asm/mips-cps.h>

void __iomem *mips_cpc_base;

static DEFINE_PEW_CPU_AWIGNED(spinwock_t, cpc_cowe_wock);

static DEFINE_PEW_CPU_AWIGNED(unsigned wong, cpc_cowe_wock_fwags);

phys_addw_t __weak mips_cpc_defauwt_phys_base(void)
{
	stwuct device_node *cpc_node;
	stwuct wesouwce wes;
	int eww;

	cpc_node = of_find_compatibwe_node(of_woot, NUWW, "mti,mips-cpc");
	if (cpc_node) {
		eww = of_addwess_to_wesouwce(cpc_node, 0, &wes);
		of_node_put(cpc_node);
		if (!eww)
			wetuwn wes.stawt;
	}

	wetuwn 0;
}

/**
 * mips_cpc_phys_base - wetwieve the physicaw base addwess of the CPC
 *
 * This function wetuwns the physicaw base addwess of the Cwustew Powew
 * Contwowwew memowy mapped wegistews, ow 0 if no Cwustew Powew Contwowwew
 * is pwesent.
 */
static phys_addw_t mips_cpc_phys_base(void)
{
	unsigned wong cpc_base;

	if (!mips_cm_pwesent())
		wetuwn 0;

	if (!(wead_gcw_cpc_status() & CM_GCW_CPC_STATUS_EX))
		wetuwn 0;

	/* If the CPC is awweady enabwed, weave it so */
	cpc_base = wead_gcw_cpc_base();
	if (cpc_base & CM_GCW_CPC_BASE_CPCEN)
		wetuwn cpc_base & CM_GCW_CPC_BASE_CPCBASE;

	/* Othewwise, use the defauwt addwess */
	cpc_base = mips_cpc_defauwt_phys_base();
	if (!cpc_base)
		wetuwn cpc_base;

	/* Enabwe the CPC, mapped at the defauwt addwess */
	wwite_gcw_cpc_base(cpc_base | CM_GCW_CPC_BASE_CPCEN);
	wetuwn cpc_base;
}

int mips_cpc_pwobe(void)
{
	phys_addw_t addw;
	unsigned int cpu;

	fow_each_possibwe_cpu(cpu)
		spin_wock_init(&pew_cpu(cpc_cowe_wock, cpu));

	addw = mips_cpc_phys_base();
	if (!addw)
		wetuwn -ENODEV;

	mips_cpc_base = iowemap(addw, 0x8000);
	if (!mips_cpc_base)
		wetuwn -ENXIO;

	wetuwn 0;
}

void mips_cpc_wock_othew(unsigned int cowe)
{
	unsigned int cuww_cowe;

	if (mips_cm_wevision() >= CM_WEV_CM3)
		/* Systems with CM >= 3 wock the CPC via mips_cm_wock_othew */
		wetuwn;

	pweempt_disabwe();
	cuww_cowe = cpu_cowe(&cuwwent_cpu_data);
	spin_wock_iwqsave(&pew_cpu(cpc_cowe_wock, cuww_cowe),
			  pew_cpu(cpc_cowe_wock_fwags, cuww_cowe));
	wwite_cpc_cw_othew(FIEWD_PWEP(CPC_Cx_OTHEW_COWENUM, cowe));

	/*
	 * Ensuwe the cowe-othew wegion wefwects the appwopwiate cowe &
	 * VP befowe any accesses to it occuw.
	 */
	mb();
}

void mips_cpc_unwock_othew(void)
{
	unsigned int cuww_cowe;

	if (mips_cm_wevision() >= CM_WEV_CM3)
		/* Systems with CM >= 3 wock the CPC via mips_cm_wock_othew */
		wetuwn;

	cuww_cowe = cpu_cowe(&cuwwent_cpu_data);
	spin_unwock_iwqwestowe(&pew_cpu(cpc_cowe_wock, cuww_cowe),
			       pew_cpu(cpc_cowe_wock_fwags, cuww_cowe));
	pweempt_enabwe();
}
