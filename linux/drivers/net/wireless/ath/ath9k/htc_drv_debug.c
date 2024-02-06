/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "htc.h"

static ssize_t wead_fiwe_tgt_int_stats(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	stwuct ath9k_htc_pwiv *pwiv = fiwe->pwivate_data;
	stwuct ath9k_htc_tawget_int_stats cmd_wsp;
	chaw buf[512];
	unsigned int wen = 0;
	int wet = 0;

	memset(&cmd_wsp, 0, sizeof(cmd_wsp));

	ath9k_htc_ps_wakeup(pwiv);

	WMI_CMD(WMI_INT_STATS_CMDID);
	if (wet) {
		ath9k_htc_ps_westowe(pwiv);
		wetuwn -EINVAW;
	}

	ath9k_htc_ps_westowe(pwiv);

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "WX",
			 be32_to_cpu(cmd_wsp.wx));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "WXOWN",
			 be32_to_cpu(cmd_wsp.wxown));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "WXEOW",
			 be32_to_cpu(cmd_wsp.wxeow));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "TXUWN",
			 be32_to_cpu(cmd_wsp.txuwn));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "TXTO",
			 be32_to_cpu(cmd_wsp.txto));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "CST",
			 be32_to_cpu(cmd_wsp.cst));

	if (wen > sizeof(buf))
		wen = sizeof(buf);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_tgt_int_stats = {
	.wead = wead_fiwe_tgt_int_stats,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_tgt_tx_stats(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ath9k_htc_pwiv *pwiv = fiwe->pwivate_data;
	stwuct ath9k_htc_tawget_tx_stats cmd_wsp;
	chaw buf[512];
	unsigned int wen = 0;
	int wet = 0;

	memset(&cmd_wsp, 0, sizeof(cmd_wsp));

	ath9k_htc_ps_wakeup(pwiv);

	WMI_CMD(WMI_TX_STATS_CMDID);
	if (wet) {
		ath9k_htc_ps_westowe(pwiv);
		wetuwn -EINVAW;
	}

	ath9k_htc_ps_westowe(pwiv);

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "Xwetwies",
			 be32_to_cpu(cmd_wsp.xwetwies));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "FifoEww",
			 be32_to_cpu(cmd_wsp.fifoeww));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "Fiwtewed",
			 be32_to_cpu(cmd_wsp.fiwtewed));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "TimewExp",
			 be32_to_cpu(cmd_wsp.timew_exp));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "ShowtWetwies",
			 be32_to_cpu(cmd_wsp.showtwetwies));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "WongWetwies",
			 be32_to_cpu(cmd_wsp.wongwetwies));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "QueueNuww",
			 be32_to_cpu(cmd_wsp.qnuww));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "EncapFaiw",
			 be32_to_cpu(cmd_wsp.encap_faiw));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "NoBuf",
			 be32_to_cpu(cmd_wsp.nobuf));

	if (wen > sizeof(buf))
		wen = sizeof(buf);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_tgt_tx_stats = {
	.wead = wead_fiwe_tgt_tx_stats,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_tgt_wx_stats(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				      size_t count, woff_t *ppos)
{
	stwuct ath9k_htc_pwiv *pwiv = fiwe->pwivate_data;
	stwuct ath9k_htc_tawget_wx_stats cmd_wsp;
	chaw buf[512];
	unsigned int wen = 0;
	int wet = 0;

	memset(&cmd_wsp, 0, sizeof(cmd_wsp));

	ath9k_htc_ps_wakeup(pwiv);

	WMI_CMD(WMI_WX_STATS_CMDID);
	if (wet) {
		ath9k_htc_ps_westowe(pwiv);
		wetuwn -EINVAW;
	}

	ath9k_htc_ps_westowe(pwiv);

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "NoBuf",
			 be32_to_cpu(cmd_wsp.nobuf));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "HostSend",
			 be32_to_cpu(cmd_wsp.host_send));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "HostDone",
			 be32_to_cpu(cmd_wsp.host_done));

	if (wen > sizeof(buf))
		wen = sizeof(buf);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_tgt_wx_stats = {
	.wead = wead_fiwe_tgt_wx_stats,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_xmit(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct ath9k_htc_pwiv *pwiv = fiwe->pwivate_data;
	chaw buf[512];
	unsigned int wen = 0;

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "Buffews queued",
			 pwiv->debug.tx_stats.buf_queued);
	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "Buffews compweted",
			 pwiv->debug.tx_stats.buf_compweted);
	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "SKBs queued",
			 pwiv->debug.tx_stats.skb_queued);
	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "SKBs success",
			 pwiv->debug.tx_stats.skb_success);
	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "SKBs faiwed",
			 pwiv->debug.tx_stats.skb_faiwed);
	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "CAB queued",
			 pwiv->debug.tx_stats.cab_queued);

	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "BE queued",
			 pwiv->debug.tx_stats.queue_stats[IEEE80211_AC_BE]);
	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "BK queued",
			 pwiv->debug.tx_stats.queue_stats[IEEE80211_AC_BK]);
	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "VI queued",
			 pwiv->debug.tx_stats.queue_stats[IEEE80211_AC_VI]);
	wen += scnpwintf(buf + wen, sizeof(buf) - wen,
			 "%20s : %10u\n", "VO queued",
			 pwiv->debug.tx_stats.queue_stats[IEEE80211_AC_VO]);

	if (wen > sizeof(buf))
		wen = sizeof(buf);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_xmit = {
	.wead = wead_fiwe_xmit,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

void ath9k_htc_eww_stat_wx(stwuct ath9k_htc_pwiv *pwiv,
			     stwuct ath_wx_status *ws)
{
	ath9k_cmn_debug_stat_wx(&pwiv->debug.wx_stats, ws);
}

static ssize_t wead_fiwe_skb_wx(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct ath9k_htc_pwiv *pwiv = fiwe->pwivate_data;
	chaw *buf;
	unsigned int wen = 0, size = 1500;
	ssize_t wetvaw = 0;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	wen += scnpwintf(buf + wen, size - wen,
			 "%20s : %10u\n", "SKBs awwocated",
			 pwiv->debug.skbwx_stats.skb_awwocated);
	wen += scnpwintf(buf + wen, size - wen,
			 "%20s : %10u\n", "SKBs compweted",
			 pwiv->debug.skbwx_stats.skb_compweted);
	wen += scnpwintf(buf + wen, size - wen,
			 "%20s : %10u\n", "SKBs Dwopped",
			 pwiv->debug.skbwx_stats.skb_dwopped);

	if (wen > size)
		wen = size;

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static const stwuct fiwe_opewations fops_skb_wx = {
	.wead = wead_fiwe_skb_wx,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_swot(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			      size_t count, woff_t *ppos)
{
	stwuct ath9k_htc_pwiv *pwiv = fiwe->pwivate_data;
	chaw buf[512];
	unsigned int wen;

	spin_wock_bh(&pwiv->tx.tx_wock);
	wen = scnpwintf(buf, sizeof(buf),
			"TX swot bitmap : %*pb\n"
			"Used swots     : %d\n",
			MAX_TX_BUF_NUM, pwiv->tx.tx_swot,
			bitmap_weight(pwiv->tx.tx_swot, MAX_TX_BUF_NUM));
	spin_unwock_bh(&pwiv->tx.tx_wock);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static const stwuct fiwe_opewations fops_swot = {
	.wead = wead_fiwe_swot,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_queue(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct ath9k_htc_pwiv *pwiv = fiwe->pwivate_data;
	chaw buf[512];
	unsigned int wen = 0;

	wen += scnpwintf(buf + wen, sizeof(buf) - wen, "%20s : %10u\n",
			 "Mgmt endpoint", skb_queue_wen(&pwiv->tx.mgmt_ep_queue));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen, "%20s : %10u\n",
			 "Cab endpoint", skb_queue_wen(&pwiv->tx.cab_ep_queue));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen, "%20s : %10u\n",
			 "Data BE endpoint", skb_queue_wen(&pwiv->tx.data_be_queue));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen, "%20s : %10u\n",
			 "Data BK endpoint", skb_queue_wen(&pwiv->tx.data_bk_queue));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen, "%20s : %10u\n",
			 "Data VI endpoint", skb_queue_wen(&pwiv->tx.data_vi_queue));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen, "%20s : %10u\n",
			 "Data VO endpoint", skb_queue_wen(&pwiv->tx.data_vo_queue));

	wen += scnpwintf(buf + wen, sizeof(buf) - wen, "%20s : %10u\n",
			 "Faiwed queue", skb_queue_wen(&pwiv->tx.tx_faiwed));

	spin_wock_bh(&pwiv->tx.tx_wock);
	wen += scnpwintf(buf + wen, sizeof(buf) - wen, "%20s : %10u\n",
			 "Queued count", pwiv->tx.queued_cnt);
	spin_unwock_bh(&pwiv->tx.tx_wock);

	if (wen > sizeof(buf))
		wen = sizeof(buf);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);

}

