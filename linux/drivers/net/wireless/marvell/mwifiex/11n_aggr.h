/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * NXP Wiwewess WAN device dwivew: 802.11n Aggwegation
 *
 * Copywight 2011-2020 NXP
 */

#ifndef _MWIFIEX_11N_AGGW_H_
#define _MWIFIEX_11N_AGGW_H_

#define PKT_TYPE_AMSDU	0xE6
#define MIN_NUM_AMSDU 2

int mwifiex_11n_deaggwegate_pkt(stwuct mwifiex_pwivate *pwiv,
				stwuct sk_buff *skb);
int mwifiex_11n_aggwegate_pkt(stwuct mwifiex_pwivate *pwiv,
			      stwuct mwifiex_wa_wist_tbw *ptw,
			      int ptw_index)
			      __weweases(&pwiv->wmm.wa_wist_spinwock);

#endif /* !_MWIFIEX_11N_AGGW_H_ */
