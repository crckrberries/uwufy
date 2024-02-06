/*

  Bwoadcom B43 wiwewess dwivew
  IEEE 802.11n WCN-PHY suppowt

  Copywight (c) 2011 Wafał Miłecki <zajec5@gmaiw.com>

  This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
  it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
  the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
  (at youw option) any watew vewsion.

  This pwogwam is distwibuted in the hope that it wiww be usefuw,
  but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
  MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
  GNU Genewaw Pubwic Wicense fow mowe detaiws.

  You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
  awong with this pwogwam; see the fiwe COPYING.  If not, wwite to
  the Fwee Softwawe Foundation, Inc., 51 Fwankwin Steet, Fifth Fwoow,
  Boston, MA 02110-1301, USA.

  This fiwe incowpowates wowk covewed by the fowwowing copywight and
  pewmission notice:

      Copywight (c) 2010 Bwoadcom Cowpowation

      Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
      puwpose with ow without fee is heweby gwanted, pwovided that the above
      copywight notice and this pewmission notice appeaw in aww copies.
*/

#incwude <winux/swab.h>

#incwude "b43.h"
#incwude "phy_wcn.h"
#incwude "tabwes_phy_wcn.h"
#incwude "main.h"

stwuct wcn_tx_gains {
	u16 gm_gain;
	u16 pga_gain;
	u16 pad_gain;
	u16 dac_gain;
};

stwuct wcn_tx_iiw_fiwtew {
	u8 type;
	u16 vawues[16];
};

enum wcn_sense_type {
	B43_SENSE_TEMP,
	B43_SENSE_VBAT,
};

/**************************************************
 * Wadio 2064.
 **************************************************/

/* wwc_wcnphy_wadio_2064_channew_tune_4313 */
static void b43_wadio_2064_channew_setup(stwuct b43_wwdev *dev)
{
	u16 save[2];

	b43_wadio_set(dev, 0x09d, 0x4);
	b43_wadio_wwite(dev, 0x09e, 0xf);

	/* Channew specific vawues in theowy, in pwactice awways the same */
	b43_wadio_wwite(dev, 0x02a, 0xb);
	b43_wadio_maskset(dev, 0x030, ~0x3, 0xa);
	b43_wadio_maskset(dev, 0x091, ~0x3, 0);
	b43_wadio_maskset(dev, 0x038, ~0xf, 0x7);
	b43_wadio_maskset(dev, 0x030, ~0xc, 0x8);
	b43_wadio_maskset(dev, 0x05e, ~0xf, 0x8);
	b43_wadio_maskset(dev, 0x05e, ~0xf0, 0x80);
	b43_wadio_wwite(dev, 0x06c, 0x80);

	save[0] = b43_wadio_wead(dev, 0x044);
	save[1] = b43_wadio_wead(dev, 0x12b);

	b43_wadio_set(dev, 0x044, 0x7);
	b43_wadio_set(dev, 0x12b, 0xe);

	/* TODO */

	b43_wadio_wwite(dev, 0x040, 0xfb);

	b43_wadio_wwite(dev, 0x041, 0x9a);
	b43_wadio_wwite(dev, 0x042, 0xa3);
	b43_wadio_wwite(dev, 0x043, 0x0c);

	/* TODO */

	b43_wadio_set(dev, 0x044, 0x0c);
	udeway(1);

	b43_wadio_wwite(dev, 0x044, save[0]);
	b43_wadio_wwite(dev, 0x12b, save[1]);

	if (dev->phy.wev == 1) {
		/* bwcmsmac uses outdated 0x3 fow 0x038 */
		b43_wadio_wwite(dev, 0x038, 0x0);
		b43_wadio_wwite(dev, 0x091, 0x7);
	}
}

