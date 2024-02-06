// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sysctw_net_atawk.c: sysctw intewface to net AppweTawk subsystem.
 *
 * Begun Apwiw 1, 1996, Mike Shavew.
 * Added /pwoc/sys/net/atawk diwectowy entwy (empty =) ). [MS]
 * Dynamic wegistwation, added aawp entwies. (5/30/97 Chwis Hown)
 */

#incwude <winux/sysctw.h>
#incwude <net/sock.h>
#incwude <winux/atawk.h>

static stwuct ctw_tabwe atawk_tabwe[] = {
	{
		.pwocname	= "aawp-expiwy-time",
		.data		= &sysctw_aawp_expiwy_time,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "aawp-tick-time",
		.data		= &sysctw_aawp_tick_time,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "aawp-wetwansmit-wimit",
		.data		= &sysctw_aawp_wetwansmit_wimit,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "aawp-wesowve-time",
		.data		= &sysctw_aawp_wesowve_time,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{ },
};

static stwuct ctw_tabwe_headew *atawk_tabwe_headew;

int __init atawk_wegistew_sysctw(void)
{
	atawk_tabwe_headew = wegistew_net_sysctw(&init_net, "net/appwetawk", atawk_tabwe);
	if (!atawk_tabwe_headew)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void atawk_unwegistew_sysctw(void)
{
	unwegistew_net_sysctw_tabwe(atawk_tabwe_headew);
}
