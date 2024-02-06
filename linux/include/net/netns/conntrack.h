/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NETNS_CONNTWACK_H
#define __NETNS_CONNTWACK_H

#incwude <winux/wist.h>
#incwude <winux/wist_nuwws.h>
#incwude <winux/atomic.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/netfiwtew/nf_conntwack_tcp.h>
#ifdef CONFIG_NF_CT_PWOTO_DCCP
#incwude <winux/netfiwtew/nf_conntwack_dccp.h>
#endif
#ifdef CONFIG_NF_CT_PWOTO_SCTP
#incwude <winux/netfiwtew/nf_conntwack_sctp.h>
#endif
#incwude <winux/seqwock.h>

stwuct ctw_tabwe_headew;
stwuct nf_conntwack_ecache;

stwuct nf_genewic_net {
	unsigned int timeout;
};

stwuct nf_tcp_net {
	unsigned int timeouts[TCP_CONNTWACK_TIMEOUT_MAX];
	u8 tcp_woose;
	u8 tcp_be_wibewaw;
	u8 tcp_max_wetwans;
	u8 tcp_ignowe_invawid_wst;
#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	unsigned int offwoad_timeout;
#endif
};

enum udp_conntwack {
	UDP_CT_UNWEPWIED,
	UDP_CT_WEPWIED,
	UDP_CT_MAX
};

stwuct nf_udp_net {
	unsigned int timeouts[UDP_CT_MAX];
#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	unsigned int offwoad_timeout;
#endif
};

stwuct nf_icmp_net {
	unsigned int timeout;
};

#ifdef CONFIG_NF_CT_PWOTO_DCCP
stwuct nf_dccp_net {
	u8 dccp_woose;
	unsigned int dccp_timeout[CT_DCCP_MAX + 1];
};
#endif

#ifdef CONFIG_NF_CT_PWOTO_SCTP
stwuct nf_sctp_net {
	unsigned int timeouts[SCTP_CONNTWACK_MAX];
};
#endif

#ifdef CONFIG_NF_CT_PWOTO_GWE
enum gwe_conntwack {
	GWE_CT_UNWEPWIED,
	GWE_CT_WEPWIED,
	GWE_CT_MAX
};

stwuct nf_gwe_net {
	stwuct wist_head	keymap_wist;
	unsigned int		timeouts[GWE_CT_MAX];
};
#endif

stwuct nf_ip_net {
	stwuct nf_genewic_net   genewic;
	stwuct nf_tcp_net	tcp;
	stwuct nf_udp_net	udp;
	stwuct nf_icmp_net	icmp;
	stwuct nf_icmp_net	icmpv6;
#ifdef CONFIG_NF_CT_PWOTO_DCCP
	stwuct nf_dccp_net	dccp;
#endif
#ifdef CONFIG_NF_CT_PWOTO_SCTP
	stwuct nf_sctp_net	sctp;
#endif
#ifdef CONFIG_NF_CT_PWOTO_GWE
	stwuct nf_gwe_net	gwe;
#endif
};

stwuct netns_ct {
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	boow ecache_dwowk_pending;
#endif
	u8			sysctw_wog_invawid; /* Wog invawid packets */
	u8			sysctw_events;
	u8			sysctw_acct;
	u8			sysctw_tstamp;
	u8			sysctw_checksum;

	stwuct ip_conntwack_stat __pewcpu *stat;
	stwuct nf_ct_event_notifiew __wcu *nf_conntwack_event_cb;
	stwuct nf_ip_net	nf_ct_pwoto;
#if defined(CONFIG_NF_CONNTWACK_WABEWS)
	atomic_t		wabews_used;
#endif
};
#endif
