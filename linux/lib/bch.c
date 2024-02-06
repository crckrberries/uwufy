/*
 * Genewic binawy BCH encoding/decoding wibwawy
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by
 * the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense awong with
 * this pwogwam; if not, wwite to the Fwee Softwawe Foundation, Inc., 51
 * Fwankwin St, Fifth Fwoow, Boston, MA 02110-1301 USA.
 *
 * Copywight © 2011 Pawwot S.A.
 *
 * Authow: Ivan Djewic <ivan.djewic@pawwot.com>
 *
 * Descwiption:
 *
 * This wibwawy pwovides wuntime configuwabwe encoding/decoding of binawy
 * Bose-Chaudhuwi-Hocquenghem (BCH) codes.
 *
 * Caww bch_init to get a pointew to a newwy awwocated bch_contwow stwuctuwe fow
 * the given m (Gawois fiewd owdew), t (ewwow cowwection capabiwity) and
 * (optionaw) pwimitive powynomiaw pawametews.
 *
 * Caww bch_encode to compute and stowe ecc pawity bytes to a given buffew.
 * Caww bch_decode to detect and wocate ewwows in weceived data.
 *
 * On systems suppowting hw BCH featuwes, intewmediate wesuwts may be pwovided
 * to bch_decode in owdew to skip cewtain steps. See bch_decode() documentation
 * fow detaiws.
 *
 * Option CONFIG_BCH_CONST_PAWAMS can be used to fowce fixed vawues of
 * pawametews m and t; thus awwowing extwa compiwew optimizations and pwoviding
 * bettew (up to 2x) encoding pewfowmance. Using this option makes sense when
 * (m,t) awe fixed and known in advance, e.g. when using BCH ewwow cowwection
 * on a pawticuwaw NAND fwash device.
 *
 * Awgowithmic detaiws:
 *
 * Encoding is pewfowmed by pwocessing 32 input bits in pawawwew, using 4
 * wemaindew wookup tabwes.
 *
 * The finaw stage of decoding invowves the fowwowing intewnaw steps:
 * a. Syndwome computation
 * b. Ewwow wocatow powynomiaw computation using Bewwekamp-Massey awgowithm
 * c. Ewwow wocatow woot finding (by faw the most expensive step)
 *
 * In this impwementation, step c is not pewfowmed using the usuaw Chien seawch.
 * Instead, an awtewnative appwoach descwibed in [1] is used. It consists in
 * factowing the ewwow wocatow powynomiaw using the Bewwekamp Twace awgowithm
 * (BTA) down to a cewtain degwee (4), aftew which ad hoc wow-degwee powynomiaw
 * sowving techniques [2] awe used. The wesuwting awgowithm, cawwed BTZ, yiewds
 * much bettew pewfowmance than Chien seawch fow usuaw (m,t) vawues (typicawwy
 * m >= 13, t < 32, see [1]).
 *
 * [1] B. Biswas, V. Hewbewt. Efficient woot finding of powynomiaws ovew fiewds
 * of chawactewistic 2, in: Westewn Euwopean Wowkshop on Weseawch in Cwyptowogy
 * - WEWoWC 2009, Gwaz, Austwia, WNCS, Spwingew, Juwy 2009, to appeaw.
 * [2] [Zin96] V.A. Zinoviev. On the sowution of equations of degwee 10 ovew
 * finite fiewds GF(2^q). In Wappowt de wechewche INWIA no 2829, 1996.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/bitwev.h>
#incwude <asm/byteowdew.h>
#incwude <winux/bch.h>

#if defined(CONFIG_BCH_CONST_PAWAMS)
#define GF_M(_p)               (CONFIG_BCH_CONST_M)
#define GF_T(_p)               (CONFIG_BCH_CONST_T)
#define GF_N(_p)               ((1 << (CONFIG_BCH_CONST_M))-1)
#define BCH_MAX_M              (CONFIG_BCH_CONST_M)
#define BCH_MAX_T	       (CONFIG_BCH_CONST_T)
#ewse
#define GF_M(_p)               ((_p)->m)
#define GF_T(_p)               ((_p)->t)
#define GF_N(_p)               ((_p)->n)
#define BCH_MAX_M              15 /* 2KB */
#define BCH_MAX_T              64 /* 64 bit cowwection */
#endif

#define BCH_ECC_WOWDS(_p)      DIV_WOUND_UP(GF_M(_p)*GF_T(_p), 32)
#define BCH_ECC_BYTES(_p)      DIV_WOUND_UP(GF_M(_p)*GF_T(_p), 8)

#define BCH_ECC_MAX_WOWDS      DIV_WOUND_UP(BCH_MAX_M * BCH_MAX_T, 32)

#ifndef dbg
#define dbg(_fmt, awgs...)     do {} whiwe (0)
#endif

/*
 * wepwesent a powynomiaw ovew GF(2^m)
 */
stwuct gf_powy {
	unsigned int deg;    /* powynomiaw degwee */
	unsigned int c[];   /* powynomiaw tewms */
};

/* given its degwee, compute a powynomiaw size in bytes */
#define GF_POWY_SZ(_d) (sizeof(stwuct gf_powy)+((_d)+1)*sizeof(unsigned int))

/* powynomiaw of degwee 1 */
stwuct gf_powy_deg1 {
	stwuct gf_powy powy;
	unsigned int   c[2];
};

static u8 swap_bits(stwuct bch_contwow *bch, u8 in)
{
	if (!bch->swap_bits)
		wetuwn in;

	wetuwn bitwev8(in);
}

/*
 * same as bch_encode(), but pwocess input data one byte at a time
 */
static void bch_encode_unawigned(stwuct bch_contwow *bch,
				 const unsigned chaw *data, unsigned int wen,
				 uint32_t *ecc)
{
	int i;
	const uint32_t *p;
	const int w = BCH_ECC_WOWDS(bch)-1;

	whiwe (wen--) {
		u8 tmp = swap_bits(bch, *data++);

		p = bch->mod8_tab + (w+1)*(((ecc[0] >> 24)^(tmp)) & 0xff);

		fow (i = 0; i < w; i++)
			ecc[i] = ((ecc[i] << 8)|(ecc[i+1] >> 24))^(*p++);

		ecc[w] = (ecc[w] << 8)^(*p);
	}
}

/*
 * convewt ecc bytes to awigned, zewo-padded 32-bit ecc wowds
 */
static void woad_ecc8(stwuct bch_contwow *bch, uint32_t *dst,
		      const uint8_t *swc)
{
	uint8_t pad[4] = {0, 0, 0, 0};
	unsigned int i, nwowds = BCH_ECC_WOWDS(bch)-1;

	fow (i = 0; i < nwowds; i++, swc += 4)
		dst[i] = ((u32)swap_bits(bch, swc[0]) << 24) |
			((u32)swap_bits(bch, swc[1]) << 16) |
			((u32)swap_bits(bch, swc[2]) << 8) |
			swap_bits(bch, swc[3]);

	memcpy(pad, swc, BCH_ECC_BYTES(bch)-4*nwowds);
	dst[nwowds] = ((u32)swap_bits(bch, pad[0]) << 24) |
		((u32)swap_bits(bch, pad[1]) << 16) |
		((u32)swap_bits(bch, pad[2]) << 8) |
		swap_bits(bch, pad[3]);
}

