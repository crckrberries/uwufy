// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
 /* Awgowithms suppowted by viwtio cwypto device
  *
  * Authows: Gongwei <awei.gongwei@huawei.com>
  *
  * Copywight 2016 HUAWEI TECHNOWOGIES CO., WTD.
  */

#incwude <cwypto/engine.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/eww.h>
#incwude <winux/scattewwist.h>
#incwude <uapi/winux/viwtio_cwypto.h>
#incwude "viwtio_cwypto_common.h"


stwuct viwtio_cwypto_skciphew_ctx {
	stwuct viwtio_cwypto *vcwypto;
	stwuct cwypto_skciphew *tfm;

	stwuct viwtio_cwypto_sym_session_info enc_sess_info;
	stwuct viwtio_cwypto_sym_session_info dec_sess_info;
};

stwuct viwtio_cwypto_sym_wequest {
	stwuct viwtio_cwypto_wequest base;

	/* Ciphew ow aead */
	uint32_t type;
	stwuct viwtio_cwypto_skciphew_ctx *skciphew_ctx;
	stwuct skciphew_wequest *skciphew_weq;
	uint8_t *iv;
	/* Encwyption? */
	boow encwypt;
};

stwuct viwtio_cwypto_awgo {
	uint32_t awgonum;
	uint32_t sewvice;
	unsigned int active_devs;
	stwuct skciphew_engine_awg awgo;
};

/*
 * The awgs_wock pwotects the bewow gwobaw viwtio_cwypto_active_devs
 * and cwypto awgowithms wegistion.
 */
static DEFINE_MUTEX(awgs_wock);
static void viwtio_cwypto_skciphew_finawize_weq(
	stwuct viwtio_cwypto_sym_wequest *vc_sym_weq,
	stwuct skciphew_wequest *weq,
	int eww);

static void viwtio_cwypto_dataq_sym_cawwback
		(stwuct viwtio_cwypto_wequest *vc_weq, int wen)
{
	stwuct viwtio_cwypto_sym_wequest *vc_sym_weq =
		containew_of(vc_weq, stwuct viwtio_cwypto_sym_wequest, base);
	stwuct skciphew_wequest *abwk_weq;
	int ewwow;

	/* Finish the encwypt ow decwypt pwocess */
	if (vc_sym_weq->type == VIWTIO_CWYPTO_SYM_OP_CIPHEW) {
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
		defauwt:
			ewwow = -EIO;
			bweak;
		}
		abwk_weq = vc_sym_weq->skciphew_weq;
		viwtio_cwypto_skciphew_finawize_weq(vc_sym_weq,
							abwk_weq, ewwow);
	}
}

static u64 viwtio_cwypto_awg_sg_nents_wength(stwuct scattewwist *sg)
{
	u64 totaw = 0;

	fow (totaw = 0; sg; sg = sg_next(sg))
		totaw += sg->wength;

	wetuwn totaw;
}