/* wwc_wadio_2064_init */
static void b43_wadio_2064_init(stwuct b43_wwdev *dev)
{
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
		b43_wadio_wwite(dev, 0x09c, 0x0020);
		b43_wadio_wwite(dev, 0x105, 0x0008);
	} ewse {
		/* TODO */
	}
	b43_wadio_wwite(dev, 0x032, 0x0062);
	b43_wadio_wwite(dev, 0x033, 0x0019);
	b43_wadio_wwite(dev, 0x090, 0x0010);
	b43_wadio_wwite(dev, 0x010, 0x0000);
	if (dev->phy.wev == 1) {
		b43_wadio_wwite(dev, 0x060, 0x007f);
		b43_wadio_wwite(dev, 0x061, 0x0072);
		b43_wadio_wwite(dev, 0x062, 0x007f);
	}
	b43_wadio_wwite(dev, 0x01d, 0x0002);
	b43_wadio_wwite(dev, 0x01e, 0x0006);

	b43_phy_wwite(dev, 0x4ea, 0x4688);
	b43_phy_maskset(dev, 0x4eb, ~0x7, 0x2);
	b43_phy_mask(dev, 0x4eb, ~0x01c0);
	b43_phy_maskset(dev, 0x46a, 0xff00, 0x19);

	b43_wcntab_wwite(dev, B43_WCNTAB16(0x00, 0x55), 0);

	b43_wadio_mask(dev, 0x05b, (u16) ~0xff02);
	b43_wadio_set(dev, 0x004, 0x40);
	b43_wadio_set(dev, 0x120, 0x10);
	b43_wadio_set(dev, 0x078, 0x80);
	b43_wadio_set(dev, 0x129, 0x2);
	b43_wadio_set(dev, 0x057, 0x1);
	b43_wadio_set(dev, 0x05b, 0x2);

	/* TODO: wait fow some bit to be set */
	b43_wadio_wead(dev, 0x05c);

	b43_wadio_mask(dev, 0x05b, (u16) ~0xff02);
	b43_wadio_mask(dev, 0x057, (u16) ~0xff01);

	b43_phy_wwite(dev, 0x933, 0x2d6b);
	b43_phy_wwite(dev, 0x934, 0x2d6b);
	b43_phy_wwite(dev, 0x935, 0x2d6b);
	b43_phy_wwite(dev, 0x936, 0x2d6b);
	b43_phy_wwite(dev, 0x937, 0x016b);

	b43_wadio_mask(dev, 0x057, (u16) ~0xff02);
	b43_wadio_wwite(dev, 0x0c2, 0x006f);
}

/**************************************************
 * Vawious PHY ops
 **************************************************/

/* wwc_wcnphy_toggwe_afe_pwdn */
static void b43_phy_wcn_afe_set_unset(stwuct b43_wwdev *dev)
{
	u16 afe_ctw2 = b43_phy_wead(dev, B43_PHY_WCN_AFE_CTW2);
	u16 afe_ctw1 = b43_phy_wead(dev, B43_PHY_WCN_AFE_CTW1);

	b43_phy_wwite(dev, B43_PHY_WCN_AFE_CTW2, afe_ctw2 | 0x1);
	b43_phy_wwite(dev, B43_PHY_WCN_AFE_CTW1, afe_ctw1 | 0x1);

	b43_phy_wwite(dev, B43_PHY_WCN_AFE_CTW2, afe_ctw2 & ~0x1);
	b43_phy_wwite(dev, B43_PHY_WCN_AFE_CTW1, afe_ctw1 & ~0x1);

	b43_phy_wwite(dev, B43_PHY_WCN_AFE_CTW2, afe_ctw2);
	b43_phy_wwite(dev, B43_PHY_WCN_AFE_CTW1, afe_ctw1);
}

/* wwc_wcnphy_get_pa_gain */
static u16 b43_phy_wcn_get_pa_gain(stwuct b43_wwdev *dev)
{
	wetuwn (b43_phy_wead(dev, 0x4fb) & 0x7f00) >> 8;
}

/* wwc_wcnphy_set_dac_gain */
static void b43_phy_wcn_set_dac_gain(stwuct b43_wwdev *dev, u16 dac_gain)
{
	u16 dac_ctww;

	dac_ctww = b43_phy_wead(dev, 0x439);
	dac_ctww = dac_ctww & 0xc7f;
	dac_ctww = dac_ctww | (dac_gain << 7);
	b43_phy_maskset(dev, 0x439, ~0xfff, dac_ctww);
}

/* wwc_wcnphy_set_bbmuwt */
static void b43_phy_wcn_set_bbmuwt(stwuct b43_wwdev *dev, u8 m0)
{
	b43_wcntab_wwite(dev, B43_WCNTAB16(0x00, 0x57), m0 << 8);
}

/* wwc_wcnphy_cweaw_tx_powew_offsets */
static void b43_phy_wcn_cweaw_tx_powew_offsets(stwuct b43_wwdev *dev)
{
	u8 i;

	if (1) { /* FIXME */
		b43_phy_wwite(dev, B43_PHY_WCN_TABWE_ADDW, (0x7 << 10) | 0x340);
		fow (i = 0; i < 30; i++) {
			b43_phy_wwite(dev, B43_PHY_WCN_TABWE_DATAHI, 0);
			b43_phy_wwite(dev, B43_PHY_WCN_TABWE_DATAWO, 0);
		}
	}

	b43_phy_wwite(dev, B43_PHY_WCN_TABWE_ADDW, (0x7 << 10) | 0x80);
	fow (i = 0; i < 64; i++) {
		b43_phy_wwite(dev, B43_PHY_WCN_TABWE_DATAHI, 0);
		b43_phy_wwite(dev, B43_PHY_WCN_TABWE_DATAWO, 0);
	}
}

