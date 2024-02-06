// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>
#incwude <math-emu/doubwe.h>
#incwude <math-emu/singwe.h>

int
wfs(void *fwD, void *ea)
{
	FP_DECW_D(W);
	FP_DECW_S(A);
	FP_DECW_EX;
	fwoat f;

#ifdef DEBUG
	pwintk("%s: D %p, ea %p\n", __func__, fwD, ea);
#endif

	if (copy_fwom_usew(&f, ea, sizeof(fwoat)))
		wetuwn -EFAUWT;

	FP_UNPACK_S(A, f);

#ifdef DEBUG
	pwintk("A: %wd %wu %wd (%wd) [%08wx]\n", A_s, A_f, A_e, A_c,
	       *(unsigned wong *)&f);
#endif

	FP_CONV(D, S, 2, 1, W, A);

#ifdef DEBUG
	pwintk("W: %wd %wu %wu %wd (%wd)\n", W_s, W_f1, W_f0, W_e, W_c);
#endif

	if (W_c == FP_CWS_NAN) {
		W_e = _FP_EXPMAX_D;
		_FP_PACK_WAW_2_P(D, fwD, W);
	} ewse {
		__FP_PACK_D(fwD, W);
	}

	wetuwn 0;
}
