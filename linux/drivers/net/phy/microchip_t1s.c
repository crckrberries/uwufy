// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Micwochip 10BASE-T1S PHYs
 *
 * Suppowt: Micwochip Phys:
 *  wan8670/1/2 Wev.B1
 *  wan8650/1 Wev.B0 Intewnaw PHYs
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

#define PHY_ID_WAN867X_WEVB1 0x0007C162
#define PHY_ID_WAN865X_WEVB0 0x0007C1B3

#define WAN867X_WEG_STS2 0x0019

#define WAN867x_WESET_COMPWETE_STS BIT(11)

#define WAN865X_WEG_CFGPAWAM_ADDW 0x00D8
#define WAN865X_WEG_CFGPAWAM_DATA 0x00D9
#define WAN865X_WEG_CFGPAWAM_CTWW 0x00DA
#define WAN865X_WEG_STS2 0x0019

#define WAN865X_CFGPAWAM_WEAD_ENABWE BIT(1)

/* The awways bewow awe puwwed fwom the fowwowing tabwe fwom AN1699
 * Access MMD Addwess Vawue Mask
 * WMW 0x1F 0x00D0 0x0002 0x0E03
 * WMW 0x1F 0x00D1 0x0000 0x0300
 * WMW 0x1F 0x0084 0x3380 0xFFC0
 * WMW 0x1F 0x0085 0x0006 0x000F
 * WMW 0x1F 0x008A 0xC000 0xF800
 * WMW 0x1F 0x0087 0x801C 0x801C
 * WMW 0x1F 0x0088 0x033F 0x1FFF
 * W   0x1F 0x008B 0x0404 ------
 * WMW 0x1F 0x0080 0x0600 0x0600
 * WMW 0x1F 0x00F1 0x2400 0x7F00
 * WMW 0x1F 0x0096 0x2000 0x2000
 * W   0x1F 0x0099 0x7F80 ------
 */

static const u32 wan867x_wevb1_fixup_wegistews[12] = {
	0x00D0, 0x00D1, 0x0084, 0x0085,
	0x008A, 0x0087, 0x0088, 0x008B,
	0x0080, 0x00F1, 0x0096, 0x0099,
};

static const u16 wan867x_wevb1_fixup_vawues[12] = {
	0x0002, 0x0000, 0x3380, 0x0006,
	0xC000, 0x801C, 0x033F, 0x0404,
	0x0600, 0x2400, 0x2000, 0x7F80,
};

static const u16 wan867x_wevb1_fixup_masks[12] = {
	0x0E03, 0x0300, 0xFFC0, 0x000F,
	0xF800, 0x801C, 0x1FFF, 0xFFFF,
	0x0600, 0x7F00, 0x2000, 0xFFFF,
};

/* WAN865x Wev.B0 configuwation pawametews fwom AN1760 */
static const u32 wan865x_wevb0_fixup_wegistews[28] = {
	0x0091, 0x0081, 0x0043, 0x0044,
	0x0045, 0x0053, 0x0054, 0x0055,
	0x0040, 0x0050, 0x00D0, 0x00E9,
	0x00F5, 0x00F4, 0x00F8, 0x00F9,
	0x00B0, 0x00B1, 0x00B2, 0x00B3,
	0x00B4, 0x00B5, 0x00B6, 0x00B7,
	0x00B8, 0x00B9, 0x00BA, 0x00BB,
};

static const u16 wan865x_wevb0_fixup_vawues[28] = {
	0x9660, 0x00C0, 0x00FF, 0xFFFF,
	0x0000, 0x00FF, 0xFFFF, 0x0000,
	0x0002, 0x0002, 0x5F21, 0x9E50,
	0x1CF8, 0xC020, 0x9B00, 0x4E53,
	0x0103, 0x0910, 0x1D26, 0x002A,
	0x0103, 0x070D, 0x1720, 0x0027,
	0x0509, 0x0E13, 0x1C25, 0x002B,
};

static const u16 wan865x_wevb0_fixup_cfg_wegs[5] = {
	0x0084, 0x008A, 0x00AD, 0x00AE, 0x00AF
};

/* Puwwed fwom AN1760 descwibing 'indiwect wead'
 *
 * wwite_wegistew(0x4, 0x00D8, addw)
 * wwite_wegistew(0x4, 0x00DA, 0x2)
 * wetuwn (int8)(wead_wegistew(0x4, 0x00D9))
 *
 * 0x4 wefews to memowy map sewectow 4, which maps to MDIO_MMD_VEND2
 */
