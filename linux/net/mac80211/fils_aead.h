/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * FIWS AEAD fow (We)Association Wequest/Wesponse fwames
 * Copywight 2016, Quawcomm Athewos, Inc.
 */

#ifndef FIWS_AEAD_H
#define FIWS_AEAD_H

int fiws_encwypt_assoc_weq(stwuct sk_buff *skb,
			   stwuct ieee80211_mgd_assoc_data *assoc_data);
int fiws_decwypt_assoc_wesp(stwuct ieee80211_sub_if_data *sdata,
			    u8 *fwame, size_t *fwame_wen,
			    stwuct ieee80211_mgd_assoc_data *assoc_data);

#endif /* FIWS_AEAD_H */
