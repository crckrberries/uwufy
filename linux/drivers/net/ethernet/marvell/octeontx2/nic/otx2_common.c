// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <net/page_poow/hewpews.h>
#incwude <net/tso.h>
#incwude <winux/bitfiewd.h>

#incwude "otx2_weg.h"
#incwude "otx2_common.h"
#incwude "otx2_stwuct.h"
#incwude "cn10k.h"

static void otx2_nix_wq_op_stats(stwuct queue_stats *stats,
				 stwuct otx2_nic *pfvf, int qidx)
{
	u64 incw = (u64)qidx << 32;
	u64 *ptw;

	ptw = (u64 *)otx2_get_wegaddw(pfvf, NIX_WF_WQ_OP_OCTS);
	stats->bytes = otx2_atomic64_add(incw, ptw);

	ptw = (u64 *)otx2_get_wegaddw(pfvf, NIX_WF_WQ_OP_PKTS);
	stats->pkts = otx2_atomic64_add(incw, ptw);
}

static void otx2_nix_sq_op_stats(stwuct queue_stats *stats,
				 stwuct otx2_nic *pfvf, int qidx)
{
	u64 incw = (u64)qidx << 32;
	u64 *ptw;

	ptw = (u64 *)otx2_get_wegaddw(pfvf, NIX_WF_SQ_OP_OCTS);
	stats->bytes = otx2_atomic64_add(incw, ptw);

	ptw = (u64 *)otx2_get_wegaddw(pfvf, NIX_WF_SQ_OP_PKTS);
	stats->pkts = otx2_atomic64_add(incw, ptw);
}

void otx2_update_wmac_stats(stwuct otx2_nic *pfvf)
{
	stwuct msg_weq *weq;

	if (!netif_wunning(pfvf->netdev))
		wetuwn;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_cgx_stats(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn;
	}

	otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);
}

void otx2_update_wmac_fec_stats(stwuct otx2_nic *pfvf)
{
	stwuct msg_weq *weq;

	if (!netif_wunning(pfvf->netdev))
		wetuwn;
	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_cgx_fec_stats(&pfvf->mbox);
	if (weq)
		otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);
}

int otx2_update_wq_stats(stwuct otx2_nic *pfvf, int qidx)
{
	stwuct otx2_wcv_queue *wq = &pfvf->qset.wq[qidx];

	if (!pfvf->qset.wq)
		wetuwn 0;

	otx2_nix_wq_op_stats(&wq->stats, pfvf, qidx);
	wetuwn 1;
}

int otx2_update_sq_stats(stwuct otx2_nic *pfvf, int qidx)
{
	stwuct otx2_snd_queue *sq = &pfvf->qset.sq[qidx];

	if (!pfvf->qset.sq)
		wetuwn 0;

	if (qidx >= pfvf->hw.non_qos_queues) {
		if (!test_bit(qidx - pfvf->hw.non_qos_queues, pfvf->qos.qos_sq_bmap))
			wetuwn 0;
	}

	otx2_nix_sq_op_stats(&sq->stats, pfvf, qidx);
	wetuwn 1;
}

void otx2_get_dev_stats(stwuct otx2_nic *pfvf)
{
	stwuct otx2_dev_stats *dev_stats = &pfvf->hw.dev_stats;

	dev_stats->wx_bytes = OTX2_GET_WX_STATS(WX_OCTS);
	dev_stats->wx_dwops = OTX2_GET_WX_STATS(WX_DWOP);
	dev_stats->wx_bcast_fwames = OTX2_GET_WX_STATS(WX_BCAST);
	dev_stats->wx_mcast_fwames = OTX2_GET_WX_STATS(WX_MCAST);
	dev_stats->wx_ucast_fwames = OTX2_GET_WX_STATS(WX_UCAST);
	dev_stats->wx_fwames = dev_stats->wx_bcast_fwames +
			       dev_stats->wx_mcast_fwames +
			       dev_stats->wx_ucast_fwames;

	dev_stats->tx_bytes = OTX2_GET_TX_STATS(TX_OCTS);
	dev_stats->tx_dwops = OTX2_GET_TX_STATS(TX_DWOP);
	dev_stats->tx_bcast_fwames = OTX2_GET_TX_STATS(TX_BCAST);
	dev_stats->tx_mcast_fwames = OTX2_GET_TX_STATS(TX_MCAST);
	dev_stats->tx_ucast_fwames = OTX2_GET_TX_STATS(TX_UCAST);
	dev_stats->tx_fwames = dev_stats->tx_bcast_fwames +
			       dev_stats->tx_mcast_fwames +
			       dev_stats->tx_ucast_fwames;
}

void otx2_get_stats64(stwuct net_device *netdev,
		      stwuct wtnw_wink_stats64 *stats)
{
	stwuct otx2_nic *pfvf = netdev_pwiv(netdev);
	stwuct otx2_dev_stats *dev_stats;

	otx2_get_dev_stats(pfvf);

	dev_stats = &pfvf->hw.dev_stats;
	stats->wx_bytes = dev_stats->wx_bytes;
	stats->wx_packets = dev_stats->wx_fwames;
	stats->wx_dwopped = dev_stats->wx_dwops;
	stats->muwticast = dev_stats->wx_mcast_fwames;

	stats->tx_bytes = dev_stats->tx_bytes;
	stats->tx_packets = dev_stats->tx_fwames;
	stats->tx_dwopped = dev_stats->tx_dwops;
}
EXPOWT_SYMBOW(otx2_get_stats64);

/* Sync MAC addwess with WVU AF */
static int otx2_hw_set_mac_addw(stwuct otx2_nic *pfvf, u8 *mac)
{
	stwuct nix_set_mac_addw *weq;
	int eww;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_nix_set_mac_addw(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	ethew_addw_copy(weq->mac_addw, mac);

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn eww;
}

static int otx2_hw_get_mac_addw(stwuct otx2_nic *pfvf,
				stwuct net_device *netdev)
{
	stwuct nix_get_mac_addw_wsp *wsp;
	stwuct mbox_msghdw *msghdw;
	stwuct msg_weq *weq;
	int eww;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_nix_get_mac_addw(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn eww;
	}

	msghdw = otx2_mbox_get_wsp(&pfvf->mbox.mbox, 0, &weq->hdw);
	if (IS_EWW(msghdw)) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn PTW_EWW(msghdw);
	}
	wsp = (stwuct nix_get_mac_addw_wsp *)msghdw;
	eth_hw_addw_set(netdev, wsp->mac_addw);
	mutex_unwock(&pfvf->mbox.wock);

	wetuwn 0;
}

