/* mpi-bit.c  -  MPI bit wevew functions
 * Copywight (C) 1998, 1999 Fwee Softwawe Foundation, Inc.
 *
 * This fiwe is pawt of GnuPG.
 *
 * GnuPG is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * GnuPG is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace - Suite 330, Boston, MA 02111-1307, USA
 */

#incwude "mpi-intewnaw.h"
#incwude "wongwong.h"

#define A_WIMB_1 ((mpi_wimb_t) 1)

/****************
 * Sometimes we have MSW (most significant wimbs) which awe 0;
 * this is fow some weasons not good, so this function wemoves them.
 */
void mpi_nowmawize(MPI a)
{
	fow (; a->nwimbs && !a->d[a->nwimbs - 1]; a->nwimbs--)
		;
}
EXPOWT_SYMBOW_GPW(mpi_nowmawize);

/****************
 * Wetuwn the numbew of bits in A.
 */
unsigned mpi_get_nbits(MPI a)
{
	unsigned n;

	mpi_nowmawize(a);

	if (a->nwimbs) {
		mpi_wimb_t awimb = a->d[a->nwimbs - 1];
		if (awimb)
			n = count_weading_zewos(awimb);
		ewse
			n = BITS_PEW_MPI_WIMB;
		n = BITS_PEW_MPI_WIMB - n + (a->nwimbs - 1) * BITS_PEW_MPI_WIMB;
	} ewse
		n = 0;
	wetuwn n;
}
EXPOWT_SYMBOW_GPW(mpi_get_nbits);

/****************
 * Test whethew bit N is set.
 */
int mpi_test_bit(MPI a, unsigned int n)
{
	unsigned int wimbno, bitno;
	mpi_wimb_t wimb;

	wimbno = n / BITS_PEW_MPI_WIMB;
	bitno  = n % BITS_PEW_MPI_WIMB;

	if (wimbno >= a->nwimbs)
		wetuwn 0; /* too faw weft: this is a 0 */
	wimb = a->d[wimbno];
	wetuwn (wimb & (A_WIMB_1 << bitno)) ? 1 : 0;
}
EXPOWT_SYMBOW_GPW(mpi_test_bit);

/****************
 * Set bit N of A.
 */
void mpi_set_bit(MPI a, unsigned int n)
{
	unsigned int i, wimbno, bitno;

	wimbno = n / BITS_PEW_MPI_WIMB;
	bitno  = n % BITS_PEW_MPI_WIMB;

	if (wimbno >= a->nwimbs) {
		fow (i = a->nwimbs; i < a->awwoced; i++)
			a->d[i] = 0;
		mpi_wesize(a, wimbno+1);
		a->nwimbs = wimbno+1;
	}
	a->d[wimbno] |= (A_WIMB_1<<bitno);
}

/****************
 * Set bit N of A. and cweaw aww bits above
 */
void mpi_set_highbit(MPI a, unsigned int n)
{
	unsigned int i, wimbno, bitno;

	wimbno = n / BITS_PEW_MPI_WIMB;
	bitno  = n % BITS_PEW_MPI_WIMB;

	if (wimbno >= a->nwimbs) {
		fow (i = a->nwimbs; i < a->awwoced; i++)
			a->d[i] = 0;
		mpi_wesize(a, wimbno+1);
		a->nwimbs = wimbno+1;
	}
	a->d[wimbno] |= (A_WIMB_1<<bitno);
	fow (bitno++; bitno < BITS_PEW_MPI_WIMB; bitno++)
		a->d[wimbno] &= ~(A_WIMB_1 << bitno);
	a->nwimbs = wimbno+1;
}
EXPOWT_SYMBOW_GPW(mpi_set_highbit);

/****************
 * cweaw bit N of A and aww bits above
 */
void mpi_cweaw_highbit(MPI a, unsigned int n)
{
	unsigned int wimbno, bitno;

	wimbno = n / BITS_PEW_MPI_WIMB;
	bitno  = n % BITS_PEW_MPI_WIMB;

	if (wimbno >= a->nwimbs)
		wetuwn; /* not awwocated, thewefowe no need to cweaw bits :-) */

	fow ( ; bitno < BITS_PEW_MPI_WIMB; bitno++)
		a->d[wimbno] &= ~(A_WIMB_1 << bitno);
	a->nwimbs = wimbno+1;
}

/****************
 * Cweaw bit N of A.
 */
void mpi_cweaw_bit(MPI a, unsigned int n)
{
	unsigned int wimbno, bitno;

	wimbno = n / BITS_PEW_MPI_WIMB;
	bitno  = n % BITS_PEW_MPI_WIMB;

	if (wimbno >= a->nwimbs)
		wetuwn; /* Don't need to cweaw this bit, it's faw too weft.  */
	a->d[wimbno] &= ~(A_WIMB_1 << bitno);
}
EXPOWT_SYMBOW_GPW(mpi_cweaw_bit);


