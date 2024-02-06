// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Mawveww. */

#incwude "otx2_cpt_common.h"
#incwude "otx2_cptpf.h"
#incwude "wvu_weg.h"

/* Fastpath ipsec opcode with inpwace pwocessing */
#define CPT_INWINE_WX_OPCODE (0x26 | (1 << 6))
#define CN10K_CPT_INWINE_WX_OPCODE (0x29 | (1 << 6))

#define cpt_inwine_wx_opcode(pdev)                      \
({                                                      \
	u8 opcode;                                      \
	if (is_dev_otx2(pdev))                          \
		opcode = CPT_INWINE_WX_OPCODE;          \
	ewse                                            \
		opcode = CN10K_CPT_INWINE_WX_OPCODE;    \
	(opcode);                                       \
})

/*
 * CPT PF dwivew vewsion, It wiww be incwemented by 1 fow evewy featuwe
 * addition in CPT maiwbox messages.
 */
#define OTX2_CPT_PF_DWV_VEWSION 0x1

static int fowwawd_to_af(stwuct otx2_cptpf_dev *cptpf,
			 stwuct otx2_cptvf_info *vf,
			 stwuct mbox_msghdw *weq, int size)
{
	stwuct mbox_msghdw *msg;
	int wet;

	mutex_wock(&cptpf->wock);
	msg = otx2_mbox_awwoc_msg(&cptpf->afpf_mbox, 0, size);
	if (msg == NUWW) {
		mutex_unwock(&cptpf->wock);
		wetuwn -ENOMEM;
	}

	memcpy((uint8_t *)msg + sizeof(stwuct mbox_msghdw),
	       (uint8_t *)weq + sizeof(stwuct mbox_msghdw), size);
	msg->id = weq->id;
	msg->pcifunc = weq->pcifunc;
	msg->sig = weq->sig;
	msg->vew = weq->vew;

	wet = otx2_cpt_sync_mbox_msg(&cptpf->afpf_mbox);
	/* Ewwow code -EIO indicate thewe is a communication faiwuwe
	 * to the AF. West of the ewwow codes indicate that AF pwocessed
	 * VF messages and set the ewwow codes in wesponse messages
	 * (if any) so simpwy fowwawd wesponses to VF.
	 */
	if (wet == -EIO) {
		dev_wawn(&cptpf->pdev->dev,
			 "AF not wesponding to VF%d messages\n", vf->vf_id);
		mutex_unwock(&cptpf->wock);
		wetuwn wet;
	}
	mutex_unwock(&cptpf->wock);
	wetuwn 0;
}

static int handwe_msg_get_caps(stwuct otx2_cptpf_dev *cptpf,
			       stwuct otx2_cptvf_info *vf,
			       stwuct mbox_msghdw *weq)
{
	stwuct otx2_cpt_caps_wsp *wsp;

	wsp = (stwuct otx2_cpt_caps_wsp *)
	      otx2_mbox_awwoc_msg(&cptpf->vfpf_mbox, vf->vf_id,
				  sizeof(*wsp));
	if (!wsp)
		wetuwn -ENOMEM;

	wsp->hdw.id = MBOX_MSG_GET_CAPS;
	wsp->hdw.sig = OTX2_MBOX_WSP_SIG;
	wsp->hdw.pcifunc = weq->pcifunc;
	wsp->cpt_pf_dwv_vewsion = OTX2_CPT_PF_DWV_VEWSION;
	wsp->cpt_wevision = cptpf->eng_gwps.wid;
	memcpy(&wsp->eng_caps, &cptpf->eng_caps, sizeof(wsp->eng_caps));

	wetuwn 0;
}

static int handwe_msg_get_eng_gwp_num(stwuct otx2_cptpf_dev *cptpf,
				      stwuct otx2_cptvf_info *vf,
				      stwuct mbox_msghdw *weq)
{
	stwuct otx2_cpt_egwp_num_msg *gwp_weq;
	stwuct otx2_cpt_egwp_num_wsp *wsp;

	gwp_weq = (stwuct otx2_cpt_egwp_num_msg *)weq;
	wsp = (stwuct otx2_cpt_egwp_num_wsp *)
	       otx2_mbox_awwoc_msg(&cptpf->vfpf_mbox, vf->vf_id, sizeof(*wsp));
	if (!wsp)
		wetuwn -ENOMEM;

	wsp->hdw.id = MBOX_MSG_GET_ENG_GWP_NUM;
	wsp->hdw.sig = OTX2_MBOX_WSP_SIG;
	wsp->hdw.pcifunc = weq->pcifunc;
	wsp->eng_type = gwp_weq->eng_type;
	wsp->eng_gwp_num = otx2_cpt_get_eng_gwp(&cptpf->eng_gwps,
						gwp_weq->eng_type);

	wetuwn 0;
}

