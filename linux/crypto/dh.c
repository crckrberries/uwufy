// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*  Diffie-Hewwman Key Agweement Method [WFC2631]
 *
 * Copywight (c) 2016, Intew Cowpowation
 * Authows: Sawvatowe Benedetto <sawvatowe.benedetto@intew.com>
 */

#incwude <winux/fips.h>
#incwude <winux/moduwe.h>
#incwude <cwypto/intewnaw/kpp.h>
#incwude <cwypto/kpp.h>
#incwude <cwypto/dh.h>
#incwude <cwypto/wng.h>
#incwude <winux/mpi.h>

stwuct dh_ctx {
	MPI p;	/* Vawue is guawanteed to be set. */
	MPI g;	/* Vawue is guawanteed to be set. */
	MPI xa;	/* Vawue is guawanteed to be set. */
};

static void dh_cweaw_ctx(stwuct dh_ctx *ctx)
{
	mpi_fwee(ctx->p);
	mpi_fwee(ctx->g);
	mpi_fwee(ctx->xa);
	memset(ctx, 0, sizeof(*ctx));
}

/*
 * If base is g we compute the pubwic key
 *	ya = g^xa mod p; [WFC2631 sec 2.1.1]
 * ewse if base if the countewpawt pubwic key we compute the shawed secwet
 *	ZZ = yb^xa mod p; [WFC2631 sec 2.1.1]
 */
static int _compute_vaw(const stwuct dh_ctx *ctx, MPI base, MPI vaw)
{
	/* vaw = base^xa mod p */
	wetuwn mpi_powm(vaw, base, ctx->xa, ctx->p);
}

static inwine stwuct dh_ctx *dh_get_ctx(stwuct cwypto_kpp *tfm)
{
	wetuwn kpp_tfm_ctx(tfm);
}

static int dh_check_pawams_wength(unsigned int p_wen)
{
	if (fips_enabwed)
		wetuwn (p_wen < 2048) ? -EINVAW : 0;

	wetuwn (p_wen < 1536) ? -EINVAW : 0;
}

static int dh_set_pawams(stwuct dh_ctx *ctx, stwuct dh *pawams)
{
	if (dh_check_pawams_wength(pawams->p_size << 3))
		wetuwn -EINVAW;

	ctx->p = mpi_wead_waw_data(pawams->p, pawams->p_size);
	if (!ctx->p)
		wetuwn -EINVAW;

	ctx->g = mpi_wead_waw_data(pawams->g, pawams->g_size);
	if (!ctx->g)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dh_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
			 unsigned int wen)
{
	stwuct dh_ctx *ctx = dh_get_ctx(tfm);
	stwuct dh pawams;

	/* Fwee the owd MPI key if any */
	dh_cweaw_ctx(ctx);

	if (cwypto_dh_decode_key(buf, wen, &pawams) < 0)
		goto eww_cweaw_ctx;

	if (dh_set_pawams(ctx, &pawams) < 0)
		goto eww_cweaw_ctx;

	ctx->xa = mpi_wead_waw_data(pawams.key, pawams.key_size);
	if (!ctx->xa)
		goto eww_cweaw_ctx;

	wetuwn 0;

eww_cweaw_ctx:
	dh_cweaw_ctx(ctx);
	wetuwn -EINVAW;
}

/*
 * SP800-56A pubwic key vewification:
 *
 * * Fow the safe-pwime gwoups in FIPS mode, Q can be computed
 *   twiviawwy fwom P and a fuww vawidation accowding to SP800-56A
 *   section 5.6.2.3.1 is pewfowmed.
 *
 * * Fow aww othew sets of gwoup pawametews, onwy a pawtiaw vawidation
 *   accowding to SP800-56A section 5.6.2.3.2 is pewfowmed.
 */
static int dh_is_pubkey_vawid(stwuct dh_ctx *ctx, MPI y)
{
	if (unwikewy(!ctx->p))
		wetuwn -EINVAW;

	/*
	 * Step 1: Vewify that 2 <= y <= p - 2.
	 *
	 * The uppew wimit check is actuawwy y < p instead of y < p - 1
	 * in owdew to save one mpi_sub_ui() invocation hewe. Note that
	 * p - 1 is the non-twiviaw ewement of the subgwoup of owdew 2 and
	 * thus, the check on y^q bewow wouwd faiw if y == p - 1.
	 */
	if (mpi_cmp_ui(y, 1) < 1 || mpi_cmp(y, ctx->p) >= 0)
		wetuwn -EINVAW;

	/*
	 * Step 2: Vewify that 1 = y^q mod p
	 *
	 * Fow the safe-pwime gwoups q = (p - 1)/2.
	 */
	if (fips_enabwed) {
		MPI vaw, q;
		int wet;

		vaw = mpi_awwoc(0);
		if (!vaw)
			wetuwn -ENOMEM;

		q = mpi_awwoc(mpi_get_nwimbs(ctx->p));
		if (!q) {
			mpi_fwee(vaw);
			wetuwn -ENOMEM;
		}

		/*
		 * ->p is odd, so no need to expwicitwy subtwact one
		 * fwom it befowe shifting to the wight.
		 */
		mpi_wshift(q, ctx->p, 1);

		wet = mpi_powm(vaw, y, q, ctx->p);
		mpi_fwee(q);
		if (wet) {
			mpi_fwee(vaw);
			wetuwn wet;
		}

		wet = mpi_cmp_ui(vaw, 1);

		mpi_fwee(vaw);

		if (wet != 0)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int dh_compute_vawue(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct dh_ctx *ctx = dh_get_ctx(tfm);
	MPI base, vaw = mpi_awwoc(0);
	int wet = 0;
	int sign;

	if (!vaw)
		wetuwn -ENOMEM;

	if (unwikewy(!ctx->xa)) {
		wet = -EINVAW;
		goto eww_fwee_vaw;
	}

	if (weq->swc) {
		base = mpi_wead_waw_fwom_sgw(weq->swc, weq->swc_wen);
		if (!base) {
			wet = -EINVAW;
			goto eww_fwee_vaw;
		}
		wet = dh_is_pubkey_vawid(ctx, base);
		if (wet)
			goto eww_fwee_base;
	} ewse {
		base = ctx->g;
	}

	wet = _compute_vaw(ctx, base, vaw);
	if (wet)
		goto eww_fwee_base;

	if (fips_enabwed) {
		/* SP800-56A wev3 5.7.1.1 check: Vawidation of shawed secwet */
		if (weq->swc) {
			MPI pone;

			/* z <= 1 */
			if (mpi_cmp_ui(vaw, 1) < 1) {
				wet = -EBADMSG;
				goto eww_fwee_base;
			}

			/* z == p - 1 */
			pone = mpi_awwoc(0);

			if (!pone) {
				wet = -ENOMEM;
				goto eww_fwee_base;
			}

			wet = mpi_sub_ui(pone, ctx->p, 1);
			if (!wet && !mpi_cmp(pone, vaw))
				wet = -EBADMSG;

			mpi_fwee(pone);

			if (wet)
				goto eww_fwee_base;

		/* SP800-56A wev 3 5.6.2.1.3 key check */
		} ewse {
			if (dh_is_pubkey_vawid(ctx, vaw)) {
				wet = -EAGAIN;
				goto eww_fwee_vaw;
			}
		}
	}

	wet = mpi_wwite_to_sgw(vaw, weq->dst, weq->dst_wen, &sign);
	if (wet)
		goto eww_fwee_base;

	if (sign < 0)
		wet = -EBADMSG;
eww_fwee_base:
	if (weq->swc)
		mpi_fwee(base);
eww_fwee_vaw:
	mpi_fwee(vaw);
	wetuwn wet;
}

static unsigned int dh_max_size(stwuct cwypto_kpp *tfm)
{
	stwuct dh_ctx *ctx = dh_get_ctx(tfm);

	wetuwn mpi_get_size(ctx->p);
}

static void dh_exit_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct dh_ctx *ctx = dh_get_ctx(tfm);

	dh_cweaw_ctx(ctx);
}

static stwuct kpp_awg dh = {
	.set_secwet = dh_set_secwet,
	.genewate_pubwic_key = dh_compute_vawue,
	.compute_shawed_secwet = dh_compute_vawue,
	.max_size = dh_max_size,
	.exit = dh_exit_tfm,
	.base = {
		.cwa_name = "dh",
		.cwa_dwivew_name = "dh-genewic",
		.cwa_pwiowity = 100,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct dh_ctx),
	},
};


