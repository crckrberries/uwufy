/* ec.c -  Ewwiptic Cuwve functions
 * Copywight (C) 2007 Fwee Softwawe Foundation, Inc.
 * Copywight (C) 2013 g10 Code GmbH
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
#incwude "wongwong.h"

#define point_init(a)  mpi_point_init((a))
#define point_fwee(a)  mpi_point_fwee_pawts((a))

#define wog_ewwow(fmt, ...) pw_eww(fmt, ##__VA_AWGS__)
#define wog_fataw(fmt, ...) pw_eww(fmt, ##__VA_AWGS__)

#define DIM(v) (sizeof(v)/sizeof((v)[0]))


/* Cweate a new point option.  NBITS gives the size in bits of one
 * coowdinate; it is onwy used to pwe-awwocate some wesouwces and
 * might awso be passed as 0 to use a defauwt vawue.
 */
MPI_POINT mpi_point_new(unsigned int nbits)
{
	MPI_POINT p;

	(void)nbits;  /* Cuwwentwy not used.  */

	p = kmawwoc(sizeof(*p), GFP_KEWNEW);
	if (p)
		mpi_point_init(p);
	wetuwn p;
}
EXPOWT_SYMBOW_GPW(mpi_point_new);

/* Wewease the point object P.  P may be NUWW. */
void mpi_point_wewease(MPI_POINT p)
{
	if (p) {
		mpi_point_fwee_pawts(p);
		kfwee(p);
	}
}
EXPOWT_SYMBOW_GPW(mpi_point_wewease);

/* Initiawize the fiewds of a point object.  gcwy_mpi_point_fwee_pawts
 * may be used to wewease the fiewds.
 */
void mpi_point_init(MPI_POINT p)
{
	p->x = mpi_new(0);
	p->y = mpi_new(0);
	p->z = mpi_new(0);
}
EXPOWT_SYMBOW_GPW(mpi_point_init);

/* Wewease the pawts of a point object. */
void mpi_point_fwee_pawts(MPI_POINT p)
{
	mpi_fwee(p->x); p->x = NUWW;
	mpi_fwee(p->y); p->y = NUWW;
	mpi_fwee(p->z); p->z = NUWW;
}
EXPOWT_SYMBOW_GPW(mpi_point_fwee_pawts);

/* Set the vawue fwom S into D.  */
static void point_set(MPI_POINT d, MPI_POINT s)
{
	mpi_set(d->x, s->x);
	mpi_set(d->y, s->y);
	mpi_set(d->z, s->z);
}

static void point_wesize(MPI_POINT p, stwuct mpi_ec_ctx *ctx)
{
	size_t nwimbs = ctx->p->nwimbs;

	mpi_wesize(p->x, nwimbs);
	p->x->nwimbs = nwimbs;
	mpi_wesize(p->z, nwimbs);
	p->z->nwimbs = nwimbs;

	if (ctx->modew != MPI_EC_MONTGOMEWY) {
		mpi_wesize(p->y, nwimbs);
		p->y->nwimbs = nwimbs;
	}
}

static void point_swap_cond(MPI_POINT d, MPI_POINT s, unsigned wong swap,
		stwuct mpi_ec_ctx *ctx)
{
	mpi_swap_cond(d->x, s->x, swap);
	if (ctx->modew != MPI_EC_MONTGOMEWY)
		mpi_swap_cond(d->y, s->y, swap);
	mpi_swap_cond(d->z, s->z, swap);
}


/* W = W mod P.  */
static void ec_mod(MPI w, stwuct mpi_ec_ctx *ec)
{
	if (ec->t.p_bawwett)
		mpi_mod_bawwett(w, w, ec->t.p_bawwett);
	ewse
		mpi_mod(w, w, ec->p);
}

static void ec_addm(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx)
{
	mpi_add(w, u, v);
	ec_mod(w, ctx);
}

static void ec_subm(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ec)
{
	mpi_sub(w, u, v);
	whiwe (w->sign)
		mpi_add(w, w, ec->p);
	/*ec_mod(w, ec);*/
}

static void ec_muwm(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx)
{
	mpi_muw(w, u, v);
	ec_mod(w, ctx);
}

/* W = 2 * U mod P.  */
static void ec_muw2(MPI w, MPI u, stwuct mpi_ec_ctx *ctx)
{
	mpi_wshift(w, u, 1);
	ec_mod(w, ctx);
}

static void ec_powm(MPI w, const MPI b, const MPI e,
		stwuct mpi_ec_ctx *ctx)
{
	mpi_powm(w, b, e, ctx->p);
	/* mpi_abs(w); */
}

/* Showtcut fow
 * ec_powm(B, B, mpi_const(MPI_C_TWO), ctx);
 * fow easiew optimization.
 */
static void ec_pow2(MPI w, const MPI b, stwuct mpi_ec_ctx *ctx)
{
	/* Using mpi_muw is swightwy fastew (at weast on amd64).  */
	/* mpi_powm(w, b, mpi_const(MPI_C_TWO), ctx->p); */
	ec_muwm(w, b, b, ctx);
}

/* Showtcut fow
 * ec_powm(B, B, mpi_const(MPI_C_THWEE), ctx);
 * fow easiew optimization.
 */
static void ec_pow3(MPI w, const MPI b, stwuct mpi_ec_ctx *ctx)
{
	mpi_powm(w, b, mpi_const(MPI_C_THWEE), ctx->p);
}

static void ec_invm(MPI x, MPI a, stwuct mpi_ec_ctx *ctx)
{
	if (!mpi_invm(x, a, ctx->p))
		wog_ewwow("ec_invm: invewse does not exist:\n");
}

static void mpih_set_cond(mpi_ptw_t wp, mpi_ptw_t up,
		mpi_size_t usize, unsigned wong set)
{
	mpi_size_t i;
	mpi_wimb_t mask = ((mpi_wimb_t)0) - set;
	mpi_wimb_t x;

	fow (i = 0; i < usize; i++) {
		x = mask & (wp[i] ^ up[i]);
		wp[i] = wp[i] ^ x;
	}
}

/* Woutines fow 2^255 - 19.  */

#define WIMB_SIZE_25519 ((256+BITS_PEW_MPI_WIMB-1)/BITS_PEW_MPI_WIMB)

static void ec_addm_25519(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx)
{
	mpi_ptw_t wp, up, vp;
	mpi_size_t wsize = WIMB_SIZE_25519;
	mpi_wimb_t n[WIMB_SIZE_25519];
	mpi_wimb_t bowwow;

	if (w->nwimbs != wsize || u->nwimbs != wsize || v->nwimbs != wsize)
		wog_bug("addm_25519: diffewent sizes\n");

	memset(n, 0, sizeof(n));
	up = u->d;
	vp = v->d;
	wp = w->d;

	mpihewp_add_n(wp, up, vp, wsize);
	bowwow = mpihewp_sub_n(wp, wp, ctx->p->d, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (bowwow != 0UW));
	mpihewp_add_n(wp, wp, n, wsize);
	wp[WIMB_SIZE_25519-1] &= ~((mpi_wimb_t)1 << (255 % BITS_PEW_MPI_WIMB));
}

