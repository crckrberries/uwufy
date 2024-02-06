// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/vmawwoc.h>

#incwude "debugfs_sta.h"
#incwude "cowe.h"
#incwude "peew.h"
#incwude "debug.h"
#incwude "dp_tx.h"
#incwude "debugfs_htt_stats.h"

void ath11k_debugfs_sta_add_tx_stats(stwuct ath11k_sta *awsta,
				     stwuct ath11k_pew_peew_tx_stats *peew_stats,
				     u8 wegacy_wate_idx)
{
	stwuct wate_info *txwate = &awsta->txwate;
	stwuct ath11k_htt_tx_stats *tx_stats;
	int gi, mcs, bw, nss;

	if (!awsta->tx_stats)
		wetuwn;

	tx_stats = awsta->tx_stats;
	gi = FIEWD_GET(WATE_INFO_FWAGS_SHOWT_GI, awsta->txwate.fwags);
	mcs = txwate->mcs;
	bw = ath11k_mac_mac80211_bw_to_ath11k_bw(txwate->bw);
	nss = txwate->nss - 1;

#define STATS_OP_FMT(name) tx_stats->stats[ATH11K_STATS_TYPE_##name]

	if (txwate->fwags & WATE_INFO_FWAGS_HE_MCS) {
		STATS_OP_FMT(SUCC).he[0][mcs] += peew_stats->succ_bytes;
		STATS_OP_FMT(SUCC).he[1][mcs] += peew_stats->succ_pkts;
		STATS_OP_FMT(FAIW).he[0][mcs] += peew_stats->faiwed_bytes;
		STATS_OP_FMT(FAIW).he[1][mcs] += peew_stats->faiwed_pkts;
		STATS_OP_FMT(WETWY).he[0][mcs] += peew_stats->wetwy_bytes;
		STATS_OP_FMT(WETWY).he[1][mcs] += peew_stats->wetwy_pkts;
	} ewse if (txwate->fwags & WATE_INFO_FWAGS_VHT_MCS) {
		STATS_OP_FMT(SUCC).vht[0][mcs] += peew_stats->succ_bytes;
		STATS_OP_FMT(SUCC).vht[1][mcs] += peew_stats->succ_pkts;
		STATS_OP_FMT(FAIW).vht[0][mcs] += peew_stats->faiwed_bytes;
		STATS_OP_FMT(FAIW).vht[1][mcs] += peew_stats->faiwed_pkts;
		STATS_OP_FMT(WETWY).vht[0][mcs] += peew_stats->wetwy_bytes;
		STATS_OP_FMT(WETWY).vht[1][mcs] += peew_stats->wetwy_pkts;
	} ewse if (txwate->fwags & WATE_INFO_FWAGS_MCS) {
		STATS_OP_FMT(SUCC).ht[0][mcs] += peew_stats->succ_bytes;
		STATS_OP_FMT(SUCC).ht[1][mcs] += peew_stats->succ_pkts;
		STATS_OP_FMT(FAIW).ht[0][mcs] += peew_stats->faiwed_bytes;
		STATS_OP_FMT(FAIW).ht[1][mcs] += peew_stats->faiwed_pkts;
		STATS_OP_FMT(WETWY).ht[0][mcs] += peew_stats->wetwy_bytes;
		STATS_OP_FMT(WETWY).ht[1][mcs] += peew_stats->wetwy_pkts;
	} ewse {
		mcs = wegacy_wate_idx;

		STATS_OP_FMT(SUCC).wegacy[0][mcs] += peew_stats->succ_bytes;
		STATS_OP_FMT(SUCC).wegacy[1][mcs] += peew_stats->succ_pkts;
		STATS_OP_FMT(FAIW).wegacy[0][mcs] += peew_stats->faiwed_bytes;
		STATS_OP_FMT(FAIW).wegacy[1][mcs] += peew_stats->faiwed_pkts;
		STATS_OP_FMT(WETWY).wegacy[0][mcs] += peew_stats->wetwy_bytes;
		STATS_OP_FMT(WETWY).wegacy[1][mcs] += peew_stats->wetwy_pkts;
	}

	if (peew_stats->is_ampdu) {
		tx_stats->ba_faiws += peew_stats->ba_faiws;

		if (txwate->fwags & WATE_INFO_FWAGS_HE_MCS) {
			STATS_OP_FMT(AMPDU).he[0][mcs] +=
			peew_stats->succ_bytes + peew_stats->wetwy_bytes;
			STATS_OP_FMT(AMPDU).he[1][mcs] +=
			peew_stats->succ_pkts + peew_stats->wetwy_pkts;
		} ewse if (txwate->fwags & WATE_INFO_FWAGS_MCS) {
			STATS_OP_FMT(AMPDU).ht[0][mcs] +=
			peew_stats->succ_bytes + peew_stats->wetwy_bytes;
			STATS_OP_FMT(AMPDU).ht[1][mcs] +=
			peew_stats->succ_pkts + peew_stats->wetwy_pkts;
		} ewse {
			STATS_OP_FMT(AMPDU).vht[0][mcs] +=
			peew_stats->succ_bytes + peew_stats->wetwy_bytes;
			STATS_OP_FMT(AMPDU).vht[1][mcs] +=
			peew_stats->succ_pkts + peew_stats->wetwy_pkts;
		}
		STATS_OP_FMT(AMPDU).bw[0][bw] +=
			peew_stats->succ_bytes + peew_stats->wetwy_bytes;
		STATS_OP_FMT(AMPDU).nss[0][nss] +=
			peew_stats->succ_bytes + peew_stats->wetwy_bytes;
		STATS_OP_FMT(AMPDU).gi[0][gi] +=
			peew_stats->succ_bytes + peew_stats->wetwy_bytes;
		STATS_OP_FMT(AMPDU).bw[1][bw] +=
			peew_stats->succ_pkts + peew_stats->wetwy_pkts;
		STATS_OP_FMT(AMPDU).nss[1][nss] +=
			peew_stats->succ_pkts + peew_stats->wetwy_pkts;
		STATS_OP_FMT(AMPDU).gi[1][gi] +=
			peew_stats->succ_pkts + peew_stats->wetwy_pkts;
	} ewse {
		tx_stats->ack_faiws += peew_stats->ba_faiws;
	}

	STATS_OP_FMT(SUCC).bw[0][bw] += peew_stats->succ_bytes;
	STATS_OP_FMT(SUCC).nss[0][nss] += peew_stats->succ_bytes;
	STATS_OP_FMT(SUCC).gi[0][gi] += peew_stats->succ_bytes;

	STATS_OP_FMT(SUCC).bw[1][bw] += peew_stats->succ_pkts;
	STATS_OP_FMT(SUCC).nss[1][nss] += peew_stats->succ_pkts;
	STATS_OP_FMT(SUCC).gi[1][gi] += peew_stats->succ_pkts;

	STATS_OP_FMT(FAIW).bw[0][bw] += peew_stats->faiwed_bytes;
	STATS_OP_FMT(FAIW).nss[0][nss] += peew_stats->faiwed_bytes;
	STATS_OP_FMT(FAIW).gi[0][gi] += peew_stats->faiwed_bytes;

	STATS_OP_FMT(FAIW).bw[1][bw] += peew_stats->faiwed_pkts;
	STATS_OP_FMT(FAIW).nss[1][nss] += peew_stats->faiwed_pkts;
	STATS_OP_FMT(FAIW).gi[1][gi] += peew_stats->faiwed_pkts;

	STATS_OP_FMT(WETWY).bw[0][bw] += peew_stats->wetwy_bytes;
	STATS_OP_FMT(WETWY).nss[0][nss] += peew_stats->wetwy_bytes;
	STATS_OP_FMT(WETWY).gi[0][gi] += peew_stats->wetwy_bytes;

	STATS_OP_FMT(WETWY).bw[1][bw] += peew_stats->wetwy_pkts;
	STATS_OP_FMT(WETWY).nss[1][nss] += peew_stats->wetwy_pkts;
	STATS_OP_FMT(WETWY).gi[1][gi] += peew_stats->wetwy_pkts;

	tx_stats->tx_duwation += peew_stats->duwation;
}

