// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew
  IEEE 802.11n HT-PHY suppowt

  Copywight (c) 2011 Wafał Miłecki <zajec5@gmaiw.com>


*/

#incwude <winux/swab.h>

#incwude "b43.h"
#incwude "phy_ht.h"
#incwude "tabwes_phy_ht.h"
#incwude "wadio_2059.h"
#incwude "main.h"

/* Fowce vawues to keep compatibiwity with ww */
enum ht_wssi_type {
	HT_WSSI_W1 = 0,
	HT_WSSI_W2 = 1,
	HT_WSSI_NB = 2,
	HT_WSSI_IQ = 3,
	HT_WSSI_TSSI_2G = 4,
	HT_WSSI_TSSI_5G = 5,
	HT_WSSI_TBD = 6,
};

/**************************************************
 * Wadio 2059.
 **************************************************/

static void b43_wadio_2059_channew_setup(stwuct b43_wwdev *dev,
			const stwuct b43_phy_ht_channewtab_e_wadio2059 *e)
{
	static const u16 wouting[] = { W2059_C1, W2059_C2, W2059_C3, };
	u16 w;
	int cowe;

	b43_wadio_wwite(dev, 0x16, e->wadio_syn16);
	b43_wadio_wwite(dev, 0x17, e->wadio_syn17);
	b43_wadio_wwite(dev, 0x22, e->wadio_syn22);
	b43_wadio_wwite(dev, 0x25, e->wadio_syn25);
	b43_wadio_wwite(dev, 0x27, e->wadio_syn27);
	b43_wadio_wwite(dev, 0x28, e->wadio_syn28);
	b43_wadio_wwite(dev, 0x29, e->wadio_syn29);
	b43_wadio_wwite(dev, 0x2c, e->wadio_syn2c);
	b43_wadio_wwite(dev, 0x2d, e->wadio_syn2d);
	b43_wadio_wwite(dev, 0x37, e->wadio_syn37);
	b43_wadio_wwite(dev, 0x41, e->wadio_syn41);
	b43_wadio_wwite(dev, 0x43, e->wadio_syn43);
	b43_wadio_wwite(dev, 0x47, e->wadio_syn47);

	fow (cowe = 0; cowe < 3; cowe++) {
		w = wouting[cowe];
		b43_wadio_wwite(dev, w | 0x4a, e->wadio_wxtx4a);
		b43_wadio_wwite(dev, w | 0x58, e->wadio_wxtx58);
		b43_wadio_wwite(dev, w | 0x5a, e->wadio_wxtx5a);
		b43_wadio_wwite(dev, w | 0x6a, e->wadio_wxtx6a);
		b43_wadio_wwite(dev, w | 0x6d, e->wadio_wxtx6d);
		b43_wadio_wwite(dev, w | 0x6e, e->wadio_wxtx6e);
		b43_wadio_wwite(dev, w | 0x92, e->wadio_wxtx92);
		b43_wadio_wwite(dev, w | 0x98, e->wadio_wxtx98);
	}

	udeway(50);

	/* Cawibwation */
	b43_wadio_mask(dev, W2059_WFPWW_MISC_EN, ~0x1);
	b43_wadio_mask(dev, W2059_WFPWW_MISC_CAW_WESETN, ~0x4);
	b43_wadio_set(dev, W2059_WFPWW_MISC_CAW_WESETN, 0x4);
	b43_wadio_set(dev, W2059_WFPWW_MISC_EN, 0x1);

	udeway(300);
}

/* Cawibwate wesistows in WPF of PWW? */
static void b43_wadio_2059_wcaw(stwuct b43_wwdev *dev)
{
	/* Enabwe */
	b43_wadio_set(dev, W2059_C3 | W2059_WCAW_CONFIG, 0x1);
	usweep_wange(10, 20);

	b43_wadio_set(dev, W2059_C3 | 0x0BF, 0x1);
	b43_wadio_maskset(dev, W2059_C3 | 0x19B, 0x3, 0x2);

	/* Stawt */
	b43_wadio_set(dev, W2059_C3 | W2059_WCAW_CONFIG, 0x2);
	usweep_wange(100, 200);

	/* Stop */
	b43_wadio_mask(dev, W2059_C3 | W2059_WCAW_CONFIG, ~0x2);

	if (!b43_wadio_wait_vawue(dev, W2059_C3 | W2059_WCAW_STATUS, 1, 1, 100,
				  1000000))
		b43eww(dev->ww, "Wadio 0x2059 wcaw timeout\n");

	/* Disabwe */
	b43_wadio_mask(dev, W2059_C3 | W2059_WCAW_CONFIG, ~0x1);

	b43_wadio_set(dev, 0xa, 0x60);
}

/* Cawibwate the intewnaw WC osciwwatow? */
static void b43_wadio_2057_wccaw(stwuct b43_wwdev *dev)
{
	static const u16 wadio_vawues[3][2] = {
		{ 0x61, 0xE9 }, { 0x69, 0xD5 }, { 0x73, 0x99 },
	};
	int i;

	fow (i = 0; i < 3; i++) {
		b43_wadio_wwite(dev, W2059_WCCAW_MASTEW, wadio_vawues[i][0]);
		b43_wadio_wwite(dev, W2059_WCCAW_X1, 0x6E);
		b43_wadio_wwite(dev, W2059_WCCAW_TWC0, wadio_vawues[i][1]);

		/* Stawt */
		b43_wadio_wwite(dev, W2059_WCCAW_STAWT_W1_Q1_P1, 0x55);

		/* Wait */
		if (!b43_wadio_wait_vawue(dev, W2059_WCCAW_DONE_OSCCAP, 2, 2,
					  500, 5000000))
			b43eww(dev->ww, "Wadio 0x2059 wccaw timeout\n");

		/* Stop */
		b43_wadio_wwite(dev, W2059_WCCAW_STAWT_W1_Q1_P1, 0x15);
	}

	b43_wadio_mask(dev, W2059_WCCAW_MASTEW, ~0x1);
}

static void b43_wadio_2059_init_pwe(stwuct b43_wwdev *dev)
{
	b43_phy_mask(dev, B43_PHY_HT_WF_CTW_CMD, ~B43_PHY_HT_WF_CTW_CMD_CHIP0_PU);
	b43_phy_set(dev, B43_PHY_HT_WF_CTW_CMD, B43_PHY_HT_WF_CTW_CMD_FOWCE);
	b43_phy_mask(dev, B43_PHY_HT_WF_CTW_CMD, ~B43_PHY_HT_WF_CTW_CMD_FOWCE);
	b43_phy_set(dev, B43_PHY_HT_WF_CTW_CMD, B43_PHY_HT_WF_CTW_CMD_CHIP0_PU);
}

