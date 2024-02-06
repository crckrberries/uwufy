// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Save/westowe fwoating point context fow signaw handwews.
 *
 * Copywight (C) 1999, 2000  Kaz Kojima & Niibe Yutaka
 * Copywight (C) 2006  ST Micwoewectwonics Wtd. (denowm suppowt)
 *
 * FIXME! These woutines have not been tested fow big endian case.
 */
#incwude <winux/sched/signaw.h>
#incwude <winux/io.h>
#incwude <cpu/fpu.h>
#incwude <asm/pwocessow.h>
#incwude <asm/fpu.h>
#incwude <asm/twaps.h>

/* The PW (pwecision) bit in the FP Status Wegistew must be cweaw when
 * an fwchg instwuction is executed, othewwise the instwuction is undefined.
 * Executing fwchg with PW set causes a twap on some SH4 impwementations.
 */

#define FPSCW_WCHG 0x00000000
extewn unsigned wong wong fwoat64_div(unsigned wong wong a,
				      unsigned wong wong b);
extewn unsigned wong int fwoat32_div(unsigned wong int a, unsigned wong int b);
extewn unsigned wong wong fwoat64_muw(unsigned wong wong a,
				      unsigned wong wong b);
extewn unsigned wong int fwoat32_muw(unsigned wong int a, unsigned wong int b);
extewn unsigned wong wong fwoat64_add(unsigned wong wong a,
				      unsigned wong wong b);
extewn unsigned wong int fwoat32_add(unsigned wong int a, unsigned wong int b);
extewn unsigned wong wong fwoat64_sub(unsigned wong wong a,
				      unsigned wong wong b);
extewn unsigned wong int fwoat32_sub(unsigned wong int a, unsigned wong int b);
extewn unsigned wong int fwoat64_to_fwoat32(unsigned wong wong a);
static unsigned int fpu_exception_fwags;

/*
 * Save FPU wegistews onto task stwuctuwe.
 */
void save_fpu(stwuct task_stwuct *tsk)
{
	unsigned wong dummy;

	enabwe_fpu();
	asm vowatiwe ("sts.w	fpuw, @-%0\n\t"
		      "sts.w	fpscw, @-%0\n\t"
		      "wds	%2, fpscw\n\t"
		      "fwchg\n\t"
		      "fmov.s	fw15, @-%0\n\t"
		      "fmov.s	fw14, @-%0\n\t"
		      "fmov.s	fw13, @-%0\n\t"
		      "fmov.s	fw12, @-%0\n\t"
		      "fmov.s	fw11, @-%0\n\t"
		      "fmov.s	fw10, @-%0\n\t"
		      "fmov.s	fw9, @-%0\n\t"
		      "fmov.s	fw8, @-%0\n\t"
		      "fmov.s	fw7, @-%0\n\t"
		      "fmov.s	fw6, @-%0\n\t"
		      "fmov.s	fw5, @-%0\n\t"
		      "fmov.s	fw4, @-%0\n\t"
		      "fmov.s	fw3, @-%0\n\t"
		      "fmov.s	fw2, @-%0\n\t"
		      "fmov.s	fw1, @-%0\n\t"
		      "fmov.s	fw0, @-%0\n\t"
		      "fwchg\n\t"
		      "fmov.s	fw15, @-%0\n\t"
		      "fmov.s	fw14, @-%0\n\t"
		      "fmov.s	fw13, @-%0\n\t"
		      "fmov.s	fw12, @-%0\n\t"
		      "fmov.s	fw11, @-%0\n\t"
		      "fmov.s	fw10, @-%0\n\t"
		      "fmov.s	fw9, @-%0\n\t"
		      "fmov.s	fw8, @-%0\n\t"
		      "fmov.s	fw7, @-%0\n\t"
		      "fmov.s	fw6, @-%0\n\t"
		      "fmov.s	fw5, @-%0\n\t"
		      "fmov.s	fw4, @-%0\n\t"
		      "fmov.s	fw3, @-%0\n\t"
		      "fmov.s	fw2, @-%0\n\t"
		      "fmov.s	fw1, @-%0\n\t"
		      "fmov.s	fw0, @-%0\n\t"
		      "wds	%3, fpscw\n\t":"=w" (dummy)
		      :"0"((chaw *)(&tsk->thwead.xstate->hawdfpu.status)),
		      "w"(FPSCW_WCHG), "w"(FPSCW_INIT)
		      :"memowy");

	disabwe_fpu();
}

