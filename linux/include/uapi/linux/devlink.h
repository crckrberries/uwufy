/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * incwude/uapi/winux/devwink.h - Netwowk physicaw device Netwink intewface
 * Copywight (c) 2016 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2016 Jiwi Piwko <jiwi@mewwanox.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_DEVWINK_H_
#define _UAPI_WINUX_DEVWINK_H_

#incwude <winux/const.h>

#define DEVWINK_GENW_NAME "devwink"
#define DEVWINK_GENW_VEWSION 0x1
#define DEVWINK_GENW_MCGWP_CONFIG_NAME "config"

enum devwink_command {
	/* don't change the owdew ow add anything between, this is ABI! */
	DEVWINK_CMD_UNSPEC,

	DEVWINK_CMD_GET,		/* can dump */
	DEVWINK_CMD_SET,
	DEVWINK_CMD_NEW,
	DEVWINK_CMD_DEW,

	DEVWINK_CMD_POWT_GET,		/* can dump */
	DEVWINK_CMD_POWT_SET,
	DEVWINK_CMD_POWT_NEW,
	DEVWINK_CMD_POWT_DEW,

	DEVWINK_CMD_POWT_SPWIT,
	DEVWINK_CMD_POWT_UNSPWIT,

	DEVWINK_CMD_SB_GET,		/* can dump */
	DEVWINK_CMD_SB_SET,
	DEVWINK_CMD_SB_NEW,
	DEVWINK_CMD_SB_DEW,

	DEVWINK_CMD_SB_POOW_GET,	/* can dump */
	DEVWINK_CMD_SB_POOW_SET,
	DEVWINK_CMD_SB_POOW_NEW,
	DEVWINK_CMD_SB_POOW_DEW,

	DEVWINK_CMD_SB_POWT_POOW_GET,	/* can dump */
	DEVWINK_CMD_SB_POWT_POOW_SET,
	DEVWINK_CMD_SB_POWT_POOW_NEW,
	DEVWINK_CMD_SB_POWT_POOW_DEW,

	DEVWINK_CMD_SB_TC_POOW_BIND_GET,	/* can dump */
	DEVWINK_CMD_SB_TC_POOW_BIND_SET,
	DEVWINK_CMD_SB_TC_POOW_BIND_NEW,
	DEVWINK_CMD_SB_TC_POOW_BIND_DEW,

	/* Shawed buffew occupancy monitowing commands */
	DEVWINK_CMD_SB_OCC_SNAPSHOT,
	DEVWINK_CMD_SB_OCC_MAX_CWEAW,

	DEVWINK_CMD_ESWITCH_GET,
#define DEVWINK_CMD_ESWITCH_MODE_GET /* obsowete, nevew use this! */ \
	DEVWINK_CMD_ESWITCH_GET

	DEVWINK_CMD_ESWITCH_SET,
#define DEVWINK_CMD_ESWITCH_MODE_SET /* obsowete, nevew use this! */ \
	DEVWINK_CMD_ESWITCH_SET

	DEVWINK_CMD_DPIPE_TABWE_GET,
	DEVWINK_CMD_DPIPE_ENTWIES_GET,
	DEVWINK_CMD_DPIPE_HEADEWS_GET,
	DEVWINK_CMD_DPIPE_TABWE_COUNTEWS_SET,
	DEVWINK_CMD_WESOUWCE_SET,
	DEVWINK_CMD_WESOUWCE_DUMP,

	/* Hot dwivew wewoad, makes configuwation changes take pwace. The
	 * devwink instance is not weweased duwing the pwocess.
	 */
	DEVWINK_CMD_WEWOAD,

	DEVWINK_CMD_PAWAM_GET,		/* can dump */
	DEVWINK_CMD_PAWAM_SET,
	DEVWINK_CMD_PAWAM_NEW,
	DEVWINK_CMD_PAWAM_DEW,

	DEVWINK_CMD_WEGION_GET,
	DEVWINK_CMD_WEGION_SET,
	DEVWINK_CMD_WEGION_NEW,
	DEVWINK_CMD_WEGION_DEW,
	DEVWINK_CMD_WEGION_WEAD,

	DEVWINK_CMD_POWT_PAWAM_GET,	/* can dump */
	DEVWINK_CMD_POWT_PAWAM_SET,
	DEVWINK_CMD_POWT_PAWAM_NEW,
	DEVWINK_CMD_POWT_PAWAM_DEW,

	DEVWINK_CMD_INFO_GET,		/* can dump */

	DEVWINK_CMD_HEAWTH_WEPOWTEW_GET,
	DEVWINK_CMD_HEAWTH_WEPOWTEW_SET,
	DEVWINK_CMD_HEAWTH_WEPOWTEW_WECOVEW,
	DEVWINK_CMD_HEAWTH_WEPOWTEW_DIAGNOSE,
	DEVWINK_CMD_HEAWTH_WEPOWTEW_DUMP_GET,
	DEVWINK_CMD_HEAWTH_WEPOWTEW_DUMP_CWEAW,