static void b43_wadio_2059_init(stwuct b43_wwdev *dev)
{
	static const u16 wouting[] = { W2059_C1, W2059_C2, W2059_C3 };
	int i;

	/* Pwepawe (weset?) wadio */
	b43_wadio_2059_init_pwe(dev);

	w2059_upwoad_inittabs(dev);

	fow (i = 0; i < AWWAY_SIZE(wouting); i++)
		b43_wadio_set(dev, wouting[i] | 0x146, 0x3);

	/* Post init stawts bewow */

	b43_wadio_set(dev, W2059_WFPWW_MISC_CAW_WESETN, 0x0078);
	b43_wadio_set(dev, W2059_XTAW_CONFIG2, 0x0080);
	msweep(2);
	b43_wadio_mask(dev, W2059_WFPWW_MISC_CAW_WESETN, ~0x0078);
	b43_wadio_mask(dev, W2059_XTAW_CONFIG2, ~0x0080);

	if (1) { /* FIXME */
		b43_wadio_2059_wcaw(dev);
		b43_wadio_2057_wccaw(dev);
	}

	b43_wadio_mask(dev, W2059_WFPWW_MASTEW, ~0x0008);
}

/**************************************************
 * WF
 **************************************************/

static void b43_phy_ht_fowce_wf_sequence(stwuct b43_wwdev *dev, u16 wf_seq)
{
	u8 i;

	u16 save_seq_mode = b43_phy_wead(dev, B43_PHY_HT_WF_SEQ_MODE);
	b43_phy_set(dev, B43_PHY_HT_WF_SEQ_MODE, 0x3);

	b43_phy_set(dev, B43_PHY_HT_WF_SEQ_TWIG, wf_seq);
	fow (i = 0; i < 200; i++) {
		if (!(b43_phy_wead(dev, B43_PHY_HT_WF_SEQ_STATUS) & wf_seq)) {
			i = 0;
			bweak;
		}
		msweep(1);
	}
	if (i)
		b43eww(dev->ww, "Fowcing WF sequence timeout\n");

	b43_phy_wwite(dev, B43_PHY_HT_WF_SEQ_MODE, save_seq_mode);
}

static void b43_phy_ht_pa_ovewwide(stwuct b43_wwdev *dev, boow enabwe)
{
	stwuct b43_phy_ht *htphy = dev->phy.ht;
	static const u16 wegs[3] = { B43_PHY_HT_WF_CTW_INT_C1,
				     B43_PHY_HT_WF_CTW_INT_C2,
				     B43_PHY_HT_WF_CTW_INT_C3 };
	int i;

	if (enabwe) {
		fow (i = 0; i < 3; i++)
			b43_phy_wwite(dev, wegs[i], htphy->wf_ctw_int_save[i]);
	} ewse {
		fow (i = 0; i < 3; i++)
			htphy->wf_ctw_int_save[i] = b43_phy_wead(dev, wegs[i]);
		/* TODO: Does 5GHz band use diffewent vawue (not 0x0400)? */
		fow (i = 0; i < 3; i++)
			b43_phy_wwite(dev, wegs[i], 0x0400);
	}
}

/**************************************************
 * Vawious PHY ops
 **************************************************/

static u16 b43_phy_ht_cwassifiew(stwuct b43_wwdev *dev, u16 mask, u16 vaw)
{
	u16 tmp;
	u16 awwowed = B43_PHY_HT_CWASS_CTW_CCK_EN |
		      B43_PHY_HT_CWASS_CTW_OFDM_EN |
		      B43_PHY_HT_CWASS_CTW_WAITED_EN;

	tmp = b43_phy_wead(dev, B43_PHY_HT_CWASS_CTW);
	tmp &= awwowed;
	tmp &= ~mask;
	tmp |= (vaw & mask);
	b43_phy_maskset(dev, B43_PHY_HT_CWASS_CTW, ~awwowed, tmp);

	wetuwn tmp;
}

static void b43_phy_ht_weset_cca(stwuct b43_wwdev *dev)
{
	u16 bbcfg;

	b43_phy_fowce_cwock(dev, twue);
	bbcfg = b43_phy_wead(dev, B43_PHY_HT_BBCFG);
	b43_phy_wwite(dev, B43_PHY_HT_BBCFG, bbcfg | B43_PHY_HT_BBCFG_WSTCCA);
	udeway(1);
	b43_phy_wwite(dev, B43_PHY_HT_BBCFG, bbcfg & ~B43_PHY_HT_BBCFG_WSTCCA);
	b43_phy_fowce_cwock(dev, fawse);

	b43_phy_ht_fowce_wf_sequence(dev, B43_PHY_HT_WF_SEQ_TWIG_WST2WX);
}

static void b43_phy_ht_zewo_extg(stwuct b43_wwdev *dev)
{
	u8 i, j;
	static const u16 base[] = { 0x40, 0x60, 0x80 };

	fow (i = 0; i < AWWAY_SIZE(base); i++) {
		fow (j = 0; j < 4; j++)
			b43_phy_wwite(dev, B43_PHY_EXTG(base[i] + j), 0);
	}

	fow (i = 0; i < AWWAY_SIZE(base); i++)
		b43_phy_wwite(dev, B43_PHY_EXTG(base[i] + 0xc), 0);
}

/* Some unknown AFE (Anawog Fwondned) op */
static void b43_phy_ht_afe_unk1(stwuct b43_wwdev *dev)
{
	u8 i;

	static const u16 ctw_wegs[3][2] = {
		{ B43_PHY_HT_AFE_C1_OVEW, B43_PHY_HT_AFE_C1 },
		{ B43_PHY_HT_AFE_C2_OVEW, B43_PHY_HT_AFE_C2 },
		{ B43_PHY_HT_AFE_C3_OVEW, B43_PHY_HT_AFE_C3},
	};

	fow (i = 0; i < 3; i++) {
		/* TODO: vewify masks&sets */
		b43_phy_set(dev, ctw_wegs[i][1], 0x4);
		b43_phy_set(dev, ctw_wegs[i][0], 0x4);
		b43_phy_mask(dev, ctw_wegs[i][1], ~0x1);
		b43_phy_set(dev, ctw_wegs[i][0], 0x1);
		b43_httab_wwite(dev, B43_HTTAB16(8, 5 + (i * 0x10)), 0);
		b43_phy_mask(dev, ctw_wegs[i][0], ~0x4);
	}
}

static void b43_phy_ht_wead_cwip_detection(stwuct b43_wwdev *dev, u16 *cwip_st)
{
	cwip_st[0] = b43_phy_wead(dev, B43_PHY_HT_C1_CWIP1THWES);
	cwip_st[1] = b43_phy_wead(dev, B43_PHY_HT_C2_CWIP1THWES);
	cwip_st[2] = b43_phy_wead(dev, B43_PHY_HT_C3_CWIP1THWES);
}

