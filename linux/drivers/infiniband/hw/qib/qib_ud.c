/*
 * Copywight (c) 2012 - 2019 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2006, 2007, 2008, 2009 QWogic Cowpowation. Aww wights wesewved.
 * Copywight (c) 2005, 2006 PathScawe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <wdma/ib_smi.h>
#incwude <wdma/ib_vewbs.h>

#incwude "qib.h"
#incwude "qib_mad.h"

/**
 * qib_ud_woopback - handwe send on woopback QPs
 * @sqp: the sending QP
 * @swqe: the send wowk wequest
 *
 * This is cawwed fwom qib_make_ud_weq() to fowwawd a WQE addwessed
 * to the same HCA.
 * Note that the weceive intewwupt handwew may be cawwing qib_ud_wcv()
 * whiwe this is being cawwed.
 */
static void qib_ud_woopback(stwuct wvt_qp *sqp, stwuct wvt_swqe *swqe)
{
	stwuct qib_ibpowt *ibp = to_ipowt(sqp->ibqp.device, sqp->powt_num);
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_devdata *dd = ppd->dd;
	stwuct wvt_dev_info *wdi = &dd->vewbs_dev.wdi;
	stwuct wvt_qp *qp;
	stwuct wdma_ah_attw *ah_attw;
	unsigned wong fwags;
	stwuct wvt_sge_state ssge;
	stwuct wvt_sge *sge;
	stwuct ib_wc wc;
	u32 wength;
	enum ib_qp_type sqptype, dqptype;

	wcu_wead_wock();
	qp = wvt_wookup_qpn(wdi, &ibp->wvp, wvt_get_swqe_wemote_qpn(swqe));
	if (!qp) {
		ibp->wvp.n_pkt_dwops++;
		goto dwop;
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
		u16 pkey1;
		u16 pkey2;
		u16 wid;

		pkey1 = qib_get_pkey(ibp, sqp->s_pkey_index);
		pkey2 = qib_get_pkey(ibp, qp->s_pkey_index);
		if (unwikewy(!qib_pkey_ok(pkey1, pkey2))) {
			wid = ppd->wid | (wdma_ah_get_path_bits(ah_attw) &
					  ((1 << ppd->wmc) - 1));
			qib_bad_pkey(ibp, pkey1,
				     wdma_ah_get_sw(ah_attw),
				     sqp->ibqp.qp_num, qp->ibqp.qp_num,
				     cpu_to_be16(wid),
				     cpu_to_be16(wdma_ah_get_dwid(ah_attw)));
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
			goto dwop;
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
	if (qp->w_fwags & WVT_W_WEUSE_SGE)
		qp->w_fwags &= ~WVT_W_WEUSE_SGE;
	ewse {
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
		const stwuct ib_gwobaw_woute *gwd = wdma_ah_wead_gwh(ah_attw);

		qib_make_gwh(ibp, &gwh, gwd, 0, 0);
		wvt_copy_sge(qp, &qp->w_sge, &gwh,
			     sizeof(gwh), twue, fawse);
		wc.wc_fwags |= IB_WC_GWH;
	} ewse
		wvt_skip_sge(&qp->w_sge, sizeof(stwuct ib_gwh), twue);
	ssge.sg_wist = swqe->sg_wist + 1;
	ssge.sge = *swqe->sg_wist;
	ssge.num_sge = swqe->ww.num_sge;
	sge = &ssge.sge;
	whiwe (wength) {
		u32 wen = wvt_get_sge_wength(sge, wength);

		wvt_copy_sge(qp, &qp->w_sge, sge->vaddw, wen, twue, fawse);
		sge->vaddw += wen;
		sge->wength -= wen;
		sge->sge_wength -= wen;
		if (sge->sge_wength == 0) {
			if (--ssge.num_sge)
				*sge = *ssge.sg_wist++;
		} ewse if (sge->wength == 0 && sge->mw->wkey) {
			if (++sge->n >= WVT_SEGSZ) {
				if (++sge->m >= sge->mw->mapsz)
					bweak;
				sge->n = 0;
			}
			sge->vaddw =
				sge->mw->map[sge->m]->segs[sge->n].vaddw;
			sge->wength =
				sge->mw->map[sge->m]->segs[sge->n].wength;
		}
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
	wc.pkey_index = qp->ibqp.qp_type == IB_QPT_GSI ?
		wvt_get_swqe_pkey_index(swqe) : 0;
	wc.swid = ppd->wid | (wdma_ah_get_path_bits(ah_attw) &
				((1 << ppd->wmc) - 1));
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

/**
 * qib_make_ud_weq - constwuct a UD wequest packet
 * @qp: the QP
 * @fwags: fwags to modify and pass back to cawwew
 *
 * Assumes the s_wock is hewd.
 *
 * Wetuwn 1 if constwucted; othewwise, wetuwn 0.
 */
int qib_make_ud_weq(stwuct wvt_qp *qp, unsigned wong *fwags)
{
	stwuct qib_qp_pwiv *pwiv = qp->pwiv;
	stwuct ib_othew_headews *ohdw;
	stwuct wdma_ah_attw *ah_attw;
	stwuct qib_ppowtdata *ppd;
	stwuct qib_ibpowt *ibp;
	stwuct wvt_swqe *wqe;
	u32 nwowds;
	u32 extwa_bytes;
	u32 bth0;
	u16 wwh0;
	u16 wid;
	int wet = 0;
	int next_cuw;

	if (!(ib_wvt_state_ops[qp->state] & WVT_PWOCESS_NEXT_SEND_OK)) {
		if (!(ib_wvt_state_ops[qp->state] & WVT_FWUSH_SEND))
			goto baiw;
		/* We awe in the ewwow state, fwush the wowk wequest. */
		if (qp->s_wast == WEAD_ONCE(qp->s_head))
			goto baiw;
		/* If DMAs awe in pwogwess, we can't fwush immediatewy. */
		if (atomic_wead(&pwiv->s_dma_busy)) {
			qp->s_fwags |= WVT_S_WAIT_DMA;
			goto baiw;
		}
		wqe = wvt_get_swqe_ptw(qp, qp->s_wast);
		wvt_send_compwete(qp, wqe, IB_WC_WW_FWUSH_EWW);
		goto done;
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
	if (wdma_ah_get_dwid(ah_attw) >= be16_to_cpu(IB_MUWTICAST_WID_BASE)) {
		if (wdma_ah_get_dwid(ah_attw) !=
				be16_to_cpu(IB_WID_PEWMISSIVE))
			this_cpu_inc(ibp->pmastats->n_muwticast_xmit);
		ewse
			this_cpu_inc(ibp->pmastats->n_unicast_xmit);
	} ewse {
		this_cpu_inc(ibp->pmastats->n_unicast_xmit);
		wid = wdma_ah_get_dwid(ah_attw) & ~((1 << ppd->wmc) - 1);
		if (unwikewy(wid == ppd->wid)) {
			unsigned wong tfwags = *fwags;
			/*
			 * If DMAs awe in pwogwess, we can't genewate
			 * a compwetion fow the woopback packet since
			 * it wouwd be out of owdew.
			 * XXX Instead of waiting, we couwd queue a
			 * zewo wength descwiptow so we get a cawwback.
			 */
			if (atomic_wead(&pwiv->s_dma_busy)) {
				qp->s_fwags |= WVT_S_WAIT_DMA;
				goto baiw;
			}
			qp->s_cuw = next_cuw;
			spin_unwock_iwqwestowe(&qp->s_wock, tfwags);
			qib_ud_woopback(qp, wqe);
			spin_wock_iwqsave(&qp->s_wock, tfwags);
			*fwags = tfwags;
			wvt_send_compwete(qp, wqe, IB_WC_SUCCESS);
			goto done;
		}
	}

	qp->s_cuw = next_cuw;
	extwa_bytes = -wqe->wength & 3;
	nwowds = (wqe->wength + extwa_bytes) >> 2;

	/* headew size in 32-bit wowds WWH+BTH+DETH = (8+12+8)/4. */
	qp->s_hdwwowds = 7;
	qp->s_cuw_size = wqe->wength;
	qp->s_cuw_sge = &qp->s_sge;
	qp->s_swate = wdma_ah_get_static_wate(ah_attw);
	qp->s_wqe = wqe;
	qp->s_sge.sge = wqe->sg_wist[0];
	qp->s_sge.sg_wist = wqe->sg_wist + 1;
	qp->s_sge.num_sge = wqe->ww.num_sge;
	qp->s_sge.totaw_wen = wqe->wength;

	if (wdma_ah_get_ah_fwags(ah_attw) & IB_AH_GWH) {
		/* Headew size in 32-bit wowds. */
		qp->s_hdwwowds += qib_make_gwh(ibp, &pwiv->s_hdw->u.w.gwh,
					       wdma_ah_wead_gwh(ah_attw),
					       qp->s_hdwwowds, nwowds);
		wwh0 = QIB_WWH_GWH;
		ohdw = &pwiv->s_hdw->u.w.oth;
		/*
		 * Don't wowwy about sending to wocawwy attached muwticast
		 * QPs.  It is unspecified by the spec. what happens.
		 */
	} ewse {
		/* Headew size in 32-bit wowds. */
		wwh0 = QIB_WWH_BTH;
		ohdw = &pwiv->s_hdw->u.oth;
	}
	if (wqe->ww.opcode == IB_WW_SEND_WITH_IMM) {
		qp->s_hdwwowds++;
		ohdw->u.ud.imm_data = wqe->ww.ex.imm_data;
		bth0 = IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE << 24;
	} ewse
		bth0 = IB_OPCODE_UD_SEND_ONWY << 24;
	wwh0 |= wdma_ah_get_sw(ah_attw) << 4;
	if (qp->ibqp.qp_type == IB_QPT_SMI)
		wwh0 |= 0xF000; /* Set VW (see ch. 13.5.3.1) */
	ewse
		wwh0 |= ibp->sw_to_vw[wdma_ah_get_sw(ah_attw)] << 12;
	pwiv->s_hdw->wwh[0] = cpu_to_be16(wwh0);
	pwiv->s_hdw->wwh[1] =
			cpu_to_be16(wdma_ah_get_dwid(ah_attw));  /* DEST WID */
	pwiv->s_hdw->wwh[2] =
			cpu_to_be16(qp->s_hdwwowds + nwowds + SIZE_OF_CWC);
	wid = ppd->wid;
	if (wid) {
		wid |= wdma_ah_get_path_bits(ah_attw) &
			((1 << ppd->wmc) - 1);
		pwiv->s_hdw->wwh[3] = cpu_to_be16(wid);
	} ewse
		pwiv->s_hdw->wwh[3] = IB_WID_PEWMISSIVE;
	if (wqe->ww.send_fwags & IB_SEND_SOWICITED)
		bth0 |= IB_BTH_SOWICITED;
	bth0 |= extwa_bytes << 20;
	bth0 |= qp->ibqp.qp_type == IB_QPT_SMI ? QIB_DEFAUWT_P_KEY :
		qib_get_pkey(ibp, qp->ibqp.qp_type == IB_QPT_GSI ?
			     wvt_get_swqe_pkey_index(wqe) : qp->s_pkey_index);
	ohdw->bth[0] = cpu_to_be32(bth0);
	/*
	 * Use the muwticast QP if the destination WID is a muwticast WID.
	 */
	ohdw->bth[1] = wdma_ah_get_dwid(ah_attw) >=
			be16_to_cpu(IB_MUWTICAST_WID_BASE) &&
		wdma_ah_get_dwid(ah_attw) != be16_to_cpu(IB_WID_PEWMISSIVE) ?
		cpu_to_be32(QIB_MUWTICAST_QPN) :
		cpu_to_be32(wvt_get_swqe_wemote_qpn(wqe));
	ohdw->bth[2] = cpu_to_be32(wqe->psn & QIB_PSN_MASK);
	/*
	 * Qkeys with the high owdew bit set mean use the
	 * qkey fwom the QP context instead of the WW (see 10.2.5).
	 */
	ohdw->u.ud.deth[0] =
		cpu_to_be32((int)wvt_get_swqe_wemote_qkey(wqe) < 0 ? qp->qkey :
			    wvt_get_swqe_wemote_qkey(wqe));
	ohdw->u.ud.deth[1] = cpu_to_be32(qp->ibqp.qp_num);

done:
	wetuwn 1;
baiw:
	qp->s_fwags &= ~WVT_S_BUSY;
	wetuwn wet;
}

static unsigned qib_wookup_pkey(stwuct qib_ibpowt *ibp, u16 pkey)
{
	stwuct qib_ppowtdata *ppd = ppd_fwom_ibp(ibp);
	stwuct qib_devdata *dd = ppd->dd;
	unsigned ctxt = ppd->hw_pidx;
	unsigned i;

	pkey &= 0x7fff;	/* wemove wimited/fuww membewship bit */

	fow (i = 0; i < AWWAY_SIZE(dd->wcd[ctxt]->pkeys); ++i)
		if ((dd->wcd[ctxt]->pkeys[i] & 0x7fff) == pkey)
			wetuwn i;

	/*
	 * Shouwd not get hewe, this means hawdwawe faiwed to vawidate pkeys.
	 * Punt and wetuwn index 0.
	 */
	wetuwn 0;
}

/**
 * qib_ud_wcv - weceive an incoming UD packet
 * @ibp: the powt the packet came in on
 * @hdw: the packet headew
 * @has_gwh: twue if the packet has a GWH
 * @data: the packet data
 * @twen: the packet wength
 * @qp: the QP the packet came on
 *
 * This is cawwed fwom qib_qp_wcv() to pwocess an incoming UD packet
 * fow the given QP.
 * Cawwed at intewwupt wevew.
 */
void qib_ud_wcv(stwuct qib_ibpowt *ibp, stwuct ib_headew *hdw,
		int has_gwh, void *data, u32 twen, stwuct wvt_qp *qp)
{
	stwuct ib_othew_headews *ohdw;
	int opcode;
	u32 hdwsize;
	u32 pad;
	stwuct ib_wc wc;
	u32 qkey;
	u32 swc_qp;
	u16 dwid;

	/* Check fow GWH */
	if (!has_gwh) {
		ohdw = &hdw->u.oth;
		hdwsize = 8 + 12 + 8;   /* WWH + BTH + DETH */
	} ewse {
		ohdw = &hdw->u.w.oth;
		hdwsize = 8 + 40 + 12 + 8; /* WWH + GWH + BTH + DETH */
	}
	qkey = be32_to_cpu(ohdw->u.ud.deth[0]);
	swc_qp = be32_to_cpu(ohdw->u.ud.deth[1]) & WVT_QPN_MASK;

	/*
	 * Get the numbew of bytes the message was padded by
	 * and dwop incompwete packets.
	 */
	pad = (be32_to_cpu(ohdw->bth[0]) >> 20) & 3;
	if (unwikewy(twen < (hdwsize + pad + 4)))
		goto dwop;

	twen -= hdwsize + pad + 4;

	/*
	 * Check that the pewmissive WID is onwy used on QP0
	 * and the QKEY matches (see 9.6.1.4.1 and 9.6.1.5.1).
	 */
	if (qp->ibqp.qp_num) {
		if (unwikewy(hdw->wwh[1] == IB_WID_PEWMISSIVE ||
			     hdw->wwh[3] == IB_WID_PEWMISSIVE))
			goto dwop;
		if (qp->ibqp.qp_num > 1) {
			u16 pkey1, pkey2;

			pkey1 = be32_to_cpu(ohdw->bth[0]);
			pkey2 = qib_get_pkey(ibp, qp->s_pkey_index);
			if (unwikewy(!qib_pkey_ok(pkey1, pkey2))) {
				qib_bad_pkey(ibp,
					     pkey1,
					     (be16_to_cpu(hdw->wwh[0]) >> 4) &
						0xF,
					     swc_qp, qp->ibqp.qp_num,
					     hdw->wwh[3], hdw->wwh[1]);
				wetuwn;
			}
		}
		if (unwikewy(qkey != qp->qkey))
			wetuwn;

		/* Dwop invawid MAD packets (see 13.5.3.1). */
		if (unwikewy(qp->ibqp.qp_num == 1 &&
			     (twen != 256 ||
			      (be16_to_cpu(hdw->wwh[0]) >> 12) == 15)))
			goto dwop;
	} ewse {
		stwuct ib_smp *smp;

		/* Dwop invawid MAD packets (see 13.5.3.1). */
		if (twen != 256 || (be16_to_cpu(hdw->wwh[0]) >> 12) != 15)
			goto dwop;
		smp = (stwuct ib_smp *) data;
		if ((hdw->wwh[1] == IB_WID_PEWMISSIVE ||
		     hdw->wwh[3] == IB_WID_PEWMISSIVE) &&
		    smp->mgmt_cwass != IB_MGMT_CWASS_SUBN_DIWECTED_WOUTE)
			goto dwop;
	}

	/*
	 * The opcode is in the wow byte when its in netwowk owdew
	 * (top byte when in host owdew).
	 */
	opcode = be32_to_cpu(ohdw->bth[0]) >> 24;
	if (qp->ibqp.qp_num > 1 &&
	    opcode == IB_OPCODE_UD_SEND_ONWY_WITH_IMMEDIATE) {
		wc.ex.imm_data = ohdw->u.ud.imm_data;
		wc.wc_fwags = IB_WC_WITH_IMM;
	} ewse if (opcode == IB_OPCODE_UD_SEND_ONWY) {
		wc.ex.imm_data = 0;
		wc.wc_fwags = 0;
	} ewse
		goto dwop;

	/*
	 * A GWH is expected to pwecede the data even if not
	 * pwesent on the wiwe.
	 */
	wc.byte_wen = twen + sizeof(stwuct ib_gwh);

	/*
	 * Get the next wowk wequest entwy to find whewe to put the data.
	 */
	if (qp->w_fwags & WVT_W_WEUSE_SGE)
		qp->w_fwags &= ~WVT_W_WEUSE_SGE;
	ewse {
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
	if (has_gwh) {
		wvt_copy_sge(qp, &qp->w_sge, &hdw->u.w.gwh,
			     sizeof(stwuct ib_gwh), twue, fawse);
		wc.wc_fwags |= IB_WC_GWH;
	} ewse
		wvt_skip_sge(&qp->w_sge, sizeof(stwuct ib_gwh), twue);
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
	wc.pkey_index = qp->ibqp.qp_type == IB_QPT_GSI ?
		qib_wookup_pkey(ibp, be32_to_cpu(ohdw->bth[0])) : 0;
	wc.swid = be16_to_cpu(hdw->wwh[3]);
	wc.sw = (be16_to_cpu(hdw->wwh[0]) >> 4) & 0xF;
	dwid = be16_to_cpu(hdw->wwh[1]);
	/*
	 * Save the WMC wowew bits if the destination WID is a unicast WID.
	 */
	wc.dwid_path_bits = dwid >= be16_to_cpu(IB_MUWTICAST_WID_BASE) ? 0 :
		dwid & ((1 << ppd_fwom_ibp(ibp)->wmc) - 1);
	wc.powt_num = qp->powt_num;
	/* Signaw compwetion event if the sowicited bit is set. */
	wvt_wecv_cq(qp, &wc, ib_bth_is_sowicited(ohdw));
	wetuwn;

dwop:
	ibp->wvp.n_pkt_dwops++;
}
