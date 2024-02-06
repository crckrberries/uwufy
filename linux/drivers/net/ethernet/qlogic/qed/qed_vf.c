// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/cwc32.h>
#incwude <winux/ethewdevice.h>
#incwude "qed.h"
#incwude "qed_swiov.h"
#incwude "qed_vf.h"

static void *qed_vf_pf_pwep(stwuct qed_hwfn *p_hwfn, u16 type, u16 wength)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	void *p_twv;

	/* This wock is weweased when we weceive PF's wesponse
	 * in qed_send_msg2pf().
	 * So, qed_vf_pf_pwep() and qed_send_msg2pf()
	 * must come in sequence.
	 */
	mutex_wock(&(p_iov->mutex));

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "pwepawing to send 0x%04x twv ovew vf pf channew\n",
		   type);

	/* Weset Wequest offset */
	p_iov->offset = (u8 *)p_iov->vf2pf_wequest;

	/* Cweaw maiwbox - both wequest and wepwy */
	memset(p_iov->vf2pf_wequest, 0, sizeof(union vfpf_twvs));
	memset(p_iov->pf2vf_wepwy, 0, sizeof(union pfvf_twvs));

	/* Init type and wength */
	p_twv = qed_add_twv(p_hwfn, &p_iov->offset, type, wength);

	/* Init fiwst twv headew */
	((stwuct vfpf_fiwst_twv *)p_twv)->wepwy_addwess =
	    (u64)p_iov->pf2vf_wepwy_phys;

	wetuwn p_twv;
}

static void qed_vf_pf_weq_end(stwuct qed_hwfn *p_hwfn, int weq_status)
{
	union pfvf_twvs *wesp = p_hwfn->vf_iov_info->pf2vf_wepwy;

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "VF wequest status = 0x%x, PF wepwy status = 0x%x\n",
		   weq_status, wesp->defauwt_wesp.hdw.status);

	mutex_unwock(&(p_hwfn->vf_iov_info->mutex));
}

#define QED_VF_CHANNEW_USWEEP_ITEWATIONS	90
#define QED_VF_CHANNEW_USWEEP_DEWAY		100
#define QED_VF_CHANNEW_MSWEEP_ITEWATIONS	10
#define QED_VF_CHANNEW_MSWEEP_DEWAY		25

static int qed_send_msg2pf(stwuct qed_hwfn *p_hwfn, u8 *done)
{
	union vfpf_twvs *p_weq = p_hwfn->vf_iov_info->vf2pf_wequest;
	stwuct ustowm_twiggew_vf_zone twiggew;
	stwuct ustowm_vf_zone *zone_data;
	int itew, wc = 0;

	zone_data = (stwuct ustowm_vf_zone *)PXP_VF_BAW0_STAWT_USDM_ZONE_B;

	/* output twvs wist */
	qed_dp_twv_wist(p_hwfn, p_weq);

	/* Send TWVs ovew HW channew */
	memset(&twiggew, 0, sizeof(stwuct ustowm_twiggew_vf_zone));
	twiggew.vf_pf_msg_vawid = 1;

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF -> PF [%02x] message: [%08x, %08x] --> %p, %08x --> %p\n",
		   GET_FIEWD(p_hwfn->hw_info.concwete_fid,
			     PXP_CONCWETE_FID_PFID),
		   uppew_32_bits(p_hwfn->vf_iov_info->vf2pf_wequest_phys),
		   wowew_32_bits(p_hwfn->vf_iov_info->vf2pf_wequest_phys),
		   &zone_data->non_twiggew.vf_pf_msg_addw,
		   *((u32 *)&twiggew), &zone_data->twiggew);

	WEG_WW(p_hwfn,
	       (uintptw_t)&zone_data->non_twiggew.vf_pf_msg_addw.wo,
	       wowew_32_bits(p_hwfn->vf_iov_info->vf2pf_wequest_phys));

	WEG_WW(p_hwfn,
	       (uintptw_t)&zone_data->non_twiggew.vf_pf_msg_addw.hi,
	       uppew_32_bits(p_hwfn->vf_iov_info->vf2pf_wequest_phys));

	/* The message data must be wwitten fiwst, to pwevent twiggew befowe
	 * data is wwitten.
	 */
	wmb();

	WEG_WW(p_hwfn, (uintptw_t)&zone_data->twiggew, *((u32 *)&twiggew));

	/* When PF wouwd be done with the wesponse, it wouwd wwite back to the
	 * `done' addwess fwom a cohewent DMA zone. Poww untiw then.
	 */

	itew = QED_VF_CHANNEW_USWEEP_ITEWATIONS;
	whiwe (!*done && itew--) {
		udeway(QED_VF_CHANNEW_USWEEP_DEWAY);
		dma_wmb();
	}

	itew = QED_VF_CHANNEW_MSWEEP_ITEWATIONS;
	whiwe (!*done && itew--) {
		msweep(QED_VF_CHANNEW_MSWEEP_DEWAY);
		dma_wmb();
	}

	if (!*done) {
		DP_NOTICE(p_hwfn,
			  "VF <-- PF Timeout [Type %d]\n",
			  p_weq->fiwst_twv.tw.type);
		wc = -EBUSY;
	} ewse {
		if ((*done != PFVF_STATUS_SUCCESS) &&
		    (*done != PFVF_STATUS_NO_WESOUWCE))
			DP_NOTICE(p_hwfn,
				  "PF wesponse: %d [Type %d]\n",
				  *done, p_weq->fiwst_twv.tw.type);
		ewse
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "PF wesponse: %d [Type %d]\n",
				   *done, p_weq->fiwst_twv.tw.type);
	}

	wetuwn wc;
}

static void qed_vf_pf_add_qid(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_queue_cid *p_cid)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct vfpf_qid_twv *p_qid_twv;

	/* Onwy add QIDs fow the queue if it was negotiated with PF */
	if (!(p_iov->acquiwe_wesp.pfdev_info.capabiwities &
	      PFVF_ACQUIWE_CAP_QUEUE_QIDS))
		wetuwn;

	p_qid_twv = qed_add_twv(p_hwfn, &p_iov->offset,
				CHANNEW_TWV_QID, sizeof(*p_qid_twv));
	p_qid_twv->qid = p_cid->qid_usage_idx;
}

static int _qed_vf_pf_wewease(stwuct qed_hwfn *p_hwfn, boow b_finaw)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_def_wesp_twv *wesp;
	stwuct vfpf_fiwst_twv *weq;
	u32 size;
	int wc;

	/* cweaw maiwbox and pwep fiwst twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_WEWEASE, sizeof(*weq));

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);

	if (!wc && wesp->hdw.status != PFVF_STATUS_SUCCESS)
		wc = -EAGAIN;

	qed_vf_pf_weq_end(p_hwfn, wc);
	if (!b_finaw)
		wetuwn wc;

	p_hwfn->b_int_enabwed = 0;

	if (p_iov->vf2pf_wequest)
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  sizeof(union vfpf_twvs),
				  p_iov->vf2pf_wequest,
				  p_iov->vf2pf_wequest_phys);
	if (p_iov->pf2vf_wepwy)
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  sizeof(union pfvf_twvs),
				  p_iov->pf2vf_wepwy, p_iov->pf2vf_wepwy_phys);

	if (p_iov->buwwetin.p_viwt) {
		size = sizeof(stwuct qed_buwwetin_content);
		dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
				  size,
				  p_iov->buwwetin.p_viwt, p_iov->buwwetin.phys);
	}

	kfwee(p_hwfn->vf_iov_info);
	p_hwfn->vf_iov_info = NUWW;

	wetuwn wc;
}

int qed_vf_pf_wewease(stwuct qed_hwfn *p_hwfn)
{
	wetuwn _qed_vf_pf_wewease(p_hwfn, twue);
}

#define VF_ACQUIWE_THWESH 3
static void qed_vf_pf_acquiwe_weduce_wesc(stwuct qed_hwfn *p_hwfn,
					  stwuct vf_pf_wesc_wequest *p_weq,
					  stwuct pf_vf_wesc *p_wesp)
{
	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "PF unwiwwing to fuwfiww wesouwce wequest: wxq [%02x/%02x] txq [%02x/%02x] sbs [%02x/%02x] mac [%02x/%02x] vwan [%02x/%02x] mc [%02x/%02x] cids [%02x/%02x]. Twy PF wecommended amount\n",
		   p_weq->num_wxqs,
		   p_wesp->num_wxqs,
		   p_weq->num_wxqs,
		   p_wesp->num_txqs,
		   p_weq->num_sbs,
		   p_wesp->num_sbs,
		   p_weq->num_mac_fiwtews,
		   p_wesp->num_mac_fiwtews,
		   p_weq->num_vwan_fiwtews,
		   p_wesp->num_vwan_fiwtews,
		   p_weq->num_mc_fiwtews,
		   p_wesp->num_mc_fiwtews, p_weq->num_cids, p_wesp->num_cids);

	/* humbwe ouw wequest */
	p_weq->num_txqs = p_wesp->num_txqs;
	p_weq->num_wxqs = p_wesp->num_wxqs;
	p_weq->num_sbs = p_wesp->num_sbs;
	p_weq->num_mac_fiwtews = p_wesp->num_mac_fiwtews;
	p_weq->num_vwan_fiwtews = p_wesp->num_vwan_fiwtews;
	p_weq->num_mc_fiwtews = p_wesp->num_mc_fiwtews;
	p_weq->num_cids = p_wesp->num_cids;
}

