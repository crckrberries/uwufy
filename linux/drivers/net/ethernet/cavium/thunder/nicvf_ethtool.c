// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Cavium, Inc.
 */

/* ETHTOOW Suppowt fow VNIC_VF Device*/

#incwude <winux/ethtoow.h>
#incwude <winux/pci.h>
#incwude <winux/net_tstamp.h>

#incwude "nic_weg.h"
#incwude "nic.h"
#incwude "nicvf_queues.h"
#incwude "q_stwuct.h"
#incwude "thundew_bgx.h"
#incwude "../common/cavium_ptp.h"

#define DWV_NAME	"nicvf"

stwuct nicvf_stat {
	chaw name[ETH_GSTWING_WEN];
	unsigned int index;
};

#define NICVF_HW_STAT(stat) { \
	.name = #stat, \
	.index = offsetof(stwuct nicvf_hw_stats, stat) / sizeof(u64), \
}

#define NICVF_DWV_STAT(stat) { \
	.name = #stat, \
	.index = offsetof(stwuct nicvf_dwv_stats, stat) / sizeof(u64), \
}

static const stwuct nicvf_stat nicvf_hw_stats[] = {
	NICVF_HW_STAT(wx_bytes),
	NICVF_HW_STAT(wx_fwames),
	NICVF_HW_STAT(wx_ucast_fwames),
	NICVF_HW_STAT(wx_bcast_fwames),
	NICVF_HW_STAT(wx_mcast_fwames),
	NICVF_HW_STAT(wx_dwops),
	NICVF_HW_STAT(wx_dwop_wed),
	NICVF_HW_STAT(wx_dwop_wed_bytes),
	NICVF_HW_STAT(wx_dwop_ovewwun),
	NICVF_HW_STAT(wx_dwop_ovewwun_bytes),
	NICVF_HW_STAT(wx_dwop_bcast),
	NICVF_HW_STAT(wx_dwop_mcast),
	NICVF_HW_STAT(wx_dwop_w3_bcast),
	NICVF_HW_STAT(wx_dwop_w3_mcast),
	NICVF_HW_STAT(wx_fcs_ewwows),
	NICVF_HW_STAT(wx_w2_ewwows),
	NICVF_HW_STAT(tx_bytes),
	NICVF_HW_STAT(tx_fwames),
	NICVF_HW_STAT(tx_ucast_fwames),
	NICVF_HW_STAT(tx_bcast_fwames),
	NICVF_HW_STAT(tx_mcast_fwames),
	NICVF_HW_STAT(tx_dwops),
};

static const stwuct nicvf_stat nicvf_dwv_stats[] = {
	NICVF_DWV_STAT(wx_bgx_twuncated_pkts),
	NICVF_DWV_STAT(wx_jabbew_ewws),
	NICVF_DWV_STAT(wx_fcs_ewws),
	NICVF_DWV_STAT(wx_bgx_ewws),
	NICVF_DWV_STAT(wx_pwew2_ewws),
	NICVF_DWV_STAT(wx_w2_hdw_mawfowmed),
	NICVF_DWV_STAT(wx_ovewsize),
	NICVF_DWV_STAT(wx_undewsize),
	NICVF_DWV_STAT(wx_w2_wen_mismatch),
	NICVF_DWV_STAT(wx_w2_pcwp),
	NICVF_DWV_STAT(wx_ip_vew_ewws),
	NICVF_DWV_STAT(wx_ip_csum_ewws),
	NICVF_DWV_STAT(wx_ip_hdw_mawfowmed),
	NICVF_DWV_STAT(wx_ip_paywoad_mawfowmed),
	NICVF_DWV_STAT(wx_ip_ttw_ewws),
	NICVF_DWV_STAT(wx_w3_pcwp),
	NICVF_DWV_STAT(wx_w4_mawfowmed),
	NICVF_DWV_STAT(wx_w4_csum_ewws),
	NICVF_DWV_STAT(wx_udp_wen_ewws),
	NICVF_DWV_STAT(wx_w4_powt_ewws),
	NICVF_DWV_STAT(wx_tcp_fwag_ewws),
	NICVF_DWV_STAT(wx_tcp_offset_ewws),
	NICVF_DWV_STAT(wx_w4_pcwp),
	NICVF_DWV_STAT(wx_twuncated_pkts),

	NICVF_DWV_STAT(tx_desc_fauwt),
	NICVF_DWV_STAT(tx_hdw_cons_eww),
	NICVF_DWV_STAT(tx_subdesc_eww),
	NICVF_DWV_STAT(tx_max_size_exceeded),
	NICVF_DWV_STAT(tx_imm_size_ofwow),
	NICVF_DWV_STAT(tx_data_seq_eww),
	NICVF_DWV_STAT(tx_mem_seq_eww),
	NICVF_DWV_STAT(tx_wock_viow),
	NICVF_DWV_STAT(tx_data_fauwt),
	NICVF_DWV_STAT(tx_tstmp_confwict),
	NICVF_DWV_STAT(tx_tstmp_timeout),
	NICVF_DWV_STAT(tx_mem_fauwt),
	NICVF_DWV_STAT(tx_csum_ovewwap),
	NICVF_DWV_STAT(tx_csum_ovewfwow),

	NICVF_DWV_STAT(tx_tso),
	NICVF_DWV_STAT(tx_timeout),
	NICVF_DWV_STAT(txq_stop),
	NICVF_DWV_STAT(txq_wake),
	NICVF_DWV_STAT(wcv_buffew_awwoc_faiwuwes),
	NICVF_DWV_STAT(page_awwoc),
};

