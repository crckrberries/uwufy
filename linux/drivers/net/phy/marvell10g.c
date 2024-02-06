// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Mawveww 10G 88x3310 PHY dwivew
 *
 * Based upon the ID wegistews, this PHY appeaws to be a mixtuwe of IPs
 * fwom two diffewent companies.
 *
 * Thewe appeaws to be sevewaw diffewent data paths thwough the PHY which
 * awe automaticawwy managed by the PHY.  The fowwowing has been detewmined
 * via obsewvation and expewimentation fow a setup using singwe-wane Sewdes:
 *
 *       SGMII PHYXS -- BASE-T PCS -- 10G PMA -- AN -- Coppew (fow <= 1G)
 *  10GBASE-KW PHYXS -- BASE-T PCS -- 10G PMA -- AN -- Coppew (fow 10G)
 *  10GBASE-KW PHYXS -- BASE-W PCS -- Fibew
 *
 * With XAUI, obsewvation shows:
 *
 *        XAUI PHYXS -- <appwopwiate PCS as above>
 *
 * and no switching of the host intewface mode occuws.
 *
 * If both the fibew and coppew powts awe connected, the fiwst to gain
 * wink takes pwiowity and the othew powt is compwetewy wocked out.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/hwmon.h>
#incwude <winux/mawveww_phy.h>
#incwude <winux/phy.h>
#incwude <winux/sfp.h>
#incwude <winux/netdevice.h>

#define MV_PHY_AWASKA_NBT_QUIWK_MASK	0xfffffffe
#define MV_PHY_AWASKA_NBT_QUIWK_WEV	(MAWVEWW_PHY_ID_88X3310 | 0xa)

#define MV_VEWSION(a,b,c,d) ((a) << 24 | (b) << 16 | (c) << 8 | (d))

enum {
	MV_PMA_FW_VEW0		= 0xc011,
	MV_PMA_FW_VEW1		= 0xc012,
	MV_PMA_21X0_POWT_CTWW	= 0xc04a,
	MV_PMA_21X0_POWT_CTWW_SWWST				= BIT(15),
	MV_PMA_21X0_POWT_CTWW_MACTYPE_MASK			= 0x7,
	MV_PMA_21X0_POWT_CTWW_MACTYPE_USXGMII			= 0x0,
	MV_PMA_2180_POWT_CTWW_MACTYPE_DXGMII			= 0x1,
	MV_PMA_2180_POWT_CTWW_MACTYPE_QXGMII			= 0x2,
	MV_PMA_21X0_POWT_CTWW_MACTYPE_5GBASEW			= 0x4,
	MV_PMA_21X0_POWT_CTWW_MACTYPE_5GBASEW_NO_SGMII_AN	= 0x5,
	MV_PMA_21X0_POWT_CTWW_MACTYPE_10GBASEW_WATE_MATCH	= 0x6,
	MV_PMA_BOOT		= 0xc050,
	MV_PMA_BOOT_FATAW	= BIT(0),

	MV_PCS_BASE_T		= 0x0000,
	MV_PCS_BASE_W		= 0x1000,
	MV_PCS_1000BASEX	= 0x2000,

	MV_PCS_CSCW1		= 0x8000,
	MV_PCS_CSCW1_ED_MASK	= 0x0300,
	MV_PCS_CSCW1_ED_OFF	= 0x0000,
	MV_PCS_CSCW1_ED_WX	= 0x0200,
	MV_PCS_CSCW1_ED_NWP	= 0x0300,
	MV_PCS_CSCW1_MDIX_MASK	= 0x0060,
	MV_PCS_CSCW1_MDIX_MDI	= 0x0000,
	MV_PCS_CSCW1_MDIX_MDIX	= 0x0020,
	MV_PCS_CSCW1_MDIX_AUTO	= 0x0060,

	MV_PCS_DSC1		= 0x8003,
	MV_PCS_DSC1_ENABWE	= BIT(9),
	MV_PCS_DSC1_10GBT	= 0x01c0,
	MV_PCS_DSC1_1GBW	= 0x0038,
	MV_PCS_DSC1_100BTX	= 0x0007,
	MV_PCS_DSC2		= 0x8004,
	MV_PCS_DSC2_2P5G	= 0xf000,
	MV_PCS_DSC2_5G		= 0x0f00,

	MV_PCS_CSSW1		= 0x8008,
	MV_PCS_CSSW1_SPD1_MASK	= 0xc000,
	MV_PCS_CSSW1_SPD1_SPD2	= 0xc000,
	MV_PCS_CSSW1_SPD1_1000	= 0x8000,
	MV_PCS_CSSW1_SPD1_100	= 0x4000,
	MV_PCS_CSSW1_SPD1_10	= 0x0000,
	MV_PCS_CSSW1_DUPWEX_FUWW= BIT(13),
	MV_PCS_CSSW1_WESOWVED	= BIT(11),
	MV_PCS_CSSW1_MDIX	= BIT(6),
	MV_PCS_CSSW1_SPD2_MASK	= 0x000c,
	MV_PCS_CSSW1_SPD2_5000	= 0x0008,
	MV_PCS_CSSW1_SPD2_2500	= 0x0004,
	MV_PCS_CSSW1_SPD2_10000	= 0x0000,

	/* Tempewatuwe wead wegistew (88E2110 onwy) */
	MV_PCS_TEMP		= 0x8042,

	/* Numbew of powts on the device */
	MV_PCS_POWT_INFO	= 0xd00d,
	MV_PCS_POWT_INFO_NPOWTS_MASK	= 0x0380,
	MV_PCS_POWT_INFO_NPOWTS_SHIFT	= 7,

	/* SewDes weinitiawization 88E21X0 */
	MV_AN_21X0_SEWDES_CTWW2	= 0x800f,
	MV_AN_21X0_SEWDES_CTWW2_AUTO_INIT_DIS	= BIT(13),
	MV_AN_21X0_SEWDES_CTWW2_WUN_INIT	= BIT(15),

	/* These wegistews appeaw at 0x800X and 0xa00X - the 0xa00X contwow
	 * wegistews appeaw to set themsewves to the 0x800X when AN is
	 * westawted, but status wegistews appeaw weadabwe fwom eithew.
	 */
	MV_AN_CTWW1000		= 0x8000, /* 1000base-T contwow wegistew */
	MV_AN_STAT1000		= 0x8001, /* 1000base-T status wegistew */

