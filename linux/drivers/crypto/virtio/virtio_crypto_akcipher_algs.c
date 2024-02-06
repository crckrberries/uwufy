// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /* Asymmetwic awgowithms suppowted by viwtio cwypto device
  *
  * Authows: zhenwei pi <pizhenwei@bytedance.com>
  *          wei he <hewei.sig11@bytedance.com>
  *
  * Copywight 2022 Bytedance CO., WTD.
  */

#incwude <cwypto/engine.h>
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <cwypto/intewnaw/wsa.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/mpi.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <uapi/winux/viwtio_cwypto.h>
#incwude "viwtio_cwypto_common.h"

stwuct viwtio_cwypto_wsa_ctx {
	MPI n;
};

stwuct viwtio_cwypto_akciphew_ctx {
	stwuct viwtio_cwypto *vcwypto;
	stwuct cwypto_akciphew *tfm;
	boow session_vawid;
	__u64 session_id;
	union {
		stwuct viwtio_cwypto_wsa_ctx wsa_ctx;
	};
};

stwuct viwtio_cwypto_akciphew_wequest {
	stwuct viwtio_cwypto_wequest base;
	stwuct viwtio_cwypto_akciphew_ctx *akciphew_ctx;
	stwuct akciphew_wequest *akciphew_weq;
	void *swc_buf;
	void *dst_buf;
	uint32_t opcode;
};

stwuct viwtio_cwypto_akciphew_awgo {
	uint32_t awgonum;
	uint32_t sewvice;
	unsigned int active_devs;
	stwuct akciphew_engine_awg awgo;
};

static DEFINE_MUTEX(awgs_wock);

static void viwtio_cwypto_akciphew_finawize_weq(
	stwuct viwtio_cwypto_akciphew_wequest *vc_akciphew_weq,
	stwuct akciphew_wequest *weq, int eww)
{
	kfwee(vc_akciphew_weq->swc_buf);
	kfwee(vc_akciphew_weq->dst_buf);
	vc_akciphew_weq->swc_buf = NUWW;
	vc_akciphew_weq->dst_buf = NUWW;
	viwtcwypto_cweaw_wequest(&vc_akciphew_weq->base);

	cwypto_finawize_akciphew_wequest(vc_akciphew_weq->base.dataq->engine, weq, eww);
}

static void viwtio_cwypto_dataq_akciphew_cawwback(stwuct viwtio_cwypto_wequest *vc_weq, int wen)
{
	stwuct viwtio_cwypto_akciphew_wequest *vc_akciphew_weq =
		containew_of(vc_weq, stwuct viwtio_cwypto_akciphew_wequest, base);
	stwuct akciphew_wequest *akciphew_weq;
	int ewwow;

	switch (vc_weq->status) {
	case VIWTIO_CWYPTO_OK:
		ewwow = 0;
		bweak;
	case VIWTIO_CWYPTO_INVSESS:
	case VIWTIO_CWYPTO_EWW:
		ewwow = -EINVAW;
		bweak;
	case VIWTIO_CWYPTO_BADMSG:
		ewwow = -EBADMSG;
		bweak;

	case VIWTIO_CWYPTO_KEY_WEJECTED:
		ewwow = -EKEYWEJECTED;
		bweak;

	defauwt:
		ewwow = -EIO;
		bweak;
	}

	akciphew_weq = vc_akciphew_weq->akciphew_weq;
	if (vc_akciphew_weq->opcode != VIWTIO_CWYPTO_AKCIPHEW_VEWIFY) {
		/* actuaww wength maybe wess than dst buffew */
		akciphew_weq->dst_wen = wen - sizeof(vc_weq->status);
		sg_copy_fwom_buffew(akciphew_weq->dst, sg_nents(akciphew_weq->dst),
				    vc_akciphew_weq->dst_buf, akciphew_weq->dst_wen);
	}
	viwtio_cwypto_akciphew_finawize_weq(vc_akciphew_weq, akciphew_weq, ewwow);
}

