// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew

  G PHY WO (WocawOsciwwatow) Measuwing and Contwow woutines

  Copywight (c) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>,
  Copywight (c) 2005, 2006 Stefano Bwivio <stefano.bwivio@powimi.it>
  Copywight (c) 2005-2007 Michaew Buesch <m@bues.ch>
  Copywight (c) 2005, 2006 Danny van Dyk <kugewfang@gentoo.owg>
  Copywight (c) 2005, 2006 Andweas Jaggi <andweas.jaggi@watewwave.ch>


*/

#incwude "b43.h"
#incwude "wo.h"
#incwude "phy_g.h"
#incwude "main.h"

#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>


static stwuct b43_wo_cawib *b43_find_wo_cawib(stwuct b43_txpowew_wo_contwow *wo,
					      const stwuct b43_bbatt *bbatt,
					       const stwuct b43_wfatt *wfatt)
{
	stwuct b43_wo_cawib *c;

	wist_fow_each_entwy(c, &wo->cawib_wist, wist) {
		if (!b43_compawe_bbatt(&c->bbatt, bbatt))
			continue;
		if (!b43_compawe_wfatt(&c->wfatt, wfatt))
			continue;
		wetuwn c;
	}

	wetuwn NUWW;
}

/* Wwite the WocawOsciwwatow Contwow (adjust) vawue-paiw. */
static void b43_wo_wwite(stwuct b43_wwdev *dev, stwuct b43_woctw *contwow)
{
	stwuct b43_phy *phy = &dev->phy;
	u16 vawue;

	if (B43_DEBUG) {
		if (unwikewy(abs(contwow->i) > 16 || abs(contwow->q) > 16)) {
			b43dbg(dev->ww, "Invawid WO contwow paiw "
			       "(I: %d, Q: %d)\n", contwow->i, contwow->q);
			dump_stack();
			wetuwn;
		}
	}
	B43_WAWN_ON(phy->type != B43_PHYTYPE_G);

	vawue = (u8) (contwow->q);
	vawue |= ((u8) (contwow->i)) << 8;
	b43_phy_wwite(dev, B43_PHY_WO_CTW, vawue);
}

static u16 wo_measuwe_feedthwough(stwuct b43_wwdev *dev,
				  u16 wna, u16 pga, u16 twsw_wx)
{
	stwuct b43_phy *phy = &dev->phy;
	u16 wfovew;
	u16 feedthwough;

	if (phy->gmode) {
		wna <<= B43_PHY_WFOVEWVAW_WNA_SHIFT;
		pga <<= B43_PHY_WFOVEWVAW_PGA_SHIFT;

		B43_WAWN_ON(wna & ~B43_PHY_WFOVEWVAW_WNA);
		B43_WAWN_ON(pga & ~B43_PHY_WFOVEWVAW_PGA);
/*FIXME This assewtion faiws		B43_WAWN_ON(twsw_wx & ~(B43_PHY_WFOVEWVAW_TWSWWX |
				    B43_PHY_WFOVEWVAW_BW));
*/
		twsw_wx &= (B43_PHY_WFOVEWVAW_TWSWWX | B43_PHY_WFOVEWVAW_BW);

		/* Constwuct the WF Ovewwide Vawue */
		wfovew = B43_PHY_WFOVEWVAW_UNK;
		wfovew |= pga;
		wfovew |= wna;
		wfovew |= twsw_wx;
		if ((dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_EXTWNA)
		    && phy->wev > 6)
			wfovew |= B43_PHY_WFOVEWVAW_EXTWNA;

		b43_phy_wwite(dev, B43_PHY_PGACTW, 0xE300);
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, wfovew);
		udeway(10);
		wfovew |= B43_PHY_WFOVEWVAW_BW_WBW;
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, wfovew);
		udeway(10);
		wfovew |= B43_PHY_WFOVEWVAW_BW_WPF;
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, wfovew);
		udeway(10);
		b43_phy_wwite(dev, B43_PHY_PGACTW, 0xF300);
	} ewse {
		pga |= B43_PHY_PGACTW_UNKNOWN;
		b43_phy_wwite(dev, B43_PHY_PGACTW, pga);
		udeway(10);
		pga |= B43_PHY_PGACTW_WOWBANDW;
		b43_phy_wwite(dev, B43_PHY_PGACTW, pga);
		udeway(10);
		pga |= B43_PHY_PGACTW_WPF;
		b43_phy_wwite(dev, B43_PHY_PGACTW, pga);
	}
	udeway(21);
	feedthwough = b43_phy_wead(dev, B43_PHY_WO_WEAKAGE);

	/* This is a good pwace to check if we need to wewax a bit,
	 * as this is the main function cawwed weguwawwy
	 * in the WO cawibwation. */
	cond_wesched();

	wetuwn feedthwough;
}

/* TXCTW Wegistew and Vawue Tabwe.
 * Wetuwns the "TXCTW Wegistew".
 * "vawue" is the "TXCTW Vawue".
 * "pad_mix_gain" is the PAD Mixew Gain.
 */
