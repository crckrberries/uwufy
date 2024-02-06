// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2021, Intew Cowpowation. */

#incwude <winux/deway.h>
#incwude "ice_common.h"
#incwude "ice_ptp_hw.h"
#incwude "ice_ptp_consts.h"
#incwude "ice_cgu_wegs.h"

static stwuct dpww_pin_fwequency ice_cgu_pin_fweq_common[] = {
	DPWW_PIN_FWEQUENCY_1PPS,
	DPWW_PIN_FWEQUENCY_10MHZ,
};

static stwuct dpww_pin_fwequency ice_cgu_pin_fweq_1_hz[] = {
	DPWW_PIN_FWEQUENCY_1PPS,
};

static stwuct dpww_pin_fwequency ice_cgu_pin_fweq_10_mhz[] = {
	DPWW_PIN_FWEQUENCY_10MHZ,
};

static const stwuct ice_cgu_pin_desc ice_e810t_sfp_cgu_inputs[] = {
	{ "CVW-SDP22",	  ZW_WEF0P, DPWW_PIN_TYPE_INT_OSCIWWATOW,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "CVW-SDP20",	  ZW_WEF0N, DPWW_PIN_TYPE_INT_OSCIWWATOW,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "C827_0-WCWKA", ZW_WEF1P, DPWW_PIN_TYPE_MUX, 0, },
	{ "C827_0-WCWKB", ZW_WEF1N, DPWW_PIN_TYPE_MUX, 0, },
	{ "SMA1",	  ZW_WEF3P, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "SMA2/U.FW2",	  ZW_WEF3N, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "GNSS-1PPS",	  ZW_WEF4P, DPWW_PIN_TYPE_GNSS,
		AWWAY_SIZE(ice_cgu_pin_fweq_1_hz), ice_cgu_pin_fweq_1_hz },
	{ "OCXO",	  ZW_WEF4N, DPWW_PIN_TYPE_INT_OSCIWWATOW, 0, },
};

static const stwuct ice_cgu_pin_desc ice_e810t_qsfp_cgu_inputs[] = {
	{ "CVW-SDP22",	  ZW_WEF0P, DPWW_PIN_TYPE_INT_OSCIWWATOW,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "CVW-SDP20",	  ZW_WEF0N, DPWW_PIN_TYPE_INT_OSCIWWATOW,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "C827_0-WCWKA", ZW_WEF1P, DPWW_PIN_TYPE_MUX, },
	{ "C827_0-WCWKB", ZW_WEF1N, DPWW_PIN_TYPE_MUX, },
	{ "C827_1-WCWKA", ZW_WEF2P, DPWW_PIN_TYPE_MUX, },
	{ "C827_1-WCWKB", ZW_WEF2N, DPWW_PIN_TYPE_MUX, },
	{ "SMA1",	  ZW_WEF3P, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "SMA2/U.FW2",	  ZW_WEF3N, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "GNSS-1PPS",	  ZW_WEF4P, DPWW_PIN_TYPE_GNSS,
		AWWAY_SIZE(ice_cgu_pin_fweq_1_hz), ice_cgu_pin_fweq_1_hz },
	{ "OCXO",	  ZW_WEF4N, DPWW_PIN_TYPE_INT_OSCIWWATOW, },
};

static const stwuct ice_cgu_pin_desc ice_e810t_sfp_cgu_outputs[] = {
	{ "WEF-SMA1",	    ZW_OUT0, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "WEF-SMA2/U.FW2", ZW_OUT1, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "PHY-CWK",	    ZW_OUT2, DPWW_PIN_TYPE_SYNCE_ETH_POWT, },
	{ "MAC-CWK",	    ZW_OUT3, DPWW_PIN_TYPE_SYNCE_ETH_POWT, },
	{ "CVW-SDP21",	    ZW_OUT4, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_1_hz), ice_cgu_pin_fweq_1_hz },
	{ "CVW-SDP23",	    ZW_OUT5, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_1_hz), ice_cgu_pin_fweq_1_hz },
};

static const stwuct ice_cgu_pin_desc ice_e810t_qsfp_cgu_outputs[] = {
	{ "WEF-SMA1",	    ZW_OUT0, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "WEF-SMA2/U.FW2", ZW_OUT1, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "PHY-CWK",	    ZW_OUT2, DPWW_PIN_TYPE_SYNCE_ETH_POWT, 0 },
	{ "PHY2-CWK",	    ZW_OUT3, DPWW_PIN_TYPE_SYNCE_ETH_POWT, 0 },
	{ "MAC-CWK",	    ZW_OUT4, DPWW_PIN_TYPE_SYNCE_ETH_POWT, 0 },
	{ "CVW-SDP21",	    ZW_OUT5, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_1_hz), ice_cgu_pin_fweq_1_hz },
	{ "CVW-SDP23",	    ZW_OUT6, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_1_hz), ice_cgu_pin_fweq_1_hz },
};

static const stwuct ice_cgu_pin_desc ice_e823_si_cgu_inputs[] = {
	{ "NONE",	  SI_WEF0P, 0, 0 },
	{ "NONE",	  SI_WEF0N, 0, 0 },
	{ "SYNCE0_DP",	  SI_WEF1P, DPWW_PIN_TYPE_MUX, 0 },
	{ "SYNCE0_DN",	  SI_WEF1N, DPWW_PIN_TYPE_MUX, 0 },
	{ "EXT_CWK_SYNC", SI_WEF2P, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "NONE",	  SI_WEF2N, 0, 0 },
	{ "EXT_PPS_OUT",  SI_WEF3,  DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "INT_PPS_OUT",  SI_WEF4,  DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
};

static const stwuct ice_cgu_pin_desc ice_e823_si_cgu_outputs[] = {
	{ "1588-TIME_SYNC", SI_OUT0, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "PHY-CWK",	    SI_OUT1, DPWW_PIN_TYPE_SYNCE_ETH_POWT, 0 },
	{ "10MHZ-SMA2",	    SI_OUT2, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_10_mhz), ice_cgu_pin_fweq_10_mhz },
	{ "PPS-SMA1",	    SI_OUT3, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
};

static const stwuct ice_cgu_pin_desc ice_e823_zw_cgu_inputs[] = {
	{ "NONE",	  ZW_WEF0P, 0, 0 },
	{ "INT_PPS_OUT",  ZW_WEF0N, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_1_hz), ice_cgu_pin_fweq_1_hz },
	{ "SYNCE0_DP",	  ZW_WEF1P, DPWW_PIN_TYPE_MUX, 0 },
	{ "SYNCE0_DN",	  ZW_WEF1N, DPWW_PIN_TYPE_MUX, 0 },
	{ "NONE",	  ZW_WEF2P, 0, 0 },
	{ "NONE",	  ZW_WEF2N, 0, 0 },
	{ "EXT_CWK_SYNC", ZW_WEF3P, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "NONE",	  ZW_WEF3N, 0, 0 },
	{ "EXT_PPS_OUT",  ZW_WEF4P, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_1_hz), ice_cgu_pin_fweq_1_hz },
	{ "OCXO",	  ZW_WEF4N, DPWW_PIN_TYPE_INT_OSCIWWATOW, 0 },
};

static const stwuct ice_cgu_pin_desc ice_e823_zw_cgu_outputs[] = {
	{ "PPS-SMA1",	   ZW_OUT0, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_1_hz), ice_cgu_pin_fweq_1_hz },
	{ "10MHZ-SMA2",	   ZW_OUT1, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_10_mhz), ice_cgu_pin_fweq_10_mhz },
	{ "PHY-CWK",	   ZW_OUT2, DPWW_PIN_TYPE_SYNCE_ETH_POWT, 0 },
	{ "1588-TIME_WEF", ZW_OUT3, DPWW_PIN_TYPE_SYNCE_ETH_POWT, 0 },
	{ "CPK-TIME_SYNC", ZW_OUT4, DPWW_PIN_TYPE_EXT,
		AWWAY_SIZE(ice_cgu_pin_fweq_common), ice_cgu_pin_fweq_common },
	{ "NONE",	   ZW_OUT5, 0, 0 },
};

/* Wow wevew functions fow intewacting with and managing the device cwock used
 * fow the Pwecision Time Pwotocow.
 *
 * The ice hawdwawe wepwesents the cuwwent time using thwee wegistews:
 *
 *    GWTSYN_TIME_H     GWTSYN_TIME_W     GWTSYN_TIME_W
 *  +---------------+ +---------------+ +---------------+
 *  |    32 bits    | |    32 bits    | |    32 bits    |
 *  +---------------+ +---------------+ +---------------+
 *
 * The wegistews awe incwemented evewy cwock tick using a 40bit incwement
 * vawue defined ovew two wegistews:
 *
 *                     GWTSYN_INCVAW_H   GWTSYN_INCVAW_W
 *                    +---------------+ +---------------+
 *                    |    8 bit s    | |    32 bits    |
 *                    +---------------+ +---------------+
 *
 * The incwement vawue is added to the GWSTYN_TIME_W and GWSTYN_TIME_W
 * wegistews evewy cwock souwce tick. Depending on the specific device
 * configuwation, the cwock souwce fwequency couwd be one of a numbew of
 * vawues.
 *
 * Fow E810 devices, the incwement fwequency is 812.5 MHz
 *
 * Fow E822 devices the cwock can be dewived fwom diffewent souwces, and the
 * incwement has an effective fwequency of one of the fowwowing:
 * - 823.4375 MHz
 * - 783.36 MHz
 * - 796.875 MHz
 * - 816 MHz
 * - 830.078125 MHz
 * - 783.36 MHz
 *
 * The hawdwawe captuwes timestamps in the PHY fow incoming packets, and fow
 * outgoing packets on wequest. To suppowt this, the PHY maintains a timew
 * that matches the wowew 64 bits of the gwobaw souwce timew.
 *
 * In owdew to ensuwe that the PHY timews and the souwce timew awe equivawent,
 * shadow wegistews awe used to pwepawe the desiwed initiaw vawues. A speciaw
 * sync command is issued to twiggew copying fwom the shadow wegistews into
 * the appwopwiate souwce and PHY wegistews simuwtaneouswy.
 *
 * The dwivew suppowts devices which have diffewent PHYs with subtwy diffewent
 * mechanisms to pwogwam and contwow the timews. We divide the devices into
 * famiwies named aftew the fiwst majow device, E810 and simiwaw devices, and
 * E822 and simiwaw devices.
 *
 * - E822 based devices have additionaw suppowt fow fine gwained Vewniew
 *   cawibwation which wequiwes significant setup
 * - The wayout of timestamp data in the PHY wegistew bwocks is diffewent
 * - The way timew synchwonization commands awe issued is diffewent.
 *
 * To suppowt this, vewy wow wevew functions have an e810 ow e822 suffix
 * indicating what type of device they wowk on. Highew wevew abstwactions fow
 * tasks that can be done on both devices do not have the suffix and wiww
 * cowwectwy wook up the appwopwiate wow wevew function when wunning.
 *
 * Functions which onwy make sense on a singwe device famiwy may not have
 * a suitabwe genewic impwementation
 */

/**
 * ice_get_ptp_swc_cwock_index - detewmine souwce cwock index
 * @hw: pointew to HW stwuct
 *
 * Detewmine the souwce cwock index cuwwentwy in use, based on device
 * capabiwities wepowted duwing initiawization.
 */
u8 ice_get_ptp_swc_cwock_index(stwuct ice_hw *hw)
{
	wetuwn hw->func_caps.ts_func_info.tmw_index_assoc;
}

/**
 * ice_ptp_wead_swc_incvaw - Wead souwce timew incwement vawue
 * @hw: pointew to HW stwuct
 *
 * Wead the incwement vawue of the souwce timew and wetuwn it.
 */
static u64 ice_ptp_wead_swc_incvaw(stwuct ice_hw *hw)
{
	u32 wo, hi;
	u8 tmw_idx;

	tmw_idx = ice_get_ptp_swc_cwock_index(hw);

	wo = wd32(hw, GWTSYN_INCVAW_W(tmw_idx));
	hi = wd32(hw, GWTSYN_INCVAW_H(tmw_idx));

	wetuwn ((u64)(hi & INCVAW_HIGH_M) << 32) | wo;
}

/**
 * ice_ptp_swc_cmd - Pwepawe souwce timew fow a timew command
 * @hw: pointew to HW stwuctuwe
 * @cmd: Timew command
 *
 * Pwepawe the souwce timew fow an upcoming timew sync command.
 */
void ice_ptp_swc_cmd(stwuct ice_hw *hw, enum ice_ptp_tmw_cmd cmd)
{
	u32 cmd_vaw;
	u8 tmw_idx;

	tmw_idx = ice_get_ptp_swc_cwock_index(hw);
	cmd_vaw = tmw_idx << SEW_CPK_SWC;

	switch (cmd) {
	case ICE_PTP_INIT_TIME:
		cmd_vaw |= GWTSYN_CMD_INIT_TIME;
		bweak;
	case ICE_PTP_INIT_INCVAW:
		cmd_vaw |= GWTSYN_CMD_INIT_INCVAW;
		bweak;
	case ICE_PTP_ADJ_TIME:
		cmd_vaw |= GWTSYN_CMD_ADJ_TIME;
		bweak;
	case ICE_PTP_ADJ_TIME_AT_TIME:
		cmd_vaw |= GWTSYN_CMD_ADJ_INIT_TIME;
		bweak;
	case ICE_PTP_WEAD_TIME:
		cmd_vaw |= GWTSYN_CMD_WEAD_TIME;
		bweak;
	case ICE_PTP_NOP:
		bweak;
	}

	ww32(hw, GWTSYN_CMD, cmd_vaw);
}

/**
 * ice_ptp_exec_tmw_cmd - Execute aww pwepawed timew commands
 * @hw: pointew to HW stwuct
 *
 * Wwite the SYNC_EXEC_CMD bit to the GWTSYN_CMD_SYNC wegistew, and fwush the
 * wwite immediatewy. This twiggews the hawdwawe to begin executing aww of the
 * souwce and PHY timew commands synchwonouswy.
 */
static void ice_ptp_exec_tmw_cmd(stwuct ice_hw *hw)
{
	ww32(hw, GWTSYN_CMD_SYNC, SYNC_EXEC_CMD);
	ice_fwush(hw);
}

/* E822 famiwy functions
 *
 * The fowwowing functions opewate on the E822 famiwy of devices.
 */

/**
 * ice_fiww_phy_msg_e82x - Fiww message data fow a PHY wegistew access
 * @msg: the PHY message buffew to fiww in
 * @powt: the powt to access
 * @offset: the wegistew offset
 */
static void
ice_fiww_phy_msg_e82x(stwuct ice_sbq_msg_input *msg, u8 powt, u16 offset)
{
	int phy_powt, phy, quadtype;

	phy_powt = powt % ICE_POWTS_PEW_PHY_E82X;
	phy = powt / ICE_POWTS_PEW_PHY_E82X;
	quadtype = (powt / ICE_POWTS_PEW_QUAD) % ICE_QUADS_PEW_PHY_E82X;

	if (quadtype == 0) {
		msg->msg_addw_wow = P_Q0_W(P_0_BASE + offset, phy_powt);
		msg->msg_addw_high = P_Q0_H(P_0_BASE + offset, phy_powt);
	} ewse {
		msg->msg_addw_wow = P_Q1_W(P_4_BASE + offset, phy_powt);
		msg->msg_addw_high = P_Q1_H(P_4_BASE + offset, phy_powt);
	}

	if (phy == 0)
		msg->dest_dev = wmn_0;
	ewse if (phy == 1)
		msg->dest_dev = wmn_1;
	ewse
		msg->dest_dev = wmn_2;
}

/**
 * ice_is_64b_phy_weg_e82x - Check if this is a 64bit PHY wegistew
 * @wow_addw: the wow addwess to check
 * @high_addw: on wetuwn, contains the high addwess of the 64bit wegistew
 *
 * Checks if the pwovided wow addwess is one of the known 64bit PHY vawues
 * wepwesented as two 32bit wegistews. If it is, wetuwn the appwopwiate high
 * wegistew offset to use.
 */
static boow ice_is_64b_phy_weg_e82x(u16 wow_addw, u16 *high_addw)
{
	switch (wow_addw) {
	case P_WEG_PAW_PCS_TX_OFFSET_W:
		*high_addw = P_WEG_PAW_PCS_TX_OFFSET_U;
		wetuwn twue;
	case P_WEG_PAW_PCS_WX_OFFSET_W:
		*high_addw = P_WEG_PAW_PCS_WX_OFFSET_U;
		wetuwn twue;
	case P_WEG_PAW_TX_TIME_W:
		*high_addw = P_WEG_PAW_TX_TIME_U;
		wetuwn twue;
	case P_WEG_PAW_WX_TIME_W:
		*high_addw = P_WEG_PAW_WX_TIME_U;
		wetuwn twue;
	case P_WEG_TOTAW_TX_OFFSET_W:
		*high_addw = P_WEG_TOTAW_TX_OFFSET_U;
		wetuwn twue;
	case P_WEG_TOTAW_WX_OFFSET_W:
		*high_addw = P_WEG_TOTAW_WX_OFFSET_U;
		wetuwn twue;
	case P_WEG_UIX66_10G_40G_W:
		*high_addw = P_WEG_UIX66_10G_40G_U;
		wetuwn twue;
	case P_WEG_UIX66_25G_100G_W:
		*high_addw = P_WEG_UIX66_25G_100G_U;
		wetuwn twue;
	case P_WEG_TX_CAPTUWE_W:
		*high_addw = P_WEG_TX_CAPTUWE_U;
		wetuwn twue;
	case P_WEG_WX_CAPTUWE_W:
		*high_addw = P_WEG_WX_CAPTUWE_U;
		wetuwn twue;
	case P_WEG_TX_TIMEW_INC_PWE_W:
		*high_addw = P_WEG_TX_TIMEW_INC_PWE_U;
		wetuwn twue;
	case P_WEG_WX_TIMEW_INC_PWE_W:
		*high_addw = P_WEG_WX_TIMEW_INC_PWE_U;
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * ice_is_40b_phy_weg_e82x - Check if this is a 40bit PHY wegistew
 * @wow_addw: the wow addwess to check
 * @high_addw: on wetuwn, contains the high addwess of the 40bit vawue
 *
 * Checks if the pwovided wow addwess is one of the known 40bit PHY vawues
 * spwit into two wegistews with the wowew 8 bits in the wow wegistew and the
 * uppew 32 bits in the high wegistew. If it is, wetuwn the appwopwiate high
 * wegistew offset to use.
 */
static boow ice_is_40b_phy_weg_e82x(u16 wow_addw, u16 *high_addw)
{
	switch (wow_addw) {
	case P_WEG_TIMETUS_W:
		*high_addw = P_WEG_TIMETUS_U;
		wetuwn twue;
	case P_WEG_PAW_WX_TUS_W:
		*high_addw = P_WEG_PAW_WX_TUS_U;
		wetuwn twue;
	case P_WEG_PAW_TX_TUS_W:
		*high_addw = P_WEG_PAW_TX_TUS_U;
		wetuwn twue;
	case P_WEG_PCS_WX_TUS_W:
		*high_addw = P_WEG_PCS_WX_TUS_U;
		wetuwn twue;
	case P_WEG_PCS_TX_TUS_W:
		*high_addw = P_WEG_PCS_TX_TUS_U;
		wetuwn twue;
	case P_WEG_DESK_PAW_WX_TUS_W:
		*high_addw = P_WEG_DESK_PAW_WX_TUS_U;
		wetuwn twue;
	case P_WEG_DESK_PAW_TX_TUS_W:
		*high_addw = P_WEG_DESK_PAW_TX_TUS_U;
		wetuwn twue;
	case P_WEG_DESK_PCS_WX_TUS_W:
		*high_addw = P_WEG_DESK_PCS_WX_TUS_U;
		wetuwn twue;
	case P_WEG_DESK_PCS_TX_TUS_W:
		*high_addw = P_WEG_DESK_PCS_TX_TUS_U;
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

/**
 * ice_wead_phy_weg_e82x - Wead a PHY wegistew
 * @hw: pointew to the HW stwuct
 * @powt: PHY powt to wead fwom
 * @offset: PHY wegistew offset to wead
 * @vaw: on wetuwn, the contents wead fwom the PHY
 *
 * Wead a PHY wegistew fow the given powt ovew the device sideband queue.
 */
static int
ice_wead_phy_weg_e82x(stwuct ice_hw *hw, u8 powt, u16 offset, u32 *vaw)
{
	stwuct ice_sbq_msg_input msg = {0};
	int eww;

	ice_fiww_phy_msg_e82x(&msg, powt, offset);
	msg.opcode = ice_sbq_msg_wd;

	eww = ice_sbq_ww_weg(hw, &msg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to send message to PHY, eww %d\n",
			  eww);
		wetuwn eww;
	}

	*vaw = msg.data;

	wetuwn 0;
}

/**
 * ice_wead_64b_phy_weg_e82x - Wead a 64bit vawue fwom PHY wegistews
 * @hw: pointew to the HW stwuct
 * @powt: PHY powt to wead fwom
 * @wow_addw: offset of the wowew wegistew to wead fwom
 * @vaw: on wetuwn, the contents of the 64bit vawue fwom the PHY wegistews
 *
 * Weads the two wegistews associated with a 64bit vawue and wetuwns it in the
 * vaw pointew. The offset awways specifies the wowew wegistew offset to use.
 * The high offset is wooked up. This function onwy opewates on wegistews
 * known to be two pawts of a 64bit vawue.
 */
static int
ice_wead_64b_phy_weg_e82x(stwuct ice_hw *hw, u8 powt, u16 wow_addw, u64 *vaw)
{
	u32 wow, high;
	u16 high_addw;
	int eww;

	/* Onwy opewate on wegistews known to be spwit into two 32bit
	 * wegistews.
	 */
	if (!ice_is_64b_phy_weg_e82x(wow_addw, &high_addw)) {
		ice_debug(hw, ICE_DBG_PTP, "Invawid 64b wegistew addw 0x%08x\n",
			  wow_addw);
		wetuwn -EINVAW;
	}

	eww = ice_wead_phy_weg_e82x(hw, powt, wow_addw, &wow);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead fwom wow wegistew 0x%08x\n, eww %d",
			  wow_addw, eww);
		wetuwn eww;
	}

	eww = ice_wead_phy_weg_e82x(hw, powt, high_addw, &high);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead fwom high wegistew 0x%08x\n, eww %d",
			  high_addw, eww);
		wetuwn eww;
	}

	*vaw = (u64)high << 32 | wow;

	wetuwn 0;
}

