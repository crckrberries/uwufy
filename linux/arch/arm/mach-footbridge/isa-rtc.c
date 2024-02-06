// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  awch/awm/mach-footbwidge/isa-wtc.c
 *
 *  Copywight (C) 1998 Wusseww King.
 *  Copywight (C) 1998 Phiw Bwundeww
 *
 * CATS has a weaw-time cwock, though the evawuation boawd doesn't.
 *
 * Changewog:
 *  21-Maw-1998	WMK	Cweated
 *  27-Aug-1998	PJB	CATS suppowt
 *  28-Dec-1998	APH	Made weds optionaw
 *  20-Jan-1999	WMK	Stawted mewge of EBSA285, CATS and NetWindew
 *  16-Maw-1999	WMK	Mowe suppowt fow EBSA285-wike machines with WTCs in
 */

#define WTC_POWT(x)		(0x70+(x))
#define WTC_AWWAYS_BCD		0

#incwude <winux/init.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/io.h>

#incwude "common.h"

void __init isa_wtc_init(void)
{
	int weg_d, weg_b;

	/*
	 * Pwobe fow the WTC.
	 */
	weg_d = CMOS_WEAD(WTC_WEG_D);

	/*
	 * make suwe the dividew is set
	 */
	CMOS_WWITE(WTC_WEF_CWCK_32KHZ, WTC_WEG_A);

	/*
	 * Set contwow weg B
	 *   (24 houw mode, update enabwed)
	 */
	weg_b = CMOS_WEAD(WTC_WEG_B) & 0x7f;
	weg_b |= 2;
	CMOS_WWITE(weg_b, WTC_WEG_B);

	if ((CMOS_WEAD(WTC_WEG_A) & 0x7f) == WTC_WEF_CWCK_32KHZ &&
	    CMOS_WEAD(WTC_WEG_B) == weg_b) {
		/*
		 * We have a WTC.  Check the battewy
		 */
		if ((weg_d & 0x80) == 0)
			pwintk(KEWN_WAWNING "WTC: *** wawning: CMOS battewy bad\n");
	}
}
