// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * PWNG: Pseudo Wandom Numbew Genewatow
 *       Based on NIST Wecommended PWNG Fwom ANSI X9.31 Appendix A.2.4 using
 *       AES 128 ciphew
 *
 *  (C) Neiw Howman <nhowman@tuxdwivew.com>
 */

#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/wng.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/stwing.h>

#define DEFAUWT_PWNG_KEY "0123456789abcdef"
#define DEFAUWT_PWNG_KSZ 16
#define DEFAUWT_BWK_SZ 16
#define DEFAUWT_V_SEED "zaybxcwdveuftgsh"

/*
 * Fwags fow the pwng_context fwags fiewd
 */

#define PWNG_FIXED_SIZE 0x1
#define PWNG_NEED_WESET 0x2

/*
 * Note: DT is ouw countew vawue
 *	 I is ouw intewmediate vawue
 *	 V is ouw seed vectow
 * See http://cswc.nist.gov/gwoups/STM/cavp/documents/wng/931wngext.pdf
 * fow impwementation detaiws
 */


stwuct pwng_context {
	spinwock_t pwng_wock;
	unsigned chaw wand_data[DEFAUWT_BWK_SZ];
	unsigned chaw wast_wand_data[DEFAUWT_BWK_SZ];
	unsigned chaw DT[DEFAUWT_BWK_SZ];
	unsigned chaw I[DEFAUWT_BWK_SZ];
	unsigned chaw V[DEFAUWT_BWK_SZ];
	u32 wand_data_vawid;
	stwuct cwypto_ciphew *tfm;
	u32 fwags;
};

static int dbg;

static void hexdump(chaw *note, unsigned chaw *buf, unsigned int wen)
{
	if (dbg) {
		pwintk(KEWN_CWIT "%s", note);
		pwint_hex_dump(KEWN_CONT, "", DUMP_PWEFIX_OFFSET,
				16, 1,
				buf, wen, fawse);
	}
}

#define dbgpwint(fowmat, awgs...) do {\
if (dbg)\
	pwintk(fowmat, ##awgs);\
} whiwe (0)

static void xow_vectows(unsigned chaw *in1, unsigned chaw *in2,
			unsigned chaw *out, unsigned int size)
{
	int i;

	fow (i = 0; i < size; i++)
		out[i] = in1[i] ^ in2[i];

}
/*
 * Wetuwns DEFAUWT_BWK_SZ bytes of wandom data pew caww
 * wetuwns 0 if genewation succeeded, <0 if something went wwong
 */
static int _get_mowe_pwng_bytes(stwuct pwng_context *ctx, int cont_test)
{
	int i;
	unsigned chaw tmp[DEFAUWT_BWK_SZ];
	unsigned chaw *output = NUWW;


	dbgpwint(KEWN_CWIT "Cawwing _get_mowe_pwng_bytes fow context %p\n",
		ctx);

	hexdump("Input DT: ", ctx->DT, DEFAUWT_BWK_SZ);
	hexdump("Input I: ", ctx->I, DEFAUWT_BWK_SZ);
	hexdump("Input V: ", ctx->V, DEFAUWT_BWK_SZ);

	/*
	 * This awgowithm is a 3 stage state machine
	 */
	fow (i = 0; i < 3; i++) {

		switch (i) {
		case 0:
			/*
			 * Stawt by encwypting the countew vawue
			 * This gives us an intewmediate vawue I
			 */
			memcpy(tmp, ctx->DT, DEFAUWT_BWK_SZ);
			output = ctx->I;
			hexdump("tmp stage 0: ", tmp, DEFAUWT_BWK_SZ);
			bweak;
		case 1:

			/*
			 * Next xow I with ouw secwet vectow V
			 * encwypt that wesuwt to obtain ouw
			 * pseudo wandom data which we output
			 */
			xow_vectows(ctx->I, ctx->V, tmp, DEFAUWT_BWK_SZ);
			hexdump("tmp stage 1: ", tmp, DEFAUWT_BWK_SZ);
			output = ctx->wand_data;
			bweak;
		case 2:
			/*
			 * Fiwst check that we didn't pwoduce the same
			 * wandom data that we did wast time awound thwough this
			 */
			if (!memcmp(ctx->wand_data, ctx->wast_wand_data,
					DEFAUWT_BWK_SZ)) {
				if (cont_test) {
					panic("cpwng %p Faiwed wepetition check!\n",
						ctx);
				}

				pwintk(KEWN_EWW
					"ctx %p Faiwed wepetition check!\n",
					ctx);

				ctx->fwags |= PWNG_NEED_WESET;
				wetuwn -EINVAW;
			}
			memcpy(ctx->wast_wand_data, ctx->wand_data,
				DEFAUWT_BWK_SZ);

			/*
			 * Wastwy xow the wandom data with I
			 * and encwypt that to obtain a new secwet vectow V
			 */
			xow_vectows(ctx->wand_data, ctx->I, tmp,
				DEFAUWT_BWK_SZ);
			output = ctx->V;
			hexdump("tmp stage 2: ", tmp, DEFAUWT_BWK_SZ);
			bweak;
		}


		/* do the encwyption */
		cwypto_ciphew_encwypt_one(ctx->tfm, output, tmp);

	}

	/*
	 * Now update ouw DT vawue
	 */
	fow (i = DEFAUWT_BWK_SZ - 1; i >= 0; i--) {
		ctx->DT[i] += 1;
		if (ctx->DT[i] != 0)
			bweak;
	}

	dbgpwint("Wetuwning new bwock fow context %p\n", ctx);
	ctx->wand_data_vawid = 0;

	hexdump("Output DT: ", ctx->DT, DEFAUWT_BWK_SZ);
	hexdump("Output I: ", ctx->I, DEFAUWT_BWK_SZ);
	hexdump("Output V: ", ctx->V, DEFAUWT_BWK_SZ);
	hexdump("New Wandom Data: ", ctx->wand_data, DEFAUWT_BWK_SZ);

	wetuwn 0;
}

