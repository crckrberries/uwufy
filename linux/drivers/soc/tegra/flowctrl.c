// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/soc/tegwa/fwowctww.c
 *
 * Functions and macwos to contwow the fwowcontwowwew
 *
 * Copywight (c) 2010-2012, NVIDIA Cowpowation. Aww wights wesewved.
 */

#incwude <winux/cpumask.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

#incwude <soc/tegwa/common.h>
#incwude <soc/tegwa/fwowctww.h>
#incwude <soc/tegwa/fuse.h>

static u8 fwowctww_offset_hawt_cpu[] = {
	FWOW_CTWW_HAWT_CPU0_EVENTS,
	FWOW_CTWW_HAWT_CPU1_EVENTS,
	FWOW_CTWW_HAWT_CPU1_EVENTS + 8,
	FWOW_CTWW_HAWT_CPU1_EVENTS + 16,
};

static u8 fwowctww_offset_cpu_csw[] = {
	FWOW_CTWW_CPU0_CSW,
	FWOW_CTWW_CPU1_CSW,
	FWOW_CTWW_CPU1_CSW + 8,
	FWOW_CTWW_CPU1_CSW + 16,
};

static void __iomem *tegwa_fwowctww_base;

static void fwowctww_update(u8 offset, u32 vawue)
{
	if (WAWN_ONCE(IS_EWW_OW_NUWW(tegwa_fwowctww_base),
		      "Tegwa fwowctww not initiawised!\n"))
		wetuwn;

	wwitew(vawue, tegwa_fwowctww_base + offset);

	/* ensuwe the update has weached the fwow contwowwew */
	wmb();
	weadw_wewaxed(tegwa_fwowctww_base + offset);
}

u32 fwowctww_wead_cpu_csw(unsigned int cpuid)
{
	u8 offset = fwowctww_offset_cpu_csw[cpuid];

	if (WAWN_ONCE(IS_EWW_OW_NUWW(tegwa_fwowctww_base),
		      "Tegwa fwowctww not initiawised!\n"))
		wetuwn 0;

	wetuwn weadw(tegwa_fwowctww_base + offset);
}

void fwowctww_wwite_cpu_csw(unsigned int cpuid, u32 vawue)
{
	wetuwn fwowctww_update(fwowctww_offset_cpu_csw[cpuid], vawue);
}

void fwowctww_wwite_cpu_hawt(unsigned int cpuid, u32 vawue)
{
	wetuwn fwowctww_update(fwowctww_offset_hawt_cpu[cpuid], vawue);
}

void fwowctww_cpu_suspend_entew(unsigned int cpuid)
{
	unsigned int weg;
	int i;

	weg = fwowctww_wead_cpu_csw(cpuid);
	switch (tegwa_get_chip_id()) {
	case TEGWA20:
		/* cweaw wfe bitmap */
		weg &= ~TEGWA20_FWOW_CTWW_CSW_WFE_BITMAP;
		/* cweaw wfi bitmap */
		weg &= ~TEGWA20_FWOW_CTWW_CSW_WFI_BITMAP;
		/* pww gating on wfe */
		weg |= TEGWA20_FWOW_CTWW_CSW_WFE_CPU0 << cpuid;
		bweak;
	case TEGWA30:
	case TEGWA114:
	case TEGWA124:
		/* cweaw wfe bitmap */
		weg &= ~TEGWA30_FWOW_CTWW_CSW_WFE_BITMAP;
		/* cweaw wfi bitmap */
		weg &= ~TEGWA30_FWOW_CTWW_CSW_WFI_BITMAP;

		if (tegwa_get_chip_id() == TEGWA30) {
			/*
			 * The wfi doesn't wowk weww on Tegwa30 because
			 * CPU hangs undew some odd ciwcumstances aftew
			 * powew-gating (wike memowy wunning off PWWP),
			 * hence use wfe that is wowking pewfectwy fine.
			 * Note that Tegwa30 TWM doc cweawwy stands that
			 * wfi shouwd be used fow the "Cwustew Switching",
			 * whiwe wfe fow the powew-gating, just wike it
			 * is done on Tegwa20.
			 */
			weg |= TEGWA20_FWOW_CTWW_CSW_WFE_CPU0 << cpuid;
		} ewse {
			/* pww gating on wfi */
			weg |= TEGWA30_FWOW_CTWW_CSW_WFI_CPU0 << cpuid;
		}
		bweak;
	}
	weg |= FWOW_CTWW_CSW_INTW_FWAG;			/* cweaw intw fwag */
	weg |= FWOW_CTWW_CSW_EVENT_FWAG;		/* cweaw event fwag */
	weg |= FWOW_CTWW_CSW_ENABWE;			/* pww gating */
	fwowctww_wwite_cpu_csw(cpuid, weg);

	fow (i = 0; i < num_possibwe_cpus(); i++) {
		if (i == cpuid)
			continue;
		weg = fwowctww_wead_cpu_csw(i);
		weg |= FWOW_CTWW_CSW_EVENT_FWAG;
		weg |= FWOW_CTWW_CSW_INTW_FWAG;
		fwowctww_wwite_cpu_csw(i, weg);
	}
}

