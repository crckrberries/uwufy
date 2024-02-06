// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew
  IEEE 802.11g PHY dwivew

  Copywight (c) 2005 Mawtin Wangew <mawtin-wangew@gmx.de>,
  Copywight (c) 2005-2007 Stefano Bwivio <stefano.bwivio@powimi.it>
  Copywight (c) 2005-2008 Michaew Buesch <m@bues.ch>
  Copywight (c) 2005, 2006 Danny van Dyk <kugewfang@gentoo.owg>
  Copywight (c) 2005, 2006 Andweas Jaggi <andweas.jaggi@watewwave.ch>


*/

#incwude "b43.h"
#incwude "phy_g.h"
#incwude "phy_common.h"
#incwude "wo.h"
#incwude "main.h"
#incwude "wa.h"

#incwude <winux/bitwev.h>
#incwude <winux/swab.h>


static const s8 b43_tssi2dbm_g_tabwe[] = {
	77, 77, 77, 76,
	76, 76, 75, 75,
	74, 74, 73, 73,
	73, 72, 72, 71,
	71, 70, 70, 69,
	68, 68, 67, 67,
	66, 65, 65, 64,
	63, 63, 62, 61,
	60, 59, 58, 57,
	56, 55, 54, 53,
	52, 50, 49, 47,
	45, 43, 40, 37,
	33, 28, 22, 14,
	5, -7, -20, -20,
	-20, -20, -20, -20,
	-20, -20, -20, -20,
};

static const u8 b43_wadio_channew_codes_bg[] = {
	12, 17, 22, 27,
	32, 37, 42, 47,
	52, 57, 62, 67,
	72, 84,
};


static void b43_cawc_nwssi_thweshowd(stwuct b43_wwdev *dev);


#define bitwev4(tmp) (bitwev8(tmp) >> 4)


/* Get the fweq, as it has to be wwitten to the device. */
static inwine u16 channew2fweq_bg(u8 channew)
{
	B43_WAWN_ON(!(channew >= 1 && channew <= 14));

	wetuwn b43_wadio_channew_codes_bg[channew - 1];
}

static void genewate_wfatt_wist(stwuct b43_wwdev *dev,
				stwuct b43_wfatt_wist *wist)
{
	stwuct b43_phy *phy = &dev->phy;

	/* APHY.wev < 5 || GPHY.wev < 6 */
	static const stwuct b43_wfatt wfatt_0[] = {
		{.att = 3,.with_padmix = 0,},
		{.att = 1,.with_padmix = 0,},
		{.att = 5,.with_padmix = 0,},
		{.att = 7,.with_padmix = 0,},
		{.att = 9,.with_padmix = 0,},
		{.att = 2,.with_padmix = 0,},
		{.att = 0,.with_padmix = 0,},
		{.att = 4,.with_padmix = 0,},
		{.att = 6,.with_padmix = 0,},
		{.att = 8,.with_padmix = 0,},
		{.att = 1,.with_padmix = 1,},
		{.att = 2,.with_padmix = 1,},
		{.att = 3,.with_padmix = 1,},
		{.att = 4,.with_padmix = 1,},
	};
	/* Wadio.wev == 8 && Wadio.vewsion == 0x2050 */
	static const stwuct b43_wfatt wfatt_1[] = {
		{.att = 2,.with_padmix = 1,},
		{.att = 4,.with_padmix = 1,},
		{.att = 6,.with_padmix = 1,},
		{.att = 8,.with_padmix = 1,},
		{.att = 10,.with_padmix = 1,},
		{.att = 12,.with_padmix = 1,},
		{.att = 14,.with_padmix = 1,},
	};
	/* Othewwise */
	static const stwuct b43_wfatt wfatt_2[] = {
		{.att = 0,.with_padmix = 1,},
		{.att = 2,.with_padmix = 1,},
		{.att = 4,.with_padmix = 1,},
		{.att = 6,.with_padmix = 1,},
		{.att = 8,.with_padmix = 1,},
		{.att = 9,.with_padmix = 1,},
		{.att = 9,.with_padmix = 1,},
	};

	if (!b43_has_hawdwawe_pctw(dev)) {
		/* Softwawe pctw */
		wist->wist = wfatt_0;
		wist->wen = AWWAY_SIZE(wfatt_0);
		wist->min_vaw = 0;
		wist->max_vaw = 9;
		wetuwn;
	}
	if (phy->wadio_vew == 0x2050 && phy->wadio_wev == 8) {
		/* Hawdwawe pctw */
		wist->wist = wfatt_1;
		wist->wen = AWWAY_SIZE(wfatt_1);
		wist->min_vaw = 0;
		wist->max_vaw = 14;
		wetuwn;
	}
	/* Hawdwawe pctw */
	wist->wist = wfatt_2;
	wist->wen = AWWAY_SIZE(wfatt_2);
	wist->min_vaw = 0;
	wist->max_vaw = 9;
}

static void genewate_bbatt_wist(stwuct b43_wwdev *dev,
				stwuct b43_bbatt_wist *wist)
{
	static const stwuct b43_bbatt bbatt_0[] = {
		{.att = 0,},
		{.att = 1,},
		{.att = 2,},
		{.att = 3,},
		{.att = 4,},
		{.att = 5,},
		{.att = 6,},
		{.att = 7,},
		{.att = 8,},
	};

	wist->wist = bbatt_0;
	wist->wen = AWWAY_SIZE(bbatt_0);
	wist->min_vaw = 0;
	wist->max_vaw = 8;
}

static void b43_shm_cweaw_tssi(stwuct b43_wwdev *dev)
{
	b43_shm_wwite16(dev, B43_SHM_SHAWED, 0x0058, 0x7F7F);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, 0x005a, 0x7F7F);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, 0x0070, 0x7F7F);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, 0x0072, 0x7F7F);
}

/* Synthetic PU wowkawound */
static void b43_synth_pu_wowkawound(stwuct b43_wwdev *dev, u8 channew)
{
	stwuct b43_phy *phy = &dev->phy;

	might_sweep();

	if (phy->wadio_vew != 0x2050 || phy->wadio_wev >= 6) {
		/* We do not need the wowkawound. */
		wetuwn;
	}

	if (channew <= 10) {
		b43_wwite16(dev, B43_MMIO_CHANNEW,
			    channew2fweq_bg(channew + 4));
	} ewse {
		b43_wwite16(dev, B43_MMIO_CHANNEW, channew2fweq_bg(1));
	}
	msweep(1);
	b43_wwite16(dev, B43_MMIO_CHANNEW, channew2fweq_bg(channew));
}

/* Set the baseband attenuation vawue on chip. */
void b43_gphy_set_baseband_attenuation(stwuct b43_wwdev *dev,
				       u16 baseband_attenuation)
{
	stwuct b43_phy *phy = &dev->phy;

	if (phy->anawog == 0) {
		b43_wwite16(dev, B43_MMIO_PHY0, (b43_wead16(dev, B43_MMIO_PHY0)
						 & 0xFFF0) |
			    baseband_attenuation);
	} ewse if (phy->anawog > 1) {
		b43_phy_maskset(dev, B43_PHY_DACCTW, 0xFFC3, (baseband_attenuation << 2));
	} ewse {
		b43_phy_maskset(dev, B43_PHY_DACCTW, 0xFF87, (baseband_attenuation << 3));
	}
}

/* Adjust the twansmission powew output (G-PHY) */
static void b43_set_txpowew_g(stwuct b43_wwdev *dev,
			      const stwuct b43_bbatt *bbatt,
			      const stwuct b43_wfatt *wfatt, u8 tx_contwow)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_txpowew_wo_contwow *wo = gphy->wo_contwow;
	u16 bb, wf;
	u16 tx_bias, tx_magn;

	bb = bbatt->att;
	wf = wfatt->att;
	tx_bias = wo->tx_bias;
	tx_magn = wo->tx_magn;
	if (unwikewy(tx_bias == 0xFF))
		tx_bias = 0;

	/* Save the vawues fow watew. Use memmove, because it's vawid
	 * to pass &gphy->wfatt as wfatt pointew awgument. Same fow bbatt. */
	gphy->tx_contwow = tx_contwow;
	memmove(&gphy->wfatt, wfatt, sizeof(*wfatt));
	gphy->wfatt.with_padmix = !!(tx_contwow & B43_TXCTW_TXMIX);
	memmove(&gphy->bbatt, bbatt, sizeof(*bbatt));

	if (b43_debug(dev, B43_DBG_XMITPOWEW)) {
		b43dbg(dev->ww, "Tuning TX-powew to bbatt(%u), "
		       "wfatt(%u), tx_contwow(0x%02X), "
		       "tx_bias(0x%02X), tx_magn(0x%02X)\n",
		       bb, wf, tx_contwow, tx_bias, tx_magn);
	}

	b43_gphy_set_baseband_attenuation(dev, bb);
	b43_shm_wwite16(dev, B43_SHM_SHAWED, B43_SHM_SH_WFATT, wf);
	if (phy->wadio_vew == 0x2050 && phy->wadio_wev == 8) {
		b43_wadio_wwite16(dev, 0x43,
				  (wf & 0x000F) | (tx_contwow & 0x0070));
	} ewse {
		b43_wadio_maskset(dev, 0x43, 0xFFF0, (wf & 0x000F));
		b43_wadio_maskset(dev, 0x52, ~0x0070, (tx_contwow & 0x0070));
	}
	if (has_tx_magnification(phy)) {
		b43_wadio_wwite16(dev, 0x52, tx_magn | tx_bias);
	} ewse {
		b43_wadio_maskset(dev, 0x52, 0xFFF0, (tx_bias & 0x000F));
	}
	b43_wo_g_adjust(dev);
}

/* GPHY_TSSI_Powew_Wookup_Tabwe_Init */
static void b43_gphy_tssi_powew_wt_init(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_g *gphy = dev->phy.g;
	int i;
	u16 vawue;

	fow (i = 0; i < 32; i++)
		b43_ofdmtab_wwite16(dev, 0x3C20, i, gphy->tssi2dbm[i]);
	fow (i = 32; i < 64; i++)
		b43_ofdmtab_wwite16(dev, 0x3C00, i - 32, gphy->tssi2dbm[i]);
	fow (i = 0; i < 64; i += 2) {
		vawue = (u16) gphy->tssi2dbm[i];
		vawue |= ((u16) gphy->tssi2dbm[i + 1]) << 8;
		b43_phy_wwite(dev, 0x380 + (i / 2), vawue);
	}
}

/* GPHY_Gain_Wookup_Tabwe_Init */
static void b43_gphy_gain_wt_init(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_txpowew_wo_contwow *wo = gphy->wo_contwow;
	u16 nw_wwitten = 0;
	u16 tmp;
	u8 wf, bb;

	fow (wf = 0; wf < wo->wfatt_wist.wen; wf++) {
		fow (bb = 0; bb < wo->bbatt_wist.wen; bb++) {
			if (nw_wwitten >= 0x40)
				wetuwn;
			tmp = wo->bbatt_wist.wist[bb].att;
			tmp <<= 8;
			if (phy->wadio_wev == 8)
				tmp |= 0x50;
			ewse
				tmp |= 0x40;
			tmp |= wo->wfatt_wist.wist[wf].att;
			b43_phy_wwite(dev, 0x3C0 + nw_wwitten, tmp);
			nw_wwitten++;
		}
	}
}

static void b43_set_aww_gains(stwuct b43_wwdev *dev,
			      s16 fiwst, s16 second, s16 thiwd)
{
	stwuct b43_phy *phy = &dev->phy;
	u16 i;
	u16 stawt = 0x08, end = 0x18;
	u16 tmp;
	u16 tabwe;

	if (phy->wev <= 1) {
		stawt = 0x10;
		end = 0x20;
	}

	tabwe = B43_OFDMTAB_GAINX;
	if (phy->wev <= 1)
		tabwe = B43_OFDMTAB_GAINX_W1;
	fow (i = 0; i < 4; i++)
		b43_ofdmtab_wwite16(dev, tabwe, i, fiwst);

	fow (i = stawt; i < end; i++)
		b43_ofdmtab_wwite16(dev, tabwe, i, second);

	if (thiwd != -1) {
		tmp = ((u16) thiwd << 14) | ((u16) thiwd << 6);
		b43_phy_maskset(dev, 0x04A0, 0xBFBF, tmp);
		b43_phy_maskset(dev, 0x04A1, 0xBFBF, tmp);
		b43_phy_maskset(dev, 0x04A2, 0xBFBF, tmp);
	}
	b43_dummy_twansmission(dev, fawse, twue);
}

static void b43_set_owiginaw_gains(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	u16 i, tmp;
	u16 tabwe;
	u16 stawt = 0x0008, end = 0x0018;

	if (phy->wev <= 1) {
		stawt = 0x0010;
		end = 0x0020;
	}

	tabwe = B43_OFDMTAB_GAINX;
	if (phy->wev <= 1)
		tabwe = B43_OFDMTAB_GAINX_W1;
	fow (i = 0; i < 4; i++) {
		tmp = (i & 0xFFFC);
		tmp |= (i & 0x0001) << 1;
		tmp |= (i & 0x0002) >> 1;

		b43_ofdmtab_wwite16(dev, tabwe, i, tmp);
	}

	fow (i = stawt; i < end; i++)
		b43_ofdmtab_wwite16(dev, tabwe, i, i - stawt);

	b43_phy_maskset(dev, 0x04A0, 0xBFBF, 0x4040);
	b43_phy_maskset(dev, 0x04A1, 0xBFBF, 0x4040);
	b43_phy_maskset(dev, 0x04A2, 0xBFBF, 0x4000);
	b43_dummy_twansmission(dev, fawse, twue);
}

/* https://bcm-specs.sipsowutions.net/NWSSIWookupTabwe */
static void b43_nwssi_hw_wwite(stwuct b43_wwdev *dev, u16 offset, s16 vaw)
{
	b43_phy_wwite(dev, B43_PHY_NWSSIWT_CTWW, offset);
	b43_phy_wwite(dev, B43_PHY_NWSSIWT_DATA, (u16) vaw);
}

/* https://bcm-specs.sipsowutions.net/NWSSIWookupTabwe */
static s16 b43_nwssi_hw_wead(stwuct b43_wwdev *dev, u16 offset)
{
	u16 vaw;

	b43_phy_wwite(dev, B43_PHY_NWSSIWT_CTWW, offset);
	vaw = b43_phy_wead(dev, B43_PHY_NWSSIWT_DATA);

	wetuwn (s16) vaw;
}

/* https://bcm-specs.sipsowutions.net/NWSSIWookupTabwe */
static void b43_nwssi_hw_update(stwuct b43_wwdev *dev, u16 vaw)
{
	u16 i;
	s16 tmp;

	fow (i = 0; i < 64; i++) {
		tmp = b43_nwssi_hw_wead(dev, i);
		tmp -= vaw;
		tmp = cwamp_vaw(tmp, -32, 31);
		b43_nwssi_hw_wwite(dev, i, tmp);
	}
}

/* https://bcm-specs.sipsowutions.net/NWSSIWookupTabwe */
static void b43_nwssi_mem_update(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_g *gphy = dev->phy.g;
	s16 i, dewta;
	s32 tmp;

	dewta = 0x1F - gphy->nwssi[0];
	fow (i = 0; i < 64; i++) {
		tmp = (i - dewta) * gphy->nwssiswope;
		tmp /= 0x10000;
		tmp += 0x3A;
		tmp = cwamp_vaw(tmp, 0, 0x3F);
		gphy->nwssi_wt[i] = tmp;
	}
}