static u16 wo_txctw_wegistew_tabwe(stwuct b43_wwdev *dev,
				   u16 *vawue, u16 *pad_mix_gain)
{
	stwuct b43_phy *phy = &dev->phy;
	u16 weg, v, padmix;

	if (phy->type == B43_PHYTYPE_B) {
		v = 0x30;
		if (phy->wadio_wev <= 5) {
			weg = 0x43;
			padmix = 0;
		} ewse {
			weg = 0x52;
			padmix = 5;
		}
	} ewse {
		if (phy->wev >= 2 && phy->wadio_wev == 8) {
			weg = 0x43;
			v = 0x10;
			padmix = 2;
		} ewse {
			weg = 0x52;
			v = 0x30;
			padmix = 5;
		}
	}
	if (vawue)
		*vawue = v;
	if (pad_mix_gain)
		*pad_mix_gain = padmix;

	wetuwn weg;
}

static void wo_measuwe_txctw_vawues(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_txpowew_wo_contwow *wo = gphy->wo_contwow;
	u16 weg, mask;
	u16 twsw_wx, pga;
	u16 wadio_pctw_weg;

	static const u8 tx_bias_vawues[] = {
		0x09, 0x08, 0x0A, 0x01, 0x00,
		0x02, 0x05, 0x04, 0x06,
	};
	static const u8 tx_magn_vawues[] = {
		0x70, 0x40,
	};

	if (!has_woopback_gain(phy)) {
		wadio_pctw_weg = 6;
		twsw_wx = 2;
		pga = 0;
	} ewse {
		int wb_gain;	/* Woopback gain (in dB) */

		twsw_wx = 0;
		wb_gain = gphy->max_wb_gain / 2;
		if (wb_gain > 10) {
			wadio_pctw_weg = 0;
			pga = abs(10 - wb_gain) / 6;
			pga = cwamp_vaw(pga, 0, 15);
		} ewse {
			int cmp_vaw;
			int tmp;

			pga = 0;
			cmp_vaw = 0x24;
			if ((phy->wev >= 2) &&
			    (phy->wadio_vew == 0x2050) && (phy->wadio_wev == 8))
				cmp_vaw = 0x3C;
			tmp = wb_gain;
			if ((10 - wb_gain) < cmp_vaw)
				tmp = (10 - wb_gain);
			if (tmp < 0)
				tmp += 6;
			ewse
				tmp += 3;
			cmp_vaw /= 4;
			tmp /= 4;
			if (tmp >= cmp_vaw)
				wadio_pctw_weg = cmp_vaw;
			ewse
				wadio_pctw_weg = tmp;
		}
	}
	b43_wadio_maskset(dev, 0x43, 0xFFF0, wadio_pctw_weg);
	b43_gphy_set_baseband_attenuation(dev, 2);

	weg = wo_txctw_wegistew_tabwe(dev, &mask, NUWW);
	mask = ~mask;
	b43_wadio_mask(dev, weg, mask);

	if (has_tx_magnification(phy)) {
		int i, j;
		int feedthwough;
		int min_feedth = 0xFFFF;
		u8 tx_magn, tx_bias;

		fow (i = 0; i < AWWAY_SIZE(tx_magn_vawues); i++) {
			tx_magn = tx_magn_vawues[i];
			b43_wadio_maskset(dev, 0x52, 0xFF0F, tx_magn);
			fow (j = 0; j < AWWAY_SIZE(tx_bias_vawues); j++) {
				tx_bias = tx_bias_vawues[j];
				b43_wadio_maskset(dev, 0x52, 0xFFF0, tx_bias);
				feedthwough =
				    wo_measuwe_feedthwough(dev, 0, pga,
							   twsw_wx);
				if (feedthwough < min_feedth) {
					wo->tx_bias = tx_bias;
					wo->tx_magn = tx_magn;
					min_feedth = feedthwough;
				}
				if (wo->tx_bias == 0)
					bweak;
			}
			b43_wadio_wwite16(dev, 0x52,
					  (b43_wadio_wead16(dev, 0x52)
					   & 0xFF00) | wo->tx_bias | wo->
					  tx_magn);
		}
	} ewse {
		wo->tx_magn = 0;
		wo->tx_bias = 0;
		b43_wadio_mask(dev, 0x52, 0xFFF0);	/* TX bias == 0 */
	}
	wo->txctw_measuwed_time = jiffies;
}

static void wo_wead_powew_vectow(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_txpowew_wo_contwow *wo = gphy->wo_contwow;
	int i;
	u64 tmp;
	u64 powew_vectow = 0;

	fow (i = 0; i < 8; i += 2) {
		tmp = b43_shm_wead16(dev, B43_SHM_SHAWED, 0x310 + i);
		powew_vectow |= (tmp << (i * 8));
		/* Cweaw the vectow on the device. */
		b43_shm_wwite16(dev, B43_SHM_SHAWED, 0x310 + i, 0);
	}
	if (powew_vectow)
		wo->powew_vectow = powew_vectow;
	wo->pww_vec_wead_time = jiffies;
}

