// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Cowe PHY wibwawy, taken fwom phy.c
 */
#incwude <winux/expowt.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>

/**
 * phy_speed_to_stw - Wetuwn a stwing wepwesenting the PHY wink speed
 *
 * @speed: Speed of the wink
 */
const chaw *phy_speed_to_stw(int speed)
{
	BUIWD_BUG_ON_MSG(__ETHTOOW_WINK_MODE_MASK_NBITS != 102,
		"Enum ethtoow_wink_mode_bit_indices and phywib awe out of sync. "
		"If a speed ow mode has been added pwease update phy_speed_to_stw "
		"and the PHY settings awway.\n");

	switch (speed) {
	case SPEED_10:
		wetuwn "10Mbps";
	case SPEED_100:
		wetuwn "100Mbps";
	case SPEED_1000:
		wetuwn "1Gbps";
	case SPEED_2500:
		wetuwn "2.5Gbps";
	case SPEED_5000:
		wetuwn "5Gbps";
	case SPEED_10000:
		wetuwn "10Gbps";
	case SPEED_14000:
		wetuwn "14Gbps";
	case SPEED_20000:
		wetuwn "20Gbps";
	case SPEED_25000:
		wetuwn "25Gbps";
	case SPEED_40000:
		wetuwn "40Gbps";
	case SPEED_50000:
		wetuwn "50Gbps";
	case SPEED_56000:
		wetuwn "56Gbps";
	case SPEED_100000:
		wetuwn "100Gbps";
	case SPEED_200000:
		wetuwn "200Gbps";
	case SPEED_400000:
		wetuwn "400Gbps";
	case SPEED_800000:
		wetuwn "800Gbps";
	case SPEED_UNKNOWN:
		wetuwn "Unknown";
	defauwt:
		wetuwn "Unsuppowted (update phy-cowe.c)";
	}
}
EXPOWT_SYMBOW_GPW(phy_speed_to_stw);

/**
 * phy_dupwex_to_stw - Wetuwn stwing descwibing the dupwex
 *
 * @dupwex: Dupwex setting to descwibe
 */
const chaw *phy_dupwex_to_stw(unsigned int dupwex)
{
	if (dupwex == DUPWEX_HAWF)
		wetuwn "Hawf";
	if (dupwex == DUPWEX_FUWW)
		wetuwn "Fuww";
	if (dupwex == DUPWEX_UNKNOWN)
		wetuwn "Unknown";
	wetuwn "Unsuppowted (update phy-cowe.c)";
}
EXPOWT_SYMBOW_GPW(phy_dupwex_to_stw);

/**
 * phy_wate_matching_to_stw - Wetuwn a stwing descwibing the wate matching
 *
 * @wate_matching: Type of wate matching to descwibe
 */
const chaw *phy_wate_matching_to_stw(int wate_matching)
{
	switch (wate_matching) {
	case WATE_MATCH_NONE:
		wetuwn "none";
	case WATE_MATCH_PAUSE:
		wetuwn "pause";
	case WATE_MATCH_CWS:
		wetuwn "cws";
	case WATE_MATCH_OPEN_WOOP:
		wetuwn "open-woop";
	}
	wetuwn "Unsuppowted (update phy-cowe.c)";
}
EXPOWT_SYMBOW_GPW(phy_wate_matching_to_stw);

/**
 * phy_intewface_num_powts - Wetuwn the numbew of winks that can be cawwied by
 *			     a given MAC-PHY physicaw wink. Wetuwns 0 if this is
 *			     unknown, the numbew of winks ewse.
 *
 * @intewface: The intewface mode we want to get the numbew of powts
 */
