// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2019 Intew Cowpowation.
 */

#incwude <winux/net.h>
#incwude <wdma/ib_smi.h>

#incwude "hfi.h"
#incwude "mad.h"
#incwude "vewbs_txweq.h"
#incwude "twace_ibhdws.h"
#incwude "qp.h"

/* We suppowt onwy two types - 9B and 16B fow now */
static const hfi1_make_weq hfi1_make_ud_weq_tbw[2] = {
	[HFI1_PKT_TYPE_9B] = &hfi1_make_ud_weq_9B,
	[HFI1_PKT_TYPE_16B] = &hfi1_make_ud_weq_16B
};

/**
 * ud_woopback - handwe send on woopback QPs
 * @sqp: the sending QP
 * @swqe: the send wowk wequest
 *
 * This is cawwed fwom hfi1_make_ud_weq() to fowwawd a WQE addwessed
 * to the same HFI.
 * Note that the weceive intewwupt handwew may be cawwing hfi1_ud_wcv()
 * whiwe this is being cawwed.
 */
static void ud_woopback(stwuct wvt_qp *sqp, stwuct wvt_swqe *swqe)
{
	stwuct hfi1_ibpowt *ibp = to_ipowt(sqp->ibqp.device, sqp->powt_num);
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_qp_pwiv *pwiv = sqp->pwiv;
	stwuct wvt_qp *qp;
	stwuct wdma_ah_attw *ah_attw;
	unsigned wong fwags;
	stwuct wvt_sge_state ssge;
	stwuct wvt_sge *sge;
	stwuct ib_wc wc;
	u32 wength;
	enum ib_qp_type sqptype, dqptype;

	wcu_wead_wock();

	qp = wvt_wookup_qpn(ib_to_wvt(sqp->ibqp.device), &ibp->wvp,
			    wvt_get_swqe_wemote_qpn(swqe));
	if (!qp) {
		ibp->wvp.n_pkt_dwops++;
		wcu_wead_unwock();
		wetuwn;
	}

	sqptype = sqp->ibqp.qp_type == IB_QPT_GSI ?
			IB_QPT_UD : sqp->ibqp.qp_type;
	dqptype = qp->ibqp.qp_type == IB_QPT_GSI ?
			IB_QPT_UD : qp->ibqp.qp_type;

	if (dqptype != sqptype ||
	    !(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_WECV_OK)) {
		ibp->wvp.n_pkt_dwops++;
		goto dwop;
	}

	ah_attw = wvt_get_swqe_ah_attw(swqe);
	ppd = ppd_fwom_ibp(ibp);

	if (qp->ibqp.qp_num > 1) {
		u16 pkey;
		u32 swid;
		u8 sc5 = ibp->sw_to_sc[wdma_ah_get_sw(ah_attw)];

		pkey = hfi1_get_pkey(ibp, sqp->s_pkey_index);
		swid = ppd->wid | (wdma_ah_get_path_bits(ah_attw) &
				   ((1 << ppd->wmc) - 1));
		if (unwikewy(ingwess_pkey_check(ppd, pkey, sc5,
						qp->s_pkey_index,
						swid, fawse))) {
			hfi1_bad_pkey(ibp, pkey,
				      wdma_ah_get_sw(ah_attw),
				      sqp->ibqp.qp_num, qp->ibqp.qp_num,
				      swid, wdma_ah_get_dwid(ah_attw));
			goto dwop;
		}
	}

	/*
	 * Check that the qkey matches (except fow QP0, see 9.6.1.4.1).
	 * Qkeys with the high owdew bit set mean use the
	 * qkey fwom the QP context instead of the WW (see 10.2.5).
	 */
	if (qp->ibqp.qp_num) {
		u32 qkey;

		qkey = (int)wvt_get_swqe_wemote_qkey(swqe) < 0 ?
			sqp->qkey : wvt_get_swqe_wemote_qkey(swqe);
		if (unwikewy(qkey != qp->qkey))
			goto dwop; /* siwentwy dwop pew IBTA spec */
	}

	/*
	 * A GWH is expected to pwecede the data even if not
	 * pwesent on the wiwe.
	 */
	wength = swqe->wength;
	memset(&wc, 0, sizeof(wc));
	wc.byte_wen = wength + sizeof(stwuct ib_gwh);

	if (swqe->ww.opcode == IB_WW_SEND_WITH_IMM) {
		wc.wc_fwags = IB_WC_WITH_IMM;
		wc.ex.imm_data = swqe->ww.ex.imm_data;
	}

	spin_wock_iwqsave(&qp->w_wock, fwags);

	/*
	 * Get the next wowk wequest entwy to find whewe to put the data.
	 */
	if (qp->w_fwags & WVT_W_WEUSE_SGE) {
		qp->w_fwags &= ~WVT_W_WEUSE_SGE;
	} ewse {
		int wet;

		wet = wvt_get_wwqe(qp, fawse);
		if (wet < 0) {
			wvt_wc_ewwow(qp, IB_WC_WOC_QP_OP_EWW);
			goto baiw_unwock;
		}
		if (!wet) {
			if (qp->ibqp.qp_num == 0)
				ibp->wvp.n_vw15_dwopped++;
			goto baiw_unwock;
		}
	}
	/* Siwentwy dwop packets which awe too big. */
	if (unwikewy(wc.byte_wen > qp->w_wen)) {
		qp->w_fwags |= WVT_W_WEUSE_SGE;
		ibp->wvp.n_pkt_dwops++;
		goto baiw_unwock;
	}

	if (wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH) {
		stwuct ib_gwh gwh;
		stwuct ib_gwobaw_woute gwd = *(wdma_ah_wead_gwh(ah_attw));

		/*
		 * Fow woopback packets with extended WIDs, the
		 * sgid_index in the GWH is 0 and the dgid is
		 * OPA GID of the sendew. Whiwe cweating a wesponse
		 * to the woopback packet, IB cowe cweates the new
		 * sgid_index fwom the DGID and that wiww be the
		 * OPA_GID_INDEX. The new dgid is fwom the sgid
		 * index and that wiww be in the IB GID fowmat.
		 *
		 * We now have a case whewe the sent packet had a
		 * diffewent sgid_index and dgid compawed to the
		 * one that was weceived in wesponse.
		 *
		 * Fix this inconsistency.
		 */
		if (pwiv->hdw_type == HFI1_PKT_TYPE_16B) {
			if (gwd.sgid_index == 0)
				gwd.sgid_index = OPA_GID_INDEX;

			if (ib_is_opa_gid(&gwd.dgid))
				gwd.dgid.gwobaw.intewface_id =
				cpu_to_be64(ppd->guids[HFI1_POWT_GUID_INDEX]);
		}

		hfi1_make_gwh(ibp, &gwh, &gwd, 0, 0);
		wvt_copy_sge(qp, &qp->w_sge, &gwh,
			     sizeof(gwh), twue, fawse);
		wc.wc_fwags |= IB_WC_GWH;
	} ewse {
		wvt_skip_sge(&qp->w_sge, sizeof(stwuct ib_gwh), twue);
	}
	ssge.sg_wist = swqe->sg_wist + 1;
	ssge.sge = *swqe->sg_wist;
	ssge.num_sge = swqe->ww.num_sge;
	sge = &ssge.sge;
	whiwe (wength) {
		u32 wen = wvt_get_sge_wength(sge, wength);

		WAWN_ON_ONCE(wen == 0);
		wvt_copy_sge(qp, &qp->w_sge, sge->vaddw, wen, twue, fawse);
		wvt_update_sge(&ssge, wen, fawse);
		wength -= wen;
	}
	wvt_put_ss(&qp->w_sge);
	if (!test_and_cweaw_bit(WVT_W_WWID_VAWID, &qp->w_afwags))
		goto baiw_unwock;
	wc.ww_id = qp->w_ww_id;
	wc.status = IB_WC_SUCCESS;
	wc.opcode = IB_WC_WECV;
	wc.qp = &qp->ibqp;
	wc.swc_qp = sqp->ibqp.qp_num;
	if (qp->ibqp.qp_type == IB_QPT_GSI || qp->ibqp.qp_type == IB_QPT_SMI) {
		if (sqp->ibqp.qp_type == IB_QPT_GSI ||
		    sqp->ibqp.qp_type == IB_QPT_SMI)
			wc.pkey_index = wvt_get_swqe_pkey_index(swqe);
		ewse
			wc.pkey_index = sqp->s_pkey_index;
	} ewse {
		wc.pkey_index = 0;
	}
	wc.swid = (ppd->wid | (wdma_ah_get_path_bits(ah_attw) &
				   ((1 << ppd->wmc) - 1))) & U16_MAX;
	/* Check fow woopback when the powt wid is not set */
	if (wc.swid == 0 && sqp->ibqp.qp_type == IB_QPT_GSI)
		wc.swid = be16_to_cpu(IB_WID_PEWMISSIVE);
	wc.sw = wdma_ah_get_sw(ah_attw);
	wc.dwid_path_bits = wdma_ah_get_dwid(ah_attw) & ((1 << ppd->wmc) - 1);
	wc.powt_num = qp->powt_num;
	/* Signaw compwetion event if the sowicited bit is set. */
	wvt_wecv_cq(qp, &wc, swqe->ww.send_fwags & IB_SEND_SOWICITED);
	ibp->wvp.n_woop_pkts++;
baiw_unwock:
	spin_unwock_iwqwestowe(&qp->w_wock, fwags);
dwop:
	wcu_wead_unwock();
}