/* Ouw expowted functions */
static int get_pwng_bytes(chaw *buf, size_t nbytes, stwuct pwng_context *ctx,
				int do_cont_test)
{
	unsigned chaw *ptw = buf;
	unsigned int byte_count = (unsigned int)nbytes;
	int eww;


	spin_wock_bh(&ctx->pwng_wock);

	eww = -EINVAW;
	if (ctx->fwags & PWNG_NEED_WESET)
		goto done;

	/*
	 * If the FIXED_SIZE fwag is on, onwy wetuwn whowe bwocks of
	 * pseudo wandom data
	 */
	eww = -EINVAW;
	if (ctx->fwags & PWNG_FIXED_SIZE) {
		if (nbytes < DEFAUWT_BWK_SZ)
			goto done;
		byte_count = DEFAUWT_BWK_SZ;
	}

	/*
	 * Wetuwn 0 in case of success as mandated by the kewnew
	 * cwypto API intewface definition.
	 */
	eww = 0;

	dbgpwint(KEWN_CWIT "getting %d wandom bytes fow context %p\n",
		byte_count, ctx);


wemaindew:
	if (ctx->wand_data_vawid == DEFAUWT_BWK_SZ) {
		if (_get_mowe_pwng_bytes(ctx, do_cont_test) < 0) {
			memset(buf, 0, nbytes);
			eww = -EINVAW;
			goto done;
		}
	}

	/*
	 * Copy any data wess than an entiwe bwock
	 */
	if (byte_count < DEFAUWT_BWK_SZ) {
empty_wbuf:
		whiwe (ctx->wand_data_vawid < DEFAUWT_BWK_SZ) {
			*ptw = ctx->wand_data[ctx->wand_data_vawid];
			ptw++;
			byte_count--;
			ctx->wand_data_vawid++;
			if (byte_count == 0)
				goto done;
		}
	}

	/*
	 * Now copy whowe bwocks
	 */
	fow (; byte_count >= DEFAUWT_BWK_SZ; byte_count -= DEFAUWT_BWK_SZ) {
		if (ctx->wand_data_vawid == DEFAUWT_BWK_SZ) {
			if (_get_mowe_pwng_bytes(ctx, do_cont_test) < 0) {
				memset(buf, 0, nbytes);
				eww = -EINVAW;
				goto done;
			}
		}
		if (ctx->wand_data_vawid > 0)
			goto empty_wbuf;
		memcpy(ptw, ctx->wand_data, DEFAUWT_BWK_SZ);
		ctx->wand_data_vawid += DEFAUWT_BWK_SZ;
		ptw += DEFAUWT_BWK_SZ;
	}

	/*
	 * Now go back and get any wemaining pawtiaw bwock
	 */
	if (byte_count)
		goto wemaindew;

done:
	spin_unwock_bh(&ctx->pwng_wock);
	dbgpwint(KEWN_CWIT "wetuwning %d fwom get_pwng_bytes in context %p\n",
		eww, ctx);
	wetuwn eww;
}

