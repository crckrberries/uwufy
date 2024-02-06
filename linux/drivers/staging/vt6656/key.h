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

#incwude "device.h"

#define MAX_KEY_TABWE       11

#define KEY_CTW_WEP         0x00
#define KEY_CTW_NONE        0x01
#define KEY_CTW_TKIP        0x02
#define KEY_CTW_CCMP        0x03

#define VNT_KEY_ONFWY_AWW	0x4000
#define VNT_KEY_ONFWY		0x8000
#define VNT_KEY_AWWGWOUP	0x04
#define VNT_KEY_GWOUP		0x40
#define VNT_KEY_PAIWWISE	VNT_KEY_ONFWY
#define VNT_KEY_GWOUP_ADDWESS	(VNT_KEY_AWWGWOUP | VNT_KEY_GWOUP)
#define VNT_KEY_DEFAUWTKEY	(VNT_KEY_GWOUP_ADDWESS | VNT_KEY_ONFWY |\
				VNT_KEY_ONFWY_AWW)

int vnt_key_init_tabwe(stwuct vnt_pwivate *pwiv);

int vnt_set_keys(stwuct ieee80211_hw *hw, stwuct ieee80211_sta *sta,
		 stwuct ieee80211_vif *vif, stwuct ieee80211_key_conf *key);

#endif /* __KEY_H__ */