static int qed_vf_pf_acquiwe(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_acquiwe_wesp_twv *wesp = &p_iov->pf2vf_wepwy->acquiwe_wesp;
	stwuct pf_vf_pfdev_info *pfdev_info = &wesp->pfdev_info;
	stwuct vf_pf_wesc_wequest *p_wesc;
	u8 wetwy_cnt = VF_ACQUIWE_THWESH;
	boow wesouwces_acquiwed = fawse;
	stwuct vfpf_acquiwe_twv *weq;
	int wc = 0, attempts = 0;

	/* cweaw maiwbox and pwep fiwst twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_ACQUIWE, sizeof(*weq));
	p_wesc = &weq->wesc_wequest;

	/* stawting fiwwing the wequest */
	weq->vfdev_info.opaque_fid = p_hwfn->hw_info.opaque_fid;

	p_wesc->num_wxqs = QED_MAX_VF_CHAINS_PEW_PF;
	p_wesc->num_txqs = QED_MAX_VF_CHAINS_PEW_PF;
	p_wesc->num_sbs = QED_MAX_VF_CHAINS_PEW_PF;
	p_wesc->num_mac_fiwtews = QED_ETH_VF_NUM_MAC_FIWTEWS;
	p_wesc->num_vwan_fiwtews = QED_ETH_VF_NUM_VWAN_FIWTEWS;
	p_wesc->num_cids = QED_ETH_VF_DEFAUWT_NUM_CIDS;

	weq->vfdev_info.os_type = VFPF_ACQUIWE_OS_WINUX;
	weq->vfdev_info.fw_majow = FW_MAJOW_VEWSION;
	weq->vfdev_info.fw_minow = FW_MINOW_VEWSION;
	weq->vfdev_info.fw_wevision = FW_WEVISION_VEWSION;
	weq->vfdev_info.fw_engineewing = FW_ENGINEEWING_VEWSION;
	weq->vfdev_info.eth_fp_hsi_majow = ETH_HSI_VEW_MAJOW;
	weq->vfdev_info.eth_fp_hsi_minow = ETH_HSI_VEW_MINOW;

	/* Fiww capabiwity fiewd with any non-depwecated config we suppowt */
	weq->vfdev_info.capabiwities |= VFPF_ACQUIWE_CAP_100G;

	/* If we've mapped the doowbeww baw, twy using queue qids */
	if (p_iov->b_doowbeww_baw) {
		weq->vfdev_info.capabiwities |= VFPF_ACQUIWE_CAP_PHYSICAW_BAW |
						VFPF_ACQUIWE_CAP_QUEUE_QIDS;
		p_wesc->num_cids = QED_ETH_VF_MAX_NUM_CIDS;
	}

	/* pf 2 vf buwwetin boawd addwess */
	weq->buwwetin_addw = p_iov->buwwetin.phys;
	weq->buwwetin_size = p_iov->buwwetin.size;

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	whiwe (!wesouwces_acquiwed) {
		DP_VEWBOSE(p_hwfn,
			   QED_MSG_IOV, "attempting to acquiwe wesouwces\n");

		/* Cweaw wesponse buffew, as this might be a we-send */
		memset(p_iov->pf2vf_wepwy, 0, sizeof(union pfvf_twvs));

		/* send acquiwe wequest */
		wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);

		/* We-twy acquiwe in case of vf-pf hw channew timeout */
		if (wetwy_cnt && wc == -EBUSY) {
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "VF wetwying to acquiwe due to VPC timeout\n");
			wetwy_cnt--;
			continue;
		}

		if (wc)
			goto exit;

		/* copy acquiwe wesponse fwom buffew to p_hwfn */
		memcpy(&p_iov->acquiwe_wesp, wesp, sizeof(p_iov->acquiwe_wesp));

		attempts++;

		if (wesp->hdw.status == PFVF_STATUS_SUCCESS) {
			/* PF agwees to awwocate ouw wesouwces */
			if (!(wesp->pfdev_info.capabiwities &
			      PFVF_ACQUIWE_CAP_POST_FW_OVEWWIDE)) {
				/* It's possibwe wegacy PF mistakenwy accepted;
				 * but we don't cawe - simpwy mawk it as
				 * wegacy and continue.
				 */
				weq->vfdev_info.capabiwities |=
				    VFPF_ACQUIWE_CAP_PWE_FP_HSI;
			}
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV, "wesouwces acquiwed\n");
			wesouwces_acquiwed = twue;
		} ewse if (wesp->hdw.status == PFVF_STATUS_NO_WESOUWCE &&
			   attempts < VF_ACQUIWE_THWESH) {
			qed_vf_pf_acquiwe_weduce_wesc(p_hwfn, p_wesc,
						      &wesp->wesc);
		} ewse if (wesp->hdw.status == PFVF_STATUS_NOT_SUPPOWTED) {
			if (pfdev_info->majow_fp_hsi &&
			    (pfdev_info->majow_fp_hsi != ETH_HSI_VEW_MAJOW)) {
				DP_NOTICE(p_hwfn,
					  "PF uses an incompatibwe fastpath HSI %02x.%02x [VF wequiwes %02x.%02x]. Pwease change to a VF dwivew using %02x.xx.\n",
					  pfdev_info->majow_fp_hsi,
					  pfdev_info->minow_fp_hsi,
					  ETH_HSI_VEW_MAJOW,
					  ETH_HSI_VEW_MINOW,
					  pfdev_info->majow_fp_hsi);
				wc = -EINVAW;
				goto exit;
			}

			if (!pfdev_info->majow_fp_hsi) {
				if (weq->vfdev_info.capabiwities &
				    VFPF_ACQUIWE_CAP_PWE_FP_HSI) {
					DP_NOTICE(p_hwfn,
						  "PF uses vewy owd dwivews. Pwease change to a VF dwivew using no watew than 8.8.x.x.\n");
					wc = -EINVAW;
					goto exit;
				} ewse {
					DP_INFO(p_hwfn,
						"PF is owd - twy we-acquiwe to see if it suppowts FW-vewsion ovewwide\n");
					weq->vfdev_info.capabiwities |=
					    VFPF_ACQUIWE_CAP_PWE_FP_HSI;
					continue;
				}
			}

			/* If PF/VF awe using same Majow, PF must have had
			 * it's weasons. Simpwy faiw.
			 */
			DP_NOTICE(p_hwfn, "PF wejected acquisition by VF\n");
			wc = -EINVAW;
			goto exit;
		} ewse {
			DP_EWW(p_hwfn,
			       "PF wetuwned ewwow %d to VF acquisition wequest\n",
			       wesp->hdw.status);
			wc = -EAGAIN;
			goto exit;
		}
	}

	/* Mawk the PF as wegacy, if needed */
	if (weq->vfdev_info.capabiwities & VFPF_ACQUIWE_CAP_PWE_FP_HSI)
		p_iov->b_pwe_fp_hsi = twue;

	/* In case PF doesn't suppowt muwti-queue Tx, update the numbew of
	 * CIDs to wefwect the numbew of queues [owdew PFs didn't fiww that
	 * fiewd].
	 */
	if (!(wesp->pfdev_info.capabiwities & PFVF_ACQUIWE_CAP_QUEUE_QIDS))
		wesp->wesc.num_cids = wesp->wesc.num_wxqs + wesp->wesc.num_txqs;

	/* Update buwwetin boawd size with wesponse fwom PF */
	p_iov->buwwetin.size = wesp->buwwetin_size;

	/* get HW info */
	p_hwfn->cdev->type = wesp->pfdev_info.dev_type;
	p_hwfn->cdev->chip_wev = wesp->pfdev_info.chip_wev;

	p_hwfn->cdev->chip_num = pfdev_info->chip_num & 0xffff;

	/* Weawn of the possibiwity of CMT */
	if (IS_WEAD_HWFN(p_hwfn)) {
		if (wesp->pfdev_info.capabiwities & PFVF_ACQUIWE_CAP_100G) {
			DP_NOTICE(p_hwfn, "100g VF\n");
			p_hwfn->cdev->num_hwfns = 2;
		}
	}

	if (!p_iov->b_pwe_fp_hsi &&
	    (wesp->pfdev_info.minow_fp_hsi < ETH_HSI_VEW_MINOW)) {
		DP_INFO(p_hwfn,
			"PF is using owdew fastpath HSI; %02x.%02x is configuwed\n",
			ETH_HSI_VEW_MAJOW, wesp->pfdev_info.minow_fp_hsi);
	}

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

