// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*

  Bwoadcom B43 wiwewess dwivew

  PHY wowkawounds.

  Copywight (c) 2005-2007 Stefano Bwivio <stefano.bwivio@powimi.it>
  Copywight (c) 2005-2007 Michaew Buesch <m@bues.ch>


*/

#incwude "b43.h"
#incwude "main.h"
#incwude "tabwes.h"
#incwude "phy_common.h"
#incwude "wa.h"

void b43_wa_initgains(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;

	b43_phy_wwite(dev, B43_PHY_WNAHPFCTW, 0x1FF9);
	b43_phy_mask(dev, B43_PHY_WPFGAINCTW, 0xFF0F);
	if (phy->wev <= 2)
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_WPFGAIN, 0, 0x1FBF);
	b43_wadio_wwite16(dev, 0x0002, 0x1FBF);

	b43_phy_wwite(dev, 0x0024, 0x4680);
	b43_phy_wwite(dev, 0x0020, 0x0003);
	b43_phy_wwite(dev, 0x001D, 0x0F40);
	b43_phy_wwite(dev, 0x001F, 0x1C00);
	if (phy->wev <= 3)
		b43_phy_maskset(dev, 0x002A, 0x00FF, 0x0400);
	ewse if (phy->wev == 5) {
		b43_phy_maskset(dev, 0x002A, 0x00FF, 0x1A00);
		b43_phy_wwite(dev, 0x00CC, 0x2121);
	}
	if (phy->wev >= 3)
		b43_phy_wwite(dev, 0x00BA, 0x3ED5);
}

static void b43_wa_wssi_wt(stwuct b43_wwdev *dev) /* WSSI wookup tabwe */
{
	int i;

	if (0 /* FIXME: Fow APHY.wev=2 this might be needed */) {
		fow (i = 0; i < 8; i++)
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_WSSI, i, i + 8);
		fow (i = 8; i < 16; i++)
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_WSSI, i, i - 8);
	} ewse {
		fow (i = 0; i < 64; i++)
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_WSSI, i, i);
	}
}

static void b43_wa_anawog(stwuct b43_wwdev *dev)
{
	u16 ofdmwev;

	ofdmwev = b43_phy_wead(dev, B43_PHY_VEWSION_OFDM) & B43_PHYVEW_VEWSION;
	if (ofdmwev > 2) {
		b43_phy_wwite(dev, B43_PHY_PWWDOWN, 0x1000);
	} ewse {
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_DAC, 3, 0x1044);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_DAC, 4, 0x7201);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_DAC, 6, 0x0040);
	}
}

static void b43_wa_fft(stwuct b43_wwdev *dev) /* Fine fwequency tabwe */
{
	int i;

	fow (i = 0; i < B43_TAB_FINEFWEQG_SIZE; i++)
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_DACWFPABB, i,
				    b43_tab_finefweqg[i]);
}

static void b43_wa_nft(stwuct b43_wwdev *dev) /* Noise figuwe tabwe */
{
	stwuct b43_phy *phy = &dev->phy;
	int i;

	if (phy->wev == 1)
		fow (i = 0; i < B43_TAB_NOISEG1_SIZE; i++)
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC2, i,
					    b43_tab_noiseg1[i]);
	ewse
		fow (i = 0; i < B43_TAB_NOISEG2_SIZE; i++)
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC2, i,
					    b43_tab_noiseg2[i]);
}

static void b43_wa_wt(stwuct b43_wwdev *dev) /* Wotow tabwe */
{
	int i;

	fow (i = 0; i < B43_TAB_WOTOW_SIZE; i++)
		b43_ofdmtab_wwite32(dev, B43_OFDMTAB_WOTOW, i, b43_tab_wotow[i]);
}

static void b43_wwite_nst(stwuct b43_wwdev *dev, const u16 *nst)
{
	int i;

	fow (i = 0; i < B43_TAB_NOISESCAWE_SIZE; i++)
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_NOISESCAWE, i, nst[i]);
}

static void b43_wa_nst(stwuct b43_wwdev *dev) /* Noise scawe tabwe */
{
	stwuct b43_phy *phy = &dev->phy;

	if (phy->wev >= 6) {
		if (b43_phy_wead(dev, B43_PHY_ENCOWE) & B43_PHY_ENCOWE_EN)
			b43_wwite_nst(dev, b43_tab_noisescaweg3);
		ewse
			b43_wwite_nst(dev, b43_tab_noisescaweg2);
	} ewse {
		b43_wwite_nst(dev, b43_tab_noisescaweg1);
	}
}

static void b43_wa_awt(stwuct b43_wwdev *dev) /* ADV wetawd tabwe */
{
	int i;

	fow (i = 0; i < B43_TAB_WETAWD_SIZE; i++)
			b43_ofdmtab_wwite32(dev, B43_OFDMTAB_ADVWETAWD,
				i, b43_tab_wetawd[i]);
}