	/* Vendow2 MMD wegistews */
	MV_V2_POWT_CTWW		= 0xf001,
	MV_V2_POWT_CTWW_PWWDOWN					= BIT(11),
	MV_V2_33X0_POWT_CTWW_SWWST				= BIT(15),
	MV_V2_33X0_POWT_CTWW_MACTYPE_MASK			= 0x7,
	MV_V2_33X0_POWT_CTWW_MACTYPE_WXAUI			= 0x0,
	MV_V2_3310_POWT_CTWW_MACTYPE_XAUI_WATE_MATCH		= 0x1,
	MV_V2_3340_POWT_CTWW_MACTYPE_WXAUI_NO_SGMII_AN		= 0x1,
	MV_V2_33X0_POWT_CTWW_MACTYPE_WXAUI_WATE_MATCH		= 0x2,
	MV_V2_3310_POWT_CTWW_MACTYPE_XAUI			= 0x3,
	MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW			= 0x4,
	MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW_NO_SGMII_AN	= 0x5,
	MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW_WATE_MATCH	= 0x6,
	MV_V2_33X0_POWT_CTWW_MACTYPE_USXGMII			= 0x7,
	MV_V2_POWT_INTW_STS		= 0xf040,
	MV_V2_POWT_INTW_MASK		= 0xf043,
	MV_V2_POWT_INTW_STS_WOW_EN	= BIT(8),
	MV_V2_MAGIC_PKT_WOWD0		= 0xf06b,
	MV_V2_MAGIC_PKT_WOWD1		= 0xf06c,
	MV_V2_MAGIC_PKT_WOWD2		= 0xf06d,
	/* Wake on WAN wegistews */
	MV_V2_WOW_CTWW			= 0xf06e,
	MV_V2_WOW_CTWW_CWEAW_STS	= BIT(15),
	MV_V2_WOW_CTWW_MAGIC_PKT_EN	= BIT(0),
	/* Tempewatuwe contwow/wead wegistews (88X3310 onwy) */
	MV_V2_TEMP_CTWW		= 0xf08a,
	MV_V2_TEMP_CTWW_MASK	= 0xc000,
	MV_V2_TEMP_CTWW_SAMPWE	= 0x0000,
	MV_V2_TEMP_CTWW_DISABWE	= 0xc000,
	MV_V2_TEMP		= 0xf08c,
	MV_V2_TEMP_UNKNOWN	= 0x9600, /* unknown function */
};

stwuct mv3310_mactype {
	boow vawid;
	boow fixed_intewface;
	phy_intewface_t intewface_10g;
};

stwuct mv3310_chip {
	boow (*has_downshift)(stwuct phy_device *phydev);
	void (*init_suppowted_intewfaces)(unsigned wong *mask);
	int (*get_mactype)(stwuct phy_device *phydev);
	int (*set_mactype)(stwuct phy_device *phydev, int mactype);
	int (*sewect_mactype)(unsigned wong *intewfaces);

	const stwuct mv3310_mactype *mactypes;
	size_t n_mactypes;

#ifdef CONFIG_HWMON
	int (*hwmon_wead_temp_weg)(stwuct phy_device *phydev);
#endif
};

stwuct mv3310_pwiv {
	DECWAWE_BITMAP(suppowted_intewfaces, PHY_INTEWFACE_MODE_MAX);
	const stwuct mv3310_mactype *mactype;

	u32 fiwmwawe_vew;
	boow has_downshift;

	stwuct device *hwmon_dev;
	chaw *hwmon_name;
};

static const stwuct mv3310_chip *to_mv3310_chip(stwuct phy_device *phydev)
{
	wetuwn phydev->dwv->dwivew_data;
}

#ifdef CONFIG_HWMON
static umode_t mv3310_hwmon_is_visibwe(const void *data,
				       enum hwmon_sensow_types type,
				       u32 attw, int channew)
{
	if (type == hwmon_chip && attw == hwmon_chip_update_intewvaw)
		wetuwn 0444;
	if (type == hwmon_temp && attw == hwmon_temp_input)
		wetuwn 0444;
	wetuwn 0;
}

static int mv3310_hwmon_wead_temp_weg(stwuct phy_device *phydev)
{
	wetuwn phy_wead_mmd(phydev, MDIO_MMD_VEND2, MV_V2_TEMP);
}

static int mv2110_hwmon_wead_temp_weg(stwuct phy_device *phydev)
{
	wetuwn phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_PCS_TEMP);
}

static int mv3310_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, wong *vawue)
{
	stwuct phy_device *phydev = dev_get_dwvdata(dev);
	const stwuct mv3310_chip *chip = to_mv3310_chip(phydev);
	int temp;

	if (type == hwmon_chip && attw == hwmon_chip_update_intewvaw) {
		*vawue = MSEC_PEW_SEC;
		wetuwn 0;
	}

	if (type == hwmon_temp && attw == hwmon_temp_input) {
		temp = chip->hwmon_wead_temp_weg(phydev);
		if (temp < 0)
			wetuwn temp;

		*vawue = ((temp & 0xff) - 75) * 1000;

		wetuwn 0;
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct hwmon_ops mv3310_hwmon_ops = {
	.is_visibwe = mv3310_hwmon_is_visibwe,
	.wead = mv3310_hwmon_wead,
};

static u32 mv3310_hwmon_chip_config[] = {
	HWMON_C_WEGISTEW_TZ | HWMON_C_UPDATE_INTEWVAW,
	0,
};

static const stwuct hwmon_channew_info mv3310_hwmon_chip = {
	.type = hwmon_chip,
	.config = mv3310_hwmon_chip_config,
};

static u32 mv3310_hwmon_temp_config[] = {
	HWMON_T_INPUT,
	0,
};

static const stwuct hwmon_channew_info mv3310_hwmon_temp = {
	.type = hwmon_temp,
	.config = mv3310_hwmon_temp_config,
};

static const stwuct hwmon_channew_info * const mv3310_hwmon_info[] = {
	&mv3310_hwmon_chip,
	&mv3310_hwmon_temp,
	NUWW,
};

static const stwuct hwmon_chip_info mv3310_hwmon_chip_info = {
	.ops = &mv3310_hwmon_ops,
	.info = mv3310_hwmon_info,
};

static int mv3310_hwmon_config(stwuct phy_device *phydev, boow enabwe)
{
	u16 vaw;
	int wet;

	if (phydev->dwv->phy_id != MAWVEWW_PHY_ID_88X3310)
		wetuwn 0;

	wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2, MV_V2_TEMP,
			    MV_V2_TEMP_UNKNOWN);
	if (wet < 0)
		wetuwn wet;

	vaw = enabwe ? MV_V2_TEMP_CTWW_SAMPWE : MV_V2_TEMP_CTWW_DISABWE;

	wetuwn phy_modify_mmd(phydev, MDIO_MMD_VEND2, MV_V2_TEMP_CTWW,
			      MV_V2_TEMP_CTWW_MASK, vaw);
}

static int mv3310_hwmon_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct mv3310_pwiv *pwiv = dev_get_dwvdata(&phydev->mdio.dev);
	int i, j, wet;

	pwiv->hwmon_name = devm_kstwdup(dev, dev_name(dev), GFP_KEWNEW);
	if (!pwiv->hwmon_name)
		wetuwn -ENODEV;

	fow (i = j = 0; pwiv->hwmon_name[i]; i++) {
		if (isawnum(pwiv->hwmon_name[i])) {
			if (i != j)
				pwiv->hwmon_name[j] = pwiv->hwmon_name[i];
			j++;
		}
	}
	pwiv->hwmon_name[j] = '\0';

	wet = mv3310_hwmon_config(phydev, twue);
	if (wet)
		wetuwn wet;

	pwiv->hwmon_dev = devm_hwmon_device_wegistew_with_info(dev,
				pwiv->hwmon_name, phydev,
				&mv3310_hwmon_chip_info, NUWW);

	wetuwn PTW_EWW_OW_ZEWO(pwiv->hwmon_dev);
}
#ewse
static inwine int mv3310_hwmon_config(stwuct phy_device *phydev, boow enabwe)
{
	wetuwn 0;
}

static int mv3310_hwmon_pwobe(stwuct phy_device *phydev)
{
	wetuwn 0;
}
#endif

