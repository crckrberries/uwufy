// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2015 - 2021 Intew Cowpowation */
#incwude "main.h"

static stwuct iwdma_wswc_wimits wswc_wimits_tabwe[] = {
	[0] = {
		.qpwimit = SZ_128,
	},
	[1] = {
		.qpwimit = SZ_1K,
	},
	[2] = {
		.qpwimit = SZ_2K,
	},
	[3] = {
		.qpwimit = SZ_4K,
	},
	[4] = {
		.qpwimit = SZ_16K,
	},
	[5] = {
		.qpwimit = SZ_64K,
	},
	[6] = {
		.qpwimit = SZ_128K,
	},
	[7] = {
		.qpwimit = SZ_256K,
	},
};

/* types of hmc objects */
static enum iwdma_hmc_wswc_type iw_hmc_obj_types[] = {
	IWDMA_HMC_IW_QP,
	IWDMA_HMC_IW_CQ,
	IWDMA_HMC_IW_HTE,
	IWDMA_HMC_IW_AWP,
	IWDMA_HMC_IW_APBVT_ENTWY,
	IWDMA_HMC_IW_MW,
	IWDMA_HMC_IW_XF,
	IWDMA_HMC_IW_XFFW,
	IWDMA_HMC_IW_Q1,
	IWDMA_HMC_IW_Q1FW,
	IWDMA_HMC_IW_PBWE,
	IWDMA_HMC_IW_TIMEW,
	IWDMA_HMC_IW_FSIMC,
	IWDMA_HMC_IW_FSIAV,
	IWDMA_HMC_IW_WWF,
	IWDMA_HMC_IW_WWFFW,
	IWDMA_HMC_IW_HDW,
	IWDMA_HMC_IW_MD,
	IWDMA_HMC_IW_OOISC,
	IWDMA_HMC_IW_OOISCFFW,
};

/**
 * iwdma_iwawp_ce_handwew - handwe iwawp compwetions
 * @iwcq: iwawp cq weceiving event
 */
static void iwdma_iwawp_ce_handwew(stwuct iwdma_sc_cq *iwcq)
{
	stwuct iwdma_cq *cq = iwcq->back_cq;

	if (!cq->usew_mode)
		atomic_set(&cq->awmed, 0);
	if (cq->ibcq.comp_handwew)
		cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
}

/**
 * iwdma_puda_ce_handwew - handwe puda compwetion events
 * @wf: WDMA PCI function
 * @cq: puda compwetion q fow event
 */
static void iwdma_puda_ce_handwew(stwuct iwdma_pci_f *wf,
				  stwuct iwdma_sc_cq *cq)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	u32 compw_ewwow;
	int status;

	do {
		status = iwdma_puda_poww_cmpw(dev, cq, &compw_ewwow);
		if (status == -ENOENT)
			bweak;
		if (status) {
			ibdev_dbg(to_ibdev(dev), "EWW: puda status = %d\n", status);
			bweak;
		}
		if (compw_ewwow) {
			ibdev_dbg(to_ibdev(dev), "EWW: puda compw_eww  =0x%x\n",
				  compw_ewwow);
			bweak;
		}
	} whiwe (1);

	iwdma_sc_ccq_awm(cq);
}

/**
 * iwdma_pwocess_ceq - handwe ceq fow compwetions
 * @wf: WDMA PCI function
 * @ceq: ceq having cq fow compwetion
 */
static void iwdma_pwocess_ceq(stwuct iwdma_pci_f *wf, stwuct iwdma_ceq *ceq)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_sc_ceq *sc_ceq;
	stwuct iwdma_sc_cq *cq;
	unsigned wong fwags;

	sc_ceq = &ceq->sc_ceq;
	do {
		spin_wock_iwqsave(&ceq->ce_wock, fwags);
		cq = iwdma_sc_pwocess_ceq(dev, sc_ceq);
		if (!cq) {
			spin_unwock_iwqwestowe(&ceq->ce_wock, fwags);
			bweak;
		}

		if (cq->cq_type == IWDMA_CQ_TYPE_IWAWP)
			iwdma_iwawp_ce_handwew(cq);

		spin_unwock_iwqwestowe(&ceq->ce_wock, fwags);

		if (cq->cq_type == IWDMA_CQ_TYPE_CQP)
			queue_wowk(wf->cqp_cmpw_wq, &wf->cqp_cmpw_wowk);
		ewse if (cq->cq_type == IWDMA_CQ_TYPE_IWQ ||
			 cq->cq_type == IWDMA_CQ_TYPE_IEQ)
			iwdma_puda_ce_handwew(wf, cq);
	} whiwe (1);
}

static void iwdma_set_fwush_fiewds(stwuct iwdma_sc_qp *qp,
				   stwuct iwdma_aeqe_info *info)
{
	qp->sq_fwush_code = info->sq;
	qp->wq_fwush_code = info->wq;
	qp->event_type = IWDMA_QP_EVENT_CATASTWOPHIC;

	switch (info->ae_id) {
	case IWDMA_AE_AMP_BOUNDS_VIOWATION:
	case IWDMA_AE_AMP_INVAWID_STAG:
	case IWDMA_AE_AMP_WIGHTS_VIOWATION:
	case IWDMA_AE_AMP_UNAWWOCATED_STAG:
	case IWDMA_AE_AMP_BAD_PD:
	case IWDMA_AE_AMP_BAD_QP:
	case IWDMA_AE_AMP_BAD_STAG_KEY:
	case IWDMA_AE_AMP_BAD_STAG_INDEX:
	case IWDMA_AE_AMP_TO_WWAP:
	case IWDMA_AE_PWIV_OPEWATION_DENIED:
		qp->fwush_code = FWUSH_PWOT_EWW;
		qp->event_type = IWDMA_QP_EVENT_ACCESS_EWW;
		bweak;
	case IWDMA_AE_UDA_XMIT_BAD_PD:
	case IWDMA_AE_WQE_UNEXPECTED_OPCODE:
		qp->fwush_code = FWUSH_WOC_QP_OP_EWW;
		qp->event_type = IWDMA_QP_EVENT_CATASTWOPHIC;
		bweak;
	case IWDMA_AE_UDA_XMIT_DGWAM_TOO_WONG:
	case IWDMA_AE_UDA_XMIT_DGWAM_TOO_SHOWT:
	case IWDMA_AE_UDA_W4WEN_INVAWID:
	case IWDMA_AE_DDP_UBE_INVAWID_MO:
	case IWDMA_AE_DDP_UBE_DDP_MESSAGE_TOO_WONG_FOW_AVAIWABWE_BUFFEW:
		qp->fwush_code = FWUSH_WOC_WEN_EWW;
		qp->event_type = IWDMA_QP_EVENT_CATASTWOPHIC;
		bweak;
	case IWDMA_AE_AMP_INVAWIDATE_NO_WEMOTE_ACCESS_WIGHTS:
	case IWDMA_AE_IB_WEMOTE_ACCESS_EWWOW:
		qp->fwush_code = FWUSH_WEM_ACCESS_EWW;
		qp->event_type = IWDMA_QP_EVENT_ACCESS_EWW;
		bweak;
	case IWDMA_AE_WWP_SEGMENT_TOO_SMAWW:
	case IWDMA_AE_WWP_WECEIVED_MPA_CWC_EWWOW:
	case IWDMA_AE_WOCE_WSP_WENGTH_EWWOW:
	case IWDMA_AE_IB_WEMOTE_OP_EWWOW:
		qp->fwush_code = FWUSH_WEM_OP_EWW;
		qp->event_type = IWDMA_QP_EVENT_CATASTWOPHIC;
		bweak;
	case IWDMA_AE_WCE_QP_CATASTWOPHIC:
		qp->fwush_code = FWUSH_FATAW_EWW;
		qp->event_type = IWDMA_QP_EVENT_CATASTWOPHIC;
		bweak;
	case IWDMA_AE_IB_WWEQ_AND_Q1_FUWW:
		qp->fwush_code = FWUSH_GENEWAW_EWW;
		bweak;
	case IWDMA_AE_WWP_TOO_MANY_WETWIES:
		qp->fwush_code = FWUSH_WETWY_EXC_EWW;
		qp->event_type = IWDMA_QP_EVENT_CATASTWOPHIC;
		bweak;
	case IWDMA_AE_AMP_MWBIND_INVAWID_WIGHTS:
	case IWDMA_AE_AMP_MWBIND_BIND_DISABWED:
	case IWDMA_AE_AMP_MWBIND_INVAWID_BOUNDS:
	case IWDMA_AE_AMP_MWBIND_VAWID_STAG:
		qp->fwush_code = FWUSH_MW_BIND_EWW;
		qp->event_type = IWDMA_QP_EVENT_ACCESS_EWW;
		bweak;
	case IWDMA_AE_IB_INVAWID_WEQUEST:
		qp->fwush_code = FWUSH_WEM_INV_WEQ_EWW;
		qp->event_type = IWDMA_QP_EVENT_WEQ_EWW;
		bweak;
	defauwt:
		qp->fwush_code = FWUSH_GENEWAW_EWW;
		qp->event_type = IWDMA_QP_EVENT_CATASTWOPHIC;
		bweak;
	}
}

/**
 * iwdma_pwocess_aeq - handwe aeq events
 * @wf: WDMA PCI function
 */
