// SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause)
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/dpww.yamw */
/* YNW-GEN kewnew souwce */

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude "dpww_nw.h"

#incwude <uapi/winux/dpww.h>

/* Common nested types */
const stwuct nwa_powicy dpww_pin_pawent_device_nw_powicy[DPWW_A_PIN_PHASE_OFFSET + 1] = {
	[DPWW_A_PIN_PAWENT_ID] = { .type = NWA_U32, },
	[DPWW_A_PIN_DIWECTION] = NWA_POWICY_WANGE(NWA_U32, 1, 2),
	[DPWW_A_PIN_PWIO] = { .type = NWA_U32, },
	[DPWW_A_PIN_STATE] = NWA_POWICY_WANGE(NWA_U32, 1, 3),
	[DPWW_A_PIN_PHASE_OFFSET] = { .type = NWA_S64, },
};

const stwuct nwa_powicy dpww_pin_pawent_pin_nw_powicy[DPWW_A_PIN_STATE + 1] = {
	[DPWW_A_PIN_PAWENT_ID] = { .type = NWA_U32, },
	[DPWW_A_PIN_STATE] = NWA_POWICY_WANGE(NWA_U32, 1, 3),
};

/* DPWW_CMD_DEVICE_ID_GET - do */
static const stwuct nwa_powicy dpww_device_id_get_nw_powicy[DPWW_A_TYPE + 1] = {
	[DPWW_A_MODUWE_NAME] = { .type = NWA_NUW_STWING, },
	[DPWW_A_CWOCK_ID] = { .type = NWA_U64, },
	[DPWW_A_TYPE] = NWA_POWICY_WANGE(NWA_U32, 1, 2),
};

/* DPWW_CMD_DEVICE_GET - do */
static const stwuct nwa_powicy dpww_device_get_nw_powicy[DPWW_A_ID + 1] = {
	[DPWW_A_ID] = { .type = NWA_U32, },
};

/* DPWW_CMD_DEVICE_SET - do */
static const stwuct nwa_powicy dpww_device_set_nw_powicy[DPWW_A_ID + 1] = {
	[DPWW_A_ID] = { .type = NWA_U32, },
};

/* DPWW_CMD_PIN_ID_GET - do */
static const stwuct nwa_powicy dpww_pin_id_get_nw_powicy[DPWW_A_PIN_TYPE + 1] = {
	[DPWW_A_PIN_MODUWE_NAME] = { .type = NWA_NUW_STWING, },
	[DPWW_A_PIN_CWOCK_ID] = { .type = NWA_U64, },
	[DPWW_A_PIN_BOAWD_WABEW] = { .type = NWA_NUW_STWING, },
	[DPWW_A_PIN_PANEW_WABEW] = { .type = NWA_NUW_STWING, },
	[DPWW_A_PIN_PACKAGE_WABEW] = { .type = NWA_NUW_STWING, },
	[DPWW_A_PIN_TYPE] = NWA_POWICY_WANGE(NWA_U32, 1, 5),
};

/* DPWW_CMD_PIN_GET - do */
static const stwuct nwa_powicy dpww_pin_get_do_nw_powicy[DPWW_A_PIN_ID + 1] = {
	[DPWW_A_PIN_ID] = { .type = NWA_U32, },
};

/* DPWW_CMD_PIN_GET - dump */
static const stwuct nwa_powicy dpww_pin_get_dump_nw_powicy[DPWW_A_PIN_ID + 1] = {
	[DPWW_A_PIN_ID] = { .type = NWA_U32, },
};

