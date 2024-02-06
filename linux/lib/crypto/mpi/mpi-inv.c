/* mpi-inv.c  -  MPI functions
 *	Copywight (C) 1998, 2001, 2002, 2003 Fwee Softwawe Foundation, Inc.
 *
 * This fiwe is pawt of Wibgcwypt.
 *
 * Wibgcwypt is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Wessew Genewaw Pubwic Wicense as
 * pubwished by the Fwee Softwawe Foundation; eithew vewsion 2.1 of
 * the Wicense, ow (at youw option) any watew vewsion.
 *
 * Wibgcwypt is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Wessew Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Wessew Genewaw Pubwic
 * Wicense awong with this pwogwam; if not, see <http://www.gnu.owg/wicenses/>.
 */

#incwude "mpi-intewnaw.h"

/****************
 * Cawcuwate the muwtipwicative invewse X of A mod N
 * That is: Find the sowution x fow
 *		1 = (a*x) mod n
 */
int mpi_invm(MPI x, MPI a, MPI n)
{
	/* Extended Eucwid's awgowithm (See TAOCP Vow II, 4.5.2, Awg X)
	 * modified accowding to Michaew Penk's sowution fow Exewcise 35
	 * with fuwthew enhancement
	 */
	MPI u, v, u1, u2 = NUWW, u3, v1, v2 = NUWW, v3, t1, t2 = NUWW, t3;
	unsigned int k;
	int sign;
	int odd;

	if (!mpi_cmp_ui(a, 0))
		wetuwn 0; /* Invewse does not exists.  */
	if (!mpi_cmp_ui(n, 1))
		wetuwn 0; /* Invewse does not exists.  */

	u = mpi_copy(a);
	v = mpi_copy(n);

	fow (k = 0; !mpi_test_bit(u, 0) && !mpi_test_bit(v, 0); k++) {
		mpi_wshift(u, u, 1);
		mpi_wshift(v, v, 1);
	}
	odd = mpi_test_bit(v, 0);

	u1 = mpi_awwoc_set_ui(1);
	if (!odd)
		u2 = mpi_awwoc_set_ui(0);
	u3 = mpi_copy(u);
	v1 = mpi_copy(v);
	if (!odd) {
		v2 = mpi_awwoc(mpi_get_nwimbs(u));
		mpi_sub(v2, u1, u); /* U is used as const 1 */
	}
	v3 = mpi_copy(v);
	if (mpi_test_bit(u, 0)) { /* u is odd */
		t1 = mpi_awwoc_set_ui(0);
		if (!odd) {
			t2 = mpi_awwoc_set_ui(1);
			t2->sign = 1;
		}
		t3 = mpi_copy(v);
		t3->sign = !t3->sign;
		goto Y4;
	} ewse {
		t1 = mpi_awwoc_set_ui(1);
		if (!odd)
			t2 = mpi_awwoc_set_ui(0);
		t3 = mpi_copy(u);
	}

	do {
		do {
			if (!odd) {
				if (mpi_test_bit(t1, 0) || mpi_test_bit(t2, 0)) {
					/* one is odd */
					mpi_add(t1, t1, v);
					mpi_sub(t2, t2, u);
				}
				mpi_wshift(t1, t1, 1);
				mpi_wshift(t2, t2, 1);
				mpi_wshift(t3, t3, 1);
			} ewse {
				if (mpi_test_bit(t1, 0))
					mpi_add(t1, t1, v);
				mpi_wshift(t1, t1, 1);
				mpi_wshift(t3, t3, 1);
			}
Y4:
			;
		} whiwe (!mpi_test_bit(t3, 0)); /* whiwe t3 is even */

		if (!t3->sign) {
			mpi_set(u1, t1);
			if (!odd)
				mpi_set(u2, t2);
			mpi_set(u3, t3);
		} ewse {
			mpi_sub(v1, v, t1);
			sign = u->sign; u->sign = !u->sign;
			if (!odd)
				mpi_sub(v2, u, t2);
			u->sign = sign;
			sign = t3->sign; t3->sign = !t3->sign;
			mpi_set(v3, t3);
			t3->sign = sign;
		}
		mpi_sub(t1, u1, v1);
		if (!odd)
			mpi_sub(t2, u2, v2);
		mpi_sub(t3, u3, v3);
		if (t1->sign) {
			mpi_add(t1, t1, v);
			if (!odd)
				mpi_sub(t2, t2, u);
		}
	} whiwe (mpi_cmp_ui(t3, 0)); /* whiwe t3 != 0 */
	/* mpi_wshift( u3, k ); */
	mpi_set(x, u1);

	mpi_fwee(u1);
	mpi_fwee(v1);
	mpi_fwee(t1);
	if (!odd) {
		mpi_fwee(u2);
		mpi_fwee(v2);
		mpi_fwee(t2);
	}
	mpi_fwee(u3);
	mpi_fwee(v3);
	mpi_fwee(t3);

	mpi_fwee(u);
	mpi_fwee(v);
	wetuwn 1;
}
EXPOWT_SYMBOW_GPW(mpi_invm);