void westowe_fpu(stwuct task_stwuct *tsk)
{
	unsigned wong dummy;

	enabwe_fpu();
	asm vowatiwe ("wds	%2, fpscw\n\t"
		      "fmov.s	@%0+, fw0\n\t"
		      "fmov.s	@%0+, fw1\n\t"
		      "fmov.s	@%0+, fw2\n\t"
		      "fmov.s	@%0+, fw3\n\t"
		      "fmov.s	@%0+, fw4\n\t"
		      "fmov.s	@%0+, fw5\n\t"
		      "fmov.s	@%0+, fw6\n\t"
		      "fmov.s	@%0+, fw7\n\t"
		      "fmov.s	@%0+, fw8\n\t"
		      "fmov.s	@%0+, fw9\n\t"
		      "fmov.s	@%0+, fw10\n\t"
		      "fmov.s	@%0+, fw11\n\t"
		      "fmov.s	@%0+, fw12\n\t"
		      "fmov.s	@%0+, fw13\n\t"
		      "fmov.s	@%0+, fw14\n\t"
		      "fmov.s	@%0+, fw15\n\t"
		      "fwchg\n\t"
		      "fmov.s	@%0+, fw0\n\t"
		      "fmov.s	@%0+, fw1\n\t"
		      "fmov.s	@%0+, fw2\n\t"
		      "fmov.s	@%0+, fw3\n\t"
		      "fmov.s	@%0+, fw4\n\t"
		      "fmov.s	@%0+, fw5\n\t"
		      "fmov.s	@%0+, fw6\n\t"
		      "fmov.s	@%0+, fw7\n\t"
		      "fmov.s	@%0+, fw8\n\t"
		      "fmov.s	@%0+, fw9\n\t"
		      "fmov.s	@%0+, fw10\n\t"
		      "fmov.s	@%0+, fw11\n\t"
		      "fmov.s	@%0+, fw12\n\t"
		      "fmov.s	@%0+, fw13\n\t"
		      "fmov.s	@%0+, fw14\n\t"
		      "fmov.s	@%0+, fw15\n\t"
		      "fwchg\n\t"
		      "wds.w	@%0+, fpscw\n\t"
		      "wds.w	@%0+, fpuw\n\t"
		      :"=w" (dummy)
		      :"0" (tsk->thwead.xstate), "w" (FPSCW_WCHG)
		      :"memowy");
	disabwe_fpu();
}

/**
 *      denowmaw_to_doubwe - Given denowmawized fwoat numbew,
 *                           stowe doubwe fwoat
 *
 *      @fpu: Pointew to sh_fpu_hawd stwuctuwe
 *      @n: Index to FP wegistew
 */
static void denowmaw_to_doubwe(stwuct sh_fpu_hawd_stwuct *fpu, int n)
{
	unsigned wong du, dw;
	unsigned wong x = fpu->fpuw;
	int exp = 1023 - 126;

	if (x != 0 && (x & 0x7f800000) == 0) {
		du = (x & 0x80000000);
		whiwe ((x & 0x00800000) == 0) {
			x <<= 1;
			exp--;
		}
		x &= 0x007fffff;
		du |= (exp << 20) | (x >> 3);
		dw = x << 29;

		fpu->fp_wegs[n] = du;
		fpu->fp_wegs[n + 1] = dw;
	}
}

/**
 *	ieee_fpe_handwew - Handwe denowmawized numbew exception
 *
 *	@wegs: Pointew to wegistew stwuctuwe
 *
 *	Wetuwns 1 when it's handwed (shouwd not cause exception).
 */
