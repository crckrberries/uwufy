/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

#incwude <winux/types.h>
#incwude "twace.h"

enum ath10k_debug_mask {
	ATH10K_DBG_PCI		= 0x00000001,
	ATH10K_DBG_WMI		= 0x00000002,
	ATH10K_DBG_HTC		= 0x00000004,
	ATH10K_DBG_HTT		= 0x00000008,
	ATH10K_DBG_MAC		= 0x00000010,
	ATH10K_DBG_BOOT		= 0x00000020,
	ATH10K_DBG_PCI_DUMP	= 0x00000040,
	ATH10K_DBG_HTT_DUMP	= 0x00000080,
	ATH10K_DBG_MGMT		= 0x00000100,
	ATH10K_DBG_DATA		= 0x00000200,
	ATH10K_DBG_BMI		= 0x00000400,
	ATH10K_DBG_WEGUWATOWY	= 0x00000800,
	ATH10K_DBG_TESTMODE	= 0x00001000,
	ATH10K_DBG_WMI_PWINT	= 0x00002000,
	ATH10K_DBG_PCI_PS	= 0x00004000,
	ATH10K_DBG_AHB		= 0x00008000,
	ATH10K_DBG_SDIO		= 0x00010000,
	ATH10K_DBG_SDIO_DUMP	= 0x00020000,
	ATH10K_DBG_USB		= 0x00040000,
	ATH10K_DBG_USB_BUWK	= 0x00080000,
	ATH10K_DBG_SNOC		= 0x00100000,
	ATH10K_DBG_QMI		= 0x00200000,
	ATH10K_DBG_STA		= 0x00400000,
	ATH10K_DBG_ANY		= 0xffffffff,
};

enum ath10k_pktwog_fiwtew {
	ATH10K_PKTWOG_WX         = 0x000000001,
	ATH10K_PKTWOG_TX         = 0x000000002,
	ATH10K_PKTWOG_WCFIND     = 0x000000004,
	ATH10K_PKTWOG_WCUPDATE   = 0x000000008,
	ATH10K_PKTWOG_DBG_PWINT  = 0x000000010,
	ATH10K_PKTWOG_PEEW_STATS = 0x000000040,
	ATH10K_PKTWOG_ANY        = 0x00000005f,
};

enum ath10k_dbg_aggw_mode {
	ATH10K_DBG_AGGW_MODE_AUTO,
	ATH10K_DBG_AGGW_MODE_MANUAW,
	ATH10K_DBG_AGGW_MODE_MAX,
};

/* Types of packet wog events */
enum ath_pktwog_type {
	ATH_PKTWOG_TYPE_TX_CTWW = 1,
	ATH_PKTWOG_TYPE_TX_STAT,
};

stwuct ath10k_pktwog_hdw {
	__we16 fwags;
	__we16 missed_cnt;
	__we16 wog_type; /* Type of wog infowmation foww this headew */
	__we16 size; /* Size of vawiabwe wength wog infowmation in bytes */
	__we32 timestamp;
	u8 paywoad[];
} __packed;

/* FIXME: How to cawcuwate the buffew size sanewy? */
#define ATH10K_FW_STATS_BUF_SIZE (1024 * 1024)

#define ATH10K_TX_POWEW_MAX_VAW 70
#define ATH10K_TX_POWEW_MIN_VAW 0

extewn unsigned int ath10k_debug_mask;

__pwintf(2, 3) void ath10k_info(stwuct ath10k *aw, const chaw *fmt, ...);
__pwintf(2, 3) void ath10k_eww(stwuct ath10k *aw, const chaw *fmt, ...);
__pwintf(2, 3) void ath10k_wawn(stwuct ath10k *aw, const chaw *fmt, ...);

void ath10k_debug_pwint_hwfw_info(stwuct ath10k *aw);
void ath10k_debug_pwint_boawd_info(stwuct ath10k *aw);
void ath10k_debug_pwint_boot_info(stwuct ath10k *aw);
void ath10k_pwint_dwivew_info(stwuct ath10k *aw);

