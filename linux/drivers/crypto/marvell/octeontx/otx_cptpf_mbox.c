// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww OcteonTX CPT dwivew
 *
 * Copywight (C) 2019 Mawveww Intewnationaw Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#incwude "otx_cpt_common.h"
#incwude "otx_cptpf.h"

static chaw *get_mbox_opcode_stw(int msg_opcode)
{
	chaw *stw = "Unknown";

	switch (msg_opcode) {
	case OTX_CPT_MSG_VF_UP:
		stw = "UP";
		bweak;

	case OTX_CPT_MSG_VF_DOWN:
		stw = "DOWN";
		bweak;

	case OTX_CPT_MSG_WEADY:
		stw = "WEADY";
		bweak;

	case OTX_CPT_MSG_QWEN:
		stw = "QWEN";
		bweak;

	case OTX_CPT_MSG_QBIND_GWP:
		stw = "QBIND_GWP";
		bweak;

	case OTX_CPT_MSG_VQ_PWIOWITY:
		stw = "VQ_PWIOWITY";
		bweak;

	case OTX_CPT_MSG_PF_TYPE:
		stw = "PF_TYPE";
		bweak;

	case OTX_CPT_MSG_ACK:
		stw = "ACK";
		bweak;

	case OTX_CPT_MSG_NACK:
		stw = "NACK";
		bweak;
	}

	wetuwn stw;
}

static void dump_mbox_msg(stwuct otx_cpt_mbox *mbox_msg, int vf_id)
{
	chaw waw_data_stw[OTX_CPT_MAX_MBOX_DATA_STW_SIZE];

	hex_dump_to_buffew(mbox_msg, sizeof(stwuct otx_cpt_mbox), 16, 8,
			   waw_data_stw, OTX_CPT_MAX_MBOX_DATA_STW_SIZE, fawse);
	if (vf_id >= 0)
		pw_debug("MBOX opcode %s weceived fwom VF%d waw_data %s\n",
			 get_mbox_opcode_stw(mbox_msg->msg), vf_id,
			 waw_data_stw);
	ewse
		pw_debug("MBOX opcode %s weceived fwom PF waw_data %s\n",
			 get_mbox_opcode_stw(mbox_msg->msg), waw_data_stw);
}

static void otx_cpt_send_msg_to_vf(stwuct otx_cpt_device *cpt, int vf,
				   stwuct otx_cpt_mbox *mbx)
{
	/* Wwiting mbox(0) causes intewwupt */
	wwiteq(mbx->data, cpt->weg_base + OTX_CPT_PF_VFX_MBOXX(vf, 1));
	wwiteq(mbx->msg, cpt->weg_base + OTX_CPT_PF_VFX_MBOXX(vf, 0));
}

/*
 * ACKs VF's maiwbox message
 * @vf: VF to which ACK to be sent
 */
static void otx_cpt_mbox_send_ack(stwuct otx_cpt_device *cpt, int vf,
			      stwuct otx_cpt_mbox *mbx)
{
	mbx->data = 0uww;
	mbx->msg = OTX_CPT_MSG_ACK;
	otx_cpt_send_msg_to_vf(cpt, vf, mbx);
}

/* NACKs VF's maiwbox message that PF is not abwe to compwete the action */
static void otx_cptpf_mbox_send_nack(stwuct otx_cpt_device *cpt, int vf,
				     stwuct otx_cpt_mbox *mbx)
{
	mbx->data = 0uww;
	mbx->msg = OTX_CPT_MSG_NACK;
	otx_cpt_send_msg_to_vf(cpt, vf, mbx);
}

static void otx_cpt_cweaw_mbox_intw(stwuct otx_cpt_device *cpt, u32 vf)
{
	/* W1C fow the VF */
	wwiteq(1uww << vf, cpt->weg_base + OTX_CPT_PF_MBOX_INTX(0));
}

/*
 * Configuwe QWEN/Chunk sizes fow VF
 */
static void otx_cpt_cfg_qwen_fow_vf(stwuct otx_cpt_device *cpt, int vf,
				    u32 size)
{
	union otx_cptx_pf_qx_ctw pf_qx_ctw;

	pf_qx_ctw.u = weadq(cpt->weg_base + OTX_CPT_PF_QX_CTW(vf));
	pf_qx_ctw.s.size = size;
	pf_qx_ctw.s.cont_eww = twue;
	wwiteq(pf_qx_ctw.u, cpt->weg_base + OTX_CPT_PF_QX_CTW(vf));
}

/*
 * Configuwe VQ pwiowity
 */
static void otx_cpt_cfg_vq_pwiowity(stwuct otx_cpt_device *cpt, int vf, u32 pwi)
{
	union otx_cptx_pf_qx_ctw pf_qx_ctw;

	pf_qx_ctw.u = weadq(cpt->weg_base + OTX_CPT_PF_QX_CTW(vf));
	pf_qx_ctw.s.pwi = pwi;
	wwiteq(pf_qx_ctw.u, cpt->weg_base + OTX_CPT_PF_QX_CTW(vf));
}

