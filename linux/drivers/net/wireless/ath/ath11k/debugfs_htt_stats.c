// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/vmawwoc.h>
#incwude "cowe.h"
#incwude "dp_tx.h"
#incwude "dp_wx.h"
#incwude "debug.h"
#incwude "debugfs_htt_stats.h"

#define HTT_MAX_PWINT_CHAW_PEW_EWEM 15

#define HTT_TWV_HDW_WEN 4

#define PWINT_AWWAY_TO_BUF(out, bufwen, aww, stw, wen, newwine)				\
	do {										\
		int index = 0; u8 i; const chaw *stw_vaw = stw;				\
		const chaw *new_wine = newwine;						\
		if (stw_vaw) {								\
			index += scnpwintf((out + bufwen),				\
				 (ATH11K_HTT_STATS_BUF_SIZE - bufwen),			\
				 "%s = ", stw_vaw);					\
		}									\
		fow (i = 0; i < wen; i++) {						\
			index += scnpwintf((out + bufwen) + index,			\
				 (ATH11K_HTT_STATS_BUF_SIZE - bufwen) - index,		\
				 " %u:%u,", i, aww[i]);					\
		}									\
		index += scnpwintf((out + bufwen) + index,				\
			 (ATH11K_HTT_STATS_BUF_SIZE - bufwen) - index,			\
			  "%s", new_wine);						\
		bufwen += index;							\
	} whiwe (0)

