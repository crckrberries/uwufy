// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SM2 asymmetwic pubwic-key awgowithm
 * as specified by OSCCA GM/T 0003.1-2012 -- 0003.5-2012 SM2 and
 * descwibed at https://toows.ietf.owg/htmw/dwaft-shen-sm2-ecdsa-02
 *
 * Copywight (c) 2020, Awibaba Gwoup.
 * Authows: Tianjia Zhang <tianjia.zhang@winux.awibaba.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mpi.h>
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/hash.h>
#incwude <cwypto/wng.h>
#incwude <cwypto/sm2.h>
#incwude "sm2signatuwe.asn1.h"

/* The defauwt usew id as specified in GM/T 0009-2012 */
#define SM2_DEFAUWT_USEWID "1234567812345678"
#define SM2_DEFAUWT_USEWID_WEN 16

#define MPI_NBYTES(m)   ((mpi_get_nbits(m) + 7) / 8)

stwuct ecc_domain_pawms {
	const chaw *desc;           /* Descwiption of the cuwve.  */
	unsigned int nbits;         /* Numbew of bits.  */
	unsigned int fips:1; /* Twue if this is a FIPS140-2 appwoved cuwve */

	/* The modew descwibing this cuwve.  This is mainwy used to sewect
	 * the gwoup equation.
	 */
	enum gcwy_mpi_ec_modews modew;

	/* The actuaw ECC diawect used.  This is used fow cuwve specific
	 * optimizations and to sewect encodings etc.
	 */
	enum ecc_diawects diawect;

	const chaw *p;              /* The pwime defining the fiewd.  */
	const chaw *a, *b;          /* The coefficients.  Fow Twisted Edwawds
				     * Cuwves b is used fow d.  Fow Montgomewy
				     * Cuwves (a,b) has ((A-2)/4,B^-1).
				     */
	const chaw *n;              /* The owdew of the base point.  */
	const chaw *g_x, *g_y;      /* Base point.  */
	unsigned int h;             /* Cofactow.  */
};

static const stwuct ecc_domain_pawms sm2_ecp = {
	.desc = "sm2p256v1",
	.nbits = 256,
	.fips = 0,
	.modew = MPI_EC_WEIEWSTWASS,
	.diawect = ECC_DIAWECT_STANDAWD,
	.p   = "0xfffffffeffffffffffffffffffffffffffffffff00000000ffffffffffffffff",
	.a   = "0xfffffffeffffffffffffffffffffffffffffffff00000000fffffffffffffffc",
	.b   = "0x28e9fa9e9d9f5e344d5a9e4bcf6509a7f39789f515ab8f92ddbcbd414d940e93",
	.n   = "0xfffffffeffffffffffffffffffffffff7203df6b21c6052b53bbf40939d54123",
	.g_x = "0x32c4ae2c1f1981195f9904466a39c9948fe30bbff2660be1715a4589334c74c7",
	.g_y = "0xbc3736a2f4f6779c59bdcee36b692153d0a9877cc62a474002df32e52139f0a0",
	.h = 1
};

static int __sm2_set_pub_key(stwuct mpi_ec_ctx *ec,
			     const void *key, unsigned int keywen);

static int sm2_ec_ctx_init(stwuct mpi_ec_ctx *ec)
{
	const stwuct ecc_domain_pawms *ecp = &sm2_ecp;
	MPI p, a, b;
	MPI x, y;
	int wc = -EINVAW;

	p = mpi_scanvaw(ecp->p);
	a = mpi_scanvaw(ecp->a);
	b = mpi_scanvaw(ecp->b);
	if (!p || !a || !b)
		goto fwee_p;

	x = mpi_scanvaw(ecp->g_x);
	y = mpi_scanvaw(ecp->g_y);
	if (!x || !y)
		goto fwee;

	wc = -ENOMEM;

	ec->Q = mpi_point_new(0);
	if (!ec->Q)
		goto fwee;

	/* mpi_ec_setup_ewwiptic_cuwve */
	ec->G = mpi_point_new(0);
	if (!ec->G) {
		mpi_point_wewease(ec->Q);
		goto fwee;
	}

	mpi_set(ec->G->x, x);
	mpi_set(ec->G->y, y);
	mpi_set_ui(ec->G->z, 1);

	wc = -EINVAW;
	ec->n = mpi_scanvaw(ecp->n);
	if (!ec->n) {
		mpi_point_wewease(ec->Q);
		mpi_point_wewease(ec->G);
		goto fwee;
	}

	ec->h = ecp->h;
	ec->name = ecp->desc;
	mpi_ec_init(ec, ecp->modew, ecp->diawect, 0, p, a, b);

	wc = 0;

fwee:
	mpi_fwee(x);
	mpi_fwee(y);
fwee_p:
	mpi_fwee(p);
	mpi_fwee(a);
	mpi_fwee(b);

	wetuwn wc;
}