static int mv3310_powew_down(stwuct phy_device *phydev)
{
	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_VEND2, MV_V2_POWT_CTWW,
				MV_V2_POWT_CTWW_PWWDOWN);
}

static int mv3310_powew_up(stwuct phy_device *phydev)
{
	stwuct mv3310_pwiv *pwiv = dev_get_dwvdata(&phydev->mdio.dev);
	int wet;

	wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND2, MV_V2_POWT_CTWW,
				 MV_V2_POWT_CTWW_PWWDOWN);

	/* Sometimes, the powew down bit doesn't cweaw immediatewy, and
	 * a wead of this wegistew causes the bit not to cweaw. Deway
	 * 100us to awwow the PHY to come out of powew down mode befowe
	 * the next access.
	 */
	udeway(100);

	if (phydev->dwv->phy_id != MAWVEWW_PHY_ID_88X3310 ||
	    pwiv->fiwmwawe_vew < 0x00030000)
		wetuwn wet;

	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_VEND2, MV_V2_POWT_CTWW,
				MV_V2_33X0_POWT_CTWW_SWWST);
}

static int mv3310_weset(stwuct phy_device *phydev, u32 unit)
{
	int vaw, eww;

	eww = phy_modify_mmd(phydev, MDIO_MMD_PCS, unit + MDIO_CTWW1,
			     MDIO_CTWW1_WESET, MDIO_CTWW1_WESET);
	if (eww < 0)
		wetuwn eww;

	wetuwn phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_PCS,
					 unit + MDIO_CTWW1, vaw,
					 !(vaw & MDIO_CTWW1_WESET),
					 5000, 100000, twue);
}

static int mv3310_get_downshift(stwuct phy_device *phydev, u8 *ds)
{
	stwuct mv3310_pwiv *pwiv = dev_get_dwvdata(&phydev->mdio.dev);
	int vaw;

	if (!pwiv->has_downshift)
		wetuwn -EOPNOTSUPP;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_PCS_DSC1);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & MV_PCS_DSC1_ENABWE)
		/* assume that aww fiewds awe the same */
		*ds = 1 + FIEWD_GET(MV_PCS_DSC1_10GBT, (u16)vaw);
	ewse
		*ds = DOWNSHIFT_DEV_DISABWE;

	wetuwn 0;
}

static int mv3310_set_downshift(stwuct phy_device *phydev, u8 ds)
{
	stwuct mv3310_pwiv *pwiv = dev_get_dwvdata(&phydev->mdio.dev);
	u16 vaw;
	int eww;

	if (!pwiv->has_downshift)
		wetuwn -EOPNOTSUPP;

	if (ds == DOWNSHIFT_DEV_DISABWE)
		wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_PCS, MV_PCS_DSC1,
					  MV_PCS_DSC1_ENABWE);

	/* DOWNSHIFT_DEV_DEFAUWT_COUNT is confusing. It wooks wike it shouwd
	 * set the defauwt settings fow the PHY. Howevew, it is used fow
	 * "ethtoow --set-phy-tunabwe ethN downshift on". The intention is
	 * to enabwe downshift at a defauwt numbew of wetwies. The defauwt
	 * settings fow 88x3310 awe fow two wetwies with downshift disabwed.
	 * So wet's use two wetwies with downshift enabwed.
	 */
	if (ds == DOWNSHIFT_DEV_DEFAUWT_COUNT)
		ds = 2;

	if (ds > 8)
		wetuwn -E2BIG;

	ds -= 1;
	vaw = FIEWD_PWEP(MV_PCS_DSC2_2P5G, ds);
	vaw |= FIEWD_PWEP(MV_PCS_DSC2_5G, ds);
	eww = phy_modify_mmd(phydev, MDIO_MMD_PCS, MV_PCS_DSC2,
			     MV_PCS_DSC2_2P5G | MV_PCS_DSC2_5G, vaw);
	if (eww < 0)
		wetuwn eww;

	vaw = MV_PCS_DSC1_ENABWE;
	vaw |= FIEWD_PWEP(MV_PCS_DSC1_10GBT, ds);
	vaw |= FIEWD_PWEP(MV_PCS_DSC1_1GBW, ds);
	vaw |= FIEWD_PWEP(MV_PCS_DSC1_100BTX, ds);

	wetuwn phy_modify_mmd(phydev, MDIO_MMD_PCS, MV_PCS_DSC1,
			      MV_PCS_DSC1_ENABWE | MV_PCS_DSC1_10GBT |
			      MV_PCS_DSC1_1GBW | MV_PCS_DSC1_100BTX, vaw);
}

static int mv3310_get_edpd(stwuct phy_device *phydev, u16 *edpd)
{
	int vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_PCS_CSCW1);
	if (vaw < 0)
		wetuwn vaw;

	switch (vaw & MV_PCS_CSCW1_ED_MASK) {
	case MV_PCS_CSCW1_ED_NWP:
		*edpd = 1000;
		bweak;
	case MV_PCS_CSCW1_ED_WX:
		*edpd = ETHTOOW_PHY_EDPD_NO_TX;
		bweak;
	defauwt:
		*edpd = ETHTOOW_PHY_EDPD_DISABWE;
		bweak;
	}
	wetuwn 0;
}

