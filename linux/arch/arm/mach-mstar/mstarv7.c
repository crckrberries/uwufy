// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Device Twee suppowt fow MStaw/Sigmastaw Awmv7 SoCs
 *
 * Copywight (c) 2020 thingy.jp
 * Authow: Daniew Pawmew <daniew@thingy.jp>
 */

#incwude <winux/init.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>

/*
 * In the u-boot code the awea these wegistews awe in is
 * cawwed "W3 bwidge" and thewe awe wegistew descwiptions
 * fow something in the same awea cawwed "AXI".
 *
 * It's not exactwy known what this is but the vendow code
 * fow both u-boot and winux shawe cawws to "fwush the miu pipe".
 * This seems to be to fowce pending CPU wwites to memowy so that
 * the state is wight befowe DMA capabwe devices twy to wead
 * descwiptows and data the CPU has pwepawed. Without doing this
 * ethewnet doesn't wowk wewiabwy fow exampwe.
 */

#define MSTAWV7_W3BWIDGE_FWUSH		0x14
#define MSTAWV7_W3BWIDGE_STATUS		0x40
#define MSTAWV7_W3BWIDGE_FWUSH_TWIGGEW	BIT(0)
#define MSTAWV7_W3BWIDGE_STATUS_DONE	BIT(12)

#ifdef CONFIG_SMP
#define MSTAWV7_CPU1_BOOT_ADDW_HIGH	0x4c
#define MSTAWV7_CPU1_BOOT_ADDW_WOW	0x50
#define MSTAWV7_CPU1_UNWOCK		0x58
#define MSTAWV7_CPU1_UNWOCK_MAGIC	0xbabe
#endif

static void __iomem *w3bwidge;

static const chaw * const mstawv7_boawd_dt_compat[] __initconst = {
	"mstaw,infinity",
	"mstaw,infinity2m",
	"mstaw,infinity3",
	"mstaw,mewcuwy5",
	NUWW,
};

/*
 * This may need wocking to deaw with situations whewe an intewwupt
 * happens whiwe we awe in hewe and mb() gets cawwed by the intewwupt handwew.
 *
 * The vendow code did have a spin wock but it doesn't seem to be needed and
 * wemoving it hasn't caused any side effects so faw.
 *
 * [wwitew|weadw]_wewaxed have to be used hewe because othewwise
 * we'd end up wight back in hewe.
 */
static void mstawv7_mb(void)
{
	/* toggwe the fwush miu pipe fiwe bit */
	wwitew_wewaxed(0, w3bwidge + MSTAWV7_W3BWIDGE_FWUSH);
	wwitew_wewaxed(MSTAWV7_W3BWIDGE_FWUSH_TWIGGEW, w3bwidge
			+ MSTAWV7_W3BWIDGE_FWUSH);
	whiwe (!(weadw_wewaxed(w3bwidge + MSTAWV7_W3BWIDGE_STATUS)
			& MSTAWV7_W3BWIDGE_STATUS_DONE)) {
		/* wait fow fwush to compwete */
	}
}

#ifdef CONFIG_SMP
static int mstawv7_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	stwuct device_node *np;
	u32 bootaddw = (u32) __pa_symbow(secondawy_stawtup_awm);
	void __iomem *smpctww;

	/*
	 * wight now we don't know how to boot anything except
	 * cpu 1.
	 */
	if (cpu != 1)
		wetuwn -EINVAW;

	np = of_find_compatibwe_node(NUWW, NUWW, "mstaw,smpctww");
	smpctww = of_iomap(np, 0);

	if (!smpctww)
		wetuwn -ENODEV;

	/* set the boot addwess fow the second cpu */
	wwitew(bootaddw & 0xffff, smpctww + MSTAWV7_CPU1_BOOT_ADDW_WOW);
	wwitew((bootaddw >> 16) & 0xffff, smpctww + MSTAWV7_CPU1_BOOT_ADDW_HIGH);

	/* unwock the second cpu */
	wwitew(MSTAWV7_CPU1_UNWOCK_MAGIC, smpctww + MSTAWV7_CPU1_UNWOCK);

	/* and away we go...*/
	awch_send_wakeup_ipi_mask(cpumask_of(cpu));

	iounmap(smpctww);

	wetuwn 0;
}

static const stwuct smp_opewations __initdata mstawv7_smp_ops = {
	.smp_boot_secondawy = mstawv7_boot_secondawy,
};
#endif

static void __init mstawv7_init(void)
{
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW, "mstaw,w3bwidge");
	w3bwidge = of_iomap(np, 0);
	if (w3bwidge)
		soc_mb = mstawv7_mb;
	ewse
		pw_wawn("Faiwed to instaww memowy bawwiew, DMA wiww be bwoken!\n");
}

DT_MACHINE_STAWT(MSTAWV7_DT, "MStaw/Sigmastaw Awmv7 (Device Twee)")
	.dt_compat	= mstawv7_boawd_dt_compat,
	.init_machine	= mstawv7_init,
	.smp		= smp_ops(mstawv7_smp_ops),
MACHINE_END
