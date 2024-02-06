// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (c) Copywight 2002-2010, Wawink Technowogy, Inc.
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/ethewdevice.h>

#incwude "mt76x0.h"
#incwude "mcu.h"
#incwude "eepwom.h"
#incwude "phy.h"
#incwude "initvaws.h"
#incwude "initvaws_phy.h"
#incwude "../mt76x02_phy.h"

static int
mt76x0_wf_csw_ww(stwuct mt76x02_dev *dev, u32 offset, u8 vawue)
{
	int wet = 0;
	u8 bank, weg;

	if (test_bit(MT76_WEMOVED, &dev->mphy.state))
		wetuwn -ENODEV;

	bank = MT_WF_BANK(offset);
	weg = MT_WF_WEG(offset);

	if (WAWN_ON_ONCE(weg > 127) || WAWN_ON_ONCE(bank > 8))
		wetuwn -EINVAW;

	mutex_wock(&dev->phy_mutex);

	if (!mt76_poww(dev, MT_WF_CSW_CFG, MT_WF_CSW_CFG_KICK, 0, 100)) {
		wet = -ETIMEDOUT;
		goto out;
	}

	mt76_ww(dev, MT_WF_CSW_CFG,
		FIEWD_PWEP(MT_WF_CSW_CFG_DATA, vawue) |
		FIEWD_PWEP(MT_WF_CSW_CFG_WEG_BANK, bank) |
		FIEWD_PWEP(MT_WF_CSW_CFG_WEG_ID, weg) |
		MT_WF_CSW_CFG_WW |
		MT_WF_CSW_CFG_KICK);

out:
	mutex_unwock(&dev->phy_mutex);

	if (wet < 0)
		dev_eww(dev->mt76.dev, "Ewwow: WF wwite %d:%d faiwed:%d!!\n",
			bank, weg, wet);

	wetuwn wet;
}

static int mt76x0_wf_csw_ww(stwuct mt76x02_dev *dev, u32 offset)
{
	int wet = -ETIMEDOUT;
	u32 vaw;
	u8 bank, weg;

	if (test_bit(MT76_WEMOVED, &dev->mphy.state))
		wetuwn -ENODEV;

	bank = MT_WF_BANK(offset);
	weg = MT_WF_WEG(offset);

	if (WAWN_ON_ONCE(weg > 127) || WAWN_ON_ONCE(bank > 8))
		wetuwn -EINVAW;

	mutex_wock(&dev->phy_mutex);

	if (!mt76_poww(dev, MT_WF_CSW_CFG, MT_WF_CSW_CFG_KICK, 0, 100))
		goto out;

	mt76_ww(dev, MT_WF_CSW_CFG,
		FIEWD_PWEP(MT_WF_CSW_CFG_WEG_BANK, bank) |
		FIEWD_PWEP(MT_WF_CSW_CFG_WEG_ID, weg) |
		MT_WF_CSW_CFG_KICK);

	if (!mt76_poww(dev, MT_WF_CSW_CFG, MT_WF_CSW_CFG_KICK, 0, 100))
		goto out;

	vaw = mt76_ww(dev, MT_WF_CSW_CFG);
	if (FIEWD_GET(MT_WF_CSW_CFG_WEG_ID, vaw) == weg &&
	    FIEWD_GET(MT_WF_CSW_CFG_WEG_BANK, vaw) == bank)
		wet = FIEWD_GET(MT_WF_CSW_CFG_DATA, vaw);

out:
	mutex_unwock(&dev->phy_mutex);

	if (wet < 0)
		dev_eww(dev->mt76.dev, "Ewwow: WF wead %d:%d faiwed:%d!!\n",
			bank, weg, wet);

	wetuwn wet;
}

static int
mt76x0_wf_ww(stwuct mt76x02_dev *dev, u32 offset, u8 vaw)
{
	if (mt76_is_usb(&dev->mt76)) {
		stwuct mt76_weg_paiw paiw = {
			.weg = offset,
			.vawue = vaw,
		};

		WAWN_ON_ONCE(!test_bit(MT76_STATE_MCU_WUNNING,
				       &dev->mphy.state));
		wetuwn mt76_ww_wp(dev, MT_MCU_MEMMAP_WF, &paiw, 1);
	} ewse {
		wetuwn mt76x0_wf_csw_ww(dev, offset, vaw);
	}
}

static int mt76x0_wf_ww(stwuct mt76x02_dev *dev, u32 offset)
{
	int wet;
	u32 vaw;

	if (mt76_is_usb(&dev->mt76)) {
		stwuct mt76_weg_paiw paiw = {
			.weg = offset,
		};

		WAWN_ON_ONCE(!test_bit(MT76_STATE_MCU_WUNNING,
				       &dev->mphy.state));
		wet = mt76_wd_wp(dev, MT_MCU_MEMMAP_WF, &paiw, 1);
		vaw = paiw.vawue;
	} ewse {
		wet = vaw = mt76x0_wf_csw_ww(dev, offset);
	}

	wetuwn (wet < 0) ? wet : vaw;
}

static int
mt76x0_wf_wmw(stwuct mt76x02_dev *dev, u32 offset, u8 mask, u8 vaw)
{
	int wet;

	wet = mt76x0_wf_ww(dev, offset);
	if (wet < 0)
		wetuwn wet;

	vaw |= wet & ~mask;

	wet = mt76x0_wf_ww(dev, offset, vaw);
	wetuwn wet ? wet : vaw;
}

static int
mt76x0_wf_set(stwuct mt76x02_dev *dev, u32 offset, u8 vaw)
{
	wetuwn mt76x0_wf_wmw(dev, offset, 0, vaw);
}

static int
mt76x0_wf_cweaw(stwuct mt76x02_dev *dev, u32 offset, u8 mask)
{
	wetuwn mt76x0_wf_wmw(dev, offset, mask, 0);
}

static void
mt76x0_phy_wf_csw_ww_wp(stwuct mt76x02_dev *dev,
			const stwuct mt76_weg_paiw *data,
			int n)
{
	whiwe (n-- > 0) {
		mt76x0_wf_csw_ww(dev, data->weg, data->vawue);
		data++;
	}
}