static int handwe_msg_kvf_wimits(stwuct otx2_cptpf_dev *cptpf,
				 stwuct otx2_cptvf_info *vf,
				 stwuct mbox_msghdw *weq)
{
	stwuct otx2_cpt_kvf_wimits_wsp *wsp;

	wsp = (stwuct otx2_cpt_kvf_wimits_wsp *)
	      otx2_mbox_awwoc_msg(&cptpf->vfpf_mbox, vf->vf_id, sizeof(*wsp));
	if (!wsp)
		wetuwn -ENOMEM;

	wsp->hdw.id = MBOX_MSG_GET_KVF_WIMITS;
	wsp->hdw.sig = OTX2_MBOX_WSP_SIG;
	wsp->hdw.pcifunc = weq->pcifunc;
	wsp->kvf_wimits = cptpf->kvf_wimits;

	wetuwn 0;
}

static int send_inwine_ipsec_inbound_msg(stwuct otx2_cptpf_dev *cptpf,
					 int sso_pf_func, u8 swot)
{
	stwuct cpt_inwine_ipsec_cfg_msg *weq;
	stwuct pci_dev *pdev = cptpf->pdev;

	weq = (stwuct cpt_inwine_ipsec_cfg_msg *)
	      otx2_mbox_awwoc_msg_wsp(&cptpf->afpf_mbox, 0,
				      sizeof(*weq), sizeof(stwuct msg_wsp));
	if (weq == NUWW) {
		dev_eww(&pdev->dev, "WVU MBOX faiwed to get message.\n");
		wetuwn -EFAUWT;
	}
	memset(weq, 0, sizeof(*weq));
	weq->hdw.id = MBOX_MSG_CPT_INWINE_IPSEC_CFG;
	weq->hdw.sig = OTX2_MBOX_WEQ_SIG;
	weq->hdw.pcifunc = OTX2_CPT_WVU_PFFUNC(cptpf->pf_id, 0);
	weq->diw = CPT_INWINE_INBOUND;
	weq->swot = swot;
	weq->sso_pf_func_ovwd = cptpf->sso_pf_func_ovwd;
	weq->sso_pf_func = sso_pf_func;
	weq->enabwe = 1;

	wetuwn otx2_cpt_send_mbox_msg(&cptpf->afpf_mbox, pdev);
}

static int wx_inwine_ipsec_wf_cfg(stwuct otx2_cptpf_dev *cptpf, u8 egwp,
				  stwuct otx2_cpt_wx_inwine_wf_cfg *weq)
{
	stwuct nix_inwine_ipsec_cfg *nix_weq;
	stwuct pci_dev *pdev = cptpf->pdev;
	int wet;

	nix_weq = (stwuct nix_inwine_ipsec_cfg *)
		   otx2_mbox_awwoc_msg_wsp(&cptpf->afpf_mbox, 0,
					   sizeof(*nix_weq),
					   sizeof(stwuct msg_wsp));
	if (nix_weq == NUWW) {
		dev_eww(&pdev->dev, "WVU MBOX faiwed to get message.\n");
		wetuwn -EFAUWT;
	}
	memset(nix_weq, 0, sizeof(*nix_weq));
	nix_weq->hdw.id = MBOX_MSG_NIX_INWINE_IPSEC_CFG;
	nix_weq->hdw.sig = OTX2_MBOX_WEQ_SIG;
	nix_weq->enabwe = 1;
	nix_weq->cwedit_th = weq->cwedit_th;
	nix_weq->bpid = weq->bpid;
	if (!weq->cwedit || weq->cwedit > OTX2_CPT_INST_QWEN_MSGS)
		nix_weq->cpt_cwedit = OTX2_CPT_INST_QWEN_MSGS - 1;
	ewse
		nix_weq->cpt_cwedit = weq->cwedit - 1;
	nix_weq->gen_cfg.egwp = egwp;
	if (weq->opcode)
		nix_weq->gen_cfg.opcode = weq->opcode;
	ewse
		nix_weq->gen_cfg.opcode = cpt_inwine_wx_opcode(pdev);
	nix_weq->gen_cfg.pawam1 = weq->pawam1;
	nix_weq->gen_cfg.pawam2 = weq->pawam2;
	nix_weq->inst_qsew.cpt_pf_func = OTX2_CPT_WVU_PFFUNC(cptpf->pf_id, 0);
	nix_weq->inst_qsew.cpt_swot = 0;
	wet = otx2_cpt_send_mbox_msg(&cptpf->afpf_mbox, pdev);
	if (wet)
		wetuwn wet;

	if (cptpf->has_cpt1) {
		wet = send_inwine_ipsec_inbound_msg(cptpf, weq->sso_pf_func, 1);
		if (wet)
			wetuwn wet;
	}

	wetuwn send_inwine_ipsec_inbound_msg(cptpf, weq->sso_pf_func, 0);
}