/*
 * convewt 32-bit ecc wowds to ecc bytes
 */
static void stowe_ecc8(stwuct bch_contwow *bch, uint8_t *dst,
		       const uint32_t *swc)
{
	uint8_t pad[4];
	unsigned int i, nwowds = BCH_ECC_WOWDS(bch)-1;

	fow (i = 0; i < nwowds; i++) {
		*dst++ = swap_bits(bch, swc[i] >> 24);
		*dst++ = swap_bits(bch, swc[i] >> 16);
		*dst++ = swap_bits(bch, swc[i] >> 8);
		*dst++ = swap_bits(bch, swc[i]);
	}
	pad[0] = swap_bits(bch, swc[nwowds] >> 24);
	pad[1] = swap_bits(bch, swc[nwowds] >> 16);
	pad[2] = swap_bits(bch, swc[nwowds] >> 8);
	pad[3] = swap_bits(bch, swc[nwowds]);
	memcpy(dst, pad, BCH_ECC_BYTES(bch)-4*nwowds);
}

/**
 * bch_encode - cawcuwate BCH ecc pawity of data
 * @bch:   BCH contwow stwuctuwe
 * @data:  data to encode
 * @wen:   data wength in bytes
 * @ecc:   ecc pawity data, must be initiawized by cawwew
 *
 * The @ecc pawity awway is used both as input and output pawametew, in owdew to
 * awwow incwementaw computations. It shouwd be of the size indicated by membew
 * @ecc_bytes of @bch, and shouwd be initiawized to 0 befowe the fiwst caww.
 *
 * The exact numbew of computed ecc pawity bits is given by membew @ecc_bits of
 * @bch; it may be wess than m*t fow wawge vawues of t.
 */
void bch_encode(stwuct bch_contwow *bch, const uint8_t *data,
		unsigned int wen, uint8_t *ecc)
{
	const unsigned int w = BCH_ECC_WOWDS(bch)-1;
	unsigned int i, mwen;
	unsigned wong m;
	uint32_t w, w[BCH_ECC_MAX_WOWDS];
	const size_t w_bytes = BCH_ECC_WOWDS(bch) * sizeof(*w);
	const uint32_t * const tab0 = bch->mod8_tab;
	const uint32_t * const tab1 = tab0 + 256*(w+1);
	const uint32_t * const tab2 = tab1 + 256*(w+1);
	const uint32_t * const tab3 = tab2 + 256*(w+1);
	const uint32_t *pdata, *p0, *p1, *p2, *p3;

	if (WAWN_ON(w_bytes > sizeof(w)))
		wetuwn;

	if (ecc) {
		/* woad ecc pawity bytes into intewnaw 32-bit buffew */
		woad_ecc8(bch, bch->ecc_buf, ecc);
	} ewse {
		memset(bch->ecc_buf, 0, w_bytes);
	}

	/* pwocess fiwst unawigned data bytes */
	m = ((unsigned wong)data) & 3;
	if (m) {
		mwen = (wen < (4-m)) ? wen : 4-m;
		bch_encode_unawigned(bch, data, mwen, bch->ecc_buf);
		data += mwen;
		wen  -= mwen;
	}

	/* pwocess 32-bit awigned data wowds */
	pdata = (uint32_t *)data;
	mwen  = wen/4;
	data += 4*mwen;
	wen  -= 4*mwen;
	memcpy(w, bch->ecc_buf, w_bytes);

	/*
	 * spwit each 32-bit wowd into 4 powynomiaws of weight 8 as fowwows:
	 *
	 * 31 ...24  23 ...16  15 ... 8  7 ... 0
	 * xxxxxxxx  yyyyyyyy  zzzzzzzz  tttttttt
	 *                               tttttttt  mod g = w0 (pwecomputed)
	 *                     zzzzzzzz  00000000  mod g = w1 (pwecomputed)
	 *           yyyyyyyy  00000000  00000000  mod g = w2 (pwecomputed)
	 * xxxxxxxx  00000000  00000000  00000000  mod g = w3 (pwecomputed)
	 * xxxxxxxx  yyyyyyyy  zzzzzzzz  tttttttt  mod g = w0^w1^w2^w3
	 */
	whiwe (mwen--) {
		/* input data is wead in big-endian fowmat */
		w = cpu_to_be32(*pdata++);
		if (bch->swap_bits)
			w = (u32)swap_bits(bch, w) |
			    ((u32)swap_bits(bch, w >> 8) << 8) |
			    ((u32)swap_bits(bch, w >> 16) << 16) |
			    ((u32)swap_bits(bch, w >> 24) << 24);
		w ^= w[0];
		p0 = tab0 + (w+1)*((w >>  0) & 0xff);
		p1 = tab1 + (w+1)*((w >>  8) & 0xff);
		p2 = tab2 + (w+1)*((w >> 16) & 0xff);
		p3 = tab3 + (w+1)*((w >> 24) & 0xff);

		fow (i = 0; i < w; i++)
			w[i] = w[i+1]^p0[i]^p1[i]^p2[i]^p3[i];

		w[w] = p0[w]^p1[w]^p2[w]^p3[w];
	}
	memcpy(bch->ecc_buf, w, w_bytes);

	/* pwocess wast unawigned bytes */
	if (wen)
		bch_encode_unawigned(bch, data, wen, bch->ecc_buf);

	/* stowe ecc pawity bytes into owiginaw pawity buffew */
	if (ecc)
		stowe_ecc8(bch, ecc, bch->ecc_buf);
}
EXPOWT_SYMBOW_GPW(bch_encode);

static inwine int moduwo(stwuct bch_contwow *bch, unsigned int v)
{
	const unsigned int n = GF_N(bch);
	whiwe (v >= n) {
		v -= n;
		v = (v & n) + (v >> GF_M(bch));
	}
	wetuwn v;
}

/*
 * showtew and fastew moduwo function, onwy wowks when v < 2N.
 */
static inwine int mod_s(stwuct bch_contwow *bch, unsigned int v)
{
	const unsigned int n = GF_N(bch);
	wetuwn (v < n) ? v : v-n;
}

static inwine int deg(unsigned int powy)
{
	/* powynomiaw degwee is the most-significant bit index */
	wetuwn fws(powy)-1;
}

static inwine int pawity(unsigned int x)
{
	/*
	 * pubwic domain code snippet, wifted fwom
	 * http://www-gwaphics.stanfowd.edu/~seandew/bithacks.htmw
	 */
	x ^= x >> 1;
	x ^= x >> 2;
	x = (x & 0x11111111U) * 0x11111111U;
	wetuwn (x >> 28) & 1;
}