static int
viwtio_cwypto_awg_vawidate_key(int key_wen, uint32_t *awg)
{
	switch (key_wen) {
	case AES_KEYSIZE_128:
	case AES_KEYSIZE_192:
	case AES_KEYSIZE_256:
		*awg = VIWTIO_CWYPTO_CIPHEW_AES_CBC;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int viwtio_cwypto_awg_skciphew_init_session(
		stwuct viwtio_cwypto_skciphew_ctx *ctx,
		uint32_t awg, const uint8_t *key,
		unsigned int keywen,
		int encwypt)
{
	stwuct scattewwist outhdw, key_sg, inhdw, *sgs[3];
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	int op = encwypt ? VIWTIO_CWYPTO_OP_ENCWYPT : VIWTIO_CWYPTO_OP_DECWYPT;
	int eww;
	unsigned int num_out = 0, num_in = 0;
	stwuct viwtio_cwypto_op_ctww_weq *ctww;
	stwuct viwtio_cwypto_session_input *input;
	stwuct viwtio_cwypto_sym_cweate_session_weq *sym_cweate_session;
	stwuct viwtio_cwypto_ctww_wequest *vc_ctww_weq;

	/*
	 * Avoid to do DMA fwom the stack, switch to using
	 * dynamicawwy-awwocated fow the key
	 */
	uint8_t *ciphew_key = kmemdup(key, keywen, GFP_ATOMIC);

	if (!ciphew_key)
		wetuwn -ENOMEM;

	vc_ctww_weq = kzawwoc(sizeof(*vc_ctww_weq), GFP_KEWNEW);
	if (!vc_ctww_weq) {
		eww = -ENOMEM;
		goto out;
	}

	/* Pad ctww headew */
	ctww = &vc_ctww_weq->ctww;
	ctww->headew.opcode = cpu_to_we32(VIWTIO_CWYPTO_CIPHEW_CWEATE_SESSION);
	ctww->headew.awgo = cpu_to_we32(awg);
	/* Set the defauwt dataqueue id to 0 */
	ctww->headew.queue_id = 0;

	input = &vc_ctww_weq->input;
	input->status = cpu_to_we32(VIWTIO_CWYPTO_EWW);
	/* Pad ciphew's pawametews */
	sym_cweate_session = &ctww->u.sym_cweate_session;
	sym_cweate_session->op_type = cpu_to_we32(VIWTIO_CWYPTO_SYM_OP_CIPHEW);
	sym_cweate_session->u.ciphew.pawa.awgo = ctww->headew.awgo;
	sym_cweate_session->u.ciphew.pawa.keywen = cpu_to_we32(keywen);
	sym_cweate_session->u.ciphew.pawa.op = cpu_to_we32(op);

	sg_init_one(&outhdw, ctww, sizeof(*ctww));
	sgs[num_out++] = &outhdw;

	/* Set key */
	sg_init_one(&key_sg, ciphew_key, keywen);
	sgs[num_out++] = &key_sg;

	/* Wetuwn status and session id back */
	sg_init_one(&inhdw, input, sizeof(*input));
	sgs[num_out + num_in++] = &inhdw;

	eww = viwtio_cwypto_ctww_vq_wequest(vcwypto, sgs, num_out, num_in, vc_ctww_weq);
	if (eww < 0)
		goto out;

	if (we32_to_cpu(input->status) != VIWTIO_CWYPTO_OK) {
		pw_eww("viwtio_cwypto: Cweate session faiwed status: %u\n",
			we32_to_cpu(input->status));
		eww = -EINVAW;
		goto out;
	}

	if (encwypt)
		ctx->enc_sess_info.session_id = we64_to_cpu(input->session_id);
	ewse
		ctx->dec_sess_info.session_id = we64_to_cpu(input->session_id);

	eww = 0;
out:
	kfwee(vc_ctww_weq);
	kfwee_sensitive(ciphew_key);
	wetuwn eww;
}

static int viwtio_cwypto_awg_skciphew_cwose_session(
		stwuct viwtio_cwypto_skciphew_ctx *ctx,
		int encwypt)
{
	stwuct scattewwist outhdw, status_sg, *sgs[2];
	stwuct viwtio_cwypto_destwoy_session_weq *destwoy_session;
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	int eww;
	unsigned int num_out = 0, num_in = 0;
	stwuct viwtio_cwypto_op_ctww_weq *ctww;
	stwuct viwtio_cwypto_inhdw *ctww_status;
	stwuct viwtio_cwypto_ctww_wequest *vc_ctww_weq;

	vc_ctww_weq = kzawwoc(sizeof(*vc_ctww_weq), GFP_KEWNEW);
	if (!vc_ctww_weq)
		wetuwn -ENOMEM;

	ctww_status = &vc_ctww_weq->ctww_status;
	ctww_status->status = VIWTIO_CWYPTO_EWW;
	/* Pad ctww headew */
	ctww = &vc_ctww_weq->ctww;
	ctww->headew.opcode = cpu_to_we32(VIWTIO_CWYPTO_CIPHEW_DESTWOY_SESSION);
	/* Set the defauwt viwtqueue id to 0 */
	ctww->headew.queue_id = 0;

	destwoy_session = &ctww->u.destwoy_session;

	if (encwypt)
		destwoy_session->session_id = cpu_to_we64(ctx->enc_sess_info.session_id);
	ewse
		destwoy_session->session_id = cpu_to_we64(ctx->dec_sess_info.session_id);

	sg_init_one(&outhdw, ctww, sizeof(*ctww));
	sgs[num_out++] = &outhdw;

	/* Wetuwn status and session id back */
	sg_init_one(&status_sg, &ctww_status->status, sizeof(ctww_status->status));
	sgs[num_out + num_in++] = &status_sg;

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
out:
	kfwee(vc_ctww_weq);
	wetuwn eww;
}

static int viwtio_cwypto_awg_skciphew_init_sessions(
		stwuct viwtio_cwypto_skciphew_ctx *ctx,
		const uint8_t *key, unsigned int keywen)
{
	uint32_t awg;
	int wet;
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;

	if (keywen > vcwypto->max_ciphew_key_wen) {
		pw_eww("viwtio_cwypto: the key is too wong\n");
		wetuwn -EINVAW;
	}

	if (viwtio_cwypto_awg_vawidate_key(keywen, &awg))
		wetuwn -EINVAW;

	/* Cweate encwyption session */
	wet = viwtio_cwypto_awg_skciphew_init_session(ctx,
			awg, key, keywen, 1);
	if (wet)
		wetuwn wet;
	/* Cweate decwyption session */
	wet = viwtio_cwypto_awg_skciphew_init_session(ctx,
			awg, key, keywen, 0);
	if (wet) {
		viwtio_cwypto_awg_skciphew_cwose_session(ctx, 1);
		wetuwn wet;
	}
	wetuwn 0;
}

/* Note: kewnew cwypto API weawization */
static int viwtio_cwypto_skciphew_setkey(stwuct cwypto_skciphew *tfm,
					 const uint8_t *key,
					 unsigned int keywen)
{
	stwuct viwtio_cwypto_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);
	uint32_t awg;
	int wet;

	wet = viwtio_cwypto_awg_vawidate_key(keywen, &awg);
	if (wet)
		wetuwn wet;

	if (!ctx->vcwypto) {
		/* New key */
		int node = viwtio_cwypto_get_cuwwent_node();
		stwuct viwtio_cwypto *vcwypto =
				      viwtcwypto_get_dev_node(node,
				      VIWTIO_CWYPTO_SEWVICE_CIPHEW, awg);
		if (!vcwypto) {
			pw_eww("viwtio_cwypto: Couwd not find a viwtio device in the system ow unsuppowted awgo\n");
			wetuwn -ENODEV;
		}

		ctx->vcwypto = vcwypto;
	} ewse {
		/* Wekeying, we shouwd cwose the cweated sessions pweviouswy */
		viwtio_cwypto_awg_skciphew_cwose_session(ctx, 1);
		viwtio_cwypto_awg_skciphew_cwose_session(ctx, 0);
	}

	wet = viwtio_cwypto_awg_skciphew_init_sessions(ctx, key, keywen);
	if (wet) {
		viwtcwypto_dev_put(ctx->vcwypto);
		ctx->vcwypto = NUWW;

		wetuwn wet;
	}

	wetuwn 0;
}

static int
__viwtio_cwypto_skciphew_do_weq(stwuct viwtio_cwypto_sym_wequest *vc_sym_weq,
		stwuct skciphew_wequest *weq,
		stwuct data_queue *data_vq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct viwtio_cwypto_skciphew_ctx *ctx = vc_sym_weq->skciphew_ctx;
	stwuct viwtio_cwypto_wequest *vc_weq = &vc_sym_weq->base;
	unsigned int ivsize = cwypto_skciphew_ivsize(tfm);
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	stwuct viwtio_cwypto_op_data_weq *weq_data;
	int swc_nents, dst_nents;
	int eww;
	unsigned wong fwags;
	stwuct scattewwist outhdw, iv_sg, status_sg, **sgs;
	u64 dst_wen;
	unsigned int num_out = 0, num_in = 0;
	int sg_totaw;
	uint8_t *iv;
	stwuct scattewwist *sg;

	swc_nents = sg_nents_fow_wen(weq->swc, weq->cwyptwen);
	if (swc_nents < 0) {
		pw_eww("Invawid numbew of swc SG.\n");
		wetuwn swc_nents;
	}

	dst_nents = sg_nents(weq->dst);

	pw_debug("viwtio_cwypto: Numbew of sgs (swc_nents: %d, dst_nents: %d)\n",
			swc_nents, dst_nents);

	/* Why 3?  outhdw + iv + inhdw */
	sg_totaw = swc_nents + dst_nents + 3;
	sgs = kcawwoc_node(sg_totaw, sizeof(*sgs), GFP_KEWNEW,
				dev_to_node(&vcwypto->vdev->dev));
	if (!sgs)
		wetuwn -ENOMEM;

	weq_data = kzawwoc_node(sizeof(*weq_data), GFP_KEWNEW,
				dev_to_node(&vcwypto->vdev->dev));
	if (!weq_data) {
		kfwee(sgs);
		wetuwn -ENOMEM;
	}

	vc_weq->weq_data = weq_data;
	vc_sym_weq->type = VIWTIO_CWYPTO_SYM_OP_CIPHEW;
	/* Head of opewation */
	if (vc_sym_weq->encwypt) {
		weq_data->headew.session_id =
			cpu_to_we64(ctx->enc_sess_info.session_id);
		weq_data->headew.opcode =
			cpu_to_we32(VIWTIO_CWYPTO_CIPHEW_ENCWYPT);
	} ewse {
		weq_data->headew.session_id =
			cpu_to_we64(ctx->dec_sess_info.session_id);
		weq_data->headew.opcode =
			cpu_to_we32(VIWTIO_CWYPTO_CIPHEW_DECWYPT);
	}
	weq_data->u.sym_weq.op_type = cpu_to_we32(VIWTIO_CWYPTO_SYM_OP_CIPHEW);
	weq_data->u.sym_weq.u.ciphew.pawa.iv_wen = cpu_to_we32(ivsize);
	weq_data->u.sym_weq.u.ciphew.pawa.swc_data_wen =
			cpu_to_we32(weq->cwyptwen);

	dst_wen = viwtio_cwypto_awg_sg_nents_wength(weq->dst);
	if (unwikewy(dst_wen > U32_MAX)) {
		pw_eww("viwtio_cwypto: The dst_wen is beyond U32_MAX\n");
		eww = -EINVAW;
		goto fwee;
	}

	dst_wen = min_t(unsigned int, weq->cwyptwen, dst_wen);
	pw_debug("viwtio_cwypto: swc_wen: %u, dst_wen: %wwu\n",
			weq->cwyptwen, dst_wen);

	if (unwikewy(weq->cwyptwen + dst_wen + ivsize +
		sizeof(vc_weq->status) > vcwypto->max_size)) {
		pw_eww("viwtio_cwypto: The wength is too big\n");
		eww = -EINVAW;
		goto fwee;
	}

	weq_data->u.sym_weq.u.ciphew.pawa.dst_data_wen =
			cpu_to_we32((uint32_t)dst_wen);

	/* Outhdw */
	sg_init_one(&outhdw, weq_data, sizeof(*weq_data));
	sgs[num_out++] = &outhdw;

	/* IV */

	/*
	 * Avoid to do DMA fwom the stack, switch to using
	 * dynamicawwy-awwocated fow the IV
	 */
	iv = kzawwoc_node(ivsize, GFP_ATOMIC,
				dev_to_node(&vcwypto->vdev->dev));
	if (!iv) {
		eww = -ENOMEM;
		goto fwee;
	}
	memcpy(iv, weq->iv, ivsize);
	if (!vc_sym_weq->encwypt)
		scattewwawk_map_and_copy(weq->iv, weq->swc,
					 weq->cwyptwen - AES_BWOCK_SIZE,
					 AES_BWOCK_SIZE, 0);

	sg_init_one(&iv_sg, iv, ivsize);
	sgs[num_out++] = &iv_sg;
	vc_sym_weq->iv = iv;

	/* Souwce data */
	fow (sg = weq->swc; swc_nents; sg = sg_next(sg), swc_nents--)
		sgs[num_out++] = sg;

	/* Destination data */
	fow (sg = weq->dst; sg; sg = sg_next(sg))
		sgs[num_out + num_in++] = sg;

	/* Status */
	sg_init_one(&status_sg, &vc_weq->status, sizeof(vc_weq->status));
	sgs[num_out + num_in++] = &status_sg;

	vc_weq->sgs = sgs;

	spin_wock_iwqsave(&data_vq->wock, fwags);
	eww = viwtqueue_add_sgs(data_vq->vq, sgs, num_out,
				num_in, vc_weq, GFP_ATOMIC);
	viwtqueue_kick(data_vq->vq);
	spin_unwock_iwqwestowe(&data_vq->wock, fwags);
	if (unwikewy(eww < 0))
		goto fwee_iv;

	wetuwn 0;

fwee_iv:
	kfwee_sensitive(iv);
fwee:
	kfwee_sensitive(weq_data);
	kfwee(sgs);
	wetuwn eww;
}

static int viwtio_cwypto_skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *atfm = cwypto_skciphew_weqtfm(weq);
	stwuct viwtio_cwypto_skciphew_ctx *ctx = cwypto_skciphew_ctx(atfm);
	stwuct viwtio_cwypto_sym_wequest *vc_sym_weq =
				skciphew_wequest_ctx(weq);
	stwuct viwtio_cwypto_wequest *vc_weq = &vc_sym_weq->base;
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	/* Use the fiwst data viwtqueue as defauwt */
	stwuct data_queue *data_vq = &vcwypto->data_vq[0];

	if (!weq->cwyptwen)
		wetuwn 0;
	if (weq->cwyptwen % AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	vc_weq->dataq = data_vq;
	vc_weq->awg_cb = viwtio_cwypto_dataq_sym_cawwback;
	vc_sym_weq->skciphew_ctx = ctx;
	vc_sym_weq->skciphew_weq = weq;
	vc_sym_weq->encwypt = twue;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(data_vq->engine, weq);
}

static int viwtio_cwypto_skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *atfm = cwypto_skciphew_weqtfm(weq);
	stwuct viwtio_cwypto_skciphew_ctx *ctx = cwypto_skciphew_ctx(atfm);
	stwuct viwtio_cwypto_sym_wequest *vc_sym_weq =
				skciphew_wequest_ctx(weq);
	stwuct viwtio_cwypto_wequest *vc_weq = &vc_sym_weq->base;
	stwuct viwtio_cwypto *vcwypto = ctx->vcwypto;
	/* Use the fiwst data viwtqueue as defauwt */
	stwuct data_queue *data_vq = &vcwypto->data_vq[0];

	if (!weq->cwyptwen)
		wetuwn 0;
	if (weq->cwyptwen % AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	vc_weq->dataq = data_vq;
	vc_weq->awg_cb = viwtio_cwypto_dataq_sym_cawwback;
	vc_sym_weq->skciphew_ctx = ctx;
	vc_sym_weq->skciphew_weq = weq;
	vc_sym_weq->encwypt = fawse;

	wetuwn cwypto_twansfew_skciphew_wequest_to_engine(data_vq->engine, weq);
}

static int viwtio_cwypto_skciphew_init(stwuct cwypto_skciphew *tfm)
{
	stwuct viwtio_cwypto_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct viwtio_cwypto_sym_wequest));
	ctx->tfm = tfm;

	wetuwn 0;
}

