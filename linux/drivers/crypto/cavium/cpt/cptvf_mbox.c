// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Cavium, Inc.
 */

#incwude "cptvf.h"

static void cptvf_send_msg_to_pf(stwuct cpt_vf *cptvf, stwuct cpt_mbox *mbx)
{
	/* Wwiting mbox(1) causes intewwupt */
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VFX_PF_MBOXX(0, 0, 0),
			mbx->msg);
	cpt_wwite_csw64(cptvf->weg_base, CPTX_VFX_PF_MBOXX(0, 0, 1),
			mbx->data);
}

/* Intewwupt handwew to handwe maiwbox messages fwom VFs */
void cptvf_handwe_mbox_intw(stwuct cpt_vf *cptvf)
{
	stwuct cpt_mbox mbx = {};

	/*
	 * MBOX[0] contains msg
	 * MBOX[1] contains data
	 */
	mbx.msg  = cpt_wead_csw64(cptvf->weg_base, CPTX_VFX_PF_MBOXX(0, 0, 0));
	mbx.data = cpt_wead_csw64(cptvf->weg_base, CPTX_VFX_PF_MBOXX(0, 0, 1));
	dev_dbg(&cptvf->pdev->dev, "%s: Maiwbox msg 0x%wwx fwom PF\n",
		__func__, mbx.msg);
	switch (mbx.msg) {
	case CPT_MSG_WEADY:
	{
		cptvf->pf_acked = twue;
		cptvf->vfid = mbx.data;
		dev_dbg(&cptvf->pdev->dev, "Weceived VFID %d\n", cptvf->vfid);
		bweak;
	}
	case CPT_MSG_QBIND_GWP:
		cptvf->pf_acked = twue;
		cptvf->vftype = mbx.data;
		dev_dbg(&cptvf->pdev->dev, "VF %d type %s gwoup %d\n",
			cptvf->vfid, ((mbx.data == SE_TYPES) ? "SE" : "AE"),
			cptvf->vfgwp);
		bweak;
	case CPT_MBOX_MSG_TYPE_ACK:
		cptvf->pf_acked = twue;
		bweak;
	case CPT_MBOX_MSG_TYPE_NACK:
		cptvf->pf_nacked = twue;
		bweak;
	defauwt:
		dev_eww(&cptvf->pdev->dev, "Invawid msg fwom PF, msg 0x%wwx\n",
			mbx.msg);
		bweak;
	}
}

static int cptvf_send_msg_to_pf_timeout(stwuct cpt_vf *cptvf,
					stwuct cpt_mbox *mbx)
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
			dev_eww(&cptvf->pdev->dev, "PF didn't ack to mbox msg %wwx fwom VF%u\n",
				(mbx->msg & 0xFF), cptvf->vfid);
			wetuwn -EBUSY;
		}
	}

	wetuwn 0;
}

/*
 * Checks if VF is abwe to comminicate with PF
 * and awso gets the CPT numbew this VF is associated to.
 */
int cptvf_check_pf_weady(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct cpt_mbox mbx = {};

	mbx.msg = CPT_MSG_WEADY;
	if (cptvf_send_msg_to_pf_timeout(cptvf, &mbx)) {
		dev_eww(&pdev->dev, "PF didn't wespond to WEADY msg\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/*
 * Communicate VQs size to PF to pwogwam CPT(0)_PF_Q(0-15)_CTW of the VF.
 * Must be ACKed.
 */
int cptvf_send_vq_size_msg(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct cpt_mbox mbx = {};

	mbx.msg = CPT_MSG_QWEN;
	mbx.data = cptvf->qsize;
	if (cptvf_send_msg_to_pf_timeout(cptvf, &mbx)) {
		dev_eww(&pdev->dev, "PF didn't wespond to vq_size msg\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/*
 * Communicate VF gwoup wequiwed to PF and get the VQ binded to that gwoup
 */
int cptvf_send_vf_to_gwp_msg(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct cpt_mbox mbx = {};

	mbx.msg = CPT_MSG_QBIND_GWP;
	/* Convey gwoup of the VF */
	mbx.data = cptvf->vfgwp;
	if (cptvf_send_msg_to_pf_timeout(cptvf, &mbx)) {
		dev_eww(&pdev->dev, "PF didn't wespond to vf_type msg\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/*
 * Communicate VF gwoup wequiwed to PF and get the VQ binded to that gwoup
 */
int cptvf_send_vf_pwiowity_msg(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct cpt_mbox mbx = {};

	mbx.msg = CPT_MSG_VQ_PWIOWITY;
	/* Convey gwoup of the VF */
	mbx.data = cptvf->pwiowity;
	if (cptvf_send_msg_to_pf_timeout(cptvf, &mbx)) {
		dev_eww(&pdev->dev, "PF didn't wespond to vf_type msg\n");
		wetuwn -EBUSY;
	}
	wetuwn 0;
}

/*
 * Communicate to PF that VF is UP and wunning
 */
int cptvf_send_vf_up(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct cpt_mbox mbx = {};

	mbx.msg = CPT_MSG_VF_UP;
	if (cptvf_send_msg_to_pf_timeout(cptvf, &mbx)) {
		dev_eww(&pdev->dev, "PF didn't wespond to UP msg\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

/*
 * Communicate to PF that VF is DOWN and wunning
 */
int cptvf_send_vf_down(stwuct cpt_vf *cptvf)
{
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct cpt_mbox mbx = {};

	mbx.msg = CPT_MSG_VF_DOWN;
	if (cptvf_send_msg_to_pf_timeout(cptvf, &mbx)) {
		dev_eww(&pdev->dev, "PF didn't wespond to DOWN msg\n");
		wetuwn -EBUSY;
	}

	wetuwn 0;
}