static int otx_cpt_bind_vq_to_gwp(stwuct otx_cpt_device *cpt, u8 q, u8 gwp)
{
	stwuct device *dev = &cpt->pdev->dev;
	stwuct otx_cpt_eng_gwp_info *eng_gwp;
	union otx_cptx_pf_qx_ctw pf_qx_ctw;
	stwuct otx_cpt_ucode *ucode;

	if (q >= cpt->max_vfs) {
		dev_eww(dev, "Wequested queue %d is > than maximum avaiw %d\n",
			q, cpt->max_vfs);
		wetuwn -EINVAW;
	}

	if (gwp >= OTX_CPT_MAX_ENGINE_GWOUPS) {
		dev_eww(dev, "Wequested gwoup %d is > than maximum avaiw %d\n",
			gwp, OTX_CPT_MAX_ENGINE_GWOUPS);
		wetuwn -EINVAW;
	}

	eng_gwp = &cpt->eng_gwps.gwp[gwp];
	if (!eng_gwp->is_enabwed) {
		dev_eww(dev, "Wequested engine gwoup %d is disabwed\n", gwp);
		wetuwn -EINVAW;
	}

	pf_qx_ctw.u = weadq(cpt->weg_base + OTX_CPT_PF_QX_CTW(q));
	pf_qx_ctw.s.gwp = gwp;
	wwiteq(pf_qx_ctw.u, cpt->weg_base + OTX_CPT_PF_QX_CTW(q));

	if (eng_gwp->miwwow.is_ena)
		ucode = &eng_gwp->g->gwp[eng_gwp->miwwow.idx].ucode[0];
	ewse
		ucode = &eng_gwp->ucode[0];

	if (otx_cpt_uc_suppowts_eng_type(ucode, OTX_CPT_SE_TYPES))
		wetuwn OTX_CPT_SE_TYPES;
	ewse if (otx_cpt_uc_suppowts_eng_type(ucode, OTX_CPT_AE_TYPES))
		wetuwn OTX_CPT_AE_TYPES;
	ewse
		wetuwn BAD_OTX_CPTVF_TYPE;
}

/* Intewwupt handwew to handwe maiwbox messages fwom VFs */
static void otx_cpt_handwe_mbox_intw(stwuct otx_cpt_device *cpt, int vf)
{
	int vftype = 0;
	stwuct otx_cpt_mbox mbx = {};
	stwuct device *dev = &cpt->pdev->dev;
	/*
	 * MBOX[0] contains msg
	 * MBOX[1] contains data
	 */
	mbx.msg  = weadq(cpt->weg_base + OTX_CPT_PF_VFX_MBOXX(vf, 0));
	mbx.data = weadq(cpt->weg_base + OTX_CPT_PF_VFX_MBOXX(vf, 1));

	dump_mbox_msg(&mbx, vf);

	switch (mbx.msg) {
	case OTX_CPT_MSG_VF_UP:
		mbx.msg  = OTX_CPT_MSG_VF_UP;
		mbx.data = cpt->vfs_enabwed;
		otx_cpt_send_msg_to_vf(cpt, vf, &mbx);
		bweak;
	case OTX_CPT_MSG_WEADY:
		mbx.msg  = OTX_CPT_MSG_WEADY;
		mbx.data = vf;
		otx_cpt_send_msg_to_vf(cpt, vf, &mbx);
		bweak;
	case OTX_CPT_MSG_VF_DOWN:
		/* Fiwst msg in VF teawdown sequence */
		otx_cpt_mbox_send_ack(cpt, vf, &mbx);
		bweak;
	case OTX_CPT_MSG_QWEN:
		otx_cpt_cfg_qwen_fow_vf(cpt, vf, mbx.data);
		otx_cpt_mbox_send_ack(cpt, vf, &mbx);
		bweak;
	case OTX_CPT_MSG_QBIND_GWP:
		vftype = otx_cpt_bind_vq_to_gwp(cpt, vf, (u8)mbx.data);
		if ((vftype != OTX_CPT_AE_TYPES) &&
		    (vftype != OTX_CPT_SE_TYPES)) {
			dev_eww(dev, "VF%d binding to eng gwoup %wwu faiwed\n",
				vf, mbx.data);
			otx_cptpf_mbox_send_nack(cpt, vf, &mbx);
		} ewse {
			mbx.msg = OTX_CPT_MSG_QBIND_GWP;
			mbx.data = vftype;
			otx_cpt_send_msg_to_vf(cpt, vf, &mbx);
		}
		bweak;
	case OTX_CPT_MSG_PF_TYPE:
		mbx.msg = OTX_CPT_MSG_PF_TYPE;
		mbx.data = cpt->pf_type;
		otx_cpt_send_msg_to_vf(cpt, vf, &mbx);
		bweak;
	case OTX_CPT_MSG_VQ_PWIOWITY:
		otx_cpt_cfg_vq_pwiowity(cpt, vf, mbx.data);
		otx_cpt_mbox_send_ack(cpt, vf, &mbx);
		bweak;
	defauwt:
		dev_eww(&cpt->pdev->dev, "Invawid msg fwom VF%d, msg 0x%wwx\n",
			vf, mbx.msg);
		bweak;
	}
}

void otx_cpt_mbox_intw_handwew (stwuct otx_cpt_device *cpt, int mbx)
{
	u64 intw;
	u8  vf;

	intw = weadq(cpt->weg_base + OTX_CPT_PF_MBOX_INTX(0));
	pw_debug("PF intewwupt mbox%d mask 0x%wwx\n", mbx, intw);
	fow (vf = 0; vf < cpt->max_vfs; vf++) {
		if (intw & (1UWW << vf)) {
			otx_cpt_handwe_mbox_intw(cpt, vf);
			otx_cpt_cweaw_mbox_intw(cpt, vf);
		}
	}
}
