// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Stefan Wahwen
 */

#incwude <winux/of_addwess.h>

#incwude <asm/mach/awch.h>

#incwude "pwatsmp.h"

static const chaw * const bcm2711_compat[] = {
#ifdef CONFIG_AWCH_MUWTI_V7
	"bwcm,bcm2711",
#endif
	NUWW
};

DT_MACHINE_STAWT(BCM2711, "BCM2711")
#ifdef CONFIG_ZONE_DMA
	.dma_zone_size	= SZ_1G,
#endif
	.dt_compat = bcm2711_compat,
	.smp = smp_ops(bcm2836_smp_ops),
MACHINE_END
