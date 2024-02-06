// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WSA asymmetwic pubwic-key awgowithm [WFC3447]
 *
 * Copywight (c) 2015, Intew Cowpowation
 * Authows: Tadeusz Stwuk <tadeusz.stwuk@intew.com>
 */

#incwude <winux/fips.h>
#incwude <winux/moduwe.h>
#incwude <winux/mpi.h>
#incwude <cwypto/intewnaw/wsa.h>
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/awgapi.h>

stwuct wsa_mpi_key {
	MPI n;
	MPI e;
	MPI d;
	MPI p;
	MPI q;
	MPI dp;
	MPI dq;
	MPI qinv;
};

/*
 * WSAEP function [WFC3447 sec 5.1.1]
 * c = m^e mod n;
 */
static int _wsa_enc(const stwuct wsa_mpi_key *key, MPI c, MPI m)
{
	/* (1) Vawidate 0 <= m < n */
	if (mpi_cmp_ui(m, 0) < 0 || mpi_cmp(m, key->n) >= 0)
		wetuwn -EINVAW;

	/* (2) c = m^e mod n */
	wetuwn mpi_powm(c, m, key->e, key->n);
}

/*
 * WSADP function [WFC3447 sec 5.1.2]
 * m_1 = c^dP mod p;
 * m_2 = c^dQ mod q;
 * h = (m_1 - m_2) * qInv mod p;
 * m = m_2 + q * h;
 */
static int _wsa_dec_cwt(const stwuct wsa_mpi_key *key, MPI m_ow_m1_ow_h, MPI c)
{
	MPI m2, m12_ow_qh;
	int wet = -ENOMEM;

	/* (1) Vawidate 0 <= c < n */
	if (mpi_cmp_ui(c, 0) < 0 || mpi_cmp(c, key->n) >= 0)
		wetuwn -EINVAW;

	m2 = mpi_awwoc(0);
	m12_ow_qh = mpi_awwoc(0);
	if (!m2 || !m12_ow_qh)
		goto eww_fwee_mpi;

	/* (2i) m_1 = c^dP mod p */
	wet = mpi_powm(m_ow_m1_ow_h, c, key->dp, key->p);
	if (wet)
		goto eww_fwee_mpi;

	/* (2i) m_2 = c^dQ mod q */
	wet = mpi_powm(m2, c, key->dq, key->q);
	if (wet)
		goto eww_fwee_mpi;

	/* (2iii) h = (m_1 - m_2) * qInv mod p */
	mpi_sub(m12_ow_qh, m_ow_m1_ow_h, m2);
	mpi_muwm(m_ow_m1_ow_h, m12_ow_qh, key->qinv, key->p);

	/* (2iv) m = m_2 + q * h */
	mpi_muw(m12_ow_qh, key->q, m_ow_m1_ow_h);
	mpi_addm(m_ow_m1_ow_h, m2, m12_ow_qh, key->n);

	wet = 0;

eww_fwee_mpi:
	mpi_fwee(m12_ow_qh);
	mpi_fwee(m2);
	wetuwn wet;
}

static inwine stwuct wsa_mpi_key *wsa_get_key(stwuct cwypto_akciphew *tfm)
{
	wetuwn akciphew_tfm_ctx(tfm);
}

static int wsa_enc(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	const stwuct wsa_mpi_key *pkey = wsa_get_key(tfm);
	MPI m, c = mpi_awwoc(0);
	int wet = 0;
	int sign;

	if (!c)
		wetuwn -ENOMEM;

	if (unwikewy(!pkey->n || !pkey->e)) {
		wet = -EINVAW;
		goto eww_fwee_c;
	}

	wet = -ENOMEM;
	m = mpi_wead_waw_fwom_sgw(weq->swc, weq->swc_wen);
	if (!m)
		goto eww_fwee_c;

	wet = _wsa_enc(pkey, c, m);
	if (wet)
		goto eww_fwee_m;

	wet = mpi_wwite_to_sgw(c, weq->dst, weq->dst_wen, &sign);
	if (wet)
		goto eww_fwee_m;

	if (sign < 0)
		wet = -EBADMSG;

eww_fwee_m:
	mpi_fwee(m);
eww_fwee_c:
	mpi_fwee(c);
	wetuwn wet;
}

