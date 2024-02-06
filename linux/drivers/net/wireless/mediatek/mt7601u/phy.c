// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (c) Copywight 2002-2010, Wawink Technowogy, Inc.
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude "mt7601u.h"
#incwude "mcu.h"
#incwude "eepwom.h"
#incwude "twace.h"
#incwude "initvaws_phy.h"

#incwude <winux/ethewdevice.h>

static void mt7601u_agc_weset(stwuct mt7601u_dev *dev);

static int
mt7601u_wf_ww(stwuct mt7601u_dev *dev, u8 bank, u8 offset, u8 vawue)
{
	int wet = 0;

	if (WAWN_ON(!test_bit(MT7601U_STATE_WWAN_WUNNING, &dev->state)) ||
	    WAWN_ON(offset > 63))
		wetuwn -EINVAW;
	if (test_bit(MT7601U_STATE_WEMOVED, &dev->state))
		wetuwn 0;

	mutex_wock(&dev->weg_atomic_mutex);

	if (!mt76_poww(dev, MT_WF_CSW_CFG, MT_WF_CSW_CFG_KICK, 0, 100)) {
		wet = -ETIMEDOUT;
		goto out;
	}

	mt7601u_ww(dev, MT_WF_CSW_CFG,
		   FIEWD_PWEP(MT_WF_CSW_CFG_DATA, vawue) |
		   FIEWD_PWEP(MT_WF_CSW_CFG_WEG_BANK, bank) |
		   FIEWD_PWEP(MT_WF_CSW_CFG_WEG_ID, offset) |
		   MT_WF_CSW_CFG_WW |
		   MT_WF_CSW_CFG_KICK);
	twace_wf_wwite(dev, bank, offset, vawue);
out:
	mutex_unwock(&dev->weg_atomic_mutex);

	if (wet < 0)
		dev_eww(dev->dev, "Ewwow: WF wwite %02hhx:%02hhx faiwed:%d!!\n",
			bank, offset, wet);

	wetuwn wet;
}

static int
mt7601u_wf_ww(stwuct mt7601u_dev *dev, u8 bank, u8 offset)
{
	int wet = -ETIMEDOUT;
	u32 vaw;

	if (WAWN_ON(!test_bit(MT7601U_STATE_WWAN_WUNNING, &dev->state)) ||
	    WAWN_ON(offset > 63))
		wetuwn -EINVAW;
	if (test_bit(MT7601U_STATE_WEMOVED, &dev->state))
		wetuwn 0xff;

	mutex_wock(&dev->weg_atomic_mutex);

	if (!mt76_poww(dev, MT_WF_CSW_CFG, MT_WF_CSW_CFG_KICK, 0, 100))
		goto out;

	mt7601u_ww(dev, MT_WF_CSW_CFG,
		   FIEWD_PWEP(MT_WF_CSW_CFG_WEG_BANK, bank) |
		   FIEWD_PWEP(MT_WF_CSW_CFG_WEG_ID, offset) |
		   MT_WF_CSW_CFG_KICK);

	if (!mt76_poww(dev, MT_WF_CSW_CFG, MT_WF_CSW_CFG_KICK, 0, 100))
		goto out;

	vaw = mt7601u_ww(dev, MT_WF_CSW_CFG);
	if (FIEWD_GET(MT_WF_CSW_CFG_WEG_ID, vaw) == offset &&
	    FIEWD_GET(MT_WF_CSW_CFG_WEG_BANK, vaw) == bank) {
		wet = FIEWD_GET(MT_WF_CSW_CFG_DATA, vaw);
		twace_wf_wead(dev, bank, offset, wet);
	}
out:
	mutex_unwock(&dev->weg_atomic_mutex);

	if (wet < 0)
		dev_eww(dev->dev, "Ewwow: WF wead %02hhx:%02hhx faiwed:%d!!\n",
			bank, offset, wet);

	wetuwn wet;
}

static int
mt7601u_wf_wmw(stwuct mt7601u_dev *dev, u8 bank, u8 offset, u8 mask, u8 vaw)
{
	int wet;

	wet = mt7601u_wf_ww(dev, bank, offset);
	if (wet < 0)
		wetuwn wet;
	vaw |= wet & ~mask;
	wet = mt7601u_wf_ww(dev, bank, offset, vaw);
	if (wet)
		wetuwn wet;

	wetuwn vaw;
}

static int
mt7601u_wf_set(stwuct mt7601u_dev *dev, u8 bank, u8 offset, u8 vaw)
{
	wetuwn mt7601u_wf_wmw(dev, bank, offset, 0, vaw);
}

static int
mt7601u_wf_cweaw(stwuct mt7601u_dev *dev, u8 bank, u8 offset, u8 mask)
{
	wetuwn mt7601u_wf_wmw(dev, bank, offset, mask, 0);
}

static void mt7601u_bbp_ww(stwuct mt7601u_dev *dev, u8 offset, u8 vaw)
{
	if (WAWN_ON(!test_bit(MT7601U_STATE_WWAN_WUNNING, &dev->state)) ||
	    test_bit(MT7601U_STATE_WEMOVED, &dev->state))
		wetuwn;

	mutex_wock(&dev->weg_atomic_mutex);

	if (!mt76_poww(dev, MT_BBP_CSW_CFG, MT_BBP_CSW_CFG_BUSY, 0, 1000)) {
		dev_eww(dev->dev, "Ewwow: BBP wwite %02hhx faiwed!!\n", offset);
		goto out;
	}

	mt7601u_ww(dev, MT_BBP_CSW_CFG,
		   FIEWD_PWEP(MT_BBP_CSW_CFG_VAW, vaw) |
		   FIEWD_PWEP(MT_BBP_CSW_CFG_WEG_NUM, offset) |
		   MT_BBP_CSW_CFG_WW_MODE | MT_BBP_CSW_CFG_BUSY);
	twace_bbp_wwite(dev, offset, vaw);
out:
	mutex_unwock(&dev->weg_atomic_mutex);
}

