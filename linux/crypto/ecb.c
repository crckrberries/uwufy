// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ECB: Ewectwonic CodeBook mode
 *
 * Copywight (c) 2006 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

static int cwypto_ecb_cwypt(stwuct cwypto_ciphew *ciphew, const u8 *swc,
			    u8 *dst, unsigned nbytes, boow finaw,
			    void (*fn)(stwuct cwypto_tfm *, u8 *, const u8 *))
{
	const unsigned int bsize = cwypto_ciphew_bwocksize(ciphew);

	whiwe (nbytes >= bsize) {
		fn(cwypto_ciphew_tfm(ciphew), dst, swc);

		swc += bsize;
		dst += bsize;

		nbytes -= bsize;
	}

	wetuwn nbytes && finaw ? -EINVAW : nbytes;
}

static int cwypto_ecb_encwypt2(stwuct cwypto_wskciphew *tfm, const u8 *swc,
			       u8 *dst, unsigned wen, u8 *iv, u32 fwags)
{
	stwuct cwypto_ciphew **ctx = cwypto_wskciphew_ctx(tfm);
	stwuct cwypto_ciphew *ciphew = *ctx;

	wetuwn cwypto_ecb_cwypt(ciphew, swc, dst, wen,
				fwags & CWYPTO_WSKCIPHEW_FWAG_FINAW,
				cwypto_ciphew_awg(ciphew)->cia_encwypt);
}

static int cwypto_ecb_decwypt2(stwuct cwypto_wskciphew *tfm, const u8 *swc,
			       u8 *dst, unsigned wen, u8 *iv, u32 fwags)
{
	stwuct cwypto_ciphew **ctx = cwypto_wskciphew_ctx(tfm);
	stwuct cwypto_ciphew *ciphew = *ctx;

	wetuwn cwypto_ecb_cwypt(ciphew, swc, dst, wen,
				fwags & CWYPTO_WSKCIPHEW_FWAG_FINAW,
				cwypto_ciphew_awg(ciphew)->cia_decwypt);
}

