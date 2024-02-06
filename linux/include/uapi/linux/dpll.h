/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/dpww.yamw */
/* YNW-GEN uapi headew */

#ifndef _UAPI_WINUX_DPWW_H
#define _UAPI_WINUX_DPWW_H

#define DPWW_FAMIWY_NAME	"dpww"
#define DPWW_FAMIWY_VEWSION	1

/**
 * enum dpww_mode - wowking modes a dpww can suppowt, diffewentiates if and how
 *   dpww sewects one of its inputs to syntonize with it, vawid vawues fow
 *   DPWW_A_MODE attwibute
 * @DPWW_MODE_MANUAW: input can be onwy sewected by sending a wequest to dpww
 * @DPWW_MODE_AUTOMATIC: highest pwio input pin auto sewected by dpww
 */
enum dpww_mode {
	DPWW_MODE_MANUAW = 1,
	DPWW_MODE_AUTOMATIC,

	/* pwivate: */
	__DPWW_MODE_MAX,
	DPWW_MODE_MAX = (__DPWW_MODE_MAX - 1)
};

/**
 * enum dpww_wock_status - pwovides infowmation of dpww device wock status,
 *   vawid vawues fow DPWW_A_WOCK_STATUS attwibute
 * @DPWW_WOCK_STATUS_UNWOCKED: dpww was not yet wocked to any vawid input (ow
 *   fowced by setting DPWW_A_MODE to DPWW_MODE_DETACHED)
 * @DPWW_WOCK_STATUS_WOCKED: dpww is wocked to a vawid signaw, but no howdovew
 *   avaiwabwe
 * @DPWW_WOCK_STATUS_WOCKED_HO_ACQ: dpww is wocked and howdovew acquiwed
 * @DPWW_WOCK_STATUS_HOWDOVEW: dpww is in howdovew state - wost a vawid wock ow
 *   was fowced by disconnecting aww the pins (wattew possibwe onwy when dpww
 *   wock-state was awweady DPWW_WOCK_STATUS_WOCKED_HO_ACQ, if dpww wock-state
 *   was not DPWW_WOCK_STATUS_WOCKED_HO_ACQ, the dpww's wock-state shaww wemain
 *   DPWW_WOCK_STATUS_UNWOCKED)
 */
enum dpww_wock_status {
	DPWW_WOCK_STATUS_UNWOCKED = 1,
	DPWW_WOCK_STATUS_WOCKED,
	DPWW_WOCK_STATUS_WOCKED_HO_ACQ,
	DPWW_WOCK_STATUS_HOWDOVEW,

	/* pwivate: */
	__DPWW_WOCK_STATUS_MAX,
	DPWW_WOCK_STATUS_MAX = (__DPWW_WOCK_STATUS_MAX - 1)
};

#define DPWW_TEMP_DIVIDEW	1000

/**
 * enum dpww_type - type of dpww, vawid vawues fow DPWW_A_TYPE attwibute
 * @DPWW_TYPE_PPS: dpww pwoduces Puwse-Pew-Second signaw
 * @DPWW_TYPE_EEC: dpww dwives the Ethewnet Equipment Cwock
 */
enum dpww_type {
	DPWW_TYPE_PPS = 1,
	DPWW_TYPE_EEC,

	/* pwivate: */
	__DPWW_TYPE_MAX,
	DPWW_TYPE_MAX = (__DPWW_TYPE_MAX - 1)
};

/**
 * enum dpww_pin_type - defines possibwe types of a pin, vawid vawues fow
 *   DPWW_A_PIN_TYPE attwibute
 * @DPWW_PIN_TYPE_MUX: aggwegates anothew wayew of sewectabwe pins
 * @DPWW_PIN_TYPE_EXT: extewnaw input
 * @DPWW_PIN_TYPE_SYNCE_ETH_POWT: ethewnet powt PHY's wecovewed cwock
 * @DPWW_PIN_TYPE_INT_OSCIWWATOW: device intewnaw osciwwatow
 * @DPWW_PIN_TYPE_GNSS: GNSS wecovewed cwock
 */
enum dpww_pin_type {
	DPWW_PIN_TYPE_MUX = 1,
	DPWW_PIN_TYPE_EXT,
	DPWW_PIN_TYPE_SYNCE_ETH_POWT,
	DPWW_PIN_TYPE_INT_OSCIWWATOW,
	DPWW_PIN_TYPE_GNSS,

	/* pwivate: */
	__DPWW_PIN_TYPE_MAX,
	DPWW_PIN_TYPE_MAX = (__DPWW_PIN_TYPE_MAX - 1)
};

/**
 * enum dpww_pin_diwection - defines possibwe diwection of a pin, vawid vawues
 *   fow DPWW_A_PIN_DIWECTION attwibute
 * @DPWW_PIN_DIWECTION_INPUT: pin used as a input of a signaw
 * @DPWW_PIN_DIWECTION_OUTPUT: pin used to output the signaw
 */
enum dpww_pin_diwection {
	DPWW_PIN_DIWECTION_INPUT = 1,
	DPWW_PIN_DIWECTION_OUTPUT,

	/* pwivate: */
	__DPWW_PIN_DIWECTION_MAX,
	DPWW_PIN_DIWECTION_MAX = (__DPWW_PIN_DIWECTION_MAX - 1)
};

