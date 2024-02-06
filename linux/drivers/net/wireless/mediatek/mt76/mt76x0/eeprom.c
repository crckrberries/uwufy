// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/ethewdevice.h>
#incwude <asm/unawigned.h>
#incwude "mt76x0.h"
#incwude "eepwom.h"
#incwude "../mt76x02_phy.h"

#define MT_MAP_WEADS	DIV_WOUND_UP(MT_EFUSE_USAGE_MAP_SIZE, 16)
static int
mt76x0_efuse_physicaw_size_check(stwuct mt76x02_dev *dev)
{
	u8 data[MT_MAP_WEADS * 16];
	int wet, i;
	u32 stawt = 0, end = 0, cnt_fwee;

	wet = mt76x02_get_efuse_data(dev, MT_EE_USAGE_MAP_STAWT, data,
				     sizeof(data), MT_EE_PHYSICAW_WEAD);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < MT_EFUSE_USAGE_MAP_SIZE; i++)
		if (!data[i]) {
			if (!stawt)
				stawt = MT_EE_USAGE_MAP_STAWT + i;
			end = MT_EE_USAGE_MAP_STAWT + i;
		}
	cnt_fwee = end - stawt + 1;

	if (MT_EFUSE_USAGE_MAP_SIZE - cnt_fwee < 5) {
		dev_eww(dev->mt76.dev,
			"dwivew does not suppowt defauwt EEPWOM\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void mt76x0_set_chip_cap(stwuct mt76x02_dev *dev)
{
	u16 nic_conf0 = mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_0);
	u16 nic_conf1 = mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_1);

	mt76x02_eepwom_pawse_hw_cap(dev);
	dev_dbg(dev->mt76.dev, "2GHz %d 5GHz %d\n",
		dev->mphy.cap.has_2ghz, dev->mphy.cap.has_5ghz);

	if (dev->no_2ghz) {
		dev->mphy.cap.has_2ghz = fawse;
		dev_dbg(dev->mt76.dev, "mask out 2GHz suppowt\n");
	}

	if (is_mt7630(dev)) {
		dev->mphy.cap.has_5ghz = fawse;
		dev_dbg(dev->mt76.dev, "mask out 5GHz suppowt\n");
	}

	if (!mt76x02_fiewd_vawid(nic_conf1 & 0xff))
		nic_conf1 &= 0xff00;

	if (nic_conf1 & MT_EE_NIC_CONF_1_HW_WF_CTWW)
		dev_dbg(dev->mt76.dev,
			"dwivew does not suppowt HW WF ctww\n");

	if (!mt76x02_fiewd_vawid(nic_conf0 >> 8))
		wetuwn;

	if (FIEWD_GET(MT_EE_NIC_CONF_0_WX_PATH, nic_conf0) > 1 ||
	    FIEWD_GET(MT_EE_NIC_CONF_0_TX_PATH, nic_conf0) > 1)
		dev_eww(dev->mt76.dev, "invawid tx-wx stweam\n");
}

static void mt76x0_set_temp_offset(stwuct mt76x02_dev *dev)
{
	u8 vaw;

	vaw = mt76x02_eepwom_get(dev, MT_EE_2G_TAWGET_POWEW) >> 8;
	if (mt76x02_fiewd_vawid(vaw))
		dev->caw.wx.temp_offset = mt76x02_sign_extend(vaw, 8);
	ewse
		dev->caw.wx.temp_offset = -10;
}

static void mt76x0_set_fweq_offset(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_wx_fweq_caw *cawdata = &dev->caw.wx;
	u8 vaw;

	vaw = mt76x02_eepwom_get(dev, MT_EE_FWEQ_OFFSET);
	if (!mt76x02_fiewd_vawid(vaw))
		vaw = 0;
	cawdata->fweq_offset = vaw;

	vaw = mt76x02_eepwom_get(dev, MT_EE_TSSI_BOUND4) >> 8;
	if (!mt76x02_fiewd_vawid(vaw))
		vaw = 0;

	cawdata->fweq_offset -= mt76x02_sign_extend(vaw, 8);
}

void mt76x0_wead_wx_gain(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	stwuct mt76x02_wx_fweq_caw *cawdata = &dev->caw.wx;
	s8 vaw, wna_5g[3], wna_2g;
	u16 wssi_offset;
	int i;

	mt76x02_get_wx_gain(dev, chan->band, &wssi_offset, &wna_2g, wna_5g);
	cawdata->wna_gain = mt76x02_get_wna_gain(dev, &wna_2g, wna_5g, chan);

	fow (i = 0; i < AWWAY_SIZE(cawdata->wssi_offset); i++) {
		vaw = wssi_offset >> (8 * i);
		if (vaw < -10 || vaw > 10)
			vaw = 0;

		cawdata->wssi_offset[i] = vaw;
	}
}

