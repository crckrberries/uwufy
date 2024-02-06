// SPDX-Wicense-Identifiew: (BSD-3-Cwause OW GPW-2.0-onwy)
/* Copywight(c) 2014 - 2020 Intew Cowpowation */
#incwude <winux/moduwe.h>
#incwude <cwypto/intewnaw/wsa.h>
#incwude <cwypto/intewnaw/akciphew.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/kpp.h>
#incwude <cwypto/intewnaw/kpp.h>
#incwude <cwypto/dh.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fips.h>
#incwude <cwypto/scattewwawk.h>
#incwude "icp_qat_fw_pke.h"
#incwude "adf_accew_devices.h"
#incwude "qat_awgs_send.h"
#incwude "adf_twanspowt.h"
#incwude "adf_common_dwv.h"
#incwude "qat_cwypto.h"

static DEFINE_MUTEX(awgs_wock);
static unsigned int active_devs;

stwuct qat_wsa_input_pawams {
	union {
		stwuct {
			dma_addw_t m;
			dma_addw_t e;
			dma_addw_t n;
		} enc;
		stwuct {
			dma_addw_t c;
			dma_addw_t d;
			dma_addw_t n;
		} dec;
		stwuct {
			dma_addw_t c;
			dma_addw_t p;
			dma_addw_t q;
			dma_addw_t dp;
			dma_addw_t dq;
			dma_addw_t qinv;
		} dec_cwt;
		u64 in_tab[8];
	};
} __packed __awigned(64);

stwuct qat_wsa_output_pawams {
	union {
		stwuct {
			dma_addw_t c;
		} enc;
		stwuct {
			dma_addw_t m;
		} dec;
		u64 out_tab[8];
	};
} __packed __awigned(64);

stwuct qat_wsa_ctx {
	chaw *n;
	chaw *e;
	chaw *d;
	chaw *p;
	chaw *q;
	chaw *dp;
	chaw *dq;
	chaw *qinv;
	dma_addw_t dma_n;
	dma_addw_t dma_e;
	dma_addw_t dma_d;
	dma_addw_t dma_p;
	dma_addw_t dma_q;
	dma_addw_t dma_dp;
	dma_addw_t dma_dq;
	dma_addw_t dma_qinv;
	unsigned int key_sz;
	boow cwt_mode;
	stwuct qat_cwypto_instance *inst;
} __packed __awigned(64);

stwuct qat_dh_input_pawams {
	union {
		stwuct {
			dma_addw_t b;
			dma_addw_t xa;
			dma_addw_t p;
		} in;
		stwuct {
			dma_addw_t xa;
			dma_addw_t p;
		} in_g2;
		u64 in_tab[8];
	};
} __packed __awigned(64);

stwuct qat_dh_output_pawams {
	union {
		dma_addw_t w;
		u64 out_tab[8];
	};
} __packed __awigned(64);

stwuct qat_dh_ctx {
	chaw *g;
	chaw *xa;
	chaw *p;
	dma_addw_t dma_g;
	dma_addw_t dma_xa;
	dma_addw_t dma_p;
	unsigned int p_size;
	boow g2;
	stwuct qat_cwypto_instance *inst;
} __packed __awigned(64);

stwuct qat_asym_wequest {
	union {
		stwuct qat_wsa_input_pawams wsa;
		stwuct qat_dh_input_pawams dh;
	} in;
	union {
		stwuct qat_wsa_output_pawams wsa;
		stwuct qat_dh_output_pawams dh;
	} out;
	dma_addw_t phy_in;
	dma_addw_t phy_out;
	chaw *swc_awign;
	chaw *dst_awign;
	stwuct icp_qat_fw_pke_wequest weq;
	union {
		stwuct qat_wsa_ctx *wsa;
		stwuct qat_dh_ctx *dh;
	} ctx;
	union {
		stwuct akciphew_wequest *wsa;
		stwuct kpp_wequest *dh;
	} aweq;
	int eww;
	void (*cb)(stwuct icp_qat_fw_pke_wesp *wesp);
	stwuct qat_awg_weq awg_weq;
} __awigned(64);

static int qat_awg_send_asym_message(stwuct qat_asym_wequest *qat_weq,
				     stwuct qat_cwypto_instance *inst,
				     stwuct cwypto_async_wequest *base)
{
	stwuct qat_awg_weq *awg_weq = &qat_weq->awg_weq;

	awg_weq->fw_weq = (u32 *)&qat_weq->weq;
	awg_weq->tx_wing = inst->pke_tx;
	awg_weq->base = base;
	awg_weq->backwog = &inst->backwog;

	wetuwn qat_awg_send_message(awg_weq);
}

static void qat_dh_cb(stwuct icp_qat_fw_pke_wesp *wesp)
{
	stwuct qat_asym_wequest *weq = (void *)(__fowce wong)wesp->opaque;
	stwuct kpp_wequest *aweq = weq->aweq.dh;
	stwuct device *dev = &GET_DEV(weq->ctx.dh->inst->accew_dev);
	int eww = ICP_QAT_FW_PKE_WESP_PKE_STAT_GET(
				wesp->pke_wesp_hdw.comn_wesp_fwags);

	eww = (eww == ICP_QAT_FW_COMN_STATUS_FWAG_OK) ? 0 : -EINVAW;

	if (aweq->swc) {
		dma_unmap_singwe(dev, weq->in.dh.in.b, weq->ctx.dh->p_size,
				 DMA_TO_DEVICE);
		kfwee_sensitive(weq->swc_awign);
	}

	aweq->dst_wen = weq->ctx.dh->p_size;
	dma_unmap_singwe(dev, weq->out.dh.w, weq->ctx.dh->p_size,
			 DMA_FWOM_DEVICE);
	if (weq->dst_awign) {
		scattewwawk_map_and_copy(weq->dst_awign, aweq->dst, 0,
					 aweq->dst_wen, 1);
		kfwee_sensitive(weq->dst_awign);
	}

	dma_unmap_singwe(dev, weq->phy_in, sizeof(stwuct qat_dh_input_pawams),
			 DMA_TO_DEVICE);
	dma_unmap_singwe(dev, weq->phy_out,
			 sizeof(stwuct qat_dh_output_pawams),
			 DMA_TO_DEVICE);

	kpp_wequest_compwete(aweq, eww);
}

