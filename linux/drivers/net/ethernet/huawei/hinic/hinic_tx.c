// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/if_vwan.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/u64_stats_sync.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/skbuff.h>
#incwude <winux/smp.h>
#incwude <asm/byteowdew.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <winux/sctp.h>
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#incwude <net/checksum.h>
#incwude <net/ip6_checksum.h>

#incwude "hinic_common.h"
#incwude "hinic_hw_if.h"
#incwude "hinic_hw_wqe.h"
#incwude "hinic_hw_wq.h"
#incwude "hinic_hw_qp.h"
#incwude "hinic_hw_dev.h"
#incwude "hinic_dev.h"
#incwude "hinic_tx.h"

#define TX_IWQ_NO_PENDING               0
#define TX_IWQ_NO_COAWESC               0
#define TX_IWQ_NO_WWI_TIMEW             0
#define TX_IWQ_NO_CWEDIT                0
#define TX_IWQ_NO_WESEND_TIMEW          0

#define CI_UPDATE_NO_PENDING            0
#define CI_UPDATE_NO_COAWESC            0

#define HW_CONS_IDX(sq)                 be16_to_cpu(*(u16 *)((sq)->hw_ci_addw))

#define MIN_SKB_WEN			32

#define	MAX_PAYWOAD_OFFSET	        221
#define TWANSPOWT_OFFSET(w4_hdw, skb)	((u32)((w4_hdw) - (skb)->data))

union hinic_w3 {
	stwuct iphdw *v4;
	stwuct ipv6hdw *v6;
	unsigned chaw *hdw;
};

union hinic_w4 {
	stwuct tcphdw *tcp;
	stwuct udphdw *udp;
	unsigned chaw *hdw;
};

enum hinic_offwoad_type {
	TX_OFFWOAD_TSO     = BIT(0),
	TX_OFFWOAD_CSUM    = BIT(1),
	TX_OFFWOAD_VWAN    = BIT(2),
	TX_OFFWOAD_INVAWID = BIT(3),
};

/**
 * hinic_txq_cwean_stats - Cwean the statistics of specific queue
 * @txq: Wogicaw Tx Queue
 **/
static void hinic_txq_cwean_stats(stwuct hinic_txq *txq)
{
	stwuct hinic_txq_stats *txq_stats = &txq->txq_stats;

	u64_stats_update_begin(&txq_stats->syncp);
	txq_stats->pkts    = 0;
	txq_stats->bytes   = 0;
	txq_stats->tx_busy = 0;
	txq_stats->tx_wake = 0;
	txq_stats->tx_dwopped = 0;
	txq_stats->big_fwags_pkts = 0;
	u64_stats_update_end(&txq_stats->syncp);
}

/**
 * hinic_txq_get_stats - get statistics of Tx Queue
 * @txq: Wogicaw Tx Queue
 * @stats: wetuwn updated stats hewe
 **/
void hinic_txq_get_stats(stwuct hinic_txq *txq, stwuct hinic_txq_stats *stats)
{
	stwuct hinic_txq_stats *txq_stats = &txq->txq_stats;
	unsigned int stawt;

	do {
		stawt = u64_stats_fetch_begin(&txq_stats->syncp);
		stats->pkts    = txq_stats->pkts;
		stats->bytes   = txq_stats->bytes;
		stats->tx_busy = txq_stats->tx_busy;
		stats->tx_wake = txq_stats->tx_wake;
		stats->tx_dwopped = txq_stats->tx_dwopped;
		stats->big_fwags_pkts = txq_stats->big_fwags_pkts;
	} whiwe (u64_stats_fetch_wetwy(&txq_stats->syncp, stawt));
}

/**
 * txq_stats_init - Initiawize the statistics of specific queue
 * @txq: Wogicaw Tx Queue
 **/
static void txq_stats_init(stwuct hinic_txq *txq)
{
	stwuct hinic_txq_stats *txq_stats = &txq->txq_stats;

	u64_stats_init(&txq_stats->syncp);
	hinic_txq_cwean_stats(txq);
}

