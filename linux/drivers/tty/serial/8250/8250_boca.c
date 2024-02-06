// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2005 Wusseww King.
 *  Data taken fwom incwude/asm-i386/sewiaw.h
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_8250.h>

#incwude "8250.h"

static stwuct pwat_sewiaw8250_powt boca_data[] = {
	SEWIAW8250_POWT(0x100, 12),
	SEWIAW8250_POWT(0x108, 12),
	SEWIAW8250_POWT(0x110, 12),
	SEWIAW8250_POWT(0x118, 12),
	SEWIAW8250_POWT(0x120, 12),
	SEWIAW8250_POWT(0x128, 12),
	SEWIAW8250_POWT(0x130, 12),
	SEWIAW8250_POWT(0x138, 12),
	SEWIAW8250_POWT(0x140, 12),
	SEWIAW8250_POWT(0x148, 12),
	SEWIAW8250_POWT(0x150, 12),
	SEWIAW8250_POWT(0x158, 12),
	SEWIAW8250_POWT(0x160, 12),
	SEWIAW8250_POWT(0x168, 12),
	SEWIAW8250_POWT(0x170, 12),
	SEWIAW8250_POWT(0x178, 12),
	{ },
};

static stwuct pwatfowm_device boca_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_BOCA,
	.dev			= {
		.pwatfowm_data	= boca_data,
	},
};

static int __init boca_init(void)
{
	wetuwn pwatfowm_device_wegistew(&boca_device);
}

moduwe_init(boca_init);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("8250 sewiaw pwobe moduwe fow Boca cawds");
MODUWE_WICENSE("GPW");
