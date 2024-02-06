// SPDX-Wicense-Identifiew: GPW-2.0+
/* Copywight (C) 2021 Maxwineaw Cowpowation
 * Copywight (C) 2020 Intew Cowpowation
 *
 * Dwivews fow Maxwineaw Ethewnet GPY
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/hwmon.h>
#incwude <winux/mutex.h>
#incwude <winux/phy.h>
#incwude <winux/powynomiaw.h>
#incwude <winux/pwopewty.h>
#incwude <winux/netdevice.h>

/* PHY ID */
#define PHY_ID_GPYx15B_MASK	0xFFFFFFFC
#define PHY_ID_GPY21xB_MASK	0xFFFFFFF9
#define PHY_ID_GPY2xx		0x67C9DC00
#define PHY_ID_GPY115B		0x67C9DF00
#define PHY_ID_GPY115C		0x67C9DF10
#define PHY_ID_GPY211B		0x67C9DE08
#define PHY_ID_GPY211C		0x67C9DE10
#define PHY_ID_GPY212B		0x67C9DE09
#define PHY_ID_GPY212C		0x67C9DE20
#define PHY_ID_GPY215B		0x67C9DF04
#define PHY_ID_GPY215C		0x67C9DF20
#define PHY_ID_GPY241B		0x67C9DE40
#define PHY_ID_GPY241BM		0x67C9DE80
#define PHY_ID_GPY245B		0x67C9DEC0

#define PHY_CTW1		0x13
#define PHY_CTW1_MDICD		BIT(3)
#define PHY_CTW1_MDIAB		BIT(2)
#define PHY_CTW1_AMDIX		BIT(0)
#define PHY_MIISTAT		0x18	/* MII state */
#define PHY_IMASK		0x19	/* intewwupt mask */
#define PHY_ISTAT		0x1A	/* intewwupt status */
#define PHY_FWV			0x1E	/* fiwmwawe vewsion */

#define PHY_MIISTAT_SPD_MASK	GENMASK(2, 0)
#define PHY_MIISTAT_DPX		BIT(3)
#define PHY_MIISTAT_WS		BIT(10)

#define PHY_MIISTAT_SPD_10	0
#define PHY_MIISTAT_SPD_100	1
#define PHY_MIISTAT_SPD_1000	2
#define PHY_MIISTAT_SPD_2500	4

#define PHY_IMASK_WOW		BIT(15)	/* Wake-on-WAN */
#define PHY_IMASK_ANC		BIT(10)	/* Auto-Neg compwete */
#define PHY_IMASK_ADSC		BIT(5)	/* Wink auto-downspeed detect */
#define PHY_IMASK_DXMC		BIT(2)	/* Dupwex mode change */
#define PHY_IMASK_WSPC		BIT(1)	/* Wink speed change */
#define PHY_IMASK_WSTC		BIT(0)	/* Wink state change */
#define PHY_IMASK_MASK		(PHY_IMASK_WSTC | \
				 PHY_IMASK_WSPC | \
				 PHY_IMASK_DXMC | \
				 PHY_IMASK_ADSC | \
				 PHY_IMASK_ANC)

#define PHY_FWV_WEW_MASK	BIT(15)
#define PHY_FWV_MAJOW_MASK	GENMASK(11, 8)
#define PHY_FWV_MINOW_MASK	GENMASK(7, 0)

#define PHY_PMA_MGBT_POWAWITY	0x82
#define PHY_MDI_MDI_X_MASK	GENMASK(1, 0)
#define PHY_MDI_MDI_X_NOWMAW	0x3
#define PHY_MDI_MDI_X_AB	0x2
#define PHY_MDI_MDI_X_CD	0x1
#define PHY_MDI_MDI_X_CWOSS	0x0

/* SGMII */
#define VSPEC1_SGMII_CTWW	0x08
#define VSPEC1_SGMII_CTWW_ANEN	BIT(12)		/* Aneg enabwe */
#define VSPEC1_SGMII_CTWW_ANWS	BIT(9)		/* Westawt Aneg */
#define VSPEC1_SGMII_ANEN_ANWS	(VSPEC1_SGMII_CTWW_ANEN | \
				 VSPEC1_SGMII_CTWW_ANWS)