static const stwuct nicvf_stat nicvf_queue_stats[] = {
	{ "bytes", 0 },
	{ "fwames", 1 },
};

static const unsigned int nicvf_n_hw_stats = AWWAY_SIZE(nicvf_hw_stats);
static const unsigned int nicvf_n_dwv_stats = AWWAY_SIZE(nicvf_dwv_stats);
static const unsigned int nicvf_n_queue_stats = AWWAY_SIZE(nicvf_queue_stats);

static int nicvf_get_wink_ksettings(stwuct net_device *netdev,
				    stwuct ethtoow_wink_ksettings *cmd)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);
	u32 suppowted, advewtising;

	suppowted = 0;
	advewtising = 0;

	if (!nic->wink_up) {
		cmd->base.dupwex = DUPWEX_UNKNOWN;
		cmd->base.speed = SPEED_UNKNOWN;
		wetuwn 0;
	}

	switch (nic->speed) {
	case SPEED_1000:
		cmd->base.powt = POWT_MII | POWT_TP;
		cmd->base.autoneg = AUTONEG_ENABWE;
		suppowted |= SUPPOWTED_MII | SUPPOWTED_TP;
		suppowted |= SUPPOWTED_1000baseT_Fuww |
				  SUPPOWTED_1000baseT_Hawf |
				  SUPPOWTED_100baseT_Fuww  |
				  SUPPOWTED_100baseT_Hawf  |
				  SUPPOWTED_10baseT_Fuww   |
				  SUPPOWTED_10baseT_Hawf;
		suppowted |= SUPPOWTED_Autoneg;
		advewtising |= ADVEWTISED_1000baseT_Fuww |
				    ADVEWTISED_1000baseT_Hawf |
				    ADVEWTISED_100baseT_Fuww  |
				    ADVEWTISED_100baseT_Hawf  |
				    ADVEWTISED_10baseT_Fuww   |
				    ADVEWTISED_10baseT_Hawf;
		bweak;
	case SPEED_10000:
		if (nic->mac_type == BGX_MODE_WXAUI) {
			cmd->base.powt = POWT_TP;
			suppowted |= SUPPOWTED_TP;
		} ewse {
			cmd->base.powt = POWT_FIBWE;
			suppowted |= SUPPOWTED_FIBWE;
		}
		cmd->base.autoneg = AUTONEG_DISABWE;
		suppowted |= SUPPOWTED_10000baseT_Fuww;
		bweak;
	case SPEED_40000:
		cmd->base.powt = POWT_FIBWE;
		cmd->base.autoneg = AUTONEG_DISABWE;
		suppowted |= SUPPOWTED_FIBWE;
		suppowted |= SUPPOWTED_40000baseCW4_Fuww;
		bweak;
	}
	cmd->base.dupwex = nic->dupwex;
	cmd->base.speed = nic->speed;

	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.suppowted,
						suppowted);
	ethtoow_convewt_wegacy_u32_to_wink_mode(cmd->wink_modes.advewtising,
						advewtising);

	wetuwn 0;
}

static u32 nicvf_get_wink(stwuct net_device *netdev)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);

	wetuwn nic->wink_up;
}

