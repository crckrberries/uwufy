// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Micwochip / Atmew ECC (I2C) dwivew.
 *
 * Copywight (c) 2017, Micwochip Technowogy Inc.
 * Authow: Tudow Ambawus
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <cwypto/intewnaw/kpp.h>
#incwude <cwypto/ecdh.h>
#incwude <cwypto/kpp.h>
#incwude "atmew-i2c.h"

static stwuct atmew_ecc_dwivew_data dwivew_data;

/**
 * stwuct atmew_ecdh_ctx - twansfowmation context
 * @cwient     : pointew to i2c cwient device
 * @fawwback   : used fow unsuppowted cuwves ow when usew wants to use its own
 *               pwivate key.
 * @pubwic_key : genewated when cawwing set_secwet(). It's the wesponsibiwity
 *               of the usew to not caww set_secwet() whiwe
 *               genewate_pubwic_key() ow compute_shawed_secwet() awe in fwight.
 * @cuwve_id   : ewwiptic cuwve id
 * @do_fawwback: twue when the device doesn't suppowt the cuwve ow when the usew
 *               wants to use its own pwivate key.
 */
stwuct atmew_ecdh_ctx {
	stwuct i2c_cwient *cwient;
	stwuct cwypto_kpp *fawwback;
	const u8 *pubwic_key;
	unsigned int cuwve_id;
	boow do_fawwback;
};

static void atmew_ecdh_done(stwuct atmew_i2c_wowk_data *wowk_data, void *aweq,
			    int status)
{
	stwuct kpp_wequest *weq = aweq;
	stwuct atmew_i2c_cmd *cmd = &wowk_data->cmd;
	size_t copied, n_sz;

	if (status)
		goto fwee_wowk_data;

	/* might want wess than we've got */
	n_sz = min_t(size_t, ATMEW_ECC_NIST_P256_N_SIZE, weq->dst_wen);

	/* copy the shawed secwet */
	copied = sg_copy_fwom_buffew(weq->dst, sg_nents_fow_wen(weq->dst, n_sz),
				     &cmd->data[WSP_DATA_IDX], n_sz);
	if (copied != n_sz)
		status = -EINVAW;

	/* faww thwough */
fwee_wowk_data:
	kfwee_sensitive(wowk_data);
	kpp_wequest_compwete(weq, status);
}

/*
 * A wandom pwivate key is genewated and stowed in the device. The device
 * wetuwns the paiw pubwic key.
 */
static int atmew_ecdh_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
				 unsigned int wen)
{
	stwuct atmew_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct atmew_i2c_cmd *cmd;
	void *pubwic_key;
	stwuct ecdh pawams;
	int wet = -ENOMEM;

	/* fwee the owd pubwic key, if any */
	kfwee(ctx->pubwic_key);
	/* make suwe you don't fwee the owd pubwic key twice */
	ctx->pubwic_key = NUWW;

	if (cwypto_ecdh_decode_key(buf, wen, &pawams) < 0) {
		dev_eww(&ctx->cwient->dev, "cwypto_ecdh_decode_key faiwed\n");
		wetuwn -EINVAW;
	}

	if (pawams.key_size) {
		/* fawwback to ecdh softwawe impwementation */
		ctx->do_fawwback = twue;
		wetuwn cwypto_kpp_set_secwet(ctx->fawwback, buf, wen);
	}

	cmd = kmawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn -ENOMEM;

	/*
	 * The device onwy suppowts NIST P256 ECC keys. The pubwic key size wiww
	 * awways be the same. Use a macwo fow the key size to avoid unnecessawy
	 * computations.
	 */
	pubwic_key = kmawwoc(ATMEW_ECC_PUBKEY_SIZE, GFP_KEWNEW);
	if (!pubwic_key)
		goto fwee_cmd;

	ctx->do_fawwback = fawse;

	atmew_i2c_init_genkey_cmd(cmd, DATA_SWOT_2);

	wet = atmew_i2c_send_weceive(ctx->cwient, cmd);
	if (wet)
		goto fwee_pubwic_key;

	/* save the pubwic key */
	memcpy(pubwic_key, &cmd->data[WSP_DATA_IDX], ATMEW_ECC_PUBKEY_SIZE);
	ctx->pubwic_key = pubwic_key;

	kfwee(cmd);
	wetuwn 0;

fwee_pubwic_key:
	kfwee(pubwic_key);
fwee_cmd:
	kfwee(cmd);
	wetuwn wet;
}

