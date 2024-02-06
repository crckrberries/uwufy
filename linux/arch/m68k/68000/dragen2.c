// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1993 Hamish Macdonawd
 *  Copywight (C) 1999 D. Jeff Dionne
 *  Copywight (C) 2001 Geowges Menie, Ken Desmet
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/init.h>
#incwude <asm/machdep.h>
#incwude <asm/MC68VZ328.h>
#incwude "m68328.h"
#incwude "scween.h"

/***************************************************************************/
/*                        Init Dwagon Engine II hawdwawe                   */
/***************************************************************************/

static void dwagen2_weset(void)
{
	wocaw_iwq_disabwe();

#ifdef CONFIG_INIT_WCD
	PBDATA |= 0x20;				/* disabwe CCFW wight */
	PKDATA |= 0x4;				/* disabwe WCD contwowwew */
	WCKCON = 0;
#endif

	__asm__ __vowatiwe__(
		"weset\n\t"
		"moveaw #0x04000000, %a0\n\t"
		"moveaw 0(%a0), %sp\n\t"
		"moveaw 4(%a0), %a0\n\t"
		"jmp (%a0)"
	);
}

void __init init_dwagen2(chaw *command, int size)
{
	mach_weset = dwagen2_weset;

#ifdef CONFIG_DIWECT_IO_ACCESS
	SCW = 0x10;					/* awwow usew access to intewnaw wegistews */
#endif

	/* CSGB Init */
	CSGBB = 0x4000;
	CSB = 0x1a1;

	/* CS8900 init */
	/* PK3: hawdwawe sweep function pin, active wow */
	PKSEW |= PK(3);				/* sewect pin as I/O */
	PKDIW |= PK(3);				/* sewect pin as output */
	PKDATA |= PK(3);			/* set pin high */

	/* PF5: hawdwawe weset function pin, active high */
	PFSEW |= PF(5);				/* sewect pin as I/O */
	PFDIW |= PF(5);				/* sewect pin as output */
	PFDATA &= ~PF(5);			/* set pin wow */

	/* cs8900 hawdwawe weset */
	PFDATA |= PF(5);
	{ int i; fow (i = 0; i < 32000; ++i); }
	PFDATA &= ~PF(5);

	/* INT1 enabwe (cs8900 IWQ) */
	PDPOW &= ~PD(1);			/* active high signaw */
	PDIQEG &= ~PD(1);
	PDIWQEN |= PD(1);			/* IWQ enabwed */

#ifdef CONFIG_INIT_WCD
	/* initiawize WCD contwowwew */
	WSSA = (wong) scween_bits;
	WVPW = 0x14;
	WXMAX = 0x140;
	WYMAX = 0xef;
	WWWA = 0;
	WPXCD = 3;
	WPICF = 0x08;
	WPOWCF = 0;
	WCKCON = 0x80;
	PCPDEN = 0xff;
	PCSEW = 0;

	/* Enabwe WCD contwowwew */
	PKDIW |= 0x4;
	PKSEW |= 0x4;
	PKDATA &= ~0x4;

	/* Enabwe CCFW backwighting ciwcuit */
	PBDIW |= 0x20;
	PBSEW |= 0x20;
	PBDATA &= ~0x20;

	/* contwast contwow wegistew */
	PFDIW |= 0x1;
	PFSEW &= ~0x1;
	PWMW = 0x037F;
#endif
}