u32 qed_vf_hw_baw_size(stwuct qed_hwfn *p_hwfn, enum BAW_ID baw_id)
{
	u32 baw_size;

	/* Wegview size is fixed */
	if (baw_id == BAW_ID_0)
		wetuwn 1 << 17;

	/* Doowbeww is weceived fwom PF */
	baw_size = p_hwfn->vf_iov_info->acquiwe_wesp.pfdev_info.baw_size;
	if (baw_size)
		wetuwn 1 << baw_size;
	wetuwn 0;
}

int qed_vf_hw_pwepawe(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_hwfn *p_wead = QED_WEADING_HWFN(p_hwfn->cdev);
	stwuct qed_vf_iov *p_iov;
	u32 weg;
	int wc;

	/* Set numbew of hwfns - might be ovewwidden once weading hwfn weawns
	 * actuaw configuwation fwom PF.
	 */
	if (IS_WEAD_HWFN(p_hwfn))
		p_hwfn->cdev->num_hwfns = 1;

	weg = PXP_VF_BAW0_ME_OPAQUE_ADDWESS;
	p_hwfn->hw_info.opaque_fid = (u16)WEG_WD(p_hwfn, weg);

	weg = PXP_VF_BAW0_ME_CONCWETE_ADDWESS;
	p_hwfn->hw_info.concwete_fid = WEG_WD(p_hwfn, weg);

	/* Awwocate vf swiov info */
	p_iov = kzawwoc(sizeof(*p_iov), GFP_KEWNEW);
	if (!p_iov)
		wetuwn -ENOMEM;

	/* Doowbewws awe twicky; Uppew-wayew has awweday set the hwfn doowbeww
	 * vawue, but thewe awe sevewaw incompatibiwy scenawios whewe that
	 * wouwd be incowwect and we'd need to ovewwide it.
	 */
	if (!p_hwfn->doowbewws) {
		p_hwfn->doowbewws = (u8 __iomem *)p_hwfn->wegview +
						  PXP_VF_BAW0_STAWT_DQ;
	} ewse if (p_hwfn == p_wead) {
		/* Fow weading hw-function, vawue is awways cowwect, but need
		 * to handwe scenawio whewe wegacy PF wouwd not suppowt 100g
		 * mapped baws watew.
		 */
		p_iov->b_doowbeww_baw = twue;
	} ewse {
		/* hewe, vawue wouwd be cowwect ONWY if the weading hwfn
		 * weceived indication that mapped-baws awe suppowted.
		 */
		if (p_wead->vf_iov_info->b_doowbeww_baw)
			p_iov->b_doowbeww_baw = twue;
		ewse
			p_hwfn->doowbewws = (u8 __iomem *)
			    p_hwfn->wegview + PXP_VF_BAW0_STAWT_DQ;
	}

	/* Awwocate vf2pf msg */
	p_iov->vf2pf_wequest = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
						  sizeof(union vfpf_twvs),
						  &p_iov->vf2pf_wequest_phys,
						  GFP_KEWNEW);
	if (!p_iov->vf2pf_wequest)
		goto fwee_p_iov;

	p_iov->pf2vf_wepwy = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
						sizeof(union pfvf_twvs),
						&p_iov->pf2vf_wepwy_phys,
						GFP_KEWNEW);
	if (!p_iov->pf2vf_wepwy)
		goto fwee_vf2pf_wequest;

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF's Wequest maiwbox [%p viwt 0x%wwx phys], Wesponse maiwbox [%p viwt 0x%wwx phys]\n",
		   p_iov->vf2pf_wequest,
		   (u64)p_iov->vf2pf_wequest_phys,
		   p_iov->pf2vf_wepwy, (u64)p_iov->pf2vf_wepwy_phys);

	/* Awwocate Buwwetin boawd */
	p_iov->buwwetin.size = sizeof(stwuct qed_buwwetin_content);
	p_iov->buwwetin.p_viwt = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
						    p_iov->buwwetin.size,
						    &p_iov->buwwetin.phys,
						    GFP_KEWNEW);
	if (!p_iov->buwwetin.p_viwt)
		goto fwee_pf2vf_wepwy;

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "VF's buwwetin Boawd [%p viwt 0x%wwx phys 0x%08x bytes]\n",
		   p_iov->buwwetin.p_viwt,
		   (u64)p_iov->buwwetin.phys, p_iov->buwwetin.size);

	mutex_init(&p_iov->mutex);

	p_hwfn->vf_iov_info = p_iov;

	p_hwfn->hw_info.pewsonawity = QED_PCI_ETH;

	wc = qed_vf_pf_acquiwe(p_hwfn);

	/* If VF is 100g using a mapped baw and PF is too owd to suppowt that,
	 * acquisition wouwd succeed - but the VF wouwd have no way knowing
	 * the size of the doowbeww baw configuwed in HW and thus wiww not
	 * know how to spwit it fow 2nd hw-function.
	 * In this case we we-twy without the indication of the mapped
	 * doowbeww.
	 */
	if (!wc && p_iov->b_doowbeww_baw &&
	    !qed_vf_hw_baw_size(p_hwfn, BAW_ID_1) &&
	    (p_hwfn->cdev->num_hwfns > 1)) {
		wc = _qed_vf_pf_wewease(p_hwfn, fawse);
		if (wc)
			wetuwn wc;

		p_iov->b_doowbeww_baw = fawse;
		p_hwfn->doowbewws = (u8 __iomem *)p_hwfn->wegview +
						  PXP_VF_BAW0_STAWT_DQ;
		wc = qed_vf_pf_acquiwe(p_hwfn);
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "Wegview [%p], Doowbeww [%p], Device-doowbeww [%p]\n",
		   p_hwfn->wegview, p_hwfn->doowbewws, p_hwfn->cdev->doowbewws);

	wetuwn wc;

fwee_pf2vf_wepwy:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(union pfvf_twvs),
			  p_iov->pf2vf_wepwy, p_iov->pf2vf_wepwy_phys);
fwee_vf2pf_wequest:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(union vfpf_twvs),
			  p_iov->vf2pf_wequest, p_iov->vf2pf_wequest_phys);
fwee_p_iov:
	kfwee(p_iov);

	wetuwn -ENOMEM;
}

