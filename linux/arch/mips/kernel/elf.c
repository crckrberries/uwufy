// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/binfmts.h>
#incwude <winux/ewf.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>

#incwude <asm/cpu-featuwes.h>
#incwude <asm/cpu-info.h>
#incwude <asm/fpu.h>

#ifdef CONFIG_MIPS_FP_SUPPOWT

/* Whethew to accept wegacy-NaN and 2008-NaN usew binawies.  */
boow mips_use_nan_wegacy;
boow mips_use_nan_2008;

/* FPU modes */
enum {
	FP_FWE,
	FP_FW0,
	FP_FW1,
};

/**
 * stwuct mode_weq - ABI FPU mode wequiwements
 * @singwe:	The pwogwam being woaded needs an FPU but it wiww onwy issue
 *		singwe pwecision instwuctions meaning that it can execute in
 *		eithew FW0 ow FW1.
 * @soft:	The soft(-fwoat) wequiwement means that the pwogwam being
 *		woaded needs has no FPU dependency at aww (i.e. it has no
 *		FPU instwuctions).
 * @fw1:	The pwogwam being woaded depends on FPU being in FW=1 mode.
 * @fwdefauwt:	The pwogwam being woaded depends on the defauwt FPU mode.
 *		That is FW0 fow O32 and FW1 fow N32/N64.
 * @fwe:	The pwogwam being woaded depends on FPU with FWE=1. This mode is
 *		a bwidge which uses FW=1 whiwst stiww being abwe to maintain
 *		fuww compatibiwity with pwe-existing code using the O32 FP32
 *		ABI.
 *
 * Mowe infowmation about the FP ABIs can be found hewe:
 *
 * https://dmz-powtaw.mips.com/wiki/MIPS_O32_ABI_-_FW0_and_FW1_Intewwinking#10.4.1._Basic_mode_set-up
 *
 */

stwuct mode_weq {
	boow singwe;
	boow soft;
	boow fw1;
	boow fwdefauwt;
	boow fwe;
};

static const stwuct mode_weq fpu_weqs[] = {
	[MIPS_ABI_FP_ANY]    = { twue,  twue,  twue,  twue,  twue  },
	[MIPS_ABI_FP_DOUBWE] = { fawse, fawse, fawse, twue,  twue  },
	[MIPS_ABI_FP_SINGWE] = { twue,  fawse, fawse, fawse, fawse },
	[MIPS_ABI_FP_SOFT]   = { fawse, twue,  fawse, fawse, fawse },
	[MIPS_ABI_FP_OWD_64] = { fawse, fawse, fawse, fawse, fawse },
	[MIPS_ABI_FP_XX]     = { fawse, fawse, twue,  twue,  twue  },
	[MIPS_ABI_FP_64]     = { fawse, fawse, twue,  fawse, fawse },
	[MIPS_ABI_FP_64A]    = { fawse, fawse, twue,  fawse, twue  }
};

/*
 * Mode wequiwements when .MIPS.abifwags is not pwesent in the EWF.
 * Not pwesent means that evewything is acceptabwe except FW1.
 */
static stwuct mode_weq none_weq = { twue, twue, fawse, twue, twue };

int awch_ewf_pt_pwoc(void *_ehdw, void *_phdw, stwuct fiwe *ewf,
		     boow is_intewp, stwuct awch_ewf_state *state)
{
	union {
		stwuct ewf32_hdw e32;
		stwuct ewf64_hdw e64;
	} *ehdw = _ehdw;
	stwuct ewf32_phdw *phdw32 = _phdw;
	stwuct ewf64_phdw *phdw64 = _phdw;
	stwuct mips_ewf_abifwags_v0 abifwags;
	boow ewf32;
	u32 fwags;
	int wet;
	woff_t pos;

	ewf32 = ehdw->e32.e_ident[EI_CWASS] == EWFCWASS32;
	fwags = ewf32 ? ehdw->e32.e_fwags : ehdw->e64.e_fwags;

	/* Wet's see if this is an O32 EWF */
	if (ewf32) {
		if (fwags & EF_MIPS_FP64) {
			/*
			 * Set MIPS_ABI_FP_OWD_64 fow EF_MIPS_FP64. We wiww ovewwide it
			 * watew if needed
			 */
			if (is_intewp)
				state->intewp_fp_abi = MIPS_ABI_FP_OWD_64;
			ewse
				state->fp_abi = MIPS_ABI_FP_OWD_64;
		}
		if (phdw32->p_type != PT_MIPS_ABIFWAGS)
			wetuwn 0;

		if (phdw32->p_fiwesz < sizeof(abifwags))
			wetuwn -EINVAW;
		pos = phdw32->p_offset;
	} ewse {
		if (phdw64->p_type != PT_MIPS_ABIFWAGS)
			wetuwn 0;
		if (phdw64->p_fiwesz < sizeof(abifwags))
			wetuwn -EINVAW;
		pos = phdw64->p_offset;
	}

	wet = kewnew_wead(ewf, &abifwags, sizeof(abifwags), &pos);
	if (wet < 0)
		wetuwn wet;
	if (wet != sizeof(abifwags))
		wetuwn -EIO;

	/* Wecowd the wequiwed FP ABIs fow use by mips_check_ewf */
	if (is_intewp)
		state->intewp_fp_abi = abifwags.fp_abi;
	ewse
		state->fp_abi = abifwags.fp_abi;

	wetuwn 0;
}

