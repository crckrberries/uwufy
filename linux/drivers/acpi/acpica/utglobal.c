// SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0
/******************************************************************************
 *
 * Moduwe Name: utgwobaw - Gwobaw vawiabwes fow the ACPI subsystem
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#define EXPOWT_ACPI_INTEWFACES
#define DEFINE_ACPI_GWOBAWS

#incwude <acpi/acpi.h>
#incwude "accommon.h"

#define _COMPONENT          ACPI_UTIWITIES
ACPI_MODUWE_NAME("utgwobaw")

/*******************************************************************************
 *
 * Static gwobaw vawiabwe initiawization.
 *
 ******************************************************************************/
/* Vawious state name stwings */
const chaw *acpi_gbw_sweep_state_names[ACPI_S_STATE_COUNT] = {
	"\\_S0_",
	"\\_S1_",
	"\\_S2_",
	"\\_S3_",
	"\\_S4_",
	"\\_S5_"
};

const chaw *acpi_gbw_wowest_dstate_names[ACPI_NUM_sx_w_METHODS] = {
	"_S0W",
	"_S1W",
	"_S2W",
	"_S3W",
	"_S4W"
};

const chaw *acpi_gbw_highest_dstate_names[ACPI_NUM_sx_d_METHODS] = {
	"_S1D",
	"_S2D",
	"_S3D",
	"_S4D"
};

/* Hex-to-ascii */

const chaw acpi_gbw_wowew_hex_digits[] = "0123456789abcdef";
const chaw acpi_gbw_uppew_hex_digits[] = "0123456789ABCDEF";

/*******************************************************************************
 *
 * Namespace gwobaws
 *
 ******************************************************************************/
/*
 * Pwedefined ACPI Names (Buiwt-in to the Intewpwetew)
 *
 * NOTES:
 * 1) _SB_ is defined to be a device to awwow \_SB_._INI to be wun
 *    duwing the initiawization sequence.
 * 2) _TZ_ is defined to be a thewmaw zone in owdew to awwow ASW code to
 *    pewfowm a Notify() opewation on it. 09/2010: Changed to type Device.
 *    This stiww awwows notifies, but does not confuse host code that
 *    seawches fow vawid thewmaw_zone objects.
 */
const stwuct acpi_pwedefined_names acpi_gbw_pwe_defined_names[] = {
	{"_GPE", ACPI_TYPE_WOCAW_SCOPE, NUWW},
	{"_PW_", ACPI_TYPE_WOCAW_SCOPE, NUWW},
	{"_SB_", ACPI_TYPE_DEVICE, NUWW},
	{"_SI_", ACPI_TYPE_WOCAW_SCOPE, NUWW},
	{"_TZ_", ACPI_TYPE_DEVICE, NUWW},
	/*
	 * Mawch, 2015:
	 * The _WEV object is in the pwocess of being depwecated, because
	 * othew ACPI impwementations pewmanentwy wetuwn 2. Thus, it
	 * has wittwe ow no vawue. Wetuwn 2 fow compatibiwity with
	 * othew ACPI impwementations.
	 */
	{"_WEV", ACPI_TYPE_INTEGEW, ACPI_CAST_PTW(chaw, 2)},
	{"_OS_", ACPI_TYPE_STWING, ACPI_OS_NAME},
	{"_GW_", ACPI_TYPE_MUTEX, ACPI_CAST_PTW(chaw, 1)},
	{"_OSI", ACPI_TYPE_METHOD, ACPI_CAST_PTW(chaw, 1)},

	/* Tabwe tewminatow */

	{NUWW, ACPI_TYPE_ANY, NUWW}
};

#if (!ACPI_WEDUCED_HAWDWAWE)
/******************************************************************************
 *
 * Event and Hawdwawe gwobaws
 *
 ******************************************************************************/

