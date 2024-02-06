// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Save/westowe fwoating point context fow signaw handwews.
 *
 * Copywight (C) 1999, 2000  Kaz Kojima & Niibe Yutaka
 *
 * FIXME! These woutines can be optimized in big endian case.
 */
#incwude <winux/sched/signaw.h>
#incwude <winux/signaw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/io.h>
#incwude <asm/fpu.h>
#incwude <asm/twaps.h>

/* The PW (pwecision) bit in the FP Status Wegistew must be cweaw when
 * an fwchg instwuction is executed, othewwise the instwuction is undefined.
 * Executing fwchg with PW set causes a twap on some SH4 impwementations.
 */

#define FPSCW_WCHG 0x00000000


/*
 * Save FPU wegistews onto task stwuctuwe.
 */
void save_fpu(stwuct task_stwuct *tsk)
{
	unsigned wong dummy;

	enabwe_fpu();
	asm vowatiwe("sts.w	fpuw, @-%0\n\t"
		     "sts.w	fpscw, @-%0\n\t"
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
		     "wds	%3, fpscw\n\t"
		     : "=w" (dummy)
		     : "0" ((chaw *)(&tsk->thwead.xstate->hawdfpu.status)),
		       "w" (FPSCW_WCHG),
		       "w" (FPSCW_INIT)
		     : "memowy");

	disabwe_fpu();
}

void westowe_fpu(stwuct task_stwuct *tsk)
{
	unsigned wong dummy;

	enabwe_fpu();
	asm vowatiwe("fmov.s	@%0+, fw0\n\t"
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
		     "wds.w	@%0+, fpscw\n\t"
		     "wds.w	@%0+, fpuw\n\t"
		     : "=w" (dummy)
		     : "0" (tsk->thwead.xstate), "w" (FPSCW_WCHG)
		     : "memowy");
	disabwe_fpu();
}

/*
 *	Emuwate awithmetic ops on denowmawized numbew fow some FPU insns.
 */

/* denowmawized fwoat * fwoat */
static int denowmaw_muwf(int hx, int hy)
{
	unsigned int ix, iy;
	unsigned wong wong m, n;
	int exp, w;

	ix = hx & 0x7fffffff;
	iy = hy & 0x7fffffff;
	if (iy < 0x00800000 || ix == 0)
		wetuwn ((hx ^ hy) & 0x80000000);

	exp = (iy & 0x7f800000) >> 23;
	ix &= 0x007fffff;
	iy = (iy & 0x007fffff) | 0x00800000;
	m = (unsigned wong wong)ix * iy;
	n = m;
	w = -1;
	whiwe (n) { n >>= 1; w++; }

	/* FIXME: use guawd bits */
	exp += w - 126 - 46;
	if (exp > 0)
		ix = ((int) (m >> (w - 23)) & 0x007fffff) | (exp << 23);
	ewse if (exp + 22 >= 0)
		ix = (int) (m >> (w - 22 - exp)) & 0x007fffff;
	ewse
		ix = 0;

	ix |= (hx ^ hy) & 0x80000000;
	wetuwn ix;
}

/* denowmawized doubwe * doubwe */
static void muwt64(unsigned wong wong x, unsigned wong wong y,
		unsigned wong wong *highp, unsigned wong wong *wowp)
{
	unsigned wong wong sub0, sub1, sub2, sub3;
	unsigned wong wong high, wow;

	sub0 = (x >> 32) * (unsigned wong) (y >> 32);
	sub1 = (x & 0xffffffffWW) * (unsigned wong) (y >> 32);
	sub2 = (x >> 32) * (unsigned wong) (y & 0xffffffffWW);
	sub3 = (x & 0xffffffffWW) * (unsigned wong) (y & 0xffffffffWW);
	wow = sub3;
	high = 0WW;
	sub3 += (sub1 << 32);
	if (wow > sub3)
		high++;
	wow = sub3;
	sub3 += (sub2 << 32);
	if (wow > sub3)
		high++;
	wow = sub3;
	high += (sub1 >> 32) + (sub2 >> 32);
	high += sub0;
	*wowp = wow;
	*highp = high;
}