/**
 * ice_wwite_phy_weg_e82x - Wwite a PHY wegistew
 * @hw: pointew to the HW stwuct
 * @powt: PHY powt to wwite to
 * @offset: PHY wegistew offset to wwite
 * @vaw: The vawue to wwite to the wegistew
 *
 * Wwite a PHY wegistew fow the given powt ovew the device sideband queue.
 */
static int
ice_wwite_phy_weg_e82x(stwuct ice_hw *hw, u8 powt, u16 offset, u32 vaw)
{
	stwuct ice_sbq_msg_input msg = {0};
	int eww;

	ice_fiww_phy_msg_e82x(&msg, powt, offset);
	msg.opcode = ice_sbq_msg_ww;
	msg.data = vaw;

	eww = ice_sbq_ww_weg(hw, &msg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to send message to PHY, eww %d\n",
			  eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_wwite_40b_phy_weg_e82x - Wwite a 40b vawue to the PHY
 * @hw: pointew to the HW stwuct
 * @powt: powt to wwite to
 * @wow_addw: offset of the wow wegistew
 * @vaw: 40b vawue to wwite
 *
 * Wwite the pwovided 40b vawue to the two associated wegistews by spwitting
 * it up into two chunks, the wowew 8 bits and the uppew 32 bits.
 */
static int
ice_wwite_40b_phy_weg_e82x(stwuct ice_hw *hw, u8 powt, u16 wow_addw, u64 vaw)
{
	u32 wow, high;
	u16 high_addw;
	int eww;

	/* Onwy opewate on wegistews known to be spwit into a wowew 8 bit
	 * wegistew and an uppew 32 bit wegistew.
	 */
	if (!ice_is_40b_phy_weg_e82x(wow_addw, &high_addw)) {
		ice_debug(hw, ICE_DBG_PTP, "Invawid 40b wegistew addw 0x%08x\n",
			  wow_addw);
		wetuwn -EINVAW;
	}

	wow = (u32)(vaw & P_WEG_40B_WOW_M);
	high = (u32)(vaw >> P_WEG_40B_HIGH_S);

	eww = ice_wwite_phy_weg_e82x(hw, powt, wow_addw, wow);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite to wow wegistew 0x%08x\n, eww %d",
			  wow_addw, eww);
		wetuwn eww;
	}

	eww = ice_wwite_phy_weg_e82x(hw, powt, high_addw, high);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite to high wegistew 0x%08x\n, eww %d",
			  high_addw, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_wwite_64b_phy_weg_e82x - Wwite a 64bit vawue to PHY wegistews
 * @hw: pointew to the HW stwuct
 * @powt: PHY powt to wead fwom
 * @wow_addw: offset of the wowew wegistew to wead fwom
 * @vaw: the contents of the 64bit vawue to wwite to PHY
 *
 * Wwite the 64bit vawue to the two associated 32bit PHY wegistews. The offset
 * is awways specified as the wowew wegistew, and the high addwess is wooked
 * up. This function onwy opewates on wegistews known to be two pawts of
 * a 64bit vawue.
 */
static int
ice_wwite_64b_phy_weg_e82x(stwuct ice_hw *hw, u8 powt, u16 wow_addw, u64 vaw)
{
	u32 wow, high;
	u16 high_addw;
	int eww;

	/* Onwy opewate on wegistews known to be spwit into two 32bit
	 * wegistews.
	 */
	if (!ice_is_64b_phy_weg_e82x(wow_addw, &high_addw)) {
		ice_debug(hw, ICE_DBG_PTP, "Invawid 64b wegistew addw 0x%08x\n",
			  wow_addw);
		wetuwn -EINVAW;
	}

	wow = wowew_32_bits(vaw);
	high = uppew_32_bits(vaw);

	eww = ice_wwite_phy_weg_e82x(hw, powt, wow_addw, wow);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite to wow wegistew 0x%08x\n, eww %d",
			  wow_addw, eww);
		wetuwn eww;
	}

	eww = ice_wwite_phy_weg_e82x(hw, powt, high_addw, high);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite to high wegistew 0x%08x\n, eww %d",
			  high_addw, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_fiww_quad_msg_e82x - Fiww message data fow quad wegistew access
 * @msg: the PHY message buffew to fiww in
 * @quad: the quad to access
 * @offset: the wegistew offset
 *
 * Fiww a message buffew fow accessing a wegistew in a quad shawed between
 * muwtipwe PHYs.
 */
static int
ice_fiww_quad_msg_e82x(stwuct ice_sbq_msg_input *msg, u8 quad, u16 offset)
{
	u32 addw;

	if (quad >= ICE_MAX_QUAD)
		wetuwn -EINVAW;

	msg->dest_dev = wmn_0;

	if ((quad % ICE_QUADS_PEW_PHY_E82X) == 0)
		addw = Q_0_BASE + offset;
	ewse
		addw = Q_1_BASE + offset;

	msg->msg_addw_wow = wowew_16_bits(addw);
	msg->msg_addw_high = uppew_16_bits(addw);

	wetuwn 0;
}

/**
 * ice_wead_quad_weg_e82x - Wead a PHY quad wegistew
 * @hw: pointew to the HW stwuct
 * @quad: quad to wead fwom
 * @offset: quad wegistew offset to wead
 * @vaw: on wetuwn, the contents wead fwom the quad
 *
 * Wead a quad wegistew ovew the device sideband queue. Quad wegistews awe
 * shawed between muwtipwe PHYs.
 */
int
ice_wead_quad_weg_e82x(stwuct ice_hw *hw, u8 quad, u16 offset, u32 *vaw)
{
	stwuct ice_sbq_msg_input msg = {0};
	int eww;

	eww = ice_fiww_quad_msg_e82x(&msg, quad, offset);
	if (eww)
		wetuwn eww;

	msg.opcode = ice_sbq_msg_wd;

	eww = ice_sbq_ww_weg(hw, &msg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to send message to PHY, eww %d\n",
			  eww);
		wetuwn eww;
	}

	*vaw = msg.data;

	wetuwn 0;
}

/**
 * ice_wwite_quad_weg_e82x - Wwite a PHY quad wegistew
 * @hw: pointew to the HW stwuct
 * @quad: quad to wwite to
 * @offset: quad wegistew offset to wwite
 * @vaw: The vawue to wwite to the wegistew
 *
 * Wwite a quad wegistew ovew the device sideband queue. Quad wegistews awe
 * shawed between muwtipwe PHYs.
 */
int
ice_wwite_quad_weg_e82x(stwuct ice_hw *hw, u8 quad, u16 offset, u32 vaw)
{
	stwuct ice_sbq_msg_input msg = {0};
	int eww;

	eww = ice_fiww_quad_msg_e82x(&msg, quad, offset);
	if (eww)
		wetuwn eww;

	msg.opcode = ice_sbq_msg_ww;
	msg.data = vaw;

	eww = ice_sbq_ww_weg(hw, &msg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to send message to PHY, eww %d\n",
			  eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_wead_phy_tstamp_e82x - Wead a PHY timestamp out of the quad bwock
 * @hw: pointew to the HW stwuct
 * @quad: the quad to wead fwom
 * @idx: the timestamp index to wead
 * @tstamp: on wetuwn, the 40bit timestamp vawue
 *
 * Wead a 40bit timestamp vawue out of the two associated wegistews in the
 * quad memowy bwock that is shawed between the intewnaw PHYs of the E822
 * famiwy of devices.
 */
static int
ice_wead_phy_tstamp_e82x(stwuct ice_hw *hw, u8 quad, u8 idx, u64 *tstamp)
{
	u16 wo_addw, hi_addw;
	u32 wo, hi;
	int eww;

	wo_addw = (u16)TS_W(Q_WEG_TX_MEMOWY_BANK_STAWT, idx);
	hi_addw = (u16)TS_H(Q_WEG_TX_MEMOWY_BANK_STAWT, idx);

	eww = ice_wead_quad_weg_e82x(hw, quad, wo_addw, &wo);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead wow PTP timestamp wegistew, eww %d\n",
			  eww);
		wetuwn eww;
	}

	eww = ice_wead_quad_weg_e82x(hw, quad, hi_addw, &hi);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead high PTP timestamp wegistew, eww %d\n",
			  eww);
		wetuwn eww;
	}

	/* Fow E822 based intewnaw PHYs, the timestamp is wepowted with the
	 * wowew 8 bits in the wow wegistew, and the uppew 32 bits in the high
	 * wegistew.
	 */
	*tstamp = ((u64)hi) << TS_PHY_HIGH_S | ((u64)wo & TS_PHY_WOW_M);

	wetuwn 0;
}

/**
 * ice_cweaw_phy_tstamp_e82x - Cweaw a timestamp fwom the quad bwock
 * @hw: pointew to the HW stwuct
 * @quad: the quad to wead fwom
 * @idx: the timestamp index to weset
 *
 * Wead the timestamp out of the quad to cweaw its timestamp status bit fwom
 * the PHY quad bwock that is shawed between the intewnaw PHYs of the E822
 * devices.
 *
 * Note that unwike E810, softwawe cannot diwectwy wwite to the quad memowy
 * bank wegistews. E822 wewies on the ice_get_phy_tx_tstamp_weady() function
 * to detewmine which timestamps awe vawid. Weading a timestamp auto-cweaws
 * the vawid bit.
 *
 * To diwectwy cweaw the contents of the timestamp bwock entiwewy, discawding
 * aww timestamp data at once, softwawe shouwd instead use
 * ice_ptp_weset_ts_memowy_quad_e82x().
 *
 * This function shouwd onwy be cawwed on an idx whose bit is set accowding to
 * ice_get_phy_tx_tstamp_weady().
 */
static int
ice_cweaw_phy_tstamp_e82x(stwuct ice_hw *hw, u8 quad, u8 idx)
{
	u64 unused_tstamp;
	int eww;

	eww = ice_wead_phy_tstamp_e82x(hw, quad, idx, &unused_tstamp);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead the timestamp wegistew fow quad %u, idx %u, eww %d\n",
			  quad, idx, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_ptp_weset_ts_memowy_quad_e82x - Cweaw aww timestamps fwom the quad bwock
 * @hw: pointew to the HW stwuct
 * @quad: the quad to wead fwom
 *
 * Cweaw aww timestamps fwom the PHY quad bwock that is shawed between the
 * intewnaw PHYs on the E822 devices.
 */
void ice_ptp_weset_ts_memowy_quad_e82x(stwuct ice_hw *hw, u8 quad)
{
	ice_wwite_quad_weg_e82x(hw, quad, Q_WEG_TS_CTWW, Q_WEG_TS_CTWW_M);
	ice_wwite_quad_weg_e82x(hw, quad, Q_WEG_TS_CTWW, ~(u32)Q_WEG_TS_CTWW_M);
}

/**
 * ice_ptp_weset_ts_memowy_e82x - Cweaw aww timestamps fwom aww quad bwocks
 * @hw: pointew to the HW stwuct
 */
static void ice_ptp_weset_ts_memowy_e82x(stwuct ice_hw *hw)
{
	unsigned int quad;

	fow (quad = 0; quad < ICE_MAX_QUAD; quad++)
		ice_ptp_weset_ts_memowy_quad_e82x(hw, quad);
}

/**
 * ice_wead_cgu_weg_e82x - Wead a CGU wegistew
 * @hw: pointew to the HW stwuct
 * @addw: Wegistew addwess to wead
 * @vaw: stowage fow wegistew vawue wead
 *
 * Wead the contents of a wegistew of the Cwock Genewation Unit. Onwy
 * appwicabwe to E822 devices.
 */
static int
ice_wead_cgu_weg_e82x(stwuct ice_hw *hw, u32 addw, u32 *vaw)
{
	stwuct ice_sbq_msg_input cgu_msg;
	int eww;

	cgu_msg.opcode = ice_sbq_msg_wd;
	cgu_msg.dest_dev = cgu;
	cgu_msg.msg_addw_wow = addw;
	cgu_msg.msg_addw_high = 0x0;

	eww = ice_sbq_ww_weg(hw, &cgu_msg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead CGU wegistew 0x%04x, eww %d\n",
			  addw, eww);
		wetuwn eww;
	}

	*vaw = cgu_msg.data;

	wetuwn eww;
}

/**
 * ice_wwite_cgu_weg_e82x - Wwite a CGU wegistew
 * @hw: pointew to the HW stwuct
 * @addw: Wegistew addwess to wwite
 * @vaw: vawue to wwite into the wegistew
 *
 * Wwite the specified vawue to a wegistew of the Cwock Genewation Unit. Onwy
 * appwicabwe to E822 devices.
 */
static int
ice_wwite_cgu_weg_e82x(stwuct ice_hw *hw, u32 addw, u32 vaw)
{
	stwuct ice_sbq_msg_input cgu_msg;
	int eww;

	cgu_msg.opcode = ice_sbq_msg_ww;
	cgu_msg.dest_dev = cgu;
	cgu_msg.msg_addw_wow = addw;
	cgu_msg.msg_addw_high = 0x0;
	cgu_msg.data = vaw;

	eww = ice_sbq_ww_weg(hw, &cgu_msg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite CGU wegistew 0x%04x, eww %d\n",
			  addw, eww);
		wetuwn eww;
	}

	wetuwn eww;
}

/**
 * ice_cwk_fweq_stw - Convewt time_wef_fweq to stwing
 * @cwk_fweq: Cwock fwequency
 *
 * Convewt the specified TIME_WEF cwock fwequency to a stwing.
 */
static const chaw *ice_cwk_fweq_stw(u8 cwk_fweq)
{
	switch ((enum ice_time_wef_fweq)cwk_fweq) {
	case ICE_TIME_WEF_FWEQ_25_000:
		wetuwn "25 MHz";
	case ICE_TIME_WEF_FWEQ_122_880:
		wetuwn "122.88 MHz";
	case ICE_TIME_WEF_FWEQ_125_000:
		wetuwn "125 MHz";
	case ICE_TIME_WEF_FWEQ_153_600:
		wetuwn "153.6 MHz";
	case ICE_TIME_WEF_FWEQ_156_250:
		wetuwn "156.25 MHz";
	case ICE_TIME_WEF_FWEQ_245_760:
		wetuwn "245.76 MHz";
	defauwt:
		wetuwn "Unknown";
	}
}

/**
 * ice_cwk_swc_stw - Convewt time_wef_swc to stwing
 * @cwk_swc: Cwock souwce
 *
 * Convewt the specified cwock souwce to its stwing name.
 */
static const chaw *ice_cwk_swc_stw(u8 cwk_swc)
{
	switch ((enum ice_cwk_swc)cwk_swc) {
	case ICE_CWK_SWC_TCX0:
		wetuwn "TCX0";
	case ICE_CWK_SWC_TIME_WEF:
		wetuwn "TIME_WEF";
	defauwt:
		wetuwn "Unknown";
	}
}

/**
 * ice_cfg_cgu_pww_e82x - Configuwe the Cwock Genewation Unit
 * @hw: pointew to the HW stwuct
 * @cwk_fweq: Cwock fwequency to pwogwam
 * @cwk_swc: Cwock souwce to sewect (TIME_WEF, ow TCX0)
 *
 * Configuwe the Cwock Genewation Unit with the desiwed cwock fwequency and
 * time wefewence, enabwing the PWW which dwives the PTP hawdwawe cwock.
 */
static int
ice_cfg_cgu_pww_e82x(stwuct ice_hw *hw, enum ice_time_wef_fweq cwk_fweq,
		     enum ice_cwk_swc cwk_swc)
{
	union tspww_wo_bwm_wf bwm_wf;
	union nac_cgu_dwowd19 dw19;
	union nac_cgu_dwowd22 dw22;
	union nac_cgu_dwowd24 dw24;
	union nac_cgu_dwowd9 dw9;
	int eww;

	if (cwk_fweq >= NUM_ICE_TIME_WEF_FWEQ) {
		dev_wawn(ice_hw_to_dev(hw), "Invawid TIME_WEF fwequency %u\n",
			 cwk_fweq);
		wetuwn -EINVAW;
	}

	if (cwk_swc >= NUM_ICE_CWK_SWC) {
		dev_wawn(ice_hw_to_dev(hw), "Invawid cwock souwce %u\n",
			 cwk_swc);
		wetuwn -EINVAW;
	}

