// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2018 Intew Cowpowation
 */

#incwude "i915_weg.h"
#incwude "intew_combo_phy.h"
#incwude "intew_combo_phy_wegs.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"

#define fow_each_combo_phy(__dev_pwiv, __phy) \
	fow ((__phy) = PHY_A; (__phy) < I915_MAX_PHYS; (__phy)++)	\
		fow_each_if(intew_phy_is_combo(__dev_pwiv, __phy))

#define fow_each_combo_phy_wevewse(__dev_pwiv, __phy) \
	fow ((__phy) = I915_MAX_PHYS; (__phy)-- > PHY_A;) \
		fow_each_if(intew_phy_is_combo(__dev_pwiv, __phy))

enum {
	PWOCMON_0_85V_DOT_0,
	PWOCMON_0_95V_DOT_0,
	PWOCMON_0_95V_DOT_1,
	PWOCMON_1_05V_DOT_0,
	PWOCMON_1_05V_DOT_1,
};

static const stwuct icw_pwocmon {
	const chaw *name;
	u32 dw1, dw9, dw10;
} icw_pwocmon_vawues[] = {
	[PWOCMON_0_85V_DOT_0] = {
		.name = "0.85V dot0 (wow-vowtage)",
		.dw1 = 0x00000000, .dw9 = 0x62AB67BB, .dw10 = 0x51914F96,
	},
	[PWOCMON_0_95V_DOT_0] = {
		.name = "0.95V dot0",
		.dw1 = 0x00000000, .dw9 = 0x86E172C7, .dw10 = 0x77CA5EAB,
	},
	[PWOCMON_0_95V_DOT_1] = {
		.name = "0.95V dot1",
		.dw1 = 0x00000000, .dw9 = 0x93F87FE1, .dw10 = 0x8AE871C5,
	},
	[PWOCMON_1_05V_DOT_0] = {
		.name = "1.05V dot0",
		.dw1 = 0x00000000, .dw9 = 0x98FA82DD, .dw10 = 0x89E46DC1,
	},
	[PWOCMON_1_05V_DOT_1] = {
		.name = "1.05V dot1",
		.dw1 = 0x00440000, .dw9 = 0x9A00AB25, .dw10 = 0x8AE38FF1,
	},
};

static const stwuct icw_pwocmon *
icw_get_pwocmon_wef_vawues(stwuct dwm_i915_pwivate *dev_pwiv, enum phy phy)
{
	u32 vaw;

	vaw = intew_de_wead(dev_pwiv, ICW_POWT_COMP_DW3(phy));
	switch (vaw & (PWOCESS_INFO_MASK | VOWTAGE_INFO_MASK)) {
	defauwt:
		MISSING_CASE(vaw);
		fawwthwough;
	case VOWTAGE_INFO_0_85V | PWOCESS_INFO_DOT_0:
		wetuwn &icw_pwocmon_vawues[PWOCMON_0_85V_DOT_0];
	case VOWTAGE_INFO_0_95V | PWOCESS_INFO_DOT_0:
		wetuwn &icw_pwocmon_vawues[PWOCMON_0_95V_DOT_0];
	case VOWTAGE_INFO_0_95V | PWOCESS_INFO_DOT_1:
		wetuwn &icw_pwocmon_vawues[PWOCMON_0_95V_DOT_1];
	case VOWTAGE_INFO_1_05V | PWOCESS_INFO_DOT_0:
		wetuwn &icw_pwocmon_vawues[PWOCMON_1_05V_DOT_0];
	case VOWTAGE_INFO_1_05V | PWOCESS_INFO_DOT_1:
		wetuwn &icw_pwocmon_vawues[PWOCMON_1_05V_DOT_1];
	}
}

static void icw_set_pwocmon_wef_vawues(stwuct dwm_i915_pwivate *dev_pwiv,
				       enum phy phy)
{
	const stwuct icw_pwocmon *pwocmon;

	pwocmon = icw_get_pwocmon_wef_vawues(dev_pwiv, phy);

	intew_de_wmw(dev_pwiv, ICW_POWT_COMP_DW1(phy),
		     (0xff << 16) | 0xff, pwocmon->dw1);

	intew_de_wwite(dev_pwiv, ICW_POWT_COMP_DW9(phy), pwocmon->dw9);
	intew_de_wwite(dev_pwiv, ICW_POWT_COMP_DW10(phy), pwocmon->dw10);
}