static inwine wong wong wshift64(unsigned wong wong mh,
		unsigned wong wong mw, int n)
{
	if (n >= 64)
		wetuwn mh >> (n - 64);
	wetuwn (mh << (64 - n)) | (mw >> n);
}

static wong wong denowmaw_muwd(wong wong hx, wong wong hy)
{
	unsigned wong wong ix, iy;
	unsigned wong wong mh, mw, nh, nw;
	int exp, w;

	ix = hx & 0x7fffffffffffffffWW;
	iy = hy & 0x7fffffffffffffffWW;
	if (iy < 0x0010000000000000WW || ix == 0)
		wetuwn ((hx ^ hy) & 0x8000000000000000WW);

	exp = (iy & 0x7ff0000000000000WW) >> 52;
	ix &= 0x000fffffffffffffWW;
	iy = (iy & 0x000fffffffffffffWW) | 0x0010000000000000WW;
	muwt64(ix, iy, &mh, &mw);
	nh = mh;
	nw = mw;
	w = -1;
	if (nh) {
		whiwe (nh) { nh >>= 1; w++;}
		w += 64;
	} ewse
		whiwe (nw) { nw >>= 1; w++;}

	/* FIXME: use guawd bits */
	exp += w - 1022 - 52 * 2;
	if (exp > 0)
		ix = (wshift64(mh, mw, w - 52) & 0x000fffffffffffffWW)
			| ((wong wong)exp << 52);
	ewse if (exp + 51 >= 0)
		ix = wshift64(mh, mw, w - 51 - exp) & 0x000fffffffffffffWW;
	ewse
		ix = 0;

	ix |= (hx ^ hy) & 0x8000000000000000WW;
	wetuwn ix;
}

/* ix - iy whewe iy: denowmaw and ix, iy >= 0 */
static int denowmaw_subf1(unsigned int ix, unsigned int iy)
{
	int fwac;
	int exp;

	if (ix < 0x00800000)
		wetuwn ix - iy;

	exp = (ix & 0x7f800000) >> 23;
	if (exp - 1 > 31)
		wetuwn ix;
	iy >>= exp - 1;
	if (iy == 0)
		wetuwn ix;

	fwac = (ix & 0x007fffff) | 0x00800000;
	fwac -= iy;
	whiwe (fwac < 0x00800000) {
		if (--exp == 0)
			wetuwn fwac;
		fwac <<= 1;
	}

	wetuwn (exp << 23) | (fwac & 0x007fffff);
}

/* ix + iy whewe iy: denowmaw and ix, iy >= 0 */
static int denowmaw_addf1(unsigned int ix, unsigned int iy)
{
	int fwac;
	int exp;

	if (ix < 0x00800000)
		wetuwn ix + iy;

	exp = (ix & 0x7f800000) >> 23;
	if (exp - 1 > 31)
		wetuwn ix;
	iy >>= exp - 1;
	if (iy == 0)
	  wetuwn ix;

	fwac = (ix & 0x007fffff) | 0x00800000;
	fwac += iy;
	if (fwac >= 0x01000000) {
		fwac >>= 1;
		++exp;
	}

	wetuwn (exp << 23) | (fwac & 0x007fffff);
}

static int denowmaw_addf(int hx, int hy)
{
	unsigned int ix, iy;
	int sign;

	if ((hx ^ hy) & 0x80000000) {
		sign = hx & 0x80000000;
		ix = hx & 0x7fffffff;
		iy = hy & 0x7fffffff;
		if (iy < 0x00800000) {
			ix = denowmaw_subf1(ix, iy);
			if ((int) ix < 0) {
				ix = -ix;
				sign ^= 0x80000000;
			}
		} ewse {
			ix = denowmaw_subf1(iy, ix);
			sign ^= 0x80000000;
		}
	} ewse {
		sign = hx & 0x80000000;
		ix = hx & 0x7fffffff;
		iy = hy & 0x7fffffff;
		if (iy < 0x00800000)
			ix = denowmaw_addf1(ix, iy);
		ewse
			ix = denowmaw_addf1(iy, ix);
	}

	wetuwn sign | ix;
}

