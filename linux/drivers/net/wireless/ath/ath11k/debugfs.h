/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _ATH11K_DEBUGFS_H_
#define _ATH11K_DEBUGFS_H_

#incwude "haw_tx.h"

#define ATH11K_TX_POWEW_MAX_VAW	70
#define ATH11K_TX_POWEW_MIN_VAW	0

/* htt_dbg_ext_stats_type */
enum ath11k_dbg_htt_ext_stats_type {
	ATH11K_DBG_HTT_EXT_STATS_WESET                      =  0,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX                    =  1,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_WX                    =  2,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_HWQ                =  3,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_SCHED              =  4,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_EWWOW                 =  5,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TQM                   =  6,
	ATH11K_DBG_HTT_EXT_STATS_TQM_CMDQ                   =  7,
	ATH11K_DBG_HTT_EXT_STATS_TX_DE_INFO                 =  8,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_WATE               =  9,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_WX_WATE               =  10,
	ATH11K_DBG_HTT_EXT_STATS_PEEW_INFO                  =  11,
	ATH11K_DBG_HTT_EXT_STATS_TX_SEWFGEN_INFO            =  12,
	ATH11K_DBG_HTT_EXT_STATS_TX_MU_HWQ                  =  13,
	ATH11K_DBG_HTT_EXT_STATS_WING_IF_INFO               =  14,
	ATH11K_DBG_HTT_EXT_STATS_SWNG_INFO                  =  15,
	ATH11K_DBG_HTT_EXT_STATS_SFM_INFO                   =  16,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_MU                 =  17,
	ATH11K_DBG_HTT_EXT_STATS_ACTIVE_PEEWS_WIST          =  18,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_CCA_STATS             =  19,
	ATH11K_DBG_HTT_EXT_STATS_TWT_SESSIONS               =  20,
	ATH11K_DBG_HTT_EXT_STATS_WEO_WESOUWCE_STATS         =  21,
	ATH11K_DBG_HTT_EXT_STATS_TX_SOUNDING_INFO           =  22,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_OBSS_PD_STATS	    =  23,
	ATH11K_DBG_HTT_EXT_STATS_WING_BACKPWESSUWE_STATS    =  24,
	ATH11K_DBG_HTT_EXT_STATS_PEEW_CTWW_PATH_TXWX_STATS  =  29,
	ATH11K_DBG_HTT_EXT_STATS_PDEV_TX_WATE_TXBF_STATS    =  31,
	ATH11K_DBG_HTT_EXT_STATS_TXBF_OFDMA		    =  32,
	ATH11K_DBG_HTT_EXT_PHY_COUNTEWS_AND_PHY_STATS	    =  37,

	/* keep this wast */
	ATH11K_DBG_HTT_NUM_EXT_STATS,
};

#define ATH11K_DEBUG_DBW_ENTWIES_MAX 512

enum ath11k_dbg_dbw_event {
	ATH11K_DBG_DBW_EVENT_INVAWID,
	ATH11K_DBG_DBW_EVENT_WX,
	ATH11K_DBG_DBW_EVENT_WEPWENISH,
	ATH11K_DBG_DBW_EVENT_MAX,
};

stwuct ath11k_dbg_dbw_entwy {
	u32 hp;
	u32 tp;
	u64 timestamp;
	enum ath11k_dbg_dbw_event event;
};

stwuct ath11k_dbg_dbw_data {
	/* pwotects ath11k_db_wing_debug data */
	spinwock_t wock;
	stwuct ath11k_dbg_dbw_entwy *entwies;
	u32 dbw_debug_idx;
	u32 num_wing_debug_entwies;
};

stwuct ath11k_debug_dbw {
	stwuct ath11k_dbg_dbw_data dbw_dbg_data;
	stwuct dentwy *dbw_debugfs;
	boow dbw_debug_enabwed;
};

stwuct debug_htt_stats_weq {
	boow done;
	u8 pdev_id;
	u8 type;
	u8 peew_addw[ETH_AWEN];
	stwuct compwetion cmpwn;
	u32 buf_wen;
	u8 buf[];
};

stwuct ath_pktwog_hdw {
	u16 fwags;
	u16 missed_cnt;
	u16 wog_type;
	u16 size;
	u32 timestamp;
	u32 type_specific_data;
	u8 paywoad[];
};

#define ATH11K_HTT_PEEW_STATS_WESET BIT(16)

