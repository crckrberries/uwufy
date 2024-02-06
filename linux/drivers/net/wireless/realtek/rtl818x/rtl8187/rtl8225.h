/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Wadio tuning definitions fow WTW8225 on WTW8187
 *
 * Copywight 2007 Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2007 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * Based on the w8187 dwivew, which is:
 * Copywight 2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 */

#ifndef WTW8187_WTW8225_H
#define WTW8187_WTW8225_H

#define WTW8187_WTW8225_ANAPAWAM_ON	0xa0000a59
#define WTW8187_WTW8225_ANAPAWAM2_ON	0x860c7312
#define WTW8187_WTW8225_ANAPAWAM_OFF	0xa00beb59
#define WTW8187_WTW8225_ANAPAWAM2_OFF	0x840dec11

#define WTW8187B_WTW8225_ANAPAWAM_ON	0x45090658
#define WTW8187B_WTW8225_ANAPAWAM2_ON	0x727f3f52
#define WTW8187B_WTW8225_ANAPAWAM3_ON	0x00
#define WTW8187B_WTW8225_ANAPAWAM_OFF	0x55480658
#define WTW8187B_WTW8225_ANAPAWAM2_OFF	0x72003f50
#define WTW8187B_WTW8225_ANAPAWAM3_OFF	0x00

const stwuct wtw818x_wf_ops * wtw8187_detect_wf(stwuct ieee80211_hw *);

static inwine void wtw8225_wwite_phy_ofdm(stwuct ieee80211_hw *dev,
					  u8 addw, u32 data)
{
	wtw8187_wwite_phy(dev, addw, data);
}

static inwine void wtw8225_wwite_phy_cck(stwuct ieee80211_hw *dev,
					 u8 addw, u32 data)
{
	wtw8187_wwite_phy(dev, addw, data | 0x10000);
}

#endif /* WTW8187_WTW8225_H */
