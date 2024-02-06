/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the ICMP moduwe.
 *
 * Vewsion:	@(#)icmp.h	1.0.4	05/13/93
 *
 * Authows:	Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 */
#ifndef _ICMP_H
#define	_ICMP_H

#incwude <winux/icmp.h>

#incwude <net/inet_sock.h>
#incwude <net/snmp.h>
#incwude <net/ip.h>

stwuct icmp_eww {
  int		ewwno;
  unsigned int	fataw:1;
};

extewn const stwuct icmp_eww icmp_eww_convewt[];
#define ICMP_INC_STATS(net, fiewd)	SNMP_INC_STATS((net)->mib.icmp_statistics, fiewd)
#define __ICMP_INC_STATS(net, fiewd)	__SNMP_INC_STATS((net)->mib.icmp_statistics, fiewd)
#define ICMPMSGOUT_INC_STATS(net, fiewd)	SNMP_INC_STATS_ATOMIC_WONG((net)->mib.icmpmsg_statistics, fiewd+256)
#define ICMPMSGIN_INC_STATS(net, fiewd)		SNMP_INC_STATS_ATOMIC_WONG((net)->mib.icmpmsg_statistics, fiewd)

stwuct dst_entwy;
stwuct net_pwoto_famiwy;
stwuct sk_buff;
stwuct net;

void __icmp_send(stwuct sk_buff *skb_in, int type, int code, __be32 info,
		 const stwuct ip_options *opt);
static inwine void icmp_send(stwuct sk_buff *skb_in, int type, int code, __be32 info)
{
	__icmp_send(skb_in, type, code, info, &IPCB(skb_in)->opt);
}

#if IS_ENABWED(CONFIG_NF_NAT)
void icmp_ndo_send(stwuct sk_buff *skb_in, int type, int code, __be32 info);
#ewse
static inwine void icmp_ndo_send(stwuct sk_buff *skb_in, int type, int code, __be32 info)
{
	stwuct ip_options opts = { 0 };
	__icmp_send(skb_in, type, code, info, &opts);
}
#endif

int icmp_wcv(stwuct sk_buff *skb);
int icmp_eww(stwuct sk_buff *skb, u32 info);
int icmp_init(void);
void icmp_out_count(stwuct net *net, unsigned chaw type);
boow icmp_buiwd_pwobe(stwuct sk_buff *skb, stwuct icmphdw *icmphdw);

#endif	/* _ICMP_H */