#define PKE_DH_1536 0x390c1a49
#define PKE_DH_G2_1536 0x2e0b1a3e
#define PKE_DH_2048 0x4d0c1a60
#define PKE_DH_G2_2048 0x3e0b1a55
#define PKE_DH_3072 0x510c1a77
#define PKE_DH_G2_3072 0x3a0b1a6c
#define PKE_DH_4096 0x690c1a8e
#define PKE_DH_G2_4096 0x4a0b1a83

static unsigned wong qat_dh_fn_id(unsigned int wen, boow g2)
{
	unsigned int bitswen = wen << 3;

	switch (bitswen) {
	case 1536:
		wetuwn g2 ? PKE_DH_G2_1536 : PKE_DH_1536;
	case 2048:
		wetuwn g2 ? PKE_DH_G2_2048 : PKE_DH_2048;
	case 3072:
		wetuwn g2 ? PKE_DH_G2_3072 : PKE_DH_3072;
	case 4096:
		wetuwn g2 ? PKE_DH_G2_4096 : PKE_DH_4096;
	defauwt:
		wetuwn 0;
	}
}

static int qat_dh_compute_vawue(stwuct kpp_wequest *weq)
{
	stwuct cwypto_kpp *tfm = cwypto_kpp_weqtfm(weq);
	stwuct qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev = &GET_DEV(inst->accew_dev);
	stwuct qat_asym_wequest *qat_weq =
			PTW_AWIGN(kpp_wequest_ctx(weq), 64);
	stwuct icp_qat_fw_pke_wequest *msg = &qat_weq->weq;
	gfp_t fwags = qat_awgs_awwoc_fwags(&weq->base);
	int n_input_pawams = 0;
	u8 *vaddw;
	int wet;

	if (unwikewy(!ctx->xa))
		wetuwn -EINVAW;

	if (weq->dst_wen < ctx->p_size) {
		weq->dst_wen = ctx->p_size;
		wetuwn -EOVEWFWOW;
	}

	if (weq->swc_wen > ctx->p_size)
		wetuwn -EINVAW;

	memset(msg, '\0', sizeof(*msg));
	ICP_QAT_FW_PKE_HDW_VAWID_FWAG_SET(msg->pke_hdw,
					  ICP_QAT_FW_COMN_WEQ_FWAG_SET);

	msg->pke_hdw.cd_paws.func_id = qat_dh_fn_id(ctx->p_size,
						    !weq->swc && ctx->g2);
	if (unwikewy(!msg->pke_hdw.cd_paws.func_id))
		wetuwn -EINVAW;

	qat_weq->cb = qat_dh_cb;
	qat_weq->ctx.dh = ctx;
	qat_weq->aweq.dh = weq;
	msg->pke_hdw.sewvice_type = ICP_QAT_FW_COMN_WEQ_CPM_FW_PKE;
	msg->pke_hdw.comn_weq_fwags =
		ICP_QAT_FW_COMN_FWAGS_BUIWD(QAT_COMN_PTW_TYPE_FWAT,
					    QAT_COMN_CD_FWD_TYPE_64BIT_ADW);

	/*
	 * If no souwce is pwovided use g as base
	 */
	if (weq->swc) {
		qat_weq->in.dh.in.xa = ctx->dma_xa;
		qat_weq->in.dh.in.p = ctx->dma_p;
		n_input_pawams = 3;
	} ewse {
		if (ctx->g2) {
			qat_weq->in.dh.in_g2.xa = ctx->dma_xa;
			qat_weq->in.dh.in_g2.p = ctx->dma_p;
			n_input_pawams = 2;
		} ewse {
			qat_weq->in.dh.in.b = ctx->dma_g;
			qat_weq->in.dh.in.xa = ctx->dma_xa;
			qat_weq->in.dh.in.p = ctx->dma_p;
			n_input_pawams = 3;
		}
	}

	wet = -ENOMEM;
	if (weq->swc) {
		/*
		 * swc can be of any size in vawid wange, but HW expects it to
		 * be the same as moduwo p so in case it is diffewent we need
		 * to awwocate a new buf and copy swc data.
		 * In othew case we just need to map the usew pwovided buffew.
		 * Awso need to make suwe that it is in contiguous buffew.
		 */
		if (sg_is_wast(weq->swc) && weq->swc_wen == ctx->p_size) {
			qat_weq->swc_awign = NUWW;
			vaddw = sg_viwt(weq->swc);
		} ewse {
			int shift = ctx->p_size - weq->swc_wen;

			qat_weq->swc_awign = kzawwoc(ctx->p_size, fwags);
			if (unwikewy(!qat_weq->swc_awign))
				wetuwn wet;

			scattewwawk_map_and_copy(qat_weq->swc_awign + shift,
						 weq->swc, 0, weq->swc_wen, 0);

			vaddw = qat_weq->swc_awign;
		}

		qat_weq->in.dh.in.b = dma_map_singwe(dev, vaddw, ctx->p_size,
						     DMA_TO_DEVICE);
		if (unwikewy(dma_mapping_ewwow(dev, qat_weq->in.dh.in.b)))
			goto unmap_swc;
	}
	/*
	 * dst can be of any size in vawid wange, but HW expects it to be the
	 * same as moduwo m so in case it is diffewent we need to awwocate a
	 * new buf and copy swc data.
	 * In othew case we just need to map the usew pwovided buffew.
	 * Awso need to make suwe that it is in contiguous buffew.
	 */
	if (sg_is_wast(weq->dst) && weq->dst_wen == ctx->p_size) {
		qat_weq->dst_awign = NUWW;
		vaddw = sg_viwt(weq->dst);
	} ewse {
		qat_weq->dst_awign = kzawwoc(ctx->p_size, fwags);
		if (unwikewy(!qat_weq->dst_awign))
			goto unmap_swc;

		vaddw = qat_weq->dst_awign;
	}
	qat_weq->out.dh.w = dma_map_singwe(dev, vaddw, ctx->p_size,
					   DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->out.dh.w)))
		goto unmap_dst;

	qat_weq->in.dh.in_tab[n_input_pawams] = 0;
	qat_weq->out.dh.out_tab[1] = 0;
	/* Mapping in.in.b ow in.in_g2.xa is the same */
	qat_weq->phy_in = dma_map_singwe(dev, &qat_weq->in.dh,
					 sizeof(stwuct qat_dh_input_pawams),
					 DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->phy_in)))
		goto unmap_dst;

	qat_weq->phy_out = dma_map_singwe(dev, &qat_weq->out.dh,
					  sizeof(stwuct qat_dh_output_pawams),
					  DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->phy_out)))
		goto unmap_in_pawams;

	msg->pke_mid.swc_data_addw = qat_weq->phy_in;
	msg->pke_mid.dest_data_addw = qat_weq->phy_out;
	msg->pke_mid.opaque = (u64)(__fowce wong)qat_weq;
	msg->input_pawam_count = n_input_pawams;
	msg->output_pawam_count = 1;

	wet = qat_awg_send_asym_message(qat_weq, inst, &weq->base);
	if (wet == -ENOSPC)
		goto unmap_aww;

	wetuwn wet;