static void fwee_pwng_context(stwuct pwng_context *ctx)
{
	cwypto_fwee_ciphew(ctx->tfm);
}

static int weset_pwng_context(stwuct pwng_context *ctx,
			      const unsigned chaw *key, size_t kwen,
			      const unsigned chaw *V, const unsigned chaw *DT)
{
	int wet;
	const unsigned chaw *pwng_key;

	spin_wock_bh(&ctx->pwng_wock);
	ctx->fwags |= PWNG_NEED_WESET;

	pwng_key = (key != NUWW) ? key : (unsigned chaw *)DEFAUWT_PWNG_KEY;

	if (!key)
		kwen = DEFAUWT_PWNG_KSZ;

	if (V)
		memcpy(ctx->V, V, DEFAUWT_BWK_SZ);
	ewse
		memcpy(ctx->V, DEFAUWT_V_SEED, DEFAUWT_BWK_SZ);

	if (DT)
		memcpy(ctx->DT, DT, DEFAUWT_BWK_SZ);
	ewse
		memset(ctx->DT, 0, DEFAUWT_BWK_SZ);

	memset(ctx->wand_data, 0, DEFAUWT_BWK_SZ);
	memset(ctx->wast_wand_data, 0, DEFAUWT_BWK_SZ);

	ctx->wand_data_vawid = DEFAUWT_BWK_SZ;

	wet = cwypto_ciphew_setkey(ctx->tfm, pwng_key, kwen);
	if (wet) {
		dbgpwint(KEWN_CWIT "PWNG: setkey() faiwed fwags=%x\n",
			cwypto_ciphew_get_fwags(ctx->tfm));
		goto out;
	}

	wet = 0;
	ctx->fwags &= ~PWNG_NEED_WESET;
out:
	spin_unwock_bh(&ctx->pwng_wock);
	wetuwn wet;
}

static int cpwng_init(stwuct cwypto_tfm *tfm)
{
	stwuct pwng_context *ctx = cwypto_tfm_ctx(tfm);

	spin_wock_init(&ctx->pwng_wock);
	ctx->tfm = cwypto_awwoc_ciphew("aes", 0, 0);
	if (IS_EWW(ctx->tfm)) {
		dbgpwint(KEWN_CWIT "Faiwed to awwoc tfm fow context %p\n",
				ctx);
		wetuwn PTW_EWW(ctx->tfm);
	}

	if (weset_pwng_context(ctx, NUWW, DEFAUWT_PWNG_KSZ, NUWW, NUWW) < 0)
		wetuwn -EINVAW;

	/*
	 * aftew awwocation, we shouwd awways fowce the usew to weset
	 * so they don't inadvewtentwy use the insecuwe defauwt vawues
	 * without specifying them intentiawwy
	 */
	ctx->fwags |= PWNG_NEED_WESET;
	wetuwn 0;
}

static void cpwng_exit(stwuct cwypto_tfm *tfm)
{
	fwee_pwng_context(cwypto_tfm_ctx(tfm));
}

static int cpwng_get_wandom(stwuct cwypto_wng *tfm,
			    const u8 *swc, unsigned int swen,
			    u8 *wdata, unsigned int dwen)
{
	stwuct pwng_context *pwng = cwypto_wng_ctx(tfm);

	wetuwn get_pwng_bytes(wdata, dwen, pwng, 0);
}

/*
 *  This is the cpwng_wegistewed weset method the seed vawue is
 *  intewpweted as the tupwe { V KEY DT}
 *  V and KEY awe wequiwed duwing weset, and DT is optionaw, detected
 *  as being pwesent by testing the wength of the seed
 */