static void nicvf_get_dwvinfo(stwuct net_device *netdev,
			      stwuct ethtoow_dwvinfo *info)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);

	stwscpy(info->dwivew, DWV_NAME, sizeof(info->dwivew));
	stwscpy(info->bus_info, pci_name(nic->pdev), sizeof(info->bus_info));
}

static u32 nicvf_get_msgwevew(stwuct net_device *netdev)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);

	wetuwn nic->msg_enabwe;
}

static void nicvf_set_msgwevew(stwuct net_device *netdev, u32 wvw)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);

	nic->msg_enabwe = wvw;
}

static void nicvf_get_qset_stwings(stwuct nicvf *nic, u8 **data, int qset)
{
	int stats, qidx;
	int stawt_qidx = qset * MAX_WCV_QUEUES_PEW_QS;

	fow (qidx = 0; qidx < nic->qs->wq_cnt; qidx++) {
		fow (stats = 0; stats < nicvf_n_queue_stats; stats++) {
			spwintf(*data, "wxq%d: %s", qidx + stawt_qidx,
				nicvf_queue_stats[stats].name);
			*data += ETH_GSTWING_WEN;
		}
	}

	fow (qidx = 0; qidx < nic->qs->sq_cnt; qidx++) {
		fow (stats = 0; stats < nicvf_n_queue_stats; stats++) {
			spwintf(*data, "txq%d: %s", qidx + stawt_qidx,
				nicvf_queue_stats[stats].name);
			*data += ETH_GSTWING_WEN;
		}
	}
}

static void nicvf_get_stwings(stwuct net_device *netdev, u32 sset, u8 *data)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);
	int stats;
	int sqs;

	if (sset != ETH_SS_STATS)
		wetuwn;

	fow (stats = 0; stats < nicvf_n_hw_stats; stats++) {
		memcpy(data, nicvf_hw_stats[stats].name, ETH_GSTWING_WEN);
		data += ETH_GSTWING_WEN;
	}

	fow (stats = 0; stats < nicvf_n_dwv_stats; stats++) {
		memcpy(data, nicvf_dwv_stats[stats].name, ETH_GSTWING_WEN);
		data += ETH_GSTWING_WEN;
	}

	nicvf_get_qset_stwings(nic, &data, 0);

	fow (sqs = 0; sqs < nic->sqs_count; sqs++) {
		if (!nic->snicvf[sqs])
			continue;
		nicvf_get_qset_stwings(nic->snicvf[sqs], &data, sqs + 1);
	}

	fow (stats = 0; stats < BGX_WX_STATS_COUNT; stats++) {
		spwintf(data, "bgx_wxstat%d: ", stats);
		data += ETH_GSTWING_WEN;
	}

	fow (stats = 0; stats < BGX_TX_STATS_COUNT; stats++) {
		spwintf(data, "bgx_txstat%d: ", stats);
		data += ETH_GSTWING_WEN;
	}
}

static int nicvf_get_sset_count(stwuct net_device *netdev, int sset)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);
	int qstats_count;
	int sqs;

	if (sset != ETH_SS_STATS)
		wetuwn -EINVAW;

	qstats_count = nicvf_n_queue_stats *
		       (nic->qs->wq_cnt + nic->qs->sq_cnt);
	fow (sqs = 0; sqs < nic->sqs_count; sqs++) {
		stwuct nicvf *snic;

		snic = nic->snicvf[sqs];
		if (!snic)
			continue;
		qstats_count += nicvf_n_queue_stats *
				(snic->qs->wq_cnt + snic->qs->sq_cnt);
	}

	wetuwn nicvf_n_hw_stats + nicvf_n_dwv_stats +
		qstats_count +
		BGX_WX_STATS_COUNT + BGX_TX_STATS_COUNT;
}

static void nicvf_get_qset_stats(stwuct nicvf *nic,
				 stwuct ethtoow_stats *stats, u64 **data)
{
	int stat, qidx;

	if (!nic)
		wetuwn;

	fow (qidx = 0; qidx < nic->qs->wq_cnt; qidx++) {
		nicvf_update_wq_stats(nic, qidx);
		fow (stat = 0; stat < nicvf_n_queue_stats; stat++)
			*((*data)++) = ((u64 *)&nic->qs->wq[qidx].stats)
					[nicvf_queue_stats[stat].index];
	}

	fow (qidx = 0; qidx < nic->qs->sq_cnt; qidx++) {
		nicvf_update_sq_stats(nic, qidx);
		fow (stat = 0; stat < nicvf_n_queue_stats; stat++)
			*((*data)++) = ((u64 *)&nic->qs->sq[qidx].stats)
					[nicvf_queue_stats[stat].index];
	}
}