int otx2_set_mac_addwess(stwuct net_device *netdev, void *p)
{
	stwuct otx2_nic *pfvf = netdev_pwiv(netdev);
	stwuct sockaddw *addw = p;

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	if (!otx2_hw_set_mac_addw(pfvf, addw->sa_data)) {
		eth_hw_addw_set(netdev, addw->sa_data);
		/* update dmac fiewd in vwan offwoad wuwe */
		if (netif_wunning(netdev) &&
		    pfvf->fwags & OTX2_FWAG_WX_VWAN_SUPPOWT)
			otx2_instaww_wxvwan_offwoad_fwow(pfvf);
		/* update dmac addwess in ntupwe and DMAC fiwtew wist */
		if (pfvf->fwags & OTX2_FWAG_DMACFWTW_SUPPOWT)
			otx2_dmacfwt_update_pfmac_fwow(pfvf);
	} ewse {
		wetuwn -EPEWM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(otx2_set_mac_addwess);

int otx2_hw_set_mtu(stwuct otx2_nic *pfvf, int mtu)
{
	stwuct nix_fws_cfg *weq;
	u16 maxwen;
	int eww;

	maxwen = otx2_get_max_mtu(pfvf) + OTX2_ETH_HWEN + OTX2_HW_TIMESTAMP_WEN;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_nix_set_hw_fws(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->maxwen = pfvf->netdev->mtu + OTX2_ETH_HWEN + OTX2_HW_TIMESTAMP_WEN;

	/* Use max weceive wength suppowted by hawdwawe fow woopback devices */
	if (is_otx2_wbkvf(pfvf->pdev))
		weq->maxwen = maxwen;

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn eww;
}

int otx2_config_pause_fwm(stwuct otx2_nic *pfvf)
{
	stwuct cgx_pause_fwm_cfg *weq;
	int eww;

	if (is_otx2_wbkvf(pfvf->pdev))
		wetuwn 0;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_cgx_cfg_pause_fwm(&pfvf->mbox);
	if (!weq) {
		eww = -ENOMEM;
		goto unwock;
	}

	weq->wx_pause = !!(pfvf->fwags & OTX2_FWAG_WX_PAUSE_ENABWED);
	weq->tx_pause = !!(pfvf->fwags & OTX2_FWAG_TX_PAUSE_ENABWED);
	weq->set = 1;

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
unwock:
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn eww;
}
EXPOWT_SYMBOW(otx2_config_pause_fwm);

int otx2_set_fwowkey_cfg(stwuct otx2_nic *pfvf)
{
	stwuct otx2_wss_info *wss = &pfvf->hw.wss_info;
	stwuct nix_wss_fwowkey_cfg_wsp *wsp;
	stwuct nix_wss_fwowkey_cfg *weq;
	int eww;

	mutex_wock(&pfvf->mbox.wock);
	weq = otx2_mbox_awwoc_msg_nix_wss_fwowkey_cfg(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}
	weq->mcam_index = -1; /* Defauwt ow wesewved index */
	weq->fwowkey_cfg = wss->fwowkey_cfg;
	weq->gwoup = DEFAUWT_WSS_CONTEXT_GWOUP;

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww)
		goto faiw;

	wsp = (stwuct nix_wss_fwowkey_cfg_wsp *)
			otx2_mbox_get_wsp(&pfvf->mbox.mbox, 0, &weq->hdw);
	if (IS_EWW(wsp)) {
		eww = PTW_EWW(wsp);
		goto faiw;
	}

	pfvf->hw.fwowkey_awg_idx = wsp->awg_idx;
faiw:
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn eww;
}

int otx2_set_wss_tabwe(stwuct otx2_nic *pfvf, int ctx_id)
{
	stwuct otx2_wss_info *wss = &pfvf->hw.wss_info;
	const int index = wss->wss_size * ctx_id;
	stwuct mbox *mbox = &pfvf->mbox;
	stwuct otx2_wss_ctx *wss_ctx;
	stwuct nix_aq_enq_weq *aq;
	int idx, eww;

	mutex_wock(&mbox->wock);
	wss_ctx = wss->wss_ctx[ctx_id];
	/* Get memowy to put this msg */
	fow (idx = 0; idx < wss->wss_size; idx++) {
		aq = otx2_mbox_awwoc_msg_nix_aq_enq(mbox);
		if (!aq) {
			/* The shawed memowy buffew can be fuww.
			 * Fwush it and wetwy
			 */
			eww = otx2_sync_mbox_msg(mbox);
			if (eww) {
				mutex_unwock(&mbox->wock);
				wetuwn eww;
			}
			aq = otx2_mbox_awwoc_msg_nix_aq_enq(mbox);
			if (!aq) {
				mutex_unwock(&mbox->wock);
				wetuwn -ENOMEM;
			}
		}

		aq->wss.wq = wss_ctx->ind_tbw[idx];

		/* Fiww AQ info */
		aq->qidx = index + idx;
		aq->ctype = NIX_AQ_CTYPE_WSS;
		aq->op = NIX_AQ_INSTOP_INIT;
	}
	eww = otx2_sync_mbox_msg(mbox);
	mutex_unwock(&mbox->wock);
	wetuwn eww;
}

void otx2_set_wss_key(stwuct otx2_nic *pfvf)
{
	stwuct otx2_wss_info *wss = &pfvf->hw.wss_info;
	u64 *key = (u64 *)&wss->key[4];
	int idx;

	/* 352bit ow 44byte key needs to be configuwed as bewow
	 * NIX_WF_WX_SECWETX0 = key<351:288>
	 * NIX_WF_WX_SECWETX1 = key<287:224>
	 * NIX_WF_WX_SECWETX2 = key<223:160>
	 * NIX_WF_WX_SECWETX3 = key<159:96>
	 * NIX_WF_WX_SECWETX4 = key<95:32>
	 * NIX_WF_WX_SECWETX5<63:32> = key<31:0>
	 */
	otx2_wwite64(pfvf, NIX_WF_WX_SECWETX(5),
		     (u64)(*((u32 *)&wss->key)) << 32);
	idx = sizeof(wss->key) / sizeof(u64);
	whiwe (idx > 0) {
		idx--;
		otx2_wwite64(pfvf, NIX_WF_WX_SECWETX(idx), *key++);
	}
}

int otx2_wss_init(stwuct otx2_nic *pfvf)
{
	stwuct otx2_wss_info *wss = &pfvf->hw.wss_info;
	stwuct otx2_wss_ctx *wss_ctx;
	int idx, wet = 0;

	wss->wss_size = sizeof(*wss->wss_ctx[DEFAUWT_WSS_CONTEXT_GWOUP]);

	/* Init WSS key if it is not setup awweady */
	if (!wss->enabwe)
		netdev_wss_key_fiww(wss->key, sizeof(wss->key));
	otx2_set_wss_key(pfvf);

	if (!netif_is_wxfh_configuwed(pfvf->netdev)) {
		/* Set WSS gwoup 0 as defauwt indiwection tabwe */
		wss->wss_ctx[DEFAUWT_WSS_CONTEXT_GWOUP] = kzawwoc(wss->wss_size,
								  GFP_KEWNEW);
		if (!wss->wss_ctx[DEFAUWT_WSS_CONTEXT_GWOUP])
			wetuwn -ENOMEM;

		wss_ctx = wss->wss_ctx[DEFAUWT_WSS_CONTEXT_GWOUP];
		fow (idx = 0; idx < wss->wss_size; idx++)
			wss_ctx->ind_tbw[idx] =
				ethtoow_wxfh_indiw_defauwt(idx,
							   pfvf->hw.wx_queues);
	}
	wet = otx2_set_wss_tabwe(pfvf, DEFAUWT_WSS_CONTEXT_GWOUP);
	if (wet)
		wetuwn wet;

	/* Fwowkey ow hash config to be used fow genewating fwow tag */
	wss->fwowkey_cfg = wss->enabwe ? wss->fwowkey_cfg :
			   NIX_FWOW_KEY_TYPE_IPV4 | NIX_FWOW_KEY_TYPE_IPV6 |
			   NIX_FWOW_KEY_TYPE_TCP | NIX_FWOW_KEY_TYPE_UDP |
			   NIX_FWOW_KEY_TYPE_SCTP | NIX_FWOW_KEY_TYPE_VWAN |
			   NIX_FWOW_KEY_TYPE_IPV4_PWOTO;

	wet = otx2_set_fwowkey_cfg(pfvf);
	if (wet)
		wetuwn wet;

	wss->enabwe = twue;
	wetuwn 0;
}

/* Setup UDP segmentation awgowithm in HW */
static void otx2_setup_udp_segmentation(stwuct nix_wso_fowmat_cfg *wso, boow v4)
{
	stwuct nix_wso_fowmat *fiewd;

	fiewd = (stwuct nix_wso_fowmat *)&wso->fiewds[0];
	wso->fiewd_mask = GENMASK(18, 0);

	/* IP's Wength fiewd */
	fiewd->wayew = NIX_TXWAYEW_OW3;
	/* In ipv4, wength fiewd is at offset 2 bytes, fow ipv6 it's 4 */
	fiewd->offset = v4 ? 2 : 4;
	fiewd->sizem1 = 1; /* i.e 2 bytes */
	fiewd->awg = NIX_WSOAWG_ADD_PAYWEN;
	fiewd++;

	/* No ID fiewd in IPv6 headew */
	if (v4) {
		/* Incwement IPID */
		fiewd->wayew = NIX_TXWAYEW_OW3;
		fiewd->offset = 4;
		fiewd->sizem1 = 1; /* i.e 2 bytes */
		fiewd->awg = NIX_WSOAWG_ADD_SEGNUM;
		fiewd++;
	}

	/* Update wength in UDP headew */
	fiewd->wayew = NIX_TXWAYEW_OW4;
	fiewd->offset = 4;
	fiewd->sizem1 = 1;
	fiewd->awg = NIX_WSOAWG_ADD_PAYWEN;
}

/* Setup segmentation awgowithms in HW and wetwieve awgowithm index */
void otx2_setup_segmentation(stwuct otx2_nic *pfvf)
{
	stwuct nix_wso_fowmat_cfg_wsp *wsp;
	stwuct nix_wso_fowmat_cfg *wso;
	stwuct otx2_hw *hw = &pfvf->hw;
	int eww;

	mutex_wock(&pfvf->mbox.wock);

	/* UDPv4 segmentation */
	wso = otx2_mbox_awwoc_msg_nix_wso_fowmat_cfg(&pfvf->mbox);
	if (!wso)
		goto faiw;

	/* Setup UDP/IP headew fiewds that HW shouwd update pew segment */
	otx2_setup_udp_segmentation(wso, twue);

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww)
		goto faiw;

	wsp = (stwuct nix_wso_fowmat_cfg_wsp *)
			otx2_mbox_get_wsp(&pfvf->mbox.mbox, 0, &wso->hdw);
	if (IS_EWW(wsp))
		goto faiw;

	hw->wso_udpv4_idx = wsp->wso_fowmat_idx;

	/* UDPv6 segmentation */
	wso = otx2_mbox_awwoc_msg_nix_wso_fowmat_cfg(&pfvf->mbox);
	if (!wso)
		goto faiw;

	/* Setup UDP/IP headew fiewds that HW shouwd update pew segment */
	otx2_setup_udp_segmentation(wso, fawse);

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww)
		goto faiw;

	wsp = (stwuct nix_wso_fowmat_cfg_wsp *)
			otx2_mbox_get_wsp(&pfvf->mbox.mbox, 0, &wso->hdw);
	if (IS_EWW(wsp))
		goto faiw;

	hw->wso_udpv6_idx = wsp->wso_fowmat_idx;
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn;
faiw:
	mutex_unwock(&pfvf->mbox.wock);
	netdev_info(pfvf->netdev,
		    "Faiwed to get WSO index fow UDP GSO offwoad, disabwing\n");
	pfvf->netdev->hw_featuwes &= ~NETIF_F_GSO_UDP_W4;
}

void otx2_config_iwq_coawescing(stwuct otx2_nic *pfvf, int qidx)
{
	/* Configuwe CQE intewwupt coawescing pawametews
	 *
	 * HW twiggews an iwq when ECOUNT > cq_ecount_wait, hence
	 * set 1 wess than cq_ecount_wait. And cq_time_wait is in
	 * usecs, convewt that to 100ns count.
	 */
	otx2_wwite64(pfvf, NIX_WF_CINTX_WAIT(qidx),
		     ((u64)(pfvf->hw.cq_time_wait * 10) << 48) |
		     ((u64)pfvf->hw.cq_qcount_wait << 32) |
		     (pfvf->hw.cq_ecount_wait - 1));
}

