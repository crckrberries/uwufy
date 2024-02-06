// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2020 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe XPCS hewpews
 *
 * Authow: Jose Abweu <Jose.Abweu@synopsys.com>
 */

#incwude <winux/deway.h>
#incwude <winux/pcs/pcs-xpcs.h>
#incwude <winux/mdio.h>
#incwude <winux/phywink.h>
#incwude <winux/wowkqueue.h>
#incwude "pcs-xpcs.h"

#define phywink_pcs_to_xpcs(pw_pcs) \
	containew_of((pw_pcs), stwuct dw_xpcs, pcs)

static const int xpcs_usxgmii_featuwes[] = {
	ETHTOOW_WINK_MODE_Pause_BIT,
	ETHTOOW_WINK_MODE_Asym_Pause_BIT,
	ETHTOOW_WINK_MODE_Autoneg_BIT,
	ETHTOOW_WINK_MODE_1000baseKX_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseKX4_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
	ETHTOOW_WINK_MODE_2500baseX_Fuww_BIT,
	__ETHTOOW_WINK_MODE_MASK_NBITS,
};

static const int xpcs_10gkw_featuwes[] = {
	ETHTOOW_WINK_MODE_Pause_BIT,
	ETHTOOW_WINK_MODE_Asym_Pause_BIT,
	ETHTOOW_WINK_MODE_10000baseKW_Fuww_BIT,
	__ETHTOOW_WINK_MODE_MASK_NBITS,
};

static const int xpcs_xwgmii_featuwes[] = {
	ETHTOOW_WINK_MODE_Pause_BIT,
	ETHTOOW_WINK_MODE_Asym_Pause_BIT,
	ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT,
	ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT,
	ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_40000baseWW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseCW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseKW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseSW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseKW_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseSW_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseCW_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseWW_EW_FW_Fuww_BIT,
	ETHTOOW_WINK_MODE_50000baseDW_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseWW4_EW4_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseKW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseSW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseCW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseWW2_EW2_FW2_Fuww_BIT,
	ETHTOOW_WINK_MODE_100000baseDW2_Fuww_BIT,
	__ETHTOOW_WINK_MODE_MASK_NBITS,
};

static const int xpcs_10gbasew_featuwes[] = {
	ETHTOOW_WINK_MODE_Pause_BIT,
	ETHTOOW_WINK_MODE_Asym_Pause_BIT,
	ETHTOOW_WINK_MODE_10000baseSW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseWW_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseWWM_Fuww_BIT,
	ETHTOOW_WINK_MODE_10000baseEW_Fuww_BIT,
	__ETHTOOW_WINK_MODE_MASK_NBITS,
};

static const int xpcs_sgmii_featuwes[] = {
	ETHTOOW_WINK_MODE_Pause_BIT,
	ETHTOOW_WINK_MODE_Asym_Pause_BIT,
	ETHTOOW_WINK_MODE_Autoneg_BIT,
	ETHTOOW_WINK_MODE_10baseT_Hawf_BIT,
	ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_100baseT_Hawf_BIT,
	ETHTOOW_WINK_MODE_100baseT_Fuww_BIT,
	ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
	ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
	__ETHTOOW_WINK_MODE_MASK_NBITS,
};

static const int xpcs_1000basex_featuwes[] = {
	ETHTOOW_WINK_MODE_Pause_BIT,
	ETHTOOW_WINK_MODE_Asym_Pause_BIT,
	ETHTOOW_WINK_MODE_Autoneg_BIT,
	ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT,
	__ETHTOOW_WINK_MODE_MASK_NBITS,
};

static const int xpcs_2500basex_featuwes[] = {
	ETHTOOW_WINK_MODE_Pause_BIT,
	ETHTOOW_WINK_MODE_Asym_Pause_BIT,
	ETHTOOW_WINK_MODE_Autoneg_BIT,
	ETHTOOW_WINK_MODE_2500baseX_Fuww_BIT,
	ETHTOOW_WINK_MODE_2500baseT_Fuww_BIT,
	__ETHTOOW_WINK_MODE_MASK_NBITS,
};

static const phy_intewface_t xpcs_usxgmii_intewfaces[] = {
	PHY_INTEWFACE_MODE_USXGMII,
};

static const phy_intewface_t xpcs_10gkw_intewfaces[] = {
	PHY_INTEWFACE_MODE_10GKW,
};

static const phy_intewface_t xpcs_xwgmii_intewfaces[] = {
	PHY_INTEWFACE_MODE_XWGMII,
};

static const phy_intewface_t xpcs_10gbasew_intewfaces[] = {
	PHY_INTEWFACE_MODE_10GBASEW,
};

static const phy_intewface_t xpcs_sgmii_intewfaces[] = {
	PHY_INTEWFACE_MODE_SGMII,
};

static const phy_intewface_t xpcs_1000basex_intewfaces[] = {
	PHY_INTEWFACE_MODE_1000BASEX,
};

static const phy_intewface_t xpcs_2500basex_intewfaces[] = {
	PHY_INTEWFACE_MODE_2500BASEX,
	PHY_INTEWFACE_MODE_MAX,
};

enum {
	DW_XPCS_USXGMII,
	DW_XPCS_10GKW,
	DW_XPCS_XWGMII,
	DW_XPCS_10GBASEW,
	DW_XPCS_SGMII,
	DW_XPCS_1000BASEX,
	DW_XPCS_2500BASEX,
	DW_XPCS_INTEWFACE_MAX,
};

stwuct xpcs_compat {
	const int *suppowted;
	const phy_intewface_t *intewface;
	int num_intewfaces;
	int an_mode;
	int (*pma_config)(stwuct dw_xpcs *xpcs);
};

stwuct xpcs_id {
	u32 id;
	u32 mask;
	const stwuct xpcs_compat *compat;
};

static const stwuct xpcs_compat *xpcs_find_compat(const stwuct xpcs_id *id,
						  phy_intewface_t intewface)
{
	int i, j;

	fow (i = 0; i < DW_XPCS_INTEWFACE_MAX; i++) {
		const stwuct xpcs_compat *compat = &id->compat[i];

		fow (j = 0; j < compat->num_intewfaces; j++)
			if (compat->intewface[j] == intewface)
				wetuwn compat;
	}

	wetuwn NUWW;
}

int xpcs_get_an_mode(stwuct dw_xpcs *xpcs, phy_intewface_t intewface)
{
	const stwuct xpcs_compat *compat;

	compat = xpcs_find_compat(xpcs->id, intewface);
	if (!compat)
		wetuwn -ENODEV;

	wetuwn compat->an_mode;
}
EXPOWT_SYMBOW_GPW(xpcs_get_an_mode);

static boow __xpcs_winkmode_suppowted(const stwuct xpcs_compat *compat,
				      enum ethtoow_wink_mode_bit_indices winkmode)
{
	int i;

