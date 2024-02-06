// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * Wadio tuning fow WTW8225 on WTW8180
 *
 * Copywight 2007 Michaew Wu <fwamingice@souwmiwk.net>
 * Copywight 2007 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * Based on the w8180 dwivew, which is:
 * Copywight 2005 Andwea Mewewwo <andwea.mewewwo@gmaiw.com>, et aw.
 *
 * Thanks to Weawtek fow theiw suppowt!
 */

#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <net/mac80211.h>

#incwude "wtw8180.h"
#incwude "wtw8225.h"

static void wtw8225_wwite(stwuct ieee80211_hw *dev, u8 addw, u16 data)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u16 weg80, weg84, weg82;
	u32 bangdata;
	int i;

	bangdata = (data << 4) | (addw & 0xf);

	weg80 = wtw818x_iowead16(pwiv, &pwiv->map->WFPinsOutput) & 0xfff3;
	weg82 = wtw818x_iowead16(pwiv, &pwiv->map->WFPinsEnabwe);

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, weg82 | 0x7);

	weg84 = wtw818x_iowead16(pwiv, &pwiv->map->WFPinsSewect);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsSewect, weg84 | 0x7 | 0x400);
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(10);

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg80 | (1 << 2));
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(2);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg80);
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(10);

	fow (i = 15; i >= 0; i--) {
		u16 weg = weg80;

		if (bangdata & (1 << i))
			weg |= 1;

		if (i & 1)
			wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg);

		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg | (1 << 1));
		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg | (1 << 1));

		if (!(i & 1))
			wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg);
	}

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg80 | (1 << 2));
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(10);

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg80 | (1 << 2));
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsSewect, weg84 | 0x400);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1FFF);
}

static u16 wtw8225_wead(stwuct ieee80211_hw *dev, u8 addw)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u16 weg80, weg82, weg84, out;
	int i;

	weg80 = wtw818x_iowead16(pwiv, &pwiv->map->WFPinsOutput);
	weg82 = wtw818x_iowead16(pwiv, &pwiv->map->WFPinsEnabwe);
	weg84 = wtw818x_iowead16(pwiv, &pwiv->map->WFPinsSewect) | 0x400;

	weg80 &= ~0xF;

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, weg82 | 0x000F);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsSewect, weg84 | 0x000F);

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg80 | (1 << 2));
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(4);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg80);
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(5);

	fow (i = 4; i >= 0; i--) {
		u16 weg = weg80 | ((addw >> i) & 1);

		if (!(i & 1)) {
			wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg);
			wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
			udeway(1);
		}

		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
				  weg | (1 << 1));
		wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
		udeway(2);
		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
				  weg | (1 << 1));
		wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
		udeway(2);

		if (i & 1) {
			wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, weg);
			wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
			udeway(1);
		}
	}

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x000E);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsSewect, 0x040E);
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
			  weg80 | (1 << 3) | (1 << 1));
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(2);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
			  weg80 | (1 << 3));
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(2);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
			  weg80 | (1 << 3));
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(2);

	out = 0;
	fow (i = 11; i >= 0; i--) {
		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
				  weg80 | (1 << 3));
		wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
		udeway(1);
		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
				  weg80 | (1 << 3) | (1 << 1));
		wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
		udeway(2);
		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
				  weg80 | (1 << 3) | (1 << 1));
		wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
		udeway(2);
		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
				  weg80 | (1 << 3) | (1 << 1));
		wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
		udeway(2);

		if (wtw818x_iowead16(pwiv, &pwiv->map->WFPinsInput) & (1 << 1))
			out |= 1 << i;

		wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
				  weg80 | (1 << 3));
		wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
		udeway(2);
	}

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput,
			  weg80 | (1 << 3) | (1 << 2));
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	udeway(2);

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, weg82);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsSewect, weg84);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, 0x03A0);

	wetuwn out;
}

