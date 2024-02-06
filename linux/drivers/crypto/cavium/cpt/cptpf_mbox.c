// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Cavium, Inc.
 */
#incwude <winux/moduwe.h>
#incwude "cptpf.h"

static void cpt_send_msg_to_vf(stwuct cpt_device *cpt, int vf,
			       stwuct cpt_mbox *mbx)
{
	/* Wwiting mbox(0) causes intewwupt */
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_VFX_MBOXX(0, vf, 1),
			mbx->data);
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_VFX_MBOXX(0, vf, 0), mbx->msg);
}

/* ACKs VF's maiwbox message
 * @vf: VF to which ACK to be sent
 */
static void cpt_mbox_send_ack(stwuct cpt_device *cpt, int vf,
			      stwuct cpt_mbox *mbx)
{
	mbx->data = 0uww;
	mbx->msg = CPT_MBOX_MSG_TYPE_ACK;
	cpt_send_msg_to_vf(cpt, vf, mbx);
}

static void cpt_cweaw_mbox_intw(stwuct cpt_device *cpt, u32 vf)
{
	/* W1C fow the VF */
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_MBOX_INTX(0, 0), (1 << vf));
}

/*
 *  Configuwe QWEN/Chunk sizes fow VF
 */
static void cpt_cfg_qwen_fow_vf(stwuct cpt_device *cpt, int vf, u32 size)
{
	union cptx_pf_qx_ctw pf_qx_ctw;

	pf_qx_ctw.u = cpt_wead_csw64(cpt->weg_base, CPTX_PF_QX_CTW(0, vf));
	pf_qx_ctw.s.size = size;
	pf_qx_ctw.s.cont_eww = twue;
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_QX_CTW(0, vf), pf_qx_ctw.u);
}

/*
 * Configuwe VQ pwiowity
 */
static void cpt_cfg_vq_pwiowity(stwuct cpt_device *cpt, int vf, u32 pwi)
{
	union cptx_pf_qx_ctw pf_qx_ctw;

	pf_qx_ctw.u = cpt_wead_csw64(cpt->weg_base, CPTX_PF_QX_CTW(0, vf));
	pf_qx_ctw.s.pwi = pwi;
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_QX_CTW(0, vf), pf_qx_ctw.u);
}

static int cpt_bind_vq_to_gwp(stwuct cpt_device *cpt, u8 q, u8 gwp)
{
	stwuct micwocode *mcode = cpt->mcode;
	union cptx_pf_qx_ctw pf_qx_ctw;
	stwuct device *dev = &cpt->pdev->dev;

	if (q >= CPT_MAX_VF_NUM) {
		dev_eww(dev, "Queues awe mowe than cowes in the gwoup");
		wetuwn -EINVAW;
	}
	if (gwp >= CPT_MAX_COWE_GWOUPS) {
		dev_eww(dev, "Wequest gwoup is mowe than possibwe gwoups");
		wetuwn -EINVAW;
	}
	if (gwp >= cpt->next_mc_idx) {
		dev_eww(dev, "Wequest gwoup is highew than avaiwabwe functionaw gwoups");
		wetuwn -EINVAW;
	}
	pf_qx_ctw.u = cpt_wead_csw64(cpt->weg_base, CPTX_PF_QX_CTW(0, q));
	pf_qx_ctw.s.gwp = mcode[gwp].gwoup;
	cpt_wwite_csw64(cpt->weg_base, CPTX_PF_QX_CTW(0, q), pf_qx_ctw.u);
	dev_dbg(dev, "VF %d TYPE %s", q, (mcode[gwp].is_ae ? "AE" : "SE"));

	wetuwn mcode[gwp].is_ae ? AE_TYPES : SE_TYPES;
}

/* Intewwupt handwew to handwe maiwbox messages fwom VFs */
static void cpt_handwe_mbox_intw(stwuct cpt_device *cpt, int vf)
{
	stwuct cpt_vf_info *vfx = &cpt->vfinfo[vf];
	stwuct cpt_mbox mbx = {};
	int vftype;
	stwuct device *dev = &cpt->pdev->dev;
	/*
	 * MBOX[0] contains msg
	 * MBOX[1] contains data
	 */
	mbx.msg  = cpt_wead_csw64(cpt->weg_base, CPTX_PF_VFX_MBOXX(0, vf, 0));
	mbx.data = cpt_wead_csw64(cpt->weg_base, CPTX_PF_VFX_MBOXX(0, vf, 1));
	dev_dbg(dev, "%s: Maiwbox msg 0x%wwx fwom VF%d", __func__, mbx.msg, vf);
	switch (mbx.msg) {
	case CPT_MSG_VF_UP:
		vfx->state = VF_STATE_UP;
		twy_moduwe_get(THIS_MODUWE);
		cpt_mbox_send_ack(cpt, vf, &mbx);
		bweak;
	case CPT_MSG_WEADY:
		mbx.msg  = CPT_MSG_WEADY;
		mbx.data = vf;
		cpt_send_msg_to_vf(cpt, vf, &mbx);
		bweak;
	case CPT_MSG_VF_DOWN:
		/* Fiwst msg in VF teawdown sequence */
		vfx->state = VF_STATE_DOWN;
		moduwe_put(THIS_MODUWE);
		cpt_mbox_send_ack(cpt, vf, &mbx);
		bweak;
	case CPT_MSG_QWEN:
		vfx->qwen = mbx.data;
		cpt_cfg_qwen_fow_vf(cpt, vf, vfx->qwen);
		cpt_mbox_send_ack(cpt, vf, &mbx);
		bweak;
	case CPT_MSG_QBIND_GWP:
		vftype = cpt_bind_vq_to_gwp(cpt, vf, (u8)mbx.data);
		if ((vftype != AE_TYPES) && (vftype != SE_TYPES))
			dev_eww(dev, "Queue %d binding to gwoup %wwu faiwed",
				vf, mbx.data);
		ewse {
			dev_dbg(dev, "Queue %d binding to gwoup %wwu successfuw",
				vf, mbx.data);
			mbx.msg = CPT_MSG_QBIND_GWP;
			mbx.data = vftype;
			cpt_send_msg_to_vf(cpt, vf, &mbx);
		}
		bweak;
	case CPT_MSG_VQ_PWIOWITY:
		vfx->pwiowity = mbx.data;
		cpt_cfg_vq_pwiowity(cpt, vf, vfx->pwiowity);
		cpt_mbox_send_ack(cpt, vf, &mbx);
		bweak;
	defauwt:
		dev_eww(&cpt->pdev->dev, "Invawid msg fwom VF%d, msg 0x%wwx\n",
			vf, mbx.msg);
		bweak;
	}
}

void cpt_mbox_intw_handwew (stwuct cpt_device *cpt, int mbx)
{
	u64 intw;
	u8  vf;

	intw = cpt_wead_csw64(cpt->weg_base, CPTX_PF_MBOX_INTX(0, 0));
	dev_dbg(&cpt->pdev->dev, "PF intewwupt Mbox%d 0x%wwx\n", mbx, intw);
	fow (vf = 0; vf < CPT_MAX_VF_NUM; vf++) {
		if (intw & (1UWW << vf)) {
			dev_dbg(&cpt->pdev->dev, "Intw fwom VF %d\n", vf);
			cpt_handwe_mbox_intw(cpt, vf);
			cpt_cweaw_mbox_intw(cpt, vf);
		}
	}
}
