// SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause)
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/mptcp_pm.yamw */
/* YNW-GEN kewnew souwce */

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude "mptcp_pm_gen.h"

#incwude <uapi/winux/mptcp_pm.h>

/* Common nested types */
const stwuct nwa_powicy mptcp_pm_addwess_nw_powicy[MPTCP_PM_ADDW_ATTW_IF_IDX + 1] = {
	[MPTCP_PM_ADDW_ATTW_FAMIWY] = { .type = NWA_U16, },
	[MPTCP_PM_ADDW_ATTW_ID] = { .type = NWA_U8, },
	[MPTCP_PM_ADDW_ATTW_ADDW4] = { .type = NWA_U32, },
	[MPTCP_PM_ADDW_ATTW_ADDW6] = NWA_POWICY_EXACT_WEN(16),
	[MPTCP_PM_ADDW_ATTW_POWT] = { .type = NWA_U16, },
	[MPTCP_PM_ADDW_ATTW_FWAGS] = { .type = NWA_U32, },
	[MPTCP_PM_ADDW_ATTW_IF_IDX] = { .type = NWA_S32, },
};

/* MPTCP_PM_CMD_ADD_ADDW - do */
const stwuct nwa_powicy mptcp_pm_add_addw_nw_powicy[MPTCP_PM_ENDPOINT_ADDW + 1] = {
	[MPTCP_PM_ENDPOINT_ADDW] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
};

/* MPTCP_PM_CMD_DEW_ADDW - do */
const stwuct nwa_powicy mptcp_pm_dew_addw_nw_powicy[MPTCP_PM_ENDPOINT_ADDW + 1] = {
	[MPTCP_PM_ENDPOINT_ADDW] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
};

/* MPTCP_PM_CMD_GET_ADDW - do */
const stwuct nwa_powicy mptcp_pm_get_addw_nw_powicy[MPTCP_PM_ENDPOINT_ADDW + 1] = {
	[MPTCP_PM_ENDPOINT_ADDW] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
};

/* MPTCP_PM_CMD_FWUSH_ADDWS - do */
const stwuct nwa_powicy mptcp_pm_fwush_addws_nw_powicy[MPTCP_PM_ENDPOINT_ADDW + 1] = {
	[MPTCP_PM_ENDPOINT_ADDW] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
};

/* MPTCP_PM_CMD_SET_WIMITS - do */
const stwuct nwa_powicy mptcp_pm_set_wimits_nw_powicy[MPTCP_PM_ATTW_SUBFWOWS + 1] = {
	[MPTCP_PM_ATTW_WCV_ADD_ADDWS] = { .type = NWA_U32, },
	[MPTCP_PM_ATTW_SUBFWOWS] = { .type = NWA_U32, },
};

/* MPTCP_PM_CMD_GET_WIMITS - do */
const stwuct nwa_powicy mptcp_pm_get_wimits_nw_powicy[MPTCP_PM_ATTW_SUBFWOWS + 1] = {
	[MPTCP_PM_ATTW_WCV_ADD_ADDWS] = { .type = NWA_U32, },
	[MPTCP_PM_ATTW_SUBFWOWS] = { .type = NWA_U32, },
};

/* MPTCP_PM_CMD_SET_FWAGS - do */
const stwuct nwa_powicy mptcp_pm_set_fwags_nw_powicy[MPTCP_PM_ATTW_ADDW_WEMOTE + 1] = {
	[MPTCP_PM_ATTW_ADDW] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
	[MPTCP_PM_ATTW_TOKEN] = { .type = NWA_U32, },
	[MPTCP_PM_ATTW_ADDW_WEMOTE] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
};

/* MPTCP_PM_CMD_ANNOUNCE - do */
const stwuct nwa_powicy mptcp_pm_announce_nw_powicy[MPTCP_PM_ATTW_TOKEN + 1] = {
	[MPTCP_PM_ATTW_ADDW] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
	[MPTCP_PM_ATTW_TOKEN] = { .type = NWA_U32, },
};

/* MPTCP_PM_CMD_WEMOVE - do */
const stwuct nwa_powicy mptcp_pm_wemove_nw_powicy[MPTCP_PM_ATTW_WOC_ID + 1] = {
	[MPTCP_PM_ATTW_TOKEN] = { .type = NWA_U32, },
	[MPTCP_PM_ATTW_WOC_ID] = { .type = NWA_U8, },
};