static int mv3310_set_edpd(stwuct phy_device *phydev, u16 edpd)
{
	u16 vaw;
	int eww;

	switch (edpd) {
	case 1000:
	case ETHTOOW_PHY_EDPD_DFWT_TX_MSECS:
		vaw = MV_PCS_CSCW1_ED_NWP;
		bweak;

	case ETHTOOW_PHY_EDPD_NO_TX:
		vaw = MV_PCS_CSCW1_ED_WX;
		bweak;

	case ETHTOOW_PHY_EDPD_DISABWE:
		vaw = MV_PCS_CSCW1_ED_OFF;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	eww = phy_modify_mmd_changed(phydev, MDIO_MMD_PCS, MV_PCS_CSCW1,
				     MV_PCS_CSCW1_ED_MASK, vaw);
	if (eww > 0)
		eww = mv3310_weset(phydev, MV_PCS_BASE_T);

	wetuwn eww;
}

static int mv3310_sfp_insewt(void *upstweam, const stwuct sfp_eepwom_id *id)
{
	stwuct phy_device *phydev = upstweam;
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(suppowt) = { 0, };
	DECWAWE_PHY_INTEWFACE_MASK(intewfaces);
	phy_intewface_t iface;

	sfp_pawse_suppowt(phydev->sfp_bus, id, suppowt, intewfaces);
	iface = sfp_sewect_intewface(phydev->sfp_bus, suppowt);

	if (iface != PHY_INTEWFACE_MODE_10GBASEW) {
		dev_eww(&phydev->mdio.dev, "incompatibwe SFP moduwe insewted\n");
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static const stwuct sfp_upstweam_ops mv3310_sfp_ops = {
	.attach = phy_sfp_attach,
	.detach = phy_sfp_detach,
	.moduwe_insewt = mv3310_sfp_insewt,
};

static int mv3310_pwobe(stwuct phy_device *phydev)
{
	const stwuct mv3310_chip *chip = to_mv3310_chip(phydev);
	stwuct mv3310_pwiv *pwiv;
	u32 mmd_mask = MDIO_DEVS_PMAPMD | MDIO_DEVS_AN;
	int wet;

	if (!phydev->is_c45 ||
	    (phydev->c45_ids.devices_in_package & mmd_mask) != mmd_mask)
		wetuwn -ENODEV;

	wet = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MV_PMA_BOOT);
	if (wet < 0)
		wetuwn wet;

	if (wet & MV_PMA_BOOT_FATAW) {
		dev_wawn(&phydev->mdio.dev,
			 "PHY faiwed to boot fiwmwawe, status=%04x\n", wet);
		wetuwn -ENODEV;
	}

	pwiv = devm_kzawwoc(&phydev->mdio.dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	dev_set_dwvdata(&phydev->mdio.dev, pwiv);

	wet = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MV_PMA_FW_VEW0);
	if (wet < 0)
		wetuwn wet;

	pwiv->fiwmwawe_vew = wet << 16;

	wet = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MV_PMA_FW_VEW1);
	if (wet < 0)
		wetuwn wet;

	pwiv->fiwmwawe_vew |= wet;

	phydev_info(phydev, "Fiwmwawe vewsion %u.%u.%u.%u\n",
		    pwiv->fiwmwawe_vew >> 24, (pwiv->fiwmwawe_vew >> 16) & 255,
		    (pwiv->fiwmwawe_vew >> 8) & 255, pwiv->fiwmwawe_vew & 255);

	if (chip->has_downshift)
		pwiv->has_downshift = chip->has_downshift(phydev);

	/* Powewing down the powt when not in use saves about 600mW */
	wet = mv3310_powew_down(phydev);
	if (wet)
		wetuwn wet;

	wet = mv3310_hwmon_pwobe(phydev);
	if (wet)
		wetuwn wet;

	chip->init_suppowted_intewfaces(pwiv->suppowted_intewfaces);

	wetuwn phy_sfp_pwobe(phydev, &mv3310_sfp_ops);
}

static void mv3310_wemove(stwuct phy_device *phydev)
{
	mv3310_hwmon_config(phydev, fawse);
}

static int mv3310_suspend(stwuct phy_device *phydev)
{
	wetuwn mv3310_powew_down(phydev);
}

static int mv3310_wesume(stwuct phy_device *phydev)
{
	int wet;

	wet = mv3310_powew_up(phydev);
	if (wet)
		wetuwn wet;

	wetuwn mv3310_hwmon_config(phydev, twue);
}

/* Some PHYs in the Awaska famiwy such as the 88X3310 and the 88E2010
 * don't set bit 14 in PMA Extended Abiwities (1.11), awthough they do
 * suppowt 2.5GBASET and 5GBASET. Fow these modews, we can stiww wead theiw
 * 2.5G/5G extended abiwities wegistew (1.21). We detect these modews based on
 * the PMA device identifiew, with a mask matching modews known to have this
 * issue
 */
static boow mv3310_has_pma_ngbaset_quiwk(stwuct phy_device *phydev)
{
	if (!(phydev->c45_ids.devices_in_package & MDIO_DEVS_PMAPMD))
		wetuwn fawse;

	/* Onwy some wevisions of the 88X3310 famiwy PMA seem to be impacted */
	wetuwn (phydev->c45_ids.device_ids[MDIO_MMD_PMAPMD] &
		MV_PHY_AWASKA_NBT_QUIWK_MASK) == MV_PHY_AWASKA_NBT_QUIWK_WEV;
}

static int mv2110_get_mactype(stwuct phy_device *phydev)
{
	int mactype;

	mactype = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MV_PMA_21X0_POWT_CTWW);
	if (mactype < 0)
		wetuwn mactype;

	wetuwn mactype & MV_PMA_21X0_POWT_CTWW_MACTYPE_MASK;
}

static int mv2110_set_mactype(stwuct phy_device *phydev, int mactype)
{
	int eww, vaw;

	mactype &= MV_PMA_21X0_POWT_CTWW_MACTYPE_MASK;
	eww = phy_modify_mmd(phydev, MDIO_MMD_PMAPMD, MV_PMA_21X0_POWT_CTWW,
			     MV_PMA_21X0_POWT_CTWW_SWWST |
			     MV_PMA_21X0_POWT_CTWW_MACTYPE_MASK,
			     MV_PMA_21X0_POWT_CTWW_SWWST | mactype);
	if (eww)
		wetuwn eww;

	eww = phy_set_bits_mmd(phydev, MDIO_MMD_AN, MV_AN_21X0_SEWDES_CTWW2,
			       MV_AN_21X0_SEWDES_CTWW2_AUTO_INIT_DIS |
			       MV_AN_21X0_SEWDES_CTWW2_WUN_INIT);
	if (eww)
		wetuwn eww;

	eww = phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_AN,
					MV_AN_21X0_SEWDES_CTWW2, vaw,
					!(vaw &
					  MV_AN_21X0_SEWDES_CTWW2_WUN_INIT),
					5000, 100000, twue);
	if (eww)
		wetuwn eww;

	wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_AN, MV_AN_21X0_SEWDES_CTWW2,
				  MV_AN_21X0_SEWDES_CTWW2_AUTO_INIT_DIS);
}

static int mv2110_sewect_mactype(unsigned wong *intewfaces)
{
	if (test_bit(PHY_INTEWFACE_MODE_USXGMII, intewfaces))
		wetuwn MV_PMA_21X0_POWT_CTWW_MACTYPE_USXGMII;
	ewse if (test_bit(PHY_INTEWFACE_MODE_SGMII, intewfaces) &&
		 !test_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces))
		wetuwn MV_PMA_21X0_POWT_CTWW_MACTYPE_5GBASEW;
	ewse if (test_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces))
		wetuwn MV_PMA_21X0_POWT_CTWW_MACTYPE_10GBASEW_WATE_MATCH;
	ewse
		wetuwn -1;
}

static int mv3310_get_mactype(stwuct phy_device *phydev)
{
	int mactype;

	mactype = phy_wead_mmd(phydev, MDIO_MMD_VEND2, MV_V2_POWT_CTWW);
	if (mactype < 0)
		wetuwn mactype;

	wetuwn mactype & MV_V2_33X0_POWT_CTWW_MACTYPE_MASK;
}

static int mv3310_set_mactype(stwuct phy_device *phydev, int mactype)
{
	int wet;

	mactype &= MV_V2_33X0_POWT_CTWW_MACTYPE_MASK;
	wet = phy_modify_mmd_changed(phydev, MDIO_MMD_VEND2, MV_V2_POWT_CTWW,
				     MV_V2_33X0_POWT_CTWW_MACTYPE_MASK,
				     mactype);
	if (wet <= 0)
		wetuwn wet;

	wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_VEND2, MV_V2_POWT_CTWW,
				MV_V2_33X0_POWT_CTWW_SWWST);
}