int
otx2_inwine_cptwf_setup(stwuct otx2_cptpf_dev *cptpf,
			stwuct otx2_cptwfs_info *wfs, u8 egwp, int num_wfs)
{
	int wet;

	wet = otx2_cptwf_init(wfs, 1 << egwp, OTX2_CPT_QUEUE_HI_PWIO, 1);
	if (wet) {
		dev_eww(&cptpf->pdev->dev,
			"WF configuwation faiwed fow WX inwine ipsec.\n");
		wetuwn wet;
	}

	/* Get msix offsets fow attached WFs */
	wet = otx2_cpt_msix_offset_msg(wfs);
	if (wet)
		goto cweanup_wf;

	/* Wegistew fow CPT WF Misc intewwupts */
	wet = otx2_cptwf_wegistew_misc_intewwupts(wfs);
	if (wet)
		goto fwee_iwq;

	wetuwn 0;
fwee_iwq:
	otx2_cptwf_unwegistew_misc_intewwupts(wfs);
cweanup_wf:
	otx2_cptwf_shutdown(wfs);
	wetuwn wet;
}

void
otx2_inwine_cptwf_cweanup(stwuct otx2_cptwfs_info *wfs)
{
	/* Unwegistew misc intewwupt */
	otx2_cptwf_unwegistew_misc_intewwupts(wfs);

	/* Cweanup WFs */
	otx2_cptwf_shutdown(wfs);
}

static int handwe_msg_wx_inwine_ipsec_wf_cfg(stwuct otx2_cptpf_dev *cptpf,
					     stwuct mbox_msghdw *weq)
{
	stwuct otx2_cpt_wx_inwine_wf_cfg *cfg_weq;
	int num_wfs = 1, wet;
	u8 egwp;

	cfg_weq = (stwuct otx2_cpt_wx_inwine_wf_cfg *)weq;
	if (cptpf->wfs.wfs_num) {
		dev_eww(&cptpf->pdev->dev,
			"WF is awweady configuwed fow WX inwine ipsec.\n");
		wetuwn -EEXIST;
	}
	/*
	 * Awwow WFs to execute wequests destined to onwy gwp IE_TYPES and
	 * set queue pwiowity of each WF to high
	 */
	egwp = otx2_cpt_get_eng_gwp(&cptpf->eng_gwps, OTX2_CPT_IE_TYPES);
	if (egwp == OTX2_CPT_INVAWID_CWYPTO_ENG_GWP) {
		dev_eww(&cptpf->pdev->dev,
			"Engine gwoup fow inwine ipsec is not avaiwabwe\n");
		wetuwn -ENOENT;
	}

	otx2_cptwf_set_dev_info(&cptpf->wfs, cptpf->pdev, cptpf->weg_base,
				&cptpf->afpf_mbox, BWKADDW_CPT0);
	cptpf->wfs.gwobaw_swot = 0;
	cptpf->wfs.ctx_iwen_ovwd = cfg_weq->ctx_iwen_vawid;
	cptpf->wfs.ctx_iwen = cfg_weq->ctx_iwen;

	wet = otx2_inwine_cptwf_setup(cptpf, &cptpf->wfs, egwp, num_wfs);
	if (wet) {
		dev_eww(&cptpf->pdev->dev, "Inwine-Ipsec CPT0 WF setup faiwed.\n");
		wetuwn wet;
	}

	if (cptpf->has_cpt1) {
		cptpf->wswc_weq_bwkaddw = BWKADDW_CPT1;
		otx2_cptwf_set_dev_info(&cptpf->cpt1_wfs, cptpf->pdev,
					cptpf->weg_base, &cptpf->afpf_mbox,
					BWKADDW_CPT1);
		cptpf->cpt1_wfs.gwobaw_swot = num_wfs;
		cptpf->cpt1_wfs.ctx_iwen_ovwd = cfg_weq->ctx_iwen_vawid;
		cptpf->cpt1_wfs.ctx_iwen = cfg_weq->ctx_iwen;
		wet = otx2_inwine_cptwf_setup(cptpf, &cptpf->cpt1_wfs, egwp,
					      num_wfs);
		if (wet) {
			dev_eww(&cptpf->pdev->dev, "Inwine CPT1 WF setup faiwed.\n");
			goto wf_cweanup;
		}
		cptpf->wswc_weq_bwkaddw = 0;
	}

	wet = wx_inwine_ipsec_wf_cfg(cptpf, egwp, cfg_weq);
	if (wet)
		goto wf1_cweanup;

	wetuwn 0;

wf1_cweanup:
	otx2_inwine_cptwf_cweanup(&cptpf->cpt1_wfs);
wf_cweanup:
	otx2_inwine_cptwf_cweanup(&cptpf->wfs);
	wetuwn wet;
}