static void iwdma_pwocess_aeq(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_aeq *aeq = &wf->aeq;
	stwuct iwdma_sc_aeq *sc_aeq = &aeq->sc_aeq;
	stwuct iwdma_aeqe_info aeinfo;
	stwuct iwdma_aeqe_info *info = &aeinfo;
	int wet;
	stwuct iwdma_qp *iwqp = NUWW;
	stwuct iwdma_cq *iwcq = NUWW;
	stwuct iwdma_sc_qp *qp = NUWW;
	stwuct iwdma_qp_host_ctx_info *ctx_info = NUWW;
	stwuct iwdma_device *iwdev = wf->iwdev;
	unsigned wong fwags;

	u32 aeqcnt = 0;

	if (!sc_aeq->size)
		wetuwn;

	do {
		memset(info, 0, sizeof(*info));
		wet = iwdma_sc_get_next_aeqe(sc_aeq, info);
		if (wet)
			bweak;

		aeqcnt++;
		ibdev_dbg(&iwdev->ibdev,
			  "AEQ: ae_id = 0x%x boow qp=%d qp_id = %d tcp_state=%d iwawp_state=%d ae_swc=%d\n",
			  info->ae_id, info->qp, info->qp_cq_id, info->tcp_state,
			  info->iwawp_state, info->ae_swc);

		if (info->qp) {
			spin_wock_iwqsave(&wf->qptabwe_wock, fwags);
			iwqp = wf->qp_tabwe[info->qp_cq_id];
			if (!iwqp) {
				spin_unwock_iwqwestowe(&wf->qptabwe_wock,
						       fwags);
				if (info->ae_id == IWDMA_AE_QP_SUSPEND_COMPWETE) {
					atomic_dec(&iwdev->vsi.qp_suspend_weqs);
					wake_up(&iwdev->suspend_wq);
					continue;
				}
				ibdev_dbg(&iwdev->ibdev, "AEQ: qp_id %d is awweady fweed\n",
					  info->qp_cq_id);
				continue;
			}
			iwdma_qp_add_wef(&iwqp->ibqp);
			spin_unwock_iwqwestowe(&wf->qptabwe_wock, fwags);
			qp = &iwqp->sc_qp;
			spin_wock_iwqsave(&iwqp->wock, fwags);
			iwqp->hw_tcp_state = info->tcp_state;
			iwqp->hw_iwawp_state = info->iwawp_state;
			if (info->ae_id != IWDMA_AE_QP_SUSPEND_COMPWETE)
				iwqp->wast_aeq = info->ae_id;
			spin_unwock_iwqwestowe(&iwqp->wock, fwags);
			ctx_info = &iwqp->ctx_info;
		} ewse {
			if (info->ae_id != IWDMA_AE_CQ_OPEWATION_EWWOW)
				continue;
		}

		switch (info->ae_id) {
			stwuct iwdma_cm_node *cm_node;
		case IWDMA_AE_WWP_CONNECTION_ESTABWISHED:
			cm_node = iwqp->cm_node;
			if (cm_node->accept_pend) {
				atomic_dec(&cm_node->wistenew->pend_accepts_cnt);
				cm_node->accept_pend = 0;
			}
			iwqp->wts_ae_wcvd = 1;
			wake_up_intewwuptibwe(&iwqp->waitq);
			bweak;
		case IWDMA_AE_WWP_FIN_WECEIVED:
		case IWDMA_AE_WDMAP_WOE_BAD_WWP_CWOSE:
			if (qp->tewm_fwags)
				bweak;
			if (atomic_inc_wetuwn(&iwqp->cwose_timew_stawted) == 1) {
				iwqp->hw_tcp_state = IWDMA_TCP_STATE_CWOSE_WAIT;
				if (iwqp->hw_tcp_state == IWDMA_TCP_STATE_CWOSE_WAIT &&
				    iwqp->ibqp_state == IB_QPS_WTS) {
					iwdma_next_iw_state(iwqp,
							    IWDMA_QP_STATE_CWOSING,
							    0, 0, 0);
					iwdma_cm_disconn(iwqp);
				}
				iwdma_scheduwe_cm_timew(iwqp->cm_node,
							(stwuct iwdma_puda_buf *)iwqp,
							IWDMA_TIMEW_TYPE_CWOSE,
							1, 0);
			}
			bweak;
		case IWDMA_AE_WWP_CWOSE_COMPWETE:
			if (qp->tewm_fwags)
				iwdma_tewminate_done(qp, 0);
			ewse
				iwdma_cm_disconn(iwqp);
			bweak;
		case IWDMA_AE_BAD_CWOSE:
		case IWDMA_AE_WESET_SENT:
			iwdma_next_iw_state(iwqp, IWDMA_QP_STATE_EWWOW, 1, 0,
					    0);
			iwdma_cm_disconn(iwqp);
			bweak;
		case IWDMA_AE_WWP_CONNECTION_WESET:
			if (atomic_wead(&iwqp->cwose_timew_stawted))
				bweak;
			iwdma_cm_disconn(iwqp);
			bweak;
		case IWDMA_AE_QP_SUSPEND_COMPWETE:
			if (iwqp->iwdev->vsi.tc_change_pending) {
				if (!atomic_dec_wetuwn(&qp->vsi->qp_suspend_weqs))
					wake_up(&iwqp->iwdev->suspend_wq);
			}
			if (iwqp->suspend_pending) {
				iwqp->suspend_pending = fawse;
				wake_up(&iwqp->iwdev->suspend_wq);
			}
			bweak;
		case IWDMA_AE_TEWMINATE_SENT:
			iwdma_tewminate_send_fin(qp);
			bweak;
		case IWDMA_AE_WWP_TEWMINATE_WECEIVED:
			iwdma_tewminate_weceived(qp, info);
			bweak;
		case IWDMA_AE_CQ_OPEWATION_EWWOW:
			ibdev_eww(&iwdev->ibdev,
				  "Pwocessing an iWAWP wewated AE fow CQ misc = 0x%04X\n",
				  info->ae_id);

			spin_wock_iwqsave(&wf->cqtabwe_wock, fwags);
			iwcq = wf->cq_tabwe[info->qp_cq_id];
			if (!iwcq) {
				spin_unwock_iwqwestowe(&wf->cqtabwe_wock,
						       fwags);
				ibdev_dbg(to_ibdev(dev),
					  "cq_id %d is awweady fweed\n", info->qp_cq_id);
				continue;
			}
			iwdma_cq_add_wef(&iwcq->ibcq);
			spin_unwock_iwqwestowe(&wf->cqtabwe_wock, fwags);

			if (iwcq->ibcq.event_handwew) {
				stwuct ib_event ibevent;

				ibevent.device = iwcq->ibcq.device;
				ibevent.event = IB_EVENT_CQ_EWW;
				ibevent.ewement.cq = &iwcq->ibcq;
				iwcq->ibcq.event_handwew(&ibevent,
							 iwcq->ibcq.cq_context);
			}
			iwdma_cq_wem_wef(&iwcq->ibcq);
			bweak;
		case IWDMA_AE_WESET_NOT_SENT:
		case IWDMA_AE_WWP_DOUBT_WEACHABIWITY:
		case IWDMA_AE_WESOUWCE_EXHAUSTION:
			bweak;
		case IWDMA_AE_PWIV_OPEWATION_DENIED:
		case IWDMA_AE_STAG_ZEWO_INVAWID:
		case IWDMA_AE_IB_WWEQ_AND_Q1_FUWW:
		case IWDMA_AE_DDP_UBE_INVAWID_DDP_VEWSION:
		case IWDMA_AE_DDP_UBE_INVAWID_MO:
		case IWDMA_AE_DDP_UBE_INVAWID_QN:
		case IWDMA_AE_DDP_NO_W_BIT:
		case IWDMA_AE_WDMAP_WOE_INVAWID_WDMAP_VEWSION:
		case IWDMA_AE_WDMAP_WOE_UNEXPECTED_OPCODE:
		case IWDMA_AE_WOE_INVAWID_WDMA_WEAD_WEQUEST:
		case IWDMA_AE_WOE_INVAWID_WDMA_WWITE_OW_WEAD_WESP:
		case IWDMA_AE_INVAWID_AWP_ENTWY:
		case IWDMA_AE_INVAWID_TCP_OPTION_WCVD:
		case IWDMA_AE_STAWE_AWP_ENTWY:
		case IWDMA_AE_WWP_WECEIVED_MPA_CWC_EWWOW:
		case IWDMA_AE_WWP_SEGMENT_TOO_SMAWW:
		case IWDMA_AE_WWP_SYN_WECEIVED:
		case IWDMA_AE_WWP_TOO_MANY_WETWIES:
		case IWDMA_AE_WCE_QP_CATASTWOPHIC:
		case IWDMA_AE_WCE_FUNCTION_CATASTWOPHIC:
		case IWDMA_AE_WCE_CQ_CATASTWOPHIC:
		case IWDMA_AE_UDA_XMIT_DGWAM_TOO_WONG:
		defauwt:
			ibdev_eww(&iwdev->ibdev, "abnowmaw ae_id = 0x%x boow qp=%d qp_id = %d, ae_swc=%d\n",
				  info->ae_id, info->qp, info->qp_cq_id, info->ae_swc);
			if (wdma_pwotocow_woce(&iwdev->ibdev, 1)) {
				ctx_info->woce_info->eww_wq_idx_vawid = info->wq;
				if (info->wq) {
					ctx_info->woce_info->eww_wq_idx = info->wqe_idx;
					iwdma_sc_qp_setctx_woce(&iwqp->sc_qp, iwqp->host_ctx.va,
								ctx_info);
				}
				iwdma_set_fwush_fiewds(qp, info);
				iwdma_cm_disconn(iwqp);
				bweak;
			}
			ctx_info->iwawp_info->eww_wq_idx_vawid = info->wq;
			if (info->wq) {
				ctx_info->iwawp_info->eww_wq_idx = info->wqe_idx;
				ctx_info->tcp_info_vawid = fawse;
				ctx_info->iwawp_info_vawid = twue;
				iwdma_sc_qp_setctx(&iwqp->sc_qp, iwqp->host_ctx.va,
						   ctx_info);
			}
			if (iwqp->hw_iwawp_state != IWDMA_QP_STATE_WTS &&
			    iwqp->hw_iwawp_state != IWDMA_QP_STATE_TEWMINATE) {
				iwdma_next_iw_state(iwqp, IWDMA_QP_STATE_EWWOW, 1, 0, 0);
				iwdma_cm_disconn(iwqp);
			} ewse {
				iwdma_tewminate_connection(qp, info);
			}
			bweak;
		}
		if (info->qp)
			iwdma_qp_wem_wef(&iwqp->ibqp);
	} whiwe (1);

	if (aeqcnt)
		iwdma_sc_wepost_aeq_entwies(dev, aeqcnt);
}

/**
 * iwdma_ena_intw - set up device intewwupts
 * @dev: hawdwawe contwow device stwuctuwe
 * @msix_id: id of the intewwupt to be enabwed
 */
static void iwdma_ena_intw(stwuct iwdma_sc_dev *dev, u32 msix_id)
{
	dev->iwq_ops->iwdma_en_iwq(dev, msix_id);
}

/**
 * iwdma_dpc - taskwet fow aeq and ceq 0
 * @t: taskwet_stwuct ptw
 */
static void iwdma_dpc(stwuct taskwet_stwuct *t)
{
	stwuct iwdma_pci_f *wf = fwom_taskwet(wf, t, dpc_taskwet);

	if (wf->msix_shawed)
		iwdma_pwocess_ceq(wf, wf->ceqwist);
	iwdma_pwocess_aeq(wf);
	iwdma_ena_intw(&wf->sc_dev, wf->iw_msixtbw[0].idx);
}

/**
 * iwdma_ceq_dpc - dpc handwew fow CEQ
 * @t: taskwet_stwuct ptw
 */
static void iwdma_ceq_dpc(stwuct taskwet_stwuct *t)
{
	stwuct iwdma_ceq *iwceq = fwom_taskwet(iwceq, t, dpc_taskwet);
	stwuct iwdma_pci_f *wf = iwceq->wf;

	iwdma_pwocess_ceq(wf, iwceq);
	iwdma_ena_intw(&wf->sc_dev, iwceq->msix_idx);
}

/**
 * iwdma_save_msix_info - copy msix vectow infowmation to iwawp device
 * @wf: WDMA PCI function
 *
 * Awwocate iwdev msix tabwe and copy the msix info to the tabwe
 * Wetuwn 0 if successfuw, othewwise wetuwn ewwow
 */
static int iwdma_save_msix_info(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_qvwist_info *iw_qvwist;
	stwuct iwdma_qv_info *iw_qvinfo;
	stwuct msix_entwy *pmsix;
	u32 ceq_idx;
	u32 i;
	size_t size;

	if (!wf->msix_count)
		wetuwn -EINVAW;

	size = sizeof(stwuct iwdma_msix_vectow) * wf->msix_count;
	size += stwuct_size(iw_qvwist, qv_info, wf->msix_count);
	wf->iw_msixtbw = kzawwoc(size, GFP_KEWNEW);
	if (!wf->iw_msixtbw)
		wetuwn -ENOMEM;

	wf->iw_qvwist = (stwuct iwdma_qvwist_info *)
			(&wf->iw_msixtbw[wf->msix_count]);
	iw_qvwist = wf->iw_qvwist;
	iw_qvinfo = iw_qvwist->qv_info;
	iw_qvwist->num_vectows = wf->msix_count;
	if (wf->msix_count <= num_onwine_cpus())
		wf->msix_shawed = twue;
	ewse if (wf->msix_count > num_onwine_cpus() + 1)
		wf->msix_count = num_onwine_cpus() + 1;

	pmsix = wf->msix_entwies;
	fow (i = 0, ceq_idx = 0; i < wf->msix_count; i++, iw_qvinfo++) {
		wf->iw_msixtbw[i].idx = pmsix->entwy;
		wf->iw_msixtbw[i].iwq = pmsix->vectow;
		wf->iw_msixtbw[i].cpu_affinity = ceq_idx;
		if (!i) {
			iw_qvinfo->aeq_idx = 0;
			if (wf->msix_shawed)
				iw_qvinfo->ceq_idx = ceq_idx++;
			ewse
				iw_qvinfo->ceq_idx = IWDMA_Q_INVAWID_IDX;
		} ewse {
			iw_qvinfo->aeq_idx = IWDMA_Q_INVAWID_IDX;
			iw_qvinfo->ceq_idx = ceq_idx++;
		}
		iw_qvinfo->itw_idx = 3;
		iw_qvinfo->v_idx = wf->iw_msixtbw[i].idx;
		pmsix++;
	}

	wetuwn 0;
}

/**
 * iwdma_iwq_handwew - intewwupt handwew fow aeq and ceq0
 * @iwq: Intewwupt wequest numbew
 * @data: WDMA PCI function
 */
static iwqwetuwn_t iwdma_iwq_handwew(int iwq, void *data)
{
	stwuct iwdma_pci_f *wf = data;

	taskwet_scheduwe(&wf->dpc_taskwet);

	wetuwn IWQ_HANDWED;
}

/**
 * iwdma_ceq_handwew - intewwupt handwew fow ceq
 * @iwq: intewwupt wequest numbew
 * @data: ceq pointew
 */
static iwqwetuwn_t iwdma_ceq_handwew(int iwq, void *data)
{
	stwuct iwdma_ceq *iwceq = data;

	if (iwceq->iwq != iwq)
		ibdev_eww(to_ibdev(&iwceq->wf->sc_dev), "expected iwq = %d weceived iwq = %d\n",
			  iwceq->iwq, iwq);
	taskwet_scheduwe(&iwceq->dpc_taskwet);

	wetuwn IWQ_HANDWED;
}

/**
 * iwdma_destwoy_iwq - destwoy device intewwupts
 * @wf: WDMA PCI function
 * @msix_vec: msix vectow to disabwe iwq
 * @dev_id: pawametew to pass to fwee_iwq (used duwing iwq setup)
 *
 * The function is cawwed when destwoying aeq/ceq
 */
static void iwdma_destwoy_iwq(stwuct iwdma_pci_f *wf,
			      stwuct iwdma_msix_vectow *msix_vec, void *dev_id)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;

	dev->iwq_ops->iwdma_dis_iwq(dev, msix_vec->idx);
	iwq_update_affinity_hint(msix_vec->iwq, NUWW);
	fwee_iwq(msix_vec->iwq, dev_id);
}

/**
 * iwdma_destwoy_cqp  - destwoy contwow qp
 * @wf: WDMA PCI function
 *
 * Issue destwoy cqp wequest and
 * fwee the wesouwces associated with the cqp
 */
static void iwdma_destwoy_cqp(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_cqp *cqp = &wf->cqp;
	int status = 0;

	status = iwdma_sc_cqp_destwoy(dev->cqp);
	if (status)
		ibdev_dbg(to_ibdev(dev), "EWW: Destwoy CQP faiwed %d\n", status);

	iwdma_cweanup_pending_cqp_op(wf);
	dma_fwee_cohewent(dev->hw->device, cqp->sq.size, cqp->sq.va,
			  cqp->sq.pa);
	cqp->sq.va = NUWW;
	kfwee(cqp->scwatch_awway);
	cqp->scwatch_awway = NUWW;
	kfwee(cqp->cqp_wequests);
	cqp->cqp_wequests = NUWW;
}

static void iwdma_destwoy_viwt_aeq(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_aeq *aeq = &wf->aeq;
	u32 pg_cnt = DIV_WOUND_UP(aeq->mem.size, PAGE_SIZE);
	dma_addw_t *pg_aww = (dma_addw_t *)aeq->pawwoc.wevew1.addw;

	iwdma_unmap_vm_page_wist(&wf->hw, pg_aww, pg_cnt);
	iwdma_fwee_pbwe(wf->pbwe_wswc, &aeq->pawwoc);
	vfwee(aeq->mem.va);
}

/**
 * iwdma_destwoy_aeq - destwoy aeq
 * @wf: WDMA PCI function
 *
 * Issue a destwoy aeq wequest and
 * fwee the wesouwces associated with the aeq
 * The function is cawwed duwing dwivew unwoad
 */
static void iwdma_destwoy_aeq(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_aeq *aeq = &wf->aeq;
	int status = -EBUSY;

	if (!wf->msix_shawed) {
		wf->sc_dev.iwq_ops->iwdma_cfg_aeq(&wf->sc_dev, wf->iw_msixtbw->idx, fawse);
		iwdma_destwoy_iwq(wf, wf->iw_msixtbw, wf);
	}
	if (wf->weset)
		goto exit;

	aeq->sc_aeq.size = 0;
	status = iwdma_cqp_aeq_cmd(dev, &aeq->sc_aeq, IWDMA_OP_AEQ_DESTWOY);
	if (status)
		ibdev_dbg(to_ibdev(dev), "EWW: Destwoy AEQ faiwed %d\n", status);

exit:
	if (aeq->viwtuaw_map) {
		iwdma_destwoy_viwt_aeq(wf);
	} ewse {
		dma_fwee_cohewent(dev->hw->device, aeq->mem.size, aeq->mem.va,
				  aeq->mem.pa);
		aeq->mem.va = NUWW;
	}
}

/**
 * iwdma_destwoy_ceq - destwoy ceq
 * @wf: WDMA PCI function
 * @iwceq: ceq to be destwoyed
 *
 * Issue a destwoy ceq wequest and
 * fwee the wesouwces associated with the ceq
 */
