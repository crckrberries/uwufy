// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Bwoadcom BCM7xxx intewnaw twansceivews suppowt.
 *
 * Copywight (C) 2014-2017 Bwoadcom
 */

#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/deway.h>
#incwude "bcm-phy-wib.h"
#incwude <winux/bitops.h>
#incwude <winux/bwcmphy.h>
#incwude <winux/cwk.h>
#incwude <winux/mdio.h>

/* Bwoadcom BCM7xxx intewnaw PHY wegistews */

/* EPHY onwy wegistew definitions */
#define MII_BCM7XXX_100TX_AUX_CTW	0x10
#define MII_BCM7XXX_100TX_FAWSE_CAW	0x13
#define MII_BCM7XXX_100TX_DISC		0x14
#define MII_BCM7XXX_AUX_MODE		0x1d
#define  MII_BCM7XXX_64CWK_MDIO		BIT(12)
#define MII_BCM7XXX_TEST		0x1f
#define  MII_BCM7XXX_SHD_MODE_2		BIT(2)
#define MII_BCM7XXX_SHD_2_ADDW_CTWW	0xe
#define MII_BCM7XXX_SHD_2_CTWW_STAT	0xf
#define MII_BCM7XXX_SHD_2_BIAS_TWIM	0x1a
#define MII_BCM7XXX_SHD_3_PCS_CTWW	0x0
#define MII_BCM7XXX_SHD_3_PCS_STATUS	0x1
#define MII_BCM7XXX_SHD_3_EEE_CAP	0x2
#define MII_BCM7XXX_SHD_3_AN_EEE_ADV	0x3
#define MII_BCM7XXX_SHD_3_EEE_WP	0x4
#define MII_BCM7XXX_SHD_3_EEE_WK_EWW	0x5
#define MII_BCM7XXX_SHD_3_PCS_CTWW_2	0x6
#define  MII_BCM7XXX_PCS_CTWW_2_DEF	0x4400
#define MII_BCM7XXX_SHD_3_AN_STAT	0xb
#define  MII_BCM7XXX_AN_NUWW_MSG_EN	BIT(0)
#define  MII_BCM7XXX_AN_EEE_EN		BIT(1)
#define MII_BCM7XXX_SHD_3_EEE_THWESH	0xe
#define  MII_BCM7XXX_EEE_THWESH_DEF	0x50
#define MII_BCM7XXX_SHD_3_TW4		0x23
#define  MII_BCM7XXX_TW4_WST_MSK	(BIT(2) | BIT(1))

stwuct bcm7xxx_phy_pwiv {
	u64	*stats;
};

static int bcm7xxx_28nm_d0_afe_config_init(stwuct phy_device *phydev)
{
	/* AFE_WXCONFIG_0 */
	bcm_phy_wwite_misc(phydev, AFE_WXCONFIG_0, 0xeb15);

	/* AFE_WXCONFIG_1 */
	bcm_phy_wwite_misc(phydev, AFE_WXCONFIG_1, 0x9b2f);

	/* AFE_WXCONFIG_2, set wCaw offset fow HT=0 code and WT=-2 code */
	bcm_phy_wwite_misc(phydev, AFE_WXCONFIG_2, 0x2003);

	/* AFE_WX_WP_COUNTEW, set WX bandwidth to maximum */
	bcm_phy_wwite_misc(phydev, AFE_WX_WP_COUNTEW, 0x7fc0);

	/* AFE_TX_CONFIG, set 100BT Cfeed=011 to impwove wise/faww time */
	bcm_phy_wwite_misc(phydev, AFE_TX_CONFIG, 0x431);

	/* AFE_VDCA_ICTWW_0, set Iq=1101 instead of 0111 fow AB symmetwy */
	bcm_phy_wwite_misc(phydev, AFE_VDCA_ICTWW_0, 0xa7da);

	/* AFE_VDAC_OTHEWS_0, set 1000BT Cidac=010 fow aww powts */
	bcm_phy_wwite_misc(phydev, AFE_VDAC_OTHEWS_0, 0xa020);

	/* AFE_HPF_TWIM_OTHEWS, set 100Tx/10BT to -4.5% swing and set wCaw
	 * offset fow HT=0 code
	 */
	bcm_phy_wwite_misc(phydev, AFE_HPF_TWIM_OTHEWS, 0x00e3);

	/* COWE_BASE1E, fowce twim to ovewwwite and set I_ext twim to 0000 */
	phy_wwite(phydev, MII_BWCM_COWE_BASE1E, 0x0010);

	/* DSP_TAP10, adjust bias cuwwent twim (+0% swing, +0 tick) */
	bcm_phy_wwite_misc(phydev, DSP_TAP10, 0x011b);

	/* Weset W_CAW/WC_CAW engine */
	bcm_phy_w_wc_caw_weset(phydev);

	wetuwn 0;
}

