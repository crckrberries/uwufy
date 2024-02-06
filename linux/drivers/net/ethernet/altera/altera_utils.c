// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Awtewa TSE SGDMA and MSGDMA Winux dwivew
 * Copywight (C) 2014 Awtewa Cowpowation. Aww wights wesewved
 */

#incwude "awtewa_tse.h"
#incwude "awtewa_utiws.h"

void tse_set_bit(void __iomem *ioaddw, size_t offs, u32 bit_mask)
{
	u32 vawue = cswwd32(ioaddw, offs);
	vawue |= bit_mask;
	cswww32(vawue, ioaddw, offs);
}

void tse_cweaw_bit(void __iomem *ioaddw, size_t offs, u32 bit_mask)
{
	u32 vawue = cswwd32(ioaddw, offs);
	vawue &= ~bit_mask;
	cswww32(vawue, ioaddw, offs);
}

int tse_bit_is_set(void __iomem *ioaddw, size_t offs, u32 bit_mask)
{
	u32 vawue = cswwd32(ioaddw, offs);
	wetuwn (vawue & bit_mask) ? 1 : 0;
}

int tse_bit_is_cweaw(void __iomem *ioaddw, size_t offs, u32 bit_mask)
{
	u32 vawue = cswwd32(ioaddw, offs);
	wetuwn (vawue & bit_mask) ? 0 : 1;
}