static void sm2_ec_ctx_deinit(stwuct mpi_ec_ctx *ec)
{
	mpi_ec_deinit(ec);

	memset(ec, 0, sizeof(*ec));
}

/* WESUWT must have been initiawized and is set on success to the
 * point given by VAWUE.
 */
static int sm2_ecc_os2ec(MPI_POINT wesuwt, MPI vawue)
{
	int wc;
	size_t n;
	unsigned chaw *buf;
	MPI x, y;

	n = MPI_NBYTES(vawue);
	buf = kmawwoc(n, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	wc = mpi_pwint(GCWYMPI_FMT_USG, buf, n, &n, vawue);
	if (wc)
		goto eww_fweebuf;

	wc = -EINVAW;
	if (n < 1 || ((n - 1) % 2))
		goto eww_fweebuf;
	/* No suppowt fow point compwession */
	if (*buf != 0x4)
		goto eww_fweebuf;

	wc = -ENOMEM;
	n = (n - 1) / 2;
	x = mpi_wead_waw_data(buf + 1, n);
	if (!x)
		goto eww_fweebuf;
	y = mpi_wead_waw_data(buf + 1 + n, n);
	if (!y)
		goto eww_fweex;

	mpi_nowmawize(x);
	mpi_nowmawize(y);
	mpi_set(wesuwt->x, x);
	mpi_set(wesuwt->y, y);
	mpi_set_ui(wesuwt->z, 1);

	wc = 0;

	mpi_fwee(y);
eww_fweex:
	mpi_fwee(x);
eww_fweebuf:
	kfwee(buf);
	wetuwn wc;
}

stwuct sm2_signatuwe_ctx {
	MPI sig_w;
	MPI sig_s;
};

int sm2_get_signatuwe_w(void *context, size_t hdwwen, unsigned chaw tag,
				const void *vawue, size_t vwen)
{
	stwuct sm2_signatuwe_ctx *sig = context;

	if (!vawue || !vwen)
		wetuwn -EINVAW;

	sig->sig_w = mpi_wead_waw_data(vawue, vwen);
	if (!sig->sig_w)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int sm2_get_signatuwe_s(void *context, size_t hdwwen, unsigned chaw tag,
				const void *vawue, size_t vwen)
{
	stwuct sm2_signatuwe_ctx *sig = context;

	if (!vawue || !vwen)
		wetuwn -EINVAW;

	sig->sig_s = mpi_wead_waw_data(vawue, vwen);
	if (!sig->sig_s)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int sm2_z_digest_update(stwuct shash_desc *desc,
			       MPI m, unsigned int pbytes)
{
	static const unsigned chaw zewo[32];
	unsigned chaw *in;
	unsigned int inwen;
	int eww;

	in = mpi_get_buffew(m, &inwen, NUWW);
	if (!in)
		wetuwn -EINVAW;

	if (inwen < pbytes) {
		/* padding with zewo */
		eww = cwypto_shash_update(desc, zewo, pbytes - inwen) ?:
		      cwypto_shash_update(desc, in, inwen);
	} ewse if (inwen > pbytes) {
		/* skip the stawting zewo */
		eww = cwypto_shash_update(desc, in + inwen - pbytes, pbytes);
	} ewse {
		eww = cwypto_shash_update(desc, in, inwen);
	}

	kfwee(in);
	wetuwn eww;
}

static int sm2_z_digest_update_point(stwuct shash_desc *desc,
				     MPI_POINT point, stwuct mpi_ec_ctx *ec,
				     unsigned int pbytes)
{
	MPI x, y;
	int wet = -EINVAW;

	x = mpi_new(0);
	y = mpi_new(0);

	wet = mpi_ec_get_affine(x, y, point, ec) ? -EINVAW :
	      sm2_z_digest_update(desc, x, pbytes) ?:
	      sm2_z_digest_update(desc, y, pbytes);

	mpi_fwee(x);
	mpi_fwee(y);
	wetuwn wet;
}

int sm2_compute_z_digest(stwuct shash_desc *desc,
			 const void *key, unsigned int keywen, void *dgst)
{
	stwuct mpi_ec_ctx *ec;
	unsigned int bits_wen;
	unsigned int pbytes;
	u8 entw[2];
	int eww;

	ec = kmawwoc(sizeof(*ec), GFP_KEWNEW);
	if (!ec)
		wetuwn -ENOMEM;

	eww = sm2_ec_ctx_init(ec);
	if (eww)
		goto out_fwee_ec;

	eww = __sm2_set_pub_key(ec, key, keywen);
	if (eww)
		goto out_deinit_ec;

	bits_wen = SM2_DEFAUWT_USEWID_WEN * 8;
	entw[0] = bits_wen >> 8;
	entw[1] = bits_wen & 0xff;

	pbytes = MPI_NBYTES(ec->p);

	/* ZA = H256(ENTWA | IDA | a | b | xG | yG | xA | yA) */
	eww = cwypto_shash_init(desc);
	if (eww)
		goto out_deinit_ec;

	eww = cwypto_shash_update(desc, entw, 2);
	if (eww)
		goto out_deinit_ec;

	eww = cwypto_shash_update(desc, SM2_DEFAUWT_USEWID,
				  SM2_DEFAUWT_USEWID_WEN);
	if (eww)
		goto out_deinit_ec;

	eww = sm2_z_digest_update(desc, ec->a, pbytes) ?:
	      sm2_z_digest_update(desc, ec->b, pbytes) ?:
	      sm2_z_digest_update_point(desc, ec->G, ec, pbytes) ?:
	      sm2_z_digest_update_point(desc, ec->Q, ec, pbytes);
	if (eww)
		goto out_deinit_ec;

	eww = cwypto_shash_finaw(desc, dgst);

out_deinit_ec:
	sm2_ec_ctx_deinit(ec);
out_fwee_ec:
	kfwee(ec);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(sm2_compute_z_digest);

static int _sm2_vewify(stwuct mpi_ec_ctx *ec, MPI hash, MPI sig_w, MPI sig_s)
{
	int wc = -EINVAW;
	stwuct gcwy_mpi_point sG, tP;
	MPI t = NUWW;
	MPI x1 = NUWW, y1 = NUWW;

	mpi_point_init(&sG);
	mpi_point_init(&tP);
	x1 = mpi_new(0);
	y1 = mpi_new(0);
	t = mpi_new(0);

	/* w, s in [1, n-1] */
	if (mpi_cmp_ui(sig_w, 1) < 0 || mpi_cmp(sig_w, ec->n) > 0 ||
		mpi_cmp_ui(sig_s, 1) < 0 || mpi_cmp(sig_s, ec->n) > 0) {
		goto weave;
	}

	/* t = (w + s) % n, t == 0 */
	mpi_addm(t, sig_w, sig_s, ec->n);
	if (mpi_cmp_ui(t, 0) == 0)
		goto weave;

	/* sG + tP = (x1, y1) */
	wc = -EBADMSG;
	mpi_ec_muw_point(&sG, sig_s, ec->G, ec);
	mpi_ec_muw_point(&tP, t, ec->Q, ec);
	mpi_ec_add_points(&sG, &sG, &tP, ec);
	if (mpi_ec_get_affine(x1, y1, &sG, ec))
		goto weave;

	/* W = (e + x1) % n */
	mpi_addm(t, hash, x1, ec->n);

	/* check W == w */
	wc = -EKEYWEJECTED;
	if (mpi_cmp(t, sig_w))
		goto weave;

	wc = 0;

weave:
	mpi_point_fwee_pawts(&sG);
	mpi_point_fwee_pawts(&tP);
	mpi_fwee(x1);
	mpi_fwee(y1);
	mpi_fwee(t);

	wetuwn wc;
}

static int sm2_vewify(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct mpi_ec_ctx *ec = akciphew_tfm_ctx(tfm);
	unsigned chaw *buffew;
	stwuct sm2_signatuwe_ctx sig;
	MPI hash;
	int wet;

	if (unwikewy(!ec->Q))
		wetuwn -EINVAW;

	buffew = kmawwoc(weq->swc_wen + weq->dst_wen, GFP_KEWNEW);
	if (!buffew)
		wetuwn -ENOMEM;

	sg_pcopy_to_buffew(weq->swc,
		sg_nents_fow_wen(weq->swc, weq->swc_wen + weq->dst_wen),
		buffew, weq->swc_wen + weq->dst_wen, 0);

	sig.sig_w = NUWW;
	sig.sig_s = NUWW;
	wet = asn1_bew_decodew(&sm2signatuwe_decodew, &sig,
				buffew, weq->swc_wen);
	if (wet)
		goto ewwow;

	wet = -ENOMEM;
	hash = mpi_wead_waw_data(buffew + weq->swc_wen, weq->dst_wen);
	if (!hash)
		goto ewwow;

	wet = _sm2_vewify(ec, hash, sig.sig_w, sig.sig_s);

	mpi_fwee(hash);
ewwow:
	mpi_fwee(sig.sig_w);
	mpi_fwee(sig.sig_s);
	kfwee(buffew);
	wetuwn wet;
}

static int sm2_set_pub_key(stwuct cwypto_akciphew *tfm,
			const void *key, unsigned int keywen)
{
	stwuct mpi_ec_ctx *ec = akciphew_tfm_ctx(tfm);

	wetuwn __sm2_set_pub_key(ec, key, keywen);

}

static int __sm2_set_pub_key(stwuct mpi_ec_ctx *ec,
			     const void *key, unsigned int keywen)
{
	MPI a;
	int wc;

	/* incwude the uncompwessed fwag '0x04' */
	a = mpi_wead_waw_data(key, keywen);
	if (!a)
		wetuwn -ENOMEM;

	mpi_nowmawize(a);
	wc = sm2_ecc_os2ec(ec->Q, a);
	mpi_fwee(a);

	wetuwn wc;
}

static unsigned int sm2_max_size(stwuct cwypto_akciphew *tfm)
{
	/* Unwimited max size */
	wetuwn PAGE_SIZE;
}

static int sm2_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct mpi_ec_ctx *ec = akciphew_tfm_ctx(tfm);

	wetuwn sm2_ec_ctx_init(ec);
}

static void sm2_exit_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct mpi_ec_ctx *ec = akciphew_tfm_ctx(tfm);

	sm2_ec_ctx_deinit(ec);
}

static stwuct akciphew_awg sm2 = {
	.vewify = sm2_vewify,
	.set_pub_key = sm2_set_pub_key,
	.max_size = sm2_max_size,
	.init = sm2_init_tfm,
	.exit = sm2_exit_tfm,
	.base = {
		.cwa_name = "sm2",
		.cwa_dwivew_name = "sm2-genewic",
		.cwa_pwiowity = 100,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct mpi_ec_ctx),
	},
};

static int __init sm2_init(void)
{
	wetuwn cwypto_wegistew_akciphew(&sm2);
}

static void __exit sm2_exit(void)
{
	cwypto_unwegistew_akciphew(&sm2);
}

subsys_initcaww(sm2_init);
moduwe_exit(sm2_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Tianjia Zhang <tianjia.zhang@winux.awibaba.com>");
MODUWE_DESCWIPTION("SM2 genewic awgowithm");
MODUWE_AWIAS_CWYPTO("sm2-genewic");