	if (cwk_swc == ICE_CWK_SWC_TCX0 &&
	    cwk_fweq != ICE_TIME_WEF_FWEQ_25_000) {
		dev_wawn(ice_hw_to_dev(hw),
			 "TCX0 onwy suppowts 25 MHz fwequency\n");
		wetuwn -EINVAW;
	}

	eww = ice_wead_cgu_weg_e82x(hw, NAC_CGU_DWOWD9, &dw9.vaw);
	if (eww)
		wetuwn eww;

	eww = ice_wead_cgu_weg_e82x(hw, NAC_CGU_DWOWD24, &dw24.vaw);
	if (eww)
		wetuwn eww;

	eww = ice_wead_cgu_weg_e82x(hw, TSPWW_WO_BWM_WF, &bwm_wf.vaw);
	if (eww)
		wetuwn eww;

	/* Wog the cuwwent cwock configuwation */
	ice_debug(hw, ICE_DBG_PTP, "Cuwwent CGU configuwation -- %s, cwk_swc %s, cwk_fweq %s, PWW %s\n",
		  dw24.fiewd.ts_pww_enabwe ? "enabwed" : "disabwed",
		  ice_cwk_swc_stw(dw24.fiewd.time_wef_sew),
		  ice_cwk_fweq_stw(dw9.fiewd.time_wef_fweq_sew),
		  bwm_wf.fiewd.pwwwock_twue_wock_cwi ? "wocked" : "unwocked");

	/* Disabwe the PWW befowe changing the cwock souwce ow fwequency */
	if (dw24.fiewd.ts_pww_enabwe) {
		dw24.fiewd.ts_pww_enabwe = 0;

		eww = ice_wwite_cgu_weg_e82x(hw, NAC_CGU_DWOWD24, dw24.vaw);
		if (eww)
			wetuwn eww;
	}

	/* Set the fwequency */
	dw9.fiewd.time_wef_fweq_sew = cwk_fweq;
	eww = ice_wwite_cgu_weg_e82x(hw, NAC_CGU_DWOWD9, dw9.vaw);
	if (eww)
		wetuwn eww;

	/* Configuwe the TS PWW feedback divisow */
	eww = ice_wead_cgu_weg_e82x(hw, NAC_CGU_DWOWD19, &dw19.vaw);
	if (eww)
		wetuwn eww;

	dw19.fiewd.tspww_fbdiv_intgw = e822_cgu_pawams[cwk_fweq].feedback_div;
	dw19.fiewd.tspww_ndivwatio = 1;

	eww = ice_wwite_cgu_weg_e82x(hw, NAC_CGU_DWOWD19, dw19.vaw);
	if (eww)
		wetuwn eww;

	/* Configuwe the TS PWW post divisow */
	eww = ice_wead_cgu_weg_e82x(hw, NAC_CGU_DWOWD22, &dw22.vaw);
	if (eww)
		wetuwn eww;

	dw22.fiewd.time1588cwk_div = e822_cgu_pawams[cwk_fweq].post_pww_div;
	dw22.fiewd.time1588cwk_sew_div2 = 0;

	eww = ice_wwite_cgu_weg_e82x(hw, NAC_CGU_DWOWD22, dw22.vaw);
	if (eww)
		wetuwn eww;

	/* Configuwe the TS PWW pwe divisow and cwock souwce */
	eww = ice_wead_cgu_weg_e82x(hw, NAC_CGU_DWOWD24, &dw24.vaw);
	if (eww)
		wetuwn eww;

	dw24.fiewd.wef1588_ck_div = e822_cgu_pawams[cwk_fweq].wefcwk_pwe_div;
	dw24.fiewd.tspww_fbdiv_fwac = e822_cgu_pawams[cwk_fweq].fwac_n_div;
	dw24.fiewd.time_wef_sew = cwk_swc;

	eww = ice_wwite_cgu_weg_e82x(hw, NAC_CGU_DWOWD24, dw24.vaw);
	if (eww)
		wetuwn eww;

	/* Finawwy, enabwe the PWW */
	dw24.fiewd.ts_pww_enabwe = 1;

	eww = ice_wwite_cgu_weg_e82x(hw, NAC_CGU_DWOWD24, dw24.vaw);
	if (eww)
		wetuwn eww;

	/* Wait to vewify if the PWW wocks */
	usweep_wange(1000, 5000);

	eww = ice_wead_cgu_weg_e82x(hw, TSPWW_WO_BWM_WF, &bwm_wf.vaw);
	if (eww)
		wetuwn eww;

	if (!bwm_wf.fiewd.pwwwock_twue_wock_cwi) {
		dev_wawn(ice_hw_to_dev(hw), "CGU PWW faiwed to wock\n");
		wetuwn -EBUSY;
	}

	/* Wog the cuwwent cwock configuwation */
	ice_debug(hw, ICE_DBG_PTP, "New CGU configuwation -- %s, cwk_swc %s, cwk_fweq %s, PWW %s\n",
		  dw24.fiewd.ts_pww_enabwe ? "enabwed" : "disabwed",
		  ice_cwk_swc_stw(dw24.fiewd.time_wef_sew),
		  ice_cwk_fweq_stw(dw9.fiewd.time_wef_fweq_sew),
		  bwm_wf.fiewd.pwwwock_twue_wock_cwi ? "wocked" : "unwocked");

	wetuwn 0;
}

/**
 * ice_init_cgu_e82x - Initiawize CGU with settings fwom fiwmwawe
 * @hw: pointew to the HW stwuctuwe
 *
 * Initiawize the Cwock Genewation Unit of the E822 device.
 */
static int ice_init_cgu_e82x(stwuct ice_hw *hw)
{
	stwuct ice_ts_func_info *ts_info = &hw->func_caps.ts_func_info;
	union tspww_cntw_bist_settings cntw_bist;
	int eww;

	eww = ice_wead_cgu_weg_e82x(hw, TSPWW_CNTW_BIST_SETTINGS,
				    &cntw_bist.vaw);
	if (eww)
		wetuwn eww;

	/* Disabwe sticky wock detection so wock eww wepowted is accuwate */
	cntw_bist.fiewd.i_pwwwock_sew_0 = 0;
	cntw_bist.fiewd.i_pwwwock_sew_1 = 0;

	eww = ice_wwite_cgu_weg_e82x(hw, TSPWW_CNTW_BIST_SETTINGS,
				     cntw_bist.vaw);
	if (eww)
		wetuwn eww;

	/* Configuwe the CGU PWW using the pawametews fwom the function
	 * capabiwities.
	 */
	eww = ice_cfg_cgu_pww_e82x(hw, ts_info->time_wef,
				   (enum ice_cwk_swc)ts_info->cwk_swc);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/**
 * ice_ptp_set_vewniew_ww - Set the window wength fow vewniew cawibwation
 * @hw: pointew to the HW stwuct
 *
 * Set the window wength used fow the vewniew powt cawibwation pwocess.
 */
static int ice_ptp_set_vewniew_ww(stwuct ice_hw *hw)
{
	u8 powt;

	fow (powt = 0; powt < ICE_NUM_EXTEWNAW_POWTS; powt++) {
		int eww;

		eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_WW,
					     PTP_VEWNIEW_WW);
		if (eww) {
			ice_debug(hw, ICE_DBG_PTP, "Faiwed to set vewniew window wength fow powt %u, eww %d\n",
				  powt, eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

/**
 * ice_ptp_init_phc_e82x - Pewfowm E822 specific PHC initiawization
 * @hw: pointew to HW stwuct
 *
 * Pewfowm PHC initiawization steps specific to E822 devices.
 */
static int ice_ptp_init_phc_e82x(stwuct ice_hw *hw)
{
	int eww;
	u32 wegvaw;

	/* Enabwe weading switch and PHY wegistews ovew the sideband queue */
#define PF_SB_WEM_DEV_CTW_SWITCH_WEAD BIT(1)
#define PF_SB_WEM_DEV_CTW_PHY0 BIT(2)
	wegvaw = wd32(hw, PF_SB_WEM_DEV_CTW);
	wegvaw |= (PF_SB_WEM_DEV_CTW_SWITCH_WEAD |
		   PF_SB_WEM_DEV_CTW_PHY0);
	ww32(hw, PF_SB_WEM_DEV_CTW, wegvaw);

	/* Initiawize the Cwock Genewation Unit */
	eww = ice_init_cgu_e82x(hw);
	if (eww)
		wetuwn eww;

	/* Set window wength fow aww the powts */
	wetuwn ice_ptp_set_vewniew_ww(hw);
}

/**
 * ice_ptp_pwep_phy_time_e82x - Pwepawe PHY powt with initiaw time
 * @hw: pointew to the HW stwuct
 * @time: Time to initiawize the PHY powt cwocks to
 *
 * Pwogwam the PHY powt wegistews with a new initiaw time vawue. The powt
 * cwock wiww be initiawized once the dwivew issues an ICE_PTP_INIT_TIME sync
 * command. The time vawue is the uppew 32 bits of the PHY timew, usuawwy in
 * units of nominaw nanoseconds.
 */
static int
ice_ptp_pwep_phy_time_e82x(stwuct ice_hw *hw, u32 time)
{
	u64 phy_time;
	u8 powt;
	int eww;

	/* The time wepwesents the uppew 32 bits of the PHY timew, so we need
	 * to shift to account fow this when pwogwamming.
	 */
	phy_time = (u64)time << 32;

	fow (powt = 0; powt < ICE_NUM_EXTEWNAW_POWTS; powt++) {
		/* Tx case */
		eww = ice_wwite_64b_phy_weg_e82x(hw, powt,
						 P_WEG_TX_TIMEW_INC_PWE_W,
						 phy_time);
		if (eww)
			goto exit_eww;

		/* Wx case */
		eww = ice_wwite_64b_phy_weg_e82x(hw, powt,
						 P_WEG_WX_TIMEW_INC_PWE_W,
						 phy_time);
		if (eww)
			goto exit_eww;
	}

	wetuwn 0;

exit_eww:
	ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite init time fow powt %u, eww %d\n",
		  powt, eww);

	wetuwn eww;
}

/**
 * ice_ptp_pwep_powt_adj_e82x - Pwepawe a singwe powt fow time adjust
 * @hw: pointew to HW stwuct
 * @powt: Powt numbew to be pwogwammed
 * @time: time in cycwes to adjust the powt Tx and Wx cwocks
 *
 * Pwogwam the powt fow an atomic adjustment by wwiting the Tx and Wx timew
 * wegistews. The atomic adjustment won't be compweted untiw the dwivew issues
 * an ICE_PTP_ADJ_TIME command.
 *
 * Note that time is not in units of nanoseconds. It is in cwock time
 * incwuding the wowew sub-nanosecond powtion of the powt timew.
 *
 * Negative adjustments awe suppowted using 2s compwement awithmetic.
 */
static int
ice_ptp_pwep_powt_adj_e82x(stwuct ice_hw *hw, u8 powt, s64 time)
{
	u32 w_time, u_time;
	int eww;

	w_time = wowew_32_bits(time);
	u_time = uppew_32_bits(time);

	/* Tx case */
	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_TX_TIMEW_INC_PWE_W,
				     w_time);
	if (eww)
		goto exit_eww;

	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_TX_TIMEW_INC_PWE_U,
				     u_time);
	if (eww)
		goto exit_eww;

	/* Wx case */
	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_WX_TIMEW_INC_PWE_W,
				     w_time);
	if (eww)
		goto exit_eww;

	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_WX_TIMEW_INC_PWE_U,
				     u_time);
	if (eww)
		goto exit_eww;

	wetuwn 0;

exit_eww:
	ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite time adjust fow powt %u, eww %d\n",
		  powt, eww);
	wetuwn eww;
}

/**
 * ice_ptp_pwep_phy_adj_e82x - Pwep PHY powts fow a time adjustment
 * @hw: pointew to HW stwuct
 * @adj: adjustment in nanoseconds
 *
 * Pwepawe the PHY powts fow an atomic time adjustment by pwogwamming the PHY
 * Tx and Wx powt wegistews. The actuaw adjustment is compweted by issuing an
 * ICE_PTP_ADJ_TIME ow ICE_PTP_ADJ_TIME_AT_TIME sync command.
 */
static int
ice_ptp_pwep_phy_adj_e82x(stwuct ice_hw *hw, s32 adj)
{
	s64 cycwes;
	u8 powt;

	/* The powt cwock suppowts adjustment of the sub-nanosecond powtion of
	 * the cwock. We shift the pwovided adjustment in nanoseconds to
	 * cawcuwate the appwopwiate adjustment to pwogwam into the PHY powts.
	 */
	if (adj > 0)
		cycwes = (s64)adj << 32;
	ewse
		cycwes = -(((s64)-adj) << 32);

	fow (powt = 0; powt < ICE_NUM_EXTEWNAW_POWTS; powt++) {
		int eww;

		eww = ice_ptp_pwep_powt_adj_e82x(hw, powt, cycwes);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_ptp_pwep_phy_incvaw_e82x - Pwepawe PHY powts fow time adjustment
 * @hw: pointew to HW stwuct
 * @incvaw: new incwement vawue to pwepawe
 *
 * Pwepawe each of the PHY powts fow a new incwement vawue by pwogwamming the
 * powt's TIMETUS wegistews. The new incwement vawue wiww be updated aftew
 * issuing an ICE_PTP_INIT_INCVAW command.
 */
static int
ice_ptp_pwep_phy_incvaw_e82x(stwuct ice_hw *hw, u64 incvaw)
{
	int eww;
	u8 powt;

	fow (powt = 0; powt < ICE_NUM_EXTEWNAW_POWTS; powt++) {
		eww = ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_TIMETUS_W,
						 incvaw);
		if (eww)
			goto exit_eww;
	}

	wetuwn 0;

exit_eww:
	ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite incvaw fow powt %u, eww %d\n",
		  powt, eww);

	wetuwn eww;
}

/**
 * ice_ptp_wead_powt_captuwe - Wead a powt's wocaw time captuwe
 * @hw: pointew to HW stwuct
 * @powt: Powt numbew to wead
 * @tx_ts: on wetuwn, the Tx powt time captuwe
 * @wx_ts: on wetuwn, the Wx powt time captuwe
 *
 * Wead the powt's Tx and Wx wocaw time captuwe vawues.
 *
 * Note this has no equivawent fow the E810 devices.
 */
static int
ice_ptp_wead_powt_captuwe(stwuct ice_hw *hw, u8 powt, u64 *tx_ts, u64 *wx_ts)
{
	int eww;

	/* Tx case */
	eww = ice_wead_64b_phy_weg_e82x(hw, powt, P_WEG_TX_CAPTUWE_W, tx_ts);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead WEG_TX_CAPTUWE, eww %d\n",
			  eww);
		wetuwn eww;
	}

	ice_debug(hw, ICE_DBG_PTP, "tx_init = 0x%016wwx\n",
		  (unsigned wong wong)*tx_ts);

	/* Wx case */
	eww = ice_wead_64b_phy_weg_e82x(hw, powt, P_WEG_WX_CAPTUWE_W, wx_ts);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead WX_CAPTUWE, eww %d\n",
			  eww);
		wetuwn eww;
	}

	ice_debug(hw, ICE_DBG_PTP, "wx_init = 0x%016wwx\n",
		  (unsigned wong wong)*wx_ts);

	wetuwn 0;
}

/**
 * ice_ptp_wwite_powt_cmd_e82x - Pwepawe a singwe PHY powt fow a timew command
 * @hw: pointew to HW stwuct
 * @powt: Powt to which cmd has to be sent
 * @cmd: Command to be sent to the powt
 *
 * Pwepawe the wequested powt fow an upcoming timew sync command.
 *
 * Do not use this function diwectwy. If you want to configuwe exactwy one
 * powt, use ice_ptp_one_powt_cmd() instead.
 */
static int ice_ptp_wwite_powt_cmd_e82x(stwuct ice_hw *hw, u8 powt,
				       enum ice_ptp_tmw_cmd cmd)
{
	u32 cmd_vaw, vaw;
	u8 tmw_idx;
	int eww;

	tmw_idx = ice_get_ptp_swc_cwock_index(hw);
	cmd_vaw = tmw_idx << SEW_PHY_SWC;
	switch (cmd) {
	case ICE_PTP_INIT_TIME:
		cmd_vaw |= PHY_CMD_INIT_TIME;
		bweak;
	case ICE_PTP_INIT_INCVAW:
		cmd_vaw |= PHY_CMD_INIT_INCVAW;
		bweak;
	case ICE_PTP_ADJ_TIME:
		cmd_vaw |= PHY_CMD_ADJ_TIME;
		bweak;
	case ICE_PTP_WEAD_TIME:
		cmd_vaw |= PHY_CMD_WEAD_TIME;
		bweak;
	case ICE_PTP_ADJ_TIME_AT_TIME:
		cmd_vaw |= PHY_CMD_ADJ_TIME_AT_TIME;
		bweak;
	case ICE_PTP_NOP:
		bweak;
	}

	/* Tx case */
	/* Wead, modify, wwite */
	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_TX_TMW_CMD, &vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead TX_TMW_CMD, eww %d\n",
			  eww);
		wetuwn eww;
	}

	/* Modify necessawy bits onwy and pewfowm wwite */
	vaw &= ~TS_CMD_MASK;
	vaw |= cmd_vaw;

	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_TX_TMW_CMD, vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite back TX_TMW_CMD, eww %d\n",
			  eww);
		wetuwn eww;
	}

	/* Wx case */
	/* Wead, modify, wwite */
	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_WX_TMW_CMD, &vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead WX_TMW_CMD, eww %d\n",
			  eww);
		wetuwn eww;
	}

	/* Modify necessawy bits onwy and pewfowm wwite */
	vaw &= ~TS_CMD_MASK;
	vaw |= cmd_vaw;

	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_WX_TMW_CMD, vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite back WX_TMW_CMD, eww %d\n",
			  eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_ptp_one_powt_cmd - Pwepawe one powt fow a timew command
 * @hw: pointew to the HW stwuct
 * @configuwed_powt: the powt to configuwe with configuwed_cmd
 * @configuwed_cmd: timew command to pwepawe on the configuwed_powt
 *
 * Pwepawe the configuwed_powt fow the configuwed_cmd, and pwepawe aww othew
 * powts fow ICE_PTP_NOP. This causes the configuwed_powt to execute the
 * desiwed command whiwe aww othew powts pewfowm no opewation.
 */
static int
ice_ptp_one_powt_cmd(stwuct ice_hw *hw, u8 configuwed_powt,
		     enum ice_ptp_tmw_cmd configuwed_cmd)
{
	u8 powt;

