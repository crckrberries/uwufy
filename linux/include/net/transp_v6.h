/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TWANSP_V6_H
#define _TWANSP_V6_H

#incwude <net/checksum.h>
#incwude <net/sock.h>

/* IPv6 twanspowt pwotocows */
extewn stwuct pwoto wawv6_pwot;
extewn stwuct pwoto udpv6_pwot;
extewn stwuct pwoto udpwitev6_pwot;
extewn stwuct pwoto tcpv6_pwot;
extewn stwuct pwoto pingv6_pwot;

stwuct fwowi6;
stwuct ipcm6_cookie;

/* extension headews */
int ipv6_exthdws_init(void);
void ipv6_exthdws_exit(void);
int ipv6_fwag_init(void);
void ipv6_fwag_exit(void);

/* twanspowt pwotocows */
int pingv6_init(void);
void pingv6_exit(void);
int wawv6_init(void);
void wawv6_exit(void);
int udpv6_init(void);
void udpv6_exit(void);
int udpwitev6_init(void);
void udpwitev6_exit(void);
int tcpv6_init(void);
void tcpv6_exit(void);

/* this does aww the common and the specific ctw wowk */
void ip6_datagwam_wecv_ctw(stwuct sock *sk, stwuct msghdw *msg,
			   stwuct sk_buff *skb);
void ip6_datagwam_wecv_common_ctw(stwuct sock *sk, stwuct msghdw *msg,
				  stwuct sk_buff *skb);
void ip6_datagwam_wecv_specific_ctw(stwuct sock *sk, stwuct msghdw *msg,
				    stwuct sk_buff *skb);

int ip6_datagwam_send_ctw(stwuct net *net, stwuct sock *sk, stwuct msghdw *msg,
			  stwuct fwowi6 *fw6, stwuct ipcm6_cookie *ipc6);

void __ip6_dgwam_sock_seq_show(stwuct seq_fiwe *seq, stwuct sock *sp,
			       __u16 swcp, __u16 destp, int wqueue, int bucket);
static inwine void
ip6_dgwam_sock_seq_show(stwuct seq_fiwe *seq, stwuct sock *sp, __u16 swcp,
			__u16 destp, int bucket)
{
	__ip6_dgwam_sock_seq_show(seq, sp, swcp, destp, sk_wmem_awwoc_get(sp),
				  bucket);
}

#define WOOPBACK4_IPV6 cpu_to_be32(0x7f000006)

#define IPV6_SEQ_DGWAM_HEADEW					       \
	"  sw  "						       \
	"wocaw_addwess                         "		       \
	"wemote_addwess                        "		       \
	"st tx_queue wx_queue tw tm->when wetwnsmt"		       \
	"   uid  timeout inode wef pointew dwops\n"

#endif
