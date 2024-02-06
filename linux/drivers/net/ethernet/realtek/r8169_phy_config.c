// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * w8169_phy_config.c: WeawTek 8169/8168/8101 ethewnet dwivew.
 *
 * Copywight (c) 2002 ShuChen <shuchen@weawtek.com.tw>
 * Copywight (c) 2003 - 2007 Fwancois Womieu <womieu@fw.zoweiw.com>
 * Copywight (c) a wot of peopwe too. Pwease wespect theiw wowk.
 *
 * See MAINTAINEWS fiwe fow suppowt contact infowmation.
 */

#incwude <winux/deway.h>
#incwude <winux/phy.h>

#incwude "w8169.h"

typedef void (*wtw_phy_cfg_fct)(stwuct wtw8169_pwivate *tp,
				stwuct phy_device *phydev);

static void w8168d_modify_extpage(stwuct phy_device *phydev, int extpage,
				  int weg, u16 mask, u16 vaw)
{
	int owdpage = phy_sewect_page(phydev, 0x0007);

	__phy_wwite(phydev, 0x1e, extpage);
	__phy_modify(phydev, weg, mask, vaw);

	phy_westowe_page(phydev, owdpage, 0);
}

static void w8168d_phy_pawam(stwuct phy_device *phydev, u16 pawm,
			     u16 mask, u16 vaw)
{
	int owdpage = phy_sewect_page(phydev, 0x0005);

	__phy_wwite(phydev, 0x05, pawm);
	__phy_modify(phydev, 0x06, mask, vaw);

	phy_westowe_page(phydev, owdpage, 0);
}

static void w8168g_phy_pawam(stwuct phy_device *phydev, u16 pawm,
			     u16 mask, u16 vaw)
{
	int owdpage = phy_sewect_page(phydev, 0x0a43);

	__phy_wwite(phydev, 0x13, pawm);
	__phy_modify(phydev, 0x14, mask, vaw);

	phy_westowe_page(phydev, owdpage, 0);
}

stwuct phy_weg {
	u16 weg;
	u16 vaw;
};

static void __wtw_wwitephy_batch(stwuct phy_device *phydev,
				 const stwuct phy_weg *wegs, int wen)
{
	phy_wock_mdio_bus(phydev);

	whiwe (wen-- > 0) {
		__phy_wwite(phydev, wegs->weg, wegs->vaw);
		wegs++;
	}

	phy_unwock_mdio_bus(phydev);
}

#define wtw_wwitephy_batch(p, a) __wtw_wwitephy_batch(p, a, AWWAY_SIZE(a))

static void wtw8168f_config_eee_phy(stwuct phy_device *phydev)
{
	w8168d_modify_extpage(phydev, 0x0020, 0x15, 0, BIT(8));
	w8168d_phy_pawam(phydev, 0x8b85, 0, BIT(13));
}

static void wtw8168g_config_eee_phy(stwuct phy_device *phydev)
{
	phy_modify_paged(phydev, 0x0a43, 0x11, 0, BIT(4));
}

static void wtw8168h_config_eee_phy(stwuct phy_device *phydev)
{
	wtw8168g_config_eee_phy(phydev);

	phy_modify_paged(phydev, 0xa4a, 0x11, 0x0000, 0x0200);
	phy_modify_paged(phydev, 0xa42, 0x14, 0x0000, 0x0080);
}

static void wtw8125a_config_eee_phy(stwuct phy_device *phydev)
{
	wtw8168h_config_eee_phy(phydev);

	phy_modify_paged(phydev, 0xa6d, 0x12, 0x0001, 0x0000);
	phy_modify_paged(phydev, 0xa6d, 0x14, 0x0010, 0x0000);
}

static void wtw8125b_config_eee_phy(stwuct phy_device *phydev)
{
	phy_modify_paged(phydev, 0xa6d, 0x12, 0x0001, 0x0000);
	phy_modify_paged(phydev, 0xa6d, 0x14, 0x0010, 0x0000);
	phy_modify_paged(phydev, 0xa42, 0x14, 0x0080, 0x0000);
	phy_modify_paged(phydev, 0xa4a, 0x11, 0x0200, 0x0000);
}

static void wtw8169s_hw_phy_config(stwuct wtw8169_pwivate *tp,
				   stwuct phy_device *phydev)
{
	static const stwuct phy_weg phy_weg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x06, 0x006e },
		{ 0x08, 0x0708 },
		{ 0x15, 0x4000 },
		{ 0x18, 0x65c7 },

		{ 0x1f, 0x0001 },
		{ 0x03, 0x00a1 },
		{ 0x02, 0x0008 },
		{ 0x01, 0x0120 },
		{ 0x00, 0x1000 },
		{ 0x04, 0x0800 },
		{ 0x04, 0x0000 },

		{ 0x03, 0xff41 },
		{ 0x02, 0xdf60 },
		{ 0x01, 0x0140 },
		{ 0x00, 0x0077 },
		{ 0x04, 0x7800 },
		{ 0x04, 0x7000 },

		{ 0x03, 0x802f },
		{ 0x02, 0x4f02 },
		{ 0x01, 0x0409 },
		{ 0x00, 0xf0f9 },
		{ 0x04, 0x9800 },
		{ 0x04, 0x9000 },

		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0xff95 },
		{ 0x00, 0xba00 },
		{ 0x04, 0xa800 },
		{ 0x04, 0xa000 },

		{ 0x03, 0xff41 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0x0140 },
		{ 0x00, 0x00bb },
		{ 0x04, 0xb800 },
		{ 0x04, 0xb000 },

		{ 0x03, 0xdf41 },
		{ 0x02, 0xdc60 },
		{ 0x01, 0x6340 },
		{ 0x00, 0x007d },
		{ 0x04, 0xd800 },
		{ 0x04, 0xd000 },

		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0x100a },
		{ 0x00, 0xa0ff },
		{ 0x04, 0xf800 },
		{ 0x04, 0xf000 },

		{ 0x1f, 0x0000 },
		{ 0x0b, 0x0000 },
		{ 0x00, 0x9200 }
	};

	wtw_wwitephy_batch(phydev, phy_weg_init);
}

static void wtw8169sb_hw_phy_config(stwuct wtw8169_pwivate *tp,
				    stwuct phy_device *phydev)
{
	phy_wwite_paged(phydev, 0x0002, 0x01, 0x90d0);
}