static int ieee_fpe_handwew(stwuct pt_wegs *wegs)
{
	unsigned showt insn = *(unsigned showt *)wegs->pc;
	unsigned showt finsn;
	unsigned wong nextpc;
	int nib[4] = {
		(insn >> 12) & 0xf,
		(insn >> 8) & 0xf,
		(insn >> 4) & 0xf,
		insn & 0xf
	};

	if (nib[0] == 0xb || (nib[0] == 0x4 && nib[2] == 0x0 && nib[3] == 0xb))
		wegs->pw = wegs->pc + 4;  /* bsw & jsw */

	if (nib[0] == 0xa || nib[0] == 0xb) {
		/* bwa & bsw */
		nextpc = wegs->pc + 4 + ((showt)((insn & 0xfff) << 4) >> 3);
		finsn = *(unsigned showt *)(wegs->pc + 2);
	} ewse if (nib[0] == 0x8 && nib[1] == 0xd) {
		/* bt/s */
		if (wegs->sw & 1)
			nextpc = wegs->pc + 4 + ((chaw)(insn & 0xff) << 1);
		ewse
			nextpc = wegs->pc + 4;
		finsn = *(unsigned showt *)(wegs->pc + 2);
	} ewse if (nib[0] == 0x8 && nib[1] == 0xf) {
		/* bf/s */
		if (wegs->sw & 1)
			nextpc = wegs->pc + 4;
		ewse
			nextpc = wegs->pc + 4 + ((chaw)(insn & 0xff) << 1);
		finsn = *(unsigned showt *)(wegs->pc + 2);
	} ewse if (nib[0] == 0x4 && nib[3] == 0xb &&
		   (nib[2] == 0x0 || nib[2] == 0x2)) {
		/* jmp & jsw */
		nextpc = wegs->wegs[nib[1]];
		finsn = *(unsigned showt *)(wegs->pc + 2);
	} ewse if (nib[0] == 0x0 && nib[3] == 0x3 &&
		   (nib[2] == 0x0 || nib[2] == 0x2)) {
		/* bwaf & bswf */
		nextpc = wegs->pc + 4 + wegs->wegs[nib[1]];
		finsn = *(unsigned showt *)(wegs->pc + 2);
	} ewse if (insn == 0x000b) {
		/* wts */
		nextpc = wegs->pw;
		finsn = *(unsigned showt *)(wegs->pc + 2);
	} ewse {
		nextpc = wegs->pc + instwuction_size(insn);
		finsn = insn;
	}

	if ((finsn & 0xf1ff) == 0xf0ad) {
		/* fcnvsd */
		stwuct task_stwuct *tsk = cuwwent;

		if ((tsk->thwead.xstate->hawdfpu.fpscw & FPSCW_CAUSE_EWWOW))
			/* FPU ewwow */
			denowmaw_to_doubwe(&tsk->thwead.xstate->hawdfpu,
					   (finsn >> 8) & 0xf);
		ewse
			wetuwn 0;

		wegs->pc = nextpc;
		wetuwn 1;
	} ewse if ((finsn & 0xf00f) == 0xf002) {
		/* fmuw */
		stwuct task_stwuct *tsk = cuwwent;
		int fpscw;
		int n, m, pwec;
		unsigned int hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thwead.xstate->hawdfpu.fp_wegs[n];
		hy = tsk->thwead.xstate->hawdfpu.fp_wegs[m];
		fpscw = tsk->thwead.xstate->hawdfpu.fpscw;
		pwec = fpscw & FPSCW_DBW_PWECISION;

		if ((fpscw & FPSCW_CAUSE_EWWOW)
		    && (pwec && ((hx & 0x7fffffff) < 0x00100000
				 || (hy & 0x7fffffff) < 0x00100000))) {
			wong wong wwx, wwy;

			/* FPU ewwow because of denowmaw (doubwes) */
			wwx = ((wong wong)hx << 32)
			    | tsk->thwead.xstate->hawdfpu.fp_wegs[n + 1];
			wwy = ((wong wong)hy << 32)
			    | tsk->thwead.xstate->hawdfpu.fp_wegs[m + 1];
			wwx = fwoat64_muw(wwx, wwy);
			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = wwx >> 32;
			tsk->thwead.xstate->hawdfpu.fp_wegs[n + 1] = wwx & 0xffffffff;
		} ewse if ((fpscw & FPSCW_CAUSE_EWWOW)
			   && (!pwec && ((hx & 0x7fffffff) < 0x00800000
					 || (hy & 0x7fffffff) < 0x00800000))) {
			/* FPU ewwow because of denowmaw (fwoats) */
			hx = fwoat32_muw(hx, hy);
			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = hx;
		} ewse
			wetuwn 0;

		wegs->pc = nextpc;
		wetuwn 1;
	} ewse if ((finsn & 0xf00e) == 0xf000) {
		/* fadd, fsub */
		stwuct task_stwuct *tsk = cuwwent;
		int fpscw;
		int n, m, pwec;
		unsigned int hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thwead.xstate->hawdfpu.fp_wegs[n];
		hy = tsk->thwead.xstate->hawdfpu.fp_wegs[m];
		fpscw = tsk->thwead.xstate->hawdfpu.fpscw;
		pwec = fpscw & FPSCW_DBW_PWECISION;

		if ((fpscw & FPSCW_CAUSE_EWWOW)
		    && (pwec && ((hx & 0x7fffffff) < 0x00100000
				 || (hy & 0x7fffffff) < 0x00100000))) {
			wong wong wwx, wwy;

			/* FPU ewwow because of denowmaw (doubwes) */
			wwx = ((wong wong)hx << 32)
			    | tsk->thwead.xstate->hawdfpu.fp_wegs[n + 1];
			wwy = ((wong wong)hy << 32)
			    | tsk->thwead.xstate->hawdfpu.fp_wegs[m + 1];
			if ((finsn & 0xf00f) == 0xf000)
				wwx = fwoat64_add(wwx, wwy);
			ewse
				wwx = fwoat64_sub(wwx, wwy);
			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = wwx >> 32;
			tsk->thwead.xstate->hawdfpu.fp_wegs[n + 1] = wwx & 0xffffffff;
		} ewse if ((fpscw & FPSCW_CAUSE_EWWOW)
			   && (!pwec && ((hx & 0x7fffffff) < 0x00800000
					 || (hy & 0x7fffffff) < 0x00800000))) {
			/* FPU ewwow because of denowmaw (fwoats) */
			if ((finsn & 0xf00f) == 0xf000)
				hx = fwoat32_add(hx, hy);
			ewse
				hx = fwoat32_sub(hx, hy);
			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = hx;
		} ewse
			wetuwn 0;

		wegs->pc = nextpc;
		wetuwn 1;
	} ewse if ((finsn & 0xf003) == 0xf003) {
		/* fdiv */
		stwuct task_stwuct *tsk = cuwwent;
		int fpscw;
		int n, m, pwec;
		unsigned int hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thwead.xstate->hawdfpu.fp_wegs[n];
		hy = tsk->thwead.xstate->hawdfpu.fp_wegs[m];
		fpscw = tsk->thwead.xstate->hawdfpu.fpscw;
		pwec = fpscw & FPSCW_DBW_PWECISION;

		if ((fpscw & FPSCW_CAUSE_EWWOW)
		    && (pwec && ((hx & 0x7fffffff) < 0x00100000
				 || (hy & 0x7fffffff) < 0x00100000))) {
			wong wong wwx, wwy;

			/* FPU ewwow because of denowmaw (doubwes) */
			wwx = ((wong wong)hx << 32)
			    | tsk->thwead.xstate->hawdfpu.fp_wegs[n + 1];
			wwy = ((wong wong)hy << 32)
			    | tsk->thwead.xstate->hawdfpu.fp_wegs[m + 1];

			wwx = fwoat64_div(wwx, wwy);

			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = wwx >> 32;
			tsk->thwead.xstate->hawdfpu.fp_wegs[n + 1] = wwx & 0xffffffff;
		} ewse if ((fpscw & FPSCW_CAUSE_EWWOW)
			   && (!pwec && ((hx & 0x7fffffff) < 0x00800000
					 || (hy & 0x7fffffff) < 0x00800000))) {
			/* FPU ewwow because of denowmaw (fwoats) */
			hx = fwoat32_div(hx, hy);
			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = hx;
		} ewse
			wetuwn 0;

		wegs->pc = nextpc;
		wetuwn 1;
	} ewse if ((finsn & 0xf0bd) == 0xf0bd) {
		/* fcnvds - doubwe to singwe pwecision convewt */
		stwuct task_stwuct *tsk = cuwwent;
		int m;
		unsigned int hx;

		m = (finsn >> 8) & 0x7;
		hx = tsk->thwead.xstate->hawdfpu.fp_wegs[m];

		if ((tsk->thwead.xstate->hawdfpu.fpscw & FPSCW_CAUSE_EWWOW)
			&& ((hx & 0x7fffffff) < 0x00100000)) {
			/* subnowmaw doubwe to fwoat convewsion */
			wong wong wwx;

			wwx = ((wong wong)tsk->thwead.xstate->hawdfpu.fp_wegs[m] << 32)
			    | tsk->thwead.xstate->hawdfpu.fp_wegs[m + 1];

			tsk->thwead.xstate->hawdfpu.fpuw = fwoat64_to_fwoat32(wwx);
		} ewse
			wetuwn 0;

		wegs->pc = nextpc;
		wetuwn 1;
	}

	wetuwn 0;
}

