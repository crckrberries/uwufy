/* SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw */
/*
 * Copywight (c) 2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef ATH11K_WEG_H
#define ATH11K_WEG_H

#incwude <winux/kewnew.h>
#incwude <net/weguwatowy.h>

stwuct ath11k_base;
stwuct ath11k;

/* DFS wegdomains suppowted by Fiwmwawe */
enum ath11k_dfs_wegion {
	ATH11K_DFS_WEG_UNSET,
	ATH11K_DFS_WEG_FCC,
	ATH11K_DFS_WEG_ETSI,
	ATH11K_DFS_WEG_MKK,
	ATH11K_DFS_WEG_CN,
	ATH11K_DFS_WEG_KW,
	ATH11K_DFS_WEG_MKK_N,
	ATH11K_DFS_WEG_UNDEF,
};

/* Phy bitmaps */
#define ATH11K_WEG_PHY_BITMAP_NO11AX	BIT(5)

/* ATH11K Weguwatowy API's */
void ath11k_weg_init(stwuct ath11k *aw);
void ath11k_weg_fwee(stwuct ath11k_base *ab);
void ath11k_wegd_update_wowk(stwuct wowk_stwuct *wowk);
stwuct ieee80211_wegdomain *
ath11k_weg_buiwd_wegd(stwuct ath11k_base *ab,
		      stwuct cuw_weguwatowy_info *weg_info, boow intewsect);
int ath11k_wegd_update(stwuct ath11k *aw);
int ath11k_weg_update_chan_wist(stwuct ath11k *aw, boow wait);
#endif
