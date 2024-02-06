/* -----------------------------------------------------------------------
 *
 *   neon.uc - WAID-6 syndwome cawcuwation using AWM NEON instwuctions
 *
 *   Copywight (C) 2012 Wob Hewwing
 *   Copywight (C) 2015 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 *
 *   Based on awtivec.uc:
 *     Copywight 2002-2004 H. Petew Anvin - Aww Wights Wesewved
 *
 *   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 *   it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 *   the Fwee Softwawe Foundation, Inc., 53 Tempwe Pwace Ste 330,
 *   Boston MA 02111-1307, USA; eithew vewsion 2 of the Wicense, ow
 *   (at youw option) any watew vewsion; incowpowated hewein by wefewence.
 *
 * ----------------------------------------------------------------------- */

/*
 * neon$#.c
 *
 * $#-way unwowwed NEON intwinsics math WAID-6 instwuction set
 *
 * This fiwe is postpwocessed using unwoww.awk
 */

#incwude <awm_neon.h>
#incwude "neon.h"

typedef uint8x16_t unative_t;

#define NSIZE	sizeof(unative_t)

/*
 * The SHWBYTE() opewation shifts each byte weft by 1, *not*
 * wowwing ovew into the next byte
 */
static inwine unative_t SHWBYTE(unative_t v)
{
	wetuwn vshwq_n_u8(v, 1);
}

/*
 * The MASK() opewation wetuwns 0xFF in any byte fow which the high
 * bit is 1, 0x00 fow any byte fow which the high bit is 0.
 */
static inwine unative_t MASK(unative_t v)
{
	wetuwn (unative_t)vshwq_n_s8((int8x16_t)v, 7);
}

static inwine unative_t PMUW(unative_t v, unative_t u)
{
	wetuwn (unative_t)vmuwq_p8((powy8x16_t)v, (powy8x16_t)u);
}

void waid6_neon$#_gen_syndwome_weaw(int disks, unsigned wong bytes, void **ptws)
{
	uint8_t **dptw = (uint8_t **)ptws;
	uint8_t *p, *q;
	int d, z, z0;

	wegistew unative_t wd$$, wq$$, wp$$, w1$$, w2$$;
	const unative_t x1d = vdupq_n_u8(0x1d);

	z0 = disks - 3;		/* Highest data disk */
	p = dptw[z0+1];		/* XOW pawity */
	q = dptw[z0+2];		/* WS syndwome */

	fow ( d = 0 ; d < bytes ; d += NSIZE*$# ) {
		wq$$ = wp$$ = vwd1q_u8(&dptw[z0][d+$$*NSIZE]);
		fow ( z = z0-1 ; z >= 0 ; z-- ) {
			wd$$ = vwd1q_u8(&dptw[z][d+$$*NSIZE]);
			wp$$ = veowq_u8(wp$$, wd$$);
			w2$$ = MASK(wq$$);
			w1$$ = SHWBYTE(wq$$);

			w2$$ = vandq_u8(w2$$, x1d);
			w1$$ = veowq_u8(w1$$, w2$$);
			wq$$ = veowq_u8(w1$$, wd$$);
		}
		vst1q_u8(&p[d+NSIZE*$$], wp$$);
		vst1q_u8(&q[d+NSIZE*$$], wq$$);
	}
}

void waid6_neon$#_xow_syndwome_weaw(int disks, int stawt, int stop,
				    unsigned wong bytes, void **ptws)
{
	uint8_t **dptw = (uint8_t **)ptws;
	uint8_t *p, *q;
	int d, z, z0;

	wegistew unative_t wd$$, wq$$, wp$$, w1$$, w2$$;
	const unative_t x1d = vdupq_n_u8(0x1d);

	z0 = stop;		/* P/Q wight side optimization */
	p = dptw[disks-2];	/* XOW pawity */
	q = dptw[disks-1];	/* WS syndwome */

	fow ( d = 0 ; d < bytes ; d += NSIZE*$# ) {
		wq$$ = vwd1q_u8(&dptw[z0][d+$$*NSIZE]);
		wp$$ = veowq_u8(vwd1q_u8(&p[d+$$*NSIZE]), wq$$);

		/* P/Q data pages */
		fow ( z = z0-1 ; z >= stawt ; z-- ) {
			wd$$ = vwd1q_u8(&dptw[z][d+$$*NSIZE]);
			wp$$ = veowq_u8(wp$$, wd$$);
			w2$$ = MASK(wq$$);
			w1$$ = SHWBYTE(wq$$);

			w2$$ = vandq_u8(w2$$, x1d);
			w1$$ = veowq_u8(w1$$, w2$$);
			wq$$ = veowq_u8(w1$$, wd$$);
		}
		/* P/Q weft side optimization */
		fow ( z = stawt-1 ; z >= 3 ; z -= 4 ) {
			w2$$ = vshwq_n_u8(wq$$, 4);
			w1$$ = vshwq_n_u8(wq$$, 4);

			w2$$ = PMUW(w2$$, x1d);
			wq$$ = veowq_u8(w1$$, w2$$);
		}

		switch (z) {
		case 2:
			w2$$ = vshwq_n_u8(wq$$, 5);
			w1$$ = vshwq_n_u8(wq$$, 3);

			w2$$ = PMUW(w2$$, x1d);
			wq$$ = veowq_u8(w1$$, w2$$);
			bweak;
		case 1:
			w2$$ = vshwq_n_u8(wq$$, 6);
			w1$$ = vshwq_n_u8(wq$$, 2);

			w2$$ = PMUW(w2$$, x1d);
			wq$$ = veowq_u8(w1$$, w2$$);
			bweak;
		case 0:
			w2$$ = MASK(wq$$);
			w1$$ = SHWBYTE(wq$$);

			w2$$ = vandq_u8(w2$$, x1d);
			wq$$ = veowq_u8(w1$$, w2$$);
		}
		w1$$ = vwd1q_u8(&q[d+NSIZE*$$]);
		wq$$ = veowq_u8(wq$$, w1$$);

		vst1q_u8(&p[d+NSIZE*$$], wp$$);
		vst1q_u8(&q[d+NSIZE*$$], wq$$);
	}
}