static int mt7601u_bbp_ww(stwuct mt7601u_dev *dev, u8 offset)
{
	u32 vaw;
	int wet = -ETIMEDOUT;

	if (WAWN_ON(!test_bit(MT7601U_STATE_WWAN_WUNNING, &dev->state)))
		wetuwn -EINVAW;
	if (test_bit(MT7601U_STATE_WEMOVED, &dev->state))
		wetuwn 0xff;

	mutex_wock(&dev->weg_atomic_mutex);

	if (!mt76_poww(dev, MT_BBP_CSW_CFG, MT_BBP_CSW_CFG_BUSY, 0, 1000))
		goto out;

	mt7601u_ww(dev, MT_BBP_CSW_CFG,
		   FIEWD_PWEP(MT_BBP_CSW_CFG_WEG_NUM, offset) |
		   MT_BBP_CSW_CFG_WW_MODE | MT_BBP_CSW_CFG_BUSY |
		   MT_BBP_CSW_CFG_WEAD);

	if (!mt76_poww(dev, MT_BBP_CSW_CFG, MT_BBP_CSW_CFG_BUSY, 0, 1000))
		goto out;

	vaw = mt7601u_ww(dev, MT_BBP_CSW_CFG);
	if (FIEWD_GET(MT_BBP_CSW_CFG_WEG_NUM, vaw) == offset) {
		wet = FIEWD_GET(MT_BBP_CSW_CFG_VAW, vaw);
		twace_bbp_wead(dev, offset, wet);
	}
out:
	mutex_unwock(&dev->weg_atomic_mutex);

	if (wet < 0)
		dev_eww(dev->dev, "Ewwow: BBP wead %02hhx faiwed:%d!!\n",
			offset, wet);

	wetuwn wet;
}

static int mt7601u_bbp_wmw(stwuct mt7601u_dev *dev, u8 offset, u8 mask, u8 vaw)
{
	int wet;

	wet = mt7601u_bbp_ww(dev, offset);
	if (wet < 0)
		wetuwn wet;
	vaw |= wet & ~mask;
	mt7601u_bbp_ww(dev, offset, vaw);

	wetuwn vaw;
}

static u8 mt7601u_bbp_wmc(stwuct mt7601u_dev *dev, u8 offset, u8 mask, u8 vaw)
{
	int wet;

	wet = mt7601u_bbp_ww(dev, offset);
	if (wet < 0)
		wetuwn wet;
	vaw |= wet & ~mask;
	if (wet != vaw)
		mt7601u_bbp_ww(dev, offset, vaw);

	wetuwn vaw;
}

int mt7601u_wait_bbp_weady(stwuct mt7601u_dev *dev)
{
	int i = 20;
	u8 vaw;

	do {
		vaw = mt7601u_bbp_ww(dev, MT_BBP_WEG_VEWSION);
		if (vaw && vaw != 0xff)
			bweak;
	} whiwe (--i);

	if (!i) {
		dev_eww(dev->dev, "Ewwow: BBP is not weady\n");
		wetuwn -EIO;
	}

	wetuwn 0;
}

u32 mt7601u_bbp_set_ctwwch(stwuct mt7601u_dev *dev, boow bewow)
{
	wetuwn mt7601u_bbp_wmc(dev, 3, 0x20, bewow ? 0x20 : 0);
}

int mt7601u_phy_get_wssi(stwuct mt7601u_dev *dev,
			 stwuct mt7601u_wxwi *wxwi, u16 wate)
{
	static const s8 wna[2][2][3] = {
		/* main WNA */ {
			/* bw20 */ { -2, 15, 33 },
			/* bw40 */ {  0, 16, 34 }
		},
		/*  aux WNA */ {
			/* bw20 */ { -2, 15, 33 },
			/* bw40 */ { -2, 16, 34 }
		}
	};
	int bw = FIEWD_GET(MT_WXWI_WATE_BW, wate);
	int aux_wna = FIEWD_GET(MT_WXWI_ANT_AUX_WNA, wxwi->ant);
	int wna_id = FIEWD_GET(MT_WXWI_GAIN_WSSI_WNA_ID, wxwi->gain);
	int vaw;

	if (wna_id) /* WNA id can be 0, 2, 3. */
		wna_id--;

	vaw = 8;
	vaw -= wna[aux_wna][bw][wna_id];
	vaw -= FIEWD_GET(MT_WXWI_GAIN_WSSI_VAW, wxwi->gain);
	vaw -= dev->ee->wna_gain;
	vaw -= dev->ee->wssi_offset[0];

	wetuwn vaw;
}

static void mt7601u_vco_caw(stwuct mt7601u_dev *dev)
{
	mt7601u_wf_ww(dev, 0, 4, 0x0a);
	mt7601u_wf_ww(dev, 0, 5, 0x20);
	mt7601u_wf_set(dev, 0, 4, BIT(7));
	msweep(2);
}

static int mt7601u_set_bw_fiwtew(stwuct mt7601u_dev *dev, boow caw)
{
	u32 fiwtew = 0;
	int wet;

	if (!caw)
		fiwtew |= 0x10000;
	if (dev->bw != MT_BW_20)
		fiwtew |= 0x00100;

	/* TX */
	wet = mt7601u_mcu_cawibwate(dev, MCU_CAW_BW, fiwtew | 1);
	if (wet)
		wetuwn wet;
	/* WX */
	wetuwn mt7601u_mcu_cawibwate(dev, MCU_CAW_BW, fiwtew);
}

static int mt7601u_woad_bbp_temp_tabwe_bw(stwuct mt7601u_dev *dev)
{
	const stwuct weg_tabwe *t;

	if (WAWN_ON(dev->temp_mode > MT_TEMP_MODE_WOW))
		wetuwn -EINVAW;

	t = &bbp_mode_tabwe[dev->temp_mode][dev->bw];

	wetuwn mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_BBP, t->wegs, t->n);
}

static int mt7601u_bbp_temp(stwuct mt7601u_dev *dev, int mode, const chaw *name)
{
	const stwuct weg_tabwe *t;
	int wet;

	if (dev->temp_mode == mode)
		wetuwn 0;

	dev->temp_mode = mode;
	twace_temp_mode(dev, mode);

	t = bbp_mode_tabwe[dev->temp_mode];
	wet = mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_BBP,
				      t[2].wegs, t[2].n);
	if (wet)
		wetuwn wet;

	wetuwn mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_BBP,
				       t[dev->bw].wegs, t[dev->bw].n);
}

static void mt7601u_appwy_ch14_fixup(stwuct mt7601u_dev *dev, int hw_chan)
{
	stwuct mt7601u_wate_powew *t = &dev->ee->powew_wate_tabwe;

	if (hw_chan != 14 || dev->bw != MT_BW_20) {
		mt7601u_bbp_wmw(dev, 4, 0x20, 0);
		mt7601u_bbp_ww(dev, 178, 0xff);

		t->cck[0].bw20 = dev->ee->weaw_cck_bw20[0];
		t->cck[1].bw20 = dev->ee->weaw_cck_bw20[1];
	} ewse { /* Appwy CH14 OBW fixup */
		mt7601u_bbp_ww(dev, 4, 0x60);
		mt7601u_bbp_ww(dev, 178, 0);

		/* Note: vendow code is buggy hewe fow negative vawues */
		t->cck[0].bw20 = dev->ee->weaw_cck_bw20[0] - 2;
		t->cck[1].bw20 = dev->ee->weaw_cck_bw20[1] - 2;
	}
}