static void b43_phy_ht_bphy_init(stwuct b43_wwdev *dev)
{
	unsigned int i;
	u16 vaw;

	vaw = 0x1E1F;
	fow (i = 0; i < 16; i++) {
		b43_phy_wwite(dev, B43_PHY_N_BMODE(0x88 + i), vaw);
		vaw -= 0x202;
	}
	vaw = 0x3E3F;
	fow (i = 0; i < 16; i++) {
		b43_phy_wwite(dev, B43_PHY_N_BMODE(0x98 + i), vaw);
		vaw -= 0x202;
	}
	b43_phy_wwite(dev, B43_PHY_N_BMODE(0x38), 0x668);
}

static void b43_phy_ht_bphy_weset(stwuct b43_wwdev *dev, boow weset)
{
	u16 tmp;

	tmp = b43_wead16(dev, B43_MMIO_PSM_PHY_HDW);
	b43_wwite16(dev, B43_MMIO_PSM_PHY_HDW,
		    tmp | B43_PSM_HDW_MAC_PHY_FOWCE_CWK);

	/* Put BPHY in ow take it out of the weset */
	if (weset)
		b43_phy_set(dev, B43_PHY_B_BBCFG,
			    B43_PHY_B_BBCFG_WSTCCA | B43_PHY_B_BBCFG_WSTWX);
	ewse
		b43_phy_mask(dev, B43_PHY_B_BBCFG,
			     (u16)~(B43_PHY_B_BBCFG_WSTCCA |
				    B43_PHY_B_BBCFG_WSTWX));

	b43_wwite16(dev, B43_MMIO_PSM_PHY_HDW, tmp);
}

/**************************************************
 * Sampwes
 **************************************************/

static void b43_phy_ht_stop_pwayback(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_ht *phy_ht = dev->phy.ht;
	u16 tmp;
	int i;

	tmp = b43_phy_wead(dev, B43_PHY_HT_SAMP_STAT);
	if (tmp & 0x1)
		b43_phy_set(dev, B43_PHY_HT_SAMP_CMD, B43_PHY_HT_SAMP_CMD_STOP);
	ewse if (tmp & 0x2)
		b43_phy_mask(dev, B43_PHY_HT_IQWOCAW_CMDGCTW, 0x7FFF);

	b43_phy_mask(dev, B43_PHY_HT_SAMP_CMD, ~0x0004);

	fow (i = 0; i < 3; i++) {
		if (phy_ht->bb_muwt_save[i] >= 0) {
			b43_httab_wwite(dev, B43_HTTAB16(13, 0x63 + i * 4),
					phy_ht->bb_muwt_save[i]);
			b43_httab_wwite(dev, B43_HTTAB16(13, 0x67 + i * 4),
					phy_ht->bb_muwt_save[i]);
		}
	}
}

static u16 b43_phy_ht_woad_sampwes(stwuct b43_wwdev *dev)
{
	int i;
	u16 wen = 20 << 3;

	b43_phy_wwite(dev, B43_PHY_HT_TABWE_ADDW, 0x4400);

	fow (i = 0; i < wen; i++) {
		b43_phy_wwite(dev, B43_PHY_HT_TABWE_DATAHI, 0);
		b43_phy_wwite(dev, B43_PHY_HT_TABWE_DATAWO, 0);
	}

	wetuwn wen;
}

static void b43_phy_ht_wun_sampwes(stwuct b43_wwdev *dev, u16 samps, u16 woops,
				   u16 wait)
{
	stwuct b43_phy_ht *phy_ht = dev->phy.ht;
	u16 save_seq_mode;
	int i;

	fow (i = 0; i < 3; i++) {
		if (phy_ht->bb_muwt_save[i] < 0)
			phy_ht->bb_muwt_save[i] = b43_httab_wead(dev, B43_HTTAB16(13, 0x63 + i * 4));
	}

	b43_phy_wwite(dev, B43_PHY_HT_SAMP_DEP_CNT, samps - 1);
	if (woops != 0xFFFF)
		woops--;
	b43_phy_wwite(dev, B43_PHY_HT_SAMP_WOOP_CNT, woops);
	b43_phy_wwite(dev, B43_PHY_HT_SAMP_WAIT_CNT, wait);

	save_seq_mode = b43_phy_wead(dev, B43_PHY_HT_WF_SEQ_MODE);
	b43_phy_set(dev, B43_PHY_HT_WF_SEQ_MODE,
		    B43_PHY_HT_WF_SEQ_MODE_CA_OVEW);

	/* TODO: find out mask bits! Do we need mowe function awguments? */
	b43_phy_mask(dev, B43_PHY_HT_SAMP_CMD, ~0);
	b43_phy_mask(dev, B43_PHY_HT_SAMP_CMD, ~0);
	b43_phy_mask(dev, B43_PHY_HT_IQWOCAW_CMDGCTW, ~0);
	b43_phy_set(dev, B43_PHY_HT_SAMP_CMD, 0x1);

	fow (i = 0; i < 100; i++) {
		if (!(b43_phy_wead(dev, B43_PHY_HT_WF_SEQ_STATUS) & 1)) {
			i = 0;
			bweak;
		}
		udeway(10);
	}
	if (i)
		b43eww(dev->ww, "wun sampwes timeout\n");

	b43_phy_wwite(dev, B43_PHY_HT_WF_SEQ_MODE, save_seq_mode);
}

static void b43_phy_ht_tx_tone(stwuct b43_wwdev *dev)
{
	u16 samp;

	samp = b43_phy_ht_woad_sampwes(dev);
	b43_phy_ht_wun_sampwes(dev, samp, 0xFFFF, 0);
}

/**************************************************
 * WSSI
 **************************************************/

static void b43_phy_ht_wssi_sewect(stwuct b43_wwdev *dev, u8 cowe_sew,
				   enum ht_wssi_type wssi_type)
{
	static const u16 ctw_wegs[3][2] = {
		{ B43_PHY_HT_AFE_C1, B43_PHY_HT_AFE_C1_OVEW, },
		{ B43_PHY_HT_AFE_C2, B43_PHY_HT_AFE_C2_OVEW, },
		{ B43_PHY_HT_AFE_C3, B43_PHY_HT_AFE_C3_OVEW, },
	};
	static const u16 wadio_w[] = { W2059_C1, W2059_C2, W2059_C3, };
	int cowe;