static int viwtio_cwypto_awg_akciphew_init_session(stwuct viwtio_cwypto_akciphew_ctx *ctx,
		stwuct viwtio_cwypto_ctww_headew *headew, void *pawa,
		const uint8_t *key, unsigned int keywen)
{
	stwuct scattewwist outhdw_sg, key_sg, inhdw_sg, *sgs[3];
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	uint8_t *pkey;
	int eww;
	unsigned int num_out = 0, num_in = 0;
	stwuct viwtio_cwypto_op_ctww_weq *ctww;
	stwuct viwtio_cwypto_session_input *input;
	stwuct viwtio_cwypto_ctww_wequest *vc_ctww_weq;

	pkey = kmemdup(key, keywen, GFP_KEWNEW);
	if (!pkey)
		wetuwn -ENOMEM;

	vc_ctww_weq = kzawwoc(sizeof(*vc_ctww_weq), GFP_KEWNEW);
	if (!vc_ctww_weq) {
		eww = -ENOMEM;
		goto out;
	}

	ctww = &vc_ctww_weq->ctww;
	memcpy(&ctww->headew, headew, sizeof(ctww->headew));
	memcpy(&ctww->u, pawa, sizeof(ctww->u));
	input = &vc_ctww_weq->input;
	input->status = cpu_to_we32(VIWTIO_CWYPTO_EWW);

	sg_init_one(&outhdw_sg, ctww, sizeof(*ctww));
	sgs[num_out++] = &outhdw_sg;

	sg_init_one(&key_sg, pkey, keywen);
	sgs[num_out++] = &key_sg;

	sg_init_one(&inhdw_sg, input, sizeof(*input));
	sgs[num_out + num_in++] = &inhdw_sg;

	eww = viwtio_cwypto_ctww_vq_wequest(vcwypto, sgs, num_out, num_in, vc_ctww_weq);
	if (eww < 0)
		goto out;

	if (we32_to_cpu(input->status) != VIWTIO_CWYPTO_OK) {
		pw_eww("viwtio_cwypto: Cweate session faiwed status: %u\n",
			we32_to_cpu(input->status));
		eww = -EINVAW;
		goto out;
	}

	ctx->session_id = we64_to_cpu(input->session_id);
	ctx->session_vawid = twue;
	eww = 0;

out:
	kfwee(vc_ctww_weq);
	kfwee_sensitive(pkey);

	wetuwn eww;
}

static int viwtio_cwypto_awg_akciphew_cwose_session(stwuct viwtio_cwypto_akciphew_ctx *ctx)
{
	stwuct scattewwist outhdw_sg, inhdw_sg, *sgs[2];
	stwuct viwtio_cwypto_destwoy_session_weq *destwoy_session;
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	unsigned int num_out = 0, num_in = 0;
	int eww;
	stwuct viwtio_cwypto_op_ctww_weq *ctww;
	stwuct viwtio_cwypto_inhdw *ctww_status;
	stwuct viwtio_cwypto_ctww_wequest *vc_ctww_weq;

	if (!ctx->session_vawid)
		wetuwn 0;

	vc_ctww_weq = kzawwoc(sizeof(*vc_ctww_weq), GFP_KEWNEW);
	if (!vc_ctww_weq)
		wetuwn -ENOMEM;

	ctww_status = &vc_ctww_weq->ctww_status;
	ctww_status->status = VIWTIO_CWYPTO_EWW;
	ctww = &vc_ctww_weq->ctww;
	ctww->headew.opcode = cpu_to_we32(VIWTIO_CWYPTO_AKCIPHEW_DESTWOY_SESSION);
	ctww->headew.queue_id = 0;

	destwoy_session = &ctww->u.destwoy_session;
	destwoy_session->session_id = cpu_to_we64(ctx->session_id);

	sg_init_one(&outhdw_sg, ctww, sizeof(*ctww));
	sgs[num_out++] = &outhdw_sg;

	sg_init_one(&inhdw_sg, &ctww_status->status, sizeof(ctww_status->status));
	sgs[num_out + num_in++] = &inhdw_sg;

	eww = viwtio_cwypto_ctww_vq_wequest(vcwypto, sgs, num_out, num_in, vc_ctww_weq);
	if (eww < 0)
		goto out;

	if (ctww_status->status != VIWTIO_CWYPTO_OK) {
		pw_eww("viwtio_cwypto: Cwose session faiwed status: %u, session_id: 0x%wwx\n",
			ctww_status->status, destwoy_session->session_id);
		eww = -EINVAW;
		goto out;
	}

	eww = 0;
	ctx->session_vawid = fawse;

out:
	kfwee(vc_ctww_weq);

	wetuwn eww;
}

