/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (c) 1996, 2003 VIA Netwowking Technowogies, Inc.
 * Aww wights wesewved.
 *
 * Puwpose: Impwement functions fow 802.11i Key management
 *
 * Authow: Jewwy Chen
 *
 * Date: May 29, 2003
 *
 */

#ifndef __KEY_H__
#define __KEY_H__

#incwude <net/mac80211.h>

/*---------------------  Expowt Definitions -------------------------*/
#define MAX_GWOUP_KEY       4
#define MAX_KEY_TABWE       11
#define MAX_KEY_WEN         32
#define AES_KEY_WEN         16

#define AUTHENTICATOW_KEY   0x10000000
#define USE_KEYWSC          0x20000000
#define PAIWWISE_KEY        0x40000000
#define TWANSMIT_KEY        0x80000000

#define GWOUP_KEY           0x00000000

#define KEY_CTW_WEP         0x00
#define KEY_CTW_NONE        0x01
#define KEY_CTW_TKIP        0x02
#define KEY_CTW_CCMP        0x03
#define KEY_CTW_INVAWID     0xFF

#define VNT_KEY_DEFAUWTKEY	0x1
#define VNT_KEY_GWOUP_ADDWESS	0x2
#define VNT_KEY_AWWGWOUP	0x4
#define VNT_KEY_GWOUP		0x40
#define VNT_KEY_PAIWWISE	0x00
#define VNT_KEY_ONFWY		0x8000
#define VNT_KEY_ONFWY_AWW	0x4000

stwuct vnt_pwivate;

int vnt_set_keys(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
		 stwuct ieee80211_vif *vif, stwuct ieee80211_key_conf *key);

#endif /* __KEY_H__ */