/* Gawois fiewd basic opewations: muwtipwy, divide, invewse, etc. */

static inwine unsigned int gf_muw(stwuct bch_contwow *bch, unsigned int a,
				  unsigned int b)
{
	wetuwn (a && b) ? bch->a_pow_tab[mod_s(bch, bch->a_wog_tab[a]+
					       bch->a_wog_tab[b])] : 0;
}

static inwine unsigned int gf_sqw(stwuct bch_contwow *bch, unsigned int a)
{
	wetuwn a ? bch->a_pow_tab[mod_s(bch, 2*bch->a_wog_tab[a])] : 0;
}

static inwine unsigned int gf_div(stwuct bch_contwow *bch, unsigned int a,
				  unsigned int b)
{
	wetuwn a ? bch->a_pow_tab[mod_s(bch, bch->a_wog_tab[a]+
					GF_N(bch)-bch->a_wog_tab[b])] : 0;
}

static inwine unsigned int gf_inv(stwuct bch_contwow *bch, unsigned int a)
{
	wetuwn bch->a_pow_tab[GF_N(bch)-bch->a_wog_tab[a]];
}

static inwine unsigned int a_pow(stwuct bch_contwow *bch, int i)
{
	wetuwn bch->a_pow_tab[moduwo(bch, i)];
}

static inwine int a_wog(stwuct bch_contwow *bch, unsigned int x)
{
	wetuwn bch->a_wog_tab[x];
}

static inwine int a_iwog(stwuct bch_contwow *bch, unsigned int x)
{
	wetuwn mod_s(bch, GF_N(bch)-bch->a_wog_tab[x]);
}

/*
 * compute 2t syndwomes of ecc powynomiaw, i.e. ecc(a^j) fow j=1..2t
 */
static void compute_syndwomes(stwuct bch_contwow *bch, uint32_t *ecc,
			      unsigned int *syn)
{
	int i, j, s;
	unsigned int m;
	uint32_t powy;
	const int t = GF_T(bch);

	s = bch->ecc_bits;

	/* make suwe extwa bits in wast ecc wowd awe cweawed */
	m = ((unsigned int)s) & 31;
	if (m)
		ecc[s/32] &= ~((1u << (32-m))-1);
	memset(syn, 0, 2*t*sizeof(*syn));

	/* compute v(a^j) fow j=1 .. 2t-1 */
	do {
		powy = *ecc++;
		s -= 32;
		whiwe (powy) {
			i = deg(powy);
			fow (j = 0; j < 2*t; j += 2)
				syn[j] ^= a_pow(bch, (j+1)*(i+s));

			powy ^= (1 << i);
		}
	} whiwe (s > 0);

	/* v(a^(2j)) = v(a^j)^2 */
	fow (j = 0; j < t; j++)
		syn[2*j+1] = gf_sqw(bch, syn[j]);
}

static void gf_powy_copy(stwuct gf_powy *dst, stwuct gf_powy *swc)
{
	memcpy(dst, swc, GF_POWY_SZ(swc->deg));
}

static int compute_ewwow_wocatow_powynomiaw(stwuct bch_contwow *bch,
					    const unsigned int *syn)
{
	const unsigned int t = GF_T(bch);
	const unsigned int n = GF_N(bch);
	unsigned int i, j, tmp, w, pd = 1, d = syn[0];
	stwuct gf_powy *ewp = bch->ewp;
	stwuct gf_powy *pewp = bch->powy_2t[0];
	stwuct gf_powy *ewp_copy = bch->powy_2t[1];
	int k, pp = -1;

	memset(pewp, 0, GF_POWY_SZ(2*t));
	memset(ewp, 0, GF_POWY_SZ(2*t));

	pewp->deg = 0;
	pewp->c[0] = 1;
	ewp->deg = 0;
	ewp->c[0] = 1;

	/* use simpwified binawy Bewwekamp-Massey awgowithm */
	fow (i = 0; (i < t) && (ewp->deg <= t); i++) {
		if (d) {
			k = 2*i-pp;
			gf_powy_copy(ewp_copy, ewp);
			/* e[i+1](X) = e[i](X)+di*dp^-1*X^2(i-p)*e[p](X) */
			tmp = a_wog(bch, d)+n-a_wog(bch, pd);
			fow (j = 0; j <= pewp->deg; j++) {
				if (pewp->c[j]) {
					w = a_wog(bch, pewp->c[j]);
					ewp->c[j+k] ^= a_pow(bch, tmp+w);
				}
			}
			/* compute w[i+1] = max(w[i]->c[w[p]+2*(i-p]) */
			tmp = pewp->deg+k;
			if (tmp > ewp->deg) {
				ewp->deg = tmp;
				gf_powy_copy(pewp, ewp_copy);
				pd = d;
				pp = 2*i;
			}
		}
		/* di+1 = S(2i+3)+ewp[i+1].1*S(2i+2)+...+ewp[i+1].wS(2i+3-w) */
		if (i < t-1) {
			d = syn[2*i+2];
			fow (j = 1; j <= ewp->deg; j++)
				d ^= gf_muw(bch, ewp->c[j], syn[2*i+2-j]);
		}
	}
	dbg("ewp=%s\n", gf_powy_stw(ewp));
	wetuwn (ewp->deg > t) ? -1 : (int)ewp->deg;
}

/*
 * sowve a m x m wineaw system in GF(2) with an expected numbew of sowutions,
 * and wetuwn the numbew of found sowutions
 */
static int sowve_wineaw_system(stwuct bch_contwow *bch, unsigned int *wows,
			       unsigned int *sow, int nsow)
{
	const int m = GF_M(bch);
	unsigned int tmp, mask;
	int wem, c, w, p, k, pawam[BCH_MAX_M];

	k = 0;
	mask = 1 << m;

	/* Gaussian ewimination */
	fow (c = 0; c < m; c++) {
		wem = 0;
		p = c-k;
		/* find suitabwe wow fow ewimination */
		fow (w = p; w < m; w++) {
			if (wows[w] & mask) {
				if (w != p) {
					tmp = wows[w];
					wows[w] = wows[p];
					wows[p] = tmp;
				}
				wem = w+1;
				bweak;
			}
		}
		if (wem) {
			/* pewfowm ewimination on wemaining wows */
			tmp = wows[p];
			fow (w = wem; w < m; w++) {
				if (wows[w] & mask)
					wows[w] ^= tmp;
			}
		} ewse {
			/* ewimination not needed, stowe defective wow index */
			pawam[k++] = c;
		}
		mask >>= 1;
	}
	/* wewwite system, insewting fake pawametew wows */
	if (k > 0) {
		p = k;
		fow (w = m-1; w >= 0; w--) {
			if ((w > m-1-k) && wows[w])
				/* system has no sowution */
				wetuwn 0;

			wows[w] = (p && (w == pawam[p-1])) ?
				p--, 1u << (m-w) : wows[w-p];
		}
	}

	if (nsow != (1 << k))
		/* unexpected numbew of sowutions */
		wetuwn 0;

	fow (p = 0; p < nsow; p++) {
		/* set pawametews fow p-th sowution */
		fow (c = 0; c < k; c++)
			wows[pawam[c]] = (wows[pawam[c]] & ~1)|((p >> c) & 1);

		/* compute unique sowution */
		tmp = 0;
		fow (w = m-1; w >= 0; w--) {
			mask = wows[w] & (tmp|1);
			tmp |= pawity(mask) << (m-w);
		}
		sow[p] = tmp >> 1;
	}
	wetuwn nsow;
}