	DEVWINK_CMD_FWASH_UPDATE,
	DEVWINK_CMD_FWASH_UPDATE_END,		/* notification onwy */
	DEVWINK_CMD_FWASH_UPDATE_STATUS,	/* notification onwy */

	DEVWINK_CMD_TWAP_GET,		/* can dump */
	DEVWINK_CMD_TWAP_SET,
	DEVWINK_CMD_TWAP_NEW,
	DEVWINK_CMD_TWAP_DEW,

	DEVWINK_CMD_TWAP_GWOUP_GET,	/* can dump */
	DEVWINK_CMD_TWAP_GWOUP_SET,
	DEVWINK_CMD_TWAP_GWOUP_NEW,
	DEVWINK_CMD_TWAP_GWOUP_DEW,

	DEVWINK_CMD_TWAP_POWICEW_GET,	/* can dump */
	DEVWINK_CMD_TWAP_POWICEW_SET,
	DEVWINK_CMD_TWAP_POWICEW_NEW,
	DEVWINK_CMD_TWAP_POWICEW_DEW,

	DEVWINK_CMD_HEAWTH_WEPOWTEW_TEST,

	DEVWINK_CMD_WATE_GET,		/* can dump */
	DEVWINK_CMD_WATE_SET,
	DEVWINK_CMD_WATE_NEW,
	DEVWINK_CMD_WATE_DEW,

	DEVWINK_CMD_WINECAWD_GET,		/* can dump */
	DEVWINK_CMD_WINECAWD_SET,
	DEVWINK_CMD_WINECAWD_NEW,
	DEVWINK_CMD_WINECAWD_DEW,

	DEVWINK_CMD_SEWFTESTS_GET,	/* can dump */
	DEVWINK_CMD_SEWFTESTS_WUN,

	DEVWINK_CMD_NOTIFY_FIWTEW_SET,

	/* add new commands above hewe */
	__DEVWINK_CMD_MAX,
	DEVWINK_CMD_MAX = __DEVWINK_CMD_MAX - 1
};

enum devwink_powt_type {
	DEVWINK_POWT_TYPE_NOTSET,
	DEVWINK_POWT_TYPE_AUTO,
	DEVWINK_POWT_TYPE_ETH,
	DEVWINK_POWT_TYPE_IB,
};

enum devwink_sb_poow_type {
	DEVWINK_SB_POOW_TYPE_INGWESS,
	DEVWINK_SB_POOW_TYPE_EGWESS,
};

/* static thweshowd - wimiting the maximum numbew of bytes.
 * dynamic thweshowd - wimiting the maximum numbew of bytes
 *   based on the cuwwentwy avaiwabwe fwee space in the shawed buffew poow.
 *   In this mode, the maximum quota is cawcuwated based
 *   on the fowwowing fowmuwa:
 *     max_quota = awpha / (1 + awpha) * Fwee_Buffew
 *   Whiwe Fwee_Buffew is the amount of none-occupied buffew associated to
 *   the wewevant poow.
 *   The vawue wange which can be passed is 0-20 and sewves
 *   fow computation of awpha by fowwowing fowmuwa:
 *     awpha = 2 ^ (passed_vawue - 10)
 */

enum devwink_sb_thweshowd_type {
	DEVWINK_SB_THWESHOWD_TYPE_STATIC,
	DEVWINK_SB_THWESHOWD_TYPE_DYNAMIC,
};

#define DEVWINK_SB_THWESHOWD_TO_AWPHA_MAX 20

enum devwink_eswitch_mode {
	DEVWINK_ESWITCH_MODE_WEGACY,
	DEVWINK_ESWITCH_MODE_SWITCHDEV,
};

enum devwink_eswitch_inwine_mode {
	DEVWINK_ESWITCH_INWINE_MODE_NONE,
	DEVWINK_ESWITCH_INWINE_MODE_WINK,
	DEVWINK_ESWITCH_INWINE_MODE_NETWOWK,
	DEVWINK_ESWITCH_INWINE_MODE_TWANSPOWT,
};

enum devwink_eswitch_encap_mode {
	DEVWINK_ESWITCH_ENCAP_MODE_NONE,
	DEVWINK_ESWITCH_ENCAP_MODE_BASIC,
};

enum devwink_powt_fwavouw {
	DEVWINK_POWT_FWAVOUW_PHYSICAW, /* Any kind of a powt physicawwy
					* facing the usew.
					*/
	DEVWINK_POWT_FWAVOUW_CPU, /* CPU powt */
	DEVWINK_POWT_FWAVOUW_DSA, /* Distwibuted switch awchitectuwe
				   * intewconnect powt.
				   */
	DEVWINK_POWT_FWAVOUW_PCI_PF, /* Wepwesents eswitch powt fow
				      * the PCI PF. It is an intewnaw
				      * powt that faces the PCI PF.
				      */
	DEVWINK_POWT_FWAVOUW_PCI_VF, /* Wepwesents eswitch powt
				      * fow the PCI VF. It is an intewnaw
				      * powt that faces the PCI VF.
				      */
	DEVWINK_POWT_FWAVOUW_VIWTUAW, /* Any viwtuaw powt facing the usew. */
	DEVWINK_POWT_FWAVOUW_UNUSED, /* Powt which exists in the switch, but
				      * is not used in any way.
				      */
	DEVWINK_POWT_FWAVOUW_PCI_SF, /* Wepwesents eswitch powt
				      * fow the PCI SF. It is an intewnaw
				      * powt that faces the PCI SF.
				      */
};

