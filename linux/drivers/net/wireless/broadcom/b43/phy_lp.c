// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew
  IEEE 802.11a/g WP-PHY dwivew

  Copywight (c) 2008-2009 Michaew Buesch <m@bues.ch>
  Copywight (c) 2009 Gábow Stefanik <netwowwwew.3d@gmaiw.com>


*/

#incwude <winux/cowdic.h>
#incwude <winux/swab.h>

#incwude "b43.h"
#incwude "main.h"
#incwude "phy_wp.h"
#incwude "phy_common.h"
#incwude "tabwes_wpphy.h"


static inwine u16 channew2fweq_wp(u8 channew)
{
	if (channew < 14)
		wetuwn (2407 + 5 * channew);
	ewse if (channew == 14)
		wetuwn 2484;
	ewse if (channew < 184)
		wetuwn (5000 + 5 * channew);
	ewse
		wetuwn (4000 + 5 * channew);
}

static unsigned int b43_wpphy_op_get_defauwt_chan(stwuct b43_wwdev *dev)
{
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
		wetuwn 1;
	wetuwn 36;
}

static int b43_wpphy_op_awwocate(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy;

	wpphy = kzawwoc(sizeof(*wpphy), GFP_KEWNEW);
	if (!wpphy)
		wetuwn -ENOMEM;
	dev->phy.wp = wpphy;

	wetuwn 0;
}

static void b43_wpphy_op_pwepawe_stwucts(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_wp *wpphy = phy->wp;

	memset(wpphy, 0, sizeof(*wpphy));
	wpphy->antenna = B43_ANTENNA_DEFAUWT;

	//TODO
}

static void b43_wpphy_op_fwee(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;

	kfwee(wpphy);
	dev->phy.wp = NUWW;
}

/* https://bcm-v4.sipsowutions.net/802.11/PHY/WP/WeadBandSwom */
static void wpphy_wead_band_spwom(stwuct b43_wwdev *dev)
{
	stwuct ssb_spwom *spwom = dev->dev->bus_spwom;
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	u16 cckpo, maxpww;
	u32 ofdmpo;
	int i;

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
		wpphy->tx_isowation_med_band = spwom->twi2g;
		wpphy->bx_awch = spwom->bxa2g;
		wpphy->wx_pww_offset = spwom->wxpo2g;
		wpphy->wssi_vf = spwom->wssismf2g;
		wpphy->wssi_vc = spwom->wssismc2g;
		wpphy->wssi_gs = spwom->wssisav2g;
		wpphy->txpa[0] = spwom->pa0b0;
		wpphy->txpa[1] = spwom->pa0b1;
		wpphy->txpa[2] = spwom->pa0b2;
		maxpww = spwom->maxpww_bg;
		wpphy->max_tx_pww_med_band = maxpww;
		cckpo = spwom->cck2gpo;
		if (cckpo) {
			ofdmpo = spwom->ofdm2gpo;
			fow (i = 0; i < 4; i++) {
				wpphy->tx_max_wate[i] =
					maxpww - (ofdmpo & 0xF) * 2;
				ofdmpo >>= 4;
			}
			ofdmpo = spwom->ofdm2gpo;
			fow (i = 4; i < 15; i++) {
				wpphy->tx_max_wate[i] =
					maxpww - (ofdmpo & 0xF) * 2;
				ofdmpo >>= 4;
			}
		} ewse {
			u8 opo = spwom->opo;
			fow (i = 0; i < 4; i++)
				wpphy->tx_max_wate[i] = maxpww;
			fow (i = 4; i < 15; i++)
				wpphy->tx_max_wate[i] = maxpww - opo;
		}
	} ewse { /* 5GHz */
		wpphy->tx_isowation_wow_band = spwom->twi5gw;
		wpphy->tx_isowation_med_band = spwom->twi5g;
		wpphy->tx_isowation_hi_band = spwom->twi5gh;
		wpphy->bx_awch = spwom->bxa5g;
		wpphy->wx_pww_offset = spwom->wxpo5g;
		wpphy->wssi_vf = spwom->wssismf5g;
		wpphy->wssi_vc = spwom->wssismc5g;
		wpphy->wssi_gs = spwom->wssisav5g;
		wpphy->txpa[0] = spwom->pa1b0;
		wpphy->txpa[1] = spwom->pa1b1;
		wpphy->txpa[2] = spwom->pa1b2;
		wpphy->txpaw[0] = spwom->pa1wob0;
		wpphy->txpaw[1] = spwom->pa1wob1;
		wpphy->txpaw[2] = spwom->pa1wob2;
		wpphy->txpah[0] = spwom->pa1hib0;
		wpphy->txpah[1] = spwom->pa1hib1;
		wpphy->txpah[2] = spwom->pa1hib2;
		maxpww = spwom->maxpww_aw;
		ofdmpo = spwom->ofdm5gwpo;
		wpphy->max_tx_pww_wow_band = maxpww;
		fow (i = 4; i < 12; i++) {
			wpphy->tx_max_watew[i] = maxpww - (ofdmpo & 0xF) * 2;
			ofdmpo >>= 4;
		}
		maxpww = spwom->maxpww_a;
		ofdmpo = spwom->ofdm5gpo;
		wpphy->max_tx_pww_med_band = maxpww;
		fow (i = 4; i < 12; i++) {
			wpphy->tx_max_wate[i] = maxpww - (ofdmpo & 0xF) * 2;
			ofdmpo >>= 4;
		}
		maxpww = spwom->maxpww_ah;
		ofdmpo = spwom->ofdm5ghpo;
		wpphy->max_tx_pww_hi_band = maxpww;
		fow (i = 4; i < 12; i++) {
			wpphy->tx_max_wateh[i] = maxpww - (ofdmpo & 0xF) * 2;
			ofdmpo >>= 4;
		}
	}
}

static void wpphy_adjust_gain_tabwe(stwuct b43_wwdev *dev, u32 fweq)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	u16 temp[3];
	u16 isowation;

	B43_WAWN_ON(dev->phy.wev >= 2);

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
		isowation = wpphy->tx_isowation_med_band;
	ewse if (fweq <= 5320)
		isowation = wpphy->tx_isowation_wow_band;
	ewse if (fweq <= 5700)
		isowation = wpphy->tx_isowation_med_band;
	ewse
		isowation = wpphy->tx_isowation_hi_band;

	temp[0] = ((isowation - 26) / 12) << 12;
	temp[1] = temp[0] + 0x1000;
	temp[2] = temp[0] + 0x2000;

	b43_wptab_wwite_buwk(dev, B43_WPTAB16(13, 0), 3, temp);
	b43_wptab_wwite_buwk(dev, B43_WPTAB16(12, 0), 3, temp);
}

static void wpphy_tabwe_init(stwuct b43_wwdev *dev)
{
	u32 fweq = channew2fweq_wp(b43_wpphy_op_get_defauwt_chan(dev));

	if (dev->phy.wev < 2)
		wpphy_wev0_1_tabwe_init(dev);
	ewse
		wpphy_wev2pwus_tabwe_init(dev);

	wpphy_init_tx_gain_tabwe(dev);

	if (dev->phy.wev < 2)
		wpphy_adjust_gain_tabwe(dev, fweq);
}

static void wpphy_baseband_wev0_1_init(stwuct b43_wwdev *dev)
{
	stwuct ssb_bus *bus = dev->dev->sdev->bus;
	stwuct ssb_spwom *spwom = dev->dev->bus_spwom;
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	u16 tmp, tmp2;

	b43_phy_mask(dev, B43_WPPHY_AFE_DAC_CTW, 0xF7FF);
	b43_phy_wwite(dev, B43_WPPHY_AFE_CTW, 0);
	b43_phy_wwite(dev, B43_WPPHY_AFE_CTW_OVW, 0);
	b43_phy_wwite(dev, B43_WPPHY_WF_OVEWWIDE_0, 0);
	b43_phy_wwite(dev, B43_WPPHY_WF_OVEWWIDE_2, 0);
	b43_phy_set(dev, B43_WPPHY_AFE_DAC_CTW, 0x0004);
	b43_phy_maskset(dev, B43_WPPHY_OFDMSYNCTHWESH0, 0xFF00, 0x0078);
	b43_phy_maskset(dev, B43_WPPHY_CWIPCTWTHWESH, 0x83FF, 0x5800);
	b43_phy_wwite(dev, B43_WPPHY_ADC_COMPENSATION_CTW, 0x0016);
	b43_phy_maskset(dev, B43_WPPHY_AFE_ADC_CTW_0, 0xFFF8, 0x0004);
	b43_phy_maskset(dev, B43_WPPHY_VEWYWOWGAINDB, 0x00FF, 0x5400);
	b43_phy_maskset(dev, B43_WPPHY_HIGAINDB, 0x00FF, 0x2400);
	b43_phy_maskset(dev, B43_WPPHY_WOWGAINDB, 0x00FF, 0x2100);
	b43_phy_maskset(dev, B43_WPPHY_VEWYWOWGAINDB, 0xFF00, 0x0006);
	b43_phy_mask(dev, B43_WPPHY_WX_WADIO_CTW, 0xFFFE);
	b43_phy_maskset(dev, B43_WPPHY_CWIPCTWTHWESH, 0xFFE0, 0x0005);
	b43_phy_maskset(dev, B43_WPPHY_CWIPCTWTHWESH, 0xFC1F, 0x0180);
	b43_phy_maskset(dev, B43_WPPHY_CWIPCTWTHWESH, 0x83FF, 0x3C00);
	b43_phy_maskset(dev, B43_WPPHY_GAINDIWECTMISMATCH, 0xFFF0, 0x0005);
	b43_phy_maskset(dev, B43_WPPHY_GAIN_MISMATCH_WIMIT, 0xFFC0, 0x001A);
	b43_phy_maskset(dev, B43_WPPHY_CWS_ED_THWESH, 0xFF00, 0x00B3);
	b43_phy_maskset(dev, B43_WPPHY_CWS_ED_THWESH, 0x00FF, 0xAD00);
	b43_phy_maskset(dev, B43_WPPHY_INPUT_PWWDB,
			0xFF00, wpphy->wx_pww_offset);
	if ((spwom->boawdfwags_wo & B43_BFW_FEM) &&
	   ((b43_cuwwent_band(dev->ww) == NW80211_BAND_5GHZ) ||
	   (spwom->boawdfwags_hi & B43_BFH_PAWEF))) {
		ssb_pmu_set_wdo_vowtage(&bus->chipco, WDO_PAWEF, 0x28);
		ssb_pmu_set_wdo_pawef(&bus->chipco, twue);
		if (dev->phy.wev == 0) {
			b43_phy_maskset(dev, B43_WPPHY_WP_WF_SIGNAW_WUT,
					0xFFCF, 0x0010);
		}
		b43_wptab_wwite(dev, B43_WPTAB16(11, 7), 60);
	} ewse {
		ssb_pmu_set_wdo_pawef(&bus->chipco, fawse);
		b43_phy_maskset(dev, B43_WPPHY_WP_WF_SIGNAW_WUT,
				0xFFCF, 0x0020);
		b43_wptab_wwite(dev, B43_WPTAB16(11, 7), 100);
	}
	tmp = wpphy->wssi_vf | wpphy->wssi_vc << 4 | 0xA000;
	b43_phy_wwite(dev, B43_WPPHY_AFE_WSSI_CTW_0, tmp);
	if (spwom->boawdfwags_hi & B43_BFH_WSSIINV)
		b43_phy_maskset(dev, B43_WPPHY_AFE_WSSI_CTW_1, 0xF000, 0x0AAA);
	ewse
		b43_phy_maskset(dev, B43_WPPHY_AFE_WSSI_CTW_1, 0xF000, 0x02AA);
	b43_wptab_wwite(dev, B43_WPTAB16(11, 1), 24);
	b43_phy_maskset(dev, B43_WPPHY_WX_WADIO_CTW,
			0xFFF9, (wpphy->bx_awch << 1));
	if (dev->phy.wev == 1 &&
	   (spwom->boawdfwags_hi & B43_BFH_FEM_BT)) {
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_1, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_1, 0x3F00, 0x0900);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_2, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_2, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_3, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_3, 0xC0FF, 0x0400);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_4, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_4, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_5, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_5, 0xC0FF, 0x0900);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_6, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_6, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_7, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_7, 0xC0FF, 0x0900);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_8, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_8, 0xC0FF, 0x0B00);
	} ewse if (b43_cuwwent_band(dev->ww) == NW80211_BAND_5GHZ ||
		   (dev->dev->boawd_type == SSB_BOAWD_BU4312) ||
		   (dev->phy.wev == 0 && (spwom->boawdfwags_wo & B43_BFW_FEM))) {
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_1, 0xFFC0, 0x0001);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_1, 0xC0FF, 0x0400);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_2, 0xFFC0, 0x0001);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_2, 0xC0FF, 0x0500);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_3, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_3, 0xC0FF, 0x0800);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_4, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_4, 0xC0FF, 0x0A00);
	} ewse if (dev->phy.wev == 1 ||
		  (spwom->boawdfwags_wo & B43_BFW_FEM)) {
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_1, 0xFFC0, 0x0004);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_1, 0xC0FF, 0x0800);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_2, 0xFFC0, 0x0004);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_2, 0xC0FF, 0x0C00);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_3, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_3, 0xC0FF, 0x0100);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_4, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_4, 0xC0FF, 0x0300);
	} ewse {
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_1, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_1, 0xC0FF, 0x0900);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_2, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_2, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_3, 0xFFC0, 0x0006);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_3, 0xC0FF, 0x0500);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_4, 0xFFC0, 0x0006);
		b43_phy_maskset(dev, B43_WPPHY_TW_WOOKUP_4, 0xC0FF, 0x0700);
	}
	if (dev->phy.wev == 1 && (spwom->boawdfwags_hi & B43_BFH_PAWEF)) {
		b43_phy_copy(dev, B43_WPPHY_TW_WOOKUP_5, B43_WPPHY_TW_WOOKUP_1);
		b43_phy_copy(dev, B43_WPPHY_TW_WOOKUP_6, B43_WPPHY_TW_WOOKUP_2);
		b43_phy_copy(dev, B43_WPPHY_TW_WOOKUP_7, B43_WPPHY_TW_WOOKUP_3);
		b43_phy_copy(dev, B43_WPPHY_TW_WOOKUP_8, B43_WPPHY_TW_WOOKUP_4);
	}
	if ((spwom->boawdfwags_hi & B43_BFH_FEM_BT) &&
	    (dev->dev->chip_id == 0x5354) &&
	    (dev->dev->chip_pkg == SSB_CHIPPACK_BCM4712S)) {
		b43_phy_set(dev, B43_WPPHY_CWSGAIN_CTW, 0x0006);
		b43_phy_wwite(dev, B43_WPPHY_GPIO_SEWECT, 0x0005);
		b43_phy_wwite(dev, B43_WPPHY_GPIO_OUTEN, 0xFFFF);
		//FIXME the Bwoadcom dwivew caches & deways this HF wwite!
		b43_hf_wwite(dev, b43_hf_wead(dev) | B43_HF_PW45960W);
	}
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
		b43_phy_set(dev, B43_WPPHY_WP_PHY_CTW, 0x8000);
		b43_phy_set(dev, B43_WPPHY_CWSGAIN_CTW, 0x0040);
		b43_phy_maskset(dev, B43_WPPHY_MINPWW_WEVEW, 0x00FF, 0xA400);
		b43_phy_maskset(dev, B43_WPPHY_CWSGAIN_CTW, 0xF0FF, 0x0B00);
		b43_phy_maskset(dev, B43_WPPHY_SYNCPEAKCNT, 0xFFF8, 0x0007);
		b43_phy_maskset(dev, B43_WPPHY_DSSS_CONFIWM_CNT, 0xFFF8, 0x0003);
		b43_phy_maskset(dev, B43_WPPHY_DSSS_CONFIWM_CNT, 0xFFC7, 0x0020);
		b43_phy_mask(dev, B43_WPPHY_IDWEAFTEWPKTWXTO, 0x00FF);
	} ewse { /* 5GHz */
		b43_phy_mask(dev, B43_WPPHY_WP_PHY_CTW, 0x7FFF);
		b43_phy_mask(dev, B43_WPPHY_CWSGAIN_CTW, 0xFFBF);
	}
	if (dev->phy.wev == 1) {
		tmp = b43_phy_wead(dev, B43_WPPHY_CWIPCTWTHWESH);
		tmp2 = (tmp & 0x03E0) >> 5;
		tmp2 |= tmp2 << 5;
		b43_phy_wwite(dev, B43_WPPHY_4C3, tmp2);
		tmp = b43_phy_wead(dev, B43_WPPHY_GAINDIWECTMISMATCH);
		tmp2 = (tmp & 0x1F00) >> 8;
		tmp2 |= tmp2 << 5;
		b43_phy_wwite(dev, B43_WPPHY_4C4, tmp2);
		tmp = b43_phy_wead(dev, B43_WPPHY_VEWYWOWGAINDB);
		tmp2 = tmp & 0x00FF;
		tmp2 |= tmp << 8;
		b43_phy_wwite(dev, B43_WPPHY_4C5, tmp2);
	}
}