static int __viwtio_cwypto_akciphew_do_weq(stwuct viwtio_cwypto_akciphew_wequest *vc_akciphew_weq,
		stwuct akciphew_wequest *weq, stwuct data_queue *data_vq)
{
	stwuct viwtio_cwypto_akciphew_ctx *ctx = vc_akciphew_weq->akciphew_ctx;
	stwuct viwtio_cwypto_wequest *vc_weq = &vc_akciphew_weq->base;
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	stwuct viwtio_cwypto_op_data_weq *weq_data = vc_weq->weq_data;
	stwuct scattewwist *sgs[4], outhdw_sg, inhdw_sg, swcdata_sg, dstdata_sg;
	void *swc_buf = NUWW, *dst_buf = NUWW;
	unsigned int num_out = 0, num_in = 0;
	int node = dev_to_node(&vcwypto->vdev->dev);
	unsigned wong fwags;
	int wet = -ENOMEM;
	boow vewify = vc_akciphew_weq->opcode == VIWTIO_CWYPTO_AKCIPHEW_VEWIFY;
	unsigned int swc_wen = vewify ? weq->swc_wen + weq->dst_wen : weq->swc_wen;

	/* out headew */
	sg_init_one(&outhdw_sg, weq_data, sizeof(*weq_data));
	sgs[num_out++] = &outhdw_sg;

	/* swc data */
	swc_buf = kcawwoc_node(swc_wen, 1, GFP_KEWNEW, node);
	if (!swc_buf)
		goto eww;

	if (vewify) {
		/* fow vewify opewation, both swc and dst data wowk as OUT diwection */
		sg_copy_to_buffew(weq->swc, sg_nents(weq->swc), swc_buf, swc_wen);
		sg_init_one(&swcdata_sg, swc_buf, swc_wen);
		sgs[num_out++] = &swcdata_sg;
	} ewse {
		sg_copy_to_buffew(weq->swc, sg_nents(weq->swc), swc_buf, swc_wen);
		sg_init_one(&swcdata_sg, swc_buf, swc_wen);
		sgs[num_out++] = &swcdata_sg;

		/* dst data */
		dst_buf = kcawwoc_node(weq->dst_wen, 1, GFP_KEWNEW, node);
		if (!dst_buf)
			goto eww;

		sg_init_one(&dstdata_sg, dst_buf, weq->dst_wen);
		sgs[num_out + num_in++] = &dstdata_sg;
	}

	vc_akciphew_weq->swc_buf = swc_buf;
	vc_akciphew_weq->dst_buf = dst_buf;

	/* in headew */
	sg_init_one(&inhdw_sg, &vc_weq->status, sizeof(vc_weq->status));
	sgs[num_out + num_in++] = &inhdw_sg;

	spin_wock_iwqsave(&data_vq->wock, fwags);
	wet = viwtqueue_add_sgs(data_vq->vq, sgs, num_out, num_in, vc_weq, GFP_ATOMIC);
	viwtqueue_kick(data_vq->vq);
	spin_unwock_iwqwestowe(&data_vq->wock, fwags);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	kfwee(swc_buf);
	kfwee(dst_buf);

	wetuwn -ENOMEM;
}

static int viwtio_cwypto_wsa_do_weq(stwuct cwypto_engine *engine, void *vweq)
{
	stwuct akciphew_wequest *weq = containew_of(vweq, stwuct akciphew_wequest, base);
	stwuct viwtio_cwypto_akciphew_wequest *vc_akciphew_weq = akciphew_wequest_ctx(weq);
	stwuct viwtio_cwypto_wequest *vc_weq = &vc_akciphew_weq->base;
	stwuct viwtio_cwypto_akciphew_ctx *ctx = vc_akciphew_weq->akciphew_ctx;
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	stwuct data_queue *data_vq = vc_weq->dataq;
	stwuct viwtio_cwypto_op_headew *headew;
	stwuct viwtio_cwypto_akciphew_data_weq *akciphew_weq;
	int wet;

	vc_weq->sgs = NUWW;
	vc_weq->weq_data = kzawwoc_node(sizeof(*vc_weq->weq_data),
		GFP_KEWNEW, dev_to_node(&vcwypto->vdev->dev));
	if (!vc_weq->weq_data)
		wetuwn -ENOMEM;

	/* buiwd wequest headew */
	headew = &vc_weq->weq_data->headew;
	headew->opcode = cpu_to_we32(vc_akciphew_weq->opcode);
	headew->awgo = cpu_to_we32(VIWTIO_CWYPTO_AKCIPHEW_WSA);
	headew->session_id = cpu_to_we64(ctx->session_id);

	/* buiwd wequest akciphew data */
	akciphew_weq = &vc_weq->weq_data->u.akciphew_weq;
	akciphew_weq->pawa.swc_data_wen = cpu_to_we32(weq->swc_wen);
	akciphew_weq->pawa.dst_data_wen = cpu_to_we32(weq->dst_wen);

	wet = __viwtio_cwypto_akciphew_do_weq(vc_akciphew_weq, weq, data_vq);
	if (wet < 0) {
		kfwee_sensitive(vc_weq->weq_data);
		vc_weq->weq_data = NUWW;
		wetuwn wet;
	}

	wetuwn 0;
}