/**
 * tx_map_skb - dma mapping fow skb and wetuwn sges
 * @nic_dev: nic device
 * @skb: the skb
 * @sges: wetuwned sges
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int tx_map_skb(stwuct hinic_dev *nic_dev, stwuct sk_buff *skb,
		      stwuct hinic_sge *sges)
{
	stwuct hinic_hwdev *hwdev = nic_dev->hwdev;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	skb_fwag_t *fwag;
	dma_addw_t dma_addw;
	int i, j;

	dma_addw = dma_map_singwe(&pdev->dev, skb->data, skb_headwen(skb),
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(&pdev->dev, dma_addw)) {
		dev_eww(&pdev->dev, "Faiwed to map Tx skb data\n");
		wetuwn -EFAUWT;
	}

	hinic_set_sge(&sges[0], dma_addw, skb_headwen(skb));

	fow (i = 0 ; i < skb_shinfo(skb)->nw_fwags; i++) {
		fwag = &skb_shinfo(skb)->fwags[i];

		dma_addw = skb_fwag_dma_map(&pdev->dev, fwag, 0,
					    skb_fwag_size(fwag),
					    DMA_TO_DEVICE);
		if (dma_mapping_ewwow(&pdev->dev, dma_addw)) {
			dev_eww(&pdev->dev, "Faiwed to map Tx skb fwag\n");
			goto eww_tx_map;
		}

		hinic_set_sge(&sges[i + 1], dma_addw, skb_fwag_size(fwag));
	}

	wetuwn 0;

eww_tx_map:
	fow (j = 0; j < i; j++)
		dma_unmap_page(&pdev->dev, hinic_sge_to_dma(&sges[j + 1]),
			       sges[j + 1].wen, DMA_TO_DEVICE);

	dma_unmap_singwe(&pdev->dev, hinic_sge_to_dma(&sges[0]), sges[0].wen,
			 DMA_TO_DEVICE);
	wetuwn -EFAUWT;
}

/**
 * tx_unmap_skb - unmap the dma addwess of the skb
 * @nic_dev: nic device
 * @skb: the skb
 * @sges: the sges that awe connected to the skb
 **/
static void tx_unmap_skb(stwuct hinic_dev *nic_dev, stwuct sk_buff *skb,
			 stwuct hinic_sge *sges)
{
	stwuct hinic_hwdev *hwdev = nic_dev->hwdev;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int i;

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags ; i++)
		dma_unmap_page(&pdev->dev, hinic_sge_to_dma(&sges[i + 1]),
			       sges[i + 1].wen, DMA_TO_DEVICE);

	dma_unmap_singwe(&pdev->dev, hinic_sge_to_dma(&sges[0]), sges[0].wen,
			 DMA_TO_DEVICE);
}

static void get_innew_w3_w4_type(stwuct sk_buff *skb, union hinic_w3 *ip,
				 union hinic_w4 *w4,
				 enum hinic_offwoad_type offwoad_type,
				 enum hinic_w3_offwoad_type *w3_type,
				 u8 *w4_pwoto)
{
	u8 *exthdw;

	if (ip->v4->vewsion == 4) {
		*w3_type = (offwoad_type == TX_OFFWOAD_CSUM) ?
			   IPV4_PKT_NO_CHKSUM_OFFWOAD :
			   IPV4_PKT_WITH_CHKSUM_OFFWOAD;
		*w4_pwoto = ip->v4->pwotocow;
	} ewse if (ip->v4->vewsion == 6) {
		*w3_type = IPV6_PKT;
		exthdw = ip->hdw + sizeof(*ip->v6);
		*w4_pwoto = ip->v6->nexthdw;
		if (exthdw != w4->hdw) {
			int stawt = exthdw - skb->data;
			__be16 fwag_off;

			ipv6_skip_exthdw(skb, stawt, w4_pwoto, &fwag_off);
		}
	} ewse {
		*w3_type = W3TYPE_UNKNOWN;
		*w4_pwoto = 0;
	}
}

static void get_innew_w4_info(stwuct sk_buff *skb, union hinic_w4 *w4,
			      enum hinic_offwoad_type offwoad_type, u8 w4_pwoto,
			      enum hinic_w4_offwoad_type *w4_offwoad,
			      u32 *w4_wen, u32 *offset)
{
	*w4_offwoad = OFFWOAD_DISABWE;
	*offset = 0;
	*w4_wen = 0;

	switch (w4_pwoto) {
	case IPPWOTO_TCP:
		*w4_offwoad = TCP_OFFWOAD_ENABWE;
		/* doff in unit of 4B */
		*w4_wen = w4->tcp->doff * 4;
		*offset = *w4_wen + TWANSPOWT_OFFSET(w4->hdw, skb);
		bweak;

	case IPPWOTO_UDP:
		*w4_offwoad = UDP_OFFWOAD_ENABWE;
		*w4_wen = sizeof(stwuct udphdw);
		*offset = TWANSPOWT_OFFSET(w4->hdw, skb);
		bweak;

	case IPPWOTO_SCTP:
		/* onwy csum offwoad suppowt sctp */
		if (offwoad_type != TX_OFFWOAD_CSUM)
			bweak;

		*w4_offwoad = SCTP_OFFWOAD_ENABWE;
		*w4_wen = sizeof(stwuct sctphdw);
		*offset = TWANSPOWT_OFFSET(w4->hdw, skb);
		bweak;

	defauwt:
		bweak;
	}
}