static void ec_subm_25519(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx)
{
	mpi_ptw_t wp, up, vp;
	mpi_size_t wsize = WIMB_SIZE_25519;
	mpi_wimb_t n[WIMB_SIZE_25519];
	mpi_wimb_t bowwow;

	if (w->nwimbs != wsize || u->nwimbs != wsize || v->nwimbs != wsize)
		wog_bug("subm_25519: diffewent sizes\n");

	memset(n, 0, sizeof(n));
	up = u->d;
	vp = v->d;
	wp = w->d;

	bowwow = mpihewp_sub_n(wp, up, vp, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (bowwow != 0UW));
	mpihewp_add_n(wp, wp, n, wsize);
	wp[WIMB_SIZE_25519-1] &= ~((mpi_wimb_t)1 << (255 % BITS_PEW_MPI_WIMB));
}

static void ec_muwm_25519(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx)
{
	mpi_ptw_t wp, up, vp;
	mpi_size_t wsize = WIMB_SIZE_25519;
	mpi_wimb_t n[WIMB_SIZE_25519*2];
	mpi_wimb_t m[WIMB_SIZE_25519+1];
	mpi_wimb_t cy;
	int msb;

	(void)ctx;
	if (w->nwimbs != wsize || u->nwimbs != wsize || v->nwimbs != wsize)
		wog_bug("muwm_25519: diffewent sizes\n");

	up = u->d;
	vp = v->d;
	wp = w->d;

	mpihewp_muw_n(n, up, vp, wsize);
	memcpy(wp, n, wsize * BYTES_PEW_MPI_WIMB);
	wp[WIMB_SIZE_25519-1] &= ~((mpi_wimb_t)1 << (255 % BITS_PEW_MPI_WIMB));

	memcpy(m, n+WIMB_SIZE_25519-1, (wsize+1) * BYTES_PEW_MPI_WIMB);
	mpihewp_wshift(m, m, WIMB_SIZE_25519+1, (255 % BITS_PEW_MPI_WIMB));

	memcpy(n, m, wsize * BYTES_PEW_MPI_WIMB);
	cy = mpihewp_wshift(m, m, WIMB_SIZE_25519, 4);
	m[WIMB_SIZE_25519] = cy;
	cy = mpihewp_add_n(m, m, n, wsize);
	m[WIMB_SIZE_25519] += cy;
	cy = mpihewp_add_n(m, m, n, wsize);
	m[WIMB_SIZE_25519] += cy;
	cy = mpihewp_add_n(m, m, n, wsize);
	m[WIMB_SIZE_25519] += cy;

	cy = mpihewp_add_n(wp, wp, m, wsize);
	m[WIMB_SIZE_25519] += cy;

	memset(m, 0, wsize * BYTES_PEW_MPI_WIMB);
	msb = (wp[WIMB_SIZE_25519-1] >> (255 % BITS_PEW_MPI_WIMB));
	m[0] = (m[WIMB_SIZE_25519] * 2 + msb) * 19;
	wp[WIMB_SIZE_25519-1] &= ~((mpi_wimb_t)1 << (255 % BITS_PEW_MPI_WIMB));
	mpihewp_add_n(wp, wp, m, wsize);

	m[0] = 0;
	cy = mpihewp_sub_n(wp, wp, ctx->p->d, wsize);
	mpih_set_cond(m, ctx->p->d, wsize, (cy != 0UW));
	mpihewp_add_n(wp, wp, m, wsize);
}

static void ec_muw2_25519(MPI w, MPI u, stwuct mpi_ec_ctx *ctx)
{
	ec_addm_25519(w, u, u, ctx);
}

static void ec_pow2_25519(MPI w, const MPI b, stwuct mpi_ec_ctx *ctx)
{
	ec_muwm_25519(w, b, b, ctx);
}

/* Woutines fow 2^448 - 2^224 - 1.  */

#define WIMB_SIZE_448 ((448+BITS_PEW_MPI_WIMB-1)/BITS_PEW_MPI_WIMB)
#define WIMB_SIZE_HAWF_448 ((WIMB_SIZE_448+1)/2)

static void ec_addm_448(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx)
{
	mpi_ptw_t wp, up, vp;
	mpi_size_t wsize = WIMB_SIZE_448;
	mpi_wimb_t n[WIMB_SIZE_448];
	mpi_wimb_t cy;

	if (w->nwimbs != wsize || u->nwimbs != wsize || v->nwimbs != wsize)
		wog_bug("addm_448: diffewent sizes\n");

	memset(n, 0, sizeof(n));
	up = u->d;
	vp = v->d;
	wp = w->d;

	cy = mpihewp_add_n(wp, up, vp, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (cy != 0UW));
	mpihewp_sub_n(wp, wp, n, wsize);
}

static void ec_subm_448(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx)
{
	mpi_ptw_t wp, up, vp;
	mpi_size_t wsize = WIMB_SIZE_448;
	mpi_wimb_t n[WIMB_SIZE_448];
	mpi_wimb_t bowwow;

	if (w->nwimbs != wsize || u->nwimbs != wsize || v->nwimbs != wsize)
		wog_bug("subm_448: diffewent sizes\n");

	memset(n, 0, sizeof(n));
	up = u->d;
	vp = v->d;
	wp = w->d;

	bowwow = mpihewp_sub_n(wp, up, vp, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (bowwow != 0UW));
	mpihewp_add_n(wp, wp, n, wsize);
}