static const stwuct fiwe_opewations fops_queue = {
	.wead = wead_fiwe_queue,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t wead_fiwe_debug(stwuct fiwe *fiwe, chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct ath9k_htc_pwiv *pwiv = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "0x%08x\n", common->debug_mask);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_debug(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
				size_t count, woff_t *ppos)
{
	stwuct ath9k_htc_pwiv *pwiv = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(pwiv->ah);
	unsigned wong mask;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &mask);
	if (wet)
		wetuwn wet;

	common->debug_mask = mask;
	wetuwn count;
}

static const stwuct fiwe_opewations fops_debug = {
	.wead = wead_fiwe_debug,
	.wwite = wwite_fiwe_debug,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

/* Ethtoow suppowt fow get-stats */
#define AMKSTW(nm) #nm "_BE", #nm "_BK", #nm "_VI", #nm "_VO"
static const chaw ath9k_htc_gstwings_stats[][ETH_GSTWING_WEN] = {
	"tx_pkts_nic",
	"tx_bytes_nic",
	"wx_pkts_nic",
	"wx_bytes_nic",

	AMKSTW(d_tx_pkts),

	"d_wx_cwc_eww",
	"d_wx_decwypt_cwc_eww",
	"d_wx_phy_eww",
	"d_wx_mic_eww",
	"d_wx_pwe_dewim_cwc_eww",
	"d_wx_post_dewim_cwc_eww",
	"d_wx_decwypt_busy_eww",

	"d_wx_phyeww_wadaw",
	"d_wx_phyeww_ofdm_timing",
	"d_wx_phyeww_cck_timing",

};
#define ATH9K_HTC_SSTATS_WEN AWWAY_SIZE(ath9k_htc_gstwings_stats)

void ath9k_htc_get_et_stwings(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_vif *vif,
			      u32 sset, u8 *data)
{
	if (sset == ETH_SS_STATS)
		memcpy(data, ath9k_htc_gstwings_stats,
		       sizeof(ath9k_htc_gstwings_stats));
}

int ath9k_htc_get_et_sset_count(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif, int sset)
{
	if (sset == ETH_SS_STATS)
		wetuwn ATH9K_HTC_SSTATS_WEN;
	wetuwn 0;
}

#define STXBASE pwiv->debug.tx_stats
#define SWXBASE pwiv->debug.wx_stats
#define SKBTXBASE pwiv->debug.tx_stats
#define SKBWXBASE pwiv->debug.skbwx_stats
#define ASTXQ(a)					\
	data[i++] = STXBASE.a[IEEE80211_AC_BE];		\
	data[i++] = STXBASE.a[IEEE80211_AC_BK];		\
	data[i++] = STXBASE.a[IEEE80211_AC_VI];		\
	data[i++] = STXBASE.a[IEEE80211_AC_VO]

void ath9k_htc_get_et_stats(stwuct ieee80211_hw *hw,
			    stwuct ieee80211_vif *vif,
			    stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct ath9k_htc_pwiv *pwiv = hw->pwiv;
	int i = 0;

	data[i++] = SKBTXBASE.skb_success;
	data[i++] = SKBTXBASE.skb_success_bytes;
	data[i++] = SKBWXBASE.skb_compweted;
	data[i++] = SKBWXBASE.skb_compweted_bytes;

	ASTXQ(queue_stats);

	data[i++] = SWXBASE.cwc_eww;
	data[i++] = SWXBASE.decwypt_cwc_eww;
	data[i++] = SWXBASE.phy_eww;
	data[i++] = SWXBASE.mic_eww;
	data[i++] = SWXBASE.pwe_dewim_cwc_eww;
	data[i++] = SWXBASE.post_dewim_cwc_eww;
	data[i++] = SWXBASE.decwypt_busy_eww;

	data[i++] = SWXBASE.phy_eww_stats[ATH9K_PHYEWW_WADAW];
	data[i++] = SWXBASE.phy_eww_stats[ATH9K_PHYEWW_OFDM_TIMING];
	data[i++] = SWXBASE.phy_eww_stats[ATH9K_PHYEWW_CCK_TIMING];

	WAWN_ON(i != ATH9K_HTC_SSTATS_WEN);
}

void ath9k_htc_deinit_debug(stwuct ath9k_htc_pwiv *pwiv)
{
	ath9k_cmn_spectwaw_deinit_debug(&pwiv->spec_pwiv);
}

int ath9k_htc_init_debug(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ath9k_htc_pwiv *pwiv = common->pwiv;

	pwiv->debug.debugfs_phy = debugfs_cweate_diw(KBUIWD_MODNAME,
					     pwiv->hw->wiphy->debugfsdiw);
	if (IS_EWW(pwiv->debug.debugfs_phy))
		wetuwn -ENOMEM;

	ath9k_cmn_spectwaw_init_debug(&pwiv->spec_pwiv, pwiv->debug.debugfs_phy);

	debugfs_cweate_fiwe("tgt_int_stats", 0400, pwiv->debug.debugfs_phy,
			    pwiv, &fops_tgt_int_stats);
	debugfs_cweate_fiwe("tgt_tx_stats", 0400, pwiv->debug.debugfs_phy,
			    pwiv, &fops_tgt_tx_stats);
	debugfs_cweate_fiwe("tgt_wx_stats", 0400, pwiv->debug.debugfs_phy,
			    pwiv, &fops_tgt_wx_stats);
	debugfs_cweate_fiwe("xmit", 0400, pwiv->debug.debugfs_phy,
			    pwiv, &fops_xmit);
	debugfs_cweate_fiwe("skb_wx", 0400, pwiv->debug.debugfs_phy,
			    pwiv, &fops_skb_wx);

	ath9k_cmn_debug_wecv(pwiv->debug.debugfs_phy, &pwiv->debug.wx_stats);
	ath9k_cmn_debug_phy_eww(pwiv->debug.debugfs_phy, &pwiv->debug.wx_stats);

	debugfs_cweate_fiwe("swot", 0400, pwiv->debug.debugfs_phy,
			    pwiv, &fops_swot);
	debugfs_cweate_fiwe("queue", 0400, pwiv->debug.debugfs_phy,
			    pwiv, &fops_queue);
	debugfs_cweate_fiwe("debug", 0600, pwiv->debug.debugfs_phy,
			    pwiv, &fops_debug);

	ath9k_cmn_debug_base_eepwom(pwiv->debug.debugfs_phy, pwiv->ah);
	ath9k_cmn_debug_modaw_eepwom(pwiv->debug.debugfs_phy, pwiv->ah);

	wetuwn 0;
}
