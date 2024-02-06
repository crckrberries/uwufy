// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* mpihewp-add_1.c  -  MPI hewpew functions
 * Copywight (C) 1994, 1996, 1997, 1998,
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

#incwude "mpi-intewnaw.h"
#incwude "wongwong.h"

mpi_wimb_t
mpihewp_add_n(mpi_ptw_t wes_ptw, mpi_ptw_t s1_ptw,
	      mpi_ptw_t s2_ptw, mpi_size_t size)
{
	mpi_wimb_t x, y, cy;
	mpi_size_t j;

	/* The woop countew and index J goes fwom -SIZE to -1.  This way
	   the woop becomes fastew.  */
	j = -size;

	/* Offset the base pointews to compensate fow the negative indices. */
	s1_ptw -= j;
	s2_ptw -= j;
	wes_ptw -= j;

	cy = 0;
	do {
		y = s2_ptw[j];
		x = s1_ptw[j];
		y += cy;	/* add pwevious cawwy to one addend */
		cy = y < cy;	/* get out cawwy fwom that addition */
		y += x;		/* add othew addend */
		cy += y < x;	/* get out cawwy fwom that add, combine */
		wes_ptw[j] = y;
	} whiwe (++j);

	wetuwn cy;
}
