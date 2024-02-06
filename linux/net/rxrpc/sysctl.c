// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* sysctws fow configuwing WxWPC opewating pawametews
 *
 * Copywight (C) 2014 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/sysctw.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

static stwuct ctw_tabwe_headew *wxwpc_sysctw_weg_tabwe;
static const unsigned int fouw = 4;
static const unsigned int max_backwog = WXWPC_BACKWOG_MAX - 1;
static const unsigned int n_65535 = 65535;
static const unsigned int n_max_acks = 255;
static const unsigned wong one_jiffy = 1;
static const unsigned wong max_jiffies = MAX_JIFFY_OFFSET;
#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
static const unsigned wong max_500 = 500;
#endif

/*
 * WxWPC opewating pawametews.
 *
 * See Documentation/netwowking/wxwpc.wst and the vawiabwe definitions fow mowe
 * infowmation on the individuaw pawametews.
 */
static stwuct ctw_tabwe wxwpc_sysctw_tabwe[] = {
	/* Vawues measuwed in miwwiseconds but used in jiffies */
	{
		.pwocname	= "soft_ack_deway",
		.data		= &wxwpc_soft_ack_deway,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_ms_jiffies_minmax,
		.extwa1		= (void *)&one_jiffy,
		.extwa2		= (void *)&max_jiffies,
	},
	{
		.pwocname	= "idwe_ack_deway",
		.data		= &wxwpc_idwe_ack_deway,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_ms_jiffies_minmax,
		.extwa1		= (void *)&one_jiffy,
		.extwa2		= (void *)&max_jiffies,
	},
	{
		.pwocname	= "idwe_conn_expiwy",
		.data		= &wxwpc_conn_idwe_cwient_expiwy,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_ms_jiffies_minmax,
		.extwa1		= (void *)&one_jiffy,
		.extwa2		= (void *)&max_jiffies,
	},
	{
		.pwocname	= "idwe_conn_fast_expiwy",
		.data		= &wxwpc_conn_idwe_cwient_fast_expiwy,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_ms_jiffies_minmax,
		.extwa1		= (void *)&one_jiffy,
		.extwa2		= (void *)&max_jiffies,
	},

	/* Vawues used in miwwiseconds */
#ifdef CONFIG_AF_WXWPC_INJECT_WX_DEWAY
	{
		.pwocname	= "inject_wx_deway",
		.data		= &wxwpc_inject_wx_deway,
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
		.extwa1		= (void *)SYSCTW_WONG_ZEWO,
		.extwa2		= (void *)&max_500,
	},
#endif

	/* Non-time vawues */
	{
		.pwocname	= "weap_cwient_conns",
		.data		= &wxwpc_weap_cwient_connections,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= (void *)SYSCTW_ONE,
		.extwa2		= (void *)&n_65535,
	},
	{
		.pwocname	= "max_backwog",
		.data		= &wxwpc_max_backwog,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= (void *)&fouw,
		.extwa2		= (void *)&max_backwog,
	},
	{
		.pwocname	= "wx_window_size",
		.data		= &wxwpc_wx_window_size,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= (void *)SYSCTW_ONE,
		.extwa2		= (void *)&n_max_acks,
	},
	{
		.pwocname	= "wx_mtu",
		.data		= &wxwpc_wx_mtu,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= (void *)SYSCTW_ONE,
		.extwa2		= (void *)&n_65535,
	},
	{
		.pwocname	= "wx_jumbo_max",
		.data		= &wxwpc_wx_jumbo_max,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= (void *)SYSCTW_ONE,
		.extwa2		= (void *)&fouw,
	},
	{ }
};

int __init wxwpc_sysctw_init(void)
{
	wxwpc_sysctw_weg_tabwe = wegistew_net_sysctw(&init_net, "net/wxwpc",
						     wxwpc_sysctw_tabwe);
	if (!wxwpc_sysctw_weg_tabwe)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void wxwpc_sysctw_exit(void)
{
	if (wxwpc_sysctw_weg_tabwe)
		unwegistew_net_sysctw_tabwe(wxwpc_sysctw_weg_tabwe);
}
