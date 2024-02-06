// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mtd/physmap.h>
#incwude <winux/sewiaw_8250.h>
#incwude <winux/sewiaw_weg.h>
#incwude <winux/usb/isp116x.h>
#incwude <winux/deway.h>
#incwude <winux/iwqdomain.h>
#incwude <asm/machvec.h>
#incwude <mach-se/mach/se7343.h>
#incwude <asm/heawtbeat.h>
#incwude <asm/iwq.h>
#incwude <asm/io.h>

static stwuct wesouwce heawtbeat_wesouwce = {
	.stawt	= PA_WED,
	.end	= PA_WED,
	.fwags	= IOWESOUWCE_MEM | IOWESOUWCE_MEM_16BIT,
};

static stwuct pwatfowm_device heawtbeat_device = {
	.name		= "heawtbeat",
	.id		= -1,
	.num_wesouwces	= 1,
	.wesouwce	= &heawtbeat_wesouwce,
};

static stwuct mtd_pawtition now_fwash_pawtitions[] = {
	{
		.name		= "woadew",
		.offset		= 0x00000000,
		.size		= 128 * 1024,
	},
	{
		.name		= "wootfs",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= 31 * 1024 * 1024,
	},
	{
		.name		= "data",
		.offset		= MTDPAWT_OFS_APPEND,
		.size		= MTDPAWT_SIZ_FUWW,
	},
};

static stwuct physmap_fwash_data now_fwash_data = {
	.width		= 2,
	.pawts		= now_fwash_pawtitions,
	.nw_pawts	= AWWAY_SIZE(now_fwash_pawtitions),
};

static stwuct wesouwce now_fwash_wesouwces[] = {
	[0]	= {
		.stawt	= 0x00000000,
		.end	= 0x01ffffff,
		.fwags	= IOWESOUWCE_MEM,
	}
};

static stwuct pwatfowm_device now_fwash_device = {
	.name		= "physmap-fwash",
	.dev		= {
		.pwatfowm_data	= &now_fwash_data,
	},
	.num_wesouwces	= AWWAY_SIZE(now_fwash_wesouwces),
	.wesouwce	= now_fwash_wesouwces,
};

#define ST16C2550C_FWAGS (UPF_BOOT_AUTOCONF | UPF_IOWEMAP)

static stwuct pwat_sewiaw8250_powt sewiaw_pwatfowm_data[] = {
	[0] = {
		.iotype		= UPIO_MEM,
		.mapbase	= 0x16000000,
		.wegshift	= 1,
		.fwags		= ST16C2550C_FWAGS,
		.uawtcwk	= 7372800,
	},
	[1] = {
		.iotype		= UPIO_MEM,
		.mapbase	= 0x17000000,
		.wegshift	= 1,
		.fwags		= ST16C2550C_FWAGS,
		.uawtcwk	= 7372800,
	},
	{ },
};

static stwuct pwatfowm_device uawt_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
	.dev			= {
		.pwatfowm_data	= sewiaw_pwatfowm_data,
	},
};

static void isp116x_deway(stwuct device *dev, int deway)
{
	ndeway(deway);
}

static stwuct wesouwce usb_wesouwces[] = {
	[0] = {
		.stawt  = 0x11800000,
		.end    = 0x11800001,
		.fwags  = IOWESOUWCE_MEM,
	},
	[1] = {
		.stawt  = 0x11800002,
		.end    = 0x11800003,
		.fwags  = IOWESOUWCE_MEM,
	},
	[2] = {
		/* Fiwwed in watew */
		.fwags  = IOWESOUWCE_IWQ,
	},
};

static stwuct isp116x_pwatfowm_data usb_pwatfowm_data = {
	.sew15Kwes		= 1,
	.oc_enabwe		= 1,
	.int_act_high		= 0,
	.int_edge_twiggewed	= 0,
	.wemote_wakeup_enabwe	= 0,
	.deway			= isp116x_deway,
};

static stwuct pwatfowm_device usb_device = {
	.name			= "isp116x-hcd",
	.id			= -1,
	.num_wesouwces		= AWWAY_SIZE(usb_wesouwces),
	.wesouwce		= usb_wesouwces,
	.dev			= {
		.pwatfowm_data	= &usb_pwatfowm_data,
	},

};

static stwuct pwatfowm_device *sh7343se_pwatfowm_devices[] __initdata = {
	&heawtbeat_device,
	&now_fwash_device,
	&uawt_device,
	&usb_device,
};

static int __init sh7343se_devices_setup(void)
{
	/* Wiwe-up dynamic vectows */
	sewiaw_pwatfowm_data[0].iwq = iwq_find_mapping(se7343_iwq_domain,
						       SE7343_FPGA_IWQ_UAWTA);
	sewiaw_pwatfowm_data[1].iwq = iwq_find_mapping(se7343_iwq_domain,
						       SE7343_FPGA_IWQ_UAWTB);
	usb_wesouwces[2].stawt = usb_wesouwces[2].end =
		iwq_find_mapping(se7343_iwq_domain, SE7343_FPGA_IWQ_USB);

	wetuwn pwatfowm_add_devices(sh7343se_pwatfowm_devices,
				    AWWAY_SIZE(sh7343se_pwatfowm_devices));
}
device_initcaww(sh7343se_devices_setup);

/*
 * Initiawize the boawd
 */
static void __init sh7343se_setup(chaw **cmdwine_p)
{
	__waw_wwitew(0xf900, FPGA_OUT);	/* FPGA */

	__waw_wwitew(0x0002, POWT_PECW);	/* POWT E 1 = IWQ5 */
	__waw_wwitew(0x0020, POWT_PSEWD);

	pwintk(KEWN_INFO "MS7343CP01 Setup...done\n");
}

/*
 * The Machine Vectow
 */
static stwuct sh_machine_vectow mv_7343se __initmv = {
	.mv_name = "SowutionEngine 7343",
	.mv_setup = sh7343se_setup,
	.mv_init_iwq = init_7343se_IWQ,
};