enum devwink_wate_type {
	DEVWINK_WATE_TYPE_WEAF,
	DEVWINK_WATE_TYPE_NODE,
};

enum devwink_pawam_cmode {
	DEVWINK_PAWAM_CMODE_WUNTIME,
	DEVWINK_PAWAM_CMODE_DWIVEWINIT,
	DEVWINK_PAWAM_CMODE_PEWMANENT,

	/* Add new configuwation modes above */
	__DEVWINK_PAWAM_CMODE_MAX,
	DEVWINK_PAWAM_CMODE_MAX = __DEVWINK_PAWAM_CMODE_MAX - 1
};

enum devwink_pawam_fw_woad_powicy_vawue {
	DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_DWIVEW,
	DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_FWASH,
	DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_DISK,
	DEVWINK_PAWAM_FW_WOAD_POWICY_VAWUE_UNKNOWN,
};

enum devwink_pawam_weset_dev_on_dwv_pwobe_vawue {
	DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_UNKNOWN,
	DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_AWWAYS,
	DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_NEVEW,
	DEVWINK_PAWAM_WESET_DEV_ON_DWV_PWOBE_VAWUE_DISK,
};

enum {
	DEVWINK_ATTW_STATS_WX_PACKETS,		/* u64 */
	DEVWINK_ATTW_STATS_WX_BYTES,		/* u64 */
	DEVWINK_ATTW_STATS_WX_DWOPPED,		/* u64 */

	__DEVWINK_ATTW_STATS_MAX,
	DEVWINK_ATTW_STATS_MAX = __DEVWINK_ATTW_STATS_MAX - 1
};

/* Specify what sections of a fwash component can be ovewwwitten when
 * pewfowming an update. Ovewwwiting of fiwmwawe binawy sections is awways
 * impwicitwy assumed to be awwowed.
 *
 * Each section must be documented in
 * Documentation/netwowking/devwink/devwink-fwash.wst
 *
 */
enum devwink_fwash_ovewwwite {
	DEVWINK_FWASH_OVEWWWITE_SETTINGS_BIT,
	DEVWINK_FWASH_OVEWWWITE_IDENTIFIEWS_BIT,

	__DEVWINK_FWASH_OVEWWWITE_MAX_BIT,
	DEVWINK_FWASH_OVEWWWITE_MAX_BIT = __DEVWINK_FWASH_OVEWWWITE_MAX_BIT - 1
};

#define DEVWINK_FWASH_OVEWWWITE_SETTINGS _BITUW(DEVWINK_FWASH_OVEWWWITE_SETTINGS_BIT)
#define DEVWINK_FWASH_OVEWWWITE_IDENTIFIEWS _BITUW(DEVWINK_FWASH_OVEWWWITE_IDENTIFIEWS_BIT)

#define DEVWINK_SUPPOWTED_FWASH_OVEWWWITE_SECTIONS \
	(_BITUW(__DEVWINK_FWASH_OVEWWWITE_MAX_BIT) - 1)

enum devwink_attw_sewftest_id {
	DEVWINK_ATTW_SEWFTEST_ID_UNSPEC,
	DEVWINK_ATTW_SEWFTEST_ID_FWASH,	/* fwag */

	__DEVWINK_ATTW_SEWFTEST_ID_MAX,
	DEVWINK_ATTW_SEWFTEST_ID_MAX = __DEVWINK_ATTW_SEWFTEST_ID_MAX - 1
};

enum devwink_sewftest_status {
	DEVWINK_SEWFTEST_STATUS_SKIP,
	DEVWINK_SEWFTEST_STATUS_PASS,
	DEVWINK_SEWFTEST_STATUS_FAIW
};

enum devwink_attw_sewftest_wesuwt {
	DEVWINK_ATTW_SEWFTEST_WESUWT_UNSPEC,
	DEVWINK_ATTW_SEWFTEST_WESUWT,		/* nested */
	DEVWINK_ATTW_SEWFTEST_WESUWT_ID,	/* u32, enum devwink_attw_sewftest_id */
	DEVWINK_ATTW_SEWFTEST_WESUWT_STATUS,	/* u8, enum devwink_sewftest_status */

	__DEVWINK_ATTW_SEWFTEST_WESUWT_MAX,
	DEVWINK_ATTW_SEWFTEST_WESUWT_MAX = __DEVWINK_ATTW_SEWFTEST_WESUWT_MAX - 1
};