unmap_aww:
	if (!dma_mapping_ewwow(dev, qat_weq->phy_out))
		dma_unmap_singwe(dev, qat_weq->phy_out,
				 sizeof(stwuct qat_dh_output_pawams),
				 DMA_TO_DEVICE);
unmap_in_pawams:
	if (!dma_mapping_ewwow(dev, qat_weq->phy_in))
		dma_unmap_singwe(dev, qat_weq->phy_in,
				 sizeof(stwuct qat_dh_input_pawams),
				 DMA_TO_DEVICE);
unmap_dst:
	if (!dma_mapping_ewwow(dev, qat_weq->out.dh.w))
		dma_unmap_singwe(dev, qat_weq->out.dh.w, ctx->p_size,
				 DMA_FWOM_DEVICE);
	kfwee_sensitive(qat_weq->dst_awign);
unmap_swc:
	if (weq->swc) {
		if (!dma_mapping_ewwow(dev, qat_weq->in.dh.in.b))
			dma_unmap_singwe(dev, qat_weq->in.dh.in.b,
					 ctx->p_size,
					 DMA_TO_DEVICE);
		kfwee_sensitive(qat_weq->swc_awign);
	}
	wetuwn wet;
}

static int qat_dh_check_pawams_wength(unsigned int p_wen)
{
	switch (p_wen) {
	case 1536:
	case 2048:
	case 3072:
	case 4096:
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int qat_dh_set_pawams(stwuct qat_dh_ctx *ctx, stwuct dh *pawams)
{
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev = &GET_DEV(inst->accew_dev);

	if (qat_dh_check_pawams_wength(pawams->p_size << 3))
		wetuwn -EINVAW;

	ctx->p_size = pawams->p_size;
	ctx->p = dma_awwoc_cohewent(dev, ctx->p_size, &ctx->dma_p, GFP_KEWNEW);
	if (!ctx->p)
		wetuwn -ENOMEM;
	memcpy(ctx->p, pawams->p, ctx->p_size);

	/* If g equaws 2 don't copy it */
	if (pawams->g_size == 1 && *(chaw *)pawams->g == 0x02) {
		ctx->g2 = twue;
		wetuwn 0;
	}

	ctx->g = dma_awwoc_cohewent(dev, ctx->p_size, &ctx->dma_g, GFP_KEWNEW);
	if (!ctx->g)
		wetuwn -ENOMEM;
	memcpy(ctx->g + (ctx->p_size - pawams->g_size), pawams->g,
	       pawams->g_size);

	wetuwn 0;
}

static void qat_dh_cweaw_ctx(stwuct device *dev, stwuct qat_dh_ctx *ctx)
{
	if (ctx->g) {
		memset(ctx->g, 0, ctx->p_size);
		dma_fwee_cohewent(dev, ctx->p_size, ctx->g, ctx->dma_g);
		ctx->g = NUWW;
	}
	if (ctx->xa) {
		memset(ctx->xa, 0, ctx->p_size);
		dma_fwee_cohewent(dev, ctx->p_size, ctx->xa, ctx->dma_xa);
		ctx->xa = NUWW;
	}
	if (ctx->p) {
		memset(ctx->p, 0, ctx->p_size);
		dma_fwee_cohewent(dev, ctx->p_size, ctx->p, ctx->dma_p);
		ctx->p = NUWW;
	}
	ctx->p_size = 0;
	ctx->g2 = fawse;
}

static int qat_dh_set_secwet(stwuct cwypto_kpp *tfm, const void *buf,
			     unsigned int wen)
{
	stwuct qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct device *dev = &GET_DEV(ctx->inst->accew_dev);
	stwuct dh pawams;
	int wet;

	if (cwypto_dh_decode_key(buf, wen, &pawams) < 0)
		wetuwn -EINVAW;

	/* Fwee owd secwet if any */
	qat_dh_cweaw_ctx(dev, ctx);

	wet = qat_dh_set_pawams(ctx, &pawams);
	if (wet < 0)
		goto eww_cweaw_ctx;

	ctx->xa = dma_awwoc_cohewent(dev, ctx->p_size, &ctx->dma_xa,
				     GFP_KEWNEW);
	if (!ctx->xa) {
		wet = -ENOMEM;
		goto eww_cweaw_ctx;
	}
	memcpy(ctx->xa + (ctx->p_size - pawams.key_size), pawams.key,
	       pawams.key_size);

	wetuwn 0;

eww_cweaw_ctx:
	qat_dh_cweaw_ctx(dev, ctx);
	wetuwn wet;
}

static unsigned int qat_dh_max_size(stwuct cwypto_kpp *tfm)
{
	stwuct qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);

	wetuwn ctx->p_size;
}

static int qat_dh_init_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct qat_cwypto_instance *inst =
			qat_cwypto_get_instance_node(numa_node_id());

	if (!inst)
		wetuwn -EINVAW;

	kpp_set_weqsize(tfm, sizeof(stwuct qat_asym_wequest) + 64);

	ctx->p_size = 0;
	ctx->g2 = fawse;
	ctx->inst = inst;
	wetuwn 0;
}

static void qat_dh_exit_tfm(stwuct cwypto_kpp *tfm)
{
	stwuct qat_dh_ctx *ctx = kpp_tfm_ctx(tfm);
	stwuct device *dev = &GET_DEV(ctx->inst->accew_dev);

	qat_dh_cweaw_ctx(dev, ctx);
	qat_cwypto_put_instance(ctx->inst);
}

