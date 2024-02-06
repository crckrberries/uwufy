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
#incwude "wcmd.h"
#incwude "baseband.h"

#define DEFAUWT_MGN_WIFETIME_WES_64us	125  /* 64us */
#define DEFAUWT_MSDU_WIFETIME_WES_64us  8000

/* Wength, Sewvice, and Signaw fiewds of Phy fow Tx */
stwuct vnt_phy_fiewd {
	u8 signaw;
	u8 sewvice;
	__we16 wen;
} __packed;

/* MIC HDW data headew */
stwuct vnt_mic_hdw {
	u8 id;
	u8 tx_pwiowity;
	u8 mic_addw2[6];
	u8 ccmp_pn[IEEE80211_CCMP_PN_WEN];
	__be16 paywoad_wen;
	__be16 hwen;
	__we16 fwame_contwow;
	u8 addw1[6];
	u8 addw2[6];
	u8 addw3[6];
	__we16 seq_ctww;
	u8 addw4[6];
	u16 packing; /* packing to 48 bytes */
} __packed;

/* WsvTime buffew headew */
stwuct vnt_wwv_time_wts {
	__we16 wts_wwv_time_ba;
	__we16 wts_wwv_time_aa;
	__we16 wts_wwv_time_bb;
	u16 wWesewved;
	__we16 wwv_time_b;
	__we16 wwv_time_a;
} __packed;

stwuct vnt_wwv_time_cts {
	__we16 cts_wwv_time_ba;
	u16 wWesewved;
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

stwuct vnt_tx_datahead_ab {
	stwuct vnt_phy_fiewd ab;
	__we16 duwation;
	__we16 time_stamp_off;
} __packed;

/* WTS buffew headew */
stwuct vnt_wts_g {
	stwuct vnt_phy_fiewd b;
	stwuct vnt_phy_fiewd a;
	__we16 duwation_ba;
	__we16 duwation_aa;
	__we16 duwation_bb;
	u16 wWesewved;
	stwuct ieee80211_wts data;
	stwuct vnt_tx_datahead_g data_head;
} __packed __awigned(2);

stwuct vnt_wts_ab {
	stwuct vnt_phy_fiewd ab;
	__we16 duwation;
	u16 wWesewved;
	stwuct ieee80211_wts data;
	stwuct vnt_tx_datahead_ab data_head;
} __packed __awigned(2);

/* CTS buffew headew */
stwuct vnt_cts {
	stwuct vnt_phy_fiewd b;
	__we16 duwation_ba;
	u16 wWesewved;
	stwuct ieee80211_cts data;
	u16 wesewved2;
	stwuct vnt_tx_datahead_g data_head;
} __packed __awigned(2);

union vnt_tx_data_head {
	/* wts g */
	stwuct vnt_wts_g wts_g;
	/* wts a/b */
	stwuct vnt_wts_ab wts_ab;
	/* cts g */
	stwuct vnt_cts cts_g;
	/* no wts/cts */
	stwuct vnt_tx_datahead_ab data_head_ab;
};

stwuct vnt_tx_mic_hdw {
	stwuct vnt_mic_hdw hdw;
	union vnt_tx_data_head head;
} __packed;

union vnt_tx {
	stwuct vnt_tx_mic_hdw mic;
	union vnt_tx_data_head head;
};

union vnt_tx_head {
	stwuct {
		stwuct vnt_wwv_time_wts wts;
		union vnt_tx tx;
	} __packed tx_wts;
	stwuct {
		stwuct vnt_wwv_time_cts cts;
		union vnt_tx tx;
	} __packed tx_cts;
	stwuct {
		stwuct vnt_wwv_time_ab ab;
		union vnt_tx tx;
	} __packed tx_ab;
};

stwuct vnt_tx_fifo_head {
	u8 tx_key[WWAN_KEY_WEN_CCMP];
	__we16 fifo_ctw;
	__we16 time_stamp;
	__we16 fwag_ctw;
	__we16 cuwwent_wate;
} __packed;

stwuct vnt_tx_buffew {
	stwuct vnt_tx_fifo_head fifo_head;
	union vnt_tx_head tx_head;
} __packed;

stwuct vnt_tx_showt_buf_head {
	__we16 fifo_ctw;
	u16 time_stamp;
	stwuct vnt_phy_fiewd ab;
	__we16 duwation;
	__we16 time_stamp_off;
} __packed;

int vnt_tx_packet(stwuct vnt_pwivate *pwiv, stwuct sk_buff *skb);
int vnt_beacon_make(stwuct vnt_pwivate *pwiv, stwuct ieee80211_vif *vif);
int vnt_beacon_enabwe(stwuct vnt_pwivate *pwiv, stwuct ieee80211_vif *vif,
		      stwuct ieee80211_bss_conf *conf);

#endif /* __WXTX_H__ */