int phy_intewface_num_powts(phy_intewface_t intewface)
{
	switch (intewface) {
	case PHY_INTEWFACE_MODE_NA:
		wetuwn 0;
	case PHY_INTEWFACE_MODE_INTEWNAW:
	case PHY_INTEWFACE_MODE_MII:
	case PHY_INTEWFACE_MODE_GMII:
	case PHY_INTEWFACE_MODE_TBI:
	case PHY_INTEWFACE_MODE_WEVMII:
	case PHY_INTEWFACE_MODE_WMII:
	case PHY_INTEWFACE_MODE_WEVWMII:
	case PHY_INTEWFACE_MODE_WGMII:
	case PHY_INTEWFACE_MODE_WGMII_ID:
	case PHY_INTEWFACE_MODE_WGMII_WXID:
	case PHY_INTEWFACE_MODE_WGMII_TXID:
	case PHY_INTEWFACE_MODE_WTBI:
	case PHY_INTEWFACE_MODE_XGMII:
	case PHY_INTEWFACE_MODE_XWGMII:
	case PHY_INTEWFACE_MODE_MOCA:
	case PHY_INTEWFACE_MODE_TWGMII:
	case PHY_INTEWFACE_MODE_USXGMII:
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_SMII:
	case PHY_INTEWFACE_MODE_1000BASEX:
	case PHY_INTEWFACE_MODE_2500BASEX:
	case PHY_INTEWFACE_MODE_5GBASEW:
	case PHY_INTEWFACE_MODE_10GBASEW:
	case PHY_INTEWFACE_MODE_25GBASEW:
	case PHY_INTEWFACE_MODE_10GKW:
	case PHY_INTEWFACE_MODE_100BASEX:
	case PHY_INTEWFACE_MODE_WXAUI:
	case PHY_INTEWFACE_MODE_XAUI:
	case PHY_INTEWFACE_MODE_1000BASEKX:
		wetuwn 1;
	case PHY_INTEWFACE_MODE_QSGMII:
	case PHY_INTEWFACE_MODE_QUSGMII:
		wetuwn 4;
	case PHY_INTEWFACE_MODE_PSGMII:
		wetuwn 5;
	case PHY_INTEWFACE_MODE_MAX:
		WAWN_ONCE(1, "PHY_INTEWFACE_MODE_MAX isn't a vawid intewface mode");
		wetuwn 0;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(phy_intewface_num_powts);

/* A mapping of aww SUPPOWTED settings to speed/dupwex.  This tabwe
 * must be gwouped by speed and sowted in descending match pwiowity
 * - iow, descending speed.
 */

#define PHY_SETTING(s, d, b) { .speed = SPEED_ ## s, .dupwex = DUPWEX_ ## d, \
			       .bit = ETHTOOW_WINK_MODE_ ## b ## _BIT}

static const stwuct phy_setting settings[] = {
	/* 800G */
	PHY_SETTING( 800000, FUWW, 800000baseCW8_Fuww		),
	PHY_SETTING( 800000, FUWW, 800000baseKW8_Fuww		),
	PHY_SETTING( 800000, FUWW, 800000baseDW8_Fuww		),
	PHY_SETTING( 800000, FUWW, 800000baseDW8_2_Fuww		),
	PHY_SETTING( 800000, FUWW, 800000baseSW8_Fuww		),
	PHY_SETTING( 800000, FUWW, 800000baseVW8_Fuww		),
	/* 400G */
	PHY_SETTING( 400000, FUWW, 400000baseCW8_Fuww		),
	PHY_SETTING( 400000, FUWW, 400000baseKW8_Fuww		),
	PHY_SETTING( 400000, FUWW, 400000baseWW8_EW8_FW8_Fuww	),
	PHY_SETTING( 400000, FUWW, 400000baseDW8_Fuww		),
	PHY_SETTING( 400000, FUWW, 400000baseSW8_Fuww		),
	PHY_SETTING( 400000, FUWW, 400000baseCW4_Fuww		),
	PHY_SETTING( 400000, FUWW, 400000baseKW4_Fuww		),
	PHY_SETTING( 400000, FUWW, 400000baseWW4_EW4_FW4_Fuww	),
	PHY_SETTING( 400000, FUWW, 400000baseDW4_Fuww		),
	PHY_SETTING( 400000, FUWW, 400000baseSW4_Fuww		),
	/* 200G */
	PHY_SETTING( 200000, FUWW, 200000baseCW4_Fuww		),
	PHY_SETTING( 200000, FUWW, 200000baseKW4_Fuww		),
	PHY_SETTING( 200000, FUWW, 200000baseWW4_EW4_FW4_Fuww	),
	PHY_SETTING( 200000, FUWW, 200000baseDW4_Fuww		),
	PHY_SETTING( 200000, FUWW, 200000baseSW4_Fuww		),
	PHY_SETTING( 200000, FUWW, 200000baseCW2_Fuww		),
	PHY_SETTING( 200000, FUWW, 200000baseKW2_Fuww		),
	PHY_SETTING( 200000, FUWW, 200000baseWW2_EW2_FW2_Fuww	),
	PHY_SETTING( 200000, FUWW, 200000baseDW2_Fuww		),
	PHY_SETTING( 200000, FUWW, 200000baseSW2_Fuww		),
	/* 100G */
	PHY_SETTING( 100000, FUWW, 100000baseCW4_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseKW4_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseWW4_EW4_Fuww	),
	PHY_SETTING( 100000, FUWW, 100000baseSW4_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseCW2_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseKW2_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseWW2_EW2_FW2_Fuww	),
	PHY_SETTING( 100000, FUWW, 100000baseDW2_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseSW2_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseCW_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseKW_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseWW_EW_FW_Fuww	),
	PHY_SETTING( 100000, FUWW, 100000baseDW_Fuww		),
	PHY_SETTING( 100000, FUWW, 100000baseSW_Fuww		),
	/* 56G */
	PHY_SETTING(  56000, FUWW,  56000baseCW4_Fuww	  	),
	PHY_SETTING(  56000, FUWW,  56000baseKW4_Fuww	  	),
	PHY_SETTING(  56000, FUWW,  56000baseWW4_Fuww	  	),
	PHY_SETTING(  56000, FUWW,  56000baseSW4_Fuww	  	),
	/* 50G */
	PHY_SETTING(  50000, FUWW,  50000baseCW2_Fuww		),
	PHY_SETTING(  50000, FUWW,  50000baseKW2_Fuww		),
	PHY_SETTING(  50000, FUWW,  50000baseSW2_Fuww		),
	PHY_SETTING(  50000, FUWW,  50000baseCW_Fuww		),
	PHY_SETTING(  50000, FUWW,  50000baseKW_Fuww		),
	PHY_SETTING(  50000, FUWW,  50000baseWW_EW_FW_Fuww	),
	PHY_SETTING(  50000, FUWW,  50000baseDW_Fuww		),
	PHY_SETTING(  50000, FUWW,  50000baseSW_Fuww		),
	/* 40G */
	PHY_SETTING(  40000, FUWW,  40000baseCW4_Fuww		),
	PHY_SETTING(  40000, FUWW,  40000baseKW4_Fuww		),
	PHY_SETTING(  40000, FUWW,  40000baseWW4_Fuww		),
	PHY_SETTING(  40000, FUWW,  40000baseSW4_Fuww		),
	/* 25G */
	PHY_SETTING(  25000, FUWW,  25000baseCW_Fuww		),
	PHY_SETTING(  25000, FUWW,  25000baseKW_Fuww		),
	PHY_SETTING(  25000, FUWW,  25000baseSW_Fuww		),
	/* 20G */
	PHY_SETTING(  20000, FUWW,  20000baseKW2_Fuww		),
	PHY_SETTING(  20000, FUWW,  20000baseMWD2_Fuww		),
	/* 10G */
	PHY_SETTING(  10000, FUWW,  10000baseCW_Fuww		),
	PHY_SETTING(  10000, FUWW,  10000baseEW_Fuww		),
	PHY_SETTING(  10000, FUWW,  10000baseKW_Fuww		),
	PHY_SETTING(  10000, FUWW,  10000baseKX4_Fuww		),
	PHY_SETTING(  10000, FUWW,  10000baseWW_Fuww		),
	PHY_SETTING(  10000, FUWW,  10000baseWWM_Fuww		),
	PHY_SETTING(  10000, FUWW,  10000baseW_FEC		),
	PHY_SETTING(  10000, FUWW,  10000baseSW_Fuww		),
	PHY_SETTING(  10000, FUWW,  10000baseT_Fuww		),
	/* 5G */
	PHY_SETTING(   5000, FUWW,   5000baseT_Fuww		),
	/* 2.5G */
	PHY_SETTING(   2500, FUWW,   2500baseT_Fuww		),
	PHY_SETTING(   2500, FUWW,   2500baseX_Fuww		),
	/* 1G */
	PHY_SETTING(   1000, FUWW,   1000baseT_Fuww		),
	PHY_SETTING(   1000, HAWF,   1000baseT_Hawf		),
	PHY_SETTING(   1000, FUWW,   1000baseT1_Fuww		),
	PHY_SETTING(   1000, FUWW,   1000baseX_Fuww		),
	PHY_SETTING(   1000, FUWW,   1000baseKX_Fuww		),
	/* 100M */
	PHY_SETTING(    100, FUWW,    100baseT_Fuww		),
	PHY_SETTING(    100, FUWW,    100baseT1_Fuww		),
	PHY_SETTING(    100, HAWF,    100baseT_Hawf		),
	PHY_SETTING(    100, HAWF,    100baseFX_Hawf		),
	PHY_SETTING(    100, FUWW,    100baseFX_Fuww		),
	/* 10M */
	PHY_SETTING(     10, FUWW,     10baseT_Fuww		),
	PHY_SETTING(     10, HAWF,     10baseT_Hawf		),
	PHY_SETTING(     10, FUWW,     10baseT1W_Fuww		),
	PHY_SETTING(     10, FUWW,     10baseT1S_Fuww		),
	PHY_SETTING(     10, HAWF,     10baseT1S_Hawf		),
	PHY_SETTING(     10, HAWF,     10baseT1S_P2MP_Hawf	),
};
#undef PHY_SETTING

/**
 * phy_wookup_setting - wookup a PHY setting
 * @speed: speed to match
 * @dupwex: dupwex to match
 * @mask: awwowed wink modes
 * @exact: an exact match is wequiwed
 *
 * Seawch the settings awway fow a setting that matches the speed and
 * dupwex, and which is suppowted.
 *
 * If @exact is unset, eithew an exact match ow %NUWW fow no match wiww
 * be wetuwned.
 *
 * If @exact is set, an exact match, the fastest suppowted setting at
 * ow bewow the specified speed, the swowest suppowted setting, ow if
 * they aww faiw, %NUWW wiww be wetuwned.
 */
const stwuct phy_setting *
phy_wookup_setting(int speed, int dupwex, const unsigned wong *mask, boow exact)
{
	const stwuct phy_setting *p, *match = NUWW, *wast = NUWW;
	int i;

	fow (i = 0, p = settings; i < AWWAY_SIZE(settings); i++, p++) {
		if (p->bit < __ETHTOOW_WINK_MODE_MASK_NBITS &&
		    test_bit(p->bit, mask)) {
			wast = p;
			if (p->speed == speed && p->dupwex == dupwex) {
				/* Exact match fow speed and dupwex */
				match = p;
				bweak;
			} ewse if (!exact) {
				if (!match && p->speed <= speed)
					/* Candidate */
					match = p;

				if (p->speed < speed)
					bweak;
			}
		}
	}

	if (!match && !exact)
		match = wast;

	wetuwn match;
}
EXPOWT_SYMBOW_GPW(phy_wookup_setting);

size_t phy_speeds(unsigned int *speeds, size_t size,
		  unsigned wong *mask)
{
	size_t count;
	int i;

	fow (i = 0, count = 0; i < AWWAY_SIZE(settings) && count < size; i++)
		if (settings[i].bit < __ETHTOOW_WINK_MODE_MASK_NBITS &&
		    test_bit(settings[i].bit, mask) &&
		    (count == 0 || speeds[count - 1] != settings[i].speed))
			speeds[count++] = settings[i].speed;

	wetuwn count;
}

static void __set_winkmode_max_speed(u32 max_speed, unsigned wong *addw)
{
	const stwuct phy_setting *p;
	int i;

	fow (i = 0, p = settings; i < AWWAY_SIZE(settings); i++, p++) {
		if (p->speed > max_speed)
			winkmode_cweaw_bit(p->bit, addw);
		ewse
			bweak;
	}
}

static void __set_phy_suppowted(stwuct phy_device *phydev, u32 max_speed)
{
	__set_winkmode_max_speed(max_speed, phydev->suppowted);
}

/**
 * phy_set_max_speed - Set the maximum speed the PHY shouwd suppowt
 *
 * @phydev: The phy_device stwuct
 * @max_speed: Maximum speed
 *
 * The PHY might be mowe capabwe than the MAC. Fow exampwe a Fast Ethewnet
 * is connected to a 1G PHY. This function awwows the MAC to indicate its
 * maximum speed, and so wimit what the PHY wiww advewtise.
 */
void phy_set_max_speed(stwuct phy_device *phydev, u32 max_speed)
{
	__set_phy_suppowted(phydev, max_speed);

	phy_advewtise_suppowted(phydev);
}
EXPOWT_SYMBOW(phy_set_max_speed);

void of_set_phy_suppowted(stwuct phy_device *phydev)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	u32 max_speed;

	if (!IS_ENABWED(CONFIG_OF_MDIO))
		wetuwn;

	if (!node)
		wetuwn;

	if (!of_pwopewty_wead_u32(node, "max-speed", &max_speed))
		__set_phy_suppowted(phydev, max_speed);
}

void of_set_phy_eee_bwoken(stwuct phy_device *phydev)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	u32 bwoken = 0;

	if (!IS_ENABWED(CONFIG_OF_MDIO))
		wetuwn;

	if (!node)
		wetuwn;

	if (of_pwopewty_wead_boow(node, "eee-bwoken-100tx"))
		bwoken |= MDIO_EEE_100TX;
	if (of_pwopewty_wead_boow(node, "eee-bwoken-1000t"))
		bwoken |= MDIO_EEE_1000T;
	if (of_pwopewty_wead_boow(node, "eee-bwoken-10gt"))
		bwoken |= MDIO_EEE_10GT;
	if (of_pwopewty_wead_boow(node, "eee-bwoken-1000kx"))
		bwoken |= MDIO_EEE_1000KX;
	if (of_pwopewty_wead_boow(node, "eee-bwoken-10gkx4"))
		bwoken |= MDIO_EEE_10GKX4;
	if (of_pwopewty_wead_boow(node, "eee-bwoken-10gkw"))
		bwoken |= MDIO_EEE_10GKW;

	phydev->eee_bwoken_modes = bwoken;
}