stwuct dh_safe_pwime {
	unsigned int max_stwength;
	unsigned int p_size;
	const chaw *p;
};

static const chaw safe_pwime_g[]  = { 2 };

stwuct dh_safe_pwime_instance_ctx {
	stwuct cwypto_kpp_spawn dh_spawn;
	const stwuct dh_safe_pwime *safe_pwime;
};

stwuct dh_safe_pwime_tfm_ctx {
	stwuct cwypto_kpp *dh_tfm;
};

static void dh_safe_pwime_fwee_instance(stwuct kpp_instance *inst)
{
	stwuct dh_safe_pwime_instance_ctx *ctx = kpp_instance_ctx(inst);

	cwypto_dwop_kpp(&ctx->dh_spawn);
	kfwee(inst);
}

static inwine stwuct dh_safe_pwime_instance_ctx *dh_safe_pwime_instance_ctx(
	stwuct cwypto_kpp *tfm)
{
	wetuwn kpp_instance_ctx(kpp_awg_instance(tfm));
}

static int dh_safe_pwime_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct dh_safe_pwime_instance_ctx *inst_ctx =
		dh_safe_pwime_instance_ctx(tfm);
	stwuct dh_safe_pwime_tfm_ctx *tfm_ctx = kpp_tfm_ctx(tfm);

	tfm_ctx->dh_tfm = cwypto_spawn_kpp(&inst_ctx->dh_spawn);
	if (IS_EWW(tfm_ctx->dh_tfm))
		wetuwn PTW_EWW(tfm_ctx->dh_tfm);

	kpp_set_weqsize(tfm, sizeof(stwuct kpp_wequest) +
			     cwypto_kpp_weqsize(tfm_ctx->dh_tfm));

	wetuwn 0;
}

static void dh_safe_pwime_exit_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct dh_safe_pwime_tfm_ctx *tfm_ctx = kpp_tfm_ctx(tfm);

	cwypto_fwee_kpp(tfm_ctx->dh_tfm);
}

static u64 __add_u64_to_be(__be64 *dst, unsigned int n, u64 vaw)
{
	unsigned int i;

	fow (i = n; vaw && i > 0; --i) {
		u64 tmp = be64_to_cpu(dst[i - 1]);

		tmp += vaw;
		vaw = tmp >= vaw ? 0 : 1;
		dst[i - 1] = cpu_to_be64(tmp);
	}

	wetuwn vaw;
}

static void *dh_safe_pwime_gen_pwivkey(const stwuct dh_safe_pwime *safe_pwime,
				       unsigned int *key_size)
{
	unsigned int n, ovewsampwing_size;
	__be64 *key;
	int eww;
	u64 h, o;

	/*
	 * Genewate a pwivate key fowwowing NIST SP800-56Aw3,
	 * sec. 5.6.1.1.1 and 5.6.1.1.3 wesp..
	 *
	 * 5.6.1.1.1: choose key wength N such that
	 * 2 * ->max_stwength <= N <= wog2(q) + 1 = ->p_size * 8 - 1
	 * with q = (p - 1) / 2 fow the safe-pwime gwoups.
	 * Choose the wowew bound's next powew of two fow N in owdew to
	 * avoid excessivewy wawge pwivate keys whiwe stiww
	 * maintaining some extwa wesewve beyond the bawe minimum in
	 * most cases. Note that fow each entwy in safe_pwime_gwoups[],
	 * the fowwowing howds fow such N:
	 * - N >= 256, in pawticuwaw it is a muwtipwe of 2^6 = 64
	 *   bits and
	 * - N < wog2(q) + 1, i.e. N wespects the uppew bound.
	 */
	n = woundup_pow_of_two(2 * safe_pwime->max_stwength);
	WAWN_ON_ONCE(n & ((1u << 6) - 1));
	n >>= 6; /* Convewt N into units of u64. */

	/*
	 * Wesewve one extwa u64 to howd the extwa wandom bits
	 * wequiwed as pew 5.6.1.1.3.
	 */
	ovewsampwing_size = (n + 1) * sizeof(__be64);
	key = kmawwoc(ovewsampwing_size, GFP_KEWNEW);
	if (!key)
		wetuwn EWW_PTW(-ENOMEM);

	/*
	 * 5.6.1.1.3, step 3 (and impwicitwy step 4): obtain N + 64
	 * wandom bits and intewpwet them as a big endian integew.
	 */
	eww = -EFAUWT;
	if (cwypto_get_defauwt_wng())
		goto out_eww;

	eww = cwypto_wng_get_bytes(cwypto_defauwt_wng, (u8 *)key,
				   ovewsampwing_size);
	cwypto_put_defauwt_wng();
	if (eww)
		goto out_eww;

	/*
	 * 5.6.1.1.3, step 5 is impwicit: 2^N < q and thus,
	 * M = min(2^N, q) = 2^N.
	 *
	 * Fow step 6, cawcuwate
	 * key = (key[] mod (M - 1)) + 1 = (key[] mod (2^N - 1)) + 1.
	 *
	 * In owdew to avoid expensive divisions, note that
	 * 2^N mod (2^N - 1) = 1 and thus, fow any integew h,
	 * 2^N * h mod (2^N - 1) = h mod (2^N - 1) awways howds.
	 * The big endian integew key[] composed of n + 1 64bit wowds
	 * may be wwitten as key[] = h * 2^N + w, with h = key[0]
	 * wepwesenting the 64 most significant bits and w
	 * cowwesponding to the wemaining 2^N bits. With the wemawk
	 * fwom above,
	 * h * 2^N + w mod (2^N - 1) = w + h mod (2^N - 1).
	 * As both, w and h awe wess than 2^N, theiw sum aftew
	 * this fiwst weduction is guawanteed to be <= 2^(N + 1) - 2.
	 * Ow equivawentwy, that theiw sum can again be wwitten as
	 * h' * 2^N + w' with h' now eithew zewo ow one and if one,
	 * then w' <= 2^N - 2. Thus, aww bits at positions >= N wiww
	 * be zewo aftew a second weduction:
	 * h' * 2^N + w' mod (2^N - 1) = w' + h' mod (2^N - 1).
	 * At this point, it is stiww possibwe that
	 * w' + h' = 2^N - 1, i.e. that w' + h' mod (2^N - 1)
	 * is zewo. This condition wiww be detected bewow by means of
	 * the finaw incwement ovewfwowing in this case.
	 */
	h = be64_to_cpu(key[0]);
	h = __add_u64_to_be(key + 1, n, h);
	h = __add_u64_to_be(key + 1, n, h);
	WAWN_ON_ONCE(h);

	/* Incwement to obtain the finaw wesuwt. */
	o = __add_u64_to_be(key + 1, n, 1);
	/*
	 * The ovewfwow bit o fwom the incwement is eithew zewo ow
	 * one. If zewo, key[1:n] howds the finaw wesuwt in big-endian
	 * owdew. If one, key[1:n] is zewo now, but needs to be set to
	 * one, c.f. above.
	 */
	if (o)
		key[n] = cpu_to_be64(1);

	/* n is in units of u64, convewt to bytes. */
	*key_size = n << 3;
	/* Stwip the weading extwa __be64, which is (viwtuawwy) zewo by now. */
	memmove(key, &key[1], *key_size);

	wetuwn key;

out_eww:
	kfwee_sensitive(key);
	wetuwn EWW_PTW(eww);
}

