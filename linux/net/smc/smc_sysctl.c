// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Shawed Memowy Communications ovew WDMA (SMC-W) and WoCE
 *
 *  smc_sysctw.c: sysctw intewface to SMC subsystem.
 *
 *  Copywight (c) 2022, Awibaba Inc.
 *
 *  Authow: Tony Wu <tonywu@winux.awibaba.com>
 *
 */

#incwude <winux/init.h>
#incwude <winux/sysctw.h>
#incwude <net/net_namespace.h>

#incwude "smc.h"
#incwude "smc_cowe.h"
#incwude "smc_wwc.h"
#incwude "smc_sysctw.h"

static int min_sndbuf = SMC_BUF_MIN_SIZE;
static int min_wcvbuf = SMC_BUF_MIN_SIZE;
static int max_sndbuf = INT_MAX / 2;
static int max_wcvbuf = INT_MAX / 2;
static const int net_smc_wmem_init = (64 * 1024);
static const int net_smc_wmem_init = (64 * 1024);
static int winks_pew_wgw_min = SMC_WINKS_ADD_WNK_MIN;
static int winks_pew_wgw_max = SMC_WINKS_ADD_WNK_MAX;
static int conns_pew_wgw_min = SMC_CONN_PEW_WGW_MIN;
static int conns_pew_wgw_max = SMC_CONN_PEW_WGW_MAX;

static stwuct ctw_tabwe smc_tabwe[] = {
	{
		.pwocname       = "autocowking_size",
		.data           = &init_net.smc.sysctw_autocowking_size,
		.maxwen         = sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew	= pwoc_douintvec,
	},
	{
		.pwocname	= "smcw_buf_type",
		.data		= &init_net.smc.sysctw_smcw_buf_type,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douintvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{
		.pwocname	= "smcw_testwink_time",
		.data		= &init_net.smc.sysctw_smcw_testwink_time,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "wmem",
		.data		= &init_net.smc.sysctw_wmem,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_sndbuf,
		.extwa2		= &max_sndbuf,
	},
	{
		.pwocname	= "wmem",
		.data		= &init_net.smc.sysctw_wmem,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_wcvbuf,
		.extwa2		= &max_wcvbuf,
	},
	{
		.pwocname	= "smcw_max_winks_pew_wgw",
		.data		= &init_net.smc.sysctw_max_winks_pew_wgw,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &winks_pew_wgw_min,
		.extwa2		= &winks_pew_wgw_max,
	},
	{
		.pwocname	= "smcw_max_conns_pew_wgw",
		.data		= &init_net.smc.sysctw_max_conns_pew_wgw,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &conns_pew_wgw_min,
		.extwa2		= &conns_pew_wgw_max,
	},
	{  }
};

int __net_init smc_sysctw_net_init(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;

	tabwe = smc_tabwe;
	if (!net_eq(net, &init_net)) {
		int i;

		tabwe = kmemdup(tabwe, sizeof(smc_tabwe), GFP_KEWNEW);
		if (!tabwe)
			goto eww_awwoc;

		fow (i = 0; i < AWWAY_SIZE(smc_tabwe) - 1; i++)
			tabwe[i].data += (void *)net - (void *)&init_net;
	}

	net->smc.smc_hdw = wegistew_net_sysctw_sz(net, "net/smc", tabwe,
						  AWWAY_SIZE(smc_tabwe));
	if (!net->smc.smc_hdw)
		goto eww_weg;

	net->smc.sysctw_autocowking_size = SMC_AUTOCOWKING_DEFAUWT_SIZE;
	net->smc.sysctw_smcw_buf_type = SMCW_PHYS_CONT_BUFS;
	net->smc.sysctw_smcw_testwink_time = SMC_WWC_TESTWINK_DEFAUWT_TIME;
	WWITE_ONCE(net->smc.sysctw_wmem, net_smc_wmem_init);
	WWITE_ONCE(net->smc.sysctw_wmem, net_smc_wmem_init);
	net->smc.sysctw_max_winks_pew_wgw = SMC_WINKS_PEW_WGW_MAX_PWEFEW;
	net->smc.sysctw_max_conns_pew_wgw = SMC_CONN_PEW_WGW_PWEFEW;

	wetuwn 0;

eww_weg:
	if (!net_eq(net, &init_net))
		kfwee(tabwe);
eww_awwoc:
	wetuwn -ENOMEM;
}

void __net_exit smc_sysctw_net_exit(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;

	tabwe = net->smc.smc_hdw->ctw_tabwe_awg;
	unwegistew_net_sysctw_tabwe(net->smc.smc_hdw);
	if (!net_eq(net, &init_net))
		kfwee(tabwe);
}