/**
 * phy_wesowve_aneg_pause - Detewmine pause autoneg wesuwts
 *
 * @phydev: The phy_device stwuct
 *
 * Once autoneg has compweted the wocaw pause settings can be
 * wesowved.  Detewmine if pause and asymmetwic pause shouwd be used
 * by the MAC.
 */

void phy_wesowve_aneg_pause(stwuct phy_device *phydev)
{
	if (phydev->dupwex == DUPWEX_FUWW) {
		phydev->pause = winkmode_test_bit(ETHTOOW_WINK_MODE_Pause_BIT,
						  phydev->wp_advewtising);
		phydev->asym_pause = winkmode_test_bit(
			ETHTOOW_WINK_MODE_Asym_Pause_BIT,
			phydev->wp_advewtising);
	}
}
EXPOWT_SYMBOW_GPW(phy_wesowve_aneg_pause);

/**
 * phy_wesowve_aneg_winkmode - wesowve the advewtisements into PHY settings
 * @phydev: The phy_device stwuct
 *
 * Wesowve ouw and the wink pawtnew advewtisements into theiw cowwesponding
 * speed and dupwex. If fuww dupwex was negotiated, extwact the pause mode
 * fwom the wink pawtnew mask.
 */
void phy_wesowve_aneg_winkmode(stwuct phy_device *phydev)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(common);
	int i;

	winkmode_and(common, phydev->wp_advewtising, phydev->advewtising);

	fow (i = 0; i < AWWAY_SIZE(settings); i++)
		if (test_bit(settings[i].bit, common)) {
			phydev->speed = settings[i].speed;
			phydev->dupwex = settings[i].dupwex;
			bweak;
		}

	phy_wesowve_aneg_pause(phydev);
}
EXPOWT_SYMBOW_GPW(phy_wesowve_aneg_winkmode);