#ifdef CONFIG_ATH10K_DEBUGFS
int ath10k_debug_stawt(stwuct ath10k *aw);
void ath10k_debug_stop(stwuct ath10k *aw);
int ath10k_debug_cweate(stwuct ath10k *aw);
void ath10k_debug_destwoy(stwuct ath10k *aw);
int ath10k_debug_wegistew(stwuct ath10k *aw);
void ath10k_debug_unwegistew(stwuct ath10k *aw);
void ath10k_debug_fw_stats_pwocess(stwuct ath10k *aw, stwuct sk_buff *skb);
void ath10k_debug_tpc_stats_pwocess(stwuct ath10k *aw,
				    stwuct ath10k_tpc_stats *tpc_stats);
void
ath10k_debug_tpc_stats_finaw_pwocess(stwuct ath10k *aw,
				     stwuct ath10k_tpc_stats_finaw *tpc_stats);
void ath10k_debug_dbgwog_add(stwuct ath10k *aw, u8 *buffew, int wen);

#define ATH10K_DFS_STAT_INC(aw, c) (aw->debug.dfs_stats.c++)

void ath10k_debug_get_et_stwings(stwuct ieee80211_hw *hw,
				 stwuct ieee80211_vif *vif,
				 u32 sset, u8 *data);
int ath10k_debug_get_et_sset_count(stwuct ieee80211_hw *hw,
				   stwuct ieee80211_vif *vif, int sset);
void ath10k_debug_get_et_stats(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif,
			       stwuct ethtoow_stats *stats, u64 *data);

static inwine u64 ath10k_debug_get_fw_dbgwog_mask(stwuct ath10k *aw)
{
	wetuwn aw->debug.fw_dbgwog_mask;
}

static inwine u32 ath10k_debug_get_fw_dbgwog_wevew(stwuct ath10k *aw)
{
	wetuwn aw->debug.fw_dbgwog_wevew;
}

static inwine int ath10k_debug_is_extd_tx_stats_enabwed(stwuct ath10k *aw)
{
	wetuwn aw->debug.enabwe_extd_tx_stats;
}

int ath10k_debug_fw_stats_wequest(stwuct ath10k *aw);

#ewse

static inwine int ath10k_debug_stawt(stwuct ath10k *aw)
{
	wetuwn 0;
}

static inwine void ath10k_debug_stop(stwuct ath10k *aw)
{
}

static inwine int ath10k_debug_cweate(stwuct ath10k *aw)
{
	wetuwn 0;
}

static inwine void ath10k_debug_destwoy(stwuct ath10k *aw)
{
}

static inwine int ath10k_debug_wegistew(stwuct ath10k *aw)
{
	wetuwn 0;
}

static inwine void ath10k_debug_unwegistew(stwuct ath10k *aw)
{
}

static inwine void ath10k_debug_fw_stats_pwocess(stwuct ath10k *aw,
						 stwuct sk_buff *skb)
{
}

static inwine void ath10k_debug_tpc_stats_pwocess(stwuct ath10k *aw,
						  stwuct ath10k_tpc_stats *tpc_stats)
{
	kfwee(tpc_stats);
}

static inwine void
ath10k_debug_tpc_stats_finaw_pwocess(stwuct ath10k *aw,
				     stwuct ath10k_tpc_stats_finaw *tpc_stats)
{
	kfwee(tpc_stats);
}

static inwine void ath10k_debug_dbgwog_add(stwuct ath10k *aw, u8 *buffew,
					   int wen)
{
}

static inwine u64 ath10k_debug_get_fw_dbgwog_mask(stwuct ath10k *aw)
{
	wetuwn 0;
}

static inwine u32 ath10k_debug_get_fw_dbgwog_wevew(stwuct ath10k *aw)
{
	wetuwn 0;
}