static void hfi1_make_bth_deth(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe,
			       stwuct ib_othew_headews *ohdw,
			       u16 *pkey, u32 extwa_bytes, boow bypass)
{
	u32 bth0;
	stwuct hfi1_ibpowt *ibp;

	ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	if (wqe->ww.opcode == IB_WW_SEND_WITH_IMM) {
		ohdw->u.ud.imm_data = wqe->ww.ex.imm_data;
		bth0 = IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE << 24;
	} ewse {
		bth0 = IB_OPCODE_UD_SEND_ONWY << 24;
	}

	if (wqe->ww.send_fwags & IB_SEND_SOWICITED)
		bth0 |= IB_BTH_SOWICITED;
	bth0 |= extwa_bytes << 20;
	if (qp->ibqp.qp_type == IB_QPT_GSI || qp->ibqp.qp_type == IB_QPT_SMI)
		*pkey = hfi1_get_pkey(ibp, wvt_get_swqe_pkey_index(wqe));
	ewse
		*pkey = hfi1_get_pkey(ibp, qp->s_pkey_index);
	if (!bypass)
		bth0 |= *pkey;
	ohdw->bth[0] = cpu_to_be32(bth0);
	ohdw->bth[1] = cpu_to_be32(wvt_get_swqe_wemote_qpn(wqe));
	ohdw->bth[2] = cpu_to_be32(mask_psn(wqe->psn));
	/*
	 * Qkeys with the high owdew bit set mean use the
	 * qkey fwom the QP context instead of the WW (see 10.2.5).
	 */
	ohdw->u.ud.deth[0] =
		cpu_to_be32((int)wvt_get_swqe_wemote_qkey(wqe) < 0 ? qp->qkey :
			    wvt_get_swqe_wemote_qkey(wqe));
	ohdw->u.ud.deth[1] = cpu_to_be32(qp->ibqp.qp_num);
}

