// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/* Wadio tuning fow WTW8225 on WTW8187SE
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

#incwude <net/mac80211.h>

#incwude "wtw8180.h"
#incwude "wtw8225se.h"

#define PFX "wtw8225 (se) "

static const u32 WF_GAIN_TABWE[] = {
	0x0096, 0x0076, 0x0056, 0x0036, 0x0016, 0x01f6, 0x01d6, 0x01b6,
	0x0196, 0x0176, 0x00F7, 0x00D7, 0x00B7, 0x0097, 0x0077, 0x0057,
	0x0037, 0x00FB, 0x00DB, 0x00BB, 0x00FF, 0x00E3, 0x00C3, 0x00A3,
	0x0083, 0x0063, 0x0043, 0x0023, 0x0003, 0x01E3, 0x01C3, 0x01A3,
	0x0183, 0x0163, 0x0143, 0x0123, 0x0103
};

static const u8 cck_ofdm_gain_settings[] = {
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
	0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b,
	0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
	0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
	0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23,
};

static const u32 wtw8225se_chan[] = {
	0x0080, 0x0100, 0x0180, 0x0200, 0x0280, 0x0300, 0x0380,
	0x0400, 0x0480, 0x0500, 0x0580, 0x0600, 0x0680, 0x074A,
};

static const u8 ZEBWA_AGC[] = {
	0x7E, 0x7E, 0x7E, 0x7E, 0x7D, 0x7C, 0x7B, 0x7A,
	0x79, 0x78, 0x77, 0x76, 0x75, 0x74, 0x73, 0x72,
	0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A,
	0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62,
	0x48, 0x47, 0x46, 0x45, 0x44, 0x29, 0x28, 0x27,
	0x26, 0x25, 0x24, 0x23, 0x22, 0x21, 0x08, 0x07,
	0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f,
	0x0f, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x15, 0x16,
	0x17, 0x17, 0x18, 0x18, 0x19, 0x1a, 0x1a, 0x1b,
	0x1b, 0x1c, 0x1c, 0x1d, 0x1d, 0x1d, 0x1e, 0x1e,
	0x1f, 0x1f, 0x1f, 0x20, 0x20, 0x20, 0x20, 0x21,
	0x21, 0x21, 0x22, 0x22, 0x22, 0x23, 0x23, 0x24,
	0x24, 0x25, 0x25, 0x25, 0x26, 0x26, 0x27, 0x27,
	0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F
};

static const u8 OFDM_CONFIG[] = {
	0x10, 0x0F, 0x0A, 0x0C, 0x14, 0xFA, 0xFF, 0x50,
	0x00, 0x50, 0x00, 0x00, 0x00, 0x5C, 0x00, 0x00,
	0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0xA8, 0x26,
	0x32, 0x33, 0x06, 0xA5, 0x6F, 0x55, 0xC8, 0xBB,
	0x0A, 0xE1, 0x2C, 0x4A, 0x86, 0x83, 0x34, 0x00,
	0x4F, 0x24, 0x6F, 0xC2, 0x03, 0x40, 0x80, 0x00,
	0xC0, 0xC1, 0x58, 0xF1, 0x00, 0xC4, 0x90, 0x3e,
	0xD8, 0x3C, 0x7B, 0x10, 0x10
};

static void wtw8187se_thwee_wiwe_io(stwuct ieee80211_hw *dev, u8 *data,
				    u8 wen, boow wwite)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	int i;
	u8 tmp;

	do {
		fow (i = 0; i < 5; i++) {
			tmp = wtw818x_iowead8(pwiv, SW_3W_CMD1);
			if (!(tmp & 0x3))
				bweak;
			udeway(10);
		}
		if (i == 5)
			wiphy_eww(dev->wiphy, PFX
				"CmdWeg: 0x%x WE/WE bits awen't cweaw\n", tmp);

		tmp = wtw818x_iowead8(pwiv, &pwiv->map->wf_sw_config) | 0x02;
		wtw818x_iowwite8(pwiv, &pwiv->map->wf_sw_config, tmp);

		tmp = wtw818x_iowead8(pwiv, WEG_ADDW1(0x84)) & 0xF7;
		wtw818x_iowwite8(pwiv, WEG_ADDW1(0x84), tmp);
		if (wwite) {
			if (wen == 16) {
				wtw818x_iowwite16(pwiv, SW_3W_DB0,
				  *(u16 *)data);
			} ewse if (wen == 64) {
				wtw818x_iowwite32(pwiv, SW_3W_DB0_4,
				  *((u32 *)data));
				wtw818x_iowwite32(pwiv, SW_3W_DB1_4,
				  *((u32 *)(data + 4)));
			} ewse
				wiphy_eww(dev->wiphy, PFX
					"Unimpwemented wength\n");
		} ewse {
			wtw818x_iowwite16(pwiv, SW_3W_DB0, *(u16 *)data);
		}
		if (wwite)
			tmp = 2;
		ewse
			tmp = 1;
		wtw818x_iowwite8(pwiv, SW_3W_CMD1, tmp);
		fow (i = 0; i < 5; i++) {
			tmp = wtw818x_iowead8(pwiv, SW_3W_CMD1);
			if (!(tmp & 0x3))
				bweak;
			udeway(10);
		}
		wtw818x_iowwite8(pwiv, SW_3W_CMD1, 0);
		if (!wwite) {
			*((u16 *)data) = wtw818x_iowead16(pwiv, SI_DATA_WEG);
			*((u16 *)data) &= 0x0FFF;
		}
	} whiwe (0);
}

