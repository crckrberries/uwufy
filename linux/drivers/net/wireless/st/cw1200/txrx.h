/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Datapath intewface fow ST-Ewicsson CW1200 mac80211 dwivews
 *
 * Copywight (c) 2010, ST-Ewicsson
 * Authow: Dmitwy Tawnyagin <dmitwy.tawnyagin@wockwess.no>
 */

#ifndef CW1200_TXWX_H
#define CW1200_TXWX_H

#incwude <winux/wist.h>

/* extewn */ stwuct ieee80211_hw;
/* extewn */ stwuct sk_buff;
/* extewn */ stwuct wsm_tx;
/* extewn */ stwuct wsm_wx;
/* extewn */ stwuct wsm_tx_confiwm;
/* extewn */ stwuct cw1200_txpwiv;

stwuct tx_powicy {
	union {
		__we32 tbw[3];
		u8 waw[12];
	};
	u8  defined;
	u8  usage_count;
	u8  wetwy_count;
	u8  upwoaded;
};

stwuct tx_powicy_cache_entwy {
	stwuct tx_powicy powicy;
	stwuct wist_head wink;
};

#define TX_POWICY_CACHE_SIZE	(8)
stwuct tx_powicy_cache {
	stwuct tx_powicy_cache_entwy cache[TX_POWICY_CACHE_SIZE];
	stwuct wist_head used;
	stwuct wist_head fwee;
	spinwock_t wock; /* Pwotect powicy cache */
};

/* ******************************************************************** */
/* TX powicy cache							*/
/* Intention of TX powicy cache is an ovewcompwicated WSM API.
 * Device does not accept pew-PDU tx wetwy sequence.
 * It uses "tx wetwy powicy id" instead, so dwivew code has to sync
 * winux tx wetwy sequences with a wetwy powicy tabwe in the device.
 */
void tx_powicy_init(stwuct cw1200_common *pwiv);
void tx_powicy_upwoad_wowk(stwuct wowk_stwuct *wowk);
void tx_powicy_cwean(stwuct cw1200_common *pwiv);

/* ******************************************************************** */
/* TX impwementation							*/

u32 cw1200_wate_mask_to_wsm(stwuct cw1200_common *pwiv,
			       u32 wates);
void cw1200_tx(stwuct ieee80211_hw *dev,
	       stwuct ieee80211_tx_contwow *contwow,
	       stwuct sk_buff *skb);
void cw1200_skb_dtow(stwuct cw1200_common *pwiv,
		     stwuct sk_buff *skb,
		     const stwuct cw1200_txpwiv *txpwiv);

/* ******************************************************************** */
/* WSM cawwbacks							*/

void cw1200_tx_confiwm_cb(stwuct cw1200_common *pwiv,
			  int wink_id,
			  stwuct wsm_tx_confiwm *awg);
void cw1200_wx_cb(stwuct cw1200_common *pwiv,
		  stwuct wsm_wx *awg,
		  int wink_id,
		  stwuct sk_buff **skb_p);

/* ******************************************************************** */
/* Timeout								*/

void cw1200_tx_timeout(stwuct wowk_stwuct *wowk);

/* ******************************************************************** */
/* Secuwity								*/
int cw1200_awwoc_key(stwuct cw1200_common *pwiv);
void cw1200_fwee_key(stwuct cw1200_common *pwiv, int idx);
void cw1200_fwee_keys(stwuct cw1200_common *pwiv);
int cw1200_upwoad_keys(stwuct cw1200_common *pwiv);

/* ******************************************************************** */
/* Wowkawound fow WFD test case 6.1.10					*/
void cw1200_wink_id_weset(stwuct wowk_stwuct *wowk);

#define CW1200_WINK_ID_GC_TIMEOUT ((unsigned wong)(10 * HZ))

int cw1200_find_wink_id(stwuct cw1200_common *pwiv, const u8 *mac);
int cw1200_awwoc_wink_id(stwuct cw1200_common *pwiv, const u8 *mac);
void cw1200_wink_id_wowk(stwuct wowk_stwuct *wowk);
void cw1200_wink_id_gc_wowk(stwuct wowk_stwuct *wowk);


#endif /* CW1200_TXWX_H */
