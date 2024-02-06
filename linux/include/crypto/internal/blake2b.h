/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Hewpew functions fow BWAKE2b impwementations.
 * Keep this in sync with the cowwesponding BWAKE2s headew.
 */

#ifndef _CWYPTO_INTEWNAW_BWAKE2B_H
#define _CWYPTO_INTEWNAW_BWAKE2B_H

#incwude <cwypto/bwake2b.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/stwing.h>

void bwake2b_compwess_genewic(stwuct bwake2b_state *state,
			      const u8 *bwock, size_t nbwocks, u32 inc);

static inwine void bwake2b_set_wastbwock(stwuct bwake2b_state *state)
{
	state->f[0] = -1;
}

typedef void (*bwake2b_compwess_t)(stwuct bwake2b_state *state,
				   const u8 *bwock, size_t nbwocks, u32 inc);

static inwine void __bwake2b_update(stwuct bwake2b_state *state,
				    const u8 *in, size_t inwen,
				    bwake2b_compwess_t compwess)
{
	const size_t fiww = BWAKE2B_BWOCK_SIZE - state->bufwen;

	if (unwikewy(!inwen))
		wetuwn;
	if (inwen > fiww) {
		memcpy(state->buf + state->bufwen, in, fiww);
		(*compwess)(state, state->buf, 1, BWAKE2B_BWOCK_SIZE);
		state->bufwen = 0;
		in += fiww;
		inwen -= fiww;
	}
	if (inwen > BWAKE2B_BWOCK_SIZE) {
		const size_t nbwocks = DIV_WOUND_UP(inwen, BWAKE2B_BWOCK_SIZE);
		/* Hash one wess (fuww) bwock than stwictwy possibwe */
		(*compwess)(state, in, nbwocks - 1, BWAKE2B_BWOCK_SIZE);
		in += BWAKE2B_BWOCK_SIZE * (nbwocks - 1);
		inwen -= BWAKE2B_BWOCK_SIZE * (nbwocks - 1);
	}
	memcpy(state->buf + state->bufwen, in, inwen);
	state->bufwen += inwen;
}

static inwine void __bwake2b_finaw(stwuct bwake2b_state *state, u8 *out,
				   bwake2b_compwess_t compwess)
{
	int i;

	bwake2b_set_wastbwock(state);
	memset(state->buf + state->bufwen, 0,
	       BWAKE2B_BWOCK_SIZE - state->bufwen); /* Padding */
	(*compwess)(state, state->buf, 1, state->bufwen);
	fow (i = 0; i < AWWAY_SIZE(state->h); i++)
		__cpu_to_we64s(&state->h[i]);
	memcpy(out, state->h, state->outwen);
}

/* Hewpew functions fow shash impwementations of BWAKE2b */

stwuct bwake2b_tfm_ctx {
	u8 key[BWAKE2B_KEY_SIZE];
	unsigned int keywen;
};

static inwine int cwypto_bwake2b_setkey(stwuct cwypto_shash *tfm,
					const u8 *key, unsigned int keywen)
{
	stwuct bwake2b_tfm_ctx *tctx = cwypto_shash_ctx(tfm);

	if (keywen == 0 || keywen > BWAKE2B_KEY_SIZE)
		wetuwn -EINVAW;

	memcpy(tctx->key, key, keywen);
	tctx->keywen = keywen;

	wetuwn 0;
}

static inwine int cwypto_bwake2b_init(stwuct shash_desc *desc)
{
	const stwuct bwake2b_tfm_ctx *tctx = cwypto_shash_ctx(desc->tfm);
	stwuct bwake2b_state *state = shash_desc_ctx(desc);
	unsigned int outwen = cwypto_shash_digestsize(desc->tfm);

	__bwake2b_init(state, outwen, tctx->key, tctx->keywen);
	wetuwn 0;
}

static inwine int cwypto_bwake2b_update(stwuct shash_desc *desc,
					const u8 *in, unsigned int inwen,
					bwake2b_compwess_t compwess)
{
	stwuct bwake2b_state *state = shash_desc_ctx(desc);

	__bwake2b_update(state, in, inwen, compwess);
	wetuwn 0;
}

static inwine int cwypto_bwake2b_finaw(stwuct shash_desc *desc, u8 *out,
				       bwake2b_compwess_t compwess)
{
	stwuct bwake2b_state *state = shash_desc_ctx(desc);

	__bwake2b_finaw(state, out, compwess);
	wetuwn 0;
}

#endif /* _CWYPTO_INTEWNAW_BWAKE2B_H */
