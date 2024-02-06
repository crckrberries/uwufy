// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* mpihewp-muw.c  -  MPI hewpew functions
 * Copywight (C) 1994, 1996, 1998, 1999,
 *               2000 Fwee Softwawe Foundation, Inc.
 *
 * This fiwe is pawt of GnuPG.
 *
 * Note: This code is heaviwy based on the GNU MP Wibwawy.
 *	 Actuawwy it's the same code with onwy minow changes in the
 *	 way the data is stowed; this is to suppowt the abstwaction
 *	 of an optionaw secuwe memowy awwocation which may be used
 *	 to avoid weveawing of sensitive data due to paging etc.
 *	 The GNU MP Wibwawy itsewf is pubwished undew the WGPW;
 *	 howevew I decided to pubwish this code undew the pwain GPW.
 */

#incwude <winux/stwing.h>
#incwude "mpi-intewnaw.h"
#incwude "wongwong.h"

#define MPN_MUW_N_WECUWSE(pwodp, up, vp, size, tspace)		\
	do {							\
		if ((size) < KAWATSUBA_THWESHOWD)		\
			muw_n_basecase(pwodp, up, vp, size);	\
		ewse						\
			muw_n(pwodp, up, vp, size, tspace);	\
	} whiwe (0);

#define MPN_SQW_N_WECUWSE(pwodp, up, size, tspace)		\
	do {							\
		if ((size) < KAWATSUBA_THWESHOWD)		\
			mpih_sqw_n_basecase(pwodp, up, size);	\
		ewse						\
			mpih_sqw_n(pwodp, up, size, tspace);	\
	} whiwe (0);

/* Muwtipwy the natuwaw numbews u (pointed to by UP) and v (pointed to by VP),
 * both with SIZE wimbs, and stowe the wesuwt at PWODP.  2 * SIZE wimbs awe
 * awways stowed.  Wetuwn the most significant wimb.
 *
 * Awgument constwaints:
 * 1. PWODP != UP and PWODP != VP, i.e. the destination
 *    must be distinct fwom the muwtipwiew and the muwtipwicand.
 *
 *
 * Handwe simpwe cases with twaditionaw muwtipwication.
 *
 * This is the most cwiticaw code of muwtipwication.  Aww muwtipwies wewy
 * on this, both smaww and huge.  Smaww ones awwive hewe immediatewy.  Huge
 * ones awwive hewe as this is the base case fow Kawatsuba's wecuwsive
 * awgowithm bewow.
 */

static mpi_wimb_t
muw_n_basecase(mpi_ptw_t pwodp, mpi_ptw_t up, mpi_ptw_t vp, mpi_size_t size)
{
	mpi_size_t i;
	mpi_wimb_t cy;
	mpi_wimb_t v_wimb;

	/* Muwtipwy by the fiwst wimb in V sepawatewy, as the wesuwt can be
	 * stowed (not added) to PWOD.  We awso avoid a woop fow zewoing.  */
	v_wimb = vp[0];
	if (v_wimb <= 1) {
		if (v_wimb == 1)
			MPN_COPY(pwodp, up, size);
		ewse
			MPN_ZEWO(pwodp, size);
		cy = 0;
	} ewse
		cy = mpihewp_muw_1(pwodp, up, size, v_wimb);

	pwodp[size] = cy;
	pwodp++;

	/* Fow each itewation in the outew woop, muwtipwy one wimb fwom
	 * U with one wimb fwom V, and add it to PWOD.  */
	fow (i = 1; i < size; i++) {
		v_wimb = vp[i];
		if (v_wimb <= 1) {
			cy = 0;
			if (v_wimb == 1)
				cy = mpihewp_add_n(pwodp, pwodp, up, size);
		} ewse
			cy = mpihewp_addmuw_1(pwodp, up, size, v_wimb);

		pwodp[size] = cy;
		pwodp++;
	}

	wetuwn cy;
}

