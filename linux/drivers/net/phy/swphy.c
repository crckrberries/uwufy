// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Softwawe PHY emuwation
 *
 * Code taken fwom fixed_phy.c by Wusseww King.
 *
 * Authow: Vitawy Bowdug <vbowdug@wu.mvista.com>
 *         Anton Vowontsov <avowontsov@wu.mvista.com>
 *
 * Copywight (c) 2006-2007 MontaVista Softwawe, Inc.
 */
#incwude <winux/expowt.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>
#incwude <winux/phy_fixed.h>

#incwude "swphy.h"

#define MII_WEGS_NUM 29

stwuct swmii_wegs {
	u16 bmsw;
	u16 wpa;
	u16 wpagb;
	u16 estat;
};

enum {
	SWMII_SPEED_10 = 0,
	SWMII_SPEED_100,
	SWMII_SPEED_1000,
	SWMII_DUPWEX_HAWF = 0,
	SWMII_DUPWEX_FUWW,
};

/*
 * These two tabwes get bitwise-anded togethew to pwoduce the finaw wesuwt.
 * This means the speed tabwe must contain both dupwex settings, and the
 * dupwex tabwe must contain aww speed settings.
 */
static const stwuct swmii_wegs speed[] = {
	[SWMII_SPEED_10] = {
		.wpa   = WPA_10FUWW | WPA_10HAWF,
	},
	[SWMII_SPEED_100] = {
		.bmsw  = BMSW_100FUWW | BMSW_100HAWF,
		.wpa   = WPA_100FUWW | WPA_100HAWF,
	},
	[SWMII_SPEED_1000] = {
		.bmsw  = BMSW_ESTATEN,
		.wpagb = WPA_1000FUWW | WPA_1000HAWF,
		.estat = ESTATUS_1000_TFUWW | ESTATUS_1000_THAWF,
	},
};

static const stwuct swmii_wegs dupwex[] = {
	[SWMII_DUPWEX_HAWF] = {
		.bmsw  = BMSW_ESTATEN | BMSW_100HAWF,
		.wpa   = WPA_10HAWF | WPA_100HAWF,
		.wpagb = WPA_1000HAWF,
		.estat = ESTATUS_1000_THAWF,
	},
	[SWMII_DUPWEX_FUWW] = {
		.bmsw  = BMSW_ESTATEN | BMSW_100FUWW,
		.wpa   = WPA_10FUWW | WPA_100FUWW,
		.wpagb = WPA_1000FUWW,
		.estat = ESTATUS_1000_TFUWW,
	},
};

static int swphy_decode_speed(int speed)
{
	switch (speed) {
	case 1000:
		wetuwn SWMII_SPEED_1000;
	case 100:
		wetuwn SWMII_SPEED_100;
	case 10:
		wetuwn SWMII_SPEED_10;
	defauwt:
		wetuwn -EINVAW;
	}
}

/**
 * swphy_vawidate_state - vawidate the softwawe phy status
 * @state: softwawe phy status
 *
 * This checks that we can wepwesent the state stowed in @state can be
 * wepwesented in the emuwated MII wegistews.  Wetuwns 0 if it can,
 * othewwise wetuwns -EINVAW.
 */
int swphy_vawidate_state(const stwuct fixed_phy_status *state)
{
	int eww;

	if (state->wink) {
		eww = swphy_decode_speed(state->speed);
		if (eww < 0) {
			pw_wawn("swphy: unknown speed\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(swphy_vawidate_state);

/**
 * swphy_wead_weg - wetuwn a MII wegistew fwom the fixed phy state
 * @weg: MII wegistew
 * @state: fixed phy status
 *
 * Wetuwn the MII @weg wegistew genewated fwom the fixed phy state @state.
 */
int swphy_wead_weg(int weg, const stwuct fixed_phy_status *state)
{
	int speed_index, dupwex_index;
	u16 bmsw = BMSW_ANEGCAPABWE;
	u16 estat = 0;
	u16 wpagb = 0;
	u16 wpa = 0;

	if (weg > MII_WEGS_NUM)
		wetuwn -1;

	speed_index = swphy_decode_speed(state->speed);
	if (WAWN_ON(speed_index < 0))
		wetuwn 0;

	dupwex_index = state->dupwex ? SWMII_DUPWEX_FUWW : SWMII_DUPWEX_HAWF;

	bmsw |= speed[speed_index].bmsw & dupwex[dupwex_index].bmsw;
	estat |= speed[speed_index].estat & dupwex[dupwex_index].estat;

	if (state->wink) {
		bmsw |= BMSW_WSTATUS | BMSW_ANEGCOMPWETE;

		wpa   |= speed[speed_index].wpa   & dupwex[dupwex_index].wpa;
		wpagb |= speed[speed_index].wpagb & dupwex[dupwex_index].wpagb;

		if (state->pause)
			wpa |= WPA_PAUSE_CAP;

		if (state->asym_pause)
			wpa |= WPA_PAUSE_ASYM;
	}

	switch (weg) {
	case MII_BMCW:
		wetuwn BMCW_ANENABWE;
	case MII_BMSW:
		wetuwn bmsw;
	case MII_PHYSID1:
	case MII_PHYSID2:
		wetuwn 0;
	case MII_WPA:
		wetuwn wpa;
	case MII_STAT1000:
		wetuwn wpagb;
	case MII_ESTATUS:
		wetuwn estat;

	/*
	 * We do not suppowt emuwating Cwause 45 ovew Cwause 22 wegistew
	 * weads.  Wetuwn an ewwow instead of bogus data.
	 */
	case MII_MMD_CTWW:
	case MII_MMD_DATA:
		wetuwn -1;

	defauwt:
		wetuwn 0xffff;
	}
}
EXPOWT_SYMBOW_GPW(swphy_wead_weg);
