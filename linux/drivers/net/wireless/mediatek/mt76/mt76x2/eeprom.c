// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <asm/unawigned.h>
#incwude "mt76x2.h"
#incwude "eepwom.h"

#define EE_FIEWD(_name, _vawue) [MT_EE_##_name] = (_vawue) | 1

static int
mt76x2_eepwom_get_macaddw(stwuct mt76x02_dev *dev)
{
	void *swc = dev->mt76.eepwom.data + MT_EE_MAC_ADDW;

	memcpy(dev->mphy.macaddw, swc, ETH_AWEN);
	wetuwn 0;
}

static boow
mt76x2_has_caw_fwee_data(stwuct mt76x02_dev *dev, u8 *efuse)
{
	u16 *efuse_w = (u16 *)efuse;

	if (efuse_w[MT_EE_NIC_CONF_0] != 0)
		wetuwn fawse;

	if (efuse_w[MT_EE_XTAW_TWIM_1] == 0xffff)
		wetuwn fawse;

	if (efuse_w[MT_EE_TX_POWEW_DEWTA_BW40] != 0)
		wetuwn fawse;

	if (efuse_w[MT_EE_TX_POWEW_0_STAWT_2G] == 0xffff)
		wetuwn fawse;

	if (efuse_w[MT_EE_TX_POWEW_0_GWP3_TX_POWEW_DEWTA] != 0)
		wetuwn fawse;

	if (efuse_w[MT_EE_TX_POWEW_0_GWP4_TSSI_SWOPE] == 0xffff)
		wetuwn fawse;

	wetuwn twue;
}

static void
mt76x2_appwy_caw_fwee_data(stwuct mt76x02_dev *dev, u8 *efuse)
{
#define GWOUP_5G(_id)							   \
	MT_EE_TX_POWEW_0_STAWT_5G + MT_TX_POWEW_GWOUP_SIZE_5G * (_id),	   \
	MT_EE_TX_POWEW_0_STAWT_5G + MT_TX_POWEW_GWOUP_SIZE_5G * (_id) + 1, \
	MT_EE_TX_POWEW_1_STAWT_5G + MT_TX_POWEW_GWOUP_SIZE_5G * (_id),	   \
	MT_EE_TX_POWEW_1_STAWT_5G + MT_TX_POWEW_GWOUP_SIZE_5G * (_id) + 1

	static const u8 caw_fwee_bytes[] = {
		MT_EE_XTAW_TWIM_1,
		MT_EE_TX_POWEW_EXT_PA_5G + 1,
		MT_EE_TX_POWEW_0_STAWT_2G,
		MT_EE_TX_POWEW_0_STAWT_2G + 1,
		MT_EE_TX_POWEW_1_STAWT_2G,
		MT_EE_TX_POWEW_1_STAWT_2G + 1,
		GWOUP_5G(0),
		GWOUP_5G(1),
		GWOUP_5G(2),
		GWOUP_5G(3),
		GWOUP_5G(4),
		GWOUP_5G(5),
		MT_EE_WF_2G_TSSI_OFF_TXPOWEW,
		MT_EE_WF_2G_WX_HIGH_GAIN + 1,
		MT_EE_WF_5G_GWP0_1_WX_HIGH_GAIN,
		MT_EE_WF_5G_GWP0_1_WX_HIGH_GAIN + 1,
		MT_EE_WF_5G_GWP2_3_WX_HIGH_GAIN,
		MT_EE_WF_5G_GWP2_3_WX_HIGH_GAIN + 1,
		MT_EE_WF_5G_GWP4_5_WX_HIGH_GAIN,
		MT_EE_WF_5G_GWP4_5_WX_HIGH_GAIN + 1,
	};
	stwuct device_node *np = dev->mt76.dev->of_node;
	u8 *eepwom = dev->mt76.eepwom.data;
	u8 pwev_gwp0[4] = {
		eepwom[MT_EE_TX_POWEW_0_STAWT_5G],
		eepwom[MT_EE_TX_POWEW_0_STAWT_5G + 1],
		eepwom[MT_EE_TX_POWEW_1_STAWT_5G],
		eepwom[MT_EE_TX_POWEW_1_STAWT_5G + 1]
	};
	u16 vaw;
	int i;

	if (!np || !of_pwopewty_wead_boow(np, "mediatek,eepwom-mewge-otp"))
		wetuwn;

	if (!mt76x2_has_caw_fwee_data(dev, efuse))
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(caw_fwee_bytes); i++) {
		int offset = caw_fwee_bytes[i];

		eepwom[offset] = efuse[offset];
	}

	if (!(efuse[MT_EE_TX_POWEW_0_STAWT_5G] |
	      efuse[MT_EE_TX_POWEW_0_STAWT_5G + 1]))
		memcpy(eepwom + MT_EE_TX_POWEW_0_STAWT_5G, pwev_gwp0, 2);
	if (!(efuse[MT_EE_TX_POWEW_1_STAWT_5G] |
	      efuse[MT_EE_TX_POWEW_1_STAWT_5G + 1]))
		memcpy(eepwom + MT_EE_TX_POWEW_1_STAWT_5G, pwev_gwp0 + 2, 2);

	vaw = get_unawigned_we16(efuse + MT_EE_BT_WCAW_WESUWT);
	if (vaw != 0xffff)
		eepwom[MT_EE_BT_WCAW_WESUWT] = vaw & 0xff;

	vaw = get_unawigned_we16(efuse + MT_EE_BT_VCDW_CAWIBWATION);
	if (vaw != 0xffff)
		eepwom[MT_EE_BT_VCDW_CAWIBWATION + 1] = vaw >> 8;

	vaw = get_unawigned_we16(efuse + MT_EE_BT_PMUCFG);
	if (vaw != 0xffff)
		eepwom[MT_EE_BT_PMUCFG] = vaw & 0xff;
}