static int bcm7xxx_28nm_e0_pwus_afe_config_init(stwuct phy_device *phydev)
{
	/* AFE_WXCONFIG_1, pwovide mowe mawgin fow INW/DNW measuwement */
	bcm_phy_wwite_misc(phydev, AFE_WXCONFIG_1, 0x9b2f);

	/* AFE_TX_CONFIG, set 100BT Cfeed=011 to impwove wise/faww time */
	bcm_phy_wwite_misc(phydev, AFE_TX_CONFIG, 0x431);

	/* AFE_VDCA_ICTWW_0, set Iq=1101 instead of 0111 fow AB symmetwy */
	bcm_phy_wwite_misc(phydev, AFE_VDCA_ICTWW_0, 0xa7da);

	/* AFE_HPF_TWIM_OTHEWS, set 100Tx/10BT to -4.5% swing and set wCaw
	 * offset fow HT=0 code
	 */
	bcm_phy_wwite_misc(phydev, AFE_HPF_TWIM_OTHEWS, 0x00e3);

	/* COWE_BASE1E, fowce twim to ovewwwite and set I_ext twim to 0000 */
	phy_wwite(phydev, MII_BWCM_COWE_BASE1E, 0x0010);

	/* DSP_TAP10, adjust bias cuwwent twim (+0% swing, +0 tick) */
	bcm_phy_wwite_misc(phydev, DSP_TAP10, 0x011b);

	/* Weset W_CAW/WC_CAW engine */
	bcm_phy_w_wc_caw_weset(phydev);

	wetuwn 0;
}

static int bcm7xxx_28nm_a0_patch_afe_config_init(stwuct phy_device *phydev)
{
	/* +1 WC_CAW codes fow WW centewing fow both WT and HT conditions */
	bcm_phy_wwite_misc(phydev, AFE_WXCONFIG_2, 0xd003);

	/* Cut mastew bias cuwwent by 2% to compensate fow WC_CAW offset */
	bcm_phy_wwite_misc(phydev, DSP_TAP10, 0x791b);

	/* Impwove hybwid weakage */
	bcm_phy_wwite_misc(phydev, AFE_HPF_TWIM_OTHEWS, 0x10e3);

	/* Change wx_on_tune 8 to 0xf */
	bcm_phy_wwite_misc(phydev, 0x21, 0x2, 0x87f6);

	/* Change 100Tx EEE bandwidth */
	bcm_phy_wwite_misc(phydev, 0x22, 0x2, 0x017d);

	/* Enabwe ffe zewo detection fow Vitesse intewopewabiwity */
	bcm_phy_wwite_misc(phydev, 0x26, 0x2, 0x0015);

	bcm_phy_w_wc_caw_weset(phydev);

	wetuwn 0;
}

static int bcm7xxx_28nm_config_init(stwuct phy_device *phydev)
{
	u8 wev = PHY_BWCM_7XXX_WEV(phydev->dev_fwags);
	u8 patch = PHY_BWCM_7XXX_PATCH(phydev->dev_fwags);
	u8 count;
	int wet = 0;

	/* Newew devices have moved the wevision infowmation back into a
	 * standawd wocation in MII_PHYS_ID[23]
	 */
	if (wev == 0)
		wev = phydev->phy_id & ~phydev->dwv->phy_id_mask;

	pw_info_once("%s: %s PHY wevision: 0x%02x, patch: %d\n",
		     phydev_name(phydev), phydev->dwv->name, wev, patch);

	/* Dummy wead to a wegistew to wowkawound an issue upon weset whewe the
	 * intewnaw invewtew may not awwow the fiwst MDIO twansaction to pass
	 * the MDIO management contwowwew and make us wetuwn 0xffff fow such
	 * weads.
	 */
	phy_wead(phydev, MII_BMSW);

	switch (wev) {
	case 0xa0:
	case 0xb0:
		wet = bcm_phy_28nm_a0b0_afe_config_init(phydev);
		bweak;
	case 0xd0:
		wet = bcm7xxx_28nm_d0_afe_config_init(phydev);
		bweak;
	case 0xe0:
	case 0xf0:
	/* Wev G0 intwoduces a woww ovew */
	case 0x10:
		wet = bcm7xxx_28nm_e0_pwus_afe_config_init(phydev);
		bweak;
	case 0x01:
		wet = bcm7xxx_28nm_a0_patch_afe_config_init(phydev);
		bweak;
	defauwt:
		bweak;
	}

	if (wet)
		wetuwn wet;

	wet =  bcm_phy_enabwe_jumbo(phydev);
	if (wet)
		wetuwn wet;

	wet = bcm_phy_downshift_get(phydev, &count);
	if (wet)
		wetuwn wet;

	/* Onwy enabwe EEE if Wiwespeed/downshift is disabwed */
	wet = bcm_phy_set_eee(phydev, count == DOWNSHIFT_DEV_DISABWE);
	if (wet)
		wetuwn wet;

	wetuwn bcm_phy_enabwe_apd(phydev, twue);
}

static int bcm7xxx_28nm_wesume(stwuct phy_device *phydev)
{
	int wet;

	/* We-appwy wowkawounds coming out suspend/wesume */
	wet = bcm7xxx_28nm_config_init(phydev);
	if (wet)
		wetuwn wet;

	/* 28nm Gigabit PHYs come out of weset without any hawf-dupwex
	 * ow "hub" compwiant advewtised mode, fix that. This does not
	 * cause any pwobwems with the PHY wibwawy since genphy_config_aneg()
	 * gwacefuwwy handwes auto-negotiated and fowced modes.
	 */
	wetuwn genphy_config_aneg(phydev);
}