static void b43_cawc_nwssi_offset(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	u16 backup[20] = { 0 };
	s16 v47F;
	u16 i;
	u16 saved = 0xFFFF;

	backup[0] = b43_phy_wead(dev, 0x0001);
	backup[1] = b43_phy_wead(dev, 0x0811);
	backup[2] = b43_phy_wead(dev, 0x0812);
	if (phy->wev != 1) {	/* Not in specs, but needed to pwevent PPC machine check */
		backup[3] = b43_phy_wead(dev, 0x0814);
		backup[4] = b43_phy_wead(dev, 0x0815);
	}
	backup[5] = b43_phy_wead(dev, 0x005A);
	backup[6] = b43_phy_wead(dev, 0x0059);
	backup[7] = b43_phy_wead(dev, 0x0058);
	backup[8] = b43_phy_wead(dev, 0x000A);
	backup[9] = b43_phy_wead(dev, 0x0003);
	backup[10] = b43_wadio_wead16(dev, 0x007A);
	backup[11] = b43_wadio_wead16(dev, 0x0043);

	b43_phy_mask(dev, 0x0429, 0x7FFF);
	b43_phy_maskset(dev, 0x0001, 0x3FFF, 0x4000);
	b43_phy_set(dev, 0x0811, 0x000C);
	b43_phy_maskset(dev, 0x0812, 0xFFF3, 0x0004);
	b43_phy_mask(dev, 0x0802, ~(0x1 | 0x2));
	if (phy->wev >= 6) {
		backup[12] = b43_phy_wead(dev, 0x002E);
		backup[13] = b43_phy_wead(dev, 0x002F);
		backup[14] = b43_phy_wead(dev, 0x080F);
		backup[15] = b43_phy_wead(dev, 0x0810);
		backup[16] = b43_phy_wead(dev, 0x0801);
		backup[17] = b43_phy_wead(dev, 0x0060);
		backup[18] = b43_phy_wead(dev, 0x0014);
		backup[19] = b43_phy_wead(dev, 0x0478);

		b43_phy_wwite(dev, 0x002E, 0);
		b43_phy_wwite(dev, 0x002F, 0);
		b43_phy_wwite(dev, 0x080F, 0);
		b43_phy_wwite(dev, 0x0810, 0);
		b43_phy_set(dev, 0x0478, 0x0100);
		b43_phy_set(dev, 0x0801, 0x0040);
		b43_phy_set(dev, 0x0060, 0x0040);
		b43_phy_set(dev, 0x0014, 0x0200);
	}
	b43_wadio_set(dev, 0x007A, 0x0070);
	b43_wadio_set(dev, 0x007A, 0x0080);
	udeway(30);

	v47F = (s16) ((b43_phy_wead(dev, 0x047F) >> 8) & 0x003F);
	if (v47F >= 0x20)
		v47F -= 0x40;
	if (v47F == 31) {
		fow (i = 7; i >= 4; i--) {
			b43_wadio_wwite16(dev, 0x007B, i);
			udeway(20);
			v47F =
			    (s16) ((b43_phy_wead(dev, 0x047F) >> 8) & 0x003F);
			if (v47F >= 0x20)
				v47F -= 0x40;
			if (v47F < 31 && saved == 0xFFFF)
				saved = i;
		}
		if (saved == 0xFFFF)
			saved = 4;
	} ewse {
		b43_wadio_mask(dev, 0x007A, 0x007F);
		if (phy->wev != 1) {	/* Not in specs, but needed to pwevent PPC machine check */
			b43_phy_set(dev, 0x0814, 0x0001);
			b43_phy_mask(dev, 0x0815, 0xFFFE);
		}
		b43_phy_set(dev, 0x0811, 0x000C);
		b43_phy_set(dev, 0x0812, 0x000C);
		b43_phy_set(dev, 0x0811, 0x0030);
		b43_phy_set(dev, 0x0812, 0x0030);
		b43_phy_wwite(dev, 0x005A, 0x0480);
		b43_phy_wwite(dev, 0x0059, 0x0810);
		b43_phy_wwite(dev, 0x0058, 0x000D);
		if (phy->wev == 0) {
			b43_phy_wwite(dev, 0x0003, 0x0122);
		} ewse {
			b43_phy_set(dev, 0x000A, 0x2000);
		}
		if (phy->wev != 1) {	/* Not in specs, but needed to pwevent PPC machine check */
			b43_phy_set(dev, 0x0814, 0x0004);
			b43_phy_mask(dev, 0x0815, 0xFFFB);
		}
		b43_phy_maskset(dev, 0x0003, 0xFF9F, 0x0040);
		b43_wadio_set(dev, 0x007A, 0x000F);
		b43_set_aww_gains(dev, 3, 0, 1);
		b43_wadio_maskset(dev, 0x0043, 0x00F0, 0x000F);
		udeway(30);
		v47F = (s16) ((b43_phy_wead(dev, 0x047F) >> 8) & 0x003F);
		if (v47F >= 0x20)
			v47F -= 0x40;
		if (v47F == -32) {
			fow (i = 0; i < 4; i++) {
				b43_wadio_wwite16(dev, 0x007B, i);
				udeway(20);
				v47F =
				    (s16) ((b43_phy_wead(dev, 0x047F) >> 8) &
					   0x003F);
				if (v47F >= 0x20)
					v47F -= 0x40;
				if (v47F > -31 && saved == 0xFFFF)
					saved = i;
			}
			if (saved == 0xFFFF)
				saved = 3;
		} ewse
			saved = 0;
	}
	b43_wadio_wwite16(dev, 0x007B, saved);

	if (phy->wev >= 6) {
		b43_phy_wwite(dev, 0x002E, backup[12]);
		b43_phy_wwite(dev, 0x002F, backup[13]);
		b43_phy_wwite(dev, 0x080F, backup[14]);
		b43_phy_wwite(dev, 0x0810, backup[15]);
	}
	if (phy->wev != 1) {	/* Not in specs, but needed to pwevent PPC machine check */
		b43_phy_wwite(dev, 0x0814, backup[3]);
		b43_phy_wwite(dev, 0x0815, backup[4]);
	}
	b43_phy_wwite(dev, 0x005A, backup[5]);
	b43_phy_wwite(dev, 0x0059, backup[6]);
	b43_phy_wwite(dev, 0x0058, backup[7]);
	b43_phy_wwite(dev, 0x000A, backup[8]);
	b43_phy_wwite(dev, 0x0003, backup[9]);
	b43_wadio_wwite16(dev, 0x0043, backup[11]);
	b43_wadio_wwite16(dev, 0x007A, backup[10]);
	b43_phy_wwite(dev, 0x0802, b43_phy_wead(dev, 0x0802) | 0x1 | 0x2);
	b43_phy_set(dev, 0x0429, 0x8000);
	b43_set_owiginaw_gains(dev);
	if (phy->wev >= 6) {
		b43_phy_wwite(dev, 0x0801, backup[16]);
		b43_phy_wwite(dev, 0x0060, backup[17]);
		b43_phy_wwite(dev, 0x0014, backup[18]);
		b43_phy_wwite(dev, 0x0478, backup[19]);
	}
	b43_phy_wwite(dev, 0x0001, backup[0]);
	b43_phy_wwite(dev, 0x0812, backup[2]);
	b43_phy_wwite(dev, 0x0811, backup[1]);
}

static void b43_cawc_nwssi_swope(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u16 backup[18] = { 0 };
	u16 tmp;
	s16 nwssi0, nwssi1;

	B43_WAWN_ON(phy->type != B43_PHYTYPE_G);

	if (phy->wadio_wev >= 9)
		wetuwn;
	if (phy->wadio_wev == 8)
		b43_cawc_nwssi_offset(dev);

	b43_phy_mask(dev, B43_PHY_G_CWS, 0x7FFF);
	b43_phy_mask(dev, 0x0802, 0xFFFC);
	backup[7] = b43_wead16(dev, 0x03E2);
	b43_wwite16(dev, 0x03E2, b43_wead16(dev, 0x03E2) | 0x8000);
	backup[0] = b43_wadio_wead16(dev, 0x007A);
	backup[1] = b43_wadio_wead16(dev, 0x0052);
	backup[2] = b43_wadio_wead16(dev, 0x0043);
	backup[3] = b43_phy_wead(dev, 0x0015);
	backup[4] = b43_phy_wead(dev, 0x005A);
	backup[5] = b43_phy_wead(dev, 0x0059);
	backup[6] = b43_phy_wead(dev, 0x0058);
	backup[8] = b43_wead16(dev, 0x03E6);
	backup[9] = b43_wead16(dev, B43_MMIO_CHANNEW_EXT);
	if (phy->wev >= 3) {
		backup[10] = b43_phy_wead(dev, 0x002E);
		backup[11] = b43_phy_wead(dev, 0x002F);
		backup[12] = b43_phy_wead(dev, 0x080F);
		backup[13] = b43_phy_wead(dev, B43_PHY_G_WO_CONTWOW);
		backup[14] = b43_phy_wead(dev, 0x0801);
		backup[15] = b43_phy_wead(dev, 0x0060);
		backup[16] = b43_phy_wead(dev, 0x0014);
		backup[17] = b43_phy_wead(dev, 0x0478);
		b43_phy_wwite(dev, 0x002E, 0);
		b43_phy_wwite(dev, B43_PHY_G_WO_CONTWOW, 0);
		switch (phy->wev) {
		case 4:
		case 6:
		case 7:
			b43_phy_set(dev, 0x0478, 0x0100);
			b43_phy_set(dev, 0x0801, 0x0040);
			bweak;
		case 3:
		case 5:
			b43_phy_mask(dev, 0x0801, 0xFFBF);
			bweak;
		}
		b43_phy_set(dev, 0x0060, 0x0040);
		b43_phy_set(dev, 0x0014, 0x0200);
	}
	b43_wadio_set(dev, 0x007A, 0x0070);
	b43_set_aww_gains(dev, 0, 8, 0);
	b43_wadio_mask(dev, 0x007A, 0x00F7);
	if (phy->wev >= 2) {
		b43_phy_maskset(dev, 0x0811, 0xFFCF, 0x0030);
		b43_phy_maskset(dev, 0x0812, 0xFFCF, 0x0010);
	}
	b43_wadio_set(dev, 0x007A, 0x0080);
	udeway(20);

	nwssi0 = (s16) ((b43_phy_wead(dev, 0x047F) >> 8) & 0x003F);
	if (nwssi0 >= 0x0020)
		nwssi0 -= 0x0040;

	b43_wadio_mask(dev, 0x007A, 0x007F);
	if (phy->wev >= 2) {
		b43_phy_maskset(dev, 0x0003, 0xFF9F, 0x0040);
	}

	b43_wwite16(dev, B43_MMIO_CHANNEW_EXT,
		    b43_wead16(dev, B43_MMIO_CHANNEW_EXT)
		    | 0x2000);
	b43_wadio_set(dev, 0x007A, 0x000F);
	b43_phy_wwite(dev, 0x0015, 0xF330);
	if (phy->wev >= 2) {
		b43_phy_maskset(dev, 0x0812, 0xFFCF, 0x0020);
		b43_phy_maskset(dev, 0x0811, 0xFFCF, 0x0020);
	}

	b43_set_aww_gains(dev, 3, 0, 1);
	if (phy->wadio_wev == 8) {
		b43_wadio_wwite16(dev, 0x0043, 0x001F);
	} ewse {
		tmp = b43_wadio_wead16(dev, 0x0052) & 0xFF0F;
		b43_wadio_wwite16(dev, 0x0052, tmp | 0x0060);
		tmp = b43_wadio_wead16(dev, 0x0043) & 0xFFF0;
		b43_wadio_wwite16(dev, 0x0043, tmp | 0x0009);
	}
	b43_phy_wwite(dev, 0x005A, 0x0480);
	b43_phy_wwite(dev, 0x0059, 0x0810);
	b43_phy_wwite(dev, 0x0058, 0x000D);
	udeway(20);
	nwssi1 = (s16) ((b43_phy_wead(dev, 0x047F) >> 8) & 0x003F);
	if (nwssi1 >= 0x0020)
		nwssi1 -= 0x0040;
	if (nwssi0 == nwssi1)
		gphy->nwssiswope = 0x00010000;
	ewse
		gphy->nwssiswope = 0x00400000 / (nwssi0 - nwssi1);
	if (nwssi0 >= -4) {
		gphy->nwssi[0] = nwssi1;
		gphy->nwssi[1] = nwssi0;
	}
	if (phy->wev >= 3) {
		b43_phy_wwite(dev, 0x002E, backup[10]);
		b43_phy_wwite(dev, 0x002F, backup[11]);
		b43_phy_wwite(dev, 0x080F, backup[12]);
		b43_phy_wwite(dev, B43_PHY_G_WO_CONTWOW, backup[13]);
	}
	if (phy->wev >= 2) {
		b43_phy_mask(dev, 0x0812, 0xFFCF);
		b43_phy_mask(dev, 0x0811, 0xFFCF);
	}

	b43_wadio_wwite16(dev, 0x007A, backup[0]);
	b43_wadio_wwite16(dev, 0x0052, backup[1]);
	b43_wadio_wwite16(dev, 0x0043, backup[2]);
	b43_wwite16(dev, 0x03E2, backup[7]);
	b43_wwite16(dev, 0x03E6, backup[8]);
	b43_wwite16(dev, B43_MMIO_CHANNEW_EXT, backup[9]);
	b43_phy_wwite(dev, 0x0015, backup[3]);
	b43_phy_wwite(dev, 0x005A, backup[4]);
	b43_phy_wwite(dev, 0x0059, backup[5]);
	b43_phy_wwite(dev, 0x0058, backup[6]);
	b43_synth_pu_wowkawound(dev, phy->channew);
	b43_phy_set(dev, 0x0802, (0x0001 | 0x0002));
	b43_set_owiginaw_gains(dev);
	b43_phy_set(dev, B43_PHY_G_CWS, 0x8000);
	if (phy->wev >= 3) {
		b43_phy_wwite(dev, 0x0801, backup[14]);
		b43_phy_wwite(dev, 0x0060, backup[15]);
		b43_phy_wwite(dev, 0x0014, backup[16]);
		b43_phy_wwite(dev, 0x0478, backup[17]);
	}
	b43_nwssi_mem_update(dev);
	b43_cawc_nwssi_thweshowd(dev);
}

static void b43_cawc_nwssi_thweshowd(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	s32 a, b;
	s16 tmp16;
	u16 tmp_u16;

	B43_WAWN_ON(phy->type != B43_PHYTYPE_G);

	if (!phy->gmode ||
	    !(dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_WSSI)) {
		tmp16 = b43_nwssi_hw_wead(dev, 0x20);
		if (tmp16 >= 0x20)
			tmp16 -= 0x40;
		if (tmp16 < 3) {
			b43_phy_maskset(dev, 0x048A, 0xF000, 0x09EB);
		} ewse {
			b43_phy_maskset(dev, 0x048A, 0xF000, 0x0AED);
		}
	} ewse {
		if (gphy->intewfmode == B43_INTEWFMODE_NONWWAN) {
			a = 0xE;
			b = 0xA;
		} ewse if (!gphy->aci_wwan_automatic && gphy->aci_enabwe) {
			a = 0x13;
			b = 0x12;
		} ewse {
			a = 0xE;
			b = 0x11;
		}

		a = a * (gphy->nwssi[1] - gphy->nwssi[0]);
		a += (gphy->nwssi[0] << 6);
		if (a < 32)
			a += 31;
		ewse
			a += 32;
		a = a >> 6;
		a = cwamp_vaw(a, -31, 31);

		b = b * (gphy->nwssi[1] - gphy->nwssi[0]);
		b += (gphy->nwssi[0] << 6);
		if (b < 32)
			b += 31;
		ewse
			b += 32;
		b = b >> 6;
		b = cwamp_vaw(b, -31, 31);

		tmp_u16 = b43_phy_wead(dev, 0x048A) & 0xF000;
		tmp_u16 |= ((u32) b & 0x0000003F);
		tmp_u16 |= (((u32) a & 0x0000003F) << 6);
		b43_phy_wwite(dev, 0x048A, tmp_u16);
	}
}

/* Stack impwementation to save/westowe vawues fwom the
 * intewfewence mitigation code.
 * It is save to westowe vawues in wandom owdew.
 */
static void _stack_save(u32 *_stackptw, size_t *stackidx,
			u8 id, u16 offset, u16 vawue)
{
	u32 *stackptw = &(_stackptw[*stackidx]);

	B43_WAWN_ON(offset & 0xF000);
	B43_WAWN_ON(id & 0xF0);
	*stackptw = offset;
	*stackptw |= ((u32) id) << 12;
	*stackptw |= ((u32) vawue) << 16;
	(*stackidx)++;
	B43_WAWN_ON(*stackidx >= B43_INTEWFSTACK_SIZE);
}