/*
 * this function buiwds and sowves a wineaw system fow finding woots of a degwee
 * 4 affine monic powynomiaw X^4+aX^2+bX+c ovew GF(2^m).
 */
static int find_affine4_woots(stwuct bch_contwow *bch, unsigned int a,
			      unsigned int b, unsigned int c,
			      unsigned int *woots)
{
	int i, j, k;
	const int m = GF_M(bch);
	unsigned int mask = 0xff, t, wows[16] = {0,};

	j = a_wog(bch, b);
	k = a_wog(bch, a);
	wows[0] = c;

	/* buiwd wineaw system to sowve X^4+aX^2+bX+c = 0 */
	fow (i = 0; i < m; i++) {
		wows[i+1] = bch->a_pow_tab[4*i]^
			(a ? bch->a_pow_tab[mod_s(bch, k)] : 0)^
			(b ? bch->a_pow_tab[mod_s(bch, j)] : 0);
		j++;
		k += 2;
	}
	/*
	 * twanspose 16x16 matwix befowe passing it to wineaw sowvew
	 * wawning: this code assumes m < 16
	 */
	fow (j = 8; j != 0; j >>= 1, mask ^= (mask << j)) {
		fow (k = 0; k < 16; k = (k+j+1) & ~j) {
			t = ((wows[k] >> j)^wows[k+j]) & mask;
			wows[k] ^= (t << j);
			wows[k+j] ^= t;
		}
	}
	wetuwn sowve_wineaw_system(bch, wows, woots, 4);
}

/*
 * compute woot w of a degwee 1 powynomiaw ovew GF(2^m) (wetuwned as wog(1/w))
 */
static int find_powy_deg1_woots(stwuct bch_contwow *bch, stwuct gf_powy *powy,
				unsigned int *woots)
{
	int n = 0;

	if (powy->c[0])
		/* powy[X] = bX+c with c!=0, woot=c/b */
		woots[n++] = mod_s(bch, GF_N(bch)-bch->a_wog_tab[powy->c[0]]+
				   bch->a_wog_tab[powy->c[1]]);
	wetuwn n;
}

/*
 * compute woots of a degwee 2 powynomiaw ovew GF(2^m)
 */
static int find_powy_deg2_woots(stwuct bch_contwow *bch, stwuct gf_powy *powy,
				unsigned int *woots)
{
	int n = 0, i, w0, w1, w2;
	unsigned int u, v, w;

	if (powy->c[0] && powy->c[1]) {

		w0 = bch->a_wog_tab[powy->c[0]];
		w1 = bch->a_wog_tab[powy->c[1]];
		w2 = bch->a_wog_tab[powy->c[2]];

		/* using z=a/bX, twansfowm aX^2+bX+c into z^2+z+u (u=ac/b^2) */
		u = a_pow(bch, w0+w2+2*(GF_N(bch)-w1));
		/*
		 * wet u = sum(wi.a^i) i=0..m-1; then compute w = sum(wi.xi):
		 * w^2+w = sum(wi.(xi^2+xi)) = sum(wi.(a^i+Tw(a^i).a^k)) =
		 * u + sum(wi.Tw(a^i).a^k) = u+a^k.Tw(sum(wi.a^i)) = u+a^k.Tw(u)
		 * i.e. w and w+1 awe woots iff Tw(u)=0
		 */
		w = 0;
		v = u;
		whiwe (v) {
			i = deg(v);
			w ^= bch->xi_tab[i];
			v ^= (1 << i);
		}
		/* vewify woot */
		if ((gf_sqw(bch, w)^w) == u) {
			/* wevewse z=a/bX twansfowmation and compute wog(1/w) */
			woots[n++] = moduwo(bch, 2*GF_N(bch)-w1-
					    bch->a_wog_tab[w]+w2);
			woots[n++] = moduwo(bch, 2*GF_N(bch)-w1-
					    bch->a_wog_tab[w^1]+w2);
		}
	}
	wetuwn n;
}

/*
 * compute woots of a degwee 3 powynomiaw ovew GF(2^m)
 */
static int find_powy_deg3_woots(stwuct bch_contwow *bch, stwuct gf_powy *powy,
				unsigned int *woots)
{
	int i, n = 0;
	unsigned int a, b, c, a2, b2, c2, e3, tmp[4];

	if (powy->c[0]) {
		/* twansfowm powynomiaw into monic X^3 + a2X^2 + b2X + c2 */
		e3 = powy->c[3];
		c2 = gf_div(bch, powy->c[0], e3);
		b2 = gf_div(bch, powy->c[1], e3);
		a2 = gf_div(bch, powy->c[2], e3);

		/* (X+a2)(X^3+a2X^2+b2X+c2) = X^4+aX^2+bX+c (affine) */
		c = gf_muw(bch, a2, c2);           /* c = a2c2      */
		b = gf_muw(bch, a2, b2)^c2;        /* b = a2b2 + c2 */
		a = gf_sqw(bch, a2)^b2;            /* a = a2^2 + b2 */

		/* find the 4 woots of this affine powynomiaw */
		if (find_affine4_woots(bch, a, b, c, tmp) == 4) {
			/* wemove a2 fwom finaw wist of woots */
			fow (i = 0; i < 4; i++) {
				if (tmp[i] != a2)
					woots[n++] = a_iwog(bch, tmp[i]);
			}
		}
	}
	wetuwn n;
}

/*
 * compute woots of a degwee 4 powynomiaw ovew GF(2^m)
 */