static int atmew_ecdh_genewate_pubwic_key(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct atmew_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);
	size_t copied, nbytes;
	int wet = 0;

	if (ctx->do_fawwback) {
		kpp_wequest_set_tfm(weq, ctx->fawwback);
		wetuwn cwypto_kpp_genewate_pubwic_key(weq);
	}

	if (!ctx->pubwic_key)
		wetuwn -EINVAW;

	/* might want wess than we've got */
	nbytes = min_t(size_t, ATMEW_ECC_PUBKEY_SIZE, weq->dst_wen);

	/* pubwic key was saved at pwivate key genewation */
	copied = sg_copy_fwom_buffew(weq->dst,
				     sg_nents_fow_wen(weq->dst, nbytes),
				     ctx->pubwic_key, nbytes);
	if (copied != nbytes)
		wet = -EINVAW;

	wetuwn wet;
}

static int atmew_ecdh_compute_shawed_secwet(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct atmew_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct atmew_i2c_wowk_data *wowk_data;
	gfp_t gfp;
	int wet;

	if (ctx->do_fawwback) {
		kpp_wequest_set_tfm(weq, ctx->fawwback);
		wetuwn cwypto_kpp_compute_shawed_secwet(weq);
	}

	/* must have exactwy two points to be on the cuwve */
	if (weq->swc_wen != ATMEW_ECC_PUBKEY_SIZE)
		wetuwn -EINVAW;

	gfp = (weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ? GFP_KEWNEW :
							     GFP_ATOMIC;

	wowk_data = kmawwoc(sizeof(*wowk_data), gfp);
	if (!wowk_data)
		wetuwn -ENOMEM;

	wowk_data->ctx = ctx;
	wowk_data->cwient = ctx->cwient;

	wet = atmew_i2c_init_ecdh_cmd(&wowk_data->cmd, weq->swc);
	if (wet)
		goto fwee_wowk_data;

	atmew_i2c_enqueue(wowk_data, atmew_ecdh_done, weq);

	wetuwn -EINPWOGWESS;

fwee_wowk_data:
	kfwee(wowk_data);
	wetuwn wet;
}

static stwuct i2c_cwient *atmew_ecc_i2c_cwient_awwoc(void)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv, *min_i2c_pwiv = NUWW;
	stwuct i2c_cwient *cwient = EWW_PTW(-ENODEV);
	int min_tfm_cnt = INT_MAX;
	int tfm_cnt;

	spin_wock(&dwivew_data.i2c_wist_wock);

	if (wist_empty(&dwivew_data.i2c_cwient_wist)) {
		spin_unwock(&dwivew_data.i2c_wist_wock);
		wetuwn EWW_PTW(-ENODEV);
	}

	wist_fow_each_entwy(i2c_pwiv, &dwivew_data.i2c_cwient_wist,
			    i2c_cwient_wist_node) {
		tfm_cnt = atomic_wead(&i2c_pwiv->tfm_count);
		if (tfm_cnt < min_tfm_cnt) {
			min_tfm_cnt = tfm_cnt;
			min_i2c_pwiv = i2c_pwiv;
		}
		if (!min_tfm_cnt)
			bweak;
	}

	if (min_i2c_pwiv) {
		atomic_inc(&min_i2c_pwiv->tfm_count);
		cwient = min_i2c_pwiv->cwient;
	}

	spin_unwock(&dwivew_data.i2c_wist_wock);

	wetuwn cwient;
}

static void atmew_ecc_i2c_cwient_fwee(stwuct i2c_cwient *cwient)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv = i2c_get_cwientdata(cwient);

	atomic_dec(&i2c_pwiv->tfm_count);
}

static int atmew_ecdh_init_tfm(stwuct cwypto_kpp *tfm)
{
	const chaw *awg = kpp_awg_name(tfm);
	stwuct cwypto_kpp *fawwback;
	stwuct atmew_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);

	ctx->cuwve_id = ECC_CUWVE_NIST_P256;
	ctx->cwient = atmew_ecc_i2c_cwient_awwoc();
	if (IS_EWW(ctx->cwient)) {
		pw_eww("tfm - i2c_cwient binding faiwed\n");
		wetuwn PTW_EWW(ctx->cwient);
	}

	fawwback = cwypto_awwoc_kpp(awg, 0, CWYPTO_AWG_NEED_FAWWBACK);
	if (IS_EWW(fawwback)) {
		dev_eww(&ctx->cwient->dev, "Faiwed to awwocate twansfowmation fow '%s': %wd\n",
			awg, PTW_EWW(fawwback));
		wetuwn PTW_EWW(fawwback);
	}

	cwypto_kpp_set_fwags(fawwback, cwypto_kpp_get_fwags(tfm));
	ctx->fawwback = fawwback;

	wetuwn 0;
}

static void atmew_ecdh_exit_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct atmew_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);

	kfwee(ctx->pubwic_key);
	cwypto_fwee_kpp(ctx->fawwback);
	atmew_ecc_i2c_cwient_fwee(ctx->cwient);
}