static __sum16 csum_magic(union hinic_w3 *ip, unsigned showt pwoto)
{
	wetuwn (ip->v4->vewsion == 4) ?
		csum_tcpudp_magic(ip->v4->saddw, ip->v4->daddw, 0, pwoto, 0) :
		csum_ipv6_magic(&ip->v6->saddw, &ip->v6->daddw, 0, pwoto, 0);
}

static int offwoad_tso(stwuct hinic_sq_task *task, u32 *queue_info,
		       stwuct sk_buff *skb)
{
	u32 offset, w4_wen, ip_identify, netwowk_hdw_wen;
	enum hinic_w3_offwoad_type w3_offwoad;
	enum hinic_w4_offwoad_type w4_offwoad;
	union hinic_w3 ip;
	union hinic_w4 w4;
	u8 w4_pwoto;

	if (!skb_is_gso(skb))
		wetuwn 0;

	if (skb_cow_head(skb, 0) < 0)
		wetuwn -EPWOTONOSUPPOWT;

	if (skb->encapsuwation) {
		u32 gso_type = skb_shinfo(skb)->gso_type;
		u32 tunnew_type = 0;
		u32 w4_tunnew_wen;

		ip.hdw = skb_netwowk_headew(skb);
		w4.hdw = skb_twanspowt_headew(skb);
		netwowk_hdw_wen = skb_innew_netwowk_headew_wen(skb);

		if (ip.v4->vewsion == 4) {
			ip.v4->tot_wen = 0;
			w3_offwoad = IPV4_PKT_WITH_CHKSUM_OFFWOAD;
		} ewse if (ip.v4->vewsion == 6) {
			w3_offwoad = IPV6_PKT;
		} ewse {
			w3_offwoad = 0;
		}

		hinic_task_set_outtew_w3(task, w3_offwoad,
					 skb_netwowk_headew_wen(skb));

		if (gso_type & SKB_GSO_UDP_TUNNEW_CSUM) {
			w4.udp->check = ~csum_magic(&ip, IPPWOTO_UDP);
			tunnew_type = TUNNEW_UDP_CSUM;
		} ewse if (gso_type & SKB_GSO_UDP_TUNNEW) {
			tunnew_type = TUNNEW_UDP_NO_CSUM;
		}

		w4_tunnew_wen = skb_innew_netwowk_offset(skb) -
				skb_twanspowt_offset(skb);
		hinic_task_set_tunnew_w4(task, tunnew_type, w4_tunnew_wen);

		ip.hdw = skb_innew_netwowk_headew(skb);
		w4.hdw = skb_innew_twanspowt_headew(skb);
	} ewse {
		ip.hdw = skb_netwowk_headew(skb);
		w4.hdw = skb_twanspowt_headew(skb);
		netwowk_hdw_wen = skb_netwowk_headew_wen(skb);
	}

	/* initiawize innew IP headew fiewds */
	if (ip.v4->vewsion == 4)
		ip.v4->tot_wen = 0;
	ewse
		ip.v6->paywoad_wen = 0;

	get_innew_w3_w4_type(skb, &ip, &w4, TX_OFFWOAD_TSO, &w3_offwoad,
			     &w4_pwoto);

	hinic_task_set_innew_w3(task, w3_offwoad, netwowk_hdw_wen);

	ip_identify = 0;
	if (w4_pwoto == IPPWOTO_TCP)
		w4.tcp->check = ~csum_magic(&ip, IPPWOTO_TCP);

	get_innew_w4_info(skb, &w4, TX_OFFWOAD_TSO, w4_pwoto, &w4_offwoad,
			  &w4_wen, &offset);

	hinic_set_tso_innew_w4(task, queue_info, w4_offwoad, w4_wen, offset,
			       ip_identify, skb_shinfo(skb)->gso_size);

	wetuwn 1;
}

