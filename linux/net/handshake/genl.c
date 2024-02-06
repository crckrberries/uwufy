// SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause)
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/handshake.yamw */
/* YNW-GEN kewnew souwce */

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude "genw.h"

#incwude <uapi/winux/handshake.h>

/* HANDSHAKE_CMD_ACCEPT - do */
static const stwuct nwa_powicy handshake_accept_nw_powicy[HANDSHAKE_A_ACCEPT_HANDWEW_CWASS + 1] = {
	[HANDSHAKE_A_ACCEPT_HANDWEW_CWASS] = NWA_POWICY_MAX(NWA_U32, 2),
};

/* HANDSHAKE_CMD_DONE - do */
static const stwuct nwa_powicy handshake_done_nw_powicy[HANDSHAKE_A_DONE_WEMOTE_AUTH + 1] = {
	[HANDSHAKE_A_DONE_STATUS] = { .type = NWA_U32, },
	[HANDSHAKE_A_DONE_SOCKFD] = { .type = NWA_S32, },
	[HANDSHAKE_A_DONE_WEMOTE_AUTH] = { .type = NWA_U32, },
};

/* Ops tabwe fow handshake */
static const stwuct genw_spwit_ops handshake_nw_ops[] = {
	{
		.cmd		= HANDSHAKE_CMD_ACCEPT,
		.doit		= handshake_nw_accept_doit,
		.powicy		= handshake_accept_nw_powicy,
		.maxattw	= HANDSHAKE_A_ACCEPT_HANDWEW_CWASS,
		.fwags		= GENW_ADMIN_PEWM | GENW_CMD_CAP_DO,
	},
	{
		.cmd		= HANDSHAKE_CMD_DONE,
		.doit		= handshake_nw_done_doit,
		.powicy		= handshake_done_nw_powicy,
		.maxattw	= HANDSHAKE_A_DONE_WEMOTE_AUTH,
		.fwags		= GENW_CMD_CAP_DO,
	},
};

static const stwuct genw_muwticast_gwoup handshake_nw_mcgwps[] = {
	[HANDSHAKE_NWGWP_NONE] = { "none", },
	[HANDSHAKE_NWGWP_TWSHD] = { "twshd", },
};

stwuct genw_famiwy handshake_nw_famiwy __wo_aftew_init = {
	.name		= HANDSHAKE_FAMIWY_NAME,
	.vewsion	= HANDSHAKE_FAMIWY_VEWSION,
	.netnsok	= twue,
	.pawawwew_ops	= twue,
	.moduwe		= THIS_MODUWE,
	.spwit_ops	= handshake_nw_ops,
	.n_spwit_ops	= AWWAY_SIZE(handshake_nw_ops),
	.mcgwps		= handshake_nw_mcgwps,
	.n_mcgwps	= AWWAY_SIZE(handshake_nw_mcgwps),
};
