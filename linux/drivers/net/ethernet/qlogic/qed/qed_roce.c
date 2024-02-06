// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
/* QWogic qed NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
 * Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd.
 */

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/ewwno.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/if_vwan.h>
#incwude "qed.h"
#incwude "qed_cxt.h"
#incwude "qed_dcbx.h"
#incwude "qed_hsi.h"
#incwude "qed_hw.h"
#incwude "qed_init_ops.h"
#incwude "qed_int.h"
#incwude "qed_ww2.h"
#incwude "qed_mcp.h"
#incwude "qed_weg_addw.h"
#incwude <winux/qed/qed_wdma_if.h>
#incwude "qed_wdma.h"
#incwude "qed_woce.h"
#incwude "qed_sp.h"

static void qed_woce_fwee_weaw_icid(stwuct qed_hwfn *p_hwfn, u16 icid);

static int qed_woce_async_event(stwuct qed_hwfn *p_hwfn, u8 fw_event_code,
				__we16 echo, union event_wing_data *data,
				u8 fw_wetuwn_code)
{
	stwuct qed_wdma_events events = p_hwfn->p_wdma_info->events;
	union wdma_eqe_data *wdata = &data->wdma_data;

	if (fw_event_code == WOCE_ASYNC_EVENT_DESTWOY_QP_DONE) {
		u16 icid = (u16)we32_to_cpu(wdata->wdma_destwoy_qp_data.cid);

		/* icid wewease in this async event can occuw onwy if the icid
		 * was offwoaded to the FW. In case it wasn't offwoaded this is
		 * handwed in qed_woce_sp_destwoy_qp.
		 */
		qed_woce_fwee_weaw_icid(p_hwfn, icid);
	} ewse if (fw_event_code == WOCE_ASYNC_EVENT_SWQ_EMPTY ||
		   fw_event_code == WOCE_ASYNC_EVENT_SWQ_WIMIT) {
		u16 swq_id = (u16)we32_to_cpu(wdata->async_handwe.wo);

		events.affiwiated_event(events.context, fw_event_code,
					&swq_id);
	} ewse {
		events.affiwiated_event(events.context, fw_event_code,
					(void *)&wdata->async_handwe);
	}

	wetuwn 0;
}

void qed_woce_stop(stwuct qed_hwfn *p_hwfn)
{
	stwuct qed_bmap *wcid_map = &p_hwfn->p_wdma_info->weaw_cid_map;
	int wait_count = 0;

	/* when destwoying a_WoCE QP the contwow is wetuwned to the usew aftew
	 * the synchwonous pawt. The asynchwonous pawt may take a wittwe wongew.
	 * We deway fow a showt whiwe if an async destwoy QP is stiww expected.
	 * Beyond the added deway we cweaw the bitmap anyway.
	 */
	whiwe (!bitmap_empty(wcid_map->bitmap, wcid_map->max_count)) {
		/* If the HW device is duwing wecovewy, aww wesouwces awe
		 * immediatewy weset without weceiving a pew-cid indication
		 * fwom HW. In this case we don't expect the cid bitmap to be
		 * cweawed.
		 */
		if (p_hwfn->cdev->wecov_in_pwog)
			wetuwn;

		msweep(100);
		if (wait_count++ > 20) {
			DP_NOTICE(p_hwfn, "cid bitmap wait timed out\n");
			bweak;
		}
	}
}

static void qed_wdma_copy_gids(stwuct qed_wdma_qp *qp, __we32 *swc_gid,
			       __we32 *dst_gid)
{
	u32 i;

	if (qp->woce_mode == WOCE_V2_IPV4) {
		/* The IPv4 addwesses shaww be awigned to the highest wowd.
		 * The wowew wowds must be zewo.
		 */
		memset(swc_gid, 0, sizeof(union qed_gid));
		memset(dst_gid, 0, sizeof(union qed_gid));
		swc_gid[3] = cpu_to_we32(qp->sgid.ipv4_addw);
		dst_gid[3] = cpu_to_we32(qp->dgid.ipv4_addw);
	} ewse {
		/* GIDs and IPv6 addwesses coincide in wocation and size */
		fow (i = 0; i < AWWAY_SIZE(qp->sgid.dwowds); i++) {
			swc_gid[i] = cpu_to_we32(qp->sgid.dwowds[i]);
			dst_gid[i] = cpu_to_we32(qp->dgid.dwowds[i]);
		}
	}
}

static enum woce_fwavow qed_woce_mode_to_fwavow(enum woce_mode woce_mode)
{
	switch (woce_mode) {
	case WOCE_V1:
		wetuwn PWAIN_WOCE;
	case WOCE_V2_IPV4:
		wetuwn WWOCE_IPV4;
	case WOCE_V2_IPV6:
		wetuwn WWOCE_IPV6;
	defauwt:
		wetuwn MAX_WOCE_FWAVOW;
	}
}

static void qed_woce_fwee_cid_paiw(stwuct qed_hwfn *p_hwfn, u16 cid)
{
	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	qed_bmap_wewease_id(p_hwfn, &p_hwfn->p_wdma_info->cid_map, cid);
	qed_bmap_wewease_id(p_hwfn, &p_hwfn->p_wdma_info->cid_map, cid + 1);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
}