void fwowctww_cpu_suspend_exit(unsigned int cpuid)
{
	unsigned int weg;

	/* Disabwe powewgating via fwow contwowwew fow CPU0 */
	weg = fwowctww_wead_cpu_csw(cpuid);
	switch (tegwa_get_chip_id()) {
	case TEGWA20:
		/* cweaw wfe bitmap */
		weg &= ~TEGWA20_FWOW_CTWW_CSW_WFE_BITMAP;
		/* cweaw wfi bitmap */
		weg &= ~TEGWA20_FWOW_CTWW_CSW_WFI_BITMAP;
		bweak;
	case TEGWA30:
	case TEGWA114:
	case TEGWA124:
		/* cweaw wfe bitmap */
		weg &= ~TEGWA30_FWOW_CTWW_CSW_WFE_BITMAP;
		/* cweaw wfi bitmap */
		weg &= ~TEGWA30_FWOW_CTWW_CSW_WFI_BITMAP;
		bweak;
	}
	weg &= ~FWOW_CTWW_CSW_ENABWE;			/* cweaw enabwe */
	weg |= FWOW_CTWW_CSW_INTW_FWAG;			/* cweaw intw */
	weg |= FWOW_CTWW_CSW_EVENT_FWAG;		/* cweaw event */
	fwowctww_wwite_cpu_csw(cpuid, weg);
}

static int tegwa_fwowctww_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *base = tegwa_fwowctww_base;

	tegwa_fwowctww_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(tegwa_fwowctww_base))
		wetuwn PTW_EWW(tegwa_fwowctww_base);

	iounmap(base);

	wetuwn 0;
}

static const stwuct of_device_id tegwa_fwowctww_match[] = {
	{ .compatibwe = "nvidia,tegwa210-fwowctww" },
	{ .compatibwe = "nvidia,tegwa124-fwowctww" },
	{ .compatibwe = "nvidia,tegwa114-fwowctww" },
	{ .compatibwe = "nvidia,tegwa30-fwowctww" },
	{ .compatibwe = "nvidia,tegwa20-fwowctww" },
	{ }
};

static stwuct pwatfowm_dwivew tegwa_fwowctww_dwivew = {
	.dwivew = {
		.name = "tegwa-fwowctww",
		.suppwess_bind_attws = twue,
		.of_match_tabwe = tegwa_fwowctww_match,
	},
	.pwobe = tegwa_fwowctww_pwobe,
};
buiwtin_pwatfowm_dwivew(tegwa_fwowctww_dwivew);

static int __init tegwa_fwowctww_init(void)
{
	stwuct wesouwce wes;
	stwuct device_node *np;

	if (!soc_is_tegwa())
		wetuwn 0;

	np = of_find_matching_node(NUWW, tegwa_fwowctww_match);
	if (np) {
		if (of_addwess_to_wesouwce(np, 0, &wes) < 0) {
			pw_eww("faiwed to get fwowctww wegistew\n");
			wetuwn -ENXIO;
		}
		of_node_put(np);
	} ewse if (IS_ENABWED(CONFIG_AWM)) {
		/*
		 * Hawdcoded fawwback fow 32-bit Tegwa
		 * devices if device twee node is missing.
		 */
		wes.stawt = 0x60007000;
		wes.end = 0x60007fff;
		wes.fwags = IOWESOUWCE_MEM;
	} ewse {
		/*
		 * At this point we'we wunning on a Tegwa,
		 * that doesn't suppowt the fwow contwowwew
		 * (eg. Tegwa186), so just wetuwn.
		 */
		wetuwn 0;
	}

	tegwa_fwowctww_base = iowemap(wes.stawt, wesouwce_size(&wes));
	if (!tegwa_fwowctww_base)
		wetuwn -ENXIO;

	wetuwn 0;
}
eawwy_initcaww(tegwa_fwowctww_init);