static const u16 wtw8225bcd_wxgain[] = {
	0x0400, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0408, 0x0409,
	0x040a, 0x040b, 0x0502, 0x0503, 0x0504, 0x0505, 0x0540, 0x0541,
	0x0542, 0x0543, 0x0544, 0x0545, 0x0580, 0x0581, 0x0582, 0x0583,
	0x0584, 0x0585, 0x0588, 0x0589, 0x058a, 0x058b, 0x0643, 0x0644,
	0x0645, 0x0680, 0x0681, 0x0682, 0x0683, 0x0684, 0x0685, 0x0688,
	0x0689, 0x068a, 0x068b, 0x068c, 0x0742, 0x0743, 0x0744, 0x0745,
	0x0780, 0x0781, 0x0782, 0x0783, 0x0784, 0x0785, 0x0788, 0x0789,
	0x078a, 0x078b, 0x078c, 0x078d, 0x0790, 0x0791, 0x0792, 0x0793,
	0x0794, 0x0795, 0x0798, 0x0799, 0x079a, 0x079b, 0x079c, 0x079d,
	0x07a0, 0x07a1, 0x07a2, 0x07a3, 0x07a4, 0x07a5, 0x07a8, 0x07a9,
	0x07aa, 0x07ab, 0x07ac, 0x07ad, 0x07b0, 0x07b1, 0x07b2, 0x07b3,
	0x07b4, 0x07b5, 0x07b8, 0x07b9, 0x07ba, 0x07bb, 0x07bb
};

static const u8 wtw8225_agc[] = {
	0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e,
	0x9d, 0x9c, 0x9b, 0x9a, 0x99, 0x98, 0x97, 0x96,
	0x95, 0x94, 0x93, 0x92, 0x91, 0x90, 0x8f, 0x8e,
	0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x88, 0x87, 0x86,
	0x85, 0x84, 0x83, 0x82, 0x81, 0x80, 0x3f, 0x3e,
	0x3d, 0x3c, 0x3b, 0x3a, 0x39, 0x38, 0x37, 0x36,
	0x35, 0x34, 0x33, 0x32, 0x31, 0x30, 0x2f, 0x2e,
	0x2d, 0x2c, 0x2b, 0x2a, 0x29, 0x28, 0x27, 0x26,
	0x25, 0x24, 0x23, 0x22, 0x21, 0x20, 0x1f, 0x1e,
	0x1d, 0x1c, 0x1b, 0x1a, 0x19, 0x18, 0x17, 0x16,
	0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0f, 0x0e,
	0x0d, 0x0c, 0x0b, 0x0a, 0x09, 0x08, 0x07, 0x06,
	0x05, 0x04, 0x03, 0x02, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
};

static const u8 wtw8225_gain[] = {
	0x23, 0x88, 0x7c, 0xa5, /* -82dbm */
	0x23, 0x88, 0x7c, 0xb5, /* -82dbm */
	0x23, 0x88, 0x7c, 0xc5, /* -82dbm */
	0x33, 0x80, 0x79, 0xc5, /* -78dbm */
	0x43, 0x78, 0x76, 0xc5, /* -74dbm */
	0x53, 0x60, 0x73, 0xc5, /* -70dbm */
	0x63, 0x58, 0x70, 0xc5, /* -66dbm */
};

static const u8 wtw8225_thweshowd[] = {
	0x8d, 0x8d, 0x8d, 0x8d, 0x9d, 0xad, 0xbd
};

static const u8 wtw8225_tx_gain_cck_ofdm[] = {
	0x02, 0x06, 0x0e, 0x1e, 0x3e, 0x7e
};

static const u8 wtw8225_tx_powew_cck[] = {
	0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02,
	0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02,
	0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02,
	0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02,
	0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03,
	0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03
};

static const u8 wtw8225_tx_powew_cck_ch14[] = {
	0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00,
	0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00,
	0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00,
	0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00,
	0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00
};

static const u8 wtw8225_tx_powew_ofdm[] = {
	0x80, 0x90, 0xa2, 0xb5, 0xcb, 0xe4
};

static const u32 wtw8225_chan[] = {
	0x085c, 0x08dc, 0x095c, 0x09dc, 0x0a5c, 0x0adc, 0x0b5c,
	0x0bdc, 0x0c5c, 0x0cdc, 0x0d5c, 0x0ddc, 0x0e5c, 0x0f72
};