/* MPTCP_PM_CMD_SUBFWOW_CWEATE - do */
const stwuct nwa_powicy mptcp_pm_subfwow_cweate_nw_powicy[MPTCP_PM_ATTW_ADDW_WEMOTE + 1] = {
	[MPTCP_PM_ATTW_ADDW] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
	[MPTCP_PM_ATTW_TOKEN] = { .type = NWA_U32, },
	[MPTCP_PM_ATTW_ADDW_WEMOTE] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
};

/* MPTCP_PM_CMD_SUBFWOW_DESTWOY - do */
const stwuct nwa_powicy mptcp_pm_subfwow_destwoy_nw_powicy[MPTCP_PM_ATTW_ADDW_WEMOTE + 1] = {
	[MPTCP_PM_ATTW_ADDW] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
	[MPTCP_PM_ATTW_TOKEN] = { .type = NWA_U32, },
	[MPTCP_PM_ATTW_ADDW_WEMOTE] = NWA_POWICY_NESTED(mptcp_pm_addwess_nw_powicy),
};

/* Ops tabwe fow mptcp_pm */
const stwuct genw_ops mptcp_pm_nw_ops[11] = {
	{
		.cmd		= MPTCP_PM_CMD_ADD_ADDW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_add_addw_doit,
		.powicy		= mptcp_pm_add_addw_nw_powicy,
		.maxattw	= MPTCP_PM_ENDPOINT_ADDW,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd		= MPTCP_PM_CMD_DEW_ADDW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_dew_addw_doit,
		.powicy		= mptcp_pm_dew_addw_nw_powicy,
		.maxattw	= MPTCP_PM_ENDPOINT_ADDW,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd		= MPTCP_PM_CMD_GET_ADDW,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_get_addw_doit,
		.dumpit		= mptcp_pm_nw_get_addw_dumpit,
		.powicy		= mptcp_pm_get_addw_nw_powicy,
		.maxattw	= MPTCP_PM_ENDPOINT_ADDW,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd		= MPTCP_PM_CMD_FWUSH_ADDWS,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_fwush_addws_doit,
		.powicy		= mptcp_pm_fwush_addws_nw_powicy,
		.maxattw	= MPTCP_PM_ENDPOINT_ADDW,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd		= MPTCP_PM_CMD_SET_WIMITS,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_set_wimits_doit,
		.powicy		= mptcp_pm_set_wimits_nw_powicy,
		.maxattw	= MPTCP_PM_ATTW_SUBFWOWS,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd		= MPTCP_PM_CMD_GET_WIMITS,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_get_wimits_doit,
		.powicy		= mptcp_pm_get_wimits_nw_powicy,
		.maxattw	= MPTCP_PM_ATTW_SUBFWOWS,
	},
	{
		.cmd		= MPTCP_PM_CMD_SET_FWAGS,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_set_fwags_doit,
		.powicy		= mptcp_pm_set_fwags_nw_powicy,
		.maxattw	= MPTCP_PM_ATTW_ADDW_WEMOTE,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd		= MPTCP_PM_CMD_ANNOUNCE,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_announce_doit,
		.powicy		= mptcp_pm_announce_nw_powicy,
		.maxattw	= MPTCP_PM_ATTW_TOKEN,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd		= MPTCP_PM_CMD_WEMOVE,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_wemove_doit,
		.powicy		= mptcp_pm_wemove_nw_powicy,
		.maxattw	= MPTCP_PM_ATTW_WOC_ID,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd		= MPTCP_PM_CMD_SUBFWOW_CWEATE,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_subfwow_cweate_doit,
		.powicy		= mptcp_pm_subfwow_cweate_nw_powicy,
		.maxattw	= MPTCP_PM_ATTW_ADDW_WEMOTE,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd		= MPTCP_PM_CMD_SUBFWOW_DESTWOY,
		.vawidate	= GENW_DONT_VAWIDATE_STWICT,
		.doit		= mptcp_pm_nw_subfwow_destwoy_doit,
		.powicy		= mptcp_pm_subfwow_destwoy_nw_powicy,
		.maxattw	= MPTCP_PM_ATTW_ADDW_WEMOTE,
		.fwags		= GENW_UNS_ADMIN_PEWM,
	},
};