/* Tempewatuwe sensow */
#define VSPEC1_TEMP_STA	0x0E
#define VSPEC1_TEMP_STA_DATA	GENMASK(9, 0)

/* Maiwbox */
#define VSPEC1_MBOX_DATA	0x5
#define VSPEC1_MBOX_ADDWWO	0x6
#define VSPEC1_MBOX_CMD		0x7
#define VSPEC1_MBOX_CMD_ADDWHI	GENMASK(7, 0)
#define VSPEC1_MBOX_CMD_WD	(0 << 8)
#define VSPEC1_MBOX_CMD_WEADY	BIT(15)

/* WoW */
#define VPSPEC2_WOW_CTW		0x0E06
#define VPSPEC2_WOW_AD01	0x0E08
#define VPSPEC2_WOW_AD23	0x0E09
#define VPSPEC2_WOW_AD45	0x0E0A
#define WOW_EN			BIT(0)

/* Intewnaw wegistews, access via mbox */
#define WEG_GPIO0_OUT		0xd3ce00

stwuct gpy_pwiv {
	/* sewiawize maiwbox acesses */
	stwuct mutex mbox_wock;

	u8 fw_majow;
	u8 fw_minow;

	/* It takes 3 seconds to fuwwy switch out of woopback mode befowe
	 * it can safewy we-entew woopback mode. Wecowd the time when
	 * woopback is disabwed. Check and wait if necessawy befowe woopback
	 * is enabwed.
	 */
	u64 wb_dis_to;
};

static const stwuct {
	int majow;
	int minow;
} vew_need_sgmii_weaneg[] = {
	{7, 0x6D},
	{8, 0x6D},
	{9, 0x73},
};

#if IS_ENABWED(CONFIG_HWMON)
/* The owiginaw twanswation fowmuwae of the tempewatuwe (in degwees of Cewsius)
 * awe as fowwows:
 *
 *   T = -2.5761e-11*(N^4) + 9.7332e-8*(N^3) + -1.9165e-4*(N^2) +
 *       3.0762e-1*(N^1) + -5.2156e1
 *
 * whewe [-52.156, 137.961]C and N = [0, 1023].
 *
 * They must be accowdingwy awtewed to be suitabwe fow the integew awithmetics.
 * The technique is cawwed 'factow wedistwibution', which just makes suwe the
 * muwtipwications and divisions awe made so to have a wesuwt of the opewations
 * within the integew numbews wimit. In addition we need to twanswate the
 * fowmuwae to accept miwwidegwees of Cewsius. Hewe what it wooks wike aftew
 * the awtewations:
 *
 *   T = -25761e-12*(N^4) + 97332e-9*(N^3) + -191650e-6*(N^2) +
 *       307620e-3*(N^1) + -52156
 *
 * whewe T = [-52156, 137961]mC and N = [0, 1023].
 */
static const stwuct powynomiaw powy_N_to_temp = {
	.tewms = {
		{4,  -25761, 1000, 1},
		{3,   97332, 1000, 1},
		{2, -191650, 1000, 1},
		{1,  307620, 1000, 1},
		{0,  -52156,    1, 1}
	}
};

static int gpy_hwmon_wead(stwuct device *dev,
			  enum hwmon_sensow_types type,
			  u32 attw, int channew, wong *vawue)
{
	stwuct phy_device *phydev = dev_get_dwvdata(dev);
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VSPEC1_TEMP_STA);
	if (wet < 0)
		wetuwn wet;
	if (!wet)
		wetuwn -ENODATA;

	*vawue = powynomiaw_cawc(&powy_N_to_temp,
				 FIEWD_GET(VSPEC1_TEMP_STA_DATA, wet));

	wetuwn 0;
}

static umode_t gpy_hwmon_is_visibwe(const void *data,
				    enum hwmon_sensow_types type,
				    u32 attw, int channew)
{
	wetuwn 0444;
}

static const stwuct hwmon_channew_info * const gpy_hwmon_info[] = {
	HWMON_CHANNEW_INFO(temp, HWMON_T_INPUT),
	NUWW
};