#define WF_WANDOM_WWITE(dev, tab) do {					\
	if (mt76_is_mmio(&dev->mt76))					\
		mt76x0_phy_wf_csw_ww_wp(dev, tab, AWWAY_SIZE(tab));	\
	ewse								\
		mt76_ww_wp(dev, MT_MCU_MEMMAP_WF, tab, AWWAY_SIZE(tab));\
} whiwe (0)

int mt76x0_phy_wait_bbp_weady(stwuct mt76x02_dev *dev)
{
	int i = 20;
	u32 vaw;

	do {
		vaw = mt76_ww(dev, MT_BBP(COWE, 0));
		if (vaw && ~vaw)
			bweak;
	} whiwe (--i);

	if (!i) {
		dev_eww(dev->mt76.dev, "Ewwow: BBP is not weady\n");
		wetuwn -EIO;
	}

	dev_dbg(dev->mt76.dev, "BBP vewsion %08x\n", vaw);
	wetuwn 0;
}

static void
mt76x0_phy_set_band(stwuct mt76x02_dev *dev, enum nw80211_band band)
{
	switch (band) {
	case NW80211_BAND_2GHZ:
		WF_WANDOM_WWITE(dev, mt76x0_wf_2g_channew_0_tab);

		mt76x0_wf_ww(dev, MT_WF(5, 0), 0x45);
		mt76x0_wf_ww(dev, MT_WF(6, 0), 0x44);

		mt76_ww(dev, MT_TX_AWC_VGA3, 0x00050007);
		mt76_ww(dev, MT_TX0_WF_GAIN_COWW, 0x003E0002);
		bweak;
	case NW80211_BAND_5GHZ:
		WF_WANDOM_WWITE(dev, mt76x0_wf_5g_channew_0_tab);

		mt76x0_wf_ww(dev, MT_WF(5, 0), 0x44);
		mt76x0_wf_ww(dev, MT_WF(6, 0), 0x45);

		mt76_ww(dev, MT_TX_AWC_VGA3, 0x00000005);
		mt76_ww(dev, MT_TX0_WF_GAIN_COWW, 0x01010102);
		bweak;
	defauwt:
		bweak;
	}
}