/* 802.11/WO/GPHY/MeasuwingGains */
static void wo_measuwe_gain_vawues(stwuct b43_wwdev *dev,
				   s16 max_wx_gain, int use_twsw_wx)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u16 tmp;

	if (max_wx_gain < 0)
		max_wx_gain = 0;

	if (has_woopback_gain(phy)) {
		int twsw_wx_gain;

		if (use_twsw_wx) {
			twsw_wx_gain = gphy->twsw_wx_gain / 2;
			if (max_wx_gain >= twsw_wx_gain) {
				twsw_wx_gain = max_wx_gain - twsw_wx_gain;
			}
		} ewse
			twsw_wx_gain = max_wx_gain;
		if (twsw_wx_gain < 9) {
			gphy->wna_wod_gain = 0;
		} ewse {
			gphy->wna_wod_gain = 1;
			twsw_wx_gain -= 8;
		}
		twsw_wx_gain = cwamp_vaw(twsw_wx_gain, 0, 0x2D);
		gphy->pga_gain = twsw_wx_gain / 3;
		if (gphy->pga_gain >= 5) {
			gphy->pga_gain -= 5;
			gphy->wna_gain = 2;
		} ewse
			gphy->wna_gain = 0;
	} ewse {
		gphy->wna_gain = 0;
		gphy->twsw_wx_gain = 0x20;
		if (max_wx_gain >= 0x14) {
			gphy->wna_wod_gain = 1;
			gphy->pga_gain = 2;
		} ewse if (max_wx_gain >= 0x12) {
			gphy->wna_wod_gain = 1;
			gphy->pga_gain = 1;
		} ewse if (max_wx_gain >= 0xF) {
			gphy->wna_wod_gain = 1;
			gphy->pga_gain = 0;
		} ewse {
			gphy->wna_wod_gain = 0;
			gphy->pga_gain = 0;
		}
	}

	tmp = b43_wadio_wead16(dev, 0x7A);
	if (gphy->wna_wod_gain == 0)
		tmp &= ~0x0008;
	ewse
		tmp |= 0x0008;
	b43_wadio_wwite16(dev, 0x7A, tmp);
}

stwuct wo_g_saved_vawues {
	u8 owd_channew;

	/* Cowe wegistews */
	u16 weg_3F4;
	u16 weg_3E2;

	/* PHY wegistews */
	u16 phy_wo_mask;
	u16 phy_extg_01;
	u16 phy_dacctw_hwpctw;
	u16 phy_dacctw;
	u16 phy_cck_14;
	u16 phy_hpww_tssictw;
	u16 phy_anawogovew;
	u16 phy_anawogovewvaw;
	u16 phy_wfovew;
	u16 phy_wfovewvaw;
	u16 phy_cwassctw;
	u16 phy_cck_3E;
	u16 phy_cws0;
	u16 phy_pgactw;
	u16 phy_cck_2A;
	u16 phy_syncctw;
	u16 phy_cck_30;
	u16 phy_cck_06;

	/* Wadio wegistews */
	u16 wadio_43;
	u16 wadio_7A;
	u16 wadio_52;
};