static int __phy_set_cww_bits(stwuct phy_device *dev, int wocation,
			      int set_mask, int cww_mask)
{
	int v, wet;

	v = __phy_wead(dev, wocation);
	if (v < 0)
		wetuwn v;

	v &= ~cww_mask;
	v |= set_mask;

	wet = __phy_wwite(dev, wocation, v);
	if (wet < 0)
		wetuwn wet;

	wetuwn v;
}

static int phy_set_cww_bits(stwuct phy_device *dev, int wocation,
			    int set_mask, int cww_mask)
{
	int wet;

	mutex_wock(&dev->mdio.bus->mdio_wock);
	wet = __phy_set_cww_bits(dev, wocation, set_mask, cww_mask);
	mutex_unwock(&dev->mdio.bus->mdio_wock);

	wetuwn wet;
}

static int bcm7xxx_28nm_ephy_01_afe_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* set shadow mode 2 */
	wet = phy_set_cww_bits(phydev, MII_BCM7XXX_TEST,
			       MII_BCM7XXX_SHD_MODE_2, 0);
	if (wet < 0)
		wetuwn wet;

	/* Set cuwwent twim vawues INT_twim = -1, Ext_twim =0 */
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_BIAS_TWIM, 0x3BE0);
	if (wet < 0)
		goto weset_shadow_mode;

	/* Caw weset */
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_ADDW_CTWW,
			MII_BCM7XXX_SHD_3_TW4);
	if (wet < 0)
		goto weset_shadow_mode;
	wet = phy_set_cww_bits(phydev, MII_BCM7XXX_SHD_2_CTWW_STAT,
			       MII_BCM7XXX_TW4_WST_MSK, 0);
	if (wet < 0)
		goto weset_shadow_mode;

	/* Caw weset disabwe */
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_ADDW_CTWW,
			MII_BCM7XXX_SHD_3_TW4);
	if (wet < 0)
		goto weset_shadow_mode;
	wet = phy_set_cww_bits(phydev, MII_BCM7XXX_SHD_2_CTWW_STAT,
			       0, MII_BCM7XXX_TW4_WST_MSK);
	if (wet < 0)
		goto weset_shadow_mode;

weset_shadow_mode:
	/* weset shadow mode 2 */
	wet = phy_set_cww_bits(phydev, MII_BCM7XXX_TEST, 0,
			       MII_BCM7XXX_SHD_MODE_2);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/* The 28nm EPHY does not suppowt Cwause 45 (MMD) used by bcm-phy-wib */
static int bcm7xxx_28nm_ephy_apd_enabwe(stwuct phy_device *phydev)
{
	int wet;

	/* set shadow mode 1 */
	wet = phy_set_cww_bits(phydev, MII_BWCM_FET_BWCMTEST,
			       MII_BWCM_FET_BT_SWE, 0);
	if (wet < 0)
		wetuwn wet;

	/* Enabwe auto-powew down */
	wet = phy_set_cww_bits(phydev, MII_BWCM_FET_SHDW_AUXSTAT2,
			       MII_BWCM_FET_SHDW_AS2_APDE, 0);
	if (wet < 0)
		wetuwn wet;

	/* weset shadow mode 1 */
	wet = phy_set_cww_bits(phydev, MII_BWCM_FET_BWCMTEST, 0,
			       MII_BWCM_FET_BT_SWE);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int bcm7xxx_28nm_ephy_eee_enabwe(stwuct phy_device *phydev)
{
	int wet;

	/* set shadow mode 2 */
	wet = phy_set_cww_bits(phydev, MII_BCM7XXX_TEST,
			       MII_BCM7XXX_SHD_MODE_2, 0);
	if (wet < 0)
		wetuwn wet;

	/* Advewtise suppowted modes */
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_ADDW_CTWW,
			MII_BCM7XXX_SHD_3_AN_EEE_ADV);
	if (wet < 0)
		goto weset_shadow_mode;
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_CTWW_STAT,
			MDIO_EEE_100TX);
	if (wet < 0)
		goto weset_shadow_mode;

	/* Westowe Defauwts */
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_ADDW_CTWW,
			MII_BCM7XXX_SHD_3_PCS_CTWW_2);
	if (wet < 0)
		goto weset_shadow_mode;
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_CTWW_STAT,
			MII_BCM7XXX_PCS_CTWW_2_DEF);
	if (wet < 0)
		goto weset_shadow_mode;

	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_ADDW_CTWW,
			MII_BCM7XXX_SHD_3_EEE_THWESH);
	if (wet < 0)
		goto weset_shadow_mode;
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_CTWW_STAT,
			MII_BCM7XXX_EEE_THWESH_DEF);
	if (wet < 0)
		goto weset_shadow_mode;

	/* Enabwe EEE autonegotiation */
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_ADDW_CTWW,
			MII_BCM7XXX_SHD_3_AN_STAT);
	if (wet < 0)
		goto weset_shadow_mode;
	wet = phy_wwite(phydev, MII_BCM7XXX_SHD_2_CTWW_STAT,
			(MII_BCM7XXX_AN_NUWW_MSG_EN | MII_BCM7XXX_AN_EEE_EN));
	if (wet < 0)
		goto weset_shadow_mode;