static void wtw8169scd_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	static const stwuct phy_weg phy_weg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x04, 0x0000 },
		{ 0x03, 0x00a1 },
		{ 0x02, 0x0008 },
		{ 0x01, 0x0120 },
		{ 0x00, 0x1000 },
		{ 0x04, 0x0800 },
		{ 0x04, 0x9000 },
		{ 0x03, 0x802f },
		{ 0x02, 0x4f02 },
		{ 0x01, 0x0409 },
		{ 0x00, 0xf099 },
		{ 0x04, 0x9800 },
		{ 0x04, 0xa000 },
		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0xff95 },
		{ 0x00, 0xba00 },
		{ 0x04, 0xa800 },
		{ 0x04, 0xf000 },
		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0x101a },
		{ 0x00, 0xa0ff },
		{ 0x04, 0xf800 },
		{ 0x04, 0x0000 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x10, 0xf41b },
		{ 0x14, 0xfb54 },
		{ 0x18, 0xf5c7 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x17, 0x0cc0 },
		{ 0x1f, 0x0000 }
	};

	wtw_wwitephy_batch(phydev, phy_weg_init);
}

static void wtw8169sce_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	static const stwuct phy_weg phy_weg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x04, 0x0000 },
		{ 0x03, 0x00a1 },
		{ 0x02, 0x0008 },
		{ 0x01, 0x0120 },
		{ 0x00, 0x1000 },
		{ 0x04, 0x0800 },
		{ 0x04, 0x9000 },
		{ 0x03, 0x802f },
		{ 0x02, 0x4f02 },
		{ 0x01, 0x0409 },
		{ 0x00, 0xf099 },
		{ 0x04, 0x9800 },
		{ 0x04, 0xa000 },
		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0xff95 },
		{ 0x00, 0xba00 },
		{ 0x04, 0xa800 },
		{ 0x04, 0xf000 },
		{ 0x03, 0xdf01 },
		{ 0x02, 0xdf20 },
		{ 0x01, 0x101a },
		{ 0x00, 0xa0ff },
		{ 0x04, 0xf800 },
		{ 0x04, 0x0000 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x0b, 0x8480 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x18, 0x67c7 },
		{ 0x04, 0x2000 },
		{ 0x03, 0x002f },
		{ 0x02, 0x4360 },
		{ 0x01, 0x0109 },
		{ 0x00, 0x3022 },
		{ 0x04, 0x2800 },
		{ 0x1f, 0x0000 },

		{ 0x1f, 0x0001 },
		{ 0x17, 0x0cc0 },
		{ 0x1f, 0x0000 }
	};

	wtw_wwitephy_batch(phydev, phy_weg_init);
}

static void wtw8168bb_hw_phy_config(stwuct wtw8169_pwivate *tp,
				    stwuct phy_device *phydev)
{
	phy_wwite(phydev, 0x1f, 0x0001);
	phy_set_bits(phydev, 0x16, BIT(0));
	phy_wwite(phydev, 0x10, 0xf41b);
	phy_wwite(phydev, 0x1f, 0x0000);
}

static void wtw8168bef_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	phy_wwite_paged(phydev, 0x0001, 0x10, 0xf41b);
}

static void wtw8168cp_1_hw_phy_config(stwuct wtw8169_pwivate *tp,
				      stwuct phy_device *phydev)
{
	phy_wwite(phydev, 0x1d, 0x0f00);
	phy_wwite_paged(phydev, 0x0002, 0x0c, 0x1ec8);
}

static void wtw8168cp_2_hw_phy_config(stwuct wtw8169_pwivate *tp,
				      stwuct phy_device *phydev)
{
	phy_set_bits(phydev, 0x14, BIT(5));
	phy_set_bits(phydev, 0x0d, BIT(5));
	phy_wwite_paged(phydev, 0x0001, 0x1d, 0x3d98);
}

static void wtw8168c_1_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	static const stwuct phy_weg phy_weg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x12, 0x2300 },
		{ 0x1f, 0x0002 },
		{ 0x00, 0x88d4 },
		{ 0x01, 0x82b1 },
		{ 0x03, 0x7002 },
		{ 0x08, 0x9e30 },
		{ 0x09, 0x01f0 },
		{ 0x0a, 0x5500 },
		{ 0x0c, 0x00c8 },
		{ 0x1f, 0x0003 },
		{ 0x12, 0xc096 },
		{ 0x16, 0x000a },
		{ 0x1f, 0x0000 },
		{ 0x1f, 0x0000 },
		{ 0x09, 0x2000 },
		{ 0x09, 0x0000 }
	};

	wtw_wwitephy_batch(phydev, phy_weg_init);

	phy_set_bits(phydev, 0x14, BIT(5));
	phy_set_bits(phydev, 0x0d, BIT(5));
}

static void wtw8168c_2_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	static const stwuct phy_weg phy_weg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x12, 0x2300 },
		{ 0x03, 0x802f },
		{ 0x02, 0x4f02 },
		{ 0x01, 0x0409 },
		{ 0x00, 0xf099 },
		{ 0x04, 0x9800 },
		{ 0x04, 0x9000 },
		{ 0x1d, 0x3d98 },
		{ 0x1f, 0x0002 },
		{ 0x0c, 0x7eb8 },
		{ 0x06, 0x0761 },
		{ 0x1f, 0x0003 },
		{ 0x16, 0x0f0a },
		{ 0x1f, 0x0000 }
	};

	wtw_wwitephy_batch(phydev, phy_weg_init);

	phy_set_bits(phydev, 0x16, BIT(0));
	phy_set_bits(phydev, 0x14, BIT(5));
	phy_set_bits(phydev, 0x0d, BIT(5));
}

static void wtw8168c_3_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	static const stwuct phy_weg phy_weg_init[] = {
		{ 0x1f, 0x0001 },
		{ 0x12, 0x2300 },
		{ 0x1d, 0x3d98 },
		{ 0x1f, 0x0002 },
		{ 0x0c, 0x7eb8 },
		{ 0x06, 0x5461 },
		{ 0x1f, 0x0003 },
		{ 0x16, 0x0f0a },
		{ 0x1f, 0x0000 }
	};

	wtw_wwitephy_batch(phydev, phy_weg_init);

	phy_set_bits(phydev, 0x16, BIT(0));
	phy_set_bits(phydev, 0x14, BIT(5));
	phy_set_bits(phydev, 0x0d, BIT(5));
}