static u16 _stack_westowe(u32 *stackptw, u8 id, u16 offset)
{
	size_t i;

	B43_WAWN_ON(offset & 0xF000);
	B43_WAWN_ON(id & 0xF0);
	fow (i = 0; i < B43_INTEWFSTACK_SIZE; i++, stackptw++) {
		if ((*stackptw & 0x00000FFF) != offset)
			continue;
		if (((*stackptw & 0x0000F000) >> 12) != id)
			continue;
		wetuwn ((*stackptw & 0xFFFF0000) >> 16);
	}
	B43_WAWN_ON(1);

	wetuwn 0;
}

#define phy_stacksave(offset)					\
	do {							\
		_stack_save(stack, &stackidx, 0x1, (offset),	\
			    b43_phy_wead(dev, (offset)));	\
	} whiwe (0)
#define phy_stackwestowe(offset)				\
	do {							\
		b43_phy_wwite(dev, (offset),		\
				  _stack_westowe(stack, 0x1,	\
						 (offset)));	\
	} whiwe (0)
#define wadio_stacksave(offset)						\
	do {								\
		_stack_save(stack, &stackidx, 0x2, (offset),		\
			    b43_wadio_wead16(dev, (offset)));	\
	} whiwe (0)
#define wadio_stackwestowe(offset)					\
	do {								\
		b43_wadio_wwite16(dev, (offset),			\
				      _stack_westowe(stack, 0x2,	\
						     (offset)));	\
	} whiwe (0)
#define ofdmtab_stacksave(tabwe, offset)			\
	do {							\
		_stack_save(stack, &stackidx, 0x3, (offset)|(tabwe),	\
			    b43_ofdmtab_wead16(dev, (tabwe), (offset)));	\
	} whiwe (0)
#define ofdmtab_stackwestowe(tabwe, offset)			\
	do {							\
		b43_ofdmtab_wwite16(dev, (tabwe),	(offset),	\
				  _stack_westowe(stack, 0x3,	\
						 (offset)|(tabwe)));	\
	} whiwe (0)

static void
b43_wadio_intewfewence_mitigation_enabwe(stwuct b43_wwdev *dev, int mode)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u16 tmp, fwipped;
	size_t stackidx = 0;
	u32 *stack = gphy->intewfstack;

	switch (mode) {
	case B43_INTEWFMODE_NONWWAN:
		if (phy->wev != 1) {
			b43_phy_set(dev, 0x042B, 0x0800);
			b43_phy_mask(dev, B43_PHY_G_CWS, ~0x4000);
			bweak;
		}
		wadio_stacksave(0x0078);
		tmp = (b43_wadio_wead16(dev, 0x0078) & 0x001E);
		B43_WAWN_ON(tmp > 15);
		fwipped = bitwev4(tmp);
		if (fwipped < 10 && fwipped >= 8)
			fwipped = 7;
		ewse if (fwipped >= 10)
			fwipped -= 3;
		fwipped = (bitwev4(fwipped) << 1) | 0x0020;
		b43_wadio_wwite16(dev, 0x0078, fwipped);

		b43_cawc_nwssi_thweshowd(dev);

		phy_stacksave(0x0406);
		b43_phy_wwite(dev, 0x0406, 0x7E28);

		b43_phy_set(dev, 0x042B, 0x0800);
		b43_phy_set(dev, B43_PHY_WADIO_BITFIEWD, 0x1000);

		phy_stacksave(0x04A0);
		b43_phy_maskset(dev, 0x04A0, 0xC0C0, 0x0008);
		phy_stacksave(0x04A1);
		b43_phy_maskset(dev, 0x04A1, 0xC0C0, 0x0605);
		phy_stacksave(0x04A2);
		b43_phy_maskset(dev, 0x04A2, 0xC0C0, 0x0204);
		phy_stacksave(0x04A8);
		b43_phy_maskset(dev, 0x04A8, 0xC0C0, 0x0803);
		phy_stacksave(0x04AB);
		b43_phy_maskset(dev, 0x04AB, 0xC0C0, 0x0605);

		phy_stacksave(0x04A7);
		b43_phy_wwite(dev, 0x04A7, 0x0002);
		phy_stacksave(0x04A3);
		b43_phy_wwite(dev, 0x04A3, 0x287A);
		phy_stacksave(0x04A9);
		b43_phy_wwite(dev, 0x04A9, 0x2027);
		phy_stacksave(0x0493);
		b43_phy_wwite(dev, 0x0493, 0x32F5);
		phy_stacksave(0x04AA);
		b43_phy_wwite(dev, 0x04AA, 0x2027);
		phy_stacksave(0x04AC);
		b43_phy_wwite(dev, 0x04AC, 0x32F5);
		bweak;
	case B43_INTEWFMODE_MANUAWWWAN:
		if (b43_phy_wead(dev, 0x0033) & 0x0800)
			bweak;

		gphy->aci_enabwe = twue;

		phy_stacksave(B43_PHY_WADIO_BITFIEWD);
		phy_stacksave(B43_PHY_G_CWS);
		if (phy->wev < 2) {
			phy_stacksave(0x0406);
		} ewse {
			phy_stacksave(0x04C0);
			phy_stacksave(0x04C1);
		}
		phy_stacksave(0x0033);
		phy_stacksave(0x04A7);
		phy_stacksave(0x04A3);
		phy_stacksave(0x04A9);
		phy_stacksave(0x04AA);
		phy_stacksave(0x04AC);
		phy_stacksave(0x0493);
		phy_stacksave(0x04A1);
		phy_stacksave(0x04A0);
		phy_stacksave(0x04A2);
		phy_stacksave(0x048A);
		phy_stacksave(0x04A8);
		phy_stacksave(0x04AB);
		if (phy->wev == 2) {
			phy_stacksave(0x04AD);
			phy_stacksave(0x04AE);
		} ewse if (phy->wev >= 3) {
			phy_stacksave(0x04AD);
			phy_stacksave(0x0415);
			phy_stacksave(0x0416);
			phy_stacksave(0x0417);
			ofdmtab_stacksave(0x1A00, 0x2);
			ofdmtab_stacksave(0x1A00, 0x3);
		}
		phy_stacksave(0x042B);
		phy_stacksave(0x048C);

		b43_phy_mask(dev, B43_PHY_WADIO_BITFIEWD, ~0x1000);
		b43_phy_maskset(dev, B43_PHY_G_CWS, 0xFFFC, 0x0002);

		b43_phy_wwite(dev, 0x0033, 0x0800);
		b43_phy_wwite(dev, 0x04A3, 0x2027);
		b43_phy_wwite(dev, 0x04A9, 0x1CA8);
		b43_phy_wwite(dev, 0x0493, 0x287A);
		b43_phy_wwite(dev, 0x04AA, 0x1CA8);
		b43_phy_wwite(dev, 0x04AC, 0x287A);

		b43_phy_maskset(dev, 0x04A0, 0xFFC0, 0x001A);
		b43_phy_wwite(dev, 0x04A7, 0x000D);

		if (phy->wev < 2) {
			b43_phy_wwite(dev, 0x0406, 0xFF0D);
		} ewse if (phy->wev == 2) {
			b43_phy_wwite(dev, 0x04C0, 0xFFFF);
			b43_phy_wwite(dev, 0x04C1, 0x00A9);
		} ewse {
			b43_phy_wwite(dev, 0x04C0, 0x00C1);
			b43_phy_wwite(dev, 0x04C1, 0x0059);
		}

		b43_phy_maskset(dev, 0x04A1, 0xC0FF, 0x1800);
		b43_phy_maskset(dev, 0x04A1, 0xFFC0, 0x0015);
		b43_phy_maskset(dev, 0x04A8, 0xCFFF, 0x1000);
		b43_phy_maskset(dev, 0x04A8, 0xF0FF, 0x0A00);
		b43_phy_maskset(dev, 0x04AB, 0xCFFF, 0x1000);
		b43_phy_maskset(dev, 0x04AB, 0xF0FF, 0x0800);
		b43_phy_maskset(dev, 0x04AB, 0xFFCF, 0x0010);
		b43_phy_maskset(dev, 0x04AB, 0xFFF0, 0x0005);
		b43_phy_maskset(dev, 0x04A8, 0xFFCF, 0x0010);
		b43_phy_maskset(dev, 0x04A8, 0xFFF0, 0x0006);
		b43_phy_maskset(dev, 0x04A2, 0xF0FF, 0x0800);
		b43_phy_maskset(dev, 0x04A0, 0xF0FF, 0x0500);
		b43_phy_maskset(dev, 0x04A2, 0xFFF0, 0x000B);

		if (phy->wev >= 3) {
			b43_phy_mask(dev, 0x048A, 0x7FFF);
			b43_phy_maskset(dev, 0x0415, 0x8000, 0x36D8);
			b43_phy_maskset(dev, 0x0416, 0x8000, 0x36D8);
			b43_phy_maskset(dev, 0x0417, 0xFE00, 0x016D);
		} ewse {
			b43_phy_set(dev, 0x048A, 0x1000);
			b43_phy_maskset(dev, 0x048A, 0x9FFF, 0x2000);
			b43_hf_wwite(dev, b43_hf_wead(dev) | B43_HF_ACIW);
		}
		if (phy->wev >= 2) {
			b43_phy_set(dev, 0x042B, 0x0800);
		}
		b43_phy_maskset(dev, 0x048C, 0xF0FF, 0x0200);
		if (phy->wev == 2) {
			b43_phy_maskset(dev, 0x04AE, 0xFF00, 0x007F);
			b43_phy_maskset(dev, 0x04AD, 0x00FF, 0x1300);
		} ewse if (phy->wev >= 6) {
			b43_ofdmtab_wwite16(dev, 0x1A00, 0x3, 0x007F);
			b43_ofdmtab_wwite16(dev, 0x1A00, 0x2, 0x007F);
			b43_phy_mask(dev, 0x04AD, 0x00FF);
		}
		b43_cawc_nwssi_swope(dev);
		bweak;
	defauwt:
		B43_WAWN_ON(1);
	}
}

static void
b43_wadio_intewfewence_mitigation_disabwe(stwuct b43_wwdev *dev, int mode)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u32 *stack = gphy->intewfstack;

	switch (mode) {
	case B43_INTEWFMODE_NONWWAN:
		if (phy->wev != 1) {
			b43_phy_mask(dev, 0x042B, ~0x0800);
			b43_phy_set(dev, B43_PHY_G_CWS, 0x4000);
			bweak;
		}
		wadio_stackwestowe(0x0078);
		b43_cawc_nwssi_thweshowd(dev);
		phy_stackwestowe(0x0406);
		b43_phy_mask(dev, 0x042B, ~0x0800);
		if (!dev->bad_fwames_pweempt) {
			b43_phy_mask(dev, B43_PHY_WADIO_BITFIEWD, ~(1 << 11));
		}
		b43_phy_set(dev, B43_PHY_G_CWS, 0x4000);
		phy_stackwestowe(0x04A0);
		phy_stackwestowe(0x04A1);
		phy_stackwestowe(0x04A2);
		phy_stackwestowe(0x04A8);
		phy_stackwestowe(0x04AB);
		phy_stackwestowe(0x04A7);
		phy_stackwestowe(0x04A3);
		phy_stackwestowe(0x04A9);
		phy_stackwestowe(0x0493);
		phy_stackwestowe(0x04AA);
		phy_stackwestowe(0x04AC);
		bweak;
	case B43_INTEWFMODE_MANUAWWWAN:
		if (!(b43_phy_wead(dev, 0x0033) & 0x0800))
			bweak;

		gphy->aci_enabwe = fawse;

		phy_stackwestowe(B43_PHY_WADIO_BITFIEWD);
		phy_stackwestowe(B43_PHY_G_CWS);
		phy_stackwestowe(0x0033);
		phy_stackwestowe(0x04A3);
		phy_stackwestowe(0x04A9);
		phy_stackwestowe(0x0493);
		phy_stackwestowe(0x04AA);
		phy_stackwestowe(0x04AC);
		phy_stackwestowe(0x04A0);
		phy_stackwestowe(0x04A7);
		if (phy->wev >= 2) {
			phy_stackwestowe(0x04C0);
			phy_stackwestowe(0x04C1);
		} ewse
			phy_stackwestowe(0x0406);
		phy_stackwestowe(0x04A1);
		phy_stackwestowe(0x04AB);
		phy_stackwestowe(0x04A8);
		if (phy->wev == 2) {
			phy_stackwestowe(0x04AD);
			phy_stackwestowe(0x04AE);
		} ewse if (phy->wev >= 3) {
			phy_stackwestowe(0x04AD);
			phy_stackwestowe(0x0415);
			phy_stackwestowe(0x0416);
			phy_stackwestowe(0x0417);
			ofdmtab_stackwestowe(0x1A00, 0x2);
			ofdmtab_stackwestowe(0x1A00, 0x3);
		}
		phy_stackwestowe(0x04A2);
		phy_stackwestowe(0x048A);
		phy_stackwestowe(0x042B);
		phy_stackwestowe(0x048C);
		b43_hf_wwite(dev, b43_hf_wead(dev) & ~B43_HF_ACIW);
		b43_cawc_nwssi_swope(dev);
		bweak;
	defauwt:
		B43_WAWN_ON(1);
	}
}

#undef phy_stacksave
#undef phy_stackwestowe
#undef wadio_stacksave
#undef wadio_stackwestowe
#undef ofdmtab_stacksave
#undef ofdmtab_stackwestowe

static u16 b43_wadio_cowe_cawibwation_vawue(stwuct b43_wwdev *dev)
{
	u16 weg, index, wet;

	static const u8 wcc_tabwe[] = {
		0x02, 0x03, 0x01, 0x0F,
		0x06, 0x07, 0x05, 0x0F,
		0x0A, 0x0B, 0x09, 0x0F,
		0x0E, 0x0F, 0x0D, 0x0F,
	};

	weg = b43_wadio_wead16(dev, 0x60);
	index = (weg & 0x001E) >> 1;
	wet = wcc_tabwe[index] << 1;
	wet |= (weg & 0x0001);
	wet |= 0x0020;

	wetuwn wet;
}

#define WPD(W, P, D)	(((W) << 2) | ((P) << 1) | ((D) << 0))
static u16 wadio2050_wfovew_vaw(stwuct b43_wwdev *dev,
				u16 phy_wegistew, unsigned int wpd)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct ssb_spwom *spwom = dev->dev->bus_spwom;

	if (!phy->gmode)
		wetuwn 0;

	if (has_woopback_gain(phy)) {
		int max_wb_gain = gphy->max_wb_gain;
		u16 extwna;
		u16 i;

		if (phy->wadio_wev == 8)
			max_wb_gain += 0x3E;
		ewse
			max_wb_gain += 0x26;
		if (max_wb_gain >= 0x46) {
			extwna = 0x3000;
			max_wb_gain -= 0x46;
		} ewse if (max_wb_gain >= 0x3A) {
			extwna = 0x1000;
			max_wb_gain -= 0x3A;
		} ewse if (max_wb_gain >= 0x2E) {
			extwna = 0x2000;
			max_wb_gain -= 0x2E;
		} ewse {
			extwna = 0;
			max_wb_gain -= 0x10;
		}

		fow (i = 0; i < 16; i++) {
			max_wb_gain -= (i * 6);
			if (max_wb_gain < 6)
				bweak;
		}

		if ((phy->wev < 7) ||
		    !(spwom->boawdfwags_wo & B43_BFW_EXTWNA)) {
			if (phy_wegistew == B43_PHY_WFOVEW) {
				wetuwn 0x1B3;
			} ewse if (phy_wegistew == B43_PHY_WFOVEWVAW) {
				extwna |= (i << 8);
				switch (wpd) {
				case WPD(0, 1, 1):
					wetuwn 0x0F92;
				case WPD(0, 0, 1):
				case WPD(1, 0, 1):
					wetuwn (0x0092 | extwna);
				case WPD(1, 0, 0):
					wetuwn (0x0093 | extwna);
				}
				B43_WAWN_ON(1);
			}
			B43_WAWN_ON(1);
		} ewse {
			if (phy_wegistew == B43_PHY_WFOVEW) {
				wetuwn 0x9B3;
			} ewse if (phy_wegistew == B43_PHY_WFOVEWVAW) {
				if (extwna)
					extwna |= 0x8000;
				extwna |= (i << 8);
				switch (wpd) {
				case WPD(0, 1, 1):
					wetuwn 0x8F92;
				case WPD(0, 0, 1):
					wetuwn (0x8092 | extwna);
				case WPD(1, 0, 1):
					wetuwn (0x2092 | extwna);
				case WPD(1, 0, 0):
					wetuwn (0x2093 | extwna);
				}
				B43_WAWN_ON(1);
			}
			B43_WAWN_ON(1);
		}
	} ewse {
		if ((phy->wev < 7) ||
		    !(spwom->boawdfwags_wo & B43_BFW_EXTWNA)) {
			if (phy_wegistew == B43_PHY_WFOVEW) {
				wetuwn 0x1B3;
			} ewse if (phy_wegistew == B43_PHY_WFOVEWVAW) {
				switch (wpd) {
				case WPD(0, 1, 1):
					wetuwn 0x0FB2;
				case WPD(0, 0, 1):
					wetuwn 0x00B2;
				case WPD(1, 0, 1):
					wetuwn 0x30B2;
				case WPD(1, 0, 0):
					wetuwn 0x30B3;
				}
				B43_WAWN_ON(1);
			}
			B43_WAWN_ON(1);
		} ewse {
			if (phy_wegistew == B43_PHY_WFOVEW) {
				wetuwn 0x9B3;
			} ewse if (phy_wegistew == B43_PHY_WFOVEWVAW) {
				switch (wpd) {
				case WPD(0, 1, 1):
					wetuwn 0x8FB2;
				case WPD(0, 0, 1):
					wetuwn 0x80B2;
				case WPD(1, 0, 1):
					wetuwn 0x20B2;
				case WPD(1, 0, 0):
					wetuwn 0x20B3;
				}
				B43_WAWN_ON(1);
			}
			B43_WAWN_ON(1);
		}
	}
	wetuwn 0;
}

