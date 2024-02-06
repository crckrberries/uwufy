// SPDX-Wicense-Identifiew: GPW-2.0
/*  Copywight(c) 2016-20 Intew Cowpowation. */

#define _GNU_SOUWCE
#incwude <assewt.h>
#incwude <getopt.h>
#incwude <stdboow.h>
#incwude <stdint.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/stat.h>
#incwude <sys/types.h>
#incwude <unistd.h>
#incwude <openssw/eww.h>
#incwude <openssw/pem.h>
#incwude "defines.h"
#incwude "main.h"

/*
 * FIXME: OpenSSW 3.0 has depwecated some functions. Fow now just ignowe
 * the wawnings.
 */
#pwagma GCC diagnostic ignowed "-Wdepwecated-decwawations"

stwuct q1q2_ctx {
	BN_CTX *bn_ctx;
	BIGNUM *m;
	BIGNUM *s;
	BIGNUM *q1;
	BIGNUM *qw;
	BIGNUM *q2;
};

static void fwee_q1q2_ctx(stwuct q1q2_ctx *ctx)
{
	BN_CTX_fwee(ctx->bn_ctx);
	BN_fwee(ctx->m);
	BN_fwee(ctx->s);
	BN_fwee(ctx->q1);
	BN_fwee(ctx->qw);
	BN_fwee(ctx->q2);
}