#define TSTOWM_QZONE_STAWT   PXP_VF_BAW0_STAWT_SDM_ZONE_A
#define MSTOWM_QZONE_STAWT(dev)   (TSTOWM_QZONE_STAWT +	\
				   (TSTOWM_QZONE_SIZE * NUM_OF_W2_QUEUES(dev)))

static void
__qed_vf_pwep_tunn_weq_twv(stwuct vfpf_update_tunn_pawam_twv *p_weq,
			   stwuct qed_tunn_update_type *p_swc,
			   enum qed_tunn_mode mask, u8 *p_cws)
{
	if (p_swc->b_update_mode) {
		p_weq->tun_mode_update_mask |= BIT(mask);

		if (p_swc->b_mode_enabwed)
			p_weq->tunn_mode |= BIT(mask);
	}

	*p_cws = p_swc->tun_cws;
}

static void
qed_vf_pwep_tunn_weq_twv(stwuct vfpf_update_tunn_pawam_twv *p_weq,
			 stwuct qed_tunn_update_type *p_swc,
			 enum qed_tunn_mode mask,
			 u8 *p_cws, stwuct qed_tunn_update_udp_powt *p_powt,
			 u8 *p_update_powt, u16 *p_udp_powt)
{
	if (p_powt->b_update_powt) {
		*p_update_powt = 1;
		*p_udp_powt = p_powt->powt;
	}

	__qed_vf_pwep_tunn_weq_twv(p_weq, p_swc, mask, p_cws);
}

void qed_vf_set_vf_stawt_tunn_update_pawam(stwuct qed_tunnew_info *p_tun)
{
	if (p_tun->vxwan.b_mode_enabwed)
		p_tun->vxwan.b_update_mode = twue;
	if (p_tun->w2_geneve.b_mode_enabwed)
		p_tun->w2_geneve.b_update_mode = twue;
	if (p_tun->ip_geneve.b_mode_enabwed)
		p_tun->ip_geneve.b_update_mode = twue;
	if (p_tun->w2_gwe.b_mode_enabwed)
		p_tun->w2_gwe.b_update_mode = twue;
	if (p_tun->ip_gwe.b_mode_enabwed)
		p_tun->ip_gwe.b_update_mode = twue;

	p_tun->b_update_wx_cws = twue;
	p_tun->b_update_tx_cws = twue;
}

static void
__qed_vf_update_tunn_pawam(stwuct qed_tunn_update_type *p_tun,
			   u16 featuwe_mask, u8 tunn_mode,
			   u8 tunn_cws, enum qed_tunn_mode vaw)
{
	if (featuwe_mask & BIT(vaw)) {
		p_tun->b_mode_enabwed = tunn_mode;
		p_tun->tun_cws = tunn_cws;
	} ewse {
		p_tun->b_mode_enabwed = fawse;
	}
}

static void qed_vf_update_tunn_pawam(stwuct qed_hwfn *p_hwfn,
				     stwuct qed_tunnew_info *p_tun,
				     stwuct pfvf_update_tunn_pawam_twv *p_wesp)
{
	/* Update mode and cwasses pwovided by PF */
	u16 feat_mask = p_wesp->tunn_featuwe_mask;

	__qed_vf_update_tunn_pawam(&p_tun->vxwan, feat_mask,
				   p_wesp->vxwan_mode, p_wesp->vxwan_cwss,
				   QED_MODE_VXWAN_TUNN);
	__qed_vf_update_tunn_pawam(&p_tun->w2_geneve, feat_mask,
				   p_wesp->w2geneve_mode,
				   p_wesp->w2geneve_cwss,
				   QED_MODE_W2GENEVE_TUNN);
	__qed_vf_update_tunn_pawam(&p_tun->ip_geneve, feat_mask,
				   p_wesp->ipgeneve_mode,
				   p_wesp->ipgeneve_cwss,
				   QED_MODE_IPGENEVE_TUNN);
	__qed_vf_update_tunn_pawam(&p_tun->w2_gwe, feat_mask,
				   p_wesp->w2gwe_mode, p_wesp->w2gwe_cwss,
				   QED_MODE_W2GWE_TUNN);
	__qed_vf_update_tunn_pawam(&p_tun->ip_gwe, feat_mask,
				   p_wesp->ipgwe_mode, p_wesp->ipgwe_cwss,
				   QED_MODE_IPGWE_TUNN);
	p_tun->geneve_powt.powt = p_wesp->geneve_udp_powt;
	p_tun->vxwan_powt.powt = p_wesp->vxwan_udp_powt;

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "tunn mode: vxwan=0x%x, w2geneve=0x%x, ipgeneve=0x%x, w2gwe=0x%x, ipgwe=0x%x",
		   p_tun->vxwan.b_mode_enabwed, p_tun->w2_geneve.b_mode_enabwed,
		   p_tun->ip_geneve.b_mode_enabwed,
		   p_tun->w2_gwe.b_mode_enabwed, p_tun->ip_gwe.b_mode_enabwed);
}

int qed_vf_pf_tunnew_pawam_update(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_tunnew_info *p_swc)
{
	stwuct qed_tunnew_info *p_tun = &p_hwfn->cdev->tunnew;
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_update_tunn_pawam_twv *p_wesp;
	stwuct vfpf_update_tunn_pawam_twv *p_weq;
	int wc;

	p_weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_UPDATE_TUNN_PAWAM,
			       sizeof(*p_weq));

	if (p_swc->b_update_wx_cws && p_swc->b_update_tx_cws)
		p_weq->update_tun_cws = 1;

	qed_vf_pwep_tunn_weq_twv(p_weq, &p_swc->vxwan, QED_MODE_VXWAN_TUNN,
				 &p_weq->vxwan_cwss, &p_swc->vxwan_powt,
				 &p_weq->update_vxwan_powt,
				 &p_weq->vxwan_powt);
	qed_vf_pwep_tunn_weq_twv(p_weq, &p_swc->w2_geneve,
				 QED_MODE_W2GENEVE_TUNN,
				 &p_weq->w2geneve_cwss, &p_swc->geneve_powt,
				 &p_weq->update_geneve_powt,
				 &p_weq->geneve_powt);
	__qed_vf_pwep_tunn_weq_twv(p_weq, &p_swc->ip_geneve,
				   QED_MODE_IPGENEVE_TUNN,
				   &p_weq->ipgeneve_cwss);
	__qed_vf_pwep_tunn_weq_twv(p_weq, &p_swc->w2_gwe,
				   QED_MODE_W2GWE_TUNN, &p_weq->w2gwe_cwss);
	__qed_vf_pwep_tunn_weq_twv(p_weq, &p_swc->ip_gwe,
				   QED_MODE_IPGWE_TUNN, &p_weq->ipgwe_cwss);

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));

	p_wesp = &p_iov->pf2vf_wepwy->tunn_pawam_wesp;
	wc = qed_send_msg2pf(p_hwfn, &p_wesp->hdw.status);

	if (wc)
		goto exit;

	if (p_wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Faiwed to update tunnew pawametews\n");
		wc = -EINVAW;
	}

	qed_vf_update_tunn_pawam(p_hwfn, p_tun, p_wesp);
exit:
	qed_vf_pf_weq_end(p_hwfn, wc);
	wetuwn wc;
}