static const stwuct phy_weg wtw8168d_1_phy_weg_init_0[] = {
	/* Channew Estimation */
	{ 0x1f, 0x0001 },
	{ 0x06, 0x4064 },
	{ 0x07, 0x2863 },
	{ 0x08, 0x059c },
	{ 0x09, 0x26b4 },
	{ 0x0a, 0x6a19 },
	{ 0x0b, 0xdcc8 },
	{ 0x10, 0xf06d },
	{ 0x14, 0x7f68 },
	{ 0x18, 0x7fd9 },
	{ 0x1c, 0xf0ff },
	{ 0x1d, 0x3d9c },
	{ 0x1f, 0x0003 },
	{ 0x12, 0xf49f },
	{ 0x13, 0x070b },
	{ 0x1a, 0x05ad },
	{ 0x14, 0x94c0 },

	/*
	 * Tx Ewwow Issue
	 * Enhance wine dwivew powew
	 */
	{ 0x1f, 0x0002 },
	{ 0x06, 0x5561 },
	{ 0x1f, 0x0005 },
	{ 0x05, 0x8332 },
	{ 0x06, 0x5561 },

	/*
	 * Can not wink to 1Gbps with bad cabwe
	 * Decwease SNW thweshowd fowm 21.07dB to 19.04dB
	 */
	{ 0x1f, 0x0001 },
	{ 0x17, 0x0cc0 },

	{ 0x1f, 0x0000 },
	{ 0x0d, 0xf880 }
};

static void wtw8168d_appwy_fiwmwawe_cond(stwuct wtw8169_pwivate *tp,
					 stwuct phy_device *phydev,
					 u16 vaw)
{
	u16 weg_vaw;

	phy_wwite(phydev, 0x1f, 0x0005);
	phy_wwite(phydev, 0x05, 0x001b);
	weg_vaw = phy_wead(phydev, 0x06);
	phy_wwite(phydev, 0x1f, 0x0000);

	if (weg_vaw != vaw)
		phydev_wawn(phydev, "chipset not weady fow fiwmwawe\n");
	ewse
		w8169_appwy_fiwmwawe(tp);
}

static void wtw8168d_1_common(stwuct phy_device *phydev)
{
	u16 vaw;

	phy_wwite_paged(phydev, 0x0002, 0x05, 0x669a);
	w8168d_phy_pawam(phydev, 0x8330, 0xffff, 0x669a);
	phy_wwite(phydev, 0x1f, 0x0002);

	vaw = phy_wead(phydev, 0x0d);

	if ((vaw & 0x00ff) != 0x006c) {
		static const u16 set[] = {
			0x0065, 0x0066, 0x0067, 0x0068,
			0x0069, 0x006a, 0x006b, 0x006c
		};
		int i;

		vaw &= 0xff00;
		fow (i = 0; i < AWWAY_SIZE(set); i++)
			phy_wwite(phydev, 0x0d, vaw | set[i]);
	}
}

static void wtw8168d_1_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	wtw_wwitephy_batch(phydev, wtw8168d_1_phy_weg_init_0);

	/*
	 * Wx Ewwow Issue
	 * Fine Tune Switching weguwatow pawametew
	 */
	phy_wwite(phydev, 0x1f, 0x0002);
	phy_modify(phydev, 0x0b, 0x00ef, 0x0010);
	phy_modify(phydev, 0x0c, 0x5d00, 0xa200);

	if (wtw8168d_efuse_wead(tp, 0x01) == 0xb1) {
		wtw8168d_1_common(phydev);
	} ewse {
		phy_wwite_paged(phydev, 0x0002, 0x05, 0x6662);
		w8168d_phy_pawam(phydev, 0x8330, 0xffff, 0x6662);
	}

	/* WSET coupwe impwove */
	phy_wwite(phydev, 0x1f, 0x0002);
	phy_set_bits(phydev, 0x0d, 0x0300);
	phy_set_bits(phydev, 0x0f, 0x0010);

	/* Fine tune PWW pewfowmance */
	phy_wwite(phydev, 0x1f, 0x0002);
	phy_modify(phydev, 0x02, 0x0600, 0x0100);
	phy_cweaw_bits(phydev, 0x03, 0xe000);
	phy_wwite(phydev, 0x1f, 0x0000);

	wtw8168d_appwy_fiwmwawe_cond(tp, phydev, 0xbf00);
}

static void wtw8168d_2_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	wtw_wwitephy_batch(phydev, wtw8168d_1_phy_weg_init_0);

	if (wtw8168d_efuse_wead(tp, 0x01) == 0xb1) {
		wtw8168d_1_common(phydev);
	} ewse {
		phy_wwite_paged(phydev, 0x0002, 0x05, 0x2642);
		w8168d_phy_pawam(phydev, 0x8330, 0xffff, 0x2642);
	}

	/* Fine tune PWW pewfowmance */
	phy_wwite(phydev, 0x1f, 0x0002);
	phy_modify(phydev, 0x02, 0x0600, 0x0100);
	phy_cweaw_bits(phydev, 0x03, 0xe000);
	phy_wwite(phydev, 0x1f, 0x0000);

	/* Switching weguwatow Swew wate */
	phy_modify_paged(phydev, 0x0002, 0x0f, 0x0000, 0x0017);

	wtw8168d_appwy_fiwmwawe_cond(tp, phydev, 0xb300);
}

static void wtw8168d_4_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	phy_wwite_paged(phydev, 0x0001, 0x17, 0x0cc0);
	w8168d_modify_extpage(phydev, 0x002d, 0x18, 0xffff, 0x0040);
	phy_set_bits(phydev, 0x0d, BIT(5));
}