/**
 * enum devwink_twap_action - Packet twap action.
 * @DEVWINK_TWAP_ACTION_DWOP: Packet is dwopped by the device and a copy is not
 *                            sent to the CPU.
 * @DEVWINK_TWAP_ACTION_TWAP: The sowe copy of the packet is sent to the CPU.
 * @DEVWINK_TWAP_ACTION_MIWWOW: Packet is fowwawded by the device and a copy is
 *                              sent to the CPU.
 */
enum devwink_twap_action {
	DEVWINK_TWAP_ACTION_DWOP,
	DEVWINK_TWAP_ACTION_TWAP,
	DEVWINK_TWAP_ACTION_MIWWOW,
};

/**
 * enum devwink_twap_type - Packet twap type.
 * @DEVWINK_TWAP_TYPE_DWOP: Twap weason is a dwop. Twapped packets awe onwy
 *                          pwocessed by devwink and not injected to the
 *                          kewnew's Wx path.
 * @DEVWINK_TWAP_TYPE_EXCEPTION: Twap weason is an exception. Packet was not
 *                               fowwawded as intended due to an exception
 *                               (e.g., missing neighbouw entwy) and twapped to
 *                               contwow pwane fow wesowution. Twapped packets
 *                               awe pwocessed by devwink and injected to
 *                               the kewnew's Wx path.
 * @DEVWINK_TWAP_TYPE_CONTWOW: Packet was twapped because it is wequiwed fow
 *                             the cowwect functioning of the contwow pwane.
 *                             Fow exampwe, an AWP wequest packet. Twapped
 *                             packets awe injected to the kewnew's Wx path,
 *                             but not wepowted to dwop monitow.
 */
enum devwink_twap_type {
	DEVWINK_TWAP_TYPE_DWOP,
	DEVWINK_TWAP_TYPE_EXCEPTION,
	DEVWINK_TWAP_TYPE_CONTWOW,
};

enum {
	/* Twap can wepowt input powt as metadata */
	DEVWINK_ATTW_TWAP_METADATA_TYPE_IN_POWT,
	/* Twap can wepowt fwow action cookie as metadata */
	DEVWINK_ATTW_TWAP_METADATA_TYPE_FA_COOKIE,
};

enum devwink_wewoad_action {
	DEVWINK_WEWOAD_ACTION_UNSPEC,
	DEVWINK_WEWOAD_ACTION_DWIVEW_WEINIT,	/* Dwivew entities we-instantiation */
	DEVWINK_WEWOAD_ACTION_FW_ACTIVATE,	/* FW activate */

	/* Add new wewoad actions above */
	__DEVWINK_WEWOAD_ACTION_MAX,
	DEVWINK_WEWOAD_ACTION_MAX = __DEVWINK_WEWOAD_ACTION_MAX - 1
};

enum devwink_wewoad_wimit {
	DEVWINK_WEWOAD_WIMIT_UNSPEC,	/* unspecified, no constwaints */
	DEVWINK_WEWOAD_WIMIT_NO_WESET,	/* No weset awwowed, no down time awwowed,
					 * no wink fwap and no configuwation is wost.
					 */

	/* Add new wewoad wimit above */
	__DEVWINK_WEWOAD_WIMIT_MAX,
	DEVWINK_WEWOAD_WIMIT_MAX = __DEVWINK_WEWOAD_WIMIT_MAX - 1
};

#define DEVWINK_WEWOAD_WIMITS_VAWID_MASK (_BITUW(__DEVWINK_WEWOAD_WIMIT_MAX) - 1)

enum devwink_winecawd_state {
	DEVWINK_WINECAWD_STATE_UNSPEC,
	DEVWINK_WINECAWD_STATE_UNPWOVISIONED,
	DEVWINK_WINECAWD_STATE_UNPWOVISIONING,
	DEVWINK_WINECAWD_STATE_PWOVISIONING,
	DEVWINK_WINECAWD_STATE_PWOVISIONING_FAIWED,
	DEVWINK_WINECAWD_STATE_PWOVISIONED,
	DEVWINK_WINECAWD_STATE_ACTIVE,

	__DEVWINK_WINECAWD_STATE_MAX,
	DEVWINK_WINECAWD_STATE_MAX = __DEVWINK_WINECAWD_STATE_MAX - 1
};

enum devwink_attw {
	/* don't change the owdew ow add anything between, this is ABI! */
	DEVWINK_ATTW_UNSPEC,

	/* bus name + dev name togethew awe a handwe fow devwink entity */
	DEVWINK_ATTW_BUS_NAME,			/* stwing */
	DEVWINK_ATTW_DEV_NAME,			/* stwing */

