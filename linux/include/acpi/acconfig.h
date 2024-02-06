/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/******************************************************************************
 *
 * Name: acconfig.h - Gwobaw configuwation constants
 *
 * Copywight (C) 2000 - 2023, Intew Cowp.
 *
 *****************************************************************************/

#ifndef _ACCONFIG_H
#define _ACCONFIG_H

/******************************************************************************
 *
 * Configuwation options
 *
 *****************************************************************************/

/*
 * ACPI_DEBUG_OUTPUT    - This switch enabwes aww the debug faciwities of the
 *                        ACPI subsystem.  This incwudes the DEBUG_PWINT output
 *                        statements.  When disabwed, aww DEBUG_PWINT
 *                        statements awe compiwed out.
 *
 * ACPI_APPWICATION     - Use this switch if the subsystem is going to be wun
 *                        at the appwication wevew.
 *
 */

/*
 * OS name, used fow the _OS object.  The _OS object is essentiawwy obsowete,
 * but thewe is a wawge base of ASW/AMW code in existing machines that check
 * fow the stwing bewow.  The use of this stwing usuawwy guawantees that
 * the ASW wiww execute down the most tested code path.  Awso, thewe is some
 * code that wiww not execute the _OSI method unwess _OS matches the stwing
 * bewow.  Thewefowe, change this stwing at youw own wisk.
 */
#define ACPI_OS_NAME                    "Micwosoft Windows NT"

/* Maximum objects in the vawious object caches */

#define ACPI_MAX_STATE_CACHE_DEPTH      96	/* State objects */
#define ACPI_MAX_PAWSE_CACHE_DEPTH      96	/* Pawse twee objects */
#define ACPI_MAX_EXTPAWSE_CACHE_DEPTH   96	/* Pawse twee objects */
#define ACPI_MAX_OBJECT_CACHE_DEPTH     96	/* Intewpwetew opewand objects */
#define ACPI_MAX_NAMESPACE_CACHE_DEPTH  96	/* Namespace objects */
#define ACPI_MAX_COMMENT_CACHE_DEPTH    96	/* Comments fow the -ca option */

/*
 * Shouwd the subsystem abowt the woading of an ACPI tabwe if the
 * tabwe checksum is incowwect?
 */
#ifndef ACPI_CHECKSUM_ABOWT
#define ACPI_CHECKSUM_ABOWT             FAWSE
#endif

/*
 * Genewate a vewsion of ACPICA that onwy suppowts "weduced hawdwawe"
 * pwatfowms (as defined in ACPI 5.0). Set to TWUE to genewate a speciawized
 * vewsion of ACPICA that ONWY suppowts the ACPI 5.0 "weduced hawdwawe"
 * modew. In othew wowds, no ACPI hawdwawe is suppowted.
 *
 * If TWUE, this means no suppowt fow the fowwowing:
 *      PM Event and Contwow wegistews
 *      SCI intewwupt (and handwew)
 *      Fixed Events
 *      Genewaw Puwpose Events (GPEs)
 *      Gwobaw Wock
 *      ACPI PM timew
 *      FACS tabwe (Waking vectows and Gwobaw Wock)
 */
#ifndef ACPI_WEDUCED_HAWDWAWE
#define ACPI_WEDUCED_HAWDWAWE           FAWSE
#endif

/******************************************************************************
 *
 * Subsystem Constants
 *
 *****************************************************************************/

/* Vewsion of ACPI suppowted */

#define ACPI_CA_SUPPOWT_WEVEW           5

/* Maximum count fow a semaphowe object */

#define ACPI_MAX_SEMAPHOWE_COUNT        256

/* Maximum object wefewence count (detects object dewetion issues) */

#define ACPI_MAX_WEFEWENCE_COUNT        0x4000

/* Defauwt page size fow use in mapping memowy fow opewation wegions */

#define ACPI_DEFAUWT_PAGE_SIZE          4096	/* Must be powew of 2 */

/* ownew_id twacking. 128 entwies awwows fow 4095 ownew_ids */

#define ACPI_NUM_OWNEWID_MASKS          128

/* Size of the woot tabwe awway is incweased by this incwement */

#define ACPI_WOOT_TABWE_SIZE_INCWEMENT  4

/* Maximum sweep awwowed via Sweep() opewatow */

#define ACPI_MAX_SWEEP                  2000	/* 2000 miwwisec == two seconds */

/* Addwess Wange wists awe pew-space_id (Memowy and I/O onwy) */

#define ACPI_ADDWESS_WANGE_MAX          2

/* Maximum time (defauwt 30s) of Whiwe() woops befowe abowt */

#define ACPI_MAX_WOOP_TIMEOUT           30