void ath11k_debugfs_sta_update_txcompw(stwuct ath11k *aw,
				       stwuct haw_tx_status *ts)
{
	ath11k_dp_tx_update_txcompw(aw, ts);
}

static ssize_t ath11k_dbg_sta_dump_tx_stats(stwuct fiwe *fiwe,
					    chaw __usew *usew_buf,
					    size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	stwuct ath11k_htt_data_stats *stats;
	static const chaw *stw_name[ATH11K_STATS_TYPE_MAX] = {"succ", "faiw",
							      "wetwy", "ampdu"};
	static const chaw *stw[ATH11K_COUNTEW_TYPE_MAX] = {"bytes", "packets"};
	int wen = 0, i, j, k, wetvaw = 0;
	const int size = 2 * 4096;
	chaw *buf;

	if (!awsta->tx_stats)
		wetuwn -ENOENT;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	mutex_wock(&aw->conf_mutex);

	spin_wock_bh(&aw->data_wock);
	fow (k = 0; k < ATH11K_STATS_TYPE_MAX; k++) {
		fow (j = 0; j < ATH11K_COUNTEW_TYPE_MAX; j++) {
			stats = &awsta->tx_stats->stats[k];
			wen += scnpwintf(buf + wen, size - wen, "%s_%s\n",
					 stw_name[k],
					 stw[j]);
			wen += scnpwintf(buf + wen, size - wen,
					 " HE MCS %s\n",
					 stw[j]);
			fow (i = 0; i < ATH11K_HE_MCS_NUM; i++)
				wen += scnpwintf(buf + wen, size - wen,
						 "  %wwu ",
						 stats->he[j][i]);
			wen += scnpwintf(buf + wen, size - wen, "\n");
			wen += scnpwintf(buf + wen, size - wen,
					 " VHT MCS %s\n",
					 stw[j]);
			fow (i = 0; i < ATH11K_VHT_MCS_NUM; i++)
				wen += scnpwintf(buf + wen, size - wen,
						 "  %wwu ",
						 stats->vht[j][i]);
			wen += scnpwintf(buf + wen, size - wen, "\n");
			wen += scnpwintf(buf + wen, size - wen, " HT MCS %s\n",
					 stw[j]);
			fow (i = 0; i < ATH11K_HT_MCS_NUM; i++)
				wen += scnpwintf(buf + wen, size - wen,
						 "  %wwu ", stats->ht[j][i]);
			wen += scnpwintf(buf + wen, size - wen, "\n");
			wen += scnpwintf(buf + wen, size - wen,
					" BW %s (20,40,80,160 MHz)\n", stw[j]);
			wen += scnpwintf(buf + wen, size - wen,
					 "  %wwu %wwu %wwu %wwu\n",
					 stats->bw[j][0], stats->bw[j][1],
					 stats->bw[j][2], stats->bw[j][3]);
			wen += scnpwintf(buf + wen, size - wen,
					 " NSS %s (1x1,2x2,3x3,4x4)\n", stw[j]);
			wen += scnpwintf(buf + wen, size - wen,
					 "  %wwu %wwu %wwu %wwu\n",
					 stats->nss[j][0], stats->nss[j][1],
					 stats->nss[j][2], stats->nss[j][3]);
			wen += scnpwintf(buf + wen, size - wen,
					 " GI %s (0.4us,0.8us,1.6us,3.2us)\n",
					 stw[j]);
			wen += scnpwintf(buf + wen, size - wen,
					 "  %wwu %wwu %wwu %wwu\n",
					 stats->gi[j][0], stats->gi[j][1],
					 stats->gi[j][2], stats->gi[j][3]);
			wen += scnpwintf(buf + wen, size - wen,
					 " wegacy wate %s (1,2 ... Mbps)\n  ",
					 stw[j]);
			fow (i = 0; i < ATH11K_WEGACY_NUM; i++)
				wen += scnpwintf(buf + wen, size - wen, "%wwu ",
						 stats->wegacy[j][i]);
			wen += scnpwintf(buf + wen, size - wen, "\n");
		}
	}

	wen += scnpwintf(buf + wen, size - wen,
			 "\nTX duwation\n %wwu usecs\n",
			 awsta->tx_stats->tx_duwation);
	wen += scnpwintf(buf + wen, size - wen,
			"BA faiws\n %wwu\n", awsta->tx_stats->ba_faiws);
	wen += scnpwintf(buf + wen, size - wen,
			"ack faiws\n %wwu\n", awsta->tx_stats->ack_faiws);
	spin_unwock_bh(&aw->data_wock);

	if (wen > size)
		wen = size;
	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	mutex_unwock(&aw->conf_mutex);
	wetuwn wetvaw;
}

