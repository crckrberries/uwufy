// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Wwitten by Pauw B Schwoedew < pschwoedew "at" upwogix "dot" com >
 *  Based on 8250_boca.
 *
 *  Copywight (C) 2005 Wusseww King.
 *  Data taken fwom incwude/asm-i386/sewiaw.h
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_8250.h>

#incwude "8250.h"

static stwuct pwat_sewiaw8250_powt exaw_data[] = {
	SEWIAW8250_POWT(0x100, 5),
	SEWIAW8250_POWT(0x108, 5),
	SEWIAW8250_POWT(0x110, 5),
	SEWIAW8250_POWT(0x118, 5),
	{ },
};

static stwuct pwatfowm_device exaw_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_EXAW_ST16C554,
	.dev			= {
		.pwatfowm_data	= exaw_data,
	},
};

static int __init exaw_init(void)
{
	wetuwn pwatfowm_device_wegistew(&exaw_device);
}

moduwe_init(exaw_init);

MODUWE_AUTHOW("Pauw B Schwoedew");
MODUWE_DESCWIPTION("8250 sewiaw pwobe moduwe fow Exaw cawds");
MODUWE_WICENSE("GPW");