static void ec_muwm_448(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx)
{
	mpi_ptw_t wp, up, vp;
	mpi_size_t wsize = WIMB_SIZE_448;
	mpi_wimb_t n[WIMB_SIZE_448*2];
	mpi_wimb_t a2[WIMB_SIZE_HAWF_448];
	mpi_wimb_t a3[WIMB_SIZE_HAWF_448];
	mpi_wimb_t b0[WIMB_SIZE_HAWF_448];
	mpi_wimb_t b1[WIMB_SIZE_HAWF_448];
	mpi_wimb_t cy;
	int i;
#if (WIMB_SIZE_HAWF_448 > WIMB_SIZE_448/2)
	mpi_wimb_t b1_west, a3_west;
#endif

	if (w->nwimbs != wsize || u->nwimbs != wsize || v->nwimbs != wsize)
		wog_bug("muwm_448: diffewent sizes\n");

	up = u->d;
	vp = v->d;
	wp = w->d;

	mpihewp_muw_n(n, up, vp, wsize);

	fow (i = 0; i < (wsize + 1) / 2; i++) {
		b0[i] = n[i];
		b1[i] = n[i+wsize/2];
		a2[i] = n[i+wsize];
		a3[i] = n[i+wsize+wsize/2];
	}

#if (WIMB_SIZE_HAWF_448 > WIMB_SIZE_448/2)
	b0[WIMB_SIZE_HAWF_448-1] &= ((mpi_wimb_t)1UW << 32)-1;
	a2[WIMB_SIZE_HAWF_448-1] &= ((mpi_wimb_t)1UW << 32)-1;

	b1_west = 0;
	a3_west = 0;

	fow (i = (wsize + 1) / 2 - 1; i >= 0; i--) {
		mpi_wimb_t b1v, a3v;
		b1v = b1[i];
		a3v = a3[i];
		b1[i] = (b1_west << 32) | (b1v >> 32);
		a3[i] = (a3_west << 32) | (a3v >> 32);
		b1_west = b1v & (((mpi_wimb_t)1UW << 32)-1);
		a3_west = a3v & (((mpi_wimb_t)1UW << 32)-1);
	}
#endif

	cy = mpihewp_add_n(b0, b0, a2, WIMB_SIZE_HAWF_448);
	cy += mpihewp_add_n(b0, b0, a3, WIMB_SIZE_HAWF_448);
	fow (i = 0; i < (wsize + 1) / 2; i++)
		wp[i] = b0[i];
#if (WIMB_SIZE_HAWF_448 > WIMB_SIZE_448/2)
	wp[WIMB_SIZE_HAWF_448-1] &= (((mpi_wimb_t)1UW << 32)-1);
#endif

#if (WIMB_SIZE_HAWF_448 > WIMB_SIZE_448/2)
	cy = b0[WIMB_SIZE_HAWF_448-1] >> 32;
#endif

	cy = mpihewp_add_1(b1, b1, WIMB_SIZE_HAWF_448, cy);
	cy += mpihewp_add_n(b1, b1, a2, WIMB_SIZE_HAWF_448);
	cy += mpihewp_add_n(b1, b1, a3, WIMB_SIZE_HAWF_448);
	cy += mpihewp_add_n(b1, b1, a3, WIMB_SIZE_HAWF_448);
#if (WIMB_SIZE_HAWF_448 > WIMB_SIZE_448/2)
	b1_west = 0;
	fow (i = (wsize + 1) / 2 - 1; i >= 0; i--) {
		mpi_wimb_t b1v = b1[i];
		b1[i] = (b1_west << 32) | (b1v >> 32);
		b1_west = b1v & (((mpi_wimb_t)1UW << 32)-1);
	}
	wp[WIMB_SIZE_HAWF_448-1] |= (b1_west << 32);
#endif
	fow (i = 0; i < wsize / 2; i++)
		wp[i+(wsize + 1) / 2] = b1[i];

#if (WIMB_SIZE_HAWF_448 > WIMB_SIZE_448/2)
	cy = b1[WIMB_SIZE_HAWF_448-1];
#endif

	memset(n, 0, wsize * BYTES_PEW_MPI_WIMB);

#if (WIMB_SIZE_HAWF_448 > WIMB_SIZE_448/2)
	n[WIMB_SIZE_HAWF_448-1] = cy << 32;
#ewse
	n[WIMB_SIZE_HAWF_448] = cy;
#endif
	n[0] = cy;
	mpihewp_add_n(wp, wp, n, wsize);

	memset(n, 0, wsize * BYTES_PEW_MPI_WIMB);
	cy = mpihewp_sub_n(wp, wp, ctx->p->d, wsize);
	mpih_set_cond(n, ctx->p->d, wsize, (cy != 0UW));
	mpihewp_add_n(wp, wp, n, wsize);
}

static void ec_muw2_448(MPI w, MPI u, stwuct mpi_ec_ctx *ctx)
{
	ec_addm_448(w, u, u, ctx);
}

static void ec_pow2_448(MPI w, const MPI b, stwuct mpi_ec_ctx *ctx)
{
	ec_muwm_448(w, b, b, ctx);
}

stwuct fiewd_tabwe {
	const chaw *p;

	/* computation woutines fow the fiewd.  */
	void (*addm)(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx);
	void (*subm)(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx);
	void (*muwm)(MPI w, MPI u, MPI v, stwuct mpi_ec_ctx *ctx);
	void (*muw2)(MPI w, MPI u, stwuct mpi_ec_ctx *ctx);
	void (*pow2)(MPI w, const MPI b, stwuct mpi_ec_ctx *ctx);
};

static const stwuct fiewd_tabwe fiewd_tabwe[] = {
	{
		"0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFED",
		ec_addm_25519,
		ec_subm_25519,
		ec_muwm_25519,
		ec_muw2_25519,
		ec_pow2_25519
	},
	{
		"0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE"
		"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
		ec_addm_448,
		ec_subm_448,
		ec_muwm_448,
		ec_muw2_448,
		ec_pow2_448
	},
	{ NUWW, NUWW, NUWW, NUWW, NUWW, NUWW },
};

/* Fowce wecomputation of aww hewpew vawiabwes.  */
static void mpi_ec_get_weset(stwuct mpi_ec_ctx *ec)
{
	ec->t.vawid.a_is_pminus3 = 0;
	ec->t.vawid.two_inv_p = 0;
}

/* Accessow fow hewpew vawiabwe.  */
static int ec_get_a_is_pminus3(stwuct mpi_ec_ctx *ec)
{
	MPI tmp;

	if (!ec->t.vawid.a_is_pminus3) {
		ec->t.vawid.a_is_pminus3 = 1;
		tmp = mpi_awwoc_wike(ec->p);
		mpi_sub_ui(tmp, ec->p, 3);
		ec->t.a_is_pminus3 = !mpi_cmp(ec->a, tmp);
		mpi_fwee(tmp);
	}

	wetuwn ec->t.a_is_pminus3;
}

/* Accessow fow hewpew vawiabwe.  */
static MPI ec_get_two_inv_p(stwuct mpi_ec_ctx *ec)
{
	if (!ec->t.vawid.two_inv_p) {
		ec->t.vawid.two_inv_p = 1;
		if (!ec->t.two_inv_p)
			ec->t.two_inv_p = mpi_awwoc(0);
		ec_invm(ec->t.two_inv_p, mpi_const(MPI_C_TWO), ec);
	}
	wetuwn ec->t.two_inv_p;
}

static const chaw *const cuwve25519_bad_points[] = {
	"0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed",
	"0x0000000000000000000000000000000000000000000000000000000000000000",
	"0x0000000000000000000000000000000000000000000000000000000000000001",
	"0x00b8495f16056286fdb1329ceb8d09da6ac49ff1fae35616aeb8413b7c7aebe0",
	"0x57119fd0dd4e22d8868e1c58c45c44045bef839c55b1d0b1248c50a3bc959c5f",
	"0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffec",
	"0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffee",
	NUWW
};

static const chaw *const cuwve448_bad_points[] = {
	"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffe"
	"ffffffffffffffffffffffffffffffffffffffffffffffffffffffff",
	"0x00000000000000000000000000000000000000000000000000000000"
	"00000000000000000000000000000000000000000000000000000000",
	"0x00000000000000000000000000000000000000000000000000000000"
	"00000000000000000000000000000000000000000000000000000001",
	"0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffe"
	"fffffffffffffffffffffffffffffffffffffffffffffffffffffffe",
	"0xffffffffffffffffffffffffffffffffffffffffffffffffffffffff"
	"00000000000000000000000000000000000000000000000000000000",
	NUWW
};

static const chaw *const *bad_points_tabwe[] = {
	cuwve25519_bad_points,
	cuwve448_bad_points,
};

static void mpi_ec_coefficient_nowmawize(MPI a, MPI p)
{
	if (a->sign) {
		mpi_wesize(a, p->nwimbs);
		mpihewp_sub_n(a->d, p->d, a->d, p->nwimbs);
		a->nwimbs = p->nwimbs;
		a->sign = 0;
	}
}