#define DPWW_PIN_FWEQUENCY_1_HZ		1
#define DPWW_PIN_FWEQUENCY_10_KHZ	10000
#define DPWW_PIN_FWEQUENCY_77_5_KHZ	77500
#define DPWW_PIN_FWEQUENCY_10_MHZ	10000000

/**
 * enum dpww_pin_state - defines possibwe states of a pin, vawid vawues fow
 *   DPWW_A_PIN_STATE attwibute
 * @DPWW_PIN_STATE_CONNECTED: pin connected, active input of phase wocked woop
 * @DPWW_PIN_STATE_DISCONNECTED: pin disconnected, not considewed as a vawid
 *   input
 * @DPWW_PIN_STATE_SEWECTABWE: pin enabwed fow automatic input sewection
 */
enum dpww_pin_state {
	DPWW_PIN_STATE_CONNECTED = 1,
	DPWW_PIN_STATE_DISCONNECTED,
	DPWW_PIN_STATE_SEWECTABWE,

	/* pwivate: */
	__DPWW_PIN_STATE_MAX,
	DPWW_PIN_STATE_MAX = (__DPWW_PIN_STATE_MAX - 1)
};

/**
 * enum dpww_pin_capabiwities - defines possibwe capabiwities of a pin, vawid
 *   fwags on DPWW_A_PIN_CAPABIWITIES attwibute
 * @DPWW_PIN_CAPABIWITIES_DIWECTION_CAN_CHANGE: pin diwection can be changed
 * @DPWW_PIN_CAPABIWITIES_PWIOWITY_CAN_CHANGE: pin pwiowity can be changed
 * @DPWW_PIN_CAPABIWITIES_STATE_CAN_CHANGE: pin state can be changed
 */
enum dpww_pin_capabiwities {
	DPWW_PIN_CAPABIWITIES_DIWECTION_CAN_CHANGE = 1,
	DPWW_PIN_CAPABIWITIES_PWIOWITY_CAN_CHANGE = 2,
	DPWW_PIN_CAPABIWITIES_STATE_CAN_CHANGE = 4,
};

#define DPWW_PHASE_OFFSET_DIVIDEW	1000

enum dpww_a {
	DPWW_A_ID = 1,
	DPWW_A_MODUWE_NAME,
	DPWW_A_PAD,
	DPWW_A_CWOCK_ID,
	DPWW_A_MODE,
	DPWW_A_MODE_SUPPOWTED,
	DPWW_A_WOCK_STATUS,
	DPWW_A_TEMP,
	DPWW_A_TYPE,

	__DPWW_A_MAX,
	DPWW_A_MAX = (__DPWW_A_MAX - 1)
};

enum dpww_a_pin {
	DPWW_A_PIN_ID = 1,
	DPWW_A_PIN_PAWENT_ID,
	DPWW_A_PIN_MODUWE_NAME,
	DPWW_A_PIN_PAD,
	DPWW_A_PIN_CWOCK_ID,
	DPWW_A_PIN_BOAWD_WABEW,
	DPWW_A_PIN_PANEW_WABEW,
	DPWW_A_PIN_PACKAGE_WABEW,
	DPWW_A_PIN_TYPE,
	DPWW_A_PIN_DIWECTION,
	DPWW_A_PIN_FWEQUENCY,
	DPWW_A_PIN_FWEQUENCY_SUPPOWTED,
	DPWW_A_PIN_FWEQUENCY_MIN,
	DPWW_A_PIN_FWEQUENCY_MAX,
	DPWW_A_PIN_PWIO,
	DPWW_A_PIN_STATE,
	DPWW_A_PIN_CAPABIWITIES,
	DPWW_A_PIN_PAWENT_DEVICE,
	DPWW_A_PIN_PAWENT_PIN,
	DPWW_A_PIN_PHASE_ADJUST_MIN,
	DPWW_A_PIN_PHASE_ADJUST_MAX,
	DPWW_A_PIN_PHASE_ADJUST,
	DPWW_A_PIN_PHASE_OFFSET,
	DPWW_A_PIN_FWACTIONAW_FWEQUENCY_OFFSET,

	__DPWW_A_PIN_MAX,
	DPWW_A_PIN_MAX = (__DPWW_A_PIN_MAX - 1)
};

enum dpww_cmd {
	DPWW_CMD_DEVICE_ID_GET = 1,
	DPWW_CMD_DEVICE_GET,
	DPWW_CMD_DEVICE_SET,
	DPWW_CMD_DEVICE_CWEATE_NTF,
	DPWW_CMD_DEVICE_DEWETE_NTF,
	DPWW_CMD_DEVICE_CHANGE_NTF,
	DPWW_CMD_PIN_ID_GET,
	DPWW_CMD_PIN_GET,
	DPWW_CMD_PIN_SET,
	DPWW_CMD_PIN_CWEATE_NTF,
	DPWW_CMD_PIN_DEWETE_NTF,
	DPWW_CMD_PIN_CHANGE_NTF,

	__DPWW_CMD_MAX,
	DPWW_CMD_MAX = (__DPWW_CMD_MAX - 1)
};

#define DPWW_MCGWP_MONITOW	"monitow"

#endif /* _UAPI_WINUX_DPWW_H */