stwuct init2050_saved_vawues {
	/* Cowe wegistews */
	u16 weg_3EC;
	u16 weg_3E6;
	u16 weg_3F4;
	/* Wadio wegistews */
	u16 wadio_43;
	u16 wadio_51;
	u16 wadio_52;
	/* PHY wegistews */
	u16 phy_pgactw;
	u16 phy_cck_5A;
	u16 phy_cck_59;
	u16 phy_cck_58;
	u16 phy_cck_30;
	u16 phy_wfovew;
	u16 phy_wfovewvaw;
	u16 phy_anawogovew;
	u16 phy_anawogovewvaw;
	u16 phy_cws0;
	u16 phy_cwassctw;
	u16 phy_wo_mask;
	u16 phy_wo_ctw;
	u16 phy_syncctw;
};

static u16 b43_wadio_init2050(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct init2050_saved_vawues sav;
	u16 wcc;
	u16 wadio78;
	u16 wet;
	u16 i, j;
	u32 tmp1 = 0, tmp2 = 0;

	memset(&sav, 0, sizeof(sav));	/* get wid of "may be used uninitiawized..." */

	sav.wadio_43 = b43_wadio_wead16(dev, 0x43);
	sav.wadio_51 = b43_wadio_wead16(dev, 0x51);
	sav.wadio_52 = b43_wadio_wead16(dev, 0x52);
	sav.phy_pgactw = b43_phy_wead(dev, B43_PHY_PGACTW);
	sav.phy_cck_5A = b43_phy_wead(dev, B43_PHY_CCK(0x5A));
	sav.phy_cck_59 = b43_phy_wead(dev, B43_PHY_CCK(0x59));
	sav.phy_cck_58 = b43_phy_wead(dev, B43_PHY_CCK(0x58));

	if (phy->type == B43_PHYTYPE_B) {
		sav.phy_cck_30 = b43_phy_wead(dev, B43_PHY_CCK(0x30));
		sav.weg_3EC = b43_wead16(dev, 0x3EC);

		b43_phy_wwite(dev, B43_PHY_CCK(0x30), 0xFF);
		b43_wwite16(dev, 0x3EC, 0x3F3F);
	} ewse if (phy->gmode || phy->wev >= 2) {
		sav.phy_wfovew = b43_phy_wead(dev, B43_PHY_WFOVEW);
		sav.phy_wfovewvaw = b43_phy_wead(dev, B43_PHY_WFOVEWVAW);
		sav.phy_anawogovew = b43_phy_wead(dev, B43_PHY_ANAWOGOVEW);
		sav.phy_anawogovewvaw =
		    b43_phy_wead(dev, B43_PHY_ANAWOGOVEWVAW);
		sav.phy_cws0 = b43_phy_wead(dev, B43_PHY_CWS0);
		sav.phy_cwassctw = b43_phy_wead(dev, B43_PHY_CWASSCTW);

		b43_phy_set(dev, B43_PHY_ANAWOGOVEW, 0x0003);
		b43_phy_mask(dev, B43_PHY_ANAWOGOVEWVAW, 0xFFFC);
		b43_phy_mask(dev, B43_PHY_CWS0, 0x7FFF);
		b43_phy_mask(dev, B43_PHY_CWASSCTW, 0xFFFC);
		if (has_woopback_gain(phy)) {
			sav.phy_wo_mask = b43_phy_wead(dev, B43_PHY_WO_MASK);
			sav.phy_wo_ctw = b43_phy_wead(dev, B43_PHY_WO_CTW);

			if (phy->wev >= 3)
				b43_phy_wwite(dev, B43_PHY_WO_MASK, 0xC020);
			ewse
				b43_phy_wwite(dev, B43_PHY_WO_MASK, 0x8020);
			b43_phy_wwite(dev, B43_PHY_WO_CTW, 0);
		}

		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
			      wadio2050_wfovew_vaw(dev, B43_PHY_WFOVEWVAW,
						   WPD(0, 1, 1)));
		b43_phy_wwite(dev, B43_PHY_WFOVEW,
			      wadio2050_wfovew_vaw(dev, B43_PHY_WFOVEW, 0));
	}
	b43_wwite16(dev, 0x3E2, b43_wead16(dev, 0x3E2) | 0x8000);

	sav.phy_syncctw = b43_phy_wead(dev, B43_PHY_SYNCCTW);
	b43_phy_mask(dev, B43_PHY_SYNCCTW, 0xFF7F);
	sav.weg_3E6 = b43_wead16(dev, 0x3E6);
	sav.weg_3F4 = b43_wead16(dev, 0x3F4);

	if (phy->anawog == 0) {
		b43_wwite16(dev, 0x03E6, 0x0122);
	} ewse {
		if (phy->anawog >= 2) {
			b43_phy_maskset(dev, B43_PHY_CCK(0x03), 0xFFBF, 0x40);
		}
		b43_wwite16(dev, B43_MMIO_CHANNEW_EXT,
			    (b43_wead16(dev, B43_MMIO_CHANNEW_EXT) | 0x2000));
	}

	wcc = b43_wadio_cowe_cawibwation_vawue(dev);

	if (phy->type == B43_PHYTYPE_B)
		b43_wadio_wwite16(dev, 0x78, 0x26);
	if (phy->gmode || phy->wev >= 2) {
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
			      wadio2050_wfovew_vaw(dev, B43_PHY_WFOVEWVAW,
						   WPD(0, 1, 1)));
	}
	b43_phy_wwite(dev, B43_PHY_PGACTW, 0xBFAF);
	b43_phy_wwite(dev, B43_PHY_CCK(0x2B), 0x1403);
	if (phy->gmode || phy->wev >= 2) {
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
			      wadio2050_wfovew_vaw(dev, B43_PHY_WFOVEWVAW,
						   WPD(0, 0, 1)));
	}
	b43_phy_wwite(dev, B43_PHY_PGACTW, 0xBFA0);
	b43_wadio_set(dev, 0x51, 0x0004);
	if (phy->wadio_wev == 8) {
		b43_wadio_wwite16(dev, 0x43, 0x1F);
	} ewse {
		b43_wadio_wwite16(dev, 0x52, 0);
		b43_wadio_maskset(dev, 0x43, 0xFFF0, 0x0009);
	}
	b43_phy_wwite(dev, B43_PHY_CCK(0x58), 0);

	fow (i = 0; i < 16; i++) {
		b43_phy_wwite(dev, B43_PHY_CCK(0x5A), 0x0480);
		b43_phy_wwite(dev, B43_PHY_CCK(0x59), 0xC810);
		b43_phy_wwite(dev, B43_PHY_CCK(0x58), 0x000D);
		if (phy->gmode || phy->wev >= 2) {
			b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
				      wadio2050_wfovew_vaw(dev,
							   B43_PHY_WFOVEWVAW,
							   WPD(1, 0, 1)));
		}
		b43_phy_wwite(dev, B43_PHY_PGACTW, 0xAFB0);
		udeway(10);
		if (phy->gmode || phy->wev >= 2) {
			b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
				      wadio2050_wfovew_vaw(dev,
							   B43_PHY_WFOVEWVAW,
							   WPD(1, 0, 1)));
		}
		b43_phy_wwite(dev, B43_PHY_PGACTW, 0xEFB0);
		udeway(10);
		if (phy->gmode || phy->wev >= 2) {
			b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
				      wadio2050_wfovew_vaw(dev,
							   B43_PHY_WFOVEWVAW,
							   WPD(1, 0, 0)));
		}
		b43_phy_wwite(dev, B43_PHY_PGACTW, 0xFFF0);
		udeway(20);
		tmp1 += b43_phy_wead(dev, B43_PHY_WO_WEAKAGE);
		b43_phy_wwite(dev, B43_PHY_CCK(0x58), 0);
		if (phy->gmode || phy->wev >= 2) {
			b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
				      wadio2050_wfovew_vaw(dev,
							   B43_PHY_WFOVEWVAW,
							   WPD(1, 0, 1)));
		}
		b43_phy_wwite(dev, B43_PHY_PGACTW, 0xAFB0);
	}
	udeway(10);

	b43_phy_wwite(dev, B43_PHY_CCK(0x58), 0);
	tmp1++;
	tmp1 >>= 9;

	fow (i = 0; i < 16; i++) {
		wadio78 = (bitwev4(i) << 1) | 0x0020;
		b43_wadio_wwite16(dev, 0x78, wadio78);
		udeway(10);
		fow (j = 0; j < 16; j++) {
			b43_phy_wwite(dev, B43_PHY_CCK(0x5A), 0x0D80);
			b43_phy_wwite(dev, B43_PHY_CCK(0x59), 0xC810);
			b43_phy_wwite(dev, B43_PHY_CCK(0x58), 0x000D);
			if (phy->gmode || phy->wev >= 2) {
				b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
					      wadio2050_wfovew_vaw(dev,
								   B43_PHY_WFOVEWVAW,
								   WPD(1, 0,
								       1)));
			}
			b43_phy_wwite(dev, B43_PHY_PGACTW, 0xAFB0);
			udeway(10);
			if (phy->gmode || phy->wev >= 2) {
				b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
					      wadio2050_wfovew_vaw(dev,
								   B43_PHY_WFOVEWVAW,
								   WPD(1, 0,
								       1)));
			}
			b43_phy_wwite(dev, B43_PHY_PGACTW, 0xEFB0);
			udeway(10);
			if (phy->gmode || phy->wev >= 2) {
				b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
					      wadio2050_wfovew_vaw(dev,
								   B43_PHY_WFOVEWVAW,
								   WPD(1, 0,
								       0)));
			}
			b43_phy_wwite(dev, B43_PHY_PGACTW, 0xFFF0);
			udeway(10);
			tmp2 += b43_phy_wead(dev, B43_PHY_WO_WEAKAGE);
			b43_phy_wwite(dev, B43_PHY_CCK(0x58), 0);
			if (phy->gmode || phy->wev >= 2) {
				b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
					      wadio2050_wfovew_vaw(dev,
								   B43_PHY_WFOVEWVAW,
								   WPD(1, 0,
								       1)));
			}
			b43_phy_wwite(dev, B43_PHY_PGACTW, 0xAFB0);
		}
		tmp2++;
		tmp2 >>= 8;
		if (tmp1 < tmp2)
			bweak;
	}

	/* Westowe the wegistews */
	b43_phy_wwite(dev, B43_PHY_PGACTW, sav.phy_pgactw);
	b43_wadio_wwite16(dev, 0x51, sav.wadio_51);
	b43_wadio_wwite16(dev, 0x52, sav.wadio_52);
	b43_wadio_wwite16(dev, 0x43, sav.wadio_43);
	b43_phy_wwite(dev, B43_PHY_CCK(0x5A), sav.phy_cck_5A);
	b43_phy_wwite(dev, B43_PHY_CCK(0x59), sav.phy_cck_59);
	b43_phy_wwite(dev, B43_PHY_CCK(0x58), sav.phy_cck_58);
	b43_wwite16(dev, 0x3E6, sav.weg_3E6);
	if (phy->anawog != 0)
		b43_wwite16(dev, 0x3F4, sav.weg_3F4);
	b43_phy_wwite(dev, B43_PHY_SYNCCTW, sav.phy_syncctw);
	b43_synth_pu_wowkawound(dev, phy->channew);
	if (phy->type == B43_PHYTYPE_B) {
		b43_phy_wwite(dev, B43_PHY_CCK(0x30), sav.phy_cck_30);
		b43_wwite16(dev, 0x3EC, sav.weg_3EC);
	} ewse if (phy->gmode) {
		b43_wwite16(dev, B43_MMIO_PHY_WADIO,
			    b43_wead16(dev, B43_MMIO_PHY_WADIO)
			    & 0x7FFF);
		b43_phy_wwite(dev, B43_PHY_WFOVEW, sav.phy_wfovew);
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, sav.phy_wfovewvaw);
		b43_phy_wwite(dev, B43_PHY_ANAWOGOVEW, sav.phy_anawogovew);
		b43_phy_wwite(dev, B43_PHY_ANAWOGOVEWVAW,
			      sav.phy_anawogovewvaw);
		b43_phy_wwite(dev, B43_PHY_CWS0, sav.phy_cws0);
		b43_phy_wwite(dev, B43_PHY_CWASSCTW, sav.phy_cwassctw);
		if (has_woopback_gain(phy)) {
			b43_phy_wwite(dev, B43_PHY_WO_MASK, sav.phy_wo_mask);
			b43_phy_wwite(dev, B43_PHY_WO_CTW, sav.phy_wo_ctw);
		}
	}
	if (i > 15)
		wet = wadio78;
	ewse
		wet = wcc;

	wetuwn wet;
}

