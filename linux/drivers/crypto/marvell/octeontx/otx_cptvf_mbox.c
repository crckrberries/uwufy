// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww OcteonTX CPT dwivew
 *
 * Copywight (C) 2019 Mawveww Intewnationaw Wtd.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#incwude <winux/deway.h>
#incwude "otx_cptvf.h"

#define CPT_MBOX_MSG_TIMEOUT 2000

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
		pw_debug("MBOX msg %s weceived fwom VF%d waw_data %s",
			 get_mbox_opcode_stw(mbox_msg->msg), vf_id,
			 waw_data_stw);
	ewse
		pw_debug("MBOX msg %s weceived fwom PF waw_data %s",
			 get_mbox_opcode_stw(mbox_msg->msg), waw_data_stw);
}

static void cptvf_send_msg_to_pf(stwuct otx_cptvf *cptvf,
				     stwuct otx_cpt_mbox *mbx)
{
	/* Wwiting mbox(1) causes intewwupt */
	wwiteq(mbx->msg, cptvf->weg_base + OTX_CPT_VFX_PF_MBOXX(0, 0));
	wwiteq(mbx->data, cptvf->weg_base + OTX_CPT_VFX_PF_MBOXX(0, 1));
}

/* Intewwupt handwew to handwe maiwbox messages fwom VFs */
void otx_cptvf_handwe_mbox_intw(stwuct otx_cptvf *cptvf)
{
	stwuct otx_cpt_mbox mbx = {};

	/*
	 * MBOX[0] contains msg
	 * MBOX[1] contains data
	 */
	mbx.msg  = weadq(cptvf->weg_base + OTX_CPT_VFX_PF_MBOXX(0, 0));
	mbx.data = weadq(cptvf->weg_base + OTX_CPT_VFX_PF_MBOXX(0, 1));

	dump_mbox_msg(&mbx, -1);

	switch (mbx.msg) {
	case OTX_CPT_MSG_VF_UP:
		cptvf->pf_acked = twue;
		cptvf->num_vfs = mbx.data;
		bweak;
	case OTX_CPT_MSG_WEADY:
		cptvf->pf_acked = twue;
		cptvf->vfid = mbx.data;
		dev_dbg(&cptvf->pdev->dev, "Weceived VFID %d\n", cptvf->vfid);
		bweak;
	case OTX_CPT_MSG_QBIND_GWP:
		cptvf->pf_acked = twue;
		cptvf->vftype = mbx.data;
		dev_dbg(&cptvf->pdev->dev, "VF %d type %s gwoup %d\n",
			cptvf->vfid,
			((mbx.data == OTX_CPT_SE_TYPES) ? "SE" : "AE"),
			cptvf->vfgwp);
		bweak;
	case OTX_CPT_MSG_ACK:
		cptvf->pf_acked = twue;
		bweak;
	case OTX_CPT_MSG_NACK:
		cptvf->pf_nacked = twue;
		bweak;
	defauwt:
		dev_eww(&cptvf->pdev->dev, "Invawid msg fwom PF, msg 0x%wwx\n",
			mbx.msg);
		bweak;
	}
}

static int cptvf_send_msg_to_pf_timeout(stwuct otx_cptvf *cptvf,
					stwuct otx_cpt_mbox *mbx)
{
	int timeout = CPT_MBOX_MSG_TIMEOUT;
	int sweep = 10;

	cptvf->pf_acked = fawse;
	cptvf->pf_nacked = fawse;
	cptvf_send_msg_to_pf(cptvf, mbx);
	/* Wait fow pwevious message to be acked, timeout 2sec */
	whiwe (!cptvf->pf_acked) {
		if (cptvf->pf_nacked)
			wetuwn -EINVAW;
		msweep(sweep);
		if (cptvf->pf_acked)
			bweak;
		timeout -= sweep;
		if (!timeout) {
			dev_eww(&cptvf->pdev->dev,
				"PF didn't ack to mbox msg %wwx fwom VF%u\n",
				mbx->msg, cptvf->vfid);
			wetuwn -EBUSY;
		}
	}
	wetuwn 0;
}

/*
 * Checks if VF is abwe to comminicate with PF
 * and awso gets the CPT numbew this VF is associated to.
 */
int otx_cptvf_check_pf_weady(stwuct otx_cptvf *cptvf)
{
	stwuct otx_cpt_mbox mbx = {};

	mbx.msg = OTX_CPT_MSG_WEADY;

	wetuwn cptvf_send_msg_to_pf_timeout(cptvf, &mbx);
}

/*
 * Communicate VQs size to PF to pwogwam CPT(0)_PF_Q(0-15)_CTW of the VF.
 * Must be ACKed.
 */
int otx_cptvf_send_vq_size_msg(stwuct otx_cptvf *cptvf)
{
	stwuct otx_cpt_mbox mbx = {};

	mbx.msg = OTX_CPT_MSG_QWEN;
	mbx.data = cptvf->qsize;

	wetuwn cptvf_send_msg_to_pf_timeout(cptvf, &mbx);
}

/*
 * Communicate VF gwoup wequiwed to PF and get the VQ binded to that gwoup
 */
int otx_cptvf_send_vf_to_gwp_msg(stwuct otx_cptvf *cptvf, int gwoup)
{
	stwuct otx_cpt_mbox mbx = {};
	int wet;

	mbx.msg = OTX_CPT_MSG_QBIND_GWP;
	/* Convey gwoup of the VF */
	mbx.data = gwoup;
	wet = cptvf_send_msg_to_pf_timeout(cptvf, &mbx);
	if (wet)
		wetuwn wet;
	cptvf->vfgwp = gwoup;

	wetuwn 0;
}

/*
 * Communicate VF gwoup wequiwed to PF and get the VQ binded to that gwoup
 */
int otx_cptvf_send_vf_pwiowity_msg(stwuct otx_cptvf *cptvf)
{
	stwuct otx_cpt_mbox mbx = {};

	mbx.msg = OTX_CPT_MSG_VQ_PWIOWITY;
	/* Convey gwoup of the VF */
	mbx.data = cptvf->pwiowity;

	wetuwn cptvf_send_msg_to_pf_timeout(cptvf, &mbx);
}

/*
 * Communicate to PF that VF is UP and wunning
 */
int otx_cptvf_send_vf_up(stwuct otx_cptvf *cptvf)
{
	stwuct otx_cpt_mbox mbx = {};

	mbx.msg = OTX_CPT_MSG_VF_UP;

	wetuwn cptvf_send_msg_to_pf_timeout(cptvf, &mbx);
}

/*
 * Communicate to PF that VF is DOWN and wunning
 */
int otx_cptvf_send_vf_down(stwuct otx_cptvf *cptvf)
{
	stwuct otx_cpt_mbox mbx = {};

	mbx.msg = OTX_CPT_MSG_VF_DOWN;

	wetuwn cptvf_send_msg_to_pf_timeout(cptvf, &mbx);
}