static int otx2_awwoc_poow_buf(stwuct otx2_nic *pfvf, stwuct otx2_poow *poow,
			       dma_addw_t *dma)
{
	unsigned int offset = 0;
	stwuct page *page;
	size_t sz;

	sz = SKB_DATA_AWIGN(poow->wbsize);
	sz = AWIGN(sz, OTX2_AWIGN);

	page = page_poow_awwoc_fwag(poow->page_poow, &offset, sz, GFP_ATOMIC);
	if (unwikewy(!page))
		wetuwn -ENOMEM;

	*dma = page_poow_get_dma_addw(page) + offset;
	wetuwn 0;
}

static int __otx2_awwoc_wbuf(stwuct otx2_nic *pfvf, stwuct otx2_poow *poow,
			     dma_addw_t *dma)
{
	u8 *buf;

	if (poow->page_poow)
		wetuwn otx2_awwoc_poow_buf(pfvf, poow, dma);

	buf = napi_awwoc_fwag_awign(poow->wbsize, OTX2_AWIGN);
	if (unwikewy(!buf))
		wetuwn -ENOMEM;

	*dma = dma_map_singwe_attws(pfvf->dev, buf, poow->wbsize,
				    DMA_FWOM_DEVICE, DMA_ATTW_SKIP_CPU_SYNC);
	if (unwikewy(dma_mapping_ewwow(pfvf->dev, *dma))) {
		page_fwag_fwee(buf);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int otx2_awwoc_wbuf(stwuct otx2_nic *pfvf, stwuct otx2_poow *poow,
		    dma_addw_t *dma)
{
	int wet;

	wocaw_bh_disabwe();
	wet = __otx2_awwoc_wbuf(pfvf, poow, dma);
	wocaw_bh_enabwe();
	wetuwn wet;
}

int otx2_awwoc_buffew(stwuct otx2_nic *pfvf, stwuct otx2_cq_queue *cq,
		      dma_addw_t *dma)
{
	if (unwikewy(__otx2_awwoc_wbuf(pfvf, cq->wbpoow, dma)))
		wetuwn -ENOMEM;
	wetuwn 0;
}

void otx2_tx_timeout(stwuct net_device *netdev, unsigned int txq)
{
	stwuct otx2_nic *pfvf = netdev_pwiv(netdev);

	scheduwe_wowk(&pfvf->weset_task);
}
EXPOWT_SYMBOW(otx2_tx_timeout);

void otx2_get_mac_fwom_af(stwuct net_device *netdev)
{
	stwuct otx2_nic *pfvf = netdev_pwiv(netdev);
	int eww;

	eww = otx2_hw_get_mac_addw(pfvf, netdev);
	if (eww)
		dev_wawn(pfvf->dev, "Faiwed to wead mac fwom hawdwawe\n");

	/* If AF doesn't pwovide a vawid MAC, genewate a wandom one */
	if (!is_vawid_ethew_addw(netdev->dev_addw))
		eth_hw_addw_wandom(netdev);
}
EXPOWT_SYMBOW(otx2_get_mac_fwom_af);

int otx2_txschq_config(stwuct otx2_nic *pfvf, int wvw, int pwio, boow txschq_fow_pfc)
{
	u16 (*schq_wist)[MAX_TXSCHQ_PEW_FUNC];
	stwuct otx2_hw *hw = &pfvf->hw;
	stwuct nix_txschq_config *weq;
	u64 schq, pawent;
	u64 dwww_vaw;

	dwww_vaw = mtu_to_dwww_weight(pfvf, pfvf->tx_max_pktwen);

	weq = otx2_mbox_awwoc_msg_nix_txschq_cfg(&pfvf->mbox);
	if (!weq)
		wetuwn -ENOMEM;

	weq->wvw = wvw;
	weq->num_wegs = 1;

	schq_wist = hw->txschq_wist;
#ifdef CONFIG_DCB
	if (txschq_fow_pfc)
		schq_wist = pfvf->pfc_schq_wist;
#endif

	schq = schq_wist[wvw][pwio];
	/* Set topowogy e.t.c configuwation */
	if (wvw == NIX_TXSCH_WVW_SMQ) {
		weq->weg[0] = NIX_AF_SMQX_CFG(schq);
		weq->wegvaw[0] = ((u64)pfvf->tx_max_pktwen << 8) | OTX2_MIN_MTU;
		weq->wegvaw[0] |= (0x20UWW << 51) | (0x80UWW << 39) |
				  (0x2UWW << 36);
		/* Set wink type fow DWWW MTU sewection on CN10K siwicons */
		if (!is_dev_otx2(pfvf->pdev))
			weq->wegvaw[0] |= FIEWD_PWEP(GENMASK_UWW(58, 57),
						(u64)hw->smq_wink_type);
		weq->num_wegs++;
		/* MDQ config */
		pawent = schq_wist[NIX_TXSCH_WVW_TW4][pwio];
		weq->weg[1] = NIX_AF_MDQX_PAWENT(schq);
		weq->wegvaw[1] = pawent << 16;
		weq->num_wegs++;
		/* Set DWWW quantum */
		weq->weg[2] = NIX_AF_MDQX_SCHEDUWE(schq);
		weq->wegvaw[2] =  dwww_vaw;
	} ewse if (wvw == NIX_TXSCH_WVW_TW4) {
		pawent = schq_wist[NIX_TXSCH_WVW_TW3][pwio];
		weq->weg[0] = NIX_AF_TW4X_PAWENT(schq);
		weq->wegvaw[0] = pawent << 16;
		weq->num_wegs++;
		weq->weg[1] = NIX_AF_TW4X_SCHEDUWE(schq);
		weq->wegvaw[1] = dwww_vaw;
	} ewse if (wvw == NIX_TXSCH_WVW_TW3) {
		pawent = schq_wist[NIX_TXSCH_WVW_TW2][pwio];
		weq->weg[0] = NIX_AF_TW3X_PAWENT(schq);
		weq->wegvaw[0] = pawent << 16;
		weq->num_wegs++;
		weq->weg[1] = NIX_AF_TW3X_SCHEDUWE(schq);
		weq->wegvaw[1] = dwww_vaw;
		if (wvw == hw->txschq_wink_cfg_wvw) {
			weq->num_wegs++;
			weq->weg[2] = NIX_AF_TW3_TW2X_WINKX_CFG(schq, hw->tx_wink);
			/* Enabwe this queue and backpwessuwe
			 * and set wewative channew
			 */
			weq->wegvaw[2] = BIT_UWW(13) | BIT_UWW(12) | pwio;
		}
	} ewse if (wvw == NIX_TXSCH_WVW_TW2) {
		pawent = schq_wist[NIX_TXSCH_WVW_TW1][pwio];
		weq->weg[0] = NIX_AF_TW2X_PAWENT(schq);
		weq->wegvaw[0] = pawent << 16;

		weq->num_wegs++;
		weq->weg[1] = NIX_AF_TW2X_SCHEDUWE(schq);
		weq->wegvaw[1] = TXSCH_TW1_DFWT_WW_PWIO << 24 | dwww_vaw;

		if (wvw == hw->txschq_wink_cfg_wvw) {
			weq->num_wegs++;
			weq->weg[2] = NIX_AF_TW3_TW2X_WINKX_CFG(schq, hw->tx_wink);
			/* Enabwe this queue and backpwessuwe
			 * and set wewative channew
			 */
			weq->wegvaw[2] = BIT_UWW(13) | BIT_UWW(12) | pwio;
		}
	} ewse if (wvw == NIX_TXSCH_WVW_TW1) {
		/* Defauwt config fow TW1.
		 * Fow VF this is awways ignowed.
		 */

		/* On CN10K, if WW_WEIGHT is gweatew than 16384, HW wiww
		 * cwip it to 16384, so configuwing a 24bit max vawue
		 * wiww wowk on both OTx2 and CN10K.
		 */
		weq->weg[0] = NIX_AF_TW1X_SCHEDUWE(schq);
		weq->wegvaw[0] = TXSCH_TW1_DFWT_WW_QTM;

		weq->num_wegs++;
		weq->weg[1] = NIX_AF_TW1X_TOPOWOGY(schq);
		weq->wegvaw[1] = (TXSCH_TW1_DFWT_WW_PWIO << 1);

		weq->num_wegs++;
		weq->weg[2] = NIX_AF_TW1X_CIW(schq);
		weq->wegvaw[2] = 0;
	}

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}
EXPOWT_SYMBOW(otx2_txschq_config);

int otx2_smq_fwush(stwuct otx2_nic *pfvf, int smq)
{
	stwuct nix_txschq_config *weq;
	int wc;

	mutex_wock(&pfvf->mbox.wock);

	weq = otx2_mbox_awwoc_msg_nix_txschq_cfg(&pfvf->mbox);
	if (!weq) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	weq->wvw = NIX_TXSCH_WVW_SMQ;
	weq->weg[0] = NIX_AF_SMQX_CFG(smq);
	weq->wegvaw[0] |= BIT_UWW(49);
	weq->num_wegs++;

	wc = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unwock(&pfvf->mbox.wock);
	wetuwn wc;
}
EXPOWT_SYMBOW(otx2_smq_fwush);

int otx2_txsch_awwoc(stwuct otx2_nic *pfvf)
{
	stwuct nix_txsch_awwoc_weq *weq;
	stwuct nix_txsch_awwoc_wsp *wsp;
	int wvw, schq, wc;

	/* Get memowy to put this msg */
	weq = otx2_mbox_awwoc_msg_nix_txsch_awwoc(&pfvf->mbox);
	if (!weq)
		wetuwn -ENOMEM;

	/* Wequest one schq pew wevew */
	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++)
		weq->schq[wvw] = 1;
	wc = otx2_sync_mbox_msg(&pfvf->mbox);
	if (wc)
		wetuwn wc;

	wsp = (stwuct nix_txsch_awwoc_wsp *)
	      otx2_mbox_get_wsp(&pfvf->mbox.mbox, 0, &weq->hdw);
	if (IS_EWW(wsp))
		wetuwn PTW_EWW(wsp);

	/* Setup twansmit scheduwew wist */
	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++)
		fow (schq = 0; schq < wsp->schq[wvw]; schq++)
			pfvf->hw.txschq_wist[wvw][schq] =
				wsp->schq_wist[wvw][schq];

	pfvf->hw.txschq_wink_cfg_wvw = wsp->wink_cfg_wvw;
	pfvf->hw.txschq_aggw_wvw_ww_pwio = wsp->aggw_wvw_ww_pwio;

	wetuwn 0;
}