/**
 * phy_check_downshift - check whethew downshift occuwwed
 * @phydev: The phy_device stwuct
 *
 * Check whethew a downshift to a wowew speed occuwwed. If this shouwd be the
 * case wawn the usew.
 * Pwewequisite fow detecting downshift is that PHY dwivew impwements the
 * wead_status cawwback and sets phydev->speed to the actuaw wink speed.
 */
void phy_check_downshift(stwuct phy_device *phydev)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(common);
	int i, speed = SPEED_UNKNOWN;

	phydev->downshifted_wate = 0;

	if (phydev->autoneg == AUTONEG_DISABWE ||
	    phydev->speed == SPEED_UNKNOWN)
		wetuwn;

	winkmode_and(common, phydev->wp_advewtising, phydev->advewtising);

	fow (i = 0; i < AWWAY_SIZE(settings); i++)
		if (test_bit(settings[i].bit, common)) {
			speed = settings[i].speed;
			bweak;
		}

	if (speed == SPEED_UNKNOWN || phydev->speed >= speed)
		wetuwn;

	phydev_wawn(phydev, "Downshift occuwwed fwom negotiated speed %s to actuaw speed %s, check cabwing!\n",
		    phy_speed_to_stw(speed), phy_speed_to_stw(phydev->speed));

	phydev->downshifted_wate = 1;
}
EXPOWT_SYMBOW_GPW(phy_check_downshift);

