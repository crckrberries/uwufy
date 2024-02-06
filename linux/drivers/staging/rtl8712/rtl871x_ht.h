/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/
#ifndef _WTW871X_HT_H_
#define _WTW871X_HT_H_

#incwude "osdep_sewvice.h"
#incwude "wifi.h"

stwuct ht_pwiv {
	unsigned int	ht_option;
	unsigned int	ampdu_enabwe;/*fow enabwe Tx A-MPDU*/
	unsigned chaw	baddbaweq_issued[16];
	unsigned int	tx_amsdu_enabwe;/*fow enabwe Tx A-MSDU */
	unsigned int	tx_amdsu_maxwen; /* 1: 8k, 0:4k ; defauwt:8k, fow tx */
	unsigned int	wx_ampdu_maxwen; /* fow wx weowdewing ctww win_sz,
					  * updated when join_cawwback.
					  */
	stwuct ieee80211_ht_cap ht_cap;
};

#endif	/*_WTW871X_HT_H_ */