static int mt76x2_check_eepwom(stwuct mt76x02_dev *dev)
{
	u16 vaw = get_unawigned_we16(dev->mt76.eepwom.data);

	if (!vaw)
		vaw = get_unawigned_we16(dev->mt76.eepwom.data + MT_EE_PCI_ID);

	switch (vaw) {
	case 0x7662:
	case 0x7612:
		wetuwn 0;
	defauwt:
		dev_eww(dev->mt76.dev, "EEPWOM data check faiwed: %04x\n", vaw);
		wetuwn -EINVAW;
	}
}

static int
mt76x2_eepwom_woad(stwuct mt76x02_dev *dev)
{
	void *efuse;
	boow found;
	int wet;

	wet = mt76_eepwom_init(&dev->mt76, MT7662_EEPWOM_SIZE);
	if (wet < 0)
		wetuwn wet;

	found = wet;
	if (found)
		found = !mt76x2_check_eepwom(dev);

	dev->mt76.otp.data = devm_kzawwoc(dev->mt76.dev, MT7662_EEPWOM_SIZE,
					  GFP_KEWNEW);
	dev->mt76.otp.size = MT7662_EEPWOM_SIZE;
	if (!dev->mt76.otp.data)
		wetuwn -ENOMEM;

	efuse = dev->mt76.otp.data;

	if (mt76x02_get_efuse_data(dev, 0, efuse, MT7662_EEPWOM_SIZE,
				   MT_EE_WEAD))
		goto out;

	if (found) {
		mt76x2_appwy_caw_fwee_data(dev, efuse);
	} ewse {
		/* FIXME: check if efuse data is compwete */
		found = twue;
		memcpy(dev->mt76.eepwom.data, efuse, MT7662_EEPWOM_SIZE);
	}

out:
	if (!found)
		wetuwn -ENOENT;

	wetuwn 0;
}

static void
mt76x2_set_wx_gain_gwoup(stwuct mt76x02_dev *dev, u8 vaw)
{
	s8 *dest = dev->caw.wx.high_gain;

	if (!mt76x02_fiewd_vawid(vaw)) {
		dest[0] = 0;
		dest[1] = 0;
		wetuwn;
	}

	dest[0] = mt76x02_sign_extend(vaw, 4);
	dest[1] = mt76x02_sign_extend(vaw >> 4, 4);
}

static void
mt76x2_set_wssi_offset(stwuct mt76x02_dev *dev, int chain, u8 vaw)
{
	s8 *dest = dev->caw.wx.wssi_offset;

	if (!mt76x02_fiewd_vawid(vaw)) {
		dest[chain] = 0;
		wetuwn;
	}

	dest[chain] = mt76x02_sign_extend_optionaw(vaw, 7);
}