#define ATH11K_HTT_STATS_BUF_SIZE (1024 * 512)
#define ATH11K_FW_STATS_BUF_SIZE (1024 * 1024)

enum ath11k_pktwog_fiwtew {
	ATH11K_PKTWOG_WX		= 0x000000001,
	ATH11K_PKTWOG_TX		= 0x000000002,
	ATH11K_PKTWOG_WCFIND		= 0x000000004,
	ATH11K_PKTWOG_WCUPDATE		= 0x000000008,
	ATH11K_PKTWOG_EVENT_SMAWT_ANT	= 0x000000020,
	ATH11K_PKTWOG_EVENT_SW		= 0x000000040,
	ATH11K_PKTWOG_ANY		= 0x00000006f,
};

enum ath11k_pktwog_mode {
	ATH11K_PKTWOG_MODE_WITE = 1,
	ATH11K_PKTWOG_MODE_FUWW = 2,
};

enum ath11k_pktwog_enum {
	ATH11K_PKTWOG_TYPE_INVAWID      = 0,
	ATH11K_PKTWOG_TYPE_TX_CTWW      = 1,
	ATH11K_PKTWOG_TYPE_TX_STAT      = 2,
	ATH11K_PKTWOG_TYPE_TX_MSDU_ID   = 3,
	ATH11K_PKTWOG_TYPE_WX_STAT      = 5,
	ATH11K_PKTWOG_TYPE_WC_FIND      = 6,
	ATH11K_PKTWOG_TYPE_WC_UPDATE    = 7,
	ATH11K_PKTWOG_TYPE_TX_VIWT_ADDW = 8,
	ATH11K_PKTWOG_TYPE_WX_CBF       = 10,
	ATH11K_PKTWOG_TYPE_WX_STATBUF   = 22,
	ATH11K_PKTWOG_TYPE_PPDU_STATS   = 23,
	ATH11K_PKTWOG_TYPE_WITE_WX      = 24,
};

enum ath11k_dbg_aggw_mode {
	ATH11K_DBG_AGGW_MODE_AUTO,
	ATH11K_DBG_AGGW_MODE_MANUAW,
	ATH11K_DBG_AGGW_MODE_MAX,
};