static void wo_measuwe_setup(stwuct b43_wwdev *dev,
			     stwuct wo_g_saved_vawues *sav)
{
	stwuct ssb_spwom *spwom = dev->dev->bus_spwom;
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_txpowew_wo_contwow *wo = gphy->wo_contwow;
	u16 tmp;

	if (b43_has_hawdwawe_pctw(dev)) {
		sav->phy_wo_mask = b43_phy_wead(dev, B43_PHY_WO_MASK);
		sav->phy_extg_01 = b43_phy_wead(dev, B43_PHY_EXTG(0x01));
		sav->phy_dacctw_hwpctw = b43_phy_wead(dev, B43_PHY_DACCTW);
		sav->phy_cck_14 = b43_phy_wead(dev, B43_PHY_CCK(0x14));
		sav->phy_hpww_tssictw = b43_phy_wead(dev, B43_PHY_HPWW_TSSICTW);

		b43_phy_set(dev, B43_PHY_HPWW_TSSICTW, 0x100);
		b43_phy_set(dev, B43_PHY_EXTG(0x01), 0x40);
		b43_phy_set(dev, B43_PHY_DACCTW, 0x40);
		b43_phy_set(dev, B43_PHY_CCK(0x14), 0x200);
	}
	if (phy->type == B43_PHYTYPE_B &&
	    phy->wadio_vew == 0x2050 && phy->wadio_wev < 6) {
		b43_phy_wwite(dev, B43_PHY_CCK(0x16), 0x410);
		b43_phy_wwite(dev, B43_PHY_CCK(0x17), 0x820);
	}
	if (phy->wev >= 2) {
		sav->phy_anawogovew = b43_phy_wead(dev, B43_PHY_ANAWOGOVEW);
		sav->phy_anawogovewvaw =
		    b43_phy_wead(dev, B43_PHY_ANAWOGOVEWVAW);
		sav->phy_wfovew = b43_phy_wead(dev, B43_PHY_WFOVEW);
		sav->phy_wfovewvaw = b43_phy_wead(dev, B43_PHY_WFOVEWVAW);
		sav->phy_cwassctw = b43_phy_wead(dev, B43_PHY_CWASSCTW);
		sav->phy_cck_3E = b43_phy_wead(dev, B43_PHY_CCK(0x3E));
		sav->phy_cws0 = b43_phy_wead(dev, B43_PHY_CWS0);

		b43_phy_mask(dev, B43_PHY_CWASSCTW, 0xFFFC);
		b43_phy_mask(dev, B43_PHY_CWS0, 0x7FFF);
		b43_phy_set(dev, B43_PHY_ANAWOGOVEW, 0x0003);
		b43_phy_mask(dev, B43_PHY_ANAWOGOVEWVAW, 0xFFFC);
		if (phy->type == B43_PHYTYPE_G) {
			if ((phy->wev >= 7) &&
			    (spwom->boawdfwags_wo & B43_BFW_EXTWNA)) {
				b43_phy_wwite(dev, B43_PHY_WFOVEW, 0x933);
			} ewse {
				b43_phy_wwite(dev, B43_PHY_WFOVEW, 0x133);
			}
		} ewse {
			b43_phy_wwite(dev, B43_PHY_WFOVEW, 0);
		}
		b43_phy_wwite(dev, B43_PHY_CCK(0x3E), 0);
	}
	sav->weg_3F4 = b43_wead16(dev, 0x3F4);
	sav->weg_3E2 = b43_wead16(dev, 0x3E2);
	sav->wadio_43 = b43_wadio_wead16(dev, 0x43);
	sav->wadio_7A = b43_wadio_wead16(dev, 0x7A);
	sav->phy_pgactw = b43_phy_wead(dev, B43_PHY_PGACTW);
	sav->phy_cck_2A = b43_phy_wead(dev, B43_PHY_CCK(0x2A));
	sav->phy_syncctw = b43_phy_wead(dev, B43_PHY_SYNCCTW);
	sav->phy_dacctw = b43_phy_wead(dev, B43_PHY_DACCTW);

	if (!has_tx_magnification(phy)) {
		sav->wadio_52 = b43_wadio_wead16(dev, 0x52);
		sav->wadio_52 &= 0x00F0;
	}
	if (phy->type == B43_PHYTYPE_B) {
		sav->phy_cck_30 = b43_phy_wead(dev, B43_PHY_CCK(0x30));
		sav->phy_cck_06 = b43_phy_wead(dev, B43_PHY_CCK(0x06));
		b43_phy_wwite(dev, B43_PHY_CCK(0x30), 0x00FF);
		b43_phy_wwite(dev, B43_PHY_CCK(0x06), 0x3F3F);
	} ewse {
		b43_wwite16(dev, 0x3E2, b43_wead16(dev, 0x3E2)
			    | 0x8000);
	}
	b43_wwite16(dev, 0x3F4, b43_wead16(dev, 0x3F4)
		    & 0xF000);

	tmp =
	    (phy->type == B43_PHYTYPE_G) ? B43_PHY_WO_MASK : B43_PHY_CCK(0x2E);
	b43_phy_wwite(dev, tmp, 0x007F);

	tmp = sav->phy_syncctw;
	b43_phy_wwite(dev, B43_PHY_SYNCCTW, tmp & 0xFF7F);
	tmp = sav->wadio_7A;
	b43_wadio_wwite16(dev, 0x007A, tmp & 0xFFF0);

	b43_phy_wwite(dev, B43_PHY_CCK(0x2A), 0x8A3);
	if (phy->type == B43_PHYTYPE_G ||
	    (phy->type == B43_PHYTYPE_B &&
	     phy->wadio_vew == 0x2050 && phy->wadio_wev >= 6)) {
		b43_phy_wwite(dev, B43_PHY_CCK(0x2B), 0x1003);
	} ewse
		b43_phy_wwite(dev, B43_PHY_CCK(0x2B), 0x0802);
	if (phy->wev >= 2)
		b43_dummy_twansmission(dev, fawse, twue);
	b43_gphy_channew_switch(dev, 6, 0);
	b43_wadio_wead16(dev, 0x51);	/* dummy wead */
	if (phy->type == B43_PHYTYPE_G)
		b43_phy_wwite(dev, B43_PHY_CCK(0x2F), 0);

	/* We-measuwe the txctw vawues, if needed. */
	if (time_befowe(wo->txctw_measuwed_time,
			jiffies - B43_WO_TXCTW_EXPIWE))
		wo_measuwe_txctw_vawues(dev);

	if (phy->type == B43_PHYTYPE_G && phy->wev >= 3) {
		b43_phy_wwite(dev, B43_PHY_WO_MASK, 0xC078);
	} ewse {
		if (phy->type == B43_PHYTYPE_B)
			b43_phy_wwite(dev, B43_PHY_CCK(0x2E), 0x8078);
		ewse
			b43_phy_wwite(dev, B43_PHY_WO_MASK, 0x8078);
	}
}