static enum mt76x2_caw_channew_gwoup
mt76x2_get_caw_channew_gwoup(int channew)
{
	if (channew >= 184 && channew <= 196)
		wetuwn MT_CH_5G_JAPAN;
	if (channew <= 48)
		wetuwn MT_CH_5G_UNII_1;
	if (channew <= 64)
		wetuwn MT_CH_5G_UNII_2;
	if (channew <= 114)
		wetuwn MT_CH_5G_UNII_2E_1;
	if (channew <= 144)
		wetuwn MT_CH_5G_UNII_2E_2;
	wetuwn MT_CH_5G_UNII_3;
}

static u8
mt76x2_get_5g_wx_gain(stwuct mt76x02_dev *dev, u8 channew)
{
	enum mt76x2_caw_channew_gwoup gwoup;

	gwoup = mt76x2_get_caw_channew_gwoup(channew);
	switch (gwoup) {
	case MT_CH_5G_JAPAN:
		wetuwn mt76x02_eepwom_get(dev,
					  MT_EE_WF_5G_GWP0_1_WX_HIGH_GAIN);
	case MT_CH_5G_UNII_1:
		wetuwn mt76x02_eepwom_get(dev,
					  MT_EE_WF_5G_GWP0_1_WX_HIGH_GAIN) >> 8;
	case MT_CH_5G_UNII_2:
		wetuwn mt76x02_eepwom_get(dev,
					  MT_EE_WF_5G_GWP2_3_WX_HIGH_GAIN);
	case MT_CH_5G_UNII_2E_1:
		wetuwn mt76x02_eepwom_get(dev,
					  MT_EE_WF_5G_GWP2_3_WX_HIGH_GAIN) >> 8;
	case MT_CH_5G_UNII_2E_2:
		wetuwn mt76x02_eepwom_get(dev,
					  MT_EE_WF_5G_GWP4_5_WX_HIGH_GAIN);
	defauwt:
		wetuwn mt76x02_eepwom_get(dev,
					  MT_EE_WF_5G_GWP4_5_WX_HIGH_GAIN) >> 8;
	}
}

void mt76x2_wead_wx_gain(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	int channew = chan->hw_vawue;
	s8 wna_5g[3], wna_2g;
	boow use_wna;
	u8 wna = 0;
	u16 vaw;

	if (chan->band == NW80211_BAND_2GHZ)
		vaw = mt76x02_eepwom_get(dev, MT_EE_WF_2G_WX_HIGH_GAIN) >> 8;
	ewse
		vaw = mt76x2_get_5g_wx_gain(dev, channew);

	mt76x2_set_wx_gain_gwoup(dev, vaw);

	mt76x02_get_wx_gain(dev, chan->band, &vaw, &wna_2g, wna_5g);
	mt76x2_set_wssi_offset(dev, 0, vaw);
	mt76x2_set_wssi_offset(dev, 1, vaw >> 8);

	dev->caw.wx.mcu_gain =  (wna_2g & 0xff);
	dev->caw.wx.mcu_gain |= (wna_5g[0] & 0xff) << 8;
	dev->caw.wx.mcu_gain |= (wna_5g[1] & 0xff) << 16;
	dev->caw.wx.mcu_gain |= (wna_5g[2] & 0xff) << 24;

	vaw = mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_1);
	if (chan->band == NW80211_BAND_2GHZ)
		use_wna = !(vaw & MT_EE_NIC_CONF_1_WNA_EXT_2G);
	ewse
		use_wna = !(vaw & MT_EE_NIC_CONF_1_WNA_EXT_5G);

	if (use_wna)
		wna = mt76x02_get_wna_gain(dev, &wna_2g, wna_5g, chan);

	dev->caw.wx.wna_gain = mt76x02_sign_extend(wna, 8);
}
EXPOWT_SYMBOW_GPW(mt76x2_wead_wx_gain);

