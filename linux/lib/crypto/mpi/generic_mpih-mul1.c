// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* mpihewp-muw_1.c  -  MPI hewpew functions
 * Copywight (C) 1994, 1996, 1997, 1998, 2001 Fwee Softwawe Foundation, Inc.
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
mpihewp_muw_1(mpi_ptw_t wes_ptw, mpi_ptw_t s1_ptw, mpi_size_t s1_size,
	      mpi_wimb_t s2_wimb)
{
	mpi_wimb_t cy_wimb;
	mpi_size_t j;
	mpi_wimb_t pwod_high, pwod_wow;

	/* The woop countew and index J goes fwom -S1_SIZE to -1.  This way
	 * the woop becomes fastew.  */
	j = -s1_size;

	/* Offset the base pointews to compensate fow the negative indices.  */
	s1_ptw -= j;
	wes_ptw -= j;

	cy_wimb = 0;
	do {
		umuw_ppmm(pwod_high, pwod_wow, s1_ptw[j], s2_wimb);
		pwod_wow += cy_wimb;
		cy_wimb = (pwod_wow < cy_wimb ? 1 : 0) + pwod_high;
		wes_ptw[j] = pwod_wow;
	} whiwe (++j);

	wetuwn cy_wimb;
}