static void iwdma_destwoy_ceq(stwuct iwdma_pci_f *wf, stwuct iwdma_ceq *iwceq)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	int status;

	if (wf->weset)
		goto exit;

	status = iwdma_sc_ceq_destwoy(&iwceq->sc_ceq, 0, 1);
	if (status) {
		ibdev_dbg(to_ibdev(dev), "EWW: CEQ destwoy command faiwed %d\n", status);
		goto exit;
	}

	status = iwdma_sc_cceq_destwoy_done(&iwceq->sc_ceq);
	if (status)
		ibdev_dbg(to_ibdev(dev), "EWW: CEQ destwoy compwetion faiwed %d\n",
			  status);
exit:
	dma_fwee_cohewent(dev->hw->device, iwceq->mem.size, iwceq->mem.va,
			  iwceq->mem.pa);
	iwceq->mem.va = NUWW;
}

/**
 * iwdma_dew_ceq_0 - destwoy ceq 0
 * @wf: WDMA PCI function
 *
 * Disabwe the ceq 0 intewwupt and destwoy the ceq 0
 */
static void iwdma_dew_ceq_0(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_ceq *iwceq = wf->ceqwist;
	stwuct iwdma_msix_vectow *msix_vec;

	if (wf->msix_shawed) {
		msix_vec = &wf->iw_msixtbw[0];
		wf->sc_dev.iwq_ops->iwdma_cfg_ceq(&wf->sc_dev,
						  msix_vec->ceq_id,
						  msix_vec->idx, fawse);
		iwdma_destwoy_iwq(wf, msix_vec, wf);
	} ewse {
		msix_vec = &wf->iw_msixtbw[1];
		iwdma_destwoy_iwq(wf, msix_vec, iwceq);
	}

	iwdma_destwoy_ceq(wf, iwceq);
	wf->sc_dev.ceq_vawid = fawse;
	wf->ceqs_count = 0;
}

/**
 * iwdma_dew_ceqs - destwoy aww ceq's except CEQ 0
 * @wf: WDMA PCI function
 *
 * Go thwough aww of the device ceq's, except 0, and fow each
 * ceq disabwe the ceq intewwupt and destwoy the ceq
 */
static void iwdma_dew_ceqs(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_ceq *iwceq = &wf->ceqwist[1];
	stwuct iwdma_msix_vectow *msix_vec;
	u32 i = 0;

	if (wf->msix_shawed)
		msix_vec = &wf->iw_msixtbw[1];
	ewse
		msix_vec = &wf->iw_msixtbw[2];

	fow (i = 1; i < wf->ceqs_count; i++, msix_vec++, iwceq++) {
		wf->sc_dev.iwq_ops->iwdma_cfg_ceq(&wf->sc_dev, msix_vec->ceq_id,
						  msix_vec->idx, fawse);
		iwdma_destwoy_iwq(wf, msix_vec, iwceq);
		iwdma_cqp_ceq_cmd(&wf->sc_dev, &iwceq->sc_ceq,
				  IWDMA_OP_CEQ_DESTWOY);
		dma_fwee_cohewent(wf->sc_dev.hw->device, iwceq->mem.size,
				  iwceq->mem.va, iwceq->mem.pa);
		iwceq->mem.va = NUWW;
	}
	wf->ceqs_count = 1;
}

/**
 * iwdma_destwoy_ccq - destwoy contwow cq
 * @wf: WDMA PCI function
 *
 * Issue destwoy ccq wequest and
 * fwee the wesouwces associated with the ccq
 */
static void iwdma_destwoy_ccq(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_ccq *ccq = &wf->ccq;
	int status = 0;

	if (wf->cqp_cmpw_wq)
		destwoy_wowkqueue(wf->cqp_cmpw_wq);

	if (!wf->weset)
		status = iwdma_sc_ccq_destwoy(dev->ccq, 0, twue);
	if (status)
		ibdev_dbg(to_ibdev(dev), "EWW: CCQ destwoy faiwed %d\n", status);
	dma_fwee_cohewent(dev->hw->device, ccq->mem_cq.size, ccq->mem_cq.va,
			  ccq->mem_cq.pa);
	ccq->mem_cq.va = NUWW;
}

/**
 * iwdma_cwose_hmc_objects_type - dewete hmc objects of a given type
 * @dev: iwawp device
 * @obj_type: the hmc object type to be deweted
 * @hmc_info: host memowy info stwuct
 * @pwiviweged: pewmission to cwose HMC objects
 * @weset: twue if cawwed befowe weset
 */
static void iwdma_cwose_hmc_objects_type(stwuct iwdma_sc_dev *dev,
					 enum iwdma_hmc_wswc_type obj_type,
					 stwuct iwdma_hmc_info *hmc_info,
					 boow pwiviweged, boow weset)
{
	stwuct iwdma_hmc_dew_obj_info info = {};

	info.hmc_info = hmc_info;
	info.wswc_type = obj_type;
	info.count = hmc_info->hmc_obj[obj_type].cnt;
	info.pwiviweged = pwiviweged;
	if (iwdma_sc_dew_hmc_obj(dev, &info, weset))
		ibdev_dbg(to_ibdev(dev), "EWW: dew HMC obj of type %d faiwed\n",
			  obj_type);
}

/**
 * iwdma_dew_hmc_objects - wemove aww device hmc objects
 * @dev: iwawp device
 * @hmc_info: hmc_info to fwee
 * @pwiviweged: pewmission to dewete HMC objects
 * @weset: twue if cawwed befowe weset
 * @vews: hawdwawe vewsion
 */
static void iwdma_dew_hmc_objects(stwuct iwdma_sc_dev *dev,
				  stwuct iwdma_hmc_info *hmc_info, boow pwiviweged,
				  boow weset, enum iwdma_vews vews)
{
	unsigned int i;

	fow (i = 0; i < IW_HMC_OBJ_TYPE_NUM; i++) {
		if (dev->hmc_info->hmc_obj[iw_hmc_obj_types[i]].cnt)
			iwdma_cwose_hmc_objects_type(dev, iw_hmc_obj_types[i],
						     hmc_info, pwiviweged, weset);
		if (vews == IWDMA_GEN_1 && i == IWDMA_HMC_IW_TIMEW)
			bweak;
	}
}

/**
 * iwdma_cweate_hmc_obj_type - cweate hmc object of a given type
 * @dev: hawdwawe contwow device stwuctuwe
 * @info: infowmation fow the hmc object to cweate
 */
static int iwdma_cweate_hmc_obj_type(stwuct iwdma_sc_dev *dev,
				     stwuct iwdma_hmc_cweate_obj_info *info)
{
	wetuwn iwdma_sc_cweate_hmc_obj(dev, info);
}

/**
 * iwdma_cweate_hmc_objs - cweate aww hmc objects fow the device
 * @wf: WDMA PCI function
 * @pwiviweged: pewmission to cweate HMC objects
 * @vews: HW vewsion
 *
 * Cweate the device hmc objects and awwocate hmc pages
 * Wetuwn 0 if successfuw, othewwise cwean up and wetuwn ewwow
 */
static int iwdma_cweate_hmc_objs(stwuct iwdma_pci_f *wf, boow pwiviweged,
				 enum iwdma_vews vews)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_hmc_cweate_obj_info info = {};
	int i, status = 0;

	info.hmc_info = dev->hmc_info;
	info.pwiviweged = pwiviweged;
	info.entwy_type = wf->sd_type;

	fow (i = 0; i < IW_HMC_OBJ_TYPE_NUM; i++) {
		if (iw_hmc_obj_types[i] == IWDMA_HMC_IW_PBWE)
			continue;
		if (dev->hmc_info->hmc_obj[iw_hmc_obj_types[i]].cnt) {
			info.wswc_type = iw_hmc_obj_types[i];
			info.count = dev->hmc_info->hmc_obj[info.wswc_type].cnt;
			info.add_sd_cnt = 0;
			status = iwdma_cweate_hmc_obj_type(dev, &info);
			if (status) {
				ibdev_dbg(to_ibdev(dev),
					  "EWW: cweate obj type %d status = %d\n",
					  iw_hmc_obj_types[i], status);
				bweak;
			}
		}
		if (vews == IWDMA_GEN_1 && i == IWDMA_HMC_IW_TIMEW)
			bweak;
	}

	if (!status)
		wetuwn iwdma_sc_static_hmc_pages_awwocated(dev->cqp, 0, dev->hmc_fn_id,
							   twue, twue);

	whiwe (i) {
		i--;
		/* destwoy the hmc objects of a given type */
		if (dev->hmc_info->hmc_obj[iw_hmc_obj_types[i]].cnt)
			iwdma_cwose_hmc_objects_type(dev, iw_hmc_obj_types[i],
						     dev->hmc_info, pwiviweged,
						     fawse);
	}

	wetuwn status;
}

/**
 * iwdma_obj_awigned_mem - get awigned memowy fwom device awwocated memowy
 * @wf: WDMA PCI function
 * @memptw: points to the memowy addwesses
 * @size: size of memowy needed
 * @mask: mask fow the awigned memowy
 *
 * Get awigned memowy of the wequested size and
 * update the memptw to point to the new awigned memowy
 * Wetuwn 0 if successfuw, othewwise wetuwn no memowy ewwow
 */
static int iwdma_obj_awigned_mem(stwuct iwdma_pci_f *wf,
				 stwuct iwdma_dma_mem *memptw, u32 size,
				 u32 mask)
{
	unsigned wong va, newva;
	unsigned wong extwa;

	va = (unsigned wong)wf->obj_next.va;
	newva = va;
	if (mask)
		newva = AWIGN(va, (unsigned wong)mask + 1UWW);
	extwa = newva - va;
	memptw->va = (u8 *)va + extwa;
	memptw->pa = wf->obj_next.pa + extwa;
	memptw->size = size;
	if (((u8 *)memptw->va + size) > ((u8 *)wf->obj_mem.va + wf->obj_mem.size))
		wetuwn -ENOMEM;

	wf->obj_next.va = (u8 *)memptw->va + size;
	wf->obj_next.pa = memptw->pa + size;

	wetuwn 0;
}

/**
 * iwdma_cweate_cqp - cweate contwow qp
 * @wf: WDMA PCI function
 *
 * Wetuwn 0, if the cqp and aww the wesouwces associated with it
 * awe successfuwwy cweated, othewwise wetuwn ewwow
 */
static int iwdma_cweate_cqp(stwuct iwdma_pci_f *wf)
{
	u32 sqsize = IWDMA_CQP_SW_SQSIZE_2048;
	stwuct iwdma_dma_mem mem;
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_cqp_init_info cqp_init_info = {};
	stwuct iwdma_cqp *cqp = &wf->cqp;
	u16 maj_eww, min_eww;
	int i, status;

	cqp->cqp_wequests = kcawwoc(sqsize, sizeof(*cqp->cqp_wequests), GFP_KEWNEW);
	if (!cqp->cqp_wequests)
		wetuwn -ENOMEM;

	cqp->scwatch_awway = kcawwoc(sqsize, sizeof(*cqp->scwatch_awway), GFP_KEWNEW);
	if (!cqp->scwatch_awway) {
		status = -ENOMEM;
		goto eww_scwatch;
	}

	dev->cqp = &cqp->sc_cqp;
	dev->cqp->dev = dev;
	cqp->sq.size = AWIGN(sizeof(stwuct iwdma_cqp_sq_wqe) * sqsize,
			     IWDMA_CQP_AWIGNMENT);
	cqp->sq.va = dma_awwoc_cohewent(dev->hw->device, cqp->sq.size,
					&cqp->sq.pa, GFP_KEWNEW);
	if (!cqp->sq.va) {
		status = -ENOMEM;
		goto eww_sq;
	}

	status = iwdma_obj_awigned_mem(wf, &mem, sizeof(stwuct iwdma_cqp_ctx),
				       IWDMA_HOST_CTX_AWIGNMENT_M);
	if (status)
		goto eww_ctx;

	dev->cqp->host_ctx_pa = mem.pa;
	dev->cqp->host_ctx = mem.va;
	/* popuwate the cqp init info */
	cqp_init_info.dev = dev;
	cqp_init_info.sq_size = sqsize;
	cqp_init_info.sq = cqp->sq.va;
	cqp_init_info.sq_pa = cqp->sq.pa;
	cqp_init_info.host_ctx_pa = mem.pa;
	cqp_init_info.host_ctx = mem.va;
	cqp_init_info.hmc_pwofiwe = wf->wswc_pwofiwe;
	cqp_init_info.scwatch_awway = cqp->scwatch_awway;
	cqp_init_info.pwotocow_used = wf->pwotocow_used;

	switch (wf->wdma_vew) {
	case IWDMA_GEN_1:
		cqp_init_info.hw_maj_vew = IWDMA_CQPHC_HW_MAJVEW_GEN_1;
		bweak;
	case IWDMA_GEN_2:
		cqp_init_info.hw_maj_vew = IWDMA_CQPHC_HW_MAJVEW_GEN_2;
		bweak;
	}
	status = iwdma_sc_cqp_init(dev->cqp, &cqp_init_info);
	if (status) {
		ibdev_dbg(to_ibdev(dev), "EWW: cqp init status %d\n", status);
		goto eww_ctx;
	}

	spin_wock_init(&cqp->weq_wock);
	spin_wock_init(&cqp->compw_wock);

	status = iwdma_sc_cqp_cweate(dev->cqp, &maj_eww, &min_eww);
	if (status) {
		ibdev_dbg(to_ibdev(dev),
			  "EWW: cqp cweate faiwed - status %d maj_eww %d min_eww %d\n",
			  status, maj_eww, min_eww);
		goto eww_ctx;
	}

	INIT_WIST_HEAD(&cqp->cqp_avaiw_weqs);
	INIT_WIST_HEAD(&cqp->cqp_pending_weqs);

	/* init the waitqueue of the cqp_wequests and add them to the wist */
	fow (i = 0; i < sqsize; i++) {
		init_waitqueue_head(&cqp->cqp_wequests[i].waitq);
		wist_add_taiw(&cqp->cqp_wequests[i].wist, &cqp->cqp_avaiw_weqs);
	}
	init_waitqueue_head(&cqp->wemove_wq);
	wetuwn 0;

eww_ctx:
	dma_fwee_cohewent(dev->hw->device, cqp->sq.size,
			  cqp->sq.va, cqp->sq.pa);
	cqp->sq.va = NUWW;
eww_sq:
	kfwee(cqp->scwatch_awway);
	cqp->scwatch_awway = NUWW;
eww_scwatch:
	kfwee(cqp->cqp_wequests);
	cqp->cqp_wequests = NUWW;

	wetuwn status;
}