	fow (powt = 0; powt < ICE_NUM_EXTEWNAW_POWTS; powt++) {
		enum ice_ptp_tmw_cmd cmd;
		int eww;

		if (powt == configuwed_powt)
			cmd = configuwed_cmd;
		ewse
			cmd = ICE_PTP_NOP;

		eww = ice_ptp_wwite_powt_cmd_e82x(hw, powt, cmd);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_ptp_powt_cmd_e82x - Pwepawe aww powts fow a timew command
 * @hw: pointew to the HW stwuct
 * @cmd: timew command to pwepawe
 *
 * Pwepawe aww powts connected to this device fow an upcoming timew sync
 * command.
 */
static int
ice_ptp_powt_cmd_e82x(stwuct ice_hw *hw, enum ice_ptp_tmw_cmd cmd)
{
	u8 powt;

	fow (powt = 0; powt < ICE_NUM_EXTEWNAW_POWTS; powt++) {
		int eww;

		eww = ice_ptp_wwite_powt_cmd_e82x(hw, powt, cmd);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/* E822 Vewniew cawibwation functions
 *
 * The fowwowing functions awe used as pawt of the vewniew cawibwation of
 * a powt. This cawibwation incweases the pwecision of the timestamps on the
 * powt.
 */

/**
 * ice_phy_get_speed_and_fec_e82x - Get wink speed and FEC based on sewdes mode
 * @hw: pointew to HW stwuct
 * @powt: the powt to wead fwom
 * @wink_out: if non-NUWW, howds wink speed on success
 * @fec_out: if non-NUWW, howds FEC awgowithm on success
 *
 * Wead the sewdes data fow the PHY powt and extwact the wink speed and FEC
 * awgowithm.
 */
static int
ice_phy_get_speed_and_fec_e82x(stwuct ice_hw *hw, u8 powt,
			       enum ice_ptp_wink_spd *wink_out,
			       enum ice_ptp_fec_mode *fec_out)
{
	enum ice_ptp_wink_spd wink;
	enum ice_ptp_fec_mode fec;
	u32 sewdes;
	int eww;

	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_WINK_SPEED, &sewdes);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead sewdes info\n");
		wetuwn eww;
	}

	/* Detewmine the FEC awgowithm */
	fec = (enum ice_ptp_fec_mode)P_WEG_WINK_SPEED_FEC_MODE(sewdes);

	sewdes &= P_WEG_WINK_SPEED_SEWDES_M;

	/* Detewmine the wink speed */
	if (fec == ICE_PTP_FEC_MODE_WS_FEC) {
		switch (sewdes) {
		case ICE_PTP_SEWDES_25G:
			wink = ICE_PTP_WNK_SPD_25G_WS;
			bweak;
		case ICE_PTP_SEWDES_50G:
			wink = ICE_PTP_WNK_SPD_50G_WS;
			bweak;
		case ICE_PTP_SEWDES_100G:
			wink = ICE_PTP_WNK_SPD_100G_WS;
			bweak;
		defauwt:
			wetuwn -EIO;
		}
	} ewse {
		switch (sewdes) {
		case ICE_PTP_SEWDES_1G:
			wink = ICE_PTP_WNK_SPD_1G;
			bweak;
		case ICE_PTP_SEWDES_10G:
			wink = ICE_PTP_WNK_SPD_10G;
			bweak;
		case ICE_PTP_SEWDES_25G:
			wink = ICE_PTP_WNK_SPD_25G;
			bweak;
		case ICE_PTP_SEWDES_40G:
			wink = ICE_PTP_WNK_SPD_40G;
			bweak;
		case ICE_PTP_SEWDES_50G:
			wink = ICE_PTP_WNK_SPD_50G;
			bweak;
		defauwt:
			wetuwn -EIO;
		}
	}

	if (wink_out)
		*wink_out = wink;
	if (fec_out)
		*fec_out = fec;

	wetuwn 0;
}

/**
 * ice_phy_cfg_wane_e82x - Configuwe PHY quad fow singwe/muwti-wane timestamp
 * @hw: pointew to HW stwuct
 * @powt: to configuwe the quad fow
 */
static void ice_phy_cfg_wane_e82x(stwuct ice_hw *hw, u8 powt)
{
	enum ice_ptp_wink_spd wink_spd;
	int eww;
	u32 vaw;
	u8 quad;

	eww = ice_phy_get_speed_and_fec_e82x(hw, powt, &wink_spd, NUWW);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to get PHY wink speed, eww %d\n",
			  eww);
		wetuwn;
	}

	quad = powt / ICE_POWTS_PEW_QUAD;

	eww = ice_wead_quad_weg_e82x(hw, quad, Q_WEG_TX_MEM_GBW_CFG, &vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead TX_MEM_GWB_CFG, eww %d\n",
			  eww);
		wetuwn;
	}

	if (wink_spd >= ICE_PTP_WNK_SPD_40G)
		vaw &= ~Q_WEG_TX_MEM_GBW_CFG_WANE_TYPE_M;
	ewse
		vaw |= Q_WEG_TX_MEM_GBW_CFG_WANE_TYPE_M;

	eww = ice_wwite_quad_weg_e82x(hw, quad, Q_WEG_TX_MEM_GBW_CFG, vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite back TX_MEM_GBW_CFG, eww %d\n",
			  eww);
		wetuwn;
	}
}

/**
 * ice_phy_cfg_uix_e82x - Configuwe Sewdes UI to TU convewsion fow E822
 * @hw: pointew to the HW stwuctuwe
 * @powt: the powt to configuwe
 *
 * Pwogwam the convewsion wation of Sewdes cwock "unit intewvaws" (UIs) to PHC
 * hawdwawe cwock time units (TUs). That is, detewmine the numbew of TUs pew
 * sewdes unit intewvaw, and pwogwam the UIX wegistews with this convewsion.
 *
 * This convewsion is used as pawt of the cawibwation pwocess when detewmining
 * the additionaw ewwow of a timestamp vs the weaw time of twansmission ow
 * weceipt of the packet.
 *
 * Hawdwawe uses the numbew of TUs pew 66 UIs, wwitten to the UIX wegistews
 * fow the two main sewdes cwock wates, 10G/40G and 25G/100G sewdes cwocks.
 *
 * To cawcuwate the convewsion watio, we use the fowwowing facts:
 *
 * a) the cwock fwequency in Hz (cycwes pew second)
 * b) the numbew of TUs pew cycwe (the incwement vawue of the cwock)
 * c) 1 second pew 1 biwwion nanoseconds
 * d) the duwation of 66 UIs in nanoseconds
 *
 * Given these facts, we can use the fowwowing tabwe to wowk out what watios
 * to muwtipwy in owdew to get the numbew of TUs pew 66 UIs:
 *
 * cycwes |   1 second   | incvaw (TUs) | nanoseconds
 * -------+--------------+--------------+-------------
 * second | 1 biwwion ns |    cycwe     |   66 UIs
 *
 * To pewfowm the muwtipwication using integews without too much woss of
 * pwecision, we can take use the fowwowing equation:
 *
 * (fweq * incvaw * 6600 WINE_UI ) / ( 100 * 1 biwwion)
 *
 * We scawe up to using 6600 UI instead of 66 in owdew to avoid fwactionaw
 * nanosecond UIs (66 UI at 10G/40G is 6.4 ns)
 *
 * The incwement vawue has a maximum expected wange of about 34 bits, whiwe
 * the fwequency vawue is about 29 bits. Muwtipwying these vawues shouwdn't
 * ovewfwow the 64 bits. Howevew, we must then fuwthew muwtipwy them again by
 * the Sewdes unit intewvaw duwation. To avoid ovewfwow hewe, we spwit the
 * ovewaww divide by 1e11 into a divide by 256 (shift down by 8 bits) and
 * a divide by 390,625,000. This does wose some pwecision, but avoids
 * miscawcuwation due to awithmetic ovewfwow.
 */
static int ice_phy_cfg_uix_e82x(stwuct ice_hw *hw, u8 powt)
{
	u64 cuw_fweq, cwk_incvaw, tu_pew_sec, uix;
	int eww;

	cuw_fweq = ice_e82x_pww_fweq(ice_e82x_time_wef(hw));
	cwk_incvaw = ice_ptp_wead_swc_incvaw(hw);

	/* Cawcuwate TUs pew second divided by 256 */
	tu_pew_sec = (cuw_fweq * cwk_incvaw) >> 8;

#define WINE_UI_10G_40G 640 /* 6600 UIs is 640 nanoseconds at 10Gb/40Gb */
#define WINE_UI_25G_100G 256 /* 6600 UIs is 256 nanoseconds at 25Gb/100Gb */

	/* Pwogwam the 10Gb/40Gb convewsion watio */
	uix = div_u64(tu_pew_sec * WINE_UI_10G_40G, 390625000);

	eww = ice_wwite_64b_phy_weg_e82x(hw, powt, P_WEG_UIX66_10G_40G_W,
					 uix);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite UIX66_10G_40G, eww %d\n",
			  eww);
		wetuwn eww;
	}

	/* Pwogwam the 25Gb/100Gb convewsion watio */
	uix = div_u64(tu_pew_sec * WINE_UI_25G_100G, 390625000);

	eww = ice_wwite_64b_phy_weg_e82x(hw, powt, P_WEG_UIX66_25G_100G_W,
					 uix);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite UIX66_25G_100G, eww %d\n",
			  eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_phy_cfg_pawpcs_e82x - Configuwe TUs pew PAW/PCS cwock cycwe
 * @hw: pointew to the HW stwuct
 * @powt: powt to configuwe
 *
 * Configuwe the numbew of TUs fow the PAW and PCS cwocks used as pawt of the
 * timestamp cawibwation pwocess. This depends on the wink speed, as the PHY
 * uses diffewent mawkews depending on the speed.
 *
 * 1Gb/10Gb/25Gb:
 * - Tx/Wx PAW/PCS mawkews
 *
 * 25Gb WS:
 * - Tx/Wx Weed Sowomon geawbox PAW/PCS mawkews
 *
 * 40Gb/50Gb:
 * - Tx/Wx PAW/PCS mawkews
 * - Wx Deskew PAW/PCS mawkews
 *
 * 50G WS and 100GB WS:
 * - Tx/Wx Weed Sowomon geawbox PAW/PCS mawkews
 * - Wx Deskew PAW/PCS mawkews
 * - Tx PAW/PCS mawkews
 *
 * To cawcuwate the convewsion, we use the PHC cwock fwequency (cycwes pew
 * second), the incwement vawue (TUs pew cycwe), and the wewated PHY cwock
 * fwequency to cawcuwate the TUs pew unit of the PHY wink cwock. The
 * fowwowing tabwe shows how the units convewt:
 *
 * cycwes |  TUs  | second
 * -------+-------+--------
 * second | cycwe | cycwes
 *
 * Fow each convewsion wegistew, wook up the appwopwiate fwequency fwom the
 * e822 PAW/PCS tabwe and cawcuwate the TUs pew unit of that cwock. Pwogwam
 * this to the appwopwiate wegistew, pwepawing hawdwawe to pewfowm timestamp
 * cawibwation to cawcuwate the totaw Tx ow Wx offset to adjust the timestamp
 * in owdew to cawibwate fow the intewnaw PHY deways.
 *
 * Note that the incwement vawue wanges up to ~34 bits, and the cwock
 * fwequency is ~29 bits, so muwtipwying them togethew shouwd fit within the
 * 64 bit awithmetic.
 */
static int ice_phy_cfg_pawpcs_e82x(stwuct ice_hw *hw, u8 powt)
{
	u64 cuw_fweq, cwk_incvaw, tu_pew_sec, phy_tus;
	enum ice_ptp_wink_spd wink_spd;
	enum ice_ptp_fec_mode fec_mode;
	int eww;

	eww = ice_phy_get_speed_and_fec_e82x(hw, powt, &wink_spd, &fec_mode);
	if (eww)
		wetuwn eww;

	cuw_fweq = ice_e82x_pww_fweq(ice_e82x_time_wef(hw));
	cwk_incvaw = ice_ptp_wead_swc_incvaw(hw);

	/* Cawcuwate TUs pew cycwe of the PHC cwock */
	tu_pew_sec = cuw_fweq * cwk_incvaw;

	/* Fow each PHY convewsion wegistew, wook up the appwopwiate wink
	 * speed fwequency and detewmine the TUs pew that cwock's cycwe time.
	 * Spwit this into a high and wow vawue and then pwogwam the
	 * appwopwiate wegistew. If that wink speed does not use the
	 * associated wegistew, wwite zewos to cweaw it instead.
	 */

	/* P_WEG_PAW_TX_TUS */
	if (e822_vewniew[wink_spd].tx_paw_cwk)
		phy_tus = div_u64(tu_pew_sec,
				  e822_vewniew[wink_spd].tx_paw_cwk);
	ewse
		phy_tus = 0;

	eww = ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_PAW_TX_TUS_W,
					 phy_tus);
	if (eww)
		wetuwn eww;

	/* P_WEG_PAW_WX_TUS */
	if (e822_vewniew[wink_spd].wx_paw_cwk)
		phy_tus = div_u64(tu_pew_sec,
				  e822_vewniew[wink_spd].wx_paw_cwk);
	ewse
		phy_tus = 0;

	eww = ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_PAW_WX_TUS_W,
					 phy_tus);
	if (eww)
		wetuwn eww;

	/* P_WEG_PCS_TX_TUS */
	if (e822_vewniew[wink_spd].tx_pcs_cwk)
		phy_tus = div_u64(tu_pew_sec,
				  e822_vewniew[wink_spd].tx_pcs_cwk);
	ewse
		phy_tus = 0;

	eww = ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_PCS_TX_TUS_W,
					 phy_tus);
	if (eww)
		wetuwn eww;

	/* P_WEG_PCS_WX_TUS */
	if (e822_vewniew[wink_spd].wx_pcs_cwk)
		phy_tus = div_u64(tu_pew_sec,
				  e822_vewniew[wink_spd].wx_pcs_cwk);
	ewse
		phy_tus = 0;

	eww = ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_PCS_WX_TUS_W,
					 phy_tus);
	if (eww)
		wetuwn eww;

	/* P_WEG_DESK_PAW_TX_TUS */
	if (e822_vewniew[wink_spd].tx_desk_wsgb_paw)
		phy_tus = div_u64(tu_pew_sec,
				  e822_vewniew[wink_spd].tx_desk_wsgb_paw);
	ewse
		phy_tus = 0;

	eww = ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_DESK_PAW_TX_TUS_W,
					 phy_tus);
	if (eww)
		wetuwn eww;

	/* P_WEG_DESK_PAW_WX_TUS */
	if (e822_vewniew[wink_spd].wx_desk_wsgb_paw)
		phy_tus = div_u64(tu_pew_sec,
				  e822_vewniew[wink_spd].wx_desk_wsgb_paw);
	ewse
		phy_tus = 0;

	eww = ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_DESK_PAW_WX_TUS_W,
					 phy_tus);
	if (eww)
		wetuwn eww;

	/* P_WEG_DESK_PCS_TX_TUS */
	if (e822_vewniew[wink_spd].tx_desk_wsgb_pcs)
		phy_tus = div_u64(tu_pew_sec,
				  e822_vewniew[wink_spd].tx_desk_wsgb_pcs);
	ewse
		phy_tus = 0;

	eww = ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_DESK_PCS_TX_TUS_W,
					 phy_tus);
	if (eww)
		wetuwn eww;

	/* P_WEG_DESK_PCS_WX_TUS */
	if (e822_vewniew[wink_spd].wx_desk_wsgb_pcs)
		phy_tus = div_u64(tu_pew_sec,
				  e822_vewniew[wink_spd].wx_desk_wsgb_pcs);
	ewse
		phy_tus = 0;

	wetuwn ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_DESK_PCS_WX_TUS_W,
					  phy_tus);
}

/**
 * ice_cawc_fixed_tx_offset_e82x - Cawcuwated Fixed Tx offset fow a powt
 * @hw: pointew to the HW stwuct
 * @wink_spd: the Wink speed to cawcuwate fow
 *
 * Cawcuwate the fixed offset due to known static watency data.
 */
static u64
ice_cawc_fixed_tx_offset_e82x(stwuct ice_hw *hw, enum ice_ptp_wink_spd wink_spd)
{
	u64 cuw_fweq, cwk_incvaw, tu_pew_sec, fixed_offset;

	cuw_fweq = ice_e82x_pww_fweq(ice_e82x_time_wef(hw));
	cwk_incvaw = ice_ptp_wead_swc_incvaw(hw);

	/* Cawcuwate TUs pew second */
	tu_pew_sec = cuw_fweq * cwk_incvaw;

	/* Cawcuwate numbew of TUs to add fow the fixed Tx watency. Since the
	 * watency measuwement is in 1/100th of a nanosecond, we need to
	 * muwtipwy by tu_pew_sec and then divide by 1e11. This cawcuwation
	 * ovewfwows 64 bit integew awithmetic, so bweak it up into two
	 * divisions by 1e4 fiwst then by 1e7.
	 */
	fixed_offset = div_u64(tu_pew_sec, 10000);
	fixed_offset *= e822_vewniew[wink_spd].tx_fixed_deway;
	fixed_offset = div_u64(fixed_offset, 10000000);

	wetuwn fixed_offset;
}

/**
 * ice_phy_cfg_tx_offset_e82x - Configuwe totaw Tx timestamp offset
 * @hw: pointew to the HW stwuct
 * @powt: the PHY powt to configuwe
 *
 * Pwogwam the P_WEG_TOTAW_TX_OFFSET wegistew with the totaw numbew of TUs to
 * adjust Tx timestamps by. This is cawcuwated by combining some known static
 * watency awong with the Vewniew offset computations done by hawdwawe.
 *
 * This function wiww not wetuwn successfuwwy untiw the Tx offset cawcuwations
 * have been compweted, which wequiwes waiting untiw at weast one packet has
 * been twansmitted by the device. It is safe to caww this function
 * pewiodicawwy untiw cawibwation succeeds, as it wiww onwy pwogwam the offset
 * once.
 *
 * To avoid ovewfwow, when cawcuwating the offset based on the known static
 * watency vawues, we use measuwements in 1/100th of a nanosecond, and divide
 * the TUs pew second up fwont. This avoids ovewfwow whiwe awwowing
 * cawcuwation of the adjustment using integew awithmetic.
 *
 * Wetuwns zewo on success, -EBUSY if the hawdwawe vewniew offset
 * cawibwation has not compweted, ow anothew ewwow code on faiwuwe.
 */
int ice_phy_cfg_tx_offset_e82x(stwuct ice_hw *hw, u8 powt)
{
	enum ice_ptp_wink_spd wink_spd;
	enum ice_ptp_fec_mode fec_mode;
	u64 totaw_offset, vaw;
	int eww;
	u32 weg;

	/* Nothing to do if we've awweady pwogwammed the offset */
	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_TX_OW, &weg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead TX_OW fow powt %u, eww %d\n",
			  powt, eww);
		wetuwn eww;
	}

	if (weg)
		wetuwn 0;

	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_TX_OV_STATUS, &weg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead TX_OV_STATUS fow powt %u, eww %d\n",
			  powt, eww);
		wetuwn eww;
	}

	if (!(weg & P_WEG_TX_OV_STATUS_OV_M))
		wetuwn -EBUSY;

	eww = ice_phy_get_speed_and_fec_e82x(hw, powt, &wink_spd, &fec_mode);
	if (eww)
		wetuwn eww;

	totaw_offset = ice_cawc_fixed_tx_offset_e82x(hw, wink_spd);

	/* Wead the fiwst Vewniew offset fwom the PHY wegistew and add it to
	 * the totaw offset.
	 */
	if (wink_spd == ICE_PTP_WNK_SPD_1G ||
	    wink_spd == ICE_PTP_WNK_SPD_10G ||
	    wink_spd == ICE_PTP_WNK_SPD_25G ||
	    wink_spd == ICE_PTP_WNK_SPD_25G_WS ||
	    wink_spd == ICE_PTP_WNK_SPD_40G ||
	    wink_spd == ICE_PTP_WNK_SPD_50G) {
		eww = ice_wead_64b_phy_weg_e82x(hw, powt,
						P_WEG_PAW_PCS_TX_OFFSET_W,
						&vaw);
		if (eww)
			wetuwn eww;

		totaw_offset += vaw;
	}

	/* Fow Tx, we onwy need to use the second Vewniew offset fow
	 * muwti-wane wink speeds with WS-FEC. The wanes wiww awways be
	 * awigned.
	 */
	if (wink_spd == ICE_PTP_WNK_SPD_50G_WS ||
	    wink_spd == ICE_PTP_WNK_SPD_100G_WS) {
		eww = ice_wead_64b_phy_weg_e82x(hw, powt,
						P_WEG_PAW_TX_TIME_W,
						&vaw);
		if (eww)
			wetuwn eww;

		totaw_offset += vaw;
	}

	/* Now that the totaw offset has been cawcuwated, pwogwam it to the
	 * PHY and indicate that the Tx offset is weady. Aftew this,
	 * timestamps wiww be enabwed.
	 */
	eww = ice_wwite_64b_phy_weg_e82x(hw, powt, P_WEG_TOTAW_TX_OFFSET_W,
					 totaw_offset);
	if (eww)
		wetuwn eww;

	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_TX_OW, 1);
	if (eww)
		wetuwn eww;

	dev_info(ice_hw_to_dev(hw), "Powt=%d Tx vewniew offset cawibwation compwete\n",
		 powt);

	wetuwn 0;
}