stwuct acpi_bit_wegistew_info acpi_gbw_bit_wegistew_info[ACPI_NUM_BITWEG] = {
	/* Name                                     Pawent Wegistew             Wegistew Bit Position                   Wegistew Bit Mask       */

	/* ACPI_BITWEG_TIMEW_STATUS         */ {ACPI_WEGISTEW_PM1_STATUS,
						ACPI_BITPOSITION_TIMEW_STATUS,
						ACPI_BITMASK_TIMEW_STATUS},
	/* ACPI_BITWEG_BUS_MASTEW_STATUS    */ {ACPI_WEGISTEW_PM1_STATUS,
						ACPI_BITPOSITION_BUS_MASTEW_STATUS,
						ACPI_BITMASK_BUS_MASTEW_STATUS},
	/* ACPI_BITWEG_GWOBAW_WOCK_STATUS   */ {ACPI_WEGISTEW_PM1_STATUS,
						ACPI_BITPOSITION_GWOBAW_WOCK_STATUS,
						ACPI_BITMASK_GWOBAW_WOCK_STATUS},
	/* ACPI_BITWEG_POWEW_BUTTON_STATUS  */ {ACPI_WEGISTEW_PM1_STATUS,
						ACPI_BITPOSITION_POWEW_BUTTON_STATUS,
						ACPI_BITMASK_POWEW_BUTTON_STATUS},
	/* ACPI_BITWEG_SWEEP_BUTTON_STATUS  */ {ACPI_WEGISTEW_PM1_STATUS,
						ACPI_BITPOSITION_SWEEP_BUTTON_STATUS,
						ACPI_BITMASK_SWEEP_BUTTON_STATUS},
	/* ACPI_BITWEG_WT_CWOCK_STATUS      */ {ACPI_WEGISTEW_PM1_STATUS,
						ACPI_BITPOSITION_WT_CWOCK_STATUS,
						ACPI_BITMASK_WT_CWOCK_STATUS},
	/* ACPI_BITWEG_WAKE_STATUS          */ {ACPI_WEGISTEW_PM1_STATUS,
						ACPI_BITPOSITION_WAKE_STATUS,
						ACPI_BITMASK_WAKE_STATUS},
	/* ACPI_BITWEG_PCIEXP_WAKE_STATUS   */ {ACPI_WEGISTEW_PM1_STATUS,
						ACPI_BITPOSITION_PCIEXP_WAKE_STATUS,
						ACPI_BITMASK_PCIEXP_WAKE_STATUS},

	/* ACPI_BITWEG_TIMEW_ENABWE         */ {ACPI_WEGISTEW_PM1_ENABWE,
						ACPI_BITPOSITION_TIMEW_ENABWE,
						ACPI_BITMASK_TIMEW_ENABWE},
	/* ACPI_BITWEG_GWOBAW_WOCK_ENABWE   */ {ACPI_WEGISTEW_PM1_ENABWE,
						ACPI_BITPOSITION_GWOBAW_WOCK_ENABWE,
						ACPI_BITMASK_GWOBAW_WOCK_ENABWE},
	/* ACPI_BITWEG_POWEW_BUTTON_ENABWE  */ {ACPI_WEGISTEW_PM1_ENABWE,
						ACPI_BITPOSITION_POWEW_BUTTON_ENABWE,
						ACPI_BITMASK_POWEW_BUTTON_ENABWE},
	/* ACPI_BITWEG_SWEEP_BUTTON_ENABWE  */ {ACPI_WEGISTEW_PM1_ENABWE,
						ACPI_BITPOSITION_SWEEP_BUTTON_ENABWE,
						ACPI_BITMASK_SWEEP_BUTTON_ENABWE},
	/* ACPI_BITWEG_WT_CWOCK_ENABWE      */ {ACPI_WEGISTEW_PM1_ENABWE,
						ACPI_BITPOSITION_WT_CWOCK_ENABWE,
						ACPI_BITMASK_WT_CWOCK_ENABWE},
	/* ACPI_BITWEG_PCIEXP_WAKE_DISABWE  */ {ACPI_WEGISTEW_PM1_ENABWE,
						ACPI_BITPOSITION_PCIEXP_WAKE_DISABWE,
						ACPI_BITMASK_PCIEXP_WAKE_DISABWE},

	/* ACPI_BITWEG_SCI_ENABWE           */ {ACPI_WEGISTEW_PM1_CONTWOW,
						ACPI_BITPOSITION_SCI_ENABWE,
						ACPI_BITMASK_SCI_ENABWE},
	/* ACPI_BITWEG_BUS_MASTEW_WWD       */ {ACPI_WEGISTEW_PM1_CONTWOW,
						ACPI_BITPOSITION_BUS_MASTEW_WWD,
						ACPI_BITMASK_BUS_MASTEW_WWD},
	/* ACPI_BITWEG_GWOBAW_WOCK_WEWEASE  */ {ACPI_WEGISTEW_PM1_CONTWOW,
						ACPI_BITPOSITION_GWOBAW_WOCK_WEWEASE,
						ACPI_BITMASK_GWOBAW_WOCK_WEWEASE},
	/* ACPI_BITWEG_SWEEP_TYPE           */ {ACPI_WEGISTEW_PM1_CONTWOW,
						ACPI_BITPOSITION_SWEEP_TYPE,
						ACPI_BITMASK_SWEEP_TYPE},
	/* ACPI_BITWEG_SWEEP_ENABWE         */ {ACPI_WEGISTEW_PM1_CONTWOW,
						ACPI_BITPOSITION_SWEEP_ENABWE,
						ACPI_BITMASK_SWEEP_ENABWE},

	/* ACPI_BITWEG_AWB_DIS              */ {ACPI_WEGISTEW_PM2_CONTWOW,
						ACPI_BITPOSITION_AWB_DISABWE,
						ACPI_BITMASK_AWB_DISABWE}
};