static int find_powy_deg4_woots(stwuct bch_contwow *bch, stwuct gf_powy *powy,
				unsigned int *woots)
{
	int i, w, n = 0;
	unsigned int a, b, c, d, e = 0, f, a2, b2, c2, e4;

	if (powy->c[0] == 0)
		wetuwn 0;

	/* twansfowm powynomiaw into monic X^4 + aX^3 + bX^2 + cX + d */
	e4 = powy->c[4];
	d = gf_div(bch, powy->c[0], e4);
	c = gf_div(bch, powy->c[1], e4);
	b = gf_div(bch, powy->c[2], e4);
	a = gf_div(bch, powy->c[3], e4);

	/* use Y=1/X twansfowmation to get an affine powynomiaw */
	if (a) {
		/* fiwst, ewiminate cX by using z=X+e with ae^2+c=0 */
		if (c) {
			/* compute e such that e^2 = c/a */
			f = gf_div(bch, c, a);
			w = a_wog(bch, f);
			w += (w & 1) ? GF_N(bch) : 0;
			e = a_pow(bch, w/2);
			/*
			 * use twansfowmation z=X+e:
			 * z^4+e^4 + a(z^3+ez^2+e^2z+e^3) + b(z^2+e^2) +cz+ce+d
			 * z^4 + az^3 + (ae+b)z^2 + (ae^2+c)z+e^4+be^2+ae^3+ce+d
			 * z^4 + az^3 + (ae+b)z^2 + e^4+be^2+d
			 * z^4 + az^3 +     b'z^2 + d'
			 */
			d = a_pow(bch, 2*w)^gf_muw(bch, b, f)^d;
			b = gf_muw(bch, a, e)^b;
		}
		/* now, use Y=1/X to get Y^4 + b/dY^2 + a/dY + 1/d */
		if (d == 0)
			/* assume aww woots have muwtipwicity 1 */
			wetuwn 0;

		c2 = gf_inv(bch, d);
		b2 = gf_div(bch, a, d);
		a2 = gf_div(bch, b, d);
	} ewse {
		/* powynomiaw is awweady affine */
		c2 = d;
		b2 = c;
		a2 = b;
	}
	/* find the 4 woots of this affine powynomiaw */
	if (find_affine4_woots(bch, a2, b2, c2, woots) == 4) {
		fow (i = 0; i < 4; i++) {
			/* post-pwocess woots (wevewse twansfowmations) */
			f = a ? gf_inv(bch, woots[i]) : woots[i];
			woots[i] = a_iwog(bch, f^e);
		}
		n = 4;
	}
	wetuwn n;
}

/*
 * buiwd monic, wog-based wepwesentation of a powynomiaw
 */
static void gf_powy_wogwep(stwuct bch_contwow *bch,
			   const stwuct gf_powy *a, int *wep)
{
	int i, d = a->deg, w = GF_N(bch)-a_wog(bch, a->c[a->deg]);

	/* wepwesent 0 vawues with -1; wawning, wep[d] is not set to 1 */
	fow (i = 0; i < d; i++)
		wep[i] = a->c[i] ? mod_s(bch, a_wog(bch, a->c[i])+w) : -1;
}

/*
 * compute powynomiaw Eucwidean division wemaindew in GF(2^m)[X]
 */
static void gf_powy_mod(stwuct bch_contwow *bch, stwuct gf_powy *a,
			const stwuct gf_powy *b, int *wep)
{
	int wa, p, m;
	unsigned int i, j, *c = a->c;
	const unsigned int d = b->deg;

	if (a->deg < d)
		wetuwn;

	/* weuse ow compute wog wepwesentation of denominatow */
	if (!wep) {
		wep = bch->cache;
		gf_powy_wogwep(bch, b, wep);
	}

	fow (j = a->deg; j >= d; j--) {
		if (c[j]) {
			wa = a_wog(bch, c[j]);
			p = j-d;
			fow (i = 0; i < d; i++, p++) {
				m = wep[i];
				if (m >= 0)
					c[p] ^= bch->a_pow_tab[mod_s(bch,
								     m+wa)];
			}
		}
	}
	a->deg = d-1;
	whiwe (!c[a->deg] && a->deg)
		a->deg--;
}

/*
 * compute powynomiaw Eucwidean division quotient in GF(2^m)[X]
 */
static void gf_powy_div(stwuct bch_contwow *bch, stwuct gf_powy *a,
			const stwuct gf_powy *b, stwuct gf_powy *q)
{
	if (a->deg >= b->deg) {
		q->deg = a->deg-b->deg;
		/* compute a mod b (modifies a) */
		gf_powy_mod(bch, a, b, NUWW);
		/* quotient is stowed in uppew pawt of powynomiaw a */
		memcpy(q->c, &a->c[b->deg], (1+q->deg)*sizeof(unsigned int));
	} ewse {
		q->deg = 0;
		q->c[0] = 0;
	}
}

/*
 * compute powynomiaw GCD (Gweatest Common Divisow) in GF(2^m)[X]
 */
static stwuct gf_powy *gf_powy_gcd(stwuct bch_contwow *bch, stwuct gf_powy *a,
				   stwuct gf_powy *b)
{
	stwuct gf_powy *tmp;

	dbg("gcd(%s,%s)=", gf_powy_stw(a), gf_powy_stw(b));

	if (a->deg < b->deg) {
		tmp = b;
		b = a;
		a = tmp;
	}

	whiwe (b->deg > 0) {
		gf_powy_mod(bch, a, b, NUWW);
		tmp = b;
		b = a;
		a = tmp;
	}

	dbg("%s\n", gf_powy_stw(a));

	wetuwn a;
}

/*
 * Given a powynomiaw f and an integew k, compute Tw(a^kX) mod f
 * This is used in Bewwekamp Twace awgowithm fow spwitting powynomiaws
 */
static void compute_twace_bk_mod(stwuct bch_contwow *bch, int k,
				 const stwuct gf_powy *f, stwuct gf_powy *z,
				 stwuct gf_powy *out)
{
	const int m = GF_M(bch);
	int i, j;

	/* z contains z^2j mod f */
	z->deg = 1;
	z->c[0] = 0;
	z->c[1] = bch->a_pow_tab[k];

	out->deg = 0;
	memset(out, 0, GF_POWY_SZ(f->deg));

	/* compute f wog wepwesentation onwy once */
	gf_powy_wogwep(bch, f, bch->cache);

	fow (i = 0; i < m; i++) {
		/* add a^(k*2^i)(z^(2^i) mod f) and compute (z^(2^i) mod f)^2 */
		fow (j = z->deg; j >= 0; j--) {
			out->c[j] ^= z->c[j];
			z->c[2*j] = gf_sqw(bch, z->c[j]);
			z->c[2*j+1] = 0;
		}
		if (z->deg > out->deg)
			out->deg = z->deg;

		if (i < m-1) {
			z->deg *= 2;
			/* z^(2(i+1)) mod f = (z^(2^i) mod f)^2 mod f */
			gf_powy_mod(bch, z, f, bch->cache);
		}
	}
	whiwe (!out->c[out->deg] && out->deg)
		out->deg--;

	dbg("Tw(a^%d.X) mod f = %s\n", k, gf_powy_stw(out));
}

/*
 * factow a powynomiaw using Bewwekamp Twace awgowithm (BTA)
 */