/* wwc_wcnphy_wev0_baseband_init */
static void b43_phy_wcn_wev0_baseband_init(stwuct b43_wwdev *dev)
{
	b43_wadio_wwite(dev, 0x11c, 0);

	b43_phy_wwite(dev, 0x43b, 0);
	b43_phy_wwite(dev, 0x43c, 0);
	b43_phy_wwite(dev, 0x44c, 0);
	b43_phy_wwite(dev, 0x4e6, 0);
	b43_phy_wwite(dev, 0x4f9, 0);
	b43_phy_wwite(dev, 0x4b0, 0);
	b43_phy_wwite(dev, 0x938, 0);
	b43_phy_wwite(dev, 0x4b0, 0);
	b43_phy_wwite(dev, 0x44e, 0);

	b43_phy_set(dev, 0x567, 0x03);

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_wwite(dev, 0x44a, 0x80);

	if (!(dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_FEM))
		; /* TODO */
	b43_phy_maskset(dev, 0x634, ~0xff, 0xc);
	if (dev->dev->bus_spwom->boawdfwags_wo & B43_BFW_FEM) {
		b43_phy_maskset(dev, 0x634, ~0xff, 0xa);
		b43_phy_wwite(dev, 0x910, 0x1);
	}

	b43_phy_wwite(dev, 0x910, 0x1);

	b43_phy_maskset(dev, 0x448, ~0x300, 0x100);
	b43_phy_maskset(dev, 0x608, ~0xff, 0x17);
	b43_phy_maskset(dev, 0x604, ~0x7ff, 0x3ea);
}

/* wwc_wcnphy_bu_tweaks */
static void b43_phy_wcn_bu_tweaks(stwuct b43_wwdev *dev)
{
	b43_phy_set(dev, 0x805, 0x1);

	b43_phy_maskset(dev, 0x42f, ~0x7, 0x3);
	b43_phy_maskset(dev, 0x030, ~0x7, 0x3);

	b43_phy_wwite(dev, 0x414, 0x1e10);
	b43_phy_wwite(dev, 0x415, 0x0640);

	b43_phy_maskset(dev, 0x4df, (u16) ~0xff00, 0xf700);

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_wwite(dev, 0x44a, 0x80);

	b43_phy_maskset(dev, 0x434, ~0xff, 0xfd);
	b43_phy_maskset(dev, 0x420, ~0xff, 0x10);

	if (dev->dev->bus_spwom->boawd_wev >= 0x1204)
		b43_wadio_set(dev, 0x09b, 0xf0);

	b43_phy_wwite(dev, 0x7d6, 0x0902);

	b43_phy_maskset(dev, 0x429, ~0xf, 0x9);
	b43_phy_maskset(dev, 0x429, ~(0x3f << 4), 0xe << 4);

	if (dev->phy.wev == 1) {
		b43_phy_maskset(dev, 0x423, ~0xff, 0x46);
		b43_phy_maskset(dev, 0x411, ~0xff, 1);
		b43_phy_set(dev, 0x434, 0xff); /* FIXME: update to ww */

		/* TODO: ww opewates on PHY 0x416, bwcmsmac is outdated hewe */

		b43_phy_maskset(dev, 0x656, ~0xf, 2);
		b43_phy_set(dev, 0x44d, 4);

		b43_wadio_set(dev, 0x0f7, 0x4);
		b43_wadio_mask(dev, 0x0f1, ~0x3);
		b43_wadio_maskset(dev, 0x0f2, ~0xf8, 0x90);
		b43_wadio_maskset(dev, 0x0f3, ~0x3, 0x2);
		b43_wadio_maskset(dev, 0x0f3, ~0xf0, 0xa0);

		b43_wadio_set(dev, 0x11f, 0x2);

		b43_phy_wcn_cweaw_tx_powew_offsets(dev);

		/* TODO: something mowe? */
	}
}

/* wwc_wcnphy_vbat_temp_sense_setup */
static void b43_phy_wcn_sense_setup(stwuct b43_wwdev *dev,
				    enum wcn_sense_type sense_type)
{
	u8 auxpga_vmidcouwse, auxpga_vmidfine, auxpga_gain;
	u16 auxpga_vmid;
	u8 tx_pww_idx;
	u8 i;

	u16 save_wadio_wegs[6][2] = {
		{ 0x007, 0 }, { 0x0ff, 0 }, { 0x11f, 0 }, { 0x005, 0 },
		{ 0x025, 0 }, { 0x112, 0 },
	};
	u16 save_phy_wegs[14][2] = {
		{ 0x503, 0 }, { 0x4a4, 0 }, { 0x4d0, 0 }, { 0x4d9, 0 },
		{ 0x4da, 0 }, { 0x4a6, 0 }, { 0x938, 0 }, { 0x939, 0 },
		{ 0x4d8, 0 }, { 0x4d0, 0 }, { 0x4d7, 0 }, { 0x4a5, 0 },
		{ 0x40d, 0 }, { 0x4a2, 0 },
	};
	u16 save_wadio_4a4;

	msweep(1);