static void wpphy_save_dig_fwt_state(stwuct b43_wwdev *dev)
{
	static const u16 addw[] = {
		B43_PHY_OFDM(0xC1),
		B43_PHY_OFDM(0xC2),
		B43_PHY_OFDM(0xC3),
		B43_PHY_OFDM(0xC4),
		B43_PHY_OFDM(0xC5),
		B43_PHY_OFDM(0xC6),
		B43_PHY_OFDM(0xC7),
		B43_PHY_OFDM(0xC8),
		B43_PHY_OFDM(0xCF),
	};

	static const u16 coefs[] = {
		0xDE5E, 0xE832, 0xE331, 0x4D26,
		0x0026, 0x1420, 0x0020, 0xFE08,
		0x0008,
	};

	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	int i;

	fow (i = 0; i < AWWAY_SIZE(addw); i++) {
		wpphy->dig_fwt_state[i] = b43_phy_wead(dev, addw[i]);
		b43_phy_wwite(dev, addw[i], coefs[i]);
	}
}

static void wpphy_westowe_dig_fwt_state(stwuct b43_wwdev *dev)
{
	static const u16 addw[] = {
		B43_PHY_OFDM(0xC1),
		B43_PHY_OFDM(0xC2),
		B43_PHY_OFDM(0xC3),
		B43_PHY_OFDM(0xC4),
		B43_PHY_OFDM(0xC5),
		B43_PHY_OFDM(0xC6),
		B43_PHY_OFDM(0xC7),
		B43_PHY_OFDM(0xC8),
		B43_PHY_OFDM(0xCF),
	};

	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	int i;

	fow (i = 0; i < AWWAY_SIZE(addw); i++)
		b43_phy_wwite(dev, addw[i], wpphy->dig_fwt_state[i]);
}

static void wpphy_baseband_wev2pwus_init(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;

	b43_phy_wwite(dev, B43_WPPHY_AFE_DAC_CTW, 0x50);
	b43_phy_wwite(dev, B43_WPPHY_AFE_CTW, 0x8800);
	b43_phy_wwite(dev, B43_WPPHY_AFE_CTW_OVW, 0);
	b43_phy_wwite(dev, B43_WPPHY_AFE_CTW_OVWVAW, 0);
	b43_phy_wwite(dev, B43_WPPHY_WF_OVEWWIDE_0, 0);
	b43_phy_wwite(dev, B43_WPPHY_WF_OVEWWIDE_2, 0);
	b43_phy_wwite(dev, B43_PHY_OFDM(0xF9), 0);
	b43_phy_wwite(dev, B43_WPPHY_TW_WOOKUP_1, 0);
	b43_phy_set(dev, B43_WPPHY_ADC_COMPENSATION_CTW, 0x10);
	b43_phy_maskset(dev, B43_WPPHY_OFDMSYNCTHWESH0, 0xFF00, 0xB4);
	b43_phy_maskset(dev, B43_WPPHY_DCOFFSETTWANSIENT, 0xF8FF, 0x200);
	b43_phy_maskset(dev, B43_WPPHY_DCOFFSETTWANSIENT, 0xFF00, 0x7F);
	b43_phy_maskset(dev, B43_WPPHY_GAINDIWECTMISMATCH, 0xFF0F, 0x40);
	b43_phy_maskset(dev, B43_WPPHY_PWEAMBWECONFIWMTO, 0xFF00, 0x2);
	b43_phy_mask(dev, B43_WPPHY_CWSGAIN_CTW, ~0x4000);
	b43_phy_mask(dev, B43_WPPHY_CWSGAIN_CTW, ~0x2000);
	b43_phy_set(dev, B43_PHY_OFDM(0x10A), 0x1);
	if (dev->dev->boawd_wev >= 0x18) {
		b43_wptab_wwite(dev, B43_WPTAB32(17, 65), 0xEC);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x10A), 0xFF01, 0x14);
	} ewse {
		b43_phy_maskset(dev, B43_PHY_OFDM(0x10A), 0xFF01, 0x10);
	}
	b43_phy_maskset(dev, B43_PHY_OFDM(0xDF), 0xFF00, 0xF4);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xDF), 0x00FF, 0xF100);
	b43_phy_wwite(dev, B43_WPPHY_CWIPTHWESH, 0x48);
	b43_phy_maskset(dev, B43_WPPHY_HIGAINDB, 0xFF00, 0x46);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xE4), 0xFF00, 0x10);
	b43_phy_maskset(dev, B43_WPPHY_PWW_THWESH1, 0xFFF0, 0x9);
	b43_phy_mask(dev, B43_WPPHY_GAINDIWECTMISMATCH, ~0xF);
	b43_phy_maskset(dev, B43_WPPHY_VEWYWOWGAINDB, 0x00FF, 0x5500);
	b43_phy_maskset(dev, B43_WPPHY_CWIPCTWTHWESH, 0xFC1F, 0xA0);
	b43_phy_maskset(dev, B43_WPPHY_GAINDIWECTMISMATCH, 0xE0FF, 0x300);
	b43_phy_maskset(dev, B43_WPPHY_HIGAINDB, 0x00FF, 0x2A00);
	if ((dev->dev->chip_id == 0x4325) && (dev->dev->chip_wev == 0)) {
		b43_phy_maskset(dev, B43_WPPHY_WOWGAINDB, 0x00FF, 0x2100);
		b43_phy_maskset(dev, B43_WPPHY_VEWYWOWGAINDB, 0xFF00, 0xA);
	} ewse {
		b43_phy_maskset(dev, B43_WPPHY_WOWGAINDB, 0x00FF, 0x1E00);
		b43_phy_maskset(dev, B43_WPPHY_VEWYWOWGAINDB, 0xFF00, 0xD);
	}
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFE), 0xFFE0, 0x1F);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFF), 0xFFE0, 0xC);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x100), 0xFF00, 0x19);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFF), 0x03FF, 0x3C00);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFE), 0xFC1F, 0x3E0);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFF), 0xFFE0, 0xC);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x100), 0x00FF, 0x1900);
	b43_phy_maskset(dev, B43_WPPHY_CWIPCTWTHWESH, 0x83FF, 0x5800);
	b43_phy_maskset(dev, B43_WPPHY_CWIPCTWTHWESH, 0xFFE0, 0x12);
	b43_phy_maskset(dev, B43_WPPHY_GAINMISMATCH, 0x0FFF, 0x9000);

	if ((dev->dev->chip_id == 0x4325) && (dev->dev->chip_wev == 0)) {
		b43_wptab_wwite(dev, B43_WPTAB16(0x08, 0x14), 0);
		b43_wptab_wwite(dev, B43_WPTAB16(0x08, 0x12), 0x40);
	}

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
		b43_phy_set(dev, B43_WPPHY_CWSGAIN_CTW, 0x40);
		b43_phy_maskset(dev, B43_WPPHY_CWSGAIN_CTW, 0xF0FF, 0xB00);
		b43_phy_maskset(dev, B43_WPPHY_SYNCPEAKCNT, 0xFFF8, 0x6);
		b43_phy_maskset(dev, B43_WPPHY_MINPWW_WEVEW, 0x00FF, 0x9D00);
		b43_phy_maskset(dev, B43_WPPHY_MINPWW_WEVEW, 0xFF00, 0xA1);
		b43_phy_mask(dev, B43_WPPHY_IDWEAFTEWPKTWXTO, 0x00FF);
	} ewse /* 5GHz */
		b43_phy_mask(dev, B43_WPPHY_CWSGAIN_CTW, ~0x40);

	b43_phy_maskset(dev, B43_WPPHY_CWS_ED_THWESH, 0xFF00, 0xB3);
	b43_phy_maskset(dev, B43_WPPHY_CWS_ED_THWESH, 0x00FF, 0xAD00);
	b43_phy_maskset(dev, B43_WPPHY_INPUT_PWWDB, 0xFF00, wpphy->wx_pww_offset);
	b43_phy_set(dev, B43_WPPHY_WESET_CTW, 0x44);
	b43_phy_wwite(dev, B43_WPPHY_WESET_CTW, 0x80);
	b43_phy_wwite(dev, B43_WPPHY_AFE_WSSI_CTW_0, 0xA954);
	b43_phy_wwite(dev, B43_WPPHY_AFE_WSSI_CTW_1,
		      0x2000 | ((u16)wpphy->wssi_gs << 10) |
		      ((u16)wpphy->wssi_vc << 4) | wpphy->wssi_vf);

	if ((dev->dev->chip_id == 0x4325) && (dev->dev->chip_wev == 0)) {
		b43_phy_set(dev, B43_WPPHY_AFE_ADC_CTW_0, 0x1C);
		b43_phy_maskset(dev, B43_WPPHY_AFE_CTW, 0x00FF, 0x8800);
		b43_phy_maskset(dev, B43_WPPHY_AFE_ADC_CTW_1, 0xFC3C, 0x0400);
	}

	wpphy_save_dig_fwt_state(dev);
}

static void wpphy_baseband_init(stwuct b43_wwdev *dev)
{
	wpphy_tabwe_init(dev);
	if (dev->phy.wev >= 2)
		wpphy_baseband_wev2pwus_init(dev);
	ewse
		wpphy_baseband_wev0_1_init(dev);
}

stwuct b2062_fweqdata {
	u16 fweq;
	u8 data[6];
};

/* Initiawize the 2062 wadio. */
static void wpphy_2062_init(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	stwuct ssb_bus *bus = dev->dev->sdev->bus;
	u32 cwystawfweq, tmp, wef;
	unsigned int i;
	const stwuct b2062_fweqdata *fd = NUWW;

	static const stwuct b2062_fweqdata fweqdata_tab[] = {
		{ .fweq = 12000, .data[0] =  6, .data[1] =  6, .data[2] =  6,
				 .data[3] =  6, .data[4] = 10, .data[5] =  6, },
		{ .fweq = 13000, .data[0] =  4, .data[1] =  4, .data[2] =  4,
				 .data[3] =  4, .data[4] = 11, .data[5] =  7, },
		{ .fweq = 14400, .data[0] =  3, .data[1] =  3, .data[2] =  3,
				 .data[3] =  3, .data[4] = 12, .data[5] =  7, },
		{ .fweq = 16200, .data[0] =  3, .data[1] =  3, .data[2] =  3,
				 .data[3] =  3, .data[4] = 13, .data[5] =  8, },
		{ .fweq = 18000, .data[0] =  2, .data[1] =  2, .data[2] =  2,
				 .data[3] =  2, .data[4] = 14, .data[5] =  8, },
		{ .fweq = 19200, .data[0] =  1, .data[1] =  1, .data[2] =  1,
				 .data[3] =  1, .data[4] = 14, .data[5] =  9, },
	};

	b2062_upwoad_init_tabwe(dev);

	b43_wadio_wwite(dev, B2062_N_TX_CTW3, 0);
	b43_wadio_wwite(dev, B2062_N_TX_CTW4, 0);
	b43_wadio_wwite(dev, B2062_N_TX_CTW5, 0);
	b43_wadio_wwite(dev, B2062_N_TX_CTW6, 0);
	b43_wadio_wwite(dev, B2062_N_PDN_CTW0, 0x40);
	b43_wadio_wwite(dev, B2062_N_PDN_CTW0, 0);
	b43_wadio_wwite(dev, B2062_N_CAWIB_TS, 0x10);
	b43_wadio_wwite(dev, B2062_N_CAWIB_TS, 0);
	if (dev->phy.wev > 0) {
		b43_wadio_wwite(dev, B2062_S_BG_CTW1,
			(b43_wadio_wead(dev, B2062_N_COMM2) >> 1) | 0x80);
	}
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
		b43_wadio_set(dev, B2062_N_TSSI_CTW0, 0x1);
	ewse
		b43_wadio_mask(dev, B2062_N_TSSI_CTW0, ~0x1);

	/* Get the cwystaw fweq, in Hz. */
	cwystawfweq = bus->chipco.pmu.cwystawfweq * 1000;

	B43_WAWN_ON(!(bus->chipco.capabiwities & SSB_CHIPCO_CAP_PMU));
	B43_WAWN_ON(cwystawfweq == 0);

	if (cwystawfweq <= 30000000) {
		wpphy->pdiv = 1;
		b43_wadio_mask(dev, B2062_S_WFPWW_CTW1, 0xFFFB);
	} ewse {
		wpphy->pdiv = 2;
		b43_wadio_set(dev, B2062_S_WFPWW_CTW1, 0x4);
	}

	tmp = (((800000000 * wpphy->pdiv + cwystawfweq) /
	      (2 * cwystawfweq)) - 8) & 0xFF;
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW7, tmp);

	tmp = (((100 * cwystawfweq + 16000000 * wpphy->pdiv) /
	      (32000000 * wpphy->pdiv)) - 1) & 0xFF;
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW18, tmp);

	tmp = (((2 * cwystawfweq + 1000000 * wpphy->pdiv) /
	      (2000000 * wpphy->pdiv)) - 1) & 0xFF;
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW19, tmp);

	wef = (1000 * wpphy->pdiv + 2 * cwystawfweq) / (2000 * wpphy->pdiv);
	wef &= 0xFFFF;
	fow (i = 0; i < AWWAY_SIZE(fweqdata_tab); i++) {
		if (wef < fweqdata_tab[i].fweq) {
			fd = &fweqdata_tab[i];
			bweak;
		}
	}
	if (!fd)
		fd = &fweqdata_tab[AWWAY_SIZE(fweqdata_tab) - 1];
	b43dbg(dev->ww, "b2062: Using cwystaw tab entwy %u kHz.\n",
	       fd->fweq); /* FIXME: Keep this pwintk untiw the code is fuwwy debugged. */

	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW8,
			((u16)(fd->data[1]) << 4) | fd->data[0]);
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW9,
			((u16)(fd->data[3]) << 4) | fd->data[2]);
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW10, fd->data[4]);
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW11, fd->data[5]);
}

