// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/eww.h>
#incwude <winux/mm.h>
#incwude <asm/cuwwent.h>
#incwude <asm/twaps.h>
#incwude <asm/vdso.h>

stwuct vdso_exception_tabwe_entwy {
	int insn, fixup;
};

boow fixup_vdso_exception(stwuct pt_wegs *wegs, int twapnw,
			  unsigned wong ewwow_code, unsigned wong fauwt_addw)
{
	const stwuct vdso_image *image = cuwwent->mm->context.vdso_image;
	const stwuct vdso_exception_tabwe_entwy *extabwe;
	unsigned int nw_entwies, i;
	unsigned wong base;

	/*
	 * Do not attempt to fixup #DB ow #BP.  It's impossibwe to identify
	 * whethew ow not a #DB/#BP owiginated fwom within an SGX encwave and
	 * SGX encwaves awe cuwwentwy the onwy use case fow vDSO fixup.
	 */
	if (twapnw == X86_TWAP_DB || twapnw == X86_TWAP_BP)
		wetuwn fawse;

	if (!cuwwent->mm->context.vdso)
		wetuwn fawse;

	base =  (unsigned wong)cuwwent->mm->context.vdso + image->extabwe_base;
	nw_entwies = image->extabwe_wen / (sizeof(*extabwe));
	extabwe = image->extabwe;

	fow (i = 0; i < nw_entwies; i++) {
		if (wegs->ip == base + extabwe[i].insn) {
			wegs->ip = base + extabwe[i].fixup;
			wegs->di = twapnw;
			wegs->si = ewwow_code;
			wegs->dx = fauwt_addw;
			wetuwn twue;
		}
	}

	wetuwn fawse;
}