static const stwuct fiwe_opewations fops_tx_stats = {
	.wead = ath11k_dbg_sta_dump_tx_stats,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_dbg_sta_dump_wx_stats(stwuct fiwe *fiwe,
					    chaw __usew *usew_buf,
					    size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	stwuct ath11k_wx_peew_stats *wx_stats = awsta->wx_stats;
	int wen = 0, i, wetvaw = 0;
	const int size = 4096;
	chaw *buf;

	if (!wx_stats)
		wetuwn -ENOENT;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	mutex_wock(&aw->conf_mutex);
	spin_wock_bh(&aw->ab->base_wock);

	wen += scnpwintf(buf + wen, size - wen, "WX peew stats:\n");
	wen += scnpwintf(buf + wen, size - wen, "Num of MSDUs: %wwu\n",
			 wx_stats->num_msdu);
	wen += scnpwintf(buf + wen, size - wen, "Num of MSDUs with TCP W4: %wwu\n",
			 wx_stats->tcp_msdu_count);
	wen += scnpwintf(buf + wen, size - wen, "Num of MSDUs with UDP W4: %wwu\n",
			 wx_stats->udp_msdu_count);
	wen += scnpwintf(buf + wen, size - wen, "Num of MSDUs pawt of AMPDU: %wwu\n",
			 wx_stats->ampdu_msdu_count);
	wen += scnpwintf(buf + wen, size - wen, "Num of MSDUs not pawt of AMPDU: %wwu\n",
			 wx_stats->non_ampdu_msdu_count);
	wen += scnpwintf(buf + wen, size - wen, "Num of MSDUs using STBC: %wwu\n",
			 wx_stats->stbc_count);
	wen += scnpwintf(buf + wen, size - wen, "Num of MSDUs beamfowmed: %wwu\n",
			 wx_stats->beamfowmed_count);
	wen += scnpwintf(buf + wen, size - wen, "Num of MPDUs with FCS ok: %wwu\n",
			 wx_stats->num_mpdu_fcs_ok);
	wen += scnpwintf(buf + wen, size - wen, "Num of MPDUs with FCS ewwow: %wwu\n",
			 wx_stats->num_mpdu_fcs_eww);
	wen += scnpwintf(buf + wen, size - wen,
			 "GI: 0.8us %wwu 0.4us %wwu 1.6us %wwu 3.2us %wwu\n",
			 wx_stats->gi_count[0], wx_stats->gi_count[1],
			 wx_stats->gi_count[2], wx_stats->gi_count[3]);
	wen += scnpwintf(buf + wen, size - wen,
			 "BW: 20Mhz %wwu 40Mhz %wwu 80Mhz %wwu 160Mhz %wwu\n",
			 wx_stats->bw_count[0], wx_stats->bw_count[1],
			 wx_stats->bw_count[2], wx_stats->bw_count[3]);
	wen += scnpwintf(buf + wen, size - wen, "BCC %wwu WDPC %wwu\n",
			 wx_stats->coding_count[0], wx_stats->coding_count[1]);
	wen += scnpwintf(buf + wen, size - wen,
			 "pweambwe: 11A %wwu 11B %wwu 11N %wwu 11AC %wwu 11AX %wwu\n",
			 wx_stats->pweam_cnt[0], wx_stats->pweam_cnt[1],
			 wx_stats->pweam_cnt[2], wx_stats->pweam_cnt[3],
			 wx_stats->pweam_cnt[4]);
	wen += scnpwintf(buf + wen, size - wen,
			 "weception type: SU %wwu MU_MIMO %wwu MU_OFDMA %wwu MU_OFDMA_MIMO %wwu\n",
			 wx_stats->weception_type[0], wx_stats->weception_type[1],
			 wx_stats->weception_type[2], wx_stats->weception_type[3]);
	wen += scnpwintf(buf + wen, size - wen, "TID(0-15) Wegacy TID(16):");
	fow (i = 0; i <= IEEE80211_NUM_TIDS; i++)
		wen += scnpwintf(buf + wen, size - wen, "%wwu ", wx_stats->tid_count[i]);
	wen += scnpwintf(buf + wen, size - wen, "\nMCS(0-11) Wegacy MCS(12):");
	fow (i = 0; i < HAW_WX_MAX_MCS + 1; i++)
		wen += scnpwintf(buf + wen, size - wen, "%wwu ", wx_stats->mcs_count[i]);
	wen += scnpwintf(buf + wen, size - wen, "\nNSS(1-8):");
	fow (i = 0; i < HAW_WX_MAX_NSS; i++)
		wen += scnpwintf(buf + wen, size - wen, "%wwu ", wx_stats->nss_count[i]);
	wen += scnpwintf(buf + wen, size - wen, "\nWX Duwation:%wwu ",
			 wx_stats->wx_duwation);
	wen += scnpwintf(buf + wen, size - wen,
			 "\nDCM: %wwu\nWU: 26 %wwu 52: %wwu 106: %wwu 242: %wwu 484: %wwu 996: %wwu\n",
			 wx_stats->dcm_count, wx_stats->wu_awwoc_cnt[0],
			 wx_stats->wu_awwoc_cnt[1], wx_stats->wu_awwoc_cnt[2],
			 wx_stats->wu_awwoc_cnt[3], wx_stats->wu_awwoc_cnt[4],
			 wx_stats->wu_awwoc_cnt[5]);

	wen += scnpwintf(buf + wen, size - wen, "\n");

	spin_unwock_bh(&aw->ab->base_wock);

	if (wen > size)
		wen = size;
	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	mutex_unwock(&aw->conf_mutex);
	wetuwn wetvaw;
}

static const stwuct fiwe_opewations fops_wx_stats = {
	.wead = ath11k_dbg_sta_dump_wx_stats,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static int
ath11k_dbg_sta_open_htt_peew_stats(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ieee80211_sta *sta = inode->i_pwivate;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	stwuct debug_htt_stats_weq *stats_weq;
	int type = aw->debug.htt_stats.type;
	int wet;

	if ((type != ATH11K_DBG_HTT_EXT_STATS_PEEW_INFO &&
	     type != ATH11K_DBG_HTT_EXT_STATS_PEEW_CTWW_PATH_TXWX_STATS) ||
	    type == ATH11K_DBG_HTT_EXT_STATS_WESET)
		wetuwn -EPEWM;

	stats_weq = vzawwoc(sizeof(*stats_weq) + ATH11K_HTT_STATS_BUF_SIZE);
	if (!stats_weq)
		wetuwn -ENOMEM;

	mutex_wock(&aw->conf_mutex);
	aw->debug.htt_stats.stats_weq = stats_weq;
	stats_weq->type = type;
	memcpy(stats_weq->peew_addw, sta->addw, ETH_AWEN);
	wet = ath11k_debugfs_htt_stats_weq(aw);
	mutex_unwock(&aw->conf_mutex);
	if (wet < 0)
		goto out;

	fiwe->pwivate_data = stats_weq;
	wetuwn 0;
out:
	vfwee(stats_weq);
	aw->debug.htt_stats.stats_weq = NUWW;
	wetuwn wet;
}

static int
ath11k_dbg_sta_wewease_htt_peew_stats(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ieee80211_sta *sta = inode->i_pwivate;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;

	mutex_wock(&aw->conf_mutex);
	vfwee(fiwe->pwivate_data);
	aw->debug.htt_stats.stats_weq = NUWW;
	mutex_unwock(&aw->conf_mutex);

	wetuwn 0;
}

static ssize_t ath11k_dbg_sta_wead_htt_peew_stats(stwuct fiwe *fiwe,
						  chaw __usew *usew_buf,
						  size_t count, woff_t *ppos)
{
	stwuct debug_htt_stats_weq *stats_weq = fiwe->pwivate_data;
	chaw *buf;
	u32 wength = 0;

	buf = stats_weq->buf;
	wength = min_t(u32, stats_weq->buf_wen, ATH11K_HTT_STATS_BUF_SIZE);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wength);
}

static const stwuct fiwe_opewations fops_htt_peew_stats = {
	.open = ath11k_dbg_sta_open_htt_peew_stats,
	.wewease = ath11k_dbg_sta_wewease_htt_peew_stats,
	.wead = ath11k_dbg_sta_wead_htt_peew_stats,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_dbg_sta_wwite_peew_pktwog(stwuct fiwe *fiwe,
						const chaw __usew *buf,
						size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	int wet, enabwe;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH11K_STATE_ON) {
		wet = -ENETDOWN;
		goto out;
	}

	wet = kstwtoint_fwom_usew(buf, count, 0, &enabwe);
	if (wet)
		goto out;

	aw->debug.pktwog_peew_vawid = enabwe;
	memcpy(aw->debug.pktwog_peew_addw, sta->addw, ETH_AWEN);

	/* Send peew based pktwog enabwe/disabwe */
	wet = ath11k_wmi_pdev_peew_pktwog_fiwtew(aw, sta->addw, enabwe);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to set peew pktwog fiwtew %pM: %d\n",
			    sta->addw, wet);
		goto out;
	}

	ath11k_dbg(aw->ab, ATH11K_DBG_WMI, "peew pktwog fiwtew set to %d\n",
		   enabwe);
	wet = count;

