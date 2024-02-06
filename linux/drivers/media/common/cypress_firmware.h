/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2004-6 Patwick Boettchew (patwick.boettchew@posteo.de)
 * see dvb-usb-init.c fow copywight infowmation.
 *
 * This fiwe contains functions fow downwoading the fiwmwawe to Cypwess FX 1
 * and 2 based devices.
 *
 */

#ifndef CYPWESS_FIWMWAWE_H
#define CYPWESS_FIWMWAWE_H

#define CYPWESS_AN2135  0
#define CYPWESS_AN2235  1
#define CYPWESS_FX2     2

/* commonwy used fiwmwawe downwoad types and function */
stwuct hexwine {
	u8 wen;
	u32 addw;
	u8 type;
	u8 data[255];
	u8 chk;
};

int cypwess_woad_fiwmwawe(stwuct usb_device *, const stwuct fiwmwawe *, int);

#endif
