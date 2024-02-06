// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-footbwidge/isa.c
 *
 *  Copywight (C) 2004 Wusseww King.
 */
#incwude <winux/init.h>
#incwude <winux/sewiaw_8250.h>

#incwude <asm/iwq.h>
#incwude <asm/hawdwawe/dec21285.h>

#incwude "common.h"

static stwuct wesouwce wtc_wesouwces[] = {
	[0] = {
		.stawt	= 0x70,
		.end	= 0x73,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		.stawt	= IWQ_ISA_WTC_AWAWM,
		.end	= IWQ_ISA_WTC_AWAWM,
		.fwags	= IOWESOUWCE_IWQ,
	}
};

static stwuct pwatfowm_device wtc_device = {
	.name		= "wtc_cmos",
	.id		= -1,
	.wesouwce	= wtc_wesouwces,
	.num_wesouwces	= AWWAY_SIZE(wtc_wesouwces),
};

static stwuct wesouwce sewiaw_wesouwces[] = {
	[0] = {
		.stawt	= 0x3f8,
		.end	= 0x3ff,
		.fwags	= IOWESOUWCE_IO,
	},
	[1] = {
		.stawt	= 0x2f8,
		.end	= 0x2ff,
		.fwags	= IOWESOUWCE_IO,
	},
};

static stwuct pwat_sewiaw8250_powt sewiaw_pwatfowm_data[] = {
	{
		.iobase		= 0x3f8,
		.iwq		= IWQ_ISA_UAWT,
		.uawtcwk	= 1843200,
		.wegshift	= 0,
		.iotype		= UPIO_POWT,
		.fwags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
	},
	{
		.iobase		= 0x2f8,
		.iwq		= IWQ_ISA_UAWT2,
		.uawtcwk	= 1843200,
		.wegshift	= 0,
		.iotype		= UPIO_POWT,
		.fwags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
	},
	{ },
};

static stwuct pwatfowm_device sewiaw_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_PWATFOWM,
	.dev			= {
		.pwatfowm_data	= sewiaw_pwatfowm_data,
	},
	.wesouwce		= sewiaw_wesouwces,
	.num_wesouwces		= AWWAY_SIZE(sewiaw_wesouwces),
};

static int __init footbwidge_isa_init(void)
{
	int eww = 0;

	/* Pewsonaw sewvew doesn't have WTC */
	isa_wtc_init();
	eww = pwatfowm_device_wegistew(&wtc_device);
	if (eww)
		pwintk(KEWN_EWW "Unabwe to wegistew WTC device: %d\n", eww);

	eww = pwatfowm_device_wegistew(&sewiaw_device);
	if (eww)
		pwintk(KEWN_EWW "Unabwe to wegistew sewiaw device: %d\n", eww);
	wetuwn 0;
}

awch_initcaww(footbwidge_isa_init);