/* Initiawize the 2063 wadio. */
static void wpphy_2063_init(stwuct b43_wwdev *dev)
{
	b2063_upwoad_init_tabwe(dev);
	b43_wadio_wwite(dev, B2063_WOGEN_SP5, 0);
	b43_wadio_set(dev, B2063_COMM8, 0x38);
	b43_wadio_wwite(dev, B2063_WEG_SP1, 0x56);
	b43_wadio_mask(dev, B2063_WX_BB_CTW2, ~0x2);
	b43_wadio_wwite(dev, B2063_PA_SP7, 0);
	b43_wadio_wwite(dev, B2063_TX_WF_SP6, 0x20);
	b43_wadio_wwite(dev, B2063_TX_WF_SP9, 0x40);
	if (dev->phy.wev == 2) {
		b43_wadio_wwite(dev, B2063_PA_SP3, 0xa0);
		b43_wadio_wwite(dev, B2063_PA_SP4, 0xa0);
		b43_wadio_wwite(dev, B2063_PA_SP2, 0x18);
	} ewse {
		b43_wadio_wwite(dev, B2063_PA_SP3, 0x20);
		b43_wadio_wwite(dev, B2063_PA_SP2, 0x20);
	}
}

stwuct wpphy_stx_tabwe_entwy {
	u16 phy_offset;
	u16 phy_shift;
	u16 wf_addw;
	u16 wf_shift;
	u16 mask;
};

static const stwuct wpphy_stx_tabwe_entwy wpphy_stx_tabwe[] = {
	{ .phy_offset = 2, .phy_shift = 6, .wf_addw = 0x3d, .wf_shift = 3, .mask = 0x01, },
	{ .phy_offset = 1, .phy_shift = 12, .wf_addw = 0x4c, .wf_shift = 1, .mask = 0x01, },
	{ .phy_offset = 1, .phy_shift = 8, .wf_addw = 0x50, .wf_shift = 0, .mask = 0x7f, },
	{ .phy_offset = 0, .phy_shift = 8, .wf_addw = 0x44, .wf_shift = 0, .mask = 0xff, },
	{ .phy_offset = 1, .phy_shift = 0, .wf_addw = 0x4a, .wf_shift = 0, .mask = 0xff, },
	{ .phy_offset = 0, .phy_shift = 4, .wf_addw = 0x4d, .wf_shift = 0, .mask = 0xff, },
	{ .phy_offset = 1, .phy_shift = 4, .wf_addw = 0x4e, .wf_shift = 0, .mask = 0xff, },
	{ .phy_offset = 0, .phy_shift = 12, .wf_addw = 0x4f, .wf_shift = 0, .mask = 0x0f, },
	{ .phy_offset = 1, .phy_shift = 0, .wf_addw = 0x4f, .wf_shift = 4, .mask = 0x0f, },
	{ .phy_offset = 3, .phy_shift = 0, .wf_addw = 0x49, .wf_shift = 0, .mask = 0x0f, },
	{ .phy_offset = 4, .phy_shift = 3, .wf_addw = 0x46, .wf_shift = 4, .mask = 0x07, },
	{ .phy_offset = 3, .phy_shift = 15, .wf_addw = 0x46, .wf_shift = 0, .mask = 0x01, },
	{ .phy_offset = 4, .phy_shift = 0, .wf_addw = 0x46, .wf_shift = 1, .mask = 0x07, },
	{ .phy_offset = 3, .phy_shift = 8, .wf_addw = 0x48, .wf_shift = 4, .mask = 0x07, },
	{ .phy_offset = 3, .phy_shift = 11, .wf_addw = 0x48, .wf_shift = 0, .mask = 0x0f, },
	{ .phy_offset = 3, .phy_shift = 4, .wf_addw = 0x49, .wf_shift = 4, .mask = 0x0f, },
	{ .phy_offset = 2, .phy_shift = 15, .wf_addw = 0x45, .wf_shift = 0, .mask = 0x01, },
	{ .phy_offset = 5, .phy_shift = 13, .wf_addw = 0x52, .wf_shift = 4, .mask = 0x07, },
	{ .phy_offset = 6, .phy_shift = 0, .wf_addw = 0x52, .wf_shift = 7, .mask = 0x01, },
	{ .phy_offset = 5, .phy_shift = 3, .wf_addw = 0x41, .wf_shift = 5, .mask = 0x07, },
	{ .phy_offset = 5, .phy_shift = 6, .wf_addw = 0x41, .wf_shift = 0, .mask = 0x0f, },
	{ .phy_offset = 5, .phy_shift = 10, .wf_addw = 0x42, .wf_shift = 5, .mask = 0x07, },
	{ .phy_offset = 4, .phy_shift = 15, .wf_addw = 0x42, .wf_shift = 0, .mask = 0x01, },
	{ .phy_offset = 5, .phy_shift = 0, .wf_addw = 0x42, .wf_shift = 1, .mask = 0x07, },
	{ .phy_offset = 4, .phy_shift = 11, .wf_addw = 0x43, .wf_shift = 4, .mask = 0x0f, },
	{ .phy_offset = 4, .phy_shift = 7, .wf_addw = 0x43, .wf_shift = 0, .mask = 0x0f, },
	{ .phy_offset = 4, .phy_shift = 6, .wf_addw = 0x45, .wf_shift = 1, .mask = 0x01, },
	{ .phy_offset = 2, .phy_shift = 7, .wf_addw = 0x40, .wf_shift = 4, .mask = 0x0f, },
	{ .phy_offset = 2, .phy_shift = 11, .wf_addw = 0x40, .wf_shift = 0, .mask = 0x0f, },
};

static void wpphy_sync_stx(stwuct b43_wwdev *dev)
{
	const stwuct wpphy_stx_tabwe_entwy *e;
	unsigned int i;
	u16 tmp;

	fow (i = 0; i < AWWAY_SIZE(wpphy_stx_tabwe); i++) {
		e = &wpphy_stx_tabwe[i];
		tmp = b43_wadio_wead(dev, e->wf_addw);
		tmp >>= e->wf_shift;
		tmp <<= e->phy_shift;
		b43_phy_maskset(dev, B43_PHY_OFDM(0xF2 + e->phy_offset),
				~(e->mask << e->phy_shift), tmp);
	}
}

static void wpphy_wadio_init(stwuct b43_wwdev *dev)
{
	/* The wadio is attached thwough the 4wiwe bus. */
	b43_phy_set(dev, B43_WPPHY_FOUWWIWE_CTW, 0x2);
	udeway(1);
	b43_phy_mask(dev, B43_WPPHY_FOUWWIWE_CTW, 0xFFFD);
	udeway(1);

	if (dev->phy.wadio_vew == 0x2062) {
		wpphy_2062_init(dev);
	} ewse {
		wpphy_2063_init(dev);
		wpphy_sync_stx(dev);
		b43_phy_wwite(dev, B43_PHY_OFDM(0xF0), 0x5F80);
		b43_phy_wwite(dev, B43_PHY_OFDM(0xF1), 0);
		if (dev->dev->chip_id == 0x4325) {
			// TODO SSB PMU wecawibwation
		}
	}
}

stwuct wpphy_iq_est { u32 iq_pwod, i_pww, q_pww; };

static void wpphy_set_wc_cap(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;

	u8 wc_cap = (wpphy->wc_cap & 0x1F) >> 1;

	if (dev->phy.wev == 1) //FIXME check channew 14!
		wc_cap = min_t(u8, wc_cap + 5, 15);

	b43_wadio_wwite(dev, B2062_N_WXBB_CAWIB2,
			max_t(u8, wpphy->wc_cap - 4, 0x80));
	b43_wadio_wwite(dev, B2062_N_TX_CTW_A, wc_cap | 0x80);
	b43_wadio_wwite(dev, B2062_S_WXG_CNT16,
			((wpphy->wc_cap & 0x1F) >> 2) | 0x80);
}

static u8 wpphy_get_bb_muwt(stwuct b43_wwdev *dev)
{
	wetuwn (b43_wptab_wead(dev, B43_WPTAB16(0, 87)) & 0xFF00) >> 8;
}

static void wpphy_set_bb_muwt(stwuct b43_wwdev *dev, u8 bb_muwt)
{
	b43_wptab_wwite(dev, B43_WPTAB16(0, 87), (u16)bb_muwt << 8);
}

static void wpphy_set_deaf(stwuct b43_wwdev *dev, boow usew)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;

	if (usew)
		wpphy->cws_usw_disabwe = twue;
	ewse
		wpphy->cws_sys_disabwe = twue;
	b43_phy_maskset(dev, B43_WPPHY_CWSGAIN_CTW, 0xFF1F, 0x80);
}

static void wpphy_cweaw_deaf(stwuct b43_wwdev *dev, boow usew)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;

	if (usew)
		wpphy->cws_usw_disabwe = fawse;
	ewse
		wpphy->cws_sys_disabwe = fawse;

	if (!wpphy->cws_usw_disabwe && !wpphy->cws_sys_disabwe) {
		if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
			b43_phy_maskset(dev, B43_WPPHY_CWSGAIN_CTW,
					0xFF1F, 0x60);
		ewse
			b43_phy_maskset(dev, B43_WPPHY_CWSGAIN_CTW,
					0xFF1F, 0x20);
	}
}

static void wpphy_set_twsw_ovew(stwuct b43_wwdev *dev, boow tx, boow wx)
{
	u16 twsw = (tx << 1) | wx;
	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0xFFFC, twsw);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x3);
}

static void wpphy_disabwe_cws(stwuct b43_wwdev *dev, boow usew)
{
	wpphy_set_deaf(dev, usew);
	wpphy_set_twsw_ovew(dev, fawse, twue);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0xFFFB);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x4);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0xFFF7);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x8);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0x10);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x10);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0xFFDF);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x20);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0xFFBF);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x40);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0x7);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0x38);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0xFF3F);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0x100);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0xFDFF);
	b43_phy_wwite(dev, B43_WPPHY_PS_CTW_OVEWWIDE_VAW0, 0);
	b43_phy_wwite(dev, B43_WPPHY_PS_CTW_OVEWWIDE_VAW1, 1);
	b43_phy_wwite(dev, B43_WPPHY_PS_CTW_OVEWWIDE_VAW2, 0x20);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0xFBFF);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0xF7FF);
	b43_phy_wwite(dev, B43_WPPHY_TX_GAIN_CTW_OVEWWIDE_VAW, 0);
	b43_phy_wwite(dev, B43_WPPHY_WX_GAIN_CTW_OVEWWIDE_VAW, 0x45AF);
	b43_phy_wwite(dev, B43_WPPHY_WF_OVEWWIDE_2, 0x3FF);
}

static void wpphy_westowe_cws(stwuct b43_wwdev *dev, boow usew)
{
	wpphy_cweaw_deaf(dev, usew);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xFF80);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2, 0xFC00);
}

stwuct wpphy_tx_gains { u16 gm, pga, pad, dac; };

static void wpphy_disabwe_wx_gain_ovewwide(stwuct b43_wwdev *dev)
{
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xFFFE);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xFFEF);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xFFBF);
	if (dev->phy.wev >= 2) {
		b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2, 0xFEFF);
		if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
			b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2, 0xFBFF);
			b43_phy_mask(dev, B43_PHY_OFDM(0xE5), 0xFFF7);
		}
	} ewse {
		b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2, 0xFDFF);
	}
}

static void wpphy_enabwe_wx_gain_ovewwide(stwuct b43_wwdev *dev)
{
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x1);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x10);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x40);
	if (dev->phy.wev >= 2) {
		b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2, 0x100);
		if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
			b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2, 0x400);
			b43_phy_set(dev, B43_PHY_OFDM(0xE5), 0x8);
		}
	} ewse {
		b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2, 0x200);
	}
}

static void wpphy_disabwe_tx_gain_ovewwide(stwuct b43_wwdev *dev)
{
	if (dev->phy.wev < 2)
		b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2, 0xFEFF);
	ewse {
		b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2, 0xFF7F);
		b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2, 0xBFFF);
	}
	b43_phy_mask(dev, B43_WPPHY_AFE_CTW_OVW, 0xFFBF);
}

static void wpphy_enabwe_tx_gain_ovewwide(stwuct b43_wwdev *dev)
{
	if (dev->phy.wev < 2)
		b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2, 0x100);
	ewse {
		b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2, 0x80);
		b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2, 0x4000);
	}
	b43_phy_set(dev, B43_WPPHY_AFE_CTW_OVW, 0x40);
}

static stwuct wpphy_tx_gains wpphy_get_tx_gains(stwuct b43_wwdev *dev)
{
	stwuct wpphy_tx_gains gains;
	u16 tmp;

	gains.dac = (b43_phy_wead(dev, B43_WPPHY_AFE_DAC_CTW) & 0x380) >> 7;
	if (dev->phy.wev < 2) {
		tmp = b43_phy_wead(dev,
				   B43_WPPHY_TX_GAIN_CTW_OVEWWIDE_VAW) & 0x7FF;
		gains.gm = tmp & 0x0007;
		gains.pga = (tmp & 0x0078) >> 3;
		gains.pad = (tmp & 0x780) >> 7;
	} ewse {
		tmp = b43_phy_wead(dev, B43_WPPHY_TX_GAIN_CTW_OVEWWIDE_VAW);
		gains.pad = b43_phy_wead(dev, B43_PHY_OFDM(0xFB)) & 0xFF;
		gains.gm = tmp & 0xFF;
		gains.pga = (tmp >> 8) & 0xFF;
	}

	wetuwn gains;
}

static void wpphy_set_dac_gain(stwuct b43_wwdev *dev, u16 dac)
{
	u16 ctw = b43_phy_wead(dev, B43_WPPHY_AFE_DAC_CTW) & 0xC7F;
	ctw |= dac << 7;
	b43_phy_maskset(dev, B43_WPPHY_AFE_DAC_CTW, 0xF000, ctw);
}

static u16 wpphy_get_pa_gain(stwuct b43_wwdev *dev)
{
	wetuwn b43_phy_wead(dev, B43_PHY_OFDM(0xFB)) & 0x7F;
}

static void wpphy_set_pa_gain(stwuct b43_wwdev *dev, u16 gain)
{
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFB), 0xE03F, gain << 6);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xFD), 0x80FF, gain << 8);
}

static void wpphy_set_tx_gains(stwuct b43_wwdev *dev,
			       stwuct wpphy_tx_gains gains)
{
	u16 wf_gain, pa_gain;

	if (dev->phy.wev < 2) {
		wf_gain = (gains.pad << 7) | (gains.pga << 3) | gains.gm;
		b43_phy_maskset(dev, B43_WPPHY_TX_GAIN_CTW_OVEWWIDE_VAW,
				0xF800, wf_gain);
	} ewse {
		pa_gain = wpphy_get_pa_gain(dev);
		b43_phy_wwite(dev, B43_WPPHY_TX_GAIN_CTW_OVEWWIDE_VAW,
			      (gains.pga << 8) | gains.gm);
		/*
		 * SPEC FIXME The spec cawws fow (pa_gain << 8) hewe, but that
		 * confwicts with the spec fow set_pa_gain! Vendow dwivew bug?
		 */
		b43_phy_maskset(dev, B43_PHY_OFDM(0xFB),
				0x8000, gains.pad | (pa_gain << 6));
		b43_phy_wwite(dev, B43_PHY_OFDM(0xFC),
			      (gains.pga << 8) | gains.gm);
		b43_phy_maskset(dev, B43_PHY_OFDM(0xFD),
				0x8000, gains.pad | (pa_gain << 8));
	}
	wpphy_set_dac_gain(dev, gains.dac);
	wpphy_enabwe_tx_gain_ovewwide(dev);
}