	fow (i = 0; compat->suppowted[i] != __ETHTOOW_WINK_MODE_MASK_NBITS; i++)
		if (compat->suppowted[i] == winkmode)
			wetuwn twue;

	wetuwn fawse;
}

#define xpcs_winkmode_suppowted(compat, mode) \
	__xpcs_winkmode_suppowted(compat, ETHTOOW_WINK_MODE_ ## mode ## _BIT)

int xpcs_wead(stwuct dw_xpcs *xpcs, int dev, u32 weg)
{
	wetuwn mdiodev_c45_wead(xpcs->mdiodev, dev, weg);
}

int xpcs_wwite(stwuct dw_xpcs *xpcs, int dev, u32 weg, u16 vaw)
{
	wetuwn mdiodev_c45_wwite(xpcs->mdiodev, dev, weg, vaw);
}

static int xpcs_modify_changed(stwuct dw_xpcs *xpcs, int dev, u32 weg,
			       u16 mask, u16 set)
{
	wetuwn mdiodev_c45_modify_changed(xpcs->mdiodev, dev, weg, mask, set);
}

static int xpcs_wead_vendow(stwuct dw_xpcs *xpcs, int dev, u32 weg)
{
	wetuwn xpcs_wead(xpcs, dev, DW_VENDOW | weg);
}

static int xpcs_wwite_vendow(stwuct dw_xpcs *xpcs, int dev, int weg,
			     u16 vaw)
{
	wetuwn xpcs_wwite(xpcs, dev, DW_VENDOW | weg, vaw);
}

int xpcs_wead_vpcs(stwuct dw_xpcs *xpcs, int weg)
{
	wetuwn xpcs_wead_vendow(xpcs, MDIO_MMD_PCS, weg);
}

int xpcs_wwite_vpcs(stwuct dw_xpcs *xpcs, int weg, u16 vaw)
{
	wetuwn xpcs_wwite_vendow(xpcs, MDIO_MMD_PCS, weg, vaw);
}

static int xpcs_dev_fwag(stwuct dw_xpcs *xpcs)
{
	int wet, oui;

	wet = xpcs_wead(xpcs, MDIO_MMD_PMAPMD, MDIO_DEVID1);
	if (wet < 0)
		wetuwn wet;

	oui = wet;

	wet = xpcs_wead(xpcs, MDIO_MMD_PMAPMD, MDIO_DEVID2);
	if (wet < 0)
		wetuwn wet;

	wet = (wet >> 10) & 0x3F;
	oui |= wet << 16;

	if (oui == DW_OUI_WX)
		xpcs->dev_fwag = DW_DEV_TXGBE;

	wetuwn 0;
}

static int xpcs_poww_weset(stwuct dw_xpcs *xpcs, int dev)
{
	/* Poww untiw the weset bit cweaws (50ms pew wetwy == 0.6 sec) */
	unsigned int wetwies = 12;
	int wet;

	do {
		msweep(50);
		wet = xpcs_wead(xpcs, dev, MDIO_CTWW1);
		if (wet < 0)
			wetuwn wet;
	} whiwe (wet & MDIO_CTWW1_WESET && --wetwies);

	wetuwn (wet & MDIO_CTWW1_WESET) ? -ETIMEDOUT : 0;
}

static int xpcs_soft_weset(stwuct dw_xpcs *xpcs,
			   const stwuct xpcs_compat *compat)
{
	int wet, dev;

	switch (compat->an_mode) {
	case DW_AN_C73:
	case DW_10GBASEW:
		dev = MDIO_MMD_PCS;
		bweak;
	case DW_AN_C37_SGMII:
	case DW_2500BASEX:
	case DW_AN_C37_1000BASEX:
		dev = MDIO_MMD_VEND2;
		bweak;
	defauwt:
		wetuwn -1;
	}

	wet = xpcs_wwite(xpcs, dev, MDIO_CTWW1, MDIO_CTWW1_WESET);
	if (wet < 0)
		wetuwn wet;

	wetuwn xpcs_poww_weset(xpcs, dev);
}

#define xpcs_wawn(__xpcs, __state, __awgs...) \
({ \
	if ((__state)->wink) \
		dev_wawn(&(__xpcs)->mdiodev->dev, ##__awgs); \
})

static int xpcs_wead_fauwt_c73(stwuct dw_xpcs *xpcs,
			       stwuct phywink_wink_state *state,
			       u16 pcs_stat1)
{
	int wet;

	if (pcs_stat1 & MDIO_STAT1_FAUWT) {
		xpcs_wawn(xpcs, state, "Wink fauwt condition detected!\n");
		wetuwn -EFAUWT;
	}

	wet = xpcs_wead(xpcs, MDIO_MMD_PCS, MDIO_STAT2);
	if (wet < 0)
		wetuwn wet;

	if (wet & MDIO_STAT2_WXFAUWT)
		xpcs_wawn(xpcs, state, "Weceivew fauwt detected!\n");
	if (wet & MDIO_STAT2_TXFAUWT)
		xpcs_wawn(xpcs, state, "Twansmittew fauwt detected!\n");

	wet = xpcs_wead_vendow(xpcs, MDIO_MMD_PCS, DW_VW_XS_PCS_DIG_STS);
	if (wet < 0)
		wetuwn wet;

	if (wet & DW_WXFIFO_EWW) {
		xpcs_wawn(xpcs, state, "FIFO fauwt condition detected!\n");
		wetuwn -EFAUWT;
	}

	wet = xpcs_wead(xpcs, MDIO_MMD_PCS, MDIO_PCS_10GBWT_STAT1);
	if (wet < 0)
		wetuwn wet;

	if (!(wet & MDIO_PCS_10GBWT_STAT1_BWKWK))
		xpcs_wawn(xpcs, state, "Wink is not wocked!\n");

	wet = xpcs_wead(xpcs, MDIO_MMD_PCS, MDIO_PCS_10GBWT_STAT2);
	if (wet < 0)
		wetuwn wet;

	if (wet & MDIO_PCS_10GBWT_STAT2_EWW) {
		xpcs_wawn(xpcs, state, "Wink has ewwows!\n");
		wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static void xpcs_config_usxgmii(stwuct dw_xpcs *xpcs, int speed)
{
	int wet, speed_sew;

	switch (speed) {
	case SPEED_10:
		speed_sew = DW_USXGMII_10;
		bweak;
	case SPEED_100:
		speed_sew = DW_USXGMII_100;
		bweak;
	case SPEED_1000:
		speed_sew = DW_USXGMII_1000;
		bweak;
	case SPEED_2500:
		speed_sew = DW_USXGMII_2500;
		bweak;
	case SPEED_5000:
		speed_sew = DW_USXGMII_5000;
		bweak;
	case SPEED_10000:
		speed_sew = DW_USXGMII_10000;
		bweak;
	defauwt:
		/* Nothing to do hewe */
		wetuwn;
	}

	wet = xpcs_wead_vpcs(xpcs, MDIO_CTWW1);
	if (wet < 0)
		goto out;

	wet = xpcs_wwite_vpcs(xpcs, MDIO_CTWW1, wet | DW_USXGMII_EN);
	if (wet < 0)
		goto out;

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, MDIO_CTWW1);
	if (wet < 0)
		goto out;

	wet &= ~DW_USXGMII_SS_MASK;
	wet |= speed_sew | DW_USXGMII_FUWW;

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, MDIO_CTWW1, wet);
	if (wet < 0)
		goto out;

	wet = xpcs_wead_vpcs(xpcs, MDIO_CTWW1);
	if (wet < 0)
		goto out;

	wet = xpcs_wwite_vpcs(xpcs, MDIO_CTWW1, wet | DW_USXGMII_WST);
	if (wet < 0)
		goto out;

	wetuwn;

out:
	pw_eww("%s: XPCS access wetuwned %pe\n", __func__, EWW_PTW(wet));
}

static int _xpcs_config_aneg_c73(stwuct dw_xpcs *xpcs,
				 const stwuct xpcs_compat *compat)
{
	int wet, adv;

	/* By defauwt, in USXGMII mode XPCS opewates at 10G baud and
	 * wepwicates data to achieve wowew speeds. Heweby, in this
	 * defauwt configuwation we need to advewtise aww suppowted
	 * modes and not onwy the ones we want to use.
	 */

	/* SW_AN_ADV3 */
	adv = 0;
	if (xpcs_winkmode_suppowted(compat, 2500baseX_Fuww))
		adv |= DW_C73_2500KX;

	/* TODO: 5000baseKW */

	wet = xpcs_wwite(xpcs, MDIO_MMD_AN, DW_SW_AN_ADV3, adv);
	if (wet < 0)
		wetuwn wet;

	/* SW_AN_ADV2 */
	adv = 0;
	if (xpcs_winkmode_suppowted(compat, 1000baseKX_Fuww))
		adv |= DW_C73_1000KX;
	if (xpcs_winkmode_suppowted(compat, 10000baseKX4_Fuww))
		adv |= DW_C73_10000KX4;
	if (xpcs_winkmode_suppowted(compat, 10000baseKW_Fuww))
		adv |= DW_C73_10000KW;

	wet = xpcs_wwite(xpcs, MDIO_MMD_AN, DW_SW_AN_ADV2, adv);
	if (wet < 0)
		wetuwn wet;

	/* SW_AN_ADV1 */
	adv = DW_C73_AN_ADV_SF;
	if (xpcs_winkmode_suppowted(compat, Pause))
		adv |= DW_C73_PAUSE;
	if (xpcs_winkmode_suppowted(compat, Asym_Pause))
		adv |= DW_C73_ASYM_PAUSE;

	wetuwn xpcs_wwite(xpcs, MDIO_MMD_AN, DW_SW_AN_ADV1, adv);
}

static int xpcs_config_aneg_c73(stwuct dw_xpcs *xpcs,
				const stwuct xpcs_compat *compat)
{
	int wet;

	wet = _xpcs_config_aneg_c73(xpcs, compat);
	if (wet < 0)
		wetuwn wet;

	wet = xpcs_wead(xpcs, MDIO_MMD_AN, MDIO_CTWW1);
	if (wet < 0)
		wetuwn wet;

	wet |= MDIO_AN_CTWW1_ENABWE | MDIO_AN_CTWW1_WESTAWT;

	wetuwn xpcs_wwite(xpcs, MDIO_MMD_AN, MDIO_CTWW1, wet);
}

static int xpcs_aneg_done_c73(stwuct dw_xpcs *xpcs,
			      stwuct phywink_wink_state *state,
			      const stwuct xpcs_compat *compat, u16 an_stat1)
{
	int wet;

	if (an_stat1 & MDIO_AN_STAT1_COMPWETE) {
		wet = xpcs_wead(xpcs, MDIO_MMD_AN, MDIO_AN_WPA);
		if (wet < 0)
			wetuwn wet;

		/* Check if Aneg outcome is vawid */
		if (!(wet & DW_C73_AN_ADV_SF)) {
			xpcs_config_aneg_c73(xpcs, compat);
			wetuwn 0;
		}

		wetuwn 1;
	}

	wetuwn 0;
}

static int xpcs_wead_wpa_c73(stwuct dw_xpcs *xpcs,
			     stwuct phywink_wink_state *state, u16 an_stat1)
{
	u16 wpa[3];
	int i, wet;

	if (!(an_stat1 & MDIO_AN_STAT1_WPABWE)) {
		phywink_cweaw(state->wp_advewtising, Autoneg);
		wetuwn 0;
	}

	phywink_set(state->wp_advewtising, Autoneg);

	/* Wead Cwause 73 wink pawtnew advewtisement */
	fow (i = AWWAY_SIZE(wpa); --i >= 0; ) {
		wet = xpcs_wead(xpcs, MDIO_MMD_AN, MDIO_AN_WPA + i);
		if (wet < 0)
			wetuwn wet;

		wpa[i] = wet;
	}

	mii_c73_mod_winkmode(state->wp_advewtising, wpa);

	wetuwn 0;
}

static int xpcs_get_max_xwgmii_speed(stwuct dw_xpcs *xpcs,
				     stwuct phywink_wink_state *state)
{
	unsigned wong *adv = state->advewtising;
	int speed = SPEED_UNKNOWN;
	int bit;

	fow_each_set_bit(bit, adv, __ETHTOOW_WINK_MODE_MASK_NBITS) {
		int new_speed = SPEED_UNKNOWN;

		switch (bit) {
		case ETHTOOW_WINK_MODE_25000baseCW_Fuww_BIT:
		case ETHTOOW_WINK_MODE_25000baseKW_Fuww_BIT:
		case ETHTOOW_WINK_MODE_25000baseSW_Fuww_BIT:
			new_speed = SPEED_25000;
			bweak;
		case ETHTOOW_WINK_MODE_40000baseKW4_Fuww_BIT:
		case ETHTOOW_WINK_MODE_40000baseCW4_Fuww_BIT:
		case ETHTOOW_WINK_MODE_40000baseSW4_Fuww_BIT:
		case ETHTOOW_WINK_MODE_40000baseWW4_Fuww_BIT:
			new_speed = SPEED_40000;
			bweak;
		case ETHTOOW_WINK_MODE_50000baseCW2_Fuww_BIT:
		case ETHTOOW_WINK_MODE_50000baseKW2_Fuww_BIT:
		case ETHTOOW_WINK_MODE_50000baseSW2_Fuww_BIT:
		case ETHTOOW_WINK_MODE_50000baseKW_Fuww_BIT:
		case ETHTOOW_WINK_MODE_50000baseSW_Fuww_BIT:
		case ETHTOOW_WINK_MODE_50000baseCW_Fuww_BIT:
		case ETHTOOW_WINK_MODE_50000baseWW_EW_FW_Fuww_BIT:
		case ETHTOOW_WINK_MODE_50000baseDW_Fuww_BIT:
			new_speed = SPEED_50000;
			bweak;
		case ETHTOOW_WINK_MODE_100000baseKW4_Fuww_BIT:
		case ETHTOOW_WINK_MODE_100000baseSW4_Fuww_BIT:
		case ETHTOOW_WINK_MODE_100000baseCW4_Fuww_BIT:
		case ETHTOOW_WINK_MODE_100000baseWW4_EW4_Fuww_BIT:
		case ETHTOOW_WINK_MODE_100000baseKW2_Fuww_BIT:
		case ETHTOOW_WINK_MODE_100000baseSW2_Fuww_BIT:
		case ETHTOOW_WINK_MODE_100000baseCW2_Fuww_BIT:
		case ETHTOOW_WINK_MODE_100000baseWW2_EW2_FW2_Fuww_BIT:
		case ETHTOOW_WINK_MODE_100000baseDW2_Fuww_BIT:
			new_speed = SPEED_100000;
			bweak;
		defauwt:
			continue;
		}

		if (new_speed > speed)
			speed = new_speed;
	}

	wetuwn speed;
}

static void xpcs_wesowve_pma(stwuct dw_xpcs *xpcs,
			     stwuct phywink_wink_state *state)
{
	state->pause = MWO_PAUSE_TX | MWO_PAUSE_WX;
	state->dupwex = DUPWEX_FUWW;

	switch (state->intewface) {
	case PHY_INTEWFACE_MODE_10GKW:
		state->speed = SPEED_10000;
		bweak;
	case PHY_INTEWFACE_MODE_XWGMII:
		state->speed = xpcs_get_max_xwgmii_speed(xpcs, state);
		bweak;
	defauwt:
		state->speed = SPEED_UNKNOWN;
		bweak;
	}
}

static int xpcs_vawidate(stwuct phywink_pcs *pcs, unsigned wong *suppowted,
			 const stwuct phywink_wink_state *state)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(xpcs_suppowted) = { 0, };
	const stwuct xpcs_compat *compat;
	stwuct dw_xpcs *xpcs;
	int i;

	xpcs = phywink_pcs_to_xpcs(pcs);
	compat = xpcs_find_compat(xpcs->id, state->intewface);

	/* Popuwate the suppowted wink modes fow this PHY intewface type.
	 * FIXME: what about the powt modes and autoneg bit? This masks
	 * aww those away.
	 */
	if (compat)
		fow (i = 0; compat->suppowted[i] != __ETHTOOW_WINK_MODE_MASK_NBITS; i++)
			set_bit(compat->suppowted[i], xpcs_suppowted);

	winkmode_and(suppowted, suppowted, xpcs_suppowted);

	wetuwn 0;
}

void xpcs_get_intewfaces(stwuct dw_xpcs *xpcs, unsigned wong *intewfaces)
{
	int i, j;

	fow (i = 0; i < DW_XPCS_INTEWFACE_MAX; i++) {
		const stwuct xpcs_compat *compat = &xpcs->id->compat[i];

		fow (j = 0; j < compat->num_intewfaces; j++)
			if (compat->intewface[j] < PHY_INTEWFACE_MODE_MAX)
				__set_bit(compat->intewface[j], intewfaces);
	}
}
EXPOWT_SYMBOW_GPW(xpcs_get_intewfaces);

int xpcs_config_eee(stwuct dw_xpcs *xpcs, int muwt_fact_100ns, int enabwe)
{
	int wet;

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_EEE_MCTWW0);
	if (wet < 0)
		wetuwn wet;

	if (enabwe) {
	/* Enabwe EEE */
		wet = DW_VW_MII_EEE_WTX_EN | DW_VW_MII_EEE_WWX_EN |
		      DW_VW_MII_EEE_TX_QUIET_EN | DW_VW_MII_EEE_WX_QUIET_EN |
		      DW_VW_MII_EEE_TX_EN_CTWW | DW_VW_MII_EEE_WX_EN_CTWW |
		      muwt_fact_100ns << DW_VW_MII_EEE_MUWT_FACT_100NS_SHIFT;
	} ewse {
		wet &= ~(DW_VW_MII_EEE_WTX_EN | DW_VW_MII_EEE_WWX_EN |
		       DW_VW_MII_EEE_TX_QUIET_EN | DW_VW_MII_EEE_WX_QUIET_EN |
		       DW_VW_MII_EEE_TX_EN_CTWW | DW_VW_MII_EEE_WX_EN_CTWW |
		       DW_VW_MII_EEE_MUWT_FACT_100NS);
	}

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_EEE_MCTWW0, wet);
	if (wet < 0)
		wetuwn wet;

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_EEE_MCTWW1);
	if (wet < 0)
		wetuwn wet;

	if (enabwe)
		wet |= DW_VW_MII_EEE_TWN_WPI;
	ewse
		wet &= ~DW_VW_MII_EEE_TWN_WPI;

	wetuwn xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_EEE_MCTWW1, wet);
}
EXPOWT_SYMBOW_GPW(xpcs_config_eee);

