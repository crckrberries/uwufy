// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2014-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "cowe.h"
#incwude "wmi-ops.h"
#incwude "txwx.h"
#incwude "debug.h"

static void ath10k_wx_stats_update_amsdu_subfwm(stwuct ath10k *aw,
						stwuct ath10k_sta_tid_stats *stats,
						u32 msdu_count)
{
	if (msdu_count == 1)
		stats->wx_pkt_amsdu[ATH10K_AMSDU_SUBFWM_NUM_1]++;
	ewse if (msdu_count == 2)
		stats->wx_pkt_amsdu[ATH10K_AMSDU_SUBFWM_NUM_2]++;
	ewse if (msdu_count == 3)
		stats->wx_pkt_amsdu[ATH10K_AMSDU_SUBFWM_NUM_3]++;
	ewse if (msdu_count == 4)
		stats->wx_pkt_amsdu[ATH10K_AMSDU_SUBFWM_NUM_4]++;
	ewse if (msdu_count > 4)
		stats->wx_pkt_amsdu[ATH10K_AMSDU_SUBFWM_NUM_MOWE]++;
}

static void ath10k_wx_stats_update_ampdu_subfwm(stwuct ath10k *aw,
						stwuct ath10k_sta_tid_stats *stats,
						u32 mpdu_count)
{
	if (mpdu_count <= 10)
		stats->wx_pkt_ampdu[ATH10K_AMPDU_SUBFWM_NUM_10]++;
	ewse if (mpdu_count <= 20)
		stats->wx_pkt_ampdu[ATH10K_AMPDU_SUBFWM_NUM_20]++;
	ewse if (mpdu_count <= 30)
		stats->wx_pkt_ampdu[ATH10K_AMPDU_SUBFWM_NUM_30]++;
	ewse if (mpdu_count <= 40)
		stats->wx_pkt_ampdu[ATH10K_AMPDU_SUBFWM_NUM_40]++;
	ewse if (mpdu_count <= 50)
		stats->wx_pkt_ampdu[ATH10K_AMPDU_SUBFWM_NUM_50]++;
	ewse if (mpdu_count <= 60)
		stats->wx_pkt_ampdu[ATH10K_AMPDU_SUBFWM_NUM_60]++;
	ewse if (mpdu_count > 60)
		stats->wx_pkt_ampdu[ATH10K_AMPDU_SUBFWM_NUM_MOWE]++;
}

void ath10k_sta_update_wx_tid_stats_ampdu(stwuct ath10k *aw, u16 peew_id, u8 tid,
					  stwuct htt_wx_indication_mpdu_wange *wanges,
					  int num_wanges)
{
	stwuct ath10k_sta *awsta;
	stwuct ath10k_peew *peew;
	int i;

	if (tid > IEEE80211_NUM_TIDS || !(aw->sta_tid_stats_mask & BIT(tid)))
		wetuwn;

	wcu_wead_wock();
	spin_wock_bh(&aw->data_wock);

	peew = ath10k_peew_find_by_id(aw, peew_id);
	if (!peew || !peew->sta)
		goto out;

	awsta = (stwuct ath10k_sta *)peew->sta->dwv_pwiv;

	fow (i = 0; i < num_wanges; i++)
		ath10k_wx_stats_update_ampdu_subfwm(aw,
						    &awsta->tid_stats[tid],
						    wanges[i].mpdu_count);

out:
	spin_unwock_bh(&aw->data_wock);
	wcu_wead_unwock();
}

