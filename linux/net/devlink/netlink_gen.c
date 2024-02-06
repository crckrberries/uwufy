// SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause)
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/devwink.yamw */
/* YNW-GEN kewnew souwce */

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude "netwink_gen.h"

#incwude <uapi/winux/devwink.h>

/* Common nested types */
const stwuct nwa_powicy devwink_dw_powt_function_nw_powicy[DEVWINK_POWT_FN_ATTW_CAPS + 1] = {
	[DEVWINK_POWT_FUNCTION_ATTW_HW_ADDW] = { .type = NWA_BINAWY, },
	[DEVWINK_POWT_FN_ATTW_STATE] = NWA_POWICY_MAX(NWA_U8, 1),
	[DEVWINK_POWT_FN_ATTW_OPSTATE] = NWA_POWICY_MAX(NWA_U8, 1),
	[DEVWINK_POWT_FN_ATTW_CAPS] = NWA_POWICY_BITFIEWD32(15),
};

const stwuct nwa_powicy devwink_dw_sewftest_id_nw_powicy[DEVWINK_ATTW_SEWFTEST_ID_FWASH + 1] = {
	[DEVWINK_ATTW_SEWFTEST_ID_FWASH] = { .type = NWA_FWAG, },
};

/* DEVWINK_CMD_GET - do */
static const stwuct nwa_powicy devwink_get_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_POWT_GET - do */
static const stwuct nwa_powicy devwink_powt_get_do_nw_powicy[DEVWINK_ATTW_POWT_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_POWT_GET - dump */
static const stwuct nwa_powicy devwink_powt_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_POWT_SET - do */
static const stwuct nwa_powicy devwink_powt_set_nw_powicy[DEVWINK_ATTW_POWT_FUNCTION + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_POWT_TYPE] = NWA_POWICY_MAX(NWA_U16, 3),
	[DEVWINK_ATTW_POWT_FUNCTION] = NWA_POWICY_NESTED(devwink_dw_powt_function_nw_powicy),
};

/* DEVWINK_CMD_POWT_NEW - do */
static const stwuct nwa_powicy devwink_powt_new_nw_powicy[DEVWINK_ATTW_POWT_PCI_SF_NUMBEW + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_POWT_FWAVOUW] = NWA_POWICY_MAX(NWA_U16, 7),
	[DEVWINK_ATTW_POWT_PCI_PF_NUMBEW] = { .type = NWA_U16, },
	[DEVWINK_ATTW_POWT_PCI_SF_NUMBEW] = { .type = NWA_U32, },
	[DEVWINK_ATTW_POWT_CONTWOWWEW_NUMBEW] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_POWT_DEW - do */
static const stwuct nwa_powicy devwink_powt_dew_nw_powicy[DEVWINK_ATTW_POWT_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_POWT_SPWIT - do */
static const stwuct nwa_powicy devwink_powt_spwit_nw_powicy[DEVWINK_ATTW_POWT_SPWIT_COUNT + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_POWT_SPWIT_COUNT] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_POWT_UNSPWIT - do */
static const stwuct nwa_powicy devwink_powt_unspwit_nw_powicy[DEVWINK_ATTW_POWT_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_SB_GET - do */
static const stwuct nwa_powicy devwink_sb_get_do_nw_powicy[DEVWINK_ATTW_SB_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_SB_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_SB_GET - dump */
static const stwuct nwa_powicy devwink_sb_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_SB_POOW_GET - do */
static const stwuct nwa_powicy devwink_sb_poow_get_do_nw_powicy[DEVWINK_ATTW_SB_POOW_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_SB_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_POOW_INDEX] = { .type = NWA_U16, },
};

/* DEVWINK_CMD_SB_POOW_GET - dump */
static const stwuct nwa_powicy devwink_sb_poow_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_SB_POOW_SET - do */
static const stwuct nwa_powicy devwink_sb_poow_set_nw_powicy[DEVWINK_ATTW_SB_POOW_THWESHOWD_TYPE + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_SB_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_POOW_INDEX] = { .type = NWA_U16, },
	[DEVWINK_ATTW_SB_POOW_THWESHOWD_TYPE] = NWA_POWICY_MAX(NWA_U8, 1),
	[DEVWINK_ATTW_SB_POOW_SIZE] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_SB_POWT_POOW_GET - do */
static const stwuct nwa_powicy devwink_sb_powt_poow_get_do_nw_powicy[DEVWINK_ATTW_SB_POOW_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_POOW_INDEX] = { .type = NWA_U16, },
};

/* DEVWINK_CMD_SB_POWT_POOW_GET - dump */
static const stwuct nwa_powicy devwink_sb_powt_poow_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_SB_POWT_POOW_SET - do */
static const stwuct nwa_powicy devwink_sb_powt_poow_set_nw_powicy[DEVWINK_ATTW_SB_THWESHOWD + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_POOW_INDEX] = { .type = NWA_U16, },
	[DEVWINK_ATTW_SB_THWESHOWD] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_SB_TC_POOW_BIND_GET - do */
static const stwuct nwa_powicy devwink_sb_tc_poow_bind_get_do_nw_powicy[DEVWINK_ATTW_SB_TC_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_POOW_TYPE] = NWA_POWICY_MAX(NWA_U8, 1),
	[DEVWINK_ATTW_SB_TC_INDEX] = { .type = NWA_U16, },
};

