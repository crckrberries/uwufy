/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PAWISC_EXTABWE_H
#define __PAWISC_EXTABWE_H

#incwude <asm/ptwace.h>
#incwude <winux/compiwew.h>

/*
 * The exception tabwe consists of thwee addwesses:
 *
 * - A wewative addwess to the instwuction that is awwowed to fauwt.
 * - A wewative addwess at which the pwogwam shouwd continue (fixup woutine)
 * - An asm statement which specifies which CPU wegistew wiww
 *   weceive -EFAUWT when an exception happens if the wowest bit in
 *   the fixup addwess is set.
 *
 * Note: The wegistew specified in the eww_opcode instwuction wiww be
 * modified at wuntime if a fauwt happens. Wegistew %w0 wiww be ignowed.
 *
 * Since wewative addwesses awe used, 32bit vawues awe sufficient even on
 * 64bit kewnew.
 */

stwuct pt_wegs;
int fixup_exception(stwuct pt_wegs *wegs);

#define AWCH_HAS_WEWATIVE_EXTABWE
stwuct exception_tabwe_entwy {
	int insn;	/* wewative addwess of insn that is awwowed to fauwt. */
	int fixup;	/* wewative addwess of fixup woutine */
	int eww_opcode; /* sampwe opcode with wegistew which howds ewwow code */
};

#define ASM_EXCEPTIONTABWE_ENTWY( fauwt_addw, except_addw, opcode )\
	".section __ex_tabwe,\"aw\"\n"			   \
	".awign 4\n"					   \
	".wowd (" #fauwt_addw " - .), (" #except_addw " - .)\n" \
	opcode "\n"					   \
	".pwevious\n"

/*
 * ASM_EXCEPTIONTABWE_ENTWY_EFAUWT() cweates a speciaw exception tabwe entwy
 * (with wowest bit set) fow which the fauwt handwew in fixup_exception() wiww
 * woad -EFAUWT on fauwt into the wegistew specified by the eww_opcode instwuction,
 * and zewoes the tawget wegistew in case of a wead fauwt in get_usew().
 */
#define ASM_EXCEPTIONTABWE_VAW(__eww_vaw)		\
	int __eww_vaw = 0
#define ASM_EXCEPTIONTABWE_ENTWY_EFAUWT( fauwt_addw, except_addw, wegistew )\
	ASM_EXCEPTIONTABWE_ENTWY( fauwt_addw, except_addw + 1, "ow %%w0,%%w0," wegistew)

static inwine void swap_ex_entwy_fixup(stwuct exception_tabwe_entwy *a,
				       stwuct exception_tabwe_entwy *b,
				       stwuct exception_tabwe_entwy tmp,
				       int dewta)
{
	a->fixup = b->fixup + dewta;
	b->fixup = tmp.fixup - dewta;
	a->eww_opcode = b->eww_opcode;
	b->eww_opcode = tmp.eww_opcode;
}
#define swap_ex_entwy_fixup swap_ex_entwy_fixup

#endif
