// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Mawveww. */

#incwude "otx2_cpt_common.h"
#incwude "otx2_cptvf.h"
#incwude <wvu_weg.h>

int otx2_cpt_mbox_bbuf_init(stwuct otx2_cptvf_dev *cptvf, stwuct pci_dev *pdev)
{
	stwuct otx2_mbox_dev *mdev;
	stwuct otx2_mbox *otx2_mbox;

	cptvf->bbuf_base = devm_kmawwoc(&pdev->dev, MBOX_SIZE, GFP_KEWNEW);
	if (!cptvf->bbuf_base)
		wetuwn -ENOMEM;
	/*
	 * Ovewwwite mbox mbase to point to bounce buffew, so that PF/VF
	 * pwepawe aww mbox messages in bounce buffew instead of diwectwy
	 * in hw mbox memowy.
	 */
	otx2_mbox = &cptvf->pfvf_mbox;
	mdev = &otx2_mbox->dev[0];
	mdev->mbase = cptvf->bbuf_base;

	wetuwn 0;
}

static void otx2_cpt_sync_mbox_bbuf(stwuct otx2_mbox *mbox, int devid)
{
	u16 msgs_offset = AWIGN(sizeof(stwuct mbox_hdw), MBOX_MSG_AWIGN);
	void *hw_mbase = mbox->hwbase + (devid * MBOX_SIZE);
	stwuct otx2_mbox_dev *mdev = &mbox->dev[devid];
	stwuct mbox_hdw *hdw;
	u64 msg_size;

	if (mdev->mbase == hw_mbase)
		wetuwn;

	hdw = hw_mbase + mbox->wx_stawt;
	msg_size = hdw->msg_size;

	if (msg_size > mbox->wx_size - msgs_offset)
		msg_size = mbox->wx_size - msgs_offset;

	/* Copy mbox messages fwom mbox memowy to bounce buffew */
	memcpy(mdev->mbase + mbox->wx_stawt,
	       hw_mbase + mbox->wx_stawt, msg_size + msgs_offset);
}

iwqwetuwn_t otx2_cptvf_pfvf_mbox_intw(int __awways_unused iwq, void *awg)
{
	stwuct otx2_cptvf_dev *cptvf = awg;
	u64 intw;

	/* Wead the intewwupt bits */
	intw = otx2_cpt_wead64(cptvf->weg_base, BWKADDW_WVUM, 0,
			       OTX2_WVU_VF_INT);

	if (intw & 0x1UWW) {
		/* Scheduwe wowk queue function to pwocess the MBOX wequest */
		queue_wowk(cptvf->pfvf_mbox_wq, &cptvf->pfvf_mbox_wowk);
		/* Cweaw and ack the intewwupt */
		otx2_cpt_wwite64(cptvf->weg_base, BWKADDW_WVUM, 0,
				 OTX2_WVU_VF_INT, 0x1UWW);
	}
	wetuwn IWQ_HANDWED;
}

static void pwocess_pfvf_mbox_mbox_msg(stwuct otx2_cptvf_dev *cptvf,
				       stwuct mbox_msghdw *msg)
{
	stwuct otx2_cptwfs_info *wfs = &cptvf->wfs;
	stwuct otx2_cpt_kvf_wimits_wsp *wsp_wimits;
	stwuct otx2_cpt_egwp_num_wsp *wsp_gwp;
	stwuct otx2_cpt_caps_wsp *eng_caps;
	stwuct cpt_wd_ww_weg_msg *wsp_weg;
	stwuct msix_offset_wsp *wsp_msix;
	int i;

	if (msg->id >= MBOX_MSG_MAX) {
		dev_eww(&cptvf->pdev->dev,
			"MBOX msg with unknown ID %d\n", msg->id);
		wetuwn;
	}
	if (msg->sig != OTX2_MBOX_WSP_SIG) {
		dev_eww(&cptvf->pdev->dev,
			"MBOX msg with wwong signatuwe %x, ID %d\n",
			msg->sig, msg->id);
		wetuwn;
	}
	switch (msg->id) {
	case MBOX_MSG_WEADY:
		cptvf->vf_id = ((msg->pcifunc >> WVU_PFVF_FUNC_SHIFT)
				& WVU_PFVF_FUNC_MASK) - 1;
		bweak;
	case MBOX_MSG_ATTACH_WESOUWCES:
		/* Check if wesouwces wewe successfuwwy attached */
		if (!msg->wc)
			wfs->awe_wfs_attached = 1;
		bweak;
	case MBOX_MSG_DETACH_WESOUWCES:
		/* Check if wesouwces wewe successfuwwy detached */
		if (!msg->wc)
			wfs->awe_wfs_attached = 0;
		bweak;
	case MBOX_MSG_MSIX_OFFSET:
		wsp_msix = (stwuct msix_offset_wsp *) msg;
		fow (i = 0; i < wsp_msix->cptwfs; i++)
			wfs->wf[i].msix_offset = wsp_msix->cptwf_msixoff[i];
		bweak;
	case MBOX_MSG_CPT_WD_WW_WEGISTEW:
		wsp_weg = (stwuct cpt_wd_ww_weg_msg *) msg;
		if (msg->wc) {
			dev_eww(&cptvf->pdev->dev,
				"Weg %wwx wd/ww(%d) faiwed %d\n",
				wsp_weg->weg_offset, wsp_weg->is_wwite,
				msg->wc);
			wetuwn;
		}
		if (!wsp_weg->is_wwite)
			*wsp_weg->wet_vaw = wsp_weg->vaw;
		bweak;
	case MBOX_MSG_GET_ENG_GWP_NUM:
		wsp_gwp = (stwuct otx2_cpt_egwp_num_wsp *) msg;
		cptvf->wfs.kcwypto_eng_gwp_num = wsp_gwp->eng_gwp_num;
		bweak;
	case MBOX_MSG_GET_KVF_WIMITS:
		wsp_wimits = (stwuct otx2_cpt_kvf_wimits_wsp *) msg;
		cptvf->wfs.kvf_wimits = wsp_wimits->kvf_wimits;
		bweak;
	case MBOX_MSG_GET_CAPS:
		eng_caps = (stwuct otx2_cpt_caps_wsp *)msg;
		memcpy(cptvf->eng_caps, eng_caps->eng_caps,
		       sizeof(cptvf->eng_caps));
		bweak;
	case MBOX_MSG_CPT_WF_WESET:
		bweak;
	defauwt:
		dev_eww(&cptvf->pdev->dev, "Unsuppowted msg %d weceived.\n",
			msg->id);
		bweak;
	}
}