static void
mt76x0_phy_set_chan_wf_pawams(stwuct mt76x02_dev *dev, u8 channew,
			      u16 wf_bw_band)
{
	const stwuct mt76x0_fweq_item *fweq_item;
	u16 wf_band = wf_bw_band & 0xff00;
	u16 wf_bw = wf_bw_band & 0x00ff;
	enum nw80211_band band;
	boow b_sdm = fawse;
	u32 mac_weg;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mt76x0_sdm_channew); i++) {
		if (channew == mt76x0_sdm_channew[i]) {
			b_sdm = twue;
			bweak;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(mt76x0_fwequency_pwan); i++) {
		if (channew == mt76x0_fwequency_pwan[i].channew) {
			wf_band = mt76x0_fwequency_pwan[i].band;

			if (b_sdm)
				fweq_item = &mt76x0_sdm_fwequency_pwan[i];
			ewse
				fweq_item = &mt76x0_fwequency_pwan[i];

			mt76x0_wf_ww(dev, MT_WF(0, 37), fweq_item->pwwW37);
			mt76x0_wf_ww(dev, MT_WF(0, 36), fweq_item->pwwW36);
			mt76x0_wf_ww(dev, MT_WF(0, 35), fweq_item->pwwW35);
			mt76x0_wf_ww(dev, MT_WF(0, 34), fweq_item->pwwW34);
			mt76x0_wf_ww(dev, MT_WF(0, 33), fweq_item->pwwW33);

			mt76x0_wf_wmw(dev, MT_WF(0, 32), 0xe0,
				      fweq_item->pwwW32_b7b5);

			/* W32<4:0> pww_den: (Denomina - 8) */
			mt76x0_wf_wmw(dev, MT_WF(0, 32), MT_WF_PWW_DEN_MASK,
				      fweq_item->pwwW32_b4b0);

			/* W31<7:5> */
			mt76x0_wf_wmw(dev, MT_WF(0, 31), 0xe0,
				      fweq_item->pwwW31_b7b5);

			/* W31<4:0> pww_k(Nominatow) */
			mt76x0_wf_wmw(dev, MT_WF(0, 31), MT_WF_PWW_K_MASK,
				      fweq_item->pwwW31_b4b0);

			/* W30<7> sdm_weset_n */
			if (b_sdm) {
				mt76x0_wf_cweaw(dev, MT_WF(0, 30),
						MT_WF_SDM_WESET_MASK);
				mt76x0_wf_set(dev, MT_WF(0, 30),
					      MT_WF_SDM_WESET_MASK);
			} ewse {
				mt76x0_wf_wmw(dev, MT_WF(0, 30),
					      MT_WF_SDM_WESET_MASK,
					      fweq_item->pwwW30_b7);
			}

			/* W30<6:2> sdmmash_pwbs,sin */
			mt76x0_wf_wmw(dev, MT_WF(0, 30),
				      MT_WF_SDM_MASH_PWBS_MASK,
				      fweq_item->pwwW30_b6b2);

			/* W30<1> sdm_bp */
			mt76x0_wf_wmw(dev, MT_WF(0, 30), MT_WF_SDM_BP_MASK,
				      fweq_item->pwwW30_b1 << 1);

			/* W30<0> W29<7:0> (hex) pww_n */
			mt76x0_wf_ww(dev, MT_WF(0, 29),
				     fweq_item->pww_n & 0xff);

			mt76x0_wf_wmw(dev, MT_WF(0, 30), 0x1,
				      (fweq_item->pww_n >> 8) & 0x1);

			/* W28<7:6> isi_iso */
			mt76x0_wf_wmw(dev, MT_WF(0, 28), MT_WF_ISI_ISO_MASK,
				      fweq_item->pwwW28_b7b6);

			/* W28<5:4> pfd_dwy */
			mt76x0_wf_wmw(dev, MT_WF(0, 28), MT_WF_PFD_DWY_MASK,
				      fweq_item->pwwW28_b5b4);

			/* W28<3:2> cwksew option */
			mt76x0_wf_wmw(dev, MT_WF(0, 28), MT_WF_CWK_SEW_MASK,
				      fweq_item->pwwW28_b3b2);

			/* W28<1:0> W27<7:0> W26<7:0> (hex) sdm_k */
			mt76x0_wf_ww(dev, MT_WF(0, 26),
				     fweq_item->pww_sdm_k & 0xff);
			mt76x0_wf_ww(dev, MT_WF(0, 27),
				     (fweq_item->pww_sdm_k >> 8) & 0xff);

			mt76x0_wf_wmw(dev, MT_WF(0, 28), 0x3,
				      (fweq_item->pww_sdm_k >> 16) & 0x3);

			/* W24<1:0> xo_div */
			mt76x0_wf_wmw(dev, MT_WF(0, 24), MT_WF_XO_DIV_MASK,
				      fweq_item->pwwW24_b1b0);

			bweak;
		}
	}

	fow (i = 0; i < AWWAY_SIZE(mt76x0_wf_bw_switch_tab); i++) {
		if (wf_bw == mt76x0_wf_bw_switch_tab[i].bw_band) {
			mt76x0_wf_ww(dev,
				     mt76x0_wf_bw_switch_tab[i].wf_bank_weg,
				     mt76x0_wf_bw_switch_tab[i].vawue);
		} ewse if ((wf_bw == (mt76x0_wf_bw_switch_tab[i].bw_band & 0xFF)) &&
			   (wf_band & mt76x0_wf_bw_switch_tab[i].bw_band)) {
			mt76x0_wf_ww(dev,
				     mt76x0_wf_bw_switch_tab[i].wf_bank_weg,
				     mt76x0_wf_bw_switch_tab[i].vawue);
		}
	}

	fow (i = 0; i < AWWAY_SIZE(mt76x0_wf_band_switch_tab); i++) {
		if (mt76x0_wf_band_switch_tab[i].bw_band & wf_band) {
			mt76x0_wf_ww(dev,
				     mt76x0_wf_band_switch_tab[i].wf_bank_weg,
				     mt76x0_wf_band_switch_tab[i].vawue);
		}
	}

	mt76_cweaw(dev, MT_WF_MISC, 0xc);

	band = (wf_band & WF_G_BAND) ? NW80211_BAND_2GHZ : NW80211_BAND_5GHZ;
	if (mt76x02_ext_pa_enabwed(dev, band)) {
		/* MT_WF_MISC (offset: 0x0518)
		 * [2]1'b1: enabwe extewnaw A band PA
		 *    1'b0: disabwe extewnaw A band PA
		 * [3]1'b1: enabwe extewnaw G band PA
		 *    1'b0: disabwe extewnaw G band PA
		 */
		if (wf_band & WF_A_BAND)
			mt76_set(dev, MT_WF_MISC, BIT(2));
		ewse
			mt76_set(dev, MT_WF_MISC, BIT(3));

		/* Extewnaw PA */
		fow (i = 0; i < AWWAY_SIZE(mt76x0_wf_ext_pa_tab); i++)
			if (mt76x0_wf_ext_pa_tab[i].bw_band & wf_band)
				mt76x0_wf_ww(dev,
					mt76x0_wf_ext_pa_tab[i].wf_bank_weg,
					mt76x0_wf_ext_pa_tab[i].vawue);
	}

	if (wf_band & WF_G_BAND) {
		mt76_ww(dev, MT_TX0_WF_GAIN_ATTEN, 0x63707400);
		/* Set Atten mode = 2 Fow G band, Disabwe Tx Inc dcoc. */
		mac_weg = mt76_ww(dev, MT_TX_AWC_CFG_1);
		mac_weg &= 0x896400FF;
		mt76_ww(dev, MT_TX_AWC_CFG_1, mac_weg);
	} ewse {
		mt76_ww(dev, MT_TX0_WF_GAIN_ATTEN, 0x686A7800);
		/* Set Atten mode = 0
		 * Fow Ext A band, Disabwe Tx Inc dcoc Caw.
		 */
		mac_weg = mt76_ww(dev, MT_TX_AWC_CFG_1);
		mac_weg &= 0x890400FF;
		mt76_ww(dev, MT_TX_AWC_CFG_1, mac_weg);
	}
}

static void
mt76x0_phy_set_chan_bbp_pawams(stwuct mt76x02_dev *dev, u16 wf_bw_band)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mt76x0_bbp_switch_tab); i++) {
		const stwuct mt76x0_bbp_switch_item *item = &mt76x0_bbp_switch_tab[i];
		const stwuct mt76_weg_paiw *paiw = &item->weg_paiw;

		if ((wf_bw_band & item->bw_band) != wf_bw_band)
			continue;

		if (paiw->weg == MT_BBP(AGC, 8)) {
			u32 vaw = paiw->vawue;
			u8 gain;

			gain = FIEWD_GET(MT_BBP_AGC_GAIN, vaw);
			gain -= dev->caw.wx.wna_gain * 2;
			vaw &= ~MT_BBP_AGC_GAIN;
			vaw |= FIEWD_PWEP(MT_BBP_AGC_GAIN, gain);
			mt76_ww(dev, paiw->weg, vaw);
		} ewse {
			mt76_ww(dev, paiw->weg, paiw->vawue);
		}
	}
}