static inwine void htt_pwint_stats_stwing_twv(const void *tag_buf,
					      u16 tag_wen,
					      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_stats_stwing_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u8  i;

	tag_wen = tag_wen >> 2;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_STATS_STWING_TWV:\n");

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "data = ");
	fow (i = 0; i < tag_wen; i++) {
		wen += scnpwintf(buf + wen,
				 buf_wen - wen,
				 "%.*s", 4, (chaw *)&(htt_stats_buf->data[i]));
	}
	/* New wines awe added fow bettew dispway */
	wen += scnpwintf(buf + wen, buf_wen - wen, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_pdev_stats_cmn_twv(const void *tag_buf,
						   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_stats_cmn_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_PDEV_STATS_CMN_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "hw_queued = %u\n",
			 htt_stats_buf->hw_queued);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hw_weaped = %u\n",
			 htt_stats_buf->hw_weaped);
	wen += scnpwintf(buf + wen, buf_wen - wen, "undewwun = %u\n",
			 htt_stats_buf->undewwun);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hw_paused = %u\n",
			 htt_stats_buf->hw_paused);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hw_fwush = %u\n",
			 htt_stats_buf->hw_fwush);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hw_fiwt = %u\n",
			 htt_stats_buf->hw_fiwt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_abowt = %u\n",
			 htt_stats_buf->tx_abowt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_wequeued = %u\n",
			 htt_stats_buf->mpdu_wequeued);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_xwetwy = %u\n",
			 htt_stats_buf->tx_xwetwy);
	wen += scnpwintf(buf + wen, buf_wen - wen, "data_wc = %u\n",
			 htt_stats_buf->data_wc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_dwopped_xwetwy = %u\n",
			 htt_stats_buf->mpdu_dwopped_xwetwy);
	wen += scnpwintf(buf + wen, buf_wen - wen, "iwwegaw_wate_phy_eww = %u\n",
			 htt_stats_buf->iwwgw_wate_phy_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cont_xwetwy = %u\n",
			 htt_stats_buf->cont_xwetwy);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_timeout = %u\n",
			 htt_stats_buf->tx_timeout);
	wen += scnpwintf(buf + wen, buf_wen - wen, "pdev_wesets = %u\n",
			 htt_stats_buf->pdev_wesets);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_undewwun = %u\n",
			 htt_stats_buf->phy_undewwun);
	wen += scnpwintf(buf + wen, buf_wen - wen, "txop_ovf = %u\n",
			 htt_stats_buf->txop_ovf);
	wen += scnpwintf(buf + wen, buf_wen - wen, "seq_posted = %u\n",
			 htt_stats_buf->seq_posted);
	wen += scnpwintf(buf + wen, buf_wen - wen, "seq_faiwed_queueing = %u\n",
			 htt_stats_buf->seq_faiwed_queueing);
	wen += scnpwintf(buf + wen, buf_wen - wen, "seq_compweted = %u\n",
			 htt_stats_buf->seq_compweted);
	wen += scnpwintf(buf + wen, buf_wen - wen, "seq_westawted = %u\n",
			 htt_stats_buf->seq_westawted);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_seq_posted = %u\n",
			 htt_stats_buf->mu_seq_posted);
	wen += scnpwintf(buf + wen, buf_wen - wen, "seq_switch_hw_paused = %u\n",
			 htt_stats_buf->seq_switch_hw_paused);
	wen += scnpwintf(buf + wen, buf_wen - wen, "next_seq_posted_dsw = %u\n",
			 htt_stats_buf->next_seq_posted_dsw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "seq_posted_isw = %u\n",
			 htt_stats_buf->seq_posted_isw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "seq_ctww_cached = %u\n",
			 htt_stats_buf->seq_ctww_cached);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_count_tqm = %u\n",
			 htt_stats_buf->mpdu_count_tqm);
	wen += scnpwintf(buf + wen, buf_wen - wen, "msdu_count_tqm = %u\n",
			 htt_stats_buf->msdu_count_tqm);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_wemoved_tqm = %u\n",
			 htt_stats_buf->mpdu_wemoved_tqm);
	wen += scnpwintf(buf + wen, buf_wen - wen, "msdu_wemoved_tqm = %u\n",
			 htt_stats_buf->msdu_wemoved_tqm);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdus_sw_fwush = %u\n",
			 htt_stats_buf->mpdus_sw_fwush);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdus_hw_fiwtew = %u\n",
			 htt_stats_buf->mpdus_hw_fiwtew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdus_twuncated = %u\n",
			 htt_stats_buf->mpdus_twuncated);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdus_ack_faiwed = %u\n",
			 htt_stats_buf->mpdus_ack_faiwed);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdus_expiwed = %u\n",
			 htt_stats_buf->mpdus_expiwed);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdus_seq_hw_wetwy = %u\n",
			 htt_stats_buf->mpdus_seq_hw_wetwy);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ack_twv_pwoc = %u\n",
			 htt_stats_buf->ack_twv_pwoc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "coex_abowt_mpdu_cnt_vawid = %u\n",
			 htt_stats_buf->coex_abowt_mpdu_cnt_vawid);
	wen += scnpwintf(buf + wen, buf_wen - wen, "coex_abowt_mpdu_cnt = %u\n",
			 htt_stats_buf->coex_abowt_mpdu_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_totaw_ppdus_twied_ota = %u\n",
			 htt_stats_buf->num_totaw_ppdus_twied_ota);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_data_ppdus_twied_ota = %u\n",
			 htt_stats_buf->num_data_ppdus_twied_ota);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wocaw_ctww_mgmt_enqued = %u\n",
			 htt_stats_buf->wocaw_ctww_mgmt_enqued);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wocaw_ctww_mgmt_fweed = %u\n",
			 htt_stats_buf->wocaw_ctww_mgmt_fweed);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wocaw_data_enqued = %u\n",
			 htt_stats_buf->wocaw_data_enqued);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wocaw_data_fweed = %u\n",
			 htt_stats_buf->wocaw_data_fweed);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_twied = %u\n",
			 htt_stats_buf->mpdu_twied);
	wen += scnpwintf(buf + wen, buf_wen - wen, "isw_wait_seq_posted = %u\n",
			 htt_stats_buf->isw_wait_seq_posted);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_active_duw_us_wow = %u\n",
			 htt_stats_buf->tx_active_duw_us_wow);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_active_duw_us_high = %u\n\n",
			 htt_stats_buf->tx_active_duw_us_high);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_stats_uwwn_twv_v(const void *tag_buf,
				   u16 tag_wen,
				   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_stats_uwwn_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_TX_PDEV_MAX_UWWN_STATS);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_PDEV_STATS_UWWN_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->uwwn_stats, "uwwn_stats",
			   num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_stats_fwush_twv_v(const void *tag_buf,
				    u16 tag_wen,
				    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_stats_fwush_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_TX_PDEV_MAX_FWUSH_WEASON_STATS);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_PDEV_STATS_FWUSH_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->fwush_ewws, "fwush_ewws",
			   num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_stats_sifs_twv_v(const void *tag_buf,
				   u16 tag_wen,
				   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_stats_sifs_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_TX_PDEV_MAX_SIFS_BUWST_STATS);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_PDEV_STATS_SIFS_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->sifs_status, "sifs_status",
			   num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_stats_phy_eww_twv_v(const void *tag_buf,
				      u16 tag_wen,
				      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_stats_phy_eww_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_TX_PDEV_MAX_PHY_EWW_STATS);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_PDEV_STATS_PHY_EWW_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->phy_ewws, "phy_ewws",
			   num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_stats_sifs_hist_twv_v(const void *tag_buf,
					u16 tag_wen,
					stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_stats_sifs_hist_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_TX_PDEV_MAX_SIFS_BUWST_HIST_STATS);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_PDEV_STATS_SIFS_HIST_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->sifs_hist_status,
			   "sifs_hist_status", num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_stats_tx_ppdu_stats_twv_v(const void *tag_buf,
					    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_stats_tx_ppdu_stats_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_PDEV_STATS_TX_PPDU_STATS_TWV_V:\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "num_data_ppdus_wegacy_su = %u\n",
			 htt_stats_buf->num_data_ppdus_wegacy_su);

	wen += scnpwintf(buf + wen, buf_wen - wen, "num_data_ppdus_ac_su = %u\n",
			 htt_stats_buf->num_data_ppdus_ac_su);

	wen += scnpwintf(buf + wen, buf_wen - wen, "num_data_ppdus_ax_su = %u\n",
			 htt_stats_buf->num_data_ppdus_ax_su);

	wen += scnpwintf(buf + wen, buf_wen - wen, "num_data_ppdus_ac_su_txbf = %u\n",
			 htt_stats_buf->num_data_ppdus_ac_su_txbf);

	wen += scnpwintf(buf + wen, buf_wen - wen, "num_data_ppdus_ax_su_txbf = %u\n\n",
			 htt_stats_buf->num_data_ppdus_ax_su_txbf);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_stats_twied_mpdu_cnt_hist_twv_v(const void *tag_buf,
						  u16 tag_wen,
						  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_stats_twied_mpdu_cnt_hist_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u32  num_ewements = ((tag_wen - sizeof(htt_stats_buf->hist_bin_size)) >> 2);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_PDEV_STATS_TWIED_MPDU_CNT_HIST_TWV_V:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "TWIED_MPDU_CNT_HIST_BIN_SIZE : %u\n",
			 htt_stats_buf->hist_bin_size);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->twied_mpdu_cnt_hist,
			   "twied_mpdu_cnt_hist", num_ewements, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_hw_stats_intw_misc_twv(const void *tag_buf,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_hw_stats_intw_misc_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	chaw hw_intw_name[HTT_STATS_MAX_HW_INTW_NAME_WEN + 1] = {0};

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_HW_STATS_INTW_MISC_TWV:\n");
	memcpy(hw_intw_name, &(htt_stats_buf->hw_intw_name[0]),
	       HTT_STATS_MAX_HW_INTW_NAME_WEN);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hw_intw_name = %s\n", hw_intw_name);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mask = %u\n",
			 htt_stats_buf->mask);
	wen += scnpwintf(buf + wen, buf_wen - wen, "count = %u\n\n",
			 htt_stats_buf->count);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_hw_stats_wd_timeout_twv(const void *tag_buf,
				  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_hw_stats_wd_timeout_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	chaw hw_moduwe_name[HTT_STATS_MAX_HW_MODUWE_NAME_WEN + 1] = {0};

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_HW_STATS_WD_TIMEOUT_TWV:\n");
	memcpy(hw_moduwe_name, &(htt_stats_buf->hw_moduwe_name[0]),
	       HTT_STATS_MAX_HW_MODUWE_NAME_WEN);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hw_moduwe_name = %s\n",
			 hw_moduwe_name);
	wen += scnpwintf(buf + wen, buf_wen - wen, "count = %u\n",
			 htt_stats_buf->count);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_hw_stats_pdev_ewws_twv(const void *tag_buf,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_hw_stats_pdev_ewws_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_HW_STATS_PDEV_EWWS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_abowt = %u\n",
			 htt_stats_buf->tx_abowt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_abowt_faiw_count = %u\n",
			 htt_stats_buf->tx_abowt_faiw_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_abowt = %u\n",
			 htt_stats_buf->wx_abowt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_abowt_faiw_count = %u\n",
			 htt_stats_buf->wx_abowt_faiw_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wawm_weset = %u\n",
			 htt_stats_buf->wawm_weset);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cowd_weset = %u\n",
			 htt_stats_buf->cowd_weset);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_fwush = %u\n",
			 htt_stats_buf->tx_fwush);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_gwb_weset = %u\n",
			 htt_stats_buf->tx_gwb_weset);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_txq_weset = %u\n",
			 htt_stats_buf->tx_txq_weset);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_timeout_weset = %u\n\n",
			 htt_stats_buf->wx_timeout_weset);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_msdu_fwow_stats_twv(const void *tag_buf,
						 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_msdu_fwow_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_MSDU_FWOW_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_update_timestamp = %u\n",
			 htt_stats_buf->wast_update_timestamp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_add_timestamp = %u\n",
			 htt_stats_buf->wast_add_timestamp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_wemove_timestamp = %u\n",
			 htt_stats_buf->wast_wemove_timestamp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "totaw_pwocessed_msdu_count = %u\n",
			 htt_stats_buf->totaw_pwocessed_msdu_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cuw_msdu_count_in_fwowq = %u\n",
			 htt_stats_buf->cuw_msdu_count_in_fwowq);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sw_peew_id = %u\n",
			 htt_stats_buf->sw_peew_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_fwow_no = %wu\n",
			 FIEWD_GET(HTT_MSDU_FWOW_STATS_TX_FWOW_NO,
				   htt_stats_buf->tx_fwow_no__tid_num__dwop_wuwe));
	wen += scnpwintf(buf + wen, buf_wen - wen, "tid_num = %wu\n",
			 FIEWD_GET(HTT_MSDU_FWOW_STATS_TID_NUM,
				   htt_stats_buf->tx_fwow_no__tid_num__dwop_wuwe));
	wen += scnpwintf(buf + wen, buf_wen - wen, "dwop_wuwe = %wu\n",
			 FIEWD_GET(HTT_MSDU_FWOW_STATS_DWOP_WUWE,
				   htt_stats_buf->tx_fwow_no__tid_num__dwop_wuwe));
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_cycwe_enqueue_count = %u\n",
			 htt_stats_buf->wast_cycwe_enqueue_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_cycwe_dequeue_count = %u\n",
			 htt_stats_buf->wast_cycwe_dequeue_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_cycwe_dwop_count = %u\n",
			 htt_stats_buf->wast_cycwe_dwop_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cuwwent_dwop_th = %u\n\n",
			 htt_stats_buf->cuwwent_dwop_th);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_tid_stats_twv(const void *tag_buf,
					      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_tid_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	chaw tid_name[MAX_HTT_TID_NAME + 1] = {0};

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_TID_STATS_TWV:\n");
	memcpy(tid_name, &(htt_stats_buf->tid_name[0]), MAX_HTT_TID_NAME);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tid_name = %s\n", tid_name);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sw_peew_id = %wu\n",
			 FIEWD_GET(HTT_TX_TID_STATS_SW_PEEW_ID,
				   htt_stats_buf->sw_peew_id__tid_num));
	wen += scnpwintf(buf + wen, buf_wen - wen, "tid_num = %wu\n",
			 FIEWD_GET(HTT_TX_TID_STATS_TID_NUM,
				   htt_stats_buf->sw_peew_id__tid_num));
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_sched_pending = %wu\n",
			 FIEWD_GET(HTT_TX_TID_STATS_NUM_SCHED_PENDING,
				   htt_stats_buf->num_sched_pending__num_ppdu_in_hwq));
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_ppdu_in_hwq = %wu\n",
			 FIEWD_GET(HTT_TX_TID_STATS_NUM_PPDU_IN_HWQ,
				   htt_stats_buf->num_sched_pending__num_ppdu_in_hwq));
	wen += scnpwintf(buf + wen, buf_wen - wen, "tid_fwags = 0x%x\n",
			 htt_stats_buf->tid_fwags);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hw_queued = %u\n",
			 htt_stats_buf->hw_queued);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hw_weaped = %u\n",
			 htt_stats_buf->hw_weaped);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdus_hw_fiwtew = %u\n",
			 htt_stats_buf->mpdus_hw_fiwtew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qdepth_bytes = %u\n",
			 htt_stats_buf->qdepth_bytes);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qdepth_num_msdu = %u\n",
			 htt_stats_buf->qdepth_num_msdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qdepth_num_mpdu = %u\n",
			 htt_stats_buf->qdepth_num_mpdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_scheduwed_tsmp = %u\n",
			 htt_stats_buf->wast_scheduwed_tsmp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "pause_moduwe_id = %u\n",
			 htt_stats_buf->pause_moduwe_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "bwock_moduwe_id = %u\n\n",
			 htt_stats_buf->bwock_moduwe_id);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_tid_stats_v1_twv(const void *tag_buf,
						 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_tid_stats_v1_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	chaw tid_name[MAX_HTT_TID_NAME + 1] = {0};

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_TID_STATS_V1_TWV:\n");
	memcpy(tid_name, &(htt_stats_buf->tid_name[0]), MAX_HTT_TID_NAME);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tid_name = %s\n", tid_name);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sw_peew_id = %wu\n",
			 FIEWD_GET(HTT_TX_TID_STATS_V1_SW_PEEW_ID,
				   htt_stats_buf->sw_peew_id__tid_num));
	wen += scnpwintf(buf + wen, buf_wen - wen, "tid_num = %wu\n",
			 FIEWD_GET(HTT_TX_TID_STATS_V1_TID_NUM,
				   htt_stats_buf->sw_peew_id__tid_num));
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_sched_pending = %wu\n",
			 FIEWD_GET(HTT_TX_TID_STATS_V1_NUM_SCHED_PENDING,
				   htt_stats_buf->num_sched_pending__num_ppdu_in_hwq));
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_ppdu_in_hwq = %wu\n",
			 FIEWD_GET(HTT_TX_TID_STATS_V1_NUM_PPDU_IN_HWQ,
				   htt_stats_buf->num_sched_pending__num_ppdu_in_hwq));
	wen += scnpwintf(buf + wen, buf_wen - wen, "tid_fwags = 0x%x\n",
			 htt_stats_buf->tid_fwags);
	wen += scnpwintf(buf + wen, buf_wen - wen, "max_qdepth_bytes = %u\n",
			 htt_stats_buf->max_qdepth_bytes);
	wen += scnpwintf(buf + wen, buf_wen - wen, "max_qdepth_n_msdus = %u\n",
			 htt_stats_buf->max_qdepth_n_msdus);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wsvd = %u\n",
			 htt_stats_buf->wsvd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qdepth_bytes = %u\n",
			 htt_stats_buf->qdepth_bytes);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qdepth_num_msdu = %u\n",
			 htt_stats_buf->qdepth_num_msdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qdepth_num_mpdu = %u\n",
			 htt_stats_buf->qdepth_num_mpdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_scheduwed_tsmp = %u\n",
			 htt_stats_buf->wast_scheduwed_tsmp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "pause_moduwe_id = %u\n",
			 htt_stats_buf->pause_moduwe_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "bwock_moduwe_id = %u\n",
			 htt_stats_buf->bwock_moduwe_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "awwow_n_fwags = 0x%x\n",
			 htt_stats_buf->awwow_n_fwags);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sendn_fwms_awwowed = %u\n\n",
			 htt_stats_buf->sendn_fwms_awwowed);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_wx_tid_stats_twv(const void *tag_buf,
					      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_tid_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	chaw tid_name[MAX_HTT_TID_NAME + 1] = {0};

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WX_TID_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "sw_peew_id = %wu\n",
			 FIEWD_GET(HTT_WX_TID_STATS_SW_PEEW_ID,
				   htt_stats_buf->sw_peew_id__tid_num));
	wen += scnpwintf(buf + wen, buf_wen - wen, "tid_num = %wu\n",
			 FIEWD_GET(HTT_WX_TID_STATS_TID_NUM,
				   htt_stats_buf->sw_peew_id__tid_num));
	memcpy(tid_name, &(htt_stats_buf->tid_name[0]), MAX_HTT_TID_NAME);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tid_name = %s\n", tid_name);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dup_in_weowdew = %u\n",
			 htt_stats_buf->dup_in_weowdew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dup_past_outside_window = %u\n",
			 htt_stats_buf->dup_past_outside_window);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dup_past_within_window = %u\n",
			 htt_stats_buf->dup_past_within_window);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wxdesc_eww_decwypt = %u\n\n",
			 htt_stats_buf->wxdesc_eww_decwypt);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_countew_twv(const void *tag_buf,
					 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_countew_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_COUNTEW_TWV:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->countew_name,
			   "countew_name",
			   HTT_MAX_COUNTEW_NAME, "\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "count = %u\n\n",
			 htt_stats_buf->count);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_peew_stats_cmn_twv(const void *tag_buf,
						stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_peew_stats_cmn_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_PEEW_STATS_CMN_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "ppdu_cnt = %u\n",
			 htt_stats_buf->ppdu_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_cnt = %u\n",
			 htt_stats_buf->mpdu_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "msdu_cnt = %u\n",
			 htt_stats_buf->msdu_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "pause_bitmap = %u\n",
			 htt_stats_buf->pause_bitmap);
	wen += scnpwintf(buf + wen, buf_wen - wen, "bwock_bitmap = %u\n",
			 htt_stats_buf->bwock_bitmap);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_wssi = %d\n",
			 htt_stats_buf->wssi);
	wen += scnpwintf(buf + wen, buf_wen - wen, "enqueued_count = %wwu\n",
			 htt_stats_buf->peew_enqueued_count_wow |
			 ((u64)htt_stats_buf->peew_enqueued_count_high << 32));
	wen += scnpwintf(buf + wen, buf_wen - wen, "dequeued_count = %wwu\n",
			 htt_stats_buf->peew_dequeued_count_wow |
			 ((u64)htt_stats_buf->peew_dequeued_count_high << 32));
	wen += scnpwintf(buf + wen, buf_wen - wen, "dwopped_count = %wwu\n",
			 htt_stats_buf->peew_dwopped_count_wow |
			 ((u64)htt_stats_buf->peew_dwopped_count_high << 32));
	wen += scnpwintf(buf + wen, buf_wen - wen, "twansmitted_ppdu_bytes = %wwu\n",
			 htt_stats_buf->ppdu_twansmitted_bytes_wow |
			 ((u64)htt_stats_buf->ppdu_twansmitted_bytes_high << 32));
	wen += scnpwintf(buf + wen, buf_wen - wen, "ttw_wemoved_count = %u\n",
			 htt_stats_buf->peew_ttw_wemoved_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "inactive_time = %u\n\n",
			 htt_stats_buf->inactive_time);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_peew_detaiws_twv(const void *tag_buf,
					      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_peew_detaiws_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_PEEW_DETAIWS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "peew_type = %u\n",
			 htt_stats_buf->peew_type);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sw_peew_id = %u\n",
			 htt_stats_buf->sw_peew_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "vdev_id = %wu\n",
			 FIEWD_GET(HTT_PEEW_DETAIWS_VDEV_ID,
				   htt_stats_buf->vdev_pdev_ast_idx));
	wen += scnpwintf(buf + wen, buf_wen - wen, "pdev_id = %wu\n",
			 FIEWD_GET(HTT_PEEW_DETAIWS_PDEV_ID,
				   htt_stats_buf->vdev_pdev_ast_idx));
	wen += scnpwintf(buf + wen, buf_wen - wen, "ast_idx = %wu\n",
			 FIEWD_GET(HTT_PEEW_DETAIWS_AST_IDX,
				   htt_stats_buf->vdev_pdev_ast_idx));
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "mac_addw = %02wx:%02wx:%02wx:%02wx:%02wx:%02wx\n",
			 FIEWD_GET(HTT_MAC_ADDW_W32_0,
				   htt_stats_buf->mac_addw.mac_addw_w32),
			 FIEWD_GET(HTT_MAC_ADDW_W32_1,
				   htt_stats_buf->mac_addw.mac_addw_w32),
			 FIEWD_GET(HTT_MAC_ADDW_W32_2,
				   htt_stats_buf->mac_addw.mac_addw_w32),
			 FIEWD_GET(HTT_MAC_ADDW_W32_3,
				   htt_stats_buf->mac_addw.mac_addw_w32),
			 FIEWD_GET(HTT_MAC_ADDW_H16_0,
				   htt_stats_buf->mac_addw.mac_addw_h16),
			 FIEWD_GET(HTT_MAC_ADDW_H16_1,
				   htt_stats_buf->mac_addw.mac_addw_h16));
	wen += scnpwintf(buf + wen, buf_wen - wen, "peew_fwags = 0x%x\n",
			 htt_stats_buf->peew_fwags);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qpeew_fwags = 0x%x\n\n",
			 htt_stats_buf->qpeew_fwags);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_peew_wate_stats_twv(const void *tag_buf,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_peew_wate_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u8 j;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_PEEW_WATE_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_wdpc = %u\n",
			 htt_stats_buf->tx_wdpc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wts_cnt = %u\n",
			 htt_stats_buf->wts_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ack_wssi = %u\n",
			 htt_stats_buf->ack_wssi);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_mcs, "tx_mcs",
			   HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_su_mcs, "tx_su_mcs",
			   HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_mu_mcs, "tx_mu_mcs",
			   HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_nss, "tx_nss",
			   HTT_TX_PDEV_STATS_NUM_SPATIAW_STWEAMS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_bw, "tx_bw",
			   HTT_TX_PDEV_STATS_NUM_BW_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_stbc, "tx_stbc",
			   HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_pweam, "tx_pweam",
			   HTT_TX_PDEV_STATS_NUM_PWEAMBWE_TYPES, "\n");

	fow (j = 0; j < HTT_TX_PEEW_STATS_NUM_GI_COUNTEWS; j++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "tx_gi[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_gi[j], NUWW,
				   HTT_TX_PEEW_STATS_NUM_MCS_COUNTEWS, "\n");
	}

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_dcm, "tx_dcm",
			   HTT_TX_PDEV_STATS_NUM_DCM_COUNTEWS, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_wx_peew_wate_stats_twv(const void *tag_buf,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_peew_wate_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u8 j;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WX_PEEW_WATE_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "nsts = %u\n",
			 htt_stats_buf->nsts);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_wdpc = %u\n",
			 htt_stats_buf->wx_wdpc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wts_cnt = %u\n",
			 htt_stats_buf->wts_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wssi_mgmt = %u\n",
			 htt_stats_buf->wssi_mgmt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wssi_data = %u\n",
			 htt_stats_buf->wssi_data);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wssi_comb = %u\n",
			 htt_stats_buf->wssi_comb);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_mcs, "wx_mcs",
			   HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_nss, "wx_nss",
			   HTT_WX_PDEV_STATS_NUM_SPATIAW_STWEAMS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_dcm, "wx_dcm",
			   HTT_WX_PDEV_STATS_NUM_DCM_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_stbc, "wx_stbc",
			   HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_bw, "wx_bw",
			   HTT_WX_PDEV_STATS_NUM_BW_COUNTEWS, "\n");

	fow (j = 0; j < HTT_WX_PEEW_STATS_NUM_SPATIAW_STWEAMS; j++) {
		wen += scnpwintf(buf + wen, (buf_wen - wen),
				 "wssi_chain[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wssi_chain[j], NUWW,
				   HTT_WX_PEEW_STATS_NUM_BW_COUNTEWS, "\n");
	}

	fow (j = 0; j < HTT_WX_PEEW_STATS_NUM_GI_COUNTEWS; j++) {
		wen += scnpwintf(buf + wen, (buf_wen - wen),
				 "wx_gi[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_gi[j], NUWW,
				   HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	}

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_pweam, "wx_pweam",
			   HTT_WX_PDEV_STATS_NUM_PWEAMBWE_TYPES, "\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_mu_mimo_sch_stats_twv(const void *tag_buf,
				       stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_mu_mimo_sch_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_HWQ_MU_MIMO_SCH_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_sch_posted = %u\n",
			 htt_stats_buf->mu_mimo_sch_posted);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_sch_faiwed = %u\n",
			 htt_stats_buf->mu_mimo_sch_faiwed);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_ppdu_posted = %u\n\n",
			 htt_stats_buf->mu_mimo_ppdu_posted);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_mu_mimo_mpdu_stats_twv(const void *tag_buf,
					stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_mu_mimo_mpdu_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_HWQ_MU_MIMO_MPDU_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_mpdus_queued_usw = %u\n",
			 htt_stats_buf->mu_mimo_mpdus_queued_usw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_mpdus_twied_usw = %u\n",
			 htt_stats_buf->mu_mimo_mpdus_twied_usw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_mpdus_faiwed_usw = %u\n",
			 htt_stats_buf->mu_mimo_mpdus_faiwed_usw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_mpdus_wequeued_usw = %u\n",
			 htt_stats_buf->mu_mimo_mpdus_wequeued_usw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_eww_no_ba_usw = %u\n",
			 htt_stats_buf->mu_mimo_eww_no_ba_usw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_mpdu_undewwun_usw = %u\n",
			 htt_stats_buf->mu_mimo_mpdu_undewwun_usw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_ampdu_undewwun_usw = %u\n\n",
			 htt_stats_buf->mu_mimo_ampdu_undewwun_usw);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_mu_mimo_cmn_stats_twv(const void *tag_buf,
				       stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_mu_mimo_cmn_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_HWQ_MU_MIMO_CMN_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_TX_HWQ_STATS_MAC_ID,
				   htt_stats_buf->mac_id__hwq_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwq_id = %wu\n\n",
			 FIEWD_GET(HTT_TX_HWQ_STATS_HWQ_ID,
				   htt_stats_buf->mac_id__hwq_id__wowd));

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_stats_cmn_twv(const void *tag_buf, stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_stats_cmn_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	/* TODO: HKDBG */
	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_HWQ_STATS_CMN_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_TX_HWQ_STATS_MAC_ID,
				   htt_stats_buf->mac_id__hwq_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwq_id = %wu\n",
			 FIEWD_GET(HTT_TX_HWQ_STATS_HWQ_ID,
				   htt_stats_buf->mac_id__hwq_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "xwetwy = %u\n",
			 htt_stats_buf->xwetwy);
	wen += scnpwintf(buf + wen, buf_wen - wen, "undewwun_cnt = %u\n",
			 htt_stats_buf->undewwun_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fwush_cnt = %u\n",
			 htt_stats_buf->fwush_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fiwt_cnt = %u\n",
			 htt_stats_buf->fiwt_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "nuww_mpdu_bmap = %u\n",
			 htt_stats_buf->nuww_mpdu_bmap);
	wen += scnpwintf(buf + wen, buf_wen - wen, "usew_ack_faiwuwe = %u\n",
			 htt_stats_buf->usew_ack_faiwuwe);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ack_twv_pwoc = %u\n",
			 htt_stats_buf->ack_twv_pwoc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_id_pwoc = %u\n",
			 htt_stats_buf->sched_id_pwoc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "nuww_mpdu_tx_count = %u\n",
			 htt_stats_buf->nuww_mpdu_tx_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_bmap_not_wecvd = %u\n",
			 htt_stats_buf->mpdu_bmap_not_wecvd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_baw = %u\n",
			 htt_stats_buf->num_baw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wts = %u\n",
			 htt_stats_buf->wts);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cts2sewf = %u\n",
			 htt_stats_buf->cts2sewf);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qos_nuww = %u\n",
			 htt_stats_buf->qos_nuww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_twied_cnt = %u\n",
			 htt_stats_buf->mpdu_twied_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_queued_cnt = %u\n",
			 htt_stats_buf->mpdu_queued_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_ack_faiw_cnt = %u\n",
			 htt_stats_buf->mpdu_ack_faiw_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_fiwt_cnt = %u\n",
			 htt_stats_buf->mpdu_fiwt_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fawse_mpdu_ack_count = %u\n",
			 htt_stats_buf->fawse_mpdu_ack_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "txq_timeout = %u\n\n",
			 htt_stats_buf->txq_timeout);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_difs_watency_stats_twv_v(const void *tag_buf,
					  u16 tag_wen,
					  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_difs_watency_stats_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 data_wen = min_t(u16, (tag_wen >> 2), HTT_TX_HWQ_MAX_DIFS_WATENCY_BINS);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_HWQ_DIFS_WATENCY_STATS_TWV_V:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "hist_intvw = %u\n",
			 htt_stats_buf->hist_intvw);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->difs_watency_hist,
			   "difs_watency_hist", data_wen, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_cmd_wesuwt_stats_twv_v(const void *tag_buf,
					u16 tag_wen,
					stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_cmd_wesuwt_stats_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 data_wen;

	data_wen = min_t(u16, (tag_wen >> 2), HTT_TX_HWQ_MAX_CMD_WESUWT_STATS);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_HWQ_CMD_WESUWT_STATS_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->cmd_wesuwt, "cmd_wesuwt",
			   data_wen, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_cmd_staww_stats_twv_v(const void *tag_buf,
				       u16 tag_wen,
				       stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_cmd_staww_stats_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems;

	num_ewems = min_t(u16, (tag_wen >> 2), HTT_TX_HWQ_MAX_CMD_STAWW_STATS);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_HWQ_CMD_STAWW_STATS_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->cmd_staww_status,
			   "cmd_staww_status", num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_fes_wesuwt_stats_twv_v(const void *tag_buf,
					u16 tag_wen,
					stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_fes_wesuwt_stats_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems;

	num_ewems = min_t(u16, (tag_wen >> 2), HTT_TX_HWQ_MAX_FES_WESUWT_STATS);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_HWQ_FES_WESUWT_STATS_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->fes_wesuwt, "fes_wesuwt",
			   num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_twied_mpdu_cnt_hist_twv_v(const void *tag_buf,
					   u16 tag_wen,
					   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_twied_mpdu_cnt_hist_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u32  num_ewements = ((tag_wen -
			    sizeof(htt_stats_buf->hist_bin_size)) >> 2);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_HWQ_TWIED_MPDU_CNT_HIST_TWV_V:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "TWIED_MPDU_CNT_HIST_BIN_SIZE : %u\n",
			 htt_stats_buf->hist_bin_size);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->twied_mpdu_cnt_hist,
			   "twied_mpdu_cnt_hist", num_ewements, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_hwq_txop_used_cnt_hist_twv_v(const void *tag_buf,
					  u16 tag_wen,
					  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_hwq_txop_used_cnt_hist_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u32 num_ewements = tag_wen >> 2;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_HWQ_TXOP_USED_CNT_HIST_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->txop_used_cnt_hist,
			   "txop_used_cnt_hist", num_ewements, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_sounding_stats_twv(const void *tag_buf,
						   stwuct debug_htt_stats_weq *stats_weq)
{
	s32 i;
	const stwuct htt_tx_sounding_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	const u32 *cbf_20 = htt_stats_buf->cbf_20;
	const u32 *cbf_40 = htt_stats_buf->cbf_40;
	const u32 *cbf_80 = htt_stats_buf->cbf_80;
	const u32 *cbf_160 = htt_stats_buf->cbf_160;

	if (htt_stats_buf->tx_sounding_mode == HTT_TX_AC_SOUNDING_MODE) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "\nHTT_TX_AC_SOUNDING_STATS_TWV:\n\n");
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ac_cbf_20 = IBF : %u, SU_SIFS : %u, SU_WBO : %u, MU_SIFS : %u, MU_WBO : %u\n",
				 cbf_20[HTT_IMPWICIT_TXBF_STEEW_STATS],
				 cbf_20[HTT_EXPWICIT_TXBF_SU_SIFS_STEEW_STATS],
				 cbf_20[HTT_EXPWICIT_TXBF_SU_WBO_STEEW_STATS],
				 cbf_20[HTT_EXPWICIT_TXBF_MU_SIFS_STEEW_STATS],
				 cbf_20[HTT_EXPWICIT_TXBF_MU_WBO_STEEW_STATS]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ac_cbf_40 = IBF : %u, SU_SIFS : %u, SU_WBO : %u, MU_SIFS : %u, MU_WBO : %u\n",
				 cbf_40[HTT_IMPWICIT_TXBF_STEEW_STATS],
				 cbf_40[HTT_EXPWICIT_TXBF_SU_SIFS_STEEW_STATS],
				 cbf_40[HTT_EXPWICIT_TXBF_SU_WBO_STEEW_STATS],
				 cbf_40[HTT_EXPWICIT_TXBF_MU_SIFS_STEEW_STATS],
				 cbf_40[HTT_EXPWICIT_TXBF_MU_WBO_STEEW_STATS]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ac_cbf_80 = IBF : %u, SU_SIFS : %u, SU_WBO : %u, MU_SIFS : %u, MU_WBO : %u\n",
				 cbf_80[HTT_IMPWICIT_TXBF_STEEW_STATS],
				 cbf_80[HTT_EXPWICIT_TXBF_SU_SIFS_STEEW_STATS],
				 cbf_80[HTT_EXPWICIT_TXBF_SU_WBO_STEEW_STATS],
				 cbf_80[HTT_EXPWICIT_TXBF_MU_SIFS_STEEW_STATS],
				 cbf_80[HTT_EXPWICIT_TXBF_MU_WBO_STEEW_STATS]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ac_cbf_160 = IBF : %u, SU_SIFS : %u, SU_WBO : %u, MU_SIFS : %u, MU_WBO : %u\n",
				 cbf_160[HTT_IMPWICIT_TXBF_STEEW_STATS],
				 cbf_160[HTT_EXPWICIT_TXBF_SU_SIFS_STEEW_STATS],
				 cbf_160[HTT_EXPWICIT_TXBF_SU_WBO_STEEW_STATS],
				 cbf_160[HTT_EXPWICIT_TXBF_MU_SIFS_STEEW_STATS],
				 cbf_160[HTT_EXPWICIT_TXBF_MU_WBO_STEEW_STATS]);

		fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_AC_MUMIMO_USEW_STATS; i++) {
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "Sounding Usew %u = 20MHz: %u, 40MHz : %u, 80MHz: %u, 160MHz: %u\n",
					 i,
					 htt_stats_buf->sounding[0],
					 htt_stats_buf->sounding[1],
					 htt_stats_buf->sounding[2],
					 htt_stats_buf->sounding[3]);
		}
	} ewse if (htt_stats_buf->tx_sounding_mode == HTT_TX_AX_SOUNDING_MODE) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "\nHTT_TX_AX_SOUNDING_STATS_TWV:\n");
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_cbf_20 = IBF : %u, SU_SIFS : %u, SU_WBO : %u, MU_SIFS : %u, MU_WBO : %u\n",
				 cbf_20[HTT_IMPWICIT_TXBF_STEEW_STATS],
				 cbf_20[HTT_EXPWICIT_TXBF_SU_SIFS_STEEW_STATS],
				 cbf_20[HTT_EXPWICIT_TXBF_SU_WBO_STEEW_STATS],
				 cbf_20[HTT_EXPWICIT_TXBF_MU_SIFS_STEEW_STATS],
				 cbf_20[HTT_EXPWICIT_TXBF_MU_WBO_STEEW_STATS]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_cbf_40 = IBF : %u, SU_SIFS : %u, SU_WBO : %u, MU_SIFS : %u, MU_WBO : %u\n",
				 cbf_40[HTT_IMPWICIT_TXBF_STEEW_STATS],
				 cbf_40[HTT_EXPWICIT_TXBF_SU_SIFS_STEEW_STATS],
				 cbf_40[HTT_EXPWICIT_TXBF_SU_WBO_STEEW_STATS],
				 cbf_40[HTT_EXPWICIT_TXBF_MU_SIFS_STEEW_STATS],
				 cbf_40[HTT_EXPWICIT_TXBF_MU_WBO_STEEW_STATS]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_cbf_80 = IBF : %u, SU_SIFS : %u, SU_WBO : %u, MU_SIFS : %u, MU_WBO : %u\n",
				 cbf_80[HTT_IMPWICIT_TXBF_STEEW_STATS],
				 cbf_80[HTT_EXPWICIT_TXBF_SU_SIFS_STEEW_STATS],
				 cbf_80[HTT_EXPWICIT_TXBF_SU_WBO_STEEW_STATS],
				 cbf_80[HTT_EXPWICIT_TXBF_MU_SIFS_STEEW_STATS],
				 cbf_80[HTT_EXPWICIT_TXBF_MU_WBO_STEEW_STATS]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_cbf_160 = IBF : %u, SU_SIFS : %u, SU_WBO : %u, MU_SIFS : %u, MU_WBO : %u\n",
				 cbf_160[HTT_IMPWICIT_TXBF_STEEW_STATS],
				 cbf_160[HTT_EXPWICIT_TXBF_SU_SIFS_STEEW_STATS],
				 cbf_160[HTT_EXPWICIT_TXBF_SU_WBO_STEEW_STATS],
				 cbf_160[HTT_EXPWICIT_TXBF_MU_SIFS_STEEW_STATS],
				 cbf_160[HTT_EXPWICIT_TXBF_MU_WBO_STEEW_STATS]);

		fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_AX_MUMIMO_USEW_STATS; i++) {
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "Sounding Usew %u = 20MHz: %u, 40MHz : %u, 80MHz: %u, 160MHz: %u\n",
					 i,
					 htt_stats_buf->sounding[0],
					 htt_stats_buf->sounding[1],
					 htt_stats_buf->sounding[2],
					 htt_stats_buf->sounding[3]);
		}
	}

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_sewfgen_cmn_stats_twv(const void *tag_buf,
				   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_sewfgen_cmn_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_SEWFGEN_CMN_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "su_baw = %u\n",
			 htt_stats_buf->su_baw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wts = %u\n",
			 htt_stats_buf->wts);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cts2sewf = %u\n",
			 htt_stats_buf->cts2sewf);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qos_nuww = %u\n",
			 htt_stats_buf->qos_nuww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dewayed_baw_1 = %u\n",
			 htt_stats_buf->dewayed_baw_1);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dewayed_baw_2 = %u\n",
			 htt_stats_buf->dewayed_baw_2);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dewayed_baw_3 = %u\n",
			 htt_stats_buf->dewayed_baw_3);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dewayed_baw_4 = %u\n",
			 htt_stats_buf->dewayed_baw_4);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dewayed_baw_5 = %u\n",
			 htt_stats_buf->dewayed_baw_5);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dewayed_baw_6 = %u\n",
			 htt_stats_buf->dewayed_baw_6);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dewayed_baw_7 = %u\n\n",
			 htt_stats_buf->dewayed_baw_7);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_sewfgen_ac_stats_twv(const void *tag_buf,
				  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_sewfgen_ac_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_SEWFGEN_AC_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_su_ndpa = %u\n",
			 htt_stats_buf->ac_su_ndpa);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_su_ndp = %u\n",
			 htt_stats_buf->ac_su_ndp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_ndpa = %u\n",
			 htt_stats_buf->ac_mu_mimo_ndpa);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_ndp = %u\n",
			 htt_stats_buf->ac_mu_mimo_ndp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_bwpoww_1 = %u\n",
			 htt_stats_buf->ac_mu_mimo_bwpoww_1);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_bwpoww_2 = %u\n",
			 htt_stats_buf->ac_mu_mimo_bwpoww_2);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_bwpoww_3 = %u\n\n",
			 htt_stats_buf->ac_mu_mimo_bwpoww_3);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_sewfgen_ax_stats_twv(const void *tag_buf,
				  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_sewfgen_ax_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_SEWFGEN_AX_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_su_ndpa = %u\n",
			 htt_stats_buf->ax_su_ndpa);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_su_ndp = %u\n",
			 htt_stats_buf->ax_su_ndp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_ndpa = %u\n",
			 htt_stats_buf->ax_mu_mimo_ndpa);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_ndp = %u\n",
			 htt_stats_buf->ax_mu_mimo_ndp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwpoww_1 = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwpoww_1);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwpoww_2 = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwpoww_2);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwpoww_3 = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwpoww_3);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwpoww_4 = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwpoww_4);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwpoww_5 = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwpoww_5);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwpoww_6 = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwpoww_6);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwpoww_7 = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwpoww_7);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_basic_twiggew = %u\n",
			 htt_stats_buf->ax_basic_twiggew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_uwmumimo_twiggew = %u\n",
			 htt_stats_buf->ax_uwmumimo_twiggew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_bsw_twiggew = %u\n",
			 htt_stats_buf->ax_bsw_twiggew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_baw_twiggew = %u\n",
			 htt_stats_buf->ax_mu_baw_twiggew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_wts_twiggew = %u\n\n",
			 htt_stats_buf->ax_mu_wts_twiggew);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_sewfgen_ac_eww_stats_twv(const void *tag_buf,
				      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_sewfgen_ac_eww_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_SEWFGEN_AC_EWW_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_su_ndp_eww = %u\n",
			 htt_stats_buf->ac_su_ndp_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_su_ndpa_eww = %u\n",
			 htt_stats_buf->ac_su_ndpa_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_ndpa_eww = %u\n",
			 htt_stats_buf->ac_mu_mimo_ndpa_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_ndp_eww = %u\n",
			 htt_stats_buf->ac_mu_mimo_ndp_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_bwp1_eww = %u\n",
			 htt_stats_buf->ac_mu_mimo_bwp1_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_bwp2_eww = %u\n",
			 htt_stats_buf->ac_mu_mimo_bwp2_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_bwp3_eww = %u\n\n",
			 htt_stats_buf->ac_mu_mimo_bwp3_eww);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_sewfgen_ax_eww_stats_twv(const void *tag_buf,
				      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_sewfgen_ax_eww_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_SEWFGEN_AX_EWW_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_su_ndp_eww = %u\n",
			 htt_stats_buf->ax_su_ndp_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_su_ndpa_eww = %u\n",
			 htt_stats_buf->ax_su_ndpa_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_ndpa_eww = %u\n",
			 htt_stats_buf->ax_mu_mimo_ndpa_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_ndp_eww = %u\n",
			 htt_stats_buf->ax_mu_mimo_ndp_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwp1_eww = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwp1_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwp2_eww = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwp2_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwp3_eww = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwp3_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwp4_eww = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwp4_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwp5_eww = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwp5_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwp6_eww = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwp6_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_bwp7_eww = %u\n",
			 htt_stats_buf->ax_mu_mimo_bwp7_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_basic_twiggew_eww = %u\n",
			 htt_stats_buf->ax_basic_twiggew_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_uwmumimo_twiggew_eww = %u\n",
			 htt_stats_buf->ax_uwmumimo_twiggew_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_bsw_twiggew_eww = %u\n",
			 htt_stats_buf->ax_bsw_twiggew_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_baw_twiggew_eww = %u\n",
			 htt_stats_buf->ax_mu_baw_twiggew_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_wts_twiggew_eww = %u\n\n",
			 htt_stats_buf->ax_mu_wts_twiggew_eww);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_mu_mimo_sch_stats_twv(const void *tag_buf,
					stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_mu_mimo_sch_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u8 i;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_PDEV_MU_MIMO_SCH_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_sch_posted = %u\n",
			 htt_stats_buf->mu_mimo_sch_posted);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_sch_faiwed = %u\n",
			 htt_stats_buf->mu_mimo_sch_faiwed);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mu_mimo_ppdu_posted = %u\n\n",
			 htt_stats_buf->mu_mimo_ppdu_posted);

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_AC_MUMIMO_USEW_STATS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ac_mu_mimo_sch_posted_pew_gwoup_index %u = %u\n",
				 i, htt_stats_buf->ac_mu_mimo_sch_posted_pew_gwp_sz[i]);

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_AX_MUMIMO_USEW_STATS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_mu_mimo_sch_posted_pew_gwoup_index %u = %u\n",
				 i, htt_stats_buf->ax_mu_mimo_sch_posted_pew_gwp_sz[i]);

	wen += scnpwintf(buf + wen, buf_wen - wen, "11ac MU_MIMO SCH STATS:\n");

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_AC_MUMIMO_USEW_STATS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ac_mu_mimo_sch_nusews_%u = %u\n",
				 i, htt_stats_buf->ac_mu_mimo_sch_nusews[i]);

	wen += scnpwintf(buf + wen, buf_wen - wen, "\n11ax MU_MIMO SCH STATS:\n");

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_AX_MUMIMO_USEW_STATS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_mu_mimo_sch_nusews_%u = %u\n",
				 i, htt_stats_buf->ax_mu_mimo_sch_nusews[i]);

	wen += scnpwintf(buf + wen, buf_wen - wen, "\n11ax OFDMA SCH STATS:\n");

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_OFDMA_USEW_STATS; i++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_sch_nusews_%u = %u\n",
				 i, htt_stats_buf->ax_ofdma_sch_nusews[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_uw_ofdma_basic_sch_nusews_%u = %u\n",
				 i, htt_stats_buf->ax_uw_ofdma_basic_sch_nusews[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_uw_ofdma_bsw_sch_nusews_%u = %u\n",
				 i, htt_stats_buf->ax_uw_ofdma_bsw_sch_nusews[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_uw_ofdma_sch_baw_nusews_%u = %u\n",
				 i, htt_stats_buf->ax_uw_ofdma_baw_sch_nusews[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_uw_ofdma_bwp_sch_nusews_%u = %u\n",
				 i, htt_stats_buf->ax_uw_ofdma_bwp_sch_nusews[i]);
	}

	wen += scnpwintf(buf + wen, buf_wen - wen, "\n11ax UW MUMIO SCH STATS:\n");

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_UW_MUMIMO_USEW_STATS; i++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_uw_mumimo_basic_sch_nusews_%u = %u\n",
				 i, htt_stats_buf->ax_uw_mumimo_basic_sch_nusews[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_uw_mumimo_bwp_sch_nusews_%u = %u\n",
				 i, htt_stats_buf->ax_uw_mumimo_bwp_sch_nusews[i]);
	}

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_mu_mimo_mpdu_stats_twv(const void *tag_buf,
					 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_mpdu_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	if (htt_stats_buf->tx_sched_mode == HTT_STATS_TX_SCHED_MODE_MU_MIMO_AC) {
		if (!htt_stats_buf->usew_index)
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "HTT_TX_PDEV_MU_MIMO_AC_MPDU_STATS:\n");

		if (htt_stats_buf->usew_index <
		    HTT_TX_PDEV_STATS_NUM_AC_MUMIMO_USEW_STATS) {
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ac_mu_mimo_mpdus_queued_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_queued_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ac_mu_mimo_mpdus_twied_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_twied_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ac_mu_mimo_mpdus_faiwed_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_faiwed_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ac_mu_mimo_mpdus_wequeued_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_wequeued_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ac_mu_mimo_eww_no_ba_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->eww_no_ba_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ac_mu_mimo_mpdu_undewwun_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdu_undewwun_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ac_mu_mimo_ampdu_undewwun_usw_%u = %u\n\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->ampdu_undewwun_usw);
		}
	}

	if (htt_stats_buf->tx_sched_mode == HTT_STATS_TX_SCHED_MODE_MU_MIMO_AX) {
		if (!htt_stats_buf->usew_index)
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "HTT_TX_PDEV_MU_MIMO_AX_MPDU_STATS:\n");

		if (htt_stats_buf->usew_index <
		    HTT_TX_PDEV_STATS_NUM_AX_MUMIMO_USEW_STATS) {
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_mimo_mpdus_queued_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_queued_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_mimo_mpdus_twied_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_twied_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_mimo_mpdus_faiwed_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_faiwed_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_mimo_mpdus_wequeued_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_wequeued_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_mimo_eww_no_ba_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->eww_no_ba_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_mimo_mpdu_undewwun_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdu_undewwun_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_mimo_ampdu_undewwun_usw_%u = %u\n\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->ampdu_undewwun_usw);
		}
	}

	if (htt_stats_buf->tx_sched_mode == HTT_STATS_TX_SCHED_MODE_MU_OFDMA_AX) {
		if (!htt_stats_buf->usew_index)
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "HTT_TX_PDEV_AX_MU_OFDMA_MPDU_STATS:\n");

		if (htt_stats_buf->usew_index < HTT_TX_PDEV_STATS_NUM_OFDMA_USEW_STATS) {
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_ofdma_mpdus_queued_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_queued_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_ofdma_mpdus_twied_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_twied_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_ofdma_mpdus_faiwed_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_faiwed_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_ofdma_mpdus_wequeued_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdus_wequeued_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_ofdma_eww_no_ba_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->eww_no_ba_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_ofdma_mpdu_undewwun_usw_%u = %u\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->mpdu_undewwun_usw);
			wen += scnpwintf(buf + wen, buf_wen - wen,
					 "ax_mu_ofdma_ampdu_undewwun_usw_%u = %u\n\n",
					 htt_stats_buf->usew_index,
					 htt_stats_buf->ampdu_undewwun_usw);
		}
	}

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_sched_txq_cmd_posted_twv_v(const void *tag_buf,
				     u16 tag_wen,
				     stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_sched_txq_cmd_posted_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewements = min_t(u16, (tag_wen >> 2), HTT_TX_PDEV_SCHED_TX_MODE_MAX);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_SCHED_TXQ_CMD_POSTED_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->sched_cmd_posted,
			   "sched_cmd_posted", num_ewements, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_sched_txq_cmd_weaped_twv_v(const void *tag_buf,
				     u16 tag_wen,
				     stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_sched_txq_cmd_weaped_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewements = min_t(u16, (tag_wen >> 2), HTT_TX_PDEV_SCHED_TX_MODE_MAX);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_SCHED_TXQ_CMD_WEAPED_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->sched_cmd_weaped,
			   "sched_cmd_weaped", num_ewements, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_sched_txq_sched_owdew_su_twv_v(const void *tag_buf,
					 u16 tag_wen,
					 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_sched_txq_sched_owdew_su_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	/* each entwy is u32, i.e. 4 bytes */
	u32 sched_owdew_su_num_entwies =
		min_t(u32, (tag_wen >> 2), HTT_TX_PDEV_NUM_SCHED_OWDEW_WOG);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_SCHED_TXQ_SCHED_OWDEW_SU_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->sched_owdew_su, "sched_owdew_su",
			   sched_owdew_su_num_entwies, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_sched_txq_sched_inewigibiwity_twv_v(const void *tag_buf,
					      u16 tag_wen,
					      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_sched_txq_sched_inewigibiwity_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	/* each entwy is u32, i.e. 4 bytes */
	u32 sched_inewigibiwity_num_entwies = tag_wen >> 2;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_SCHED_TXQ_SCHED_INEWIGIBIWITY_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->sched_inewigibiwity,
			   "sched_inewigibiwity", sched_inewigibiwity_num_entwies,
			   "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_pdev_stats_sched_pew_txq_twv(const void *tag_buf,
					  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_stats_sched_pew_txq_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_PDEV_STATS_SCHED_PEW_TXQ_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_TX_PDEV_STATS_SCHED_PEW_TXQ_MAC_ID,
				   htt_stats_buf->mac_id__txq_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "txq_id = %wu\n",
			 FIEWD_GET(HTT_TX_PDEV_STATS_SCHED_PEW_TXQ_ID,
				   htt_stats_buf->mac_id__txq_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_powicy = %u\n",
			 htt_stats_buf->sched_powicy);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "wast_sched_cmd_posted_timestamp = %u\n",
			 htt_stats_buf->wast_sched_cmd_posted_timestamp);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "wast_sched_cmd_compw_timestamp = %u\n",
			 htt_stats_buf->wast_sched_cmd_compw_timestamp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_2_tac_wwm_count = %u\n",
			 htt_stats_buf->sched_2_tac_wwm_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_2_tac_wing_fuww = %u\n",
			 htt_stats_buf->sched_2_tac_wing_fuww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_cmd_post_faiwuwe = %u\n",
			 htt_stats_buf->sched_cmd_post_faiwuwe);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_active_tids = %u\n",
			 htt_stats_buf->num_active_tids);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_ps_scheduwes = %u\n",
			 htt_stats_buf->num_ps_scheduwes);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_cmds_pending = %u\n",
			 htt_stats_buf->sched_cmds_pending);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_tid_wegistew = %u\n",
			 htt_stats_buf->num_tid_wegistew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_tid_unwegistew = %u\n",
			 htt_stats_buf->num_tid_unwegistew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_qstats_quewied = %u\n",
			 htt_stats_buf->num_qstats_quewied);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qstats_update_pending = %u\n",
			 htt_stats_buf->qstats_update_pending);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_qstats_quewy_timestamp = %u\n",
			 htt_stats_buf->wast_qstats_quewy_timestamp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_tqm_cmdq_fuww = %u\n",
			 htt_stats_buf->num_tqm_cmdq_fuww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_de_sched_awgo_twiggew = %u\n",
			 htt_stats_buf->num_de_sched_awgo_twiggew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_wt_sched_awgo_twiggew = %u\n",
			 htt_stats_buf->num_wt_sched_awgo_twiggew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_tqm_sched_awgo_twiggew = %u\n",
			 htt_stats_buf->num_tqm_sched_awgo_twiggew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "notify_sched = %u\n\n",
			 htt_stats_buf->notify_sched);
	wen += scnpwintf(buf + wen, buf_wen - wen, "duw_based_sendn_tewm = %u\n\n",
			 htt_stats_buf->duw_based_sendn_tewm);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_stats_tx_sched_cmn_twv(const void *tag_buf,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_stats_tx_sched_cmn_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_STATS_TX_SCHED_CMN_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "cuwwent_timestamp = %u\n\n",
			 htt_stats_buf->cuwwent_timestamp);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_tqm_gen_mpdu_stats_twv_v(const void *tag_buf,
				      u16 tag_wen,
				      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_tqm_gen_mpdu_stats_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewements = min_t(u16, (tag_wen >> 2),
				 HTT_TX_TQM_MAX_WIST_MPDU_END_WEASON);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_TQM_GEN_MPDU_STATS_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->gen_mpdu_end_weason,
			   "gen_mpdu_end_weason", num_ewements, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_tqm_wist_mpdu_stats_twv_v(const void *tag_buf,
				       u16 tag_wen,
				       stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_tqm_wist_mpdu_stats_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_TX_TQM_MAX_WIST_MPDU_END_WEASON);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_TQM_WIST_MPDU_STATS_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wist_mpdu_end_weason,
			   "wist_mpdu_end_weason", num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_tqm_wist_mpdu_cnt_twv_v(const void *tag_buf,
				     u16 tag_wen,
				     stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_tqm_wist_mpdu_cnt_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2),
			      HTT_TX_TQM_MAX_WIST_MPDU_CNT_HISTOGWAM_BINS);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_TQM_WIST_MPDU_CNT_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wist_mpdu_cnt_hist,
			   "wist_mpdu_cnt_hist", num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_tqm_pdev_stats_twv_v(const void *tag_buf,
				  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_tqm_pdev_stats_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_TQM_PDEV_STATS_TWV_V:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "msdu_count = %u\n",
			 htt_stats_buf->msdu_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_count = %u\n",
			 htt_stats_buf->mpdu_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wemove_msdu = %u\n",
			 htt_stats_buf->wemove_msdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wemove_mpdu = %u\n",
			 htt_stats_buf->wemove_mpdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wemove_msdu_ttw = %u\n",
			 htt_stats_buf->wemove_msdu_ttw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "send_baw = %u\n",
			 htt_stats_buf->send_baw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "baw_sync = %u\n",
			 htt_stats_buf->baw_sync);
	wen += scnpwintf(buf + wen, buf_wen - wen, "notify_mpdu = %u\n",
			 htt_stats_buf->notify_mpdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sync_cmd = %u\n",
			 htt_stats_buf->sync_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wwite_cmd = %u\n",
			 htt_stats_buf->wwite_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwsch_twiggew = %u\n",
			 htt_stats_buf->hwsch_twiggew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ack_twv_pwoc = %u\n",
			 htt_stats_buf->ack_twv_pwoc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "gen_mpdu_cmd = %u\n",
			 htt_stats_buf->gen_mpdu_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "gen_wist_cmd = %u\n",
			 htt_stats_buf->gen_wist_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wemove_mpdu_cmd = %u\n",
			 htt_stats_buf->wemove_mpdu_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wemove_mpdu_twied_cmd = %u\n",
			 htt_stats_buf->wemove_mpdu_twied_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_queue_stats_cmd = %u\n",
			 htt_stats_buf->mpdu_queue_stats_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_head_info_cmd = %u\n",
			 htt_stats_buf->mpdu_head_info_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "msdu_fwow_stats_cmd = %u\n",
			 htt_stats_buf->msdu_fwow_stats_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wemove_msdu_cmd = %u\n",
			 htt_stats_buf->wemove_msdu_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wemove_msdu_ttw_cmd = %u\n",
			 htt_stats_buf->wemove_msdu_ttw_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fwush_cache_cmd = %u\n",
			 htt_stats_buf->fwush_cache_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "update_mpduq_cmd = %u\n",
			 htt_stats_buf->update_mpduq_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "enqueue = %u\n",
			 htt_stats_buf->enqueue);
	wen += scnpwintf(buf + wen, buf_wen - wen, "enqueue_notify = %u\n",
			 htt_stats_buf->enqueue_notify);
	wen += scnpwintf(buf + wen, buf_wen - wen, "notify_mpdu_at_head = %u\n",
			 htt_stats_buf->notify_mpdu_at_head);
	wen += scnpwintf(buf + wen, buf_wen - wen, "notify_mpdu_state_vawid = %u\n",
			 htt_stats_buf->notify_mpdu_state_vawid);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_udp_notify1 = %u\n",
			 htt_stats_buf->sched_udp_notify1);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_udp_notify2 = %u\n",
			 htt_stats_buf->sched_udp_notify2);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_nonudp_notify1 = %u\n",
			 htt_stats_buf->sched_nonudp_notify1);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sched_nonudp_notify2 = %u\n\n",
			 htt_stats_buf->sched_nonudp_notify2);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_tqm_cmn_stats_twv(const void *tag_buf,
						  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_tqm_cmn_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_TQM_CMN_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "max_cmdq_id = %u\n",
			 htt_stats_buf->max_cmdq_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wist_mpdu_cnt_hist_intvw = %u\n",
			 htt_stats_buf->wist_mpdu_cnt_hist_intvw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "add_msdu = %u\n",
			 htt_stats_buf->add_msdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "q_empty = %u\n",
			 htt_stats_buf->q_empty);
	wen += scnpwintf(buf + wen, buf_wen - wen, "q_not_empty = %u\n",
			 htt_stats_buf->q_not_empty);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dwop_notification = %u\n",
			 htt_stats_buf->dwop_notification);
	wen += scnpwintf(buf + wen, buf_wen - wen, "desc_thweshowd = %u\n\n",
			 htt_stats_buf->desc_thweshowd);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_tqm_ewwow_stats_twv(const void *tag_buf,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_tqm_ewwow_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_TQM_EWWOW_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "q_empty_faiwuwe = %u\n",
			 htt_stats_buf->q_empty_faiwuwe);
	wen += scnpwintf(buf + wen, buf_wen - wen, "q_not_empty_faiwuwe = %u\n",
			 htt_stats_buf->q_not_empty_faiwuwe);
	wen += scnpwintf(buf + wen, buf_wen - wen, "add_msdu_faiwuwe = %u\n\n",
			 htt_stats_buf->add_msdu_faiwuwe);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_tqm_cmdq_status_twv(const void *tag_buf,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_tqm_cmdq_status_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_TQM_CMDQ_STATUS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_TX_TQM_CMDQ_STATUS_MAC_ID,
				   htt_stats_buf->mac_id__cmdq_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "cmdq_id = %wu\n\n",
			 FIEWD_GET(HTT_TX_TQM_CMDQ_STATUS_CMDQ_ID,
				   htt_stats_buf->mac_id__cmdq_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "sync_cmd = %u\n",
			 htt_stats_buf->sync_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wwite_cmd = %u\n",
			 htt_stats_buf->wwite_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "gen_mpdu_cmd = %u\n",
			 htt_stats_buf->gen_mpdu_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_queue_stats_cmd = %u\n",
			 htt_stats_buf->mpdu_queue_stats_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_head_info_cmd = %u\n",
			 htt_stats_buf->mpdu_head_info_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "msdu_fwow_stats_cmd = %u\n",
			 htt_stats_buf->msdu_fwow_stats_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wemove_mpdu_cmd = %u\n",
			 htt_stats_buf->wemove_mpdu_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wemove_msdu_cmd = %u\n",
			 htt_stats_buf->wemove_msdu_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fwush_cache_cmd = %u\n",
			 htt_stats_buf->fwush_cache_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "update_mpduq_cmd = %u\n",
			 htt_stats_buf->update_mpduq_cmd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "update_msduq_cmd = %u\n\n",
			 htt_stats_buf->update_msduq_cmd);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_de_eapow_packets_stats_twv(const void *tag_buf,
					stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_de_eapow_packets_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			   "HTT_TX_DE_EAPOW_PACKETS_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "m1_packets = %u\n",
			 htt_stats_buf->m1_packets);
	wen += scnpwintf(buf + wen, buf_wen - wen, "m2_packets = %u\n",
			 htt_stats_buf->m2_packets);
	wen += scnpwintf(buf + wen, buf_wen - wen, "m3_packets = %u\n",
			 htt_stats_buf->m3_packets);
	wen += scnpwintf(buf + wen, buf_wen - wen, "m4_packets = %u\n",
			 htt_stats_buf->m4_packets);
	wen += scnpwintf(buf + wen, buf_wen - wen, "g1_packets = %u\n",
			 htt_stats_buf->g1_packets);
	wen += scnpwintf(buf + wen, buf_wen - wen, "g2_packets = %u\n\n",
			 htt_stats_buf->g2_packets);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_de_cwassify_faiwed_stats_twv(const void *tag_buf,
					  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_de_cwassify_faiwed_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			   "HTT_TX_DE_CWASSIFY_FAIWED_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "ap_bss_peew_not_found = %u\n",
			 htt_stats_buf->ap_bss_peew_not_found);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ap_bcast_mcast_no_peew = %u\n",
			 htt_stats_buf->ap_bcast_mcast_no_peew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sta_dewete_in_pwogwess = %u\n",
			 htt_stats_buf->sta_dewete_in_pwogwess);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ibss_no_bss_peew = %u\n",
			 htt_stats_buf->ibss_no_bss_peew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "invawid_vdev_type = %u\n",
			 htt_stats_buf->invawid_vdev_type);
	wen += scnpwintf(buf + wen, buf_wen - wen, "invawid_ast_peew_entwy = %u\n",
			 htt_stats_buf->invawid_ast_peew_entwy);
	wen += scnpwintf(buf + wen, buf_wen - wen, "peew_entwy_invawid = %u\n",
			 htt_stats_buf->peew_entwy_invawid);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ethewtype_not_ip = %u\n",
			 htt_stats_buf->ethewtype_not_ip);
	wen += scnpwintf(buf + wen, buf_wen - wen, "eapow_wookup_faiwed = %u\n",
			 htt_stats_buf->eapow_wookup_faiwed);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qpeew_not_awwow_data = %u\n",
			 htt_stats_buf->qpeew_not_awwow_data);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_tid_ovewwide = %u\n",
			 htt_stats_buf->fse_tid_ovewwide);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ipv6_jumbogwam_zewo_wength = %u\n",
			 htt_stats_buf->ipv6_jumbogwam_zewo_wength);
	wen += scnpwintf(buf + wen, buf_wen - wen, "qos_to_non_qos_in_pwog = %u\n\n",
			 htt_stats_buf->qos_to_non_qos_in_pwog);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_de_cwassify_stats_twv(const void *tag_buf,
				   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_de_cwassify_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_DE_CWASSIFY_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "awp_packets = %u\n",
			 htt_stats_buf->awp_packets);
	wen += scnpwintf(buf + wen, buf_wen - wen, "igmp_packets = %u\n",
			 htt_stats_buf->igmp_packets);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dhcp_packets = %u\n",
			 htt_stats_buf->dhcp_packets);
	wen += scnpwintf(buf + wen, buf_wen - wen, "host_inspected = %u\n",
			 htt_stats_buf->host_inspected);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_incwuded = %u\n",
			 htt_stats_buf->htt_incwuded);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_mcs = %u\n",
			 htt_stats_buf->htt_vawid_mcs);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_nss = %u\n",
			 htt_stats_buf->htt_vawid_nss);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_pweambwe_type = %u\n",
			 htt_stats_buf->htt_vawid_pweambwe_type);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_chainmask = %u\n",
			 htt_stats_buf->htt_vawid_chainmask);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_guawd_intewvaw = %u\n",
			 htt_stats_buf->htt_vawid_guawd_intewvaw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_wetwies = %u\n",
			 htt_stats_buf->htt_vawid_wetwies);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_bw_info = %u\n",
			 htt_stats_buf->htt_vawid_bw_info);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_powew = %u\n",
			 htt_stats_buf->htt_vawid_powew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_key_fwags = 0x%x\n",
			 htt_stats_buf->htt_vawid_key_fwags);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_vawid_no_encwyption = %u\n",
			 htt_stats_buf->htt_vawid_no_encwyption);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_entwy_count = %u\n",
			 htt_stats_buf->fse_entwy_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_pwiowity_be = %u\n",
			 htt_stats_buf->fse_pwiowity_be);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_pwiowity_high = %u\n",
			 htt_stats_buf->fse_pwiowity_high);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_pwiowity_wow = %u\n",
			 htt_stats_buf->fse_pwiowity_wow);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_twaffic_ptwn_be = %u\n",
			 htt_stats_buf->fse_twaffic_ptwn_be);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_twaffic_ptwn_ovew_sub = %u\n",
			 htt_stats_buf->fse_twaffic_ptwn_ovew_sub);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_twaffic_ptwn_buwsty = %u\n",
			 htt_stats_buf->fse_twaffic_ptwn_buwsty);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_twaffic_ptwn_intewactive = %u\n",
			 htt_stats_buf->fse_twaffic_ptwn_intewactive);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_twaffic_ptwn_pewiodic = %u\n",
			 htt_stats_buf->fse_twaffic_ptwn_pewiodic);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_hwqueue_awwoc = %u\n",
			 htt_stats_buf->fse_hwqueue_awwoc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_hwqueue_cweated = %u\n",
			 htt_stats_buf->fse_hwqueue_cweated);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_hwqueue_send_to_host = %u\n",
			 htt_stats_buf->fse_hwqueue_send_to_host);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mcast_entwy = %u\n",
			 htt_stats_buf->mcast_entwy);
	wen += scnpwintf(buf + wen, buf_wen - wen, "bcast_entwy = %u\n",
			 htt_stats_buf->bcast_entwy);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_update_peew_cache = %u\n",
			 htt_stats_buf->htt_update_peew_cache);
	wen += scnpwintf(buf + wen, buf_wen - wen, "htt_weawning_fwame = %u\n",
			 htt_stats_buf->htt_weawning_fwame);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fse_invawid_peew = %u\n",
			 htt_stats_buf->fse_invawid_peew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mec_notify = %u\n\n",
			 htt_stats_buf->mec_notify);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_de_cwassify_status_stats_twv(const void *tag_buf,
					  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_de_cwassify_status_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			   "HTT_TX_DE_CWASSIFY_STATUS_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "eok = %u\n",
			 htt_stats_buf->eok);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cwassify_done = %u\n",
			 htt_stats_buf->cwassify_done);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wookup_faiwed = %u\n",
			 htt_stats_buf->wookup_faiwed);
	wen += scnpwintf(buf + wen, buf_wen - wen, "send_host_dhcp = %u\n",
			 htt_stats_buf->send_host_dhcp);
	wen += scnpwintf(buf + wen, buf_wen - wen, "send_host_mcast = %u\n",
			 htt_stats_buf->send_host_mcast);
	wen += scnpwintf(buf + wen, buf_wen - wen, "send_host_unknown_dest = %u\n",
			 htt_stats_buf->send_host_unknown_dest);
	wen += scnpwintf(buf + wen, buf_wen - wen, "send_host = %u\n",
			 htt_stats_buf->send_host);
	wen += scnpwintf(buf + wen, buf_wen - wen, "status_invawid = %u\n\n",
			 htt_stats_buf->status_invawid);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_de_enqueue_packets_stats_twv(const void *tag_buf,
					  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_de_enqueue_packets_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_DE_ENQUEUE_PACKETS_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "enqueued_pkts = %u\n",
			 htt_stats_buf->enqueued_pkts);
	wen += scnpwintf(buf + wen, buf_wen - wen, "to_tqm = %u\n",
			 htt_stats_buf->to_tqm);
	wen += scnpwintf(buf + wen, buf_wen - wen, "to_tqm_bypass = %u\n\n",
			 htt_stats_buf->to_tqm_bypass);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_de_enqueue_discawd_stats_twv(const void *tag_buf,
					  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_de_enqueue_discawd_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_DE_ENQUEUE_DISCAWD_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "discawded_pkts = %u\n",
			 htt_stats_buf->discawded_pkts);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wocaw_fwames = %u\n",
			 htt_stats_buf->wocaw_fwames);
	wen += scnpwintf(buf + wen, buf_wen - wen, "is_ext_msdu = %u\n\n",
			 htt_stats_buf->is_ext_msdu);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_de_compw_stats_twv(const void *tag_buf,
						   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_de_compw_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_DE_COMPW_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "tcw_dummy_fwame = %u\n",
			 htt_stats_buf->tcw_dummy_fwame);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tqm_dummy_fwame = %u\n",
			 htt_stats_buf->tqm_dummy_fwame);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tqm_notify_fwame = %u\n",
			 htt_stats_buf->tqm_notify_fwame);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw2wbm_enq = %u\n",
			 htt_stats_buf->fw2wbm_enq);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tqm_bypass_fwame = %u\n\n",
			 htt_stats_buf->tqm_bypass_fwame);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_de_fw2wbm_wing_fuww_hist_twv(const void *tag_buf,
					  u16 tag_wen,
					  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_de_fw2wbm_wing_fuww_hist_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16  num_ewements = tag_wen >> 2;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TX_DE_FW2WBM_WING_FUWW_HIST_TWV");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->fw2wbm_wing_fuww_hist,
			   "fw2wbm_wing_fuww_hist", num_ewements, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_tx_de_cmn_stats_twv(const void *tag_buf, stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_de_cmn_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_DE_CMN_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "tcw2fw_entwy_count = %u\n",
			 htt_stats_buf->tcw2fw_entwy_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "not_to_fw = %u\n",
			 htt_stats_buf->not_to_fw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "invawid_pdev_vdev_peew = %u\n",
			 htt_stats_buf->invawid_pdev_vdev_peew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tcw_wes_invawid_addwx = %u\n",
			 htt_stats_buf->tcw_wes_invawid_addwx);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wbm2fw_entwy_count = %u\n",
			 htt_stats_buf->wbm2fw_entwy_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "invawid_pdev = %u\n\n",
			 htt_stats_buf->invawid_pdev);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_wing_if_stats_twv(const void *tag_buf,
					       stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wing_if_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WING_IF_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "base_addw = %u\n",
			 htt_stats_buf->base_addw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ewem_size = %u\n",
			 htt_stats_buf->ewem_size);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_ewems = %wu\n",
			 FIEWD_GET(HTT_WING_IF_STATS_NUM_EWEMS,
				   htt_stats_buf->num_ewems__pwefetch_taiw_idx));
	wen += scnpwintf(buf + wen, buf_wen - wen, "pwefetch_taiw_idx = %wu\n",
			 FIEWD_GET(HTT_WING_IF_STATS_PWEFETCH_TAIW_INDEX,
				   htt_stats_buf->num_ewems__pwefetch_taiw_idx));
	wen += scnpwintf(buf + wen, buf_wen - wen, "head_idx = %wu\n",
			 FIEWD_GET(HTT_WING_IF_STATS_HEAD_IDX,
				   htt_stats_buf->head_idx__taiw_idx));
	wen += scnpwintf(buf + wen, buf_wen - wen, "taiw_idx = %wu\n",
			 FIEWD_GET(HTT_WING_IF_STATS_TAIW_IDX,
				   htt_stats_buf->head_idx__taiw_idx));
	wen += scnpwintf(buf + wen, buf_wen - wen, "shadow_head_idx = %wu\n",
			 FIEWD_GET(HTT_WING_IF_STATS_SHADOW_HEAD_IDX,
				   htt_stats_buf->shadow_head_idx__shadow_taiw_idx));
	wen += scnpwintf(buf + wen, buf_wen - wen, "shadow_taiw_idx = %wu\n",
			 FIEWD_GET(HTT_WING_IF_STATS_SHADOW_TAIW_IDX,
				   htt_stats_buf->shadow_head_idx__shadow_taiw_idx));
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_taiw_incw = %u\n",
			 htt_stats_buf->num_taiw_incw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wwm_thwesh = %wu\n",
			 FIEWD_GET(HTT_WING_IF_STATS_WWM_THWESH,
				   htt_stats_buf->wwm_thwesh__hwm_thwesh));
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwm_thwesh = %wu\n",
			 FIEWD_GET(HTT_WING_IF_STATS_HWM_THWESH,
				   htt_stats_buf->wwm_thwesh__hwm_thwesh));
	wen += scnpwintf(buf + wen, buf_wen - wen, "ovewwun_hit_count = %u\n",
			 htt_stats_buf->ovewwun_hit_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "undewwun_hit_count = %u\n",
			 htt_stats_buf->undewwun_hit_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "pwod_bwockwait_count = %u\n",
			 htt_stats_buf->pwod_bwockwait_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cons_bwockwait_count = %u\n",
			 htt_stats_buf->cons_bwockwait_count);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wow_wm_hit_count,
			   "wow_wm_hit_count", HTT_STATS_WOW_WM_BINS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->high_wm_hit_count,
			   "high_wm_hit_count", HTT_STATS_HIGH_WM_BINS, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_wing_if_cmn_twv(const void *tag_buf,
					     stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wing_if_cmn_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WING_IF_CMN_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_wecowds = %u\n\n",
			 htt_stats_buf->num_wecowds);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_sfm_cwient_usew_twv_v(const void *tag_buf,
						   u16 tag_wen,
						   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_sfm_cwient_usew_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = tag_wen >> 2;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_SFM_CWIENT_USEW_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->dwowds_used_by_usew_n,
			   "dwowds_used_by_usew_n", num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_sfm_cwient_twv(const void *tag_buf,
					    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_sfm_cwient_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_SFM_CWIENT_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "cwient_id = %u\n",
			 htt_stats_buf->cwient_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "buf_min = %u\n",
			 htt_stats_buf->buf_min);
	wen += scnpwintf(buf + wen, buf_wen - wen, "buf_max = %u\n",
			 htt_stats_buf->buf_max);
	wen += scnpwintf(buf + wen, buf_wen - wen, "buf_busy = %u\n",
			 htt_stats_buf->buf_busy);
	wen += scnpwintf(buf + wen, buf_wen - wen, "buf_awwoc = %u\n",
			 htt_stats_buf->buf_awwoc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "buf_avaiw = %u\n",
			 htt_stats_buf->buf_avaiw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_usews = %u\n\n",
			 htt_stats_buf->num_usews);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_sfm_cmn_twv(const void *tag_buf,
					 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_sfm_cmn_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_SFM_CMN_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "buf_totaw = %u\n",
			 htt_stats_buf->buf_totaw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mem_empty = %u\n",
			 htt_stats_buf->mem_empty);
	wen += scnpwintf(buf + wen, buf_wen - wen, "deawwocate_bufs = %u\n",
			 htt_stats_buf->deawwocate_bufs);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_wecowds = %u\n\n",
			 htt_stats_buf->num_wecowds);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_swing_stats_twv(const void *tag_buf,
					     stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_swing_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_SWING_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_MAC_ID,
				   htt_stats_buf->mac_id__wing_id__awena__ep));
	wen += scnpwintf(buf + wen, buf_wen - wen, "wing_id = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_WING_ID,
				   htt_stats_buf->mac_id__wing_id__awena__ep));
	wen += scnpwintf(buf + wen, buf_wen - wen, "awena = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_AWENA,
				   htt_stats_buf->mac_id__wing_id__awena__ep));
	wen += scnpwintf(buf + wen, buf_wen - wen, "ep = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_EP,
				   htt_stats_buf->mac_id__wing_id__awena__ep));
	wen += scnpwintf(buf + wen, buf_wen - wen, "base_addw_wsb = 0x%x\n",
			 htt_stats_buf->base_addw_wsb);
	wen += scnpwintf(buf + wen, buf_wen - wen, "base_addw_msb = 0x%x\n",
			 htt_stats_buf->base_addw_msb);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wing_size = %u\n",
			 htt_stats_buf->wing_size);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ewem_size = %u\n",
			 htt_stats_buf->ewem_size);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_avaiw_wowds = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_NUM_AVAIW_WOWDS,
				   htt_stats_buf->num_avaiw_wowds__num_vawid_wowds));
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_vawid_wowds = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_NUM_VAWID_WOWDS,
				   htt_stats_buf->num_avaiw_wowds__num_vawid_wowds));
	wen += scnpwintf(buf + wen, buf_wen - wen, "head_ptw = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_HEAD_PTW,
				   htt_stats_buf->head_ptw__taiw_ptw));
	wen += scnpwintf(buf + wen, buf_wen - wen, "taiw_ptw = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_TAIW_PTW,
				   htt_stats_buf->head_ptw__taiw_ptw));
	wen += scnpwintf(buf + wen, buf_wen - wen, "consumew_empty = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_CONSUMEW_EMPTY,
				   htt_stats_buf->consumew_empty__pwoducew_fuww));
	wen += scnpwintf(buf + wen, buf_wen - wen, "pwoducew_fuww = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_PWODUCEW_FUWW,
				   htt_stats_buf->consumew_empty__pwoducew_fuww));
	wen += scnpwintf(buf + wen, buf_wen - wen, "pwefetch_count = %wu\n",
			 FIEWD_GET(HTT_SWING_STATS_PWEFETCH_COUNT,
				   htt_stats_buf->pwefetch_count__intewnaw_taiw_ptw));
	wen += scnpwintf(buf + wen, buf_wen - wen, "intewnaw_taiw_ptw = %wu\n\n",
			 FIEWD_GET(HTT_SWING_STATS_INTEWNAW_TAIW_PTW,
				   htt_stats_buf->pwefetch_count__intewnaw_taiw_ptw));

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_swing_cmn_twv(const void *tag_buf,
					   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_swing_cmn_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_SWING_CMN_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_wecowds = %u\n\n",
			 htt_stats_buf->num_wecowds);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_tx_pdev_wate_stats_twv(const void *tag_buf,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_tx_pdev_wate_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u8 j;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_TX_PDEV_WATE_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_wdpc = %u\n",
			 htt_stats_buf->tx_wdpc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ac_mu_mimo_tx_wdpc = %u\n",
			 htt_stats_buf->ac_mu_mimo_tx_wdpc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ax_mu_mimo_tx_wdpc = %u\n",
			 htt_stats_buf->ax_mu_mimo_tx_wdpc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ofdma_tx_wdpc = %u\n",
			 htt_stats_buf->ofdma_tx_wdpc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wts_cnt = %u\n",
			 htt_stats_buf->wts_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wts_success = %u\n",
			 htt_stats_buf->wts_success);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ack_wssi = %u\n",
			 htt_stats_buf->ack_wssi);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "Wegacy CCK Wates: 1 Mbps: %u, 2 Mbps: %u, 5.5 Mbps: %u, 11 Mbps: %u\n",
			 htt_stats_buf->tx_wegacy_cck_wate[0],
			 htt_stats_buf->tx_wegacy_cck_wate[1],
			 htt_stats_buf->tx_wegacy_cck_wate[2],
			 htt_stats_buf->tx_wegacy_cck_wate[3]);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "Wegacy OFDM Wates: 6 Mbps: %u, 9 Mbps: %u, 12 Mbps: %u, 18 Mbps: %u\n"
			 "                   24 Mbps: %u, 36 Mbps: %u, 48 Mbps: %u, 54 Mbps: %u\n",
			 htt_stats_buf->tx_wegacy_ofdm_wate[0],
			 htt_stats_buf->tx_wegacy_ofdm_wate[1],
			 htt_stats_buf->tx_wegacy_ofdm_wate[2],
			 htt_stats_buf->tx_wegacy_ofdm_wate[3],
			 htt_stats_buf->tx_wegacy_ofdm_wate[4],
			 htt_stats_buf->tx_wegacy_ofdm_wate[5],
			 htt_stats_buf->tx_wegacy_ofdm_wate[6],
			 htt_stats_buf->tx_wegacy_ofdm_wate[7]);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_mcs, "tx_mcs",
			   HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ac_mu_mimo_tx_mcs,
			   "ac_mu_mimo_tx_mcs", HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ax_mu_mimo_tx_mcs,
			   "ax_mu_mimo_tx_mcs", HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ofdma_tx_mcs, "ofdma_tx_mcs",
			   HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_nss, "tx_nss",
			   HTT_TX_PDEV_STATS_NUM_SPATIAW_STWEAMS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ac_mu_mimo_tx_nss,
			   "ac_mu_mimo_tx_nss",
			   HTT_TX_PDEV_STATS_NUM_SPATIAW_STWEAMS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ax_mu_mimo_tx_nss,
			   "ax_mu_mimo_tx_nss",
			   HTT_TX_PDEV_STATS_NUM_SPATIAW_STWEAMS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ofdma_tx_nss, "ofdma_tx_nss",
			   HTT_TX_PDEV_STATS_NUM_SPATIAW_STWEAMS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_bw, "tx_bw",
			   HTT_TX_PDEV_STATS_NUM_BW_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ac_mu_mimo_tx_bw,
			   "ac_mu_mimo_tx_bw", HTT_TX_PDEV_STATS_NUM_BW_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ax_mu_mimo_tx_bw,
			   "ax_mu_mimo_tx_bw",
			   HTT_TX_PDEV_STATS_NUM_BW_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ofdma_tx_bw, "ofdma_tx_bw",
			   HTT_TX_PDEV_STATS_NUM_BW_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_stbc, "tx_stbc",
			   HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_pweam, "tx_pweam",
			   HTT_TX_PDEV_STATS_NUM_PWEAMBWE_TYPES, "\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "HE WTF: 1x: %u, 2x: %u, 4x: %u\n",
			 htt_stats_buf->tx_he_wtf[1],
			 htt_stats_buf->tx_he_wtf[2],
			 htt_stats_buf->tx_he_wtf[3]);

	/* SU GI Stats */
	fow (j = 0; j < HTT_TX_PDEV_STATS_NUM_GI_COUNTEWS; j++) {
		wen += scnpwintf(buf + wen, (buf_wen - wen),
				 "tx_gi[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_gi[j], NUWW,
				   HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	}

	/* AC MU-MIMO GI Stats */
	fow (j = 0; j < HTT_TX_PDEV_STATS_NUM_GI_COUNTEWS; j++) {
		wen += scnpwintf(buf + wen, (buf_wen - wen),
				 "ac_mu_mimo_tx_gi[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ac_mu_mimo_tx_gi[j],
				   NUWW, HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	}

	/* AX MU-MIMO GI Stats */
	fow (j = 0; j < HTT_TX_PDEV_STATS_NUM_GI_COUNTEWS; j++) {
		wen += scnpwintf(buf + wen, (buf_wen - wen),
				 "ax_mu_mimo_tx_gi[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ax_mu_mimo_tx_gi[j],
				   NUWW, HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	}

	/* DW OFDMA GI Stats */
	fow (j = 0; j < HTT_TX_PDEV_STATS_NUM_GI_COUNTEWS; j++) {
		wen += scnpwintf(buf + wen, (buf_wen - wen),
				 "ofdma_tx_gi[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->ofdma_tx_gi[j], NUWW,
				   HTT_TX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	}

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->tx_dcm, "tx_dcm",
			   HTT_TX_PDEV_STATS_NUM_DCM_COUNTEWS, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_wx_pdev_wate_stats_twv(const void *tag_buf,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_pdev_wate_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u8 i, j;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WX_PDEV_WATE_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "nsts = %u\n",
			 htt_stats_buf->nsts);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_wdpc = %u\n",
			 htt_stats_buf->wx_wdpc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wts_cnt = %u\n",
			 htt_stats_buf->wts_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wssi_mgmt = %u\n",
			 htt_stats_buf->wssi_mgmt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wssi_data = %u\n",
			 htt_stats_buf->wssi_data);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wssi_comb = %u\n",
			 htt_stats_buf->wssi_comb);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wssi_in_dbm = %d\n",
			 htt_stats_buf->wssi_in_dbm);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_mcs, "wx_mcs",
			   HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_nss, "wx_nss",
			   HTT_WX_PDEV_STATS_NUM_SPATIAW_STWEAMS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_dcm, "wx_dcm",
			   HTT_WX_PDEV_STATS_NUM_DCM_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_stbc, "wx_stbc",
			   HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_bw, "wx_bw",
			   HTT_WX_PDEV_STATS_NUM_BW_COUNTEWS, "\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_evm_nss_count = %u\n",
			 htt_stats_buf->nss_count);

	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_evm_piwot_count = %u\n",
			 htt_stats_buf->piwot_count);

	fow (j = 0; j < HTT_WX_PDEV_STATS_NUM_SPATIAW_STWEAMS; j++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "piwot_evm_db[%u] = ", j);
		fow (i = 0; i < HTT_WX_PDEV_STATS_WXEVM_MAX_PIWOTS_PEW_NSS; i++)
			wen += scnpwintf(buf + wen,
					 buf_wen - wen,
					 " %u:%d,",
					 i,
					 htt_stats_buf->wx_piwot_evm_db[j][i]);
		wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	}

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "piwot_evm_db_mean = ");
	fow (i = 0; i < HTT_WX_PDEV_STATS_NUM_SPATIAW_STWEAMS; i++)
		wen += scnpwintf(buf + wen,
				 buf_wen - wen,
				 " %u:%d,", i,
				 htt_stats_buf->wx_piwot_evm_db_mean[i]);
	wen += scnpwintf(buf + wen, buf_wen - wen, "\n");

	fow (j = 0; j < HTT_WX_PDEV_STATS_NUM_SPATIAW_STWEAMS; j++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "wssi_chain[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wssi_chain[j], NUWW,
				   HTT_WX_PDEV_STATS_NUM_BW_COUNTEWS, "\n");
	}

	fow (j = 0; j < HTT_WX_PDEV_STATS_NUM_GI_COUNTEWS; j++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "wx_gi[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_gi[j], NUWW,
				   HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	}

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_pweam, "wx_pweam",
			   HTT_WX_PDEV_STATS_NUM_PWEAMBWE_TYPES, "\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_11ax_su_ext = %u\n",
			 htt_stats_buf->wx_11ax_su_ext);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_11ac_mumimo = %u\n",
			 htt_stats_buf->wx_11ac_mumimo);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_11ax_mumimo = %u\n",
			 htt_stats_buf->wx_11ax_mumimo);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_11ax_ofdma = %u\n",
			 htt_stats_buf->wx_11ax_ofdma);
	wen += scnpwintf(buf + wen, buf_wen - wen, "txbf = %u\n",
			 htt_stats_buf->txbf);

	wen += scnpwintf(buf + wen, buf_wen - wen, "\nwx_su_ndpa = %u",
			 htt_stats_buf->wx_su_ndpa);
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_11ax_su_txbf_mcs,
			   "wx_11ax_su_txbf_mcs", HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS,
			   "\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "\nwx_mu_ndpa = %u",
			 htt_stats_buf->wx_mu_ndpa);
	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_11ax_mu_txbf_mcs,
			   "wx_11ax_mu_txbf_mcs", HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS,
			   "\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "\nwx_bw_poww = %u",
			 htt_stats_buf->wx_bw_poww);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_wegacy_cck_wate,
			   "wx_wegacy_cck_wate",
			   HTT_WX_PDEV_STATS_NUM_WEGACY_CCK_STATS, "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_wegacy_ofdm_wate,
			   "wx_wegacy_ofdm_wate",
			   HTT_WX_PDEV_STATS_NUM_WEGACY_OFDM_STATS, "\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_active_duw_us_wow = %u\n",
			 htt_stats_buf->wx_active_duw_us_wow);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_active_duw_us_high = %u\n",
			 htt_stats_buf->wx_active_duw_us_high);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_11ax_uw_ofdma = %u\n",
			 htt_stats_buf->wx_11ax_uw_ofdma);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->uw_ofdma_wx_mcs,
			   "uw_ofdma_wx_mcs",
			   HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");

	fow (j = 0; j < HTT_WX_PDEV_STATS_NUM_GI_COUNTEWS; j++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "uw_ofdma_wx_gi[%u] = ", j);
		PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->uw_ofdma_wx_gi[j], NUWW,
				   HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS, "\n");
	}

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->uw_ofdma_wx_nss,
			   "uw_ofdma_wx_nss",
			   HTT_WX_PDEV_STATS_NUM_SPATIAW_STWEAMS, "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->uw_ofdma_wx_bw, "uw_ofdma_wx_bw",
			   HTT_WX_PDEV_STATS_NUM_BW_COUNTEWS, "\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "uw_ofdma_wx_stbc = %u\n",
			htt_stats_buf->uw_ofdma_wx_stbc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "uw_ofdma_wx_wdpc = %u\n",
			htt_stats_buf->uw_ofdma_wx_wdpc);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwofdma_non_data_ppdu,
			   "wx_uwofdma_non_data_ppdu",
			   HTT_WX_PDEV_MAX_OFDMA_NUM_USEW, "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwofdma_data_ppdu,
			   "wx_uwofdma_data_ppdu", HTT_WX_PDEV_MAX_OFDMA_NUM_USEW, "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwofdma_mpdu_ok,
			   "wx_uwofdma_mpdu_ok", HTT_WX_PDEV_MAX_OFDMA_NUM_USEW, "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwofdma_mpdu_faiw,
			   "wx_uwofdma_mpdu_faiw", HTT_WX_PDEV_MAX_OFDMA_NUM_USEW, "\n");

	fow (j = 0; j < HTT_WX_PDEV_STATS_NUM_SPATIAW_STWEAMS; j++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "wx_uw_fd_wssi: nss[%u] = ", j);
		fow (i = 0; i < HTT_WX_PDEV_MAX_OFDMA_NUM_USEW; i++)
			wen += scnpwintf(buf + wen,
					 buf_wen - wen,
					 " %u:%d,",
					 i, htt_stats_buf->wx_uw_fd_wssi[j][i]);
		wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	}

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwofdma_non_data_nusews,
			   "wx_uwofdma_non_data_nusews", HTT_WX_PDEV_MAX_OFDMA_NUM_USEW,
			   "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwofdma_data_nusews,
			   "wx_uwofdma_data_nusews", HTT_WX_PDEV_MAX_OFDMA_NUM_USEW,
			   "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_11ax_dw_ofdma_mcs,
			   "wx_11ax_dw_ofdma_mcs", HTT_WX_PDEV_STATS_NUM_MCS_COUNTEWS,
			   "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_11ax_dw_ofdma_wu,
			   "wx_11ax_dw_ofdma_wu", HTT_WX_PDEV_STATS_NUM_WU_SIZE_COUNTEWS,
			   "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwmumimo_non_data_ppdu,
			   "wx_uwmumimo_non_data_ppdu", HTT_WX_PDEV_MAX_UWMUMIMO_NUM_USEW,
			   "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwmumimo_data_ppdu,
			   "wx_uwmumimo_data_ppdu", HTT_WX_PDEV_MAX_UWMUMIMO_NUM_USEW,
			   "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwmumimo_mpdu_ok,
			   "wx_uwmumimo_mpdu_ok", HTT_WX_PDEV_MAX_UWMUMIMO_NUM_USEW,
			   "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wx_uwmumimo_mpdu_faiw,
			   "wx_uwmumimo_mpdu_faiw", HTT_WX_PDEV_MAX_UWMUMIMO_NUM_USEW,
			   "\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "pew_chain_wssi_pkt_type = %#x\n",
			 htt_stats_buf->pew_chain_wssi_pkt_type);

	fow (j = 0; j < HTT_WX_PDEV_STATS_NUM_SPATIAW_STWEAMS; j++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "wx_pew_chain_wssi_in_dbm[%u] = ", j);
		fow (i = 0; i < HTT_WX_PDEV_STATS_NUM_BW_COUNTEWS; i++)
			wen += scnpwintf(buf + wen,
					 buf_wen - wen,
					 " %u:%d,",
					 i,
					 htt_stats_buf->wx_pew_chain_wssi_in_dbm[j][i]);
		wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	}
	wen += scnpwintf(buf + wen, buf_wen - wen, "\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_wx_soc_fw_stats_twv(const void *tag_buf,
						 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_soc_fw_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WX_SOC_FW_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_weo_wing_data_msdu = %u\n",
			 htt_stats_buf->fw_weo_wing_data_msdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_to_host_data_msdu_bcmc = %u\n",
			 htt_stats_buf->fw_to_host_data_msdu_bcmc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_to_host_data_msdu_uc = %u\n",
			 htt_stats_buf->fw_to_host_data_msdu_uc);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "ofwd_wemote_data_buf_wecycwe_cnt = %u\n",
			 htt_stats_buf->ofwd_wemote_data_buf_wecycwe_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "ofwd_wemote_fwee_buf_indication_cnt = %u\n",
			 htt_stats_buf->ofwd_wemote_fwee_buf_indication_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "ofwd_buf_to_host_data_msdu_uc = %u\n",
			 htt_stats_buf->ofwd_buf_to_host_data_msdu_uc);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "weo_fw_wing_to_host_data_msdu_uc = %u\n",
			 htt_stats_buf->weo_fw_wing_to_host_data_msdu_uc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wbm_sw_wing_weap = %u\n",
			 htt_stats_buf->wbm_sw_wing_weap);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wbm_fowwawd_to_host_cnt = %u\n",
			 htt_stats_buf->wbm_fowwawd_to_host_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wbm_tawget_wecycwe_cnt = %u\n",
			 htt_stats_buf->wbm_tawget_wecycwe_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "tawget_wefiww_wing_wecycwe_cnt = %u\n",
			 htt_stats_buf->tawget_wefiww_wing_wecycwe_cnt);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_wx_soc_fw_wefiww_wing_empty_twv_v(const void *tag_buf,
					    u16 tag_wen,
					    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_soc_fw_wefiww_wing_empty_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_WX_STATS_WEFIWW_MAX_WING);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_WX_SOC_FW_WEFIWW_WING_EMPTY_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wefiww_wing_empty_cnt,
			   "wefiww_wing_empty_cnt", num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_wx_soc_fw_wefiww_wing_num_wxdma_eww_twv_v(const void *tag_buf,
						    u16 tag_wen,
						    stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_soc_fw_wefiww_wing_num_wxdma_eww_twv_v *htt_stats_buf =
		tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_WX_WXDMA_MAX_EWW_CODE);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_WX_SOC_FW_WEFIWW_WING_NUM_WXDMA_EWW_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wxdma_eww, "wxdma_eww",
			   num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_wx_soc_fw_wefiww_wing_num_weo_eww_twv_v(const void *tag_buf,
						  u16 tag_wen,
						  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_soc_fw_wefiww_wing_num_weo_eww_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_WX_WEO_MAX_EWW_CODE);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_WX_SOC_FW_WEFIWW_WING_NUM_WEO_EWW_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->weo_eww, "weo_eww",
			   num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_wx_weo_debug_stats_twv_v(const void *tag_buf,
				   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_weo_wesouwce_stats_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WX_WEO_WESOUWCE_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "sampwe_id = %u\n",
			 htt_stats_buf->sampwe_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "totaw_max = %u\n",
			 htt_stats_buf->totaw_max);
	wen += scnpwintf(buf + wen, buf_wen - wen, "totaw_avg = %u\n",
			 htt_stats_buf->totaw_avg);
	wen += scnpwintf(buf + wen, buf_wen - wen, "totaw_sampwe = %u\n",
			 htt_stats_buf->totaw_sampwe);
	wen += scnpwintf(buf + wen, buf_wen - wen, "non_zewos_avg = %u\n",
			 htt_stats_buf->non_zewos_avg);
	wen += scnpwintf(buf + wen, buf_wen - wen, "non_zewos_sampwe = %u\n",
			 htt_stats_buf->non_zewos_sampwe);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_non_zewos_max = %u\n",
			 htt_stats_buf->wast_non_zewos_max);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_non_zewos_min %u\n",
			 htt_stats_buf->wast_non_zewos_min);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_non_zewos_avg %u\n",
			 htt_stats_buf->wast_non_zewos_avg);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_non_zewos_sampwe %u\n\n",
			 htt_stats_buf->wast_non_zewos_sampwe);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_wx_soc_fw_wefiww_wing_num_wefiww_twv_v(const void *tag_buf,
						 u16 tag_wen,
						 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_soc_fw_wefiww_wing_num_wefiww_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_WX_STATS_WEFIWW_MAX_WING);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_WX_SOC_FW_WEFIWW_WING_NUM_WEFIWW_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->wefiww_wing_num_wefiww,
			   "wefiww_wing_num_wefiww", num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_wx_pdev_fw_stats_twv(const void *tag_buf,
						  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_pdev_fw_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WX_PDEV_FW_STATS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "ppdu_wecvd = %u\n",
			 htt_stats_buf->ppdu_wecvd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_cnt_fcs_ok = %u\n",
			 htt_stats_buf->mpdu_cnt_fcs_ok);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mpdu_cnt_fcs_eww = %u\n",
			 htt_stats_buf->mpdu_cnt_fcs_eww);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tcp_msdu_cnt = %u\n",
			 htt_stats_buf->tcp_msdu_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "tcp_ack_msdu_cnt = %u\n",
			 htt_stats_buf->tcp_ack_msdu_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "udp_msdu_cnt = %u\n",
			 htt_stats_buf->udp_msdu_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "othew_msdu_cnt = %u\n",
			 htt_stats_buf->othew_msdu_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_wing_mpdu_ind = %u\n",
			 htt_stats_buf->fw_wing_mpdu_ind);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->fw_wing_mgmt_subtype,
			   "fw_wing_mgmt_subtype", HTT_STATS_SUBTYPE_MAX, "\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->fw_wing_ctww_subtype,
			   "fw_wing_ctww_subtype", HTT_STATS_SUBTYPE_MAX, "\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_wing_mcast_data_msdu = %u\n",
			 htt_stats_buf->fw_wing_mcast_data_msdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_wing_bcast_data_msdu = %u\n",
			 htt_stats_buf->fw_wing_bcast_data_msdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_wing_ucast_data_msdu = %u\n",
			 htt_stats_buf->fw_wing_ucast_data_msdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_wing_nuww_data_msdu = %u\n",
			 htt_stats_buf->fw_wing_nuww_data_msdu);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_wing_mpdu_dwop = %u\n",
			 htt_stats_buf->fw_wing_mpdu_dwop);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ofwd_wocaw_data_ind_cnt = %u\n",
			 htt_stats_buf->ofwd_wocaw_data_ind_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "ofwd_wocaw_data_buf_wecycwe_cnt = %u\n",
			 htt_stats_buf->ofwd_wocaw_data_buf_wecycwe_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dwx_wocaw_data_ind_cnt = %u\n",
			 htt_stats_buf->dwx_wocaw_data_ind_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "dwx_wocaw_data_buf_wecycwe_cnt = %u\n",
			 htt_stats_buf->dwx_wocaw_data_buf_wecycwe_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wocaw_nondata_ind_cnt = %u\n",
			 htt_stats_buf->wocaw_nondata_ind_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wocaw_nondata_buf_wecycwe_cnt = %u\n",
			 htt_stats_buf->wocaw_nondata_buf_wecycwe_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_status_buf_wing_wefiww_cnt = %u\n",
			 htt_stats_buf->fw_status_buf_wing_wefiww_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_status_buf_wing_empty_cnt = %u\n",
			 htt_stats_buf->fw_status_buf_wing_empty_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_pkt_buf_wing_wefiww_cnt = %u\n",
			 htt_stats_buf->fw_pkt_buf_wing_wefiww_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_pkt_buf_wing_empty_cnt = %u\n",
			 htt_stats_buf->fw_pkt_buf_wing_empty_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_wink_buf_wing_wefiww_cnt = %u\n",
			 htt_stats_buf->fw_wink_buf_wing_wefiww_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_wink_buf_wing_empty_cnt = %u\n",
			 htt_stats_buf->fw_wink_buf_wing_empty_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "host_pkt_buf_wing_wefiww_cnt = %u\n",
			 htt_stats_buf->host_pkt_buf_wing_wefiww_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "host_pkt_buf_wing_empty_cnt = %u\n",
			 htt_stats_buf->host_pkt_buf_wing_empty_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mon_pkt_buf_wing_wefiww_cnt = %u\n",
			 htt_stats_buf->mon_pkt_buf_wing_wefiww_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mon_pkt_buf_wing_empty_cnt = %u\n",
			 htt_stats_buf->mon_pkt_buf_wing_empty_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "mon_status_buf_wing_wefiww_cnt = %u\n",
			 htt_stats_buf->mon_status_buf_wing_wefiww_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mon_status_buf_wing_empty_cnt = %u\n",
			 htt_stats_buf->mon_status_buf_wing_empty_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mon_desc_buf_wing_wefiww_cnt = %u\n",
			 htt_stats_buf->mon_desc_buf_wing_wefiww_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mon_desc_buf_wing_empty_cnt = %u\n",
			 htt_stats_buf->mon_desc_buf_wing_empty_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mon_dest_wing_update_cnt = %u\n",
			 htt_stats_buf->mon_dest_wing_update_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mon_dest_wing_fuww_cnt = %u\n",
			 htt_stats_buf->mon_dest_wing_fuww_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_suspend_cnt = %u\n",
			 htt_stats_buf->wx_suspend_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_suspend_faiw_cnt = %u\n",
			 htt_stats_buf->wx_suspend_faiw_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_wesume_cnt = %u\n",
			 htt_stats_buf->wx_wesume_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_wesume_faiw_cnt = %u\n",
			 htt_stats_buf->wx_wesume_faiw_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_wing_switch_cnt = %u\n",
			 htt_stats_buf->wx_wing_switch_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_wing_westowe_cnt = %u\n",
			 htt_stats_buf->wx_wing_westowe_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_fwush_cnt = %u\n",
			 htt_stats_buf->wx_fwush_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_wecovewy_weset_cnt = %u\n\n",
			 htt_stats_buf->wx_wecovewy_weset_cnt);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_wx_pdev_fw_wing_mpdu_eww_twv_v(const void *tag_buf,
					 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_pdev_fw_wing_mpdu_eww_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_WX_PDEV_FW_WING_MPDU_EWW_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->fw_wing_mpdu_eww,
			   "fw_wing_mpdu_eww", HTT_WX_STATS_WXDMA_MAX_EWW, "\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_wx_pdev_fw_mpdu_dwop_twv_v(const void *tag_buf,
				     u16 tag_wen,
				     stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_pdev_fw_mpdu_dwop_twv_v *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	u16 num_ewems = min_t(u16, (tag_wen >> 2), HTT_WX_STATS_FW_DWOP_WEASON_MAX);

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WX_PDEV_FW_MPDU_DWOP_TWV_V:\n");

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->fw_mpdu_dwop, "fw_mpdu_dwop",
			   num_ewems, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_wx_pdev_fw_stats_phy_eww_twv(const void *tag_buf,
				       stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_wx_pdev_fw_stats_phy_eww_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_WX_PDEV_FW_STATS_PHY_EWW_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id__wowd = %u\n",
			 htt_stats_buf->mac_id__wowd);
	wen += scnpwintf(buf + wen, buf_wen - wen, "totaw_phy_eww_nct = %u\n",
			 htt_stats_buf->totaw_phy_eww_cnt);

	PWINT_AWWAY_TO_BUF(buf, wen, htt_stats_buf->phy_eww, "phy_ewws",
			   HTT_STATS_PHY_EWW_MAX, "\n\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_pdev_cca_stats_hist_twv(const void *tag_buf,
				  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_pdev_cca_stats_hist_v1_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\nHTT_PDEV_CCA_STATS_HIST_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "chan_num = %u\n",
			 htt_stats_buf->chan_num);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_wecowds = %u\n",
			 htt_stats_buf->num_wecowds);
	wen += scnpwintf(buf + wen, buf_wen - wen, "vawid_cca_countews_bitmap = 0x%x\n",
			 htt_stats_buf->vawid_cca_countews_bitmap);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cowwection_intewvaw = %u\n\n",
			 htt_stats_buf->cowwection_intewvaw);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_PDEV_STATS_CCA_COUNTEWS_TWV:(in usec)\n");
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "|  tx_fwame|   wx_fwame|   wx_cweaw| my_wx_fwame|        cnt| med_wx_idwe| med_tx_idwe_gwobaw|   cca_obss|\n");

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_pdev_stats_cca_countews_twv(const void *tag_buf,
				      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_pdev_stats_cca_countews_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "|%10u| %10u| %10u| %11u| %10u| %11u| %18u| %10u|\n",
			 htt_stats_buf->tx_fwame_usec,
			 htt_stats_buf->wx_fwame_usec,
			 htt_stats_buf->wx_cweaw_usec,
			 htt_stats_buf->my_wx_fwame_usec,
			 htt_stats_buf->usec_cnt,
			 htt_stats_buf->med_wx_idwe_usec,
			 htt_stats_buf->med_tx_idwe_gwobaw_usec,
			 htt_stats_buf->cca_obss_usec);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_hw_stats_whaw_tx_twv(const void *tag_buf,
						  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_hw_stats_whaw_tx_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_HW_STATS_WHAW_TX_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "mac_id = %wu\n",
			 FIEWD_GET(HTT_STATS_MAC_ID, htt_stats_buf->mac_id__wowd));
	wen += scnpwintf(buf + wen, buf_wen - wen, "wast_unpause_ppdu_id = %u\n",
			 htt_stats_buf->wast_unpause_ppdu_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwsch_unpause_wait_tqm_wwite = %u\n",
			 htt_stats_buf->hwsch_unpause_wait_tqm_wwite);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwsch_dummy_twv_skipped = %u\n",
			 htt_stats_buf->hwsch_dummy_twv_skipped);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "hwsch_misawigned_offset_weceived = %u\n",
			 htt_stats_buf->hwsch_misawigned_offset_weceived);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwsch_weset_count = %u\n",
			 htt_stats_buf->hwsch_weset_count);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwsch_dev_weset_waw = %u\n",
			 htt_stats_buf->hwsch_dev_weset_waw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwsch_dewayed_pause = %u\n",
			 htt_stats_buf->hwsch_dewayed_pause);
	wen += scnpwintf(buf + wen, buf_wen - wen, "hwsch_wong_dewayed_pause = %u\n",
			 htt_stats_buf->hwsch_wong_dewayed_pause);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sch_wx_ppdu_no_wesponse = %u\n",
			 htt_stats_buf->sch_wx_ppdu_no_wesponse);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sch_sewfgen_wesponse = %u\n",
			 htt_stats_buf->sch_sewfgen_wesponse);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sch_wx_sifs_wesp_twiggew= %u\n\n",
			 htt_stats_buf->sch_wx_sifs_wesp_twiggew);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_pdev_stats_twt_sessions_twv(const void *tag_buf,
				      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_pdev_stats_twt_sessions_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_PDEV_STATS_TWT_SESSIONS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "pdev_id = %u\n",
			 htt_stats_buf->pdev_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_sessions = %u\n\n",
			 htt_stats_buf->num_sessions);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_pdev_stats_twt_session_twv(const void *tag_buf,
				     stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_pdev_stats_twt_session_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_PDEV_STATS_TWT_SESSION_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "vdev_id = %u\n",
			 htt_stats_buf->vdev_id);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "peew_mac = %02wx:%02wx:%02wx:%02wx:%02wx:%02wx\n",
			 FIEWD_GET(HTT_MAC_ADDW_W32_0,
				   htt_stats_buf->peew_mac.mac_addw_w32),
			 FIEWD_GET(HTT_MAC_ADDW_W32_1,
				   htt_stats_buf->peew_mac.mac_addw_w32),
			 FIEWD_GET(HTT_MAC_ADDW_W32_2,
				   htt_stats_buf->peew_mac.mac_addw_w32),
			 FIEWD_GET(HTT_MAC_ADDW_W32_3,
				   htt_stats_buf->peew_mac.mac_addw_w32),
			 FIEWD_GET(HTT_MAC_ADDW_H16_0,
				   htt_stats_buf->peew_mac.mac_addw_h16),
			 FIEWD_GET(HTT_MAC_ADDW_H16_1,
				   htt_stats_buf->peew_mac.mac_addw_h16));
	wen += scnpwintf(buf + wen, buf_wen - wen, "fwow_id_fwags = %u\n",
			 htt_stats_buf->fwow_id_fwags);
	wen += scnpwintf(buf + wen, buf_wen - wen, "diawog_id = %u\n",
			 htt_stats_buf->diawog_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wake_duwa_us = %u\n",
			 htt_stats_buf->wake_duwa_us);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wake_intvw_us = %u\n",
			 htt_stats_buf->wake_intvw_us);
	wen += scnpwintf(buf + wen, buf_wen - wen, "sp_offset_us = %u\n\n",
			 htt_stats_buf->sp_offset_us);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_pdev_obss_pd_stats_twv_v(const void *tag_buf,
				   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_pdev_obss_pd_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "OBSS Tx success PPDU = %u\n",
			   htt_stats_buf->num_obss_tx_ppdu_success);
	wen += scnpwintf(buf + wen, buf_wen - wen, "OBSS Tx faiwuwes PPDU = %u\n",
			   htt_stats_buf->num_obss_tx_ppdu_faiwuwe);
	wen += scnpwintf(buf + wen, buf_wen - wen, "Non-SWG Oppowtunities = %u\n",
			   htt_stats_buf->num_non_swg_oppowtunities);
	wen += scnpwintf(buf + wen, buf_wen - wen, "Non-SWG twied PPDU = %u\n",
			   htt_stats_buf->num_non_swg_ppdu_twied);
	wen += scnpwintf(buf + wen, buf_wen - wen, "Non-SWG success PPDU = %u\n",
			   htt_stats_buf->num_non_swg_ppdu_success);
	wen += scnpwintf(buf + wen, buf_wen - wen, "SWG Oppowtunities = %u\n",
			   htt_stats_buf->num_swg_oppowtunities);
	wen += scnpwintf(buf + wen, buf_wen - wen, "SWG twied PPDU = %u\n",
			   htt_stats_buf->num_swg_ppdu_twied);
	wen += scnpwintf(buf + wen, buf_wen - wen, "SWG success PPDU = %u\n\n",
			   htt_stats_buf->num_swg_ppdu_success);

	if (wen >= buf_wen)
		buf[buf_wen - 1] = 0;
	ewse
		buf[wen] = 0;

	stats_weq->buf_wen = wen;
}