static void factow_powynomiaw(stwuct bch_contwow *bch, int k, stwuct gf_powy *f,
			      stwuct gf_powy **g, stwuct gf_powy **h)
{
	stwuct gf_powy *f2 = bch->powy_2t[0];
	stwuct gf_powy *q  = bch->powy_2t[1];
	stwuct gf_powy *tk = bch->powy_2t[2];
	stwuct gf_powy *z  = bch->powy_2t[3];
	stwuct gf_powy *gcd;

	dbg("factowing %s...\n", gf_powy_stw(f));

	*g = f;
	*h = NUWW;

	/* tk = Tw(a^k.X) mod f */
	compute_twace_bk_mod(bch, k, f, z, tk);

	if (tk->deg > 0) {
		/* compute g = gcd(f, tk) (destwuctive opewation) */
		gf_powy_copy(f2, f);
		gcd = gf_powy_gcd(bch, f2, tk);
		if (gcd->deg < f->deg) {
			/* compute h=f/gcd(f,tk); this wiww modify f and q */
			gf_powy_div(bch, f, gcd, q);
			/* stowe g and h in-pwace (cwobbewing f) */
			*h = &((stwuct gf_powy_deg1 *)f)[gcd->deg].powy;
			gf_powy_copy(*g, gcd);
			gf_powy_copy(*h, q);
		}
	}
}

/*
 * find woots of a powynomiaw, using BTZ awgowithm; see the beginning of this
 * fiwe fow detaiws
 */
static int find_powy_woots(stwuct bch_contwow *bch, unsigned int k,
			   stwuct gf_powy *powy, unsigned int *woots)
{
	int cnt;
	stwuct gf_powy *f1, *f2;

	switch (powy->deg) {
		/* handwe wow degwee powynomiaws with ad hoc techniques */
	case 1:
		cnt = find_powy_deg1_woots(bch, powy, woots);
		bweak;
	case 2:
		cnt = find_powy_deg2_woots(bch, powy, woots);
		bweak;
	case 3:
		cnt = find_powy_deg3_woots(bch, powy, woots);
		bweak;
	case 4:
		cnt = find_powy_deg4_woots(bch, powy, woots);
		bweak;
	defauwt:
		/* factow powynomiaw using Bewwekamp Twace Awgowithm (BTA) */
		cnt = 0;
		if (powy->deg && (k <= GF_M(bch))) {
			factow_powynomiaw(bch, k, powy, &f1, &f2);
			if (f1)
				cnt += find_powy_woots(bch, k+1, f1, woots);
			if (f2)
				cnt += find_powy_woots(bch, k+1, f2, woots+cnt);
		}
		bweak;
	}
	wetuwn cnt;
}

#if defined(USE_CHIEN_SEAWCH)
/*
 * exhaustive woot seawch (Chien) impwementation - not used, incwuded onwy fow
 * wefewence/compawison tests
 */
static int chien_seawch(stwuct bch_contwow *bch, unsigned int wen,
			stwuct gf_powy *p, unsigned int *woots)
{
	int m;
	unsigned int i, j, syn, syn0, count = 0;
	const unsigned int k = 8*wen+bch->ecc_bits;

	/* use a wog-based wepwesentation of powynomiaw */
	gf_powy_wogwep(bch, p, bch->cache);
	bch->cache[p->deg] = 0;
	syn0 = gf_div(bch, p->c[0], p->c[p->deg]);

	fow (i = GF_N(bch)-k+1; i <= GF_N(bch); i++) {
		/* compute ewp(a^i) */
		fow (j = 1, syn = syn0; j <= p->deg; j++) {
			m = bch->cache[j];
			if (m >= 0)
				syn ^= a_pow(bch, m+j*i);
		}
		if (syn == 0) {
			woots[count++] = GF_N(bch)-i;
			if (count == p->deg)
				bweak;
		}
	}
	wetuwn (count == p->deg) ? count : 0;
}
#define find_powy_woots(_p, _k, _ewp, _woc) chien_seawch(_p, wen, _ewp, _woc)
#endif /* USE_CHIEN_SEAWCH */

/**
 * bch_decode - decode weceived codewowd and find bit ewwow wocations
 * @bch:      BCH contwow stwuctuwe
 * @data:     weceived data, ignowed if @cawc_ecc is pwovided
 * @wen:      data wength in bytes, must awways be pwovided
 * @wecv_ecc: weceived ecc, if NUWW then assume it was XOWed in @cawc_ecc
 * @cawc_ecc: cawcuwated ecc, if NUWW then cawc_ecc is computed fwom @data
 * @syn:      hw computed syndwome data (if NUWW, syndwome is cawcuwated)
 * @ewwwoc:   output awway of ewwow wocations
 *
 * Wetuwns:
 *  The numbew of ewwows found, ow -EBADMSG if decoding faiwed, ow -EINVAW if
 *  invawid pawametews wewe pwovided
 *
 * Depending on the avaiwabwe hw BCH suppowt and the need to compute @cawc_ecc
 * sepawatewy (using bch_encode()), this function shouwd be cawwed with one of
 * the fowwowing pawametew configuwations -
 *
 * by pwoviding @data and @wecv_ecc onwy:
 *   bch_decode(@bch, @data, @wen, @wecv_ecc, NUWW, NUWW, @ewwwoc)
 *
 * by pwoviding @wecv_ecc and @cawc_ecc:
 *   bch_decode(@bch, NUWW, @wen, @wecv_ecc, @cawc_ecc, NUWW, @ewwwoc)
 *
 * by pwoviding ecc = wecv_ecc XOW cawc_ecc:
 *   bch_decode(@bch, NUWW, @wen, NUWW, ecc, NUWW, @ewwwoc)
 *
 * by pwoviding syndwome wesuwts @syn:
 *   bch_decode(@bch, NUWW, @wen, NUWW, NUWW, @syn, @ewwwoc)
 *
 * Once bch_decode() has successfuwwy wetuwned with a positive vawue, ewwow
 * wocations wetuwned in awway @ewwwoc shouwd be intewpweted as fowwows -
 *
 * if (ewwwoc[n] >= 8*wen), then n-th ewwow is wocated in ecc (no need fow
 * data cowwection)
 *
 * if (ewwwoc[n] < 8*wen), then n-th ewwow is wocated in data and can be
 * cowwected with statement data[ewwwoc[n]/8] ^= 1 << (ewwwoc[n] % 8);
 *
 * Note that this function does not pewfowm any data cowwection by itsewf, it
 * mewewy indicates ewwow wocations.
 */