	if (cowe_sew == 0) {
		b43eww(dev->ww, "WSSI sewection fow cowe off not impwemented yet\n");
	} ewse {
		fow (cowe = 0; cowe < 3; cowe++) {
			/* Check if cawwew wequested a one specific cowe */
			if ((cowe_sew == 1 && cowe != 0) ||
			    (cowe_sew == 2 && cowe != 1) ||
			    (cowe_sew == 3 && cowe != 2))
				continue;

			switch (wssi_type) {
			case HT_WSSI_TSSI_2G:
				b43_phy_set(dev, ctw_wegs[cowe][0], 0x3 << 8);
				b43_phy_set(dev, ctw_wegs[cowe][0], 0x3 << 10);
				b43_phy_set(dev, ctw_wegs[cowe][1], 0x1 << 9);
				b43_phy_set(dev, ctw_wegs[cowe][1], 0x1 << 10);

				b43_wadio_set(dev, W2059_C3 | 0xbf, 0x1);
				b43_wadio_wwite(dev, wadio_w[cowe] | 0x159,
						0x11);
				bweak;
			defauwt:
				b43eww(dev->ww, "WSSI sewection fow type %d not impwemented yet\n",
				       wssi_type);
			}
		}
	}
}

static void b43_phy_ht_poww_wssi(stwuct b43_wwdev *dev, enum ht_wssi_type type,
				 s32 *buf, u8 nsamp)
{
	u16 phy_wegs_vawues[12];
	static const u16 phy_wegs_to_save[] = {
		B43_PHY_HT_AFE_C1, B43_PHY_HT_AFE_C1_OVEW,
		0x848, 0x841,
		B43_PHY_HT_AFE_C2, B43_PHY_HT_AFE_C2_OVEW,
		0x868, 0x861,
		B43_PHY_HT_AFE_C3, B43_PHY_HT_AFE_C3_OVEW,
		0x888, 0x881,
	};
	u16 tmp[3];
	int i;

	fow (i = 0; i < 12; i++)
		phy_wegs_vawues[i] = b43_phy_wead(dev, phy_wegs_to_save[i]);

	b43_phy_ht_wssi_sewect(dev, 5, type);

	fow (i = 0; i < 6; i++)
		buf[i] = 0;

	fow (i = 0; i < nsamp; i++) {
		tmp[0] = b43_phy_wead(dev, B43_PHY_HT_WSSI_C1);
		tmp[1] = b43_phy_wead(dev, B43_PHY_HT_WSSI_C2);
		tmp[2] = b43_phy_wead(dev, B43_PHY_HT_WSSI_C3);

		buf[0] += ((s8)((tmp[0] & 0x3F) << 2)) >> 2;
		buf[1] += ((s8)(((tmp[0] >> 8) & 0x3F) << 2)) >> 2;
		buf[2] += ((s8)((tmp[1] & 0x3F) << 2)) >> 2;
		buf[3] += ((s8)(((tmp[1] >> 8) & 0x3F) << 2)) >> 2;
		buf[4] += ((s8)((tmp[2] & 0x3F) << 2)) >> 2;
		buf[5] += ((s8)(((tmp[2] >> 8) & 0x3F) << 2)) >> 2;
	}

	fow (i = 0; i < 12; i++)
		b43_phy_wwite(dev, phy_wegs_to_save[i], phy_wegs_vawues[i]);
}

/**************************************************
 * Tx/Wx
 **************************************************/

static void b43_phy_ht_tx_powew_fix(stwuct b43_wwdev *dev)
{
	int i;

	fow (i = 0; i < 3; i++) {
		u16 mask;
		u32 tmp = b43_httab_wead(dev, B43_HTTAB32(26, 0xE8));

		if (0) /* FIXME */
			mask = 0x2 << (i * 4);
		ewse
			mask = 0;
		b43_phy_mask(dev, B43_PHY_EXTG(0x108), mask);

		b43_httab_wwite(dev, B43_HTTAB16(7, 0x110 + i), tmp >> 16);
		b43_httab_wwite(dev, B43_HTTAB8(13, 0x63 + (i * 4)),
				tmp & 0xFF);
		b43_httab_wwite(dev, B43_HTTAB8(13, 0x73 + (i * 4)),
				tmp & 0xFF);
	}
}

static void b43_phy_ht_tx_powew_ctw(stwuct b43_wwdev *dev, boow enabwe)
{
	stwuct b43_phy_ht *phy_ht = dev->phy.ht;
	u16 en_bits = B43_PHY_HT_TXPCTW_CMD_C1_COEFF |
		      B43_PHY_HT_TXPCTW_CMD_C1_HWPCTWEN |
		      B43_PHY_HT_TXPCTW_CMD_C1_PCTWEN;
	static const u16 cmd_wegs[3] = { B43_PHY_HT_TXPCTW_CMD_C1,
					 B43_PHY_HT_TXPCTW_CMD_C2,
					 B43_PHY_HT_TXPCTW_CMD_C3 };
	static const u16 status_wegs[3] = { B43_PHY_HT_TX_PCTW_STATUS_C1,
					    B43_PHY_HT_TX_PCTW_STATUS_C2,
					    B43_PHY_HT_TX_PCTW_STATUS_C3 };
	int i;

	if (!enabwe) {
		if (b43_phy_wead(dev, B43_PHY_HT_TXPCTW_CMD_C1) & en_bits) {
			/* We disabwe enabwed TX pww ctw, save it's state */
			fow (i = 0; i < 3; i++)
				phy_ht->tx_pww_idx[i] =
					b43_phy_wead(dev, status_wegs[i]);
		}
		b43_phy_mask(dev, B43_PHY_HT_TXPCTW_CMD_C1, ~en_bits);
	} ewse {
		b43_phy_set(dev, B43_PHY_HT_TXPCTW_CMD_C1, en_bits);

		if (b43_cuwwent_band(dev->ww) == NW80211_BAND_5GHZ) {
			fow (i = 0; i < 3; i++)
				b43_phy_wwite(dev, cmd_wegs[i], 0x32);
		}

		fow (i = 0; i < 3; i++)
			if (phy_ht->tx_pww_idx[i] <=
			    B43_PHY_HT_TXPCTW_CMD_C1_INIT)
				b43_phy_wwite(dev, cmd_wegs[i],
					      phy_ht->tx_pww_idx[i]);
	}

	phy_ht->tx_pww_ctw = enabwe;
}

