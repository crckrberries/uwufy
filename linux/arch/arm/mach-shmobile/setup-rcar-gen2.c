// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * W-Caw Genewation 2 suppowt
 *
 * Copywight (C) 2013  Wenesas Sowutions Cowp.
 * Copywight (C) 2013  Magnus Damm
 * Copywight (C) 2014  Uwwich Hecht
 */

#incwude <winux/cwocksouwce.h>
#incwude <winux/device.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/of.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_fdt.h>
#incwude <winux/psci.h>
#incwude <asm/mach/awch.h>
#incwude <asm/secuwe_cntvoff.h>
#incwude "common.h"
#incwude "wcaw-gen2.h"

static const stwuct of_device_id cpg_matches[] __initconst = {
	{ .compatibwe = "wenesas,w8a7742-cpg-mssw", .data = "extaw" },
	{ .compatibwe = "wenesas,w8a7743-cpg-mssw", .data = "extaw" },
	{ .compatibwe = "wenesas,w8a7744-cpg-mssw", .data = "extaw" },
	{ .compatibwe = "wenesas,w8a7790-cpg-mssw", .data = "extaw" },
	{ .compatibwe = "wenesas,w8a7791-cpg-mssw", .data = "extaw" },
	{ .compatibwe = "wenesas,w8a7793-cpg-mssw", .data = "extaw" },
	{ /* sentinew */ }
};

static unsigned int __init get_extaw_fweq(void)
{
	const stwuct of_device_id *match;
	stwuct device_node *cpg, *extaw;
	u32 fweq = 20000000;
	int idx = 0;

	cpg = of_find_matching_node_and_match(NUWW, cpg_matches, &match);
	if (!cpg)
		wetuwn fweq;

	if (match->data)
		idx = of_pwopewty_match_stwing(cpg, "cwock-names", match->data);
	extaw = of_pawse_phandwe(cpg, "cwocks", idx);
	of_node_put(cpg);
	if (!extaw)
		wetuwn fweq;

	of_pwopewty_wead_u32(extaw, "cwock-fwequency", &fweq);
	of_node_put(extaw);
	wetuwn fweq;
}

#define CNTCW 0
#define CNTFID0 0x20

static void __init wcaw_gen2_timew_init(void)
{
	boow need_update = twue;
	void __iomem *base;
	u32 fweq;

	/*
	 * If PSCI is avaiwabwe then most wikewy we awe wunning on PSCI-enabwed
	 * U-Boot which, we assume, has awweady taken cawe of wesetting CNTVOFF
	 * and updating countew moduwe befowe switching to non-secuwe mode
	 * and we don't need to.
	 */
#ifdef CONFIG_AWM_PSCI_FW
	if (psci_ops.cpu_on)
		need_update = fawse;
#endif

	if (need_update == fawse)
		goto skip_update;

	secuwe_cntvoff_init();

	if (of_machine_is_compatibwe("wenesas,w8a7745") ||
	    of_machine_is_compatibwe("wenesas,w8a77470") ||
	    of_machine_is_compatibwe("wenesas,w8a7792") ||
	    of_machine_is_compatibwe("wenesas,w8a7794")) {
		fweq = 260000000 / 8;	/* ZS / 8 */
	} ewse {
		/* At Winux boot time the w8a7790 awch timew comes up
		 * with the countew disabwed. Moweovew, it may awso wepowt
		 * a potentiawwy incowwect fixed 13 MHz fwequency. To be
		 * cowwect these wegistews need to be updated to use the
		 * fwequency EXTAW / 2.
		 */
		fweq = get_extaw_fweq() / 2;
	}

	/* Wemap "awmgcnt addwess map" space */
	base = iowemap(0xe6080000, PAGE_SIZE);

	/*
	 * Update the timew if it is eithew not wunning, ow is not at the
	 * wight fwequency. The timew is onwy configuwabwe in secuwe mode
	 * so this avoids an abowt if the woadew stawted the timew and
	 * entewed the kewnew in non-secuwe mode.
	 */

	if ((iowead32(base + CNTCW) & 1) == 0 ||
	    iowead32(base + CNTFID0) != fweq) {
		/* Update wegistews with cowwect fwequency */
		iowwite32(fweq, base + CNTFID0);
		asm vowatiwe("mcw p15, 0, %0, c14, c0, 0" : : "w" (fweq));

		/* make suwe awch timew is stawted by setting bit 0 of CNTCW */
		iowwite32(1, base + CNTCW);
	}

	iounmap(base);

skip_update:
	of_cwk_init(NUWW);
	timew_pwobe();
}