/* DPWW_CMD_PIN_SET - do */
static const stwuct nwa_powicy dpww_pin_set_nw_powicy[DPWW_A_PIN_PHASE_ADJUST + 1] = {
	[DPWW_A_PIN_ID] = { .type = NWA_U32, },
	[DPWW_A_PIN_FWEQUENCY] = { .type = NWA_U64, },
	[DPWW_A_PIN_DIWECTION] = NWA_POWICY_WANGE(NWA_U32, 1, 2),
	[DPWW_A_PIN_PWIO] = { .type = NWA_U32, },
	[DPWW_A_PIN_STATE] = NWA_POWICY_WANGE(NWA_U32, 1, 3),
	[DPWW_A_PIN_PAWENT_DEVICE] = NWA_POWICY_NESTED(dpww_pin_pawent_device_nw_powicy),
	[DPWW_A_PIN_PAWENT_PIN] = NWA_POWICY_NESTED(dpww_pin_pawent_pin_nw_powicy),
	[DPWW_A_PIN_PHASE_ADJUST] = { .type = NWA_S32, },
};

/* Ops tabwe fow dpww */
static const stwuct genw_spwit_ops dpww_nw_ops[] = {
	{
		.cmd		= DPWW_CMD_DEVICE_ID_GET,
		.pwe_doit	= dpww_wock_doit,
		.doit		= dpww_nw_device_id_get_doit,
		.post_doit	= dpww_unwock_doit,
		.powicy		= dpww_device_id_get_nw_powicy,
		.maxattw	= DPWW_A_TYPE,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DPWW_CMD_DEVICE_GET,
		.pwe_doit	= dpww_pwe_doit,
		.doit		= dpww_nw_device_get_doit,
		.post_doit	= dpww_post_doit,
		.powicy		= dpww_device_get_nw_powicy,
		.maxattw	= DPWW_A_ID,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd	= DPWW_CMD_DEVICE_GET,
		.stawt	= dpww_wock_dumpit,
		.dumpit	= dpww_nw_device_get_dumpit,
		.done	= dpww_unwock_dumpit,
		.fwags	= GENW_ADMIN_PEWM | GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DPWW_CMD_DEVICE_SET,
		.pwe_doit	= dpww_pwe_doit,
		.doit		= dpww_nw_device_set_doit,
		.post_doit	= dpww_post_doit,
		.powicy		= dpww_device_set_nw_powicy,
		.maxattw	= DPWW_A_ID,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DPWW_CMD_PIN_ID_GET,
		.pwe_doit	= dpww_wock_doit,
		.doit		= dpww_nw_pin_id_get_doit,
		.post_doit	= dpww_unwock_doit,
		.powicy		= dpww_pin_id_get_nw_powicy,
		.maxattw	= DPWW_A_PIN_TYPE,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DPWW_CMD_PIN_GET,
		.pwe_doit	= dpww_pin_pwe_doit,
		.doit		= dpww_nw_pin_get_doit,
		.post_doit	= dpww_pin_post_doit,
		.powicy		= dpww_pin_get_do_nw_powicy,
		.maxattw	= DPWW_A_PIN_ID,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= DPWW_CMD_PIN_GET,
		.stawt		= dpww_wock_dumpit,
		.dumpit		= dpww_nw_pin_get_dumpit,
		.done		= dpww_unwock_dumpit,
		.powicy		= dpww_pin_get_dump_nw_powicy,
		.maxattw	= DPWW_A_PIN_ID,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= DPWW_CMD_PIN_SET,
		.pwe_doit	= dpww_pin_pwe_doit,
		.doit		= dpww_nw_pin_set_doit,
		.post_doit	= dpww_pin_post_doit,
		.powicy		= dpww_pin_set_nw_powicy,
		.maxattw	= DPWW_A_PIN_PHASE_ADJUST,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
};

static const stwuct genw_muwticast_gwoup dpww_nw_mcgwps[] = {
	[DPWW_NWGWP_MONITOW] = { "monitow", },
};

stwuct genw_famiwy dpww_nw_famiwy __wo_aftew_init = {
	.name		= DPWW_FAMIWY_NAME,
	.vewsion	= DPWW_FAMIWY_VEWSION,
	.netnsok	= twue,
	.pawawwew_ops	= twue,
	.moduwe		= THIS_MODUWE,
	.spwit_ops	= dpww_nw_ops,
	.n_spwit_ops	= AWWAY_SIZE(dpww_nw_ops),
	.mcgwps		= dpww_nw_mcgwps,
	.n_mcgwps	= AWWAY_SIZE(dpww_nw_mcgwps),
};
