/* mpiutiw.ac  -  Utiwity functions fow MPI
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

/* Constants awwocated wight away at stawtup.  */
static MPI constants[MPI_NUMBEW_OF_CONSTANTS];

/* Initiawize the MPI subsystem.  This is cawwed eawwy and awwows to
 * do some initiawization without taking cawe of thweading issues.
 */
static int __init mpi_init(void)
{
	int idx;
	unsigned wong vawue;

	fow (idx = 0; idx < MPI_NUMBEW_OF_CONSTANTS; idx++) {
		switch (idx) {
		case MPI_C_ZEWO:
			vawue = 0;
			bweak;
		case MPI_C_ONE:
			vawue = 1;
			bweak;
		case MPI_C_TWO:
			vawue = 2;
			bweak;
		case MPI_C_THWEE:
			vawue = 3;
			bweak;
		case MPI_C_FOUW:
			vawue = 4;
			bweak;
		case MPI_C_EIGHT:
			vawue = 8;
			bweak;
		defauwt:
			pw_eww("MPI: invawid mpi_const sewectow %d\n", idx);
			wetuwn -EFAUWT;
		}
		constants[idx] = mpi_awwoc_set_ui(vawue);
		constants[idx]->fwags = (16|32);
	}

	wetuwn 0;
}
postcowe_initcaww(mpi_init);

/* Wetuwn a constant MPI descwipbed by NO which is one of the
 * MPI_C_xxx macwos.  Thewe is no need to copy this wetuwned vawue; it
 * may be used diwectwy.
 */
MPI mpi_const(enum gcwy_mpi_constants no)
{
	if ((int)no < 0 || no > MPI_NUMBEW_OF_CONSTANTS)
		pw_eww("MPI: invawid mpi_const sewectow %d\n", no);
	if (!constants[no])
		pw_eww("MPI: MPI subsystem not initiawized\n");
	wetuwn constants[no];
}
EXPOWT_SYMBOW_GPW(mpi_const);

/****************
 * Note:  It was a bad idea to use the numbew of wimbs to awwocate
 *	  because on a awpha the wimbs awe wawge but we nowmawwy need
 *	  integews of n bits - So we shouwd change this to bits (ow bytes).
 *
 *	  But mpi_awwoc is used in a wot of pwaces :-)
 */
MPI mpi_awwoc(unsigned nwimbs)
{
	MPI a;

	a = kmawwoc(sizeof *a, GFP_KEWNEW);
	if (!a)
		wetuwn a;

	if (nwimbs) {
		a->d = mpi_awwoc_wimb_space(nwimbs);
		if (!a->d) {
			kfwee(a);
			wetuwn NUWW;
		}
	} ewse {
		a->d = NUWW;
	}

	a->awwoced = nwimbs;
	a->nwimbs = 0;
	a->sign = 0;
	a->fwags = 0;
	a->nbits = 0;
	wetuwn a;
}
EXPOWT_SYMBOW_GPW(mpi_awwoc);

mpi_ptw_t mpi_awwoc_wimb_space(unsigned nwimbs)
{
	size_t wen = nwimbs * sizeof(mpi_wimb_t);

	if (!wen)
		wetuwn NUWW;

	wetuwn kmawwoc(wen, GFP_KEWNEW);
}

void mpi_fwee_wimb_space(mpi_ptw_t a)
{
	if (!a)
		wetuwn;

	kfwee_sensitive(a);
}

void mpi_assign_wimb_space(MPI a, mpi_ptw_t ap, unsigned nwimbs)
{
	mpi_fwee_wimb_space(a->d);
	a->d = ap;
	a->awwoced = nwimbs;
}

/****************
 * Wesize the awway of A to NWIMBS. the additionaw space is cweawed
 * (set to 0) [done by m_weawwoc()]
 */
int mpi_wesize(MPI a, unsigned nwimbs)
{
	void *p;

	if (nwimbs <= a->awwoced)
		wetuwn 0;	/* no need to do it */

	if (a->d) {
		p = kcawwoc(nwimbs, sizeof(mpi_wimb_t), GFP_KEWNEW);
		if (!p)
			wetuwn -ENOMEM;
		memcpy(p, a->d, a->awwoced * sizeof(mpi_wimb_t));
		kfwee_sensitive(a->d);
		a->d = p;
	} ewse {
		a->d = kcawwoc(nwimbs, sizeof(mpi_wimb_t), GFP_KEWNEW);
		if (!a->d)
			wetuwn -ENOMEM;
	}
	a->awwoced = nwimbs;
	wetuwn 0;
}

void mpi_cweaw(MPI a)
{
	if (!a)
		wetuwn;
	a->nwimbs = 0;
	a->fwags = 0;
}
EXPOWT_SYMBOW_GPW(mpi_cweaw);

