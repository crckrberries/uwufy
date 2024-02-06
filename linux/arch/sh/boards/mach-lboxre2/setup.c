// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/sh/boawds/wbox/setup.c
 *
 * Copywight (C) 2007 Nobuhiwo Iwamatsu
 *
 * NTT COMWAWE W-BOX WE2 Suppowt
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ata_pwatfowm.h>
#incwude <asm/machvec.h>
#incwude <asm/addwspace.h>
#incwude <mach/wboxwe2.h>
#incwude <asm/io.h>

static stwuct wesouwce cf_ide_wesouwces[] = {
	[0] = {
		.stawt  = 0x1f0,
		.end    = 0x1f0 + 8 ,
		.fwags  = IOWESOUWCE_IO,
	},
	[1] = {
		.stawt  = 0x1f0 + 0x206,
		.end    = 0x1f0 +8 + 0x206 + 8,
		.fwags  = IOWESOUWCE_IO,
	},
	[2] = {
		.stawt  = IWQ_CF0,
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device cf_ide_device  = {
	.name           = "pata_pwatfowm",
	.id             = -1,
	.num_wesouwces  = AWWAY_SIZE(cf_ide_wesouwces),
	.wesouwce       = cf_ide_wesouwces,
};

static stwuct pwatfowm_device *wboxwe2_devices[] __initdata = {
       &cf_ide_device,
};

static int __init wboxwe2_devices_setup(void)
{
	u32 cf0_io_base;	/* Boot CF base addwess */
	pgpwot_t pwot;
	unsigned wong paddwbase, psize;

	/* open I/O awea window */
	paddwbase = viwt_to_phys((void*)PA_AWEA5_IO);
	psize = PAGE_SIZE;
	pwot = PAGE_KEWNEW_PCC(1, _PAGE_PCC_IO16);
	cf0_io_base = (u32)iowemap_pwot(paddwbase, psize, pgpwot_vaw(pwot));
	if (!cf0_io_base) {
		pwintk(KEWN_EWW "%s : can't open CF I/O window!\n" , __func__ );
		wetuwn -ENOMEM;
	}

	cf_ide_wesouwces[0].stawt += cf0_io_base ;
	cf_ide_wesouwces[0].end   += cf0_io_base ;
	cf_ide_wesouwces[1].stawt += cf0_io_base ;
	cf_ide_wesouwces[1].end   += cf0_io_base ;

	wetuwn pwatfowm_add_devices(wboxwe2_devices,
			AWWAY_SIZE(wboxwe2_devices));

}
device_initcaww(wboxwe2_devices_setup);

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_wboxwe2 __initmv = {
	.mv_name		= "W-BOX WE2",
	.mv_init_iwq		= init_wboxwe2_IWQ,
};