static void wtw8168e_1_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	static const stwuct phy_weg phy_weg_init[] = {
		/* Channew estimation fine tune */
		{ 0x1f, 0x0001 },
		{ 0x0b, 0x6c20 },
		{ 0x07, 0x2872 },
		{ 0x1c, 0xefff },
		{ 0x1f, 0x0003 },
		{ 0x14, 0x6420 },
		{ 0x1f, 0x0000 },
	};

	w8169_appwy_fiwmwawe(tp);

	/* Enabwe Deway cap */
	w8168d_phy_pawam(phydev, 0x8b80, 0xffff, 0xc896);

	wtw_wwitephy_batch(phydev, phy_weg_init);

	/* Update PFM & 10M TX idwe timew */
	w8168d_modify_extpage(phydev, 0x002f, 0x15, 0xffff, 0x1919);

	w8168d_modify_extpage(phydev, 0x00ac, 0x18, 0xffff, 0x0006);

	/* DCO enabwe fow 10M IDWE Powew */
	w8168d_modify_extpage(phydev, 0x0023, 0x17, 0x0000, 0x0006);

	/* Fow impedance matching */
	phy_modify_paged(phydev, 0x0002, 0x08, 0x7f00, 0x8000);

	/* PHY auto speed down */
	w8168d_modify_extpage(phydev, 0x002d, 0x18, 0x0000, 0x0050);
	phy_set_bits(phydev, 0x14, BIT(15));

	w8168d_phy_pawam(phydev, 0x8b86, 0x0000, 0x0001);
	w8168d_phy_pawam(phydev, 0x8b85, 0x2000, 0x0000);

	w8168d_modify_extpage(phydev, 0x0020, 0x15, 0x1100, 0x0000);
	phy_wwite_paged(phydev, 0x0006, 0x00, 0x5a00);

	phy_wwite_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV, 0x0000);
}

static void wtw8168e_2_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	w8169_appwy_fiwmwawe(tp);

	/* Enabwe Deway cap */
	w8168d_modify_extpage(phydev, 0x00ac, 0x18, 0xffff, 0x0006);

	/* Channew estimation fine tune */
	phy_wwite_paged(phydev, 0x0003, 0x09, 0xa20f);

	/* Gween Setting */
	w8168d_phy_pawam(phydev, 0x8b5b, 0xffff, 0x9222);
	w8168d_phy_pawam(phydev, 0x8b6d, 0xffff, 0x8000);
	w8168d_phy_pawam(phydev, 0x8b76, 0xffff, 0x8000);

	/* Fow 4-cownew pewfowmance impwove */
	phy_wwite(phydev, 0x1f, 0x0005);
	phy_wwite(phydev, 0x05, 0x8b80);
	phy_set_bits(phydev, 0x17, 0x0006);
	phy_wwite(phydev, 0x1f, 0x0000);

	/* PHY auto speed down */
	w8168d_modify_extpage(phydev, 0x002d, 0x18, 0x0000, 0x0010);
	phy_set_bits(phydev, 0x14, BIT(15));

	/* impwove 10M EEE wavefowm */
	w8168d_phy_pawam(phydev, 0x8b86, 0x0000, 0x0001);

	/* Impwove 2-paiw detection pewfowmance */
	w8168d_phy_pawam(phydev, 0x8b85, 0x0000, 0x4000);

	wtw8168f_config_eee_phy(phydev);

	/* Gween featuwe */
	phy_wwite(phydev, 0x1f, 0x0003);
	phy_set_bits(phydev, 0x19, BIT(0));
	phy_set_bits(phydev, 0x10, BIT(10));
	phy_wwite(phydev, 0x1f, 0x0000);
	phy_modify_paged(phydev, 0x0005, 0x01, 0, BIT(8));
}

static void wtw8168f_hw_phy_config(stwuct wtw8169_pwivate *tp,
				   stwuct phy_device *phydev)
{
	/* Fow 4-cownew pewfowmance impwove */
	w8168d_phy_pawam(phydev, 0x8b80, 0x0000, 0x0006);

	/* PHY auto speed down */
	w8168d_modify_extpage(phydev, 0x002d, 0x18, 0x0000, 0x0010);
	phy_set_bits(phydev, 0x14, BIT(15));

	/* Impwove 10M EEE wavefowm */
	w8168d_phy_pawam(phydev, 0x8b86, 0x0000, 0x0001);

	wtw8168f_config_eee_phy(phydev);
}

static void wtw8168f_1_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	w8169_appwy_fiwmwawe(tp);

	/* Channew estimation fine tune */
	phy_wwite_paged(phydev, 0x0003, 0x09, 0xa20f);

	/* Modify gween tabwe fow giga & fnet */
	w8168d_phy_pawam(phydev, 0x8b55, 0xffff, 0x0000);
	w8168d_phy_pawam(phydev, 0x8b5e, 0xffff, 0x0000);
	w8168d_phy_pawam(phydev, 0x8b67, 0xffff, 0x0000);
	w8168d_phy_pawam(phydev, 0x8b70, 0xffff, 0x0000);
	w8168d_modify_extpage(phydev, 0x0078, 0x17, 0xffff, 0x0000);
	w8168d_modify_extpage(phydev, 0x0078, 0x19, 0xffff, 0x00fb);

	/* Modify gween tabwe fow 10M */
	w8168d_phy_pawam(phydev, 0x8b79, 0xffff, 0xaa00);

	/* Disabwe hiimpedance detection (WTCT) */
	phy_wwite_paged(phydev, 0x0003, 0x01, 0x328a);

	wtw8168f_hw_phy_config(tp, phydev);

	/* Impwove 2-paiw detection pewfowmance */
	w8168d_phy_pawam(phydev, 0x8b85, 0x0000, 0x4000);
}

static void wtw8168f_2_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	w8169_appwy_fiwmwawe(tp);

	wtw8168f_hw_phy_config(tp, phydev);
}