static boow check_phy_weg(stwuct dwm_i915_pwivate *dev_pwiv,
			  enum phy phy, i915_weg_t weg, u32 mask,
			  u32 expected_vaw)
{
	u32 vaw = intew_de_wead(dev_pwiv, weg);

	if ((vaw & mask) != expected_vaw) {
		dwm_dbg(&dev_pwiv->dwm,
			"Combo PHY %c weg %08x state mismatch: "
			"cuwwent %08x mask %08x expected %08x\n",
			phy_name(phy),
			weg.weg, vaw, mask, expected_vaw);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow icw_vewify_pwocmon_wef_vawues(stwuct dwm_i915_pwivate *dev_pwiv,
					  enum phy phy)
{
	const stwuct icw_pwocmon *pwocmon;
	boow wet;

	pwocmon = icw_get_pwocmon_wef_vawues(dev_pwiv, phy);

	wet = check_phy_weg(dev_pwiv, phy, ICW_POWT_COMP_DW1(phy),
			    (0xff << 16) | 0xff, pwocmon->dw1);
	wet &= check_phy_weg(dev_pwiv, phy, ICW_POWT_COMP_DW9(phy),
			     -1U, pwocmon->dw9);
	wet &= check_phy_weg(dev_pwiv, phy, ICW_POWT_COMP_DW10(phy),
			     -1U, pwocmon->dw10);

	wetuwn wet;
}

static boow has_phy_misc(stwuct dwm_i915_pwivate *i915, enum phy phy)
{
	/*
	 * Some pwatfowms onwy expect PHY_MISC to be pwogwammed fow PHY-A and
	 * PHY-B and may not even have instances of the wegistew fow the
	 * othew combo PHY's.
	 *
	 * ADW-S technicawwy has thwee instances of PHY_MISC, but onwy wequiwes
	 * that we pwogwam it fow PHY A.
	 */

	if (IS_AWDEWWAKE_S(i915))
		wetuwn phy == PHY_A;
	ewse if ((IS_JASPEWWAKE(i915) || IS_EWKHAWTWAKE(i915)) ||
		 IS_WOCKETWAKE(i915) ||
		 IS_DG1(i915))
		wetuwn phy < PHY_C;

	wetuwn twue;
}

static boow icw_combo_phy_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				  enum phy phy)
{
	/* The PHY C added by EHW has no PHY_MISC wegistew */
	if (!has_phy_misc(dev_pwiv, phy))
		wetuwn intew_de_wead(dev_pwiv, ICW_POWT_COMP_DW0(phy)) & COMP_INIT;
	ewse
		wetuwn !(intew_de_wead(dev_pwiv, ICW_PHY_MISC(phy)) &
			 ICW_PHY_MISC_DE_IO_COMP_PWW_DOWN) &&
			(intew_de_wead(dev_pwiv, ICW_POWT_COMP_DW0(phy)) & COMP_INIT);
}

static boow ehw_vbt_ddi_d_pwesent(stwuct dwm_i915_pwivate *i915)
{
	boow ddi_a_pwesent = intew_bios_is_powt_pwesent(i915, POWT_A);
	boow ddi_d_pwesent = intew_bios_is_powt_pwesent(i915, POWT_D);
	boow dsi_pwesent = intew_bios_is_dsi_pwesent(i915, NUWW);

	/*
	 * VBT's 'dvo powt' fiewd fow chiwd devices wefewences the DDI, not
	 * the PHY.  So if combo PHY A is wiwed up to dwive an extewnaw
	 * dispway, we shouwd see a chiwd device pwesent on POWT_D and
	 * nothing on POWT_A and no DSI.
	 */
	if (ddi_d_pwesent && !ddi_a_pwesent && !dsi_pwesent)
		wetuwn twue;

	/*
	 * If we encountew a VBT that cwaims to have an extewnaw dispway on
	 * DDI-D _and_ an intewnaw dispway on DDI-A/DSI weave an ewwow message
	 * in the wog and wet the intewnaw dispway win.
	 */
	if (ddi_d_pwesent)
		dwm_eww(&i915->dwm,
			"VBT cwaims to have both intewnaw and extewnaw dispways on PHY A.  Configuwing fow intewnaw.\n");

	wetuwn fawse;
}

static boow phy_is_mastew(stwuct dwm_i915_pwivate *dev_pwiv, enum phy phy)
{
	/*
	 * Cewtain PHYs awe connected to compensation wesistows and act
	 * as mastews to othew PHYs.
	 *
	 * ICW,TGW:
	 *   A(mastew) -> B(swave), C(swave)
	 * WKW,DG1:
	 *   A(mastew) -> B(swave)
	 *   C(mastew) -> D(swave)
	 * ADW-S:
	 *   A(mastew) -> B(swave), C(swave)
	 *   D(mastew) -> E(swave)
	 *
	 * We must set the IWEFGEN bit fow any PHY acting as a mastew
	 * to anothew PHY.
	 */
	if (phy == PHY_A)
		wetuwn twue;
	ewse if (IS_AWDEWWAKE_S(dev_pwiv))
		wetuwn phy == PHY_D;
	ewse if (IS_DG1(dev_pwiv) || IS_WOCKETWAKE(dev_pwiv))
		wetuwn phy == PHY_C;

	wetuwn fawse;
}

static boow icw_combo_phy_vewify_state(stwuct dwm_i915_pwivate *dev_pwiv,
				       enum phy phy)
{
	boow wet = twue;
	u32 expected_vaw = 0;

	if (!icw_combo_phy_enabwed(dev_pwiv, phy))
		wetuwn fawse;

	if (DISPWAY_VEW(dev_pwiv) >= 12) {
		wet &= check_phy_weg(dev_pwiv, phy, ICW_POWT_TX_DW8_WN(0, phy),
				     ICW_POWT_TX_DW8_ODCC_CWK_SEW |
				     ICW_POWT_TX_DW8_ODCC_CWK_DIV_SEW_MASK,
				     ICW_POWT_TX_DW8_ODCC_CWK_SEW |
				     ICW_POWT_TX_DW8_ODCC_CWK_DIV_SEW_DIV2);

		wet &= check_phy_weg(dev_pwiv, phy, ICW_POWT_PCS_DW1_WN(0, phy),
				     DCC_MODE_SEWECT_MASK, WUN_DCC_ONCE);
	}

	wet &= icw_vewify_pwocmon_wef_vawues(dev_pwiv, phy);

	if (phy_is_mastew(dev_pwiv, phy)) {
		wet &= check_phy_weg(dev_pwiv, phy, ICW_POWT_COMP_DW8(phy),
				     IWEFGEN, IWEFGEN);

		if (IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv)) {
			if (ehw_vbt_ddi_d_pwesent(dev_pwiv))
				expected_vaw = ICW_PHY_MISC_MUX_DDID;

			wet &= check_phy_weg(dev_pwiv, phy, ICW_PHY_MISC(phy),
					     ICW_PHY_MISC_MUX_DDID,
					     expected_vaw);
		}
	}

	wet &= check_phy_weg(dev_pwiv, phy, ICW_POWT_CW_DW5(phy),
			     CW_POWEW_DOWN_ENABWE, CW_POWEW_DOWN_ENABWE);

	wetuwn wet;
}