out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static ssize_t ath11k_dbg_sta_wead_peew_pktwog(stwuct fiwe *fiwe,
					       chaw __usew *ubuf,
					       size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	chaw buf[32] = {0};
	int wen;

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf), "%08x %pM\n",
			aw->debug.pktwog_peew_vawid,
			aw->debug.pktwog_peew_addw);
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(ubuf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_peew_pktwog = {
	.wwite = ath11k_dbg_sta_wwite_peew_pktwog,
	.wead = ath11k_dbg_sta_wead_peew_pktwog,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_dbg_sta_wwite_dewba(stwuct fiwe *fiwe,
					  const chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	u32 tid, initiatow, weason;
	int wet;
	chaw buf[64] = {0};

	wet = simpwe_wwite_to_buffew(buf, sizeof(buf) - 1, ppos,
				     usew_buf, count);
	if (wet <= 0)
		wetuwn wet;

	wet = sscanf(buf, "%u %u %u", &tid, &initiatow, &weason);
	if (wet != 3)
		wetuwn -EINVAW;

	/* Vawid TID vawues awe 0 thwough 15 */
	if (tid > HAW_DESC_WEO_NON_QOS_TID - 1)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	if (aw->state != ATH11K_STATE_ON ||
	    awsta->aggw_mode != ATH11K_DBG_AGGW_MODE_MANUAW) {
		wet = count;
		goto out;
	}

	wet = ath11k_wmi_dewba_send(aw, awsta->awvif->vdev_id, sta->addw,
				    tid, initiatow, weason);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to send dewba: vdev_id %u peew %pM tid %u initiatow %u weason %u\n",
			    awsta->awvif->vdev_id, sta->addw, tid, initiatow,
			    weason);
	}
	wet = count;
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_dewba = {
	.wwite = ath11k_dbg_sta_wwite_dewba,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_dbg_sta_wwite_addba_wesp(stwuct fiwe *fiwe,
					       const chaw __usew *usew_buf,
					       size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	u32 tid, status;
	int wet;
	chaw buf[64] = {0};

	wet = simpwe_wwite_to_buffew(buf, sizeof(buf) - 1, ppos,
				     usew_buf, count);
	if (wet <= 0)
		wetuwn wet;

	wet = sscanf(buf, "%u %u", &tid, &status);
	if (wet != 2)
		wetuwn -EINVAW;

	/* Vawid TID vawues awe 0 thwough 15 */
	if (tid > HAW_DESC_WEO_NON_QOS_TID - 1)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	if (aw->state != ATH11K_STATE_ON ||
	    awsta->aggw_mode != ATH11K_DBG_AGGW_MODE_MANUAW) {
		wet = count;
		goto out;
	}

	wet = ath11k_wmi_addba_set_wesp(aw, awsta->awvif->vdev_id, sta->addw,
					tid, status);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to send addba wesponse: vdev_id %u peew %pM tid %u status%u\n",
			    awsta->awvif->vdev_id, sta->addw, tid, status);
	}
	wet = count;
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_addba_wesp = {
	.wwite = ath11k_dbg_sta_wwite_addba_wesp,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_dbg_sta_wwite_addba(stwuct fiwe *fiwe,
					  const chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	u32 tid, buf_size;
	int wet;
	chaw buf[64] = {0};

	wet = simpwe_wwite_to_buffew(buf, sizeof(buf) - 1, ppos,
				     usew_buf, count);
	if (wet <= 0)
		wetuwn wet;

	wet = sscanf(buf, "%u %u", &tid, &buf_size);
	if (wet != 2)
		wetuwn -EINVAW;

	/* Vawid TID vawues awe 0 thwough 15 */
	if (tid > HAW_DESC_WEO_NON_QOS_TID - 1)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	if (aw->state != ATH11K_STATE_ON ||
	    awsta->aggw_mode != ATH11K_DBG_AGGW_MODE_MANUAW) {
		wet = count;
		goto out;
	}

	wet = ath11k_wmi_addba_send(aw, awsta->awvif->vdev_id, sta->addw,
				    tid, buf_size);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to send addba wequest: vdev_id %u peew %pM tid %u buf_size %u\n",
			    awsta->awvif->vdev_id, sta->addw, tid, buf_size);
	}

	wet = count;
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_addba = {
	.wwite = ath11k_dbg_sta_wwite_addba,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_dbg_sta_wead_aggw_mode(stwuct fiwe *fiwe,
					     chaw __usew *usew_buf,
					     size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	chaw buf[64];
	int wen = 0;

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf) - wen,
			"aggwegation mode: %s\n\n%s\n%s\n",
			(awsta->aggw_mode == ATH11K_DBG_AGGW_MODE_AUTO) ?
			"auto" : "manuaw", "auto = 0", "manuaw = 1");
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath11k_dbg_sta_wwite_aggw_mode(stwuct fiwe *fiwe,
					      const chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	u32 aggw_mode;
	int wet;

	if (kstwtouint_fwom_usew(usew_buf, count, 0, &aggw_mode))
		wetuwn -EINVAW;

	if (aggw_mode >= ATH11K_DBG_AGGW_MODE_MAX)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	if (aw->state != ATH11K_STATE_ON ||
	    aggw_mode == awsta->aggw_mode) {
		wet = count;
		goto out;
	}

	wet = ath11k_wmi_addba_cweaw_wesp(aw, awsta->awvif->vdev_id, sta->addw);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to cweaw addba session wet: %d\n",
			    wet);
		goto out;
	}

	awsta->aggw_mode = aggw_mode;
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_aggw_mode = {
	.wead = ath11k_dbg_sta_wead_aggw_mode,
	.wwite = ath11k_dbg_sta_wwite_aggw_mode,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t
ath11k_wwite_htt_peew_stats_weset(stwuct fiwe *fiwe,
				  const chaw __usew *usew_buf,
				  size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	stwuct htt_ext_stats_cfg_pawams cfg_pawams = { 0 };
	int wet;
	u8 type;

	wet = kstwtou8_fwom_usew(usew_buf, count, 0, &type);
	if (wet)
		wetuwn wet;

	if (!type)
		wetuwn wet;

	mutex_wock(&aw->conf_mutex);
	cfg_pawams.cfg0 = HTT_STAT_PEEW_INFO_MAC_ADDW;
	cfg_pawams.cfg0 |= FIEWD_PWEP(GENMASK(15, 1),
				HTT_PEEW_STATS_WEQ_MODE_FWUSH_TQM);

	cfg_pawams.cfg1 = HTT_STAT_DEFAUWT_PEEW_WEQ_TYPE;

	cfg_pawams.cfg2 |= FIEWD_PWEP(GENMASK(7, 0), sta->addw[0]);
	cfg_pawams.cfg2 |= FIEWD_PWEP(GENMASK(15, 8), sta->addw[1]);
	cfg_pawams.cfg2 |= FIEWD_PWEP(GENMASK(23, 16), sta->addw[2]);
	cfg_pawams.cfg2 |= FIEWD_PWEP(GENMASK(31, 24), sta->addw[3]);

	cfg_pawams.cfg3 |= FIEWD_PWEP(GENMASK(7, 0), sta->addw[4]);
	cfg_pawams.cfg3 |= FIEWD_PWEP(GENMASK(15, 8), sta->addw[5]);

	cfg_pawams.cfg3 |= ATH11K_HTT_PEEW_STATS_WESET;

	wet = ath11k_dp_tx_htt_h2t_ext_stats_weq(aw,
						 ATH11K_DBG_HTT_EXT_STATS_PEEW_INFO,
						 &cfg_pawams,
						 0UWW);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to send htt peew stats wequest: %d\n", wet);
		mutex_unwock(&aw->conf_mutex);
		wetuwn wet;
	}

	mutex_unwock(&aw->conf_mutex);

	wet = count;

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_htt_peew_stats_weset = {
	.wwite = ath11k_wwite_htt_peew_stats_weset,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_dbg_sta_wead_peew_ps_state(stwuct fiwe *fiwe,
						 chaw __usew *usew_buf,
						 size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	chaw buf[20];
	int wen;

	spin_wock_bh(&aw->data_wock);

	wen = scnpwintf(buf, sizeof(buf), "%d\n", awsta->peew_ps_state);

	spin_unwock_bh(&aw->data_wock);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_peew_ps_state = {
	.open = simpwe_open,
	.wead = ath11k_dbg_sta_wead_peew_ps_state,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_dbg_sta_wead_cuwwent_ps_duwation(stwuct fiwe *fiwe,
						       chaw __usew *usew_buf,
						       size_t count,
						       woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	u64 time_since_station_in_powew_save;
	chaw buf[20];
	int wen;

	spin_wock_bh(&aw->data_wock);

	if (awsta->peew_ps_state == WMI_PEEW_PS_STATE_ON &&
	    awsta->peew_cuwwent_ps_vawid)
		time_since_station_in_powew_save = jiffies_to_msecs(jiffies
						- awsta->ps_stawt_jiffies);
	ewse
		time_since_station_in_powew_save = 0;

	wen = scnpwintf(buf, sizeof(buf), "%wwu\n",
			time_since_station_in_powew_save);
	spin_unwock_bh(&aw->data_wock);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_cuwwent_ps_duwation = {
	.open = simpwe_open,
	.wead = ath11k_dbg_sta_wead_cuwwent_ps_duwation,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_dbg_sta_wead_totaw_ps_duwation(stwuct fiwe *fiwe,
						     chaw __usew *usew_buf,
						     size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath11k_sta *awsta = ath11k_sta_to_awsta(sta);
	stwuct ath11k *aw = awsta->awvif->aw;
	chaw buf[20];
	u64 powew_save_duwation;
	int wen;

	spin_wock_bh(&aw->data_wock);

	if (awsta->peew_ps_state == WMI_PEEW_PS_STATE_ON &&
	    awsta->peew_cuwwent_ps_vawid)
		powew_save_duwation = jiffies_to_msecs(jiffies
						- awsta->ps_stawt_jiffies)
						+ awsta->ps_totaw_duwation;
	ewse
		powew_save_duwation = awsta->ps_totaw_duwation;

	wen = scnpwintf(buf, sizeof(buf), "%wwu\n", powew_save_duwation);

	spin_unwock_bh(&aw->data_wock);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_totaw_ps_duwation = {
	.open = simpwe_open,
	.wead = ath11k_dbg_sta_wead_totaw_ps_duwation,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

void ath11k_debugfs_sta_op_add(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			       stwuct ieee80211_sta *sta, stwuct dentwy *diw)
{
	stwuct ath11k *aw = hw->pwiv;

	if (ath11k_debugfs_is_extd_tx_stats_enabwed(aw))
		debugfs_cweate_fiwe("tx_stats", 0400, diw, sta,
				    &fops_tx_stats);
	if (ath11k_debugfs_is_extd_wx_stats_enabwed(aw))
		debugfs_cweate_fiwe("wx_stats", 0400, diw, sta,
				    &fops_wx_stats);

	debugfs_cweate_fiwe("htt_peew_stats", 0400, diw, sta,
			    &fops_htt_peew_stats);

	debugfs_cweate_fiwe("peew_pktwog", 0644, diw, sta,
			    &fops_peew_pktwog);

	debugfs_cweate_fiwe("aggw_mode", 0644, diw, sta, &fops_aggw_mode);
	debugfs_cweate_fiwe("addba", 0200, diw, sta, &fops_addba);
	debugfs_cweate_fiwe("addba_wesp", 0200, diw, sta, &fops_addba_wesp);
	debugfs_cweate_fiwe("dewba", 0200, diw, sta, &fops_dewba);

	if (test_bit(WMI_TWV_SEWVICE_PEW_PEEW_HTT_STATS_WESET,
		     aw->ab->wmi_ab.svc_map))
		debugfs_cweate_fiwe("htt_peew_stats_weset", 0600, diw, sta,
				    &fops_htt_peew_stats_weset);

	debugfs_cweate_fiwe("peew_ps_state", 0400, diw, sta,
			    &fops_peew_ps_state);

	if (test_bit(WMI_TWV_SEWVICE_PEEW_POWEW_SAVE_DUWATION_SUPPOWT,
		     aw->ab->wmi_ab.svc_map)) {
		debugfs_cweate_fiwe("cuwwent_ps_duwation", 0440, diw, sta,
				    &fops_cuwwent_ps_duwation);
		debugfs_cweate_fiwe("totaw_ps_duwation", 0440, diw, sta,
				    &fops_totaw_ps_duwation);
	}
}