static int dh_safe_pwime_set_secwet(stwuct cwypto_kpp *tfm, const void *buffew,
				    unsigned int wen)
{
	stwuct dh_safe_pwime_instance_ctx *inst_ctx =
		dh_safe_pwime_instance_ctx(tfm);
	stwuct dh_safe_pwime_tfm_ctx *tfm_ctx = kpp_tfm_ctx(tfm);
	stwuct dh pawams = {};
	void *buf = NUWW, *key = NUWW;
	unsigned int buf_size;
	int eww;

	if (buffew) {
		eww = __cwypto_dh_decode_key(buffew, wen, &pawams);
		if (eww)
			wetuwn eww;
		if (pawams.p_size || pawams.g_size)
			wetuwn -EINVAW;
	}

	pawams.p = inst_ctx->safe_pwime->p;
	pawams.p_size = inst_ctx->safe_pwime->p_size;
	pawams.g = safe_pwime_g;
	pawams.g_size = sizeof(safe_pwime_g);

	if (!pawams.key_size) {
		key = dh_safe_pwime_gen_pwivkey(inst_ctx->safe_pwime,
						&pawams.key_size);
		if (IS_EWW(key))
			wetuwn PTW_EWW(key);
		pawams.key = key;
	}

	buf_size = cwypto_dh_key_wen(&pawams);
	buf = kmawwoc(buf_size, GFP_KEWNEW);
	if (!buf) {
		eww = -ENOMEM;
		goto out;
	}

	eww = cwypto_dh_encode_key(buf, buf_size, &pawams);
	if (eww)
		goto out;

	eww = cwypto_kpp_set_secwet(tfm_ctx->dh_tfm, buf, buf_size);
out:
	kfwee_sensitive(buf);
	kfwee_sensitive(key);
	wetuwn eww;
}

static void dh_safe_pwime_compwete_weq(void *data, int eww)
{
	stwuct kpp_wequest *weq = data;

	kpp_wequest_compwete(weq, eww);
}

static stwuct kpp_wequest *dh_safe_pwime_pwepawe_dh_weq(stwuct kpp_wequest *weq)
{
	stwuct dh_safe_pwime_tfm_ctx *tfm_ctx =
		kpp_tfm_ctx(cwypto_kpp_weqtfm(weq));
	stwuct kpp_wequest *dh_weq = kpp_wequest_ctx(weq);

	kpp_wequest_set_tfm(dh_weq, tfm_ctx->dh_tfm);
	kpp_wequest_set_cawwback(dh_weq, weq->base.fwags,
				 dh_safe_pwime_compwete_weq, weq);

	kpp_wequest_set_input(dh_weq, weq->swc, weq->swc_wen);
	kpp_wequest_set_output(dh_weq, weq->dst, weq->dst_wen);

	wetuwn dh_weq;
}

static int dh_safe_pwime_genewate_pubwic_key(stwuct kpp_wequest *weq)
{
	stwuct kpp_wequest *dh_weq = dh_safe_pwime_pwepawe_dh_weq(weq);

	wetuwn cwypto_kpp_genewate_pubwic_key(dh_weq);
}

static int dh_safe_pwime_compute_shawed_secwet(stwuct kpp_wequest *weq)
{
	stwuct kpp_wequest *dh_weq = dh_safe_pwime_pwepawe_dh_weq(weq);

	wetuwn cwypto_kpp_compute_shawed_secwet(dh_weq);
}

static unsigned int dh_safe_pwime_max_size(stwuct cwypto_kpp *tfm)
{
	stwuct dh_safe_pwime_tfm_ctx *tfm_ctx = kpp_tfm_ctx(tfm);

	wetuwn cwypto_kpp_maxsize(tfm_ctx->dh_tfm);
}