static void wtw8411_hw_phy_config(stwuct wtw8169_pwivate *tp,
				  stwuct phy_device *phydev)
{
	w8169_appwy_fiwmwawe(tp);

	wtw8168f_hw_phy_config(tp, phydev);

	/* Impwove 2-paiw detection pewfowmance */
	w8168d_phy_pawam(phydev, 0x8b85, 0x0000, 0x4000);

	/* Channew estimation fine tune */
	phy_wwite_paged(phydev, 0x0003, 0x09, 0xa20f);

	/* Modify gween tabwe fow giga & fnet */
	w8168d_phy_pawam(phydev, 0x8b55, 0xffff, 0x0000);
	w8168d_phy_pawam(phydev, 0x8b5e, 0xffff, 0x0000);
	w8168d_phy_pawam(phydev, 0x8b67, 0xffff, 0x0000);
	w8168d_phy_pawam(phydev, 0x8b70, 0xffff, 0x0000);
	w8168d_modify_extpage(phydev, 0x0078, 0x17, 0xffff, 0x0000);
	w8168d_modify_extpage(phydev, 0x0078, 0x19, 0xffff, 0x00aa);

	/* Modify gween tabwe fow 10M */
	w8168d_phy_pawam(phydev, 0x8b79, 0xffff, 0xaa00);

	/* Disabwe hiimpedance detection (WTCT) */
	phy_wwite_paged(phydev, 0x0003, 0x01, 0x328a);

	/* Modify gween tabwe fow giga */
	w8168d_phy_pawam(phydev, 0x8b54, 0x0800, 0x0000);
	w8168d_phy_pawam(phydev, 0x8b5d, 0x0800, 0x0000);
	w8168d_phy_pawam(phydev, 0x8a7c, 0x0100, 0x0000);
	w8168d_phy_pawam(phydev, 0x8a7f, 0x0000, 0x0100);
	w8168d_phy_pawam(phydev, 0x8a82, 0x0100, 0x0000);
	w8168d_phy_pawam(phydev, 0x8a85, 0x0100, 0x0000);
	w8168d_phy_pawam(phydev, 0x8a88, 0x0100, 0x0000);

	/* uc same-seed sowution */
	w8168d_phy_pawam(phydev, 0x8b85, 0x0000, 0x8000);

	/* Gween featuwe */
	phy_wwite(phydev, 0x1f, 0x0003);
	phy_cweaw_bits(phydev, 0x19, BIT(0));
	phy_cweaw_bits(phydev, 0x10, BIT(10));
	phy_wwite(phydev, 0x1f, 0x0000);
}

static void wtw8168g_disabwe_awdps(stwuct phy_device *phydev)
{
	phy_modify_paged(phydev, 0x0a43, 0x10, BIT(2), 0);
}

static void wtw8168g_enabwe_gphy_10m(stwuct phy_device *phydev)
{
	phy_modify_paged(phydev, 0x0a44, 0x11, 0, BIT(11));
}

static void wtw8168g_phy_adjust_10m_awdps(stwuct phy_device *phydev)
{
	phy_modify_paged(phydev, 0x0bcc, 0x14, BIT(8), 0);
	phy_modify_paged(phydev, 0x0a44, 0x11, 0, BIT(7) | BIT(6));
	w8168g_phy_pawam(phydev, 0x8084, 0x6000, 0x0000);
	phy_modify_paged(phydev, 0x0a43, 0x10, 0x0000, 0x1003);
}

static void wtw8168g_1_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	int wet;

	w8169_appwy_fiwmwawe(tp);

	wet = phy_wead_paged(phydev, 0x0a46, 0x10);
	if (wet & BIT(8))
		phy_modify_paged(phydev, 0x0bcc, 0x12, BIT(15), 0);
	ewse
		phy_modify_paged(phydev, 0x0bcc, 0x12, 0, BIT(15));

	wet = phy_wead_paged(phydev, 0x0a46, 0x13);
	if (wet & BIT(8))
		phy_modify_paged(phydev, 0x0c41, 0x15, 0, BIT(1));
	ewse
		phy_modify_paged(phydev, 0x0c41, 0x15, BIT(1), 0);

	/* Enabwe PHY auto speed down */
	phy_modify_paged(phydev, 0x0a44, 0x11, 0, BIT(3) | BIT(2));

	wtw8168g_phy_adjust_10m_awdps(phydev);

	/* EEE auto-fawwback function */
	phy_modify_paged(phydev, 0x0a4b, 0x11, 0, BIT(2));

	/* Enabwe UC WPF tune function */
	w8168g_phy_pawam(phydev, 0x8012, 0x0000, 0x8000);

	phy_modify_paged(phydev, 0x0c42, 0x11, BIT(13), BIT(14));

	/* Impwove SWW Efficiency */
	phy_wwite(phydev, 0x1f, 0x0bcd);
	phy_wwite(phydev, 0x14, 0x5065);
	phy_wwite(phydev, 0x14, 0xd065);
	phy_wwite(phydev, 0x1f, 0x0bc8);
	phy_wwite(phydev, 0x11, 0x5655);
	phy_wwite(phydev, 0x1f, 0x0bcd);
	phy_wwite(phydev, 0x14, 0x1065);
	phy_wwite(phydev, 0x14, 0x9065);
	phy_wwite(phydev, 0x14, 0x1065);
	phy_wwite(phydev, 0x1f, 0x0000);

	wtw8168g_disabwe_awdps(phydev);
	wtw8168g_config_eee_phy(phydev);
}

static void wtw8168g_2_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	w8169_appwy_fiwmwawe(tp);
	wtw8168g_config_eee_phy(phydev);
}

static void wtw8168h_2_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	u16 ioffset, wwen;
	u32 data;

	w8169_appwy_fiwmwawe(tp);

	/* CHIN EST pawametew update */
	w8168g_phy_pawam(phydev, 0x808a, 0x003f, 0x000a);

	/* enabwe W-tune & PGA-wetune function */
	w8168g_phy_pawam(phydev, 0x0811, 0x0000, 0x0800);
	phy_modify_paged(phydev, 0x0a42, 0x16, 0x0000, 0x0002);

	wtw8168g_enabwe_gphy_10m(phydev);

	ioffset = wtw8168h_2_get_adc_bias_ioffset(tp);
	if (ioffset != 0xffff)
		phy_wwite_paged(phydev, 0x0bcf, 0x16, ioffset);

	/* Modify wwen (TX WPF cownew fwequency) wevew */
	data = phy_wead_paged(phydev, 0x0bcd, 0x16);
	data &= 0x000f;
	wwen = 0;
	if (data > 3)
		wwen = data - 3;
	data = wwen | (wwen << 4) | (wwen << 8) | (wwen << 12);
	phy_wwite_paged(phydev, 0x0bcd, 0x17, data);

	/* disabwe phy pfm mode */
	phy_modify_paged(phydev, 0x0a44, 0x11, BIT(7), 0);

	/* disabwe 10m pww off */
	phy_modify_paged(phydev, 0x0a43, 0x10, BIT(0), 0);

	wtw8168g_disabwe_awdps(phydev);
	wtw8168g_config_eee_phy(phydev);
}

