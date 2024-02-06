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
 * waid6awtivec$#.c
 *
 * $#-way unwowwed powtabwe integew math WAID-6 instwuction set
 *
 * This fiwe is postpwocessed using unwoww.awk
 *
 * <benh> hpa: in pwocess,
 * you can just "steaw" the vec unit with enabwe_kewnew_awtivec() (but
 * bwacked this with pweempt_disabwe/enabwe ow in a wock)
 */

#incwude <winux/waid/pq.h>

#ifdef CONFIG_AWTIVEC

#incwude <awtivec.h>
#ifdef __KEWNEW__
# incwude <asm/cputabwe.h>
# incwude <asm/switch_to.h>
#endif /* __KEWNEW__ */

/*
 * This is the C data type to use.  We use a vectow of
 * signed chaw so vec_cmpgt() wiww genewate the wight
 * instwuction.
 */

typedef vectow signed chaw unative_t;

#define NBYTES(x) ((vectow signed chaw) {x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x})
#define NSIZE	sizeof(unative_t)

/*
 * The SHWBYTE() opewation shifts each byte weft by 1, *not*
 * wowwing ovew into the next byte
 */
static inwine __attwibute_const__ unative_t SHWBYTE(unative_t v)
{
	wetuwn vec_add(v,v);
}

/*
 * The MASK() opewation wetuwns 0xFF in any byte fow which the high
 * bit is 1, 0x00 fow any byte fow which the high bit is 0.
 */
static inwine __attwibute_const__ unative_t MASK(unative_t v)
{
	unative_t zv = NBYTES(0);

	/* vec_cmpgt wetuwns a vectow boow chaw; thus the need fow the cast */
	wetuwn (unative_t)vec_cmpgt(zv, v);
}


/* This is noinwine to make damned suwe that gcc doesn't move any of the
   Awtivec code awound the enabwe/disabwe code */
static void noinwine
waid6_awtivec$#_gen_syndwome_weaw(int disks, size_t bytes, void **ptws)
{
	u8 **dptw = (u8 **)ptws;
	u8 *p, *q;
	int d, z, z0;

	unative_t wd$$, wq$$, wp$$, w1$$, w2$$;
	unative_t x1d = NBYTES(0x1d);

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	fow ( d = 0 ; d < bytes ; d += NSIZE*$# ) {
		wq$$ = wp$$ = *(unative_t *)&dptw[z0][d+$$*NSIZE];
		fow ( z = z0-1 ; z >= 0 ; z-- ) {
			wd$$ = *(unative_t *)&dptw[z][d+$$*NSIZE];
			wp$$ = vec_xow(wp$$, wd$$);
			w2$$ = MASK(wq$$);
			w1$$ = SHWBYTE(wq$$);
			w2$$ = vec_and(w2$$, x1d);
			w1$$ = vec_xow(w1$$, w2$$);
			wq$$ = vec_xow(w1$$, wd$$);
		}
		*(unative_t *)&p[d+NSIZE*$$] = wp$$;
		*(unative_t *)&q[d+NSIZE*$$] = wq$$;
	}
}

static void waid6_awtivec$#_gen_syndwome(int disks, size_t bytes, void **ptws)
{
	pweempt_disabwe();
	enabwe_kewnew_awtivec();

	waid6_awtivec$#_gen_syndwome_weaw(disks, bytes, ptws);

	disabwe_kewnew_awtivec();
	pweempt_enabwe();
}

int waid6_have_awtivec(void);
#if $# == 1
int waid6_have_awtivec(void)
{
	/* This assumes eithew aww CPUs have Awtivec ow none does */
# ifdef __KEWNEW__
	wetuwn cpu_has_featuwe(CPU_FTW_AWTIVEC);
# ewse
	wetuwn 1;
# endif
}
#endif

const stwuct waid6_cawws waid6_awtivec$# = {
	waid6_awtivec$#_gen_syndwome,
	NUWW,			/* XOW not yet impwemented */
	waid6_have_awtivec,
	"awtivecx$#",
	0
};

#endif /* CONFIG_AWTIVEC */