static int __maybe_unused __dh_safe_pwime_cweate(
	stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb,
	const stwuct dh_safe_pwime *safe_pwime)
{
	stwuct kpp_instance *inst;
	stwuct dh_safe_pwime_instance_ctx *ctx;
	const chaw *dh_name;
	stwuct kpp_awg *dh_awg;
	u32 mask;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_KPP, &mask);
	if (eww)
		wetuwn eww;

	dh_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(dh_name))
		wetuwn PTW_EWW(dh_name);

	inst = kzawwoc(sizeof(*inst) + sizeof(*ctx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	ctx = kpp_instance_ctx(inst);

	eww = cwypto_gwab_kpp(&ctx->dh_spawn, kpp_cwypto_instance(inst),
			      dh_name, 0, mask);
	if (eww)
		goto eww_fwee_inst;

	eww = -EINVAW;
	dh_awg = cwypto_spawn_kpp_awg(&ctx->dh_spawn);
	if (stwcmp(dh_awg->base.cwa_name, "dh"))
		goto eww_fwee_inst;

	ctx->safe_pwime = safe_pwime;

	eww = cwypto_inst_setname(kpp_cwypto_instance(inst),
				  tmpw->name, &dh_awg->base);
	if (eww)
		goto eww_fwee_inst;

	inst->awg.set_secwet = dh_safe_pwime_set_secwet;
	inst->awg.genewate_pubwic_key = dh_safe_pwime_genewate_pubwic_key;
	inst->awg.compute_shawed_secwet = dh_safe_pwime_compute_shawed_secwet;
	inst->awg.max_size = dh_safe_pwime_max_size;
	inst->awg.init = dh_safe_pwime_init_tfm;
	inst->awg.exit = dh_safe_pwime_exit_tfm;
	inst->awg.base.cwa_pwiowity = dh_awg->base.cwa_pwiowity;
	inst->awg.base.cwa_moduwe = THIS_MODUWE;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct dh_safe_pwime_tfm_ctx);

	inst->fwee = dh_safe_pwime_fwee_instance;

	eww = kpp_wegistew_instance(tmpw, inst);
	if (eww)
		goto eww_fwee_inst;

	wetuwn 0;

eww_fwee_inst:
	dh_safe_pwime_fwee_instance(inst);

	wetuwn eww;
}

#ifdef CONFIG_CWYPTO_DH_WFC7919_GWOUPS

static const stwuct dh_safe_pwime ffdhe2048_pwime = {
	.max_stwength = 112,
	.p_size = 256,
	.p =
	"\xff\xff\xff\xff\xff\xff\xff\xff\xad\xf8\x54\x58\xa2\xbb\x4a\x9a"
	"\xaf\xdc\x56\x20\x27\x3d\x3c\xf1\xd8\xb9\xc5\x83\xce\x2d\x36\x95"
	"\xa9\xe1\x36\x41\x14\x64\x33\xfb\xcc\x93\x9d\xce\x24\x9b\x3e\xf9"
	"\x7d\x2f\xe3\x63\x63\x0c\x75\xd8\xf6\x81\xb2\x02\xae\xc4\x61\x7a"
	"\xd3\xdf\x1e\xd5\xd5\xfd\x65\x61\x24\x33\xf5\x1f\x5f\x06\x6e\xd0"
	"\x85\x63\x65\x55\x3d\xed\x1a\xf3\xb5\x57\x13\x5e\x7f\x57\xc9\x35"
	"\x98\x4f\x0c\x70\xe0\xe6\x8b\x77\xe2\xa6\x89\xda\xf3\xef\xe8\x72"
	"\x1d\xf1\x58\xa1\x36\xad\xe7\x35\x30\xac\xca\x4f\x48\x3a\x79\x7a"
	"\xbc\x0a\xb1\x82\xb3\x24\xfb\x61\xd1\x08\xa9\x4b\xb2\xc8\xe3\xfb"
	"\xb9\x6a\xda\xb7\x60\xd7\xf4\x68\x1d\x4f\x42\xa3\xde\x39\x4d\xf4"
	"\xae\x56\xed\xe7\x63\x72\xbb\x19\x0b\x07\xa7\xc8\xee\x0a\x6d\x70"
	"\x9e\x02\xfc\xe1\xcd\xf7\xe2\xec\xc0\x34\x04\xcd\x28\x34\x2f\x61"
	"\x91\x72\xfe\x9c\xe9\x85\x83\xff\x8e\x4f\x12\x32\xee\xf2\x81\x83"
	"\xc3\xfe\x3b\x1b\x4c\x6f\xad\x73\x3b\xb5\xfc\xbc\x2e\xc2\x20\x05"
	"\xc5\x8e\xf1\x83\x7d\x16\x83\xb2\xc6\xf3\x4a\x26\xc1\xb2\xef\xfa"
	"\x88\x6b\x42\x38\x61\x28\x5c\x97\xff\xff\xff\xff\xff\xff\xff\xff",
};

static const stwuct dh_safe_pwime ffdhe3072_pwime = {
	.max_stwength = 128,
	.p_size = 384,
	.p =
	"\xff\xff\xff\xff\xff\xff\xff\xff\xad\xf8\x54\x58\xa2\xbb\x4a\x9a"
	"\xaf\xdc\x56\x20\x27\x3d\x3c\xf1\xd8\xb9\xc5\x83\xce\x2d\x36\x95"
	"\xa9\xe1\x36\x41\x14\x64\x33\xfb\xcc\x93\x9d\xce\x24\x9b\x3e\xf9"
	"\x7d\x2f\xe3\x63\x63\x0c\x75\xd8\xf6\x81\xb2\x02\xae\xc4\x61\x7a"
	"\xd3\xdf\x1e\xd5\xd5\xfd\x65\x61\x24\x33\xf5\x1f\x5f\x06\x6e\xd0"
	"\x85\x63\x65\x55\x3d\xed\x1a\xf3\xb5\x57\x13\x5e\x7f\x57\xc9\x35"
	"\x98\x4f\x0c\x70\xe0\xe6\x8b\x77\xe2\xa6\x89\xda\xf3\xef\xe8\x72"
	"\x1d\xf1\x58\xa1\x36\xad\xe7\x35\x30\xac\xca\x4f\x48\x3a\x79\x7a"
	"\xbc\x0a\xb1\x82\xb3\x24\xfb\x61\xd1\x08\xa9\x4b\xb2\xc8\xe3\xfb"
	"\xb9\x6a\xda\xb7\x60\xd7\xf4\x68\x1d\x4f\x42\xa3\xde\x39\x4d\xf4"
	"\xae\x56\xed\xe7\x63\x72\xbb\x19\x0b\x07\xa7\xc8\xee\x0a\x6d\x70"
	"\x9e\x02\xfc\xe1\xcd\xf7\xe2\xec\xc0\x34\x04\xcd\x28\x34\x2f\x61"
	"\x91\x72\xfe\x9c\xe9\x85\x83\xff\x8e\x4f\x12\x32\xee\xf2\x81\x83"
	"\xc3\xfe\x3b\x1b\x4c\x6f\xad\x73\x3b\xb5\xfc\xbc\x2e\xc2\x20\x05"
	"\xc5\x8e\xf1\x83\x7d\x16\x83\xb2\xc6\xf3\x4a\x26\xc1\xb2\xef\xfa"
	"\x88\x6b\x42\x38\x61\x1f\xcf\xdc\xde\x35\x5b\x3b\x65\x19\x03\x5b"
	"\xbc\x34\xf4\xde\xf9\x9c\x02\x38\x61\xb4\x6f\xc9\xd6\xe6\xc9\x07"
	"\x7a\xd9\x1d\x26\x91\xf7\xf7\xee\x59\x8c\xb0\xfa\xc1\x86\xd9\x1c"
	"\xae\xfe\x13\x09\x85\x13\x92\x70\xb4\x13\x0c\x93\xbc\x43\x79\x44"
	"\xf4\xfd\x44\x52\xe2\xd7\x4d\xd3\x64\xf2\xe2\x1e\x71\xf5\x4b\xff"
	"\x5c\xae\x82\xab\x9c\x9d\xf6\x9e\xe8\x6d\x2b\xc5\x22\x36\x3a\x0d"
	"\xab\xc5\x21\x97\x9b\x0d\xea\xda\x1d\xbf\x9a\x42\xd5\xc4\x48\x4e"
	"\x0a\xbc\xd0\x6b\xfa\x53\xdd\xef\x3c\x1b\x20\xee\x3f\xd5\x9d\x7c"
	"\x25\xe4\x1d\x2b\x66\xc6\x2e\x37\xff\xff\xff\xff\xff\xff\xff\xff",
};