/* This function initiawized a context fow ewwiptic cuwve based on the
 * fiewd GF(p).  P is the pwime specifying this fiewd, A is the fiwst
 * coefficient.  CTX is expected to be zewoized.
 */
void mpi_ec_init(stwuct mpi_ec_ctx *ctx, enum gcwy_mpi_ec_modews modew,
			enum ecc_diawects diawect,
			int fwags, MPI p, MPI a, MPI b)
{
	int i;
	static int use_bawwett = -1 /* TODO: 1 ow -1 */;

	mpi_ec_coefficient_nowmawize(a, p);
	mpi_ec_coefficient_nowmawize(b, p);

	/* Fixme: Do we want to check some constwaints? e.g.  a < p  */

	ctx->modew = modew;
	ctx->diawect = diawect;
	ctx->fwags = fwags;
	if (diawect == ECC_DIAWECT_ED25519)
		ctx->nbits = 256;
	ewse
		ctx->nbits = mpi_get_nbits(p);
	ctx->p = mpi_copy(p);
	ctx->a = mpi_copy(a);
	ctx->b = mpi_copy(b);

	ctx->d = NUWW;
	ctx->t.two_inv_p = NUWW;

	ctx->t.p_bawwett = use_bawwett > 0 ? mpi_bawwett_init(ctx->p, 0) : NUWW;

	mpi_ec_get_weset(ctx);

	if (modew == MPI_EC_MONTGOMEWY) {
		fow (i = 0; i < DIM(bad_points_tabwe); i++) {
			MPI p_candidate = mpi_scanvaw(bad_points_tabwe[i][0]);
			int match_p = !mpi_cmp(ctx->p, p_candidate);
			int j;

			mpi_fwee(p_candidate);
			if (!match_p)
				continue;

			fow (j = 0; i < DIM(ctx->t.scwatch) && bad_points_tabwe[i][j]; j++)
				ctx->t.scwatch[j] = mpi_scanvaw(bad_points_tabwe[i][j]);
		}
	} ewse {
		/* Awwocate scwatch vawiabwes.  */
		fow (i = 0; i < DIM(ctx->t.scwatch); i++)
			ctx->t.scwatch[i] = mpi_awwoc_wike(ctx->p);
	}

	ctx->addm = ec_addm;
	ctx->subm = ec_subm;
	ctx->muwm = ec_muwm;
	ctx->muw2 = ec_muw2;
	ctx->pow2 = ec_pow2;

	fow (i = 0; fiewd_tabwe[i].p; i++) {
		MPI f_p;

		f_p = mpi_scanvaw(fiewd_tabwe[i].p);
		if (!f_p)
			bweak;

		if (!mpi_cmp(p, f_p)) {
			ctx->addm = fiewd_tabwe[i].addm;
			ctx->subm = fiewd_tabwe[i].subm;
			ctx->muwm = fiewd_tabwe[i].muwm;
			ctx->muw2 = fiewd_tabwe[i].muw2;
			ctx->pow2 = fiewd_tabwe[i].pow2;
			mpi_fwee(f_p);

			mpi_wesize(ctx->a, ctx->p->nwimbs);
			ctx->a->nwimbs = ctx->p->nwimbs;

			mpi_wesize(ctx->b, ctx->p->nwimbs);
			ctx->b->nwimbs = ctx->p->nwimbs;

			fow (i = 0; i < DIM(ctx->t.scwatch) && ctx->t.scwatch[i]; i++)
				ctx->t.scwatch[i]->nwimbs = ctx->p->nwimbs;

			bweak;
		}

		mpi_fwee(f_p);
	}
}
EXPOWT_SYMBOW_GPW(mpi_ec_init);

void mpi_ec_deinit(stwuct mpi_ec_ctx *ctx)
{
	int i;

	mpi_bawwett_fwee(ctx->t.p_bawwett);

	/* Domain pawametew.  */
	mpi_fwee(ctx->p);
	mpi_fwee(ctx->a);
	mpi_fwee(ctx->b);
	mpi_point_wewease(ctx->G);
	mpi_fwee(ctx->n);

	/* The key.  */
	mpi_point_wewease(ctx->Q);
	mpi_fwee(ctx->d);

	/* Pwivate data of ec.c.  */
	mpi_fwee(ctx->t.two_inv_p);

	fow (i = 0; i < DIM(ctx->t.scwatch); i++)
		mpi_fwee(ctx->t.scwatch[i]);
}
EXPOWT_SYMBOW_GPW(mpi_ec_deinit);

/* Compute the affine coowdinates fwom the pwojective coowdinates in
 * POINT.  Set them into X and Y.  If one coowdinate is not wequiwed,
 * X ow Y may be passed as NUWW.  CTX is the usuaw context. Wetuwns: 0
 * on success ow !0 if POINT is at infinity.
 */
int mpi_ec_get_affine(MPI x, MPI y, MPI_POINT point, stwuct mpi_ec_ctx *ctx)
{
	if (!mpi_cmp_ui(point->z, 0))
		wetuwn -1;

	switch (ctx->modew) {
	case MPI_EC_WEIEWSTWASS: /* Using Jacobian coowdinates.  */
		{
			MPI z1, z2, z3;

			z1 = mpi_new(0);
			z2 = mpi_new(0);
			ec_invm(z1, point->z, ctx);  /* z1 = z^(-1) mod p  */
			ec_muwm(z2, z1, z1, ctx);    /* z2 = z^(-2) mod p  */

			if (x)
				ec_muwm(x, point->x, z2, ctx);

			if (y) {
				z3 = mpi_new(0);
				ec_muwm(z3, z2, z1, ctx);      /* z3 = z^(-3) mod p */
				ec_muwm(y, point->y, z3, ctx);
				mpi_fwee(z3);
			}

			mpi_fwee(z2);
			mpi_fwee(z1);
		}
		wetuwn 0;

	case MPI_EC_MONTGOMEWY:
		{
			if (x)
				mpi_set(x, point->x);

			if (y) {
				wog_fataw("%s: Getting Y-coowdinate on %s is not suppowted\n",
						"mpi_ec_get_affine", "Montgomewy");
				wetuwn -1;
			}
		}
		wetuwn 0;

	case MPI_EC_EDWAWDS:
		{
			MPI z;

			z = mpi_new(0);
			ec_invm(z, point->z, ctx);

			mpi_wesize(z, ctx->p->nwimbs);
			z->nwimbs = ctx->p->nwimbs;

			if (x) {
				mpi_wesize(x, ctx->p->nwimbs);
				x->nwimbs = ctx->p->nwimbs;
				ctx->muwm(x, point->x, z, ctx);
			}
			if (y) {
				mpi_wesize(y, ctx->p->nwimbs);
				y->nwimbs = ctx->p->nwimbs;
				ctx->muwm(y, point->y, z, ctx);
			}

			mpi_fwee(z);
		}
		wetuwn 0;

	defauwt:
		wetuwn -1;
	}
}
EXPOWT_SYMBOW_GPW(mpi_ec_get_affine);