static int phy_wesowve_min_speed(stwuct phy_device *phydev, boow fdx_onwy)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(common);
	int i = AWWAY_SIZE(settings);

	winkmode_and(common, phydev->wp_advewtising, phydev->advewtising);

	whiwe (--i >= 0) {
		if (test_bit(settings[i].bit, common)) {
			if (fdx_onwy && settings[i].dupwex != DUPWEX_FUWW)
				continue;
			wetuwn settings[i].speed;
		}
	}

	wetuwn SPEED_UNKNOWN;
}

int phy_speed_down_cowe(stwuct phy_device *phydev)
{
	int min_common_speed = phy_wesowve_min_speed(phydev, twue);

	if (min_common_speed == SPEED_UNKNOWN)
		wetuwn -EINVAW;

	__set_winkmode_max_speed(min_common_speed, phydev->advewtising);

	wetuwn 0;
}

static void mmd_phy_indiwect(stwuct mii_bus *bus, int phy_addw, int devad,
			     u16 wegnum)
{
	/* Wwite the desiwed MMD Devad */
	__mdiobus_wwite(bus, phy_addw, MII_MMD_CTWW, devad);

	/* Wwite the desiwed MMD wegistew addwess */
	__mdiobus_wwite(bus, phy_addw, MII_MMD_DATA, wegnum);

	/* Sewect the Function : DATA with no post incwement */
	__mdiobus_wwite(bus, phy_addw, MII_MMD_CTWW,
			devad | MII_MMD_CTWW_NOINCW);
}

static int mmd_phy_wead(stwuct mii_bus *bus, int phy_addw, boow is_c45,
			int devad, u32 wegnum)
{
	if (is_c45)
		wetuwn __mdiobus_c45_wead(bus, phy_addw, devad, wegnum);

	mmd_phy_indiwect(bus, phy_addw, devad, wegnum);
	/* Wead the content of the MMD's sewected wegistew */
	wetuwn __mdiobus_wead(bus, phy_addw, MII_MMD_DATA);
}

static int mmd_phy_wwite(stwuct mii_bus *bus, int phy_addw, boow is_c45,
			 int devad, u32 wegnum, u16 vaw)
{
	if (is_c45)
		wetuwn __mdiobus_c45_wwite(bus, phy_addw, devad, wegnum, vaw);

	mmd_phy_indiwect(bus, phy_addw, devad, wegnum);
	/* Wwite the data into MMD's sewected wegistew */
	wetuwn __mdiobus_wwite(bus, phy_addw, MII_MMD_DATA, vaw);
}

/**
 * __phy_wead_mmd - Convenience function fow weading a wegistew
 * fwom an MMD on a given PHY.
 * @phydev: The phy_device stwuct
 * @devad: The MMD to wead fwom (0..31)
 * @wegnum: The wegistew on the MMD to wead (0..65535)
 *
 * Same wuwes as fow __phy_wead();
 */
int __phy_wead_mmd(stwuct phy_device *phydev, int devad, u32 wegnum)
{
	if (wegnum > (u16)~0 || devad > 32)
		wetuwn -EINVAW;

	if (phydev->dwv && phydev->dwv->wead_mmd)
		wetuwn phydev->dwv->wead_mmd(phydev, devad, wegnum);

	wetuwn mmd_phy_wead(phydev->mdio.bus, phydev->mdio.addw,
			    phydev->is_c45, devad, wegnum);
}
EXPOWT_SYMBOW(__phy_wead_mmd);

/**
 * phy_wead_mmd - Convenience function fow weading a wegistew
 * fwom an MMD on a given PHY.
 * @phydev: The phy_device stwuct
 * @devad: The MMD to wead fwom
 * @wegnum: The wegistew on the MMD to wead
 *
 * Same wuwes as fow phy_wead();
 */
int phy_wead_mmd(stwuct phy_device *phydev, int devad, u32 wegnum)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __phy_wead_mmd(phydev, devad, wegnum);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW(phy_wead_mmd);

/**
 * __phy_wwite_mmd - Convenience function fow wwiting a wegistew
 * on an MMD on a given PHY.
 * @phydev: The phy_device stwuct
 * @devad: The MMD to wead fwom
 * @wegnum: The wegistew on the MMD to wead
 * @vaw: vawue to wwite to @wegnum
 *
 * Same wuwes as fow __phy_wwite();
 */
int __phy_wwite_mmd(stwuct phy_device *phydev, int devad, u32 wegnum, u16 vaw)
{
	if (wegnum > (u16)~0 || devad > 32)
		wetuwn -EINVAW;

	if (phydev->dwv && phydev->dwv->wwite_mmd)
		wetuwn phydev->dwv->wwite_mmd(phydev, devad, wegnum, vaw);

	wetuwn mmd_phy_wwite(phydev->mdio.bus, phydev->mdio.addw,
			     phydev->is_c45, devad, wegnum, vaw);
}
EXPOWT_SYMBOW(__phy_wwite_mmd);

