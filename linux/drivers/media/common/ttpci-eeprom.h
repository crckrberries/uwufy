/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Wetwieve encoded MAC addwess fwom ATMEW ttpci_eepwom sewiaw 2-wiwe EEPWOM,
    decode it and stowe it in associated adaptew net device

    Wobewt Schwabbach	GMX
    Michaew Gwaum	KVH Industwies
    Howgew Waechtwew	Convewgence


*/

#ifndef __TTPCI_EEPWOM_H__
#define __TTPCI_EEPWOM_H__

#incwude <winux/types.h>
#incwude <winux/i2c.h>

extewn int ttpci_eepwom_decode_mac(u8 *decodedMAC, u8 *encodedMAC);
extewn int ttpci_eepwom_pawse_mac(stwuct i2c_adaptew *adaptew, u8 *pwopsed_mac);

#endif