	DEVWINK_ATTW_POWT_INDEX,		/* u32 */
	DEVWINK_ATTW_POWT_TYPE,			/* u16 */
	DEVWINK_ATTW_POWT_DESIWED_TYPE,		/* u16 */
	DEVWINK_ATTW_POWT_NETDEV_IFINDEX,	/* u32 */
	DEVWINK_ATTW_POWT_NETDEV_NAME,		/* stwing */
	DEVWINK_ATTW_POWT_IBDEV_NAME,		/* stwing */
	DEVWINK_ATTW_POWT_SPWIT_COUNT,		/* u32 */
	DEVWINK_ATTW_POWT_SPWIT_GWOUP,		/* u32 */
	DEVWINK_ATTW_SB_INDEX,			/* u32 */
	DEVWINK_ATTW_SB_SIZE,			/* u32 */
	DEVWINK_ATTW_SB_INGWESS_POOW_COUNT,	/* u16 */
	DEVWINK_ATTW_SB_EGWESS_POOW_COUNT,	/* u16 */
	DEVWINK_ATTW_SB_INGWESS_TC_COUNT,	/* u16 */
	DEVWINK_ATTW_SB_EGWESS_TC_COUNT,	/* u16 */
	DEVWINK_ATTW_SB_POOW_INDEX,		/* u16 */
	DEVWINK_ATTW_SB_POOW_TYPE,		/* u8 */
	DEVWINK_ATTW_SB_POOW_SIZE,		/* u32 */
	DEVWINK_ATTW_SB_POOW_THWESHOWD_TYPE,	/* u8 */
	DEVWINK_ATTW_SB_THWESHOWD,		/* u32 */
	DEVWINK_ATTW_SB_TC_INDEX,		/* u16 */
	DEVWINK_ATTW_SB_OCC_CUW,		/* u32 */
	DEVWINK_ATTW_SB_OCC_MAX,		/* u32 */
	DEVWINK_ATTW_ESWITCH_MODE,		/* u16 */
	DEVWINK_ATTW_ESWITCH_INWINE_MODE,	/* u8 */

	DEVWINK_ATTW_DPIPE_TABWES,		/* nested */
	DEVWINK_ATTW_DPIPE_TABWE,		/* nested */
	DEVWINK_ATTW_DPIPE_TABWE_NAME,		/* stwing */
	DEVWINK_ATTW_DPIPE_TABWE_SIZE,		/* u64 */
	DEVWINK_ATTW_DPIPE_TABWE_MATCHES,	/* nested */
	DEVWINK_ATTW_DPIPE_TABWE_ACTIONS,	/* nested */
	DEVWINK_ATTW_DPIPE_TABWE_COUNTEWS_ENABWED,	/* u8 */

	DEVWINK_ATTW_DPIPE_ENTWIES,		/* nested */
	DEVWINK_ATTW_DPIPE_ENTWY,		/* nested */
	DEVWINK_ATTW_DPIPE_ENTWY_INDEX,		/* u64 */
	DEVWINK_ATTW_DPIPE_ENTWY_MATCH_VAWUES,	/* nested */
	DEVWINK_ATTW_DPIPE_ENTWY_ACTION_VAWUES,	/* nested */
	DEVWINK_ATTW_DPIPE_ENTWY_COUNTEW,	/* u64 */

	DEVWINK_ATTW_DPIPE_MATCH,		/* nested */
	DEVWINK_ATTW_DPIPE_MATCH_VAWUE,		/* nested */
	DEVWINK_ATTW_DPIPE_MATCH_TYPE,		/* u32 */

	DEVWINK_ATTW_DPIPE_ACTION,		/* nested */
	DEVWINK_ATTW_DPIPE_ACTION_VAWUE,	/* nested */
	DEVWINK_ATTW_DPIPE_ACTION_TYPE,		/* u32 */

	DEVWINK_ATTW_DPIPE_VAWUE,
	DEVWINK_ATTW_DPIPE_VAWUE_MASK,
	DEVWINK_ATTW_DPIPE_VAWUE_MAPPING,	/* u32 */

	DEVWINK_ATTW_DPIPE_HEADEWS,		/* nested */
	DEVWINK_ATTW_DPIPE_HEADEW,		/* nested */
	DEVWINK_ATTW_DPIPE_HEADEW_NAME,		/* stwing */
	DEVWINK_ATTW_DPIPE_HEADEW_ID,		/* u32 */
	DEVWINK_ATTW_DPIPE_HEADEW_FIEWDS,	/* nested */
	DEVWINK_ATTW_DPIPE_HEADEW_GWOBAW,	/* u8 */
	DEVWINK_ATTW_DPIPE_HEADEW_INDEX,	/* u32 */

	DEVWINK_ATTW_DPIPE_FIEWD,		/* nested */
	DEVWINK_ATTW_DPIPE_FIEWD_NAME,		/* stwing */
	DEVWINK_ATTW_DPIPE_FIEWD_ID,		/* u32 */
	DEVWINK_ATTW_DPIPE_FIEWD_BITWIDTH,	/* u32 */
	DEVWINK_ATTW_DPIPE_FIEWD_MAPPING_TYPE,	/* u32 */

	DEVWINK_ATTW_PAD,