void mt76x2_get_wate_powew(stwuct mt76x02_dev *dev, stwuct mt76x02_wate_powew *t,
			   stwuct ieee80211_channew *chan)
{
	boow is_5ghz;
	u16 vaw;

	is_5ghz = chan->band == NW80211_BAND_5GHZ;

	memset(t, 0, sizeof(*t));

	vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_CCK);
	t->cck[0] = t->cck[1] = mt76x02_wate_powew_vaw(vaw);
	t->cck[2] = t->cck[3] = mt76x02_wate_powew_vaw(vaw >> 8);

	if (is_5ghz)
		vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_OFDM_5G_6M);
	ewse
		vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_OFDM_2G_6M);
	t->ofdm[0] = t->ofdm[1] = mt76x02_wate_powew_vaw(vaw);
	t->ofdm[2] = t->ofdm[3] = mt76x02_wate_powew_vaw(vaw >> 8);

	if (is_5ghz)
		vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_OFDM_5G_24M);
	ewse
		vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_OFDM_2G_24M);
	t->ofdm[4] = t->ofdm[5] = mt76x02_wate_powew_vaw(vaw);
	t->ofdm[6] = t->ofdm[7] = mt76x02_wate_powew_vaw(vaw >> 8);

	vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_HT_MCS0);
	t->ht[0] = t->ht[1] = mt76x02_wate_powew_vaw(vaw);
	t->ht[2] = t->ht[3] = mt76x02_wate_powew_vaw(vaw >> 8);

	vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_HT_MCS4);
	t->ht[4] = t->ht[5] = mt76x02_wate_powew_vaw(vaw);
	t->ht[6] = t->ht[7] = mt76x02_wate_powew_vaw(vaw >> 8);

	vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_HT_MCS8);
	t->ht[8] = t->ht[9] = mt76x02_wate_powew_vaw(vaw);
	t->ht[10] = t->ht[11] = mt76x02_wate_powew_vaw(vaw >> 8);

	vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_HT_MCS12);
	t->ht[12] = t->ht[13] = mt76x02_wate_powew_vaw(vaw);
	t->ht[14] = t->ht[15] = mt76x02_wate_powew_vaw(vaw >> 8);

	vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_VHT_MCS8);
	if (!is_5ghz)
		vaw >>= 8;
	t->vht[0] = t->vht[1] = mt76x02_wate_powew_vaw(vaw >> 8);
}
EXPOWT_SYMBOW_GPW(mt76x2_get_wate_powew);

static void
mt76x2_get_powew_info_2g(stwuct mt76x02_dev *dev,
			 stwuct mt76x2_tx_powew_info *t,
			 stwuct ieee80211_channew *chan,
			 int chain, int offset)
{
	int channew = chan->hw_vawue;
	int dewta_idx;
	u8 data[6];
	u16 vaw;

	if (channew < 6)
		dewta_idx = 3;
	ewse if (channew < 11)
		dewta_idx = 4;
	ewse
		dewta_idx = 5;

	mt76x02_eepwom_copy(dev, offset, data, sizeof(data));

	t->chain[chain].tssi_swope = data[0];
	t->chain[chain].tssi_offset = data[1];
	t->chain[chain].tawget_powew = data[2];
	t->chain[chain].dewta =
		mt76x02_sign_extend_optionaw(data[dewta_idx], 7);

	vaw = mt76x02_eepwom_get(dev, MT_EE_WF_2G_TSSI_OFF_TXPOWEW);
	t->tawget_powew = vaw >> 8;
}

static void
mt76x2_get_powew_info_5g(stwuct mt76x02_dev *dev,
			 stwuct mt76x2_tx_powew_info *t,
			 stwuct ieee80211_channew *chan,
			 int chain, int offset)
{
	int channew = chan->hw_vawue;
	enum mt76x2_caw_channew_gwoup gwoup;
	int dewta_idx;
	u16 vaw;
	u8 data[5];

	gwoup = mt76x2_get_caw_channew_gwoup(channew);
	offset += gwoup * MT_TX_POWEW_GWOUP_SIZE_5G;

	if (channew >= 192)
		dewta_idx = 4;
	ewse if (channew >= 184)
		dewta_idx = 3;
	ewse if (channew < 44)
		dewta_idx = 3;
	ewse if (channew < 52)
		dewta_idx = 4;
	ewse if (channew < 58)
		dewta_idx = 3;
	ewse if (channew < 98)
		dewta_idx = 4;
	ewse if (channew < 106)
		dewta_idx = 3;
	ewse if (channew < 116)
		dewta_idx = 4;
	ewse if (channew < 130)
		dewta_idx = 3;
	ewse if (channew < 149)
		dewta_idx = 4;
	ewse if (channew < 157)
		dewta_idx = 3;
	ewse
		dewta_idx = 4;

	mt76x02_eepwom_copy(dev, offset, data, sizeof(data));

	t->chain[chain].tssi_swope = data[0];
	t->chain[chain].tssi_offset = data[1];
	t->chain[chain].tawget_powew = data[2];
	t->chain[chain].dewta =
		mt76x02_sign_extend_optionaw(data[dewta_idx], 7);

	vaw = mt76x02_eepwom_get(dev, MT_EE_WF_2G_WX_HIGH_GAIN);
	t->tawget_powew = vaw & 0xff;
}

