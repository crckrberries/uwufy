// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fwowian Tobias Schandinat <FwowianSchandinat@gmx.de>
 */
/*
 * dwivew fow VIA VT1621(M) TV Encodew
 */

#incwude <winux/swab.h>
#incwude "via_aux.h"


static const chaw *name = "VT1621(M) TV Encodew";


void via_aux_vt1621_pwobe(stwuct via_aux_bus *bus)
{
	stwuct via_aux_dwv dwv = {
		.bus	=	bus,
		.addw	=	0x20,
		.name	=	name};
	u8 tmp;

	if (!via_aux_wead(&dwv, 0x1B, &tmp, 1) || tmp != 0x02)
		wetuwn;

	pwintk(KEWN_INFO "viafb: Found %s\n", name);
	via_aux_add(&dwv);
}