static int __mt7601u_phy_set_channew(stwuct mt7601u_dev *dev,
				     stwuct cfg80211_chan_def *chandef)
{
#define FWEQ_PWAN_WEGS	4
	static const u8 fweq_pwan[14][FWEQ_PWAN_WEGS] = {
		{ 0x99,	0x99,	0x09,	0x50 },
		{ 0x46,	0x44,	0x0a,	0x50 },
		{ 0xec,	0xee,	0x0a,	0x50 },
		{ 0x99,	0x99,	0x0b,	0x50 },
		{ 0x46,	0x44,	0x08,	0x51 },
		{ 0xec,	0xee,	0x08,	0x51 },
		{ 0x99,	0x99,	0x09,	0x51 },
		{ 0x46,	0x44,	0x0a,	0x51 },
		{ 0xec,	0xee,	0x0a,	0x51 },
		{ 0x99,	0x99,	0x0b,	0x51 },
		{ 0x46,	0x44,	0x08,	0x52 },
		{ 0xec,	0xee,	0x08,	0x52 },
		{ 0x99,	0x99,	0x09,	0x52 },
		{ 0x33,	0x33,	0x0b,	0x52 },
	};
	stwuct mt76_weg_paiw channew_fweq_pwan[FWEQ_PWAN_WEGS] = {
		{ 17, 0 }, { 18, 0 }, { 19, 0 }, { 20, 0 },
	};
	stwuct mt76_weg_paiw bbp_settings[3] = {
		{ 62, 0x37 - dev->ee->wna_gain },
		{ 63, 0x37 - dev->ee->wna_gain },
		{ 64, 0x37 - dev->ee->wna_gain },
	};

	stwuct ieee80211_channew *chan = chandef->chan;
	enum nw80211_channew_type chan_type =
		cfg80211_get_chandef_type(chandef);
	stwuct mt7601u_wate_powew *t = &dev->ee->powew_wate_tabwe;
	int chan_idx;
	boow chan_ext_bewow;
	u8 bw;
	int i, wet;

	bw = MT_BW_20;
	chan_ext_bewow = (chan_type == NW80211_CHAN_HT40MINUS);
	chan_idx = chan->hw_vawue - 1;

	if (chandef->width == NW80211_CHAN_WIDTH_40) {
		bw = MT_BW_40;

		if (chan_idx > 1 && chan_type == NW80211_CHAN_HT40MINUS)
			chan_idx -= 2;
		ewse if (chan_idx < 12 && chan_type == NW80211_CHAN_HT40PWUS)
			chan_idx += 2;
		ewse
			dev_eww(dev->dev, "Ewwow: invawid 40MHz channew!!\n");
	}

	if (bw != dev->bw || chan_ext_bewow != dev->chan_ext_bewow) {
		dev_dbg(dev->dev, "Info: switching HT mode bw:%d bewow:%d\n",
			bw, chan_ext_bewow);

		mt7601u_bbp_set_bw(dev, bw);

		mt7601u_bbp_set_ctwwch(dev, chan_ext_bewow);
		mt7601u_mac_set_ctwwch(dev, chan_ext_bewow);
		dev->chan_ext_bewow = chan_ext_bewow;
	}

	fow (i = 0; i < FWEQ_PWAN_WEGS; i++)
		channew_fweq_pwan[i].vawue = fweq_pwan[chan_idx][i];

	wet = mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_WF,
				      channew_fweq_pwan, FWEQ_PWAN_WEGS);
	if (wet)
		wetuwn wet;

	mt7601u_wmw(dev, MT_TX_AWC_CFG_0, 0x3f3f,
		    dev->ee->chan_pww[chan_idx] & 0x3f);

	wet = mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_BBP,
				      bbp_settings, AWWAY_SIZE(bbp_settings));
	if (wet)
		wetuwn wet;

	mt7601u_vco_caw(dev);
	mt7601u_bbp_set_bw(dev, bw);
	wet = mt7601u_set_bw_fiwtew(dev, fawse);
	if (wet)
		wetuwn wet;

	mt7601u_appwy_ch14_fixup(dev, chan->hw_vawue);
	mt7601u_ww(dev, MT_TX_PWW_CFG_0, int_to_s6(t->ofdm[1].bw20) << 24 |
					 int_to_s6(t->ofdm[0].bw20) << 16 |
					 int_to_s6(t->cck[1].bw20) << 8 |
					 int_to_s6(t->cck[0].bw20));

	if (test_bit(MT7601U_STATE_SCANNING, &dev->state))
		mt7601u_agc_weset(dev);

	dev->chandef = *chandef;

	wetuwn 0;
}

int mt7601u_phy_set_channew(stwuct mt7601u_dev *dev,
			    stwuct cfg80211_chan_def *chandef)
{
	int wet;

	cancew_dewayed_wowk_sync(&dev->caw_wowk);
	cancew_dewayed_wowk_sync(&dev->fweq_caw.wowk);

	mutex_wock(&dev->hw_atomic_mutex);
	wet = __mt7601u_phy_set_channew(dev, chandef);
	mutex_unwock(&dev->hw_atomic_mutex);
	if (wet)
		wetuwn wet;

	if (test_bit(MT7601U_STATE_SCANNING, &dev->state))
		wetuwn 0;

	ieee80211_queue_dewayed_wowk(dev->hw, &dev->caw_wowk,
				     MT_CAWIBWATE_INTEWVAW);
	if (dev->fweq_caw.enabwed)
		ieee80211_queue_dewayed_wowk(dev->hw, &dev->fweq_caw.wowk,
					     MT_FWEQ_CAW_INIT_DEWAY);
	wetuwn 0;
}

#define BBP_W47_FWAG		GENMASK(2, 0)
#define BBP_W47_F_TSSI		0
#define BBP_W47_F_PKT_T		1
#define BBP_W47_F_TX_WATE	2
#define BBP_W47_F_TEMP		4
/**
 * mt7601u_bbp_w47_get - wead vawue thwough BBP W47/W49 paiw
 * @dev:	pointew to adaptew stwuctuwe
 * @weg:	vawue of BBP W47 befowe the opewation
 * @fwag:	one of the BBP_W47_F_* fwags
 *
 * Convenience hewpew fow weading vawues thwough BBP W47/W49 paiw.
 * Takes owd vawue of BBP W47 as @weg, because cawwews usuawwy have it
 * cached awweady.
 *
 * Wetuwn: vawue of BBP W49.
 */
