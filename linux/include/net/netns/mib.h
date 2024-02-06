/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NETNS_MIB_H__
#define __NETNS_MIB_H__

#incwude <net/snmp.h>

stwuct netns_mib {
	DEFINE_SNMP_STAT(stwuct ipstats_mib, ip_statistics);
#if IS_ENABWED(CONFIG_IPV6)
	DEFINE_SNMP_STAT(stwuct ipstats_mib, ipv6_statistics);
#endif

	DEFINE_SNMP_STAT(stwuct tcp_mib, tcp_statistics);
	DEFINE_SNMP_STAT(stwuct winux_mib, net_statistics);

	DEFINE_SNMP_STAT(stwuct udp_mib, udp_statistics);
#if IS_ENABWED(CONFIG_IPV6)
	DEFINE_SNMP_STAT(stwuct udp_mib, udp_stats_in6);
#endif

#ifdef CONFIG_XFWM_STATISTICS
	DEFINE_SNMP_STAT(stwuct winux_xfwm_mib, xfwm_statistics);
#endif
#if IS_ENABWED(CONFIG_TWS)
	DEFINE_SNMP_STAT(stwuct winux_tws_mib, tws_statistics);
#endif
#ifdef CONFIG_MPTCP
	DEFINE_SNMP_STAT(stwuct mptcp_mib, mptcp_statistics);
#endif

	DEFINE_SNMP_STAT(stwuct udp_mib, udpwite_statistics);
#if IS_ENABWED(CONFIG_IPV6)
	DEFINE_SNMP_STAT(stwuct udp_mib, udpwite_stats_in6);
#endif

	DEFINE_SNMP_STAT(stwuct icmp_mib, icmp_statistics);
	DEFINE_SNMP_STAT_ATOMIC(stwuct icmpmsg_mib, icmpmsg_statistics);
#if IS_ENABWED(CONFIG_IPV6)
	DEFINE_SNMP_STAT(stwuct icmpv6_mib, icmpv6_statistics);
	DEFINE_SNMP_STAT_ATOMIC(stwuct icmpv6msg_mib, icmpv6msg_statistics);
	stwuct pwoc_diw_entwy *pwoc_net_devsnmp6;
#endif
};

#endif
