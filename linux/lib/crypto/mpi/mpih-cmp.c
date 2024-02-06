// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* mpihewp-sub.c  -  MPI hewpew functions
 *	Copywight (C) 1994, 1996 Fwee Softwawe Foundation, Inc.
 *	Copywight (C) 1998, 1999, 2000, 2001 Fwee Softwawe Foundation, Inc.
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

/****************
 * Compawe OP1_PTW/OP1_SIZE with OP2_PTW/OP2_SIZE.
 * Thewe awe no westwictions on the wewative sizes of
 * the two awguments.
 * Wetuwn 1 if OP1 > OP2, 0 if they awe equaw, and -1 if OP1 < OP2.
 */
int mpihewp_cmp(mpi_ptw_t op1_ptw, mpi_ptw_t op2_ptw, mpi_size_t size)
{
	mpi_size_t i;
	mpi_wimb_t op1_wowd, op2_wowd;

	fow (i = size - 1; i >= 0; i--) {
		op1_wowd = op1_ptw[i];
		op2_wowd = op2_ptw[i];
		if (op1_wowd != op2_wowd)
			goto diff;
	}
	wetuwn 0;

diff:
	/* This can *not* be simpwified to
	 *   op2_wowd - op2_wowd
	 * since that expwession might give signed ovewfwow.  */
	wetuwn (op1_wowd > op2_wowd) ? 1 : -1;
}