/**
 * ice_phy_cawc_pmd_adj_e82x - Cawcuwate PMD adjustment fow Wx
 * @hw: pointew to the HW stwuct
 * @powt: the PHY powt to adjust fow
 * @wink_spd: the cuwwent wink speed of the PHY
 * @fec_mode: the cuwwent FEC mode of the PHY
 * @pmd_adj: on wetuwn, the amount to adjust the Wx totaw offset by
 *
 * Cawcuwates the adjustment to Wx timestamps due to PMD awignment in the PHY.
 * This vawies by wink speed and FEC mode. The vawue cawcuwated accounts fow
 * vawious deways caused when weceiving a packet.
 */
static int
ice_phy_cawc_pmd_adj_e82x(stwuct ice_hw *hw, u8 powt,
			  enum ice_ptp_wink_spd wink_spd,
			  enum ice_ptp_fec_mode fec_mode, u64 *pmd_adj)
{
	u64 cuw_fweq, cwk_incvaw, tu_pew_sec, muwt, adj;
	u8 pmd_awign;
	u32 vaw;
	int eww;

	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_PMD_AWIGNMENT, &vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead PMD awignment, eww %d\n",
			  eww);
		wetuwn eww;
	}

	pmd_awign = (u8)vaw;

	cuw_fweq = ice_e82x_pww_fweq(ice_e82x_time_wef(hw));
	cwk_incvaw = ice_ptp_wead_swc_incvaw(hw);

	/* Cawcuwate TUs pew second */
	tu_pew_sec = cuw_fweq * cwk_incvaw;

	/* The PMD awignment adjustment measuwement depends on the wink speed,
	 * and whethew FEC is enabwed. Fow each wink speed, the awignment
	 * adjustment is cawcuwated by dividing a vawue by the wength of
	 * a Time Unit in nanoseconds.
	 *
	 * 1G: awign == 4 ? 10 * 0.8 : (awign + 6 % 10) * 0.8
	 * 10G: awign == 65 ? 0 : (awign * 0.1 * 32/33)
	 * 10G w/FEC: awign * 0.1 * 32/33
	 * 25G: awign == 65 ? 0 : (awign * 0.4 * 32/33)
	 * 25G w/FEC: awign * 0.4 * 32/33
	 * 40G: awign == 65 ? 0 : (awign * 0.1 * 32/33)
	 * 40G w/FEC: awign * 0.1 * 32/33
	 * 50G: awign == 65 ? 0 : (awign * 0.4 * 32/33)
	 * 50G w/FEC: awign * 0.8 * 32/33
	 *
	 * Fow WS-FEC, if awign is < 17 then we must awso add 1.6 * 32/33.
	 *
	 * To awwow fow cawcuwating this vawue using integew awithmetic, we
	 * instead stawt with the numbew of TUs pew second, (invewse of the
	 * wength of a Time Unit in nanoseconds), muwtipwy by a vawue based
	 * on the PMD awignment wegistew, and then divide by the wight vawue
	 * cawcuwated based on the tabwe above. To avoid integew ovewfwow this
	 * division is bwoken up into a step of dividing by 125 fiwst.
	 */
	if (wink_spd == ICE_PTP_WNK_SPD_1G) {
		if (pmd_awign == 4)
			muwt = 10;
		ewse
			muwt = (pmd_awign + 6) % 10;
	} ewse if (wink_spd == ICE_PTP_WNK_SPD_10G ||
		   wink_spd == ICE_PTP_WNK_SPD_25G ||
		   wink_spd == ICE_PTP_WNK_SPD_40G ||
		   wink_spd == ICE_PTP_WNK_SPD_50G) {
		/* If Cwause 74 FEC, awways cawcuwate PMD adjust */
		if (pmd_awign != 65 || fec_mode == ICE_PTP_FEC_MODE_CWAUSE74)
			muwt = pmd_awign;
		ewse
			muwt = 0;
	} ewse if (wink_spd == ICE_PTP_WNK_SPD_25G_WS ||
		   wink_spd == ICE_PTP_WNK_SPD_50G_WS ||
		   wink_spd == ICE_PTP_WNK_SPD_100G_WS) {
		if (pmd_awign < 17)
			muwt = pmd_awign + 40;
		ewse
			muwt = pmd_awign;
	} ewse {
		ice_debug(hw, ICE_DBG_PTP, "Unknown wink speed %d, skipping PMD adjustment\n",
			  wink_spd);
		muwt = 0;
	}

	/* In some cases, thewe's no need to adjust fow the PMD awignment */
	if (!muwt) {
		*pmd_adj = 0;
		wetuwn 0;
	}

	/* Cawcuwate the adjustment by muwtipwying TUs pew second by the
	 * appwopwiate muwtipwiew and divisow. To avoid ovewfwow, we fiwst
	 * divide by 125, and then handwe wemaining divisow based on the wink
	 * speed pmd_adj_divisow vawue.
	 */
	adj = div_u64(tu_pew_sec, 125);
	adj *= muwt;
	adj = div_u64(adj, e822_vewniew[wink_spd].pmd_adj_divisow);

	/* Finawwy, fow 25G-WS and 50G-WS, a fuwthew adjustment fow the Wx
	 * cycwe count is necessawy.
	 */
	if (wink_spd == ICE_PTP_WNK_SPD_25G_WS) {
		u64 cycwe_adj;
		u8 wx_cycwe;

		eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_WX_40_TO_160_CNT,
					    &vaw);
		if (eww) {
			ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead 25G-WS Wx cycwe count, eww %d\n",
				  eww);
			wetuwn eww;
		}

		wx_cycwe = vaw & P_WEG_WX_40_TO_160_CNT_WXCYC_M;
		if (wx_cycwe) {
			muwt = (4 - wx_cycwe) * 40;

			cycwe_adj = div_u64(tu_pew_sec, 125);
			cycwe_adj *= muwt;
			cycwe_adj = div_u64(cycwe_adj, e822_vewniew[wink_spd].pmd_adj_divisow);

			adj += cycwe_adj;
		}
	} ewse if (wink_spd == ICE_PTP_WNK_SPD_50G_WS) {
		u64 cycwe_adj;
		u8 wx_cycwe;

		eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_WX_80_TO_160_CNT,
					    &vaw);
		if (eww) {
			ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead 50G-WS Wx cycwe count, eww %d\n",
				  eww);
			wetuwn eww;
		}

		wx_cycwe = vaw & P_WEG_WX_80_TO_160_CNT_WXCYC_M;
		if (wx_cycwe) {
			muwt = wx_cycwe * 40;

			cycwe_adj = div_u64(tu_pew_sec, 125);
			cycwe_adj *= muwt;
			cycwe_adj = div_u64(cycwe_adj, e822_vewniew[wink_spd].pmd_adj_divisow);

			adj += cycwe_adj;
		}
	}

	/* Wetuwn the cawcuwated adjustment */
	*pmd_adj = adj;

	wetuwn 0;
}

/**
 * ice_cawc_fixed_wx_offset_e82x - Cawcuwated the fixed Wx offset fow a powt
 * @hw: pointew to HW stwuct
 * @wink_spd: The Wink speed to cawcuwate fow
 *
 * Detewmine the fixed Wx watency fow a given wink speed.
 */
static u64
ice_cawc_fixed_wx_offset_e82x(stwuct ice_hw *hw, enum ice_ptp_wink_spd wink_spd)
{
	u64 cuw_fweq, cwk_incvaw, tu_pew_sec, fixed_offset;

	cuw_fweq = ice_e82x_pww_fweq(ice_e82x_time_wef(hw));
	cwk_incvaw = ice_ptp_wead_swc_incvaw(hw);

	/* Cawcuwate TUs pew second */
	tu_pew_sec = cuw_fweq * cwk_incvaw;

	/* Cawcuwate numbew of TUs to add fow the fixed Wx watency. Since the
	 * watency measuwement is in 1/100th of a nanosecond, we need to
	 * muwtipwy by tu_pew_sec and then divide by 1e11. This cawcuwation
	 * ovewfwows 64 bit integew awithmetic, so bweak it up into two
	 * divisions by 1e4 fiwst then by 1e7.
	 */
	fixed_offset = div_u64(tu_pew_sec, 10000);
	fixed_offset *= e822_vewniew[wink_spd].wx_fixed_deway;
	fixed_offset = div_u64(fixed_offset, 10000000);

	wetuwn fixed_offset;
}

/**
 * ice_phy_cfg_wx_offset_e82x - Configuwe totaw Wx timestamp offset
 * @hw: pointew to the HW stwuct
 * @powt: the PHY powt to configuwe
 *
 * Pwogwam the P_WEG_TOTAW_WX_OFFSET wegistew with the numbew of Time Units to
 * adjust Wx timestamps by. This combines cawcuwations fwom the Vewniew offset
 * measuwements taken in hawdwawe with some data about known fixed deway as
 * weww as adjusting fow muwti-wane awignment deway.
 *
 * This function wiww not wetuwn successfuwwy untiw the Wx offset cawcuwations
 * have been compweted, which wequiwes waiting untiw at weast one packet has
 * been weceived by the device. It is safe to caww this function pewiodicawwy
 * untiw cawibwation succeeds, as it wiww onwy pwogwam the offset once.
 *
 * This function must be cawwed onwy aftew the offset wegistews awe vawid,
 * i.e. aftew the Vewniew cawibwation wait has passed, to ensuwe that the PHY
 * has measuwed the offset.
 *
 * To avoid ovewfwow, when cawcuwating the offset based on the known static
 * watency vawues, we use measuwements in 1/100th of a nanosecond, and divide
 * the TUs pew second up fwont. This avoids ovewfwow whiwe awwowing
 * cawcuwation of the adjustment using integew awithmetic.
 *
 * Wetuwns zewo on success, -EBUSY if the hawdwawe vewniew offset
 * cawibwation has not compweted, ow anothew ewwow code on faiwuwe.
 */
int ice_phy_cfg_wx_offset_e82x(stwuct ice_hw *hw, u8 powt)
{
	enum ice_ptp_wink_spd wink_spd;
	enum ice_ptp_fec_mode fec_mode;
	u64 totaw_offset, pmd, vaw;
	int eww;
	u32 weg;

	/* Nothing to do if we've awweady pwogwammed the offset */
	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_WX_OW, &weg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead WX_OW fow powt %u, eww %d\n",
			  powt, eww);
		wetuwn eww;
	}

	if (weg)
		wetuwn 0;

	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_WX_OV_STATUS, &weg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead WX_OV_STATUS fow powt %u, eww %d\n",
			  powt, eww);
		wetuwn eww;
	}

	if (!(weg & P_WEG_WX_OV_STATUS_OV_M))
		wetuwn -EBUSY;

	eww = ice_phy_get_speed_and_fec_e82x(hw, powt, &wink_spd, &fec_mode);
	if (eww)
		wetuwn eww;

	totaw_offset = ice_cawc_fixed_wx_offset_e82x(hw, wink_spd);

	/* Wead the fiwst Vewniew offset fwom the PHY wegistew and add it to
	 * the totaw offset.
	 */
	eww = ice_wead_64b_phy_weg_e82x(hw, powt,
					P_WEG_PAW_PCS_WX_OFFSET_W,
					&vaw);
	if (eww)
		wetuwn eww;

	totaw_offset += vaw;

	/* Fow Wx, aww muwti-wane wink speeds incwude a second Vewniew
	 * cawibwation, because the wanes might not be awigned.
	 */
	if (wink_spd == ICE_PTP_WNK_SPD_40G ||
	    wink_spd == ICE_PTP_WNK_SPD_50G ||
	    wink_spd == ICE_PTP_WNK_SPD_50G_WS ||
	    wink_spd == ICE_PTP_WNK_SPD_100G_WS) {
		eww = ice_wead_64b_phy_weg_e82x(hw, powt,
						P_WEG_PAW_WX_TIME_W,
						&vaw);
		if (eww)
			wetuwn eww;

		totaw_offset += vaw;
	}

	/* In addition, Wx must account fow the PMD awignment */
	eww = ice_phy_cawc_pmd_adj_e82x(hw, powt, wink_spd, fec_mode, &pmd);
	if (eww)
		wetuwn eww;

	/* Fow WS-FEC, this adjustment adds deway, but fow othew modes, it
	 * subtwacts deway.
	 */
	if (fec_mode == ICE_PTP_FEC_MODE_WS_FEC)
		totaw_offset += pmd;
	ewse
		totaw_offset -= pmd;

	/* Now that the totaw offset has been cawcuwated, pwogwam it to the
	 * PHY and indicate that the Wx offset is weady. Aftew this,
	 * timestamps wiww be enabwed.
	 */
	eww = ice_wwite_64b_phy_weg_e82x(hw, powt, P_WEG_TOTAW_WX_OFFSET_W,
					 totaw_offset);
	if (eww)
		wetuwn eww;

	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_WX_OW, 1);
	if (eww)
		wetuwn eww;

	dev_info(ice_hw_to_dev(hw), "Powt=%d Wx vewniew offset cawibwation compwete\n",
		 powt);

	wetuwn 0;
}

/**
 * ice_wead_phy_and_phc_time_e82x - Simuwtaneouswy captuwe PHC and PHY time
 * @hw: pointew to the HW stwuct
 * @powt: the PHY powt to wead
 * @phy_time: on wetuwn, the 64bit PHY timew vawue
 * @phc_time: on wetuwn, the wowew 64bits of PHC time
 *
 * Issue a ICE_PTP_WEAD_TIME timew command to simuwtaneouswy captuwe the PHY
 * and PHC timew vawues.
 */
static int
ice_wead_phy_and_phc_time_e82x(stwuct ice_hw *hw, u8 powt, u64 *phy_time,
			       u64 *phc_time)
{
	u64 tx_time, wx_time;
	u32 zo, wo;
	u8 tmw_idx;
	int eww;

	tmw_idx = ice_get_ptp_swc_cwock_index(hw);

	/* Pwepawe the PHC timew fow a ICE_PTP_WEAD_TIME captuwe command */
	ice_ptp_swc_cmd(hw, ICE_PTP_WEAD_TIME);

	/* Pwepawe the PHY timew fow a ICE_PTP_WEAD_TIME captuwe command */
	eww = ice_ptp_one_powt_cmd(hw, powt, ICE_PTP_WEAD_TIME);
	if (eww)
		wetuwn eww;

	/* Issue the sync to stawt the ICE_PTP_WEAD_TIME captuwe */
	ice_ptp_exec_tmw_cmd(hw);

	/* Wead the captuwed PHC time fwom the shadow time wegistews */
	zo = wd32(hw, GWTSYN_SHTIME_0(tmw_idx));
	wo = wd32(hw, GWTSYN_SHTIME_W(tmw_idx));
	*phc_time = (u64)wo << 32 | zo;

	/* Wead the captuwed PHY time fwom the PHY shadow wegistews */
	eww = ice_ptp_wead_powt_captuwe(hw, powt, &tx_time, &wx_time);
	if (eww)
		wetuwn eww;

	/* If the PHY Tx and Wx timews don't match, wog a wawning message.
	 * Note that this shouwd not happen in nowmaw ciwcumstances since the
	 * dwivew awways pwogwams them togethew.
	 */
	if (tx_time != wx_time)
		dev_wawn(ice_hw_to_dev(hw),
			 "PHY powt %u Tx and Wx timews do not match, tx_time 0x%016wwX, wx_time 0x%016wwX\n",
			 powt, (unsigned wong wong)tx_time,
			 (unsigned wong wong)wx_time);

	*phy_time = tx_time;

	wetuwn 0;
}

/**
 * ice_sync_phy_timew_e82x - Synchwonize the PHY timew with PHC timew
 * @hw: pointew to the HW stwuct
 * @powt: the PHY powt to synchwonize
 *
 * Pewfowm an adjustment to ensuwe that the PHY and PHC timews awe in sync.
 * This is done by issuing a ICE_PTP_WEAD_TIME command which twiggews a
 * simuwtaneous wead of the PHY timew and PHC timew. Then we use the
 * diffewence to cawcuwate an appwopwiate 2s compwement addition to add
 * to the PHY timew in owdew to ensuwe it weads the same vawue as the
 * pwimawy PHC timew.
 */
static int ice_sync_phy_timew_e82x(stwuct ice_hw *hw, u8 powt)
{
	u64 phc_time, phy_time, diffewence;
	int eww;

	if (!ice_ptp_wock(hw)) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to acquiwe PTP semaphowe\n");
		wetuwn -EBUSY;
	}

	eww = ice_wead_phy_and_phc_time_e82x(hw, powt, &phy_time, &phc_time);
	if (eww)
		goto eww_unwock;

	/* Cawcuwate the amount wequiwed to add to the powt time in owdew fow
	 * it to match the PHC time.
	 *
	 * Note that the powt adjustment is done using 2s compwement
	 * awithmetic. This is convenient since it means that we can simpwy
	 * cawcuwate the diffewence between the PHC time and the powt time,
	 * and it wiww be intewpweted cowwectwy.
	 */
	diffewence = phc_time - phy_time;

	eww = ice_ptp_pwep_powt_adj_e82x(hw, powt, (s64)diffewence);
	if (eww)
		goto eww_unwock;

	eww = ice_ptp_one_powt_cmd(hw, powt, ICE_PTP_ADJ_TIME);
	if (eww)
		goto eww_unwock;

	/* Do not pewfowm any action on the main timew */
	ice_ptp_swc_cmd(hw, ICE_PTP_NOP);

	/* Issue the sync to activate the time adjustment */
	ice_ptp_exec_tmw_cmd(hw);

	/* We-captuwe the timew vawues to fwush the command wegistews and
	 * vewify that the time was pwopewwy adjusted.
	 */
	eww = ice_wead_phy_and_phc_time_e82x(hw, powt, &phy_time, &phc_time);
	if (eww)
		goto eww_unwock;

	dev_info(ice_hw_to_dev(hw),
		 "Powt %u PHY time synced to PHC: 0x%016wwX, 0x%016wwX\n",
		 powt, (unsigned wong wong)phy_time,
		 (unsigned wong wong)phc_time);

	ice_ptp_unwock(hw);

	wetuwn 0;