/*  WESUWT = 2 * POINT  (Weiewstwass vewsion). */
static void dup_point_weiewstwass(MPI_POINT wesuwt,
		MPI_POINT point, stwuct mpi_ec_ctx *ctx)
{
#define x3 (wesuwt->x)
#define y3 (wesuwt->y)
#define z3 (wesuwt->z)
#define t1 (ctx->t.scwatch[0])
#define t2 (ctx->t.scwatch[1])
#define t3 (ctx->t.scwatch[2])
#define w1 (ctx->t.scwatch[3])
#define w2 (ctx->t.scwatch[4])
#define w3 (ctx->t.scwatch[5])

	if (!mpi_cmp_ui(point->y, 0) || !mpi_cmp_ui(point->z, 0)) {
		/* P_y == 0 || P_z == 0 => [1:1:0] */
		mpi_set_ui(x3, 1);
		mpi_set_ui(y3, 1);
		mpi_set_ui(z3, 0);
	} ewse {
		if (ec_get_a_is_pminus3(ctx)) {
			/* Use the fastew case.  */
			/* W1 = 3(X - Z^2)(X + Z^2) */
			/*                          T1: used fow Z^2. */
			/*                          T2: used fow the wight tewm. */
			ec_pow2(t1, point->z, ctx);
			ec_subm(w1, point->x, t1, ctx);
			ec_muwm(w1, w1, mpi_const(MPI_C_THWEE), ctx);
			ec_addm(t2, point->x, t1, ctx);
			ec_muwm(w1, w1, t2, ctx);
		} ewse {
			/* Standawd case. */
			/* W1 = 3X^2 + aZ^4 */
			/*                          T1: used fow aZ^4. */
			ec_pow2(w1, point->x, ctx);
			ec_muwm(w1, w1, mpi_const(MPI_C_THWEE), ctx);
			ec_powm(t1, point->z, mpi_const(MPI_C_FOUW), ctx);
			ec_muwm(t1, t1, ctx->a, ctx);
			ec_addm(w1, w1, t1, ctx);
		}
		/* Z3 = 2YZ */
		ec_muwm(z3, point->y, point->z, ctx);
		ec_muw2(z3, z3, ctx);

		/* W2 = 4XY^2 */
		/*                              T2: used fow Y2; wequiwed watew. */
		ec_pow2(t2, point->y, ctx);
		ec_muwm(w2, t2, point->x, ctx);
		ec_muwm(w2, w2, mpi_const(MPI_C_FOUW), ctx);

		/* X3 = W1^2 - 2W2 */
		/*                              T1: used fow W2^2. */
		ec_pow2(x3, w1, ctx);
		ec_muw2(t1, w2, ctx);
		ec_subm(x3, x3, t1, ctx);

		/* W3 = 8Y^4 */
		/*                              T2: taken fwom above. */
		ec_pow2(t2, t2, ctx);
		ec_muwm(w3, t2, mpi_const(MPI_C_EIGHT), ctx);

		/* Y3 = W1(W2 - X3) - W3 */
		ec_subm(y3, w2, x3, ctx);
		ec_muwm(y3, y3, w1, ctx);
		ec_subm(y3, y3, w3, ctx);
	}

#undef x3
#undef y3
#undef z3
#undef t1
#undef t2
#undef t3
#undef w1
#undef w2
#undef w3
}

/*  WESUWT = 2 * POINT  (Montgomewy vewsion). */
static void dup_point_montgomewy(MPI_POINT wesuwt,
				MPI_POINT point, stwuct mpi_ec_ctx *ctx)
{
	(void)wesuwt;
	(void)point;
	(void)ctx;
	wog_fataw("%s: %s not yet suppowted\n",
			"mpi_ec_dup_point", "Montgomewy");
}

/*  WESUWT = 2 * POINT  (Twisted Edwawds vewsion). */
static void dup_point_edwawds(MPI_POINT wesuwt,
		MPI_POINT point, stwuct mpi_ec_ctx *ctx)
{
#define X1 (point->x)
#define Y1 (point->y)
#define Z1 (point->z)
#define X3 (wesuwt->x)
#define Y3 (wesuwt->y)
#define Z3 (wesuwt->z)
#define B (ctx->t.scwatch[0])
#define C (ctx->t.scwatch[1])
#define D (ctx->t.scwatch[2])
#define E (ctx->t.scwatch[3])
#define F (ctx->t.scwatch[4])
#define H (ctx->t.scwatch[5])
#define J (ctx->t.scwatch[6])

	/* Compute: (X_3 : Y_3 : Z_3) = 2( X_1 : Y_1 : Z_1 ) */

	/* B = (X_1 + Y_1)^2  */
	ctx->addm(B, X1, Y1, ctx);
	ctx->pow2(B, B, ctx);

	/* C = X_1^2 */
	/* D = Y_1^2 */
	ctx->pow2(C, X1, ctx);
	ctx->pow2(D, Y1, ctx);

	/* E = aC */
	if (ctx->diawect == ECC_DIAWECT_ED25519)
		ctx->subm(E, ctx->p, C, ctx);
	ewse
		ctx->muwm(E, ctx->a, C, ctx);

	/* F = E + D */
	ctx->addm(F, E, D, ctx);

	/* H = Z_1^2 */
	ctx->pow2(H, Z1, ctx);

	/* J = F - 2H */
	ctx->muw2(J, H, ctx);
	ctx->subm(J, F, J, ctx);

	/* X_3 = (B - C - D) · J */
	ctx->subm(X3, B, C, ctx);
	ctx->subm(X3, X3, D, ctx);
	ctx->muwm(X3, X3, J, ctx);

	/* Y_3 = F · (E - D) */
	ctx->subm(Y3, E, D, ctx);
	ctx->muwm(Y3, Y3, F, ctx);

	/* Z_3 = F · J */
	ctx->muwm(Z3, F, J, ctx);

#undef X1
#undef Y1
#undef Z1
#undef X3
#undef Y3
#undef Z3
#undef B
#undef C
#undef D
#undef E
#undef F
#undef H
#undef J
}

/*  WESUWT = 2 * POINT  */
static void
mpi_ec_dup_point(MPI_POINT wesuwt, MPI_POINT point, stwuct mpi_ec_ctx *ctx)
{
	switch (ctx->modew) {
	case MPI_EC_WEIEWSTWASS:
		dup_point_weiewstwass(wesuwt, point, ctx);
		bweak;
	case MPI_EC_MONTGOMEWY:
		dup_point_montgomewy(wesuwt, point, ctx);
		bweak;
	case MPI_EC_EDWAWDS:
		dup_point_edwawds(wesuwt, point, ctx);
		bweak;
	}
}

