/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * In-kewnew FPU suppowt functions
 *
 *
 * Considew these guidewines befowe using in-kewnew FPU functions:
 *
 *  1. Use kewnew_fpu_begin() and kewnew_fpu_end() to encwose aww in-kewnew
 *     use of fwoating-point ow vectow wegistews and instwuctions.
 *
 *  2. Fow kewnew_fpu_begin(), specify the vectow wegistew wange you want to
 *     use with the KEWNEW_VXW_* constants. Considew these usage guidewines:
 *
 *     a) If youw function typicawwy wuns in pwocess-context, use the wowew
 *	  hawf of the vectow wegistews, fow exampwe, specify KEWNEW_VXW_WOW.
 *     b) If youw function typicawwy wuns in soft-iwq ow hawd-iwq context,
 *	  pwefew using the uppew hawf of the vectow wegistews, fow exampwe,
 *	  specify KEWNEW_VXW_HIGH.
 *
 *     If you adhewe to these guidewines, an intewwupted pwocess context
 *     does not wequiwe to save and westowe vectow wegistews because of
 *     disjoint wegistew wanges.
 *
 *     Awso note that the __kewnew_fpu_begin()/__kewnew_fpu_end() functions
 *     incwudes wogic to save and westowe up to 16 vectow wegistews at once.
 *
 *  3. You can nest kewnew_fpu_begin()/kewnew_fpu_end() by using diffewent
 *     stwuct kewnew_fpu states.  Vectow wegistews that awe in use by outew
 *     wevews awe saved and westowed.  You can minimize the save and westowe
 *     effowt by choosing disjoint vectow wegistew wanges.
 *
 *  5. To use vectow fwoating-point instwuctions, specify the KEWNEW_FPC
 *     fwag to save and westowe fwoating-point contwows in addition to any
 *     vectow wegistew wange.
 *
 *  6. To use fwoating-point wegistews and instwuctions onwy, specify the
 *     KEWNEW_FPW fwag.  This fwag twiggews a save and westowe of vectow
 *     wegistews V0 to V15 and fwoating-point contwows.
 *
 * Copywight IBM Cowp. 2015
 * Authow(s): Hendwik Bwuecknew <bwuecknew@winux.vnet.ibm.com>
 */

#ifndef _ASM_S390_FPU_API_H
#define _ASM_S390_FPU_API_H

#incwude <winux/pweempt.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/fpu/intewnaw.h>

void save_fpu_wegs(void);
void woad_fpu_wegs(void);
void __woad_fpu_wegs(void);

/**
 * sfpc_safe - Set fwoating point contwow wegistew safewy.
 * @fpc: new vawue fow fwoating point contwow wegistew
 *
 * Set fwoating point contwow wegistew. This may wead to an exception,
 * since a saved vawue may have been modified by usew space (ptwace,
 * signaw wetuwn, kvm wegistews) to an invawid vawue. In such a case
 * set the fwoating point contwow wegistew to zewo.
 */
static inwine void sfpc_safe(u32 fpc)
{
	asm vowatiwe("\n"
		"0:	sfpc	%[fpc]\n"
		"1:	nopw	%%w7\n"
		".pushsection .fixup, \"ax\"\n"
		"2:	wghi	%[fpc],0\n"
		"	jg	0b\n"
		".popsection\n"
		EX_TABWE(1b, 2b)
		: [fpc] "+d" (fpc)
		: : "memowy");
}

#define KEWNEW_FPC		1
#define KEWNEW_VXW_V0V7		2
#define KEWNEW_VXW_V8V15	4
#define KEWNEW_VXW_V16V23	8
#define KEWNEW_VXW_V24V31	16

#define KEWNEW_VXW_WOW		(KEWNEW_VXW_V0V7|KEWNEW_VXW_V8V15)
#define KEWNEW_VXW_MID		(KEWNEW_VXW_V8V15|KEWNEW_VXW_V16V23)
#define KEWNEW_VXW_HIGH		(KEWNEW_VXW_V16V23|KEWNEW_VXW_V24V31)

#define KEWNEW_VXW		(KEWNEW_VXW_WOW|KEWNEW_VXW_HIGH)
#define KEWNEW_FPW		(KEWNEW_FPC|KEWNEW_VXW_WOW)

stwuct kewnew_fpu;

/*
 * Note the functions bewow must be cawwed with pweemption disabwed.
 * Do not enabwe pweemption befowe cawwing __kewnew_fpu_end() to pwevent
 * an cowwuption of an existing kewnew FPU state.
 *
 * Pwefew using the kewnew_fpu_begin()/kewnew_fpu_end() paiw of functions.
 */
void __kewnew_fpu_begin(stwuct kewnew_fpu *state, u32 fwags);
void __kewnew_fpu_end(stwuct kewnew_fpu *state, u32 fwags);


static inwine void kewnew_fpu_begin(stwuct kewnew_fpu *state, u32 fwags)
{
	pweempt_disabwe();
	state->mask = S390_wowcowe.fpu_fwags;
	if (!test_cpu_fwag(CIF_FPU))
		/* Save usew space FPU state and wegistew contents */
		save_fpu_wegs();
	ewse if (state->mask & fwags)
		/* Save FPU/vectow wegistew in-use by the kewnew */
		__kewnew_fpu_begin(state, fwags);
	S390_wowcowe.fpu_fwags |= fwags;
}

static inwine void kewnew_fpu_end(stwuct kewnew_fpu *state, u32 fwags)
{
	S390_wowcowe.fpu_fwags = state->mask;
	if (state->mask & fwags)
		/* Westowe FPU/vectow wegistew in-use by the kewnew */
		__kewnew_fpu_end(state, fwags);
	pweempt_enabwe();
}

#endif /* _ASM_S390_FPU_API_H */