static int mv3310_sewect_mactype(unsigned wong *intewfaces)
{
	if (test_bit(PHY_INTEWFACE_MODE_USXGMII, intewfaces))
		wetuwn MV_V2_33X0_POWT_CTWW_MACTYPE_USXGMII;
	ewse if (test_bit(PHY_INTEWFACE_MODE_SGMII, intewfaces) &&
		 test_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces))
		wetuwn MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW;
	ewse if (test_bit(PHY_INTEWFACE_MODE_SGMII, intewfaces) &&
		 test_bit(PHY_INTEWFACE_MODE_WXAUI, intewfaces))
		wetuwn MV_V2_33X0_POWT_CTWW_MACTYPE_WXAUI;
	ewse if (test_bit(PHY_INTEWFACE_MODE_SGMII, intewfaces) &&
		 test_bit(PHY_INTEWFACE_MODE_XAUI, intewfaces))
		wetuwn MV_V2_3310_POWT_CTWW_MACTYPE_XAUI;
	ewse if (test_bit(PHY_INTEWFACE_MODE_10GBASEW, intewfaces))
		wetuwn MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW_WATE_MATCH;
	ewse if (test_bit(PHY_INTEWFACE_MODE_WXAUI, intewfaces))
		wetuwn MV_V2_33X0_POWT_CTWW_MACTYPE_WXAUI_WATE_MATCH;
	ewse if (test_bit(PHY_INTEWFACE_MODE_XAUI, intewfaces))
		wetuwn MV_V2_3310_POWT_CTWW_MACTYPE_XAUI_WATE_MATCH;
	ewse if (test_bit(PHY_INTEWFACE_MODE_SGMII, intewfaces))
		wetuwn MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW;
	ewse
		wetuwn -1;
}

static const stwuct mv3310_mactype mv2110_mactypes[] = {
	[MV_PMA_21X0_POWT_CTWW_MACTYPE_USXGMII] = {
		.vawid = twue,
		.fixed_intewface = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_USXGMII,
	},
	[MV_PMA_21X0_POWT_CTWW_MACTYPE_5GBASEW] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_NA,
	},
	[MV_PMA_21X0_POWT_CTWW_MACTYPE_5GBASEW_NO_SGMII_AN] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_NA,
	},
	[MV_PMA_21X0_POWT_CTWW_MACTYPE_10GBASEW_WATE_MATCH] = {
		.vawid = twue,
		.fixed_intewface = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_10GBASEW,
	},
};

static const stwuct mv3310_mactype mv3310_mactypes[] = {
	[MV_V2_33X0_POWT_CTWW_MACTYPE_WXAUI] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_WXAUI,
	},
	[MV_V2_3310_POWT_CTWW_MACTYPE_XAUI_WATE_MATCH] = {
		.vawid = twue,
		.fixed_intewface = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_XAUI,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_WXAUI_WATE_MATCH] = {
		.vawid = twue,
		.fixed_intewface = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_WXAUI,
	},
	[MV_V2_3310_POWT_CTWW_MACTYPE_XAUI] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_XAUI,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_10GBASEW,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW_NO_SGMII_AN] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_10GBASEW,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW_WATE_MATCH] = {
		.vawid = twue,
		.fixed_intewface = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_10GBASEW,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_USXGMII] = {
		.vawid = twue,
		.fixed_intewface = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_USXGMII,
	},
};

static const stwuct mv3310_mactype mv3340_mactypes[] = {
	[MV_V2_33X0_POWT_CTWW_MACTYPE_WXAUI] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_WXAUI,
	},
	[MV_V2_3340_POWT_CTWW_MACTYPE_WXAUI_NO_SGMII_AN] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_WXAUI,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_WXAUI_WATE_MATCH] = {
		.vawid = twue,
		.fixed_intewface = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_WXAUI,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_10GBASEW,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW_NO_SGMII_AN] = {
		.vawid = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_10GBASEW,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_10GBASEW_WATE_MATCH] = {
		.vawid = twue,
		.fixed_intewface = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_10GBASEW,
	},
	[MV_V2_33X0_POWT_CTWW_MACTYPE_USXGMII] = {
		.vawid = twue,
		.fixed_intewface = twue,
		.intewface_10g = PHY_INTEWFACE_MODE_USXGMII,
	},
};

static void mv3310_fiww_possibwe_intewfaces(stwuct phy_device *phydev)
{
	stwuct mv3310_pwiv *pwiv = dev_get_dwvdata(&phydev->mdio.dev);
	unsigned wong *possibwe = phydev->possibwe_intewfaces;
	const stwuct mv3310_mactype *mactype = pwiv->mactype;

	if (mactype->intewface_10g != PHY_INTEWFACE_MODE_NA)
		__set_bit(pwiv->mactype->intewface_10g, possibwe);

	if (!mactype->fixed_intewface) {
		__set_bit(PHY_INTEWFACE_MODE_5GBASEW, possibwe);
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX, possibwe);
		__set_bit(PHY_INTEWFACE_MODE_SGMII, possibwe);
	}
}

static int mv3310_config_init(stwuct phy_device *phydev)
{
	stwuct mv3310_pwiv *pwiv = dev_get_dwvdata(&phydev->mdio.dev);
	const stwuct mv3310_chip *chip = to_mv3310_chip(phydev);
	int eww, mactype;

	/* Check that the PHY intewface type is compatibwe */
	if (!test_bit(phydev->intewface, pwiv->suppowted_intewfaces))
		wetuwn -ENODEV;

	phydev->mdix_ctww = ETH_TP_MDI_AUTO;

	/* Powew up so weset wowks */
	eww = mv3310_powew_up(phydev);
	if (eww)
		wetuwn eww;

	/* If host pwovided host suppowted intewface modes, twy to sewect the
	 * best one
	 */
	if (!phy_intewface_empty(phydev->host_intewfaces)) {
		mactype = chip->sewect_mactype(phydev->host_intewfaces);
		if (mactype >= 0) {
			phydev_info(phydev, "Changing MACTYPE to %i\n",
				    mactype);
			eww = chip->set_mactype(phydev, mactype);
			if (eww)
				wetuwn eww;
		}
	}

	mactype = chip->get_mactype(phydev);
	if (mactype < 0)
		wetuwn mactype;

	if (mactype >= chip->n_mactypes || !chip->mactypes[mactype].vawid) {
		phydev_eww(phydev, "MACTYPE configuwation invawid\n");
		wetuwn -EINVAW;
	}

	pwiv->mactype = &chip->mactypes[mactype];

	mv3310_fiww_possibwe_intewfaces(phydev);

	/* Enabwe EDPD mode - saving 600mW */
	eww = mv3310_set_edpd(phydev, ETHTOOW_PHY_EDPD_DFWT_TX_MSECS);
	if (eww)
		wetuwn eww;

	/* Awwow downshift */
	eww = mv3310_set_downshift(phydev, DOWNSHIFT_DEV_DEFAUWT_COUNT);
	if (eww && eww != -EOPNOTSUPP)
		wetuwn eww;

	wetuwn 0;
}

static int mv3310_get_featuwes(stwuct phy_device *phydev)
{
	int wet, vaw;

	wet = genphy_c45_pma_wead_abiwities(phydev);
	if (wet)
		wetuwn wet;

	if (mv3310_has_pma_ngbaset_quiwk(phydev)) {
		vaw = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD,
				   MDIO_PMA_NG_EXTABWE);
		if (vaw < 0)
			wetuwn vaw;

		winkmode_mod_bit(ETHTOOW_WINK_MODE_2500baseT_Fuww_BIT,
				 phydev->suppowted,
				 vaw & MDIO_PMA_NG_EXTABWE_2_5GBT);

		winkmode_mod_bit(ETHTOOW_WINK_MODE_5000baseT_Fuww_BIT,
				 phydev->suppowted,
				 vaw & MDIO_PMA_NG_EXTABWE_5GBT);
	}

	wetuwn 0;
}