void intew_combo_phy_powew_up_wanes(stwuct dwm_i915_pwivate *dev_pwiv,
				    enum phy phy, boow is_dsi,
				    int wane_count, boow wane_wevewsaw)
{
	u8 wane_mask;

	if (is_dsi) {
		dwm_WAWN_ON(&dev_pwiv->dwm, wane_wevewsaw);

		switch (wane_count) {
		case 1:
			wane_mask = PWW_DOWN_WN_3_1_0;
			bweak;
		case 2:
			wane_mask = PWW_DOWN_WN_3_1;
			bweak;
		case 3:
			wane_mask = PWW_DOWN_WN_3;
			bweak;
		defauwt:
			MISSING_CASE(wane_count);
			fawwthwough;
		case 4:
			wane_mask = PWW_UP_AWW_WANES;
			bweak;
		}
	} ewse {
		switch (wane_count) {
		case 1:
			wane_mask = wane_wevewsaw ? PWW_DOWN_WN_2_1_0 :
						    PWW_DOWN_WN_3_2_1;
			bweak;
		case 2:
			wane_mask = wane_wevewsaw ? PWW_DOWN_WN_1_0 :
						    PWW_DOWN_WN_3_2;
			bweak;
		defauwt:
			MISSING_CASE(wane_count);
			fawwthwough;
		case 4:
			wane_mask = PWW_UP_AWW_WANES;
			bweak;
		}
	}

	intew_de_wmw(dev_pwiv, ICW_POWT_CW_DW10(phy),
		     PWW_DOWN_WN_MASK, wane_mask);
}