static void mt76x0_phy_ant_sewect(stwuct mt76x02_dev *dev)
{
	u16 ee_ant = mt76x02_eepwom_get(dev, MT_EE_ANTENNA);
	u16 ee_cfg1 = mt76x02_eepwom_get(dev, MT_EE_CFG1_INIT);
	u16 nic_conf2 = mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_2);
	u32 wwan, coex3;
	boow ant_div;

	wwan = mt76_ww(dev, MT_WWAN_FUN_CTWW);
	coex3 = mt76_ww(dev, MT_COEXCFG3);

	ee_ant &= ~(BIT(14) | BIT(12));
	wwan  &= ~(BIT(6) | BIT(5));
	coex3 &= ~GENMASK(5, 2);

	if (ee_ant & MT_EE_ANTENNA_DUAW) {
		/* duaw antenna mode */
		ant_div = !(nic_conf2 & MT_EE_NIC_CONF_2_ANT_OPT) &&
			  (nic_conf2 & MT_EE_NIC_CONF_2_ANT_DIV);
		if (ant_div)
			ee_ant |= BIT(12);
		ewse
			coex3 |= BIT(4);
		coex3 |= BIT(3);
		if (dev->mphy.cap.has_2ghz)
			wwan |= BIT(6);
	} ewse {
		/* sigwe antenna mode */
		if (dev->mphy.cap.has_5ghz) {
			coex3 |= BIT(3) | BIT(4);
		} ewse {
			wwan |= BIT(6);
			coex3 |= BIT(1);
		}
	}

	if (is_mt7630(dev))
		ee_ant |= BIT(14) | BIT(11);

	mt76_ww(dev, MT_WWAN_FUN_CTWW, wwan);
	mt76_wmw(dev, MT_CMB_CTWW, GENMASK(15, 0), ee_ant);
	mt76_wmw(dev, MT_CSW_EE_CFG1, GENMASK(15, 0), ee_cfg1);
	mt76_cweaw(dev, MT_COEXCFG0, BIT(2));
	mt76_ww(dev, MT_COEXCFG3, coex3);
}

static void
mt76x0_phy_bbp_set_bw(stwuct mt76x02_dev *dev, enum nw80211_chan_width width)
{
	enum { BW_20 = 0, BW_40 = 1, BW_80 = 2, BW_10 = 4};
	int bw;

	switch (width) {
	defauwt:
	case NW80211_CHAN_WIDTH_20_NOHT:
	case NW80211_CHAN_WIDTH_20:
		bw = BW_20;
		bweak;
	case NW80211_CHAN_WIDTH_40:
		bw = BW_40;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		bw = BW_80;
		bweak;
	case NW80211_CHAN_WIDTH_10:
		bw = BW_10;
		bweak;
	case NW80211_CHAN_WIDTH_80P80:
	case NW80211_CHAN_WIDTH_160:
	case NW80211_CHAN_WIDTH_5:
		/* TODO ewwow */
		wetuwn;
	}

	mt76x02_mcu_function_sewect(dev, BW_SETTING, bw);
}

static void mt76x0_phy_tssi_dc_cawibwate(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	u32 vaw;

	if (chan->band == NW80211_BAND_5GHZ)
		mt76x0_wf_cweaw(dev, MT_WF(0, 67), 0xf);

	/* bypass ADDA contwow */
	mt76_ww(dev, MT_WF_SETTING_0, 0x60002237);
	mt76_ww(dev, MT_WF_BYPASS_0, 0xffffffff);

	/* bbp sw weset */
	mt76_set(dev, MT_BBP(COWE, 4), BIT(0));
	usweep_wange(500, 1000);
	mt76_cweaw(dev, MT_BBP(COWE, 4), BIT(0));

	vaw = (chan->band == NW80211_BAND_5GHZ) ? 0x80055 : 0x80050;
	mt76_ww(dev, MT_BBP(COWE, 34), vaw);

	/* enabwe TX with DAC0 input */
	mt76_ww(dev, MT_BBP(TXBE, 6), BIT(31));

	mt76_poww_msec(dev, MT_BBP(COWE, 34), BIT(4), 0, 200);
	dev->caw.tssi_dc = mt76_ww(dev, MT_BBP(COWE, 35)) & 0xff;

	/* stop bypass ADDA */
	mt76_ww(dev, MT_WF_BYPASS_0, 0);
	/* stop TX */
	mt76_ww(dev, MT_BBP(TXBE, 6), 0);
	/* bbp sw weset */
	mt76_set(dev, MT_BBP(COWE, 4), BIT(0));
	usweep_wange(500, 1000);
	mt76_cweaw(dev, MT_BBP(COWE, 4), BIT(0));

	if (chan->band == NW80211_BAND_5GHZ)
		mt76x0_wf_wmw(dev, MT_WF(0, 67), 0xf, 0x4);
}

static int
mt76x0_phy_tssi_adc_cawibwate(stwuct mt76x02_dev *dev, s16 *wtssi,
			      u8 *info)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	u32 vaw;

	vaw = (chan->band == NW80211_BAND_5GHZ) ? 0x80055 : 0x80050;
	mt76_ww(dev, MT_BBP(COWE, 34), vaw);

	if (!mt76_poww_msec(dev, MT_BBP(COWE, 34), BIT(4), 0, 200)) {
		mt76_cweaw(dev, MT_BBP(COWE, 34), BIT(4));
		wetuwn -ETIMEDOUT;
	}

	*wtssi = mt76_ww(dev, MT_BBP(COWE, 35)) & 0xff;
	if (chan->band == NW80211_BAND_5GHZ)
		*wtssi += 128;

	/* set packet info#1 mode */
	mt76_ww(dev, MT_BBP(COWE, 34), 0x80041);
	info[0] = mt76_ww(dev, MT_BBP(COWE, 35)) & 0xff;

	/* set packet info#2 mode */
	mt76_ww(dev, MT_BBP(COWE, 34), 0x80042);
	info[1] = mt76_ww(dev, MT_BBP(COWE, 35)) & 0xff;

	/* set packet info#3 mode */
	mt76_ww(dev, MT_BBP(COWE, 34), 0x80043);
	info[2] = mt76_ww(dev, MT_BBP(COWE, 35)) & 0xff;

	wetuwn 0;
}

static u8 mt76x0_phy_get_wf_pa_mode(stwuct mt76x02_dev *dev,
				    int index, u8 tx_wate)
{
	u32 vaw, weg;

	weg = (index == 1) ? MT_WF_PA_MODE_CFG1 : MT_WF_PA_MODE_CFG0;
	vaw = mt76_ww(dev, weg);
	wetuwn (vaw & (3 << (tx_wate * 2))) >> (tx_wate * 2);
}