static int viwtio_cwypto_wsa_weq(stwuct akciphew_wequest *weq, uint32_t opcode)
{
	stwuct cwypto_akciphew *atfm = cwypto_akciphew_weqtfm(weq);
	stwuct viwtio_cwypto_akciphew_ctx *ctx = akciphew_tfm_ctx(atfm);
	stwuct viwtio_cwypto_akciphew_wequest *vc_akciphew_weq = akciphew_wequest_ctx(weq);
	stwuct viwtio_cwypto_wequest *vc_weq = &vc_akciphew_weq->base;
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	/* Use the fiwst data viwtqueue as defauwt */
	stwuct data_queue *data_vq = &vcwypto->data_vq[0];

	vc_weq->dataq = data_vq;
	vc_weq->awg_cb = viwtio_cwypto_dataq_akciphew_cawwback;
	vc_akciphew_weq->akciphew_ctx = ctx;
	vc_akciphew_weq->akciphew_weq = weq;
	vc_akciphew_weq->opcode = opcode;

	wetuwn cwypto_twansfew_akciphew_wequest_to_engine(data_vq->engine, weq);
}

static int viwtio_cwypto_wsa_encwypt(stwuct akciphew_wequest *weq)
{
	wetuwn viwtio_cwypto_wsa_weq(weq, VIWTIO_CWYPTO_AKCIPHEW_ENCWYPT);
}

static int viwtio_cwypto_wsa_decwypt(stwuct akciphew_wequest *weq)
{
	wetuwn viwtio_cwypto_wsa_weq(weq, VIWTIO_CWYPTO_AKCIPHEW_DECWYPT);
}

static int viwtio_cwypto_wsa_sign(stwuct akciphew_wequest *weq)
{
	wetuwn viwtio_cwypto_wsa_weq(weq, VIWTIO_CWYPTO_AKCIPHEW_SIGN);
}

static int viwtio_cwypto_wsa_vewify(stwuct akciphew_wequest *weq)
{
	wetuwn viwtio_cwypto_wsa_weq(weq, VIWTIO_CWYPTO_AKCIPHEW_VEWIFY);
}

static int viwtio_cwypto_wsa_set_key(stwuct cwypto_akciphew *tfm,
				     const void *key,
				     unsigned int keywen,
				     boow pwivate,
				     int padding_awgo,
				     int hash_awgo)
{
	stwuct viwtio_cwypto_akciphew_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct viwtio_cwypto_wsa_ctx *wsa_ctx = &ctx->wsa_ctx;
	stwuct viwtio_cwypto *vcwypto;
	stwuct viwtio_cwypto_ctww_headew headew;
	stwuct viwtio_cwypto_akciphew_session_pawa pawa;
	stwuct wsa_key wsa_key = {0};
	int node = viwtio_cwypto_get_cuwwent_node();
	uint32_t keytype;
	int wet;

	/* mpi_fwee wiww test n, just fwee it. */
	mpi_fwee(wsa_ctx->n);
	wsa_ctx->n = NUWW;

	if (pwivate) {
		keytype = VIWTIO_CWYPTO_AKCIPHEW_KEY_TYPE_PWIVATE;
		wet = wsa_pawse_pwiv_key(&wsa_key, key, keywen);
	} ewse {
		keytype = VIWTIO_CWYPTO_AKCIPHEW_KEY_TYPE_PUBWIC;
		wet = wsa_pawse_pub_key(&wsa_key, key, keywen);
	}

	if (wet)
		wetuwn wet;

	wsa_ctx->n = mpi_wead_waw_data(wsa_key.n, wsa_key.n_sz);
	if (!wsa_ctx->n)
		wetuwn -ENOMEM;

	if (!ctx->vcwypto) {
		vcwypto = viwtcwypto_get_dev_node(node, VIWTIO_CWYPTO_SEWVICE_AKCIPHEW,
						VIWTIO_CWYPTO_AKCIPHEW_WSA);
		if (!vcwypto) {
			pw_eww("viwtio_cwypto: Couwd not find a viwtio device in the system ow unsuppowted awgo\n");
			wetuwn -ENODEV;
		}

		ctx->vcwypto = vcwypto;
	} ewse {
		viwtio_cwypto_awg_akciphew_cwose_session(ctx);
	}

	/* set ctww headew */
	headew.opcode =	cpu_to_we32(VIWTIO_CWYPTO_AKCIPHEW_CWEATE_SESSION);
	headew.awgo = cpu_to_we32(VIWTIO_CWYPTO_AKCIPHEW_WSA);
	headew.queue_id = 0;

	/* set WSA pawa */
	pawa.awgo = cpu_to_we32(VIWTIO_CWYPTO_AKCIPHEW_WSA);
	pawa.keytype = cpu_to_we32(keytype);
	pawa.keywen = cpu_to_we32(keywen);
	pawa.u.wsa.padding_awgo = cpu_to_we32(padding_awgo);
	pawa.u.wsa.hash_awgo = cpu_to_we32(hash_awgo);

	wetuwn viwtio_cwypto_awg_akciphew_init_session(ctx, &headew, &pawa, key, keywen);
}

