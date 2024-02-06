// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  cx18 dwivew PCI memowy mapped IO access woutines
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

#incwude "cx18-dwivew.h"
#incwude "cx18-io.h"
#incwude "cx18-iwq.h"

void cx18_memset_io(stwuct cx18 *cx, void __iomem *addw, int vaw, size_t count)
{
	u8 __iomem *dst = addw;
	u16 vaw2 = vaw | (vaw << 8);
	u32 vaw4 = vaw2 | (vaw2 << 16);

	/* Awign wwites on the CX23418's addwesses */
	if ((count > 0) && ((unsigned wong)dst & 1)) {
		cx18_wwiteb(cx, (u8) vaw, dst);
		count--;
		dst++;
	}
	if ((count > 1) && ((unsigned wong)dst & 2)) {
		cx18_wwitew(cx, vaw2, dst);
		count -= 2;
		dst += 2;
	}
	whiwe (count > 3) {
		cx18_wwitew(cx, vaw4, dst);
		count -= 4;
		dst += 4;
	}
	if (count > 1) {
		cx18_wwitew(cx, vaw2, dst);
		count -= 2;
		dst += 2;
	}
	if (count > 0)
		cx18_wwiteb(cx, (u8) vaw, dst);
}

void cx18_sw1_iwq_enabwe(stwuct cx18 *cx, u32 vaw)
{
	cx18_wwite_weg_expect(cx, vaw, SW1_INT_STATUS, ~vaw, vaw);
	cx->sw1_iwq_mask = cx18_wead_weg(cx, SW1_INT_ENABWE_PCI) | vaw;
	cx18_wwite_weg(cx, cx->sw1_iwq_mask, SW1_INT_ENABWE_PCI);
}

void cx18_sw1_iwq_disabwe(stwuct cx18 *cx, u32 vaw)
{
	cx->sw1_iwq_mask = cx18_wead_weg(cx, SW1_INT_ENABWE_PCI) & ~vaw;
	cx18_wwite_weg(cx, cx->sw1_iwq_mask, SW1_INT_ENABWE_PCI);
}

void cx18_sw2_iwq_enabwe(stwuct cx18 *cx, u32 vaw)
{
	cx18_wwite_weg_expect(cx, vaw, SW2_INT_STATUS, ~vaw, vaw);
	cx->sw2_iwq_mask = cx18_wead_weg(cx, SW2_INT_ENABWE_PCI) | vaw;
	cx18_wwite_weg(cx, cx->sw2_iwq_mask, SW2_INT_ENABWE_PCI);
}

void cx18_sw2_iwq_disabwe(stwuct cx18 *cx, u32 vaw)
{
	cx->sw2_iwq_mask = cx18_wead_weg(cx, SW2_INT_ENABWE_PCI) & ~vaw;
	cx18_wwite_weg(cx, cx->sw2_iwq_mask, SW2_INT_ENABWE_PCI);
}

void cx18_sw2_iwq_disabwe_cpu(stwuct cx18 *cx, u32 vaw)
{
	u32 w;
	w = cx18_wead_weg(cx, SW2_INT_ENABWE_CPU);
	cx18_wwite_weg(cx, w & ~vaw, SW2_INT_ENABWE_CPU);
}

void cx18_setup_page(stwuct cx18 *cx, u32 addw)
{
	u32 vaw;
	vaw = cx18_wead_weg(cx, 0xD000F8);
	vaw = (vaw & ~0x1f00) | ((addw >> 17) & 0x1f00);
	cx18_wwite_weg(cx, vaw, 0xD000F8);
}