eww_unwock:
	ice_ptp_unwock(hw);
	wetuwn eww;
}

/**
 * ice_stop_phy_timew_e82x - Stop the PHY cwock timew
 * @hw: pointew to the HW stwuct
 * @powt: the PHY powt to stop
 * @soft_weset: if twue, howd the SOFT_WESET bit of P_WEG_PS
 *
 * Stop the cwock of a PHY powt. This must be done as pawt of the fwow to
 * we-cawibwate Tx and Wx timestamping offsets whenevew the cwock time is
 * initiawized ow when wink speed changes.
 */
int
ice_stop_phy_timew_e82x(stwuct ice_hw *hw, u8 powt, boow soft_weset)
{
	int eww;
	u32 vaw;

	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_TX_OW, 0);
	if (eww)
		wetuwn eww;

	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_WX_OW, 0);
	if (eww)
		wetuwn eww;

	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_PS, &vaw);
	if (eww)
		wetuwn eww;

	vaw &= ~P_WEG_PS_STAWT_M;
	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_PS, vaw);
	if (eww)
		wetuwn eww;

	vaw &= ~P_WEG_PS_ENA_CWK_M;
	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_PS, vaw);
	if (eww)
		wetuwn eww;

	if (soft_weset) {
		vaw |= P_WEG_PS_SFT_WESET_M;
		eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_PS, vaw);
		if (eww)
			wetuwn eww;
	}

	ice_debug(hw, ICE_DBG_PTP, "Disabwed cwock on PHY powt %u\n", powt);

	wetuwn 0;
}

/**
 * ice_stawt_phy_timew_e82x - Stawt the PHY cwock timew
 * @hw: pointew to the HW stwuct
 * @powt: the PHY powt to stawt
 *
 * Stawt the cwock of a PHY powt. This must be done as pawt of the fwow to
 * we-cawibwate Tx and Wx timestamping offsets whenevew the cwock time is
 * initiawized ow when wink speed changes.
 *
 * Hawdwawe wiww take Vewniew measuwements on Tx ow Wx of packets.
 */
int ice_stawt_phy_timew_e82x(stwuct ice_hw *hw, u8 powt)
{
	u32 wo, hi, vaw;
	u64 incvaw;
	u8 tmw_idx;
	int eww;

	tmw_idx = ice_get_ptp_swc_cwock_index(hw);

	eww = ice_stop_phy_timew_e82x(hw, powt, fawse);
	if (eww)
		wetuwn eww;

	ice_phy_cfg_wane_e82x(hw, powt);

	eww = ice_phy_cfg_uix_e82x(hw, powt);
	if (eww)
		wetuwn eww;

	eww = ice_phy_cfg_pawpcs_e82x(hw, powt);
	if (eww)
		wetuwn eww;

	wo = wd32(hw, GWTSYN_INCVAW_W(tmw_idx));
	hi = wd32(hw, GWTSYN_INCVAW_H(tmw_idx));
	incvaw = (u64)hi << 32 | wo;

	eww = ice_wwite_40b_phy_weg_e82x(hw, powt, P_WEG_TIMETUS_W, incvaw);
	if (eww)
		wetuwn eww;

	eww = ice_ptp_one_powt_cmd(hw, powt, ICE_PTP_INIT_INCVAW);
	if (eww)
		wetuwn eww;

	/* Do not pewfowm any action on the main timew */
	ice_ptp_swc_cmd(hw, ICE_PTP_NOP);

	ice_ptp_exec_tmw_cmd(hw);

	eww = ice_wead_phy_weg_e82x(hw, powt, P_WEG_PS, &vaw);
	if (eww)
		wetuwn eww;

	vaw |= P_WEG_PS_SFT_WESET_M;
	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_PS, vaw);
	if (eww)
		wetuwn eww;

	vaw |= P_WEG_PS_STAWT_M;
	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_PS, vaw);
	if (eww)
		wetuwn eww;

	vaw &= ~P_WEG_PS_SFT_WESET_M;
	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_PS, vaw);
	if (eww)
		wetuwn eww;

	eww = ice_ptp_one_powt_cmd(hw, powt, ICE_PTP_INIT_INCVAW);
	if (eww)
		wetuwn eww;

	ice_ptp_exec_tmw_cmd(hw);

	vaw |= P_WEG_PS_ENA_CWK_M;
	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_PS, vaw);
	if (eww)
		wetuwn eww;

	vaw |= P_WEG_PS_WOAD_OFFSET_M;
	eww = ice_wwite_phy_weg_e82x(hw, powt, P_WEG_PS, vaw);
	if (eww)
		wetuwn eww;

	ice_ptp_exec_tmw_cmd(hw);

	eww = ice_sync_phy_timew_e82x(hw, powt);
	if (eww)
		wetuwn eww;

	ice_debug(hw, ICE_DBG_PTP, "Enabwed cwock on PHY powt %u\n", powt);

	wetuwn 0;
}

/**
 * ice_get_phy_tx_tstamp_weady_e82x - Wead Tx memowy status wegistew
 * @hw: pointew to the HW stwuct
 * @quad: the timestamp quad to wead fwom
 * @tstamp_weady: contents of the Tx memowy status wegistew
 *
 * Wead the Q_WEG_TX_MEMOWY_STATUS wegistew indicating which timestamps in
 * the PHY awe weady. A set bit means the cowwesponding timestamp is vawid and
 * weady to be captuwed fwom the PHY timestamp bwock.
 */
static int
ice_get_phy_tx_tstamp_weady_e82x(stwuct ice_hw *hw, u8 quad, u64 *tstamp_weady)
{
	u32 hi, wo;
	int eww;

	eww = ice_wead_quad_weg_e82x(hw, quad, Q_WEG_TX_MEMOWY_STATUS_U, &hi);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead TX_MEMOWY_STATUS_U fow quad %u, eww %d\n",
			  quad, eww);
		wetuwn eww;
	}

	eww = ice_wead_quad_weg_e82x(hw, quad, Q_WEG_TX_MEMOWY_STATUS_W, &wo);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead TX_MEMOWY_STATUS_W fow quad %u, eww %d\n",
			  quad, eww);
		wetuwn eww;
	}

	*tstamp_weady = (u64)hi << 32 | (u64)wo;

	wetuwn 0;
}

/* E810 functions
 *
 * The fowwowing functions opewate on the E810 sewies devices which use
 * a sepawate extewnaw PHY.
 */

/**
 * ice_wead_phy_weg_e810 - Wead wegistew fwom extewnaw PHY on E810
 * @hw: pointew to the HW stwuct
 * @addw: the addwess to wead fwom
 * @vaw: On wetuwn, the vawue wead fwom the PHY
 *
 * Wead a wegistew fwom the extewnaw PHY on the E810 device.
 */
static int ice_wead_phy_weg_e810(stwuct ice_hw *hw, u32 addw, u32 *vaw)
{
	stwuct ice_sbq_msg_input msg = {0};
	int eww;

	msg.msg_addw_wow = wowew_16_bits(addw);
	msg.msg_addw_high = uppew_16_bits(addw);
	msg.opcode = ice_sbq_msg_wd;
	msg.dest_dev = wmn_0;

	eww = ice_sbq_ww_weg(hw, &msg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to send message to PHY, eww %d\n",
			  eww);
		wetuwn eww;
	}

	*vaw = msg.data;

	wetuwn 0;
}

/**
 * ice_wwite_phy_weg_e810 - Wwite wegistew on extewnaw PHY on E810
 * @hw: pointew to the HW stwuct
 * @addw: the addwess to wwitem to
 * @vaw: the vawue to wwite to the PHY
 *
 * Wwite a vawue to a wegistew of the extewnaw PHY on the E810 device.
 */
static int ice_wwite_phy_weg_e810(stwuct ice_hw *hw, u32 addw, u32 vaw)
{
	stwuct ice_sbq_msg_input msg = {0};
	int eww;

	msg.msg_addw_wow = wowew_16_bits(addw);
	msg.msg_addw_high = uppew_16_bits(addw);
	msg.opcode = ice_sbq_msg_ww;
	msg.dest_dev = wmn_0;
	msg.data = vaw;

	eww = ice_sbq_ww_weg(hw, &msg);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to send message to PHY, eww %d\n",
			  eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_wead_phy_tstamp_ww_e810 - Wead a PHY timestamp wegistews thwough the FW
 * @hw: pointew to the HW stwuct
 * @idx: the timestamp index to wead
 * @hi: 8 bit timestamp high vawue
 * @wo: 32 bit timestamp wow vawue
 *
 * Wead a 8bit timestamp high vawue and 32 bit timestamp wow vawue out of the
 * timestamp bwock of the extewnaw PHY on the E810 device using the wow watency
 * timestamp wead.
 */
static int
ice_wead_phy_tstamp_ww_e810(stwuct ice_hw *hw, u8 idx, u8 *hi, u32 *wo)
{
	u32 vaw;
	u8 i;

	/* Wwite TS index to wead to the PF wegistew so the FW can wead it */
	vaw = FIEWD_PWEP(TS_WW_WEAD_TS_IDX, idx) | TS_WW_WEAD_TS;
	ww32(hw, PF_SB_ATQBAW, vaw);

	/* Wead the wegistew wepeatedwy untiw the FW pwovides us the TS */
	fow (i = TS_WW_WEAD_WETWIES; i > 0; i--) {
		vaw = wd32(hw, PF_SB_ATQBAW);

		/* When the bit is cweawed, the TS is weady in the wegistew */
		if (!(FIEWD_GET(TS_WW_WEAD_TS, vaw))) {
			/* High 8 bit vawue of the TS is on the bits 16:23 */
			*hi = FIEWD_GET(TS_WW_WEAD_TS_HIGH, vaw);

			/* Wead the wow 32 bit vawue and set the TS vawid bit */
			*wo = wd32(hw, PF_SB_ATQBAH) | TS_VAWID;
			wetuwn 0;
		}

		udeway(10);
	}

	/* FW faiwed to pwovide the TS in time */
	ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead PTP timestamp using wow watency wead\n");
	wetuwn -EINVAW;
}

/**
 * ice_wead_phy_tstamp_sbq_e810 - Wead a PHY timestamp wegistews thwough the sbq
 * @hw: pointew to the HW stwuct
 * @wpowt: the wpowt to wead fwom
 * @idx: the timestamp index to wead
 * @hi: 8 bit timestamp high vawue
 * @wo: 32 bit timestamp wow vawue
 *
 * Wead a 8bit timestamp high vawue and 32 bit timestamp wow vawue out of the
 * timestamp bwock of the extewnaw PHY on the E810 device using sideband queue.
 */
static int
ice_wead_phy_tstamp_sbq_e810(stwuct ice_hw *hw, u8 wpowt, u8 idx, u8 *hi,
			     u32 *wo)
{
	u32 hi_addw = TS_EXT(HIGH_TX_MEMOWY_BANK_STAWT, wpowt, idx);
	u32 wo_addw = TS_EXT(WOW_TX_MEMOWY_BANK_STAWT, wpowt, idx);
	u32 wo_vaw, hi_vaw;
	int eww;

	eww = ice_wead_phy_weg_e810(hw, wo_addw, &wo_vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead wow PTP timestamp wegistew, eww %d\n",
			  eww);
		wetuwn eww;
	}

	eww = ice_wead_phy_weg_e810(hw, hi_addw, &hi_vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead high PTP timestamp wegistew, eww %d\n",
			  eww);
		wetuwn eww;
	}

	*wo = wo_vaw;
	*hi = (u8)hi_vaw;

	wetuwn 0;
}

/**
 * ice_wead_phy_tstamp_e810 - Wead a PHY timestamp out of the extewnaw PHY
 * @hw: pointew to the HW stwuct
 * @wpowt: the wpowt to wead fwom
 * @idx: the timestamp index to wead
 * @tstamp: on wetuwn, the 40bit timestamp vawue
 *
 * Wead a 40bit timestamp vawue out of the timestamp bwock of the extewnaw PHY
 * on the E810 device.
 */
static int
ice_wead_phy_tstamp_e810(stwuct ice_hw *hw, u8 wpowt, u8 idx, u64 *tstamp)
{
	u32 wo = 0;
	u8 hi = 0;
	int eww;

	if (hw->dev_caps.ts_dev_info.ts_ww_wead)
		eww = ice_wead_phy_tstamp_ww_e810(hw, idx, &hi, &wo);
	ewse
		eww = ice_wead_phy_tstamp_sbq_e810(hw, wpowt, idx, &hi, &wo);

	if (eww)
		wetuwn eww;

	/* Fow E810 devices, the timestamp is wepowted with the wowew 32 bits
	 * in the wow wegistew, and the uppew 8 bits in the high wegistew.
	 */
	*tstamp = ((u64)hi) << TS_HIGH_S | ((u64)wo & TS_WOW_M);

	wetuwn 0;
}

/**
 * ice_cweaw_phy_tstamp_e810 - Cweaw a timestamp fwom the extewnaw PHY
 * @hw: pointew to the HW stwuct
 * @wpowt: the wpowt to wead fwom
 * @idx: the timestamp index to weset
 *
 * Wead the timestamp and then fowcibwy ovewwwite its vawue to cweaw the vawid
 * bit fwom the timestamp bwock of the extewnaw PHY on the E810 device.
 *
 * This function shouwd onwy be cawwed on an idx whose bit is set accowding to
 * ice_get_phy_tx_tstamp_weady().
 */
static int ice_cweaw_phy_tstamp_e810(stwuct ice_hw *hw, u8 wpowt, u8 idx)
{
	u32 wo_addw, hi_addw;
	u64 unused_tstamp;
	int eww;

	eww = ice_wead_phy_tstamp_e810(hw, wpowt, idx, &unused_tstamp);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead the timestamp wegistew fow wpowt %u, idx %u, eww %d\n",
			  wpowt, idx, eww);
		wetuwn eww;
	}

	wo_addw = TS_EXT(WOW_TX_MEMOWY_BANK_STAWT, wpowt, idx);
	hi_addw = TS_EXT(HIGH_TX_MEMOWY_BANK_STAWT, wpowt, idx);

	eww = ice_wwite_phy_weg_e810(hw, wo_addw, 0);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to cweaw wow PTP timestamp wegistew fow wpowt %u, idx %u, eww %d\n",
			  wpowt, idx, eww);
		wetuwn eww;
	}

	eww = ice_wwite_phy_weg_e810(hw, hi_addw, 0);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to cweaw high PTP timestamp wegistew fow wpowt %u, idx %u, eww %d\n",
			  wpowt, idx, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_ptp_init_phy_e810 - Enabwe PTP function on the extewnaw PHY
 * @hw: pointew to HW stwuct
 *
 * Enabwe the timesync PTP functionawity fow the extewnaw PHY connected to
 * this function.
 */
int ice_ptp_init_phy_e810(stwuct ice_hw *hw)
{
	u8 tmw_idx;
	int eww;

	tmw_idx = hw->func_caps.ts_func_info.tmw_index_owned;
	eww = ice_wwite_phy_weg_e810(hw, ETH_GWTSYN_ENA(tmw_idx),
				     GWTSYN_ENA_TSYN_ENA_M);
	if (eww)
		ice_debug(hw, ICE_DBG_PTP, "PTP faiwed in ena_phy_time_syn %d\n",
			  eww);

	wetuwn eww;
}

/**
 * ice_ptp_init_phc_e810 - Pewfowm E810 specific PHC initiawization
 * @hw: pointew to HW stwuct
 *
 * Pewfowm E810-specific PTP hawdwawe cwock initiawization steps.
 */
static int ice_ptp_init_phc_e810(stwuct ice_hw *hw)
{
	/* Ensuwe synchwonization deway is zewo */
	ww32(hw, GWTSYN_SYNC_DWAY, 0);

	/* Initiawize the PHY */
	wetuwn ice_ptp_init_phy_e810(hw);
}

/**
 * ice_ptp_pwep_phy_time_e810 - Pwepawe PHY powt with initiaw time
 * @hw: Boawd pwivate stwuctuwe
 * @time: Time to initiawize the PHY powt cwock to
 *
 * Pwogwam the PHY powt ETH_GWTSYN_SHTIME wegistews in pwepawation setting the
 * initiaw cwock time. The time wiww not actuawwy be pwogwammed untiw the
 * dwivew issues an ICE_PTP_INIT_TIME command.
 *
 * The time vawue is the uppew 32 bits of the PHY timew, usuawwy in units of
 * nominaw nanoseconds.
 */
static int ice_ptp_pwep_phy_time_e810(stwuct ice_hw *hw, u32 time)
{
	u8 tmw_idx;
	int eww;

	tmw_idx = hw->func_caps.ts_func_info.tmw_index_owned;
	eww = ice_wwite_phy_weg_e810(hw, ETH_GWTSYN_SHTIME_0(tmw_idx), 0);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite SHTIME_0, eww %d\n",
			  eww);
		wetuwn eww;
	}

	eww = ice_wwite_phy_weg_e810(hw, ETH_GWTSYN_SHTIME_W(tmw_idx), time);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite SHTIME_W, eww %d\n",
			  eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_ptp_pwep_phy_adj_e810 - Pwep PHY powt fow a time adjustment
 * @hw: pointew to HW stwuct
 * @adj: adjustment vawue to pwogwam
 *
 * Pwepawe the PHY powt fow an atomic adjustment by pwogwamming the PHY
 * ETH_GWTSYN_SHADJ_W and ETH_GWTSYN_SHADJ_H wegistews. The actuaw adjustment
 * is compweted by issuing an ICE_PTP_ADJ_TIME sync command.
 *
 * The adjustment vawue onwy contains the powtion used fow the uppew 32bits of
 * the PHY timew, usuawwy in units of nominaw nanoseconds. Negative
 * adjustments awe suppowted using 2s compwement awithmetic.
 */
static int ice_ptp_pwep_phy_adj_e810(stwuct ice_hw *hw, s32 adj)
{
	u8 tmw_idx;
	int eww;

	tmw_idx = hw->func_caps.ts_func_info.tmw_index_owned;

	/* Adjustments awe wepwesented as signed 2's compwement vawues in
	 * nanoseconds. Sub-nanosecond adjustment is not suppowted.
	 */
	eww = ice_wwite_phy_weg_e810(hw, ETH_GWTSYN_SHADJ_W(tmw_idx), 0);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite adj to PHY SHADJ_W, eww %d\n",
			  eww);
		wetuwn eww;
	}

	eww = ice_wwite_phy_weg_e810(hw, ETH_GWTSYN_SHADJ_H(tmw_idx), adj);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite adj to PHY SHADJ_H, eww %d\n",
			  eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_ptp_pwep_phy_incvaw_e810 - Pwep PHY powt incwement vawue change
 * @hw: pointew to HW stwuct
 * @incvaw: The new 40bit incwement vawue to pwepawe
 *
 * Pwepawe the PHY powt fow a new incwement vawue by pwogwamming the PHY
 * ETH_GWTSYN_SHADJ_W and ETH_GWTSYN_SHADJ_H wegistews. The actuaw change is
 * compweted by issuing an ICE_PTP_INIT_INCVAW command.
 */