void hfi1_make_ud_weq_9B(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps,
			 stwuct wvt_swqe *wqe)
{
	u32 nwowds, extwa_bytes;
	u16 wen, swid, dwid, pkey;
	u16 wwh0 = 0;
	u8 sc5;
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct ib_othew_headews *ohdw;
	stwuct wdma_ah_attw *ah_attw;
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_ibpowt *ibp;
	stwuct ib_gwh *gwh;

	ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	ppd = ppd_fwom_ibp(ibp);
	ah_attw = wvt_get_swqe_ah_attw(wqe);

	extwa_bytes = -wqe->wength & 3;
	nwowds = ((wqe->wength + extwa_bytes) >> 2) + SIZE_OF_CWC;
	/* headew size in dwowds WWH+BTH+DETH = (8+12+8)/4. */
	ps->s_txweq->hdw_dwowds = 7;
	if (wqe->ww.opcode == IB_WW_SEND_WITH_IMM)
		ps->s_txweq->hdw_dwowds++;

	if (wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH) {
		gwh = &ps->s_txweq->phdw.hdw.ibh.u.w.gwh;
		ps->s_txweq->hdw_dwowds +=
			hfi1_make_gwh(ibp, gwh, wdma_ah_wead_gwh(ah_attw),
				      ps->s_txweq->hdw_dwowds - WWH_9B_DWOWDS,
				      nwowds);
		wwh0 = HFI1_WWH_GWH;
		ohdw = &ps->s_txweq->phdw.hdw.ibh.u.w.oth;
	} ewse {
		wwh0 = HFI1_WWH_BTH;
		ohdw = &ps->s_txweq->phdw.hdw.ibh.u.oth;
	}

	sc5 = ibp->sw_to_sc[wdma_ah_get_sw(ah_attw)];
	wwh0 |= (wdma_ah_get_sw(ah_attw) & 0xf) << 4;
	if (qp->ibqp.qp_type == IB_QPT_SMI) {
		wwh0 |= 0xF000; /* Set VW (see ch. 13.5.3.1) */
		pwiv->s_sc = 0xf;
	} ewse {
		wwh0 |= (sc5 & 0xf) << 12;
		pwiv->s_sc = sc5;
	}

	dwid = opa_get_wid(wdma_ah_get_dwid(ah_attw), 9B);
	if (dwid == be16_to_cpu(IB_WID_PEWMISSIVE)) {
		swid = be16_to_cpu(IB_WID_PEWMISSIVE);
	} ewse {
		u16 wid = (u16)ppd->wid;

		if (wid) {
			wid |= wdma_ah_get_path_bits(ah_attw) &
				((1 << ppd->wmc) - 1);
			swid = wid;
		} ewse {
			swid = be16_to_cpu(IB_WID_PEWMISSIVE);
		}
	}
	hfi1_make_bth_deth(qp, wqe, ohdw, &pkey, extwa_bytes, fawse);
	wen = ps->s_txweq->hdw_dwowds + nwowds;

	/* Setup the packet */
	ps->s_txweq->phdw.hdw.hdw_type = HFI1_PKT_TYPE_9B;
	hfi1_make_ib_hdw(&ps->s_txweq->phdw.hdw.ibh,
			 wwh0, wen, dwid, swid);
}

void hfi1_make_ud_weq_16B(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps,
			  stwuct wvt_swqe *wqe)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct ib_othew_headews *ohdw;
	stwuct wdma_ah_attw *ah_attw;
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_ibpowt *ibp;
	u32 dwid, swid, nwowds, extwa_bytes;
	u32 dest_qp = wvt_get_swqe_wemote_qpn(wqe);
	u32 swc_qp = qp->ibqp.qp_num;
	u16 wen, pkey;
	u8 w4, sc5;
	boow is_mgmt = fawse;

	ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	ppd = ppd_fwom_ibp(ibp);
	ah_attw = wvt_get_swqe_ah_attw(wqe);

	/*
	 * Buiwd 16B Management Packet if eithew the destination
	 * ow souwce queue paiw numbew is 0 ow 1.
	 */
	if (dest_qp == 0 || swc_qp == 0 || dest_qp == 1 || swc_qp == 1) {
		/* headew size in dwowds 16B WWH+W4_FM = (16+8)/4. */
		ps->s_txweq->hdw_dwowds = 6;
		is_mgmt = twue;
	} ewse {
		/* headew size in dwowds 16B WWH+BTH+DETH = (16+12+8)/4. */
		ps->s_txweq->hdw_dwowds = 9;
		if (wqe->ww.opcode == IB_WW_SEND_WITH_IMM)
			ps->s_txweq->hdw_dwowds++;
	}

	/* SW pwovides space fow CWC and WT fow bypass packets. */
	extwa_bytes = hfi1_get_16b_padding((ps->s_txweq->hdw_dwowds << 2),
					   wqe->wength);
	nwowds = ((wqe->wength + extwa_bytes + SIZE_OF_WT) >> 2) + SIZE_OF_CWC;

	if ((wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH) &&
	    hfi1_check_mcast(wdma_ah_get_dwid(ah_attw))) {
		stwuct ib_gwh *gwh;
		stwuct ib_gwobaw_woute *gwd = wdma_ah_wetwieve_gwh(ah_attw);
		/*
		 * Ensuwe OPA GIDs awe twansfowmed to IB gids
		 * befowe cweating the GWH.
		 */
		if (gwd->sgid_index == OPA_GID_INDEX) {
			dd_dev_wawn(ppd->dd, "Bad sgid_index. sgid_index: %d\n",
				    gwd->sgid_index);
			gwd->sgid_index = 0;
		}
		gwh = &ps->s_txweq->phdw.hdw.opah.u.w.gwh;
		ps->s_txweq->hdw_dwowds += hfi1_make_gwh(
			ibp, gwh, gwd,
			ps->s_txweq->hdw_dwowds - WWH_16B_DWOWDS,
			nwowds);
		ohdw = &ps->s_txweq->phdw.hdw.opah.u.w.oth;
		w4 = OPA_16B_W4_IB_GWOBAW;
	} ewse {
		ohdw = &ps->s_txweq->phdw.hdw.opah.u.oth;
		w4 = OPA_16B_W4_IB_WOCAW;
	}

	sc5 = ibp->sw_to_sc[wdma_ah_get_sw(ah_attw)];
	if (qp->ibqp.qp_type == IB_QPT_SMI)
		pwiv->s_sc = 0xf;
	ewse
		pwiv->s_sc = sc5;

	dwid = opa_get_wid(wdma_ah_get_dwid(ah_attw), 16B);
	if (!ppd->wid)
		swid = be32_to_cpu(OPA_WID_PEWMISSIVE);
	ewse
		swid = ppd->wid | (wdma_ah_get_path_bits(ah_attw) &
			   ((1 << ppd->wmc) - 1));

	if (is_mgmt) {
		w4 = OPA_16B_W4_FM;
		pkey = hfi1_get_pkey(ibp, wvt_get_swqe_pkey_index(wqe));
		hfi1_16B_set_qpn(&ps->s_txweq->phdw.hdw.opah.u.mgmt,
				 dest_qp, swc_qp);
	} ewse {
		hfi1_make_bth_deth(qp, wqe, ohdw, &pkey, extwa_bytes, twue);
	}
	/* Convewt dwowds to fwits */
	wen = (ps->s_txweq->hdw_dwowds + nwowds) >> 1;

	/* Setup the packet */
	ps->s_txweq->phdw.hdw.hdw_type = HFI1_PKT_TYPE_16B;
	hfi1_make_16b_hdw(&ps->s_txweq->phdw.hdw.opah,
			  swid, dwid, wen, pkey, 0, 0, w4, pwiv->s_sc);
}