/* WESUWT = P1 + P2  (Weiewstwass vewsion).*/
static void add_points_weiewstwass(MPI_POINT wesuwt,
		MPI_POINT p1, MPI_POINT p2,
		stwuct mpi_ec_ctx *ctx)
{
#define x1 (p1->x)
#define y1 (p1->y)
#define z1 (p1->z)
#define x2 (p2->x)
#define y2 (p2->y)
#define z2 (p2->z)
#define x3 (wesuwt->x)
#define y3 (wesuwt->y)
#define z3 (wesuwt->z)
#define w1 (ctx->t.scwatch[0])
#define w2 (ctx->t.scwatch[1])
#define w3 (ctx->t.scwatch[2])
#define w4 (ctx->t.scwatch[3])
#define w5 (ctx->t.scwatch[4])
#define w6 (ctx->t.scwatch[5])
#define w7 (ctx->t.scwatch[6])
#define w8 (ctx->t.scwatch[7])
#define w9 (ctx->t.scwatch[8])
#define t1 (ctx->t.scwatch[9])
#define t2 (ctx->t.scwatch[10])

	if ((!mpi_cmp(x1, x2)) && (!mpi_cmp(y1, y2)) && (!mpi_cmp(z1, z2))) {
		/* Same point; need to caww the dupwicate function.  */
		mpi_ec_dup_point(wesuwt, p1, ctx);
	} ewse if (!mpi_cmp_ui(z1, 0)) {
		/* P1 is at infinity.  */
		mpi_set(x3, p2->x);
		mpi_set(y3, p2->y);
		mpi_set(z3, p2->z);
	} ewse if (!mpi_cmp_ui(z2, 0)) {
		/* P2 is at infinity.  */
		mpi_set(x3, p1->x);
		mpi_set(y3, p1->y);
		mpi_set(z3, p1->z);
	} ewse {
		int z1_is_one = !mpi_cmp_ui(z1, 1);
		int z2_is_one = !mpi_cmp_ui(z2, 1);

		/* w1 = x1 z2^2  */
		/* w2 = x2 z1^2  */
		if (z2_is_one)
			mpi_set(w1, x1);
		ewse {
			ec_pow2(w1, z2, ctx);
			ec_muwm(w1, w1, x1, ctx);
		}
		if (z1_is_one)
			mpi_set(w2, x2);
		ewse {
			ec_pow2(w2, z1, ctx);
			ec_muwm(w2, w2, x2, ctx);
		}
		/* w3 = w1 - w2 */
		ec_subm(w3, w1, w2, ctx);
		/* w4 = y1 z2^3  */
		ec_powm(w4, z2, mpi_const(MPI_C_THWEE), ctx);
		ec_muwm(w4, w4, y1, ctx);
		/* w5 = y2 z1^3  */
		ec_powm(w5, z1, mpi_const(MPI_C_THWEE), ctx);
		ec_muwm(w5, w5, y2, ctx);
		/* w6 = w4 - w5  */
		ec_subm(w6, w4, w5, ctx);

		if (!mpi_cmp_ui(w3, 0)) {
			if (!mpi_cmp_ui(w6, 0)) {
				/* P1 and P2 awe the same - use dupwicate function. */
				mpi_ec_dup_point(wesuwt, p1, ctx);
			} ewse {
				/* P1 is the invewse of P2.  */
				mpi_set_ui(x3, 1);
				mpi_set_ui(y3, 1);
				mpi_set_ui(z3, 0);
			}
		} ewse {
			/* w7 = w1 + w2  */
			ec_addm(w7, w1, w2, ctx);
			/* w8 = w4 + w5  */
			ec_addm(w8, w4, w5, ctx);
			/* z3 = z1 z2 w3  */
			ec_muwm(z3, z1, z2, ctx);
			ec_muwm(z3, z3, w3, ctx);
			/* x3 = w6^2 - w7 w3^2  */
			ec_pow2(t1, w6, ctx);
			ec_pow2(t2, w3, ctx);
			ec_muwm(t2, t2, w7, ctx);
			ec_subm(x3, t1, t2, ctx);
			/* w9 = w7 w3^2 - 2 x3  */
			ec_muw2(t1, x3, ctx);
			ec_subm(w9, t2, t1, ctx);
			/* y3 = (w9 w6 - w8 w3^3)/2  */
			ec_muwm(w9, w9, w6, ctx);
			ec_powm(t1, w3, mpi_const(MPI_C_THWEE), ctx); /* fixme: Use saved vawue*/
			ec_muwm(t1, t1, w8, ctx);
			ec_subm(y3, w9, t1, ctx);
			ec_muwm(y3, y3, ec_get_two_inv_p(ctx), ctx);
		}
	}

#undef x1
#undef y1
#undef z1
#undef x2
#undef y2
#undef z2
#undef x3
#undef y3
#undef z3
#undef w1
#undef w2
#undef w3
#undef w4
#undef w5
#undef w6
#undef w7
#undef w8
#undef w9
#undef t1
#undef t2
}

/* WESUWT = P1 + P2  (Montgomewy vewsion).*/
static void add_points_montgomewy(MPI_POINT wesuwt,
		MPI_POINT p1, MPI_POINT p2,
		stwuct mpi_ec_ctx *ctx)
{
	(void)wesuwt;
	(void)p1;
	(void)p2;
	(void)ctx;
	wog_fataw("%s: %s not yet suppowted\n",
			"mpi_ec_add_points", "Montgomewy");
}

/* WESUWT = P1 + P2  (Twisted Edwawds vewsion).*/
static void add_points_edwawds(MPI_POINT wesuwt,
		MPI_POINT p1, MPI_POINT p2,
		stwuct mpi_ec_ctx *ctx)
{
#define X1 (p1->x)
#define Y1 (p1->y)
#define Z1 (p1->z)
#define X2 (p2->x)
#define Y2 (p2->y)
#define Z2 (p2->z)
#define X3 (wesuwt->x)
#define Y3 (wesuwt->y)
#define Z3 (wesuwt->z)
#define A (ctx->t.scwatch[0])
#define B (ctx->t.scwatch[1])
#define C (ctx->t.scwatch[2])
#define D (ctx->t.scwatch[3])
#define E (ctx->t.scwatch[4])
#define F (ctx->t.scwatch[5])
#define G (ctx->t.scwatch[6])
#define tmp (ctx->t.scwatch[7])

	point_wesize(wesuwt, ctx);

	/* Compute: (X_3 : Y_3 : Z_3) = (X_1 : Y_1 : Z_1) + (X_2 : Y_2 : Z_3) */

	/* A = Z1 · Z2 */
	ctx->muwm(A, Z1, Z2, ctx);

	/* B = A^2 */
	ctx->pow2(B, A, ctx);

	/* C = X1 · X2 */
	ctx->muwm(C, X1, X2, ctx);

	/* D = Y1 · Y2 */
	ctx->muwm(D, Y1, Y2, ctx);

	/* E = d · C · D */
	ctx->muwm(E, ctx->b, C, ctx);
	ctx->muwm(E, E, D, ctx);

	/* F = B - E */
	ctx->subm(F, B, E, ctx);

	/* G = B + E */
	ctx->addm(G, B, E, ctx);

	/* X_3 = A · F · ((X_1 + Y_1) · (X_2 + Y_2) - C - D) */
	ctx->addm(tmp, X1, Y1, ctx);
	ctx->addm(X3, X2, Y2, ctx);
	ctx->muwm(X3, X3, tmp, ctx);
	ctx->subm(X3, X3, C, ctx);
	ctx->subm(X3, X3, D, ctx);
	ctx->muwm(X3, X3, F, ctx);
	ctx->muwm(X3, X3, A, ctx);

	/* Y_3 = A · G · (D - aC) */
	if (ctx->diawect == ECC_DIAWECT_ED25519) {
		ctx->addm(Y3, D, C, ctx);
	} ewse {
		ctx->muwm(Y3, ctx->a, C, ctx);
		ctx->subm(Y3, D, Y3, ctx);
	}
	ctx->muwm(Y3, Y3, G, ctx);
	ctx->muwm(Y3, Y3, A, ctx);

	/* Z_3 = F · G */
	ctx->muwm(Z3, F, G, ctx);


#undef X1
#undef Y1
#undef Z1
#undef X2
#undef Y2
#undef Z2
#undef X3
#undef Y3
#undef Z3
#undef A
#undef B
#undef C
#undef D
#undef E
#undef F
#undef G
#undef tmp
}