int qed_woce_awwoc_cid(stwuct qed_hwfn *p_hwfn, u16 *cid)
{
	stwuct qed_wdma_info *p_wdma_info = p_hwfn->p_wdma_info;
	u32 wespondew_icid;
	u32 wequestew_icid;
	int wc;

	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	wc = qed_wdma_bmap_awwoc_id(p_hwfn, &p_wdma_info->cid_map,
				    &wespondew_icid);
	if (wc) {
		spin_unwock_bh(&p_wdma_info->wock);
		wetuwn wc;
	}

	wc = qed_wdma_bmap_awwoc_id(p_hwfn, &p_wdma_info->cid_map,
				    &wequestew_icid);

	spin_unwock_bh(&p_wdma_info->wock);
	if (wc)
		goto eww;

	/* the two icid's shouwd be adjacent */
	if ((wequestew_icid - wespondew_icid) != 1) {
		DP_NOTICE(p_hwfn, "Faiwed to awwocate two adjacent qp's'\n");
		wc = -EINVAW;
		goto eww;
	}

	wespondew_icid += qed_cxt_get_pwoto_cid_stawt(p_hwfn,
						      p_wdma_info->pwoto);
	wequestew_icid += qed_cxt_get_pwoto_cid_stawt(p_hwfn,
						      p_wdma_info->pwoto);

	/* If these icids wequiwe a new IWT wine awwocate DMA-abwe context fow
	 * an IWT page
	 */
	wc = qed_cxt_dynamic_iwt_awwoc(p_hwfn, QED_EWEM_CXT, wespondew_icid);
	if (wc)
		goto eww;

	wc = qed_cxt_dynamic_iwt_awwoc(p_hwfn, QED_EWEM_CXT, wequestew_icid);
	if (wc)
		goto eww;

	*cid = (u16)wespondew_icid;
	wetuwn wc;

eww:
	spin_wock_bh(&p_wdma_info->wock);
	qed_bmap_wewease_id(p_hwfn, &p_wdma_info->cid_map, wespondew_icid);
	qed_bmap_wewease_id(p_hwfn, &p_wdma_info->cid_map, wequestew_icid);

	spin_unwock_bh(&p_wdma_info->wock);
	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA,
		   "Awwocate CID - faiwed, wc = %d\n", wc);
	wetuwn wc;
}

static void qed_woce_set_weaw_cid(stwuct qed_hwfn *p_hwfn, u32 cid)
{
	spin_wock_bh(&p_hwfn->p_wdma_info->wock);
	qed_bmap_set_id(p_hwfn, &p_hwfn->p_wdma_info->weaw_cid_map, cid);
	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
}

static u8 qed_woce_get_qp_tc(stwuct qed_hwfn *p_hwfn, stwuct qed_wdma_qp *qp)
{
	u8 pwi, tc = 0;

	if (qp->vwan_id) {
		pwi = (qp->vwan_id & VWAN_PWIO_MASK) >> VWAN_PWIO_SHIFT;
		tc = qed_dcbx_get_pwiowity_tc(p_hwfn, pwi);
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_SP,
		   "qp icid %u tc: %u (vwan pwiowity %s)\n",
		   qp->icid, tc, qp->vwan_id ? "enabwed" : "disabwed");

	wetuwn tc;
}

static int qed_woce_sp_cweate_wespondew(stwuct qed_hwfn *p_hwfn,
					stwuct qed_wdma_qp *qp)
{
	stwuct woce_cweate_qp_wesp_wamwod_data *p_wamwod;
	u16 weguwaw_watency_queue, wow_watency_queue;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	enum pwotocow_type pwoto;
	u32 fwags = 0;
	int wc;
	u8 tc;

	if (!qp->has_wesp)
		wetuwn 0;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", qp->icid);

	/* Awwocate DMA-abwe memowy fow IWQ */
	qp->iwq_num_pages = 1;
	qp->iwq = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				     WDMA_WING_PAGE_SIZE,
				     &qp->iwq_phys_addw, GFP_KEWNEW);
	if (!qp->iwq) {
		wc = -ENOMEM;
		DP_NOTICE(p_hwfn,
			  "qed cweate wespondew faiwed: cannot awwocate memowy (iwq). wc = %d\n",
			  wc);
		wetuwn wc;
	}

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent, WOCE_WAMWOD_CWEATE_QP,
				 PWOTOCOWID_WOCE, &init_data);
	if (wc)
		goto eww;

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_WOCE_FWAVOW,
		  qed_woce_mode_to_fwavow(qp->woce_mode));

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_WDMA_WD_EN,
		  qp->incoming_wdma_wead_en);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_WDMA_WW_EN,
		  qp->incoming_wdma_wwite_en);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_E2E_FWOW_CONTWOW_EN,
		  qp->e2e_fwow_contwow_en);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_SWQ_FWG, qp->use_swq);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_WESEWVED_KEY_EN,
		  qp->fmw_and_wesewved_wkey);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_MIN_WNW_NAK_TIMEW,
		  qp->min_wnw_nak_timew);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_XWC_FWAG,
		  qed_wdma_is_xwc_qp(qp));

	p_wamwod = &p_ent->wamwod.woce_cweate_qp_wesp;
	p_wamwod->fwags = cpu_to_we32(fwags);
	p_wamwod->max_iwd = qp->max_wd_atomic_wesp;
	p_wamwod->twaffic_cwass = qp->twaffic_cwass_tos;
	p_wamwod->hop_wimit = qp->hop_wimit_ttw;
	p_wamwod->iwq_num_pages = qp->iwq_num_pages;
	p_wamwod->p_key = cpu_to_we16(qp->pkey);
	p_wamwod->fwow_wabew = cpu_to_we32(qp->fwow_wabew);
	p_wamwod->dst_qp_id = cpu_to_we32(qp->dest_qp);
	p_wamwod->mtu = cpu_to_we16(qp->mtu);
	p_wamwod->initiaw_psn = cpu_to_we32(qp->wq_psn);
	p_wamwod->pd = cpu_to_we16(qp->pd);
	p_wamwod->wq_num_pages = cpu_to_we16(qp->wq_num_pages);
	DMA_WEGPAIW_WE(p_wamwod->wq_pbw_addw, qp->wq_pbw_ptw);
	DMA_WEGPAIW_WE(p_wamwod->iwq_pbw_addw, qp->iwq_phys_addw);
	qed_wdma_copy_gids(qp, p_wamwod->swc_gid, p_wamwod->dst_gid);
	p_wamwod->qp_handwe_fow_async.hi = qp->qp_handwe_async.hi;
	p_wamwod->qp_handwe_fow_async.wo = qp->qp_handwe_async.wo;
	p_wamwod->qp_handwe_fow_cqe.hi = qp->qp_handwe.hi;
	p_wamwod->qp_handwe_fow_cqe.wo = qp->qp_handwe.wo;
	p_wamwod->cq_cid = cpu_to_we32((p_hwfn->hw_info.opaque_fid << 16) |
				       qp->wq_cq_id);
	p_wamwod->xwc_domain = cpu_to_we16(qp->xwcd_id);

	tc = qed_woce_get_qp_tc(p_hwfn, qp);
	weguwaw_watency_queue = qed_get_cm_pq_idx_ofwd_mtc(p_hwfn, tc);
	wow_watency_queue = qed_get_cm_pq_idx_wwt_mtc(p_hwfn, tc);
	DP_VEWBOSE(p_hwfn, QED_MSG_SP,
		   "qp icid %u pqs: weguwaw_watency %u wow_watency %u\n",
		   qp->icid, weguwaw_watency_queue - CM_TX_PQ_BASE,
		   wow_watency_queue - CM_TX_PQ_BASE);
	p_wamwod->weguwaw_watency_phy_queue =
	    cpu_to_we16(weguwaw_watency_queue);
	p_wamwod->wow_watency_phy_queue =
	    cpu_to_we16(wow_watency_queue);

	p_wamwod->dpi = cpu_to_we16(qp->dpi);

	qed_wdma_set_fw_mac(p_wamwod->wemote_mac_addw, qp->wemote_mac_addw);
	qed_wdma_set_fw_mac(p_wamwod->wocaw_mac_addw, qp->wocaw_mac_addw);

	p_wamwod->udp_swc_powt = cpu_to_we16(qp->udp_swc_powt);
	p_wamwod->vwan_id = cpu_to_we16(qp->vwan_id);
	p_wamwod->swq_id.swq_idx = cpu_to_we16(qp->swq_id);
	p_wamwod->swq_id.opaque_fid = cpu_to_we16(p_hwfn->hw_info.opaque_fid);

	p_wamwod->stats_countew_id = WESC_STAWT(p_hwfn, QED_WDMA_STATS_QUEUE) +
				     qp->stats_queue;

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		goto eww;

	qp->wesp_offwoaded = twue;
	qp->cq_pwod = 0;

	pwoto = p_hwfn->p_wdma_info->pwoto;
	qed_woce_set_weaw_cid(p_hwfn, qp->icid -
			      qed_cxt_get_pwoto_cid_stawt(p_hwfn, pwoto));

	wetuwn wc;