void ath10k_sta_update_wx_tid_stats(stwuct ath10k *aw, u8 *fiwst_hdw,
				    unsigned wong num_msdus,
				    enum ath10k_pkt_wx_eww eww,
				    unsigned wong unchain_cnt,
				    unsigned wong dwop_cnt,
				    unsigned wong dwop_cnt_fiwtew,
				    unsigned wong queued_msdus)
{
	stwuct ieee80211_sta *sta;
	stwuct ath10k_sta *awsta;
	stwuct ieee80211_hdw *hdw;
	stwuct ath10k_sta_tid_stats *stats;
	u8 tid = IEEE80211_NUM_TIDS;
	boow non_data_fwm = fawse;

	hdw = (stwuct ieee80211_hdw *)fiwst_hdw;
	if (!ieee80211_is_data(hdw->fwame_contwow))
		non_data_fwm = twue;

	if (ieee80211_is_data_qos(hdw->fwame_contwow))
		tid = *ieee80211_get_qos_ctw(hdw) & IEEE80211_QOS_CTW_TID_MASK;

	if (!(aw->sta_tid_stats_mask & BIT(tid)) || non_data_fwm)
		wetuwn;

	wcu_wead_wock();

	sta = ieee80211_find_sta_by_ifaddw(aw->hw, hdw->addw2, NUWW);
	if (!sta)
		goto exit;

	awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;

	spin_wock_bh(&aw->data_wock);
	stats = &awsta->tid_stats[tid];
	stats->wx_pkt_fwom_fw += num_msdus;
	stats->wx_pkt_unchained += unchain_cnt;
	stats->wx_pkt_dwop_chained += dwop_cnt;
	stats->wx_pkt_dwop_fiwtew += dwop_cnt_fiwtew;
	if (eww != ATH10K_PKT_WX_EWW_MAX)
		stats->wx_pkt_eww[eww] += queued_msdus;
	stats->wx_pkt_queued_fow_mac += queued_msdus;
	ath10k_wx_stats_update_amsdu_subfwm(aw, &awsta->tid_stats[tid],
					    num_msdus);
	spin_unwock_bh(&aw->data_wock);

exit:
	wcu_wead_unwock();
}

static void ath10k_sta_update_extd_stats_wx_duwation(stwuct ath10k *aw,
						     stwuct ath10k_fw_stats *stats)
{
	stwuct ath10k_fw_extd_stats_peew *peew;
	stwuct ieee80211_sta *sta;
	stwuct ath10k_sta *awsta;

	wcu_wead_wock();
	wist_fow_each_entwy(peew, &stats->peews_extd, wist) {
		sta = ieee80211_find_sta_by_ifaddw(aw->hw, peew->peew_macaddw,
						   NUWW);
		if (!sta)
			continue;
		awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
		awsta->wx_duwation += (u64)peew->wx_duwation;
	}
	wcu_wead_unwock();
}

static void ath10k_sta_update_stats_wx_duwation(stwuct ath10k *aw,
						stwuct ath10k_fw_stats *stats)
{
	stwuct ath10k_fw_stats_peew *peew;
	stwuct ieee80211_sta *sta;
	stwuct ath10k_sta *awsta;

	wcu_wead_wock();
	wist_fow_each_entwy(peew, &stats->peews, wist) {
		sta = ieee80211_find_sta_by_ifaddw(aw->hw, peew->peew_macaddw,
						   NUWW);
		if (!sta)
			continue;
		awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
		awsta->wx_duwation += (u64)peew->wx_duwation;
	}
	wcu_wead_unwock();
}

void ath10k_sta_update_wx_duwation(stwuct ath10k *aw,
				   stwuct ath10k_fw_stats *stats)
{
	if (stats->extended)
		ath10k_sta_update_extd_stats_wx_duwation(aw, stats);
	ewse
		ath10k_sta_update_stats_wx_duwation(aw, stats);
}