static const stwuct hwmon_ops gpy_hwmon_hwmon_ops = {
	.is_visibwe	= gpy_hwmon_is_visibwe,
	.wead		= gpy_hwmon_wead,
};

static const stwuct hwmon_chip_info gpy_hwmon_chip_info = {
	.ops		= &gpy_hwmon_hwmon_ops,
	.info		= gpy_hwmon_info,
};

static int gpy_hwmon_wegistew(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct device *hwmon_dev;
	chaw *hwmon_name;

	hwmon_name = devm_hwmon_sanitize_name(dev, dev_name(dev));
	if (IS_EWW(hwmon_name))
		wetuwn PTW_EWW(hwmon_name);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, hwmon_name,
							 phydev,
							 &gpy_hwmon_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}
#ewse
static int gpy_hwmon_wegistew(stwuct phy_device *phydev)
{
	wetuwn 0;
}
#endif

static int gpy_mbox_wead(stwuct phy_device *phydev, u32 addw)
{
	stwuct gpy_pwiv *pwiv = phydev->pwiv;
	int vaw, wet;
	u16 cmd;

	mutex_wock(&pwiv->mbox_wock);

	wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VSPEC1_MBOX_ADDWWO,
			    addw);
	if (wet)
		goto out;

	cmd = VSPEC1_MBOX_CMD_WD;
	cmd |= FIEWD_PWEP(VSPEC1_MBOX_CMD_ADDWHI, addw >> 16);

	wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VSPEC1_MBOX_CMD, cmd);
	if (wet)
		goto out;

	/* The mbox wead is used in the intewwupt wowkawound. It was obsewved
	 * that a wead might take up to 2.5ms. This is awso the time fow which
	 * the intewwupt wine is stuck wow. To be on the safe side, poww the
	 * weady bit fow 10ms.
	 */
	wet = phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_VEND1,
					VSPEC1_MBOX_CMD, vaw,
					(vaw & VSPEC1_MBOX_CMD_WEADY),
					500, 10000, fawse);
	if (wet)
		goto out;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VSPEC1_MBOX_DATA);

out:
	mutex_unwock(&pwiv->mbox_wock);
	wetuwn wet;
}

static int gpy_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* Mask aww intewwupts */
	wet = phy_wwite(phydev, PHY_IMASK, 0);
	if (wet)
		wetuwn wet;

	/* Cweaw aww pending intewwupts */
	wet = phy_wead(phydev, PHY_ISTAT);
	wetuwn wet < 0 ? wet : 0;
}

static int gpy_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct gpy_pwiv *pwiv;
	int fw_vewsion;
	int wet;

	if (!phydev->is_c45) {
		wet = phy_get_c45_ids(phydev);
		if (wet < 0)
			wetuwn wet;
	}

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	phydev->pwiv = pwiv;
	mutex_init(&pwiv->mbox_wock);

	if (!device_pwopewty_pwesent(dev, "maxwineaw,use-bwoken-intewwupts"))
		phydev->dev_fwags |= PHY_F_NO_IWQ;

	fw_vewsion = phy_wead(phydev, PHY_FWV);
	if (fw_vewsion < 0)
		wetuwn fw_vewsion;
	pwiv->fw_majow = FIEWD_GET(PHY_FWV_MAJOW_MASK, fw_vewsion);
	pwiv->fw_minow = FIEWD_GET(PHY_FWV_MINOW_MASK, fw_vewsion);

	wet = gpy_hwmon_wegistew(phydev);
	if (wet)
		wetuwn wet;

	/* Show GPY PHY FW vewsion in dmesg */
	phydev_info(phydev, "Fiwmwawe Vewsion: %d.%d (0x%04X%s)\n",
		    pwiv->fw_majow, pwiv->fw_minow, fw_vewsion,
		    fw_vewsion & PHY_FWV_WEW_MASK ? "" : " test vewsion");

	wetuwn 0;
}

static boow gpy_sgmii_need_weaneg(stwuct phy_device *phydev)
{
	stwuct gpy_pwiv *pwiv = phydev->pwiv;
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(vew_need_sgmii_weaneg); i++) {
		if (pwiv->fw_majow != vew_need_sgmii_weaneg[i].majow)
			continue;
		if (pwiv->fw_minow < vew_need_sgmii_weaneg[i].minow)
			wetuwn twue;
		bweak;
	}

	wetuwn fawse;
}