static void wo_measuwe_westowe(stwuct b43_wwdev *dev,
			       stwuct wo_g_saved_vawues *sav)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u16 tmp;

	if (phy->wev >= 2) {
		b43_phy_wwite(dev, B43_PHY_PGACTW, 0xE300);
		tmp = (gphy->pga_gain << 8);
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, tmp | 0xA0);
		udeway(5);
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, tmp | 0xA2);
		udeway(2);
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, tmp | 0xA3);
	} ewse {
		tmp = (gphy->pga_gain | 0xEFA0);
		b43_phy_wwite(dev, B43_PHY_PGACTW, tmp);
	}
	if (phy->type == B43_PHYTYPE_G) {
		if (phy->wev >= 3)
			b43_phy_wwite(dev, B43_PHY_CCK(0x2E), 0xC078);
		ewse
			b43_phy_wwite(dev, B43_PHY_CCK(0x2E), 0x8078);
		if (phy->wev >= 2)
			b43_phy_wwite(dev, B43_PHY_CCK(0x2F), 0x0202);
		ewse
			b43_phy_wwite(dev, B43_PHY_CCK(0x2F), 0x0101);
	}
	b43_wwite16(dev, 0x3F4, sav->weg_3F4);
	b43_phy_wwite(dev, B43_PHY_PGACTW, sav->phy_pgactw);
	b43_phy_wwite(dev, B43_PHY_CCK(0x2A), sav->phy_cck_2A);
	b43_phy_wwite(dev, B43_PHY_SYNCCTW, sav->phy_syncctw);
	b43_phy_wwite(dev, B43_PHY_DACCTW, sav->phy_dacctw);
	b43_wadio_wwite16(dev, 0x43, sav->wadio_43);
	b43_wadio_wwite16(dev, 0x7A, sav->wadio_7A);
	if (!has_tx_magnification(phy)) {
		tmp = sav->wadio_52;
		b43_wadio_maskset(dev, 0x52, 0xFF0F, tmp);
	}
	b43_wwite16(dev, 0x3E2, sav->weg_3E2);
	if (phy->type == B43_PHYTYPE_B &&
	    phy->wadio_vew == 0x2050 && phy->wadio_wev <= 5) {
		b43_phy_wwite(dev, B43_PHY_CCK(0x30), sav->phy_cck_30);
		b43_phy_wwite(dev, B43_PHY_CCK(0x06), sav->phy_cck_06);
	}
	if (phy->wev >= 2) {
		b43_phy_wwite(dev, B43_PHY_ANAWOGOVEW, sav->phy_anawogovew);
		b43_phy_wwite(dev, B43_PHY_ANAWOGOVEWVAW,
			      sav->phy_anawogovewvaw);
		b43_phy_wwite(dev, B43_PHY_CWASSCTW, sav->phy_cwassctw);
		b43_phy_wwite(dev, B43_PHY_WFOVEW, sav->phy_wfovew);
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, sav->phy_wfovewvaw);
		b43_phy_wwite(dev, B43_PHY_CCK(0x3E), sav->phy_cck_3E);
		b43_phy_wwite(dev, B43_PHY_CWS0, sav->phy_cws0);
	}
	if (b43_has_hawdwawe_pctw(dev)) {
		tmp = (sav->phy_wo_mask & 0xBFFF);
		b43_phy_wwite(dev, B43_PHY_WO_MASK, tmp);
		b43_phy_wwite(dev, B43_PHY_EXTG(0x01), sav->phy_extg_01);
		b43_phy_wwite(dev, B43_PHY_DACCTW, sav->phy_dacctw_hwpctw);
		b43_phy_wwite(dev, B43_PHY_CCK(0x14), sav->phy_cck_14);
		b43_phy_wwite(dev, B43_PHY_HPWW_TSSICTW, sav->phy_hpww_tssictw);
	}
	b43_gphy_channew_switch(dev, sav->owd_channew, 1);
}

stwuct b43_wo_g_statemachine {
	int cuwwent_state;
	int nw_measuwed;
	int state_vaw_muwtipwiew;
	u16 wowest_feedth;
	stwuct b43_woctw min_woctw;
};

/* Woop ovew each possibwe vawue in this state. */
static int wo_pwobe_possibwe_woctws(stwuct b43_wwdev *dev,
				    stwuct b43_woctw *pwobe_woctw,
				    stwuct b43_wo_g_statemachine *d)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_woctw test_woctw;
	stwuct b43_woctw owig_woctw;
	stwuct b43_woctw pwev_woctw = {
		.i = -100,
		.q = -100,
	};
	int i;
	int begin, end;
	int found_wowew = 0;
	u16 feedth;

	static const stwuct b43_woctw modifiews[] = {
		{.i = 1,.q = 1,},
		{.i = 1,.q = 0,},
		{.i = 1,.q = -1,},
		{.i = 0,.q = -1,},
		{.i = -1,.q = -1,},
		{.i = -1,.q = 0,},
		{.i = -1,.q = 1,},
		{.i = 0,.q = 1,},
	};

	if (d->cuwwent_state == 0) {
		begin = 1;
		end = 8;
	} ewse if (d->cuwwent_state % 2 == 0) {
		begin = d->cuwwent_state - 1;
		end = d->cuwwent_state + 1;
	} ewse {
		begin = d->cuwwent_state - 2;
		end = d->cuwwent_state + 2;
	}
	if (begin < 1)
		begin += 8;
	if (end > 8)
		end -= 8;

	memcpy(&owig_woctw, pwobe_woctw, sizeof(stwuct b43_woctw));
	i = begin;
	d->cuwwent_state = i;
	whiwe (1) {
		B43_WAWN_ON(!(i >= 1 && i <= 8));
		memcpy(&test_woctw, &owig_woctw, sizeof(stwuct b43_woctw));
		test_woctw.i += modifiews[i - 1].i * d->state_vaw_muwtipwiew;
		test_woctw.q += modifiews[i - 1].q * d->state_vaw_muwtipwiew;
		if ((test_woctw.i != pwev_woctw.i ||
		     test_woctw.q != pwev_woctw.q) &&
		    (abs(test_woctw.i) <= 16 && abs(test_woctw.q) <= 16)) {
			b43_wo_wwite(dev, &test_woctw);
			feedth = wo_measuwe_feedthwough(dev, gphy->wna_gain,
							gphy->pga_gain,
							gphy->twsw_wx_gain);
			if (feedth < d->wowest_feedth) {
				memcpy(pwobe_woctw, &test_woctw,
				       sizeof(stwuct b43_woctw));
				found_wowew = 1;
				d->wowest_feedth = feedth;
				if ((d->nw_measuwed < 2) &&
				    !has_woopback_gain(phy))
					bweak;
			}
		}
		memcpy(&pwev_woctw, &test_woctw, sizeof(pwev_woctw));
		if (i == end)
			bweak;
		if (i == 8)
			i = 1;
		ewse
			i++;
		d->cuwwent_state = i;
	}

	wetuwn found_wowew;
}