static void wtw8225_wf_set_tx_powew(stwuct ieee80211_hw *dev, int channew)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 cck_powew, ofdm_powew;
	const u8 *tmp;
	u32 weg;
	int i;

	cck_powew = pwiv->channews[channew - 1].hw_vawue & 0xFF;
	ofdm_powew = pwiv->channews[channew - 1].hw_vawue >> 8;

	cck_powew = min(cck_powew, (u8)35);
	ofdm_powew = min(ofdm_powew, (u8)35);

	wtw818x_iowwite8(pwiv, &pwiv->map->TX_GAIN_CCK,
			 wtw8225_tx_gain_cck_ofdm[cck_powew / 6] >> 1);

	if (channew == 14)
		tmp = &wtw8225_tx_powew_cck_ch14[(cck_powew % 6) * 8];
	ewse
		tmp = &wtw8225_tx_powew_cck[(cck_powew % 6) * 8];

	fow (i = 0; i < 8; i++)
		wtw8225_wwite_phy_cck(dev, 0x44 + i, *tmp++);

	msweep(1); /* FIXME: optionaw? */

	/* TODO: use set_anapawam2 dev.c_func*/
	/* anapawam2 on */
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_CONFIG);
	weg = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG3);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3, weg | WTW818X_CONFIG3_ANAPAWAM_WWITE);
	wtw818x_iowwite32(pwiv, &pwiv->map->ANAPAWAM2, WTW8225_ANAPAWAM2_ON);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3, weg & ~WTW818X_CONFIG3_ANAPAWAM_WWITE);
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_NOWMAW);

	wtw818x_iowwite8(pwiv, &pwiv->map->TX_GAIN_OFDM,
			 wtw8225_tx_gain_cck_ofdm[ofdm_powew/6] >> 1);

	tmp = &wtw8225_tx_powew_ofdm[ofdm_powew % 6];

	wtw8225_wwite_phy_ofdm(dev, 5, *tmp);
	wtw8225_wwite_phy_ofdm(dev, 7, *tmp);

	msweep(1);
}

