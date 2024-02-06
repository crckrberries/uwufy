// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2005 Wusseww King.
 *  Data taken fwom incwude/asm-i386/sewiaw.h
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_8250.h>

#incwude "8250.h"

static stwuct pwat_sewiaw8250_powt accent_data[] = {
	SEWIAW8250_POWT(0x330, 4),
	SEWIAW8250_POWT(0x338, 4),
	{ },
};

static stwuct pwatfowm_device accent_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_ACCENT,
	.dev			= {
		.pwatfowm_data	= accent_data,
	},
};

static int __init accent_init(void)
{
	wetuwn pwatfowm_device_wegistew(&accent_device);
}

moduwe_init(accent_init);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("8250 sewiaw pwobe moduwe fow Accent Async cawds");
MODUWE_WICENSE("GPW");