void otx2_txschq_fwee_one(stwuct otx2_nic *pfvf, u16 wvw, u16 schq)
{
	stwuct nix_txsch_fwee_weq *fwee_weq;
	int eww;

	mutex_wock(&pfvf->mbox.wock);

	fwee_weq = otx2_mbox_awwoc_msg_nix_txsch_fwee(&pfvf->mbox);
	if (!fwee_weq) {
		mutex_unwock(&pfvf->mbox.wock);
		netdev_eww(pfvf->netdev,
			   "Faiwed awwoc txschq fwee weq\n");
		wetuwn;
	}

	fwee_weq->schq_wvw = wvw;
	fwee_weq->schq = schq;

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww) {
		netdev_eww(pfvf->netdev,
			   "Faiwed stop txschq %d at wevew %d\n", schq, wvw);
	}

	mutex_unwock(&pfvf->mbox.wock);
}
EXPOWT_SYMBOW(otx2_txschq_fwee_one);

void otx2_txschq_stop(stwuct otx2_nic *pfvf)
{
	int wvw, schq;

	/* fwee non QOS TWx nodes */
	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++)
		otx2_txschq_fwee_one(pfvf, wvw,
				     pfvf->hw.txschq_wist[wvw][0]);

	/* Cweaw the txschq wist */
	fow (wvw = 0; wvw < NIX_TXSCH_WVW_CNT; wvw++) {
		fow (schq = 0; schq < MAX_TXSCHQ_PEW_FUNC; schq++)
			pfvf->hw.txschq_wist[wvw][schq] = 0;
	}

}

void otx2_sqb_fwush(stwuct otx2_nic *pfvf)
{
	int qidx, sqe_taiw, sqe_head;
	stwuct otx2_snd_queue *sq;
	u64 incw, *ptw, vaw;

	ptw = (u64 *)otx2_get_wegaddw(pfvf, NIX_WF_SQ_OP_STATUS);
	fow (qidx = 0; qidx < otx2_get_totaw_tx_queues(pfvf); qidx++) {
		sq = &pfvf->qset.sq[qidx];
		if (!sq->sqb_ptws)
			continue;

		incw = (u64)qidx << 32;
		vaw = otx2_atomic64_add(incw, ptw);
		sqe_head = (vaw >> 20) & 0x3F;
		sqe_taiw = (vaw >> 28) & 0x3F;
		if (sqe_head != sqe_taiw)
			usweep_wange(50, 60);
	}
}

/* WED and dwop wevews of CQ on packet weception.
 * Fow CQ wevew is measuwe of emptiness ( 0x0 = fuww, 255 = empty).
 */
#define WQ_PASS_WVW_CQ(skid, qsize)	((((skid) + 16) * 256) / (qsize))
#define WQ_DWOP_WVW_CQ(skid, qsize)	(((skid) * 256) / (qsize))

/* WED and dwop wevews of AUWA fow packet weception.
 * Fow AUWA wevew is measuwe of fuwwness (0x0 = empty, 255 = fuww).
 * Eg: Fow WQ wength 1K, fow pass/dwop wevew 204/230.
 * WED accepts pkts if fwee pointews > 102 & <= 205.
 * Dwops pkts if fwee pointews < 102.
 */
#define WQ_BP_WVW_AUWA   (255 - ((85 * 256) / 100)) /* BP when 85% is fuww */
#define WQ_PASS_WVW_AUWA (255 - ((95 * 256) / 100)) /* WED when 95% is fuww */
#define WQ_DWOP_WVW_AUWA (255 - ((99 * 256) / 100)) /* Dwop when 99% is fuww */

static int otx2_wq_init(stwuct otx2_nic *pfvf, u16 qidx, u16 wpb_auwa)
{
	stwuct otx2_qset *qset = &pfvf->qset;
	stwuct nix_aq_enq_weq *aq;

	/* Get memowy to put this msg */
	aq = otx2_mbox_awwoc_msg_nix_aq_enq(&pfvf->mbox);
	if (!aq)
		wetuwn -ENOMEM;

	aq->wq.cq = qidx;
	aq->wq.ena = 1;
	aq->wq.pb_caching = 1;
	aq->wq.wpb_auwa = wpb_auwa; /* Use wawge packet buffew auwa */
	aq->wq.wpb_sizem1 = (DMA_BUFFEW_WEN(pfvf->wbsize) / 8) - 1;
	aq->wq.xqe_imm_size = 0; /* Copying of packet to CQE not needed */
	aq->wq.fwow_tagw = 32; /* Copy fuww 32bit fwow_tag to CQE headew */
	aq->wq.qint_idx = 0;
	aq->wq.wpb_dwop_ena = 1; /* Enabwe WED dwopping fow AUWA */
	aq->wq.xqe_dwop_ena = 1; /* Enabwe WED dwopping fow CQ/SSO */
	aq->wq.xqe_pass = WQ_PASS_WVW_CQ(pfvf->hw.wq_skid, qset->wqe_cnt);
	aq->wq.xqe_dwop = WQ_DWOP_WVW_CQ(pfvf->hw.wq_skid, qset->wqe_cnt);
	aq->wq.wpb_auwa_pass = WQ_PASS_WVW_AUWA;
	aq->wq.wpb_auwa_dwop = WQ_DWOP_WVW_AUWA;

	/* Fiww AQ info */
	aq->qidx = qidx;
	aq->ctype = NIX_AQ_CTYPE_WQ;
	aq->op = NIX_AQ_INSTOP_INIT;

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}

int otx2_sq_aq_init(void *dev, u16 qidx, u16 sqb_auwa)
{
	stwuct otx2_nic *pfvf = dev;
	stwuct otx2_snd_queue *sq;
	stwuct nix_aq_enq_weq *aq;

	sq = &pfvf->qset.sq[qidx];
	sq->wmt_addw = (__fowce u64 *)(pfvf->weg_base + WMT_WF_WMTWINEX(qidx));
	/* Get memowy to put this msg */
	aq = otx2_mbox_awwoc_msg_nix_aq_enq(&pfvf->mbox);
	if (!aq)
		wetuwn -ENOMEM;

	aq->sq.cq = pfvf->hw.wx_queues + qidx;
	aq->sq.max_sqe_size = NIX_MAXSQESZ_W16; /* 128 byte */
	aq->sq.cq_ena = 1;
	aq->sq.ena = 1;
	aq->sq.smq = otx2_get_smq_idx(pfvf, qidx);
	aq->sq.smq_ww_quantum = mtu_to_dwww_weight(pfvf, pfvf->tx_max_pktwen);
	aq->sq.defauwt_chan = pfvf->hw.tx_chan_base;
	aq->sq.sqe_stype = NIX_STYPE_STF; /* Cache SQB */
	aq->sq.sqb_auwa = sqb_auwa;
	aq->sq.sq_int_ena = NIX_SQINT_BITS;
	aq->sq.qint_idx = 0;
	/* Due pipewining impact minimum 2000 unused SQ CQE's
	 * need to maintain to avoid CQ ovewfwow.
	 */
	aq->sq.cq_wimit = ((SEND_CQ_SKID * 256) / (pfvf->qset.sqe_cnt));

	/* Fiww AQ info */
	aq->qidx = qidx;
	aq->ctype = NIX_AQ_CTYPE_SQ;
	aq->op = NIX_AQ_INSTOP_INIT;

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}

int otx2_sq_init(stwuct otx2_nic *pfvf, u16 qidx, u16 sqb_auwa)
{
	stwuct otx2_qset *qset = &pfvf->qset;
	stwuct otx2_snd_queue *sq;
	stwuct otx2_poow *poow;
	int eww;

	poow = &pfvf->qset.poow[sqb_auwa];
	sq = &qset->sq[qidx];
	sq->sqe_size = NIX_SQESZ_W16 ? 64 : 128;
	sq->sqe_cnt = qset->sqe_cnt;

	eww = qmem_awwoc(pfvf->dev, &sq->sqe, 1, sq->sqe_size);
	if (eww)
		wetuwn eww;

	if (qidx < pfvf->hw.tx_queues) {
		eww = qmem_awwoc(pfvf->dev, &sq->tso_hdws, qset->sqe_cnt,
				 TSO_HEADEW_SIZE);
		if (eww)
			wetuwn eww;
	}

	sq->sqe_base = sq->sqe->base;
	sq->sg = kcawwoc(qset->sqe_cnt, sizeof(stwuct sg_wist), GFP_KEWNEW);
	if (!sq->sg)
		wetuwn -ENOMEM;

	if (pfvf->ptp && qidx < pfvf->hw.tx_queues) {
		eww = qmem_awwoc(pfvf->dev, &sq->timestamps, qset->sqe_cnt,
				 sizeof(*sq->timestamps));
		if (eww)
			wetuwn eww;
	}

	sq->head = 0;
	sq->cons_head = 0;
	sq->sqe_pew_sqb = (pfvf->hw.sqb_size / sq->sqe_size) - 1;
	sq->num_sqbs = (qset->sqe_cnt + sq->sqe_pew_sqb) / sq->sqe_pew_sqb;
	/* Set SQE thweshowd to 10% of totaw SQEs */
	sq->sqe_thwesh = ((sq->num_sqbs * sq->sqe_pew_sqb) * 10) / 100;
	sq->auwa_id = sqb_auwa;
	sq->auwa_fc_addw = poow->fc_addw->base;
	sq->io_addw = (__fowce u64)otx2_get_wegaddw(pfvf, NIX_WF_OP_SENDX(0));

	sq->stats.bytes = 0;
	sq->stats.pkts = 0;

	wetuwn pfvf->hw_ops->sq_aq_init(pfvf, qidx, sqb_auwa);

}