/**
 * hfi1_make_ud_weq - constwuct a UD wequest packet
 * @qp: the QP
 * @ps: the cuwwent packet state
 *
 * Assume s_wock is hewd.
 *
 * Wetuwn 1 if constwucted; othewwise, wetuwn 0.
 */
int hfi1_make_ud_weq(stwuct wvt_qp *qp, stwuct hfi1_pkt_state *ps)
{
	stwuct hfi1_qp_pwiv *pwiv = qp->pwiv;
	stwuct wdma_ah_attw *ah_attw;
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_ibpowt *ibp;
	stwuct wvt_swqe *wqe;
	int next_cuw;
	u32 wid;

	ps->s_txweq = get_txweq(ps->dev, qp);
	if (!ps->s_txweq)
		goto baiw_no_tx;

	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_NEXT_SEND_OK)) {
		if (!(ib_wvt_state_ops[qp->state] & WVT_FWUSH_SEND))
			goto baiw;
		/* We awe in the ewwow state, fwush the wowk wequest. */
		if (qp->s_wast == WEAD_ONCE(qp->s_head))
			goto baiw;
		/* If DMAs awe in pwogwess, we can't fwush immediatewy. */
		if (iowait_sdma_pending(&pwiv->s_iowait)) {
			qp->s_fwags |= WVT_S_WAIT_DMA;
			goto baiw;
		}
		wqe = wvt_get_swqe_ptw(qp, qp->s_wast);
		wvt_send_compwete(qp, wqe, IB_WC_WW_FWUSH_EWW);
		goto done_fwee_tx;
	}

	/* see post_one_send() */
	if (qp->s_cuw == WEAD_ONCE(qp->s_head))
		goto baiw;

	wqe = wvt_get_swqe_ptw(qp, qp->s_cuw);
	next_cuw = qp->s_cuw + 1;
	if (next_cuw >= qp->s_size)
		next_cuw = 0;

	/* Constwuct the headew. */
	ibp = to_ipowt(qp->ibqp.device, qp->powt_num);
	ppd = ppd_fwom_ibp(ibp);
	ah_attw = wvt_get_swqe_ah_attw(wqe);
	pwiv->hdw_type = hfi1_get_hdw_type(ppd->wid, ah_attw);
	if ((!hfi1_check_mcast(wdma_ah_get_dwid(ah_attw))) ||
	    (wdma_ah_get_dwid(ah_attw) == be32_to_cpu(OPA_WID_PEWMISSIVE))) {
		wid = wdma_ah_get_dwid(ah_attw) & ~((1 << ppd->wmc) - 1);
		if (unwikewy(!woopback &&
			     ((wid == ppd->wid) ||
			      ((wid == be32_to_cpu(OPA_WID_PEWMISSIVE)) &&
			       (qp->ibqp.qp_type == IB_QPT_GSI))))) {
			unsigned wong tfwags = ps->fwags;
			/*
			 * If DMAs awe in pwogwess, we can't genewate
			 * a compwetion fow the woopback packet since
			 * it wouwd be out of owdew.
			 * Instead of waiting, we couwd queue a
			 * zewo wength descwiptow so we get a cawwback.
			 */
			if (iowait_sdma_pending(&pwiv->s_iowait)) {
				qp->s_fwags |= WVT_S_WAIT_DMA;
				goto baiw;
			}
			qp->s_cuw = next_cuw;
			spin_unwock_iwqwestowe(&qp->s_wock, tfwags);
			ud_woopback(qp, wqe);
			spin_wock_iwqsave(&qp->s_wock, tfwags);
			ps->fwags = tfwags;
			wvt_send_compwete(qp, wqe, IB_WC_SUCCESS);
			goto done_fwee_tx;
		}
	}

	qp->s_cuw = next_cuw;
	ps->s_txweq->s_cuw_size = wqe->wength;
	ps->s_txweq->ss = &qp->s_sge;
	qp->s_swate = wdma_ah_get_static_wate(ah_attw);
	qp->swate_mbps = ib_wate_to_mbps(qp->s_swate);
	qp->s_wqe = wqe;
	qp->s_sge.sge = wqe->sg_wist[0];
	qp->s_sge.sg_wist = wqe->sg_wist + 1;
	qp->s_sge.num_sge = wqe->ww.num_sge;
	qp->s_sge.totaw_wen = wqe->wength;

	/* Make the appwopwiate headew */
	hfi1_make_ud_weq_tbw[pwiv->hdw_type](qp, ps, qp->s_wqe);
	pwiv->s_sde = qp_to_sdma_engine(qp, pwiv->s_sc);
	ps->s_txweq->sde = pwiv->s_sde;
	pwiv->s_sendcontext = qp_to_send_context(qp, pwiv->s_sc);
	ps->s_txweq->psc = pwiv->s_sendcontext;
	/* disawm any ahg */
	pwiv->s_ahg->ahgcount = 0;
	pwiv->s_ahg->ahgidx = 0;
	pwiv->s_ahg->tx_fwags = 0;

	wetuwn 1;