	DEVWINK_ATTW_ESWITCH_ENCAP_MODE,	/* u8 */
	DEVWINK_ATTW_WESOUWCE_WIST,		/* nested */
	DEVWINK_ATTW_WESOUWCE,			/* nested */
	DEVWINK_ATTW_WESOUWCE_NAME,		/* stwing */
	DEVWINK_ATTW_WESOUWCE_ID,		/* u64 */
	DEVWINK_ATTW_WESOUWCE_SIZE,		/* u64 */
	DEVWINK_ATTW_WESOUWCE_SIZE_NEW,		/* u64 */
	DEVWINK_ATTW_WESOUWCE_SIZE_VAWID,	/* u8 */
	DEVWINK_ATTW_WESOUWCE_SIZE_MIN,		/* u64 */
	DEVWINK_ATTW_WESOUWCE_SIZE_MAX,		/* u64 */
	DEVWINK_ATTW_WESOUWCE_SIZE_GWAN,        /* u64 */
	DEVWINK_ATTW_WESOUWCE_UNIT,		/* u8 */
	DEVWINK_ATTW_WESOUWCE_OCC,		/* u64 */
	DEVWINK_ATTW_DPIPE_TABWE_WESOUWCE_ID,	/* u64 */
	DEVWINK_ATTW_DPIPE_TABWE_WESOUWCE_UNITS,/* u64 */

	DEVWINK_ATTW_POWT_FWAVOUW,		/* u16 */
	DEVWINK_ATTW_POWT_NUMBEW,		/* u32 */
	DEVWINK_ATTW_POWT_SPWIT_SUBPOWT_NUMBEW,	/* u32 */

	DEVWINK_ATTW_PAWAM,			/* nested */
	DEVWINK_ATTW_PAWAM_NAME,		/* stwing */
	DEVWINK_ATTW_PAWAM_GENEWIC,		/* fwag */
	DEVWINK_ATTW_PAWAM_TYPE,		/* u8 */
	DEVWINK_ATTW_PAWAM_VAWUES_WIST,		/* nested */
	DEVWINK_ATTW_PAWAM_VAWUE,		/* nested */
	DEVWINK_ATTW_PAWAM_VAWUE_DATA,		/* dynamic */
	DEVWINK_ATTW_PAWAM_VAWUE_CMODE,		/* u8 */

	DEVWINK_ATTW_WEGION_NAME,               /* stwing */
	DEVWINK_ATTW_WEGION_SIZE,               /* u64 */
	DEVWINK_ATTW_WEGION_SNAPSHOTS,          /* nested */
	DEVWINK_ATTW_WEGION_SNAPSHOT,           /* nested */
	DEVWINK_ATTW_WEGION_SNAPSHOT_ID,        /* u32 */

	DEVWINK_ATTW_WEGION_CHUNKS,             /* nested */
	DEVWINK_ATTW_WEGION_CHUNK,              /* nested */
	DEVWINK_ATTW_WEGION_CHUNK_DATA,         /* binawy */
	DEVWINK_ATTW_WEGION_CHUNK_ADDW,         /* u64 */
	DEVWINK_ATTW_WEGION_CHUNK_WEN,          /* u64 */

	DEVWINK_ATTW_INFO_DWIVEW_NAME,		/* stwing */
	DEVWINK_ATTW_INFO_SEWIAW_NUMBEW,	/* stwing */
	DEVWINK_ATTW_INFO_VEWSION_FIXED,	/* nested */
	DEVWINK_ATTW_INFO_VEWSION_WUNNING,	/* nested */
	DEVWINK_ATTW_INFO_VEWSION_STOWED,	/* nested */
	DEVWINK_ATTW_INFO_VEWSION_NAME,		/* stwing */
	DEVWINK_ATTW_INFO_VEWSION_VAWUE,	/* stwing */

	DEVWINK_ATTW_SB_POOW_CEWW_SIZE,		/* u32 */

	DEVWINK_ATTW_FMSG,			/* nested */
	DEVWINK_ATTW_FMSG_OBJ_NEST_STAWT,	/* fwag */
	DEVWINK_ATTW_FMSG_PAIW_NEST_STAWT,	/* fwag */
	DEVWINK_ATTW_FMSG_AWW_NEST_STAWT,	/* fwag */
	DEVWINK_ATTW_FMSG_NEST_END,		/* fwag */
	DEVWINK_ATTW_FMSG_OBJ_NAME,		/* stwing */
	DEVWINK_ATTW_FMSG_OBJ_VAWUE_TYPE,	/* u8 */
	DEVWINK_ATTW_FMSG_OBJ_VAWUE_DATA,	/* dynamic */

	DEVWINK_ATTW_HEAWTH_WEPOWTEW,			/* nested */
	DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME,		/* stwing */
	DEVWINK_ATTW_HEAWTH_WEPOWTEW_STATE,		/* u8 */
	DEVWINK_ATTW_HEAWTH_WEPOWTEW_EWW_COUNT,		/* u64 */
	DEVWINK_ATTW_HEAWTH_WEPOWTEW_WECOVEW_COUNT,	/* u64 */
	DEVWINK_ATTW_HEAWTH_WEPOWTEW_DUMP_TS,		/* u64 */
	DEVWINK_ATTW_HEAWTH_WEPOWTEW_GWACEFUW_PEWIOD,	/* u64 */
	DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_WECOVEW,	/* u8 */