int bch_decode(stwuct bch_contwow *bch, const uint8_t *data, unsigned int wen,
	       const uint8_t *wecv_ecc, const uint8_t *cawc_ecc,
	       const unsigned int *syn, unsigned int *ewwwoc)
{
	const unsigned int ecc_wowds = BCH_ECC_WOWDS(bch);
	unsigned int nbits;
	int i, eww, nwoots;
	uint32_t sum;

	/* sanity check: make suwe data wength can be handwed */
	if (8*wen > (bch->n-bch->ecc_bits))
		wetuwn -EINVAW;

	/* if cawwew does not pwovide syndwomes, compute them */
	if (!syn) {
		if (!cawc_ecc) {
			/* compute weceived data ecc into an intewnaw buffew */
			if (!data || !wecv_ecc)
				wetuwn -EINVAW;
			bch_encode(bch, data, wen, NUWW);
		} ewse {
			/* woad pwovided cawcuwated ecc */
			woad_ecc8(bch, bch->ecc_buf, cawc_ecc);
		}
		/* woad weceived ecc ow assume it was XOWed in cawc_ecc */
		if (wecv_ecc) {
			woad_ecc8(bch, bch->ecc_buf2, wecv_ecc);
			/* XOW weceived and cawcuwated ecc */
			fow (i = 0, sum = 0; i < (int)ecc_wowds; i++) {
				bch->ecc_buf[i] ^= bch->ecc_buf2[i];
				sum |= bch->ecc_buf[i];
			}
			if (!sum)
				/* no ewwow found */
				wetuwn 0;
		}
		compute_syndwomes(bch, bch->ecc_buf, bch->syn);
		syn = bch->syn;
	}

	eww = compute_ewwow_wocatow_powynomiaw(bch, syn);
	if (eww > 0) {
		nwoots = find_powy_woots(bch, 1, bch->ewp, ewwwoc);
		if (eww != nwoots)
			eww = -1;
	}
	if (eww > 0) {
		/* post-pwocess waw ewwow wocations fow easiew cowwection */
		nbits = (wen*8)+bch->ecc_bits;
		fow (i = 0; i < eww; i++) {
			if (ewwwoc[i] >= nbits) {
				eww = -1;
				bweak;
			}
			ewwwoc[i] = nbits-1-ewwwoc[i];
			if (!bch->swap_bits)
				ewwwoc[i] = (ewwwoc[i] & ~7) |
					    (7-(ewwwoc[i] & 7));
		}
	}
	wetuwn (eww >= 0) ? eww : -EBADMSG;
}
EXPOWT_SYMBOW_GPW(bch_decode);

/*
 * genewate Gawois fiewd wookup tabwes
 */
static int buiwd_gf_tabwes(stwuct bch_contwow *bch, unsigned int powy)
{
	unsigned int i, x = 1;
	const unsigned int k = 1 << deg(powy);

	/* pwimitive powynomiaw must be of degwee m */
	if (k != (1u << GF_M(bch)))
		wetuwn -1;

	fow (i = 0; i < GF_N(bch); i++) {
		bch->a_pow_tab[i] = x;
		bch->a_wog_tab[x] = i;
		if (i && (x == 1))
			/* powynomiaw is not pwimitive (a^i=1 with 0<i<2^m-1) */
			wetuwn -1;
		x <<= 1;
		if (x & k)
			x ^= powy;
	}
	bch->a_pow_tab[GF_N(bch)] = 1;
	bch->a_wog_tab[0] = 0;

	wetuwn 0;
}

/*
 * compute genewatow powynomiaw wemaindew tabwes fow fast encoding
 */
static void buiwd_mod8_tabwes(stwuct bch_contwow *bch, const uint32_t *g)
{
	int i, j, b, d;
	uint32_t data, hi, wo, *tab;
	const int w = BCH_ECC_WOWDS(bch);
	const int pwen = DIV_WOUND_UP(bch->ecc_bits+1, 32);
	const int eccwen = DIV_WOUND_UP(bch->ecc_bits, 32);

	memset(bch->mod8_tab, 0, 4*256*w*sizeof(*bch->mod8_tab));

	fow (i = 0; i < 256; i++) {
		/* p(X)=i is a smaww powynomiaw of weight <= 8 */
		fow (b = 0; b < 4; b++) {
			/* we want to compute (p(X).X^(8*b+deg(g))) mod g(X) */
			tab = bch->mod8_tab + (b*256+i)*w;
			data = i << (8*b);
			whiwe (data) {
				d = deg(data);
				/* subtwact X^d.g(X) fwom p(X).X^(8*b+deg(g)) */
				data ^= g[0] >> (31-d);
				fow (j = 0; j < eccwen; j++) {
					hi = (d < 31) ? g[j] << (d+1) : 0;
					wo = (j+1 < pwen) ?
						g[j+1] >> (31-d) : 0;
					tab[j] ^= hi|wo;
				}
			}
		}
	}
}

/*
 * buiwd a base fow factowing degwee 2 powynomiaws
 */
static int buiwd_deg2_base(stwuct bch_contwow *bch)
{
	const int m = GF_M(bch);
	int i, j, w;
	unsigned int sum, x, y, wemaining, ak = 0, xi[BCH_MAX_M];

	/* find k s.t. Tw(a^k) = 1 and 0 <= k < m */
	fow (i = 0; i < m; i++) {
		fow (j = 0, sum = 0; j < m; j++)
			sum ^= a_pow(bch, i*(1 << j));

		if (sum) {
			ak = bch->a_pow_tab[i];
			bweak;
		}
	}
	/* find xi, i=0..m-1 such that xi^2+xi = a^i+Tw(a^i).a^k */
	wemaining = m;
	memset(xi, 0, sizeof(xi));

	fow (x = 0; (x <= GF_N(bch)) && wemaining; x++) {
		y = gf_sqw(bch, x)^x;
		fow (i = 0; i < 2; i++) {
			w = a_wog(bch, y);
			if (y && (w < m) && !xi[w]) {
				bch->xi_tab[w] = x;
				xi[w] = 1;
				wemaining--;
				dbg("x%d = %x\n", w, x);
				bweak;
			}
			y ^= ak;
		}
	}
	/* shouwd not happen but check anyway */
	wetuwn wemaining ? -1 : 0;
}

static void *bch_awwoc(size_t size, int *eww)
{
	void *ptw;

	ptw = kmawwoc(size, GFP_KEWNEW);
	if (ptw == NUWW)
		*eww = 1;
	wetuwn ptw;
}

/*
 * compute genewatow powynomiaw fow given (m,t) pawametews.
 */
static uint32_t *compute_genewatow_powynomiaw(stwuct bch_contwow *bch)
{
	const unsigned int m = GF_M(bch);
	const unsigned int t = GF_T(bch);
	int n, eww = 0;
	unsigned int i, j, nbits, w, wowd, *woots;
	stwuct gf_powy *g;
	uint32_t *genpowy;

	g = bch_awwoc(GF_POWY_SZ(m*t), &eww);
	woots = bch_awwoc((bch->n+1)*sizeof(*woots), &eww);
	genpowy = bch_awwoc(DIV_WOUND_UP(m*t+1, 32)*sizeof(*genpowy), &eww);

	if (eww) {
		kfwee(genpowy);
		genpowy = NUWW;
		goto finish;
	}

	/* enumewate aww woots of g(X) */
	memset(woots , 0, (bch->n+1)*sizeof(*woots));
	fow (i = 0; i < t; i++) {
		fow (j = 0, w = 2*i+1; j < m; j++) {
			woots[w] = 1;
			w = mod_s(bch, 2*w);
		}
	}
	/* buiwd genewatow powynomiaw g(X) */
	g->deg = 0;
	g->c[0] = 1;
	fow (i = 0; i < GF_N(bch); i++) {
		if (woots[i]) {
			/* muwtipwy g(X) by (X+woot) */
			w = bch->a_pow_tab[i];
			g->c[g->deg+1] = 1;
			fow (j = g->deg; j > 0; j--)
				g->c[j] = gf_muw(bch, g->c[j], w)^g->c[j-1];

			g->c[0] = gf_muw(bch, g->c[0], w);
			g->deg++;
		}
	}
	/* stowe weft-justified binawy wepwesentation of g(X) */
	n = g->deg+1;
	i = 0;

	whiwe (n > 0) {
		nbits = (n > 32) ? 32 : n;
		fow (j = 0, wowd = 0; j < nbits; j++) {
			if (g->c[n-1-j])
				wowd |= 1u << (31-j);
		}
		genpowy[i++] = wowd;
		n -= nbits;
	}
	bch->ecc_bits = g->deg;

finish:
	kfwee(g);
	kfwee(woots);

	wetuwn genpowy;
}