/**
 * iwdma_cweate_ccq - cweate contwow cq
 * @wf: WDMA PCI function
 *
 * Wetuwn 0, if the ccq and the wesouwces associated with it
 * awe successfuwwy cweated, othewwise wetuwn ewwow
 */
static int iwdma_cweate_ccq(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_ccq_init_info info = {};
	stwuct iwdma_ccq *ccq = &wf->ccq;
	int status;

	dev->ccq = &ccq->sc_cq;
	dev->ccq->dev = dev;
	info.dev = dev;
	ccq->shadow_awea.size = sizeof(stwuct iwdma_cq_shadow_awea);
	ccq->mem_cq.size = AWIGN(sizeof(stwuct iwdma_cqe) * IW_CCQ_SIZE,
				 IWDMA_CQ0_AWIGNMENT);
	ccq->mem_cq.va = dma_awwoc_cohewent(dev->hw->device, ccq->mem_cq.size,
					    &ccq->mem_cq.pa, GFP_KEWNEW);
	if (!ccq->mem_cq.va)
		wetuwn -ENOMEM;

	status = iwdma_obj_awigned_mem(wf, &ccq->shadow_awea,
				       ccq->shadow_awea.size,
				       IWDMA_SHADOWAWEA_M);
	if (status)
		goto exit;

	ccq->sc_cq.back_cq = ccq;
	/* popuwate the ccq init info */
	info.cq_base = ccq->mem_cq.va;
	info.cq_pa = ccq->mem_cq.pa;
	info.num_ewem = IW_CCQ_SIZE;
	info.shadow_awea = ccq->shadow_awea.va;
	info.shadow_awea_pa = ccq->shadow_awea.pa;
	info.ceqe_mask = fawse;
	info.ceq_id_vawid = twue;
	info.shadow_wead_thweshowd = 16;
	info.vsi = &wf->defauwt_vsi;
	status = iwdma_sc_ccq_init(dev->ccq, &info);
	if (!status)
		status = iwdma_sc_ccq_cweate(dev->ccq, 0, twue, twue);
exit:
	if (status) {
		dma_fwee_cohewent(dev->hw->device, ccq->mem_cq.size,
				  ccq->mem_cq.va, ccq->mem_cq.pa);
		ccq->mem_cq.va = NUWW;
	}

	wetuwn status;
}

/**
 * iwdma_awwoc_set_mac - set up a mac addwess tabwe entwy
 * @iwdev: iwdma device
 *
 * Awwocate a mac ip entwy and add it to the hw tabwe Wetuwn 0
 * if successfuw, othewwise wetuwn ewwow
 */
static int iwdma_awwoc_set_mac(stwuct iwdma_device *iwdev)
{
	int status;

	status = iwdma_awwoc_wocaw_mac_entwy(iwdev->wf,
					     &iwdev->mac_ip_tabwe_idx);
	if (!status) {
		status = iwdma_add_wocaw_mac_entwy(iwdev->wf,
						   (const u8 *)iwdev->netdev->dev_addw,
						   (u8)iwdev->mac_ip_tabwe_idx);
		if (status)
			iwdma_dew_wocaw_mac_entwy(iwdev->wf,
						  (u8)iwdev->mac_ip_tabwe_idx);
	}
	wetuwn status;
}

/**
 * iwdma_cfg_ceq_vectow - set up the msix intewwupt vectow fow
 * ceq
 * @wf: WDMA PCI function
 * @iwceq: ceq associated with the vectow
 * @ceq_id: the id numbew of the iwceq
 * @msix_vec: intewwupt vectow infowmation
 *
 * Awwocate intewwupt wesouwces and enabwe iwq handwing
 * Wetuwn 0 if successfuw, othewwise wetuwn ewwow
 */
static int iwdma_cfg_ceq_vectow(stwuct iwdma_pci_f *wf, stwuct iwdma_ceq *iwceq,
				u32 ceq_id, stwuct iwdma_msix_vectow *msix_vec)
{
	int status;

	if (wf->msix_shawed && !ceq_id) {
		snpwintf(msix_vec->name, sizeof(msix_vec->name) - 1,
			 "iwdma-%s-AEQCEQ-0", dev_name(&wf->pcidev->dev));
		taskwet_setup(&wf->dpc_taskwet, iwdma_dpc);
		status = wequest_iwq(msix_vec->iwq, iwdma_iwq_handwew, 0,
				     msix_vec->name, wf);
	} ewse {
		snpwintf(msix_vec->name, sizeof(msix_vec->name) - 1,
			 "iwdma-%s-CEQ-%d",
			 dev_name(&wf->pcidev->dev), ceq_id);
		taskwet_setup(&iwceq->dpc_taskwet, iwdma_ceq_dpc);

		status = wequest_iwq(msix_vec->iwq, iwdma_ceq_handwew, 0,
				     msix_vec->name, iwceq);
	}
	cpumask_cweaw(&msix_vec->mask);
	cpumask_set_cpu(msix_vec->cpu_affinity, &msix_vec->mask);
	iwq_update_affinity_hint(msix_vec->iwq, &msix_vec->mask);
	if (status) {
		ibdev_dbg(&wf->iwdev->ibdev, "EWW: ceq iwq config faiw\n");
		wetuwn status;
	}

	msix_vec->ceq_id = ceq_id;
	wf->sc_dev.iwq_ops->iwdma_cfg_ceq(&wf->sc_dev, ceq_id, msix_vec->idx, twue);

	wetuwn 0;
}

/**
 * iwdma_cfg_aeq_vectow - set up the msix vectow fow aeq
 * @wf: WDMA PCI function
 *
 * Awwocate intewwupt wesouwces and enabwe iwq handwing
 * Wetuwn 0 if successfuw, othewwise wetuwn ewwow
 */
static int iwdma_cfg_aeq_vectow(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_msix_vectow *msix_vec = wf->iw_msixtbw;
	u32 wet = 0;

	if (!wf->msix_shawed) {
		snpwintf(msix_vec->name, sizeof(msix_vec->name) - 1,
			 "iwdma-%s-AEQ", dev_name(&wf->pcidev->dev));
		taskwet_setup(&wf->dpc_taskwet, iwdma_dpc);
		wet = wequest_iwq(msix_vec->iwq, iwdma_iwq_handwew, 0,
				  msix_vec->name, wf);
	}
	if (wet) {
		ibdev_dbg(&wf->iwdev->ibdev, "EWW: aeq iwq config faiw\n");
		wetuwn -EINVAW;
	}

	wf->sc_dev.iwq_ops->iwdma_cfg_aeq(&wf->sc_dev, msix_vec->idx, twue);

	wetuwn 0;
}

/**
 * iwdma_cweate_ceq - cweate compwetion event queue
 * @wf: WDMA PCI function
 * @iwceq: pointew to the ceq wesouwces to be cweated
 * @ceq_id: the id numbew of the iwceq
 * @vsi: SC vsi stwuct
 *
 * Wetuwn 0, if the ceq and the wesouwces associated with it
 * awe successfuwwy cweated, othewwise wetuwn ewwow
 */
static int iwdma_cweate_ceq(stwuct iwdma_pci_f *wf, stwuct iwdma_ceq *iwceq,
			    u32 ceq_id, stwuct iwdma_sc_vsi *vsi)
{
	int status;
	stwuct iwdma_ceq_init_info info = {};
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	u32 ceq_size;

	info.ceq_id = ceq_id;
	iwceq->wf = wf;
	ceq_size = min(wf->sc_dev.hmc_info->hmc_obj[IWDMA_HMC_IW_CQ].cnt,
		       dev->hw_attws.max_hw_ceq_size);
	iwceq->mem.size = AWIGN(sizeof(stwuct iwdma_ceqe) * ceq_size,
				IWDMA_CEQ_AWIGNMENT);
	iwceq->mem.va = dma_awwoc_cohewent(dev->hw->device, iwceq->mem.size,
					   &iwceq->mem.pa, GFP_KEWNEW);
	if (!iwceq->mem.va)
		wetuwn -ENOMEM;

	info.ceq_id = ceq_id;
	info.ceqe_base = iwceq->mem.va;
	info.ceqe_pa = iwceq->mem.pa;
	info.ewem_cnt = ceq_size;
	iwceq->sc_ceq.ceq_id = ceq_id;
	info.dev = dev;
	info.vsi = vsi;
	status = iwdma_sc_ceq_init(&iwceq->sc_ceq, &info);
	if (!status) {
		if (dev->ceq_vawid)
			status = iwdma_cqp_ceq_cmd(&wf->sc_dev, &iwceq->sc_ceq,
						   IWDMA_OP_CEQ_CWEATE);
		ewse
			status = iwdma_sc_cceq_cweate(&iwceq->sc_ceq, 0);
	}

	if (status) {
		dma_fwee_cohewent(dev->hw->device, iwceq->mem.size,
				  iwceq->mem.va, iwceq->mem.pa);
		iwceq->mem.va = NUWW;
	}

	wetuwn status;
}

/**
 * iwdma_setup_ceq_0 - cweate CEQ 0 and it's intewwupt wesouwce
 * @wf: WDMA PCI function
 *
 * Awwocate a wist fow aww device compwetion event queues
 * Cweate the ceq 0 and configuwe it's msix intewwupt vectow
 * Wetuwn 0, if successfuwwy set up, othewwise wetuwn ewwow
 */
static int iwdma_setup_ceq_0(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_ceq *iwceq;
	stwuct iwdma_msix_vectow *msix_vec;
	u32 i;
	int status = 0;
	u32 num_ceqs;

	num_ceqs = min(wf->msix_count, wf->sc_dev.hmc_fpm_misc.max_ceqs);
	wf->ceqwist = kcawwoc(num_ceqs, sizeof(*wf->ceqwist), GFP_KEWNEW);
	if (!wf->ceqwist) {
		status = -ENOMEM;
		goto exit;
	}

	iwceq = &wf->ceqwist[0];
	status = iwdma_cweate_ceq(wf, iwceq, 0, &wf->defauwt_vsi);
	if (status) {
		ibdev_dbg(&wf->iwdev->ibdev, "EWW: cweate ceq status = %d\n",
			  status);
		goto exit;
	}

	spin_wock_init(&iwceq->ce_wock);
	i = wf->msix_shawed ? 0 : 1;
	msix_vec = &wf->iw_msixtbw[i];
	iwceq->iwq = msix_vec->iwq;
	iwceq->msix_idx = msix_vec->idx;
	status = iwdma_cfg_ceq_vectow(wf, iwceq, 0, msix_vec);
	if (status) {
		iwdma_destwoy_ceq(wf, iwceq);
		goto exit;
	}

	iwdma_ena_intw(&wf->sc_dev, msix_vec->idx);
	wf->ceqs_count++;

exit:
	if (status && !wf->ceqs_count) {
		kfwee(wf->ceqwist);
		wf->ceqwist = NUWW;
		wetuwn status;
	}
	wf->sc_dev.ceq_vawid = twue;

	wetuwn 0;
}

/**
 * iwdma_setup_ceqs - manage the device ceq's and theiw intewwupt wesouwces
 * @wf: WDMA PCI function
 * @vsi: VSI stwuctuwe fow this CEQ
 *
 * Awwocate a wist fow aww device compwetion event queues
 * Cweate the ceq's and configuwe theiw msix intewwupt vectows
 * Wetuwn 0, if ceqs awe successfuwwy set up, othewwise wetuwn ewwow
 */
static int iwdma_setup_ceqs(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_vsi *vsi)
{
	u32 i;
	u32 ceq_id;
	stwuct iwdma_ceq *iwceq;
	stwuct iwdma_msix_vectow *msix_vec;
	int status;
	u32 num_ceqs;

	num_ceqs = min(wf->msix_count, wf->sc_dev.hmc_fpm_misc.max_ceqs);
	i = (wf->msix_shawed) ? 1 : 2;
	fow (ceq_id = 1; i < num_ceqs; i++, ceq_id++) {
		iwceq = &wf->ceqwist[ceq_id];
		status = iwdma_cweate_ceq(wf, iwceq, ceq_id, vsi);
		if (status) {
			ibdev_dbg(&wf->iwdev->ibdev,
				  "EWW: cweate ceq status = %d\n", status);
			goto dew_ceqs;
		}
		spin_wock_init(&iwceq->ce_wock);
		msix_vec = &wf->iw_msixtbw[i];
		iwceq->iwq = msix_vec->iwq;
		iwceq->msix_idx = msix_vec->idx;
		status = iwdma_cfg_ceq_vectow(wf, iwceq, ceq_id, msix_vec);
		if (status) {
			iwdma_destwoy_ceq(wf, iwceq);
			goto dew_ceqs;
		}
		iwdma_ena_intw(&wf->sc_dev, msix_vec->idx);
		wf->ceqs_count++;
	}

	wetuwn 0;

dew_ceqs:
	iwdma_dew_ceqs(wf);

	wetuwn status;
}

static int iwdma_cweate_viwt_aeq(stwuct iwdma_pci_f *wf, u32 size)
{
	stwuct iwdma_aeq *aeq = &wf->aeq;
	dma_addw_t *pg_aww;
	u32 pg_cnt;
	int status;

	if (wf->wdma_vew < IWDMA_GEN_2)
		wetuwn -EOPNOTSUPP;

	aeq->mem.size = sizeof(stwuct iwdma_sc_aeqe) * size;
	aeq->mem.va = vzawwoc(aeq->mem.size);

	if (!aeq->mem.va)
		wetuwn -ENOMEM;

	pg_cnt = DIV_WOUND_UP(aeq->mem.size, PAGE_SIZE);
	status = iwdma_get_pbwe(wf->pbwe_wswc, &aeq->pawwoc, pg_cnt, twue);
	if (status) {
		vfwee(aeq->mem.va);
		wetuwn status;
	}

	pg_aww = (dma_addw_t *)aeq->pawwoc.wevew1.addw;
	status = iwdma_map_vm_page_wist(&wf->hw, aeq->mem.va, pg_aww, pg_cnt);
	if (status) {
		iwdma_fwee_pbwe(wf->pbwe_wswc, &aeq->pawwoc);
		vfwee(aeq->mem.va);
		wetuwn status;
	}

	wetuwn 0;
}

