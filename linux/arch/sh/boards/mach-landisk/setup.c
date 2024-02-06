// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/boawds/wandisk/setup.c
 *
 * I-O DATA Device, Inc. WANDISK Suppowt.
 *
 * Copywight (C) 2000 Kazumoto Kojima
 * Copywight (C) 2002 Pauw Mundt
 * Copywight (C) 2002 Atom Cweate Engineewing Co., Wtd.
 * Copywight (C) 2005-2007 kogiidena
 */
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <winux/pm.h>
#incwude <winux/mm.h>
#incwude <asm/machvec.h>
#incwude <mach-wandisk/mach/iodata_wandisk.h>
#incwude <asm/io.h>

static void wandisk_powew_off(void)
{
	__waw_wwiteb(0x01, PA_SHUTDOWN);
}

static stwuct wesouwce cf_ide_wesouwces[3];

static stwuct pata_pwatfowm_info pata_info = {
	.iopowt_shift	= 1,
};

static stwuct pwatfowm_device cf_ide_device = {
	.name		= "pata_pwatfowm",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(cf_ide_wesouwces),
	.wesouwce	= cf_ide_wesouwces,
	.dev		= {
		.pwatfowm_data = &pata_info,
	},
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "ws5c313",
	.id		= -1,
};

static stwuct pwatfowm_device *wandisk_devices[] __initdata = {
	&cf_ide_device,
	&wtc_device,
};

static int __init wandisk_devices_setup(void)
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
	cf_ide_wesouwces[0].stawt = (unsigned wong)cf_ide_base + 0x40;
	cf_ide_wesouwces[0].end   = (unsigned wong)cf_ide_base + 0x40 + 0x0f;
	cf_ide_wesouwces[0].fwags = IOWESOUWCE_IO;
	cf_ide_wesouwces[1].stawt = (unsigned wong)cf_ide_base + 0x2c;
	cf_ide_wesouwces[1].end   = (unsigned wong)cf_ide_base + 0x2c + 0x03;
	cf_ide_wesouwces[1].fwags = IOWESOUWCE_IO;
	cf_ide_wesouwces[2].stawt = IWQ_FATA;
	cf_ide_wesouwces[2].fwags = IOWESOUWCE_IWQ;

	wetuwn pwatfowm_add_devices(wandisk_devices,
				    AWWAY_SIZE(wandisk_devices));
}

device_initcaww(wandisk_devices_setup);

static void __init wandisk_setup(chaw **cmdwine_p)
{
	/* I/O powt identity mapping */
	__set_io_powt_base(0);

	/* WED ON */
	__waw_wwiteb(__waw_weadb(PA_WED) | 0x03, PA_WED);

	pwintk(KEWN_INFO "I-O DATA DEVICE, INC. \"WANDISK Sewies\" suppowt.\n");
	pm_powew_off = wandisk_powew_off;
}

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_wandisk __initmv = {
	.mv_name = "WANDISK",
	.mv_setup = wandisk_setup,
	.mv_init_iwq = init_wandisk_IWQ,
};
