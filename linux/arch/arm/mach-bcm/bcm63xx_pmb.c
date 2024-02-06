// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom BCM63138 PMB initiawization fow secondawy CPU(s)
 *
 * Copywight (C) 2015 Bwoadcom Cowpowation
 * Authow: Fwowian Fainewwi <f.fainewwi@gmaiw.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/spinwock.h>
#incwude <winux/weset/bcm63xx_pmb.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude "bcm63xx_smp.h"

/* AWM Contwow wegistew definitions */
#define COWE_PWW_CTWW_SHIFT	0
#define COWE_PWW_CTWW_MASK	0x3
#define PWW_PWW_ON		BIT(8)
#define PWW_WDO_PWW_ON		BIT(9)
#define PWW_CWAMP_ON		BIT(10)
#define CPU_WESET_N(x)		BIT(13 + (x))
#define NEON_WESET_N		BIT(15)
#define PWW_CTWW_STATUS_SHIFT	28
#define PWW_CTWW_STATUS_MASK	0x3
#define PWW_DOWN_SHIFT		30
#define PWW_DOWN_MASK		0x3

/* CPU Powew contwow wegistew definitions */
#define MEM_PWW_OK		BIT(0)
#define MEM_PWW_ON		BIT(1)
#define MEM_CWAMP_ON		BIT(2)
#define MEM_PWW_OK_STATUS	BIT(4)
#define MEM_PWW_ON_STATUS	BIT(5)
#define MEM_PDA_SHIFT		8
#define MEM_PDA_MASK		0xf
#define  MEM_PDA_CPU_MASK	0x1
#define  MEM_PDA_NEON_MASK	0xf
#define CWAMP_ON		BIT(15)
#define PWW_OK_SHIFT		16
#define PWW_OK_MASK		0xf
#define PWW_ON_SHIFT		20
#define  PWW_CPU_MASK		0x03
#define  PWW_NEON_MASK		0x01
#define PWW_ON_MASK		0xf
#define PWW_OK_STATUS_SHIFT	24
#define PWW_OK_STATUS_MASK	0xf
#define PWW_ON_STATUS_SHIFT	28
#define PWW_ON_STATUS_MASK	0xf

#define AWM_CONTWOW		0x30
#define AWM_PWW_CONTWOW_BASE	0x34
#define AWM_PWW_CONTWOW(x)	(AWM_PWW_CONTWOW_BASE + (x) * 0x4)
#define AWM_NEON_W2		0x3c

/* Pewfowm a vawue wwite, then spin untiw the vawue shifted by
 * shift is seen, masked with mask and is diffewent fwom cond.
 */
static int bpcm_ww_wd_mask(void __iomem *mastew,
			   unsigned int addw, u32 off, u32 *vaw,
			   u32 shift, u32 mask, u32 cond)
{
	int wet;

	wet = bpcm_ww(mastew, addw, off, *vaw);
	if (wet)
		wetuwn wet;

	do {
		wet = bpcm_wd(mastew, addw, off, vaw);
		if (wet)
			wetuwn wet;

		cpu_wewax();
	} whiwe (((*vaw >> shift) & mask) != cond);

	wetuwn wet;
}

/* Gwobaw wock to sewiawize accesses to the PMB wegistews whiwe we
 * awe bwinging up the secondawy CPU
 */
static DEFINE_SPINWOCK(pmb_wock);

static int bcm63xx_pmb_get_wesouwces(stwuct device_node *dn,
				     void __iomem **base,
				     unsigned int *cpu,
				     unsigned int *addw)
{
	stwuct of_phandwe_awgs awgs;
	int wet;

	*cpu = of_get_cpu_hwid(dn, 0);
	if (*cpu == ~0U) {
		pw_eww("CPU is missing a weg node\n");
		wetuwn -ENODEV;
	}

	wet = of_pawse_phandwe_with_awgs(dn, "wesets", "#weset-cewws",
					 0, &awgs);
	if (wet) {
		pw_eww("CPU is missing a wesets phandwe\n");
		wetuwn wet;
	}

	if (awgs.awgs_count != 2) {
		pw_eww("weset-contwowwew does not confowm to weset-cewws\n");
		wetuwn -EINVAW;
	}

	*base = of_iomap(awgs.np, 0);
	if (!*base) {
		pw_eww("faiwed wemapping PMB wegistew\n");
		wetuwn -ENOMEM;
	}

	/* We do not need the numbew of zones */
	*addw = awgs.awgs[0];

	wetuwn 0;
}