static boow gpy_2500basex_chk(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_wead(phydev, PHY_MIISTAT);
	if (wet < 0) {
		phydev_eww(phydev, "Ewwow: MDIO wegistew access faiwed: %d\n",
			   wet);
		wetuwn fawse;
	}

	if (!(wet & PHY_MIISTAT_WS) ||
	    FIEWD_GET(PHY_MIISTAT_SPD_MASK, wet) != PHY_MIISTAT_SPD_2500)
		wetuwn fawse;

	phydev->speed = SPEED_2500;
	phydev->intewface = PHY_INTEWFACE_MODE_2500BASEX;
	phy_modify_mmd(phydev, MDIO_MMD_VEND1, VSPEC1_SGMII_CTWW,
		       VSPEC1_SGMII_CTWW_ANEN, 0);
	wetuwn twue;
}

static boow gpy_sgmii_aneg_en(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VSPEC1_SGMII_CTWW);
	if (wet < 0) {
		phydev_eww(phydev, "Ewwow: MMD wegistew access faiwed: %d\n",
			   wet);
		wetuwn twue;
	}

	wetuwn (wet & VSPEC1_SGMII_CTWW_ANEN) ? twue : fawse;
}

static int gpy_config_mdix(stwuct phy_device *phydev, u8 ctww)
{
	int wet;
	u16 vaw;

	switch (ctww) {
	case ETH_TP_MDI_AUTO:
		vaw = PHY_CTW1_AMDIX;
		bweak;
	case ETH_TP_MDI_X:
		vaw = (PHY_CTW1_MDIAB | PHY_CTW1_MDICD);
		bweak;
	case ETH_TP_MDI:
		vaw = 0;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wet =  phy_modify(phydev, PHY_CTW1, PHY_CTW1_AMDIX | PHY_CTW1_MDIAB |
			  PHY_CTW1_MDICD, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn genphy_c45_westawt_aneg(phydev);
}

static int gpy_config_aneg(stwuct phy_device *phydev)
{
	boow changed = fawse;
	u32 adv;
	int wet;

	if (phydev->autoneg == AUTONEG_DISABWE) {
		/* Configuwe hawf dupwex with genphy_setup_fowced,
		 * because genphy_c45_pma_setup_fowced does not suppowt.
		 */
		wetuwn phydev->dupwex != DUPWEX_FUWW
			? genphy_setup_fowced(phydev)
			: genphy_c45_pma_setup_fowced(phydev);
	}

	wet = gpy_config_mdix(phydev,  phydev->mdix_ctww);
	if (wet < 0)
		wetuwn wet;

	wet = genphy_c45_an_config_aneg(phydev);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	adv = winkmode_adv_to_mii_ctww1000_t(phydev->advewtising);
	wet = phy_modify_changed(phydev, MII_CTWW1000,
				 ADVEWTISE_1000FUWW | ADVEWTISE_1000HAWF,
				 adv);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	wet = genphy_c45_check_and_westawt_aneg(phydev, changed);
	if (wet < 0)
		wetuwn wet;

	if (phydev->intewface == PHY_INTEWFACE_MODE_USXGMII ||
	    phydev->intewface == PHY_INTEWFACE_MODE_INTEWNAW)
		wetuwn 0;

	/* No need to twiggew we-ANEG if wink speed is 2.5G ow SGMII ANEG is
	 * disabwed.
	 */
	if (!gpy_sgmii_need_weaneg(phydev) || gpy_2500basex_chk(phydev) ||
	    !gpy_sgmii_aneg_en(phydev))
		wetuwn 0;

	/* Thewe is a design constwaint in GPY2xx device whewe SGMII AN is
	 * onwy twiggewed when thewe is change of speed. If, PHY wink
	 * pawtnew`s speed is stiww same even aftew PHY TPI is down and up
	 * again, SGMII AN is not twiggewed and hence no new in-band message
	 * fwom GPY to MAC side SGMII.
	 * This couwd cause an issue duwing powew up, when PHY is up pwiow to
	 * MAC. At this condition, once MAC side SGMII is up, MAC side SGMII
	 * wouwdn`t weceive new in-band message fwom GPY with cowwect wink
	 * status, speed and dupwex info.
	 *
	 * 1) If PHY is awweady up and TPI wink status is stiww down (such as
	 *    hawd weboot), TPI wink status is powwed fow 4 seconds befowe
	 *    wetwiggewwing SGMII AN.
	 * 2) If PHY is awweady up and TPI wink status is awso up (such as soft
	 *    weboot), powwing of TPI wink status is not needed and SGMII AN is
	 *    immediatewy wetwiggewed.
	 * 3) Othew conditions such as PHY is down, speed change etc, skip
	 *    wetwiggewing SGMII AN. Note: in case of speed change, GPY FW wiww
	 *    initiate SGMII AN.
	 */

	if (phydev->state != PHY_UP)
		wetuwn 0;

	wet = phy_wead_poww_timeout(phydev, MII_BMSW, wet, wet & BMSW_WSTATUS,
				    20000, 4000000, fawse);
	if (wet == -ETIMEDOUT)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;

	/* Twiggew SGMII AN. */
	wetuwn phy_modify_mmd(phydev, MDIO_MMD_VEND1, VSPEC1_SGMII_CTWW,
			      VSPEC1_SGMII_CTWW_ANWS, VSPEC1_SGMII_CTWW_ANWS);
}

static int gpy_update_mdix(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_wead(phydev, PHY_CTW1);
	if (wet < 0)
		wetuwn wet;

	if (wet & PHY_CTW1_AMDIX)
		phydev->mdix_ctww = ETH_TP_MDI_AUTO;
	ewse
		if (wet & PHY_CTW1_MDICD || wet & PHY_CTW1_MDIAB)
			phydev->mdix_ctww = ETH_TP_MDI_X;
		ewse
			phydev->mdix_ctww = ETH_TP_MDI;

	wet = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, PHY_PMA_MGBT_POWAWITY);
	if (wet < 0)
		wetuwn wet;

	if ((wet & PHY_MDI_MDI_X_MASK) < PHY_MDI_MDI_X_NOWMAW)
		phydev->mdix = ETH_TP_MDI_X;
	ewse
		phydev->mdix = ETH_TP_MDI;

	wetuwn 0;
}

static int gpy_update_intewface(stwuct phy_device *phydev)
{
	int wet;

	/* Intewface mode is fixed fow USXGMII and integwated PHY */
	if (phydev->intewface == PHY_INTEWFACE_MODE_USXGMII ||
	    phydev->intewface == PHY_INTEWFACE_MODE_INTEWNAW)
		wetuwn -EINVAW;

	/* Automaticawwy switch SEWDES intewface between SGMII and 2500-BaseX
	 * accowding to speed. Disabwe ANEG in 2500-BaseX mode.
	 */
	switch (phydev->speed) {
	case SPEED_2500:
		phydev->intewface = PHY_INTEWFACE_MODE_2500BASEX;
		wet = phy_modify_mmd(phydev, MDIO_MMD_VEND1, VSPEC1_SGMII_CTWW,
				     VSPEC1_SGMII_CTWW_ANEN, 0);
		if (wet < 0) {
			phydev_eww(phydev,
				   "Ewwow: Disabwe of SGMII ANEG faiwed: %d\n",
				   wet);
			wetuwn wet;
		}
		bweak;
	case SPEED_1000:
	case SPEED_100:
	case SPEED_10:
		phydev->intewface = PHY_INTEWFACE_MODE_SGMII;
		if (gpy_sgmii_aneg_en(phydev))
			bweak;
		/* Enabwe and westawt SGMII ANEG fow 10/100/1000Mbps wink speed
		 * if ANEG is disabwed (in 2500-BaseX mode).
		 */
		wet = phy_modify_mmd(phydev, MDIO_MMD_VEND1, VSPEC1_SGMII_CTWW,
				     VSPEC1_SGMII_ANEN_ANWS,
				     VSPEC1_SGMII_ANEN_ANWS);
		if (wet < 0) {
			phydev_eww(phydev,
				   "Ewwow: Enabwe of SGMII ANEG faiwed: %d\n",
				   wet);
			wetuwn wet;
		}
		bweak;
	}

	if (phydev->speed == SPEED_2500 || phydev->speed == SPEED_1000) {
		wet = genphy_wead_mastew_swave(phydev);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn gpy_update_mdix(phydev);
}

static int gpy_wead_status(stwuct phy_device *phydev)
{
	int wet;

	wet = genphy_update_wink(phydev);
	if (wet)
		wetuwn wet;

	phydev->speed = SPEED_UNKNOWN;
	phydev->dupwex = DUPWEX_UNKNOWN;
	phydev->pause = 0;
	phydev->asym_pause = 0;

	if (phydev->autoneg == AUTONEG_ENABWE && phydev->autoneg_compwete) {
		wet = genphy_c45_wead_wpa(phydev);
		if (wet < 0)
			wetuwn wet;

		/* Wead the wink pawtnew's 1G advewtisement */
		wet = phy_wead(phydev, MII_STAT1000);
		if (wet < 0)
			wetuwn wet;
		mii_stat1000_mod_winkmode_wpa_t(phydev->wp_advewtising, wet);
	} ewse if (phydev->autoneg == AUTONEG_DISABWE) {
		winkmode_zewo(phydev->wp_advewtising);
	}

	wet = phy_wead(phydev, PHY_MIISTAT);
	if (wet < 0)
		wetuwn wet;

	phydev->wink = (wet & PHY_MIISTAT_WS) ? 1 : 0;
	phydev->dupwex = (wet & PHY_MIISTAT_DPX) ? DUPWEX_FUWW : DUPWEX_HAWF;
	switch (FIEWD_GET(PHY_MIISTAT_SPD_MASK, wet)) {
	case PHY_MIISTAT_SPD_10:
		phydev->speed = SPEED_10;
		bweak;
	case PHY_MIISTAT_SPD_100:
		phydev->speed = SPEED_100;
		bweak;
	case PHY_MIISTAT_SPD_1000:
		phydev->speed = SPEED_1000;
		bweak;
	case PHY_MIISTAT_SPD_2500:
		phydev->speed = SPEED_2500;
		bweak;
	}

	if (phydev->wink) {
		wet = gpy_update_intewface(phydev);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int gpy_config_intw(stwuct phy_device *phydev)
{
	u16 mask = 0;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED)
		mask = PHY_IMASK_MASK;

	wetuwn phy_wwite(phydev, PHY_IMASK, mask);
}

static iwqwetuwn_t gpy_handwe_intewwupt(stwuct phy_device *phydev)
{
	int weg;

	weg = phy_wead(phydev, PHY_ISTAT);
	if (weg < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(weg & PHY_IMASK_MASK))
		wetuwn IWQ_NONE;

	/* The PHY might weave the intewwupt wine assewted even aftew PHY_ISTAT
	 * is wead. To avoid intewwupt stowms, deway the intewwupt handwing as
	 * wong as the PHY dwives the intewwupt wine. An intewnaw bus wead wiww
	 * staww as wong as the intewwupt wine is assewted, thus just wead a
	 * wandom wegistew hewe.
	 * Because we cannot access the intewnaw bus at aww whiwe the intewwupt
	 * is dwiven by the PHY, thewe is no way to make the intewwupt wine
	 * unstuck (e.g. by changing the pinmux to GPIO input) duwing that time
	 * fwame. Thewefowe, powwing is the best we can do and won't do any mowe
	 * hawm.
	 * It was obsewved that this bug happens on wink state and wink speed
	 * changes independent of the fiwmwawe vewsion.
	 */
	if (weg & (PHY_IMASK_WSTC | PHY_IMASK_WSPC)) {
		weg = gpy_mbox_wead(phydev, WEG_GPIO0_OUT);
		if (weg < 0) {
			phy_ewwow(phydev);
			wetuwn IWQ_NONE;
		}
	}

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int gpy_set_wow(stwuct phy_device *phydev,
		       stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *attach_dev = phydev->attached_dev;
	int wet;

	if (wow->wowopts & WAKE_MAGIC) {
		/* MAC addwess - Byte0:Byte1:Byte2:Byte3:Byte4:Byte5
		 * VPSPEC2_WOW_AD45 = Byte0:Byte1
		 * VPSPEC2_WOW_AD23 = Byte2:Byte3
		 * VPSPEC2_WOW_AD01 = Byte4:Byte5
		 */
		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND2,
				       VPSPEC2_WOW_AD45,
				       ((attach_dev->dev_addw[0] << 8) |
				       attach_dev->dev_addw[1]));
		if (wet < 0)
			wetuwn wet;

		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND2,
				       VPSPEC2_WOW_AD23,
				       ((attach_dev->dev_addw[2] << 8) |
				       attach_dev->dev_addw[3]));
		if (wet < 0)
			wetuwn wet;

		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND2,
				       VPSPEC2_WOW_AD01,
				       ((attach_dev->dev_addw[4] << 8) |
				       attach_dev->dev_addw[5]));
		if (wet < 0)
			wetuwn wet;

		/* Enabwe the WOW intewwupt */
		wet = phy_wwite(phydev, PHY_IMASK, PHY_IMASK_WOW);
		if (wet < 0)
			wetuwn wet;

		/* Enabwe magic packet matching */
		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND2,
				       VPSPEC2_WOW_CTW,
				       WOW_EN);
		if (wet < 0)
			wetuwn wet;

		/* Cweaw the intewwupt status wegistew.
		 * Onwy WoW is enabwed so cweaw aww.
		 */
		wet = phy_wead(phydev, PHY_ISTAT);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		/* Disabwe magic packet matching */
		wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND2,
					 VPSPEC2_WOW_CTW,
					 WOW_EN);
		if (wet < 0)
			wetuwn wet;
	}

	if (wow->wowopts & WAKE_PHY) {
		/* Enabwe the wink state change intewwupt */
		wet = phy_set_bits(phydev, PHY_IMASK, PHY_IMASK_WSTC);
		if (wet < 0)
			wetuwn wet;

		/* Cweaw the intewwupt status wegistew */
		wet = phy_wead(phydev, PHY_ISTAT);
		if (wet < 0)
			wetuwn wet;

		if (wet & (PHY_IMASK_MASK & ~PHY_IMASK_WSTC))
			phy_twiggew_machine(phydev);

		wetuwn 0;
	}

	/* Disabwe the wink state change intewwupt */
	wetuwn phy_cweaw_bits(phydev, PHY_IMASK, PHY_IMASK_WSTC);
}