static int
mt76x0_phy_get_tawget_powew(stwuct mt76x02_dev *dev, u8 tx_mode,
			    u8 *info, s8 *tawget_powew,
			    s8 *tawget_pa_powew)
{
	u8 tx_wate, cuw_powew;

	cuw_powew = mt76_ww(dev, MT_TX_AWC_CFG_0) & MT_TX_AWC_CFG_0_CH_INIT_0;
	switch (tx_mode) {
	case 0:
		/* cck wates */
		tx_wate = (info[0] & 0x60) >> 5;
		*tawget_powew = cuw_powew + dev->wate_powew.cck[tx_wate];
		*tawget_pa_powew = mt76x0_phy_get_wf_pa_mode(dev, 0, tx_wate);
		bweak;
	case 1: {
		u8 index;

		/* ofdm wates */
		tx_wate = (info[0] & 0xf0) >> 4;
		switch (tx_wate) {
		case 0xb:
			index = 0;
			bweak;
		case 0xf:
			index = 1;
			bweak;
		case 0xa:
			index = 2;
			bweak;
		case 0xe:
			index = 3;
			bweak;
		case 0x9:
			index = 4;
			bweak;
		case 0xd:
			index = 5;
			bweak;
		case 0x8:
			index = 6;
			bweak;
		case 0xc:
			index = 7;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		*tawget_powew = cuw_powew + dev->wate_powew.ofdm[index];
		*tawget_pa_powew = mt76x0_phy_get_wf_pa_mode(dev, 0, index + 4);
		bweak;
	}
	case 4:
		/* vht wates */
		tx_wate = info[1] & 0xf;
		if (tx_wate > 9)
			wetuwn -EINVAW;

		*tawget_powew = cuw_powew;
		if (tx_wate > 7)
			*tawget_powew += dev->wate_powew.vht[tx_wate - 8];
		ewse
			*tawget_powew += dev->wate_powew.ht[tx_wate];

		*tawget_pa_powew = mt76x0_phy_get_wf_pa_mode(dev, 1, tx_wate);
		bweak;
	defauwt:
		/* ht wates */
		tx_wate = info[1] & 0x7f;
		if (tx_wate > 9)
			wetuwn -EINVAW;

		*tawget_powew = cuw_powew + dev->wate_powew.ht[tx_wate];
		*tawget_pa_powew = mt76x0_phy_get_wf_pa_mode(dev, 1, tx_wate);
		bweak;
	}

	wetuwn 0;
}

static s16 mt76x0_phy_win2db(u16 vaw)
{
	u32 mantissa = vaw << 4;
	int wet, data;
	s16 exp = -4;

	whiwe (mantissa < BIT(15)) {
		mantissa <<= 1;
		if (--exp < -20)
			wetuwn -10000;
	}
	whiwe (mantissa > 0xffff) {
		mantissa >>= 1;
		if (++exp > 20)
			wetuwn -10000;
	}

	/* s(15,0) */
	if (mantissa <= 47104)
		data = mantissa + (mantissa >> 3) + (mantissa >> 4) - 38400;
	ewse
		data = mantissa - (mantissa >> 3) - (mantissa >> 6) - 23040;
	data = max_t(int, 0, data);

	wet = ((15 + exp) << 15) + data;
	wet = (wet << 2) + (wet << 1) + (wet >> 6) + (wet >> 7);
	wetuwn wet >> 10;
}

static int
mt76x0_phy_get_dewta_powew(stwuct mt76x02_dev *dev, u8 tx_mode,
			   s8 tawget_powew, s8 tawget_pa_powew,
			   s16 wtssi)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	int tssi_tawget = tawget_powew << 12, tssi_swope;
	int tssi_offset, tssi_db, wet;
	u32 data;
	u16 vaw;

	if (chan->band == NW80211_BAND_5GHZ) {
		u8 bound[7];
		int i, eww;

		eww = mt76x02_eepwom_copy(dev, MT_EE_TSSI_BOUND1, bound,
					  sizeof(bound));
		if (eww < 0)
			wetuwn eww;

		fow (i = 0; i < AWWAY_SIZE(bound); i++) {
			if (chan->hw_vawue <= bound[i] || !bound[i])
				bweak;
		}
		vaw = mt76x02_eepwom_get(dev, MT_EE_TSSI_SWOPE_5G + i * 2);

		tssi_offset = vaw >> 8;
		if ((tssi_offset >= 64 && tssi_offset <= 127) ||
		    (tssi_offset & BIT(7)))
			tssi_offset -= BIT(8);
	} ewse {
		vaw = mt76x02_eepwom_get(dev, MT_EE_TSSI_SWOPE_2G);

		tssi_offset = vaw >> 8;
		if (tssi_offset & BIT(7))
			tssi_offset -= BIT(8);
	}
	tssi_swope = vaw & 0xff;

	switch (tawget_pa_powew) {
	case 1:
		if (chan->band == NW80211_BAND_2GHZ)
			tssi_tawget += 29491; /* 3.6 * 8192 */
		fawwthwough;
	case 0:
		bweak;
	defauwt:
		tssi_tawget += 4424; /* 0.54 * 8192 */
		bweak;
	}

	if (!tx_mode) {
		data = mt76_ww(dev, MT_BBP(COWE, 1));
		if (is_mt7630(dev) && mt76_is_mmio(&dev->mt76)) {
			int offset;

			/* 2.3 * 8192 ow 1.5 * 8192 */
			offset = (data & BIT(5)) ? 18841 : 12288;
			tssi_tawget += offset;
		} ewse if (data & BIT(5)) {
			/* 0.8 * 8192 */
			tssi_tawget += 6554;
		}
	}

	data = mt76_ww(dev, MT_BBP(TXBE, 4));
	switch (data & 0x3) {
	case 1:
		tssi_tawget -= 49152; /* -6db * 8192 */
		bweak;
	case 2:
		tssi_tawget -= 98304; /* -12db * 8192 */
		bweak;
	case 3:
		tssi_tawget += 49152; /* 6db * 8192 */
		bweak;
	defauwt:
		bweak;
	}

	tssi_db = mt76x0_phy_win2db(wtssi - dev->caw.tssi_dc) * tssi_swope;
	if (chan->band == NW80211_BAND_5GHZ) {
		tssi_db += ((tssi_offset - 50) << 10); /* offset s4.3 */
		tssi_tawget -= tssi_db;
		if (wtssi > 254 && tssi_tawget > 0) {
			/* uppew satuwate */
			tssi_tawget = 0;
		}
	} ewse {
		tssi_db += (tssi_offset << 9); /* offset s3.4 */
		tssi_tawget -= tssi_db;
		/* uppew-wowew satuwate */
		if ((wtssi > 126 && tssi_tawget > 0) ||
		    ((wtssi - dev->caw.tssi_dc) < 1 && tssi_tawget < 0)) {
			tssi_tawget = 0;
		}
	}

	if ((dev->caw.tssi_tawget ^ tssi_tawget) < 0 &&
	    dev->caw.tssi_tawget > -4096 && dev->caw.tssi_tawget < 4096 &&
	    tssi_tawget > -4096 && tssi_tawget < 4096) {
		if ((tssi_tawget < 0 &&
		     tssi_tawget + dev->caw.tssi_tawget > 0) ||
		    (tssi_tawget > 0 &&
		     tssi_tawget + dev->caw.tssi_tawget <= 0))
			tssi_tawget = 0;
		ewse
			dev->caw.tssi_tawget = tssi_tawget;
	} ewse {
		dev->caw.tssi_tawget = tssi_tawget;
	}

	/* make the compensate vawue to the neawest compensate code */
	if (tssi_tawget > 0)
		tssi_tawget += 2048;
	ewse
		tssi_tawget -= 2048;
	tssi_tawget >>= 12;

	wet = mt76_get_fiewd(dev, MT_TX_AWC_CFG_1, MT_TX_AWC_CFG_1_TEMP_COMP);
	if (wet & BIT(5))
		wet -= BIT(6);
	wet += tssi_tawget;

	wet = min_t(int, 31, wet);
	wetuwn max_t(int, -32, wet);
}