static inwine void htt_pwint_backpwessuwe_stats_twv_v(const u32 *tag_buf,
						      u8 *data)
{
	stwuct debug_htt_stats_weq *stats_weq =
			(stwuct debug_htt_stats_weq *)data;
	stwuct htt_wing_backpwessuwe_stats_twv *htt_stats_buf =
			(stwuct htt_wing_backpwessuwe_stats_twv *)tag_buf;
	int i;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	wen += scnpwintf(buf + wen, buf_wen - wen, "pdev_id = %u\n",
			 htt_stats_buf->pdev_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cuwwent_head_idx = %u\n",
			 htt_stats_buf->cuwwent_head_idx);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cuwwent_taiw_idx = %u\n",
			 htt_stats_buf->cuwwent_taiw_idx);
	wen += scnpwintf(buf + wen, buf_wen - wen, "num_htt_msgs_sent = %u\n",
			 htt_stats_buf->num_htt_msgs_sent);
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "backpwessuwe_time_ms = %u\n",
			 htt_stats_buf->backpwessuwe_time_ms);

	fow (i = 0; i < 5; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "backpwessuwe_hist_%u = %u\n",
				 i + 1, htt_stats_buf->backpwessuwe_hist[i]);

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "============================\n");

	if (wen >= buf_wen) {
		buf[buf_wen - 1] = 0;
		stats_weq->buf_wen = buf_wen - 1;
	} ewse {
		buf[wen] = 0;
		stats_weq->buf_wen = wen;
	}
}

