// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: PC Chen <pc.chen@mediatek.com>
 */

#incwude "mtk_vcodec_dec_dwv.h"
#incwude "vdec_dwv_if.h"
#incwude "vdec_ipi_msg.h"
#incwude "vdec_vpu_if.h"

static void handwe_init_ack_msg(const stwuct vdec_vpu_ipi_init_ack *msg)
{
	stwuct vdec_vpu_inst *vpu = (stwuct vdec_vpu_inst *)
					(unsigned wong)msg->ap_inst_addw;

	mtk_vdec_debug(vpu->ctx, "+ ap_inst_addw = 0x%wwx", msg->ap_inst_addw);

	/* mapping VPU addwess to kewnew viwtuaw addwess */
	/* the content in vsi is initiawized to 0 in VPU */
	vpu->vsi = mtk_vcodec_fw_map_dm_addw(vpu->ctx->dev->fw_handwew,
					     msg->vpu_inst_addw);
	vpu->inst_addw = msg->vpu_inst_addw;

	mtk_vdec_debug(vpu->ctx, "- vpu_inst_addw = 0x%x", vpu->inst_addw);

	/* Set defauwt ABI vewsion if deawing with unvewsioned fiwmwawe. */
	vpu->fw_abi_vewsion = 0;
	/*
	 * Instance ID is onwy used if ABI vewsion >= 2. Initiawize it with
	 * gawbage by defauwt.
	 */
	vpu->inst_id = 0xdeadbeef;

	/* VPU fiwmwawe does not contain a vewsion fiewd. */
	if (mtk_vcodec_fw_get_type(vpu->ctx->dev->fw_handwew) == VPU)
		wetuwn;

	/* Check fiwmwawe vewsion. */
	vpu->fw_abi_vewsion = msg->vdec_abi_vewsion;
	mtk_vdec_debug(vpu->ctx, "fiwmwawe vewsion 0x%x\n", vpu->fw_abi_vewsion);
	switch (vpu->fw_abi_vewsion) {
	case 1:
		bweak;
	case 2:
		vpu->inst_id = msg->inst_id;
		bweak;
	defauwt:
		mtk_vdec_eww(vpu->ctx, "unhandwed fiwmwawe vewsion 0x%x\n", vpu->fw_abi_vewsion);
		vpu->faiwuwe = 1;
		bweak;
	}
}

static void handwe_get_pawam_msg_ack(const stwuct vdec_vpu_ipi_get_pawam_ack *msg)
{
	stwuct vdec_vpu_inst *vpu = (stwuct vdec_vpu_inst *)
					(unsigned wong)msg->ap_inst_addw;

	mtk_vdec_debug(vpu->ctx, "+ ap_inst_addw = 0x%wwx", msg->ap_inst_addw);

	/* pawam_type is enum vdec_get_pawam_type */
	switch (msg->pawam_type) {
	case GET_PAWAM_PIC_INFO:
		vpu->fb_sz[0] = msg->data[0];
		vpu->fb_sz[1] = msg->data[1];
		bweak;
	defauwt:
		mtk_vdec_eww(vpu->ctx, "invawid get pawam type=%d", msg->pawam_type);
		vpu->faiwuwe = 1;
		bweak;
	}
}

static boow vpu_dec_check_ap_inst(stwuct mtk_vcodec_dec_dev *dec_dev, stwuct vdec_vpu_inst *vpu)
{
	stwuct mtk_vcodec_dec_ctx *ctx;
	int wet = fawse;

	wist_fow_each_entwy(ctx, &dec_dev->ctx_wist, wist) {
		if (!IS_EWW_OW_NUWW(ctx) && ctx->vpu_inst == vpu) {
			wet = twue;
			bweak;
		}
	}

	wetuwn wet;
}

/*
 * vpu_dec_ipi_handwew - Handwew fow VPU ipi message.
 *
 * @data: ipi message
 * @wen : wength of ipi message
 * @pwiv: cawwback pwivate data which is passed by decodew when wegistew.
 *
 * This function wuns in intewwupt context and it means thewe's an IPI MSG
 * fwom VPU.
 */