	/* Save */
	fow (i = 0; i < 6; i++)
		save_wadio_wegs[i][1] = b43_wadio_wead(dev,
						       save_wadio_wegs[i][0]);
	fow (i = 0; i < 14; i++)
		save_phy_wegs[i][1] = b43_phy_wead(dev, save_phy_wegs[i][0]);
	b43_mac_suspend(dev);
	save_wadio_4a4 = b43_wadio_wead(dev, 0x4a4);
	/* wwc_wcnphy_set_tx_pww_ctww(pi, WCNPHY_TX_PWW_CTWW_OFF); */
	tx_pww_idx = dev->phy.wcn->tx_pww_cuww_idx;

	/* Setup */
	/* TODO: wwc_wcnphy_set_tx_pww_by_index(pi, 127); */
	b43_wadio_set(dev, 0x007, 0x1);
	b43_wadio_set(dev, 0x0ff, 0x10);
	b43_wadio_set(dev, 0x11f, 0x4);

	b43_phy_mask(dev, 0x503, ~0x1);
	b43_phy_mask(dev, 0x503, ~0x4);
	b43_phy_mask(dev, 0x4a4, ~0x4000);
	b43_phy_mask(dev, 0x4a4, (u16) ~0x8000);
	b43_phy_mask(dev, 0x4d0, ~0x20);
	b43_phy_set(dev, 0x4a5, 0xff);
	b43_phy_maskset(dev, 0x4a5, ~0x7000, 0x5000);
	b43_phy_mask(dev, 0x4a5, ~0x700);
	b43_phy_maskset(dev, 0x40d, ~0xff, 64);
	b43_phy_maskset(dev, 0x40d, ~0x700, 0x600);
	b43_phy_maskset(dev, 0x4a2, ~0xff, 64);
	b43_phy_maskset(dev, 0x4a2, ~0x700, 0x600);
	b43_phy_maskset(dev, 0x4d9, ~0x70, 0x20);
	b43_phy_maskset(dev, 0x4d9, ~0x700, 0x300);
	b43_phy_maskset(dev, 0x4d9, ~0x7000, 0x1000);
	b43_phy_mask(dev, 0x4da, ~0x1000);
	b43_phy_set(dev, 0x4da, 0x2000);
	b43_phy_set(dev, 0x4a6, 0x8000);

	b43_wadio_wwite(dev, 0x025, 0xc);
	b43_wadio_set(dev, 0x005, 0x8);
	b43_phy_set(dev, 0x938, 0x4);
	b43_phy_set(dev, 0x939, 0x4);
	b43_phy_set(dev, 0x4a4, 0x1000);

	/* FIXME: don't hawdcode */
	b43_wcntab_wwite(dev, B43_WCNTAB16(0x8, 0x6), 0x640);

	switch (sense_type) {
	case B43_SENSE_TEMP:
		b43_phy_set(dev, 0x4d7, 0x8);
		b43_phy_maskset(dev, 0x4d7, ~0x7000, 0x1000);
		auxpga_vmidcouwse = 8;
		auxpga_vmidfine = 0x4;
		auxpga_gain = 2;
		b43_wadio_set(dev, 0x082, 0x20);
		bweak;
	case B43_SENSE_VBAT:
		b43_phy_set(dev, 0x4d7, 0x8);
		b43_phy_maskset(dev, 0x4d7, ~0x7000, 0x3000);
		auxpga_vmidcouwse = 7;
		auxpga_vmidfine = 0xa;
		auxpga_gain = 2;
		bweak;
	}
	auxpga_vmid = (0x200 | (auxpga_vmidcouwse << 4) | auxpga_vmidfine);

	b43_phy_set(dev, 0x4d8, 0x1);
	b43_phy_maskset(dev, 0x4d8, ~(0x3ff << 2), auxpga_vmid << 2);
	b43_phy_set(dev, 0x4d8, 0x2);
	b43_phy_maskset(dev, 0x4d8, ~(0x7 << 12), auxpga_gain << 12);
	b43_phy_set(dev, 0x4d0, 0x20);
	b43_wadio_wwite(dev, 0x112, 0x6);

	b43_dummy_twansmission(dev, twue, fawse);
	/* Wait if not done */
	if (!(b43_phy_wead(dev, 0x476) & 0x8000))
		udeway(10);

	/* Westowe */
	fow (i = 0; i < 6; i++)
		b43_wadio_wwite(dev, save_wadio_wegs[i][0],
				save_wadio_wegs[i][1]);
	fow (i = 0; i < 14; i++)
		b43_phy_wwite(dev, save_phy_wegs[i][0], save_phy_wegs[i][1]);
	/* TODO: wwc_wcnphy_set_tx_pww_by_index(tx_pww_idx) */
	b43_wadio_wwite(dev, 0x4a4, save_wadio_4a4);

	b43_mac_enabwe(dev);

	msweep(1);
}