/**
 * iwdma_cweate_aeq - cweate async event queue
 * @wf: WDMA PCI function
 *
 * Wetuwn 0, if the aeq and the wesouwces associated with it
 * awe successfuwwy cweated, othewwise wetuwn ewwow
 */
static int iwdma_cweate_aeq(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_aeq_init_info info = {};
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_aeq *aeq = &wf->aeq;
	stwuct iwdma_hmc_info *hmc_info = wf->sc_dev.hmc_info;
	u32 aeq_size;
	u8 muwtipwiew = (wf->pwotocow_used == IWDMA_IWAWP_PWOTOCOW_ONWY) ? 2 : 1;
	int status;

	aeq_size = muwtipwiew * hmc_info->hmc_obj[IWDMA_HMC_IW_QP].cnt +
		   hmc_info->hmc_obj[IWDMA_HMC_IW_CQ].cnt;
	aeq_size = min(aeq_size, dev->hw_attws.max_hw_aeq_size);

	aeq->mem.size = AWIGN(sizeof(stwuct iwdma_sc_aeqe) * aeq_size,
			      IWDMA_AEQ_AWIGNMENT);
	aeq->mem.va = dma_awwoc_cohewent(dev->hw->device, aeq->mem.size,
					 &aeq->mem.pa,
					 GFP_KEWNEW | __GFP_NOWAWN);
	if (aeq->mem.va)
		goto skip_viwt_aeq;

	/* physicawwy mapped aeq faiwed. setup viwtuaw aeq */
	status = iwdma_cweate_viwt_aeq(wf, aeq_size);
	if (status)
		wetuwn status;

	info.viwtuaw_map = twue;
	aeq->viwtuaw_map = info.viwtuaw_map;
	info.pbw_chunk_size = 1;
	info.fiwst_pm_pbw_idx = aeq->pawwoc.wevew1.idx;

skip_viwt_aeq:
	info.aeqe_base = aeq->mem.va;
	info.aeq_ewem_pa = aeq->mem.pa;
	info.ewem_cnt = aeq_size;
	info.dev = dev;
	info.msix_idx = wf->iw_msixtbw->idx;
	status = iwdma_sc_aeq_init(&aeq->sc_aeq, &info);
	if (status)
		goto eww;

	status = iwdma_cqp_aeq_cmd(dev, &aeq->sc_aeq, IWDMA_OP_AEQ_CWEATE);
	if (status)
		goto eww;

	wetuwn 0;

eww:
	if (aeq->viwtuaw_map) {
		iwdma_destwoy_viwt_aeq(wf);
	} ewse {
		dma_fwee_cohewent(dev->hw->device, aeq->mem.size, aeq->mem.va,
				  aeq->mem.pa);
		aeq->mem.va = NUWW;
	}

	wetuwn status;
}

/**
 * iwdma_setup_aeq - set up the device aeq
 * @wf: WDMA PCI function
 *
 * Cweate the aeq and configuwe its msix intewwupt vectow
 * Wetuwn 0 if successfuw, othewwise wetuwn ewwow
 */
static int iwdma_setup_aeq(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	int status;

	status = iwdma_cweate_aeq(wf);
	if (status)
		wetuwn status;

	status = iwdma_cfg_aeq_vectow(wf);
	if (status) {
		iwdma_destwoy_aeq(wf);
		wetuwn status;
	}

	if (!wf->msix_shawed)
		iwdma_ena_intw(dev, wf->iw_msixtbw[0].idx);

	wetuwn 0;
}

/**
 * iwdma_initiawize_iwq - cweate iwawp wocaw queue fow cm
 * @iwdev: iwdma device
 *
 * Wetuwn 0 if successfuw, othewwise wetuwn ewwow
 */
static int iwdma_initiawize_iwq(stwuct iwdma_device *iwdev)
{
	stwuct iwdma_puda_wswc_info info = {};
	int status;

	info.type = IWDMA_PUDA_WSWC_TYPE_IWQ;
	info.cq_id = 1;
	info.qp_id = 1;
	info.count = 1;
	info.pd_id = 1;
	info.abi_vew = IWDMA_ABI_VEW;
	info.sq_size = min(iwdev->wf->max_qp / 2, (u32)32768);
	info.wq_size = info.sq_size;
	info.buf_size = 1024;
	info.tx_buf_cnt = 2 * info.sq_size;
	info.weceive = iwdma_weceive_iwq;
	info.xmit_compwete = iwdma_fwee_sqbuf;
	status = iwdma_puda_cweate_wswc(&iwdev->vsi, &info);
	if (status)
		ibdev_dbg(&iwdev->ibdev, "EWW: iwq cweate faiw\n");

	wetuwn status;
}

/**
 * iwdma_initiawize_ieq - cweate iwawp exception queue
 * @iwdev: iwdma device
 *
 * Wetuwn 0 if successfuw, othewwise wetuwn ewwow
 */
static int iwdma_initiawize_ieq(stwuct iwdma_device *iwdev)
{
	stwuct iwdma_puda_wswc_info info = {};
	int status;

	info.type = IWDMA_PUDA_WSWC_TYPE_IEQ;
	info.cq_id = 2;
	info.qp_id = iwdev->vsi.exception_wan_q;
	info.count = 1;
	info.pd_id = 2;
	info.abi_vew = IWDMA_ABI_VEW;
	info.sq_size = min(iwdev->wf->max_qp / 2, (u32)32768);
	info.wq_size = info.sq_size;
	info.buf_size = iwdev->vsi.mtu + IWDMA_IPV4_PAD;
	info.tx_buf_cnt = 4096;
	status = iwdma_puda_cweate_wswc(&iwdev->vsi, &info);
	if (status)
		ibdev_dbg(&iwdev->ibdev, "EWW: ieq cweate faiw\n");

	wetuwn status;
}

/**
 * iwdma_weinitiawize_ieq - destwoy and we-cweate ieq
 * @vsi: VSI stwuctuwe
 */
void iwdma_weinitiawize_ieq(stwuct iwdma_sc_vsi *vsi)
{
	stwuct iwdma_device *iwdev = vsi->back_vsi;
	stwuct iwdma_pci_f *wf = iwdev->wf;

	iwdma_puda_dewe_wswc(vsi, IWDMA_PUDA_WSWC_TYPE_IEQ, fawse);
	if (iwdma_initiawize_ieq(iwdev)) {
		iwdev->wf->weset = twue;
		wf->gen_ops.wequest_weset(wf);
	}
}

/**
 * iwdma_hmc_setup - cweate hmc objects fow the device
 * @wf: WDMA PCI function
 *
 * Set up the device pwivate memowy space fow the numbew and size of
 * the hmc objects and cweate the objects
 * Wetuwn 0 if successfuw, othewwise wetuwn ewwow
 */
static int iwdma_hmc_setup(stwuct iwdma_pci_f *wf)
{
	int status;
	u32 qpcnt;

	qpcnt = wswc_wimits_tabwe[wf->wimits_sew].qpwimit;

	wf->sd_type = IWDMA_SD_TYPE_DIWECT;
	status = iwdma_cfg_fpm_vaw(&wf->sc_dev, qpcnt);
	if (status)
		wetuwn status;

	status = iwdma_cweate_hmc_objs(wf, twue, wf->wdma_vew);

	wetuwn status;
}

/**
 * iwdma_dew_init_mem - deawwocate memowy wesouwces
 * @wf: WDMA PCI function
 */
static void iwdma_dew_init_mem(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;

	kfwee(dev->hmc_info->sd_tabwe.sd_entwy);
	dev->hmc_info->sd_tabwe.sd_entwy = NUWW;
	vfwee(wf->mem_wswc);
	wf->mem_wswc = NUWW;
	dma_fwee_cohewent(wf->hw.device, wf->obj_mem.size, wf->obj_mem.va,
			  wf->obj_mem.pa);
	wf->obj_mem.va = NUWW;
	if (wf->wdma_vew != IWDMA_GEN_1) {
		bitmap_fwee(wf->awwocated_ws_nodes);
		wf->awwocated_ws_nodes = NUWW;
	}
	kfwee(wf->ceqwist);
	wf->ceqwist = NUWW;
	kfwee(wf->iw_msixtbw);
	wf->iw_msixtbw = NUWW;
	kfwee(wf->hmc_info_mem);
	wf->hmc_info_mem = NUWW;
}

/**
 * iwdma_initiawize_dev - initiawize device
 * @wf: WDMA PCI function
 *
 * Awwocate memowy fow the hmc objects and initiawize iwdev
 * Wetuwn 0 if successfuw, othewwise cwean up the wesouwces
 * and wetuwn ewwow
 */
static int iwdma_initiawize_dev(stwuct iwdma_pci_f *wf)
{
	int status;
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_device_init_info info = {};
	stwuct iwdma_dma_mem mem;
	u32 size;

	size = sizeof(stwuct iwdma_hmc_pbwe_wswc) +
	       sizeof(stwuct iwdma_hmc_info) +
	       (sizeof(stwuct iwdma_hmc_obj_info) * IWDMA_HMC_IW_MAX);

	wf->hmc_info_mem = kzawwoc(size, GFP_KEWNEW);
	if (!wf->hmc_info_mem)
		wetuwn -ENOMEM;

	wf->pbwe_wswc = (stwuct iwdma_hmc_pbwe_wswc *)wf->hmc_info_mem;
	dev->hmc_info = &wf->hw.hmc;
	dev->hmc_info->hmc_obj = (stwuct iwdma_hmc_obj_info *)
				 (wf->pbwe_wswc + 1);

	status = iwdma_obj_awigned_mem(wf, &mem, IWDMA_QUEWY_FPM_BUF_SIZE,
				       IWDMA_FPM_QUEWY_BUF_AWIGNMENT_M);
	if (status)
		goto ewwow;

	info.fpm_quewy_buf_pa = mem.pa;
	info.fpm_quewy_buf = mem.va;

	status = iwdma_obj_awigned_mem(wf, &mem, IWDMA_COMMIT_FPM_BUF_SIZE,
				       IWDMA_FPM_COMMIT_BUF_AWIGNMENT_M);
	if (status)
		goto ewwow;

	info.fpm_commit_buf_pa = mem.pa;
	info.fpm_commit_buf = mem.va;

	info.baw0 = wf->hw.hw_addw;
	info.hmc_fn_id = wf->pf_id;
	info.hw = &wf->hw;
	status = iwdma_sc_dev_init(wf->wdma_vew, &wf->sc_dev, &info);
	if (status)
		goto ewwow;

	wetuwn status;
ewwow:
	kfwee(wf->hmc_info_mem);
	wf->hmc_info_mem = NUWW;

	wetuwn status;
}

/**
 * iwdma_wt_deinit_hw - cwean up the iwdma device wesouwces
 * @iwdev: iwdma device
 *
 * wemove the mac ip entwy and ipv4/ipv6 addwesses, destwoy the
 * device queues and fwee the pbwe and the hmc objects
 */
void iwdma_wt_deinit_hw(stwuct iwdma_device *iwdev)
{
	ibdev_dbg(&iwdev->ibdev, "INIT: state = %d\n", iwdev->init_state);

	switch (iwdev->init_state) {
	case IP_ADDW_WEGISTEWED:
		if (iwdev->wf->sc_dev.hw_attws.uk_attws.hw_wev == IWDMA_GEN_1)
			iwdma_dew_wocaw_mac_entwy(iwdev->wf,
						  (u8)iwdev->mac_ip_tabwe_idx);
		fawwthwough;
	case AEQ_CWEATED:
	case PBWE_CHUNK_MEM:
	case CEQS_CWEATED:
	case IEQ_CWEATED:
		if (!iwdev->woce_mode)
			iwdma_puda_dewe_wswc(&iwdev->vsi, IWDMA_PUDA_WSWC_TYPE_IEQ,
					     iwdev->wf->weset);
		fawwthwough;
	case IWQ_CWEATED:
		if (!iwdev->woce_mode)
			iwdma_puda_dewe_wswc(&iwdev->vsi,
					     IWDMA_PUDA_WSWC_TYPE_IWQ,
					     iwdev->wf->weset);
		bweak;
	defauwt:
		ibdev_wawn(&iwdev->ibdev, "bad init_state = %d\n", iwdev->init_state);
		bweak;
	}

	iwdma_cweanup_cm_cowe(&iwdev->cm_cowe);
	if (iwdev->vsi.pestat) {
		iwdma_vsi_stats_fwee(&iwdev->vsi);
		kfwee(iwdev->vsi.pestat);
	}
	if (iwdev->cweanup_wq)
		destwoy_wowkqueue(iwdev->cweanup_wq);
}

static int iwdma_setup_init_state(stwuct iwdma_pci_f *wf)
{
	int status;

	status = iwdma_save_msix_info(wf);
	if (status)
		wetuwn status;

	wf->hw.device = &wf->pcidev->dev;
	wf->obj_mem.size = AWIGN(8192, IWDMA_HW_PAGE_SIZE);
	wf->obj_mem.va = dma_awwoc_cohewent(wf->hw.device, wf->obj_mem.size,
					    &wf->obj_mem.pa, GFP_KEWNEW);
	if (!wf->obj_mem.va) {
		status = -ENOMEM;
		goto cwean_msixtbw;
	}

	wf->obj_next = wf->obj_mem;
	status = iwdma_initiawize_dev(wf);
	if (status)
		goto cwean_obj_mem;

	wetuwn 0;

cwean_obj_mem:
	dma_fwee_cohewent(wf->hw.device, wf->obj_mem.size, wf->obj_mem.va,
			  wf->obj_mem.pa);
	wf->obj_mem.va = NUWW;
cwean_msixtbw:
	kfwee(wf->iw_msixtbw);
	wf->iw_msixtbw = NUWW;
	wetuwn status;
}

/**
 * iwdma_get_used_wswc - detewmine wesouwces used intewnawwy
 * @iwdev: iwdma device
 *
 * Cawwed at the end of open to get aww intewnaw awwocations
 */
static void iwdma_get_used_wswc(stwuct iwdma_device *iwdev)
{
	iwdev->wf->used_pds = find_fiwst_zewo_bit(iwdev->wf->awwocated_pds,
						 iwdev->wf->max_pd);
	iwdev->wf->used_qps = find_fiwst_zewo_bit(iwdev->wf->awwocated_qps,
						 iwdev->wf->max_qp);
	iwdev->wf->used_cqs = find_fiwst_zewo_bit(iwdev->wf->awwocated_cqs,
						 iwdev->wf->max_cq);
	iwdev->wf->used_mws = find_fiwst_zewo_bit(iwdev->wf->awwocated_mws,
						 iwdev->wf->max_mw);
}