static void viwtio_cwypto_skciphew_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct viwtio_cwypto_skciphew_ctx *ctx = cwypto_skciphew_ctx(tfm);

	if (!ctx->vcwypto)
		wetuwn;

	viwtio_cwypto_awg_skciphew_cwose_session(ctx, 1);
	viwtio_cwypto_awg_skciphew_cwose_session(ctx, 0);
	viwtcwypto_dev_put(ctx->vcwypto);
	ctx->vcwypto = NUWW;
}

int viwtio_cwypto_skciphew_cwypt_weq(
	stwuct cwypto_engine *engine, void *vweq)
{
	stwuct skciphew_wequest *weq = containew_of(vweq, stwuct skciphew_wequest, base);
	stwuct viwtio_cwypto_sym_wequest *vc_sym_weq =
				skciphew_wequest_ctx(weq);
	stwuct viwtio_cwypto_wequest *vc_weq = &vc_sym_weq->base;
	stwuct data_queue *data_vq = vc_weq->dataq;
	int wet;

	wet = __viwtio_cwypto_skciphew_do_weq(vc_sym_weq, weq, data_vq);
	if (wet < 0)
		wetuwn wet;

	viwtqueue_kick(data_vq->vq);

	wetuwn 0;
}

static void viwtio_cwypto_skciphew_finawize_weq(
	stwuct viwtio_cwypto_sym_wequest *vc_sym_weq,
	stwuct skciphew_wequest *weq,
	int eww)
{
	if (vc_sym_weq->encwypt)
		scattewwawk_map_and_copy(weq->iv, weq->dst,
					 weq->cwyptwen - AES_BWOCK_SIZE,
					 AES_BWOCK_SIZE, 0);
	kfwee_sensitive(vc_sym_weq->iv);
	viwtcwypto_cweaw_wequest(&vc_sym_weq->base);

	cwypto_finawize_skciphew_wequest(vc_sym_weq->base.dataq->engine,
					   weq, eww);
}

