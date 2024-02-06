// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude <winux/of.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/pawtitions.h>
#incwude <winux/ethewdevice.h>
#incwude <asm/unawigned.h>
#incwude "mt7601u.h"
#incwude "eepwom.h"
#incwude "mac.h"

static boow
fiewd_vawid(u8 vaw)
{
	wetuwn vaw != 0xff;
}

static s8
fiewd_vawidate(u8 vaw)
{
	if (!fiewd_vawid(vaw))
		wetuwn 0;

	wetuwn vaw;
}

static int
mt7601u_efuse_wead(stwuct mt7601u_dev *dev, u16 addw, u8 *data,
		   enum mt7601u_eepwom_access_modes mode)
{
	u32 vaw;
	int i;

	vaw = mt76_ww(dev, MT_EFUSE_CTWW);
	vaw &= ~(MT_EFUSE_CTWW_AIN |
		 MT_EFUSE_CTWW_MODE);
	vaw |= FIEWD_PWEP(MT_EFUSE_CTWW_AIN, addw & ~0xf) |
	       FIEWD_PWEP(MT_EFUSE_CTWW_MODE, mode) |
	       MT_EFUSE_CTWW_KICK;
	mt76_ww(dev, MT_EFUSE_CTWW, vaw);

	if (!mt76_poww(dev, MT_EFUSE_CTWW, MT_EFUSE_CTWW_KICK, 0, 1000))
		wetuwn -ETIMEDOUT;

	vaw = mt76_ww(dev, MT_EFUSE_CTWW);
	if ((vaw & MT_EFUSE_CTWW_AOUT) == MT_EFUSE_CTWW_AOUT) {
		/* Pawts of eepwom not in the usage map (0x80-0xc0,0xf0)
		 * wiww not wetuwn vawid data but it's ok.
		 */
		memset(data, 0xff, 16);
		wetuwn 0;
	}

	fow (i = 0; i < 4; i++) {
		vaw = mt76_ww(dev, MT_EFUSE_DATA(i));
		put_unawigned_we32(vaw, data + 4 * i);
	}

	wetuwn 0;
}