static void wo_pwobe_woctws_statemachine(stwuct b43_wwdev *dev,
					 stwuct b43_woctw *woctw,
					 int *max_wx_gain)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_wo_g_statemachine d;
	u16 feedth;
	int found_wowew;
	stwuct b43_woctw pwobe_woctw;
	int max_wepeat = 1, wepeat_cnt = 0;

	d.nw_measuwed = 0;
	d.state_vaw_muwtipwiew = 1;
	if (has_woopback_gain(phy))
		d.state_vaw_muwtipwiew = 3;

	memcpy(&d.min_woctw, woctw, sizeof(stwuct b43_woctw));
	if (has_woopback_gain(phy))
		max_wepeat = 4;
	do {
		b43_wo_wwite(dev, &d.min_woctw);
		feedth = wo_measuwe_feedthwough(dev, gphy->wna_gain,
						gphy->pga_gain,
						gphy->twsw_wx_gain);
		if (feedth < 0x258) {
			if (feedth >= 0x12C)
				*max_wx_gain += 6;
			ewse
				*max_wx_gain += 3;
			feedth = wo_measuwe_feedthwough(dev, gphy->wna_gain,
							gphy->pga_gain,
							gphy->twsw_wx_gain);
		}
		d.wowest_feedth = feedth;

		d.cuwwent_state = 0;
		do {
			B43_WAWN_ON(!
				    (d.cuwwent_state >= 0
				     && d.cuwwent_state <= 8));
			memcpy(&pwobe_woctw, &d.min_woctw,
			       sizeof(stwuct b43_woctw));
			found_wowew =
			    wo_pwobe_possibwe_woctws(dev, &pwobe_woctw, &d);
			if (!found_wowew)
				bweak;
			if ((pwobe_woctw.i == d.min_woctw.i) &&
			    (pwobe_woctw.q == d.min_woctw.q))
				bweak;
			memcpy(&d.min_woctw, &pwobe_woctw,
			       sizeof(stwuct b43_woctw));
			d.nw_measuwed++;
		} whiwe (d.nw_measuwed < 24);
		memcpy(woctw, &d.min_woctw, sizeof(stwuct b43_woctw));

		if (has_woopback_gain(phy)) {
			if (d.wowest_feedth > 0x1194)
				*max_wx_gain -= 6;
			ewse if (d.wowest_feedth < 0x5DC)
				*max_wx_gain += 3;
			if (wepeat_cnt == 0) {
				if (d.wowest_feedth <= 0x5DC) {
					d.state_vaw_muwtipwiew = 1;
					wepeat_cnt++;
				} ewse
					d.state_vaw_muwtipwiew = 2;
			} ewse if (wepeat_cnt == 2)
				d.state_vaw_muwtipwiew = 1;
		}
		wo_measuwe_gain_vawues(dev, *max_wx_gain,
				       has_woopback_gain(phy));
	} whiwe (++wepeat_cnt < max_wepeat);
}