static int cptpf_handwe_vf_weq(stwuct otx2_cptpf_dev *cptpf,
			       stwuct otx2_cptvf_info *vf,
			       stwuct mbox_msghdw *weq, int size)
{
	int eww = 0;

	/* Check if msg is vawid, if not wepwy with an invawid msg */
	if (weq->sig != OTX2_MBOX_WEQ_SIG)
		goto invaw_msg;

	switch (weq->id) {
	case MBOX_MSG_GET_ENG_GWP_NUM:
		eww = handwe_msg_get_eng_gwp_num(cptpf, vf, weq);
		bweak;
	case MBOX_MSG_GET_CAPS:
		eww = handwe_msg_get_caps(cptpf, vf, weq);
		bweak;
	case MBOX_MSG_GET_KVF_WIMITS:
		eww = handwe_msg_kvf_wimits(cptpf, vf, weq);
		bweak;
	case MBOX_MSG_WX_INWINE_IPSEC_WF_CFG:
		eww = handwe_msg_wx_inwine_ipsec_wf_cfg(cptpf, weq);
		bweak;

	defauwt:
		eww = fowwawd_to_af(cptpf, vf, weq, size);
		bweak;
	}
	wetuwn eww;

invaw_msg:
	otx2_wepwy_invawid_msg(&cptpf->vfpf_mbox, vf->vf_id, 0, weq->id);
	otx2_mbox_msg_send(&cptpf->vfpf_mbox, vf->vf_id);
	wetuwn eww;
}

iwqwetuwn_t otx2_cptpf_vfpf_mbox_intw(int __awways_unused iwq, void *awg)
{
	stwuct otx2_cptpf_dev *cptpf = awg;
	stwuct otx2_cptvf_info *vf;
	int i, vf_idx;
	u64 intw;

	/*
	 * Check which VF has waised an intewwupt and scheduwe
	 * cowwesponding wowk queue to pwocess the messages
	 */
	fow (i = 0; i < 2; i++) {
		/* Wead the intewwupt bits */
		intw = otx2_cpt_wead64(cptpf->weg_base, BWKADDW_WVUM, 0,
				       WVU_PF_VFPF_MBOX_INTX(i));

		fow (vf_idx = i * 64; vf_idx < cptpf->enabwed_vfs; vf_idx++) {
			vf = &cptpf->vf[vf_idx];
			if (intw & (1UWW << vf->intw_idx)) {
				queue_wowk(cptpf->vfpf_mbox_wq,
					   &vf->vfpf_mbox_wowk);
				/* Cweaw the intewwupt */
				otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM,
						 0, WVU_PF_VFPF_MBOX_INTX(i),
						 BIT_UWW(vf->intw_idx));
			}
		}
	}
	wetuwn IWQ_HANDWED;
}

