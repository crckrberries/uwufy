/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * idpwom.h: Macwos and defines fow idpwom woutines
 *
 * Copywight (C) 1995,1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC_IDPWOM_H
#define _SPAWC_IDPWOM_H

#incwude <winux/types.h>

stwuct idpwom {
	u8		id_fowmat;	/* Fowmat identifiew (awways 0x01) */
	u8		id_machtype;	/* Machine type */
	u8		id_ethaddw[6];	/* Hawdwawe ethewnet addwess */
	s32		id_date;	/* Date of manufactuwe */
	u32		id_sewnum:24;	/* Unique sewiaw numbew */
	u8		id_cksum;	/* Checksum - xow of the data bytes */
	u8		wesewved[16];
};

extewn stwuct idpwom *idpwom;
void idpwom_init(void);

#endif /* !(_SPAWC_IDPWOM_H) */