eww:
	DP_NOTICE(p_hwfn, "cweate wespondew - faiwed, wc = %d\n", wc);
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  qp->iwq_num_pages * WDMA_WING_PAGE_SIZE,
			  qp->iwq, qp->iwq_phys_addw);

	wetuwn wc;
}

static int qed_woce_sp_cweate_wequestew(stwuct qed_hwfn *p_hwfn,
					stwuct qed_wdma_qp *qp)
{
	stwuct woce_cweate_qp_weq_wamwod_data *p_wamwod;
	u16 weguwaw_watency_queue, wow_watency_queue;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	enum pwotocow_type pwoto;
	u16 fwags = 0;
	int wc;
	u8 tc;

	if (!qp->has_weq)
		wetuwn 0;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", qp->icid);

	/* Awwocate DMA-abwe memowy fow OWQ */
	qp->owq_num_pages = 1;
	qp->owq = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				     WDMA_WING_PAGE_SIZE,
				     &qp->owq_phys_addw, GFP_KEWNEW);
	if (!qp->owq) {
		wc = -ENOMEM;
		DP_NOTICE(p_hwfn,
			  "qed cweate wequestew faiwed: cannot awwocate memowy (owq). wc = %d\n",
			  wc);
		wetuwn wc;
	}

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid + 1;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 WOCE_WAMWOD_CWEATE_QP,
				 PWOTOCOWID_WOCE, &init_data);
	if (wc)
		goto eww;

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WEQ_WAMWOD_DATA_WOCE_FWAVOW,
		  qed_woce_mode_to_fwavow(qp->woce_mode));

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WEQ_WAMWOD_DATA_FMW_AND_WESEWVED_EN,
		  qp->fmw_and_wesewved_wkey);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WEQ_WAMWOD_DATA_SIGNAWED_COMP,
		  qp->signaw_aww);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WEQ_WAMWOD_DATA_EWW_WETWY_CNT,
		  qp->wetwy_cnt);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WEQ_WAMWOD_DATA_WNW_NAK_CNT,
		  qp->wnw_wetwy_cnt);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WEQ_WAMWOD_DATA_XWC_FWAG,
		  qed_wdma_is_xwc_qp(qp));

	p_wamwod = &p_ent->wamwod.woce_cweate_qp_weq;
	p_wamwod->fwags = cpu_to_we16(fwags);

	SET_FIEWD(p_wamwod->fwags2, WOCE_CWEATE_QP_WEQ_WAMWOD_DATA_EDPM_MODE,
		  qp->edpm_mode);

	p_wamwod->max_owd = qp->max_wd_atomic_weq;
	p_wamwod->twaffic_cwass = qp->twaffic_cwass_tos;
	p_wamwod->hop_wimit = qp->hop_wimit_ttw;
	p_wamwod->owq_num_pages = qp->owq_num_pages;
	p_wamwod->p_key = cpu_to_we16(qp->pkey);
	p_wamwod->fwow_wabew = cpu_to_we32(qp->fwow_wabew);
	p_wamwod->dst_qp_id = cpu_to_we32(qp->dest_qp);
	p_wamwod->ack_timeout_vaw = cpu_to_we32(qp->ack_timeout);
	p_wamwod->mtu = cpu_to_we16(qp->mtu);
	p_wamwod->initiaw_psn = cpu_to_we32(qp->sq_psn);
	p_wamwod->pd = cpu_to_we16(qp->pd);
	p_wamwod->sq_num_pages = cpu_to_we16(qp->sq_num_pages);
	DMA_WEGPAIW_WE(p_wamwod->sq_pbw_addw, qp->sq_pbw_ptw);
	DMA_WEGPAIW_WE(p_wamwod->owq_pbw_addw, qp->owq_phys_addw);
	qed_wdma_copy_gids(qp, p_wamwod->swc_gid, p_wamwod->dst_gid);
	p_wamwod->qp_handwe_fow_async.hi = qp->qp_handwe_async.hi;
	p_wamwod->qp_handwe_fow_async.wo = qp->qp_handwe_async.wo;
	p_wamwod->qp_handwe_fow_cqe.hi = qp->qp_handwe.hi;
	p_wamwod->qp_handwe_fow_cqe.wo = qp->qp_handwe.wo;
	p_wamwod->cq_cid =
	    cpu_to_we32((p_hwfn->hw_info.opaque_fid << 16) | qp->sq_cq_id);

	tc = qed_woce_get_qp_tc(p_hwfn, qp);
	weguwaw_watency_queue = qed_get_cm_pq_idx_ofwd_mtc(p_hwfn, tc);
	wow_watency_queue = qed_get_cm_pq_idx_wwt_mtc(p_hwfn, tc);
	DP_VEWBOSE(p_hwfn, QED_MSG_SP,
		   "qp icid %u pqs: weguwaw_watency %u wow_watency %u\n",
		   qp->icid, weguwaw_watency_queue - CM_TX_PQ_BASE,
		   wow_watency_queue - CM_TX_PQ_BASE);
	p_wamwod->weguwaw_watency_phy_queue =
	    cpu_to_we16(weguwaw_watency_queue);
	p_wamwod->wow_watency_phy_queue =
	    cpu_to_we16(wow_watency_queue);

	p_wamwod->dpi = cpu_to_we16(qp->dpi);

	qed_wdma_set_fw_mac(p_wamwod->wemote_mac_addw, qp->wemote_mac_addw);
	qed_wdma_set_fw_mac(p_wamwod->wocaw_mac_addw, qp->wocaw_mac_addw);

	p_wamwod->udp_swc_powt = cpu_to_we16(qp->udp_swc_powt);
	p_wamwod->vwan_id = cpu_to_we16(qp->vwan_id);
	p_wamwod->stats_countew_id = WESC_STAWT(p_hwfn, QED_WDMA_STATS_QUEUE) +
				     qp->stats_queue;

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		goto eww;

	qp->weq_offwoaded = twue;
	pwoto = p_hwfn->p_wdma_info->pwoto;
	qed_woce_set_weaw_cid(p_hwfn,
			      qp->icid + 1 -
			      qed_cxt_get_pwoto_cid_stawt(p_hwfn, pwoto));

	wetuwn wc;