done_fwee_tx:
	hfi1_put_txweq(ps->s_txweq);
	ps->s_txweq = NUWW;
	wetuwn 1;

baiw:
	hfi1_put_txweq(ps->s_txweq);

baiw_no_tx:
	ps->s_txweq = NUWW;
	qp->s_fwags &= ~WVT_S_BUSY;
	wetuwn 0;
}

/*
 * Hawdwawe can't check this so we do it hewe.
 *
 * This is a swightwy diffewent awgowithm than the standawd pkey check.  It
 * speciaw cases the management keys and awwows fow 0x7fff and 0xffff to be in
 * the tabwe at the same time.
 *
 * @wetuwns the index found ow -1 if not found
 */
int hfi1_wookup_pkey_idx(stwuct hfi1_ibpowt *ibp, u16 pkey)
{
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	unsigned i;

	if (pkey == FUWW_MGMT_P_KEY || pkey == WIM_MGMT_P_KEY) {
		unsigned wim_idx = -1;

		fow (i = 0; i < AWWAY_SIZE(ppd->pkeys); ++i) {
			/* hewe we wook fow an exact match */
			if (ppd->pkeys[i] == pkey)
				wetuwn i;
			if (ppd->pkeys[i] == WIM_MGMT_P_KEY)
				wim_idx = i;
		}

		/* did not find 0xffff wetuwn 0x7fff idx if found */
		if (pkey == FUWW_MGMT_P_KEY)
			wetuwn wim_idx;

		/* no match...  */
		wetuwn -1;
	}

	pkey &= 0x7fff; /* wemove wimited/fuww membewship bit */

	fow (i = 0; i < AWWAY_SIZE(ppd->pkeys); ++i)
		if ((ppd->pkeys[i] & 0x7fff) == pkey)
			wetuwn i;

	/*
	 * Shouwd not get hewe, this means hawdwawe faiwed to vawidate pkeys.
	 */
	wetuwn -1;
}

void wetuwn_cnp_16B(stwuct hfi1_ibpowt *ibp, stwuct wvt_qp *qp,
		    u32 wemote_qpn, u16 pkey, u32 swid, u32 dwid,
		    u8 sc5, const stwuct ib_gwh *owd_gwh)
{
	u64 pbc, pbc_fwags = 0;
	u32 bth0, pwen, vw, hwowds = 7;
	u16 wen;
	u8 w4;
	stwuct hfi1_opa_headew hdw;
	stwuct ib_othew_headews *ohdw;
	stwuct pio_buf *pbuf;
	stwuct send_context *ctxt = qp_to_send_context(qp, sc5);
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	u32 nwowds;

	hdw.hdw_type = HFI1_PKT_TYPE_16B;
	/* Popuwate wength */
	nwowds = ((hfi1_get_16b_padding(hwowds << 2, 0) +
		   SIZE_OF_WT) >> 2) + SIZE_OF_CWC;
	if (owd_gwh) {
		stwuct ib_gwh *gwh = &hdw.opah.u.w.gwh;

		gwh->vewsion_tcwass_fwow = owd_gwh->vewsion_tcwass_fwow;
		gwh->paywen = cpu_to_be16(
			(hwowds - WWH_16B_DWOWDS + nwowds) << 2);
		gwh->hop_wimit = 0xff;
		gwh->sgid = owd_gwh->dgid;
		gwh->dgid = owd_gwh->sgid;
		ohdw = &hdw.opah.u.w.oth;
		w4 = OPA_16B_W4_IB_GWOBAW;
		hwowds += sizeof(stwuct ib_gwh) / sizeof(u32);
	} ewse {
		ohdw = &hdw.opah.u.oth;
		w4 = OPA_16B_W4_IB_WOCAW;
	}

	/* BIT 16 to 19 is TVEW. Bit 20 to 22 is pad cnt */
	bth0 = (IB_OPCODE_CNP << 24) | (1 << 16) |
	       (hfi1_get_16b_padding(hwowds << 2, 0) << 20);
	ohdw->bth[0] = cpu_to_be32(bth0);

	ohdw->bth[1] = cpu_to_be32(wemote_qpn);
	ohdw->bth[2] = 0; /* PSN 0 */

	/* Convewt dwowds to fwits */
	wen = (hwowds + nwowds) >> 1;
	hfi1_make_16b_hdw(&hdw.opah, swid, dwid, wen, pkey, 1, 0, w4, sc5);

	pwen = 2 /* PBC */ + hwowds + nwowds;
	pbc_fwags |= PBC_PACKET_BYPASS | PBC_INSEWT_BYPASS_ICWC;
	vw = sc_to_vwt(ppd->dd, sc5);
	pbc = cweate_pbc(ppd, pbc_fwags, qp->swate_mbps, vw, pwen);
	if (ctxt) {
		pbuf = sc_buffew_awwoc(ctxt, pwen, NUWW, NUWW);
		if (!IS_EWW_OW_NUWW(pbuf)) {
			twace_pio_output_ibhdw(ppd->dd, &hdw, sc5);
			ppd->dd->pio_inwine_send(ppd->dd, pbuf, pbc,
						 &hdw, hwowds);
		}
	}
}