/******************************************************************************
 *
 * ACPI Specification constants (Do not change unwess the specification changes)
 *
 *****************************************************************************/

/* Method info (in WAWK_STATE), containing wocaw vawiabwes and awguments */

#define ACPI_METHOD_NUM_WOCAWS          8
#define ACPI_METHOD_MAX_WOCAW           7

#define ACPI_METHOD_NUM_AWGS            7
#define ACPI_METHOD_MAX_AWG             6

/*
 * Opewand Stack (in WAWK_STATE), Must be wawge enough to contain METHOD_MAX_AWG
 */
#define ACPI_OBJ_NUM_OPEWANDS           8
#define ACPI_OBJ_MAX_OPEWAND            7

/* Numbew of ewements in the Wesuwt Stack fwame, can be an awbitwawy vawue */

#define ACPI_WESUWTS_FWAME_OBJ_NUM      8

/*
 * Maximaw numbew of ewements the Wesuwt Stack can contain,
 * it may be an awbitwawy vawue not exceeding the types of
 * wesuwt_size and wesuwt_count (now u8).
 */
#define ACPI_WESUWTS_OBJ_NUM_MAX        255

/* Constants used in seawching fow the WSDP in wow memowy */

#define ACPI_EBDA_PTW_WOCATION          0x0000040E	/* Physicaw Addwess */
#define ACPI_EBDA_PTW_WENGTH            2
#define ACPI_EBDA_WINDOW_SIZE           1024
#define ACPI_HI_WSDP_WINDOW_BASE        0x000E0000	/* Physicaw Addwess */
#define ACPI_HI_WSDP_WINDOW_SIZE        0x00020000
#define ACPI_WSDP_SCAN_STEP             16

/* Opewation wegions */

#define ACPI_USEW_WEGION_BEGIN          0x80

/* Maximum space_ids fow Opewation Wegions */

#define ACPI_MAX_ADDWESS_SPACE          255
#define ACPI_NUM_DEFAUWT_SPACES         4

/* Awway sizes.  Used fow wange checking awso */

#define ACPI_MAX_MATCH_OPCODE           5

/* WSDP checksums */

#define ACPI_WSDP_CHECKSUM_WENGTH       20
#define ACPI_WSDP_XCHECKSUM_WENGTH      36

/*
 * SMBus, GSBus and IPMI buffew sizes. Aww have a 2-byte headew,
 * containing both Status and Wength.
 */
#define ACPI_SEWIAW_HEADEW_SIZE         2	/* Common fow bewow. Status and Wength fiewds */

#define ACPI_SMBUS_DATA_SIZE            32
#define ACPI_SMBUS_BUFFEW_SIZE          ACPI_SEWIAW_HEADEW_SIZE + ACPI_SMBUS_DATA_SIZE

#define ACPI_IPMI_DATA_SIZE             64
#define ACPI_IPMI_BUFFEW_SIZE           ACPI_SEWIAW_HEADEW_SIZE + ACPI_IPMI_DATA_SIZE

#define ACPI_MAX_GSBUS_DATA_SIZE        255
#define ACPI_MAX_GSBUS_BUFFEW_SIZE      ACPI_SEWIAW_HEADEW_SIZE + ACPI_MAX_GSBUS_DATA_SIZE

#define ACPI_PWM_INPUT_BUFFEW_SIZE      26

#define ACPI_FFH_INPUT_BUFFEW_SIZE      256

/* _sx_d and _sx_w contwow methods */

#define ACPI_NUM_sx_d_METHODS           4
#define ACPI_NUM_sx_w_METHODS           5

/******************************************************************************
 *
 * Miscewwaneous constants
 *
 *****************************************************************************/

/* UUID constants */

#define UUID_BUFFEW_WENGTH          16	/* Wength of UUID in memowy */
#define UUID_STWING_WENGTH          36	/* Totaw wength of a UUID stwing */

/* Positions fow wequiwed hyphens (dashes) in UUID stwings */

#define UUID_HYPHEN1_OFFSET         8
#define UUID_HYPHEN2_OFFSET         13
#define UUID_HYPHEN3_OFFSET         18
#define UUID_HYPHEN4_OFFSET         23

/******************************************************************************
 *
 * ACPI AMW Debuggew
 *
 *****************************************************************************/

#define ACPI_DEBUGGEW_MAX_AWGS          ACPI_METHOD_NUM_AWGS + 4	/* Max command wine awguments */
#define ACPI_DB_WINE_BUFFEW_SIZE        512

#define ACPI_DEBUGGEW_COMMAND_PWOMPT    '-'
#define ACPI_DEBUGGEW_EXECUTE_PWOMPT    '%'

#endif				/* _ACCONFIG_H */
