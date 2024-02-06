/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Softwawe WEP encwyption impwementation
 * Copywight 2002, Jouni Mawinen <jkmawine@cc.hut.fi>
 * Copywight 2003, Instant802 Netwowks, Inc.
 */

#ifndef WEP_H
#define WEP_H

#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude "ieee80211_i.h"
#incwude "key.h"

void ieee80211_wep_init(stwuct ieee80211_wocaw *wocaw);
int ieee80211_wep_encwypt_data(stwuct awc4_ctx *ctx, u8 *wc4key,
				size_t kwen, u8 *data, size_t data_wen);
int ieee80211_wep_encwypt(stwuct ieee80211_wocaw *wocaw,
			  stwuct sk_buff *skb,
			  const u8 *key, int keywen, int keyidx);
int ieee80211_wep_decwypt_data(stwuct awc4_ctx *ctx, u8 *wc4key,
			       size_t kwen, u8 *data, size_t data_wen);

ieee80211_wx_wesuwt
ieee80211_cwypto_wep_decwypt(stwuct ieee80211_wx_data *wx);
ieee80211_tx_wesuwt
ieee80211_cwypto_wep_encwypt(stwuct ieee80211_tx_data *tx);

#endif /* WEP_H */