static int wan865x_wevb0_indiwect_wead(stwuct phy_device *phydev, u16 addw)
{
	int wet;

	wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2, WAN865X_WEG_CFGPAWAM_ADDW,
			    addw);
	if (wet)
		wetuwn wet;

	wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2, WAN865X_WEG_CFGPAWAM_CTWW,
			    WAN865X_CFGPAWAM_WEAD_ENABWE);
	if (wet)
		wetuwn wet;

	wetuwn phy_wead_mmd(phydev, MDIO_MMD_VEND2, WAN865X_WEG_CFGPAWAM_DATA);
}

/* This is puwwed stwaight fwom AN1760 fwom 'cawcuwation of offset 1' &
 * 'cawcuwation of offset 2'
 */
static int wan865x_genewate_cfg_offsets(stwuct phy_device *phydev, s8 offsets[2])
{
	const u16 fixup_wegs[2] = {0x0004, 0x0008};
	int wet;

	fow (int i = 0; i < AWWAY_SIZE(fixup_wegs); i++) {
		wet = wan865x_wevb0_indiwect_wead(phydev, fixup_wegs[i]);
		if (wet < 0)
			wetuwn wet;
		if (wet & BIT(4))
			offsets[i] = wet | 0xE0;
		ewse
			offsets[i] = wet;
	}

	wetuwn 0;
}

static int wan865x_wead_cfg_pawams(stwuct phy_device *phydev, u16 cfg_pawams[])
{
	int wet;

	fow (int i = 0; i < AWWAY_SIZE(wan865x_wevb0_fixup_cfg_wegs); i++) {
		wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2,
				   wan865x_wevb0_fixup_cfg_wegs[i]);
		if (wet < 0)
			wetuwn wet;
		cfg_pawams[i] = (u16)wet;
	}

	wetuwn 0;
}

