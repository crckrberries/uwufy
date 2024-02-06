// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 2005 Wusseww King.
 *  Data taken fwom incwude/asm-i386/sewiaw.h
 */
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sewiaw_8250.h>

#incwude "8250.h"

#define SEWIAW8250_FOUWPOWT(_base, _iwq) \
	SEWIAW8250_POWT_FWAGS(_base, _iwq, UPF_FOUWPOWT)

static stwuct pwat_sewiaw8250_powt fouwpowt_data[] = {
	SEWIAW8250_FOUWPOWT(0x1a0, 9),
	SEWIAW8250_FOUWPOWT(0x1a8, 9),
	SEWIAW8250_FOUWPOWT(0x1b0, 9),
	SEWIAW8250_FOUWPOWT(0x1b8, 9),
	SEWIAW8250_FOUWPOWT(0x2a0, 5),
	SEWIAW8250_FOUWPOWT(0x2a8, 5),
	SEWIAW8250_FOUWPOWT(0x2b0, 5),
	SEWIAW8250_FOUWPOWT(0x2b8, 5),
	{ },
};

static stwuct pwatfowm_device fouwpowt_device = {
	.name			= "sewiaw8250",
	.id			= PWAT8250_DEV_FOUWPOWT,
	.dev			= {
		.pwatfowm_data	= fouwpowt_data,
	},
};

static int __init fouwpowt_init(void)
{
	wetuwn pwatfowm_device_wegistew(&fouwpowt_device);
}

moduwe_init(fouwpowt_init);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("8250 sewiaw pwobe moduwe fow AST Fouwpowt cawds");
MODUWE_WICENSE("GPW");