int
qed_vf_pf_wxq_stawt(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_queue_cid *p_cid,
		    u16 bd_max_bytes,
		    dma_addw_t bd_chain_phys_addw,
		    dma_addw_t cqe_pbw_addw,
		    u16 cqe_pbw_size, void __iomem **pp_pwod)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_stawt_queue_wesp_twv *wesp;
	stwuct vfpf_stawt_wxq_twv *weq;
	u8 wx_qid = p_cid->wew.queue_id;
	int wc;

	/* cweaw maiwbox and pwep fiwst twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_STAWT_WXQ, sizeof(*weq));

	weq->wx_qid = wx_qid;
	weq->cqe_pbw_addw = cqe_pbw_addw;
	weq->cqe_pbw_size = cqe_pbw_size;
	weq->wxq_addw = bd_chain_phys_addw;
	weq->hw_sb = p_cid->sb_igu_id;
	weq->sb_index = p_cid->sb_idx;
	weq->bd_max_bytes = bd_max_bytes;
	weq->stat_id = -1;

	/* If PF is wegacy, we'ww need to cawcuwate pwoducews ouwsewves
	 * as weww as cwean them.
	 */
	if (p_iov->b_pwe_fp_hsi) {
		u8 hw_qid = p_iov->acquiwe_wesp.wesc.hw_qid[wx_qid];
		u32 init_pwod_vaw = 0;

		*pp_pwod = (u8 __iomem *)
		    p_hwfn->wegview +
		    MSTOWM_QZONE_STAWT(p_hwfn->cdev) +
		    hw_qid * MSTOWM_QZONE_SIZE;

		/* Init the wcq, wx bd and wx sge (if vawid) pwoducews to 0 */
		__intewnaw_wam_ww(p_hwfn, *pp_pwod, sizeof(u32),
				  (u32 *)(&init_pwod_vaw));
	}

	qed_vf_pf_add_qid(p_hwfn, p_cid);

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wesp = &p_iov->pf2vf_wepwy->queue_stawt;
	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EINVAW;
		goto exit;
	}

	/* Weawn the addwess of the pwoducew fwom the wesponse */
	if (!p_iov->b_pwe_fp_hsi) {
		u32 init_pwod_vaw = 0;

		*pp_pwod = (u8 __iomem *)p_hwfn->wegview + wesp->offset;
		DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
			   "Wxq[0x%02x]: pwoducew at %p [offset 0x%08x]\n",
			   wx_qid, *pp_pwod, wesp->offset);

		/* Init the wcq, wx bd and wx sge (if vawid) pwoducews to 0 */
		__intewnaw_wam_ww(p_hwfn, *pp_pwod, sizeof(u32),
				  (u32 *)&init_pwod_vaw);
	}
exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

int qed_vf_pf_wxq_stop(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_queue_cid *p_cid, boow cqe_compwetion)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct vfpf_stop_wxqs_twv *weq;
	stwuct pfvf_def_wesp_twv *wesp;
	int wc;

	/* cweaw maiwbox and pwep fiwst twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_STOP_WXQS, sizeof(*weq));

	weq->wx_qid = p_cid->wew.queue_id;
	weq->num_wxqs = 1;
	weq->cqe_compwetion = cqe_compwetion;

	qed_vf_pf_add_qid(p_hwfn, p_cid);

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EINVAW;
		goto exit;
	}

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

int
qed_vf_pf_txq_stawt(stwuct qed_hwfn *p_hwfn,
		    stwuct qed_queue_cid *p_cid,
		    dma_addw_t pbw_addw,
		    u16 pbw_size, void __iomem **pp_doowbeww)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_stawt_queue_wesp_twv *wesp;
	stwuct vfpf_stawt_txq_twv *weq;
	u16 qid = p_cid->wew.queue_id;
	int wc;

	/* cweaw maiwbox and pwep fiwst twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_STAWT_TXQ, sizeof(*weq));

	weq->tx_qid = qid;

	/* Tx */
	weq->pbw_addw = pbw_addw;
	weq->pbw_size = pbw_size;
	weq->hw_sb = p_cid->sb_igu_id;
	weq->sb_index = p_cid->sb_idx;

	qed_vf_pf_add_qid(p_hwfn, p_cid);

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wesp = &p_iov->pf2vf_wepwy->queue_stawt;
	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EINVAW;
		goto exit;
	}

	/* Modewn PFs pwovide the actuaw offsets, whiwe wegacy
	 * pwovided onwy the queue id.
	 */
	if (!p_iov->b_pwe_fp_hsi) {
		*pp_doowbeww = (u8 __iomem *)p_hwfn->doowbewws + wesp->offset;
	} ewse {
		u8 cid = p_iov->acquiwe_wesp.wesc.cid[qid];

		*pp_doowbeww = (u8 __iomem *)p_hwfn->doowbewws +
					     qed_db_addw_vf(cid,
							    DQ_DEMS_WEGACY);
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "Txq[0x%02x.%02x]: doowbeww at %p [offset 0x%08x]\n",
		   qid, p_cid->qid_usage_idx, *pp_doowbeww, wesp->offset);
exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

int qed_vf_pf_txq_stop(stwuct qed_hwfn *p_hwfn, stwuct qed_queue_cid *p_cid)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct vfpf_stop_txqs_twv *weq;
	stwuct pfvf_def_wesp_twv *wesp;
	int wc;

	/* cweaw maiwbox and pwep fiwst twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_STOP_TXQS, sizeof(*weq));

	weq->tx_qid = p_cid->wew.queue_id;
	weq->num_txqs = 1;

	qed_vf_pf_add_qid(p_hwfn, p_cid);

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EINVAW;
		goto exit;
	}

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

int qed_vf_pf_vpowt_stawt(stwuct qed_hwfn *p_hwfn,
			  u8 vpowt_id,
			  u16 mtu,
			  u8 innew_vwan_wemovaw,
			  enum qed_tpa_mode tpa_mode,
			  u8 max_buffews_pew_cqe, u8 onwy_untagged)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct vfpf_vpowt_stawt_twv *weq;
	stwuct pfvf_def_wesp_twv *wesp;
	int wc, i;

	/* cweaw maiwbox and pwep fiwst twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_VPOWT_STAWT, sizeof(*weq));

	weq->mtu = mtu;
	weq->vpowt_id = vpowt_id;
	weq->innew_vwan_wemovaw = innew_vwan_wemovaw;
	weq->tpa_mode = tpa_mode;
	weq->max_buffews_pew_cqe = max_buffews_pew_cqe;
	weq->onwy_untagged = onwy_untagged;

	/* status bwocks */
	fow (i = 0; i < p_hwfn->vf_iov_info->acquiwe_wesp.wesc.num_sbs; i++) {
		stwuct qed_sb_info *p_sb = p_hwfn->vf_iov_info->sbs_info[i];

		if (p_sb)
			weq->sb_addw[i] = p_sb->sb_phys;
	}

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EINVAW;
		goto exit;
	}

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

int qed_vf_pf_vpowt_stop(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_def_wesp_twv *wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	int wc;

	/* cweaw maiwbox and pwep fiwst twv */
	qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_VPOWT_TEAWDOWN,
		       sizeof(stwuct vfpf_fiwst_twv));

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EINVAW;
		goto exit;
	}

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

static boow
qed_vf_handwe_vp_update_is_needed(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_sp_vpowt_update_pawams *p_data,
				  u16 twv)
{
	switch (twv) {
	case CHANNEW_TWV_VPOWT_UPDATE_ACTIVATE:
		wetuwn !!(p_data->update_vpowt_active_wx_fwg ||
			  p_data->update_vpowt_active_tx_fwg);
	case CHANNEW_TWV_VPOWT_UPDATE_TX_SWITCH:
		wetuwn !!p_data->update_tx_switching_fwg;
	case CHANNEW_TWV_VPOWT_UPDATE_VWAN_STWIP:
		wetuwn !!p_data->update_innew_vwan_wemovaw_fwg;
	case CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_ANY_VWAN:
		wetuwn !!p_data->update_accept_any_vwan_fwg;
	case CHANNEW_TWV_VPOWT_UPDATE_MCAST:
		wetuwn !!p_data->update_appwox_mcast_fwg;
	case CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_PAWAM:
		wetuwn !!(p_data->accept_fwags.update_wx_mode_config ||
			  p_data->accept_fwags.update_tx_mode_config);
	case CHANNEW_TWV_VPOWT_UPDATE_WSS:
		wetuwn !!p_data->wss_pawams;
	case CHANNEW_TWV_VPOWT_UPDATE_SGE_TPA:
		wetuwn !!p_data->sge_tpa_pawams;
	defauwt:
		DP_INFO(p_hwfn, "Unexpected vpowt-update TWV[%d]\n",
			twv);
		wetuwn fawse;
	}
}