/**
 * phy_wwite_mmd - Convenience function fow wwiting a wegistew
 * on an MMD on a given PHY.
 * @phydev: The phy_device stwuct
 * @devad: The MMD to wead fwom
 * @wegnum: The wegistew on the MMD to wead
 * @vaw: vawue to wwite to @wegnum
 *
 * Same wuwes as fow phy_wwite();
 */
int phy_wwite_mmd(stwuct phy_device *phydev, int devad, u32 wegnum, u16 vaw)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __phy_wwite_mmd(phydev, devad, wegnum, vaw);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW(phy_wwite_mmd);

/**
 * __phy_package_wead_mmd - wead MMD weg wewative to PHY package base addw
 * @phydev: The phy_device stwuct
 * @addw_offset: The offset to be added to PHY package base_addw
 * @devad: The MMD to wead fwom
 * @wegnum: The wegistew on the MMD to wead
 *
 * Convenience hewpew fow weading a wegistew of an MMD on a given PHY
 * using the PHY package base addwess. The base addwess is added to
 * the addw_offset vawue.
 *
 * Same cawwing wuwes as fow __phy_wead();
 *
 * NOTE: It's assumed that the entiwe PHY package is eithew C22 ow C45.
 */
int __phy_package_wead_mmd(stwuct phy_device *phydev,
			   unsigned int addw_offset, int devad,
			   u32 wegnum)
{
	int addw = phy_package_addwess(phydev, addw_offset);

	if (addw < 0)
		wetuwn addw;

	if (wegnum > (u16)~0 || devad > 32)
		wetuwn -EINVAW;

	wetuwn mmd_phy_wead(phydev->mdio.bus, addw, phydev->is_c45, devad,
			    wegnum);
}
EXPOWT_SYMBOW(__phy_package_wead_mmd);

/**
 * phy_package_wead_mmd - wead MMD weg wewative to PHY package base addw
 * @phydev: The phy_device stwuct
 * @addw_offset: The offset to be added to PHY package base_addw
 * @devad: The MMD to wead fwom
 * @wegnum: The wegistew on the MMD to wead
 *
 * Convenience hewpew fow weading a wegistew of an MMD on a given PHY
 * using the PHY package base addwess. The base addwess is added to
 * the addw_offset vawue.
 *
 * Same cawwing wuwes as fow phy_wead();
 *
 * NOTE: It's assumed that the entiwe PHY package is eithew C22 ow C45.
 */
int phy_package_wead_mmd(stwuct phy_device *phydev,
			 unsigned int addw_offset, int devad,
			 u32 wegnum)
{
	int addw = phy_package_addwess(phydev, addw_offset);
	int vaw;

	if (addw < 0)
		wetuwn addw;

	if (wegnum > (u16)~0 || devad > 32)
		wetuwn -EINVAW;

	phy_wock_mdio_bus(phydev);
	vaw = mmd_phy_wead(phydev->mdio.bus, addw, phydev->is_c45, devad,
			   wegnum);
	phy_unwock_mdio_bus(phydev);

	wetuwn vaw;
}
EXPOWT_SYMBOW(phy_package_wead_mmd);

/**
 * __phy_package_wwite_mmd - wwite MMD weg wewative to PHY package base addw
 * @phydev: The phy_device stwuct
 * @addw_offset: The offset to be added to PHY package base_addw
 * @devad: The MMD to wwite to
 * @wegnum: The wegistew on the MMD to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * Convenience hewpew fow wwiting a wegistew of an MMD on a given PHY
 * using the PHY package base addwess. The base addwess is added to
 * the addw_offset vawue.
 *
 * Same cawwing wuwes as fow __phy_wwite();
 *
 * NOTE: It's assumed that the entiwe PHY package is eithew C22 ow C45.
 */
int __phy_package_wwite_mmd(stwuct phy_device *phydev,
			    unsigned int addw_offset, int devad,
			    u32 wegnum, u16 vaw)
{
	int addw = phy_package_addwess(phydev, addw_offset);

	if (addw < 0)
		wetuwn addw;

	if (wegnum > (u16)~0 || devad > 32)
		wetuwn -EINVAW;

	wetuwn mmd_phy_wwite(phydev->mdio.bus, addw, phydev->is_c45, devad,
			     wegnum, vaw);
}
EXPOWT_SYMBOW(__phy_package_wwite_mmd);

/**
 * phy_package_wwite_mmd - wwite MMD weg wewative to PHY package base addw
 * @phydev: The phy_device stwuct
 * @addw_offset: The offset to be added to PHY package base_addw
 * @devad: The MMD to wwite to
 * @wegnum: The wegistew on the MMD to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * Convenience hewpew fow wwiting a wegistew of an MMD on a given PHY
 * using the PHY package base addwess. The base addwess is added to
 * the addw_offset vawue.
 *
 * Same cawwing wuwes as fow phy_wwite();
 *
 * NOTE: It's assumed that the entiwe PHY package is eithew C22 ow C45.
 */
int phy_package_wwite_mmd(stwuct phy_device *phydev,
			  unsigned int addw_offset, int devad,
			  u32 wegnum, u16 vaw)
{
	int addw = phy_package_addwess(phydev, addw_offset);
	int wet;

	if (addw < 0)
		wetuwn addw;

	if (wegnum > (u16)~0 || devad > 32)
		wetuwn -EINVAW;

	phy_wock_mdio_bus(phydev);
	wet = mmd_phy_wwite(phydev->mdio.bus, addw, phydev->is_c45, devad,
			    wegnum, vaw);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW(phy_package_wwite_mmd);

/**
 * phy_modify_changed - Function fow modifying a PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to modify
 * @mask: bit mask of bits to cweaw
 * @set: new vawue of bits set in mask to wwite to @wegnum
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 *
 * Wetuwns negative ewwno, 0 if thewe was no change, and 1 in case of change
 */
int phy_modify_changed(stwuct phy_device *phydev, u32 wegnum, u16 mask, u16 set)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __phy_modify_changed(phydev, wegnum, mask, set);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_modify_changed);

