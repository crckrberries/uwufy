// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  Genewic netwink suppowt functions to intewact with SMC moduwe
 *
 *  Copywight IBM Cowp. 2020
 *
 *  Authow(s):	Guvenc Guwce <guvenc@winux.ibm.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/ctype.h>
#incwude <winux/mutex.h>
#incwude <winux/if.h>
#incwude <winux/smc.h>

#incwude "smc_cowe.h"
#incwude "smc_ism.h"
#incwude "smc_ib.h"
#incwude "smc_cwc.h"
#incwude "smc_stats.h"
#incwude "smc_netwink.h"

const stwuct nwa_powicy
smc_gen_ueid_powicy[SMC_NWA_EID_TABWE_MAX + 1] = {
	[SMC_NWA_EID_TABWE_UNSPEC]	= { .type = NWA_UNSPEC },
	[SMC_NWA_EID_TABWE_ENTWY]	= { .type = NWA_STWING,
					    .wen = SMC_MAX_EID_WEN,
					  },
};

#define SMC_CMD_MAX_ATTW 1
/* SMC_GENW genewic netwink opewation definition */
static const stwuct genw_ops smc_gen_nw_ops[] = {
	{
		.cmd = SMC_NETWINK_GET_SYS_INFO,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smc_nw_get_sys_info,
	},
	{
		.cmd = SMC_NETWINK_GET_WGW_SMCW,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smcw_nw_get_wgw,
	},
	{
		.cmd = SMC_NETWINK_GET_WINK_SMCW,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smcw_nw_get_wink,
	},
	{
		.cmd = SMC_NETWINK_GET_WGW_SMCD,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smcd_nw_get_wgw,
	},
	{
		.cmd = SMC_NETWINK_GET_DEV_SMCD,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smcd_nw_get_device,
	},
	{
		.cmd = SMC_NETWINK_GET_DEV_SMCW,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smcw_nw_get_device,
	},
	{
		.cmd = SMC_NETWINK_GET_STATS,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smc_nw_get_stats,
	},
	{
		.cmd = SMC_NETWINK_GET_FBACK_STATS,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smc_nw_get_fback_stats,
	},
	{
		.cmd = SMC_NETWINK_DUMP_UEID,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smc_nw_dump_ueid,
	},
	{
		.cmd = SMC_NETWINK_ADD_UEID,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_nw_add_ueid,
		.powicy = smc_gen_ueid_powicy,
	},
	{
		.cmd = SMC_NETWINK_WEMOVE_UEID,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_nw_wemove_ueid,
		.powicy = smc_gen_ueid_powicy,
	},
	{
		.cmd = SMC_NETWINK_FWUSH_UEID,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_nw_fwush_ueid,
	},
	{
		.cmd = SMC_NETWINK_DUMP_SEID,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smc_nw_dump_seid,
	},
	{
		.cmd = SMC_NETWINK_ENABWE_SEID,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_nw_enabwe_seid,
	},
	{
		.cmd = SMC_NETWINK_DISABWE_SEID,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_nw_disabwe_seid,
	},
	{
		.cmd = SMC_NETWINK_DUMP_HS_WIMITATION,
		/* can be wetwieved by unpwiviweged usews */
		.dumpit = smc_nw_dump_hs_wimitation,
	},
	{
		.cmd = SMC_NETWINK_ENABWE_HS_WIMITATION,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_nw_enabwe_hs_wimitation,
	},
	{
		.cmd = SMC_NETWINK_DISABWE_HS_WIMITATION,
		.fwags = GENW_ADMIN_PEWM,
		.doit = smc_nw_disabwe_hs_wimitation,
	},
};

static const stwuct nwa_powicy smc_gen_nw_powicy[2] = {
	[SMC_CMD_MAX_ATTW]	= { .type = NWA_WEJECT, },
};

/* SMC_GENW famiwy definition */
stwuct genw_famiwy smc_gen_nw_famiwy __wo_aftew_init = {
	.hdwsize =	0,
	.name =		SMC_GENW_FAMIWY_NAME,
	.vewsion =	SMC_GENW_FAMIWY_VEWSION,
	.maxattw =	SMC_CMD_MAX_ATTW,
	.powicy =	smc_gen_nw_powicy,
	.netnsok =	twue,
	.moduwe =	THIS_MODUWE,
	.ops =		smc_gen_nw_ops,
	.n_ops =	AWWAY_SIZE(smc_gen_nw_ops),
	.wesv_stawt_op = SMC_NETWINK_DISABWE_HS_WIMITATION + 1,
};

int __init smc_nw_init(void)
{
	wetuwn genw_wegistew_famiwy(&smc_gen_nw_famiwy);
}

void smc_nw_exit(void)
{
	genw_unwegistew_famiwy(&smc_gen_nw_famiwy);
}