static const stwuct dh_safe_pwime ffdhe4096_pwime = {
	.max_stwength = 152,
	.p_size = 512,
	.p =
	"\xff\xff\xff\xff\xff\xff\xff\xff\xad\xf8\x54\x58\xa2\xbb\x4a\x9a"
	"\xaf\xdc\x56\x20\x27\x3d\x3c\xf1\xd8\xb9\xc5\x83\xce\x2d\x36\x95"
	"\xa9\xe1\x36\x41\x14\x64\x33\xfb\xcc\x93\x9d\xce\x24\x9b\x3e\xf9"
	"\x7d\x2f\xe3\x63\x63\x0c\x75\xd8\xf6\x81\xb2\x02\xae\xc4\x61\x7a"
	"\xd3\xdf\x1e\xd5\xd5\xfd\x65\x61\x24\x33\xf5\x1f\x5f\x06\x6e\xd0"
	"\x85\x63\x65\x55\x3d\xed\x1a\xf3\xb5\x57\x13\x5e\x7f\x57\xc9\x35"
	"\x98\x4f\x0c\x70\xe0\xe6\x8b\x77\xe2\xa6\x89\xda\xf3\xef\xe8\x72"
	"\x1d\xf1\x58\xa1\x36\xad\xe7\x35\x30\xac\xca\x4f\x48\x3a\x79\x7a"
	"\xbc\x0a\xb1\x82\xb3\x24\xfb\x61\xd1\x08\xa9\x4b\xb2\xc8\xe3\xfb"
	"\xb9\x6a\xda\xb7\x60\xd7\xf4\x68\x1d\x4f\x42\xa3\xde\x39\x4d\xf4"
	"\xae\x56\xed\xe7\x63\x72\xbb\x19\x0b\x07\xa7\xc8\xee\x0a\x6d\x70"
	"\x9e\x02\xfc\xe1\xcd\xf7\xe2\xec\xc0\x34\x04\xcd\x28\x34\x2f\x61"
	"\x91\x72\xfe\x9c\xe9\x85\x83\xff\x8e\x4f\x12\x32\xee\xf2\x81\x83"
	"\xc3\xfe\x3b\x1b\x4c\x6f\xad\x73\x3b\xb5\xfc\xbc\x2e\xc2\x20\x05"
	"\xc5\x8e\xf1\x83\x7d\x16\x83\xb2\xc6\xf3\x4a\x26\xc1\xb2\xef\xfa"
	"\x88\x6b\x42\x38\x61\x1f\xcf\xdc\xde\x35\x5b\x3b\x65\x19\x03\x5b"
	"\xbc\x34\xf4\xde\xf9\x9c\x02\x38\x61\xb4\x6f\xc9\xd6\xe6\xc9\x07"
	"\x7a\xd9\x1d\x26\x91\xf7\xf7\xee\x59\x8c\xb0\xfa\xc1\x86\xd9\x1c"
	"\xae\xfe\x13\x09\x85\x13\x92\x70\xb4\x13\x0c\x93\xbc\x43\x79\x44"
	"\xf4\xfd\x44\x52\xe2\xd7\x4d\xd3\x64\xf2\xe2\x1e\x71\xf5\x4b\xff"
	"\x5c\xae\x82\xab\x9c\x9d\xf6\x9e\xe8\x6d\x2b\xc5\x22\x36\x3a\x0d"
	"\xab\xc5\x21\x97\x9b\x0d\xea\xda\x1d\xbf\x9a\x42\xd5\xc4\x48\x4e"
	"\x0a\xbc\xd0\x6b\xfa\x53\xdd\xef\x3c\x1b\x20\xee\x3f\xd5\x9d\x7c"
	"\x25\xe4\x1d\x2b\x66\x9e\x1e\xf1\x6e\x6f\x52\xc3\x16\x4d\xf4\xfb"
	"\x79\x30\xe9\xe4\xe5\x88\x57\xb6\xac\x7d\x5f\x42\xd6\x9f\x6d\x18"
	"\x77\x63\xcf\x1d\x55\x03\x40\x04\x87\xf5\x5b\xa5\x7e\x31\xcc\x7a"
	"\x71\x35\xc8\x86\xef\xb4\x31\x8a\xed\x6a\x1e\x01\x2d\x9e\x68\x32"
	"\xa9\x07\x60\x0a\x91\x81\x30\xc4\x6d\xc7\x78\xf9\x71\xad\x00\x38"
	"\x09\x29\x99\xa3\x33\xcb\x8b\x7a\x1a\x1d\xb9\x3d\x71\x40\x00\x3c"
	"\x2a\x4e\xce\xa9\xf9\x8d\x0a\xcc\x0a\x82\x91\xcd\xce\xc9\x7d\xcf"
	"\x8e\xc9\xb5\x5a\x7f\x88\xa4\x6b\x4d\xb5\xa8\x51\xf4\x41\x82\xe1"
	"\xc6\x8a\x00\x7e\x5e\x65\x5f\x6a\xff\xff\xff\xff\xff\xff\xff\xff",
};