static inwine
void htt_pwint_pdev_tx_wate_txbf_stats_twv(const void *tag_buf,
					   stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_pdev_txwate_txbf_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	int i;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_STATS_PDEV_TX_WATE_TXBF_STATS:\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "tx_ow_mcs = ");
	fow (i = 0; i < HTT_TX_TXBF_WATE_STATS_NUM_MCS_COUNTEWS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%d:%u,", i, htt_stats_buf->tx_su_ow_mcs[i]);
	wen--;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\ntx_ibf_mcs = ");
	fow (i = 0; i < HTT_TX_TXBF_WATE_STATS_NUM_MCS_COUNTEWS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%d:%u,", i, htt_stats_buf->tx_su_ibf_mcs[i]);
	wen--;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\ntx_txbf_mcs =");
	fow (i = 0; i < HTT_TX_TXBF_WATE_STATS_NUM_MCS_COUNTEWS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%d:%u,", i, htt_stats_buf->tx_su_txbf_mcs[i]);
	wen--;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\ntx_ow_nss = ");
	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_SPATIAW_STWEAMS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%d:%u,", i, htt_stats_buf->tx_su_ow_nss[i]);
	wen--;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\ntx_ibf_nss = ");
	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_SPATIAW_STWEAMS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%d:%u,", i, htt_stats_buf->tx_su_ibf_nss[i]);
	wen--;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\ntx_txbf_nss = ");
	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_SPATIAW_STWEAMS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%d:%u,", i, htt_stats_buf->tx_su_txbf_nss[i]);
	wen--;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\ntx_ow_bw = ");
	fow (i = 0; i < HTT_TX_TXBF_WATE_STATS_NUM_BW_COUNTEWS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%d:%u,", i, htt_stats_buf->tx_su_ow_bw[i]);
	wen--;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\ntx_ibf_bw = ");
	fow (i = 0; i < HTT_TX_TXBF_WATE_STATS_NUM_BW_COUNTEWS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%d:%u,", i, htt_stats_buf->tx_su_ibf_bw[i]);
	wen--;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\ntx_txbf_bw = ");
	fow (i = 0; i < HTT_TX_TXBF_WATE_STATS_NUM_BW_COUNTEWS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "%d:%u,", i, htt_stats_buf->tx_su_txbf_bw[i]);
	wen--;

	wen += scnpwintf(buf + wen, buf_wen - wen, "\n");

	stats_weq->buf_wen = wen;
}

static inwine
void htt_pwint_txbf_ofdma_ndpa_stats_twv(const void *tag_buf,
					 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_txbf_ofdma_ndpa_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	int i;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TXBF_OFDMA_NDPA_STATS_TWV:\n");

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_OFDMA_USEW_STATS; i++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_ndpa_queued_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_ndpa_queued[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_ndpa_twied_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_ndpa_twied[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_ndpa_fwushed_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_ndpa_fwushed[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_ndpa_eww_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_ndpa_eww[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	}

	stats_weq->buf_wen = wen;
}

static inwine
void htt_pwint_txbf_ofdma_ndp_stats_twv(const void *tag_buf,
					stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_txbf_ofdma_ndp_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	int i;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TXBF_OFDMA_NDP_STATS_TWV:\n");

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_OFDMA_USEW_STATS; i++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_ndp_queued_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_ndp_queued[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_ndp_twied_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_ndp_twied[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_ndp_fwushed_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_ndp_fwushed[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_ndp_eww_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_ndp_eww[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	}

	stats_weq->buf_wen = wen;
}

static inwine
void htt_pwint_txbf_ofdma_bwp_stats_twv(const void *tag_buf,
					stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_txbf_ofdma_bwp_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	int i;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TXBF_OFDMA_BWP_STATS_TWV:\n");

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_OFDMA_USEW_STATS; i++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_bwpoww_queued_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_bwpoww_queued[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_bwpoww_twied_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_bwpoww_twied[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_bwpoww_fwushed_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_bwpoww_fwushed[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_bwp_eww_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_bwp_eww[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_bwp_eww_num_cbf_wcvd_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_bwp_eww_num_cbf_wcvd[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	}

	stats_weq->buf_wen = wen;
}

static inwine
void htt_pwint_txbf_ofdma_steew_stats_twv(const void *tag_buf,
					  stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_txbf_ofdma_steew_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	int i;

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_TXBF_OFDMA_STEEW_STATS_TWV:\n");

	fow (i = 0; i < HTT_TX_PDEV_STATS_NUM_OFDMA_USEW_STATS; i++) {
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_num_ppdu_steew_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_num_ppdu_steew[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_num_ppdu_ow_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_num_ppdu_ow[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_num_usws_pwefetch_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_num_usws_pwefetch[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_num_usws_sound_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_num_usws_sound[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "ax_ofdma_num_usws_fowce_sound_usew%d = %u\n",
				 i, htt_stats_buf->ax_ofdma_num_usws_fowce_sound[i]);
		wen += scnpwintf(buf + wen, buf_wen - wen, "\n");
	}

	stats_weq->buf_wen = wen;
}

static inwine
void htt_pwint_phy_countews_twv(const void *tag_buf,
				stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_phy_countews_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	int i;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_PHY_COUNTEWS_TWV:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_ofdma_timing_eww_cnt = %u\n",
			 htt_stats_buf->wx_ofdma_timing_eww_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_cck_faiw_cnt = %u\n",
			 htt_stats_buf->wx_cck_faiw_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "mactx_abowt_cnt = %u\n",
			 htt_stats_buf->mactx_abowt_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "macwx_abowt_cnt = %u\n",
			 htt_stats_buf->macwx_abowt_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phytx_abowt_cnt = %u\n",
			 htt_stats_buf->phytx_abowt_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phywx_abowt_cnt = %u\n",
			 htt_stats_buf->phywx_abowt_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phywx_defew_abowt_cnt = %u\n",
			 htt_stats_buf->phywx_defew_abowt_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_gain_adj_wstf_event_cnt = %u\n",
			 htt_stats_buf->wx_gain_adj_wstf_event_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_gain_adj_non_wegacy_cnt = %u\n",
			 htt_stats_buf->wx_gain_adj_non_wegacy_cnt);

	fow (i = 0; i < HTT_MAX_WX_PKT_CNT; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen, "wx_pkt_cnt[%d] = %u\n",
				 i, htt_stats_buf->wx_pkt_cnt[i]);

	fow (i = 0; i < HTT_MAX_WX_PKT_CWC_PASS_CNT; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "wx_pkt_cwc_pass_cnt[%d] = %u\n",
				 i, htt_stats_buf->wx_pkt_cwc_pass_cnt[i]);

	fow (i = 0; i < HTT_MAX_PEW_BWK_EWW_CNT; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "pew_bwk_eww_cnt[%d] = %u\n",
				 i, htt_stats_buf->pew_bwk_eww_cnt[i]);

	fow (i = 0; i < HTT_MAX_WX_OTA_EWW_CNT; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen,
				 "wx_ota_eww_cnt[%d] = %u\n",
				 i, htt_stats_buf->wx_ota_eww_cnt[i]);

	stats_weq->buf_wen = wen;
}

static inwine
void htt_pwint_phy_stats_twv(const void *tag_buf,
			     stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_phy_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	int i;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_PHY_STATS_TWV:\n");

	fow (i = 0; i < HTT_STATS_MAX_CHAINS; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen, "nf_chain[%d] = %d\n",
				 i, htt_stats_buf->nf_chain[i]);

	wen += scnpwintf(buf + wen, buf_wen - wen, "fawse_wadaw_cnt = %u\n",
			 htt_stats_buf->fawse_wadaw_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wadaw_cs_cnt = %u\n",
			 htt_stats_buf->wadaw_cs_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "ani_wevew = %d\n",
			 htt_stats_buf->ani_wevew);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fw_wun_time = %u\n",
			 htt_stats_buf->fw_wun_time);

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_phy_weset_countews_twv(const void *tag_buf,
				 u16 tag_wen,
				 stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_phy_weset_countews_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	if (tag_wen < sizeof(*htt_stats_buf))
		wetuwn;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_PHY_WESET_COUNTEWS_TWV:\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "pdev_id = %u\n",
			 htt_stats_buf->pdev_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cf_active_wow_faiw_cnt = %u\n",
			 htt_stats_buf->cf_active_wow_faiw_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cf_active_wow_pass_cnt = %u\n",
			 htt_stats_buf->cf_active_wow_pass_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_off_thwough_vweg_cnt = %u\n",
			 htt_stats_buf->phy_off_thwough_vweg_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fowce_cawibwation_cnt = %u\n",
			 htt_stats_buf->fowce_cawibwation_cnt);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wf_mode_switch_phy_off_cnt = %u\n",
			 htt_stats_buf->wf_mode_switch_phy_off_cnt);

	stats_weq->buf_wen = wen;
}

static inwine void
htt_pwint_phy_weset_stats_twv(const void *tag_buf,
			      u16 tag_wen,
			      stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_phy_weset_stats_twv *htt_stats_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;

	if (tag_wen < sizeof(*htt_stats_buf))
		wetuwn;

	wen += scnpwintf(buf + wen, buf_wen - wen, "HTT_PHY_WESET_STATS_TWV:\n");

	wen += scnpwintf(buf + wen, buf_wen - wen, "pdev_id = %u\n",
			 htt_stats_buf->pdev_id);
	wen += scnpwintf(buf + wen, buf_wen - wen, "chan_mhz = %u\n",
			 htt_stats_buf->chan_mhz);
	wen += scnpwintf(buf + wen, buf_wen - wen, "chan_band_centew_fweq1 = %u\n",
			 htt_stats_buf->chan_band_centew_fweq1);
	wen += scnpwintf(buf + wen, buf_wen - wen, "chan_band_centew_fweq2 = %u\n",
			 htt_stats_buf->chan_band_centew_fweq2);
	wen += scnpwintf(buf + wen, buf_wen - wen, "chan_phy_mode = %u\n",
			 htt_stats_buf->chan_phy_mode);
	wen += scnpwintf(buf + wen, buf_wen - wen, "chan_fwags = 0x%0x\n",
			 htt_stats_buf->chan_fwags);
	wen += scnpwintf(buf + wen, buf_wen - wen, "chan_num = %u\n",
			 htt_stats_buf->chan_num);
	wen += scnpwintf(buf + wen, buf_wen - wen, "weset_cause = 0x%0x\n",
			 htt_stats_buf->weset_cause);
	wen += scnpwintf(buf + wen, buf_wen - wen, "pwev_weset_cause = 0x%0x\n",
			 htt_stats_buf->pwev_weset_cause);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_wawm_weset_swc = 0x%0x\n",
			 htt_stats_buf->phy_wawm_weset_swc);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wx_gain_tbw_mode = %d\n",
			 htt_stats_buf->wx_gain_tbw_mode);
	wen += scnpwintf(buf + wen, buf_wen - wen, "xbaw_vaw = 0x%0x\n",
			 htt_stats_buf->xbaw_vaw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "fowce_cawibwation = %u\n",
			 htt_stats_buf->fowce_cawibwation);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phywf_mode = %u\n",
			 htt_stats_buf->phywf_mode);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_homechan = %u\n",
			 htt_stats_buf->phy_homechan);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_tx_ch_mask = 0x%0x\n",
			 htt_stats_buf->phy_tx_ch_mask);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_wx_ch_mask = 0x%0x\n",
			 htt_stats_buf->phy_wx_ch_mask);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phybb_ini_mask = 0x%0x\n",
			 htt_stats_buf->phybb_ini_mask);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phywf_ini_mask = 0x%0x\n",
			 htt_stats_buf->phywf_ini_mask);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_dfs_en_mask = 0x%0x\n",
			 htt_stats_buf->phy_dfs_en_mask);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_sscan_en_mask = 0x%0x\n",
			 htt_stats_buf->phy_sscan_en_mask);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_synth_sew_mask = 0x%0x\n",
			 htt_stats_buf->phy_synth_sew_mask);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_adfs_fweq = %u\n",
			 htt_stats_buf->phy_adfs_fweq);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cck_fiw_settings = 0x%0x\n",
			 htt_stats_buf->cck_fiw_settings);
	wen += scnpwintf(buf + wen, buf_wen - wen, "phy_dyn_pwi_chan = %u\n",
			 htt_stats_buf->phy_dyn_pwi_chan);
	wen += scnpwintf(buf + wen, buf_wen - wen, "cca_thwesh = 0x%0x\n",
			 htt_stats_buf->cca_thwesh);
	wen += scnpwintf(buf + wen, buf_wen - wen, "dyn_cca_status = %u\n",
			 htt_stats_buf->dyn_cca_status);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wxdesense_thwesh_hw = 0x%x\n",
			 htt_stats_buf->wxdesense_thwesh_hw);
	wen += scnpwintf(buf + wen, buf_wen - wen, "wxdesense_thwesh_sw = 0x%x\n",
			 htt_stats_buf->wxdesense_thwesh_sw);

	stats_weq->buf_wen = wen;
}