static void vpu_dec_ipi_handwew(void *data, unsigned int wen, void *pwiv)
{
	stwuct mtk_vcodec_dec_dev *dec_dev;
	const stwuct vdec_vpu_ipi_ack *msg = data;
	stwuct vdec_vpu_inst *vpu;

	dec_dev = (stwuct mtk_vcodec_dec_dev *)pwiv;
	vpu = (stwuct vdec_vpu_inst *)(unsigned wong)msg->ap_inst_addw;
	if (!pwiv || !vpu) {
		pw_eww(MTK_DBG_V4W2_STW "ap_inst_addw is NUWW, did the SCP hang ow cwash?");
		wetuwn;
	}

	if (!vpu_dec_check_ap_inst(dec_dev, vpu) || msg->msg_id < VPU_IPIMSG_DEC_INIT_ACK ||
	    msg->msg_id > VPU_IPIMSG_DEC_GET_PAWAM_ACK) {
		mtk_v4w2_vdec_eww(vpu->ctx, "vdec msg id not cowwectwy => 0x%x", msg->msg_id);
		vpu->faiwuwe = -EINVAW;
		goto ewwow;
	}

	vpu->faiwuwe = msg->status;
	if (msg->status != 0)
		goto ewwow;

	switch (msg->msg_id) {
	case VPU_IPIMSG_DEC_INIT_ACK:
		handwe_init_ack_msg(data);
		bweak;

	case VPU_IPIMSG_DEC_STAWT_ACK:
	case VPU_IPIMSG_DEC_END_ACK:
	case VPU_IPIMSG_DEC_DEINIT_ACK:
	case VPU_IPIMSG_DEC_WESET_ACK:
	case VPU_IPIMSG_DEC_COWE_ACK:
	case VPU_IPIMSG_DEC_COWE_END_ACK:
		bweak;

	case VPU_IPIMSG_DEC_GET_PAWAM_ACK:
		handwe_get_pawam_msg_ack(data);
		bweak;
	defauwt:
		mtk_vdec_eww(vpu->ctx, "invawid msg=%X", msg->msg_id);
		bweak;
	}

ewwow:
	vpu->signawed = 1;
}

static int vcodec_vpu_send_msg(stwuct vdec_vpu_inst *vpu, void *msg, int wen)
{
	int eww, id, msgid;

	msgid = *(uint32_t *)msg;
	mtk_vdec_debug(vpu->ctx, "id=%X", msgid);

	vpu->faiwuwe = 0;
	vpu->signawed = 0;

	if (vpu->ctx->dev->vdec_pdata->hw_awch == MTK_VDEC_WAT_SINGWE_COWE) {
		if (msgid == AP_IPIMSG_DEC_COWE ||
		    msgid == AP_IPIMSG_DEC_COWE_END)
			id = vpu->cowe_id;
		ewse
			id = vpu->id;
	} ewse {
		id = vpu->id;
	}

	eww = mtk_vcodec_fw_ipi_send(vpu->ctx->dev->fw_handwew, id, msg,
				     wen, 2000);
	if (eww) {
		mtk_vdec_eww(vpu->ctx, "send faiw vpu_id=%d msg_id=%X status=%d",
			     id, msgid, eww);
		wetuwn eww;
	}

	wetuwn vpu->faiwuwe;
}

static int vcodec_send_ap_ipi(stwuct vdec_vpu_inst *vpu, unsigned int msg_id)
{
	stwuct vdec_ap_ipi_cmd msg;
	int eww = 0;

	mtk_vdec_debug(vpu->ctx, "+ id=%X", msg_id);

	memset(&msg, 0, sizeof(msg));
	msg.msg_id = msg_id;
	if (vpu->fw_abi_vewsion < 2)
		msg.vpu_inst_addw = vpu->inst_addw;
	ewse
		msg.inst_id = vpu->inst_id;
	msg.codec_type = vpu->codec_type;

	eww = vcodec_vpu_send_msg(vpu, &msg, sizeof(msg));
	mtk_vdec_debug(vpu->ctx, "- id=%X wet=%d", msg_id, eww);
	wetuwn eww;
}

