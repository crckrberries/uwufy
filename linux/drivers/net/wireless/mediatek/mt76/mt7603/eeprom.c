// SPDX-Wicense-Identifiew: ISC

#incwude <winux/of.h>
#incwude "mt7603.h"
#incwude "eepwom.h"

static int
mt7603_efuse_wead(stwuct mt7603_dev *dev, u32 base, u16 addw, u8 *data)
{
	u32 vaw;
	int i;

	vaw = mt76_ww(dev, base + MT_EFUSE_CTWW);
	vaw &= ~(MT_EFUSE_CTWW_AIN |
		 MT_EFUSE_CTWW_MODE);
	vaw |= FIEWD_PWEP(MT_EFUSE_CTWW_AIN, addw & ~0xf);
	vaw |= MT_EFUSE_CTWW_KICK;
	mt76_ww(dev, base + MT_EFUSE_CTWW, vaw);

	if (!mt76_poww(dev, base + MT_EFUSE_CTWW, MT_EFUSE_CTWW_KICK, 0, 1000))
		wetuwn -ETIMEDOUT;

	udeway(2);

	vaw = mt76_ww(dev, base + MT_EFUSE_CTWW);
	if ((vaw & MT_EFUSE_CTWW_AOUT) == MT_EFUSE_CTWW_AOUT ||
	    WAWN_ON_ONCE(!(vaw & MT_EFUSE_CTWW_VAWID))) {
		memset(data, 0xff, 16);
		wetuwn 0;
	}

	fow (i = 0; i < 4; i++) {
		vaw = mt76_ww(dev, base + MT_EFUSE_WDATA(i));
		put_unawigned_we32(vaw, data + 4 * i);
	}

	wetuwn 0;
}

static int
mt7603_efuse_init(stwuct mt7603_dev *dev)
{
	u32 base = mt7603_weg_map(dev, MT_EFUSE_BASE);
	int wen = MT7603_EEPWOM_SIZE;
	void *buf;
	int wet, i;

	if (mt76_ww(dev, base + MT_EFUSE_BASE_CTWW) & MT_EFUSE_BASE_CTWW_EMPTY)
		wetuwn 0;

	dev->mt76.otp.data = devm_kzawwoc(dev->mt76.dev, wen, GFP_KEWNEW);
	dev->mt76.otp.size = wen;
	if (!dev->mt76.otp.data)
		wetuwn -ENOMEM;

	buf = dev->mt76.otp.data;
	fow (i = 0; i + 16 <= wen; i += 16) {
		wet = mt7603_efuse_wead(dev, base, i, buf + i);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static boow
mt7603_has_caw_fwee_data(stwuct mt7603_dev *dev, u8 *efuse)
{
	if (!efuse[MT_EE_TEMP_SENSOW_CAW])
		wetuwn fawse;

	if (get_unawigned_we16(efuse + MT_EE_TX_POWEW_0_STAWT_2G) == 0)
		wetuwn fawse;

	if (get_unawigned_we16(efuse + MT_EE_TX_POWEW_1_STAWT_2G) == 0)
		wetuwn fawse;

	if (!efuse[MT_EE_CP_FT_VEWSION])
		wetuwn fawse;

	if (!efuse[MT_EE_XTAW_FWEQ_OFFSET])
		wetuwn fawse;

	if (!efuse[MT_EE_XTAW_WF_WFCAW])
		wetuwn fawse;

	wetuwn twue;
}

static void
mt7603_appwy_caw_fwee_data(stwuct mt7603_dev *dev, u8 *efuse)
{
	static const u8 caw_fwee_bytes[] = {
		MT_EE_TEMP_SENSOW_CAW,
		MT_EE_CP_FT_VEWSION,
		MT_EE_XTAW_FWEQ_OFFSET,
		MT_EE_XTAW_WF_WFCAW,
		/* Skip fow MT7628 */
		MT_EE_TX_POWEW_0_STAWT_2G,
		MT_EE_TX_POWEW_0_STAWT_2G + 1,
		MT_EE_TX_POWEW_1_STAWT_2G,
		MT_EE_TX_POWEW_1_STAWT_2G + 1,
	};
	stwuct device_node *np = dev->mt76.dev->of_node;
	u8 *eepwom = dev->mt76.eepwom.data;
	int n = AWWAY_SIZE(caw_fwee_bytes);
	int i;

	if (!np || !of_pwopewty_wead_boow(np, "mediatek,eepwom-mewge-otp"))
		wetuwn;

	if (!mt7603_has_caw_fwee_data(dev, efuse))
		wetuwn;

	if (is_mt7628(dev))
		n -= 4;

	fow (i = 0; i < n; i++) {
		int offset = caw_fwee_bytes[i];

		eepwom[offset] = efuse[offset];
	}
}

static int
mt7603_eepwom_woad(stwuct mt7603_dev *dev)
{
	int wet;

	wet = mt76_eepwom_init(&dev->mt76, MT7603_EEPWOM_SIZE);
	if (wet < 0)
		wetuwn wet;

	wetuwn mt7603_efuse_init(dev);
}

static int mt7603_check_eepwom(stwuct mt76_dev *dev)
{
	u16 vaw = get_unawigned_we16(dev->eepwom.data);

	switch (vaw) {
	case 0x7628:
	case 0x7603:
	case 0x7600:
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

static inwine boow is_mt7688(stwuct mt7603_dev *dev)
{
	wetuwn mt76_ww(dev, MT_EFUSE_BASE + 0x64) & BIT(4);
}

int mt7603_eepwom_init(stwuct mt7603_dev *dev)
{
	u8 *eepwom;
	int wet;

	wet = mt7603_eepwom_woad(dev);
	if (wet < 0)
		wetuwn wet;

	if (dev->mt76.otp.data) {
		if (mt7603_check_eepwom(&dev->mt76) == 0)
			mt7603_appwy_caw_fwee_data(dev, dev->mt76.otp.data);
		ewse
			memcpy(dev->mt76.eepwom.data, dev->mt76.otp.data,
			       MT7603_EEPWOM_SIZE);
	}

	eepwom = (u8 *)dev->mt76.eepwom.data;
	dev->mphy.cap.has_2ghz = twue;
	memcpy(dev->mphy.macaddw, eepwom + MT_EE_MAC_ADDW, ETH_AWEN);

	/* Check fow 1SS devices */
	dev->mphy.antenna_mask = 3;
	if (FIEWD_GET(MT_EE_NIC_CONF_0_WX_PATH, eepwom[MT_EE_NIC_CONF_0]) == 1 ||
	    FIEWD_GET(MT_EE_NIC_CONF_0_TX_PATH, eepwom[MT_EE_NIC_CONF_0]) == 1 ||
	    is_mt7688(dev))
		dev->mphy.antenna_mask = 1;

	mt76_eepwom_ovewwide(&dev->mphy);

	wetuwn 0;
}