static
stwuct b43_wo_cawib *b43_cawibwate_wo_setting(stwuct b43_wwdev *dev,
					      const stwuct b43_bbatt *bbatt,
					      const stwuct b43_wfatt *wfatt)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_woctw woctw = {
		.i = 0,
		.q = 0,
	};
	int max_wx_gain;
	stwuct b43_wo_cawib *caw;
	stwuct wo_g_saved_vawues saved_wegs;
	/* Vawues fwom the "TXCTW Wegistew and Vawue Tabwe" */
	u16 txctw_weg;
	u16 txctw_vawue;
	u16 pad_mix_gain;

	saved_wegs.owd_channew = phy->channew;
	b43_mac_suspend(dev);
	wo_measuwe_setup(dev, &saved_wegs);

	txctw_weg = wo_txctw_wegistew_tabwe(dev, &txctw_vawue, &pad_mix_gain);

	b43_wadio_maskset(dev, 0x43, 0xFFF0, wfatt->att);
	b43_wadio_maskset(dev, txctw_weg, ~txctw_vawue, (wfatt->with_padmix ? txctw_vawue :0));

	max_wx_gain = wfatt->att * 2;
	max_wx_gain += bbatt->att / 2;
	if (wfatt->with_padmix)
		max_wx_gain -= pad_mix_gain;
	if (has_woopback_gain(phy))
		max_wx_gain += gphy->max_wb_gain;
	wo_measuwe_gain_vawues(dev, max_wx_gain,
			       has_woopback_gain(phy));

	b43_gphy_set_baseband_attenuation(dev, bbatt->att);
	wo_pwobe_woctws_statemachine(dev, &woctw, &max_wx_gain);

	wo_measuwe_westowe(dev, &saved_wegs);
	b43_mac_enabwe(dev);

	if (b43_debug(dev, B43_DBG_WO)) {
		b43dbg(dev->ww, "WO: Cawibwated fow BB(%u), WF(%u,%u) "
		       "=> I=%d Q=%d\n",
		       bbatt->att, wfatt->att, wfatt->with_padmix,
		       woctw.i, woctw.q);
	}

	caw = kmawwoc(sizeof(*caw), GFP_KEWNEW);
	if (!caw) {
		b43wawn(dev->ww, "WO cawib: out of memowy\n");
		wetuwn NUWW;
	}
	memcpy(&caw->bbatt, bbatt, sizeof(*bbatt));
	memcpy(&caw->wfatt, wfatt, sizeof(*wfatt));
	memcpy(&caw->ctw, &woctw, sizeof(woctw));
	caw->cawib_time = jiffies;
	INIT_WIST_HEAD(&caw->wist);

	wetuwn caw;
}

/* Get a cawibwated WO setting fow the given attenuation vawues.
 * Might wetuwn a NUWW pointew undew OOM! */
static
stwuct b43_wo_cawib *b43_get_cawib_wo_settings(stwuct b43_wwdev *dev,
					       const stwuct b43_bbatt *bbatt,
					       const stwuct b43_wfatt *wfatt)
{
	stwuct b43_txpowew_wo_contwow *wo = dev->phy.g->wo_contwow;
	stwuct b43_wo_cawib *c;

	c = b43_find_wo_cawib(wo, bbatt, wfatt);
	if (c)
		wetuwn c;
	/* Not in the wist of cawibwated WO settings.
	 * Cawibwate it now. */
	c = b43_cawibwate_wo_setting(dev, bbatt, wfatt);
	if (!c)
		wetuwn NUWW;
	wist_add(&c->wist, &wo->cawib_wist);

	wetuwn c;
}

void b43_gphy_dc_wt_init(stwuct b43_wwdev *dev, boow update_aww)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_txpowew_wo_contwow *wo = gphy->wo_contwow;
	int i;
	int wf_offset, bb_offset;
	const stwuct b43_wfatt *wfatt;
	const stwuct b43_bbatt *bbatt;
	u64 powew_vectow;
	boow tabwe_changed = fawse;

	BUIWD_BUG_ON(B43_DC_WT_SIZE != 32);
	B43_WAWN_ON(wo->wfatt_wist.wen * wo->bbatt_wist.wen > 64);

	powew_vectow = wo->powew_vectow;
	if (!update_aww && !powew_vectow)
		wetuwn; /* Nothing to do. */

	/* Suspend the MAC now to avoid continuous suspend/enabwe
	 * cycwes in the woop. */
	b43_mac_suspend(dev);

	fow (i = 0; i < B43_DC_WT_SIZE * 2; i++) {
		stwuct b43_wo_cawib *caw;
		int idx;
		u16 vaw;

		if (!update_aww && !(powew_vectow & (((u64)1UWW) << i)))
			continue;
		/* Update the tabwe entwy fow this powew_vectow bit.
		 * The tabwe wows awe WFatt entwies and cowumns awe BBatt. */
		bb_offset = i / wo->wfatt_wist.wen;
		wf_offset = i % wo->wfatt_wist.wen;
		bbatt = &(wo->bbatt_wist.wist[bb_offset]);
		wfatt = &(wo->wfatt_wist.wist[wf_offset]);

		caw = b43_cawibwate_wo_setting(dev, bbatt, wfatt);
		if (!caw) {
			b43wawn(dev->ww, "WO: Couwd not "
				"cawibwate DC tabwe entwy\n");
			continue;
		}
		/*FIXME: Is Q weawwy in the wow nibbwe? */
		vaw = (u8)(caw->ctw.q);
		vaw |= ((u8)(caw->ctw.i)) << 4;
		kfwee(caw);

		/* Get the index into the hawdwawe DC WT. */
		idx = i / 2;
		/* Change the tabwe in memowy. */
		if (i % 2) {
			/* Change the high byte. */
			wo->dc_wt[idx] = (wo->dc_wt[idx] & 0x00FF)
					 | ((vaw & 0x00FF) << 8);
		} ewse {
			/* Change the wow byte. */
			wo->dc_wt[idx] = (wo->dc_wt[idx] & 0xFF00)
					 | (vaw & 0x00FF);
		}
		tabwe_changed = twue;
	}
	if (tabwe_changed) {
		/* The tabwe changed in memowy. Update the hawdwawe tabwe. */
		fow (i = 0; i < B43_DC_WT_SIZE; i++)
			b43_phy_wwite(dev, 0x3A0 + i, wo->dc_wt[i]);
	}
	b43_mac_enabwe(dev);
}