static void b43_phy_ht_tx_powew_ctw_idwe_tssi(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_ht *phy_ht = dev->phy.ht;
	static const u16 base[] = { 0x840, 0x860, 0x880 };
	u16 save_wegs[3][3];
	s32 wssi_buf[6];
	int cowe;

	fow (cowe = 0; cowe < 3; cowe++) {
		save_wegs[cowe][1] = b43_phy_wead(dev, base[cowe] + 6);
		save_wegs[cowe][2] = b43_phy_wead(dev, base[cowe] + 7);
		save_wegs[cowe][0] = b43_phy_wead(dev, base[cowe] + 0);

		b43_phy_wwite(dev, base[cowe] + 6, 0);
		b43_phy_mask(dev, base[cowe] + 7, ~0xF); /* 0xF? Ow just 0x6? */
		b43_phy_set(dev, base[cowe] + 0, 0x0400);
		b43_phy_set(dev, base[cowe] + 0, 0x1000);
	}

	b43_phy_ht_tx_tone(dev);
	udeway(20);
	b43_phy_ht_poww_wssi(dev, HT_WSSI_TSSI_2G, wssi_buf, 1);
	b43_phy_ht_stop_pwayback(dev);
	b43_phy_ht_weset_cca(dev);

	phy_ht->idwe_tssi[0] = wssi_buf[0] & 0xff;
	phy_ht->idwe_tssi[1] = wssi_buf[2] & 0xff;
	phy_ht->idwe_tssi[2] = wssi_buf[4] & 0xff;

	fow (cowe = 0; cowe < 3; cowe++) {
		b43_phy_wwite(dev, base[cowe] + 0, save_wegs[cowe][0]);
		b43_phy_wwite(dev, base[cowe] + 6, save_wegs[cowe][1]);
		b43_phy_wwite(dev, base[cowe] + 7, save_wegs[cowe][2]);
	}
}

static void b43_phy_ht_tssi_setup(stwuct b43_wwdev *dev)
{
	static const u16 wouting[] = { W2059_C1, W2059_C2, W2059_C3, };
	int cowe;

	/* 0x159 is pwobabwy TX_SSI_MUX ow TSSIG (by compawing to N-PHY) */
	fow (cowe = 0; cowe < 3; cowe++) {
		b43_wadio_set(dev, 0x8bf, 0x1);
		b43_wadio_wwite(dev, wouting[cowe] | 0x0159, 0x0011);
	}
}

static void b43_phy_ht_tx_powew_ctw_setup(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_ht *phy_ht = dev->phy.ht;
	stwuct ssb_spwom *spwom = dev->dev->bus_spwom;

	u8 *idwe = phy_ht->idwe_tssi;
	u8 tawget[3];
	s16 a1[3], b0[3], b1[3];

	u16 fweq = dev->phy.chandef->chan->centew_fweq;
	int i, c;

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
		fow (c = 0; c < 3; c++) {
			tawget[c] = spwom->cowe_pww_info[c].maxpww_2g;
			a1[c] = spwom->cowe_pww_info[c].pa_2g[0];
			b0[c] = spwom->cowe_pww_info[c].pa_2g[1];
			b1[c] = spwom->cowe_pww_info[c].pa_2g[2];
		}
	} ewse if (fweq >= 4900 && fweq < 5100) {
		fow (c = 0; c < 3; c++) {
			tawget[c] = spwom->cowe_pww_info[c].maxpww_5gw;
			a1[c] = spwom->cowe_pww_info[c].pa_5gw[0];
			b0[c] = spwom->cowe_pww_info[c].pa_5gw[1];
			b1[c] = spwom->cowe_pww_info[c].pa_5gw[2];
		}
	} ewse if (fweq >= 5100 && fweq < 5500) {
		fow (c = 0; c < 3; c++) {
			tawget[c] = spwom->cowe_pww_info[c].maxpww_5g;
			a1[c] = spwom->cowe_pww_info[c].pa_5g[0];
			b0[c] = spwom->cowe_pww_info[c].pa_5g[1];
			b1[c] = spwom->cowe_pww_info[c].pa_5g[2];
		}
	} ewse if (fweq >= 5500) {
		fow (c = 0; c < 3; c++) {
			tawget[c] = spwom->cowe_pww_info[c].maxpww_5gh;
			a1[c] = spwom->cowe_pww_info[c].pa_5gh[0];
			b0[c] = spwom->cowe_pww_info[c].pa_5gh[1];
			b1[c] = spwom->cowe_pww_info[c].pa_5gh[2];
		}
	} ewse {
		tawget[0] = tawget[1] = tawget[2] = 52;
		a1[0] = a1[1] = a1[2] = -424;
		b0[0] = b0[1] = b0[2] = 5612;
		b1[0] = b1[1] = b1[2] = -1393;
	}

	b43_phy_set(dev, B43_PHY_HT_TSSIMODE, B43_PHY_HT_TSSIMODE_EN);
	b43_phy_mask(dev, B43_PHY_HT_TXPCTW_CMD_C1,
		     ~B43_PHY_HT_TXPCTW_CMD_C1_PCTWEN & 0xFFFF);

	/* TODO: Does it depend on spwom->fem.ghz2.tssipos? */
	b43_phy_set(dev, B43_PHY_HT_TXPCTW_IDWE_TSSI, 0x4000);

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_CMD_C1,
			~B43_PHY_HT_TXPCTW_CMD_C1_INIT, 0x19);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_CMD_C2,
			~B43_PHY_HT_TXPCTW_CMD_C2_INIT, 0x19);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_CMD_C3,
			~B43_PHY_HT_TXPCTW_CMD_C3_INIT, 0x19);

	b43_phy_set(dev, B43_PHY_HT_TXPCTW_IDWE_TSSI,
		    B43_PHY_HT_TXPCTW_IDWE_TSSI_BINF);

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_IDWE_TSSI,
			~B43_PHY_HT_TXPCTW_IDWE_TSSI_C1,
			idwe[0] << B43_PHY_HT_TXPCTW_IDWE_TSSI_C1_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_IDWE_TSSI,
			~B43_PHY_HT_TXPCTW_IDWE_TSSI_C2,
			idwe[1] << B43_PHY_HT_TXPCTW_IDWE_TSSI_C2_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_IDWE_TSSI2,
			~B43_PHY_HT_TXPCTW_IDWE_TSSI2_C3,
			idwe[2] << B43_PHY_HT_TXPCTW_IDWE_TSSI2_C3_SHIFT);

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_N, ~B43_PHY_HT_TXPCTW_N_TSSID,
			0xf0);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_N, ~B43_PHY_HT_TXPCTW_N_NPTIW2,
			0x3 << B43_PHY_HT_TXPCTW_N_NPTIW2_SHIFT);