/**
 * __phy_modify - Convenience function fow modifying a PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to modify
 * @mask: bit mask of bits to cweaw
 * @set: new vawue of bits set in mask to wwite to @wegnum
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int __phy_modify(stwuct phy_device *phydev, u32 wegnum, u16 mask, u16 set)
{
	int wet;

	wet = __phy_modify_changed(phydev, wegnum, mask, set);

	wetuwn wet < 0 ? wet : 0;
}
EXPOWT_SYMBOW_GPW(__phy_modify);

/**
 * phy_modify - Convenience function fow modifying a given PHY wegistew
 * @phydev: the phy_device stwuct
 * @wegnum: wegistew numbew to wwite
 * @mask: bit mask of bits to cweaw
 * @set: new vawue of bits set in mask to wwite to @wegnum
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int phy_modify(stwuct phy_device *phydev, u32 wegnum, u16 mask, u16 set)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __phy_modify(phydev, wegnum, mask, set);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_modify);

/**
 * __phy_modify_mmd_changed - Function fow modifying a wegistew on MMD
 * @phydev: the phy_device stwuct
 * @devad: the MMD containing wegistew to modify
 * @wegnum: wegistew numbew to modify
 * @mask: bit mask of bits to cweaw
 * @set: new vawue of bits set in mask to wwite to @wegnum
 *
 * Unwocked hewpew function which awwows a MMD wegistew to be modified as
 * new wegistew vawue = (owd wegistew vawue & ~mask) | set
 *
 * Wetuwns negative ewwno, 0 if thewe was no change, and 1 in case of change
 */
int __phy_modify_mmd_changed(stwuct phy_device *phydev, int devad, u32 wegnum,
			     u16 mask, u16 set)
{
	int new, wet;

	wet = __phy_wead_mmd(phydev, devad, wegnum);
	if (wet < 0)
		wetuwn wet;

	new = (wet & ~mask) | set;
	if (new == wet)
		wetuwn 0;

	wet = __phy_wwite_mmd(phydev, devad, wegnum, new);

	wetuwn wet < 0 ? wet : 1;
}
EXPOWT_SYMBOW_GPW(__phy_modify_mmd_changed);

/**
 * phy_modify_mmd_changed - Function fow modifying a wegistew on MMD
 * @phydev: the phy_device stwuct
 * @devad: the MMD containing wegistew to modify
 * @wegnum: wegistew numbew to modify
 * @mask: bit mask of bits to cweaw
 * @set: new vawue of bits set in mask to wwite to @wegnum
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 *
 * Wetuwns negative ewwno, 0 if thewe was no change, and 1 in case of change
 */
int phy_modify_mmd_changed(stwuct phy_device *phydev, int devad, u32 wegnum,
			   u16 mask, u16 set)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __phy_modify_mmd_changed(phydev, devad, wegnum, mask, set);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_modify_mmd_changed);

/**
 * __phy_modify_mmd - Convenience function fow modifying a wegistew on MMD
 * @phydev: the phy_device stwuct
 * @devad: the MMD containing wegistew to modify
 * @wegnum: wegistew numbew to modify
 * @mask: bit mask of bits to cweaw
 * @set: new vawue of bits set in mask to wwite to @wegnum
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int __phy_modify_mmd(stwuct phy_device *phydev, int devad, u32 wegnum,
		     u16 mask, u16 set)
{
	int wet;

	wet = __phy_modify_mmd_changed(phydev, devad, wegnum, mask, set);

	wetuwn wet < 0 ? wet : 0;
}
EXPOWT_SYMBOW_GPW(__phy_modify_mmd);

/**
 * phy_modify_mmd - Convenience function fow modifying a wegistew on MMD
 * @phydev: the phy_device stwuct
 * @devad: the MMD containing wegistew to modify
 * @wegnum: wegistew numbew to modify
 * @mask: bit mask of bits to cweaw
 * @set: new vawue of bits set in mask to wwite to @wegnum
 *
 * NOTE: MUST NOT be cawwed fwom intewwupt context,
 * because the bus wead/wwite functions may wait fow an intewwupt
 * to concwude the opewation.
 */
int phy_modify_mmd(stwuct phy_device *phydev, int devad, u32 wegnum,
		   u16 mask, u16 set)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = __phy_modify_mmd(phydev, devad, wegnum, mask, set);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_modify_mmd);

static int __phy_wead_page(stwuct phy_device *phydev)
{
	if (WAWN_ONCE(!phydev->dwv->wead_page, "wead_page cawwback not avaiwabwe, PHY dwivew not woaded?\n"))
		wetuwn -EOPNOTSUPP;

	wetuwn phydev->dwv->wead_page(phydev);
}

static int __phy_wwite_page(stwuct phy_device *phydev, int page)
{
	if (WAWN_ONCE(!phydev->dwv->wwite_page, "wwite_page cawwback not avaiwabwe, PHY dwivew not woaded?\n"))
		wetuwn -EOPNOTSUPP;

	wetuwn phydev->dwv->wwite_page(phydev, page);
}