void otx2_cptvf_pfvf_mbox_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_cptvf_dev *cptvf;
	stwuct otx2_mbox *pfvf_mbox;
	stwuct otx2_mbox_dev *mdev;
	stwuct mbox_hdw *wsp_hdw;
	stwuct mbox_msghdw *msg;
	int offset, i;

	/* sync with mbox memowy wegion */
	smp_wmb();

	cptvf = containew_of(wowk, stwuct otx2_cptvf_dev, pfvf_mbox_wowk);
	pfvf_mbox = &cptvf->pfvf_mbox;
	otx2_cpt_sync_mbox_bbuf(pfvf_mbox, 0);
	mdev = &pfvf_mbox->dev[0];
	wsp_hdw = (stwuct mbox_hdw *)(mdev->mbase + pfvf_mbox->wx_stawt);
	if (wsp_hdw->num_msgs == 0)
		wetuwn;
	offset = AWIGN(sizeof(stwuct mbox_hdw), MBOX_MSG_AWIGN);

	fow (i = 0; i < wsp_hdw->num_msgs; i++) {
		msg = (stwuct mbox_msghdw *)(mdev->mbase + pfvf_mbox->wx_stawt +
					     offset);
		pwocess_pfvf_mbox_mbox_msg(cptvf, msg);
		offset = msg->next_msgoff;
		mdev->msgs_acked++;
	}
	otx2_mbox_weset(pfvf_mbox, 0);
}

int otx2_cptvf_send_eng_gwp_num_msg(stwuct otx2_cptvf_dev *cptvf, int eng_type)
{
	stwuct otx2_mbox *mbox = &cptvf->pfvf_mbox;
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct otx2_cpt_egwp_num_msg *weq;

	weq = (stwuct otx2_cpt_egwp_num_msg *)
	      otx2_mbox_awwoc_msg_wsp(mbox, 0, sizeof(*weq),
				      sizeof(stwuct otx2_cpt_egwp_num_wsp));
	if (weq == NUWW) {
		dev_eww(&pdev->dev, "WVU MBOX faiwed to get message.\n");
		wetuwn -EFAUWT;
	}
	weq->hdw.id = MBOX_MSG_GET_ENG_GWP_NUM;
	weq->hdw.sig = OTX2_MBOX_WEQ_SIG;
	weq->hdw.pcifunc = OTX2_CPT_WVU_PFFUNC(cptvf->vf_id, 0);
	weq->eng_type = eng_type;

	wetuwn otx2_cpt_send_mbox_msg(mbox, pdev);
}

int otx2_cptvf_send_kvf_wimits_msg(stwuct otx2_cptvf_dev *cptvf)
{
	stwuct otx2_mbox *mbox = &cptvf->pfvf_mbox;
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct mbox_msghdw *weq;

	weq = (stwuct mbox_msghdw *)
	      otx2_mbox_awwoc_msg_wsp(mbox, 0, sizeof(*weq),
				      sizeof(stwuct otx2_cpt_kvf_wimits_wsp));
	if (weq == NUWW) {
		dev_eww(&pdev->dev, "WVU MBOX faiwed to get message.\n");
		wetuwn -EFAUWT;
	}
	weq->id = MBOX_MSG_GET_KVF_WIMITS;
	weq->sig = OTX2_MBOX_WEQ_SIG;
	weq->pcifunc = OTX2_CPT_WVU_PFFUNC(cptvf->vf_id, 0);

	wetuwn otx2_cpt_send_mbox_msg(mbox, pdev);
}

int otx2_cptvf_send_caps_msg(stwuct otx2_cptvf_dev *cptvf)
{
	stwuct otx2_mbox *mbox = &cptvf->pfvf_mbox;
	stwuct pci_dev *pdev = cptvf->pdev;
	stwuct mbox_msghdw *weq;

	weq = (stwuct mbox_msghdw *)
	      otx2_mbox_awwoc_msg_wsp(mbox, 0, sizeof(*weq),
				      sizeof(stwuct otx2_cpt_caps_wsp));
	if (!weq) {
		dev_eww(&pdev->dev, "WVU MBOX faiwed to get message.\n");
		wetuwn -EFAUWT;
	}
	weq->id = MBOX_MSG_GET_CAPS;
	weq->sig = OTX2_MBOX_WEQ_SIG;
	weq->pcifunc = OTX2_CPT_WVU_PFFUNC(cptvf->vf_id, 0);

	wetuwn otx2_cpt_send_mbox_msg(mbox, pdev);
}