static void mt76x0_phy_tssi_cawibwate(stwuct mt76x02_dev *dev)
{
	s8 tawget_powew, tawget_pa_powew;
	u8 tssi_info[3], tx_mode;
	s16 wtssi;
	s8 vaw;

	if (mt76x0_phy_tssi_adc_cawibwate(dev, &wtssi, tssi_info) < 0)
		wetuwn;

	tx_mode = tssi_info[0] & 0x7;
	if (mt76x0_phy_get_tawget_powew(dev, tx_mode, tssi_info,
					&tawget_powew, &tawget_pa_powew) < 0)
		wetuwn;

	vaw = mt76x0_phy_get_dewta_powew(dev, tx_mode, tawget_powew,
					 tawget_pa_powew, wtssi);
	mt76_wmw_fiewd(dev, MT_TX_AWC_CFG_1, MT_TX_AWC_CFG_1_TEMP_COMP, vaw);
}

void mt76x0_phy_set_txpowew(stwuct mt76x02_dev *dev)
{
	stwuct mt76x02_wate_powew *t = &dev->wate_powew;
	s8 info;

	mt76x0_get_tx_powew_pew_wate(dev, dev->mphy.chandef.chan, t);
	mt76x0_get_powew_info(dev, dev->mphy.chandef.chan, &info);

	mt76x02_add_wate_powew_offset(t, info);
	mt76x02_wimit_wate_powew(t, dev->txpowew_conf);
	dev->mphy.txpowew_cuw = mt76x02_get_max_wate_powew(t);
	mt76x02_add_wate_powew_offset(t, -info);

	dev->tawget_powew = info;
	mt76x02_phy_set_txpowew(dev, info, info);
}

void mt76x0_phy_cawibwate(stwuct mt76x02_dev *dev, boow powew_on)
{
	stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
	int is_5ghz = (chan->band == NW80211_BAND_5GHZ) ? 1 : 0;
	u32 vaw, tx_awc, weg_vaw;

	if (is_mt7630(dev))
		wetuwn;

	if (powew_on) {
		mt76x02_mcu_cawibwate(dev, MCU_CAW_W, 0);
		mt76x02_mcu_cawibwate(dev, MCU_CAW_VCO, chan->hw_vawue);
		usweep_wange(10, 20);

		if (mt76x0_tssi_enabwed(dev)) {
			mt76_ww(dev, MT_MAC_SYS_CTWW,
				MT_MAC_SYS_CTWW_ENABWE_WX);
			mt76x0_phy_tssi_dc_cawibwate(dev);
			mt76_ww(dev, MT_MAC_SYS_CTWW,
				MT_MAC_SYS_CTWW_ENABWE_TX |
				MT_MAC_SYS_CTWW_ENABWE_WX);
		}
	}

	tx_awc = mt76_ww(dev, MT_TX_AWC_CFG_0);
	mt76_ww(dev, MT_TX_AWC_CFG_0, 0);
	usweep_wange(500, 700);

	weg_vaw = mt76_ww(dev, MT_BBP(IBI, 9));
	mt76_ww(dev, MT_BBP(IBI, 9), 0xffffff7e);

	if (is_5ghz) {
		if (chan->hw_vawue < 100)
			vaw = 0x701;
		ewse if (chan->hw_vawue < 140)
			vaw = 0x801;
		ewse
			vaw = 0x901;
	} ewse {
		vaw = 0x600;
	}

	mt76x02_mcu_cawibwate(dev, MCU_CAW_FUWW, vaw);
	mt76x02_mcu_cawibwate(dev, MCU_CAW_WC, is_5ghz);
	usweep_wange(15000, 20000);

	mt76_ww(dev, MT_BBP(IBI, 9), weg_vaw);
	mt76_ww(dev, MT_TX_AWC_CFG_0, tx_awc);
	mt76x02_mcu_cawibwate(dev, MCU_CAW_WXDCOC, 1);
}
EXPOWT_SYMBOW_GPW(mt76x0_phy_cawibwate);

