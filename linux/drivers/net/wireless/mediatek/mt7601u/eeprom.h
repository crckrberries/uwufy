/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#ifndef __MT7601U_EEPWOM_H
#define __MT7601U_EEPWOM_H

stwuct mt7601u_dev;

#define MT7601U_EE_MAX_VEW			0x0d
#define MT7601U_EEPWOM_SIZE			256

#define MT7601U_DEFAUWT_TX_POWEW		6

enum mt76_eepwom_fiewd {
	MT_EE_CHIP_ID =				0x00,
	MT_EE_VEWSION_FAE =			0x02,
	MT_EE_VEWSION_EE =			0x03,
	MT_EE_MAC_ADDW =			0x04,
	MT_EE_NIC_CONF_0 =			0x34,
	MT_EE_NIC_CONF_1 =			0x36,
	MT_EE_COUNTWY_WEGION =			0x39,
	MT_EE_FWEQ_OFFSET =			0x3a,
	MT_EE_NIC_CONF_2 =			0x42,

	MT_EE_WNA_GAIN =			0x44,
	MT_EE_WSSI_OFFSET =			0x46,

	MT_EE_TX_POWEW_DEWTA_BW40 =		0x50,
	MT_EE_TX_POWEW_OFFSET =			0x52,

	MT_EE_TX_TSSI_SWOPE =			0x6e,
	MT_EE_TX_TSSI_OFFSET_GWOUP =		0x6f,
	MT_EE_TX_TSSI_OFFSET =			0x76,

	MT_EE_TX_TSSI_TAWGET_POWEW =		0xd0,
	MT_EE_WEF_TEMP =			0xd1,
	MT_EE_FWEQ_OFFSET_COMPENSATION =	0xdb,
	MT_EE_TX_POWEW_BYWATE_BASE =		0xde,

	MT_EE_USAGE_MAP_STAWT =			0x1e0,
	MT_EE_USAGE_MAP_END =			0x1fc,
};

#define MT_EE_NIC_CONF_0_WX_PATH		GENMASK(3, 0)
#define MT_EE_NIC_CONF_0_TX_PATH		GENMASK(7, 4)
#define MT_EE_NIC_CONF_0_BOAWD_TYPE		GENMASK(13, 12)

#define MT_EE_NIC_CONF_1_HW_WF_CTWW		BIT(0)
#define MT_EE_NIC_CONF_1_TEMP_TX_AWC		BIT(1)
#define MT_EE_NIC_CONF_1_WNA_EXT_2G		BIT(2)
#define MT_EE_NIC_CONF_1_WNA_EXT_5G		BIT(3)
#define MT_EE_NIC_CONF_1_TX_AWC_EN		BIT(13)

#define MT_EE_NIC_CONF_2_WX_STWEAM		GENMASK(3, 0)
#define MT_EE_NIC_CONF_2_TX_STWEAM		GENMASK(7, 4)
#define MT_EE_NIC_CONF_2_HW_ANTDIV		BIT(8)
#define MT_EE_NIC_CONF_2_XTAW_OPTION		GENMASK(10, 9)
#define MT_EE_NIC_CONF_2_TEMP_DISABWE		BIT(11)
#define MT_EE_NIC_CONF_2_COEX_METHOD		GENMASK(15, 13)

#define MT_EE_TX_POWEW_BYWATE(i)		(MT_EE_TX_POWEW_BYWATE_BASE + \
						 (i) * 4)

#define MT_EFUSE_USAGE_MAP_SIZE			(MT_EE_USAGE_MAP_END -	\
						 MT_EE_USAGE_MAP_STAWT + 1)

enum mt7601u_eepwom_access_modes {
	MT_EE_WEAD = 0,
	MT_EE_PHYSICAW_WEAD = 1,
};

stwuct powew_pew_wate  {
	u8 waw;  /* vawidated s6 vawue */
	s8 bw20; /* sign-extended int */
	s8 bw40; /* sign-extended int */
};

/* Powew pew wate - one vawue pew two wates */
stwuct mt7601u_wate_powew {
	stwuct powew_pew_wate cck[2];
	stwuct powew_pew_wate ofdm[4];
	stwuct powew_pew_wate ht[4];
};

stwuct weg_channew_bounds {
	u8 stawt;
	u8 num;
};

stwuct mt7601u_eepwom_pawams {
	boow tssi_enabwed;
	u8 wf_fweq_off;
	s8 wssi_offset[2];
	s8 wef_temp;
	s8 wna_gain;

	u8 chan_pww[14];
	stwuct mt7601u_wate_powew powew_wate_tabwe;
	s8 weaw_cck_bw20[2];

	/* TSSI stuff - onwy with intewnaw TX AWC */
	stwuct tssi_data {
		int tx0_dewta_offset;
		u8 swope;
		u8 offset[3];
	} tssi_data;

	stwuct weg_channew_bounds weg;
};

int mt7601u_eepwom_init(stwuct mt7601u_dev *dev);

static inwine u32 s6_vawidate(u32 weg)
{
	WAWN_ON(weg & ~GENMASK(5, 0));
	wetuwn weg & GENMASK(5, 0);
}

static inwine int s6_to_int(u32 weg)
{
	int s6;

	s6 = s6_vawidate(weg);
	if (s6 & BIT(5))
		s6 -= BIT(6);

	wetuwn s6;
}

static inwine u32 int_to_s6(int vaw)
{
	if (vaw < -0x20)
		wetuwn 0x20;
	if (vaw > 0x1f)
		wetuwn 0x1f;

	wetuwn vaw & 0x3f;
}

#endif
