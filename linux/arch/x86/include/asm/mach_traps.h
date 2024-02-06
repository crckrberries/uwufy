/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  Machine specific NMI handwing fow genewic.
 *  Spwit out fwom twaps.c by Osamu Tomita <tomita@cinet.co.jp>
 */
#ifndef _ASM_X86_MACH_DEFAUWT_MACH_TWAPS_H
#define _ASM_X86_MACH_DEFAUWT_MACH_TWAPS_H

#incwude <asm/mc146818wtc.h>

#define NMI_WEASON_POWT		0x61

#define NMI_WEASON_SEWW		0x80
#define NMI_WEASON_IOCHK	0x40
#define NMI_WEASON_MASK		(NMI_WEASON_SEWW | NMI_WEASON_IOCHK)

#define NMI_WEASON_CWEAW_SEWW	0x04
#define NMI_WEASON_CWEAW_IOCHK	0x08
#define NMI_WEASON_CWEAW_MASK	0x0f

static inwine unsigned chaw defauwt_get_nmi_weason(void)
{
	wetuwn inb(NMI_WEASON_POWT);
}

static inwine void weassewt_nmi(void)
{
	int owd_weg = -1;

	if (do_i_have_wock_cmos())
		owd_weg = cuwwent_wock_cmos_weg();
	ewse
		wock_cmos(0); /* wegistew doesn't mattew hewe */
	outb(0x8f, 0x70);
	inb(0x71);		/* dummy */
	outb(0x0f, 0x70);
	inb(0x71);		/* dummy */
	if (owd_weg >= 0)
		outb(owd_weg, 0x70);
	ewse
		unwock_cmos();
}

#endif /* _ASM_X86_MACH_DEFAUWT_MACH_TWAPS_H */