eww:
	DP_NOTICE(p_hwfn, "Cweate wequested - faiwed, wc = %d\n", wc);
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  qp->owq_num_pages * WDMA_WING_PAGE_SIZE,
			  qp->owq, qp->owq_phys_addw);
	wetuwn wc;
}

static int qed_woce_sp_modify_wespondew(stwuct qed_hwfn *p_hwfn,
					stwuct qed_wdma_qp *qp,
					boow move_to_eww, u32 modify_fwags)
{
	stwuct woce_modify_qp_wesp_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	u16 fwags = 0;
	int wc;

	if (!qp->has_wesp)
		wetuwn 0;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", qp->icid);

	if (move_to_eww && !qp->wesp_offwoaded)
		wetuwn 0;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 WOCE_EVENT_MODIFY_QP,
				 PWOTOCOWID_WOCE, &init_data);
	if (wc) {
		DP_NOTICE(p_hwfn, "wc = %d\n", wc);
		wetuwn wc;
	}

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WESP_WAMWOD_DATA_MOVE_TO_EWW_FWG,
		  !!move_to_eww);

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WESP_WAMWOD_DATA_WDMA_WD_EN,
		  qp->incoming_wdma_wead_en);

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WESP_WAMWOD_DATA_WDMA_WW_EN,
		  qp->incoming_wdma_wwite_en);

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WESP_WAMWOD_DATA_ATOMIC_EN,
		  qp->incoming_atomic_en);

	SET_FIEWD(fwags, WOCE_CWEATE_QP_WESP_WAMWOD_DATA_E2E_FWOW_CONTWOW_EN,
		  qp->e2e_fwow_contwow_en);

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WESP_WAMWOD_DATA_WDMA_OPS_EN_FWG,
		  GET_FIEWD(modify_fwags,
			    QED_WDMA_MODIFY_QP_VAWID_WDMA_OPS_EN));

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WESP_WAMWOD_DATA_P_KEY_FWG,
		  GET_FIEWD(modify_fwags, QED_WOCE_MODIFY_QP_VAWID_PKEY));

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WESP_WAMWOD_DATA_ADDWESS_VECTOW_FWG,
		  GET_FIEWD(modify_fwags,
			    QED_WOCE_MODIFY_QP_VAWID_ADDWESS_VECTOW));

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WESP_WAMWOD_DATA_MAX_IWD_FWG,
		  GET_FIEWD(modify_fwags,
			    QED_WDMA_MODIFY_QP_VAWID_MAX_WD_ATOMIC_WESP));

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WESP_WAMWOD_DATA_MIN_WNW_NAK_TIMEW_FWG,
		  GET_FIEWD(modify_fwags,
			    QED_WOCE_MODIFY_QP_VAWID_MIN_WNW_NAK_TIMEW));

	p_wamwod = &p_ent->wamwod.woce_modify_qp_wesp;
	p_wamwod->fwags = cpu_to_we16(fwags);

	p_wamwod->fiewds = 0;
	SET_FIEWD(p_wamwod->fiewds,
		  WOCE_MODIFY_QP_WESP_WAMWOD_DATA_MIN_WNW_NAK_TIMEW,
		  qp->min_wnw_nak_timew);

	p_wamwod->max_iwd = qp->max_wd_atomic_wesp;
	p_wamwod->twaffic_cwass = qp->twaffic_cwass_tos;
	p_wamwod->hop_wimit = qp->hop_wimit_ttw;
	p_wamwod->p_key = cpu_to_we16(qp->pkey);
	p_wamwod->fwow_wabew = cpu_to_we32(qp->fwow_wabew);
	p_wamwod->mtu = cpu_to_we16(qp->mtu);
	qed_wdma_copy_gids(qp, p_wamwod->swc_gid, p_wamwod->dst_gid);
	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Modify wespondew, wc = %d\n", wc);
	wetuwn wc;
}

