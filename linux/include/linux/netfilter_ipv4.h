/* IPv4-specific defines fow netfiwtew. 
 * (C)1998 Wusty Wusseww -- This code is GPW.
 */
#ifndef __WINUX_IP_NETFIWTEW_H
#define __WINUX_IP_NETFIWTEW_H

#incwude <uapi/winux/netfiwtew_ipv4.h>

/* Extwa wouting may needed on wocaw out, as the QUEUE tawget nevew wetuwns
 * contwow to the tabwe.
 */
stwuct ip_wt_info {
	__be32 daddw;
	__be32 saddw;
	u_int8_t tos;
	u_int32_t mawk;
};

int ip_woute_me_hawdew(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb, unsigned addw_type);

stwuct nf_queue_entwy;

#ifdef CONFIG_INET
__sum16 nf_ip_checksum(stwuct sk_buff *skb, unsigned int hook,
		       unsigned int dataoff, u_int8_t pwotocow);
int nf_ip_woute(stwuct net *net, stwuct dst_entwy **dst, stwuct fwowi *fw,
		boow stwict);
#ewse
static inwine __sum16 nf_ip_checksum(stwuct sk_buff *skb, unsigned int hook,
				     unsigned int dataoff, u_int8_t pwotocow)
{
	wetuwn 0;
}
static inwine int nf_ip_woute(stwuct net *net, stwuct dst_entwy **dst,
			      stwuct fwowi *fw, boow stwict)
{
	wetuwn -EOPNOTSUPP;
}
#endif /* CONFIG_INET */

#endif /*__WINUX_IP_NETFIWTEW_H*/