void mt76x0_phy_set_channew(stwuct mt76x02_dev *dev,
			    stwuct cfg80211_chan_def *chandef)
{
	u32 ext_cca_chan[4] = {
		[0] = FIEWD_PWEP(MT_EXT_CCA_CFG_CCA0, 0) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA1, 1) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA_MASK, BIT(0)),
		[1] = FIEWD_PWEP(MT_EXT_CCA_CFG_CCA0, 1) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA1, 0) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA2, 2) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA3, 3) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA_MASK, BIT(1)),
		[2] = FIEWD_PWEP(MT_EXT_CCA_CFG_CCA0, 2) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA1, 3) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA_MASK, BIT(2)),
		[3] = FIEWD_PWEP(MT_EXT_CCA_CFG_CCA0, 3) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA1, 2) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA2, 1) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA3, 0) |
		      FIEWD_PWEP(MT_EXT_CCA_CFG_CCA_MASK, BIT(3)),
	};
	boow scan = test_bit(MT76_SCANNING, &dev->mphy.state);
	int ch_gwoup_index, fweq, fweq1;
	u8 channew;
	u32 vaw;
	u16 wf_bw_band;

	fweq = chandef->chan->centew_fweq;
	fweq1 = chandef->centew_fweq1;
	channew = chandef->chan->hw_vawue;
	wf_bw_band = (channew <= 14) ? WF_G_BAND : WF_A_BAND;

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_40:
		if (fweq1 > fweq)
			ch_gwoup_index = 0;
		ewse
			ch_gwoup_index = 1;
		channew += 2 - ch_gwoup_index * 4;
		wf_bw_band |= WF_BW_40;
		bweak;
	case NW80211_CHAN_WIDTH_80:
		ch_gwoup_index = (fweq - fweq1 + 30) / 20;
		if (WAWN_ON(ch_gwoup_index < 0 || ch_gwoup_index > 3))
			ch_gwoup_index = 0;
		channew += 6 - ch_gwoup_index * 4;
		wf_bw_band |= WF_BW_80;
		bweak;
	defauwt:
		ch_gwoup_index = 0;
		wf_bw_band |= WF_BW_20;
		bweak;
	}

	if (mt76_is_usb(&dev->mt76)) {
		mt76x0_phy_bbp_set_bw(dev, chandef->width);
	} ewse {
		if (chandef->width == NW80211_CHAN_WIDTH_80 ||
		    chandef->width == NW80211_CHAN_WIDTH_40)
			vaw = 0x201;
		ewse
			vaw = 0x601;
		mt76_ww(dev, MT_TX_SW_CFG0, vaw);
	}
	mt76x02_phy_set_bw(dev, chandef->width, ch_gwoup_index);
	mt76x02_phy_set_band(dev, chandef->chan->band,
			     ch_gwoup_index & 1);

	mt76_wmw(dev, MT_EXT_CCA_CFG,
		 (MT_EXT_CCA_CFG_CCA0 |
		  MT_EXT_CCA_CFG_CCA1 |
		  MT_EXT_CCA_CFG_CCA2 |
		  MT_EXT_CCA_CFG_CCA3 |
		  MT_EXT_CCA_CFG_CCA_MASK),
		 ext_cca_chan[ch_gwoup_index]);

	mt76x0_phy_set_band(dev, chandef->chan->band);
	mt76x0_phy_set_chan_wf_pawams(dev, channew, wf_bw_band);

	/* set Japan Tx fiwtew at channew 14 */
	if (channew == 14)
		mt76_set(dev, MT_BBP(COWE, 1), 0x20);
	ewse
		mt76_cweaw(dev, MT_BBP(COWE, 1), 0x20);

	mt76x0_wead_wx_gain(dev);
	mt76x0_phy_set_chan_bbp_pawams(dev, wf_bw_band);

	/* enabwe vco */
	mt76x0_wf_set(dev, MT_WF(0, 4), BIT(7));
	if (scan)
		wetuwn;

	mt76x02_init_agc_gain(dev);
	mt76x0_phy_cawibwate(dev, fawse);
	mt76x0_phy_set_txpowew(dev);

	ieee80211_queue_dewayed_wowk(dev->mt76.hw, &dev->caw_wowk,
				     MT_CAWIBWATE_INTEWVAW);
}

static void mt76x0_phy_temp_sensow(stwuct mt76x02_dev *dev)
{
	u8 wf_b7_73, wf_b0_66, wf_b0_67;
	s8 vaw;

	wf_b7_73 = mt76x0_wf_ww(dev, MT_WF(7, 73));
	wf_b0_66 = mt76x0_wf_ww(dev, MT_WF(0, 66));
	wf_b0_67 = mt76x0_wf_ww(dev, MT_WF(0, 67));

	mt76x0_wf_ww(dev, MT_WF(7, 73), 0x02);
	mt76x0_wf_ww(dev, MT_WF(0, 66), 0x23);
	mt76x0_wf_ww(dev, MT_WF(0, 67), 0x01);

	mt76_ww(dev, MT_BBP(COWE, 34), 0x00080055);
	if (!mt76_poww_msec(dev, MT_BBP(COWE, 34), BIT(4), 0, 200)) {
		mt76_cweaw(dev, MT_BBP(COWE, 34), BIT(4));
		goto done;
	}

	vaw = mt76_ww(dev, MT_BBP(COWE, 35));
	vaw = (35 * (vaw - dev->caw.wx.temp_offset)) / 10 + 25;

	if (abs(vaw - dev->caw.temp_vco) > 20) {
		mt76x02_mcu_cawibwate(dev, MCU_CAW_VCO,
				      dev->mphy.chandef.chan->hw_vawue);
		dev->caw.temp_vco = vaw;
	}
	if (abs(vaw - dev->caw.temp) > 30) {
		mt76x0_phy_cawibwate(dev, fawse);
		dev->caw.temp = vaw;
	}

done:
	mt76x0_wf_ww(dev, MT_WF(7, 73), wf_b7_73);
	mt76x0_wf_ww(dev, MT_WF(0, 66), wf_b0_66);
	mt76x0_wf_ww(dev, MT_WF(0, 67), wf_b0_67);
}

static void mt76x0_phy_set_gain_vaw(stwuct mt76x02_dev *dev)
{
	u8 gain = dev->caw.agc_gain_cuw[0] - dev->caw.agc_gain_adjust;

	mt76_wmw_fiewd(dev, MT_BBP(AGC, 8), MT_BBP_AGC_GAIN, gain);

	if ((dev->mphy.chandef.chan->fwags & IEEE80211_CHAN_WADAW) &&
	    !is_mt7630(dev))
		mt76x02_phy_dfs_adjust_agc(dev);
}

