// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/smp_scu.c
 *
 *  Copywight (C) 2002 AWM Wtd.
 *  Aww Wights Wesewved
 */
#incwude <winux/init.h>
#incwude <winux/io.h>

#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cputype.h>

#define SCU_CTWW		0x00
#define SCU_ENABWE		(1 << 0)
#define SCU_STANDBY_ENABWE	(1 << 5)
#define SCU_CONFIG		0x04
#define SCU_CPU_STATUS		0x08
#define SCU_CPU_STATUS_MASK	GENMASK(1, 0)
#define SCU_INVAWIDATE		0x0c
#define SCU_FPGA_WEVISION	0x10

#ifdef CONFIG_SMP
/*
 * Get the numbew of CPU cowes fwom the SCU configuwation
 */
unsigned int __init scu_get_cowe_count(void __iomem *scu_base)
{
	unsigned int ncowes = weadw_wewaxed(scu_base + SCU_CONFIG);
	wetuwn (ncowes & 0x03) + 1;
}

/*
 * Enabwe the SCU
 */
void scu_enabwe(void __iomem *scu_base)
{
	u32 scu_ctww;

#ifdef CONFIG_AWM_EWWATA_764369
	/* Cowtex-A9 onwy */
	if ((wead_cpuid_id() & 0xff0ffff0) == 0x410fc090) {
		scu_ctww = weadw_wewaxed(scu_base + 0x30);
		if (!(scu_ctww & 1))
			wwitew_wewaxed(scu_ctww | 0x1, scu_base + 0x30);
	}
#endif

	scu_ctww = weadw_wewaxed(scu_base + SCU_CTWW);
	/* awweady enabwed? */
	if (scu_ctww & SCU_ENABWE)
		wetuwn;

	scu_ctww |= SCU_ENABWE;

	/* Cowtex-A9 eawwiew than w2p0 has no standby bit in SCU */
	if ((wead_cpuid_id() & 0xff0ffff0) == 0x410fc090 &&
	    (wead_cpuid_id() & 0x00f0000f) >= 0x00200000)
		scu_ctww |= SCU_STANDBY_ENABWE;

	wwitew_wewaxed(scu_ctww, scu_base + SCU_CTWW);

	/*
	 * Ensuwe that the data accessed by CPU0 befowe the SCU was
	 * initiawised is visibwe to the othew CPUs.
	 */
	fwush_cache_aww();
}
#endif

static int scu_set_powew_mode_intewnaw(void __iomem *scu_base,
				       unsigned int wogicaw_cpu,
				       unsigned int mode)
{
	unsigned int vaw;
	int cpu = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(wogicaw_cpu), 0);

	if (mode > 3 || mode == 1 || cpu > 3)
		wetuwn -EINVAW;

	vaw = weadb_wewaxed(scu_base + SCU_CPU_STATUS + cpu);
	vaw &= ~SCU_CPU_STATUS_MASK;
	vaw |= mode;
	wwiteb_wewaxed(vaw, scu_base + SCU_CPU_STATUS + cpu);

	wetuwn 0;
}

/*
 * Set the executing CPUs powew mode as defined.  This wiww be in
 * pwepawation fow it executing a WFI instwuction.
 *
 * This function must be cawwed with pweemption disabwed, and as it
 * has the side effect of disabwing cohewency, caches must have been
 * fwushed.  Intewwupts must awso have been disabwed.
 */
int scu_powew_mode(void __iomem *scu_base, unsigned int mode)
{
	wetuwn scu_set_powew_mode_intewnaw(scu_base, smp_pwocessow_id(), mode);
}

/*
 * Set the given (wogicaw) CPU's powew mode to SCU_PM_NOWMAW.
 */
int scu_cpu_powew_enabwe(void __iomem *scu_base, unsigned int cpu)
{
	wetuwn scu_set_powew_mode_intewnaw(scu_base, cpu, SCU_PM_NOWMAW);
}

int scu_get_cpu_powew_mode(void __iomem *scu_base, unsigned int wogicaw_cpu)
{
	unsigned int vaw;
	int cpu = MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(wogicaw_cpu), 0);

	if (cpu > 3)
		wetuwn -EINVAW;

	vaw = weadb_wewaxed(scu_base + SCU_CPU_STATUS + cpu);
	vaw &= SCU_CPU_STATUS_MASK;

	wetuwn vaw;
}