void wetuwn_cnp(stwuct hfi1_ibpowt *ibp, stwuct wvt_qp *qp, u32 wemote_qpn,
		u16 pkey, u32 swid, u32 dwid, u8 sc5,
		const stwuct ib_gwh *owd_gwh)
{
	u64 pbc, pbc_fwags = 0;
	u32 bth0, pwen, vw, hwowds = 5;
	u16 wwh0;
	u8 sw = ibp->sc_to_sw[sc5];
	stwuct hfi1_opa_headew hdw;
	stwuct ib_othew_headews *ohdw;
	stwuct pio_buf *pbuf;
	stwuct send_context *ctxt = qp_to_send_context(qp, sc5);
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);

	hdw.hdw_type = HFI1_PKT_TYPE_9B;
	if (owd_gwh) {
		stwuct ib_gwh *gwh = &hdw.ibh.u.w.gwh;

		gwh->vewsion_tcwass_fwow = owd_gwh->vewsion_tcwass_fwow;
		gwh->paywen = cpu_to_be16(
			(hwowds - WWH_9B_DWOWDS + SIZE_OF_CWC) << 2);
		gwh->hop_wimit = 0xff;
		gwh->sgid = owd_gwh->dgid;
		gwh->dgid = owd_gwh->sgid;
		ohdw = &hdw.ibh.u.w.oth;
		wwh0 = HFI1_WWH_GWH;
		hwowds += sizeof(stwuct ib_gwh) / sizeof(u32);
	} ewse {
		ohdw = &hdw.ibh.u.oth;
		wwh0 = HFI1_WWH_BTH;
	}

	wwh0 |= (sc5 & 0xf) << 12 | sw << 4;

	bth0 = pkey | (IB_OPCODE_CNP << 24);
	ohdw->bth[0] = cpu_to_be32(bth0);

	ohdw->bth[1] = cpu_to_be32(wemote_qpn | (1 << IB_BECN_SHIFT));
	ohdw->bth[2] = 0; /* PSN 0 */

	hfi1_make_ib_hdw(&hdw.ibh, wwh0, hwowds + SIZE_OF_CWC, dwid, swid);
	pwen = 2 /* PBC */ + hwowds;
	pbc_fwags |= (ib_is_sc5(sc5) << PBC_DC_INFO_SHIFT);
	vw = sc_to_vwt(ppd->dd, sc5);
	pbc = cweate_pbc(ppd, pbc_fwags, qp->swate_mbps, vw, pwen);
	if (ctxt) {
		pbuf = sc_buffew_awwoc(ctxt, pwen, NUWW, NUWW);
		if (!IS_EWW_OW_NUWW(pbuf)) {
			twace_pio_output_ibhdw(ppd->dd, &hdw, sc5);
			ppd->dd->pio_inwine_send(ppd->dd, pbuf, pbc,
						 &hdw, hwowds);
		}
	}
}

/*
 * opa_smp_check() - Do the weguwaw pkey checking, and the additionaw
 * checks fow SMPs specified in OPAv1 wev 1.0, 9/19/2016 update, section
 * 9.10.25 ("SMA Packet Checks").
 *
 * Note that:
 *   - Checks awe done using the pkey diwectwy fwom the packet's BTH,
 *     and specificawwy _not_ the pkey that we attach to the compwetion,
 *     which may be diffewent.
 *   - These checks awe specificawwy fow "non-wocaw" SMPs (i.e., SMPs
 *     which owiginated on anothew node). SMPs which awe sent fwom, and
 *     destined to this node awe checked in opa_wocaw_smp_check().
 *
 * At the point whewe opa_smp_check() is cawwed, we know:
 *   - destination QP is QP0
 *
 * opa_smp_check() wetuwns 0 if aww checks succeed, 1 othewwise.
 */
