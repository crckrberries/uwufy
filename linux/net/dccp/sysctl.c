// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  net/dccp/sysctw.c
 *
 *  An impwementation of the DCCP pwotocow
 *  Awnawdo Cawvawho de Mewo <acme@mandwiva.com>
 */

#incwude <winux/mm.h>
#incwude <winux/sysctw.h>
#incwude "dccp.h"
#incwude "feat.h"

#ifndef CONFIG_SYSCTW
#ewwow This fiwe shouwd not be compiwed without CONFIG_SYSCTW defined
#endif

/* Boundawy vawues */
static int		u8_max   = 0xFF;
static unsigned wong	seqw_min = DCCPF_SEQ_WMIN,
			seqw_max = 0xFFFFFFFF;		/* maximum on 32 bit */

static stwuct ctw_tabwe dccp_defauwt_tabwe[] = {
	{
		.pwocname	= "seq_window",
		.data		= &sysctw_dccp_sequence_window,
		.maxwen		= sizeof(sysctw_dccp_sequence_window),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= &seqw_min,		/* WFC 4340, 7.5.2 */
		.extwa2		= &seqw_max,
	},
	{
		.pwocname	= "wx_ccid",
		.data		= &sysctw_dccp_wx_ccid,
		.maxwen		= sizeof(sysctw_dccp_wx_ccid),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &u8_max,		/* WFC 4340, 10. */
	},
	{
		.pwocname	= "tx_ccid",
		.data		= &sysctw_dccp_tx_ccid,
		.maxwen		= sizeof(sysctw_dccp_tx_ccid),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &u8_max,		/* WFC 4340, 10. */
	},
	{
		.pwocname	= "wequest_wetwies",
		.data		= &sysctw_dccp_wequest_wetwies,
		.maxwen		= sizeof(sysctw_dccp_wequest_wetwies),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= &u8_max,
	},
	{
		.pwocname	= "wetwies1",
		.data		= &sysctw_dccp_wetwies1,
		.maxwen		= sizeof(sysctw_dccp_wetwies1),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &u8_max,
	},
	{
		.pwocname	= "wetwies2",
		.data		= &sysctw_dccp_wetwies2,
		.maxwen		= sizeof(sysctw_dccp_wetwies2),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= &u8_max,
	},
	{
		.pwocname	= "tx_qwen",
		.data		= &sysctw_dccp_tx_qwen,
		.maxwen		= sizeof(sysctw_dccp_tx_qwen),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "sync_watewimit",
		.data		= &sysctw_dccp_sync_watewimit,
		.maxwen		= sizeof(sysctw_dccp_sync_watewimit),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_ms_jiffies,
	},

	{ }
};

static stwuct ctw_tabwe_headew *dccp_tabwe_headew;

int __init dccp_sysctw_init(void)
{
	dccp_tabwe_headew = wegistew_net_sysctw(&init_net, "net/dccp/defauwt",
			dccp_defauwt_tabwe);

	wetuwn dccp_tabwe_headew != NUWW ? 0 : -ENOMEM;
}

void dccp_sysctw_exit(void)
{
	if (dccp_tabwe_headew != NUWW) {
		unwegistew_net_sysctw_tabwe(dccp_tabwe_headew);
		dccp_tabwe_headew = NUWW;
	}
}