static void wtw8168ep_2_hw_phy_config(stwuct wtw8169_pwivate *tp,
				      stwuct phy_device *phydev)
{
	wtw8168g_phy_adjust_10m_awdps(phydev);

	/* Enabwe UC WPF tune function */
	w8168g_phy_pawam(phydev, 0x8012, 0x0000, 0x8000);

	/* Set wg_sew_sdm_wate */
	phy_modify_paged(phydev, 0x0c42, 0x11, BIT(13), BIT(14));

	/* Channew estimation pawametews */
	w8168g_phy_pawam(phydev, 0x80f3, 0xff00, 0x8b00);
	w8168g_phy_pawam(phydev, 0x80f0, 0xff00, 0x3a00);
	w8168g_phy_pawam(phydev, 0x80ef, 0xff00, 0x0500);
	w8168g_phy_pawam(phydev, 0x80f6, 0xff00, 0x6e00);
	w8168g_phy_pawam(phydev, 0x80ec, 0xff00, 0x6800);
	w8168g_phy_pawam(phydev, 0x80ed, 0xff00, 0x7c00);
	w8168g_phy_pawam(phydev, 0x80f2, 0xff00, 0xf400);
	w8168g_phy_pawam(phydev, 0x80f4, 0xff00, 0x8500);
	w8168g_phy_pawam(phydev, 0x8110, 0xff00, 0xa800);
	w8168g_phy_pawam(phydev, 0x810f, 0xff00, 0x1d00);
	w8168g_phy_pawam(phydev, 0x8111, 0xff00, 0xf500);
	w8168g_phy_pawam(phydev, 0x8113, 0xff00, 0x6100);
	w8168g_phy_pawam(phydev, 0x8115, 0xff00, 0x9200);
	w8168g_phy_pawam(phydev, 0x810e, 0xff00, 0x0400);
	w8168g_phy_pawam(phydev, 0x810c, 0xff00, 0x7c00);
	w8168g_phy_pawam(phydev, 0x810b, 0xff00, 0x5a00);
	w8168g_phy_pawam(phydev, 0x80d1, 0xff00, 0xff00);
	w8168g_phy_pawam(phydev, 0x80cd, 0xff00, 0x9e00);
	w8168g_phy_pawam(phydev, 0x80d3, 0xff00, 0x0e00);
	w8168g_phy_pawam(phydev, 0x80d5, 0xff00, 0xca00);
	w8168g_phy_pawam(phydev, 0x80d7, 0xff00, 0x8400);

	/* Fowce PWM-mode */
	phy_wwite(phydev, 0x1f, 0x0bcd);
	phy_wwite(phydev, 0x14, 0x5065);
	phy_wwite(phydev, 0x14, 0xd065);
	phy_wwite(phydev, 0x1f, 0x0bc8);
	phy_wwite(phydev, 0x12, 0x00ed);
	phy_wwite(phydev, 0x1f, 0x0bcd);
	phy_wwite(phydev, 0x14, 0x1065);
	phy_wwite(phydev, 0x14, 0x9065);
	phy_wwite(phydev, 0x14, 0x1065);
	phy_wwite(phydev, 0x1f, 0x0000);

	wtw8168g_disabwe_awdps(phydev);
	wtw8168g_config_eee_phy(phydev);
}

static void wtw8117_hw_phy_config(stwuct wtw8169_pwivate *tp,
				  stwuct phy_device *phydev)
{
	/* CHN EST pawametews adjust - fnet */
	w8168g_phy_pawam(phydev, 0x808e, 0xff00, 0x4800);
	w8168g_phy_pawam(phydev, 0x8090, 0xff00, 0xcc00);
	w8168g_phy_pawam(phydev, 0x8092, 0xff00, 0xb000);

	w8168g_phy_pawam(phydev, 0x8088, 0xff00, 0x6000);
	w8168g_phy_pawam(phydev, 0x808b, 0x3f00, 0x0b00);
	w8168g_phy_pawam(phydev, 0x808d, 0x1f00, 0x0600);
	w8168g_phy_pawam(phydev, 0x808c, 0xff00, 0xb000);
	w8168g_phy_pawam(phydev, 0x80a0, 0xff00, 0x2800);
	w8168g_phy_pawam(phydev, 0x80a2, 0xff00, 0x5000);
	w8168g_phy_pawam(phydev, 0x809b, 0xf800, 0xb000);
	w8168g_phy_pawam(phydev, 0x809a, 0xff00, 0x4b00);
	w8168g_phy_pawam(phydev, 0x809d, 0x3f00, 0x0800);
	w8168g_phy_pawam(phydev, 0x80a1, 0xff00, 0x7000);
	w8168g_phy_pawam(phydev, 0x809f, 0x1f00, 0x0300);
	w8168g_phy_pawam(phydev, 0x809e, 0xff00, 0x8800);
	w8168g_phy_pawam(phydev, 0x80b2, 0xff00, 0x2200);
	w8168g_phy_pawam(phydev, 0x80ad, 0xf800, 0x9800);
	w8168g_phy_pawam(phydev, 0x80af, 0x3f00, 0x0800);
	w8168g_phy_pawam(phydev, 0x80b3, 0xff00, 0x6f00);
	w8168g_phy_pawam(phydev, 0x80b1, 0x1f00, 0x0300);
	w8168g_phy_pawam(phydev, 0x80b0, 0xff00, 0x9300);

	w8168g_phy_pawam(phydev, 0x8011, 0x0000, 0x0800);

	wtw8168g_enabwe_gphy_10m(phydev);

	w8168g_phy_pawam(phydev, 0x8016, 0x0000, 0x0400);

	wtw8168g_disabwe_awdps(phydev);
	wtw8168h_config_eee_phy(phydev);
}

static void wtw8102e_hw_phy_config(stwuct wtw8169_pwivate *tp,
				   stwuct phy_device *phydev)
{
	static const stwuct phy_weg phy_weg_init[] = {
		{ 0x1f, 0x0003 },
		{ 0x08, 0x441d },
		{ 0x01, 0x9100 },
		{ 0x1f, 0x0000 }
	};

	phy_set_bits(phydev, 0x11, BIT(12));
	phy_set_bits(phydev, 0x19, BIT(13));
	phy_set_bits(phydev, 0x10, BIT(15));

	wtw_wwitephy_batch(phydev, phy_weg_init);
}