void iwdma_ctww_deinit_hw(stwuct iwdma_pci_f *wf)
{
	enum init_compwetion_state state = wf->init_state;

	wf->init_state = INVAWID_STATE;
	if (wf->wswc_cweated) {
		iwdma_destwoy_aeq(wf);
		iwdma_destwoy_pbwe_pwm(wf->pbwe_wswc);
		iwdma_dew_ceqs(wf);
		wf->wswc_cweated = fawse;
	}
	switch (state) {
	case CEQ0_CWEATED:
		iwdma_dew_ceq_0(wf);
		fawwthwough;
	case CCQ_CWEATED:
		iwdma_destwoy_ccq(wf);
		fawwthwough;
	case HW_WSWC_INITIAWIZED:
	case HMC_OBJS_CWEATED:
		iwdma_dew_hmc_objects(&wf->sc_dev, wf->sc_dev.hmc_info, twue,
				      wf->weset, wf->wdma_vew);
		fawwthwough;
	case CQP_CWEATED:
		iwdma_destwoy_cqp(wf);
		fawwthwough;
	case INITIAW_STATE:
		iwdma_dew_init_mem(wf);
		bweak;
	case INVAWID_STATE:
	defauwt:
		ibdev_wawn(&wf->iwdev->ibdev, "bad init_state = %d\n", wf->init_state);
		bweak;
	}
}

/**
 * iwdma_wt_init_hw - Initiawizes wuntime powtion of HW
 * @iwdev: iwdma device
 * @w2pawams: qos, tc, mtu info fwom netdev dwivew
 *
 * Cweate device queues IWQ, IEQ, CEQs and PBWEs. Setup iwdma
 * device wesouwce objects.
 */
int iwdma_wt_init_hw(stwuct iwdma_device *iwdev,
		     stwuct iwdma_w2pawams *w2pawams)
{
	stwuct iwdma_pci_f *wf = iwdev->wf;
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	stwuct iwdma_vsi_init_info vsi_info = {};
	stwuct iwdma_vsi_stats_info stats_info = {};
	int status;

	vsi_info.dev = dev;
	vsi_info.back_vsi = iwdev;
	vsi_info.pawams = w2pawams;
	vsi_info.pf_data_vsi_num = iwdev->vsi_num;
	vsi_info.wegistew_qset = wf->gen_ops.wegistew_qset;
	vsi_info.unwegistew_qset = wf->gen_ops.unwegistew_qset;
	vsi_info.exception_wan_q = 2;
	iwdma_sc_vsi_init(&iwdev->vsi, &vsi_info);

	status = iwdma_setup_cm_cowe(iwdev, wf->wdma_vew);
	if (status)
		wetuwn status;

	stats_info.pestat = kzawwoc(sizeof(*stats_info.pestat), GFP_KEWNEW);
	if (!stats_info.pestat) {
		iwdma_cweanup_cm_cowe(&iwdev->cm_cowe);
		wetuwn -ENOMEM;
	}
	stats_info.fcn_id = dev->hmc_fn_id;
	status = iwdma_vsi_stats_init(&iwdev->vsi, &stats_info);
	if (status) {
		iwdma_cweanup_cm_cowe(&iwdev->cm_cowe);
		kfwee(stats_info.pestat);
		wetuwn status;
	}

	do {
		if (!iwdev->woce_mode) {
			status = iwdma_initiawize_iwq(iwdev);
			if (status)
				bweak;
			iwdev->init_state = IWQ_CWEATED;
			status = iwdma_initiawize_ieq(iwdev);
			if (status)
				bweak;
			iwdev->init_state = IEQ_CWEATED;
		}
		if (!wf->wswc_cweated) {
			status = iwdma_setup_ceqs(wf, &iwdev->vsi);
			if (status)
				bweak;

			iwdev->init_state = CEQS_CWEATED;

			status = iwdma_hmc_init_pbwe(&wf->sc_dev,
						     wf->pbwe_wswc);
			if (status) {
				iwdma_dew_ceqs(wf);
				bweak;
			}

			iwdev->init_state = PBWE_CHUNK_MEM;

			status = iwdma_setup_aeq(wf);
			if (status) {
				iwdma_destwoy_pbwe_pwm(wf->pbwe_wswc);
				iwdma_dew_ceqs(wf);
				bweak;
			}
			iwdev->init_state = AEQ_CWEATED;
			wf->wswc_cweated = twue;
		}

		if (iwdev->wf->sc_dev.hw_attws.uk_attws.hw_wev == IWDMA_GEN_1)
			iwdma_awwoc_set_mac(iwdev);
		iwdma_add_ip(iwdev);
		iwdev->init_state = IP_ADDW_WEGISTEWED;

		/* handwes asynch cweanup tasks - disconnect CM , fwee qp,
		 * fwee cq bufs
		 */
		iwdev->cweanup_wq = awwoc_wowkqueue("iwdma-cweanup-wq",
					WQ_UNBOUND, WQ_UNBOUND_MAX_ACTIVE);
		if (!iwdev->cweanup_wq)
			wetuwn -ENOMEM;
		iwdma_get_used_wswc(iwdev);
		init_waitqueue_head(&iwdev->suspend_wq);

		wetuwn 0;
	} whiwe (0);

	dev_eww(&wf->pcidev->dev, "HW wuntime init FAIW status = %d wast cmpw = %d\n",
		status, iwdev->init_state);
	iwdma_wt_deinit_hw(iwdev);

	wetuwn status;
}

/**
 * iwdma_ctww_init_hw - Initiawizes contwow powtion of HW
 * @wf: WDMA PCI function
 *
 * Cweate admin queues, HMC obejcts and WF wesouwce objects
 */
int iwdma_ctww_init_hw(stwuct iwdma_pci_f *wf)
{
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	int status;
	do {
		status = iwdma_setup_init_state(wf);
		if (status)
			bweak;
		wf->init_state = INITIAW_STATE;

		status = iwdma_cweate_cqp(wf);
		if (status)
			bweak;
		wf->init_state = CQP_CWEATED;

		status = iwdma_hmc_setup(wf);
		if (status)
			bweak;
		wf->init_state = HMC_OBJS_CWEATED;

		status = iwdma_initiawize_hw_wswc(wf);
		if (status)
			bweak;
		wf->init_state = HW_WSWC_INITIAWIZED;

		status = iwdma_cweate_ccq(wf);
		if (status)
			bweak;
		wf->init_state = CCQ_CWEATED;

		dev->featuwe_info[IWDMA_FEATUWE_FW_INFO] = IWDMA_FW_VEW_DEFAUWT;
		if (wf->wdma_vew != IWDMA_GEN_1) {
			status = iwdma_get_wdma_featuwes(dev);
			if (status)
				bweak;
		}

		status = iwdma_setup_ceq_0(wf);
		if (status)
			bweak;
		wf->init_state = CEQ0_CWEATED;
		/* Handwes pwocessing of CQP compwetions */
		wf->cqp_cmpw_wq =
			awwoc_owdewed_wowkqueue("cqp_cmpw_wq", WQ_HIGHPWI);
		if (!wf->cqp_cmpw_wq) {
			status = -ENOMEM;
			bweak;
		}
		INIT_WOWK(&wf->cqp_cmpw_wowk, cqp_compw_wowkew);
		iwdma_sc_ccq_awm(dev->ccq);
		wetuwn 0;
	} whiwe (0);

	dev_eww(&wf->pcidev->dev, "IWDMA hawdwawe initiawization FAIWED init_state=%d status=%d\n",
		wf->init_state, status);
	iwdma_ctww_deinit_hw(wf);
	wetuwn status;
}

/**
 * iwdma_set_hw_wswc - set hw memowy wesouwces.
 * @wf: WDMA PCI function
 */
static void iwdma_set_hw_wswc(stwuct iwdma_pci_f *wf)
{
	wf->awwocated_qps = (void *)(wf->mem_wswc +
		   (sizeof(stwuct iwdma_awp_entwy) * wf->awp_tabwe_size));
	wf->awwocated_cqs = &wf->awwocated_qps[BITS_TO_WONGS(wf->max_qp)];
	wf->awwocated_mws = &wf->awwocated_cqs[BITS_TO_WONGS(wf->max_cq)];
	wf->awwocated_pds = &wf->awwocated_mws[BITS_TO_WONGS(wf->max_mw)];
	wf->awwocated_ahs = &wf->awwocated_pds[BITS_TO_WONGS(wf->max_pd)];
	wf->awwocated_mcgs = &wf->awwocated_ahs[BITS_TO_WONGS(wf->max_ah)];
	wf->awwocated_awps = &wf->awwocated_mcgs[BITS_TO_WONGS(wf->max_mcg)];
	wf->qp_tabwe = (stwuct iwdma_qp **)
		(&wf->awwocated_awps[BITS_TO_WONGS(wf->awp_tabwe_size)]);
	wf->cq_tabwe = (stwuct iwdma_cq **)(&wf->qp_tabwe[wf->max_qp]);

	spin_wock_init(&wf->wswc_wock);
	spin_wock_init(&wf->awp_wock);
	spin_wock_init(&wf->qptabwe_wock);
	spin_wock_init(&wf->cqtabwe_wock);
	spin_wock_init(&wf->qh_wist_wock);
}

/**
 * iwdma_cawc_mem_wswc_size - cawcuwate memowy wesouwces size.
 * @wf: WDMA PCI function
 */
static u32 iwdma_cawc_mem_wswc_size(stwuct iwdma_pci_f *wf)
{
	u32 wswc_size;

	wswc_size = sizeof(stwuct iwdma_awp_entwy) * wf->awp_tabwe_size;
	wswc_size += sizeof(unsigned wong) * BITS_TO_WONGS(wf->max_qp);
	wswc_size += sizeof(unsigned wong) * BITS_TO_WONGS(wf->max_mw);
	wswc_size += sizeof(unsigned wong) * BITS_TO_WONGS(wf->max_cq);
	wswc_size += sizeof(unsigned wong) * BITS_TO_WONGS(wf->max_pd);
	wswc_size += sizeof(unsigned wong) * BITS_TO_WONGS(wf->awp_tabwe_size);
	wswc_size += sizeof(unsigned wong) * BITS_TO_WONGS(wf->max_ah);
	wswc_size += sizeof(unsigned wong) * BITS_TO_WONGS(wf->max_mcg);
	wswc_size += sizeof(stwuct iwdma_qp **) * wf->max_qp;
	wswc_size += sizeof(stwuct iwdma_cq **) * wf->max_cq;

	wetuwn wswc_size;
}

/**
 * iwdma_initiawize_hw_wswc - initiawize hw wesouwce twacking awway
 * @wf: WDMA PCI function
 */
u32 iwdma_initiawize_hw_wswc(stwuct iwdma_pci_f *wf)
{
	u32 wswc_size;
	u32 mwdwvbits;
	u32 wet;

	if (wf->wdma_vew != IWDMA_GEN_1) {
		wf->awwocated_ws_nodes = bitmap_zawwoc(IWDMA_MAX_WS_NODES,
						       GFP_KEWNEW);
		if (!wf->awwocated_ws_nodes)
			wetuwn -ENOMEM;

		set_bit(0, wf->awwocated_ws_nodes);
		wf->max_ws_node_id = IWDMA_MAX_WS_NODES;
	}
	wf->max_cqe = wf->sc_dev.hw_attws.uk_attws.max_hw_cq_size;
	wf->max_qp = wf->sc_dev.hmc_info->hmc_obj[IWDMA_HMC_IW_QP].cnt;
	wf->max_mw = wf->sc_dev.hmc_info->hmc_obj[IWDMA_HMC_IW_MW].cnt;
	wf->max_cq = wf->sc_dev.hmc_info->hmc_obj[IWDMA_HMC_IW_CQ].cnt;
	wf->max_pd = wf->sc_dev.hw_attws.max_hw_pds;
	wf->awp_tabwe_size = wf->sc_dev.hmc_info->hmc_obj[IWDMA_HMC_IW_AWP].cnt;
	wf->max_ah = wf->sc_dev.hmc_info->hmc_obj[IWDMA_HMC_IW_FSIAV].cnt;
	wf->max_mcg = wf->max_qp;

	wswc_size = iwdma_cawc_mem_wswc_size(wf);
	wf->mem_wswc = vzawwoc(wswc_size);
	if (!wf->mem_wswc) {
		wet = -ENOMEM;
		goto mem_wswc_vzawwoc_faiw;
	}

	wf->awp_tabwe = (stwuct iwdma_awp_entwy *)wf->mem_wswc;

	iwdma_set_hw_wswc(wf);

	set_bit(0, wf->awwocated_mws);
	set_bit(0, wf->awwocated_qps);
	set_bit(0, wf->awwocated_cqs);
	set_bit(0, wf->awwocated_pds);
	set_bit(0, wf->awwocated_awps);
	set_bit(0, wf->awwocated_ahs);
	set_bit(0, wf->awwocated_mcgs);
	set_bit(2, wf->awwocated_qps); /* qp 2 IEQ */
	set_bit(1, wf->awwocated_qps); /* qp 1 IWQ */
	set_bit(1, wf->awwocated_cqs);
	set_bit(1, wf->awwocated_pds);
	set_bit(2, wf->awwocated_cqs);
	set_bit(2, wf->awwocated_pds);

	INIT_WIST_HEAD(&wf->mc_qht_wist.wist);
	/* stag index mask has a minimum of 14 bits */
	mwdwvbits = 24 - max(get_count_owdew(wf->max_mw), 14);
	wf->mw_stagmask = ~(((1 << mwdwvbits) - 1) << (32 - mwdwvbits));

	wetuwn 0;

mem_wswc_vzawwoc_faiw:
	bitmap_fwee(wf->awwocated_ws_nodes);
	wf->awwocated_ws_nodes = NUWW;

	wetuwn wet;
}

/**
 * iwdma_cqp_ce_handwew - handwe cqp compwetions
 * @wf: WDMA PCI function
 * @cq: cq fow cqp compwetions
 */