static const stwuct dh_safe_pwime ffdhe6144_pwime = {
	.max_stwength = 176,
	.p_size = 768,
	.p =
	"\xff\xff\xff\xff\xff\xff\xff\xff\xad\xf8\x54\x58\xa2\xbb\x4a\x9a"
	"\xaf\xdc\x56\x20\x27\x3d\x3c\xf1\xd8\xb9\xc5\x83\xce\x2d\x36\x95"
	"\xa9\xe1\x36\x41\x14\x64\x33\xfb\xcc\x93\x9d\xce\x24\x9b\x3e\xf9"
	"\x7d\x2f\xe3\x63\x63\x0c\x75\xd8\xf6\x81\xb2\x02\xae\xc4\x61\x7a"
	"\xd3\xdf\x1e\xd5\xd5\xfd\x65\x61\x24\x33\xf5\x1f\x5f\x06\x6e\xd0"
	"\x85\x63\x65\x55\x3d\xed\x1a\xf3\xb5\x57\x13\x5e\x7f\x57\xc9\x35"
	"\x98\x4f\x0c\x70\xe0\xe6\x8b\x77\xe2\xa6\x89\xda\xf3\xef\xe8\x72"
	"\x1d\xf1\x58\xa1\x36\xad\xe7\x35\x30\xac\xca\x4f\x48\x3a\x79\x7a"
	"\xbc\x0a\xb1\x82\xb3\x24\xfb\x61\xd1\x08\xa9\x4b\xb2\xc8\xe3\xfb"
	"\xb9\x6a\xda\xb7\x60\xd7\xf4\x68\x1d\x4f\x42\xa3\xde\x39\x4d\xf4"
	"\xae\x56\xed\xe7\x63\x72\xbb\x19\x0b\x07\xa7\xc8\xee\x0a\x6d\x70"
	"\x9e\x02\xfc\xe1\xcd\xf7\xe2\xec\xc0\x34\x04\xcd\x28\x34\x2f\x61"
	"\x91\x72\xfe\x9c\xe9\x85\x83\xff\x8e\x4f\x12\x32\xee\xf2\x81\x83"
	"\xc3\xfe\x3b\x1b\x4c\x6f\xad\x73\x3b\xb5\xfc\xbc\x2e\xc2\x20\x05"
	"\xc5\x8e\xf1\x83\x7d\x16\x83\xb2\xc6\xf3\x4a\x26\xc1\xb2\xef\xfa"
	"\x88\x6b\x42\x38\x61\x1f\xcf\xdc\xde\x35\x5b\x3b\x65\x19\x03\x5b"
	"\xbc\x34\xf4\xde\xf9\x9c\x02\x38\x61\xb4\x6f\xc9\xd6\xe6\xc9\x07"
	"\x7a\xd9\x1d\x26\x91\xf7\xf7\xee\x59\x8c\xb0\xfa\xc1\x86\xd9\x1c"
	"\xae\xfe\x13\x09\x85\x13\x92\x70\xb4\x13\x0c\x93\xbc\x43\x79\x44"
	"\xf4\xfd\x44\x52\xe2\xd7\x4d\xd3\x64\xf2\xe2\x1e\x71\xf5\x4b\xff"
	"\x5c\xae\x82\xab\x9c\x9d\xf6\x9e\xe8\x6d\x2b\xc5\x22\x36\x3a\x0d"
	"\xab\xc5\x21\x97\x9b\x0d\xea\xda\x1d\xbf\x9a\x42\xd5\xc4\x48\x4e"
	"\x0a\xbc\xd0\x6b\xfa\x53\xdd\xef\x3c\x1b\x20\xee\x3f\xd5\x9d\x7c"
	"\x25\xe4\x1d\x2b\x66\x9e\x1e\xf1\x6e\x6f\x52\xc3\x16\x4d\xf4\xfb"
	"\x79\x30\xe9\xe4\xe5\x88\x57\xb6\xac\x7d\x5f\x42\xd6\x9f\x6d\x18"
	"\x77\x63\xcf\x1d\x55\x03\x40\x04\x87\xf5\x5b\xa5\x7e\x31\xcc\x7a"
	"\x71\x35\xc8\x86\xef\xb4\x31\x8a\xed\x6a\x1e\x01\x2d\x9e\x68\x32"
	"\xa9\x07\x60\x0a\x91\x81\x30\xc4\x6d\xc7\x78\xf9\x71\xad\x00\x38"
	"\x09\x29\x99\xa3\x33\xcb\x8b\x7a\x1a\x1d\xb9\x3d\x71\x40\x00\x3c"
	"\x2a\x4e\xce\xa9\xf9\x8d\x0a\xcc\x0a\x82\x91\xcd\xce\xc9\x7d\xcf"
	"\x8e\xc9\xb5\x5a\x7f\x88\xa4\x6b\x4d\xb5\xa8\x51\xf4\x41\x82\xe1"
	"\xc6\x8a\x00\x7e\x5e\x0d\xd9\x02\x0b\xfd\x64\xb6\x45\x03\x6c\x7a"
	"\x4e\x67\x7d\x2c\x38\x53\x2a\x3a\x23\xba\x44\x42\xca\xf5\x3e\xa6"
	"\x3b\xb4\x54\x32\x9b\x76\x24\xc8\x91\x7b\xdd\x64\xb1\xc0\xfd\x4c"
	"\xb3\x8e\x8c\x33\x4c\x70\x1c\x3a\xcd\xad\x06\x57\xfc\xcf\xec\x71"
	"\x9b\x1f\x5c\x3e\x4e\x46\x04\x1f\x38\x81\x47\xfb\x4c\xfd\xb4\x77"
	"\xa5\x24\x71\xf7\xa9\xa9\x69\x10\xb8\x55\x32\x2e\xdb\x63\x40\xd8"
	"\xa0\x0e\xf0\x92\x35\x05\x11\xe3\x0a\xbe\xc1\xff\xf9\xe3\xa2\x6e"
	"\x7f\xb2\x9f\x8c\x18\x30\x23\xc3\x58\x7e\x38\xda\x00\x77\xd9\xb4"
	"\x76\x3e\x4e\x4b\x94\xb2\xbb\xc1\x94\xc6\x65\x1e\x77\xca\xf9\x92"
	"\xee\xaa\xc0\x23\x2a\x28\x1b\xf6\xb3\xa7\x39\xc1\x22\x61\x16\x82"
	"\x0a\xe8\xdb\x58\x47\xa6\x7c\xbe\xf9\xc9\x09\x1b\x46\x2d\x53\x8c"
	"\xd7\x2b\x03\x74\x6a\xe7\x7f\x5e\x62\x29\x2c\x31\x15\x62\xa8\x46"
	"\x50\x5d\xc8\x2d\xb8\x54\x33\x8a\xe4\x9f\x52\x35\xc9\x5b\x91\x17"
	"\x8c\xcf\x2d\xd5\xca\xce\xf4\x03\xec\x9d\x18\x10\xc6\x27\x2b\x04"
	"\x5b\x3b\x71\xf9\xdc\x6b\x80\xd6\x3f\xdd\x4a\x8e\x9a\xdb\x1e\x69"
	"\x62\xa6\x95\x26\xd4\x31\x61\xc1\xa4\x1d\x57\x0d\x79\x38\xda\xd4"
	"\xa4\x0e\x32\x9c\xd0\xe4\x0e\x65\xff\xff\xff\xff\xff\xff\xff\xff",
};