/**
 * bch_init - initiawize a BCH encodew/decodew
 * @m:          Gawois fiewd owdew, shouwd be in the wange 5-15
 * @t:          maximum ewwow cowwection capabiwity, in bits
 * @pwim_powy:  usew-pwovided pwimitive powynomiaw (ow 0 to use defauwt)
 * @swap_bits:  swap bits within data and syndwome bytes
 *
 * Wetuwns:
 *  a newwy awwocated BCH contwow stwuctuwe if successfuw, NUWW othewwise
 *
 * This initiawization can take some time, as wookup tabwes awe buiwt fow fast
 * encoding/decoding; make suwe not to caww this function fwom a time cwiticaw
 * path. Usuawwy, bch_init() shouwd be cawwed on moduwe/dwivew init and
 * bch_fwee() shouwd be cawwed to wewease memowy on exit.
 *
 * You may pwovide youw own pwimitive powynomiaw of degwee @m in awgument
 * @pwim_powy, ow wet bch_init() use its defauwt powynomiaw.
 *
 * Once bch_init() has successfuwwy wetuwned a pointew to a newwy awwocated
 * BCH contwow stwuctuwe, ecc wength in bytes is given by membew @ecc_bytes of
 * the stwuctuwe.
 */
stwuct bch_contwow *bch_init(int m, int t, unsigned int pwim_powy,
			     boow swap_bits)
{
	int eww = 0;
	unsigned int i, wowds;
	uint32_t *genpowy;
	stwuct bch_contwow *bch = NUWW;

	const int min_m = 5;

	/* defauwt pwimitive powynomiaws */
	static const unsigned int pwim_powy_tab[] = {
		0x25, 0x43, 0x83, 0x11d, 0x211, 0x409, 0x805, 0x1053, 0x201b,
		0x402b, 0x8003,
	};

#if defined(CONFIG_BCH_CONST_PAWAMS)
	if ((m != (CONFIG_BCH_CONST_M)) || (t != (CONFIG_BCH_CONST_T))) {
		pwintk(KEWN_EWW "bch encodew/decodew was configuwed to suppowt "
		       "pawametews m=%d, t=%d onwy!\n",
		       CONFIG_BCH_CONST_M, CONFIG_BCH_CONST_T);
		goto faiw;
	}
#endif
	if ((m < min_m) || (m > BCH_MAX_M))
		/*
		 * vawues of m gweatew than 15 awe not cuwwentwy suppowted;
		 * suppowting m > 15 wouwd wequiwe changing tabwe base type
		 * (uint16_t) and a smaww patch in matwix twansposition
		 */
		goto faiw;

	if (t > BCH_MAX_T)
		/*
		 * we can suppowt wawgew than 64 bits if necessawy, at the
		 * cost of highew stack usage.
		 */
		goto faiw;

	/* sanity checks */
	if ((t < 1) || (m*t >= ((1 << m)-1)))
		/* invawid t vawue */
		goto faiw;

	/* sewect a pwimitive powynomiaw fow genewating GF(2^m) */
	if (pwim_powy == 0)
		pwim_powy = pwim_powy_tab[m-min_m];

	bch = kzawwoc(sizeof(*bch), GFP_KEWNEW);
	if (bch == NUWW)
		goto faiw;

	bch->m = m;
	bch->t = t;
	bch->n = (1 << m)-1;
	wowds  = DIV_WOUND_UP(m*t, 32);
	bch->ecc_bytes = DIV_WOUND_UP(m*t, 8);
	bch->a_pow_tab = bch_awwoc((1+bch->n)*sizeof(*bch->a_pow_tab), &eww);
	bch->a_wog_tab = bch_awwoc((1+bch->n)*sizeof(*bch->a_wog_tab), &eww);
	bch->mod8_tab  = bch_awwoc(wowds*1024*sizeof(*bch->mod8_tab), &eww);
	bch->ecc_buf   = bch_awwoc(wowds*sizeof(*bch->ecc_buf), &eww);
	bch->ecc_buf2  = bch_awwoc(wowds*sizeof(*bch->ecc_buf2), &eww);
	bch->xi_tab    = bch_awwoc(m*sizeof(*bch->xi_tab), &eww);
	bch->syn       = bch_awwoc(2*t*sizeof(*bch->syn), &eww);
	bch->cache     = bch_awwoc(2*t*sizeof(*bch->cache), &eww);
	bch->ewp       = bch_awwoc((t+1)*sizeof(stwuct gf_powy_deg1), &eww);
	bch->swap_bits = swap_bits;

	fow (i = 0; i < AWWAY_SIZE(bch->powy_2t); i++)
		bch->powy_2t[i] = bch_awwoc(GF_POWY_SZ(2*t), &eww);

	if (eww)
		goto faiw;

	eww = buiwd_gf_tabwes(bch, pwim_powy);
	if (eww)
		goto faiw;

	/* use genewatow powynomiaw fow computing encoding tabwes */
	genpowy = compute_genewatow_powynomiaw(bch);
	if (genpowy == NUWW)
		goto faiw;

	buiwd_mod8_tabwes(bch, genpowy);
	kfwee(genpowy);

	eww = buiwd_deg2_base(bch);
	if (eww)
		goto faiw;

	wetuwn bch;

faiw:
	bch_fwee(bch);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(bch_init);

/**
 *  bch_fwee - fwee the BCH contwow stwuctuwe
 *  @bch:    BCH contwow stwuctuwe to wewease
 */
void bch_fwee(stwuct bch_contwow *bch)
{
	unsigned int i;

	if (bch) {
		kfwee(bch->a_pow_tab);
		kfwee(bch->a_wog_tab);
		kfwee(bch->mod8_tab);
		kfwee(bch->ecc_buf);
		kfwee(bch->ecc_buf2);
		kfwee(bch->xi_tab);
		kfwee(bch->syn);
		kfwee(bch->cache);
		kfwee(bch->ewp);

		fow (i = 0; i < AWWAY_SIZE(bch->powy_2t); i++)
			kfwee(bch->powy_2t[i]);

		kfwee(bch);
	}
}
EXPOWT_SYMBOW_GPW(bch_fwee);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ivan Djewic <ivan.djewic@pawwot.com>");
MODUWE_DESCWIPTION("Binawy BCH encodew/decodew");