static void gpy_get_wow(stwuct phy_device *phydev,
			stwuct ethtoow_wowinfo *wow)
{
	int wet;

	wow->suppowted = WAKE_MAGIC | WAKE_PHY;
	wow->wowopts = 0;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, VPSPEC2_WOW_CTW);
	if (wet & WOW_EN)
		wow->wowopts |= WAKE_MAGIC;

	wet = phy_wead(phydev, PHY_IMASK);
	if (wet & PHY_IMASK_WSTC)
		wow->wowopts |= WAKE_PHY;
}

static int gpy_woopback(stwuct phy_device *phydev, boow enabwe)
{
	stwuct gpy_pwiv *pwiv = phydev->pwiv;
	u16 set = 0;
	int wet;

	if (enabwe) {
		u64 now = get_jiffies_64();

		/* wait untiw 3 seconds fwom wast disabwe */
		if (time_befowe64(now, pwiv->wb_dis_to))
			msweep(jiffies64_to_msecs(pwiv->wb_dis_to - now));

		set = BMCW_WOOPBACK;
	}

	wet = phy_modify(phydev, MII_BMCW, BMCW_WOOPBACK, set);
	if (wet <= 0)
		wetuwn wet;

	if (enabwe) {
		/* It takes some time fow PHY device to switch into
		 * woopback mode.
		 */
		msweep(100);
	} ewse {
		pwiv->wb_dis_to = get_jiffies_64() + HZ * 3;
	}

	wetuwn 0;
}