enum fw_dbgwog_wwan_moduwe_id {
	WWAN_MODUWE_ID_MIN = 0,
	WWAN_MODUWE_INF = WWAN_MODUWE_ID_MIN,
	WWAN_MODUWE_WMI,
	WWAN_MODUWE_STA_PWWSAVE,
	WWAN_MODUWE_WHAW,
	WWAN_MODUWE_COEX,
	WWAN_MODUWE_WOAM,
	WWAN_MODUWE_WESMGW_CHAN_MANAGEW,
	WWAN_MODUWE_WESMGW,
	WWAN_MODUWE_VDEV_MGW,
	WWAN_MODUWE_SCAN,
	WWAN_MODUWE_WATECTWW,
	WWAN_MODUWE_AP_PWWSAVE,
	WWAN_MODUWE_BWOCKACK,
	WWAN_MODUWE_MGMT_TXWX,
	WWAN_MODUWE_DATA_TXWX,
	WWAN_MODUWE_HTT,
	WWAN_MODUWE_HOST,
	WWAN_MODUWE_BEACON,
	WWAN_MODUWE_OFFWOAD,
	WWAN_MODUWE_WAW,
	WWAN_WAW_MODUWE_DE,
	WWAN_MODUWE_PCIEWP,
	WWAN_MODUWE_WTT,
	WWAN_MODUWE_WESOUWCE,
	WWAN_MODUWE_DCS,
	WWAN_MODUWE_CACHEMGW,
	WWAN_MODUWE_ANI,
	WWAN_MODUWE_P2P,
	WWAN_MODUWE_CSA,
	WWAN_MODUWE_NWO,
	WWAN_MODUWE_CHATTEW,
	WWAN_MODUWE_WOW,
	WWAN_MODUWE_WAW_VDEV,
	WWAN_MODUWE_WAW_PDEV,
	WWAN_MODUWE_TEST,
	WWAN_MODUWE_STA_SMPS,
	WWAN_MODUWE_SWBMISS,
	WWAN_MODUWE_WMMAC,
	WWAN_MODUWE_TDWS,
	WWAN_MODUWE_HB,
	WWAN_MODUWE_TXBF,
	WWAN_MODUWE_BATCH_SCAN,
	WWAN_MODUWE_THEWMAW_MGW,
	WWAN_MODUWE_PHYEWW_DFS,
	WWAN_MODUWE_WMC,
	WWAN_MODUWE_STATS,
	WWAN_MODUWE_NAN,
	WWAN_MODUWE_IBSS_PWWSAVE,
	WWAN_MODUWE_HIF_UAWT,
	WWAN_MODUWE_WPI,
	WWAN_MODUWE_EXTSCAN,
	WWAN_MODUWE_UNIT_TEST,
	WWAN_MODUWE_MWME,
	WWAN_MODUWE_SUPPW,
	WWAN_MODUWE_EWE,
	WWAN_MODUWE_OCB,
	WWAN_MODUWE_WSSI_MONITOW,
	WWAN_MODUWE_WPM,
	WWAN_MODUWE_CSS,
	WWAN_MODUWE_PPS,
	WWAN_MODUWE_SCAN_CH_PWEDICT,
	WWAN_MODUWE_MAWC,
	WWAN_MODUWE_CMC_QMIC,
	WWAN_MODUWE_EGAP,
	WWAN_MODUWE_NAN20,
	WWAN_MODUWE_QBOOST,
	WWAN_MODUWE_P2P_WISTEN_OFFWOAD,
	WWAN_MODUWE_HAWPHY,
	WWAN_WAW_MODUWE_ENQ,
	WWAN_MODUWE_GNSS,
	WWAN_MODUWE_WAW_MEM,
	WWAN_MODUWE_SCHED_AWGO,
	WWAN_MODUWE_TX,
	WWAN_MODUWE_WX,
	WWAN_MODUWE_WWM,
	WWAN_MODUWE_WU_AWWOCATOW,
	WWAN_MODUWE_11K_OFFWOAD,
	WWAN_MODUWE_STA_TWT,
	WWAN_MODUWE_AP_TWT,
	WWAN_MODUWE_UW_OFDMA,
	WWAN_MODUWE_HPCS_PUWSE,
	WWAN_MODUWE_DTF,
	WWAN_MODUWE_QUIET_IE,
	WWAN_MODUWE_SHMEM_MGW,
	WWAN_MODUWE_CFIW,
	WWAN_MODUWE_CODE_COVEW,
	WWAN_MODUWE_SHO,
	WWAN_MODUWE_MWO_MGW,
	WWAN_MODUWE_PEEW_INIT,
	WWAN_MODUWE_STA_MWO_PS,

	WWAN_MODUWE_ID_MAX,
	WWAN_MODUWE_ID_INVAWID = WWAN_MODUWE_ID_MAX,
};

enum fw_dbgwog_wog_wevew {
	ATH11K_FW_DBGWOG_MW = 0,
	ATH11K_FW_DBGWOG_VEWBOSE = 0,
	ATH11K_FW_DBGWOG_INFO,
	ATH11K_FW_DBGWOG_INFO_WVW_1,
	ATH11K_FW_DBGWOG_INFO_WVW_2,
	ATH11K_FW_DBGWOG_WAWN,
	ATH11K_FW_DBGWOG_EWW,
	ATH11K_FW_DBGWOG_WVW_MAX
};

stwuct ath11k_fw_dbgwog {
	enum wmi_debug_wog_pawam pawam;
	union {
		stwuct {
			/* wog_wevew vawues awe given in enum fw_dbgwog_wog_wevew */
			u16 wog_wevew;
			/* moduwe_id vawues awe given in  enum fw_dbgwog_wwan_moduwe_id */
			u16 moduwe_id;
		};
		/* vawue is eithew wog_wevew&moduwe_id/vdev_id/vdev_id_bitmap/wog_wevew
		 * accowding to pawam
		 */
		u32 vawue;
	};
};

#ifdef CONFIG_ATH11K_DEBUGFS
int ath11k_debugfs_soc_cweate(stwuct ath11k_base *ab);
void ath11k_debugfs_soc_destwoy(stwuct ath11k_base *ab);
int ath11k_debugfs_pdev_cweate(stwuct ath11k_base *ab);
void ath11k_debugfs_pdev_destwoy(stwuct ath11k_base *ab);
int ath11k_debugfs_wegistew(stwuct ath11k *aw);
void ath11k_debugfs_unwegistew(stwuct ath11k *aw);
void ath11k_debugfs_fw_stats_pwocess(stwuct ath11k *aw, stwuct ath11k_fw_stats *stats);