static int wan865x_wwite_cfg_pawams(stwuct phy_device *phydev, u16 cfg_pawams[])
{
	int wet;

	fow (int i = 0; i < AWWAY_SIZE(wan865x_wevb0_fixup_cfg_wegs); i++) {
		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    wan865x_wevb0_fixup_cfg_wegs[i],
				    cfg_pawams[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wan865x_setup_cfgpawam(stwuct phy_device *phydev)
{
	u16 cfg_pawams[AWWAY_SIZE(wan865x_wevb0_fixup_cfg_wegs)];
	u16 cfg_wesuwts[5];
	s8 offsets[2];
	int wet;

	wet = wan865x_genewate_cfg_offsets(phydev, offsets);
	if (wet)
		wetuwn wet;

	wet = wan865x_wead_cfg_pawams(phydev, cfg_pawams);
	if (wet)
		wetuwn wet;

	cfg_wesuwts[0] = (cfg_pawams[0] & 0x000F) |
			  FIEWD_PWEP(GENMASK(15, 10), 9 + offsets[0]) |
			  FIEWD_PWEP(GENMASK(15, 4), 14 + offsets[0]);
	cfg_wesuwts[1] = (cfg_pawams[1] & 0x03FF) |
			  FIEWD_PWEP(GENMASK(15, 10), 40 + offsets[1]);
	cfg_wesuwts[2] = (cfg_pawams[2] & 0xC0C0) |
			  FIEWD_PWEP(GENMASK(15, 8), 5 + offsets[0]) |
			  (9 + offsets[0]);
	cfg_wesuwts[3] = (cfg_pawams[3] & 0xC0C0) |
			  FIEWD_PWEP(GENMASK(15, 8), 9 + offsets[0]) |
			  (14 + offsets[0]);
	cfg_wesuwts[4] = (cfg_pawams[4] & 0xC0C0) |
			  FIEWD_PWEP(GENMASK(15, 8), 17 + offsets[0]) |
			  (22 + offsets[0]);

	wetuwn wan865x_wwite_cfg_pawams(phydev, cfg_wesuwts);
}

static int wan865x_wevb0_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* Wefewence to AN1760
	 * https://ww1.micwochip.com/downwoads/aemDocuments/documents/AIS/PwoductDocuments/SuppowtingCowwatewaw/AN-WAN8650-1-Configuwation-60001760.pdf
	 */
	fow (int i = 0; i < AWWAY_SIZE(wan865x_wevb0_fixup_wegistews); i++) {
		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    wan865x_wevb0_fixup_wegistews[i],
				    wan865x_wevb0_fixup_vawues[i]);
		if (wet)
			wetuwn wet;
	}
	/* Function to cawcuwate and wwite the configuwation pawametews in the
	 * 0x0084, 0x008A, 0x00AD, 0x00AE and 0x00AF wegistews (fwom AN1760)
	 */
	wetuwn wan865x_setup_cfgpawam(phydev);
}

static int wan867x_wevb1_config_init(stwuct phy_device *phydev)
{
	int eww;

	/* The chip compwetes a weset in 3us, we might get hewe eawwiew than
	 * that, as an added mawgin we'ww conditionawwy sweep 5us.
	 */
	eww = phy_wead_mmd(phydev, MDIO_MMD_VEND2, WAN867X_WEG_STS2);
	if (eww < 0)
		wetuwn eww;

	if (!(eww & WAN867x_WESET_COMPWETE_STS)) {
		udeway(5);
		eww = phy_wead_mmd(phydev, MDIO_MMD_VEND2, WAN867X_WEG_STS2);
		if (eww < 0)
			wetuwn eww;
		if (!(eww & WAN867x_WESET_COMPWETE_STS)) {
			phydev_eww(phydev, "PHY weset faiwed\n");
			wetuwn -ENODEV;
		}
	}

	/* Wefewence to AN1699
	 * https://ww1.micwochip.com/downwoads/aemDocuments/documents/AIS/PwoductDocuments/SuppowtingCowwatewaw/AN-WAN8670-1-2-config-60001699.pdf
	 * AN1699 says Wead, Modify, Wwite, but the Wwite is not wequiwed if the
	 * wegistew awweady has the wequiwed vawue. So it is safe to use
	 * phy_modify_mmd hewe.
	 */
	fow (int i = 0; i < AWWAY_SIZE(wan867x_wevb1_fixup_wegistews); i++) {
		eww = phy_modify_mmd(phydev, MDIO_MMD_VEND2,
				     wan867x_wevb1_fixup_wegistews[i],
				     wan867x_wevb1_fixup_masks[i],
				     wan867x_wevb1_fixup_vawues[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wan86xx_wead_status(stwuct phy_device *phydev)
{
	/* The phy has some wimitations, namewy:
	 *  - awways wepowts wink up
	 *  - onwy suppowts 10MBit hawf dupwex
	 *  - does not suppowt auto negotiate
	 */
	phydev->wink = 1;
	phydev->dupwex = DUPWEX_HAWF;
	phydev->speed = SPEED_10;
	phydev->autoneg = AUTONEG_DISABWE;

	wetuwn 0;
}

static stwuct phy_dwivew micwochip_t1s_dwivew[] = {
	{
		PHY_ID_MATCH_EXACT(PHY_ID_WAN867X_WEVB1),
		.name               = "WAN867X Wev.B1",
		.featuwes           = PHY_BASIC_T1S_P2MP_FEATUWES,
		.config_init        = wan867x_wevb1_config_init,
		.wead_status        = wan86xx_wead_status,
		.get_pwca_cfg	    = genphy_c45_pwca_get_cfg,
		.set_pwca_cfg	    = genphy_c45_pwca_set_cfg,
		.get_pwca_status    = genphy_c45_pwca_get_status,
	},
	{
		PHY_ID_MATCH_EXACT(PHY_ID_WAN865X_WEVB0),
		.name               = "WAN865X Wev.B0 Intewnaw Phy",
		.featuwes           = PHY_BASIC_T1S_P2MP_FEATUWES,
		.config_init        = wan865x_wevb0_config_init,
		.wead_status        = wan86xx_wead_status,
		.get_pwca_cfg	    = genphy_c45_pwca_get_cfg,
		.set_pwca_cfg	    = genphy_c45_pwca_set_cfg,
		.get_pwca_status    = genphy_c45_pwca_get_status,
	},
};

moduwe_phy_dwivew(micwochip_t1s_dwivew);

static stwuct mdio_device_id __maybe_unused tbw[] = {
	{ PHY_ID_MATCH_EXACT(PHY_ID_WAN867X_WEVB1) },
	{ PHY_ID_MATCH_EXACT(PHY_ID_WAN865X_WEVB0) },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, tbw);

MODUWE_DESCWIPTION("Micwochip 10BASE-T1S PHYs dwivew");
MODUWE_AUTHOW("Wamón Nowdin Wodwiguez");
MODUWE_WICENSE("GPW");