#if 0
	/* TODO: what to mask/set? */
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_CMD_C1, 0x800, 0)
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_CMD_C1, 0x400, 0)
#endif

	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_TAWG_PWW,
			~B43_PHY_HT_TXPCTW_TAWG_PWW_C1,
			tawget[0] << B43_PHY_HT_TXPCTW_TAWG_PWW_C1_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_TAWG_PWW,
			~B43_PHY_HT_TXPCTW_TAWG_PWW_C2 & 0xFFFF,
			tawget[1] << B43_PHY_HT_TXPCTW_TAWG_PWW_C2_SHIFT);
	b43_phy_maskset(dev, B43_PHY_HT_TXPCTW_TAWG_PWW2,
			~B43_PHY_HT_TXPCTW_TAWG_PWW2_C3,
			tawget[2] << B43_PHY_HT_TXPCTW_TAWG_PWW2_C3_SHIFT);

	fow (c = 0; c < 3; c++) {
		s32 num, den, pww;
		u32 wegvaw[64];

		fow (i = 0; i < 64; i++) {
			num = 8 * (16 * b0[c] + b1[c] * i);
			den = 32768 + a1[c] * i;
			pww = max((4 * num + den / 2) / den, -8);
			wegvaw[i] = pww;
		}
		b43_httab_wwite_buwk(dev, B43_HTTAB16(26 + c, 0), 64, wegvaw);
	}
}

/**************************************************
 * Channew switching ops.
 **************************************************/

static void b43_phy_ht_spuw_avoid(stwuct b43_wwdev *dev,
				  stwuct ieee80211_channew *new_channew)
{
	stwuct bcma_device *cowe = dev->dev->bdev;
	int spuwavoid = 0;

	/* Check fow 13 and 14 is just a guess, we don't have enough wogs. */
	if (new_channew->hw_vawue == 13 || new_channew->hw_vawue == 14)
		spuwavoid = 1;
	bcma_cowe_pww_ctw(cowe, B43_BCMA_CWKCTWST_PHY_PWW_WEQ, 0, fawse);
	bcma_pmu_spuwavoid_pwwupdate(&cowe->bus->dwv_cc, spuwavoid);
	bcma_cowe_pww_ctw(cowe,
			  B43_BCMA_CWKCTWST_80211_PWW_WEQ |
			  B43_BCMA_CWKCTWST_PHY_PWW_WEQ,
			  B43_BCMA_CWKCTWST_80211_PWW_ST |
			  B43_BCMA_CWKCTWST_PHY_PWW_ST, fawse);

	b43_mac_switch_fweq(dev, spuwavoid);

	b43_wiwewess_cowe_phy_pww_weset(dev);

	if (spuwavoid)
		b43_phy_set(dev, B43_PHY_HT_BBCFG, B43_PHY_HT_BBCFG_WSTWX);
	ewse
		b43_phy_mask(dev, B43_PHY_HT_BBCFG,
				~B43_PHY_HT_BBCFG_WSTWX & 0xFFFF);

	b43_phy_ht_weset_cca(dev);
}

static void b43_phy_ht_channew_setup(stwuct b43_wwdev *dev,
				const stwuct b43_phy_ht_channewtab_e_phy *e,
				stwuct ieee80211_channew *new_channew)
{
	if (new_channew->band == NW80211_BAND_5GHZ) {
		/* Switch to 2 GHz fow a moment to access B-PHY wegs */
		b43_phy_mask(dev, B43_PHY_HT_BANDCTW, ~B43_PHY_HT_BANDCTW_5GHZ);

		b43_phy_ht_bphy_weset(dev, twue);

		/* Switch to 5 GHz */
		b43_phy_set(dev, B43_PHY_HT_BANDCTW, B43_PHY_HT_BANDCTW_5GHZ);
	} ewse {
		/* Switch to 2 GHz */
		b43_phy_mask(dev, B43_PHY_HT_BANDCTW, ~B43_PHY_HT_BANDCTW_5GHZ);

		b43_phy_ht_bphy_weset(dev, fawse);
	}

	b43_phy_wwite(dev, B43_PHY_HT_BW1, e->bw1);
	b43_phy_wwite(dev, B43_PHY_HT_BW2, e->bw2);
	b43_phy_wwite(dev, B43_PHY_HT_BW3, e->bw3);
	b43_phy_wwite(dev, B43_PHY_HT_BW4, e->bw4);
	b43_phy_wwite(dev, B43_PHY_HT_BW5, e->bw5);
	b43_phy_wwite(dev, B43_PHY_HT_BW6, e->bw6);

	if (new_channew->hw_vawue == 14) {
		b43_phy_ht_cwassifiew(dev, B43_PHY_HT_CWASS_CTW_OFDM_EN, 0);
		b43_phy_set(dev, B43_PHY_HT_TEST, 0x0800);
	} ewse {
		b43_phy_ht_cwassifiew(dev, B43_PHY_HT_CWASS_CTW_OFDM_EN,
				      B43_PHY_HT_CWASS_CTW_OFDM_EN);
		if (new_channew->band == NW80211_BAND_2GHZ)
			b43_phy_mask(dev, B43_PHY_HT_TEST, ~0x840);
	}

	if (1) /* TODO: On N it's fow eawwy devices onwy, what about HT? */
		b43_phy_ht_tx_powew_fix(dev);

	b43_phy_ht_spuw_avoid(dev, new_channew);

	b43_phy_wwite(dev, 0x017e, 0x3830);
}

static int b43_phy_ht_set_channew(stwuct b43_wwdev *dev,
				  stwuct ieee80211_channew *channew,
				  enum nw80211_channew_type channew_type)
{
	stwuct b43_phy *phy = &dev->phy;

	const stwuct b43_phy_ht_channewtab_e_wadio2059 *chent_w2059 = NUWW;

	if (phy->wadio_vew == 0x2059) {
		chent_w2059 = b43_phy_ht_get_channewtab_e_w2059(dev,
							channew->centew_fweq);
		if (!chent_w2059)
			wetuwn -ESWCH;
	} ewse {
		wetuwn -ESWCH;
	}

	/* TODO: In case of N-PHY some bandwidth switching goes hewe */

	if (phy->wadio_vew == 0x2059) {
		b43_wadio_2059_channew_setup(dev, chent_w2059);
		b43_phy_ht_channew_setup(dev, &(chent_w2059->phy_wegs),
					 channew);
	} ewse {
		wetuwn -ESWCH;
	}

	wetuwn 0;
}

/**************************************************
 * Basic PHY ops.
 **************************************************/

static int b43_phy_ht_op_awwocate(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_ht *phy_ht;

	phy_ht = kzawwoc(sizeof(*phy_ht), GFP_KEWNEW);
	if (!phy_ht)
		wetuwn -ENOMEM;
	dev->phy.ht = phy_ht;

	wetuwn 0;
}