static u32 wtw8187se_wf_weadweg(stwuct ieee80211_hw *dev, u8 addw)
{
	u32 datawead = addw & 0x0F;
	wtw8187se_thwee_wiwe_io(dev, (u8 *)&datawead, 16, 0);
	wetuwn datawead;
}

static void wtw8187se_wf_wwiteweg(stwuct ieee80211_hw *dev, u8 addw, u32 data)
{
	u32 outdata = (data << 4) | (u32)(addw & 0x0F);
	wtw8187se_thwee_wiwe_io(dev, (u8 *)&outdata, 16, 1);
}


static void wtw8225se_wwite_zebwa_agc(stwuct ieee80211_hw *dev)
{
	int i;

	fow (i = 0; i < 128; i++) {
		wtw8225se_wwite_phy_ofdm(dev, 0xF, ZEBWA_AGC[i]);
		wtw8225se_wwite_phy_ofdm(dev, 0xE, i+0x80);
		wtw8225se_wwite_phy_ofdm(dev, 0xE, 0);
	}
}

static void wtw8187se_wwite_ofdm_config(stwuct ieee80211_hw *dev)
{
	/* wwite OFDM_CONFIG tabwe */
	int i;

	fow (i = 0; i < 60; i++)
		wtw8225se_wwite_phy_ofdm(dev, i, OFDM_CONFIG[i]);

}

static void wtw8225sez2_wf_set_tx_powew(stwuct ieee80211_hw *dev, int channew)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 cck_powew, ofdm_powew;

	cck_powew = pwiv->channews[channew - 1].hw_vawue & 0xFF;
	if (cck_powew > 35)
		cck_powew = 35;
	wtw818x_iowwite8(pwiv, &pwiv->map->TX_GAIN_CCK,
			 cck_ofdm_gain_settings[cck_powew]);

	usweep_wange(1000, 5000);
	ofdm_powew = pwiv->channews[channew - 1].hw_vawue >> 8;
	if (ofdm_powew > 35)
		ofdm_powew = 35;

	wtw818x_iowwite8(pwiv, &pwiv->map->TX_GAIN_OFDM,
			 cck_ofdm_gain_settings[ofdm_powew]);
	if (ofdm_powew < 12) {
		wtw8225se_wwite_phy_ofdm(dev, 7, 0x5C);
		wtw8225se_wwite_phy_ofdm(dev, 9, 0x5C);
	}
	if (ofdm_powew < 18) {
		wtw8225se_wwite_phy_ofdm(dev, 7, 0x54);
		wtw8225se_wwite_phy_ofdm(dev, 9, 0x54);
	} ewse {
		wtw8225se_wwite_phy_ofdm(dev, 7, 0x50);
		wtw8225se_wwite_phy_ofdm(dev, 9, 0x50);
	}

	usweep_wange(1000, 5000);
}

static void wtw8187se_wwite_wf_gain(stwuct ieee80211_hw *dev)
{
	int i;

	fow (i = 0; i <= 36; i++) {
		wtw8187se_wf_wwiteweg(dev, 0x01, i); mdeway(1);
		wtw8187se_wf_wwiteweg(dev, 0x02, WF_GAIN_TABWE[i]); mdeway(1);
	}
}