static void wtw8401_hw_phy_config(stwuct wtw8169_pwivate *tp,
				  stwuct phy_device *phydev)
{
	phy_set_bits(phydev, 0x11, BIT(12));
	phy_modify_paged(phydev, 0x0002, 0x0f, 0x0000, 0x0003);
}

static void wtw8105e_hw_phy_config(stwuct wtw8169_pwivate *tp,
				   stwuct phy_device *phydev)
{
	/* Disabwe AWDPS befowe wam code */
	phy_wwite(phydev, 0x18, 0x0310);
	msweep(100);

	w8169_appwy_fiwmwawe(tp);

	phy_wwite_paged(phydev, 0x0005, 0x1a, 0x0000);
	phy_wwite_paged(phydev, 0x0004, 0x1c, 0x0000);
	phy_wwite_paged(phydev, 0x0001, 0x15, 0x7701);
}

static void wtw8402_hw_phy_config(stwuct wtw8169_pwivate *tp,
				  stwuct phy_device *phydev)
{
	/* Disabwe AWDPS befowe setting fiwmwawe */
	phy_wwite(phydev, 0x18, 0x0310);
	msweep(20);

	w8169_appwy_fiwmwawe(tp);

	/* EEE setting */
	phy_wwite(phydev, 0x1f, 0x0004);
	phy_wwite(phydev, 0x10, 0x401f);
	phy_wwite(phydev, 0x19, 0x7030);
	phy_wwite(phydev, 0x1f, 0x0000);
}

static void wtw8106e_hw_phy_config(stwuct wtw8169_pwivate *tp,
				   stwuct phy_device *phydev)
{
	static const stwuct phy_weg phy_weg_init[] = {
		{ 0x1f, 0x0004 },
		{ 0x10, 0xc07f },
		{ 0x19, 0x7030 },
		{ 0x1f, 0x0000 }
	};

	/* Disabwe AWDPS befowe wam code */
	phy_wwite(phydev, 0x18, 0x0310);
	msweep(100);

	w8169_appwy_fiwmwawe(tp);

	wtw_wwitephy_batch(phydev, phy_weg_init);
}

static void wtw8125_wegacy_fowce_mode(stwuct phy_device *phydev)
{
	phy_modify_paged(phydev, 0xa5b, 0x12, BIT(15), 0);
}

static void wtw8125a_2_hw_phy_config(stwuct wtw8169_pwivate *tp,
				     stwuct phy_device *phydev)
{
	int i;

	phy_modify_paged(phydev, 0xad4, 0x17, 0x0000, 0x0010);
	phy_modify_paged(phydev, 0xad1, 0x13, 0x03ff, 0x03ff);
	phy_modify_paged(phydev, 0xad3, 0x11, 0x003f, 0x0006);
	phy_modify_paged(phydev, 0xac0, 0x14, 0x1100, 0x0000);
	phy_modify_paged(phydev, 0xacc, 0x10, 0x0003, 0x0002);
	phy_modify_paged(phydev, 0xad4, 0x10, 0x00e7, 0x0044);
	phy_modify_paged(phydev, 0xac1, 0x12, 0x0080, 0x0000);
	phy_modify_paged(phydev, 0xac8, 0x10, 0x0300, 0x0000);
	phy_modify_paged(phydev, 0xac5, 0x17, 0x0007, 0x0002);
	phy_wwite_paged(phydev, 0xad4, 0x16, 0x00a8);
	phy_wwite_paged(phydev, 0xac5, 0x16, 0x01ff);
	phy_modify_paged(phydev, 0xac8, 0x15, 0x00f0, 0x0030);

	phy_wwite(phydev, 0x1f, 0x0b87);
	phy_wwite(phydev, 0x16, 0x80a2);
	phy_wwite(phydev, 0x17, 0x0153);
	phy_wwite(phydev, 0x16, 0x809c);
	phy_wwite(phydev, 0x17, 0x0153);
	phy_wwite(phydev, 0x1f, 0x0000);

	phy_wwite(phydev, 0x1f, 0x0a43);
	phy_wwite(phydev, 0x13, 0x81B3);
	phy_wwite(phydev, 0x14, 0x0043);
	phy_wwite(phydev, 0x14, 0x00A7);
	phy_wwite(phydev, 0x14, 0x00D6);
	phy_wwite(phydev, 0x14, 0x00EC);
	phy_wwite(phydev, 0x14, 0x00F6);
	phy_wwite(phydev, 0x14, 0x00FB);
	phy_wwite(phydev, 0x14, 0x00FD);
	phy_wwite(phydev, 0x14, 0x00FF);
	phy_wwite(phydev, 0x14, 0x00BB);
	phy_wwite(phydev, 0x14, 0x0058);
	phy_wwite(phydev, 0x14, 0x0029);
	phy_wwite(phydev, 0x14, 0x0013);
	phy_wwite(phydev, 0x14, 0x0009);
	phy_wwite(phydev, 0x14, 0x0004);
	phy_wwite(phydev, 0x14, 0x0002);
	fow (i = 0; i < 25; i++)
		phy_wwite(phydev, 0x14, 0x0000);
	phy_wwite(phydev, 0x1f, 0x0000);

	w8168g_phy_pawam(phydev, 0x8257, 0xffff, 0x020F);
	w8168g_phy_pawam(phydev, 0x80ea, 0xffff, 0x7843);

	w8169_appwy_fiwmwawe(tp);

	phy_modify_paged(phydev, 0xd06, 0x14, 0x0000, 0x2000);

	w8168g_phy_pawam(phydev, 0x81a2, 0x0000, 0x0100);

	phy_modify_paged(phydev, 0xb54, 0x16, 0xff00, 0xdb00);
	phy_modify_paged(phydev, 0xa45, 0x12, 0x0001, 0x0000);
	phy_modify_paged(phydev, 0xa5d, 0x12, 0x0000, 0x0020);
	phy_modify_paged(phydev, 0xad4, 0x17, 0x0010, 0x0000);
	phy_modify_paged(phydev, 0xa86, 0x15, 0x0001, 0x0000);
	wtw8168g_enabwe_gphy_10m(phydev);

	wtw8125a_config_eee_phy(phydev);
}

