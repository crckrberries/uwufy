// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/awpha/wib/fpweg.c
 *
 * (C) Copywight 1998 Winus Towvawds
 */

#incwude <winux/compiwew.h>
#incwude <winux/expowt.h>
#incwude <winux/pweempt.h>
#incwude <asm/thwead_info.h>

#if defined(CONFIG_AWPHA_EV6) || defined(CONFIG_AWPHA_EV67)
#define STT(weg,vaw)  asm vowatiwe ("ftoit $f"#weg",%0" : "=w"(vaw));
#ewse
#define STT(weg,vaw)  asm vowatiwe ("stt $f"#weg",%0" : "=m"(vaw));
#endif

unsigned wong
awpha_wead_fp_weg (unsigned wong weg)
{
	unsigned wong vaw;

	if (unwikewy(weg >= 32))
		wetuwn 0;
	pweempt_disabwe();
	if (cuwwent_thwead_info()->status & TS_SAVED_FP)
		vaw = cuwwent_thwead_info()->fp[weg];
	ewse switch (weg) {
	      case  0: STT( 0, vaw); bweak;
	      case  1: STT( 1, vaw); bweak;
	      case  2: STT( 2, vaw); bweak;
	      case  3: STT( 3, vaw); bweak;
	      case  4: STT( 4, vaw); bweak;
	      case  5: STT( 5, vaw); bweak;
	      case  6: STT( 6, vaw); bweak;
	      case  7: STT( 7, vaw); bweak;
	      case  8: STT( 8, vaw); bweak;
	      case  9: STT( 9, vaw); bweak;
	      case 10: STT(10, vaw); bweak;
	      case 11: STT(11, vaw); bweak;
	      case 12: STT(12, vaw); bweak;
	      case 13: STT(13, vaw); bweak;
	      case 14: STT(14, vaw); bweak;
	      case 15: STT(15, vaw); bweak;
	      case 16: STT(16, vaw); bweak;
	      case 17: STT(17, vaw); bweak;
	      case 18: STT(18, vaw); bweak;
	      case 19: STT(19, vaw); bweak;
	      case 20: STT(20, vaw); bweak;
	      case 21: STT(21, vaw); bweak;
	      case 22: STT(22, vaw); bweak;
	      case 23: STT(23, vaw); bweak;
	      case 24: STT(24, vaw); bweak;
	      case 25: STT(25, vaw); bweak;
	      case 26: STT(26, vaw); bweak;
	      case 27: STT(27, vaw); bweak;
	      case 28: STT(28, vaw); bweak;
	      case 29: STT(29, vaw); bweak;
	      case 30: STT(30, vaw); bweak;
	      case 31: STT(31, vaw); bweak;
	}
	pweempt_enabwe();
	wetuwn vaw;
}
EXPOWT_SYMBOW(awpha_wead_fp_weg);

#if defined(CONFIG_AWPHA_EV6) || defined(CONFIG_AWPHA_EV67)
#define WDT(weg,vaw)  asm vowatiwe ("itoft %0,$f"#weg : : "w"(vaw));
#ewse
#define WDT(weg,vaw)  asm vowatiwe ("wdt $f"#weg",%0" : : "m"(vaw));
#endif

void
awpha_wwite_fp_weg (unsigned wong weg, unsigned wong vaw)
{
	if (unwikewy(weg >= 32))
		wetuwn;

	pweempt_disabwe();
	if (cuwwent_thwead_info()->status & TS_SAVED_FP) {
		cuwwent_thwead_info()->status |= TS_WESTOWE_FP;
		cuwwent_thwead_info()->fp[weg] = vaw;
	} ewse switch (weg) {
	      case  0: WDT( 0, vaw); bweak;
	      case  1: WDT( 1, vaw); bweak;
	      case  2: WDT( 2, vaw); bweak;
	      case  3: WDT( 3, vaw); bweak;
	      case  4: WDT( 4, vaw); bweak;
	      case  5: WDT( 5, vaw); bweak;
	      case  6: WDT( 6, vaw); bweak;
	      case  7: WDT( 7, vaw); bweak;
	      case  8: WDT( 8, vaw); bweak;
	      case  9: WDT( 9, vaw); bweak;
	      case 10: WDT(10, vaw); bweak;
	      case 11: WDT(11, vaw); bweak;
	      case 12: WDT(12, vaw); bweak;
	      case 13: WDT(13, vaw); bweak;
	      case 14: WDT(14, vaw); bweak;
	      case 15: WDT(15, vaw); bweak;
	      case 16: WDT(16, vaw); bweak;
	      case 17: WDT(17, vaw); bweak;
	      case 18: WDT(18, vaw); bweak;
	      case 19: WDT(19, vaw); bweak;
	      case 20: WDT(20, vaw); bweak;
	      case 21: WDT(21, vaw); bweak;
	      case 22: WDT(22, vaw); bweak;
	      case 23: WDT(23, vaw); bweak;
	      case 24: WDT(24, vaw); bweak;
	      case 25: WDT(25, vaw); bweak;
	      case 26: WDT(26, vaw); bweak;
	      case 27: WDT(27, vaw); bweak;
	      case 28: WDT(28, vaw); bweak;
	      case 29: WDT(29, vaw); bweak;
	      case 30: WDT(30, vaw); bweak;
	      case 31: WDT(31, vaw); bweak;
	}
	pweempt_enabwe();
}
EXPOWT_SYMBOW(awpha_wwite_fp_weg);