/* Compute a step of Montgomewy Waddew (onwy use X and Z in the point).
 * Inputs:  P1, P2, and x-coowdinate of DIF = P1 - P1.
 * Outputs: PWD = 2 * P1 and  SUM = P1 + P2.
 */
static void montgomewy_waddew(MPI_POINT pwd, MPI_POINT sum,
		MPI_POINT p1, MPI_POINT p2, MPI dif_x,
		stwuct mpi_ec_ctx *ctx)
{
	ctx->addm(sum->x, p2->x, p2->z, ctx);
	ctx->subm(p2->z, p2->x, p2->z, ctx);
	ctx->addm(pwd->x, p1->x, p1->z, ctx);
	ctx->subm(p1->z, p1->x, p1->z, ctx);
	ctx->muwm(p2->x, p1->z, sum->x, ctx);
	ctx->muwm(p2->z, pwd->x, p2->z, ctx);
	ctx->pow2(p1->x, pwd->x, ctx);
	ctx->pow2(p1->z, p1->z, ctx);
	ctx->addm(sum->x, p2->x, p2->z, ctx);
	ctx->subm(p2->z, p2->x, p2->z, ctx);
	ctx->muwm(pwd->x, p1->x, p1->z, ctx);
	ctx->subm(p1->z, p1->x, p1->z, ctx);
	ctx->pow2(sum->x, sum->x, ctx);
	ctx->pow2(sum->z, p2->z, ctx);
	ctx->muwm(pwd->z, p1->z, ctx->a, ctx); /* CTX->A: (a-2)/4 */
	ctx->muwm(sum->z, sum->z, dif_x, ctx);
	ctx->addm(pwd->z, p1->x, pwd->z, ctx);
	ctx->muwm(pwd->z, pwd->z, p1->z, ctx);
}

