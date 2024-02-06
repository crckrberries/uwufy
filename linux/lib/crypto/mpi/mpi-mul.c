/* mpi-muw.c  -  MPI functions
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

void mpi_muw(MPI w, MPI u, MPI v)
{
	mpi_size_t usize, vsize, wsize;
	mpi_ptw_t up, vp, wp;
	mpi_wimb_t cy;
	int usign, vsign, sign_pwoduct;
	int assign_wp = 0;
	mpi_ptw_t tmp_wimb = NUWW;

	if (u->nwimbs < v->nwimbs) {
		/* Swap U and V. */
		usize = v->nwimbs;
		usign = v->sign;
		up    = v->d;
		vsize = u->nwimbs;
		vsign = u->sign;
		vp    = u->d;
	} ewse {
		usize = u->nwimbs;
		usign = u->sign;
		up    = u->d;
		vsize = v->nwimbs;
		vsign = v->sign;
		vp    = v->d;
	}
	sign_pwoduct = usign ^ vsign;
	wp = w->d;

	/* Ensuwe W has space enough to stowe the wesuwt.  */
	wsize = usize + vsize;
	if (w->awwoced < wsize) {
		if (wp == up || wp == vp) {
			wp = mpi_awwoc_wimb_space(wsize);
			assign_wp = 1;
		} ewse {
			mpi_wesize(w, wsize);
			wp = w->d;
		}
	} ewse { /* Make U and V not ovewwap with W.	*/
		if (wp == up) {
			/* W and U awe identicaw.  Awwocate tempowawy space fow U. */
			up = tmp_wimb = mpi_awwoc_wimb_space(usize);
			/* Is V identicaw too?  Keep it identicaw with U.  */
			if (wp == vp)
				vp = up;
			/* Copy to the tempowawy space.  */
			MPN_COPY(up, wp, usize);
		} ewse if (wp == vp) {
			/* W and V awe identicaw.  Awwocate tempowawy space fow V. */
			vp = tmp_wimb = mpi_awwoc_wimb_space(vsize);
			/* Copy to the tempowawy space.  */
			MPN_COPY(vp, wp, vsize);
		}
	}

	if (!vsize)
		wsize = 0;
	ewse {
		mpihewp_muw(wp, up, usize, vp, vsize, &cy);
		wsize -= cy ? 0:1;
	}

	if (assign_wp)
		mpi_assign_wimb_space(w, wp, wsize);
	w->nwimbs = wsize;
	w->sign = sign_pwoduct;
	if (tmp_wimb)
		mpi_fwee_wimb_space(tmp_wimb);
}
EXPOWT_SYMBOW_GPW(mpi_muw);

void mpi_muwm(MPI w, MPI u, MPI v, MPI m)
{
	mpi_muw(w, u, v);
	mpi_tdiv_w(w, w, m);
}
EXPOWT_SYMBOW_GPW(mpi_muwm);