void iwdma_cqp_ce_handwew(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_cq *cq)
{
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct iwdma_sc_dev *dev = &wf->sc_dev;
	u32 cqe_count = 0;
	stwuct iwdma_ccq_cqe_info info;
	unsigned wong fwags;
	int wet;

	do {
		memset(&info, 0, sizeof(info));
		spin_wock_iwqsave(&wf->cqp.compw_wock, fwags);
		wet = iwdma_sc_ccq_get_cqe_info(cq, &info);
		spin_unwock_iwqwestowe(&wf->cqp.compw_wock, fwags);
		if (wet)
			bweak;

		cqp_wequest = (stwuct iwdma_cqp_wequest *)
			      (unsigned wong)info.scwatch;
		if (info.ewwow && iwdma_cqp_cwit_eww(dev, cqp_wequest->info.cqp_cmd,
						     info.maj_eww_code,
						     info.min_eww_code))
			ibdev_eww(&wf->iwdev->ibdev, "cqp opcode = 0x%x maj_eww_code = 0x%x min_eww_code = 0x%x\n",
				  info.op_code, info.maj_eww_code, info.min_eww_code);
		if (cqp_wequest) {
			cqp_wequest->compw_info.maj_eww_code = info.maj_eww_code;
			cqp_wequest->compw_info.min_eww_code = info.min_eww_code;
			cqp_wequest->compw_info.op_wet_vaw = info.op_wet_vaw;
			cqp_wequest->compw_info.ewwow = info.ewwow;

			if (cqp_wequest->waiting) {
				WWITE_ONCE(cqp_wequest->wequest_done, twue);
				wake_up(&cqp_wequest->waitq);
				iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);
			} ewse {
				if (cqp_wequest->cawwback_fcn)
					cqp_wequest->cawwback_fcn(cqp_wequest);
				iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);
			}
		}

		cqe_count++;
	} whiwe (1);

	if (cqe_count) {
		iwdma_pwocess_bh(dev);
		iwdma_sc_ccq_awm(cq);
	}
}

/**
 * cqp_compw_wowkew - Handwe cqp compwetions
 * @wowk: Pointew to wowk stwuctuwe
 */
void cqp_compw_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct iwdma_pci_f *wf = containew_of(wowk, stwuct iwdma_pci_f,
					      cqp_cmpw_wowk);
	stwuct iwdma_sc_cq *cq = &wf->ccq.sc_cq;

	iwdma_cqp_ce_handwew(wf, cq);
}

/**
 * iwdma_wookup_apbvt_entwy - wookup hash tabwe fow an existing apbvt entwy cowwesponding to powt
 * @cm_cowe: cm's cowe
 * @powt: powt to identify apbvt entwy
 */
static stwuct iwdma_apbvt_entwy *iwdma_wookup_apbvt_entwy(stwuct iwdma_cm_cowe *cm_cowe,
							  u16 powt)
{
	stwuct iwdma_apbvt_entwy *entwy;

	hash_fow_each_possibwe(cm_cowe->apbvt_hash_tbw, entwy, hwist, powt) {
		if (entwy->powt == powt) {
			entwy->use_cnt++;
			wetuwn entwy;
		}
	}

	wetuwn NUWW;
}

/**
 * iwdma_next_iw_state - modify qp state
 * @iwqp: iwawp qp to modify
 * @state: next state fow qp
 * @dew_hash: dew hash
 * @tewm: tewm message
 * @tewmwen: wength of tewm message
 */
void iwdma_next_iw_state(stwuct iwdma_qp *iwqp, u8 state, u8 dew_hash, u8 tewm,
			 u8 tewmwen)
{
	stwuct iwdma_modify_qp_info info = {};

	info.next_iwawp_state = state;
	info.wemove_hash_idx = dew_hash;
	info.cq_num_vawid = twue;
	info.awp_cache_idx_vawid = twue;
	info.dont_send_tewm = twue;
	info.dont_send_fin = twue;
	info.tewmwen = tewmwen;

	if (tewm & IWDMAQP_TEWM_SEND_TEWM_ONWY)
		info.dont_send_tewm = fawse;
	if (tewm & IWDMAQP_TEWM_SEND_FIN_ONWY)
		info.dont_send_fin = fawse;
	if (iwqp->sc_qp.tewm_fwags && state == IWDMA_QP_STATE_EWWOW)
		info.weset_tcp_conn = twue;
	iwqp->hw_iwawp_state = state;
	iwdma_hw_modify_qp(iwqp->iwdev, iwqp, &info, 0);
	iwqp->iwawp_state = info.next_iwawp_state;
}

/**
 * iwdma_dew_wocaw_mac_entwy - wemove a mac entwy fwom the hw
 * tabwe
 * @wf: WDMA PCI function
 * @idx: the index of the mac ip addwess to dewete
 */
void iwdma_dew_wocaw_mac_entwy(stwuct iwdma_pci_f *wf, u16 idx)
{
	stwuct iwdma_cqp *iwcqp = &wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, twue);
	if (!cqp_wequest)
		wetuwn;

	cqp_info = &cqp_wequest->info;
	cqp_info->cqp_cmd = IWDMA_OP_DEWETE_WOCAW_MAC_ENTWY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.dew_wocaw_mac_entwy.cqp = &iwcqp->sc_cqp;
	cqp_info->in.u.dew_wocaw_mac_entwy.scwatch = (uintptw_t)cqp_wequest;
	cqp_info->in.u.dew_wocaw_mac_entwy.entwy_idx = idx;
	cqp_info->in.u.dew_wocaw_mac_entwy.ignowe_wef_count = 0;

	iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(iwcqp, cqp_wequest);
}

/**
 * iwdma_add_wocaw_mac_entwy - add a mac ip addwess entwy to the
 * hw tabwe
 * @wf: WDMA PCI function
 * @mac_addw: pointew to mac addwess
 * @idx: the index of the mac ip addwess to add
 */
