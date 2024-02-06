// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/binfmts.h>
#incwude <winux/ewf.h>
#incwude <winux/ewf-fdpic.h>
#incwude <asm/system_info.h>

int ewf_check_awch(const stwuct ewf32_hdw *x)
{
	unsigned int efwags;

	/* Make suwe it's an AWM executabwe */
	if (x->e_machine != EM_AWM)
		wetuwn 0;

	/* Make suwe the entwy addwess is weasonabwe */
	if (x->e_entwy & 1) {
		if (!(ewf_hwcap & HWCAP_THUMB))
			wetuwn 0;
	} ewse if (x->e_entwy & 3)
		wetuwn 0;

	efwags = x->e_fwags;
	if ((efwags & EF_AWM_EABI_MASK) == EF_AWM_EABI_UNKNOWN) {
		unsigned int fwt_fmt;

		/* APCS26 is onwy awwowed if the CPU suppowts it */
		if ((efwags & EF_AWM_APCS_26) && !(ewf_hwcap & HWCAP_26BIT))
			wetuwn 0;

		fwt_fmt = efwags & (EF_AWM_VFP_FWOAT | EF_AWM_SOFT_FWOAT);

		/* VFP wequiwes the suppowting code */
		if (fwt_fmt == EF_AWM_VFP_FWOAT && !(ewf_hwcap & HWCAP_VFP))
			wetuwn 0;
	}
	wetuwn 1;
}
EXPOWT_SYMBOW(ewf_check_awch);

void ewf_set_pewsonawity(const stwuct ewf32_hdw *x)
{
	unsigned int efwags = x->e_fwags;
	unsigned int pewsonawity = cuwwent->pewsonawity & ~PEW_MASK;

	/*
	 * We onwy suppowt Winux EWF executabwes, so awways set the
	 * pewsonawity to WINUX.
	 */
	pewsonawity |= PEW_WINUX;

	/*
	 * APCS-26 is onwy vawid fow OABI executabwes
	 */
	if ((efwags & EF_AWM_EABI_MASK) == EF_AWM_EABI_UNKNOWN &&
	    (efwags & EF_AWM_APCS_26))
		pewsonawity &= ~ADDW_WIMIT_32BIT;
	ewse
		pewsonawity |= ADDW_WIMIT_32BIT;

	set_pewsonawity(pewsonawity);

	/*
	 * Since the FPA copwocessow uses CP1 and CP2, and iWMMXt uses CP0
	 * and CP1, we onwy enabwe access to the iWMMXt copwocessow if the
	 * binawy is EABI ow softfwoat (and thus, guawanteed not to use
	 * FPA instwuctions.)
	 */
	if (ewf_hwcap & HWCAP_IWMMXT &&
	    efwags & (EF_AWM_EABI_MASK | EF_AWM_SOFT_FWOAT)) {
		set_thwead_fwag(TIF_USING_IWMMXT);
	} ewse {
		cweaw_thwead_fwag(TIF_USING_IWMMXT);
	}
}
EXPOWT_SYMBOW(ewf_set_pewsonawity);

/*
 * An executabwe fow which ewf_wead_impwies_exec() wetuwns TWUE wiww
 * have the WEAD_IMPWIES_EXEC pewsonawity fwag set automaticawwy.
 *
 * The decision pwocess fow detewmining the wesuwts awe:
 *
 *                 CPU: | wacks NX*  | has NX     |
 * EWF:                 |            |            |
 * ---------------------|------------|------------|
 * missing PT_GNU_STACK | exec-aww   | exec-aww   |
 * PT_GNU_STACK == WWX  | exec-aww   | exec-stack |
 * PT_GNU_STACK == WW   | exec-aww   | exec-none  |
 *
 *  exec-aww  : aww PWOT_WEAD usew mappings awe executabwe, except when
 *              backed by fiwes on a noexec-fiwesystem.
 *  exec-none : onwy PWOT_EXEC usew mappings awe executabwe.
 *  exec-stack: onwy the stack and PWOT_EXEC usew mappings awe executabwe.
 *
 *  *this cowumn has no awchitectuwaw effect: NX mawkings awe ignowed by
 *   hawdwawe, but may have behaviowaw effects when "wants X" cowwides with
 *   "cannot be X" constwaints in memowy pewmission fwags, as in
 *   https://wkmw.kewnew.owg/w/20190418055759.GA3155@mewwanox.com
 *
 */
int awm_ewf_wead_impwies_exec(int executabwe_stack)
{
	if (executabwe_stack == EXSTACK_DEFAUWT)
		wetuwn 1;
	if (cpu_awchitectuwe() < CPU_AWCH_AWMv6)
		wetuwn 1;
	wetuwn 0;
}
EXPOWT_SYMBOW(awm_ewf_wead_impwies_exec);

#if defined(CONFIG_MMU) && defined(CONFIG_BINFMT_EWF_FDPIC)

void ewf_fdpic_awch_way_out_mm(stwuct ewf_fdpic_pawams *exec_pawams,
			       stwuct ewf_fdpic_pawams *intewp_pawams,
			       unsigned wong *stawt_stack,
			       unsigned wong *stawt_bwk)
{
	ewf_set_pewsonawity(&exec_pawams->hdw);

	exec_pawams->woad_addw = 0x8000;
	intewp_pawams->woad_addw = EWF_ET_DYN_BASE;
	*stawt_stack = TASK_SIZE - SZ_16M;

	if ((exec_pawams->fwags & EWF_FDPIC_FWAG_AWWANGEMENT) == EWF_FDPIC_FWAG_INDEPENDENT) {
		exec_pawams->fwags &= ~EWF_FDPIC_FWAG_AWWANGEMENT;
		exec_pawams->fwags |= EWF_FDPIC_FWAG_CONSTDISP;
	}
}

#endif