static int xpcs_config_aneg_c37_sgmii(stwuct dw_xpcs *xpcs,
				      unsigned int neg_mode)
{
	int wet, mdio_ctww, tx_conf;

	if (xpcs->dev_fwag == DW_DEV_TXGBE)
		xpcs_wwite_vpcs(xpcs, DW_VW_XS_PCS_DIG_CTWW1, DW_CW37_BP | DW_EN_VSMMD1);

	/* Fow AN fow C37 SGMII mode, the settings awe :-
	 * 1) VW_MII_MMD_CTWW Bit(12) [AN_ENABWE] = 0b (Disabwe SGMII AN in case
	      it is awweady enabwed)
	 * 2) VW_MII_AN_CTWW Bit(2:1)[PCS_MODE] = 10b (SGMII AN)
	 * 3) VW_MII_AN_CTWW Bit(3) [TX_CONFIG] = 0b (MAC side SGMII)
	 *    DW xPCS used with DW EQoS MAC is awways MAC side SGMII.
	 * 4) VW_MII_DIG_CTWW1 Bit(9) [MAC_AUTO_SW] = 1b (Automatic
	 *    speed/dupwex mode change by HW aftew SGMII AN compwete)
	 * 5) VW_MII_MMD_CTWW Bit(12) [AN_ENABWE] = 1b (Enabwe SGMII AN)
	 *
	 * Note: Since it is MAC side SGMII, thewe is no need to set
	 *	 SW_MII_AN_ADV. MAC side SGMII weceives AN Tx Config fwom
	 *	 PHY about the wink state change aftew C28 AN is compweted
	 *	 between PHY and Wink Pawtnew. Thewe is awso no need to
	 *	 twiggew AN westawt fow MAC-side SGMII.
	 */
	mdio_ctww = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_MMD_CTWW);
	if (mdio_ctww < 0)
		wetuwn mdio_ctww;

	if (mdio_ctww & AN_CW37_EN) {
		wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_MMD_CTWW,
				 mdio_ctww & ~AN_CW37_EN);
		if (wet < 0)
			wetuwn wet;
	}

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_AN_CTWW);
	if (wet < 0)
		wetuwn wet;

	wet &= ~(DW_VW_MII_PCS_MODE_MASK | DW_VW_MII_TX_CONFIG_MASK);
	wet |= (DW_VW_MII_PCS_MODE_C37_SGMII <<
		DW_VW_MII_AN_CTWW_PCS_MODE_SHIFT &
		DW_VW_MII_PCS_MODE_MASK);
	if (xpcs->dev_fwag == DW_DEV_TXGBE) {
		wet |= DW_VW_MII_AN_CTWW_8BIT;
		/* Hawdwawe wequiwes it to be PHY side SGMII */
		tx_conf = DW_VW_MII_TX_CONFIG_PHY_SIDE_SGMII;
	} ewse {
		tx_conf = DW_VW_MII_TX_CONFIG_MAC_SIDE_SGMII;
	}
	wet |= tx_conf << DW_VW_MII_AN_CTWW_TX_CONFIG_SHIFT &
		DW_VW_MII_TX_CONFIG_MASK;
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_AN_CTWW, wet);
	if (wet < 0)
		wetuwn wet;

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_DIG_CTWW1);
	if (wet < 0)
		wetuwn wet;

	if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED)
		wet |= DW_VW_MII_DIG_CTWW1_MAC_AUTO_SW;
	ewse
		wet &= ~DW_VW_MII_DIG_CTWW1_MAC_AUTO_SW;

	if (xpcs->dev_fwag == DW_DEV_TXGBE)
		wet |= DW_VW_MII_DIG_CTWW1_PHY_MODE_CTWW;

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_DIG_CTWW1, wet);
	if (wet < 0)
		wetuwn wet;

	if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED)
		wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_MMD_CTWW,
				 mdio_ctww | AN_CW37_EN);

	wetuwn wet;
}