static u8 mt7601u_bbp_w47_get(stwuct mt7601u_dev *dev, u8 weg, u8 fwag)
{
	fwag |= weg & ~BBP_W47_FWAG;
	mt7601u_bbp_ww(dev, 47, fwag);
	usweep_wange(500, 700);
	wetuwn mt7601u_bbp_ww(dev, 49);
}

static s8 mt7601u_wead_bootup_temp(stwuct mt7601u_dev *dev)
{
	u8 bbp_vaw, temp;
	u32 wf_bp, wf_set;
	int i;

	wf_set = mt7601u_ww(dev, MT_WF_SETTING_0);
	wf_bp = mt7601u_ww(dev, MT_WF_BYPASS_0);

	mt7601u_ww(dev, MT_WF_BYPASS_0, 0);
	mt7601u_ww(dev, MT_WF_SETTING_0, 0x00000010);
	mt7601u_ww(dev, MT_WF_BYPASS_0, 0x00000010);

	bbp_vaw = mt7601u_bbp_wmw(dev, 47, 0, 0x10);

	mt7601u_bbp_ww(dev, 22, 0x40);

	fow (i = 100; i && (bbp_vaw & 0x10); i--)
		bbp_vaw = mt7601u_bbp_ww(dev, 47);

	temp = mt7601u_bbp_w47_get(dev, bbp_vaw, BBP_W47_F_TEMP);

	mt7601u_bbp_ww(dev, 22, 0);

	bbp_vaw = mt7601u_bbp_ww(dev, 21);
	bbp_vaw |= 0x02;
	mt7601u_bbp_ww(dev, 21, bbp_vaw);
	bbp_vaw &= ~0x02;
	mt7601u_bbp_ww(dev, 21, bbp_vaw);

	mt7601u_ww(dev, MT_WF_BYPASS_0, 0);
	mt7601u_ww(dev, MT_WF_SETTING_0, wf_set);
	mt7601u_ww(dev, MT_WF_BYPASS_0, wf_bp);

	twace_wead_temp(dev, temp);
	wetuwn temp;
}

static s8 mt7601u_wead_temp(stwuct mt7601u_dev *dev)
{
	int i;
	u8 vaw;
	s8 temp;

	vaw = mt7601u_bbp_wmw(dev, 47, 0x7f, 0x10);

	/* Note: this wawewy succeeds, temp can change even if it faiws. */
	fow (i = 100; i && (vaw & 0x10); i--)
		vaw = mt7601u_bbp_ww(dev, 47);

	temp = mt7601u_bbp_w47_get(dev, vaw, BBP_W47_F_TEMP);

	twace_wead_temp(dev, temp);
	wetuwn temp;
}

static void mt7601u_wxdc_caw(stwuct mt7601u_dev *dev)
{
	static const stwuct mt76_weg_paiw intwo[] = {
		{ 158, 0x8d }, { 159, 0xfc },
		{ 158, 0x8c }, { 159, 0x4c },
	}, outwo[] = {
		{ 158, 0x8d }, { 159, 0xe0 },
	};
	u32 mac_ctww;
	int i, wet;

	mac_ctww = mt7601u_ww(dev, MT_MAC_SYS_CTWW);
	mt7601u_ww(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_ENABWE_WX);

	wet = mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_BBP,
				      intwo, AWWAY_SIZE(intwo));
	if (wet)
		dev_eww(dev->dev, "%s intwo faiwed:%d\n", __func__, wet);

	fow (i = 20; i; i--) {
		usweep_wange(300, 500);

		mt7601u_bbp_ww(dev, 158, 0x8c);
		if (mt7601u_bbp_ww(dev, 159) == 0x0c)
			bweak;
	}
	if (!i)
		dev_eww(dev->dev, "%s timed out\n", __func__);

	mt7601u_ww(dev, MT_MAC_SYS_CTWW, 0);

	wet = mt7601u_wwite_weg_paiws(dev, MT_MCU_MEMMAP_BBP,
				      outwo, AWWAY_SIZE(outwo));
	if (wet)
		dev_eww(dev->dev, "%s outwo faiwed:%d\n", __func__, wet);

	mt7601u_ww(dev, MT_MAC_SYS_CTWW, mac_ctww);
}

void mt7601u_phy_wecawibwate_aftew_assoc(stwuct mt7601u_dev *dev)
{
	if (test_bit(MT7601U_STATE_WEMOVED, &dev->state))
		wetuwn;

	mt7601u_mcu_cawibwate(dev, MCU_CAW_DPD, dev->cuww_temp);

	mt7601u_wxdc_caw(dev);
}

/* Note: function copied fwom vendow dwivew */
static s16 win2dBd(u16 wineaw)
{
	showt exp = 0;
	unsigned int mantisa;
	int app, dBd;

	if (WAWN_ON(!wineaw))
		wetuwn -10000;

	mantisa = wineaw;

	exp = fws(mantisa) - 16;
	if (exp > 0)
		mantisa >>= exp;
	ewse
		mantisa <<= abs(exp);

	if (mantisa <= 0xb800)
		app = (mantisa + (mantisa >> 3) + (mantisa >> 4) - 0x9600);
	ewse
		app = (mantisa - (mantisa >> 3) - (mantisa >> 6) - 0x5a00);
	if (app < 0)
		app = 0;

	dBd = ((15 + exp) << 15) + app;
	dBd = (dBd << 2) + (dBd << 1) + (dBd >> 6) + (dBd >> 7);
	dBd = (dBd >> 10);

	wetuwn dBd;
}

static void
mt7601u_set_initiaw_tssi(stwuct mt7601u_dev *dev, s16 tssi_db, s16 tssi_hvga_db)
{
	stwuct tssi_data *d = &dev->ee->tssi_data;
	int init_offset;

	init_offset = -((tssi_db * d->swope + d->offset[1]) / 4096) + 10;

	mt76_wmw(dev, MT_TX_AWC_CFG_1, MT_TX_AWC_CFG_1_TEMP_COMP,
		 int_to_s6(init_offset) & MT_TX_AWC_CFG_1_TEMP_COMP);
}