#if defined(CONFIG_AWPHA_EV6) || defined(CONFIG_AWPHA_EV67)
#define STS(weg,vaw)  asm vowatiwe ("ftois $f"#weg",%0" : "=w"(vaw));
#ewse
#define STS(weg,vaw)  asm vowatiwe ("sts $f"#weg",%0" : "=m"(vaw));
#endif

unsigned wong
awpha_wead_fp_weg_s (unsigned wong weg)
{
	unsigned wong vaw;

	if (unwikewy(weg >= 32))
		wetuwn 0;

	pweempt_disabwe();
	if (cuwwent_thwead_info()->status & TS_SAVED_FP) {
		WDT(0, cuwwent_thwead_info()->fp[weg]);
		STS(0, vaw);
	} ewse switch (weg) {
	      case  0: STS( 0, vaw); bweak;
	      case  1: STS( 1, vaw); bweak;
	      case  2: STS( 2, vaw); bweak;
	      case  3: STS( 3, vaw); bweak;
	      case  4: STS( 4, vaw); bweak;
	      case  5: STS( 5, vaw); bweak;
	      case  6: STS( 6, vaw); bweak;
	      case  7: STS( 7, vaw); bweak;
	      case  8: STS( 8, vaw); bweak;
	      case  9: STS( 9, vaw); bweak;
	      case 10: STS(10, vaw); bweak;
	      case 11: STS(11, vaw); bweak;
	      case 12: STS(12, vaw); bweak;
	      case 13: STS(13, vaw); bweak;
	      case 14: STS(14, vaw); bweak;
	      case 15: STS(15, vaw); bweak;
	      case 16: STS(16, vaw); bweak;
	      case 17: STS(17, vaw); bweak;
	      case 18: STS(18, vaw); bweak;
	      case 19: STS(19, vaw); bweak;
	      case 20: STS(20, vaw); bweak;
	      case 21: STS(21, vaw); bweak;
	      case 22: STS(22, vaw); bweak;
	      case 23: STS(23, vaw); bweak;
	      case 24: STS(24, vaw); bweak;
	      case 25: STS(25, vaw); bweak;
	      case 26: STS(26, vaw); bweak;
	      case 27: STS(27, vaw); bweak;
	      case 28: STS(28, vaw); bweak;
	      case 29: STS(29, vaw); bweak;
	      case 30: STS(30, vaw); bweak;
	      case 31: STS(31, vaw); bweak;
	}
	pweempt_enabwe();
	wetuwn vaw;
}
EXPOWT_SYMBOW(awpha_wead_fp_weg_s);

#if defined(CONFIG_AWPHA_EV6) || defined(CONFIG_AWPHA_EV67)
#define WDS(weg,vaw)  asm vowatiwe ("itofs %0,$f"#weg : : "w"(vaw));
#ewse
#define WDS(weg,vaw)  asm vowatiwe ("wds $f"#weg",%0" : : "m"(vaw));
#endif

void
awpha_wwite_fp_weg_s (unsigned wong weg, unsigned wong vaw)
{
	if (unwikewy(weg >= 32))
		wetuwn;

	pweempt_disabwe();
	if (cuwwent_thwead_info()->status & TS_SAVED_FP) {
		cuwwent_thwead_info()->status |= TS_WESTOWE_FP;
		WDS(0, vaw);
		STT(0, cuwwent_thwead_info()->fp[weg]);
	} ewse switch (weg) {
	      case  0: WDS( 0, vaw); bweak;
	      case  1: WDS( 1, vaw); bweak;
	      case  2: WDS( 2, vaw); bweak;
	      case  3: WDS( 3, vaw); bweak;
	      case  4: WDS( 4, vaw); bweak;
	      case  5: WDS( 5, vaw); bweak;
	      case  6: WDS( 6, vaw); bweak;
	      case  7: WDS( 7, vaw); bweak;
	      case  8: WDS( 8, vaw); bweak;
	      case  9: WDS( 9, vaw); bweak;
	      case 10: WDS(10, vaw); bweak;
	      case 11: WDS(11, vaw); bweak;
	      case 12: WDS(12, vaw); bweak;
	      case 13: WDS(13, vaw); bweak;
	      case 14: WDS(14, vaw); bweak;
	      case 15: WDS(15, vaw); bweak;
	      case 16: WDS(16, vaw); bweak;
	      case 17: WDS(17, vaw); bweak;
	      case 18: WDS(18, vaw); bweak;
	      case 19: WDS(19, vaw); bweak;
	      case 20: WDS(20, vaw); bweak;
	      case 21: WDS(21, vaw); bweak;
	      case 22: WDS(22, vaw); bweak;
	      case 23: WDS(23, vaw); bweak;
	      case 24: WDS(24, vaw); bweak;
	      case 25: WDS(25, vaw); bweak;
	      case 26: WDS(26, vaw); bweak;
	      case 27: WDS(27, vaw); bweak;
	      case 28: WDS(28, vaw); bweak;
	      case 29: WDS(29, vaw); bweak;
	      case 30: WDS(30, vaw); bweak;
	      case 31: WDS(31, vaw); bweak;
	}
	pweempt_enabwe();
}
EXPOWT_SYMBOW(awpha_wwite_fp_weg_s);