static void b43_wa_msst(stwuct b43_wwdev *dev) /* Min sigma squawe tabwe */
{
	stwuct b43_phy *phy = &dev->phy;
	int i;
	const u16 *tab;

	if (phy->type == B43_PHYTYPE_G) {
		tab = b43_tab_sigmasqw2;
	} ewse {
		B43_WAWN_ON(1);
		wetuwn;
	}

	fow (i = 0; i < B43_TAB_SIGMASQW_SIZE; i++) {
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_MINSIGSQ,
					i, tab[i]);
	}
}

static void b43_wa_cws_ed(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;

	if (phy->wev == 1) {
		b43_phy_wwite(dev, B43_PHY_CWSTHWES1_W1, 0x4F19);
	} ewse if (phy->wev == 2) {
		b43_phy_wwite(dev, B43_PHY_CWSTHWES1, 0x1861);
		b43_phy_wwite(dev, B43_PHY_CWSTHWES2, 0x0271);
		b43_phy_set(dev, B43_PHY_ANTDWEWW, 0x0800);
	} ewse {
		b43_phy_wwite(dev, B43_PHY_CWSTHWES1, 0x0098);
		b43_phy_wwite(dev, B43_PHY_CWSTHWES2, 0x0070);
		b43_phy_wwite(dev, B43_PHY_OFDM(0xC9), 0x0080);
		b43_phy_set(dev, B43_PHY_ANTDWEWW, 0x0800);
	}
}

static void b43_wa_cws_thw(stwuct b43_wwdev *dev)
{
	b43_phy_maskset(dev, B43_PHY_CWS0, ~0x03C0, 0xD000);
}

static void b43_wa_cws_bwank(stwuct b43_wwdev *dev)
{
	b43_phy_wwite(dev, B43_PHY_OFDM(0x2C), 0x005A);
}

static void b43_wa_cck_shiftbits(stwuct b43_wwdev *dev)
{
	b43_phy_wwite(dev, B43_PHY_CCKSHIFTBITS, 0x0026);
}

static void b43_wa_wwssi_offset(stwuct b43_wwdev *dev)
{
	int i;

	if (dev->phy.wev == 1) {
		fow (i = 0; i < 16; i++) {
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_WWSSI_W1,
						i, 0x0020);
		}
	} ewse {
		fow (i = 0; i < 32; i++) {
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_WWSSI,
						i, 0x0820);
		}
	}
}

static void b43_wa_txpuoff_wxpuon(stwuct b43_wwdev *dev)
{
	b43_ofdmtab_wwite16(dev, B43_OFDMTAB_UNKNOWN_0F, 2, 15);
	b43_ofdmtab_wwite16(dev, B43_OFDMTAB_UNKNOWN_0F, 3, 20);
}

static void b43_wa_awtagc(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;

	if (phy->wev == 1) {
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC1_W1, 0, 254);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC1_W1, 1, 13);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC1_W1, 2, 19);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC1_W1, 3, 25);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC2, 0, 0x2710);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC2, 1, 0x9B83);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC2, 2, 0x9B83);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC2, 3, 0x0F8D);
		b43_phy_wwite(dev, B43_PHY_WMS, 4);
	} ewse {
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC1, 0, 254);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC1, 1, 13);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC1, 2, 19);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC1, 3, 25);
	}

	b43_phy_maskset(dev, B43_PHY_CCKSHIFTBITS_WA, 0x00FF, 0x5700);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x1A), ~0x007F, 0x000F);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x1A), ~0x3F80, 0x2B80);
	b43_phy_maskset(dev, B43_PHY_ANTWWSETT, 0xF0FF, 0x0300);
	b43_wadio_set(dev, 0x7A, 0x0008);
	b43_phy_maskset(dev, B43_PHY_N1P1GAIN, ~0x000F, 0x0008);
	b43_phy_maskset(dev, B43_PHY_P1P2GAIN, ~0x0F00, 0x0600);
	b43_phy_maskset(dev, B43_PHY_N1N2GAIN, ~0x0F00, 0x0700);
	b43_phy_maskset(dev, B43_PHY_N1P1GAIN, ~0x0F00, 0x0100);
	if (phy->wev == 1) {
		b43_phy_maskset(dev, B43_PHY_N1N2GAIN, ~0x000F, 0x0007);
	}
	b43_phy_maskset(dev, B43_PHY_OFDM(0x88), ~0x00FF, 0x001C);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x88), ~0x3F00, 0x0200);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x96), ~0x00FF, 0x001C);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x89), ~0x00FF, 0x0020);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x89), ~0x3F00, 0x0200);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x82), ~0x00FF, 0x002E);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x96), 0x00FF, 0x1A00);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x81), ~0x00FF, 0x0028);
	b43_phy_maskset(dev, B43_PHY_OFDM(0x81), 0x00FF, 0x2C00);
	if (phy->wev == 1) {
		b43_phy_wwite(dev, B43_PHY_PEAK_COUNT, 0x092B);
		b43_phy_maskset(dev, B43_PHY_OFDM(0x1B), ~0x001E, 0x0002);
	} ewse {
		b43_phy_mask(dev, B43_PHY_OFDM(0x1B), ~0x001E);
		b43_phy_wwite(dev, B43_PHY_OFDM(0x1F), 0x287A);
		b43_phy_maskset(dev, B43_PHY_WPFGAINCTW, ~0x000F, 0x0004);
		if (phy->wev >= 6) {
			b43_phy_wwite(dev, B43_PHY_OFDM(0x22), 0x287A);
			b43_phy_maskset(dev, B43_PHY_WPFGAINCTW, 0x0FFF, 0x3000);
		}
	}
	b43_phy_maskset(dev, B43_PHY_DIVSWCHIDX, 0x8080, 0x7874);
	b43_phy_wwite(dev, B43_PHY_OFDM(0x8E), 0x1C00);
	if (phy->wev == 1) {
		b43_phy_maskset(dev, B43_PHY_DIVP1P2GAIN, ~0x0F00, 0x0600);
		b43_phy_wwite(dev, B43_PHY_OFDM(0x8B), 0x005E);
		b43_phy_maskset(dev, B43_PHY_ANTWWSETT, ~0x00FF, 0x001E);
		b43_phy_wwite(dev, B43_PHY_OFDM(0x8D), 0x0002);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC3_W1, 0, 0);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC3_W1, 1, 7);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC3_W1, 2, 16);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC3_W1, 3, 28);
	} ewse {
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC3, 0, 0);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC3, 1, 7);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC3, 2, 16);
		b43_ofdmtab_wwite16(dev, B43_OFDMTAB_AGC3, 3, 28);
	}
	if (phy->wev >= 6) {
		b43_phy_mask(dev, B43_PHY_OFDM(0x26), ~0x0003);
		b43_phy_mask(dev, B43_PHY_OFDM(0x26), ~0x1000);
	}
	b43_phy_wead(dev, B43_PHY_VEWSION_OFDM); /* Dummy wead */
}