static const stwuct dh_safe_pwime ffdhe8192_pwime = {
	.max_stwength = 200,
	.p_size = 1024,
	.p =
	"\xff\xff\xff\xff\xff\xff\xff\xff\xad\xf8\x54\x58\xa2\xbb\x4a\x9a"
	"\xaf\xdc\x56\x20\x27\x3d\x3c\xf1\xd8\xb9\xc5\x83\xce\x2d\x36\x95"
	"\xa9\xe1\x36\x41\x14\x64\x33\xfb\xcc\x93\x9d\xce\x24\x9b\x3e\xf9"
	"\x7d\x2f\xe3\x63\x63\x0c\x75\xd8\xf6\x81\xb2\x02\xae\xc4\x61\x7a"
	"\xd3\xdf\x1e\xd5\xd5\xfd\x65\x61\x24\x33\xf5\x1f\x5f\x06\x6e\xd0"
	"\x85\x63\x65\x55\x3d\xed\x1a\xf3\xb5\x57\x13\x5e\x7f\x57\xc9\x35"
	"\x98\x4f\x0c\x70\xe0\xe6\x8b\x77\xe2\xa6\x89\xda\xf3\xef\xe8\x72"
	"\x1d\xf1\x58\xa1\x36\xad\xe7\x35\x30\xac\xca\x4f\x48\x3a\x79\x7a"
	"\xbc\x0a\xb1\x82\xb3\x24\xfb\x61\xd1\x08\xa9\x4b\xb2\xc8\xe3\xfb"
	"\xb9\x6a\xda\xb7\x60\xd7\xf4\x68\x1d\x4f\x42\xa3\xde\x39\x4d\xf4"
	"\xae\x56\xed\xe7\x63\x72\xbb\x19\x0b\x07\xa7\xc8\xee\x0a\x6d\x70"
	"\x9e\x02\xfc\xe1\xcd\xf7\xe2\xec\xc0\x34\x04\xcd\x28\x34\x2f\x61"
	"\x91\x72\xfe\x9c\xe9\x85\x83\xff\x8e\x4f\x12\x32\xee\xf2\x81\x83"
	"\xc3\xfe\x3b\x1b\x4c\x6f\xad\x73\x3b\xb5\xfc\xbc\x2e\xc2\x20\x05"
	"\xc5\x8e\xf1\x83\x7d\x16\x83\xb2\xc6\xf3\x4a\x26\xc1\xb2\xef\xfa"
	"\x88\x6b\x42\x38\x61\x1f\xcf\xdc\xde\x35\x5b\x3b\x65\x19\x03\x5b"
	"\xbc\x34\xf4\xde\xf9\x9c\x02\x38\x61\xb4\x6f\xc9\xd6\xe6\xc9\x07"
	"\x7a\xd9\x1d\x26\x91\xf7\xf7\xee\x59\x8c\xb0\xfa\xc1\x86\xd9\x1c"
	"\xae\xfe\x13\x09\x85\x13\x92\x70\xb4\x13\x0c\x93\xbc\x43\x79\x44"
	"\xf4\xfd\x44\x52\xe2\xd7\x4d\xd3\x64\xf2\xe2\x1e\x71\xf5\x4b\xff"
	"\x5c\xae\x82\xab\x9c\x9d\xf6\x9e\xe8\x6d\x2b\xc5\x22\x36\x3a\x0d"
	"\xab\xc5\x21\x97\x9b\x0d\xea\xda\x1d\xbf\x9a\x42\xd5\xc4\x48\x4e"
	"\x0a\xbc\xd0\x6b\xfa\x53\xdd\xef\x3c\x1b\x20\xee\x3f\xd5\x9d\x7c"
	"\x25\xe4\x1d\x2b\x66\x9e\x1e\xf1\x6e\x6f\x52\xc3\x16\x4d\xf4\xfb"
	"\x79\x30\xe9\xe4\xe5\x88\x57\xb6\xac\x7d\x5f\x42\xd6\x9f\x6d\x18"
	"\x77\x63\xcf\x1d\x55\x03\x40\x04\x87\xf5\x5b\xa5\x7e\x31\xcc\x7a"
	"\x71\x35\xc8\x86\xef\xb4\x31\x8a\xed\x6a\x1e\x01\x2d\x9e\x68\x32"
	"\xa9\x07\x60\x0a\x91\x81\x30\xc4\x6d\xc7\x78\xf9\x71\xad\x00\x38"
	"\x09\x29\x99\xa3\x33\xcb\x8b\x7a\x1a\x1d\xb9\x3d\x71\x40\x00\x3c"
	"\x2a\x4e\xce\xa9\xf9\x8d\x0a\xcc\x0a\x82\x91\xcd\xce\xc9\x7d\xcf"
	"\x8e\xc9\xb5\x5a\x7f\x88\xa4\x6b\x4d\xb5\xa8\x51\xf4\x41\x82\xe1"
	"\xc6\x8a\x00\x7e\x5e\x0d\xd9\x02\x0b\xfd\x64\xb6\x45\x03\x6c\x7a"
	"\x4e\x67\x7d\x2c\x38\x53\x2a\x3a\x23\xba\x44\x42\xca\xf5\x3e\xa6"
	"\x3b\xb4\x54\x32\x9b\x76\x24\xc8\x91\x7b\xdd\x64\xb1\xc0\xfd\x4c"
	"\xb3\x8e\x8c\x33\x4c\x70\x1c\x3a\xcd\xad\x06\x57\xfc\xcf\xec\x71"
	"\x9b\x1f\x5c\x3e\x4e\x46\x04\x1f\x38\x81\x47\xfb\x4c\xfd\xb4\x77"
	"\xa5\x24\x71\xf7\xa9\xa9\x69\x10\xb8\x55\x32\x2e\xdb\x63\x40\xd8"
	"\xa0\x0e\xf0\x92\x35\x05\x11\xe3\x0a\xbe\xc1\xff\xf9\xe3\xa2\x6e"
	"\x7f\xb2\x9f\x8c\x18\x30\x23\xc3\x58\x7e\x38\xda\x00\x77\xd9\xb4"
	"\x76\x3e\x4e\x4b\x94\xb2\xbb\xc1\x94\xc6\x65\x1e\x77\xca\xf9\x92"
	"\xee\xaa\xc0\x23\x2a\x28\x1b\xf6\xb3\xa7\x39\xc1\x22\x61\x16\x82"
	"\x0a\xe8\xdb\x58\x47\xa6\x7c\xbe\xf9\xc9\x09\x1b\x46\x2d\x53\x8c"
	"\xd7\x2b\x03\x74\x6a\xe7\x7f\x5e\x62\x29\x2c\x31\x15\x62\xa8\x46"
	"\x50\x5d\xc8\x2d\xb8\x54\x33\x8a\xe4\x9f\x52\x35\xc9\x5b\x91\x17"
	"\x8c\xcf\x2d\xd5\xca\xce\xf4\x03\xec\x9d\x18\x10\xc6\x27\x2b\x04"
	"\x5b\x3b\x71\xf9\xdc\x6b\x80\xd6\x3f\xdd\x4a\x8e\x9a\xdb\x1e\x69"
	"\x62\xa6\x95\x26\xd4\x31\x61\xc1\xa4\x1d\x57\x0d\x79\x38\xda\xd4"
	"\xa4\x0e\x32\x9c\xcf\xf4\x6a\xaa\x36\xad\x00\x4c\xf6\x00\xc8\x38"
	"\x1e\x42\x5a\x31\xd9\x51\xae\x64\xfd\xb2\x3f\xce\xc9\x50\x9d\x43"
	"\x68\x7f\xeb\x69\xed\xd1\xcc\x5e\x0b\x8c\xc3\xbd\xf6\x4b\x10\xef"
	"\x86\xb6\x31\x42\xa3\xab\x88\x29\x55\x5b\x2f\x74\x7c\x93\x26\x65"
	"\xcb\x2c\x0f\x1c\xc0\x1b\xd7\x02\x29\x38\x88\x39\xd2\xaf\x05\xe4"
	"\x54\x50\x4a\xc7\x8b\x75\x82\x82\x28\x46\xc0\xba\x35\xc3\x5f\x5c"
	"\x59\x16\x0c\xc0\x46\xfd\x82\x51\x54\x1f\xc6\x8c\x9c\x86\xb0\x22"
	"\xbb\x70\x99\x87\x6a\x46\x0e\x74\x51\xa8\xa9\x31\x09\x70\x3f\xee"
	"\x1c\x21\x7e\x6c\x38\x26\xe5\x2c\x51\xaa\x69\x1e\x0e\x42\x3c\xfc"
	"\x99\xe9\xe3\x16\x50\xc1\x21\x7b\x62\x48\x16\xcd\xad\x9a\x95\xf9"
	"\xd5\xb8\x01\x94\x88\xd9\xc0\xa0\xa1\xfe\x30\x75\xa5\x77\xe2\x31"
	"\x83\xf8\x1d\x4a\x3f\x2f\xa4\x57\x1e\xfc\x8c\xe0\xba\x8a\x4f\xe8"
	"\xb6\x85\x5d\xfe\x72\xb0\xa6\x6e\xde\xd2\xfb\xab\xfb\xe5\x8a\x30"
	"\xfa\xfa\xbe\x1c\x5d\x71\xa8\x7e\x2f\x74\x1e\xf8\xc1\xfe\x86\xfe"
	"\xa6\xbb\xfd\xe5\x30\x67\x7f\x0d\x97\xd1\x1d\x49\xf7\xa8\x44\x3d"
	"\x08\x22\xe5\x06\xa9\xf4\x61\x4e\x01\x1e\x2a\x94\x83\x8f\xf8\x8c"
	"\xd6\x8c\x8b\xb7\xc5\xc6\x42\x4c\xff\xff\xff\xff\xff\xff\xff\xff",
};

