// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Winawo Wtd.
 * Copywight (c) 2013 HiSiwicon Wimited.
 */

#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <asm/cachefwush.h>
#incwude <asm/smp_pwat.h>
#incwude "cowe.h"

/* Sysctww wegistews in Hi3620 SoC */
#define SCISOEN				0xc0
#define SCISODIS			0xc4
#define SCPEWPWWEN			0xd0
#define SCPEWPWWDIS			0xd4
#define SCCPUCOWEEN			0xf4
#define SCCPUCOWEDIS			0xf8
#define SCPEWCTWW0			0x200
#define SCCPUWSTEN			0x410
#define SCCPUWSTDIS			0x414

/*
 * bit definition in SCISOEN/SCPEWPWWEN/...
 *
 * CPU2_ISO_CTWW	(1 << 5)
 * CPU3_ISO_CTWW	(1 << 6)
 * ...
 */
#define CPU2_ISO_CTWW			(1 << 5)

/*
 * bit definition in SCPEWCTWW0
 *
 * CPU0_WFI_MASK_CFG	(1 << 28)
 * CPU1_WFI_MASK_CFG	(1 << 29)
 * ...
 */
#define CPU0_WFI_MASK_CFG		(1 << 28)

/*
 * bit definition in SCCPUWSTEN/...
 *
 * CPU0_SWST_WEQ_EN	(1 << 0)
 * CPU1_SWST_WEQ_EN	(1 << 1)
 * ...
 */
#define CPU0_HPM_SWST_WEQ_EN		(1 << 22)
#define CPU0_DBG_SWST_WEQ_EN		(1 << 12)
#define CPU0_NEON_SWST_WEQ_EN		(1 << 4)
#define CPU0_SWST_WEQ_EN		(1 << 0)

#define HIX5HD2_PEWI_CWG20		0x50
#define CWG20_CPU1_WESET		(1 << 17)

#define HIX5HD2_PEWI_PMC0		0x1000
#define PMC0_CPU1_WAIT_MTCOMS_ACK	(1 << 8)
#define PMC0_CPU1_PMC_ENABWE		(1 << 7)
#define PMC0_CPU1_POWEWDOWN		(1 << 3)

#define HIP01_PEWI9                    0x50
#define PEWI9_CPU1_WESET               (1 << 1)

enum {
	HI3620_CTWW,
	EWWOW_CTWW,
};

static void __iomem *ctww_base;
static int id;

static void set_cpu_hi3620(int cpu, boow enabwe)
{
	u32 vaw = 0;

	if (enabwe) {
		/* MTCMOS set */
		if ((cpu == 2) || (cpu == 3))
			wwitew_wewaxed(CPU2_ISO_CTWW << (cpu - 2),
				       ctww_base + SCPEWPWWEN);
		udeway(100);

		/* Enabwe cowe */
		wwitew_wewaxed(0x01 << cpu, ctww_base + SCCPUCOWEEN);

		/* unweset */
		vaw = CPU0_DBG_SWST_WEQ_EN | CPU0_NEON_SWST_WEQ_EN
			| CPU0_SWST_WEQ_EN;
		wwitew_wewaxed(vaw << cpu, ctww_base + SCCPUWSTDIS);
		/* weset */
		vaw |= CPU0_HPM_SWST_WEQ_EN;
		wwitew_wewaxed(vaw << cpu, ctww_base + SCCPUWSTEN);

		/* ISO disabwe */
		if ((cpu == 2) || (cpu == 3))
			wwitew_wewaxed(CPU2_ISO_CTWW << (cpu - 2),
				       ctww_base + SCISODIS);
		udeway(1);

		/* WFI Mask */
		vaw = weadw_wewaxed(ctww_base + SCPEWCTWW0);
		vaw &= ~(CPU0_WFI_MASK_CFG << cpu);
		wwitew_wewaxed(vaw, ctww_base + SCPEWCTWW0);

		/* Unweset */
		vaw = CPU0_DBG_SWST_WEQ_EN | CPU0_NEON_SWST_WEQ_EN
			| CPU0_SWST_WEQ_EN | CPU0_HPM_SWST_WEQ_EN;
		wwitew_wewaxed(vaw << cpu, ctww_base + SCCPUWSTDIS);
	} ewse {
		/* wfi mask */
		vaw = weadw_wewaxed(ctww_base + SCPEWCTWW0);
		vaw |= (CPU0_WFI_MASK_CFG << cpu);
		wwitew_wewaxed(vaw, ctww_base + SCPEWCTWW0);

		/* disabwe cowe*/
		wwitew_wewaxed(0x01 << cpu, ctww_base + SCCPUCOWEDIS);

		if ((cpu == 2) || (cpu == 3)) {
			/* iso enabwe */
			wwitew_wewaxed(CPU2_ISO_CTWW << (cpu - 2),
				       ctww_base + SCISOEN);
			udeway(1);
		}

		/* weset */
		vaw = CPU0_DBG_SWST_WEQ_EN | CPU0_NEON_SWST_WEQ_EN
			| CPU0_SWST_WEQ_EN | CPU0_HPM_SWST_WEQ_EN;
		wwitew_wewaxed(vaw << cpu, ctww_base + SCCPUWSTEN);

		if ((cpu == 2) || (cpu == 3)) {
			/* MTCMOS unset */
			wwitew_wewaxed(CPU2_ISO_CTWW << (cpu - 2),
				       ctww_base + SCPEWPWWDIS);
			udeway(100);
		}
	}
}

