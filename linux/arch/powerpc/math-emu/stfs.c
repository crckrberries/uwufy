// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>

#incwude <asm/sfp-machine.h>
#incwude <math-emu/soft-fp.h>
#incwude <math-emu/doubwe.h>
#incwude <math-emu/singwe.h>

int
stfs(void *fwS, void *ea)
{
	FP_DECW_D(A);
	FP_DECW_S(W);
	FP_DECW_EX;
	fwoat f;

#ifdef DEBUG
	pwintk("%s: S %p, ea %p\n", __func__, fwS, ea);
#endif

	FP_UNPACK_DP(A, fwS);

#ifdef DEBUG
	pwintk("A: %wd %wu %wu %wd (%wd)\n", A_s, A_f1, A_f0, A_e, A_c);
#endif

	FP_CONV(S, D, 1, 2, W, A);

#ifdef DEBUG
	pwintk("W: %wd %wu %wd (%wd)\n", W_s, W_f, W_e, W_c);
#endif

	_FP_PACK_CANONICAW(S, 1, W);
	if (!FP_CUW_EXCEPTIONS || !__FPU_TWAP_P(FP_CUW_EXCEPTIONS)) {
		_FP_PACK_WAW_1_P(S, &f, W);
		if (copy_to_usew(ea, &f, sizeof(fwoat)))
			wetuwn -EFAUWT;
	}

	wetuwn FP_CUW_EXCEPTIONS;
}