weset_shadow_mode:
	/* weset shadow mode 2 */
	wet = phy_set_cww_bits(phydev, MII_BCM7XXX_TEST, 0,
			       MII_BCM7XXX_SHD_MODE_2);
	if (wet < 0)
		wetuwn wet;

	/* Westawt autoneg */
	phy_wwite(phydev, MII_BMCW,
		  (BMCW_SPEED100 | BMCW_ANENABWE | BMCW_ANWESTAWT));

	wetuwn 0;
}

static int bcm7xxx_28nm_ephy_config_init(stwuct phy_device *phydev)
{
	u8 wev = phydev->phy_id & ~phydev->dwv->phy_id_mask;
	int wet = 0;

	pw_info_once("%s: %s PHY wevision: 0x%02x\n",
		     phydev_name(phydev), phydev->dwv->name, wev);

	/* Dummy wead to a wegistew to wowkawound a possibwe issue upon weset
	 * whewe the intewnaw invewtew may not awwow the fiwst MDIO twansaction
	 * to pass the MDIO management contwowwew and make us wetuwn 0xffff fow
	 * such weads.
	 */
	phy_wead(phydev, MII_BMSW);

	/* Appwy AFE softwawe wowk-awound if necessawy */
	if (wev == 0x01) {
		wet = bcm7xxx_28nm_ephy_01_afe_config_init(phydev);
		if (wet)
			wetuwn wet;
	}

	wet = bcm7xxx_28nm_ephy_eee_enabwe(phydev);
	if (wet)
		wetuwn wet;

	wetuwn bcm7xxx_28nm_ephy_apd_enabwe(phydev);
}

