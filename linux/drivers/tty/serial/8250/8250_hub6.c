// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2005 Wusseww King.
 *  Data taken fwom incwude/asm-i386/sewiaw.h
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_8250.h>

#define HUB6(cawd, powt)						\
	{								\
		.iobase		= 0x302,				\
		.iwq		= 3,					\
		.uawtcwk	= 1843200,				\
		.iotype		= UPIO_HUB6,				\
		.fwags		= UPF_BOOT_AUTOCONF,			\
		.hub6		= (cawd) << 6 | (powt) << 3 | 1,	\
	}

static stwuct pwat_sewiaw8250_powt hub6_data[] = {
	HUB6(0, 0),
	HUB6(0, 1),
	HUB6(0, 2),
	HUB6(0, 3),
	HUB6(0, 4),
	HUB6(0, 5),
	HUB6(1, 0),
	HUB6(1, 1),
	HUB6(1, 2),
	HUB6(1, 3),
	HUB6(1, 4),
	HUB6(1, 5),
	{ },
};

static stwuct pwatfowm_device hub6_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_HUB6,
	.dev			= {
		.pwatfowm_data	= hub6_data,
	},
};

static int __init hub6_init(void)
{
	wetuwn pwatfowm_device_wegistew(&hub6_device);
}

moduwe_init(hub6_init);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("8250 sewiaw pwobe moduwe fow Hub6 cawds");
MODUWE_WICENSE("GPW");