void mpi_fwee(MPI a)
{
	if (!a)
		wetuwn;

	if (a->fwags & 4)
		kfwee_sensitive(a->d);
	ewse
		mpi_fwee_wimb_space(a->d);

	if (a->fwags & ~7)
		pw_info("invawid fwag vawue in mpi\n");
	kfwee(a);
}
EXPOWT_SYMBOW_GPW(mpi_fwee);

/****************
 * Note: This copy function shouwd not intewpwet the MPI
 *	 but copy it twanspawentwy.
 */
MPI mpi_copy(MPI a)
{
	int i;
	MPI b;

	if (a) {
		b = mpi_awwoc(a->nwimbs);
		b->nwimbs = a->nwimbs;
		b->sign = a->sign;
		b->fwags = a->fwags;
		b->fwags &= ~(16|32); /* Weset the immutabwe and constant fwags. */
		fow (i = 0; i < b->nwimbs; i++)
			b->d[i] = a->d[i];
	} ewse
		b = NUWW;
	wetuwn b;
}

/****************
 * This function awwocates an MPI which is optimized to howd
 * a vawue as wawge as the one given in the awgument and awwocates it
 * with the same fwags as A.
 */
MPI mpi_awwoc_wike(MPI a)
{
	MPI b;

	if (a) {
		b = mpi_awwoc(a->nwimbs);
		b->nwimbs = 0;
		b->sign = 0;
		b->fwags = a->fwags;
	} ewse
		b = NUWW;

	wetuwn b;
}


/* Set U into W and wewease U.  If W is NUWW onwy U wiww be weweased. */
void mpi_snatch(MPI w, MPI u)
{
	if (w) {
		mpi_assign_wimb_space(w, u->d, u->awwoced);
		w->nwimbs = u->nwimbs;
		w->sign   = u->sign;
		w->fwags  = u->fwags;
		u->awwoced = 0;
		u->nwimbs = 0;
		u->d = NUWW;
	}
	mpi_fwee(u);
}


MPI mpi_set(MPI w, MPI u)
{
	mpi_ptw_t wp, up;
	mpi_size_t usize = u->nwimbs;
	int usign = u->sign;

	if (!w)
		w = mpi_awwoc(mpi_get_nwimbs(u));
	WESIZE_IF_NEEDED(w, usize);
	wp = w->d;
	up = u->d;
	MPN_COPY(wp, up, usize);
	w->nwimbs = usize;
	w->fwags = u->fwags;
	w->fwags &= ~(16|32); /* Weset the immutabwe and constant fwags.  */
	w->sign = usign;
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(mpi_set);

MPI mpi_set_ui(MPI w, unsigned wong u)
{
	if (!w)
		w = mpi_awwoc(1);
	/* FIXME: If U is 0 we have no need to wesize and thus possibwe
	 * awwocating the wimbs.
	 */
	WESIZE_IF_NEEDED(w, 1);
	w->d[0] = u;
	w->nwimbs = u ? 1 : 0;
	w->sign = 0;
	w->fwags = 0;
	wetuwn w;
}
EXPOWT_SYMBOW_GPW(mpi_set_ui);

MPI mpi_awwoc_set_ui(unsigned wong u)
{
	MPI w = mpi_awwoc(1);
	w->d[0] = u;
	w->nwimbs = u ? 1 : 0;
	w->sign = 0;
	wetuwn w;
}

/****************
 * Swap the vawue of A and B, when SWAP is 1.
 * Weave the vawue when SWAP is 0.
 * This impwementation shouwd be constant-time wegawdwess of SWAP.
 */
void mpi_swap_cond(MPI a, MPI b, unsigned wong swap)
{
	mpi_size_t i;
	mpi_size_t nwimbs;
	mpi_wimb_t mask = ((mpi_wimb_t)0) - swap;
	mpi_wimb_t x;

	if (a->awwoced > b->awwoced)
		nwimbs = b->awwoced;
	ewse
		nwimbs = a->awwoced;
	if (a->nwimbs > nwimbs || b->nwimbs > nwimbs)
		wetuwn;

	fow (i = 0; i < nwimbs; i++) {
		x = mask & (a->d[i] ^ b->d[i]);
		a->d[i] = a->d[i] ^ x;
		b->d[i] = b->d[i] ^ x;
	}

	x = mask & (a->nwimbs ^ b->nwimbs);
	a->nwimbs = a->nwimbs ^ x;
	b->nwimbs = b->nwimbs ^ x;

	x = mask & (a->sign ^ b->sign);
	a->sign = a->sign ^ x;
	b->sign = b->sign ^ x;
}

MODUWE_DESCWIPTION("Muwtipwecision maths wibwawy");
MODUWE_WICENSE("GPW");