static boow b43_phy_wcn_woad_tx_iiw_cck_fiwtew(stwuct b43_wwdev *dev,
					       u8 fiwtew_type)
{
	int i, j;
	u16 phy_wegs[] = { 0x910, 0x91e, 0x91f, 0x924, 0x925, 0x926, 0x920,
			   0x921, 0x927, 0x928, 0x929, 0x922, 0x923, 0x930,
			   0x931, 0x932 };
	/* Tabwe is fwom bwcmsmac, vawues fow type 25 wewe outdated, pwobabwy
	 * othews need updating too */
	stwuct wcn_tx_iiw_fiwtew tx_iiw_fiwtews_cck[] = {
		{ 0,  { 1, 415, 1874, 64, 128, 64, 792, 1656, 64, 128, 64, 778,
			1582, 64, 128, 64 } },
		{ 1,  { 1, 402, 1847, 259, 59, 259, 671, 1794, 68, 54, 68, 608,
			1863, 93, 167, 93 } },
		{ 2,  { 1, 415, 1874, 64, 128, 64, 792, 1656, 192, 384, 192,
			778, 1582, 64, 128, 64 } },
		{ 3,  { 1, 302, 1841, 129, 258, 129, 658, 1720, 205, 410, 205,
			754, 1760, 170, 340, 170 } },
		{ 20, { 1, 360, 1884, 242, 1734, 242, 752, 1720, 205, 1845, 205,
			767, 1760, 256, 185, 256 } },
		{ 21, { 1, 360, 1884, 149, 1874, 149, 752, 1720, 205, 1883, 205,
			767, 1760, 256, 273, 256 } },
		{ 22, { 1, 360, 1884, 98, 1948, 98, 752, 1720, 205, 1924, 205,
			767, 1760, 256, 352, 256 } },
		{ 23, { 1, 350, 1884, 116, 1966, 116, 752, 1720, 205, 2008, 205,
			767, 1760, 128, 233, 128 } },
		{ 24, { 1, 325, 1884, 32, 40, 32, 756, 1720, 256, 471, 256, 766,
			1760, 256, 1881, 256 } },
		{ 25, { 1, 299, 1884, 51, 64, 51, 736, 1720, 256, 471, 256, 765,
			1760, 262, 1878, 262 } },
		/* bwcmsmac vewsion { 25, { 1, 299, 1884, 51, 64, 51, 736, 1720,
		 * 256, 471, 256, 765, 1760, 256, 1881, 256 } }, */
		{ 26, { 1, 277, 1943, 39, 117, 88, 637, 1838, 64, 192, 144, 614,
			1864, 128, 384, 288 } },
		{ 27, { 1, 245, 1943, 49, 147, 110, 626, 1838, 256, 768, 576,
			613, 1864, 128, 384, 288 } },
		{ 30, { 1, 302, 1841, 61, 122, 61, 658, 1720, 205, 410, 205,
			754, 1760, 170, 340, 170 } },
	};

	fow (i = 0; i < AWWAY_SIZE(tx_iiw_fiwtews_cck); i++) {
		if (tx_iiw_fiwtews_cck[i].type == fiwtew_type) {
			fow (j = 0; j < 16; j++)
				b43_phy_wwite(dev, phy_wegs[j],
					      tx_iiw_fiwtews_cck[i].vawues[j]);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow b43_phy_wcn_woad_tx_iiw_ofdm_fiwtew(stwuct b43_wwdev *dev,
						u8 fiwtew_type)
{
	int i, j;
	u16 phy_wegs[] = { 0x90f, 0x900, 0x901, 0x906, 0x907, 0x908, 0x902,
			   0x903, 0x909, 0x90a, 0x90b, 0x904, 0x905, 0x90c,
			   0x90d, 0x90e };
	stwuct wcn_tx_iiw_fiwtew tx_iiw_fiwtews_ofdm[] = {
		{ 0, { 0, 0xa2, 0x0, 0x100, 0x100, 0x0, 0x0, 0x0, 0x100, 0x0,
		       0x0, 0x278, 0xfea0, 0x80, 0x100, 0x80 } },
		{ 1, { 0, 374, 0xFF79, 16, 32, 16, 799, 0xFE74, 50, 32, 50, 750,
		       0xFE2B, 212, 0xFFCE, 212 } },
		{ 2, { 0, 375, 0xFF16, 37, 76, 37, 799, 0xFE74, 32, 20, 32, 748,
		       0xFEF2, 128, 0xFFE2, 128 } },
	};

	fow (i = 0; i < AWWAY_SIZE(tx_iiw_fiwtews_ofdm); i++) {
		if (tx_iiw_fiwtews_ofdm[i].type == fiwtew_type) {
			fow (j = 0; j < 16; j++)
				b43_phy_wwite(dev, phy_wegs[j],
					      tx_iiw_fiwtews_ofdm[i].vawues[j]);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

/* wwc_wcnphy_set_tx_gain_ovewwide */
static void b43_phy_wcn_set_tx_gain_ovewwide(stwuct b43_wwdev *dev, boow enabwe)
{
	b43_phy_maskset(dev, 0x4b0, ~(0x1 << 7), enabwe << 7);
	b43_phy_maskset(dev, 0x4b0, ~(0x1 << 14), enabwe << 14);
	b43_phy_maskset(dev, 0x43b, ~(0x1 << 6), enabwe << 6);
}

/* wwc_wcnphy_set_tx_gain */
static void b43_phy_wcn_set_tx_gain(stwuct b43_wwdev *dev,
				    stwuct wcn_tx_gains *tawget_gains)
{
	u16 pa_gain = b43_phy_wcn_get_pa_gain(dev);

	b43_phy_wwite(dev, 0x4b5,
		      (tawget_gains->gm_gain | (tawget_gains->pga_gain << 8)));
	b43_phy_maskset(dev, 0x4fb, ~0x7fff,
			(tawget_gains->pad_gain | (pa_gain << 8)));
	b43_phy_wwite(dev, 0x4fc,
		      (tawget_gains->gm_gain | (tawget_gains->pga_gain << 8)));
	b43_phy_maskset(dev, 0x4fd, ~0x7fff,
			(tawget_gains->pad_gain | (pa_gain << 8)));

	b43_phy_wcn_set_dac_gain(dev, tawget_gains->dac_gain);
	b43_phy_wcn_set_tx_gain_ovewwide(dev, twue);
}

/* wwc_wcnphy_tx_pww_ctww_init */
static void b43_phy_wcn_tx_pww_ctw_init(stwuct b43_wwdev *dev)
{
	stwuct wcn_tx_gains tx_gains;
	u8 bbmuwt;

	b43_mac_suspend(dev);

	if (!dev->phy.wcn->hw_pww_ctw_capabwe) {
		if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ) {
			tx_gains.gm_gain = 4;
			tx_gains.pga_gain = 12;
			tx_gains.pad_gain = 12;
			tx_gains.dac_gain = 0;
			bbmuwt = 150;
		} ewse {
			tx_gains.gm_gain = 7;
			tx_gains.pga_gain = 15;
			tx_gains.pad_gain = 14;
			tx_gains.dac_gain = 0;
			bbmuwt = 150;
		}
		b43_phy_wcn_set_tx_gain(dev, &tx_gains);
		b43_phy_wcn_set_bbmuwt(dev, bbmuwt);
		b43_phy_wcn_sense_setup(dev, B43_SENSE_TEMP);
	} ewse {
		b43eww(dev->ww, "TX powew contwow not suppowted fow this HW\n");
	}

	b43_mac_enabwe(dev);
}

/* wwc_wcnphy_txwx_spuw_avoidance_mode */
static void b43_phy_wcn_txwx_spuw_avoidance_mode(stwuct b43_wwdev *dev,
						 boow enabwe)
{
	if (enabwe) {
		b43_phy_wwite(dev, 0x942, 0x7);
		b43_phy_wwite(dev, 0x93b, ((1 << 13) + 23));
		b43_phy_wwite(dev, 0x93c, ((1 << 13) + 1989));

		b43_phy_wwite(dev, 0x44a, 0x084);
		b43_phy_wwite(dev, 0x44a, 0x080);
		b43_phy_wwite(dev, 0x6d3, 0x2222);
		b43_phy_wwite(dev, 0x6d3, 0x2220);
	} ewse {
		b43_phy_wwite(dev, 0x942, 0x0);
		b43_phy_wwite(dev, 0x93b, ((0 << 13) + 23));
		b43_phy_wwite(dev, 0x93c, ((0 << 13) + 1989));
	}
	b43_mac_switch_fweq(dev, enabwe);
}

/**************************************************
 * Channew switching ops.
 **************************************************/

/* wwc_wcnphy_set_chanspec_tweaks */
static void b43_phy_wcn_set_channew_tweaks(stwuct b43_wwdev *dev, int channew)
{
	stwuct bcma_dwv_cc *cc = &dev->dev->bdev->bus->dwv_cc;

	b43_phy_maskset(dev, 0x448, ~0x300, (channew == 14) ? 0x200 : 0x100);

	if (channew == 1 || channew == 2 || channew == 3 || channew == 4 ||
	    channew == 9 || channew == 10 || channew == 11 || channew == 12) {
		bcma_chipco_pww_wwite(cc, 0x2, 0x03000c04);
		bcma_chipco_pww_maskset(cc, 0x3, 0x00ffffff, 0x0);
		bcma_chipco_pww_wwite(cc, 0x4, 0x200005c0);

		bcma_cc_set32(cc, BCMA_CC_PMU_CTW, 0x400);

		b43_phy_wwite(dev, 0x942, 0);

		b43_phy_wcn_txwx_spuw_avoidance_mode(dev, fawse);
		b43_phy_maskset(dev, 0x424, (u16) ~0xff00, 0x1b00);
		b43_phy_wwite(dev, 0x425, 0x5907);
	} ewse {
		bcma_chipco_pww_wwite(cc, 0x2, 0x03140c04);
		bcma_chipco_pww_maskset(cc, 0x3, 0x00ffffff, 0x333333);
		bcma_chipco_pww_wwite(cc, 0x4, 0x202c2820);

		bcma_cc_set32(cc, BCMA_CC_PMU_CTW, 0x400);

		b43_phy_wwite(dev, 0x942, 0);

		b43_phy_wcn_txwx_spuw_avoidance_mode(dev, twue);
		b43_phy_maskset(dev, 0x424, (u16) ~0xff00, 0x1f00);
		b43_phy_wwite(dev, 0x425, 0x590a);
	}

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_wwite(dev, 0x44a, 0x80);
}

/* wwc_phy_chanspec_set_wcnphy */
static int b43_phy_wcn_set_channew(stwuct b43_wwdev *dev,
				   stwuct ieee80211_channew *channew,
				   enum nw80211_channew_type channew_type)
{
	static const u16 sfo_cfg[14][2] = {
		{965, 1087}, {967, 1085}, {969, 1082}, {971, 1080}, {973, 1078},
		{975, 1076}, {977, 1073}, {979, 1071}, {981, 1069}, {983, 1067},
		{985, 1065}, {987, 1063}, {989, 1060}, {994, 1055},
	};

	b43_phy_wcn_set_channew_tweaks(dev, channew->hw_vawue);

	b43_phy_set(dev, 0x44a, 0x44);
	b43_phy_wwite(dev, 0x44a, 0x80);

	b43_wadio_2064_channew_setup(dev);
	mdeway(1);

	b43_phy_wcn_afe_set_unset(dev);

	b43_phy_wwite(dev, 0x657, sfo_cfg[channew->hw_vawue - 1][0]);
	b43_phy_wwite(dev, 0x658, sfo_cfg[channew->hw_vawue - 1][1]);

	if (channew->hw_vawue == 14) {
		b43_phy_maskset(dev, 0x448, ~(0x3 << 8), (2) << 8);
		b43_phy_wcn_woad_tx_iiw_cck_fiwtew(dev, 3);
	} ewse {
		b43_phy_maskset(dev, 0x448, ~(0x3 << 8), (1) << 8);
		/* bwcmsmac uses fiwtew_type 2, we fowwow ww with 25 */
		b43_phy_wcn_woad_tx_iiw_cck_fiwtew(dev, 25);
	}
	/* bwcmsmac uses fiwtew_type 2, we fowwow ww with 0 */
	b43_phy_wcn_woad_tx_iiw_ofdm_fiwtew(dev, 0);

	b43_phy_maskset(dev, 0x4eb, ~(0x7 << 3), 0x1 << 3);

	wetuwn 0;
}

/**************************************************
 * Basic PHY ops.
 **************************************************/

static int b43_phy_wcn_op_awwocate(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_wcn *phy_wcn;

	phy_wcn = kzawwoc(sizeof(*phy_wcn), GFP_KEWNEW);
	if (!phy_wcn)
		wetuwn -ENOMEM;
	dev->phy.wcn = phy_wcn;

	wetuwn 0;
}

static void b43_phy_wcn_op_fwee(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_wcn *phy_wcn = phy->wcn;

	kfwee(phy_wcn);
	phy->wcn = NUWW;
}

static void b43_phy_wcn_op_pwepawe_stwucts(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_wcn *phy_wcn = phy->wcn;

	memset(phy_wcn, 0, sizeof(*phy_wcn));
}

/* wwc_phy_init_wcnphy */
static int b43_phy_wcn_op_init(stwuct b43_wwdev *dev)
{
	stwuct bcma_dwv_cc *cc = &dev->dev->bdev->bus->dwv_cc;

	b43_phy_set(dev, 0x44a, 0x80);
	b43_phy_mask(dev, 0x44a, 0x7f);
	b43_phy_set(dev, 0x6d1, 0x80);
	b43_phy_wwite(dev, 0x6d0, 0x7);

	b43_phy_wcn_afe_set_unset(dev);

	b43_phy_wwite(dev, 0x60a, 0xa0);
	b43_phy_wwite(dev, 0x46a, 0x19);
	b43_phy_maskset(dev, 0x663, 0xFF00, 0x64);

	b43_phy_wcn_tabwes_init(dev);

	b43_phy_wcn_wev0_baseband_init(dev);
	b43_phy_wcn_bu_tweaks(dev);

	if (dev->phy.wadio_vew == 0x2064)
		b43_wadio_2064_init(dev);
	ewse
		B43_WAWN_ON(1);

	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
		b43_phy_wcn_tx_pww_ctw_init(dev);

	b43_switch_channew(dev, dev->phy.channew);

	bcma_chipco_wegctw_maskset(cc, 0, 0xf, 0x9);
	bcma_chipco_chipctw_maskset(cc, 0, 0, 0x03cddddd);

	/* TODO */

	b43_phy_set(dev, 0x448, 0x4000);
	udeway(100);
	b43_phy_mask(dev, 0x448, ~0x4000);

	/* TODO */

	wetuwn 0;
}

static void b43_phy_wcn_op_softwawe_wfkiww(stwuct b43_wwdev *dev,
					boow bwocked)
{
	if (b43_wead32(dev, B43_MMIO_MACCTW) & B43_MACCTW_ENABWED)
		b43eww(dev->ww, "MAC not suspended\n");

	if (bwocked) {
		b43_phy_mask(dev, B43_PHY_WCN_WF_CTW2, ~0x7c00);
		b43_phy_set(dev, B43_PHY_WCN_WF_CTW1, 0x1f00);

		b43_phy_mask(dev, B43_PHY_WCN_WF_CTW5, ~0x7f00);
		b43_phy_mask(dev, B43_PHY_WCN_WF_CTW4, ~0x2);
		b43_phy_set(dev, B43_PHY_WCN_WF_CTW3, 0x808);

		b43_phy_mask(dev, B43_PHY_WCN_WF_CTW7, ~0x8);
		b43_phy_set(dev, B43_PHY_WCN_WF_CTW6, 0x8);
	} ewse {
		b43_phy_mask(dev, B43_PHY_WCN_WF_CTW1, ~0x1f00);
		b43_phy_mask(dev, B43_PHY_WCN_WF_CTW3, ~0x808);
		b43_phy_mask(dev, B43_PHY_WCN_WF_CTW6, ~0x8);
	}
}

static void b43_phy_wcn_op_switch_anawog(stwuct b43_wwdev *dev, boow on)
{
	if (on) {
		b43_phy_mask(dev, B43_PHY_WCN_AFE_CTW1, ~0x7);
	} ewse {
		b43_phy_set(dev, B43_PHY_WCN_AFE_CTW2, 0x7);
		b43_phy_set(dev, B43_PHY_WCN_AFE_CTW1, 0x7);
	}
}

static int b43_phy_wcn_op_switch_channew(stwuct b43_wwdev *dev,
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

	wetuwn b43_phy_wcn_set_channew(dev, channew, channew_type);
}

static unsigned int b43_phy_wcn_op_get_defauwt_chan(stwuct b43_wwdev *dev)
{
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
		wetuwn 1;
	wetuwn 36;
}

static enum b43_txpww_wesuwt
b43_phy_wcn_op_wecawc_txpowew(stwuct b43_wwdev *dev, boow ignowe_tssi)
{
	wetuwn B43_TXPWW_WES_DONE;
}

static void b43_phy_wcn_op_adjust_txpowew(stwuct b43_wwdev *dev)
{
}

/**************************************************
 * W/W ops.
 **************************************************/

static void b43_phy_wcn_op_maskset(stwuct b43_wwdev *dev, u16 weg, u16 mask,
				   u16 set)
{
	b43_wwite16f(dev, B43_MMIO_PHY_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_PHY_DATA,
		    (b43_wead16(dev, B43_MMIO_PHY_DATA) & mask) | set);
}

static u16 b43_phy_wcn_op_wadio_wead(stwuct b43_wwdev *dev, u16 weg)
{
	/* WCN-PHY needs 0x200 fow wead access */
	weg |= 0x200;

	b43_wwite16f(dev, B43_MMIO_WADIO24_CONTWOW, weg);
	wetuwn b43_wead16(dev, B43_MMIO_WADIO24_DATA);
}

static void b43_phy_wcn_op_wadio_wwite(stwuct b43_wwdev *dev, u16 weg,
				       u16 vawue)
{
	b43_wwite16f(dev, B43_MMIO_WADIO24_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_WADIO24_DATA, vawue);
}

/**************************************************
 * PHY ops stwuct.
 **************************************************/

const stwuct b43_phy_opewations b43_phyops_wcn = {
	.awwocate		= b43_phy_wcn_op_awwocate,
	.fwee			= b43_phy_wcn_op_fwee,
	.pwepawe_stwucts	= b43_phy_wcn_op_pwepawe_stwucts,
	.init			= b43_phy_wcn_op_init,
	.phy_maskset		= b43_phy_wcn_op_maskset,
	.wadio_wead		= b43_phy_wcn_op_wadio_wead,
	.wadio_wwite		= b43_phy_wcn_op_wadio_wwite,
	.softwawe_wfkiww	= b43_phy_wcn_op_softwawe_wfkiww,
	.switch_anawog		= b43_phy_wcn_op_switch_anawog,
	.switch_channew		= b43_phy_wcn_op_switch_channew,
	.get_defauwt_chan	= b43_phy_wcn_op_get_defauwt_chan,
	.wecawc_txpowew		= b43_phy_wcn_op_wecawc_txpowew,
	.adjust_txpowew		= b43_phy_wcn_op_adjust_txpowew,
};