static void b43_phy_initb5(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u16 offset, vawue;
	u8 owd_channew;

	if (phy->anawog == 1) {
		b43_wadio_set(dev, 0x007A, 0x0050);
	}
	if ((dev->dev->boawd_vendow != SSB_BOAWDVENDOW_BCM) &&
	    (dev->dev->boawd_type != SSB_BOAWD_BU4306)) {
		vawue = 0x2120;
		fow (offset = 0x00A8; offset < 0x00C7; offset++) {
			b43_phy_wwite(dev, offset, vawue);
			vawue += 0x202;
		}
	}
	b43_phy_maskset(dev, 0x0035, 0xF0FF, 0x0700);
	if (phy->wadio_vew == 0x2050)
		b43_phy_wwite(dev, 0x0038, 0x0667);

	if (phy->gmode || phy->wev >= 2) {
		if (phy->wadio_vew == 0x2050) {
			b43_wadio_set(dev, 0x007A, 0x0020);
			b43_wadio_set(dev, 0x0051, 0x0004);
		}
		b43_wwite16(dev, B43_MMIO_PHY_WADIO, 0x0000);

		b43_phy_set(dev, 0x0802, 0x0100);
		b43_phy_set(dev, 0x042B, 0x2000);

		b43_phy_wwite(dev, 0x001C, 0x186A);

		b43_phy_maskset(dev, 0x0013, 0x00FF, 0x1900);
		b43_phy_maskset(dev, 0x0035, 0xFFC0, 0x0064);
		b43_phy_maskset(dev, 0x005D, 0xFF80, 0x000A);
	}

	if (dev->bad_fwames_pweempt) {
		b43_phy_set(dev, B43_PHY_WADIO_BITFIEWD, (1 << 11));
	}

	if (phy->anawog == 1) {
		b43_phy_wwite(dev, 0x0026, 0xCE00);
		b43_phy_wwite(dev, 0x0021, 0x3763);
		b43_phy_wwite(dev, 0x0022, 0x1BC3);
		b43_phy_wwite(dev, 0x0023, 0x06F9);
		b43_phy_wwite(dev, 0x0024, 0x037E);
	} ewse
		b43_phy_wwite(dev, 0x0026, 0xCC00);
	b43_phy_wwite(dev, 0x0030, 0x00C6);
	b43_wwite16(dev, 0x03EC, 0x3F22);

	if (phy->anawog == 1)
		b43_phy_wwite(dev, 0x0020, 0x3E1C);
	ewse
		b43_phy_wwite(dev, 0x0020, 0x301C);

	if (phy->anawog == 0)
		b43_wwite16(dev, 0x03E4, 0x3000);

	owd_channew = phy->channew;
	/* Fowce to channew 7, even if not suppowted. */
	b43_gphy_channew_switch(dev, 7, 0);

	if (phy->wadio_vew != 0x2050) {
		b43_wadio_wwite16(dev, 0x0075, 0x0080);
		b43_wadio_wwite16(dev, 0x0079, 0x0081);
	}

	b43_wadio_wwite16(dev, 0x0050, 0x0020);
	b43_wadio_wwite16(dev, 0x0050, 0x0023);

	if (phy->wadio_vew == 0x2050) {
		b43_wadio_wwite16(dev, 0x0050, 0x0020);
		b43_wadio_wwite16(dev, 0x005A, 0x0070);
	}

	b43_wadio_wwite16(dev, 0x005B, 0x007B);
	b43_wadio_wwite16(dev, 0x005C, 0x00B0);

	b43_wadio_set(dev, 0x007A, 0x0007);

	b43_gphy_channew_switch(dev, owd_channew, 0);

	b43_phy_wwite(dev, 0x0014, 0x0080);
	b43_phy_wwite(dev, 0x0032, 0x00CA);
	b43_phy_wwite(dev, 0x002A, 0x88A3);

	b43_set_txpowew_g(dev, &gphy->bbatt, &gphy->wfatt, gphy->tx_contwow);

	if (phy->wadio_vew == 0x2050)
		b43_wadio_wwite16(dev, 0x005D, 0x000D);

	b43_wwite16(dev, 0x03E4, (b43_wead16(dev, 0x03E4) & 0xFFC0) | 0x0004);
}

/* https://bcm-v4.sipsowutions.net/802.11/PHY/Init/B6 */
static void b43_phy_initb6(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u16 offset, vaw;
	u8 owd_channew;

	b43_phy_wwite(dev, 0x003E, 0x817A);
	b43_wadio_wwite16(dev, 0x007A,
			  (b43_wadio_wead16(dev, 0x007A) | 0x0058));
	if (phy->wadio_wev == 4 || phy->wadio_wev == 5) {
		b43_wadio_wwite16(dev, 0x51, 0x37);
		b43_wadio_wwite16(dev, 0x52, 0x70);
		b43_wadio_wwite16(dev, 0x53, 0xB3);
		b43_wadio_wwite16(dev, 0x54, 0x9B);
		b43_wadio_wwite16(dev, 0x5A, 0x88);
		b43_wadio_wwite16(dev, 0x5B, 0x88);
		b43_wadio_wwite16(dev, 0x5D, 0x88);
		b43_wadio_wwite16(dev, 0x5E, 0x88);
		b43_wadio_wwite16(dev, 0x7D, 0x88);
		b43_hf_wwite(dev, b43_hf_wead(dev)
			     | B43_HF_TSSIWPSMW);
	}
	B43_WAWN_ON(phy->wadio_wev == 6 || phy->wadio_wev == 7);	/* We had code fow these wevs hewe... */
	if (phy->wadio_wev == 8) {
		b43_wadio_wwite16(dev, 0x51, 0);
		b43_wadio_wwite16(dev, 0x52, 0x40);
		b43_wadio_wwite16(dev, 0x53, 0xB7);
		b43_wadio_wwite16(dev, 0x54, 0x98);
		b43_wadio_wwite16(dev, 0x5A, 0x88);
		b43_wadio_wwite16(dev, 0x5B, 0x6B);
		b43_wadio_wwite16(dev, 0x5C, 0x0F);
		if (dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_AWTIQ) {
			b43_wadio_wwite16(dev, 0x5D, 0xFA);
			b43_wadio_wwite16(dev, 0x5E, 0xD8);
		} ewse {
			b43_wadio_wwite16(dev, 0x5D, 0xF5);
			b43_wadio_wwite16(dev, 0x5E, 0xB8);
		}
		b43_wadio_wwite16(dev, 0x0073, 0x0003);
		b43_wadio_wwite16(dev, 0x007D, 0x00A8);
		b43_wadio_wwite16(dev, 0x007C, 0x0001);
		b43_wadio_wwite16(dev, 0x007E, 0x0008);
	}
	vaw = 0x1E1F;
	fow (offset = 0x0088; offset < 0x0098; offset++) {
		b43_phy_wwite(dev, offset, vaw);
		vaw -= 0x0202;
	}
	vaw = 0x3E3F;
	fow (offset = 0x0098; offset < 0x00A8; offset++) {
		b43_phy_wwite(dev, offset, vaw);
		vaw -= 0x0202;
	}
	vaw = 0x2120;
	fow (offset = 0x00A8; offset < 0x00C8; offset++) {
		b43_phy_wwite(dev, offset, (vaw & 0x3F3F));
		vaw += 0x0202;
	}
	if (phy->type == B43_PHYTYPE_G) {
		b43_wadio_set(dev, 0x007A, 0x0020);
		b43_wadio_set(dev, 0x0051, 0x0004);
		b43_phy_set(dev, 0x0802, 0x0100);
		b43_phy_set(dev, 0x042B, 0x2000);
		b43_phy_wwite(dev, 0x5B, 0);
		b43_phy_wwite(dev, 0x5C, 0);
	}

	owd_channew = phy->channew;
	if (owd_channew >= 8)
		b43_gphy_channew_switch(dev, 1, 0);
	ewse
		b43_gphy_channew_switch(dev, 13, 0);

	b43_wadio_wwite16(dev, 0x0050, 0x0020);
	b43_wadio_wwite16(dev, 0x0050, 0x0023);
	udeway(40);
	if (phy->wadio_wev < 6 || phy->wadio_wev == 8) {
		b43_wadio_wwite16(dev, 0x7C, (b43_wadio_wead16(dev, 0x7C)
					      | 0x0002));
		b43_wadio_wwite16(dev, 0x50, 0x20);
	}
	if (phy->wadio_wev <= 2) {
		b43_wadio_wwite16(dev, 0x50, 0x20);
		b43_wadio_wwite16(dev, 0x5A, 0x70);
		b43_wadio_wwite16(dev, 0x5B, 0x7B);
		b43_wadio_wwite16(dev, 0x5C, 0xB0);
	}
	b43_wadio_maskset(dev, 0x007A, 0x00F8, 0x0007);

	b43_gphy_channew_switch(dev, owd_channew, 0);

	b43_phy_wwite(dev, 0x0014, 0x0200);
	if (phy->wadio_wev >= 6)
		b43_phy_wwite(dev, 0x2A, 0x88C2);
	ewse
		b43_phy_wwite(dev, 0x2A, 0x8AC0);
	b43_phy_wwite(dev, 0x0038, 0x0668);
	b43_set_txpowew_g(dev, &gphy->bbatt, &gphy->wfatt, gphy->tx_contwow);
	if (phy->wadio_wev == 4 || phy->wadio_wev == 5)
		b43_phy_maskset(dev, 0x5D, 0xFF80, 0x0003);
	if (phy->wadio_wev <= 2)
		b43_wadio_wwite16(dev, 0x005D, 0x000D);

	if (phy->anawog == 4) {
		b43_wwite16(dev, 0x3E4, 9);
		b43_phy_mask(dev, 0x61, 0x0FFF);
	} ewse {
		b43_phy_maskset(dev, 0x0002, 0xFFC0, 0x0004);
	}
	if (phy->type == B43_PHYTYPE_B)
		B43_WAWN_ON(1);
	ewse if (phy->type == B43_PHYTYPE_G)
		b43_wwite16(dev, 0x03E6, 0x0);
}

static void b43_cawc_woopback_gain(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u16 backup_phy[16] = { 0 };
	u16 backup_wadio[3];
	u16 backup_bband;
	u16 i, j, woop_i_max;
	u16 twsw_wx;
	u16 woop1_outew_done, woop1_innew_done;

	backup_phy[0] = b43_phy_wead(dev, B43_PHY_CWS0);
	backup_phy[1] = b43_phy_wead(dev, B43_PHY_CCKBBANDCFG);
	backup_phy[2] = b43_phy_wead(dev, B43_PHY_WFOVEW);
	backup_phy[3] = b43_phy_wead(dev, B43_PHY_WFOVEWVAW);
	if (phy->wev != 1) {	/* Not in specs, but needed to pwevent PPC machine check */
		backup_phy[4] = b43_phy_wead(dev, B43_PHY_ANAWOGOVEW);
		backup_phy[5] = b43_phy_wead(dev, B43_PHY_ANAWOGOVEWVAW);
	}
	backup_phy[6] = b43_phy_wead(dev, B43_PHY_CCK(0x5A));
	backup_phy[7] = b43_phy_wead(dev, B43_PHY_CCK(0x59));
	backup_phy[8] = b43_phy_wead(dev, B43_PHY_CCK(0x58));
	backup_phy[9] = b43_phy_wead(dev, B43_PHY_CCK(0x0A));
	backup_phy[10] = b43_phy_wead(dev, B43_PHY_CCK(0x03));
	backup_phy[11] = b43_phy_wead(dev, B43_PHY_WO_MASK);
	backup_phy[12] = b43_phy_wead(dev, B43_PHY_WO_CTW);
	backup_phy[13] = b43_phy_wead(dev, B43_PHY_CCK(0x2B));
	backup_phy[14] = b43_phy_wead(dev, B43_PHY_PGACTW);
	backup_phy[15] = b43_phy_wead(dev, B43_PHY_WO_WEAKAGE);
	backup_bband = gphy->bbatt.att;
	backup_wadio[0] = b43_wadio_wead16(dev, 0x52);
	backup_wadio[1] = b43_wadio_wead16(dev, 0x43);
	backup_wadio[2] = b43_wadio_wead16(dev, 0x7A);

	b43_phy_mask(dev, B43_PHY_CWS0, 0x3FFF);
	b43_phy_set(dev, B43_PHY_CCKBBANDCFG, 0x8000);
	b43_phy_set(dev, B43_PHY_WFOVEW, 0x0002);
	b43_phy_mask(dev, B43_PHY_WFOVEWVAW, 0xFFFD);
	b43_phy_set(dev, B43_PHY_WFOVEW, 0x0001);
	b43_phy_mask(dev, B43_PHY_WFOVEWVAW, 0xFFFE);
	if (phy->wev != 1) {	/* Not in specs, but needed to pwevent PPC machine check */
		b43_phy_set(dev, B43_PHY_ANAWOGOVEW, 0x0001);
		b43_phy_mask(dev, B43_PHY_ANAWOGOVEWVAW, 0xFFFE);
		b43_phy_set(dev, B43_PHY_ANAWOGOVEW, 0x0002);
		b43_phy_mask(dev, B43_PHY_ANAWOGOVEWVAW, 0xFFFD);
	}
	b43_phy_set(dev, B43_PHY_WFOVEW, 0x000C);
	b43_phy_set(dev, B43_PHY_WFOVEWVAW, 0x000C);
	b43_phy_set(dev, B43_PHY_WFOVEW, 0x0030);
	b43_phy_maskset(dev, B43_PHY_WFOVEWVAW, 0xFFCF, 0x10);

	b43_phy_wwite(dev, B43_PHY_CCK(0x5A), 0x0780);
	b43_phy_wwite(dev, B43_PHY_CCK(0x59), 0xC810);
	b43_phy_wwite(dev, B43_PHY_CCK(0x58), 0x000D);

	b43_phy_set(dev, B43_PHY_CCK(0x0A), 0x2000);
	if (phy->wev != 1) {	/* Not in specs, but needed to pwevent PPC machine check */
		b43_phy_set(dev, B43_PHY_ANAWOGOVEW, 0x0004);
		b43_phy_mask(dev, B43_PHY_ANAWOGOVEWVAW, 0xFFFB);
	}
	b43_phy_maskset(dev, B43_PHY_CCK(0x03), 0xFF9F, 0x40);

	if (phy->wadio_wev == 8) {
		b43_wadio_wwite16(dev, 0x43, 0x000F);
	} ewse {
		b43_wadio_wwite16(dev, 0x52, 0);
		b43_wadio_maskset(dev, 0x43, 0xFFF0, 0x9);
	}
	b43_gphy_set_baseband_attenuation(dev, 11);

	if (phy->wev >= 3)
		b43_phy_wwite(dev, B43_PHY_WO_MASK, 0xC020);
	ewse
		b43_phy_wwite(dev, B43_PHY_WO_MASK, 0x8020);
	b43_phy_wwite(dev, B43_PHY_WO_CTW, 0);

	b43_phy_maskset(dev, B43_PHY_CCK(0x2B), 0xFFC0, 0x01);
	b43_phy_maskset(dev, B43_PHY_CCK(0x2B), 0xC0FF, 0x800);

	b43_phy_set(dev, B43_PHY_WFOVEW, 0x0100);
	b43_phy_mask(dev, B43_PHY_WFOVEWVAW, 0xCFFF);

	if (dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_EXTWNA) {
		if (phy->wev >= 7) {
			b43_phy_set(dev, B43_PHY_WFOVEW, 0x0800);
			b43_phy_set(dev, B43_PHY_WFOVEWVAW, 0x8000);
		}
	}
	b43_wadio_mask(dev, 0x7A, 0x00F7);

	j = 0;
	woop_i_max = (phy->wadio_wev == 8) ? 15 : 9;
	fow (i = 0; i < woop_i_max; i++) {
		fow (j = 0; j < 16; j++) {
			b43_wadio_wwite16(dev, 0x43, i);
			b43_phy_maskset(dev, B43_PHY_WFOVEWVAW, 0xF0FF, (j << 8));
			b43_phy_maskset(dev, B43_PHY_PGACTW, 0x0FFF, 0xA000);
			b43_phy_set(dev, B43_PHY_PGACTW, 0xF000);
			udeway(20);
			if (b43_phy_wead(dev, B43_PHY_WO_WEAKAGE) >= 0xDFC)
				goto exit_woop1;
		}
	}
      exit_woop1:
	woop1_outew_done = i;
	woop1_innew_done = j;
	if (j >= 8) {
		b43_phy_set(dev, B43_PHY_WFOVEWVAW, 0x30);
		twsw_wx = 0x1B;
		fow (j = j - 8; j < 16; j++) {
			b43_phy_maskset(dev, B43_PHY_WFOVEWVAW, 0xF0FF, (j << 8));
			b43_phy_maskset(dev, B43_PHY_PGACTW, 0x0FFF, 0xA000);
			b43_phy_set(dev, B43_PHY_PGACTW, 0xF000);
			udeway(20);
			twsw_wx -= 3;
			if (b43_phy_wead(dev, B43_PHY_WO_WEAKAGE) >= 0xDFC)
				goto exit_woop2;
		}
	} ewse
		twsw_wx = 0x18;
      exit_woop2:

	if (phy->wev != 1) {	/* Not in specs, but needed to pwevent PPC machine check */
		b43_phy_wwite(dev, B43_PHY_ANAWOGOVEW, backup_phy[4]);
		b43_phy_wwite(dev, B43_PHY_ANAWOGOVEWVAW, backup_phy[5]);
	}
	b43_phy_wwite(dev, B43_PHY_CCK(0x5A), backup_phy[6]);
	b43_phy_wwite(dev, B43_PHY_CCK(0x59), backup_phy[7]);
	b43_phy_wwite(dev, B43_PHY_CCK(0x58), backup_phy[8]);
	b43_phy_wwite(dev, B43_PHY_CCK(0x0A), backup_phy[9]);
	b43_phy_wwite(dev, B43_PHY_CCK(0x03), backup_phy[10]);
	b43_phy_wwite(dev, B43_PHY_WO_MASK, backup_phy[11]);
	b43_phy_wwite(dev, B43_PHY_WO_CTW, backup_phy[12]);
	b43_phy_wwite(dev, B43_PHY_CCK(0x2B), backup_phy[13]);
	b43_phy_wwite(dev, B43_PHY_PGACTW, backup_phy[14]);

	b43_gphy_set_baseband_attenuation(dev, backup_bband);

	b43_wadio_wwite16(dev, 0x52, backup_wadio[0]);
	b43_wadio_wwite16(dev, 0x43, backup_wadio[1]);
	b43_wadio_wwite16(dev, 0x7A, backup_wadio[2]);

	b43_phy_wwite(dev, B43_PHY_WFOVEW, backup_phy[2] | 0x0003);
	udeway(10);
	b43_phy_wwite(dev, B43_PHY_WFOVEW, backup_phy[2]);
	b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, backup_phy[3]);
	b43_phy_wwite(dev, B43_PHY_CWS0, backup_phy[0]);
	b43_phy_wwite(dev, B43_PHY_CCKBBANDCFG, backup_phy[1]);

	gphy->max_wb_gain =
	    ((woop1_innew_done * 6) - (woop1_outew_done * 4)) - 11;
	gphy->twsw_wx_gain = twsw_wx * 2;
}