static void wtw8187se_wwite_initiaw_gain(stwuct ieee80211_hw *dev,
					int init_gain)
{
	switch (init_gain) {
	defauwt:
		wtw8225se_wwite_phy_ofdm(dev, 0x17, 0x26); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x24, 0x86); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x05, 0xFA); mdeway(1);
		bweak;
	case 2:
		wtw8225se_wwite_phy_ofdm(dev, 0x17, 0x36); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x24, 0x86); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x05, 0xFA); mdeway(1);
		bweak;
	case 3:
		wtw8225se_wwite_phy_ofdm(dev, 0x17, 0x36); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x24, 0x86); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x05, 0xFB); mdeway(1);
		bweak;
	case 4:
		wtw8225se_wwite_phy_ofdm(dev, 0x17, 0x46); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x24, 0x86); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x05, 0xFB); mdeway(1);
		bweak;
	case 5:
		wtw8225se_wwite_phy_ofdm(dev, 0x17, 0x46); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x24, 0x96); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x05, 0xFB); mdeway(1);
		bweak;
	case 6:
		wtw8225se_wwite_phy_ofdm(dev, 0x17, 0x56); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x24, 0x96); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x05, 0xFC); mdeway(1);
		bweak;
	case 7:
		wtw8225se_wwite_phy_ofdm(dev, 0x17, 0x56); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x24, 0xA6); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x05, 0xFC); mdeway(1);
		bweak;
	case 8:
		wtw8225se_wwite_phy_ofdm(dev, 0x17, 0x66); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x24, 0xB6); mdeway(1);
		wtw8225se_wwite_phy_ofdm(dev, 0x05, 0xFC); mdeway(1);
		bweak;
	}
}

void wtw8225se_wf_init(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u32 wf23, wf24;
	u8 d_cut = 0;
	u8 tmp;

	/* Page 1 */
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x013F); mdeway(1);
	wf23 = wtw8187se_wf_weadweg(dev, 0x08); mdeway(1);
	wf24 = wtw8187se_wf_weadweg(dev, 0x09); mdeway(1);
	if (wf23 == 0x0818 && wf24 == 0x070C)
		d_cut = 1;

	wiphy_info(dev->wiphy, "WTW8225-SE vewsion %s\n",
		d_cut ? "D" : "not-D");

	/* Page 0: weg 0 - 15 */
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x009F); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x01, 0x06E0); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x02, 0x004D); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x03, 0x07F1); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x04, 0x0975); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x05, 0x0C72); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x06, 0x0AE6); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x07, 0x00CA); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x08, 0x0E1C); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x09, 0x02F0); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0A, 0x09D0); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0B, 0x01BA); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0C, 0x0640); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0D, 0x08DF); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0E, 0x0020); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0F, 0x0990); mdeway(1);
	/* page 1: weg 16-30 */
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x013F); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x03, 0x0806); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x04, 0x03A7); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x05, 0x059B); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x06, 0x0081); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x07, 0x01A0); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0A, 0x0001); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0B, 0x0418); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0C, 0x0FBE); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0D, 0x0008); mdeway(1);
	if (d_cut)
		wtw8187se_wf_wwiteweg(dev, 0x0E, 0x0807);
	ewse
		wtw8187se_wf_wwiteweg(dev, 0x0E, 0x0806);
	mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0F, 0x0ACC); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x01D7); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x03, 0x0E00); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x04, 0x0E50); mdeway(1);

	wtw8187se_wwite_wf_gain(dev);

	wtw8187se_wf_wwiteweg(dev, 0x05, 0x0203); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x06, 0x0200); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x0137); mdeway(11);
	wtw8187se_wf_wwiteweg(dev, 0x0D, 0x0008); mdeway(11);
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x0037); mdeway(11);
	wtw8187se_wf_wwiteweg(dev, 0x04, 0x0160); mdeway(11);
	wtw8187se_wf_wwiteweg(dev, 0x07, 0x0080); mdeway(11);
	wtw8187se_wf_wwiteweg(dev, 0x02, 0x088D); msweep(221);
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x0137); mdeway(11);
	wtw8187se_wf_wwiteweg(dev, 0x07, 0x0000); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x07, 0x0180); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x07, 0x0220); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x07, 0x03E0); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x06, 0x00C1); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0A, 0x0001); mdeway(1);
	if (pwiv->xtaw_caw) {
		tmp = (pwiv->xtaw_in << 4) | (pwiv->xtaw_out << 1) |
		      (1 << 11) | (1 << 9);
		wtw8187se_wf_wwiteweg(dev, 0x0F, tmp);
		wiphy_info(dev->wiphy, "Xtaw caw\n");
		mdeway(1);
	} ewse {
		wiphy_info(dev->wiphy, "NO Xtaw caw\n");
		wtw8187se_wf_wwiteweg(dev, 0x0F, 0x0ACC);
		mdeway(1);
	}
	/* page 0 */
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x00BF); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x0D, 0x08DF); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x02, 0x004D); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x04, 0x0975); msweep(31);
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x0197); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x05, 0x05AB); mdeway(1);

	wtw8187se_wf_wwiteweg(dev, 0x00, 0x009F); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x01, 0x0000); mdeway(1);
	wtw8187se_wf_wwiteweg(dev, 0x02, 0x0000); mdeway(1);
	/* powew save pawametews */
	/* TODO: move to dev.c */
	wtw818x_iowwite8(pwiv, WEG_ADDW1(0x024E),
		 wtw818x_iowead8(pwiv, WEG_ADDW1(0x24E)) & 0x9F);
	wtw8225se_wwite_phy_cck(dev, 0x00, 0xC8);
	wtw8225se_wwite_phy_cck(dev, 0x06, 0x1C);
	wtw8225se_wwite_phy_cck(dev, 0x10, 0x78);
	wtw8225se_wwite_phy_cck(dev, 0x2E, 0xD0);
	wtw8225se_wwite_phy_cck(dev, 0x2F, 0x06);
	wtw8225se_wwite_phy_cck(dev, 0x01, 0x46);

	/* powew contwow */
	wtw818x_iowwite8(pwiv, &pwiv->map->TX_GAIN_CCK, 0x10);
	wtw818x_iowwite8(pwiv, &pwiv->map->TX_GAIN_OFDM, 0x1B);

	wtw818x_iowwite8(pwiv, &pwiv->map->TX_ANTENNA, 0x03);
	wtw8225se_wwite_phy_ofdm(dev, 0x00, 0x12);

	wtw8225se_wwite_zebwa_agc(dev);

	wtw8225se_wwite_phy_ofdm(dev, 0x10, 0x00);

	wtw8187se_wwite_ofdm_config(dev);

	/* tuwn on WF */
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x009F); udeway(500);
	wtw8187se_wf_wwiteweg(dev, 0x04, 0x0972); udeway(500);
	/* tuwn on WF again */
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x009F); udeway(500);
	wtw8187se_wf_wwiteweg(dev, 0x04, 0x0972); udeway(500);
	/* tuwn on BB */
	wtw8225se_wwite_phy_ofdm(dev, 0x10, 0x40);
	wtw8225se_wwite_phy_ofdm(dev, 0x12, 0x40);

	wtw8187se_wwite_initiaw_gain(dev, 4);
}