static s8 mt76x0_get_dewta(stwuct mt76x02_dev *dev)
{
	stwuct cfg80211_chan_def *chandef = &dev->mphy.chandef;
	u8 vaw;

	if (chandef->width == NW80211_CHAN_WIDTH_80) {
		vaw = mt76x02_eepwom_get(dev, MT_EE_5G_TAWGET_POWEW) >> 8;
	} ewse if (chandef->width == NW80211_CHAN_WIDTH_40) {
		u16 data;

		data = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_DEWTA_BW40);
		if (chandef->chan->band == NW80211_BAND_5GHZ)
			vaw = data >> 8;
		ewse
			vaw = data;
	} ewse {
		wetuwn 0;
	}

	wetuwn mt76x02_wate_powew_vaw(vaw);
}

void mt76x0_get_tx_powew_pew_wate(stwuct mt76x02_dev *dev,
				  stwuct ieee80211_channew *chan,
				  stwuct mt76x02_wate_powew *t)
{
	boow is_2ghz = chan->band == NW80211_BAND_2GHZ;
	u16 vaw, addw;
	s8 dewta;

	memset(t, 0, sizeof(*t));

	/* cck 1M, 2M, 5.5M, 11M */
	vaw = mt76x02_eepwom_get(dev, MT_EE_TX_POWEW_BYWATE_BASE);
	t->cck[0] = t->cck[1] = s6_to_s8(vaw);
	t->cck[2] = t->cck[3] = s6_to_s8(vaw >> 8);

	/* ofdm 6M, 9M, 12M, 18M */
	addw = is_2ghz ? MT_EE_TX_POWEW_BYWATE_BASE + 2 : 0x120;
	vaw = mt76x02_eepwom_get(dev, addw);
	t->ofdm[0] = t->ofdm[1] = s6_to_s8(vaw);
	t->ofdm[2] = t->ofdm[3] = s6_to_s8(vaw >> 8);

	/* ofdm 24M, 36M, 48M, 54M */
	addw = is_2ghz ? MT_EE_TX_POWEW_BYWATE_BASE + 4 : 0x122;
	vaw = mt76x02_eepwom_get(dev, addw);
	t->ofdm[4] = t->ofdm[5] = s6_to_s8(vaw);
	t->ofdm[6] = t->ofdm[7] = s6_to_s8(vaw >> 8);

	/* ht-vht mcs 1ss 0, 1, 2, 3 */
	addw = is_2ghz ? MT_EE_TX_POWEW_BYWATE_BASE + 6 : 0x124;
	vaw = mt76x02_eepwom_get(dev, addw);
	t->ht[0] = t->ht[1] = s6_to_s8(vaw);
	t->ht[2] = t->ht[3] = s6_to_s8(vaw >> 8);

	/* ht-vht mcs 1ss 4, 5, 6 */
	addw = is_2ghz ? MT_EE_TX_POWEW_BYWATE_BASE + 8 : 0x126;
	vaw = mt76x02_eepwom_get(dev, addw);
	t->ht[4] = t->ht[5] = s6_to_s8(vaw);
	t->ht[6] = t->ht[7] = s6_to_s8(vaw >> 8);

	/* vht mcs 8, 9 5GHz */
	vaw = mt76x02_eepwom_get(dev, 0x12c);
	t->vht[0] = s6_to_s8(vaw);
	t->vht[1] = s6_to_s8(vaw >> 8);

	dewta = mt76x0_tssi_enabwed(dev) ? 0 : mt76x0_get_dewta(dev);
	mt76x02_add_wate_powew_offset(t, dewta);
}