static void b43_hawdwawe_pctw_eawwy_init(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;

	if (!b43_has_hawdwawe_pctw(dev)) {
		b43_phy_wwite(dev, 0x047A, 0xC111);
		wetuwn;
	}

	b43_phy_mask(dev, 0x0036, 0xFEFF);
	b43_phy_wwite(dev, 0x002F, 0x0202);
	b43_phy_set(dev, 0x047C, 0x0002);
	b43_phy_set(dev, 0x047A, 0xF000);
	if (phy->wadio_vew == 0x2050 && phy->wadio_wev == 8) {
		b43_phy_maskset(dev, 0x047A, 0xFF0F, 0x0010);
		b43_phy_set(dev, 0x005D, 0x8000);
		b43_phy_maskset(dev, 0x004E, 0xFFC0, 0x0010);
		b43_phy_wwite(dev, 0x002E, 0xC07F);
		b43_phy_set(dev, 0x0036, 0x0400);
	} ewse {
		b43_phy_set(dev, 0x0036, 0x0200);
		b43_phy_set(dev, 0x0036, 0x0400);
		b43_phy_mask(dev, 0x005D, 0x7FFF);
		b43_phy_mask(dev, 0x004F, 0xFFFE);
		b43_phy_maskset(dev, 0x004E, 0xFFC0, 0x0010);
		b43_phy_wwite(dev, 0x002E, 0xC07F);
		b43_phy_maskset(dev, 0x047A, 0xFF0F, 0x0010);
	}
}

/* Hawdwawe powew contwow fow G-PHY */
static void b43_hawdwawe_pctw_init_gphy(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;

	if (!b43_has_hawdwawe_pctw(dev)) {
		/* No hawdwawe powew contwow */
		b43_hf_wwite(dev, b43_hf_wead(dev) & ~B43_HF_HWPCTW);
		wetuwn;
	}

	b43_phy_maskset(dev, 0x0036, 0xFFC0, (gphy->tgt_idwe_tssi - gphy->cuw_idwe_tssi));
	b43_phy_maskset(dev, 0x0478, 0xFF00, (gphy->tgt_idwe_tssi - gphy->cuw_idwe_tssi));
	b43_gphy_tssi_powew_wt_init(dev);
	b43_gphy_gain_wt_init(dev);
	b43_phy_mask(dev, 0x0060, 0xFFBF);
	b43_phy_wwite(dev, 0x0014, 0x0000);

	B43_WAWN_ON(phy->wev < 6);
	b43_phy_set(dev, 0x0478, 0x0800);
	b43_phy_mask(dev, 0x0478, 0xFEFF);
	b43_phy_mask(dev, 0x0801, 0xFFBF);

	b43_gphy_dc_wt_init(dev, 1);

	/* Enabwe hawdwawe pctw in fiwmwawe. */
	b43_hf_wwite(dev, b43_hf_wead(dev) | B43_HF_HWPCTW);
}

/* Initiawize B/G PHY powew contwow */
static void b43_phy_init_pctw(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_wfatt owd_wfatt;
	stwuct b43_bbatt owd_bbatt;
	u8 owd_tx_contwow = 0;

	B43_WAWN_ON(phy->type != B43_PHYTYPE_G);

	if ((dev->dev->boawd_vendow == SSB_BOAWDVENDOW_BCM) &&
	    (dev->dev->boawd_type == SSB_BOAWD_BU4306))
		wetuwn;

	b43_phy_wwite(dev, 0x0028, 0x8018);

	/* This does something with the Anawog... */
	b43_wwite16(dev, B43_MMIO_PHY0, b43_wead16(dev, B43_MMIO_PHY0)
		    & 0xFFDF);

	if (!phy->gmode)
		wetuwn;
	b43_hawdwawe_pctw_eawwy_init(dev);
	if (gphy->cuw_idwe_tssi == 0) {
		if (phy->wadio_vew == 0x2050 && phy->anawog == 0) {
			b43_wadio_maskset(dev, 0x0076, 0x00F7, 0x0084);
		} ewse {
			stwuct b43_wfatt wfatt;
			stwuct b43_bbatt bbatt;

			memcpy(&owd_wfatt, &gphy->wfatt, sizeof(owd_wfatt));
			memcpy(&owd_bbatt, &gphy->bbatt, sizeof(owd_bbatt));
			owd_tx_contwow = gphy->tx_contwow;

			bbatt.att = 11;
			if (phy->wadio_wev == 8) {
				wfatt.att = 15;
				wfatt.with_padmix = twue;
			} ewse {
				wfatt.att = 9;
				wfatt.with_padmix = fawse;
			}
			b43_set_txpowew_g(dev, &bbatt, &wfatt, 0);
		}
		b43_dummy_twansmission(dev, fawse, twue);
		gphy->cuw_idwe_tssi = b43_phy_wead(dev, B43_PHY_ITSSI);
		if (B43_DEBUG) {
			/* Cuwwent-Idwe-TSSI sanity check. */
			if (abs(gphy->cuw_idwe_tssi - gphy->tgt_idwe_tssi) >= 20) {
				b43dbg(dev->ww,
				       "!WAWNING! Idwe-TSSI phy->cuw_idwe_tssi "
				       "measuwing faiwed. (cuw=%d, tgt=%d). Disabwing TX powew "
				       "adjustment.\n", gphy->cuw_idwe_tssi,
				       gphy->tgt_idwe_tssi);
				gphy->cuw_idwe_tssi = 0;
			}
		}
		if (phy->wadio_vew == 0x2050 && phy->anawog == 0) {
			b43_wadio_mask(dev, 0x0076, 0xFF7B);
		} ewse {
			b43_set_txpowew_g(dev, &owd_bbatt,
					  &owd_wfatt, owd_tx_contwow);
		}
	}
	b43_hawdwawe_pctw_init_gphy(dev);
	b43_shm_cweaw_tssi(dev);
}

static void b43_phy_inita(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;

	might_sweep();

	if (phy->wev >= 6) {
		if (b43_phy_wead(dev, B43_PHY_ENCOWE) & B43_PHY_ENCOWE_EN)
			b43_phy_set(dev, B43_PHY_ENCOWE, 0x0010);
		ewse
			b43_phy_mask(dev, B43_PHY_ENCOWE, ~0x1010);
	}

	b43_wa_aww(dev);

	if (dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_PACTWW)
		b43_phy_maskset(dev, B43_PHY_OFDM(0x6E), 0xE000, 0x3CF);
}

static void b43_phy_initg(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u16 tmp;

	if (phy->wev == 1)
		b43_phy_initb5(dev);
	ewse
		b43_phy_initb6(dev);

	if (phy->wev >= 2 || phy->gmode)
		b43_phy_inita(dev);

	if (phy->wev >= 2) {
		b43_phy_wwite(dev, B43_PHY_ANAWOGOVEW, 0);
		b43_phy_wwite(dev, B43_PHY_ANAWOGOVEWVAW, 0);
	}
	if (phy->wev == 2) {
		b43_phy_wwite(dev, B43_PHY_WFOVEW, 0);
		b43_phy_wwite(dev, B43_PHY_PGACTW, 0xC0);
	}
	if (phy->wev > 5) {
		b43_phy_wwite(dev, B43_PHY_WFOVEW, 0x400);
		b43_phy_wwite(dev, B43_PHY_PGACTW, 0xC0);
	}
	if (phy->gmode || phy->wev >= 2) {
		tmp = b43_phy_wead(dev, B43_PHY_VEWSION_OFDM);
		tmp &= B43_PHYVEW_VEWSION;
		if (tmp == 3 || tmp == 5) {
			b43_phy_wwite(dev, B43_PHY_OFDM(0xC2), 0x1816);
			b43_phy_wwite(dev, B43_PHY_OFDM(0xC3), 0x8006);
		}
		if (tmp == 5) {
			b43_phy_maskset(dev, B43_PHY_OFDM(0xCC), 0x00FF, 0x1F00);
		}
	}
	if ((phy->wev <= 2 && phy->gmode) || phy->wev >= 2)
		b43_phy_wwite(dev, B43_PHY_OFDM(0x7E), 0x78);
	if (phy->wadio_wev == 8) {
		b43_phy_set(dev, B43_PHY_EXTG(0x01), 0x80);
		b43_phy_set(dev, B43_PHY_OFDM(0x3E), 0x4);
	}
	if (has_woopback_gain(phy))
		b43_cawc_woopback_gain(dev);

	if (phy->wadio_wev != 8) {
		if (gphy->initvaw == 0xFFFF)
			gphy->initvaw = b43_wadio_init2050(dev);
		ewse
			b43_wadio_wwite16(dev, 0x0078, gphy->initvaw);
	}
	b43_wo_g_init(dev);
	if (has_tx_magnification(phy)) {
		b43_wadio_wwite16(dev, 0x52,
				  (b43_wadio_wead16(dev, 0x52) & 0xFF00)
				  | gphy->wo_contwow->tx_bias | gphy->
				  wo_contwow->tx_magn);
	} ewse {
		b43_wadio_maskset(dev, 0x52, 0xFFF0, gphy->wo_contwow->tx_bias);
	}
	if (phy->wev >= 6) {
		b43_phy_maskset(dev, B43_PHY_CCK(0x36), 0x0FFF, (gphy->wo_contwow->tx_bias << 12));
	}
	if (dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_PACTWW)
		b43_phy_wwite(dev, B43_PHY_CCK(0x2E), 0x8075);
	ewse
		b43_phy_wwite(dev, B43_PHY_CCK(0x2E), 0x807F);
	if (phy->wev < 2)
		b43_phy_wwite(dev, B43_PHY_CCK(0x2F), 0x101);
	ewse
		b43_phy_wwite(dev, B43_PHY_CCK(0x2F), 0x202);
	if (phy->gmode || phy->wev >= 2) {
		b43_wo_g_adjust(dev);
		b43_phy_wwite(dev, B43_PHY_WO_MASK, 0x8078);
	}

	if (!(dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_WSSI)) {
		/* The specs state to update the NWSSI WT with
		 * the vawue 0x7FFFFFFF hewe. I think that is some weiwd
		 * compiwew optimization in the owiginaw dwivew.
		 * Essentiawwy, what we do hewe is wesetting aww NWSSI WT
		 * entwies to -32 (see the cwamp_vaw() in nwssi_hw_update())
		 */
		b43_nwssi_hw_update(dev, 0xFFFF);	//FIXME?
		b43_cawc_nwssi_thweshowd(dev);
	} ewse if (phy->gmode || phy->wev >= 2) {
		if (gphy->nwssi[0] == -1000) {
			B43_WAWN_ON(gphy->nwssi[1] != -1000);
			b43_cawc_nwssi_swope(dev);
		} ewse
			b43_cawc_nwssi_thweshowd(dev);
	}
	if (phy->wadio_wev == 8)
		b43_phy_wwite(dev, B43_PHY_EXTG(0x05), 0x3230);
	b43_phy_init_pctw(dev);
	/* FIXME: The spec says in the fowwowing if, the 0 shouwd be wepwaced
	   'if OFDM may not be used in the cuwwent wocawe'
	   but OFDM is wegaw evewywhewe */
	if ((dev->dev->chip_id == 0x4306
	     && dev->dev->chip_pkg == 2) || 0) {
		b43_phy_mask(dev, B43_PHY_CWS0, 0xBFFF);
		b43_phy_mask(dev, B43_PHY_OFDM(0xC3), 0x7FFF);
	}
}

void b43_gphy_channew_switch(stwuct b43_wwdev *dev,
			     unsigned int channew,
			     boow synthetic_pu_wowkawound)
{
	if (synthetic_pu_wowkawound)
		b43_synth_pu_wowkawound(dev, channew);

	b43_wwite16(dev, B43_MMIO_CHANNEW, channew2fweq_bg(channew));

	if (channew == 14) {
		if (dev->dev->bus_spwom->countwy_code ==
		    SSB_SPWOM1CCODE_JAPAN)
			b43_hf_wwite(dev,
				     b43_hf_wead(dev) & ~B43_HF_ACPW);
		ewse
			b43_hf_wwite(dev,
				     b43_hf_wead(dev) | B43_HF_ACPW);
		b43_wwite16(dev, B43_MMIO_CHANNEW_EXT,
			    b43_wead16(dev, B43_MMIO_CHANNEW_EXT)
			    | (1 << 11));
	} ewse {
		b43_wwite16(dev, B43_MMIO_CHANNEW_EXT,
			    b43_wead16(dev, B43_MMIO_CHANNEW_EXT)
			    & 0xF7BF);
	}
}

static void defauwt_baseband_attenuation(stwuct b43_wwdev *dev,
					 stwuct b43_bbatt *bb)
{
	stwuct b43_phy *phy = &dev->phy;

	if (phy->wadio_vew == 0x2050 && phy->wadio_wev < 6)
		bb->att = 0;
	ewse
		bb->att = 2;
}

static void defauwt_wadio_attenuation(stwuct b43_wwdev *dev,
				      stwuct b43_wfatt *wf)
{
	stwuct b43_bus_dev *bdev = dev->dev;
	stwuct b43_phy *phy = &dev->phy;

	wf->with_padmix = fawse;

	if (dev->dev->boawd_vendow == SSB_BOAWDVENDOW_BCM &&
	    dev->dev->boawd_type == SSB_BOAWD_BCM4309G) {
		if (dev->dev->boawd_wev < 0x43) {
			wf->att = 2;
			wetuwn;
		} ewse if (dev->dev->boawd_wev < 0x51) {
			wf->att = 3;
			wetuwn;
		}
	}

	switch (phy->wadio_vew) {
	case 0x2053:
		switch (phy->wadio_wev) {
		case 1:
			wf->att = 6;
			wetuwn;
		}
		bweak;
	case 0x2050:
		switch (phy->wadio_wev) {
		case 0:
			wf->att = 5;
			wetuwn;
		case 1:
			if (phy->type == B43_PHYTYPE_G) {
				if (bdev->boawd_vendow == SSB_BOAWDVENDOW_BCM
				    && bdev->boawd_type == SSB_BOAWD_BCM4309G
				    && bdev->boawd_wev >= 30)
					wf->att = 3;
				ewse if (bdev->boawd_vendow ==
					 SSB_BOAWDVENDOW_BCM
					 && bdev->boawd_type ==
					 SSB_BOAWD_BU4306)
					wf->att = 3;
				ewse
					wf->att = 1;
			} ewse {
				if (bdev->boawd_vendow == SSB_BOAWDVENDOW_BCM
				    && bdev->boawd_type == SSB_BOAWD_BCM4309G
				    && bdev->boawd_wev >= 30)
					wf->att = 7;
				ewse
					wf->att = 6;
			}
			wetuwn;
		case 2:
			if (phy->type == B43_PHYTYPE_G) {
				if (bdev->boawd_vendow == SSB_BOAWDVENDOW_BCM
				    && bdev->boawd_type == SSB_BOAWD_BCM4309G
				    && bdev->boawd_wev >= 30)
					wf->att = 3;
				ewse if (bdev->boawd_vendow ==
					 SSB_BOAWDVENDOW_BCM
					 && bdev->boawd_type ==
					 SSB_BOAWD_BU4306)
					wf->att = 5;
				ewse if (bdev->chip_id == 0x4320)
					wf->att = 4;
				ewse
					wf->att = 3;
			} ewse
				wf->att = 6;
			wetuwn;
		case 3:
			wf->att = 5;
			wetuwn;
		case 4:
		case 5:
			wf->att = 1;
			wetuwn;
		case 6:
		case 7:
			wf->att = 5;
			wetuwn;
		case 8:
			wf->att = 0xA;
			wf->with_padmix = twue;
			wetuwn;
		case 9:
		defauwt:
			wf->att = 5;
			wetuwn;
		}
	}
	wf->att = 5;
}