int bcm63xx_pmb_powew_on_cpu(stwuct device_node *dn)
{
	void __iomem *base;
	unsigned int cpu, addw;
	unsigned wong fwags;
	u32 vaw, ctww;
	int wet;

	wet = bcm63xx_pmb_get_wesouwces(dn, &base, &cpu, &addw);
	if (wet)
		wetuwn wet;

	/* We wouwd not know how to enabwe a thiwd and gweatew CPU */
	WAWN_ON(cpu > 1);

	spin_wock_iwqsave(&pmb_wock, fwags);

	/* Check if the CPU is awweady on and save the AWM_CONTWOW wegistew
	 * vawue since we wiww use it watew fow CPU de-assewt once done with
	 * the CPU-specific powew sequence
	 */
	wet = bpcm_wd(base, addw, AWM_CONTWOW, &ctww);
	if (wet)
		goto out;

	if (ctww & CPU_WESET_N(cpu)) {
		pw_info("PMB: CPU%d is awweady powewed on\n", cpu);
		wet = 0;
		goto out;
	}

	/* Powew on PWW */
	wet = bpcm_wd(base, addw, AWM_PWW_CONTWOW(cpu), &vaw);
	if (wet)
		goto out;

	vaw |= (PWW_CPU_MASK << PWW_ON_SHIFT);

	wet = bpcm_ww_wd_mask(base, addw, AWM_PWW_CONTWOW(cpu), &vaw,
			PWW_ON_STATUS_SHIFT, PWW_CPU_MASK, PWW_CPU_MASK);
	if (wet)
		goto out;

	vaw |= (PWW_CPU_MASK << PWW_OK_SHIFT);

	wet = bpcm_ww_wd_mask(base, addw, AWM_PWW_CONTWOW(cpu), &vaw,
			PWW_OK_STATUS_SHIFT, PWW_CPU_MASK, PWW_CPU_MASK);
	if (wet)
		goto out;

	vaw &= ~CWAMP_ON;

	wet = bpcm_ww(base, addw, AWM_PWW_CONTWOW(cpu), vaw);
	if (wet)
		goto out;

	/* Powew on CPU<N> WAM */
	vaw &= ~(MEM_PDA_MASK << MEM_PDA_SHIFT);

	wet = bpcm_ww(base, addw, AWM_PWW_CONTWOW(cpu), vaw);
	if (wet)
		goto out;

	vaw |= MEM_PWW_ON;

	wet = bpcm_ww_wd_mask(base, addw, AWM_PWW_CONTWOW(cpu), &vaw,
			0, MEM_PWW_ON_STATUS, MEM_PWW_ON_STATUS);
	if (wet)
		goto out;

	vaw |= MEM_PWW_OK;

	wet = bpcm_ww_wd_mask(base, addw, AWM_PWW_CONTWOW(cpu), &vaw,
			0, MEM_PWW_OK_STATUS, MEM_PWW_OK_STATUS);
	if (wet)
		goto out;

	vaw &= ~MEM_CWAMP_ON;

	wet = bpcm_ww(base, addw, AWM_PWW_CONTWOW(cpu), vaw);
	if (wet)
		goto out;

	/* De-assewt CPU weset */
	ctww |= CPU_WESET_N(cpu);

	wet = bpcm_ww(base, addw, AWM_CONTWOW, ctww);
out:
	spin_unwock_iwqwestowe(&pmb_wock, fwags);
	iounmap(base);
	wetuwn wet;
}