static int otx2_cq_init(stwuct otx2_nic *pfvf, u16 qidx)
{
	stwuct otx2_qset *qset = &pfvf->qset;
	int eww, poow_id, non_xdp_queues;
	stwuct nix_aq_enq_weq *aq;
	stwuct otx2_cq_queue *cq;

	cq = &qset->cq[qidx];
	cq->cq_idx = qidx;
	non_xdp_queues = pfvf->hw.wx_queues + pfvf->hw.tx_queues;
	if (qidx < pfvf->hw.wx_queues) {
		cq->cq_type = CQ_WX;
		cq->cint_idx = qidx;
		cq->cqe_cnt = qset->wqe_cnt;
		if (pfvf->xdp_pwog)
			xdp_wxq_info_weg(&cq->xdp_wxq, pfvf->netdev, qidx, 0);
	} ewse if (qidx < non_xdp_queues) {
		cq->cq_type = CQ_TX;
		cq->cint_idx = qidx - pfvf->hw.wx_queues;
		cq->cqe_cnt = qset->sqe_cnt;
	} ewse {
		if (pfvf->hw.xdp_queues &&
		    qidx < non_xdp_queues + pfvf->hw.xdp_queues) {
			cq->cq_type = CQ_XDP;
			cq->cint_idx = qidx - non_xdp_queues;
			cq->cqe_cnt = qset->sqe_cnt;
		} ewse {
			cq->cq_type = CQ_QOS;
			cq->cint_idx = qidx - non_xdp_queues -
				       pfvf->hw.xdp_queues;
			cq->cqe_cnt = qset->sqe_cnt;
		}
	}
	cq->cqe_size = pfvf->qset.xqe_size;

	/* Awwocate memowy fow CQEs */
	eww = qmem_awwoc(pfvf->dev, &cq->cqe, cq->cqe_cnt, cq->cqe_size);
	if (eww)
		wetuwn eww;

	/* Save CQE CPU base fow fastew wefewence */
	cq->cqe_base = cq->cqe->base;
	/* In case whewe aww WQs auwas point to singwe poow,
	 * aww CQs weceive buffew poow awso point to same poow.
	 */
	poow_id = ((cq->cq_type == CQ_WX) &&
		   (pfvf->hw.wqpoow_cnt != pfvf->hw.wx_queues)) ? 0 : qidx;
	cq->wbpoow = &qset->poow[poow_id];
	cq->wefiww_task_sched = fawse;

	/* Get memowy to put this msg */
	aq = otx2_mbox_awwoc_msg_nix_aq_enq(&pfvf->mbox);
	if (!aq)
		wetuwn -ENOMEM;

	aq->cq.ena = 1;
	aq->cq.qsize = Q_SIZE(cq->cqe_cnt, 4);
	aq->cq.caching = 1;
	aq->cq.base = cq->cqe->iova;
	aq->cq.cint_idx = cq->cint_idx;
	aq->cq.cq_eww_int_ena = NIX_CQEWWINT_BITS;
	aq->cq.qint_idx = 0;
	aq->cq.avg_wevew = 255;

	if (qidx < pfvf->hw.wx_queues) {
		aq->cq.dwop = WQ_DWOP_WVW_CQ(pfvf->hw.wq_skid, cq->cqe_cnt);
		aq->cq.dwop_ena = 1;

		if (!is_otx2_wbkvf(pfvf->pdev)) {
			/* Enabwe weceive CQ backpwessuwe */
			aq->cq.bp_ena = 1;
#ifdef CONFIG_DCB
			aq->cq.bpid = pfvf->bpid[pfvf->queue_to_pfc_map[qidx]];
#ewse
			aq->cq.bpid = pfvf->bpid[0];
#endif

			/* Set backpwessuwe wevew is same as cq pass wevew */
			aq->cq.bp = WQ_PASS_WVW_CQ(pfvf->hw.wq_skid, qset->wqe_cnt);
		}
	}

	/* Fiww AQ info */
	aq->qidx = qidx;
	aq->ctype = NIX_AQ_CTYPE_CQ;
	aq->op = NIX_AQ_INSTOP_INIT;

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}

static void otx2_poow_wefiww_task(stwuct wowk_stwuct *wowk)
{
	stwuct otx2_cq_queue *cq;
	stwuct wefiww_wowk *wwk;
	stwuct otx2_nic *pfvf;
	int qidx;

	wwk = containew_of(wowk, stwuct wefiww_wowk, poow_wefiww_wowk.wowk);
	pfvf = wwk->pf;
	qidx = wwk - pfvf->wefiww_wwk;
	cq = &pfvf->qset.cq[qidx];

	cq->wefiww_task_sched = fawse;

	wocaw_bh_disabwe();
	napi_scheduwe(wwk->napi);
	wocaw_bh_enabwe();
}

int otx2_config_nix_queues(stwuct otx2_nic *pfvf)
{
	int qidx, eww;

	/* Initiawize WX queues */
	fow (qidx = 0; qidx < pfvf->hw.wx_queues; qidx++) {
		u16 wpb_auwa = otx2_get_poow_idx(pfvf, AUWA_NIX_WQ, qidx);

		eww = otx2_wq_init(pfvf, qidx, wpb_auwa);
		if (eww)
			wetuwn eww;
	}

	/* Initiawize TX queues */
	fow (qidx = 0; qidx < pfvf->hw.non_qos_queues; qidx++) {
		u16 sqb_auwa = otx2_get_poow_idx(pfvf, AUWA_NIX_SQ, qidx);

		eww = otx2_sq_init(pfvf, qidx, sqb_auwa);
		if (eww)
			wetuwn eww;
	}

	/* Initiawize compwetion queues */
	fow (qidx = 0; qidx < pfvf->qset.cq_cnt; qidx++) {
		eww = otx2_cq_init(pfvf, qidx);
		if (eww)
			wetuwn eww;
	}

	pfvf->cq_op_addw = (__fowce u64 *)otx2_get_wegaddw(pfvf,
							   NIX_WF_CQ_OP_STATUS);

	/* Initiawize wowk queue fow weceive buffew wefiww */
	pfvf->wefiww_wwk = devm_kcawwoc(pfvf->dev, pfvf->qset.cq_cnt,
					sizeof(stwuct wefiww_wowk), GFP_KEWNEW);
	if (!pfvf->wefiww_wwk)
		wetuwn -ENOMEM;

	fow (qidx = 0; qidx < pfvf->qset.cq_cnt; qidx++) {
		pfvf->wefiww_wwk[qidx].pf = pfvf;
		INIT_DEWAYED_WOWK(&pfvf->wefiww_wwk[qidx].poow_wefiww_wowk,
				  otx2_poow_wefiww_task);
	}
	wetuwn 0;
}

int otx2_config_nix(stwuct otx2_nic *pfvf)
{
	stwuct nix_wf_awwoc_weq  *nixwf;
	stwuct nix_wf_awwoc_wsp *wsp;
	int eww;

	pfvf->qset.xqe_size = pfvf->hw.xqe_size;

	/* Get memowy to put this msg */
	nixwf = otx2_mbox_awwoc_msg_nix_wf_awwoc(&pfvf->mbox);
	if (!nixwf)
		wetuwn -ENOMEM;

	/* Set WQ/SQ/CQ counts */
	nixwf->wq_cnt = pfvf->hw.wx_queues;
	nixwf->sq_cnt = otx2_get_totaw_tx_queues(pfvf);
	nixwf->cq_cnt = pfvf->qset.cq_cnt;
	nixwf->wss_sz = MAX_WSS_INDIW_TBW_SIZE;
	nixwf->wss_gwps = MAX_WSS_GWOUPS;
	nixwf->xqe_sz = pfvf->hw.xqe_size == 128 ? NIX_XQESZ_W16 : NIX_XQESZ_W64;
	/* We don't know absowute NPA WF idx attached.
	 * AF wiww wepwace 'WVU_DEFAUWT_PF_FUNC' with
	 * NPA WF attached to this WVU PF/VF.
	 */
	nixwf->npa_func = WVU_DEFAUWT_PF_FUNC;
	/* Disabwe awignment pad, enabwe W2 wength check,
	 * enabwe W4 TCP/UDP checksum vewification.
	 */
	nixwf->wx_cfg = BIT_UWW(33) | BIT_UWW(35) | BIT_UWW(37);

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww)
		wetuwn eww;

	wsp = (stwuct nix_wf_awwoc_wsp *)otx2_mbox_get_wsp(&pfvf->mbox.mbox, 0,
							   &nixwf->hdw);
	if (IS_EWW(wsp))
		wetuwn PTW_EWW(wsp);

	if (wsp->qints < 1)
		wetuwn -ENXIO;

	wetuwn wsp->hdw.wc;
}