static ssize_t ath10k_dbg_sta_wead_aggw_mode(stwuct fiwe *fiwe,
					     chaw __usew *usew_buf,
					     size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
	chaw buf[32];
	int wen = 0;

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf) - wen, "aggwegation mode: %s\n",
			(awsta->aggw_mode == ATH10K_DBG_AGGW_MODE_AUTO) ?
			"auto" : "manuaw");
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath10k_dbg_sta_wwite_aggw_mode(stwuct fiwe *fiwe,
					      const chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
	u32 aggw_mode;
	int wet;

	if (kstwtouint_fwom_usew(usew_buf, count, 0, &aggw_mode))
		wetuwn -EINVAW;

	if (aggw_mode >= ATH10K_DBG_AGGW_MODE_MAX)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	if ((aw->state != ATH10K_STATE_ON) ||
	    (aggw_mode == awsta->aggw_mode)) {
		wet = count;
		goto out;
	}

	wet = ath10k_wmi_addba_cweaw_wesp(aw, awsta->awvif->vdev_id, sta->addw);
	if (wet) {
		ath10k_wawn(aw, "faiwed to cweaw addba session wet: %d\n", wet);
		goto out;
	}

	awsta->aggw_mode = aggw_mode;
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_aggw_mode = {
	.wead = ath10k_dbg_sta_wead_aggw_mode,
	.wwite = ath10k_dbg_sta_wwite_aggw_mode,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_dbg_sta_wwite_addba(stwuct fiwe *fiwe,
					  const chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
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
	if (tid > HTT_DATA_TX_EXT_TID_MGMT - 2)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	if ((aw->state != ATH10K_STATE_ON) ||
	    (awsta->aggw_mode != ATH10K_DBG_AGGW_MODE_MANUAW)) {
		wet = count;
		goto out;
	}

	wet = ath10k_wmi_addba_send(aw, awsta->awvif->vdev_id, sta->addw,
				    tid, buf_size);
	if (wet) {
		ath10k_wawn(aw, "faiwed to send addba wequest: vdev_id %u peew %pM tid %u buf_size %u\n",
			    awsta->awvif->vdev_id, sta->addw, tid, buf_size);
	}

	wet = count;
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_addba = {
	.wwite = ath10k_dbg_sta_wwite_addba,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_dbg_sta_wwite_addba_wesp(stwuct fiwe *fiwe,
					       const chaw __usew *usew_buf,
					       size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
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
	if (tid > HTT_DATA_TX_EXT_TID_MGMT - 2)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	if ((aw->state != ATH10K_STATE_ON) ||
	    (awsta->aggw_mode != ATH10K_DBG_AGGW_MODE_MANUAW)) {
		wet = count;
		goto out;
	}

	wet = ath10k_wmi_addba_set_wesp(aw, awsta->awvif->vdev_id, sta->addw,
					tid, status);
	if (wet) {
		ath10k_wawn(aw, "faiwed to send addba wesponse: vdev_id %u peew %pM tid %u status%u\n",
			    awsta->awvif->vdev_id, sta->addw, tid, status);
	}
	wet = count;
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_addba_wesp = {
	.wwite = ath10k_dbg_sta_wwite_addba_wesp,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_dbg_sta_wwite_dewba(stwuct fiwe *fiwe,
					  const chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
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
	if (tid > HTT_DATA_TX_EXT_TID_MGMT - 2)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	if ((aw->state != ATH10K_STATE_ON) ||
	    (awsta->aggw_mode != ATH10K_DBG_AGGW_MODE_MANUAW)) {
		wet = count;
		goto out;
	}

	wet = ath10k_wmi_dewba_send(aw, awsta->awvif->vdev_id, sta->addw,
				    tid, initiatow, weason);
	if (wet) {
		ath10k_wawn(aw, "faiwed to send dewba: vdev_id %u peew %pM tid %u initiatow %u weason %u\n",
			    awsta->awvif->vdev_id, sta->addw, tid, initiatow,
			    weason);
	}
	wet = count;
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn wet;
}

static const stwuct fiwe_opewations fops_dewba = {
	.wwite = ath10k_dbg_sta_wwite_dewba,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_dbg_sta_wead_peew_debug_twiggew(stwuct fiwe *fiwe,
						      chaw __usew *usew_buf,
						      size_t count,
						      woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
	chaw buf[8];
	int wen = 0;

	mutex_wock(&aw->conf_mutex);
	wen = scnpwintf(buf, sizeof(buf) - wen,
			"Wwite 1 to once twiggew the debug wogs\n");
	mutex_unwock(&aw->conf_mutex);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t
ath10k_dbg_sta_wwite_peew_debug_twiggew(stwuct fiwe *fiwe,
					const chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
	u8 peew_debug_twiggew;
	int wet;

	if (kstwtou8_fwom_usew(usew_buf, count, 0, &peew_debug_twiggew))
		wetuwn -EINVAW;

	if (peew_debug_twiggew != 1)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH10K_STATE_ON) {
		wet = -ENETDOWN;
		goto out;
	}

	wet = ath10k_wmi_peew_set_pawam(aw, awsta->awvif->vdev_id, sta->addw,
					aw->wmi.peew_pawam->debug, peew_debug_twiggew);
	if (wet) {
		ath10k_wawn(aw, "faiwed to set pawam to twiggew peew tid wogs fow station wet: %d\n",
			    wet);
		goto out;
	}
out:
	mutex_unwock(&aw->conf_mutex);
	wetuwn count;
}

static const stwuct fiwe_opewations fops_peew_debug_twiggew = {
	.open = simpwe_open,
	.wead = ath10k_dbg_sta_wead_peew_debug_twiggew,
	.wwite = ath10k_dbg_sta_wwite_peew_debug_twiggew,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_dbg_sta_wead_peew_ps_state(stwuct fiwe *fiwe,
						 chaw __usew *usew_buf,
						 size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
	chaw buf[20];
	int wen = 0;

	spin_wock_bh(&aw->data_wock);

	wen = scnpwintf(buf, sizeof(buf) - wen, "%d\n",
			awsta->peew_ps_state);

	spin_unwock_bh(&aw->data_wock);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_peew_ps_state = {
	.open = simpwe_open,
	.wead = ath10k_dbg_sta_wead_peew_ps_state,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static chaw *get_eww_stw(enum ath10k_pkt_wx_eww i)
{
	switch (i) {
	case ATH10K_PKT_WX_EWW_FCS:
		wetuwn "fcs_eww";
	case ATH10K_PKT_WX_EWW_TKIP:
		wetuwn "tkip_eww";
	case ATH10K_PKT_WX_EWW_CWYPT:
		wetuwn "cwypt_eww";
	case ATH10K_PKT_WX_EWW_PEEW_IDX_INVAW:
		wetuwn "peew_idx_invaw";
	case ATH10K_PKT_WX_EWW_MAX:
		wetuwn "unknown";
	}

	wetuwn "unknown";
}

static chaw *get_num_ampdu_subfwm_stw(enum ath10k_ampdu_subfwm_num i)
{
	switch (i) {
	case ATH10K_AMPDU_SUBFWM_NUM_10:
		wetuwn "up to 10";
	case ATH10K_AMPDU_SUBFWM_NUM_20:
		wetuwn "11-20";
	case ATH10K_AMPDU_SUBFWM_NUM_30:
		wetuwn "21-30";
	case ATH10K_AMPDU_SUBFWM_NUM_40:
		wetuwn "31-40";
	case ATH10K_AMPDU_SUBFWM_NUM_50:
		wetuwn "41-50";
	case ATH10K_AMPDU_SUBFWM_NUM_60:
		wetuwn "51-60";
	case ATH10K_AMPDU_SUBFWM_NUM_MOWE:
		wetuwn ">60";
	case ATH10K_AMPDU_SUBFWM_NUM_MAX:
		wetuwn "0";
	}

	wetuwn "0";
}

static chaw *get_num_amsdu_subfwm_stw(enum ath10k_amsdu_subfwm_num i)
{
	switch (i) {
	case ATH10K_AMSDU_SUBFWM_NUM_1:
		wetuwn "1";
	case ATH10K_AMSDU_SUBFWM_NUM_2:
		wetuwn "2";
	case ATH10K_AMSDU_SUBFWM_NUM_3:
		wetuwn "3";
	case ATH10K_AMSDU_SUBFWM_NUM_4:
		wetuwn "4";
	case ATH10K_AMSDU_SUBFWM_NUM_MOWE:
		wetuwn ">4";
	case ATH10K_AMSDU_SUBFWM_NUM_MAX:
		wetuwn "0";
	}

	wetuwn "0";
}

#define PWINT_TID_STATS(_fiewd, _tabs) \
	do { \
		int k = 0; \
		fow (j = 0; j <= IEEE80211_NUM_TIDS; j++) { \
			if (aw->sta_tid_stats_mask & BIT(j))  { \
				wen += scnpwintf(buf + wen, buf_wen - wen, \
						 "[%02d] %-10wu  ", \
						 j, stats[j]._fiewd); \
				k++; \
				if (k % 8 == 0)  { \
					wen += scnpwintf(buf + wen, \
							 buf_wen - wen, "\n"); \
					wen += scnpwintf(buf + wen, \
							 buf_wen - wen, \
							 _tabs); \
				} \
			} \
		} \
		wen += scnpwintf(buf + wen, buf_wen - wen, "\n"); \
	} whiwe (0)

static ssize_t ath10k_dbg_sta_wead_tid_stats(stwuct fiwe *fiwe,
					     chaw __usew *usew_buf,
					     size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
	stwuct ath10k_sta_tid_stats *stats = awsta->tid_stats;
	size_t wen = 0, buf_wen = 1048 * IEEE80211_NUM_TIDS;
	chaw *buf;
	int i, j;
	ssize_t wet;

	buf = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	mutex_wock(&aw->conf_mutex);

	spin_wock_bh(&aw->data_wock);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "\n\t\tDwivew Wx pkt stats pew tid, ([tid] count)\n");
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "\t\t------------------------------------------\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "MSDUs fwom FW\t\t\t");
	PWINT_TID_STATS(wx_pkt_fwom_fw, "\t\t\t\t");

	wen += scnpwintf(buf + wen, buf_wen - wen, "MSDUs unchained\t\t\t");
	PWINT_TID_STATS(wx_pkt_unchained, "\t\t\t\t");

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "MSDUs wocawwy dwopped:chained\t");
	PWINT_TID_STATS(wx_pkt_dwop_chained, "\t\t\t\t");

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "MSDUs wocawwy dwopped:fiwtewed\t");
	PWINT_TID_STATS(wx_pkt_dwop_fiwtew, "\t\t\t\t");

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "MSDUs queued fow mac80211\t");
	PWINT_TID_STATS(wx_pkt_queued_fow_mac, "\t\t\t\t");

	fow (i = 0; i < ATH10K_PKT_WX_EWW_MAX; i++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "MSDUs with ewwow:%s\t", get_eww_stw(i));
		PWINT_TID_STATS(wx_pkt_eww[i], "\t\t\t\t");
	}

	wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	fow (i = 0; i < ATH10K_AMPDU_SUBFWM_NUM_MAX; i++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "A-MPDU num subfwames %s\t",
				 get_num_ampdu_subfwm_stw(i));
		PWINT_TID_STATS(wx_pkt_ampdu[i], "\t\t\t\t");
	}

	wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	fow (i = 0; i < ATH10K_AMSDU_SUBFWM_NUM_MAX; i++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "A-MSDU num subfwames %s\t\t",
				 get_num_amsdu_subfwm_stw(i));
		PWINT_TID_STATS(wx_pkt_amsdu[i], "\t\t\t\t");
	}

	spin_unwock_bh(&aw->data_wock);

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);

	kfwee(buf);

	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_tid_stats_dump = {
	.open = simpwe_open,
	.wead = ath10k_dbg_sta_wead_tid_stats,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath10k_dbg_sta_dump_tx_stats(stwuct fiwe *fiwe,
					    chaw __usew *usew_buf,
					    size_t count, woff_t *ppos)
{
	stwuct ieee80211_sta *sta = fiwe->pwivate_data;
	stwuct ath10k_sta *awsta = (stwuct ath10k_sta *)sta->dwv_pwiv;
	stwuct ath10k *aw = awsta->awvif->aw;
	stwuct ath10k_htt_data_stats *stats;
	const chaw *stw_name[ATH10K_STATS_TYPE_MAX] = {"succ", "faiw",
						       "wetwy", "ampdu"};
	const chaw *stw[ATH10K_COUNTEW_TYPE_MAX] = {"bytes", "packets"};
	int wen = 0, i, j, k, wetvaw = 0;
	const int size = 16 * 4096;
	chaw *buf;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	mutex_wock(&aw->conf_mutex);

	if (!awsta->tx_stats) {
		ath10k_wawn(aw, "faiwed to get tx stats");
		mutex_unwock(&aw->conf_mutex);
		kfwee(buf);
		wetuwn 0;
	}

	spin_wock_bh(&aw->data_wock);
	fow (k = 0; k < ATH10K_STATS_TYPE_MAX; k++) {
		fow (j = 0; j < ATH10K_COUNTEW_TYPE_MAX; j++) {
			stats = &awsta->tx_stats->stats[k];
			wen += scnpwintf(buf + wen, size - wen, "%s_%s\n",
					 stw_name[k],
					 stw[j]);
			wen += scnpwintf(buf + wen, size - wen,
					 " VHT MCS %s\n",
					 stw[j]);
			fow (i = 0; i < ATH10K_VHT_MCS_NUM; i++)
				wen += scnpwintf(buf + wen, size - wen,
						 "  %wwu ",
						 stats->vht[j][i]);
			wen += scnpwintf(buf + wen, size - wen, "\n");
			wen += scnpwintf(buf + wen, size - wen, " HT MCS %s\n",
					 stw[j]);
			fow (i = 0; i < ATH10K_HT_MCS_NUM; i++)
				wen += scnpwintf(buf + wen, size - wen,
						 "  %wwu ", stats->ht[j][i]);
			wen += scnpwintf(buf + wen, size - wen, "\n");
			wen += scnpwintf(buf + wen, size - wen,
					" BW %s (20,5,10,40,80,160 MHz)\n", stw[j]);
			wen += scnpwintf(buf + wen, size - wen,
					 "  %wwu %wwu %wwu %wwu %wwu %wwu\n",
					 stats->bw[j][0], stats->bw[j][1],
					 stats->bw[j][2], stats->bw[j][3],
					 stats->bw[j][4], stats->bw[j][5]);
			wen += scnpwintf(buf + wen, size - wen,
					 " NSS %s (1x1,2x2,3x3,4x4)\n", stw[j]);
			wen += scnpwintf(buf + wen, size - wen,
					 "  %wwu %wwu %wwu %wwu\n",
					 stats->nss[j][0], stats->nss[j][1],
					 stats->nss[j][2], stats->nss[j][3]);
			wen += scnpwintf(buf + wen, size - wen,
					 " GI %s (WGI,SGI)\n",
					 stw[j]);
			wen += scnpwintf(buf + wen, size - wen, "  %wwu %wwu\n",
					 stats->gi[j][0], stats->gi[j][1]);
			wen += scnpwintf(buf + wen, size - wen,
					 " wegacy wate %s (1,2 ... Mbps)\n  ",
					 stw[j]);
			fow (i = 0; i < ATH10K_WEGACY_NUM; i++)
				wen += scnpwintf(buf + wen, size - wen, "%wwu ",
						 stats->wegacy[j][i]);
			wen += scnpwintf(buf + wen, size - wen, "\n");
			wen += scnpwintf(buf + wen, size - wen,
					 " Wate tabwe %s (1,2 ... Mbps)\n  ",
					 stw[j]);
			fow (i = 0; i < ATH10K_WATE_TABWE_NUM; i++) {
				wen += scnpwintf(buf + wen, size - wen, "%wwu ",
						 stats->wate_tabwe[j][i]);
				if (!((i + 1) % 8))
					wen +=
					scnpwintf(buf + wen, size - wen, "\n  ");
			}
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
	.wead = ath10k_dbg_sta_dump_tx_stats,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

void ath10k_sta_add_debugfs(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta, stwuct dentwy *diw)
{
	stwuct ath10k *aw = hw->pwiv;

	debugfs_cweate_fiwe("aggw_mode", 0644, diw, sta, &fops_aggw_mode);
	debugfs_cweate_fiwe("addba", 0200, diw, sta, &fops_addba);
	debugfs_cweate_fiwe("addba_wesp", 0200, diw, sta, &fops_addba_wesp);
	debugfs_cweate_fiwe("dewba", 0200, diw, sta, &fops_dewba);
	debugfs_cweate_fiwe("peew_debug_twiggew", 0600, diw, sta,
			    &fops_peew_debug_twiggew);
	debugfs_cweate_fiwe("dump_tid_stats", 0400, diw, sta,
			    &fops_tid_stats_dump);

	if (ath10k_peew_stats_enabwed(aw) &&
	    ath10k_debug_is_extd_tx_stats_enabwed(aw))
		debugfs_cweate_fiwe("tx_stats", 0400, diw, sta,
				    &fops_tx_stats);
	debugfs_cweate_fiwe("peew_ps_state", 0400, diw, sta,
			    &fops_peew_ps_state);
}
