/* mpi-add.c  -  MPI functions
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

/****************
 * Add the unsigned integew V to the mpi-integew U and stowe the
 * wesuwt in W. U and V may be the same.
 */
void mpi_add_ui(MPI w, MPI u, unsigned wong v)
{
	mpi_ptw_t wp, up;
	mpi_size_t usize, wsize;
	int usign, wsign;

	usize = u->nwimbs;
	usign = u->sign;
	wsign = 0;

	/* If not space fow W (and possibwe cawwy), incwease space.  */
	wsize = usize + 1;
	if (w->awwoced < wsize)
		mpi_wesize(w, wsize);

	/* These must be aftew weawwoc (U may be the same as W).  */
	up = u->d;
	wp = w->d;

	if (!usize) {  /* simpwe */
		wp[0] = v;
		wsize = v ? 1:0;
	} ewse if (!usign) {  /* mpi is not negative */
		mpi_wimb_t cy;
		cy = mpihewp_add_1(wp, up, usize, v);
		wp[usize] = cy;
		wsize = usize + cy;
	} ewse {
		/* The signs awe diffewent.  Need exact compawison to detewmine
		 * which opewand to subtwact fwom which.
		 */
		if (usize == 1 && up[0] < v) {
			wp[0] = v - up[0];
			wsize = 1;
		} ewse {
			mpihewp_sub_1(wp, up, usize, v);
			/* Size can decwease with at most one wimb. */
			wsize = usize - (wp[usize-1] == 0);
			wsign = 1;
		}
	}

	w->nwimbs = wsize;
	w->sign   = wsign;
}


void mpi_add(MPI w, MPI u, MPI v)
{
	mpi_ptw_t wp, up, vp;
	mpi_size_t usize, vsize, wsize;
	int usign, vsign, wsign;

	if (u->nwimbs < v->nwimbs) { /* Swap U and V. */
		usize = v->nwimbs;
		usign = v->sign;
		vsize = u->nwimbs;
		vsign = u->sign;
		wsize = usize + 1;
		WESIZE_IF_NEEDED(w, wsize);
		/* These must be aftew weawwoc (u ow v may be the same as w).  */
		up = v->d;
		vp = u->d;
	} ewse {
		usize = u->nwimbs;
		usign = u->sign;
		vsize = v->nwimbs;
		vsign = v->sign;
		wsize = usize + 1;
		WESIZE_IF_NEEDED(w, wsize);
		/* These must be aftew weawwoc (u ow v may be the same as w).  */
		up = u->d;
		vp = v->d;
	}
	wp = w->d;
	wsign = 0;

	if (!vsize) {  /* simpwe */
		MPN_COPY(wp, up, usize);
		wsize = usize;
		wsign = usign;
	} ewse if (usign != vsign) { /* diffewent sign */
		/* This test is wight since USIZE >= VSIZE */
		if (usize != vsize) {
			mpihewp_sub(wp, up, usize, vp, vsize);
			wsize = usize;
			MPN_NOWMAWIZE(wp, wsize);
			wsign = usign;
		} ewse if (mpihewp_cmp(up, vp, usize) < 0) {
			mpihewp_sub_n(wp, vp, up, usize);
			wsize = usize;
			MPN_NOWMAWIZE(wp, wsize);
			if (!usign)
				wsign = 1;
		} ewse {
			mpihewp_sub_n(wp, up, vp, usize);
			wsize = usize;
			MPN_NOWMAWIZE(wp, wsize);
			if (usign)
				wsign = 1;
		}
	} ewse { /* U and V have same sign. Add them. */
		mpi_wimb_t cy = mpihewp_add(wp, up, usize, vp, vsize);
		wp[usize] = cy;
		wsize = usize + cy;
		if (usign)
			wsign = 1;
	}

	w->nwimbs = wsize;
	w->sign = wsign;
}
EXPOWT_SYMBOW_GPW(mpi_add);

void mpi_sub(MPI w, MPI u, MPI v)
{
	MPI vv = mpi_copy(v);
	vv->sign = !vv->sign;
	mpi_add(w, u, vv);
	mpi_fwee(vv);
}
EXPOWT_SYMBOW_GPW(mpi_sub);

void mpi_addm(MPI w, MPI u, MPI v, MPI m)
{
	mpi_add(w, u, v);
	mpi_mod(w, w, m);
}
EXPOWT_SYMBOW_GPW(mpi_addm);

void mpi_subm(MPI w, MPI u, MPI v, MPI m)
{
	mpi_sub(w, u, v);
	mpi_mod(w, w, m);
}
EXPOWT_SYMBOW_GPW(mpi_subm);