static inwine
void htt_pwint_peew_ctww_path_txwx_stats_twv(const void *tag_buf,
					     stwuct debug_htt_stats_weq *stats_weq)
{
	const stwuct htt_peew_ctww_path_txwx_stats_twv *htt_stat_buf = tag_buf;
	u8 *buf = stats_weq->buf;
	u32 wen = stats_weq->buf_wen;
	u32 buf_wen = ATH11K_HTT_STATS_BUF_SIZE;
	int i;
	const chaw *mgmt_fwm_type[ATH11K_STATS_MGMT_FWM_TYPE_MAX - 1] = {
		"assoc_weq", "assoc_wesp",
		"weassoc_weq", "weassoc_wesp",
		"pwobe_weq", "pwobe_wesp",
		"timing_advewtisement", "wesewved",
		"beacon", "atim", "disassoc",
		"auth", "deauth", "action", "action_no_ack"};

	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "HTT_STATS_PEEW_CTWW_PATH_TXWX_STATS_TAG:\n");
	wen += scnpwintf(buf + wen, buf_wen - wen,
			 "peew_mac_addw = %02x:%02x:%02x:%02x:%02x:%02x\n",
			 htt_stat_buf->peew_mac_addw[0], htt_stat_buf->peew_mac_addw[1],
			 htt_stat_buf->peew_mac_addw[2], htt_stat_buf->peew_mac_addw[3],
			 htt_stat_buf->peew_mac_addw[4], htt_stat_buf->peew_mac_addw[5]);

	wen += scnpwintf(buf + wen, buf_wen - wen, "peew_tx_mgmt_subtype:\n");
	fow (i = 0; i < ATH11K_STATS_MGMT_FWM_TYPE_MAX - 1; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen, "%s:%u\n",
				 mgmt_fwm_type[i],
				 htt_stat_buf->peew_wx_mgmt_subtype[i]);

	wen += scnpwintf(buf + wen, buf_wen - wen, "peew_wx_mgmt_subtype:\n");
	fow (i = 0; i < ATH11K_STATS_MGMT_FWM_TYPE_MAX - 1; i++)
		wen += scnpwintf(buf + wen, buf_wen - wen, "%s:%u\n",
				 mgmt_fwm_type[i],
				 htt_stat_buf->peew_wx_mgmt_subtype[i]);

	wen += scnpwintf(buf + wen, buf_wen - wen, "\n");

	stats_weq->buf_wen = wen;
}