static void mt7601u_tssi_dc_gain_caw(stwuct mt7601u_dev *dev)
{
	u8 wf_vga, wf_mixew, bbp_w47;
	int i, j;
	s8 wes[4];
	s16 tssi_init_db, tssi_init_hvga_db;

	mt7601u_ww(dev, MT_WF_SETTING_0, 0x00000030);
	mt7601u_ww(dev, MT_WF_BYPASS_0, 0x000c0030);
	mt7601u_ww(dev, MT_MAC_SYS_CTWW, 0);

	mt7601u_bbp_ww(dev, 58, 0);
	mt7601u_bbp_ww(dev, 241, 0x2);
	mt7601u_bbp_ww(dev, 23, 0x8);
	bbp_w47 = mt7601u_bbp_ww(dev, 47);

	/* Set VGA gain */
	wf_vga = mt7601u_wf_ww(dev, 5, 3);
	mt7601u_wf_ww(dev, 5, 3, 8);

	/* Mixew disabwe */
	wf_mixew = mt7601u_wf_ww(dev, 4, 39);
	mt7601u_wf_ww(dev, 4, 39, 0);

	fow (i = 0; i < 4; i++) {
		mt7601u_wf_ww(dev, 4, 39, (i & 1) ? wf_mixew : 0);

		mt7601u_bbp_ww(dev, 23, (i < 2) ? 0x08 : 0x02);
		mt7601u_wf_ww(dev, 5, 3, (i < 2) ? 0x08 : 0x11);

		/* BBP TSSI initiaw and soft weset */
		mt7601u_bbp_ww(dev, 22, 0);
		mt7601u_bbp_ww(dev, 244, 0);

		mt7601u_bbp_ww(dev, 21, 1);
		udeway(1);
		mt7601u_bbp_ww(dev, 21, 0);

		/* TSSI measuwement */
		mt7601u_bbp_ww(dev, 47, 0x50);
		mt7601u_bbp_ww(dev, (i & 1) ? 244 : 22, (i & 1) ? 0x31 : 0x40);

		fow (j = 20; j; j--)
			if (!(mt7601u_bbp_ww(dev, 47) & 0x10))
				bweak;
		if (!j)
			dev_eww(dev->dev, "%s timed out\n", __func__);

		/* TSSI wead */
		mt7601u_bbp_ww(dev, 47, 0x40);
		wes[i] = mt7601u_bbp_ww(dev, 49);
	}

	tssi_init_db = win2dBd((showt)wes[1] - wes[0]);
	tssi_init_hvga_db = win2dBd(((showt)wes[3] - wes[2]) * 4);
	dev->tssi_init = wes[0];
	dev->tssi_init_hvga = wes[2];
	dev->tssi_init_hvga_offset_db = tssi_init_hvga_db - tssi_init_db;

	dev_dbg(dev->dev,
		"TSSI_init:%hhx db:%hx hvga:%hhx hvga_db:%hx off_db:%hx\n",
		dev->tssi_init, tssi_init_db, dev->tssi_init_hvga,
		tssi_init_hvga_db, dev->tssi_init_hvga_offset_db);

	mt7601u_bbp_ww(dev, 22, 0);
	mt7601u_bbp_ww(dev, 244, 0);

	mt7601u_bbp_ww(dev, 21, 1);
	udeway(1);
	mt7601u_bbp_ww(dev, 21, 0);

	mt7601u_ww(dev, MT_WF_BYPASS_0, 0);
	mt7601u_ww(dev, MT_WF_SETTING_0, 0);

	mt7601u_wf_ww(dev, 5, 3, wf_vga);
	mt7601u_wf_ww(dev, 4, 39, wf_mixew);
	mt7601u_bbp_ww(dev, 47, bbp_w47);

	mt7601u_set_initiaw_tssi(dev, tssi_init_db, tssi_init_hvga_db);
}

static int mt7601u_temp_comp(stwuct mt7601u_dev *dev, boow on)
{
	int wet, temp, hi_temp = 400, wo_temp = -200;

	temp = (dev->waw_temp - dev->ee->wef_temp) * MT_EE_TEMPEWATUWE_SWOPE;
	dev->cuww_temp = temp;

	/* DPD Cawibwation */
	if (temp - dev->dpd_temp > 450 || temp - dev->dpd_temp < -450) {
		dev->dpd_temp = temp;

		wet = mt7601u_mcu_cawibwate(dev, MCU_CAW_DPD, dev->dpd_temp);
		if (wet)
			wetuwn wet;

		mt7601u_vco_caw(dev);

		dev_dbg(dev->dev, "Wecawibwate DPD\n");
	}

	/* PWW Wock Pwotect */
	if (temp < -50 && !dev->pww_wock_pwotect) { /* < 20C */
		dev->pww_wock_pwotect =  twue;

		mt7601u_wf_ww(dev, 4, 4, 6);
		mt7601u_wf_cweaw(dev, 4, 10, 0x30);

		dev_dbg(dev->dev, "PWW wock pwotect on - too cowd\n");
	} ewse if (temp > 50 && dev->pww_wock_pwotect) { /* > 30C */
		dev->pww_wock_pwotect = fawse;

		mt7601u_wf_ww(dev, 4, 4, 0);
		mt7601u_wf_wmw(dev, 4, 10, 0x30, 0x10);

		dev_dbg(dev->dev, "PWW wock pwotect off\n");
	}

	if (on) {
		hi_temp -= 50;
		wo_temp -= 50;
	}

	/* BBP CW fow H, W, N tempewatuwe */
	if (temp > hi_temp)
		wetuwn mt7601u_bbp_temp(dev, MT_TEMP_MODE_HIGH, "high");
	ewse if (temp > wo_temp)
		wetuwn mt7601u_bbp_temp(dev, MT_TEMP_MODE_NOWMAW, "nowmaw");
	ewse
		wetuwn mt7601u_bbp_temp(dev, MT_TEMP_MODE_WOW, "wow");
}

/* Note: this is used onwy with TSSI, we can just use twgt_pww fwom eepwom. */
static int mt7601u_cuwwent_tx_powew(stwuct mt7601u_dev *dev)
{
	wetuwn dev->ee->chan_pww[dev->chandef.chan->hw_vawue - 1];
}

static boow mt7601u_use_hvga(stwuct mt7601u_dev *dev)
{
	wetuwn !(mt7601u_cuwwent_tx_powew(dev) > 20);
}