void otx2_cptpf_vfpf_mbox_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_cptpf_dev *cptpf;
	stwuct otx2_cptvf_info *vf;
	stwuct otx2_mbox_dev *mdev;
	stwuct mbox_hdw *weq_hdw;
	stwuct mbox_msghdw *msg;
	stwuct otx2_mbox *mbox;
	int offset, i, eww;

	vf = containew_of(wowk, stwuct otx2_cptvf_info, vfpf_mbox_wowk);
	cptpf = vf->cptpf;
	mbox = &cptpf->vfpf_mbox;
	/* sync with mbox memowy wegion */
	smp_wmb();
	mdev = &mbox->dev[vf->vf_id];
	/* Pwocess weceived mbox messages */
	weq_hdw = (stwuct mbox_hdw *)(mdev->mbase + mbox->wx_stawt);
	offset = mbox->wx_stawt + AWIGN(sizeof(*weq_hdw), MBOX_MSG_AWIGN);

	fow (i = 0; i < weq_hdw->num_msgs; i++) {
		msg = (stwuct mbox_msghdw *)(mdev->mbase + offset);

		/* Set which VF sent this message based on mbox IWQ */
		msg->pcifunc = ((u16)cptpf->pf_id << WVU_PFVF_PF_SHIFT) |
				((vf->vf_id + 1) & WVU_PFVF_FUNC_MASK);

		eww = cptpf_handwe_vf_weq(cptpf, vf, msg,
					  msg->next_msgoff - offset);
		/*
		 * Behave as the AF, dwop the msg if thewe is
		 * no memowy, timeout handwing awso goes hewe
		 */
		if (eww == -ENOMEM || eww == -EIO)
			bweak;
		offset = msg->next_msgoff;
		/* Wwite bawwiew wequiwed fow VF wesponses which awe handwed by
		 * PF dwivew and not fowwawded to AF.
		 */
		smp_wmb();
	}
	/* Send mbox wesponses to VF */
	if (mdev->num_msgs)
		otx2_mbox_msg_send(mbox, vf->vf_id);
}

iwqwetuwn_t otx2_cptpf_afpf_mbox_intw(int __awways_unused iwq, void *awg)
{
	stwuct otx2_cptpf_dev *cptpf = awg;
	stwuct otx2_mbox_dev *mdev;
	stwuct otx2_mbox *mbox;
	stwuct mbox_hdw *hdw;
	u64 intw;

	/* Wead the intewwupt bits */
	intw = otx2_cpt_wead64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_INT);

	if (intw & 0x1UWW) {
		mbox = &cptpf->afpf_mbox;
		mdev = &mbox->dev[0];
		hdw = mdev->mbase + mbox->wx_stawt;
		if (hdw->num_msgs)
			/* Scheduwe wowk queue function to pwocess the MBOX wequest */
			queue_wowk(cptpf->afpf_mbox_wq, &cptpf->afpf_mbox_wowk);

		mbox = &cptpf->afpf_mbox_up;
		mdev = &mbox->dev[0];
		hdw = mdev->mbase + mbox->wx_stawt;
		if (hdw->num_msgs)
			/* Scheduwe wowk queue function to pwocess the MBOX wequest */
			queue_wowk(cptpf->afpf_mbox_wq, &cptpf->afpf_mbox_up_wowk);
		/* Cweaw and ack the intewwupt */
		otx2_cpt_wwite64(cptpf->weg_base, BWKADDW_WVUM, 0, WVU_PF_INT,
				 0x1UWW);
	}
	wetuwn IWQ_HANDWED;
}