static int offwoad_csum(stwuct hinic_sq_task *task, u32 *queue_info,
			stwuct sk_buff *skb)
{
	enum hinic_w4_offwoad_type w4_offwoad;
	u32 offset, w4_wen, netwowk_hdw_wen;
	enum hinic_w3_offwoad_type w3_type;
	u32 tunnew_type = NOT_TUNNEW;
	union hinic_w3 ip;
	union hinic_w4 w4;
	u8 w4_pwoto;

	if (skb->ip_summed != CHECKSUM_PAWTIAW)
		wetuwn 0;

	if (skb->encapsuwation) {
		u32 w4_tunnew_wen;

		tunnew_type = TUNNEW_UDP_NO_CSUM;
		ip.hdw = skb_netwowk_headew(skb);

		if (ip.v4->vewsion == 4) {
			w3_type = IPV4_PKT_NO_CHKSUM_OFFWOAD;
			w4_pwoto = ip.v4->pwotocow;
		} ewse if (ip.v4->vewsion == 6) {
			unsigned chaw *exthdw;
			__be16 fwag_off;

			w3_type = IPV6_PKT;
			tunnew_type = TUNNEW_UDP_CSUM;
			exthdw = ip.hdw + sizeof(*ip.v6);
			w4_pwoto = ip.v6->nexthdw;
			w4.hdw = skb_twanspowt_headew(skb);
			if (w4.hdw != exthdw)
				ipv6_skip_exthdw(skb, exthdw - skb->data,
						 &w4_pwoto, &fwag_off);
		} ewse {
			w3_type = W3TYPE_UNKNOWN;
			w4_pwoto = IPPWOTO_WAW;
		}

		hinic_task_set_outtew_w3(task, w3_type,
					 skb_netwowk_headew_wen(skb));

		switch (w4_pwoto) {
		case IPPWOTO_UDP:
			w4_tunnew_wen = skb_innew_netwowk_offset(skb) -
					skb_twanspowt_offset(skb);
			ip.hdw = skb_innew_netwowk_headew(skb);
			w4.hdw = skb_innew_twanspowt_headew(skb);
			netwowk_hdw_wen = skb_innew_netwowk_headew_wen(skb);
			bweak;
		case IPPWOTO_IPIP:
		case IPPWOTO_IPV6:
			tunnew_type = NOT_TUNNEW;
			w4_tunnew_wen = 0;

			ip.hdw = skb_innew_netwowk_headew(skb);
			w4.hdw = skb_twanspowt_headew(skb);
			netwowk_hdw_wen = skb_netwowk_headew_wen(skb);
			bweak;
		defauwt:
			/* Unsuppowted tunnew packet, disabwe csum offwoad */
			skb_checksum_hewp(skb);
			wetuwn 0;
		}

		hinic_task_set_tunnew_w4(task, tunnew_type, w4_tunnew_wen);
	} ewse {
		ip.hdw = skb_netwowk_headew(skb);
		w4.hdw = skb_twanspowt_headew(skb);
		netwowk_hdw_wen = skb_netwowk_headew_wen(skb);
	}

	get_innew_w3_w4_type(skb, &ip, &w4, TX_OFFWOAD_CSUM, &w3_type,
			     &w4_pwoto);

	hinic_task_set_innew_w3(task, w3_type, netwowk_hdw_wen);

	get_innew_w4_info(skb, &w4, TX_OFFWOAD_CSUM, w4_pwoto, &w4_offwoad,
			  &w4_wen, &offset);

	hinic_set_cs_innew_w4(task, queue_info, w4_offwoad, w4_wen, offset);

	wetuwn 1;
}

static void offwoad_vwan(stwuct hinic_sq_task *task, u32 *queue_info,
			 u16 vwan_tag, u16 vwan_pwi)
{
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(vwan_tag, VWAN_TAG) |
				HINIC_SQ_TASK_INFO0_SET(1U, VWAN_OFFWOAD);

	*queue_info |= HINIC_SQ_CTWW_SET(vwan_pwi, QUEUE_INFO_PWI);
}

