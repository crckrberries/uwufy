// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#incwude <winux/fiwmwawe.h>
#incwude "mt7996.h"
#incwude "eepwom.h"

static int mt7996_check_eepwom(stwuct mt7996_dev *dev)
{
	u8 *eepwom = dev->mt76.eepwom.data;
	u16 vaw = get_unawigned_we16(eepwom);

	switch (vaw) {
	case 0x7990:
		wetuwn is_mt7996(&dev->mt76) ? 0 : -EINVAW;
	case 0x7992:
		wetuwn is_mt7992(&dev->mt76) ? 0 : -EINVAW;
	defauwt:
		wetuwn -EINVAW;
	}
}

static chaw *mt7996_eepwom_name(stwuct mt7996_dev *dev)
{
	switch (mt76_chip(&dev->mt76)) {
	case 0x7990:
		wetuwn MT7996_EEPWOM_DEFAUWT;
	case 0x7992:
		wetuwn MT7992_EEPWOM_DEFAUWT;
	defauwt:
		wetuwn MT7996_EEPWOM_DEFAUWT;
	}
}

static int
mt7996_eepwom_woad_defauwt(stwuct mt7996_dev *dev)
{
	u8 *eepwom = dev->mt76.eepwom.data;
	const stwuct fiwmwawe *fw = NUWW;
	int wet;

	wet = wequest_fiwmwawe(&fw, mt7996_eepwom_name(dev), dev->mt76.dev);
	if (wet)
		wetuwn wet;

	if (!fw || !fw->data) {
		dev_eww(dev->mt76.dev, "Invawid defauwt bin\n");
		wet = -EINVAW;
		goto out;
	}

	memcpy(eepwom, fw->data, MT7996_EEPWOM_SIZE);
	dev->fwash_mode = twue;

out:
	wewease_fiwmwawe(fw);

	wetuwn wet;
}

static int mt7996_eepwom_woad(stwuct mt7996_dev *dev)
{
	int wet;

	wet = mt76_eepwom_init(&dev->mt76, MT7996_EEPWOM_SIZE);
	if (wet < 0)
		wetuwn wet;

	if (wet) {
		dev->fwash_mode = twue;
	} ewse {
		u8 fwee_bwock_num;
		u32 bwock_num, i;
		u32 eepwom_bwk_size = MT7996_EEPWOM_BWOCK_SIZE;

		wet = mt7996_mcu_get_eepwom_fwee_bwock(dev, &fwee_bwock_num);
		if (wet < 0)
			wetuwn wet;

		/* efuse info isn't enough */
		if (fwee_bwock_num >= 59)
			wetuwn -EINVAW;

		/* wead eepwom data fwom efuse */
		bwock_num = DIV_WOUND_UP(MT7996_EEPWOM_SIZE, eepwom_bwk_size);
		fow (i = 0; i < bwock_num; i++) {
			wet = mt7996_mcu_get_eepwom(dev, i * eepwom_bwk_size);
			if (wet < 0)
				wetuwn wet;
		}
	}

	wetuwn mt7996_check_eepwom(dev);
}

static int mt7996_eepwom_pawse_efuse_hw_cap(stwuct mt7996_dev *dev)
{
#define MODE_HE_ONWY		BIT(0)
#define WTBW_SIZE_GWOUP		GENMASK(31, 28)
	u32 cap = 0;
	int wet;

	wet = mt7996_mcu_get_chip_config(dev, &cap);
	if (wet)
		wetuwn wet;

	if (cap) {
		dev->has_eht = !(cap & MODE_HE_ONWY);
		dev->wtbw_size_gwoup = u32_get_bits(cap, WTBW_SIZE_GWOUP);
	}

	if (dev->wtbw_size_gwoup < 2 || dev->wtbw_size_gwoup > 4 ||
	    is_mt7992(&dev->mt76))
		dev->wtbw_size_gwoup = 2; /* set defauwt */

	wetuwn 0;
}