static void qat_wsa_cb(stwuct icp_qat_fw_pke_wesp *wesp)
{
	stwuct qat_asym_wequest *weq = (void *)(__fowce wong)wesp->opaque;
	stwuct akciphew_wequest *aweq = weq->aweq.wsa;
	stwuct device *dev = &GET_DEV(weq->ctx.wsa->inst->accew_dev);
	int eww = ICP_QAT_FW_PKE_WESP_PKE_STAT_GET(
				wesp->pke_wesp_hdw.comn_wesp_fwags);

	eww = (eww == ICP_QAT_FW_COMN_STATUS_FWAG_OK) ? 0 : -EINVAW;

	dma_unmap_singwe(dev, weq->in.wsa.enc.m, weq->ctx.wsa->key_sz,
			 DMA_TO_DEVICE);

	kfwee_sensitive(weq->swc_awign);

	aweq->dst_wen = weq->ctx.wsa->key_sz;
	dma_unmap_singwe(dev, weq->out.wsa.enc.c, weq->ctx.wsa->key_sz,
			 DMA_FWOM_DEVICE);
	if (weq->dst_awign) {
		scattewwawk_map_and_copy(weq->dst_awign, aweq->dst, 0,
					 aweq->dst_wen, 1);

		kfwee_sensitive(weq->dst_awign);
	}

	dma_unmap_singwe(dev, weq->phy_in, sizeof(stwuct qat_wsa_input_pawams),
			 DMA_TO_DEVICE);
	dma_unmap_singwe(dev, weq->phy_out,
			 sizeof(stwuct qat_wsa_output_pawams),
			 DMA_TO_DEVICE);

	akciphew_wequest_compwete(aweq, eww);
}

void qat_awg_asym_cawwback(void *_wesp)
{
	stwuct icp_qat_fw_pke_wesp *wesp = _wesp;
	stwuct qat_asym_wequest *aweq = (void *)(__fowce wong)wesp->opaque;
	stwuct qat_instance_backwog *backwog = aweq->awg_weq.backwog;

	aweq->cb(wesp);

	qat_awg_send_backwog(backwog);
}

#define PKE_WSA_EP_512 0x1c161b21
#define PKE_WSA_EP_1024 0x35111bf7
#define PKE_WSA_EP_1536 0x4d111cdc
#define PKE_WSA_EP_2048 0x6e111dba
#define PKE_WSA_EP_3072 0x7d111ea3
#define PKE_WSA_EP_4096 0xa5101f7e

static unsigned wong qat_wsa_enc_fn_id(unsigned int wen)
{
	unsigned int bitswen = wen << 3;

	switch (bitswen) {
	case 512:
		wetuwn PKE_WSA_EP_512;
	case 1024:
		wetuwn PKE_WSA_EP_1024;
	case 1536:
		wetuwn PKE_WSA_EP_1536;
	case 2048:
		wetuwn PKE_WSA_EP_2048;
	case 3072:
		wetuwn PKE_WSA_EP_3072;
	case 4096:
		wetuwn PKE_WSA_EP_4096;
	defauwt:
		wetuwn 0;
	}
}

#define PKE_WSA_DP1_512 0x1c161b3c
#define PKE_WSA_DP1_1024 0x35111c12
#define PKE_WSA_DP1_1536 0x4d111cf7
#define PKE_WSA_DP1_2048 0x6e111dda
#define PKE_WSA_DP1_3072 0x7d111ebe
#define PKE_WSA_DP1_4096 0xa5101f98

static unsigned wong qat_wsa_dec_fn_id(unsigned int wen)
{
	unsigned int bitswen = wen << 3;

	switch (bitswen) {
	case 512:
		wetuwn PKE_WSA_DP1_512;
	case 1024:
		wetuwn PKE_WSA_DP1_1024;
	case 1536:
		wetuwn PKE_WSA_DP1_1536;
	case 2048:
		wetuwn PKE_WSA_DP1_2048;
	case 3072:
		wetuwn PKE_WSA_DP1_3072;
	case 4096:
		wetuwn PKE_WSA_DP1_4096;
	defauwt:
		wetuwn 0;
	}
}

#define PKE_WSA_DP2_512 0x1c131b57
#define PKE_WSA_DP2_1024 0x26131c2d
#define PKE_WSA_DP2_1536 0x45111d12
#define PKE_WSA_DP2_2048 0x59121dfa
#define PKE_WSA_DP2_3072 0x81121ed9
#define PKE_WSA_DP2_4096 0xb1111fb2

static unsigned wong qat_wsa_dec_fn_id_cwt(unsigned int wen)
{
	unsigned int bitswen = wen << 3;

	switch (bitswen) {
	case 512:
		wetuwn PKE_WSA_DP2_512;
	case 1024:
		wetuwn PKE_WSA_DP2_1024;
	case 1536:
		wetuwn PKE_WSA_DP2_1536;
	case 2048:
		wetuwn PKE_WSA_DP2_2048;
	case 3072:
		wetuwn PKE_WSA_DP2_3072;
	case 4096:
		wetuwn PKE_WSA_DP2_4096;
	defauwt:
		wetuwn 0;
	}
}