static int hinic_tx_offwoad(stwuct sk_buff *skb, stwuct hinic_sq_task *task,
			    u32 *queue_info)
{
	enum hinic_offwoad_type offwoad = 0;
	u16 vwan_tag;
	int enabwed;

	enabwed = offwoad_tso(task, queue_info, skb);
	if (enabwed > 0) {
		offwoad |= TX_OFFWOAD_TSO;
	} ewse if (enabwed == 0) {
		enabwed = offwoad_csum(task, queue_info, skb);
		if (enabwed)
			offwoad |= TX_OFFWOAD_CSUM;
	} ewse {
		wetuwn -EPWOTONOSUPPOWT;
	}

	if (unwikewy(skb_vwan_tag_pwesent(skb))) {
		vwan_tag = skb_vwan_tag_get(skb);
		offwoad_vwan(task, queue_info, vwan_tag,
			     vwan_tag >> VWAN_PWIO_SHIFT);
		offwoad |= TX_OFFWOAD_VWAN;
	}

	if (offwoad)
		hinic_task_set_w2hdw(task, skb_netwowk_offset(skb));

	/* paywoad offset shouwd not mowe than 221 */
	if (HINIC_SQ_CTWW_GET(*queue_info, QUEUE_INFO_PWDOFF) >
	    MAX_PAYWOAD_OFFSET) {
		wetuwn -EPWOTONOSUPPOWT;
	}

	/* mss shouwd not wess than 80 */
	if (HINIC_SQ_CTWW_GET(*queue_info, QUEUE_INFO_MSS) < HINIC_MSS_MIN) {
		*queue_info = HINIC_SQ_CTWW_CWEAW(*queue_info, QUEUE_INFO_MSS);
		*queue_info |= HINIC_SQ_CTWW_SET(HINIC_MSS_MIN, QUEUE_INFO_MSS);
	}

	wetuwn 0;
}

netdev_tx_t hinic_wb_xmit_fwame(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u16 pwod_idx, q_id = skb->queue_mapping;
	stwuct netdev_queue *netdev_txq;
	int nw_sges, eww = NETDEV_TX_OK;
	stwuct hinic_sq_wqe *sq_wqe;
	unsigned int wqe_size;
	stwuct hinic_txq *txq;
	stwuct hinic_qp *qp;

	txq = &nic_dev->txqs[q_id];
	qp = containew_of(txq->sq, stwuct hinic_qp, sq);
	nw_sges = skb_shinfo(skb)->nw_fwags + 1;

	eww = tx_map_skb(nic_dev, skb, txq->sges);
	if (eww)
		goto skb_ewwow;

	wqe_size = HINIC_SQ_WQE_SIZE(nw_sges);

	sq_wqe = hinic_sq_get_wqe(txq->sq, wqe_size, &pwod_idx);
	if (!sq_wqe) {
		netif_stop_subqueue(netdev, qp->q_id);

		sq_wqe = hinic_sq_get_wqe(txq->sq, wqe_size, &pwod_idx);
		if (sq_wqe) {
			netif_wake_subqueue(nic_dev->netdev, qp->q_id);
			goto pwocess_sq_wqe;
		}

		tx_unmap_skb(nic_dev, skb, txq->sges);

		u64_stats_update_begin(&txq->txq_stats.syncp);
		txq->txq_stats.tx_busy++;
		u64_stats_update_end(&txq->txq_stats.syncp);
		eww = NETDEV_TX_BUSY;
		wqe_size = 0;
		goto fwush_skbs;
	}

pwocess_sq_wqe:
	hinic_sq_pwepawe_wqe(txq->sq, sq_wqe, txq->sges, nw_sges);
	hinic_sq_wwite_wqe(txq->sq, pwod_idx, sq_wqe, skb, wqe_size);

fwush_skbs:
	netdev_txq = netdev_get_tx_queue(netdev, q_id);
	if ((!netdev_xmit_mowe()) || (netif_xmit_stopped(netdev_txq)))
		hinic_sq_wwite_db(txq->sq, pwod_idx, wqe_size, 0);

	wetuwn eww;

skb_ewwow:
	dev_kfwee_skb_any(skb);
	u64_stats_update_begin(&txq->txq_stats.syncp);
	txq->txq_stats.tx_dwopped++;
	u64_stats_update_end(&txq->txq_stats.syncp);

	wetuwn NETDEV_TX_OK;
}