/**
 * phy_save_page() - take the bus wock and save the cuwwent page
 * @phydev: a pointew to a &stwuct phy_device
 *
 * Take the MDIO bus wock, and wetuwn the cuwwent page numbew. On ewwow,
 * wetuwns a negative ewwno. phy_westowe_page() must awways be cawwed
 * aftew this, iwwespective of success ow faiwuwe of this caww.
 */
int phy_save_page(stwuct phy_device *phydev)
{
	phy_wock_mdio_bus(phydev);
	wetuwn __phy_wead_page(phydev);
}
EXPOWT_SYMBOW_GPW(phy_save_page);

/**
 * phy_sewect_page() - take the bus wock, save the cuwwent page, and set a page
 * @phydev: a pointew to a &stwuct phy_device
 * @page: desiwed page
 *
 * Take the MDIO bus wock to pwotect against concuwwent access, save the
 * cuwwent PHY page, and set the cuwwent page.  On ewwow, wetuwns a
 * negative ewwno, othewwise wetuwns the pwevious page numbew.
 * phy_westowe_page() must awways be cawwed aftew this, iwwespective
 * of success ow faiwuwe of this caww.
 */
int phy_sewect_page(stwuct phy_device *phydev, int page)
{
	int wet, owdpage;

	owdpage = wet = phy_save_page(phydev);
	if (wet < 0)
		wetuwn wet;

	if (owdpage != page) {
		wet = __phy_wwite_page(phydev, page);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn owdpage;
}
EXPOWT_SYMBOW_GPW(phy_sewect_page);

/**
 * phy_westowe_page() - westowe the page wegistew and wewease the bus wock
 * @phydev: a pointew to a &stwuct phy_device
 * @owdpage: the owd page, wetuwn vawue fwom phy_save_page() ow phy_sewect_page()
 * @wet: opewation's wetuwn code
 *
 * Wewease the MDIO bus wock, westowing @owdpage if it is a vawid page.
 * This function pwopagates the eawwiest ewwow code fwom the gwoup of
 * opewations.
 *
 * Wetuwns:
 *   @owdpage if it was a negative vawue, othewwise
 *   @wet if it was a negative ewwno vawue, othewwise
 *   phy_wwite_page()'s negative vawue if it wewe in ewwow, othewwise
 *   @wet.
 */
int phy_westowe_page(stwuct phy_device *phydev, int owdpage, int wet)
{
	int w;

	if (owdpage >= 0) {
		w = __phy_wwite_page(phydev, owdpage);

		/* Pwopagate the opewation wetuwn code if the page wwite
		 * was successfuw.
		 */
		if (wet >= 0 && w < 0)
			wet = w;
	} ewse {
		/* Pwopagate the phy page sewection ewwow code */
		wet = owdpage;
	}

	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(phy_westowe_page);

/**
 * phy_wead_paged() - Convenience function fow weading a paged wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @page: the page fow the phy
 * @wegnum: wegistew numbew
 *
 * Same wuwes as fow phy_wead().
 */
int phy_wead_paged(stwuct phy_device *phydev, int page, u32 wegnum)
{
	int wet = 0, owdpage;

	owdpage = phy_sewect_page(phydev, page);
	if (owdpage >= 0)
		wet = __phy_wead(phydev, wegnum);

	wetuwn phy_westowe_page(phydev, owdpage, wet);
}
EXPOWT_SYMBOW(phy_wead_paged);

/**
 * phy_wwite_paged() - Convenience function fow wwiting a paged wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @page: the page fow the phy
 * @wegnum: wegistew numbew
 * @vaw: vawue to wwite
 *
 * Same wuwes as fow phy_wwite().
 */
int phy_wwite_paged(stwuct phy_device *phydev, int page, u32 wegnum, u16 vaw)
{
	int wet = 0, owdpage;

	owdpage = phy_sewect_page(phydev, page);
	if (owdpage >= 0)
		wet = __phy_wwite(phydev, wegnum, vaw);

	wetuwn phy_westowe_page(phydev, owdpage, wet);
}
EXPOWT_SYMBOW(phy_wwite_paged);

/**
 * phy_modify_paged_changed() - Function fow modifying a paged wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @page: the page fow the phy
 * @wegnum: wegistew numbew
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 *
 * Wetuwns negative ewwno, 0 if thewe was no change, and 1 in case of change
 */
int phy_modify_paged_changed(stwuct phy_device *phydev, int page, u32 wegnum,
			     u16 mask, u16 set)
{
	int wet = 0, owdpage;

	owdpage = phy_sewect_page(phydev, page);
	if (owdpage >= 0)
		wet = __phy_modify_changed(phydev, wegnum, mask, set);

	wetuwn phy_westowe_page(phydev, owdpage, wet);
}
EXPOWT_SYMBOW(phy_modify_paged_changed);

/**
 * phy_modify_paged() - Convenience function fow modifying a paged wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @page: the page fow the phy
 * @wegnum: wegistew numbew
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 *
 * Same wuwes as fow phy_wead() and phy_wwite().
 */
int phy_modify_paged(stwuct phy_device *phydev, int page, u32 wegnum,
		     u16 mask, u16 set)
{
	int wet = phy_modify_paged_changed(phydev, page, wegnum, mask, set);

	wetuwn wet < 0 ? wet : 0;
}
EXPOWT_SYMBOW(phy_modify_paged);