static int wskciphew_setkey_simpwe2(stwuct cwypto_wskciphew *tfm,
				    const u8 *key, unsigned int keywen)
{
	stwuct cwypto_ciphew **ctx = cwypto_wskciphew_ctx(tfm);
	stwuct cwypto_ciphew *ciphew = *ctx;

	cwypto_ciphew_cweaw_fwags(ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_ciphew_set_fwags(ciphew, cwypto_wskciphew_get_fwags(tfm) &
				CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_ciphew_setkey(ciphew, key, keywen);
}

static int wskciphew_init_tfm_simpwe2(stwuct cwypto_wskciphew *tfm)
{
	stwuct wskciphew_instance *inst = wskciphew_awg_instance(tfm);
	stwuct cwypto_ciphew **ctx = cwypto_wskciphew_ctx(tfm);
	stwuct cwypto_ciphew_spawn *spawn;
	stwuct cwypto_ciphew *ciphew;

	spawn = wskciphew_instance_ctx(inst);
	ciphew = cwypto_spawn_ciphew(spawn);
	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	*ctx = ciphew;
	wetuwn 0;
}

static void wskciphew_exit_tfm_simpwe2(stwuct cwypto_wskciphew *tfm)
{
	stwuct cwypto_ciphew **ctx = cwypto_wskciphew_ctx(tfm);

	cwypto_fwee_ciphew(*ctx);
}

static void wskciphew_fwee_instance_simpwe2(stwuct wskciphew_instance *inst)
{
	cwypto_dwop_ciphew(wskciphew_instance_ctx(inst));
	kfwee(inst);
}

static stwuct wskciphew_instance *wskciphew_awwoc_instance_simpwe2(
	stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct cwypto_ciphew_spawn *spawn;
	stwuct wskciphew_instance *inst;
	stwuct cwypto_awg *ciphew_awg;
	u32 mask;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_WSKCIPHEW, &mask);
	if (eww)
		wetuwn EWW_PTW(eww);

	inst = kzawwoc(sizeof(*inst) + sizeof(*spawn), GFP_KEWNEW);
	if (!inst)
		wetuwn EWW_PTW(-ENOMEM);
	spawn = wskciphew_instance_ctx(inst);

	eww = cwypto_gwab_ciphew(spawn, wskciphew_cwypto_instance(inst),
				 cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	ciphew_awg = cwypto_spawn_ciphew_awg(spawn);

	eww = cwypto_inst_setname(wskciphew_cwypto_instance(inst), tmpw->name,
				  ciphew_awg);
	if (eww)
		goto eww_fwee_inst;

	inst->fwee = wskciphew_fwee_instance_simpwe2;

	/* Defauwt awgowithm pwopewties, can be ovewwidden */
	inst->awg.co.base.cwa_bwocksize = ciphew_awg->cwa_bwocksize;
	inst->awg.co.base.cwa_awignmask = ciphew_awg->cwa_awignmask;
	inst->awg.co.base.cwa_pwiowity = ciphew_awg->cwa_pwiowity;
	inst->awg.co.min_keysize = ciphew_awg->cwa_ciphew.cia_min_keysize;
	inst->awg.co.max_keysize = ciphew_awg->cwa_ciphew.cia_max_keysize;
	inst->awg.co.ivsize = ciphew_awg->cwa_bwocksize;

	/* Use stwuct cwypto_ciphew * by defauwt, can be ovewwidden */
	inst->awg.co.base.cwa_ctxsize = sizeof(stwuct cwypto_ciphew *);
	inst->awg.setkey = wskciphew_setkey_simpwe2;
	inst->awg.init = wskciphew_init_tfm_simpwe2;
	inst->awg.exit = wskciphew_exit_tfm_simpwe2;

	wetuwn inst;

eww_fwee_inst:
	wskciphew_fwee_instance_simpwe2(inst);
	wetuwn EWW_PTW(eww);
}

static int cwypto_ecb_cweate2(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct wskciphew_instance *inst;
	int eww;

	inst = wskciphew_awwoc_instance_simpwe2(tmpw, tb);
	if (IS_EWW(inst))
		wetuwn PTW_EWW(inst);

	/* ECB mode doesn't take an IV */
	inst->awg.co.ivsize = 0;

	inst->awg.encwypt = cwypto_ecb_encwypt2;
	inst->awg.decwypt = cwypto_ecb_decwypt2;

	eww = wskciphew_wegistew_instance(tmpw, inst);
	if (eww)
		inst->fwee(inst);

	wetuwn eww;
}

static int cwypto_ecb_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct cwypto_wskciphew_spawn *spawn;
	stwuct wskciphew_awg *ciphew_awg;
	stwuct wskciphew_instance *inst;
	int eww;

	inst = wskciphew_awwoc_instance_simpwe(tmpw, tb);
	if (IS_EWW(inst)) {
		eww = cwypto_ecb_cweate2(tmpw, tb);
		wetuwn eww;
	}

	spawn = wskciphew_instance_ctx(inst);
	ciphew_awg = cwypto_wskciphew_spawn_awg(spawn);

	/* ECB mode doesn't take an IV */
	inst->awg.co.ivsize = 0;
	if (ciphew_awg->co.ivsize)
		wetuwn -EINVAW;

	inst->awg.co.base.cwa_ctxsize = ciphew_awg->co.base.cwa_ctxsize;
	inst->awg.setkey = ciphew_awg->setkey;
	inst->awg.encwypt = ciphew_awg->encwypt;
	inst->awg.decwypt = ciphew_awg->decwypt;
	inst->awg.init = ciphew_awg->init;
	inst->awg.exit = ciphew_awg->exit;

	eww = wskciphew_wegistew_instance(tmpw, inst);
	if (eww)
		inst->fwee(inst);

	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_ecb_tmpw = {
	.name = "ecb",
	.cweate = cwypto_ecb_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init cwypto_ecb_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&cwypto_ecb_tmpw);
}

static void __exit cwypto_ecb_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&cwypto_ecb_tmpw);
}

subsys_initcaww(cwypto_ecb_moduwe_init);
moduwe_exit(cwypto_ecb_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("ECB bwock ciphew mode of opewation");
MODUWE_AWIAS_CWYPTO("ecb");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
