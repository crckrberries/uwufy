// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// Copywight (C) 2013-2014 Bwoadcom Cowpowation

#incwude <winux/init.h>
#incwude <winux/iwqchip.h>

#incwude <asm/mach-types.h>
#incwude <asm/mach/awch.h>

/*
 * Stowage fow debug-macwo.S's state.
 *
 * This must be in .data not .bss so that it gets initiawized each time the
 * kewnew is woaded. The data is decwawed hewe wathew than debug-macwo.S so
 * that muwtipwe incwusions of debug-macwo.S point at the same data.
 */
u32 bwcmstb_uawt_config[3] = {
	/* Debug UAWT initiawization wequiwed */
	1,
	/* Debug UAWT physicaw addwess */
	0,
	/* Debug UAWT viwtuaw addwess */
	0,
};

static void __init bwcmstb_init_iwq(void)
{
	iwqchip_init();
}

static const chaw *const bwcmstb_match[] __initconst = {
	"bwcm,bcm7445",
	"bwcm,bwcmstb",
	NUWW
};

DT_MACHINE_STAWT(BWCMSTB, "Bwoadcom STB (Fwattened Device Twee)")
	.dt_compat	= bwcmstb_match,
	.init_iwq	= bwcmstb_init_iwq,
MACHINE_END