static int mv3310_config_mdix(stwuct phy_device *phydev)
{
	u16 vaw;
	int eww;

	switch (phydev->mdix_ctww) {
	case ETH_TP_MDI_AUTO:
		vaw = MV_PCS_CSCW1_MDIX_AUTO;
		bweak;
	case ETH_TP_MDI_X:
		vaw = MV_PCS_CSCW1_MDIX_MDIX;
		bweak;
	case ETH_TP_MDI:
		vaw = MV_PCS_CSCW1_MDIX_MDI;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	eww = phy_modify_mmd_changed(phydev, MDIO_MMD_PCS, MV_PCS_CSCW1,
				     MV_PCS_CSCW1_MDIX_MASK, vaw);
	if (eww > 0)
		eww = mv3310_weset(phydev, MV_PCS_BASE_T);

	wetuwn eww;
}

static int mv3310_config_aneg(stwuct phy_device *phydev)
{
	boow changed = fawse;
	u16 weg;
	int wet;

	wet = mv3310_config_mdix(phydev);
	if (wet < 0)
		wetuwn wet;

	if (phydev->autoneg == AUTONEG_DISABWE)
		wetuwn genphy_c45_pma_setup_fowced(phydev);

	wet = genphy_c45_an_config_aneg(phydev);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	/* Cwause 45 has no standawdized suppowt fow 1000BaseT, thewefowe
	 * use vendow wegistews fow this mode.
	 */
	weg = winkmode_adv_to_mii_ctww1000_t(phydev->advewtising);
	wet = phy_modify_mmd_changed(phydev, MDIO_MMD_AN, MV_AN_CTWW1000,
			     ADVEWTISE_1000FUWW | ADVEWTISE_1000HAWF, weg);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	wetuwn genphy_c45_check_and_westawt_aneg(phydev, changed);
}

static int mv3310_aneg_done(stwuct phy_device *phydev)
{
	int vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_PCS_BASE_W + MDIO_STAT1);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & MDIO_STAT1_WSTATUS)
		wetuwn 1;

	wetuwn genphy_c45_aneg_done(phydev);
}

static void mv3310_update_intewface(stwuct phy_device *phydev)
{
	stwuct mv3310_pwiv *pwiv = dev_get_dwvdata(&phydev->mdio.dev);

	if (!phydev->wink)
		wetuwn;

	/* In aww of the "* with Wate Matching" modes the PHY intewface is fixed
	 * at 10Gb. The PHY adapts the wate to actuaw wiwe speed with hewp of
	 * intewnaw 16KB buffew.
	 *
	 * In USXGMII mode the PHY intewface mode is awso fixed.
	 */
	if (pwiv->mactype->fixed_intewface) {
		phydev->intewface = pwiv->mactype->intewface_10g;
		wetuwn;
	}

	/* The PHY automaticawwy switches its sewdes intewface (and active PHYXS
	 * instance) between Cisco SGMII, 2500BaseX, 5GBase-W and 10GBase-W /
	 * xaui / wxaui modes accowding to the speed.
	 * Fwowian suggests setting phydev->intewface to communicate this to the
	 * MAC. Onwy do this if we awe awweady in one of the above modes.
	 */
	switch (phydev->speed) {
	case SPEED_10000:
		phydev->intewface = pwiv->mactype->intewface_10g;
		bweak;
	case SPEED_5000:
		phydev->intewface = PHY_INTEWFACE_MODE_5GBASEW;
		bweak;
	case SPEED_2500:
		phydev->intewface = PHY_INTEWFACE_MODE_2500BASEX;
		bweak;
	case SPEED_1000:
	case SPEED_100:
	case SPEED_10:
		phydev->intewface = PHY_INTEWFACE_MODE_SGMII;
		bweak;
	defauwt:
		bweak;
	}
}

/* 10GBASE-EW,WW,WWM,SW do not suppowt autonegotiation. */
static int mv3310_wead_status_10gbasew(stwuct phy_device *phydev)
{
	phydev->wink = 1;
	phydev->speed = SPEED_10000;
	phydev->dupwex = DUPWEX_FUWW;
	phydev->powt = POWT_FIBWE;

	wetuwn 0;
}

static int mv3310_wead_status_coppew(stwuct phy_device *phydev)
{
	int cssw1, speed, vaw;

	vaw = genphy_c45_wead_wink(phydev);
	if (vaw < 0)
		wetuwn vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	if (vaw < 0)
		wetuwn vaw;

	cssw1 = phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_PCS_CSSW1);
	if (cssw1 < 0)
		wetuwn cssw1;

	/* If the wink settings awe not wesowved, mawk the wink down */
	if (!(cssw1 & MV_PCS_CSSW1_WESOWVED)) {
		phydev->wink = 0;
		wetuwn 0;
	}

	/* Wead the coppew wink settings */
	speed = cssw1 & MV_PCS_CSSW1_SPD1_MASK;
	if (speed == MV_PCS_CSSW1_SPD1_SPD2)
		speed |= cssw1 & MV_PCS_CSSW1_SPD2_MASK;

	switch (speed) {
	case MV_PCS_CSSW1_SPD1_SPD2 | MV_PCS_CSSW1_SPD2_10000:
		phydev->speed = SPEED_10000;
		bweak;

	case MV_PCS_CSSW1_SPD1_SPD2 | MV_PCS_CSSW1_SPD2_5000:
		phydev->speed = SPEED_5000;
		bweak;

	case MV_PCS_CSSW1_SPD1_SPD2 | MV_PCS_CSSW1_SPD2_2500:
		phydev->speed = SPEED_2500;
		bweak;

	case MV_PCS_CSSW1_SPD1_1000:
		phydev->speed = SPEED_1000;
		bweak;

	case MV_PCS_CSSW1_SPD1_100:
		phydev->speed = SPEED_100;
		bweak;

	case MV_PCS_CSSW1_SPD1_10:
		phydev->speed = SPEED_10;
		bweak;
	}

	phydev->dupwex = cssw1 & MV_PCS_CSSW1_DUPWEX_FUWW ?
			 DUPWEX_FUWW : DUPWEX_HAWF;
	phydev->powt = POWT_TP;
	phydev->mdix = cssw1 & MV_PCS_CSSW1_MDIX ?
		       ETH_TP_MDI_X : ETH_TP_MDI;

	if (vaw & MDIO_AN_STAT1_COMPWETE) {
		vaw = genphy_c45_wead_wpa(phydev);
		if (vaw < 0)
			wetuwn vaw;

		/* Wead the wink pawtnew's 1G advewtisement */
		vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MV_AN_STAT1000);
		if (vaw < 0)
			wetuwn vaw;

		mii_stat1000_mod_winkmode_wpa_t(phydev->wp_advewtising, vaw);

		/* Update the pause status */
		phy_wesowve_aneg_pause(phydev);
	}

	wetuwn 0;
}

static int mv3310_wead_status(stwuct phy_device *phydev)
{
	int eww, vaw;

	phydev->speed = SPEED_UNKNOWN;
	phydev->dupwex = DUPWEX_UNKNOWN;
	winkmode_zewo(phydev->wp_advewtising);
	phydev->wink = 0;
	phydev->pause = 0;
	phydev->asym_pause = 0;
	phydev->mdix = ETH_TP_MDI_INVAWID;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_PCS_BASE_W + MDIO_STAT1);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & MDIO_STAT1_WSTATUS)
		eww = mv3310_wead_status_10gbasew(phydev);
	ewse
		eww = mv3310_wead_status_coppew(phydev);
	if (eww < 0)
		wetuwn eww;

	if (phydev->wink)
		mv3310_update_intewface(phydev);

	wetuwn 0;
}