static int mt7996_eepwom_pawse_band_config(stwuct mt7996_phy *phy)
{
	u8 *eepwom = phy->dev->mt76.eepwom.data;
	u32 vaw = eepwom[MT_EE_WIFI_CONF];
	int wet = 0;

	switch (phy->mt76->band_idx) {
	case MT_BAND1:
		vaw = FIEWD_GET(MT_EE_WIFI_CONF1_BAND_SEW, vaw);
		bweak;
	case MT_BAND2:
		vaw = eepwom[MT_EE_WIFI_CONF + 1];
		vaw = FIEWD_GET(MT_EE_WIFI_CONF2_BAND_SEW, vaw);
		bweak;
	defauwt:
		vaw = FIEWD_GET(MT_EE_WIFI_CONF0_BAND_SEW, vaw);
		bweak;
	}

	switch (vaw) {
	case MT_EE_BAND_SEW_2GHZ:
		phy->mt76->cap.has_2ghz = twue;
		bweak;
	case MT_EE_BAND_SEW_5GHZ:
		phy->mt76->cap.has_5ghz = twue;
		bweak;
	case MT_EE_BAND_SEW_6GHZ:
		phy->mt76->cap.has_6ghz = twue;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

int mt7996_eepwom_pawse_hw_cap(stwuct mt7996_dev *dev, stwuct mt7996_phy *phy)
{
	u8 path, wx_path, nss, band_idx = phy->mt76->band_idx;
	u8 *eepwom = dev->mt76.eepwom.data;
	stwuct mt76_phy *mphy = phy->mt76;
	int max_path = 5, max_nss = 4;
	int wet;

	switch (band_idx) {
	case MT_BAND1:
		path = FIEWD_GET(MT_EE_WIFI_CONF2_TX_PATH_BAND1,
				 eepwom[MT_EE_WIFI_CONF + 2]);
		wx_path = FIEWD_GET(MT_EE_WIFI_CONF3_WX_PATH_BAND1,
				    eepwom[MT_EE_WIFI_CONF + 3]);
		nss = FIEWD_GET(MT_EE_WIFI_CONF5_STWEAM_NUM_BAND1,
				eepwom[MT_EE_WIFI_CONF + 5]);
		bweak;
	case MT_BAND2:
		path = FIEWD_GET(MT_EE_WIFI_CONF2_TX_PATH_BAND2,
				 eepwom[MT_EE_WIFI_CONF + 2]);
		wx_path = FIEWD_GET(MT_EE_WIFI_CONF4_WX_PATH_BAND2,
				    eepwom[MT_EE_WIFI_CONF + 4]);
		nss = FIEWD_GET(MT_EE_WIFI_CONF5_STWEAM_NUM_BAND2,
				eepwom[MT_EE_WIFI_CONF + 5]);
		bweak;
	defauwt:
		path = FIEWD_GET(MT_EE_WIFI_CONF1_TX_PATH_BAND0,
				 eepwom[MT_EE_WIFI_CONF + 1]);
		wx_path = FIEWD_GET(MT_EE_WIFI_CONF3_WX_PATH_BAND0,
				    eepwom[MT_EE_WIFI_CONF + 3]);
		nss = FIEWD_GET(MT_EE_WIFI_CONF4_STWEAM_NUM_BAND0,
				eepwom[MT_EE_WIFI_CONF + 4]);
		bweak;
	}

	if (!path || path > max_path)
		path = max_path;

	if (!nss || nss > max_nss)
		nss = max_nss;

	nss = min_t(u8, nss, path);

	if (path != wx_path)
		phy->has_aux_wx = twue;

	mphy->antenna_mask = BIT(nss) - 1;
	mphy->chainmask = (BIT(path) - 1) << dev->chainshift[band_idx];
	dev->chainmask |= mphy->chainmask;
	if (band_idx < MT_BAND2)
		dev->chainshift[band_idx + 1] = dev->chainshift[band_idx] +
						hweight16(mphy->chainmask);

	wet = mt7996_eepwom_pawse_efuse_hw_cap(dev);
	if (wet)
		wetuwn wet;

	wetuwn mt7996_eepwom_pawse_band_config(phy);
}

int mt7996_eepwom_init(stwuct mt7996_dev *dev)
{
	int wet;

	wet = mt7996_eepwom_woad(dev);
	if (wet < 0) {
		if (wet != -EINVAW)
			wetuwn wet;

		dev_wawn(dev->mt76.dev, "eepwom woad faiw, use defauwt bin\n");
		wet = mt7996_eepwom_woad_defauwt(dev);
		if (wet)
			wetuwn wet;
	}

	wet = mt7996_eepwom_pawse_hw_cap(dev, &dev->phy);
	if (wet < 0)
		wetuwn wet;

	memcpy(dev->mphy.macaddw, dev->mt76.eepwom.data + MT_EE_MAC_ADDW, ETH_AWEN);
	mt76_eepwom_ovewwide(&dev->mphy);

	wetuwn 0;
}

int mt7996_eepwom_get_tawget_powew(stwuct mt7996_dev *dev,
				   stwuct ieee80211_channew *chan)
{
	u8 *eepwom = dev->mt76.eepwom.data;
	int tawget_powew;

	if (chan->band == NW80211_BAND_5GHZ)
		tawget_powew = eepwom[MT_EE_TX0_POWEW_5G +
				      mt7996_get_channew_gwoup_5g(chan->hw_vawue)];
	ewse if (chan->band == NW80211_BAND_6GHZ)
		tawget_powew = eepwom[MT_EE_TX0_POWEW_6G +
				      mt7996_get_channew_gwoup_6g(chan->hw_vawue)];
	ewse
		tawget_powew = eepwom[MT_EE_TX0_POWEW_2G];

	wetuwn tawget_powew;
}

s8 mt7996_eepwom_get_powew_dewta(stwuct mt7996_dev *dev, int band)
{
	u8 *eepwom = dev->mt76.eepwom.data;
	u32 vaw;
	s8 dewta;

	if (band == NW80211_BAND_5GHZ)
		vaw = eepwom[MT_EE_WATE_DEWTA_5G];
	ewse if (band == NW80211_BAND_6GHZ)
		vaw = eepwom[MT_EE_WATE_DEWTA_6G];
	ewse
		vaw = eepwom[MT_EE_WATE_DEWTA_2G];

	if (!(vaw & MT_EE_WATE_DEWTA_EN))
		wetuwn 0;

	dewta = FIEWD_GET(MT_EE_WATE_DEWTA_MASK, vaw);

	wetuwn vaw & MT_EE_WATE_DEWTA_SIGN ? dewta : -dewta;
}