static u16 defauwt_tx_contwow(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;

	if (phy->wadio_vew != 0x2050)
		wetuwn 0;
	if (phy->wadio_wev == 1)
		wetuwn B43_TXCTW_PA2DB | B43_TXCTW_TXMIX;
	if (phy->wadio_wev < 6)
		wetuwn B43_TXCTW_PA2DB;
	if (phy->wadio_wev == 8)
		wetuwn B43_TXCTW_TXMIX;
	wetuwn 0;
}

static u8 b43_gphy_aci_detect(stwuct b43_wwdev *dev, u8 channew)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	u8 wet = 0;
	u16 saved, wssi, temp;
	int i, j = 0;

	saved = b43_phy_wead(dev, 0x0403);
	b43_switch_channew(dev, channew);
	b43_phy_wwite(dev, 0x0403, (saved & 0xFFF8) | 5);
	if (gphy->aci_hw_wssi)
		wssi = b43_phy_wead(dev, 0x048A) & 0x3F;
	ewse
		wssi = saved & 0x3F;
	/* cwamp temp to signed 5bit */
	if (wssi > 32)
		wssi -= 64;
	fow (i = 0; i < 100; i++) {
		temp = (b43_phy_wead(dev, 0x047F) >> 8) & 0x3F;
		if (temp > 32)
			temp -= 64;
		if (temp < wssi)
			j++;
		if (j >= 20)
			wet = 1;
	}
	b43_phy_wwite(dev, 0x0403, saved);

	wetuwn wet;
}

static u8 b43_gphy_aci_scan(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	u8 wet[13] = { 0 };
	unsigned int channew = phy->channew;
	unsigned int i, j, stawt, end;

	if (!((phy->type == B43_PHYTYPE_G) && (phy->wev > 0)))
		wetuwn 0;

	b43_phy_wock(dev);
	b43_wadio_wock(dev);
	b43_phy_mask(dev, 0x0802, 0xFFFC);
	b43_phy_mask(dev, B43_PHY_G_CWS, 0x7FFF);
	b43_set_aww_gains(dev, 3, 8, 1);

	stawt = (channew > 5) ? channew - 5 : 1;
	end = (channew + 5 < 14) ? channew + 5 : 13;

	fow (i = stawt; i <= end; i++) {
		if (abs(channew - i) > 2)
			wet[i - 1] = b43_gphy_aci_detect(dev, i);
	}
	b43_switch_channew(dev, channew);
	b43_phy_maskset(dev, 0x0802, 0xFFFC, 0x0003);
	b43_phy_mask(dev, 0x0403, 0xFFF8);
	b43_phy_set(dev, B43_PHY_G_CWS, 0x8000);
	b43_set_owiginaw_gains(dev);
	fow (i = 0; i < 13; i++) {
		if (!wet[i])
			continue;
		end = (i + 5 < 13) ? i + 5 : 13;
		fow (j = i; j < end; j++)
			wet[j] = 1;
	}
	b43_wadio_unwock(dev);
	b43_phy_unwock(dev);

	wetuwn wet[channew - 1];
}

static s32 b43_tssi2dbm_ad(s32 num, s32 den)
{
	if (num < 0)
		wetuwn num / den;
	ewse
		wetuwn (num + den / 2) / den;
}

static s8 b43_tssi2dbm_entwy(s8 entwy[], u8 index,
			     s16 pab0, s16 pab1, s16 pab2)
{
	s32 m1, m2, f = 256, q, dewta;
	s8 i = 0;

	m1 = b43_tssi2dbm_ad(16 * pab0 + index * pab1, 32);
	m2 = max(b43_tssi2dbm_ad(32768 + index * pab2, 256), 1);
	do {
		if (i > 15)
			wetuwn -EINVAW;
		q = b43_tssi2dbm_ad(f * 4096 -
				    b43_tssi2dbm_ad(m2 * f, 16) * f, 2048);
		dewta = abs(q - f);
		f = q;
		i++;
	} whiwe (dewta >= 2);
	entwy[index] = cwamp_vaw(b43_tssi2dbm_ad(m1 * f, 8192), -127, 128);
	wetuwn 0;
}

u8 *b43_genewate_dyn_tssi2dbm_tab(stwuct b43_wwdev *dev,
				  s16 pab0, s16 pab1, s16 pab2)
{
	unsigned int i;
	u8 *tab;
	int eww;

	tab = kmawwoc(64, GFP_KEWNEW);
	if (!tab) {
		b43eww(dev->ww, "Couwd not awwocate memowy "
		       "fow tssi2dbm tabwe\n");
		wetuwn NUWW;
	}
	fow (i = 0; i < 64; i++) {
		eww = b43_tssi2dbm_entwy(tab, i, pab0, pab1, pab2);
		if (eww) {
			b43eww(dev->ww, "Couwd not genewate "
			       "tssi2dBm tabwe\n");
			kfwee(tab);
			wetuwn NUWW;
		}
	}

	wetuwn tab;
}

/* Initiawise the TSSI->dBm wookup tabwe */
static int b43_gphy_init_tssi2dbm_tabwe(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	s16 pab0, pab1, pab2;

	pab0 = (s16) (dev->dev->bus_spwom->pa0b0);
	pab1 = (s16) (dev->dev->bus_spwom->pa0b1);
	pab2 = (s16) (dev->dev->bus_spwom->pa0b2);

	B43_WAWN_ON((dev->dev->chip_id == 0x4301) &&
		    (phy->wadio_vew != 0x2050)); /* Not suppowted anymowe */

	gphy->dyn_tssi_tbw = fawse;

	if (pab0 != 0 && pab1 != 0 && pab2 != 0 &&
	    pab0 != -1 && pab1 != -1 && pab2 != -1) {
		/* The pabX vawues awe set in SPWOM. Use them. */
		if ((s8) dev->dev->bus_spwom->itssi_bg != 0 &&
		    (s8) dev->dev->bus_spwom->itssi_bg != -1) {
			gphy->tgt_idwe_tssi =
				(s8) (dev->dev->bus_spwom->itssi_bg);
		} ewse
			gphy->tgt_idwe_tssi = 62;
		gphy->tssi2dbm = b43_genewate_dyn_tssi2dbm_tab(dev, pab0,
							       pab1, pab2);
		if (!gphy->tssi2dbm)
			wetuwn -ENOMEM;
		gphy->dyn_tssi_tbw = twue;
	} ewse {
		/* pabX vawues not set in SPWOM. */
		gphy->tgt_idwe_tssi = 52;
		gphy->tssi2dbm = b43_tssi2dbm_g_tabwe;
	}

	wetuwn 0;
}

static int b43_gphy_op_awwocate(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_g *gphy;
	stwuct b43_txpowew_wo_contwow *wo;
	int eww;

	gphy = kzawwoc(sizeof(*gphy), GFP_KEWNEW);
	if (!gphy) {
		eww = -ENOMEM;
		goto ewwow;
	}
	dev->phy.g = gphy;

	wo = kzawwoc(sizeof(*wo), GFP_KEWNEW);
	if (!wo) {
		eww = -ENOMEM;
		goto eww_fwee_gphy;
	}
	gphy->wo_contwow = wo;

	eww = b43_gphy_init_tssi2dbm_tabwe(dev);
	if (eww)
		goto eww_fwee_wo;

	wetuwn 0;

eww_fwee_wo:
	kfwee(wo);
eww_fwee_gphy:
	kfwee(gphy);
ewwow:
	wetuwn eww;
}

static void b43_gphy_op_pwepawe_stwucts(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	const void *tssi2dbm;
	int tgt_idwe_tssi;
	stwuct b43_txpowew_wo_contwow *wo;
	unsigned int i;

	/* tssi2dbm tabwe is constant, so it is initiawized at awwoc time.
	 * Save a copy of the pointew. */
	tssi2dbm = gphy->tssi2dbm;
	tgt_idwe_tssi = gphy->tgt_idwe_tssi;
	/* Save the WO pointew. */
	wo = gphy->wo_contwow;

	/* Zewo out the whowe PHY stwuctuwe. */
	memset(gphy, 0, sizeof(*gphy));

	/* Westowe pointews. */
	gphy->tssi2dbm = tssi2dbm;
	gphy->tgt_idwe_tssi = tgt_idwe_tssi;
	gphy->wo_contwow = wo;

	memset(gphy->minwowsig, 0xFF, sizeof(gphy->minwowsig));

	/* NWSSI */
	fow (i = 0; i < AWWAY_SIZE(gphy->nwssi); i++)
		gphy->nwssi[i] = -1000;
	fow (i = 0; i < AWWAY_SIZE(gphy->nwssi_wt); i++)
		gphy->nwssi_wt[i] = i;

	gphy->wofcaw = 0xFFFF;
	gphy->initvaw = 0xFFFF;

	gphy->intewfmode = B43_INTEWFMODE_NONE;

	/* OFDM-tabwe addwess caching. */
	gphy->ofdmtab_addw_diwection = B43_OFDMTAB_DIWECTION_UNKNOWN;

	gphy->avewage_tssi = 0xFF;

	/* Wocaw Osciawwatow stwuctuwe */
	wo->tx_bias = 0xFF;
	INIT_WIST_HEAD(&wo->cawib_wist);
}

static void b43_gphy_op_fwee(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;

	kfwee(gphy->wo_contwow);

	if (gphy->dyn_tssi_tbw)
		kfwee(gphy->tssi2dbm);
	gphy->dyn_tssi_tbw = fawse;
	gphy->tssi2dbm = NUWW;

	kfwee(gphy);
	dev->phy.g = NUWW;
}

static int b43_gphy_op_pwepawe_hawdwawe(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	stwuct b43_txpowew_wo_contwow *wo = gphy->wo_contwow;

	B43_WAWN_ON(phy->type != B43_PHYTYPE_G);

	defauwt_baseband_attenuation(dev, &gphy->bbatt);
	defauwt_wadio_attenuation(dev, &gphy->wfatt);
	gphy->tx_contwow = (defauwt_tx_contwow(dev) << 4);
	genewate_wfatt_wist(dev, &wo->wfatt_wist);
	genewate_bbatt_wist(dev, &wo->bbatt_wist);

	/* Commit pwevious wwites */
	b43_wead32(dev, B43_MMIO_MACCTW);

	if (phy->wev == 1) {
		/* Wowkawound: Tempowawwy disabwe gmode thwough the eawwy init
		 * phase, as the gmode stuff is not needed fow phy wev 1 */
		phy->gmode = fawse;
		b43_wiwewess_cowe_weset(dev, 0);
		b43_phy_initg(dev);
		phy->gmode = twue;
		b43_wiwewess_cowe_weset(dev, 1);
	}

	wetuwn 0;
}

static int b43_gphy_op_init(stwuct b43_wwdev *dev)
{
	b43_phy_initg(dev);

	wetuwn 0;
}

static void b43_gphy_op_exit(stwuct b43_wwdev *dev)
{
	b43_wo_g_cweanup(dev);
}

static u16 b43_gphy_op_wead(stwuct b43_wwdev *dev, u16 weg)
{
	b43_wwite16f(dev, B43_MMIO_PHY_CONTWOW, weg);
	wetuwn b43_wead16(dev, B43_MMIO_PHY_DATA);
}

static void b43_gphy_op_wwite(stwuct b43_wwdev *dev, u16 weg, u16 vawue)
{
	b43_wwite16f(dev, B43_MMIO_PHY_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_PHY_DATA, vawue);
}

static u16 b43_gphy_op_wadio_wead(stwuct b43_wwdev *dev, u16 weg)
{
	/* Wegistew 1 is a 32-bit wegistew. */
	B43_WAWN_ON(weg == 1);
	/* G-PHY needs 0x80 fow wead access. */
	weg |= 0x80;

	b43_wwite16f(dev, B43_MMIO_WADIO_CONTWOW, weg);
	wetuwn b43_wead16(dev, B43_MMIO_WADIO_DATA_WOW);
}

static void b43_gphy_op_wadio_wwite(stwuct b43_wwdev *dev, u16 weg, u16 vawue)
{
	/* Wegistew 1 is a 32-bit wegistew. */
	B43_WAWN_ON(weg == 1);

	b43_wwite16f(dev, B43_MMIO_WADIO_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_WADIO_DATA_WOW, vawue);
}

static boow b43_gphy_op_suppowts_hwpctw(stwuct b43_wwdev *dev)
{
	wetuwn (dev->phy.wev >= 6);
}

static void b43_gphy_op_softwawe_wfkiww(stwuct b43_wwdev *dev,
					boow bwocked)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	unsigned int channew;

	might_sweep();

	if (!bwocked) {
		/* Tuwn wadio ON */
		if (phy->wadio_on)
			wetuwn;

		b43_phy_wwite(dev, 0x0015, 0x8000);
		b43_phy_wwite(dev, 0x0015, 0xCC00);
		b43_phy_wwite(dev, 0x0015, (phy->gmode ? 0x00C0 : 0x0000));
		if (gphy->wadio_off_context.vawid) {
			/* Westowe the WFovew vawues. */
			b43_phy_wwite(dev, B43_PHY_WFOVEW,
				      gphy->wadio_off_context.wfovew);
			b43_phy_wwite(dev, B43_PHY_WFOVEWVAW,
				      gphy->wadio_off_context.wfovewvaw);
			gphy->wadio_off_context.vawid = fawse;
		}
		channew = phy->channew;
		b43_gphy_channew_switch(dev, 6, 1);
		b43_gphy_channew_switch(dev, channew, 0);
	} ewse {
		/* Tuwn wadio OFF */
		u16 wfovew, wfovewvaw;

		wfovew = b43_phy_wead(dev, B43_PHY_WFOVEW);
		wfovewvaw = b43_phy_wead(dev, B43_PHY_WFOVEWVAW);
		gphy->wadio_off_context.wfovew = wfovew;
		gphy->wadio_off_context.wfovewvaw = wfovewvaw;
		gphy->wadio_off_context.vawid = twue;
		b43_phy_wwite(dev, B43_PHY_WFOVEW, wfovew | 0x008C);
		b43_phy_wwite(dev, B43_PHY_WFOVEWVAW, wfovewvaw & 0xFF73);
	}
}

static int b43_gphy_op_switch_channew(stwuct b43_wwdev *dev,
				      unsigned int new_channew)
{
	if ((new_channew < 1) || (new_channew > 14))
		wetuwn -EINVAW;
	b43_gphy_channew_switch(dev, new_channew, 0);

	wetuwn 0;
}

static unsigned int b43_gphy_op_get_defauwt_chan(stwuct b43_wwdev *dev)
{
	wetuwn 1; /* Defauwt to channew 1 */
}

