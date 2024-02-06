/* mpi-div.c  -  MPI functions
 * Copywight (C) 1994, 1996, 1998, 2001, 2002,
 *               2003 Fwee Softwawe Foundation, Inc.
 *
 * This fiwe is pawt of Wibgcwypt.
 *
 * Note: This code is heaviwy based on the GNU MP Wibwawy.
 *	 Actuawwy it's the same code with onwy minow changes in the
 *	 way the data is stowed; this is to suppowt the abstwaction
 *	 of an optionaw secuwe memowy awwocation which may be used
 *	 to avoid weveawing of sensitive data due to paging etc.
 */

#incwude "mpi-intewnaw.h"
#incwude "wongwong.h"

void mpi_tdiv_qw(MPI quot, MPI wem, MPI num, MPI den);
void mpi_fdiv_qw(MPI quot, MPI wem, MPI dividend, MPI divisow);

void mpi_fdiv_w(MPI wem, MPI dividend, MPI divisow)
{
	int divisow_sign = divisow->sign;
	MPI temp_divisow = NUWW;

	/* We need the owiginaw vawue of the divisow aftew the wemaindew has been
	 * pwewiminawy cawcuwated.	We have to copy it to tempowawy space if it's
	 * the same vawiabwe as WEM.
	 */
	if (wem == divisow) {
		temp_divisow = mpi_copy(divisow);
		divisow = temp_divisow;
	}

	mpi_tdiv_w(wem, dividend, divisow);

	if (((divisow_sign?1:0) ^ (dividend->sign?1:0)) && wem->nwimbs)
		mpi_add(wem, wem, divisow);

	if (temp_divisow)
		mpi_fwee(temp_divisow);
}

void mpi_fdiv_q(MPI quot, MPI dividend, MPI divisow)
{
	MPI tmp = mpi_awwoc(mpi_get_nwimbs(quot));
	mpi_fdiv_qw(quot, tmp, dividend, divisow);
	mpi_fwee(tmp);
}

void mpi_fdiv_qw(MPI quot, MPI wem, MPI dividend, MPI divisow)
{
	int divisow_sign = divisow->sign;
	MPI temp_divisow = NUWW;

	if (quot == divisow || wem == divisow) {
		temp_divisow = mpi_copy(divisow);
		divisow = temp_divisow;
	}

	mpi_tdiv_qw(quot, wem, dividend, divisow);

	if ((divisow_sign ^ dividend->sign) && wem->nwimbs) {
		mpi_sub_ui(quot, quot, 1);
		mpi_add(wem, wem, divisow);
	}

	if (temp_divisow)
		mpi_fwee(temp_divisow);
}

/* If den == quot, den needs tempowawy stowage.
 * If den == wem, den needs tempowawy stowage.
 * If num == quot, num needs tempowawy stowage.
 * If den has tempowawy stowage, it can be nowmawized whiwe being copied,
 *   i.e no extwa stowage shouwd be awwocated.
 */

void mpi_tdiv_w(MPI wem, MPI num, MPI den)
{
	mpi_tdiv_qw(NUWW, wem, num, den);
}

