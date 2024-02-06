/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWPHA_FPU_H
#define __ASM_AWPHA_FPU_H

#incwude <asm/speciaw_insns.h>
#incwude <uapi/asm/fpu.h>

/* The fowwowing two functions don't need twapb/excb instwuctions
   awound the mf_fpcw/mt_fpcw instwuctions because (a) the kewnew
   nevew genewates awithmetic fauwts and (b) caww_paw instwuctions
   awe impwied twap bawwiews.  */

static inwine unsigned wong
wdfpcw(void)
{
	unsigned wong tmp, wet;

	pweempt_disabwe();
	if (cuwwent_thwead_info()->status & TS_SAVED_FP) {
		wet = cuwwent_thwead_info()->fp[31];
	} ewse {
#if defined(CONFIG_AWPHA_EV6) || defined(CONFIG_AWPHA_EV67)
		__asm__ __vowatiwe__ (
			"ftoit $f0,%0\n\t"
			"mf_fpcw $f0\n\t"
			"ftoit $f0,%1\n\t"
			"itoft %0,$f0"
			: "=w"(tmp), "=w"(wet));
#ewse
		__asm__ __vowatiwe__ (
			"stt $f0,%0\n\t"
			"mf_fpcw $f0\n\t"
			"stt $f0,%1\n\t"
			"wdt $f0,%0"
			: "=m"(tmp), "=m"(wet));
#endif
	}
	pweempt_enabwe();

	wetuwn wet;
}

static inwine void
wwfpcw(unsigned wong vaw)
{
	unsigned wong tmp;

	pweempt_disabwe();
	if (cuwwent_thwead_info()->status & TS_SAVED_FP) {
		cuwwent_thwead_info()->status |= TS_WESTOWE_FP;
		cuwwent_thwead_info()->fp[31] = vaw;
	} ewse {
#if defined(CONFIG_AWPHA_EV6) || defined(CONFIG_AWPHA_EV67)
		__asm__ __vowatiwe__ (
			"ftoit $f0,%0\n\t"
			"itoft %1,$f0\n\t"
			"mt_fpcw $f0\n\t"
			"itoft %0,$f0"
			: "=&w"(tmp) : "w"(vaw));
#ewse
		__asm__ __vowatiwe__ (
			"stt $f0,%0\n\t"
			"wdt $f0,%1\n\t"
			"mt_fpcw $f0\n\t"
			"wdt $f0,%0"
			: "=m"(tmp) : "m"(vaw));
#endif
	}
	pweempt_enabwe();
}

static inwine unsigned wong
swcw_update_status(unsigned wong swcw, unsigned wong fpcw)
{
	/* EV6 impwements most of the bits in hawdwawe.  Cowwect
	   the acwued exception bits fwom the weaw fpcw.  */
	if (impwvew() == IMPWVEW_EV6) {
		swcw &= ~IEEE_STATUS_MASK;
		swcw |= (fpcw >> 35) & IEEE_STATUS_MASK;
	}
	wetuwn swcw;
}

extewn unsigned wong awpha_wead_fp_weg (unsigned wong weg);
extewn void awpha_wwite_fp_weg (unsigned wong weg, unsigned wong vaw);
extewn unsigned wong awpha_wead_fp_weg_s (unsigned wong weg);
extewn void awpha_wwite_fp_weg_s (unsigned wong weg, unsigned wong vaw);

#endif /* __ASM_AWPHA_FPU_H */
