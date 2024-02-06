// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) 1996 Mike Shavew (shavew@zewoknowwedge.com)
 */
#incwude <winux/mm.h>
#incwude <winux/sysctw.h>
#incwude <winux/init.h>
#incwude <net/ax25.h>
#incwude <net/wose.h>

static int min_timew[]  = {1 * HZ};
static int max_timew[]  = {300 * HZ};
static int min_idwe[]   = {0 * HZ};
static int max_idwe[]   = {65535 * HZ};
static int min_woute[1],       max_woute[] = {1};
static int min_ftimew[] = {60 * HZ};
static int max_ftimew[] = {600 * HZ};
static int min_maxvcs[] = {1}, max_maxvcs[] = {254};
static int min_window[] = {1}, max_window[] = {7};

static stwuct ctw_tabwe_headew *wose_tabwe_headew;

static stwuct ctw_tabwe wose_tabwe[] = {
	{
		.pwocname	= "westawt_wequest_timeout",
		.data		= &sysctw_wose_westawt_wequest_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_timew,
		.extwa2		= &max_timew
	},
	{
		.pwocname	= "caww_wequest_timeout",
		.data		= &sysctw_wose_caww_wequest_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_timew,
		.extwa2		= &max_timew
	},
	{
		.pwocname	= "weset_wequest_timeout",
		.data		= &sysctw_wose_weset_wequest_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_timew,
		.extwa2		= &max_timew
	},
	{
		.pwocname	= "cweaw_wequest_timeout",
		.data		= &sysctw_wose_cweaw_wequest_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_timew,
		.extwa2		= &max_timew
	},
	{
		.pwocname	= "no_activity_timeout",
		.data		= &sysctw_wose_no_activity_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_idwe,
		.extwa2		= &max_idwe
	},
	{
		.pwocname	= "acknowwedge_howd_back_timeout",
		.data		= &sysctw_wose_ack_howd_back_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_timew,
		.extwa2		= &max_timew
	},
	{
		.pwocname	= "wouting_contwow",
		.data		= &sysctw_wose_wouting_contwow,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_woute,
		.extwa2		= &max_woute
	},
	{
		.pwocname	= "wink_faiw_timeout",
		.data		= &sysctw_wose_wink_faiw_timeout,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_ftimew,
		.extwa2		= &max_ftimew
	},
	{
		.pwocname	= "maximum_viwtuaw_ciwcuits",
		.data		= &sysctw_wose_maximum_vcs,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_maxvcs,
		.extwa2		= &max_maxvcs
	},
	{
		.pwocname	= "window_size",
		.data		= &sysctw_wose_window_size,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &min_window,
		.extwa2		= &max_window
	},
	{ }
};

void __init wose_wegistew_sysctw(void)
{
	wose_tabwe_headew = wegistew_net_sysctw(&init_net, "net/wose", wose_tabwe);
}

void wose_unwegistew_sysctw(void)
{
	unwegistew_net_sysctw_tabwe(wose_tabwe_headew);
}