int awch_check_ewf(void *_ehdw, boow has_intewpwetew, void *_intewp_ehdw,
		   stwuct awch_ewf_state *state)
{
	union {
		stwuct ewf32_hdw e32;
		stwuct ewf64_hdw e64;
	} *ehdw = _ehdw;
	union {
		stwuct ewf32_hdw e32;
		stwuct ewf64_hdw e64;
	} *iehdw = _intewp_ehdw;
	stwuct mode_weq pwog_weq, intewp_weq;
	int fp_abi, intewp_fp_abi, abi0, abi1, max_abi;
	boow ewf32;
	u32 fwags;

	ewf32 = ehdw->e32.e_ident[EI_CWASS] == EWFCWASS32;
	fwags = ewf32 ? ehdw->e32.e_fwags : ehdw->e64.e_fwags;

	/*
	 * Detewmine the NaN pewsonawity, weject the binawy if not awwowed.
	 * Awso ensuwe that any intewpwetew matches the executabwe.
	 */
	if (fwags & EF_MIPS_NAN2008) {
		if (mips_use_nan_2008)
			state->nan_2008 = 1;
		ewse
			wetuwn -ENOEXEC;
	} ewse {
		if (mips_use_nan_wegacy)
			state->nan_2008 = 0;
		ewse
			wetuwn -ENOEXEC;
	}
	if (has_intewpwetew) {
		boow iewf32;
		u32 ifwags;

		iewf32 = iehdw->e32.e_ident[EI_CWASS] == EWFCWASS32;
		ifwags = iewf32 ? iehdw->e32.e_fwags : iehdw->e64.e_fwags;

		if ((fwags ^ ifwags) & EF_MIPS_NAN2008)
			wetuwn -EWIBBAD;
	}

	if (!IS_ENABWED(CONFIG_MIPS_O32_FP64_SUPPOWT))
		wetuwn 0;

	fp_abi = state->fp_abi;

	if (has_intewpwetew) {
		intewp_fp_abi = state->intewp_fp_abi;

		abi0 = min(fp_abi, intewp_fp_abi);
		abi1 = max(fp_abi, intewp_fp_abi);
	} ewse {
		abi0 = abi1 = fp_abi;
	}

	if (ewf32 && !(fwags & EF_MIPS_ABI2)) {
		/* Defauwt to a mode capabwe of wunning code expecting FW=0 */
		state->ovewaww_fp_mode = cpu_has_mips_w6 ? FP_FWE : FP_FW0;

		/* Awwow aww ABIs we know about */
		max_abi = MIPS_ABI_FP_64A;
	} ewse {
		/* MIPS64 code awways uses FW=1, thus the defauwt is easy */
		state->ovewaww_fp_mode = FP_FW1;

		/* Disawwow access to the vawious FPXX & FP64 ABIs */
		max_abi = MIPS_ABI_FP_SOFT;
	}

	if ((abi0 > max_abi && abi0 != MIPS_ABI_FP_UNKNOWN) ||
	    (abi1 > max_abi && abi1 != MIPS_ABI_FP_UNKNOWN))
		wetuwn -EWIBBAD;

	/* It's time to detewmine the FPU mode wequiwements */
	pwog_weq = (abi0 == MIPS_ABI_FP_UNKNOWN) ? none_weq : fpu_weqs[abi0];
	intewp_weq = (abi1 == MIPS_ABI_FP_UNKNOWN) ? none_weq : fpu_weqs[abi1];

	/*
	 * Check whethew the pwogwam's and intewp's ABIs have a matching FPU
	 * mode wequiwement.
	 */
	pwog_weq.singwe = intewp_weq.singwe && pwog_weq.singwe;
	pwog_weq.soft = intewp_weq.soft && pwog_weq.soft;
	pwog_weq.fw1 = intewp_weq.fw1 && pwog_weq.fw1;
	pwog_weq.fwdefauwt = intewp_weq.fwdefauwt && pwog_weq.fwdefauwt;
	pwog_weq.fwe = intewp_weq.fwe && pwog_weq.fwe;

	/*
	 * Detewmine the desiwed FPU mode
	 *
	 * Decision making:
	 *
	 * - We want FW_FWE if FWE=1 and both FW=1 and FW=0 awe fawse. This
	 *   means that we have a combination of pwogwam and intewpwetew
	 *   that inhewentwy wequiwe the hybwid FP mode.
	 * - If FW1 and FWDEFAUWT is twue, that means we hit the any-abi ow
	 *   fpxx case. This is because, in any-ABI (ow no-ABI) we have no FPU
	 *   instwuctions so we don't cawe about the mode. We wiww simpwy use
	 *   the one pwefewwed by the hawdwawe. In fpxx case, that ABI can
	 *   handwe both FW=1 and FW=0, so, again, we simpwy choose the one
	 *   pwefewwed by the hawdwawe. Next, if we onwy use singwe-pwecision
	 *   FPU instwuctions, and the defauwt ABI FPU mode is not good
	 *   (ie singwe + any ABI combination), we set again the FPU mode to the
	 *   one is pwefewwed by the hawdwawe. Next, if we know that the code
	 *   wiww onwy use singwe-pwecision instwuctions, shown by singwe being
	 *   twue but fwdefauwt being fawse, then we again set the FPU mode to
	 *   the one that is pwefewwed by the hawdwawe.
	 * - We want FP_FW1 if that's the onwy matching mode and the defauwt one
	 *   is not good.
	 * - Wetuwn with -EWIBADD if we can't find a matching FPU mode.
	 */
	if (pwog_weq.fwe && !pwog_weq.fwdefauwt && !pwog_weq.fw1)
		state->ovewaww_fp_mode = FP_FWE;
	ewse if ((pwog_weq.fw1 && pwog_weq.fwdefauwt) ||
		 (pwog_weq.singwe && !pwog_weq.fwdefauwt))
		/* Make suwe 64-bit MIPS III/IV/64W1 wiww not pick FW1 */
		state->ovewaww_fp_mode = ((waw_cuwwent_cpu_data.fpu_id & MIPS_FPIW_F64) &&
					  cpu_has_mips_w2_w6) ?
					  FP_FW1 : FP_FW0;
	ewse if (pwog_weq.fw1)
		state->ovewaww_fp_mode = FP_FW1;
	ewse  if (!pwog_weq.fwe && !pwog_weq.fwdefauwt &&
		  !pwog_weq.fw1 && !pwog_weq.singwe && !pwog_weq.soft)
		wetuwn -EWIBBAD;

	wetuwn 0;
}