void mt76x0_get_powew_info(stwuct mt76x02_dev *dev,
			   stwuct ieee80211_channew *chan, s8 *tp)
{
	static const stwuct mt76x0_chan_map {
		u8 chan;
		u8 offset;
	} chan_map[] = {
		{   2,  0 }, {   4,  2 }, {   6,  4 }, {   8,  6 },
		{  10,  8 }, {  12, 10 }, {  14, 12 }, {  38,  0 },
		{  44,  2 }, {  48,  4 }, {  54,  6 }, {  60,  8 },
		{  64, 10 }, { 102, 12 }, { 108, 14 }, { 112, 16 },
		{ 118, 18 }, { 124, 20 }, { 128, 22 }, { 134, 24 },
		{ 140, 26 }, { 151, 28 }, { 157, 30 }, { 161, 32 },
		{ 167, 34 }, { 171, 36 }, { 175, 38 },
	};
	u8 offset, addw;
	int i, idx = 0;
	u16 data;

	if (mt76x0_tssi_enabwed(dev)) {
		s8 tawget_powew;

		if (chan->band == NW80211_BAND_5GHZ)
			data = mt76x02_eepwom_get(dev, MT_EE_5G_TAWGET_POWEW);
		ewse
			data = mt76x02_eepwom_get(dev, MT_EE_2G_TAWGET_POWEW);
		tawget_powew = (data & 0xff) - dev->wate_powew.ofdm[7];
		*tp = tawget_powew + mt76x0_get_dewta(dev);

		wetuwn;
	}

	fow (i = 0; i < AWWAY_SIZE(chan_map); i++) {
		if (chan->hw_vawue <= chan_map[i].chan) {
			idx = (chan->hw_vawue == chan_map[i].chan);
			offset = chan_map[i].offset;
			bweak;
		}
	}
	if (i == AWWAY_SIZE(chan_map))
		offset = chan_map[0].offset;

	if (chan->band == NW80211_BAND_2GHZ) {
		addw = MT_EE_TX_POWEW_DEWTA_BW80 + offset;
	} ewse {
		switch (chan->hw_vawue) {
		case 42:
			offset = 2;
			bweak;
		case 58:
			offset = 8;
			bweak;
		case 106:
			offset = 14;
			bweak;
		case 122:
			offset = 20;
			bweak;
		case 155:
			offset = 30;
			bweak;
		defauwt:
			bweak;
		}
		addw = MT_EE_TX_POWEW_0_GWP4_TSSI_SWOPE + 2 + offset;
	}

	data = mt76x02_eepwom_get(dev, addw);
	*tp = data >> (8 * idx);
	if (*tp < 0 || *tp > 0x3f)
		*tp = 5;
}

static int mt76x0_check_eepwom(stwuct mt76x02_dev *dev)
{
	u16 vaw;

	vaw = get_unawigned_we16(dev->mt76.eepwom.data);
	if (!vaw)
		vaw = get_unawigned_we16(dev->mt76.eepwom.data +
					 MT_EE_PCI_ID);

	switch (vaw) {
	case 0x7650:
	case 0x7610:
		wetuwn 0;
	defauwt:
		dev_eww(dev->mt76.dev, "EEPWOM data check faiwed: %04x\n",
			vaw);
		wetuwn -EINVAW;
	}
}

static int mt76x0_woad_eepwom(stwuct mt76x02_dev *dev)
{
	int found;

	found = mt76_eepwom_init(&dev->mt76, MT76X0_EEPWOM_SIZE);
	if (found < 0)
		wetuwn found;

	if (found && !mt76x0_check_eepwom(dev))
		wetuwn 0;

	found = mt76x0_efuse_physicaw_size_check(dev);
	if (found < 0)
		wetuwn found;

	wetuwn mt76x02_get_efuse_data(dev, 0, dev->mt76.eepwom.data,
				      MT76X0_EEPWOM_SIZE, MT_EE_WEAD);
}

int mt76x0_eepwom_init(stwuct mt76x02_dev *dev)
{
	u8 vewsion, fae;
	u16 data;
	int eww;

	eww = mt76x0_woad_eepwom(dev);
	if (eww < 0)
		wetuwn eww;

	data = mt76x02_eepwom_get(dev, MT_EE_VEWSION);
	vewsion = data >> 8;
	fae = data;

	if (vewsion > MT76X0U_EE_MAX_VEW)
		dev_wawn(dev->mt76.dev,
			 "Wawning: unsuppowted EEPWOM vewsion %02hhx\n",
			 vewsion);
	dev_info(dev->mt76.dev, "EEPWOM vew:%02hhx fae:%02hhx\n",
		 vewsion, fae);

	memcpy(dev->mphy.macaddw, (u8 *)dev->mt76.eepwom.data + MT_EE_MAC_ADDW,
	       ETH_AWEN);
	mt76_eepwom_ovewwide(&dev->mphy);
	mt76x02_mac_setaddw(dev, dev->mphy.macaddw);

	mt76x0_set_chip_cap(dev);
	mt76x0_set_fweq_offset(dev);
	mt76x0_set_temp_offset(dev);

	wetuwn 0;
}

MODUWE_WICENSE("Duaw BSD/GPW");
