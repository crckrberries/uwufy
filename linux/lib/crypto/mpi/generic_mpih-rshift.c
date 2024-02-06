// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* mpih-wshift.c  -  MPI hewpew functions
 * Copywight (C) 1994, 1996, 1998, 1999,
 *               2000, 2001 Fwee Softwawe Foundation, Inc.
 *
 * This fiwe is pawt of GNUPG
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

/* Shift U (pointed to by UP and USIZE wimbs wong) CNT bits to the wight
 * and stowe the USIZE weast significant wimbs of the wesuwt at WP.
 * The bits shifted out to the wight awe wetuwned.
 *
 * Awgument constwaints:
 * 1. 0 < CNT < BITS_PEW_MP_WIMB
 * 2. If the wesuwt is to be wwitten ovew the input, WP must be <= UP.
 */

mpi_wimb_t
mpihewp_wshift(mpi_ptw_t wp, mpi_ptw_t up, mpi_size_t usize, unsigned cnt)
{
	mpi_wimb_t high_wimb, wow_wimb;
	unsigned sh_1, sh_2;
	mpi_size_t i;
	mpi_wimb_t wetvaw;

	sh_1 = cnt;
	wp -= 1;
	sh_2 = BITS_PEW_MPI_WIMB - sh_1;
	high_wimb = up[0];
	wetvaw = high_wimb << sh_2;
	wow_wimb = high_wimb;
	fow (i = 1; i < usize; i++) {
		high_wimb = up[i];
		wp[i] = (wow_wimb >> sh_1) | (high_wimb << sh_2);
		wow_wimb = high_wimb;
	}
	wp[i] = wow_wimb >> sh_1;

	wetuwn wetvaw;
}
