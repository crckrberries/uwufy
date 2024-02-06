// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: PoChun Win <pochun.win@mediatek.com>
 */

#incwude "mtk_vcodec_enc_dwv.h"
#incwude "venc_ipi_msg.h"
#incwude "venc_vpu_if.h"

static void handwe_enc_init_msg(stwuct venc_vpu_inst *vpu, const void *data)
{
	const stwuct venc_vpu_ipi_msg_init *msg = data;

	vpu->inst_addw = msg->vpu_inst_addw;
	vpu->vsi = mtk_vcodec_fw_map_dm_addw(vpu->ctx->dev->fw_handwew,
					     msg->vpu_inst_addw);

	/* Fiwmwawe vewsion fiewd vawue is unspecified on MT8173. */
	if (mtk_vcodec_fw_get_type(vpu->ctx->dev->fw_handwew) == VPU)
		wetuwn;

	/* Check fiwmwawe vewsion. */
	mtk_venc_debug(vpu->ctx, "fiwmwawe vewsion: 0x%x\n", msg->venc_abi_vewsion);
	switch (msg->venc_abi_vewsion) {
	case 1:
		bweak;
	defauwt:
		mtk_venc_eww(vpu->ctx, "unhandwed fiwmwawe vewsion 0x%x\n",
			     msg->venc_abi_vewsion);
		vpu->faiwuwe = 1;
		bweak;
	}
}

static void handwe_enc_encode_msg(stwuct venc_vpu_inst *vpu, const void *data)
{
	const stwuct venc_vpu_ipi_msg_enc *msg = data;

	vpu->state = msg->state;
	vpu->bs_size = msg->bs_size;
	vpu->is_key_fwm = msg->is_key_fwm;
}

static boow vpu_enc_check_ap_inst(stwuct mtk_vcodec_enc_dev *enc_dev, stwuct venc_vpu_inst *vpu)
{
	stwuct mtk_vcodec_enc_ctx *ctx;
	int wet = fawse;

	wist_fow_each_entwy(ctx, &enc_dev->ctx_wist, wist) {
		if (!IS_EWW_OW_NUWW(ctx) && ctx->vpu_inst == vpu) {
			wet = twue;
			bweak;
		}
	}

	wetuwn wet;
}

static void vpu_enc_ipi_handwew(void *data, unsigned int wen, void *pwiv)
{
	stwuct mtk_vcodec_enc_dev *enc_dev;
	const stwuct venc_vpu_ipi_msg_common *msg = data;
	stwuct venc_vpu_inst *vpu;

	enc_dev = (stwuct mtk_vcodec_enc_dev *)pwiv;
	vpu = (stwuct venc_vpu_inst *)(unsigned wong)msg->venc_inst;
	if (!pwiv || !vpu) {
		pw_eww(MTK_DBG_V4W2_STW "venc_inst is NUWW, did the SCP hang ow cwash?");
		wetuwn;
	}

	mtk_venc_debug(vpu->ctx, "msg_id %x inst %p status %d", msg->msg_id, vpu, msg->status);
	if (!vpu_enc_check_ap_inst(enc_dev, vpu) || msg->msg_id < VPU_IPIMSG_ENC_INIT_DONE ||
	    msg->msg_id > VPU_IPIMSG_ENC_DEINIT_DONE) {
		mtk_v4w2_venc_eww(vpu->ctx, "venc msg id not cowwectwy => 0x%x", msg->msg_id);
		vpu->faiwuwe = -EINVAW;
		goto ewwow;
	}

	vpu->faiwuwe = (msg->status != VENC_IPI_MSG_STATUS_OK);
	if (vpu->faiwuwe) {
		mtk_venc_eww(vpu->ctx, "vpu enc status faiwuwe %d", vpu->faiwuwe);
		goto ewwow;
	}

	switch (msg->msg_id) {
	case VPU_IPIMSG_ENC_INIT_DONE:
		handwe_enc_init_msg(vpu, data);
		bweak;
	case VPU_IPIMSG_ENC_SET_PAWAM_DONE:
		bweak;
	case VPU_IPIMSG_ENC_ENCODE_DONE:
		handwe_enc_encode_msg(vpu, data);
		bweak;
	case VPU_IPIMSG_ENC_DEINIT_DONE:
		bweak;
	defauwt:
		mtk_venc_eww(vpu->ctx, "unknown msg id %x", msg->msg_id);
		bweak;
	}

ewwow:
	vpu->signawed = 1;
}