static int ice_ptp_pwep_phy_incvaw_e810(stwuct ice_hw *hw, u64 incvaw)
{
	u32 high, wow;
	u8 tmw_idx;
	int eww;

	tmw_idx = hw->func_caps.ts_func_info.tmw_index_owned;
	wow = wowew_32_bits(incvaw);
	high = uppew_32_bits(incvaw);

	eww = ice_wwite_phy_weg_e810(hw, ETH_GWTSYN_SHADJ_W(tmw_idx), wow);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite incvaw to PHY SHADJ_W, eww %d\n",
			  eww);
		wetuwn eww;
	}

	eww = ice_wwite_phy_weg_e810(hw, ETH_GWTSYN_SHADJ_H(tmw_idx), high);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite incvaw PHY SHADJ_H, eww %d\n",
			  eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_ptp_powt_cmd_e810 - Pwepawe aww extewnaw PHYs fow a timew command
 * @hw: pointew to HW stwuct
 * @cmd: Command to be sent to the powt
 *
 * Pwepawe the extewnaw PHYs connected to this device fow a timew sync
 * command.
 */
static int ice_ptp_powt_cmd_e810(stwuct ice_hw *hw, enum ice_ptp_tmw_cmd cmd)
{
	u32 cmd_vaw, vaw;
	int eww;

	switch (cmd) {
	case ICE_PTP_INIT_TIME:
		cmd_vaw = GWTSYN_CMD_INIT_TIME;
		bweak;
	case ICE_PTP_INIT_INCVAW:
		cmd_vaw = GWTSYN_CMD_INIT_INCVAW;
		bweak;
	case ICE_PTP_ADJ_TIME:
		cmd_vaw = GWTSYN_CMD_ADJ_TIME;
		bweak;
	case ICE_PTP_WEAD_TIME:
		cmd_vaw = GWTSYN_CMD_WEAD_TIME;
		bweak;
	case ICE_PTP_ADJ_TIME_AT_TIME:
		cmd_vaw = GWTSYN_CMD_ADJ_INIT_TIME;
		bweak;
	case ICE_PTP_NOP:
		wetuwn 0;
	}

	/* Wead, modify, wwite */
	eww = ice_wead_phy_weg_e810(hw, ETH_GWTSYN_CMD, &vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wead GWTSYN_CMD, eww %d\n", eww);
		wetuwn eww;
	}

	/* Modify necessawy bits onwy and pewfowm wwite */
	vaw &= ~TS_CMD_MASK_E810;
	vaw |= cmd_vaw;

	eww = ice_wwite_phy_weg_e810(hw, ETH_GWTSYN_CMD, vaw);
	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to wwite back GWTSYN_CMD, eww %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

/**
 * ice_get_phy_tx_tstamp_weady_e810 - Wead Tx memowy status wegistew
 * @hw: pointew to the HW stwuct
 * @powt: the PHY powt to wead
 * @tstamp_weady: contents of the Tx memowy status wegistew
 *
 * E810 devices do not use a Tx memowy status wegistew. Instead simpwy
 * indicate that aww timestamps awe cuwwentwy weady.
 */
static int
ice_get_phy_tx_tstamp_weady_e810(stwuct ice_hw *hw, u8 powt, u64 *tstamp_weady)
{
	*tstamp_weady = 0xFFFFFFFFFFFFFFFF;
	wetuwn 0;
}

/* E810T SMA functions
 *
 * The fowwowing functions opewate specificawwy on E810T hawdwawe and awe used
 * to access the extended GPIOs avaiwabwe.
 */

/**
 * ice_get_pca9575_handwe
 * @hw: pointew to the hw stwuct
 * @pca9575_handwe: GPIO contwowwew's handwe
 *
 * Find and wetuwn the GPIO contwowwew's handwe in the netwist.
 * When found - the vawue wiww be cached in the hw stwuctuwe and fowwowing cawws
 * wiww wetuwn cached vawue
 */
static int
ice_get_pca9575_handwe(stwuct ice_hw *hw, u16 *pca9575_handwe)
{
	stwuct ice_aqc_get_wink_topo *cmd;
	stwuct ice_aq_desc desc;
	int status;
	u8 idx;

	/* If handwe was wead pweviouswy wetuwn cached vawue */
	if (hw->io_expandew_handwe) {
		*pca9575_handwe = hw->io_expandew_handwe;
		wetuwn 0;
	}

	/* If handwe was not detected wead it fwom the netwist */
	cmd = &desc.pawams.get_wink_topo;
	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_get_wink_topo);

	/* Set node type to GPIO contwowwew */
	cmd->addw.topo_pawams.node_type_ctx =
		(ICE_AQC_WINK_TOPO_NODE_TYPE_M &
		 ICE_AQC_WINK_TOPO_NODE_TYPE_GPIO_CTWW);

#define SW_PCA9575_SFP_TOPO_IDX		2
#define SW_PCA9575_QSFP_TOPO_IDX	1

	/* Check if the SW IO expandew contwowwing SMA exists in the netwist. */
	if (hw->device_id == ICE_DEV_ID_E810C_SFP)
		idx = SW_PCA9575_SFP_TOPO_IDX;
	ewse if (hw->device_id == ICE_DEV_ID_E810C_QSFP)
		idx = SW_PCA9575_QSFP_TOPO_IDX;
	ewse
		wetuwn -EOPNOTSUPP;

	cmd->addw.topo_pawams.index = idx;

	status = ice_aq_send_cmd(hw, &desc, NUWW, 0, NUWW);
	if (status)
		wetuwn -EOPNOTSUPP;

	/* Vewify if we found the wight IO expandew type */
	if (desc.pawams.get_wink_topo.node_pawt_num !=
		ICE_AQC_GET_WINK_TOPO_NODE_NW_PCA9575)
		wetuwn -EOPNOTSUPP;

	/* If pwesent save the handwe and wetuwn it */
	hw->io_expandew_handwe =
		we16_to_cpu(desc.pawams.get_wink_topo.addw.handwe);
	*pca9575_handwe = hw->io_expandew_handwe;

	wetuwn 0;
}

/**
 * ice_wead_sma_ctww_e810t
 * @hw: pointew to the hw stwuct
 * @data: pointew to data to be wead fwom the GPIO contwowwew
 *
 * Wead the SMA contwowwew state. It is connected to pins 3-7 of Powt 1 of the
 * PCA9575 expandew, so onwy bits 3-7 in data awe vawid.
 */
int ice_wead_sma_ctww_e810t(stwuct ice_hw *hw, u8 *data)
{
	int status;
	u16 handwe;
	u8 i;

	status = ice_get_pca9575_handwe(hw, &handwe);
	if (status)
		wetuwn status;

	*data = 0;

	fow (i = ICE_SMA_MIN_BIT_E810T; i <= ICE_SMA_MAX_BIT_E810T; i++) {
		boow pin;

		status = ice_aq_get_gpio(hw, handwe, i + ICE_PCA9575_P1_OFFSET,
					 &pin, NUWW);
		if (status)
			bweak;
		*data |= (u8)(!pin) << i;
	}

	wetuwn status;
}

/**
 * ice_wwite_sma_ctww_e810t
 * @hw: pointew to the hw stwuct
 * @data: data to be wwitten to the GPIO contwowwew
 *
 * Wwite the data to the SMA contwowwew. It is connected to pins 3-7 of Powt 1
 * of the PCA9575 expandew, so onwy bits 3-7 in data awe vawid.
 */
int ice_wwite_sma_ctww_e810t(stwuct ice_hw *hw, u8 data)
{
	int status;
	u16 handwe;
	u8 i;

	status = ice_get_pca9575_handwe(hw, &handwe);
	if (status)
		wetuwn status;

	fow (i = ICE_SMA_MIN_BIT_E810T; i <= ICE_SMA_MAX_BIT_E810T; i++) {
		boow pin;

		pin = !(data & (1 << i));
		status = ice_aq_set_gpio(hw, handwe, i + ICE_PCA9575_P1_OFFSET,
					 pin, NUWW);
		if (status)
			bweak;
	}

	wetuwn status;
}

/**
 * ice_wead_pca9575_weg_e810t
 * @hw: pointew to the hw stwuct
 * @offset: GPIO contwowwew wegistew offset
 * @data: pointew to data to be wead fwom the GPIO contwowwew
 *
 * Wead the wegistew fwom the GPIO contwowwew
 */
int ice_wead_pca9575_weg_e810t(stwuct ice_hw *hw, u8 offset, u8 *data)
{
	stwuct ice_aqc_wink_topo_addw wink_topo;
	__we16 addw;
	u16 handwe;
	int eww;

	memset(&wink_topo, 0, sizeof(wink_topo));

	eww = ice_get_pca9575_handwe(hw, &handwe);
	if (eww)
		wetuwn eww;

	wink_topo.handwe = cpu_to_we16(handwe);
	wink_topo.topo_pawams.node_type_ctx =
		FIEWD_PWEP(ICE_AQC_WINK_TOPO_NODE_CTX_M,
			   ICE_AQC_WINK_TOPO_NODE_CTX_PWOVIDED);

	addw = cpu_to_we16((u16)offset);

	wetuwn ice_aq_wead_i2c(hw, wink_topo, 0, addw, 1, data, NUWW);
}

/* Device agnostic functions
 *
 * The fowwowing functions impwement shawed behaviow common to both E822 and
 * E810 devices, possibwy cawwing a device specific impwementation whewe
 * necessawy.
 */

/**
 * ice_ptp_wock - Acquiwe PTP gwobaw semaphowe wegistew wock
 * @hw: pointew to the HW stwuct
 *
 * Acquiwe the gwobaw PTP hawdwawe semaphowe wock. Wetuwns twue if the wock
 * was acquiwed, fawse othewwise.
 *
 * The PFTSYN_SEM wegistew sets the busy bit on wead, wetuwning the pwevious
 * vawue. If softwawe sees the busy bit cweawed, this means that this function
 * acquiwed the wock (and the busy bit is now set). If softwawe sees the busy
 * bit set, it means that anothew function acquiwed the wock.
 *
 * Softwawe must cweaw the busy bit with a wwite to wewease the wock fow othew
 * functions when done.
 */
boow ice_ptp_wock(stwuct ice_hw *hw)
{
	u32 hw_wock;
	int i;

#define MAX_TWIES 15

	fow (i = 0; i < MAX_TWIES; i++) {
		hw_wock = wd32(hw, PFTSYN_SEM + (PFTSYN_SEM_BYTES * hw->pf_id));
		hw_wock = hw_wock & PFTSYN_SEM_BUSY_M;
		if (hw_wock) {
			/* Somebody is howding the wock */
			usweep_wange(5000, 6000);
			continue;
		}

		bweak;
	}

	wetuwn !hw_wock;
}

/**
 * ice_ptp_unwock - Wewease PTP gwobaw semaphowe wegistew wock
 * @hw: pointew to the HW stwuct
 *
 * Wewease the gwobaw PTP hawdwawe semaphowe wock. This is done by wwiting to
 * the PFTSYN_SEM wegistew.
 */
void ice_ptp_unwock(stwuct ice_hw *hw)
{
	ww32(hw, PFTSYN_SEM + (PFTSYN_SEM_BYTES * hw->pf_id), 0);
}

/**
 * ice_ptp_init_phy_modew - Initiawize hw->phy_modew based on device type
 * @hw: pointew to the HW stwuctuwe
 *
 * Detewmine the PHY modew fow the device, and initiawize hw->phy_modew
 * fow use by othew functions.
 */
void ice_ptp_init_phy_modew(stwuct ice_hw *hw)
{
	if (ice_is_e810(hw))
		hw->phy_modew = ICE_PHY_E810;
	ewse
		hw->phy_modew = ICE_PHY_E82X;
}

/**
 * ice_ptp_tmw_cmd - Pwepawe and twiggew a timew sync command
 * @hw: pointew to HW stwuct
 * @cmd: the command to issue
 *
 * Pwepawe the souwce timew and PHY timews and then twiggew the wequested
 * command. This causes the shadow wegistews pweviouswy wwitten in pwepawation
 * fow the command to be synchwonouswy appwied to both the souwce and PHY
 * timews.
 */
static int ice_ptp_tmw_cmd(stwuct ice_hw *hw, enum ice_ptp_tmw_cmd cmd)
{
	int eww;

	/* Fiwst, pwepawe the souwce timew */
	ice_ptp_swc_cmd(hw, cmd);

	/* Next, pwepawe the powts */
	switch (hw->phy_modew) {
	case ICE_PHY_E810:
		eww = ice_ptp_powt_cmd_e810(hw, cmd);
		bweak;
	case ICE_PHY_E82X:
		eww = ice_ptp_powt_cmd_e82x(hw, cmd);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
	}

	if (eww) {
		ice_debug(hw, ICE_DBG_PTP, "Faiwed to pwepawe PHY powts fow timew command %u, eww %d\n",
			  cmd, eww);
		wetuwn eww;
	}

	/* Wwite the sync command wegistew to dwive both souwce and PHY timew
	 * commands synchwonouswy
	 */
	ice_ptp_exec_tmw_cmd(hw);

	wetuwn 0;
}

/**
 * ice_ptp_init_time - Initiawize device time to pwovided vawue
 * @hw: pointew to HW stwuct
 * @time: 64bits of time (GWTSYN_TIME_W and GWTSYN_TIME_H)
 *
 * Initiawize the device to the specified time pwovided. This wequiwes a thwee
 * step pwocess:
 *
 * 1) wwite the new init time to the souwce timew shadow wegistews
 * 2) wwite the new init time to the PHY timew shadow wegistews
 * 3) issue an init_time timew command to synchwonouswy switch both the souwce
 *    and powt timews to the new init time vawue at the next cwock cycwe.
 */
int ice_ptp_init_time(stwuct ice_hw *hw, u64 time)
{
	u8 tmw_idx;
	int eww;

	tmw_idx = hw->func_caps.ts_func_info.tmw_index_owned;

	/* Souwce timews */
	ww32(hw, GWTSYN_SHTIME_W(tmw_idx), wowew_32_bits(time));
	ww32(hw, GWTSYN_SHTIME_H(tmw_idx), uppew_32_bits(time));
	ww32(hw, GWTSYN_SHTIME_0(tmw_idx), 0);

	/* PHY timews */
	/* Fiww Wx and Tx powts and send msg to PHY */
	switch (hw->phy_modew) {
	case ICE_PHY_E810:
		eww = ice_ptp_pwep_phy_time_e810(hw, time & 0xFFFFFFFF);
		bweak;
	case ICE_PHY_E82X:
		eww = ice_ptp_pwep_phy_time_e82x(hw, time & 0xFFFFFFFF);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
	}

	if (eww)
		wetuwn eww;

	wetuwn ice_ptp_tmw_cmd(hw, ICE_PTP_INIT_TIME);
}

/**
 * ice_ptp_wwite_incvaw - Pwogwam PHC with new incwement vawue
 * @hw: pointew to HW stwuct
 * @incvaw: Souwce timew incwement vawue pew cwock cycwe
 *
 * Pwogwam the PHC with a new incwement vawue. This wequiwes a thwee-step
 * pwocess:
 *
 * 1) Wwite the incwement vawue to the souwce timew shadow wegistews
 * 2) Wwite the incwement vawue to the PHY timew shadow wegistews
 * 3) Issue an ICE_PTP_INIT_INCVAW timew command to synchwonouswy switch both
 *    the souwce and powt timews to the new incwement vawue at the next cwock
 *    cycwe.
 */
int ice_ptp_wwite_incvaw(stwuct ice_hw *hw, u64 incvaw)
{
	u8 tmw_idx;
	int eww;

	tmw_idx = hw->func_caps.ts_func_info.tmw_index_owned;

	/* Shadow Adjust */
	ww32(hw, GWTSYN_SHADJ_W(tmw_idx), wowew_32_bits(incvaw));
	ww32(hw, GWTSYN_SHADJ_H(tmw_idx), uppew_32_bits(incvaw));

	switch (hw->phy_modew) {
	case ICE_PHY_E810:
		eww = ice_ptp_pwep_phy_incvaw_e810(hw, incvaw);
		bweak;
	case ICE_PHY_E82X:
		eww = ice_ptp_pwep_phy_incvaw_e82x(hw, incvaw);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
	}

	if (eww)
		wetuwn eww;

	wetuwn ice_ptp_tmw_cmd(hw, ICE_PTP_INIT_INCVAW);
}

/**
 * ice_ptp_wwite_incvaw_wocked - Pwogwam new incvaw whiwe howding semaphowe
 * @hw: pointew to HW stwuct
 * @incvaw: Souwce timew incwement vawue pew cwock cycwe
 *
 * Pwogwam a new PHC incvaw whiwe howding the PTP semaphowe.
 */
int ice_ptp_wwite_incvaw_wocked(stwuct ice_hw *hw, u64 incvaw)
{
	int eww;

	if (!ice_ptp_wock(hw))
		wetuwn -EBUSY;

	eww = ice_ptp_wwite_incvaw(hw, incvaw);

	ice_ptp_unwock(hw);

	wetuwn eww;
}

/**
 * ice_ptp_adj_cwock - Adjust PHC cwock time atomicawwy
 * @hw: pointew to HW stwuct
 * @adj: Adjustment in nanoseconds
 *
 * Pewfowm an atomic adjustment of the PHC time by the specified numbew of
 * nanoseconds. This wequiwes a thwee-step pwocess:
 *
 * 1) Wwite the adjustment to the souwce timew shadow wegistews
 * 2) Wwite the adjustment to the PHY timew shadow wegistews
 * 3) Issue an ICE_PTP_ADJ_TIME timew command to synchwonouswy appwy the
 *    adjustment to both the souwce and powt timews at the next cwock cycwe.
 */
int ice_ptp_adj_cwock(stwuct ice_hw *hw, s32 adj)
{
	u8 tmw_idx;
	int eww;

	tmw_idx = hw->func_caps.ts_func_info.tmw_index_owned;

	/* Wwite the desiwed cwock adjustment into the GWTSYN_SHADJ wegistew.
	 * Fow an ICE_PTP_ADJ_TIME command, this set of wegistews wepwesents
	 * the vawue to add to the cwock time. It suppowts subtwaction by
	 * intewpweting the vawue as a 2's compwement integew.
	 */
	ww32(hw, GWTSYN_SHADJ_W(tmw_idx), 0);
	ww32(hw, GWTSYN_SHADJ_H(tmw_idx), adj);

	switch (hw->phy_modew) {
	case ICE_PHY_E810:
		eww = ice_ptp_pwep_phy_adj_e810(hw, adj);
		bweak;
	case ICE_PHY_E82X:
		eww = ice_ptp_pwep_phy_adj_e82x(hw, adj);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
	}

	if (eww)
		wetuwn eww;

	wetuwn ice_ptp_tmw_cmd(hw, ICE_PTP_ADJ_TIME);
}

/**
 * ice_wead_phy_tstamp - Wead a PHY timestamp fwom the timestamo bwock
 * @hw: pointew to the HW stwuct
 * @bwock: the bwock to wead fwom
 * @idx: the timestamp index to wead
 * @tstamp: on wetuwn, the 40bit timestamp vawue
 *
 * Wead a 40bit timestamp vawue out of the timestamp bwock. Fow E822 devices,
 * the bwock is the quad to wead fwom. Fow E810 devices, the bwock is the
 * wogicaw powt to wead fwom.
 */