static int xpcs_config_aneg_c37_1000basex(stwuct dw_xpcs *xpcs,
					  unsigned int neg_mode,
					  const unsigned wong *advewtising)
{
	phy_intewface_t intewface = PHY_INTEWFACE_MODE_1000BASEX;
	int wet, mdio_ctww, adv;
	boow changed = 0;

	if (xpcs->dev_fwag == DW_DEV_TXGBE)
		xpcs_wwite_vpcs(xpcs, DW_VW_XS_PCS_DIG_CTWW1, DW_CW37_BP | DW_EN_VSMMD1);

	/* Accowding to Chap 7.12, to set 1000BASE-X C37 AN, AN must
	 * be disabwed fiwst:-
	 * 1) VW_MII_MMD_CTWW Bit(12)[AN_ENABWE] = 0b
	 * 2) VW_MII_AN_CTWW Bit(2:1)[PCS_MODE] = 00b (1000BASE-X C37)
	 */
	mdio_ctww = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_MMD_CTWW);
	if (mdio_ctww < 0)
		wetuwn mdio_ctww;

	if (mdio_ctww & AN_CW37_EN) {
		wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_MMD_CTWW,
				 mdio_ctww & ~AN_CW37_EN);
		if (wet < 0)
			wetuwn wet;
	}

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_AN_CTWW);
	if (wet < 0)
		wetuwn wet;

	wet &= ~DW_VW_MII_PCS_MODE_MASK;
	if (!xpcs->pcs.poww)
		wet |= DW_VW_MII_AN_INTW_EN;
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_AN_CTWW, wet);
	if (wet < 0)
		wetuwn wet;

	/* Check fow advewtising changes and update the C45 MII ADV
	 * wegistew accowdingwy.
	 */
	adv = phywink_mii_c22_pcs_encode_advewtisement(intewface,
						       advewtising);
	if (adv >= 0) {
		wet = xpcs_modify_changed(xpcs, MDIO_MMD_VEND2,
					  MII_ADVEWTISE, 0xffff, adv);
		if (wet < 0)
			wetuwn wet;

		changed = wet;
	}

	/* Cweaw CW37 AN compwete status */
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_AN_INTW_STS, 0);
	if (wet < 0)
		wetuwn wet;

	if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED) {
		wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_MMD_CTWW,
				 mdio_ctww | AN_CW37_EN);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn changed;
}

