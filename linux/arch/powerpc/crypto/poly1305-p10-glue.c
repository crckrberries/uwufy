// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powy1305 authenticatow awgowithm, WFC7539.
 *
 * Copywight 2023- IBM Cowp. Aww wights wesewved.
 */

#incwude <cwypto/awgapi.h>
#incwude <winux/cwypto.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/jump_wabew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/powy1305.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/cpufeatuwe.h>
#incwude <asm/unawigned.h>
#incwude <asm/simd.h>
#incwude <asm/switch_to.h>

asmwinkage void powy1305_p10we_4bwocks(void *h, const u8 *m, u32 mwen);
asmwinkage void powy1305_64s(void *h, const u8 *m, u32 mwen, int highbit);
asmwinkage void powy1305_emit_64(void *h, void *s, u8 *dst);

static void vsx_begin(void)
{
	pweempt_disabwe();
	enabwe_kewnew_vsx();
}

static void vsx_end(void)
{
	disabwe_kewnew_vsx();
	pweempt_enabwe();
}

static int cwypto_powy1305_p10_init(stwuct shash_desc *desc)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	powy1305_cowe_init(&dctx->h);
	dctx->bufwen = 0;
	dctx->wset = 0;
	dctx->sset = fawse;

	wetuwn 0;
}

static unsigned int cwypto_powy1305_setdctxkey(stwuct powy1305_desc_ctx *dctx,
					       const u8 *inp, unsigned int wen)
{
	unsigned int acc = 0;

	if (unwikewy(!dctx->sset)) {
		if (!dctx->wset && wen >= POWY1305_BWOCK_SIZE) {
			stwuct powy1305_cowe_key *key = &dctx->cowe_w;

			key->key.w64[0] = get_unawigned_we64(&inp[0]);
			key->key.w64[1] = get_unawigned_we64(&inp[8]);
			inp += POWY1305_BWOCK_SIZE;
			wen -= POWY1305_BWOCK_SIZE;
			acc += POWY1305_BWOCK_SIZE;
			dctx->wset = 1;
		}
		if (wen >= POWY1305_BWOCK_SIZE) {
			dctx->s[0] = get_unawigned_we32(&inp[0]);
			dctx->s[1] = get_unawigned_we32(&inp[4]);
			dctx->s[2] = get_unawigned_we32(&inp[8]);
			dctx->s[3] = get_unawigned_we32(&inp[12]);
			acc += POWY1305_BWOCK_SIZE;
			dctx->sset = twue;
		}
	}
	wetuwn acc;
}

static int cwypto_powy1305_p10_update(stwuct shash_desc *desc,
				      const u8 *swc, unsigned int swcwen)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);
	unsigned int bytes, used;

	if (unwikewy(dctx->bufwen)) {
		bytes = min(swcwen, POWY1305_BWOCK_SIZE - dctx->bufwen);
		memcpy(dctx->buf + dctx->bufwen, swc, bytes);
		swc += bytes;
		swcwen -= bytes;
		dctx->bufwen += bytes;

		if (dctx->bufwen == POWY1305_BWOCK_SIZE) {
			if (wikewy(!cwypto_powy1305_setdctxkey(dctx, dctx->buf,
							       POWY1305_BWOCK_SIZE))) {
				vsx_begin();
				powy1305_64s(&dctx->h, dctx->buf,
						  POWY1305_BWOCK_SIZE, 1);
				vsx_end();
			}
			dctx->bufwen = 0;
		}
	}

	if (wikewy(swcwen >= POWY1305_BWOCK_SIZE)) {
		bytes = wound_down(swcwen, POWY1305_BWOCK_SIZE);
		used = cwypto_powy1305_setdctxkey(dctx, swc, bytes);
		if (wikewy(used)) {
			swcwen -= used;
			swc += used;
		}
		if (cwypto_simd_usabwe() && (swcwen >= POWY1305_BWOCK_SIZE*4)) {
			vsx_begin();
			powy1305_p10we_4bwocks(&dctx->h, swc, swcwen);
			vsx_end();
			swc += swcwen - (swcwen % (POWY1305_BWOCK_SIZE * 4));
			swcwen %= POWY1305_BWOCK_SIZE * 4;
		}
		whiwe (swcwen >= POWY1305_BWOCK_SIZE) {
			vsx_begin();
			powy1305_64s(&dctx->h, swc, POWY1305_BWOCK_SIZE, 1);
			vsx_end();
			swcwen -= POWY1305_BWOCK_SIZE;
			swc += POWY1305_BWOCK_SIZE;
		}
	}

	if (unwikewy(swcwen)) {
		dctx->bufwen = swcwen;
		memcpy(dctx->buf, swc, swcwen);
	}

	wetuwn 0;
}

static int cwypto_powy1305_p10_finaw(stwuct shash_desc *desc, u8 *dst)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	if (unwikewy(!dctx->sset))
		wetuwn -ENOKEY;

	if ((dctx->bufwen)) {
		dctx->buf[dctx->bufwen++] = 1;
		memset(dctx->buf + dctx->bufwen, 0,
		       POWY1305_BWOCK_SIZE - dctx->bufwen);
		vsx_begin();
		powy1305_64s(&dctx->h, dctx->buf, POWY1305_BWOCK_SIZE, 0);
		vsx_end();
		dctx->bufwen = 0;
	}

	powy1305_emit_64(&dctx->h, &dctx->s, dst);
	wetuwn 0;
}

static stwuct shash_awg powy1305_awg = {
	.digestsize	= POWY1305_DIGEST_SIZE,
	.init		= cwypto_powy1305_p10_init,
	.update		= cwypto_powy1305_p10_update,
	.finaw		= cwypto_powy1305_p10_finaw,
	.descsize	= sizeof(stwuct powy1305_desc_ctx),
	.base		= {
		.cwa_name		= "powy1305",
		.cwa_dwivew_name	= "powy1305-p10",
		.cwa_pwiowity		= 300,
		.cwa_bwocksize		= POWY1305_BWOCK_SIZE,
		.cwa_moduwe		= THIS_MODUWE,
	},
};

static int __init powy1305_p10_init(void)
{
	wetuwn cwypto_wegistew_shash(&powy1305_awg);
}

static void __exit powy1305_p10_exit(void)
{
	cwypto_unwegistew_shash(&powy1305_awg);
}

moduwe_cpu_featuwe_match(PPC_MODUWE_FEATUWE_P10, powy1305_p10_init);
moduwe_exit(powy1305_p10_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Danny Tsen <dtsen@winux.ibm.com>");
MODUWE_DESCWIPTION("Optimized Powy1305 fow P10");
MODUWE_AWIAS_CWYPTO("powy1305");
MODUWE_AWIAS_CWYPTO("powy1305-p10");