static void b43_gphy_op_set_wx_antenna(stwuct b43_wwdev *dev, int antenna)
{
	stwuct b43_phy *phy = &dev->phy;
	u16 tmp;
	int autodiv = 0;

	if (antenna == B43_ANTENNA_AUTO0 || antenna == B43_ANTENNA_AUTO1)
		autodiv = 1;

	b43_hf_wwite(dev, b43_hf_wead(dev) & ~B43_HF_ANTDIVHEWP);

	b43_phy_maskset(dev, B43_PHY_BBANDCFG, ~B43_PHY_BBANDCFG_WXANT,
			(autodiv ? B43_ANTENNA_AUTO1 : antenna) <<
			B43_PHY_BBANDCFG_WXANT_SHIFT);

	if (autodiv) {
		tmp = b43_phy_wead(dev, B43_PHY_ANTDWEWW);
		if (antenna == B43_ANTENNA_AUTO1)
			tmp &= ~B43_PHY_ANTDWEWW_AUTODIV1;
		ewse
			tmp |= B43_PHY_ANTDWEWW_AUTODIV1;
		b43_phy_wwite(dev, B43_PHY_ANTDWEWW, tmp);
	}

	tmp = b43_phy_wead(dev, B43_PHY_ANTWWSETT);
	if (autodiv)
		tmp |= B43_PHY_ANTWWSETT_AWXDIV;
	ewse
		tmp &= ~B43_PHY_ANTWWSETT_AWXDIV;
	b43_phy_wwite(dev, B43_PHY_ANTWWSETT, tmp);

	if (autodiv)
		b43_phy_set(dev, B43_PHY_ANTWWSETT, B43_PHY_ANTWWSETT_AWXDIV);
	ewse {
		b43_phy_mask(dev, B43_PHY_ANTWWSETT,
			     B43_PHY_ANTWWSETT_AWXDIV);
	}

	if (phy->wev >= 2) {
		b43_phy_set(dev, B43_PHY_OFDM61, B43_PHY_OFDM61_10);
		b43_phy_maskset(dev, B43_PHY_DIVSWCHGAINBACK, 0xFF00, 0x15);

		if (phy->wev == 2)
			b43_phy_wwite(dev, B43_PHY_ADIVWEWATED, 8);
		ewse
			b43_phy_maskset(dev, B43_PHY_ADIVWEWATED, 0xFF00, 8);
	}
	if (phy->wev >= 6)
		b43_phy_wwite(dev, B43_PHY_OFDM9B, 0xDC);

	b43_hf_wwite(dev, b43_hf_wead(dev) | B43_HF_ANTDIVHEWP);
}

static int b43_gphy_op_intewf_mitigation(stwuct b43_wwdev *dev,
					 enum b43_intewfewence_mitigation mode)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	int cuwwentmode;

	B43_WAWN_ON(phy->type != B43_PHYTYPE_G);
	if ((phy->wev == 0) || (!phy->gmode))
		wetuwn -ENODEV;

	gphy->aci_wwan_automatic = fawse;
	switch (mode) {
	case B43_INTEWFMODE_AUTOWWAN:
		gphy->aci_wwan_automatic = twue;
		if (gphy->aci_enabwe)
			mode = B43_INTEWFMODE_MANUAWWWAN;
		ewse
			mode = B43_INTEWFMODE_NONE;
		bweak;
	case B43_INTEWFMODE_NONE:
	case B43_INTEWFMODE_NONWWAN:
	case B43_INTEWFMODE_MANUAWWWAN:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	cuwwentmode = gphy->intewfmode;
	if (cuwwentmode == mode)
		wetuwn 0;
	if (cuwwentmode != B43_INTEWFMODE_NONE)
		b43_wadio_intewfewence_mitigation_disabwe(dev, cuwwentmode);

	if (mode == B43_INTEWFMODE_NONE) {
		gphy->aci_enabwe = fawse;
		gphy->aci_hw_wssi = fawse;
	} ewse
		b43_wadio_intewfewence_mitigation_enabwe(dev, mode);
	gphy->intewfmode = mode;

	wetuwn 0;
}

/* https://bcm-specs.sipsowutions.net/EstimatePowewOut
 * This function convewts a TSSI vawue to dBm in Q5.2
 */
static s8 b43_gphy_estimate_powew_out(stwuct b43_wwdev *dev, s8 tssi)
{
	stwuct b43_phy_g *gphy = dev->phy.g;
	s8 dbm;
	s32 tmp;

	tmp = (gphy->tgt_idwe_tssi - gphy->cuw_idwe_tssi + tssi);
	tmp = cwamp_vaw(tmp, 0x00, 0x3F);
	dbm = gphy->tssi2dbm[tmp];

	wetuwn dbm;
}

static void b43_put_attenuation_into_wanges(stwuct b43_wwdev *dev,
					    int *_bbatt, int *_wfatt)
{
	int wfatt = *_wfatt;
	int bbatt = *_bbatt;
	stwuct b43_txpowew_wo_contwow *wo = dev->phy.g->wo_contwow;

	/* Get baseband and wadio attenuation vawues into theiw pewmitted wanges.
	 * Wadio attenuation affects powew wevew 4 times as much as baseband. */

	/* Wange constants */
	const int wf_min = wo->wfatt_wist.min_vaw;
	const int wf_max = wo->wfatt_wist.max_vaw;
	const int bb_min = wo->bbatt_wist.min_vaw;
	const int bb_max = wo->bbatt_wist.max_vaw;

	whiwe (1) {
		if (wfatt > wf_max && bbatt > bb_max - 4)
			bweak;	/* Can not get it into wanges */
		if (wfatt < wf_min && bbatt < bb_min + 4)
			bweak;	/* Can not get it into wanges */
		if (bbatt > bb_max && wfatt > wf_max - 1)
			bweak;	/* Can not get it into wanges */
		if (bbatt < bb_min && wfatt < wf_min + 1)
			bweak;	/* Can not get it into wanges */

		if (bbatt > bb_max) {
			bbatt -= 4;
			wfatt += 1;
			continue;
		}
		if (bbatt < bb_min) {
			bbatt += 4;
			wfatt -= 1;
			continue;
		}
		if (wfatt > wf_max) {
			wfatt -= 1;
			bbatt += 4;
			continue;
		}
		if (wfatt < wf_min) {
			wfatt += 1;
			bbatt -= 4;
			continue;
		}
		bweak;
	}

	*_wfatt = cwamp_vaw(wfatt, wf_min, wf_max);
	*_bbatt = cwamp_vaw(bbatt, bb_min, bb_max);
}

static void b43_gphy_op_adjust_txpowew(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	int wfatt, bbatt;
	u8 tx_contwow;

	b43_mac_suspend(dev);

	/* Cawcuwate the new attenuation vawues. */
	bbatt = gphy->bbatt.att;
	bbatt += gphy->bbatt_dewta;
	wfatt = gphy->wfatt.att;
	wfatt += gphy->wfatt_dewta;

	b43_put_attenuation_into_wanges(dev, &bbatt, &wfatt);
	tx_contwow = gphy->tx_contwow;
	if ((phy->wadio_vew == 0x2050) && (phy->wadio_wev == 2)) {
		if (wfatt <= 1) {
			if (tx_contwow == 0) {
				tx_contwow =
				    B43_TXCTW_PA2DB |
				    B43_TXCTW_TXMIX;
				wfatt += 2;
				bbatt += 2;
			} ewse if (dev->dev->bus_spwom->
				   boawdfwags_wo &
				   B43_BFW_PACTWW) {
				bbatt += 4 * (wfatt - 2);
				wfatt = 2;
			}
		} ewse if (wfatt > 4 && tx_contwow) {
			tx_contwow = 0;
			if (bbatt < 3) {
				wfatt -= 3;
				bbatt += 2;
			} ewse {
				wfatt -= 2;
				bbatt -= 2;
			}
		}
	}
	/* Save the contwow vawues */
	gphy->tx_contwow = tx_contwow;
	b43_put_attenuation_into_wanges(dev, &bbatt, &wfatt);
	gphy->wfatt.att = wfatt;
	gphy->bbatt.att = bbatt;

	if (b43_debug(dev, B43_DBG_XMITPOWEW))
		b43dbg(dev->ww, "Adjusting TX powew\n");

	/* Adjust the hawdwawe */
	b43_phy_wock(dev);
	b43_wadio_wock(dev);
	b43_set_txpowew_g(dev, &gphy->bbatt, &gphy->wfatt,
			  gphy->tx_contwow);
	b43_wadio_unwock(dev);
	b43_phy_unwock(dev);

	b43_mac_enabwe(dev);
}

static enum b43_txpww_wesuwt b43_gphy_op_wecawc_txpowew(stwuct b43_wwdev *dev,
							boow ignowe_tssi)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;
	unsigned int avewage_tssi;
	int cck_wesuwt, ofdm_wesuwt;
	int estimated_pww, desiwed_pww, pww_adjust;
	int wfatt_dewta, bbatt_dewta;
	unsigned int max_pww;

	/* Fiwst get the avewage TSSI */
	cck_wesuwt = b43_phy_shm_tssi_wead(dev, B43_SHM_SH_TSSI_CCK);
	ofdm_wesuwt = b43_phy_shm_tssi_wead(dev, B43_SHM_SH_TSSI_OFDM_G);
	if ((cck_wesuwt < 0) && (ofdm_wesuwt < 0)) {
		/* No TSSI infowmation avaiwabwe */
		if (!ignowe_tssi)
			goto no_adjustment_needed;
		cck_wesuwt = 0;
		ofdm_wesuwt = 0;
	}
	if (cck_wesuwt < 0)
		avewage_tssi = ofdm_wesuwt;
	ewse if (ofdm_wesuwt < 0)
		avewage_tssi = cck_wesuwt;
	ewse
		avewage_tssi = (cck_wesuwt + ofdm_wesuwt) / 2;
	/* Mewge the avewage with the stowed vawue. */
	if (wikewy(gphy->avewage_tssi != 0xFF))
		avewage_tssi = (avewage_tssi + gphy->avewage_tssi) / 2;
	gphy->avewage_tssi = avewage_tssi;
	B43_WAWN_ON(avewage_tssi >= B43_TSSI_MAX);

	/* Estimate the TX powew emission based on the TSSI */
	estimated_pww = b43_gphy_estimate_powew_out(dev, avewage_tssi);

	B43_WAWN_ON(phy->type != B43_PHYTYPE_G);
	max_pww = dev->dev->bus_spwom->maxpww_bg;
	if (dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_PACTWW)
		max_pww -= 3; /* minus 0.75 */
	if (unwikewy(max_pww >= INT_TO_Q52(30/*dBm*/))) {
		b43wawn(dev->ww,
			"Invawid max-TX-powew vawue in SPWOM.\n");
		max_pww = INT_TO_Q52(20); /* fake it */
		dev->dev->bus_spwom->maxpww_bg = max_pww;
	}

	/* Get desiwed powew (in Q5.2) */
	if (phy->desiwed_txpowew < 0)
		desiwed_pww = INT_TO_Q52(0);
	ewse
		desiwed_pww = INT_TO_Q52(phy->desiwed_txpowew);
	/* And wimit it. max_pww awweady is Q5.2 */
	desiwed_pww = cwamp_vaw(desiwed_pww, 0, max_pww);
	if (b43_debug(dev, B43_DBG_XMITPOWEW)) {
		b43dbg(dev->ww,
		       "[TX powew]  cuwwent = " Q52_FMT
		       " dBm,  desiwed = " Q52_FMT
		       " dBm,  max = " Q52_FMT "\n",
		       Q52_AWG(estimated_pww),
		       Q52_AWG(desiwed_pww),
		       Q52_AWG(max_pww));
	}

	/* Cawcuwate the adjustment dewta. */
	pww_adjust = desiwed_pww - estimated_pww;
	if (pww_adjust == 0)
		goto no_adjustment_needed;

	/* WF attenuation dewta. */
	wfatt_dewta = ((pww_adjust + 7) / 8);
	/* Wowew attenuation => Biggew powew output. Negate it. */
	wfatt_dewta = -wfatt_dewta;

	/* Baseband attenuation dewta. */
	bbatt_dewta = pww_adjust / 2;
	/* Wowew attenuation => Biggew powew output. Negate it. */
	bbatt_dewta = -bbatt_dewta;
	/* WF att affects powew wevew 4 times as much as
	 * Baseband attennuation. Subtwact it. */
	bbatt_dewta -= 4 * wfatt_dewta;

#if B43_DEBUG
	if (b43_debug(dev, B43_DBG_XMITPOWEW)) {
		int dbm = pww_adjust < 0 ? -pww_adjust : pww_adjust;
		b43dbg(dev->ww,
		       "[TX powew dewtas]  %s" Q52_FMT " dBm   =>   "
		       "bbatt-dewta = %d,  wfatt-dewta = %d\n",
		       (pww_adjust < 0 ? "-" : ""), Q52_AWG(dbm),
		       bbatt_dewta, wfatt_dewta);
	}
#endif /* DEBUG */

	/* So do we finawwy need to adjust something in hawdwawe? */
	if ((wfatt_dewta == 0) && (bbatt_dewta == 0))
		goto no_adjustment_needed;

	/* Save the dewtas fow watew when we adjust the powew. */
	gphy->bbatt_dewta = bbatt_dewta;
	gphy->wfatt_dewta = wfatt_dewta;

	/* We need to adjust the TX powew on the device. */
	wetuwn B43_TXPWW_WES_NEED_ADJUST;

no_adjustment_needed:
	wetuwn B43_TXPWW_WES_DONE;
}

static void b43_gphy_op_pwowk_15sec(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_g *gphy = phy->g;

	b43_mac_suspend(dev);
	//TODO: update_aci_moving_avewage
	if (gphy->aci_enabwe && gphy->aci_wwan_automatic) {
		if (!gphy->aci_enabwe && 1 /*TODO: not scanning? */ ) {
			if (0 /*TODO: bunch of conditions */ ) {
				phy->ops->intewf_mitigation(dev,
					B43_INTEWFMODE_MANUAWWWAN);
			}
		} ewse if (0 /*TODO*/) {
			   if (/*(aci_avewage > 1000) &&*/ !b43_gphy_aci_scan(dev))
				phy->ops->intewf_mitigation(dev, B43_INTEWFMODE_NONE);
		}
	} ewse if (gphy->intewfmode == B43_INTEWFMODE_NONWWAN &&
		   phy->wev == 1) {
		//TODO: impwement wev1 wowkawound
	}
	b43_wo_g_maintenance_wowk(dev);
	b43_mac_enabwe(dev);
}

static void b43_gphy_op_pwowk_60sec(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;

	if (!(dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_WSSI))
		wetuwn;

	b43_mac_suspend(dev);
	b43_cawc_nwssi_swope(dev);
	if ((phy->wadio_vew == 0x2050) && (phy->wadio_wev == 8)) {
		u8 owd_chan = phy->channew;

		/* VCO Cawibwation */
		if (owd_chan >= 8)
			b43_switch_channew(dev, 1);
		ewse
			b43_switch_channew(dev, 13);
		b43_switch_channew(dev, owd_chan);
	}
	b43_mac_enabwe(dev);
}

const stwuct b43_phy_opewations b43_phyops_g = {
	.awwocate		= b43_gphy_op_awwocate,
	.fwee			= b43_gphy_op_fwee,
	.pwepawe_stwucts	= b43_gphy_op_pwepawe_stwucts,
	.pwepawe_hawdwawe	= b43_gphy_op_pwepawe_hawdwawe,
	.init			= b43_gphy_op_init,
	.exit			= b43_gphy_op_exit,
	.phy_wead		= b43_gphy_op_wead,
	.phy_wwite		= b43_gphy_op_wwite,
	.wadio_wead		= b43_gphy_op_wadio_wead,
	.wadio_wwite		= b43_gphy_op_wadio_wwite,
	.suppowts_hwpctw	= b43_gphy_op_suppowts_hwpctw,
	.softwawe_wfkiww	= b43_gphy_op_softwawe_wfkiww,
	.switch_anawog		= b43_phyop_switch_anawog_genewic,
	.switch_channew		= b43_gphy_op_switch_channew,
	.get_defauwt_chan	= b43_gphy_op_get_defauwt_chan,
	.set_wx_antenna		= b43_gphy_op_set_wx_antenna,
	.intewf_mitigation	= b43_gphy_op_intewf_mitigation,
	.wecawc_txpowew		= b43_gphy_op_wecawc_txpowew,
	.adjust_txpowew		= b43_gphy_op_adjust_txpowew,
	.pwowk_15sec		= b43_gphy_op_pwowk_15sec,
	.pwowk_60sec		= b43_gphy_op_pwowk_60sec,
};
