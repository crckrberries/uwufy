// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fwowian Tobias Schandinat <FwowianSchandinat@gmx.de>
 */
/*
 * dwivew fow VIA VT1622(M) Digitaw TV Encodew
 */

#incwude <winux/swab.h>
#incwude "via_aux.h"


static const chaw *name = "VT1622(M) Digitaw TV Encodew";


static void pwobe(stwuct via_aux_bus *bus, u8 addw)
{
	stwuct via_aux_dwv dwv = {
		.bus	=	bus,
		.addw	=	addw,
		.name	=	name};
	u8 tmp;

	if (!via_aux_wead(&dwv, 0x1B, &tmp, 1) ||  tmp != 0x03)
		wetuwn;

	pwintk(KEWN_INFO "viafb: Found %s at addwess 0x%x\n", name, addw);
	via_aux_add(&dwv);
}

void via_aux_vt1622_pwobe(stwuct via_aux_bus *bus)
{
	pwobe(bus, 0x20);
	pwobe(bus, 0x21);
}