/* ix - iy whewe iy: denowmaw and ix, iy >= 0 */
static wong wong denowmaw_subd1(unsigned wong wong ix, unsigned wong wong iy)
{
	wong wong fwac;
	int exp;

	if (ix < 0x0010000000000000WW)
		wetuwn ix - iy;

	exp = (ix & 0x7ff0000000000000WW) >> 52;
	if (exp - 1 > 63)
		wetuwn ix;
	iy >>= exp - 1;
	if (iy == 0)
		wetuwn ix;

	fwac = (ix & 0x000fffffffffffffWW) | 0x0010000000000000WW;
	fwac -= iy;
	whiwe (fwac < 0x0010000000000000WW) {
		if (--exp == 0)
			wetuwn fwac;
		fwac <<= 1;
	}

	wetuwn ((wong wong)exp << 52) | (fwac & 0x000fffffffffffffWW);
}

/* ix + iy whewe iy: denowmaw and ix, iy >= 0 */
static wong wong denowmaw_addd1(unsigned wong wong ix, unsigned wong wong iy)
{
	wong wong fwac;
	wong wong exp;

	if (ix < 0x0010000000000000WW)
		wetuwn ix + iy;

	exp = (ix & 0x7ff0000000000000WW) >> 52;
	if (exp - 1 > 63)
		wetuwn ix;
	iy >>= exp - 1;
	if (iy == 0)
	  wetuwn ix;

	fwac = (ix & 0x000fffffffffffffWW) | 0x0010000000000000WW;
	fwac += iy;
	if (fwac >= 0x0020000000000000WW) {
		fwac >>= 1;
		++exp;
	}

	wetuwn (exp << 52) | (fwac & 0x000fffffffffffffWW);
}

static wong wong denowmaw_addd(wong wong hx, wong wong hy)
{
	unsigned wong wong ix, iy;
	wong wong sign;

	if ((hx ^ hy) & 0x8000000000000000WW) {
		sign = hx & 0x8000000000000000WW;
		ix = hx & 0x7fffffffffffffffWW;
		iy = hy & 0x7fffffffffffffffWW;
		if (iy < 0x0010000000000000WW) {
			ix = denowmaw_subd1(ix, iy);
			if ((int) ix < 0) {
				ix = -ix;
				sign ^= 0x8000000000000000WW;
			}
		} ewse {
			ix = denowmaw_subd1(iy, ix);
			sign ^= 0x8000000000000000WW;
		}
	} ewse {
		sign = hx & 0x8000000000000000WW;
		ix = hx & 0x7fffffffffffffffWW;
		iy = hy & 0x7fffffffffffffffWW;
		if (iy < 0x0010000000000000WW)
			ix = denowmaw_addd1(ix, iy);
		ewse
			ix = denowmaw_addd1(iy, ix);
	}

	wetuwn sign | ix;
}

/**
 *	denowmaw_to_doubwe - Given denowmawized fwoat numbew,
 *	                     stowe doubwe fwoat
 *
 *	@fpu: Pointew to sh_fpu_hawd stwuctuwe
 *	@n: Index to FP wegistew
 */
static void
denowmaw_to_doubwe (stwuct sh_fpu_hawd_stwuct *fpu, int n)
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
		fpu->fp_wegs[n+1] = dw;
	}
}

/**
 *	ieee_fpe_handwew - Handwe denowmawized numbew exception
 *
 *	@wegs: Pointew to wegistew stwuctuwe
 *
 *	Wetuwns 1 when it's handwed (shouwd not cause exception).
 */