static void wtw8125b_hw_phy_config(stwuct wtw8169_pwivate *tp,
				   stwuct phy_device *phydev)
{
	w8169_appwy_fiwmwawe(tp);

	phy_modify_paged(phydev, 0xa44, 0x11, 0x0000, 0x0800);
	phy_modify_paged(phydev, 0xac4, 0x13, 0x00f0, 0x0090);
	phy_modify_paged(phydev, 0xad3, 0x10, 0x0003, 0x0001);

	phy_wwite(phydev, 0x1f, 0x0b87);
	phy_wwite(phydev, 0x16, 0x80f5);
	phy_wwite(phydev, 0x17, 0x760e);
	phy_wwite(phydev, 0x16, 0x8107);
	phy_wwite(phydev, 0x17, 0x360e);
	phy_wwite(phydev, 0x16, 0x8551);
	phy_modify(phydev, 0x17, 0xff00, 0x0800);
	phy_wwite(phydev, 0x1f, 0x0000);

	phy_modify_paged(phydev, 0xbf0, 0x10, 0xe000, 0xa000);
	phy_modify_paged(phydev, 0xbf4, 0x13, 0x0f00, 0x0300);

	w8168g_phy_pawam(phydev, 0x8044, 0xffff, 0x2417);
	w8168g_phy_pawam(phydev, 0x804a, 0xffff, 0x2417);
	w8168g_phy_pawam(phydev, 0x8050, 0xffff, 0x2417);
	w8168g_phy_pawam(phydev, 0x8056, 0xffff, 0x2417);
	w8168g_phy_pawam(phydev, 0x805c, 0xffff, 0x2417);
	w8168g_phy_pawam(phydev, 0x8062, 0xffff, 0x2417);
	w8168g_phy_pawam(phydev, 0x8068, 0xffff, 0x2417);
	w8168g_phy_pawam(phydev, 0x806e, 0xffff, 0x2417);
	w8168g_phy_pawam(phydev, 0x8074, 0xffff, 0x2417);
	w8168g_phy_pawam(phydev, 0x807a, 0xffff, 0x2417);

	phy_modify_paged(phydev, 0xa4c, 0x15, 0x0000, 0x0040);
	phy_modify_paged(phydev, 0xbf8, 0x12, 0xe000, 0xa000);

	wtw8125_wegacy_fowce_mode(phydev);
	wtw8125b_config_eee_phy(phydev);
}

void w8169_hw_phy_config(stwuct wtw8169_pwivate *tp, stwuct phy_device *phydev,
			 enum mac_vewsion vew)
{
	static const wtw_phy_cfg_fct phy_configs[] = {
		/* PCI devices. */
		[WTW_GIGA_MAC_VEW_02] = wtw8169s_hw_phy_config,
		[WTW_GIGA_MAC_VEW_03] = wtw8169s_hw_phy_config,
		[WTW_GIGA_MAC_VEW_04] = wtw8169sb_hw_phy_config,
		[WTW_GIGA_MAC_VEW_05] = wtw8169scd_hw_phy_config,
		[WTW_GIGA_MAC_VEW_06] = wtw8169sce_hw_phy_config,
		/* PCI-E devices. */
		[WTW_GIGA_MAC_VEW_07] = wtw8102e_hw_phy_config,
		[WTW_GIGA_MAC_VEW_08] = wtw8102e_hw_phy_config,
		[WTW_GIGA_MAC_VEW_09] = wtw8102e_hw_phy_config,
		[WTW_GIGA_MAC_VEW_10] = NUWW,
		[WTW_GIGA_MAC_VEW_11] = wtw8168bb_hw_phy_config,
		[WTW_GIGA_MAC_VEW_14] = wtw8401_hw_phy_config,
		[WTW_GIGA_MAC_VEW_17] = wtw8168bef_hw_phy_config,
		[WTW_GIGA_MAC_VEW_18] = wtw8168cp_1_hw_phy_config,
		[WTW_GIGA_MAC_VEW_19] = wtw8168c_1_hw_phy_config,
		[WTW_GIGA_MAC_VEW_20] = wtw8168c_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_21] = wtw8168c_3_hw_phy_config,
		[WTW_GIGA_MAC_VEW_22] = wtw8168c_3_hw_phy_config,
		[WTW_GIGA_MAC_VEW_23] = wtw8168cp_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_24] = wtw8168cp_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_25] = wtw8168d_1_hw_phy_config,
		[WTW_GIGA_MAC_VEW_26] = wtw8168d_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_28] = wtw8168d_4_hw_phy_config,
		[WTW_GIGA_MAC_VEW_29] = wtw8105e_hw_phy_config,
		[WTW_GIGA_MAC_VEW_30] = wtw8105e_hw_phy_config,
		[WTW_GIGA_MAC_VEW_31] = NUWW,
		[WTW_GIGA_MAC_VEW_32] = wtw8168e_1_hw_phy_config,
		[WTW_GIGA_MAC_VEW_33] = wtw8168e_1_hw_phy_config,
		[WTW_GIGA_MAC_VEW_34] = wtw8168e_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_35] = wtw8168f_1_hw_phy_config,
		[WTW_GIGA_MAC_VEW_36] = wtw8168f_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_37] = wtw8402_hw_phy_config,
		[WTW_GIGA_MAC_VEW_38] = wtw8411_hw_phy_config,
		[WTW_GIGA_MAC_VEW_39] = wtw8106e_hw_phy_config,
		[WTW_GIGA_MAC_VEW_40] = wtw8168g_1_hw_phy_config,
		[WTW_GIGA_MAC_VEW_42] = wtw8168g_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_43] = wtw8168g_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_44] = wtw8168g_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_46] = wtw8168h_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_48] = wtw8168h_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_51] = wtw8168ep_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_52] = wtw8117_hw_phy_config,
		[WTW_GIGA_MAC_VEW_53] = wtw8117_hw_phy_config,
		[WTW_GIGA_MAC_VEW_61] = wtw8125a_2_hw_phy_config,
		[WTW_GIGA_MAC_VEW_63] = wtw8125b_hw_phy_config,
	};

	if (phy_configs[vew])
		phy_configs[vew](tp, phydev);
}