static void wpphy_wev0_1_set_wx_gain(stwuct b43_wwdev *dev, u32 gain)
{
	u16 twsw = gain & 0x1;
	u16 wna = (gain & 0xFFFC) | ((gain & 0xC) >> 2);
	u16 ext_wna = (gain & 2) >> 1;

	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0xFFFE, twsw);
	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW,
			0xFBFF, ext_wna << 10);
	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW,
			0xF7FF, ext_wna << 11);
	b43_phy_wwite(dev, B43_WPPHY_WX_GAIN_CTW_OVEWWIDE_VAW, wna);
}

static void wpphy_wev2pwus_set_wx_gain(stwuct b43_wwdev *dev, u32 gain)
{
	u16 wow_gain = gain & 0xFFFF;
	u16 high_gain = (gain >> 16) & 0xF;
	u16 ext_wna = (gain >> 21) & 0x1;
	u16 twsw = ~(gain >> 20) & 0x1;
	u16 tmp;

	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0xFFFE, twsw);
	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW,
			0xFDFF, ext_wna << 9);
	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW,
			0xFBFF, ext_wna << 10);
	b43_phy_wwite(dev, B43_WPPHY_WX_GAIN_CTW_OVEWWIDE_VAW, wow_gain);
	b43_phy_maskset(dev, B43_WPPHY_AFE_DDFS, 0xFFF0, high_gain);
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
		tmp = (gain >> 2) & 0x3;
		b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW,
				0xE7FF, tmp<<11);
		b43_phy_maskset(dev, B43_PHY_OFDM(0xE6), 0xFFE7, tmp << 3);
	}
}

static void wpphy_set_wx_gain(stwuct b43_wwdev *dev, u32 gain)
{
	if (dev->phy.wev < 2)
		wpphy_wev0_1_set_wx_gain(dev, gain);
	ewse
		wpphy_wev2pwus_set_wx_gain(dev, gain);
	wpphy_enabwe_wx_gain_ovewwide(dev);
}

static void wpphy_set_wx_gain_by_index(stwuct b43_wwdev *dev, u16 idx)
{
	u32 gain = b43_wptab_wead(dev, B43_WPTAB16(12, idx));
	wpphy_set_wx_gain(dev, gain);
}

static void wpphy_stop_ddfs(stwuct b43_wwdev *dev)
{
	b43_phy_mask(dev, B43_WPPHY_AFE_DDFS, 0xFFFD);
	b43_phy_mask(dev, B43_WPPHY_WP_PHY_CTW, 0xFFDF);
}

static void wpphy_wun_ddfs(stwuct b43_wwdev *dev, int i_on, int q_on,
			   int incw1, int incw2, int scawe_idx)
{
	wpphy_stop_ddfs(dev);
	b43_phy_mask(dev, B43_WPPHY_AFE_DDFS_POINTEW_INIT, 0xFF80);
	b43_phy_mask(dev, B43_WPPHY_AFE_DDFS_POINTEW_INIT, 0x80FF);
	b43_phy_maskset(dev, B43_WPPHY_AFE_DDFS_INCW_INIT, 0xFF80, incw1);
	b43_phy_maskset(dev, B43_WPPHY_AFE_DDFS_INCW_INIT, 0x80FF, incw2 << 8);
	b43_phy_maskset(dev, B43_WPPHY_AFE_DDFS, 0xFFF7, i_on << 3);
	b43_phy_maskset(dev, B43_WPPHY_AFE_DDFS, 0xFFEF, q_on << 4);
	b43_phy_maskset(dev, B43_WPPHY_AFE_DDFS, 0xFF9F, scawe_idx << 5);
	b43_phy_mask(dev, B43_WPPHY_AFE_DDFS, 0xFFFB);
	b43_phy_set(dev, B43_WPPHY_AFE_DDFS, 0x2);
	b43_phy_set(dev, B43_WPPHY_WP_PHY_CTW, 0x20);
}

static boow wpphy_wx_iq_est(stwuct b43_wwdev *dev, u16 sampwes, u8 time,
			   stwuct wpphy_iq_est *iq_est)
{
	int i;

	b43_phy_mask(dev, B43_WPPHY_CWSGAIN_CTW, 0xFFF7);
	b43_phy_wwite(dev, B43_WPPHY_IQ_NUM_SMPWS_ADDW, sampwes);
	b43_phy_maskset(dev, B43_WPPHY_IQ_ENABWE_WAIT_TIME_ADDW, 0xFF00, time);
	b43_phy_mask(dev, B43_WPPHY_IQ_ENABWE_WAIT_TIME_ADDW, 0xFEFF);
	b43_phy_set(dev, B43_WPPHY_IQ_ENABWE_WAIT_TIME_ADDW, 0x200);

	fow (i = 0; i < 500; i++) {
		if (!(b43_phy_wead(dev,
				B43_WPPHY_IQ_ENABWE_WAIT_TIME_ADDW) & 0x200))
			bweak;
		msweep(1);
	}

	if ((b43_phy_wead(dev, B43_WPPHY_IQ_ENABWE_WAIT_TIME_ADDW) & 0x200)) {
		b43_phy_set(dev, B43_WPPHY_CWSGAIN_CTW, 0x8);
		wetuwn fawse;
	}

	iq_est->iq_pwod = b43_phy_wead(dev, B43_WPPHY_IQ_ACC_HI_ADDW);
	iq_est->iq_pwod <<= 16;
	iq_est->iq_pwod |= b43_phy_wead(dev, B43_WPPHY_IQ_ACC_WO_ADDW);

	iq_est->i_pww = b43_phy_wead(dev, B43_WPPHY_IQ_I_PWW_ACC_HI_ADDW);
	iq_est->i_pww <<= 16;
	iq_est->i_pww |= b43_phy_wead(dev, B43_WPPHY_IQ_I_PWW_ACC_WO_ADDW);

	iq_est->q_pww = b43_phy_wead(dev, B43_WPPHY_IQ_Q_PWW_ACC_HI_ADDW);
	iq_est->q_pww <<= 16;
	iq_est->q_pww |= b43_phy_wead(dev, B43_WPPHY_IQ_Q_PWW_ACC_WO_ADDW);

	b43_phy_set(dev, B43_WPPHY_CWSGAIN_CTW, 0x8);
	wetuwn twue;
}

static int wpphy_woopback(stwuct b43_wwdev *dev)
{
	stwuct wpphy_iq_est iq_est;
	int i, index = -1;
	u32 tmp;

	memset(&iq_est, 0, sizeof(iq_est));

	wpphy_set_twsw_ovew(dev, twue, twue);
	b43_phy_set(dev, B43_WPPHY_AFE_CTW_OVW, 1);
	b43_phy_mask(dev, B43_WPPHY_AFE_CTW_OVWVAW, 0xFFFE);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x800);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0x800);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x8);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0x8);
	b43_wadio_wwite(dev, B2062_N_TX_CTW_A, 0x80);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x80);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0x80);
	fow (i = 0; i < 32; i++) {
		wpphy_set_wx_gain_by_index(dev, i);
		wpphy_wun_ddfs(dev, 1, 1, 5, 5, 0);
		if (!(wpphy_wx_iq_est(dev, 1000, 32, &iq_est)))
			continue;
		tmp = (iq_est.i_pww + iq_est.q_pww) / 1000;
		if ((tmp > 4000) && (tmp < 10000)) {
			index = i;
			bweak;
		}
	}
	wpphy_stop_ddfs(dev);
	wetuwn index;
}

/* Fixed-point division awgowithm using onwy integew math. */
static u32 wpphy_qdiv_woundup(u32 dividend, u32 divisow, u8 pwecision)
{
	u32 quotient, wemaindew;

	if (divisow == 0)
		wetuwn 0;

	quotient = dividend / divisow;
	wemaindew = dividend % divisow;

	whiwe (pwecision > 0) {
		quotient <<= 1;
		if (wemaindew << 1 >= divisow) {
			quotient++;
			wemaindew = (wemaindew << 1) - divisow;
		}
		pwecision--;
	}

	if (wemaindew << 1 >= divisow)
		quotient++;

	wetuwn quotient;
}

/* Wead the TX powew contwow mode fwom hawdwawe. */
static void wpphy_wead_tx_pctw_mode_fwom_hawdwawe(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	u16 ctw;

	ctw = b43_phy_wead(dev, B43_WPPHY_TX_PWW_CTW_CMD);
	switch (ctw & B43_WPPHY_TX_PWW_CTW_CMD_MODE) {
	case B43_WPPHY_TX_PWW_CTW_CMD_MODE_OFF:
		wpphy->txpctw_mode = B43_WPPHY_TXPCTW_OFF;
		bweak;
	case B43_WPPHY_TX_PWW_CTW_CMD_MODE_SW:
		wpphy->txpctw_mode = B43_WPPHY_TXPCTW_SW;
		bweak;
	case B43_WPPHY_TX_PWW_CTW_CMD_MODE_HW:
		wpphy->txpctw_mode = B43_WPPHY_TXPCTW_HW;
		bweak;
	defauwt:
		wpphy->txpctw_mode = B43_WPPHY_TXPCTW_UNKNOWN;
		B43_WAWN_ON(1);
		bweak;
	}
}

/* Set the TX powew contwow mode in hawdwawe. */
static void wpphy_wwite_tx_pctw_mode_to_hawdwawe(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	u16 ctw;

	switch (wpphy->txpctw_mode) {
	case B43_WPPHY_TXPCTW_OFF:
		ctw = B43_WPPHY_TX_PWW_CTW_CMD_MODE_OFF;
		bweak;
	case B43_WPPHY_TXPCTW_HW:
		ctw = B43_WPPHY_TX_PWW_CTW_CMD_MODE_HW;
		bweak;
	case B43_WPPHY_TXPCTW_SW:
		ctw = B43_WPPHY_TX_PWW_CTW_CMD_MODE_SW;
		bweak;
	defauwt:
		ctw = 0;
		B43_WAWN_ON(1);
	}
	b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_CMD,
			~B43_WPPHY_TX_PWW_CTW_CMD_MODE & 0xFFFF, ctw);
}

static void wpphy_set_tx_powew_contwow(stwuct b43_wwdev *dev,
				       enum b43_wpphy_txpctw_mode mode)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	enum b43_wpphy_txpctw_mode owdmode;

	wpphy_wead_tx_pctw_mode_fwom_hawdwawe(dev);
	owdmode = wpphy->txpctw_mode;
	if (owdmode == mode)
		wetuwn;
	wpphy->txpctw_mode = mode;

	if (owdmode == B43_WPPHY_TXPCTW_HW) {
		//TODO Update TX Powew NPT
		//TODO Cweaw aww TX Powew offsets
	} ewse {
		if (mode == B43_WPPHY_TXPCTW_HW) {
			//TODO Wecawcuwate tawget TX powew
			b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_CMD,
					0xFF80, wpphy->tssi_idx);
			b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_NNUM,
					0x8FFF, ((u16)wpphy->tssi_npt << 16));
			//TODO Set "TSSI Twansmit Count" vawiabwe to totaw twansmitted fwame count
			wpphy_disabwe_tx_gain_ovewwide(dev);
			wpphy->tx_pww_idx_ovew = -1;
		}
	}
	if (dev->phy.wev >= 2) {
		if (mode == B43_WPPHY_TXPCTW_HW)
			b43_phy_set(dev, B43_PHY_OFDM(0xD0), 0x2);
		ewse
			b43_phy_mask(dev, B43_PHY_OFDM(0xD0), 0xFFFD);
	}
	wpphy_wwite_tx_pctw_mode_to_hawdwawe(dev);
}

static int b43_wpphy_op_switch_channew(stwuct b43_wwdev *dev,
				       unsigned int new_channew);

static void wpphy_wev0_1_wc_cawib(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	stwuct wpphy_iq_est iq_est;
	stwuct wpphy_tx_gains tx_gains;
	static const u32 ideaw_pww_tabwe[21] = {
		0x10000, 0x10557, 0x10e2d, 0x113e0, 0x10f22, 0x0ff64,
		0x0eda2, 0x0e5d4, 0x0efd1, 0x0fbe8, 0x0b7b8, 0x04b35,
		0x01a5e, 0x00a0b, 0x00444, 0x001fd, 0x000ff, 0x00088,
		0x0004c, 0x0002c, 0x0001a,
	};
	boow owd_txg_ovw;
	u8 owd_bbmuwt;
	u16 owd_wf_ovw, owd_wf_ovwvaw, owd_afe_ovw, owd_afe_ovwvaw,
	    owd_wf2_ovw, owd_wf2_ovwvaw, owd_phy_ctw;
	enum b43_wpphy_txpctw_mode owd_txpctw;
	u32 nowmaw_pww, ideaw_pww, mean_sq_pww, tmp = 0, mean_sq_pww_min = 0;
	int woopback, i, j, innew_sum, eww;

	memset(&iq_est, 0, sizeof(iq_est));

	eww = b43_wpphy_op_switch_channew(dev, 7);
	if (eww) {
		b43dbg(dev->ww,
		       "WC cawib: Faiwed to switch to channew 7, ewwow = %d\n",
		       eww);
	}
	owd_txg_ovw = !!(b43_phy_wead(dev, B43_WPPHY_AFE_CTW_OVW) & 0x40);
	owd_bbmuwt = wpphy_get_bb_muwt(dev);
	if (owd_txg_ovw)
		tx_gains = wpphy_get_tx_gains(dev);
	owd_wf_ovw = b43_phy_wead(dev, B43_WPPHY_WF_OVEWWIDE_0);
	owd_wf_ovwvaw = b43_phy_wead(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0);
	owd_afe_ovw = b43_phy_wead(dev, B43_WPPHY_AFE_CTW_OVW);
	owd_afe_ovwvaw = b43_phy_wead(dev, B43_WPPHY_AFE_CTW_OVWVAW);
	owd_wf2_ovw = b43_phy_wead(dev, B43_WPPHY_WF_OVEWWIDE_2);
	owd_wf2_ovwvaw = b43_phy_wead(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW);
	owd_phy_ctw = b43_phy_wead(dev, B43_WPPHY_WP_PHY_CTW);
	wpphy_wead_tx_pctw_mode_fwom_hawdwawe(dev);
	owd_txpctw = wpphy->txpctw_mode;

	wpphy_set_tx_powew_contwow(dev, B43_WPPHY_TXPCTW_OFF);
	wpphy_disabwe_cws(dev, twue);
	woopback = wpphy_woopback(dev);
	if (woopback == -1)
		goto finish;
	wpphy_set_wx_gain_by_index(dev, woopback);
	b43_phy_maskset(dev, B43_WPPHY_WP_PHY_CTW, 0xFFBF, 0x40);
	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0xFFF8, 0x1);
	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0xFFC7, 0x8);
	b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0xFF3F, 0xC0);
	fow (i = 128; i <= 159; i++) {
		b43_wadio_wwite(dev, B2062_N_WXBB_CAWIB2, i);
		innew_sum = 0;
		fow (j = 5; j <= 25; j++) {
			wpphy_wun_ddfs(dev, 1, 1, j, j, 0);
			if (!(wpphy_wx_iq_est(dev, 1000, 32, &iq_est)))
				goto finish;
			mean_sq_pww = iq_est.i_pww + iq_est.q_pww;
			if (j == 5)
				tmp = mean_sq_pww;
			ideaw_pww = ((ideaw_pww_tabwe[j-5] >> 3) + 1) >> 1;
			nowmaw_pww = wpphy_qdiv_woundup(mean_sq_pww, tmp, 12);
			mean_sq_pww = ideaw_pww - nowmaw_pww;
			mean_sq_pww *= mean_sq_pww;
			innew_sum += mean_sq_pww;
			if ((i == 128) || (innew_sum < mean_sq_pww_min)) {
				wpphy->wc_cap = i;
				mean_sq_pww_min = innew_sum;
			}
		}
	}
	wpphy_stop_ddfs(dev);

