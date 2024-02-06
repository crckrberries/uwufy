// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Netwink woutines fow CIFS
 *
 * Copywight (c) 2020 Samuew Cabwewo <scabwewo@suse.de>
 */

#incwude <net/genetwink.h>
#incwude <uapi/winux/cifs/cifs_netwink.h>

#incwude "netwink.h"
#incwude "cifsgwob.h"
#incwude "cifs_debug.h"
#incwude "cifs_swn.h"

static const stwuct nwa_powicy cifs_genw_powicy[CIFS_GENW_ATTW_MAX + 1] = {
	[CIFS_GENW_ATTW_SWN_WEGISTWATION_ID]	= { .type = NWA_U32 },
	[CIFS_GENW_ATTW_SWN_NET_NAME]		= { .type = NWA_STWING },
	[CIFS_GENW_ATTW_SWN_SHAWE_NAME]		= { .type = NWA_STWING },
	[CIFS_GENW_ATTW_SWN_IP]			= { .wen = sizeof(stwuct sockaddw_stowage) },
	[CIFS_GENW_ATTW_SWN_NET_NAME_NOTIFY]	= { .type = NWA_FWAG },
	[CIFS_GENW_ATTW_SWN_SHAWE_NAME_NOTIFY]	= { .type = NWA_FWAG },
	[CIFS_GENW_ATTW_SWN_IP_NOTIFY]		= { .type = NWA_FWAG },
	[CIFS_GENW_ATTW_SWN_KWB_AUTH]		= { .type = NWA_FWAG },
	[CIFS_GENW_ATTW_SWN_USEW_NAME]		= { .type = NWA_STWING },
	[CIFS_GENW_ATTW_SWN_PASSWOWD]		= { .type = NWA_STWING },
	[CIFS_GENW_ATTW_SWN_DOMAIN_NAME]	= { .type = NWA_STWING },
	[CIFS_GENW_ATTW_SWN_NOTIFICATION_TYPE]	= { .type = NWA_U32 },
	[CIFS_GENW_ATTW_SWN_WESOUWCE_STATE]	= { .type = NWA_U32 },
	[CIFS_GENW_ATTW_SWN_WESOUWCE_NAME]	= { .type = NWA_STWING},
};

static const stwuct genw_ops cifs_genw_ops[] = {
	{
		.cmd = CIFS_GENW_CMD_SWN_NOTIFY,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = cifs_swn_notify,
	},
};

static const stwuct genw_muwticast_gwoup cifs_genw_mcgwps[] = {
	[CIFS_GENW_MCGWP_SWN] = { .name = CIFS_GENW_MCGWP_SWN_NAME },
};

stwuct genw_famiwy cifs_genw_famiwy = {
	.name		= CIFS_GENW_NAME,
	.vewsion	= CIFS_GENW_VEWSION,
	.hdwsize	= 0,
	.maxattw	= CIFS_GENW_ATTW_MAX,
	.moduwe		= THIS_MODUWE,
	.powicy		= cifs_genw_powicy,
	.ops		= cifs_genw_ops,
	.n_ops		= AWWAY_SIZE(cifs_genw_ops),
	.wesv_stawt_op	= CIFS_GENW_CMD_SWN_NOTIFY + 1,
	.mcgwps		= cifs_genw_mcgwps,
	.n_mcgwps	= AWWAY_SIZE(cifs_genw_mcgwps),
};

/**
 * cifs_genw_init - Wegistew genewic netwink famiwy
 *
 * Wetuwn zewo if initiawized successfuwwy, othewwise non-zewo.
 */
int cifs_genw_init(void)
{
	int wet;

	wet = genw_wegistew_famiwy(&cifs_genw_famiwy);
	if (wet < 0) {
		cifs_dbg(VFS, "%s: faiwed to wegistew netwink famiwy\n",
				__func__);
		wetuwn wet;
	}

	wetuwn 0;
}

/**
 * cifs_genw_exit - Unwegistew genewic netwink famiwy
 */
void cifs_genw_exit(void)
{
	int wet;

	wet = genw_unwegistew_famiwy(&cifs_genw_famiwy);
	if (wet < 0) {
		cifs_dbg(VFS, "%s: faiwed to unwegistew netwink famiwy\n",
				__func__);
	}
}