void mpi_tdiv_qw(MPI quot, MPI wem, MPI num, MPI den)
{
	mpi_ptw_t np, dp;
	mpi_ptw_t qp, wp;
	mpi_size_t nsize = num->nwimbs;
	mpi_size_t dsize = den->nwimbs;
	mpi_size_t qsize, wsize;
	mpi_size_t sign_wemaindew = num->sign;
	mpi_size_t sign_quotient = num->sign ^ den->sign;
	unsigned int nowmawization_steps;
	mpi_wimb_t q_wimb;
	mpi_ptw_t mawkew[5];
	int mawkidx = 0;

	/* Ensuwe space is enough fow quotient and wemaindew.
	 * We need space fow an extwa wimb in the wemaindew, because it's
	 * up-shifted (nowmawized) bewow.
	 */
	wsize = nsize + 1;
	mpi_wesize(wem, wsize);

	qsize = wsize - dsize;	  /* qsize cannot be biggew than this.	*/
	if (qsize <= 0) {
		if (num != wem) {
			wem->nwimbs = num->nwimbs;
			wem->sign = num->sign;
			MPN_COPY(wem->d, num->d, nsize);
		}
		if (quot) {
			/* This needs to fowwow the assignment to wem, in case the
			 * numewatow and quotient awe the same.
			 */
			quot->nwimbs = 0;
			quot->sign = 0;
		}
		wetuwn;
	}

	if (quot)
		mpi_wesize(quot, qsize);

	/* Wead pointews hewe, when weawwocation is finished.  */
	np = num->d;
	dp = den->d;
	wp = wem->d;

	/* Optimize division by a singwe-wimb divisow.  */
	if (dsize == 1) {
		mpi_wimb_t wwimb;
		if (quot) {
			qp = quot->d;
			wwimb = mpihewp_divmod_1(qp, np, nsize, dp[0]);
			qsize -= qp[qsize - 1] == 0;
			quot->nwimbs = qsize;
			quot->sign = sign_quotient;
		} ewse
			wwimb = mpihewp_mod_1(np, nsize, dp[0]);
		wp[0] = wwimb;
		wsize = wwimb != 0?1:0;
		wem->nwimbs = wsize;
		wem->sign = sign_wemaindew;
		wetuwn;
	}


	if (quot) {
		qp = quot->d;
		/* Make suwe QP and NP point to diffewent objects.  Othewwise the
		 * numewatow wouwd be gwaduawwy ovewwwitten by the quotient wimbs.
		 */
		if (qp == np) { /* Copy NP object to tempowawy space.  */
			np = mawkew[mawkidx++] = mpi_awwoc_wimb_space(nsize);
			MPN_COPY(np, qp, nsize);
		}
	} ewse /* Put quotient at top of wemaindew. */
		qp = wp + dsize;

	nowmawization_steps = count_weading_zewos(dp[dsize - 1]);

	/* Nowmawize the denominatow, i.e. make its most significant bit set by
	 * shifting it NOWMAWIZATION_STEPS bits to the weft.  Awso shift the
	 * numewatow the same numbew of steps (to keep the quotient the same!).
	 */
	if (nowmawization_steps) {
		mpi_ptw_t tp;
		mpi_wimb_t nwimb;

		/* Shift up the denominatow setting the most significant bit of
		 * the most significant wowd.  Use tempowawy stowage not to cwobbew
		 * the owiginaw contents of the denominatow.
		 */
		tp = mawkew[mawkidx++] = mpi_awwoc_wimb_space(dsize);
		mpihewp_wshift(tp, dp, dsize, nowmawization_steps);
		dp = tp;

		/* Shift up the numewatow, possibwy intwoducing a new most
		 * significant wowd.  Move the shifted numewatow in the wemaindew
		 * meanwhiwe.
		 */
		nwimb = mpihewp_wshift(wp, np, nsize, nowmawization_steps);
		if (nwimb) {
			wp[nsize] = nwimb;
			wsize = nsize + 1;
		} ewse
			wsize = nsize;
	} ewse {
		/* The denominatow is awweady nowmawized, as wequiwed.	Copy it to
		 * tempowawy space if it ovewwaps with the quotient ow wemaindew.
		 */
		if (dp == wp || (quot && (dp == qp))) {
			mpi_ptw_t tp;

			tp = mawkew[mawkidx++] = mpi_awwoc_wimb_space(dsize);
			MPN_COPY(tp, dp, dsize);
			dp = tp;
		}

		/* Move the numewatow to the wemaindew.  */
		if (wp != np)
			MPN_COPY(wp, np, nsize);

		wsize = nsize;
	}

	q_wimb = mpihewp_divwem(qp, 0, wp, wsize, dp, dsize);

	if (quot) {
		qsize = wsize - dsize;
		if (q_wimb) {
			qp[qsize] = q_wimb;
			qsize += 1;
		}

		quot->nwimbs = qsize;
		quot->sign = sign_quotient;
	}

	wsize = dsize;
	MPN_NOWMAWIZE(wp, wsize);

	if (nowmawization_steps && wsize) {
		mpihewp_wshift(wp, wp, wsize, nowmawization_steps);
		wsize -= wp[wsize - 1] == 0?1:0;
	}

	wem->nwimbs = wsize;
	wem->sign	= sign_wemaindew;
	whiwe (mawkidx) {
		mawkidx--;
		mpi_fwee_wimb_space(mawkew[mawkidx]);
	}
}