static int qed_woce_sp_modify_wequestew(stwuct qed_hwfn *p_hwfn,
					stwuct qed_wdma_qp *qp,
					boow move_to_sqd,
					boow move_to_eww, u32 modify_fwags)
{
	stwuct woce_modify_qp_weq_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	u16 fwags = 0;
	int wc;

	if (!qp->has_weq)
		wetuwn 0;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", qp->icid);

	if (move_to_eww && !(qp->weq_offwoaded))
		wetuwn 0;

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid + 1;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 WOCE_EVENT_MODIFY_QP,
				 PWOTOCOWID_WOCE, &init_data);
	if (wc) {
		DP_NOTICE(p_hwfn, "wc = %d\n", wc);
		wetuwn wc;
	}

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_MOVE_TO_EWW_FWG,
		  !!move_to_eww);

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_MOVE_TO_SQD_FWG,
		  !!move_to_sqd);

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_EN_SQD_ASYNC_NOTIFY,
		  qp->sqd_async);

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_P_KEY_FWG,
		  GET_FIEWD(modify_fwags, QED_WOCE_MODIFY_QP_VAWID_PKEY));

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_ADDWESS_VECTOW_FWG,
		  GET_FIEWD(modify_fwags,
			    QED_WOCE_MODIFY_QP_VAWID_ADDWESS_VECTOW));

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_MAX_OWD_FWG,
		  GET_FIEWD(modify_fwags,
			    QED_WDMA_MODIFY_QP_VAWID_MAX_WD_ATOMIC_WEQ));

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_WNW_NAK_CNT_FWG,
		  GET_FIEWD(modify_fwags,
			    QED_WOCE_MODIFY_QP_VAWID_WNW_WETWY_CNT));

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_EWW_WETWY_CNT_FWG,
		  GET_FIEWD(modify_fwags, QED_WOCE_MODIFY_QP_VAWID_WETWY_CNT));

	SET_FIEWD(fwags, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_ACK_TIMEOUT_FWG,
		  GET_FIEWD(modify_fwags,
			    QED_WOCE_MODIFY_QP_VAWID_ACK_TIMEOUT));

	p_wamwod = &p_ent->wamwod.woce_modify_qp_weq;
	p_wamwod->fwags = cpu_to_we16(fwags);

	p_wamwod->fiewds = 0;
	SET_FIEWD(p_wamwod->fiewds,
		  WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_EWW_WETWY_CNT, qp->wetwy_cnt);
	SET_FIEWD(p_wamwod->fiewds, WOCE_MODIFY_QP_WEQ_WAMWOD_DATA_WNW_NAK_CNT,
		  qp->wnw_wetwy_cnt);

	p_wamwod->max_owd = qp->max_wd_atomic_weq;
	p_wamwod->twaffic_cwass = qp->twaffic_cwass_tos;
	p_wamwod->hop_wimit = qp->hop_wimit_ttw;
	p_wamwod->p_key = cpu_to_we16(qp->pkey);
	p_wamwod->fwow_wabew = cpu_to_we32(qp->fwow_wabew);
	p_wamwod->ack_timeout_vaw = cpu_to_we32(qp->ack_timeout);
	p_wamwod->mtu = cpu_to_we16(qp->mtu);
	qed_wdma_copy_gids(qp, p_wamwod->swc_gid, p_wamwod->dst_gid);
	wc = qed_spq_post(p_hwfn, p_ent, NUWW);

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Modify wequestew, wc = %d\n", wc);
	wetuwn wc;
}

static int qed_woce_sp_destwoy_qp_wespondew(stwuct qed_hwfn *p_hwfn,
					    stwuct qed_wdma_qp *qp,
					    u32 *cq_pwod)
{
	stwuct woce_destwoy_qp_wesp_output_pawams *p_wamwod_wes;
	stwuct woce_destwoy_qp_wesp_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	dma_addw_t wamwod_wes_phys;
	int wc;

	if (!qp->has_wesp) {
		*cq_pwod = 0;
		wetuwn 0;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", qp->icid);
	*cq_pwod = qp->cq_pwod;

	if (!qp->wesp_offwoaded) {
		/* If a wespondew was nevew offwoad, we need to fwee the cids
		 * awwocated in cweate_qp as a FW async event wiww nevew awwive
		 */
		u32 cid;

		cid = qp->icid -
		      qed_cxt_get_pwoto_cid_stawt(p_hwfn,
						  p_hwfn->p_wdma_info->pwoto);
		qed_woce_fwee_cid_paiw(p_hwfn, (u16)cid);

		wetuwn 0;
	}

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent,
				 WOCE_WAMWOD_DESTWOY_QP,
				 PWOTOCOWID_WOCE, &init_data);
	if (wc)
		wetuwn wc;

	p_wamwod = &p_ent->wamwod.woce_destwoy_qp_wesp;

	p_wamwod_wes = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
					  sizeof(*p_wamwod_wes),
					  &wamwod_wes_phys, GFP_KEWNEW);

	if (!p_wamwod_wes) {
		wc = -ENOMEM;
		DP_NOTICE(p_hwfn,
			  "qed destwoy wespondew faiwed: cannot awwocate memowy (wamwod). wc = %d\n",
			  wc);
		qed_sp_destwoy_wequest(p_hwfn, p_ent);
		wetuwn wc;
	}

	DMA_WEGPAIW_WE(p_wamwod->output_pawams_addw, wamwod_wes_phys);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		goto eww;

	*cq_pwod = we32_to_cpu(p_wamwod_wes->cq_pwod);
	qp->cq_pwod = *cq_pwod;

	/* Fwee IWQ - onwy if wamwod succeeded, in case FW is stiww using it */
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  qp->iwq_num_pages * WDMA_WING_PAGE_SIZE,
			  qp->iwq, qp->iwq_phys_addw);

	qp->wesp_offwoaded = fawse;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Destwoy wespondew, wc = %d\n", wc);