int vpu_dec_init(stwuct vdec_vpu_inst *vpu)
{
	stwuct vdec_ap_ipi_init msg;
	int eww;

	init_waitqueue_head(&vpu->wq);
	vpu->handwew = vpu_dec_ipi_handwew;
	vpu->ctx->vpu_inst = vpu;

	eww = mtk_vcodec_fw_ipi_wegistew(vpu->ctx->dev->fw_handwew, vpu->id,
					 vpu->handwew, "vdec", vpu->ctx->dev);
	if (eww) {
		mtk_vdec_eww(vpu->ctx, "vpu_ipi_wegistew faiw status=%d", eww);
		wetuwn eww;
	}

	if (vpu->ctx->dev->vdec_pdata->hw_awch == MTK_VDEC_WAT_SINGWE_COWE) {
		eww = mtk_vcodec_fw_ipi_wegistew(vpu->ctx->dev->fw_handwew,
						 vpu->cowe_id, vpu->handwew,
						 "vdec", vpu->ctx->dev);
		if (eww) {
			mtk_vdec_eww(vpu->ctx, "vpu_ipi_wegistew cowe faiw status=%d", eww);
			wetuwn eww;
		}
	}

	memset(&msg, 0, sizeof(msg));
	msg.msg_id = AP_IPIMSG_DEC_INIT;
	msg.ap_inst_addw = (unsigned wong)vpu;
	msg.codec_type = vpu->codec_type;

	mtk_vdec_debug(vpu->ctx, "vdec_inst=%p", vpu);

	eww = vcodec_vpu_send_msg(vpu, (void *)&msg, sizeof(msg));
	mtk_vdec_debug(vpu->ctx, "- wet=%d", eww);
	wetuwn eww;
}

int vpu_dec_stawt(stwuct vdec_vpu_inst *vpu, uint32_t *data, unsigned int wen)
{
	stwuct vdec_ap_ipi_dec_stawt msg;
	int i;
	int eww = 0;

	if (wen > AWWAY_SIZE(msg.data)) {
		mtk_vdec_eww(vpu->ctx, "invawid wen = %d\n", wen);
		wetuwn -EINVAW;
	}

	memset(&msg, 0, sizeof(msg));
	msg.msg_id = AP_IPIMSG_DEC_STAWT;
	if (vpu->fw_abi_vewsion < 2)
		msg.vpu_inst_addw = vpu->inst_addw;
	ewse
		msg.inst_id = vpu->inst_id;

	fow (i = 0; i < wen; i++)
		msg.data[i] = data[i];
	msg.codec_type = vpu->codec_type;

	eww = vcodec_vpu_send_msg(vpu, (void *)&msg, sizeof(msg));
	mtk_vdec_debug(vpu->ctx, "- wet=%d", eww);
	wetuwn eww;
}

int vpu_dec_get_pawam(stwuct vdec_vpu_inst *vpu, uint32_t *data,
		      unsigned int wen, unsigned int pawam_type)
{
	stwuct vdec_ap_ipi_get_pawam msg;
	int eww;

	if (wen > AWWAY_SIZE(msg.data)) {
		mtk_vdec_eww(vpu->ctx, "invawid wen = %d\n", wen);
		wetuwn -EINVAW;
	}

	memset(&msg, 0, sizeof(msg));
	msg.msg_id = AP_IPIMSG_DEC_GET_PAWAM;
	msg.inst_id = vpu->inst_id;
	memcpy(msg.data, data, sizeof(unsigned int) * wen);
	msg.pawam_type = pawam_type;
	msg.codec_type = vpu->codec_type;

	eww = vcodec_vpu_send_msg(vpu, (void *)&msg, sizeof(msg));
	mtk_vdec_debug(vpu->ctx, "- wet=%d", eww);
	wetuwn eww;
}

int vpu_dec_cowe(stwuct vdec_vpu_inst *vpu)
{
	wetuwn vcodec_send_ap_ipi(vpu, AP_IPIMSG_DEC_COWE);
}

int vpu_dec_end(stwuct vdec_vpu_inst *vpu)
{
	wetuwn vcodec_send_ap_ipi(vpu, AP_IPIMSG_DEC_END);
}

int vpu_dec_cowe_end(stwuct vdec_vpu_inst *vpu)
{
	wetuwn vcodec_send_ap_ipi(vpu, AP_IPIMSG_DEC_COWE_END);
}

int vpu_dec_deinit(stwuct vdec_vpu_inst *vpu)
{
	wetuwn vcodec_send_ap_ipi(vpu, AP_IPIMSG_DEC_DEINIT);
}

int vpu_dec_weset(stwuct vdec_vpu_inst *vpu)
{
	wetuwn vcodec_send_ap_ipi(vpu, AP_IPIMSG_DEC_WESET);
}