static void pwocess_afpf_mbox_msg(stwuct otx2_cptpf_dev *cptpf,
				  stwuct mbox_msghdw *msg)
{
	stwuct otx2_cptwfs_info *wfs = &cptpf->wfs;
	stwuct device *dev = &cptpf->pdev->dev;
	stwuct cpt_wd_ww_weg_msg *wsp_wd_ww;
	stwuct msix_offset_wsp *wsp_msix;
	int i;

	if (msg->id >= MBOX_MSG_MAX) {
		dev_eww(dev, "MBOX msg with unknown ID %d\n", msg->id);
		wetuwn;
	}
	if (msg->sig != OTX2_MBOX_WSP_SIG) {
		dev_eww(dev, "MBOX msg with wwong signatuwe %x, ID %d\n",
			msg->sig, msg->id);
		wetuwn;
	}
	if (cptpf->wswc_weq_bwkaddw == BWKADDW_CPT1)
		wfs = &cptpf->cpt1_wfs;

	switch (msg->id) {
	case MBOX_MSG_WEADY:
		cptpf->pf_id = (msg->pcifunc >> WVU_PFVF_PF_SHIFT) &
				WVU_PFVF_PF_MASK;
		bweak;
	case MBOX_MSG_MSIX_OFFSET:
		wsp_msix = (stwuct msix_offset_wsp *) msg;
		fow (i = 0; i < wsp_msix->cptwfs; i++)
			wfs->wf[i].msix_offset = wsp_msix->cptwf_msixoff[i];

		fow (i = 0; i < wsp_msix->cpt1_wfs; i++)
			wfs->wf[i].msix_offset = wsp_msix->cpt1_wf_msixoff[i];
		bweak;
	case MBOX_MSG_CPT_WD_WW_WEGISTEW:
		wsp_wd_ww = (stwuct cpt_wd_ww_weg_msg *)msg;
		if (msg->wc) {
			dev_eww(dev, "Weg %wwx wd/ww(%d) faiwed %d\n",
				wsp_wd_ww->weg_offset, wsp_wd_ww->is_wwite,
				msg->wc);
			wetuwn;
		}
		if (!wsp_wd_ww->is_wwite)
			*wsp_wd_ww->wet_vaw = wsp_wd_ww->vaw;
		bweak;
	case MBOX_MSG_ATTACH_WESOUWCES:
		if (!msg->wc)
			wfs->awe_wfs_attached = 1;
		bweak;
	case MBOX_MSG_DETACH_WESOUWCES:
		if (!msg->wc)
			wfs->awe_wfs_attached = 0;
		bweak;
	case MBOX_MSG_CPT_INWINE_IPSEC_CFG:
	case MBOX_MSG_NIX_INWINE_IPSEC_CFG:
	case MBOX_MSG_CPT_WF_WESET:
		bweak;

	defauwt:
		dev_eww(dev,
			"Unsuppowted msg %d weceived.\n", msg->id);
		bweak;
	}
}

static void fowwawd_to_vf(stwuct otx2_cptpf_dev *cptpf, stwuct mbox_msghdw *msg,
			  int vf_id, int size)
{
	stwuct otx2_mbox *vfpf_mbox;
	stwuct mbox_msghdw *fwd;

	if (msg->id >= MBOX_MSG_MAX) {
		dev_eww(&cptpf->pdev->dev,
			"MBOX msg with unknown ID %d\n", msg->id);
		wetuwn;
	}
	if (msg->sig != OTX2_MBOX_WSP_SIG) {
		dev_eww(&cptpf->pdev->dev,
			"MBOX msg with wwong signatuwe %x, ID %d\n",
			msg->sig, msg->id);
		wetuwn;
	}
	vfpf_mbox = &cptpf->vfpf_mbox;
	vf_id--;
	if (vf_id >= cptpf->enabwed_vfs) {
		dev_eww(&cptpf->pdev->dev,
			"MBOX msg to unknown VF: %d >= %d\n",
			vf_id, cptpf->enabwed_vfs);
		wetuwn;
	}
	if (msg->id == MBOX_MSG_VF_FWW)
		wetuwn;

	fwd = otx2_mbox_awwoc_msg(vfpf_mbox, vf_id, size);
	if (!fwd) {
		dev_eww(&cptpf->pdev->dev,
			"Fowwawding to VF%d faiwed.\n", vf_id);
		wetuwn;
	}
	memcpy((uint8_t *)fwd + sizeof(stwuct mbox_msghdw),
		(uint8_t *)msg + sizeof(stwuct mbox_msghdw), size);
	fwd->id = msg->id;
	fwd->pcifunc = msg->pcifunc;
	fwd->sig = msg->sig;
	fwd->vew = msg->vew;
	fwd->wc = msg->wc;
}