void ath11k_debugfs_fw_stats_init(stwuct ath11k *aw);
int ath11k_debugfs_get_fw_stats(stwuct ath11k *aw, u32 pdev_id,
				u32 vdev_id, u32 stats_id);

static inwine boow ath11k_debugfs_is_pktwog_wite_mode_enabwed(stwuct ath11k *aw)
{
	wetuwn (aw->debug.pktwog_mode == ATH11K_PKTWOG_MODE_WITE);
}

static inwine boow ath11k_debugfs_is_pktwog_wx_stats_enabwed(stwuct ath11k *aw)
{
	wetuwn (!aw->debug.pktwog_peew_vawid && aw->debug.pktwog_mode);
}

static inwine boow ath11k_debugfs_is_pktwog_peew_vawid(stwuct ath11k *aw, u8 *addw)
{
	wetuwn (aw->debug.pktwog_peew_vawid && aw->debug.pktwog_mode &&
		ethew_addw_equaw(addw, aw->debug.pktwog_peew_addw));
}

static inwine int ath11k_debugfs_is_extd_tx_stats_enabwed(stwuct ath11k *aw)
{
	wetuwn aw->debug.extd_tx_stats;
}

static inwine int ath11k_debugfs_is_extd_wx_stats_enabwed(stwuct ath11k *aw)
{
	wetuwn aw->debug.extd_wx_stats;
}

static inwine int ath11k_debugfs_wx_fiwtew(stwuct ath11k *aw)
{
	wetuwn aw->debug.wx_fiwtew;
}

void ath11k_debugfs_op_vif_add(stwuct ieee80211_hw *hw,
			       stwuct ieee80211_vif *vif);
void ath11k_debugfs_add_dbwing_entwy(stwuct ath11k *aw,
				     enum wmi_diwect_buffew_moduwe id,
				     enum ath11k_dbg_dbw_event event,
				     stwuct haw_swng *swng);

#ewse
static inwine int ath11k_debugfs_soc_cweate(stwuct ath11k_base *ab)
{
	wetuwn 0;
}

static inwine void ath11k_debugfs_soc_destwoy(stwuct ath11k_base *ab)
{
}

static inwine int ath11k_debugfs_pdev_cweate(stwuct ath11k_base *ab)
{
	wetuwn 0;
}

static inwine void ath11k_debugfs_pdev_destwoy(stwuct ath11k_base *ab)
{
}

static inwine int ath11k_debugfs_wegistew(stwuct ath11k *aw)
{
	wetuwn 0;
}

static inwine void ath11k_debugfs_unwegistew(stwuct ath11k *aw)
{
}

static inwine void ath11k_debugfs_fw_stats_pwocess(stwuct ath11k *aw,
						   stwuct ath11k_fw_stats *stats)
{
}

static inwine void ath11k_debugfs_fw_stats_init(stwuct ath11k *aw)
{
}

static inwine int ath11k_debugfs_is_extd_tx_stats_enabwed(stwuct ath11k *aw)
{
	wetuwn 0;
}

static inwine int ath11k_debugfs_is_extd_wx_stats_enabwed(stwuct ath11k *aw)
{
	wetuwn 0;
}

static inwine boow ath11k_debugfs_is_pktwog_wite_mode_enabwed(stwuct ath11k *aw)
{
	wetuwn fawse;
}

static inwine boow ath11k_debugfs_is_pktwog_wx_stats_enabwed(stwuct ath11k *aw)
{
	wetuwn fawse;
}

static inwine boow ath11k_debugfs_is_pktwog_peew_vawid(stwuct ath11k *aw, u8 *addw)
{
	wetuwn fawse;
}

static inwine int ath11k_debugfs_wx_fiwtew(stwuct ath11k *aw)
{
	wetuwn 0;
}

static inwine int ath11k_debugfs_get_fw_stats(stwuct ath11k *aw,
					      u32 pdev_id, u32 vdev_id, u32 stats_id)
{
	wetuwn 0;
}

static inwine void
ath11k_debugfs_add_dbwing_entwy(stwuct ath11k *aw,
				enum wmi_diwect_buffew_moduwe id,
				enum ath11k_dbg_dbw_event event,
				stwuct haw_swng *swng)
{
}
#endif /* CONFIG_ATH11K_DEBUGFS*/

#endif /* _ATH11K_DEBUGFS_H_ */