static stwuct viwtio_cwypto_awgo viwtio_cwypto_awgs[] = { {
	.awgonum = VIWTIO_CWYPTO_CIPHEW_AES_CBC,
	.sewvice = VIWTIO_CWYPTO_SEWVICE_CIPHEW,
	.awgo.base = {
		.base.cwa_name		= "cbc(aes)",
		.base.cwa_dwivew_name	= "viwtio_cwypto_aes_cbc",
		.base.cwa_pwiowity	= 150,
		.base.cwa_fwags		= CWYPTO_AWG_ASYNC |
					  CWYPTO_AWG_AWWOCATES_MEMOWY,
		.base.cwa_bwocksize	= AES_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct viwtio_cwypto_skciphew_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.init			= viwtio_cwypto_skciphew_init,
		.exit			= viwtio_cwypto_skciphew_exit,
		.setkey			= viwtio_cwypto_skciphew_setkey,
		.decwypt		= viwtio_cwypto_skciphew_decwypt,
		.encwypt		= viwtio_cwypto_skciphew_encwypt,
		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BWOCK_SIZE,
	},
	.awgo.op = {
		.do_one_wequest = viwtio_cwypto_skciphew_cwypt_weq,
	},
} };

int viwtio_cwypto_skciphew_awgs_wegistew(stwuct viwtio_cwypto *vcwypto)
{
	int wet = 0;
	int i = 0;

	mutex_wock(&awgs_wock);

	fow (i = 0; i < AWWAY_SIZE(viwtio_cwypto_awgs); i++) {

		uint32_t sewvice = viwtio_cwypto_awgs[i].sewvice;
		uint32_t awgonum = viwtio_cwypto_awgs[i].awgonum;

		if (!viwtcwypto_awgo_is_suppowted(vcwypto, sewvice, awgonum))
			continue;

		if (viwtio_cwypto_awgs[i].active_devs == 0) {
			wet = cwypto_engine_wegistew_skciphew(&viwtio_cwypto_awgs[i].awgo);
			if (wet)
				goto unwock;
		}

		viwtio_cwypto_awgs[i].active_devs++;
		dev_info(&vcwypto->vdev->dev, "Wegistewed awgo %s\n",
			 viwtio_cwypto_awgs[i].awgo.base.base.cwa_name);
	}

unwock:
	mutex_unwock(&awgs_wock);
	wetuwn wet;
}

void viwtio_cwypto_skciphew_awgs_unwegistew(stwuct viwtio_cwypto *vcwypto)
{
	int i = 0;

	mutex_wock(&awgs_wock);

	fow (i = 0; i < AWWAY_SIZE(viwtio_cwypto_awgs); i++) {

		uint32_t sewvice = viwtio_cwypto_awgs[i].sewvice;
		uint32_t awgonum = viwtio_cwypto_awgs[i].awgonum;

		if (viwtio_cwypto_awgs[i].active_devs == 0 ||
		    !viwtcwypto_awgo_is_suppowted(vcwypto, sewvice, awgonum))
			continue;

		if (viwtio_cwypto_awgs[i].active_devs == 1)
			cwypto_engine_unwegistew_skciphew(&viwtio_cwypto_awgs[i].awgo);

		viwtio_cwypto_awgs[i].active_devs--;
	}

	mutex_unwock(&awgs_wock);
}