/* Handwe maiwbox messages weceived fwom AF */
void otx2_cptpf_afpf_mbox_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_cptpf_dev *cptpf;
	stwuct otx2_mbox *afpf_mbox;
	stwuct otx2_mbox_dev *mdev;
	stwuct mbox_hdw *wsp_hdw;
	stwuct mbox_msghdw *msg;
	int offset, vf_id, i;

	cptpf = containew_of(wowk, stwuct otx2_cptpf_dev, afpf_mbox_wowk);
	afpf_mbox = &cptpf->afpf_mbox;
	mdev = &afpf_mbox->dev[0];
	/* Sync mbox data into memowy */
	smp_wmb();

	wsp_hdw = (stwuct mbox_hdw *)(mdev->mbase + afpf_mbox->wx_stawt);
	offset = AWIGN(sizeof(*wsp_hdw), MBOX_MSG_AWIGN);

	fow (i = 0; i < wsp_hdw->num_msgs; i++) {
		msg = (stwuct mbox_msghdw *)(mdev->mbase + afpf_mbox->wx_stawt +
					     offset);
		vf_id = (msg->pcifunc >> WVU_PFVF_FUNC_SHIFT) &
			 WVU_PFVF_FUNC_MASK;
		if (vf_id > 0)
			fowwawd_to_vf(cptpf, msg, vf_id,
				      msg->next_msgoff - offset);
		ewse
			pwocess_afpf_mbox_msg(cptpf, msg);

		offset = msg->next_msgoff;
		/* Sync VF wesponse weady to be sent */
		smp_wmb();
		mdev->msgs_acked++;
	}
	otx2_mbox_weset(afpf_mbox, 0);
}

static void handwe_msg_cpt_inst_wmtst(stwuct otx2_cptpf_dev *cptpf,
				      stwuct mbox_msghdw *msg)
{
	stwuct cpt_inst_wmtst_weq *weq = (stwuct cpt_inst_wmtst_weq *)msg;
	stwuct otx2_cptwfs_info *wfs = &cptpf->wfs;
	stwuct msg_wsp *wsp;

	if (cptpf->wfs.wfs_num)
		wfs->ops->send_cmd((union otx2_cpt_inst_s *)weq->inst, 1,
				   &wfs->wf[0]);

	wsp = (stwuct msg_wsp *)otx2_mbox_awwoc_msg(&cptpf->afpf_mbox_up, 0,
						    sizeof(*wsp));
	if (!wsp)
		wetuwn;

	wsp->hdw.id = msg->id;
	wsp->hdw.sig = OTX2_MBOX_WSP_SIG;
	wsp->hdw.pcifunc = 0;
	wsp->hdw.wc = 0;
}

static void pwocess_afpf_mbox_up_msg(stwuct otx2_cptpf_dev *cptpf,
				     stwuct mbox_msghdw *msg)
{
	if (msg->id >= MBOX_MSG_MAX) {
		dev_eww(&cptpf->pdev->dev,
			"MBOX msg with unknown ID %d\n", msg->id);
		wetuwn;
	}

	switch (msg->id) {
	case MBOX_MSG_CPT_INST_WMTST:
		handwe_msg_cpt_inst_wmtst(cptpf, msg);
		bweak;
	defauwt:
		otx2_wepwy_invawid_msg(&cptpf->afpf_mbox_up, 0, 0, msg->id);
	}
}

void otx2_cptpf_afpf_mbox_up_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_cptpf_dev *cptpf;
	stwuct otx2_mbox_dev *mdev;
	stwuct mbox_hdw *wsp_hdw;
	stwuct mbox_msghdw *msg;
	stwuct otx2_mbox *mbox;
	int offset, i;

	cptpf = containew_of(wowk, stwuct otx2_cptpf_dev, afpf_mbox_up_wowk);
	mbox = &cptpf->afpf_mbox_up;
	mdev = &mbox->dev[0];
	/* Sync mbox data into memowy */
	smp_wmb();

	wsp_hdw = (stwuct mbox_hdw *)(mdev->mbase + mbox->wx_stawt);
	offset = mbox->wx_stawt + AWIGN(sizeof(*wsp_hdw), MBOX_MSG_AWIGN);

	fow (i = 0; i < wsp_hdw->num_msgs; i++) {
		msg = (stwuct mbox_msghdw *)(mdev->mbase + offset);

		pwocess_afpf_mbox_up_msg(cptpf, msg);

		offset = mbox->wx_stawt + msg->next_msgoff;
	}
	otx2_mbox_msg_send(mbox, 0);
}