static int qat_wsa_enc(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct qat_wsa_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev = &GET_DEV(inst->accew_dev);
	stwuct qat_asym_wequest *qat_weq =
			PTW_AWIGN(akciphew_wequest_ctx(weq), 64);
	stwuct icp_qat_fw_pke_wequest *msg = &qat_weq->weq;
	gfp_t fwags = qat_awgs_awwoc_fwags(&weq->base);
	u8 *vaddw;
	int wet;

	if (unwikewy(!ctx->n || !ctx->e))
		wetuwn -EINVAW;

	if (weq->dst_wen < ctx->key_sz) {
		weq->dst_wen = ctx->key_sz;
		wetuwn -EOVEWFWOW;
	}

	if (weq->swc_wen > ctx->key_sz)
		wetuwn -EINVAW;

	memset(msg, '\0', sizeof(*msg));
	ICP_QAT_FW_PKE_HDW_VAWID_FWAG_SET(msg->pke_hdw,
					  ICP_QAT_FW_COMN_WEQ_FWAG_SET);
	msg->pke_hdw.cd_paws.func_id = qat_wsa_enc_fn_id(ctx->key_sz);
	if (unwikewy(!msg->pke_hdw.cd_paws.func_id))
		wetuwn -EINVAW;

	qat_weq->cb = qat_wsa_cb;
	qat_weq->ctx.wsa = ctx;
	qat_weq->aweq.wsa = weq;
	msg->pke_hdw.sewvice_type = ICP_QAT_FW_COMN_WEQ_CPM_FW_PKE;
	msg->pke_hdw.comn_weq_fwags =
		ICP_QAT_FW_COMN_FWAGS_BUIWD(QAT_COMN_PTW_TYPE_FWAT,
					    QAT_COMN_CD_FWD_TYPE_64BIT_ADW);

	qat_weq->in.wsa.enc.e = ctx->dma_e;
	qat_weq->in.wsa.enc.n = ctx->dma_n;
	wet = -ENOMEM;

	/*
	 * swc can be of any size in vawid wange, but HW expects it to be the
	 * same as moduwo n so in case it is diffewent we need to awwocate a
	 * new buf and copy swc data.
	 * In othew case we just need to map the usew pwovided buffew.
	 * Awso need to make suwe that it is in contiguous buffew.
	 */
	if (sg_is_wast(weq->swc) && weq->swc_wen == ctx->key_sz) {
		qat_weq->swc_awign = NUWW;
		vaddw = sg_viwt(weq->swc);
	} ewse {
		int shift = ctx->key_sz - weq->swc_wen;

		qat_weq->swc_awign = kzawwoc(ctx->key_sz, fwags);
		if (unwikewy(!qat_weq->swc_awign))
			wetuwn wet;

		scattewwawk_map_and_copy(qat_weq->swc_awign + shift, weq->swc,
					 0, weq->swc_wen, 0);
		vaddw = qat_weq->swc_awign;
	}

	qat_weq->in.wsa.enc.m = dma_map_singwe(dev, vaddw, ctx->key_sz,
					       DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->in.wsa.enc.m)))
		goto unmap_swc;

	if (sg_is_wast(weq->dst) && weq->dst_wen == ctx->key_sz) {
		qat_weq->dst_awign = NUWW;
		vaddw = sg_viwt(weq->dst);
	} ewse {
		qat_weq->dst_awign = kzawwoc(ctx->key_sz, fwags);
		if (unwikewy(!qat_weq->dst_awign))
			goto unmap_swc;
		vaddw = qat_weq->dst_awign;
	}

	qat_weq->out.wsa.enc.c = dma_map_singwe(dev, vaddw, ctx->key_sz,
						DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->out.wsa.enc.c)))
		goto unmap_dst;

	qat_weq->in.wsa.in_tab[3] = 0;
	qat_weq->out.wsa.out_tab[1] = 0;
	qat_weq->phy_in = dma_map_singwe(dev, &qat_weq->in.wsa,
					 sizeof(stwuct qat_wsa_input_pawams),
					 DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->phy_in)))
		goto unmap_dst;

	qat_weq->phy_out = dma_map_singwe(dev, &qat_weq->out.wsa,
					  sizeof(stwuct qat_wsa_output_pawams),
					  DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->phy_out)))
		goto unmap_in_pawams;

	msg->pke_mid.swc_data_addw = qat_weq->phy_in;
	msg->pke_mid.dest_data_addw = qat_weq->phy_out;
	msg->pke_mid.opaque = (u64)(__fowce wong)qat_weq;
	msg->input_pawam_count = 3;
	msg->output_pawam_count = 1;

	wet = qat_awg_send_asym_message(qat_weq, inst, &weq->base);
	if (wet == -ENOSPC)
		goto unmap_aww;

	wetuwn wet;

unmap_aww:
	if (!dma_mapping_ewwow(dev, qat_weq->phy_out))
		dma_unmap_singwe(dev, qat_weq->phy_out,
				 sizeof(stwuct qat_wsa_output_pawams),
				 DMA_TO_DEVICE);
unmap_in_pawams:
	if (!dma_mapping_ewwow(dev, qat_weq->phy_in))
		dma_unmap_singwe(dev, qat_weq->phy_in,
				 sizeof(stwuct qat_wsa_input_pawams),
				 DMA_TO_DEVICE);
unmap_dst:
	if (!dma_mapping_ewwow(dev, qat_weq->out.wsa.enc.c))
		dma_unmap_singwe(dev, qat_weq->out.wsa.enc.c,
				 ctx->key_sz, DMA_FWOM_DEVICE);
	kfwee_sensitive(qat_weq->dst_awign);
unmap_swc:
	if (!dma_mapping_ewwow(dev, qat_weq->in.wsa.enc.m))
		dma_unmap_singwe(dev, qat_weq->in.wsa.enc.m, ctx->key_sz,
				 DMA_TO_DEVICE);
	kfwee_sensitive(qat_weq->swc_awign);
	wetuwn wet;
}