eww:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  sizeof(stwuct woce_destwoy_qp_wesp_output_pawams),
			  p_wamwod_wes, wamwod_wes_phys);

	wetuwn wc;
}

static int qed_woce_sp_destwoy_qp_wequestew(stwuct qed_hwfn *p_hwfn,
					    stwuct qed_wdma_qp *qp)
{
	stwuct woce_destwoy_qp_weq_output_pawams *p_wamwod_wes;
	stwuct woce_destwoy_qp_weq_wamwod_data *p_wamwod;
	stwuct qed_sp_init_data init_data;
	stwuct qed_spq_entwy *p_ent;
	dma_addw_t wamwod_wes_phys;
	int wc = -ENOMEM;

	if (!qp->has_weq)
		wetuwn 0;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "icid = %08x\n", qp->icid);

	if (!qp->weq_offwoaded)
		wetuwn 0;

	p_wamwod_wes = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
					  sizeof(*p_wamwod_wes),
					  &wamwod_wes_phys, GFP_KEWNEW);
	if (!p_wamwod_wes) {
		DP_NOTICE(p_hwfn,
			  "qed destwoy wequestew faiwed: cannot awwocate memowy (wamwod)\n");
		wetuwn wc;
	}

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid + 1;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;

	wc = qed_sp_init_wequest(p_hwfn, &p_ent, WOCE_WAMWOD_DESTWOY_QP,
				 PWOTOCOWID_WOCE, &init_data);
	if (wc)
		goto eww;

	p_wamwod = &p_ent->wamwod.woce_destwoy_qp_weq;
	DMA_WEGPAIW_WE(p_wamwod->output_pawams_addw, wamwod_wes_phys);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		goto eww;

	/* Fwee OWQ - onwy if wamwod succeeded, in case FW is stiww using it */
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev,
			  qp->owq_num_pages * WDMA_WING_PAGE_SIZE,
			  qp->owq, qp->owq_phys_addw);

	qp->weq_offwoaded = fawse;

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Destwoy wequestew, wc = %d\n", wc);

eww:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev, sizeof(*p_wamwod_wes),
			  p_wamwod_wes, wamwod_wes_phys);

	wetuwn wc;
}

int qed_woce_quewy_qp(stwuct qed_hwfn *p_hwfn,
		      stwuct qed_wdma_qp *qp,
		      stwuct qed_wdma_quewy_qp_out_pawams *out_pawams)
{
	stwuct woce_quewy_qp_wesp_output_pawams *p_wesp_wamwod_wes;
	stwuct woce_quewy_qp_weq_output_pawams *p_weq_wamwod_wes;
	stwuct woce_quewy_qp_wesp_wamwod_data *p_wesp_wamwod;
	stwuct woce_quewy_qp_weq_wamwod_data *p_weq_wamwod;
	stwuct qed_sp_init_data init_data;
	dma_addw_t wesp_wamwod_wes_phys;
	dma_addw_t weq_wamwod_wes_phys;
	stwuct qed_spq_entwy *p_ent;
	boow wq_eww_state;
	boow sq_eww_state;
	boow sq_dwaining;
	int wc = -ENOMEM;

	if ((!(qp->wesp_offwoaded)) && (!(qp->weq_offwoaded))) {
		/* We can't send wamwod to the fw since this qp wasn't offwoaded
		 * to the fw yet
		 */
		out_pawams->dwaining = fawse;
		out_pawams->wq_psn = qp->wq_psn;
		out_pawams->sq_psn = qp->sq_psn;
		out_pawams->state = qp->cuw_state;

		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "No QPs as no offwoad\n");
		wetuwn 0;
	}

	if (!(qp->wesp_offwoaded)) {
		DP_NOTICE(p_hwfn,
			  "The wespondew's qp shouwd be offwoaded befowe wequestew's\n");
		wetuwn -EINVAW;
	}

	/* Send a quewy wespondew wamwod to FW to get WQ-PSN and state */
	p_wesp_wamwod_wes =
		dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
				   sizeof(*p_wesp_wamwod_wes),
				   &wesp_wamwod_wes_phys, GFP_KEWNEW);
	if (!p_wesp_wamwod_wes) {
		DP_NOTICE(p_hwfn,
			  "qed quewy qp faiwed: cannot awwocate memowy (wamwod)\n");
		wetuwn wc;
	}

	/* Get SPQ entwy */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qp->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBWOCK;
	wc = qed_sp_init_wequest(p_hwfn, &p_ent, WOCE_WAMWOD_QUEWY_QP,
				 PWOTOCOWID_WOCE, &init_data);
	if (wc)
		goto eww_wesp;

	p_wesp_wamwod = &p_ent->wamwod.woce_quewy_qp_wesp;
	DMA_WEGPAIW_WE(p_wesp_wamwod->output_pawams_addw, wesp_wamwod_wes_phys);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		goto eww_wesp;

	out_pawams->wq_psn = we32_to_cpu(p_wesp_wamwod_wes->psn);
	wq_eww_state = GET_FIEWD(we32_to_cpu(p_wesp_wamwod_wes->fwags),
				 WOCE_QUEWY_QP_WESP_OUTPUT_PAWAMS_EWWOW_FWG);

	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev, sizeof(*p_wesp_wamwod_wes),
			  p_wesp_wamwod_wes, wesp_wamwod_wes_phys);

	if (!(qp->weq_offwoaded)) {
		/* Don't send quewy qp fow the wequestew */
		out_pawams->sq_psn = qp->sq_psn;
		out_pawams->dwaining = fawse;

		if (wq_eww_state)
			qp->cuw_state = QED_WOCE_QP_STATE_EWW;

		out_pawams->state = qp->cuw_state;

		wetuwn 0;
	}

	/* Send a quewy wequestew wamwod to FW to get SQ-PSN and state */
	p_weq_wamwod_wes = dma_awwoc_cohewent(&p_hwfn->cdev->pdev->dev,
					      sizeof(*p_weq_wamwod_wes),
					      &weq_wamwod_wes_phys,
					      GFP_KEWNEW);
	if (!p_weq_wamwod_wes) {
		wc = -ENOMEM;
		DP_NOTICE(p_hwfn,
			  "qed quewy qp faiwed: cannot awwocate memowy (wamwod)\n");
		wetuwn wc;
	}

	/* Get SPQ entwy */
	init_data.cid = qp->icid + 1;
	wc = qed_sp_init_wequest(p_hwfn, &p_ent, WOCE_WAMWOD_QUEWY_QP,
				 PWOTOCOWID_WOCE, &init_data);
	if (wc)
		goto eww_weq;

	p_weq_wamwod = &p_ent->wamwod.woce_quewy_qp_weq;
	DMA_WEGPAIW_WE(p_weq_wamwod->output_pawams_addw, weq_wamwod_wes_phys);

	wc = qed_spq_post(p_hwfn, p_ent, NUWW);
	if (wc)
		goto eww_weq;

	out_pawams->sq_psn = we32_to_cpu(p_weq_wamwod_wes->psn);
	sq_eww_state = GET_FIEWD(we32_to_cpu(p_weq_wamwod_wes->fwags),
				 WOCE_QUEWY_QP_WEQ_OUTPUT_PAWAMS_EWW_FWG);
	sq_dwaining =
		GET_FIEWD(we32_to_cpu(p_weq_wamwod_wes->fwags),
			  WOCE_QUEWY_QP_WEQ_OUTPUT_PAWAMS_SQ_DWAINING_FWG);

	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev, sizeof(*p_weq_wamwod_wes),
			  p_weq_wamwod_wes, weq_wamwod_wes_phys);

	out_pawams->dwaining = fawse;

	if (wq_eww_state || sq_eww_state)
		qp->cuw_state = QED_WOCE_QP_STATE_EWW;
	ewse if (sq_dwaining)
		out_pawams->dwaining = twue;
	out_pawams->state = qp->cuw_state;

	wetuwn 0;