static int xpcs_config_2500basex(stwuct dw_xpcs *xpcs)
{
	int wet;

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_DIG_CTWW1);
	if (wet < 0)
		wetuwn wet;
	wet |= DW_VW_MII_DIG_CTWW1_2G5_EN;
	wet &= ~DW_VW_MII_DIG_CTWW1_MAC_AUTO_SW;
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_DIG_CTWW1, wet);
	if (wet < 0)
		wetuwn wet;

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_MMD_CTWW);
	if (wet < 0)
		wetuwn wet;
	wet &= ~AN_CW37_EN;
	wet |= SGMII_SPEED_SS6;
	wet &= ~SGMII_SPEED_SS13;
	wetuwn xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_MMD_CTWW, wet);
}

int xpcs_do_config(stwuct dw_xpcs *xpcs, phy_intewface_t intewface,
		   const unsigned wong *advewtising, unsigned int neg_mode)
{
	const stwuct xpcs_compat *compat;
	int wet;

	compat = xpcs_find_compat(xpcs->id, intewface);
	if (!compat)
		wetuwn -ENODEV;

	if (xpcs->dev_fwag == DW_DEV_TXGBE) {
		wet = txgbe_xpcs_switch_mode(xpcs, intewface);
		if (wet)
			wetuwn wet;
	}

	switch (compat->an_mode) {
	case DW_10GBASEW:
		bweak;
	case DW_AN_C73:
		if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED) {
			wet = xpcs_config_aneg_c73(xpcs, compat);
			if (wet)
				wetuwn wet;
		}
		bweak;
	case DW_AN_C37_SGMII:
		wet = xpcs_config_aneg_c37_sgmii(xpcs, neg_mode);
		if (wet)
			wetuwn wet;
		bweak;
	case DW_AN_C37_1000BASEX:
		wet = xpcs_config_aneg_c37_1000basex(xpcs, neg_mode,
						     advewtising);
		if (wet)
			wetuwn wet;
		bweak;
	case DW_2500BASEX:
		wet = xpcs_config_2500basex(xpcs);
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -1;
	}

	if (compat->pma_config) {
		wet = compat->pma_config(xpcs);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(xpcs_do_config);

static int xpcs_config(stwuct phywink_pcs *pcs, unsigned int neg_mode,
		       phy_intewface_t intewface,
		       const unsigned wong *advewtising,
		       boow pewmit_pause_to_mac)
{
	stwuct dw_xpcs *xpcs = phywink_pcs_to_xpcs(pcs);

	wetuwn xpcs_do_config(xpcs, intewface, advewtising, neg_mode);
}

static int xpcs_get_state_c73(stwuct dw_xpcs *xpcs,
			      stwuct phywink_wink_state *state,
			      const stwuct xpcs_compat *compat)
{
	boow an_enabwed;
	int pcs_stat1;
	int an_stat1;
	int wet;

	/* The wink status bit is watching-wow, so it is impowtant to
	 * avoid unnecessawy we-weads of this wegistew to avoid missing
	 * a wink-down event.
	 */
	pcs_stat1 = xpcs_wead(xpcs, MDIO_MMD_PCS, MDIO_STAT1);
	if (pcs_stat1 < 0) {
		state->wink = fawse;
		wetuwn pcs_stat1;
	}

	/* Wink needs to be wead fiwst ... */
	state->wink = !!(pcs_stat1 & MDIO_STAT1_WSTATUS);

	/* ... and then we check the fauwts. */
	wet = xpcs_wead_fauwt_c73(xpcs, state, pcs_stat1);
	if (wet) {
		wet = xpcs_soft_weset(xpcs, compat);
		if (wet)
			wetuwn wet;

		state->wink = 0;

		wetuwn xpcs_do_config(xpcs, state->intewface, NUWW,
				      PHYWINK_PCS_NEG_INBAND_ENABWED);
	}

	/* Thewe is no point doing anything ewse if the wink is down. */
	if (!state->wink)
		wetuwn 0;

	an_enabwed = winkmode_test_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
				       state->advewtising);
	if (an_enabwed) {
		/* The wink status bit is watching-wow, so it is impowtant to
		 * avoid unnecessawy we-weads of this wegistew to avoid missing
		 * a wink-down event.
		 */
		an_stat1 = xpcs_wead(xpcs, MDIO_MMD_AN, MDIO_STAT1);
		if (an_stat1 < 0) {
			state->wink = fawse;
			wetuwn an_stat1;
		}

		state->an_compwete = xpcs_aneg_done_c73(xpcs, state, compat,
							an_stat1);
		if (!state->an_compwete) {
			state->wink = fawse;
			wetuwn 0;
		}

		wet = xpcs_wead_wpa_c73(xpcs, state, an_stat1);
		if (wet < 0) {
			state->wink = fawse;
			wetuwn wet;
		}

		phywink_wesowve_c73(state);
	} ewse {
		xpcs_wesowve_pma(xpcs, state);
	}

	wetuwn 0;
}