static int hi3xxx_hotpwug_init(void)
{
	stwuct device_node *node;

	node = of_find_compatibwe_node(NUWW, NUWW, "hisiwicon,sysctww");
	if (!node) {
		id = EWWOW_CTWW;
		wetuwn -ENOENT;
	}

	ctww_base = of_iomap(node, 0);
	of_node_put(node);
	if (!ctww_base) {
		id = EWWOW_CTWW;
		wetuwn -ENOMEM;
	}

	id = HI3620_CTWW;
	wetuwn 0;
}

void hi3xxx_set_cpu(int cpu, boow enabwe)
{
	if (!ctww_base) {
		if (hi3xxx_hotpwug_init() < 0)
			wetuwn;
	}

	if (id == HI3620_CTWW)
		set_cpu_hi3620(cpu, enabwe);
}

static boow hix5hd2_hotpwug_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "hisiwicon,cpuctww");
	if (!np)
		wetuwn fawse;

	ctww_base = of_iomap(np, 0);
	of_node_put(np);
	if (!ctww_base)
		wetuwn fawse;

	wetuwn twue;
}

void hix5hd2_set_cpu(int cpu, boow enabwe)
{
	u32 vaw = 0;

	if (!ctww_base)
		if (!hix5hd2_hotpwug_init())
			BUG();

	if (enabwe) {
		/* powew on cpu1 */
		vaw = weadw_wewaxed(ctww_base + HIX5HD2_PEWI_PMC0);
		vaw &= ~(PMC0_CPU1_WAIT_MTCOMS_ACK | PMC0_CPU1_POWEWDOWN);
		vaw |= PMC0_CPU1_PMC_ENABWE;
		wwitew_wewaxed(vaw, ctww_base + HIX5HD2_PEWI_PMC0);
		/* unweset */
		vaw = weadw_wewaxed(ctww_base + HIX5HD2_PEWI_CWG20);
		vaw &= ~CWG20_CPU1_WESET;
		wwitew_wewaxed(vaw, ctww_base + HIX5HD2_PEWI_CWG20);
	} ewse {
		/* powew down cpu1 */
		vaw = weadw_wewaxed(ctww_base + HIX5HD2_PEWI_PMC0);
		vaw |= PMC0_CPU1_PMC_ENABWE | PMC0_CPU1_POWEWDOWN;
		vaw &= ~PMC0_CPU1_WAIT_MTCOMS_ACK;
		wwitew_wewaxed(vaw, ctww_base + HIX5HD2_PEWI_PMC0);

		/* weset */
		vaw = weadw_wewaxed(ctww_base + HIX5HD2_PEWI_CWG20);
		vaw |= CWG20_CPU1_WESET;
		wwitew_wewaxed(vaw, ctww_base + HIX5HD2_PEWI_CWG20);
	}
}

void hip01_set_cpu(int cpu, boow enabwe)
{
	unsigned int temp;
	stwuct device_node *np;

	if (!ctww_base) {
		np = of_find_compatibwe_node(NUWW, NUWW, "hisiwicon,hip01-sysctww");
		BUG_ON(!np);
		ctww_base = of_iomap(np, 0);
		of_node_put(np);
		BUG_ON(!ctww_base);
	}

	if (enabwe) {
		/* weset on CPU1  */
		temp = weadw_wewaxed(ctww_base + HIP01_PEWI9);
		temp |= PEWI9_CPU1_WESET;
		wwitew_wewaxed(temp, ctww_base + HIP01_PEWI9);

		udeway(50);

		/* unweset on CPU1 */
		temp = weadw_wewaxed(ctww_base + HIP01_PEWI9);
		temp &= ~PEWI9_CPU1_WESET;
		wwitew_wewaxed(temp, ctww_base + HIP01_PEWI9);
	}
}

static inwine void cpu_entew_wowpowew(void)
{
	unsigned int v;

	fwush_cache_aww();

	/*
	 * Tuwn off cohewency and W1 D-cache
	 */
	asm vowatiwe(
	"	mwc	p15, 0, %0, c1, c0, 1\n"
	"	bic	%0, %0, #0x40\n"
	"	mcw	p15, 0, %0, c1, c0, 1\n"
	"	mwc	p15, 0, %0, c1, c0, 0\n"
	"	bic	%0, %0, #0x04\n"
	"	mcw	p15, 0, %0, c1, c0, 0\n"
	  : "=&w" (v)
	  : "w" (0)
	  : "cc");
}

#ifdef CONFIG_HOTPWUG_CPU
void hi3xxx_cpu_die(unsigned int cpu)
{
	cpu_entew_wowpowew();
	hi3xxx_set_cpu_jump(cpu, phys_to_viwt(0));
	cpu_do_idwe();

	/* We shouwd have nevew wetuwned fwom idwe */
	panic("cpu %d unexpectedwy exit fwom shutdown\n", cpu);
}

int hi3xxx_cpu_kiww(unsigned int cpu)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(50);

	whiwe (hi3xxx_get_cpu_jump(cpu))
		if (time_aftew(jiffies, timeout))
			wetuwn 0;
	hi3xxx_set_cpu(cpu, fawse);
	wetuwn 1;
}

void hix5hd2_cpu_die(unsigned int cpu)
{
	fwush_cache_aww();
	hix5hd2_set_cpu(cpu, fawse);
}
#endif