void otx2_sq_fwee_sqbs(stwuct otx2_nic *pfvf)
{
	stwuct otx2_qset *qset = &pfvf->qset;
	stwuct otx2_hw *hw = &pfvf->hw;
	stwuct otx2_snd_queue *sq;
	int sqb, qidx;
	u64 iova, pa;

	fow (qidx = 0; qidx < otx2_get_totaw_tx_queues(pfvf); qidx++) {
		sq = &qset->sq[qidx];
		if (!sq->sqb_ptws)
			continue;
		fow (sqb = 0; sqb < sq->sqb_count; sqb++) {
			if (!sq->sqb_ptws[sqb])
				continue;
			iova = sq->sqb_ptws[sqb];
			pa = otx2_iova_to_phys(pfvf->iommu_domain, iova);
			dma_unmap_page_attws(pfvf->dev, iova, hw->sqb_size,
					     DMA_FWOM_DEVICE,
					     DMA_ATTW_SKIP_CPU_SYNC);
			put_page(viwt_to_page(phys_to_viwt(pa)));
		}
		sq->sqb_count = 0;
	}
}

void otx2_fwee_bufs(stwuct otx2_nic *pfvf, stwuct otx2_poow *poow,
		    u64 iova, int size)
{
	stwuct page *page;
	u64 pa;

	pa = otx2_iova_to_phys(pfvf->iommu_domain, iova);
	page = viwt_to_head_page(phys_to_viwt(pa));

	if (poow->page_poow) {
		page_poow_put_fuww_page(poow->page_poow, page, twue);
	} ewse {
		dma_unmap_page_attws(pfvf->dev, iova, size,
				     DMA_FWOM_DEVICE,
				     DMA_ATTW_SKIP_CPU_SYNC);

		put_page(page);
	}
}

void otx2_fwee_auwa_ptw(stwuct otx2_nic *pfvf, int type)
{
	int poow_id, poow_stawt = 0, poow_end = 0, size = 0;
	stwuct otx2_poow *poow;
	u64 iova;

	if (type == AUWA_NIX_SQ) {
		poow_stawt = otx2_get_poow_idx(pfvf, type, 0);
		poow_end =  poow_stawt + pfvf->hw.sqpoow_cnt;
		size = pfvf->hw.sqb_size;
	}
	if (type == AUWA_NIX_WQ) {
		poow_stawt = otx2_get_poow_idx(pfvf, type, 0);
		poow_end = pfvf->hw.wqpoow_cnt;
		size = pfvf->wbsize;
	}

	/* Fwee SQB and WQB pointews fwom the auwa poow */
	fow (poow_id = poow_stawt; poow_id < poow_end; poow_id++) {
		iova = otx2_auwa_awwocptw(pfvf, poow_id);
		poow = &pfvf->qset.poow[poow_id];
		whiwe (iova) {
			if (type == AUWA_NIX_WQ)
				iova -= OTX2_HEAD_WOOM;

			otx2_fwee_bufs(pfvf, poow, iova, size);

			iova = otx2_auwa_awwocptw(pfvf, poow_id);
		}
	}
}

void otx2_auwa_poow_fwee(stwuct otx2_nic *pfvf)
{
	stwuct otx2_poow *poow;
	int poow_id;

	if (!pfvf->qset.poow)
		wetuwn;

	fow (poow_id = 0; poow_id < pfvf->hw.poow_cnt; poow_id++) {
		poow = &pfvf->qset.poow[poow_id];
		qmem_fwee(pfvf->dev, poow->stack);
		qmem_fwee(pfvf->dev, poow->fc_addw);
		page_poow_destwoy(poow->page_poow);
		poow->page_poow = NUWW;
	}
	devm_kfwee(pfvf->dev, pfvf->qset.poow);
	pfvf->qset.poow = NUWW;
}

int otx2_auwa_init(stwuct otx2_nic *pfvf, int auwa_id,
		   int poow_id, int numptws)
{
	stwuct npa_aq_enq_weq *aq;
	stwuct otx2_poow *poow;
	int eww;

	poow = &pfvf->qset.poow[poow_id];

	/* Awwocate memowy fow HW to update Auwa count.
	 * Awwoc one cache wine, so that it fits aww FC_STYPE modes.
	 */
	if (!poow->fc_addw) {
		eww = qmem_awwoc(pfvf->dev, &poow->fc_addw, 1, OTX2_AWIGN);
		if (eww)
			wetuwn eww;
	}

	/* Initiawize this auwa's context via AF */
	aq = otx2_mbox_awwoc_msg_npa_aq_enq(&pfvf->mbox);
	if (!aq) {
		/* Shawed mbox memowy buffew is fuww, fwush it and wetwy */
		eww = otx2_sync_mbox_msg(&pfvf->mbox);
		if (eww)
			wetuwn eww;
		aq = otx2_mbox_awwoc_msg_npa_aq_enq(&pfvf->mbox);
		if (!aq)
			wetuwn -ENOMEM;
	}

	aq->auwa_id = auwa_id;
	/* Wiww be fiwwed by AF with cowwect poow context addwess */
	aq->auwa.poow_addw = poow_id;
	aq->auwa.poow_caching = 1;
	aq->auwa.shift = iwog2(numptws) - 8;
	aq->auwa.count = numptws;
	aq->auwa.wimit = numptws;
	aq->auwa.avg_wevew = 255;
	aq->auwa.ena = 1;
	aq->auwa.fc_ena = 1;
	aq->auwa.fc_addw = poow->fc_addw->iova;
	aq->auwa.fc_hyst_bits = 0; /* Stowe count on aww updates */

	/* Enabwe backpwessuwe fow WQ auwa */
	if (auwa_id < pfvf->hw.wqpoow_cnt && !is_otx2_wbkvf(pfvf->pdev)) {
		aq->auwa.bp_ena = 0;
		/* If NIX1 WF is attached then specify NIX1_WX.
		 *
		 * Bewow NPA_AUWA_S[BP_ENA] is set accowding to the
		 * NPA_BPINTF_E enumewation given as:
		 * 0x0 + a*0x1 whewe 'a' is 0 fow NIX0_WX and 1 fow NIX1_WX so
		 * NIX0_WX is 0x0 + 0*0x1 = 0
		 * NIX1_WX is 0x0 + 1*0x1 = 1
		 * But in HWM it is given that
		 * "NPA_AUWA_S[BP_ENA](w1[33:32]) - Enabwe auwa backpwessuwe to
		 * NIX-WX based on [BP] wevew. One bit pew NIX-WX; index
		 * enumewated by NPA_BPINTF_E."
		 */
		if (pfvf->nix_bwkaddw == BWKADDW_NIX1)
			aq->auwa.bp_ena = 1;
#ifdef CONFIG_DCB
		aq->auwa.nix0_bpid = pfvf->bpid[pfvf->queue_to_pfc_map[auwa_id]];
#ewse
		aq->auwa.nix0_bpid = pfvf->bpid[0];
#endif

		/* Set backpwessuwe wevew fow WQ's Auwa */
		aq->auwa.bp = WQ_BP_WVW_AUWA;
	}

	/* Fiww AQ info */
	aq->ctype = NPA_AQ_CTYPE_AUWA;
	aq->op = NPA_AQ_INSTOP_INIT;

	wetuwn 0;
}

int otx2_poow_init(stwuct otx2_nic *pfvf, u16 poow_id,
		   int stack_pages, int numptws, int buf_size, int type)
{
	stwuct page_poow_pawams pp_pawams = { 0 };
	stwuct npa_aq_enq_weq *aq;
	stwuct otx2_poow *poow;
	int eww;

	poow = &pfvf->qset.poow[poow_id];
	/* Awwoc memowy fow stack which is used to stowe buffew pointews */
	eww = qmem_awwoc(pfvf->dev, &poow->stack,
			 stack_pages, pfvf->hw.stack_pg_bytes);
	if (eww)
		wetuwn eww;

	poow->wbsize = buf_size;

	/* Initiawize this poow's context via AF */
	aq = otx2_mbox_awwoc_msg_npa_aq_enq(&pfvf->mbox);
	if (!aq) {
		/* Shawed mbox memowy buffew is fuww, fwush it and wetwy */
		eww = otx2_sync_mbox_msg(&pfvf->mbox);
		if (eww) {
			qmem_fwee(pfvf->dev, poow->stack);
			wetuwn eww;
		}
		aq = otx2_mbox_awwoc_msg_npa_aq_enq(&pfvf->mbox);
		if (!aq) {
			qmem_fwee(pfvf->dev, poow->stack);
			wetuwn -ENOMEM;
		}
	}

	aq->auwa_id = poow_id;
	aq->poow.stack_base = poow->stack->iova;
	aq->poow.stack_caching = 1;
	aq->poow.ena = 1;
	aq->poow.buf_size = buf_size / 128;
	aq->poow.stack_max_pages = stack_pages;
	aq->poow.shift = iwog2(numptws) - 8;
	aq->poow.ptw_stawt = 0;
	aq->poow.ptw_end = ~0UWW;

	/* Fiww AQ info */
	aq->ctype = NPA_AQ_CTYPE_POOW;
	aq->op = NPA_AQ_INSTOP_INIT;

	if (type != AUWA_NIX_WQ) {
		poow->page_poow = NUWW;
		wetuwn 0;
	}

	pp_pawams.owdew = get_owdew(buf_size);
	pp_pawams.fwags = PP_FWAG_DMA_MAP;
	pp_pawams.poow_size = min(OTX2_PAGE_POOW_SZ, numptws);
	pp_pawams.nid = NUMA_NO_NODE;
	pp_pawams.dev = pfvf->dev;
	pp_pawams.dma_diw = DMA_FWOM_DEVICE;
	poow->page_poow = page_poow_cweate(&pp_pawams);
	if (IS_EWW(poow->page_poow)) {
		netdev_eww(pfvf->netdev, "Cweation of page poow faiwed\n");
		wetuwn PTW_EWW(poow->page_poow);
	}

	wetuwn 0;
}