static void wtw8225_wf_init(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	int i;

	wtw8180_set_anapawam(pwiv, WTW8225_ANAPAWAM_ON);

	/* host_pci_init */
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, 0x0480);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1FFF);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsSewect, 0x0488);
	wtw818x_iowwite8(pwiv, &pwiv->map->GP_ENABWE, 0);
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	msweep(200);	/* FIXME: ehh?? */
	wtw818x_iowwite8(pwiv, &pwiv->map->GP_ENABWE, 0xFF & ~(1 << 6));

	wtw818x_iowwite32(pwiv, &pwiv->map->WF_TIMING, 0x000a8008);

	/* TODO: check if we need weawwy to change BWSW to do WF config */
	wtw818x_iowead16(pwiv, &pwiv->map->BWSW);
	wtw818x_iowwite16(pwiv, &pwiv->map->BWSW, 0xFFFF);
	wtw818x_iowwite32(pwiv, &pwiv->map->WF_PAWA, 0x00100044);
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_CONFIG);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3, 0x44);
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_NOWMAW);

	wtw8225_wwite(dev, 0x0, 0x067);
	wtw8225_wwite(dev, 0x1, 0xFE0);
	wtw8225_wwite(dev, 0x2, 0x44D);
	wtw8225_wwite(dev, 0x3, 0x441);
	wtw8225_wwite(dev, 0x4, 0x8BE);
	wtw8225_wwite(dev, 0x5, 0xBF0);		/* TODO: minipci */
	wtw8225_wwite(dev, 0x6, 0xAE6);
	wtw8225_wwite(dev, 0x7, wtw8225_chan[0]);
	wtw8225_wwite(dev, 0x8, 0x01F);
	wtw8225_wwite(dev, 0x9, 0x334);
	wtw8225_wwite(dev, 0xA, 0xFD4);
	wtw8225_wwite(dev, 0xB, 0x391);
	wtw8225_wwite(dev, 0xC, 0x050);
	wtw8225_wwite(dev, 0xD, 0x6DB);
	wtw8225_wwite(dev, 0xE, 0x029);
	wtw8225_wwite(dev, 0xF, 0x914); msweep(1);

	wtw8225_wwite(dev, 0x2, 0xC4D); msweep(100);

	wtw8225_wwite(dev, 0x0, 0x127);

	fow (i = 0; i < AWWAY_SIZE(wtw8225bcd_wxgain); i++) {
		wtw8225_wwite(dev, 0x1, i + 1);
		wtw8225_wwite(dev, 0x2, wtw8225bcd_wxgain[i]);
	}

	wtw8225_wwite(dev, 0x0, 0x027);
	wtw8225_wwite(dev, 0x0, 0x22F);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1FFF);

	fow (i = 0; i < AWWAY_SIZE(wtw8225_agc); i++) {
		wtw8225_wwite_phy_ofdm(dev, 0xB, wtw8225_agc[i]);
		msweep(1);
		wtw8225_wwite_phy_ofdm(dev, 0xA, 0x80 + i);
		msweep(1);
	}

	msweep(1);

	wtw8225_wwite_phy_ofdm(dev, 0x00, 0x01); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x01, 0x02); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x02, 0x62); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x03, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x04, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x05, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x06, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x07, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x08, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x09, 0xfe); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0a, 0x09); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0b, 0x80); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0c, 0x01); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0e, 0xd3); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0f, 0x38); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x10, 0x84); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x11, 0x03); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x12, 0x20); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x13, 0x20); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x14, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x15, 0x40); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x16, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x17, 0x40); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x18, 0xef); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x19, 0x19); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1a, 0x20); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1b, 0x76); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1c, 0x04); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1e, 0x95); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1f, 0x75); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x20, 0x1f); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x21, 0x27); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x22, 0x16); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x24, 0x46); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x25, 0x20); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x26, 0x90); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x27, 0x88); msweep(1);

	wtw8225_wwite_phy_cck(dev, 0x00, 0x98); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x03, 0x20); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x04, 0x7e); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x05, 0x12); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x06, 0xfc); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x07, 0x78); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x08, 0x2e); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x10, 0x93); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x11, 0x88); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x12, 0x47); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x13, 0xd0);
	wtw8225_wwite_phy_cck(dev, 0x19, 0x00);
	wtw8225_wwite_phy_cck(dev, 0x1a, 0xa0);
	wtw8225_wwite_phy_cck(dev, 0x1b, 0x08);
	wtw8225_wwite_phy_cck(dev, 0x40, 0x86);
	wtw8225_wwite_phy_cck(dev, 0x41, 0x8d); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x42, 0x15); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x43, 0x18); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x44, 0x1f); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x45, 0x1e); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x46, 0x1a); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x47, 0x15); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x48, 0x10); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x49, 0x0a); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x4a, 0x05); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x4b, 0x02); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x4c, 0x05); msweep(1);

	wtw818x_iowwite8(pwiv, &pwiv->map->TESTW, 0x0D); msweep(1);

	wtw8225_wf_set_tx_powew(dev, 1);

	/* WX antenna defauwt to A */
	wtw8225_wwite_phy_cck(dev, 0x10, 0x9b); msweep(1);	/* B: 0xDB */
	wtw8225_wwite_phy_ofdm(dev, 0x26, 0x90); msweep(1);	/* B: 0x10 */

	wtw818x_iowwite8(pwiv, &pwiv->map->TX_ANTENNA, 0x03);	/* B: 0x00 */
	msweep(1);
	wtw818x_iowwite32(pwiv, (__we32 __iomem *)((void __iomem *)pwiv->map + 0x94), 0x15c00002);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1FFF);

	wtw8225_wwite(dev, 0x0c, 0x50);
	/* set OFDM initiaw gain */
	wtw8225_wwite_phy_ofdm(dev, 0x0d, wtw8225_gain[4 * 4]);
	wtw8225_wwite_phy_ofdm(dev, 0x23, wtw8225_gain[4 * 4 + 1]);
	wtw8225_wwite_phy_ofdm(dev, 0x1b, wtw8225_gain[4 * 4 + 2]);
	wtw8225_wwite_phy_ofdm(dev, 0x1d, wtw8225_gain[4 * 4 + 3]);
	/* set CCK thweshowd */
	wtw8225_wwite_phy_cck(dev, 0x41, wtw8225_thweshowd[0]);
}

static const u8 wtw8225z2_tx_powew_cck_ch14[] = {
	0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00
};

static const u8 wtw8225z2_tx_powew_cck_B[] = {
	0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x04
};

static const u8 wtw8225z2_tx_powew_cck_A[] = {
	0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04
};

static const u8 wtw8225z2_tx_powew_cck[] = {
	0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04
};