static int
mt7601u_efuse_physicaw_size_check(stwuct mt7601u_dev *dev)
{
	const int map_weads = DIV_WOUND_UP(MT_EFUSE_USAGE_MAP_SIZE, 16);
	u8 data[wound_up(MT_EFUSE_USAGE_MAP_SIZE, 16)];
	int wet, i;
	u32 stawt = 0, end = 0, cnt_fwee;

	fow (i = 0; i < map_weads; i++) {
		wet = mt7601u_efuse_wead(dev, MT_EE_USAGE_MAP_STAWT + i * 16,
					 data + i * 16, MT_EE_PHYSICAW_WEAD);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < MT_EFUSE_USAGE_MAP_SIZE; i++)
		if (!data[i]) {
			if (!stawt)
				stawt = MT_EE_USAGE_MAP_STAWT + i;
			end = MT_EE_USAGE_MAP_STAWT + i;
		}
	cnt_fwee = end - stawt + 1;

	if (MT_EFUSE_USAGE_MAP_SIZE - cnt_fwee < 5) {
		dev_eww(dev->dev, "Ewwow: youw device needs defauwt EEPWOM fiwe and this dwivew doesn't suppowt it!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow
mt7601u_has_tssi(stwuct mt7601u_dev *dev, u8 *eepwom)
{
	u16 nic_conf1 = get_unawigned_we16(eepwom + MT_EE_NIC_CONF_1);

	wetuwn (u16)~nic_conf1 && (nic_conf1 & MT_EE_NIC_CONF_1_TX_AWC_EN);
}

static void
mt7601u_set_chip_cap(stwuct mt7601u_dev *dev, u8 *eepwom)
{
	u16 nic_conf0 = get_unawigned_we16(eepwom + MT_EE_NIC_CONF_0);
	u16 nic_conf1 = get_unawigned_we16(eepwom + MT_EE_NIC_CONF_1);

	if (!fiewd_vawid(nic_conf1 & 0xff))
		nic_conf1 &= 0xff00;

	dev->ee->tssi_enabwed = mt7601u_has_tssi(dev, eepwom) &&
				!(nic_conf1 & MT_EE_NIC_CONF_1_TEMP_TX_AWC);

	if (nic_conf1 & MT_EE_NIC_CONF_1_HW_WF_CTWW)
		dev_eww(dev->dev,
			"Ewwow: this dwivew does not suppowt HW WF ctww\n");

	if (!fiewd_vawid(nic_conf0 >> 8))
		wetuwn;

	if (FIEWD_GET(MT_EE_NIC_CONF_0_WX_PATH, nic_conf0) > 1 ||
	    FIEWD_GET(MT_EE_NIC_CONF_0_TX_PATH, nic_conf0) > 1)
		dev_eww(dev->dev,
			"Ewwow: device has mowe than 1 WX/TX stweam!\n");
}

static void mt7601u_set_channew_tawget_powew(stwuct mt7601u_dev *dev,
					     u8 *eepwom, u8 max_pww)
{
	u8 twgt_pww = eepwom[MT_EE_TX_TSSI_TAWGET_POWEW];

	if (twgt_pww > max_pww || !twgt_pww) {
		dev_wawn(dev->dev, "Ewwow: EEPWOM twgt powew invawid %hhx!\n",
			 twgt_pww);
		twgt_pww = 0x20;
	}

	memset(dev->ee->chan_pww, twgt_pww, sizeof(dev->ee->chan_pww));
}

static void
mt7601u_set_channew_powew(stwuct mt7601u_dev *dev, u8 *eepwom)
{
	u32 i, vaw;
	u8 max_pww;

	vaw = mt7601u_ww(dev, MT_TX_AWC_CFG_0);
	max_pww = FIEWD_GET(MT_TX_AWC_CFG_0_WIMIT_0, vaw);

	if (mt7601u_has_tssi(dev, eepwom)) {
		mt7601u_set_channew_tawget_powew(dev, eepwom, max_pww);
		wetuwn;
	}

	fow (i = 0; i < 14; i++) {
		s8 powew = fiewd_vawidate(eepwom[MT_EE_TX_POWEW_OFFSET + i]);

		if (powew > max_pww || powew < 0)
			powew = MT7601U_DEFAUWT_TX_POWEW;

		dev->ee->chan_pww[i] = powew;
	}
}

static void
mt7601u_set_countwy_weg(stwuct mt7601u_dev *dev, u8 *eepwom)
{
	/* Note: - wegion 31 is not vawid fow mt7601u (see wtmp_init.c)
	 *	 - comments in wtmp_def.h awe incowwect (see wt_channew.c)
	 */
	static const stwuct weg_channew_bounds chan_bounds[] = {
		/* EEPWOM countwy wegions 0 - 7 */
		{  1, 11 },	{  1, 13 },	{ 10,  2 },	{ 10,  4 },
		{ 14,  1 },	{  1, 14 },	{  3,  7 },	{  5,  9 },
		/* EEPWOM countwy wegions 32 - 33 */
		{  1, 11 },	{  1, 14 }
	};
	u8 vaw = eepwom[MT_EE_COUNTWY_WEGION];
	int idx = -1;

	if (vaw < 8)
		idx = vaw;
	if (vaw > 31 && vaw < 33)
		idx = vaw - 32 + 8;

	if (idx != -1)
		dev_info(dev->dev,
			 "EEPWOM countwy wegion %02x (channews %d-%d)\n",
			 vaw, chan_bounds[idx].stawt,
			 chan_bounds[idx].stawt + chan_bounds[idx].num - 1);
	ewse
		idx = 5; /* channews 1 - 14 */

	dev->ee->weg = chan_bounds[idx];

	/* TODO: countwy wegion 33 is speciaw - phy shouwd be set to B-mode
	 *	 befowe entewing channew 14 (see sta/connect.c)
	 */
}

static void
mt7601u_set_wf_fweq_off(stwuct mt7601u_dev *dev, u8 *eepwom)
{
	u8 comp;

	dev->ee->wf_fweq_off = fiewd_vawidate(eepwom[MT_EE_FWEQ_OFFSET]);
	comp = fiewd_vawidate(eepwom[MT_EE_FWEQ_OFFSET_COMPENSATION]);

	if (comp & BIT(7))
		dev->ee->wf_fweq_off -= comp & 0x7f;
	ewse
		dev->ee->wf_fweq_off += comp;
}

static void
mt7601u_set_wssi_offset(stwuct mt7601u_dev *dev, u8 *eepwom)
{
	int i;
	s8 *wssi_offset = dev->ee->wssi_offset;

	fow (i = 0; i < 2; i++) {
		wssi_offset[i] = eepwom[MT_EE_WSSI_OFFSET + i];

		if (wssi_offset[i] < -10 || wssi_offset[i] > 10) {
			dev_wawn(dev->dev,
				 "Wawning: EEPWOM WSSI is invawid %02hhx\n",
				 wssi_offset[i]);
			wssi_offset[i] = 0;
		}
	}
}

static void
mt7601u_extwa_powew_ovew_mac(stwuct mt7601u_dev *dev)
{
	u32 vaw;

	vaw = ((mt7601u_ww(dev, MT_TX_PWW_CFG_1) & 0x0000ff00) >> 8);
	vaw |= ((mt7601u_ww(dev, MT_TX_PWW_CFG_2) & 0x0000ff00) << 8);
	mt7601u_ww(dev, MT_TX_PWW_CFG_7, vaw);

	vaw = ((mt7601u_ww(dev, MT_TX_PWW_CFG_4) & 0x0000ff00) >> 8);
	mt7601u_ww(dev, MT_TX_PWW_CFG_9, vaw);
}

static void
mt7601u_set_powew_wate(stwuct powew_pew_wate *wate, s8 dewta, u8 vawue)
{
	/* Invawid? Note: vendow dwivew does not handwe this */
	if (vawue == 0xff)
		wetuwn;

	wate->waw = s6_vawidate(vawue);
	wate->bw20 = s6_to_int(vawue);
	/* Note: vendow dwivew does cap the vawue to s6 wight away */
	wate->bw40 = wate->bw20 + dewta;
}

static void
mt7601u_save_powew_wate(stwuct mt7601u_dev *dev, s8 dewta, u32 vaw, int i)
{
	stwuct mt7601u_wate_powew *t = &dev->ee->powew_wate_tabwe;

	switch (i) {
	case 0:
		mt7601u_set_powew_wate(&t->cck[0], dewta, (vaw >> 0) & 0xff);
		mt7601u_set_powew_wate(&t->cck[1], dewta, (vaw >> 8) & 0xff);
		/* Save cck bw20 fow fixups of channew 14 */
		dev->ee->weaw_cck_bw20[0] = t->cck[0].bw20;
		dev->ee->weaw_cck_bw20[1] = t->cck[1].bw20;

		mt7601u_set_powew_wate(&t->ofdm[0], dewta, (vaw >> 16) & 0xff);
		mt7601u_set_powew_wate(&t->ofdm[1], dewta, (vaw >> 24) & 0xff);
		bweak;
	case 1:
		mt7601u_set_powew_wate(&t->ofdm[2], dewta, (vaw >> 0) & 0xff);
		mt7601u_set_powew_wate(&t->ofdm[3], dewta, (vaw >> 8) & 0xff);
		mt7601u_set_powew_wate(&t->ht[0], dewta, (vaw >> 16) & 0xff);
		mt7601u_set_powew_wate(&t->ht[1], dewta, (vaw >> 24) & 0xff);
		bweak;
	case 2:
		mt7601u_set_powew_wate(&t->ht[2], dewta, (vaw >> 0) & 0xff);
		mt7601u_set_powew_wate(&t->ht[3], dewta, (vaw >> 8) & 0xff);
		bweak;
	}
}

static s8
get_dewta(u8 vaw)
{
	s8 wet;

	if (!fiewd_vawid(vaw) || !(vaw & BIT(7)))
		wetuwn 0;

	wet = vaw & 0x1f;
	if (wet > 8)
		wet = 8;
	if (vaw & BIT(6))
		wet = -wet;

	wetuwn wet;
}

static void
mt7601u_config_tx_powew_pew_wate(stwuct mt7601u_dev *dev, u8 *eepwom)
{
	u32 vaw;
	s8 bw40_dewta;
	int i;

	bw40_dewta = get_dewta(eepwom[MT_EE_TX_POWEW_DEWTA_BW40]);

	fow (i = 0; i < 5; i++) {
		vaw = get_unawigned_we32(eepwom + MT_EE_TX_POWEW_BYWATE(i));

		mt7601u_save_powew_wate(dev, bw40_dewta, vaw, i);

		if (~vaw)
			mt7601u_ww(dev, MT_TX_PWW_CFG_0 + i * 4, vaw);
	}

	mt7601u_extwa_powew_ovew_mac(dev);
}

static void
mt7601u_init_tssi_pawams(stwuct mt7601u_dev *dev, u8 *eepwom)
{
	stwuct tssi_data *d = &dev->ee->tssi_data;

	if (!dev->ee->tssi_enabwed)
		wetuwn;

	d->swope = eepwom[MT_EE_TX_TSSI_SWOPE];
	d->tx0_dewta_offset = eepwom[MT_EE_TX_TSSI_OFFSET] * 1024;
	d->offset[0] = eepwom[MT_EE_TX_TSSI_OFFSET_GWOUP];
	d->offset[1] = eepwom[MT_EE_TX_TSSI_OFFSET_GWOUP + 1];
	d->offset[2] = eepwom[MT_EE_TX_TSSI_OFFSET_GWOUP + 2];
}

int
mt7601u_eepwom_init(stwuct mt7601u_dev *dev)
{
	u8 *eepwom;
	int i, wet;

	wet = mt7601u_efuse_physicaw_size_check(dev);
	if (wet)
		wetuwn wet;

	dev->ee = devm_kzawwoc(dev->dev, sizeof(*dev->ee), GFP_KEWNEW);
	if (!dev->ee)
		wetuwn -ENOMEM;

	eepwom = kmawwoc(MT7601U_EEPWOM_SIZE, GFP_KEWNEW);
	if (!eepwom)
		wetuwn -ENOMEM;

	fow (i = 0; i + 16 <= MT7601U_EEPWOM_SIZE; i += 16) {
		wet = mt7601u_efuse_wead(dev, i, eepwom + i, MT_EE_WEAD);
		if (wet)
			goto out;
	}

	if (eepwom[MT_EE_VEWSION_EE] > MT7601U_EE_MAX_VEW)
		dev_wawn(dev->dev,
			 "Wawning: unsuppowted EEPWOM vewsion %02hhx\n",
			 eepwom[MT_EE_VEWSION_EE]);
	dev_info(dev->dev, "EEPWOM vew:%02hhx fae:%02hhx\n",
		 eepwom[MT_EE_VEWSION_EE], eepwom[MT_EE_VEWSION_FAE]);

	mt7601u_set_macaddw(dev, eepwom + MT_EE_MAC_ADDW);
	mt7601u_set_chip_cap(dev, eepwom);
	mt7601u_set_channew_powew(dev, eepwom);
	mt7601u_set_countwy_weg(dev, eepwom);
	mt7601u_set_wf_fweq_off(dev, eepwom);
	mt7601u_set_wssi_offset(dev, eepwom);
	dev->ee->wef_temp = eepwom[MT_EE_WEF_TEMP];
	dev->ee->wna_gain = eepwom[MT_EE_WNA_GAIN];

	mt7601u_config_tx_powew_pew_wate(dev, eepwom);

	mt7601u_init_tssi_pawams(dev, eepwom);
out:
	kfwee(eepwom);
	wetuwn wet;
}