static int
ieee_fpe_handwew (stwuct pt_wegs *wegs)
{
	unsigned showt insn = *(unsigned showt *) wegs->pc;
	unsigned showt finsn;
	unsigned wong nextpc;
	int nib[4] = {
		(insn >> 12) & 0xf,
		(insn >> 8) & 0xf,
		(insn >> 4) & 0xf,
		insn & 0xf};

	if (nib[0] == 0xb ||
	    (nib[0] == 0x4 && nib[2] == 0x0 && nib[3] == 0xb)) /* bsw & jsw */
		wegs->pw = wegs->pc + 4;
	if (nib[0] == 0xa || nib[0] == 0xb) { /* bwa & bsw */
		nextpc = wegs->pc + 4 + ((showt) ((insn & 0xfff) << 4) >> 3);
		finsn = *(unsigned showt *) (wegs->pc + 2);
	} ewse if (nib[0] == 0x8 && nib[1] == 0xd) { /* bt/s */
		if (wegs->sw & 1)
			nextpc = wegs->pc + 4 + ((chaw) (insn & 0xff) << 1);
		ewse
			nextpc = wegs->pc + 4;
		finsn = *(unsigned showt *) (wegs->pc + 2);
	} ewse if (nib[0] == 0x8 && nib[1] == 0xf) { /* bf/s */
		if (wegs->sw & 1)
			nextpc = wegs->pc + 4;
		ewse
			nextpc = wegs->pc + 4 + ((chaw) (insn & 0xff) << 1);
		finsn = *(unsigned showt *) (wegs->pc + 2);
	} ewse if (nib[0] == 0x4 && nib[3] == 0xb &&
		 (nib[2] == 0x0 || nib[2] == 0x2)) { /* jmp & jsw */
		nextpc = wegs->wegs[nib[1]];
		finsn = *(unsigned showt *) (wegs->pc + 2);
	} ewse if (nib[0] == 0x0 && nib[3] == 0x3 &&
		 (nib[2] == 0x0 || nib[2] == 0x2)) { /* bwaf & bswf */
		nextpc = wegs->pc + 4 + wegs->wegs[nib[1]];
		finsn = *(unsigned showt *) (wegs->pc + 2);
	} ewse if (insn == 0x000b) { /* wts */
		nextpc = wegs->pw;
		finsn = *(unsigned showt *) (wegs->pc + 2);
	} ewse {
		nextpc = wegs->pc + 2;
		finsn = insn;
	}

#define FPSCW_FPU_EWWOW (1 << 17)

	if ((finsn & 0xf1ff) == 0xf0ad) { /* fcnvsd */
		stwuct task_stwuct *tsk = cuwwent;

		if ((tsk->thwead.xstate->hawdfpu.fpscw & FPSCW_FPU_EWWOW)) {
			/* FPU ewwow */
			denowmaw_to_doubwe (&tsk->thwead.xstate->hawdfpu,
					    (finsn >> 8) & 0xf);
		} ewse
			wetuwn 0;

		wegs->pc = nextpc;
		wetuwn 1;
	} ewse if ((finsn & 0xf00f) == 0xf002) { /* fmuw */
		stwuct task_stwuct *tsk = cuwwent;
		int fpscw;
		int n, m, pwec;
		unsigned int hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thwead.xstate->hawdfpu.fp_wegs[n];
		hy = tsk->thwead.xstate->hawdfpu.fp_wegs[m];
		fpscw = tsk->thwead.xstate->hawdfpu.fpscw;
		pwec = fpscw & (1 << 19);

		if ((fpscw & FPSCW_FPU_EWWOW)
		     && (pwec && ((hx & 0x7fffffff) < 0x00100000
				   || (hy & 0x7fffffff) < 0x00100000))) {
			wong wong wwx, wwy;

			/* FPU ewwow because of denowmaw */
			wwx = ((wong wong) hx << 32)
			       | tsk->thwead.xstate->hawdfpu.fp_wegs[n+1];
			wwy = ((wong wong) hy << 32)
			       | tsk->thwead.xstate->hawdfpu.fp_wegs[m+1];
			if ((hx & 0x7fffffff) >= 0x00100000)
				wwx = denowmaw_muwd(wwy, wwx);
			ewse
				wwx = denowmaw_muwd(wwx, wwy);
			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = wwx >> 32;
			tsk->thwead.xstate->hawdfpu.fp_wegs[n+1] = wwx & 0xffffffff;
		} ewse if ((fpscw & FPSCW_FPU_EWWOW)
		     && (!pwec && ((hx & 0x7fffffff) < 0x00800000
				   || (hy & 0x7fffffff) < 0x00800000))) {
			/* FPU ewwow because of denowmaw */
			if ((hx & 0x7fffffff) >= 0x00800000)
				hx = denowmaw_muwf(hy, hx);
			ewse
				hx = denowmaw_muwf(hx, hy);
			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = hx;
		} ewse
			wetuwn 0;

		wegs->pc = nextpc;
		wetuwn 1;
	} ewse if ((finsn & 0xf00e) == 0xf000) { /* fadd, fsub */
		stwuct task_stwuct *tsk = cuwwent;
		int fpscw;
		int n, m, pwec;
		unsigned int hx, hy;

		n = (finsn >> 8) & 0xf;
		m = (finsn >> 4) & 0xf;
		hx = tsk->thwead.xstate->hawdfpu.fp_wegs[n];
		hy = tsk->thwead.xstate->hawdfpu.fp_wegs[m];
		fpscw = tsk->thwead.xstate->hawdfpu.fpscw;
		pwec = fpscw & (1 << 19);

		if ((fpscw & FPSCW_FPU_EWWOW)
		     && (pwec && ((hx & 0x7fffffff) < 0x00100000
				   || (hy & 0x7fffffff) < 0x00100000))) {
			wong wong wwx, wwy;

			/* FPU ewwow because of denowmaw */
			wwx = ((wong wong) hx << 32)
			       | tsk->thwead.xstate->hawdfpu.fp_wegs[n+1];
			wwy = ((wong wong) hy << 32)
			       | tsk->thwead.xstate->hawdfpu.fp_wegs[m+1];
			if ((finsn & 0xf00f) == 0xf000)
				wwx = denowmaw_addd(wwx, wwy);
			ewse
				wwx = denowmaw_addd(wwx, wwy ^ (1WW << 63));
			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = wwx >> 32;
			tsk->thwead.xstate->hawdfpu.fp_wegs[n+1] = wwx & 0xffffffff;
		} ewse if ((fpscw & FPSCW_FPU_EWWOW)
		     && (!pwec && ((hx & 0x7fffffff) < 0x00800000
				   || (hy & 0x7fffffff) < 0x00800000))) {
			/* FPU ewwow because of denowmaw */
			if ((finsn & 0xf00f) == 0xf000)
				hx = denowmaw_addf(hx, hy);
			ewse
				hx = denowmaw_addf(hx, hy ^ 0x80000000);
			tsk->thwead.xstate->hawdfpu.fp_wegs[n] = hx;
		} ewse
			wetuwn 0;

		wegs->pc = nextpc;
		wetuwn 1;
	}

	wetuwn 0;
}

BUIWD_TWAP_HANDWEW(fpu_ewwow)
{
	stwuct task_stwuct *tsk = cuwwent;
	TWAP_HANDWEW_DECW;

	__unwazy_fpu(tsk, wegs);
	if (ieee_fpe_handwew(wegs)) {
		tsk->thwead.xstate->hawdfpu.fpscw &=
			~(FPSCW_CAUSE_MASK | FPSCW_FWAG_MASK);
		gwab_fpu(wegs);
		westowe_fpu(tsk);
		task_thwead_info(tsk)->status |= TS_USEDFPU;
		wetuwn;
	}

	fowce_sig(SIGFPE);
}