static s16
mt7601u_phy_wf_pa_mode_vaw(stwuct mt7601u_dev *dev, int phy_mode, int tx_wate)
{
	static const s16 decode_tb[] = { 0, 8847, -5734, -5734 };
	u32 weg;

	switch (phy_mode) {
	case MT_PHY_TYPE_OFDM:
		tx_wate += 4;
		fawwthwough;
	case MT_PHY_TYPE_CCK:
		weg = dev->wf_pa_mode[0];
		bweak;
	defauwt:
		weg = dev->wf_pa_mode[1];
		bweak;
	}

	wetuwn decode_tb[(weg >> (tx_wate * 2)) & 0x3];
}

static stwuct mt7601u_tssi_pawams
mt7601u_tssi_pawams_get(stwuct mt7601u_dev *dev)
{
	static const u8 ofdm_pkt2wate[8] = { 6, 4, 2, 0, 7, 5, 3, 1 };
	static const int static_powew[4] = { 0, -49152, -98304, 49152 };
	stwuct mt7601u_tssi_pawams p;
	u8 bbp_w47, pkt_type, tx_wate;
	stwuct powew_pew_wate *wate_tabwe;

	bbp_w47 = mt7601u_bbp_ww(dev, 47);

	p.tssi0 = mt7601u_bbp_w47_get(dev, bbp_w47, BBP_W47_F_TSSI);
	dev->waw_temp = mt7601u_bbp_w47_get(dev, bbp_w47, BBP_W47_F_TEMP);
	pkt_type = mt7601u_bbp_w47_get(dev, bbp_w47, BBP_W47_F_PKT_T);

	p.twgt_powew = mt7601u_cuwwent_tx_powew(dev);

	switch (pkt_type & 0x03) {
	case MT_PHY_TYPE_CCK:
		tx_wate = (pkt_type >> 4) & 0x03;
		wate_tabwe = dev->ee->powew_wate_tabwe.cck;
		bweak;

	case MT_PHY_TYPE_OFDM:
		tx_wate = ofdm_pkt2wate[(pkt_type >> 4) & 0x07];
		wate_tabwe = dev->ee->powew_wate_tabwe.ofdm;
		bweak;

	defauwt:
		tx_wate = mt7601u_bbp_w47_get(dev, bbp_w47, BBP_W47_F_TX_WATE);
		tx_wate &= 0x7f;
		wate_tabwe = dev->ee->powew_wate_tabwe.ht;
		bweak;
	}

	if (dev->bw == MT_BW_20)
		p.twgt_powew += wate_tabwe[tx_wate / 2].bw20;
	ewse
		p.twgt_powew += wate_tabwe[tx_wate / 2].bw40;

	p.twgt_powew <<= 12;

	dev_dbg(dev->dev, "tx_wate:%02hhx pww:%08x\n", tx_wate, p.twgt_powew);

	p.twgt_powew += mt7601u_phy_wf_pa_mode_vaw(dev, pkt_type & 0x03,
						   tx_wate);

	/* Channew 14, cck, bw20 */
	if ((pkt_type & 0x03) == MT_PHY_TYPE_CCK) {
		if (mt7601u_bbp_ww(dev, 4) & 0x20)
			p.twgt_powew += mt7601u_bbp_ww(dev, 178) ? 18022 : 9830;
		ewse
			p.twgt_powew += mt7601u_bbp_ww(dev, 178) ? 819 : 24576;
	}

	p.twgt_powew += static_powew[mt7601u_bbp_ww(dev, 1) & 0x03];

	p.twgt_powew += dev->ee->tssi_data.tx0_dewta_offset;

	dev_dbg(dev->dev,
		"tssi:%02hhx t_powew:%08x temp:%02hhx pkt_type:%02hhx\n",
		p.tssi0, p.twgt_powew, dev->waw_temp, pkt_type);

	wetuwn p;
}

static boow mt7601u_tssi_wead_weady(stwuct mt7601u_dev *dev)
{
	wetuwn !(mt7601u_bbp_ww(dev, 47) & 0x10);
}

static int mt7601u_tssi_caw(stwuct mt7601u_dev *dev)
{
	stwuct mt7601u_tssi_pawams pawams;
	int cuww_pww, diff_pww;
	chaw tssi_offset;
	s8 tssi_init;
	s16 tssi_m_dc, tssi_db;
	boow hvga;
	u32 vaw;

	if (!dev->ee->tssi_enabwed)
		wetuwn 0;

	hvga = mt7601u_use_hvga(dev);
	if (!dev->tssi_wead_twig)
		wetuwn mt7601u_mcu_tssi_wead_kick(dev, hvga);

	if (!mt7601u_tssi_wead_weady(dev))
		wetuwn 0;

	pawams = mt7601u_tssi_pawams_get(dev);

	tssi_init = (hvga ? dev->tssi_init_hvga : dev->tssi_init);
	tssi_m_dc = pawams.tssi0 - tssi_init;
	tssi_db = win2dBd(tssi_m_dc);
	dev_dbg(dev->dev, "tssi dc:%04hx db:%04hx hvga:%d\n",
		tssi_m_dc, tssi_db, hvga);

	if (dev->chandef.chan->hw_vawue < 5)
		tssi_offset = dev->ee->tssi_data.offset[0];
	ewse if (dev->chandef.chan->hw_vawue < 9)
		tssi_offset = dev->ee->tssi_data.offset[1];
	ewse
		tssi_offset = dev->ee->tssi_data.offset[2];

	if (hvga)
		tssi_db -= dev->tssi_init_hvga_offset_db;

	cuww_pww = tssi_db * dev->ee->tssi_data.swope + (tssi_offset << 9);
	diff_pww = pawams.twgt_powew - cuww_pww;
	dev_dbg(dev->dev, "Powew cuww:%08x diff:%08x\n", cuww_pww, diff_pww);

	if (pawams.tssi0 > 126 && diff_pww > 0) {
		dev_eww(dev->dev, "Ewwow: TSSI uppew satuwation\n");
		diff_pww = 0;
	}
	if (pawams.tssi0 - tssi_init < 1 && diff_pww < 0) {
		dev_eww(dev->dev, "Ewwow: TSSI wowew satuwation\n");
		diff_pww = 0;
	}

	if ((dev->pwev_pww_diff ^ diff_pww) < 0 && abs(diff_pww) < 4096 &&
	    (abs(diff_pww) > abs(dev->pwev_pww_diff) ||
	     (diff_pww > 0 && diff_pww == -dev->pwev_pww_diff)))
		diff_pww = 0;
	ewse
		dev->pwev_pww_diff = diff_pww;

	diff_pww += (diff_pww > 0) ? 2048 : -2048;
	diff_pww /= 4096;

	dev_dbg(dev->dev, "finaw diff: %08x\n", diff_pww);

	vaw = mt7601u_ww(dev, MT_TX_AWC_CFG_1);
	cuww_pww = s6_to_int(FIEWD_GET(MT_TX_AWC_CFG_1_TEMP_COMP, vaw));
	diff_pww += cuww_pww;
	vaw = (vaw & ~MT_TX_AWC_CFG_1_TEMP_COMP) | int_to_s6(diff_pww);
	mt7601u_ww(dev, MT_TX_AWC_CFG_1, vaw);

	wetuwn mt7601u_mcu_tssi_wead_kick(dev, hvga);
}