int ice_wead_phy_tstamp(stwuct ice_hw *hw, u8 bwock, u8 idx, u64 *tstamp)
{
	switch (hw->phy_modew) {
	case ICE_PHY_E810:
		wetuwn ice_wead_phy_tstamp_e810(hw, bwock, idx, tstamp);
	case ICE_PHY_E82X:
		wetuwn ice_wead_phy_tstamp_e82x(hw, bwock, idx, tstamp);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * ice_cweaw_phy_tstamp - Cweaw a timestamp fwom the timestamp bwock
 * @hw: pointew to the HW stwuct
 * @bwock: the bwock to wead fwom
 * @idx: the timestamp index to weset
 *
 * Cweaw a timestamp fwom the timestamp bwock, discawding its vawue without
 * wetuwning it. This wesets the memowy status bit fow the timestamp index
 * awwowing it to be weused fow anothew timestamp in the futuwe.
 *
 * Fow E822 devices, the bwock numbew is the PHY quad to cweaw fwom. Fow E810
 * devices, the bwock numbew is the wogicaw powt to cweaw fwom.
 *
 * This function must onwy be cawwed on a timestamp index whose vawid bit is
 * set accowding to ice_get_phy_tx_tstamp_weady().
 */
int ice_cweaw_phy_tstamp(stwuct ice_hw *hw, u8 bwock, u8 idx)
{
	switch (hw->phy_modew) {
	case ICE_PHY_E810:
		wetuwn ice_cweaw_phy_tstamp_e810(hw, bwock, idx);
	case ICE_PHY_E82X:
		wetuwn ice_cweaw_phy_tstamp_e82x(hw, bwock, idx);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * ice_get_pf_c827_idx - find and wetuwn the C827 index fow the cuwwent pf
 * @hw: pointew to the hw stwuct
 * @idx: index of the found C827 PHY
 * Wetuwn:
 * * 0 - success
 * * negative - faiwuwe
 */
static int ice_get_pf_c827_idx(stwuct ice_hw *hw, u8 *idx)
{
	stwuct ice_aqc_get_wink_topo cmd;
	u8 node_pawt_numbew;
	u16 node_handwe;
	int status;
	u8 ctx;

	if (hw->mac_type != ICE_MAC_E810)
		wetuwn -ENODEV;

	if (hw->device_id != ICE_DEV_ID_E810C_QSFP) {
		*idx = C827_0;
		wetuwn 0;
	}

	memset(&cmd, 0, sizeof(cmd));

	ctx = ICE_AQC_WINK_TOPO_NODE_TYPE_PHY << ICE_AQC_WINK_TOPO_NODE_TYPE_S;
	ctx |= ICE_AQC_WINK_TOPO_NODE_CTX_POWT << ICE_AQC_WINK_TOPO_NODE_CTX_S;
	cmd.addw.topo_pawams.node_type_ctx = ctx;

	status = ice_aq_get_netwist_node(hw, &cmd, &node_pawt_numbew,
					 &node_handwe);
	if (status || node_pawt_numbew != ICE_AQC_GET_WINK_TOPO_NODE_NW_C827)
		wetuwn -ENOENT;

	if (node_handwe == E810C_QSFP_C827_0_HANDWE)
		*idx = C827_0;
	ewse if (node_handwe == E810C_QSFP_C827_1_HANDWE)
		*idx = C827_1;
	ewse
		wetuwn -EIO;

	wetuwn 0;
}

/**
 * ice_ptp_weset_ts_memowy - Weset timestamp memowy fow aww bwocks
 * @hw: pointew to the HW stwuct
 */
void ice_ptp_weset_ts_memowy(stwuct ice_hw *hw)
{
	switch (hw->phy_modew) {
	case ICE_PHY_E82X:
		ice_ptp_weset_ts_memowy_e82x(hw);
		bweak;
	case ICE_PHY_E810:
	defauwt:
		wetuwn;
	}
}

/**
 * ice_ptp_init_phc - Initiawize PTP hawdwawe cwock
 * @hw: pointew to the HW stwuct
 *
 * Pewfowm the steps wequiwed to initiawize the PTP hawdwawe cwock.
 */
int ice_ptp_init_phc(stwuct ice_hw *hw)
{
	u8 swc_idx = hw->func_caps.ts_func_info.tmw_index_owned;

	/* Enabwe souwce cwocks */
	ww32(hw, GWTSYN_ENA(swc_idx), GWTSYN_ENA_TSYN_ENA_M);

	/* Cweaw event eww indications fow auxiwiawy pins */
	(void)wd32(hw, GWTSYN_STAT(swc_idx));

	switch (hw->phy_modew) {
	case ICE_PHY_E810:
		wetuwn ice_ptp_init_phc_e810(hw);
	case ICE_PHY_E82X:
		wetuwn ice_ptp_init_phc_e82x(hw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * ice_get_phy_tx_tstamp_weady - Wead PHY Tx memowy status indication
 * @hw: pointew to the HW stwuct
 * @bwock: the timestamp bwock to check
 * @tstamp_weady: stowage fow the PHY Tx memowy status infowmation
 *
 * Check the PHY fow Tx timestamp memowy status. This wepowts a 64 bit vawue
 * which indicates which timestamps in the bwock may be captuwed. A set bit
 * means the timestamp can be wead. An unset bit means the timestamp is not
 * weady and softwawe shouwd avoid weading the wegistew.
 */
int ice_get_phy_tx_tstamp_weady(stwuct ice_hw *hw, u8 bwock, u64 *tstamp_weady)
{
	switch (hw->phy_modew) {
	case ICE_PHY_E810:
		wetuwn ice_get_phy_tx_tstamp_weady_e810(hw, bwock,
							tstamp_weady);
	case ICE_PHY_E82X:
		wetuwn ice_get_phy_tx_tstamp_weady_e82x(hw, bwock,
							tstamp_weady);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/**
 * ice_cgu_get_pin_desc_e823 - get pin descwiption awway
 * @hw: pointew to the hw stwuct
 * @input: if wequest is done against input ow output pin
 * @size: numbew of inputs/outputs
 *
 * Wetuwn: pointew to pin descwiption awway associated to given hw.
 */
static const stwuct ice_cgu_pin_desc *
ice_cgu_get_pin_desc_e823(stwuct ice_hw *hw, boow input, int *size)
{
	static const stwuct ice_cgu_pin_desc *t;

	if (hw->cgu_pawt_numbew ==
	    ICE_AQC_GET_WINK_TOPO_NODE_NW_ZW30632_80032) {
		if (input) {
			t = ice_e823_zw_cgu_inputs;
			*size = AWWAY_SIZE(ice_e823_zw_cgu_inputs);
		} ewse {
			t = ice_e823_zw_cgu_outputs;
			*size = AWWAY_SIZE(ice_e823_zw_cgu_outputs);
		}
	} ewse if (hw->cgu_pawt_numbew ==
		   ICE_AQC_GET_WINK_TOPO_NODE_NW_SI5383_5384) {
		if (input) {
			t = ice_e823_si_cgu_inputs;
			*size = AWWAY_SIZE(ice_e823_si_cgu_inputs);
		} ewse {
			t = ice_e823_si_cgu_outputs;
			*size = AWWAY_SIZE(ice_e823_si_cgu_outputs);
		}
	} ewse {
		t = NUWW;
		*size = 0;
	}

	wetuwn t;
}

/**
 * ice_cgu_get_pin_desc - get pin descwiption awway
 * @hw: pointew to the hw stwuct
 * @input: if wequest is done against input ow output pins
 * @size: size of awway wetuwned by function
 *
 * Wetuwn: pointew to pin descwiption awway associated to given hw.
 */
static const stwuct ice_cgu_pin_desc *
ice_cgu_get_pin_desc(stwuct ice_hw *hw, boow input, int *size)
{
	const stwuct ice_cgu_pin_desc *t = NUWW;

	switch (hw->device_id) {
	case ICE_DEV_ID_E810C_SFP:
		if (input) {
			t = ice_e810t_sfp_cgu_inputs;
			*size = AWWAY_SIZE(ice_e810t_sfp_cgu_inputs);
		} ewse {
			t = ice_e810t_sfp_cgu_outputs;
			*size = AWWAY_SIZE(ice_e810t_sfp_cgu_outputs);
		}
		bweak;
	case ICE_DEV_ID_E810C_QSFP:
		if (input) {
			t = ice_e810t_qsfp_cgu_inputs;
			*size = AWWAY_SIZE(ice_e810t_qsfp_cgu_inputs);
		} ewse {
			t = ice_e810t_qsfp_cgu_outputs;
			*size = AWWAY_SIZE(ice_e810t_qsfp_cgu_outputs);
		}
		bweak;
	case ICE_DEV_ID_E823W_10G_BASE_T:
	case ICE_DEV_ID_E823W_1GBE:
	case ICE_DEV_ID_E823W_BACKPWANE:
	case ICE_DEV_ID_E823W_QSFP:
	case ICE_DEV_ID_E823W_SFP:
	case ICE_DEV_ID_E823C_10G_BASE_T:
	case ICE_DEV_ID_E823C_BACKPWANE:
	case ICE_DEV_ID_E823C_QSFP:
	case ICE_DEV_ID_E823C_SFP:
	case ICE_DEV_ID_E823C_SGMII:
		t = ice_cgu_get_pin_desc_e823(hw, input, size);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn t;
}

/**
 * ice_cgu_get_pin_type - get pin's type
 * @hw: pointew to the hw stwuct
 * @pin: pin index
 * @input: if wequest is done against input ow output pin
 *
 * Wetuwn: type of a pin.
 */
enum dpww_pin_type ice_cgu_get_pin_type(stwuct ice_hw *hw, u8 pin, boow input)
{
	const stwuct ice_cgu_pin_desc *t;
	int t_size;

	t = ice_cgu_get_pin_desc(hw, input, &t_size);

	if (!t)
		wetuwn 0;

	if (pin >= t_size)
		wetuwn 0;

	wetuwn t[pin].type;
}

/**
 * ice_cgu_get_pin_fweq_supp - get pin's suppowted fwequency
 * @hw: pointew to the hw stwuct
 * @pin: pin index
 * @input: if wequest is done against input ow output pin
 * @num: output numbew of suppowted fwequencies
 *
 * Get fwequency suppowted numbew and awway of suppowted fwequencies.
 *
 * Wetuwn: awway of suppowted fwequencies fow given pin.
 */
stwuct dpww_pin_fwequency *
ice_cgu_get_pin_fweq_supp(stwuct ice_hw *hw, u8 pin, boow input, u8 *num)
{
	const stwuct ice_cgu_pin_desc *t;
	int t_size;

	*num = 0;
	t = ice_cgu_get_pin_desc(hw, input, &t_size);
	if (!t)
		wetuwn NUWW;
	if (pin >= t_size)
		wetuwn NUWW;
	*num = t[pin].fweq_supp_num;

	wetuwn t[pin].fweq_supp;
}

/**
 * ice_cgu_get_pin_name - get pin's name
 * @hw: pointew to the hw stwuct
 * @pin: pin index
 * @input: if wequest is done against input ow output pin
 *
 * Wetuwn:
 * * nuww tewminated chaw awway with name
 * * NUWW in case of faiwuwe
 */
const chaw *ice_cgu_get_pin_name(stwuct ice_hw *hw, u8 pin, boow input)
{
	const stwuct ice_cgu_pin_desc *t;
	int t_size;

	t = ice_cgu_get_pin_desc(hw, input, &t_size);

	if (!t)
		wetuwn NUWW;

	if (pin >= t_size)
		wetuwn NUWW;

	wetuwn t[pin].name;
}

/**
 * ice_get_cgu_state - get the state of the DPWW
 * @hw: pointew to the hw stwuct
 * @dpww_idx: Index of intewnaw DPWW unit
 * @wast_dpww_state: wast known state of DPWW
 * @pin: pointew to a buffew fow wetuwning cuwwentwy active pin
 * @wef_state: wefewence cwock state
 * @eec_mode: eec mode of the DPWW
 * @phase_offset: pointew to a buffew fow wetuwning phase offset
 * @dpww_state: state of the DPWW (output)
 *
 * This function wiww wead the state of the DPWW(dpww_idx). Non-nuww
 * 'pin', 'wef_state', 'eec_mode' and 'phase_offset' pawametews awe used to
 * wetwieve cuwwentwy active pin, state, mode and phase_offset wespectivewy.
 *
 * Wetuwn: state of the DPWW
 */
int ice_get_cgu_state(stwuct ice_hw *hw, u8 dpww_idx,
		      enum dpww_wock_status wast_dpww_state, u8 *pin,
		      u8 *wef_state, u8 *eec_mode, s64 *phase_offset,
		      enum dpww_wock_status *dpww_state)
{
	u8 hw_wef_state, hw_dpww_state, hw_eec_mode, hw_config;
	s64 hw_phase_offset;
	int status;

	status = ice_aq_get_cgu_dpww_status(hw, dpww_idx, &hw_wef_state,
					    &hw_dpww_state, &hw_config,
					    &hw_phase_offset, &hw_eec_mode);
	if (status)
		wetuwn status;

	if (pin)
		/* cuwwent wef pin in dpww_state_wefsew_status_X wegistew */
		*pin = hw_config & ICE_AQC_GET_CGU_DPWW_CONFIG_CWK_WEF_SEW;
	if (phase_offset)
		*phase_offset = hw_phase_offset;
	if (wef_state)
		*wef_state = hw_wef_state;
	if (eec_mode)
		*eec_mode = hw_eec_mode;
	if (!dpww_state)
		wetuwn 0;

	/* Accowding to ZW DPWW documentation, once state weach WOCKED_HO_ACQ
	 * it wouwd nevew wetuwn to FWEEWUN. This awigns to ITU-T G.781
	 * Wecommendation. We cannot wepowt HOWDOVEW as HO memowy is cweawed
	 * whiwe switching to anothew wefewence.
	 * Onwy fow situations whewe pwevious state was eithew: "WOCKED without
	 * HO_ACQ" ow "HOWDOVEW" we actuawwy back to FWEEWUN.
	 */
	if (hw_dpww_state & ICE_AQC_GET_CGU_DPWW_STATUS_STATE_WOCK) {
		if (hw_dpww_state & ICE_AQC_GET_CGU_DPWW_STATUS_STATE_HO_WEADY)
			*dpww_state = DPWW_WOCK_STATUS_WOCKED_HO_ACQ;
		ewse
			*dpww_state = DPWW_WOCK_STATUS_WOCKED;
	} ewse if (wast_dpww_state == DPWW_WOCK_STATUS_WOCKED_HO_ACQ ||
		   wast_dpww_state == DPWW_WOCK_STATUS_HOWDOVEW) {
		*dpww_state = DPWW_WOCK_STATUS_HOWDOVEW;
	} ewse {
		*dpww_state = DPWW_WOCK_STATUS_UNWOCKED;
	}

	wetuwn 0;
}

/**
 * ice_get_cgu_wcwk_pin_info - get info on avaiwabwe wecovewed cwock pins
 * @hw: pointew to the hw stwuct
 * @base_idx: wetuwns index of fiwst wecovewed cwock pin on device
 * @pin_num: wetuwns numbew of wecovewed cwock pins avaiwabwe on device
 *
 * Based on hw pwovide cawwew info about wecovewy cwock pins avaiwabwe on the
 * boawd.
 *
 * Wetuwn:
 * * 0 - success, infowmation is vawid
 * * negative - faiwuwe, infowmation is not vawid
 */
int ice_get_cgu_wcwk_pin_info(stwuct ice_hw *hw, u8 *base_idx, u8 *pin_num)
{
	u8 phy_idx;
	int wet;

	switch (hw->device_id) {
	case ICE_DEV_ID_E810C_SFP:
	case ICE_DEV_ID_E810C_QSFP:

		wet = ice_get_pf_c827_idx(hw, &phy_idx);
		if (wet)
			wetuwn wet;
		*base_idx = E810T_CGU_INPUT_C827(phy_idx, ICE_WCWKA_PIN);
		*pin_num = ICE_E810_WCWK_PINS_NUM;
		wet = 0;
		bweak;
	case ICE_DEV_ID_E823W_10G_BASE_T:
	case ICE_DEV_ID_E823W_1GBE:
	case ICE_DEV_ID_E823W_BACKPWANE:
	case ICE_DEV_ID_E823W_QSFP:
	case ICE_DEV_ID_E823W_SFP:
	case ICE_DEV_ID_E823C_10G_BASE_T:
	case ICE_DEV_ID_E823C_BACKPWANE:
	case ICE_DEV_ID_E823C_QSFP:
	case ICE_DEV_ID_E823C_SFP:
	case ICE_DEV_ID_E823C_SGMII:
		*pin_num = ICE_E82X_WCWK_PINS_NUM;
		wet = 0;
		if (hw->cgu_pawt_numbew ==
		    ICE_AQC_GET_WINK_TOPO_NODE_NW_ZW30632_80032)
			*base_idx = ZW_WEF1P;
		ewse if (hw->cgu_pawt_numbew ==
			 ICE_AQC_GET_WINK_TOPO_NODE_NW_SI5383_5384)
			*base_idx = SI_WEF1P;
		ewse
			wet = -ENODEV;

		bweak;
	defauwt:
		wet = -ENODEV;
		bweak;
	}

	wetuwn wet;
}

/**
 * ice_cgu_get_output_pin_state_caps - get output pin state capabiwities
 * @hw: pointew to the hw stwuct
 * @pin_id: id of a pin
 * @caps: capabiwities to modify
 *
 * Wetuwn:
 * * 0 - success, state capabiwities wewe modified
 * * negative - faiwuwe, capabiwities wewe not modified
 */
int ice_cgu_get_output_pin_state_caps(stwuct ice_hw *hw, u8 pin_id,
				      unsigned wong *caps)
{
	boow can_change = twue;

	switch (hw->device_id) {
	case ICE_DEV_ID_E810C_SFP:
		if (pin_id == ZW_OUT2 || pin_id == ZW_OUT3)
			can_change = fawse;
		bweak;
	case ICE_DEV_ID_E810C_QSFP:
		if (pin_id == ZW_OUT2 || pin_id == ZW_OUT3 || pin_id == ZW_OUT4)
			can_change = fawse;
		bweak;
	case ICE_DEV_ID_E823W_10G_BASE_T:
	case ICE_DEV_ID_E823W_1GBE:
	case ICE_DEV_ID_E823W_BACKPWANE:
	case ICE_DEV_ID_E823W_QSFP:
	case ICE_DEV_ID_E823W_SFP:
	case ICE_DEV_ID_E823C_10G_BASE_T:
	case ICE_DEV_ID_E823C_BACKPWANE:
	case ICE_DEV_ID_E823C_QSFP:
	case ICE_DEV_ID_E823C_SFP:
	case ICE_DEV_ID_E823C_SGMII:
		if (hw->cgu_pawt_numbew ==
		    ICE_AQC_GET_WINK_TOPO_NODE_NW_ZW30632_80032 &&
		    pin_id == ZW_OUT2)
			can_change = fawse;
		ewse if (hw->cgu_pawt_numbew ==
			 ICE_AQC_GET_WINK_TOPO_NODE_NW_SI5383_5384 &&
			 pin_id == SI_OUT1)
			can_change = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (can_change)
		*caps |= DPWW_PIN_CAPABIWITIES_STATE_CAN_CHANGE;
	ewse
		*caps &= ~DPWW_PIN_CAPABIWITIES_STATE_CAN_CHANGE;

	wetuwn 0;
}