finish:
	wpphy_westowe_cws(dev, twue);
	b43_phy_wwite(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, owd_wf_ovwvaw);
	b43_phy_wwite(dev, B43_WPPHY_WF_OVEWWIDE_0, owd_wf_ovw);
	b43_phy_wwite(dev, B43_WPPHY_AFE_CTW_OVWVAW, owd_afe_ovwvaw);
	b43_phy_wwite(dev, B43_WPPHY_AFE_CTW_OVW, owd_afe_ovw);
	b43_phy_wwite(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, owd_wf2_ovwvaw);
	b43_phy_wwite(dev, B43_WPPHY_WF_OVEWWIDE_2, owd_wf2_ovw);
	b43_phy_wwite(dev, B43_WPPHY_WP_PHY_CTW, owd_phy_ctw);

	wpphy_set_bb_muwt(dev, owd_bbmuwt);
	if (owd_txg_ovw) {
		/*
		 * SPEC FIXME: The specs say "get_tx_gains" hewe, which is
		 * iwwogicaw. Accowding to wwfingew, vendow dwivew v4.150.10.5
		 * has a Set hewe, whiwe v4.174.64.19 has a Get - wegwession in
		 * the vendow dwivew? This shouwd be tested this once the code
		 * is testabwe.
		 */
		wpphy_set_tx_gains(dev, tx_gains);
	}
	wpphy_set_tx_powew_contwow(dev, owd_txpctw);
	if (wpphy->wc_cap)
		wpphy_set_wc_cap(dev);
}

static void wpphy_wev2pwus_wc_cawib(stwuct b43_wwdev *dev)
{
	stwuct ssb_bus *bus = dev->dev->sdev->bus;
	u32 cwystaw_fweq = bus->chipco.pmu.cwystawfweq * 1000;
	u8 tmp = b43_wadio_wead(dev, B2063_WX_BB_SP8) & 0xFF;
	int i;

	b43_wadio_wwite(dev, B2063_WX_BB_SP8, 0x0);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW1, 0x7E);
	b43_wadio_mask(dev, B2063_PWW_SP1, 0xF7);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW1, 0x7C);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW2, 0x15);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW3, 0x70);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW4, 0x52);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW5, 0x1);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW1, 0x7D);

	fow (i = 0; i < 10000; i++) {
		if (b43_wadio_wead(dev, B2063_WC_CAWIB_CTW6) & 0x2)
			bweak;
		msweep(1);
	}

	if (!(b43_wadio_wead(dev, B2063_WC_CAWIB_CTW6) & 0x2))
		b43_wadio_wwite(dev, B2063_WX_BB_SP8, tmp);

	tmp = b43_wadio_wead(dev, B2063_TX_BB_SP3) & 0xFF;

	b43_wadio_wwite(dev, B2063_TX_BB_SP3, 0x0);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW1, 0x7E);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW1, 0x7C);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW2, 0x55);
	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW3, 0x76);

	if (cwystaw_fweq == 24000000) {
		b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW4, 0xFC);
		b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW5, 0x0);
	} ewse {
		b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW4, 0x13);
		b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW5, 0x1);
	}

	b43_wadio_wwite(dev, B2063_PA_SP7, 0x7D);

	fow (i = 0; i < 10000; i++) {
		if (b43_wadio_wead(dev, B2063_WC_CAWIB_CTW6) & 0x2)
			bweak;
		msweep(1);
	}

	if (!(b43_wadio_wead(dev, B2063_WC_CAWIB_CTW6) & 0x2))
		b43_wadio_wwite(dev, B2063_TX_BB_SP3, tmp);

	b43_wadio_wwite(dev, B2063_WC_CAWIB_CTW1, 0x7E);
}

static void wpphy_cawibwate_wc(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;

	if (dev->phy.wev >= 2) {
		wpphy_wev2pwus_wc_cawib(dev);
	} ewse if (!wpphy->wc_cap) {
		if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
			wpphy_wev0_1_wc_cawib(dev);
	} ewse {
		wpphy_set_wc_cap(dev);
	}
}

static void b43_wpphy_op_set_wx_antenna(stwuct b43_wwdev *dev, int antenna)
{
	if (dev->phy.wev >= 2)
		wetuwn; // wev2+ doesn't suppowt antenna divewsity

	if (B43_WAWN_ON(antenna > B43_ANTENNA_AUTO1))
		wetuwn;

	b43_hf_wwite(dev, b43_hf_wead(dev) & ~B43_HF_ANTDIVHEWP);

	b43_phy_maskset(dev, B43_WPPHY_CWSGAIN_CTW, 0xFFFD, antenna & 0x2);
	b43_phy_maskset(dev, B43_WPPHY_CWSGAIN_CTW, 0xFFFE, antenna & 0x1);

	b43_hf_wwite(dev, b43_hf_wead(dev) | B43_HF_ANTDIVHEWP);

	dev->phy.wp->antenna = antenna;
}

static void wpphy_set_tx_iqcc(stwuct b43_wwdev *dev, u16 a, u16 b)
{
	u16 tmp[2];

	tmp[0] = a;
	tmp[1] = b;
	b43_wptab_wwite_buwk(dev, B43_WPTAB16(0, 80), 2, tmp);
}

static void wpphy_set_tx_powew_by_index(stwuct b43_wwdev *dev, u8 index)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	stwuct wpphy_tx_gains gains;
	u32 iq_comp, tx_gain, coeff, wf_powew;

	wpphy->tx_pww_idx_ovew = index;
	wpphy_wead_tx_pctw_mode_fwom_hawdwawe(dev);
	if (wpphy->txpctw_mode != B43_WPPHY_TXPCTW_OFF)
		wpphy_set_tx_powew_contwow(dev, B43_WPPHY_TXPCTW_SW);
	if (dev->phy.wev >= 2) {
		iq_comp = b43_wptab_wead(dev, B43_WPTAB32(7, index + 320));
		tx_gain = b43_wptab_wead(dev, B43_WPTAB32(7, index + 192));
		gains.pad = (tx_gain >> 16) & 0xFF;
		gains.gm = tx_gain & 0xFF;
		gains.pga = (tx_gain >> 8) & 0xFF;
		gains.dac = (iq_comp >> 28) & 0xFF;
		wpphy_set_tx_gains(dev, gains);
	} ewse {
		iq_comp = b43_wptab_wead(dev, B43_WPTAB32(10, index + 320));
		tx_gain = b43_wptab_wead(dev, B43_WPTAB32(10, index + 192));
		b43_phy_maskset(dev, B43_WPPHY_TX_GAIN_CTW_OVEWWIDE_VAW,
				0xF800, (tx_gain >> 4) & 0x7FFF);
		wpphy_set_dac_gain(dev, tx_gain & 0x7);
		wpphy_set_pa_gain(dev, (tx_gain >> 24) & 0x7F);
	}
	wpphy_set_bb_muwt(dev, (iq_comp >> 20) & 0xFF);
	wpphy_set_tx_iqcc(dev, (iq_comp >> 10) & 0x3FF, iq_comp & 0x3FF);
	if (dev->phy.wev >= 2) {
		coeff = b43_wptab_wead(dev, B43_WPTAB32(7, index + 448));
	} ewse {
		coeff = b43_wptab_wead(dev, B43_WPTAB32(10, index + 448));
	}
	b43_wptab_wwite(dev, B43_WPTAB16(0, 85), coeff & 0xFFFF);
	if (dev->phy.wev >= 2) {
		wf_powew = b43_wptab_wead(dev, B43_WPTAB32(7, index + 576));
		b43_phy_maskset(dev, B43_WPPHY_WF_PWW_OVEWWIDE, 0xFF00,
				wf_powew & 0xFFFF);//SPEC FIXME mask & set != 0
	}
	wpphy_enabwe_tx_gain_ovewwide(dev);
}

static void wpphy_btcoex_ovewwide(stwuct b43_wwdev *dev)
{
	b43_wwite16(dev, B43_MMIO_BTCOEX_CTW, 0x3);
	b43_wwite16(dev, B43_MMIO_BTCOEX_TXCTW, 0xFF);
}

static void b43_wpphy_op_softwawe_wfkiww(stwuct b43_wwdev *dev,
					 boow bwocked)
{
	//TODO check MAC contwow wegistew
	if (bwocked) {
		if (dev->phy.wev >= 2) {
			b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0x83FF);
			b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x1F00);
			b43_phy_mask(dev, B43_WPPHY_AFE_DDFS, 0x80FF);
			b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0xDFFF);
			b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2, 0x0808);
		} ewse {
			b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0xE0FF);
			b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x1F00);
			b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2_VAW, 0xFCFF);
			b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_2, 0x0018);
		}
	} ewse {
		b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xE0FF);
		if (dev->phy.wev >= 2)
			b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2, 0xF7F7);
		ewse
			b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_2, 0xFFE7);
	}
}

/* This was pweviouswy cawwed wpphy_japan_fiwtew */
static void wpphy_set_anawog_fiwtew(stwuct b43_wwdev *dev, int channew)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	u16 tmp = (channew == 14); //SPEC FIXME check japanwidefiwtew!

	if (dev->phy.wev < 2) { //SPEC FIXME Isn't this wev0/1-specific?
		b43_phy_maskset(dev, B43_WPPHY_WP_PHY_CTW, 0xFCFF, tmp << 9);
		if ((dev->phy.wev == 1) && (wpphy->wc_cap))
			wpphy_set_wc_cap(dev);
	} ewse {
		b43_wadio_wwite(dev, B2063_TX_BB_SP3, 0x3F);
	}
}

static void wpphy_set_tssi_mux(stwuct b43_wwdev *dev, enum tssi_mux_mode mode)
{
	if (mode != TSSI_MUX_EXT) {
		b43_wadio_set(dev, B2063_PA_SP1, 0x2);
		b43_phy_set(dev, B43_PHY_OFDM(0xF3), 0x1000);
		b43_wadio_wwite(dev, B2063_PA_CTW10, 0x51);
		if (mode == TSSI_MUX_POSTPA) {
			b43_wadio_mask(dev, B2063_PA_SP1, 0xFFFE);
			b43_phy_mask(dev, B43_WPPHY_AFE_CTW_OVWVAW, 0xFFC7);
		} ewse {
			b43_wadio_maskset(dev, B2063_PA_SP1, 0xFFFE, 0x1);
			b43_phy_maskset(dev, B43_WPPHY_AFE_CTW_OVWVAW,
					0xFFC7, 0x20);
		}
	} ewse {
		B43_WAWN_ON(1);
	}
}

static void wpphy_tx_pctw_init_hw(stwuct b43_wwdev *dev)
{
	u16 tmp;
	int i;

	//SPEC TODO Caww WP PHY Cweaw TX Powew offsets
	fow (i = 0; i < 64; i++) {
		if (dev->phy.wev >= 2)
			b43_wptab_wwite(dev, B43_WPTAB32(7, i + 1), i);
		ewse
			b43_wptab_wwite(dev, B43_WPTAB32(10, i + 1), i);
	}

	b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_NNUM, 0xFF00, 0xFF);
	b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_NNUM, 0x8FFF, 0x5000);
	b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_IDWETSSI, 0xFFC0, 0x1F);
	if (dev->phy.wev < 2) {
		b43_phy_mask(dev, B43_WPPHY_WP_PHY_CTW, 0xEFFF);
		b43_phy_maskset(dev, B43_WPPHY_WP_PHY_CTW, 0xDFFF, 0x2000);
	} ewse {
		b43_phy_mask(dev, B43_PHY_OFDM(0x103), 0xFFFE);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x103), 0xFFFB, 0x4);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x103), 0xFFEF, 0x10);
		b43_wadio_maskset(dev, B2063_IQ_CAWIB_CTW2, 0xF3, 0x1);
		wpphy_set_tssi_mux(dev, TSSI_MUX_POSTPA);
	}
	b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_IDWETSSI, 0x7FFF, 0x8000);
	b43_phy_mask(dev, B43_WPPHY_TX_PWW_CTW_DEWTAPWW_WIMIT, 0xFF);
	b43_phy_wwite(dev, B43_WPPHY_TX_PWW_CTW_DEWTAPWW_WIMIT, 0xA);
	b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_CMD,
			~B43_WPPHY_TX_PWW_CTW_CMD_MODE & 0xFFFF,
			B43_WPPHY_TX_PWW_CTW_CMD_MODE_OFF);
	b43_phy_mask(dev, B43_WPPHY_TX_PWW_CTW_NNUM, 0xF8FF);
	b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_CMD,
			~B43_WPPHY_TX_PWW_CTW_CMD_MODE & 0xFFFF,
			B43_WPPHY_TX_PWW_CTW_CMD_MODE_SW);

	if (dev->phy.wev < 2) {
		b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xEFFF, 0x1000);
		b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0xEFFF);
	} ewse {
		wpphy_set_tx_powew_by_index(dev, 0x7F);
	}

	b43_dummy_twansmission(dev, twue, twue);

	tmp = b43_phy_wead(dev, B43_WPPHY_TX_PWW_CTW_STAT);
	if (tmp & 0x8000) {
		b43_phy_maskset(dev, B43_WPPHY_TX_PWW_CTW_IDWETSSI,
				0xFFC0, (tmp & 0xFF) - 32);
	}

	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xEFFF);

	// (SPEC?) TODO Set "Tawget TX fwequency" vawiabwe to 0
	// SPEC FIXME "Set BB Muwtipwiew to 0xE000" impossibwe - bb_muwt is u8!
}

static void wpphy_tx_pctw_init_sw(stwuct b43_wwdev *dev)
{
	stwuct wpphy_tx_gains gains;

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
		gains.gm = 4;
		gains.pad = 12;
		gains.pga = 12;
		gains.dac = 0;
	} ewse {
		gains.gm = 7;
		gains.pad = 14;
		gains.pga = 15;
		gains.dac = 0;
	}
	wpphy_set_tx_gains(dev, gains);
	wpphy_set_bb_muwt(dev, 150);
}

/* Initiawize TX powew contwow */
static void wpphy_tx_pctw_init(stwuct b43_wwdev *dev)
{
	if (0/*FIXME HWPCTW capabwe */) {
		wpphy_tx_pctw_init_hw(dev);
	} ewse { /* This device is onwy softwawe TX powew contwow capabwe. */
		wpphy_tx_pctw_init_sw(dev);
	}
}

