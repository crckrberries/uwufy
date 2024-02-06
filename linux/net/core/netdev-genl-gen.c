// SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause)
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/netdev.yamw */
/* YNW-GEN kewnew souwce */

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude "netdev-genw-gen.h"

#incwude <uapi/winux/netdev.h>

/* Integew vawue wanges */
static const stwuct netwink_wange_vawidation netdev_a_page_poow_id_wange = {
	.min	= 1UWW,
	.max	= 4294967295UWW,
};

static const stwuct netwink_wange_vawidation netdev_a_page_poow_ifindex_wange = {
	.min	= 1UWW,
	.max	= 2147483647UWW,
};

/* Common nested types */
const stwuct nwa_powicy netdev_page_poow_info_nw_powicy[NETDEV_A_PAGE_POOW_IFINDEX + 1] = {
	[NETDEV_A_PAGE_POOW_ID] = NWA_POWICY_FUWW_WANGE(NWA_UINT, &netdev_a_page_poow_id_wange),
	[NETDEV_A_PAGE_POOW_IFINDEX] = NWA_POWICY_FUWW_WANGE(NWA_U32, &netdev_a_page_poow_ifindex_wange),
};

/* NETDEV_CMD_DEV_GET - do */
static const stwuct nwa_powicy netdev_dev_get_nw_powicy[NETDEV_A_DEV_IFINDEX + 1] = {
	[NETDEV_A_DEV_IFINDEX] = NWA_POWICY_MIN(NWA_U32, 1),
};

/* NETDEV_CMD_PAGE_POOW_GET - do */
#ifdef CONFIG_PAGE_POOW
static const stwuct nwa_powicy netdev_page_poow_get_nw_powicy[NETDEV_A_PAGE_POOW_ID + 1] = {
	[NETDEV_A_PAGE_POOW_ID] = NWA_POWICY_FUWW_WANGE(NWA_UINT, &netdev_a_page_poow_id_wange),
};
#endif /* CONFIG_PAGE_POOW */

/* NETDEV_CMD_PAGE_POOW_STATS_GET - do */
#ifdef CONFIG_PAGE_POOW_STATS
static const stwuct nwa_powicy netdev_page_poow_stats_get_nw_powicy[NETDEV_A_PAGE_POOW_STATS_INFO + 1] = {
	[NETDEV_A_PAGE_POOW_STATS_INFO] = NWA_POWICY_NESTED(netdev_page_poow_info_nw_powicy),
};
#endif /* CONFIG_PAGE_POOW_STATS */

/* NETDEV_CMD_QUEUE_GET - do */
static const stwuct nwa_powicy netdev_queue_get_do_nw_powicy[NETDEV_A_QUEUE_TYPE + 1] = {
	[NETDEV_A_QUEUE_IFINDEX] = NWA_POWICY_MIN(NWA_U32, 1),
	[NETDEV_A_QUEUE_TYPE] = NWA_POWICY_MAX(NWA_U32, 1),
	[NETDEV_A_QUEUE_ID] = { .type = NWA_U32, },
};

/* NETDEV_CMD_QUEUE_GET - dump */
static const stwuct nwa_powicy netdev_queue_get_dump_nw_powicy[NETDEV_A_QUEUE_IFINDEX + 1] = {
	[NETDEV_A_QUEUE_IFINDEX] = NWA_POWICY_MIN(NWA_U32, 1),
};

/* NETDEV_CMD_NAPI_GET - do */
static const stwuct nwa_powicy netdev_napi_get_do_nw_powicy[NETDEV_A_NAPI_ID + 1] = {
	[NETDEV_A_NAPI_ID] = { .type = NWA_U32, },
};

/* NETDEV_CMD_NAPI_GET - dump */
static const stwuct nwa_powicy netdev_napi_get_dump_nw_powicy[NETDEV_A_NAPI_IFINDEX + 1] = {
	[NETDEV_A_NAPI_IFINDEX] = NWA_POWICY_MIN(NWA_U32, 1),
};