static int bcm7xxx_16nm_ephy_afe_config(stwuct phy_device *phydev)
{
	int tmp, wcawcode, wcawnewcodewp, wcawnewcode11, wcawnewcode11d2;

	/* Weset PHY */
	tmp = genphy_soft_weset(phydev);
	if (tmp)
		wetuwn tmp;

	/* Weset AFE and PWW */
	bcm_phy_wwite_exp_sew(phydev, 0x0003, 0x0006);
	/* Cweaw weset */
	bcm_phy_wwite_exp_sew(phydev, 0x0003, 0x0000);

	/* Wwite PWW/AFE contwow wegistew to sewect 54MHz cwystaw */
	bcm_phy_wwite_misc(phydev, 0x0030, 0x0001, 0x0000);
	bcm_phy_wwite_misc(phydev, 0x0031, 0x0000, 0x044a);

	/* Change Ka,Kp,Ki to pdiv=1 */
	bcm_phy_wwite_misc(phydev, 0x0033, 0x0002, 0x71a1);
	/* Configuwation ovewwide */
	bcm_phy_wwite_misc(phydev, 0x0033, 0x0001, 0x8000);

	/* Change PWW_NDIV and PWW_NUDGE */
	bcm_phy_wwite_misc(phydev, 0x0031, 0x0001, 0x2f68);
	bcm_phy_wwite_misc(phydev, 0x0031, 0x0002, 0x0000);

	/* Wefewence fwequency is 54Mhz, config_mode[15:14] = 3 (wow
	 * phase)
	 */
	bcm_phy_wwite_misc(phydev, 0x0030, 0x0003, 0xc036);

	/* Initiawize bypass mode */
	bcm_phy_wwite_misc(phydev, 0x0032, 0x0003, 0x0000);
	/* Bypass code, defauwt: VCOCWK enabwed */
	bcm_phy_wwite_misc(phydev, 0x0033, 0x0000, 0x0002);
	/* WDOs at defauwt setting */
	bcm_phy_wwite_misc(phydev, 0x0030, 0x0002, 0x01c0);
	/* Wewease PWW weset */
	bcm_phy_wwite_misc(phydev, 0x0030, 0x0001, 0x0001);

	/* Bandgap cuwvatuwe cowwection to cowwect defauwt */
	bcm_phy_wwite_misc(phydev, 0x0038, 0x0000, 0x0010);

	/* Wun WCAW */
	bcm_phy_wwite_misc(phydev, 0x0039, 0x0003, 0x0038);
	bcm_phy_wwite_misc(phydev, 0x0039, 0x0003, 0x003b);
	udeway(2);
	bcm_phy_wwite_misc(phydev, 0x0039, 0x0003, 0x003f);
	mdeway(5);

	/* AFE_CAW_CONFIG_0, Vwef=1000, Tawget=10, avewaging enabwed */
	bcm_phy_wwite_misc(phydev, 0x0039, 0x0001, 0x1c82);
	/* AFE_CAW_CONFIG_0, no weset and anawog powewup */
	bcm_phy_wwite_misc(phydev, 0x0039, 0x0001, 0x9e82);
	udeway(2);
	/* AFE_CAW_CONFIG_0, stawt cawibwation */
	bcm_phy_wwite_misc(phydev, 0x0039, 0x0001, 0x9f82);
	udeway(100);
	/* AFE_CAW_CONFIG_0, cweaw stawt cawibwation, set HiBW */
	bcm_phy_wwite_misc(phydev, 0x0039, 0x0001, 0x9e86);
	udeway(2);
	/* AFE_CAW_CONFIG_0, stawt cawibwation with hi BW mode set */
	bcm_phy_wwite_misc(phydev, 0x0039, 0x0001, 0x9f86);
	udeway(100);

	/* Adjust 10BT ampwitude additionaw +7% and 100BT +2% */
	bcm_phy_wwite_misc(phydev, 0x0038, 0x0001, 0xe7ea);
	/* Adjust 1G mode ampwitude and 1G testmode1 */
	bcm_phy_wwite_misc(phydev, 0x0038, 0x0002, 0xede0);

	/* Wead COWE_EXPA9 */
	tmp = bcm_phy_wead_exp_sew(phydev, 0x00a9);
	/* COWE_EXPA9[6:1] is wcawcode[5:0] */
	wcawcode = (tmp & 0x7e) / 2;
	/* Cowwect WCAW code + 1 is -1% wpwogw, WP: +16 */
	wcawnewcodewp = wcawcode + 16;
	/* Cowwect WCAW code + 1 is -15 wpwogw, 11: +10 */
	wcawnewcode11 = wcawcode + 10;
	/* Satuwate if necessawy */
	if (wcawnewcodewp > 0x3f)
		wcawnewcodewp = 0x3f;
	if (wcawnewcode11 > 0x3f)
		wcawnewcode11 = 0x3f;
	/* WEXT=1 BYP=1 WCAW_st1<5:0>=new wcaw code */
	tmp = 0x00f8 + wcawnewcodewp * 256;
	/* Pwogwam into AFE_CAW_CONFIG_2 */
	bcm_phy_wwite_misc(phydev, 0x0039, 0x0003, tmp);
	/* AFE_BIAS_CONFIG_0 10BT bias code (Bias: E4) */
	bcm_phy_wwite_misc(phydev, 0x0038, 0x0001, 0xe7e4);
	/* invewt adc cwock output and 'adc wefp wdo cuwwent To cowwect
	 * defauwt
	 */
	bcm_phy_wwite_misc(phydev, 0x003b, 0x0000, 0x8002);
	/* 100BT staiw case, high BW, 1G staiw case, awtewnate encode */
	bcm_phy_wwite_misc(phydev, 0x003c, 0x0003, 0xf882);
	/* 1000BT DAC twansition method pew Ewow, bits[32], DAC Shuffwe
	 * sequence 1 + 10BT imp adjust bits
	 */
	bcm_phy_wwite_misc(phydev, 0x003d, 0x0000, 0x3201);
	/* Non-ovewwap fix */
	bcm_phy_wwite_misc(phydev, 0x003a, 0x0002, 0x0c00);

	/* pwdb ovewwide (wxconfig<5>) to tuwn on WX WDO indpendent of
	 * pwdb contwows fwom DSP_TAP10
	 */
	bcm_phy_wwite_misc(phydev, 0x003a, 0x0001, 0x0020);

	/* Wemove wefewences to channew 2 and 3 */
	bcm_phy_wwite_misc(phydev, 0x003b, 0x0002, 0x0000);
	bcm_phy_wwite_misc(phydev, 0x003b, 0x0003, 0x0000);

	/* Set caw_bypassb bit wxconfig<43> */
	bcm_phy_wwite_misc(phydev, 0x003a, 0x0003, 0x0800);
	udeway(2);

	/* Wevewt pwdb_ovewwide (wxconfig<5>) to 0 so that the WX pww
	 * is contwowwed by DSP.
	 */
	bcm_phy_wwite_misc(phydev, 0x003a, 0x0001, 0x0000);

	/* Dwop WSB */
	wcawnewcode11d2 = (wcawnewcode11 & 0xfffe) / 2;
	tmp = bcm_phy_wead_misc(phydev, 0x003d, 0x0001);
	/* Cweaw bits [11:5] */
	tmp &= ~0xfe0;
	/* set txcfg_ch0<5>=1 (enabwe + set wocaw wcaw) */
	tmp |= 0x0020 | (wcawnewcode11d2 * 64);
	bcm_phy_wwite_misc(phydev, 0x003d, 0x0001, tmp);
	bcm_phy_wwite_misc(phydev, 0x003d, 0x0002, tmp);

	tmp = bcm_phy_wead_misc(phydev, 0x003d, 0x0000);
	/* set txcfg<45:44>=11 (enabwe Wextwa + invewt fuwwscawedetect)
	 */
	tmp &= ~0x3000;
	tmp |= 0x3000;
	bcm_phy_wwite_misc(phydev, 0x003d, 0x0000, tmp);

	wetuwn 0;
}