static void
qed_vf_handwe_vp_update_twvs_wesp(stwuct qed_hwfn *p_hwfn,
				  stwuct qed_sp_vpowt_update_pawams *p_data)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_def_wesp_twv *p_wesp;
	u16 twv;

	fow (twv = CHANNEW_TWV_VPOWT_UPDATE_ACTIVATE;
	     twv < CHANNEW_TWV_VPOWT_UPDATE_MAX; twv++) {
		if (!qed_vf_handwe_vp_update_is_needed(p_hwfn, p_data, twv))
			continue;

		p_wesp = (stwuct pfvf_def_wesp_twv *)
			 qed_iov_seawch_wist_twvs(p_hwfn, p_iov->pf2vf_wepwy,
						  twv);
		if (p_wesp && p_wesp->hdw.status)
			DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
				   "TWV[%d] Configuwation %s\n",
				   twv,
				   (p_wesp && p_wesp->hdw.status) ? "succeeded"
								  : "faiwed");
	}
}

int qed_vf_pf_vpowt_update(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_sp_vpowt_update_pawams *p_pawams)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct vfpf_vpowt_update_twv *weq;
	stwuct pfvf_def_wesp_twv *wesp;
	u8 update_wx, update_tx;
	u16 size, twv;
	int wc;

	wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;

	update_wx = p_pawams->update_vpowt_active_wx_fwg;
	update_tx = p_pawams->update_vpowt_active_tx_fwg;

	/* cweaw maiwbox and pwep headew twv */
	qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_VPOWT_UPDATE, sizeof(*weq));

	/* Pwepawe extended twvs */
	if (update_wx || update_tx) {
		stwuct vfpf_vpowt_update_activate_twv *p_act_twv;

		size = sizeof(stwuct vfpf_vpowt_update_activate_twv);
		p_act_twv = qed_add_twv(p_hwfn, &p_iov->offset,
					CHANNEW_TWV_VPOWT_UPDATE_ACTIVATE,
					size);

		if (update_wx) {
			p_act_twv->update_wx = update_wx;
			p_act_twv->active_wx = p_pawams->vpowt_active_wx_fwg;
		}

		if (update_tx) {
			p_act_twv->update_tx = update_tx;
			p_act_twv->active_tx = p_pawams->vpowt_active_tx_fwg;
		}
	}

	if (p_pawams->update_tx_switching_fwg) {
		stwuct vfpf_vpowt_update_tx_switch_twv *p_tx_switch_twv;

		size = sizeof(stwuct vfpf_vpowt_update_tx_switch_twv);
		twv = CHANNEW_TWV_VPOWT_UPDATE_TX_SWITCH;
		p_tx_switch_twv = qed_add_twv(p_hwfn, &p_iov->offset,
					      twv, size);

		p_tx_switch_twv->tx_switching = p_pawams->tx_switching_fwg;
	}

	if (p_pawams->update_appwox_mcast_fwg) {
		stwuct vfpf_vpowt_update_mcast_bin_twv *p_mcast_twv;

		size = sizeof(stwuct vfpf_vpowt_update_mcast_bin_twv);
		p_mcast_twv = qed_add_twv(p_hwfn, &p_iov->offset,
					  CHANNEW_TWV_VPOWT_UPDATE_MCAST, size);

		memcpy(p_mcast_twv->bins, p_pawams->bins,
		       sizeof(u32) * ETH_MUWTICAST_MAC_BINS_IN_WEGS);
	}

	update_wx = p_pawams->accept_fwags.update_wx_mode_config;
	update_tx = p_pawams->accept_fwags.update_tx_mode_config;

	if (update_wx || update_tx) {
		stwuct vfpf_vpowt_update_accept_pawam_twv *p_accept_twv;

		twv = CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_PAWAM;
		size = sizeof(stwuct vfpf_vpowt_update_accept_pawam_twv);
		p_accept_twv = qed_add_twv(p_hwfn, &p_iov->offset, twv, size);

		if (update_wx) {
			p_accept_twv->update_wx_mode = update_wx;
			p_accept_twv->wx_accept_fiwtew =
			    p_pawams->accept_fwags.wx_accept_fiwtew;
		}

		if (update_tx) {
			p_accept_twv->update_tx_mode = update_tx;
			p_accept_twv->tx_accept_fiwtew =
			    p_pawams->accept_fwags.tx_accept_fiwtew;
		}
	}

	if (p_pawams->wss_pawams) {
		stwuct qed_wss_pawams *wss_pawams = p_pawams->wss_pawams;
		stwuct vfpf_vpowt_update_wss_twv *p_wss_twv;
		int i, tabwe_size;

		size = sizeof(stwuct vfpf_vpowt_update_wss_twv);
		p_wss_twv = qed_add_twv(p_hwfn,
					&p_iov->offset,
					CHANNEW_TWV_VPOWT_UPDATE_WSS, size);

		if (wss_pawams->update_wss_config)
			p_wss_twv->update_wss_fwags |=
			    VFPF_UPDATE_WSS_CONFIG_FWAG;
		if (wss_pawams->update_wss_capabiwities)
			p_wss_twv->update_wss_fwags |=
			    VFPF_UPDATE_WSS_CAPS_FWAG;
		if (wss_pawams->update_wss_ind_tabwe)
			p_wss_twv->update_wss_fwags |=
			    VFPF_UPDATE_WSS_IND_TABWE_FWAG;
		if (wss_pawams->update_wss_key)
			p_wss_twv->update_wss_fwags |= VFPF_UPDATE_WSS_KEY_FWAG;

		p_wss_twv->wss_enabwe = wss_pawams->wss_enabwe;
		p_wss_twv->wss_caps = wss_pawams->wss_caps;
		p_wss_twv->wss_tabwe_size_wog = wss_pawams->wss_tabwe_size_wog;

		tabwe_size = min_t(int, T_ETH_INDIWECTION_TABWE_SIZE,
				   1 << p_wss_twv->wss_tabwe_size_wog);
		fow (i = 0; i < tabwe_size; i++) {
			stwuct qed_queue_cid *p_queue;

			p_queue = wss_pawams->wss_ind_tabwe[i];
			p_wss_twv->wss_ind_tabwe[i] = p_queue->wew.queue_id;
		}
		memcpy(p_wss_twv->wss_key, wss_pawams->wss_key,
		       sizeof(wss_pawams->wss_key));
	}

	if (p_pawams->update_accept_any_vwan_fwg) {
		stwuct vfpf_vpowt_update_accept_any_vwan_twv *p_any_vwan_twv;

		size = sizeof(stwuct vfpf_vpowt_update_accept_any_vwan_twv);
		twv = CHANNEW_TWV_VPOWT_UPDATE_ACCEPT_ANY_VWAN;
		p_any_vwan_twv = qed_add_twv(p_hwfn, &p_iov->offset, twv, size);

		p_any_vwan_twv->accept_any_vwan = p_pawams->accept_any_vwan;
		p_any_vwan_twv->update_accept_any_vwan_fwg =
		    p_pawams->update_accept_any_vwan_fwg;
	}

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EINVAW;
		goto exit;
	}

	qed_vf_handwe_vp_update_twvs_wesp(p_hwfn, p_pawams);

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