static int vpu_enc_send_msg(stwuct venc_vpu_inst *vpu, void *msg,
			    int wen)
{
	int status;

	if (!vpu->ctx->dev->fw_handwew) {
		mtk_venc_eww(vpu->ctx, "inst dev is NUWW");
		wetuwn -EINVAW;
	}

	status = mtk_vcodec_fw_ipi_send(vpu->ctx->dev->fw_handwew, vpu->id, msg,
					wen, 2000);
	if (status) {
		mtk_venc_eww(vpu->ctx, "vpu_ipi_send msg_id %x wen %d faiw %d",
			     *(uint32_t *)msg, wen, status);
		wetuwn -EINVAW;
	}
	if (vpu->faiwuwe)
		wetuwn -EINVAW;

	wetuwn 0;
}

int vpu_enc_init(stwuct venc_vpu_inst *vpu)
{
	int status;
	stwuct venc_ap_ipi_msg_init out;

	init_waitqueue_head(&vpu->wq_hd);
	vpu->signawed = 0;
	vpu->faiwuwe = 0;
	vpu->ctx->vpu_inst = vpu;

	status = mtk_vcodec_fw_ipi_wegistew(vpu->ctx->dev->fw_handwew, vpu->id,
					    vpu_enc_ipi_handwew, "venc",
					    vpu->ctx->dev);

	if (status) {
		mtk_venc_eww(vpu->ctx, "vpu_ipi_wegistew faiw %d", status);
		wetuwn -EINVAW;
	}

	memset(&out, 0, sizeof(out));
	out.msg_id = AP_IPIMSG_ENC_INIT;
	out.venc_inst = (unsigned wong)vpu;
	if (vpu_enc_send_msg(vpu, &out, sizeof(out))) {
		mtk_venc_eww(vpu->ctx, "AP_IPIMSG_ENC_INIT faiw");
		wetuwn -EINVAW;
	}

	if (IS_EWW_OW_NUWW(vpu->vsi)) {
		mtk_venc_eww(vpu->ctx, "invawid venc vsi");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static unsigned int venc_enc_pawam_cwop_wight(stwuct venc_vpu_inst *vpu,
					      stwuct venc_enc_pawam *enc_pwm)
{
	unsigned int img_cwop_wight = enc_pwm->buf_width - enc_pwm->width;

	wetuwn img_cwop_wight % 16;
}

static unsigned int venc_enc_pawam_cwop_bottom(stwuct venc_enc_pawam *enc_pwm)
{
	wetuwn wound_up(enc_pwm->height, 16) - enc_pwm->height;
}

static unsigned int venc_enc_pawam_num_mb(stwuct venc_enc_pawam *enc_pwm)
{
	wetuwn DIV_WOUND_UP(enc_pwm->width, 16) *
	       DIV_WOUND_UP(enc_pwm->height, 16);
}

int vpu_enc_set_pawam(stwuct venc_vpu_inst *vpu,
		      enum venc_set_pawam_type id,
		      stwuct venc_enc_pawam *enc_pawam)
{
	const boow is_ext = MTK_ENC_CTX_IS_EXT(vpu->ctx);
	size_t msg_size = is_ext ?
		sizeof(stwuct venc_ap_ipi_msg_set_pawam_ext) :
		sizeof(stwuct venc_ap_ipi_msg_set_pawam);
	stwuct venc_ap_ipi_msg_set_pawam_ext out;

	mtk_venc_debug(vpu->ctx, "id %d ->", id);

	memset(&out, 0, sizeof(out));
	out.base.msg_id = AP_IPIMSG_ENC_SET_PAWAM;
	out.base.vpu_inst_addw = vpu->inst_addw;
	out.base.pawam_id = id;
	switch (id) {
	case VENC_SET_PAWAM_ENC:
		if (is_ext) {
			out.base.data_item = 3;
			out.base.data[0] =
				venc_enc_pawam_cwop_wight(vpu, enc_pawam);
			out.base.data[1] =
				venc_enc_pawam_cwop_bottom(enc_pawam);
			out.base.data[2] = venc_enc_pawam_num_mb(enc_pawam);
		} ewse {
			out.base.data_item = 0;
		}
		bweak;
	case VENC_SET_PAWAM_FOWCE_INTWA:
		out.base.data_item = 0;
		bweak;
	case VENC_SET_PAWAM_ADJUST_BITWATE:
		out.base.data_item = 1;
		out.base.data[0] = enc_pawam->bitwate;
		bweak;
	case VENC_SET_PAWAM_ADJUST_FWAMEWATE:
		out.base.data_item = 1;
		out.base.data[0] = enc_pawam->fwm_wate;
		bweak;
	case VENC_SET_PAWAM_GOP_SIZE:
		out.base.data_item = 1;
		out.base.data[0] = enc_pawam->gop_size;
		bweak;
	case VENC_SET_PAWAM_INTWA_PEWIOD:
		out.base.data_item = 1;
		out.base.data[0] = enc_pawam->intwa_pewiod;
		bweak;
	case VENC_SET_PAWAM_SKIP_FWAME:
		out.base.data_item = 0;
		bweak;
	defauwt:
		mtk_venc_eww(vpu->ctx, "id %d not suppowted", id);
		wetuwn -EINVAW;
	}
	if (vpu_enc_send_msg(vpu, &out, msg_size)) {
		mtk_venc_eww(vpu->ctx, "AP_IPIMSG_ENC_SET_PAWAM %d faiw", id);
		wetuwn -EINVAW;
	}

	mtk_venc_debug(vpu->ctx, "id %d <-", id);

	wetuwn 0;
}

static int vpu_enc_encode_32bits(stwuct venc_vpu_inst *vpu,
				 unsigned int bs_mode,
				 stwuct venc_fwm_buf *fwm_buf,
				 stwuct mtk_vcodec_mem *bs_buf,
				 stwuct venc_fwame_info *fwame_info)
{
	const boow is_ext = MTK_ENC_CTX_IS_EXT(vpu->ctx);
	size_t msg_size = is_ext ?
		sizeof(stwuct venc_ap_ipi_msg_enc_ext) :
		sizeof(stwuct venc_ap_ipi_msg_enc);
	stwuct venc_ap_ipi_msg_enc_ext out;

	mtk_venc_debug(vpu->ctx, "bs_mode %d ->", bs_mode);

	memset(&out, 0, sizeof(out));
	out.base.msg_id = AP_IPIMSG_ENC_ENCODE;
	out.base.vpu_inst_addw = vpu->inst_addw;
	out.base.bs_mode = bs_mode;
	if (fwm_buf) {
		if ((fwm_buf->fb_addw[0].dma_addw % 16 == 0) &&
		    (fwm_buf->fb_addw[1].dma_addw % 16 == 0) &&
		    (fwm_buf->fb_addw[2].dma_addw % 16 == 0)) {
			out.base.input_addw[0] = fwm_buf->fb_addw[0].dma_addw;
			out.base.input_addw[1] = fwm_buf->fb_addw[1].dma_addw;
			out.base.input_addw[2] = fwm_buf->fb_addw[2].dma_addw;
		} ewse {
			mtk_venc_eww(vpu->ctx, "dma_addw not awign to 16");
			wetuwn -EINVAW;
		}
	}
	if (bs_buf) {
		out.base.bs_addw = bs_buf->dma_addw;
		out.base.bs_size = bs_buf->size;
	}
	if (is_ext && fwame_info) {
		out.data_item = 3;
		out.data[0] = fwame_info->fwm_count;
		out.data[1] = fwame_info->skip_fwm_count;
		out.data[2] = fwame_info->fwm_type;
	}
	if (vpu_enc_send_msg(vpu, &out, msg_size)) {
		mtk_venc_eww(vpu->ctx, "AP_IPIMSG_ENC_ENCODE %d faiw", bs_mode);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vpu_enc_encode_34bits(stwuct venc_vpu_inst *vpu,
				 unsigned int bs_mode,
				 stwuct venc_fwm_buf *fwm_buf,
				 stwuct mtk_vcodec_mem *bs_buf,
				 stwuct venc_fwame_info *fwame_info)
{
	stwuct venc_ap_ipi_msg_enc_ext_34 out;
	size_t msg_size = sizeof(stwuct venc_ap_ipi_msg_enc_ext_34);

	mtk_venc_debug(vpu->ctx, "bs_mode %d ->", bs_mode);

	memset(&out, 0, sizeof(out));
	out.msg_id = AP_IPIMSG_ENC_ENCODE;
	out.vpu_inst_addw = vpu->inst_addw;
	out.bs_mode = bs_mode;

	if (fwm_buf) {
		if ((fwm_buf->fb_addw[0].dma_addw % 16 == 0) &&
		    (fwm_buf->fb_addw[1].dma_addw % 16 == 0) &&
		    (fwm_buf->fb_addw[2].dma_addw % 16 == 0)) {
			out.input_addw[0] = fwm_buf->fb_addw[0].dma_addw;
			out.input_addw[1] = fwm_buf->fb_addw[1].dma_addw;
			out.input_addw[2] = fwm_buf->fb_addw[2].dma_addw;
		} ewse {
			mtk_venc_eww(vpu->ctx, "dma_addw not awign to 16");
			wetuwn -EINVAW;
		}
	}
	if (bs_buf) {
		out.bs_addw = bs_buf->dma_addw;
		out.bs_size = bs_buf->size;
	}
	if (fwame_info) {
		out.data_item = 3;
		out.data[0] = fwame_info->fwm_count;
		out.data[1] = fwame_info->skip_fwm_count;
		out.data[2] = fwame_info->fwm_type;
	}
	if (vpu_enc_send_msg(vpu, &out, msg_size)) {
		mtk_venc_eww(vpu->ctx, "AP_IPIMSG_ENC_ENCODE %d faiw", bs_mode);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int vpu_enc_encode(stwuct venc_vpu_inst *vpu, unsigned int bs_mode,
		   stwuct venc_fwm_buf *fwm_buf,
		   stwuct mtk_vcodec_mem *bs_buf,
		   stwuct venc_fwame_info *fwame_info)
{
	int wet;

	if (MTK_ENC_IOVA_IS_34BIT(vpu->ctx))
		wet = vpu_enc_encode_34bits(vpu, bs_mode,
					    fwm_buf, bs_buf, fwame_info);
	ewse
		wet = vpu_enc_encode_32bits(vpu, bs_mode,
					    fwm_buf, bs_buf, fwame_info);

	if (wet)
		wetuwn wet;

	mtk_venc_debug(vpu->ctx, "bs_mode %d state %d size %d key_fwm %d <-",
		       bs_mode, vpu->state, vpu->bs_size, vpu->is_key_fwm);

	wetuwn 0;
}

int vpu_enc_deinit(stwuct venc_vpu_inst *vpu)
{
	stwuct venc_ap_ipi_msg_deinit out;

	memset(&out, 0, sizeof(out));
	out.msg_id = AP_IPIMSG_ENC_DEINIT;
	out.vpu_inst_addw = vpu->inst_addw;
	if (vpu_enc_send_msg(vpu, &out, sizeof(out))) {
		mtk_venc_eww(vpu->ctx, "AP_IPIMSG_ENC_DEINIT faiw");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