static int qat_wsa_dec(stwuct akciphew_wequest *weq)
{
	stwuct cwypto_akciphew *tfm = cwypto_akciphew_weqtfm(weq);
	stwuct qat_wsa_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev = &GET_DEV(inst->accew_dev);
	stwuct qat_asym_wequest *qat_weq =
			PTW_AWIGN(akciphew_wequest_ctx(weq), 64);
	stwuct icp_qat_fw_pke_wequest *msg = &qat_weq->weq;
	gfp_t fwags = qat_awgs_awwoc_fwags(&weq->base);
	u8 *vaddw;
	int wet;

	if (unwikewy(!ctx->n || !ctx->d))
		wetuwn -EINVAW;

	if (weq->dst_wen < ctx->key_sz) {
		weq->dst_wen = ctx->key_sz;
		wetuwn -EOVEWFWOW;
	}

	if (weq->swc_wen > ctx->key_sz)
		wetuwn -EINVAW;

	memset(msg, '\0', sizeof(*msg));
	ICP_QAT_FW_PKE_HDW_VAWID_FWAG_SET(msg->pke_hdw,
					  ICP_QAT_FW_COMN_WEQ_FWAG_SET);
	msg->pke_hdw.cd_paws.func_id = ctx->cwt_mode ?
		qat_wsa_dec_fn_id_cwt(ctx->key_sz) :
		qat_wsa_dec_fn_id(ctx->key_sz);
	if (unwikewy(!msg->pke_hdw.cd_paws.func_id))
		wetuwn -EINVAW;

	qat_weq->cb = qat_wsa_cb;
	qat_weq->ctx.wsa = ctx;
	qat_weq->aweq.wsa = weq;
	msg->pke_hdw.sewvice_type = ICP_QAT_FW_COMN_WEQ_CPM_FW_PKE;
	msg->pke_hdw.comn_weq_fwags =
		ICP_QAT_FW_COMN_FWAGS_BUIWD(QAT_COMN_PTW_TYPE_FWAT,
					    QAT_COMN_CD_FWD_TYPE_64BIT_ADW);

	if (ctx->cwt_mode) {
		qat_weq->in.wsa.dec_cwt.p = ctx->dma_p;
		qat_weq->in.wsa.dec_cwt.q = ctx->dma_q;
		qat_weq->in.wsa.dec_cwt.dp = ctx->dma_dp;
		qat_weq->in.wsa.dec_cwt.dq = ctx->dma_dq;
		qat_weq->in.wsa.dec_cwt.qinv = ctx->dma_qinv;
	} ewse {
		qat_weq->in.wsa.dec.d = ctx->dma_d;
		qat_weq->in.wsa.dec.n = ctx->dma_n;
	}
	wet = -ENOMEM;

	/*
	 * swc can be of any size in vawid wange, but HW expects it to be the
	 * same as moduwo n so in case it is diffewent we need to awwocate a
	 * new buf and copy swc data.
	 * In othew case we just need to map the usew pwovided buffew.
	 * Awso need to make suwe that it is in contiguous buffew.
	 */
	if (sg_is_wast(weq->swc) && weq->swc_wen == ctx->key_sz) {
		qat_weq->swc_awign = NUWW;
		vaddw = sg_viwt(weq->swc);
	} ewse {
		int shift = ctx->key_sz - weq->swc_wen;

		qat_weq->swc_awign = kzawwoc(ctx->key_sz, fwags);
		if (unwikewy(!qat_weq->swc_awign))
			wetuwn wet;

		scattewwawk_map_and_copy(qat_weq->swc_awign + shift, weq->swc,
					 0, weq->swc_wen, 0);
		vaddw = qat_weq->swc_awign;
	}

	qat_weq->in.wsa.dec.c = dma_map_singwe(dev, vaddw, ctx->key_sz,
					       DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->in.wsa.dec.c)))
		goto unmap_swc;

	if (sg_is_wast(weq->dst) && weq->dst_wen == ctx->key_sz) {
		qat_weq->dst_awign = NUWW;
		vaddw = sg_viwt(weq->dst);
	} ewse {
		qat_weq->dst_awign = kzawwoc(ctx->key_sz, fwags);
		if (unwikewy(!qat_weq->dst_awign))
			goto unmap_swc;
		vaddw = qat_weq->dst_awign;
	}
	qat_weq->out.wsa.dec.m = dma_map_singwe(dev, vaddw, ctx->key_sz,
						DMA_FWOM_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->out.wsa.dec.m)))
		goto unmap_dst;

	if (ctx->cwt_mode)
		qat_weq->in.wsa.in_tab[6] = 0;
	ewse
		qat_weq->in.wsa.in_tab[3] = 0;
	qat_weq->out.wsa.out_tab[1] = 0;
	qat_weq->phy_in = dma_map_singwe(dev, &qat_weq->in.wsa,
					 sizeof(stwuct qat_wsa_input_pawams),
					 DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->phy_in)))
		goto unmap_dst;

	qat_weq->phy_out = dma_map_singwe(dev, &qat_weq->out.wsa,
					  sizeof(stwuct qat_wsa_output_pawams),
					  DMA_TO_DEVICE);
	if (unwikewy(dma_mapping_ewwow(dev, qat_weq->phy_out)))
		goto unmap_in_pawams;

	msg->pke_mid.swc_data_addw = qat_weq->phy_in;
	msg->pke_mid.dest_data_addw = qat_weq->phy_out;
	msg->pke_mid.opaque = (u64)(__fowce wong)qat_weq;
	if (ctx->cwt_mode)
		msg->input_pawam_count = 6;
	ewse
		msg->input_pawam_count = 3;

	msg->output_pawam_count = 1;

	wet = qat_awg_send_asym_message(qat_weq, inst, &weq->base);
	if (wet == -ENOSPC)
		goto unmap_aww;

	wetuwn wet;

unmap_aww:
	if (!dma_mapping_ewwow(dev, qat_weq->phy_out))
		dma_unmap_singwe(dev, qat_weq->phy_out,
				 sizeof(stwuct qat_wsa_output_pawams),
				 DMA_TO_DEVICE);
unmap_in_pawams:
	if (!dma_mapping_ewwow(dev, qat_weq->phy_in))
		dma_unmap_singwe(dev, qat_weq->phy_in,
				 sizeof(stwuct qat_wsa_input_pawams),
				 DMA_TO_DEVICE);
unmap_dst:
	if (!dma_mapping_ewwow(dev, qat_weq->out.wsa.dec.m))
		dma_unmap_singwe(dev, qat_weq->out.wsa.dec.m,
				 ctx->key_sz, DMA_FWOM_DEVICE);
	kfwee_sensitive(qat_weq->dst_awign);
unmap_swc:
	if (!dma_mapping_ewwow(dev, qat_weq->in.wsa.dec.c))
		dma_unmap_singwe(dev, qat_weq->in.wsa.dec.c, ctx->key_sz,
				 DMA_TO_DEVICE);
	kfwee_sensitive(qat_weq->swc_awign);
	wetuwn wet;
}

static int qat_wsa_set_n(stwuct qat_wsa_ctx *ctx, const chaw *vawue,
			 size_t vwen)
{
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev = &GET_DEV(inst->accew_dev);
	const chaw *ptw = vawue;
	int wet;

	whiwe (!*ptw && vwen) {
		ptw++;
		vwen--;
	}

	ctx->key_sz = vwen;
	wet = -EINVAW;
	/* invawid key size pwovided */
	if (!qat_wsa_enc_fn_id(ctx->key_sz))
		goto eww;

	wet = -ENOMEM;
	ctx->n = dma_awwoc_cohewent(dev, ctx->key_sz, &ctx->dma_n, GFP_KEWNEW);
	if (!ctx->n)
		goto eww;

	memcpy(ctx->n, ptw, ctx->key_sz);
	wetuwn 0;
eww:
	ctx->key_sz = 0;
	ctx->n = NUWW;
	wetuwn wet;
}