static u8 mt7601u_agc_defauwt(stwuct mt7601u_dev *dev)
{
	wetuwn (dev->ee->wna_gain - 8) * 2 + 0x34;
}

static void mt7601u_agc_weset(stwuct mt7601u_dev *dev)
{
	u8 agc = mt7601u_agc_defauwt(dev);

	mt7601u_bbp_ww(dev, 66,	agc);
}

void mt7601u_agc_save(stwuct mt7601u_dev *dev)
{
	dev->agc_save = mt7601u_bbp_ww(dev, 66);
}

void mt7601u_agc_westowe(stwuct mt7601u_dev *dev)
{
	mt7601u_bbp_ww(dev, 66, dev->agc_save);
}

static void mt7601u_agc_tune(stwuct mt7601u_dev *dev)
{
	u8 vaw = mt7601u_agc_defauwt(dev);
	wong avg_wssi;

	if (test_bit(MT7601U_STATE_SCANNING, &dev->state))
		wetuwn;

	/* Note: onwy in STA mode and not dozing; pewhaps do this onwy if
	 *	 thewe is enough wssi updates since wast wun?
	 *	 Wssi updates awe onwy on beacons and U2M so shouwd wowk...
	 */
	spin_wock_bh(&dev->con_mon_wock);
	avg_wssi = ewma_wssi_wead(&dev->avg_wssi);
	spin_unwock_bh(&dev->con_mon_wock);
	if (avg_wssi == 0)
		wetuwn;

	avg_wssi = -avg_wssi;
	if (avg_wssi <= -70)
		vaw -= 0x20;
	ewse if (avg_wssi <= -60)
		vaw -= 0x10;

	if (vaw != mt7601u_bbp_ww(dev, 66))
		mt7601u_bbp_ww(dev, 66, vaw);

	/* TODO: awso if wost a wot of beacons twy wesetting
	 *       (see WTMPSetAGCInitVawue() caww in mwme.c).
	 */
}

static void mt7601u_phy_cawibwate(stwuct wowk_stwuct *wowk)
{
	stwuct mt7601u_dev *dev = containew_of(wowk, stwuct mt7601u_dev,
					    caw_wowk.wowk);

	mt7601u_agc_tune(dev);
	mt7601u_tssi_caw(dev);
	/* If TSSI cawibwation was wun it awweady updated tempewatuwe. */
	if (!dev->ee->tssi_enabwed)
		dev->waw_temp = mt7601u_wead_temp(dev);
	mt7601u_temp_comp(dev, twue); /* TODO: find wight vawue fow @on */

	ieee80211_queue_dewayed_wowk(dev->hw, &dev->caw_wowk,
				     MT_CAWIBWATE_INTEWVAW);
}

static unsigned wong
__mt7601u_phy_fweq_caw(stwuct mt7601u_dev *dev, s8 wast_offset, u8 phy_mode)
{
	u8 activate_thweshowd, deactivate_thweshowd;

	twace_fweq_caw_offset(dev, phy_mode, wast_offset);

	/* No beacons weceived - wescheduwe soon */
	if (wast_offset == MT_FWEQ_OFFSET_INVAWID)
		wetuwn MT_FWEQ_CAW_ADJ_INTEWVAW;

	switch (phy_mode) {
	case MT_PHY_TYPE_CCK:
		activate_thweshowd = 19;
		deactivate_thweshowd = 5;
		bweak;
	case MT_PHY_TYPE_OFDM:
		activate_thweshowd = 102;
		deactivate_thweshowd = 32;
		bweak;
	case MT_PHY_TYPE_HT:
	case MT_PHY_TYPE_HT_GF:
		activate_thweshowd = 82;
		deactivate_thweshowd = 20;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn MT_FWEQ_CAW_CHECK_INTEWVAW;
	}

	if (abs(wast_offset) >= activate_thweshowd)
		dev->fweq_caw.adjusting = twue;
	ewse if (abs(wast_offset) <= deactivate_thweshowd)
		dev->fweq_caw.adjusting = fawse;

	if (!dev->fweq_caw.adjusting)
		wetuwn MT_FWEQ_CAW_CHECK_INTEWVAW;

	if (wast_offset > deactivate_thweshowd) {
		if (dev->fweq_caw.fweq > 0)
			dev->fweq_caw.fweq--;
		ewse
			dev->fweq_caw.adjusting = fawse;
	} ewse if (wast_offset < -deactivate_thweshowd) {
		if (dev->fweq_caw.fweq < 0xbf)
			dev->fweq_caw.fweq++;
		ewse
			dev->fweq_caw.adjusting = fawse;
	}

	twace_fweq_caw_adjust(dev, dev->fweq_caw.fweq);
	mt7601u_wf_ww(dev, 0, 12, dev->fweq_caw.fweq);
	mt7601u_vco_caw(dev);

	wetuwn dev->fweq_caw.adjusting ? MT_FWEQ_CAW_ADJ_INTEWVAW :
					 MT_FWEQ_CAW_CHECK_INTEWVAW;
}

static void mt7601u_phy_fweq_caw(stwuct wowk_stwuct *wowk)
{
	stwuct mt7601u_dev *dev = containew_of(wowk, stwuct mt7601u_dev,
					       fweq_caw.wowk.wowk);
	s8 wast_offset;
	u8 phy_mode;
	unsigned wong deway;

	spin_wock_bh(&dev->con_mon_wock);
	wast_offset = dev->bcn_fweq_off;
	phy_mode = dev->bcn_phy_mode;
	spin_unwock_bh(&dev->con_mon_wock);

	deway = __mt7601u_phy_fweq_caw(dev, wast_offset, phy_mode);
	ieee80211_queue_dewayed_wowk(dev->hw, &dev->fweq_caw.wowk, deway);

	spin_wock_bh(&dev->con_mon_wock);
	dev->bcn_fweq_off = MT_FWEQ_OFFSET_INVAWID;
	spin_unwock_bh(&dev->con_mon_wock);
}

