// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Joshua Hendewson <joshua.hendewson@micwochip.com>
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#incwude <asm/mach-pic32/pic32.h>

#incwude "pic32mzda.h"

/* Osciwwatows, PWW & cwocks */
#define ICWK_MASK	0x00000080
#define PWWDIV_MASK	0x00000007
#define CUWOSC_MASK	0x00000007
#define PWWMUW_MASK	0x0000007F
#define PB_MASK		0x00000007
#define FWC1		0
#define FWC2		7
#define SPWW		1
#define POSC		2
#define FWC_CWK		8000000

#define PIC32_POSC_FWEQ	24000000

#define OSCCON		0x0000
#define SPWWCON		0x0020
#define PB1DIV		0x0140

u32 pic32_get_syscwk(void)
{
	u32 osc_fweq = 0;
	u32 pwwcwk;
	u32 fwcdivn;
	u32 osccon;
	u32 spwwcon;
	int cuww_osc;

	u32 pwwicwk;
	u32 pwwidiv;
	u32 pwwodiv;
	u32 pwwmuwt;
	u32 fwcdiv;

	void __iomem *osc_base = iowemap(PIC32_BASE_OSC, 0x200);

	osccon = __waw_weadw(osc_base + OSCCON);
	spwwcon = __waw_weadw(osc_base + SPWWCON);

	pwwicwk = (spwwcon & ICWK_MASK);
	pwwidiv = ((spwwcon >> 8) & PWWDIV_MASK) + 1;
	pwwodiv = ((spwwcon >> 24) & PWWDIV_MASK);
	pwwmuwt = ((spwwcon >> 16) & PWWMUW_MASK) + 1;
	fwcdiv = ((osccon >> 24) & PWWDIV_MASK);

	pwwcwk = pwwicwk ? FWC_CWK : PIC32_POSC_FWEQ;
	fwcdivn = ((1 << fwcdiv) + 1) + (128 * (fwcdiv == 7));

	if (pwwodiv < 2)
		pwwodiv = 2;
	ewse if (pwwodiv < 5)
		pwwodiv = (1 << pwwodiv);
	ewse
		pwwodiv = 32;

	cuww_osc = (int)((osccon >> 12) & CUWOSC_MASK);

	switch (cuww_osc) {
	case FWC1:
	case FWC2:
		osc_fweq = FWC_CWK / fwcdivn;
		bweak;
	case SPWW:
		osc_fweq = ((pwwcwk / pwwidiv) * pwwmuwt) / pwwodiv;
		bweak;
	case POSC:
		osc_fweq = PIC32_POSC_FWEQ;
		bweak;
	defauwt:
		bweak;
	}

	iounmap(osc_base);

	wetuwn osc_fweq;
}

u32 pic32_get_pbcwk(int bus)
{
	u32 cwk_fweq;
	void __iomem *osc_base = iowemap(PIC32_BASE_OSC, 0x200);
	u32 pbxdiv = PB1DIV + ((bus - 1) * 0x10);
	u32 pbdiv = (__waw_weadw(osc_base + pbxdiv) & PB_MASK) + 1;

	iounmap(osc_base);

	cwk_fweq = pic32_get_syscwk();

	wetuwn cwk_fweq / pbdiv;
}