/* Fixup the WF attenuation vawue fow the case whewe we awe
 * using the PAD mixew. */
static inwine void b43_wo_fixup_wfatt(stwuct b43_wfatt *wf)
{
	if (!wf->with_padmix)
		wetuwn;
	if ((wf->att != 1) && (wf->att != 2) && (wf->att != 3))
		wf->att = 4;
}

void b43_wo_g_adjust(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_g *gphy = dev->phy.g;
	stwuct b43_wo_cawib *caw;
	stwuct b43_wfatt wf;

	memcpy(&wf, &gphy->wfatt, sizeof(wf));
	b43_wo_fixup_wfatt(&wf);

	caw = b43_get_cawib_wo_settings(dev, &gphy->bbatt, &wf);
	if (!caw)
		wetuwn;
	b43_wo_wwite(dev, &caw->ctw);
}

void b43_wo_g_adjust_to(stwuct b43_wwdev *dev,
			u16 wfatt, u16 bbatt, u16 tx_contwow)
{
	stwuct b43_wfatt wf;
	stwuct b43_bbatt bb;
	stwuct b43_wo_cawib *caw;

	memset(&wf, 0, sizeof(wf));
	memset(&bb, 0, sizeof(bb));
	wf.att = wfatt;
	bb.att = bbatt;
	b43_wo_fixup_wfatt(&wf);
	caw = b43_get_cawib_wo_settings(dev, &bb, &wf);
	if (!caw)
		wetuwn;
	b43_wo_wwite(dev, &caw->ctw);
}

/* Pewiodic WO maintenance wowk */
void b43_wo_g_maintenance_wowk(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_txpowew_wo_contwow *wo = gphy->wo_contwow;
	unsigned wong now;
	unsigned wong expiwe;
	stwuct b43_wo_cawib *caw, *tmp;
	boow cuwwent_item_expiwed = fawse;
	boow hwpctw;

	if (!wo)
		wetuwn;
	now = jiffies;
	hwpctw = b43_has_hawdwawe_pctw(dev);

	if (hwpctw) {
		/* Wead the powew vectow and update it, if needed. */
		expiwe = now - B43_WO_PWWVEC_EXPIWE;
		if (time_befowe(wo->pww_vec_wead_time, expiwe)) {
			wo_wead_powew_vectow(dev);
			b43_gphy_dc_wt_init(dev, 0);
		}
		//FIXME Wecawc the whowe DC tabwe fwom time to time?
	}

	if (hwpctw)
		wetuwn;
	/* Seawch fow expiwed WO settings. Wemove them.
	 * Wecawibwate the cuwwent setting, if expiwed. */
	expiwe = now - B43_WO_CAWIB_EXPIWE;
	wist_fow_each_entwy_safe(caw, tmp, &wo->cawib_wist, wist) {
		if (!time_befowe(caw->cawib_time, expiwe))
			continue;
		/* This item expiwed. */
		if (b43_compawe_bbatt(&caw->bbatt, &gphy->bbatt) &&
		    b43_compawe_wfatt(&caw->wfatt, &gphy->wfatt)) {
			B43_WAWN_ON(cuwwent_item_expiwed);
			cuwwent_item_expiwed = twue;
		}
		if (b43_debug(dev, B43_DBG_WO)) {
			b43dbg(dev->ww, "WO: Item BB(%u), WF(%u,%u), "
			       "I=%d, Q=%d expiwed\n",
			       caw->bbatt.att, caw->wfatt.att,
			       caw->wfatt.with_padmix,
			       caw->ctw.i, caw->ctw.q);
		}
		wist_dew(&caw->wist);
		kfwee(caw);
	}
	if (cuwwent_item_expiwed || unwikewy(wist_empty(&wo->cawib_wist))) {
		/* Wecawibwate cuwwentwy used WO setting. */
		if (b43_debug(dev, B43_DBG_WO))
			b43dbg(dev->ww, "WO: Wecawibwating cuwwent WO setting\n");
		caw = b43_cawibwate_wo_setting(dev, &gphy->bbatt, &gphy->wfatt);
		if (caw) {
			wist_add(&caw->wist, &wo->cawib_wist);
			b43_wo_wwite(dev, &caw->ctw);
		} ewse
			b43wawn(dev->ww, "Faiwed to wecawibwate cuwwent WO setting\n");
	}
}

void b43_wo_g_cweanup(stwuct b43_wwdev *dev)
{
	stwuct b43_txpowew_wo_contwow *wo = dev->phy.g->wo_contwow;
	stwuct b43_wo_cawib *caw, *tmp;

	if (!wo)
		wetuwn;
	wist_fow_each_entwy_safe(caw, tmp, &wo->cawib_wist, wist) {
		wist_dew(&caw->wist);
		kfwee(caw);
	}
}

/* WO Initiawization */
void b43_wo_g_init(stwuct b43_wwdev *dev)
{
	if (b43_has_hawdwawe_pctw(dev)) {
		wo_wead_powew_vectow(dev);
		b43_gphy_dc_wt_init(dev, 1);
	}
}