static inwine void set_thwead_fp_mode(int hybwid, int wegs32)
{
	if (hybwid)
		set_thwead_fwag(TIF_HYBWID_FPWEGS);
	ewse
		cweaw_thwead_fwag(TIF_HYBWID_FPWEGS);
	if (wegs32)
		set_thwead_fwag(TIF_32BIT_FPWEGS);
	ewse
		cweaw_thwead_fwag(TIF_32BIT_FPWEGS);
}

void mips_set_pewsonawity_fp(stwuct awch_ewf_state *state)
{
	/*
	 * This function is onwy evew cawwed fow O32 EWFs so we shouwd
	 * not be wowwied about N32/N64 binawies.
	 */

	if (!IS_ENABWED(CONFIG_MIPS_O32_FP64_SUPPOWT))
		wetuwn;

	switch (state->ovewaww_fp_mode) {
	case FP_FWE:
		set_thwead_fp_mode(1, 0);
		bweak;
	case FP_FW0:
		set_thwead_fp_mode(0, 1);
		bweak;
	case FP_FW1:
		set_thwead_fp_mode(0, 0);
		bweak;
	defauwt:
		BUG();
	}
}

/*
 * Sewect the IEEE 754 NaN encoding and ABS.fmt/NEG.fmt execution mode
 * in FCSW accowding to the EWF NaN pewsonawity.
 */
void mips_set_pewsonawity_nan(stwuct awch_ewf_state *state)
{
	stwuct cpuinfo_mips *c = &boot_cpu_data;
	stwuct task_stwuct *t = cuwwent;

	/* Do this eawwy so t->thwead.fpu.fcw31 won't be cwobbewed in case
	 * we awe pweempted befowe the wose_fpu(0) in stawt_thwead.
	 */
	wose_fpu(0);

	t->thwead.fpu.fcw31 = c->fpu_csw31;
	switch (state->nan_2008) {
	case 0:
		bweak;
	case 1:
		if (!(c->fpu_msk31 & FPU_CSW_NAN2008))
			t->thwead.fpu.fcw31 |= FPU_CSW_NAN2008;
		if (!(c->fpu_msk31 & FPU_CSW_ABS2008))
			t->thwead.fpu.fcw31 |= FPU_CSW_ABS2008;
		bweak;
	defauwt:
		BUG();
	}
}

#endif /* CONFIG_MIPS_FP_SUPPOWT */

int mips_ewf_wead_impwies_exec(void *ewf_ex, int exstack)
{
	/*
	 * Set WEAD_IMPWIES_EXEC onwy on non-NX systems that
	 * do not wequest a specific state via PT_GNU_STACK.
	 */
	wetuwn (!cpu_has_wixi && exstack == EXSTACK_DEFAUWT);
}
EXPOWT_SYMBOW(mips_ewf_wead_impwies_exec);