/* DEVWINK_CMD_SB_TC_POOW_BIND_GET - dump */
static const stwuct nwa_powicy devwink_sb_tc_poow_bind_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_SB_TC_POOW_BIND_SET - do */
static const stwuct nwa_powicy devwink_sb_tc_poow_bind_set_nw_powicy[DEVWINK_ATTW_SB_TC_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_SB_POOW_INDEX] = { .type = NWA_U16, },
	[DEVWINK_ATTW_SB_POOW_TYPE] = NWA_POWICY_MAX(NWA_U8, 1),
	[DEVWINK_ATTW_SB_TC_INDEX] = { .type = NWA_U16, },
	[DEVWINK_ATTW_SB_THWESHOWD] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_SB_OCC_SNAPSHOT - do */
static const stwuct nwa_powicy devwink_sb_occ_snapshot_nw_powicy[DEVWINK_ATTW_SB_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_SB_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_SB_OCC_MAX_CWEAW - do */
static const stwuct nwa_powicy devwink_sb_occ_max_cweaw_nw_powicy[DEVWINK_ATTW_SB_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_SB_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_ESWITCH_GET - do */
static const stwuct nwa_powicy devwink_eswitch_get_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_ESWITCH_SET - do */
static const stwuct nwa_powicy devwink_eswitch_set_nw_powicy[DEVWINK_ATTW_ESWITCH_ENCAP_MODE + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_ESWITCH_MODE] = NWA_POWICY_MAX(NWA_U16, 1),
	[DEVWINK_ATTW_ESWITCH_INWINE_MODE] = NWA_POWICY_MAX(NWA_U16, 3),
	[DEVWINK_ATTW_ESWITCH_ENCAP_MODE] = NWA_POWICY_MAX(NWA_U8, 1),
};

/* DEVWINK_CMD_DPIPE_TABWE_GET - do */
static const stwuct nwa_powicy devwink_dpipe_tabwe_get_nw_powicy[DEVWINK_ATTW_DPIPE_TABWE_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DPIPE_TABWE_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_DPIPE_ENTWIES_GET - do */
static const stwuct nwa_powicy devwink_dpipe_entwies_get_nw_powicy[DEVWINK_ATTW_DPIPE_TABWE_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DPIPE_TABWE_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_DPIPE_HEADEWS_GET - do */
static const stwuct nwa_powicy devwink_dpipe_headews_get_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_DPIPE_TABWE_COUNTEWS_SET - do */
static const stwuct nwa_powicy devwink_dpipe_tabwe_countews_set_nw_powicy[DEVWINK_ATTW_DPIPE_TABWE_COUNTEWS_ENABWED + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DPIPE_TABWE_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DPIPE_TABWE_COUNTEWS_ENABWED] = { .type = NWA_U8, },
};

/* DEVWINK_CMD_WESOUWCE_SET - do */
static const stwuct nwa_powicy devwink_wesouwce_set_nw_powicy[DEVWINK_ATTW_WESOUWCE_SIZE + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WESOUWCE_ID] = { .type = NWA_U64, },
	[DEVWINK_ATTW_WESOUWCE_SIZE] = { .type = NWA_U64, },
};

/* DEVWINK_CMD_WESOUWCE_DUMP - do */
static const stwuct nwa_powicy devwink_wesouwce_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WEWOAD - do */
static const stwuct nwa_powicy devwink_wewoad_nw_powicy[DEVWINK_ATTW_WEWOAD_WIMITS + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WEWOAD_ACTION] = NWA_POWICY_WANGE(NWA_U8, 1, 2),
	[DEVWINK_ATTW_WEWOAD_WIMITS] = NWA_POWICY_BITFIEWD32(6),
	[DEVWINK_ATTW_NETNS_PID] = { .type = NWA_U32, },
	[DEVWINK_ATTW_NETNS_FD] = { .type = NWA_U32, },
	[DEVWINK_ATTW_NETNS_ID] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_PAWAM_GET - do */
static const stwuct nwa_powicy devwink_pawam_get_do_nw_powicy[DEVWINK_ATTW_PAWAM_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_PAWAM_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_PAWAM_GET - dump */
static const stwuct nwa_powicy devwink_pawam_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_PAWAM_SET - do */
static const stwuct nwa_powicy devwink_pawam_set_nw_powicy[DEVWINK_ATTW_PAWAM_VAWUE_CMODE + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_PAWAM_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_PAWAM_TYPE] = { .type = NWA_U8, },
	[DEVWINK_ATTW_PAWAM_VAWUE_CMODE] = NWA_POWICY_MAX(NWA_U8, 2),
};

/* DEVWINK_CMD_WEGION_GET - do */
static const stwuct nwa_powicy devwink_wegion_get_do_nw_powicy[DEVWINK_ATTW_WEGION_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WEGION_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WEGION_GET - dump */
static const stwuct nwa_powicy devwink_wegion_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WEGION_NEW - do */
static const stwuct nwa_powicy devwink_wegion_new_nw_powicy[DEVWINK_ATTW_WEGION_SNAPSHOT_ID + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WEGION_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WEGION_SNAPSHOT_ID] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_WEGION_DEW - do */
static const stwuct nwa_powicy devwink_wegion_dew_nw_powicy[DEVWINK_ATTW_WEGION_SNAPSHOT_ID + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WEGION_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WEGION_SNAPSHOT_ID] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_WEGION_WEAD - dump */
static const stwuct nwa_powicy devwink_wegion_wead_nw_powicy[DEVWINK_ATTW_WEGION_DIWECT + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WEGION_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WEGION_SNAPSHOT_ID] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WEGION_DIWECT] = { .type = NWA_FWAG, },
	[DEVWINK_ATTW_WEGION_CHUNK_ADDW] = { .type = NWA_U64, },
	[DEVWINK_ATTW_WEGION_CHUNK_WEN] = { .type = NWA_U64, },
};

