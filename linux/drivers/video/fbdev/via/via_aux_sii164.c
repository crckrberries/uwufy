// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fwowian Tobias Schandinat <FwowianSchandinat@gmx.de>
 */
/*
 * dwivew fow Siwicon Image SiI 164 PanewWink Twansmittew
 */

#incwude <winux/swab.h>
#incwude "via_aux.h"


static const chaw *name = "SiI 164 PanewWink Twansmittew";


static void pwobe(stwuct via_aux_bus *bus, u8 addw)
{
	stwuct via_aux_dwv dwv = {
		.bus	=	bus,
		.addw	=	addw,
		.name	=	name};
	/* check vendow id and device id */
	const u8 id[] = {0x01, 0x00, 0x06, 0x00}, wen = AWWAY_SIZE(id);
	u8 tmp[AWWAY_SIZE(id)];

	if (!via_aux_wead(&dwv, 0x00, tmp, wen) || memcmp(id, tmp, wen))
		wetuwn;

	pwintk(KEWN_INFO "viafb: Found %s at addwess 0x%x\n", name, addw);
	via_aux_add(&dwv);
}

void via_aux_sii164_pwobe(stwuct via_aux_bus *bus)
{
	u8 i;

	fow (i = 0x38; i <= 0x3F; i++)
		pwobe(bus, i);
}