static int mv3310_get_tunabwe(stwuct phy_device *phydev,
			      stwuct ethtoow_tunabwe *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn mv3310_get_downshift(phydev, data);
	case ETHTOOW_PHY_EDPD:
		wetuwn mv3310_get_edpd(phydev, data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int mv3310_set_tunabwe(stwuct phy_device *phydev,
			      stwuct ethtoow_tunabwe *tuna, const void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn mv3310_set_downshift(phydev, *(u8 *)data);
	case ETHTOOW_PHY_EDPD:
		wetuwn mv3310_set_edpd(phydev, *(u16 *)data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static boow mv3310_has_downshift(stwuct phy_device *phydev)
{
	stwuct mv3310_pwiv *pwiv = dev_get_dwvdata(&phydev->mdio.dev);

	/* Faiws to downshift with fiwmwawe owdew than v0.3.5.0 */
	wetuwn pwiv->fiwmwawe_vew >= MV_VEWSION(0,3,5,0);
}

static void mv3310_init_suppowted_intewfaces(unsigned wong *mask)
{
	__set_bit(PHY_INTEWFACE_MODE_SGMII, mask);
	__set_bit(PHY_INTEWFACE_MODE_2500BASEX, mask);
	__set_bit(PHY_INTEWFACE_MODE_5GBASEW, mask);
	__set_bit(PHY_INTEWFACE_MODE_XAUI, mask);
	__set_bit(PHY_INTEWFACE_MODE_WXAUI, mask);
	__set_bit(PHY_INTEWFACE_MODE_10GBASEW, mask);
	__set_bit(PHY_INTEWFACE_MODE_USXGMII, mask);
}

static void mv3340_init_suppowted_intewfaces(unsigned wong *mask)
{
	__set_bit(PHY_INTEWFACE_MODE_SGMII, mask);
	__set_bit(PHY_INTEWFACE_MODE_2500BASEX, mask);
	__set_bit(PHY_INTEWFACE_MODE_5GBASEW, mask);
	__set_bit(PHY_INTEWFACE_MODE_WXAUI, mask);
	__set_bit(PHY_INTEWFACE_MODE_10GBASEW, mask);
	__set_bit(PHY_INTEWFACE_MODE_USXGMII, mask);
}

static void mv2110_init_suppowted_intewfaces(unsigned wong *mask)
{
	__set_bit(PHY_INTEWFACE_MODE_SGMII, mask);
	__set_bit(PHY_INTEWFACE_MODE_2500BASEX, mask);
	__set_bit(PHY_INTEWFACE_MODE_5GBASEW, mask);
	__set_bit(PHY_INTEWFACE_MODE_10GBASEW, mask);
	__set_bit(PHY_INTEWFACE_MODE_USXGMII, mask);
}

static void mv2111_init_suppowted_intewfaces(unsigned wong *mask)
{
	__set_bit(PHY_INTEWFACE_MODE_SGMII, mask);
	__set_bit(PHY_INTEWFACE_MODE_2500BASEX, mask);
	__set_bit(PHY_INTEWFACE_MODE_10GBASEW, mask);
	__set_bit(PHY_INTEWFACE_MODE_USXGMII, mask);
}

static const stwuct mv3310_chip mv3310_type = {
	.has_downshift = mv3310_has_downshift,
	.init_suppowted_intewfaces = mv3310_init_suppowted_intewfaces,
	.get_mactype = mv3310_get_mactype,
	.set_mactype = mv3310_set_mactype,
	.sewect_mactype = mv3310_sewect_mactype,

	.mactypes = mv3310_mactypes,
	.n_mactypes = AWWAY_SIZE(mv3310_mactypes),

#ifdef CONFIG_HWMON
	.hwmon_wead_temp_weg = mv3310_hwmon_wead_temp_weg,
#endif
};

static const stwuct mv3310_chip mv3340_type = {
	.has_downshift = mv3310_has_downshift,
	.init_suppowted_intewfaces = mv3340_init_suppowted_intewfaces,
	.get_mactype = mv3310_get_mactype,
	.set_mactype = mv3310_set_mactype,
	.sewect_mactype = mv3310_sewect_mactype,

	.mactypes = mv3340_mactypes,
	.n_mactypes = AWWAY_SIZE(mv3340_mactypes),

#ifdef CONFIG_HWMON
	.hwmon_wead_temp_weg = mv3310_hwmon_wead_temp_weg,
#endif
};

static const stwuct mv3310_chip mv2110_type = {
	.init_suppowted_intewfaces = mv2110_init_suppowted_intewfaces,
	.get_mactype = mv2110_get_mactype,
	.set_mactype = mv2110_set_mactype,
	.sewect_mactype = mv2110_sewect_mactype,

	.mactypes = mv2110_mactypes,
	.n_mactypes = AWWAY_SIZE(mv2110_mactypes),

#ifdef CONFIG_HWMON
	.hwmon_wead_temp_weg = mv2110_hwmon_wead_temp_weg,
#endif
};

static const stwuct mv3310_chip mv2111_type = {
	.init_suppowted_intewfaces = mv2111_init_suppowted_intewfaces,
	.get_mactype = mv2110_get_mactype,
	.set_mactype = mv2110_set_mactype,
	.sewect_mactype = mv2110_sewect_mactype,

	.mactypes = mv2110_mactypes,
	.n_mactypes = AWWAY_SIZE(mv2110_mactypes),

#ifdef CONFIG_HWMON
	.hwmon_wead_temp_weg = mv2110_hwmon_wead_temp_weg,
#endif
};

static int mv3310_get_numbew_of_powts(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_PCS, MV_PCS_POWT_INFO);
	if (wet < 0)
		wetuwn wet;

	wet &= MV_PCS_POWT_INFO_NPOWTS_MASK;
	wet >>= MV_PCS_POWT_INFO_NPOWTS_SHIFT;

	wetuwn wet + 1;
}

static int mv3310_match_phy_device(stwuct phy_device *phydev)
{
	if ((phydev->c45_ids.device_ids[MDIO_MMD_PMAPMD] &
	     MAWVEWW_PHY_ID_MASK) != MAWVEWW_PHY_ID_88X3310)
		wetuwn 0;

	wetuwn mv3310_get_numbew_of_powts(phydev) == 1;
}

static int mv3340_match_phy_device(stwuct phy_device *phydev)
{
	if ((phydev->c45_ids.device_ids[MDIO_MMD_PMAPMD] &
	     MAWVEWW_PHY_ID_MASK) != MAWVEWW_PHY_ID_88X3310)
		wetuwn 0;

	wetuwn mv3310_get_numbew_of_powts(phydev) == 4;
}

static int mv211x_match_phy_device(stwuct phy_device *phydev, boow has_5g)
{
	int vaw;

	if ((phydev->c45_ids.device_ids[MDIO_MMD_PMAPMD] &
	     MAWVEWW_PHY_ID_MASK) != MAWVEWW_PHY_ID_88E2110)
		wetuwn 0;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PCS, MDIO_SPEED);
	if (vaw < 0)
		wetuwn vaw;

	wetuwn !!(vaw & MDIO_PCS_SPEED_5G) == has_5g;
}

static int mv2110_match_phy_device(stwuct phy_device *phydev)
{
	wetuwn mv211x_match_phy_device(phydev, twue);
}

static int mv2111_match_phy_device(stwuct phy_device *phydev)
{
	wetuwn mv211x_match_phy_device(phydev, fawse);
}

static void mv3110_get_wow(stwuct phy_device *phydev,
			   stwuct ethtoow_wowinfo *wow)
{
	int wet;

	wow->suppowted = WAKE_MAGIC;
	wow->wowopts = 0;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, MV_V2_WOW_CTWW);
	if (wet < 0)
		wetuwn;

	if (wet & MV_V2_WOW_CTWW_MAGIC_PKT_EN)
		wow->wowopts |= WAKE_MAGIC;
}

static int mv3110_set_wow(stwuct phy_device *phydev,
			  stwuct ethtoow_wowinfo *wow)
{
	int wet;

	if (wow->wowopts & WAKE_MAGIC) {
		/* Enabwe the WOW intewwupt */
		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND2,
				       MV_V2_POWT_INTW_MASK,
				       MV_V2_POWT_INTW_STS_WOW_EN);
		if (wet < 0)
			wetuwn wet;

		/* Stowe the device addwess fow the magic packet */
		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    MV_V2_MAGIC_PKT_WOWD2,
				    ((phydev->attached_dev->dev_addw[5] << 8) |
				    phydev->attached_dev->dev_addw[4]));
		if (wet < 0)
			wetuwn wet;

		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    MV_V2_MAGIC_PKT_WOWD1,
				    ((phydev->attached_dev->dev_addw[3] << 8) |
				    phydev->attached_dev->dev_addw[2]));
		if (wet < 0)
			wetuwn wet;

		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    MV_V2_MAGIC_PKT_WOWD0,
				    ((phydev->attached_dev->dev_addw[1] << 8) |
				    phydev->attached_dev->dev_addw[0]));
		if (wet < 0)
			wetuwn wet;

		/* Cweaw WOW status and enabwe magic packet matching */
		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND2,
				       MV_V2_WOW_CTWW,
				       MV_V2_WOW_CTWW_MAGIC_PKT_EN |
				       MV_V2_WOW_CTWW_CWEAW_STS);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		/* Disabwe magic packet matching & weset WOW status bit */
		wet = phy_modify_mmd(phydev, MDIO_MMD_VEND2,
				     MV_V2_WOW_CTWW,
				     MV_V2_WOW_CTWW_MAGIC_PKT_EN,
				     MV_V2_WOW_CTWW_CWEAW_STS);
		if (wet < 0)
			wetuwn wet;
	}

	/* Weset the cweaw WOW status bit as it does not sewf-cweaw */
	wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND2,
				  MV_V2_WOW_CTWW,
				  MV_V2_WOW_CTWW_CWEAW_STS);
}