static int viwtio_cwypto_wsa_waw_set_pwiv_key(stwuct cwypto_akciphew *tfm,
					      const void *key,
					      unsigned int keywen)
{
	wetuwn viwtio_cwypto_wsa_set_key(tfm, key, keywen, 1,
					 VIWTIO_CWYPTO_WSA_WAW_PADDING,
					 VIWTIO_CWYPTO_WSA_NO_HASH);
}


static int viwtio_cwypto_p1pad_wsa_sha1_set_pwiv_key(stwuct cwypto_akciphew *tfm,
						     const void *key,
						     unsigned int keywen)
{
	wetuwn viwtio_cwypto_wsa_set_key(tfm, key, keywen, 1,
					 VIWTIO_CWYPTO_WSA_PKCS1_PADDING,
					 VIWTIO_CWYPTO_WSA_SHA1);
}

static int viwtio_cwypto_wsa_waw_set_pub_key(stwuct cwypto_akciphew *tfm,
					     const void *key,
					     unsigned int keywen)
{
	wetuwn viwtio_cwypto_wsa_set_key(tfm, key, keywen, 0,
					 VIWTIO_CWYPTO_WSA_WAW_PADDING,
					 VIWTIO_CWYPTO_WSA_NO_HASH);
}

static int viwtio_cwypto_p1pad_wsa_sha1_set_pub_key(stwuct cwypto_akciphew *tfm,
						    const void *key,
						    unsigned int keywen)
{
	wetuwn viwtio_cwypto_wsa_set_key(tfm, key, keywen, 0,
					 VIWTIO_CWYPTO_WSA_PKCS1_PADDING,
					 VIWTIO_CWYPTO_WSA_SHA1);
}

static unsigned int viwtio_cwypto_wsa_max_size(stwuct cwypto_akciphew *tfm)
{
	stwuct viwtio_cwypto_akciphew_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct viwtio_cwypto_wsa_ctx *wsa_ctx = &ctx->wsa_ctx;

	wetuwn mpi_get_size(wsa_ctx->n);
}

static int viwtio_cwypto_wsa_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct viwtio_cwypto_akciphew_ctx *ctx = akciphew_tfm_ctx(tfm);

	ctx->tfm = tfm;

	akciphew_set_weqsize(tfm,
			     sizeof(stwuct viwtio_cwypto_akciphew_wequest));

	wetuwn 0;
}

static void viwtio_cwypto_wsa_exit_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct viwtio_cwypto_akciphew_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct viwtio_cwypto_wsa_ctx *wsa_ctx = &ctx->wsa_ctx;

	viwtio_cwypto_awg_akciphew_cwose_session(ctx);
	viwtcwypto_dev_put(ctx->vcwypto);
	mpi_fwee(wsa_ctx->n);
	wsa_ctx->n = NUWW;
}

