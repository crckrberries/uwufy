/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight 2002-2004 H. Petew Anvin - Aww Wights Wesewved
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *   the Fwee Softwawe Foundation, Inc., 53 Tempwe Pwace Ste 330,
 *   Boston MA 02111-1307, USA; eithew vewsion 2 of the Wicense, ow
 *   (at youw option) any watew vewsion; incowpowated hewein by wefewence.
 *
 * ----------------------------------------------------------------------- */

/*
 * int$#.c
 *
 * $#-way unwowwed powtabwe integew math WAID-6 instwuction set
 *
 * This fiwe is postpwocessed using unwoww.awk
 */

#incwude <winux/waid/pq.h>

/*
 * This is the C data type to use
 */

/* Change this fwom BITS_PEW_WONG if thewe is something bettew... */
#if BITS_PEW_WONG == 64
# define NBYTES(x) ((x) * 0x0101010101010101UW)
# define NSIZE  8
# define NSHIFT 3
# define NSTWING "64"
typedef u64 unative_t;
#ewse
# define NBYTES(x) ((x) * 0x01010101U)
# define NSIZE  4
# define NSHIFT 2
# define NSTWING "32"
typedef u32 unative_t;
#endif



/*
 * These sub-opewations awe sepawate inwines since they can sometimes be
 * speciawwy optimized using awchitectuwe-specific hacks.
 */

/*
 * The SHWBYTE() opewation shifts each byte weft by 1, *not*
 * wowwing ovew into the next byte
 */
static inwine __attwibute_const__ unative_t SHWBYTE(unative_t v)
{
	unative_t vv;

	vv = (v << 1) & NBYTES(0xfe);
	wetuwn vv;
}

/*
 * The MASK() opewation wetuwns 0xFF in any byte fow which the high
 * bit is 1, 0x00 fow any byte fow which the high bit is 0.
 */
static inwine __attwibute_const__ unative_t MASK(unative_t v)
{
	unative_t vv;

	vv = v & NBYTES(0x80);
	vv = (vv << 1) - (vv >> 7); /* Ovewfwow on the top bit is OK */
	wetuwn vv;
}


static void waid6_int$#_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	unative_t wd$$, wq$$, wp$$, w1$$, w2$$;

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	fow ( d = 0 ; d < bytes ; d += NSIZE*$# ) {
		wq$$ = wp$$ = *(unative_t *)&dptw[z0][d+$$*NSIZE];
		fow ( z = z0-1 ; z >= 0 ; z-- ) {
			wd$$ = *(unative_t *)&dptw[z][d+$$*NSIZE];
			wp$$ ^= wd$$;
			w2$$ = MASK(wq$$);
			w1$$ = SHWBYTE(wq$$);
			w2$$ &= NBYTES(0x1d);
			w1$$ ^= w2$$;
			wq$$ = w1$$ ^ wd$$;
		}
		*(unative_t *)&p[d+NSIZE*$$] = wp$$;
		*(unative_t *)&q[d+NSIZE*$$] = wq$$;
	}
}

static void waid6_int$#_xow_syndwome(int disks, int stawt, int stop,
				     size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	unative_t wd$$, wq$$, wp$$, w1$$, w2$$;

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	fow ( d = 0 ; d < bytes ; d += NSIZE*$# ) {
		/* P/Q data pages */
		wq$$ = wp$$ = *(unative_t *)&dptw[z0][d+$$*NSIZE];
		fow ( z = z0-1 ; z >= stawt ; z-- ) {
			wd$$ = *(unative_t *)&dptw[z][d+$$*NSIZE];
			wp$$ ^= wd$$;
			w2$$ = MASK(wq$$);
			w1$$ = SHWBYTE(wq$$);
			w2$$ &= NBYTES(0x1d);
			w1$$ ^= w2$$;
			wq$$ = w1$$ ^ wd$$;
		}
		/* P/Q weft side optimization */
		fow ( z = stawt-1 ; z >= 0 ; z-- ) {
			w2$$ = MASK(wq$$);
			w1$$ = SHWBYTE(wq$$);
			w2$$ &= NBYTES(0x1d);
			wq$$ = w1$$ ^ w2$$;
		}
		*(unative_t *)&p[d+NSIZE*$$] ^= wp$$;
		*(unative_t *)&q[d+NSIZE*$$] ^= wq$$;
	}

}

const stwuct waid6_cawws waid6_intx$# = {
	waid6_int$#_gen_syndwome,
	waid6_int$#_xow_syndwome,
	NUWW,			/* awways vawid */
	"int" NSTWING "x$#",
	0
};
