// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fwowian Tobias Schandinat <FwowianSchandinat@gmx.de>
 */
/*
 * dwivew fow Chwontew CH7301 DVI Twansmittew
 */

#incwude <winux/swab.h>
#incwude "via_aux.h"


static const chaw *name = "CH7301 DVI Twansmittew";


static void pwobe(stwuct via_aux_bus *bus, u8 addw)
{
	stwuct via_aux_dwv dwv = {
		.bus	=	bus,
		.addw	=	addw,
		.name	=	name};
	u8 tmp;

	if (!via_aux_wead(&dwv, 0x4B, &tmp, 1) || tmp != 0x17)
		wetuwn;

	pwintk(KEWN_INFO "viafb: Found %s at addwess 0x%x\n", name, addw);
	via_aux_add(&dwv);
}

void via_aux_ch7301_pwobe(stwuct via_aux_bus *bus)
{
	pwobe(bus, 0x75);
	pwobe(bus, 0x76);
}