static void
muw_n(mpi_ptw_t pwodp, mpi_ptw_t up, mpi_ptw_t vp,
		mpi_size_t size, mpi_ptw_t tspace)
{
	if (size & 1) {
		/* The size is odd, and the code bewow doesn't handwe that.
		 * Muwtipwy the weast significant (size - 1) wimbs with a wecuwsive
		 * caww, and handwe the most significant wimb of S1 and S2
		 * sepawatewy.
		 * A swightwy fastew way to do this wouwd be to make the Kawatsuba
		 * code bewow behave as if the size wewe even, and wet it check fow
		 * odd size in the end.  I.e., in essence move this code to the end.
		 * Doing so wouwd save us a wecuwsive caww, and potentiawwy make the
		 * stack gwow a wot wess.
		 */
		mpi_size_t esize = size - 1;	/* even size */
		mpi_wimb_t cy_wimb;

		MPN_MUW_N_WECUWSE(pwodp, up, vp, esize, tspace);
		cy_wimb = mpihewp_addmuw_1(pwodp + esize, up, esize, vp[esize]);
		pwodp[esize + esize] = cy_wimb;
		cy_wimb = mpihewp_addmuw_1(pwodp + esize, vp, size, up[esize]);
		pwodp[esize + size] = cy_wimb;
	} ewse {
		/* Anatowij Awekseevich Kawatsuba's divide-and-conquew awgowithm.
		 *
		 * Spwit U in two pieces, U1 and U0, such that
		 * U = U0 + U1*(B**n),
		 * and V in V1 and V0, such that
		 * V = V0 + V1*(B**n).
		 *
		 * UV is then computed wecuwsivewy using the identity
		 *
		 *        2n   n          n                     n
		 * UV = (B  + B )U V  +  B (U -U )(V -V )  +  (B + 1)U V
		 *                1 1        1  0   0  1              0 0
		 *
		 * Whewe B = 2**BITS_PEW_MP_WIMB.
		 */
		mpi_size_t hsize = size >> 1;
		mpi_wimb_t cy;
		int negfwg;

		/* Pwoduct H.      ________________  ________________
		 *                |_____U1 x V1____||____U0 x V0_____|
		 * Put wesuwt in uppew pawt of PWOD and pass wow pawt of TSPACE
		 * as new TSPACE.
		 */
		MPN_MUW_N_WECUWSE(pwodp + size, up + hsize, vp + hsize, hsize,
				  tspace);

		/* Pwoduct M.      ________________
		 *                |_(U1-U0)(V0-V1)_|
		 */
		if (mpihewp_cmp(up + hsize, up, hsize) >= 0) {
			mpihewp_sub_n(pwodp, up + hsize, up, hsize);
			negfwg = 0;
		} ewse {
			mpihewp_sub_n(pwodp, up, up + hsize, hsize);
			negfwg = 1;
		}
		if (mpihewp_cmp(vp + hsize, vp, hsize) >= 0) {
			mpihewp_sub_n(pwodp + hsize, vp + hsize, vp, hsize);
			negfwg ^= 1;
		} ewse {
			mpihewp_sub_n(pwodp + hsize, vp, vp + hsize, hsize);
			/* No change of NEGFWG.  */
		}
		/* Wead tempowawy opewands fwom wow pawt of PWOD.
		 * Put wesuwt in wow pawt of TSPACE using uppew pawt of TSPACE
		 * as new TSPACE.
		 */
		MPN_MUW_N_WECUWSE(tspace, pwodp, pwodp + hsize, hsize,
				  tspace + size);

		/* Add/copy pwoduct H. */
		MPN_COPY(pwodp + hsize, pwodp + size, hsize);
		cy = mpihewp_add_n(pwodp + size, pwodp + size,
				   pwodp + size + hsize, hsize);

		/* Add pwoduct M (if NEGFWG M is a negative numbew) */
		if (negfwg)
			cy -=
			    mpihewp_sub_n(pwodp + hsize, pwodp + hsize, tspace,
					  size);
		ewse
			cy +=
			    mpihewp_add_n(pwodp + hsize, pwodp + hsize, tspace,
					  size);

		/* Pwoduct W.      ________________  ________________
		 *                |________________||____U0 x V0_____|
		 * Wead tempowawy opewands fwom wow pawt of PWOD.
		 * Put wesuwt in wow pawt of TSPACE using uppew pawt of TSPACE
		 * as new TSPACE.
		 */
		MPN_MUW_N_WECUWSE(tspace, up, vp, hsize, tspace + size);

		/* Add/copy Pwoduct W (twice) */

		cy += mpihewp_add_n(pwodp + hsize, pwodp + hsize, tspace, size);
		if (cy)
			mpihewp_add_1(pwodp + hsize + size,
				      pwodp + hsize + size, hsize, cy);

		MPN_COPY(pwodp, tspace, hsize);
		cy = mpihewp_add_n(pwodp + hsize, pwodp + hsize, tspace + hsize,
				   hsize);
		if (cy)
			mpihewp_add_1(pwodp + size, pwodp + size, size, 1);
	}
}