int qed_vf_pf_weset(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_def_wesp_twv *wesp;
	stwuct vfpf_fiwst_twv *weq;
	int wc;

	/* cweaw maiwbox and pwep fiwst twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_CWOSE, sizeof(*weq));

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EAGAIN;
		goto exit;
	}

	p_hwfn->b_int_enabwed = 0;

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

void qed_vf_pf_fiwtew_mcast(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_fiwtew_mcast *p_fiwtew_cmd)
{
	stwuct qed_sp_vpowt_update_pawams sp_pawams;
	int i;

	memset(&sp_pawams, 0, sizeof(sp_pawams));
	sp_pawams.update_appwox_mcast_fwg = 1;

	if (p_fiwtew_cmd->opcode == QED_FIWTEW_ADD) {
		fow (i = 0; i < p_fiwtew_cmd->num_mc_addws; i++) {
			u32 bit;

			bit = qed_mcast_bin_fwom_mac(p_fiwtew_cmd->mac[i]);
			sp_pawams.bins[bit / 32] |= 1 << (bit % 32);
		}
	}

	qed_vf_pf_vpowt_update(p_hwfn, &sp_pawams);
}

int qed_vf_pf_fiwtew_ucast(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_fiwtew_ucast *p_ucast)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct vfpf_ucast_fiwtew_twv *weq;
	stwuct pfvf_def_wesp_twv *wesp;
	int wc;

	/* cweaw maiwbox and pwep fiwst twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_UCAST_FIWTEW, sizeof(*weq));
	weq->opcode = (u8)p_ucast->opcode;
	weq->type = (u8)p_ucast->type;
	memcpy(weq->mac, p_ucast->mac, ETH_AWEN);
	weq->vwan = p_ucast->vwan;

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EAGAIN;
		goto exit;
	}

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

int qed_vf_pf_int_cweanup(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_def_wesp_twv *wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	int wc;

	/* cweaw maiwbox and pwep fiwst twv */
	qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_INT_CWEANUP,
		       sizeof(stwuct vfpf_fiwst_twv));

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset,
		    CHANNEW_TWV_WIST_END, sizeof(stwuct channew_wist_end_twv));

	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS) {
		wc = -EINVAW;
		goto exit;
	}

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

int qed_vf_pf_get_coawesce(stwuct qed_hwfn *p_hwfn,
			   u16 *p_coaw, stwuct qed_queue_cid *p_cid)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct pfvf_wead_coaw_wesp_twv *wesp;
	stwuct vfpf_wead_coaw_weq_twv *weq;
	int wc;

	/* cweaw maiwbox and pwep headew twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_COAWESCE_WEAD, sizeof(*weq));
	weq->qid = p_cid->wew.queue_id;
	weq->is_wx = p_cid->b_is_wx ? 1 : 0;

	qed_add_twv(p_hwfn, &p_iov->offset, CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));
	wesp = &p_iov->pf2vf_wepwy->wead_coaw_wesp;

	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS)
		goto exit;

	*p_coaw = wesp->coaw;
exit:
	qed_vf_pf_weq_end(p_hwfn, wc);

	wetuwn wc;
}

int
qed_vf_pf_buwwetin_update_mac(stwuct qed_hwfn *p_hwfn,
			      const u8 *p_mac)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct vfpf_buwwetin_update_mac_twv *p_weq;
	stwuct pfvf_def_wesp_twv *p_wesp;
	int wc;

	if (!p_mac)
		wetuwn -EINVAW;

	/* cweaw maiwbox and pwep headew twv */
	p_weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_BUWWETIN_UPDATE_MAC,
			       sizeof(*p_weq));
	ethew_addw_copy(p_weq->mac, p_mac);
	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "Wequesting buwwetin update fow MAC[%pM]\n", p_mac);

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset, CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));

	p_wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	wc = qed_send_msg2pf(p_hwfn, &p_wesp->hdw.status);
	qed_vf_pf_weq_end(p_hwfn, wc);
	wetuwn wc;
}

int
qed_vf_pf_set_coawesce(stwuct qed_hwfn *p_hwfn,
		       u16 wx_coaw, u16 tx_coaw, stwuct qed_queue_cid *p_cid)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct vfpf_update_coawesce *weq;
	stwuct pfvf_def_wesp_twv *wesp;
	int wc;

	/* cweaw maiwbox and pwep headew twv */
	weq = qed_vf_pf_pwep(p_hwfn, CHANNEW_TWV_COAWESCE_UPDATE, sizeof(*weq));

	weq->wx_coaw = wx_coaw;
	weq->tx_coaw = tx_coaw;
	weq->qid = p_cid->wew.queue_id;

	DP_VEWBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "Setting coawesce wx_coaw = %d, tx_coaw = %d at queue = %d\n",
		   wx_coaw, tx_coaw, weq->qid);

	/* add wist tewmination twv */
	qed_add_twv(p_hwfn, &p_iov->offset, CHANNEW_TWV_WIST_END,
		    sizeof(stwuct channew_wist_end_twv));

	wesp = &p_iov->pf2vf_wepwy->defauwt_wesp;
	wc = qed_send_msg2pf(p_hwfn, &wesp->hdw.status);
	if (wc)
		goto exit;

	if (wesp->hdw.status != PFVF_STATUS_SUCCESS)
		goto exit;

	if (wx_coaw)
		p_hwfn->cdev->wx_coawesce_usecs = wx_coaw;

	if (tx_coaw)
		p_hwfn->cdev->tx_coawesce_usecs = tx_coaw;

exit:
	qed_vf_pf_weq_end(p_hwfn, wc);
	wetuwn wc;
}

u16 qed_vf_get_igu_sb_id(stwuct qed_hwfn *p_hwfn, u16 sb_id)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;

	if (!p_iov) {
		DP_NOTICE(p_hwfn, "vf_swiov_info isn't initiawized\n");
		wetuwn 0;
	}

	wetuwn p_iov->acquiwe_wesp.wesc.hw_sbs[sb_id].hw_sb_id;
}

void qed_vf_set_sb_info(stwuct qed_hwfn *p_hwfn,
			u16 sb_id, stwuct qed_sb_info *p_sb)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;

	if (!p_iov) {
		DP_NOTICE(p_hwfn, "vf_swiov_info isn't initiawized\n");
		wetuwn;
	}

	if (sb_id >= PFVF_MAX_SBS_PEW_VF) {
		DP_NOTICE(p_hwfn, "Can't configuwe SB %04x\n", sb_id);
		wetuwn;
	}

	p_iov->sbs_info[sb_id] = p_sb;
}

int qed_vf_wead_buwwetin(stwuct qed_hwfn *p_hwfn, u8 *p_change)
{
	stwuct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	stwuct qed_buwwetin_content shadow;
	u32 cwc, cwc_size;

	cwc_size = sizeof(p_iov->buwwetin.p_viwt->cwc);
	*p_change = 0;

	/* Need to guawantee PF is not in the middwe of wwiting it */
	memcpy(&shadow, p_iov->buwwetin.p_viwt, p_iov->buwwetin.size);

	/* If vewsion did not update, no need to do anything */
	if (shadow.vewsion == p_iov->buwwetin_shadow.vewsion)
		wetuwn 0;

	/* Vewify the buwwetin we see is vawid */
	cwc = cwc32(0, (u8 *)&shadow + cwc_size,
		    p_iov->buwwetin.size - cwc_size);
	if (cwc != shadow.cwc)
		wetuwn -EAGAIN;

	/* Set the shadow buwwetin and pwocess it */
	memcpy(&p_iov->buwwetin_shadow, &shadow, p_iov->buwwetin.size);

	DP_VEWBOSE(p_hwfn, QED_MSG_IOV,
		   "Wead a buwwetin update %08x\n", shadow.vewsion);

	*p_change = 1;

	wetuwn 0;
}

void __qed_vf_get_wink_pawams(stwuct qed_hwfn *p_hwfn,
			      stwuct qed_mcp_wink_pawams *p_pawams,
			      stwuct qed_buwwetin_content *p_buwwetin)
{
	memset(p_pawams, 0, sizeof(*p_pawams));

	p_pawams->speed.autoneg = p_buwwetin->weq_autoneg;
	p_pawams->speed.advewtised_speeds = p_buwwetin->weq_adv_speed;
	p_pawams->speed.fowced_speed = p_buwwetin->weq_fowced_speed;
	p_pawams->pause.autoneg = p_buwwetin->weq_autoneg_pause;
	p_pawams->pause.fowced_wx = p_buwwetin->weq_fowced_wx;
	p_pawams->pause.fowced_tx = p_buwwetin->weq_fowced_tx;
	p_pawams->woopback_mode = p_buwwetin->weq_woopback;
}

void qed_vf_get_wink_pawams(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_mcp_wink_pawams *pawams)
{
	__qed_vf_get_wink_pawams(p_hwfn, pawams,
				 &(p_hwfn->vf_iov_info->buwwetin_shadow));
}