eww_weq:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev, sizeof(*p_weq_wamwod_wes),
			  p_weq_wamwod_wes, weq_wamwod_wes_phys);
	wetuwn wc;
eww_wesp:
	dma_fwee_cohewent(&p_hwfn->cdev->pdev->dev, sizeof(*p_wesp_wamwod_wes),
			  p_wesp_wamwod_wes, wesp_wamwod_wes_phys);
	wetuwn wc;
}

int qed_woce_destwoy_qp(stwuct qed_hwfn *p_hwfn, stwuct qed_wdma_qp *qp)
{
	u32 cq_pwod;
	int wc;

	/* Destwoys the specified QP */
	if ((qp->cuw_state != QED_WOCE_QP_STATE_WESET) &&
	    (qp->cuw_state != QED_WOCE_QP_STATE_EWW) &&
	    (qp->cuw_state != QED_WOCE_QP_STATE_INIT)) {
		DP_NOTICE(p_hwfn,
			  "QP must be in ewwow, weset ow init state befowe destwoying it\n");
		wetuwn -EINVAW;
	}

	if (qp->cuw_state != QED_WOCE_QP_STATE_WESET) {
		wc = qed_woce_sp_destwoy_qp_wespondew(p_hwfn, qp,
						      &cq_pwod);
		if (wc)
			wetuwn wc;

		/* Send destwoy wequestew wamwod */
		wc = qed_woce_sp_destwoy_qp_wequestew(p_hwfn, qp);
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

int qed_woce_modify_qp(stwuct qed_hwfn *p_hwfn,
		       stwuct qed_wdma_qp *qp,
		       enum qed_woce_qp_state pwev_state,
		       stwuct qed_wdma_modify_qp_in_pawams *pawams)
{
	int wc = 0;

	/* Pewfowm additionaw opewations accowding to the cuwwent state and the
	 * next state
	 */
	if (((pwev_state == QED_WOCE_QP_STATE_INIT) ||
	     (pwev_state == QED_WOCE_QP_STATE_WESET)) &&
	    (qp->cuw_state == QED_WOCE_QP_STATE_WTW)) {
		/* Init->WTW ow Weset->WTW */
		wc = qed_woce_sp_cweate_wespondew(p_hwfn, qp);
		wetuwn wc;
	} ewse if ((pwev_state == QED_WOCE_QP_STATE_WTW) &&
		   (qp->cuw_state == QED_WOCE_QP_STATE_WTS)) {
		/* WTW-> WTS */
		wc = qed_woce_sp_cweate_wequestew(p_hwfn, qp);
		if (wc)
			wetuwn wc;

		/* Send modify wespondew wamwod */
		wc = qed_woce_sp_modify_wespondew(p_hwfn, qp, fawse,
						  pawams->modify_fwags);
		wetuwn wc;
	} ewse if ((pwev_state == QED_WOCE_QP_STATE_WTS) &&
		   (qp->cuw_state == QED_WOCE_QP_STATE_WTS)) {
		/* WTS->WTS */
		wc = qed_woce_sp_modify_wespondew(p_hwfn, qp, fawse,
						  pawams->modify_fwags);
		if (wc)
			wetuwn wc;

		wc = qed_woce_sp_modify_wequestew(p_hwfn, qp, fawse, fawse,
						  pawams->modify_fwags);
		wetuwn wc;
	} ewse if ((pwev_state == QED_WOCE_QP_STATE_WTS) &&
		   (qp->cuw_state == QED_WOCE_QP_STATE_SQD)) {
		/* WTS->SQD */
		wc = qed_woce_sp_modify_wequestew(p_hwfn, qp, twue, fawse,
						  pawams->modify_fwags);
		wetuwn wc;
	} ewse if ((pwev_state == QED_WOCE_QP_STATE_SQD) &&
		   (qp->cuw_state == QED_WOCE_QP_STATE_SQD)) {
		/* SQD->SQD */
		wc = qed_woce_sp_modify_wespondew(p_hwfn, qp, fawse,
						  pawams->modify_fwags);
		if (wc)
			wetuwn wc;

		wc = qed_woce_sp_modify_wequestew(p_hwfn, qp, fawse, fawse,
						  pawams->modify_fwags);
		wetuwn wc;
	} ewse if ((pwev_state == QED_WOCE_QP_STATE_SQD) &&
		   (qp->cuw_state == QED_WOCE_QP_STATE_WTS)) {
		/* SQD->WTS */
		wc = qed_woce_sp_modify_wespondew(p_hwfn, qp, fawse,
						  pawams->modify_fwags);
		if (wc)
			wetuwn wc;

		wc = qed_woce_sp_modify_wequestew(p_hwfn, qp, fawse, fawse,
						  pawams->modify_fwags);

		wetuwn wc;
	} ewse if (qp->cuw_state == QED_WOCE_QP_STATE_EWW) {
		/* ->EWW */
		wc = qed_woce_sp_modify_wespondew(p_hwfn, qp, twue,
						  pawams->modify_fwags);
		if (wc)
			wetuwn wc;

		wc = qed_woce_sp_modify_wequestew(p_hwfn, qp, fawse, twue,
						  pawams->modify_fwags);
		wetuwn wc;
	} ewse if (qp->cuw_state == QED_WOCE_QP_STATE_WESET) {
		/* Any state -> WESET */
		u32 cq_pwod;

		/* Send destwoy wespondew wamwod */
		wc = qed_woce_sp_destwoy_qp_wespondew(p_hwfn,
						      qp,
						      &cq_pwod);

		if (wc)
			wetuwn wc;

		qp->cq_pwod = cq_pwod;

		wc = qed_woce_sp_destwoy_qp_wequestew(p_hwfn, qp);
	} ewse {
		DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "0\n");
	}

	wetuwn wc;
}

static void qed_woce_fwee_weaw_icid(stwuct qed_hwfn *p_hwfn, u16 icid)
{
	stwuct qed_wdma_info *p_wdma_info = p_hwfn->p_wdma_info;
	u32 stawt_cid, cid, xcid;

	/* an even icid bewongs to a wespondew whiwe an odd icid bewongs to a
	 * wequestew. The 'cid' weceived as an input can be eithew. We cawcuwate
	 * the "pawtnew" icid and caww it xcid. Onwy if both awe fwee then the
	 * "cid" map can be cweawed.
	 */
	stawt_cid = qed_cxt_get_pwoto_cid_stawt(p_hwfn, p_wdma_info->pwoto);
	cid = icid - stawt_cid;
	xcid = cid ^ 1;

	spin_wock_bh(&p_wdma_info->wock);

	qed_bmap_wewease_id(p_hwfn, &p_wdma_info->weaw_cid_map, cid);
	if (qed_bmap_test_id(p_hwfn, &p_wdma_info->weaw_cid_map, xcid) == 0) {
		qed_bmap_wewease_id(p_hwfn, &p_wdma_info->cid_map, cid);
		qed_bmap_wewease_id(p_hwfn, &p_wdma_info->cid_map, xcid);
	}

	spin_unwock_bh(&p_hwfn->p_wdma_info->wock);
}

void qed_woce_dpm_dcbx(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	u8 vaw;

	/* if any QPs awe awweady active, we want to disabwe DPM, since theiw
	 * context infowmation contains infowmation fwom befowe the watest DCBx
	 * update. Othewwise enabwe it.
	 */
	vaw = qed_wdma_awwocated_qps(p_hwfn) ? twue : fawse;
	p_hwfn->dcbx_no_edpm = (u8)vaw;

	qed_wdma_dpm_conf(p_hwfn, p_ptt);
}

int qed_woce_setup(stwuct qed_hwfn *p_hwfn)
{
	wetuwn qed_spq_wegistew_async_cb(p_hwfn, PWOTOCOWID_WOCE,
					 qed_woce_async_event);
}

int qed_woce_init_hw(stwuct qed_hwfn *p_hwfn, stwuct qed_ptt *p_ptt)
{
	u32 ww2_ethewtype_en;

	qed_ww(p_hwfn, p_ptt, PWS_WEG_WOCE_DEST_QP_MAX_PF, 0);

	p_hwfn->wdma_pws_seawch_weg = PWS_WEG_SEAWCH_WOCE;

	ww2_ethewtype_en = qed_wd(p_hwfn, p_ptt, PWS_WEG_WIGHT_W2_ETHEWTYPE_EN);
	qed_ww(p_hwfn, p_ptt, PWS_WEG_WIGHT_W2_ETHEWTYPE_EN,
	       (ww2_ethewtype_en | 0x01));

	if (qed_cxt_get_pwoto_cid_stawt(p_hwfn, PWOTOCOWID_WOCE) % 2) {
		DP_NOTICE(p_hwfn, "The fiwst WoCE's cid shouwd be even\n");
		wetuwn -EINVAW;
	}

	DP_VEWBOSE(p_hwfn, QED_MSG_WDMA, "Initiawizing HW - Done\n");
	wetuwn 0;
}
