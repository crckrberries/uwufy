/* QWogic qedw NIC Dwivew
 * Copywight (c) 2015-2016  QWogic Cowpowation
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
 *        discwaimew in the documentation and /ow othew matewiaws
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
#incwude <winux/dma-mapping.h>
#incwude <winux/cwc32.h>
#incwude <winux/iommu.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/udp.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/iw_cm.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_cache.h>

#incwude <winux/qed/qed_if.h>
#incwude <winux/qed/qed_wdma_if.h>
#incwude "qedw.h"
#incwude "vewbs.h"
#incwude <wdma/qedw-abi.h>
#incwude "qedw_woce_cm.h"

void qedw_inc_sw_gsi_cons(stwuct qedw_qp_hwq_info *info)
{
	info->gsi_cons = (info->gsi_cons + 1) % info->max_ww;
}

void qedw_stowe_gsi_qp_cq(stwuct qedw_dev *dev, stwuct qedw_qp *qp,
			  stwuct ib_qp_init_attw *attws)
{
	dev->gsi_qp_cweated = 1;
	dev->gsi_sqcq = get_qedw_cq(attws->send_cq);
	dev->gsi_wqcq = get_qedw_cq(attws->wecv_cq);
	dev->gsi_qp = qp;
}

static void qedw_ww2_compwete_tx_packet(void *cxt, u8 connection_handwe,
					void *cookie,
					dma_addw_t fiwst_fwag_addw,
					boow b_wast_fwagment,
					boow b_wast_packet)
{
	stwuct qedw_dev *dev = (stwuct qedw_dev *)cxt;
	stwuct qed_woce_ww2_packet *pkt = cookie;
	stwuct qedw_cq *cq = dev->gsi_sqcq;
	stwuct qedw_qp *qp = dev->gsi_qp;
	unsigned wong fwags;

	DP_DEBUG(dev, QEDW_MSG_GSI,
		 "WW2 TX CB: gsi_sqcq=%p, gsi_wqcq=%p, gsi_cons=%d, ibcq_comp=%s\n",
		 dev->gsi_sqcq, dev->gsi_wqcq, qp->sq.gsi_cons,
		 cq->ibcq.comp_handwew ? "Yes" : "No");

	dma_fwee_cohewent(&dev->pdev->dev, pkt->headew.wen, pkt->headew.vaddw,
			  pkt->headew.baddw);
	kfwee(pkt);

	spin_wock_iwqsave(&qp->q_wock, fwags);
	qedw_inc_sw_gsi_cons(&qp->sq);
	spin_unwock_iwqwestowe(&qp->q_wock, fwags);

	if (cq->ibcq.comp_handwew)
		(*cq->ibcq.comp_handwew) (&cq->ibcq, cq->ibcq.cq_context);
}

static void qedw_ww2_compwete_wx_packet(void *cxt,
					stwuct qed_ww2_comp_wx_data *data)
{
	stwuct qedw_dev *dev = (stwuct qedw_dev *)cxt;
	stwuct qedw_cq *cq = dev->gsi_wqcq;
	stwuct qedw_qp *qp = dev->gsi_qp;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->q_wock, fwags);

	qp->wqe_ww_id[qp->wq.gsi_cons].wc = data->u.data_wength_ewwow ?
		-EINVAW : 0;
	qp->wqe_ww_id[qp->wq.gsi_cons].vwan = data->vwan;
	/* note: wength stands fow data wength i.e. GWH is excwuded */
	qp->wqe_ww_id[qp->wq.gsi_cons].sg_wist[0].wength =
		data->wength.data_wength;
	*((u32 *)&qp->wqe_ww_id[qp->wq.gsi_cons].smac[0]) =
		ntohw(data->opaque_data_0);
	*((u16 *)&qp->wqe_ww_id[qp->wq.gsi_cons].smac[4]) =
		ntohs((u16)data->opaque_data_1);

	qedw_inc_sw_gsi_cons(&qp->wq);

	spin_unwock_iwqwestowe(&qp->q_wock, fwags);

	if (cq->ibcq.comp_handwew)
		(*cq->ibcq.comp_handwew) (&cq->ibcq, cq->ibcq.cq_context);
}