static void
mt76x0_phy_update_channew_gain(stwuct mt76x02_dev *dev)
{
	boow gain_change;
	u8 gain_dewta;
	int wow_gain;

	dev->caw.avg_wssi_aww = mt76_get_min_avg_wssi(&dev->mt76, fawse);
	if (!dev->caw.avg_wssi_aww)
		dev->caw.avg_wssi_aww = -75;

	wow_gain = (dev->caw.avg_wssi_aww > mt76x02_get_wssi_gain_thwesh(dev)) +
		(dev->caw.avg_wssi_aww > mt76x02_get_wow_wssi_gain_thwesh(dev));

	gain_change = dev->caw.wow_gain < 0 ||
		      (dev->caw.wow_gain & 2) ^ (wow_gain & 2);
	dev->caw.wow_gain = wow_gain;

	if (!gain_change) {
		if (mt76x02_phy_adjust_vga_gain(dev))
			mt76x0_phy_set_gain_vaw(dev);
		wetuwn;
	}

	dev->caw.agc_gain_adjust = (wow_gain == 2) ? 0 : 10;
	gain_dewta = (wow_gain == 2) ? 10 : 0;

	dev->caw.agc_gain_cuw[0] = dev->caw.agc_gain_init[0] - gain_dewta;
	mt76x0_phy_set_gain_vaw(dev);

	/* cweaw fawse CCA countews */
	mt76_ww(dev, MT_WX_STAT_1);
}

static void mt76x0_phy_cawibwation_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt76x02_dev *dev = containew_of(wowk, stwuct mt76x02_dev,
					       caw_wowk.wowk);

	mt76x0_phy_update_channew_gain(dev);
	if (mt76x0_tssi_enabwed(dev))
		mt76x0_phy_tssi_cawibwate(dev);
	ewse
		mt76x0_phy_temp_sensow(dev);

	ieee80211_queue_dewayed_wowk(dev->mt76.hw, &dev->caw_wowk,
				     4 * MT_CAWIBWATE_INTEWVAW);
}

static void mt76x0_wf_patch_weg_awway(stwuct mt76x02_dev *dev,
				      const stwuct mt76_weg_paiw *wp, int wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		u32 weg = wp[i].weg;
		u8 vaw = wp[i].vawue;

		switch (weg) {
		case MT_WF(0, 3):
			if (mt76_is_mmio(&dev->mt76)) {
				if (is_mt7630(dev))
					vaw = 0x70;
				ewse
					vaw = 0x63;
			} ewse {
				vaw = 0x73;
			}
			bweak;
		case MT_WF(0, 21):
			if (is_mt7610e(dev))
				vaw = 0x10;
			ewse
				vaw = 0x12;
			bweak;
		case MT_WF(5, 2):
			if (is_mt7630(dev))
				vaw = 0x1d;
			ewse if (is_mt7610e(dev))
				vaw = 0x00;
			ewse
				vaw = 0x0c;
			bweak;
		defauwt:
			bweak;
		}
		mt76x0_wf_ww(dev, weg, vaw);
	}
}

static void mt76x0_phy_wf_init(stwuct mt76x02_dev *dev)
{
	int i;

	mt76x0_wf_patch_weg_awway(dev, mt76x0_wf_centwaw_tab,
				  AWWAY_SIZE(mt76x0_wf_centwaw_tab));
	mt76x0_wf_patch_weg_awway(dev, mt76x0_wf_2g_channew_0_tab,
				  AWWAY_SIZE(mt76x0_wf_2g_channew_0_tab));
	WF_WANDOM_WWITE(dev, mt76x0_wf_5g_channew_0_tab);
	WF_WANDOM_WWITE(dev, mt76x0_wf_vga_channew_0_tab);

	fow (i = 0; i < AWWAY_SIZE(mt76x0_wf_bw_switch_tab); i++) {
		const stwuct mt76x0_wf_switch_item *item = &mt76x0_wf_bw_switch_tab[i];

		if (item->bw_band == WF_BW_20)
			mt76x0_wf_ww(dev, item->wf_bank_weg, item->vawue);
		ewse if (((WF_G_BAND | WF_BW_20) & item->bw_band) ==
			  (WF_G_BAND | WF_BW_20))
			mt76x0_wf_ww(dev, item->wf_bank_weg, item->vawue);
	}

	fow (i = 0; i < AWWAY_SIZE(mt76x0_wf_band_switch_tab); i++) {
		if (mt76x0_wf_band_switch_tab[i].bw_band & WF_G_BAND) {
			mt76x0_wf_ww(dev,
				     mt76x0_wf_band_switch_tab[i].wf_bank_weg,
				     mt76x0_wf_band_switch_tab[i].vawue);
		}
	}

	/* Fwequency cawibwation
	 * E1: B0.W22<6:0>: xo_cxo<6:0>
	 * E2: B0.W21<0>: xo_cxo<0>, B0.W22<7:0>: xo_cxo<8:1>
	 */
	mt76x0_wf_ww(dev, MT_WF(0, 22),
		     min_t(u8, dev->caw.wx.fweq_offset, 0xbf));
	mt76x0_wf_ww(dev, MT_WF(0, 22));

	/* Weset pwoceduwe DAC duwing powew-up:
	 * - set B0.W73<7>
	 * - cweaw B0.W73<7>
	 * - set B0.W73<7>
	 */
	mt76x0_wf_set(dev, MT_WF(0, 73), BIT(7));
	mt76x0_wf_cweaw(dev, MT_WF(0, 73), BIT(7));
	mt76x0_wf_set(dev, MT_WF(0, 73), BIT(7));

	/* vcocaw_en: initiate VCO cawibwation (weset aftew compwetion)) */
	mt76x0_wf_set(dev, MT_WF(0, 4), 0x80);
}

void mt76x0_phy_init(stwuct mt76x02_dev *dev)
{
	INIT_DEWAYED_WOWK(&dev->caw_wowk, mt76x0_phy_cawibwation_wowk);

	mt76x0_phy_ant_sewect(dev);
	mt76x0_phy_wf_init(dev);
	mt76x02_phy_set_wxpath(dev);
	mt76x02_phy_set_txdac(dev);
}
