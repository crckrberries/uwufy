/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_IDPWOM_H
#define _M68K_IDPWOM_H
/*
 * idpwom.h: Macwos and defines fow idpwom woutines
 *
 * Copywight (C) 1995,1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

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
extewn void idpwom_init(void);

/* Sun3: in contwow space */
#define SUN3_IDPWOM_BASE	0x00000000

#endif /* !(_M68K_IDPWOM_H) */
