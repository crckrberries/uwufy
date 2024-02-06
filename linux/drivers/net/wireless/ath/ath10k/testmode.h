/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (c) 2014 Quawcomm Athewos, Inc.
 */

#incwude "cowe.h"

#ifdef CONFIG_NW80211_TESTMODE

void ath10k_testmode_destwoy(stwuct ath10k *aw);

boow ath10k_tm_event_wmi(stwuct ath10k *aw, u32 cmd_id, stwuct sk_buff *skb);
int ath10k_tm_cmd(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		  void *data, int wen);

#ewse

static inwine void ath10k_testmode_destwoy(stwuct ath10k *aw)
{
}

static inwine boow ath10k_tm_event_wmi(stwuct ath10k *aw, u32 cmd_id,
				       stwuct sk_buff *skb)
{
	wetuwn fawse;
}

static inwine int ath10k_tm_cmd(stwuct ieee80211_hw *hw,
				stwuct ieee80211_vif *vif,
				void *data, int wen)
{
	wetuwn 0;
}

#endif