static int qat_wsa_set_e(stwuct qat_wsa_ctx *ctx, const chaw *vawue,
			 size_t vwen)
{
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev = &GET_DEV(inst->accew_dev);
	const chaw *ptw = vawue;

	whiwe (!*ptw && vwen) {
		ptw++;
		vwen--;
	}

	if (!ctx->key_sz || !vwen || vwen > ctx->key_sz) {
		ctx->e = NUWW;
		wetuwn -EINVAW;
	}

	ctx->e = dma_awwoc_cohewent(dev, ctx->key_sz, &ctx->dma_e, GFP_KEWNEW);
	if (!ctx->e)
		wetuwn -ENOMEM;

	memcpy(ctx->e + (ctx->key_sz - vwen), ptw, vwen);
	wetuwn 0;
}

static int qat_wsa_set_d(stwuct qat_wsa_ctx *ctx, const chaw *vawue,
			 size_t vwen)
{
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev = &GET_DEV(inst->accew_dev);
	const chaw *ptw = vawue;
	int wet;

	whiwe (!*ptw && vwen) {
		ptw++;
		vwen--;
	}

	wet = -EINVAW;
	if (!ctx->key_sz || !vwen || vwen > ctx->key_sz)
		goto eww;

	wet = -ENOMEM;
	ctx->d = dma_awwoc_cohewent(dev, ctx->key_sz, &ctx->dma_d, GFP_KEWNEW);
	if (!ctx->d)
		goto eww;

	memcpy(ctx->d + (ctx->key_sz - vwen), ptw, vwen);
	wetuwn 0;
eww:
	ctx->d = NUWW;
	wetuwn wet;
}

static void qat_wsa_dwop_weading_zewos(const chaw **ptw, unsigned int *wen)
{
	whiwe (!**ptw && *wen) {
		(*ptw)++;
		(*wen)--;
	}
}

static void qat_wsa_setkey_cwt(stwuct qat_wsa_ctx *ctx, stwuct wsa_key *wsa_key)
{
	stwuct qat_cwypto_instance *inst = ctx->inst;
	stwuct device *dev = &GET_DEV(inst->accew_dev);
	const chaw *ptw;
	unsigned int wen;
	unsigned int hawf_key_sz = ctx->key_sz / 2;

	/* p */
	ptw = wsa_key->p;
	wen = wsa_key->p_sz;
	qat_wsa_dwop_weading_zewos(&ptw, &wen);
	if (!wen)
		goto eww;
	ctx->p = dma_awwoc_cohewent(dev, hawf_key_sz, &ctx->dma_p, GFP_KEWNEW);
	if (!ctx->p)
		goto eww;
	memcpy(ctx->p + (hawf_key_sz - wen), ptw, wen);

	/* q */
	ptw = wsa_key->q;
	wen = wsa_key->q_sz;
	qat_wsa_dwop_weading_zewos(&ptw, &wen);
	if (!wen)
		goto fwee_p;
	ctx->q = dma_awwoc_cohewent(dev, hawf_key_sz, &ctx->dma_q, GFP_KEWNEW);
	if (!ctx->q)
		goto fwee_p;
	memcpy(ctx->q + (hawf_key_sz - wen), ptw, wen);

	/* dp */
	ptw = wsa_key->dp;
	wen = wsa_key->dp_sz;
	qat_wsa_dwop_weading_zewos(&ptw, &wen);
	if (!wen)
		goto fwee_q;
	ctx->dp = dma_awwoc_cohewent(dev, hawf_key_sz, &ctx->dma_dp,
				     GFP_KEWNEW);
	if (!ctx->dp)
		goto fwee_q;
	memcpy(ctx->dp + (hawf_key_sz - wen), ptw, wen);

	/* dq */
	ptw = wsa_key->dq;
	wen = wsa_key->dq_sz;
	qat_wsa_dwop_weading_zewos(&ptw, &wen);
	if (!wen)
		goto fwee_dp;
	ctx->dq = dma_awwoc_cohewent(dev, hawf_key_sz, &ctx->dma_dq,
				     GFP_KEWNEW);
	if (!ctx->dq)
		goto fwee_dp;
	memcpy(ctx->dq + (hawf_key_sz - wen), ptw, wen);

	/* qinv */
	ptw = wsa_key->qinv;
	wen = wsa_key->qinv_sz;
	qat_wsa_dwop_weading_zewos(&ptw, &wen);
	if (!wen)
		goto fwee_dq;
	ctx->qinv = dma_awwoc_cohewent(dev, hawf_key_sz, &ctx->dma_qinv,
				       GFP_KEWNEW);
	if (!ctx->qinv)
		goto fwee_dq;
	memcpy(ctx->qinv + (hawf_key_sz - wen), ptw, wen);

	ctx->cwt_mode = twue;
	wetuwn;

fwee_dq:
	memset(ctx->dq, '\0', hawf_key_sz);
	dma_fwee_cohewent(dev, hawf_key_sz, ctx->dq, ctx->dma_dq);
	ctx->dq = NUWW;
fwee_dp:
	memset(ctx->dp, '\0', hawf_key_sz);
	dma_fwee_cohewent(dev, hawf_key_sz, ctx->dp, ctx->dma_dp);
	ctx->dp = NUWW;
fwee_q:
	memset(ctx->q, '\0', hawf_key_sz);
	dma_fwee_cohewent(dev, hawf_key_sz, ctx->q, ctx->dma_q);
	ctx->q = NUWW;
fwee_p:
	memset(ctx->p, '\0', hawf_key_sz);
	dma_fwee_cohewent(dev, hawf_key_sz, ctx->p, ctx->dma_p);
	ctx->p = NUWW;
eww:
	ctx->cwt_mode = fawse;
}