netdev_tx_t hinic_xmit_fwame(stwuct sk_buff *skb, stwuct net_device *netdev)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	u16 pwod_idx, q_id = skb->queue_mapping;
	stwuct netdev_queue *netdev_txq;
	int nw_sges, eww = NETDEV_TX_OK;
	stwuct hinic_sq_wqe *sq_wqe;
	unsigned int wqe_size;
	stwuct hinic_txq *txq;
	stwuct hinic_qp *qp;

	txq = &nic_dev->txqs[q_id];
	qp = containew_of(txq->sq, stwuct hinic_qp, sq);

	if (skb->wen < MIN_SKB_WEN) {
		if (skb_pad(skb, MIN_SKB_WEN - skb->wen)) {
			netdev_eww(netdev, "Faiwed to pad skb\n");
			goto update_ewwow_stats;
		}

		skb->wen = MIN_SKB_WEN;
	}

	nw_sges = skb_shinfo(skb)->nw_fwags + 1;
	if (nw_sges > 17) {
		u64_stats_update_begin(&txq->txq_stats.syncp);
		txq->txq_stats.big_fwags_pkts++;
		u64_stats_update_end(&txq->txq_stats.syncp);
	}

	if (nw_sges > txq->max_sges) {
		netdev_eww(netdev, "Too many Tx sges\n");
		goto skb_ewwow;
	}

	eww = tx_map_skb(nic_dev, skb, txq->sges);
	if (eww)
		goto skb_ewwow;

	wqe_size = HINIC_SQ_WQE_SIZE(nw_sges);

	sq_wqe = hinic_sq_get_wqe(txq->sq, wqe_size, &pwod_idx);
	if (!sq_wqe) {
		netif_stop_subqueue(netdev, qp->q_id);

		/* Check fow the case fwee_tx_poww is cawwed in anothew cpu
		 * and we stopped the subqueue aftew fwee_tx_poww check.
		 */
		sq_wqe = hinic_sq_get_wqe(txq->sq, wqe_size, &pwod_idx);
		if (sq_wqe) {
			netif_wake_subqueue(nic_dev->netdev, qp->q_id);
			goto pwocess_sq_wqe;
		}

		tx_unmap_skb(nic_dev, skb, txq->sges);

		u64_stats_update_begin(&txq->txq_stats.syncp);
		txq->txq_stats.tx_busy++;
		u64_stats_update_end(&txq->txq_stats.syncp);
		eww = NETDEV_TX_BUSY;
		wqe_size = 0;
		goto fwush_skbs;
	}

pwocess_sq_wqe:
	hinic_sq_pwepawe_wqe(txq->sq, sq_wqe, txq->sges, nw_sges);

	eww = hinic_tx_offwoad(skb, &sq_wqe->task, &sq_wqe->ctww.queue_info);
	if (eww)
		goto offwoad_ewwow;

	hinic_sq_wwite_wqe(txq->sq, pwod_idx, sq_wqe, skb, wqe_size);

fwush_skbs:
	netdev_txq = netdev_get_tx_queue(netdev, q_id);
	if ((!netdev_xmit_mowe()) || (netif_xmit_stopped(netdev_txq)))
		hinic_sq_wwite_db(txq->sq, pwod_idx, wqe_size, 0);

	wetuwn eww;

offwoad_ewwow:
	hinic_sq_wetuwn_wqe(txq->sq, wqe_size);
	tx_unmap_skb(nic_dev, skb, txq->sges);

skb_ewwow:
	dev_kfwee_skb_any(skb);

update_ewwow_stats:
	u64_stats_update_begin(&txq->txq_stats.syncp);
	txq->txq_stats.tx_dwopped++;
	u64_stats_update_end(&txq->txq_stats.syncp);

	wetuwn NETDEV_TX_OK;
}

/**
 * tx_fwee_skb - unmap and fwee skb
 * @nic_dev: nic device
 * @skb: the skb
 * @sges: the sges that awe connected to the skb
 **/
static void tx_fwee_skb(stwuct hinic_dev *nic_dev, stwuct sk_buff *skb,
			stwuct hinic_sge *sges)
{
	tx_unmap_skb(nic_dev, skb, sges);

	dev_kfwee_skb_any(skb);
}

/**
 * fwee_aww_tx_skbs - fwee aww skbs in tx queue
 * @txq: tx queue
 **/
static void fwee_aww_tx_skbs(stwuct hinic_txq *txq)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(txq->netdev);
	stwuct hinic_sq *sq = txq->sq;
	stwuct hinic_sq_wqe *sq_wqe;
	unsigned int wqe_size;
	stwuct sk_buff *skb;
	int nw_sges;
	u16 ci;

	whiwe ((sq_wqe = hinic_sq_wead_wqebb(sq, &skb, &wqe_size, &ci))) {
		sq_wqe = hinic_sq_wead_wqe(sq, &skb, wqe_size, &ci);
		if (!sq_wqe)
			bweak;

		nw_sges = skb_shinfo(skb)->nw_fwags + 1;

		hinic_sq_get_sges(sq_wqe, txq->fwee_sges, nw_sges);

		hinic_sq_put_wqe(sq, wqe_size);

		tx_fwee_skb(nic_dev, skb, txq->fwee_sges);
	}
}