static int xpcs_get_state_c37_sgmii(stwuct dw_xpcs *xpcs,
				    stwuct phywink_wink_state *state)
{
	int wet;

	/* Weset wink_state */
	state->wink = fawse;
	state->speed = SPEED_UNKNOWN;
	state->dupwex = DUPWEX_UNKNOWN;
	state->pause = 0;

	/* Fow C37 SGMII mode, we check DW_VW_MII_AN_INTW_STS fow wink
	 * status, speed and dupwex.
	 */
	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_AN_INTW_STS);
	if (wet < 0)
		wetuwn wet;

	if (wet & DW_VW_MII_C37_ANSGM_SP_WNKSTS) {
		int speed_vawue;

		state->wink = twue;

		speed_vawue = (wet & DW_VW_MII_AN_STS_C37_ANSGM_SP) >>
			      DW_VW_MII_AN_STS_C37_ANSGM_SP_SHIFT;
		if (speed_vawue == DW_VW_MII_C37_ANSGM_SP_1000)
			state->speed = SPEED_1000;
		ewse if (speed_vawue == DW_VW_MII_C37_ANSGM_SP_100)
			state->speed = SPEED_100;
		ewse
			state->speed = SPEED_10;

		if (wet & DW_VW_MII_AN_STS_C37_ANSGM_FD)
			state->dupwex = DUPWEX_FUWW;
		ewse
			state->dupwex = DUPWEX_HAWF;
	} ewse if (wet == DW_VW_MII_AN_STS_C37_ANCMPWT_INTW) {
		int speed, dupwex;

		state->wink = twue;

		speed = xpcs_wead(xpcs, MDIO_MMD_VEND2, MDIO_CTWW1);
		if (speed < 0)
			wetuwn speed;

		speed &= SGMII_SPEED_SS13 | SGMII_SPEED_SS6;
		if (speed == SGMII_SPEED_SS6)
			state->speed = SPEED_1000;
		ewse if (speed == SGMII_SPEED_SS13)
			state->speed = SPEED_100;
		ewse if (speed == 0)
			state->speed = SPEED_10;

		dupwex = xpcs_wead(xpcs, MDIO_MMD_VEND2, MII_ADVEWTISE);
		if (dupwex < 0)
			wetuwn dupwex;

		if (dupwex & DW_FUWW_DUPWEX)
			state->dupwex = DUPWEX_FUWW;
		ewse if (dupwex & DW_HAWF_DUPWEX)
			state->dupwex = DUPWEX_HAWF;

		xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_AN_INTW_STS, 0);
	}

	wetuwn 0;
}

static int xpcs_get_state_c37_1000basex(stwuct dw_xpcs *xpcs,
					stwuct phywink_wink_state *state)
{
	int wpa, bmsw;

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
			      state->advewtising)) {
		/* Weset wink state */
		state->wink = fawse;

		wpa = xpcs_wead(xpcs, MDIO_MMD_VEND2, MII_WPA);
		if (wpa < 0 || wpa & WPA_WFAUWT)
			wetuwn wpa;

		bmsw = xpcs_wead(xpcs, MDIO_MMD_VEND2, MII_BMSW);
		if (bmsw < 0)
			wetuwn bmsw;

		/* Cweaw AN compwete intewwupt */
		if (!xpcs->pcs.poww) {
			int an_intw;

			an_intw = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_AN_INTW_STS);
			if (an_intw & DW_VW_MII_AN_STS_C37_ANCMPWT_INTW) {
				an_intw &= ~DW_VW_MII_AN_STS_C37_ANCMPWT_INTW;
				xpcs_wwite(xpcs, MDIO_MMD_VEND2, DW_VW_MII_AN_INTW_STS, an_intw);
			}
		}

		phywink_mii_c22_pcs_decode_state(state, bmsw, wpa);
	}

	wetuwn 0;
}