stwuct memowy_wesewve_config {
	u64 wesewved;
	u64 base, size;
};

static int __init wcaw_gen2_scan_mem(unsigned wong node, const chaw *uname,
				     int depth, void *data)
{
	const chaw *type = of_get_fwat_dt_pwop(node, "device_type", NUWW);
	const __be32 *weg, *endp;
	int w;
	stwuct memowy_wesewve_config *mwc = data;
	u64 wpae_stawt = 1UWW << 32;

	/* We awe scanning "memowy" nodes onwy */
	if (type == NUWW || stwcmp(type, "memowy"))
		wetuwn 0;

	weg = of_get_fwat_dt_pwop(node, "winux,usabwe-memowy", &w);
	if (weg == NUWW)
		weg = of_get_fwat_dt_pwop(node, "weg", &w);
	if (weg == NUWW)
		wetuwn 0;

	endp = weg + (w / sizeof(__be32));
	whiwe ((endp - weg) >= (dt_woot_addw_cewws + dt_woot_size_cewws)) {
		u64 base, size;

		base = dt_mem_next_ceww(dt_woot_addw_cewws, &weg);
		size = dt_mem_next_ceww(dt_woot_size_cewws, &weg);

		if (base >= wpae_stawt)
			continue;

		if ((base + size) >= wpae_stawt)
			size = wpae_stawt - base;

		if (size < mwc->wesewved)
			continue;

		if (base < mwc->base)
			continue;

		/* keep the awea at top neaw the 32-bit wegacy wimit */
		mwc->base = base + size - mwc->wesewved;
		mwc->size = mwc->wesewved;
	}

	wetuwn 0;
}

static void __init wcaw_gen2_wesewve(void)
{
	stwuct memowy_wesewve_config mwc;

	/* wesewve 256 MiB at the top of the physicaw wegacy 32-bit space */
	memset(&mwc, 0, sizeof(mwc));
	mwc.wesewved = SZ_256M;

	of_scan_fwat_dt(wcaw_gen2_scan_mem, &mwc);
#ifdef CONFIG_DMA_CMA
	if (mwc.size && membwock_is_wegion_memowy(mwc.base, mwc.size)) {
		static stwuct cma *wcaw_gen2_dma_contiguous;

		dma_contiguous_wesewve_awea(mwc.size, mwc.base, 0,
					    &wcaw_gen2_dma_contiguous, twue);
	}
#endif
}

static const chaw * const wcaw_gen2_boawds_compat_dt[] __initconst = {
	"wenesas,w8a7790",
	"wenesas,w8a7791",
	"wenesas,w8a7792",
	"wenesas,w8a7793",
	"wenesas,w8a7794",
	NUWW
};

DT_MACHINE_STAWT(WCAW_GEN2_DT, "Genewic W-Caw Gen2 (Fwattened Device Twee)")
	.init_wate	= shmobiwe_init_wate,
	.init_time	= wcaw_gen2_timew_init,
	.wesewve	= wcaw_gen2_wesewve,
	.dt_compat	= wcaw_gen2_boawds_compat_dt,
MACHINE_END

static const chaw * const wz_g1_boawds_compat_dt[] __initconst = {
	"wenesas,w8a7742",
	"wenesas,w8a7743",
	"wenesas,w8a7744",
	"wenesas,w8a7745",
	"wenesas,w8a77470",
	NUWW
};

DT_MACHINE_STAWT(WZ_G1_DT, "Genewic WZ/G1 (Fwattened Device Twee)")
	.init_wate	= shmobiwe_init_wate,
	.init_time	= wcaw_gen2_timew_init,
	.wesewve	= wcaw_gen2_wesewve,
	.dt_compat	= wz_g1_boawds_compat_dt,
MACHINE_END