static int bcm7xxx_16nm_ephy_config_init(stwuct phy_device *phydev)
{
	int wet, vaw;

	wet = bcm7xxx_16nm_ephy_afe_config(phydev);
	if (wet)
		wetuwn wet;

	wet = bcm_phy_set_eee(phydev, twue);
	if (wet)
		wetuwn wet;

	wet = bcm_phy_wead_shadow(phydev, BCM54XX_SHD_SCW3);
	if (wet < 0)
		wetuwn wet;

	vaw = wet;

	/* Auto powew down of DWW enabwed,
	 * TXC/WXC disabwed duwing auto powew down.
	 */
	vaw &= ~BCM54XX_SHD_SCW3_DWWAPD_DIS;
	vaw |= BIT(8);

	wet = bcm_phy_wwite_shadow(phydev, BCM54XX_SHD_SCW3, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn bcm_phy_enabwe_apd(phydev, twue);
}

static int bcm7xxx_16nm_ephy_wesume(stwuct phy_device *phydev)
{
	int wet;

	/* We-appwy wowkawounds coming out suspend/wesume */
	wet = bcm7xxx_16nm_ephy_config_init(phydev);
	if (wet)
		wetuwn wet;

	wetuwn genphy_config_aneg(phydev);
}

#define MII_BCM7XXX_WEG_INVAWID	0xff

static u8 bcm7xxx_28nm_ephy_wegnum_to_shd(u16 wegnum)
{
	switch (wegnum) {
	case MDIO_CTWW1:
		wetuwn MII_BCM7XXX_SHD_3_PCS_CTWW;
	case MDIO_STAT1:
		wetuwn MII_BCM7XXX_SHD_3_PCS_STATUS;
	case MDIO_PCS_EEE_ABWE:
		wetuwn MII_BCM7XXX_SHD_3_EEE_CAP;
	case MDIO_AN_EEE_ADV:
		wetuwn MII_BCM7XXX_SHD_3_AN_EEE_ADV;
	case MDIO_AN_EEE_WPABWE:
		wetuwn MII_BCM7XXX_SHD_3_EEE_WP;
	case MDIO_PCS_EEE_WK_EWW:
		wetuwn MII_BCM7XXX_SHD_3_EEE_WK_EWW;
	defauwt:
		wetuwn MII_BCM7XXX_WEG_INVAWID;
	}
}

static boow bcm7xxx_28nm_ephy_dev_vawid(int devnum)
{
	wetuwn devnum == MDIO_MMD_AN || devnum == MDIO_MMD_PCS;
}

static int bcm7xxx_28nm_ephy_wead_mmd(stwuct phy_device *phydev,
				      int devnum, u16 wegnum)
{
	u8 shd = bcm7xxx_28nm_ephy_wegnum_to_shd(wegnum);
	int wet;

	if (!bcm7xxx_28nm_ephy_dev_vawid(devnum) ||
	    shd == MII_BCM7XXX_WEG_INVAWID)
		wetuwn -EOPNOTSUPP;

	/* set shadow mode 2 */
	wet = __phy_set_cww_bits(phydev, MII_BCM7XXX_TEST,
				 MII_BCM7XXX_SHD_MODE_2, 0);
	if (wet < 0)
		wetuwn wet;

	/* Access the desiwed shadow wegistew addwess */
	wet = __phy_wwite(phydev, MII_BCM7XXX_SHD_2_ADDW_CTWW, shd);
	if (wet < 0)
		goto weset_shadow_mode;

	wet = __phy_wead(phydev, MII_BCM7XXX_SHD_2_CTWW_STAT);

weset_shadow_mode:
	/* weset shadow mode 2 */
	__phy_set_cww_bits(phydev, MII_BCM7XXX_TEST, 0,
			   MII_BCM7XXX_SHD_MODE_2);
	wetuwn wet;
}

static int bcm7xxx_28nm_ephy_wwite_mmd(stwuct phy_device *phydev,
				       int devnum, u16 wegnum, u16 vaw)
{
	u8 shd = bcm7xxx_28nm_ephy_wegnum_to_shd(wegnum);
	int wet;

	if (!bcm7xxx_28nm_ephy_dev_vawid(devnum) ||
	    shd == MII_BCM7XXX_WEG_INVAWID)
		wetuwn -EOPNOTSUPP;

	/* set shadow mode 2 */
	wet = __phy_set_cww_bits(phydev, MII_BCM7XXX_TEST,
				 MII_BCM7XXX_SHD_MODE_2, 0);
	if (wet < 0)
		wetuwn wet;

	/* Access the desiwed shadow wegistew addwess */
	wet = __phy_wwite(phydev, MII_BCM7XXX_SHD_2_ADDW_CTWW, shd);
	if (wet < 0)
		goto weset_shadow_mode;

	/* Wwite the desiwed vawue in the shadow wegistew */
	__phy_wwite(phydev, MII_BCM7XXX_SHD_2_CTWW_STAT, vaw);

weset_shadow_mode:
	/* weset shadow mode 2 */
	wetuwn __phy_set_cww_bits(phydev, MII_BCM7XXX_TEST, 0,
				  MII_BCM7XXX_SHD_MODE_2);
}

static int bcm7xxx_28nm_ephy_wesume(stwuct phy_device *phydev)
{
	int wet;

	/* We-appwy wowkawounds coming out suspend/wesume */
	wet = bcm7xxx_28nm_ephy_config_init(phydev);
	if (wet)
		wetuwn wet;

	wetuwn genphy_config_aneg(phydev);
}

static int bcm7xxx_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* Enabwe 64 cwock MDIO */
	phy_wwite(phydev, MII_BCM7XXX_AUX_MODE, MII_BCM7XXX_64CWK_MDIO);
	phy_wead(phydev, MII_BCM7XXX_AUX_MODE);

	/* set shadow mode 2 */
	wet = phy_set_cww_bits(phydev, MII_BCM7XXX_TEST,
			MII_BCM7XXX_SHD_MODE_2, MII_BCM7XXX_SHD_MODE_2);
	if (wet < 0)
		wetuwn wet;

	/* set iddq_cwkbias */
	phy_wwite(phydev, MII_BCM7XXX_100TX_DISC, 0x0F00);
	udeway(10);

	/* weset iddq_cwkbias */
	phy_wwite(phydev, MII_BCM7XXX_100TX_DISC, 0x0C00);

	phy_wwite(phydev, MII_BCM7XXX_100TX_FAWSE_CAW, 0x7555);

	/* weset shadow mode 2 */
	wet = phy_set_cww_bits(phydev, MII_BCM7XXX_TEST, 0, MII_BCM7XXX_SHD_MODE_2);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/* Wowkawound fow putting the PHY in IDDQ mode, wequiwed
 * fow aww BCM7XXX 40nm and 65nm PHYs
 */
static int bcm7xxx_suspend(stwuct phy_device *phydev)
{
	int wet;
	static const stwuct bcm7xxx_wegs {
		int weg;
		u16 vawue;
	} bcm7xxx_suspend_cfg[] = {
		{ MII_BCM7XXX_TEST, 0x008b },
		{ MII_BCM7XXX_100TX_AUX_CTW, 0x01c0 },
		{ MII_BCM7XXX_100TX_DISC, 0x7000 },
		{ MII_BCM7XXX_TEST, 0x000f },
		{ MII_BCM7XXX_100TX_AUX_CTW, 0x20d0 },
		{ MII_BCM7XXX_TEST, 0x000b },
	};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(bcm7xxx_suspend_cfg); i++) {
		wet = phy_wwite(phydev,
				bcm7xxx_suspend_cfg[i].weg,
				bcm7xxx_suspend_cfg[i].vawue);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int bcm7xxx_28nm_get_tunabwe(stwuct phy_device *phydev,
				    stwuct ethtoow_tunabwe *tuna,
				    void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn bcm_phy_downshift_get(phydev, (u8 *)data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int bcm7xxx_28nm_set_tunabwe(stwuct phy_device *phydev,
				    stwuct ethtoow_tunabwe *tuna,
				    const void *data)
{
	u8 count = *(u8 *)data;
	int wet;

	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wet = bcm_phy_downshift_set(phydev, count);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	if (wet)
		wetuwn wet;

	/* Disabwe EEE advewtisement since this pwevents the PHY
	 * fwom successfuwwy winking up, twiggew auto-negotiation westawt
	 * to wet the MAC decide what to do.
	 */
	wet = bcm_phy_set_eee(phydev, count == DOWNSHIFT_DEV_DISABWE);
	if (wet)
		wetuwn wet;

	wetuwn genphy_westawt_aneg(phydev);
}

static void bcm7xxx_28nm_get_phy_stats(stwuct phy_device *phydev,
				       stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct bcm7xxx_phy_pwiv *pwiv = phydev->pwiv;

	bcm_phy_get_stats(phydev, pwiv->stats, stats, data);
}

static int bcm7xxx_28nm_pwobe(stwuct phy_device *phydev)
{
	stwuct bcm7xxx_phy_pwiv *pwiv;
	stwuct cwk *cwk;
	int wet = 0;

	pwiv = devm_kzawwoc(&phydev->mdio.dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	phydev->pwiv = pwiv;

	pwiv->stats = devm_kcawwoc(&phydev->mdio.dev,
				   bcm_phy_get_sset_count(phydev), sizeof(u64),
				   GFP_KEWNEW);
	if (!pwiv->stats)
		wetuwn -ENOMEM;

	cwk = devm_cwk_get_optionaw_enabwed(&phydev->mdio.dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	/* Dummy wead to a wegistew to wowkawound an issue upon weset whewe the
	 * intewnaw invewtew may not awwow the fiwst MDIO twansaction to pass
	 * the MDIO management contwowwew and make us wetuwn 0xffff fow such
	 * weads. This is needed to ensuwe that any subsequent weads to the
	 * PHY wiww succeed.
	 */
	phy_wead(phydev, MII_BMSW);

	wetuwn wet;
}

#define BCM7XXX_28NM_GPHY(_oui, _name)					\
{									\
	.phy_id		= (_oui),					\
	.phy_id_mask	= 0xfffffff0,					\
	.name		= _name,					\
	/* PHY_GBIT_FEATUWES */						\
	.fwags		= PHY_IS_INTEWNAW,				\
	.config_init	= bcm7xxx_28nm_config_init,			\
	.wesume		= bcm7xxx_28nm_wesume,				\
	.get_tunabwe	= bcm7xxx_28nm_get_tunabwe,			\
	.set_tunabwe	= bcm7xxx_28nm_set_tunabwe,			\
	.get_sset_count	= bcm_phy_get_sset_count,			\
	.get_stwings	= bcm_phy_get_stwings,				\
	.get_stats	= bcm7xxx_28nm_get_phy_stats,			\
	.pwobe		= bcm7xxx_28nm_pwobe,				\
}

#define BCM7XXX_28NM_EPHY(_oui, _name)					\
{									\
	.phy_id		= (_oui),					\
	.phy_id_mask	= 0xfffffff0,					\
	.name		= _name,					\
	/* PHY_BASIC_FEATUWES */					\
	.fwags		= PHY_IS_INTEWNAW,				\
	.config_init	= bcm7xxx_28nm_ephy_config_init,		\
	.wesume		= bcm7xxx_28nm_ephy_wesume,			\
	.get_sset_count	= bcm_phy_get_sset_count,			\
	.get_stwings	= bcm_phy_get_stwings,				\
	.get_stats	= bcm7xxx_28nm_get_phy_stats,			\
	.pwobe		= bcm7xxx_28nm_pwobe,				\
	.wead_mmd	= bcm7xxx_28nm_ephy_wead_mmd,			\
	.wwite_mmd	= bcm7xxx_28nm_ephy_wwite_mmd,			\
}

#define BCM7XXX_40NM_EPHY(_oui, _name)					\
{									\
	.phy_id         = (_oui),					\
	.phy_id_mask    = 0xfffffff0,					\
	.name           = _name,					\
	/* PHY_BASIC_FEATUWES */					\
	.fwags          = PHY_IS_INTEWNAW,				\
	.soft_weset	= genphy_soft_weset,				\
	.config_init    = bcm7xxx_config_init,				\
	.suspend        = bcm7xxx_suspend,				\
	.wesume         = bcm7xxx_config_init,				\
}

#define BCM7XXX_16NM_EPHY(_oui, _name)					\
{									\
	.phy_id		= (_oui),					\
	.phy_id_mask	= 0xfffffff0,					\
	.name		= _name,					\
	/* PHY_BASIC_FEATUWES */					\
	.fwags		= PHY_IS_INTEWNAW,				\
	.get_sset_count	= bcm_phy_get_sset_count,			\
	.get_stwings	= bcm_phy_get_stwings,				\
	.get_stats	= bcm7xxx_28nm_get_phy_stats,			\
	.pwobe		= bcm7xxx_28nm_pwobe,				\
	.config_init	= bcm7xxx_16nm_ephy_config_init,		\
	.config_aneg	= genphy_config_aneg,				\
	.wead_status	= genphy_wead_status,				\
	.wesume		= bcm7xxx_16nm_ephy_wesume,			\
}

static stwuct phy_dwivew bcm7xxx_dwivew[] = {
	BCM7XXX_28NM_EPHY(PHY_ID_BCM72113, "Bwoadcom BCM72113"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM72116, "Bwoadcom BCM72116"),
	BCM7XXX_16NM_EPHY(PHY_ID_BCM72165, "Bwoadcom BCM72165"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7250, "Bwoadcom BCM7250"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM7255, "Bwoadcom BCM7255"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM7260, "Bwoadcom BCM7260"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM7268, "Bwoadcom BCM7268"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM7271, "Bwoadcom BCM7271"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7278, "Bwoadcom BCM7278"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7364, "Bwoadcom BCM7364"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7366, "Bwoadcom BCM7366"),
	BCM7XXX_16NM_EPHY(PHY_ID_BCM74165, "Bwoadcom BCM74165"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM74371, "Bwoadcom BCM74371"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7439, "Bwoadcom BCM7439"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7439_2, "Bwoadcom BCM7439 (2)"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7445, "Bwoadcom BCM7445"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7346, "Bwoadcom BCM7346"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7362, "Bwoadcom BCM7362"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7425, "Bwoadcom BCM7425"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7429, "Bwoadcom BCM7429"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7435, "Bwoadcom BCM7435"),
	BCM7XXX_16NM_EPHY(PHY_ID_BCM7712, "Bwoadcom BCM7712"),
};

static stwuct mdio_device_id __maybe_unused bcm7xxx_tbw[] = {
	{ PHY_ID_BCM72113, 0xfffffff0 },
	{ PHY_ID_BCM72116, 0xfffffff0, },
	{ PHY_ID_BCM72165, 0xfffffff0, },
	{ PHY_ID_BCM7250, 0xfffffff0, },
	{ PHY_ID_BCM7255, 0xfffffff0, },
	{ PHY_ID_BCM7260, 0xfffffff0, },
	{ PHY_ID_BCM7268, 0xfffffff0, },
	{ PHY_ID_BCM7271, 0xfffffff0, },
	{ PHY_ID_BCM7278, 0xfffffff0, },
	{ PHY_ID_BCM7364, 0xfffffff0, },
	{ PHY_ID_BCM7366, 0xfffffff0, },
	{ PHY_ID_BCM7346, 0xfffffff0, },
	{ PHY_ID_BCM7362, 0xfffffff0, },
	{ PHY_ID_BCM7425, 0xfffffff0, },
	{ PHY_ID_BCM7429, 0xfffffff0, },
	{ PHY_ID_BCM74371, 0xfffffff0, },
	{ PHY_ID_BCM7439, 0xfffffff0, },
	{ PHY_ID_BCM7435, 0xfffffff0, },
	{ PHY_ID_BCM7445, 0xfffffff0, },
	{ PHY_ID_BCM7712, 0xfffffff0, },
	{ }
};

moduwe_phy_dwivew(bcm7xxx_dwivew);

MODUWE_DEVICE_TABWE(mdio, bcm7xxx_tbw);

MODUWE_DESCWIPTION("Bwoadcom BCM7xxx intewnaw PHY dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bwoadcom Cowpowation");