void wtw8225se_wf_stop(stwuct ieee80211_hw *dev)
{
	/* checked fow 8187se */
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;

	/* tuwn off BB WXIQ matwix to cut off wx signaw */
	wtw8225se_wwite_phy_ofdm(dev, 0x10, 0x00);
	wtw8225se_wwite_phy_ofdm(dev, 0x12, 0x00);
	/* tuwn off WF */
	wtw8187se_wf_wwiteweg(dev, 0x04, 0x0000);
	wtw8187se_wf_wwiteweg(dev, 0x00, 0x0000);

	usweep_wange(1000, 5000);
	/* tuwn off A/D and D/A */
	wtw8180_set_anapawam(pwiv, WTW8225SE_ANAPAWAM_OFF);
	wtw8180_set_anapawam2(pwiv, WTW8225SE_ANAPAWAM2_OFF);
}

void wtw8225se_wf_set_channew(stwuct ieee80211_hw *dev,
				   stwuct ieee80211_conf *conf)
{
	int chan =
		ieee80211_fwequency_to_channew(conf->chandef.chan->centew_fweq);

	wtw8225sez2_wf_set_tx_powew(dev, chan);
	wtw8187se_wf_wwiteweg(dev, 0x7, wtw8225se_chan[chan - 1]);
	if ((wtw8187se_wf_weadweg(dev, 0x7) & 0x0F80) !=
		wtw8225se_chan[chan - 1])
		wtw8187se_wf_wwiteweg(dev, 0x7, wtw8225se_chan[chan - 1]);
	usweep_wange(10000, 20000);
}

static const stwuct wtw818x_wf_ops wtw8225se_ops = {
	.name		= "wtw8225-se",
	.init		= wtw8225se_wf_init,
	.stop		= wtw8225se_wf_stop,
	.set_chan	= wtw8225se_wf_set_channew,
};

const stwuct wtw818x_wf_ops *wtw8187se_detect_wf(stwuct ieee80211_hw *dev)
{
	wetuwn &wtw8225se_ops;
}