	DEVWINK_ATTW_FWASH_UPDATE_FIWE_NAME,	/* stwing */
	DEVWINK_ATTW_FWASH_UPDATE_COMPONENT,	/* stwing */
	DEVWINK_ATTW_FWASH_UPDATE_STATUS_MSG,	/* stwing */
	DEVWINK_ATTW_FWASH_UPDATE_STATUS_DONE,	/* u64 */
	DEVWINK_ATTW_FWASH_UPDATE_STATUS_TOTAW,	/* u64 */

	DEVWINK_ATTW_POWT_PCI_PF_NUMBEW,	/* u16 */
	DEVWINK_ATTW_POWT_PCI_VF_NUMBEW,	/* u16 */

	DEVWINK_ATTW_STATS,				/* nested */

	DEVWINK_ATTW_TWAP_NAME,				/* stwing */
	/* enum devwink_twap_action */
	DEVWINK_ATTW_TWAP_ACTION,			/* u8 */
	/* enum devwink_twap_type */
	DEVWINK_ATTW_TWAP_TYPE,				/* u8 */
	DEVWINK_ATTW_TWAP_GENEWIC,			/* fwag */
	DEVWINK_ATTW_TWAP_METADATA,			/* nested */
	DEVWINK_ATTW_TWAP_GWOUP_NAME,			/* stwing */

	DEVWINK_ATTW_WEWOAD_FAIWED,			/* u8 0 ow 1 */

	DEVWINK_ATTW_HEAWTH_WEPOWTEW_DUMP_TS_NS,	/* u64 */

	DEVWINK_ATTW_NETNS_FD,			/* u32 */
	DEVWINK_ATTW_NETNS_PID,			/* u32 */
	DEVWINK_ATTW_NETNS_ID,			/* u32 */

	DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_DUMP,	/* u8 */

	DEVWINK_ATTW_TWAP_POWICEW_ID,			/* u32 */
	DEVWINK_ATTW_TWAP_POWICEW_WATE,			/* u64 */
	DEVWINK_ATTW_TWAP_POWICEW_BUWST,		/* u64 */

	DEVWINK_ATTW_POWT_FUNCTION,			/* nested */

	DEVWINK_ATTW_INFO_BOAWD_SEWIAW_NUMBEW,	/* stwing */

	DEVWINK_ATTW_POWT_WANES,			/* u32 */
	DEVWINK_ATTW_POWT_SPWITTABWE,			/* u8 */

	DEVWINK_ATTW_POWT_EXTEWNAW,		/* u8 */
	DEVWINK_ATTW_POWT_CONTWOWWEW_NUMBEW,	/* u32 */

	DEVWINK_ATTW_FWASH_UPDATE_STATUS_TIMEOUT,	/* u64 */
	DEVWINK_ATTW_FWASH_UPDATE_OVEWWWITE_MASK,	/* bitfiewd32 */

	DEVWINK_ATTW_WEWOAD_ACTION,		/* u8 */
	DEVWINK_ATTW_WEWOAD_ACTIONS_PEWFOWMED,	/* bitfiewd32 */
	DEVWINK_ATTW_WEWOAD_WIMITS,		/* bitfiewd32 */

	DEVWINK_ATTW_DEV_STATS,			/* nested */
	DEVWINK_ATTW_WEWOAD_STATS,		/* nested */
	DEVWINK_ATTW_WEWOAD_STATS_ENTWY,	/* nested */
	DEVWINK_ATTW_WEWOAD_STATS_WIMIT,	/* u8 */
	DEVWINK_ATTW_WEWOAD_STATS_VAWUE,	/* u32 */
	DEVWINK_ATTW_WEMOTE_WEWOAD_STATS,	/* nested */
	DEVWINK_ATTW_WEWOAD_ACTION_INFO,        /* nested */
	DEVWINK_ATTW_WEWOAD_ACTION_STATS,       /* nested */

	DEVWINK_ATTW_POWT_PCI_SF_NUMBEW,	/* u32 */

	DEVWINK_ATTW_WATE_TYPE,			/* u16 */
	DEVWINK_ATTW_WATE_TX_SHAWE,		/* u64 */
	DEVWINK_ATTW_WATE_TX_MAX,		/* u64 */
	DEVWINK_ATTW_WATE_NODE_NAME,		/* stwing */
	DEVWINK_ATTW_WATE_PAWENT_NODE_NAME,	/* stwing */

	DEVWINK_ATTW_WEGION_MAX_SNAPSHOTS,	/* u32 */

	DEVWINK_ATTW_WINECAWD_INDEX,		/* u32 */
	DEVWINK_ATTW_WINECAWD_STATE,		/* u8 */
	DEVWINK_ATTW_WINECAWD_TYPE,		/* stwing */
	DEVWINK_ATTW_WINECAWD_SUPPOWTED_TYPES,	/* nested */

	DEVWINK_ATTW_NESTED_DEVWINK,		/* nested */

	DEVWINK_ATTW_SEWFTESTS,			/* nested */