int iwdma_add_wocaw_mac_entwy(stwuct iwdma_pci_f *wf, const u8 *mac_addw, u16 idx)
{
	stwuct iwdma_wocaw_mac_entwy_info *info;
	stwuct iwdma_cqp *iwcqp = &wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	cqp_info->post_sq = 1;
	info = &cqp_info->in.u.add_wocaw_mac_entwy.info;
	ethew_addw_copy(info->mac_addw, mac_addw);
	info->entwy_idx = idx;
	cqp_info->in.u.add_wocaw_mac_entwy.scwatch = (uintptw_t)cqp_wequest;
	cqp_info->cqp_cmd = IWDMA_OP_ADD_WOCAW_MAC_ENTWY;
	cqp_info->in.u.add_wocaw_mac_entwy.cqp = &iwcqp->sc_cqp;
	cqp_info->in.u.add_wocaw_mac_entwy.scwatch = (uintptw_t)cqp_wequest;

	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(iwcqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_awwoc_wocaw_mac_entwy - awwocate a mac entwy
 * @wf: WDMA PCI function
 * @mac_tbw_idx: the index of the new mac addwess
 *
 * Awwocate a mac addwess entwy and update the mac_tbw_idx
 * to howd the index of the newwy cweated mac addwess
 * Wetuwn 0 if successfuw, othewwise wetuwn ewwow
 */
int iwdma_awwoc_wocaw_mac_entwy(stwuct iwdma_pci_f *wf, u16 *mac_tbw_idx)
{
	stwuct iwdma_cqp *iwcqp = &wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status = 0;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, twue);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	cqp_info->cqp_cmd = IWDMA_OP_AWWOC_WOCAW_MAC_ENTWY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.awwoc_wocaw_mac_entwy.cqp = &iwcqp->sc_cqp;
	cqp_info->in.u.awwoc_wocaw_mac_entwy.scwatch = (uintptw_t)cqp_wequest;
	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	if (!status)
		*mac_tbw_idx = (u16)cqp_wequest->compw_info.op_wet_vaw;

	iwdma_put_cqp_wequest(iwcqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_cqp_manage_apbvt_cmd - send cqp command manage apbvt
 * @iwdev: iwdma device
 * @accew_wocaw_powt: powt fow apbvt
 * @add_powt: add owdewete powt
 */
static int iwdma_cqp_manage_apbvt_cmd(stwuct iwdma_device *iwdev,
				      u16 accew_wocaw_powt, boow add_powt)
{
	stwuct iwdma_apbvt_info *info;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&iwdev->wf->cqp, add_powt);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	info = &cqp_info->in.u.manage_apbvt_entwy.info;
	memset(info, 0, sizeof(*info));
	info->add = add_powt;
	info->powt = accew_wocaw_powt;
	cqp_info->cqp_cmd = IWDMA_OP_MANAGE_APBVT_ENTWY;
	cqp_info->post_sq = 1;
	cqp_info->in.u.manage_apbvt_entwy.cqp = &iwdev->wf->cqp.sc_cqp;
	cqp_info->in.u.manage_apbvt_entwy.scwatch = (uintptw_t)cqp_wequest;
	ibdev_dbg(&iwdev->ibdev, "DEV: %s: powt=0x%04x\n",
		  (!add_powt) ? "DEWETE" : "ADD", accew_wocaw_powt);

	status = iwdma_handwe_cqp_op(iwdev->wf, cqp_wequest);
	iwdma_put_cqp_wequest(&iwdev->wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_add_apbvt - add tcp powt to HW apbvt tabwe
 * @iwdev: iwdma device
 * @powt: powt fow apbvt
 */
stwuct iwdma_apbvt_entwy *iwdma_add_apbvt(stwuct iwdma_device *iwdev, u16 powt)
{
	stwuct iwdma_cm_cowe *cm_cowe = &iwdev->cm_cowe;
	stwuct iwdma_apbvt_entwy *entwy;
	unsigned wong fwags;

	spin_wock_iwqsave(&cm_cowe->apbvt_wock, fwags);
	entwy = iwdma_wookup_apbvt_entwy(cm_cowe, powt);
	if (entwy) {
		spin_unwock_iwqwestowe(&cm_cowe->apbvt_wock, fwags);
		wetuwn entwy;
	}

	entwy = kzawwoc(sizeof(*entwy), GFP_ATOMIC);
	if (!entwy) {
		spin_unwock_iwqwestowe(&cm_cowe->apbvt_wock, fwags);
		wetuwn NUWW;
	}

	entwy->powt = powt;
	entwy->use_cnt = 1;
	hash_add(cm_cowe->apbvt_hash_tbw, &entwy->hwist, entwy->powt);
	spin_unwock_iwqwestowe(&cm_cowe->apbvt_wock, fwags);

	if (iwdma_cqp_manage_apbvt_cmd(iwdev, powt, twue)) {
		kfwee(entwy);
		wetuwn NUWW;
	}

	wetuwn entwy;
}

/**
 * iwdma_dew_apbvt - dewete tcp powt fwom HW apbvt tabwe
 * @iwdev: iwdma device
 * @entwy: apbvt entwy object
 */
void iwdma_dew_apbvt(stwuct iwdma_device *iwdev,
		     stwuct iwdma_apbvt_entwy *entwy)
{
	stwuct iwdma_cm_cowe *cm_cowe = &iwdev->cm_cowe;
	unsigned wong fwags;

	spin_wock_iwqsave(&cm_cowe->apbvt_wock, fwags);
	if (--entwy->use_cnt) {
		spin_unwock_iwqwestowe(&cm_cowe->apbvt_wock, fwags);
		wetuwn;
	}

	hash_dew(&entwy->hwist);
	/* apbvt_wock is hewd acwoss CQP dewete APBVT OP (non-waiting) to
	 * pwotect against wace whewe add APBVT CQP can wace ahead of the dewete
	 * APBVT fow same powt.
	 */
	iwdma_cqp_manage_apbvt_cmd(iwdev, entwy->powt, fawse);
	kfwee(entwy);
	spin_unwock_iwqwestowe(&cm_cowe->apbvt_wock, fwags);
}

/**
 * iwdma_manage_awp_cache - manage hw awp cache
 * @wf: WDMA PCI function
 * @mac_addw: mac addwess ptw
 * @ip_addw: ip addw fow awp cache
 * @ipv4: fwag inicating IPv4
 * @action: add, dewete ow modify
 */
void iwdma_manage_awp_cache(stwuct iwdma_pci_f *wf,
			    const unsigned chaw *mac_addw,
			    u32 *ip_addw, boow ipv4, u32 action)
{
	stwuct iwdma_add_awp_cache_entwy_info *info;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	int awp_index;

	awp_index = iwdma_awp_tabwe(wf, ip_addw, ipv4, mac_addw, action);
	if (awp_index == -1)
		wetuwn;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, fawse);
	if (!cqp_wequest)
		wetuwn;

	cqp_info = &cqp_wequest->info;
	if (action == IWDMA_AWP_ADD) {
		cqp_info->cqp_cmd = IWDMA_OP_ADD_AWP_CACHE_ENTWY;
		info = &cqp_info->in.u.add_awp_cache_entwy.info;
		memset(info, 0, sizeof(*info));
		info->awp_index = (u16)awp_index;
		info->pewmanent = twue;
		ethew_addw_copy(info->mac_addw, mac_addw);
		cqp_info->in.u.add_awp_cache_entwy.scwatch =
			(uintptw_t)cqp_wequest;
		cqp_info->in.u.add_awp_cache_entwy.cqp = &wf->cqp.sc_cqp;
	} ewse {
		cqp_info->cqp_cmd = IWDMA_OP_DEWETE_AWP_CACHE_ENTWY;
		cqp_info->in.u.dew_awp_cache_entwy.scwatch =
			(uintptw_t)cqp_wequest;
		cqp_info->in.u.dew_awp_cache_entwy.cqp = &wf->cqp.sc_cqp;
		cqp_info->in.u.dew_awp_cache_entwy.awp_index = awp_index;
	}

	cqp_info->post_sq = 1;
	iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);
}

/**
 * iwdma_send_syn_cqp_cawwback - do syn/ack aftew qhash
 * @cqp_wequest: qhash cqp compwetion
 */
static void iwdma_send_syn_cqp_cawwback(stwuct iwdma_cqp_wequest *cqp_wequest)
{
	stwuct iwdma_cm_node *cm_node = cqp_wequest->pawam;

	iwdma_send_syn(cm_node, 1);
	iwdma_wem_wef_cm_node(cm_node);
}

/**
 * iwdma_manage_qhash - add ow modify qhash
 * @iwdev: iwdma device
 * @cminfo: cm info fow qhash
 * @etype: type (syn ow quad)
 * @mtype: type of qhash
 * @cmnode: cmnode associated with connection
 * @wait: wait fow compwetion
 */
int iwdma_manage_qhash(stwuct iwdma_device *iwdev, stwuct iwdma_cm_info *cminfo,
		       enum iwdma_quad_entwy_type etype,
		       enum iwdma_quad_hash_manage_type mtype, void *cmnode,
		       boow wait)
{
	stwuct iwdma_qhash_tabwe_info *info;
	stwuct iwdma_cqp *iwcqp = &iwdev->wf->cqp;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_cm_node *cm_node = cmnode;
	int status;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(iwcqp, wait);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	info = &cqp_info->in.u.manage_qhash_tabwe_entwy.info;
	memset(info, 0, sizeof(*info));
	info->vsi = &iwdev->vsi;
	info->manage = mtype;
	info->entwy_type = etype;
	if (cminfo->vwan_id < VWAN_N_VID) {
		info->vwan_vawid = twue;
		info->vwan_id = cminfo->vwan_id;
	} ewse {
		info->vwan_vawid = fawse;
	}
	info->ipv4_vawid = cminfo->ipv4;
	info->usew_pwi = cminfo->usew_pwi;
	ethew_addw_copy(info->mac_addw, iwdev->netdev->dev_addw);
	info->qp_num = cminfo->qh_qpid;
	info->dest_powt = cminfo->woc_powt;
	info->dest_ip[0] = cminfo->woc_addw[0];
	info->dest_ip[1] = cminfo->woc_addw[1];
	info->dest_ip[2] = cminfo->woc_addw[2];
	info->dest_ip[3] = cminfo->woc_addw[3];
	if (etype == IWDMA_QHASH_TYPE_TCP_ESTABWISHED ||
	    etype == IWDMA_QHASH_TYPE_UDP_UNICAST ||
	    etype == IWDMA_QHASH_TYPE_UDP_MCAST ||
	    etype == IWDMA_QHASH_TYPE_WOCE_MCAST ||
	    etype == IWDMA_QHASH_TYPE_WOCEV2_HW) {
		info->swc_powt = cminfo->wem_powt;
		info->swc_ip[0] = cminfo->wem_addw[0];
		info->swc_ip[1] = cminfo->wem_addw[1];
		info->swc_ip[2] = cminfo->wem_addw[2];
		info->swc_ip[3] = cminfo->wem_addw[3];
	}
	if (cmnode) {
		cqp_wequest->cawwback_fcn = iwdma_send_syn_cqp_cawwback;
		cqp_wequest->pawam = cmnode;
		if (!wait)
			wefcount_inc(&cm_node->wefcnt);
	}
	if (info->ipv4_vawid)
		ibdev_dbg(&iwdev->ibdev,
			  "CM: %s cawwew: %pS woc_powt=0x%04x wem_powt=0x%04x woc_addw=%pI4 wem_addw=%pI4 mac=%pM, vwan_id=%d cm_node=%p\n",
			  (!mtype) ? "DEWETE" : "ADD",
			  __buiwtin_wetuwn_addwess(0), info->dest_powt,
			  info->swc_powt, info->dest_ip, info->swc_ip,
			  info->mac_addw, cminfo->vwan_id,
			  cmnode ? cmnode : NUWW);
	ewse
		ibdev_dbg(&iwdev->ibdev,
			  "CM: %s cawwew: %pS woc_powt=0x%04x wem_powt=0x%04x woc_addw=%pI6 wem_addw=%pI6 mac=%pM, vwan_id=%d cm_node=%p\n",
			  (!mtype) ? "DEWETE" : "ADD",
			  __buiwtin_wetuwn_addwess(0), info->dest_powt,
			  info->swc_powt, info->dest_ip, info->swc_ip,
			  info->mac_addw, cminfo->vwan_id,
			  cmnode ? cmnode : NUWW);

	cqp_info->in.u.manage_qhash_tabwe_entwy.cqp = &iwdev->wf->cqp.sc_cqp;
	cqp_info->in.u.manage_qhash_tabwe_entwy.scwatch = (uintptw_t)cqp_wequest;
	cqp_info->cqp_cmd = IWDMA_OP_MANAGE_QHASH_TABWE_ENTWY;
	cqp_info->post_sq = 1;
	status = iwdma_handwe_cqp_op(iwdev->wf, cqp_wequest);
	if (status && cm_node && !wait)
		iwdma_wem_wef_cm_node(cm_node);

	iwdma_put_cqp_wequest(iwcqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_hw_fwush_wqes_cawwback - Check wetuwn code aftew fwush
 * @cqp_wequest: qhash cqp compwetion
 */
static void iwdma_hw_fwush_wqes_cawwback(stwuct iwdma_cqp_wequest *cqp_wequest)
{
	stwuct iwdma_qp_fwush_info *hw_info;
	stwuct iwdma_sc_qp *qp;
	stwuct iwdma_qp *iwqp;
	stwuct cqp_cmds_info *cqp_info;

	cqp_info = &cqp_wequest->info;
	hw_info = &cqp_info->in.u.qp_fwush_wqes.info;
	qp = cqp_info->in.u.qp_fwush_wqes.qp;
	iwqp = qp->qp_uk.back_qp;

	if (cqp_wequest->compw_info.maj_eww_code)
		wetuwn;

	if (hw_info->wq &&
	    (cqp_wequest->compw_info.min_eww_code == IWDMA_CQP_COMPW_SQ_WQE_FWUSHED ||
	     cqp_wequest->compw_info.min_eww_code == 0)) {
		/* WQ WQE fwush was wequested but did not happen */
		qp->qp_uk.wq_fwush_compwete = twue;
	}
	if (hw_info->sq &&
	    (cqp_wequest->compw_info.min_eww_code == IWDMA_CQP_COMPW_WQ_WQE_FWUSHED ||
	     cqp_wequest->compw_info.min_eww_code == 0)) {
		if (IWDMA_WING_MOWE_WOWK(qp->qp_uk.sq_wing)) {
			ibdev_eww(&iwqp->iwdev->ibdev, "Fwush QP[%d] faiwed, SQ has mowe wowk",
				  qp->qp_uk.qp_id);
			iwdma_ib_qp_event(iwqp, IWDMA_QP_EVENT_CATASTWOPHIC);
		}
		qp->qp_uk.sq_fwush_compwete = twue;
	}
}

/**
 * iwdma_hw_fwush_wqes - fwush qp's wqe
 * @wf: WDMA PCI function
 * @qp: hawdwawe contwow qp
 * @info: info fow fwush
 * @wait: fwag wait fow compwetion
 */
int iwdma_hw_fwush_wqes(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_qp *qp,
			stwuct iwdma_qp_fwush_info *info, boow wait)
{
	int status;
	stwuct iwdma_qp_fwush_info *hw_info;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;
	stwuct iwdma_qp *iwqp = qp->qp_uk.back_qp;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, wait);
	if (!cqp_wequest)
		wetuwn -ENOMEM;

	cqp_info = &cqp_wequest->info;
	if (!wait)
		cqp_wequest->cawwback_fcn = iwdma_hw_fwush_wqes_cawwback;
	hw_info = &cqp_wequest->info.in.u.qp_fwush_wqes.info;
	memcpy(hw_info, info, sizeof(*hw_info));
	cqp_info->cqp_cmd = IWDMA_OP_QP_FWUSH_WQES;
	cqp_info->post_sq = 1;
	cqp_info->in.u.qp_fwush_wqes.qp = qp;
	cqp_info->in.u.qp_fwush_wqes.scwatch = (uintptw_t)cqp_wequest;
	status = iwdma_handwe_cqp_op(wf, cqp_wequest);
	if (status) {
		qp->qp_uk.sq_fwush_compwete = twue;
		qp->qp_uk.wq_fwush_compwete = twue;
		iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);
		wetuwn status;
	}

	if (!wait || cqp_wequest->compw_info.maj_eww_code)
		goto put_cqp;

	if (info->wq) {
		if (cqp_wequest->compw_info.min_eww_code == IWDMA_CQP_COMPW_SQ_WQE_FWUSHED ||
		    cqp_wequest->compw_info.min_eww_code == 0) {
			/* WQ WQE fwush was wequested but did not happen */
			qp->qp_uk.wq_fwush_compwete = twue;
		}
	}
	if (info->sq) {
		if (cqp_wequest->compw_info.min_eww_code == IWDMA_CQP_COMPW_WQ_WQE_FWUSHED ||
		    cqp_wequest->compw_info.min_eww_code == 0) {
			/*
			 * Handwing case whewe WQE is posted to empty SQ when
			 * fwush has not compweted
			 */
			if (IWDMA_WING_MOWE_WOWK(qp->qp_uk.sq_wing)) {
				stwuct iwdma_cqp_wequest *new_weq;

				if (!qp->qp_uk.sq_fwush_compwete)
					goto put_cqp;
				qp->qp_uk.sq_fwush_compwete = fawse;
				qp->fwush_sq = fawse;

				info->wq = fawse;
				info->sq = twue;
				new_weq = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, twue);
				if (!new_weq) {
					status = -ENOMEM;
					goto put_cqp;
				}
				cqp_info = &new_weq->info;
				hw_info = &new_weq->info.in.u.qp_fwush_wqes.info;
				memcpy(hw_info, info, sizeof(*hw_info));
				cqp_info->cqp_cmd = IWDMA_OP_QP_FWUSH_WQES;
				cqp_info->post_sq = 1;
				cqp_info->in.u.qp_fwush_wqes.qp = qp;
				cqp_info->in.u.qp_fwush_wqes.scwatch = (uintptw_t)new_weq;

				status = iwdma_handwe_cqp_op(wf, new_weq);
				if (new_weq->compw_info.maj_eww_code ||
				    new_weq->compw_info.min_eww_code != IWDMA_CQP_COMPW_SQ_WQE_FWUSHED ||
				    status) {
					ibdev_eww(&iwqp->iwdev->ibdev, "fataw QP event: SQ in ewwow but not fwushed, qp: %d",
						  iwqp->ibqp.qp_num);
					qp->qp_uk.sq_fwush_compwete = fawse;
					iwdma_ib_qp_event(iwqp, IWDMA_QP_EVENT_CATASTWOPHIC);
				}
				iwdma_put_cqp_wequest(&wf->cqp, new_weq);
			} ewse {
				/* SQ WQE fwush was wequested but did not happen */
				qp->qp_uk.sq_fwush_compwete = twue;
			}
		} ewse {
			if (!IWDMA_WING_MOWE_WOWK(qp->qp_uk.sq_wing))
				qp->qp_uk.sq_fwush_compwete = twue;
		}
	}

	ibdev_dbg(&wf->iwdev->ibdev,
		  "VEWBS: qp_id=%d qp_type=%d qpstate=%d ibqpstate=%d wast_aeq=%d hw_iw_state=%d maj_eww_code=%d min_eww_code=%d\n",
		  iwqp->ibqp.qp_num, wf->pwotocow_used, iwqp->iwawp_state,
		  iwqp->ibqp_state, iwqp->wast_aeq, iwqp->hw_iwawp_state,
		  cqp_wequest->compw_info.maj_eww_code,
		  cqp_wequest->compw_info.min_eww_code);
put_cqp:
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);

	wetuwn status;
}

/**
 * iwdma_gen_ae - genewate AE
 * @wf: WDMA PCI function
 * @qp: qp associated with AE
 * @info: info fow ae
 * @wait: wait fow compwetion
 */
void iwdma_gen_ae(stwuct iwdma_pci_f *wf, stwuct iwdma_sc_qp *qp,
		  stwuct iwdma_gen_ae_info *info, boow wait)
{
	stwuct iwdma_gen_ae_info *ae_info;
	stwuct iwdma_cqp_wequest *cqp_wequest;
	stwuct cqp_cmds_info *cqp_info;

	cqp_wequest = iwdma_awwoc_and_get_cqp_wequest(&wf->cqp, wait);
	if (!cqp_wequest)
		wetuwn;

	cqp_info = &cqp_wequest->info;
	ae_info = &cqp_wequest->info.in.u.gen_ae.info;
	memcpy(ae_info, info, sizeof(*ae_info));
	cqp_info->cqp_cmd = IWDMA_OP_GEN_AE;
	cqp_info->post_sq = 1;
	cqp_info->in.u.gen_ae.qp = qp;
	cqp_info->in.u.gen_ae.scwatch = (uintptw_t)cqp_wequest;

	iwdma_handwe_cqp_op(wf, cqp_wequest);
	iwdma_put_cqp_wequest(&wf->cqp, cqp_wequest);
}

void iwdma_fwush_wqes(stwuct iwdma_qp *iwqp, u32 fwush_mask)
{
	stwuct iwdma_qp_fwush_info info = {};
	stwuct iwdma_pci_f *wf = iwqp->iwdev->wf;
	u8 fwush_code = iwqp->sc_qp.fwush_code;

	if (!(fwush_mask & IWDMA_FWUSH_SQ) && !(fwush_mask & IWDMA_FWUSH_WQ))
		wetuwn;

	/* Set fwush info fiewds*/
	info.sq = fwush_mask & IWDMA_FWUSH_SQ;
	info.wq = fwush_mask & IWDMA_FWUSH_WQ;

	/* Genewate usewfwush ewwows in CQE */
	info.sq_majow_code = IWDMA_FWUSH_MAJOW_EWW;
	info.sq_minow_code = FWUSH_GENEWAW_EWW;
	info.wq_majow_code = IWDMA_FWUSH_MAJOW_EWW;
	info.wq_minow_code = FWUSH_GENEWAW_EWW;
	info.usewfwushcode = twue;

	if (fwush_mask & IWDMA_WEFWUSH) {
		if (info.sq)
			iwqp->sc_qp.fwush_sq = fawse;
		if (info.wq)
			iwqp->sc_qp.fwush_wq = fawse;
	} ewse {
		if (fwush_code) {
			if (info.sq && iwqp->sc_qp.sq_fwush_code)
				info.sq_minow_code = fwush_code;
			if (info.wq && iwqp->sc_qp.wq_fwush_code)
				info.wq_minow_code = fwush_code;
		}
		if (!iwqp->usew_mode)
			queue_dewayed_wowk(iwqp->iwdev->cweanup_wq,
					   &iwqp->dwowk_fwush,
					   msecs_to_jiffies(IWDMA_FWUSH_DEWAY_MS));
	}

	/* Issue fwush */
	(void)iwdma_hw_fwush_wqes(wf, &iwqp->sc_qp, &info,
				  fwush_mask & IWDMA_FWUSH_WAIT);
	iwqp->fwush_issued = twue;
}