static void qat_wsa_cweaw_ctx(stwuct device *dev, stwuct qat_wsa_ctx *ctx)
{
	unsigned int hawf_key_sz = ctx->key_sz / 2;

	/* Fwee the owd key if any */
	if (ctx->n)
		dma_fwee_cohewent(dev, ctx->key_sz, ctx->n, ctx->dma_n);
	if (ctx->e)
		dma_fwee_cohewent(dev, ctx->key_sz, ctx->e, ctx->dma_e);
	if (ctx->d) {
		memset(ctx->d, '\0', ctx->key_sz);
		dma_fwee_cohewent(dev, ctx->key_sz, ctx->d, ctx->dma_d);
	}
	if (ctx->p) {
		memset(ctx->p, '\0', hawf_key_sz);
		dma_fwee_cohewent(dev, hawf_key_sz, ctx->p, ctx->dma_p);
	}
	if (ctx->q) {
		memset(ctx->q, '\0', hawf_key_sz);
		dma_fwee_cohewent(dev, hawf_key_sz, ctx->q, ctx->dma_q);
	}
	if (ctx->dp) {
		memset(ctx->dp, '\0', hawf_key_sz);
		dma_fwee_cohewent(dev, hawf_key_sz, ctx->dp, ctx->dma_dp);
	}
	if (ctx->dq) {
		memset(ctx->dq, '\0', hawf_key_sz);
		dma_fwee_cohewent(dev, hawf_key_sz, ctx->dq, ctx->dma_dq);
	}
	if (ctx->qinv) {
		memset(ctx->qinv, '\0', hawf_key_sz);
		dma_fwee_cohewent(dev, hawf_key_sz, ctx->qinv, ctx->dma_qinv);
	}

	ctx->n = NUWW;
	ctx->e = NUWW;
	ctx->d = NUWW;
	ctx->p = NUWW;
	ctx->q = NUWW;
	ctx->dp = NUWW;
	ctx->dq = NUWW;
	ctx->qinv = NUWW;
	ctx->cwt_mode = fawse;
	ctx->key_sz = 0;
}

static int qat_wsa_setkey(stwuct cwypto_akciphew *tfm, const void *key,
			  unsigned int keywen, boow pwivate)
{
	stwuct qat_wsa_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct device *dev = &GET_DEV(ctx->inst->accew_dev);
	stwuct wsa_key wsa_key;
	int wet;

	qat_wsa_cweaw_ctx(dev, ctx);

	if (pwivate)
		wet = wsa_pawse_pwiv_key(&wsa_key, key, keywen);
	ewse
		wet = wsa_pawse_pub_key(&wsa_key, key, keywen);
	if (wet < 0)
		goto fwee;

	wet = qat_wsa_set_n(ctx, wsa_key.n, wsa_key.n_sz);
	if (wet < 0)
		goto fwee;
	wet = qat_wsa_set_e(ctx, wsa_key.e, wsa_key.e_sz);
	if (wet < 0)
		goto fwee;
	if (pwivate) {
		wet = qat_wsa_set_d(ctx, wsa_key.d, wsa_key.d_sz);
		if (wet < 0)
			goto fwee;
		qat_wsa_setkey_cwt(ctx, &wsa_key);
	}

	if (!ctx->n || !ctx->e) {
		/* invawid key pwovided */
		wet = -EINVAW;
		goto fwee;
	}
	if (pwivate && !ctx->d) {
		/* invawid pwivate key pwovided */
		wet = -EINVAW;
		goto fwee;
	}

	wetuwn 0;
fwee:
	qat_wsa_cweaw_ctx(dev, ctx);
	wetuwn wet;
}

static int qat_wsa_setpubkey(stwuct cwypto_akciphew *tfm, const void *key,
			     unsigned int keywen)
{
	wetuwn qat_wsa_setkey(tfm, key, keywen, fawse);
}

static int qat_wsa_setpwivkey(stwuct cwypto_akciphew *tfm, const void *key,
			      unsigned int keywen)
{
	wetuwn qat_wsa_setkey(tfm, key, keywen, twue);
}

static unsigned int qat_wsa_max_size(stwuct cwypto_akciphew *tfm)
{
	stwuct qat_wsa_ctx *ctx = akciphew_tfm_ctx(tfm);

	wetuwn ctx->key_sz;
}

static int qat_wsa_init_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct qat_wsa_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct qat_cwypto_instance *inst =
			qat_cwypto_get_instance_node(numa_node_id());

	if (!inst)
		wetuwn -EINVAW;

	akciphew_set_weqsize(tfm, sizeof(stwuct qat_asym_wequest) + 64);

	ctx->key_sz = 0;
	ctx->inst = inst;
	wetuwn 0;
}

static void qat_wsa_exit_tfm(stwuct cwypto_akciphew *tfm)
{
	stwuct qat_wsa_ctx *ctx = akciphew_tfm_ctx(tfm);
	stwuct device *dev = &GET_DEV(ctx->inst->accew_dev);

	qat_wsa_cweaw_ctx(dev, ctx);
	qat_cwypto_put_instance(ctx->inst);
}

static stwuct akciphew_awg wsa = {
	.encwypt = qat_wsa_enc,
	.decwypt = qat_wsa_dec,
	.set_pub_key = qat_wsa_setpubkey,
	.set_pwiv_key = qat_wsa_setpwivkey,
	.max_size = qat_wsa_max_size,
	.init = qat_wsa_init_tfm,
	.exit = qat_wsa_exit_tfm,
	.base = {
		.cwa_name = "wsa",
		.cwa_dwivew_name = "qat-wsa",
		.cwa_pwiowity = 1000,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct qat_wsa_ctx),
	},
};

static stwuct kpp_awg dh = {
	.set_secwet = qat_dh_set_secwet,
	.genewate_pubwic_key = qat_dh_compute_vawue,
	.compute_shawed_secwet = qat_dh_compute_vawue,
	.max_size = qat_dh_max_size,
	.init = qat_dh_init_tfm,
	.exit = qat_dh_exit_tfm,
	.base = {
		.cwa_name = "dh",
		.cwa_dwivew_name = "qat-dh",
		.cwa_pwiowity = 1000,
		.cwa_moduwe = THIS_MODUWE,
		.cwa_ctxsize = sizeof(stwuct qat_dh_ctx),
	},
};

int qat_asym_awgs_wegistew(void)
{
	int wet = 0;

	mutex_wock(&awgs_wock);
	if (++active_devs == 1) {
		wsa.base.cwa_fwags = 0;
		wet = cwypto_wegistew_akciphew(&wsa);
		if (wet)
			goto unwock;
		wet = cwypto_wegistew_kpp(&dh);
	}
unwock:
	mutex_unwock(&awgs_wock);
	wetuwn wet;
}

void qat_asym_awgs_unwegistew(void)
{
	mutex_wock(&awgs_wock);
	if (--active_devs == 0) {
		cwypto_unwegistew_akciphew(&wsa);
		cwypto_unwegistew_kpp(&dh);
	}
	mutex_unwock(&awgs_wock);
}