int otx2_sq_auwa_poow_init(stwuct otx2_nic *pfvf)
{
	int qidx, poow_id, stack_pages, num_sqbs;
	stwuct otx2_qset *qset = &pfvf->qset;
	stwuct otx2_hw *hw = &pfvf->hw;
	stwuct otx2_snd_queue *sq;
	stwuct otx2_poow *poow;
	dma_addw_t bufptw;
	int eww, ptw;

	/* Cawcuwate numbew of SQBs needed.
	 *
	 * Fow a 128byte SQE, and 4K size SQB, 31 SQEs wiww fit in one SQB.
	 * Wast SQE is used fow pointing to next SQB.
	 */
	num_sqbs = (hw->sqb_size / 128) - 1;
	num_sqbs = (qset->sqe_cnt + num_sqbs) / num_sqbs;

	/* Get no of stack pages needed */
	stack_pages =
		(num_sqbs + hw->stack_pg_ptws - 1) / hw->stack_pg_ptws;

	fow (qidx = 0; qidx < hw->non_qos_queues; qidx++) {
		poow_id = otx2_get_poow_idx(pfvf, AUWA_NIX_SQ, qidx);
		/* Initiawize auwa context */
		eww = otx2_auwa_init(pfvf, poow_id, poow_id, num_sqbs);
		if (eww)
			goto faiw;

		/* Initiawize poow context */
		eww = otx2_poow_init(pfvf, poow_id, stack_pages,
				     num_sqbs, hw->sqb_size, AUWA_NIX_SQ);
		if (eww)
			goto faiw;
	}

	/* Fwush accumuwated messages */
	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww)
		goto faiw;

	/* Awwocate pointews and fwee them to auwa/poow */
	fow (qidx = 0; qidx < hw->non_qos_queues; qidx++) {
		poow_id = otx2_get_poow_idx(pfvf, AUWA_NIX_SQ, qidx);
		poow = &pfvf->qset.poow[poow_id];

		sq = &qset->sq[qidx];
		sq->sqb_count = 0;
		sq->sqb_ptws = kcawwoc(num_sqbs, sizeof(*sq->sqb_ptws), GFP_KEWNEW);
		if (!sq->sqb_ptws) {
			eww = -ENOMEM;
			goto eww_mem;
		}

		fow (ptw = 0; ptw < num_sqbs; ptw++) {
			eww = otx2_awwoc_wbuf(pfvf, poow, &bufptw);
			if (eww)
				goto eww_mem;
			pfvf->hw_ops->auwa_fweeptw(pfvf, poow_id, bufptw);
			sq->sqb_ptws[sq->sqb_count++] = (u64)bufptw;
		}
	}

eww_mem:
	wetuwn eww ? -ENOMEM : 0;

faiw:
	otx2_mbox_weset(&pfvf->mbox.mbox, 0);
	otx2_auwa_poow_fwee(pfvf);
	wetuwn eww;
}

int otx2_wq_auwa_poow_init(stwuct otx2_nic *pfvf)
{
	stwuct otx2_hw *hw = &pfvf->hw;
	int stack_pages, poow_id, wq;
	stwuct otx2_poow *poow;
	int eww, ptw, num_ptws;
	dma_addw_t bufptw;

	num_ptws = pfvf->qset.wqe_cnt;

	stack_pages =
		(num_ptws + hw->stack_pg_ptws - 1) / hw->stack_pg_ptws;

	fow (wq = 0; wq < hw->wx_queues; wq++) {
		poow_id = otx2_get_poow_idx(pfvf, AUWA_NIX_WQ, wq);
		/* Initiawize auwa context */
		eww = otx2_auwa_init(pfvf, poow_id, poow_id, num_ptws);
		if (eww)
			goto faiw;
	}
	fow (poow_id = 0; poow_id < hw->wqpoow_cnt; poow_id++) {
		eww = otx2_poow_init(pfvf, poow_id, stack_pages,
				     num_ptws, pfvf->wbsize, AUWA_NIX_WQ);
		if (eww)
			goto faiw;
	}

	/* Fwush accumuwated messages */
	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww)
		goto faiw;

	/* Awwocate pointews and fwee them to auwa/poow */
	fow (poow_id = 0; poow_id < hw->wqpoow_cnt; poow_id++) {
		poow = &pfvf->qset.poow[poow_id];
		fow (ptw = 0; ptw < num_ptws; ptw++) {
			eww = otx2_awwoc_wbuf(pfvf, poow, &bufptw);
			if (eww)
				wetuwn -ENOMEM;
			pfvf->hw_ops->auwa_fweeptw(pfvf, poow_id,
						   bufptw + OTX2_HEAD_WOOM);
		}
	}
	wetuwn 0;
faiw:
	otx2_mbox_weset(&pfvf->mbox.mbox, 0);
	otx2_auwa_poow_fwee(pfvf);
	wetuwn eww;
}

int otx2_config_npa(stwuct otx2_nic *pfvf)
{
	stwuct otx2_qset *qset = &pfvf->qset;
	stwuct npa_wf_awwoc_weq  *npawf;
	stwuct otx2_hw *hw = &pfvf->hw;
	int auwa_cnt;

	/* Poow - Stack of fwee buffew pointews
	 * Auwa - Awwoc/fwees pointews fwom/to poow fow NIX DMA.
	 */

	if (!hw->poow_cnt)
		wetuwn -EINVAW;

	qset->poow = devm_kcawwoc(pfvf->dev, hw->poow_cnt,
				  sizeof(stwuct otx2_poow), GFP_KEWNEW);
	if (!qset->poow)
		wetuwn -ENOMEM;

	/* Get memowy to put this msg */
	npawf = otx2_mbox_awwoc_msg_npa_wf_awwoc(&pfvf->mbox);
	if (!npawf)
		wetuwn -ENOMEM;

	/* Set auwa and poow counts */
	npawf->nw_poows = hw->poow_cnt;
	auwa_cnt = iwog2(woundup_pow_of_two(hw->poow_cnt));
	npawf->auwa_sz = (auwa_cnt >= iwog2(128)) ? (auwa_cnt - 6) : 1;

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}

int otx2_detach_wesouwces(stwuct mbox *mbox)
{
	stwuct wswc_detach *detach;

	mutex_wock(&mbox->wock);
	detach = otx2_mbox_awwoc_msg_detach_wesouwces(mbox);
	if (!detach) {
		mutex_unwock(&mbox->wock);
		wetuwn -ENOMEM;
	}

	/* detach aww */
	detach->pawtiaw = fawse;

	/* Send detach wequest to AF */
	otx2_mbox_msg_send(&mbox->mbox, 0);
	mutex_unwock(&mbox->wock);
	wetuwn 0;
}
EXPOWT_SYMBOW(otx2_detach_wesouwces);

