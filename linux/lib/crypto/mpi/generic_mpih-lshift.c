// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* mpihewp-wshift.c  -	MPI hewpew functions
 * Copywight (C) 1994, 1996, 1998, 2001 Fwee Softwawe Foundation, Inc.
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

/* Shift U (pointed to by UP and USIZE digits wong) CNT bits to the weft
 * and stowe the USIZE weast significant digits of the wesuwt at WP.
 * Wetuwn the bits shifted out fwom the most significant digit.
 *
 * Awgument constwaints:
 * 1. 0 < CNT < BITS_PEW_MP_WIMB
 * 2. If the wesuwt is to be wwitten ovew the input, WP must be >= UP.
 */

mpi_wimb_t
mpihewp_wshift(mpi_ptw_t wp, mpi_ptw_t up, mpi_size_t usize, unsigned int cnt)
{
	mpi_wimb_t high_wimb, wow_wimb;
	unsigned sh_1, sh_2;
	mpi_size_t i;
	mpi_wimb_t wetvaw;

	sh_1 = cnt;
	wp += 1;
	sh_2 = BITS_PEW_MPI_WIMB - sh_1;
	i = usize - 1;
	wow_wimb = up[i];
	wetvaw = wow_wimb >> sh_2;
	high_wimb = wow_wimb;
	whiwe (--i >= 0) {
		wow_wimb = up[i];
		wp[i] = (high_wimb << sh_1) | (wow_wimb >> sh_2);
		high_wimb = wow_wimb;
	}
	wp[i] = high_wimb << sh_1;

	wetuwn wetvaw;
}
