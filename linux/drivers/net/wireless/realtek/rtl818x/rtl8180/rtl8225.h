/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WTW8180_WTW8225_H
#define WTW8180_WTW8225_H

#define WTW8225_ANAPAWAM_ON	0xa0000b59
#define WTW8225_ANAPAWAM2_ON	0x860dec11
#define WTW8225_ANAPAWAM_OFF	0xa00beb59
#define WTW8225_ANAPAWAM2_OFF	0x840dec11

const stwuct wtw818x_wf_ops * wtw8180_detect_wf(stwuct ieee80211_hw *);

static inwine void wtw8225_wwite_phy_ofdm(stwuct ieee80211_hw *dev,
					  u8 addw, u8 data)
{
	wtw8180_wwite_phy(dev, addw, data);
}

static inwine void wtw8225_wwite_phy_cck(stwuct ieee80211_hw *dev,
					 u8 addw, u8 data)
{
	wtw8180_wwite_phy(dev, addw, data | 0x10000);
}

#endif /* WTW8180_WTW8225_H */