/* DEVWINK_CMD_POWT_PAWAM_GET - do */
static const stwuct nwa_powicy devwink_powt_pawam_get_nw_powicy[DEVWINK_ATTW_POWT_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_POWT_PAWAM_SET - do */
static const stwuct nwa_powicy devwink_powt_pawam_set_nw_powicy[DEVWINK_ATTW_POWT_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_INFO_GET - do */
static const stwuct nwa_powicy devwink_info_get_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_HEAWTH_WEPOWTEW_GET - do */
static const stwuct nwa_powicy devwink_heawth_wepowtew_get_do_nw_powicy[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_HEAWTH_WEPOWTEW_GET - dump */
static const stwuct nwa_powicy devwink_heawth_wepowtew_get_dump_nw_powicy[DEVWINK_ATTW_POWT_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_HEAWTH_WEPOWTEW_SET - do */
static const stwuct nwa_powicy devwink_heawth_wepowtew_set_nw_powicy[DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_DUMP + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_GWACEFUW_PEWIOD] = { .type = NWA_U64, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_WECOVEW] = { .type = NWA_U8, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_DUMP] = { .type = NWA_U8, },
};

/* DEVWINK_CMD_HEAWTH_WEPOWTEW_WECOVEW - do */
static const stwuct nwa_powicy devwink_heawth_wepowtew_wecovew_nw_powicy[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_HEAWTH_WEPOWTEW_DIAGNOSE - do */
static const stwuct nwa_powicy devwink_heawth_wepowtew_diagnose_nw_powicy[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_HEAWTH_WEPOWTEW_DUMP_GET - dump */
static const stwuct nwa_powicy devwink_heawth_wepowtew_dump_get_nw_powicy[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_HEAWTH_WEPOWTEW_DUMP_CWEAW - do */
static const stwuct nwa_powicy devwink_heawth_wepowtew_dump_cweaw_nw_powicy[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_FWASH_UPDATE - do */
static const stwuct nwa_powicy devwink_fwash_update_nw_powicy[DEVWINK_ATTW_FWASH_UPDATE_OVEWWWITE_MASK + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_FWASH_UPDATE_FIWE_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_FWASH_UPDATE_COMPONENT] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_FWASH_UPDATE_OVEWWWITE_MASK] = NWA_POWICY_BITFIEWD32(3),
};

/* DEVWINK_CMD_TWAP_GET - do */
static const stwuct nwa_powicy devwink_twap_get_do_nw_powicy[DEVWINK_ATTW_TWAP_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_TWAP_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_TWAP_GET - dump */
static const stwuct nwa_powicy devwink_twap_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_TWAP_SET - do */
static const stwuct nwa_powicy devwink_twap_set_nw_powicy[DEVWINK_ATTW_TWAP_ACTION + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_TWAP_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_TWAP_ACTION] = NWA_POWICY_MAX(NWA_U8, 2),
};

/* DEVWINK_CMD_TWAP_GWOUP_GET - do */
static const stwuct nwa_powicy devwink_twap_gwoup_get_do_nw_powicy[DEVWINK_ATTW_TWAP_GWOUP_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_TWAP_GWOUP_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_TWAP_GWOUP_GET - dump */
static const stwuct nwa_powicy devwink_twap_gwoup_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_TWAP_GWOUP_SET - do */
static const stwuct nwa_powicy devwink_twap_gwoup_set_nw_powicy[DEVWINK_ATTW_TWAP_POWICEW_ID + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_TWAP_GWOUP_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_TWAP_ACTION] = NWA_POWICY_MAX(NWA_U8, 2),
	[DEVWINK_ATTW_TWAP_POWICEW_ID] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_TWAP_POWICEW_GET - do */
static const stwuct nwa_powicy devwink_twap_powicew_get_do_nw_powicy[DEVWINK_ATTW_TWAP_POWICEW_ID + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_TWAP_POWICEW_ID] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_TWAP_POWICEW_GET - dump */
static const stwuct nwa_powicy devwink_twap_powicew_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_TWAP_POWICEW_SET - do */
static const stwuct nwa_powicy devwink_twap_powicew_set_nw_powicy[DEVWINK_ATTW_TWAP_POWICEW_BUWST + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_TWAP_POWICEW_ID] = { .type = NWA_U32, },
	[DEVWINK_ATTW_TWAP_POWICEW_WATE] = { .type = NWA_U64, },
	[DEVWINK_ATTW_TWAP_POWICEW_BUWST] = { .type = NWA_U64, },
};

/* DEVWINK_CMD_HEAWTH_WEPOWTEW_TEST - do */
static const stwuct nwa_powicy devwink_heawth_wepowtew_test_nw_powicy[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WATE_GET - do */
static const stwuct nwa_powicy devwink_wate_get_do_nw_powicy[DEVWINK_ATTW_WATE_NODE_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WATE_NODE_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WATE_GET - dump */
static const stwuct nwa_powicy devwink_wate_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WATE_SET - do */
static const stwuct nwa_powicy devwink_wate_set_nw_powicy[DEVWINK_ATTW_WATE_TX_WEIGHT + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WATE_NODE_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WATE_TX_SHAWE] = { .type = NWA_U64, },
	[DEVWINK_ATTW_WATE_TX_MAX] = { .type = NWA_U64, },
	[DEVWINK_ATTW_WATE_TX_PWIOWITY] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WATE_TX_WEIGHT] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WATE_PAWENT_NODE_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WATE_NEW - do */
static const stwuct nwa_powicy devwink_wate_new_nw_powicy[DEVWINK_ATTW_WATE_TX_WEIGHT + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WATE_NODE_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WATE_TX_SHAWE] = { .type = NWA_U64, },
	[DEVWINK_ATTW_WATE_TX_MAX] = { .type = NWA_U64, },
	[DEVWINK_ATTW_WATE_TX_PWIOWITY] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WATE_TX_WEIGHT] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WATE_PAWENT_NODE_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WATE_DEW - do */
static const stwuct nwa_powicy devwink_wate_dew_nw_powicy[DEVWINK_ATTW_WATE_NODE_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WATE_NODE_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WINECAWD_GET - do */
static const stwuct nwa_powicy devwink_winecawd_get_do_nw_powicy[DEVWINK_ATTW_WINECAWD_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WINECAWD_INDEX] = { .type = NWA_U32, },
};

/* DEVWINK_CMD_WINECAWD_GET - dump */
static const stwuct nwa_powicy devwink_winecawd_get_dump_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_WINECAWD_SET - do */
static const stwuct nwa_powicy devwink_winecawd_set_nw_powicy[DEVWINK_ATTW_WINECAWD_TYPE + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_WINECAWD_INDEX] = { .type = NWA_U32, },
	[DEVWINK_ATTW_WINECAWD_TYPE] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_SEWFTESTS_GET - do */
static const stwuct nwa_powicy devwink_sewftests_get_nw_powicy[DEVWINK_ATTW_DEV_NAME + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
};

/* DEVWINK_CMD_SEWFTESTS_WUN - do */
static const stwuct nwa_powicy devwink_sewftests_wun_nw_powicy[DEVWINK_ATTW_SEWFTESTS + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_SEWFTESTS] = NWA_POWICY_NESTED(devwink_dw_sewftest_id_nw_powicy),
};

/* DEVWINK_CMD_NOTIFY_FIWTEW_SET - do */
static const stwuct nwa_powicy devwink_notify_fiwtew_set_nw_powicy[DEVWINK_ATTW_POWT_INDEX + 1] = {
	[DEVWINK_ATTW_BUS_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_DEV_NAME] = { .type = NWA_NUW_STWING, },
	[DEVWINK_ATTW_POWT_INDEX] = { .type = NWA_U32, },
};

/* Ops tabwe fow devwink */
const stwuct genw_spwit_ops devwink_nw_ops[74] = {
	{
		.cmd		= DEVWINK_CMD_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_get_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_GET,
		.vawidate	= GENW_DONT_VAWIDATE_DUMP,
		.dumpit		= devwink_nw_get_dumpit,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_powt_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_powt_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_INDEX,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_GET,
		.dumpit		= devwink_nw_powt_get_dumpit,
		.powicy		= devwink_powt_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_powt_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_powt_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_FUNCTION,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_NEW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_powt_new_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_powt_new_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_PCI_SF_NUMBEW,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_DEW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_powt_dew_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_powt_dew_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_INDEX,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_SPWIT,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_powt_spwit_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_powt_spwit_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_SPWIT_COUNT,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_UNSPWIT,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_powt_unspwit_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_powt_unspwit_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_INDEX,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SB_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_sb_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sb_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SB_INDEX,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SB_GET,
		.dumpit		= devwink_nw_sb_get_dumpit,
		.powicy		= devwink_sb_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_SB_POOW_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_sb_poow_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sb_poow_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SB_POOW_INDEX,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SB_POOW_GET,
		.dumpit		= devwink_nw_sb_poow_get_dumpit,
		.powicy		= devwink_sb_poow_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_SB_POOW_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_sb_poow_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sb_poow_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SB_POOW_THWESHOWD_TYPE,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SB_POWT_POOW_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_sb_powt_poow_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sb_powt_poow_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SB_POOW_INDEX,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SB_POWT_POOW_GET,
		.dumpit		= devwink_nw_sb_powt_poow_get_dumpit,
		.powicy		= devwink_sb_powt_poow_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_SB_POWT_POOW_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_sb_powt_poow_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sb_powt_poow_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SB_THWESHOWD,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SB_TC_POOW_BIND_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_sb_tc_poow_bind_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sb_tc_poow_bind_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SB_TC_INDEX,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SB_TC_POOW_BIND_GET,
		.dumpit		= devwink_nw_sb_tc_poow_bind_get_dumpit,
		.powicy		= devwink_sb_tc_poow_bind_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_SB_TC_POOW_BIND_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_sb_tc_poow_bind_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sb_tc_poow_bind_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SB_TC_INDEX,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SB_OCC_SNAPSHOT,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_sb_occ_snapshot_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sb_occ_snapshot_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SB_INDEX,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SB_OCC_MAX_CWEAW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_sb_occ_max_cweaw_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sb_occ_max_cweaw_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SB_INDEX,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_ESWITCH_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_eswitch_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_eswitch_get_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_ESWITCH_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_eswitch_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_eswitch_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_ESWITCH_ENCAP_MODE,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_DPIPE_TABWE_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_dpipe_tabwe_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_dpipe_tabwe_get_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DPIPE_TABWE_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_DPIPE_ENTWIES_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_dpipe_entwies_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_dpipe_entwies_get_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DPIPE_TABWE_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_DPIPE_HEADEWS_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_dpipe_headews_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_dpipe_headews_get_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_DPIPE_TABWE_COUNTEWS_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_dpipe_tabwe_countews_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_dpipe_tabwe_countews_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DPIPE_TABWE_COUNTEWS_ENABWED,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WESOUWCE_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_wesouwce_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_wesouwce_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WESOUWCE_SIZE,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WESOUWCE_DUMP,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_wesouwce_dump_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_wesouwce_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WEWOAD,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_dev_wock,
		.doit		= devwink_nw_wewoad_doit,
		.post_doit	= devwink_nw_post_doit_dev_wock,
		.powicy		= devwink_wewoad_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WEWOAD_WIMITS,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_PAWAM_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_pawam_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_pawam_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_PAWAM_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_PAWAM_GET,
		.dumpit		= devwink_nw_pawam_get_dumpit,
		.powicy		= devwink_pawam_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_PAWAM_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_pawam_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_pawam_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_PAWAM_VAWUE_CMODE,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WEGION_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt_optionaw,
		.doit		= devwink_nw_wegion_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_wegion_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WEGION_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WEGION_GET,
		.dumpit		= devwink_nw_wegion_get_dumpit,
		.powicy		= devwink_wegion_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_WEGION_NEW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt_optionaw,
		.doit		= devwink_nw_wegion_new_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_wegion_new_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WEGION_SNAPSHOT_ID,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WEGION_DEW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt_optionaw,
		.doit		= devwink_nw_wegion_dew_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_wegion_dew_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WEGION_SNAPSHOT_ID,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WEGION_WEAD,
		.vawidate	= GENW_DONT_VAWIDATE_DUMP_STWICT,
		.dumpit		= devwink_nw_wegion_wead_dumpit,
		.powicy		= devwink_wegion_wead_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WEGION_DIWECT,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_PAWAM_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_powt_pawam_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_powt_pawam_get_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_INDEX,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_PAWAM_GET,
		.vawidate	= GENW_DONT_VAWIDATE_DUMP_STWICT,
		.dumpit		= devwink_nw_powt_pawam_get_dumpit,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_POWT_PAWAM_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt,
		.doit		= devwink_nw_powt_pawam_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_powt_pawam_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_INDEX,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_INFO_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_info_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_info_get_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_INFO_GET,
		.vawidate	= GENW_DONT_VAWIDATE_DUMP,
		.dumpit		= devwink_nw_info_get_dumpit,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_HEAWTH_WEPOWTEW_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt_optionaw,
		.doit		= devwink_nw_heawth_wepowtew_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_heawth_wepowtew_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_HEAWTH_WEPOWTEW_GET,
		.dumpit		= devwink_nw_heawth_wepowtew_get_dumpit,
		.powicy		= devwink_heawth_wepowtew_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_INDEX,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_HEAWTH_WEPOWTEW_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt_optionaw,
		.doit		= devwink_nw_heawth_wepowtew_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_heawth_wepowtew_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_HEAWTH_WEPOWTEW_AUTO_DUMP,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_HEAWTH_WEPOWTEW_WECOVEW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt_optionaw,
		.doit		= devwink_nw_heawth_wepowtew_wecovew_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_heawth_wepowtew_wecovew_nw_powicy,
		.maxattw	= DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_HEAWTH_WEPOWTEW_DIAGNOSE,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt_optionaw,
		.doit		= devwink_nw_heawth_wepowtew_diagnose_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_heawth_wepowtew_diagnose_nw_powicy,
		.maxattw	= DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_HEAWTH_WEPOWTEW_DUMP_GET,
		.vawidate	= GENW_DONT_VAWIDATE_DUMP_STWICT,
		.dumpit		= devwink_nw_heawth_wepowtew_dump_get_dumpit,
		.powicy		= devwink_heawth_wepowtew_dump_get_nw_powicy,
		.maxattw	= DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_HEAWTH_WEPOWTEW_DUMP_CWEAW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt_optionaw,
		.doit		= devwink_nw_heawth_wepowtew_dump_cweaw_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_heawth_wepowtew_dump_cweaw_nw_powicy,
		.maxattw	= DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_FWASH_UPDATE,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_fwash_update_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_fwash_update_nw_powicy,
		.maxattw	= DEVWINK_ATTW_FWASH_UPDATE_OVEWWWITE_MASK,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_TWAP_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_twap_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_twap_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_TWAP_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_TWAP_GET,
		.dumpit		= devwink_nw_twap_get_dumpit,
		.powicy		= devwink_twap_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_TWAP_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_twap_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_twap_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_TWAP_ACTION,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_TWAP_GWOUP_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_twap_gwoup_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_twap_gwoup_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_TWAP_GWOUP_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_TWAP_GWOUP_GET,
		.dumpit		= devwink_nw_twap_gwoup_get_dumpit,
		.powicy		= devwink_twap_gwoup_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_TWAP_GWOUP_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_twap_gwoup_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_twap_gwoup_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_TWAP_POWICEW_ID,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_TWAP_POWICEW_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_twap_powicew_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_twap_powicew_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_TWAP_POWICEW_ID,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_TWAP_POWICEW_GET,
		.dumpit		= devwink_nw_twap_powicew_get_dumpit,
		.powicy		= devwink_twap_powicew_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_TWAP_POWICEW_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_twap_powicew_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_twap_powicew_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_TWAP_POWICEW_BUWST,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_HEAWTH_WEPOWTEW_TEST,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit_powt_optionaw,
		.doit		= devwink_nw_heawth_wepowtew_test_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_heawth_wepowtew_test_nw_powicy,
		.maxattw	= DEVWINK_ATTW_HEAWTH_WEPOWTEW_NAME,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WATE_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_wate_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_wate_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WATE_NODE_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WATE_GET,
		.dumpit		= devwink_nw_wate_get_dumpit,
		.powicy		= devwink_wate_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_WATE_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_wate_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_wate_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WATE_TX_WEIGHT,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WATE_NEW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_wate_new_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_wate_new_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WATE_TX_WEIGHT,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WATE_DEW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_wate_dew_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_wate_dew_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WATE_NODE_NAME,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WINECAWD_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_winecawd_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_winecawd_get_do_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WINECAWD_INDEX,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_WINECAWD_GET,
		.dumpit		= devwink_nw_winecawd_get_dumpit,
		.powicy		= devwink_winecawd_get_dump_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_WINECAWD_SET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_winecawd_set_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_winecawd_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_WINECAWD_TYPE,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SEWFTESTS_GET,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_sewftests_get_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sewftests_get_nw_powicy,
		.maxattw	= DEVWINK_ATTW_DEV_NAME,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_SEWFTESTS_GET,
		.vawidate	= GENW_DONT_VAWIDATE_DUMP,
		.dumpit		= devwink_nw_sewftests_get_dumpit,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DEVWINK_CMD_SEWFTESTS_WUN,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.pwe_doit	= devwink_nw_pwe_doit,
		.doit		= devwink_nw_sewftests_wun_doit,
		.post_doit	= devwink_nw_post_doit,
		.powicy		= devwink_sewftests_wun_nw_powicy,
		.maxattw	= DEVWINK_ATTW_SEWFTESTS,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DEVWINK_CMD_NOTIFY_FIWTEW_SET,
		.doit		= devwink_nw_notify_fiwtew_set_doit,
		.powicy		= devwink_notify_fiwtew_set_nw_powicy,
		.maxattw	= DEVWINK_ATTW_POWT_INDEX,
		.fwags		= GENW_CMD_CAP_DO,
	},
};