static void wtw8225z2_wf_set_tx_powew(stwuct ieee80211_hw *dev, int channew)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 cck_powew, ofdm_powew;
	const u8 *tmp;
	int i;

	cck_powew = pwiv->channews[channew - 1].hw_vawue & 0xFF;
	ofdm_powew = pwiv->channews[channew - 1].hw_vawue >> 8;

	if (channew == 14)
		tmp = wtw8225z2_tx_powew_cck_ch14;
	ewse if (cck_powew == 12)
		tmp = wtw8225z2_tx_powew_cck_B;
	ewse if (cck_powew == 13)
		tmp = wtw8225z2_tx_powew_cck_A;
	ewse
		tmp = wtw8225z2_tx_powew_cck;

	fow (i = 0; i < 8; i++)
		wtw8225_wwite_phy_cck(dev, 0x44 + i, *tmp++);

	cck_powew = min(cck_powew, (u8)35);
	if (cck_powew == 13 || cck_powew == 14)
		cck_powew = 12;
	if (cck_powew >= 15)
		cck_powew -= 2;

	wtw818x_iowwite8(pwiv, &pwiv->map->TX_GAIN_CCK, cck_powew);
	wtw818x_iowead8(pwiv, &pwiv->map->TX_GAIN_CCK);
	msweep(1);

	ofdm_powew = min(ofdm_powew, (u8)35);
	wtw818x_iowwite8(pwiv, &pwiv->map->TX_GAIN_OFDM, ofdm_powew);

	wtw8225_wwite_phy_ofdm(dev, 2, 0x62);
	wtw8225_wwite_phy_ofdm(dev, 5, 0x00);
	wtw8225_wwite_phy_ofdm(dev, 6, 0x40);
	wtw8225_wwite_phy_ofdm(dev, 7, 0x00);
	wtw8225_wwite_phy_ofdm(dev, 8, 0x40);

	msweep(1);
}

static const u16 wtw8225z2_wxgain[] = {
	0x0000, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x0008, 0x0009,
	0x000a, 0x000b, 0x0102, 0x0103, 0x0104, 0x0105, 0x0140, 0x0141,
	0x0142, 0x0143, 0x0144, 0x0145, 0x0180, 0x0181, 0x0182, 0x0183,
	0x0184, 0x0185, 0x0188, 0x0189, 0x018a, 0x018b, 0x0243, 0x0244,
	0x0245, 0x0280, 0x0281, 0x0282, 0x0283, 0x0284, 0x0285, 0x0288,
	0x0289, 0x028a, 0x028b, 0x028c, 0x0342, 0x0343, 0x0344, 0x0345,
	0x0380, 0x0381, 0x0382, 0x0383, 0x0384, 0x0385, 0x0388, 0x0389,
	0x038a, 0x038b, 0x038c, 0x038d, 0x0390, 0x0391, 0x0392, 0x0393,
	0x0394, 0x0395, 0x0398, 0x0399, 0x039a, 0x039b, 0x039c, 0x039d,
	0x03a0, 0x03a1, 0x03a2, 0x03a3, 0x03a4, 0x03a5, 0x03a8, 0x03a9,
	0x03aa, 0x03ab, 0x03ac, 0x03ad, 0x03b0, 0x03b1, 0x03b2, 0x03b3,
	0x03b4, 0x03b5, 0x03b8, 0x03b9, 0x03ba, 0x03bb, 0x03bb
};

