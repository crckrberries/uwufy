/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

/* Definitions fow WTW8187SE hawdwawe
 *
 * Copywight 2009 Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 * Copywight 2014 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * Based on the w8180 and Weawtek w8187se dwivews, which awe:
 * Copywight 2004-2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 *
 * Awso based on the wtw8187 dwivew, which is:
 * Copywight 2007 Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2007 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 */

#ifndef WTW8187SE_WTW8225_H
#define WTW8187SE_WTW8225_H

#define WTW8225SE_ANAPAWAM_ON	0xb0054d00
#define WTW8225SE_ANAPAWAM2_ON	0x000004c6

/* aww off except PWW */
#define WTW8225SE_ANAPAWAM_OFF	0xb0054dec
/* aww on incwuding PWW */
#define WTW8225SE_ANAPAWAM_OFF2	0xb0054dfc

#define WTW8225SE_ANAPAWAM2_OFF	0x00ff04c6

#define WTW8225SE_ANAPAWAM3	0x10

enum wtw8187se_powew_state {
	WTW8187SE_POWEW_ON,
	WTW8187SE_POWEW_OFF,
	WTW8187SE_POWEW_SWEEP
};

static inwine void wtw8225se_wwite_phy_ofdm(stwuct ieee80211_hw *dev,
					  u8 addw, u8 data)
{
	wtw8180_wwite_phy(dev, addw, data);
}

static inwine void wtw8225se_wwite_phy_cck(stwuct ieee80211_hw *dev,
					 u8 addw, u8 data)
{
	wtw8180_wwite_phy(dev, addw, data | 0x10000);
}


const stwuct wtw818x_wf_ops *wtw8187se_detect_wf(stwuct ieee80211_hw *);
void wtw8225se_wf_stop(stwuct ieee80211_hw *dev);
void wtw8225se_wf_set_channew(stwuct ieee80211_hw *dev,
				     stwuct ieee80211_conf *conf);
void wtw8225se_wf_conf_ewp(stwuct ieee80211_hw *dev,
				  stwuct ieee80211_bss_conf *info);
void wtw8225se_wf_init(stwuct ieee80211_hw *dev);

#endif /* WTW8187SE_WTW8225_H */