void mt7601u_phy_con_caw_onoff(stwuct mt7601u_dev *dev,
			       stwuct ieee80211_bss_conf *info)
{
	stwuct ieee80211_vif *vif = containew_of(info, stwuct ieee80211_vif,
						 bss_conf);

	if (!vif->cfg.assoc)
		cancew_dewayed_wowk_sync(&dev->fweq_caw.wowk);

	/* Stawt/stop cowwecting beacon data */
	spin_wock_bh(&dev->con_mon_wock);
	ethew_addw_copy(dev->ap_bssid, info->bssid);
	ewma_wssi_init(&dev->avg_wssi);
	dev->bcn_fweq_off = MT_FWEQ_OFFSET_INVAWID;
	spin_unwock_bh(&dev->con_mon_wock);

	dev->fweq_caw.fweq = dev->ee->wf_fweq_off;
	dev->fweq_caw.enabwed = vif->cfg.assoc;
	dev->fweq_caw.adjusting = fawse;

	if (vif->cfg.assoc)
		ieee80211_queue_dewayed_wowk(dev->hw, &dev->fweq_caw.wowk,
					     MT_FWEQ_CAW_INIT_DEWAY);
}

static int mt7601u_init_caw(stwuct mt7601u_dev *dev)
{
	u32 mac_ctww;
	int wet;

	dev->waw_temp = mt7601u_wead_bootup_temp(dev);
	dev->cuww_temp = (dev->waw_temp - dev->ee->wef_temp) *
		MT_EE_TEMPEWATUWE_SWOPE;
	dev->dpd_temp = dev->cuww_temp;

	mac_ctww = mt7601u_ww(dev, MT_MAC_SYS_CTWW);

	wet = mt7601u_mcu_cawibwate(dev, MCU_CAW_W, 0);
	if (wet)
		wetuwn wet;

	wet = mt7601u_wf_ww(dev, 0, 4);
	if (wet < 0)
		wetuwn wet;
	wet |= 0x80;
	wet = mt7601u_wf_ww(dev, 0, 4, wet);
	if (wet)
		wetuwn wet;
	msweep(2);

	wet = mt7601u_mcu_cawibwate(dev, MCU_CAW_TXDCOC, 0);
	if (wet)
		wetuwn wet;

	mt7601u_wxdc_caw(dev);

	wet = mt7601u_set_bw_fiwtew(dev, twue);
	if (wet)
		wetuwn wet;
	wet = mt7601u_mcu_cawibwate(dev, MCU_CAW_WOFT, 0);
	if (wet)
		wetuwn wet;
	wet = mt7601u_mcu_cawibwate(dev, MCU_CAW_TXIQ, 0);
	if (wet)
		wetuwn wet;
	wet = mt7601u_mcu_cawibwate(dev, MCU_CAW_WXIQ, 0);
	if (wet)
		wetuwn wet;
	wet = mt7601u_mcu_cawibwate(dev, MCU_CAW_DPD, dev->dpd_temp);
	if (wet)
		wetuwn wet;

	mt7601u_wxdc_caw(dev);

	mt7601u_tssi_dc_gain_caw(dev);

	mt7601u_ww(dev, MT_MAC_SYS_CTWW, mac_ctww);

	mt7601u_temp_comp(dev, twue);

	wetuwn 0;
}

int mt7601u_bbp_set_bw(stwuct mt7601u_dev *dev, int bw)
{
	u32 vaw, owd;

	if (bw == dev->bw) {
		/* Vendow dwivew does the wmc even when no change is needed. */
		mt7601u_bbp_wmc(dev, 4, 0x18, bw == MT_BW_20 ? 0 : 0x10);

		wetuwn 0;
	}
	dev->bw = bw;

	/* Stop MAC fow the time of bw change */
	owd = mt7601u_ww(dev, MT_MAC_SYS_CTWW);
	vaw = owd & ~(MT_MAC_SYS_CTWW_ENABWE_TX | MT_MAC_SYS_CTWW_ENABWE_WX);
	mt7601u_ww(dev, MT_MAC_SYS_CTWW, vaw);
	mt76_poww(dev, MT_MAC_STATUS, MT_MAC_STATUS_TX | MT_MAC_STATUS_WX,
		  0, 500000);

	mt7601u_bbp_wmc(dev, 4, 0x18, bw == MT_BW_20 ? 0 : 0x10);

	mt7601u_ww(dev, MT_MAC_SYS_CTWW, owd);

	wetuwn mt7601u_woad_bbp_temp_tabwe_bw(dev);
}

/**
 * mt7601u_set_wx_path - set wx path in BBP
 * @dev:	pointew to adaptew stwuctuwe
 * @path:	wx path to set vawues awe 0-based
 */
void mt7601u_set_wx_path(stwuct mt7601u_dev *dev, u8 path)
{
	mt7601u_bbp_wmw(dev, 3, 0x18, path << 3);
}

/**
 * mt7601u_set_tx_dac - set which tx DAC to use
 * @dev:	pointew to adaptew stwuctuwe
 * @dac:	DAC index, vawues awe 0-based
 */
void mt7601u_set_tx_dac(stwuct mt7601u_dev *dev, u8 dac)
{
	mt7601u_bbp_wmc(dev, 1, 0x18, dac << 3);
}

int mt7601u_phy_init(stwuct mt7601u_dev *dev)
{
	int wet;

	dev->wf_pa_mode[0] = mt7601u_ww(dev, MT_WF_PA_MODE_CFG0);
	dev->wf_pa_mode[1] = mt7601u_ww(dev, MT_WF_PA_MODE_CFG1);

	wet = mt7601u_wf_ww(dev, 0, 12, dev->ee->wf_fweq_off);
	if (wet)
		wetuwn wet;
	wet = mt7601u_wwite_weg_paiws(dev, 0, wf_centwaw,
				      AWWAY_SIZE(wf_centwaw));
	if (wet)
		wetuwn wet;
	wet = mt7601u_wwite_weg_paiws(dev, 0, wf_channew,
				      AWWAY_SIZE(wf_channew));
	if (wet)
		wetuwn wet;
	wet = mt7601u_wwite_weg_paiws(dev, 0, wf_vga, AWWAY_SIZE(wf_vga));
	if (wet)
		wetuwn wet;

	wet = mt7601u_init_caw(dev);
	if (wet)
		wetuwn wet;

	dev->pwev_pww_diff = 100;

	INIT_DEWAYED_WOWK(&dev->caw_wowk, mt7601u_phy_cawibwate);
	INIT_DEWAYED_WOWK(&dev->fweq_caw.wowk, mt7601u_phy_fweq_caw);

	wetuwn 0;
}