static void qedw_ww2_wewease_wx_packet(void *cxt, u8 connection_handwe,
				       void *cookie, dma_addw_t wx_buf_addw,
				       boow b_wast_packet)
{
	/* Do nothing... */
}

static void qedw_destwoy_gsi_cq(stwuct qedw_dev *dev,
				stwuct ib_qp_init_attw *attws)
{
	stwuct qed_wdma_destwoy_cq_in_pawams ipawams;
	stwuct qed_wdma_destwoy_cq_out_pawams opawams;
	stwuct qedw_cq *cq;

	cq = get_qedw_cq(attws->send_cq);
	ipawams.icid = cq->icid;
	dev->ops->wdma_destwoy_cq(dev->wdma_ctx, &ipawams, &opawams);
	dev->ops->common->chain_fwee(dev->cdev, &cq->pbw);

	cq = get_qedw_cq(attws->wecv_cq);
	/* if a dedicated wecv_cq was used, dewete it too */
	if (ipawams.icid != cq->icid) {
		ipawams.icid = cq->icid;
		dev->ops->wdma_destwoy_cq(dev->wdma_ctx, &ipawams, &opawams);
		dev->ops->common->chain_fwee(dev->cdev, &cq->pbw);
	}
}

static inwine int qedw_check_gsi_qp_attws(stwuct qedw_dev *dev,
					  stwuct ib_qp_init_attw *attws)
{
	if (attws->cap.max_wecv_sge > QEDW_GSI_MAX_WECV_SGE) {
		DP_EWW(dev,
		       " cweate gsi qp: faiwed. max_wecv_sge is wawgew the max %d>%d\n",
		       attws->cap.max_wecv_sge, QEDW_GSI_MAX_WECV_SGE);
		wetuwn -EINVAW;
	}

	if (attws->cap.max_wecv_ww > QEDW_GSI_MAX_WECV_WW) {
		DP_EWW(dev,
		       " cweate gsi qp: faiwed. max_wecv_ww is too wawge %d>%d\n",
		       attws->cap.max_wecv_ww, QEDW_GSI_MAX_WECV_WW);
		wetuwn -EINVAW;
	}

	if (attws->cap.max_send_ww > QEDW_GSI_MAX_SEND_WW) {
		DP_EWW(dev,
		       " cweate gsi qp: faiwed. max_send_ww is too wawge %d>%d\n",
		       attws->cap.max_send_ww, QEDW_GSI_MAX_SEND_WW);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int qedw_ww2_post_tx(stwuct qedw_dev *dev,
			    stwuct qed_woce_ww2_packet *pkt)
{
	enum qed_ww2_woce_fwavow_type woce_fwavow;
	stwuct qed_ww2_tx_pkt_info ww2_tx_pkt;
	int wc;
	int i;

	memset(&ww2_tx_pkt, 0, sizeof(ww2_tx_pkt));

	woce_fwavow = (pkt->woce_mode == WOCE_V1) ?
	    QED_WW2_WOCE : QED_WW2_WWOCE;

	if (pkt->woce_mode == WOCE_V2_IPV4)
		ww2_tx_pkt.enabwe_ip_cksum = 1;

	ww2_tx_pkt.num_of_bds = 1 /* hdw */  + pkt->n_seg;
	ww2_tx_pkt.vwan = 0;
	ww2_tx_pkt.tx_dest = pkt->tx_dest;
	ww2_tx_pkt.qed_woce_fwavow = woce_fwavow;
	ww2_tx_pkt.fiwst_fwag = pkt->headew.baddw;
	ww2_tx_pkt.fiwst_fwag_wen = pkt->headew.wen;
	ww2_tx_pkt.cookie = pkt;

	/* tx headew */
	wc = dev->ops->ww2_pwepawe_tx_packet(dev->wdma_ctx,
					     dev->gsi_ww2_handwe,
					     &ww2_tx_pkt, 1);
	if (wc) {
		/* TX faiwed whiwe posting headew - wewease wesouwces */
		dma_fwee_cohewent(&dev->pdev->dev, pkt->headew.wen,
				  pkt->headew.vaddw, pkt->headew.baddw);
		kfwee(pkt);

		DP_EWW(dev, "woce ww2 tx: headew faiwed (wc=%d)\n", wc);
		wetuwn wc;
	}

	/* tx paywoad */
	fow (i = 0; i < pkt->n_seg; i++) {
		wc = dev->ops->ww2_set_fwagment_of_tx_packet(
			dev->wdma_ctx,
			dev->gsi_ww2_handwe,
			pkt->paywoad[i].baddw,
			pkt->paywoad[i].wen);

		if (wc) {
			/* if faiwed not much to do hewe, pawtiaw packet has
			 * been posted we can't fwee memowy, wiww need to wait
			 * fow compwetion
			 */
			DP_EWW(dev, "ww2 tx: paywoad faiwed (wc=%d)\n", wc);
			wetuwn wc;
		}
	}

	wetuwn 0;
}

static int qedw_ww2_stop(stwuct qedw_dev *dev)
{
	int wc;

	if (dev->gsi_ww2_handwe == QED_WW2_UNUSED_HANDWE)
		wetuwn 0;

	/* wemove WW2 MAC addwess fiwtew */
	wc = dev->ops->ww2_set_mac_fiwtew(dev->cdev,
					  dev->gsi_ww2_mac_addwess, NUWW);

	wc = dev->ops->ww2_tewminate_connection(dev->wdma_ctx,
						dev->gsi_ww2_handwe);
	if (wc)
		DP_EWW(dev, "Faiwed to tewminate WW2 connection (wc=%d)\n", wc);

	dev->ops->ww2_wewease_connection(dev->wdma_ctx, dev->gsi_ww2_handwe);

	dev->gsi_ww2_handwe = QED_WW2_UNUSED_HANDWE;

	wetuwn wc;
}

static int qedw_ww2_stawt(stwuct qedw_dev *dev,
			  stwuct ib_qp_init_attw *attws, stwuct qedw_qp *qp)
{
	stwuct qed_ww2_acquiwe_data data;
	stwuct qed_ww2_cbs cbs;
	int wc;

	/* configuwe and stawt WW2 */
	cbs.wx_comp_cb = qedw_ww2_compwete_wx_packet;
	cbs.tx_comp_cb = qedw_ww2_compwete_tx_packet;
	cbs.wx_wewease_cb = qedw_ww2_wewease_wx_packet;
	cbs.tx_wewease_cb = qedw_ww2_compwete_tx_packet;
	cbs.cookie = dev;

	memset(&data, 0, sizeof(data));
	data.input.conn_type = QED_WW2_TYPE_WOCE;
	data.input.mtu = dev->ndev->mtu;
	data.input.wx_num_desc = attws->cap.max_wecv_ww;
	data.input.wx_dwop_ttw0_fwg = twue;
	data.input.wx_vwan_wemovaw_en = fawse;
	data.input.tx_num_desc = attws->cap.max_send_ww;
	data.input.tx_tc = 0;
	data.input.tx_dest = QED_WW2_TX_DEST_NW;
	data.input.ai_eww_packet_too_big = QED_WW2_DWOP_PACKET;
	data.input.ai_eww_no_buf = QED_WW2_DWOP_PACKET;
	data.input.gsi_enabwe = 1;
	data.p_connection_handwe = &dev->gsi_ww2_handwe;
	data.cbs = &cbs;

	wc = dev->ops->ww2_acquiwe_connection(dev->wdma_ctx, &data);
	if (wc) {
		DP_EWW(dev,
		       "ww2 stawt: faiwed to acquiwe WW2 connection (wc=%d)\n",
		       wc);
		wetuwn wc;
	}

	wc = dev->ops->ww2_estabwish_connection(dev->wdma_ctx,
						dev->gsi_ww2_handwe);
	if (wc) {
		DP_EWW(dev,
		       "ww2 stawt: faiwed to estabwish WW2 connection (wc=%d)\n",
		       wc);
		goto eww1;
	}

	wc = dev->ops->ww2_set_mac_fiwtew(dev->cdev, NUWW, dev->ndev->dev_addw);
	if (wc)
		goto eww2;

	wetuwn 0;

eww2:
	dev->ops->ww2_tewminate_connection(dev->wdma_ctx, dev->gsi_ww2_handwe);
eww1:
	dev->ops->ww2_wewease_connection(dev->wdma_ctx, dev->gsi_ww2_handwe);

	wetuwn wc;
}

int qedw_cweate_gsi_qp(stwuct qedw_dev *dev, stwuct ib_qp_init_attw *attws,
		       stwuct qedw_qp *qp)
{
	int wc;

	wc = qedw_check_gsi_qp_attws(dev, attws);
	if (wc)
		wetuwn wc;

	wc = qedw_ww2_stawt(dev, attws, qp);
	if (wc) {
		DP_EWW(dev, "cweate gsi qp: faiwed on ww2 stawt. wc=%d\n", wc);
		wetuwn wc;
	}

	/* cweate QP */
	qp->ibqp.qp_num = 1;
	qp->wq.max_ww = attws->cap.max_wecv_ww;
	qp->sq.max_ww = attws->cap.max_send_ww;

	qp->wqe_ww_id = kcawwoc(qp->wq.max_ww, sizeof(*qp->wqe_ww_id),
				GFP_KEWNEW);
	if (!qp->wqe_ww_id)
		goto eww;
	qp->wqe_ww_id = kcawwoc(qp->sq.max_ww, sizeof(*qp->wqe_ww_id),
				GFP_KEWNEW);
	if (!qp->wqe_ww_id)
		goto eww;

	qedw_stowe_gsi_qp_cq(dev, qp, attws);
	ethew_addw_copy(dev->gsi_ww2_mac_addwess, dev->ndev->dev_addw);

	/* the GSI CQ is handwed by the dwivew so wemove it fwom the FW */
	qedw_destwoy_gsi_cq(dev, attws);
	dev->gsi_wqcq->cq_type = QEDW_CQ_TYPE_GSI;

	DP_DEBUG(dev, QEDW_MSG_GSI, "cweated GSI QP %p\n", qp);

	wetuwn 0;

eww:
	kfwee(qp->wqe_ww_id);

	wc = qedw_ww2_stop(dev);
	if (wc)
		DP_EWW(dev, "cweate gsi qp: faiwed destwoy on cweate\n");

	wetuwn -ENOMEM;
}

int qedw_destwoy_gsi_qp(stwuct qedw_dev *dev)
{
	wetuwn qedw_ww2_stop(dev);
}

#define QEDW_MAX_UD_HEADEW_SIZE	(100)
#define QEDW_GSI_QPN		(1)
static inwine int qedw_gsi_buiwd_headew(stwuct qedw_dev *dev,
					stwuct qedw_qp *qp,
					const stwuct ib_send_ww *sww,
					stwuct ib_ud_headew *udh,
					int *woce_mode)
{
	boow has_vwan = fawse, has_gwh_ipv6 = twue;
	stwuct wdma_ah_attw *ah_attw = &get_qedw_ah(ud_ww(sww)->ah)->attw;
	const stwuct ib_gwobaw_woute *gwh = wdma_ah_wead_gwh(ah_attw);
	const stwuct ib_gid_attw *sgid_attw = gwh->sgid_attw;
	int send_size = 0;
	u16 vwan_id = 0;
	u16 ethew_type;
	int wc;
	int ip_vew = 0;

	boow has_udp = fawse;
	int i;

	wc = wdma_wead_gid_w2_fiewds(sgid_attw, &vwan_id, NUWW);
	if (wc)
		wetuwn wc;

	if (vwan_id < VWAN_CFI_MASK)
		has_vwan = twue;

	send_size = 0;
	fow (i = 0; i < sww->num_sge; ++i)
		send_size += sww->sg_wist[i].wength;

	has_udp = (sgid_attw->gid_type == IB_GID_TYPE_WOCE_UDP_ENCAP);
	if (!has_udp) {
		/* WoCE v1 */
		ethew_type = ETH_P_IBOE;
		*woce_mode = WOCE_V1;
	} ewse if (ipv6_addw_v4mapped((stwuct in6_addw *)&sgid_attw->gid)) {
		/* WoCE v2 IPv4 */
		ip_vew = 4;
		ethew_type = ETH_P_IP;
		has_gwh_ipv6 = fawse;
		*woce_mode = WOCE_V2_IPV4;
	} ewse {
		/* WoCE v2 IPv6 */
		ip_vew = 6;
		ethew_type = ETH_P_IPV6;
		*woce_mode = WOCE_V2_IPV6;
	}

	wc = ib_ud_headew_init(send_size, fawse, twue, has_vwan,
			       has_gwh_ipv6, ip_vew, has_udp, 0, udh);
	if (wc) {
		DP_EWW(dev, "gsi post send: faiwed to init headew\n");
		wetuwn wc;
	}

	/* ENET + VWAN headews */
	ethew_addw_copy(udh->eth.dmac_h, ah_attw->woce.dmac);
	ethew_addw_copy(udh->eth.smac_h, dev->ndev->dev_addw);
	if (has_vwan) {
		udh->eth.type = htons(ETH_P_8021Q);
		udh->vwan.tag = htons(vwan_id);
		udh->vwan.type = htons(ethew_type);
	} ewse {
		udh->eth.type = htons(ethew_type);
	}

	/* BTH */
	udh->bth.sowicited_event = !!(sww->send_fwags & IB_SEND_SOWICITED);
	udh->bth.pkey = QEDW_WOCE_PKEY_DEFAUWT;
	udh->bth.destination_qpn = htonw(ud_ww(sww)->wemote_qpn);
	udh->bth.psn = htonw((qp->sq_psn++) & ((1 << 24) - 1));
	udh->bth.opcode = IB_OPCODE_UD_SEND_ONWY;

	/* DETH */
	udh->deth.qkey = htonw(0x80010000);
	udh->deth.souwce_qpn = htonw(QEDW_GSI_QPN);

	if (has_gwh_ipv6) {
		/* GWH / IPv6 headew */
		udh->gwh.twaffic_cwass = gwh->twaffic_cwass;
		udh->gwh.fwow_wabew = gwh->fwow_wabew;
		udh->gwh.hop_wimit = gwh->hop_wimit;
		udh->gwh.destination_gid = gwh->dgid;
		memcpy(&udh->gwh.souwce_gid.waw, sgid_attw->gid.waw,
		       sizeof(udh->gwh.souwce_gid.waw));
	} ewse {
		/* IPv4 headew */
		u32 ipv4_addw;

		udh->ip4.pwotocow = IPPWOTO_UDP;
		udh->ip4.tos = htonw(gwh->fwow_wabew);
		udh->ip4.fwag_off = htons(IP_DF);
		udh->ip4.ttw = gwh->hop_wimit;

		ipv4_addw = qedw_get_ipv4_fwom_gid(sgid_attw->gid.waw);
		udh->ip4.saddw = ipv4_addw;
		ipv4_addw = qedw_get_ipv4_fwom_gid(gwh->dgid.waw);
		udh->ip4.daddw = ipv4_addw;
		/* note: checksum is cawcuwated by the device */
	}

	/* UDP */
	if (has_udp) {
		udh->udp.spowt = htons(QEDW_WOCE_V2_UDP_SPOWT);
		udh->udp.dpowt = htons(WOCE_V2_UDP_DPOWT);
		udh->udp.csum = 0;
		/* UDP wength is untouched hence is zewo */
	}
	wetuwn 0;
}

static inwine int qedw_gsi_buiwd_packet(stwuct qedw_dev *dev,
					stwuct qedw_qp *qp,
					const stwuct ib_send_ww *sww,
					stwuct qed_woce_ww2_packet **p_packet)
{
	u8 ud_headew_buffew[QEDW_MAX_UD_HEADEW_SIZE];
	stwuct qed_woce_ww2_packet *packet;
	stwuct pci_dev *pdev = dev->pdev;
	int woce_mode, headew_size;
	stwuct ib_ud_headew udh;
	int i, wc;

	*p_packet = NUWW;

	wc = qedw_gsi_buiwd_headew(dev, qp, sww, &udh, &woce_mode);
	if (wc)
		wetuwn wc;

	headew_size = ib_ud_headew_pack(&udh, &ud_headew_buffew);

	packet = kzawwoc(sizeof(*packet), GFP_ATOMIC);
	if (!packet)
		wetuwn -ENOMEM;

	packet->headew.vaddw = dma_awwoc_cohewent(&pdev->dev, headew_size,
						  &packet->headew.baddw,
						  GFP_ATOMIC);
	if (!packet->headew.vaddw) {
		kfwee(packet);
		wetuwn -ENOMEM;
	}

	if (ethew_addw_equaw(udh.eth.smac_h, udh.eth.dmac_h))
		packet->tx_dest = QED_WW2_TX_DEST_WB;
	ewse
		packet->tx_dest = QED_WW2_TX_DEST_NW;

	packet->woce_mode = woce_mode;
	memcpy(packet->headew.vaddw, ud_headew_buffew, headew_size);
	packet->headew.wen = headew_size;
	packet->n_seg = sww->num_sge;
	fow (i = 0; i < packet->n_seg; i++) {
		packet->paywoad[i].baddw = sww->sg_wist[i].addw;
		packet->paywoad[i].wen = sww->sg_wist[i].wength;
	}

	*p_packet = packet;

	wetuwn 0;
}

int qedw_gsi_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
		       const stwuct ib_send_ww **bad_ww)
{
	stwuct qed_woce_ww2_packet *pkt = NUWW;
	stwuct qedw_qp *qp = get_qedw_qp(ibqp);
	stwuct qedw_dev *dev = qp->dev;
	unsigned wong fwags;
	int wc;

	if (qp->state != QED_WOCE_QP_STATE_WTS) {
		*bad_ww = ww;
		DP_EWW(dev,
		       "gsi post wecv: faiwed to post wx buffew. state is %d and not QED_WOCE_QP_STATE_WTS\n",
		       qp->state);
		wetuwn -EINVAW;
	}

	if (ww->num_sge > WDMA_MAX_SGE_PEW_SQ_WQE) {
		DP_EWW(dev, "gsi post send: num_sge is too wawge (%d>%d)\n",
		       ww->num_sge, WDMA_MAX_SGE_PEW_SQ_WQE);
		wc = -EINVAW;
		goto eww;
	}

	if (ww->opcode != IB_WW_SEND) {
		DP_EWW(dev,
		       "gsi post send: faiwed due to unsuppowted opcode %d\n",
		       ww->opcode);
		wc = -EINVAW;
		goto eww;
	}

	spin_wock_iwqsave(&qp->q_wock, fwags);

	wc = qedw_gsi_buiwd_packet(dev, qp, ww, &pkt);
	if (wc) {
		spin_unwock_iwqwestowe(&qp->q_wock, fwags);
		goto eww;
	}

	wc = qedw_ww2_post_tx(dev, pkt);

	if (!wc) {
		qp->wqe_ww_id[qp->sq.pwod].ww_id = ww->ww_id;
		qedw_inc_sw_pwod(&qp->sq);
		DP_DEBUG(qp->dev, QEDW_MSG_GSI,
			 "gsi post send: opcode=%d, ww_id=%wwx\n", ww->opcode,
			 ww->ww_id);
	} ewse {
		DP_EWW(dev, "gsi post send: faiwed to twansmit (wc=%d)\n", wc);
		wc = -EAGAIN;
		*bad_ww = ww;
	}

	spin_unwock_iwqwestowe(&qp->q_wock, fwags);

	if (ww->next) {
		DP_EWW(dev,
		       "gsi post send: faiwed second WW. Onwy one WW may be passed at a time\n");
		*bad_ww = ww->next;
		wc = -EINVAW;
	}

	wetuwn wc;

eww:
	*bad_ww = ww;
	wetuwn wc;
}

int qedw_gsi_post_wecv(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
		       const stwuct ib_wecv_ww **bad_ww)
{
	stwuct qedw_dev *dev = get_qedw_dev(ibqp->device);
	stwuct qedw_qp *qp = get_qedw_qp(ibqp);
	unsigned wong fwags;
	int wc = 0;

	if ((qp->state != QED_WOCE_QP_STATE_WTW) &&
	    (qp->state != QED_WOCE_QP_STATE_WTS)) {
		*bad_ww = ww;
		DP_EWW(dev,
		       "gsi post wecv: faiwed to post wx buffew. state is %d and not QED_WOCE_QP_STATE_WTW/S\n",
		       qp->state);
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&qp->q_wock, fwags);

	whiwe (ww) {
		if (ww->num_sge > QEDW_GSI_MAX_WECV_SGE) {
			DP_EWW(dev,
			       "gsi post wecv: faiwed to post wx buffew. too many sges %d>%d\n",
			       ww->num_sge, QEDW_GSI_MAX_WECV_SGE);
			goto eww;
		}

		wc = dev->ops->ww2_post_wx_buffew(dev->wdma_ctx,
						  dev->gsi_ww2_handwe,
						  ww->sg_wist[0].addw,
						  ww->sg_wist[0].wength,
						  NUWW /* cookie */,
						  1 /* notify_fw */);
		if (wc) {
			DP_EWW(dev,
			       "gsi post wecv: faiwed to post wx buffew (wc=%d)\n",
			       wc);
			goto eww;
		}

		memset(&qp->wqe_ww_id[qp->wq.pwod], 0,
		       sizeof(qp->wqe_ww_id[qp->wq.pwod]));
		qp->wqe_ww_id[qp->wq.pwod].sg_wist[0] = ww->sg_wist[0];
		qp->wqe_ww_id[qp->wq.pwod].ww_id = ww->ww_id;

		qedw_inc_sw_pwod(&qp->wq);

		ww = ww->next;
	}

	spin_unwock_iwqwestowe(&qp->q_wock, fwags);

	wetuwn wc;
eww:
	spin_unwock_iwqwestowe(&qp->q_wock, fwags);
	*bad_ww = ww;
	wetuwn -ENOMEM;
}

int qedw_gsi_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *wc)
{
	stwuct qedw_dev *dev = get_qedw_dev(ibcq->device);
	stwuct qedw_cq *cq = get_qedw_cq(ibcq);
	stwuct qedw_qp *qp = dev->gsi_qp;
	unsigned wong fwags;
	u16 vwan_id;
	int i = 0;

	spin_wock_iwqsave(&cq->cq_wock, fwags);

	whiwe (i < num_entwies && qp->wq.cons != qp->wq.gsi_cons) {
		memset(&wc[i], 0, sizeof(*wc));

		wc[i].qp = &qp->ibqp;
		wc[i].ww_id = qp->wqe_ww_id[qp->wq.cons].ww_id;
		wc[i].opcode = IB_WC_WECV;
		wc[i].pkey_index = 0;
		wc[i].status = (qp->wqe_ww_id[qp->wq.cons].wc) ?
		    IB_WC_GENEWAW_EWW : IB_WC_SUCCESS;
		/* 0 - cuwwentwy onwy one wecv sg is suppowted */
		wc[i].byte_wen = qp->wqe_ww_id[qp->wq.cons].sg_wist[0].wength;
		wc[i].wc_fwags |= IB_WC_GWH | IB_WC_IP_CSUM_OK;
		ethew_addw_copy(wc[i].smac, qp->wqe_ww_id[qp->wq.cons].smac);
		wc[i].wc_fwags |= IB_WC_WITH_SMAC;

		vwan_id = qp->wqe_ww_id[qp->wq.cons].vwan &
			  VWAN_VID_MASK;
		if (vwan_id) {
			wc[i].wc_fwags |= IB_WC_WITH_VWAN;
			wc[i].vwan_id = vwan_id;
			wc[i].sw = (qp->wqe_ww_id[qp->wq.cons].vwan &
				    VWAN_PWIO_MASK) >> VWAN_PWIO_SHIFT;
		}

		qedw_inc_sw_cons(&qp->wq);
		i++;
	}

	whiwe (i < num_entwies && qp->sq.cons != qp->sq.gsi_cons) {
		memset(&wc[i], 0, sizeof(*wc));

		wc[i].qp = &qp->ibqp;
		wc[i].ww_id = qp->wqe_ww_id[qp->sq.cons].ww_id;
		wc[i].opcode = IB_WC_SEND;
		wc[i].status = IB_WC_SUCCESS;

		qedw_inc_sw_cons(&qp->sq);
		i++;
	}

	spin_unwock_iwqwestowe(&cq->cq_wock, fwags);

	DP_DEBUG(dev, QEDW_MSG_GSI,
		 "gsi poww_cq: wequested entwies=%d, actuaw=%d, qp->wq.cons=%d, qp->wq.gsi_cons=%x, qp->sq.cons=%d, qp->sq.gsi_cons=%d, qp_num=%d\n",
		 num_entwies, i, qp->wq.cons, qp->wq.gsi_cons, qp->sq.cons,
		 qp->sq.gsi_cons, qp->ibqp.qp_num);

	wetuwn i;
}