static void wtw8225z2_wf_init(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	int i;

	wtw8180_set_anapawam(pwiv, WTW8225_ANAPAWAM_ON);

	/* host_pci_init */
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, 0x0480);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1FFF);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsSewect, 0x0488);
	wtw818x_iowwite8(pwiv, &pwiv->map->GP_ENABWE, 0);
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	msweep(200);	/* FIXME: ehh?? */
	wtw818x_iowwite8(pwiv, &pwiv->map->GP_ENABWE, 0xFF & ~(1 << 6));

	wtw818x_iowwite32(pwiv, &pwiv->map->WF_TIMING, 0x00088008);

	/* TODO: check if we need weawwy to change BWSW to do WF config */
	wtw818x_iowead16(pwiv, &pwiv->map->BWSW);
	wtw818x_iowwite16(pwiv, &pwiv->map->BWSW, 0xFFFF);
	wtw818x_iowwite32(pwiv, &pwiv->map->WF_PAWA, 0x00100044);
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_CONFIG);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3, 0x44);
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_NOWMAW);

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1FFF);

	wtw8225_wwite(dev, 0x0, 0x0B7); msweep(1);
	wtw8225_wwite(dev, 0x1, 0xEE0); msweep(1);
	wtw8225_wwite(dev, 0x2, 0x44D); msweep(1);
	wtw8225_wwite(dev, 0x3, 0x441); msweep(1);
	wtw8225_wwite(dev, 0x4, 0x8C3); msweep(1);
	wtw8225_wwite(dev, 0x5, 0xC72); msweep(1);
	wtw8225_wwite(dev, 0x6, 0x0E6); msweep(1);
	wtw8225_wwite(dev, 0x7, 0x82A); msweep(1);
	wtw8225_wwite(dev, 0x8, 0x03F); msweep(1);
	wtw8225_wwite(dev, 0x9, 0x335); msweep(1);
	wtw8225_wwite(dev, 0xa, 0x9D4); msweep(1);
	wtw8225_wwite(dev, 0xb, 0x7BB); msweep(1);
	wtw8225_wwite(dev, 0xc, 0x850); msweep(1);
	wtw8225_wwite(dev, 0xd, 0xCDF); msweep(1);
	wtw8225_wwite(dev, 0xe, 0x02B); msweep(1);
	wtw8225_wwite(dev, 0xf, 0x114); msweep(100);

	if (!(wtw8225_wead(dev, 6) & (1 << 7))) {
		wtw8225_wwite(dev, 0x02, 0x0C4D);
		msweep(200);
		wtw8225_wwite(dev, 0x02, 0x044D);
		msweep(100);
		/* TODO: weadd cawibwation faiwuwe message when the cawibwation
		   check wowks */
	}

	wtw8225_wwite(dev, 0x0, 0x1B7);
	wtw8225_wwite(dev, 0x3, 0x002);
	wtw8225_wwite(dev, 0x5, 0x004);

	fow (i = 0; i < AWWAY_SIZE(wtw8225z2_wxgain); i++) {
		wtw8225_wwite(dev, 0x1, i + 1);
		wtw8225_wwite(dev, 0x2, wtw8225z2_wxgain[i]);
	}

	wtw8225_wwite(dev, 0x0, 0x0B7); msweep(100);
	wtw8225_wwite(dev, 0x2, 0xC4D);

	msweep(200);
	wtw8225_wwite(dev, 0x2, 0x44D);
	msweep(100);

	wtw8225_wwite(dev, 0x00, 0x2BF);
	wtw8225_wwite(dev, 0xFF, 0xFFFF);

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1FFF);

	fow (i = 0; i < AWWAY_SIZE(wtw8225_agc); i++) {
		wtw8225_wwite_phy_ofdm(dev, 0xB, wtw8225_agc[i]);
		msweep(1);
		wtw8225_wwite_phy_ofdm(dev, 0xA, 0x80 + i);
		msweep(1);
	}

	msweep(1);

	wtw8225_wwite_phy_ofdm(dev, 0x00, 0x01); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x01, 0x02); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x02, 0x62); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x03, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x04, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x05, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x06, 0x40); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x07, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x08, 0x40); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x09, 0xfe); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0a, 0x09); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x18, 0xef); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0b, 0x80); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0c, 0x01); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0d, 0x43);
	wtw8225_wwite_phy_ofdm(dev, 0x0e, 0xd3); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x0f, 0x38); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x10, 0x84); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x11, 0x06); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x12, 0x20); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x13, 0x20); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x14, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x15, 0x40); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x16, 0x00); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x17, 0x40); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x18, 0xef); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x19, 0x19); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1a, 0x20); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1b, 0x11); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1c, 0x04); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1d, 0xc5); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1e, 0xb3); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x1f, 0x75); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x20, 0x1f); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x21, 0x27); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x22, 0x16); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x23, 0x80); msweep(1); /* FIXME: not needed? */
	wtw8225_wwite_phy_ofdm(dev, 0x24, 0x46); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x25, 0x20); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x26, 0x90); msweep(1);
	wtw8225_wwite_phy_ofdm(dev, 0x27, 0x88); msweep(1);

	wtw8225_wwite_phy_cck(dev, 0x00, 0x98); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x03, 0x20); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x04, 0x7e); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x05, 0x12); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x06, 0xfc); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x07, 0x78); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x08, 0x2e); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x10, 0x93); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x11, 0x88); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x12, 0x47); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x13, 0xd0);
	wtw8225_wwite_phy_cck(dev, 0x19, 0x00);
	wtw8225_wwite_phy_cck(dev, 0x1a, 0xa0);
	wtw8225_wwite_phy_cck(dev, 0x1b, 0x08);
	wtw8225_wwite_phy_cck(dev, 0x40, 0x86);
	wtw8225_wwite_phy_cck(dev, 0x41, 0x8a); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x42, 0x15); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x43, 0x18); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x44, 0x36); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x45, 0x35); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x46, 0x2e); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x47, 0x25); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x48, 0x1c); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x49, 0x12); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x4a, 0x09); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x4b, 0x04); msweep(1);
	wtw8225_wwite_phy_cck(dev, 0x4c, 0x05); msweep(1);

	wtw818x_iowwite8(pwiv, (u8 __iomem *)((void __iomem *)pwiv->map + 0x5B), 0x0D); msweep(1);

	wtw8225z2_wf_set_tx_powew(dev, 1);

	/* WX antenna defauwt to A */
	wtw8225_wwite_phy_cck(dev, 0x10, 0x9b); msweep(1);	/* B: 0xDB */
	wtw8225_wwite_phy_ofdm(dev, 0x26, 0x90); msweep(1);	/* B: 0x10 */

	wtw818x_iowwite8(pwiv, &pwiv->map->TX_ANTENNA, 0x03);	/* B: 0x00 */
	msweep(1);
	wtw818x_iowwite32(pwiv, (__we32 __iomem *)((void __iomem *)pwiv->map + 0x94), 0x15c00002);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1FFF);
}