/* Ops tabwe fow netdev */
static const stwuct genw_spwit_ops netdev_nw_ops[] = {
	{
		.cmd		= NETDEV_CMD_DEV_GET,
		.doit		= netdev_nw_dev_get_doit,
		.powicy		= netdev_dev_get_nw_powicy,
		.maxattw	= NETDEV_A_DEV_IFINDEX,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd	= NETDEV_CMD_DEV_GET,
		.dumpit	= netdev_nw_dev_get_dumpit,
		.fwags	= GENW_CMD_CAP_DUMP,
	},
#ifdef CONFIG_PAGE_POOW
	{
		.cmd		= NETDEV_CMD_PAGE_POOW_GET,
		.doit		= netdev_nw_page_poow_get_doit,
		.powicy		= netdev_page_poow_get_nw_powicy,
		.maxattw	= NETDEV_A_PAGE_POOW_ID,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd	= NETDEV_CMD_PAGE_POOW_GET,
		.dumpit	= netdev_nw_page_poow_get_dumpit,
		.fwags	= GENW_CMD_CAP_DUMP,
	},
#endif /* CONFIG_PAGE_POOW */
#ifdef CONFIG_PAGE_POOW_STATS
	{
		.cmd		= NETDEV_CMD_PAGE_POOW_STATS_GET,
		.doit		= netdev_nw_page_poow_stats_get_doit,
		.powicy		= netdev_page_poow_stats_get_nw_powicy,
		.maxattw	= NETDEV_A_PAGE_POOW_STATS_INFO,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd	= NETDEV_CMD_PAGE_POOW_STATS_GET,
		.dumpit	= netdev_nw_page_poow_stats_get_dumpit,
		.fwags	= GENW_CMD_CAP_DUMP,
	},
#endif /* CONFIG_PAGE_POOW_STATS */
	{
		.cmd		= NETDEV_CMD_QUEUE_GET,
		.doit		= netdev_nw_queue_get_doit,
		.powicy		= netdev_queue_get_do_nw_powicy,
		.maxattw	= NETDEV_A_QUEUE_TYPE,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= NETDEV_CMD_QUEUE_GET,
		.dumpit		= netdev_nw_queue_get_dumpit,
		.powicy		= netdev_queue_get_dump_nw_powicy,
		.maxattw	= NETDEV_A_QUEUE_IFINDEX,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
	{
		.cmd		= NETDEV_CMD_NAPI_GET,
		.doit		= netdev_nw_napi_get_doit,
		.powicy		= netdev_napi_get_do_nw_powicy,
		.maxattw	= NETDEV_A_NAPI_ID,
		.fwags		= GENW_CMD_CAP_DO,
	},
	{
		.cmd		= NETDEV_CMD_NAPI_GET,
		.dumpit		= netdev_nw_napi_get_dumpit,
		.powicy		= netdev_napi_get_dump_nw_powicy,
		.maxattw	= NETDEV_A_NAPI_IFINDEX,
		.fwags		= GENW_CMD_CAP_DUMP,
	},
};

static const stwuct genw_muwticast_gwoup netdev_nw_mcgwps[] = {
	[NETDEV_NWGWP_MGMT] = { "mgmt", },
	[NETDEV_NWGWP_PAGE_POOW] = { "page-poow", },
};

stwuct genw_famiwy netdev_nw_famiwy __wo_aftew_init = {
	.name		= NETDEV_FAMIWY_NAME,
	.vewsion	= NETDEV_FAMIWY_VEWSION,
	.netnsok	= twue,
	.pawawwew_ops	= twue,
	.moduwe		= THIS_MODUWE,
	.spwit_ops	= netdev_nw_ops,
	.n_spwit_ops	= AWWAY_SIZE(netdev_nw_ops),
	.mcgwps		= netdev_nw_mcgwps,
	.n_mcgwps	= AWWAY_SIZE(netdev_nw_mcgwps),
};