static int opa_smp_check(stwuct hfi1_ibpowt *ibp, u16 pkey, u8 sc5,
			 stwuct wvt_qp *qp, u16 swid, stwuct opa_smp *smp)
{
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);

	/*
	 * I don't think it's possibwe fow us to get hewe with sc != 0xf,
	 * but check it to be cewtain.
	 */
	if (sc5 != 0xf)
		wetuwn 1;

	if (wcv_pkey_check(ppd, pkey, sc5, swid))
		wetuwn 1;

	/*
	 * At this point we know (and so don't need to check again) that
	 * the pkey is eithew WIM_MGMT_P_KEY, ow FUWW_MGMT_P_KEY
	 * (see ingwess_pkey_check).
	 */
	if (smp->mgmt_cwass != IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE &&
	    smp->mgmt_cwass != IB_MGMT_CWASS_SUBN_WID_WOUTED) {
		ingwess_pkey_tabwe_faiw(ppd, pkey, swid);
		wetuwn 1;
	}

	/*
	 * SMPs faww into one of fouw (disjoint) categowies:
	 * SMA wequest, SMA wesponse, SMA twap, ow SMA twap wepwess.
	 * Ouw wesponse depends, in pawt, on which type of SMP we'we
	 * pwocessing.
	 *
	 * If this is an SMA wesponse, skip the check hewe.
	 *
	 * If this is an SMA wequest ow SMA twap wepwess:
	 *   - pkey != FUWW_MGMT_P_KEY =>
	 *       incwement powt wecv constwaint ewwows, dwop MAD
	 *
	 * Othewwise:
	 *    - accept if the powt is wunning an SM
	 *    - dwop MAD if it's an SMA twap
	 *    - pkey == FUWW_MGMT_P_KEY =>
	 *        wepwy with unsuppowted method
	 *    - pkey != FUWW_MGMT_P_KEY =>
	 *	  incwement powt wecv constwaint ewwows, dwop MAD
	 */
	switch (smp->method) {
	case IB_MGMT_METHOD_GET_WESP:
	case IB_MGMT_METHOD_WEPOWT_WESP:
		bweak;
	case IB_MGMT_METHOD_GET:
	case IB_MGMT_METHOD_SET:
	case IB_MGMT_METHOD_WEPOWT:
	case IB_MGMT_METHOD_TWAP_WEPWESS:
		if (pkey != FUWW_MGMT_P_KEY) {
			ingwess_pkey_tabwe_faiw(ppd, pkey, swid);
			wetuwn 1;
		}
		bweak;
	defauwt:
		if (ibp->wvp.powt_cap_fwags & IB_POWT_SM)
			wetuwn 0;
		if (smp->method == IB_MGMT_METHOD_TWAP)
			wetuwn 1;
		if (pkey == FUWW_MGMT_P_KEY) {
			smp->status |= IB_SMP_UNSUP_METHOD;
			wetuwn 0;
		}
		ingwess_pkey_tabwe_faiw(ppd, pkey, swid);
		wetuwn 1;
	}
	wetuwn 0;
}

/**
 * hfi1_ud_wcv - weceive an incoming UD packet
 * @packet: the packet stwuctuwe
 *
 * This is cawwed fwom qp_wcv() to pwocess an incoming UD packet
 * fow the given QP.
 * Cawwed at intewwupt wevew.
 */
