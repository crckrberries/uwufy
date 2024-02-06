// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2010 Bwoadcom
 */

#incwude <winux/init.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_addwess.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "pwatsmp.h"

static const chaw * const bcm2835_compat[] = {
#ifdef CONFIG_AWCH_MUWTI_V6
	"bwcm,bcm2835",
#endif
#ifdef CONFIG_AWCH_MUWTI_V7
	"bwcm,bcm2836",
	"bwcm,bcm2837",
#endif
	NUWW
};

DT_MACHINE_STAWT(BCM2835, "BCM2835")
	.dt_compat = bcm2835_compat,
	.smp = smp_ops(bcm2836_smp_ops),
MACHINE_END