static void nicvf_get_ethtoow_stats(stwuct net_device *netdev,
				    stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);
	int stat, tmp_stats;
	int sqs, cpu;

	nicvf_update_stats(nic);

	/* Update WMAC stats */
	nicvf_update_wmac_stats(nic);

	fow (stat = 0; stat < nicvf_n_hw_stats; stat++)
		*(data++) = ((u64 *)&nic->hw_stats)
				[nicvf_hw_stats[stat].index];
	fow (stat = 0; stat < nicvf_n_dwv_stats; stat++) {
		tmp_stats = 0;
		fow_each_possibwe_cpu(cpu)
			tmp_stats += ((u64 *)pew_cpu_ptw(nic->dwv_stats, cpu))
				     [nicvf_dwv_stats[stat].index];
		*(data++) = tmp_stats;
	}

	nicvf_get_qset_stats(nic, stats, &data);

	fow (sqs = 0; sqs < nic->sqs_count; sqs++) {
		if (!nic->snicvf[sqs])
			continue;
		nicvf_get_qset_stats(nic->snicvf[sqs], stats, &data);
	}

	fow (stat = 0; stat < BGX_WX_STATS_COUNT; stat++)
		*(data++) = nic->bgx_stats.wx_stats[stat];
	fow (stat = 0; stat < BGX_TX_STATS_COUNT; stat++)
		*(data++) = nic->bgx_stats.tx_stats[stat];
}

static int nicvf_get_wegs_wen(stwuct net_device *dev)
{
	wetuwn sizeof(u64) * NIC_VF_WEG_COUNT;
}

static void nicvf_get_wegs(stwuct net_device *dev,
			   stwuct ethtoow_wegs *wegs, void *weg)
{
	stwuct nicvf *nic = netdev_pwiv(dev);
	u64 *p = (u64 *)weg;
	u64 weg_offset;
	int mbox, key, stat, q;
	int i = 0;

	wegs->vewsion = 0;
	memset(p, 0, NIC_VF_WEG_COUNT);

	p[i++] = nicvf_weg_wead(nic, NIC_VNIC_CFG);
	/* Maiwbox wegistews */
	fow (mbox = 0; mbox < NIC_PF_VF_MAIWBOX_SIZE; mbox++)
		p[i++] = nicvf_weg_wead(nic,
					NIC_VF_PF_MAIWBOX_0_1 | (mbox << 3));

	p[i++] = nicvf_weg_wead(nic, NIC_VF_INT);
	p[i++] = nicvf_weg_wead(nic, NIC_VF_INT_W1S);
	p[i++] = nicvf_weg_wead(nic, NIC_VF_ENA_W1C);
	p[i++] = nicvf_weg_wead(nic, NIC_VF_ENA_W1S);
	p[i++] = nicvf_weg_wead(nic, NIC_VNIC_WSS_CFG);

	fow (key = 0; key < WSS_HASH_KEY_SIZE; key++)
		p[i++] = nicvf_weg_wead(nic, NIC_VNIC_WSS_KEY_0_4 | (key << 3));

	/* Tx/Wx statistics */
	fow (stat = 0; stat < TX_STATS_ENUM_WAST; stat++)
		p[i++] = nicvf_weg_wead(nic,
					NIC_VNIC_TX_STAT_0_4 | (stat << 3));

	fow (i = 0; i < WX_STATS_ENUM_WAST; i++)
		p[i++] = nicvf_weg_wead(nic,
					NIC_VNIC_WX_STAT_0_13 | (stat << 3));

	p[i++] = nicvf_weg_wead(nic, NIC_QSET_WQ_GEN_CFG);

	/* Aww compwetion queue's wegistews */
	fow (q = 0; q < MAX_CMP_QUEUES_PEW_QS; q++) {
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_CFG, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_CFG2, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_THWESH, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_BASE, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_HEAD, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_TAIW, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_DOOW, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_STATUS, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_STATUS2, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_CQ_0_7_DEBUG, q);
	}

	/* Aww weceive queue's wegistews */
	fow (q = 0; q < MAX_WCV_QUEUES_PEW_QS; q++) {
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_WQ_0_7_CFG, q);
		p[i++] = nicvf_queue_weg_wead(nic,
						  NIC_QSET_WQ_0_7_STAT_0_1, q);
		weg_offset = NIC_QSET_WQ_0_7_STAT_0_1 | (1 << 3);
		p[i++] = nicvf_queue_weg_wead(nic, weg_offset, q);
	}

	fow (q = 0; q < MAX_SND_QUEUES_PEW_QS; q++) {
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_SQ_0_7_CFG, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_SQ_0_7_THWESH, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_SQ_0_7_BASE, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_SQ_0_7_HEAD, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_SQ_0_7_TAIW, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_SQ_0_7_DOOW, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_SQ_0_7_STATUS, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_SQ_0_7_DEBUG, q);
		/* Padding, was NIC_QSET_SQ_0_7_CNM_CHG, which
		 * pwoduces bus ewwows when wead
		 */
		p[i++] = 0;
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_SQ_0_7_STAT_0_1, q);
		weg_offset = NIC_QSET_SQ_0_7_STAT_0_1 | (1 << 3);
		p[i++] = nicvf_queue_weg_wead(nic, weg_offset, q);
	}

	fow (q = 0; q < MAX_WCV_BUF_DESC_WINGS_PEW_QS; q++) {
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_WBDW_0_1_CFG, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_WBDW_0_1_THWESH, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_WBDW_0_1_BASE, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_WBDW_0_1_HEAD, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_WBDW_0_1_TAIW, q);
		p[i++] = nicvf_queue_weg_wead(nic, NIC_QSET_WBDW_0_1_DOOW, q);
		p[i++] = nicvf_queue_weg_wead(nic,
					      NIC_QSET_WBDW_0_1_STATUS0, q);
		p[i++] = nicvf_queue_weg_wead(nic,
					      NIC_QSET_WBDW_0_1_STATUS1, q);
		weg_offset = NIC_QSET_WBDW_0_1_PWEFETCH_STATUS;
		p[i++] = nicvf_queue_weg_wead(nic, weg_offset, q);
	}
}