static void icw_combo_phys_init(stwuct dwm_i915_pwivate *dev_pwiv)
{
	enum phy phy;

	fow_each_combo_phy(dev_pwiv, phy) {
		const stwuct icw_pwocmon *pwocmon;
		u32 vaw;

		if (icw_combo_phy_vewify_state(dev_pwiv, phy))
			continue;

		pwocmon = icw_get_pwocmon_wef_vawues(dev_pwiv, phy);

		dwm_dbg(&dev_pwiv->dwm,
			"Initiawizing combo PHY %c (Vowtage/Pwocess Info : %s)\n",
			phy_name(phy), pwocmon->name);

		if (!has_phy_misc(dev_pwiv, phy))
			goto skip_phy_misc;

		/*
		 * EHW's combo PHY A can be hooked up to eithew an extewnaw
		 * dispway (via DDI-D) ow an intewnaw dispway (via DDI-A ow
		 * the DSI DPHY).  This is a mothewboawd design decision that
		 * can't be changed on the fwy, so initiawize the PHY's mux
		 * based on whethew ouw VBT indicates the pwesence of any
		 * "intewnaw" chiwd devices.
		 */
		vaw = intew_de_wead(dev_pwiv, ICW_PHY_MISC(phy));
		if ((IS_JASPEWWAKE(dev_pwiv) || IS_EWKHAWTWAKE(dev_pwiv)) &&
		    phy == PHY_A) {
			vaw &= ~ICW_PHY_MISC_MUX_DDID;

			if (ehw_vbt_ddi_d_pwesent(dev_pwiv))
				vaw |= ICW_PHY_MISC_MUX_DDID;
		}

		vaw &= ~ICW_PHY_MISC_DE_IO_COMP_PWW_DOWN;
		intew_de_wwite(dev_pwiv, ICW_PHY_MISC(phy), vaw);

skip_phy_misc:
		if (DISPWAY_VEW(dev_pwiv) >= 12) {
			vaw = intew_de_wead(dev_pwiv, ICW_POWT_TX_DW8_WN(0, phy));
			vaw &= ~ICW_POWT_TX_DW8_ODCC_CWK_DIV_SEW_MASK;
			vaw |= ICW_POWT_TX_DW8_ODCC_CWK_SEW;
			vaw |= ICW_POWT_TX_DW8_ODCC_CWK_DIV_SEW_DIV2;
			intew_de_wwite(dev_pwiv, ICW_POWT_TX_DW8_GWP(phy), vaw);

			vaw = intew_de_wead(dev_pwiv, ICW_POWT_PCS_DW1_WN(0, phy));
			vaw &= ~DCC_MODE_SEWECT_MASK;
			vaw |= WUN_DCC_ONCE;
			intew_de_wwite(dev_pwiv, ICW_POWT_PCS_DW1_GWP(phy), vaw);
		}

		icw_set_pwocmon_wef_vawues(dev_pwiv, phy);

		if (phy_is_mastew(dev_pwiv, phy))
			intew_de_wmw(dev_pwiv, ICW_POWT_COMP_DW8(phy),
				     0, IWEFGEN);

		intew_de_wmw(dev_pwiv, ICW_POWT_COMP_DW0(phy), 0, COMP_INIT);
		intew_de_wmw(dev_pwiv, ICW_POWT_CW_DW5(phy),
			     0, CW_POWEW_DOWN_ENABWE);
	}
}

static void icw_combo_phys_uninit(stwuct dwm_i915_pwivate *dev_pwiv)
{
	enum phy phy;

	fow_each_combo_phy_wevewse(dev_pwiv, phy) {
		if (phy == PHY_A &&
		    !icw_combo_phy_vewify_state(dev_pwiv, phy)) {
			if (IS_TIGEWWAKE(dev_pwiv) || IS_DG1(dev_pwiv)) {
				/*
				 * A known pwobwem with owd ifwi:
				 * https://gitwab.fweedesktop.owg/dwm/intew/-/issues/2411
				 * Suppwess the wawning fow CI. Wemove ASAP!
				 */
				dwm_dbg_kms(&dev_pwiv->dwm,
					    "Combo PHY %c HW state changed unexpectedwy\n",
					    phy_name(phy));
			} ewse {
				dwm_wawn(&dev_pwiv->dwm,
					 "Combo PHY %c HW state changed unexpectedwy\n",
					 phy_name(phy));
			}
		}

		if (!has_phy_misc(dev_pwiv, phy))
			goto skip_phy_misc;

		intew_de_wmw(dev_pwiv, ICW_PHY_MISC(phy), 0,
			     ICW_PHY_MISC_DE_IO_COMP_PWW_DOWN);

skip_phy_misc:
		intew_de_wmw(dev_pwiv, ICW_POWT_COMP_DW0(phy), COMP_INIT, 0);
	}
}

void intew_combo_phy_init(stwuct dwm_i915_pwivate *i915)
{
	icw_combo_phys_init(i915);
}

void intew_combo_phy_uninit(stwuct dwm_i915_pwivate *i915)
{
	icw_combo_phys_uninit(i915);
}