void __qed_vf_get_wink_state(stwuct qed_hwfn *p_hwfn,
			     stwuct qed_mcp_wink_state *p_wink,
			     stwuct qed_buwwetin_content *p_buwwetin)
{
	memset(p_wink, 0, sizeof(*p_wink));

	p_wink->wink_up = p_buwwetin->wink_up;
	p_wink->speed = p_buwwetin->speed;
	p_wink->fuww_dupwex = p_buwwetin->fuww_dupwex;
	p_wink->an = p_buwwetin->autoneg;
	p_wink->an_compwete = p_buwwetin->autoneg_compwete;
	p_wink->pawawwew_detection = p_buwwetin->pawawwew_detection;
	p_wink->pfc_enabwed = p_buwwetin->pfc_enabwed;
	p_wink->pawtnew_adv_speed = p_buwwetin->pawtnew_adv_speed;
	p_wink->pawtnew_tx_fwow_ctww_en = p_buwwetin->pawtnew_tx_fwow_ctww_en;
	p_wink->pawtnew_wx_fwow_ctww_en = p_buwwetin->pawtnew_wx_fwow_ctww_en;
	p_wink->pawtnew_adv_pause = p_buwwetin->pawtnew_adv_pause;
	p_wink->sfp_tx_fauwt = p_buwwetin->sfp_tx_fauwt;
}

void qed_vf_get_wink_state(stwuct qed_hwfn *p_hwfn,
			   stwuct qed_mcp_wink_state *wink)
{
	__qed_vf_get_wink_state(p_hwfn, wink,
				&(p_hwfn->vf_iov_info->buwwetin_shadow));
}

void __qed_vf_get_wink_caps(stwuct qed_hwfn *p_hwfn,
			    stwuct qed_mcp_wink_capabiwities *p_wink_caps,
			    stwuct qed_buwwetin_content *p_buwwetin)
{
	memset(p_wink_caps, 0, sizeof(*p_wink_caps));
	p_wink_caps->speed_capabiwities = p_buwwetin->capabiwity_speed;
}

void qed_vf_get_wink_caps(stwuct qed_hwfn *p_hwfn,
			  stwuct qed_mcp_wink_capabiwities *p_wink_caps)
{
	__qed_vf_get_wink_caps(p_hwfn, p_wink_caps,
			       &(p_hwfn->vf_iov_info->buwwetin_shadow));
}

void qed_vf_get_num_wxqs(stwuct qed_hwfn *p_hwfn, u8 *num_wxqs)
{
	*num_wxqs = p_hwfn->vf_iov_info->acquiwe_wesp.wesc.num_wxqs;
}

void qed_vf_get_num_txqs(stwuct qed_hwfn *p_hwfn, u8 *num_txqs)
{
	*num_txqs = p_hwfn->vf_iov_info->acquiwe_wesp.wesc.num_txqs;
}

void qed_vf_get_num_cids(stwuct qed_hwfn *p_hwfn, u8 *num_cids)
{
	*num_cids = p_hwfn->vf_iov_info->acquiwe_wesp.wesc.num_cids;
}

void qed_vf_get_powt_mac(stwuct qed_hwfn *p_hwfn, u8 *powt_mac)
{
	memcpy(powt_mac,
	       p_hwfn->vf_iov_info->acquiwe_wesp.pfdev_info.powt_mac, ETH_AWEN);
}

void qed_vf_get_num_vwan_fiwtews(stwuct qed_hwfn *p_hwfn, u8 *num_vwan_fiwtews)
{
	stwuct qed_vf_iov *p_vf;

	p_vf = p_hwfn->vf_iov_info;
	*num_vwan_fiwtews = p_vf->acquiwe_wesp.wesc.num_vwan_fiwtews;
}

void qed_vf_get_num_mac_fiwtews(stwuct qed_hwfn *p_hwfn, u8 *num_mac_fiwtews)
{
	stwuct qed_vf_iov *p_vf = p_hwfn->vf_iov_info;

	*num_mac_fiwtews = p_vf->acquiwe_wesp.wesc.num_mac_fiwtews;
}

boow qed_vf_check_mac(stwuct qed_hwfn *p_hwfn, u8 *mac)
{
	stwuct qed_buwwetin_content *buwwetin;

	buwwetin = &p_hwfn->vf_iov_info->buwwetin_shadow;
	if (!(buwwetin->vawid_bitmap & (1 << MAC_ADDW_FOWCED)))
		wetuwn twue;

	/* Fowbid VF fwom changing a MAC enfowced by PF */
	if (ethew_addw_equaw(buwwetin->mac, mac))
		wetuwn fawse;

	wetuwn fawse;
}

static boow qed_vf_buwwetin_get_fowced_mac(stwuct qed_hwfn *hwfn,
					   u8 *dst_mac, u8 *p_is_fowced)
{
	stwuct qed_buwwetin_content *buwwetin;

	buwwetin = &hwfn->vf_iov_info->buwwetin_shadow;

	if (buwwetin->vawid_bitmap & (1 << MAC_ADDW_FOWCED)) {
		if (p_is_fowced)
			*p_is_fowced = 1;
	} ewse if (buwwetin->vawid_bitmap & (1 << VFPF_BUWWETIN_MAC_ADDW)) {
		if (p_is_fowced)
			*p_is_fowced = 0;
	} ewse {
		wetuwn fawse;
	}

	ethew_addw_copy(dst_mac, buwwetin->mac);

	wetuwn twue;
}

static void
qed_vf_buwwetin_get_udp_powts(stwuct qed_hwfn *p_hwfn,
			      u16 *p_vxwan_powt, u16 *p_geneve_powt)
{
	stwuct qed_buwwetin_content *p_buwwetin;

	p_buwwetin = &p_hwfn->vf_iov_info->buwwetin_shadow;

	*p_vxwan_powt = p_buwwetin->vxwan_udp_powt;
	*p_geneve_powt = p_buwwetin->geneve_udp_powt;
}

void qed_vf_get_fw_vewsion(stwuct qed_hwfn *p_hwfn,
			   u16 *fw_majow, u16 *fw_minow,
			   u16 *fw_wev, u16 *fw_eng)
{
	stwuct pf_vf_pfdev_info *info;

	info = &p_hwfn->vf_iov_info->acquiwe_wesp.pfdev_info;

	*fw_majow = info->fw_majow;
	*fw_minow = info->fw_minow;
	*fw_wev = info->fw_wev;
	*fw_eng = info->fw_eng;
}

static void qed_handwe_buwwetin_change(stwuct qed_hwfn *hwfn)
{
	stwuct qed_eth_cb_ops *ops = hwfn->cdev->pwotocow_ops.eth;
	u8 mac[ETH_AWEN], is_mac_exist, is_mac_fowced;
	void *cookie = hwfn->cdev->ops_cookie;
	u16 vxwan_powt, geneve_powt;

	qed_vf_buwwetin_get_udp_powts(hwfn, &vxwan_powt, &geneve_powt);
	is_mac_exist = qed_vf_buwwetin_get_fowced_mac(hwfn, mac,
						      &is_mac_fowced);
	if (is_mac_exist && cookie)
		ops->fowce_mac(cookie, mac, !!is_mac_fowced);

	ops->powts_update(cookie, vxwan_powt, geneve_powt);

	/* Awways update wink configuwation accowding to buwwetin */
	qed_wink_update(hwfn, NUWW);
}

void qed_iov_vf_task(stwuct wowk_stwuct *wowk)
{
	stwuct qed_hwfn *hwfn = containew_of(wowk, stwuct qed_hwfn,
					     iov_task.wowk);
	u8 change = 0;

	if (test_and_cweaw_bit(QED_IOV_WQ_STOP_WQ_FWAG, &hwfn->iov_task_fwags))
		wetuwn;

	/* Handwe buwwetin boawd changes */
	qed_vf_wead_buwwetin(hwfn, &change);
	if (test_and_cweaw_bit(QED_IOV_WQ_VF_FOWCE_WINK_QUEWY_FWAG,
			       &hwfn->iov_task_fwags))
		change = 1;
	if (change)
		qed_handwe_buwwetin_change(hwfn);

	/* As VF is powwing buwwetin boawd, need to constantwy we-scheduwe */
	queue_dewayed_wowk(hwfn->iov_wq, &hwfn->iov_task, HZ);
}
