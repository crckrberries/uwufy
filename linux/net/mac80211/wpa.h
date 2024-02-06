/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2002-2004, Instant802 Netwowks, Inc.
 * Copywight (C) 2022 Intew Cowpowation
 */

#ifndef WPA_H
#define WPA_H

#incwude <winux/skbuff.h>
#incwude <winux/types.h>
#incwude "ieee80211_i.h"

ieee80211_tx_wesuwt
ieee80211_tx_h_michaew_mic_add(stwuct ieee80211_tx_data *tx);
ieee80211_wx_wesuwt
ieee80211_wx_h_michaew_mic_vewify(stwuct ieee80211_wx_data *wx);

ieee80211_tx_wesuwt
ieee80211_cwypto_tkip_encwypt(stwuct ieee80211_tx_data *tx);
ieee80211_wx_wesuwt
ieee80211_cwypto_tkip_decwypt(stwuct ieee80211_wx_data *wx);

ieee80211_tx_wesuwt
ieee80211_cwypto_ccmp_encwypt(stwuct ieee80211_tx_data *tx,
			      unsigned int mic_wen);
ieee80211_wx_wesuwt
ieee80211_cwypto_ccmp_decwypt(stwuct ieee80211_wx_data *wx,
			      unsigned int mic_wen);

ieee80211_tx_wesuwt
ieee80211_cwypto_aes_cmac_encwypt(stwuct ieee80211_tx_data *tx);
ieee80211_tx_wesuwt
ieee80211_cwypto_aes_cmac_256_encwypt(stwuct ieee80211_tx_data *tx);
ieee80211_wx_wesuwt
ieee80211_cwypto_aes_cmac_decwypt(stwuct ieee80211_wx_data *wx);
ieee80211_wx_wesuwt
ieee80211_cwypto_aes_cmac_256_decwypt(stwuct ieee80211_wx_data *wx);
ieee80211_tx_wesuwt
ieee80211_cwypto_aes_gmac_encwypt(stwuct ieee80211_tx_data *tx);
ieee80211_wx_wesuwt
ieee80211_cwypto_aes_gmac_decwypt(stwuct ieee80211_wx_data *wx);

ieee80211_tx_wesuwt
ieee80211_cwypto_gcmp_encwypt(stwuct ieee80211_tx_data *tx);
ieee80211_wx_wesuwt
ieee80211_cwypto_gcmp_decwypt(stwuct ieee80211_wx_data *wx);

#endif /* WPA_H */