static int ath11k_dbg_htt_ext_stats_pawse(stwuct ath11k_base *ab,
					  u16 tag, u16 wen, const void *tag_buf,
					  void *usew_data)
{
	stwuct debug_htt_stats_weq *stats_weq = usew_data;

	switch (tag) {
	case HTT_STATS_TX_PDEV_CMN_TAG:
		htt_pwint_tx_pdev_stats_cmn_twv(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_TX_PDEV_UNDEWWUN_TAG:
		htt_pwint_tx_pdev_stats_uwwn_twv_v(tag_buf, wen, stats_weq);
		bweak;
	case HTT_STATS_TX_PDEV_SIFS_TAG:
		htt_pwint_tx_pdev_stats_sifs_twv_v(tag_buf, wen, stats_weq);
		bweak;
	case HTT_STATS_TX_PDEV_FWUSH_TAG:
		htt_pwint_tx_pdev_stats_fwush_twv_v(tag_buf, wen, stats_weq);
		bweak;
	case HTT_STATS_TX_PDEV_PHY_EWW_TAG:
		htt_pwint_tx_pdev_stats_phy_eww_twv_v(tag_buf, wen, stats_weq);
		bweak;
	case HTT_STATS_TX_PDEV_SIFS_HIST_TAG:
		htt_pwint_tx_pdev_stats_sifs_hist_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_PDEV_TX_PPDU_STATS_TAG:
		htt_pwint_tx_pdev_stats_tx_ppdu_stats_twv_v(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_PDEV_TWIED_MPDU_CNT_HIST_TAG:
		htt_pwint_tx_pdev_stats_twied_mpdu_cnt_hist_twv_v(tag_buf, wen,
								  stats_weq);
		bweak;

	case HTT_STATS_STWING_TAG:
		htt_pwint_stats_stwing_twv(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_CMN_TAG:
		htt_pwint_tx_hwq_stats_cmn_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_DIFS_WATENCY_TAG:
		htt_pwint_tx_hwq_difs_watency_stats_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_CMD_WESUWT_TAG:
		htt_pwint_tx_hwq_cmd_wesuwt_stats_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_CMD_STAWW_TAG:
		htt_pwint_tx_hwq_cmd_staww_stats_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_FES_STATUS_TAG:
		htt_pwint_tx_hwq_fes_wesuwt_stats_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_TWIED_MPDU_CNT_HIST_TAG:
		htt_pwint_tx_hwq_twied_mpdu_cnt_hist_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_TXOP_USED_CNT_HIST_TAG:
		htt_pwint_tx_hwq_txop_used_cnt_hist_twv_v(tag_buf, wen, stats_weq);
		bweak;
	case HTT_STATS_TX_TQM_GEN_MPDU_TAG:
		htt_pwint_tx_tqm_gen_mpdu_stats_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_TQM_WIST_MPDU_TAG:
		htt_pwint_tx_tqm_wist_mpdu_stats_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_TQM_WIST_MPDU_CNT_TAG:
		htt_pwint_tx_tqm_wist_mpdu_cnt_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_TQM_CMN_TAG:
		htt_pwint_tx_tqm_cmn_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_TQM_PDEV_TAG:
		htt_pwint_tx_tqm_pdev_stats_twv_v(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_TQM_CMDQ_STATUS_TAG:
		htt_pwint_tx_tqm_cmdq_status_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_DE_EAPOW_PACKETS_TAG:
		htt_pwint_tx_de_eapow_packets_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_DE_CWASSIFY_FAIWED_TAG:
		htt_pwint_tx_de_cwassify_faiwed_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_DE_CWASSIFY_STATS_TAG:
		htt_pwint_tx_de_cwassify_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_DE_CWASSIFY_STATUS_TAG:
		htt_pwint_tx_de_cwassify_status_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_DE_ENQUEUE_PACKETS_TAG:
		htt_pwint_tx_de_enqueue_packets_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_DE_ENQUEUE_DISCAWD_TAG:
		htt_pwint_tx_de_enqueue_discawd_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_DE_FW2WBM_WING_FUWW_HIST_TAG:
		htt_pwint_tx_de_fw2wbm_wing_fuww_hist_twv(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_TX_DE_CMN_TAG:
		htt_pwint_tx_de_cmn_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_WING_IF_TAG:
		htt_pwint_wing_if_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_PDEV_MU_MIMO_STATS_TAG:
		htt_pwint_tx_pdev_mu_mimo_sch_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_SFM_CMN_TAG:
		htt_pwint_sfm_cmn_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_SWING_STATS_TAG:
		htt_pwint_swing_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_WX_PDEV_FW_STATS_TAG:
		htt_pwint_wx_pdev_fw_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_WX_PDEV_FW_WING_MPDU_EWW_TAG:
		htt_pwint_wx_pdev_fw_wing_mpdu_eww_twv_v(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_WX_PDEV_FW_MPDU_DWOP_TAG:
		htt_pwint_wx_pdev_fw_mpdu_dwop_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_WX_SOC_FW_STATS_TAG:
		htt_pwint_wx_soc_fw_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_WX_SOC_FW_WEFIWW_WING_EMPTY_TAG:
		htt_pwint_wx_soc_fw_wefiww_wing_empty_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_WX_SOC_FW_WEFIWW_WING_NUM_WEFIWW_TAG:
		htt_pwint_wx_soc_fw_wefiww_wing_num_wefiww_twv_v(
				tag_buf, wen, stats_weq);
		bweak;
	case HTT_STATS_WX_WEFIWW_WXDMA_EWW_TAG:
		htt_pwint_wx_soc_fw_wefiww_wing_num_wxdma_eww_twv_v(
				tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_WX_WEFIWW_WEO_EWW_TAG:
		htt_pwint_wx_soc_fw_wefiww_wing_num_weo_eww_twv_v(
				tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_WX_WEO_WESOUWCE_STATS_TAG:
		htt_pwint_wx_weo_debug_stats_twv_v(
				tag_buf, stats_weq);
		bweak;
	case HTT_STATS_WX_PDEV_FW_STATS_PHY_EWW_TAG:
		htt_pwint_wx_pdev_fw_stats_phy_eww_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_PDEV_WATE_STATS_TAG:
		htt_pwint_tx_pdev_wate_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_WX_PDEV_WATE_STATS_TAG:
		htt_pwint_wx_pdev_wate_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_PDEV_SCHEDUWEW_TXQ_STATS_TAG:
		htt_pwint_tx_pdev_stats_sched_pew_txq_twv(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_TX_SCHED_CMN_TAG:
		htt_pwint_stats_tx_sched_cmn_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_PDEV_MPDU_STATS_TAG:
		htt_pwint_tx_pdev_mu_mimo_mpdu_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_SCHED_TXQ_CMD_POSTED_TAG:
		htt_pwint_sched_txq_cmd_posted_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_WING_IF_CMN_TAG:
		htt_pwint_wing_if_cmn_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_SFM_CWIENT_USEW_TAG:
		htt_pwint_sfm_cwient_usew_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_SFM_CWIENT_TAG:
		htt_pwint_sfm_cwient_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_TQM_EWWOW_STATS_TAG:
		htt_pwint_tx_tqm_ewwow_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_SCHED_TXQ_CMD_WEAPED_TAG:
		htt_pwint_sched_txq_cmd_weaped_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_SWING_CMN_TAG:
		htt_pwint_swing_cmn_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_SOUNDING_STATS_TAG:
		htt_pwint_tx_sounding_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_SEWFGEN_AC_EWW_STATS_TAG:
		htt_pwint_tx_sewfgen_ac_eww_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_SEWFGEN_CMN_STATS_TAG:
		htt_pwint_tx_sewfgen_cmn_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_SEWFGEN_AC_STATS_TAG:
		htt_pwint_tx_sewfgen_ac_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_SEWFGEN_AX_STATS_TAG:
		htt_pwint_tx_sewfgen_ax_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_SEWFGEN_AX_EWW_STATS_TAG:
		htt_pwint_tx_sewfgen_ax_eww_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_MUMIMO_SCH_STATS_TAG:
		htt_pwint_tx_hwq_mu_mimo_sch_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_MUMIMO_MPDU_STATS_TAG:
		htt_pwint_tx_hwq_mu_mimo_mpdu_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_HWQ_MUMIMO_CMN_STATS_TAG:
		htt_pwint_tx_hwq_mu_mimo_cmn_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_HW_INTW_MISC_TAG:
		htt_pwint_hw_stats_intw_misc_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_HW_WD_TIMEOUT_TAG:
		htt_pwint_hw_stats_wd_timeout_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_HW_PDEV_EWWS_TAG:
		htt_pwint_hw_stats_pdev_ewws_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_COUNTEW_NAME_TAG:
		htt_pwint_countew_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_TID_DETAIWS_TAG:
		htt_pwint_tx_tid_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_TID_DETAIWS_V1_TAG:
		htt_pwint_tx_tid_stats_v1_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_WX_TID_DETAIWS_TAG:
		htt_pwint_wx_tid_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_PEEW_STATS_CMN_TAG:
		htt_pwint_peew_stats_cmn_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_PEEW_DETAIWS_TAG:
		htt_pwint_peew_detaiws_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_PEEW_MSDU_FWOWQ_TAG:
		htt_pwint_msdu_fwow_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_PEEW_TX_WATE_STATS_TAG:
		htt_pwint_tx_peew_wate_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_PEEW_WX_WATE_STATS_TAG:
		htt_pwint_wx_peew_wate_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_TX_DE_COMPW_STATS_TAG:
		htt_pwint_tx_de_compw_stats_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_PDEV_CCA_1SEC_HIST_TAG:
	case HTT_STATS_PDEV_CCA_100MSEC_HIST_TAG:
	case HTT_STATS_PDEV_CCA_STAT_CUMUWATIVE_TAG:
		htt_pwint_pdev_cca_stats_hist_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_PDEV_CCA_COUNTEWS_TAG:
		htt_pwint_pdev_stats_cca_countews_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_WHAW_TX_TAG:
		htt_pwint_hw_stats_whaw_tx_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_PDEV_TWT_SESSIONS_TAG:
		htt_pwint_pdev_stats_twt_sessions_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_PDEV_TWT_SESSION_TAG:
		htt_pwint_pdev_stats_twt_session_twv(tag_buf, stats_weq);
		bweak;

	case HTT_STATS_SCHED_TXQ_SCHED_OWDEW_SU_TAG:
		htt_pwint_sched_txq_sched_owdew_su_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_SCHED_TXQ_SCHED_INEWIGIBIWITY_TAG:
		htt_pwint_sched_txq_sched_inewigibiwity_twv_v(tag_buf, wen, stats_weq);
		bweak;

	case HTT_STATS_PDEV_OBSS_PD_TAG:
		htt_pwint_pdev_obss_pd_stats_twv_v(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_WING_BACKPWESSUWE_STATS_TAG:
		htt_pwint_backpwessuwe_stats_twv_v(tag_buf, usew_data);
		bweak;
	case HTT_STATS_PDEV_TX_WATE_TXBF_STATS_TAG:
		htt_pwint_pdev_tx_wate_txbf_stats_twv(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_TXBF_OFDMA_NDPA_STATS_TAG:
		htt_pwint_txbf_ofdma_ndpa_stats_twv(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_TXBF_OFDMA_NDP_STATS_TAG:
		htt_pwint_txbf_ofdma_ndp_stats_twv(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_TXBF_OFDMA_BWP_STATS_TAG:
		htt_pwint_txbf_ofdma_bwp_stats_twv(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_TXBF_OFDMA_STEEW_STATS_TAG:
		htt_pwint_txbf_ofdma_steew_stats_twv(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_PHY_COUNTEWS_TAG:
		htt_pwint_phy_countews_twv(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_PHY_STATS_TAG:
		htt_pwint_phy_stats_twv(tag_buf, stats_weq);
		bweak;
	case HTT_STATS_PHY_WESET_COUNTEWS_TAG:
		htt_pwint_phy_weset_countews_twv(tag_buf, wen, stats_weq);
		bweak;
	case HTT_STATS_PHY_WESET_STATS_TAG:
		htt_pwint_phy_weset_stats_twv(tag_buf, wen, stats_weq);
		bweak;
	case HTT_STATS_PEEW_CTWW_PATH_TXWX_STATS_TAG:
		htt_pwint_peew_ctww_path_txwx_stats_twv(tag_buf, stats_weq);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

void ath11k_debugfs_htt_ext_stats_handwew(stwuct ath11k_base *ab,
					  stwuct sk_buff *skb)
{
	stwuct ath11k_htt_extd_stats_msg *msg;
	stwuct debug_htt_stats_weq *stats_weq;
	stwuct ath11k *aw;
	u32 wen;
	u64 cookie;
	int wet;
	boow send_compwetion = fawse;
	u8 pdev_id;

	msg = (stwuct ath11k_htt_extd_stats_msg *)skb->data;
	cookie = msg->cookie;

	if (FIEWD_GET(HTT_STATS_COOKIE_MSB, cookie) != HTT_STATS_MAGIC_VAWUE) {
		ath11k_wawn(ab, "weceived invawid htt ext stats event\n");
		wetuwn;
	}

	pdev_id = FIEWD_GET(HTT_STATS_COOKIE_WSB, cookie);
	wcu_wead_wock();
	aw = ath11k_mac_get_aw_by_pdev_id(ab, pdev_id);
	wcu_wead_unwock();
	if (!aw) {
		ath11k_wawn(ab, "faiwed to get aw fow pdev_id %d\n", pdev_id);
		wetuwn;
	}

	stats_weq = aw->debug.htt_stats.stats_weq;
	if (!stats_weq)
		wetuwn;

	spin_wock_bh(&aw->debug.htt_stats.wock);

	stats_weq->done = FIEWD_GET(HTT_T2H_EXT_STATS_INFO1_DONE, msg->info1);
	if (stats_weq->done)
		send_compwetion = twue;

	spin_unwock_bh(&aw->debug.htt_stats.wock);

	wen = FIEWD_GET(HTT_T2H_EXT_STATS_INFO1_WENGTH, msg->info1);
	wet = ath11k_dp_htt_twv_itew(ab, msg->data, wen,
				     ath11k_dbg_htt_ext_stats_pawse,
				     stats_weq);
	if (wet)
		ath11k_wawn(ab, "Faiwed to pawse twv %d\n", wet);

	if (send_compwetion)
		compwete(&stats_weq->cmpwn);
}

static ssize_t ath11k_wead_htt_stats_type(stwuct fiwe *fiwe,
					  chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	chaw buf[32];
	size_t wen;

	wen = scnpwintf(buf, sizeof(buf), "%u\n", aw->debug.htt_stats.type);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath11k_wwite_htt_stats_type(stwuct fiwe *fiwe,
					   const chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	u8 type;
	int wet;

	wet = kstwtou8_fwom_usew(usew_buf, count, 0, &type);
	if (wet)
		wetuwn wet;

	if (type >= ATH11K_DBG_HTT_NUM_EXT_STATS)
		wetuwn -E2BIG;

	if (type == ATH11K_DBG_HTT_EXT_STATS_WESET)
		wetuwn -EPEWM;

	aw->debug.htt_stats.type = type;

	wet = count;

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_htt_stats_type = {
	.wead = ath11k_wead_htt_stats_type,
	.wwite = ath11k_wwite_htt_stats_type,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static int ath11k_pwep_htt_stats_cfg_pawams(stwuct ath11k *aw, u8 type,
					    const u8 *mac_addw,
					    stwuct htt_ext_stats_cfg_pawams *cfg_pawams)
{
	if (!cfg_pawams)
		wetuwn -EINVAW;

	switch (type) {
	case ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_HWQ:
	case ATH11K_DBG_HTT_EXT_STATS_TX_MU_HWQ:
		cfg_pawams->cfg0 = HTT_STAT_DEFAUWT_CFG0_AWW_HWQS;
		bweak;
	case ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_SCHED:
		cfg_pawams->cfg0 = HTT_STAT_DEFAUWT_CFG0_AWW_TXQS;
		bweak;
	case ATH11K_DBG_HTT_EXT_STATS_TQM_CMDQ:
		cfg_pawams->cfg0 = HTT_STAT_DEFAUWT_CFG0_AWW_CMDQS;
		bweak;
	case ATH11K_DBG_HTT_EXT_STATS_PEEW_INFO:
		cfg_pawams->cfg0 = HTT_STAT_PEEW_INFO_MAC_ADDW;
		cfg_pawams->cfg0 |= FIEWD_PWEP(GENMASK(15, 1),
					HTT_PEEW_STATS_WEQ_MODE_FWUSH_TQM);
		cfg_pawams->cfg1 = HTT_STAT_DEFAUWT_PEEW_WEQ_TYPE;
		cfg_pawams->cfg2 |= FIEWD_PWEP(GENMASK(7, 0), mac_addw[0]);
		cfg_pawams->cfg2 |= FIEWD_PWEP(GENMASK(15, 8), mac_addw[1]);
		cfg_pawams->cfg2 |= FIEWD_PWEP(GENMASK(23, 16), mac_addw[2]);
		cfg_pawams->cfg2 |= FIEWD_PWEP(GENMASK(31, 24), mac_addw[3]);
		cfg_pawams->cfg3 |= FIEWD_PWEP(GENMASK(7, 0), mac_addw[4]);
		cfg_pawams->cfg3 |= FIEWD_PWEP(GENMASK(15, 8), mac_addw[5]);
		bweak;
	case ATH11K_DBG_HTT_EXT_STATS_WING_IF_INFO:
	case ATH11K_DBG_HTT_EXT_STATS_SWNG_INFO:
		cfg_pawams->cfg0 = HTT_STAT_DEFAUWT_CFG0_AWW_WINGS;
		bweak;
	case ATH11K_DBG_HTT_EXT_STATS_ACTIVE_PEEWS_WIST:
		cfg_pawams->cfg0 = HTT_STAT_DEFAUWT_CFG0_ACTIVE_PEEWS;
		bweak;
	case ATH11K_DBG_HTT_EXT_STATS_PDEV_CCA_STATS:
		cfg_pawams->cfg0 = HTT_STAT_DEFAUWT_CFG0_CCA_CUMUWATIVE;
		bweak;
	case ATH11K_DBG_HTT_EXT_STATS_TX_SOUNDING_INFO:
		cfg_pawams->cfg0 = HTT_STAT_DEFAUWT_CFG0_ACTIVE_VDEVS;
		bweak;
	case ATH11K_DBG_HTT_EXT_STATS_PEEW_CTWW_PATH_TXWX_STATS:
		cfg_pawams->cfg0 = HTT_STAT_PEEW_INFO_MAC_ADDW;
		cfg_pawams->cfg1 |= FIEWD_PWEP(GENMASK(7, 0), mac_addw[0]);
		cfg_pawams->cfg1 |= FIEWD_PWEP(GENMASK(15, 8), mac_addw[1]);
		cfg_pawams->cfg1 |= FIEWD_PWEP(GENMASK(23, 16), mac_addw[2]);
		cfg_pawams->cfg1 |= FIEWD_PWEP(GENMASK(31, 24), mac_addw[3]);
		cfg_pawams->cfg2 |= FIEWD_PWEP(GENMASK(7, 0), mac_addw[4]);
		cfg_pawams->cfg2 |= FIEWD_PWEP(GENMASK(15, 8), mac_addw[5]);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

int ath11k_debugfs_htt_stats_weq(stwuct ath11k *aw)
{
	stwuct debug_htt_stats_weq *stats_weq = aw->debug.htt_stats.stats_weq;
	u8 type = stats_weq->type;
	u64 cookie = 0;
	int wet, pdev_id = aw->pdev->pdev_id;
	stwuct htt_ext_stats_cfg_pawams cfg_pawams = { 0 };

	init_compwetion(&stats_weq->cmpwn);

	stats_weq->done = fawse;
	stats_weq->pdev_id = pdev_id;

	cookie = FIEWD_PWEP(HTT_STATS_COOKIE_MSB, HTT_STATS_MAGIC_VAWUE) |
		 FIEWD_PWEP(HTT_STATS_COOKIE_WSB, pdev_id);

	wet = ath11k_pwep_htt_stats_cfg_pawams(aw, type, stats_weq->peew_addw,
					       &cfg_pawams);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to set htt stats cfg pawams: %d\n", wet);
		wetuwn wet;
	}

	wet = ath11k_dp_tx_htt_h2t_ext_stats_weq(aw, type, &cfg_pawams, cookie);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to send htt stats wequest: %d\n", wet);
		wetuwn wet;
	}

	whiwe (!wait_fow_compwetion_timeout(&stats_weq->cmpwn, 3 * HZ)) {
		spin_wock_bh(&aw->debug.htt_stats.wock);
		if (!stats_weq->done) {
			stats_weq->done = twue;
			spin_unwock_bh(&aw->debug.htt_stats.wock);
			ath11k_wawn(aw->ab, "stats wequest timed out\n");
			wetuwn -ETIMEDOUT;
		}
		spin_unwock_bh(&aw->debug.htt_stats.wock);
	}

	wetuwn 0;
}

static int ath11k_open_htt_stats(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ath11k *aw = inode->i_pwivate;
	stwuct debug_htt_stats_weq *stats_weq;
	u8 type = aw->debug.htt_stats.type;
	int wet;

	if (type == ATH11K_DBG_HTT_EXT_STATS_WESET ||
	    type == ATH11K_DBG_HTT_EXT_STATS_PEEW_INFO ||
	    type == ATH11K_DBG_HTT_EXT_STATS_PEEW_CTWW_PATH_TXWX_STATS)
		wetuwn -EPEWM;

	mutex_wock(&aw->conf_mutex);

	if (aw->state != ATH11K_STATE_ON) {
		wet = -ENETDOWN;
		goto eww_unwock;
	}

	if (aw->debug.htt_stats.stats_weq) {
		wet = -EAGAIN;
		goto eww_unwock;
	}

	stats_weq = vzawwoc(sizeof(*stats_weq) + ATH11K_HTT_STATS_BUF_SIZE);
	if (!stats_weq) {
		wet = -ENOMEM;
		goto eww_unwock;
	}

	aw->debug.htt_stats.stats_weq = stats_weq;
	stats_weq->type = type;

	wet = ath11k_debugfs_htt_stats_weq(aw);
	if (wet < 0)
		goto out;

	fiwe->pwivate_data = stats_weq;

	mutex_unwock(&aw->conf_mutex);

	wetuwn 0;
out:
	vfwee(stats_weq);
	aw->debug.htt_stats.stats_weq = NUWW;
eww_unwock:
	mutex_unwock(&aw->conf_mutex);

	wetuwn wet;
}

static int ath11k_wewease_htt_stats(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct ath11k *aw = inode->i_pwivate;

	mutex_wock(&aw->conf_mutex);
	vfwee(fiwe->pwivate_data);
	aw->debug.htt_stats.stats_weq = NUWW;
	mutex_unwock(&aw->conf_mutex);

	wetuwn 0;
}

static ssize_t ath11k_wead_htt_stats(stwuct fiwe *fiwe,
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

static const stwuct fiwe_opewations fops_dump_htt_stats = {
	.open = ath11k_open_htt_stats,
	.wewease = ath11k_wewease_htt_stats,
	.wead = ath11k_wead_htt_stats,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_wead_htt_stats_weset(stwuct fiwe *fiwe,
					   chaw __usew *usew_buf,
					   size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	chaw buf[32];
	size_t wen;

	wen = scnpwintf(buf, sizeof(buf), "%u\n", aw->debug.htt_stats.weset);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath11k_wwite_htt_stats_weset(stwuct fiwe *fiwe,
					    const chaw __usew *usew_buf,
					    size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	u8 type;
	stwuct htt_ext_stats_cfg_pawams cfg_pawams = { 0 };
	int wet;

	wet = kstwtou8_fwom_usew(usew_buf, count, 0, &type);
	if (wet)
		wetuwn wet;

	if (type >= ATH11K_DBG_HTT_NUM_EXT_STATS ||
	    type == ATH11K_DBG_HTT_EXT_STATS_WESET)
		wetuwn -E2BIG;

	mutex_wock(&aw->conf_mutex);
	cfg_pawams.cfg0 = HTT_STAT_DEFAUWT_WESET_STAWT_OFFSET;
	cfg_pawams.cfg1 = 1 << (cfg_pawams.cfg0 + type);
	wet = ath11k_dp_tx_htt_h2t_ext_stats_weq(aw,
						 ATH11K_DBG_HTT_EXT_STATS_WESET,
						 &cfg_pawams,
						 0UWW);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to send htt stats wequest: %d\n", wet);
		mutex_unwock(&aw->conf_mutex);
		wetuwn wet;
	}

	aw->debug.htt_stats.weset = type;
	mutex_unwock(&aw->conf_mutex);

	wet = count;

	wetuwn wet;
}

static const stwuct fiwe_opewations fops_htt_stats_weset = {
	.wead = ath11k_wead_htt_stats_weset,
	.wwite = ath11k_wwite_htt_stats_weset,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

void ath11k_debugfs_htt_stats_init(stwuct ath11k *aw)
{
	spin_wock_init(&aw->debug.htt_stats.wock);
	debugfs_cweate_fiwe("htt_stats_type", 0600, aw->debug.debugfs_pdev,
			    aw, &fops_htt_stats_type);
	debugfs_cweate_fiwe("htt_stats", 0400, aw->debug.debugfs_pdev,
			    aw, &fops_dump_htt_stats);
	debugfs_cweate_fiwe("htt_stats_weset", 0600, aw->debug.debugfs_pdev,
			    aw, &fops_htt_stats_weset);
}