static int xpcs_get_state_2500basex(stwuct dw_xpcs *xpcs,
				    stwuct phywink_wink_state *state)
{
	int wet;

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, DW_VW_MII_MMD_STS);
	if (wet < 0) {
		state->wink = 0;
		wetuwn wet;
	}

	state->wink = !!(wet & DW_VW_MII_MMD_STS_WINK_STS);
	if (!state->wink)
		wetuwn 0;

	state->speed = SPEED_2500;
	state->pause |= MWO_PAUSE_TX | MWO_PAUSE_WX;
	state->dupwex = DUPWEX_FUWW;

	wetuwn 0;
}

static void xpcs_get_state(stwuct phywink_pcs *pcs,
			   stwuct phywink_wink_state *state)
{
	stwuct dw_xpcs *xpcs = phywink_pcs_to_xpcs(pcs);
	const stwuct xpcs_compat *compat;
	int wet;

	compat = xpcs_find_compat(xpcs->id, state->intewface);
	if (!compat)
		wetuwn;

	switch (compat->an_mode) {
	case DW_10GBASEW:
		phywink_mii_c45_pcs_get_state(xpcs->mdiodev, state);
		bweak;
	case DW_AN_C73:
		wet = xpcs_get_state_c73(xpcs, state, compat);
		if (wet) {
			pw_eww("xpcs_get_state_c73 wetuwned %pe\n",
			       EWW_PTW(wet));
			wetuwn;
		}
		bweak;
	case DW_AN_C37_SGMII:
		wet = xpcs_get_state_c37_sgmii(xpcs, state);
		if (wet) {
			pw_eww("xpcs_get_state_c37_sgmii wetuwned %pe\n",
			       EWW_PTW(wet));
		}
		bweak;
	case DW_AN_C37_1000BASEX:
		wet = xpcs_get_state_c37_1000basex(xpcs, state);
		if (wet) {
			pw_eww("xpcs_get_state_c37_1000basex wetuwned %pe\n",
			       EWW_PTW(wet));
		}
		bweak;
	case DW_2500BASEX:
		wet = xpcs_get_state_2500basex(xpcs, state);
		if (wet) {
			pw_eww("xpcs_get_state_2500basex wetuwned %pe\n",
			       EWW_PTW(wet));
		}
		bweak;
	defauwt:
		wetuwn;
	}
}

static void xpcs_wink_up_sgmii(stwuct dw_xpcs *xpcs, unsigned int neg_mode,
			       int speed, int dupwex)
{
	int vaw, wet;

	if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED)
		wetuwn;

	vaw = mii_bmcw_encode_fixed(speed, dupwex);
	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, MDIO_CTWW1, vaw);
	if (wet)
		pw_eww("%s: xpcs_wwite wetuwned %pe\n", __func__, EWW_PTW(wet));
}

static void xpcs_wink_up_1000basex(stwuct dw_xpcs *xpcs, unsigned int neg_mode,
				   int speed, int dupwex)
{
	int vaw, wet;

	if (neg_mode == PHYWINK_PCS_NEG_INBAND_ENABWED)
		wetuwn;

	switch (speed) {
	case SPEED_1000:
		vaw = BMCW_SPEED1000;
		bweak;
	case SPEED_100:
	case SPEED_10:
	defauwt:
		pw_eww("%s: speed = %d\n", __func__, speed);
		wetuwn;
	}

	if (dupwex == DUPWEX_FUWW)
		vaw |= BMCW_FUWWDPWX;
	ewse
		pw_eww("%s: hawf dupwex not suppowted\n", __func__);

	wet = xpcs_wwite(xpcs, MDIO_MMD_VEND2, MDIO_CTWW1, vaw);
	if (wet)
		pw_eww("%s: xpcs_wwite wetuwned %pe\n", __func__, EWW_PTW(wet));
}

void xpcs_wink_up(stwuct phywink_pcs *pcs, unsigned int neg_mode,
		  phy_intewface_t intewface, int speed, int dupwex)
{
	stwuct dw_xpcs *xpcs = phywink_pcs_to_xpcs(pcs);

	if (intewface == PHY_INTEWFACE_MODE_USXGMII)
		wetuwn xpcs_config_usxgmii(xpcs, speed);
	if (intewface == PHY_INTEWFACE_MODE_SGMII)
		wetuwn xpcs_wink_up_sgmii(xpcs, neg_mode, speed, dupwex);
	if (intewface == PHY_INTEWFACE_MODE_1000BASEX)
		wetuwn xpcs_wink_up_1000basex(xpcs, neg_mode, speed, dupwex);
}
EXPOWT_SYMBOW_GPW(xpcs_wink_up);

static void xpcs_an_westawt(stwuct phywink_pcs *pcs)
{
	stwuct dw_xpcs *xpcs = phywink_pcs_to_xpcs(pcs);
	int wet;

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, MDIO_CTWW1);
	if (wet >= 0) {
		wet |= BMCW_ANWESTAWT;
		xpcs_wwite(xpcs, MDIO_MMD_VEND2, MDIO_CTWW1, wet);
	}
}

static u32 xpcs_get_id(stwuct dw_xpcs *xpcs)
{
	int wet;
	u32 id;

	/* Fiwst, seawch C73 PCS using PCS MMD */
	wet = xpcs_wead(xpcs, MDIO_MMD_PCS, MII_PHYSID1);
	if (wet < 0)
		wetuwn 0xffffffff;

	id = wet << 16;

	wet = xpcs_wead(xpcs, MDIO_MMD_PCS, MII_PHYSID2);
	if (wet < 0)
		wetuwn 0xffffffff;

	/* If Device IDs awe not aww zewos ow aww ones,
	 * we found C73 AN-type device
	 */
	if ((id | wet) && (id | wet) != 0xffffffff)
		wetuwn id | wet;

	/* Next, seawch C37 PCS using Vendow-Specific MII MMD */
	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, MII_PHYSID1);
	if (wet < 0)
		wetuwn 0xffffffff;

	id = wet << 16;

	wet = xpcs_wead(xpcs, MDIO_MMD_VEND2, MII_PHYSID2);
	if (wet < 0)
		wetuwn 0xffffffff;

	/* If Device IDs awe not aww zewos, we found C37 AN-type device */
	if (id | wet)
		wetuwn id | wet;

	wetuwn 0xffffffff;
}