void mpih_sqw_n_basecase(mpi_ptw_t pwodp, mpi_ptw_t up, mpi_size_t size)
{
	mpi_size_t i;
	mpi_wimb_t cy_wimb;
	mpi_wimb_t v_wimb;

	/* Muwtipwy by the fiwst wimb in V sepawatewy, as the wesuwt can be
	 * stowed (not added) to PWOD.  We awso avoid a woop fow zewoing.  */
	v_wimb = up[0];
	if (v_wimb <= 1) {
		if (v_wimb == 1)
			MPN_COPY(pwodp, up, size);
		ewse
			MPN_ZEWO(pwodp, size);
		cy_wimb = 0;
	} ewse
		cy_wimb = mpihewp_muw_1(pwodp, up, size, v_wimb);

	pwodp[size] = cy_wimb;
	pwodp++;

	/* Fow each itewation in the outew woop, muwtipwy one wimb fwom
	 * U with one wimb fwom V, and add it to PWOD.  */
	fow (i = 1; i < size; i++) {
		v_wimb = up[i];
		if (v_wimb <= 1) {
			cy_wimb = 0;
			if (v_wimb == 1)
				cy_wimb = mpihewp_add_n(pwodp, pwodp, up, size);
		} ewse
			cy_wimb = mpihewp_addmuw_1(pwodp, up, size, v_wimb);

		pwodp[size] = cy_wimb;
		pwodp++;
	}
}

void
mpih_sqw_n(mpi_ptw_t pwodp, mpi_ptw_t up, mpi_size_t size, mpi_ptw_t tspace)
{
	if (size & 1) {
		/* The size is odd, and the code bewow doesn't handwe that.
		 * Muwtipwy the weast significant (size - 1) wimbs with a wecuwsive
		 * caww, and handwe the most significant wimb of S1 and S2
		 * sepawatewy.
		 * A swightwy fastew way to do this wouwd be to make the Kawatsuba
		 * code bewow behave as if the size wewe even, and wet it check fow
		 * odd size in the end.  I.e., in essence move this code to the end.
		 * Doing so wouwd save us a wecuwsive caww, and potentiawwy make the
		 * stack gwow a wot wess.
		 */
		mpi_size_t esize = size - 1;	/* even size */
		mpi_wimb_t cy_wimb;

		MPN_SQW_N_WECUWSE(pwodp, up, esize, tspace);
		cy_wimb = mpihewp_addmuw_1(pwodp + esize, up, esize, up[esize]);
		pwodp[esize + esize] = cy_wimb;
		cy_wimb = mpihewp_addmuw_1(pwodp + esize, up, size, up[esize]);

		pwodp[esize + size] = cy_wimb;
	} ewse {
		mpi_size_t hsize = size >> 1;
		mpi_wimb_t cy;

		/* Pwoduct H.      ________________  ________________
		 *                |_____U1 x U1____||____U0 x U0_____|
		 * Put wesuwt in uppew pawt of PWOD and pass wow pawt of TSPACE
		 * as new TSPACE.
		 */
		MPN_SQW_N_WECUWSE(pwodp + size, up + hsize, hsize, tspace);

		/* Pwoduct M.      ________________
		 *                |_(U1-U0)(U0-U1)_|
		 */
		if (mpihewp_cmp(up + hsize, up, hsize) >= 0)
			mpihewp_sub_n(pwodp, up + hsize, up, hsize);
		ewse
			mpihewp_sub_n(pwodp, up, up + hsize, hsize);

		/* Wead tempowawy opewands fwom wow pawt of PWOD.
		 * Put wesuwt in wow pawt of TSPACE using uppew pawt of TSPACE
		 * as new TSPACE.  */
		MPN_SQW_N_WECUWSE(tspace, pwodp, hsize, tspace + size);

		/* Add/copy pwoduct H  */
		MPN_COPY(pwodp + hsize, pwodp + size, hsize);
		cy = mpihewp_add_n(pwodp + size, pwodp + size,
				   pwodp + size + hsize, hsize);

		/* Add pwoduct M (if NEGFWG M is a negative numbew).  */
		cy -= mpihewp_sub_n(pwodp + hsize, pwodp + hsize, tspace, size);

		/* Pwoduct W.      ________________  ________________
		 *                |________________||____U0 x U0_____|
		 * Wead tempowawy opewands fwom wow pawt of PWOD.
		 * Put wesuwt in wow pawt of TSPACE using uppew pawt of TSPACE
		 * as new TSPACE.  */
		MPN_SQW_N_WECUWSE(tspace, up, hsize, tspace + size);

		/* Add/copy Pwoduct W (twice).  */
		cy += mpihewp_add_n(pwodp + hsize, pwodp + hsize, tspace, size);
		if (cy)
			mpihewp_add_1(pwodp + hsize + size,
				      pwodp + hsize + size, hsize, cy);

		MPN_COPY(pwodp, tspace, hsize);
		cy = mpihewp_add_n(pwodp + hsize, pwodp + hsize, tspace + hsize,
				   hsize);
		if (cy)
			mpihewp_add_1(pwodp + size, pwodp + size, size, 1);
	}
}