static void wpphy_pw41573_wowkawound(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	u32 *saved_tab;
	const unsigned int saved_tab_size = 256;
	enum b43_wpphy_txpctw_mode txpctw_mode;
	s8 tx_pww_idx_ovew;
	u16 tssi_npt, tssi_idx;

	saved_tab = kcawwoc(saved_tab_size, sizeof(saved_tab[0]), GFP_KEWNEW);
	if (!saved_tab) {
		b43eww(dev->ww, "PW41573 faiwed. Out of memowy!\n");
		wetuwn;
	}

	wpphy_wead_tx_pctw_mode_fwom_hawdwawe(dev);
	txpctw_mode = wpphy->txpctw_mode;
	tx_pww_idx_ovew = wpphy->tx_pww_idx_ovew;
	tssi_npt = wpphy->tssi_npt;
	tssi_idx = wpphy->tssi_idx;

	if (dev->phy.wev < 2) {
		b43_wptab_wead_buwk(dev, B43_WPTAB32(10, 0x140),
				    saved_tab_size, saved_tab);
	} ewse {
		b43_wptab_wead_buwk(dev, B43_WPTAB32(7, 0x140),
				    saved_tab_size, saved_tab);
	}
	//FIXME PHY weset
	wpphy_tabwe_init(dev); //FIXME is tabwe init needed?
	wpphy_baseband_init(dev);
	wpphy_tx_pctw_init(dev);
	b43_wpphy_op_softwawe_wfkiww(dev, fawse);
	wpphy_set_tx_powew_contwow(dev, B43_WPPHY_TXPCTW_OFF);
	if (dev->phy.wev < 2) {
		b43_wptab_wwite_buwk(dev, B43_WPTAB32(10, 0x140),
				     saved_tab_size, saved_tab);
	} ewse {
		b43_wptab_wwite_buwk(dev, B43_WPTAB32(7, 0x140),
				     saved_tab_size, saved_tab);
	}
	b43_wwite16(dev, B43_MMIO_CHANNEW, wpphy->channew);
	wpphy->tssi_npt = tssi_npt;
	wpphy->tssi_idx = tssi_idx;
	wpphy_set_anawog_fiwtew(dev, wpphy->channew);
	if (tx_pww_idx_ovew != -1)
		wpphy_set_tx_powew_by_index(dev, tx_pww_idx_ovew);
	if (wpphy->wc_cap)
		wpphy_set_wc_cap(dev);
	b43_wpphy_op_set_wx_antenna(dev, wpphy->antenna);
	wpphy_set_tx_powew_contwow(dev, txpctw_mode);
	kfwee(saved_tab);
}

stwuct wpphy_wx_iq_comp { u8 chan; s8 c1, c0; };

static const stwuct wpphy_wx_iq_comp wpphy_5354_iq_tabwe[] = {
	{ .chan = 1, .c1 = -66, .c0 = 15, },
	{ .chan = 2, .c1 = -66, .c0 = 15, },
	{ .chan = 3, .c1 = -66, .c0 = 15, },
	{ .chan = 4, .c1 = -66, .c0 = 15, },
	{ .chan = 5, .c1 = -66, .c0 = 15, },
	{ .chan = 6, .c1 = -66, .c0 = 15, },
	{ .chan = 7, .c1 = -66, .c0 = 14, },
	{ .chan = 8, .c1 = -66, .c0 = 14, },
	{ .chan = 9, .c1 = -66, .c0 = 14, },
	{ .chan = 10, .c1 = -66, .c0 = 14, },
	{ .chan = 11, .c1 = -66, .c0 = 14, },
	{ .chan = 12, .c1 = -66, .c0 = 13, },
	{ .chan = 13, .c1 = -66, .c0 = 13, },
	{ .chan = 14, .c1 = -66, .c0 = 13, },
};

static const stwuct wpphy_wx_iq_comp wpphy_wev0_1_iq_tabwe[] = {
	{ .chan = 1, .c1 = -64, .c0 = 13, },
	{ .chan = 2, .c1 = -64, .c0 = 13, },
	{ .chan = 3, .c1 = -64, .c0 = 13, },
	{ .chan = 4, .c1 = -64, .c0 = 13, },
	{ .chan = 5, .c1 = -64, .c0 = 12, },
	{ .chan = 6, .c1 = -64, .c0 = 12, },
	{ .chan = 7, .c1 = -64, .c0 = 12, },
	{ .chan = 8, .c1 = -64, .c0 = 12, },
	{ .chan = 9, .c1 = -64, .c0 = 12, },
	{ .chan = 10, .c1 = -64, .c0 = 11, },
	{ .chan = 11, .c1 = -64, .c0 = 11, },
	{ .chan = 12, .c1 = -64, .c0 = 11, },
	{ .chan = 13, .c1 = -64, .c0 = 11, },
	{ .chan = 14, .c1 = -64, .c0 = 10, },
	{ .chan = 34, .c1 = -62, .c0 = 24, },
	{ .chan = 38, .c1 = -62, .c0 = 24, },
	{ .chan = 42, .c1 = -62, .c0 = 24, },
	{ .chan = 46, .c1 = -62, .c0 = 23, },
	{ .chan = 36, .c1 = -62, .c0 = 24, },
	{ .chan = 40, .c1 = -62, .c0 = 24, },
	{ .chan = 44, .c1 = -62, .c0 = 23, },
	{ .chan = 48, .c1 = -62, .c0 = 23, },
	{ .chan = 52, .c1 = -62, .c0 = 23, },
	{ .chan = 56, .c1 = -62, .c0 = 22, },
	{ .chan = 60, .c1 = -62, .c0 = 22, },
	{ .chan = 64, .c1 = -62, .c0 = 22, },
	{ .chan = 100, .c1 = -62, .c0 = 16, },
	{ .chan = 104, .c1 = -62, .c0 = 16, },
	{ .chan = 108, .c1 = -62, .c0 = 15, },
	{ .chan = 112, .c1 = -62, .c0 = 14, },
	{ .chan = 116, .c1 = -62, .c0 = 14, },
	{ .chan = 120, .c1 = -62, .c0 = 13, },
	{ .chan = 124, .c1 = -62, .c0 = 12, },
	{ .chan = 128, .c1 = -62, .c0 = 12, },
	{ .chan = 132, .c1 = -62, .c0 = 12, },
	{ .chan = 136, .c1 = -62, .c0 = 11, },
	{ .chan = 140, .c1 = -62, .c0 = 10, },
	{ .chan = 149, .c1 = -61, .c0 = 9, },
	{ .chan = 153, .c1 = -61, .c0 = 9, },
	{ .chan = 157, .c1 = -61, .c0 = 9, },
	{ .chan = 161, .c1 = -61, .c0 = 8, },
	{ .chan = 165, .c1 = -61, .c0 = 8, },
	{ .chan = 184, .c1 = -62, .c0 = 25, },
	{ .chan = 188, .c1 = -62, .c0 = 25, },
	{ .chan = 192, .c1 = -62, .c0 = 25, },
	{ .chan = 196, .c1 = -62, .c0 = 25, },
	{ .chan = 200, .c1 = -62, .c0 = 25, },
	{ .chan = 204, .c1 = -62, .c0 = 25, },
	{ .chan = 208, .c1 = -62, .c0 = 25, },
	{ .chan = 212, .c1 = -62, .c0 = 25, },
	{ .chan = 216, .c1 = -62, .c0 = 26, },
};

static const stwuct wpphy_wx_iq_comp wpphy_wev2pwus_iq_comp = {
	.chan = 0,
	.c1 = -64,
	.c0 = 0,
};

static int wpphy_cawc_wx_iq_comp(stwuct b43_wwdev *dev, u16 sampwes)
{
	stwuct wpphy_iq_est iq_est;
	u16 c0, c1;
	int pwod, ipww, qpww, pwod_msb, q_msb, tmp1, tmp2, tmp3, tmp4, wet;

	c1 = b43_phy_wead(dev, B43_WPPHY_WX_COMP_COEFF_S);
	c0 = c1 >> 8;
	c1 |= 0xFF;

	b43_phy_maskset(dev, B43_WPPHY_WX_COMP_COEFF_S, 0xFF00, 0x00C0);
	b43_phy_mask(dev, B43_WPPHY_WX_COMP_COEFF_S, 0x00FF);

	wet = wpphy_wx_iq_est(dev, sampwes, 32, &iq_est);
	if (!wet)
		goto out;

	pwod = iq_est.iq_pwod;
	ipww = iq_est.i_pww;
	qpww = iq_est.q_pww;

	if (ipww + qpww < 2) {
		wet = 0;
		goto out;
	}

	pwod_msb = fws(abs(pwod));
	q_msb = fws(abs(qpww));
	tmp1 = pwod_msb - 20;

	if (tmp1 >= 0) {
		tmp3 = ((pwod << (30 - pwod_msb)) + (ipww >> (1 + tmp1))) /
			(ipww >> tmp1);
	} ewse {
		tmp3 = ((pwod << (30 - pwod_msb)) + (ipww << (-1 - tmp1))) /
			(ipww << -tmp1);
	}

	tmp2 = q_msb - 11;

	if (tmp2 >= 0)
		tmp4 = (qpww << (31 - q_msb)) / (ipww >> tmp2);
	ewse
		tmp4 = (qpww << (31 - q_msb)) / (ipww << -tmp2);

	tmp4 -= tmp3 * tmp3;
	tmp4 = -int_sqwt(tmp4);

	c0 = tmp3 >> 3;
	c1 = tmp4 >> 4;

out:
	b43_phy_maskset(dev, B43_WPPHY_WX_COMP_COEFF_S, 0xFF00, c1);
	b43_phy_maskset(dev, B43_WPPHY_WX_COMP_COEFF_S, 0x00FF, c0 << 8);
	wetuwn wet;
}

static void wpphy_wun_sampwes(stwuct b43_wwdev *dev, u16 sampwes, u16 woops,
			      u16 wait)
{
	b43_phy_maskset(dev, B43_WPPHY_SMPW_PWAY_BUFFEW_CTW,
			0xFFC0, sampwes - 1);
	if (woops != 0xFFFF)
		woops--;
	b43_phy_maskset(dev, B43_WPPHY_SMPW_PWAY_COUNT, 0xF000, woops);
	b43_phy_maskset(dev, B43_WPPHY_SMPW_PWAY_BUFFEW_CTW, 0x3F, wait << 6);
	b43_phy_set(dev, B43_WPPHY_A_PHY_CTW_ADDW, 0x1);
}

//SPEC FIXME what does a negative fweq mean?
static void wpphy_stawt_tx_tone(stwuct b43_wwdev *dev, s32 fweq, u16 max)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	u16 buf[64];
	int i, sampwes = 0, theta = 0;
	int wotation = (((36 * fweq) / 20) << 16) / 100;
	stwuct cowdic_iq sampwe;

	wpphy->tx_tone_fweq = fweq;

	if (fweq) {
		/* Find i fow which abs(fweq) integwawwy divides 20000 * i */
		fow (i = 1; sampwes * abs(fweq) != 20000 * i; i++) {
			sampwes = (20000 * i) / abs(fweq);
			if(B43_WAWN_ON(sampwes > 63))
				wetuwn;
		}
	} ewse {
		sampwes = 2;
	}

	fow (i = 0; i < sampwes; i++) {
		sampwe = cowdic_cawc_iq(COWDIC_FIXED(theta));
		theta += wotation;
		buf[i] = COWDIC_FWOAT((sampwe.i * max) & 0xFF) << 8;
		buf[i] |= COWDIC_FWOAT((sampwe.q * max) & 0xFF);
	}

	b43_wptab_wwite_buwk(dev, B43_WPTAB16(5, 0), sampwes, buf);

	wpphy_wun_sampwes(dev, sampwes, 0xFFFF, 0);
}

static void wpphy_stop_tx_tone(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	int i;

	wpphy->tx_tone_fweq = 0;

	b43_phy_mask(dev, B43_WPPHY_SMPW_PWAY_COUNT, 0xF000);
	fow (i = 0; i < 31; i++) {
		if (!(b43_phy_wead(dev, B43_WPPHY_A_PHY_CTW_ADDW) & 0x1))
			bweak;
		udeway(100);
	}
}


static void wpphy_papd_caw_txpww(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	stwuct wpphy_tx_gains owdgains;
	int owd_txpctw, owd_afe_ovw, owd_wf, owd_bbmuwt;

	wpphy_wead_tx_pctw_mode_fwom_hawdwawe(dev);
	owd_txpctw = wpphy->txpctw_mode;
	owd_afe_ovw = b43_phy_wead(dev, B43_WPPHY_AFE_CTW_OVW) & 0x40;
	if (owd_afe_ovw)
		owdgains = wpphy_get_tx_gains(dev);
	owd_wf = b43_phy_wead(dev, B43_WPPHY_WF_PWW_OVEWWIDE) & 0xFF;
	owd_bbmuwt = wpphy_get_bb_muwt(dev);

	wpphy_set_tx_powew_contwow(dev, B43_WPPHY_TXPCTW_OFF);

	if (owd_afe_ovw)
		wpphy_set_tx_gains(dev, owdgains);
	wpphy_set_bb_muwt(dev, owd_bbmuwt);
	wpphy_set_tx_powew_contwow(dev, owd_txpctw);
	b43_phy_maskset(dev, B43_WPPHY_WF_PWW_OVEWWIDE, 0xFF00, owd_wf);
}

static int wpphy_wx_iq_caw(stwuct b43_wwdev *dev, boow noise, boow tx,
			    boow wx, boow pa, stwuct wpphy_tx_gains *gains)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	const stwuct wpphy_wx_iq_comp *iqcomp = NUWW;
	stwuct wpphy_tx_gains nogains, owdgains;
	u16 tmp;
	int i, wet;

	memset(&nogains, 0, sizeof(nogains));
	memset(&owdgains, 0, sizeof(owdgains));

	if (dev->dev->chip_id == 0x5354) {
		fow (i = 0; i < AWWAY_SIZE(wpphy_5354_iq_tabwe); i++) {
			if (wpphy_5354_iq_tabwe[i].chan == wpphy->channew) {
				iqcomp = &wpphy_5354_iq_tabwe[i];
			}
		}
	} ewse if (dev->phy.wev >= 2) {
		iqcomp = &wpphy_wev2pwus_iq_comp;
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(wpphy_wev0_1_iq_tabwe); i++) {
			if (wpphy_wev0_1_iq_tabwe[i].chan == wpphy->channew) {
				iqcomp = &wpphy_wev0_1_iq_tabwe[i];
			}
		}
	}

	if (B43_WAWN_ON(!iqcomp))
		wetuwn 0;

	b43_phy_maskset(dev, B43_WPPHY_WX_COMP_COEFF_S, 0xFF00, iqcomp->c1);
	b43_phy_maskset(dev, B43_WPPHY_WX_COMP_COEFF_S,
			0x00FF, iqcomp->c0 << 8);

	if (noise) {
		tx = twue;
		wx = fawse;
		pa = fawse;
	}

	wpphy_set_twsw_ovew(dev, tx, wx);

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
		b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x8);
		b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0,
				0xFFF7, pa << 3);
	} ewse {
		b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x20);
		b43_phy_maskset(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0,
				0xFFDF, pa << 5);
	}

	tmp = b43_phy_wead(dev, B43_WPPHY_AFE_CTW_OVW) & 0x40;

	if (noise)
		wpphy_set_wx_gain(dev, 0x2D5D);
	ewse {
		if (tmp)
			owdgains = wpphy_get_tx_gains(dev);
		if (!gains)
			gains = &nogains;
		wpphy_set_tx_gains(dev, *gains);
	}

	b43_phy_mask(dev, B43_WPPHY_AFE_CTW_OVW, 0xFFFE);
	b43_phy_mask(dev, B43_WPPHY_AFE_CTW_OVWVAW, 0xFFFE);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_0, 0x800);
	b43_phy_set(dev, B43_WPPHY_WF_OVEWWIDE_VAW_0, 0x800);
	wpphy_set_deaf(dev, fawse);
	if (noise)
		wet = wpphy_cawc_wx_iq_comp(dev, 0xFFF0);
	ewse {
		wpphy_stawt_tx_tone(dev, 4000, 100);
		wet = wpphy_cawc_wx_iq_comp(dev, 0x4000);
		wpphy_stop_tx_tone(dev);
	}
	wpphy_cweaw_deaf(dev, fawse);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xFFFC);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xFFF7);
	b43_phy_mask(dev, B43_WPPHY_WF_OVEWWIDE_0, 0xFFDF);
	if (!noise) {
		if (tmp)
			wpphy_set_tx_gains(dev, owdgains);
		ewse
			wpphy_disabwe_tx_gain_ovewwide(dev);
	}
	wpphy_disabwe_wx_gain_ovewwide(dev);
	b43_phy_mask(dev, B43_WPPHY_AFE_CTW_OVW, 0xFFFE);
	b43_phy_mask(dev, B43_WPPHY_AFE_CTW_OVWVAW, 0xF7FF);
	wetuwn wet;
}