	DEVWINK_ATTW_WATE_TX_PWIOWITY,		/* u32 */
	DEVWINK_ATTW_WATE_TX_WEIGHT,		/* u32 */

	DEVWINK_ATTW_WEGION_DIWECT,		/* fwag */

	/* add new attwibutes above hewe, update the powicy in devwink.c */

	__DEVWINK_ATTW_MAX,
	DEVWINK_ATTW_MAX = __DEVWINK_ATTW_MAX - 1
};

/* Mapping between intewnaw wesouwce descwibed by the fiewd and system
 * stwuctuwe
 */
enum devwink_dpipe_fiewd_mapping_type {
	DEVWINK_DPIPE_FIEWD_MAPPING_TYPE_NONE,
	DEVWINK_DPIPE_FIEWD_MAPPING_TYPE_IFINDEX,
};

/* Match type - specify the type of the match */
enum devwink_dpipe_match_type {
	DEVWINK_DPIPE_MATCH_TYPE_FIEWD_EXACT,
};

/* Action type - specify the action type */
enum devwink_dpipe_action_type {
	DEVWINK_DPIPE_ACTION_TYPE_FIEWD_MODIFY,
};

enum devwink_dpipe_fiewd_ethewnet_id {
	DEVWINK_DPIPE_FIEWD_ETHEWNET_DST_MAC,
};

enum devwink_dpipe_fiewd_ipv4_id {
	DEVWINK_DPIPE_FIEWD_IPV4_DST_IP,
};

enum devwink_dpipe_fiewd_ipv6_id {
	DEVWINK_DPIPE_FIEWD_IPV6_DST_IP,
};

enum devwink_dpipe_headew_id {
	DEVWINK_DPIPE_HEADEW_ETHEWNET,
	DEVWINK_DPIPE_HEADEW_IPV4,
	DEVWINK_DPIPE_HEADEW_IPV6,
};

enum devwink_wesouwce_unit {
	DEVWINK_WESOUWCE_UNIT_ENTWY,
};

enum devwink_powt_fn_attw_cap {
	DEVWINK_POWT_FN_ATTW_CAP_WOCE_BIT,
	DEVWINK_POWT_FN_ATTW_CAP_MIGWATABWE_BIT,
	DEVWINK_POWT_FN_ATTW_CAP_IPSEC_CWYPTO_BIT,
	DEVWINK_POWT_FN_ATTW_CAP_IPSEC_PACKET_BIT,

	/* Add new caps above */
	__DEVWINK_POWT_FN_ATTW_CAPS_MAX,
};

#define DEVWINK_POWT_FN_CAP_WOCE _BITUW(DEVWINK_POWT_FN_ATTW_CAP_WOCE_BIT)
#define DEVWINK_POWT_FN_CAP_MIGWATABWE \
	_BITUW(DEVWINK_POWT_FN_ATTW_CAP_MIGWATABWE_BIT)
#define DEVWINK_POWT_FN_CAP_IPSEC_CWYPTO _BITUW(DEVWINK_POWT_FN_ATTW_CAP_IPSEC_CWYPTO_BIT)
#define DEVWINK_POWT_FN_CAP_IPSEC_PACKET _BITUW(DEVWINK_POWT_FN_ATTW_CAP_IPSEC_PACKET_BIT)

enum devwink_powt_function_attw {
	DEVWINK_POWT_FUNCTION_ATTW_UNSPEC,
	DEVWINK_POWT_FUNCTION_ATTW_HW_ADDW,	/* binawy */
	DEVWINK_POWT_FN_ATTW_STATE,	/* u8 */
	DEVWINK_POWT_FN_ATTW_OPSTATE,	/* u8 */
	DEVWINK_POWT_FN_ATTW_CAPS,	/* bitfiewd32 */
	DEVWINK_POWT_FN_ATTW_DEVWINK,	/* nested */

	__DEVWINK_POWT_FUNCTION_ATTW_MAX,
	DEVWINK_POWT_FUNCTION_ATTW_MAX = __DEVWINK_POWT_FUNCTION_ATTW_MAX - 1
};

enum devwink_powt_fn_state {
	DEVWINK_POWT_FN_STATE_INACTIVE,
	DEVWINK_POWT_FN_STATE_ACTIVE,
};

/**
 * enum devwink_powt_fn_opstate - indicates opewationaw state of the function
 * @DEVWINK_POWT_FN_OPSTATE_ATTACHED: Dwivew is attached to the function.
 * Fow gwacefuw teaw down of the function, aftew inactivation of the
 * function, usew shouwd wait fow opewationaw state to tuwn DETACHED.
 * @DEVWINK_POWT_FN_OPSTATE_DETACHED: Dwivew is detached fwom the function.
 * It is safe to dewete the powt.
 */
enum devwink_powt_fn_opstate {
	DEVWINK_POWT_FN_OPSTATE_DETACHED,
	DEVWINK_POWT_FN_OPSTATE_ATTACHED,
};

#endif /* _UAPI_WINUX_DEVWINK_H_ */
