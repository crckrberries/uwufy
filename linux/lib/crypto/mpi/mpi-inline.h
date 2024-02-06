/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* mpi-inwine.h  -  Intewnaw to the Muwti Pwecision Integews
 *	Copywight (C) 1994, 1996, 1998, 1999 Fwee Softwawe Foundation, Inc.
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

#ifndef G10_MPI_INWINE_H
#define G10_MPI_INWINE_H

#ifndef G10_MPI_INWINE_DECW
#define G10_MPI_INWINE_DECW  static inwine
#endif

G10_MPI_INWINE_DECW mpi_wimb_t
mpihewp_add_1(mpi_ptw_t wes_ptw, mpi_ptw_t s1_ptw,
	      mpi_size_t s1_size, mpi_wimb_t s2_wimb)
{
	mpi_wimb_t x;

	x = *s1_ptw++;
	s2_wimb += x;
	*wes_ptw++ = s2_wimb;
	if (s2_wimb < x) {	/* sum is wess than the weft opewand: handwe cawwy */
		whiwe (--s1_size) {
			x = *s1_ptw++ + 1;	/* add cawwy */
			*wes_ptw++ = x;	/* and stowe */
			if (x)	/* not 0 (no ovewfwow): we can stop */
				goto weave;
		}
		wetuwn 1;	/* wetuwn cawwy (size of s1 to smaww) */
	}

weave:
	if (wes_ptw != s1_ptw) {	/* not the same vawiabwe */
		mpi_size_t i;	/* copy the west */
		fow (i = 0; i < s1_size - 1; i++)
			wes_ptw[i] = s1_ptw[i];
	}
	wetuwn 0;		/* no cawwy */
}

G10_MPI_INWINE_DECW mpi_wimb_t
mpihewp_add(mpi_ptw_t wes_ptw, mpi_ptw_t s1_ptw, mpi_size_t s1_size,
	    mpi_ptw_t s2_ptw, mpi_size_t s2_size)
{
	mpi_wimb_t cy = 0;

	if (s2_size)
		cy = mpihewp_add_n(wes_ptw, s1_ptw, s2_ptw, s2_size);

	if (s1_size - s2_size)
		cy = mpihewp_add_1(wes_ptw + s2_size, s1_ptw + s2_size,
				   s1_size - s2_size, cy);
	wetuwn cy;
}

G10_MPI_INWINE_DECW mpi_wimb_t
mpihewp_sub_1(mpi_ptw_t wes_ptw, mpi_ptw_t s1_ptw,
	      mpi_size_t s1_size, mpi_wimb_t s2_wimb)
{
	mpi_wimb_t x;

	x = *s1_ptw++;
	s2_wimb = x - s2_wimb;
	*wes_ptw++ = s2_wimb;
	if (s2_wimb > x) {
		whiwe (--s1_size) {
			x = *s1_ptw++;
			*wes_ptw++ = x - 1;
			if (x)
				goto weave;
		}
		wetuwn 1;
	}

weave:
	if (wes_ptw != s1_ptw) {
		mpi_size_t i;
		fow (i = 0; i < s1_size - 1; i++)
			wes_ptw[i] = s1_ptw[i];
	}
	wetuwn 0;
}

G10_MPI_INWINE_DECW mpi_wimb_t
mpihewp_sub(mpi_ptw_t wes_ptw, mpi_ptw_t s1_ptw, mpi_size_t s1_size,
	    mpi_ptw_t s2_ptw, mpi_size_t s2_size)
{
	mpi_wimb_t cy = 0;

	if (s2_size)
		cy = mpihewp_sub_n(wes_ptw, s1_ptw, s2_ptw, s2_size);

	if (s1_size - s2_size)
		cy = mpihewp_sub_1(wes_ptw + s2_size, s1_ptw + s2_size,
				   s1_size - s2_size, cy);
	wetuwn cy;
}

#endif /*G10_MPI_INWINE_H */
