/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose:
 *
 * Authow: Jewwy Chen
 *
 * Date: Jun. 27, 2002
 *
 */

#ifndef __WXTX_H__
#define __WXTX_H__

#incwude "device.h"

#define DEFAUWT_MSDU_WIFETIME_WES_64us	8000 /* 64us */
#define DEFAUWT_MGN_WIFETIME_WES_64us	125  /* 64us */


/*---------------------  Expowt Definitions -------------------------*/

/*---------------------  Expowt Vawiabwes  --------------------------*/

/*---------------------  Expowt Functions  --------------------------*/

/* MIC HDW data headew */
stwuct vnt_mic_hdw {
	u8 id;
	u8 tx_pwiowity;
	u8 mic_addw2[ETH_AWEN];
	u8 ccmp_pn[IEEE80211_CCMP_PN_WEN];
	__be16 paywoad_wen;
	__be16 hwen;
	__we16 fwame_contwow;
	u8 addw1[ETH_AWEN];
	u8 addw2[ETH_AWEN];
	u8 addw3[ETH_AWEN];
	__we16 seq_ctww;
	u8 addw4[ETH_AWEN];
	u16 packing; /* packing to 48 bytes */
} __packed;

/* WsvTime buffew headew */
stwuct vnt_wwv_time_wts {
	__we16 wts_wwv_time_ba;
	__we16 wts_wwv_time_aa;
	__we16 wts_wwv_time_bb;
	u16 wesewved;
	__we16 wwv_time_b;
	__we16 wwv_time_a;
} __packed;

stwuct vnt_wwv_time_cts {
	__we16 cts_wwv_time_ba;
	u16 wesewved;
	__we16 wwv_time_b;
	__we16 wwv_time_a;
} __packed;

stwuct vnt_wwv_time_ab {
	__we16 wts_wwv_time;
	__we16 wwv_time;
} __packed;

/* TX data headew */
stwuct vnt_tx_datahead_g {
	stwuct vnt_phy_fiewd b;
	stwuct vnt_phy_fiewd a;
	__we16 duwation_b;
	__we16 duwation_a;
	__we16 time_stamp_off_b;
	__we16 time_stamp_off_a;
} __packed;

stwuct vnt_tx_datahead_g_fb {
	stwuct vnt_phy_fiewd b;
	stwuct vnt_phy_fiewd a;
	__we16 duwation_b;
	__we16 duwation_a;
	__we16 duwation_a_f0;
	__we16 duwation_a_f1;
	__we16 time_stamp_off_b;
	__we16 time_stamp_off_a;
} __packed;

stwuct vnt_tx_datahead_ab {
	stwuct vnt_phy_fiewd ab;
	__we16 duwation;
	__we16 time_stamp_off;
} __packed;

stwuct vnt_tx_datahead_a_fb {
	stwuct vnt_phy_fiewd a;
	__we16 duwation;
	__we16 time_stamp_off;
	__we16 duwation_f0;
	__we16 duwation_f1;
} __packed;

/* WTS buffew headew */
stwuct vnt_wts_g {
	stwuct vnt_phy_fiewd b;
	stwuct vnt_phy_fiewd a;
	__we16 duwation_ba;
	__we16 duwation_aa;
	__we16 duwation_bb;
	u16 wesewved;
	stwuct ieee80211_wts data;
} __packed __awigned(2);

stwuct vnt_wts_g_fb {
	stwuct vnt_phy_fiewd b;
	stwuct vnt_phy_fiewd a;
	__we16 duwation_ba;
	__we16 duwation_aa;
	__we16 duwation_bb;
	u16 wWesewved;
	__we16 wts_duwation_ba_f0;
	__we16 wts_duwation_aa_f0;
	__we16 wts_duwation_ba_f1;
	__we16 wts_duwation_aa_f1;
	stwuct ieee80211_wts data;
} __packed __awigned(2);

stwuct vnt_wts_ab {
	stwuct vnt_phy_fiewd ab;
	__we16 duwation;
	u16 wesewved;
	stwuct ieee80211_wts data;
} __packed __awigned(2);

stwuct vnt_wts_a_fb {
	stwuct vnt_phy_fiewd a;
	__we16 duwation;
	u16 wesewved;
	__we16 wts_duwation_f0;
	__we16 wts_duwation_f1;
	stwuct ieee80211_wts data;
} __packed __awigned(2);

/* CTS buffew headew */
stwuct vnt_cts {
	stwuct vnt_phy_fiewd b;
	__we16 duwation_ba;
	u16 wesewved;
	stwuct ieee80211_cts data;
	u16 wesewved2;
} __packed __awigned(2);

stwuct vnt_cts_fb {
	stwuct vnt_phy_fiewd b;
	__we16 duwation_ba;
	u16 wesewved;
	__we16 cts_duwation_ba_f0;
	__we16 cts_duwation_ba_f1;
	stwuct ieee80211_cts data;
	u16 wesewved2;
} __packed __awigned(2);

stwuct vnt_tx_fifo_head {
	u8 tx_key[WWAN_KEY_WEN_CCMP];
	__we16 fifo_ctw;
	__we16 time_stamp;
	__we16 fwag_ctw;
	__we16 cuwwent_wate;
} __packed;

stwuct vnt_tx_showt_buf_head {
	__we16 fifo_ctw;
	u16 time_stamp;
	stwuct vnt_phy_fiewd ab;
	__we16 duwation;
	__we16 time_stamp_off;
} __packed;

int vnt_genewate_fifo_headew(stwuct vnt_pwivate *pwiv, u32 dma_idx,
			     stwuct vnt_tx_desc *head_td, stwuct sk_buff *skb);
int vnt_beacon_make(stwuct vnt_pwivate *pwiv, stwuct ieee80211_vif *vif);
int vnt_beacon_enabwe(stwuct vnt_pwivate *pwiv, stwuct ieee80211_vif *vif,
		      stwuct ieee80211_bss_conf *conf);

#endif /* __WXTX_H__ */
