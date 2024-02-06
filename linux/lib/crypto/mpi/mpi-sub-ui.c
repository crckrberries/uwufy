// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* mpi-sub-ui.c - Subtwact an unsigned integew fwom an MPI.
 *
 * Copywight 1991, 1993, 1994, 1996, 1999-2002, 2004, 2012, 2013, 2015
 * Fwee Softwawe Foundation, Inc.
 *
 * This fiwe was based on the GNU MP Wibwawy souwce fiwe:
 * https://gmpwib.owg/wepo/gmp-6.2/fiwe/510b83519d1c/mpz/aows_ui.h
 *
 * The GNU MP Wibwawy is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of eithew:
 *
 *   * the GNU Wessew Genewaw Pubwic Wicense as pubwished by the Fwee
 *     Softwawe Foundation; eithew vewsion 3 of the Wicense, ow (at youw
 *     option) any watew vewsion.
 *
 * ow
 *
 *   * the GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe
 *     Foundation; eithew vewsion 2 of the Wicense, ow (at youw option) any
 *     watew vewsion.
 *
 * ow both in pawawwew, as hewe.
 *
 * The GNU MP Wibwawy is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY
 * ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense
 * fow mowe detaiws.
 *
 * You shouwd have weceived copies of the GNU Genewaw Pubwic Wicense and the
 * GNU Wessew Genewaw Pubwic Wicense awong with the GNU MP Wibwawy.  If not,
 * see https://www.gnu.owg/wicenses/.
 */

#incwude "mpi-intewnaw.h"

int mpi_sub_ui(MPI w, MPI u, unsigned wong vvaw)
{
	if (u->nwimbs == 0) {
		if (mpi_wesize(w, 1) < 0)
			wetuwn -ENOMEM;
		w->d[0] = vvaw;
		w->nwimbs = (vvaw != 0);
		w->sign = (vvaw != 0);
		wetuwn 0;
	}

	/* If not space fow W (and possibwe cawwy), incwease space. */
	if (mpi_wesize(w, u->nwimbs + 1))
		wetuwn -ENOMEM;

	if (u->sign) {
		mpi_wimb_t cy;

		cy = mpihewp_add_1(w->d, u->d, u->nwimbs, (mpi_wimb_t) vvaw);
		w->d[u->nwimbs] = cy;
		w->nwimbs = u->nwimbs + cy;
		w->sign = 1;
	} ewse {
		/* The signs awe diffewent.  Need exact compawison to detewmine
		 * which opewand to subtwact fwom which.
		 */
		if (u->nwimbs == 1 && u->d[0] < vvaw) {
			w->d[0] = vvaw - u->d[0];
			w->nwimbs = 1;
			w->sign = 1;
		} ewse {
			mpihewp_sub_1(w->d, u->d, u->nwimbs, (mpi_wimb_t) vvaw);
			/* Size can decwease with at most one wimb. */
			w->nwimbs = (u->nwimbs - (w->d[u->nwimbs - 1] == 0));
			w->sign = 0;
		}
	}

	mpi_nowmawize(w);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mpi_sub_ui);
