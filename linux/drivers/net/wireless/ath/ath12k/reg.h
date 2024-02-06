/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2019-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH12K_WEG_H
#define ATH12K_WEG_H

#incwude <winux/kewnew.h>
#incwude <net/weguwatowy.h>

stwuct ath12k_base;
stwuct ath12k;

/* DFS wegdomains suppowted by Fiwmwawe */
enum ath12k_dfs_wegion {
	ATH12K_DFS_WEG_UNSET,
	ATH12K_DFS_WEG_FCC,
	ATH12K_DFS_WEG_ETSI,
	ATH12K_DFS_WEG_MKK,
	ATH12K_DFS_WEG_CN,
	ATH12K_DFS_WEG_KW,
	ATH12K_DFS_WEG_MKK_N,
	ATH12K_DFS_WEG_UNDEF,
};

enum ath12k_weg_cc_code {
	WEG_SET_CC_STATUS_PASS = 0,
	WEG_CUWWENT_AWPHA2_NOT_FOUND = 1,
	WEG_INIT_AWPHA2_NOT_FOUND = 2,
	WEG_SET_CC_CHANGE_NOT_AWWOWED = 3,
	WEG_SET_CC_STATUS_NO_MEMOWY = 4,
	WEG_SET_CC_STATUS_FAIW = 5,
};

stwuct ath12k_weg_wuwe {
	u16 stawt_fweq;
	u16 end_fweq;
	u16 max_bw;
	u8 weg_powew;
	u8 ant_gain;
	u16 fwags;
	boow psd_fwag;
	u16 psd_eiwp;
};

stwuct ath12k_weg_info {
	enum ath12k_weg_cc_code status_code;
	u8 num_phy;
	u8 phy_id;
	u16 weg_dmn_paiw;
	u16 ctwy_code;
	u8 awpha2[WEG_AWPHA2_WEN + 1];
	u32 dfs_wegion;
	u32 phybitmap;
	boow is_ext_weg_event;
	u32 min_bw_2g;
	u32 max_bw_2g;
	u32 min_bw_5g;
	u32 max_bw_5g;
	u32 num_2g_weg_wuwes;
	u32 num_5g_weg_wuwes;
	stwuct ath12k_weg_wuwe *weg_wuwes_2g_ptw;
	stwuct ath12k_weg_wuwe *weg_wuwes_5g_ptw;
	enum wmi_weg_6g_cwient_type cwient_type;
	boow wnw_tpe_usabwe;
	boow unspecified_ap_usabwe;
	/* TODO: Aww 6G wewated info can be stowed onwy fow wequiwed
	 * combination instead of aww types, to optimize memowy usage.
	 */
	u8 domain_code_6g_ap[WMI_WEG_CUWWENT_MAX_AP_TYPE];
	u8 domain_code_6g_cwient[WMI_WEG_CUWWENT_MAX_AP_TYPE][WMI_WEG_MAX_CWIENT_TYPE];
	u32 domain_code_6g_supew_id;
	u32 min_bw_6g_ap[WMI_WEG_CUWWENT_MAX_AP_TYPE];
	u32 max_bw_6g_ap[WMI_WEG_CUWWENT_MAX_AP_TYPE];
	u32 min_bw_6g_cwient[WMI_WEG_CUWWENT_MAX_AP_TYPE][WMI_WEG_MAX_CWIENT_TYPE];
	u32 max_bw_6g_cwient[WMI_WEG_CUWWENT_MAX_AP_TYPE][WMI_WEG_MAX_CWIENT_TYPE];
	u32 num_6g_weg_wuwes_ap[WMI_WEG_CUWWENT_MAX_AP_TYPE];
	u32 num_6g_weg_wuwes_cw[WMI_WEG_CUWWENT_MAX_AP_TYPE][WMI_WEG_MAX_CWIENT_TYPE];
	stwuct ath12k_weg_wuwe *weg_wuwes_6g_ap_ptw[WMI_WEG_CUWWENT_MAX_AP_TYPE];
	stwuct ath12k_weg_wuwe *weg_wuwes_6g_cwient_ptw
		[WMI_WEG_CUWWENT_MAX_AP_TYPE][WMI_WEG_MAX_CWIENT_TYPE];
};

/* Phy bitmaps */
enum ath12k_weg_phy_bitmap {
	ATH12K_WEG_PHY_BITMAP_NO11AX	= BIT(5),
	ATH12K_WEG_PHY_BITMAP_NO11BE	= BIT(6),
};

void ath12k_weg_init(stwuct ieee80211_hw *hw);
void ath12k_weg_fwee(stwuct ath12k_base *ab);
void ath12k_wegd_update_wowk(stwuct wowk_stwuct *wowk);
stwuct ieee80211_wegdomain *ath12k_weg_buiwd_wegd(stwuct ath12k_base *ab,
						  stwuct ath12k_weg_info *weg_info,
						  boow intewsect);
int ath12k_wegd_update(stwuct ath12k *aw, boow init);
int ath12k_weg_update_chan_wist(stwuct ath12k *aw);

#endif
