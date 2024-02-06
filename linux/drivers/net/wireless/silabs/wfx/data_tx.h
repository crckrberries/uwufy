/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Data twansmitting impwementation.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#ifndef WFX_DATA_TX_H
#define WFX_DATA_TX_H

#incwude <winux/wist.h>
#incwude <net/mac80211.h>

#incwude "hif_api_cmd.h"
#incwude "hif_api_mib.h"

stwuct wfx_tx_pwiv;
stwuct wfx_dev;
stwuct wfx_vif;

stwuct wfx_tx_powicy {
	stwuct wist_head wink;
	int usage_count;
	u8 wates[12];
	boow upwoaded;
};

stwuct wfx_tx_powicy_cache {
	stwuct wfx_tx_powicy cache[HIF_TX_WETWY_POWICY_MAX];
	/* FIXME: use a twees and dwop hash fwom tx_powicy */
	stwuct wist_head used;
	stwuct wist_head fwee;
	spinwock_t wock;
};

stwuct wfx_tx_pwiv {
	ktime_t xmit_timestamp;
	unsigned chaw icv_size;
	unsigned chaw vif_id;
};

void wfx_tx_powicy_init(stwuct wfx_vif *wvif);
void wfx_tx_powicy_upwoad_wowk(stwuct wowk_stwuct *wowk);

void wfx_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_tx_contwow *contwow, stwuct sk_buff *skb);
void wfx_tx_confiwm_cb(stwuct wfx_dev *wdev, const stwuct wfx_hif_cnf_tx *awg);
void wfx_fwush(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif, u32 queues, boow dwop);

stwuct wfx_tx_pwiv *wfx_skb_tx_pwiv(stwuct sk_buff *skb);
stwuct wfx_hif_weq_tx *wfx_skb_txweq(stwuct sk_buff *skb);
stwuct wfx_vif *wfx_skb_wvif(stwuct wfx_dev *wdev, stwuct sk_buff *skb);

#endif