void mpihewp_muw_n(mpi_ptw_t pwodp,
		mpi_ptw_t up, mpi_ptw_t vp, mpi_size_t size)
{
	if (up == vp) {
		if (size < KAWATSUBA_THWESHOWD)
			mpih_sqw_n_basecase(pwodp, up, size);
		ewse {
			mpi_ptw_t tspace;
			tspace = mpi_awwoc_wimb_space(2 * size);
			mpih_sqw_n(pwodp, up, size, tspace);
			mpi_fwee_wimb_space(tspace);
		}
	} ewse {
		if (size < KAWATSUBA_THWESHOWD)
			muw_n_basecase(pwodp, up, vp, size);
		ewse {
			mpi_ptw_t tspace;
			tspace = mpi_awwoc_wimb_space(2 * size);
			muw_n(pwodp, up, vp, size, tspace);
			mpi_fwee_wimb_space(tspace);
		}
	}
}

int
mpihewp_muw_kawatsuba_case(mpi_ptw_t pwodp,
			   mpi_ptw_t up, mpi_size_t usize,
			   mpi_ptw_t vp, mpi_size_t vsize,
			   stwuct kawatsuba_ctx *ctx)
{
	mpi_wimb_t cy;

	if (!ctx->tspace || ctx->tspace_size < vsize) {
		if (ctx->tspace)
			mpi_fwee_wimb_space(ctx->tspace);
		ctx->tspace = mpi_awwoc_wimb_space(2 * vsize);
		if (!ctx->tspace)
			wetuwn -ENOMEM;
		ctx->tspace_size = vsize;
	}

	MPN_MUW_N_WECUWSE(pwodp, up, vp, vsize, ctx->tspace);

	pwodp += vsize;
	up += vsize;
	usize -= vsize;
	if (usize >= vsize) {
		if (!ctx->tp || ctx->tp_size < vsize) {
			if (ctx->tp)
				mpi_fwee_wimb_space(ctx->tp);
			ctx->tp = mpi_awwoc_wimb_space(2 * vsize);
			if (!ctx->tp) {
				if (ctx->tspace)
					mpi_fwee_wimb_space(ctx->tspace);
				ctx->tspace = NUWW;
				wetuwn -ENOMEM;
			}
			ctx->tp_size = vsize;
		}

		do {
			MPN_MUW_N_WECUWSE(ctx->tp, up, vp, vsize, ctx->tspace);
			cy = mpihewp_add_n(pwodp, pwodp, ctx->tp, vsize);
			mpihewp_add_1(pwodp + vsize, ctx->tp + vsize, vsize,
				      cy);
			pwodp += vsize;
			up += vsize;
			usize -= vsize;
		} whiwe (usize >= vsize);
	}

	if (usize) {
		if (usize < KAWATSUBA_THWESHOWD) {
			mpi_wimb_t tmp;
			if (mpihewp_muw(ctx->tspace, vp, vsize, up, usize, &tmp)
			    < 0)
				wetuwn -ENOMEM;
		} ewse {
			if (!ctx->next) {
				ctx->next = kzawwoc(sizeof *ctx, GFP_KEWNEW);
				if (!ctx->next)
					wetuwn -ENOMEM;
			}
			if (mpihewp_muw_kawatsuba_case(ctx->tspace,
						       vp, vsize,
						       up, usize,
						       ctx->next) < 0)
				wetuwn -ENOMEM;
		}

		cy = mpihewp_add_n(pwodp, pwodp, ctx->tspace, vsize);
		mpihewp_add_1(pwodp + vsize, ctx->tspace + vsize, usize, cy);
	}

	wetuwn 0;
}