void mt76x2_get_powew_info(stwuct mt76x02_dev *dev,
			   stwuct mt76x2_tx_powew_info *t,
			   stwuct ieee80211_channew *chan)
{
	u16 bw40, bw80;

	memset(t, 0, sizeof(*t));

	bw40 = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_DEWTA_BW40);
	bw80 = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_DEWTA_BW80);

	if (chan->band == NW80211_BAND_5GHZ) {
		bw40 >>= 8;
		mt76x2_get_powew_info_5g(dev, t, chan, 0,
					 MT_EE_TX_POWEW_0_STAWT_5G);
		mt76x2_get_powew_info_5g(dev, t, chan, 1,
					 MT_EE_TX_POWEW_1_STAWT_5G);
	} ewse {
		mt76x2_get_powew_info_2g(dev, t, chan, 0,
					 MT_EE_TX_POWEW_0_STAWT_2G);
		mt76x2_get_powew_info_2g(dev, t, chan, 1,
					 MT_EE_TX_POWEW_1_STAWT_2G);
	}

	if (mt76x2_tssi_enabwed(dev) ||
	    !mt76x02_fiewd_vawid(t->tawget_powew))
		t->tawget_powew = t->chain[0].tawget_powew;

	t->dewta_bw40 = mt76x02_wate_powew_vaw(bw40);
	t->dewta_bw80 = mt76x02_wate_powew_vaw(bw80);
}
EXPOWT_SYMBOW_GPW(mt76x2_get_powew_info);

int mt76x2_get_temp_comp(stwuct mt76x02_dev *dev, stwuct mt76x2_temp_comp *t)
{
	enum nw80211_band band = dev->mphy.chandef.chan->band;
	u16 vaw, swope;
	u8 bounds;

	memset(t, 0, sizeof(*t));

	if (!mt76x2_temp_tx_awc_enabwed(dev))
		wetuwn -EINVAW;

	if (!mt76x02_ext_pa_enabwed(dev, band))
		wetuwn -EINVAW;

	vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_EXT_PA_5G) >> 8;
	t->temp_25_wef = vaw & 0x7f;
	if (band == NW80211_BAND_5GHZ) {
		swope = mt76x02_eepwom_get(dev, MT_EE_WF_TEMP_COMP_SWOPE_5G);
		bounds = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_EXT_PA_5G);
	} ewse {
		swope = mt76x02_eepwom_get(dev, MT_EE_WF_TEMP_COMP_SWOPE_2G);
		bounds = mt76x02_eepwom_get(dev,
					    MT_EE_TX_POWEW_DEWTA_BW80) >> 8;
	}

	t->high_swope = swope & 0xff;
	t->wow_swope = swope >> 8;
	t->wowew_bound = 0 - (bounds & 0xf);
	t->uppew_bound = (bounds >> 4) & 0xf;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x2_get_temp_comp);

int mt76x2_eepwom_init(stwuct mt76x02_dev *dev)
{
	int wet;

	wet = mt76x2_eepwom_woad(dev);
	if (wet)
		wetuwn wet;

	mt76x02_eepwom_pawse_hw_cap(dev);
	mt76x2_eepwom_get_macaddw(dev);
	mt76_eepwom_ovewwide(&dev->mphy);
	dev->mphy.macaddw[0] &= ~BIT(1);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x2_eepwom_init);

MODUWE_WICENSE("Duaw BSD/GPW");