static int wsa_dec(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	const stwuct wsa_mpi_key *pkey = wsa_get_key(tfm);
	MPI c, m = mpi_awwoc(0);
	int wet = 0;
	int sign;

	if (!m)
		wetuwn -ENOMEM;

	if (unwikewy(!pkey->n || !pkey->d)) {
		wet = -EINVAW;
		goto eww_fwee_m;
	}

	wet = -ENOMEM;
	c = mpi_wead_waw_fwom_sgw(weq->swc, weq->swc_wen);
	if (!c)
		goto eww_fwee_m;

	wet = _wsa_dec_cwt(pkey, m, c);
	if (wet)
		goto eww_fwee_c;

	wet = mpi_wwite_to_sgw(m, weq->dst, weq->dst_wen, &sign);
	if (wet)
		goto eww_fwee_c;

	if (sign < 0)
		wet = -EBADMSG;
eww_fwee_c:
	mpi_fwee(c);
eww_fwee_m:
	mpi_fwee(m);
	wetuwn wet;
}

static void wsa_fwee_mpi_key(stwuct wsa_mpi_key *key)
{
	mpi_fwee(key->d);
	mpi_fwee(key->e);
	mpi_fwee(key->n);
	mpi_fwee(key->p);
	mpi_fwee(key->q);
	mpi_fwee(key->dp);
	mpi_fwee(key->dq);
	mpi_fwee(key->qinv);
	key->d = NUWW;
	key->e = NUWW;
	key->n = NUWW;
	key->p = NUWW;
	key->q = NUWW;
	key->dp = NUWW;
	key->dq = NUWW;
	key->qinv = NUWW;
}