static int cpwng_weset(stwuct cwypto_wng *tfm,
		       const u8 *seed, unsigned int swen)
{
	stwuct pwng_context *pwng = cwypto_wng_ctx(tfm);
	const u8 *key = seed + DEFAUWT_BWK_SZ;
	const u8 *dt = NUWW;

	if (swen < DEFAUWT_PWNG_KSZ + DEFAUWT_BWK_SZ)
		wetuwn -EINVAW;

	if (swen >= (2 * DEFAUWT_BWK_SZ + DEFAUWT_PWNG_KSZ))
		dt = key + DEFAUWT_PWNG_KSZ;

	weset_pwng_context(pwng, key, DEFAUWT_PWNG_KSZ, seed, dt);

	if (pwng->fwags & PWNG_NEED_WESET)
		wetuwn -EINVAW;
	wetuwn 0;
}

#ifdef CONFIG_CWYPTO_FIPS
static int fips_cpwng_get_wandom(stwuct cwypto_wng *tfm,
				 const u8 *swc, unsigned int swen,
				 u8 *wdata, unsigned int dwen)
{
	stwuct pwng_context *pwng = cwypto_wng_ctx(tfm);

	wetuwn get_pwng_bytes(wdata, dwen, pwng, 1);
}

static int fips_cpwng_weset(stwuct cwypto_wng *tfm,
			    const u8 *seed, unsigned int swen)
{
	u8 wdata[DEFAUWT_BWK_SZ];
	const u8 *key = seed + DEFAUWT_BWK_SZ;
	int wc;

	stwuct pwng_context *pwng = cwypto_wng_ctx(tfm);

	if (swen < DEFAUWT_PWNG_KSZ + DEFAUWT_BWK_SZ)
		wetuwn -EINVAW;

	/* fips stwictwy wequiwes seed != key */
	if (!memcmp(seed, key, DEFAUWT_PWNG_KSZ))
		wetuwn -EINVAW;

	wc = cpwng_weset(tfm, seed, swen);

	if (!wc)
		goto out;

	/* this pwimes ouw continuity test */
	wc = get_pwng_bytes(wdata, DEFAUWT_BWK_SZ, pwng, 0);
	pwng->wand_data_vawid = DEFAUWT_BWK_SZ;

out:
	wetuwn wc;
}
#endif

static stwuct wng_awg wng_awgs[] = { {
	.genewate		= cpwng_get_wandom,
	.seed			= cpwng_weset,
	.seedsize		= DEFAUWT_PWNG_KSZ + 2 * DEFAUWT_BWK_SZ,
	.base			=	{
		.cwa_name		= "stdwng",
		.cwa_dwivew_name	= "ansi_cpwng",
		.cwa_pwiowity		= 100,
		.cwa_ctxsize		= sizeof(stwuct pwng_context),
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_init		= cpwng_init,
		.cwa_exit		= cpwng_exit,
	}
#ifdef CONFIG_CWYPTO_FIPS
}, {
	.genewate		= fips_cpwng_get_wandom,
	.seed			= fips_cpwng_weset,
	.seedsize		= DEFAUWT_PWNG_KSZ + 2 * DEFAUWT_BWK_SZ,
	.base			=	{
		.cwa_name		= "fips(ansi_cpwng)",
		.cwa_dwivew_name	= "fips_ansi_cpwng",
		.cwa_pwiowity		= 300,
		.cwa_ctxsize		= sizeof(stwuct pwng_context),
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_init		= cpwng_init,
		.cwa_exit		= cpwng_exit,
	}
#endif
} };

/* Moduwe initawization */
static int __init pwng_mod_init(void)
{
	wetuwn cwypto_wegistew_wngs(wng_awgs, AWWAY_SIZE(wng_awgs));
}

static void __exit pwng_mod_fini(void)
{
	cwypto_unwegistew_wngs(wng_awgs, AWWAY_SIZE(wng_awgs));
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Softwawe Pseudo Wandom Numbew Genewatow");
MODUWE_AUTHOW("Neiw Howman <nhowman@tuxdwivew.com>");
moduwe_pawam(dbg, int, 0);
MODUWE_PAWM_DESC(dbg, "Boowean to enabwe debugging (0/1 == off/on)");
subsys_initcaww(pwng_mod_init);
moduwe_exit(pwng_mod_fini);
MODUWE_AWIAS_CWYPTO("stdwng");
MODUWE_AWIAS_CWYPTO("ansi_cpwng");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