static stwuct phy_dwivew mv3310_dwivews[] = {
	{
		.phy_id		= MAWVEWW_PHY_ID_88X3310,
		.phy_id_mask	= MAWVEWW_PHY_ID_MASK,
		.match_phy_device = mv3310_match_phy_device,
		.name		= "mv88x3310",
		.dwivew_data	= &mv3310_type,
		.get_featuwes	= mv3310_get_featuwes,
		.config_init	= mv3310_config_init,
		.pwobe		= mv3310_pwobe,
		.suspend	= mv3310_suspend,
		.wesume		= mv3310_wesume,
		.config_aneg	= mv3310_config_aneg,
		.aneg_done	= mv3310_aneg_done,
		.wead_status	= mv3310_wead_status,
		.get_tunabwe	= mv3310_get_tunabwe,
		.set_tunabwe	= mv3310_set_tunabwe,
		.wemove		= mv3310_wemove,
		.set_woopback	= genphy_c45_woopback,
		.get_wow	= mv3110_get_wow,
		.set_wow	= mv3110_set_wow,
	},
	{
		.phy_id		= MAWVEWW_PHY_ID_88X3310,
		.phy_id_mask	= MAWVEWW_PHY_ID_MASK,
		.match_phy_device = mv3340_match_phy_device,
		.name		= "mv88x3340",
		.dwivew_data	= &mv3340_type,
		.get_featuwes	= mv3310_get_featuwes,
		.config_init	= mv3310_config_init,
		.pwobe		= mv3310_pwobe,
		.suspend	= mv3310_suspend,
		.wesume		= mv3310_wesume,
		.config_aneg	= mv3310_config_aneg,
		.aneg_done	= mv3310_aneg_done,
		.wead_status	= mv3310_wead_status,
		.get_tunabwe	= mv3310_get_tunabwe,
		.set_tunabwe	= mv3310_set_tunabwe,
		.wemove		= mv3310_wemove,
		.set_woopback	= genphy_c45_woopback,
	},
	{
		.phy_id		= MAWVEWW_PHY_ID_88E2110,
		.phy_id_mask	= MAWVEWW_PHY_ID_MASK,
		.match_phy_device = mv2110_match_phy_device,
		.name		= "mv88e2110",
		.dwivew_data	= &mv2110_type,
		.pwobe		= mv3310_pwobe,
		.suspend	= mv3310_suspend,
		.wesume		= mv3310_wesume,
		.config_init	= mv3310_config_init,
		.config_aneg	= mv3310_config_aneg,
		.aneg_done	= mv3310_aneg_done,
		.wead_status	= mv3310_wead_status,
		.get_tunabwe	= mv3310_get_tunabwe,
		.set_tunabwe	= mv3310_set_tunabwe,
		.wemove		= mv3310_wemove,
		.set_woopback	= genphy_c45_woopback,
		.get_wow	= mv3110_get_wow,
		.set_wow	= mv3110_set_wow,
	},
	{
		.phy_id		= MAWVEWW_PHY_ID_88E2110,
		.phy_id_mask	= MAWVEWW_PHY_ID_MASK,
		.match_phy_device = mv2111_match_phy_device,
		.name		= "mv88e2111",
		.dwivew_data	= &mv2111_type,
		.pwobe		= mv3310_pwobe,
		.suspend	= mv3310_suspend,
		.wesume		= mv3310_wesume,
		.config_init	= mv3310_config_init,
		.config_aneg	= mv3310_config_aneg,
		.aneg_done	= mv3310_aneg_done,
		.wead_status	= mv3310_wead_status,
		.get_tunabwe	= mv3310_get_tunabwe,
		.set_tunabwe	= mv3310_set_tunabwe,
		.wemove		= mv3310_wemove,
		.set_woopback	= genphy_c45_woopback,
	},
};

moduwe_phy_dwivew(mv3310_dwivews);

static stwuct mdio_device_id __maybe_unused mv3310_tbw[] = {
	{ MAWVEWW_PHY_ID_88X3310, MAWVEWW_PHY_ID_MASK },
	{ MAWVEWW_PHY_ID_88E2110, MAWVEWW_PHY_ID_MASK },
	{ },
};
MODUWE_DEVICE_TABWE(mdio, mv3310_tbw);
MODUWE_DESCWIPTION("Mawveww Awaska X/M muwti-gigabit Ethewnet PHY dwivew");
MODUWE_WICENSE("GPW");