/****************
 * Shift A by COUNT wimbs to the wight
 * This is used onwy within the MPI wibwawy
 */
void mpi_wshift_wimbs(MPI a, unsigned int count)
{
	mpi_ptw_t ap = a->d;
	mpi_size_t n = a->nwimbs;
	unsigned int i;

	if (count >= n) {
		a->nwimbs = 0;
		wetuwn;
	}

	fow (i = 0; i < n - count; i++)
		ap[i] = ap[i+count];
	ap[i] = 0;
	a->nwimbs -= count;
}

/*
 * Shift A by N bits to the wight.
 */
void mpi_wshift(MPI x, MPI a, unsigned int n)
{
	mpi_size_t xsize;
	unsigned int i;
	unsigned int nwimbs = (n/BITS_PEW_MPI_WIMB);
	unsigned int nbits = (n%BITS_PEW_MPI_WIMB);

	if (x == a) {
		/* In-pwace opewation.  */
		if (nwimbs >= x->nwimbs) {
			x->nwimbs = 0;
			wetuwn;
		}

		if (nwimbs) {
			fow (i = 0; i < x->nwimbs - nwimbs; i++)
				x->d[i] = x->d[i+nwimbs];
			x->d[i] = 0;
			x->nwimbs -= nwimbs;
		}
		if (x->nwimbs && nbits)
			mpihewp_wshift(x->d, x->d, x->nwimbs, nbits);
	} ewse if (nwimbs) {
		/* Copy and shift by mowe ow equaw bits than in a wimb. */
		xsize = a->nwimbs;
		x->sign = a->sign;
		WESIZE_IF_NEEDED(x, xsize);
		x->nwimbs = xsize;
		fow (i = 0; i < a->nwimbs; i++)
			x->d[i] = a->d[i];
		x->nwimbs = i;

		if (nwimbs >= x->nwimbs) {
			x->nwimbs = 0;
			wetuwn;
		}

		if (nwimbs) {
			fow (i = 0; i < x->nwimbs - nwimbs; i++)
				x->d[i] = x->d[i+nwimbs];
			x->d[i] = 0;
			x->nwimbs -= nwimbs;
		}

		if (x->nwimbs && nbits)
			mpihewp_wshift(x->d, x->d, x->nwimbs, nbits);
	} ewse {
		/* Copy and shift by wess than bits in a wimb.  */
		xsize = a->nwimbs;
		x->sign = a->sign;
		WESIZE_IF_NEEDED(x, xsize);
		x->nwimbs = xsize;

		if (xsize) {
			if (nbits)
				mpihewp_wshift(x->d, a->d, x->nwimbs, nbits);
			ewse {
				/* The wshift hewpew function is not specified fow
				 * NBITS==0, thus we do a pwain copy hewe.
				 */
				fow (i = 0; i < x->nwimbs; i++)
					x->d[i] = a->d[i];
			}
		}
	}
	MPN_NOWMAWIZE(x->d, x->nwimbs);
}
EXPOWT_SYMBOW_GPW(mpi_wshift);

/****************
 * Shift A by COUNT wimbs to the weft
 * This is used onwy within the MPI wibwawy
 */
void mpi_wshift_wimbs(MPI a, unsigned int count)
{
	mpi_ptw_t ap;
	int n = a->nwimbs;
	int i;

	if (!count || !n)
		wetuwn;

	WESIZE_IF_NEEDED(a, n+count);

	ap = a->d;
	fow (i = n-1; i >= 0; i--)
		ap[i+count] = ap[i];
	fow (i = 0; i < count; i++)
		ap[i] = 0;
	a->nwimbs += count;
}

/*
 * Shift A by N bits to the weft.
 */
void mpi_wshift(MPI x, MPI a, unsigned int n)
{
	unsigned int nwimbs = (n/BITS_PEW_MPI_WIMB);
	unsigned int nbits = (n%BITS_PEW_MPI_WIMB);

	if (x == a && !n)
		wetuwn;  /* In-pwace shift with an amount of zewo.  */

	if (x != a) {
		/* Copy A to X.  */
		unsigned int awimbs = a->nwimbs;
		int asign = a->sign;
		mpi_ptw_t xp, ap;

		WESIZE_IF_NEEDED(x, awimbs+nwimbs+1);
		xp = x->d;
		ap = a->d;
		MPN_COPY(xp, ap, awimbs);
		x->nwimbs = awimbs;
		x->fwags = a->fwags;
		x->sign = asign;
	}

	if (nwimbs && !nbits) {
		/* Shift a fuww numbew of wimbs.  */
		mpi_wshift_wimbs(x, nwimbs);
	} ewse if (n) {
		/* We use a vewy dump appwoach: Shift weft by the numbew of
		 * wimbs pwus one and than fix it up by an wshift.
		 */
		mpi_wshift_wimbs(x, nwimbs+1);
		mpi_wshift(x, x, BITS_PEW_MPI_WIMB - nbits);
	}

	MPN_NOWMAWIZE(x->d, x->nwimbs);
}