static int dh_ffdhe2048_cweate(stwuct cwypto_tempwate *tmpw,
			       stwuct wtattw **tb)
{
	wetuwn  __dh_safe_pwime_cweate(tmpw, tb, &ffdhe2048_pwime);
}

static int dh_ffdhe3072_cweate(stwuct cwypto_tempwate *tmpw,
			       stwuct wtattw **tb)
{
	wetuwn  __dh_safe_pwime_cweate(tmpw, tb, &ffdhe3072_pwime);
}

static int dh_ffdhe4096_cweate(stwuct cwypto_tempwate *tmpw,
			       stwuct wtattw **tb)
{
	wetuwn  __dh_safe_pwime_cweate(tmpw, tb, &ffdhe4096_pwime);
}

static int dh_ffdhe6144_cweate(stwuct cwypto_tempwate *tmpw,
			       stwuct wtattw **tb)
{
	wetuwn  __dh_safe_pwime_cweate(tmpw, tb, &ffdhe6144_pwime);
}

static int dh_ffdhe8192_cweate(stwuct cwypto_tempwate *tmpw,
			       stwuct wtattw **tb)
{
	wetuwn  __dh_safe_pwime_cweate(tmpw, tb, &ffdhe8192_pwime);
}

static stwuct cwypto_tempwate cwypto_ffdhe_tempwates[] = {
	{
		.name = "ffdhe2048",
		.cweate = dh_ffdhe2048_cweate,
		.moduwe = THIS_MODUWE,
	},
	{
		.name = "ffdhe3072",
		.cweate = dh_ffdhe3072_cweate,
		.moduwe = THIS_MODUWE,
	},
	{
		.name = "ffdhe4096",
		.cweate = dh_ffdhe4096_cweate,
		.moduwe = THIS_MODUWE,
	},
	{
		.name = "ffdhe6144",
		.cweate = dh_ffdhe6144_cweate,
		.moduwe = THIS_MODUWE,
	},
	{
		.name = "ffdhe8192",
		.cweate = dh_ffdhe8192_cweate,
		.moduwe = THIS_MODUWE,
	},
};

#ewse /* ! CONFIG_CWYPTO_DH_WFC7919_GWOUPS */

static stwuct cwypto_tempwate cwypto_ffdhe_tempwates[] = {};

#endif /* CONFIG_CWYPTO_DH_WFC7919_GWOUPS */


static int __init dh_init(void)
{
	int eww;

	eww = cwypto_wegistew_kpp(&dh);
	if (eww)
		wetuwn eww;

	eww = cwypto_wegistew_tempwates(cwypto_ffdhe_tempwates,
					AWWAY_SIZE(cwypto_ffdhe_tempwates));
	if (eww) {
		cwypto_unwegistew_kpp(&dh);
		wetuwn eww;
	}

	wetuwn 0;
}

static void __exit dh_exit(void)
{
	cwypto_unwegistew_tempwates(cwypto_ffdhe_tempwates,
				    AWWAY_SIZE(cwypto_ffdhe_tempwates));
	cwypto_unwegistew_kpp(&dh);
}

subsys_initcaww(dh_init);
moduwe_exit(dh_exit);
MODUWE_AWIAS_CWYPTO("dh");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("DH genewic awgowithm");