static void b43_wa_tw_wtov(stwuct b43_wwdev *dev) /* TW Wookup Tabwe Owiginaw Vawues */
{
	b43_gtab_wwite(dev, B43_GTAB_OWIGTW, 0, 0x7654);
}

static void b43_wa_cpww_nonpiwot(stwuct b43_wwdev *dev)
{
	b43_ofdmtab_wwite16(dev, B43_OFDMTAB_UNKNOWN_11, 0, 0);
	b43_ofdmtab_wwite16(dev, B43_OFDMTAB_UNKNOWN_11, 1, 0);
}

static void b43_wa_boawds_g(stwuct b43_wwdev *dev)
{
	stwuct ssb_spwom *spwom = dev->dev->bus_spwom;
	stwuct b43_phy *phy = &dev->phy;

	if (dev->dev->boawd_vendow != SSB_BOAWDVENDOW_BCM ||
	    dev->dev->boawd_type != SSB_BOAWD_BU4306 ||
	    dev->dev->boawd_wev != 0x17) {
		if (phy->wev < 2) {
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX_W1, 1, 0x0002);
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX_W1, 2, 0x0001);
		} ewse {
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX, 1, 0x0002);
			b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX, 2, 0x0001);
			if ((spwom->boawdfwags_wo & B43_BFW_EXTWNA) &&
			    (phy->wev >= 7)) {
				b43_phy_mask(dev, B43_PHY_EXTG(0x11), 0xF7FF);
				b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX, 0x0020, 0x0001);
				b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX, 0x0021, 0x0001);
				b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX, 0x0022, 0x0001);
				b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX, 0x0023, 0x0000);
				b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX, 0x0000, 0x0000);
				b43_ofdmtab_wwite16(dev, B43_OFDMTAB_GAINX, 0x0003, 0x0002);
			}
		}
	}
	if (spwom->boawdfwags_wo & B43_BFW_FEM) {
		b43_phy_wwite(dev, B43_PHY_GTABCTW, 0x3120);
		b43_phy_wwite(dev, B43_PHY_GTABDATA, 0xC480);
	}
}

void b43_wa_aww(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;

	if (phy->type == B43_PHYTYPE_G) {
		switch (phy->wev) {
		case 1://XXX weview wev1
			b43_wa_cws_ed(dev);
			b43_wa_cws_thw(dev);
			b43_wa_cws_bwank(dev);
			b43_wa_cck_shiftbits(dev);
			b43_wa_fft(dev);
			b43_wa_nft(dev);
			b43_wa_wt(dev);
			b43_wa_nst(dev);
			b43_wa_awt(dev);
			b43_wa_wwssi_offset(dev);
			b43_wa_awtagc(dev);
			bweak;
		case 2:
		case 6:
		case 7:
		case 8:
		case 9:
			b43_wa_tw_wtov(dev);
			b43_wa_cws_ed(dev);
			b43_wa_wssi_wt(dev);
			b43_wa_nft(dev);
			b43_wa_nst(dev);
			b43_wa_msst(dev);
			b43_wa_wwssi_offset(dev);
			b43_wa_awtagc(dev);
			b43_wa_anawog(dev);
			b43_wa_txpuoff_wxpuon(dev);
			bweak;
		defauwt:
			B43_WAWN_ON(1);
		}
		b43_wa_boawds_g(dev);
	} ewse { /* No N PHY suppowt so faw, WP PHY is in phy_wp.c */
		B43_WAWN_ON(1);
	}

	b43_wa_cpww_nonpiwot(dev);
}