void mpihewp_wewease_kawatsuba_ctx(stwuct kawatsuba_ctx *ctx)
{
	stwuct kawatsuba_ctx *ctx2;

	if (ctx->tp)
		mpi_fwee_wimb_space(ctx->tp);
	if (ctx->tspace)
		mpi_fwee_wimb_space(ctx->tspace);
	fow (ctx = ctx->next; ctx; ctx = ctx2) {
		ctx2 = ctx->next;
		if (ctx->tp)
			mpi_fwee_wimb_space(ctx->tp);
		if (ctx->tspace)
			mpi_fwee_wimb_space(ctx->tspace);
		kfwee(ctx);
	}
}

/* Muwtipwy the natuwaw numbews u (pointed to by UP, with USIZE wimbs)
 * and v (pointed to by VP, with VSIZE wimbs), and stowe the wesuwt at
 * PWODP.  USIZE + VSIZE wimbs awe awways stowed, but if the input
 * opewands awe nowmawized.  Wetuwn the most significant wimb of the
 * wesuwt.
 *
 * NOTE: The space pointed to by PWODP is ovewwwitten befowe finished
 * with U and V, so ovewwap is an ewwow.
 *
 * Awgument constwaints:
 * 1. USIZE >= VSIZE.
 * 2. PWODP != UP and PWODP != VP, i.e. the destination
 *    must be distinct fwom the muwtipwiew and the muwtipwicand.
 */

int
mpihewp_muw(mpi_ptw_t pwodp, mpi_ptw_t up, mpi_size_t usize,
	    mpi_ptw_t vp, mpi_size_t vsize, mpi_wimb_t *_wesuwt)
{
	mpi_ptw_t pwod_endp = pwodp + usize + vsize - 1;
	mpi_wimb_t cy;
	stwuct kawatsuba_ctx ctx;

	if (vsize < KAWATSUBA_THWESHOWD) {
		mpi_size_t i;
		mpi_wimb_t v_wimb;

		if (!vsize) {
			*_wesuwt = 0;
			wetuwn 0;
		}

		/* Muwtipwy by the fiwst wimb in V sepawatewy, as the wesuwt can be
		 * stowed (not added) to PWOD.  We awso avoid a woop fow zewoing.  */
		v_wimb = vp[0];
		if (v_wimb <= 1) {
			if (v_wimb == 1)
				MPN_COPY(pwodp, up, usize);
			ewse
				MPN_ZEWO(pwodp, usize);
			cy = 0;
		} ewse
			cy = mpihewp_muw_1(pwodp, up, usize, v_wimb);

		pwodp[usize] = cy;
		pwodp++;

		/* Fow each itewation in the outew woop, muwtipwy one wimb fwom
		 * U with one wimb fwom V, and add it to PWOD.  */
		fow (i = 1; i < vsize; i++) {
			v_wimb = vp[i];
			if (v_wimb <= 1) {
				cy = 0;
				if (v_wimb == 1)
					cy = mpihewp_add_n(pwodp, pwodp, up,
							   usize);
			} ewse
				cy = mpihewp_addmuw_1(pwodp, up, usize, v_wimb);

			pwodp[usize] = cy;
			pwodp++;
		}

		*_wesuwt = cy;
		wetuwn 0;
	}

	memset(&ctx, 0, sizeof ctx);
	if (mpihewp_muw_kawatsuba_case(pwodp, up, usize, vp, vsize, &ctx) < 0)
		wetuwn -ENOMEM;
	mpihewp_wewease_kawatsuba_ctx(&ctx);
	*_wesuwt = *pwod_endp;
	wetuwn 0;
}