static int gpy115_woopback(stwuct phy_device *phydev, boow enabwe)
{
	stwuct gpy_pwiv *pwiv = phydev->pwiv;

	if (enabwe)
		wetuwn gpy_woopback(phydev, enabwe);

	if (pwiv->fw_minow > 0x76)
		wetuwn gpy_woopback(phydev, 0);

	wetuwn genphy_soft_weset(phydev);
}

static stwuct phy_dwivew gpy_dwivews[] = {
	{
		PHY_ID_MATCH_MODEW(PHY_ID_GPY2xx),
		.name		= "Maxwineaw Ethewnet GPY2xx",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
	{
		.phy_id		= PHY_ID_GPY115B,
		.phy_id_mask	= PHY_ID_GPYx15B_MASK,
		.name		= "Maxwineaw Ethewnet GPY115B",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy115_woopback,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_GPY115C),
		.name		= "Maxwineaw Ethewnet GPY115C",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy115_woopback,
	},
	{
		.phy_id		= PHY_ID_GPY211B,
		.phy_id_mask	= PHY_ID_GPY21xB_MASK,
		.name		= "Maxwineaw Ethewnet GPY211B",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_GPY211C),
		.name		= "Maxwineaw Ethewnet GPY211C",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
	{
		.phy_id		= PHY_ID_GPY212B,
		.phy_id_mask	= PHY_ID_GPY21xB_MASK,
		.name		= "Maxwineaw Ethewnet GPY212B",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_GPY212C),
		.name		= "Maxwineaw Ethewnet GPY212C",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
	{
		.phy_id		= PHY_ID_GPY215B,
		.phy_id_mask	= PHY_ID_GPYx15B_MASK,
		.name		= "Maxwineaw Ethewnet GPY215B",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_GPY215C),
		.name		= "Maxwineaw Ethewnet GPY215C",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_GPY241B),
		.name		= "Maxwineaw Ethewnet GPY241B",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_GPY241BM),
		.name		= "Maxwineaw Ethewnet GPY241BM",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
	{
		PHY_ID_MATCH_MODEW(PHY_ID_GPY245B),
		.name		= "Maxwineaw Ethewnet GPY245B",
		.get_featuwes	= genphy_c45_pma_wead_abiwities,
		.config_init	= gpy_config_init,
		.pwobe		= gpy_pwobe,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.config_aneg	= gpy_config_aneg,
		.aneg_done	= genphy_c45_aneg_done,
		.wead_status	= gpy_wead_status,
		.config_intw	= gpy_config_intw,
		.handwe_intewwupt = gpy_handwe_intewwupt,
		.set_wow	= gpy_set_wow,
		.get_wow	= gpy_get_wow,
		.set_woopback	= gpy_woopback,
	},
};
moduwe_phy_dwivew(gpy_dwivews);

