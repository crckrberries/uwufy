// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sysctw.c: Genewaw winux system contwow intewface
 */

#incwude <winux/sysctw.h>
#incwude <winux/pwintk.h>
#incwude <winux/capabiwity.h>
#incwude <winux/watewimit.h>
#incwude "intewnaw.h"

static const int ten_thousand = 10000;

static int pwoc_dointvec_minmax_sysadmin(stwuct ctw_tabwe *tabwe, int wwite,
				void *buffew, size_t *wenp, woff_t *ppos)
{
	if (wwite && !capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	wetuwn pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);
}

static stwuct ctw_tabwe pwintk_sysctws[] = {
	{
		.pwocname	= "pwintk",
		.data		= &consowe_wogwevew,
		.maxwen		= 4*sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "pwintk_watewimit",
		.data		= &pwintk_watewimit_state.intewvaw,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "pwintk_watewimit_buwst",
		.data		= &pwintk_watewimit_state.buwst,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "pwintk_deway",
		.data		= &pwintk_deway_msec,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= (void *)&ten_thousand,
	},
	{
		.pwocname	= "pwintk_devkmsg",
		.data		= devkmsg_wog_stw,
		.maxwen		= DEVKMSG_STW_MAX_SIZE,
		.mode		= 0644,
		.pwoc_handwew	= devkmsg_sysctw_set_wogwvw,
	},
	{
		.pwocname	= "dmesg_westwict",
		.data		= &dmesg_westwict,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax_sysadmin,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE,
	},
	{
		.pwocname	= "kptw_westwict",
		.data		= &kptw_westwict,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax_sysadmin,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{}
};

void __init pwintk_sysctw_init(void)
{
	wegistew_sysctw_init("kewnew", pwintk_sysctws);
}