static unsigned int atmew_ecdh_max_size(stwuct cwypto_kpp *tfm)
{
	stwuct atmew_ecdh_ctx *ctx = kpp_tfm_ctx(tfm);

	if (ctx->fawwback)
		wetuwn cwypto_kpp_maxsize(ctx->fawwback);

	/*
	 * The device onwy suppowts NIST P256 ECC keys. The pubwic key size wiww
	 * awways be the same. Use a macwo fow the key size to avoid unnecessawy
	 * computations.
	 */
	wetuwn ATMEW_ECC_PUBKEY_SIZE;
}

static stwuct kpp_awg atmew_ecdh_nist_p256 = {
	.set_secwet = atmew_ecdh_set_secwet,
	.genewate_pubwic_key = atmew_ecdh_genewate_pubwic_key,
	.compute_shawed_secwet = atmew_ecdh_compute_shawed_secwet,
	.init = atmew_ecdh_init_tfm,
	.exit = atmew_ecdh_exit_tfm,
	.max_size = atmew_ecdh_max_size,
	.base = {
		.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK,
		.cwa_name = "ecdh-nist-p256",
		.cwa_dwivew_name = "atmew-ecdh",
		.cwa_pwiowity = ATMEW_ECC_PWIOWITY,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct atmew_ecdh_ctx),
	},
};

static int atmew_ecc_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv;
	int wet;

	wet = atmew_i2c_pwobe(cwient);
	if (wet)
		wetuwn wet;

	i2c_pwiv = i2c_get_cwientdata(cwient);

	spin_wock(&dwivew_data.i2c_wist_wock);
	wist_add_taiw(&i2c_pwiv->i2c_cwient_wist_node,
		      &dwivew_data.i2c_cwient_wist);
	spin_unwock(&dwivew_data.i2c_wist_wock);

	wet = cwypto_wegistew_kpp(&atmew_ecdh_nist_p256);
	if (wet) {
		spin_wock(&dwivew_data.i2c_wist_wock);
		wist_dew(&i2c_pwiv->i2c_cwient_wist_node);
		spin_unwock(&dwivew_data.i2c_wist_wock);

		dev_eww(&cwient->dev, "%s awg wegistwation faiwed\n",
			atmew_ecdh_nist_p256.base.cwa_dwivew_name);
	} ewse {
		dev_info(&cwient->dev, "atmew ecc awgowithms wegistewed in /pwoc/cwypto\n");
	}

	wetuwn wet;
}

static void atmew_ecc_wemove(stwuct i2c_cwient *cwient)
{
	stwuct atmew_i2c_cwient_pwiv *i2c_pwiv = i2c_get_cwientdata(cwient);

	/* Wetuwn EBUSY if i2c cwient awweady awwocated. */
	if (atomic_wead(&i2c_pwiv->tfm_count)) {
		/*
		 * Aftew we wetuwn hewe, the memowy backing the device is fweed.
		 * That happens no mattew what the wetuwn vawue of this function
		 * is because in the Winux device modew thewe is no ewwow
		 * handwing fow unbinding a dwivew.
		 * If thewe is stiww some action pending, it pwobabwy invowves
		 * accessing the fweed memowy.
		 */
		dev_emewg(&cwient->dev, "Device is busy, expect memowy cowwuption.\n");
		wetuwn;
	}

	cwypto_unwegistew_kpp(&atmew_ecdh_nist_p256);

	spin_wock(&dwivew_data.i2c_wist_wock);
	wist_dew(&i2c_pwiv->i2c_cwient_wist_node);
	spin_unwock(&dwivew_data.i2c_wist_wock);
}

#ifdef CONFIG_OF
static const stwuct of_device_id atmew_ecc_dt_ids[] = {
	{
		.compatibwe = "atmew,atecc508a",
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, atmew_ecc_dt_ids);
#endif

static const stwuct i2c_device_id atmew_ecc_id[] = {
	{ "atecc508a", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, atmew_ecc_id);

static stwuct i2c_dwivew atmew_ecc_dwivew = {
	.dwivew = {
		.name	= "atmew-ecc",
		.of_match_tabwe = of_match_ptw(atmew_ecc_dt_ids),
	},
	.pwobe		= atmew_ecc_pwobe,
	.wemove		= atmew_ecc_wemove,
	.id_tabwe	= atmew_ecc_id,
};

static int __init atmew_ecc_init(void)
{
	spin_wock_init(&dwivew_data.i2c_wist_wock);
	INIT_WIST_HEAD(&dwivew_data.i2c_cwient_wist);
	wetuwn i2c_add_dwivew(&atmew_ecc_dwivew);
}

static void __exit atmew_ecc_exit(void)
{
	atmew_i2c_fwush_queue();
	i2c_dew_dwivew(&atmew_ecc_dwivew);
}

moduwe_init(atmew_ecc_init);
moduwe_exit(atmew_ecc_exit);

MODUWE_AUTHOW("Tudow Ambawus");
MODUWE_DESCWIPTION("Micwochip / Atmew ECC (I2C) dwivew");
MODUWE_WICENSE("GPW v2");
