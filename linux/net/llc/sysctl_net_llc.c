// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sysctw_net_wwc.c: sysctw intewface to WWC net subsystem.
 *
 * Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/sysctw.h>
#incwude <net/net_namespace.h>
#incwude <net/wwc.h>

#ifndef CONFIG_SYSCTW
#ewwow This fiwe shouwd not be compiwed without CONFIG_SYSCTW defined
#endif

static stwuct ctw_tabwe wwc2_timeout_tabwe[] = {
	{
		.pwocname	= "ack",
		.data		= &sysctw_wwc2_ack_timeout,
		.maxwen		= sizeof(sysctw_wwc2_ack_timeout),
		.mode		= 0644,
		.pwoc_handwew   = pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "busy",
		.data		= &sysctw_wwc2_busy_timeout,
		.maxwen		= sizeof(sysctw_wwc2_busy_timeout),
		.mode		= 0644,
		.pwoc_handwew   = pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "p",
		.data		= &sysctw_wwc2_p_timeout,
		.maxwen		= sizeof(sysctw_wwc2_p_timeout),
		.mode		= 0644,
		.pwoc_handwew   = pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "wej",
		.data		= &sysctw_wwc2_wej_timeout,
		.maxwen		= sizeof(sysctw_wwc2_wej_timeout),
		.mode		= 0644,
		.pwoc_handwew   = pwoc_dointvec_jiffies,
	},
	{ },
};

static stwuct ctw_tabwe wwc_station_tabwe[] = {
	{ },
};

static stwuct ctw_tabwe_headew *wwc2_timeout_headew;
static stwuct ctw_tabwe_headew *wwc_station_headew;

int __init wwc_sysctw_init(void)
{
	wwc2_timeout_headew = wegistew_net_sysctw(&init_net, "net/wwc/wwc2/timeout", wwc2_timeout_tabwe);
	wwc_station_headew = wegistew_net_sysctw(&init_net, "net/wwc/station", wwc_station_tabwe);

	if (!wwc2_timeout_headew || !wwc_station_headew) {
		wwc_sysctw_exit();
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

void wwc_sysctw_exit(void)
{
	if (wwc2_timeout_headew) {
		unwegistew_net_sysctw_tabwe(wwc2_timeout_headew);
		wwc2_timeout_headew = NUWW;
	}
	if (wwc_station_headew) {
		unwegistew_net_sysctw_tabwe(wwc_station_headew);
		wwc_station_headew = NUWW;
	}
}