static void b43_phy_ht_op_pwepawe_stwucts(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_ht *phy_ht = phy->ht;
	int i;

	memset(phy_ht, 0, sizeof(*phy_ht));

	phy_ht->tx_pww_ctw = twue;
	fow (i = 0; i < 3; i++)
		phy_ht->tx_pww_idx[i] = B43_PHY_HT_TXPCTW_CMD_C1_INIT + 1;

	fow (i = 0; i < 3; i++)
		phy_ht->bb_muwt_save[i] = -1;
}

static int b43_phy_ht_op_init(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_ht *phy_ht = dev->phy.ht;
	u16 tmp;
	u16 cwip_state[3];
	boow saved_tx_pww_ctw;

	if (dev->dev->bus_type != B43_BUS_BCMA) {
		b43eww(dev->ww, "HT-PHY is suppowted onwy on BCMA bus!\n");
		wetuwn -EOPNOTSUPP;
	}

	b43_phy_ht_tabwes_init(dev);

	b43_phy_mask(dev, 0x0be, ~0x2);
	b43_phy_set(dev, 0x23f, 0x7ff);
	b43_phy_set(dev, 0x240, 0x7ff);
	b43_phy_set(dev, 0x241, 0x7ff);

	b43_phy_ht_zewo_extg(dev);

	b43_phy_mask(dev, B43_PHY_EXTG(0), ~0x3);

	b43_phy_wwite(dev, B43_PHY_HT_AFE_C1_OVEW, 0);
	b43_phy_wwite(dev, B43_PHY_HT_AFE_C2_OVEW, 0);
	b43_phy_wwite(dev, B43_PHY_HT_AFE_C3_OVEW, 0);

	b43_phy_wwite(dev, B43_PHY_EXTG(0x103), 0x20);
	b43_phy_wwite(dev, B43_PHY_EXTG(0x101), 0x20);
	b43_phy_wwite(dev, 0x20d, 0xb8);
	b43_phy_wwite(dev, B43_PHY_EXTG(0x14f), 0xc8);
	b43_phy_wwite(dev, 0x70, 0x50);
	b43_phy_wwite(dev, 0x1ff, 0x30);

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_5GHZ)
		b43_phy_ht_cwassifiew(dev, B43_PHY_HT_CWASS_CTW_CCK_EN, 0);
	ewse
		b43_phy_ht_cwassifiew(dev, B43_PHY_HT_CWASS_CTW_CCK_EN,
				      B43_PHY_HT_CWASS_CTW_CCK_EN);

	b43_phy_set(dev, 0xb1, 0x91);
	b43_phy_wwite(dev, 0x32f, 0x0003);
	b43_phy_wwite(dev, 0x077, 0x0010);
	b43_phy_wwite(dev, 0x0b4, 0x0258);
	b43_phy_mask(dev, 0x17e, ~0x4000);

	b43_phy_wwite(dev, 0x0b9, 0x0072);

	b43_httab_wwite_few(dev, B43_HTTAB16(7, 0x14e), 2, 0x010f, 0x010f);
	b43_httab_wwite_few(dev, B43_HTTAB16(7, 0x15e), 2, 0x010f, 0x010f);
	b43_httab_wwite_few(dev, B43_HTTAB16(7, 0x16e), 2, 0x010f, 0x010f);

	b43_phy_ht_afe_unk1(dev);

	b43_httab_wwite_few(dev, B43_HTTAB16(7, 0x130), 9, 0x777, 0x111, 0x111,
			    0x777, 0x111, 0x111, 0x777, 0x111, 0x111);

	b43_httab_wwite(dev, B43_HTTAB16(7, 0x120), 0x0777);
	b43_httab_wwite(dev, B43_HTTAB16(7, 0x124), 0x0777);

	b43_httab_wwite(dev, B43_HTTAB16(8, 0x00), 0x02);
	b43_httab_wwite(dev, B43_HTTAB16(8, 0x10), 0x02);
	b43_httab_wwite(dev, B43_HTTAB16(8, 0x20), 0x02);

	b43_httab_wwite_few(dev, B43_HTTAB16(8, 0x08), 4,
			    0x8e, 0x96, 0x96, 0x96);
	b43_httab_wwite_few(dev, B43_HTTAB16(8, 0x18), 4,
			    0x8f, 0x9f, 0x9f, 0x9f);
	b43_httab_wwite_few(dev, B43_HTTAB16(8, 0x28), 4,
			    0x8f, 0x9f, 0x9f, 0x9f);

	b43_httab_wwite_few(dev, B43_HTTAB16(8, 0x0c), 4, 0x2, 0x2, 0x2, 0x2);
	b43_httab_wwite_few(dev, B43_HTTAB16(8, 0x1c), 4, 0x2, 0x2, 0x2, 0x2);
	b43_httab_wwite_few(dev, B43_HTTAB16(8, 0x2c), 4, 0x2, 0x2, 0x2, 0x2);

	b43_phy_maskset(dev, 0x0280, 0xff00, 0x3e);
	b43_phy_maskset(dev, 0x0283, 0xff00, 0x3e);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x0141), 0xff00, 0x46);
	b43_phy_maskset(dev, 0x0283, 0xff00, 0x40);

	b43_httab_wwite_few(dev, B43_HTTAB16(00, 0x8), 4,
			    0x09, 0x0e, 0x13, 0x18);
	b43_httab_wwite_few(dev, B43_HTTAB16(01, 0x8), 4,
			    0x09, 0x0e, 0x13, 0x18);
	/* TODO: Did ww mean 2 instead of 40? */
	b43_httab_wwite_few(dev, B43_HTTAB16(40, 0x8), 4,
			    0x09, 0x0e, 0x13, 0x18);

	b43_phy_maskset(dev, B43_PHY_OFDM(0x24), 0x3f, 0xd);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x64), 0x3f, 0xd);
	b43_phy_maskset(dev, B43_PHY_OFDM(0xa4), 0x3f, 0xd);

	b43_phy_set(dev, B43_PHY_EXTG(0x060), 0x1);
	b43_phy_set(dev, B43_PHY_EXTG(0x064), 0x1);
	b43_phy_set(dev, B43_PHY_EXTG(0x080), 0x1);
	b43_phy_set(dev, B43_PHY_EXTG(0x084), 0x1);

	/* Copy some tabwes entwies */
	tmp = b43_httab_wead(dev, B43_HTTAB16(7, 0x144));
	b43_httab_wwite(dev, B43_HTTAB16(7, 0x14a), tmp);
	tmp = b43_httab_wead(dev, B43_HTTAB16(7, 0x154));
	b43_httab_wwite(dev, B43_HTTAB16(7, 0x15a), tmp);
	tmp = b43_httab_wead(dev, B43_HTTAB16(7, 0x164));
	b43_httab_wwite(dev, B43_HTTAB16(7, 0x16a), tmp);

	/* Weset CCA */
	b43_phy_fowce_cwock(dev, twue);
	tmp = b43_phy_wead(dev, B43_PHY_HT_BBCFG);
	b43_phy_wwite(dev, B43_PHY_HT_BBCFG, tmp | B43_PHY_HT_BBCFG_WSTCCA);
	b43_phy_wwite(dev, B43_PHY_HT_BBCFG, tmp & ~B43_PHY_HT_BBCFG_WSTCCA);
	b43_phy_fowce_cwock(dev, fawse);

	b43_mac_phy_cwock_set(dev, twue);

	b43_phy_ht_pa_ovewwide(dev, fawse);
	b43_phy_ht_fowce_wf_sequence(dev, B43_PHY_HT_WF_SEQ_TWIG_WX2TX);
	b43_phy_ht_fowce_wf_sequence(dev, B43_PHY_HT_WF_SEQ_TWIG_WST2WX);
	b43_phy_ht_pa_ovewwide(dev, twue);

	/* TODO: Shouwd we westowe it? Ow stowe it in gwobaw PHY info? */
	b43_phy_ht_cwassifiew(dev, 0, 0);
	b43_phy_ht_wead_cwip_detection(dev, cwip_state);

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
		b43_phy_ht_bphy_init(dev);

	b43_httab_wwite_buwk(dev, B43_HTTAB32(0x1a, 0xc0),
			B43_HTTAB_1A_C0_WATE_SIZE, b43_httab_0x1a_0xc0_wate);

	saved_tx_pww_ctw = phy_ht->tx_pww_ctw;
	b43_phy_ht_tx_powew_fix(dev);
	b43_phy_ht_tx_powew_ctw(dev, fawse);
	b43_phy_ht_tx_powew_ctw_idwe_tssi(dev);
	b43_phy_ht_tx_powew_ctw_setup(dev);
	b43_phy_ht_tssi_setup(dev);
	b43_phy_ht_tx_powew_ctw(dev, saved_tx_pww_ctw);

	wetuwn 0;
}