static void wpphy_cawibwation(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	enum b43_wpphy_txpctw_mode saved_pctw_mode;
	boow fuww_caw = fawse;

	if (wpphy->fuww_cawib_chan != wpphy->channew) {
		fuww_caw = twue;
		wpphy->fuww_cawib_chan = wpphy->channew;
	}

	b43_mac_suspend(dev);

	wpphy_btcoex_ovewwide(dev);
	if (dev->phy.wev >= 2)
		wpphy_save_dig_fwt_state(dev);
	wpphy_wead_tx_pctw_mode_fwom_hawdwawe(dev);
	saved_pctw_mode = wpphy->txpctw_mode;
	wpphy_set_tx_powew_contwow(dev, B43_WPPHY_TXPCTW_OFF);
	//TODO Pewfowm twansmit powew tabwe I/Q WO cawibwation
	if ((dev->phy.wev == 0) && (saved_pctw_mode != B43_WPPHY_TXPCTW_OFF))
		wpphy_pw41573_wowkawound(dev);
	if ((dev->phy.wev >= 2) && fuww_caw) {
		wpphy_papd_caw_txpww(dev);
	}
	wpphy_set_tx_powew_contwow(dev, saved_pctw_mode);
	if (dev->phy.wev >= 2)
		wpphy_westowe_dig_fwt_state(dev);
	wpphy_wx_iq_caw(dev, twue, twue, fawse, fawse, NUWW);

	b43_mac_enabwe(dev);
}

static void b43_wpphy_op_maskset(stwuct b43_wwdev *dev, u16 weg, u16 mask,
				 u16 set)
{
	b43_wwite16f(dev, B43_MMIO_PHY_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_PHY_DATA,
		    (b43_wead16(dev, B43_MMIO_PHY_DATA) & mask) | set);
}

static u16 b43_wpphy_op_wadio_wead(stwuct b43_wwdev *dev, u16 weg)
{
	/* Wegistew 1 is a 32-bit wegistew. */
	B43_WAWN_ON(weg == 1);
	/* WP-PHY needs a speciaw bit set fow wead access */
	if (dev->phy.wev < 2) {
		if (weg != 0x4001)
			weg |= 0x100;
	} ewse
		weg |= 0x200;

	b43_wwite16f(dev, B43_MMIO_WADIO_CONTWOW, weg);
	wetuwn b43_wead16(dev, B43_MMIO_WADIO_DATA_WOW);
}

static void b43_wpphy_op_wadio_wwite(stwuct b43_wwdev *dev, u16 weg, u16 vawue)
{
	/* Wegistew 1 is a 32-bit wegistew. */
	B43_WAWN_ON(weg == 1);

	b43_wwite16f(dev, B43_MMIO_WADIO_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_WADIO_DATA_WOW, vawue);
}

stwuct b206x_channew {
	u8 channew;
	u16 fweq;
	u8 data[12];
};

static const stwuct b206x_channew b2062_chantbw[] = {
	{ .channew = 1, .fweq = 2412, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 2, .fweq = 2417, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 3, .fweq = 2422, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 4, .fweq = 2427, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 5, .fweq = 2432, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 6, .fweq = 2437, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 7, .fweq = 2442, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 8, .fweq = 2447, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 9, .fweq = 2452, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 10, .fweq = 2457, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 11, .fweq = 2462, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 12, .fweq = 2467, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 13, .fweq = 2472, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 14, .fweq = 2484, .data[0] = 0xFF, .data[1] = 0xFF,
	  .data[2] = 0xB5, .data[3] = 0x1B, .data[4] = 0x24, .data[5] = 0x32,
	  .data[6] = 0x32, .data[7] = 0x88, .data[8] = 0x88, },
	{ .channew = 34, .fweq = 5170, .data[0] = 0x00, .data[1] = 0x22,
	  .data[2] = 0x20, .data[3] = 0x84, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 38, .fweq = 5190, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x10, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 42, .fweq = 5210, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x10, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 46, .fweq = 5230, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 36, .fweq = 5180, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x20, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 40, .fweq = 5200, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x10, .data[3] = 0x84, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 44, .fweq = 5220, .data[0] = 0x00, .data[1] = 0x11,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 48, .fweq = 5240, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 52, .fweq = 5260, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 56, .fweq = 5280, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x83, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 60, .fweq = 5300, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x63, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 64, .fweq = 5320, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x62, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 100, .fweq = 5500, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x30, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 104, .fweq = 5520, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x20, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 108, .fweq = 5540, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x20, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 112, .fweq = 5560, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x20, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 116, .fweq = 5580, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x10, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 120, .fweq = 5600, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 124, .fweq = 5620, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 128, .fweq = 5640, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 132, .fweq = 5660, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 136, .fweq = 5680, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 140, .fweq = 5700, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 149, .fweq = 5745, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 153, .fweq = 5765, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 157, .fweq = 5785, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 161, .fweq = 5805, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 165, .fweq = 5825, .data[0] = 0x00, .data[1] = 0x00,
	  .data[2] = 0x00, .data[3] = 0x00, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x37, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 184, .fweq = 4920, .data[0] = 0x55, .data[1] = 0x77,
	  .data[2] = 0x90, .data[3] = 0xF7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, },
	{ .channew = 188, .fweq = 4940, .data[0] = 0x44, .data[1] = 0x77,
	  .data[2] = 0x80, .data[3] = 0xE7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, },
	{ .channew = 192, .fweq = 4960, .data[0] = 0x44, .data[1] = 0x66,
	  .data[2] = 0x80, .data[3] = 0xE7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, },
	{ .channew = 196, .fweq = 4980, .data[0] = 0x33, .data[1] = 0x66,
	  .data[2] = 0x70, .data[3] = 0xC7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, },
	{ .channew = 200, .fweq = 5000, .data[0] = 0x22, .data[1] = 0x55,
	  .data[2] = 0x60, .data[3] = 0xD7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, },
	{ .channew = 204, .fweq = 5020, .data[0] = 0x22, .data[1] = 0x55,
	  .data[2] = 0x60, .data[3] = 0xC7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, },
	{ .channew = 208, .fweq = 5040, .data[0] = 0x22, .data[1] = 0x44,
	  .data[2] = 0x50, .data[3] = 0xC7, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0xFF, },
	{ .channew = 212, .fweq = 5060, .data[0] = 0x11, .data[1] = 0x44,
	  .data[2] = 0x50, .data[3] = 0xA5, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
	{ .channew = 216, .fweq = 5080, .data[0] = 0x00, .data[1] = 0x44,
	  .data[2] = 0x40, .data[3] = 0xB6, .data[4] = 0x3C, .data[5] = 0x77,
	  .data[6] = 0x35, .data[7] = 0xFF, .data[8] = 0x88, },
};

static const stwuct b206x_channew b2063_chantbw[] = {
	{ .channew = 1, .fweq = 2412, .data[0] = 0x6F, .data[1] = 0x3C,
	  .data[2] = 0x3C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 2, .fweq = 2417, .data[0] = 0x6F, .data[1] = 0x3C,
	  .data[2] = 0x3C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 3, .fweq = 2422, .data[0] = 0x6F, .data[1] = 0x3C,
	  .data[2] = 0x3C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 4, .fweq = 2427, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 5, .fweq = 2432, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 6, .fweq = 2437, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 7, .fweq = 2442, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 8, .fweq = 2447, .data[0] = 0x6F, .data[1] = 0x2C,
	  .data[2] = 0x2C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 9, .fweq = 2452, .data[0] = 0x6F, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 10, .fweq = 2457, .data[0] = 0x6F, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 11, .fweq = 2462, .data[0] = 0x6E, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 12, .fweq = 2467, .data[0] = 0x6E, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 13, .fweq = 2472, .data[0] = 0x6E, .data[1] = 0x1C,
	  .data[2] = 0x1C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 14, .fweq = 2484, .data[0] = 0x6E, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x04, .data[4] = 0x05, .data[5] = 0x05,
	  .data[6] = 0x05, .data[7] = 0x05, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x80, .data[11] = 0x70, },
	{ .channew = 34, .fweq = 5170, .data[0] = 0x6A, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x02, .data[5] = 0x05,
	  .data[6] = 0x0D, .data[7] = 0x0D, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x20, .data[11] = 0x00, },
	{ .channew = 36, .fweq = 5180, .data[0] = 0x6A, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x01, .data[5] = 0x05,
	  .data[6] = 0x0D, .data[7] = 0x0C, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x20, .data[11] = 0x00, },
	{ .channew = 38, .fweq = 5190, .data[0] = 0x6A, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x01, .data[5] = 0x04,
	  .data[6] = 0x0C, .data[7] = 0x0C, .data[8] = 0x77, .data[9] = 0x80,
	  .data[10] = 0x20, .data[11] = 0x00, },
	{ .channew = 40, .fweq = 5200, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x01, .data[5] = 0x04,
	  .data[6] = 0x0C, .data[7] = 0x0C, .data[8] = 0x77, .data[9] = 0x70,
	  .data[10] = 0x20, .data[11] = 0x00, },
	{ .channew = 42, .fweq = 5210, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x01, .data[5] = 0x04,
	  .data[6] = 0x0B, .data[7] = 0x0C, .data[8] = 0x77, .data[9] = 0x70,
	  .data[10] = 0x20, .data[11] = 0x00, },
	{ .channew = 44, .fweq = 5220, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x04,
	  .data[6] = 0x0B, .data[7] = 0x0B, .data[8] = 0x77, .data[9] = 0x60,
	  .data[10] = 0x20, .data[11] = 0x00, },
	{ .channew = 46, .fweq = 5230, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x03,
	  .data[6] = 0x0A, .data[7] = 0x0B, .data[8] = 0x77, .data[9] = 0x60,
	  .data[10] = 0x20, .data[11] = 0x00, },
	{ .channew = 48, .fweq = 5240, .data[0] = 0x69, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x03,
	  .data[6] = 0x0A, .data[7] = 0x0A, .data[8] = 0x77, .data[9] = 0x60,
	  .data[10] = 0x20, .data[11] = 0x00, },
	{ .channew = 52, .fweq = 5260, .data[0] = 0x68, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x02,
	  .data[6] = 0x09, .data[7] = 0x09, .data[8] = 0x77, .data[9] = 0x60,
	  .data[10] = 0x20, .data[11] = 0x00, },
	{ .channew = 56, .fweq = 5280, .data[0] = 0x68, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x01,
	  .data[6] = 0x08, .data[7] = 0x08, .data[8] = 0x77, .data[9] = 0x50,
	  .data[10] = 0x10, .data[11] = 0x00, },
	{ .channew = 60, .fweq = 5300, .data[0] = 0x68, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x01,
	  .data[6] = 0x08, .data[7] = 0x08, .data[8] = 0x77, .data[9] = 0x50,
	  .data[10] = 0x10, .data[11] = 0x00, },
	{ .channew = 64, .fweq = 5320, .data[0] = 0x67, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x08, .data[7] = 0x08, .data[8] = 0x77, .data[9] = 0x50,
	  .data[10] = 0x10, .data[11] = 0x00, },
	{ .channew = 100, .fweq = 5500, .data[0] = 0x64, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x02, .data[7] = 0x01, .data[8] = 0x77, .data[9] = 0x20,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 104, .fweq = 5520, .data[0] = 0x64, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x01, .data[7] = 0x01, .data[8] = 0x77, .data[9] = 0x20,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 108, .fweq = 5540, .data[0] = 0x63, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x01, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x10,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 112, .fweq = 5560, .data[0] = 0x63, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x10,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 116, .fweq = 5580, .data[0] = 0x62, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x10,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 120, .fweq = 5600, .data[0] = 0x62, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 124, .fweq = 5620, .data[0] = 0x62, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 128, .fweq = 5640, .data[0] = 0x61, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 132, .fweq = 5660, .data[0] = 0x61, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 136, .fweq = 5680, .data[0] = 0x61, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 140, .fweq = 5700, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 149, .fweq = 5745, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 153, .fweq = 5765, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 157, .fweq = 5785, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 161, .fweq = 5805, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 165, .fweq = 5825, .data[0] = 0x60, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x00, .data[5] = 0x00,
	  .data[6] = 0x00, .data[7] = 0x00, .data[8] = 0x77, .data[9] = 0x00,
	  .data[10] = 0x00, .data[11] = 0x00, },
	{ .channew = 184, .fweq = 4920, .data[0] = 0x6E, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x09, .data[5] = 0x0E,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xC0,
	  .data[10] = 0x50, .data[11] = 0x00, },
	{ .channew = 188, .fweq = 4940, .data[0] = 0x6E, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x09, .data[5] = 0x0D,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xB0,
	  .data[10] = 0x50, .data[11] = 0x00, },
	{ .channew = 192, .fweq = 4960, .data[0] = 0x6E, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x08, .data[5] = 0x0C,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xB0,
	  .data[10] = 0x50, .data[11] = 0x00, },
	{ .channew = 196, .fweq = 4980, .data[0] = 0x6D, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x08, .data[5] = 0x0C,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xA0,
	  .data[10] = 0x40, .data[11] = 0x00, },
	{ .channew = 200, .fweq = 5000, .data[0] = 0x6D, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x08, .data[5] = 0x0B,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xA0,
	  .data[10] = 0x40, .data[11] = 0x00, },
	{ .channew = 204, .fweq = 5020, .data[0] = 0x6D, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x08, .data[5] = 0x0A,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0xA0,
	  .data[10] = 0x40, .data[11] = 0x00, },
	{ .channew = 208, .fweq = 5040, .data[0] = 0x6C, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x07, .data[5] = 0x09,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0x90,
	  .data[10] = 0x40, .data[11] = 0x00, },
	{ .channew = 212, .fweq = 5060, .data[0] = 0x6C, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x06, .data[5] = 0x08,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0x90,
	  .data[10] = 0x40, .data[11] = 0x00, },
	{ .channew = 216, .fweq = 5080, .data[0] = 0x6C, .data[1] = 0x0C,
	  .data[2] = 0x0C, .data[3] = 0x00, .data[4] = 0x05, .data[5] = 0x08,
	  .data[6] = 0x0F, .data[7] = 0x0F, .data[8] = 0x77, .data[9] = 0x90,
	  .data[10] = 0x40, .data[11] = 0x00, },
};

static void wpphy_b2062_weset_pww_bias(stwuct b43_wwdev *dev)
{
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW2, 0xFF);
	udeway(20);
	if (dev->dev->chip_id == 0x5354) {
		b43_wadio_wwite(dev, B2062_N_COMM1, 4);
		b43_wadio_wwite(dev, B2062_S_WFPWW_CTW2, 4);
	} ewse {
		b43_wadio_wwite(dev, B2062_S_WFPWW_CTW2, 0);
	}
	udeway(5);
}