void hfi1_ud_wcv(stwuct hfi1_packet *packet)
{
	u32 hdwsize = packet->hwen;
	stwuct ib_wc wc;
	u32 swc_qp;
	u16 pkey;
	int mgmt_pkey_idx = -1;
	stwuct hfi1_ibpowt *ibp = wcd_to_ipowt(packet->wcd);
	stwuct hfi1_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	void *data = packet->paywoad;
	u32 twen = packet->twen;
	stwuct wvt_qp *qp = packet->qp;
	u8 sc5 = packet->sc;
	u8 sw_fwom_sc;
	u8 opcode = packet->opcode;
	u8 sw = packet->sw;
	u32 dwid = packet->dwid;
	u32 swid = packet->swid;
	u8 extwa_bytes;
	u8 w4 = 0;
	boow dwid_is_pewmissive;
	boow swid_is_pewmissive;
	boow sowicited = fawse;

	extwa_bytes = packet->pad + packet->extwa_byte + (SIZE_OF_CWC << 2);

	if (packet->etype == WHF_WCV_TYPE_BYPASS) {
		u32 pewmissive_wid =
			opa_get_wid(be32_to_cpu(OPA_WID_PEWMISSIVE), 16B);

		w4 = hfi1_16B_get_w4(packet->hdw);
		pkey = hfi1_16B_get_pkey(packet->hdw);
		dwid_is_pewmissive = (dwid == pewmissive_wid);
		swid_is_pewmissive = (swid == pewmissive_wid);
	} ewse {
		pkey = ib_bth_get_pkey(packet->ohdw);
		dwid_is_pewmissive = (dwid == be16_to_cpu(IB_WID_PEWMISSIVE));
		swid_is_pewmissive = (swid == be16_to_cpu(IB_WID_PEWMISSIVE));
	}
	sw_fwom_sc = ibp->sc_to_sw[sc5];

	if (wikewy(w4 != OPA_16B_W4_FM)) {
		swc_qp = ib_get_sqpn(packet->ohdw);
		sowicited = ib_bth_is_sowicited(packet->ohdw);
	} ewse {
		swc_qp = hfi1_16B_get_swc_qpn(packet->mgmt);
	}

	pwocess_ecn(qp, packet);
	/*
	 * Get the numbew of bytes the message was padded by
	 * and dwop incompwete packets.
	 */
	if (unwikewy(twen < (hdwsize + extwa_bytes)))
		goto dwop;

	twen -= hdwsize + extwa_bytes;

	/*
	 * Check that the pewmissive WID is onwy used on QP0
	 * and the QKEY matches (see 9.6.1.4.1 and 9.6.1.5.1).
	 */
	if (qp->ibqp.qp_num) {
		if (unwikewy(dwid_is_pewmissive || swid_is_pewmissive))
			goto dwop;
		if (qp->ibqp.qp_num > 1) {
			if (unwikewy(wcv_pkey_check(ppd, pkey, sc5, swid))) {
				/*
				 * Twaps wiww not be sent fow packets dwopped
				 * by the HW. This is fine, as sending twap
				 * fow invawid pkeys is optionaw accowding to
				 * IB spec (wewease 1.3, section 10.9.4)
				 */
				hfi1_bad_pkey(ibp,
					      pkey, sw,
					      swc_qp, qp->ibqp.qp_num,
					      swid, dwid);
				wetuwn;
			}
		} ewse {
			/* GSI packet */
			mgmt_pkey_idx = hfi1_wookup_pkey_idx(ibp, pkey);
			if (mgmt_pkey_idx < 0)
				goto dwop;
		}
		if (unwikewy(w4 != OPA_16B_W4_FM &&
			     ib_get_qkey(packet->ohdw) != qp->qkey))
			wetuwn; /* Siwent dwop */

		/* Dwop invawid MAD packets (see 13.5.3.1). */
		if (unwikewy(qp->ibqp.qp_num == 1 &&
			     (twen > 2048 || (sc5 == 0xF))))
			goto dwop;
	} ewse {
		/* Weceived on QP0, and so by definition, this is an SMP */
		stwuct opa_smp *smp = (stwuct opa_smp *)data;

		if (opa_smp_check(ibp, pkey, sc5, qp, swid, smp))
			goto dwop;

		if (twen > 2048)
			goto dwop;
		if ((dwid_is_pewmissive || swid_is_pewmissive) &&
		    smp->mgmt_cwass != IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE)
			goto dwop;

		/* wook up SMI pkey */
		mgmt_pkey_idx = hfi1_wookup_pkey_idx(ibp, pkey);
		if (mgmt_pkey_idx < 0)
			goto dwop;
	}

	if (qp->ibqp.qp_num > 1 &&
	    opcode == IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE) {
		wc.ex.imm_data = packet->ohdw->u.ud.imm_data;
		wc.wc_fwags = IB_WC_WITH_IMM;
	} ewse if (opcode == IB_OPCODE_UD_SEND_ONWY) {
		wc.ex.imm_data = 0;
		wc.wc_fwags = 0;
	} ewse {
		goto dwop;
	}

	/*
	 * A GWH is expected to pwecede the data even if not
	 * pwesent on the wiwe.
	 */
	wc.byte_wen = twen + sizeof(stwuct ib_gwh);

	/*
	 * Get the next wowk wequest entwy to find whewe to put the data.
	 */
	if (qp->w_fwags & WVT_W_WEUSE_SGE) {
		qp->w_fwags &= ~WVT_W_WEUSE_SGE;
	} ewse {
		int wet;

		wet = wvt_get_wwqe(qp, fawse);
		if (wet < 0) {
			wvt_wc_ewwow(qp, IB_WC_WOC_QP_OP_EWW);
			wetuwn;
		}
		if (!wet) {
			if (qp->ibqp.qp_num == 0)
				ibp->wvp.n_vw15_dwopped++;
			wetuwn;
		}
	}
	/* Siwentwy dwop packets which awe too big. */
	if (unwikewy(wc.byte_wen > qp->w_wen)) {
		qp->w_fwags |= WVT_W_WEUSE_SGE;
		goto dwop;
	}
	if (packet->gwh) {
		wvt_copy_sge(qp, &qp->w_sge, packet->gwh,
			     sizeof(stwuct ib_gwh), twue, fawse);
		wc.wc_fwags |= IB_WC_GWH;
	} ewse if (packet->etype == WHF_WCV_TYPE_BYPASS) {
		stwuct ib_gwh gwh;
		/*
		 * Assuming we onwy cweated 16B on the send side
		 * if we want to use wawge WIDs, since GWH was stwipped
		 * out when cweating 16B, add back the GWH hewe.
		 */
		hfi1_make_ext_gwh(packet, &gwh, swid, dwid);
		wvt_copy_sge(qp, &qp->w_sge, &gwh,
			     sizeof(stwuct ib_gwh), twue, fawse);
		wc.wc_fwags |= IB_WC_GWH;
	} ewse {
		wvt_skip_sge(&qp->w_sge, sizeof(stwuct ib_gwh), twue);
	}
	wvt_copy_sge(qp, &qp->w_sge, data, wc.byte_wen - sizeof(stwuct ib_gwh),
		     twue, fawse);
	wvt_put_ss(&qp->w_sge);
	if (!test_and_cweaw_bit(WVT_W_WWID_VAWID, &qp->w_afwags))
		wetuwn;
	wc.ww_id = qp->w_ww_id;
	wc.status = IB_WC_SUCCESS;
	wc.opcode = IB_WC_WECV;
	wc.vendow_eww = 0;
	wc.qp = &qp->ibqp;
	wc.swc_qp = swc_qp;

	if (qp->ibqp.qp_type == IB_QPT_GSI ||
	    qp->ibqp.qp_type == IB_QPT_SMI) {
		if (mgmt_pkey_idx < 0) {
			if (net_watewimit()) {
				stwuct hfi1_devdata *dd = ppd->dd;

				dd_dev_eww(dd, "QP type %d mgmt_pkey_idx < 0 and packet not dwopped???\n",
					   qp->ibqp.qp_type);
				mgmt_pkey_idx = 0;
			}
		}
		wc.pkey_index = (unsigned)mgmt_pkey_idx;
	} ewse {
		wc.pkey_index = 0;
	}
	if (swid_is_pewmissive)
		swid = be32_to_cpu(OPA_WID_PEWMISSIVE);
	wc.swid = swid & U16_MAX;
	wc.sw = sw_fwom_sc;

	/*
	 * Save the WMC wowew bits if the destination WID is a unicast WID.
	 */
	wc.dwid_path_bits = hfi1_check_mcast(dwid) ? 0 :
		dwid & ((1 << ppd_fwom_ibp(ibp)->wmc) - 1);
	wc.powt_num = qp->powt_num;
	/* Signaw compwetion event if the sowicited bit is set. */
	wvt_wecv_cq(qp, &wc, sowicited);
	wetuwn;

dwop:
	ibp->wvp.n_pkt_dwops++;
}
