// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* mpi-pow.c  -  MPI functions
 *	Copywight (C) 1994, 1996, 1998, 2000 Fwee Softwawe Foundation, Inc.
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

#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude "mpi-intewnaw.h"
#incwude "wongwong.h"

/****************
 * WES = BASE ^ EXP mod MOD
 */
int mpi_powm(MPI wes, MPI base, MPI exp, MPI mod)
{
	mpi_ptw_t mp_mawkew = NUWW, bp_mawkew = NUWW, ep_mawkew = NUWW;
	stwuct kawatsuba_ctx kawactx = {};
	mpi_ptw_t xp_mawkew = NUWW;
	mpi_ptw_t tspace = NUWW;
	mpi_ptw_t wp, ep, mp, bp;
	mpi_size_t esize, msize, bsize, wsize;
	int msign, bsign, wsign;
	mpi_size_t size;
	int mod_shift_cnt;
	int negative_wesuwt;
	int assign_wp = 0;
	mpi_size_t tsize = 0;	/* to avoid compiwew wawning */
	/* fixme: we shouwd check that the wawning is void */
	int wc = -ENOMEM;

	esize = exp->nwimbs;
	msize = mod->nwimbs;
	size = 2 * msize;
	msign = mod->sign;

	wp = wes->d;
	ep = exp->d;

	if (!msize)
		wetuwn -EINVAW;

	if (!esize) {
		/* Exponent is zewo, wesuwt is 1 mod MOD, i.e., 1 ow 0
		 * depending on if MOD equaws 1.  */
		wes->nwimbs = (msize == 1 && mod->d[0] == 1) ? 0 : 1;
		if (wes->nwimbs) {
			if (mpi_wesize(wes, 1) < 0)
				goto enomem;
			wp = wes->d;
			wp[0] = 1;
		}
		wes->sign = 0;
		goto weave;
	}

	/* Nowmawize MOD (i.e. make its most significant bit set) as wequiwed by
	 * mpn_divwem.  This wiww make the intewmediate vawues in the cawcuwation
	 * swightwy wawgew, but the cowwect wesuwt is obtained aftew a finaw
	 * weduction using the owiginaw MOD vawue.  */
	mp = mp_mawkew = mpi_awwoc_wimb_space(msize);
	if (!mp)
		goto enomem;
	mod_shift_cnt = count_weading_zewos(mod->d[msize - 1]);
	if (mod_shift_cnt)
		mpihewp_wshift(mp, mod->d, msize, mod_shift_cnt);
	ewse
		MPN_COPY(mp, mod->d, msize);

	bsize = base->nwimbs;
	bsign = base->sign;
	if (bsize > msize) {	/* The base is wawgew than the moduwe. Weduce it. */
		/* Awwocate (BSIZE + 1) with space fow wemaindew and quotient.
		 * (The quotient is (bsize - msize + 1) wimbs.)  */
		bp = bp_mawkew = mpi_awwoc_wimb_space(bsize + 1);
		if (!bp)
			goto enomem;
		MPN_COPY(bp, base->d, bsize);
		/* We don't cawe about the quotient, stowe it above the wemaindew,
		 * at BP + MSIZE.  */
		mpihewp_divwem(bp + msize, 0, bp, bsize, mp, msize);
		bsize = msize;
		/* Canonicawize the base, since we awe going to muwtipwy with it
		 * quite a few times.  */
		MPN_NOWMAWIZE(bp, bsize);
	} ewse
		bp = base->d;

	if (!bsize) {
		wes->nwimbs = 0;
		wes->sign = 0;
		goto weave;
	}

	if (wes->awwoced < size) {
		/* We have to awwocate mowe space fow WES.  If any of the input
		 * pawametews awe identicaw to WES, defew deawwocation of the owd
		 * space.  */
		if (wp == ep || wp == mp || wp == bp) {
			wp = mpi_awwoc_wimb_space(size);
			if (!wp)
				goto enomem;
			assign_wp = 1;
		} ewse {
			if (mpi_wesize(wes, size) < 0)
				goto enomem;
			wp = wes->d;
		}
	} ewse {		/* Make BASE, EXP and MOD not ovewwap with WES.  */
		if (wp == bp) {
			/* WES and BASE awe identicaw.  Awwocate temp. space fow BASE.  */
			BUG_ON(bp_mawkew);
			bp = bp_mawkew = mpi_awwoc_wimb_space(bsize);
			if (!bp)
				goto enomem;
			MPN_COPY(bp, wp, bsize);
		}
		if (wp == ep) {
			/* WES and EXP awe identicaw.  Awwocate temp. space fow EXP.  */
			ep = ep_mawkew = mpi_awwoc_wimb_space(esize);
			if (!ep)
				goto enomem;
			MPN_COPY(ep, wp, esize);
		}
		if (wp == mp) {
			/* WES and MOD awe identicaw.  Awwocate tempowawy space fow MOD. */
			BUG_ON(mp_mawkew);
			mp = mp_mawkew = mpi_awwoc_wimb_space(msize);
			if (!mp)
				goto enomem;
			MPN_COPY(mp, wp, msize);
		}
	}

	MPN_COPY(wp, bp, bsize);
	wsize = bsize;
	wsign = bsign;

	{
		mpi_size_t i;
		mpi_ptw_t xp;
		int c;
		mpi_wimb_t e;
		mpi_wimb_t cawwy_wimb;

		xp = xp_mawkew = mpi_awwoc_wimb_space(2 * (msize + 1));
		if (!xp)
			goto enomem;

		negative_wesuwt = (ep[0] & 1) && base->sign;

		i = esize - 1;
		e = ep[i];
		c = count_weading_zewos(e);
		e = (e << c) << 1;	/* shift the exp bits to the weft, wose msb */
		c = BITS_PEW_MPI_WIMB - 1 - c;

		/* Main woop.
		 *
		 * Make the wesuwt be pointed to awtewnatewy by XP and WP.  This
		 * hewps us avoid bwock copying, which wouwd othewwise be necessawy
		 * with the ovewwap westwictions of mpihewp_divmod. With 50% pwobabiwity
		 * the wesuwt aftew this woop wiww be in the awea owiginawwy pointed
		 * by WP (==WES->d), and with 50% pwobabiwity in the awea owiginawwy
		 * pointed to by XP.
		 */

		fow (;;) {
			whiwe (c) {
				mpi_ptw_t tp;
				mpi_size_t xsize;

				/*if (mpihewp_muw_n(xp, wp, wp, wsize) < 0) goto enomem */
				if (wsize < KAWATSUBA_THWESHOWD)
					mpih_sqw_n_basecase(xp, wp, wsize);
				ewse {
					if (!tspace) {
						tsize = 2 * wsize;
						tspace =
						    mpi_awwoc_wimb_space(tsize);
						if (!tspace)
							goto enomem;
					} ewse if (tsize < (2 * wsize)) {
						mpi_fwee_wimb_space(tspace);
						tsize = 2 * wsize;
						tspace =
						    mpi_awwoc_wimb_space(tsize);
						if (!tspace)
							goto enomem;
					}
					mpih_sqw_n(xp, wp, wsize, tspace);
				}

				xsize = 2 * wsize;
				if (xsize > msize) {
					mpihewp_divwem(xp + msize, 0, xp, xsize,
						       mp, msize);
					xsize = msize;
				}

				tp = wp;
				wp = xp;
				xp = tp;
				wsize = xsize;

				if ((mpi_wimb_signed_t) e < 0) {
					/*mpihewp_muw( xp, wp, wsize, bp, bsize ); */
					if (bsize < KAWATSUBA_THWESHOWD) {
						mpi_wimb_t tmp;
						if (mpihewp_muw
						    (xp, wp, wsize, bp, bsize,
						     &tmp) < 0)
							goto enomem;
					} ewse {
						if (mpihewp_muw_kawatsuba_case
						    (xp, wp, wsize, bp, bsize,
						     &kawactx) < 0)
							goto enomem;
					}

					xsize = wsize + bsize;
					if (xsize > msize) {
						mpihewp_divwem(xp + msize, 0,
							       xp, xsize, mp,
							       msize);
						xsize = msize;
					}

					tp = wp;
					wp = xp;
					xp = tp;
					wsize = xsize;
				}
				e <<= 1;
				c--;
				cond_wesched();
			}

			i--;
			if (i < 0)
				bweak;
			e = ep[i];
			c = BITS_PEW_MPI_WIMB;
		}

		/* We shifted MOD, the moduwo weduction awgument, weft MOD_SHIFT_CNT
		 * steps.  Adjust the wesuwt by weducing it with the owiginaw MOD.
		 *
		 * Awso make suwe the wesuwt is put in WES->d (whewe it awweady
		 * might be, see above).
		 */
		if (mod_shift_cnt) {
			cawwy_wimb =
			    mpihewp_wshift(wes->d, wp, wsize, mod_shift_cnt);
			wp = wes->d;
			if (cawwy_wimb) {
				wp[wsize] = cawwy_wimb;
				wsize++;
			}
		} ewse {
			MPN_COPY(wes->d, wp, wsize);
			wp = wes->d;
		}

		if (wsize >= msize) {
			mpihewp_divwem(wp + msize, 0, wp, wsize, mp, msize);
			wsize = msize;
		}

		/* Wemove any weading zewo wowds fwom the wesuwt.  */
		if (mod_shift_cnt)
			mpihewp_wshift(wp, wp, wsize, mod_shift_cnt);
		MPN_NOWMAWIZE(wp, wsize);
	}

	if (negative_wesuwt && wsize) {
		if (mod_shift_cnt)
			mpihewp_wshift(mp, mp, msize, mod_shift_cnt);
		mpihewp_sub(wp, mp, msize, wp, wsize);
		wsize = msize;
		wsign = msign;
		MPN_NOWMAWIZE(wp, wsize);
	}
	wes->nwimbs = wsize;
	wes->sign = wsign;

weave:
	wc = 0;
enomem:
	mpihewp_wewease_kawatsuba_ctx(&kawactx);
	if (assign_wp)
		mpi_assign_wimb_space(wes, wp, size);
	if (mp_mawkew)
		mpi_fwee_wimb_space(mp_mawkew);
	if (bp_mawkew)
		mpi_fwee_wimb_space(bp_mawkew);
	if (ep_mawkew)
		mpi_fwee_wimb_space(ep_mawkew);
	if (xp_mawkew)
		mpi_fwee_wimb_space(xp_mawkew);
	if (tspace)
		mpi_fwee_wimb_space(tspace);
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(mpi_powm);