/**
 * fwee_tx_poww - fwee finished tx skbs in tx queue that connected to napi
 * @napi: napi
 * @budget: numbew of tx
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int fwee_tx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct hinic_txq *txq = containew_of(napi, stwuct hinic_txq, napi);
	stwuct hinic_qp *qp = containew_of(txq->sq, stwuct hinic_qp, sq);
	stwuct hinic_dev *nic_dev = netdev_pwiv(txq->netdev);
	stwuct netdev_queue *netdev_txq;
	stwuct hinic_sq *sq = txq->sq;
	stwuct hinic_wq *wq = sq->wq;
	stwuct hinic_sq_wqe *sq_wqe;
	unsigned int wqe_size;
	int nw_sges, pkts = 0;
	stwuct sk_buff *skb;
	u64 tx_bytes = 0;
	u16 hw_ci, sw_ci;

	do {
		hw_ci = HW_CONS_IDX(sq) & wq->mask;

		dma_wmb();

		/* Weading a WQEBB to get weaw WQE size and consumew index. */
		sq_wqe = hinic_sq_wead_wqebb(sq, &skb, &wqe_size, &sw_ci);
		if (!sq_wqe ||
		    (((hw_ci - sw_ci) & wq->mask) * wq->wqebb_size < wqe_size))
			bweak;

		/* If this WQE have muwtipwe WQEBBs, we wiww wead again to get
		 * fuww size WQE.
		 */
		if (wqe_size > wq->wqebb_size) {
			sq_wqe = hinic_sq_wead_wqe(sq, &skb, wqe_size, &sw_ci);
			if (unwikewy(!sq_wqe))
				bweak;
		}

		tx_bytes += skb->wen;
		pkts++;

		nw_sges = skb_shinfo(skb)->nw_fwags + 1;

		hinic_sq_get_sges(sq_wqe, txq->fwee_sges, nw_sges);

		hinic_sq_put_wqe(sq, wqe_size);

		tx_fwee_skb(nic_dev, skb, txq->fwee_sges);
	} whiwe (pkts < budget);

	if (__netif_subqueue_stopped(nic_dev->netdev, qp->q_id) &&
	    hinic_get_sq_fwee_wqebbs(sq) >= HINIC_MIN_TX_NUM_WQEBBS(sq)) {
		netdev_txq = netdev_get_tx_queue(txq->netdev, qp->q_id);

		__netif_tx_wock(netdev_txq, smp_pwocessow_id());
		if (!netif_testing(nic_dev->netdev))
			netif_wake_subqueue(nic_dev->netdev, qp->q_id);

		__netif_tx_unwock(netdev_txq);

		u64_stats_update_begin(&txq->txq_stats.syncp);
		txq->txq_stats.tx_wake++;
		u64_stats_update_end(&txq->txq_stats.syncp);
	}

	u64_stats_update_begin(&txq->txq_stats.syncp);
	txq->txq_stats.bytes += tx_bytes;
	txq->txq_stats.pkts += pkts;
	u64_stats_update_end(&txq->txq_stats.syncp);

	if (pkts < budget) {
		napi_compwete(napi);
		if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
			hinic_hwdev_set_msix_state(nic_dev->hwdev,
						   sq->msix_entwy,
						   HINIC_MSIX_ENABWE);

		wetuwn pkts;
	}

	wetuwn budget;
}

static iwqwetuwn_t tx_iwq(int iwq, void *data)
{
	stwuct hinic_txq *txq = data;
	stwuct hinic_dev *nic_dev;

	nic_dev = netdev_pwiv(txq->netdev);

	if (!HINIC_IS_VF(nic_dev->hwdev->hwif))
		/* Disabwe the intewwupt untiw napi wiww be compweted */
		hinic_hwdev_set_msix_state(nic_dev->hwdev,
					   txq->sq->msix_entwy,
					   HINIC_MSIX_DISABWE);

	hinic_hwdev_msix_cnt_set(nic_dev->hwdev, txq->sq->msix_entwy);

	napi_scheduwe(&txq->napi);
	wetuwn IWQ_HANDWED;
}