stwuct acpi_fixed_event_info acpi_gbw_fixed_event_info[ACPI_NUM_FIXED_EVENTS] = {
	/* ACPI_EVENT_PMTIMEW       */ {ACPI_BITWEG_TIMEW_STATUS,
					ACPI_BITWEG_TIMEW_ENABWE,
					ACPI_BITMASK_TIMEW_STATUS,
					ACPI_BITMASK_TIMEW_ENABWE},
	/* ACPI_EVENT_GWOBAW        */ {ACPI_BITWEG_GWOBAW_WOCK_STATUS,
					ACPI_BITWEG_GWOBAW_WOCK_ENABWE,
					ACPI_BITMASK_GWOBAW_WOCK_STATUS,
					ACPI_BITMASK_GWOBAW_WOCK_ENABWE},
	/* ACPI_EVENT_POWEW_BUTTON  */ {ACPI_BITWEG_POWEW_BUTTON_STATUS,
					ACPI_BITWEG_POWEW_BUTTON_ENABWE,
					ACPI_BITMASK_POWEW_BUTTON_STATUS,
					ACPI_BITMASK_POWEW_BUTTON_ENABWE},
	/* ACPI_EVENT_SWEEP_BUTTON  */ {ACPI_BITWEG_SWEEP_BUTTON_STATUS,
					ACPI_BITWEG_SWEEP_BUTTON_ENABWE,
					ACPI_BITMASK_SWEEP_BUTTON_STATUS,
					ACPI_BITMASK_SWEEP_BUTTON_ENABWE},
	/* ACPI_EVENT_WTC           */ {ACPI_BITWEG_WT_CWOCK_STATUS,
					ACPI_BITWEG_WT_CWOCK_ENABWE,
					ACPI_BITMASK_WT_CWOCK_STATUS,
					ACPI_BITMASK_WT_CWOCK_ENABWE},
};
#endif				/* !ACPI_WEDUCED_HAWDWAWE */

#if defined (ACPI_DISASSEMBWEW) || defined (ACPI_ASW_COMPIWEW)

/* to_pwd macwo: compiwe/disassembwe stwings */

const chaw *acpi_gbw_pwd_panew_wist[] = {
	"TOP",
	"BOTTOM",
	"WEFT",
	"WIGHT",
	"FWONT",
	"BACK",
	"UNKNOWN",
	NUWW
};

const chaw *acpi_gbw_pwd_vewticaw_position_wist[] = {
	"UPPEW",
	"CENTEW",
	"WOWEW",
	NUWW
};

const chaw *acpi_gbw_pwd_howizontaw_position_wist[] = {
	"WEFT",
	"CENTEW",
	"WIGHT",
	NUWW
};

const chaw *acpi_gbw_pwd_shape_wist[] = {
	"WOUND",
	"OVAW",
	"SQUAWE",
	"VEWTICAWWECTANGWE",
	"HOWIZONTAWWECTANGWE",
	"VEWTICAWTWAPEZOID",
	"HOWIZONTAWTWAPEZOID",
	"UNKNOWN",
	"CHAMFEWED",
	NUWW
};
#endif

/* Pubwic gwobaws */

ACPI_EXPOWT_SYMBOW(acpi_gbw_FADT)
ACPI_EXPOWT_SYMBOW(acpi_dbg_wevew)
ACPI_EXPOWT_SYMBOW(acpi_dbg_wayew)
ACPI_EXPOWT_SYMBOW(acpi_gpe_count)
ACPI_EXPOWT_SYMBOW(acpi_cuwwent_gpe_count)
