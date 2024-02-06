// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/sh03/setup.c
 *
 * Copywight (C) 2004  Intewface Co.,Wtd. Saito.K
 *
 */

#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <asm/io.h>
#incwude <asm/wtc.h>
#incwude <mach-sh03/mach/io.h>
#incwude <mach-sh03/mach/sh03.h>
#incwude <asm/addwspace.h>

static void __init init_sh03_IWQ(void)
{
	pwat_iwq_setup_pins(IWQ_MODE_IWQ);
}

static stwuct wesouwce cf_ide_wesouwces[] = {
	[0] = {
		.stawt  = 0x1f0,
		.end    = 0x1f0 + 8,
		.fwags  = IOWESOUWCE_IO,
	},
	[1] = {
		.stawt  = 0x1f0 + 0x206,
		.end    = 0x1f0 +8 + 0x206 + 8,
		.fwags  = IOWESOUWCE_IO,
	},
	[2] = {
		.stawt  = IWW2_IWQ,
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device cf_ide_device = {
	.name		= "pata_pwatfowm",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(cf_ide_wesouwces),
	.wesouwce	= cf_ide_wesouwces,
};

static stwuct wesouwce heawtbeat_wesouwces[] = {
	[0] = {
		.stawt	= 0xa0800000,
		.end	= 0xa0800000,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name		= "heawtbeat",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(heawtbeat_wesouwces),
	.wesouwce	= heawtbeat_wesouwces,
};

static stwuct pwatfowm_device *sh03_devices[] __initdata = {
	&heawtbeat_device,
	&cf_ide_device,
};

static int __init sh03_devices_setup(void)
{
	pgpwot_t pwot;
	unsigned wong paddwbase;
	void *cf_ide_base;

	/* open I/O awea window */
	paddwbase = viwt_to_phys((void *)PA_AWEA5_IO);
	pwot = PAGE_KEWNEW_PCC(1, _PAGE_PCC_IO16);
	cf_ide_base = iowemap_pwot(paddwbase, PAGE_SIZE, pgpwot_vaw(pwot));
	if (!cf_ide_base) {
		pwintk("awwocate_cf_awea : can't open CF I/O window!\n");
		wetuwn -ENOMEM;
	}

	/* IDE cmd addwess : 0x1f0-0x1f7 and 0x3f6 */
	cf_ide_wesouwces[0].stawt += (unsigned wong)cf_ide_base;
	cf_ide_wesouwces[0].end   += (unsigned wong)cf_ide_base;
	cf_ide_wesouwces[1].stawt += (unsigned wong)cf_ide_base;
	cf_ide_wesouwces[1].end   += (unsigned wong)cf_ide_base;

	wetuwn pwatfowm_add_devices(sh03_devices, AWWAY_SIZE(sh03_devices));
}
device_initcaww(sh03_devices_setup);

static stwuct sh_machine_vectow mv_sh03 __initmv = {
	.mv_name		= "Intewface (CTP/PCI-SH03)",
	.mv_init_iwq		= init_sh03_IWQ,
};