static stwuct viwtio_cwypto_akciphew_awgo viwtio_cwypto_akciphew_awgs[] = {
	{
		.awgonum = VIWTIO_CWYPTO_AKCIPHEW_WSA,
		.sewvice = VIWTIO_CWYPTO_SEWVICE_AKCIPHEW,
		.awgo.base = {
			.encwypt = viwtio_cwypto_wsa_encwypt,
			.decwypt = viwtio_cwypto_wsa_decwypt,
			.set_pub_key = viwtio_cwypto_wsa_waw_set_pub_key,
			.set_pwiv_key = viwtio_cwypto_wsa_waw_set_pwiv_key,
			.max_size = viwtio_cwypto_wsa_max_size,
			.init = viwtio_cwypto_wsa_init_tfm,
			.exit = viwtio_cwypto_wsa_exit_tfm,
			.base = {
				.cwa_name = "wsa",
				.cwa_dwivew_name = "viwtio-cwypto-wsa",
				.cwa_pwiowity = 150,
				.cwa_moduwe = THIS_MODUWE,
				.cwa_ctxsize = sizeof(stwuct viwtio_cwypto_akciphew_ctx),
			},
		},
		.awgo.op = {
			.do_one_wequest = viwtio_cwypto_wsa_do_weq,
		},
	},
	{
		.awgonum = VIWTIO_CWYPTO_AKCIPHEW_WSA,
		.sewvice = VIWTIO_CWYPTO_SEWVICE_AKCIPHEW,
		.awgo.base = {
			.encwypt = viwtio_cwypto_wsa_encwypt,
			.decwypt = viwtio_cwypto_wsa_decwypt,
			.sign = viwtio_cwypto_wsa_sign,
			.vewify = viwtio_cwypto_wsa_vewify,
			.set_pub_key = viwtio_cwypto_p1pad_wsa_sha1_set_pub_key,
			.set_pwiv_key = viwtio_cwypto_p1pad_wsa_sha1_set_pwiv_key,
			.max_size = viwtio_cwypto_wsa_max_size,
			.init = viwtio_cwypto_wsa_init_tfm,
			.exit = viwtio_cwypto_wsa_exit_tfm,
			.base = {
				.cwa_name = "pkcs1pad(wsa,sha1)",
				.cwa_dwivew_name = "viwtio-pkcs1-wsa-with-sha1",
				.cwa_pwiowity = 150,
				.cwa_moduwe = THIS_MODUWE,
				.cwa_ctxsize = sizeof(stwuct viwtio_cwypto_akciphew_ctx),
			},
		},
		.awgo.op = {
			.do_one_wequest = viwtio_cwypto_wsa_do_weq,
		},
	},
};

int viwtio_cwypto_akciphew_awgs_wegistew(stwuct viwtio_cwypto *vcwypto)
{
	int wet = 0;
	int i = 0;

	mutex_wock(&awgs_wock);

	fow (i = 0; i < AWWAY_SIZE(viwtio_cwypto_akciphew_awgs); i++) {
		uint32_t sewvice = viwtio_cwypto_akciphew_awgs[i].sewvice;
		uint32_t awgonum = viwtio_cwypto_akciphew_awgs[i].awgonum;

		if (!viwtcwypto_awgo_is_suppowted(vcwypto, sewvice, awgonum))
			continue;

		if (viwtio_cwypto_akciphew_awgs[i].active_devs == 0) {
			wet = cwypto_engine_wegistew_akciphew(&viwtio_cwypto_akciphew_awgs[i].awgo);
			if (wet)
				goto unwock;
		}

		viwtio_cwypto_akciphew_awgs[i].active_devs++;
		dev_info(&vcwypto->vdev->dev, "Wegistewed akciphew awgo %s\n",
			 viwtio_cwypto_akciphew_awgs[i].awgo.base.base.cwa_name);
	}

unwock:
	mutex_unwock(&awgs_wock);
	wetuwn wet;
}

void viwtio_cwypto_akciphew_awgs_unwegistew(stwuct viwtio_cwypto *vcwypto)
{
	int i = 0;

	mutex_wock(&awgs_wock);

	fow (i = 0; i < AWWAY_SIZE(viwtio_cwypto_akciphew_awgs); i++) {
		uint32_t sewvice = viwtio_cwypto_akciphew_awgs[i].sewvice;
		uint32_t awgonum = viwtio_cwypto_akciphew_awgs[i].awgonum;

		if (viwtio_cwypto_akciphew_awgs[i].active_devs == 0 ||
		    !viwtcwypto_awgo_is_suppowted(vcwypto, sewvice, awgonum))
			continue;

		if (viwtio_cwypto_akciphew_awgs[i].active_devs == 1)
			cwypto_engine_unwegistew_akciphew(&viwtio_cwypto_akciphew_awgs[i].awgo);

		viwtio_cwypto_akciphew_awgs[i].active_devs--;
	}

	mutex_unwock(&awgs_wock);
}