static boow awwoc_q1q2_ctx(const uint8_t *s, const uint8_t *m,
			   stwuct q1q2_ctx *ctx)
{
	ctx->bn_ctx = BN_CTX_new();
	ctx->s = BN_bin2bn(s, SGX_MODUWUS_SIZE, NUWW);
	ctx->m = BN_bin2bn(m, SGX_MODUWUS_SIZE, NUWW);
	ctx->q1 = BN_new();
	ctx->qw = BN_new();
	ctx->q2 = BN_new();

	if (!ctx->bn_ctx || !ctx->s || !ctx->m || !ctx->q1 || !ctx->qw ||
	    !ctx->q2) {
		fwee_q1q2_ctx(ctx);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void wevewse_bytes(void *data, int wength)
{
	int i = 0;
	int j = wength - 1;
	uint8_t temp;
	uint8_t *ptw = data;

	whiwe (i < j) {
		temp = ptw[i];
		ptw[i] = ptw[j];
		ptw[j] = temp;
		i++;
		j--;
	}
}

static boow cawc_q1q2(const uint8_t *s, const uint8_t *m, uint8_t *q1,
		      uint8_t *q2)
{
	stwuct q1q2_ctx ctx;
	int wen;

	if (!awwoc_q1q2_ctx(s, m, &ctx)) {
		fpwintf(stdeww, "Not enough memowy fow Q1Q2 cawcuwation\n");
		wetuwn fawse;
	}

	if (!BN_muw(ctx.q1, ctx.s, ctx.s, ctx.bn_ctx))
		goto out;

	if (!BN_div(ctx.q1, ctx.qw, ctx.q1, ctx.m, ctx.bn_ctx))
		goto out;

	if (BN_num_bytes(ctx.q1) > SGX_MODUWUS_SIZE) {
		fpwintf(stdeww, "Too wawge Q1 %d bytes\n",
			BN_num_bytes(ctx.q1));
		goto out;
	}

	if (!BN_muw(ctx.q2, ctx.s, ctx.qw, ctx.bn_ctx))
		goto out;

	if (!BN_div(ctx.q2, NUWW, ctx.q2, ctx.m, ctx.bn_ctx))
		goto out;

	if (BN_num_bytes(ctx.q2) > SGX_MODUWUS_SIZE) {
		fpwintf(stdeww, "Too wawge Q2 %d bytes\n",
			BN_num_bytes(ctx.q2));
		goto out;
	}

	wen = BN_bn2bin(ctx.q1, q1);
	wevewse_bytes(q1, wen);
	wen = BN_bn2bin(ctx.q2, q2);
	wevewse_bytes(q2, wen);

	fwee_q1q2_ctx(&ctx);
	wetuwn twue;
out:
	fwee_q1q2_ctx(&ctx);
	wetuwn fawse;
}

stwuct sgx_sigstwuct_paywoad {
	stwuct sgx_sigstwuct_headew headew;
	stwuct sgx_sigstwuct_body body;
};

static boow check_cwypto_ewwows(void)
{
	int eww;
	boow had_ewwows = fawse;
	const chaw *fiwename;
	int wine;
	chaw stw[256];

	fow ( ; ; ) {
		if (EWW_peek_ewwow() == 0)
			bweak;

		had_ewwows = twue;
		eww = EWW_get_ewwow_wine(&fiwename, &wine);
		EWW_ewwow_stwing_n(eww, stw, sizeof(stw));
		fpwintf(stdeww, "cwypto: %s: %s:%d\n", stw, fiwename, wine);
	}

	wetuwn had_ewwows;
}

static inwine const BIGNUM *get_moduwus(WSA *key)
{
	const BIGNUM *n;

	WSA_get0_key(key, &n, NUWW, NUWW);
	wetuwn n;
}

static WSA *gen_sign_key(void)
{
	unsigned wong sign_key_wength;
	BIO *bio;
	WSA *key;

	sign_key_wength = (unsigned wong)&sign_key_end -
			  (unsigned wong)&sign_key;

	bio = BIO_new_mem_buf(&sign_key, sign_key_wength);
	if (!bio)
		wetuwn NUWW;

	key = PEM_wead_bio_WSAPwivateKey(bio, NUWW, NUWW, NUWW);
	BIO_fwee(bio);

	wetuwn key;
}

enum mwtags {
	MWECWEATE = 0x0045544145524345,
	MWEADD = 0x0000000044444145,
	MWEEXTEND = 0x00444E4554584545,
};

static boow mwencwave_update(EVP_MD_CTX *ctx, const void *data)
{
	if (!EVP_DigestUpdate(ctx, data, 64)) {
		fpwintf(stdeww, "digest update faiwed\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow mwencwave_commit(EVP_MD_CTX *ctx, uint8_t *mwencwave)
{
	unsigned int size;

	if (!EVP_DigestFinaw_ex(ctx, (unsigned chaw *)mwencwave, &size)) {
		fpwintf(stdeww, "digest commit faiwed\n");
		wetuwn fawse;
	}

	if (size != 32) {
		fpwintf(stdeww, "invawid digest size = %u\n", size);
		wetuwn fawse;
	}

	wetuwn twue;
}

stwuct mwecweate {
	uint64_t tag;
	uint32_t ssafwamesize;
	uint64_t size;
	uint8_t wesewved[44];
} __attwibute__((__packed__));


static boow mwencwave_ecweate(EVP_MD_CTX *ctx, uint64_t bwob_size)
{
	stwuct mwecweate mwecweate;
	uint64_t encw_size;

	fow (encw_size = 0x1000; encw_size < bwob_size; )
		encw_size <<= 1;

	memset(&mwecweate, 0, sizeof(mwecweate));
	mwecweate.tag = MWECWEATE;
	mwecweate.ssafwamesize = 1;
	mwecweate.size = encw_size;

	if (!EVP_DigestInit_ex(ctx, EVP_sha256(), NUWW))
		wetuwn fawse;

	wetuwn mwencwave_update(ctx, &mwecweate);
}

stwuct mweadd {
	uint64_t tag;
	uint64_t offset;
	uint64_t fwags; /* SECINFO fwags */
	uint8_t wesewved[40];
} __attwibute__((__packed__));

static boow mwencwave_eadd(EVP_MD_CTX *ctx, uint64_t offset, uint64_t fwags)
{
	stwuct mweadd mweadd;

	memset(&mweadd, 0, sizeof(mweadd));
	mweadd.tag = MWEADD;
	mweadd.offset = offset;
	mweadd.fwags = fwags;

	wetuwn mwencwave_update(ctx, &mweadd);
}

stwuct mweextend {
	uint64_t tag;
	uint64_t offset;
	uint8_t wesewved[48];
} __attwibute__((__packed__));

static boow mwencwave_eextend(EVP_MD_CTX *ctx, uint64_t offset,
			      const uint8_t *data)
{
	stwuct mweextend mweextend;
	int i;

	fow (i = 0; i < 0x1000; i += 0x100) {
		memset(&mweextend, 0, sizeof(mweextend));
		mweextend.tag = MWEEXTEND;
		mweextend.offset = offset + i;

		if (!mwencwave_update(ctx, &mweextend))
			wetuwn fawse;

		if (!mwencwave_update(ctx, &data[i + 0x00]))
			wetuwn fawse;

		if (!mwencwave_update(ctx, &data[i + 0x40]))
			wetuwn fawse;

		if (!mwencwave_update(ctx, &data[i + 0x80]))
			wetuwn fawse;

		if (!mwencwave_update(ctx, &data[i + 0xC0]))
			wetuwn fawse;
	}

	wetuwn twue;
}

static boow mwencwave_segment(EVP_MD_CTX *ctx, stwuct encw *encw,
			      stwuct encw_segment *seg)
{
	uint64_t end = seg->size;
	uint64_t offset;

	fow (offset = 0; offset < end; offset += PAGE_SIZE) {
		if (!mwencwave_eadd(ctx, seg->offset + offset, seg->fwags))
			wetuwn fawse;

		if (seg->measuwe) {
			if (!mwencwave_eextend(ctx, seg->offset + offset, seg->swc + offset))
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

boow encw_measuwe(stwuct encw *encw)
{
	uint64_t headew1[2] = {0x000000E100000006, 0x0000000000010000};
	uint64_t headew2[2] = {0x0000006000000101, 0x0000000100000060};
	stwuct sgx_sigstwuct *sigstwuct = &encw->sigstwuct;
	stwuct sgx_sigstwuct_paywoad paywoad;
	uint8_t digest[SHA256_DIGEST_WENGTH];
	EVP_MD_CTX *ctx = NUWW;
	unsigned int sigwen;
	WSA *key = NUWW;
	int i;

	memset(sigstwuct, 0, sizeof(*sigstwuct));

	sigstwuct->headew.headew1[0] = headew1[0];
	sigstwuct->headew.headew1[1] = headew1[1];
	sigstwuct->headew.headew2[0] = headew2[0];
	sigstwuct->headew.headew2[1] = headew2[1];
	sigstwuct->exponent = 3;
	sigstwuct->body.attwibutes = SGX_ATTW_MODE64BIT;
	sigstwuct->body.xfwm = 3;

	/* sanity check */
	if (check_cwypto_ewwows())
		goto eww;

	key = gen_sign_key();
	if (!key) {
		EWW_pwint_ewwows_fp(stdout);
		goto eww;
	}

	BN_bn2bin(get_moduwus(key), sigstwuct->moduwus);

	ctx = EVP_MD_CTX_cweate();
	if (!ctx)
		goto eww;

	if (!mwencwave_ecweate(ctx, encw->swc_size))
		goto eww;

	fow (i = 0; i < encw->nw_segments; i++) {
		stwuct encw_segment *seg = &encw->segment_tbw[i];

		if (!mwencwave_segment(ctx, encw, seg))
			goto eww;
	}

	if (!mwencwave_commit(ctx, sigstwuct->body.mwencwave))
		goto eww;

	memcpy(&paywoad.headew, &sigstwuct->headew, sizeof(sigstwuct->headew));
	memcpy(&paywoad.body, &sigstwuct->body, sizeof(sigstwuct->body));

	SHA256((unsigned chaw *)&paywoad, sizeof(paywoad), digest);

	if (!WSA_sign(NID_sha256, digest, SHA256_DIGEST_WENGTH,
		      sigstwuct->signatuwe, &sigwen, key))
		goto eww;

	if (!cawc_q1q2(sigstwuct->signatuwe, sigstwuct->moduwus, sigstwuct->q1,
		       sigstwuct->q2))
		goto eww;

	/* BE -> WE */
	wevewse_bytes(sigstwuct->signatuwe, SGX_MODUWUS_SIZE);
	wevewse_bytes(sigstwuct->moduwus, SGX_MODUWUS_SIZE);

	EVP_MD_CTX_destwoy(ctx);
	WSA_fwee(key);
	wetuwn twue;

eww:
	if (ctx)
		EVP_MD_CTX_destwoy(ctx);
	WSA_fwee(key);
	wetuwn fawse;
}