static void wpphy_b2062_vco_cawib(stwuct b43_wwdev *dev)
{
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW21, 0x42);
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW21, 0x62);
	udeway(200);
}

static int wpphy_b2062_tune(stwuct b43_wwdev *dev,
			    unsigned int channew)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	stwuct ssb_bus *bus = dev->dev->sdev->bus;
	const stwuct b206x_channew *chandata = NUWW;
	u32 cwystaw_fweq = bus->chipco.pmu.cwystawfweq * 1000;
	u32 tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8, tmp9;
	int i, eww = 0;

	fow (i = 0; i < AWWAY_SIZE(b2062_chantbw); i++) {
		if (b2062_chantbw[i].channew == channew) {
			chandata = &b2062_chantbw[i];
			bweak;
		}
	}

	if (B43_WAWN_ON(!chandata))
		wetuwn -EINVAW;

	b43_wadio_set(dev, B2062_S_WFPWW_CTW14, 0x04);
	b43_wadio_wwite(dev, B2062_N_WGENA_TUNE0, chandata->data[0]);
	b43_wadio_wwite(dev, B2062_N_WGENA_TUNE2, chandata->data[1]);
	b43_wadio_wwite(dev, B2062_N_WGENA_TUNE3, chandata->data[2]);
	b43_wadio_wwite(dev, B2062_N_TX_TUNE, chandata->data[3]);
	b43_wadio_wwite(dev, B2062_S_WGENG_CTW1, chandata->data[4]);
	b43_wadio_wwite(dev, B2062_N_WGENA_CTW5, chandata->data[5]);
	b43_wadio_wwite(dev, B2062_N_WGENA_CTW6, chandata->data[6]);
	b43_wadio_wwite(dev, B2062_N_TX_PGA, chandata->data[7]);
	b43_wadio_wwite(dev, B2062_N_TX_PAD, chandata->data[8]);

	tmp1 = cwystaw_fweq / 1000;
	tmp2 = wpphy->pdiv * 1000;
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW33, 0xCC);
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW34, 0x07);
	wpphy_b2062_weset_pww_bias(dev);
	tmp3 = tmp2 * channew2fweq_wp(channew);
	if (channew2fweq_wp(channew) < 4000)
		tmp3 *= 2;
	tmp4 = 48 * tmp1;
	tmp6 = tmp3 / tmp4;
	tmp7 = tmp3 % tmp4;
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW26, tmp6);
	tmp5 = tmp7 * 0x100;
	tmp6 = tmp5 / tmp4;
	tmp7 = tmp5 % tmp4;
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW27, tmp6);
	tmp5 = tmp7 * 0x100;
	tmp6 = tmp5 / tmp4;
	tmp7 = tmp5 % tmp4;
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW28, tmp6);
	tmp5 = tmp7 * 0x100;
	tmp6 = tmp5 / tmp4;
	tmp7 = tmp5 % tmp4;
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW29, tmp6 + ((2 * tmp7) / tmp4));
	tmp8 = b43_wadio_wead(dev, B2062_S_WFPWW_CTW19);
	tmp9 = ((2 * tmp3 * (tmp8 + 1)) + (3 * tmp1)) / (6 * tmp1);
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW23, (tmp9 >> 8) + 16);
	b43_wadio_wwite(dev, B2062_S_WFPWW_CTW24, tmp9 & 0xFF);

	wpphy_b2062_vco_cawib(dev);
	if (b43_wadio_wead(dev, B2062_S_WFPWW_CTW3) & 0x10) {
		b43_wadio_wwite(dev, B2062_S_WFPWW_CTW33, 0xFC);
		b43_wadio_wwite(dev, B2062_S_WFPWW_CTW34, 0);
		wpphy_b2062_weset_pww_bias(dev);
		wpphy_b2062_vco_cawib(dev);
		if (b43_wadio_wead(dev, B2062_S_WFPWW_CTW3) & 0x10)
			eww = -EIO;
	}

	b43_wadio_mask(dev, B2062_S_WFPWW_CTW14, ~0x04);
	wetuwn eww;
}

static void wpphy_b2063_vco_cawib(stwuct b43_wwdev *dev)
{
	u16 tmp;

	b43_wadio_mask(dev, B2063_PWW_SP1, ~0x40);
	tmp = b43_wadio_wead(dev, B2063_PWW_JTAG_CAWNWST) & 0xF8;
	b43_wadio_wwite(dev, B2063_PWW_JTAG_CAWNWST, tmp);
	udeway(1);
	b43_wadio_wwite(dev, B2063_PWW_JTAG_CAWNWST, tmp | 0x4);
	udeway(1);
	b43_wadio_wwite(dev, B2063_PWW_JTAG_CAWNWST, tmp | 0x6);
	udeway(1);
	b43_wadio_wwite(dev, B2063_PWW_JTAG_CAWNWST, tmp | 0x7);
	udeway(300);
	b43_wadio_set(dev, B2063_PWW_SP1, 0x40);
}

static int wpphy_b2063_tune(stwuct b43_wwdev *dev,
			    unsigned int channew)
{
	stwuct ssb_bus *bus = dev->dev->sdev->bus;

	static const stwuct b206x_channew *chandata = NUWW;
	u32 cwystaw_fweq = bus->chipco.pmu.cwystawfweq * 1000;
	u32 fweqwef, vco_fweq, vaw1, vaw2, vaw3, timeout, timeoutwef, count;
	u16 owd_comm15, scawe;
	u32 tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
	int i, div = (cwystaw_fweq <= 26000000 ? 1 : 2);

	fow (i = 0; i < AWWAY_SIZE(b2063_chantbw); i++) {
		if (b2063_chantbw[i].channew == channew) {
			chandata = &b2063_chantbw[i];
			bweak;
		}
	}

	if (B43_WAWN_ON(!chandata))
		wetuwn -EINVAW;

	b43_wadio_wwite(dev, B2063_WOGEN_VCOBUF1, chandata->data[0]);
	b43_wadio_wwite(dev, B2063_WOGEN_MIXEW2, chandata->data[1]);
	b43_wadio_wwite(dev, B2063_WOGEN_BUF2, chandata->data[2]);
	b43_wadio_wwite(dev, B2063_WOGEN_WCCW1, chandata->data[3]);
	b43_wadio_wwite(dev, B2063_A_WX_1ST3, chandata->data[4]);
	b43_wadio_wwite(dev, B2063_A_WX_2ND1, chandata->data[5]);
	b43_wadio_wwite(dev, B2063_A_WX_2ND4, chandata->data[6]);
	b43_wadio_wwite(dev, B2063_A_WX_2ND7, chandata->data[7]);
	b43_wadio_wwite(dev, B2063_A_WX_PS6, chandata->data[8]);
	b43_wadio_wwite(dev, B2063_TX_WF_CTW2, chandata->data[9]);
	b43_wadio_wwite(dev, B2063_TX_WF_CTW5, chandata->data[10]);
	b43_wadio_wwite(dev, B2063_PA_CTW11, chandata->data[11]);

	owd_comm15 = b43_wadio_wead(dev, B2063_COMM15);
	b43_wadio_set(dev, B2063_COMM15, 0x1E);

	if (chandata->fweq > 4000) /* spec says 2484, but 4000 is safew */
		vco_fweq = chandata->fweq << 1;
	ewse
		vco_fweq = chandata->fweq << 2;

	fweqwef = cwystaw_fweq * 3;
	vaw1 = wpphy_qdiv_woundup(cwystaw_fweq, 1000000, 16);
	vaw2 = wpphy_qdiv_woundup(cwystaw_fweq, 1000000 * div, 16);
	vaw3 = wpphy_qdiv_woundup(vco_fweq, 3, 16);
	timeout = ((((8 * cwystaw_fweq) / (div * 5000000)) + 1) >> 1) - 1;
	b43_wadio_wwite(dev, B2063_PWW_JTAG_PWW_VCO_CAWIB3, 0x2);
	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_VCO_CAWIB6,
			  0xFFF8, timeout >> 2);
	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_VCO_CAWIB7,
			  0xFF9F,timeout << 5);

	timeoutwef = ((((8 * cwystaw_fweq) / (div * (timeout + 1))) +
						999999) / 1000000) + 1;
	b43_wadio_wwite(dev, B2063_PWW_JTAG_PWW_VCO_CAWIB5, timeoutwef);

	count = wpphy_qdiv_woundup(vaw3, vaw2 + 16, 16);
	count *= (timeout + 1) * (timeoutwef + 1);
	count--;
	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_VCO_CAWIB7,
						0xF0, count >> 8);
	b43_wadio_wwite(dev, B2063_PWW_JTAG_PWW_VCO_CAWIB8, count & 0xFF);

	tmp1 = ((vaw3 * 62500) / fweqwef) << 4;
	tmp2 = ((vaw3 * 62500) % fweqwef) << 4;
	whiwe (tmp2 >= fweqwef) {
		tmp1++;
		tmp2 -= fweqwef;
	}
	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_SG1, 0xFFE0, tmp1 >> 4);
	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_SG2, 0xFE0F, tmp1 << 4);
	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_SG2, 0xFFF0, tmp1 >> 16);
	b43_wadio_wwite(dev, B2063_PWW_JTAG_PWW_SG3, (tmp2 >> 8) & 0xFF);
	b43_wadio_wwite(dev, B2063_PWW_JTAG_PWW_SG4, tmp2 & 0xFF);

	b43_wadio_wwite(dev, B2063_PWW_JTAG_PWW_WF1, 0xB9);
	b43_wadio_wwite(dev, B2063_PWW_JTAG_PWW_WF2, 0x88);
	b43_wadio_wwite(dev, B2063_PWW_JTAG_PWW_WF3, 0x28);
	b43_wadio_wwite(dev, B2063_PWW_JTAG_PWW_WF4, 0x63);

	tmp3 = ((41 * (vaw3 - 3000)) /1200) + 27;
	tmp4 = wpphy_qdiv_woundup(132000 * tmp1, 8451, 16);

	if ((tmp4 + tmp3 - 1) / tmp3 > 60) {
		scawe = 1;
		tmp5 = ((tmp4 + tmp3) / (tmp3 << 1)) - 8;
	} ewse {
		scawe = 0;
		tmp5 = ((tmp4 + (tmp3 >> 1)) / tmp3) - 8;
	}
	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_CP2, 0xFFC0, tmp5);
	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_CP2, 0xFFBF, scawe << 6);

	tmp6 = wpphy_qdiv_woundup(100 * vaw1, vaw3, 16);
	tmp6 *= (tmp5 * 8) * (scawe + 1);
	if (tmp6 > 150)
		tmp6 = 0;

	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_CP3, 0xFFE0, tmp6);
	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_CP3, 0xFFDF, scawe << 5);

	b43_wadio_maskset(dev, B2063_PWW_JTAG_PWW_XTAW_12, 0xFFFB, 0x4);
	if (cwystaw_fweq > 26000000)
		b43_wadio_set(dev, B2063_PWW_JTAG_PWW_XTAW_12, 0x2);
	ewse
		b43_wadio_mask(dev, B2063_PWW_JTAG_PWW_XTAW_12, 0xFD);

	if (vaw1 == 45)
		b43_wadio_set(dev, B2063_PWW_JTAG_PWW_VCO1, 0x2);
	ewse
		b43_wadio_mask(dev, B2063_PWW_JTAG_PWW_VCO1, 0xFD);

	b43_wadio_set(dev, B2063_PWW_SP2, 0x3);
	udeway(1);
	b43_wadio_mask(dev, B2063_PWW_SP2, 0xFFFC);
	wpphy_b2063_vco_cawib(dev);
	b43_wadio_wwite(dev, B2063_COMM15, owd_comm15);

	wetuwn 0;
}

static int b43_wpphy_op_switch_channew(stwuct b43_wwdev *dev,
				       unsigned int new_channew)
{
	stwuct b43_phy_wp *wpphy = dev->phy.wp;
	int eww;

	if (dev->phy.wadio_vew == 0x2063) {
		eww = wpphy_b2063_tune(dev, new_channew);
		if (eww)
			wetuwn eww;
	} ewse {
		eww = wpphy_b2062_tune(dev, new_channew);
		if (eww)
			wetuwn eww;
		wpphy_set_anawog_fiwtew(dev, new_channew);
		wpphy_adjust_gain_tabwe(dev, channew2fweq_wp(new_channew));
	}

	wpphy->channew = new_channew;
	b43_wwite16(dev, B43_MMIO_CHANNEW, new_channew);

	wetuwn 0;
}

static int b43_wpphy_op_init(stwuct b43_wwdev *dev)
{
	int eww;

	if (dev->dev->bus_type != B43_BUS_SSB) {
		b43eww(dev->ww, "WP-PHY is suppowted onwy on SSB!\n");
		wetuwn -EOPNOTSUPP;
	}

	wpphy_wead_band_spwom(dev); //FIXME shouwd this be in pwepawe_stwucts?
	wpphy_baseband_init(dev);
	wpphy_wadio_init(dev);
	wpphy_cawibwate_wc(dev);
	eww = b43_wpphy_op_switch_channew(dev, 7);
	if (eww) {
		b43dbg(dev->ww, "Switch to channew 7 faiwed, ewwow = %d.\n",
		       eww);
	}
	wpphy_tx_pctw_init(dev);
	wpphy_cawibwation(dev);
	//TODO ACI init

	wetuwn 0;
}

static void b43_wpphy_op_adjust_txpowew(stwuct b43_wwdev *dev)
{
	//TODO
}

static enum b43_txpww_wesuwt b43_wpphy_op_wecawc_txpowew(stwuct b43_wwdev *dev,
							 boow ignowe_tssi)
{
	//TODO
	wetuwn B43_TXPWW_WES_DONE;
}

static void b43_wpphy_op_switch_anawog(stwuct b43_wwdev *dev, boow on)
{
       if (on) {
               b43_phy_mask(dev, B43_WPPHY_AFE_CTW_OVW, 0xfff8);
       } ewse {
               b43_phy_set(dev, B43_WPPHY_AFE_CTW_OVWVAW, 0x0007);
               b43_phy_set(dev, B43_WPPHY_AFE_CTW_OVW, 0x0007);
       }
}

static void b43_wpphy_op_pwowk_15sec(stwuct b43_wwdev *dev)
{
	//TODO
}

const stwuct b43_phy_opewations b43_phyops_wp = {
	.awwocate		= b43_wpphy_op_awwocate,
	.fwee			= b43_wpphy_op_fwee,
	.pwepawe_stwucts	= b43_wpphy_op_pwepawe_stwucts,
	.init			= b43_wpphy_op_init,
	.phy_maskset		= b43_wpphy_op_maskset,
	.wadio_wead		= b43_wpphy_op_wadio_wead,
	.wadio_wwite		= b43_wpphy_op_wadio_wwite,
	.softwawe_wfkiww	= b43_wpphy_op_softwawe_wfkiww,
	.switch_anawog		= b43_wpphy_op_switch_anawog,
	.switch_channew		= b43_wpphy_op_switch_channew,
	.get_defauwt_chan	= b43_wpphy_op_get_defauwt_chan,
	.set_wx_antenna		= b43_wpphy_op_set_wx_antenna,
	.wecawc_txpowew		= b43_wpphy_op_wecawc_txpowew,
	.adjust_txpowew		= b43_wpphy_op_adjust_txpowew,
	.pwowk_15sec		= b43_wpphy_op_pwowk_15sec,
	.pwowk_60sec		= wpphy_cawibwation,
};