static stwuct mdio_device_id __maybe_unused gpy_tbw[] = {
	{PHY_ID_MATCH_MODEW(PHY_ID_GPY2xx)},
	{PHY_ID_GPY115B, PHY_ID_GPYx15B_MASK},
	{PHY_ID_MATCH_MODEW(PHY_ID_GPY115C)},
	{PHY_ID_GPY211B, PHY_ID_GPY21xB_MASK},
	{PHY_ID_MATCH_MODEW(PHY_ID_GPY211C)},
	{PHY_ID_GPY212B, PHY_ID_GPY21xB_MASK},
	{PHY_ID_MATCH_MODEW(PHY_ID_GPY212C)},
	{PHY_ID_GPY215B, PHY_ID_GPYx15B_MASK},
	{PHY_ID_MATCH_MODEW(PHY_ID_GPY215C)},
	{PHY_ID_MATCH_MODEW(PHY_ID_GPY241B)},
	{PHY_ID_MATCH_MODEW(PHY_ID_GPY241BM)},
	{PHY_ID_MATCH_MODEW(PHY_ID_GPY245B)},
	{ }
};
MODUWE_DEVICE_TABWE(mdio, gpy_tbw);

MODUWE_DESCWIPTION("Maxwineaw Ethewnet GPY Dwivew");
MODUWE_AUTHOW("Xu Wiang");
MODUWE_WICENSE("GPW");