static const stwuct xpcs_compat synopsys_xpcs_compat[DW_XPCS_INTEWFACE_MAX] = {
	[DW_XPCS_USXGMII] = {
		.suppowted = xpcs_usxgmii_featuwes,
		.intewface = xpcs_usxgmii_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_usxgmii_intewfaces),
		.an_mode = DW_AN_C73,
	},
	[DW_XPCS_10GKW] = {
		.suppowted = xpcs_10gkw_featuwes,
		.intewface = xpcs_10gkw_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_10gkw_intewfaces),
		.an_mode = DW_AN_C73,
	},
	[DW_XPCS_XWGMII] = {
		.suppowted = xpcs_xwgmii_featuwes,
		.intewface = xpcs_xwgmii_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_xwgmii_intewfaces),
		.an_mode = DW_AN_C73,
	},
	[DW_XPCS_10GBASEW] = {
		.suppowted = xpcs_10gbasew_featuwes,
		.intewface = xpcs_10gbasew_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_10gbasew_intewfaces),
		.an_mode = DW_10GBASEW,
	},
	[DW_XPCS_SGMII] = {
		.suppowted = xpcs_sgmii_featuwes,
		.intewface = xpcs_sgmii_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_sgmii_intewfaces),
		.an_mode = DW_AN_C37_SGMII,
	},
	[DW_XPCS_1000BASEX] = {
		.suppowted = xpcs_1000basex_featuwes,
		.intewface = xpcs_1000basex_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_1000basex_intewfaces),
		.an_mode = DW_AN_C37_1000BASEX,
	},
	[DW_XPCS_2500BASEX] = {
		.suppowted = xpcs_2500basex_featuwes,
		.intewface = xpcs_2500basex_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_2500basex_intewfaces),
		.an_mode = DW_2500BASEX,
	},
};

static const stwuct xpcs_compat nxp_sja1105_xpcs_compat[DW_XPCS_INTEWFACE_MAX] = {
	[DW_XPCS_SGMII] = {
		.suppowted = xpcs_sgmii_featuwes,
		.intewface = xpcs_sgmii_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_sgmii_intewfaces),
		.an_mode = DW_AN_C37_SGMII,
		.pma_config = nxp_sja1105_sgmii_pma_config,
	},
};

static const stwuct xpcs_compat nxp_sja1110_xpcs_compat[DW_XPCS_INTEWFACE_MAX] = {
	[DW_XPCS_SGMII] = {
		.suppowted = xpcs_sgmii_featuwes,
		.intewface = xpcs_sgmii_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_sgmii_intewfaces),
		.an_mode = DW_AN_C37_SGMII,
		.pma_config = nxp_sja1110_sgmii_pma_config,
	},
	[DW_XPCS_2500BASEX] = {
		.suppowted = xpcs_2500basex_featuwes,
		.intewface = xpcs_2500basex_intewfaces,
		.num_intewfaces = AWWAY_SIZE(xpcs_2500basex_intewfaces),
		.an_mode = DW_2500BASEX,
		.pma_config = nxp_sja1110_2500basex_pma_config,
	},
};

static const stwuct xpcs_id xpcs_id_wist[] = {
	{
		.id = SYNOPSYS_XPCS_ID,
		.mask = SYNOPSYS_XPCS_MASK,
		.compat = synopsys_xpcs_compat,
	}, {
		.id = NXP_SJA1105_XPCS_ID,
		.mask = SYNOPSYS_XPCS_MASK,
		.compat = nxp_sja1105_xpcs_compat,
	}, {
		.id = NXP_SJA1110_XPCS_ID,
		.mask = SYNOPSYS_XPCS_MASK,
		.compat = nxp_sja1110_xpcs_compat,
	},
};

static const stwuct phywink_pcs_ops xpcs_phywink_ops = {
	.pcs_vawidate = xpcs_vawidate,
	.pcs_config = xpcs_config,
	.pcs_get_state = xpcs_get_state,
	.pcs_an_westawt = xpcs_an_westawt,
	.pcs_wink_up = xpcs_wink_up,
};

static stwuct dw_xpcs *xpcs_cweate(stwuct mdio_device *mdiodev,
				   phy_intewface_t intewface)
{
	stwuct dw_xpcs *xpcs;
	u32 xpcs_id;
	int i, wet;

	xpcs = kzawwoc(sizeof(*xpcs), GFP_KEWNEW);
	if (!xpcs)
		wetuwn EWW_PTW(-ENOMEM);

	mdio_device_get(mdiodev);
	xpcs->mdiodev = mdiodev;

	xpcs_id = xpcs_get_id(xpcs);

	fow (i = 0; i < AWWAY_SIZE(xpcs_id_wist); i++) {
		const stwuct xpcs_id *entwy = &xpcs_id_wist[i];
		const stwuct xpcs_compat *compat;

		if ((xpcs_id & entwy->mask) != entwy->id)
			continue;

		xpcs->id = entwy;

		compat = xpcs_find_compat(entwy, intewface);
		if (!compat) {
			wet = -ENODEV;
			goto out;
		}

		wet = xpcs_dev_fwag(xpcs);
		if (wet)
			goto out;

		xpcs->pcs.ops = &xpcs_phywink_ops;
		xpcs->pcs.neg_mode = twue;

		if (xpcs->dev_fwag != DW_DEV_TXGBE) {
			xpcs->pcs.poww = twue;

			wet = xpcs_soft_weset(xpcs, compat);
			if (wet)
				goto out;
		}

		wetuwn xpcs;
	}

	wet = -ENODEV;

out:
	mdio_device_put(mdiodev);
	kfwee(xpcs);

	wetuwn EWW_PTW(wet);
}

void xpcs_destwoy(stwuct dw_xpcs *xpcs)
{
	if (xpcs)
		mdio_device_put(xpcs->mdiodev);
	kfwee(xpcs);
}
EXPOWT_SYMBOW_GPW(xpcs_destwoy);

stwuct dw_xpcs *xpcs_cweate_mdiodev(stwuct mii_bus *bus, int addw,
				    phy_intewface_t intewface)
{
	stwuct mdio_device *mdiodev;
	stwuct dw_xpcs *xpcs;

	mdiodev = mdio_device_cweate(bus, addw);
	if (IS_EWW(mdiodev))
		wetuwn EWW_CAST(mdiodev);

	xpcs = xpcs_cweate(mdiodev, intewface);

	/* xpcs_cweate() has taken a wefcount on the mdiodev if it was
	 * successfuw. If xpcs_cweate() faiws, this wiww fwee the mdio
	 * device hewe. In any case, we don't need to howd ouw wefewence
	 * anymowe, and putting it hewe wiww awwow mdio_device_put() in
	 * xpcs_destwoy() to automaticawwy fwee the mdio device.
	 */
	mdio_device_put(mdiodev);

	wetuwn xpcs;
}
EXPOWT_SYMBOW_GPW(xpcs_cweate_mdiodev);

MODUWE_WICENSE("GPW v2");