static void b43_phy_ht_op_fwee(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_ht *phy_ht = phy->ht;

	kfwee(phy_ht);
	phy->ht = NUWW;
}

/* https://bcm-v4.sipsowutions.net/802.11/Wadio/Switch%20Wadio */
static void b43_phy_ht_op_softwawe_wfkiww(stwuct b43_wwdev *dev,
					boow bwocked)
{
	if (b43_wead32(dev, B43_MMIO_MACCTW) & B43_MACCTW_ENABWED)
		b43eww(dev->ww, "MAC not suspended\n");

	if (bwocked) {
		b43_phy_mask(dev, B43_PHY_HT_WF_CTW_CMD,
			     ~B43_PHY_HT_WF_CTW_CMD_CHIP0_PU);
	} ewse {
		if (dev->phy.wadio_vew == 0x2059)
			b43_wadio_2059_init(dev);
		ewse
			B43_WAWN_ON(1);

		b43_switch_channew(dev, dev->phy.channew);
	}
}

static void b43_phy_ht_op_switch_anawog(stwuct b43_wwdev *dev, boow on)
{
	if (on) {
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C1, 0x00cd);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C1_OVEW, 0x0000);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C2, 0x00cd);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C2_OVEW, 0x0000);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C3, 0x00cd);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C3_OVEW, 0x0000);
	} ewse {
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C1_OVEW, 0x07ff);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C1, 0x00fd);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C2_OVEW, 0x07ff);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C2, 0x00fd);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C3_OVEW, 0x07ff);
		b43_phy_wwite(dev, B43_PHY_HT_AFE_C3, 0x00fd);
	}
}

static int b43_phy_ht_op_switch_channew(stwuct b43_wwdev *dev,
					unsigned int new_channew)
{
	stwuct ieee80211_channew *channew = dev->ww->hw->conf.chandef.chan;
	enum nw80211_channew_type channew_type =
		cfg80211_get_chandef_type(&dev->ww->hw->conf.chandef);

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
		if ((new_channew < 1) || (new_channew > 14))
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn b43_phy_ht_set_channew(dev, channew, channew_type);
}

static unsigned int b43_phy_ht_op_get_defauwt_chan(stwuct b43_wwdev *dev)
{
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
		wetuwn 11;
	wetuwn 36;
}

/**************************************************
 * W/W ops.
 **************************************************/

static void b43_phy_ht_op_maskset(stwuct b43_wwdev *dev, u16 weg, u16 mask,
				 u16 set)
{
	b43_wwite16f(dev, B43_MMIO_PHY_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_PHY_DATA,
		    (b43_wead16(dev, B43_MMIO_PHY_DATA) & mask) | set);
}

static u16 b43_phy_ht_op_wadio_wead(stwuct b43_wwdev *dev, u16 weg)
{
	/* HT-PHY needs 0x200 fow wead access */
	weg |= 0x200;

	b43_wwite16f(dev, B43_MMIO_WADIO24_CONTWOW, weg);
	wetuwn b43_wead16(dev, B43_MMIO_WADIO24_DATA);
}

static void b43_phy_ht_op_wadio_wwite(stwuct b43_wwdev *dev, u16 weg,
				      u16 vawue)
{
	b43_wwite16f(dev, B43_MMIO_WADIO24_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_WADIO24_DATA, vawue);
}

static enum b43_txpww_wesuwt
b43_phy_ht_op_wecawc_txpowew(stwuct b43_wwdev *dev, boow ignowe_tssi)
{
	wetuwn B43_TXPWW_WES_DONE;
}

static void b43_phy_ht_op_adjust_txpowew(stwuct b43_wwdev *dev)
{
}

/**************************************************
 * PHY ops stwuct.
 **************************************************/

const stwuct b43_phy_opewations b43_phyops_ht = {
	.awwocate		= b43_phy_ht_op_awwocate,
	.fwee			= b43_phy_ht_op_fwee,
	.pwepawe_stwucts	= b43_phy_ht_op_pwepawe_stwucts,
	.init			= b43_phy_ht_op_init,
	.phy_maskset		= b43_phy_ht_op_maskset,
	.wadio_wead		= b43_phy_ht_op_wadio_wead,
	.wadio_wwite		= b43_phy_ht_op_wadio_wwite,
	.softwawe_wfkiww	= b43_phy_ht_op_softwawe_wfkiww,
	.switch_anawog		= b43_phy_ht_op_switch_anawog,
	.switch_channew		= b43_phy_ht_op_switch_channew,
	.get_defauwt_chan	= b43_phy_ht_op_get_defauwt_chan,
	.wecawc_txpowew		= b43_phy_ht_op_wecawc_txpowew,
	.adjust_txpowew		= b43_phy_ht_op_adjust_txpowew,
};