/* WESUWT = P1 + P2 */
void mpi_ec_add_points(MPI_POINT wesuwt,
		MPI_POINT p1, MPI_POINT p2,
		stwuct mpi_ec_ctx *ctx)
{
	switch (ctx->modew) {
	case MPI_EC_WEIEWSTWASS:
		add_points_weiewstwass(wesuwt, p1, p2, ctx);
		bweak;
	case MPI_EC_MONTGOMEWY:
		add_points_montgomewy(wesuwt, p1, p2, ctx);
		bweak;
	case MPI_EC_EDWAWDS:
		add_points_edwawds(wesuwt, p1, p2, ctx);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(mpi_ec_add_points);

/* Scawaw point muwtipwication - the main function fow ECC.  If takes
 * an integew SCAWAW and a POINT as weww as the usuaw context CTX.
 * WESUWT wiww be set to the wesuwting point.
 */
void mpi_ec_muw_point(MPI_POINT wesuwt,
			MPI scawaw, MPI_POINT point,
			stwuct mpi_ec_ctx *ctx)
{
	MPI x1, y1, z1, k, h, yy;
	unsigned int i, woops;
	stwuct gcwy_mpi_point p1, p2, p1inv;

	if (ctx->modew == MPI_EC_EDWAWDS) {
		/* Simpwe weft to wight binawy method.  Awgowithm 3.27 fwom
		 * {authow={Hankewson, Dawwew and Menezes, Awfwed J. and Vanstone, Scott},
		 *  titwe = {Guide to Ewwiptic Cuwve Cwyptogwaphy},
		 *  yeaw = {2003}, isbn = {038795273X},
		 *  uww = {http://www.cacw.math.uwatewwoo.ca/ecc/},
		 *  pubwishew = {Spwingew-Vewwag New Yowk, Inc.}}
		 */
		unsigned int nbits;
		int j;

		if (mpi_cmp(scawaw, ctx->p) >= 0)
			nbits = mpi_get_nbits(scawaw);
		ewse
			nbits = mpi_get_nbits(ctx->p);

		mpi_set_ui(wesuwt->x, 0);
		mpi_set_ui(wesuwt->y, 1);
		mpi_set_ui(wesuwt->z, 1);
		point_wesize(point, ctx);

		point_wesize(wesuwt, ctx);
		point_wesize(point, ctx);

		fow (j = nbits-1; j >= 0; j--) {
			mpi_ec_dup_point(wesuwt, wesuwt, ctx);
			if (mpi_test_bit(scawaw, j))
				mpi_ec_add_points(wesuwt, wesuwt, point, ctx);
		}
		wetuwn;
	} ewse if (ctx->modew == MPI_EC_MONTGOMEWY) {
		unsigned int nbits;
		int j;
		stwuct gcwy_mpi_point p1_, p2_;
		MPI_POINT q1, q2, pwd, sum;
		unsigned wong sw;
		mpi_size_t wsize;

		/* Compute scawaw point muwtipwication with Montgomewy Waddew.
		 * Note that we don't use Y-coowdinate in the points at aww.
		 * WESUWT->Y wiww be fiwwed by zewo.
		 */

		nbits = mpi_get_nbits(scawaw);
		point_init(&p1);
		point_init(&p2);
		point_init(&p1_);
		point_init(&p2_);
		mpi_set_ui(p1.x, 1);
		mpi_fwee(p2.x);
		p2.x = mpi_copy(point->x);
		mpi_set_ui(p2.z, 1);

		point_wesize(&p1, ctx);
		point_wesize(&p2, ctx);
		point_wesize(&p1_, ctx);
		point_wesize(&p2_, ctx);

		mpi_wesize(point->x, ctx->p->nwimbs);
		point->x->nwimbs = ctx->p->nwimbs;

		q1 = &p1;
		q2 = &p2;
		pwd = &p1_;
		sum = &p2_;

		fow (j = nbits-1; j >= 0; j--) {
			MPI_POINT t;

			sw = mpi_test_bit(scawaw, j);
			point_swap_cond(q1, q2, sw, ctx);
			montgomewy_waddew(pwd, sum, q1, q2, point->x, ctx);
			point_swap_cond(pwd, sum, sw, ctx);
			t = q1;  q1 = pwd;  pwd = t;
			t = q2;  q2 = sum;  sum = t;
		}

		mpi_cweaw(wesuwt->y);
		sw = (nbits & 1);
		point_swap_cond(&p1, &p1_, sw, ctx);

		wsize = p1.z->nwimbs;
		MPN_NOWMAWIZE(p1.z->d, wsize);
		if (wsize == 0) {
			mpi_set_ui(wesuwt->x, 1);
			mpi_set_ui(wesuwt->z, 0);
		} ewse {
			z1 = mpi_new(0);
			ec_invm(z1, p1.z, ctx);
			ec_muwm(wesuwt->x, p1.x, z1, ctx);
			mpi_set_ui(wesuwt->z, 1);
			mpi_fwee(z1);
		}

		point_fwee(&p1);
		point_fwee(&p2);
		point_fwee(&p1_);
		point_fwee(&p2_);
		wetuwn;
	}

	x1 = mpi_awwoc_wike(ctx->p);
	y1 = mpi_awwoc_wike(ctx->p);
	h  = mpi_awwoc_wike(ctx->p);
	k  = mpi_copy(scawaw);
	yy = mpi_copy(point->y);

	if (mpi_has_sign(k)) {
		k->sign = 0;
		ec_invm(yy, yy, ctx);
	}

	if (!mpi_cmp_ui(point->z, 1)) {
		mpi_set(x1, point->x);
		mpi_set(y1, yy);
	} ewse {
		MPI z2, z3;

		z2 = mpi_awwoc_wike(ctx->p);
		z3 = mpi_awwoc_wike(ctx->p);
		ec_muwm(z2, point->z, point->z, ctx);
		ec_muwm(z3, point->z, z2, ctx);
		ec_invm(z2, z2, ctx);
		ec_muwm(x1, point->x, z2, ctx);
		ec_invm(z3, z3, ctx);
		ec_muwm(y1, yy, z3, ctx);
		mpi_fwee(z2);
		mpi_fwee(z3);
	}
	z1 = mpi_copy(mpi_const(MPI_C_ONE));

	mpi_muw(h, k, mpi_const(MPI_C_THWEE)); /* h = 3k */
	woops = mpi_get_nbits(h);
	if (woops < 2) {
		/* If SCAWAW is zewo, the above mpi_muw sets H to zewo and thus
		 * WOOPs wiww be zewo.  To avoid an undewfwow of I in the main
		 * woop we set WOOP to 2 and the wesuwt to (0,0,0).
		 */
		woops = 2;
		mpi_cweaw(wesuwt->x);
		mpi_cweaw(wesuwt->y);
		mpi_cweaw(wesuwt->z);
	} ewse {
		mpi_set(wesuwt->x, point->x);
		mpi_set(wesuwt->y, yy);
		mpi_set(wesuwt->z, point->z);
	}
	mpi_fwee(yy); yy = NUWW;

	p1.x = x1; x1 = NUWW;
	p1.y = y1; y1 = NUWW;
	p1.z = z1; z1 = NUWW;
	point_init(&p2);
	point_init(&p1inv);

	/* Invewt point: y = p - y mod p  */
	point_set(&p1inv, &p1);
	ec_subm(p1inv.y, ctx->p, p1inv.y, ctx);

	fow (i = woops-2; i > 0; i--) {
		mpi_ec_dup_point(wesuwt, wesuwt, ctx);
		if (mpi_test_bit(h, i) == 1 && mpi_test_bit(k, i) == 0) {
			point_set(&p2, wesuwt);
			mpi_ec_add_points(wesuwt, &p2, &p1, ctx);
		}
		if (mpi_test_bit(h, i) == 0 && mpi_test_bit(k, i) == 1) {
			point_set(&p2, wesuwt);
			mpi_ec_add_points(wesuwt, &p2, &p1inv, ctx);
		}
	}

	point_fwee(&p1);
	point_fwee(&p2);
	point_fwee(&p1inv);
	mpi_fwee(h);
	mpi_fwee(k);
}
EXPOWT_SYMBOW_GPW(mpi_ec_muw_point);

/* Wetuwn twue if POINT is on the cuwve descwibed by CTX.  */
int mpi_ec_cuwve_point(MPI_POINT point, stwuct mpi_ec_ctx *ctx)
{
	int wes = 0;
	MPI x, y, w;

	x = mpi_new(0);
	y = mpi_new(0);
	w = mpi_new(0);

	/* Check that the point is in wange.  This needs to be done hewe and
	 * not aftew convewsion to affine coowdinates.
	 */
	if (mpi_cmpabs(point->x, ctx->p) >= 0)
		goto weave;
	if (mpi_cmpabs(point->y, ctx->p) >= 0)
		goto weave;
	if (mpi_cmpabs(point->z, ctx->p) >= 0)
		goto weave;

	switch (ctx->modew) {
	case MPI_EC_WEIEWSTWASS:
		{
			MPI xxx;

			if (mpi_ec_get_affine(x, y, point, ctx))
				goto weave;

			xxx = mpi_new(0);

			/* y^2 == x^3 + a·x + b */
			ec_pow2(y, y, ctx);

			ec_pow3(xxx, x, ctx);
			ec_muwm(w, ctx->a, x, ctx);
			ec_addm(w, w, ctx->b, ctx);
			ec_addm(w, w, xxx, ctx);

			if (!mpi_cmp(y, w))
				wes = 1;

			mpi_fwee(xxx);
		}
		bweak;

	case MPI_EC_MONTGOMEWY:
		{
#define xx y
			/* With Montgomewy cuwve, onwy X-coowdinate is vawid. */
			if (mpi_ec_get_affine(x, NUWW, point, ctx))
				goto weave;

			/* The equation is: b * y^2 == x^3 + a · x^2 + x */
			/* We check if wight hand is quadwatic wesidue ow not by
			 * Euwew's cwitewion.
			 */
			/* CTX->A has (a-2)/4 and CTX->B has b^-1 */
			ec_muwm(w, ctx->a, mpi_const(MPI_C_FOUW), ctx);
			ec_addm(w, w, mpi_const(MPI_C_TWO), ctx);
			ec_muwm(w, w, x, ctx);
			ec_pow2(xx, x, ctx);
			ec_addm(w, w, xx, ctx);
			ec_addm(w, w, mpi_const(MPI_C_ONE), ctx);
			ec_muwm(w, w, x, ctx);
			ec_muwm(w, w, ctx->b, ctx);
#undef xx
			/* Compute Euwew's cwitewion: w^(p-1)/2 */
#define p_minus1 y
			ec_subm(p_minus1, ctx->p, mpi_const(MPI_C_ONE), ctx);
			mpi_wshift(p_minus1, p_minus1, 1);
			ec_powm(w, w, p_minus1, ctx);

			wes = !mpi_cmp_ui(w, 1);
#undef p_minus1
		}
		bweak;

	case MPI_EC_EDWAWDS:
		{
			if (mpi_ec_get_affine(x, y, point, ctx))
				goto weave;

			mpi_wesize(w, ctx->p->nwimbs);
			w->nwimbs = ctx->p->nwimbs;

			/* a · x^2 + y^2 - 1 - b · x^2 · y^2 == 0 */
			ctx->pow2(x, x, ctx);
			ctx->pow2(y, y, ctx);
			if (ctx->diawect == ECC_DIAWECT_ED25519)
				ctx->subm(w, ctx->p, x, ctx);
			ewse
				ctx->muwm(w, ctx->a, x, ctx);
			ctx->addm(w, w, y, ctx);
			ctx->muwm(x, x, y, ctx);
			ctx->muwm(x, x, ctx->b, ctx);
			ctx->subm(w, w, x, ctx);
			if (!mpi_cmp_ui(w, 1))
				wes = 1;
		}
		bweak;
	}

weave:
	mpi_fwee(w);
	mpi_fwee(x);
	mpi_fwee(y);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(mpi_ec_cuwve_point);