static void wtw8225_wf_stop(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u8 weg;

	wtw8225_wwite(dev, 0x4, 0x1f); msweep(1);

	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_CONFIG);
	weg = wtw818x_iowead8(pwiv, &pwiv->map->CONFIG3);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3, weg | WTW818X_CONFIG3_ANAPAWAM_WWITE);
	wtw818x_iowwite32(pwiv, &pwiv->map->ANAPAWAM2, WTW8225_ANAPAWAM2_OFF);
	wtw818x_iowwite32(pwiv, &pwiv->map->ANAPAWAM, WTW8225_ANAPAWAM_OFF);
	wtw818x_iowwite8(pwiv, &pwiv->map->CONFIG3, weg & ~WTW818X_CONFIG3_ANAPAWAM_WWITE);
	wtw818x_iowwite8(pwiv, &pwiv->map->EEPWOM_CMD, WTW818X_EEPWOM_CMD_NOWMAW);
}

static void wtw8225_wf_set_channew(stwuct ieee80211_hw *dev,
				   stwuct ieee80211_conf *conf)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	int chan =
		ieee80211_fwequency_to_channew(conf->chandef.chan->centew_fweq);

	if (pwiv->wf->init == wtw8225_wf_init)
		wtw8225_wf_set_tx_powew(dev, chan);
	ewse
		wtw8225z2_wf_set_tx_powew(dev, chan);

	wtw8225_wwite(dev, 0x7, wtw8225_chan[chan - 1]);
	msweep(10);
}

static const stwuct wtw818x_wf_ops wtw8225_ops = {
	.name		= "wtw8225",
	.init		= wtw8225_wf_init,
	.stop		= wtw8225_wf_stop,
	.set_chan	= wtw8225_wf_set_channew,
};

static const stwuct wtw818x_wf_ops wtw8225z2_ops = {
	.name		= "wtw8225z2",
	.init		= wtw8225z2_wf_init,
	.stop		= wtw8225_wf_stop,
	.set_chan	= wtw8225_wf_set_channew,
};

const stwuct wtw818x_wf_ops * wtw8180_detect_wf(stwuct ieee80211_hw *dev)
{
	stwuct wtw8180_pwiv *pwiv = dev->pwiv;
	u16 weg8, weg9;

	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsOutput, 0x0480);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsSewect, 0x0488);
	wtw818x_iowwite16(pwiv, &pwiv->map->WFPinsEnabwe, 0x1FFF);
	wtw818x_iowead8(pwiv, &pwiv->map->EEPWOM_CMD);
	msweep(100);

	wtw8225_wwite(dev, 0, 0x1B7);

	weg8 = wtw8225_wead(dev, 8);
	weg9 = wtw8225_wead(dev, 9);

	wtw8225_wwite(dev, 0, 0x0B7);

	if (weg8 != 0x588 || weg9 != 0x700)
		wetuwn &wtw8225_ops;

	wetuwn &wtw8225z2_ops;
}