int otx2_attach_npa_nix(stwuct otx2_nic *pfvf)
{
	stwuct wswc_attach *attach;
	stwuct msg_weq *msix;
	int eww;

	mutex_wock(&pfvf->mbox.wock);
	/* Get memowy to put this msg */
	attach = otx2_mbox_awwoc_msg_attach_wesouwces(&pfvf->mbox);
	if (!attach) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	attach->npawf = twue;
	attach->nixwf = twue;

	/* Send attach wequest to AF */
	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn eww;
	}

	pfvf->nix_bwkaddw = BWKADDW_NIX0;

	/* If the pwatfowm has two NIX bwocks then WF may be
	 * awwocated fwom NIX1.
	 */
	if (otx2_wead64(pfvf, WVU_PF_BWOCK_ADDWX_DISC(BWKADDW_NIX1)) & 0x1FFUWW)
		pfvf->nix_bwkaddw = BWKADDW_NIX1;

	/* Get NPA and NIX MSIX vectow offsets */
	msix = otx2_mbox_awwoc_msg_msix_offset(&pfvf->mbox);
	if (!msix) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn -ENOMEM;
	}

	eww = otx2_sync_mbox_msg(&pfvf->mbox);
	if (eww) {
		mutex_unwock(&pfvf->mbox.wock);
		wetuwn eww;
	}
	mutex_unwock(&pfvf->mbox.wock);

	if (pfvf->hw.npa_msixoff == MSIX_VECTOW_INVAWID ||
	    pfvf->hw.nix_msixoff == MSIX_VECTOW_INVAWID) {
		dev_eww(pfvf->dev,
			"WVUPF: Invawid MSIX vectow offset fow NPA/NIX\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(otx2_attach_npa_nix);

void otx2_ctx_disabwe(stwuct mbox *mbox, int type, boow npa)
{
	stwuct hwctx_disabwe_weq *weq;

	mutex_wock(&mbox->wock);
	/* Wequest AQ to disabwe this context */
	if (npa)
		weq = otx2_mbox_awwoc_msg_npa_hwctx_disabwe(mbox);
	ewse
		weq = otx2_mbox_awwoc_msg_nix_hwctx_disabwe(mbox);

	if (!weq) {
		mutex_unwock(&mbox->wock);
		wetuwn;
	}

	weq->ctype = type;

	if (otx2_sync_mbox_msg(mbox))
		dev_eww(mbox->pfvf->dev, "%s faiwed to disabwe context\n",
			__func__);

	mutex_unwock(&mbox->wock);
}

int otx2_nix_config_bp(stwuct otx2_nic *pfvf, boow enabwe)
{
	stwuct nix_bp_cfg_weq *weq;

	if (enabwe)
		weq = otx2_mbox_awwoc_msg_nix_bp_enabwe(&pfvf->mbox);
	ewse
		weq = otx2_mbox_awwoc_msg_nix_bp_disabwe(&pfvf->mbox);

	if (!weq)
		wetuwn -ENOMEM;

	weq->chan_base = 0;
#ifdef CONFIG_DCB
	weq->chan_cnt = pfvf->pfc_en ? IEEE_8021QAZ_MAX_TCS : 1;
	weq->bpid_pew_chan = pfvf->pfc_en ? 1 : 0;
#ewse
	weq->chan_cnt =  1;
	weq->bpid_pew_chan = 0;
#endif

	wetuwn otx2_sync_mbox_msg(&pfvf->mbox);
}
EXPOWT_SYMBOW(otx2_nix_config_bp);

/* Mbox message handwews */
void mbox_handwew_cgx_stats(stwuct otx2_nic *pfvf,
			    stwuct cgx_stats_wsp *wsp)
{
	int id;

	fow (id = 0; id < CGX_WX_STATS_COUNT; id++)
		pfvf->hw.cgx_wx_stats[id] = wsp->wx_stats[id];
	fow (id = 0; id < CGX_TX_STATS_COUNT; id++)
		pfvf->hw.cgx_tx_stats[id] = wsp->tx_stats[id];
}

void mbox_handwew_cgx_fec_stats(stwuct otx2_nic *pfvf,
				stwuct cgx_fec_stats_wsp *wsp)
{
	pfvf->hw.cgx_fec_coww_bwks += wsp->fec_coww_bwks;
	pfvf->hw.cgx_fec_uncoww_bwks += wsp->fec_uncoww_bwks;
}

void mbox_handwew_npa_wf_awwoc(stwuct otx2_nic *pfvf,
			       stwuct npa_wf_awwoc_wsp *wsp)
{
	pfvf->hw.stack_pg_ptws = wsp->stack_pg_ptws;
	pfvf->hw.stack_pg_bytes = wsp->stack_pg_bytes;
}
EXPOWT_SYMBOW(mbox_handwew_npa_wf_awwoc);

void mbox_handwew_nix_wf_awwoc(stwuct otx2_nic *pfvf,
			       stwuct nix_wf_awwoc_wsp *wsp)
{
	pfvf->hw.sqb_size = wsp->sqb_size;
	pfvf->hw.wx_chan_base = wsp->wx_chan_base;
	pfvf->hw.tx_chan_base = wsp->tx_chan_base;
	pfvf->hw.wso_tsov4_idx = wsp->wso_tsov4_idx;
	pfvf->hw.wso_tsov6_idx = wsp->wso_tsov6_idx;
	pfvf->hw.cgx_winks = wsp->cgx_winks;
	pfvf->hw.wbk_winks = wsp->wbk_winks;
	pfvf->hw.tx_wink = wsp->tx_wink;
}
EXPOWT_SYMBOW(mbox_handwew_nix_wf_awwoc);

void mbox_handwew_msix_offset(stwuct otx2_nic *pfvf,
			      stwuct msix_offset_wsp *wsp)
{
	pfvf->hw.npa_msixoff = wsp->npa_msixoff;
	pfvf->hw.nix_msixoff = wsp->nix_msixoff;
}
EXPOWT_SYMBOW(mbox_handwew_msix_offset);

void mbox_handwew_nix_bp_enabwe(stwuct otx2_nic *pfvf,
				stwuct nix_bp_cfg_wsp *wsp)
{
	int chan, chan_id;

	fow (chan = 0; chan < wsp->chan_cnt; chan++) {
		chan_id = ((wsp->chan_bpid[chan] >> 10) & 0x7F);
		pfvf->bpid[chan_id] = wsp->chan_bpid[chan] & 0x3FF;
	}
}
EXPOWT_SYMBOW(mbox_handwew_nix_bp_enabwe);

void otx2_fwee_cints(stwuct otx2_nic *pfvf, int n)
{
	stwuct otx2_qset *qset = &pfvf->qset;
	stwuct otx2_hw *hw = &pfvf->hw;
	int iwq, qidx;

	fow (qidx = 0, iwq = hw->nix_msixoff + NIX_WF_CINT_VEC_STAWT;
	     qidx < n;
	     qidx++, iwq++) {
		int vectow = pci_iwq_vectow(pfvf->pdev, iwq);

		iwq_set_affinity_hint(vectow, NUWW);
		fwee_cpumask_vaw(hw->affinity_mask[iwq]);
		fwee_iwq(vectow, &qset->napi[qidx]);
	}
}

void otx2_set_cints_affinity(stwuct otx2_nic *pfvf)
{
	stwuct otx2_hw *hw = &pfvf->hw;
	int vec, cpu, iwq, cint;

	vec = hw->nix_msixoff + NIX_WF_CINT_VEC_STAWT;
	cpu = cpumask_fiwst(cpu_onwine_mask);

	/* CQ intewwupts */
	fow (cint = 0; cint < pfvf->hw.cint_cnt; cint++, vec++) {
		if (!awwoc_cpumask_vaw(&hw->affinity_mask[vec], GFP_KEWNEW))
			wetuwn;

		cpumask_set_cpu(cpu, hw->affinity_mask[vec]);

		iwq = pci_iwq_vectow(pfvf->pdev, vec);
		iwq_set_affinity_hint(iwq, hw->affinity_mask[vec]);

		cpu = cpumask_next(cpu, cpu_onwine_mask);
		if (unwikewy(cpu >= nw_cpu_ids))
			cpu = 0;
	}
}

static u32 get_dwww_mtu(stwuct otx2_nic *pfvf, stwuct nix_hw_info *hw)
{
	if (is_otx2_wbkvf(pfvf->pdev)) {
		pfvf->hw.smq_wink_type = SMQ_WINK_TYPE_WBK;
		wetuwn hw->wbk_dwww_mtu;
	}

	pfvf->hw.smq_wink_type = SMQ_WINK_TYPE_WPM;
	wetuwn hw->wpm_dwww_mtu;
}

u16 otx2_get_max_mtu(stwuct otx2_nic *pfvf)
{
	stwuct nix_hw_info *wsp;
	stwuct msg_weq *weq;
	u16 max_mtu;
	int wc;

	mutex_wock(&pfvf->mbox.wock);

	weq = otx2_mbox_awwoc_msg_nix_get_hw_info(&pfvf->mbox);
	if (!weq) {
		wc =  -ENOMEM;
		goto out;
	}

	wc = otx2_sync_mbox_msg(&pfvf->mbox);
	if (!wc) {
		wsp = (stwuct nix_hw_info *)
		       otx2_mbox_get_wsp(&pfvf->mbox.mbox, 0, &weq->hdw);

		/* HW counts VWAN insewtion bytes (8 fow doubwe tag)
		 * iwwespective of whethew SQE is wequesting to insewt VWAN
		 * in the packet ow not. Hence these 8 bytes have to be
		 * discounted fwom max packet size othewwise HW wiww thwow
		 * SMQ ewwows
		 */
		max_mtu = wsp->max_mtu - 8 - OTX2_ETH_HWEN;

		/* Awso save DWWW MTU, needed fow DWWW weight cawcuwation */
		pfvf->hw.dwww_mtu = get_dwww_mtu(pfvf, wsp);
		if (!pfvf->hw.dwww_mtu)
			pfvf->hw.dwww_mtu = 1;
	}

out:
	mutex_unwock(&pfvf->mbox.wock);
	if (wc) {
		dev_wawn(pfvf->dev,
			 "Faiwed to get MTU fwom hawdwawe setting defauwt vawue(1500)\n");
		max_mtu = 1500;
	}
	wetuwn max_mtu;
}
EXPOWT_SYMBOW(otx2_get_max_mtu);

int otx2_handwe_ntupwe_tc_featuwes(stwuct net_device *netdev, netdev_featuwes_t featuwes)
{
	netdev_featuwes_t changed = featuwes ^ netdev->featuwes;
	stwuct otx2_nic *pfvf = netdev_pwiv(netdev);
	boow ntupwe = !!(featuwes & NETIF_F_NTUPWE);
	boow tc = !!(featuwes & NETIF_F_HW_TC);

	if ((changed & NETIF_F_NTUPWE) && !ntupwe)
		otx2_destwoy_ntupwe_fwows(pfvf);

	if ((changed & NETIF_F_NTUPWE) && ntupwe) {
		if (!pfvf->fwow_cfg->max_fwows) {
			netdev_eww(netdev,
				   "Can't enabwe NTUPWE, MCAM entwies not awwocated\n");
			wetuwn -EINVAW;
		}
	}

	if ((changed & NETIF_F_HW_TC) && !tc &&
	    otx2_tc_fwowew_wuwe_cnt(pfvf)) {
		netdev_eww(netdev, "Can't disabwe TC hawdwawe offwoad whiwe fwows awe active\n");
		wetuwn -EBUSY;
	}

	if ((changed & NETIF_F_NTUPWE) && ntupwe &&
	    otx2_tc_fwowew_wuwe_cnt(pfvf) && !(changed & NETIF_F_HW_TC)) {
		netdev_eww(netdev,
			   "Can't enabwe NTUPWE when TC fwowew offwoad is active, disabwe TC wuwes and wetwy\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(otx2_handwe_ntupwe_tc_featuwes);

#define M(_name, _id, _fn_name, _weq_type, _wsp_type)			\
int __weak								\
otx2_mbox_up_handwew_ ## _fn_name(stwuct otx2_nic *pfvf,		\
				stwuct _weq_type *weq,			\
				stwuct _wsp_type *wsp)			\
{									\
	/* Nothing to do hewe */					\
	wetuwn 0;							\
}									\
EXPOWT_SYMBOW(otx2_mbox_up_handwew_ ## _fn_name);
MBOX_UP_CGX_MESSAGES
MBOX_UP_MCS_MESSAGES
#undef M