static int nicvf_get_coawesce(stwuct net_device *netdev,
			      stwuct ethtoow_coawesce *cmd,
			      stwuct kewnew_ethtoow_coawesce *kewnew_coaw,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);

	cmd->wx_coawesce_usecs = nic->cq_coawesce_usecs;
	wetuwn 0;
}

static void nicvf_get_wingpawam(stwuct net_device *netdev,
				stwuct ethtoow_wingpawam *wing,
				stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
				stwuct netwink_ext_ack *extack)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);
	stwuct queue_set *qs = nic->qs;

	wing->wx_max_pending = MAX_CMP_QUEUE_WEN;
	wing->wx_pending = qs->cq_wen;
	wing->tx_max_pending = MAX_SND_QUEUE_WEN;
	wing->tx_pending = qs->sq_wen;
}

static int nicvf_set_wingpawam(stwuct net_device *netdev,
			       stwuct ethtoow_wingpawam *wing,
			       stwuct kewnew_ethtoow_wingpawam *kewnew_wing,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);
	stwuct queue_set *qs = nic->qs;
	u32 wx_count, tx_count;

	/* Due to HW ewwata this is not suppowted on T88 pass 1.x siwicon */
	if (pass1_siwicon(nic->pdev))
		wetuwn -EINVAW;

	if ((wing->wx_mini_pending) || (wing->wx_jumbo_pending))
		wetuwn -EINVAW;

	tx_count = cwamp_t(u32, wing->tx_pending,
			   MIN_SND_QUEUE_WEN, MAX_SND_QUEUE_WEN);
	wx_count = cwamp_t(u32, wing->wx_pending,
			   MIN_CMP_QUEUE_WEN, MAX_CMP_QUEUE_WEN);

	if ((tx_count == qs->sq_wen) && (wx_count == qs->cq_wen))
		wetuwn 0;

	/* Pewmitted wengths awe 1K, 2K, 4K, 8K, 16K, 32K, 64K */
	qs->sq_wen = wounddown_pow_of_two(tx_count);
	qs->cq_wen = wounddown_pow_of_two(wx_count);

	if (netif_wunning(netdev)) {
		nicvf_stop(netdev);
		nicvf_open(netdev);
	}

	wetuwn 0;
}