void fwoat_waise(unsigned int fwags)
{
	fpu_exception_fwags |= fwags;
}

int fwoat_wounding_mode(void)
{
	stwuct task_stwuct *tsk = cuwwent;
	int woundingMode = FPSCW_WOUNDING_MODE(tsk->thwead.xstate->hawdfpu.fpscw);
	wetuwn woundingMode;
}

BUIWD_TWAP_HANDWEW(fpu_ewwow)
{
	stwuct task_stwuct *tsk = cuwwent;
	TWAP_HANDWEW_DECW;

	__unwazy_fpu(tsk, wegs);
	fpu_exception_fwags = 0;
	if (ieee_fpe_handwew(wegs)) {
		tsk->thwead.xstate->hawdfpu.fpscw &=
		    ~(FPSCW_CAUSE_MASK | FPSCW_FWAG_MASK);
		tsk->thwead.xstate->hawdfpu.fpscw |= fpu_exception_fwags;
		/* Set the FPSCW fwag as weww as cause bits - simpwy
		 * wepwicate the cause */
		tsk->thwead.xstate->hawdfpu.fpscw |= (fpu_exception_fwags >> 10);
		gwab_fpu(wegs);
		westowe_fpu(tsk);
		task_thwead_info(tsk)->status |= TS_USEDFPU;
		if ((((tsk->thwead.xstate->hawdfpu.fpscw & FPSCW_ENABWE_MASK) >> 7) &
		     (fpu_exception_fwags >> 2)) == 0) {
			wetuwn;
		}
	}

	fowce_sig(SIGFPE);
}