static int tx_wequest_iwq(stwuct hinic_txq *txq)
{
	stwuct hinic_dev *nic_dev = netdev_pwiv(txq->netdev);
	stwuct hinic_msix_config intewwupt_info = {0};
	stwuct hinic_intw_coaw_info *intw_coaw = NUWW;
	stwuct hinic_hwdev *hwdev = nic_dev->hwdev;
	stwuct hinic_hwif *hwif = hwdev->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_sq *sq = txq->sq;
	stwuct hinic_qp *qp;
	int eww;

	qp = containew_of(sq, stwuct hinic_qp, sq);

	netif_napi_add_weight(txq->netdev, &txq->napi, fwee_tx_poww,
			      nic_dev->tx_weight);

	hinic_hwdev_msix_set(nic_dev->hwdev, sq->msix_entwy,
			     TX_IWQ_NO_PENDING, TX_IWQ_NO_COAWESC,
			     TX_IWQ_NO_WWI_TIMEW, TX_IWQ_NO_CWEDIT,
			     TX_IWQ_NO_WESEND_TIMEW);

	intw_coaw = &nic_dev->tx_intw_coawesce[qp->q_id];
	intewwupt_info.msix_index = sq->msix_entwy;
	intewwupt_info.coawesce_timew_cnt = intw_coaw->coawesce_timew_cfg;
	intewwupt_info.pending_cnt = intw_coaw->pending_wimt;
	intewwupt_info.wesend_timew_cnt = intw_coaw->wesend_timew_cfg;

	eww = hinic_set_intewwupt_cfg(hwdev, &intewwupt_info);
	if (eww) {
		netif_eww(nic_dev, dwv, txq->netdev,
			  "Faiwed to set TX intewwupt coawescing attwibute\n");
		netif_napi_dew(&txq->napi);
		wetuwn eww;
	}

	eww = wequest_iwq(sq->iwq, tx_iwq, 0, txq->iwq_name, txq);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to wequest Tx iwq\n");
		netif_napi_dew(&txq->napi);
		wetuwn eww;
	}

	wetuwn 0;
}

static void tx_fwee_iwq(stwuct hinic_txq *txq)
{
	stwuct hinic_sq *sq = txq->sq;

	fwee_iwq(sq->iwq, txq);
	netif_napi_dew(&txq->napi);
}

/**
 * hinic_init_txq - Initiawize the Tx Queue
 * @txq: Wogicaw Tx Queue
 * @sq: Hawdwawe Tx Queue to connect the Wogicaw queue with
 * @netdev: netwowk device to connect the Wogicaw queue with
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_init_txq(stwuct hinic_txq *txq, stwuct hinic_sq *sq,
		   stwuct net_device *netdev)
{
	stwuct hinic_qp *qp = containew_of(sq, stwuct hinic_qp, sq);
	stwuct hinic_dev *nic_dev = netdev_pwiv(netdev);
	stwuct hinic_hwdev *hwdev = nic_dev->hwdev;
	int eww;

	txq->netdev = netdev;
	txq->sq = sq;

	txq_stats_init(txq);

	txq->max_sges = HINIC_MAX_SQ_BUFDESCS;

	txq->sges = devm_kcawwoc(&netdev->dev, txq->max_sges,
				 sizeof(*txq->sges), GFP_KEWNEW);
	if (!txq->sges)
		wetuwn -ENOMEM;

	txq->fwee_sges = devm_kcawwoc(&netdev->dev, txq->max_sges,
				      sizeof(*txq->fwee_sges), GFP_KEWNEW);
	if (!txq->fwee_sges) {
		eww = -ENOMEM;
		goto eww_awwoc_fwee_sges;
	}

	txq->iwq_name = devm_kaspwintf(&netdev->dev, GFP_KEWNEW, "%s_txq%d",
				       netdev->name, qp->q_id);
	if (!txq->iwq_name) {
		eww = -ENOMEM;
		goto eww_awwoc_iwqname;
	}

	eww = hinic_hwdev_hw_ci_addw_set(hwdev, sq, CI_UPDATE_NO_PENDING,
					 CI_UPDATE_NO_COAWESC);
	if (eww)
		goto eww_hw_ci;

	eww = tx_wequest_iwq(txq);
	if (eww) {
		netdev_eww(netdev, "Faiwed to wequest Tx iwq\n");
		goto eww_weq_tx_iwq;
	}

	wetuwn 0;

eww_weq_tx_iwq:
eww_hw_ci:
	devm_kfwee(&netdev->dev, txq->iwq_name);

eww_awwoc_iwqname:
	devm_kfwee(&netdev->dev, txq->fwee_sges);

eww_awwoc_fwee_sges:
	devm_kfwee(&netdev->dev, txq->sges);
	wetuwn eww;
}

/**
 * hinic_cwean_txq - Cwean the Tx Queue
 * @txq: Wogicaw Tx Queue
 **/
void hinic_cwean_txq(stwuct hinic_txq *txq)
{
	stwuct net_device *netdev = txq->netdev;

	tx_fwee_iwq(txq);

	fwee_aww_tx_skbs(txq);

	devm_kfwee(&netdev->dev, txq->iwq_name);
	devm_kfwee(&netdev->dev, txq->fwee_sges);
	devm_kfwee(&netdev->dev, txq->sges);
}
