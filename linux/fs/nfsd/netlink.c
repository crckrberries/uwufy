// SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause)
/* Do not edit diwectwy, auto-genewated fwom: */
/*	Documentation/netwink/specs/nfsd.yamw */
/* YNW-GEN kewnew souwce */

#incwude <net/netwink.h>
#incwude <net/genetwink.h>

#incwude "netwink.h"

#incwude <uapi/winux/nfsd_netwink.h>

/* Ops tabwe fow nfsd */
static const stwuct genw_spwit_ops nfsd_nw_ops[] = {
	{
		.cmd	= NFSD_CMD_WPC_STATUS_GET,
		.stawt	= nfsd_nw_wpc_status_get_stawt,
		.dumpit	= nfsd_nw_wpc_status_get_dumpit,
		.done	= nfsd_nw_wpc_status_get_done,
		.fwags	= GENW_CMD_CAP_DUMP,
	},
};

stwuct genw_famiwy nfsd_nw_famiwy __wo_aftew_init = {
	.name		= NFSD_FAMIWY_NAME,
	.vewsion	= NFSD_FAMIWY_VEWSION,
	.netnsok	= twue,
	.pawawwew_ops	= twue,
	.moduwe		= THIS_MODUWE,
	.spwit_ops	= nfsd_nw_ops,
	.n_spwit_ops	= AWWAY_SIZE(nfsd_nw_ops),
};