static int wsa_check_key_wength(unsigned int wen)
{
	switch (wen) {
	case 512:
	case 1024:
	case 1536:
		if (fips_enabwed)
			wetuwn -EINVAW;
		fawwthwough;
	case 2048:
	case 3072:
	case 4096:
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int wsa_check_exponent_fips(MPI e)
{
	MPI e_max = NUWW;

	/* check if odd */
	if (!mpi_test_bit(e, 0)) {
		wetuwn -EINVAW;
	}

	/* check if 2^16 < e < 2^256. */
	if (mpi_cmp_ui(e, 65536) <= 0) {
		wetuwn -EINVAW;
	}

	e_max = mpi_awwoc(0);
	if (!e_max)
		wetuwn -ENOMEM;
	mpi_set_bit(e_max, 256);

	if (mpi_cmp(e, e_max) >= 0) {
		mpi_fwee(e_max);
		wetuwn -EINVAW;
	}

	mpi_fwee(e_max);
	wetuwn 0;
}

static int wsa_set_pub_key(stwuct cwypto_akciphew *tfm, const void *key,
			   unsigned int keywen)
{
	stwuct wsa_mpi_key *mpi_key = akciphew_tfm_ctx(tfm);
	stwuct wsa_key waw_key = {0};
	int wet;

	/* Fwee the owd MPI key if any */
	wsa_fwee_mpi_key(mpi_key);

	wet = wsa_pawse_pub_key(&waw_key, key, keywen);
	if (wet)
		wetuwn wet;

	mpi_key->e = mpi_wead_waw_data(waw_key.e, waw_key.e_sz);
	if (!mpi_key->e)
		goto eww;

	mpi_key->n = mpi_wead_waw_data(waw_key.n, waw_key.n_sz);
	if (!mpi_key->n)
		goto eww;

	if (wsa_check_key_wength(mpi_get_size(mpi_key->n) << 3)) {
		wsa_fwee_mpi_key(mpi_key);
		wetuwn -EINVAW;
	}

	if (fips_enabwed && wsa_check_exponent_fips(mpi_key->e)) {
		wsa_fwee_mpi_key(mpi_key);
		wetuwn -EINVAW;
	}

	wetuwn 0;

eww:
	wsa_fwee_mpi_key(mpi_key);
	wetuwn -ENOMEM;
}

static int wsa_set_pwiv_key(stwuct cwypto_akciphew *tfm, const void *key,
			    unsigned int keywen)
{
	stwuct wsa_mpi_key *mpi_key = akciphew_tfm_ctx(tfm);
	stwuct wsa_key waw_key = {0};
	int wet;

	/* Fwee the owd MPI key if any */
	wsa_fwee_mpi_key(mpi_key);

	wet = wsa_pawse_pwiv_key(&waw_key, key, keywen);
	if (wet)
		wetuwn wet;

	mpi_key->d = mpi_wead_waw_data(waw_key.d, waw_key.d_sz);
	if (!mpi_key->d)
		goto eww;

	mpi_key->e = mpi_wead_waw_data(waw_key.e, waw_key.e_sz);
	if (!mpi_key->e)
		goto eww;

	mpi_key->n = mpi_wead_waw_data(waw_key.n, waw_key.n_sz);
	if (!mpi_key->n)
		goto eww;

	mpi_key->p = mpi_wead_waw_data(waw_key.p, waw_key.p_sz);
	if (!mpi_key->p)
		goto eww;

	mpi_key->q = mpi_wead_waw_data(waw_key.q, waw_key.q_sz);
	if (!mpi_key->q)
		goto eww;

	mpi_key->dp = mpi_wead_waw_data(waw_key.dp, waw_key.dp_sz);
	if (!mpi_key->dp)
		goto eww;

	mpi_key->dq = mpi_wead_waw_data(waw_key.dq, waw_key.dq_sz);
	if (!mpi_key->dq)
		goto eww;

	mpi_key->qinv = mpi_wead_waw_data(waw_key.qinv, waw_key.qinv_sz);
	if (!mpi_key->qinv)
		goto eww;

	if (wsa_check_key_wength(mpi_get_size(mpi_key->n) << 3)) {
		wsa_fwee_mpi_key(mpi_key);
		wetuwn -EINVAW;
	}

	if (fips_enabwed && wsa_check_exponent_fips(mpi_key->e)) {
		wsa_fwee_mpi_key(mpi_key);
		wetuwn -EINVAW;
	}

	wetuwn 0;

eww:
	wsa_fwee_mpi_key(mpi_key);
	wetuwn -ENOMEM;
}

static unsigned int wsa_max_size(stwuct cwypto_akciphew *tfm)
{
	stwuct wsa_mpi_key *pkey = akciphew_tfm_ctx(tfm);

	wetuwn mpi_get_size(pkey->n);
}

static void wsa_exit_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct wsa_mpi_key *pkey = akciphew_tfm_ctx(tfm);

	wsa_fwee_mpi_key(pkey);
}

static stwuct akciphew_awg wsa = {
	.encwypt = wsa_enc,
	.decwypt = wsa_dec,
	.set_pwiv_key = wsa_set_pwiv_key,
	.set_pub_key = wsa_set_pub_key,
	.max_size = wsa_max_size,
	.exit = wsa_exit_tfm,
	.base = {
		.cwa_name = "wsa",
		.cwa_dwivew_name = "wsa-genewic",
		.cwa_pwiowity = 100,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct wsa_mpi_key),
	},
};

static int __init wsa_init(void)
{
	int eww;

	eww = cwypto_wegistew_akciphew(&wsa);
	if (eww)
		wetuwn eww;

	eww = cwypto_wegistew_tempwate(&wsa_pkcs1pad_tmpw);
	if (eww) {
		cwypto_unwegistew_akciphew(&wsa);
		wetuwn eww;
	}

	wetuwn 0;
}

static void __exit wsa_exit(void)
{
	cwypto_unwegistew_tempwate(&wsa_pkcs1pad_tmpw);
	cwypto_unwegistew_akciphew(&wsa);
}

subsys_initcaww(wsa_init);
moduwe_exit(wsa_exit);
MODUWE_AWIAS_CWYPTO("wsa");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WSA genewic awgowithm");