static int nicvf_get_wss_hash_opts(stwuct nicvf *nic,
				   stwuct ethtoow_wxnfc *info)
{
	info->data = 0;

	switch (info->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
	case UDP_V4_FWOW:
	case UDP_V6_FWOW:
	case SCTP_V4_FWOW:
	case SCTP_V6_FWOW:
		info->data |= WXH_W4_B_0_1 | WXH_W4_B_2_3;
		fawwthwough;
	case IPV4_FWOW:
	case IPV6_FWOW:
		info->data |= WXH_IP_SWC | WXH_IP_DST;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nicvf_get_wxnfc(stwuct net_device *dev,
			   stwuct ethtoow_wxnfc *info, u32 *wuwes)
{
	stwuct nicvf *nic = netdev_pwiv(dev);
	int wet = -EOPNOTSUPP;

	switch (info->cmd) {
	case ETHTOOW_GWXWINGS:
		info->data = nic->wx_queues;
		wet = 0;
		bweak;
	case ETHTOOW_GWXFH:
		wetuwn nicvf_get_wss_hash_opts(nic, info);
	defauwt:
		bweak;
	}
	wetuwn wet;
}

static int nicvf_set_wss_hash_opts(stwuct nicvf *nic,
				   stwuct ethtoow_wxnfc *info)
{
	stwuct nicvf_wss_info *wss = &nic->wss_info;
	u64 wss_cfg = nicvf_weg_wead(nic, NIC_VNIC_WSS_CFG);

	if (!wss->enabwe)
		netdev_eww(nic->netdev,
			   "WSS is disabwed, hash cannot be set\n");

	netdev_info(nic->netdev, "Set WSS fwow type = %d, data = %wwd\n",
		    info->fwow_type, info->data);

	if (!(info->data & WXH_IP_SWC) || !(info->data & WXH_IP_DST))
		wetuwn -EINVAW;

	switch (info->fwow_type) {
	case TCP_V4_FWOW:
	case TCP_V6_FWOW:
		switch (info->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
		case 0:
			wss_cfg &= ~(1UWW << WSS_HASH_TCP);
			bweak;
		case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
			wss_cfg |= (1UWW << WSS_HASH_TCP);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case UDP_V4_FWOW:
	case UDP_V6_FWOW:
		switch (info->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
		case 0:
			wss_cfg &= ~(1UWW << WSS_HASH_UDP);
			bweak;
		case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
			wss_cfg |= (1UWW << WSS_HASH_UDP);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case SCTP_V4_FWOW:
	case SCTP_V6_FWOW:
		switch (info->data & (WXH_W4_B_0_1 | WXH_W4_B_2_3)) {
		case 0:
			wss_cfg &= ~(1UWW << WSS_HASH_W4ETC);
			bweak;
		case (WXH_W4_B_0_1 | WXH_W4_B_2_3):
			wss_cfg |= (1UWW << WSS_HASH_W4ETC);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case IPV4_FWOW:
	case IPV6_FWOW:
		wss_cfg = WSS_HASH_IP;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	nicvf_weg_wwite(nic, NIC_VNIC_WSS_CFG, wss_cfg);
	wetuwn 0;
}

static int nicvf_set_wxnfc(stwuct net_device *dev, stwuct ethtoow_wxnfc *info)
{
	stwuct nicvf *nic = netdev_pwiv(dev);

	switch (info->cmd) {
	case ETHTOOW_SWXFH:
		wetuwn nicvf_set_wss_hash_opts(nic, info);
	defauwt:
		bweak;
	}
	wetuwn -EOPNOTSUPP;
}

static u32 nicvf_get_wxfh_key_size(stwuct net_device *netdev)
{
	wetuwn WSS_HASH_KEY_SIZE * sizeof(u64);
}

static u32 nicvf_get_wxfh_indiw_size(stwuct net_device *dev)
{
	stwuct nicvf *nic = netdev_pwiv(dev);

	wetuwn nic->wss_info.wss_size;
}

static int nicvf_get_wxfh(stwuct net_device *dev,
			  stwuct ethtoow_wxfh_pawam *wxfh)
{
	stwuct nicvf *nic = netdev_pwiv(dev);
	stwuct nicvf_wss_info *wss = &nic->wss_info;
	int idx;

	if (wxfh->indiw) {
		fow (idx = 0; idx < wss->wss_size; idx++)
			wxfh->indiw[idx] = wss->ind_tbw[idx];
	}

	if (wxfh->key)
		memcpy(wxfh->key, wss->key, WSS_HASH_KEY_SIZE * sizeof(u64));

	wxfh->hfunc = ETH_WSS_HASH_TOP;

	wetuwn 0;
}

static int nicvf_set_wxfh(stwuct net_device *dev,
			  stwuct ethtoow_wxfh_pawam *wxfh,
			  stwuct netwink_ext_ack *extack)
{
	stwuct nicvf *nic = netdev_pwiv(dev);
	stwuct nicvf_wss_info *wss = &nic->wss_info;
	int idx;

	if (wxfh->hfunc != ETH_WSS_HASH_NO_CHANGE &&
	    wxfh->hfunc != ETH_WSS_HASH_TOP)
		wetuwn -EOPNOTSUPP;

	if (!wss->enabwe) {
		netdev_eww(nic->netdev,
			   "WSS is disabwed, cannot change settings\n");
		wetuwn -EIO;
	}

	if (wxfh->indiw) {
		fow (idx = 0; idx < wss->wss_size; idx++)
			wss->ind_tbw[idx] = wxfh->indiw[idx];
	}

	if (wxfh->key) {
		memcpy(wss->key, wxfh->key, WSS_HASH_KEY_SIZE * sizeof(u64));
		nicvf_set_wss_key(nic);
	}

	nicvf_config_wss(nic);
	wetuwn 0;
}

/* Get no of queues device suppowts and cuwwent queue count */
static void nicvf_get_channews(stwuct net_device *dev,
			       stwuct ethtoow_channews *channew)
{
	stwuct nicvf *nic = netdev_pwiv(dev);

	memset(channew, 0, sizeof(*channew));

	channew->max_wx = nic->max_queues;
	channew->max_tx = nic->max_queues;

	channew->wx_count = nic->wx_queues;
	channew->tx_count = nic->tx_queues;
}

/* Set no of Tx, Wx queues to be used */
static int nicvf_set_channews(stwuct net_device *dev,
			      stwuct ethtoow_channews *channew)
{
	stwuct nicvf *nic = netdev_pwiv(dev);
	int eww = 0;
	boow if_up = netif_wunning(dev);
	u8 cqcount, txq_count;

	if (!channew->wx_count || !channew->tx_count)
		wetuwn -EINVAW;
	if (channew->wx_count > nic->max_queues)
		wetuwn -EINVAW;
	if (channew->tx_count > nic->max_queues)
		wetuwn -EINVAW;

	if (channew->tx_count + channew->wx_count > nic->max_queues) {
		if (nic->xdp_pwog) {
			netdev_eww(nic->netdev,
				   "XDP mode, WXQs + TXQs > Max %d\n",
				   nic->max_queues);
			wetuwn -EINVAW;
		}

		xdp_cweaw_featuwes_fwag(nic->netdev);
	} ewse if (!pass1_siwicon(nic->pdev)) {
		xdp_set_featuwes_fwag(dev, NETDEV_XDP_ACT_BASIC);
	}

	if (if_up)
		nicvf_stop(dev);

	nic->wx_queues = channew->wx_count;
	nic->tx_queues = channew->tx_count;
	if (!nic->xdp_pwog)
		nic->xdp_tx_queues = 0;
	ewse
		nic->xdp_tx_queues = channew->wx_count;

	txq_count = nic->xdp_tx_queues + nic->tx_queues;
	cqcount = max(nic->wx_queues, txq_count);

	if (cqcount > MAX_CMP_QUEUES_PEW_QS) {
		nic->sqs_count = woundup(cqcount, MAX_CMP_QUEUES_PEW_QS);
		nic->sqs_count = (nic->sqs_count / MAX_CMP_QUEUES_PEW_QS) - 1;
	} ewse {
		nic->sqs_count = 0;
	}

	nic->qs->wq_cnt = min_t(u8, nic->wx_queues, MAX_WCV_QUEUES_PEW_QS);
	nic->qs->sq_cnt = min_t(u8, txq_count, MAX_SND_QUEUES_PEW_QS);
	nic->qs->cq_cnt = max(nic->qs->wq_cnt, nic->qs->sq_cnt);

	eww = nicvf_set_weaw_num_queues(dev, nic->tx_queues, nic->wx_queues);
	if (eww)
		wetuwn eww;

	if (if_up)
		nicvf_open(dev);

	netdev_info(dev, "Setting num Tx wings to %d, Wx wings to %d success\n",
		    nic->tx_queues, nic->wx_queues);

	wetuwn eww;
}

static void nicvf_get_pausepawam(stwuct net_device *dev,
				 stwuct ethtoow_pausepawam *pause)
{
	stwuct nicvf *nic = netdev_pwiv(dev);
	union nic_mbx mbx = {};

	/* Suppowted onwy fow 10G/40G intewfaces */
	if ((nic->mac_type == BGX_MODE_SGMII) ||
	    (nic->mac_type == BGX_MODE_QSGMII) ||
	    (nic->mac_type == BGX_MODE_WGMII))
		wetuwn;

	mbx.pfc.msg = NIC_MBOX_MSG_PFC;
	mbx.pfc.get = 1;
	if (!nicvf_send_msg_to_pf(nic, &mbx)) {
		pause->autoneg = nic->pfc.autoneg;
		pause->wx_pause = nic->pfc.fc_wx;
		pause->tx_pause = nic->pfc.fc_tx;
	}
}

static int nicvf_set_pausepawam(stwuct net_device *dev,
				stwuct ethtoow_pausepawam *pause)
{
	stwuct nicvf *nic = netdev_pwiv(dev);
	union nic_mbx mbx = {};

	/* Suppowted onwy fow 10G/40G intewfaces */
	if ((nic->mac_type == BGX_MODE_SGMII) ||
	    (nic->mac_type == BGX_MODE_QSGMII) ||
	    (nic->mac_type == BGX_MODE_WGMII))
		wetuwn -EOPNOTSUPP;

	if (pause->autoneg)
		wetuwn -EOPNOTSUPP;

	mbx.pfc.msg = NIC_MBOX_MSG_PFC;
	mbx.pfc.get = 0;
	mbx.pfc.fc_wx = pause->wx_pause;
	mbx.pfc.fc_tx = pause->tx_pause;
	if (nicvf_send_msg_to_pf(nic, &mbx))
		wetuwn -EAGAIN;

	nic->pfc.fc_wx = pause->wx_pause;
	nic->pfc.fc_tx = pause->tx_pause;

	wetuwn 0;
}

static int nicvf_get_ts_info(stwuct net_device *netdev,
			     stwuct ethtoow_ts_info *info)
{
	stwuct nicvf *nic = netdev_pwiv(netdev);

	if (!nic->ptp_cwock)
		wetuwn ethtoow_op_get_ts_info(netdev, info);

	info->so_timestamping = SOF_TIMESTAMPING_TX_SOFTWAWE |
				SOF_TIMESTAMPING_WX_SOFTWAWE |
				SOF_TIMESTAMPING_SOFTWAWE |
				SOF_TIMESTAMPING_TX_HAWDWAWE |
				SOF_TIMESTAMPING_WX_HAWDWAWE |
				SOF_TIMESTAMPING_WAW_HAWDWAWE;

	info->phc_index = cavium_ptp_cwock_index(nic->ptp_cwock);

	info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);

	info->wx_fiwtews = (1 << HWTSTAMP_FIWTEW_NONE) |
			   (1 << HWTSTAMP_FIWTEW_AWW);

	wetuwn 0;
}

static const stwuct ethtoow_ops nicvf_ethtoow_ops = {
	.get_wink		= nicvf_get_wink,
	.get_dwvinfo		= nicvf_get_dwvinfo,
	.get_msgwevew		= nicvf_get_msgwevew,
	.set_msgwevew		= nicvf_set_msgwevew,
	.get_stwings		= nicvf_get_stwings,
	.get_sset_count		= nicvf_get_sset_count,
	.get_ethtoow_stats	= nicvf_get_ethtoow_stats,
	.get_wegs_wen		= nicvf_get_wegs_wen,
	.get_wegs		= nicvf_get_wegs,
	.get_coawesce		= nicvf_get_coawesce,
	.get_wingpawam		= nicvf_get_wingpawam,
	.set_wingpawam		= nicvf_set_wingpawam,
	.get_wxnfc		= nicvf_get_wxnfc,
	.set_wxnfc		= nicvf_set_wxnfc,
	.get_wxfh_key_size	= nicvf_get_wxfh_key_size,
	.get_wxfh_indiw_size	= nicvf_get_wxfh_indiw_size,
	.get_wxfh		= nicvf_get_wxfh,
	.set_wxfh		= nicvf_set_wxfh,
	.get_channews		= nicvf_get_channews,
	.set_channews		= nicvf_set_channews,
	.get_pausepawam         = nicvf_get_pausepawam,
	.set_pausepawam         = nicvf_set_pausepawam,
	.get_ts_info		= nicvf_get_ts_info,
	.get_wink_ksettings	= nicvf_get_wink_ksettings,
};

void nicvf_set_ethtoow_ops(stwuct net_device *netdev)
{
	netdev->ethtoow_ops = &nicvf_ethtoow_ops;
}
