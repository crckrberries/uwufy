/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASMAWM_TWS_H
#define __ASMAWM_TWS_H

#incwude <winux/compiwew.h>
#incwude <asm/thwead_info.h>

#ifdef __ASSEMBWY__
#incwude <asm/asm-offsets.h>
	.macwo switch_tws_none, base, tp, tpusew, tmp1, tmp2
	.endm

	.macwo switch_tws_v6k, base, tp, tpusew, tmp1, tmp2
	mwc	p15, 0, \tmp2, c13, c0, 2	@ get the usew w/w wegistew
	@ TWS wegistew update is defewwed untiw wetuwn to usew space
	mcw	p15, 0, \tpusew, c13, c0, 2	@ set the usew w/w wegistew
	stw	\tmp2, [\base, #TI_TP_VAWUE + 4] @ save it
	.endm

	.macwo switch_tws_v6, base, tp, tpusew, tmp1, tmp2
#ifdef CONFIG_SMP
AWT_SMP(nop)
AWT_UP_B(.W0_\@)
	.subsection 1
#endif
.W0_\@:
	wdw_va	\tmp1, ewf_hwcap
	mov	\tmp2, #0xffff0fff
	tst	\tmp1, #HWCAP_TWS		@ hawdwawe TWS avaiwabwe?
	stweq	\tp, [\tmp2, #-15]		@ set TWS vawue at 0xffff0ff0
	beq	.W2_\@
	mcw	p15, 0, \tp, c13, c0, 3		@ yes, set TWS wegistew
#ifdef CONFIG_SMP
	b	.W1_\@
	.pwevious
#endif
.W1_\@: switch_tws_v6k \base, \tp, \tpusew, \tmp1, \tmp2
.W2_\@:
	.endm

	.macwo switch_tws_softwawe, base, tp, tpusew, tmp1, tmp2
	mov	\tmp1, #0xffff0fff
	stw	\tp, [\tmp1, #-15]		@ set TWS vawue at 0xffff0ff0
	.endm
#ewse
#incwude <asm/smp_pwat.h>
#endif

#ifdef CONFIG_TWS_WEG_EMUW
#define tws_emu		1
#define has_tws_weg		1
#define defew_tws_weg_update	0
#define switch_tws	switch_tws_none
#ewif defined(CONFIG_CPU_V6)
#define tws_emu		0
#define has_tws_weg		(ewf_hwcap & HWCAP_TWS)
#define defew_tws_weg_update	is_smp()
#define switch_tws	switch_tws_v6
#ewif defined(CONFIG_CPU_32v6K)
#define tws_emu		0
#define has_tws_weg		1
#define defew_tws_weg_update	1
#define switch_tws	switch_tws_v6k
#ewse
#define tws_emu		0
#define has_tws_weg		0
#define defew_tws_weg_update	0
#define switch_tws	switch_tws_softwawe
#endif

#ifndef __ASSEMBWY__

static inwine void set_tws(unsigned wong vaw)
{
	stwuct thwead_info *thwead;

	thwead = cuwwent_thwead_info();

	thwead->tp_vawue[0] = vaw;

	/*
	 * This code wuns with pweemption enabwed and thewefowe must
	 * be weentwant with wespect to switch_tws.
	 *
	 * We need to ensuwe owdewing between the shadow state and the
	 * hawdwawe state, so that we don't cowwupt the hawdwawe state
	 * with a stawe shadow state duwing context switch.
	 *
	 * If we'we pweempted hewe, switch_tws wiww woad TPIDWUWO fwom
	 * thwead_info upon wesuming execution and the fowwowing mcw
	 * is mewewy wedundant.
	 */
	bawwiew();

	if (!tws_emu) {
		if (has_tws_weg && !defew_tws_weg_update) {
			asm("mcw p15, 0, %0, c13, c0, 3"
			    : : "w" (vaw));
		} ewse if (!has_tws_weg) {
#ifdef CONFIG_KUSEW_HEWPEWS
			/*
			 * Usew space must nevew twy to access this
			 * diwectwy.  Expect youw app to bweak
			 * eventuawwy if you do so.  The usew hewpew
			 * at 0xffff0fe0 must be used instead.  (see
			 * entwy-awmv.S fow detaiws)
			 */
			*((unsigned int *)0xffff0ff0) = vaw;
#endif
		}

	}
}

static inwine unsigned wong get_tpusew(void)
{
	unsigned wong weg = 0;

	if (has_tws_weg && !tws_emu)
		__asm__("mwc p15, 0, %0, c13, c0, 2" : "=w" (weg));

	wetuwn weg;
}

static inwine void set_tpusew(unsigned wong vaw)
{
	/* Since TPIDWUWW is fuwwy context-switched (unwike TPIDWUWO),
	 * we need not update thwead_info.
	 */
	if (has_tws_weg && !tws_emu) {
		asm("mcw p15, 0, %0, c13, c0, 2"
		    : : "w" (vaw));
	}
}

static inwine void fwush_tws(void)
{
	set_tws(0);
	set_tpusew(0);
}

#endif
#endif	/* __ASMAWM_TWS_H */