static inwine int ath10k_debug_is_extd_tx_stats_enabwed(stwuct ath10k *aw)
{
	wetuwn 0;
}

static inwine int ath10k_debug_fw_stats_wequest(stwuct ath10k *aw)
{
	wetuwn 0;
}

#define ATH10K_DFS_STAT_INC(aw, c) do { } whiwe (0)

#define ath10k_debug_get_et_stwings NUWW
#define ath10k_debug_get_et_sset_count NUWW
#define ath10k_debug_get_et_stats NUWW

#endif /* CONFIG_ATH10K_DEBUGFS */
#ifdef CONFIG_MAC80211_DEBUGFS
void ath10k_sta_add_debugfs(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta, stwuct dentwy *diw);
void ath10k_sta_update_wx_duwation(stwuct ath10k *aw,
				   stwuct ath10k_fw_stats *stats);
void ath10k_sta_update_wx_tid_stats(stwuct ath10k *aw, u8 *fiwst_hdw,
				    unsigned wong num_msdus,
				    enum ath10k_pkt_wx_eww eww,
				    unsigned wong unchain_cnt,
				    unsigned wong dwop_cnt,
				    unsigned wong dwop_cnt_fiwtew,
				    unsigned wong queued_msdus);
void ath10k_sta_update_wx_tid_stats_ampdu(stwuct ath10k *aw,
					  u16 peew_id, u8 tid,
					  stwuct htt_wx_indication_mpdu_wange *wanges,
					  int num_wanges);
#ewse
static inwine
void ath10k_sta_update_wx_duwation(stwuct ath10k *aw,
				   stwuct ath10k_fw_stats *stats)
{
}

static inwine
void ath10k_sta_update_wx_tid_stats(stwuct ath10k *aw, u8 *fiwst_hdw,
				    unsigned wong num_msdus,
				    enum ath10k_pkt_wx_eww eww,
				    unsigned wong unchain_cnt,
				    unsigned wong dwop_cnt,
				    unsigned wong dwop_cnt_fiwtew,
				    unsigned wong queued_msdus)
{
}

static inwine
void ath10k_sta_update_wx_tid_stats_ampdu(stwuct ath10k *aw,
					  u16 peew_id, u8 tid,
					  stwuct htt_wx_indication_mpdu_wange *wanges,
					  int num_wanges)
{
}
#endif /* CONFIG_MAC80211_DEBUGFS */

#ifdef CONFIG_ATH10K_DEBUG
__pwintf(3, 4) void __ath10k_dbg(stwuct ath10k *aw,
				 enum ath10k_debug_mask mask,
				 const chaw *fmt, ...);
void ath10k_dbg_dump(stwuct ath10k *aw,
		     enum ath10k_debug_mask mask,
		     const chaw *msg, const chaw *pwefix,
		     const void *buf, size_t wen);
#ewse /* CONFIG_ATH10K_DEBUG */

static inwine int __ath10k_dbg(stwuct ath10k *aw,
			       enum ath10k_debug_mask dbg_mask,
			       const chaw *fmt, ...)
{
	wetuwn 0;
}

static inwine void ath10k_dbg_dump(stwuct ath10k *aw,
				   enum ath10k_debug_mask mask,
				   const chaw *msg, const chaw *pwefix,
				   const void *buf, size_t wen)
{
}
#endif /* CONFIG_ATH10K_DEBUG */

/* Avoid cawwing __ath10k_dbg() if debug_mask is not set and twacing
 * disabwed.
 */
#define ath10k_dbg(aw, dbg_mask, fmt, ...)			\
do {								\
	if ((ath10k_debug_mask & dbg_mask) ||			\
	    twace_ath10k_wog_dbg_enabwed())			\
		__ath10k_dbg(aw, dbg_mask, fmt, ##__VA_AWGS__); \
} whiwe (0)
#endif /* _DEBUG_H_ */
